// GPObjDialog.cpp : implementation file
//

#include "stdafx.h"
#include "GP_term.h"
#include "GPObjDialog.h"
#include "GP_DlgSetting.h"
#include "GPStatusBarCtrl.h"
#include "GPToolBarCtrl.h"
#include "GPStatusBar.h"
#include "GPToolBar.h"
#include "GPReBar.h"
#include "GPFrameBar.h"
#include "GPReBarCtrl.h"
#include "GPToolTipCtrl.h"
#include "GP_TermView.h"

#ifdef W_95
#else
	#ifdef W_NT
	#else
		#ifdef W_98
		#else
			#ifdef W_2000
			#else
#include "uxtheme.h"
			#endif
		#endif
	#endif
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPObjDialog dialog
const UINT GPObjDialog::uNMethods=23;
const char *GPObjDialog::cArrMethods[]={
		"MapDialogRect","NextDlgCtrl","PrevDlgCtrl","GotoDlgCtrl","SetDefID",
		"GetDefID","SetHelpID","SetRepositionOrder","AddScroller","DelScroller",
		"SetScroller","UpdateScloller","SetScrollerPos","EnsureVisibleScroller","AutoSetAutoSizing",
		"AutoSizingPause","AutoSizingResume","AutoSizingReset","AutoSizingReinitSize","GetObjectByHWND",
		"GetObjectsList","EnableThemeDialogTexture","SetScrollerPos","","",
		"","","", "", "", 
	};
const char *GPObjDialog::cArrMethodsParams[]={
		"left,top,right,bottom","","","ObjId","ObjId",
		"","iHelpID","IdObj1,IdObj2,IdObj3,...","ScrName,ObjName,nX,nY,nXPage,nYPage[,Flags]","ScrName",
		"ScrName,[nX],[nY],[nXPage],[nYPage][,Flags]","ScrName","ScrName,X,Y","","",
		"","","","","hWnd",
		"","ETDT_ENABLETAB|ETDT_ENABLE|ETDT_DISABLE","ScrName", "", "", 
		"","","", "", "", 
		"","","", "", "", 
	};

GPObjDialog::GPObjDialog(UINT iId, const char *iiStr, CWnd* pParent /*=NULL*/)
{
	m_LastSizeType=0;
	m_NGPUNITmax=NINITIALUNITS;
	GPU= new GPUnit * [NINITIALUNITS];
	ZeroMemory(GPU,sizeof(GPUnit *)*NINITIALUNITS);

	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwCreateDlg++;
//mtb=NULL;
	iRepositionArray=NULL;
	nUnitENTIRE=0;
	m_CDlgDialogEditor=NULL;
	DlgAutoSize=NULL;
	DlgGPMenu=NULL;
	DlgMenu=NULL;
	IdDlg=iId;
	initialStr=new char [(int)strlen(iiStr)+256];
	strcpy(initialStr,iiStr);

	m_ToolTip=new CGPToolTipCtrl;

	//{{AFX_DATA_INIT(GPObjDialog)
	//}}AFX_DATA_INIT
	nScroller=0;
	nMaxScroller=9;
	ScrollerArr=new CGPScroller * [nMaxScroller];
	ZeroMemory(ScrollerArr,sizeof(CGPScroller *)*nMaxScroller);
}

GPObjDialog::~GPObjDialog()
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwDeleteDlg++;
	if (ScrollerArr)
	{
		UINT i;
		for(i=0;i<nScroller;i++)
			if (ScrollerArr[i]) delete ScrollerArr[i];
		delete[] ScrollerArr;
		ScrollerArr=NULL;
	}

	if (iRepositionArray!=NULL) delete[] iRepositionArray;
	iRepositionArray=NULL;

	try
	{
		if (m_CDlgDialogEditor!=NULL) delete m_CDlgDialogEditor;
	}catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPObjDialog", "~GPObjDialog","");
	}
	m_CDlgDialogEditor=NULL;
	ClearDialog();

	if (DlgAutoSize!=NULL) delete DlgAutoSize;
	DlgAutoSize=NULL;

}

void GPObjDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GPObjDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GPObjDialog, CDialog)
	//{{AFX_MSG_MAP(GPObjDialog)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_SETCURSOR()
	ON_WM_NCHITTEST()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// GPObjDialog message handlers
