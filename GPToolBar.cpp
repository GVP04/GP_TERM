// GPToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPToolBar.h"
#include "GPToolBarCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// GPToolBar
const UINT GPToolBar::uNMethods=71;
const char *GPToolBar::cArrMethods[]={
		"UpdateGroup","TBCIsButtonEnabled","TBCIsButtonChecked","TBCIsButtonPressed","TBCIsButtonHidden",
		"TBCIsButtonIndeterminate","TBCSetState","TBCGetState","TBCGetButton","TBCGetButtonCount",
		"TBCGetItemRect","TBCGetRect","TBCGetButtonSize","TBCSetButtonSize","TBCSetBitmapSize",
		"TBCSetRows","TBCGetRows","TBCSetCmdID","TBCGetBitmapFlags","TBCGetDisabledImageList",
		"TBCGetHotImageList","TBCGetImageList","TBCGetTBStyle","TBCGetMaxTextRows","TBCIsButtonHighlighted",
		"TBCSetButtonWidth","TBCSetDisabledImageList","TBCSetHotImageList","TBCSetImageList","TBCSetIndent",
		"TBCSetMaxTextRows","TBCGetAnchorHighlight","TBCSetAnchorHighlight","TBCGetHotItem","TBCSetHotItem",
		"TBCGetInsertMark","TBCSetInsertMark","TBCGetMaxSize","TBCInsertMarkHitTest","TBCGetExtendedStyle",
		"TBCSetExtendedStyle","TBCGetInsertMarkColor","TBCSetInsertMarkColor","TBCMapAccelerator","TBCMoveButton",
		"TBCHitTest","TBCEnableButton","TBCCheckButton","TBCPressButton","TBCHideButton",
		"TBCIndeterminate","TBCMarkButton","TBCGetButtonInfo","TBCSetButtonInfo","TBCSetDrawTextFlags",
		"TBCAddBitmap","TBCAddButton","TBCInsertButton","TBCDeleteButton","TBCCommandToIndex",
		"TBCRestoreState","TBCLoadImages","TBCSaveState","TBCCustomize","TBCAddStrings",
		"TBCAutoSize","MultiClick","SetDropMenu","SetSizes","SetHeight",
		"GetItemRect","","","","",
		"","","", "", "", 
	};

const char *GPToolBar::cArrMethodsParams[]={
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
		"","bMultiClick","iId,iIdPopup","Buttoncx,Buttoncy,Imagecx,Imagecy","nHeight",
		"IdIndex","","","","",
		"","","", "", "", 
	};

GPToolBar::GPToolBar(UINT iUnitId)
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

GPToolBar::~GPToolBar()
{
	if (aToolTipArr!=NULL) delete aToolTipArr;
	aToolTipArr=NULL;
}


BEGIN_MESSAGE_MAP(GPToolBar, CToolBar)
	//{{AFX_MSG_MAP(GPToolBar)
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
// GPToolBar message handlers



