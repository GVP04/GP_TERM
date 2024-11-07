// GPStatusBarCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPStatusBarCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPStatusBarCtrl
const UINT GPStatusBarCtrl::uNPaneStyle=6;
const char *GPStatusBarCtrl::aSBCPaneStyle[6]={"SBT_OWNERDRAW","SBT_NOBORDERS","SBT_POPOUT","SBT_RTLREADING","SBT_TOOLTIPS","SBT_NOTABPARSING"};
const UINT  GPStatusBarCtrl::uSBCPaneStyle[6]={SBT_OWNERDRAW,SBT_NOBORDERS,SBT_POPOUT,SBT_RTLREADING,SBT_TOOLTIPS,SBT_NOTABPARSING,};

const UINT GPStatusBarCtrl::uNMethods=17;
const char *GPStatusBarCtrl::cArrMethods[]={
		"UpdateGroup","SetText","GetText","GetTextLength","SetParts",
		"GetParts","GetBorders","SetMinHeight","SetSimple","GetRect",
		"IsSimple",	"GetTipText","SetTipText","SetBkColor","SetIconSB",
		"OptimizeSize","HitTest","","","",
		"","","", "", "", 
	};
const char *GPStatusBarCtrl::cArrMethodsParams[]={
		"","nPane,PaneStyle;Text","nPane","nPane","nWidths1,nWidths2,nWidths3,...",
		"","","nMinHeight","bSimple","nPane",
		"","nPane","nPane,Text","r,g,b","nPane,nImage,ILName",
		"nParts=-1","X","","","",
		"","","", "", "", 
	};



GPStatusBarCtrl::GPStatusBarCtrl(UINT iUnitId)
{
	referGPU=NULL;
	UnitId=iUnitId;
}

GPStatusBarCtrl::~GPStatusBarCtrl()
{
}


BEGIN_MESSAGE_MAP(GPStatusBarCtrl, CStatusBarCtrl)
	//{{AFX_MSG_MAP(GPStatusBarCtrl)
	ON_WM_PARENTNOTIFY()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_WM_NCHITTEST()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPStatusBarCtrl message handlers


