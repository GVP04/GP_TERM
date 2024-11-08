// GPSlider.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPSlider.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPSlider
const UINT GPSlider::uNMethods=38;
const char *GPSlider::cArrMethods[]={
/*00*/	"GetLineSize","SetLineSize","GetPageSize","SetPageSize","GetRangeMax",
/*05*/	"GetRangeMin","GetRange","SetRangeMin","SetRangeMax","SetRange",
/*10*/	"GetSelection","SetSelection","GetChannelRect","GetThumbRect","GetPos",
/*15*/	"SetPos","GetNumTics","GetTicArray","GetTic","GetTicPos",
/*20*/	"SetTic","SetTicFreq","GetBuddy","SetBuddy","SetTipSide",
/*25*/	"ClearSel","VerifyPos","ClearTics","UpdateGroup","SetSelStart",
/*30*/	"SetSelend","GetPTics","GetSelStart","GetSelEnd","SetThumbLength",
/*35*/	"GetThumbLength","SetUnicodeFormat","GetUnicodeFormat","","",
	"","","",
		"","","", "", "", 
	};
const char *GPSlider::cArrMethodsParams[]={
/*00*/	"","nLineSize","","nPageSize","",
/*05*/	"","","nRangeMin","nRangeMax","start,end",
/*10*/	"","start,end","","","",
/*15*/	"nPos","","Not Present","nTic","nTic",
/*20*/	"Tic1^Tic2^Tic3^....","nTicFreq","","nObject","TOP|LEFT|BOTTOM|RIGHT",
/*25*/	"","","","","lStart,fRedraw",
/*30*/	"lEnd,fRedraw","","","","ThumbLength",
/*35*/	"","bFormat","","","",
	"","","",
		"","","", "", "", 
	};

// TBM_SETTOOLTIPS         (WM_USER+29)
// TBM_GETTOOLTIPS         (WM_USER+30)

GPSlider::GPSlider(UINT iUnitId)
{
	referGPU=NULL;
	UnitId=iUnitId;
	m_LastHiPos=-123456;
}

GPSlider::~GPSlider()
{
}


BEGIN_MESSAGE_MAP(GPSlider, CSliderCtrl)
	//{{AFX_MSG_MAP(GPSlider)
	ON_NOTIFY_REFLECT(NM_OUTOFMEMORY, OnOutofmemory)
	ON_WM_PARENTNOTIFY_REFLECT()
	ON_NOTIFY_REFLECT(NM_RELEASEDCAPTURE, OnReleasedcapture)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomdraw)
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
// GPSlider message handlers

