// GPToolTipCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPToolTipCtrl.h"
#include "GPUnit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGPToolTipCtrl

#define TTM_RELAYEVENT          (WM_USER + 7)
#define TTM_WINDOWFROMPOINT     (WM_USER + 16)





const UINT CGPToolTipCtrl::uNToolTipMethods=22;
const char *CGPToolTipCtrl::cArrToolTipMethods[35]={
	/*00*/	"TT_Activate","TT_SetDelayTime","TT_GetToolCount","TT_SetWindowTheme","TT_TrackPosition",
	/*05*/	"TT_SetTipBkColor","TT_SetTipTextColor","TT_GetDelayTime","TT_GetTipBkColor","TT_GetTipTextColor",
	/*10*/	"TT_SetMaxTipWidth","TT_GetMaxTipWidth","TT_SetMargin","TT_GetMargin","TT_Pop",
	/*15*/	"TT_Update","TT_SetTitle","TT_AdjustTextRect","TT_AdjustWindowRect","TT_GetTitle",
	/*20*/	"TT_EnumTools","TT_GetCurrentTool","","","",
	/*25*/	"","","","","",
	/*30*/	"","","","","",
	};

const char *CGPToolTipCtrl::cArrToolTipMethodsParams[35]={
	/*00*/	"bActivate","timeRESHOW,&timeAUTOPOP,&timeINITIAL","","AppName","posX,posY",
	/*05*/	"r,g,b","r,g,b","","","",
	/*10*/	"MaxTipWidth","","left,top,right,bottom","","",
	/*15*/	"","IdIcon,TitleText","left,top,right,bottom","left,top,right,bottom","",
	/*20*/	"","","","","",
	/*25*/	"","","","","",
	/*30*/	"","","","","",
	};

const UINT CGPToolTipCtrl::uNToolTipMethodsAll=11;
const char *CGPToolTipCtrl::cArrToolTipMethodsAll[15]={
	/*00*/	"TT_TrackActivate","TT_GetBubbleSize","TT_NewToolRect","TT_GetToolInfo","TT_SetToolInfo",
	/*05*/	"TT_GetText","TT_UpdateTipText","TT_Popup","TT_AddTool","TT_DelTool",
	/*10*/	"TT_SetFlags","","","","",
	};

const char *CGPToolTipCtrl::cArrToolTipMethodsParamsAll[15]={
	/*00*/	"bTrack","","left,top,right,bottom","","Flags,ID,left,top,right,bottom,lParam;Text",
	/*05*/	"","Text","x,y","Flags,Text","",
	/*10*/	"newFlag","","","","",
	};


CGPToolTipCtrl::CGPToolTipCtrl()
{
	GPU=NULL;
	GPMSG=new GPMessage("TTN_Show,TTN_Pop,TTN_LinkClick,TTN_NeedText,",GPU,0);
	m_IdScrDlg=0;
	mainHWND=NULL;
	m_PopupPoint.x=-123456;
	m_PopupPoint.y=-123456;
	m_PopupHWND=NULL;
}

CGPToolTipCtrl::~CGPToolTipCtrl()
{
	if (GPMSG) delete GPMSG;
	GPMSG=NULL;
}


BEGIN_MESSAGE_MAP(CGPToolTipCtrl, CToolTipCtrl)
	//{{AFX_MSG_MAP(CGPToolTipCtrl)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGPToolTipCtrl message handlers

void CGPToolTipCtrl::OnTimer(UINT nIDEvent) 
{
	CToolTipCtrl::OnTimer(nIDEvent);
}

void CGPToolTipCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CToolTipCtrl::OnSize(nType, cx, cy);
}

void CGPToolTipCtrl::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CToolTipCtrl::OnShowWindow(bShow, nStatus);
}

LRESULT CGPToolTipCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	LRESULT ret=NULL;
	if (message==TTM_WINDOWFROMPOINT)
	{
		if (m_PopupPoint.x!=-123456 && m_PopupPoint.y!=-123456 && m_PopupHWND)
		{
			POINT *po=(POINT*) lParam;
			po->x=m_PopupPoint.x;
			po->y=m_PopupPoint.y;
			ret=(LRESULT)m_PopupHWND;
		}
		else
		m_PopupPoint.x=-123456;m_PopupPoint.y=-123456;m_PopupHWND=NULL;
	}
	
	return ret?ret:CToolTipCtrl::WindowProc(message, wParam, lParam);
}

