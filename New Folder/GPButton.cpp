// GPButton.cpp : implementation file
//

#include "stdafx.h"
#include "GP_term.h"
#include "GPButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPButton
const UINT GPButton::uNMethods=15;
const char *GPButton::cArrMethods[]={
		"GetState","SetState","GetCheck","SetCheck","GetButtonStyle",
		"UpdateGroup","BtnSetBitmap","BtnSetIcon","MultiClick","SetAutoClick",
		"SetStateText","GetStateText","Click","LoadBitmap","SetDontClick",
		"","","", "", "", 
	};
const char *GPButton::cArrMethodsParams[]={
		"","nState","","nCheck","",
		"","nImage, ILName","nImage, ILName","bMode","msDelay",
		"StateText","","","useIcm,R,G,B;FileName","bClick",
		"","","", "", "", 
	};


GPButton::GPButton(UINT iUnitId)
{
	hbmtodelete=NULL;
	hicontodelete=NULL;
	m_LastStateCheck=0;
	m_uAutoClickDelay=0;
	m_bEnableMultiClick=FALSE;
	m_EnableClick=TRUE;
	referGPU=NULL;
	UnitId=iUnitId;
	OldState=0;
	m_StateText="";
}

GPButton::~GPButton()
{
	if (hbmtodelete) ::DeleteObject(hbmtodelete);
	if (hicontodelete) ::DestroyIcon(hicontodelete);
}

BEGIN_MESSAGE_MAP(GPButton, CButton)
	//{{AFX_MSG_MAP(GPButton)
	ON_WM_PARENTNOTIFY_REFLECT()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_SIZING()
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_NCHITTEST()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPButton message handlers
UINT GPButton::DoMethod(const char *iStr, char *oStr)
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
		{
			tmpUINT=GetButtonStyle();
			*oStr=0;
			char brk[5]={127,0,};
			char *lpstl[25]={"_AUTOCHECKBOX|","_AUTORADIOBUTTON|","_AUTO3STATE|","_CHECKBOX|","_DEFPUSHBUTTON|","_GROUPBOX|","_LEFTTEXT|","_OWNERDRAW|","_PUSHBUTTON|","_RADIOBUTTON|","_3STATE|","_TEXT|","_ICON|","_BITMAP|","_LEFT|","_RIGHT|","_CENTER|","_TOP|","_BOTTOM|","_VCENTER|","_PUSHLIKE|","_MULTILINE|","_NOTIFY|","_FLAT|","_RIGHTBUTTON|",};
			UINT  uistl[25]={BS_AUTOCHECKBOX,BS_AUTORADIOBUTTON,BS_AUTO3STATE,BS_CHECKBOX,BS_DEFPUSHBUTTON,BS_GROUPBOX,BS_LEFTTEXT,BS_OWNERDRAW,BS_PUSHBUTTON,BS_RADIOBUTTON,BS_3STATE,BS_TEXT,BS_ICON,BS_BITMAP,BS_LEFT,BS_RIGHT,BS_CENTER,BS_TOP,BS_BOTTOM,BS_VCENTER,BS_PUSHLIKE,BS_MULTILINE,BS_NOTIFY,BS_FLAT,BS_RIGHTBUTTON,};
			int i;
			for(i=0;i<25;i++)
				if ((tmpUINT&uistl[i])==uistl[i])
				{
					if (*oStr!=0) strcat(oStr,brk);
					strcat(oStr,lpstl[i]);
				}
		}
		break;
	case 5: /*UpdateGroup*/
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
		{
				referGPU[UnitId&0xFFFF]->UpdateGroup(GetState()&0x3,GetStyle());
				referGPU[UnitId&0xFFFF]->UpdateGroup((GetState()&0x4)+0x1000,GetStyle());
				referGPU[UnitId&0xFFFF]->UpdateGroup((GetState()&0x8)+0x1000,GetStyle());
		}
		break;
	case 6: /*BtnSetBitmap*/
		{
			HBITMAP hbmold=GetBitmap();
			const char *name=strchr(pos,',');
			if (name==NULL) name="MISCL";
			else name++;
			GPImageList *SMainIl;
			int ImgLId=atoi(pos);
			HBITMAP hbm=NULL;
			int imgnum=atoi(pos);

			if ((ImgLId=GPC.GetImageListId(name))>=0 
				&& (SMainIl=&(GPC.a_GPImageList[ImgLId]))!=NULL
				&& SMainIl->m_IL.GetImageCount()>imgnum)
						hbm=SMainIl->CreateBitmap(m_hWnd, imgnum);
			SetBitmap(hbmtodelete=hbm);
			if (hbmold) DeleteObject(hbmold);
		}
		break;
	case 7: /*BtnSetIcon*/
		{
			const char *name=strchr(pos,',');
			if (name==NULL) name="MISCL";
			else name++;
			GPImageList *SMainIl;
			int ImgLId;
			if ((ImgLId=GPC.GetImageListId(name))>=0 &&(SMainIl=&(GPC.a_GPImageList[ImgLId]))!=NULL)
			DestroyIcon(SetIcon(hicontodelete=(HICON)	SMainIl->m_IL.ExtractIcon(atoi(pos))));
		}
		break;
	case 8: /*MultiClick*/ m_bEnableMultiClick=atoi(pos);	break;
	case 9: /*SetAutoClick*/ m_uAutoClickDelay=atoi(pos);	break;
	case 10: /*SetStateText*/ m_StateText=pos;	break;
	case 11: /*GetStateText*/
		if (oStr) strcpy(oStr,m_StateText);
		break;
	case 12: /*Click*/ 		SendMessage(BM_CLICK,0,0);		break;
	case 13: /*LoadBitmap*/
		if (*pos)
		{
			SIZE bmpSize={0};
			BSTR m_fName=ExtractField(pos,2,";").AllocSysString();
			Bitmap img(m_fName,atoi(pos));
			SysFreeString(m_fName);
			HBITMAP hbmp=NULL;
			Color m_Color(atoi(ExtractField(pos,2,",")),atoi(ExtractField(pos,3,",")),atoi(ExtractField(pos,4,",")));
			img.GetHBITMAP(m_Color,&hbmp);
			if (hbmp)
			{
				GetBitmapDimensionEx(hbmp,&bmpSize);
				SetBitmap(hbmp);
				DeleteObject(hbmp);
			}
			if (oStr) sprintf(oStr,"%d\x7F%d",bmpSize.cx,bmpSize.cy);
		}
		break;
	case 14: /*SetDontClick*/
		SendMessage(BM_SETDONTCLICK,atoi(pos),0);
		break;

	default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
	}
	return nfunc;
}

