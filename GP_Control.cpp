// GP_Control.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GP_Control.h"
#include "GP_TermDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GP_Control
const UINT GP_Control::uNMethods=5;
const char *GP_Control::cArrMethods[]={
		"SendString",	"GetControlEvents",	"GetControlMethods",	"GetValue",	"SetValue",
//		"GetProp","PutProp","PutPropRef","DispMethod",
		"","","", "", "", 
	};
const char *GP_Control::cArrMethodsParams[]={
		"String","","","","","Value",
		"","","", "", "", 
		"","","", "", "", 
	};

const UINT GP_Control::uNTypes=42;
const char *GP_Control::cArrTypes[42]={
		"VT_EMPTY",		"VT_NULL",		"VT_I2",		"VT_I4",		"VT_R4",
		"VT_R8",		"VT_CY",		"VT_DATE",		"VT_BSTR",		"VT_DISPATCH",
		"VT_ERROR",		"VT_BOOL",		"VT_VARIANT",	"VT_DECIMAL",	"VT_RECORD",
		"VT_UNKNOWN",	"VT_I1",		"VT_UI1",		"VT_UI2",		"VT_UI4",
		"VT_INT",		"VT_UINT",		"VT_VOID",		"VT_HRESULT",	"VT_PTR",
		"VT_SAFEARRAY",	"VT_CARRAY",	"VT_USERDEFINED","VT_LPSTR",	"VT_LPWSTR",
		"VT_FILETIME",	"VT_BLOB",		"VT_STREAM",	"VT_STORAGE",	"VT_STREAMED_OBJECT",
		"VT_STORED_OBJECT","VT_BLOB_OBJECT","VT_CF",	"VT_CLSID",		"VT_VECTOR",
		"VT_ARRAY",		"VT_BYREF",
	};
const UINT GP_Control::uArrTypes[42]={
		VT_EMPTY,		VT_NULL,		VT_I2,			VT_I4,			VT_R4,
		VT_R8,			VT_CY,			VT_DATE,		VT_BSTR,		VT_DISPATCH,
		VT_ERROR,		VT_BOOL,		VT_VARIANT,		VT_DECIMAL,		VT_RECORD,
		VT_UNKNOWN,		VT_I1,			VT_UI1,			VT_UI2,			VT_UI4,
		VT_INT,			VT_UINT,		VT_VOID,		VT_HRESULT,		VT_PTR,
		VT_SAFEARRAY,	VT_CARRAY,		VT_USERDEFINED,	VT_LPSTR,		VT_LPWSTR,
		VT_FILETIME,	VT_BLOB,		VT_STREAM,		VT_STORAGE,		VT_STREAMED_OBJECT,
		VT_STORED_OBJECT,VT_BLOB_OBJECT,VT_CF,			VT_CLSID,		VT_VECTOR,
		VT_ARRAY,		VT_BYREF,
	};


GP_Control::GP_Control(UINT iUnitId)
{
	tmpWnd=NULL;
	referGPU=NULL;
	UnitId=iUnitId;
}

GP_Control::~GP_Control()
{
	if (tmpWnd) delete[] tmpWnd;
	tmpWnd=NULL;
}

BEGIN_MESSAGE_MAP(GP_Control, CWnd)
	//{{AFX_MSG_MAP(GP_Control)
	ON_WM_NCHITTEST()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// GP_Control message handlers