BOOL CGPToolTipCtrl::PreTranslateMessage(MSG* pMsg) 
{
	return CToolTipCtrl::PreTranslateMessage(pMsg);
}

BOOL CGPToolTipCtrl::DoMethod(const char *iStr, char *oStr, HWND ihWnd)
{
	BOOL FRet=FALSE;
	try
	{
		if (mainHWND) 	
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

			if (*met=='T' && met[1]>='0' && met[1]<='9') nfunc=atoi(met+1);
			else
			{
				for(nfunc=0;nfunc<uNToolTipMethods && _stricmp(met,cArrToolTipMethods[nfunc])!=0;nfunc++); 

				if (nfunc==uNToolTipMethods)
				{
					for(nfunc=0;nfunc<uNToolTipMethodsAll && _stricmp(met,cArrToolTipMethodsAll[nfunc])!=0;nfunc++); 
					nfunc+=1000;
				}
			}

			FRet=TRUE;
			if (oStr!=NULL) *oStr=0;
			switch(nfunc)
			{
			case 0: /*TT_Activate*/
				Activate(atoipos);
				break;
			case 1: /*TT_SetDelayTime*/
				{
					int timeRESHOW=500,timeAUTOPOP=500,timeINITIAL=500;
					m_LastScanf=sscanf(pos,"%d,%d,%d",&timeRESHOW,&timeAUTOPOP,&timeINITIAL);
					SetDelayTime(TTDT_RESHOW,timeRESHOW);
					SetDelayTime(TTDT_AUTOPOP,timeAUTOPOP);
					SetDelayTime(TTDT_INITIAL,timeINITIAL);
				}
				break;
			case 2: /*TT_GetToolCount*/		retint=GetToolCount();	break;
			case 1000: /*TT_TrackActivate*/
				{
					TOOLINFO ti={0};
					ti.cbSize=sizeof(ti);
					ti.hwnd=ihWnd;
					ti.uId= (UINT)ihWnd;
					ti.uFlags=TTF_IDISHWND;
					ti.lpszText=new char [15000];
					*(ti.lpszText)=0;
					retint=SendMessage(TTM_GETTOOLINFO,0,(LPARAM)&ti);
					retint=SendMessage(TTM_TRACKACTIVATE,atoipos,(WPARAM)&ti);
					delete[] ti.lpszText;
				}
				break;
			case 4: /*TT_TrackPosition*/
				{
					int posX=0,posY=0;
					m_LastScanf=sscanf(pos,"%d,%d",&posX,&posY);
					retint=SendMessage(TTM_TRACKPOSITION,0,(WPARAM)(DWORD) MAKELONG(posX, posY));
				}
				break;
			case 5: /*TT_SetTipBkColor*/
				{
					int r=0,g=0,b=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d",&r,&g,&b);
					SetTipBkColor(RGB(r,g,b));
				}
				break;
			case 6: /*TT_SetTipTextColor*/
				{
					int r=0,g=0,b=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d",&r,&g,&b);
					SetTipTextColor(RGB(r,g,b));
				}
				break;
			case 7: /*TT_GetDelayTime*/
				if (oStr)
					sprintf(oStr,"%d\x7F%d\x7F%d",
							GetDelayTime(TTDT_RESHOW),
							GetDelayTime(TTDT_AUTOPOP),
							GetDelayTime(TTDT_INITIAL));
				break;
			case 8: /*TT_GetTipBkColor*/
				if (oStr)
				{
					COLORREF clr=GetTipBkColor();
					sprintf(oStr,"%d\x7F%d\x7F%d",GetRValue(clr),GetGValue(clr),GetBValue(clr));
				}
				break;
			case 9: /*TT_GetTipTextColor*/
				if (oStr)
				{
					COLORREF clr=GetTipTextColor();
					sprintf(oStr,"%d\x7F%d\x7F%d",GetRValue(clr),GetGValue(clr),GetBValue(clr));
				}
				break;
			case 10: /*TT_SetMaxTipWidth*/
				retint=SetMaxTipWidth(atoipos);
				break;
			case 11: /*TT_GetMaxTipWidth*/
				if (oStr)
					retint=GetMaxTipWidth();
				break;
			case 12: /*TT_SetMargin*/
				{
					RECT re={0};
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&re.left,&re.top,&re.right,&re.bottom);
					SetMargin(&re);
				}
				break;
			case 13: /*TT_GetMargin*/
				if (oStr)
				{
					RECT re={0};
					GetMargin(&re);
					sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);	
				}
				break;
			case 14: /*TT_Pop*/
				Pop();
				break;
			case 15: /*TT_Update*/
				Update();
				break;
			case 1001: /*TT_GetBubbleSize*/
				if (oStr)
				{
					TOOLINFO ti={0};
					ti.cbSize=sizeof(ti);
					ti.uFlags=TTF_TRACK|TTF_ABSOLUTE|TTF_IDISHWND;
					ti.hwnd=ihWnd;
					ti.uId=(UINT)ihWnd;
					ti.lpszText=new char [15000];
					*(ti.lpszText)=0;

					DWORD ret=SendMessage(TTM_GETBUBBLESIZE,0,(LPARAM)&ti);
					sprintf(oStr,"%d\x7F%d",LOWORD(ret),HIWORD(ret));
					delete[] ti.lpszText;
				}
				break;
			case 17: /*TT_AdjustTextRect*/
			case 18: /*TT_AdjustWindowRect*/
				if (oStr)
				{
					RECT re={0};
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&re.left,&re.top,&re.right,&re.bottom);
					SendMessage(TTM_ADJUSTRECT,18-nfunc,(LPARAM)&re);
					sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);	
				}
				break;
			#ifdef W_95
				if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
			#else
				#ifdef W_NT
					if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
				#else
					#ifdef W_98
						if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
					#else
						#ifdef W_98
							if (oStr) strcpy(oStr,"Required version for WXP");
						#else
							case 19: /*TT_GetTitle*/
								if (oStr)
								{
									TTGETTITLE ttgt={0};
									ttgt.dwSize=0;
									ttgt.cch=10000;
									ttgt.pszTitle = new WCHAR [10010];
									ttgt.uTitleBitmap=0;

									SendMessage(TTM_GETTITLE,0,(LPARAM)&ttgt);
									CString tmps(ttgt.pszTitle);
									sprintf(oStr,"%d\x7F%d\x7F%s",ttgt.dwSize,ttgt.uTitleBitmap,(LPCSTR)tmps);	
									delete[] ttgt.pszTitle;
								}
								break;
						#endif
					#endif
				#endif
			#endif
			case 1002: /*TT_NewToolRect*/
				{
					TOOLINFO ti={0};
					ti.cbSize=sizeof(ti);
					ti.uFlags=TTF_IDISHWND;
					ti.hwnd=ihWnd;
					ti.uId=(UINT)ihWnd;
					ti.lpszText=new char [15000];
					*(ti.lpszText)=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&ti.rect.left,&ti.rect.top,&ti.rect.right,&ti.rect.bottom);

					retint=SendMessage(TTM_NEWTOOLRECT,0,(LPARAM)&ti);
					delete[] ti.lpszText;
				}
				break;
			case 1003: /*TT_GetToolInfo*/
				if (oStr)
				{
					TOOLINFO ti={0};
					ti.cbSize=sizeof(ti);
					ti.hwnd=ihWnd;
					ti.uId=(UINT)ihWnd;
					ti.lpszText=new char [15000];
					*(ti.lpszText)=0;
					retint=SendMessage(TTM_GETTOOLINFO,0,(LPARAM)&ti);
					*oStr=0;
					DWORD flgtmp=ti.uFlags;
					StringFromToToolTipFlags(oStr,flgtmp);
					sprintf(oStr+(int)strlen(oStr),"\x7F%d\x7%d\x7%d\x7%d\x7F%s\x7F%d\x7F%d",
						ti.rect.left,ti.rect.top,ti.rect.right,ti.rect.bottom,
						ti.lpszText,ti.lParam,ti.uId);
					delete[] ti.lpszText;
				}
				break;
			case 1004: /*TT_SetToolInfo Flags,ID,left,top,right,bottom,lParam;Text*/
				if (*pos)
				{
					TOOLINFO ti={0};
					ti.cbSize=sizeof(ti);
					DWORD flg=0;
					StringFromToToolTipFlags(pos,flg);
					ti.uFlags=flg;
					ti.hwnd=ihWnd;
					ti.uId=(UINT)ihWnd;
					const char *txttmp=FindField(pos,2,";");
					if (txttmp==NULL) txttmp="";
					ti.lpszText=(char *)txttmp;

					const char *pos2=strchr(pos,',');
					if ((pos2++)==NULL) pos2="";
	
					m_LastScanf=sscanf(pos2,"%d,%d,%d,%d,%d,%d",&ti.uId,&ti.rect.left,&ti.rect.top,&ti.rect.right,&ti.rect.bottom,&ti.lParam);
					if (ti.uId==NULL)
						ti.uId=(UINT)ihWnd;

					retint=SendMessage(TTM_SETTOOLINFO,0,(LPARAM)&ti);

				}
				break;
			case 1005: /*TT_GetText*/
				if (oStr)
				{
					CString retstr;
					GetText(retstr,CWnd::FromHandle(ihWnd));
					strcpy(oStr,retstr);
				}
				break;
			case 1006: /*TT_UpdateTipText*/
				UpdateTipText(pos,CWnd::FromHandle(ihWnd));
				break;
			case 20: /*TT_EnumTools*/
				if (oStr)
				{
					TOOLINFO ti={0};
					ti.cbSize=sizeof(ti);
					char *posout=oStr;
					ti.lpszText=new char [15000];
					int nTools=GetToolCount();
					int iTool;
					for(iTool=0;iTool<nTools;iTool++)
					{
						*ti.lpszText=0;
						SendMessage(TTM_ENUMTOOLS,iTool,(LPARAM)(&ti));
						if (*oStr) *(posout++)='\x7F',*posout=0;
						DWORD flgtmp=ti.uFlags;
						StringFromToToolTipFlags(posout,flgtmp);
						posout+=(int)strlen(posout);
						sprintf(posout,"\x7%d\x2%d\x2%d\x2%d\x7%s\x7%d\x7%d",
							ti.rect.left,ti.rect.top,ti.rect.right,ti.rect.bottom,
							ti.lpszText,ti.lParam,ti.uId);
						posout+=(int)strlen(posout);
					}
					delete[] ti.lpszText;
				}
				break;
			case 21: /*TT_GetCurrentTool*/
				if (oStr)
				{
					TOOLINFO ti={0};
					ti.cbSize=sizeof(ti);
					char *posout=oStr;
					ti.lpszText=new char [15000];
					*ti.lpszText=0;
					SendMessage(TTM_GETCURRENTTOOL,0,(LPARAM)(&ti));
					DWORD flgtmp=ti.uFlags;
					StringFromToToolTipFlags(posout,flgtmp);
					posout+=(int)strlen(posout);
					sprintf(posout,"\x7F%d\x7%d\x7%d\x7%d\x7F%s\x7F%d\x7F%d",
						ti.rect.left,ti.rect.top,ti.rect.right,ti.rect.bottom,
						ti.lpszText,ti.lParam,ti.uId);
					delete[] ti.lpszText;
				}
				break;
			case 16: /*TT_SetTitle*/
				{
					const char *pos2=strchr(pos,',');
					if ((pos2++)==NULL) pos2=" ";
					SendMessage(TTM_SETTITLE,atoipos,(LPARAM)(pos2));
				}
				break;
			case 3: /*TT_SetWindowTheme*/
				{
					CString tmps=pos;
					BSTR bstr=tmps.AllocSysString();
					retint=SendMessage(TTM_SETWINDOWTHEME,0,(LPARAM)bstr);
					SysFreeString(bstr);
				}
				break;
			case 1007: /*TT_Popup*/
				if (*pos)
				{
					m_LastScanf=sscanf(pos,"%d,%d",&m_PopupPoint.x,&m_PopupPoint.y);
					::ClientToScreen(ihWnd,&m_PopupPoint);
					m_PopupHWND=ihWnd;
					retint=SendMessage(TTM_POPUP,0,0);
				}
				break;
			case 1008: /*TT_AddTool Flags,Text*/
				if (*pos)
				{
					TOOLINFO ti={0};
					ti.cbSize=sizeof(ti);
					DWORD flg=0;
					StringFromToToolTipFlags(pos,flg);
					ti.uFlags=flg;
					ti.hwnd=ihWnd;
					ti.uId=(UINT)ihWnd;
					const char *txttmp=FindField(pos,2,",");
					if (txttmp==NULL) txttmp="";
					ti.lpszText=(char *)txttmp;

					retint=SendMessage(TTM_ADDTOOL,0,(LPARAM)&ti);
				}
				break;
			case 1009: /*TT_DelTool*/
				{
					TOOLINFO ti={0};
					ti.cbSize=sizeof(ti);
					ti.hwnd=ihWnd;
					ti.uId=(UINT)ihWnd;
					retint=SendMessage(TTM_DELTOOL,0,(LPARAM)&ti);
				}
				break;
			case 1010: /*TT_SetFlags*/
				if (*pos)
				{
					TOOLINFO ti={0};
					ti.cbSize=sizeof(ti);
					ti.hwnd=ihWnd;
					ti.uId=(UINT)ihWnd;
					ti.lpszText=new char [15000];
					*(ti.lpszText)=0;
					retint=SendMessage(TTM_GETTOOLINFO,0,(LPARAM)&ti);
					DWORD flg=0;
					StringFromToToolTipFlags(pos,flg);
					ti.uFlags=flg;
					retint=SendMessage(TTM_SETTOOLINFO,0,(LPARAM)&ti);
					delete[] ti.lpszText;
				}
				break;

			
			
			case 23: /*TT_HitTest*/
			case 12345678:
			default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);FRet=FALSE;break;
			}
			if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
		}
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGPToolTipCtrl", "DoMethod",iStr);
	}
	return FRet;
}

