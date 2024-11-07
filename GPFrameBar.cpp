// GPFrameBar.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPFrameBar.h"
#include "GPToolTipCtrl.h"

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
// GPFrameBar
const UINT GPFrameBar::uNMethods=33;
const char *GPFrameBar::cArrMethods[]={
		"LoadBarState","SaveBarState","ShowControlBar","ActivateFrame","GetControlBar",
		"GetMessageString","IsTracking","SetMessageText","EnableDocking","DockControlBar",
		"FloatControlBar","BeginModalState","EndModalState","InModalState","ShowOwnedWindows",
		"RecalcLayout",	"UpdateGroup","AddScroller","DelScroller","SetScroller",
		"UpdateScloller","SetScrollerPos","EnsureVisibleScroller","barAutoSizingPause","barAutoSizingResume",
		"barAutoSizingReset","barAutoSizingReinitSize","Reposition","barAutoSetAutoSizing","FlashOnChildFocus",
		"EnableThemeDialogTexture","SetAutoFocus","GetScrollerPos","","",
		"","","","","",
	};
const char *GPFrameBar::cArrMethodsParams[]={
		"","","bShow","ShowWindowFlags","",
		"","","Text","bEnable","",
		"","","","","",
		"",	"","ScrName,ObjName,nX,nY,nXPage,nYPage[,Flags]","ScrName","ScrName,[nX],[nY],[nXPage],[nYPage][,Flags]",
		"ScrName","ScrName,X,Y","","","",
		"","","","bOnOff","bFlash",
		"ETDT_ENABLETAB|ETDT_ENABLE|ETDT_DISABLE","bAutoFocus","Name","","",
		"","","","","",
	};


IMPLEMENT_DYNCREATE(GPFrameBar, CFrameWnd)

GPFrameBar::GPFrameBar()
{
	m_LastSizeType=0;
	m_bAutoFocus=0;
	nUnitENTIRE=0;
	m_dwFlashFlag=0xFFFF;
	DlgAutoSize=NULL;
	CharSpec=NULL;
	FloatPoint=-1;
	referGPU=NULL;
	UnitId=0;
	nScroller=0;
	nMaxScroller=9;
	ScrollerArr=new CGPScroller * [nMaxScroller];

	UINT i;
	for(i=0;i<nMaxScroller;i++)
		ScrollerArr[i]=NULL;
}

GPFrameBar::~GPFrameBar()
{
	if (ScrollerArr)
	{
		UINT i;
		for(i=0;i<nScroller;i++)
			if (ScrollerArr[i]) delete ScrollerArr[i];
		delete[] ScrollerArr;
		ScrollerArr=NULL;
	}

	if (DlgAutoSize!=NULL) delete DlgAutoSize;
	DlgAutoSize=NULL;
}


BEGIN_MESSAGE_MAP(GPFrameBar, CFrameWnd)
	//{{AFX_MSG_MAP(GPFrameBar)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_CREATE()
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
// GPFrameBar message handlers

BOOL GPFrameBar::CreateFrameBar(UINT iStyleEx, const char *Capt,UINT iStyle,CRect ir,CWnd *ParentCWnd,UINT iUnitId)
{
	BOOL ret=Create(AfxRegisterWndClass(CS_VREDRAW|CS_HREDRAW|CS_DBLCLKS),
				Capt,		iStyle,		ir,
				ParentCWnd,	NULL, 		iStyleEx,	NULL 	);

	ShowWindow((iStyle&WS_VISIBLE)==WS_VISIBLE?SW_SHOW:SW_HIDE);
	DlgAutoSize=new GP_AutoSizing;
	DlgAutoSize->AddSetMain(this->m_hWnd);
	SetForegroundWindow();
	return ret;
}