UINT GPStatusBarCtrl::DoMethod(const char *iStr, char *oStr)
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
	int atoipos=atoi(pos);

	try
	{
		switch(nfunc)
		{
		case 0:  /*UpdateGroup*/
			if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
				referGPU[UnitId&0xFFFF]->UpdateGroup(-123456,GetStyle());
			break;
		case 1:  /*SetText*/
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				int nType=0;
				char *pText=strchr(pos333,';');
				if (pText==NULL) pText="";
				else *(pText++)=0;

				_strupr(pos333);

				int i;
				for(i=0;i<uNPaneStyle;i++)
					if (strstr(pos333,aSBCPaneStyle[i])!=NULL) nType|=uSBCPaneStyle[i];

				SetText(pText,atoipos,nType);
				delete[] pos333;
			}
			break;
		case 2:  /*GetText*/
		case 3:  /*GetTextLength*/
			if (oStr!=NULL)
			{
				int nType=0;
				if (nfunc==2) oStr[GetText(oStr,atoipos,&nType)]=0;
				else sprintf(oStr,"%d",GetTextLength(atoipos,&nType));
				strcat(oStr,"\x7F");

				int i;
				for(i=0;i<uNPaneStyle;i++)
					if ((nType&uSBCPaneStyle[i])==uSBCPaneStyle[i])
					{
						strcat(oStr,aSBCPaneStyle[i]);
						strcat(oStr,"|");
					}
			}
			break;
		case 4:  /*SetParts*/
			{
				int nParts,aWidths[255];
				for(nParts=0;nParts<255;nParts++)	aWidths[nParts]=-1;

				const char *pos2=pos;
				nParts=0;
				do
				{
					aWidths[nParts++]=atoi(pos2);
					pos2=strchr(pos2,',');
					if (pos2!=NULL) pos2++;
				}
				while(pos2!=NULL);
				retint=SetParts(nParts,aWidths);
			}
			break;
		case 5:  /*GetParts*/
			if (oStr!=NULL)
			{
				int nParts,aWidths[255];
				nParts=GetParts(254,aWidths);
				char *pos2=oStr;
				pos2+=sprintf(pos2,"%d",aWidths[0]);
				int i;
				for(i=1;i<nParts;i++)
					pos2+=sprintf(pos2,"\x7F%d",aWidths[i]);
			}
			break;
		case 6:  /*GetBorders*/
			if (oStr!=NULL)
			{
				int nHorz=0,nVert=0,nSpacing=0;
				GetBorders(nHorz,nVert,nSpacing);
				sprintf(oStr,"%d\x7F%d\x7F%d",nHorz,nVert,nSpacing);
			}
			break;
		case 7:  /*SetMinHeight*/	SetMinHeight(atoipos); break;
		case 8:  /*SetSimple*/		retint=SetSimple(atoipos); break;
		case 9:  /*GetRect*/
			if (oStr!=NULL)
			{
				CRect re;
				if (GetRect(atoipos,&re))
					sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
			}
			break;
		case 10: /*IsSimple*/		retint=IsSimple(); break;
		case 11: /*GetTipText*/
			if (oStr!=NULL)	strcpy(oStr,GetTipText(atoipos));
			break;
		case 12: /*SetTipText*/
			{
				const char *szTipText=strchr(pos,',');
				if (szTipText++==NULL) szTipText="";
				SetTipText(atoipos, szTipText);
			}
			break;
		case 13: /*SetBkColor*/
			{
				UINT r=0,g=0,b=0;
				m_LastScanf=sscanf(pos,"%d,%d,%d",&r,&g,&b);
				retint=SetBkColor(RGB(r,g,b));
			}
			break;
		case 14: /*SetIconSB*/
			{
				int nPane=0,nImage=0;
				char ImageName[500];
				m_LastScanf=sscanf(pos,"%d,%d,%s",&nPane,&nImage,ImageName);
				GPImageList *SMainIl;
				int ImgLId;
				if ((ImgLId=GPC.GetImageListId(ImageName))>=0 && (SMainIl=&(GPC.a_GPImageList[ImgLId]))!=NULL)
				retint=SetIcon(nPane,(HICON)SMainIl->m_IL.ExtractIcon(nImage));
			}
			break;
		case 15: /*OptimizeSize*/
			GPStatusBarCtrl::OptimizeSize(m_hWnd,*pos?atoi(pos):-1);
			if (oStr) DoMethod("GetParts",oStr);
			break;
		case 16: /*HitTest*/
			{
				POINT po={0};
				po.x=atoipos;
				retint=HitTest(m_hWnd,po);
			}

		default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL; break;
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
		GPC.m_ErrReport.GPWriteErrorLog("GPStatusBarCtrl", "DoMethod",iStr);
		delete[] str;
	}
		if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
		return nfunc;
}

