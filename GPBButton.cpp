// GPBButton.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPBButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPBButton
const UINT GPBButton::uNMethods=14;
const char *GPBButton::cArrMethods[]={
		"GetState","SetState","GetCheck","SetCheck","GetButtonStyle",
		"LoadBitmaps","SizeToContent","UpdateGroup","MultiClick","SetAutoClick",
		"SetStateText","GetStateText","Click","SetDontClick","",
		"","","", "", "", 
	};
const char *GPBButton::cArrMethodsParams[]={
		"","nState","","nCheck","",
		"Name1,Name2,Name3,Name4","","","bMode","msDelay",
		"StateText","","","bClick","",
		"","","", "", "", 
	};

GPBButton::GPBButton(UINT iUnitId)
{
	m_uAutoClickDelay=0;
	m_bEnableMultiClick=FALSE;
	m_EnableClick=TRUE;
	referGPU=NULL;
	UnitId=iUnitId;
	OldState=0;
	MouseLBState=0;
	m_StateText="";
}

GPBButton::~GPBButton()
{
}


BEGIN_MESSAGE_MAP(GPBButton, CButton)
	//{{AFX_MSG_MAP(GPBButton)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_CONTROL_REFLECT(BN_DOUBLECLICKED, OnDoubleclicked)
	ON_CONTROL_REFLECT(BN_PAINT, OnPaintM)
	ON_CONTROL_REFLECT(BN_HILITE, OnHiliteM)
	ON_CONTROL_REFLECT(BN_UNHILITE, OnUnhiliteM)
	ON_CONTROL_REFLECT(BN_DISABLE, OnDisableM)
	ON_CONTROL_REFLECT(BN_SETFOCUS, OnSetFocusM)
	ON_CONTROL_REFLECT(BN_KILLFOCUS, OnKillFocusM)
	ON_WM_PARENTNOTIFY_REFLECT()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_SIZING()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_NCHITTEST()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPBButton message handlers
