// GPFrameWnd.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPFrameWnd.h"
#include "GP_DlgSetting.h"
#include "GP_TermDoc.h"
#include "GPStatusBarCtrl.h"
#include "GPToolBarCtrl.h"
#include "GPStatusBar.h"
#include "GPToolBar.h"
#include "GPToolTipCtrl.h"
#include "GP_TermView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPFrameWnd
const UINT GPFrameWnd::uNMethods=29;
const char *GPFrameWnd::cArrMethods[]={
		"LoadBarState","SaveBarState","ShowControlBar","ActivateFrame",	"IsTracking",
		"SetMessageText","EnableDocking","DockControlBar","FloatControlBar","BeginModalState",
		"EndModalState","InModalState","ShowOwnedWindows","RecalcLayout","AddScroller",
		"DelScroller","SetScroller","UpdateScloller","SetScrollerPos","EnsureVisibleScroller",
		"AutoSetAutoSizing","AutoSizingPause","AutoSizingResume","AutoSizingReset","AutoSizingReinitSize",
		"Reposition","GetObjectByHWND","GetObjectsList","GetScrollerPos","",
		"","","", "", "", 
	};
const char *GPFrameWnd::cArrMethodsParams[]={
		"SectionName","SectionName","nUnit,bShow,bDelay","WndShowStyle","",
		"Text","CtrlBarStyle","nUnit,TOP|LEFT|RIGHT|BOTTOM|FLOAT","nUnit,poX,poY,TOP|LEFT|RIGHT|BOTTOM","",
		"","","bShow","","ScrName,ObjName,nX,nY,nXPage,nYPage[,Flags]",
		"ScrName","ScrName,[nX],[nY],[nXPage],[nYPage][,Flags]","ScrName","ScrName,X,Y","",
		"","","","","",
		"","","","ScrName","",
		"","","", "", "", 
	};

IMPLEMENT_DYNCREATE(GPFrameWnd, CFrameWnd)

GPFrameWnd::GPFrameWnd()
{
	m_LastSizeType=0;
	m_NGPUNITmax=NINITIALUNITS;
	GPU= new GPUnit * [NINITIALUNITS];
	ZeroMemory(GPU,sizeof(GPUnit *)*NINITIALUNITS);
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwCreateFrm++;
	nUnitENTIRE=0;
	m_CDlgDialogEditor=NULL;
	DlgAutoSize=NULL;
	DlgGPMenu=NULL;
	DlgMenu=NULL;
	iStr=NULL;

	m_ToolTip=new CGPToolTipCtrl;
	nScroller=0;
	nMaxScroller=9;
	ScrollerArr=new CGPScroller * [nMaxScroller];
	ZeroMemory(ScrollerArr,sizeof(CGPScroller *)*nMaxScroller);
}

BOOL GPFrameWnd::GPCreate(UINT iId, const char *iiStr, CWnd* pParent )
{
	IdDlg=iId;
	iStr=new char [5000];
	strcpy(iStr,iiStr);

	int IdParent=0;
	int IdDlg=0;
	m_LastScanf=sscanf(iStr,"%d,%d",&IdDlg,&IdParent);

	CWnd *tmpParent=pParent;

	UINT iS=0,iSex=0,PN=0;
	CRect iRe(50,50,150,100);
	char Capt[1000];*Capt=0;
	char m_CLSID[1000];*m_CLSID=0;
	DWORD tmpScale=GPC.m_GUISet.Scale;

	GPUnit::GetInitParam(NULL,0,iStr,iS,iSex,iRe,Capt,&PN,m_CLSID,tmpScale);
	BOOL visflg=FALSE;
	if ((iS&WS_VISIBLE)==WS_VISIBLE)
	{
		visflg=TRUE;
		iS^=WS_VISIBLE;
		char *tmppos=strstr(iStr,"WS_VISIBLE");
		if (tmppos!=NULL) *tmppos='_';
	}
	if (PN<MAX_OBJDLG && PN!=(UINT)IdDlg && GPC.m_Document->a_GPObjDialog[PN]!=NULL)
	{
		if (GPC.m_Document->a_GPObjType[PN]==0)
			tmpParent=CWnd::FromHandle(((GPObjDialog *)GPC.m_Document->a_GPObjDialog[PN])->m_hWnd);
		else
			tmpParent=CWnd::FromHandle(((GPFrameWnd *)GPC.m_Document->a_GPObjDialog[PN])->m_hWnd);
	}


	if ((iS&WS_POPUP)!=WS_POPUP && (iS&WS_CHILD)!=WS_CHILD)	iS|=WS_POPUP;



	Create(AfxRegisterWndClass(CS_VREDRAW|CS_HREDRAW|CS_DBLCLKS),
				Capt,		iS,			iRe,
				tmpParent,	NULL, 		iSex,		NULL 	);


	if (visflg==TRUE)  ShowWindow(SW_SHOW);

	DlgAutoSize=new GP_AutoSizing;
	DlgAutoSize->AddSetMain(this->m_hWnd);

	CRect MinimumRecr;
	GetWindowRect(&MinimumRecr);
	DlgAutoSize->SetMinSize(this->m_hWnd,MinimumRecr.Width(),MinimumRecr.Height());

	m_ToolTip->GPCreate(m_hWnd,IdDlg,iStr,GPU);
	*GPU= new GPUnit(0+IS_DLG_UNIT+IdDlg*0x10000,0,iStr,GPU,&m_ToolTip,this->m_hWnd,DlgAutoSize);

	if (GPU && GPU[0]!=NULL)
		GPU[0]->UnitPtr=this;

	m_ToolTip->Activate(TRUE);
	EnableToolTips(TRUE);
	EnableTrackingToolTips(TRUE);

	return TRUE;  
}

GPFrameWnd::~GPFrameWnd()
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwDeleteFrm++;
	if (ScrollerArr)
	{
		UINT i;
		for(i=0;i<nScroller;i++)
			if (ScrollerArr[i]) delete ScrollerArr[i];
		delete[] ScrollerArr;
		ScrollerArr=NULL;
	}

	try
	{
		if (m_CDlgDialogEditor!=NULL)
		{
			m_CDlgDialogEditor->DestroyWindow();
			delete m_CDlgDialogEditor;
		}
	}catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPFrameWnd", "~GPFrameWnd","");
	}
	m_CDlgDialogEditor=NULL;
	ClearDialog();
	if (DlgAutoSize!=NULL) delete DlgAutoSize;
	DlgAutoSize=NULL;
}


BEGIN_MESSAGE_MAP(GPFrameWnd, CFrameWnd)
	//{{AFX_MSG_MAP(GPFrameWnd)
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_NCHITTEST()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_SIZING()
	//}}AFX_MSG_MAP
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPFrameWnd message handlers

GPMenu *GPFrameWnd::CreateDlgMenu()
{
	if (DlgMenu==NULL) 
	{
		DlgMenu=new CMenu;
		DlgMenu->CreateMenu();
		SetMenu(DlgMenu);
		DlgGPMenu=new GPMenu(this->m_hWnd,1);
	}
	return DlgGPMenu;
}

