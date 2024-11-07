// GPTabCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPTabCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPTabCtrl
char *TabMaskName[5]={"_IMAGE","_PARAM","_RTLREADING","_STATE","_TEXT",};
UINT TabMaskUINT[5]={TCIF_IMAGE,TCIF_PARAM,TCIF_RTLREADING,TCIF_STATE,TCIF_TEXT,};

const UINT GPTabCtrl::uNMethods=36;
const char *GPTabCtrl::cArrMethods[]={
/*00*/		"GetImageList","SetImageList","GetItemCount","GetItem","SetItem",
/*05*/		"SetItemExtra","GetItemRect","GetCurSel","SetCurSel","SetCurFocus",
/*10*/		"SetItemSize","SetPadding","GetRowCount","GetToolTips","SetToolTips",
/*15*/		"GetCurFocus","SetMinTabWidth","GetExtendedStyle","SetExtendedStyle","GetItemState",
/*20*/		"SetItemState","InsertItem","DeleteItem","DeleteAllItems","AdjustDspRect",
/*25*/		"RemoveImage","HitTest","DeselectAll","HighlightItem","GetStyle",
/*30*/		"UpdateGroup","AdjustWndRect","SetItemText","SetItemImage","SetUnicodeFormat",
/*35*/		"GetUnicodeFormat","","","","",
		"","","", "", "", 
	};

const char *GPTabCtrl::cArrMethodsParams[]={
/*00*/		"","ImageListName","","nItem","IdItem,iImage,lParam,State,pszText",
/*05*/		"nBytes","nItem","","nItem","nItem",
/*10*/		"cx,cy","cx,cy","","Not Present","Not Present",
/*15*/		"","nWidth","","ExtendedStyles","nItem,Mask",
/*20*/		"nItem,Mask,State","IdItem,iImage,lParam,State,pszText","nItem","","left,top,right,bottom",
/*25*/		"nItem","ptx,pty","fExcludeFocus","nItem,bHiLi","",
/*30*/		"","left,top,right,bottom","Item,Text","Item,nImage","bFormat",
/*35*/		"","","","","",
		"","","", "", "", 
	};

GPTabCtrl::GPTabCtrl(UINT iUnitId)
{
	referGPU=NULL;
	UnitId=iUnitId;
	m_LastHiLight=-1;
}

GPTabCtrl::~GPTabCtrl()
{
}


BEGIN_MESSAGE_MAP(GPTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(GPTabCtrl)
	ON_WM_PARENTNOTIFY_REFLECT()
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelchange)
	ON_NOTIFY_REFLECT(TCN_SELCHANGING, OnSelchanging)
	ON_NOTIFY_REFLECT(TCN_KEYDOWN, OnKeydown)
	ON_NOTIFY_REFLECT(TCN_GETOBJECT, OnGetobject)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(NM_OUTOFMEMORY, OnOutofmemory)
	ON_NOTIFY_REFLECT(TCN_FOCUSCHANGE, OnFocusChange)
	ON_NOTIFY_REFLECT(NM_RELEASEDCAPTURE, OnReleasedCapture)
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
// GPTabCtrl message handlers

