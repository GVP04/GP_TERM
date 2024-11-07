// GPToolBarCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPToolBarCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const UINT  GPToolBarCtrl::uBtnState[]={TBSTATE_CHECKED,TBSTATE_PRESSED,TBSTATE_ENABLED,TBSTATE_HIDDEN,TBSTATE_INDETERMINATE,TBSTATE_WRAP,TBSTATE_ELLIPSES,TBSTATE_MARKED,};
const char *GPToolBarCtrl::cBtnState[]={"_CHECKED|","_PRESSED|","_ENABLED|","_HIDDEN|","_INDETERMINATE|","_WRAP|","_ELLIPSES|","_MARKED|",};


/////////////////////////////////////////////////////////////////////////////
// GPToolBarCtrl
const UINT GPToolBarCtrl::uNMethods=71;
const char *GPToolBarCtrl::cArrMethods[]={
		"UpdateGroup","IsButtonEnabled","IsButtonChecked","IsButtonPressed","IsButtonHidden",
		"IsButtonIndeterminate","SetState","GetState","GetButton","GetButtonCount",
		"GetItemRect","GetRect","GetButtonSize","SetButtonSize","SetBitmapSize",
		"SetRows","GetRows","SetCmdID","GetBitmapFlags","GetDisabledImageList",
		"GetHotImageList","GetImageList","GetTBStyle","GetMaxTextRows","IsButtonHighlighted",
		"SetButtonWidth","SetDisabledImageList","SetHotImageList","SetImageList","SetIndent",
		"SetMaxTextRows","GetAnchorHighlight","SetAnchorHighlight","GetHotItem","SetHotItem",
		"GetInsertMark","SetInsertMark","GetMaxSize","InsertMarkHitTest","GetExtendedStyle",
		"SetExtendedStyle","GetInsertMarkColor","SetInsertMarkColor","MapAccelerator","MoveButton",
		"HitTest","EnableButton","CheckButton","PressButton","HideButton",
		"Indeterminate","MarkButton","GetButtonInfo","SetButtonInfo","SetDrawTextFlags",
		"AddBitmap","AddButton","InsertButton","DeleteButton","CommandToIndex",
		"RestoreState","LoadImages","SaveState","Customize","AddStrings",
		"AutoSize","MultiClick","SetDropMenu","SetUnicodeFormat", "GetUnicodeFormat",
		"TBSetWindowTheme","","","","",
		"","","", "", "", 
	};

//#define TB_GETMETRICS           (WM_USER + 101)
//#define TB_SETMETRICS           (WM_USER + 102)

const char *GPToolBarCtrl::cArrMethodsParams[]={
		"","IdCommand","IdCommand","IdCommand","IdCommand",
		"IdCommand","IdCommand,State","IdCommand","IdIndex","",
		"IdIndex","IdCommand","","szcx,szcy","szcx,szcy",
		"nRows,bLarger","","nIndex,nID","","",
		"","","","","IdCommand",
		"cxMin,cxMax","ImageListName","ImageListName","ImageListName","nIndent",
		"nMaxTextRows","","bAnchor","","IdIndex",
		"","IdIndex,Type","","pox,poy","",
		"ExtendedStyles","","r,g,b","Accelerator","nOldPos,nNewPos",
		"pox,poy","IdCommand,bEnable","IdCommand,bCheck","IdCommand,bPress","IdCommand,bHide",
		"IdCommand,bIndeterminate","IdCommand,bMark","IdCommand","IdCommand,TEXT=;COMMAND=;IMAGE=;LPARAM=;SIZE=;STATE=;STYLE=;TOOLTIP=","DrawTextFlag",
		"nImage,ILName","iBitmap,idCommand,iString,dwData,State,Style;ToolTip","IdIndex,iBitmap,idCommand,iString,dwData,State,Style;ToolTip","IdIndex","IdCommand",
		"SectName,ItemNAme","IdIndex","SectName,ItemNAme","","String1^String2^String3^...",
		"","bMultiClick","iId,iIdPopup","UnicodeFormat","",
		"WindowTheme","","","","",
		"","","", "", "", 
	};

GPToolBarCtrl::GPToolBarCtrl(UINT iUnitId)
{
	m_bEnableMultiClick=FALSE;
	m_EnableClick=TRUE;
	aToolTipArr=new GPTextArray(TOOLBAR_ID_COUNT);
	referGPU=NULL;
	UnitId=iUnitId;
	RefDlgGPMenu= NULL;
	int i;
	for(i=0;i<TOOLBAR_ID_COUNT;i++)	aPopupMenuInd[i]=-1;
}

GPToolBarCtrl::~GPToolBarCtrl()
{
	if (aToolTipArr!=NULL) delete aToolTipArr;
	aToolTipArr=NULL;
}


BEGIN_MESSAGE_MAP(GPToolBarCtrl, CToolBarCtrl)
	//{{AFX_MSG_MAP(GPToolBarCtrl)
	ON_WM_PARENTNOTIFY()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_NCHITTEST()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPToolBarCtrl message handlers