BOOL GPFrameWnd::DeleteDlgMenu()
{
	BOOL ret=FALSE;
	if (DlgGPMenu!=NULL)
	{
		delete DlgGPMenu;
		DlgGPMenu=NULL;
	}
	if (DlgMenu!=NULL) 
	{
		ret=TRUE;
		delete DlgMenu;
		DlgMenu=NULL;
		SetMenu(DlgMenu);
	}
	return ret;
}

void GPFrameWnd::ClearDialog()
{
	if (GPU && *GPU)
	{
		int i;
		for(i=1;(UINT)i<(*GPU)->m_NGPUNIT;i++) 
			if (GPU[i]!=NULL) DeleteUnit(i, FALSE);

		(*GPU)->UnitHWND=NULL;
		delete *GPU;
		*GPU=NULL;
	}

	if (GPU)	delete[] GPU;
	GPU=NULL;

	if (DlgGPMenu!=NULL) delete DlgGPMenu;
	DlgGPMenu=NULL;

	if (DlgMenu!=NULL) delete DlgMenu;
	DlgMenu=NULL;

	if (iStr!=NULL) delete[] iStr;
	iStr=NULL;

	if (m_ToolTip!=NULL) delete m_ToolTip;
	m_ToolTip=NULL;
}

void GPFrameWnd::DelAllHotkey()
{
	if (GPU && GPU[0]) GPU[0]->DelAllHotkey();
}

BOOL GPFrameWnd::DelHotkey(UINT iId, const char *iHotkeyName)
{
	BOOL ret=FALSE;
	if (GPU && GPU[0]) ret=GPU[0]->DelHotkey(iId,iHotkeyName);
	return ret;
}

BOOL GPFrameWnd::AddHotkey(char *nm_VK, UINT iId, const char *seq)
{
	BOOL ret=FALSE;
	if (GPU && GPU[0]) ret=GPU[0]->AddHotkey(nm_VK,iId,seq);
	return ret;
}

GPUnit * GPFrameWnd::GetUnit(UINT iUnitId)
{
	GPUnit *tmp=NULL;
	if (iUnitId<(*GPU)->m_NGPUNIT) tmp=GPU[iUnitId];

	return tmp;
}

void GPFrameWnd::OnSize(UINT nType, int cx, int cy) 
{
	BOOL DOIT=TRUE;
	if (DlgAutoSize)
		DOIT=DlgAutoSize->CheckMainSize(m_hWnd,nType,&cx, &cy);
	if (DOIT)
		CFrameWnd::OnSize(nType, cx, cy);
	else 
		if (cx>0 && cy>0) Invalidate();

	if (m_hWnd)
	{
		if (GPU!=NULL && GPU[0])
			GPU[0]->UpdateSizerSize();
	}

	if (DlgAutoSize!=NULL && nType!=SIZE_MINIMIZED) 
		if ((GetWindowLong(m_hWnd,GWL_STYLE)&WS_POPUP)==WS_POPUP)
		{
			//LockWindowUpdate();
			DlgAutoSize->UpdateSize();
			//UnlockWindowUpdate();
		}
		else
			DlgAutoSize->UpdateSize();

	if (nType!=SIZE_MINIMIZED && GPU!=NULL)
	{
		int i;
		if (GPU && *GPU)
		for(i=1;(UINT)i<(*GPU)->m_NGPUNIT;i++) 
			if (GPU[i] && GPU[i]->UnitHWND)
			{
				switch(GPU[i]->UnitType)
				{
				case GPUnit::UT_DLGBAR:
					{
						CWnd *tmp=CWnd::FromHandle(GPU[i]->UnitHWND);
						if (tmp->IsZoomed() && (tmp->GetStyle()&WS_CHILD)==WS_CHILD) 
						{
							CRect re;
							GetClientRect(&re);
							tmp->MoveWindow(re);
						}
					}
					break;
				case GPUnit::UT_TOOLBARCTRL:
					((GPToolBarCtrl*)GPU[i]->UnitPtr)->AutoSize();	
					break;
				case GPUnit::UT_TOOLBAR:
				case GPUnit::UT_STATUSBAR:
				case GPUnit::UT_STATUSBARCTRL:
//l					CWnd::FromHandle(GPU[i]->UnitHWND)->SendMessage(WM_SIZEPARENT,nType,cx+cy*0x10000);
					break;
				}
			}
	}
	UpdateScrollers();
//	RecalcLayout();
//	this->RepositionBars(AFX_IDW_PANE_FIRST ,AFX_IDW_PANE_LAST,AFX_IDW_PANE_FIRST);
//	Invalidate();
	m_LastSizeType=m_LastSizeType*0x100+nType;
}


BOOL GPFrameWnd::AskExit()
{
	BOOL ret=FALSE;
#ifdef RUS
	if (MessageBox("������� ������ ��� ���������� ������?",GPC.MsgBoxCaption,MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2)==IDYES)
#else
	if (MessageBox("Close Dialog and discard changes?",GPC.MsgBoxCaption,MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2)==IDYES)
#endif
	{
		GetParent()->EnableWindow();
		GPEndDlg();
		GPC.m_Document->DeleteObjDlg(IdDlg,FALSE,TRUE);
		ret=TRUE;
	}
	return ret;
}

/*
void GPFrameWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	if (GPU!=NULL)
	{
		int i;
		for(i=0;i<NGPUNIT;i++) 
			if (GPU[i]!=NULL && (GPU[i]->UnitType==1 
				|| GPU[i]->UnitType==2 || GPU[i]->UnitType==3 
				|| GPU[i]->UnitType==10)) 
			{
				CRect ClRe,WRe(0,0,80,25);
				GetClientRect(&ClRe);
				GPU[i]->UnitPaint(&dc,WRe,ClRe);	
			}
	}
}
*/