UINT GPTabCtrl::DoMethod(const char *iStr, char *oStr)
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
		case  0: /*GetImageList*/
			if (oStr!=NULL)
			{
				CImageList* tmp=GetImageList();
				int id=GPC.FindImageList(tmp);
				if (id>=0) strcpy(oStr,GPC.a_GPImageList[id].ILName);
			}
			break;
		case  1: /*SetImageList*/
			{
				int num=GPC.GetImageListId(pos);
				if (num>=0)	SetImageList(&(GPC.a_GPImageList[num].m_IL));
			}
			break;
		case  2: /*GetItemCount*/
			retint=GetItemCount();
			break;
		case  3: /*GetItem*/
			if (oStr!=NULL)
			{
				TCITEM it={0};
				it.mask=TCIF_TEXT|TCIF_IMAGE|TCIF_PARAM|TCIF_RTLREADING|TCIF_STATE;
				it.pszText = new char [500];
				it.cchTextMax =490;
				it.dwStateMask =TCIS_BUTTONPRESSED|TCIS_HIGHLIGHTED;
				GetItem(atoipos, &it);
				sprintf(oStr,"%s|%s%c%s%c%d%c%ld",
					(it.dwState&TCIS_BUTTONPRESSED)==TCIS_BUTTONPRESSED?"_BUTTONPRESSED":"",
					(it.dwState&TCIS_HIGHLIGHTED)==TCIS_HIGHLIGHTED?"_HIGHLIGHTED":"",
					127,it.pszText,
					127,it.iImage,
					127,it.lParam);
				delete[] it.pszText;
			}
			break;
		case  4: /*SetItem*/
		case 21: /*InsertItem*/
			// format PICK  IdItem,iImage,lParam,State,pszText
			{
				char *postmpcc=new char [(int)strlen(pos)+10];
				strcpy(postmpcc,pos);
				TCITEM it={0};
				int IdItem=0;
				it.mask=TCIF_TEXT|TCIF_IMAGE|TCIF_PARAM|TCIF_STATE;
				it.cchTextMax =490;
				it.dwStateMask =TCIS_BUTTONPRESSED|TCIS_HIGHLIGHTED;
				m_LastScanf=sscanf(postmpcc,"%d,%d,%d",&IdItem,&it.iImage,&it.lParam);
				if (strstr(postmpcc,"_BUTTONPRESSED")!=NULL) it.dwState|=TCIS_BUTTONPRESSED;
				if (strstr(postmpcc,"_HIGHLIGHTED")!=NULL) it.dwState|=TCIS_HIGHLIGHTED;
				char *pos2=strchr(postmpcc,',');
				int i;
				for(i=0;i<3;i++)
					if (pos2!=NULL) pos2=strchr(++pos2,',');
				if (pos2!=NULL) pos2++;
				#ifdef RUS
					else  pos2="Закладка №";
				#else
					else  pos2="Tab №";
				#endif
				it.pszText=pos2;

				if (nfunc==4)	retint=SetItem(IdItem,&it);
				else			retint=InsertItem(IdItem,&it);
				delete[] postmpcc;
			}
			break;
		case  5: /*SetItemExtra*/
			retint=SetItemExtra(atoipos);
			break;
		case  6: /*GetItemRect*/
			if (oStr!=NULL)
			{
				CRect re;
				GetItemRect(atoipos,&re);
				sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
			}
			break;
		case  7: /*GetCurSel*/	retint=GetCurSel();	break;
		case  8: /*SetCurSel*/
			retint=SetCurSel(atoipos);
			if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
				DoMethod("UpdateGroup",NULL);
			break;
		case  9: /*SetCurFocus*/	SetCurFocus(atoi(pos));	break;
		case 10: /*SetItemSize*/
			{
				CSize sz;
				m_LastScanf=sscanf(pos,"%d,%d",&sz.cx,&sz.cy);
				sz=SetItemSize(sz);
				if (oStr!=NULL)	sprintf(oStr,"%d\x7F%d",(DWORD)&sz.cx,(DWORD)&sz.cy);
			}
			break;
		case 11: /*SetPadding*/
			{
				CSize sz;
				m_LastScanf=sscanf(pos,"%d,%d",&sz.cx,&sz.cy);
				SetPadding(sz);
			}
			break;
		case 12: /*GetRowCount*/	retint=GetRowCount(); break;
		case 15: /*GetCurFocus*/	retint=GetCurFocus(); break;
		case 16: /*SetMinTabWidth*/
			retint=SetMinTabWidth(atoi(pos));
			break;
		case 17: /*GetExtendedStyle*/
			if (oStr!=NULL)
				GetObjStlStr(oStr, GetExtendedStyle(), N_TAB_EX_STYLES,  aTabExStyleName, aTabExStyleUINT, aTabExStyleMask);
			break;
		case 18: /*SetExtendedStyle*/
			{
				UINT stl=0;
				int i;
					for(i=0;i<N_TAB_EX_STYLES;i++)
						if (strstr(pos,aTabExStyleName[i])!=NULL) stl|=aTabExStyleUINT[i];
					stl=SetExtendedStyle(stl);
			}
			break;
		case 19: /*GetItemState*/
			if (oStr!=NULL)
			{
				UINT mask=0;
				int i;
				for(i=0;i<5;i++)
					if (strstr(pos,TabMaskName[i])!=NULL) mask|=TabMaskUINT[i];

				DWORD dwState=GetItemState(atoi(pos), mask);
				sprintf(oStr,"%s|%s",(dwState&TCIS_BUTTONPRESSED)==TCIS_BUTTONPRESSED?"_BUTTONPRESSED":""
					,(dwState&TCIS_HIGHLIGHTED)==TCIS_HIGHLIGHTED?"_HIGHLIGHTED":"");
			}
			break;
		case 20: /*SetItemState*/
			{
				UINT mask=0;
				int i;
				for(i=0;i<5;i++)
					if (strstr(pos,TabMaskName[i])!=NULL) mask|=TabMaskUINT[i];

				DWORD dwState=(strstr(pos,"_BUTTONPRESSED")==NULL)?0:TCIS_BUTTONPRESSED;
				dwState|=(strstr(pos,"_HIGHLIGHTED")==NULL)?0:TCIS_HIGHLIGHTED;

				retint=SetItemState(atoi(pos), mask, dwState );
			}
			break;
		case 22: /*DeleteItem*/
			retint=DeleteItem(atoi(pos));
			break;
		case 23: /*DeleteAllItems*/
			retint=DeleteAllItems();
			break;
		case 24: /*AdjustDspRect*/
		case 31: /*AdjustWndRect*/
			if (oStr!=NULL)
			{
				CRect re;
				int Item=0;
				m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d",&Item,&re.left,&re.top,&re.right,&re.bottom);
				AdjustRect(nfunc==24,re);
				sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
			}
			break;
		case 25: /*RemoveImage*/	RemoveImage(atoipos);		break;
		case 26: /*HitTest*/
			if (oStr!=NULL)
			{
				TCHITTESTINFO htst={0};
				char *httype[5]={"TCHT_NOWHERE","TCHT_ONITEM","TCHT_ONITEMICON","TCHT_ONITEMLABEL","",};
				UINT htUint[4]={TCHT_NOWHERE,TCHT_ONITEM,TCHT_ONITEMICON,TCHT_ONITEMLABEL,};
				m_LastScanf=sscanf(pos,"%d,%d",&htst.pt.x,&htst.pt.y);
				int ret=HitTest(&htst);
				int i;
				for(i=0;i<4 && (htst.flags&htUint[i])!=htUint[i];i++);
				sprintf(oStr,"%d\x7F%s",ret,httype[i]);
			}
			break;
		case 27: /*DeselectAll*/		DeselectAll(atoi(pos));	break;
		case 28: /*HighlightItem*/
			{
				int IdItem=0,HiLi=0;
				m_LastScanf=sscanf(pos,"%d,%d",&IdItem,&HiLi);
				retint=HighlightItem(IdItem,HiLi);
			}
			break;
		case 29: /*GetStyle*/
			if (oStr!=NULL)
				GetObjStlStr(oStr, GetStyle(), N_TAB_STYLES,  aTabStyleName, aTabStyleUINT, aTabStyleMask);
			break;
		case 30: /*UpdateGroup*/
			if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
				referGPU[UnitId&0xFFFF]->UpdateGroup(GetCurSel(),GetStyle());
			break;
		case 32: /*SetItemText*/
			{
				char *postmpcc=new char [(int)strlen(pos)+10];
				strcpy(postmpcc,pos);
				TCITEM it={0};
				int IdItem=atoipos;
				it.mask=TCIF_TEXT;
				it.cchTextMax =5000;
				char *pos2=strchr(postmpcc,',');
				if (pos2++==NULL) pos2="";
				it.pszText=pos2;

				retint=SetItem(IdItem,&it);
				delete[] postmpcc;
			}
			break;
		case 33: /*SetItemImage*/
			{
				TCITEM it={0};
				int IdItem=0;
				it.mask=TCIF_IMAGE;
				m_LastScanf=sscanf(pos,"%d,%d",&IdItem,&it.iImage);

				retint=SetItem(IdItem,&it);
			}
			break;
		case 34: /*SetUnicodeFormat*/
			retint=SendMessage(TCM_SETUNICODEFORMAT,atoipos,0);
			break;
		case 35: /*GetUnicodeFormat*/
				retint=SendMessage(TCM_GETUNICODEFORMAT,0,0);
			break;


			// не реализовано (пока не надо, или не пока)
		case 13: /*GetToolTips*/
		case 14: /*SetToolTips*/
		default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
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
		GPC.m_ErrReport.GPWriteErrorLog("GPTabCtrl", "DoMethod",iStr);
		delete[] str;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);

	return nfunc;
}

