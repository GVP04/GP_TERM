// GPProgress.cpp : implementation file
//

#include "stdafx.h"
#include "GP_term.h"
#include "GPProgress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPProgress
const UINT GPProgress::uNMethods=20;
const char *GPProgress::cArrMethods[]={
		"SetRange","GetRange","GetPos","SetPos","OffsetPos",
		"SetStep","StepIt","SetRange32","GetRange32","UpdateGroup",
		"SetBarColor","SetBkColor","SetNextPos","SetNextPosMod", "SetMarquee", 
		"GetStep", "GetBKColor", "GetBarColor", "SetState", "GetState", 
		"", "", "", "", "", 
	};

const char *GPProgress::cArrMethodsParams[]={
		"start,end","","","nPos","nOffsetPos",
		"nSetStep","nStepIt","start,end","","",
		"R,G,B","R,G,B","[nItems]","[nItems]", "bOnOff,Timeout", 
		"", "", "", "State", "", 
		"", "", "", "", "", 
	};

GPProgress::GPProgress(UINT iUnitId)
{
	referGPU=NULL;
	UnitId=iUnitId;
	m_LastHiPos=-123456;
}

GPProgress::~GPProgress()
{
}


BEGIN_MESSAGE_MAP(GPProgress, CProgressCtrl)
	//{{AFX_MSG_MAP(GPProgress)
	ON_NOTIFY_REFLECT(NM_OUTOFMEMORY, OnOutofmemory)
	ON_WM_PARENTNOTIFY_REFLECT()
	ON_WM_CLOSE()
	ON_WM_SIZING()
	ON_WM_NCHITTEST()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPProgress message handlers


UINT GPProgress::DoMethod(const char *iStr, char *oStr)
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
	case 0: /*SetRange*/
	case 7: /*SetRange32*/
		{

			int start,end; m_LastScanf=sscanf(pos,"%d,%d",&start,&end);
			SetRange32(start,end);
			if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
				DoMethod("UpdateGroup",NULL);
		}
		break;
	case 1: /*GetRange*/
	case 8: /*GetRange32*/
		if (oStr!=NULL)
		{
			int start,end;
			GetRange(start,end);
			sprintf(oStr,"%d\x7F%d",start,end);
		}
		break;
	case 2: /*GetPos*/	if (oStr!=NULL)	sprintf(oStr,"%d",GetPos());	break;
		{
			int start,end; m_LastScanf=sscanf(pos,"%d,%d",&start,&end);
			SetRange32(start,end);
		}
		break;
	case 3: /*SetPos*/
	case 4: /*OffsetPos*/
	case 5: /*SetStep*/
		{
			int retint=-1;
			if (nfunc==3)	retint=SetPos(atoi(pos));
			else
				if (nfunc==4)	retint=OffsetPos(atoi(pos));
				else
					if (nfunc==5)	retint=SetStep(atoi(pos));

			if (oStr!=NULL)	sprintf(oStr,"%d",retint);
			if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
				DoMethod("UpdateGroup",NULL);
		}
		break;
	case 6: /*StepIt*/
		{
			int retint;
			retint=StepIt();
			if (oStr!=NULL)	sprintf(oStr,"%d",retint);
			if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
				DoMethod("UpdateGroup",NULL);
		}
		break;
	case 9: /*UpdateGroup*/
		if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
			referGPU[UnitId&0xFFFF]->UpdateGroup(GetPos(),GetStyle());
		break;
	case 10: /*SetBarColor*/
	case 11: /*SetBkColor*/
		{
			UINT r=0,g=0,b=0;
			m_LastScanf=sscanf(pos,"%d,%d,%d",&r,&g,&b);
			COLORREF clr=0;
			clr=SendMessage(nfunc==10?PBM_SETBARCOLOR:PBM_SETBKCOLOR,0,(LPARAM)RGB(r,g,b));
			if (oStr)
				sprintf(oStr,"%d\x7F%d\x7F%d",r,g,b);
		}
		break;
	case 12: /*SetNextPos*/
	case 13: /*SetNextPosMod*/
		{
			int nDelta=atoi(pos);
			if (*pos==0) nDelta=1;
			if (nDelta!=0)
			{
				int nMax=100,nMin=0;
				GetRange(nMin,nMax);
				int newPos=GetPos()+nDelta;
				if (nfunc==12)
				{
					if (newPos>nMax) newPos=nMax;
					if (newPos<nMin) newPos=nMin;
				}
				else
					newPos=((newPos-nMin)%(nMax-nMin+1))+nMin;

				SetPos(newPos);
			}
		}
		break;
	case 14: /*SetMarquee*/
		{
			int retint=::SendMessage(m_hWnd,PBM_SETMARQUEE,atoi(pos),atoi(ExtractField(pos,2,",")));
			if (oStr) sprintf(oStr,"%d",retint);
		}
		break;
	case 15: /*GetStep*/
		{
			int retint=::SendMessage(m_hWnd,PBM_GETSTEP,0,0);
			if (oStr) sprintf(oStr,"%d",retint);
		}
		break;
	case 16: /*GetBKColor*/
		{
			int retint=::SendMessage(m_hWnd,PBM_GETBKCOLOR,0,0);
			if (oStr) sprintf(oStr,"%d\x7F%d\x7F%d",GetRValue(retint),GetGValue(retint),GetBValue(retint));
		}
		break;
	case 17: /*GetBarColor*/
		{
			int retint=::SendMessage(m_hWnd,PBM_GETBARCOLOR,0,0);
			if (oStr) sprintf(oStr,"%d\x7F%d\x7F%d",GetRValue(retint),GetGValue(retint),GetBValue(retint));
		}
		break;
	case 18: /*SetState State*/
		{
			int retint=::SendMessage(m_hWnd,PBM_SETSTATE,atoi(pos),0);
			if (oStr) sprintf(oStr,"%d",retint);
		}
		break;
	case 19: /*GetState*/
		{
			int retint=::SendMessage(m_hWnd,PBM_GETSTATE,0,0);
			if (oStr) sprintf(oStr,"%d",retint);
		}
		break;
	default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
	}
	return nfunc;
}