UINT GPStatusBarCtrl::GPSetProperty(char *iStr)
{
	char *iValue=new char [(int)strlen(iStr)+5];
	strcpy(iValue,iStr);
	UINT ret=1,i;
	char *pos=strchr(iValue,'=');

	if (pos!=NULL && m_hWnd)
	{
		char *prop[]={ "TEXT", "ADDSTYLE", "DELSTYLE","STYLE", };
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
					// Static specif
					for(i=0;i<N_STATUSBARCTRL_STYLES;i++)
						if (strstr(pos,aStatusBarCtrlStyleName[i])!=NULL)
						{
							InvFlg++;
							switch(propnum)
							{
							case 3: /* STYLE*/
							case 1: /* ADDSTYLE*/	ModifyStyle(0,aStatusBarCtrlStyleUINT[i]);break;
							case 2: /* DELSTYLE*/	ModifyStyle(aStatusBarCtrlStyleUINT[i],0);break;
							}
						}

					char *postmp=strstr(pos,"&U");
					if (postmp!=NULL)
					{
						UINT tmpstl=0;
						m_LastScanf=sscanf(postmp,"&U%X",&tmpstl);
						InvFlg++;
						switch(propnum)
						{
						case 3: /* STYLE*/
						case 1: /* ADDSTYLE*/	ModifyStyle(0,tmpstl);	break;
						case 2: /* DELSTYLE*/	ModifyStyle(tmpstl,0);break;
						}
					}
					else
					for(i=0;i<N_COMCTRL_STYLES;i++)
						if (strstr(pos,aComCtrlStyleName[i])!=NULL)
						{
							InvFlg++;
							switch(propnum)
							{
							case 3: /* STYLE*/
							case 1: /* ADDSTYLE*/	ModifyStyle(0,aComCtrlStyleUINT[i]);break;
							case 2: /* DELSTYLE*/	ModifyStyle(aComCtrlStyleUINT[i],0);break;
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


void GPStatusBarCtrl::OnParentNotify(UINT message, LPARAM lParam)
{
	CStatusBarCtrl::OnParentNotify(message, lParam);
	char txt[100];
	if (message==WM_CREATE || message==WM_DESTROY)
		sprintf(txt,"%d\x7F%d\x7F%X",message/0x10000,(message&0xFFFF),lParam/0x10000);
	else
		sprintf(txt,"%d\x7F%d\x7F%d\x7F%d",message/0x10000,(message&0xFFFF),lParam/0x10000,(lParam&0xFFFF));
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"ParentNotify",txt);
}

HBRUSH GPStatusBarCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CStatusBarCtrl::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}

LRESULT GPStatusBarCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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

	LRESULT lpr;
	if (message==WM_SETCURSOR && GPC.m_bWaitCursor) lpr=FALSE;
	else lpr=CStatusBarCtrl::WindowProc(message, wParam, lParam);

	return lpr;
}

BOOL GPStatusBarCtrl::PreTranslateMessage(MSG* pMsg)
{
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		if (!referGPU[UnitId&0xFFFF]->DefPreTranslateMessage(pMsg)) return 0;
		referGPU[UnitId&0xFFFF]->m_CurPreMessage=pMsg;
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

	return CStatusBarCtrl::PreTranslateMessage(pMsg);
}

void GPStatusBarCtrl::OnClose()
{
	if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClose","");
//	CStatusBarCtrl::OnClose();
}

void GPStatusBarCtrl::OnDragMouseHover()
{
	if (referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(GPC.m_DragDrop.DragName)<0xFFFFFFFFL)
	{
		// Reset the timer.
		::KillTimer (GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);

		// Get the current cursor position and window height.
		DWORD dwPos = ::GetMessagePos ();
		CPoint point (LOWORD (dwPos), HIWORD (dwPos));
		ScreenToClient (&point);

		int mParts[255];
		int nParts=GetParts(250,mParts);
		int i;
		for(i=0;i<nParts && mParts[i]<point.x;i++);
		i=i>=nParts || mParts[0]==-1?-2:i;
		CString tmp;
		tmp.Format("%d\x07%s",i,(LPCSTR)GetText(i));

		referGPU[UnitId&0xFFFF]->SendDropHoverEvent(tmp,&GPC.m_DragDrop,&point);
	}
}

void GPStatusBarCtrl::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
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

		DWORD iItem=0xFFFFFFFF;
		BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
		// Highlight the drop target if the cursor is over an item.
		if (mDrop)
			iItem = HighlightDropTarget(pDrDrStruct, CPoint(*point));
		// Modify the cursor to provide visual feedback to the user. Note: It's important to do this AFTER the call to DragMove.
		::SetCursor (iItem == 0xFFFFFFFF ?
			AfxGetApp()->LoadStandardCursor (IDC_NO) :
			(HCURSOR) ::GetClassLong (m_hWnd, GCL_HCURSOR));

		int mParts[255];
		int nParts=GetParts(250,mParts);
		int i;
		for(i=0;i<nParts && mParts[i]<point->x;i++);
		i=(i>=nParts || mParts[0]==-1)?-2:i;
		CString tmp;
		tmp.Format("%d\x07%s",i,(LPCSTR)GetText(i));
		referGPU[UnitId&0xFFFF]->SendDropMoveEvent(tmp,pDrDrStruct,point);

		if (mDrop)
				::SetTimer (pDrDrStruct->hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nDelayInterval, NULL);
	}
}

void GPStatusBarCtrl::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && referGPU)
	{
		::ScreenToClient(m_hWnd,point);

		int mParts[255];
		int nParts=GetParts(250,mParts);
		int i;
		for(i=0;i<nParts && mParts[i]<point->x;i++);
		i=(i>=nParts || mParts[0]==-1)?-2:i;

		CString tmp;
		tmp.Format("%d\x07%s",i,(LPCSTR)GetText(i));

		referGPU[UnitId&0xFFFF]->SendDropEvent(tmp,pDrDrStruct,point);
	}
}

DWORD GPStatusBarCtrl::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	int parts[150];
	int nParts=GetParts(140,parts);
	int i;
	for(i=0;i<nParts && parts[i]<point.x;i++);

	return i>=nParts || parts[0]==-1?-2:i;
}