BOOL GPFrameBar::PreTranslateMessage(MSG* pMsg)
{
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		referGPU[UnitId&0xFFFF]->m_CurPreMessage=pMsg;
		if (!referGPU[UnitId&0xFFFF]->DefPreTranslateMessage(pMsg)) return 0;
		if (referGPU[UnitId&0xFFFF]->m_ToolTip && *(referGPU[UnitId&0xFFFF]->m_ToolTip))
			(*(referGPU[UnitId&0xFFFF]->m_ToolTip))->RelayEvent(pMsg);

		if (referGPU[UnitId&0xFFFF]->GPMSG)
		{
			UINT ret;
			if (pMsg->message!=WM_KEYDOWN || pMsg->wParam==VK_RETURN || pMsg->wParam==VK_TAB || pMsg->wParam==VK_CANCEL || pMsg->wParam==VK_ESCAPE || pMsg->wParam==VK_HELP)
			{
				if((ret=referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjMessage(m_hWnd, UnitId, pMsg->message, pMsg->wParam, pMsg->lParam))>0) return ret;
				if (pMsg->message==WM_KEYDOWN && referGPU!=NULL && referGPU[UnitId&0xFFFF]->UnitHotkey && this->m_hWnd!=NULL && IsWindowEnabled()==TRUE && IsWindowVisible()==TRUE)
						if((ret=referGPU[UnitId&0xFFFF]->UnitHotkey->SendHotkeyMessage(pMsg->message, pMsg->wParam,pMsg->lParam))>0) return ret;
			}
		}
	}
	return CFrameWnd::PreTranslateMessage(pMsg);
}