UINT GPFrameWnd::CreateUnit(UINT iType, UINT iId, const char *iInit, HWND pParentWnd)
{
	UINT ret=0;
	CString tpms;
	tpms.Format("object %d",iId);
	if (iId>=m_NGPUNITmax && iId<0x10000)
	{
		UINT newNMax=iId+5000;
		if (newNMax>0x10000) newNMax=0xFFFF;
		GPUnit **GPUtmp= new GPUnit * [newNMax];
		ZeroMemory(GPUtmp,sizeof(GPUnit *)*newNMax);
		UINT i;
		GPUtmp[0]=GPU[0];
		for(i=1;i<GPU[0]->m_NGPUNIT;i++)
			if ((GPUtmp[i]=GPU[i]))
			{
				GPUtmp[i]->GPU=GPUtmp;
				GPUtmp[i]->SetReferGPU(GPUtmp);
				GPUtmp[i]->GPMSG->SetReferGPU(GPUtmp);
			}

		GPUtmp[0]->GPU=GPUtmp;
		GPUtmp[0]->GPMSG->SetReferGPU(GPUtmp);
		delete []GPU;
		GPU=GPUtmp;
		m_NGPUNITmax=newNMax;
	}
	if (iId>0 && GPU!=NULL && iId<m_NGPUNITmax)
	{
		if (GPU[iId]==NULL)
		{
			if (iId>=GPU[0]->m_NGPUNIT) GPU[0]->m_NGPUNIT=iId+1;
			GPU[iId]=new GPUnit(iId+IS_DLG_UNIT+IdDlg*0x10000,iType,iInit,GPU,&m_ToolTip,GPU[0]->UnitHWND,DlgAutoSize);
			if (GPU[iId])
			{
				UINT ro=GPU[iId]->GetResizeingOwner();
				CRect re;
				if (ro>0 && ro<GPU[0]->m_NGPUNIT && GPU[ro])
				{	
					GPU[ro]->GPGetWndRect(&re);
				}
				else
				{
					GetClientRect(&re);
					if (re.IsRectEmpty()==FALSE) re.OffsetRect(-re.TopLeft());
				}
				switch(GPU[iId]->UnitType)
				{
					case GPUnit::UT_TOOLBAR:
						((GPToolBar*)GPU[iId]->UnitPtr)->SetDropDownMenu(&DlgGPMenu);	
						break;
					case GPUnit::UT_TOOLBARCTRL:
						((GPToolBarCtrl*)GPU[iId]->UnitPtr)->SetDropDownMenu(&DlgGPMenu);	
						break;
					case GPUnit::UT_STATUSBAR:
					case GPUnit::UT_STATUSBARCTRL:
						//UnitHWND=((GPStatusBar*)UnitPtr)->m_hWnd;
						break;
				}
				ret=iId;
			}
			else GPC.m_ErrReport.GPWriteErrorLog2("Can't create object",tpms ,iInit);
		}
		else GPC.m_ErrReport.GPWriteErrorLog2("Object already exist",tpms ,iInit);
	}
	else GPC.m_ErrReport.GPWriteErrorLog2("Can't create object",tpms ,iInit);

	return ret;
}

void GPFrameWnd::DeleteUnit(UINT iId, BOOL bReport)
{
	BOOL rep=FALSE;
	if (iId>0)
	{
		if (iId<GPU[0]->m_NGPUNIT && GPU[iId])
		{
			if (GPU[iId]==GPUnit::m_ptrUnitValChange) 
			{
				GPUnit::m_ptrUnitValChange=NULL;
//					TRACE("m_ptrUnitValChange=NULL DeleteUnit %s\n",GPU[iId]->UnitInfoToString("\x01") );
			}
			UINT i;
			for(i=1;i<GPU[0]->m_NGPUNIT;i++)
				if (GPU[i] && i!=iId)
				{
					if (GPU[i]->UnitHWND && ::GetParent(GPU[i]->UnitHWND)==GPU[iId]->UnitHWND)
					{
						if (bReport)
						{
							CString tpms=GPU[iId]->UnitInfoToString("\x01")+"\x02"+GPU[i]->UnitInfoToString("\x01");
							GPC.m_ErrReport.GPWriteWarnLog("Implicit deleting of child object",GPU[0]->UnitInfoToString("\x01") ,tpms);
						}
						DeleteUnit(i, bReport);
					}
				}

			if (GPU[iId]->UnitHWND && !GPU[iId]->m_WindowLessFlag && ::IsWindow(GPU[iId]->UnitHWND))
			{
				::SetWindowLong(GPU[iId]->UnitHWND,GWL_STYLE,::GetWindowLong(GPU[iId]->UnitHWND,GWL_STYLE)|WS_DISABLED);
				//::DestroyWindow(GPU[iId]->UnitHWND);
			}
			delete GPU[iId];
			GPU[iId]=NULL;
			for(i=iId+1;i<GPU[0]->m_NGPUNIT && !GPU[i];i++)
			if (i>=GPU[0]->m_NGPUNIT)
			{
				GPU[0]->m_NGPUNIT=iId;
				for(i=iId;i>0 && !GPU[i];i--)
					GPU[0]->m_NGPUNIT=i;
			}
			RecalcLayout();
		}
		else rep=TRUE;
	}
	else rep=TRUE;

	if (bReport && rep)
	{
		CString tpms;
		tpms.Format("dialog %d  object %d",IdDlg, iId);
		GPC.m_ErrReport.GPWriteWarnLog("Try to delete nonexistent object",tpms ,"");
	}
}

void GPFrameWnd::DoMethod(UINT iId, const char *iStr, char *oStr)
{
	if (iId!=0)
	{	
		if (iId<(*GPU)->m_NGPUNIT && GPU[iId]) GPU[iId]->DoMethod(iStr, oStr);
	}
	else DoDlgMethod(iStr, oStr);
}