#include "GPDlgBar.h"

BOOL GPObjDialog::OnInitDialog() 
{

	CDialog::OnInitDialog();


	CRect MinimumRecr;
	GetWindowRect(&MinimumRecr);
	char *posRect=strstr(initialStr,"_ECT=");
	if (!posRect) posRect=strstr(initialStr,"RECT=");
	if (posRect)
	{
		CRect InitRect;
		m_LastScanf=sscanf(posRect+5,"%d,%d,%d,%d",&InitRect.left,&InitRect.top,&InitRect.right,&InitRect.bottom);
		MinimumRecr.bottom=MinimumRecr.top+InitRect.Height();
		MinimumRecr.right=MinimumRecr.left+InitRect.Width();
		if ((GetWindowLong(m_hWnd,GWL_STYLE)&WS_POPUP)!=WS_POPUP) 
			GetParent()->ScreenToClient(&MinimumRecr);

		MoveWindow(MinimumRecr);
	}

	DlgAutoSize=new GP_AutoSizing;
	DlgAutoSize->AddSetMain(this->m_hWnd);


	m_ToolTip->GPCreate(m_hWnd,IdDlg,initialStr,GPU);
	*GPU= new GPUnit(0+IS_DLG_UNIT+IdDlg*0x10000,0,initialStr,GPU,&m_ToolTip,this->m_hWnd,DlgAutoSize);
	DlgAutoSize->SetMinSize(this->m_hWnd,MinimumRecr.Width(),MinimumRecr.Height());

	if (GPU && GPU[0])	GPU[0]->UnitPtr=this;

	EnableToolTips(TRUE);
	EnableTrackingToolTips(TRUE);
	m_ToolTip->Activate(TRUE);

	SetForegroundWindow();
	SetTimer(ID_DELAY_TIMER_ID,ID_DELAY_TIMER_DELAY,NULL);

	return TRUE;
}


BOOL GPObjDialog::AttachHWND(HWND iHWND)
{
	BOOL ret=Attach(iHWND);
	if (ret && m_hWnd)
	{
		DlgAutoSize=new GP_AutoSizing;
		DlgAutoSize->AddSetMain(this->m_hWnd);

		CRect MinimumRecr(0,0,0,0);
		DlgAutoSize->SetMinSize(this->m_hWnd,MinimumRecr.Width(),MinimumRecr.Height());

		m_ToolTip->GPCreate(m_hWnd,IdDlg,initialStr,GPU);
		*GPU= new GPUnit(0+IS_DLG_UNIT+IdDlg*0x10000,0,initialStr,GPU,&m_ToolTip,this->m_hWnd,DlgAutoSize);
		if (*GPU) (*GPU)->UnitPtr=this;

		EnableToolTips(TRUE);
		EnableTrackingToolTips(TRUE);
		m_ToolTip->Activate(TRUE);

		SetTimer(ID_DELAY_TIMER_ID,ID_DELAY_TIMER_DELAY,NULL);
	}
	return ret;
}