LRESULT GPFrameBar::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		referGPU[UnitId&0xFFFF]->m_CurMessage.message=message;
		referGPU[UnitId&0xFFFF]->m_CurMessage.wParam=wParam;
		referGPU[UnitId&0xFFFF]->m_CurMessage.lParam=lParam;
		if (referGPU[UnitId&0xFFFF]->DefWindowProc(message, wParam, lParam)) return 0;
	}

	if (message==GPM_SETAUTOSIZE)
	{
		GetParent()->PostMessage(GPM_SETAUTOSIZE,wParam);
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

	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)
	{
		UINT ret;
		if (message==GPM_CLIENTKILLFOCUS || message==GPM_CLIENTSETFOCUS)
		{
			if ((m_dwFlashFlag&FLASH_ON_FOCUS) && ((::GetWindowLong(m_hWnd,GWL_STYLE)&WS_CAPTION)==WS_CAPTION))
			{
				if (message==GPM_CLIENTKILLFOCUS)
				{
					#ifdef W_95
						::FlashWindow(m_hWnd,FALSE);
					#else
						#ifdef W_NT
							::FlashWindow(m_hWnd,FALSE);
						#else
							FLASHWINFO fi={0};
							fi.cbSize=sizeof(fi);
							fi.hwnd=m_hWnd;
							fi.dwFlags=FLASHW_CAPTION|FLASHW_STOP;
							fi.uCount=1;
							fi.dwTimeout=1;
							::FlashWindowEx(&fi);
							::FlashWindowEx(&fi);
						#endif
					#endif
				}
				if (message==GPM_CLIENTSETFOCUS)
				{
					#ifdef W_95
						::FlashWindow(m_hWnd,FALSE);
					#else
						#ifdef W_NT
							::FlashWindow(m_hWnd,FALSE);
						#else
							FLASHWINFO fi={0};
							fi.cbSize=sizeof(fi);
							fi.hwnd=m_hWnd;
							fi.dwFlags=FLASHW_CAPTION|FLASHW_TIMER;
							fi.uCount=1;
							fi.dwTimeout=100000000;
							::FlashWindowEx(&fi);
						#endif
					#endif
				}
			}
			PGPUNITINFO ui=(PGPUNITINFO)lParam;
			if (ui)
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent
					(m_hWnd, UnitId,message==GPM_CLIENTSETFOCUS?"OnCSetFocus":"OnCKillFocus",GPUnit::UnitInfoToString2(ui,"\x7F"));
		}

		if (message==GPM_CLIENTKILLFOCUS || message==GPM_CLIENTSETFOCUS || message==GPM_UPDATESCROLLER)
		{
			UpdateScrollers();
			if (referGPU && *referGPU)
			{
				HWND hParent=::GetParent(m_hWnd);
				int ParentID=referGPU[0]->GetObjectIdByHWND(hParent);
				if (ParentID>=0) ::SendMessage(hParent,GPM_UPDATESCROLLER,UnitId,0);
			}
		}

		if((ret=referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjMessage(m_hWnd, UnitId, message, wParam, lParam))>0) return ret;
		if (message==WM_KEYDOWN && referGPU!=NULL && referGPU[UnitId&0xFFFF]->UnitHotkey && this->m_hWnd!=NULL && IsWindowEnabled()==TRUE && IsWindowVisible()==TRUE)
				if((ret=referGPU[UnitId&0xFFFF]->UnitHotkey->SendHotkeyMessage(message, wParam,lParam))>0) return ret;
		if (message==GPM_PROCHOTKEY)
		{
			if(referGPU[UnitId&0xFFFF]->UnitHotkey && (ret=referGPU[UnitId&0xFFFF]->UnitHotkey->SendHotkeyMessage(WM_KEYDOWN, wParam,lParam))>0) return ret;
			GetParent()->SendMessage(message, wParam,lParam);
		}
		else
		if  (message==WM_KEYDOWN)
			GetParent()->SendMessage(GPM_PROCHOTKEY, wParam,lParam);

		if (message==WM_MENUCHAR)
			::SendMessage(referGPU[0]->UnitHWND,WM_MENUCHAR, wParam,lParam);
	}

	if (message==WM_SIZEPARENT && referGPU!=NULL)
	{
		UINT SizStyle=referGPU[UnitId&0xFFFF]->SizStyle;
		if ((SizStyle&0xFFFF0000)!=0)
		{
			AFX_SIZEPARENTPARAMS* lpLayout = (AFX_SIZEPARENTPARAMS*)lParam;

			CRect re;
			GetWindowRect(&re);
			switch((SizStyle&0xFFFF0000)/0x10000)
			{
			case GPUA_TOP:
				MoveWindow(lpLayout->rect.left,lpLayout->rect.top,lpLayout->rect.right-lpLayout->rect.left,re.Height());
				lpLayout->rect.top+=re.Height();
				break;
			case GPUA_BOTTOM:
				MoveWindow(lpLayout->rect.left,lpLayout->rect.bottom-re.Height(),lpLayout->rect.right-lpLayout->rect.left,re.Height());
				lpLayout->rect.bottom-=re.Height();
				break;
			case GPUA_LEFT:
				MoveWindow(lpLayout->rect.left,lpLayout->rect.top,re.Width(),lpLayout->rect.bottom-lpLayout->rect.top);
				lpLayout->rect.left+=re.Width();
				break;
			case GPUA_RIGHT:
				MoveWindow(lpLayout->rect.right-re.Width(),lpLayout->rect.top,re.Width(),lpLayout->rect.bottom-lpLayout->rect.top);
				lpLayout->rect.right-=re.Width();
				break;
			}
		}
	}

	switch(message)
	{
	case GPM_DRAGMOUSELEAVE:
		if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDragLeave","");
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

	if (m_bAutoFocus && (message==WM_NCLBUTTONDOWN ||  message==WM_MOUSEACTIVATE))
	{
		::BringWindowToTop(m_hWnd);
		if (!::IsChild(m_hWnd,::GetFocus())) ::SetFocus(m_hWnd);
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

void GPFrameBar::OnClose()
{
	if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClose","");
//	CFrameWnd::OnClose();
}

void GPFrameBar::OnSize(UINT nType, int cx, int cy)
{
	if (m_hWnd && nType==SIZE_MAXIMIZED && (GetStyle()&WS_POPUP)!=WS_POPUP)
	{
		RECT mRect={0};
		::GetClientRect(::GetParent(m_hWnd),&mRect);
		MoveWindow(&mRect,TRUE);
	}

	BOOL DOIT=TRUE;
	if (DlgAutoSize)
		DOIT=DlgAutoSize->CheckMainSize(m_hWnd,nType,&cx, &cy);
	if (DOIT)
		CFrameWnd::OnSize(nType, cx, cy);
	else 
		if (cx>0 && cy>0) Invalidate();

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
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

	UpdateScrollers();
	Invalidate();
	m_LastSizeType=m_LastSizeType*0x100+nType;
}

UINT GPFrameBar::DoMethod(const char *iStr, char *oStr)
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
	case 0: /*LoadBarState*/		LoadBarState(pos);		break;
	case 1: /*SaveBarState*/		SaveBarState(pos);		break;
	case 2: /*ShowControlBar*/
		{
			int nUnit;
			int bShow=1,bDelay=0;
			m_LastScanf=sscanf(pos,"%d,%d,%d",&nUnit,&bShow,&bDelay);
			if (referGPU && (UINT)nUnit<=(*referGPU)->m_NGPUNIT && referGPU[nUnit])
;
//				ShowControlBar( CControlBar* pBar, BOOL bShow, BOOL bDelay );

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
	case 4: /*GetControlBar*/
		break;
	case 5: /*GetMessageString*/
		break;
	case 6: /*IsTracking*/
		break;
	case 7: /*SetMessageText*/
		break;
	case 8: /*EnableDocking*/
		break;
	case 9: /*DockControlBar*/
		break;
	case 10: /*FloatControlBar*/
		break;
	case 11: /*BeginModalState*/
		break;
	case 12: /*EndModalState*/
		break;
	case 13: /*InModalState*/
		break;
	case 14: /*ShowOwnedWindows*/
		break;
	case 15: /*RecalcLayout*/
		break;

	case 16: /*UpdateGroup*/
		if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
			referGPU[UnitId&0xFFFF]->UpdateGroup(0,GetStyle());
		break;
	case  17: /*AddScroller ScrName,ObjName,nX,nY,nXPage,nYPage*/
	case  22: /*EnsureVisibleScroller ScrName,ObjName*/
		{
			CString ScrName=ExtractField(pos,1,",");
			CString ObjName=ExtractField(pos,2,",");
			UINT i=-1;

			if (referGPU!=NULL && referGPU[UnitId&0xFFFF]!=NULL)
			{
				for(i=0;i<(*referGPU)->m_NGPUNIT;i++)
					if (referGPU[i] && referGPU[i]->m_ObjName==ObjName)	break;

			}
			if (i<(*referGPU)->m_NGPUNIT)
			{
				if (strcmp(cArrMethods[nfunc],"AddScroller")==0)
				{
					CGPScroller *tmp=GetScroller(ScrName,referGPU[i]->UnitHWND);
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
					if (tmp) tmp->EnsureVisible(referGPU[i]->UnitHWND);
				}
			}
		}
		break;
	case  18: /*DelScroller ScrName*/
		DeleteScroller(pos);
		break;
	case  19: /*SetScroller ScrName,[nX],[nY],[nXPage],[nYPage][,Flags]*/
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
	case  20: /*UpdateScloller ScrName*/
		{
			CGPScroller *tmp=GetScroller(pos,NULL);
			if (tmp)	tmp->UpdatePosition();
		}
		break;
	case  21: /*SetScrollerPos ScrName,X,Y*/
		{
			CGPScroller *tmp=GetScroller(pos,NULL);
			if (tmp)
			tmp->SetScrollerPos(
				atoi(ExtractField(pos,2,",")),
				atoi(ExtractField(pos,3,",")));
		}
		break;
	case  23: /*barAutoSizingPause*/
		referGPU[UnitId&0xFFFF]->AutoSizingPause();
		break;
	case  24: /*barAutoSizingResume*/
		referGPU[UnitId&0xFFFF]->AutoSizingResume();
		break;
	case  25: /*barAutoSizingReset*/
		referGPU[UnitId&0xFFFF]->AutoSizingReset();
		break;
	case  26: /*barAutoSizingReinitSize*/
		referGPU[UnitId&0xFFFF]->AutoSizingReinitSize();
		break;
	case  27: /*Reposition*/
		SendMessage(DM_REPOSITION,0,0);
		break;
	case  28: /*barAutoSetAutoSizing*/
		referGPU[UnitId&0xFFFF]->AutoSetAutoSizing(0);
		break;
	case  29: /*FlashOnChildFocus*/
		m_dwFlashFlag=(m_dwFlashFlag&(0xFFFFFFFF^FLASH_ON_FOCUS))|(atoi(pos)?FLASH_ON_FOCUS:0);
		break;
	case  30: /*EnableThemeDialogTexture*/
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
						EnableThemeDialogTexture(m_hWnd,atoipos);
						Invalidate();
					}
					#endif
				#endif
			#endif
		#endif
		break;
	case  31: /*SetAutoFocus*/
		if (oStr) sprintf(oStr,"%d",m_bAutoFocus);
		m_bAutoFocus=atoi(pos);
		break;
	case  32: /*GetScrollerPos ScrollerName*/
		if (oStr)
		{
			*oStr=0;
			CGPScroller *tmp=GetScroller(pos,NULL);
			if (tmp)
				sprintf(oStr,"%d\x7F%d",tmp->CurPoint.x,tmp->CurPoint.y);
		}
		break;


	default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
	}

	return nfunc;
}