void GPFrameWnd::DoDlgMethod(const char *iStr, char *oStr)
{
	char met[150];
	strncpy(met,iStr,145);
	met[145]=0;
	
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc=0;
	int retint=-123456; 

	if (*met>='0' && *met<='9') nfunc=atoi(met);
	else
	{
		static const char *sccArrMethods[sizeof(cArrMethods)/sizeof(char *)];
		static DWORD scdMethodsId[sizeof(cArrMethods)/sizeof(char *)];
		if (!*sccArrMethods)
		{
			DWORD i;
			for(i=0;i<uNMethods;i++)
			{
				sccArrMethods[i]=cArrMethods[i];
				scdMethodsId[i]=i;
			}
			qsCharILineAndDWORD(sccArrMethods, scdMethodsId, 0, uNMethods-1);
			scdMethodsId[i]=i;
		}
		nfunc=scdMethodsId[FindInSortArrayIC(met, sccArrMethods, uNMethods)];
	}

	switch(nfunc)
	{
	case 0: /*LoadBarState*/	LoadBarState(pos);		break;
	case 1: /*SaveBarState*/	SaveBarState(pos);		break;
	case 2: /*ShowControlBar*/
		{
			int nUnit=-1;
			int bShow=1,bDelay=0;
			m_LastScanf=sscanf(pos,"%d,%d,%d",&nUnit,&bShow,&bDelay);
			if (nUnit>0 && GPU && (UINT)nUnit<(*GPU)->m_NGPUNIT && GPU[nUnit] && GPU[nUnit]->UnitPtr)
			switch(GPU[nUnit]->UnitType)
			{
			case GPUnit::UT_STATUSBAR: 
				ShowControlBar((GPStatusBar *)GPU[nUnit]->UnitPtr,bShow,bDelay);break;
			case GPUnit::UT_TOOLBAR:
				ShowControlBar((GPToolBar *)GPU[nUnit]->UnitPtr,bShow,bDelay);break;
			}// end TypeUnit Switch
		}
		break;
	case 3: /*ActivateFrame*/
		{
			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
			_strupr(pos333);
			if (*pos333==0) ActivateFrame();
			else
			{
				int i;
				for(i=0; i < N_WND_SHOW_STYLES && strstr(pos333,aWndShowStyleName[i])==NULL; i++);
				if (i<N_WND_SHOW_STYLES)
					ActivateFrame(aWndShowStyleUINT[i]);
			}
			delete[] pos333;
		}
		break;
	case 4: /*IsTracking*/		retint=IsTracking();	break;
	case 5: /*SetMessageText*/	SetMessageText(pos);	break;
	case 6: /*EnableDocking*/
		{
			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
			_strupr(pos333);
			UINT Stl=0;
			int i;
			for(i=0;i<N_CTRLBAR_STYLES;i++)	
				if (strstr(pos333,aCtrlBarStyleName[i])!=NULL)
						Stl|=aCtrlBarStyleUINT[i];
			EnableDocking(Stl);
			delete[] pos333;
		}
		break;
	case 7: /*DockControlBar*/
		{
			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
			_strupr(pos333);
			UINT nUnit=atoi(pos333);
			UINT uArr[]={AFX_IDW_DOCKBAR_TOP,AFX_IDW_DOCKBAR_LEFT,AFX_IDW_DOCKBAR_RIGHT,AFX_IDW_DOCKBAR_BOTTOM,AFX_IDW_DOCKBAR_FLOAT,0,};
			char *cArr[]={"TOP","LEFT","RIGHT","BOTTOM","FLOAT",""};
			UINT stl=0;

			int i;
			for(i=0;i<5 && strstr(pos333,cArr[i])==NULL;i++);

			stl=uArr[i];	
			
			if (nUnit>0 && GPU && nUnit<(*GPU)->m_NGPUNIT && GPU[nUnit] && GPU[nUnit]->UnitPtr)
			switch(GPU[nUnit]->UnitType)
			{
			case GPUnit::UT_STATUSBAR: 
				DockControlBar((GPStatusBar *)GPU[nUnit]->UnitPtr,stl);break;
			case GPUnit::UT_TOOLBAR:
				DockControlBar((GPToolBar *)GPU[nUnit]->UnitPtr,stl);break;
			}// end TypeUnit Switch
			delete[] pos333;
		}
		break;
	case 8: /*FloatControlBar*/
		{
			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
			_strupr(pos333);
			UINT nUnit=0;
			UINT uArr[]={CBRS_ALIGN_TOP,CBRS_ALIGN_BOTTOM,CBRS_ALIGN_LEFT,CBRS_ALIGN_RIGHT,0,};
			char *cArr[]={"TOP","BOTTOM","LEFT","RIGHT",""};
			UINT stl=0;
			CPoint po(0,0);
			m_LastScanf=sscanf(pos333,"%d,%d,%d",&nUnit,&po.x,&po.y);

			int i;
			for(i=0;i<4 && strstr(pos333,cArr[i])==NULL;i++);

			stl=uArr[i];	
			
			if (nUnit>0 && GPU && nUnit<(*GPU)->m_NGPUNIT && GPU[nUnit] && GPU[nUnit]->UnitPtr)
			switch(GPU[nUnit]->UnitType)
			{
			case GPUnit::UT_STATUSBAR: 
				FloatControlBar((GPStatusBar *)GPU[nUnit]->UnitPtr,po,stl);break;
			case GPUnit::UT_TOOLBAR:
				FloatControlBar((GPToolBar *)GPU[nUnit]->UnitPtr,po,stl);break;
			}// end TypeUnit Switch
			delete[] pos333;
		}
		break;
	case 9: /*BeginModalState*/	BeginModalState();		break;
	case 10: /*EndModalState*/		EndModalState();		break;
	case 11: /*InModalState*/		retint=InModalState();	break;
	case 12: /*ShowOwnedWindows*/	ShowOwnedWindows(atoi(pos));	break;
	case 13: /*RecalcLayout*/ RecalcLayout();	break;
	case 14: /*AddScroller ScrName,ObjName,nX,nY,nXPage,nYPage[,Flags]*/
	case 19: /*EnsureVisibleScroller ScrName,ObjName*/
		{
			CString ScrName=ExtractField(pos,1,",");
			CString ObjName=ExtractField(pos,2,",");
			UINT i=-1;

			if (GPU && *GPU) 
			{
				for(i=1;i<(*GPU)->m_NGPUNIT;i++)
					if (GPU[i] && GPU[i]->m_ObjName==ObjName)	break;

				if (i<(*GPU)->m_NGPUNIT)
				{
					if (strcmp(cArrMethods[nfunc],"AddScroller")==0)
					{
						CGPScroller *tmp=GetScroller(ScrName,GPU[i]->UnitHWND);
						if (tmp)
						{
							int nX,nY,nXPage,nYPage;
							DWORD dwFlags;
							CString tmpCS;
							tmpCS=ExtractField(pos,3,",");
							if (tmpCS!="") nX=atoi(tmpCS);
							else nX=tmp->DeltaX;

							tmpCS=ExtractField(pos,4,",");
							if (tmpCS!="") nY=atoi(tmpCS);
							else nY=tmp->DeltaY;

							tmpCS=ExtractField(pos,5,",");
							if (tmpCS!="") nXPage=atoi(tmpCS);
							else nXPage=tmp->nPageX;

							tmpCS=ExtractField(pos,6,",");
							if (tmpCS!="") nYPage=atoi(tmpCS);
							else nYPage=tmp->nPageY;

							tmpCS=ExtractField(pos,7,",");
							if (tmpCS!="") dwFlags=atoi(tmpCS);
							else dwFlags=tmp->dwFlags;

							tmp->SetScroller(nX,nY,nXPage,nYPage,dwFlags);
						}
					}
					else
					{
						CGPScroller *tmp=GetScroller(ScrName,0);
						if (tmp) tmp->EnsureVisible(GPU[i]->UnitHWND);
					}
				}
			}
		}
		break;
	case  15: /*DelScroller ScrName*/
		DeleteScroller(pos);
		break;
	case  16: /*SetScroller ScrName,[nX],[nY],[nXPage],[nYPage][,Flags]*/
		{
			CGPScroller *tmp=GetScroller(pos,NULL);
			if (tmp)
			{
				int nX,nY,nXPage,nYPage;
				DWORD dwFlags;
				CString tmpCS;
				tmpCS=ExtractField(pos,3,",");
				if (tmpCS!="") nX=atoi(tmpCS);
				else nX=tmp->DeltaX;

				tmpCS=ExtractField(pos,4,",");
				if (tmpCS!="") nY=atoi(tmpCS);
				else nY=tmp->DeltaY;

				tmpCS=ExtractField(pos,5,",");
				if (tmpCS!="") nXPage=atoi(tmpCS);
				else nXPage=tmp->nPageX;

				tmpCS=ExtractField(pos,6,",");
				if (tmpCS!="") nYPage=atoi(tmpCS);
				else nYPage=tmp->nPageY;

				tmpCS=ExtractField(pos,7,",");
				if (tmpCS!="") dwFlags=atoi(tmpCS);
				else dwFlags=tmp->dwFlags;

				tmp->SetScroller(nX,nY,nXPage,nYPage,dwFlags);
			}
		}
		break;
	case  17: /*UpdateScloller ScrName*/
		{
			CGPScroller *tmp=GetScroller(pos,NULL);
			if (tmp)	tmp->UpdatePosition();
		}
		break;
	case  18: /*SetScrollerPos ScrName,X,Y*/
		{
			CGPScroller *tmp=GetScroller(pos,NULL);
			if (tmp)
			tmp->SetScrollerPos(
				atoi(ExtractField(pos,2,",")),
				atoi(ExtractField(pos,3,",")));
		}
		break;
	case  20: /*AutoSetAutoSizing*/
		GPU[0]->AutoSetAutoSizing(0);
		break;
	case  21: /*AutoSizingPause*/
		GPU[0]->AutoSizingPause();
		break;
	case  22: /*AutoSizingResume*/
		GPU[0]->AutoSizingResume();
		break;
	case  23: /*AutoSizingReset*/
		GPU[0]->AutoSizingReset();
		break;
	case  24: /*AutoSizingReinitSize*/
		GPU[0]->AutoSizingReinitSize();
		break;
	case  25: /*Reposition*/
		SendMessage(DM_REPOSITION,0,0);
		break;
	case  26: /*GetObjectByHWND*/
		if (oStr)
		{
			retint=GetObjIdByHWND((HWND)atoi(pos));
			sprintf(oStr,"%d\x7F%s",retint,retint<0?"":GPU[retint]->m_ObjName);
		}
		break;
	case  27: /*GetObjectsList*/
		if (oStr && GPU && *GPU)
		{
			char *posout=oStr;
			UINT i;
			for(i=1;i<(*GPU)->m_NGPUNIT;i++)
				if (GPU[i])
				{
					if (posout!=oStr) *(posout++)=0x7F;
					posout+=sprintf(posout,"%d\x7%s\x7%d",i,(LPCSTR)GPU[i]->m_ObjName,GetObjIdByHWND(::GetParent(GPU[i]->UnitHWND)));
				}
		}
		break;
	case  28: /*GetScrollerPos ScrollerName*/
		if (oStr)
		{
			*oStr=0;
			CGPScroller *tmp=GetScroller(pos,NULL);
			if (tmp)
				sprintf(oStr,"%d\x7F%d",tmp->CurPoint.x,tmp->CurPoint.y);
		}
		break;

	default: 
		GPU[0]->DoMethod(iStr, oStr);	break;
	}
	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
}