UINT GPObjDialog::CreateUnit(UINT iType, UINT iId, const char *iInit, HWND pParentWnd)
{
	UINT ret=0;
	CString tpms;
	tpms.Format("object %d",iId);
	if (iId>=m_NGPUNITmax && iId<0x10000)
	{
		UINT newNMax=iId+2000;
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
						//	UnitHWND=((GPStatusBar*)UnitPtr)->m_hWnd;
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

void GPObjDialog::DeleteUnit(UINT iId, BOOL bReport)
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

void GPObjDialog::DoMethod(UINT iId, const char *iStr, char *oStr)
{
	if (iId!=0)
	{
		if (iId<(*GPU)->m_NGPUNIT && GPU[iId]) GPU[iId]->DoMethod(iStr, oStr);
	}
	else 
		DoDlgMethod(iStr, oStr);
}

void GPObjDialog::DoDlgMethod(const char *iStr, char *oStr)
{
	char met[150];
	strncpy(met,iStr,145);
	met[145]=0;
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc=0;

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
	case  0: /*MapDialogRect*/
		if (oStr!=NULL)
		{
			CRect re(0,0,0,0);
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&re.left,&re.top,&re.right,&re.bottom);
			MapDialogRect(&re);
			sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);	
		}
		break;
	case  1: /*NextDlgCtrl*/
		(GPUnit::m_IgnoreMessages)|=0x00000001;
		NextDlgCtrl();
		(GPUnit::m_IgnoreMessages)&=(0xFFFFFFFF^0x00000001);
		break;
	case  2: /*PrevDlgCtrl*/
		(GPUnit::m_IgnoreMessages)|=0x00000001;
		PrevDlgCtrl();
		(GPUnit::m_IgnoreMessages)&=(0xFFFFFFFF^0x00000001);
		break;
	case  3: /*GotoDlgCtrl*/
		{
			int nOdj=atoi(pos);
			if (nOdj>0 && GPU && (UINT)nOdj<(*GPU)->m_NGPUNIT && GPU[nOdj] && GPU[nOdj]->UnitHWND) 
			{
				HWND tmpH=::GetParent(GPU[nOdj]->UnitHWND);
				while(tmpH && tmpH!=m_hWnd && (GetWindowLong(tmpH,GWL_STYLE)&WS_POPUP)!=WS_POPUP)
					tmpH=::GetParent(tmpH);
				if (tmpH==m_hWnd)
				{
					(GPUnit::m_IgnoreMessages)|=0x00000001;
					GotoDlgCtrl(CWnd::FromHandle(GPU[nOdj]->UnitHWND));
					(GPUnit::m_IgnoreMessages)&=(0xFFFFFFFF^0x00000001);
				}
				else
				{
					UINT i;
					for(i=1;i<GPU[0]->m_NGPUNIT && (!GPU[i] || GPU[i]->UnitHWND!=tmpH);i++);
				
					if (i<GPU[0]->m_NGPUNIT &&  GPU[i]->UnitHWND==tmpH && tmpH!=m_hWnd)
						GPU[i]->DoMethod(iStr,oStr);
				}
			}
		}
		break;
	case  4: /*SetDefID*/	
		{
			int nOdj=atoi(pos);
			if (GPU && (UINT)nOdj<(*GPU)->m_NGPUNIT && GPU[nOdj] && GPU[nOdj]->UnitHWND) 
				SetDefID(GPU[nOdj]->UnitId&0xFFFF);
		}
		break;
	case  5: /*GetDefID*/
		if (oStr!=NULL && GPU!=NULL)
		{
			DWORD Id=GetDefID();
			UINT nObj;
			for(nObj=0;nObj<(*GPU)->m_NGPUNIT;nObj++)
				if (GPU[nObj] && GPU[nObj]->UnitHWND &&(GPU[nObj]->UnitId&0xFFFF)==(Id&0xFFFF)) break; 
			
			if (nObj==(*GPU)->m_NGPUNIT) nObj=0;
			sprintf(oStr,"%d",nObj);
		}
		break;
	case  6: /*SetHelpID*/	SetHelpID(atoi(pos));	break;
	case  7: /*SetRepositionOrder*/
		{
			if (iRepositionArray!=NULL) delete[] iRepositionArray;
			iRepositionArray=NULL;
			const char *pos2=pos;
			int nPos=0;
			while(*pos2!=0)
			{
				if (*pos2==',' || *pos2==GPC.DelimiterIn1) nPos++;
				pos2++;
			}
			pos2=pos;
			if (nPos>0)
			{
				iRepositionArray=new int [nPos+2];
				nPos=0;
				while(*pos2!=0)
				{
					if (*pos2==',' || *pos2==GPC.DelimiterIn1)
					{
						pos2++;
						iRepositionArray[nPos++]=atoi(pos2);
					}
					pos2++;
				}
				iRepositionArray[nPos++]=0;
			}
			break;
		}
	case  8: /*AddScroller ScrName,ObjName,nX,nY,nXPage,nYPage[,Flags]*/
	case  13: /*EnsureVisibleScroller ScrName,ObjName*/
		{
			CString ScrName=ExtractField(pos,1,",");
			CString ObjName=ExtractField(pos,2,",");
			UINT i=(UINT)-1;

			if (GPU!=NULL && GPU[0]) 
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
	case   9: /*DelScroller ScrName*/
		DeleteScroller(pos);
		break;
	case  10: /*SetScroller ScrName,[nX],[nY],[nXPage],[nYPage][,Flags]*/
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
	case  11: /*UpdateScloller ScrName*/
		{
			CGPScroller *tmp=GetScroller(pos,NULL);
			if (tmp)	tmp->UpdatePosition();
		}
		break;
	case  12: /*SetScrollerPos ScrName,X,Y*/
		{
			CGPScroller *tmp=GetScroller(pos,NULL);
			if (tmp)
			tmp->SetScrollerPos(
				atoi(ExtractField(pos,2,",")),
				atoi(ExtractField(pos,3,",")));
		}
		break;
	case  14: /*AutoSetAutoSizing*/
		GPU[0]->AutoSetAutoSizing(0);
		break;
	case  15: /*AutoSizingPause*/
		GPU[0]->AutoSizingPause();
		break;
	case  16: /*AutoSizingResume*/
		GPU[0]->AutoSizingResume();
		break;
	case  17: /*AutoSizingReset*/
		GPU[0]->AutoSizingReset();
		break;
	case  18: /*AutoSizingReinitSize*/
		GPU[0]->AutoSizingReinitSize();
		break;
	case  19: /*GetObjectByHWND*/
		if (oStr)
		{
			int retint=GetObjIdByHWND((HWND)atoi(pos));
			sprintf(oStr,"%d\x7F%s",retint,retint<0?"":GPU[retint]->m_ObjName);
		}
		break;
	case  20: /*GetObjectsList*/
		if (oStr && GPU)
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
	case  21: /*EnableThemeDialogTexture*/
		#ifdef W_95
		#else
			#ifdef W_NT
			#else
				#ifdef W_98
				#else
					#ifdef W_2000
					#else
					{
						int atoipos=atoi(pos);
						if (strstr(pos,"ETDT_ENABLETAB")) atoipos|=ETDT_ENABLETAB;
						if (strstr(pos,"ETDT_ENABLE")) atoipos|=ETDT_ENABLE;
						if (strstr(pos,"ETDT_DISABLE")) atoipos|=ETDT_DISABLE;
						if (strstr(pos,"ETDT_USETABTEXTURE")) atoipos|=ETDT_USETABTEXTURE;
						atoipos=EnableThemeDialogTexture(m_hWnd,atoipos);
						if (oStr) sprintf(oStr,"%d",atoipos);
						Invalidate();
					}
					#endif
				#endif
			#endif
		#endif
		break;
	case  22: /*GetScrollerPos ScrollerName*/
		if (oStr)
		{
			*oStr=0;
			CGPScroller *tmp=GetScroller(pos,NULL);
			if (tmp)
				sprintf(oStr,"%d\x7F%d",tmp->CurPoint.x,tmp->CurPoint.y);
		}
		break;

	default:
		GPU[0]->DoMethod(iStr, oStr);
		break;
	}

}

