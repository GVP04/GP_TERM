// GPScrollBar.cpp : implementation file
//

#include "stdafx.h"
#include "GP_term.h"
#include "GPScrollBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPScrollBar
const UINT GPScrollBar::nSBCode=9;
const char *GPScrollBar::cSBCode[10]={
	"SB_ENDSCROLL","SB_LEFT","SB_RIGHT","SB_LINELEFT","SB_LINERIGHT",
	"SB_PAGELEFT","SB_PAGERIGHT","SB_THUMBPOSITION","SB_THUMBTRACK","ERROR",
};

const UINT GPScrollBar::uSBCode[9]={
	SB_ENDSCROLL,SB_LEFT,SB_RIGHT,SB_LINELEFT,SB_LINERIGHT,
	SB_PAGELEFT,SB_PAGERIGHT,SB_THUMBPOSITION,SB_THUMBTRACK,
};

const UINT GPScrollBar::uNMethods=11;
const char *GPScrollBar::cArrMethods[]={
		"GetScrollPos","SetScrollPos","GetScrollRange","SetScrollRange","ShowScrollBar",
		"EnableScrollBar","SetScrollInfo","GetScrollInfo","GetScrollLimit","UpdateGroup",
		"GetScrollBarInfo",
		"","","", "", "", 
	};
const char *GPScrollBar::cArrMethodsParams[]={
		"","ipos,bRedr","","start,end,bRedr","bShow",
		"EnableType","nMin,nMax,nPage,nPos,nTrackPos,bRedr","","","",
		"",
		"","","", "", "", 
	};

GPScrollBar::GPScrollBar(UINT iUnitId)
{
	referGPU=NULL;
	UnitId=iUnitId;
	m_LastHiPos=-123456;
}

GPScrollBar::~GPScrollBar()
{
}


BEGIN_MESSAGE_MAP(GPScrollBar, CScrollBar)
	//{{AFX_MSG_MAP(GPScrollBar)
	ON_WM_CLOSE()
	ON_WM_SIZING()
	ON_WM_NCHITTEST()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_PARENTNOTIFY_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPScrollBar message handlers


UINT GPScrollBar::DoMethod(const char *iStr, char *oStr)
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
	case 0: /*GetScrollPos*/	if (oStr!=NULL)	sprintf(oStr,"%d",GetScrollPos());	break;
	case 1: /*SetScrollPos*/
		{
			int retint,ipos,redr; m_LastScanf=sscanf(pos,"%d,%d",&ipos,&redr);
			retint=SetScrollPos(ipos,redr);
			if (oStr!=NULL)	sprintf(oStr,"%d",retint);
			if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
				DoMethod("UpdateGroup",NULL);
		}
		break;
	case 2: /*GetScrollRange*/
		if (oStr!=NULL)
		{
			int start,end;
			GetScrollRange(&start,&end);
			sprintf(oStr,"%d\x7F%d",start,end);
		}
		break;
	case 3: /*SetScrollRange*/
		{
			int start,end,redr; m_LastScanf=sscanf(pos,"%d,%d,%d",&start,&end,&redr);
			SetScrollRange(start,end,redr);
			if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
				DoMethod("UpdateGroup",NULL);
		}
		break;
	case 4: /*ShowScrollBar*/	ShowScrollBar(atoi(pos));	break;
	case 5: /*EnableScrollBar*/
		{
			int retint;
			if (strstr(pos,"FALSE")!=NULL)	retint=EnableScrollBar(ESB_DISABLE_BOTH);
			else
			if (strstr(pos,"LTUP")!=NULL)	retint=EnableScrollBar(ESB_DISABLE_LTUP);
			else
			if (strstr(pos,"RTDN")!=NULL)	retint=EnableScrollBar(ESB_DISABLE_RTDN);
			else							retint=EnableScrollBar(ESB_ENABLE_BOTH);

			if (oStr!=NULL)	sprintf(oStr,"%d",retint);
		}
		break;
	case 6: /*SetScrollInfo*/
		{
			int retint;BOOL redr=TRUE;
			SCROLLINFO si={0};
			si.cbSize=sizeof(si);
			m_LastScanf=sscanf(pos,"%d,%d,%u,%d,%d,%d",&si.nMin,&si.nMax,&si.nPage,&si.nPos,&si.nTrackPos,&redr);
			si.fMask=SIF_ALL;
			retint=SetScrollInfo(&si,redr);
			if (oStr!=NULL)	sprintf(oStr,"%d",retint);
			if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
				DoMethod("UpdateGroup",NULL);
		}
		break;
	case 7: /*GetScrollInfo*/
		if (oStr!=NULL)
		{
			SCROLLINFO si={0};
			si.cbSize=sizeof(si);
			si.fMask=SIF_ALL;
			if (GetScrollInfo(&si,SIF_ALL))
					sprintf(oStr,"%d\x7F%d\x7F%u\x7F%d\x7F%d",si.nMin,si.nMax,si.nPage,si.nPos,si.nTrackPos);
		}
		break;
	case 8: /*GetScrollLimit*/	if (oStr!=NULL)	sprintf(oStr,"%d",GetScrollLimit());	break;
	case 9: /*UpdateGroup*/
		if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
			referGPU[UnitId&0xFFFF]->UpdateGroup(GetScrollPos(),GetStyle());
		break;
	case 10: /*GetScrollBarInfo*/
		if (oStr)
		{
			SCROLLBARINFO sbi={0};
			sbi.cbSize=sizeof(sbi);

			if (SendMessage(SBM_GETSCROLLBARINFO,0,(LPARAM)&sbi))
			{
				sprintf(oStr,"%d\x07%d\x07%d\x07%d\x7F%d\x7F%d\x7F%d\x7F%d",
					sbi.rcScrollBar.top,
					sbi.rcScrollBar.left,
					sbi.rcScrollBar.bottom,
					sbi.rcScrollBar.right,
					sbi.dxyLineButton,
					sbi.xyThumbTop,
					sbi.xyThumbBottom,
					sbi.reserved
					);
				UINT i;
				for(i=0;i<CCHILDREN_SCROLLBAR;i++)
				{
					strcat(oStr,"\x7F");
					if (sbi.rgstate[i]==STATE_SYSTEM_INVISIBLE) strcat(oStr,"INVISIBLE");
					if (sbi.rgstate[i]==STATE_SYSTEM_OFFSCREEN) strcat(oStr,"OFFSCREEN");
					if (sbi.rgstate[i]==STATE_SYSTEM_PRESSED) strcat(oStr,"PRESSED");
					if (sbi.rgstate[i]==STATE_SYSTEM_UNAVAILABLE) strcat(oStr,"UNAVAILABLE");
				}
			}
		}
		break;
	default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
	}
	return nfunc;
}