LRESULT GPFrameWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if (GPU && GPU[0])
	{
		switch(message)
		{
		case WM_DRAWITEM:
			if (lParam)
			{
				LPDRAWITEMSTRUCT lpds=(LPDRAWITEMSTRUCT) lParam;
				if (lpds->CtlType==ODT_MENU)
				{
					GPC.m_View->m_ODContextsArray->PaintByDRAWITEMSTRUCT(GPU[0], wParam, lpds, DlgGPMenu);
					return TRUE;
				}
				else
				{
					GPUnit *gpu=GetUnit(lpds->CtlID%50000);
					if (gpu && gpu->UnitType!=GPUnit::UT_CHECKLISTBOX)
					{
						GPC.m_View->m_ODContextsArray->PaintByDRAWITEMSTRUCT(gpu, wParam, lpds, DlgGPMenu);
						return TRUE;
					}
				}
			}
			break;

		case WM_MEASUREITEM:
			if (lParam)
			{
				LPMEASUREITEMSTRUCT lpds=(LPMEASUREITEMSTRUCT) lParam;
				if (lpds->CtlType==ODT_MENU)
				{
					return GPC.m_View->m_ODContextsArray->MeasureItem(GPU[0], wParam, lpds, DlgGPMenu);
				}
				else
				{
					HWND ctrlHWND=::GetDlgItem(m_hWnd,lpds->CtlID);
					if (ctrlHWND)
					{
						GPUnit *gpu=GetUnit(lpds->CtlID%50000);
						if (gpu && gpu->UnitType!=GPUnit::UT_CHECKLISTBOX)
						{
							return GPC.m_View->m_ODContextsArray->MeasureItem(gpu, wParam, lpds, DlgGPMenu);
						}
					}
				}
			}
			break;
		}

		GPU[0]->m_CurMessage.message=message;
		GPU[0]->m_CurMessage.wParam=wParam;
		GPU[0]->m_CurMessage.lParam=lParam;
		if (GPU[0]->DefWindowProc(message, wParam, lParam)) return 0;
	}

	if (message==WM_MENUCHAR && GPU && GPU[0] && GPU[0]->UnitHotkey)
	{
		BYTE kstate[260];
		if (GetKeyboardState(kstate))
		{
			UINT VKTMP=0;
			kstate[VK_SHIFT]=0;
			kstate[VK_CONTROL]=0;
			kstate[VK_MENU]=0;
			kstate[VK_RSHIFT]=0;
			kstate[VK_LSHIFT]=0;
			kstate[VK_RCONTROL]=0;
			kstate[VK_LCONTROL]=0;
			for(VKTMP=0;VKTMP<144;VKTMP++)
				if ((kstate[VKTMP]&0x80))
				{
					if (GPU[0]->UnitHotkey->SendHotkeyMessage(WM_KEYDOWN, VKTMP ,0)>0) 
						return MNC_CLOSE;
				}
		}
	}

	if (message==GPM_SETAUTOSIZE) 
	{
		DlgAutoSize->ReinitSize((HWND)wParam);
		DlgAutoSize->UpdateSize((HWND)wParam);
		GPC.m_UpdateSizeNow=0;
		return 0;
	}

	if (message==GPM_DODLGMETHOD) 
	{
		DoDlgMethod((char *)wParam,(char *)lParam);
		return 0;
	}

	if (message==GPN_UPDATESIZE) 
	{
		if ((GetWindowLong(m_hWnd,GWL_STYLE)&WS_POPUP)==WS_POPUP)
		{
			//LockWindowUpdate();
			DlgAutoSize->UpdateSize();
			//UnlockWindowUpdate();
		}
		else
			DlgAutoSize->UpdateSize();
		return 0;
	}

	if (message==GPN_SETENTIRE) 
	{
		nUnitENTIRE=wParam;
		return 0;
	}

	if (message==WM_APP+1)	RecalcLayout();

	if (GPU && GPU[0] && GPU[0]->GPMSG)
	{
		if (message==GPM_CLIENTKILLFOCUS || message==GPM_CLIENTSETFOCUS)
		{
			PGPUNITINFO ui=(PGPUNITINFO)lParam;
			if (ui)
				GPU[0]->GPMSG->GPSendObjEvent(m_hWnd, GPU[0]->UnitId,message==GPM_CLIENTSETFOCUS?"OnCSetFocus":"OnCKillFocus",GPUnit::UnitInfoToString2(ui,"\x7F"));
		}
		if (message==GPM_CLIENTKILLFOCUS || message==GPM_CLIENTSETFOCUS || message==GPM_UPDATESCROLLER)
		{
			UpdateScrollers();
		}
		if (GPU[0]->GPMSG->GPSendObjMessage(m_hWnd,GPU[0]->UnitId, message, wParam, lParam)>0) return 1;
	}
	if (message==WM_KEYDOWN)
		if (GPU && GPU[0] && GPU[0]->UnitHotkey && GPU[0]->UnitHotkey->SendHotkeyMessage(message, wParam,lParam)>0) return 1;

	if (message==GPM_PROCHOTKEY)
		if (GPU && GPU[0] && GPU[0]->UnitHotkey!=NULL && GPU[0]->UnitHotkey->SendHotkeyMessage(WM_KEYDOWN, wParam,lParam)>0) return 1;
	
	if (m_CDlgDialogEditor!=NULL) m_CDlgDialogEditor->EnableWindow();

	switch(message)
	{
	case GPM_DRAGMOUSELEAVE:
		if (GPU!=NULL)	GPU[0]->GPMSG->GPSendObjEvent(m_hWnd, GPU[0]->UnitId,"OnDragLeave","");
		break;
	case GPM_DRAGMOUSEMOVE:	
		OnMouseDragMove((PGPDRAGDROPSTRUCT)wParam,(LPPOINT)lParam);
		break;
	case GPM_DRAGMOUSEHOVER:
		OnDragMouseHover();
		break;
	case GPM_DROPITEMS:
		OnDragLButtonUp((PGPDRAGDROPSTRUCT)wParam,(LPPOINT)lParam);
		break;
	}

	LRESULT lpr;
	if (message==WM_SETCURSOR && GPC.m_bWaitCursor) lpr=FALSE;
	else 
	{
		if (message==WM_SETFOCUS) (GPUnit::m_IgnoreMessages)|=0x00000001;
		lpr=CFrameWnd::WindowProc(message, wParam, lParam);
		if (message==WM_SETFOCUS) (GPUnit::m_IgnoreMessages)&=(0xFFFFFFFF^0x00000001);
	}
	return lpr;
}