UINT GPTabCtrl::GPSetProperty(char *iStr)
{
	char *iValue=new char [(int)strlen(iStr)+5];
	strcpy(iValue,iStr);
	UINT ret=1,i;
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
				if (m_hWnd!=NULL)
				{
					ret=2;
					strcat(pos,"|");
					int InvFlg=0;
					// GPTabCtrl specif
					for(i=0;i<N_TAB_STYLES;i++)
						if (strstr(pos,aTabStyleName[i])!=NULL)
						{
							InvFlg++;
							switch(propnum)
							{
							case 2: /* STYLE*/
							case 0: /* ADDSTYLE*/	ModifyStyle(0,aTabStyleUINT[i]);break;
							case 1: /* DELSTYLE*/	ModifyStyle(aTabStyleUINT[i],0);break;
							}
						}

					UINT es=GetExtendedStyle();
					if (propnum==2) es=0;

					char *postmp=strstr(pos,"&X");
					if (postmp!=NULL)
					{
						UINT tmpstl=0;
						m_LastScanf=sscanf(postmp,"&X%X",&tmpstl);
						InvFlg++;
						switch(propnum)
						{
						case 2: /* STYLE*/
						case 0: /* ADDSTYLE*/	es|=tmpstl;	break;
						case 1: /* DELSTYLE*/	es=((es|tmpstl)^tmpstl);break;
						}
					}
					else
					for(i=0;i<N_TAB_EX_STYLES;i++)
						if (strstr(pos,aTabExStyleName[i])!=NULL)
						{
							InvFlg++;
							switch(propnum)
							{
							case 2: /* STYLE*/
							case 0: /* ADDSTYLE*/	es|=aTabExStyleUINT[i];	break;
							case 1: /* DELSTYLE*/	es=((es|aTabExStyleUINT[i])^aTabExStyleUINT[i]);break;
							}
						}

					SetExtendedStyle(es);
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

void GPTabCtrl::ParentNotify(UINT message, LPARAM lParam)
{
	char txt[100];
	if (message==WM_CREATE || message==WM_DESTROY)
		sprintf(txt,"%d\x7F%d\x7F%X",message/0x10000,(message&0xFFFF),lParam/0x10000);
	else
		sprintf(txt,"%d\x7F%d\x7F%d\x7F%d",message/0x10000,(message&0xFFFF),lParam/0x10000,(lParam&0xFFFF));
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"ParentNotify",txt);
}

LRESULT GPTabCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message==WM_GETDLGCODE && !lParam) return 0x8c|DLGC_HASSETSEL;


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
		if (m_LastHiLight>=0) HighlightItem(m_LastHiLight,FALSE);
		m_LastHiLight=-1;
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
	else lpr=CTabCtrl::WindowProc(message, wParam, lParam);

	return lpr;
}