UINT GPToolBarCtrl::DoMethod(const char *iStr, char *oStr)
{
	char met[150];
	strncpy(met,iStr,145);
	met[145]=0;
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc=0;
///////////////////	case : "SetButtonStructSize","GetDropTarget",

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
	int atoiIdIndex=atoi(pos);
	int atoiIdCommand=atoiIdIndex+TOOLBAR_ID_START;

	try
	{
		switch(nfunc)
		{
		case 0: /*UpdateGroup*/
			if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
				referGPU[UnitId&0xFFFF]->UpdateGroup(-123456,GetStyle());
			break;
		case 1: /*IsButtonEnabled*/			retint=IsButtonEnabled(atoiIdCommand);	break;
		case 2: /*IsButtonChecked*/
			retint=IsButtonChecked(atoiIdCommand);
			break;
		case 3: /*IsButtonPressed*/			retint=IsButtonPressed(atoiIdCommand);	break;
		case 4: /*IsButtonHidden*/
			retint=IsButtonHidden(atoiIdCommand);
			break;
		case 5: /*IsButtonIndeterminate*/	retint=IsButtonIndeterminate(atoiIdCommand);	break;
		case 6: /*SetState*/
			{
				char *pos333=new char [(int)strlen(pos)+20];
				strcpy(pos333,pos);
				_strupr(pos333);
				strcat(pos333,"|");
				UINT state=0;
				int i;
				for(i=0;i<8;i++)
					if (strstr(pos333,cBtnState[i])!=0)
					{
						state|=uBtnState[i];
						if (uBtnState[i]==TBSTATE_WRAP) state|=TBSTATE_ENABLED;
					}

				retint=SetState(atoiIdCommand,state);
				AutoSize( );
				delete[] pos333;
			}
			break;
		case 7: /*GetState*/
			if (oStr!=NULL)
			{
				*oStr=0;
				GPTranslateTBCtrlState(GetState(atoiIdCommand),oStr);
			}
			break;
		case 8: /*GetButton*/
			if (oStr!=NULL)
			{
				TBBUTTON tbt={0};
				if (GetButton(atoiIdIndex,&tbt))
				{
					sprintf(oStr,"%d\x7F%d\x7F%d\x7F%ld\x7F",tbt.iBitmap,tbt.idCommand-TOOLBAR_ID_START,tbt.iString,tbt.dwData);
					GPTranslateTBCtrlState(tbt.fsState,oStr);
					strcat(oStr,"\x7F");
					GPTranslateTBCtrlStyle(tbt.fsStyle,oStr);
				}
			}
			break;
		case 9: /*GetButtonCount*/		retint=GetButtonCount();	break;
		case 10: /*GetItemRect*/
			if (oStr!=NULL)
			{
				CRect re;
				if (GetItemRect(atoiIdIndex,&re))
					sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
			}
			break;
		case 11: /*GetRect*/
			if (oStr!=NULL)
			{
				CRect re;
				if (GetRect(atoiIdCommand,&re))
					sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
			}
			break;
		case 12: /*GetButtonSize*/
			if (oStr!=NULL)
			{
				DWORD sz=GetButtonSize();
					sprintf(oStr,"%d\x7F%d",LOWORD(sz),HIWORD(sz));
			}
			break;
		case 13: /*SetButtonSize*/
			{
				CSize sz(0,0);
				m_LastScanf=sscanf(pos,"%d,%d",&sz.cx,&sz.cy);
				retint=SetButtonSize(sz);
				AutoSize( );
			}
			break;
		case 14: /*SetBitmapSize*/
			{
				CSize sz(0,0);
				m_LastScanf=sscanf(pos,"%d,%d",&sz.cx,&sz.cy);
				retint=SetBitmapSize(sz);
				AutoSize( );
			}
			break;
		case 15: /*SetRows*/
			{
				CRect re;
				int nRows=1,bLarger=1;
				m_LastScanf=sscanf(pos,"%d,%d",&nRows,&bLarger);
				SetRows(nRows,bLarger,&re);
				if (oStr!=NULL)
					sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
				AutoSize( );
			}
			break;
		case 16: /*GetRows*/		retint=GetRows();	break;
		case 17: /*SetCmdID*/
			{
				UINT nIndex=0,nID=0;
				m_LastScanf=sscanf(pos,"%d,%d",&nIndex,&nID);
				if (nID>=TOOLBAR_ID_COUNT) nID=0;
				retint=SetCmdID(nIndex,nID+TOOLBAR_ID_START);
			}
			break;
		case 18: /*GetBitmapFlags*/
			if (oStr!=NULL)
			{
				if (GetBitmapFlags()==TBBF_LARGE) strcat(oStr,"TBBF_LARGE");
			}
			break;
		case 19: /*GetDisabledImageList*/
			if (oStr!=NULL)
			{
				int id=GPC.FindImageList(GetDisabledImageList());
				if (id>=0) strcpy(oStr,GPC.a_GPImageList[id].ILName);
			}
			break;
		case 20: /*GetHotImageList*/
			if (oStr!=NULL)
			{
				int id=GPC.FindImageList(GetHotImageList());
				if (id>=0) strcpy(oStr,GPC.a_GPImageList[id].ILName);
			}
			break;
		case 21: /*GetImageList*/
			if (oStr!=NULL)
			{
				int id=GPC.FindImageList(GetImageList());
				if (id>=0) strcpy(oStr,GPC.a_GPImageList[id].ILName);
			}
			break;
		case 22: /*GetTBStyle*/
			if (oStr!=NULL)
			{
				GetObjStlStr(oStr, GetStyle(), N_TOOLBARCTRL_STYLES,  aToolBarCtrlStyleName, aToolBarCtrlStyleUINT, aToolBarCtrlStyleMask);
			}

			break;
		case 23: /*GetMaxTextRows*/		retint=GetMaxTextRows();	break;
		case 24: /*IsButtonHighlighted*/	retint=IsButtonHighlighted(atoiIdCommand);	break;
		case 25: /*SetButtonWidth*/
			{
				int cxMin=10,cxMax =48;
				m_LastScanf=sscanf(pos,"%d,%d",&cxMin,&cxMax);
				retint=SetButtonWidth(cxMin,cxMax);
				AutoSize( );
			}
			break;
		case 26: /*SetDisabledImageList*/
			if ((atoiIdIndex=GPC.GetImageListId(pos))>=0)
				SetDisabledImageList(&(GPC.a_GPImageList[atoiIdIndex].m_IL));
			AutoSize( );
			break;
		case 27: /*SetHotImageList*/
			if ((atoiIdIndex=GPC.GetImageListId(pos))>=0)
				SetHotImageList(&(GPC.a_GPImageList[atoiIdIndex].m_IL));
			AutoSize( );
			break;
		case 28: /*SetImageList*/
			if ((atoiIdIndex=GPC.GetImageListId(pos))>=0)
				SetImageList(&(GPC.a_GPImageList[atoiIdIndex].m_IL));
			AutoSize( );
			break;
		case 29: /*SetIndent*/			retint=SetIndent(atoiIdIndex);	AutoSize( );	break;
		case 30: /*SetMaxTextRows*/ 	retint=SetMaxTextRows(atoiIdIndex);		break;
		case 31: /*GetAnchorHighlight*/	retint=GetAnchorHighlight();		break;
		case 32: /*SetAnchorHighlight*/	retint=SetAnchorHighlight(atoiIdIndex);	break;
		case 33: /*GetHotItem*/			retint=GetHotItem();				break;
		case 34: /*SetHotItem*/ 		retint=SetHotItem(atoiIdIndex);		break;
		case 35: /*GetInsertMark*/
			if (oStr!=NULL)
			{
				TBINSERTMARK tbim={0};
				GetInsertMark(&tbim);
				sprintf(oStr,"%d\x7F%s",tbim.iButton,tbim.dwFlags==0?"BEFORE":tbim.dwFlags==TBIMHT_AFTER?"AFTER":"BACKGROUND");
			}
			break;
		case 36: /*SetInsertMark*/
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				TBINSERTMARK tbim={0};
				tbim.iButton=atoiIdIndex;
				_strupr(pos333);
				if (strstr(pos333,"AFTER")!=NULL) tbim.dwFlags=TBIMHT_AFTER;
					else
					if (strstr(pos333,"BACKGROUND")!=NULL) tbim.dwFlags=TBIMHT_BACKGROUND;

				SetInsertMark(&tbim);
				AutoSize( );
				delete[] pos333;
			}
			break;
		case 37: /*GetMaxSize*/
			{
				CSize sz;
				if (GetMaxSize(&sz))	sprintf(oStr,"%d\x7F%d",sz.cx,sz.cy);
				else retint=-1;
			}
			break;
		case 38: /*InsertMarkHitTest*/
			if (oStr!=NULL)
			{
				TBINSERTMARK tbim={0};
				CPoint po(0,0);

				m_LastScanf=sscanf(pos,"%d,%d",&po.x,&po.y);

				retint=InsertMarkHitTest(&po,&tbim);
				sprintf(oStr,"%d\x7F%s",tbim.iButton,tbim.dwFlags==TBIMHT_AFTER?"AFTER":tbim.dwFlags==TBIMHT_BACKGROUND?"BACKGROUND":"0");

			}
			break;
		case 39: /*GetExtendedStyle*/
			if (oStr!=NULL)
				GetObjStlStr(oStr, GetExtendedStyle(), N_TOOLBARCTRL_EX_STYLES,  aToolBarCtrlExStyleName, aToolBarCtrlExStyleUINT, aToolBarCtrlExStyleMask);
			break;

		case 40: /*SetExtendedStyle*/
			{
				UINT stl=0;
				int i;
				for(i=0;i<N_TOOLBARCTRL_EX_STYLES;i++)
					if (strstr(pos,aToolBarCtrlExStyleName[i])) stl|=aToolBarCtrlExStyleUINT[i];

				stl=SetExtendedStyle(stl);
				Invalidate();
			}
			break;
		case 41: /*GetInsertMarkColor*/
			if (oStr!=NULL)
			{	UINT cref=GetInsertMarkColor();
				sprintf(oStr,"%d%c%d%c%d",(cref&0xFF),7,((cref/0x100)&0xFF),7,((cref/0x10000)&0xFF));
			}
			break;
		case 42: /*SetInsertMarkColor*/
			{
				UINT r=0,g=0,b=0,cref=0;

				m_LastScanf=sscanf(pos,"%d,%d,%d",&r,&g,&b);
				cref=SetInsertMarkColor(RGB(r,g,b));
				if (oStr!=NULL)
					sprintf(oStr,"%d%c%d%c%d",(cref&0xFF),7,((cref/0x100)&0xFF),7,((cref/0x10000)&0xFF));
			}
			break;
		case 43: /*MapAccelerator*/
			{
				UINT nId;
				MapAccelerator(*pos,&nId);
				retint=nId;
			}
			break;
		case 44: /*MoveButton*/
			{
				UINT nOldPos=0,nNewPos=0;
				m_LastScanf=sscanf(pos,"%d,%d",&nOldPos,&nNewPos);
				retint=MoveButton(nOldPos,nNewPos);
				AutoSize( );
			}
			break;
		case 45: /*HitTest*/
			{
				CPoint po(0,0);
				m_LastScanf=sscanf(pos,"%d,%d",&po.x,&po.y);
				retint=HitTest(&po);
			}
			break;
		case 46: /*EnableButton*/
		case 47: /*CheckButton*/
		case 48: /*PressButton*/
		case 49: /*HideButton*/
		case 50: /*Indeterminate*/
		case 51: /*MarkButton*/
			{
				int IdCommand=0,bEnable = TRUE;
				m_LastScanf=sscanf(pos,"%d,%d",&IdCommand,&bEnable);
				IdCommand+=TOOLBAR_ID_START;
				switch(nfunc)
				{
				case 46: /*EnableButton*/	retint=EnableButton(IdCommand,bEnable);	break;
				case 47: /*CheckButton*/ 	retint=CheckButton(IdCommand,bEnable);	break;
				case 48: /*PressButton*/	retint=PressButton(IdCommand,bEnable);	break;
				case 49: /*HideButton*/		retint=HideButton(IdCommand,bEnable);		break;
				case 50: /*Indeterminate*/	retint=Indeterminate(IdCommand,bEnable);	break;
				case 51: /*MarkButton*/		retint=MarkButton(IdCommand,bEnable);		break;
				}
			}
			AutoSize( );
			break;

		case 52: /*GetButtonInfo*/
			if (oStr!=NULL)
			{
				TBBUTTONINFO tbti={0};
				tbti.cbSize=sizeof(tbti);
				tbti.dwMask=TBIF_COMMAND|TBIF_IMAGE|TBIF_LPARAM|TBIF_SIZE|TBIF_STATE|TBIF_STYLE|TBIF_TEXT;
				char str[256];
				*str=0;
				tbti.cchText=250;
				tbti.pszText=str;
				tbti.idCommand=atoiIdCommand;
				GetButtonInfo(atoiIdCommand,&tbti);
				sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d\x7F%s\x7F",tbti.idCommand-TOOLBAR_ID_START,tbti.iImage,tbti.cx,tbti.lParam,str);
				GPTranslateTBCtrlState(tbti.fsState,oStr);
				strcat(oStr,"\x7F");
				GPTranslateTBCtrlStyle(tbti.fsStyle,oStr);
				strcat(oStr,"\x7F");
				strcat(oStr,tbti.pszText);
			}
			break;
		case 53: /*SetButtonInfo*/ // SetButtonInfo  nId,COMMAND=10;IMAGE=2 ......
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				TBBUTTONINFO tbti={0};
				tbti.cbSize=sizeof(tbti);
				UINT  uMask[8]={TBIF_TEXT,TBIF_COMMAND,TBIF_IMAGE,TBIF_LPARAM,TBIF_SIZE,TBIF_STATE,TBIF_STYLE,};
				char *cMask[8]={"TEXT=","COMMAND=","IMAGE=","LPARAM=","SIZE=","STATE=","STYLE=","TOOLTIP=",};
				char *cpos[8],*pos2;
				UINT tmpUI;
				int i;

				for(i=0;i<8;i++)
					if ((cpos[i]=strstr(pos333,cMask[i]))!=NULL)
						cpos[i]+=(int)strlen(cMask[i]);

				for(i=0;i<8;i++)
					if (cpos[i]!=NULL)
					{
						if ((pos2=strchr(cpos[i],';'))!=NULL) *pos2=0;
						if (i>0) _strupr(cpos[i]);

						switch(i)
						{
						case 0:
							tbti.dwMask|=TBIF_TEXT;
							tbti.cchText=(int)strlen(cpos[i]+5);
							tbti.pszText=cpos[i];
							break;
						case 1:
							tbti.dwMask|=TBIF_COMMAND;
							tbti.idCommand=(atoi(cpos[i])%TOOLBAR_ID_COUNT)+TOOLBAR_ID_START;
							break;
						case 2:
							tbti.dwMask|=TBIF_IMAGE;
							tbti.iImage=atoi(cpos[i]);
							break;
						case 3:
							tbti.dwMask|=TBIF_LPARAM;
							tbti.lParam=atol(cpos[i]);
							break;
						case 4:
							tbti.dwMask|=TBIF_SIZE;
							tbti.cx=(WORD)atoi(cpos[i]);
							break;
						case 5:
							tbti.dwMask|=TBIF_STATE;
							GPTranslateTBCtrlState(cpos[i],tmpUI);
							tbti.fsState=(unsigned char)tmpUI;
							break;
						case 6:
							tbti.dwMask|=TBIF_STYLE;
							GPTranslateTBCtrlStyle((const char *)cpos[i],tmpUI);
							tbti.fsStyle=(unsigned char)tmpUI;
							break;
						case 7:
							if (tbti.idCommand>=TOOLBAR_ID_START && tbti.idCommand<=TOOLBAR_ID_END)
								aToolTipArr->SetItem(tbti.idCommand-TOOLBAR_ID_START,pos2);
							break;
						}
					}
				retint=SetButtonInfo(atoiIdCommand,&tbti);
				AutoSize( );
				delete[] pos333;
			}
			break;
		case 54: /*SetDrawTextFlags*/
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				UINT dwMask=0;
				_strupr(pos333);
				int i;
				for(i=0;i<N_DRAWTEXT_FLAGS;i++)
					if (strstr(pos333,aDrawTextFlagName[i])!=NULL)  dwMask|=aDrawTextFlagUINT[i];
				SetDrawTextFlags(dwMask,dwMask);
				delete[] pos333;
			}
			break;
		case 55: /*AddBitmap*/
			{
				const char *name=strchr(pos,',');
				if (name==NULL) name="MISCL";
				else name++;
				GPImageList *SMainIl;
				int ImgLId=atoi(pos);

				if ((ImgLId=GPC.GetImageListId(name))>=0 && (SMainIl=&(GPC.a_GPImageList[ImgLId]))!=NULL)
				{
					ICONINFO ii={0};
					GetIconInfo(SMainIl->m_IL.ExtractIcon(atoi(pos)),&ii);
					retint=AddBitmap(1, CBitmap::FromHandle(ii.hbmColor));
				}
				else retint=-1;
				AutoSize( );
			}
			break;
		case 56: /*AddButton*/
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				TBBUTTON tbt={0};
				int iWidth=-1;
				m_LastScanf=sscanf(pos333,"%d,%d,%d,%d,%d",&tbt.iBitmap,&tbt.idCommand,&tbt.iString,&tbt.dwData,&iWidth);
				tbt.idCommand=(tbt.idCommand%TOOLBAR_ID_COUNT)+TOOLBAR_ID_START;
				char *pos2=strchr(pos333,';');
				if (pos2++!=NULL)
				{
					if (tbt.idCommand>=TOOLBAR_ID_START && tbt.idCommand<=TOOLBAR_ID_END)
							aToolTipArr->SetItem(tbt.idCommand-TOOLBAR_ID_START,pos2);
				}
				_strupr(pos333);
				UINT tmpUI;
				GPTranslateTBCtrlState(pos333,tmpUI);
				tbt.fsState=(unsigned char)tmpUI;
				GPTranslateTBCtrlStyle(pos333,tmpUI);
				tbt.fsStyle=(unsigned char)tmpUI;
				AddButtons(1,&tbt);
				if (iWidth>0)
				{
					TBBUTTONINFO tbti={0};
					tbti.cbSize=sizeof(tbti);
					tbti.dwMask=TBIF_SIZE;
					tbti.cx=iWidth;
					retint=SetButtonInfo(tbt.idCommand,&tbti);
				}
				AutoSize( );
				delete[] pos333;
			}
			break;
		case 57: /*InsertButton*/
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				TBBUTTON tbt={0};
				m_LastScanf=sscanf(pos333,"%d,%d,%d,%d,%d",&atoiIdIndex,&tbt.iBitmap,&tbt.idCommand,&tbt.iString,&tbt.dwData);
				tbt.idCommand=(tbt.idCommand%TOOLBAR_ID_COUNT)+TOOLBAR_ID_START;
				char *pos2=strchr(pos333,';');
				if (pos2++!=NULL)
				{
					if (tbt.idCommand>=TOOLBAR_ID_START && tbt.idCommand<=TOOLBAR_ID_END)
							aToolTipArr->SetItem(tbt.idCommand-TOOLBAR_ID_START,pos2);
				}
				UINT tmpUI;
				_strupr(pos333);
				GPTranslateTBCtrlState(pos333,tmpUI);
				tbt.fsState=(unsigned char)tmpUI;
				GPTranslateTBCtrlStyle(pos333,tmpUI);
				tbt.fsStyle=(unsigned char)tmpUI;
				InsertButton(atoiIdIndex,&tbt);
				AutoSize( );
				delete[] pos333;
			}
			break;
		case 58: /*DeleteButton*/		retint=DeleteButton(atoiIdIndex);AutoSize( );break;
		case 59: /*CommandToIndex*/
			retint=CommandToIndex((atoiIdIndex%TOOLBAR_ID_COUNT)+TOOLBAR_ID_START);
			break;
		case 60: /*RestoreState*/
		case 62: /*SaveState*/
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				HKEY curkey;
				RegOpenKeyEx(HKEY_CURRENT_USER,AfxGetApp()->m_pszRegistryKey,0,KEY_ALL_ACCESS,&curkey);
				char *pos2=strchr(pos333,',');
				if (pos2!=NULL) *(pos2++)=0;
				else pos2="";
				if (nfunc==60)	RestoreState(curkey,pos333,pos2);
				else			SaveState(curkey,pos333,pos2);
				RegCloseKey(curkey);
				delete[] pos333;
			}
			break;
		case 61: /*LoadImages*/
				LoadImages(atoiIdIndex, HINST_COMMCTRL);
			break;
		case 63: /*Customize*/			Customize();	break;
		case 64: /*AddStrings*/
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				char *pos2=pos333;
				while(*pos2!=0)
				{
					if (*pos2==GPC.DelimiterIn1) *pos2=0;
					pos2++;
				}
				*(++pos2)=0;
				retint=AddStrings(pos333);
				AutoSize( );
				delete[] pos333;
			}
			break;
		case 65: /*AutoSize*/		AutoSize(); break;
		case 66: /*MultiClick*/		m_bEnableMultiClick=atoi(pos);	break;
		case 67: /*SetDropMenu*/
			{
				int iId=0,iIdPopup=-1;
				m_LastScanf=sscanf(pos,"%d,%d",&iId,&iIdPopup);
				if (iId>=0 && iId<=TOOLBAR_ID_COUNT && iIdPopup>=MENU_POPUP_START && iIdPopup<=MENU_POPUP_START+MENU_POPUP_COUNT)
					aPopupMenuInd[iId]=iIdPopup;
			}
			break;
		case 68: /*SetUnicodeFormat*/
			retint=SendMessage(TB_SETUNICODEFORMAT, (WPARAM)atoi(pos),0);
			break;
		case 69: /*GetUnicodeFormat*/
			retint=SendMessage(TB_SETUNICODEFORMAT,0,0);
			break;
		case 70: /*TBSetWindowTheme*/
			{
				CString tmps=pos;
				BSTR bstr=tmps.AllocSysString();
				retint=SendMessage(TB_SETWINDOWTHEME,0,(LPARAM)bstr);
				SysFreeString(bstr);
			}
			break;


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
		GPC.m_ErrReport.GPWriteErrorLog("GPToolBarCtrl", "DoMethod",iStr);
		delete[] str;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
	return nfunc;
}