UINT GPToolBar::DoMethod(const char *iStr, char *oStr)
{
	char met[150];
	strncpy(met,iStr,145);
	met[145]=0;
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc=0;
///////////////////	case : "SetButtonStructSize","GetToolTips","SetToolTips","SetOwner","GetDropTarget",
///////////////////	case : "SetStyle",

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
		case 1: /*TBCIsButtonEnabled*/			retint=GetToolBarCtrl().IsButtonEnabled(atoiIdCommand);	break;
		case 2: /*TBCIsButtonChecked*/			retint=GetToolBarCtrl().IsButtonChecked(atoiIdCommand);	break;
		case 3: /*TBCIsButtonPressed*/			retint=GetToolBarCtrl().IsButtonPressed(atoiIdCommand);	break;
		case 4: /*TBCIsButtonHidden*/			retint=GetToolBarCtrl().IsButtonHidden(atoiIdCommand);		break;
		case 5: /*TBCIsButtonIndeterminate*/	retint=GetToolBarCtrl().IsButtonIndeterminate(atoiIdCommand);	break;
		case 6: /*TBCSetState*/
			{
				char *pos333=new char [(int)strlen(pos)+20];
				strcpy(pos333,pos);
				_strupr(pos333);
				strcat(pos333,"|");
				UINT state=0;
				int i;
				for(i=0;i<8;i++)
					if (strstr(pos333,GPToolBarCtrl::cBtnState[i])!=0)
					{
						state|=GPToolBarCtrl::uBtnState[i];
						if (GPToolBarCtrl::uBtnState[i]==TBSTATE_WRAP) state|=TBSTATE_ENABLED;
					}

				retint=GetToolBarCtrl().SetState(atoiIdCommand,state);
				GetToolBarCtrl().AutoSize( );
				delete[] pos333;
			}
			break;
		case 7: /*TBCGetState*/
			if (oStr!=NULL)
			{
				*oStr=0;
				GPToolBarCtrl::GPTranslateTBCtrlState(GetToolBarCtrl().GetState(atoiIdCommand),oStr);
			}
			break;
		case 8: /*TBCGetButton*/
			if (oStr!=NULL)
			{
				TBBUTTON tbt={0};
				if (GetToolBarCtrl().GetButton(atoiIdIndex,&tbt))
				{
					sprintf(oStr,"%d\x7F%d\x7F%d\x7F%ld\x7F",tbt.iBitmap,tbt.idCommand-TOOLBAR_ID_START,tbt.iString,tbt.dwData);
					GPToolBarCtrl::GPTranslateTBCtrlState(tbt.fsState,oStr);
					strcat(oStr,"\x7F");
					GPToolBarCtrl::GPTranslateTBCtrlStyle(tbt.fsStyle,oStr);
				}
			}
			break;
		case 9: /*TBCGetButtonCount*/		retint=GetToolBarCtrl().GetButtonCount();	break;
		case 10: /*TBCGetItemRect*/
			if (oStr!=NULL)
			{
				CRect re;
				if (GetToolBarCtrl().GetItemRect(atoiIdIndex,&re))
					sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
			}
			break;
		case 11: /*TBCGetRect*/
			if (oStr!=NULL)
			{
				CRect re;
				if (GetToolBarCtrl().GetRect(atoiIdCommand,&re))
					sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
			}
			break;
		case 12: /*TBCGetButtonSize*/
			if (oStr!=NULL)
			{
				DWORD sz=GetToolBarCtrl().GetButtonSize();
					sprintf(oStr,"%d\x7F%d",LOWORD(sz),HIWORD(sz));
			}
			break;
		case 13: /*TBCSetButtonSize*/
			{
				CSize sz(0,0);
				m_LastScanf=sscanf(pos,"%d,%d",&sz.cx,&sz.cy);
				retint=GetToolBarCtrl().SetButtonSize(sz);
				GetToolBarCtrl().AutoSize( );
			}
			break;
		case 14: /*TBCSetBitmapSize*/
			{
				CSize sz(0,0);
				m_LastScanf=sscanf(pos,"%d,%d",&sz.cx,&sz.cy);
				retint=GetToolBarCtrl().SetBitmapSize(sz);
				GetToolBarCtrl().AutoSize( );
			}
			break;
		case 15: /*TBCSetRows*/
			{
				CRect re;
				int nRows=1,bLarger=1;
				m_LastScanf=sscanf(pos,"%d,%d",&nRows,&bLarger);
				GetToolBarCtrl().SetRows(nRows,bLarger,&re);
				if (oStr!=NULL)
					sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
				GetToolBarCtrl().AutoSize( );
			}
			break;
		case 16: /*TBCGetRows*/		retint=GetToolBarCtrl().GetRows();	break;
		case 17: /*TBCSetCmdID*/
			{
				UINT nIndex=0,nID=0;
				m_LastScanf=sscanf(pos,"%d,%d",&nIndex,&nID);
				if (nID>=TOOLBAR_ID_COUNT) nID=0;
				retint=GetToolBarCtrl().SetCmdID(nIndex,nID+TOOLBAR_ID_START);
			}
			break;
		case 18: /*TBCGetBitmapFlags*/
			if (oStr!=NULL)
			{
				if (GetToolBarCtrl().GetBitmapFlags()==TBBF_LARGE) strcat(oStr,"TBBF_LARGE");
			}
			break;
		case 19: /*TBCGetDisabledImageList*/
			if (oStr!=NULL)
			{
				int id=GPC.FindImageList(GetToolBarCtrl().GetDisabledImageList());
				if (id>=0) strcpy(oStr,GPC.a_GPImageList[id].ILName);
			}
			break;
		case 20: /*TBCGetHotImageList*/
			if (oStr!=NULL)
			{
				int id=GPC.FindImageList(GetToolBarCtrl().GetHotImageList());
				if (id>=0) strcpy(oStr,GPC.a_GPImageList[id].ILName);
			}
			break;
		case 21: /*TBCGetImageList*/
			if (oStr!=NULL)
			{
				int id=GPC.FindImageList(GetToolBarCtrl().GetImageList());
				if (id>=0) strcpy(oStr,GPC.a_GPImageList[id].ILName);
			}
			break;
		case 22: /*TBCGetTBStyle*/
			if (oStr!=NULL)
				GetObjStlStr(oStr, GetToolBarCtrl().GetStyle(), N_TOOLBARCTRL_STYLES,  aToolBarCtrlStyleName, aToolBarCtrlStyleUINT, aToolBarCtrlStyleMask);
			break;
		case 23: /*TBCGetMaxTextRows*/		retint=GetToolBarCtrl().GetMaxTextRows();	break;
		case 24: /*TBCIsButtonHighlighted*/	retint=GetToolBarCtrl().IsButtonHighlighted(atoiIdCommand);	break;
		case 25: /*TBCSetButtonWidth*/
			{
				int cxMin=10,cxMax =48;
				m_LastScanf=sscanf(pos,"%d,%d",&cxMin,&cxMax);
				retint=GetToolBarCtrl().SetButtonWidth(cxMin,cxMax);
				GetToolBarCtrl().AutoSize( );
			}
			break;
		case 26: /*TBCSetDisabledImageList*/
			if ((atoiIdIndex=GPC.GetImageListId(pos))>=0)
				GetToolBarCtrl().SetDisabledImageList(&(GPC.a_GPImageList[atoiIdIndex].m_IL));
			GetToolBarCtrl().AutoSize( );
			break;
		case 27: /*TBCSetHotImageList*/
			if ((atoiIdIndex=GPC.GetImageListId(pos))>=0)
				GetToolBarCtrl().SetHotImageList(&(GPC.a_GPImageList[atoiIdIndex].m_IL));
			GetToolBarCtrl().AutoSize( );
			break;
		case 28: /*TBCSetImageList*/
			if ((atoiIdIndex=GPC.GetImageListId(pos))>=0)
				GetToolBarCtrl().SetImageList(&(GPC.a_GPImageList[atoiIdIndex].m_IL));
			GetToolBarCtrl().AutoSize( );
			break;
		case 29: /*TBCSetIndent*/
			retint=GetToolBarCtrl().SetIndent(atoiIdIndex);
			GetToolBarCtrl().AutoSize( );
			break;
		case 30: /*TBCSetMaxTextRows*/ 	retint=GetToolBarCtrl().SetMaxTextRows(atoiIdIndex);		break;
		case 31: /*TBCGetAnchorHighlight*/	retint=GetToolBarCtrl().GetAnchorHighlight();		break;
		case 32: /*TBCSetAnchorHighlight*/	retint=GetToolBarCtrl().SetAnchorHighlight(atoiIdIndex);	break;
		case 33: /*TBCGetHotItem*/			retint=GetToolBarCtrl().GetHotItem();				break;
		case 34: /*TBCSetHotItem*/ 		retint=GetToolBarCtrl().SetHotItem(atoiIdIndex);		break;
		case 35: /*TBCGetInsertMark*/
			if (oStr!=NULL)
			{
				TBINSERTMARK tbim={0};
				GetToolBarCtrl().GetInsertMark(&tbim);
				sprintf(oStr,"%d\x7F%s",tbim.iButton,tbim.dwFlags==0?"BEFORE":tbim.dwFlags==TBIMHT_AFTER?"AFTER":"BACKGROUND");
			}
			break;
		case 36: /*TBCSetInsertMark*/
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				TBINSERTMARK tbim={0};
				tbim.iButton=atoiIdIndex;
				_strupr(pos333);
				if (strstr(pos333,"AFTER")!=NULL) tbim.dwFlags=TBIMHT_AFTER;
					else
					if (strstr(pos333,"BACKGROUND")!=NULL) tbim.dwFlags=TBIMHT_BACKGROUND;

				GetToolBarCtrl().SetInsertMark(&tbim);
				GetToolBarCtrl().AutoSize( );
				delete[] pos333;
			}
			break;
		case 37: /*TBCGetMaxSize*/
			{
				CSize sz;
				if (GetToolBarCtrl().GetMaxSize(&sz))	sprintf(oStr,"%d\x7F%d",sz.cx,sz.cy);
				else retint=-1;
			}
			break;
		case 38: /*TBCInsertMarkHitTest*/
			if (oStr!=NULL)
			{
				TBINSERTMARK tbim={0};
				CPoint po(0,0);
				m_LastScanf=sscanf(pos,"%d,%d",&po.x,&po.y);

				retint=GetToolBarCtrl().InsertMarkHitTest(&po,&tbim);
				sprintf(oStr,"%d\x7F%s",tbim.iButton,tbim.dwFlags==TBIMHT_AFTER?"AFTER":tbim.dwFlags==TBIMHT_BACKGROUND?"BACKGROUND":"0");

			}
			break;
		case 39: /*TBCGetExtendedStyle*/
			if (oStr!=NULL)
				GetObjStlStr(oStr, GetToolBarCtrl().GetExtendedStyle(), N_TOOLBARCTRL_EX_STYLES,  aToolBarCtrlExStyleName, aToolBarCtrlExStyleUINT, aToolBarCtrlExStyleMask);
			break;

		case 40: /*TBCSetExtendedStyle*/
			{
				UINT stl=0;
				int i;
				for(i=0;i<N_TOOLBARCTRL_EX_STYLES;i++)
					if (strstr(pos,aToolBarCtrlExStyleName[i])!=NULL) stl|=aToolBarCtrlExStyleUINT[i];

				stl=GetToolBarCtrl().SetExtendedStyle(stl);
				GetToolBarCtrl().Invalidate();
			}
			break;
		case 41: /*TBCGetInsertMarkColor*/
			if (oStr!=NULL)
			{	UINT cref=GetToolBarCtrl().GetInsertMarkColor();
				sprintf(oStr,"%d%c%d%c%d",(cref&0xFF),7,((cref/0x100)&0xFF),7,((cref/0x10000)&0xFF));
			}
			break;
		case 42: /*TBCSetInsertMarkColor*/
			{
				UINT r=0,g=0,b=0,cref=0;

				m_LastScanf=sscanf(pos,"%d,%d,%d",&r,&g,&b);
				cref=GetToolBarCtrl().SetInsertMarkColor(RGB(r,g,b));
				if (oStr!=NULL)
					sprintf(oStr,"%d%c%d%c%d",(cref&0xFF),7,((cref/0x100)&0xFF),7,((cref/0x10000)&0xFF));
			}
			break;
		case 43: /*TBCMapAccelerator*/
			{
				UINT nId;
				GetToolBarCtrl().MapAccelerator(*pos,&nId);
				retint=nId;
			}
			break;
		case 44: /*TBCMoveButton*/
			{
				UINT nOldPos=0,nNewPos=0;
				m_LastScanf=sscanf(pos,"%d,%d",&nOldPos,&nNewPos);
				retint=GetToolBarCtrl().MoveButton(nOldPos,nNewPos);
				GetToolBarCtrl().AutoSize( );
			}
			break;
		case 45: /*TBCHitTest*/
			{
				CPoint po(0,0);
				m_LastScanf=sscanf(pos,"%d,%d",&po.x,&po.y);
				retint=GetToolBarCtrl().HitTest(&po);
			}
			break;
		case 46: /*TBCEnableButton*/
		case 47: /*TBCCheckButton*/
		case 48: /*TBCPressButton*/
		case 49: /*TBCHideButton*/
		case 50: /*TBCIndeterminate*/
		case 51: /*TBCMarkButton*/
			{
				int IdCommand=0,bEnable = TRUE;
				m_LastScanf=sscanf(pos,"%d,%d",&IdCommand,&bEnable);
				IdCommand+=TOOLBAR_ID_START;
				switch(nfunc)
				{
				case 46: /*TBCEnableButton*/	retint=GetToolBarCtrl().EnableButton(IdCommand,bEnable);	break;
				case 47: /*TBCCheckButton*/ 	retint=GetToolBarCtrl().CheckButton(IdCommand,bEnable);	break;
				case 48: /*TBCPressButton*/	retint=GetToolBarCtrl().PressButton(IdCommand,bEnable);	break;
				case 49: /*TBCHideButton*/		retint=GetToolBarCtrl().HideButton(IdCommand,bEnable);		break;
				case 50: /*TBCIndeterminate*/	retint=GetToolBarCtrl().Indeterminate(IdCommand,bEnable);	break;
				case 51: /*TBCMarkButton*/		retint=GetToolBarCtrl().MarkButton(IdCommand,bEnable);		break;
				}
			}
			GetToolBarCtrl().AutoSize( );
			break;

		case 52: /*TBCGetButtonInfo*/
			if (oStr)
			{
				TBBUTTONINFO tbti={0};
				tbti.cbSize=sizeof(tbti);
				tbti.dwMask=TBIF_COMMAND|TBIF_IMAGE|TBIF_LPARAM|TBIF_SIZE|TBIF_STATE|TBIF_STYLE|TBIF_TEXT;
				GetToolBarCtrl().GetButtonInfo(atoiIdCommand,&tbti);
				char str[256];
				*str=0;
				tbti.cchText=250;
				tbti.pszText=str;
				sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d\x7F%s\x7F",tbti.idCommand-TOOLBAR_ID_START,tbti.iImage,tbti.cx,tbti.lParam,str);
				GPToolBarCtrl::GPTranslateTBCtrlState(tbti.fsState,oStr);
				strcat(oStr,"\x7F");
				GPToolBarCtrl::GPTranslateTBCtrlStyle(tbti.fsStyle,oStr);
				strcat(oStr,"\x7F");
				tbti.pszText[255]=0;
				strcat(oStr,tbti.pszText);
			}
			break;
		case 53: /*TBCSetButtonInfo*/ // SetButtonInfo  nId,COMMAND=10;IMAGE=2 ......
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
							tbti.cx=atoi(cpos[i]);
							break;
						case 5:
							tbti.dwMask|=TBIF_STATE;
							GPToolBarCtrl::GPTranslateTBCtrlState(cpos[i],tmpUI);
							tbti.fsState=tmpUI;
							break;
						case 6:
							tbti.dwMask|=TBIF_STYLE;
							GPToolBarCtrl::GPTranslateTBCtrlStyle((const char *)cpos[i],tmpUI);
							tbti.fsStyle=tmpUI;
							break;
						case 7:
							if (tbti.idCommand>=TOOLBAR_ID_START && tbti.idCommand<=TOOLBAR_ID_END)
								aToolTipArr->SetItem(tbti.idCommand-TOOLBAR_ID_START,pos2);
							break;
						}
					}

				if ((tbti.fsStyle&TBBS_SEPARATOR)==TBBS_SEPARATOR)
					tbti.idCommand=ID_SEPARATOR;

				retint=GetToolBarCtrl().SetButtonInfo(atoiIdCommand,&tbti);
				GetToolBarCtrl().AutoSize( );
				delete[] pos333;
			}
			break;
		case 54: /*TBCSetDrawTextFlags*/
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				UINT dwMask=0;
				_strupr(pos333);
				int i;
				for(i=0;i<N_DRAWTEXT_FLAGS;i++)
					if (strstr(pos333,aDrawTextFlagName[i])!=NULL)  dwMask|=aDrawTextFlagUINT[i];
				GetToolBarCtrl().SetDrawTextFlags(dwMask,dwMask);
				delete[] pos333;
			}
			break;
		case 55: /*TBCAddBitmap*/
			{
				const char *name=strchr(pos,',');
				if (name==NULL) name="MISCL";
				else name++;
				GPImageList *SMainIl;
				int ImgLId=atoi(pos);

				if ((ImgLId=GPC.GetImageListId(name))>=0 &&(SMainIl=&(GPC.a_GPImageList[ImgLId]))!=NULL)
				{
					ICONINFO ii={0};
					GetIconInfo(SMainIl->m_IL.ExtractIcon(atoi(pos)),&ii);
					retint=GetToolBarCtrl().AddBitmap(1, CBitmap::FromHandle(ii.hbmColor));
				}
				else retint=-1;
				GetToolBarCtrl().AutoSize( );
			}
			break;
		case 56: /*TBCAddButton*/
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				TBBUTTON tbt={0};
				m_LastScanf=sscanf(pos333,"%d,%d,%d,%d",&tbt.iBitmap,&tbt.idCommand,&tbt.iString,&tbt.dwData);
				tbt.idCommand=(tbt.idCommand%TOOLBAR_ID_COUNT)+TOOLBAR_ID_START;
				char *pos2=strchr(pos333,';');
				if (pos2++!=NULL)
				{
					if (tbt.idCommand>=TOOLBAR_ID_START && tbt.idCommand<=TOOLBAR_ID_END)
							aToolTipArr->SetItem(tbt.idCommand-TOOLBAR_ID_START,pos2);
				}
				_strupr(pos333);
				UINT tmpUI;
				GPToolBarCtrl::GPTranslateTBCtrlState(pos333,tmpUI);
				tbt.fsState=tmpUI;
				GPToolBarCtrl::GPTranslateTBCtrlStyle(pos333,tmpUI);
				tbt.fsStyle=tmpUI;
				if ((tmpUI&TBBS_SEPARATOR)==TBBS_SEPARATOR)
					tbt.idCommand=ID_SEPARATOR;
				GetToolBarCtrl().AddButtons(1,&tbt);
				GetToolBarCtrl().AutoSize( );
				delete[] pos333;
			}
			break;
		case 57: /*TBCInsertButton*/
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
				GPToolBarCtrl::GPTranslateTBCtrlState(pos333,tmpUI);
				tbt.fsState=tmpUI;
				GPToolBarCtrl::GPTranslateTBCtrlStyle(pos333,tmpUI);
				tbt.fsStyle=tmpUI;
				if ((tmpUI&TBBS_SEPARATOR)==TBBS_SEPARATOR)
					tbt.idCommand=ID_SEPARATOR;
				GetToolBarCtrl().InsertButton(atoiIdIndex,&tbt);
				GetToolBarCtrl().AutoSize( );
				delete[] pos333;
			}
			break;
		case 58: /*TBCDeleteButton*/
			retint=GetToolBarCtrl().DeleteButton(atoiIdIndex);
			GetToolBarCtrl().AutoSize( );break;
		case 59: /*TBCCommandToIndex*/
			retint=GetToolBarCtrl().CommandToIndex((atoiIdIndex%TOOLBAR_ID_COUNT)+TOOLBAR_ID_START);
			break;
		case 60: /*TBCRestoreState*/
		case 62: /*TBCSaveState*/
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				HKEY curkey;
				RegOpenKeyEx(HKEY_CURRENT_USER,AfxGetApp()->m_pszRegistryKey,0,KEY_ALL_ACCESS,&curkey);
				char *pos2=strchr(pos333,',');
				if (pos2!=NULL) *(pos2++)=0;
				else pos2="";
				if (nfunc==60)	GetToolBarCtrl().RestoreState(curkey,pos333,pos2);
				else			GetToolBarCtrl().SaveState(curkey,pos333,pos2);
				RegCloseKey(curkey);
				delete[] pos333;
			}
			break;
		case 61: /*TBCLoadImages*/
				GetToolBarCtrl().LoadImages(atoiIdIndex, HINST_COMMCTRL);
			break;
		case 63: /*TBCCustomize*/		GetToolBarCtrl().Customize();	break;
		case 64: /*TBCAddStrings*/
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
				retint=GetToolBarCtrl().AddStrings(pos333);
				GetToolBarCtrl().AutoSize( );
				delete[] pos333;
			}
			break;
		case 65: /*TBCAutoSize*/	GetToolBarCtrl().AutoSize(); break;
		case 66: /*MultiClick*/		m_bEnableMultiClick=atoi(pos);	break;
		case 67: /*SetDropMenu*/
			{
				int iId=0,iIdPopup=-1;
				m_LastScanf=sscanf(pos,"%d,%d",&iId,&iIdPopup);
				if (iId>=0 && iId<=TOOLBAR_ID_COUNT && iIdPopup>=MENU_POPUP_START && iIdPopup<=MENU_POPUP_START+MENU_POPUP_COUNT)
					aPopupMenuInd[iId]=iIdPopup;
			}
			break;
		case 68: /*SetSizes*/
			{
				CSize sizeButton(32,32), sizeImage(24,24);
				m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&sizeButton.cx,&sizeButton.cy,&sizeImage.cx,&sizeImage.cy);
				SetSizes(sizeButton,sizeImage);
			}
			break;
		case 69: /*SetHeight*/		SetHeight(atoiIdIndex); break;
		case 70: /*GetItemRect*/
			if (oStr!=NULL)
			{
				CRect re(0,0,0,0);
				GetItemRect(atoiIdIndex,&re);
				sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
			}
			break;
		default:  nfunc=GPUnit::DoControlBarMethod(this,iStr,oStr); break;
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
		GPC.m_ErrReport.GPWriteErrorLog("GPToolBar", "DoMethod",iStr);
		delete[] str;
	}

	switch(nfunc)
	{
	case 6: /*TBCSetState*/
	case 13: /*TBCSetButtonSize*/
	case 14: /*TBCSetBitmapSize*/
	case 15: /*TBCSetRows*/
	case 17: /*TBCSetCmdID*/
	case 25: /*TBCSetButtonWidth*/
	case 26: /*TBCSetDisabledImageList*/
	case 27: /*TBCSetHotImageList*/
	case 28: /*TBCSetImageList*/
	case 29: /*TBCSetIndent*/
	case 30: /*TBCSetMaxTextRows*/
	case 32: /*TBCSetAnchorHighlight*/
	case 34: /*TBCSetHotItem*/
	case 36: /*TBCSetInsertMark*/
	case 40: /*TBCSetExtendedStyle*/
	case 44: /*TBCMoveButton*/
	case 46: /*TBCEnableButton*/
	case 47: /*TBCCheckButton*/
	case 48: /*TBCPressButton*/
	case 49: /*TBCHideButton*/
	case 50: /*TBCIndeterminate*/
	case 51: /*TBCMarkButton*/
	case 53: /*TBCSetButtonInfo*/ // SetButtonInfo  nId,COMMAND=10;IMAGE=2 ......
	case 54: /*TBCSetDrawTextFlags*/
	case 55: /*TBCAddBitmap*/
	case 56: /*TBCAddButton*/
	case 57: /*TBCInsertButton*/
	case 58: /*TBCDeleteButton*/
	case 60: /*TBCRestoreState*/
	case 61: /*TBCLoadImages*/
	case 63: /*TBCCustomize*/
	case 64: /*TBCAddStrings*/
	case 65: /*TBCAutoSize*/
	case 68: /*SetSizes*/
	case 69: /*SetHeight*/
		GetParent()->SendMessage(WM_APP+1);
		break;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
	return nfunc;
}

