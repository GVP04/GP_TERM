// GPStatusBar.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPStatusBar.h"
#include "GPStatusBarCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const UINT GPStatusBar::uNIndicatorsName=8;
const char *GPStatusBar::IndicatorsName[8]={"_SEPARATOR","_EXT","_OVR","_REC","_KANA","_CAPS","_NUM","_SCRL",};
const UINT  GPStatusBar::IndicatorsUINT[8]={ID_SEPARATOR,ID_INDICATOR_EXT,ID_INDICATOR_OVR,ID_INDICATOR_REC,ID_INDICATOR_KANA,ID_INDICATOR_CAPS,ID_INDICATOR_NUM,ID_INDICATOR_SCRL,};

const UINT GPStatusBar::uNPaneStyle=5;
const char *GPStatusBar::aPaneStyle[5]={"SBPS_NOBORDERS","SBPS_POPOUT","SBPS_DISABLED","SBPS_STRETCH","SBPS_NORMAL",};
const UINT  GPStatusBar::uPaneStyle[5]={SBPS_NOBORDERS,SBPS_POPOUT,SBPS_DISABLED,SBPS_STRETCH,SBPS_NORMAL,};


/////////////////////////////////////////////////////////////////////////////
// GPStatusBar
const UINT GPStatusBar::uNMethods=26;
const char *GPStatusBar::cArrMethods[]={
		"UpdateGroup","SBCSetText","SBCGetText","SBCGetTextLength","SBCSetParts",
		"SBCGetParts","SBCGetBorders","SBCSetMinHeight","SBCSetSimple","SBCGetRect",
		"SBCIsSimple","SBCGetTipText","SBCSetTipText","SBCSetBkColor","SBCSetIcon",
		"SetIndicators","CommandToIndex","GetItemID","GetItemRect","GetPaneInfo",
		"GetPaneStyle","GetPaneText","SetPaneStyle","SetPaneText","SetPaneInfo",
		"DoSBCMethod","","","","",
		"","","", "", "", 
	};
const char *GPStatusBar::cArrMethodsParams[]={
		"","nPane,PaneStyle;Text","nPane","nPane","nWidths1,nWidths2,nWidths3,...",
		"","","nMinHeight","bSimple","nPane",
		"","nPane","nPane,Text","r,g,b","nPane,nImage,ILName",
		"Indicators","Comm1,Comm2,....","nPane1,nPane2,nPane3,...","nPane","nPane",
		"nPane","nPane","nPane,Style","nPane;Text","nPane,nId,cxWidth,PaneStyle",
		"SBCMethod","","","","",
		"","","", "", "", 
	};

GPStatusBar::GPStatusBar(UINT iUnitId)
{
	referGPU=NULL;
	UnitId=iUnitId;
}

GPStatusBar::GPStatusBar()
{
	referGPU=NULL;
	UnitId=(UINT)-1;
}

GPStatusBar::~GPStatusBar()
{
}


BEGIN_MESSAGE_MAP(GPStatusBar, CStatusBar)
	//{{AFX_MSG_MAP(GPStatusBar)
	ON_WM_PARENTNOTIFY()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_WM_NCHITTEST()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPStatusBar message handlers