UINT GP_Control::DoMethod(const char *iStr, char *oStr)
{
	char met[250];
	int retint=-123456;
	strncpy(met,iStr?iStr:"",245);
	met[245]=0;
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc=0;

	try
	{
		if (*met=='_')
		{
			nfunc=1000;
			AX_METHOD meth={0};
			CString MethName=met;
			CString MethParams=pos;
			CString MethResult="";

			meth.cbSize=sizeof(AX_METHOD);
			if (!oStr) meth.MethodFlags|=AX_FLAG_NORETURNVALUE;

			meth.MethodName=MethName.AllocSysString();
			meth.Parameters=MethParams.AllocSysString();
			meth.RetStr=MethResult.AllocSysString();

			::SendMessage(tmpWnd->m_hWnd,GPM_AX_DOMETHOD,nfunc,(LPARAM)(&meth));

			::SysFreeString(meth.MethodName);
			::SysFreeString(meth.Parameters);
			if (oStr) 
			{
				MethResult=meth.RetStr;
				strcpy(oStr,MethResult);
			}
			::SysFreeString(meth.RetStr);
		}
		else
		{
			if (*met>='0' && *met<='9') nfunc=atoi(met);
			else			for(nfunc=0;nfunc<uNMethods && _stricmp(met,cArrMethods[nfunc])!=0;nfunc++);

			switch(nfunc)
			{
			case 0: /*SendString*/
				retint=::SendMessage(tmpWnd->m_hWnd,GPM_AX_DATAFROMSERVER,(int)strlen(pos),(LPARAM)(pos));
				break;
			case 1: /*GetControlEvents*/
			case 2: /*GetControlMethods*/
				if (oStr)
				{
					AX_NAMES tmpNames;
					tmpNames.cbSize=sizeof(AX_NAMES);
					tmpNames.DescriptionsArr=::SysAllocString(L"");
					tmpNames.NamesArr=::SysAllocString(L"");
					retint=::SendMessage(tmpWnd->m_hWnd,nfunc!=1?GPM_AX_GETMETHODS:GPM_AX_GETEVENTS,0,(LPARAM)(&tmpNames));
					CString tmps=tmpNames.NamesArr;
					tmps.Replace(0x1,0x7F);
					strcpy(oStr,tmps);
					::SysFreeString(tmpNames.DescriptionsArr);
					::SysFreeString(tmpNames.NamesArr);
				}
				break;
			case 3: /*GetValue*/
				if (oStr) 
				{
					CString MethResult="";
					BSTR mbstrResult=MethResult.AllocSysString();
					::SendMessage(tmpWnd->m_hWnd,GPM_AX_GETVALUE,0,(LPARAM)(&mbstrResult));
					MethResult=mbstrResult;
					strcpy(oStr,MethResult);
					::SysFreeString(mbstrResult);
				}
				break;
			case 4: /*SetValue*/
				{
					CString MethResult=pos;
					BSTR mbstrResult=MethResult.AllocSysString();
					::SendMessage(tmpWnd->m_hWnd,GPM_AX_SETVALUE,0,(LPARAM)(&mbstrResult));
					::SysFreeString(mbstrResult);
				}
				break;

			default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
			}
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
		GPC.m_ErrReport.GPWriteErrorLog("GP_Control", "DoMethod",str );
		delete[] str;
	}

	if (oStr && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
	return nfunc;
}


//#define DLGC_WANTARROWS     0x0001      /* Control wants arrow keys         */
//#define DLGC_WANTTAB        0x0002      /* Control wants tab keys           */
//#define DLGC_WANTALLKEYS    0x0004      /* Control wants all keys           */
//#define DLGC_WANTMESSAGE    0x0004      /* Pass message to control          */
//#define DLGC_HASSETSEL      0x0008      /* Understands EM_SETSEL message    */
//#define DLGC_DEFPUSHBUTTON  0x0010      /* Default pushbutton               */
//#define DLGC_UNDEFPUSHBUTTON 0x0020     /* Non-default pushbutton           */
//#define DLGC_RADIOBUTTON    0x0040      /* Radio button                     */
//#define DLGC_WANTCHARS      0x0080      /* Want WM_CHAR messages            */
//#define DLGC_STATIC         0x0100      /* Static item: don't include       */
//#define DLGC_BUTTON         0x2000      /* Button item: can be checked      */

LRESULT GP_Control::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		referGPU[UnitId&0xFFFF]->m_CurMessage.message=message;
		referGPU[UnitId&0xFFFF]->m_CurMessage.wParam=wParam;
		referGPU[UnitId&0xFFFF]->m_CurMessage.lParam=lParam;
		if (referGPU[UnitId&0xFFFF]->DefWindowProc(message, wParam, lParam)) return 0;
	}

	if (tmpWnd && tmpWnd->m_hWnd)
	{

		if (message==WM_GETDLGCODE && m_dwLastMessage!=WM_GETDLGCODE) 
		{
			m_dwLastMessage=WM_GETDLGCODE;
		if (lParam)
			return PreTranslateMessage((MSG*)lParam);
		else
			return DLGC_WANTARROWS|DLGC_WANTTAB|DLGC_WANTALLKEYS|DLGC_HASSETSEL|DLGC_WANTCHARS;

		}
	}
	m_dwLastMessage=message;

	if (message==GPM_SETAUTOSIZE)
		GetParent()->PostMessage(GPM_SETAUTOSIZE,wParam);

	if (message==GPN_UPDATESIZE) GetParent()->SendMessage(GPN_UPDATESIZE);

	if (referGPU!=NULL && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG!=NULL)
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
		if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDragLeave","");
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

	case GPM_AX_FIREEVENT:
		if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG && lParam)
		{
			PAX_NAMES pNames=(PAX_NAMES )lParam;
			CString evName=pNames->NamesArr;
			CString evBody=pNames->DescriptionsArr;
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd,UnitId,evName,evBody);
		}
		break;
	case GPM_AX_DATATOSERVER:
		if (wParam && lParam)
		{
			AnsiToDos((BYTE *)lParam,1,wParam);
			m_Comm.GPSendBlock((char *)lParam,wParam);
		}
		break;
	case GPM_AX_GETGUIOBJECTSLIST:
		if (lParam && referGPU)
		{
			CString sOut;
			if (wParam)
				sOut=GPC.m_Document->GetUnitsInfo();
			else
				sOut=GPC.m_Document->GetUnitsInfo((UnitId/0x10000)&0xFF);
			::SysFreeString(*((BSTR *)lParam));
			*((BSTR *)lParam)=sOut.AllocSysString();
		}
		break;

	case GPM_AX_DOMETHOD:
	case GPM_AX_DATAFROMSERVER:
	case GPM_AX_GETMETHODS:
	case GPM_AX_GETEVENTS:
	case GPM_AX_ADDEVENT:
	case GPM_AX_DELEVENT:
	case GPM_AX_SETREGNAME:
	case GPM_AX_CHARFROMSERVER:
	case GPM_AX_DELALLEVENTS:
	case GPM_AX_SETWINDOWTEXT:
	case GPM_AX_GETWINDOWTEXT:
	case GPM_AX_GETWINDOWTEXTEX:
	case GPM_AX_SETWINDOWTEXTEX:
	case GPM_AX_SETDIRECTINPUT:
		return ::SendMessage(tmpWnd->m_hWnd,message,wParam,lParam);
		break;
	}

	LRESULT lpr;
	if (message==WM_SETCURSOR && GPC.m_bWaitCursor) lpr=FALSE;
	else
		lpr=CWnd::WindowProc(message, wParam, lParam);

	return lpr;
}