void GPObjDialog::GPEndDlg()
{
	ClearDialog();
//	EndDialog(1);
}

void GPObjDialog::OnClose() 
{
	if (GPU && GPU[0] && GPU[0]->GPMSG && GPU[0]->GPMSG->FindInActive("OnClose")) GPU[0]->GPMSG->GPSendDlgEvent(m_hWnd, IdDlg,"OnClose","");
}

void GPObjDialog::OnTimer(UINT nIDEvent) 
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
		if (nIDEvent!=DLGEDITOR_TIMER_ID) KillTimer(nIDEvent);
	}

	if (IsWindow(m_hWnd)) CDialog::OnTimer(nIDEvent);
}

GPUnit * GPObjDialog::GetUnitById(UINT Id)
{
	return Id<(*GPU)->m_NGPUNIT && Id>=0?GPU[Id]:NULL;
}


void GPObjDialog::GPAddMessage(char *mes)
{
	if (GPU && GPU[0]) GPU[0]->GPAddMessage(mes);
}

void GPObjDialog::GPDeleteMessage(char *mes)
{
	if (GPU && GPU[0]) GPU[0]->GPDeleteMessage(mes);
}

void GPObjDialog::GPDeleteAllMessage()
{
	if (GPU && GPU[0]) GPU[0]->GPDeleteAllMessage();
}