UINT CGPToolTipCtrl::GPCreate(HWND ihWnd, UINT iIdScrDlg, const char *iStileString, GPUnit **iGPU)
{
	GPU=iGPU;
	mainHWND=ihWnd;
	m_IdScrDlg=iIdScrDlg;
	DWORD ttStyle=0;
	DWORD ttStyleTT=0;
	DWORD ttStyleEx=0;
	const char *iStr=iStileString;
	if (iStr==NULL) iStr="";
	char *tmps=new char [(int)strlen(iStr)+10];
	strcpy(tmps,iStr);
	_strupr(tmps);
	char *pos=strstr(tmps,"TOOLTIPSTYLE=");
	if (pos && *pos)
	{
		char *pos2=strchr(pos,';');
		if (pos2) *(pos2++)=0;
		StringFromToToolTipStyles(pos,ttStyleTT);
		StringFromToWindowStyles(pos,ttStyle);
		StringFromToWindowStylesEx(pos,ttStyleEx);
	}
	delete[] tmps;

	ttStyle&=(0xFFFFFFFF^WS_CHILD);
	#ifndef _VC80_UPGRADE
		return CToolTipCtrl::CreateEx(ttStyleEx, TOOLTIPS_CLASS, NULL,
			WS_POPUP |ttStyleTT|ttStyle, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			ihWnd, NULL, NULL);
	#else
		return CToolTipCtrl::CreateEx(CWnd::FromHandle(ihWnd), WS_POPUP |ttStyleTT|ttStyle,   ttStyleEx); 
	#endif
}