UINT GPToolBarCtrl::GPSetProperty(char *iStr)
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
					int InvFlg=0;
					char *postmp=strstr(pos,"&U");
					int tbctrlchange=0;

					if (postmp!=NULL)
					{
						UINT es=GetStyle();
						UINT tmpstl=0;
						m_LastScanf=sscanf(postmp,"&U%X",&tmpstl);
						InvFlg++;
						tbctrlchange++;
						switch(propnum)
						{
						case 2: /* STYLE*/
						case 0: /* ADDSTYLE*/	SetStyle(es|tmpstl);			break;
						case 1: /* DELSTYLE*/	SetStyle((es|tmpstl)^tmpstl);	break;
						}
						if (InvFlg!=0) Invalidate();
					}
					else
					{
						strcat(pos,"|");
						UINT Stl=0;
						switch(propnum)
						{
						case 0: /* ADDSTYLE*/	Stl=GetStyle();
						case 2: /* STYLE*/
							for(i=0;i<N_TOOLBARCTRL_STYLES;i++)
								if (strstr(pos,aToolBarCtrlStyleName[i])!=NULL)
								{
									InvFlg++;
									Stl|=aToolBarCtrlStyleUINT[i];
									tbctrlchange++;
								}
							SetStyle(Stl);
							break;
						case 1: /* DELSTYLE*/
							for(i=0;i<N_TOOLBARCTRL_STYLES;i++)
								if (strstr(pos,aToolBarCtrlStyleName[i])!=NULL)
								{
									InvFlg++;
									Stl|=aToolBarCtrlStyleUINT[i];
									tbctrlchange++;
								}
							SetStyle(GetStyle()&(Stl^0xFFFFFFFF));
							break;
						}
					}

					postmp=strstr(pos,"&X");

					if (postmp!=NULL)
					{
						UINT es=GetExtendedStyle();
						UINT tmpstl=0;
						m_LastScanf=sscanf(postmp,"&X%X",&tmpstl);
						InvFlg++;
						switch(propnum)
						{
						case 2: /* STYLE*/
						case 0: /* ADDSTYLE*/	SetExtendedStyle(es|tmpstl);			break;
						case 1: /* DELSTYLE*/	SetExtendedStyle((es|tmpstl)^tmpstl);	break;
						}
						if (InvFlg!=0) Invalidate();
						tbctrlchange++;
					}
					else
					{
						strcat(pos,"|");
						UINT Stl=0;
						switch(propnum)
						{
						case 0: /* ADDSTYLE*/	Stl=GetExtendedStyle();
						case 2: /* STYLE*/
							for(i=0;i<N_TOOLBARCTRL_EX_STYLES;i++)
								if (strstr(pos,aToolBarCtrlExStyleName[i])!=NULL)
								{
									InvFlg++;
									tbctrlchange++;
									Stl|=aToolBarCtrlExStyleUINT[i];
								}
							SetExtendedStyle(Stl);
							break;
						case 1: /* DELSTYLE*/
							for(i=0;i<N_TOOLBARCTRL_EX_STYLES;i++)
								if (strstr(pos,aToolBarCtrlExStyleName[i])!=NULL)
								{
									InvFlg++;
									tbctrlchange++;
									Stl|=aToolBarCtrlExStyleUINT[i];
								}
							SetExtendedStyle(GetExtendedStyle()&(Stl^0xFFFFFFFF));
							break;
						}
					}


					for(i=0;i<N_COMCTRL_STYLES;i++)
						if (strstr(pos,aComCtrlStyleName[i])!=NULL)
						{
							InvFlg++;
							tbctrlchange++;
							switch(propnum)
							{
							case 2: /* STYLE*/
							case 0: /* ADDSTYLE*/	ModifyStyle(0,aComCtrlStyleUINT[i]);break;
							case 1: /* DELSTYLE*/	ModifyStyle(aComCtrlStyleUINT[i],0);break;
							}
						}


					if (tbctrlchange!=0)
					{
						UINT Stl=GetStyle();
						SetStyle(Stl^TBSTYLE_WRAPABLE);
						SetStyle(Stl);
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

void GPToolBarCtrl::OnParentNotify(UINT message, LPARAM lParam)
{
	CToolBarCtrl::OnParentNotify(message, lParam);
//TRACE("PN %X,%d\n",message,lParam);

	char txt[100];
	if (message==WM_CREATE || message==WM_DESTROY)
		sprintf(txt,"%d\x7F%d\x7F%X",message/0x10000,(message&0xFFFF),lParam/0x10000);
	else
		sprintf(txt,"%d\x7F%d\x7F%d\x7F%d",message/0x10000,(message&0xFFFF),lParam/0x10000,(lParam&0xFFFF));
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"ParentNotify",txt);

}

