// GPMonthCalCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPMonthCalCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPMonthCalCtrl
const UINT GPMonthCalCtrl::uNMethods=24;
const char *GPMonthCalCtrl::cArrMethods[]={
		"GetMinReqRect","SetMonthDelta","GetMonthDelta","SetFirstDayOfWeek","GetFirstDayOfWeek",
		"SizeMinReq","SetToday","GetToday","SetCurSel","GetCurSel",
		"SetDayState","SetMaxSelCount","GetMaxSelCount","SetRange","GetRange",
		"GetMonthRange","SetSelRange","GetSelRange","HitTest","GetColor",
		"SetColor","UpdateGroup","SetLow","SetHigh","",
		"","","","",
	};
const char *GPMonthCalCtrl::cArrMethodsParams[]={
		"","iDelta","","iDay","pbLocal",
		"bRepaint","nYear1,nMonth1,nDay1,nHour1,nMin1,nSec1","","nYear1,nMonth1,nDay1,nHour1,nMin1,nSec1","",
		"nMonths, pStates","nMax","","nYear1,nMonth1,nDay1,nHour1,nMin1,nSec1,nYear2,nMonth2,nDay2,nHour2,nMin2,nSec2","",
		"dwFlags","nYear1,nMonth1,nDay1,nHour1,nMin1,nSec1,nYear2,nMonth2,nDay2,nHour2,nMin2,nSec2","","X,Y","nRegion",
		"BACKGROUND|MONTHBK|TEXT|TITLEBK|TITLETEXT|TRAILINGTEXT,R,G,B","","nObject","nObject","",
		"","","","",
	};

const UINT GPMonthCalCtrl::uNHTI=12;
const char *GPMonthCalCtrl::cArrHTI[13]={
		"CALENDARBK","CALENDARDATE","CALENDARDATENEXT","CALENDARDATEPREV","CALENDARDAY",
		"CALENDARWEEKNUM","NOWHERE","TITLEBK","TITLEBTNNEXT","TITLEBTNPREV",
		"TITLEMONTH","TITLEYEAR","NOWHERE",
	};

const UINT GPMonthCalCtrl::uArrHTI[13]={
		MCHT_CALENDARBK,	MCHT_CALENDARDATE,	MCHT_CALENDARDATENEXT,	MCHT_CALENDARDATEPREV,	MCHT_CALENDARDAY,
		MCHT_CALENDARWEEKNUM,	MCHT_NOWHERE,	MCHT_TITLEBK,			MCHT_TITLEBTNNEXT,		MCHT_TITLEBTNPREV,
		MCHT_TITLEMONTH,	MCHT_TITLEYEAR,0,
	};

const UINT GPMonthCalCtrl::unClrMask=6;
const char * GPMonthCalCtrl::cArrClrMask[6]={
		"BACKGROUND","MONTHBK","TEXT","TITLEBK","TITLETEXT","TRAILINGTEXT",
	};
const UINT GPMonthCalCtrl::uArrClrMask[6]={
		MCSC_BACKGROUND, MCSC_MONTHBK, MCSC_TEXT, MCSC_TITLEBK, MCSC_TITLETEXT, MCSC_TRAILINGTEXT,
	};




GPMonthCalCtrl::GPMonthCalCtrl(UINT iUnitId)
{
	referGPU=NULL;
	UnitId=iUnitId;
	ObjLow=NULL;
	ObjHigh=NULL;
}

GPMonthCalCtrl::~GPMonthCalCtrl()
{
}


BEGIN_MESSAGE_MAP(GPMonthCalCtrl, CMonthCalCtrl)
	//{{AFX_MSG_MAP(GPMonthCalCtrl)
	ON_WM_PARENTNOTIFY_REFLECT()
	ON_WM_CLOSE()
	ON_WM_SIZING()
	ON_WM_NCHITTEST()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_NOTIFY_REFLECT(MCN_GETDAYSTATE, OnGetdaystate)
	ON_NOTIFY_REFLECT(MCN_SELCHANGE, OnSelchange)
	ON_NOTIFY_REFLECT(MCN_SELECT, OnSelect)
	ON_NOTIFY_REFLECT(NM_RELEASEDCAPTURE, OnReleasedcapture)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPMonthCalCtrl message handlers