UINT GPButton::GPSetProperty(char *iStr)
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
					char *postmp=strstr(pos,"&U");

					if (postmp!=NULL)
					{
						UINT es=GetButtonStyle();
						UINT tmpstl=0;
						m_LastScanf=sscanf(postmp,"&U%X",&tmpstl);
						switch(propnum)
						{
						case 1: /* ADDSTYLE*/
							if (tmpstl&BS_TYPEMASK) SetButtonStyle(tmpstl&BS_TYPEMASK,TRUE);
							else					ModifyStyle(0,(es|tmpstl)&(0xFFFF^BS_TYPEMASK),TRUE);
							break;
						case 3: /* STYLE*/
							SetButtonStyle(tmpstl&BS_TYPEMASK,TRUE);
							ModifyStyle(0xFFFF,tmpstl&(0xFFFF^BS_TYPEMASK),TRUE);
							break;
						case 2: /* DELSTYLE*/
							if (tmpstl&BS_TYPEMASK) SetButtonStyle(0);
							else					ModifyStyle((es|tmpstl)&(0xFFFF^BS_TYPEMASK),0,TRUE);

							break;
						}
						Invalidate();
					}
					else
					{
						strcat(pos,"|");
						// BUTTON specif
						switch(propnum)
						{
						case 3: /* STYLE*/
							ModifyStyle(0xFFFF,0,TRUE);
						case 1: /* ADDSTYLE*/
							for(i=0;i<N_BUTTON_STYLES;i++)
								if (strstr(pos,aButtonStyleName[i])!=NULL)
								{
									if ((aButtonStyleUINT[i]&BS_TYPEMASK))
										SetButtonStyle(aButtonStyleUINT[i],TRUE);
									else
										ModifyStyle(0,aButtonStyleUINT[i]&(0xFFFF^BS_TYPEMASK),TRUE);
								}
							break;
						case 2: /* DELSTYLE*/
							for(i=0;i<N_BUTTON_STYLES;i++)
								if (strstr(pos,aButtonStyleName[i])!=NULL)
								{
									if ((aButtonStyleUINT[i]&BS_TYPEMASK))	SetButtonStyle(0,TRUE);
									else									ModifyStyle(aButtonStyleUINT[i]&(0xFFFF^BS_TYPEMASK),0,TRUE);
								}
							break;
						}
						Invalidate();
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

void GPButton::ParentNotify(UINT message, LPARAM lParam)
{
	char txt[100];
	if (message==WM_CREATE || message==WM_DESTROY)
		sprintf(txt,"%d\x7F%d\x7F%X",message/0x10000,(message&0xFFFF),lParam/0x10000);
	else
		sprintf(txt,"%d\x7F%d\x7F%d\x7F%d",message/0x10000,(message&0xFFFF),lParam/0x10000,(lParam&0xFFFF));
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"ParentNotify",txt);
}

