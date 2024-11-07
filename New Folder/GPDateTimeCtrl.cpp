// GPDateTimeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPDateTimeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPDateTimeCtrl
const UINT GPDateTimeCtrl::uNMethods=13;
const char *GPDateTimeCtrl::cArrMethods[]={
		"GetMonthCalColor","SetMonthCalColor","SetFormat","GetMonthCalCtrl","GetMonthCalFont",
		"SetMonthCalFont","SetRange","GetRange","SetTime","GetTime",
		"UpdateGroup","SetLow","SetHigh","","",
		"","","", "", "", 
	};
const char *GPDateTimeCtrl::cArrMethodsParams[]={
		"Type","r,g,b,Type","FormatStr","Not Present","",
		"LOGFONT","nYear1,nMonth1,nDay1,nHour1,nMin1,nSec1,nYear2,nMonth2,nDay2,nHour2,nMin2,nSec2","","nYear,nMonth,nDay,nHour,nMin,nSec","",
		"","nObject","nObject","","",
		"","","", "", "", 
	};

GPDateTimeCtrl::GPDateTimeCtrl(UINT iUnitId)
{
	MCStyle=0;
	referGPU=NULL;
	UnitId=iUnitId;
	FormatStr="dd.MM.yy";
	ObjLow=NULL;
	ObjHigh=NULL;
}

GPDateTimeCtrl::~GPDateTimeCtrl()
{
}


BEGIN_MESSAGE_MAP(GPDateTimeCtrl, CDateTimeCtrl)
	//{{AFX_MSG_MAP(GPDateTimeCtrl)
	ON_NOTIFY_REFLECT(DTN_CLOSEUP, OnCloseup)
	ON_NOTIFY_REFLECT(DTN_DATETIMECHANGE, OnDatetimechange)
	ON_NOTIFY_REFLECT(DTN_DROPDOWN, OnDropdown)
	ON_NOTIFY_REFLECT(DTN_FORMAT, OnFormat)
	ON_NOTIFY_REFLECT(DTN_FORMATQUERY, OnFormatquery)
	ON_NOTIFY_REFLECT(DTN_USERSTRING, OnUserstring)
	ON_NOTIFY_REFLECT(DTN_WMKEYDOWN, OnWmkeydown)
	ON_NOTIFY_REFLECT(NM_KILLFOCUS, OnKillfocus)
	ON_NOTIFY_REFLECT(NM_SETFOCUS, OnSetfocus)
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
// GPDateTimeCtrl message handlers