BOOL GPObjDialog::PreTranslateMessage(MSG* pMsg) 
{
	if (GPU && GPU[0]) GPU[0]->m_CurPreMessage=pMsg;

	if (m_ToolTip) m_ToolTip->RelayEvent(pMsg);

	if (GPU && GPU[0] && GPU[0]->GPMSG)
	{
		if (!GPU[0]->DefPreTranslateMessage(pMsg)) return 0;
		if (GPU[0]->GPMSG->GPSendObjMessage(m_hWnd, GPU[0]->UnitId, pMsg->message, pMsg->wParam, pMsg->lParam)>0) return 1;
	}

	if (pMsg->message==WM_KEYDOWN)
		if (GPU && GPU[0] && GPU[0]->UnitHotkey && GPU[0]->UnitHotkey->SendHotkeyMessage(pMsg->message, pMsg->wParam,pMsg->lParam)>0) return 1;

	switch(pMsg->message)
	{
	case WM_SYSKEYDOWN:
		break;
	case WM_SYSCHAR:
		return 0;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void GPObjDialog::OnSize(UINT nType, int cx, int cy) 
{
	if (iRepositionArray==NULL)	RepositionBars(0x0000,0xFFFF,nUnitENTIRE+50000);
	else
		if (GPU!=NULL)
		{
			CRect ClRect;
			GetClientRect(&ClRect);
			int *pos=iRepositionArray;
			while(*pos!=0)
			{
				if (GPU[*pos])
					RepositionBars(GPU[*pos]->UnitId&0xFFFF,GPU[*pos]->UnitId&0xFFFF,50000,NULL,&ClRect);
			}
			RepositionBars(nUnitENTIRE+50000,nUnitENTIRE+50000,nUnitENTIRE+50000);
		}

	BOOL DOIT=TRUE;
	if (DlgAutoSize)
		DOIT=DlgAutoSize->CheckMainSize(m_hWnd,nType,&cx, &cy);
	if (DOIT)
		CDialog::OnSize(nType, cx, cy);
	else 
		if (cx>0 && cy>0) Invalidate();

	if (m_hWnd && GPU && GPU[0])	GPU[0]->UpdateSizerSize();

	if (DlgAutoSize!=NULL && nType!=SIZE_MINIMIZED) DlgAutoSize->UpdateSize();

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
				case GPUnit::UT_FRAMEBAR:
					{
						CWnd *tmp=CWnd::FromHandle(GPU[i]->UnitHWND);
						if (tmp->IsZoomed() &&(tmp->GetStyle()&WS_CHILD)==WS_CHILD) 
						{
							CRect re;
							GetClientRect(&re);
							tmp->MoveWindow(re);
						}
					//	if (GPU[i]->UnitType==GPUnit::UT_DLGBAR)
					//		((GPDlgBar *)(GPU[i]->UnitPtr))->DlgAutoSize->UpdateSize();
					//	else
					//		((GPFrameBar *)(GPU[i]->UnitPtr))->DlgAutoSize->UpdateSize();

					}
					break;
				case GPUnit::UT_TOOLBARCTRL:
					((GPToolBarCtrl*)GPU[i]->UnitPtr)->AutoSize();	
					break;
				case GPUnit::UT_REBAR:
				case GPUnit::UT_REBARCTRL:
				case GPUnit::UT_TOOLBAR:
				case GPUnit::UT_STATUSBAR:
				case GPUnit::UT_STATUSBARCTRL:
					::SendMessage(GPU[i]->UnitHWND,WM_SIZE,nType,cx+cy*0x10000);
					break;
				}
			}
	}
	UpdateScrollers();
	Invalidate();
	m_LastSizeType=m_LastSizeType*0x100+nType;
}

void GPObjDialog::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	if (((point.x>4 || point.y>4) &&((MK_CONTROL|MK_SHIFT)&nFlags)!=(MK_CONTROL|MK_SHIFT))  || !AskExit())
		CDialog::OnLButtonDblClk(nFlags, point);
}

void GPObjDialog::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	if ((point.x<4 && point.y<4) ||((MK_CONTROL|MK_SHIFT)&nFlags)==(MK_CONTROL|MK_SHIFT))
	{
		RunEditor();
	}
	else CDialog::OnRButtonDblClk(nFlags, point);
}