UINT GPSlider::DoMethod(const char *iStr, char *oStr)
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

		case  0: /*GetLineSize*/	retint=GetLineSize();			break;
		case  1: /*SetLineSize*/	retint=SetLineSize(atoipos);	break;
		case  2: /*GetPageSize*/	retint=GetPageSize();			break;
		case  3: /*SetPageSize*/	retint=SetPageSize(atoipos);	break;
		case  4: /*GetRangeMax*/	retint=GetRangeMax();			break;
		case  5: /*GetRangeMin*/	retint=GetRangeMin();			break;
		case  6: /*GetRange*/
			if (oStr!=NULL)
			{
				int start,end;
				GetRange(start,end);
				sprintf(oStr,"%d\x7F%d",start,end);
			}
			break;
		case  7: /*SetRangeMin*/	SetRangeMin(atoipos,TRUE);	break;
		case  8: /*SetRangeMax*/	SetRangeMax(atoipos,TRUE);	break;
		case  9: /*SetRange*/
			{
				int start,end; m_LastScanf=sscanf(pos,"%d,%d",&start,&end);
				SetRange(start,end,TRUE);
			}
			break;
		case 10: /*GetSelection*/
			if (oStr!=NULL)
			{
				int start,end;
				GetSelection(start,end);
				sprintf(oStr,"%d\x7F%d",start,end);
			}
			break;
		case 11: /*SetSelection*/
			{
				int start,end; m_LastScanf=sscanf(pos,"%d,%d",&start,&end);
				SetSelection(start,end);
			}
			break;
		case 12: /*GetChannelRect*/
		case 13: /*GetThumbRect*/
			if (oStr!=NULL)
			{
				CRect re;
				if (nfunc==12)	GetChannelRect(&re);
				else			GetThumbRect(&re);
				sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
			}
			break;
		case 14: /*GetPos*/		retint=GetPos();	break;
		case 15: /*SetPos*/
			SetPos(atoipos);
			if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
				DoMethod("UpdateGroup",NULL);
			break;
		case 16: /*GetNumTics*/	retint=GetNumTics();		break;
		case 18: /*GetTic*/		retint=GetTic(atoipos);		break;
		case 19: /*GetTicPos*/	retint=GetTicPos(atoipos);	break;
		case 20: /*SetTic*/
			{
				const char *pos2=pos;
				do
				{
					retint=SetTic(atoi(pos2));
					pos2=strchr(pos2,GPC.DelimiterIn1);
				}
				while(pos2++!=NULL);
			}
			break;
		case 21: /*SetTicFreq */ SetTicFreq(atoipos);	break;
		case 22: /*GetBuddy*/
			if (oStr!=NULL && referGPU!=NULL)
			{
				HWND tmp= GetBuddy( )->m_hWnd;
				int i;
				for(i=0;(UINT)i<(*referGPU)->m_NGPUNIT;i++)
					if (referGPU[i] &&  referGPU[i]->UnitHWND &&  referGPU[i]->UnitHWND==tmp) break;
				if ((UINT)i>=(*referGPU)->m_NGPUNIT) i=-1;
				retint=i;
			}
			break;
		case 23: /*SetBuddy*/
			{
				int bad=-1;
				int orient=0;
				HWND tmp=NULL;
				m_LastScanf=sscanf(pos,"%d,%d",&bad,&orient);
				if (bad>=0 && referGPU && (UINT)bad<(*referGPU)->m_NGPUNIT && referGPU[bad] && referGPU[bad]->UnitHWND)
					tmp=SetBuddy(CWnd::FromHandle(referGPU[bad]->UnitHWND),orient)->m_hWnd;
				retint=(int)tmp;
			}
			break;
		case 24: /*SetTipSide */
			{
				char *asize[4]={"_TOP","_LEFT","_BOTTOM","_RIGHT",};
				UINT asizeUINT[4]={TBTS_TOP,TBTS_LEFT,TBTS_BOTTOM,TBTS_RIGHT,};
				int i;
				for(i=0;i<4 && strstr(pos,asize[i])==NULL;i++);
				if (i==4) i=0;
				int ret=SetTipSide(asizeUINT[i]);
				for(i=0;i<4 && ret!=(int)asizeUINT[i];i++);
				if (i==4) i=0;
				if (oStr!=NULL) strcpy(oStr,asize[i]);
			}
			break;
		case 25: /*ClearSel*/	 ClearSel(TRUE);	break;


		#ifndef _VC80_UPGRADE
			case 26: /*VerifyPos*/
				VerifyPos();
				break;
		#endif


		case 27: /*ClearTics*/	 ClearTics(TRUE);	break;
		case 28: /*UpdateGroup*/
			if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
				referGPU[UnitId&0xFFFF]->UpdateGroup(GetPos(),GetStyle());
			break;
		case 29: /*SetSelStart*/
			{
				int lStart=0;
				int fRedraw=0;
				m_LastScanf=sscanf(pos,"%d,%d",&lStart,&fRedraw);
				SendMessage(TBM_SETSELSTART,(WPARAM)fRedraw, (LPARAM)lStart);
			}
			break;
		case 30: /*SetSelend*/
			{
				int lEnd=0;
				int fRedraw=0;
				m_LastScanf=sscanf(pos,"%d,%d",&lEnd,&fRedraw);
				SendMessage(TBM_SETSELEND,(WPARAM)fRedraw, (LPARAM)lEnd);
			}
			break;
		case 31: /*GetPTics*/
			if (oStr)
			{
				int nTics=SendMessage(TBM_GETNUMTICS,0,0);
				DWORD *pTics=(DWORD *)SendMessage(TBM_GETPTICS,0,0);
				if (pTics)
				{
					int p=0;
					int i;
					for(i=0;i<nTics;i++)
					{
						if (i>0) strcpy(oStr+(p++),"\x7F");
						p+=sprintf(oStr+p,"%d",pTics[i]);
					}
				}
				else *oStr=0;
			}
			break;
		case 32: /*GetSelStart*/
			retint=SendMessage(TBM_GETSELSTART,0,0);
			break;
		case 33: /*GetSelEnd*/
			retint=SendMessage(TBM_GETSELEND,0,0);
			break;
		case 34: /*SetThumbLength*/
			SendMessage(TBM_SETTHUMBLENGTH,(WPARAM)atoipos,0);
			break;
		case 35: /*GetThumbLength*/
			retint=SendMessage(TBM_GETTHUMBLENGTH,0,0);
			break;
		case 36: /*SetUnicodeFormat*/
			retint=SendMessage(TBM_SETUNICODEFORMAT, (WPARAM)atoipos,0);
			break;
		case 37: /*GetUnicodeFormat*/
			retint=SendMessage(TBM_GETUNICODEFORMAT,0,0);
			break;

		case 17: /*GetTicArray*/ // �� ����
		default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
		}
	}catch(...)
	{
		char *str=new char [200+(int)strlen(pos)];
		#ifdef RUS
			sprintf(str,"������ ���������� ������ %s %s",met,pos);
			MessageBox(str,"������ ������");
		#else
			sprintf(str,"Error execution of method %s %s",met,pos);
			MessageBox(str,"Error execution");
		#endif
		if (oStr!=NULL) strcpy(oStr,str);
		nfunc=0xFFFFFFFFL;
		GPC.m_ErrReport.GPWriteErrorLog("GPSlider", "DoMethod",iStr);
		delete[] str;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
	return nfunc;
}