/////////////////////////////////////////////////////////////////////////////
// GPButton message handlers
UINT GPMonthCalCtrl::DoMethod(const char *iStr, char *oStr)
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
		case 0: /*GetMinReqRect*/
			if (oStr)
			{
				RECT re={0};
				if (GetMinReqRect(&re))
					sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.top,re.left,re.bottom,re.right);
			}
			break;
		case 1: /*SetMonthDelta*/
			retint=SetMonthDelta(atoipos);
			break;
		case 2: /*GetMonthDelta*/
			GetMonthDelta();
			break;
		case 3: /*SetFirstDayOfWeek*/
			SetFirstDayOfWeek(atoipos,&retint);
			break;
		case 4: /*GetFirstDayOfWeek*/
			retint=GetFirstDayOfWeek(NULL);
			break;
		case 5: /*SizeMinReq*/
			retint=SizeMinReq(atoipos);
			break;
		case 6: /*SetToday*/
			{
				int nYear1=0, nMonth1=0, nDay1=0, nHour1=0, nMin1=0, nSec1=0;
				m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d,%d",
					&nYear1, &nMonth1, &nDay1, &nHour1, &nMin1, &nSec1);
				SetToday(COleDateTime(nYear1, nMonth1, nDay1, nHour1, nMin1, nSec1));
			}
			break;
		case 7: /*GetToday*/
			if (oStr)
			{
				SYSTEMTIME ds={0};
				GetToday(&ds);
				sprintf(oStr,"%d\x7F%d\x07%d\x07%d\x07%d\x07%d\x07%d\x07%d",
					ds.wYear,
					ds.wMonth,
					ds.wDay,
					ds.wDayOfWeek,
					ds.wHour,
					ds.wMinute,
					ds.wSecond,
					ds.wMilliseconds
					);
			}
			break;
		case 8: /*SetCurSel*/
			{
				int nYear1=0, nMonth1=0, nDay1=0, nHour1=0, nMin1=0, nSec1=0;
				m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d,%d",
					&nYear1, &nMonth1, &nDay1, &nHour1, &nMin1, &nSec1);
				retint=SetCurSel(COleDateTime(nYear1, nMonth1, nDay1, nHour1, nMin1, nSec1));
			}
			break;
		case 9: /*GetCurSel*/
			if (oStr)
			{
				SYSTEMTIME ds={0};
				GetCurSel(&ds);
				sprintf(oStr,"%d\x7F%d\x07%d\x07%d\x07%d\x07%d\x07%d\x07%d",
					ds.wYear,
					ds.wMonth,
					ds.wDay,
					ds.wDayOfWeek,
					ds.wHour,
					ds.wMinute,
					ds.wSecond,
					ds.wMilliseconds
					);
			}
			break;
		case 10: /*SetDayState*/
			if (atoipos>0)
			{
				const char *tmp=strchr(pos,',');
				if (tmp)
				{
					LPMONTHDAYSTATE ds=new MONTHDAYSTATE [atoipos];
					int ind=0;
					while(tmp++)
					{
						m_LastScanf=sscanf(tmp,"%X",&ds[ind++]);
						tmp=strchr(tmp,GPC.DelimiterIn1);
					}

					retint=SetDayState(atoipos,ds);
					delete[] ds;
				}
			}
		case 11: /*SetMaxSelCount*/
			retint=SetMaxSelCount(atoipos);
			break;
		case 12: /*GetMaxSelCount*/
			retint=GetMaxSelCount();
			break;
		case 13: /*SetRange*/
			{
				int nYear1=0, nMonth1=0, nDay1=0, nHour1=0, nMin1=0, nSec1=0;
				int nYear2=0, nMonth2=0, nDay2=0, nHour2=0, nMin2=0, nSec2=0;
				m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
					&nYear1, &nMonth1, &nDay1, &nHour1, &nMin1, &nSec1,
					&nYear2, &nMonth2, &nDay2, &nHour2, &nMin2, &nSec2);
				retint=SetRange(	&COleDateTime(nYear1, nMonth1, nDay1, nHour1, nMin1, nSec1),
									&COleDateTime(nYear2, nMonth2, nDay2, nHour2, nMin2, nSec2));
			}
			break;
		case 14: /*GetRange*/
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
		case 15: /*GetMonthRange*/
			if (oStr!=NULL)
			{
				COleDateTime pMinRange, pMaxRange;
				GetMonthRange(pMinRange, pMaxRange ,atoipos?GMR_VISIBLE:GMR_DAYSTATE);
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
		case 16: /*SetSelRange*/
			{
				int nYear1=0, nMonth1=0, nDay1=0, nHour1=0, nMin1=0, nSec1=0;
				int nYear2=0, nMonth2=0, nDay2=0, nHour2=0, nMin2=0, nSec2=0;
				m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
					&nYear1, &nMonth1, &nDay1, &nHour1, &nMin1, &nSec1,
					&nYear2, &nMonth2, &nDay2, &nHour2, &nMin2, &nSec2);
				retint=SetSelRange(	COleDateTime(nYear1, nMonth1, nDay1, nHour1, nMin1, nSec1),
									COleDateTime(nYear2, nMonth2, nDay2, nHour2, nMin2, nSec2));
			}
			break;
		case 17: /*GetSelRange*/
			if (oStr!=NULL)
			{
				COleDateTime pMinRange, pMaxRange;
				GetSelRange(pMinRange, pMaxRange );
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
		case 18: /*HitTest*/
			{
				MCHITTESTINFO hi={0};
				hi.cbSize=sizeof(hi);
				m_LastScanf=sscanf(pos,"%d,%d",&hi.pt.x,&hi.pt.y);
				retint=HitTest(&hi);

				UINT i;
				for(i=0;i<GPMonthCalCtrl::uNHTI;i++)
					if (retint==(int) GPMonthCalCtrl::uArrHTI[i])
						break;

				sprintf(oStr,"%s\x7F%d\x07%d\x07%d\x07%d\x07%d\x07%d\x07%d\x07%d\x7F",
					GPMonthCalCtrl::cArrHTI[i],
					hi.st.wYear,
					hi.st.wMonth,
					hi.st.wDay,
					hi.st.wDayOfWeek,
					hi.st.wHour,
					hi.st.wMinute,
					hi.st.wSecond,
					hi.st.wMilliseconds
					);
			}
			break;
		case 19: /*GetColor*/
			if (oStr)
			{
				UINT i;
				for(i=0;i<GPMonthCalCtrl::unClrMask;i++)
				if (_stricmp(GPMonthCalCtrl::cArrClrMask[i],pos)==0)
				{
					UINT clr=GetColor(GPMonthCalCtrl::uArrClrMask[i]);
					sprintf(oStr,"%d\x7F%d\x7F%d",GetRValue(clr),GetGValue(clr),GetBValue(clr));
					break;
				}
			}
			break;
		case 20: /*SetColor*/
			{
				int R,G,B;
				const char *pos2=strchr(pos,',');
				if (pos2++==NULL) pos2="";
				m_LastScanf=sscanf(pos2,"%d,%d,%d",&R,&G,&B);
				UINT i;
				for(i=0;i<GPMonthCalCtrl::unClrMask;i++)
					if (strncmp(GPMonthCalCtrl::cArrClrMask[i],pos,(int)strlen(GPMonthCalCtrl::cArrClrMask[i]))==0)
					{
						UINT clr=SetColor(GPMonthCalCtrl::uArrClrMask[i],RGB(R,G,B));
						if (oStr)
							sprintf(oStr,"%d\x7F%d\x7F%d",GetRValue(clr),GetGValue(clr),GetBValue(clr));
					}
			}
			break;
		case 21: /*UpdateGroup*/
			if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
			{
				char str[50];
				GetWindowText(str,45);str[45]=0;
				char *pp=str; while((pp=strchr(pp,'.'))!=NULL) strcpy(pp,pp+1);
				referGPU[UnitId&0xFFFF]->UpdateGroup(atoi(str),GetStyle());
			}
			break;
		case 22: /*SetLow*/
			if (referGPU!=NULL)
			{
				ObjLow=NULL;
				atoipos=(*referGPU)->GetObjectIdByName(pos);
				if (atoipos>0 && (UINT)atoipos<(*referGPU)->m_NGPUNIT && referGPU[atoipos]
					&&
					(referGPU[atoipos]->UnitType==GPUnit::UT_DATETIMECTRL || referGPU[atoipos]->UnitType==GPUnit::UT_MONTHCAL))
					ObjLow=(GPMonthCalCtrl *)(referGPU[atoipos]->UnitPtr);
			}
			break;
		case 23: /*SetHigh*/
			if (referGPU!=NULL)
			{
				ObjHigh=NULL;
				atoipos=(*referGPU)->GetObjectIdByName(pos);
				if (atoipos>0 && (UINT)atoipos<(*referGPU)->m_NGPUNIT && referGPU[atoipos]
					&&
					(referGPU[atoipos]->UnitType==GPUnit::UT_DATETIMECTRL || referGPU[atoipos]->UnitType==GPUnit::UT_MONTHCAL))
					ObjHigh=(GPMonthCalCtrl *)(referGPU[atoipos]->UnitPtr);
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
		GPC.m_ErrReport.GPWriteErrorLog("GPMonthCalCtrl", "DoMethod",iStr);
		nfunc=0xFFFFFFFFL;
		delete[] str;
}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
	return nfunc;
}