UINT GPFrameBar::GPSetProperty(char *iStr)
{
	char *iValue=new char [(int)strlen(iStr)+5];
	strcpy(iValue,iStr);
	UINT ret=1,i;
	char *pos=strchr(iValue,'=');

	if (pos!=NULL && m_hWnd)
	{
		char *prop[]={"ADDSTYLE", "DELSTYLE","STYLE",};
		int propnum;
		*(pos++)=0;
		for(propnum=0;propnum<3 && strcmp(prop[propnum],iValue)!=0;propnum++);
		if (propnum>=3) ret=2;
		else
		{
			ret=3;
			switch(propnum)
			{
			case 0: // ADDSTYLE
			case 1: // DELSTYLE
			case 2: // STYLE
				if (m_hWnd!=NULL)
				{
					ret=2;
					strcat(pos,"|");
					int InvFlg=0;
					for(i=0;i<N_DLG_STYLES;i++)
						if (strstr(pos,aDlgStyleName[i])!=NULL)
						{
							InvFlg++;
							switch(propnum)
							{
							case 2: /* STYLE*/
							case 0: /* ADDSTYLE*/	ModifyStyle(0,aDlgStyleUINT[i]);break;
							case 1: /* DELSTYLE*/	ModifyStyle(aDlgStyleUINT[i],0);break;
							}
						}
					if (InvFlg!=0) Invalidate();
				}
				break;
			default: /* end */
				ret=2;
				break;
			}
		}
		*(--pos)='=';
	}

	delete[] iValue;
	return ret;
}