UINT GPSlider::GPSetProperty(char *iStr)
{
	char *iValue=new char [(int)strlen(iStr)+5];
	strcpy(iValue,iStr);
	UINT ret=1,i;
	char *pos=strchr(iValue,'=');

	if (pos!=NULL && m_hWnd)
	{
		char *prop[]={"ADDSTYLE", "DELSTYLE","STYLE", "TEXT",};
		int propnum;
		*(pos++)=0;
		for(propnum=0;propnum<4 && _stricmp(prop[propnum],iValue)!=0;propnum++);
		if (propnum>=4) ret=2;
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
					for(i=0;i<N_SLIDER_STYLES;i++)
						if (strstr(pos,aSliderStyleName[i])!=NULL)
						{
							InvFlg++;
							switch(propnum)
							{
							case 2: /* STYLE*/
							case 0: /* ADDSTYLE*/	ModifyStyle(0,aSliderStyleUINT[i]);break;
							case 1: /* DELSTYLE*/	ModifyStyle(aSliderStyleUINT[i],0);break;
							}
						}
					if (InvFlg!=0) Invalidate();
				}
				break;
			case 3: // TEXT
					SetPos(atoi(pos)); break;
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

void GPSlider::OnOutofmemory(NMHDR* pNMHDR, LRESULT* pResult)
{
	char tmp[250];
	sprintf(tmp,"%X%c%ld%c%ld",(DWORD)pNMHDR->hwndFrom,127,pNMHDR->idFrom,127,pNMHDR->code);
	if (referGPU!=NULL)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnOutofmemory",tmp);

	*pResult = 0;
}

void GPSlider::ParentNotify(UINT message, LPARAM lParam)
{
	char txt[100];
	if (message==WM_CREATE || message==WM_DESTROY)
		sprintf(txt,"%d\x7F%d\x7F%X",message/0x10000,(message&0xFFFF),lParam/0x10000);
	else
		sprintf(txt,"%d\x7F%d\x7F%d\x7F%d",message/0x10000,(message&0xFFFF),lParam/0x10000,(lParam&0xFFFF));
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"ParentNotify",txt);
}