UINT GPMonthCalCtrl::GPSetProperty(char *iStr)
{
	char *iValue=new char [(int)strlen(iStr)+5];
	strcpy(iValue,iStr);
	UINT ret=1,i;



	char *pos=strchr(iValue,'=');

	if (pos!=NULL && m_hWnd)
	{
		char *prop[]={"TEXT", "ADDSTYLE", "DELSTYLE","STYLE", };
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
						dtTmp.Format("dd.MM.yy");
						if (dtTmp.ParseDateTime(pos))	SetCurSel(dtTmp);
					}
					catch(...)
					{
						GPC.m_ErrReport.GPWriteErrorLog("GPMonthCalCtrl", "DoMethod 438",iStr);
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
					// MonthCal specif
					for(i=0;i<N_MONTHCAL_STYLES;i++)
						if (strstr(pos,aMonthCalStyleName[i])!=NULL)
						{
							InvFlg++;
							switch(propnum)
							{
							case 3: /* STYLE*/
							case 1: /* ADDSTYLE*/	ModifyStyle(0,aMonthCalStyleUINT[i]);break;
							case 2: /* DELSTYLE*/	ModifyStyle(aMonthCalStyleUINT[i],0);break;
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

void GPMonthCalCtrl::ParentNotify(UINT message, LPARAM lParam)
{
	char txt[100];
	if (message==WM_CREATE || message==WM_DESTROY)
		sprintf(txt,"%d\x7F%d\x7F%X",message/0x10000,(message&0xFFFF),lParam/0x10000);
	else
		sprintf(txt,"%d\x7F%d\x7F%d\x7F%d",message/0x10000,(message&0xFFFF),lParam/0x10000,(lParam&0xFFFF));
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"ParentNotify",txt);
}

LRESULT GPMonthCalCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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
	else lpr=CMonthCalCtrl::WindowProc(message, wParam, lParam);

	return lpr;
}

BOOL GPMonthCalCtrl::PreTranslateMessage(MSG* pMsg)
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

	return CMonthCalCtrl::PreTranslateMessage(pMsg);
}

void GPMonthCalCtrl::OnClose()
{
	char str[250];
	DoMethod("GetCurSel",str);
	if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClose",str);
//	CMonthCalCtrl::OnClose();
}

void GPMonthCalCtrl::OnSizing(UINT fwSide, LPRECT pRect)
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

	if (EnableSz) CMonthCalCtrl::OnSizing(fwSide, pRect);

	GetParent()->SendMessage(GPN_UPDATESIZE);

}