BOOL GPFrameBar::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
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

		}


	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BOOL GPFrameBar::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if ((wParam!=1 && wParam!=2) || lParam!=0) return CFrameWnd::OnCommand(wParam, lParam);

	if (referGPU!=NULL)
	{
		if (wParam==1) referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnOk","");
		if (wParam==2) referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnCancel","");
	}
	return TRUE;

}

void GPFrameBar::RecalcLayout(BOOL bNotify)
{
	RepositionBars(0x0000,0xFFFF,nUnitENTIRE+50000);

//	CFrameWnd::RecalcLayout(bNotify);
}

int GPFrameBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	EnableDocking(CBRS_ALIGN_ANY  );

	return 0;
}

void GPFrameBar::OnDragMouseHover()
{
	if (referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(GPC.m_DragDrop.DragName)<0xFFFFFFFFL)
	{
		// Reset the timer.
		::SetTimer (GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nScrollInterval, NULL);

		// Get the current cursor position and window height.
		DWORD dwPos = ::GetMessagePos ();
		CPoint point (LOWORD (dwPos), HIWORD (dwPos));
		ScreenToClient (&point);

		CRect rect;
		GetClientRect (rect);
		int cy = rect.Height ();

		referGPU[UnitId&0xFFFF]->SendDropHoverEvent("",&GPC.m_DragDrop,&point);

		// Scroll the window if the cursor is near the top or bottom.
		if (point.y >= 0 && point.y <= referGPU[UnitId&0xFFFF]->m_nScrollMargin)
		{
			GPC.m_DragDrop.pImageList->DragShowNolock (FALSE);
			SendMessage (WM_VSCROLL, MAKEWPARAM (SB_LINEUP, 0), NULL);
			GPC.m_DragDrop.pImageList->DragShowNolock (TRUE);
			// Kill the timer if the window did not scroll, or redraw the drop target highlight if the window did scroll.
			if (GetScrollPos(SB_VERT))
				::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);
				else
					HighlightDropTarget(&GPC.m_DragDrop, point);
		}
		else
			if (point.y >= cy - referGPU[UnitId&0xFFFF]->m_nScrollMargin && point.y <= cy)
			{
				GPC.m_DragDrop.pImageList->DragShowNolock (FALSE);
				SendMessage (WM_VSCROLL, MAKEWPARAM (SB_LINEDOWN, 0), NULL);
				GPC.m_DragDrop.pImageList->DragShowNolock (TRUE);
				// Kill the timer if the window did not scroll, or redraw the drop target highlight if the window did scroll.
				if (GetScrollPos(SB_HORZ)) ::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);
				else
					HighlightDropTarget(&GPC.m_DragDrop, point);
			}
			else ::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);
	}
}