LRESULT GPButton::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		referGPU[UnitId&0xFFFF]->m_CurMessage.message=message;
		referGPU[UnitId&0xFFFF]->m_CurMessage.wParam=wParam;
		referGPU[UnitId&0xFFFF]->m_CurMessage.lParam=lParam;
		if (referGPU[UnitId&0xFFFF]->DefWindowProc(message, wParam, lParam)) return 0;
	}

	if (message==WM_ERASEBKGND)
	{

		HWND ghWnd=::GetParent(m_hWnd);
		if (ghWnd && (::GetWindowLong(m_hWnd,GWL_STYLE)&BS_GROUPBOX)==BS_GROUPBOX && (::GetWindowLong(ghWnd,GWL_STYLE)&WS_CLIPCHILDREN)==WS_CLIPCHILDREN)
		{
			HBRUSH  hBrush, hOldBrush;
			HPEN    hPen, hOldPen;
			RECT    rect;
			HDC     hDC;
			hDC = ::GetDC(m_hWnd);

			hBrush = (HBRUSH)::GetClassWord(ghWnd, GCL_HBRBACKGROUND);
			hOldBrush = (HBRUSH)::SelectObject(hDC, hBrush);
			hPen = (HPEN)::CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BACKGROUND));
			hOldPen = (HPEN)::SelectObject(hDC, hPen);

			::GetClientRect(m_hWnd, &rect);
			::Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);

			::SelectObject(hDC, hOldPen);
			::SelectObject(hDC, hOldBrush);

			::DeleteObject(hPen);

			::ReleaseDC(m_hWnd, hDC);

			// Instruct Windows to paint the group box text and frame.
			::InvalidateRect(m_hWnd, NULL, FALSE);

			// Insert code here to instruct the contents of the group box
			// to repaint as well.

			return TRUE; // Background has been erased.
		}

	}
	if (message==GPM_SETAUTOSIZE)
		GetParent()->PostMessage(GPM_SETAUTOSIZE,wParam);

	if (message==GPN_UPDATESIZE) GetParent()->SendMessage(GPN_UPDATESIZE);
	if (message==GPM_CLIENTKILLFOCUS || message==GPM_CLIENTSETFOCUS)
	{
		PGPUNITINFO ui=(PGPUNITINFO)lParam;
		if (ui)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent
				(m_hWnd, UnitId,message==GPM_CLIENTSETFOCUS?"OnCSetFocus":"OnCKillFocus",GPUnit::UnitInfoToString2(ui,"\x7F"));
	}
	else
	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)
	{
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

	LRESULT lr;
	if (message==WM_SETCURSOR && GPC.m_bWaitCursor) lr=FALSE;
	else lr=CButton::WindowProc(message, wParam, lParam);


	if (message==BM_SETCHECK || message==BM_SETSTATE)
	{
//#define BM_GETCHECK        0x00F0
//#define BM_GETSTATE        0x00F2
//#define BM_SETSTYLE        0x00F4
//#define BM_CLICK           0x00F5
		if (referGPU!=NULL)// && (m_LastStateCheck&0xFF)!=(wParam&0xFF))
		{
			m_LastStateCheck=wParam;
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

BOOL GPButton::PreTranslateMessage(MSG* pMsg)
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

	return CButton::PreTranslateMessage(pMsg);
}

void GPButton::OnTimer(UINT nIDEvent)
{
	if (nIDEvent==CLICK_TIMER_ID)
	{
		KillTimer(nIDEvent);
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

void GPButton::OnClose()
{
	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClose","");
//	CButton::OnClose();
}

void GPButton::OnSizing(UINT fwSide, LPRECT pRect)
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


HBRUSH GPButton::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CButton::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}

void GPButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_uAutoClickDelay && referGPU!=NULL)
		SetTimer(AUTOCLICK_TIMER_ID,m_uAutoClickDelay,0);

	CButton::OnLButtonDown(nFlags, point);
}

void GPButton::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (m_uAutoClickDelay && referGPU!=NULL)
	{
		SetTimer(RAUTOCLICK_TIMER_ID,m_uAutoClickDelay,0);
		SetCapture();
	}

	CButton::OnRButtonDown(nFlags, point);
}