UINT GPBButton::DoMethod(const char *iStr, char *oStr)
{
	char met[150];
	UINT tmpUINT=0;
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
	case 0: /*GetState*/tmpUINT=GetState();
		if (oStr!=NULL)	sprintf(oStr,"%d\x7F%d\x7F%d",(tmpUINT%3),((tmpUINT/4)%2),tmpUINT/8);
		break;
	case 1: /*SetState*/
			SetState(atoi(pos));
			if (referGPU!=NULL && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
				DoMethod("UpdateGroup",NULL);
			break;
	case 2: /*GetCheck*/if (oStr!=NULL)	sprintf(oStr,"%d",GetCheck());	break;
	case 3: /*SetCheck*/
			SetCheck(atoi(pos));
			if (referGPU!=NULL && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
				DoMethod("UpdateGroup",NULL);
			break;
	case 4:	/*GetButtonStyle*/
		if (oStr!=NULL)
			GetObjStlStr(oStr, GetButtonStyle(), N_BUTTON_STYLES,  aButtonStyleName, aButtonStyleUINT, aButtonStyleMask);
		break;
	case 5: /*LoadBitmaps*/
			{
				char *postmpcc=new char [(int)strlen(pos)+10];
				strcpy(postmpcc,pos);
				char *pos2,*pos3=NULL,*pos4=NULL;
				if ((pos2=strchr(postmpcc,','))!=NULL)
				{
					*(pos2++)=0;
					if ((pos3=strchr(pos2,','))!=NULL)
					{
						*(pos3++)=0;
						if ((pos4=strchr(pos3,','))!=NULL) *(pos4++)=0;
					}
				}
				int retint=LoadBitmaps(postmpcc,pos2,pos3,pos4);
				if (oStr!=NULL)	sprintf(oStr,"%d",retint);
				delete[] postmpcc;
			}
			break;
	case 6: /*SizeToContent*/SizeToContent();					break;
	case 7: /*UpdateGroup*/
		if (referGPU!=NULL)
		{
			if (referGPU!=NULL && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
			{
				referGPU[UnitId&0xFFFF]->UpdateGroup(GetState()&0x3,GetStyle());
				referGPU[UnitId&0xFFFF]->UpdateGroup((GetState()&0x4)+0x1000,GetStyle());
				referGPU[UnitId&0xFFFF]->UpdateGroup((GetState()&0x8)+0x1000,GetStyle());
			}
		}
		break;
	case 8: /*MultiClick*/ m_bEnableMultiClick=atoi(pos);	break;
	case 9: /*SetAutoClick*/ m_uAutoClickDelay=atoi(pos);	break;
	case 10: /*SetStateText*/
		m_StateText=pos;
		break;
	case 11: /*GetStateText*/
		if (oStr) strcpy(oStr,m_StateText);
		break;
	case 12: /*Click*/ 		SendMessage(BM_CLICK,0,0);		break;
	case 13: /*SetDontClick*/
		SendMessage(BM_SETDONTCLICK,atoi(pos),0);
		break;
	default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
	}
	return nfunc;
}

UINT GPBButton::GPSetProperty(char *iStr)
{
	char *iValue=new char [(int)strlen(iStr)+5];
	strcpy(iValue,iStr);
	UINT ret=1,i;
	char *pos=strchr(iValue,'=');

	if (pos!=NULL && m_hWnd)
	{
		char *prop[]={"TEXT","ADDSTYLE", "DELSTYLE","STYLE",};
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
				{
					char *pos1=pos;
					char *pos2=pos;
					while(*pos2!=0)
						if (*pos2!='\\') *(pos1++)=*(pos2++);
						else
						{
							switch(pos2[1])
							{
							case '\\':	*(pos1++)=*pos2;	break;
							case 'n':	*(pos1++)='\n';		break;
							case 't':	*(pos1++)='\t';		break;
							case 'r':	*(pos1++)='\r';		break;
							default: break;
							}
							pos2++;
							if (*pos2!=0) pos2++;
						}

					*pos1=*pos2;
					SetWindowText(pos);
					Invalidate();
				}
					break;
			case 1: // ADDSTYLE
			case 2: // DELSTYLE
			case 3: // STYLE
				if (m_hWnd!=NULL)
				{
					ret=2;
					int InvFlg=0;
					char *postmp=strstr(pos,"&U");

					if (postmp!=NULL)
					{
						UINT es=GetButtonStyle();
						UINT tmpstl=0;
						m_LastScanf=sscanf(postmp,"&U%X",&tmpstl);
						InvFlg++;
						switch(propnum)
						{
						case 3: /* STYLE*/
						case 1: /* ADDSTYLE*/
							if ((tmpstl&BS_TYPEMASK)!=0)
								SetButtonStyle(es|tmpstl);
							ModifyStyle(0,tmpstl&0xFFFFFFF0L);
							break;
						case 2: /* DELSTYLE*/
							if ((tmpstl&BS_TYPEMASK)!=0)
								SetButtonStyle(((es|tmpstl)^tmpstl));
							ModifyStyle(tmpstl&0xFFFFFFF0L,0);
							break;
						}
						if (InvFlg!=0) Invalidate();
					}
					else
					{
						strcat(pos,"|");
						// BUTTON specif
						UINT Stl=0;
						switch(propnum)
						{
						case 1: /* ADDSTYLE*/
							Stl=GetButtonStyle();
						case 3: /* STYLE*/
							for(i=0;i<N_BUTTON_STYLES;i++)
							if (strstr(pos,aButtonStyleName[i])!=NULL)
							{
								InvFlg++;
								if (aButtonStyleMask[i]==BS_TYPEMASK) Stl|=aButtonStyleUINT[i];
								else ModifyStyle(0,aButtonStyleUINT[i]);
							}
							SetButtonStyle(Stl);
							break;
						case 2: /* DELSTYLE*/
							Stl=GetButtonStyle();
							for(i=0;i<N_BUTTON_STYLES;i++)
							if (strstr(pos,aButtonStyleName[i])!=NULL)
							{
								InvFlg++;
								if (aButtonStyleMask[i]==BS_TYPEMASK) Stl&=(0xFFFFFFFF^aButtonStyleUINT[i]);
								else ModifyStyle(aButtonStyleUINT[i],0);
							}
							SetButtonStyle(Stl);
							break;
						}
						if (InvFlg!=0)	Invalidate();
					}
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


void GPBButton::OnClicked()
{
	if (m_EnableClick && referGPU!=NULL)
	{
		m_EnableClick=FALSE;
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClicked","");
		if (m_bEnableMultiClick==FALSE) SetTimer(CLICK_TIMER_ID,CLICK_TIMER_DELAY,0);
		else m_EnableClick=TRUE;
	}
}

void GPBButton::OnDoubleclicked()
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDoubleclicked","");
}

void GPBButton::OnPaintM()
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnPaint","");
}

void GPBButton::OnHiliteM()
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnHilite","");
}

void GPBButton::OnUnhiliteM()
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnUnhilite","");
}

void GPBButton::OnDisableM()
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDisable","");
}