HBRUSH GPToolBarCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CToolBarCtrl::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}

LRESULT GPToolBarCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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

	if (message==WM_NOTIFY)
	{
		LPNMHDR lpnm=((LPNMHDR)lParam);
		LPNMTOOLBAR lpnmTB= ((LPNMTOOLBAR)lParam);
		LPNMTTDISPINFO lpnmTTDI= ((LPNMTTDISPINFO)lParam);
		if (lpnm->code==TTN_GETDISPINFO)
		{
			LPTOOLTIPTEXT lpttt;
			lpttt = (LPTOOLTIPTEXT) lParam;
			lpttt->hinst = NULL;

			if (lpttt->hdr.idFrom>=TOOLBAR_ID_START && lpttt->hdr.idFrom<=TOOLBAR_ID_END)
				lpttt->lpszText=(char *)aToolTipArr->GetItem(lpttt->hdr.idFrom-TOOLBAR_ID_START);
		}
		else
		if (lpnm->code==TTN_GETDISPINFOW)
		{
			LPTOOLTIPTEXTW lpttt;
			lpttt = (LPTOOLTIPTEXTW) lParam;
			lpttt->hinst = NULL;
			if (lpttt->hdr.idFrom>=TOOLBAR_ID_START && lpttt->hdr.idFrom<=TOOLBAR_ID_END)
				mbstowcs( lpttt->szText, (const char *)aToolTipArr->GetItem(lpttt->hdr.idFrom-TOOLBAR_ID_START), 79);
		}
	}


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
	else lpr=CToolBarCtrl::WindowProc(message, wParam, lParam);

	return lpr;
}