void GPFrameBar::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	if (pDrDrStruct && pDrDrStruct->pImageList != NULL)
	{
		::ScreenToClient(m_hWnd,point);
		::KillTimer(pDrDrStruct->hWndDrag,DRAG_TIMER_ID);
		// Offset point
		if (referGPU && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->OffsetWndPoint(point);

		// Erase the old drag image and draw a new one.
		if (pDrDrStruct->hWndLast!=m_hWnd)
		{
			pDrDrStruct->pImageList->DragLeave(CWnd::FromHandle(pDrDrStruct->hWndLast));
			pDrDrStruct->hWndLast=m_hWnd;
			pDrDrStruct->pImageList->DragEnter(this, CPoint(*point));
		}
		pDrDrStruct->pImageList->DragMove (CPoint(*point));

		DWORD bDropTarget=0xFFFFFFFF;
		BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
		// Highlight the drop target if the cursor is over an item.
		if (mDrop)
			bDropTarget = HighlightDropTarget(pDrDrStruct, CPoint(*point));
		// Modify the cursor to provide visual feedback to the user. Note: It's important to do this AFTER the call to DragMove.
		::SetCursor (bDropTarget==0xFFFFFFFF ?
			AfxGetApp()->LoadStandardCursor (IDC_NO)
			: (HCURSOR) ::GetClassLong (m_hWnd, GCL_HCURSOR));

		referGPU[UnitId&0xFFFF]->SendDropMoveEvent("",pDrDrStruct,point);

		if (mDrop)
			::SetTimer (pDrDrStruct->hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nDelayInterval, NULL);
	}
}