BOOL GPObjDialog::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
//		if (nCode==CN_EVENT)
//	TRACE("OnCmdMsg %X %d %X %d\n",nID,nID,nCode,nCode);
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
#if (WINVER >= 0x0400)
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
			DlgGPMenu->DoUpdateUserMenu(nID-MENU_ID_START,(CCmdUI*)pExtra);
			else
			DlgGPMenu->DoUpdateUserMenu(nID-MENU_ID_START,(CCmdUI*)pExtra);
			return TRUE;
		}
	}
	return CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



GPMenu *GPObjDialog::CreateDlgMenu()
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

BOOL GPObjDialog::DeleteDlgMenu()
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

void GPObjDialog::ClearDialog()
{
	if (GPU && *GPU)
	{
		int i;
		for(i=1;(UINT)i<(*GPU)->m_NGPUNIT;i++) 
			if (GPU[i]) DeleteUnit(i, FALSE);
		delete *GPU;
		*GPU=NULL;
	}

	if (GPU) delete[] GPU;
	GPU=NULL;

	if (DlgGPMenu!=NULL)
		delete DlgGPMenu;
	DlgGPMenu=NULL;

	if (DlgMenu!=NULL)
		delete DlgMenu;
	DlgMenu=NULL;

	if (initialStr!=NULL) delete[] initialStr;
	initialStr=NULL;

	if (m_ToolTip!=NULL) delete m_ToolTip;
	m_ToolTip=NULL;
}

BOOL GPObjDialog::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if ((wParam!=1 && wParam!=2) || lParam!=0)
		if (lParam==NULL || ::IsWindow((HWND)lParam))	return CDialog::OnCommand(wParam, lParam);
		else return TRUE;

	if (GPU && GPU[0] && GPU[0]->GPMSG)
	{
		if (wParam==1 && GPU[0]->GPMSG->FindInActive("OnOk")) GPU[0]->GPMSG->GPSendDlgEvent(m_hWnd, IdDlg,"OnOk","");
		else
		if (wParam==2 && GPU[0]->GPMSG->FindInActive("OnCancel")) GPU[0]->GPMSG->GPSendDlgEvent(m_hWnd, IdDlg,"OnCancel","");
	}

	return TRUE;
}

LRESULT GPObjDialog::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
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

		if (message==WM_MENUCHAR && GPU[0]->UnitHotkey)
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
	}


	if (message==GPM_DODLGMETHOD) 
	{
		DoDlgMethod((char *)wParam,(char *)lParam);
		return 0;
	}

	if (message==GPM_SETAUTOSIZE) 
	{
		DlgAutoSize->ReinitSize((HWND)wParam);
		DlgAutoSize->UpdateSize((HWND)wParam);
		GPC.m_UpdateSizeNow=0;
		return 0;
	}

	if (message==GPN_UPDATESIZE) 
	{
		DlgAutoSize->UpdateSize();
		return 0;
	}

	if (message==GPN_SETENTIRE) 
	{
		nUnitENTIRE=wParam;
		return 0;
	}

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

		if (GPU[0]->GPMSG->GPSendObjMessage(m_hWnd, GPU[0]->UnitId, message, wParam, lParam)>0) return 1;
	}
	if (message==WM_KEYDOWN)
		if (GPU && GPU[0] && GPU[0]->UnitHotkey!=NULL && GPU[0]->UnitHotkey->SendHotkeyMessage(message, wParam,lParam)>0) return 1;

	if (message==GPM_PROCHOTKEY)
		if (GPU && GPU[0] && GPU[0]->UnitHotkey!=NULL && GPU[0]->UnitHotkey->SendHotkeyMessage(WM_KEYDOWN, wParam,lParam)>0) return 1;

	switch(message)
	{
	case GPM_DRAGMOUSELEAVE:
		if (GPU && GPU[0] && GPU[0]->GPMSG)	GPU[0]->GPMSG->GPSendObjEvent(m_hWnd, GPU[0]->UnitId,"OnDragLeave","");
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

	LRESULT lpr=0;
	if (message==WM_SETCURSOR && GPC.m_bWaitCursor) lpr=FALSE;
	else 
	{
		if (message==WM_SETFOCUS) (GPUnit::m_IgnoreMessages)|=0x00000001;
		lpr=CDialog::WindowProc(message, wParam, lParam);
		if (message==WM_SETFOCUS) (GPUnit::m_IgnoreMessages)&=(0xFFFFFFFF^0x00000001);
	}

	return lpr;
}