void GPTabCtrl::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		char *str=new char [5008];;
		int curSel=GetCurSel();
		TCITEM tci={0};
		tci.mask=TCIF_IMAGE|TCIF_PARAM|TCIF_STATE|TCIF_TEXT;
		tci.pszText=str+1000;
		tci.cchTextMax=4000;

		GetItem(curSel,&tci);

		sprintf(str,"%d\x7F%d\x7F%d\x7F%d\x7F%s",curSel,tci.lParam,tci.iImage,tci.dwState,tci.pszText);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSelchange",str);
		if (referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
			DoMethod("UpdateGroup",NULL);

		delete [] str;
	}
	*pResult = 0;
}

void GPTabCtrl::OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult)
{
	char str[50]; sprintf(str,"%d",GetCurSel());
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSelchanging",str);
	*pResult = 0;
}

void GPTabCtrl::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult)
{
	TC_KEYDOWN* pTCKeyDown = (TC_KEYDOWN*)pNMHDR;
	if (referGPU!=NULL)
	{
		char str[200];
		if (pTCKeyDown)
			sprintf(str,"%d\x7F%d", pTCKeyDown->wVKey,pTCKeyDown->flags);
		else *str=0;

		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnKeydown",str);
	}
	*pResult = 0;
}

void GPTabCtrl::OnGetobject(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMOBJECTNOTIFY* pTCObjectNotify = (NMOBJECTNOTIFY*)pNMHDR;
	if (referGPU!=NULL)
	{
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnGetobject","");
	}
	*pResult = 0;
}