UINT GPStatusBar::DoMethod(const char *iStr, char *oStr)
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
		case 1:  /*SBCSetText*/
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				int nType=0;
				char *pText=strchr(pos333,';');
				if (pText==NULL) pText="";
				else *(pText++)=0;
				_strupr(pos333);
				int i;
				for(i=0;i<5;i++)
					if (strstr(pos333,GPStatusBarCtrl::aSBCPaneStyle[i])!=NULL) nType|=GPStatusBarCtrl::uSBCPaneStyle[i];

				GetStatusBarCtrl().SetText(pText,atoipos,nType);
				delete[] pos333;
			}
			break;
		case 2:  /*SBCGetText*/
		case 3:  /*SBCGetTextLength*/
			if (oStr!=NULL)
			{
				int nType=0;
				if (nfunc==2) oStr[GetStatusBarCtrl().GetText(oStr,atoipos,&nType)]=0;
				else sprintf(oStr,"%d",GetStatusBarCtrl().GetTextLength(atoipos,&nType));
				strcat(oStr,"\x7F");

				int i;
				for(i=0;i<5;i++)
					if ((nType&GPStatusBarCtrl::uSBCPaneStyle[i])==GPStatusBarCtrl::uSBCPaneStyle[i])
					{
						strcat(oStr,GPStatusBarCtrl::aSBCPaneStyle[i]);
						strcat(oStr,"|");
					}
			}
			break;
		case 4:  /*SBCSetParts*/
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
				retint=GetStatusBarCtrl().SetParts(nParts,aWidths);
			}
			break;
		case 5:  /*SBCGetParts*/
			if (oStr!=NULL)
			{
				int nParts,aWidths[255];
				nParts=GetStatusBarCtrl().GetParts(254,aWidths);
				char *pos2=oStr;
				pos2+=sprintf(pos2,"%d",aWidths[0]);
				int i;
				for(i=1;i<nParts;i++)
					pos2+=sprintf(pos2,"\x7F%d",aWidths[i]);
			}
			break;
		case 6:  /*SBCGetBorders*/
			if (oStr!=NULL)
			{
				int nHorz=0,nVert=0,nSpacing=0;
				GetStatusBarCtrl().GetBorders(nHorz,nVert,nSpacing);
				sprintf(oStr,"%d\x7F%d\x7F%d",nHorz,nVert,nSpacing);
			}
			break;
		case 7:  /*SBCSetMinHeight*/	GetStatusBarCtrl().SetMinHeight(atoipos); break;
		case 8:  /*SBCSetSimple*/		retint=GetStatusBarCtrl().SetSimple(atoipos); break;
		case 9:  /*SBCGetRect*/
			if (oStr!=NULL)
			{
				CRect re;
				if (GetStatusBarCtrl().GetRect(atoipos,&re))
					sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
			}
			break;
		case 10: /*SBCIsSimple*/		retint=GetStatusBarCtrl().IsSimple(); break;
		case 11: /*SBCGetTipText*/
			if (oStr!=NULL)	strcpy(oStr,GetStatusBarCtrl().GetTipText(atoipos));
			break;
		case 12: /*SBCSetTipText*/
			{
				const char *szTipText=strchr(pos,',');
				if (szTipText++==NULL) szTipText="";
				GetStatusBarCtrl().SetTipText(atoipos, szTipText);
			}
			break;
		case 13: /*SBCSetBkColor*/
			{
				UINT r=0,g=0,b=0;
				m_LastScanf=sscanf(pos,"%d,%d,%d",&r,&g,&b);
				retint=GetStatusBarCtrl().SetBkColor(RGB(r,g,b));
			}
			break;
		case 14: /*SBCSetIcon*/
			{
				int nPane=0,nImage=0;
				char ImageName[500];
				m_LastScanf=sscanf(pos,"%d,%d,%s",&nPane,&nImage,ImageName);
				GPImageList *SMainIl;
				int ImgLId;
				if ((ImgLId=GPC.GetImageListId(ImageName))>=0 && (SMainIl=&(GPC.a_GPImageList[ImgLId]))!=NULL)
				retint=GetStatusBarCtrl().SetIcon(nPane,(HICON)SMainIl->m_IL.ExtractIcon(nImage));
			}
			break;
		case 15: /*SetIndicators*/
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				_strupr(pos333);
				char *pos2=pos333;
				int nInd=0;
				while(pos2!=NULL && *pos2!=0 && nInd<32)
				{
					char *pos3=strchr(pos2,',');
					if (pos3!=NULL) *(pos3++)=0;
					int i;
					for(i=0;i<uNIndicatorsName;i++)
						if (strcmp(pos2,IndicatorsName[i])==0)
						{indicators[nInd++]=IndicatorsUINT[i];break;}
					if (i>=uNIndicatorsName && strncmp(pos2,"MENU",4)==0)
						indicators[nInd++]=atoi(pos2+4)+MENU_ID_START;
					pos2=pos3;
				}
				retint=0;
				if (nInd>0) retint=SetIndicators(indicators,nInd);
				delete[] pos333;
			}
			break;
		case 16: /*CommandToIndex*/
			if (oStr!=NULL)
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				_strupr(pos333);
				char *pos2=pos333,*curpos=oStr;
				UINT nInd=0;
				*curpos=0;
				while(pos2!=NULL && *pos2!=0)
				{
					char *pos3=strchr(pos2,',');
					nInd=0;
					if (pos3!=NULL) *(pos3++)=0;
					int i;
					for(i=0;i<uNIndicatorsName;i++)
						if (strcmp(pos2,IndicatorsName[i])==0)
						{nInd=IndicatorsUINT[i];break;}
					if (i>=uNIndicatorsName && strncmp(pos2,"MENU",4)==0)
						nInd=atoi(pos2+4)+MENU_ID_START;
					curpos+=sprintf(curpos,"%d\x7F",CommandToIndex(nInd));
					pos2=pos3;
				}
				delete[] pos333;
			}
			break;
		case 17: /*GetItemID*/
			if (oStr!=NULL)
			{
				const char *pos2=pos;
				char *curpos=oStr;
				UINT nInd=0;
				*curpos=0;
				while(pos2!=NULL && *pos2!=0)
				{
					const char *pos3=strchr(pos2,',');
					nInd=GetItemID(atoi(pos2));

					int i;
					for(i=0;i<uNIndicatorsName;i++)
						if (IndicatorsUINT[i]==nInd)
						{curpos+=sprintf(curpos,"%s\x7F",IndicatorsName[i]);break;}
					if (i>=uNIndicatorsName)
						curpos+=sprintf(curpos,"%d\x7F",(nInd>=MENU_ID_START && nInd<=MENU_ID_END)?nInd-MENU_ID_START:nInd);
					pos2=pos3;
				}
			}
			break;
		case 18: /*GetItemRect*/
			if (oStr!=NULL)
			{
				CRect re;
				GetItemRect(atoipos,&re);
				sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
			}
			break;
		case 19: /*GetPaneInfo*/
			if (oStr!=NULL)
			{
				char *curpos=oStr;
				*curpos=0;
				UINT nID,nStyle;
				int cxWidth;
				GetPaneInfo(atoipos,nID,nStyle,cxWidth);
				int i;
				for(i=0;i<uNIndicatorsName;i++)
					if (IndicatorsUINT[i]==nID)
						{curpos+=sprintf(curpos,"%s\x7F",IndicatorsName[i]);break;}
				if (i>=uNIndicatorsName)
					curpos+=sprintf(curpos,"%d\x7F",(nID>=MENU_ID_START && nID<=MENU_ID_END)?nID-MENU_ID_START:nID);

				for(i=0;i<uNPaneStyle;i++)
					if ((nStyle&GPStatusBar::uPaneStyle[i])==GPStatusBar::uPaneStyle[i])
						curpos+=sprintf(curpos,"%s|",GPStatusBar::aPaneStyle[i]);

				sprintf(curpos,"\x7F%d",cxWidth);
			}
			break;
		case 20: /*GetPaneStyle*/
			if (oStr!=NULL)
			{
				UINT nStyle=GetPaneStyle(atoipos);
				int i;
				for(i=0;i<uNPaneStyle;i++)
					if ((nStyle&GPStatusBar::uPaneStyle[i])==GPStatusBar::uPaneStyle[i])
					{
						strcat(oStr,GPStatusBar::aPaneStyle[i]);
						strcat(oStr,"|");
					}
			}
			break;
		case 21: /*GetPaneText*/	if (oStr!=NULL) strcpy(oStr,GetPaneText(atoipos));break;
		case 22: /*SetPaneStyle*/
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				int nType=0;
				_strupr(pos333);
				int i;
				for(i=0;i<uNPaneStyle;i++)
					if (strstr(pos333,GPStatusBar::aPaneStyle[i])!=NULL) nType|=GPStatusBar::uPaneStyle[i];
				SetPaneStyle(atoipos,nType);
				delete[] pos333;
			}
			break;
		case 23: /*SetPaneText*/
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				char *pText=strchr(pos333,';');
				if (pText==NULL) pText="";
				else *(pText++)=0;
				retint=SetPaneText(atoipos,pText);
				delete[] pos333;
			}
			break;
		case 24: /*SetPaneInfo*/
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				UINT nID=0,nStyle=0;
				int cxWidth=15;

				m_LastScanf=sscanf(pos333,"%d,%d,%d",&atoipos,&nID,&cxWidth);
				nID+=MENU_ID_START;
				_strupr(pos333);
				int i;
				for(i=0;i<uNPaneStyle;i++)
					if (strstr(pos333,GPStatusBar::aPaneStyle[i])!=NULL) nStyle|=GPStatusBar::uPaneStyle[i];

				SetPaneInfo(atoipos,nID,nStyle,cxWidth);
				delete[] pos333;
			}
			break;
		case 25: /*DoSBCMethod*/
			if (*pos)
			{
				GPStatusBarCtrl mGPSBC(UnitId);
				mGPSBC.referGPU=referGPU;
				mGPSBC.Attach(GetStatusBarCtrl().m_hWnd);
				mGPSBC.DoMethod(pos,oStr);
				mGPSBC.Detach();
			}
			break;
		default:
			nfunc=GPUnit::DoControlBarMethod(this,iStr,oStr); break;
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
		GPC.m_ErrReport.GPWriteErrorLog("GPStatusBar", "DoMethod",iStr);
		delete[] str;
	}
	switch(nfunc)
	{
	case 1:  /*SBCSetText*/
	case 4:  /*SBCSetParts*/
	case 7:  /*SBCSetMinHeight*/
	case 8:  /*SBCSetSimple*/
	case 13: /*SBCSetBkColor*/
	case 14: /*SBCSetIcon*/
	case 15: /*SetIndicators*/
	case 22: /*SetPaneStyle*/
	case 23: /*SetPaneText*/
	case 24: /*SetPaneInfo*/
		GetParent()->SendMessage(WM_APP+1);
		break;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
	return nfunc;
}

