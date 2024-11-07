// GPDialogBar.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPDialogBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// GPDialogBar
const UINT GPDialogBar::uNMethods=1;
const char *GPDialogBar::cArrMethods[]={
		"UpdateGroup","","","","","",
		"","","", "", "", 
	};
const char *GPDialogBar::cArrMethodsParams[]={
		"","","","","","",
		"","","", "", "", 
	};

GPDialogBar::GPDialogBar(UINT iUnitId)
{
	referGPU=NULL;
	UnitId=iUnitId;
}

GPDialogBar::~GPDialogBar()
{
}


BEGIN_MESSAGE_MAP(GPDialogBar, CDialogBar)
	//{{AFX_MSG_MAP(GPDialogBar)
	ON_WM_PARENTNOTIFY()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_WM_NCHITTEST()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPDialogBar message handlers


UINT GPDialogBar::DoMethod(const char *iStr, char *oStr)
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

	int retint=-123456;

	try
	{
		switch(nfunc)
		{
		case 0:  /*UpdateGroup*/
			if (referGPU!=NULL && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
				referGPU[UnitId&0xFFFF]->UpdateGroup(-123456,GetStyle());
			break;
		default:
			nfunc=GPUnit::DoControlBarMethod(this,iStr,oStr); break;
		}
	}catch(...)
	{
		char *str=new char [200+(int)strlen(pos)];
		#ifdef RUS
			sprintf(str,"Ошибка выполнения метода %s %s",met,pos);
			MessageBox(str,"Ошибка метода");
		#else
			sprintf(str,"Error execution of method %s %s",met,pos);
			MessageBox(str,"Error execution");
		#endif
		if (oStr!=NULL) strcpy(oStr,str);
		nfunc=0xFFFFFFFFL;
		GPC.m_ErrReport.GPWriteErrorLog("GPDialogBar", "DoMethod",iStr);
		delete[] str;
	}
	switch(nfunc)
	{
	case 123456: /**/
		GetParent()->SendMessage(WM_APP+1);
		break;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
	return nfunc;
}

UINT GPDialogBar::GPSetProperty(char *iStr)
{
	char *iValue=new char [(int)strlen(iStr)+5];
	strcpy(iValue,iStr);
	UINT ret=1,i;
	char *pos=strchr(iValue,'=');

	if (pos!=NULL && m_hWnd)
	{
		char *prop[]={ "TEXT", "ADDSTYLE", "DELSTYLE","STYLE",};
		int propnum;
		*(pos++)=0;
		for(propnum=0;propnum<4 && strcmp(prop[propnum],iValue)!=0;propnum++);
		if (propnum>=4) ret=2;
		else
		{
			ret=3;
			switch(propnum)
			{
			case 0: // TEXT
				SetWindowText(pos);
				Invalidate();
				break;
			case 1: // ADDSTYLE
			case 2: // DELSTYLE
			case 3: // STYLE
				if (m_hWnd!=NULL)
				{
					ret=2;
					strcat(pos,"|");
					int InvFlg=0;

					UINT Stl=0;
					switch(propnum)
					{
					case 1: /* ADDSTYLE*/	Stl=GetBarStyle();
					case 3: /* STYLE*/
						for(i=0;i<N_CTRLBAR_STYLES;i++)
							if (strstr(pos,aCtrlBarStyleName[i])!=NULL)
							{
								InvFlg++;
								Stl|=aCtrlBarStyleUINT[i];
							}
						SetBarStyle(Stl);
						break;
					case 2: /* DELSTYLE*/
						for(i=0;i<N_CTRLBAR_STYLES;i++)
							if (strstr(pos,aCtrlBarStyleName[i])!=NULL)
							{
								InvFlg++;
								Stl|=aCtrlBarStyleUINT[i];
							}
						SetBarStyle(GetBarStyle()&(Stl^0xFFFFFFFF));
						break;
					}

					Invalidate();
					GetParent()->SendMessage(WM_APP+1);
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


void GPDialogBar::OnParentNotify(UINT message, LPARAM lParam)
{
	CDialogBar::OnParentNotify(message, lParam);
	char txt[100];
	if (message==WM_CREATE || message==WM_DESTROY)
		sprintf(txt,"%d\x7F%d\x7F%X",message/0x10000,(message&0xFFFF),lParam/0x10000);
	else
		sprintf(txt,"%d\x7F%d\x7F%d\x7F%d",message/0x10000,(message&0xFFFF),lParam/0x10000,(lParam&0xFFFF));
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"ParentNotify",txt);
}

HBRUSH GPDialogBar::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = NULL;
	if (referGPU && referGPU[UnitId&0xFFFF]->m_brBkgnd) 
	{
		hbr = (HBRUSH) *(referGPU[UnitId&0xFFFF]->m_brBkgnd);
	    RECT rc;
		::GetWindowRect(pWnd->m_hWnd, &rc);
		::MapWindowPoints(NULL, m_hWnd, (POINT *)&rc, 2);
		::SetBrushOrgEx(pDC->m_hDC, -rc.left, -rc.top, NULL);
	}

	if (pWnd && pDC && pWnd->m_hWnd && pDC->m_hDC)
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CDialogBar::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}

LRESULT GPDialogBar::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		referGPU[UnitId&0xFFFF]->m_CurMessage.message=message;
		referGPU[UnitId&0xFFFF]->m_CurMessage.wParam=wParam;
		referGPU[UnitId&0xFFFF]->m_CurMessage.lParam=lParam;
		if (referGPU[UnitId&0xFFFF]->DefWindowProc(message, wParam, lParam)) return 0;
	}

	if (message==GPM_SETAUTOSIZE)
		GetParent()->PostMessage(GPM_SETAUTOSIZE,wParam);

	if (message==GPN_UPDATESIZE) GetParent()->SendMessage(GPN_UPDATESIZE);

	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)
	{
		if (message==GPM_CLIENTKILLFOCUS || message==GPM_CLIENTSETFOCUS)
		{
			PGPUNITINFO ui=(PGPUNITINFO)lParam;
			if (ui)
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent
					(m_hWnd, UnitId,message==GPM_CLIENTSETFOCUS?"OnCSetFocus":"OnCKillFocus",GPUnit::UnitInfoToString2(ui,"\x7F"));
		}
		UINT ret;
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

	LRESULT lpr;
	if (message==WM_SETCURSOR && GPC.m_bWaitCursor) lpr=FALSE;
	else lpr=CDialogBar::WindowProc(message, wParam, lParam);

	return lpr;
}

BOOL GPDialogBar::PreTranslateMessage(MSG* pMsg)
{
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		referGPU[UnitId&0xFFFF]->m_CurPreMessage=pMsg;
		if (!referGPU[UnitId&0xFFFF]->DefPreTranslateMessage(pMsg)) return 0;
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
	return CDialogBar::PreTranslateMessage(pMsg);
}

void GPDialogBar::OnClose()
{
	if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClose","");
//	CDialogBar::OnClose();
}

BOOL GPDialogBar::OnInitDialog()
{
	CRect MinimumRecr;
	GetWindowRect(&MinimumRecr);
/*	char *posRect=strstr(iStr,"_ECT=");
	if (!posRect) strstr(iStr,"RECT=");
	if (posRect)
	{
		CRect InitRect;
		m_LastScanf=sscanf(posRect+5,"%d,%d,%d,%d",&InitRect.left,&InitRect.top,&InitRect.right,&InitRect.bottom);
		MinimumRecr.bottom=MinimumRecr.top+InitRect.Height();
		MinimumRecr.right=MinimumRecr.left+InitRect.Width();
//		if ((GetWindowLong(m_hWnd,GWL_STYLE)&WS_POPUP)==WS_POPUP) 
//			MoveWindow(MinimumRecr);
	}
*/
	return TRUE;
}

void GPDialogBar::OnDragMouseHover()
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

void GPDialogBar::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
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

void GPDialogBar::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && referGPU)
	{
		::ScreenToClient(m_hWnd,point);
		referGPU[UnitId&0xFFFF]->SendDropEvent("",pDrDrStruct,point);
	}
}

DWORD GPDialogBar::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	return 0;
}


LRESULT GPDialogBar::OnNcHitTest(CPoint point)
{
	LRESULT ret=CDialogBar::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

void GPDialogBar::OnSize(UINT nType, int cx, int cy)
{
	CDialogBar::OnSize(nType, cx, cy);

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
	}
}