/////////////////////////////////////////////////////////////////////////////
// GPButton message handlers
UINT GPDateTimeCtrl::DoMethod(const char *iStr, char *oStr)
{
	char met[150];
	strncpy(met,iStr,145);
	met[145]=0;
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc=0;

	int retint=-123456;
	int atoipos=atoi(pos);

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

	try
	{
		switch(nfunc)
		{
		case 0: /*GetMonthCalColor*/
		case 1: /*SetMonthCalColor*/
			{
				UINT uColorMask[6]={MCSC_BACKGROUND,MCSC_MONTHBK,MCSC_TEXT,MCSC_TITLEBK,MCSC_TITLETEXT,MCSC_TRAILINGTEXT,};
				char *cColorMask[6]={"_BACKGROUND","_MONTHBK","_TEXT","_TITLEBK","_TITLETEXT","_TRAILINGTEXT",};
				UINT cref=0;

				int i;
				for(i=0;i<6 && strstr(pos,cColorMask[i])==NULL;i++);

				if (i<6)
				{
					if (nfunc==0)	cref=GetMonthCalColor(uColorMask[i]);
					else
					if (nfunc==1)
					{
						UINT r=0,g=0,b=0;
						m_LastScanf=sscanf(pos,"%d,%d,%d",&r,&g,&b);
						cref=SetMonthCalColor(uColorMask[i],RGB(r,g,b));
					}
				}

				if (oStr!=NULL)
				{
					for(i=0;i<6 && strstr(pos,cColorMask[i])==NULL;i++);
					if (i<6)
					{
						cref=GetMonthCalColor(uColorMask[i]);
						sprintf(oStr,"%d%c%d%c%d",(cref&0xFF),7,((cref/0x100)&0xFF),7,((cref/0x10000)&0xFF));
					}
				}
			}
			break;
		case 2: /*SetFormat*/
			{
				FormatStr=pos;
				int ret=SetFormat(pos);
				if (oStr!=NULL) sprintf(oStr,"%d",ret);
			}
			break;
		case 3: /*GetMonthCalCtrl*/
			if (oStr!=NULL) sprintf(oStr,"%X",(DWORD)GetMonthCalCtrl());
			break;
		case 4: /*GetMonthCalFont*/
			if (oStr!=NULL)
			{
				CFont* fn=GetMonthCalFont();
				LOGFONT lf={0};
				fn->GetLogFont(&lf);
				TranslLOGFONTtoString(oStr,lf);
			}
			break;
		case 5: /*SetMonthCalFont*/
			{
				LOGFONT lf={0};
				TranslLOGFONT(lf,pos);
				CFont fn;
				fn.CreateFontIndirect(&lf);
				SetMonthCalFont(fn,TRUE);
			}
			break;
		case 6: /*SetRange*/
			{
				int nYear1=0, nMonth1=0, nDay1=0, nHour1=0, nMin1=0, nSec1=0;
				int nYear2=0, nMonth2=0, nDay2=0, nHour2=0, nMin2=0, nSec2=0;
				m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
					&nYear1, &nMonth1, &nDay1, &nHour1, &nMin1, &nSec1,
					&nYear2, &nMonth2, &nDay2, &nHour2, &nMin2, &nSec2);
				BOOL ret=SetRange(	&COleDateTime(nYear1, nMonth1, nDay1, nHour1, nMin1, nSec1),
									&COleDateTime(nYear2, nMonth2, nDay2, nHour2, nMin2, nSec2));
				if (oStr!=NULL) sprintf(oStr,"%d",ret);
			}
			break;
		case 7: /*GetRange*/
			if (oStr!=NULL)
			{
				COleDateTime pMinRange, pMaxRange;
				GetRange( &pMinRange, &pMaxRange );
				sprintf(oStr,"%d\x07%d\x07%d\x07%d\x07%d\x07%d\x7F%d\x07%d\x07%d\x07%d\x07%d\x07%d",
					pMinRange.GetYear(),
					pMinRange.GetMonth(),
					pMinRange.GetDay(),
					pMinRange.GetHour(),
					pMinRange.GetMinute(),
					pMinRange.GetSecond(),
					pMaxRange.GetYear(),
					pMaxRange.GetMonth(),
					pMaxRange.GetDay(),
					pMaxRange.GetHour(),
					pMaxRange.GetMinute(),
					pMaxRange.GetSecond()
					);
			}
			break;
		case 8: /*SetTime*/
			{
				int nYear1=0, nMonth1=0, nDay1=0, nHour1=0, nMin1=0, nSec1=0;
				m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d,%d",
					&nYear1, &nMonth1, &nDay1, &nHour1, &nMin1, &nSec1);
				if (nYear1==0) nYear1=1;
				if (nMonth1==0) nMonth1=1;
				if (nDay1==0) nDay1=1;
				BOOL ret=SetTime(COleDateTime (nYear1, nMonth1, nDay1, nHour1, nMin1, nSec1));
				if (oStr!=NULL) sprintf(oStr,"%d",ret);
				if (referGPU!=NULL && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
					DoMethod("UpdateGroup",NULL);
			}
			break;
		case 9: /*GetTime*/
			if (oStr!=NULL)
			{
				COleDateTime pMinRange;
				if (!GetTime(pMinRange))
					strcpy(oStr,"NONE");
				else
					sprintf(oStr,"%d\x07%d\x07%d\x07%d\x07%d\x07%d",
						pMinRange.GetYear(),
						pMinRange.GetMonth(),
						pMinRange.GetDay(),
						pMinRange.GetHour(),
						pMinRange.GetMinute(),
						pMinRange.GetSecond()
						);
			}
			break;
		case 10: /*UpdateGroup*/
			if (referGPU!=NULL && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
			{
				char str[50];
				GetWindowText(str,45);str[45]=0;
				char *pp=str; while((pp=strchr(pp,'.'))!=NULL) strcpy(pp,pp+1);
				referGPU[UnitId&0xFFFF]->UpdateGroup(atoi(str),GetStyle());
			}
			break;
		case 11:/*SetLow*/
			if (referGPU!=NULL)
			{
				ObjLow=NULL;
				atoipos=(*referGPU)->GetObjectIdByName(pos);
				if (atoipos>0 && (UINT)atoipos<(*referGPU)->m_NGPUNIT && referGPU[atoipos]!=NULL &&
					(referGPU[atoipos]->UnitType==GPUnit::UT_DATETIMECTRL || referGPU[atoipos]->UnitType==GPUnit::UT_MONTHCAL))
					ObjLow=(GPDateTimeCtrl *)(referGPU[atoipos]->UnitPtr);
			}
			break;
		case 12:/*SetHigh*/
			if (referGPU!=NULL)
			{
				ObjHigh=NULL;
				atoipos=(*referGPU)->GetObjectIdByName(pos);
				if (atoipos>0 && (UINT)atoipos<(*referGPU)->m_NGPUNIT && referGPU[atoipos]!=NULL &&
					(referGPU[atoipos]->UnitType==GPUnit::UT_DATETIMECTRL || referGPU[atoipos]->UnitType==GPUnit::UT_MONTHCAL))
					ObjHigh=(GPDateTimeCtrl *)(referGPU[atoipos]->UnitPtr);
			}
			break;
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
		GPC.m_ErrReport.GPWriteErrorLog("GPDateTimeCtrl", "DoMethod",iStr);
		delete[] str;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
	return nfunc;
}

UINT GPDateTimeCtrl::GPSetProperty(char *iStr)
{
	char *iValue=new char [(int)strlen(iStr)+5];
	strcpy(iValue,iStr);
	UINT ret=1,i;



	char *pos=strchr(iValue,'=');

	if (pos!=NULL && m_hWnd)
	{
		char *prop[]={"TEXT", "ADDSTYLE", "DELSTYLE","STYLE",};
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
					COleDateTime dtTmp;
					try
					{
						CString tmpstr=pos;
						if (dtTmp.ParseDateTime(pos))
							SetTime(dtTmp);
						else
						{
							if (tmpstr.Find("/",0)>=0) tmpstr.Replace("/",".");
								else
							if (tmpstr.Find(".",0)>=0) tmpstr.Replace(".","/");
								else
							if (tmpstr.Find("_",0)>=0) tmpstr.Replace("_",".");

							if (dtTmp.ParseDateTime(tmpstr))
								SetTime(dtTmp);
						}

					}
					catch(...)
					{
						GPC.m_ErrReport.GPWriteErrorLog("GPDateTimeCtrl", "DoMethod 313",iStr);
					}
				}
					break;
			case 1: // ADDSTYLE
			case 2: // DELSTYLE
			case 3: // STYLE
				if (m_hWnd!=NULL)
				{
					ret=2;
					strcat(pos,"|");
					int InvFlg=0;
					// DateTime specif
					for(i=0;i<N_DATETIME_STYLES;i++)
						if (strstr(pos,aDateTimeStyleName[i])!=NULL)
						{
							InvFlg++;
							switch(propnum)
							{
							case 3: /* STYLE*/
							case 1: /* ADDSTYLE*/	ModifyStyle(0,aDateTimeStyleUINT[i]);break;
							case 2: /* DELSTYLE*/	ModifyStyle(aDateTimeStyleUINT[i],0);break;
							}
						}


					{
						char *postmp=strstr(pos,"&O");
						if (postmp!=NULL)
						{
							if (propnum==3) MCStyle=0;
							UINT tmpstl=0;
							m_LastScanf=sscanf(postmp,"&O%X",&tmpstl);
							switch(propnum)
							{
							case 3: /* STYLE*/
							case 1: /* ADDSTYLE*/	MCStyle|=tmpstl;	break;
							case 2: /* DELSTYLE*/	MCStyle&=(0xFFFFFFFFL^tmpstl);break;
							}
						}
						else
						for(InvFlg=i=0;i<N_MONTHCAL_STYLES;i++)
							if (strstr(pos,aMonthCalStyleName[i])!=NULL)
							{
								switch(propnum)
								{
								case 3: /* STYLE*/
								case 1: /* ADDSTYLE*/	MCStyle|=aMonthCalStyleUINT[i];break;
								case 2: /* DELSTYLE*/	MCStyle&=(0xFFFFFFFFL^aMonthCalStyleUINT[i]);break;
								}
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

void GPDateTimeCtrl::OnCloseup(NMHDR* pNMHDR, LRESULT* pResult)
{
	char str[250];
	DoMethod("GetTime",str);
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnCloseup",str);

	*pResult = 0;
}

void GPDateTimeCtrl::OnDatetimechange(NMHDR* pNMHDR, LRESULT* pResult)
{
	char str[250];
	if (referGPU!=NULL)
		referGPU[0]->DoMethod("GetFocus",str);

	DoMethod("GetTime",str);
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDatetimechange",str);
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
		DoMethod("UpdateGroup",NULL);
	if (ObjHigh!=NULL || ObjLow!=NULL)
	{
		COleDateTime CurObjTime;
		GetTime(CurObjTime);
		if (ObjHigh!=NULL)
		{
			COleDateTime pMinRange, pMaxRange;
			ObjHigh->GetRange( &pMinRange, &pMaxRange );
			ObjHigh->SetRange( &CurObjTime, &pMaxRange );
		}
		if (ObjLow!=NULL)
		{
			COleDateTime pMinRange, pMaxRange;
			ObjLow->GetRange( &pMinRange, &pMaxRange );
			ObjLow->SetRange( &pMinRange, &CurObjTime );
		}
	}
	*pResult = 0;
}

void GPDateTimeCtrl::OnDropdown(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDropdown","");

	CMonthCalCtrl* tmpmc=GetMonthCalCtrl( );
	if (tmpmc!=NULL)
		tmpmc->ModifyStyle(MCS_DAYSTATE|MCS_MULTISELECT|MCS_WEEKNUMBERS|MCS_NOTODAYCIRCLE|MCS_NOTODAY,MCStyle);

	*pResult = 0;
}

void GPDateTimeCtrl::OnFormat(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnFormat","");
	*pResult = 0;
}

void GPDateTimeCtrl::OnFormatquery(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnFormatquery","");
	*pResult = 0;
}

void GPDateTimeCtrl::OnUserstring(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnUserstring","");
	*pResult = 0;
}

void GPDateTimeCtrl::OnWmkeydown(NMHDR* pNMHDR, LRESULT* pResult)
{
	char str[250];
	DoMethod("GetTime",str);
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnWmkeydown",str);
	*pResult = 0;
}

void GPDateTimeCtrl::OnKillfocus(NMHDR* pNMHDR, LRESULT* pResult)
{
	char str[250];
	DoMethod("GetTime",str);
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnKillfocus",str);
	*pResult = 0;
}

void GPDateTimeCtrl::OnSetfocus(NMHDR* pNMHDR, LRESULT* pResult)
{
	char str[250];
	DoMethod("GetTime",str);
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSetfocus",str);
	*pResult = 0;
}

void GPDateTimeCtrl::ParentNotify(UINT message, LPARAM lParam)
{
	char txt[100];
	if (message==WM_CREATE || message==WM_DESTROY)
		sprintf(txt,"%d\x7F%d\x7F%X",message/0x10000,(message&0xFFFF),lParam/0x10000);
	else
		sprintf(txt,"%d\x7F%d\x7F%d\x7F%d",message/0x10000,(message&0xFFFF),lParam/0x10000,(lParam&0xFFFF));
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"ParentNotify",txt);
}

LRESULT GPDateTimeCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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
	else lpr=CDateTimeCtrl::WindowProc(message, wParam, lParam);

	return lpr;
}

BOOL GPDateTimeCtrl::PreTranslateMessage(MSG* pMsg)
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

	return CDateTimeCtrl::PreTranslateMessage(pMsg);
}

void GPDateTimeCtrl::OnClose()
{
	char str[250];
	DoMethod("GetTime",str);
	if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClose",str);
//	CDateTimeCtrl::OnClose();
}

void GPDateTimeCtrl::OnSizing(UINT fwSide, LPRECT pRect)
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

	if (EnableSz) CDateTimeCtrl::OnSizing(fwSide, pRect);

	GetParent()->SendMessage(GPN_UPDATESIZE);

}

void GPDateTimeCtrl::OnDragMouseHover()
{
	if (referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(GPC.m_DragDrop.DragName)<0xFFFFFFFFL)
	{
		// Reset the timer.
		::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);

		// Get the current cursor position and window height.
		DWORD dwPos = ::GetMessagePos ();
		CPoint point (LOWORD (dwPos), HIWORD (dwPos));
		ScreenToClient (&point);

		referGPU[UnitId&0xFFFF]->SendDropHoverEvent("",&GPC.m_DragDrop,&point);
	}
}

void GPDateTimeCtrl::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
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

		DWORD bDropTarget=0xFFFFFFF;
		BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
		// Highlight the drop target if the cursor is over an item.
		if (mDrop)
			bDropTarget = HighlightDropTarget(pDrDrStruct, CPoint(*point));
		// Modify the cursor to provide visual feedback to the user. Note: It's important to do this AFTER the call to DragMove.
		::SetCursor (bDropTarget==0xFFFFFFF ?
			AfxGetApp()->LoadStandardCursor (IDC_NO)
			: (HCURSOR) ::GetClassLong (m_hWnd, GCL_HCURSOR));

		referGPU[UnitId&0xFFFF]->SendDropMoveEvent("",pDrDrStruct,point);

		if (mDrop)
			::SetTimer (pDrDrStruct->hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nDelayInterval, NULL);
	}
}

void GPDateTimeCtrl::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && referGPU)
	{
		::ScreenToClient(m_hWnd,point);
		referGPU[UnitId&0xFFFF]->SendDropEvent("",pDrDrStruct,point);
	}
}

DWORD GPDateTimeCtrl::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	return 0;
}

LRESULT GPDateTimeCtrl::OnNcHitTest(CPoint point)
{
	LRESULT ret=CDateTimeCtrl::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

#include "GP_TermDoc.h"

void GPDateTimeCtrl::OnKillFocus(CWnd* pNewWnd)
{
	CDateTimeCtrl::OnKillFocus(pNewWnd);
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

void GPDateTimeCtrl::OnSetFocus(CWnd* pOldWnd)
{
	CDateTimeCtrl::OnSetFocus(pOldWnd);
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

void GPDateTimeCtrl::OnSize(UINT nType, int cx, int cy)
{
	CDateTimeCtrl::OnSize(nType, cx, cy);

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
	}
}

HBRUSH GPDateTimeCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CDateTimeCtrl::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}