void GPTabCtrl::OnRclick(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnRclick","");
	*pResult = 0;
}

void GPTabCtrl::OnClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		CString str;
		str.Format("%d",GetCurSel());
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClick",str);
		if (referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
			DoMethod("UpdateGroup",NULL);
	}
	*pResult = 0;
}

void GPTabCtrl::OnOutofmemory(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnOutofmemory","");
	*pResult = 0;
}


BOOL GPTabCtrl::PreTranslateMessage(MSG* pMsg)
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

	return CTabCtrl::PreTranslateMessage(pMsg);
}

void GPTabCtrl::OnClose()
{
	if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClose","");
//	CTabCtrl::OnClose();
}

void GPTabCtrl::OnSizing(UINT fwSide, LPRECT pRect)
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

	if (EnableSz) CTabCtrl::OnSizing(fwSide, pRect);

	GetParent()->SendMessage(GPN_UPDATESIZE);

}

void GPTabCtrl::OnDragMouseHover()
{
	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(GPC.m_DragDrop.DragName)<0xFFFFFFFFL)
	{
		// Reset the timer.
		::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);

		// Get the current cursor position and window height.
		DWORD dwPos = ::GetMessagePos ();
		CPoint point (LOWORD (dwPos), HIWORD (dwPos));
		ScreenToClient (&point);


		int nSel=GetCurSel();
		TCHITTESTINFO tch={0};
		tch.pt.x=point.x;
		tch.pt.y=point.y;
		int nItem=HitTest(&tch);
		CString tmp="-1";
		if (nItem>=0)
		{
			if (nItem!=nSel)
			{
				GPC.m_DragDrop.pImageList->DragShowNolock(FALSE);
				SetCurSel(nItem);
				if (referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
					DoMethod("UpdateGroup",NULL);
				UpdateWindow();
				GPC.m_DragDrop.pImageList->DragShowNolock(TRUE);
			}
			TCITEM tci={0};
			tci.mask=TCIF_TEXT;
			tci.cchTextMax=250;
			tci.pszText=new char [300];
			*tci.pszText=0;
			GetItem(nItem,&tci);
			tmp.Format("%d\x07%s",nItem,tci.pszText);
			delete[] tci.pszText;
		}
		referGPU[UnitId&0xFFFF]->SendDropHoverEvent(tmp,&GPC.m_DragDrop,&point);
	}
}

void GPTabCtrl::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
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

		int nSel=GetCurSel();
		TCHITTESTINFO tch={0};
		tch.pt.x=point->x;
		tch.pt.y=point->y;
		int nItem=HitTest(&tch);
		CString tmp="-1";
		if (nItem>=0)
		{
			if (nItem!=nSel)
			{
				GPC.m_DragDrop.pImageList->DragShowNolock(FALSE);
				SetCurSel(nItem);
				if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
					DoMethod("UpdateGroup",NULL);
				UpdateWindow();
				GPC.m_DragDrop.pImageList->DragShowNolock(TRUE);
			}
			TCITEM tci={0};
			tci.mask=TCIF_TEXT;
			tci.cchTextMax=250;
			tci.pszText=new char [300];
			*tci.pszText=0;
			GetItem(nItem,&tci);
			tmp.Format("%d\x07%s",nItem,tci.pszText);
			delete[] tci.pszText;
		}

		referGPU[UnitId&0xFFFF]->SendDropMoveEvent(tmp,pDrDrStruct,point);

		if (mDrop)
			::SetTimer (pDrDrStruct->hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nDelayInterval, NULL);
	}
}