BOOL GPFrameWnd::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
//	if (pHandlerInfo==NULL)
	{
		if (nCode == CN_COMMAND) 
		{
/*
#define IDOK                1
#define IDCANCEL            2
#define IDABORT             3
#define IDRETRY             4
#define IDIGNORE            5
#define IDYES               6
#define IDNO                7
#if(WINVER >= 0x0400)
#define IDCLOSE         8
#define IDHELP          9
*/
			if (nID==IDOK || nID==IDCANCEL) 	return FALSE;

			if (nID>=MENU_ID_START && nID<=MENU_ID_END && DlgMenu!=NULL && DlgGPMenu!=NULL)
			{
				DlgGPMenu->OnCommandUserMenu(IdDlg,nID-MENU_ID_START);
				return TRUE;
			}
		}

		if (nCode == CN_UPDATE_COMMAND_UI && DlgMenu!=NULL && DlgGPMenu!=NULL) 
		{
			if (((CCmdUI*)pExtra)->m_pSubMenu==NULL)
			DlgGPMenu->DoUpdateUserMenu(nID-MENU_ID_START, (CCmdUI*)pExtra);
			else
			DlgGPMenu->DoUpdateUserMenu(nID-MENU_ID_START, (CCmdUI*)pExtra);
			return TRUE;
		}
	}
	
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BOOL GPFrameWnd::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	
	if ((wParam!=1 && wParam!=2) || lParam!=0) return CFrameWnd::OnCommand(wParam, lParam);

	if (GPU && GPU[0] && GPU[0]->GPMSG)
	{
		if (wParam==1 && GPU[0]->GPMSG->FindInActive("OnOk")!=NULL) GPU[0]->GPMSG->GPSendDlgEvent(m_hWnd, IdDlg,"OnOk","");
		else
		if (wParam==2 && GPU[0]->GPMSG->FindInActive("OnCancel")!=NULL) GPU[0]->GPMSG->GPSendDlgEvent(m_hWnd, IdDlg,"OnCancel","");
	}

	return TRUE;
}

void GPFrameWnd::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	if (((point.x>4 || point.y>4) && ((MK_CONTROL|MK_SHIFT)&nFlags)!=(MK_CONTROL|MK_SHIFT))  || !AskExit())
		CFrameWnd::OnLButtonDblClk(nFlags, point);
}

void GPFrameWnd::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	if ((point.x<4 && point.y<4) || ((MK_CONTROL|MK_SHIFT)&nFlags)==(MK_CONTROL|MK_SHIFT))
	{
		RunEditor();
	}
	else CFrameWnd::OnRButtonDblClk(nFlags, point);
}

void GPFrameWnd::RunEditor()
{
	if (m_CDlgDialogEditor==NULL)
	{
		m_CDlgDialogEditor =new CDlgDialogEditor(this,this);
		m_CDlgDialogEditor->Create(IDD_DIALOGOBJECTS);
	}

	try
	{
		m_CDlgDialogEditor->ShowWindow(SW_SHOW);
	}catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPFrameWnd", "RunEditor 865","");
		m_CDlgDialogEditor =new CDlgDialogEditor(this,this);
		m_CDlgDialogEditor->Create(IDD_DIALOGOBJECTS);
	}

	try
	{
		m_CDlgDialogEditor->ShowWindow(SW_SHOW);
	}catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPFrameWnd", "RunEditor 875","");
	}

	m_CDlgDialogEditor->SetWindowPos(&wndTop,0,0,0,0,SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOSIZE);

}

void GPFrameWnd::GPEndDlg()
{
	ClearDialog();
}

GPUnit * GPFrameWnd::GetUnitById(UINT Id)
{
	return Id<(*GPU)->m_NGPUNIT && Id>=0?GPU[Id]:NULL;
}

void GPFrameWnd::GPAddMessage(char *mes)
{
	if (GPU && GPU[0]) GPU[0]->GPAddMessage(mes);
}

void GPFrameWnd::GPDeleteMessage(char *mes)
{
	if (GPU && GPU[0]) GPU[0]->GPDeleteMessage(mes);
}

void GPFrameWnd::GPDeleteAllMessage()
{
	if (GPU && GPU[0]) GPU[0]->GPDeleteAllMessage();
}

void GPFrameWnd::OnClose() 
{
	if (GPU && GPU[0] && GPU[0]->GPMSG && GPU[0]->GPMSG->FindInActive("OnClose")!=NULL) GPU[0]->GPMSG->GPSendDlgEvent(m_hWnd, IdDlg,"OnClose","");
//	CFrameWnd::OnClose();
}

BOOL GPFrameWnd::PreTranslateMessage(MSG* pMsg) 
{
	if (m_ToolTip!=NULL) m_ToolTip->RelayEvent(	pMsg);

	if (GPU && GPU[0])
	{
		GPU[0]->m_CurPreMessage=pMsg;
		if (!GPU[0]->DefPreTranslateMessage(pMsg)) return 0;
		if (GPU[0]->GPMSG && GPU[0]->GPMSG->GPSendObjMessage(m_hWnd, GPU[0]->UnitId, pMsg->message, pMsg->wParam, pMsg->lParam)>0) return 1;

		if (pMsg->message==WM_KEYDOWN)
			if (GPU[0]->UnitHotkey && GPU[0]->UnitHotkey->SendHotkeyMessage(pMsg->message, pMsg->wParam,pMsg->lParam)>0) return 1;
	}
	
	switch(pMsg->message)
	{
	case WM_SYSKEYDOWN:
		break;
	case WM_SYSCHAR:
		return 0;
	}

	return CFrameWnd::PreTranslateMessage(pMsg);
}