UINT GPToolBar::GPSetProperty(char *iStr)
{
	char *iValue=new char [(int)strlen(iStr)+5];
	strcpy(iValue,iStr);
	UINT ret=1,i;
	char *pos=strchr(iValue,'=');

	if (pos!=NULL && m_hWnd)
	{
		char *prop[]={ "ADDSTYLE", "DELSTYLE","STYLE",};
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
					int tbctrlchange=0;

					char *postmp=strstr(pos,"&U");

					if (postmp!=NULL)
					{
						UINT es=GetStyle();
						UINT tmpstl=0;
						m_LastScanf=sscanf(postmp,"&U%X",&tmpstl);
						InvFlg++;
						tbctrlchange=1;
						switch(propnum)
						{
						case 2: /* STYLE*/
						case 0: /* ADDSTYLE*/	GetToolBarCtrl().SetStyle(es|tmpstl);		break;
						case 1: /* DELSTYLE*/	GetToolBarCtrl().SetStyle((es|tmpstl)^tmpstl);	break;
						}
						if (InvFlg!=0) Invalidate();
					}
					else
					{
						strcat(pos,"|");
						UINT Stl=0;
						switch(propnum)
						{
						case 0: /* ADDSTYLE*/	Stl=GetToolBarCtrl().GetStyle();
						case 2: /* STYLE*/
							for(i=0;i<N_TOOLBARCTRL_STYLES;i++)
								if (strstr(pos,aToolBarCtrlStyleName[i])!=NULL)
								{
									InvFlg++;
									Stl|=aToolBarCtrlStyleUINT[i];
									tbctrlchange=1;
								}
							GetToolBarCtrl().SetStyle(Stl);
							break;
						case 1: /* DELSTYLE*/
							for(i=0;i<N_TOOLBARCTRL_STYLES;i++)
								if (strstr(pos,aToolBarCtrlStyleName[i])!=NULL)
								{
									InvFlg++;
									Stl|=aToolBarCtrlStyleUINT[i];
									tbctrlchange=1;
								}
							GetToolBarCtrl().SetStyle(GetToolBarCtrl().GetStyle()&(Stl^0xFFFFFFFF));
							break;
						}

						Stl=0;
						switch(propnum)
						{
						case 0: /* ADDSTYLE*/	Stl=GetBarStyle();
						case 2: /* STYLE*/
							for(i=0;i<N_CTRLBAR_STYLES;i++)
								if (strstr(pos,aCtrlBarStyleName[i])!=NULL)
								{
									InvFlg++;
									Stl|=aCtrlBarStyleUINT[i];
								}
							SetBarStyle(Stl);
							break;
						case 1: /* DELSTYLE*/
							for(i=0;i<N_CTRLBAR_STYLES;i++)
								if (strstr(pos,aCtrlBarStyleName[i])!=NULL)
								{
									InvFlg++;
									Stl|=aCtrlBarStyleUINT[i];
								}
							SetBarStyle(GetBarStyle()&(Stl^0xFFFFFFFF));
							break;
						}
					}

					postmp=strstr(pos,"&X");

					if (postmp!=NULL)
					{
						UINT es=GetToolBarCtrl().GetExtendedStyle();
						UINT tmpstl=0;
						m_LastScanf=sscanf(postmp,"&X%X",&tmpstl);
						InvFlg++;
						switch(propnum)
						{
						case 2: /* STYLE*/
						case 0: /* ADDSTYLE*/	GetToolBarCtrl().SetExtendedStyle(es|tmpstl);			break;
						case 1: /* DELSTYLE*/	GetToolBarCtrl().SetExtendedStyle((es|tmpstl)^tmpstl);	break;
						}
						if (InvFlg!=0) Invalidate();
					}
					else
					{
						strcat(pos,"|");
						UINT Stl=0;
						switch(propnum)
						{
						case 0: /* ADDSTYLE*/	Stl=GetToolBarCtrl().GetExtendedStyle();
						case 2: /* STYLE*/
							for(i=0;i<N_TOOLBARCTRL_EX_STYLES;i++)
								if (strstr(pos,aToolBarCtrlExStyleName[i])!=NULL)
								{
									InvFlg++;
									Stl|=aToolBarCtrlExStyleUINT[i];
									tbctrlchange=1;
								}
							GetToolBarCtrl().SetExtendedStyle(Stl);
							break;
						case 1: /* DELSTYLE*/
							for(i=0;i<N_TOOLBARCTRL_EX_STYLES;i++)
								if (strstr(pos,aToolBarCtrlExStyleName[i])!=NULL)
								{
									InvFlg++;
									Stl|=aToolBarCtrlExStyleUINT[i];
									tbctrlchange=1;
								}
							GetToolBarCtrl().SetExtendedStyle(GetToolBarCtrl().GetExtendedStyle()&(Stl^0xFFFFFFFF));
							break;
						}
					}


					for(i=0;i<N_COMCTRL_STYLES;i++)
						if (strstr(pos,aComCtrlStyleName[i])!=NULL)
						{
							InvFlg++;
							switch(propnum)
							{
							case 2: /* STYLE*/
							case 0: /* ADDSTYLE*/	ModifyStyle(0,aComCtrlStyleUINT[i]);break;
							case 1: /* DELSTYLE*/	ModifyStyle(aComCtrlStyleUINT[i],0);break;
							}
						}

					GetToolBarCtrl().AutoSize( );
					GetParent()->PostMessage(WM_SIZE,SIZE_RESTORED,0x00000);
					if (tbctrlchange!=0)
					{
						UINT Stl=GetToolBarCtrl().GetStyle();
						GetToolBarCtrl().SetStyle(Stl^TBSTYLE_WRAPABLE);
						GetToolBarCtrl().SetStyle(Stl);
					}
					if (InvFlg!=0)
					{
						GetParent()->PostMessage(WM_APP+1);
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

void GPToolBar::OnParentNotify(UINT message, LPARAM lParam)
{
//TRACE("OnParentNotify %X,%d\n",message,lParam);

	char txt[100];
	if (message==WM_CREATE || message==WM_DESTROY)
		sprintf(txt,"%d\x7F%d\x7F%X",message/0x10000,(message&0xFFFF),lParam/0x10000);
	else
		sprintf(txt,"%d\x7F%d\x7F%d\x7F%d",message/0x10000,(message&0xFFFF),lParam/0x10000,(lParam&0xFFFF));
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"ParentNotify",txt);

	CToolBar::OnParentNotify(message, lParam);
}



HBRUSH GPToolBar::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CToolBar::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}

LRESULT GPToolBar::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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
		LPNMTOOLBAR lpnmTB=((LPNMTOOLBAR)lParam);
		UINT tttt=0U-520U;
		if (lpnm->code==TTN_GETDISPINFO)
		{
			LPTOOLTIPTEXT lpttt;
			lpttt =(LPTOOLTIPTEXT) lParam;
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

	if (message==WM_SIZEPARENT)
	{
		DWORD dwStyle=GetBarStyle();
		{
			AFX_SIZEPARENTPARAMS* lpLayout =(AFX_SIZEPARENTPARAMS*)lParam;
       		GetToolBarCtrl().AutoSize( );
			int nrow=GetToolBarCtrl().GetRows();
			CSize szf;
			GetToolBarCtrl().GetMaxSize(&szf);
			if ((dwStyle&CBRS_ALIGN_TOP)==CBRS_ALIGN_TOP)
			{
				szf.cx=lpLayout->rect.right-lpLayout->rect.left;
				MoveWindow(lpLayout->rect.left,lpLayout->rect.top,szf.cx,szf.cy*nrow+8);
				lpLayout->rect.top+=szf.cy*nrow+5;
			}
			else
			if ((dwStyle&CBRS_ALIGN_BOTTOM)==CBRS_ALIGN_BOTTOM)
			{
				szf.cx=lpLayout->rect.right-lpLayout->rect.left;
				MoveWindow(lpLayout->rect.left,lpLayout->rect.bottom-szf.cy*nrow-5,szf.cx,szf.cy*nrow+8);
				lpLayout->rect.bottom-=szf.cy*nrow+5;
			}
			else
			if ((dwStyle&(CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT))!=0)
			{
				int nbutton=GetToolBarCtrl().GetButtonCount( );
				szf.cx=16;

				CRect re;
				int nb;
				for(nb=0;nb<nbutton;nb++)
				{
					GetToolBarCtrl().GetItemRect(nb,&re);
					if (szf.cx<re.Width()) szf.cx=re.Width();
				}

				szf.cx+=6;
				szf.cy=lpLayout->rect.bottom-lpLayout->rect.top;

				if ((dwStyle&CBRS_ALIGN_LEFT)==CBRS_ALIGN_LEFT)
				{

					if (nbutton>0)
						while(szf.cx<1024)
						{
							MoveWindow(lpLayout->rect.left,lpLayout->rect.top,szf.cx,szf.cy);
							GetToolBarCtrl().GetItemRect(nbutton-1,&re);
							if (lpLayout->rect.bottom>re.bottom) break;
							szf.cx++;
						}

					MoveWindow(lpLayout->rect.left,lpLayout->rect.top,szf.cx,szf.cy);
					lpLayout->rect.left+=szf.cx;
				}
				else
				if ((dwStyle&CBRS_ALIGN_RIGHT)==CBRS_ALIGN_RIGHT)
				{
					if (nbutton>0)
						while(szf.cx<1024)
						{
							MoveWindow(lpLayout->rect.right-szf.cx,lpLayout->rect.top,szf.cx,szf.cy);
							GetToolBarCtrl().GetItemRect(nbutton-1,&re);
							if (lpLayout->rect.bottom>re.bottom) break;
							szf.cx++;
						}

					MoveWindow(lpLayout->rect.right-szf.cx,lpLayout->rect.top,szf.cx,szf.cy);
					lpLayout->rect.right-=szf.cx;
				}
			}
			return FALSE;
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

	if (message==WM_IDLEUPDATECMDUI) return TRUE;

	if (LOWORD(wParam)>=TOOLBAR_ID_START && LOWORD(wParam)<=TOOLBAR_ID_END)
	{
		if (message==WM_COMMAND && m_EnableClick && referGPU!=NULL)
		{
			m_EnableClick=FALSE;
			char str[100]; sprintf(str,"%d",wParam-TOOLBAR_ID_START);
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClicked",str);
			if (m_bEnableMultiClick==FALSE) SetTimer(CLICK_TIMER_ID,CLICK_TIMER_DELAY,0);
			else m_EnableClick=TRUE;
		}
		return TRUE;
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
	else lpr=CToolBar::WindowProc(message, wParam, lParam);

	return lpr;
}

BOOL GPToolBar::PreTranslateMessage(MSG* pMsg)
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
	return CToolBar::PreTranslateMessage(pMsg);
}

void GPToolBar::OnClose()
{

	if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClose","");
//	CToolBar::OnClose();
}


void GPToolBar::GPTranslateTBState(UINT iState, char *oStr)
{
	GPToolBarCtrl::GPTranslateTBCtrlState(iState,oStr);
//	if (oStr!=NULL)
//	{
//		int i;
//		for(i=0;i<8;i++)
//			if ((iState&uBtnState[i])==uBtnState[i])	strcat(oStr,cBtnState[i]);
//	}
}

void GPToolBar::GPTranslateTBStyle(UINT iStyle, char *oStr)
{
	GPToolBarCtrl::GPTranslateTBCtrlStyle(iStyle,oStr);
//	if (oStr!=NULL)
//	{
//		int i;
//		for(i=0;i<N_TOOLBAR_STYLES;i++)
//			if ((iStyle&aToolBarStyleUINT[i])==aToolBarStyleUINT[i])	strcat(oStr,aToolBarStyleName[i]);
//	}
}


void GPToolBar::GPTranslateTBState(const char *oStr, UINT & iState)
{
	GPToolBarCtrl::GPTranslateTBCtrlState(oStr,iState);
//	iState=0;
//	if (oStr!=NULL)
//	{
//		int i;
//		for(i=0;i<8;i++)
//			if (strstr(oStr,cBtnState[i])!=NULL)  iState|=uBtnState[i];
//	}
}

void GPToolBar::GPTranslateTBStyle(const char *oStr, UINT & iStyle)
{
	GPToolBarCtrl::GPTranslateTBCtrlStyle(oStr,iStyle);
//	iStyle=0;
//	if (oStr!=NULL)
//	{
//		int i;
//		for(i=0;i<N_TOOLBAR_STYLES;i++)
//			if (strstr(oStr,aToolBarStyleName[i])!=NULL)  iStyle|=aToolBarStyleUINT[i];
//	}
}




BOOL GPToolBar::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
//TRACE("OnNotify %d,%d code=%X\n",wParam,lParam,((LPNMHDR)lParam)->code);

char str[500];*str=0;
CRect re(0,0,0,0);
*pResult=TRUE;

	switch(((LPNMHDR)lParam)->code)
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
			*pResult=0;
		}
		break;
	case TBN_BEGINADJUST:
	case TBN_TOOLBARCHANGE:
	case TBN_RESET:
	case NM_RDBLCLK:
	case NM_RCLICK:
	case TBN_CUSTHELP:
	case NM_CLICK:
	case NM_DBLCLK:
	case NM_KILLFOCUS:
	case NM_OUTOFMEMORY:
	case NM_RETURN:
	case NM_SETFOCUS:
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
		}
		break;


	case TBN_QUERYINSERT:
	case TBN_QUERYDELETE:
	case TBN_BEGINDRAG :
	case TBN_ENDDRAG:
	case TBN_DRAGOUT:
	case TBN_DROPDOWN:
		{
			try
			{
				LPNMTOOLBAR lpnmTB=(LPNMTOOLBAR)lParam;
				GetToolBarCtrl().GetButton(GetToolBarCtrl().CommandToIndex(lpnmTB->iItem),&lpnmTB->tbButton);
				GetToolBarCtrl().GetItemRect(GetToolBarCtrl().CommandToIndex(lpnmTB->iItem),&re);
				ClientToScreen(&re);
				sprintf(str,"%d\x7F%d\x7F%s\x7F%d\x07%d\x07%d\x07%d",
						lpnmTB->iItem-TOOLBAR_ID_START,
						GetToolBarCtrl().CommandToIndex(lpnmTB->iItem),
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
					case TBN_DROPDOWN:
						referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDropDown",str);
						if (
							lpnmTB->iItem>=TOOLBAR_ID_START && lpnmTB->iItem<=TOOLBAR_ID_END &&
							aPopupMenuInd[lpnmTB->iItem-TOOLBAR_ID_START]>=MENU_POPUP_START &&
							aPopupMenuInd[lpnmTB->iItem-TOOLBAR_ID_START]<=MENU_POPUP_START+MENU_POPUP_COUNT &&
							RefDlgGPMenu!=NULL && *RefDlgGPMenu!=NULL
							)
							(*RefDlgGPMenu)->GPTrackPopupMenu(aPopupMenuInd[lpnmTB->iItem-TOOLBAR_ID_START],TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL,re.left,re.bottom,NULL);
							*pResult=TBDDRET_DEFAULT;
						break;
					}
			}
			catch(...)
			{
				GPC.m_ErrReport.GPWriteErrorLog("GPToolBar", "OnNotify","");
				*str=0;
			}

		}
		break;
	default:
		return CToolBar::OnNotify(wParam, lParam, pResult);
		break;
  }

	if ((wParam&0xFFFF)==(UnitId&0xFFFF)+50000 || wParam>=TOOLBAR_ID_START && wParam<=TOOLBAR_ID_END) return TRUE;