DWORD CGPToolTipCtrl::StringFromToToolTipFlags(const char *iToolTipFlags, DWORD & convToolTipFlags)
{
	const char *OptionName[]={
	"TTF_IDISHWND","TTF_CENTERTIP","TTF_RTLREADING","TTF_SUBCLASS","TTF_TRACK",
	"TTF_ABSOLUTE","TTF_TRANSPARENT","TTF_PARSELINKS","TTF_DI_SETITEM",
	};
	const UINT  uOptionList[]={
	TTF_IDISHWND,TTF_CENTERTIP,TTF_RTLREADING,TTF_SUBCLASS,TTF_TRACK,
	TTF_ABSOLUTE,TTF_TRANSPARENT,TTF_PARSELINKS,TTF_DI_SETITEM,
	};

	if (iToolTipFlags)
	{
		if (*iToolTipFlags)
		{
			char *tmps=new char [(int)strlen(iToolTipFlags)+100];
			strcpy(tmps,iToolTipFlags);
			_strupr(tmps);
			convToolTipFlags=atoi(tmps);
			UINT i;
			for(i=0;i<9;i++)
				if (strstr(tmps,OptionName[i]))
					convToolTipFlags|=uOptionList[i];
			delete[] tmps;
		}
		else
		{
			UINT convSD=convToolTipFlags;
			UINT i;
			for(i=0;i<9;i++)
				if ((convSD&uOptionList[i])==uOptionList[i])
				{
					if (*iToolTipFlags) strcat((char *)iToolTipFlags,"|");
					strcat((char *)iToolTipFlags,OptionName[i]);
					convSD^=uOptionList[i];
				}
				if (convSD) sprintf((char *)iToolTipFlags+(int)strlen(iToolTipFlags),"%s%d",*iToolTipFlags?"|":"",convSD);
		}
	}

	return convToolTipFlags;
}