void GPBButton::OnSetFocusM()
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSetFocus","");
}

void GPBButton::OnKillFocusM()
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnKillFocus","");
}

void GPBButton::ParentNotify(UINT message, LPARAM lParam)
{
	char txt[100];
	if (message==WM_CREATE || message==WM_DESTROY)
		sprintf(txt,"%d\x7F%d\x7F%X",message/0x10000,(message&0xFFFF),lParam/0x10000);
	else
		sprintf(txt,"%d\x7F%d\x7F%d\x7F%d",message/0x10000,(message&0xFFFF),lParam/0x10000,(lParam&0xFFFF));
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"ParentNotify",txt);
}

LRESULT GPBButton::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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
		if ((ret=referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjMessage(m_hWnd, UnitId, message, wParam, lParam))>0) return ret;
		if (message==WM_KEYDOWN && referGPU!=NULL && referGPU[UnitId&0xFFFF]->UnitHotkey && this->m_hWnd!=NULL && IsWindowEnabled()==TRUE && IsWindowVisible()==TRUE)
				if ((ret=referGPU[UnitId&0xFFFF]->UnitHotkey->SendHotkeyMessage(message, wParam,lParam))>0) return ret;
		if (message==GPM_PROCHOTKEY)
		{
			if(referGPU[UnitId&0xFFFF]->UnitHotkey && (ret=referGPU[UnitId&0xFFFF]->UnitHotkey->SendHotkeyMessage(WM_KEYDOWN, wParam,lParam))>0) return ret;
			GetParent()->SendMessage(message, wParam,lParam);
		}
		else
		if  (message==WM_KEYDOWN)
			GetParent()->SendMessage(GPM_PROCHOTKEY, wParam,lParam);

	}

	switch(message)
	{
	case GPM_DRAGMOUSELEAVE:
		if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDragLeave","");
		GPC.m_DragDrop.pImageList->DragShowNolock(FALSE);
		SetState(FALSE);
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

	LRESULT lr=CBitmapButton::WindowProc(message, wParam, lParam);

	if (message==WM_LBUTTONDOWN) MouseLBState=1;

	if (message==WM_LBUTTONUP)	MouseLBState=0;


	if (message==BM_SETCHECK || message==BM_SETSTATE)
	{
//#define BM_GETCHECK        0x00F0
//#define BM_GETSTATE        0x00F2
//#define BM_SETSTYLE        0x00F4
//#define BM_CLICK           0x00F5

		if (referGPU!=NULL)
		{
			char st[500];*st=0;
			char *ms="";
			if ((wParam&BST_CHECKED)==BST_CHECKED)				{strcat(st,"_CHECKED");			ms="OnCheck";			}
			else
			if ((wParam&BST_UNCHECKED)==BST_UNCHECKED)  		{strcat(st,"_UNCHECKED");		ms="OnUncheck";			}
			if ((wParam&BST_INDETERMINATE)==BST_INDETERMINATE)	{strcat(st,"_INDETERMINATE");	ms="OnIndeterminate";	}
			if ((wParam&BST_PUSHED)==BST_PUSHED)  				{strcat(st,"_PUSHED");			ms="OnPush";			}
			if ((wParam&BST_FOCUS)==BST_FOCUS)  				{strcat(st,"_FOCUS");			ms="OnFocus";			}


			if (OldState!=wParam && message==BM_SETCHECK )
			{
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,ms,st);
				if (referGPU!=NULL && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
					DoMethod("UpdateGroup",NULL);
				OldState=wParam;
			}

			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnCheckChanged",st);
		}
	}

	if (message==WM_SIZEPARENT && referGPU!=NULL)
	{
		UINT SizStyle=referGPU[UnitId&0xFFFF]->SizStyle;
		if ((SizStyle&0xFFFF0000)!=0)
		{
			AFX_SIZEPARENTPARAMS* lpLayout =(AFX_SIZEPARENTPARAMS*)lParam;

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


	return lr;
}

BOOL GPBButton::PreTranslateMessage(MSG* pMsg)
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
				if ((ret=referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjMessage(m_hWnd, UnitId, pMsg->message, pMsg->wParam, pMsg->lParam))>0) return ret;
				if (pMsg->message==WM_KEYDOWN && referGPU!=NULL && referGPU[UnitId&0xFFFF]->UnitHotkey && this->m_hWnd!=NULL && IsWindowEnabled()==TRUE && IsWindowVisible()==TRUE)
						if ((ret=referGPU[UnitId&0xFFFF]->UnitHotkey->SendHotkeyMessage(pMsg->message, pMsg->wParam,pMsg->lParam))>0) return ret;
			}
		}
	}

	return CBitmapButton::PreTranslateMessage(pMsg);
}