void GPTabCtrl::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && referGPU)
	{
		::ScreenToClient(m_hWnd,point);
		TCHITTESTINFO tch={0};
		tch.pt.x=point->x;
		tch.pt.y=point->y;
		int nItem=HitTest(&tch);
		CString tmp="-1";

		pDrDrStruct->pImageList->DragShowNolock(FALSE);
		if (m_LastHiLight>=0)
			HighlightItem(m_LastHiLight,FALSE);
		m_LastHiLight=-1;
		pDrDrStruct->pImageList->DragShowNolock(TRUE);

		if (nItem>=0)
		{
			TCITEM tci={0};
			tci.mask=TCIF_TEXT;
			tci.cchTextMax=250;
			tci.pszText=new char [300];
			*tci.pszText=0;
			GetItem(nItem,&tci);
			tmp.Format("%d\x07%s",nItem,tci.pszText);
			delete[] tci.pszText;
		}
		referGPU[UnitId&0xFFFF]->SendDropEvent(tmp,pDrDrStruct,point);
	}
}

DWORD GPTabCtrl::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	int nItem=-1;
	if (pDrDrStruct && mDrop && referGPU)
	{
		TCHITTESTINFO tch={0};
		tch.pt.x=point.x;
		tch.pt.y=point.y;
		nItem=HitTest(&tch);

		pDrDrStruct->pImageList->DragShowNolock(FALSE);
		if (nItem<0) nItem=-1;
		if (m_LastHiLight>=0 && nItem!=m_LastHiLight) HighlightItem(m_LastHiLight,FALSE);
		if (nItem>=0) HighlightItem(nItem, TRUE );
		UpdateWindow();
		m_LastHiLight=nItem;
		pDrDrStruct->pImageList->DragShowNolock(TRUE);
	}
	return nItem;
}

LRESULT GPTabCtrl::OnNcHitTest(CPoint point)
{
	LRESULT ret=CTabCtrl::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

#include "GP_TermDoc.h"

void GPTabCtrl::OnKillFocus(CWnd* pNewWnd)
{
	CTabCtrl::OnKillFocus(pNewWnd);
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

void GPTabCtrl::OnSetFocus(CWnd* pOldWnd)
{
	CTabCtrl::OnSetFocus(pOldWnd);
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


void GPTabCtrl::OnSize(UINT nType, int cx, int cy)
{
	CTabCtrl::OnSize(nType, cx, cy);

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
	}
}

void GPTabCtrl::OnFocusChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMOBJECTNOTIFY* pTCObjectNotify = (NMOBJECTNOTIFY*)pNMHDR;
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnFocusChange","");
	*pResult = 0;
}

void GPTabCtrl::OnReleasedCapture(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMOBJECTNOTIFY* pTCObjectNotify = (NMOBJECTNOTIFY*)pNMHDR;
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnReleasedCapture","");
	*pResult = 0;
}

BOOL GPTabCtrl::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
	if (referGPU!=NULL)
	{
		switch(message)
		{
		case WM_COMMAND:
			{
				switch(HIWORD(wParam))
				{
				case CBN_EDITCHANGE:
					break;
				case CBN_CLOSEUP:
					break;
				case CBN_DBLCLK:
					break;
				default:
//					TRACE("GPTabCtrl OnChildNotify WM_COMMAND %d\n",HIWORD(wParam));
					break;
				}
			}
			break;
		case WM_NOTIFY:
			{
				int i;
				NMHDR* pNMHDR=(NMHDR *) lParam;
				switch(pNMHDR->code)
				{
					break;
				case TCN_SELCHANGE:
					i=28;break;
				case TCN_SELCHANGING:
					i=27;break;
				case TCN_KEYDOWN:
					i=26;break;
				case TCN_FOCUSCHANGE:
					i=25;break;
				case NM_RCLICK:
					i=24;break;
				case NM_CLICK:
					i=23;break;
				case NM_OUTOFMEMORY:
					i=22;break;
				case NM_RELEASEDCAPTURE:
					i=21;break;
				default:
//					TRACE("GPTabCtrl OnChildNotify WM_NOTIFY %d\n",HIWORD(wParam));
					break;
				}
			}
		break;
		default:
//			TRACE("GPTabCtrl OnChildNotify message %d\n",HIWORD(wParam));
			break;
		}
	}


	return CTabCtrl::OnChildNotify(message, wParam, lParam, pLResult);
}

HBRUSH GPTabCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CTabCtrl::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}