UINT GPScrollBar::GPSetProperty(char *iStr)
{
	char *iValue=new char [(int)strlen(iStr)+5];
	strcpy(iValue,iStr);
	UINT ret=1,i;
	char *pos=strchr(iValue,'=');

	if (pos!=NULL && m_hWnd)
	{
		char *prop[]={ "ENABLE", "ADDSTYLE", "DELSTYLE","STYLE", };
		int propnum;
		*(pos++)=0;
		for(propnum=0;propnum<4 && strcmp(prop[propnum],iValue)!=0;propnum++);
		if (propnum>=4) ret=2;
		else
		{
			ret=3;
			switch(propnum)
			{
			case 0: /* enable*/
				if (strstr(pos,"FALSE")!=NULL)	EnableScrollBar(ESB_DISABLE_BOTH);
				else
				if (strstr(pos,"LTUP")!=NULL)	EnableScrollBar(ESB_DISABLE_LTUP);
				else
				if (strstr(pos,"RTDN")!=NULL)	EnableScrollBar(ESB_DISABLE_RTDN);
				else							EnableScrollBar(ESB_ENABLE_BOTH);
				Invalidate();
				break;
			case 3: /* STYLE*/
			case 1: // ADDSTYLE
			case 2: // DELSTYLE
				if (m_hWnd!=NULL)
				{
					ret=2;
					strcat(pos,"|");
					int InvFlg=0;
					// ScrollBar specif
					for(i=0;i<N_SCROLL_STYLES;i++)
						if (strstr(pos,aScrollStyleName[i])!=NULL)
						{
							InvFlg++;
							switch(propnum)
							{
							case 3: /* STYLE*/
							case 1: /* ADDSTYLE*/	ModifyStyle(0,aScrollStyleUINT[i]);break;
							case 2: /* DELSTYLE*/	ModifyStyle(aScrollStyleUINT[i],0);break;
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

void GPScrollBar::ParentNotify(UINT message, LPARAM lParam)
{
	char txt[100];
	if (message==WM_CREATE || message==WM_DESTROY)
		sprintf(txt,"%d\x7F%d\x7F%X",message/0x10000,(message&0xFFFF),lParam/0x10000);
	else
		sprintf(txt,"%d\x7F%d\x7F%d\x7F%d",message/0x10000,(message&0xFFFF),lParam/0x10000,(lParam&0xFFFF));
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"ParentNotify",txt);
}

LRESULT GPScrollBar::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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

	if (message==GPN_UPDATESIZE) 
		GetParent()->PostMessage(GPN_UPDATESIZE);

	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)
	{
		UINT ret;
		if (message==GPM_CLIENTKILLFOCUS || message==GPM_CLIENTSETFOCUS)
		{
			PGPUNITINFO ui=(PGPUNITINFO)lParam;
			if (ui)
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent
					(m_hWnd, UnitId,message==GPM_CLIENTSETFOCUS?"OnCSetFocus":"OnCKillFocus",GPUnit::UnitInfoToString2(ui,"\x7F"));
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
		GPC.m_DragDrop.pImageList->DragShowNolock(FALSE);
		Invalidate();
		UpdateWindow();
		m_LastHiPos=-123456;
		GPC.m_DragDrop.pImageList->DragShowNolock(TRUE);
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

	LRESULT lpr=TRUE;
	if (message==WM_SETCURSOR && GPC.m_bWaitCursor) lpr=FALSE;
	else lpr=CScrollBar::WindowProc(message, wParam, lParam);
	return lpr;
}

BOOL GPScrollBar::PreTranslateMessage(MSG* pMsg)
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

	return CScrollBar::PreTranslateMessage(pMsg);
}

void GPScrollBar::OnClose()
{
	if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClose","");
//	CScrollBar::OnClose();
}

void GPScrollBar::OnSizing(UINT fwSide, LPRECT pRect)
{
	BOOL EnableSz=TRUE;
	UINT SizStyle=referGPU[UnitId&0xFFFF]->SizStyle;
	if ((SizStyle&0xFFFF)!=0)
	{
		CRect re;
		GetWindowRect(&re);
		switch(fwSide)
		{
		case WMSZ_BOTTOM:
			if ((SizStyle&GPUA_BOTTOM)!=GPUA_BOTTOM) EnableSz=FALSE;
			break;
		case WMSZ_BOTTOMLEFT:
			if ((SizStyle&GPUA_BOTTOM)!=GPUA_BOTTOM && (SizStyle&GPUA_LEFT)!=GPUA_LEFT) EnableSz=FALSE;
			break;
		case WMSZ_BOTTOMRIGHT:
			if ((SizStyle&GPUA_BOTTOM)!=GPUA_BOTTOM && (SizStyle&GPUA_RIGHT)!=GPUA_RIGHT) EnableSz=FALSE;
			break;
		case WMSZ_LEFT:
			if ((SizStyle&GPUA_LEFT)!=GPUA_LEFT) EnableSz=FALSE;
			break;
		case WMSZ_RIGHT:
			if ((SizStyle&GPUA_RIGHT)!=GPUA_RIGHT) EnableSz=FALSE;
			break;
		case WMSZ_TOP:
			if ((SizStyle&GPUA_TOP)!=GPUA_TOP) EnableSz=FALSE;
			break;
		case WMSZ_TOPLEFT:
			if ((SizStyle&GPUA_LEFT)!=GPUA_LEFT && (SizStyle&GPUA_TOP)!=GPUA_TOP) EnableSz=FALSE;
			break;
		case WMSZ_TOPRIGHT:
			if ((SizStyle&GPUA_RIGHT)!=GPUA_RIGHT && (SizStyle&GPUA_TOP)!=GPUA_TOP) EnableSz=FALSE;
			break;
		}
		if (EnableSz==FALSE)
		{
			pRect->top=re.top;
			pRect->left=re.left;
			pRect->right=re.right;
			pRect->bottom=re.bottom;
		}
		else
		{
			GetParent()->SendMessage(WM_SIZE);
		}
	}

	if (EnableSz) CScrollBar::OnSizing(fwSide, pRect);

	GetParent()->SendMessage(GPN_UPDATESIZE);

}

void GPScrollBar::OnDragMouseHover()
{
	if (referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(GPC.m_DragDrop.DragName)<0xFFFFFFFFL)
	{
		// Reset the timer.
		::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);

		// Get the current cursor position and window height.
		DWORD dwPos = ::GetMessagePos ();
		CPoint point (LOWORD (dwPos), HIWORD (dwPos));
		ScreenToClient (&point);
		int MaxPOs=0,MinPos=0;
		GetScrollRange(&MaxPOs,&MinPos);
		CRect re;
		GetClientRect(&re);
		int Width=re.Width();
		int mPos=point.x;
		if ((GetStyle()&SBS_VERT)==SBS_VERT)
		{
			Width=re.Height();
			mPos=point.y;
		}
		CString tmps;
		tmps.Format("%d\x07%d\x07%d\x07%d",MinPos,MaxPOs,GetScrollPos(),(int)((MaxPOs-MinPos)/Width*mPos));

		referGPU[UnitId&0xFFFF]->SendDropHoverEvent(tmps,&GPC.m_DragDrop,&point);
	}
}

void GPScrollBar::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
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

		int MaxPOs=0,MinPos=0;
		GetScrollRange(&MaxPOs,&MinPos);
		CRect re;
		GetClientRect(&re);
		int Width=re.Width();
		int mPos=point->x;
		if ((GetStyle()&SBS_VERT)==SBS_VERT)
		{
			Width=re.Height();
			mPos=point->y;
		}
		CString tmps;
		tmps.Format("%d\x07%d\x07%d\x07%d",MinPos,MaxPOs,GetScrollPos(),(int)((MaxPOs-MinPos)/Width*mPos));

		referGPU[UnitId&0xFFFF]->SendDropMoveEvent(tmps,pDrDrStruct,point);


		if (mDrop)
			::SetTimer (pDrDrStruct->hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nDelayInterval, NULL);
	}
}

void GPScrollBar::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && referGPU)
	{
		pDrDrStruct->pImageList->DragShowNolock(FALSE);
		Invalidate();
		UpdateWindow();
		pDrDrStruct->pImageList->DragShowNolock(TRUE);
		m_LastHiPos=-123456;
		::ScreenToClient(m_hWnd,point);
		int MaxPOs=0,MinPos=0;
		GetScrollRange(&MaxPOs,&MinPos);
		CRect re;
		GetClientRect(&re);
		int Width=re.Width();
		int mPos=point->x;
		if ((GetStyle()&SBS_VERT)==SBS_VERT)
		{
			Width=re.Height();
			mPos=point->y;
		}
		CString tmps;
		tmps.Format("%d\x07%d\x07%d\x07%d",MinPos,MaxPOs,GetScrollPos(),(int)((MaxPOs-MinPos)/Width*mPos));
		referGPU[UnitId&0xFFFF]->SendDropEvent(tmps,pDrDrStruct,point);
	}
}