LRESULT GPStatusBarCtrl::OnNcHitTest(CPoint point)
{
	LRESULT ret=CStatusBarCtrl::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

#include "GP_TermDoc.h"

void GPStatusBarCtrl::OnKillFocus(CWnd* pNewWnd)
{
	CStatusBarCtrl::OnKillFocus(pNewWnd);
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

void GPStatusBarCtrl::OnSetFocus(CWnd* pOldWnd)
{
	CStatusBarCtrl::OnSetFocus(pOldWnd);
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


void GPStatusBarCtrl::OnSize(UINT nType, int cx, int cy)
{
	CStatusBarCtrl::OnSize(nType, cx, cy);

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
	}
}

void GPStatusBarCtrl::OptimizeSize(HWND iHWND, int nPart, UINT uFlag)
{
	HDC mdc=::GetDC(iHWND);
	if (mdc)
	{
		if (nPart>255) nPart=255;
		int parts[256];
		int nParts=::SendMessage(iHWND,SB_GETPARTS,nPart,(LPARAM)parts);

		if (nPart>nParts && nParts) nParts=nPart;
		if (nParts>0)
		{
			char * tmps=new char [1500];
			BOOL bUpdate=FALSE;
			int i;
			for(i=nParts-1;i>0;i--)
			{
				::SendMessage(iHWND,SB_GETTEXT,i,(LPARAM)tmps);
				if (uFlag || *tmps)
				{
					SIZE sz={0};
					::GetTextExtentPoint32(mdc,tmps,(int)strlen(tmps),&sz);
					HICON hIcon=NULL;
					if ((hIcon=(HICON)::SendMessage(iHWND,SB_GETICON,i,0)))
						sz.cx+=20;
					int delta=(parts[i]-parts[i-1])-sz.cx;
					if (delta!=0)
					{
						bUpdate=TRUE;
						int j;
						for(j=i-1;j>=0;j--)
							parts[j]+=delta;
					}
				}
			}
			if (bUpdate) ::SendMessage(iHWND,SB_SETPARTS,nParts,(LPARAM)parts);
			delete[] tmps;
		}
		::ReleaseDC(iHWND,mdc);
	}
}

void GPStatusBarCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CStatusBarCtrl::OnLButtonDblClk(nFlags, point);

}

void GPStatusBarCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	CStatusBarCtrl::OnLButtonUp(nFlags, point);
}

int GPStatusBarCtrl::HitTest(HWND iHWND, POINT po)
{
	int ret=-1;
	int parts[256];
	int nParts=::SendMessage(iHWND,SB_GETPARTS,255,(LPARAM)parts);
	if (nParts>0 && po.x>0)
	{
		int i;
		for(i=0;i<nParts && ret>=0;i++)
			if (po.x>parts[i]) ret=i;
	}
	return ret;
}

BOOL GPStatusBarCtrl::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
//	if (referGPU!=NULL)
	{
		switch(message)
		{
		case WM_COMMAND:
			{
//					TRACE("GPStatusBar OnChildNotify WM_COMMAND %d\n",HIWORD(wParam));
			}
			break;
		case WM_NOTIFY:
			{
				LPNMMOUSE lpn=(LPNMMOUSE)lParam;
				const char *msg=NULL;
				if (lpn)
				{
					switch(lpn->hdr.code)
					{
					case NM_CLICK:		msg="OnClick";		break;
					case NM_DBLCLK:		msg="OnDblClick";	break;
					case NM_RCLICK:		msg="OnRClick";		break;
					case NM_RDBLCLK:	msg="OnRDblClick";	break;
					case SBN_SIMPLEMODECHANGE:
						referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSimpleModeChange","");
						break;
					default:
	//					TRACE("GPStatusBar OnChildNotify WM_NOTIFY %d\n",HIWORD(wParam));
						break;
					break;
					}
					if (msg)
					{
						char tmps[250];
						sprintf(tmps,"%d\x7F%d\x7F%d\x7F%d\x7F%d",lpn->pt.x,lpn->pt.y,lpn->dwItemSpec,lpn->dwItemData,lpn->dwHitInfo);
						referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSimpleModeChange",tmps);
					}
				}
			}
		break;
		}
	}
	return CStatusBarCtrl::OnChildNotify(message, wParam, lParam, pLResult);
}