void GPMonthCalCtrl::OnDragMouseHover()
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

void GPMonthCalCtrl::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
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

void GPMonthCalCtrl::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && referGPU)
	{
		::ScreenToClient(m_hWnd,point);
		referGPU[UnitId&0xFFFF]->SendDropEvent("",pDrDrStruct,point);
	}
}

DWORD GPMonthCalCtrl::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	return 0;
}

LRESULT GPMonthCalCtrl::OnNcHitTest(CPoint point)
{
	LRESULT ret=CMonthCalCtrl::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

#include "GP_TermDoc.h"

void GPMonthCalCtrl::OnKillFocus(CWnd* pNewWnd)
{
	CMonthCalCtrl::OnKillFocus(pNewWnd);
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

void GPMonthCalCtrl::OnSetFocus(CWnd* pOldWnd)
{
	CMonthCalCtrl::OnSetFocus(pOldWnd);
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

void GPMonthCalCtrl::OnSize(UINT nType, int cx, int cy)
{
	CMonthCalCtrl::OnSize(nType, cx, cy);

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
	}
}

void GPMonthCalCtrl::OnGetdaystate(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)
	{
		LPNMDAYSTATE ds=(LPNMDAYSTATE)pNMHDR;
		CString tmps;

		tmps.Format("%d\x7F%d\x07%d\x07%d\x07%d\x07%d\x07%d\x07%d\x07%d\x7F",
			ds->cDayState,
			ds->stStart.wYear,
			ds->stStart.wMonth,
			ds->stStart.wDay,
			ds->stStart.wDayOfWeek,
			ds->stStart.wHour,
			ds->stStart.wMinute,
			ds->stStart.wSecond,
			ds->stStart.wMilliseconds
			);

		CString tmpday;
		int i;
		for(i=0;i<ds->cDayState;i++)
		{
			if (i)		tmpday.Format("\x07%X",ds->prgDayState[i]);
				else	tmpday.Format("%X",ds->prgDayState[i]);
			tmps+=tmpday;
		}

		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent
			(m_hWnd, UnitId,"OnGetdaystate",(LPCSTR)tmps);
	}
	*pResult = 0;
}

void GPMonthCalCtrl::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)
	{
		LPNMSELCHANGE ds=(LPNMSELCHANGE)pNMHDR;
		CString tmps;

		tmps.Format("%d\x07%d\x07%d\x07%d\x07%d\x07%d\x07%d\x07%d\x7F%d\x07%d\x07%d\x07%d\x07%d\x07%d\x07%d\x07%d",
			ds->stSelStart.wYear,
			ds->stSelStart.wMonth,
			ds->stSelStart.wDay,
			ds->stSelStart.wDayOfWeek,
			ds->stSelStart.wHour,
			ds->stSelStart.wMinute,
			ds->stSelStart.wSecond,
			ds->stSelStart.wMilliseconds,
			ds->stSelEnd.wYear,
			ds->stSelEnd.wMonth,
			ds->stSelEnd.wDay,
			ds->stSelEnd.wDayOfWeek,
			ds->stSelEnd.wHour,
			ds->stSelEnd.wMinute,
			ds->stSelEnd.wSecond,
			ds->stSelEnd.wMilliseconds
			);

		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent
			(m_hWnd, UnitId,"OnSelchange",(LPCSTR)tmps);
	}
	*pResult = 0;
}