DWORD GPScrollBar::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	pDrDrStruct->pImageList->DragShowNolock(FALSE);
	CRect re;
	GetClientRect(&re);
	if ((GetStyle()&SBS_VERT)==SBS_VERT)
	{
		re.top=re.bottom=point.y;
		re.InflateRect(0,2);
		if (m_LastHiPos!=point.y)
		{
			if (m_LastHiPos!=-123456)
			{
				CRect re2=re;
				re2.top=re2.bottom=m_LastHiPos;
				re2.InflateRect(0,2);
				GetDC()->InvertRect(&re2);
			}
			GetDC()->InvertRect(&re);
		}
		m_LastHiPos=point.y;
	}
	else
	{
		re.left=re.right=point.x;
		re.InflateRect(2,0);
		if (m_LastHiPos!=point.x)
		{
			if (m_LastHiPos!=-123456)
			{
				CRect re2=re;
				re2.left=re2.right=m_LastHiPos;
				re2.InflateRect(2,0);
				GetDC()->InvertRect(&re2);
			}
			GetDC()->InvertRect(&re);
		}
		m_LastHiPos=point.x;
	}

	pDrDrStruct->pImageList->DragShowNolock(TRUE);

	return 0;
}

LRESULT GPScrollBar::OnNcHitTest(CPoint point)
{
	LRESULT ret=CScrollBar::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

const char *GPScrollBar::GetSBCodeStr(UINT SBCode)
{
	int i;
	for(i=0;i<9 && SBCode!=uSBCode[i];i++);

	return cSBCode[i];
}

#include "GP_TermDoc.h"

void GPScrollBar::OnKillFocus(CWnd* pNewWnd)
{
	CScrollBar::OnKillFocus(pNewWnd);
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
	::PostMessage(::GetParent(m_hWnd),GPM_CLIENTKILLFOCUS,(WPARAM)(pNewWnd?pNewWnd->m_hWnd:NULL),(LPARAM)&ui);
}

void GPScrollBar::OnSetFocus(CWnd* pOldWnd)
{
	CScrollBar::OnSetFocus(pOldWnd);
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

	::PostMessage(::GetParent(m_hWnd),GPM_CLIENTSETFOCUS,(WPARAM)(pOldWnd?pOldWnd->m_hWnd:NULL),(LPARAM)&ui);
}


void GPScrollBar::OnSize(UINT nType, int cx, int cy)
{
	CScrollBar::OnSize(nType, cx, cy);

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
	}
}

HBRUSH GPScrollBar::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CScrollBar::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}

BOOL GPScrollBar::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult) 
{

	return CScrollBar::OnChildNotify(message, wParam, lParam, pLResult);
}