BOOL GPToolBarCtrl::PreTranslateMessage(MSG* pMsg)
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
//TRACE("PRE%X,%d,%d\n",pMsg->message,pMsg->wParam,pMsg->lParam);

	return CToolBarCtrl::PreTranslateMessage(pMsg);
}

void GPToolBarCtrl::OnClose()
{

	if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClose","");
//	CToolBarCtrl::OnClose();
}


void GPToolBarCtrl::GPTranslateTBCtrlState(UINT iState, char *oStr)
{
	if (oStr!=NULL)
	{
		int i;
		for(i=0;i<8;i++)
			if ((iState&uBtnState[i])==uBtnState[i])	strcat(oStr,cBtnState[i]);
	}
}

void GPToolBarCtrl::GPTranslateTBCtrlStyle(UINT iStyle, char *oStr)
{
	if (oStr!=NULL)
	{
		int i;
		for(i=0;i<N_TOOLBARCTRL_STYLES;i++)
			if ((iStyle&aToolBarCtrlStyleUINT[i])==aToolBarCtrlStyleUINT[i])	strcat(oStr,aToolBarCtrlStyleName[i]);
	}
}


void GPToolBarCtrl::GPTranslateTBCtrlState(const char *oStr, UINT & iState)
{
	iState=0;
	if (oStr!=NULL)
	{
		int i;
		for(i=0;i<8;i++)
			if (strstr(oStr,cBtnState[i])!=NULL)  iState|=uBtnState[i];
	}
}