void GPFrameBar::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && referGPU)
	{
		::ScreenToClient(m_hWnd,point);
		referGPU[UnitId&0xFFFF]->SendDropEvent("",pDrDrStruct,point);
	}
}

DWORD GPFrameBar::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	return 0;
}

LRESULT GPFrameBar::OnNcHitTest(CPoint point)
{
	LRESULT ret=CFrameWnd::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

#include "GP_TermDoc.h"

void GPFrameBar::OnKillFocus(CWnd* pNewWnd)
{
	CFrameWnd::OnKillFocus(pNewWnd);
	GPUNITINFO ui;
	GPUNITINFO uiold;
	if (referGPU && referGPU[UnitId&0xFFFF])
		referGPU[UnitId&0xFFFF]->GetUnitInfo(ui);
	if (pNewWnd)
	{
		GPC.m_Document->FindObject(pNewWnd->m_hWnd,uiold);
		ui.hWnd2=uiold.hWnd;
		ui.IdDlg2=uiold.IdDlg;
		ui.IdObj2=uiold.IdObj;
	}
	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)
	{
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent
			(m_hWnd, UnitId,"OnKillFocus",GPUnit::UnitInfoToString2(&ui,"\x7F"));
	}
	::SendMessage(::GetParent(m_hWnd),GPM_CLIENTKILLFOCUS,(WPARAM)(pNewWnd?pNewWnd->m_hWnd:NULL),(LPARAM)&ui);
}

void GPFrameBar::OnSetFocus(CWnd* pOldWnd)
{
	CFrameWnd::OnSetFocus(pOldWnd);
	GPUNITINFO ui;
	GPUNITINFO uiold;
	if (referGPU && referGPU[UnitId&0xFFFF])
		referGPU[UnitId&0xFFFF]->GetUnitInfo(ui);
	if (pOldWnd)
	{
		GPC.m_Document->FindObject(pOldWnd->m_hWnd,uiold);
		ui.hWnd2=uiold.hWnd;
		ui.IdDlg2=uiold.IdDlg;
		ui.IdObj2=uiold.IdObj;
	}
	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent
			(m_hWnd, UnitId,"OnSetFocus",GPUnit::UnitInfoToString2(&ui,"\x7F"));

	::SendMessage(::GetParent(m_hWnd),GPM_CLIENTSETFOCUS,(WPARAM)(pOldWnd?pOldWnd->m_hWnd:NULL),(LPARAM)&ui);
}


CGPScroller * GPFrameBar::GetScroller(const char *iStr, HWND iScrHwnd)
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

UINT GPFrameBar::DeleteScroller(const char *iStr)
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

void GPFrameBar::UpdateScrollers()
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

void GPFrameBar::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (ScrollerArr)
	{
		UINT i;
		for(i=0;i<nScroller;i++)
			if (ScrollerArr[i])
				ScrollerArr[i]->OnHScroll(nSBCode, nPos, pScrollBar);
	}
	else	CFrameWnd::OnHScroll(nSBCode, nPos, pScrollBar);
	if (referGPU && referGPU[UnitId&0xFFFF]->m_SizerArray)	Invalidate();
}

void GPFrameBar::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (ScrollerArr)
	{
		UINT i;
		for(i=0;i<nScroller;i++)
			if (ScrollerArr[i])
				ScrollerArr[i]->OnVScroll(nSBCode, nPos, pScrollBar);
	}
	else	CFrameWnd::OnVScroll(nSBCode, nPos, pScrollBar);
	if (referGPU && referGPU[UnitId&0xFFFF]->m_SizerArray)	Invalidate();
}

void GPFrameBar::OnSizing(UINT fwSide, LPRECT pRect)
{
	CFrameWnd::OnSizing(fwSide, pRect);
	UpdateScrollers();
}

void GPFrameBar::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CFrameWnd::OnShowWindow(bShow, nStatus);
	if ((m_LastSizeType&0x200)) ShowWindow(SW_MAXIMIZE);
}