void GPBButton::OnTimer(UINT nIDEvent)
{
	if (nIDEvent==CLICK_TIMER_ID)
	{
		KillTimer(nIDEvent);
		if (nIDEvent==CLICK_TIMER_ID)
				m_EnableClick=TRUE;
	}
	else
	if (nIDEvent==AUTOCLICK_TIMER_ID)
	{
		KillTimer(nIDEvent);
		if ((GetState( )&0x0004)==0x0004)
		{
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnAutoClick","");
			SetTimer(AUTOCLICK_TIMER_ID,m_uAutoClickDelay,0);
		}
	}
	else
	if (nIDEvent==RAUTOCLICK_TIMER_ID)
	{
		KillTimer(nIDEvent);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnRAutoClick","");
		SetTimer(RAUTOCLICK_TIMER_ID,m_uAutoClickDelay,0);
	}

	CButton::OnTimer(nIDEvent);
}

void GPBButton::OnClose()
{
	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClose","");
//	CButton::OnClose();
}

void GPBButton::OnSizing(UINT fwSide, LPRECT pRect)
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
			if ((SizStyle&GPUA_BOTTOM)!=GPUA_BOTTOM &&(SizStyle&GPUA_LEFT)!=GPUA_LEFT) EnableSz=FALSE;
			break;
		case WMSZ_BOTTOMRIGHT:
			if ((SizStyle&GPUA_BOTTOM)!=GPUA_BOTTOM &&(SizStyle&GPUA_RIGHT)!=GPUA_RIGHT) EnableSz=FALSE;
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
			if ((SizStyle&GPUA_LEFT)!=GPUA_LEFT &&(SizStyle&GPUA_TOP)!=GPUA_TOP) EnableSz=FALSE;
			break;
		case WMSZ_TOPRIGHT:
			if ((SizStyle&GPUA_RIGHT)!=GPUA_RIGHT &&(SizStyle&GPUA_TOP)!=GPUA_TOP) EnableSz=FALSE;
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

	if (EnableSz) CButton::OnSizing(fwSide, pRect);

	GetParent()->SendMessage(GPN_UPDATESIZE);

}

void GPBButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_uAutoClickDelay && referGPU!=NULL)
		SetTimer(AUTOCLICK_TIMER_ID,m_uAutoClickDelay,0);

	CButton::OnLButtonDown(nFlags, point);
}

void GPBButton::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (m_uAutoClickDelay && referGPU!=NULL)
	{
		SetTimer(RAUTOCLICK_TIMER_ID,m_uAutoClickDelay,0);
		SetCapture();
	}
	CButton::OnRButtonDown(nFlags, point);
}

void GPBButton::OnRButtonUp(UINT nFlags, CPoint point)
{
	KillTimer(RAUTOCLICK_TIMER_ID);
	CButton::OnRButtonUp(nFlags, point);
}