void GPButton::OnRButtonUp(UINT nFlags, CPoint point)
{
	KillTimer(RAUTOCLICK_TIMER_ID);
	CButton::OnRButtonUp(nFlags, point);
}

void GPButton::OnDragMouseHover()
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

void GPButton::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
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
		::SetCursor(bDropTarget == 0xFFFFFFFF ?
			AfxGetApp()->LoadStandardCursor(IDC_NO)
			:(HCURSOR) ::GetClassLong(m_hWnd, GCL_HCURSOR));
		referGPU[UnitId&0xFFFF]->SendDropMoveEvent("",pDrDrStruct,point);
		// Set a timer if the cursor is at the top or bottom of the window, or if it's over a collapsed item.
		if (mDrop)
				::SetTimer(pDrDrStruct->hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nDelayInterval, NULL);
	}
}

void GPButton::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && referGPU)
	{
		SetState(FALSE);
		::ScreenToClient(m_hWnd,point);
		referGPU[UnitId&0xFFFF]->SendDropEvent("",pDrDrStruct,point);
	}
}

DWORD GPButton::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	GPC.m_DragDrop.pImageList->DragShowNolock(FALSE);
		SetState(TRUE);
	GPC.m_DragDrop.pImageList->DragShowNolock(TRUE);
	return 0;
}

LRESULT GPButton::OnNcHitTest(CPoint point)
{
	LRESULT ret=CButton::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

#include "GP_TermDoc.h"

void GPButton::OnKillFocus(CWnd* pNewWnd)
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

void GPButton::OnSetFocus(CWnd* pOldWnd)
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

void GPButton::OnSize(UINT nType, int cx, int cy)
{
	CButton::OnSize(nType, cx, cy);

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
	}
}

BOOL GPButton::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
	if (referGPU!=NULL)
	{
		switch(message)
		{
		case WM_COMMAND:
			{
				switch(HIWORD(wParam))
				{
				case BN_CLICKED:
					if (m_EnableClick)
					{
						m_EnableClick=FALSE;
						char tmpstate[10];
						sprintf(tmpstate,"%d",GetState());
						referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClicked",tmpstate);
						if (m_bEnableMultiClick==FALSE) SetTimer(CLICK_TIMER_ID,CLICK_TIMER_DELAY,0);
						else m_EnableClick=TRUE;
					}
					break;
				case BN_DOUBLECLICKED:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDoubleclicked","");
					break;
				case BN_PAINT:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnPaint","");
					break;
				case BN_HILITE:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnHilite","");
					break;
				case BN_UNHILITE:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnUnhilite","");
					break;
				case BN_DISABLE:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDisable","");
					break;
				case BN_SETFOCUS:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSetFocus","");
					break;
				case BN_KILLFOCUS:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnKillFocus","");
					break;
				default:
//					TRACE("GPButton OnChildNotify WM_COMMAND %d\n",HIWORD(wParam));
					break;
				}
			}
			break;
		case WM_NOTIFY:
			{
//				TRACE("GPButton OnChildNotify WM_NOTIFY %d\n",HIWORD(wParam));
				break;
			}
		break;
		}
	}

	return CButton::OnChildNotify(message, wParam, lParam, pLResult);
}