void GPMonthCalCtrl::OnSelect(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)
	{
		LPNMSELCHANGE ds=(LPNMSELCHANGE)pNMHDR;
		CString tmps;

		tmps.Format("%d\x07%d\x07%d\x07%d\x07%d\x07%d\x07%d\x07%d\x7F%d\x07%d\x07%d\x07%d\x07%d\x07%d\x07%d\x07%d",
			ds->stSelStart.wYear,
			ds->stSelStart.wMonth,
			ds->stSelStart.wDay,
			ds->stSelStart.wDayOfWeek,
			ds->stSelStart.wHour,
			ds->stSelStart.wMinute,
			ds->stSelStart.wSecond,
			ds->stSelStart.wMilliseconds,
			ds->stSelEnd.wYear,
			ds->stSelEnd.wMonth,
			ds->stSelEnd.wDay,
			ds->stSelEnd.wDayOfWeek,
			ds->stSelEnd.wHour,
			ds->stSelEnd.wMinute,
			ds->stSelEnd.wSecond,
			ds->stSelEnd.wMilliseconds
			);

		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent
			(m_hWnd, UnitId,"OnSelect",(LPCSTR)tmps);
	}
	*pResult = 0;
}

void GPMonthCalCtrl::OnReleasedcapture(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent
			(m_hWnd, UnitId,"OnReleasedcapture","");
	*pResult = 0;
}

HBRUSH GPMonthCalCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CMonthCalCtrl::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}