BOOL GP_Control::PreTranslateMessage(MSG* pMsg)
{
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		referGPU[UnitId&0xFFFF]->m_CurPreMessage=pMsg;
		if (!referGPU[UnitId&0xFFFF]->DefPreTranslateMessage(pMsg)) return 0;
	}

    if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST) 
	{
		if (pMsg->wParam>=VK_PRIOR  && pMsg->wParam<=VK_DOWN)
			return IsDialogMessage(pMsg); 

		::TranslateMessage(pMsg); 
		::DispatchMessage(pMsg); 
			return 1;
	} 
	return CWnd::PreTranslateMessage(pMsg);
}

void GP_Control::OnDragMouseHover()
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

void GP_Control::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
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
		// Set a timer if the cursor is at the top or bottom of the window, or if it's over a collapsed item.

		referGPU[UnitId&0xFFFF]->SendDropMoveEvent("",pDrDrStruct,point);

		if (mDrop)
			::SetTimer (pDrDrStruct->hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nDelayInterval, NULL);
	}
}

void GP_Control::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && referGPU)
	{
		::ScreenToClient(m_hWnd,point);
		referGPU[UnitId&0xFFFF]->SendDropEvent("",pDrDrStruct,point);
	}
}

DWORD GP_Control::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	return 0;
}

LRESULT GP_Control::OnNcHitTest(CPoint point)
{
	LRESULT ret=CWnd::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

#include "GP_TermDoc.h"

void GP_Control::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);
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

void GP_Control::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);
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

void GP_Control::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
		if (tmpWnd && tmpWnd->m_hWnd)
			tmpWnd->MoveWindow(0,0,cx,cy);

	}
}

HBRUSH GP_Control::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CWnd::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}


BOOL GP_Control::DestroyWindow() 
{
	if (tmpWnd)	tmpWnd->DestroyWindow();
	return CWnd::DestroyWindow();
}

int GP_Control::AddChar(char iChar, DWORD iFlags)
{
	int ret=0;
	::SendMessage(tmpWnd->m_hWnd,GPM_AX_CHARFROMSERVER,iChar,0);
	return ret;
}

UINT GP_Control::GPSetProperty(char *iStr)
{
	char *iValue=new char [(int)strlen(iStr)+5];
	strcpy(iValue,iStr);
	UINT ret=1;
	char *pos=strchr(iValue,'=');

	if (pos!=NULL && m_hWnd)
	{
		char *prop[]={ "ADDSTYLE", "DELSTYLE","STYLE", };
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
				ret=2;

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


void GP_Control::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}