LRESULT GPSlider::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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
	else lpr=CSliderCtrl::WindowProc(message, wParam, lParam);

	return lpr;
}


void GPSlider::OnReleasedcapture(NMHDR* pNMHDR, LRESULT* pResult)
{
	char txt[100];
		sprintf(txt,"%d\x7F%d",GetPos(),GetTic(GetPos()));
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnReleasedcapture",txt);

	*pResult = 0;
}

void GPSlider::OnCustomdraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	char txt[100];
		sprintf(txt,"%d\x7F%d",GetPos(),GetTic(GetPos()));
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnCustomdraw",txt);
	*pResult = 0;
}

BOOL GPSlider::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
	if (message==WM_VSCROLL || message==WM_HSCROLL)
	{
		UINT tmppos=GetPos();
		if (LastPos!=tmppos)
		{
			LastPos=tmppos;
			char tmp[100];
			char *mess[9]={"OnLineup","OnLinedown","OnPageup","OnPagedown","OnThumbPosition","OnThumbTrack","OnTop","OnBottom","OnEndTrack",};
			sprintf(tmp,"%d\x7F%d\x7F%s",HIWORD(wParam),LOWORD(wParam),mess[(LOWORD(wParam))%9]);

			if (referGPU && referGPU[UnitId&0xFFFF])
			{
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,mess[(LOWORD(wParam))%9],tmp);
				if (referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
					DoMethod("UpdateGroup",NULL);
			}
		}
	}

	return CSliderCtrl::OnChildNotify(message, wParam, lParam, pLResult);
}

BOOL GPSlider::PreTranslateMessage(MSG* pMsg)
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

	return CSliderCtrl::PreTranslateMessage(pMsg);
}

void GPSlider::OnClose()
{
	if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClose","");
//	CSliderCtrl::OnClose();
}

void GPSlider::OnSizing(UINT fwSide, LPRECT pRect)
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

	if (EnableSz) CSliderCtrl::OnSizing(fwSide, pRect);

	GetParent()->SendMessage(GPN_UPDATESIZE);

}

void GPSlider::OnDragMouseHover()
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
		if ((GetStyle()&TBS_VERT)==TBS_VERT)
		{
			Width=re.Height();
			mPos=point.y;
		}
		CString tmps;
		tmps.Format("%d\x07%d\x07%d\x07%d",MinPos,MaxPOs,GetPos(),(int)((MaxPOs-MinPos)/Width*mPos));

		referGPU[UnitId&0xFFFF]->SendDropHoverEvent(tmps,&GPC.m_DragDrop,&point);
	}
}

void GPSlider::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
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
		if ((GetStyle()&TBS_VERT)==TBS_VERT)
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

void GPSlider::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
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
		if ((GetStyle()&TBS_VERT)==TBS_VERT)
		{
			Width=re.Height();
			mPos=point->y;
		}
		CString tmps;
		tmps.Format("%d\x07%d\x07%d\x07%d",MinPos,MaxPOs,GetPos(),(int)((MaxPOs-MinPos)/Width*mPos));

		referGPU[UnitId&0xFFFF]->SendDropEvent(tmps,pDrDrStruct,point);
	}
}

DWORD GPSlider::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	pDrDrStruct->pImageList->DragShowNolock(FALSE);
	CRect re;
	GetClientRect(&re);
	if ((GetStyle()&TBS_VERT)==TBS_VERT)
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

LRESULT GPSlider::OnNcHitTest(CPoint point)
{
	LRESULT ret=CSliderCtrl::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

#include "GP_TermDoc.h"

void GPSlider::OnKillFocus(CWnd* pNewWnd)
{
	CSliderCtrl::OnKillFocus(pNewWnd);
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

void GPSlider::OnSetFocus(CWnd* pOldWnd)
{
	CSliderCtrl::OnSetFocus(pOldWnd);
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

void GPSlider::OnSize(UINT nType, int cx, int cy)
{
	CSliderCtrl::OnSize(nType, cx, cy);

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
	}
}

HBRUSH GPSlider::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CSliderCtrl::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}