void GPToolBarCtrl::GPTranslateTBCtrlStyle(const char *oStr, UINT & iStyle)
{
	iStyle=0;
	if (oStr!=NULL)
	{
		int i;
		for(i=0;i<N_TOOLBARCTRL_STYLES;i++)
			if (strstr(oStr,aToolBarCtrlStyleName[i])!=NULL)  iStyle|=aToolBarCtrlStyleUINT[i];
	}
}




//DEL BOOL GPToolBarCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
//DEL {
//DEL //TRACE("OnNotify %d,%d\n",wParam,lParam);
//DEL 
//DEL char str[500];*str=0;
//DEL CRect re(0,0,0,0);
//DEL *pResult=TRUE;
//DEL LPNMTOOLBAR lpnm= (LPNMTOOLBAR)lParam;
//DEL 	switch(lpnm->hdr.code)
//DEL 	{
//DEL 	case NM_RDBLCLK:
//DEL 	case NM_RCLICK:
//DEL 	case NM_CLICK:
//DEL 	case NM_DBLCLK:
//DEL 	case NM_KILLFOCUS:
//DEL 	case NM_OUTOFMEMORY:
//DEL 	case NM_RETURN:
//DEL 	case NM_SETFOCUS:
//DEL 	case TBN_CUSTHELP:
//DEL 	case TBN_BEGINADJUST:
//DEL 	case TBN_TOOLBARCHANGE:
//DEL 	case TBN_RESET:
//DEL 	case TBN_ENDADJUST:
//DEL 	case TBN_RESTORE:
//DEL 	case TBN_SAVE:
//DEL 	case TBN_INITCUSTOMIZE:
//DEL 	case TBN_GETINFOTIP:
//DEL 	case TBN_GETDISPINFO:
//DEL 		sprintf(str,"%d",((LPNMHDR) lParam)->idFrom-TOOLBAR_ID_START);
//DEL 		if (referGPU!=NULL)
//DEL 		switch(((LPNMHDR)lParam)->code)
//DEL 		{
//DEL 		case TBN_BEGINADJUST:
//DEL 			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnBeginAdjust",str);
//DEL 			break;
//DEL 		case TBN_TOOLBARCHANGE:
//DEL 			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnToolBarChange",str);
//DEL 			break;
//DEL 		case TBN_RESET:
//DEL 			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnReset",str);
//DEL 			break;
//DEL 		case NM_RDBLCLK:
//DEL 			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnRDblClick",str);
//DEL 			break;
//DEL 		case NM_RCLICK:
//DEL 			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnRClick",str);
//DEL 			break;
//DEL 		case TBN_CUSTHELP:
//DEL 			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnCustHelp",str);
//DEL 			break;
//DEL 		case NM_CLICK:
//DEL 			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNClick",str);
//DEL 			break;
//DEL 		case NM_DBLCLK:
//DEL 			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNDblClick",str);
//DEL 			break;
//DEL 		case NM_KILLFOCUS:
//DEL 			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNKillFocus",str);
//DEL 			break;
//DEL 		case NM_OUTOFMEMORY:
//DEL 			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNOutOfMemory",str);
//DEL 			break;
//DEL 		case NM_RETURN:
//DEL 			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNReturn",str);
//DEL 			break;
//DEL 		case NM_SETFOCUS:
//DEL 			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNSetFocus",str);
//DEL 			break;
//DEL 		case TBN_ENDADJUST:
//DEL 			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNEndAdjust",str);
//DEL 			break;
//DEL 		case TBN_RESTORE:
//DEL 			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNRestore",str);
//DEL 			break;
//DEL 		case TBN_SAVE:
//DEL 			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNSave",str);
//DEL 			break;
//DEL 		case TBN_INITCUSTOMIZE:
//DEL 			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNInitCustomize",str);
//DEL 			break;
//DEL 		case TBN_GETINFOTIP:
//DEL 			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNGetInfotip",str);
//DEL 			break;
//DEL 		case TBN_GETDISPINFO:
//DEL 			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNGetDispInfo",str);
//DEL 			break;
//DEL 		}
//DEL 		break;
//DEL 
//DEL 	case TBN_QUERYINSERT:
//DEL 	case TBN_QUERYDELETE:
//DEL 	case TBN_BEGINDRAG :
//DEL 	case TBN_ENDDRAG:
//DEL 	case TBN_DRAGOUT:
//DEL 	case TBN_DROPDOWN:
//DEL 	case TBN_DELETINGBUTTON:
//DEL 	case TBN_GETBUTTONINFO:
//DEL 		{
//DEL 			try
//DEL 			{
//DEL 				LPNMTOOLBAR lpnmTB=(LPNMTOOLBAR)lParam;
//DEL 				GetButton(CommandToIndex(lpnmTB->iItem),&lpnmTB->tbButton);
//DEL 				GetItemRect(CommandToIndex(lpnmTB->iItem),&re);
//DEL 				ClientToScreen(&re);
//DEL 				sprintf(str,"%d\x7F%d\x7F%s\x7F%d\x07%d\x07%d\x07%d",
//DEL 						lpnmTB->iItem-TOOLBAR_ID_START,
//DEL 						CommandToIndex(lpnmTB->iItem),
//DEL 						lpnmTB->pszText==NULL?"":lpnmTB->pszText,
//DEL 						re.top,
//DEL 						re.left,
//DEL 						re.bottom,
//DEL 						re.right);
//DEL 
//DEL 				if (referGPU!=NULL)
//DEL 					switch(((LPNMHDR)lParam)->code)
//DEL 					{
//DEL 					case TBN_QUERYINSERT:
//DEL 						referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnQueryInsert",str);
//DEL 						break;
//DEL 					case TBN_QUERYDELETE:
//DEL 						referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnQueryDelete",str);
//DEL 						break;
//DEL 					case TBN_BEGINDRAG :
//DEL 						referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnBeginDrag",str);
//DEL 						break;
//DEL 					case TBN_ENDDRAG:
//DEL 						referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnEndDrag",str);
//DEL 						break;
//DEL 					case TBN_DRAGOUT:
//DEL 						referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDragOut",str);
//DEL 						break;
//DEL 					case TBN_DELETINGBUTTON:
//DEL 						referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDeletingButton",str);
//DEL 						break;
//DEL 					case TBN_GETBUTTONINFO:
//DEL 						referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnGetButtonInfo",str);
//DEL 						break;
//DEL 					case TBN_DROPDOWN:
//DEL 						referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDropDown",str);
//DEL 						if (
//DEL 							lpnmTB->iItem>=TOOLBAR_ID_START && lpnmTB->iItem<=TOOLBAR_ID_END &&
//DEL 							aPopupMenuInd[lpnmTB->iItem-TOOLBAR_ID_START]>=MENU_POPUP_START &&
//DEL 							aPopupMenuInd[lpnmTB->iItem-TOOLBAR_ID_START]<=MENU_POPUP_START+MENU_POPUP_COUNT &&
//DEL 							RefDlgGPMenu!=NULL && *RefDlgGPMenu!=NULL
//DEL 							)
//DEL 							(*RefDlgGPMenu)->GPTrackPopupMenu(aPopupMenuInd[lpnmTB->iItem-TOOLBAR_ID_START],TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL,re.left,re.bottom,NULL);
//DEL 							*pResult=TBDDRET_DEFAULT;
//DEL 						break;
//DEL 					}
//DEL 			}
//DEL 			catch(...)
//DEL 			{GPWriteErrorLog("ERROR GPToolBarCtrl.cpp(1137):", "");*str=0;}
//DEL 
//DEL 		}
//DEL 		break;
//DEL   }
//DEL 
//DEL 	if ((wParam&0xFFFF)==(UnitId&0xFFFF)+50000 || wParam>=TOOLBAR_ID_START && wParam<=TOOLBAR_ID_END) return TRUE;
//DEL 
//DEL 	return TRUE;
//DEL //	return CToolBarCtrl::OnNotify(wParam, lParam, pResult);
//DEL }