void GPObjDialog::DelAllHotkey()
{
	if (GPU && GPU[0]) GPU[0]->DelAllHotkey();
}

BOOL GPObjDialog::DelHotkey(UINT iId, const char *iHotkeyName)
{
	BOOL ret = FALSE;
	if (GPU && GPU[0]) ret=GPU[0]->DelHotkey(iId,iHotkeyName);
	return ret;
}

BOOL GPObjDialog::AddHotkey(char *nm_VK, UINT iId, const char *seq)
{
	BOOL ret = FALSE;
	if (GPU && GPU[0]) ret=GPU[0]->AddHotkey(nm_VK,iId,seq);
	return ret;
}

GPUnit * GPObjDialog::GetUnit(UINT iUnitId)
{
	GPUnit *tmp=NULL;
	if (GPU && iUnitId<(*GPU)->m_NGPUNIT) tmp=GPU[iUnitId];

	return tmp;
}

BOOL GPObjDialog::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	 return CDialog::OnSetCursor(pWnd, nHitTest, message);
}


#include "GP_TermDoc.h"

BOOL GPObjDialog::AskExit()
{
	BOOL ret=FALSE;

#ifdef RUS
	if (MessageBox("«акрыть диалог без сохранени€ данных?",GPC.MsgBoxCaption,MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2)==IDYES)
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


BOOL GPObjDialog::DestroyWindow() 
{
	ClearDialog();
	if (DlgGPMenu!=NULL) DlgGPMenu->ReleaseHBMP();
	return CDialog::DestroyWindow();
}

void GPObjDialog::OnDragMouseHover() 
{
	if (GPU[0]->m_DropNamesArray && GPU[0]->m_DropNamesArray->GetIdByVal(GPC.m_DragDrop.DragName)<0xFFFFFFFFL)
	{
		// Reset the timer.
		::SetTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID, GPU[0]->m_nScrollInterval, NULL);

		// Get the current cursor position and window height.
		DWORD dwPos = ::GetMessagePos();
		CPoint point(LOWORD(dwPos), HIWORD(dwPos));
		ScreenToClient(&point);

		CRect rect;
		GetClientRect(rect);
		int cy = rect.Height();

		GPU[0]->SendDropHoverEvent("",&GPC.m_DragDrop,&point);

		// Scroll the window if the cursor is near the top or bottom.
		if (point.y >= 0 && point.y <= GPU[0]->m_nScrollMargin)
		{
			GPC.m_DragDrop.pImageList->DragShowNolock(FALSE);
			SendMessage(WM_VSCROLL, MAKEWPARAM(SB_LINEUP, 0), NULL);
			GPC.m_DragDrop.pImageList->DragShowNolock(TRUE);
			// Kill the timer if the window did not scroll, or redraw the drop target highlight if the window did scroll.
			if (GetScrollPos(SB_VERT))
				::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);
		}
		else
			if (point.y >= cy - GPU[0]->m_nScrollMargin && point.y <= cy) 
			{
				GPC.m_DragDrop.pImageList->DragShowNolock(FALSE);
				SendMessage(WM_VSCROLL, MAKEWPARAM(SB_LINEDOWN, 0), NULL);
				GPC.m_DragDrop.pImageList->DragShowNolock(TRUE);
				// Kill the timer if the window did not scroll, or redraw the drop target highlight if the window did scroll.
				if (GetScrollPos(SB_HORZ)) ::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);
			}
			else ::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);
	}
}

void GPObjDialog::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point) 
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
		pDrDrStruct->pImageList->DragMove(CPoint(*point));

		DWORD bDropTarget=0xFFFFFFFF;
		BOOL mDrop=GPU[0]->m_DropNamesArray && GPU[0]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
		// Highlight the drop target if the cursor is over an item.
		if (mDrop)
			bDropTarget = HighlightDropTarget(pDrDrStruct, CPoint(*point));
		// Modify the cursor to provide visual feedback to the user. Note: It's important to do this AFTER the call to DragMove.
		::SetCursor(bDropTarget==0xFFFFFFFF ?
			AfxGetApp()->LoadStandardCursor(IDC_NO) 
			:(HCURSOR) ::GetClassLong(m_hWnd, GCL_HCURSOR));

		GPU[0]->SendDropMoveEvent("",pDrDrStruct,point);
		
		if (mDrop)
			::SetTimer(pDrDrStruct->hWndDrag,DRAG_TIMER_ID, GPU[0]->m_nDelayInterval, NULL);
	}
}