return TRUE;
//	return CToolBar::OnNotify(wParam, lParam, pResult);
}


void GPToolBar::OnTimer(UINT nIDEvent)
{
	if (nIDEvent==CLICK_TIMER_ID)
	{
		KillTimer(nIDEvent);
		m_EnableClick=TRUE;
	}

	CToolBar::OnTimer(nIDEvent);
}

void GPToolBar::SetDropDownMenu(GPMenu **iDlgGPMenu)
{
	RefDlgGPMenu=iDlgGPMenu;
}

void GPToolBar::OnDragMouseHover()
{
	if (referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(GPC.m_DragDrop.DragName)<0xFFFFFFFFL)
	{
		// Reset the timer.
		::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);

		// Get the current cursor position and window height.
		DWORD dwPos = ::GetMessagePos();
		CPoint point(LOWORD(dwPos), HIWORD(dwPos));
		ScreenToClient(&point);

		int nItem = GetToolBarCtrl().HitTest(&point);
		if (nItem<0) nItem=-nItem;
		TBBUTTONINFO tbb={0};
		tbb.cbSize=sizeof(tbb);
		tbb.dwMask=TBIF_TEXT;
		tbb.pszText=new char [300];
		*tbb.pszText=0;
		tbb.cchText=250;
		GetToolBarCtrl().GetButtonInfo(nItem,&tbb);


		CString tmp;
		tmp.Format("%d\x07%s",nItem,tbb.pszText);
		referGPU[UnitId&0xFFFF]->SendDropHoverEvent(tmp,&GPC.m_DragDrop,&point);
		delete[] tbb.pszText;
	}
}