#include <afxhtml.h>

int GPFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	EnableDocking(CBRS_ALIGN_ANY  );
	SetFont(GetParent()->GetFont());
	SetTimer(ID_DELAY_TIMER_ID,ID_DELAY_TIMER_DELAY,NULL);

//	OnRButtonDblClk(MK_CONTROL|MK_SHIFT, CPoint(2,2)); 

	return 0;
}

void GPFrameWnd::RecalcLayout(BOOL bNotify) 
{
	RepositionBars(0x0000,0xFFFF,nUnitENTIRE+50000);
//	CFrameWnd::RecalcLayout(bNotify);
}

BOOL GPFrameWnd::DestroyWindow() 
{
	ClearDialog();
	if (DlgGPMenu!=NULL) DlgGPMenu->ReleaseHBMP();
	return CFrameWnd::DestroyWindow();
}

void GPFrameWnd::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==ID_DELAY_TIMER_ID)
	{
		KillTimer(nIDEvent);
		if ((GetAsyncKeyState(VK_CONTROL)&0xFF00)!=0 && (GetAsyncKeyState(VK_MENU)&0xFF00)!=0)
		{
			if ((GetAsyncKeyState(VK_SHIFT)&0xFF00)!=0 && (GetAsyncKeyState(0x45)&0xFF00)!=0)
			{

				ModifyStyle(WS_DISABLED,0);
				::SetWindowLong(::GetParent(m_hWnd),GWL_STYLE,
					::GetWindowLong(::GetParent(m_hWnd),GWL_STYLE)&(0xFFFFFFFF^WS_DISABLED));
			}
			if ((GetAsyncKeyState(0x08)&0xFF00)!=0 && ::GetForegroundWindow()==m_hWnd)
			{
				AskExit();
			}
		}
		if (IsWindow(m_hWnd))
			SetTimer(nIDEvent,ID_DELAY_TIMER_DELAY,NULL);
	}
	else
	if (nIDEvent<20000 || nIDEvent>=20020)
	{
		char str[25]; sprintf(str,"%ld",nIDEvent);
		KillTimer(nIDEvent);
	}

	if (IsWindow(m_hWnd)) CFrameWnd::OnTimer(nIDEvent);
}

void GPFrameWnd::OnDragMouseHover() 
{
	while (GPU[0]->m_DropNamesArray && GPU[0]->m_DropNamesArray->GetIdByVal(GPC.m_DragDrop.DragName)<0xFFFFFFFFL)
	{
		// Reset the timer.
		::SetTimer (GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID, GPU[0]->m_nScrollInterval, NULL);

		// Get the current cursor position and window height.
		DWORD dwPos = ::GetMessagePos ();
		CPoint point (LOWORD (dwPos), HIWORD (dwPos));
		ScreenToClient (&point);

		CRect rect;
		GetClientRect (rect);
		int cy = rect.Height ();

		GPU[0]->SendDropHoverEvent("",&GPC.m_DragDrop,&point);

		// Scroll the window if the cursor is near the top or bottom.
		if (point.y >= 0 && point.y <= GPU[0]->m_nScrollMargin)
		{
			GPC.m_DragDrop.pImageList->DragShowNolock (FALSE);
			SendMessage (WM_VSCROLL, MAKEWPARAM (SB_LINEUP, 0), NULL);
			GPC.m_DragDrop.pImageList->DragShowNolock (TRUE);
			// Kill the timer if the window did not scroll, or redraw the drop target highlight if the window did scroll.
			if (GetScrollPos(SB_VERT))
				::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);
			else break;
		}
		else
			if (point.y >= cy - GPU[0]->m_nScrollMargin && point.y <= cy) 
			{
				GPC.m_DragDrop.pImageList->DragShowNolock (FALSE);
				SendMessage (WM_VSCROLL, MAKEWPARAM (SB_LINEDOWN, 0), NULL);
				GPC.m_DragDrop.pImageList->DragShowNolock (TRUE);
				// Kill the timer if the window did not scroll, or redraw the drop target highlight if the window did scroll.
				if (GetScrollPos(SB_HORZ)) ::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);
				else break;
			}
			else ::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);

		break;
	}
}

void GPFrameWnd::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point) 
{
	if (pDrDrStruct && pDrDrStruct->pImageList != NULL)
	{
		::ScreenToClient(m_hWnd,point);
		::KillTimer(pDrDrStruct->hWndDrag,DRAG_TIMER_ID);
		// Offset point
		if (GPU && GPU[0])	
			GPU[0]->OffsetWndPoint(point);

		// Erase the old drag image and draw a new one.
		if (pDrDrStruct->hWndLast!=m_hWnd)
		{
			pDrDrStruct->pImageList->DragLeave(CWnd::FromHandle(pDrDrStruct->hWndLast));
			pDrDrStruct->hWndLast=m_hWnd;
			pDrDrStruct->pImageList->DragEnter(this, CPoint(*point));
		}
		pDrDrStruct->pImageList->DragMove (CPoint(*point));

		DWORD bDropTarget=0xFFFFFFFF;
		BOOL mDrop=GPU[0]->m_DropNamesArray && GPU[0]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
		// Highlight the drop target if the cursor is over an item.
		if (mDrop)
			bDropTarget = HighlightDropTarget(pDrDrStruct, CPoint(*point));
		// Modify the cursor to provide visual feedback to the user. Note: It's important to do this AFTER the call to DragMove.
		::SetCursor (bDropTarget==0xFFFFFFFF ?
			AfxGetApp()->LoadStandardCursor (IDC_NO) 
			: (HCURSOR) ::GetClassLong (m_hWnd, GCL_HCURSOR));

		GPU[0]->SendDropMoveEvent("",pDrDrStruct,point);
		
		if (mDrop)
			::SetTimer (pDrDrStruct->hWndDrag,DRAG_TIMER_ID, GPU[0]->m_nDelayInterval, NULL);
	}
}