DWORD CGPToolTipCtrl::StringFromToToolTipStyles(const char *iToolTipStyles, DWORD & convToolTipStyles)
{
	const char *OptionName[]={
	"TTS_ALWAYSTIP","TTS_NOPREFIX","TTS_NOANIMATE","TTS_NOFADE","TTS_BALLOON",
	"TTS_CLOSE","TTS_USEVISUALSTYLE",
	};
	const UINT  uOptionList[]={
	TTS_ALWAYSTIP,TTS_NOPREFIX,TTS_NOANIMATE,TTS_NOFADE,TTS_BALLOON,
	TTS_CLOSE,TTS_USEVISUALSTYLE,
	};

	if (iToolTipStyles)
	{
		if (*iToolTipStyles)
		{
			char *tmps=new char [(int)strlen(iToolTipStyles)+100];
			strcpy(tmps,iToolTipStyles);
			_strupr(tmps);
			convToolTipStyles=atoi(tmps);
			UINT i;
			for(i=0;i<7;i++)
				if (strstr(tmps,OptionName[i]))
					convToolTipStyles|=uOptionList[i];
			delete[] tmps;
		}
		else
		{
			UINT convSD=convToolTipStyles;
			UINT i;
			for(i=0;i<7;i++)
				if ((convSD&uOptionList[i])==uOptionList[i])
				{
					if (*iToolTipStyles) strcat((char *)iToolTipStyles,"|");
					strcat((char *)iToolTipStyles,OptionName[i]);
					convSD^=uOptionList[i];
				}
				if (convSD) sprintf((char *)iToolTipStyles+(int)strlen(iToolTipStyles),"%s%d",*iToolTipStyles?"|":"",convSD);
		}
	}
	return convToolTipStyles;
}