void GPToolBarCtrl::OnTimer(UINT nIDEvent)
{
	if (nIDEvent==CLICK_TIMER_ID)
	{
		KillTimer(nIDEvent);
		m_EnableClick=TRUE;
	}

	CToolBarCtrl::OnTimer(nIDEvent);
}

void GPToolBarCtrl::SetDropDownMenu(GPMenu **iDlgGPMenu)
{
	RefDlgGPMenu=iDlgGPMenu;
}

void GPToolBarCtrl::OnDragMouseHover()
{
	if (referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(GPC.m_DragDrop.DragName)<0xFFFFFFFFL)
	{
		// Reset the timer.
		::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);

		// Get the current cursor position and window height.
		DWORD dwPos = ::GetMessagePos();
		CPoint point(LOWORD(dwPos), HIWORD(dwPos));
		ScreenToClient(&point);

		int nItem = HitTest(&point);
		if (nItem<0) nItem=-nItem;
		TBBUTTONINFO tbb={0};
		tbb.cbSize=sizeof(tbb);
		tbb.dwMask=TBIF_TEXT;
		tbb.pszText=new char [300];
		*tbb.pszText=0;
		tbb.cchText=250;
		GetButtonInfo(nItem,&tbb);


		CString tmp;
		tmp.Format("%d\x07%s",nItem,tbb.pszText);
		referGPU[UnitId&0xFFFF]->SendDropHoverEvent(tmp,&GPC.m_DragDrop,&point);
		delete[] tbb.pszText;
	}
}

void GPToolBarCtrl::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
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

		DWORD iItem=NULL;
		BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
		// Highlight the drop target if the cursor is over an item.
		if (mDrop)
			iItem = HighlightDropTarget(pDrDrStruct, CPoint(*point));
		// Modify the cursor to provide visual feedback to the user. Note: It's important to do this AFTER the call to DragMove.
		::SetCursor(iItem == 0xFFFFFFFF ?
			AfxGetApp()->LoadStandardCursor(IDC_NO) :
			(HCURSOR) ::GetClassLong(m_hWnd, GCL_HCURSOR));

		int nItem = HitTest(point);
		if (nItem<0) nItem=-nItem;
		TBBUTTONINFO tbb={0};
		tbb.cbSize=sizeof(tbb);
		tbb.dwMask=TBIF_TEXT;
		tbb.pszText=new char [300];
		*tbb.pszText=0;
		tbb.cchText=250;
		GetButtonInfo(nItem,&tbb);

		CString tmp;
		tmp.Format("%d\x07%s",nItem,tbb.pszText);
		referGPU[UnitId&0xFFFF]->SendDropMoveEvent(tmp,pDrDrStruct,point);
		delete[] tbb.pszText;

		if (mDrop)
			::SetTimer(pDrDrStruct->hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nDelayInterval, NULL);
	}
}

void GPToolBarCtrl::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && referGPU)
	{
		::ScreenToClient(m_hWnd,point);

		int nItem = HitTest(point);
		if (nItem<0) nItem=-nItem;
		TBBUTTONINFO tbb={0};
		tbb.cbSize=sizeof(tbb);
		tbb.dwMask=TBIF_TEXT;
		tbb.pszText=new char [300];
		*tbb.pszText=0;
		tbb.cchText=250;
		GetButtonInfo(nItem,&tbb);


		CString tmp;
		tmp.Format("%d\x07%s",nItem,tbb.pszText);
		referGPU[UnitId&0xFFFF]->SendDropEvent(tmp,pDrDrStruct,point);
		delete[] tbb.pszText;
	}
}

DWORD GPToolBarCtrl::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	return 0xFFFFFFFF;
}