UINT GPProgress::GPSetProperty(char *iStr)
{
	char *iValue=new char [(int)strlen(iStr)+5];
	strcpy(iValue,iStr);
	UINT ret=1,i;
	char *pos=strchr(iValue,'=');

	if (pos!=NULL && m_hWnd)
	{
		char *prop[]={"ADDSTYLE", "DELSTYLE","STYLE", };
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
					// CProgress specif
					for(i=0;i<N_PROGRESS_STYLES;i++)
						if (strstr(pos,aProgressStyleName[i])!=NULL)
						{
							InvFlg++;
							switch(propnum)
							{
							case 2: /* STYLE*/
							case 0: /* ADDSTYLE*/	ModifyStyle(0,aProgressStyleUINT[i]);break;
							case 1: /* DELSTYLE*/	ModifyStyle(aProgressStyleUINT[i],0);break;
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

void GPProgress::OnOutofmemory(NMHDR* pNMHDR, LRESULT* pResult)
{
	{
		char tmp[250];
		sprintf(tmp,"%X\x7F%ld\x7F%ld",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code);
		if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnOutofmemory",tmp);
	}

	*pResult = 0;
}

void GPProgress::ParentNotify(UINT message, LPARAM lParam)
{
	char txt[100];
	if (message==WM_CREATE || message==WM_DESTROY)
		sprintf(txt,"%d\x7F%d\x7F%X",message/0x10000,(message&0xFFFF),lParam/0x10000);
	else
		sprintf(txt,"%d\x7F%d\x7F%d\x7F%d",message/0x10000,(message&0xFFFF),lParam/0x10000,(lParam&0xFFFF));
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"ParentNotify",txt);
}

LRESULT GPProgress::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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

	LRESULT lpr;
	if (message==WM_SETCURSOR && GPC.m_bWaitCursor) lpr=FALSE;
	else lpr=CProgressCtrl::WindowProc(message, wParam, lParam);

	return lpr;
}

BOOL GPProgress::PreTranslateMessage(MSG* pMsg)
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


	return CProgressCtrl::PreTranslateMessage(pMsg);
}

void GPProgress::OnClose()
{
	if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClose","");
//	CProgressCtrl::OnClose();
}

void GPProgress::OnSizing(UINT fwSide, LPRECT pRect)
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

	if (EnableSz) CProgressCtrl::OnSizing(fwSide, pRect);

	GetParent()->SendMessage(GPN_UPDATESIZE);

}