void GPBButton::OnDragMouseHover()
{
	if (referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(GPC.m_DragDrop.DragName)<0xFFFFFFFFL)
	{
		// Reset the timer.
		::SetTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nScrollInterval, NULL);

		// Get the current cursor position and window height.
		DWORD dwPos = ::GetMessagePos();
		CPoint point(LOWORD(dwPos), HIWORD(dwPos));
		ScreenToClient(&point);

		CRect rect;
		GetClientRect(rect);
		int cy = rect.Height();

		referGPU[UnitId&0xFFFF]->SendDropHoverEvent("",&GPC.m_DragDrop,&point);

		// Scroll the window if the cursor is near the top or bottom.
		if (point.y >= 0 && point.y <= referGPU[UnitId&0xFFFF]->m_nScrollMargin)
		{
			GPC.m_DragDrop.pImageList->DragShowNolock(FALSE);
			SendMessage(WM_VSCROLL, MAKEWPARAM(SB_LINEUP, 0), NULL);
			GPC.m_DragDrop.pImageList->DragShowNolock(TRUE);
			// Kill the timer if the window did not scroll, or redraw the drop target highlight if the window did scroll.
			if (GetScrollPos(SB_VERT))
				::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);
				else
					HighlightDropTarget(&GPC.m_DragDrop, point);
		}
		else
			if (point.y >= cy - referGPU[UnitId&0xFFFF]->m_nScrollMargin && point.y <= cy)
			{
				GPC.m_DragDrop.pImageList->DragShowNolock(FALSE);
				SendMessage(WM_VSCROLL, MAKEWPARAM(SB_LINEDOWN, 0), NULL);
				GPC.m_DragDrop.pImageList->DragShowNolock(TRUE);
				// Kill the timer if the window did not scroll, or redraw the drop target highlight if the window did scroll.
				if (GetScrollPos(SB_HORZ)) ::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);
				else
					HighlightDropTarget(&GPC.m_DragDrop, point);
			}
			else ::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);
	}
}

void GPBButton::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
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
		pDrDrStruct->pImageList->DragMove(CPoint(*point));

		DWORD bDropTarget=0xFFFFFFFF;
		BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
		// Highlight the drop target if the cursor is over an item.
		if (mDrop)
			bDropTarget = HighlightDropTarget(pDrDrStruct, CPoint(*point));
		// Modify the cursor to provide visual feedback to the user. Note: It's important to do this AFTER the call to DragMove.
		::SetCursor(bDropTarget== 0xFFFFFFFF ?
			AfxGetApp()->LoadStandardCursor(IDC_NO)
			:(HCURSOR) ::GetClassLong(m_hWnd, GCL_HCURSOR));
		// Set a timer if the cursor is at the top or bottom of the window, or if it's over a collapsed item.
		referGPU[UnitId&0xFFFF]->SendDropMoveEvent("",pDrDrStruct,point);
		if (mDrop)
				::SetTimer(pDrDrStruct->hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nDelayInterval, NULL);
	}
}

void GPBButton::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && referGPU)
	{
		SetState(FALSE);
		::ScreenToClient(m_hWnd,point);
		referGPU[UnitId&0xFFFF]->SendDropEvent("",pDrDrStruct,point);
	}
}

DWORD GPBButton::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	GPC.m_DragDrop.pImageList->DragShowNolock(FALSE);
		SetState(TRUE);
	GPC.m_DragDrop.pImageList->DragShowNolock(TRUE);
	return 0;
}


LRESULT GPBButton::OnNcHitTest(CPoint point)
{
	LRESULT ret=CBitmapButton::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

#include "GP_TermDoc.h"

void GPBButton::OnKillFocus(CWnd* pNewWnd)
{
	CButton::OnKillFocus(pNewWnd);
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

void GPBButton::OnSetFocus(CWnd* pOldWnd)
{
	CButton::OnSetFocus(pOldWnd);
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

void GPBButton::OnSize(UINT nType, int cx, int cy)
{
	CButton::OnSize(nType, cx, cy);

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
	}
}

HBRUSH GPBButton::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CBitmapButton::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}