BOOL CGPToolTipCtrl::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult) 
{
		LPNMHDR tmpnm=(LPNMHDR) lParam;

		if (tmpnm!=NULL && GPMSG) 
		{
			switch(tmpnm->code)
			{
			case TTN_SHOW:
				if (GPMSG->FindInActive("TTN_Show"))
					GPMSG->GPSendDlgEvent(GPU[0]->UnitHWND,m_IdScrDlg,"TTN_Show","");
				m_PopupPoint.x=-123456;m_PopupPoint.y=-123456;m_PopupHWND=NULL;
				break;
			case TTN_POP:
				if (GPMSG->FindInActive("TTN_Pop"))
					GPMSG->GPSendDlgEvent(GPU[0]->UnitHWND,m_IdScrDlg,"TTN_Pop","");
				break;
			case TTN_LINKCLICK:
				if (GPMSG->FindInActive("TTN_LinkClick"))
					GPMSG->GPSendDlgEvent(GPU[0]->UnitHWND,m_IdScrDlg,"TTN_LinkClick","");
				break;
			case TTN_NEEDTEXT:
				if (GPMSG->FindInActive("TTN_NeedText"))
					GPMSG->GPSendDlgEvent(GPU[0]->UnitHWND,m_IdScrDlg,"TTN_NeedText","");
				break;
			default:
				break;
			}
		}

	return CToolTipCtrl::OnChildNotify(message, wParam, lParam, pLResult);
}