void GPProgress::OnDragMouseHover()
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
		GetRange(MinPos,MaxPOs);
		CRect re;
		GetClientRect(&re);
		int Width=re.Width();
		int mPos=point.x;
		if ((GetStyle()&PBS_VERTICAL)==PBS_VERTICAL)
		{
			Width=re.Height();
			mPos=point.y;
		}
		CString tmps;
		tmps.Format("%d\x07%d\x07%d\x07%d",MinPos,MaxPOs,GetPos(),(int)((MaxPOs-MinPos)/Width*mPos));

		referGPU[UnitId&0xFFFF]->SendDropHoverEvent(tmps,&GPC.m_DragDrop,&point);
	}
}

void GPProgress::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
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
		GetRange(MinPos,MaxPOs);
		CRect re;
		GetClientRect(&re);
		int Width=re.Width();
		int mPos=point->x;
		if ((GetStyle()&PBS_VERTICAL)==PBS_VERTICAL)
		{
			Width=re.Height();
			mPos=point->y;
		}
		CString tmps;
		tmps.Format("%d\x07%d\x07%d\x07%d",MinPos,MaxPOs,GetPos(),(int)((MaxPOs-MinPos)/Width*mPos));
		referGPU[UnitId&0xFFFF]->SendDropMoveEvent(tmps,pDrDrStruct,point);

		if (mDrop)
			::SetTimer (pDrDrStruct->hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nDelayInterval, NULL);
	}
}

void GPProgress::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
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
		GetRange(MinPos,MaxPOs);
		CRect re;
		GetClientRect(&re);
		int Width=re.Width();
		int mPos=point->x;
		if ((GetStyle()&PBS_VERTICAL)==PBS_VERTICAL)
		{
			Width=re.Height();
			mPos=point->y;
		}
		CString tmps;
		tmps.Format("%d\x07%d\x07%d\x07%d",MinPos,MaxPOs,GetPos(),(int)((MaxPOs-MinPos)/Width*mPos));

		referGPU[UnitId&0xFFFF]->SendDropEvent(tmps,pDrDrStruct,point);
	}
}

DWORD GPProgress::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	pDrDrStruct->pImageList->DragShowNolock(FALSE);
	CRect re;
	GetClientRect(&re);
	if ((GetStyle()&PBS_VERTICAL)==PBS_VERTICAL)
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

LRESULT GPProgress::OnNcHitTest(CPoint point)
{
	LRESULT ret=CProgressCtrl::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

#include "GP_TermDoc.h"

void GPProgress::OnKillFocus(CWnd* pNewWnd)
{
	CProgressCtrl::OnKillFocus(pNewWnd);
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

void GPProgress::OnSetFocus(CWnd* pOldWnd)
{
	CProgressCtrl::OnSetFocus(pOldWnd);
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

void GPProgress::OnSize(UINT nType, int cx, int cy)
{
	CProgressCtrl::OnSize(nType, cx, cy);

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
	}
}

HBRUSH GPProgress::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CProgressCtrl::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}

int GPProgress::AddChar(char iChar, DWORD iFlags)
{
	int ret=0;
	if (iChar)
	{
		if (iChar<'0' || iChar>'9')
		{
			if (m_csDOString!="") SetPos(atoi(m_csDOString));
			m_csDOString="";
		}
		else 
		if (iChar==8 && (iFlags&0x4))
		{
			int pos=m_csDOString.GetLength();
			if (pos) m_csDOString=m_csDOString.Left(pos-1);
		}
		else m_csDOString+=iChar;

		ret=GetPos();
	}
	return ret;
}