UINT GPStatusBar::GPSetProperty(char *iStr)
{
	char *iValue=new char [(int)strlen(iStr)+5];
	strcpy(iValue,iStr);
	UINT ret=1,i;
	char *pos=strchr(iValue,'=');

	if (pos!=NULL && m_hWnd)
	{
		char *prop[]={ "TEXT", "ADDSTYLE", "DELSTYLE","STYLE",  };
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
					for(i=0;i<N_STATUSBAR_STYLES;i++)
						if (strstr(pos,aStatusBarStyleName[i])!=NULL)
						{
							InvFlg++;
							switch(propnum)
							{
							case 3: /* STYLE*/
							case 1: /* ADDSTYLE*/	ModifyStyle(0,aStatusBarStyleUINT[i]);break;
							case 2: /* DELSTYLE*/	ModifyStyle(aStatusBarStyleUINT[i],0);break;
							}
						}

					UINT Stl=0;
					switch(propnum)
					{
					case 1: /* ADDSTYLE*/	Stl=GetBarStyle();
					case 3: /* STYLE*/
						for(i=0;i<N_CTRLBAR_STYLES;i++)
							if (strstr(pos,aCtrlBarStyleName[i])!=NULL)
							{
								InvFlg++;
								Stl|=aCtrlBarStyleUINT[i];
							}
						SetBarStyle(Stl);
						break;
					case 2: /* DELSTYLE*/
						for(i=0;i<N_CTRLBAR_STYLES;i++)
							if (strstr(pos,aCtrlBarStyleName[i])!=NULL)
							{
								InvFlg++;
								Stl|=aCtrlBarStyleUINT[i];
							}
						SetBarStyle(GetBarStyle()&(Stl^0xFFFFFFFF));
						break;
					}

					Invalidate();
					GetParent()->SendMessage(WM_APP+1);
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


void GPStatusBar::OnParentNotify(UINT message, LPARAM lParam)
{
	CStatusBar::OnParentNotify(message, lParam);
	char txt[100];
	if (message==WM_CREATE || message==WM_DESTROY)
		sprintf(txt,"%d\x7F%d\x7F%X",message/0x10000,(message&0xFFFF),lParam/0x10000);
	else
		sprintf(txt,"%d\x7F%d\x7F%d\x7F%d",message/0x10000,(message&0xFFFF),lParam/0x10000,(lParam&0xFFFF));
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"ParentNotify",txt);
}

HBRUSH GPStatusBar::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CStatusBar::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}