LRESULT GPToolBarCtrl::OnNcHitTest(CPoint point)
{
	LRESULT ret=CToolBarCtrl::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

#include "GP_TermDoc.h"

void GPToolBarCtrl::OnKillFocus(CWnd* pNewWnd)
{
	CToolBarCtrl::OnKillFocus(pNewWnd);
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

void GPToolBarCtrl::OnSetFocus(CWnd* pOldWnd)
{
	CToolBarCtrl::OnSetFocus(pOldWnd);
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

void GPToolBarCtrl::OnSize(UINT nType, int cx, int cy)
{
	CToolBarCtrl::OnSize(nType, cx, cy);

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
	}
}

BOOL GPToolBarCtrl::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
	BOOL ret=TRUE;
	if (message==WM_COMMAND && referGPU!=NULL)
	{
		if (wParam>=TOOLBAR_ID_START && wParam<=TOOLBAR_ID_END)
		{
			char str[300];
			TBBUTTON tbt={0};
			int btIndex=-1;
			if (GetButton(btIndex=CommandToIndex(wParam),&tbt))
			{
				sprintf(str,"%d\x7F%d\x7F%d\x7F%ld\x7F",tbt.idCommand-TOOLBAR_ID_START,tbt.iBitmap,tbt.iString,tbt.dwData);
				GPTranslateTBCtrlState(tbt.fsState,str);
				sprintf(str+(int)strlen(str),"\x7F%d",btIndex);
			}
			else sprintf(str,"%d",wParam-TOOLBAR_ID_START);

			if (m_EnableClick || (tbt.fsStyle&TBSTYLE_CHECK)==TBSTYLE_CHECK || (tbt.fsStyle&TBSTYLE_CHECKGROUP)==TBSTYLE_CHECKGROUP)
			{
				m_EnableClick=FALSE;
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClicked",str);
				if (m_bEnableMultiClick==FALSE) SetTimer(CLICK_TIMER_ID,CLICK_TIMER_DELAY,0);
				else m_EnableClick=TRUE;
			}
			ret=FALSE;
		}
	}

	if (message==WM_NOTIFY)
	{

	char str[500];*str=0;
	CRect re(0,0,0,0);
	ret=TRUE;
	LPNMTOOLBAR lpnm= (LPNMTOOLBAR)lParam;
		switch(lpnm->hdr.code)
		{
		case TBN_HOTITEMCHANGE:
			{
				DWORD uflg[9]={HICF_ACCELERATOR,HICF_ARROWKEYS,HICF_DUPACCEL,HICF_ENTERING,HICF_LEAVING,HICF_MOUSE,HICF_OTHER,HICF_RESELECT,HICF_TOGGLEDROPDOWN,};
				char *cflg[9]={"ACCELERATOR|","ARROWKEYS|","DUPACCEL|","ENTERING|","LEAVING|","MOUSE|","OTHER|","RESELECT|","TOGGLEDROPDOWN|",};
				NMTBHOTITEM *Hi=(NMTBHOTITEM *)lParam;
				sprintf(str,"%d\x7F%d\x7F",Hi->idOld,Hi->idNew);
				int i;
				for(i=0;i<9;i++)
					if ((Hi->dwFlags&uflg[i])==uflg[i])
						strcat(str,cflg[i]);

				if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnHotImageChange",str);
				ret=0;
			}
			break;
		case NM_RDBLCLK:
		case NM_RCLICK:
		case NM_CLICK:
		case NM_DBLCLK:
		case NM_KILLFOCUS:
		case NM_OUTOFMEMORY:
		case NM_RETURN:
		case NM_SETFOCUS:
		case TBN_CUSTHELP:
		case TBN_BEGINADJUST:
		case TBN_TOOLBARCHANGE:
		case TBN_RESET:
		case TBN_ENDADJUST:
		case TBN_RESTORE:
		case TBN_SAVE:
		case TBN_INITCUSTOMIZE:
		case TBN_GETINFOTIP:
		case TBN_GETDISPINFO:
			sprintf(str,"%d",((LPNMHDR) lParam)->idFrom-TOOLBAR_ID_START);
			if (referGPU!=NULL)
			switch(((LPNMHDR)lParam)->code)
			{
			case TBN_BEGINADJUST:
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnBeginAdjust",str);
				break;
			case TBN_TOOLBARCHANGE:
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnToolBarChange",str);
				break;
			case TBN_RESET:
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnReset",str);
				break;
			case NM_RDBLCLK:
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnRDblClick",str);
				break;
			case NM_RCLICK:
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnRClick",str);
				break;
			case TBN_CUSTHELP:
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnCustHelp",str);
				break;
			case NM_CLICK:
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNClick",str);
				break;
			case NM_DBLCLK:
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNDblClick",str);
				break;
			case NM_KILLFOCUS:
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNKillFocus",str);
				break;
			case NM_OUTOFMEMORY:
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNOutOfMemory",str);
				break;
			case NM_RETURN:
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNReturn",str);
				break;
			case NM_SETFOCUS:
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNSetFocus",str);
				break;
			case TBN_ENDADJUST:
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNEndAdjust",str);
				break;
			case TBN_RESTORE:
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNRestore",str);
				break;
			case TBN_SAVE:
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNSave",str);
				break;
			case TBN_INITCUSTOMIZE:
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNInitCustomize",str);
				break;
			case TBN_GETINFOTIP:
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNGetInfotip",str);
				break;
			case TBN_GETDISPINFO:
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNGetDispInfo",str);
				break;
			}
			break;

		case TBN_QUERYINSERT:
		case TBN_QUERYDELETE:
		case TBN_BEGINDRAG :
		case TBN_ENDDRAG:
		case TBN_DRAGOUT:
		case TBN_DROPDOWN:
		case TBN_DELETINGBUTTON:
		case TBN_GETBUTTONINFO:
			{
				try
				{
					LPNMTOOLBAR lpnmTB=(LPNMTOOLBAR)lParam;
					GetButton(CommandToIndex(lpnmTB->iItem),&lpnmTB->tbButton);
					GetItemRect(CommandToIndex(lpnmTB->iItem),&re);
					ClientToScreen(&re);
					sprintf(str,"%d\x7F%d\x7F%s\x7F%d\x07%d\x07%d\x07%d",
							lpnmTB->iItem-TOOLBAR_ID_START,
							CommandToIndex(lpnmTB->iItem),
							lpnmTB->pszText==NULL?"":lpnmTB->pszText,
							re.top,
							re.left,
							re.bottom,
							re.right);

					if (referGPU!=NULL)
						switch(((LPNMHDR)lParam)->code)
						{
						case TBN_QUERYINSERT:
							referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnQueryInsert",str);
							break;
						case TBN_QUERYDELETE:
							referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnQueryDelete",str);
							break;
						case TBN_BEGINDRAG :
							referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnBeginDrag",str);
							break;
						case TBN_ENDDRAG:
							referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnEndDrag",str);
							break;
						case TBN_DRAGOUT:
							referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDragOut",str);
							break;
						case TBN_DELETINGBUTTON:
							referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDeletingButton",str);
							break;
						case TBN_GETBUTTONINFO:
							referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnGetButtonInfo",str);
							break;
						case TBN_DROPDOWN:
							referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDropDown",str);
							if (
								lpnmTB->iItem>=TOOLBAR_ID_START && lpnmTB->iItem<=TOOLBAR_ID_END &&
								aPopupMenuInd[lpnmTB->iItem-TOOLBAR_ID_START]>=MENU_POPUP_START &&
								aPopupMenuInd[lpnmTB->iItem-TOOLBAR_ID_START]<=MENU_POPUP_START+MENU_POPUP_COUNT &&
								RefDlgGPMenu!=NULL && *RefDlgGPMenu!=NULL
								)
								(*RefDlgGPMenu)->GPTrackPopupMenu(aPopupMenuInd[lpnmTB->iItem-TOOLBAR_ID_START],TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL,re.left,re.bottom,NULL);
								ret=TBDDRET_DEFAULT;
							break;
						}
				}
				catch(...)
				{
					GPC.m_ErrReport.GPWriteErrorLog("GPToolBarCtrl", "OnChildNotify","");
					*str=0;
				}

			}
			break;
	  }
	}
	return ret?CToolBarCtrl::OnChildNotify(message, wParam, lParam, pLResult):ret;
}