void GPToolBar::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
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

		int nItem = GetToolBarCtrl().HitTest(point);
		if (nItem<0) nItem=-nItem;
		TBBUTTONINFO tbb={0};
		tbb.cbSize=sizeof(tbb);
		tbb.dwMask=TBIF_TEXT;
		tbb.pszText=new char [300];
		*tbb.pszText=0;
		tbb.cchText=250;
		GetToolBarCtrl().GetButtonInfo(nItem,&tbb);

		CString tmp;
		tmp.Format("%d\x07%s",nItem,tbb.pszText);
		referGPU[UnitId&0xFFFF]->SendDropMoveEvent(tmp,pDrDrStruct,point);
		delete[] tbb.pszText;
		if (mDrop)
			::SetTimer(pDrDrStruct->hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nDelayInterval, NULL);
	}
}

void GPToolBar::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && referGPU)
	{
		::ScreenToClient(m_hWnd,point);

		int nItem = GetToolBarCtrl().HitTest(point);
		if (nItem<0) nItem=-nItem;
		TBBUTTONINFO tbb={0};
		tbb.cbSize=sizeof(tbb);
		tbb.dwMask=TBIF_TEXT|TBIF_BYINDEX;
		tbb.pszText=new char [300];
		*tbb.pszText=0;
		tbb.cchText=250;
		GetToolBarCtrl().GetButtonInfo(nItem,&tbb);


		CString tmp;
		tmp.Format("%d\x07%s",nItem,tbb.pszText);
		referGPU[UnitId&0xFFFF]->SendDropEvent(tmp,pDrDrStruct,point);
		delete[] tbb.pszText;
	}
}

DWORD GPToolBar::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	int nItem = GetToolBarCtrl().HitTest(&point);
	if (nItem<0) nItem=-nItem;
	if ((GetToolBarCtrl().GetState(nItem)&TBSTATE_ENABLED)!=TBSTATE_ENABLED)
		nItem=-nItem;
	return nItem;
}

LRESULT GPToolBar::OnNcHitTest(CPoint point)
{
	LRESULT ret=CToolBar::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

#include "GP_TermDoc.h"

void GPToolBar::OnKillFocus(CWnd* pNewWnd)
{
	CToolBar::OnKillFocus(pNewWnd);
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

void GPToolBar::OnSetFocus(CWnd* pOldWnd)
{
	CToolBar::OnSetFocus(pOldWnd);
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


void GPToolBar::OnSize(UINT nType, int cx, int cy)
{
	CToolBar::OnSize(nType, cx, cy);

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
	}
}