void GPFrameWnd::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point) 
{
	BOOL mDrop=GPU[0]->m_DropNamesArray && GPU[0]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && GPU)
	{
		UINT ret=SendMessage(WM_NCHITTEST,0,MAKELPARAM(point->x,point->y));
		const char *pos="ERROR";
		switch(ret)
		{
		case HTBORDER:		pos="BORDER";		break;
		case HTBOTTOM:		pos="BOTTOM";		break;
		case HTBOTTOMLEFT:	pos="BOTTOMLEFT";	break;
		case HTBOTTOMRIGHT:	pos="BOTTOMRIGHT";	break;
		case HTCAPTION:		pos="CAPTION";		break;
		case HTCLIENT:		pos="CLIENT";		break;
		case HTCLOSE:		pos="CLOSE";		break;
		case HTERROR:		pos="ERROR";		break;
		case HTGROWBOX:		pos="GROWBOX";		break;
		case HTHELP:		pos="HELP";			break;
		case HTHSCROLL:		pos="HSCROLL"; 		break;
		case HTLEFT:		pos="LEFT"; 		break;
		case HTMENU:		pos="MENU"; 		break;
		case HTMAXBUTTON:	pos="MAXBUTTON"; 	break;
		case HTMINBUTTON:	pos="MINBUTTON"; 	break;
		case HTNOWHERE:		pos="NOWHERE"; 		break;
		case HTRIGHT:		pos="RIGHT"; 		break;
		case HTSYSMENU:		pos="SYSMENU"; 		break;
		case HTTOP:			pos="TOP"; 			break;
		case HTTOPLEFT:		pos="TOPLEFT"; 		break;
		case HTTOPRIGHT:	pos="TOPRIGHT"; 	break;
		case HTTRANSPARENT:	pos="TRANSPARENT";	break;
		case HTVSCROLL:		pos="VSCROLL"; 		break;
		}
		::ScreenToClient(m_hWnd,point);
		GPU[0]->SendDropEvent(pos,pDrDrStruct,point);
	}
}

DWORD GPFrameWnd::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	return 0;
}

LRESULT GPFrameWnd::OnNcHitTest(CPoint point) 
{
	LRESULT ret=CFrameWnd::OnNcHitTest(point);
	if (GPU && GPU[0])
		ret=GPU[0]->GPNCHitTest(point,ret);
	return ret;
}

void GPFrameWnd::OnKillFocus(CWnd* pNewWnd) 
{
	CFrameWnd::OnKillFocus(pNewWnd);
	
	if (GPU && GPU[0] && GPU[0]->GPMSG) 
	{
		GPUNITINFO ui;
		GPUNITINFO uiold;
		if (GPU && GPU[0])
			GPU[0]->GetUnitInfo(ui);
		if (pNewWnd)
		{
			GPC.m_Document->FindObject(pNewWnd->m_hWnd,uiold);
			ui.hWnd2=uiold.hWnd;
			ui.IdDlg2=uiold.IdDlg;
			ui.IdObj2=uiold.IdObj;
		}
		GPU[0]->GPMSG->GPSendObjEvent(m_hWnd, IdDlg,"OnKillFocus",GPUnit::UnitInfoToString2(&ui,"\x7F"));
	}
	
}

void GPFrameWnd::OnSetFocus(CWnd* pOldWnd) 
{
	CFrameWnd::OnSetFocus(pOldWnd);
	
	if (GPU && GPU[0] && GPU[0]->GPMSG) 
	{
		GPUNITINFO ui;
		GPUNITINFO uiold;
		if (GPU && GPU[0])
			GPU[0]->GetUnitInfo(ui);
		if (pOldWnd)
		{
			GPC.m_Document->FindObject(pOldWnd->m_hWnd,uiold);
			ui.hWnd2=uiold.hWnd;
			ui.IdDlg2=uiold.IdDlg;
			ui.IdObj2=uiold.IdObj;
		}
		GPU[0]->GPMSG->GPSendObjEvent(m_hWnd, IdDlg,"OnSetFocus",GPUnit::UnitInfoToString2(&ui,"\x7F"));
	}
	
}

CGPScroller * GPFrameWnd::GetScroller(const char *iStr, HWND iScrHwnd)
{
	CGPScroller *ret=NULL;
	UINT i;

	if (!ScrollerArr)
	{
		ScrollerArr=new CGPScroller * [nMaxScroller];
		for(i=0;i<nMaxScroller;i++)
			ScrollerArr[i]=NULL;
	}

	if (ScrollerArr)
	{
		CString tmp=ExtractField(iStr,1,",");

		for(i=0;i<nScroller && !ret;i++)
			if (ScrollerArr[i] && ScrollerArr[i]->GetName()==tmp)
				ret=ScrollerArr[i];

		if (!ret && iScrHwnd)
		{
			while(nScroller>=nMaxScroller-1 || nMaxScroller==0)
			{
				CGPScroller **tmpArr=new CGPScroller * [nMaxScroller+8];
				for(i=0;i<nMaxScroller;i++)
					tmpArr[i]=ScrollerArr[i];

				nMaxScroller+=8;
				for(;i<nMaxScroller;i++)
					tmpArr[i]=NULL;
				
				delete[] ScrollerArr;
				ScrollerArr=tmpArr;
			}
			ret=ScrollerArr[nScroller++]=new CGPScroller(tmp,m_hWnd,iScrHwnd,1);
		}
	}
	return ret;
}

UINT GPFrameWnd::DeleteScroller(const char *iStr)
{
	if (ScrollerArr && nScroller)
	{
		CString sName=ExtractField(iStr,1,",");

		UINT i;
		for(i=0;i<nScroller;i++)
			if (ScrollerArr[i] && ScrollerArr[i]->GetName()==sName)
			{
				delete ScrollerArr[i];
				nScroller--;
				for(;i<nScroller;i++)
					ScrollerArr[i]=ScrollerArr[i+1];
				ScrollerArr[i]=NULL;
			}
	}

	return nScroller;
}

void GPFrameWnd::UpdateScrollers()
{
	if (ScrollerArr)
	{
		UINT i;
		for(i=0;i<nScroller;i++)
			if (ScrollerArr[i])
			{
				ScrollerArr[i]->UpdatePosition();
				if ((ScrollerArr[i]->dwFlags&0x0001)) 
					ScrollerArr[i]->EnsureVisible(::GetFocus());
			}
	}
}

void GPFrameWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (ScrollerArr)
	{
		UINT i;
		for(i=0;i<nScroller;i++)
			if (ScrollerArr[i])
				ScrollerArr[i]->OnHScroll(nSBCode, nPos, pScrollBar);
	}
	else	CFrameWnd::OnHScroll(nSBCode, nPos, pScrollBar);
	if (GPU && GPU[0]->m_SizerArray)	Invalidate();
}

void GPFrameWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (ScrollerArr)
	{
		UINT i;
		for(i=0;i<nScroller;i++)
			if (ScrollerArr[i])
				ScrollerArr[i]->OnVScroll(nSBCode, nPos, pScrollBar);
	}
	else	CFrameWnd::OnVScroll(nSBCode, nPos, pScrollBar);
	if (GPU && GPU[0]->m_SizerArray)	Invalidate();
}

void GPFrameWnd::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CFrameWnd::OnSizing(fwSide, pRect);
	UpdateScrollers();
}

DWORD GPFrameWnd::GetObjIdByHWND(HWND iHWND)
{
	DWORD ret=-1;
	if (iHWND)
	{
		UINT i;
		for(i=0;i<(*GPU)->m_NGPUNIT && ret==-1;i++)
			if (GPU[i] && GPU[i]->UnitHWND==iHWND) ret=i;
	}
	return ret;
}

void GPFrameWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CFrameWnd::OnShowWindow(bShow, nStatus);
	if ((m_LastSizeType&0x200)) ShowWindow(SW_MAXIMIZE);
}