LRESULT GPStatusBar::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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
	else lpr=CStatusBar::WindowProc(message, wParam, lParam);

	return lpr;
}

BOOL GPStatusBar::PreTranslateMessage(MSG* pMsg)
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

	return CStatusBar::PreTranslateMessage(pMsg);
}

void GPStatusBar::OnClose()
{
	if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClose","");
//	CStatusBar::OnClose();
}

void GPStatusBar::OnDragMouseHover()
{
	if (referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(GPC.m_DragDrop.DragName)<0xFFFFFFFFL)
	{
		// Reset the timer.
		::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);

		// Get the current cursor position and window height.
		DWORD dwPos = ::GetMessagePos ();
		CPoint point (LOWORD (dwPos), HIWORD (dwPos));
		ScreenToClient (&point);

		int mParts[255];
		int nParts=GetStatusBarCtrl().GetParts(250,mParts);
		int i;
		for(i=0;i<nParts && mParts[i]<point.x;i++);
		i=i>=nParts || mParts[0]==-1?-2:i;
		CString tmp;
		tmp.Format("%d\x07%s",i,(LPCSTR)GetStatusBarCtrl().GetText(i));
		referGPU[UnitId&0xFFFF]->SendDropHoverEvent(tmp,&GPC.m_DragDrop,&point);
	}
}