void GPObjDialog::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point) 
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
		GPU[0]->SendDropEvent("",pDrDrStruct,point);
	}
}

DWORD GPObjDialog::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{

	return 0;
}

LRESULT GPObjDialog::OnNcHitTest(CPoint point) 
{
	LRESULT ret=CDialog::OnNcHitTest(point);
	if (GPU && GPU[0])
		ret=GPU[0]->GPNCHitTest(point,ret);
	return ret;
}

void GPObjDialog::OnKillFocus(CWnd* pNewWnd) 
{
	CDialog::OnKillFocus(pNewWnd);
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

void GPObjDialog::OnSetFocus(CWnd* pNewWnd) 
{
	CDialog::OnSetFocus(pNewWnd);
	if (GPU && GPU[0] && GPU[0]->GPMSG && GPU[0]->GPMSG) 
	{
		GPUNITINFO ui;
		GPUNITINFO uiold;
		if (GPU && GPU[0])GPU[0]->GetUnitInfo(ui);
		if (pNewWnd)
		{
			GPC.m_Document->FindObject(pNewWnd->m_hWnd,uiold);
			ui.hWnd2=uiold.hWnd;
			ui.IdDlg2=uiold.IdDlg;
			ui.IdObj2=uiold.IdObj;
		}
		GPU[0]->GPMSG->GPSendObjEvent(m_hWnd, IdDlg,"OnSetFocus",GPUnit::UnitInfoToString2(&ui,"\x7F"));
	}
}

CGPScroller * GPObjDialog::GetScroller(const char *iStr, HWND iScrHwnd)
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

UINT GPObjDialog::DeleteScroller(const char *iStr)
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


void GPObjDialog::UpdateScrollers()
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

void GPObjDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (ScrollerArr)
	{
		UINT i;
		for(i=0;i<nScroller;i++)
			if (ScrollerArr[i])
				ScrollerArr[i]->OnHScroll(nSBCode, nPos, pScrollBar);
	}
	else	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	if (GPU && GPU[0]->m_SizerArray)	Invalidate();
}

void GPObjDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (ScrollerArr)
	{
		UINT i;
		for(i=0;i<nScroller;i++)
			if (ScrollerArr[i])
				ScrollerArr[i]->OnVScroll(nSBCode, nPos, pScrollBar);
	}
	else	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
	if (GPU && GPU[0]->m_SizerArray)	Invalidate();
}

void GPObjDialog::RunEditor()
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
		GPC.m_ErrReport.GPWriteErrorLog("GPObjDialog", "RunEditor 1233","");
		m_CDlgDialogEditor =new CDlgDialogEditor(this,this);
		m_CDlgDialogEditor->Create(IDD_DIALOGOBJECTS);
	}

	try
	{
		m_CDlgDialogEditor->ShowWindow(SW_SHOW);
	}catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPObjDialog", "RunEditor 1243","");
	}

	m_CDlgDialogEditor->SetWindowPos(&wndTop,0,0,0,0,SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOSIZE);
}

BOOL GPObjDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	return CDialog::OnNotify(wParam, lParam, pResult);
}

HBRUSH GPObjDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = NULL;
	
	if (GPU && GPU[0] && GPU[0]->m_brBkgnd) 
	{
		hbr = (HBRUSH) *(GPU[0]->m_brBkgnd);
		if (pWnd->m_hWnd!=m_hWnd)
		{
	        RECT rc;
			::GetWindowRect(pWnd->m_hWnd, &rc);
			::MapWindowPoints(NULL, m_hWnd, (POINT *)&rc, 2);
			::SetBrushOrgEx(pDC->m_hDC, -rc.left, -rc.top, NULL);
		}
	}

	if (pWnd && pDC && pWnd->m_hWnd && pDC->m_hDC)
		GPUnit::ChildCtlColor(GPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CDialog::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);
	return hbr;
}


DWORD GPObjDialog::GetObjIdByHWND(HWND iHWND)
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

void GPObjDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	if ((m_LastSizeType&0x200)) ShowWindow(SW_MAXIMIZE);
}