void GPStatusBar::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
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
		int nParts=GetStatusBarCtrl().GetParts(250,mParts);
		int i;
		for(i=0;i<nParts && mParts[i]<point->x;i++);
		i=i>=nParts || mParts[0]==-1?-2:i;
		CString tmp;
		tmp.Format("%d\x07%s",i,(LPCSTR)GetStatusBarCtrl().GetText(i));
		referGPU[UnitId&0xFFFF]->SendDropMoveEvent(tmp,pDrDrStruct,point);

		if (mDrop)
			::SetTimer (pDrDrStruct->hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nDelayInterval, NULL);
	}
}

void GPStatusBar::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && referGPU)
	{
		::ScreenToClient(m_hWnd,point);

		int mParts[255];
		int nParts=GetStatusBarCtrl().GetParts(250,mParts);
		int i;
		for(i=0;i<nParts && mParts[i]<point->x;i++);
		i=i>=nParts || mParts[0]==-1?-2:i;

		CString tmp;
		tmp.Format("%d\x07%s",i,(LPCSTR)GetStatusBarCtrl().GetText(i));

		referGPU[UnitId&0xFFFF]->SendDropEvent(tmp,pDrDrStruct,point);
	}
}

DWORD GPStatusBar::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	int parts[150];
	int nParts=GetStatusBarCtrl().GetParts(140,parts);
	int i;
	for(i=0;i<nParts && parts[i]<point.x;i++);

	return i>=nParts || parts[0]==-1?-2:i;
}

LRESULT GPStatusBar::OnNcHitTest(CPoint point)
{
	LRESULT ret=CStatusBar::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

#include "GP_TermDoc.h"

void GPStatusBar::OnKillFocus(CWnd* pNewWnd)
{
	CStatusBar::OnKillFocus(pNewWnd);
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

void GPStatusBar::OnSetFocus(CWnd* pOldWnd)
{
	CStatusBar::OnSetFocus(pOldWnd);
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

void GPStatusBar::OnSize(UINT nType, int cx, int cy)
{
	CStatusBar::OnSize(nType, cx, cy);

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
	}
}

BOOL GPStatusBar::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
	if (referGPU!=NULL)
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
	return CStatusBar::OnChildNotify(message, wParam, lParam, pLResult);
}
