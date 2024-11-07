// GPUnit.cpp: implementation of the GPUnit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GP_term.h"
#include "GPUnit.h"
#include <stdio.h>
#include <process.h>

#include "GP_TermDoc.h"
#include "GP_TermView.h"

#include "GPFrameWnd.h"

#include "GPToolTipCtrl.h"
#include "GP_comm.h"
#include "GPChLBox.h"
#include "GPDrLBox.h"
#include "GPStatic.h"
#include "GPAniStatic.h"
#include "GPEdit.h"
#include "GPButton.h"
#include "GPAniButton.h"
#include "GPBButton.h"
#include "GPListBox.h"
#include "GPComboBox.h"
#include "GPComboBoxEx.h"
#include "GPScrollBar.h"
#include "GPProgress.h"
#include "GPAnimate.h"
#include "GPListCtr.h"
#include "GPDateTimeCtrl.h"
#include "GPMonthCalCtrl.h"
#include "GPSpinButton.h"
#include "GPTabCtrl.h"
#include "GPSlider.h"
#include "GPHeader.h"
#include "GPTree.h"
#include "GP_RTF.h"
#include "GPDlgBar.h"
#include "GPFrameBar.h"
#include "GPStatusBarCtrl.h"
#include "GPStatusBar.h"
#include "GPToolBarCtrl.h"
#include "GPToolBar.h"
#include "GPDialogBar.h"
#include "GPReBarCtrl.h"
#include "GPReBar.h"
#include "GPDrawWnd.h"
#include "WndPrint.h"
#include "GP_Control.h"
#include "HtmlHelp.h"
#include "gpmsflexgrid.h"
#include "GPWebBrowser2.h"
#include "GPScintilla.h"
#include <comdef.h>
#include "ODContextItem.h"

#ifdef W_95
#else
	#ifdef W_NT
	#else
		#ifdef W_98
		#else
			#ifdef W_2000
			#else
#include "uxtheme.h"
			#endif
		#endif
	#endif
#endif


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

GPUnit * GPUnit::m_ptrUnitValChange;
CString GPUnit::m_csLastValueForValChange;
DWORD GPUnit::m_IgnoreMessages;
DWORD GPUnit::m_WarningsIgnore;
RECT GPUnit::reMouseSelection;

const char *GPUnit::cArrMethods[]={
/*00*/	"CalcWindowRect","GetStyle","GetExStyle","SetFocus","Invalidate",
/*05*/	"GetWindowText","ClientToScreen","ScreenToClient","GetClientOffset","InvalidateParent",
/*10*/	"GetFocus","GetNextDlgTabItem","GetWindowTextEx","ShowWindow","SetForegroundWindow",
/*15*/	"FlashWindow","FlashWindowEx","BringWindowToTop","ArrangeIconicWindows","IsIconic",
/*20*/	"IsZoomed","GetWindowRect","GetClientRect","SetWindowPos","MoveWindow",
/*25*/	"SetWindowPlacement","GetWindowPlacement","AnimateWindow","IsWindowEnabled","EnableWindow",
/*30*/	"GetActiveWindow","SetActiveWindow","GetCapture","SetCapture","GetForegroundWindow",
/*35*/	"GetWindowContextHelpId","SetWindowContextHelpId","ChildWindowFromPoint","GetZOrder","SetZOrder",
/*40*/	"SetIcon","GetNextWindow","GetOwner","SetOwner","GetTopWindow",
/*45*/	"GetWindow","GetLastActivePopup","GetParent","SetParent","WindowFromPoint",
/*50*/	"CenterWindow","InvalidateRect","IsWindowVisible","ShowOwnedPopups","EnableScrollBar",
/*55*/	"MapWindowPoints","GetScrollPos","GetScrollRange","SetScrollPos","SetScrollRange",
/*60*/	"ShowScrollBar","SetScrollInfo","GetScrollInfo","GetScrollLimit","ScrollWindow",
/*65*/	"ScrollWindowEx","CreateCaret","GetCaretPos","SetCaretPos","HideCaret",
/*70*/	"ShowCaret","GetNextDlgGroupItem","DrawMenuBar","PrintWnd","TrackMouseEvent",
/*75*/	"HtmlHelp","WinHelp","BeginWaitCursor","EndWaitCursor","SetFocusNextTab",
/*80*/	"SetCursor","SetClassCursor","GetClassCursor","RestoreClassCursor","SetDragName",
/*85*/	"SetDropName","AddDropName","DeleteDropName","SetDropDelay","SetDropScrollInterval",
/*90*/	"SetDropScrollMargin","SetNextParent","SizerAdd","SizerRemove","SizerSet",
/*95*/	"SetWindowText","SizerSetIcon","SizerSetRgn","SizerSetBrush","KeyDown",
/*100*/	"SetWindowTextEx","SetParamDelimiter","AutoSizingReinitMySize","GetChildsText","LockWindowUpdate",
/*105*/ "UnLockWindowUpdate","DrawAnimatedRects","RedrawWindow","UpdateWindow","ValidateRect",
/*110*/	"GetWindowInfo","GetClassName","GetObjectType","MoveWindowEx","ChangeWindowSize",
/*115*/	"SetWindowSize","AutoSizingByActualSize","DoChildsMethod","DoChildsMethodEx","SubclassWindow",
/*120*/ "UnsubclassWindow","GetHWND","DoMethods","GetClassStyle","SetClassStyle",
/*125*/ "SetDirectOutput","GetDirectOutput","SetHScrollMask","SetVScrollMask","SetScrollTimeout",
/*130*/ "SetKeyProc","DeleteKeyProc","SetCheckPoint","GetCurrentValue","GetCurrentValueCRC",
/*135*/ "GetChangedValue","SetValChangeCheckPoint","SetIgnoreSelChangeOnTAB","GetCommonStyle","MoveWindowRelative",
/*140*/ "SetScrollPosFlag","GetScrollPosFlag","SetWindowTheme","SetDrawContext","ODCMethod",
/*145*/ "SetLayeredWindowAttributes","ShowWindowAsync","SetWndEditMode","GetWndEditMode","",
/*150*/ "","","","","",
/*155*/ "","","","","",
	};

const char *GPUnit::cArrMethodsParams[]={
/*00*/	"left,top,right,bottom,nAdjustType","","","","[bErase]",
/*05*/	"","pox,poy","pox,poy","","",
/*10*/	"","","","cmdShow","",
/*15*/	"bInvert","uCount,dwTimeout,Flags","","","",
/*20*/	"","[type]","[type]","x,y,cx,cy,nObjAfter,Style","xTL,yTL,xBR,yBR,bRepaint",
/*25*/	"NormalPosLeft,NormalPosTop,NormalPosRight,NormalPosBottom,MinPosX,MinPosY,MaxPosX,MaxPosY,ShowStyle","","Time,Flags","","bEnable",
/*30*/	"","","","","",
/*35*/	"","HelpId","pox,poy,cFlag","","Obj1^Obj2^Obj3^...",
/*40*/	"nImage,ImageListName","bForvard","","IdObj","",
/*45*/	"FIRST/LAST/NEXT/PREV/OWNER/CHILD/MAX","","","IdObj","pox,poy",
/*50*/	"IdObj","left,top,right,bottom,bErase","","fShow","wSBflags,wArrows",
/*55*/	"nObj,po1x,po1y,po2x,po2y","wSBflags","wSBflags","ipos,bRedr,wSBflags","start,end,bRedr,wSBflags",
/*60*/	"bShow,wSBflags","nMin,nMax,nPage,nPos,nTrackPos,bRedr,wSBflags","wSBflags","wSBflags","XAmount,YAmount,Rectleft,Recttop,Rectright,Rectbottom,ClipRectleft,ClipRecttop,ClipRectright,ClipRectbottom",
/*65*/	"XAmount,YAmount,iTime,Rectleft,Recttop,Rectright,Rectbottom,ClipRectleft,ClipRecttop,ClipRectright,ClipRectbottom,rcUpdateleft,rcUpdatetop,rcUpdateright,rcUpdatebottom","nWidth,nHeight,[GRAY] OR nImage,ImageListName","","pox,poy","",
/*70*/	"","idObj,bPrevious","","bDlg,bOrientation,icPaper","dwHoverTime,CANCEL|HOVER|LEAVE|NONCLIENT",
/*75*/	"File,Command,Data","File,Command,Data","","","nPosition",
/*80*/	"CursorName","CursorName","","","DragName",
/*85*/	"DropName1^DropName2...","DropName1^DropName2...","DropName1^DropName2...","DelayInterval","ScrollInterval",
/*90*/	"ScrollMargin","","Name,Type,Size,MinParentSize,MaxParentSize","Name","Name,Type,Size,MinParentSize,MaxParentSize",
/*95*/	"text","Name,ILName,nImage","Name,RegionName","Name,BRUSH_AS_PROPERTY_BRUSH","lParam,VirtualKey",
/*100*/	"text","DelimiterText","","TypeGroupObj","",
/*105*/ "","start.left,start.top,start.right,start.bottom,end.left,end.top,end.right,end.bottom,style","left,top,right,bottom,style","left,top,right,bottom","",
/*110*/	"","","","DeltaXtl,DeltaYtl,DeltaXbr,DeltaYbr,bRepaint","DeltaCX,DeltaCY,bRepaint,FixPoint",
/*115*/	"CX,CY,bRepaint,FixPoint","","Method params...","Method params...","IdDlg,IdObj  OR  HWND",
/*120*/ "","","","","ClassStyle",
/*125*/ "bOnOff,_CRON|_BSON|_AMON|_VMON|_SVMON|_TABOFF","","[MASK]","[MASK]","ms",
/*130*/ "VKey,[newVK];[Method1][char(2)Method2][....]","[VKey]","","","",
/*135*/ "[bRecursive=TRUE]","","dwIgnore","","[DialogName],[ObjectName],[X],[Y],[CX],[CY]",
/*140*/ "AUTOPOS|","","ClassName","DrawContextName","MethodName MethodParameters",
/*145*/ "R,G,B,A,[COLORKEY|LWA_ALPHA]","cmdShow","","","",
/*150*/ "","","","","",
/*155*/ "","","","","",
	};

int GPUnit::m_UpdateGroupFlagCntr=0;

const UINT GPUnit::uNCCMethods=9;
const char *GPUnit::cArrCCMethods[10]={
	"CCSetBkColor","CCSetColorScheme","CCGetColorScheme","CCSetUnicodeFormat","CCGetUnicodeFormat",
	"CCSetVersion","CCGetVersion","CCSetWindowTheme","CCDPIScale","",
	};
const char *GPUnit::cArrCCMethodsParams[10]={
	"r,g,b","r,g,b,rS,gS,bS","","bUnicode","",
	"nVersion","","themeText","bDPIScale","",
	};

const UINT GPUnit::uNControlBarMethod=9;
const char *GPUnit::cArrControlBarMethod[9]={
		"CBGetBarStyle","CBEnableDocking","CBSetBarStyle","CBGetBorders","CBSetBorders",
		"CBGetCount","CBIsFloating","CBCalcFixedLayout","CBCalcDynamicLayout",
	};

const char *GPUnit::cArrControlBarMethodParams[9]={
		"","DockingStyle","DockingStyle","","cxLeft,cyTop,cxRight,cyBottom",
		"","","bStretch,bHorz","nLength,Mode",
	};

const UINT GPUnit::uNRedrawFlag=12;
const char *GPUnit::aRedrawFlagName[12]={
		"RDW_NOFRAME","RDW_FRAME","RDW_NOWERASE","RDW_NOWUPDATE","RDW_ALLCHILDREN",
		"RDW_NOCHILDREN","RDW_NOERASE","RDW_NOINTERNALPAINT","RDW_VALIDATE","RDW_ERASE",
		"RDW_INTERNALPAINT","RDW_INVALIDATE",
		};
const UINT  GPUnit::aRedrawFlagUINT[12]={
		RDW_NOFRAME, RDW_FRAME, RDW_ERASENOW, RDW_UPDATENOW, RDW_ALLCHILDREN,
		RDW_NOCHILDREN, RDW_NOERASE, RDW_NOINTERNALPAINT, RDW_VALIDATE, RDW_ERASE,
		RDW_INTERNALPAINT, RDW_INVALIDATE,
		};

const char *GPUnit::aTypeUnit[]={
	";0","CONTROL",	"DRAW",
	"ANISTATIC","ANIBUTTON","FRAMEBAR",
	"DATETIMECTRL",	"DLGBAR","RTF",
	"TREECTRL","HEADER",	"SLIDER",
	"TABCTRL","SPINBUTTON","BBUTTON",
	"STATIC",	"EDIT","BUTTON",
	"LISTBOX","COMBOBOX","SCROLLBAR",
	"PROGRESS","ANIMAT","CHECKLISTBOX",
	"DRAGLISTBOX","LISTCTRL",	"STATUSBARCTRL",
	"TOOLBARCTRL","STATUSBAR","TOOLBAR",
	"DIALOGBAR",	"REBARCTRL","REBAR",
	"FLEXGRID","MONTHCAL","WEBBROWSER",
	"COMBOBOXEX","EDITOR",
	"",
};

const int GPUnit::auTypeUnit[]={
	UT_MAINDLGSCR,		UT_CONTROL,			UT_DRAW,
	UT_ANISTATIC,		UT_ANIBUTTON,		UT_FRAMEBAR,
	UT_DATETIMECTRL,	UT_DLGBAR,	UT_RTF,	
	UT_TREECTRL,		UT_HEADER,	UT_SLIDER,
	UT_TABCTRL,			UT_SPINBUTTON,	UT_BBUTTON,	
	UT_STATIC,			UT_EDIT,	UT_BUTTON,		
	UT_LISTBOX,			UT_COMBOBOX,	UT_SCROLLBAR,
	UT_PROGRESS,		UT_ANIMAT,	UT_CHECKLISTBOX,
	UT_DRAGLISTBOX,		UT_LISTCTRL,	UT_STATUSBARCTRL,
	UT_TOOLBARCTRL,		UT_STATUSBAR,	UT_TOOLBAR,		
	UT_DIALOGBAR,		UT_REBARCTRL,	UT_REBARCTRL,	
	UT_FLEXGRID,		UT_MONTHCAL,	UT_WEBBROWSER,	
	UT_COMBOBOXEX,		UT_EDITOR, 
	0,
	};

const char *GPUnit::cArrAlignSize[]={"TOP","BOTTOM","LEFT","RIGHT","ENTIRE"};
const UINT  GPUnit::uArrAlignSize[]={GPUA_TOP,GPUA_BOTTOM,GPUA_LEFT,GPUA_RIGHT,GPUA_ENTIRE,};

const UINT GPUnit::uNClassStyles=13;
const char *GPUnit::cArrClassStyles[]=
	{
		"CS_VREDRAW",	"CS_HREDRAW",	"CS_DBLCLKS",	"CS_OWNDC",	"CS_CLASSDC",
		"CS_PARENTDC",	"CS_NOCLOSE",	"CS_SAVEBITS",	"CS_BYTEALIGNCLIENT",	"CS_BYTEALIGNWINDOW",
		"CS_GLOBALCLASS",	"CS_IME",	"CS_DROPSHADOW",
	};
const UINT  GPUnit::uArrClassStyles[]=
	{
		CS_VREDRAW,	CS_HREDRAW,	CS_DBLCLKS,	CS_OWNDC,	CS_CLASSDC,
		CS_PARENTDC,	CS_NOCLOSE,	CS_SAVEBITS,	CS_BYTEALIGNCLIENT,	CS_BYTEALIGNWINDOW,
		CS_GLOBALCLASS,	CS_IME,	CS_DROPSHADOW,
	};


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPUnit::GPUnit(UINT iUnitId, UINT iUnitType, const char *iInitSrc, GPUnit **iGPU, CGPToolTipCtrl **ipToolTip, HWND iUnitHWND, GP_AutoSizing *iAUSI)
{
	dwWndEditFlag=0;
	m_ODC=NULL;
	m_NGPUNIT=1;
	dwScrollFlags=0;
	char *iInit=new char [(int)strlen(iInitSrc)+100];
	strcpy(iInit,iInitSrc);
	UnitCommonStyles=0;
	m_IgnoreSelectionOnTAB=0;
	m_dwValChangeFlag=0;
	m_LastValChangeCRC=0;
	m_Scale=GPC.m_GUISet.Scale;
	UnitFont=NULL;
	m_clrText = m_clrBkgnd =-1;
	m_brBkgnd= NULL;
	m_bkgSrc=-1;
	m_BkgMode=-1;
	m_DirectOutputFlag=0;
	m_LastDIChar=0;
	iArrTimerCount=NULL;

	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwCreateObj++;
	m_UpdateGroupFlag=0;
	m_WindowLessFlag=0;
	if (strstr(iInit,"WS_WINDOWLESS")) m_WindowLessFlag=1;
	m_ParamDelimiter=",";
	m_SizerArray=NULL;
	m_ObjName="";
	m_NCHITTESTflag=0;
	m_nDelayInterval = 500;		// Default delay interval = 500 milliseconds
	m_nScrollInterval = 200;	// Default scroll interval = 200 milliseconds
	m_nScrollMargin = 10;		// Default scroll margin = 10 pixels

	m_DrawContextName=ExtractField(ExtractField(iInitSrc,2,"DRAWCONTEXT="),1,";");
	m_DropNamesArray=NULL;
	m_KeyRedefine=NULL;

	char *pp;
	GPMSG=NULL;
	m_OldHCURSOR=NULL;
	SizStyle=0;
	UnitHotkey=NULL;
	GPU=iGPU;
	GroupNum=NULL;
	CurGroupSelection=-1;
	CRect ir;
	UnitHWND=NULL;
	UINT iStyle=0,iStyleEx=0;
	UnitId=iUnitId;
	UnitType=iUnitType;
	UnitPtr=NULL;
	m_ToolTip=ipToolTip;
	ToolTipText=NULL;
	NoUpdateParent=FALSE;
	AUSI=iAUSI;
	if (iUnitType==UT_MAINDLGSCR) UnitHWND=iUnitHWND;
	else UnitHWND=NULL;

	char *iCapt=new char [(int)strlen(iInit)+1000];
	char *m_CLSID=new char [(int)strlen(iInit)+1000];
	*iCapt=0;
	*m_CLSID=0;

	GetInitParam(this,UnitType,iInit,iStyle,iStyleEx,ir,iCapt,&ParentNum,m_CLSID,m_Scale);

	HWND TmpParent=NULL;
	if (iUnitType!=UT_MAINDLGSCR)
	{
		TmpParent=GPU[0]->UnitHWND;
		if (ParentNum > (*GPU)->m_NGPUNIT)
		{
			TmpParent=GetDesktopWindow();
		}
		else
			if (GPU[ParentNum] && GPU[ParentNum]->UnitHWND)
				TmpParent=GPU[ParentNum]->UnitHWND;
	}
	GPMSG=new GPMessage(aUnitMessage[UnitType],GPU,UnitId);

	iUnitId=(UnitId&0xFFFF)+50000;
	if (UnitType!=UT_MAINDLGSCR)
	{
		if (UnitType!=UT_DLGBAR && UnitType!=UT_FRAMEBAR)
		{
			if ((iStyle&WS_POPUP)!=WS_POPUP) iStyle|=WS_CHILD;
			if (TmpParent==NULL) TmpParent=GPC.m_hViewWnd;
		}
		else
		{
			if ((iStyle&WS_CHILD)!=WS_CHILD && (iStyleEx&WS_EX_MDICHILD)!=WS_EX_MDICHILD) iStyle|=WS_POPUP;
			else
			{
				iStyle&=(0xFFFFFFFF^WS_POPUP);
				iStyle|=WS_CHILD;
			}
		}
		GPU[UnitId&0xFFFF]=this;
	}

	switch(UnitType)
	{
		case UT_DRAW:
			UnitPtr		=(void *)new GPDrawWnd(UnitId, GPU);
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				((GPDrawWnd*)UnitPtr)->CreateEx(iStyleEx,NULL,iCapt,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				UnitHWND=((GPDrawWnd*)UnitPtr)->m_hWnd;
			}
			break;

/*
		case UT_DRAW:
			UnitPtr		=(void *)new GPDrawWnd(UnitId, GPU);
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				((GPDrawWnd*)UnitPtr)->CreateEx(iStyleEx,NULL,iCapt,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				UnitHWND=((GPDrawWnd*)UnitPtr)->m_hWnd;
				((GPDrawWnd*)UnitPtr)->m_DrawContext.m_CurHWND=UnitHWND;
				((GPDrawWnd*)UnitPtr)->m_DrawContext.m_CurDialogGPU=GPU;
			}
			break;
*/
		case UT_DATETIMECTRL:
			UnitPtr		=(void *)new GPDateTimeCtrl(UnitId);
			((GPDateTimeCtrl *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				((GPDateTimeCtrl*)UnitPtr)->CreateEx(iStyleEx,DATETIMEPICK_CLASS,iCapt,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				UnitHWND=((GPDateTimeCtrl*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_MONTHCAL:
			UnitPtr		=(void *)new GPMonthCalCtrl(UnitId);
			((GPMonthCalCtrl *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				((GPMonthCalCtrl*)UnitPtr)->CreateEx(iStyleEx,MONTHCAL_CLASS,iCapt,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				UnitHWND=((GPMonthCalCtrl*)UnitPtr)->m_hWnd;
			}
			break;

		case UT_CONTROL:
			{
				UnitPtr	=(void *)new GP_Control(UnitId);
				((GP_Control *)UnitPtr)->referGPU=GPU;
				((GP_Control *)UnitPtr)->tmpWnd=new CGPContainer;

//strcpy(m_CLSID,"ExBRIZAX.ExampleBRIZAXFlex,tmpa\\ExampleBRIZActiveXproject.ocx /s");
//strcpy(m_CLSID,"ExBRIZActiveX.ExampleBRIZActiveX,tmpa\\ExampleBRIZActiveXproject.ocx /s");
				char *posFileName=strchr(m_CLSID,',');
				if (posFileName)
					*(posFileName++)=0;
				else posFileName="";

				do
				{
					((GP_Control *)UnitPtr)->Create(NULL,iCapt,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);

					CRect re22=ir;
					re22-=re22.TopLeft();
					((GP_Control *)UnitPtr)->tmpWnd->CreateControl(m_CLSID,NULL,iStyle,re22,((GP_Control *)UnitPtr),iUnitId,NULL,FALSE);
					UnitHWND=((GP_Control *)UnitPtr)->m_hWnd;
					if (posFileName && !*posFileName) posFileName=NULL;
					while(!((GP_Control *)UnitPtr)->tmpWnd->m_hWnd && posFileName && *posFileName)
					{
						char *postmp2=strchr(posFileName,',');
						if (postmp2) *(postmp2++)=0;
						else postmp2="";
						char tmpssss[600];
						GetSystemDirectory(tmpssss,500);
						strcat(tmpssss,"\\RegSvr32.exe");
						_spawnl(_P_WAIT,tmpssss,tmpssss,posFileName,NULL);
						posFileName=postmp2;
					}

				}
				while(!((GP_Control *)UnitPtr)->tmpWnd->m_hWnd && posFileName);

				if (UnitHWND)
				{
//					((GP_Control *)UnitPtr)->SubclassWindow(((GP_Control *)UnitPtr)->tmpWnd->Detach());
					BSTR sss=GPC.m_TermRegName.AllocSysString();
					::SendMessage(((GP_Control *)UnitPtr)->tmpWnd->m_hWnd,GPM_AX_SETREGNAME,0,(LPARAM)(&sss));
					::SysFreeString(sss);
				}
			}
			break;
		case UT_FRAMEBAR:
			UnitPtr	=(void *)new GPFrameBar;
			((GPFrameBar *)UnitPtr)->UnitId=UnitId;
			((GPFrameBar *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				((GPFrameBar *)UnitPtr)->CreateFrameBar(iStyleEx,iCapt,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				UnitHWND=((GPFrameBar*)UnitPtr)->m_hWnd;
			}
			break;

		case UT_DLGBAR:
			UnitPtr	=(void *)new GPDlgBar(UnitId,iInit);
			((GPDlgBar *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				((GPDlgBar *)UnitPtr)->CreateDlgBar(iStyleEx,iCapt,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId,iInit,m_Scale);
				UnitHWND=((GPDlgBar*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_RTF:
			UnitPtr	=(void *)new GP_RTF(UnitId);
			((GP_RTF *)UnitPtr)->referGPU=GPU;
//			((GP_RTF *)UnitPtr)->CreateEx(iStyleEx,RICHEDIT_CLASS,NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				((GP_RTF *)UnitPtr)->Create(iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				((GP_RTF *)UnitPtr)->ModifyStyleEx(0,iStyleEx);
				((GP_RTF *)UnitPtr)->DoMethod("SetTextMode RICHTEXT|MULTILEVELUNDO|TM_SINGLECODEPAGE|",NULL);
				UnitHWND=((GP_RTF*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_EDITOR:
			UnitPtr	=(void *)new GPScintilla(UnitId);
			((GPScintilla *)UnitPtr)->referGPU=GPU;
			m_IgnoreSelectionOnTAB=2;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				((GPScintilla *)UnitPtr)->CreateEx(iStyleEx,"Scintilla","",iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId,NULL);
				UnitHWND=((GPScintilla*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_TREECTRL:
			UnitPtr	=(void *)new GPTree(UnitId);
			((GPTree *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				#ifndef _VC80_UPGRADE
					((GPTree *)UnitPtr)->CreateEx(iStyleEx,WC_TREEVIEW,NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#else
					((GPTree *)UnitPtr)->CreateEx(iStyleEx,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#endif
				UnitHWND=((GPTree*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_HEADER:
			UnitPtr	=(void *)new GPHeader(UnitId);
			((GPHeader *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				#ifndef _VC80_UPGRADE
					((GPHeader *)UnitPtr)->CreateEx(iStyleEx,WC_HEADER,NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#else
					((GPHeader *)UnitPtr)->CreateEx(iStyleEx,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#endif
				UnitHWND=((GPHeader*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_SLIDER:
			UnitPtr	=(void *)new GPSlider(UnitId);
			((GPSlider *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				#ifndef _VC80_UPGRADE
					((GPSlider *)UnitPtr)->CreateEx(iStyleEx,TRACKBAR_CLASS,NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#else
					((GPSlider *)UnitPtr)->CreateEx(iStyleEx,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#endif
				UnitHWND=((GPSlider*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_TABCTRL:
			UnitPtr	=(void *)new GPTabCtrl(UnitId);
			((GPTabCtrl *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				#ifndef _VC80_UPGRADE
					((GPTabCtrl *)UnitPtr)->CreateEx(iStyleEx,WC_TABCONTROL,NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#else
					((GPTabCtrl *)UnitPtr)->CreateEx(iStyleEx,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#endif
				UnitHWND=((GPTabCtrl*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_SPINBUTTON:
			UnitPtr	=(void *)new GPSpinButton(UnitId);
			((GPSpinButton *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				#ifndef _VC80_UPGRADE
					((GPSpinButton *)UnitPtr)->CreateEx(iStyleEx,UPDOWN_CLASS,NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#else
					((GPSpinButton *)UnitPtr)->CreateEx(iStyleEx,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#endif
				UnitHWND=((GPSpinButton*)UnitPtr)->m_hWnd;
	//			if (UnitHWND)	::SetWindowLong(UnitHWND,GWL_EXSTYLE,iStyleEx)
			}
			break;
		case UT_STATIC:
			UnitPtr		=(void *)new GPStatic(UnitId);
			((GPStatic *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				((GPStatic *)UnitPtr)->CreateEx(iStyleEx,_T("STATIC"),NULL, iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				UnitHWND=((GPStatic*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_ANISTATIC:
			UnitPtr		=(void *)new GPAniStatic(UnitId);
			((GPAniStatic *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				((GPAniStatic *)UnitPtr)->CreateEx(iStyleEx,_T("STATIC"),NULL, iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				UnitHWND=((GPStatic*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_EDIT:
			UnitPtr	=(void *)new GPEdit(UnitId);
			((GPEdit *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				((GPEdit *)UnitPtr)->CreateEx(iStyleEx,_T("EDIT"),NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				UnitHWND=((GPEdit*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_BUTTON:
			UnitPtr		=(void *)new GPButton(UnitId);
			((GPButton *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				((GPButton *)UnitPtr)->CreateEx(iStyleEx,_T("BUTTON"),iCapt,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				UnitHWND=((GPButton*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_ANIBUTTON:
			UnitPtr		=(void *)new GPAniButton(UnitId);
			((GPAniButton *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				((GPAniButton *)UnitPtr)->CreateEx(iStyleEx,_T("BUTTON"),iCapt,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				UnitHWND=((GPAniButton*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_BBUTTON:
			UnitPtr		=(void *)new GPBButton(UnitId);
			((GPBButton *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				((GPBButton*)UnitPtr)->CreateEx(iStyleEx,_T("BUTTON"),iCapt,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				UnitHWND=((GPBButton*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_LISTBOX:
			UnitPtr		=(void *)new GPListBox(UnitId);
			((GPListBox *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				((GPListBox *)UnitPtr)->CreateEx(iStyleEx,_T("LISTBOX"),NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				UnitHWND=((GPListBox*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_COMBOBOX:
			UnitPtr		=(void *)new GPComboBox(UnitId);
			((GPComboBox *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				((GPComboBox *)UnitPtr)->CreateEx(iStyleEx,_T("COMBOBOX"),NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				UnitHWND=((GPComboBox*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_COMBOBOXEX:
			UnitPtr		=(void *)new GPComboBoxEx(UnitId);
			((GPComboBoxEx *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				#ifndef _VC80_UPGRADE
					((GPComboBoxEx *)UnitPtr)->CreateEx(iStyleEx,WC_COMBOBOXEX,NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#else
					((GPComboBoxEx *)UnitPtr)->CreateEx(iStyleEx,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#endif
				UnitHWND=((GPComboBoxEx*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_SCROLLBAR:
			UnitPtr		=(void *)new GPScrollBar(UnitId);
			((GPScrollBar *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				((GPScrollBar *)UnitPtr)->CreateEx(iStyleEx,_T("SCROLLBAR"),NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				UnitHWND=((GPScrollBar*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_PROGRESS:
			UnitPtr		=(void *)new GPProgress(UnitId);
			((GPProgress *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				#ifndef _VC80_UPGRADE
					((GPProgress *)UnitPtr)->CreateEx(iStyleEx,PROGRESS_CLASS,NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#else
					((GPProgress *)UnitPtr)->CreateEx(iStyleEx,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#endif
				UnitHWND=((GPProgress*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_ANIMAT:
			UnitPtr		=(void *)new GPAnimate(UnitId);
			((GPAnimate *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				#ifndef _VC80_UPGRADE
					((GPAnimate *)UnitPtr)->CreateEx(iStyleEx,ANIMATE_CLASS,NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#else
					((GPAnimate *)UnitPtr)->CreateEx(iStyleEx,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#endif
				UnitHWND=((GPAnimate*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_CHECKLISTBOX:
			if ((iStyle&LBS_OWNERDRAWFIXED)!=LBS_OWNERDRAWFIXED && (iStyle&LBS_OWNERDRAWVARIABLE)!=LBS_OWNERDRAWVARIABLE) iStyle|=LBS_OWNERDRAWFIXED;
			iStyle|=LBS_HASSTRINGS;
			UnitPtr		=(void *)new GPChLBox(UnitId);
			((GPChLBox *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				((GPChLBox *)UnitPtr)->CreateEx(iStyleEx,_T("LISTBOX"),NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				UnitHWND=((GPChLBox*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_DRAGLISTBOX:
//			if ((iStyle&LBS_OWNERDRAWFIXED)!=LBS_OWNERDRAWFIXED && (iStyle&LBS_OWNERDRAWVARIABLE)!=LBS_OWNERDRAWVARIABLE) iStyle|=LBS_OWNERDRAWFIXED;
			UnitPtr		=(void *)new GPDrLBox(UnitId);
			((GPDrLBox *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				((GPDrLBox *)UnitPtr)->CreateEx(iStyleEx,_T("LISTBOX"),NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				UnitHWND=((GPDrLBox*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_LISTCTRL:
			UnitPtr		=(void *)new GPListCtr(UnitId);
			((GPListCtr *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				#ifndef _VC80_UPGRADE
					((GPListCtr *)UnitPtr)->CreateEx(iStyleEx,WC_LISTVIEW,NULL,iStyle|LVS_SHAREIMAGELISTS,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#else
					((GPListCtr *)UnitPtr)->CreateEx(iStyleEx,iStyle|LVS_SHAREIMAGELISTS,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#endif
				//((GPListCtr *)UnitPtr)->Create(iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				UnitHWND=((GPListCtr*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_STATUSBARCTRL:
			UnitPtr		=(void *)new GPStatusBarCtrl(UnitId);
			((GPStatusBarCtrl *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				#ifndef _VC80_UPGRADE
					((GPStatusBarCtrl *)UnitPtr)->CreateEx(iStyleEx,STATUSCLASSNAME,NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#else
					((GPStatusBarCtrl *)UnitPtr)->CreateEx(iStyleEx,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#endif
				UnitHWND=((GPStatusBarCtrl*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_STATUSBAR:
			UnitPtr		=(void *)new GPStatusBar(UnitId);
			((GPStatusBar *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				((GPStatusBar *)UnitPtr)->CreateEx(CWnd::FromHandle(TmpParent),iStyleEx,iStyle,iUnitId);
				((GPStatusBar*)UnitPtr)->m_bAutoDelete=TRUE;
				UnitHWND=((GPStatusBar*)UnitPtr)->m_hWnd;
				sprintf(iCapt,"CBSetBarStyle %s",iInit);
				((GPStatusBar*)UnitPtr)->DoMethod(iCapt,NULL);
				::PostMessage(TmpParent,WM_SIZE,SIZE_RESTORED,0x00000);
			}
			break;
		case UT_TOOLBARCTRL:
			UnitPtr		=(void *)new GPToolBarCtrl(UnitId);
			((GPToolBarCtrl *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				#ifndef _VC80_UPGRADE
					((GPToolBarCtrl *)UnitPtr)->CreateEx(iStyleEx,TOOLBARCLASSNAME,NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#else
					((GPToolBarCtrl *)UnitPtr)->CreateEx(iStyleEx,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#endif
				UnitHWND=((GPToolBarCtrl*)UnitPtr)->m_hWnd;
			}
			break;
		case UT_TOOLBAR:
			UnitPtr		=(void *)new GPToolBar(UnitId);
			((GPToolBar *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				((GPToolBar *)UnitPtr)->CreateEx(CWnd::FromHandle(TmpParent),iStyleEx,iStyle,CRect(0,0,0,0),iUnitId);
				UnitHWND=((GPToolBar*)UnitPtr)->m_hWnd;
				((GPToolBar*)UnitPtr)->m_bAutoDelete=TRUE;
				((GPToolBar*)UnitPtr)->GetToolBarCtrl().SetOwner(CWnd::FromHandle(UnitHWND));
				sprintf(iCapt,"CBSetBarStyle %s",iInit);
				((GPToolBar*)UnitPtr)->DoMethod(iCapt,NULL);
				::PostMessage(TmpParent,WM_SIZE,SIZE_RESTORED,0x00000);
			}
			break;
		case UT_DIALOGBAR:
			UnitPtr		=(void *)new GPDialogBar(UnitId);
			((GPDialogBar *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				((GPDialogBar *)UnitPtr)->Create(CWnd::FromHandle(TmpParent),IDD_DIALOGBAR,iStyle,iUnitId);
				UnitHWND=((GPDialogBar*)UnitPtr)->m_hWnd;
	//			((GPDialogBar*)UnitPtr)->SetOwner(CWnd::FromHandle(UnitHWND));
			}
			break;
		case UT_REBARCTRL:
			UnitPtr		=(void *)new GPReBarCtrl(UnitId);
			((GPReBarCtrl *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				#ifndef _VC80_UPGRADE
					((GPReBarCtrl *)UnitPtr)->CreateEx(iStyleEx,REBARCLASSNAME,NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#else
					((GPReBarCtrl *)UnitPtr)->CreateEx(iStyleEx,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
				#endif
				UnitHWND=((GPReBarCtrl*)UnitPtr)->m_hWnd;
				((GPReBarCtrl*)UnitPtr)->SetOwner(CWnd::FromHandle(UnitHWND));
			}
			break;
		case UT_REBAR:
			UnitPtr		=(void *)new GPReBar(UnitId);
			((GPReBar *)UnitPtr)->referGPU=GPU;
			if (m_WindowLessFlag)	UnitHWND=NULL;
			else
			{
				((GPReBar *)UnitPtr)->Create(CWnd::FromHandle(TmpParent),iStyleEx,iStyle,iUnitId);
				((GPReBar*)UnitPtr)->m_bAutoDelete=TRUE;
				UnitHWND=((GPReBar*)UnitPtr)->m_hWnd;
				sprintf(iCapt,"CBSetBarStyle %s",iInit);
				((GPReBar*)UnitPtr)->DoMethod(iCapt,NULL);
				::PostMessage(TmpParent,WM_SIZE,SIZE_RESTORED,0x00000);
			}
			break;
		case UT_FLEXGRID:
			{
				int cnt=0;
				UnitPtr	=(void *)new GPCMSFlexGrid(UnitId);
				((GPCMSFlexGrid *)UnitPtr)->referGPU=GPU;
				if (m_WindowLessFlag)
					UnitHWND=NULL;
				else
				{
					while(UnitHWND==NULL && cnt<10)
					{
						cnt++;
						try
						{
							switch(cnt)
							{
							case 1:	case 6:
								{
									WORD lpDWData[] = {
											0x0024, 0x0000, 0x0037, 0x0032, 0x0045, 0x0036, 0x0037, 0x0031, 0x0032, 
											0x0030, 0x002d, 0x0035, 0x0039, 0x0035, 0x0039, 0x002d, 0x0031, 0x0031, 
											0x0063, 0x0066, 0x002d, 0x0039, 0x0031, 0x0046, 0x0036, 0x002d, 0x0043, 
											0x0032, 0x0038, 0x0036, 0x0033, 0x0043, 0x0033, 0x0038, 0x0035, 0x0045, 
											0x0033, 0x0030, 0x0012, 0x0000, 0x0001, 0x0000, 0x000a, 0x0000, 0x004c, 
											0x0000, 0x0000, 0x4321, 0x1234, 0x0008, 0x0000, 0x1477, 0x0000, 0x085f, 
											0x0000, 0x6f42, 0x506f, 0x0000, 0x0006, 0x0080, 0x0000, 0x0002, 0x0000, 
											0x0002, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000, 0x0000, 0x0000, 0x0005, 
											0x8000, 0x0008, 0x8000, 0x000f, 0x8000, 0x0012, 0x8000, 0x000d, 0x8000, 
											0x000e, 0x8000, 0x8080, 0x0080, 0xc0c0, 0x00c0, 0x0000, 0x0000, 0x0000, 
											0x0000, 0x0001, 0x0000, 0x0001, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000, 
											0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0000, 0x0001, 0x0002, 
											0x0003, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0000, 0x0001, 
											0x0004, 0x0000, 0x0000, 0x0000, 0x5203, 0x0be3, 0x8f91, 0x11ce, 0xe39d, 
											0xaa00, 0x4b00, 0x51b8, 0xcc01, 0x0000, 0x0190, 0x4244, 0x0001, 0x4d0d, 
											0x2053, 0x6153, 0x736e, 0x5320, 0x7265, 0x6669, 0x5204, 0x0be3, 0x8f91, 
											0x11ce, 0xe39d, 0xaa00, 0x4b00, 0x51b8, 0x746c, 0x0000, 0x0000, 0x0000
												};
									BYTE* lpData,* lpData2;
									BSTR bstrLicKey = NULL;
									CLSID clsid;
									int cb = 306;
									int i;

									lpData2=lpData = new BYTE[306];
									for(i = 0;i<153;i++)
									{
										lpData[2*i] = 0xFF & lpDWData[i];
										lpData[(2*i) + 1] = lpDWData[i] >> 8;
									}
									// extract license key data, if any
									{
										ULONG cchLicKey = *(UNALIGNED ULONG*)lpData;
										lpData += sizeof(ULONG);
										cb -= sizeof(ULONG);
										if (cchLicKey > 0)
										{
											bstrLicKey = SysAllocStringLen((LPCOLESTR)lpData, cchLicKey);
											lpData += cchLicKey * sizeof(WCHAR);
											cb -= cchLicKey * sizeof(WCHAR);
										}
									}

									clsid=((GPCMSFlexGrid *)UnitPtr)->GetClsid();
									((GPCMSFlexGrid *)UnitPtr)->CreateControl(clsid,NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId,NULL,FALSE,bstrLicKey);
									if (bstrLicKey != NULL)
										SysFreeString(bstrLicKey);
									if (((GPCMSFlexGrid *)UnitPtr)->m_hWnd)
									{
										UnitHWND=((GPCMSFlexGrid *)UnitPtr)->m_hWnd;
									}
									else UnitHWND=NULL;
									if (lpData2) delete[] lpData2;
									lpData2=NULL;
								}
								break;
							case 2:	case 7:
								((GPCMSFlexGrid *)UnitPtr)->CreateControl("MSFlexGridLib.MSFlexGrid",NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
								break;
							case 3:	case 8:
								((GPCMSFlexGrid *)UnitPtr)->CreateControl("{6B93DE84-A00D-47B0-9A78-114E8B0CF652}",NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
								break;
							case 4:	case 9:
								((GPCMSFlexGrid *)UnitPtr)->CreateControl("{6262D3A0-531B-11CF-91F6-C2863C385E30}",NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
								break;
							case 5:	case 10:
								((GPCMSFlexGrid *)UnitPtr)->CreateControl("{5F4DF280-531B-11CF-91F6-C2863C385E30}",NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
								break;
							}

							if (((GPCMSFlexGrid *)UnitPtr)->m_hWnd)
							{
								UnitHWND=((GPCMSFlexGrid *)UnitPtr)->m_hWnd;
	//							UnitHWND=(HWND)((GPCMSFlexGrid*)UnitPtr)->GetHWnd();
								if (UnitHWND) ((GPCMSFlexGrid*)UnitPtr)->ModifyStyleEx(0,iStyleEx);
							}
							else UnitHWND=NULL;
						}
						catch(...)
						{
							GPC.m_ErrReport.GPWriteErrorLog("GPUnit", "GPUnit 888","");
						}
						if (UnitHWND==NULL  && cnt==4) ((GPCMSFlexGrid *)UnitPtr)->InstallFlex();
					}
				}
			}
			break;
		case UT_WEBBROWSER:
			{
				int cnt=0;
				UnitPtr	=(void *)new GPWebBrowser2(UnitId);
				((GPWebBrowser2 *)UnitPtr)->referGPU=GPU;
				if (m_WindowLessFlag)
					UnitHWND=NULL;
				else
				{

					while(UnitHWND==NULL && cnt<8)
					{
						cnt++;
						try
						{
							switch(cnt)
							{
							case 1:	case 5:
								((GPWebBrowser2 *)UnitPtr)->Create(NULL,NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
								break;
							case 2:	case 6:
								((GPWebBrowser2 *)UnitPtr)->CreateControl("Shell.Explorer",NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
								break;
							case 3:	case 7:
								((GPWebBrowser2 *)UnitPtr)->CreateControl("{8856F961-340A-11D0-A96B-00C04FD705A2}",NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
								break;
							case 4:	case 8:
								((GPWebBrowser2 *)UnitPtr)->CreateControl("{EAB22AC3-30C1-11CF-A7EB-0000C05BAE0B}",NULL,iStyle,ir,CWnd::FromHandle(TmpParent),iUnitId);
								break;
							}

							if (((GPWebBrowser2 *)UnitPtr)->m_hWnd)
							{
								UnitHWND=((GPWebBrowser2 *)UnitPtr)->m_hWnd;
								if (UnitHWND) ::SetWindowLong(UnitHWND,GWL_EXSTYLE,iStyleEx);
							}
							else UnitHWND=NULL;
						}
						catch(...)
						{
							GPC.m_ErrReport.GPWriteErrorLog("GPUnit", "GPUnit 935","");
						}
					}
				}
			}
			break;
	}
	if ((iStyle&WS_CHILD)==WS_CHILD)
		switch(UnitType)
		{
		case UT_COMBOBOX:
		case UT_COMBOBOXEX:
				#ifdef W_XP
				#else
					break;
				#endif		
		case UT_ANIMAT:
		case UT_DRAW:
		case UT_DATETIMECTRL:
		case UT_MONTHCAL:
		case UT_DLGBAR:
		case UT_FRAMEBAR:
		case UT_RTF:
		case UT_EDITOR:
		case UT_TREECTRL:
		case UT_SLIDER:
		case UT_TABCTRL:
		case UT_SPINBUTTON:
		case UT_BUTTON:
		case UT_ANIBUTTON:
		case UT_BBUTTON:
		case UT_STATIC:
		case UT_ANISTATIC:
		case UT_EDIT:
		case UT_LISTBOX:
		case UT_PROGRESS:
		case UT_CHECKLISTBOX:
		case UT_DRAGLISTBOX:
		case UT_LISTCTRL:
		case UT_TOOLBAR:
		case UT_DIALOGBAR:
		case UT_REBARCTRL:
		case UT_WEBBROWSER:
		case UT_CONTROL:
		case UT_FLEXGRID:
			{
				CRect re;
				::GetWindowRect(UnitHWND,&re);
				CPoint po(0,0);
				ClientToScreen(::GetParent(UnitHWND),&po);
				re-=po;
				::MoveWindow(UnitHWND,re.left,re.top,re.Width()+1,re.Height()+1,0);
				::MoveWindow(UnitHWND,re.left,re.top,re.Width(),re.Height(),0);
			}
			break;
		case UT_HEADER:
		case UT_SCROLLBAR:
		case UT_STATUSBARCTRL:
		case UT_TOOLBARCTRL:
		case UT_STATUSBAR:
		case UT_REBAR:		
		case UT_MAINDLGSCR:
			break;
		}

	strcpy(iCapt,iInit);
	char *posiCapt=strstr(iCapt,";NAME=");
	if (posiCapt && posiCapt!=iCapt && posiCapt[-1]==';')  strcpy(posiCapt-1,posiCapt);

	if (UnitType!=UT_MAINDLGSCR) 
		CheckGroups(UnitId&0xFFFF);

	if (m_WindowLessFlag==0)
	{
		switch(UnitType)
		{
		case UT_DIALOGBAR:
		case UT_REBARCTRL:
		case UT_REBAR:
		case UT_STATUSBARCTRL:
		case UT_STATUSBAR:
//		case UT_TOOLBAR:
			while((pp=strstr(iCapt,"STYLE="))) *pp='_';
			::SendMessage(::GetParent(UnitHWND),WM_APP+1,0,0);
			break;
		case UT_MAINDLGSCR:
			while((pp=strstr(iCapt,"STYLE="))) *pp='_';
			break;
		}


		if (strstr(iInit,"FONT=")==NULL && UnitType!=UT_RTF && UnitType!=UT_EDITOR)
		{
			if ((int)strlen(iInit)>0 && iInit[(int)strlen(iInit)-1]!=';') strcat(iCapt,";");
			strcat(iCapt,"FONT=CURRENT;");
		}
		if (UnitType!=UT_MAINDLGSCR) while((pp=strstr(iCapt,"WS_"))) *pp='_';

		if ((UnitType==UT_MAINDLGSCR || UnitType==UT_DLGBAR || UnitType==UT_FRAMEBAR) && UnitHWND)
		{
			char *ppos;
			ppos=strstr(iCapt,"FONT=");
			if (ppos) *ppos='_';

		/*	if (strstr(iCapt,"DS_CENTER"))
			{
				ppos=strstr(iCapt,"RECT=");
				if (ppos)
				{
					*ppos='_';
					ppos+=5;
					CRect rrr,r2;
					::GetWindowRect(UnitHWND,&rrr);
					r2=ir;
					r2.OffsetRect(-r2.TopLeft());
					r2.OffsetRect(rrr.TopLeft());
					char strtmp[150];
					sprintf(strtmp,"RECT=%d,%d,%d,%d;",r2.left,r2.top,r2.right,r2.bottom);
					RemappingProperty(strtmp);
				}
			}*/

			if (UnitType==UT_DLGBAR || UnitType==UT_FRAMEBAR)
			{
				while((pp=strstr(iCapt,"WS_"))) *pp='_';
				while((pp=strstr(iCapt,"DS_"))) *pp='_';
			}
		}

		if (UnitHWND) m_OldHCURSOR=(HCURSOR)GetClassLong(UnitHWND,GCL_HCURSOR);
		RemappingProperty(iCapt);
	}
	if (m_ObjName=="")
	{
		char *posname=strstr(iCapt,";NAME=");
		if (posname==NULL && strncmp(iCapt,"NAME=",5)==0) posname=iCapt;
		if (posname)
		{
			if (*posname==';') posname++;
			if (posname!=iCapt && posname[-2]==';')
			{
				strcpy(posname-1,posname);
				posname--;
			}
			posname+=5;
			char *tmp=strchr(posname,';');
			if (tmp) *tmp=0;
			m_ObjName=posname;
		}
		else
		if (this->UnitHWND==GetDesktopWindow()) m_ObjName="DESKTOP";
		else		m_ObjName.Format("%d",(UnitId&0xFFFF));
	}
	delete[] iCapt;
	delete[] m_CLSID;
	delete[] iInit;
}

GPUnit::~GPUnit()
{
//	TRACE("~GPUnit %s\n",UnitInfoToString("\x01") );
	if (m_ptrUnitValChange==this) 
	{
		m_ptrUnitValChange=NULL;
//			TRACE("m_ptrUnitValChange=NULL ~GPUnit %s\n",UnitInfoToString("\x01") );
	}
	if (m_DirectOutputFlag)
		GPC.DirecOutputArray.RemoveItemByVal((DWORD)this);
	m_DirectOutputFlag=0;

	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwDeleteObj++;
	if (m_SizerArray) delete m_SizerArray;
	m_SizerArray=NULL;

	if (m_DropNamesArray)
	{
		m_DropNamesArray->ResetArray();
		delete m_DropNamesArray;
		m_DropNamesArray=NULL;
	}

	if (m_KeyRedefine)
	{
		m_KeyRedefine->ResetArray();
		delete m_KeyRedefine;
		m_KeyRedefine=NULL;
	}

	if (UnitHotkey) delete[] UnitHotkey;
	UnitHotkey=NULL;

	if (UnitPtr)
	{
		if (UnitType==UT_FLEXGRID && CWnd::FromHandlePermanent(UnitHWND)) ((GPCMSFlexGrid *)UnitPtr)->ClearAllData();
		try
		{
			if (*m_ToolTip && UnitHWND && (*m_ToolTip)->m_hWnd) (*m_ToolTip)->DelTool(CWnd::FromHandle(UnitHWND));
		} catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("GPUnit", "~GPUnit 1094","");
		}

		try
		{
			if (UnitHWND && CWnd::FromHandlePermanent(UnitHWND)) ::DestroyWindow(UnitHWND);
		} catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("GPUnit", "~GPUnit 1102","");
		}

		try
		{
			switch(UnitType)
			{
			case UT_MAINDLGSCR: /*cwnd*/								break;
			case UT_CONTROL:		delete ((GP_Control *)UnitPtr);		break;
			case UT_DRAW:			delete ((GPDrawWnd *)UnitPtr);		break;
			case UT_DATETIMECTRL:	delete ((GPDateTimeCtrl *)UnitPtr);	break;
			case UT_MONTHCAL:		delete ((GPMonthCalCtrl *)UnitPtr);	break;
			case UT_DLGBAR:			delete ((GPDlgBar *)UnitPtr);		break;
			case UT_FRAMEBAR:		delete ((GPFrameBar *)UnitPtr);		break;
			case UT_RTF: 			delete ((GP_RTF*)UnitPtr);			break;
			case UT_EDITOR: 		delete ((GPScintilla*)UnitPtr);		break;
			case UT_TREECTRL:		delete ((GPTree*)UnitPtr);			break;
			case UT_HEADER:			delete ((GPHeader*)UnitPtr);		break;
			case UT_SLIDER:			delete ((GPSlider*)UnitPtr);		break;
			case UT_TABCTRL:		delete ((GPTabCtrl*)UnitPtr);		break;
			case UT_SPINBUTTON:		delete ((GPSpinButton*)UnitPtr);	break;
			case UT_BUTTON:			delete ((GPButton *)UnitPtr);		break;
			case UT_ANIBUTTON:		delete ((GPAniButton *)UnitPtr);	break;
			case UT_BBUTTON:		delete ((GPBButton*)UnitPtr);		break;
			case UT_STATIC:			delete ((GPStatic *)UnitPtr);		break;
			case UT_ANISTATIC:		delete ((GPAniStatic *)UnitPtr);	break;
			case UT_EDIT:			delete ((GPEdit *)UnitPtr);			break;
			case UT_LISTBOX:		delete ((GPListBox *)UnitPtr);		break;
			case UT_COMBOBOX:		delete ((GPComboBox *)UnitPtr);		break;
			case UT_COMBOBOXEX:		delete ((GPComboBoxEx *)UnitPtr);		break;
			case UT_SCROLLBAR:		delete ((GPScrollBar *)UnitPtr);	break;
			case UT_PROGRESS:		delete ((GPProgress *)UnitPtr);		break;
			case UT_ANIMAT:			delete ((GPAnimate *)UnitPtr);		break;
			case UT_CHECKLISTBOX:	delete ((GPChLBox *)UnitPtr);		break;
			case UT_DRAGLISTBOX:	delete ((GPDrLBox *)UnitPtr);		break;
			case UT_LISTCTRL: 		delete ((GPListCtr *)UnitPtr);		break;
			case UT_STATUSBARCTRL: 	delete ((GPStatusBarCtrl *)UnitPtr);break;
			case UT_TOOLBARCTRL: 	delete ((GPToolBarCtrl *)UnitPtr);	break;
			case UT_STATUSBAR: 		delete ((GPStatusBar *)UnitPtr);	break;
			case UT_TOOLBAR: 		delete ((GPToolBar *)UnitPtr);		break;
			case UT_DIALOGBAR: 		delete ((GPDialogBar *)UnitPtr);	break;
			case UT_REBARCTRL: 		delete ((GPReBarCtrl *)UnitPtr);	break;
			case UT_REBAR:	 		delete ((GPReBar *)UnitPtr);		break;
			case UT_FLEXGRID:		delete ((GPCMSFlexGrid *)UnitPtr);	break;
			case UT_WEBBROWSER:		delete ((GPWebBrowser2 *)UnitPtr);	break;
			}// end TypeUnit Switch
		} catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("GPUnit", "~GPUnit 1154","");
		}
	}

	UnitPtr=NULL;

	try
	{
		if (AUSI)	AUSI->DeleteWnd(UnitHWND);
	} catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPUnit", "~GPUnit 1165","");
	}

	try
	{
		if (ToolTipText) delete ToolTipText;
	} catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPUnit", "~GPUnit 1173","");
	}
	ToolTipText=NULL;

	try
	{
		if (GroupNum) delete[] GroupNum;
	} catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPUnit", "~GPUnit 1182","");
	}
	GroupNum=NULL;

	try
	{
		if (GPMSG) delete GPMSG;
	} catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPUnit", "~GPUnit 1191","");
	}
	GPMSG=NULL;

	if (m_brBkgnd) delete m_brBkgnd;
	m_brBkgnd=NULL;

	if (UnitFont) delete UnitFont;
	UnitFont=NULL;

	if (iArrTimerCount)
	{
		int i;
		for(i=0;i<50;i++)
			KillTimer(UnitHWND,i+20000);

		delete[] iArrTimerCount;
	}
	iArrTimerCount=NULL;
	if (m_ODC) delete m_ODC;
}

void GPUnit::SetReferGPU(GPUnit **newGPU)
{
	switch(UnitType)
	{
	case UT_MAINDLGSCR:		break;
	case UT_CONTROL:		((GP_Control *)UnitPtr)->referGPU=newGPU;		break;
	case UT_DRAW:			((GPDrawWnd *)UnitPtr)->referGPU=newGPU;		break;
	case UT_DATETIMECTRL:	((GPDateTimeCtrl *)UnitPtr)->referGPU=newGPU;	break;
	case UT_MONTHCAL:		((GPMonthCalCtrl *)UnitPtr)->referGPU=newGPU;	break;
	case UT_DLGBAR:			((GPDlgBar *)UnitPtr)->referGPU=newGPU;		break;
	case UT_FRAMEBAR:		((GPFrameBar *)UnitPtr)->referGPU=newGPU;		break;
	case UT_RTF: 			((GP_RTF*)UnitPtr)->referGPU=newGPU;			break;
	case UT_EDITOR: 		((GPScintilla*)UnitPtr)->referGPU=newGPU;		break;
	case UT_TREECTRL:		((GPTree*)UnitPtr)->referGPU=newGPU;			break;
	case UT_HEADER:			((GPHeader*)UnitPtr)->referGPU=newGPU;		break;
	case UT_SLIDER:			((GPSlider*)UnitPtr)->referGPU=newGPU;		break;
	case UT_TABCTRL:		((GPTabCtrl*)UnitPtr)->referGPU=newGPU;		break;
	case UT_SPINBUTTON:		((GPSpinButton*)UnitPtr)->referGPU=newGPU;	break;
	case UT_BUTTON:			((GPButton *)UnitPtr)->referGPU=newGPU;		break;
	case UT_ANIBUTTON:		((GPAniButton *)UnitPtr)->referGPU=newGPU;	break;
	case UT_BBUTTON:		((GPBButton*)UnitPtr)->referGPU=newGPU;		break;
	case UT_STATIC:			((GPStatic *)UnitPtr)->referGPU=newGPU;		break;
	case UT_ANISTATIC:		((GPAniStatic *)UnitPtr)->referGPU=newGPU;	break;
	case UT_EDIT:			((GPEdit *)UnitPtr)->referGPU=newGPU;			break;
	case UT_LISTBOX:		((GPListBox *)UnitPtr)->referGPU=newGPU;		break;
	case UT_COMBOBOX:		((GPComboBox *)UnitPtr)->referGPU=newGPU;		break;
	case UT_COMBOBOXEX:		((GPComboBoxEx *)UnitPtr)->referGPU=newGPU;		break;
	case UT_SCROLLBAR:		((GPScrollBar *)UnitPtr)->referGPU=newGPU;	break;
	case UT_PROGRESS:		((GPProgress *)UnitPtr)->referGPU=newGPU;		break;
	case UT_ANIMAT:			((GPAnimate *)UnitPtr)->referGPU=newGPU;		break;
	case UT_CHECKLISTBOX:	((GPChLBox *)UnitPtr)->referGPU=newGPU;		break;
	case UT_DRAGLISTBOX:	((GPDrLBox *)UnitPtr)->referGPU=newGPU;		break;
	case UT_LISTCTRL: 		((GPListCtr *)UnitPtr)->referGPU=newGPU;		break;
	case UT_STATUSBARCTRL: 	((GPStatusBarCtrl *)UnitPtr)->referGPU=newGPU;break;
	case UT_TOOLBARCTRL: 	((GPToolBarCtrl *)UnitPtr)->referGPU=newGPU;	break;
	case UT_STATUSBAR: 		((GPStatusBar *)UnitPtr)->referGPU=newGPU;	break;
	case UT_TOOLBAR: 		((GPToolBar *)UnitPtr)->referGPU=newGPU;		break;
	case UT_DIALOGBAR: 		((GPDialogBar *)UnitPtr)->referGPU=newGPU;	break;
	case UT_REBARCTRL: 		((GPReBarCtrl *)UnitPtr)->referGPU=newGPU;	break;
	case UT_REBAR:	 		((GPReBar *)UnitPtr)->referGPU=newGPU;		break;
	case UT_FLEXGRID:		((GPCMSFlexGrid *)UnitPtr)->referGPU=newGPU;	break;
	case UT_WEBBROWSER:		((GPWebBrowser2 *)UnitPtr)->referGPU=newGPU;	break;
	}// end TypeUnit Switch

}

void GPUnit::RemappingProperty(const char *iStr)
{
	const char *pos=iStr;
	char *str=new char [(int)strlen(iStr)+100];
	while(*pos!=0)
	{
		char *pos2=str;
		while(*pos!=0)
		{
			if (*pos==';' && pos[1]!=';') break;
			if ((*pos==';' && pos[1]==';') || (*pos=='=' && pos[1]=='=')) pos++;
			*(pos2++)=*(pos++);
		}
		if (*pos==';') pos++;
		while (*pos!=0 && *pos==' ') pos++;
		*pos2=0;
		if (strchr(str,'='))
			GPSetProperty(str);
	}
	delete[] str;
}

int GPUnit::GetInitParam(GPUnit *mThis, unsigned int UnitType, char *iInit, UINT &InitStyle, UINT &InitStyleEx,  CRect &InitRect, char *iCaption, UINT *ParentNum, char *m_CLSID, DWORD &iScale)
{
	int i;
	char *str=new char [(int)strlen(iInit)+20];
	strcpy(str,iInit);
	char *pos=strstr(str,";NAME=");
	if (pos && pos!=str && pos[-1]==';')  strcpy(pos-1,pos);
	pos=strstr(str,"STYLE=");
	char *pos2;
	if (pos && (pos2=strchr(pos,';'))) *pos2=0;
	InitStyle=0;

	if (pos)
	{
		strcat(pos,"|");

		// standart
		for(i=0;i<N_WND_STYLES;i++)
			if (strstr(pos,aWndStyleName[i]))
				InitStyle|=aWndStyleUINT[i];

		for(i=0;i<N_WND_EX_STYLES;i++)
			if (strstr(pos,aWndExStyleName[i]))
				InitStyleEx|=aWndExStyleUINT[i];

		switch(UnitType)
		{
		case UT_MAINDLGSCR:
		case UT_FRAMEBAR:
		case UT_DLGBAR:
			break;
		default:
			InitStyle|=WS_CHILD;
			break;
		}

		switch(UnitType)
		{
		case UT_MAINDLGSCR:
		case UT_FRAMEBAR:
		case UT_DLGBAR:
			{	// standart
				for(i=0;i<N_DLG_STYLES;i++)
					if (strstr(pos,aDlgStyleName[i]))
						InitStyle|=aDlgStyleUINT[i];
				break;
			}
		case UT_DATETIMECTRL:
				for(i=0;i<N_DATETIME_STYLES;i++)
					if (strstr(pos,aDateTimeStyleName[i]))
						InitStyle|=aDateTimeStyleUINT[i];
				break;
		case UT_MONTHCAL:
				for(i=0;i<N_MONTHCAL_STYLES;i++)
					if (strstr(pos,aMonthCalStyleName[i]))
						InitStyle|=aMonthCalStyleUINT[i];
				break;
		case UT_RTF:
				for(i=0;i<N_RTF_STYLES;i++)
					if (strstr(pos,aRTFStyleName[i]))
						InitStyle|=aRTFStyleUINT[i];
				break;
		case UT_EDITOR:
				break;
		case UT_TREECTRL:
				for(i=0;i<N_TREECTRL_STYLES;i++)
					if (strstr(pos,aTreeCtrlStyleName[i]))
						InitStyle|=aTreeCtrlStyleUINT[i];
				break;
		case UT_HEADER:
				for(i=0;i<N_HEADER_STYLES;i++)
					if (strstr(pos,aHeaderStyleName[i]))
						InitStyle|=aHeaderStyleUINT[i];
				for(i=0;i<N_COMCTRL_STYLES;i++)
					if (strstr(pos,aComCtrlStyleName[i]))
						InitStyle|=aComCtrlStyleUINT[i];
				break;
		case UT_STATUSBARCTRL:
				for(i=0;i<N_COMCTRL_STYLES;i++)
					if (strstr(pos,aComCtrlStyleName[i]))
						InitStyle|=aComCtrlStyleUINT[i];
				for(i=0;i<N_STATUSBARCTRL_STYLES;i++)
					if (strstr(pos,aStatusBarCtrlStyleName[i]))
						InitStyle|=aStatusBarCtrlStyleUINT[i];
				break;
		case UT_REBARCTRL:
				for(i=0;i<N_COMCTRL_STYLES;i++)
					if (strstr(pos,aComCtrlStyleName[i]))
						InitStyle|=aComCtrlStyleUINT[i];
				for(i=0;i<N_REBARCTRL_STYLES;i++)
					if (strstr(pos,aReBarCtrlStyleName[i]))
						InitStyle|=aReBarCtrlStyleUINT[i];
				break;
		case UT_REBAR:
				for(i=0;i<N_REBARCTRL_STYLES;i++)
					if (strstr(pos,aReBarCtrlStyleName[i]))
						InitStyle|=aReBarCtrlStyleUINT[i];
				for(i=0;i<N_CTRLBAR_STYLES;i++)
					if (strstr(pos,aCtrlBarStyleName[i]))
						InitStyle|=aCtrlBarStyleUINT[i];
				break;
		case UT_STATUSBAR:
				for(i=0;i<N_STATUSBARCTRL_STYLES;i++)
					if (strstr(pos,aStatusBarCtrlStyleName[i]))
						InitStyle|=aStatusBarCtrlStyleUINT[i];
				for(i=0;i<N_CTRLBAR_STYLES;i++)
					if (strstr(pos,aCtrlBarStyleName[i]))
						InitStyle|=aCtrlBarStyleUINT[i];
				break;
		case UT_TOOLBARCTRL:
				for(i=0;i<N_COMCTRL_STYLES;i++)
					if (strstr(pos,aComCtrlStyleName[i]))
						InitStyle|=aComCtrlStyleUINT[i];
				for(i=0;i<N_TOOLBARCTRL_STYLES;i++)
					if (strstr(pos,aToolBarCtrlStyleName[i]))
						InitStyle|=aToolBarCtrlStyleUINT[i];
				break;
		case UT_TOOLBAR:
				for(i=0;i<N_TOOLBARCTRL_STYLES;i++)
					if (strstr(pos,aToolBarCtrlStyleName[i]))
						InitStyle|=aToolBarCtrlStyleUINT[i];
				for(i=0;i<N_CTRLBAR_STYLES;i++)
					if (strstr(pos,aCtrlBarStyleName[i]))
						InitStyle|=aCtrlBarStyleUINT[i];
				break;
		case UT_DIALOGBAR:
				for(i=0;i<N_CTRLBAR_STYLES;i++)
					if (strstr(pos,aCtrlBarStyleName[i]))
						InitStyle|=aCtrlBarStyleUINT[i];
				break;
		case UT_SLIDER:
				for(i=0;i<N_SLIDER_STYLES;i++)
					if (strstr(pos,aSliderStyleName[i]))
						InitStyle|=aSliderStyleUINT[i];
				break;
		case UT_TABCTRL:
				for(i=0;i<N_TAB_STYLES;i++)
					if (strstr(pos,aTabStyleName[i]))
						InitStyle|=aTabStyleUINT[i];
				break;
		case UT_SPINBUTTON:
				for(i=0;i<N_SPIN_STYLES;i++)
					if (strstr(pos,aSpinStyleName[i]))
						InitStyle|=aSpinStyleUINT[i];
				break;
		case UT_STATIC:
		case UT_ANISTATIC:
				for(i=0;i<N_STATIC_STYLES;i++)
					if (strstr(pos,aStaticStyleName[i]))
						InitStyle|=aStaticStyleUINT[i];
				break;
		case UT_EDIT:
				for(i=0;i<N_EDIT_STYLES;i++)
					if (strstr(pos,aEditStyleName[i]))
						InitStyle|=aEditStyleUINT[i];
				break;
		case UT_BBUTTON:
		case UT_ANIBUTTON:
		case UT_BUTTON:
				for(i=0;i<N_BUTTON_STYLES;i++)
					if (strstr(pos,aButtonStyleName[i]))
						InitStyle|=aButtonStyleUINT[i];
				break;
		case UT_DRAGLISTBOX:
		case UT_CHECKLISTBOX:
		case UT_LISTBOX:
				for(i=0;i<N_LISTBOX_STYLES;i++)
					if (strstr(pos,aListBoxStyleName[i]))
						InitStyle|=aListBoxStyleUINT[i];
				break;
		case UT_COMBOBOX:
				for(i=0;i<N_COMBOBOX_STYLES;i++)
					if (strstr(pos,aComboBoxStyleName[i]))
						InitStyle|=aComboBoxStyleUINT[i];
				break;
		case UT_COMBOBOXEX:
				for(i=0;i<N_COMBOBOXEX_STYLES;i++)
					if (strstr(pos,aComboBoxExStyleName[i]))
						InitStyle|=aComboBoxExStyleUINT[i];
				break;
		case UT_SCROLLBAR:
				for(i=0;i<N_SCROLL_STYLES;i++)
					if (strstr(pos,aScrollStyleName[i]))
						InitStyle|=aScrollStyleUINT[i];
				break;
		case UT_PROGRESS:
				for(i=0;i<N_PROGRESS_STYLES;i++)
					if (strstr(pos,aProgressStyleName[i]))
						InitStyle|=aProgressStyleUINT[i];
				break;
		case UT_ANIMAT:
				for(i=0;i<N_ANIMATION_STYLES;i++)
					if (strstr(pos,aAnimationStyleName[i]))
						InitStyle|=aAnimationStyleUINT[i];
				break;
		case UT_LISTCTRL:
				for(i=0;i<N_LISTCTRL_STYLES;i++)
					if (strstr(pos,aListCtrlStyleName[i]))
						InitStyle|=aListCtrlStyleUINT[i];
				break;
		case UT_DRAW:
				break;
		}// end TypeUnit Switch
	}


	strcpy(str,iInit);
	if ((pos=strstr(str,"TEXT=")))
	{
		pos+=5;
		pos2=pos;
		while(*pos2!=0)
		{
			if (*pos2==';' && pos2[1]!=';') break;
			if (*pos2==';' && pos2[1]==';') pos2++;
			pos2++;
		}
		*pos2=0;
		strcpy(iCaption,pos);
	}
	else *iCaption=0;

	strcpy(str,iInit);
	if ((pos=strstr(str,"CLSID=")))
	{
		pos+=6;
		pos2=pos;
		while(*pos2!=0)
		{
			if (*pos2==';' && pos2[1]!=';') break;
			if (*pos2==';' && pos2[1]==';') pos2++;
			pos2++;
		}
		*pos2=0;
		strcpy(m_CLSID,pos);
	}
	else *m_CLSID=0;

	*ParentNum=0;
	if ((pos=strstr(iInit,"PARENT=")))
	{
		if (mThis) *ParentNum=mThis->GetObjectIdByName(pos+7);
		else *ParentNum=atoi(pos+7);
		*pos='_';
	}
	if (!mThis || !mThis->GPU || !mThis->GPU[0] || *ParentNum>=(*(mThis->GPU))->m_NGPUNIT) *ParentNum=0;
	else
		if (*ParentNum && (!mThis || !mThis->GPU || !mThis->GPU[*ParentNum] || !mThis->GPU[*ParentNum]->UnitHWND)) *ParentNum=0;


	iScale=GPC.m_GUISet.Scale;
	strcpy(str,iInit);
	DWORD tmpParentScale=iScale;
	if (mThis && mThis->GPU && mThis->GPU[*ParentNum]) tmpParentScale=mThis->GPU[*ParentNum]->m_Scale;

	if ((pos=strstr(str,"SCALE=")))
	{
		UINT tmpScale=atoi(pos+6);
		if (tmpScale>=30 && tmpScale<=500) iScale=tmpScale;
		*pos='_';
	}
	else
		iScale=tmpParentScale;

	if ((pos=strstr(iInit,"RECT=")))
	{
		int iCaptScale=iScale;
		m_LastScanf=sscanf(pos+5,"%d,%d,%d,%d",&InitRect.left,&InitRect.top,&InitRect.right,&InitRect.bottom);
		if ((InitStyle&WS_POPUP)==WS_POPUP)
		{
			InitRect.right=InitRect.left+(InitRect.Width()*((int)iScale))/100;
			InitRect.bottom=InitRect.top+(InitRect.Height()*((int)iScale))/100;
		}
		else
		{
			iCaptScale=tmpParentScale;
			InitRect.top=(InitRect.top*((int)tmpParentScale))/100;
			InitRect.bottom=(InitRect.bottom*((int)tmpParentScale))/100;
			InitRect.left=(InitRect.left*((int)tmpParentScale))/100;
			InitRect.right=(InitRect.right*((int)tmpParentScale))/100;
		}

		if ((InitStyle&WS_CAPTION)==WS_CAPTION)
		{
			int iCYCaption=0;
			if ((InitStyleEx&WS_EX_TOOLWINDOW)==WS_EX_TOOLWINDOW)
				iCYCaption=(::GetSystemMetrics(SM_CYSMCAPTION)-16)-16*iCaptScale/100+16;
			else
				iCYCaption=(::GetSystemMetrics(SM_CYCAPTION)-19)-19*iCaptScale/100+19;
			InitRect.bottom+=iCYCaption;
		}
//		if ((InitStyle&WS_CHILD)==WS_CHILD) 
		{
			pos2=strchr(pos,';');
			if (pos2++==NULL) pos2="";
			strcpy(str,pos2);
			sprintf(pos,"RECT=%d,%d,%d,%d;%s",InitRect.left,InitRect.top,InitRect.right,InitRect.bottom,str);
			*pos='_';
		}
	}
	else 
	{
		if ((pos=strstr(iInit,"_ECT=")))
			m_LastScanf=sscanf(pos+5,"%d,%d,%d,%d",&InitRect.left,&InitRect.top,&InitRect.right,&InitRect.bottom);
		else InitRect.SetRect(10,10,50,20);
	}

	delete[] str;
	return 0;
}


UINT GPUnit::DoMethod(const char *iStr, char *oStr)
{
	UINT reti=0xFFFFFFFFL;

	if (oStr) *oStr=0;

	if (iStr[1]=='_' && (iStr[0]=='D' || iStr[0]=='d'))
	{
		if (UnitHWND)
		{
			char *tmpMeth=new char[(int)strlen(iStr)];
			strcpy(tmpMeth,iStr+2);
			::PostMessage(UnitHWND,GPM_DOMETHOD,(WPARAM)oStr,(LPARAM) tmpMeth);
		}
	}
	else
	{
		if (UnitPtr && UnitHWND)
		{
			switch(UnitType)
			{
			case UT_MAINDLGSCR: 								break;
			case UT_CONTROL:		reti=((GP_Control *)UnitPtr)->	DoMethod(iStr,oStr);		break;
			case UT_DRAW:	 		reti=((GPDrawWnd *)UnitPtr)->	DoMethod(iStr,oStr);		break;
			case UT_DATETIMECTRL: 	reti=((GPDateTimeCtrl *)UnitPtr)->DoMethod(iStr,oStr);	break;
			case UT_MONTHCAL:		reti=((GPMonthCalCtrl *)UnitPtr)->DoMethod(iStr,oStr);	break;
			case UT_DLGBAR: 		reti=((GPDlgBar*)UnitPtr)->		DoMethod(iStr,oStr);		break;
			case UT_FRAMEBAR: 		reti=((GPFrameBar*)UnitPtr)->	DoMethod(iStr,oStr);		break;
			case UT_RTF: 			reti=((GP_RTF*)UnitPtr)->		DoMethod(iStr,oStr);		break;
			case UT_EDITOR: 		reti=((GPScintilla*)UnitPtr)->	DoMethod(iStr,oStr);		break;
			case UT_TREECTRL: 		reti=((GPTree*)UnitPtr)->		DoMethod(iStr,oStr);		break;
			case UT_HEADER:			reti=((GPHeader*)UnitPtr)->		DoMethod(iStr,oStr);		break;
			case UT_SLIDER: 		reti=((GPSlider*)UnitPtr)->		DoMethod(iStr,oStr);		break;
			case UT_TABCTRL:		reti=((GPTabCtrl*)UnitPtr)->	DoMethod(iStr,oStr);		break;
			case UT_SPINBUTTON:		reti=((GPSpinButton*)UnitPtr)->	DoMethod(iStr,oStr);		break;
			case UT_BUTTON:			reti=((GPButton *)UnitPtr)->	DoMethod(iStr,oStr);		break;
			case UT_ANIBUTTON:		reti=((GPAniButton *)UnitPtr)->	DoMethod(iStr,oStr);		break;
			case UT_BBUTTON:		reti=((GPBButton*)UnitPtr)->	DoMethod(iStr,oStr);		break;
			case UT_STATIC:			reti=((GPStatic *)UnitPtr)->	DoMethod(iStr,oStr);		break;
			case UT_ANISTATIC:		reti=((GPAniStatic *)UnitPtr)->	DoMethod(iStr,oStr);		break;
			case UT_EDIT: 			reti=((GPEdit *)UnitPtr)->		DoMethod(iStr,oStr);		break;
			case UT_LISTBOX:		reti=((GPListBox *)UnitPtr)->	DoMethod(iStr,oStr);		break;
			case UT_COMBOBOX:		reti=((GPComboBox *)UnitPtr)->	DoMethod(iStr,oStr);		break;
			case UT_COMBOBOXEX:		reti=((GPComboBoxEx *)UnitPtr)->DoMethod(iStr,oStr);		break;
			case UT_SCROLLBAR:		reti=((GPScrollBar *)UnitPtr)->	DoMethod(iStr,oStr);		break;
			case UT_PROGRESS:		reti=((GPProgress *)UnitPtr)->	DoMethod(iStr,oStr);		break;
			case UT_ANIMAT:			reti=((GPAnimate *)UnitPtr)->	DoMethod(iStr,oStr);		break;
			case UT_CHECKLISTBOX:	reti=((GPChLBox *)UnitPtr)->	DoMethod(iStr,oStr);		break;
			case UT_DRAGLISTBOX:	reti=((GPDrLBox *)UnitPtr)->	DoMethod(iStr,oStr);		break;
			case UT_LISTCTRL:		reti=((GPListCtr *)UnitPtr)->	DoMethod(iStr,oStr);		break;
			case UT_STATUSBARCTRL: 	reti=((GPStatusBarCtrl *)UnitPtr)->DoMethod(iStr,oStr);	break;
			case UT_TOOLBARCTRL: 	reti=((GPToolBarCtrl *)UnitPtr)->DoMethod(iStr,oStr);	break;
			case UT_STATUSBAR:		reti=((GPStatusBar *)UnitPtr)->	DoMethod(iStr,oStr);		break;
			case UT_TOOLBAR:		reti=((GPToolBar *)UnitPtr)->	DoMethod(iStr,oStr);		break;
			case UT_DIALOGBAR:		reti=((GPDialogBar *)UnitPtr)->	DoMethod(iStr,oStr);		break;
			case UT_REBARCTRL:		reti=((GPReBarCtrl *)UnitPtr)->	DoMethod(iStr,oStr);		break;
			case UT_REBAR:			reti=((GPReBar *)UnitPtr)->	DoMethod(iStr,oStr);			break;
			case UT_FLEXGRID:		reti=((GPCMSFlexGrid *)UnitPtr)->DoMethod(iStr,oStr);	break;
			case UT_WEBBROWSER:		reti=((GPWebBrowser2 *)UnitPtr)->DoMethod(iStr,oStr);	break;
			}// end TypeUnit Switch
		}
		else reti=0xFFFFFFFFL;

		if (reti==0xFFFFFFFFL)
		{
			reti=DoWindowMethod(iStr, oStr);
			if (reti==FALSE && m_ToolTip && *m_ToolTip && UnitHWND) reti=(*m_ToolTip)->DoMethod(iStr, oStr, UnitHWND);
			if (reti==FALSE && UnitHWND) reti=DoCCMethod(iStr, oStr);
			if (reti==FALSE && UnitHWND && !m_WarningsIgnore)
			{
				GPC.m_ErrReport.GPWriteWarnLog2("GPUnit unknown method", UnitInfoToString("\x01"),iStr);
			}
		}
	}

	return reti;
}

UINT GPUnit::GPSetProperty(const char *iStr)
{
	char *iValue=new char [(int)strlen(iStr)+5];
	strcpy(iValue,iStr);
	UINT ret=1,i;
	char *pos=strchr(iValue,'=');
	if (UnitType==UT_MAINDLGSCR && UnitHWND==NULL)
		ret=3;
	else
	if (UnitPtr)
		switch(UnitType)
		{
		case UT_MAINDLGSCR: 		if (UnitHWND==NULL)				ret=3; break;
		case UT_DRAW: 			ret= ((GPDrawWnd*)UnitPtr)->GPSetProperty(iValue);		break;
		case UT_DATETIMECTRL:	ret= ((GPDateTimeCtrl *)UnitPtr)->GPSetProperty(iValue);break;
		case UT_MONTHCAL:		ret= ((GPMonthCalCtrl *)UnitPtr)->GPSetProperty(iValue);break;
		case UT_DLGBAR: 		ret= ((GPDlgBar*)UnitPtr)->GPSetProperty(iValue);		break;
		case UT_FRAMEBAR: 		ret= ((GPFrameBar*)UnitPtr)->GPSetProperty(iValue);		break;
		case UT_RTF: 			ret= ((GP_RTF*)UnitPtr)->GPSetProperty(iValue);			break;
		case UT_CONTROL:		ret= ((GP_Control *)UnitPtr)->GPSetProperty(iValue);	break;
		case UT_EDITOR: 		ret= ((GPScintilla*)UnitPtr)->GPSetProperty(iValue);	break;
		case UT_TREECTRL:		ret= ((GPTree*)UnitPtr)->GPSetProperty(iValue);			break;
		case UT_HEADER:			ret= ((GPHeader*)UnitPtr)->GPSetProperty(iValue);		break;
		case UT_SLIDER: 		ret= ((GPSlider*)UnitPtr)->GPSetProperty(iValue);		break;
		case UT_TABCTRL: 		ret= ((GPTabCtrl*)UnitPtr)->GPSetProperty(iValue);		break;
		case UT_SPINBUTTON:		ret= ((GPSpinButton*)UnitPtr)->GPSetProperty(iValue);	break;
		case UT_BUTTON: 		ret= ((GPButton *)UnitPtr)->GPSetProperty(iValue);		break;
		case UT_ANIBUTTON: 		ret= ((GPAniButton *)UnitPtr)->GPSetProperty(iValue);	break;
		case UT_BBUTTON: 		ret= ((GPBButton*)UnitPtr)->GPSetProperty(iValue);		break;
		case UT_STATIC: 		ret= ((GPStatic *)UnitPtr)->GPSetProperty(iValue);		break;
		case UT_ANISTATIC: 		ret= ((GPAniStatic *)UnitPtr)->GPSetProperty(iValue);	break;
		case UT_EDIT: 			ret= ((GPEdit *)UnitPtr)->GPSetProperty(iValue);		break;
		case UT_LISTBOX: 		ret= ((GPListBox *)UnitPtr)->GPSetProperty(iValue);		break;
		case UT_COMBOBOX: 		ret= ((GPComboBox *)UnitPtr)->GPSetProperty(iValue);	break;
		case UT_COMBOBOXEX:		ret= ((GPComboBoxEx *)UnitPtr)->GPSetProperty(iValue);	break;
		case UT_SCROLLBAR: 		ret= ((GPScrollBar *)UnitPtr)->GPSetProperty(iValue);	break;
		case UT_PROGRESS: 		ret= ((GPProgress *)UnitPtr)->GPSetProperty(iValue);	break;
		case UT_ANIMAT: 		ret= ((GPAnimate *)UnitPtr)->GPSetProperty(iValue);		break;
		case UT_CHECKLISTBOX: 	ret= ((GPChLBox *)UnitPtr)->GPSetProperty(iValue);		break;
		case UT_DRAGLISTBOX:	ret= ((GPDrLBox *)UnitPtr)->GPSetProperty(iValue);		break;
		case UT_LISTCTRL:		ret= ((GPListCtr *)UnitPtr)->GPSetProperty(iValue);		break;
		case UT_STATUSBARCTRL:	ret= ((GPStatusBarCtrl *)UnitPtr)->GPSetProperty(iValue);break;
		case UT_TOOLBARCTRL:	ret= ((GPToolBarCtrl *)UnitPtr)->GPSetProperty(iValue);	break;
		case UT_STATUSBAR:		ret= ((GPStatusBar *)UnitPtr)->GPSetProperty(iValue);	break;
		case UT_TOOLBAR:		ret= ((GPToolBar *)UnitPtr)->GPSetProperty(iValue);		break;
		case UT_DIALOGBAR:		ret= ((GPDialogBar *)UnitPtr)->GPSetProperty(iValue);	break;
		case UT_REBARCTRL:		ret= ((GPReBarCtrl *)UnitPtr)->GPSetProperty(iValue);	break;
		case UT_REBAR:			ret= ((GPReBar *)UnitPtr)->GPSetProperty(iValue);		break;
		case UT_FLEXGRID:		ret= ((GPCMSFlexGrid *)UnitPtr)->GPSetProperty(iValue);	break;
		case UT_WEBBROWSER:		ret= ((GPWebBrowser2 *)UnitPtr)->GPSetProperty(iValue);	break;
		}

	if (pos && ret!=3)
	{
		char *prop[]=
		{
			"ENABLE",		"VISIBLE",		"FRG",		"BKG",		"PEN",
			"BRUSH",		"TEXT",			"RECT",		"ADDSTYLE", "DELSTYLE",
			"STYLE",		"FONT",			"FONT2",	"TALIGN",	"TOOLTIP",
			"PARENT",		"GROUP",		"DELSIZING","SIZING",	"MINSIZE",
			"MAXSIZE",		"MINPOS",		"MAXPOS",	"FRALIGN",	"FRSIZING",
			"MRECT",		"DRECT",		"REGION",	"NCHITANS",	"NAME",
			"ADDTTSTYLE",	"DELTTSTYLE",	"TTSTYLE",	"BKGMODE",	"BKGSRC",
			"SCALE",
		};
		int propnum;
		*(pos++)=0;
		for(propnum=0;propnum<GP_NPROPERTY && strcmp(prop[propnum],iValue)!=0;propnum++);
		if (propnum==GP_NPROPERTY || (UnitHWND==NULL && propnum!=29)) ret=2;
		else
		{
			int nunit;
			try
			{
			switch(propnum)
			{
			case 0: /* enable*/
				{
					BOOL rv=strstr(pos,"FALSE")==NULL;
					char strtmp[50];
					sprintf(strtmp,",%d,",(UnitId&0xFFFF));
					if (UnitHWND && CWnd::FromHandle(UnitHWND))
					{
						CWnd::FromHandle(UnitHWND)->ModifyStyle(rv?WS_DISABLED:0,rv?0:WS_DISABLED);
						CWnd::FromHandle(UnitHWND)->Invalidate();
					}

					if (m_UpdateGroupFlag && UnitType!=UT_MAINDLGSCR && UnitHWND)
					{
						if (++m_UpdateGroupFlagCntr<10)
							for(nunit=1;(UINT)nunit<(*GPU)->m_NGPUNIT;nunit++)
								if (GPU[nunit] && GPU[nunit]->GroupNum && strstr(GPU[nunit]->GroupNum,strtmp))
								{
									char str[150];sprintf(str,"ENABLE=%s",pos);
									GPU[nunit]->GPSetProperty(str);
								}
						m_UpdateGroupFlagCntr--;
					}

				}
				break;
			case 1: // visible
				{
					char strtmp[50];
					sprintf(strtmp,",%d,",(UnitId&0xFFFF));

					if (UnitHWND && CWnd::FromHandle(UnitHWND) && UnitType!=UT_SCROLLBAR)
					{
						::SetWindowLong(UnitHWND,GWL_STYLE,
							::GetWindowLong(UnitHWND,GWL_STYLE)&(0xFFFFFFFF^WS_VISIBLE)|(strstr(pos,"FALSE")==NULL?WS_VISIBLE:0));
						CWnd::FromHandle(UnitHWND)->Invalidate();
					}
					if (UnitHWND)
					{

						CRect re;
						CPoint po(0,0);

						switch(GPU[ParentNum]->UnitType)
						{
						case UT_BBUTTON:
						case UT_BUTTON:
						case UT_ANIBUTTON:
						case UT_STATIC:
						case UT_ANISTATIC:
							::ClientToScreen(::GetParent(::GetParent(UnitHWND)),&po);
							::GetWindowRect(UnitHWND,&re);
							re.top-=3;re.bottom+=3;re.right+=3;re.left-=3;
							re.OffsetRect(-po);
							CWnd::FromHandle(::GetParent(::GetParent(UnitHWND)))->Invalidate();
							break;
						default:
							::ClientToScreen(::GetParent(UnitHWND),&po);
							::GetWindowRect(UnitHWND,&re);
							re.top-=3;re.bottom+=3;re.right+=3;re.left-=3;
							re.OffsetRect(-po);
							CWnd::FromHandle(::GetParent(UnitHWND))->InvalidateRect(&re);
							break;
						}


						if (m_UpdateGroupFlag && UnitType!=UT_MAINDLGSCR && UnitHWND)
						{
							if (++m_UpdateGroupFlagCntr<10)
								for(nunit=1;(UINT)nunit<(*GPU)->m_NGPUNIT;nunit++)
									if (GPU[nunit] && GPU[nunit]->GroupNum && strstr(GPU[nunit]->GroupNum,strtmp))
									{
										char str[150];sprintf(str,"VISIBLE=%s",pos);
										GPU[nunit]->GPSetProperty(str);
									}
							m_UpdateGroupFlagCntr--;
						}
					}
				}
				break;
			case 4: /*PEN*/
				if (UnitHWND && CWnd::FromHandle(UnitHWND))
					InvalidateRect(UnitHWND,NULL,TRUE);
				break;

			case 2: /*FRG*/
			case 3: /*BKG*/
				{
					int r,g,b;r=g=b=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d",&r,&g,&b);
					if (propnum==2) m_clrText=(r==-1)?-1:RGB(r,g,b);
					else			m_clrBkgnd=(r==-1)?-1:RGB(r,g,b);
					if (UnitHWND) InvalidateRect(UnitHWND,NULL,TRUE);
				}
				break;

			case 5: /*BRUSH*/
				if (atoi(pos)==-1)
				{
					if (m_brBkgnd) delete m_brBkgnd;
					m_brBkgnd=NULL;
				}
				else
				{
					GPSetBrushProperty(&lb,pos);
					GPSetBrush(UnitHWND?UnitHWND: (::GetDesktopWindow()),&m_brBkgnd,&lb,m_clrBkgnd);
				}
				if (UnitHWND) InvalidateRect(UnitHWND,NULL,TRUE);
				break;

			case 34: /*BKGSRC*/
				m_bkgSrc=GetObjectIdByName(pos);
				break;

			case 6: /* TEXT*/
				switch(UnitType)
				{
				case UT_RTF:
				case UT_EDIT:
					break;
				case UT_MAINDLGSCR:
				case UT_DATETIMECTRL:
				case UT_MONTHCAL:
				case UT_DRAW:
				case UT_DLGBAR:
				case UT_FRAMEBAR:
				case UT_EDITOR:
				case UT_TREECTRL:
				case UT_HEADER:
				case UT_SLIDER:
				case UT_TABCTRL:
				case UT_SPINBUTTON:
				case UT_BUTTON:
				case UT_ANIBUTTON:
				case UT_BBUTTON:
				case UT_STATIC:
				case UT_ANISTATIC:
				case UT_LISTBOX:
				case UT_COMBOBOX:
				case UT_COMBOBOXEX:
				case UT_SCROLLBAR:
				case UT_PROGRESS:
				case UT_ANIMAT:
				case UT_CHECKLISTBOX:
				case UT_DRAGLISTBOX:
				case UT_LISTCTRL:
				case UT_STATUSBARCTRL:
				case UT_TOOLBARCTRL:
				case UT_STATUSBAR:
				case UT_TOOLBAR:
				case UT_DIALOGBAR:
				case UT_REBARCTRL:
				case UT_REBAR:
				case UT_WEBBROWSER:
					if (UnitHWND && CWnd::FromHandle(UnitHWND))
					{
						SetWindowText(UnitHWND,pos);
						InvalidateRect(UnitHWND,NULL,TRUE);
					}
					break;
				case UT_CONTROL:
					{
						CString tmps=pos;
						BSTR tmpBSTR=tmps.AllocSysString();
						::SendMessage(UnitHWND,GPM_AX_SETWINDOWTEXT,0,(LPARAM)(&tmpBSTR));
						::SysFreeString(tmpBSTR);
					}
					break;
				case UT_FLEXGRID:
					if (UnitHWND && UnitPtr)
						((GPCMSFlexGrid *)UnitPtr)->SetText(pos);
					break;
				}
				if (m_UpdateGroupFlag)
					DoMethod("UpdateGroup",NULL);
				break;
			case 7: // RECT
			case 25: // MRECT
			case 26: // DRECT
				if (UnitPtr || UnitType==UT_MAINDLGSCR)
				{
					CRect re(11,11,22,22);
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&re.left,&re.top,&re.right,&re.bottom);
					switch(propnum)
					{
					case 25: // MRECT
						{
							CPoint po;
							GetCursorPos(&po);
							if (GetParent(UnitHWND)!=GetDesktopWindow())
								ScreenToClient(GetParent(UnitHWND),&po);
							re+=po;
						}
						break;
					case 26: // DRECT
						{
							if (GetParent(UnitHWND)!=GetDesktopWindow())
							{
								CPoint po1=re.TopLeft();
								CPoint po2=re.BottomRight();
								ScreenToClient(GetParent(UnitHWND),&po1);
								ScreenToClient(GetParent(UnitHWND),&po2);
								re=CRect(po1,po2);
							}
						}
						break;
					}

					if (AUSI)
					{
						if (UnitType!=UT_MAINDLGSCR)	AUSI->SetNewSize(UnitHWND,re);
						else
						{
							AUSI->SetNewMainSize(re,1);
							AUSI->SetMinSize(UnitHWND,re.Width(),re.Height());
						}
					}

					if (UnitHWND && CWnd::FromHandle(UnitHWND))
					{
						MoveWindow(UnitHWND,re.left,re.top,re.Width(),re.Height(),TRUE);
						::RedrawWindow(UnitHWND,&re,NULL,RDW_ALLCHILDREN|RDW_ERASE|RDW_FRAME|RDW_INTERNALPAINT|RDW_INVALIDATE);
						//InvalidateRect(UnitHWND,re,TRUE);
					}
				}
				break;


			case 8: // ADDSTYLE
			case 9: // DELSTYLE
			case 10: // STYLE
				{
					strcat(pos,"|");
					UINT OldStyle=0;
					UINT OldExStyle=0;


					if (UnitHWND && CWnd::FromHandle(UnitHWND))
					{	// standart
						OldStyle=::GetWindowLong(UnitHWND,GWL_STYLE);
						OldExStyle=::GetWindowLong(UnitHWND,GWL_EXSTYLE);
						char strtmp[50],*postmp;
						sprintf(strtmp,",%d,",(UnitId&0xFFFF));
						UINT tmpstl=OldStyle&WS_CHILD;

						if ((postmp=strstr(pos,"&W")))
						{
							UINT tmp=0;
							m_LastScanf=sscanf(postmp,"&W%X",&tmp);
							switch(propnum)
							{
							case 10: /* STYLE*/
							case 8: /* ADDSTYLE*/
								::SetWindowLong(UnitHWND,GWL_STYLE,OldStyle|tmp);
								if (tmp&(WS_DISABLED|WS_GROUP|WS_TABSTOP|WS_VISIBLE))
								{
									if (m_UpdateGroupFlag)
									{
										if (++m_UpdateGroupFlagCntr<10)
											for(nunit=1;(UINT)nunit<(*GPU)->m_NGPUNIT;nunit++)
												if (GPU[nunit] && GPU[nunit]->GroupNum && strstr(GPU[nunit]->GroupNum,strtmp))
												{
													char str[150];sprintf(str,"%s=&W%X",propnum==10?"STYLE=":"ADDSTYLE=",tmp&(WS_DISABLED|WS_GROUP|WS_TABSTOP|WS_VISIBLE));
													GPU[nunit]->GPSetProperty(str);
												}
										m_UpdateGroupFlagCntr--;
									}
								}
								break;
							case 9: /* DELSTYLE*/
								::SetWindowLong(UnitHWND,GWL_STYLE,OldStyle&(0xFFFFFFFF^tmp));
								if ((tmp&WS_VISIBLE)== WS_VISIBLE && (tmp&WS_CHILD)==WS_CHILD)
								{
									RECT pRect={0};
									::GetWindowRect(::GetParent(UnitHWND),&pRect);
									::InvalidateRect(::GetParent(UnitHWND),&pRect,TRUE);
								}
								if (tmp&(WS_DISABLED|WS_GROUP|WS_TABSTOP|WS_VISIBLE))
								{
									if (m_UpdateGroupFlag)
									{
										if (++m_UpdateGroupFlagCntr<10)
											for(nunit=1;(UINT)nunit<(*GPU)->m_NGPUNIT;nunit++)
												if (GPU[nunit] && GPU[nunit]->GroupNum && strstr(GPU[nunit]->GroupNum,strtmp))
												{
													char str[150];sprintf(str,"DELSTYLE=&W%X",tmp&(WS_DISABLED|WS_GROUP|WS_TABSTOP|WS_VISIBLE));
													GPU[nunit]->GPSetProperty(str);
												}
										m_UpdateGroupFlagCntr--;
									}
								}
								break;
							}
						}

						for(i=0;i<N_WND_STYLES;i++)
							if (strstr(pos,aWndStyleName[i]) && (tmpstl==0 || (aWndStyleUINT[i]!=WS_POPUPWINDOW && aWndStyleUINT[i]!=WS_POPUP)))
							{
								switch(propnum)
								{
								case 10: /* STYLE*/
								case 8: /* ADDSTYLE*/
									::SetWindowLong(UnitHWND,GWL_STYLE,OldStyle|aWndStyleUINT[i]);
									if (
										aWndStyleUINT[i]== WS_DISABLED ||
										aWndStyleUINT[i]== WS_GROUP ||
										aWndStyleUINT[i]== WS_TABSTOP ||
										aWndStyleUINT[i]== WS_VISIBLE
										)
									{
										if (m_UpdateGroupFlag)
										{
											if (++m_UpdateGroupFlagCntr<10)
												for(nunit=1;(UINT)nunit<(*GPU)->m_NGPUNIT;nunit++)
													if (GPU[nunit] && GPU[nunit]->GroupNum && strstr(GPU[nunit]->GroupNum,strtmp))
													{
														char str[150];sprintf(str,"%s=%s",propnum==10?"STYLE=":"ADDSTYLE=",aWndStyleName[i]);
														GPU[nunit]->GPSetProperty(str);
													}
											m_UpdateGroupFlagCntr--;
										}
									}
									break;
								case 9: /* DELSTYLE*/
									::SetWindowLong(UnitHWND,GWL_STYLE,OldStyle&(0xFFFFFFFF^aWndStyleUINT[i]));
									if (
										aWndStyleUINT[i]== WS_DISABLED ||
										aWndStyleUINT[i]== WS_GROUP ||
										aWndStyleUINT[i]== WS_TABSTOP ||
										aWndStyleUINT[i]== WS_VISIBLE
										)
									{
										if (m_UpdateGroupFlag)
										{
											if (++m_UpdateGroupFlagCntr<10)
												for(nunit=1;(UINT)nunit<(*GPU)->m_NGPUNIT;nunit++)
													if (GPU[nunit] && GPU[nunit]->GroupNum && strstr(GPU[nunit]->GroupNum,strtmp))
													{
														char str[150];sprintf(str,"DELSTYLE=%s",aWndStyleName[i]);
														GPU[nunit]->GPSetProperty(str);
													}
											m_UpdateGroupFlagCntr--;
										}
									}
									break;
								}
							}

						if ((postmp=strstr(pos,"&E")))
						{
							UINT tmp=0;
							m_LastScanf=sscanf(postmp,"&E%X",&tmp);
							switch(propnum)
							{
							case 10: /* STYLE*/
							case 8: /* ADDSTYLE*/
								::SetWindowLong(UnitHWND,GWL_EXSTYLE,::GetWindowLong(UnitHWND,GWL_EXSTYLE)|tmp);
								break;
							case 9: /* DELSTYLE*/
								::SetWindowLong(UnitHWND,GWL_EXSTYLE,::GetWindowLong(UnitHWND,GWL_EXSTYLE)&(0xFFFFFFFF^tmp));
								break;
							}
						}

						for(i=0;i<N_WND_EX_STYLES;i++)
							if (strstr(pos,aWndExStyleName[i]))
							{
								switch(propnum)
								{
								case 10: /* STYLE*/
								case 8: /* ADDSTYLE*/
									::SetWindowLong(UnitHWND,GWL_EXSTYLE,::GetWindowLong(UnitHWND,GWL_EXSTYLE)|aWndExStyleUINT[i]);
									break;
								case 9: /* DELSTYLE*/
									::SetWindowLong(UnitHWND,GWL_EXSTYLE,::GetWindowLong(UnitHWND,GWL_EXSTYLE)&(0xFFFFFFFF^aWndExStyleUINT[i]));
									break;
								}
							}

						if ((postmp=strstr(pos,"&C")))
						{
							UINT tmp=0;
							m_LastScanf=sscanf(postmp,"&C%X",&tmp);
							switch(propnum)
							{
							case 10: /* STYLE*/
							case 8: /* ADDSTYLE*/
								UnitCommonStyles|=tmp;
								break;
							case 9: /* DELSTYLE*/
								UnitCommonStyles&=(0xFFFFFFFF^tmp);
								break;
							}
						}

						for(i=0;i<N_UNITCOMMON_STYLES;i++)
							if (strstr(pos,aUnitCommonStyleName[i]))
							{
								switch(propnum)
								{
								case 10: /* STYLE*/
								case 8: /* ADDSTYLE*/
									UnitCommonStyles|=aUnitCommonStyleUINT[i];
									break;
								case 9: /* DELSTYLE*/
									UnitCommonStyles&=(0xFFFFFFFF^aUnitCommonStyleUINT[i]);
									break;
								}
							}

						// cwnd specif
						if (UnitHWND)
						{
							RECT pRect={0};
							::GetWindowRect(UnitHWND,&pRect);
							HWND hwp=::GetParent(UnitHWND);
							if (hwp)
							{
								::ScreenToClient(hwp,((POINT *)&pRect));
								::ScreenToClient(hwp,((POINT *)&pRect)+1);
								::InvalidateRect(hwp,&pRect,TRUE);
							}
						}
					}

					switch(UnitType)
					{
					case UT_MAINDLGSCR:
					case UT_FRAMEBAR:
					case UT_DLGBAR:
						{	// Dialog
							for(i=0;i<N_DLG_STYLES;i++)
								if (strstr(pos,aDlgStyleName[i]))
								{
									switch(propnum)
									{
									case 10: /* STYLE*/
									case 8: /* ADDSTYLE*/
										::SetWindowLong(UnitHWND,GWL_STYLE,::GetWindowLong(UnitHWND,GWL_STYLE)|aDlgStyleUINT[i]);
										break;
									case 9: /* DELSTYLE*/
										::SetWindowLong(UnitHWND,GWL_STYLE,::GetWindowLong(UnitHWND,GWL_STYLE)&(0xFFFFFFFF^aDlgStyleUINT[i]));
										break;
									}
								}
							break;
						}
					}

					if (UnitHWND && GPU && ParentNum>=0 && ParentNum<(*GPU)->m_NGPUNIT && GPU[ParentNum])
					{

						CRect re;
						POINT po={0};

						switch(GPU[ParentNum]->UnitType)
						{
						case UT_BBUTTON:
						case UT_ANIBUTTON:
						case UT_BUTTON:
						case UT_STATIC:
						case UT_ANISTATIC:
							::ClientToScreen(GetParent(GetParent(UnitHWND)),&po);
							::GetWindowRect(UnitHWND,re);
							re.OffsetRect(-po.x,-po.y);
							re.top-=3;re.bottom+=3;re.right+=3;re.left-=3;
							if ((::GetWindowLong(::GetParent(UnitHWND),GWL_STYLE)&WS_CHILD)==WS_CHILD)
								::InvalidateRect(::GetParent(::GetParent(UnitHWND)),re,TRUE);
							break;
//						case UT_FLEXGRID:
//							break;
//						case UT_WEBBROWSER:
//							break;
						default:

							::ClientToScreen(::GetParent(UnitHWND),&po);
							::GetWindowRect(UnitHWND,re);
							re.OffsetRect(-po.x,-po.y);
							re.top-=3;re.bottom+=3;re.right+=3;re.left-=3;
//									tmpCWnd->GetParent()->ClientToScreen(&re);

							if ((::GetWindowLong(UnitHWND,GWL_STYLE)&WS_CHILD)==WS_CHILD)
								::InvalidateRect(::GetParent(UnitHWND),re,TRUE);
							break;
						}

					}
					else
					if (UnitHWND && CWnd::FromHandle(UnitHWND))
					{
						CRect re;
						POINT po={0};
						::ClientToScreen(::GetParent(UnitHWND),&po);

						::GetWindowRect(UnitHWND,re);
						re.OffsetRect(-po.x,-po.y);
						re.top-=3;re.bottom+=3;re.right+=3;re.left-=3;
//								tmpCWnd->GetParent()->ClientToScreen(&re);
						if ((::GetWindowLong(UnitHWND,GWL_STYLE)&WS_CHILD)==WS_CHILD)
							::InvalidateRect(::GetParent(UnitHWND),re,TRUE);
					}


					if (UnitHWND && CWnd::FromHandle(UnitHWND))
					{
						UINT NewStyle=0;
						UINT NewExStyle=0;
						NewStyle=::GetWindowLong(UnitHWND,GWL_STYLE);
						NewExStyle=::GetWindowLong(UnitHWND,GWL_EXSTYLE);
						if (((NewStyle^OldStyle)&(WS_CAPTION|WS_OVERLAPPEDWINDOW|WS_THICKFRAME|WS_DLGFRAME|WS_HSCROLL|WS_VSCROLL|WS_SYSMENU))!=0
							|| ((NewExStyle^OldExStyle)&(WS_EX_CLIENTEDGE|WS_EX_DLGMODALFRAME|WS_EX_LEFT|WS_EX_LEFTSCROLLBAR|WS_EX_LTRREADING|WS_EX_MDICHILD|WS_EX_OVERLAPPEDWINDOW|WS_EX_PALETTEWINDOW|WS_EX_RIGHT|WS_EX_RIGHTSCROLLBAR|WS_EX_RTLREADING|WS_EX_STATICEDGE|WS_EX_TOOLWINDOW|WS_EX_TOPMOST|WS_EX_TRANSPARENT|WS_EX_WINDOWEDGE))!=0)
						{
							InvalidateGPUnit();
							if ((NewStyle&WS_CHILD)==WS_CHILD || UnitType==UT_FLEXGRID || UnitType==UT_WEBBROWSER)
							{

								CRect re2;
								RECT retmp={0};
								::GetClientRect(::GetParent(UnitHWND),&retmp);
								::ClientToScreen(::GetParent(UnitHWND),(POINT *)&retmp);
								::ClientToScreen(::GetParent(UnitHWND),((POINT *)&retmp)+1);

								::GetWindowRect(UnitHWND,re2);
								re2.OffsetRect(-((POINT*)&retmp)->x,-((POINT*)&retmp)->y);
								re2.right++;
								::MoveWindow(UnitHWND,re2.left,re2.top,re2.Width(),re2.Height(),TRUE);
								re2.right--;
								::MoveWindow(UnitHWND,re2.left,re2.top,re2.Width(),re2.Height(),TRUE);
								if (NoUpdateParent==FALSE)
									if ((::GetWindowLong(UnitHWND,GWL_STYLE)&WS_CHILD)==WS_CHILD)
									{
										RECT pRect={0};
										::GetWindowRect(::GetParent(UnitHWND),&pRect);
										::InvalidateRect(::GetParent(UnitHWND),&pRect,TRUE);
									}
							}
							else
							if (UnitHWND)
							{
								CRect re2;
								::GetWindowRect(UnitHWND,&re2);
								re2.right++;
								::MoveWindow(UnitHWND,re2.left,re2.top,re2.Width(),re2.Height(),TRUE);
								re2.right--;
								::MoveWindow(UnitHWND,re2.left,re2.top,re2.Width(),re2.Height(),TRUE);
								if ((::GetWindowLong(UnitHWND,GWL_STYLE)&WS_CHILD)==WS_CHILD)
								{
									RECT pRect={0};
									::GetWindowRect(::GetParent(UnitHWND),&pRect);
									::InvalidateRect(::GetParent(UnitHWND),&pRect,TRUE);
								}
							}
						}
					}

				}
				break;

			case 11: /*FONT*/
			case 12: /*FONT2*/
				if (UnitHWND && CWnd::FromHandle(UnitHWND))
				{
					CFont *CFtoDelete=NULL;
					if (strstr(pos,"CURRENT"))
					{
						CWnd::FromHandle(UnitHWND)->SetFont(CWnd::FromHandle(GPU[0]->UnitHWND)->GetFont());
						if ((UnitId&0xFFFF))
						{
							CFtoDelete=UnitFont;
							UnitFont=NULL;
						}
					}
					else
					{
						CFont *fn=new CFont;
						LOGFONT lf={0};
						if (UnitFont) UnitFont->GetLogFont(&lf);
						else
							GetObject((HFONT)(*(CWnd::FromHandle(UnitHWND)->GetFont())),sizeof(lf),&lf);
						TranslLOGFONT(lf,pos);
						fn->CreateFontIndirect(&lf);
						CWnd::FromHandle(UnitHWND)->SetFont(fn);
						CFtoDelete=UnitFont;
						UnitFont=fn;
					}
					if ((UnitId&0xFFFF)==0 && CFtoDelete)
					{
						UINT uNumTmp;
						for(uNumTmp=1;uNumTmp<(*GPU)->m_NGPUNIT;uNumTmp++)
							if (GPU[uNumTmp] && GPU[uNumTmp]->UnitHWND)
							{
								CFont *CFtoCompare=((CWnd*)GPU[uNumTmp]->UnitPtr)->GetFont();
								if (CFtoCompare && (HFONT)(*CFtoDelete)==(HFONT)(*CFtoCompare))
									((CWnd*)GPU[uNumTmp]->UnitPtr)->SetFont(UnitFont);
							}
					}
					if (CFtoDelete) delete CFtoDelete;
				}
				break;
			case 13: /* TALIGN */ break;
			case 14: /* TOOLTIP */

				if (UnitHWND && CWnd::FromHandle(UnitHWND))
				if (*m_ToolTip)
				{
					(*m_ToolTip)->DelTool(CWnd::FromHandle(UnitHWND));
					if (ToolTipText) delete[] ToolTipText;
					ToolTipText=NULL;
					if (*pos!=0)
					{
						(*m_ToolTip)->AddTool(CWnd::FromHandle(UnitHWND),pos);
						ToolTipText=new char [(int)strlen(pos)+10];
						strcpy(ToolTipText,pos);
						char *pos2=strchr(ToolTipText,';');
						if (pos2) *pos2=0;
					}
				}
				break;
			case 15: /* PARENT */
				if (UnitHWND && CWnd::FromHandle(UnitHWND))
				{
					UINT tmpp=atoi(pos);
					if (tmpp==0 && *pos!='0')
					{
						char *pname=new char [(int)strlen(pos)+10];
						strcpy(pname,pos);
						char *pos2=strchr(pname,';');
						if (pos2) *pos2=0;
						pos2=strchr(pname,' ');
						if (pos2) *pos2=0;
						tmpp=GetObjectIdByName(pname);
						if (tmpp<(*GPU)->m_NGPUNIT && GPU[tmpp] && GPU[tmpp]->UnitHWND)
							SetParent(UnitHWND,GPU[tmpp]->UnitHWND);
						delete[] pname;
					}
					else
					if (tmpp>=(*GPU)->m_NGPUNIT)
					{
						ParentNum=-1;
						SetParent(UnitHWND,GetDesktopWindow());
					}
					else
					{
						if (GPU[tmpp]==NULL || GPU[tmpp]->UnitHWND==NULL) tmpp=0;
						ParentNum=tmpp;
						SetParent(UnitHWND,GPU[tmpp]->UnitHWND);
					}
				}
				break;
			case 16: /* GROUP */
				{
					if (GroupNum) delete[] GroupNum;
					GroupNum=NULL;
					if (*pos!=0)
					{
						GroupNum=new char [(int)strlen(pos)*2+40];
						char *pos2=pos;
						char *posdest=GroupNum;
						char *tmps=new char [(int)strlen(pos)*2+40];
						*(posdest++)=',';

						while(*pos2)
						{

							while(*pos2==',') pos2++;
							char *postmp=pos2;
							char *postmps=tmps;
							*postmps=0;
							while(*postmp && *postmp!=',' && *postmp!='.' && *postmp!=';')  *(postmps++)=*(postmp++);
							*postmps=0;
							int objtmp=GetObjectIdByName(tmps);
							if (*tmps && tmps[1]!=0 && objtmp<0 && (*tmps<'0' || *tmps>'9'))
							{
								objtmp=GetObjectIdByName(tmps+1);
								if (objtmp>=0) *(posdest++)=*tmps;
							}

							if (objtmp>=0)
							{
								posdest+=sprintf(posdest,"%d",objtmp);
								while(*postmp && *postmp!=',' && *postmp!=';')  *(posdest++)=*(postmp++);
							}
							else while(*postmp && *postmp!=',' && *postmp!=';')  postmp++;
							*(posdest++)=*postmp;
							if (*postmp) postmp++;
							pos2=postmp;
						}
						*(posdest++)=0;
						if ((int)strlen(GroupNum)<2) *GroupNum=0;
						else
							if (*GroupNum && GroupNum[(int)strlen(GroupNum)-1]!=',') strcat(GroupNum,",");
						delete[] tmps;
						if (*GroupNum==0)
						{
							delete[] GroupNum;
							GroupNum=NULL;
						}
					}
					CheckGroups();
				}
				break;
			case 17: // DELSIZING
				if (UnitHWND && CWnd::FromHandle(UnitHWND) && UnitType!=UT_MAINDLGSCR && AUSI)
				{
					int SizeProvider=atoi(pos);
					if (SizeProvider==0 && *pos=='0')
					{
						CString SizeProviderName=ExtractField(pos,1,",");
						for(SizeProvider=0;(UINT)SizeProvider<(*GPU)->m_NGPUNIT && (GPU[SizeProvider]==NULL || GPU[SizeProvider]->m_ObjName!=SizeProviderName);SizeProvider++);
					}
					if (UnitHWND && SizeProvider>=0 && (UINT)SizeProvider<(*GPU)->m_NGPUNIT
						&& GPU[SizeProvider] && GPU[SizeProvider]->UnitHWND)
					{
						if (GPU[SizeProvider]->UnitType!=UT_DLGBAR && GPU[SizeProvider]->UnitType!=UT_FRAMEBAR)
							AUSI->DeleteWndEx(UnitHWND,GPU[SizeProvider]->UnitHWND);
						else
						{
							if (GPU[SizeProvider]->UnitType==UT_DLGBAR)
								((GPDlgBar *)GPU[SizeProvider]->UnitPtr)->DlgAutoSize->DeleteWndEx(UnitHWND,GPU[SizeProvider]->UnitHWND);
							else
								((GPFrameBar *)GPU[SizeProvider]->UnitPtr)->DlgAutoSize->DeleteWndEx(UnitHWND,GPU[SizeProvider]->UnitHWND);
						}
					}
				}
				break;
			case 18: // SIZING
				if (UnitHWND && UnitType!=UT_MAINDLGSCR && AUSI)
				{
					char *postmpcc=new char [(int)strlen(pos)+10];
					strcpy(postmpcc,pos);
					char *pos2=strchr(postmpcc,',');
					int SizeProvider=atoi(postmpcc);
					if (SizeProvider==0 && *postmpcc!='0')
						SizeProvider=GetObjectIdByName(ExtractField(postmpcc,1,","));

					if (pos2++ && SizeProvider>=0 && (UINT)SizeProvider<(*GPU)->m_NGPUNIT
						&& GPU[SizeProvider] && GPU[SizeProvider]->UnitHWND)
					{
						int m_iSizingHolder=0;
						for(m_iSizingHolder=0;(UINT)m_iSizingHolder<(*GPU)->m_NGPUNIT;m_iSizingHolder++)
						{
							if (GPU[m_iSizingHolder] && GPU[m_iSizingHolder]->UnitHWND)
							{
								if (GPU[m_iSizingHolder]->UnitType==UT_MAINDLGSCR)
									{if (AUSI->GetResizingOwner(GPU[SizeProvider]->UnitHWND)) break;}
								else
								if (GPU[m_iSizingHolder]->UnitType==UT_DLGBAR)
									{if (((GPDlgBar *)(GPU[m_iSizingHolder]->UnitPtr))->DlgAutoSize->GetResizingOwner(GPU[SizeProvider]->UnitHWND)) break;}
								else
								if (GPU[m_iSizingHolder]->UnitType==UT_FRAMEBAR)
									{if (((GPFrameBar *)(GPU[m_iSizingHolder]->UnitPtr))->DlgAutoSize->GetResizingOwner(GPU[SizeProvider]->UnitHWND)) break;}
							}
						}
						if ((UINT)m_iSizingHolder<(*GPU)->m_NGPUNIT)
						{
							char tmp[15];
							strcpy(tmp,"        ");
							if (*pos2=='-') tmp[2]=*(pos2++);
							tmp[3]=*(pos2++);
							if (*pos2=='-') tmp[0]=*(pos2++);
							tmp[1]=*(pos2++);
							if (*pos2=='-') tmp[6]=*(pos2++);
							tmp[7]=*(pos2++);
							if (*pos2=='-') tmp[4]=*(pos2++);
							tmp[5]=*(pos2++);

							char *tmppos=pos2=tmp;
							do
							{
								if ((*pos2=*tmppos)!=' ' && *pos2!=0) pos2++;
								tmppos++;
							}
							while(*pos2!=0);

							switch(GPU[m_iSizingHolder]->UnitType)
							{
							case UT_MAINDLGSCR:
								AUSI->AddWnd(UnitHWND,GPU[SizeProvider]->UnitHWND,tmp);
								break;
							case UT_DLGBAR:
								((GPDlgBar *)GPU[m_iSizingHolder]->UnitPtr)->DlgAutoSize->AddWnd(UnitHWND,GPU[SizeProvider]->UnitHWND,tmp);
								break;
							case UT_FRAMEBAR:
								((GPFrameBar *)GPU[m_iSizingHolder]->UnitPtr)->DlgAutoSize->AddWnd(UnitHWND,GPU[SizeProvider]->UnitHWND,tmp);
								break;
							}


							if (UnitType==UT_COMBOBOX)
							{
								CRect ReTmp(0,0,20,250);
								((GPComboBox *)UnitPtr)->GetDroppedControlRect(&ReTmp);
								AUSI->SetMinSize(UnitHWND,10,ReTmp.Height());
							}
							else
							if (UnitType==UT_COMBOBOXEX)
							{
								CRect ReTmp(0,0,20,250);
								((GPComboBoxEx *)UnitPtr)->GetDroppedControlRect(&ReTmp);
								AUSI->SetMinSize(UnitHWND,10,ReTmp.Height());
							}
						}
					}
					delete[] postmpcc;
				}
				break;
			case 19: // MINSIZE
			case 20: // MAXSIZE
				if (UnitHWND && CWnd::FromHandle(UnitHWND) && AUSI)
				{
					int mcx=100,mcy=100;
					m_LastScanf=sscanf(pos,"%d,%d",&mcx,&mcy);
					if (UnitHWND && AUSI)
					{
						HWND SizeProviderHWND=AUSI->GetResizingOwner(UnitHWND);
						if (SizeProviderHWND || UnitType==UT_MAINDLGSCR)
						{
							if (propnum==19) AUSI->SetMinSize(UnitHWND,mcx,mcy);
							else			 AUSI->SetMaxSize(UnitHWND,mcx,mcy);
						}
						else
						{
							int SizeProvider;
							for(SizeProvider=0; (UINT)SizeProvider<(*GPU)->m_NGPUNIT;SizeProvider++)
								if (GPU[SizeProvider] && GPU[SizeProvider]->UnitHWND==SizeProviderHWND) break;
							if ((UINT)SizeProvider<(*GPU)->m_NGPUNIT)
							{
								if (GPU[SizeProvider]->UnitType==UT_DLGBAR)
								{
									if (propnum==19) ((GPDlgBar *)GPU[SizeProvider]->UnitPtr)->DlgAutoSize->SetMinSize(UnitHWND,mcx,mcy);
									else			 ((GPDlgBar *)GPU[SizeProvider]->UnitPtr)->DlgAutoSize->SetMaxSize(UnitHWND,mcx,mcy);
								}
								else
								{
									if (propnum==19) ((GPFrameBar *)GPU[SizeProvider]->UnitPtr)->DlgAutoSize->SetMinSize(UnitHWND,mcx,mcy);
									else			 ((GPFrameBar *)GPU[SizeProvider]->UnitPtr)->DlgAutoSize->SetMaxSize(UnitHWND,mcx,mcy);
								}
							}
						}
					}
				}
				break;

			case 21: // MINPOS
			case 22: // MAXPOS
				if (UnitHWND && CWnd::FromHandle(UnitHWND) && AUSI)
				{
					int mtop=0,mbottom=0,mleft=0,mright=0;
					if (propnum==22) mtop=mbottom=mleft=mright=5000;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&mleft,&mtop,&mright,&mbottom);
					if (UnitHWND && AUSI)
					{
						HWND SizeProviderHWND=AUSI->GetResizingOwner(UnitHWND);
						if (SizeProviderHWND || UnitType==UT_MAINDLGSCR)
						{
							if (propnum==21) AUSI->SetMinPos(UnitHWND,mtop,mleft,mbottom,mright);
							else			 AUSI->SetMaxPos(UnitHWND,mtop,mleft,mbottom,mright);
						}
						else
						{
							int SizeProvider;
							for(SizeProvider=0; (UINT)SizeProvider<(*GPU)->m_NGPUNIT;SizeProvider++)
								if (GPU[SizeProvider] && GPU[SizeProvider]->UnitHWND==SizeProviderHWND) break;
							if ((UINT)SizeProvider<(*GPU)->m_NGPUNIT)
							{
								if (GPU[SizeProvider]->UnitType==UT_DLGBAR)
								{
									if (propnum==21) ((GPDlgBar *)GPU[SizeProvider]->UnitPtr)->DlgAutoSize->SetMinPos(UnitHWND,mtop,mleft,mbottom,mright);
									else			 ((GPDlgBar *)GPU[SizeProvider]->UnitPtr)->DlgAutoSize->SetMaxPos(UnitHWND,mtop,mleft,mbottom,mright);
								}
								else
								{
									if (propnum==21) ((GPFrameBar *)GPU[SizeProvider]->UnitPtr)->DlgAutoSize->SetMinPos(UnitHWND,mtop,mleft,mbottom,mright);
									else			 ((GPFrameBar *)GPU[SizeProvider]->UnitPtr)->DlgAutoSize->SetMaxPos(UnitHWND,mtop,mleft,mbottom,mright);
								}
							}
						}
					}
				}
				break;
			case 23: // FRALIGN
				if (UnitHWND && CWnd::FromHandle(UnitHWND))
				{
					SizStyle^=(SizStyle&0xFFFF0000);

					UINT j;
					for(j=0;j<5;j++)
						if (_stricmp(pos,cArrAlignSize[j])==0)
						{
							SizStyle|=uArrAlignSize[j]*0x10000;
							break;
						}

					if (GPU && j==4)
					{
						CWnd::FromHandle(UnitHWND)->GetParent()->SendMessage(GPN_SETENTIRE,UnitId&0xFFFF+50000);
						UINT i22;
						for(i22=0;i22<(*GPU)->m_NGPUNIT;i22++)
							if (GPU[i22] && i22!=(UnitId&0xFFFF) && (GPU[i22]->SizStyle/0x10000)==GPUA_ENTIRE)
								GPU[i22]->SizStyle=GPUA_TOP*0x10000;
					}
					PostMessage(GetParent(UnitHWND),WM_SIZE,0,0);
//					CWnd::FromHandle(UnitHWND)->GetParent()->PostMessage(WM_SIZE);
				}
				break;
			case 24: // FRSIZING
				if (UnitHWND && CWnd::FromHandle(UnitHWND))
				{
					SizStyle^=(SizStyle&0xFFFF);
					_strupr(pos);
					UINT i22;
					for(i22=0;i22<4;i22++)
						if (strstr(pos,cArrAlignSize[i22]))	SizStyle|=uArrAlignSize[i22];

					PostMessage(GetParent(UnitHWND),WM_SIZE,0,0);
//					CWnd::FromHandle(UnitHWND)->GetParent()->PostMessage(WM_SIZE);
				}
				break;
			case 27: // REGION
				if (UnitHWND && CWnd::FromHandle(UnitHWND))
				{
					int rrr;
					GPRegion *tmpreg=GPC.RegionArr.GetRgn(pos);
					if (tmpreg && tmpreg->GetHRGN())
					{
						HRGN rgtmp=CreateRectRgn(0,0,55,55);
						CombineRgn(rgtmp,tmpreg->GetHRGN(),NULL,RGN_COPY);
						rrr=SetWindowRgn(UnitHWND,rgtmp,TRUE);
					}
					else
					{
						CRect re;
						GetWindowRect(UnitHWND,&re);
						re.OffsetRect(-re.TopLeft());
						HRGN rg=CreateRectRgnIndirect(re);
						SetWindowRgn(UnitHWND,rg,TRUE);
					}
				}
				break;
			case 28: // NCHITANS
				m_NCHITTESTflag=atoi(pos);
				break;
			case 29: // NAME
				m_ObjName=pos;
				break;
			case 30: // ADDTTSTYLE
			case 31: // DELTTSTYLE
			case 32: // TTSTYLE
				if (m_ToolTip && *m_ToolTip && *pos && (*m_ToolTip)->m_hWnd)
				{
					DWORD curStyle=0, curExStyle=0;
					curStyle=(*m_ToolTip)->GetStyle();
					curExStyle=(*m_ToolTip)->GetExStyle();

					DWORD newStyleTT=0,	newStyle=0, newExStyle=0;

					CGPToolTipCtrl::StringFromToToolTipStyles(pos,newStyleTT);
					StringFromToWindowStyles(pos,newStyle);
					StringFromToWindowStylesEx(pos,newExStyle);

					switch(propnum)
					{
					case 30:// ADDTTSTYLE
						if (newStyle|newStyleTT)
							(*m_ToolTip)->ModifyStyle(0,newStyle|newStyleTT);
						if (newExStyle)
							(*m_ToolTip)->ModifyStyleEx(0,newExStyle);
						break;
					case 31:// DELTTSTYLE
						if (newStyle|newStyleTT)
							(*m_ToolTip)->ModifyStyle(newStyle|newStyleTT,0);
						if (newExStyle)
							(*m_ToolTip)->ModifyStyleEx(newExStyle,0);
						break;
					case 32:// TTSTYLE
						(*m_ToolTip)->ModifyStyle((curStyle|WS_CHILD)&(0xFFFFFFFF^(newStyle|newStyleTT|WS_POPUP)),newStyle|newStyleTT|WS_POPUP);
						(*m_ToolTip)->ModifyStyleEx(curExStyle&(0xFFFFFFFF^newExStyle),newExStyle);
						break;
					}
				}
				break;
			case 33: // BKGMODE
				{
					m_BkgMode=atoi(pos);
					if (strchr(pos,'t') || strchr(pos,'T')) m_BkgMode=TRANSPARENT;
					if (strchr(pos,'o') || strchr(pos,'O')) m_BkgMode=OPAQUE;
				}
				break;
			case 35: // SCALE
				{
					UINT tmpScale=atoi(pos);
					if (tmpScale<30 || tmpScale>500) tmpScale=GPC.m_GUISet.Scale;
					m_Scale=tmpScale;
				}
				break;

			default: /* end */break;
			}
			}
			catch(...)
			{
				GPC.m_ErrReport.GPWriteErrorLog("GPUnit", "GPSetProperty",iStr);
			}
		}
		*(--pos)='=';
	}
	delete[] iValue;
	return ret;
}

void GPUnit::GPAddMessage(char *mes)
{
	if ((UnitPtr || UnitType==UT_MAINDLGSCR) && GPMSG)
	{
		char str[50];
		strncpy(str,mes,45);
		str[45]=0;
		_strupr(str);
		if (strncmp(str,"ONVALCHANGE",11)==0)
		{
			if ((UnitId&0xFFFF)==0)
			{
				UINT i;
				for(i=1;i<(*GPU)->m_NGPUNIT;i++)
					if (GPU[i]) GPU[i]->GPAddMessage(mes);

			}
			GPMSG->AddMessage(mes);
			m_dwValChangeFlag|=1;
		}
		else
		if (strncmp(str,"ONTIMER",7)==0)
		{
			UINT nId=0,nDelay=1000;
			int nCount=0;
			m_LastScanf=sscanf(mes+8,"%d,%d,%d",&nId,&nDelay,&nCount);
			if (nId<20)
			{
				if (!iArrTimerCount) 
				{
					iArrTimerCount= new UINT [50];
					int j;
					for(j=1;j<50;j++) iArrTimerCount[j]=0;
				}
				char *tmpmes=new char [(int)strlen(mes)+10];
				char *posout=strchr(mes,'=');
				if (posout) posout++;
				else posout="";
				sprintf(tmpmes,"ONTIMER=%s",posout);
				GPMSG->AddMessage(tmpmes);
				delete[] tmpmes;
				if (nDelay<100) nDelay=100;
				KillTimer(UnitHWND,nId+20000);
				
				GPU[UnitId&0xFFFF]->iArrTimerCount[nId]=nCount<0?0:nCount;
				GPU[UnitId&0xFFFF]->iArrTimerCount[nId+20]=nCount<0?-nCount:nCount;
				SetTimer(UnitHWND,nId+20000,nDelay,NULL);
			}
		}
		else GPMSG->AddMessage(mes);

		if (strncmp(str,"ONHELPER",8)==0)
		{
			switch(UnitType)
			{
			case UT_TREECTRL:
				((GPTree*)UnitPtr)->m_HelperMode=1;	
				break;
			default:
				break;
			}// end TypeUnit Switch

		}
	}

}

void GPUnit::GPDeleteMessage(char *mes)
{
	if ((UnitPtr || UnitType==UT_MAINDLGSCR) && GPMSG)
	{
		char str[50];
		strncpy(str,mes,45);
		str[45]=0;
		_strupr(str);
		if (strncmp(str,"ONVALCHANGE",11)==0)
		{
			if ((UnitId&0xFFFF)==0)
			{
				UINT i;
				for(i=1;i<(*GPU)->m_NGPUNIT;i++)
					if (GPU[i]) GPU[i]->GPDeleteMessage(mes);

			}
			if (this==m_ptrUnitValChange) 
			{
				m_ptrUnitValChange=NULL;
//				TRACE("m_ptrUnitValChange=NULL GPDeleteMessage %s\n",UnitInfoToString("\x01") );
			}
			GPMSG->DelMessage(mes);
			m_dwValChangeFlag&=0xFFFFFFFE;
		}
		else
		if (strncmp(str,"ONTIMER",7)==0)
		{
			UINT nId=atoi(mes+8);
			if (nId<20)
			{
				GPMSG->DelMessage("ONTIMER");
				KillTimer(UnitHWND,nId+20000);
			}
		}
		else GPMSG->DelMessage(mes);

		if (strncmp(str,"ONHELPER",8)==0)
		{
			switch(UnitType)
			{
			case UT_TREECTRL:
				((GPTree*)UnitPtr)->m_HelperMode=0;	
				break;
			default:
				break;
			}// end TypeUnit Switch

		}
	}
}

void GPUnit::GPDeleteAllMessage()
{
	if ((UnitPtr || UnitType==UT_MAINDLGSCR) && GPMSG)
	{
		if ((UnitId&0xFFFF)==0)
		{
			UINT i;
			for(i=1;i<(*GPU)->m_NGPUNIT;i++)
			{
				if (GPU[i]) GPU[i]->GPDeleteMessage("ONVALCHANGE");
				if (GPU[i]) GPU[i]->GPDeleteMessage("ONVALCHANGEEX");
			}
			m_ptrUnitValChange=NULL;
//			TRACE("m_ptrUnitValChange=NULL GPDeleteAllMessage %s\n",UnitInfoToString("\x01") );
		}
		m_dwValChangeFlag&=0xFFFFFFFE;
		if (this==m_ptrUnitValChange)
		{
//			TRACE("m_ptrUnitValChange=NULL GPDeleteAllMessage %s\n",UnitInfoToString("\x01") );
			m_ptrUnitValChange=NULL;
		}
		GPMSG->DelAllMessages();
		switch(UnitType)
		{
		case UT_TREECTRL:
			((GPTree*)UnitPtr)->m_HelperMode=1;	
			break;
		default:
			break;
		}// end TypeUnit Switch
	}
}

void GPUnit::GPGetWndRect(CRect *re)
{
	*re=CRect(0,0,0,0);
	if ((UnitPtr || UnitType==UT_MAINDLGSCR) && UnitHWND)
		GetWindowRect(UnitHWND,re);	
}

void GPUnit::GPGetClientRect(CRect *re)
{
	*re=CRect(0,0,0,0);
	if ((UnitPtr || UnitType==UT_MAINDLGSCR) && UnitHWND)
		CWnd::FromHandle(UnitHWND)->GetClientRect(re);
}

UINT GPUnit::GetResizeingOwner()
{
	HWND tmp=AUSI->GetResizingOwner(UnitHWND);
	int ret=-1;

	if (tmp)
	{
		for(ret=0;(UINT)ret<(*GPU)->m_NGPUNIT && (GPU[ret]==NULL || GPU[ret]->UnitHWND!=tmp);ret++);
	}
	else
	{
		int i=0;
		for(i=0;(UINT)i<(*GPU)->m_NGPUNIT && ret<0;i++)
			if (GPU[i] && tmp==NULL && GPU[i]->UnitHWND && (GPU[i]->UnitType==UT_FRAMEBAR || GPU[i]->UnitType==UT_DLGBAR)) 
			{
				if (GPU[i]->UnitType==UT_FRAMEBAR)
						tmp=((GPFrameBar *)GPU[i]->UnitPtr)->DlgAutoSize->GetResizingOwner(UnitHWND);
					else
					if (GPU[i]->UnitType==UT_DLGBAR)
						tmp=((GPDlgBar *)(GPU[i]->UnitPtr))->DlgAutoSize->GetResizingOwner(UnitHWND);
				if (tmp)
					for(ret=0;(UINT)ret<(*GPU)->m_NGPUNIT && (GPU[ret]==NULL || GPU[ret]->UnitHWND!=tmp);ret++);
			}
	}

	return ret;
}



void GPUnit::SetFont(CFont *fn)
{
	if ((UnitPtr || UnitType==UT_MAINDLGSCR) && UnitHWND)
		switch(UnitType)
		{
		case UT_DATETIMECTRL:
		case UT_MONTHCAL:
		case UT_DRAW:
		case UT_DLGBAR:
		case UT_FRAMEBAR:
		case UT_TREECTRL:
		case UT_HEADER:
		case UT_SLIDER:
		case UT_TABCTRL:
		case UT_SPINBUTTON:
		case UT_BUTTON:
		case UT_ANIBUTTON:
		case UT_BBUTTON:
		case UT_STATIC:
		case UT_ANISTATIC:
		case UT_EDIT:
		case UT_LISTBOX:
		case UT_CONTROL:
		case UT_COMBOBOX:
		case UT_COMBOBOXEX:
		case UT_SCROLLBAR:
		case UT_PROGRESS:
		case UT_ANIMAT:
		case UT_CHECKLISTBOX:
		case UT_DRAGLISTBOX:
		case UT_LISTCTRL:
		case UT_STATUSBARCTRL:
		case UT_TOOLBARCTRL:
		case UT_STATUSBAR:
		case UT_TOOLBAR:
		case UT_DIALOGBAR:
		case UT_REBARCTRL:
		case UT_REBAR:
		case UT_MAINDLGSCR: /*cwnd*/
		case UT_FLEXGRID:
		case UT_WEBBROWSER:
			CWnd::FromHandle(UnitHWND)->SetFont(fn);		break;
		}// end TypeUnit Switch

}


BOOL GPUnit::DoCCMethod(const char *iStr, char *oStr)
{
	BOOL FRet=FALSE;
	try
	{
		if ((UnitPtr || UnitType==UT_MAINDLGSCR) && UnitHWND)
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
				for(nfunc=0;nfunc<uNCCMethods && _stricmp(met,cArrCCMethods[nfunc])!=0;nfunc++);

			FRet=TRUE;
			if (oStr) *oStr=0;
			switch(nfunc)
			{
			case 0: /*SetBkColor*/
				{
					COLORREF clr=CLR_DEFAULT;
					COLORREF clrret=CLR_DEFAULT;
					if (*pos)
					{
						UINT r=0,g=0,b=0;
						m_LastScanf=sscanf(pos,"%d,%d,%d",&r,&g,&b);
						clr=RGB(r,g,b);
					}
					clrret=SendMessage(UnitHWND,CCM_SETBKCOLOR,0,(LPARAM)clr);
					if (oStr)
						sprintf(oStr,"%d\x07%d\x07%d",GetRValue(clrret),GetGValue(clrret),GetBValue(clrret));
				}
				break;
			case 1: /*SetColorScheme*/
				{
					COLORSCHEME cs={0};
					cs.dwSize=sizeof(cs);
					cs.clrBtnHighlight=CLR_DEFAULT;
					cs.clrBtnShadow=CLR_DEFAULT;
					if (*pos)
					{
						UINT r=0,g=0,b=0;
						m_LastScanf=sscanf(pos,"%d,%d,%d",&r,&g,&b);
						cs.clrBtnHighlight=RGB(r,g,b);
					}
					const char *tmp=FindField(pos,3,",");
					if (*tmp)
					{
						UINT r=0,g=0,b=0;
						m_LastScanf=sscanf(tmp,"%d,%d,%d",&r,&g,&b);
						cs.clrBtnShadow=RGB(r,g,b);
					}
					SendMessage(UnitHWND,CCM_SETCOLORSCHEME,0,(LPARAM)&cs);
				}
				break;
			case 2: /*GetColorScheme*/
				if (oStr)
				{
					COLORSCHEME cs={0};
					cs.dwSize=sizeof(cs);
					cs.clrBtnHighlight=CLR_DEFAULT;
					cs.clrBtnShadow=CLR_DEFAULT;
					SendMessage(UnitHWND,CCM_GETCOLORSCHEME,0,(LPARAM)&cs);
					sprintf(oStr,"%d\x07%d\x07%d\x7F%d\x07%d\x07%d",
						GetRValue(cs.clrBtnHighlight),GetGValue(cs.clrBtnHighlight),GetBValue(cs.clrBtnHighlight),
						GetRValue(cs.clrBtnShadow),GetGValue(cs.clrBtnShadow),GetBValue(cs.clrBtnShadow)
						);
				}
				break;
			case 3: /*SetUnicodeFormat*/
				retint=SendMessage(UnitHWND,CCM_SETUNICODEFORMAT,atoipos,0);
				break;
			case 4: /*GetUnicodeFormat*/
				retint=SendMessage(UnitHWND,CCM_GETUNICODEFORMAT,0,0);
				break;
			case 5: /*SetVersion*/
				retint=SendMessage(UnitHWND,CCM_SETVERSION,atoipos,0);
				break;
			case 6: /*GetVersion*/
				retint=SendMessage(UnitHWND,CCM_GETVERSION,0,0);
				break;
			case 7: /*CCSetWindowTheme*/
				{
					CString tmps=pos;
					BSTR tmpbstr=tmps.AllocSysString();
					retint=SendMessage(UnitHWND,CCM_SETWINDOWTHEME,0,(LPARAM)tmpbstr);
					::SysFreeString(tmpbstr);
				}
				break;
			case 8: /*DPIScale*/
				SendMessage(UnitHWND,CCM_DPISCALE,atoipos,0);
				break;

			case 12345678:
			default: if (oStr)	sprintf(oStr,ErrObjSub,met);FRet=FALSE;break;
			}
			if (oStr && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
		}
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPUnit", "DoCCMethod",iStr);
	}
	return FRet;
}


BOOL GPUnit::DoWindowMethod(const char *iStr, char *oStr)
{
	BOOL FRet=FALSE;
	try
	{
		if ((UnitPtr || UnitType==UT_MAINDLGSCR))
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

			if (*met>='W' && met[1]>='0' && met[1]<='9') nfunc=atoi(met+1);
			else
			{
				static const char *sccArrMethods[sizeof(cArrMethods)/sizeof(char *)];
				static DWORD scdMethodsId[sizeof(cArrMethods)/sizeof(char *)];
				static DWORD uNMethods;
				if (!*sccArrMethods)
				{
					for(uNMethods=0;*cArrMethods[uNMethods];uNMethods++)
					{
						sccArrMethods[uNMethods]=cArrMethods[uNMethods];
						scdMethodsId[uNMethods]=uNMethods;
					}
					qsCharILineAndDWORD(sccArrMethods, scdMethodsId, 0, uNMethods-1);
					scdMethodsId[uNMethods]=uNMethods;
				}
				nfunc=scdMethodsId[FindInSortArrayIC(met, sccArrMethods, uNMethods)];
			}

			if (oStr) *oStr=0;
			if (UnitHWND || nfunc==119)
			{
				FRet=TRUE;
				switch(nfunc)
				{
				case 0: /*CalcWindowRect*/
					if (oStr)
					{
						CRect re(0,0,0,0);
						int AdjBo=0;
						m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d",&re.left,&re.top,&re.right,&re.bottom,&AdjBo);
						CWnd::FromHandle(UnitHWND)->CalcWindowRect(&re,AdjBo);
						sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
					}
					break;
				case 1: /*GetStyle*/
					if (oStr)
					{
						DWORD stl=::GetWindowLong(UnitHWND,GWL_STYLE);
						int i;
						for(i=0;i<N_WND_STYLES;i++)
							if ((aWndStyleUINT[i]&stl)==aWndStyleUINT[i])	strcat(oStr,aWndStyleName[i]);
					}
					break;
				case 2: /*GetExStyle*/
					if (oStr)
					{
						DWORD stl=::GetWindowLong(UnitHWND,GWL_EXSTYLE);
						int i;
						for(i=0;i<N_WND_EX_STYLES;i++)
							if ((aWndExStyleUINT[i]&stl)==aWndExStyleUINT[i])	strcat(oStr,aWndExStyleName[i]);
					}
					break;
				case 3: /*SetFocus*/
					{
						HWND tmp=SetFocus(UnitHWND);
						if (oStr) sprintf(oStr,"%X",(DWORD)tmp);
					}
					break;
				case 4: /*Invalidate*/
					CWnd::FromHandle(UnitHWND)->Invalidate(*pos?atoipos:TRUE);
					break;
				case 5: /*GetWindowText*/
					if (oStr)
					{
						switch(UnitType)
						{
						case UT_CONTROL:
							{
								CString tmps=pos;
								BSTR tmpBSTR=tmps.AllocSysString();
								::SendMessage(UnitHWND,GPM_AX_GETWINDOWTEXT,0,(LPARAM)(&tmpBSTR));
								tmps=tmpBSTR;
								::SysFreeString(tmpBSTR);
								strcpy(oStr,tmps);
							}
							break;
						case UT_RTF:
							((GP_RTF*)UnitPtr)->DoMethod("GetLine 0",oStr);
							break;
						case UT_EDIT:
							((GPEdit*)UnitPtr)->DoMethod("GetAllText",oStr);
							break;
						case UT_EDITOR:
							((GPScintilla*)UnitPtr)->DoMethod("GetLine 0",oStr);
							break;
						case UT_HEADER:
						case UT_DRAW:
						case UT_ANIMAT:
							break;
						case UT_TREECTRL: 	((GPTree*)UnitPtr)->DoMethod("GetSelectedItem",oStr);	break;
						case UT_SLIDER:		((GPSlider*)UnitPtr)->DoMethod("GetPos",oStr);			break;
						case UT_TABCTRL: 	((GPTabCtrl*)UnitPtr)->DoMethod("GetCurSel",oStr);		break;
						case UT_SPINBUTTON: ((GPSpinButton*)UnitPtr)->DoMethod("GetPos",oStr);		break;
						case UT_LISTBOX:	((GPListBox*)UnitPtr)->DoMethod("GetSelectedItem",oStr);	break;
						case UT_SCROLLBAR: 	((GPScrollBar*)UnitPtr)->DoMethod("GetScrollPos",oStr);	break;
						case UT_PROGRESS: 	((GPProgress*)UnitPtr)->DoMethod("GetPos",oStr);			break;
						case UT_CHECKLISTBOX:((GPChLBox*)UnitPtr)->DoMethod("GetSelectedItem",oStr);	break;
						case UT_DRAGLISTBOX: ((GPDrLBox*)UnitPtr)->DoMethod("GetSelectedItem",oStr);	break;
						case UT_LISTCTRL: 	((GPListCtr*)UnitPtr)->DoMethod("GetSelected",oStr);		break;
						case UT_FLEXGRID:	strcpy(oStr,((GPCMSFlexGrid *)UnitPtr)->GetText());		break;
						case UT_WEBBROWSER:	((GPWebBrowser2 *)UnitPtr)->DoMethod("GetLocationName",oStr);	break;
						case UT_COMBOBOX:
						case UT_COMBOBOXEX:
						case UT_DATETIMECTRL:
						case UT_MONTHCAL:
						case UT_STATUSBARCTRL:
						case UT_TOOLBARCTRL:
						case UT_STATUSBAR:
						case UT_TOOLBAR:
						case UT_DIALOGBAR:
						case UT_REBARCTRL:
						case UT_REBAR:
						default:
							{
								int nnn=::GetWindowTextLength(UnitHWND);
								if (nnn>TMP_STR_OUT_LEN-10) nnn=TMP_STR_OUT_LEN-10;
								if (nnn) nnn=::GetWindowText(UnitHWND,oStr,nnn+2);
								oStr[nnn]=0;
								char *str=oStr;
								char *str2=oStr;
								while(*(str)!=0)
								{
									if ((*str==10 && str[1]==13) || (*str==13 && str[1]==10)) {str++;*(str2++)=127;}
									else
									if (*str==13 || *str==10) *(str2++)=127;
									else *(str2++)=*str;
									str++;
								}
							}
							break;
						}// end TypeUnit Switch
					}
					break;

				case 12: /*GetWindowTextEx*/
					if (oStr)
					{
						switch(UnitType)
						{
						case UT_CONTROL:
							{
								CString tmps=pos;
								BSTR tmpBSTR=tmps.AllocSysString();
								::SendMessage(UnitHWND,GPM_AX_GETWINDOWTEXTEX,0,(LPARAM)(&tmpBSTR));
								tmps=tmpBSTR;
								::SysFreeString(tmpBSTR);
								strcpy(oStr,tmps);
							}
							break;
						case UT_RTF:
							((GP_RTF*)UnitPtr)->DoMethod("GetLine 0",oStr);
							break;
						case UT_EDITOR:
							((GPScintilla*)UnitPtr)->DoMethod("GetLine 0",oStr);
							break;
						case UT_HEADER:
						case UT_DRAW:
						case UT_ANIMAT:	break;
						case UT_DATETIMECTRL: 	((GPDateTimeCtrl *)UnitPtr)->DoMethod("GetTime",oStr);	break;
						case UT_MONTHCAL:		((GPMonthCalCtrl *)UnitPtr)->DoMethod("GetCurSel",oStr);	break;
						case UT_TREECTRL:		((GPTree*)UnitPtr)->DoMethod("GetSelectedItem",oStr);	break;
						case UT_SLIDER: 		((GPSlider*)UnitPtr)->DoMethod("GetPos",oStr);			break;
						case UT_TABCTRL: 		((GPTabCtrl*)UnitPtr)->DoMethod("GetCurSel",oStr);		break;
						case UT_SPINBUTTON:		((GPSpinButton*)UnitPtr)->DoMethod("GetPos",oStr);		break;
						case UT_LISTBOX: 		((GPListBox*)UnitPtr)->DoMethod("GetSelectedItem",oStr);	break;
						case UT_COMBOBOX: 		((GPComboBox*)UnitPtr)->DoMethod("GetCurSel",oStr);		break;
						case UT_COMBOBOXEX:		((GPComboBoxEx*)UnitPtr)->DoMethod("GetCurSel",oStr);	break;
						case UT_SCROLLBAR: 		((GPScrollBar*)UnitPtr)->DoMethod("GetScrollPos",oStr);	break;
						case UT_PROGRESS: 		((GPProgress*)UnitPtr)->DoMethod("GetPos",oStr);			break;
						case UT_CHECKLISTBOX:	((GPChLBox*)UnitPtr)->DoMethod("GetSelectedItem",oStr);	break;
						case UT_EDIT:			((GPEdit*)UnitPtr)->DoMethod("GetAllText",oStr);	break;
						case UT_DRAGLISTBOX:	((GPDrLBox*)UnitPtr)->DoMethod("GetSelectedItem",oStr);	break;
						case UT_LISTCTRL: 		((GPListCtr*)UnitPtr)->	DoMethod("GetSelected",oStr);	break;
						case UT_WEBBROWSER:		((GPWebBrowser2 *)UnitPtr)->DoMethod("GetLocationName",oStr);	break;
						case UT_FLEXGRID:
							strcpy(oStr,(LPCTSTR)((GPCMSFlexGrid *)UnitPtr)->GetText());
							break;
						case UT_BUTTON:
							{
								char *postmp=oStr;
								((GPButton*)UnitPtr)->DoMethod("GetState",oStr);
								while(*postmp) 
									if (*postmp==0x7F) *(postmp++)=0x7;
										else postmp++;
								*(postmp++)=0x7F;
								*postmp=0;
								DoWindowMethod("GetWindowText",postmp);
							}
							break;
						case UT_BBUTTON:
							{
								char *postmp=oStr;
								((GPBButton*)UnitPtr)->DoMethod("GetState",oStr);
								while(*postmp) 
									if (*postmp==0x7F) *(postmp++)=0x7;
										else postmp++;
								*(postmp++)=0x7F;
								*postmp=0;
								DoWindowMethod("GetWindowText",postmp);
							}
							break;
						case UT_STATUSBARCTRL:
						case UT_TOOLBARCTRL:
						case UT_STATUSBAR:
						case UT_TOOLBAR:
						case UT_DIALOGBAR:
						case UT_REBARCTRL:
						case UT_REBAR:
						default:
							{
								int nnn=::GetWindowTextLength(UnitHWND);
								if (nnn)
								{
									if (nnn>TMP_STR_OUT_LEN) nnn=TMP_STR_OUT_LEN-10;
									nnn=::GetWindowText(UnitHWND,oStr,nnn+2);
								}
								oStr[nnn]=0;
								char *str=oStr;str--;
								while(*(++str)!=0)
									if (*str==10) *str=' ';
									else
									if (*str==13) *str=127;
											break;
										}// end TypeUnit Switch
										char *pp=oStr;
										while(*pp!=0)
										{
											if (*pp=='13' || *pp=='10') *pp=127;
											pp++;
										}
									}
							}
							break;

				case 6: /*ClientToScreen*/
				case 7: /*ScreenToClient*/
				case 8: /*GetClientOffset*/
					if (oStr)
					{
						POINT po={0},po2={1234,4321};
						CString tmps=pos;
						tmps.Replace(GPC.DelimiterIn1,',');
						m_LastScanf=sscanf(tmps,"%d,%d,%d,%d",&po.x,&po.y,&po2.x,&po2.y);
						switch(nfunc)
						{
						case 6: /*ClientToScreen*/
								::ClientToScreen(UnitHWND,&po);
								::ClientToScreen(UnitHWND,&po2);
								break;
						case 7: /*ScreenToClient*/
								::ScreenToClient(UnitHWND,&po);
								::ScreenToClient(UnitHWND,&po2);
								break;
						case 8: /*GetClientOffset*/
								::ClientToScreen(UnitHWND,&po);
								::ClientToScreen(UnitHWND,&po2);
								break;
						}
						if (po2.x==1234 &&  po2.y==4321)
							sprintf(oStr,"%d\x7F%d",po.x,po.y);
						else
							sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",po.x,po.y,po2.x,po2.y);
					}
					break;
				case 9: /*InvalidateParent*/
					{
						try
						{
							CWnd::FromHandle(UnitHWND)->GetParent()->Invalidate();
						}
						catch(...)
						{
							GPC.m_ErrReport.GPWriteErrorLog("GPUnit", "DoWindowMethod 3457",iStr);
						}
					}
					break;
				case 10: /*GetFocus*/
				case 30: /*GetActiveWindow*/
				case 31: /*SetActiveWindow*/
				case 32: /*GetCapture*/
				case 33: /*SetCapture*/
				case 34: /*GetForegroundWindow*/
				case 37: /*ChildWindowFromPoint*/
					{
						CWnd *tmp=NULL;
						switch(nfunc)
						{
						case 10:	tmp=CWnd::GetFocus(); break;
						case 30:	tmp=CWnd::GetActiveWindow();break;
						case 31:	tmp=CWnd::FromHandle(UnitHWND)->SetActiveWindow();break;
						case 32:	tmp=CWnd::GetCapture();break;
						case 33:	tmp=CWnd::FromHandle(UnitHWND)->SetCapture();break;
						case 34:	tmp=CWnd::GetForegroundWindow();break;
						case 37: /*ChildWindowFromPoint*/
							{
								char *pos333=new char [(int)strlen(pos)+2];
								strcpy(pos333,pos);
								CPoint po(0,0);
								m_LastScanf=sscanf(pos333,"%d,%d",&po.x,&po.y);
								UINT uStl[4]={CWP_ALL,CWP_SKIPINVISIBLE,CWP_SKIPDISABLED,CWP_SKIPTRANSPARENT,};
								char *cStl[4]={"ALL","SKIPINVISIBLE","SKIPDISABLED","SKIPTRANSPARENT",};
								_strupr(pos333);
								UINT stl=0;
								int i;
								for(i=0;i<4;i++)
									if (strstr(pos333,cStl[i])) stl|=uStl[i];
								tmp=CWnd::FromHandle(UnitHWND)->ChildWindowFromPoint(po,stl);
								delete[] pos333;
							}
							break;
						}
						retint=-1;
						if (tmp)
						{
							int i;
							for(i=0;(UINT)i<(*GPU)->m_NGPUNIT;i++)
								if (GPU[i] && GPU[i]->UnitHWND==tmp->m_hWnd)
									retint=i; break;
						}
					}
					break;
				case 11: /*GetNextDlgTabItem*/
					if (oStr)
					{
						HWND tmp=::GetFocus();
						retint=-1;
						if (tmp)
						{
							int n=atoi(pos);
							if (n>0) while(n-->0) tmp=::GetNextDlgTabItem(UnitHWND,tmp,FALSE);
							else  while(n++<0) tmp=::GetNextDlgTabItem(UnitHWND,tmp,TRUE);
							int i;
							for(i=0;(UINT)i<(*GPU)->m_NGPUNIT;i++)
								if (GPU[i] && GPU[i]->UnitHWND==tmp)
								{
									retint=i;	break;
								}
						}
					}
					break;
				case 13: /*ShowWindow cmdShow*/
				case 146: /*ShowWindowAsync cmdShow*/
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						_strupr(pos333);
						int i;
						for(i=0; i < N_WND_SHOW_STYLES && strstr(pos333,aWndShowStyleName[i])==NULL; i++);
						if (i<N_WND_SHOW_STYLES)
						{
							if (nfunc==146)
								retint=::ShowWindowAsync(UnitHWND,aWndShowStyleUINT[i]);
							else
								retint=::ShowWindow(UnitHWND,aWndShowStyleUINT[i]);
						}
						delete[] pos333;
					}
					break;

				case 14: /*SetForegroundWindow*/
					retint=::SetForegroundWindow(UnitHWND);
					break;
				case 15: /*FlashWindow*/
					retint=::FlashWindow(UnitHWND,atoi(pos));
					break;
				case 16: /*FlashWindowEx*/
						#ifdef W_95
						#else
							#ifdef W_NT
							#else
							{
								char *pos333=new char [(int)strlen(pos)+2];
								strcpy(pos333,pos);
								FLASHWINFO fwi={0};
								fwi.cbSize=sizeof(fwi);
								fwi.hwnd=UnitHWND;
								m_LastScanf=sscanf(pos333,"%d,%d",&fwi.uCount,&fwi.dwTimeout);
								fwi.dwFlags=0;
								_strupr(pos333);

								char *nmflg[6]={"_STOP","_CAPTION","_TRAY","_ALL","_TIMER","_NOFGTIMER",};
								UINT uflg[6]={FLASHW_STOP,FLASHW_CAPTION,FLASHW_TRAY,FLASHW_ALL,FLASHW_TIMER,FLASHW_TIMERNOFG,};

								int i;
								for(i=0;i<6;i++)
									if (strstr(pos333,nmflg[i]))
										fwi.dwFlags|=uflg[i];

								retint=FlashWindowEx(&fwi);
								delete[] pos333;
							}
							#endif
						#endif
					break;
				case 17: /*BringWindowToTop*/
					retint=::BringWindowToTop(UnitHWND);
					break;
				case 18: /*ArrangeIconicWindows*/
					retint=::ArrangeIconicWindows(UnitHWND);
					break;
				case 19: /*IsIconic*/
					retint=::IsIconic(UnitHWND);
					break;
				case 20: /*IsZoomed*/
					retint=::IsZoomed(UnitHWND);
					break;
				case 21: /*GetWindowRect*/
				case 22: /*GetClientRect*/
					if (oStr)
					{
						RECT re={0};
						if (nfunc==21)	::GetWindowRect(UnitHWND,&re);
							else		::GetClientRect(UnitHWND,&re);

							if (atoipos==1)
							{
								::ScreenToClient(::GetParent(UnitHWND),(LPPOINT)(&re));
								::ScreenToClient(::GetParent(UnitHWND),((LPPOINT)(&re))+1);
							}
						sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
						
					}
					break;
				case 23: /*SetWindowPos*/
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						int x=0, y=0, cx=0, cy=0,nAfter=-1;
						_strupr(pos333);
						UINT uStl[13]={SWP_DRAWFRAME,SWP_FRAMECHANGED,SWP_HIDEWINDOW,SWP_NOACTIVATE,SWP_NOCOPYBITS,SWP_NOMOVE,SWP_NOOWNERZORDER,SWP_NOREDRAW,SWP_NOREPOSITION,SWP_NOSENDCHANGING,SWP_NOSIZE,SWP_NOZORDER,SWP_SHOWWINDOW,};
						char *cStl[13]={"_DRAWFRAME","_FRAMECHANGED","_HIDEWINDOW","_NOACTIVATE","_NOCOPYBITS","_NOMOVE","_NOOWNERZORDER","_NOREDRAW","_NOREPOSITION","_NOSENDCHANGING","_NOSIZE","_NOZORDER","_SHOWWINDOW",};
						UINT stl=0;
						int i;
						for(i=0;i<13;i++)
							if (strstr(pos333,cStl[i]))
								stl|=uStl[i];

						m_LastScanf=sscanf(pos333,"%d,%d,%d,%d,%d",&x,&y,&cx,&cy,&nAfter);
						retint=0;

						const CWnd *tmpAfter=&CWnd::wndTop;
						if (nAfter>=0 && (UINT)nAfter<=(*GPU)->m_NGPUNIT && GPU[nAfter] && GPU[nAfter]->UnitHWND)
							tmpAfter=CWnd::FromHandle(GPU[nAfter]->UnitHWND);
						else
						{
							const CWnd *wStl2[4]={&CWnd::wndBottom,&CWnd::wndTopMost,&CWnd::wndTop,&CWnd::wndNoTopMost,};
							char *cStl2[4]={"WNDBOTTOM","WNDTOPMOST","WNDTOP","WNDNOTOPMOST",};

							for(i=0;i<4 ;i++);
								if (strstr(pos333,cStl2[i]))
								{	tmpAfter=wStl2[i]; break;}
						}
						retint=::SetWindowPos(UnitHWND,tmpAfter->m_hWnd,x,y,cx,cy,stl);
						delete[] pos333;
					}
					break;
				case 24: /*MoveWindow*/
					{
						int x=0, y=0, cx=10, cy=10,Repa=1;
						m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d",&x,&y,&cx,&cy,&Repa);
						::MoveWindow(UnitHWND,x,y,cx-x,cy-y,Repa);
					}
					break;
				case 25: /*SetWindowPlacement*/
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						_strupr(pos333);
						WINDOWPLACEMENT wp;
						wp.length=sizeof(wp);
						wp.flags=WPF_RESTORETOMAXIMIZED|WPF_SETMINPOSITION;

						wp.ptMaxPosition.x=wp.ptMaxPosition.y=0;
						wp.ptMinPosition.x=wp.ptMinPosition.y=0;
						wp.rcNormalPosition.left=wp.rcNormalPosition.right=wp.rcNormalPosition.top=wp.rcNormalPosition.bottom=0;
						wp.showCmd=0;
						m_LastScanf=sscanf(pos333,"%d,%d,%d,%d,%d,%d,%d,%d",&wp.rcNormalPosition.left,&wp.rcNormalPosition.top,&wp.rcNormalPosition.right,&wp.rcNormalPosition.bottom,&wp.ptMinPosition.x,&wp.ptMinPosition.y,&wp.ptMaxPosition.x,&wp.ptMaxPosition.y);

						int i;
						for(i=0;i<N_WND_SHOW_STYLES;i++)
							if(strstr(pos333,aWndShowStyleName[i]))
								wp.showCmd=aWndShowStyleUINT[i];

						::SetWindowPlacement(UnitHWND,&wp);
						delete[] pos333;
					}
					break;
				case 26: /*GetWindowPlacement*/
					if (oStr)
					{
						WINDOWPLACEMENT wp;
						wp.length=sizeof(wp);
						wp.flags=WPF_RESTORETOMAXIMIZED|WPF_SETMINPOSITION;
						::GetWindowPlacement(UnitHWND,&wp);
						int i;
						for(i=0;i<N_WND_SHOW_STYLES && wp.showCmd!=aWndShowStyleUINT[i];i++);

						if(i>=N_WND_SHOW_STYLES) i=0;

						sprintf(oStr,"%d\x07%d\x07%d\x07%d\x7F%d\x07%d\x7F%d\x07%d\x7F%s",
							wp.rcNormalPosition.left,wp.rcNormalPosition.top,wp.rcNormalPosition.right,wp.rcNormalPosition.bottom,
							wp.ptMinPosition.x,wp.ptMinPosition.y,
							wp.ptMaxPosition.x,wp.ptMaxPosition.y,
							aWndShowStyleName[i]);
					}
					break;
				case 27: /*AnimateWindow*/
					#ifdef W_95
					#else
						#ifdef W_NT
						#else
							if (UnitHWND)
							{
								UINT uType[10]={AW_SLIDE,AW_ACTIVATE,AW_BLEND,AW_HIDE,AW_CENTER,AW_HOR_POSITIVE,AW_HOR_NEGATIVE,AW_VER_POSITIVE,AW_VER_NEGATIVE,};
								char *cType[10]={"AW_SLIDE","AW_ACTIVATE","AW_BLEND","AW_HIDE","AW_CENTER","AW_HOR_POSITIVE","AW_HOR_NEGATIVE","AW_VER_POSITIVE","AW_VER_NEGATIVE",};
								char *pos333=new char [(int)strlen(pos)+2];
								strcpy(pos333,pos);
								_strupr(pos333);
								if (atoipos<0 || atoipos>30000) atoipos=200;
								UINT stl=0;
								int i;
								for(i=0;i<9 ;i++)
									if (strstr(pos333,cType[i])) stl|=uType[i];
								AnimateWindow(UnitHWND,atoipos,stl);
								delete[] pos333;
							}
						#endif
					#endif
					break;
				case 28: /*IsWindowEnabled*/retint=::IsWindowEnabled(UnitHWND);		break;
				case 29: /*EnableWindow*/	retint=::EnableWindow(UnitHWND,atoipos);	break;
				case 35: /*GetWindowContextHelpId*/	retint=::GetWindowContextHelpId(UnitHWND);		break;
				case 36: /*SetWindowContextHelpId*/	retint=::SetWindowContextHelpId(UnitHWND,atoipos);	break;
				case 38: /*GetZOrder*/
					if (UnitHWND && oStr)
					{
						char *outpos=oStr;
						HWND hWndChild ;
						for(hWndChild = GetTopWindow(UnitHWND); hWndChild != NULL;	hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
						{
							if (*oStr!=0) *(outpos++)=0x7F;
							char tmps[250];
							sprintf(tmps,"GetObjectByHWND %d",(DWORD)hWndChild);
							GPU[0]->DoMethod(tmps,outpos);
							char *tmppos=outpos;
							while((tmppos=strchr(tmppos,0x7F))) *(tmppos++)=0x7;
							outpos+=(int)strlen(outpos);
						}
					}
					break;
				case 39: /*SetZOrder*/
					if (UnitHWND && GPU)
					{
						const char *pos2=pos;
						HWND hAfter=UnitHWND;
						while(*pos2!=0)
						{
							UINT n=atoi(pos2);
							if (n>0 && n<(*GPU)->m_NGPUNIT && GPU[n] && GPU[n]->UnitHWND && GPU[n]->UnitHWND!=UnitHWND)
							{
								::SetWindowPos(GPU[n]->UnitHWND,hAfter,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOOWNERZORDER|SWP_NOSENDCHANGING);
								hAfter=GPU[n]->UnitHWND;
							}
							while(*pos2!=0 && *pos2!=GPC.DelimiterIn1 && *pos2!=',' && *pos2!=';') pos2++;
							if (*pos2!=0) pos2++;
						}
					}
					break;
				case 40: /*SetIcon*/
					{
						int num=0;
						const char *pos2=strchr(pos,',');
						if (pos2++==NULL) pos2="MISCL";
						if ((num=GPC.GetImageListId(pos2))>=0 && GPC.a_GPImageList[num].m_IL.m_hImageList)
						{
							HICON tmpHICON=GPC.a_GPImageList[num].m_IL.ExtractIcon(atoipos);
							IMAGEINFO ii={0};
							GPC.a_GPImageList[num].m_IL.GetImageInfo(atoipos,&ii);
							DestroyIcon(CWnd::FromHandle(UnitHWND)->SetIcon(tmpHICON,ii.rcImage.bottom-ii.rcImage.top>16));
						}
					}
					break;
				case 41: /*GetNextWindow*/
				case 42: /*GetOwner*/
				case 44: /*GetTopWindow*/
				case 45: /*GetWindow*/
				case 46: /*GetLastActivePopup*/
				case 47: /*GetParent*/
				case 49: /*WindowFromPoint*/
					{
						HWND tmphWnd=NULL;
						CWnd *tmpcwnd=NULL;
						switch(nfunc)
						{
						case 41:/*GetNextWindow*/
							tmphWnd=GetNextWindow(UnitHWND,atoipos==0?GW_HWNDNEXT:GW_HWNDPREV);	break;
						case 42:/*GetOwner*/
							tmpcwnd=CWnd::FromHandle(UnitHWND)->GetOwner();
							if (tmpcwnd) tmphWnd=tmpcwnd->m_hWnd;
							break;
						case 44: /*GetTopWindow*/
							tmphWnd=GetTopWindow(UnitHWND);	break;
						case 45: /*GetWindow*/
							{
								char *pos333=new char [(int)strlen(pos)+2];
								strcpy(pos333,pos);
								const char *cNm[7]={"FIRST","LAST","NEXT","PREV","OWNER","CHILD","MAX",};
								const UINT  uNm[8]={GW_HWNDFIRST,GW_HWNDLAST,GW_HWNDNEXT,GW_HWNDPREV,GW_OWNER,GW_CHILD,GW_MAX,GW_HWNDFIRST};
								_strupr(pos333);
								int i;
								for(i=0;i<7 && strstr(pos333,cNm[i])==NULL;i++);
								tmpcwnd=CWnd::FromHandle(UnitHWND)->GetWindow(uNm[i]);
								if (tmpcwnd) tmphWnd=tmpcwnd->m_hWnd;
								delete[] pos333;
							}
							break;
						case 46: /*GetLastActivePopup*/
							tmphWnd=GetLastActivePopup(UnitHWND);	break;
						case 47: /*GetParent*/
							tmphWnd=GetParent(UnitHWND);	break;
						case 49: /*WindowFromPoint*/
							{
								CPoint po(0,0);
								m_LastScanf=sscanf(pos,"%d,%d",&po.x,&po.y);
								tmphWnd=WindowFromPoint(po);
							}
							break;
						}

						if (tmphWnd==NULL) retint=-1;
						else
						{
							int i;
							for(i=0;(UINT)i<(*GPU)->m_NGPUNIT;i++)
								if (GPU[i] && GPU[i]->UnitHWND==tmphWnd)
									{	retint=i;	break;	}
						}
					}
					break;
				case 43: /*SetOwner*/
					if (atoipos>=0 && (UINT)atoipos<(*GPU)->m_NGPUNIT && GPU[atoipos] && GPU[atoipos]->UnitHWND)
						CWnd::FromHandle(UnitHWND)->SetOwner(CWnd::FromHandle(GPU[atoipos]->UnitHWND));
					else
						if (atoipos==-1)
							CWnd::FromHandle(UnitHWND)->SetOwner(CWnd::FromHandle(GetDesktopWindow()));
					break;
				case 48: /*SetParent*/
					if (atoipos>=0 && (UINT)atoipos<(*GPU)->m_NGPUNIT && GPU[atoipos] && GPU[atoipos]->UnitHWND)
						::SetParent(UnitHWND,GPU[atoipos]->UnitHWND);
					else
						if (atoipos==-1)
							::SetParent(UnitHWND,GetDesktopWindow());
					break;
				case 50: /*CenterWindow*/
					{
						CWnd* pAlternateOwner=NULL;
						if (atoipos>=0 && (UINT)atoipos<(*GPU)->m_NGPUNIT && GPU[atoipos] && GPU[atoipos]->UnitHWND)
							pAlternateOwner=CWnd::FromHandle(GPU[atoipos]->UnitHWND);
						CWnd::FromHandle(UnitHWND)->CenterWindow(pAlternateOwner);
					}
					break;
				case 51: /*InvalidateRect*/
					{
						CRect re(0,0,0,0);
						UINT bErase;
						m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d",&re.left,&re.top,&re.right,&re.bottom,&bErase);
						retint=InvalidateRect(UnitHWND,re,bErase);
					}
					break;
				case 52: /*IsWindowVisible*/
					retint=::IsWindowVisible(UnitHWND);
					break;
				case 53: /*ShowOwnedPopups*/
					retint=::ShowOwnedPopups(UnitHWND,atoipos);
					break;
				case 54: /*EnableScrollBar*/
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						const char *nmwSBflags[4]={"SB_BOTH","SB_CTL","SB_HORZ","SB_VERT",};
						const char *nmwArrows[8]={"ESB_DISABLE_BOTH","ESB_DISABLE_DOWN","ESB_DISABLE_LEFT","ESB_DISABLE_LTUP","ESB_DISABLE_RIGHT","ESB_DISABLE_RTDN","ESB_DISABLE_UP","ESB_ENABLE_BOTH",};
						const UINT uwSBflags[5]={SB_BOTH,SB_CTL,SB_HORZ,SB_VERT,SB_BOTH,};
						const UINT uwArrows[9]={ESB_DISABLE_BOTH,ESB_DISABLE_DOWN,ESB_DISABLE_LEFT,ESB_DISABLE_LTUP,ESB_DISABLE_RIGHT,ESB_DISABLE_RTDN,ESB_DISABLE_UP,ESB_ENABLE_BOTH,ESB_ENABLE_BOTH,};
						UINT wSBflags=0;
						UINT wArrows=0;
						int i;
						_strupr(pos333);
						for(i=0;i<4 && strstr(pos333,nmwSBflags[i])==NULL;i++);
						wSBflags=uwSBflags[i];

						for(i=0;i<8 && strstr(pos333,nmwArrows[i])==NULL;i++);
						wSBflags=uwArrows[i];

						EnableScrollBar(UnitHWND,wSBflags,wArrows);
						delete[] pos333;
					}
					break;
				case 55: /*MapWindowPoints*/
					if (oStr)
					{
						POINT po[5];
						po[0].x=po[0].y=po[1].x=po[1].y=0;
						UINT nObj=0;
						m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d",&nObj,&po[0].x,&po[0].y,&po[1].x,&po[1].y);
						HWND hWndTo=NULL;
						if (nObj>=0 && nObj<(*GPU)->m_NGPUNIT && GPU[nObj] && GPU[nObj]->UnitHWND)
							hWndTo=GPU[nObj]->UnitHWND;

						retint=MapWindowPoints(UnitHWND,hWndTo,po,2);
						sprintf(oStr,"%d\x7%d\x7F%d\x7%d",po[0].x,po[0].y,po[1].x,po[1].y);
					}
					break;
				case 56: /*GetScrollPos*/
				case 57: /*GetScrollRange*/
				case 58: /*SetScrollPos*/
				case 59: /*SetScrollRange*/
				case 60: /*ShowScrollBar*/
				case 61: /*SetScrollInfo*/
				case 62: /*GetScrollInfo*/
				case 63: /*GetScrollLimit*/
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						char *nm[4]={"CTL","HORZ","VERT","BOTH",};
						int ufl[5]={SB_CTL,SB_HORZ,SB_VERT,SB_BOTH,SB_CTL,};
						int i,wSBflags=0;
						_strupr(pos333);
						for(i=0;i<4 && strstr(pos333,nm[i])==NULL;i++);
						wSBflags=ufl[i];

						switch(nfunc)
						{
						case 56: /*GetScrollPos*/
							retint=GetScrollPos(UnitHWND,wSBflags);break;
						case 57: /*GetScrollRange*/
							if (oStr)
							{
								int posmin,posmax;posmin=posmax=0;
								GetScrollRange(UnitHWND,wSBflags,&posmin,&posmax);
								sprintf(oStr,"%d\x7F%d",posmin,posmax);
							}
							break;
						case 58: /*SetScrollPos*/
							{
								int nPos=0;
								BOOL bRedraw=TRUE;
								m_LastScanf=sscanf(pos333,"%d,%d",&nPos,&bRedraw);
								retint=SetScrollPos(UnitHWND,wSBflags,nPos,bRedraw);
							}
							break;
						case 59: /*SetScrollRange*/
							{
								int nMinPos=0,nMaxPos=0;
								BOOL bRedraw=TRUE;
								m_LastScanf=sscanf(pos333,"%d,%d,%d",&nMinPos,&nMaxPos,&bRedraw);
								retint=SetScrollRange(UnitHWND,wSBflags,nMinPos,nMaxPos,bRedraw);
							}
							break;
						case 60: /*ShowScrollBar*/	retint=ShowScrollBar(UnitHWND,wSBflags,atoipos);break;
						case 61: /*SetScrollInfo*/
							{
								BOOL redr=TRUE;
								SCROLLINFO si={0};
								si.cbSize=sizeof(si);
								m_LastScanf=sscanf(pos333,"%d,%d,%u,%d,%d,%d",&si.nMin,&si.nMax,&si.nPage,&si.nPos,&si.nTrackPos,&redr);
								si.fMask=SIF_ALL;
								retint=SetScrollInfo(UnitHWND,wSBflags,&si,redr);
							}
							break;
						case 62: /*GetScrollInfo*/
							if (oStr)
							{
								SCROLLINFO si={0};
								si.cbSize=sizeof(si);
								si.fMask=SIF_ALL;
								GetScrollInfo(UnitHWND,wSBflags,&si);
								sprintf(oStr,"%d\x7F%d\x7F%u\x7F%d\x7F%d",si.nMin,si.nMax,si.nPage,si.nPos,si.nTrackPos);
							}
							break;
						case 63: /*GetScrollLimit*/
							{
								CWnd *tmpcwnd=CWnd::FromHandle(UnitHWND);
								if (tmpcwnd)
									retint=tmpcwnd->GetScrollLimit(wSBflags);
							}
							break;
						}
						delete[] pos333;
					}
					break;
				case 64: /*ScrollWindow*/
					{
						CRect Rect(0,0,0,0);
						CRect ClipRect(0,0,0,0);
						int XAmount=0;            // horizontal scrolling
						int YAmount=0;            // vertical scrolling
						m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
							&XAmount,&YAmount,
							&Rect.left,&Rect.top,&Rect.right,&Rect.bottom,
							&ClipRect.left,&ClipRect.top,&ClipRect.right,&ClipRect.bottom);

						retint=ScrollWindow(UnitHWND,XAmount,YAmount,Rect.IsRectEmpty()?NULL:Rect,ClipRect.IsRectEmpty()?NULL:ClipRect);
					}
					break;
				case 65: /*ScrollWindowEx*/
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						CRect Rect(0,0,0,0);
						CRect ClipRect(0,0,0,0);
						CRect rcUpdate(0,0,0,0);
						int XAmount=0;            // horizontal scrolling
						int YAmount=0;            // vertical scrolling
						int iTime=0;
						UINT wSBflags=0;
						m_LastScanf=sscanf(pos333,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
							&XAmount,&YAmount,&iTime,
							&Rect.left,&Rect.top,&Rect.right,&Rect.bottom,
							&ClipRect.left,&ClipRect.top,&ClipRect.right,&ClipRect.bottom,
							&rcUpdate.left,&rcUpdate.top,&rcUpdate.right,&rcUpdate.bottom
							);
						_strupr(pos333);
						int i;

						char *nm[4]={"ERASE","INVALIDATE","SCROLLCHILDREN","SMOOTHSCROLL",};
						int ufl[5]={SW_ERASE,SW_INVALIDATE,SW_SCROLLCHILDREN,SW_SMOOTHSCROLL,SW_ERASE,};

						for(i=0;i<4 && strstr(pos333,nm[i])==NULL;i++);
						wSBflags=ufl[i];
						if (wSBflags==0x0010) wSBflags+=iTime*0x10000;

						retint=ScrollWindowEx(UnitHWND,XAmount,YAmount,Rect.IsRectEmpty()?NULL:Rect,ClipRect.IsRectEmpty()?NULL:ClipRect,NULL,rcUpdate.IsRectEmpty()?NULL:rcUpdate,wSBflags);
						delete[] pos333;
					}
					break;
				case 66: /*CreateCaret*/
					{
						int nWidth=0;
						int nHeight=0;
						int num=0;
						const char *tmp=strchr(pos,',');
						if (tmp++==NULL) tmp="";
						m_LastScanf=sscanf(pos,"%d,%d",&nWidth,&nHeight);
						HICON tmpHICON=NULL;

						HBITMAP hBitmap=NULL;
						if (strstr(tmp,"GRAY")) hBitmap=(HBITMAP)1;
						else
						if (*tmp!=0 && *tmp>='0' && *tmp<='9' && (num=GPC.GetImageListId(tmp))>=0)
						{
							tmpHICON=GPC.a_GPImageList[num].m_IL.ExtractIcon(nWidth);
							ICONINFO ii={0};
							GetIconInfo(tmpHICON,&ii);
							hBitmap=ii.hbmColor;
						}
						retint=CreateCaret(UnitHWND,hBitmap,nWidth,nHeight);
					}
					break;
				case 67: /*GetCaretPos*/
					if (oStr)
					{
						CPoint po(0,0);
						GetCaretPos(&po);
						sprintf(oStr,"%d\x7F%d",po.x,po.y);
					}
					break;
				case 68: /*SetCaretPos*/
					{
						int nWidth=0;
						int nHeight=0;
						m_LastScanf=sscanf(pos,"%d,%d",&nWidth,&nHeight);
						SetCaretPos(nWidth,nHeight);
					}
					break;
				case 69: /*HideCaret*/		retint=HideCaret(UnitHWND); break;
				case 70: /*ShowCaret*/		retint=ShowCaret(UnitHWND); break;
				case 71: /*GetNextDlgGroupItem*/
					{
						int idObj=0;
						int bPrevious=0;
						retint=-1;
						m_LastScanf=sscanf(pos,"%d,%d",&idObj,&bPrevious);
						if (idObj>=0 && (UINT)idObj<(*GPU)->m_NGPUNIT && GPU[idObj] && GPU[idObj]->UnitHWND)
						{
							HWND ret=GetNextDlgGroupItem(UnitHWND,GPU[idObj]->UnitHWND, bPrevious);
							int i;
							for(i=0;(UINT)i<(*GPU)->m_NGPUNIT;i++)
								if (GPU[i] && GPU[i]->UnitHWND==ret)
									{	retint=i;	break;	}
						}
					}
					break;
				case 72: /*DrawMenuBar*/	retint=DrawMenuBar(UnitHWND); break;

				case 73: /*PrintWnd*/
					{
						WndPrint tmp(UnitHWND);
						SetForegroundWindow(UnitHWND);
						int Dlg=0,Paper=-12345,Orient=-12345;
						tmp.TranslateParam(pos, Dlg,Paper,Orient);
						tmp.PrintWindowToDC(Dlg,Paper,Orient);
					}
					break;
				case 74: /*TrackMouseEvent*/
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						char *nm[4]={"CANCEL","HOVER","LEAVE","NONCLIENT",};
						int ufl[4]={TME_CANCEL,TME_HOVER,TME_LEAVE,TME_NONCLIENT,};
						_strupr(pos333);
						TRACKMOUSEEVENT te={0};
						te.cbSize=sizeof(te);

						int i;
						for(i=0;i<4;i++)
							if (strstr(pos333,nm[i]))	te.dwFlags|=ufl[i];

						te.hwndTrack=UnitHWND;
						te.dwHoverTime=atoipos;
						_TrackMouseEvent(&te);
						delete[] pos333;
					}
					break;
				case 75:/*HtmlHelp*///File,Command,Data
					if(UnitHWND)
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						char *pszFile=pos333;
						char *pszComand=pos333;
						char *pszData=pos333;
						UINT uCommand=HH_DISPLAY_TOPIC;
						pszComand=strchr(pos333,',');
						if (pszComand) *(pszComand++)=0;
						else pszComand="";
						pszData=strchr(pszComand,',');
						if (pszData) *(pszData++)=0;
						else pszData="";

						UINT dwData=0;


						const UINT uCmdArr[32]={
							HH_DISPLAY_TOPIC,HH_HELP_FINDER,HH_DISPLAY_TOC,HH_DISPLAY_INDEX,HH_DISPLAY_SEARCH,
							HH_SET_WIN_TYPE,HH_GET_WIN_TYPE,HH_GET_WIN_HANDLE,HH_ENUM_INFO_TYPE,HH_SET_INFO_TYPE,
							HH_SYNC,HH_RESERVED1,HH_RESERVED2,HH_RESERVED3,HH_KEYWORD_LOOKUP,
							HH_DISPLAY_TEXT_POPUP,HH_HELP_CONTEXT,HH_TP_HELP_CONTEXTMENU,HH_TP_HELP_WM_HELP,HH_CLOSE_ALL,
							HH_ALINK_LOOKUP,HH_GET_LAST_ERROR,HH_ENUM_CATEGORY,HH_ENUM_CATEGORY_IT,HH_RESET_IT_FILTER,
							HH_SET_INCLUSIVE_FILTER,HH_SET_EXCLUSIVE_FILTER,HH_INITIALIZE,HH_UNINITIALIZE,HH_PRETRANSLATEMESSAGE,
							HH_SET_GLOBAL_PROPERTY,HH_SET_QUERYSERVICE};
						const char *pszCmdArr[32]={
							"HH_DISPLAY_TOPIC","HH_HELP_FINDER","HH_DISPLAY_TOC","HH_DISPLAY_INDEX","HH_DISPLAY_SEARCH",
							"HH_SET_WIN_TYPE","HH_GET_WIN_TYPE","HH_GET_WIN_HANDLE","HH_ENUM_INFO_TYPE","HH_SET_INFO_TYPE",
							"HH_SYNC","HH_RESERVED1","HH_RESERVED2","HH_RESERVED3","HH_KEYWORD_LOOKUP",
							"HH_DISPLAY_TEXT_POPUP","HH_HELP_CONTEXT","HH_TP_HELP_CONTEXTMENU","HH_TP_HELP_WM_HELP","HH_CLOSE_ALL",
							"HH_ALINK_LOOKUP","HH_GET_LAST_ERROR","HH_ENUM_CATEGORY","HH_ENUM_CATEGORY_IT","HH_RESET_IT_FILTER",
							"HH_SET_INCLUSIVE_FILTER","HH_SET_EXCLUSIVE_FILTER","HH_INITIALIZE","HH_UNINITIALIZE","HH_PRETRANSLATEMESSAGE",
							"HH_SET_GLOBAL_PROPERTY","HH_SET_QUERYSERVICE",};

							UINT i;
						for(i=0;i<32;i++)
							if(_stricmp(pszCmdArr[i],pszComand)==0)
							{
								uCommand=uCmdArr[i];
								break;
							}

						switch(uCommand)
						{
	//					case HH_DISPLAY_TOPIC:
						case HH_HELP_FINDER:			//WinHelp equivalent
						case HH_DISPLAY_TOC:
						case HH_HELP_CONTEXT:			// display mapped numeric value in dwData
							dwData=atoi(pszData);
							retint=(UINT)HtmlHelp(GetDesktopWindow(),pszFile,uCommand,dwData);
							break;
						case HH_GET_WIN_HANDLE:
						case HH_DISPLAY_INDEX:
						case HH_SYNC:
							dwData=(UINT)pszData;
							retint=(UINT)HtmlHelp(GetDesktopWindow(),pszFile,uCommand,dwData);
							break;
						case HH_CLOSE_ALL:				// close all windows opened directly or indirectly by the caller
						case HH_RESET_IT_FILTER:		// Clear the info type filter of all info types.
							dwData=0;
							retint=(UINT)HtmlHelp(GetDesktopWindow(),pszFile,uCommand,dwData);
							break;
						case HH_DISPLAY_SEARCH:
							{
								HH_FTS_QUERY hhq={0};
								dwData=(UINT)&hhq;
								hhq.cbStruct=sizeof(hhq);
								char strtmp[2000];*strtmp=0;
								m_LastScanf=sscanf(pszData,"%d,%d,%d,%d,%d,%s",&hhq.fUniCodeStrings,&hhq.fStemmedSearch,&hhq.fTitleOnly,&hhq.fExecute,&hhq.iProximity,strtmp);
								char *postmp=strchr(strtmp,',');
								if (postmp) *(postmp++)=0; else postmp="";
								hhq.pszWindow=strtmp;
								hhq.pszSearchQuery=postmp;
								retint=(UINT)HtmlHelp(GetDesktopWindow(),pszFile,uCommand,dwData);
							}
							break;
						case HH_SET_WIN_TYPE:
						case HH_GET_WIN_TYPE:
							{
								HH_WINTYPE hhwt={0};
								hhwt.cbStruct=sizeof(hhwt);
								hhwt.fsValidMembers=0;
								dwData=(UINT)&hhwt;

								const char *memb[26]={
									"UNICODE=","TYPE=","CAPTION=","STYLES=","EXSTYLES=",
									"WINDOWPOS=","SHOWSTATE=","NAVWIDTH=","TOC=","INDEX=",
									"FILE=","HOME=","TOOLBARFLAGS=","NOTEXPANDED=","NAVTYPE=",
									"TABPOS=","NOTIFY=","ORDER=","HISTORY=","JUMP1=",
									"JUMP2=","JUMPURL1=","JUMPURL2=","MINSIZE=","WINPROP=",
									"RCHTML=",
									};
								char *posdata[26]={
									NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
									NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
									NULL,NULL,NULL,NULL,NULL,
									NULL,
								};

								UINT nPar;
								for(nPar=0;nPar<26;nPar++)
									posdata[nPar]=strstr(pszData,memb[nPar]);

								for(nPar=0;nPar<26;nPar++)
									if (posdata[nPar])
									{
										char *pos2=strchr(posdata[nPar],'=');
										if (pos2++)
										{
											char *pos3=strchr(posdata[nPar],';');
											if (pos3) *pos3=0;
											switch(nPar)
											{
											case 0: /*UNICODE*/
												hhwt.fsValidMembers|=1;
												hhwt.fUniCodeStrings=atoi(pos2);
												break;
											case 1: /*TYPE*/
												hhwt.fsValidMembers|=HHWIN_PARAM_INFOTYPES;
												hhwt.pszType=pos2;
												break;
											case 2: /*CAPTION*/
												hhwt.pszCaption=pos2;
												break;
											case 3: /*STYLES*/
												{
													hhwt.fsValidMembers|=HHWIN_PARAM_STYLES;
													for(i=0;i<N_WND_STYLES;i++)
														if (strstr(pos333,aWndStyleName[i]))
															hhwt.dwStyles|=aWndStyleUINT[i];
												}
												break;
											case 4: /*EXSTYLES*/
												{
													hhwt.fsValidMembers|=HHWIN_PARAM_EXSTYLES;
													for(i=0;i<N_WND_EX_STYLES;i++)
														if (strstr(pos333,aWndExStyleName[i]))
															hhwt.dwExStyles|=aWndExStyleUINT[i];
												}
												break;
											case 5: /*WINDOWPOS*/
												hhwt.fsValidMembers|=HHWIN_PARAM_RECT;
												m_LastScanf=sscanf(pos2,"%d,%d,%d,%d",&hhwt.rcWindowPos.left,&hhwt.rcWindowPos.top,&hhwt.rcWindowPos.right,&hhwt.rcWindowPos.bottom);
												break;
											case 6: /*SHOWSTATE*/
												{
													hhwt.fsValidMembers|=HHWIN_PARAM_SHOWSTATE;
													_strupr(pos333);
													for(i=0; i < N_WND_SHOW_STYLES && strstr(pos333,aWndShowStyleName[i])==NULL; i++);
													if (i<N_WND_SHOW_STYLES) hhwt.nShowState=aWndShowStyleUINT[i];
												}
												break;
											case 7: /*NAVWIDTH*/
												hhwt.fsValidMembers|=HHWIN_PARAM_NAV_WIDTH;
												hhwt.iNavWidth=atoi(pos2);
												break;
											case 8: /*TOC*/
												hhwt.pszToc=pos2;
												break;
											case 9: /*INDEX*/
												hhwt.pszIndex=pos2;
												break;
											case 10:/*FILE*/
												hhwt.pszFile=pos2;
												break;
											case 11:/*HOME*/
												hhwt.pszHome=pos2;
												break;
											case 12:/*TOOLBARFLAGS*/
												{
													UINT uprop[22]=
													{
														HHWIN_BUTTON_EXPAND,HHWIN_BUTTON_BACK,HHWIN_BUTTON_FORWARD,HHWIN_BUTTON_STOP,HHWIN_BUTTON_REFRESH,
														HHWIN_BUTTON_HOME,HHWIN_BUTTON_BROWSE_FWD,HHWIN_BUTTON_BROWSE_BCK,HHWIN_BUTTON_NOTES,HHWIN_BUTTON_CONTENTS,
														HHWIN_BUTTON_SYNC,HHWIN_BUTTON_OPTIONS,HHWIN_BUTTON_PRINT,HHWIN_BUTTON_INDEX,HHWIN_BUTTON_SEARCH,
														HHWIN_BUTTON_HISTORY,HHWIN_BUTTON_FAVORITES,HHWIN_BUTTON_JUMP1,HHWIN_BUTTON_JUMP2,HHWIN_BUTTON_ZOOM,
														HHWIN_BUTTON_TOC_NEXT,HHWIN_BUTTON_TOC_PREV,
													};
													char *cprop[22]=
													{
														"_EXPAND","_BACK","_FORWARD","_STOP","_REFRESH",
														"_HOME","_BROWSE_FWD","_BROWSE_BCK","_NOTES","_CONTENTS",
														"_SYNC","_OPTIONS","_PRINT","_INDEX","_SEARCH",
														"_HISTORY","_FAVORITES","_JUMP1","_JUMP2","_ZOOM",
														"_TOC_NEXT","_TOC_PREV",
													};

													hhwt.fsValidMembers|=HHWIN_PARAM_TB_FLAGS;
													_strupr(pos2);
													UINT nProp;
													for(nProp=0;nProp<22;i++)
														if (strstr(pos2,cprop[nProp]))
															hhwt.fsToolBarFlags|=uprop[nProp];
												}
												break;
											case 13:/*NOTEXPANDED*/
												hhwt.fsValidMembers|=HHWIN_PARAM_EXPANSION;
												hhwt.fNotExpanded=atoi(pos2);
												break;
											case 14:/*NAVTYPE*/
												hhwt.fsValidMembers|=HHWIN_PARAM_CUR_TAB;
												hhwt.curNavType=strstr(pos2,"TOC")?HHWIN_NAVTYPE_TOC:HHWIN_NAVTYPE_INDEX;
												break;
											case 15:/*TABPOS*/
												hhwt.fsValidMembers|=HHWIN_PARAM_TABPOS;
												hhwt.tabpos=strstr(pos2,"TOP")?HHWIN_NAVTAB_TOP:strstr(pos2,"BOT")?HHWIN_NAVTAB_BOTTOM:HHWIN_NAVTAB_LEFT;
												break;
											case 16:/*NOTIFY*/
												hhwt.idNotify=atoi(pos2);
												break;
											case 17:/*ORDER*/
												{
													char *ppos[20]=
														{
															"CONTENTS","INDEX","SEARCH","FAVORITES","HISTORY","AUTHOR","TAB6","TAB7","TAB8","TAB9",
															"TAB10","TAB11","TAB12","TAB13","TAB14","TAB15","TAB16","TAB17","TAB18","TAB19",
														};
													hhwt.fsValidMembers|=HHWIN_PARAM_TABORDER;

													hhwt.tabOrder[HH_TAB_CONTENTS] = 1;
													UINT ntab=0;
													_strupr(pos2);

													pos3=pos2;
													while(pos3 && ntab<HH_MAX_TABS)
													{
														char *pos4=strchr(pos3,',');
														if (pos4) *(pos4++)=0;

														for(i=0; i<HH_MAX_TABS; i++)
															if (strcmp(ppos[i],pos3)==0)
															{
																hhwt.tabOrder[i]=ntab++;
																break;
															}

														pos3=pos4;
													}
												}
												break;
											case 18:/*HISTORY*/
												hhwt.fsValidMembers|=HHWIN_PARAM_HISTORY_COUNT;
												hhwt.cHistory=atoi(pos2);
												break;
											case 19:/*JUMP1*/
												hhwt.pszJump1=pos2;
												break;
											case 20:/*JUMP2*/
												hhwt.pszJump2=pos2;
												break;
											case 21:/*JUMPURL1*/
												hhwt.pszUrlJump1=pos2;
												break;
											case 22:/*JUMPURL2*/
												hhwt.pszUrlJump2=pos2;
												break;
											case 23:/*MINSIZE*/
												m_LastScanf=sscanf(pos2,"%d,%d,%d,%d",&hhwt.rcMinSize.left,&hhwt.rcMinSize.top,&hhwt.rcMinSize.right,&hhwt.rcMinSize.bottom);
												break;
											case 24:/*WINPROP*/
												{
													UINT uprop[29]=
													{
														HHWIN_PROP_AUTO_SYNC,HHWIN_PROP_CHANGE_TITLE,HHWIN_PROP_NAV_ONLY_WIN,HHWIN_PROP_NODEF_EXSTYLES,HHWIN_PROP_NODEF_STYLES,
														HHWIN_PROP_NOTB_TEXT,HHWIN_PROP_NOTITLEBAR,HHWIN_PROP_NO_TOOLBAR,HHWIN_PROP_ONTOP,HHWIN_PROP_POST_QUIT,
														HHWIN_PROP_TAB_ADVSEARCH,HHWIN_PROP_TAB_SEARCH,HHWIN_PROP_TAB_FAVORITES,HHWIN_PROP_TRACKING,HHWIN_PROP_TRI_PANE,
														HHWIN_PROP_USER_POS,HHWIN_PROP_TAB_AUTOHIDESHOW,HHWIN_PROP_TAB_HISTORY,HHWIN_PROP_MENU,HHWIN_PROP_TAB_CUSTOM1,
														HHWIN_PROP_TAB_CUSTOM2,HHWIN_PROP_TAB_CUSTOM3,HHWIN_PROP_TAB_CUSTOM4,HHWIN_PROP_TAB_CUSTOM5,HHWIN_PROP_TAB_CUSTOM6,
														HHWIN_PROP_TAB_CUSTOM7,HHWIN_PROP_TAB_CUSTOM8,HHWIN_PROP_TAB_CUSTOM9,HHWIN_TB_MARGIN,
													};
													char *cprop[29]=
													{
														"AUTO_SYNC","CHANGE_TITLE","NAV_ONLY_WIN","NODEF_EXSTYLES","NODEF_STYLES",
														"NOTB_TEXT","NOTITLEBAR","NO_TOOLBAR","ONTOP","POST_QUIT",
														"TAB_ADVSEARCH","TAB_SEARCH","TAB_FAVORITES","TRACKING","TRI_PANE",
														"USER_POS","TAB_AUTOHIDESHOW","TAB_HISTORY","MENU","TAB_CUSTOM1",
														"TAB_CUSTOM2","TAB_CUSTOM3","TAB_CUSTOM4","TAB_CUSTOM5","TAB_CUSTOM6",
														"TAB_CUSTOM7","TAB_CUSTOM8","TAB_CUSTOM9","TB_MARGIN",
													};

													hhwt.fsValidMembers|=HHWIN_PARAM_PROPERTIES;
													_strupr(pos2);
													UINT nProp;
													for(nProp=0;nProp<29;i++)
														if (strstr(pos2,cprop[nProp]))
															hhwt.fsWinProperties|=uprop[nProp];
												}
												break;
											case 25:/*RCHTML*/
												m_LastScanf=sscanf(pos2,"%d,%d,%d,%d",&hhwt.rcHTML.left,&hhwt.rcHTML.top,&hhwt.rcHTML.right,&hhwt.rcHTML.bottom);
												break;
											}
										}
									}
								retint=(UINT)HtmlHelp(GetDesktopWindow(),pszFile,uCommand,dwData);
							}
							break;
						case HH_KEYWORD_LOOKUP:
						case HH_ALINK_LOOKUP:			// ALink version of HH_KEYWORD_LOOKUP
							{
								HH_AKLINK hhq={0};
								dwData=(UINT)&hhq;
								hhq.cbStruct=sizeof(hhq);
								char *postmp=pszData;
								for(i=0;i<6 && postmp;i++)
								{
									char *pos2=strchr(postmp,',');
									if (pos2) *(pos2++)=0;
									switch(i)
									{
									case 0:	hhq.fIndexOnFail=atoi(postmp);				break;
									case 1:	if (*postmp!=0)	hhq.pszKeywords	=postmp;	break;
									case 2:	if (*postmp!=0)	hhq.pszUrl		=postmp;	break;
									case 3:	if (*postmp!=0)	hhq.pszMsgText	=postmp;	break;
									case 4:	if (*postmp!=0)	hhq.pszMsgTitle	=postmp;	break;
									case 5:	if (*postmp!=0)	hhq.pszWindow	=postmp;	break;
									}
									postmp=pos2;
								}
								retint=(UINT)HtmlHelp(GetDesktopWindow(),pszFile,uCommand,dwData);
							}
							break;
						case HH_DISPLAY_TEXT_POPUP:		// display string resource id or text in a popup window
							{
								HH_POPUP hhq={0};
								dwData=(UINT)&hhq;
								hhq.cbStruct=sizeof(hhq);
								char *strtmp=new char [(int)strlen(pszData)+50];*strtmp=0;
								UINT r=0,g=0,b=0,r1=0,g1=0,b1=0;
								m_LastScanf=sscanf(pszData,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s",
									&(hhq.pt.x),&(hhq.pt.y),
									&(hhq.rcMargins.left),&(hhq.rcMargins.top),&(hhq.rcMargins.right),&(hhq.rcMargins.bottom),
									&r,&g,&b,&r1,&g1,&b1,strtmp);
								hhq.clrForeground=RGB(r,g,b);
								hhq.clrBackground=RGB(r1,g1,b1);
								char *postmp=strchr(strtmp,',');
								if (postmp) *(postmp++)=0; else postmp="";
								hhq.pszText=strtmp;
								hhq.pszFont=postmp;
								retint=(UINT)HtmlHelp(GetDesktopWindow(),pszFile,uCommand,dwData);
								delete[] strtmp;
							}
							break;
						case HH_TP_HELP_CONTEXTMENU:	// text popup help, same as WinHelp HELP_CONTEXTMENU
						case HH_TP_HELP_WM_HELP:		// text popup help, same as WinHelp HELP_WM_HELP
							{
								DWORD *ids=new DWORD[256];
								dwData=(UINT)ids;
								char *postmp=pszData;
								for(i=0;i<250 && postmp;i++)
								{
									char *pos2=strchr(postmp,',');
									if (pos2) pos2++;
									ids[i]=atoi(postmp);
									postmp=pos2;
								}
								ids[i++]=0;
								ids[i]=0;
								retint=(UINT)HtmlHelp(GetDesktopWindow(),pszFile,uCommand,dwData);
								delete[] ids;
							}
							break;
						case HH_GET_LAST_ERROR:			// not currently implemented // See HHERROR.h
							if (oStr)
							{
								USES_CONVERSION; // For Unicode to ANSI string conversion
								typedef struct tagHH_LAST_ERROR
								{
									 int      cbStruct ;
									 HRESULT  hr ;
									 BSTR     description ;
								} HH_LAST_ERROR ;



								HH_LAST_ERROR lasterror ;
								HWND hwnd = HtmlHelp(GetDesktopWindow(),NULL,HH_GET_LAST_ERROR,reinterpret_cast<DWORD>(&lasterror));

								if (hwnd != 0 && FAILED(lasterror.hr) && lasterror.description)
								{
									CString csTmp(lasterror.description);
									::SysFreeString(lasterror.description) ;
									strcpy(oStr,csTmp);
								}
							}
							break;
						case HH_INITIALIZE:				// Initializes the help system.
								HtmlHelp(GetDesktopWindow(),NULL,uCommand,(UINT)&retint); break;
						case HH_UNINITIALIZE:			// Uninitializes the help system.
								HtmlHelp(GetDesktopWindow(),NULL,uCommand,atoi(pszData)); break;

						// Not Supported
						case HH_ENUM_INFO_TYPE:			//GetInfotypename,callrepeatedlytoenumerate,-1atend
						case HH_SET_INFO_TYPE:			//AddInfotypetofilter.
						case HH_RESERVED1:
						case HH_RESERVED2:
						case HH_RESERVED3:
						case HH_ENUM_CATEGORY:			// Get category name, call repeatedly to enumerate, -1 at end
						case HH_ENUM_CATEGORY_IT:		// Get category info type members, call repeatedly to enumerate, -1 at end
						case HH_SET_INCLUSIVE_FILTER:	// set inclusive filtering method for untyped topics to be included in display
						case HH_SET_EXCLUSIVE_FILTER:	// set exclusive filtering method for untyped topics to be excluded from display
						case HH_SET_QUERYSERVICE:		// Set the Host IQueryService interface
						case HH_SET_GLOBAL_PROPERTY:	//Setaglobalproperty.(NULL,NULL,HH_GPROP)
						case HH_PRETRANSLATEMESSAGE:	// Pumps messages. (NULL, NULL, MSG*).
						break;
						}
						delete[] pos333;
					}
					break;
				case 76: /*WihHelp*/
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						char *pszFile=pos333;
						char *pszComand=pos333;
						char *pszData=pos333;
						UINT uCommand=HH_DISPLAY_TOPIC;
						pszComand=strchr(pos333,',');
						if (pszComand) *(pszComand++)=0;
						else pszComand="";
						pszData=strchr(pszComand,',');
						if (pszData) *(pszData++)=0;
						else pszData="";

						UINT dwData=0;


						const UINT uCmdArr[21]={
							HELP_CONTEXT,HELP_QUIT,HELP_INDEX,HELP_CONTENTS,HELP_HELPONHELP,
							HELP_SETINDEX,HELP_SETCONTENTS,HELP_CONTEXTPOPUP,HELP_FORCEFILE,HELP_KEY,
							HELP_COMMAND,HELP_PARTIALKEY,HELP_MULTIKEY,HELP_SETWINPOS,HELP_CONTEXTMENU,
							HELP_FINDER,HELP_WM_HELP,HELP_SETPOPUP_POS,HELP_TCARD,HELP_TCARD_DATA,
							HELP_TCARD_OTHER_CALLER,};
						const char *pszCmdArr[21]={
							"HELP_CONTEXT","HELP_QUIT","HELP_INDEX","HELP_CONTENTS","HELP_HELPONHELP",
							"HELP_SETINDEX","HELP_SETCONTENTS","HELP_CONTEXTPOPUP","HELP_FORCEFILE","HELP_KEY",
							"HELP_COMMAND","HELP_PARTIALKEY","HELP_MULTIKEY","HELP_SETWINPOS","HELP_CONTEXTMENU",
							"HELP_FINDER","HELP_WM_HELP","HELP_SETPOPUP_POS","HELP_TCARD","HELP_TCARD_DATA",
							"HELP_TCARD_OTHER_CALLER",};

							UINT i;
						for(i=0;i<21;i++)
							if(_stricmp(pszCmdArr[i],pszComand)==0)
							{
								uCommand=uCmdArr[i];
								break;
							}

						switch(uCommand)
						{
						case HELP_CONTEXT:
						case HELP_CONTEXTPOPUP:
						case HELP_SETCONTENTS:
							dwData=atoi(pszData);
							retint=(UINT)WinHelp(GetDesktopWindow(),pszFile,uCommand,dwData);
							break;
						case HELP_COMMAND:
						case HELP_KEY:
						case HELP_PARTIALKEY:
							dwData=(UINT)pszData;
							retint=(UINT)WinHelp(GetDesktopWindow(),pszFile,uCommand,dwData);
							break;
	//					case HELP_CONTENTS:
						case HELP_FINDER:
						case HELP_FORCEFILE:
						case HELP_HELPONHELP:
						case HELP_INDEX:
						case HELP_QUIT:
							dwData=0;
							retint=(UINT)WinHelp(GetDesktopWindow(),pszFile,uCommand,dwData);
							break;
						case HELP_CONTEXTMENU:
							{
								DWORD *ids=new DWORD[256];
								dwData=(UINT)ids;
								char *postmp=pszData;
								for(i=0;i<250 && postmp;i++)
								{
									char *pos2=strchr(postmp,',');
									if (pos2) pos2++;
									ids[i]=atoi(postmp);
									postmp=pos2;
								}
								ids[i++]=0;
								ids[i]=0;
								retint=(UINT)WinHelp(GetDesktopWindow(),pszFile,uCommand,dwData);
								delete[] ids;
							}
							break;
						case HELP_MULTIKEY:
							{
								MULTIKEYHELP *mkh;
								UINT cb;
								char *postmp=strchr(pszData,',');
								if (postmp++==NULL) postmp="";
								cb=sizeof(MULTIKEYHELP) + (int)strlen(postmp);
								HGLOBAL hglblmkh;
								hglblmkh = GlobalAlloc(GHND, (DWORD) cb);
								if (hglblmkh != NULL)
								{
									mkh = (MULTIKEYHELP FAR*) GlobalLock(hglblmkh);
									dwData=(UINT)mkh;
									mkh->mkKeylist=atoi(pszData);
									mkh->mkSize=cb;
									lstrcpy(mkh->szKeyphrase, postmp);
									retint=(UINT)WinHelp(GetDesktopWindow(),pszFile,uCommand,dwData);
									GlobalUnlock(hglblmkh);
									GlobalFree(hglblmkh);
								}
							}
							break;
						case HELP_SETPOPUP_POS:
							{
								int posx=0,posy=0;
								m_LastScanf=sscanf(pszData,"%d,%d",&posx,&posy);
								retint=(UINT)WinHelp(GetDesktopWindow(),pszFile,uCommand,MAKELONG(posx,posy));
							}
							break;
						case HELP_SETWINPOS:
							{
								HELPWININFO *hmi;
								UINT cb;
								cb=sizeof(HELPWININFO) + (int)strlen(pszData);
								HGLOBAL hglblmkh;
								hglblmkh = GlobalAlloc(GHND, (DWORD) cb);
								if (hglblmkh != NULL)
								{
									hmi = (HELPWININFO FAR*) GlobalLock(hglblmkh);
									dwData=(UINT)hmi;
									char *tmpstr=new char [(int)strlen(pszData)];
									m_LastScanf=sscanf(pszData,"%d,%d,%d,%d,%d,%s",&hmi->x,&hmi->y,&hmi->dx,&hmi->dy,&hmi->wMax,tmpstr);
									hmi->wStructSize=cb;
									lstrcpy(hmi->rgchMember,tmpstr);
									retint=(UINT)WinHelp(GetDesktopWindow(),pszFile,uCommand,dwData);
									GlobalUnlock(hglblmkh);
									GlobalFree(hglblmkh);
									delete[] tmpstr;
								}
							}
							break;
						}
						delete[] pos333;
					}
					break;

				case 77: /*BeginWaitCursor*/
	//				if (m_WaitCursor==NULL) m_WaitCursor=new CWaitCursor;
					if (!GPC.m_bWaitCursor)	CWnd::FromHandle(UnitHWND)->BeginWaitCursor();
					GPC.m_bWaitCursor=TRUE;
					break;
				case 78: /*EndWaitCursor*/
					if (GPC.m_bWaitCursor) CWnd::FromHandle(UnitHWND)->EndWaitCursor();
					GPC.m_bWaitCursor=FALSE;
	//				if (m_WaitCursor) {delete m_WaitCursor;m_WaitCursor=NULL;}
					break;
				case 79: /*SetFocusNextTab*/
					{
						HWND tmp=::GetFocus();
						retint=-1;
						if (tmp)
						{
							int n=atoi(pos);
							if (n>0) while(n-->0) tmp=::GetNextDlgTabItem(UnitHWND,tmp,FALSE);
							else  while(n++<0) tmp=::GetNextDlgTabItem(UnitHWND,tmp,TRUE);
							if (tmp) SetFocus(tmp);
						}
					}
					break;
				case 80: /*SetCursor*/
					SetCursor(GPC.CursorArr.GetCursor(pos)->GetHCURSOR());
					break;
				case 81: /*SetClassCursor*/
					SetClassLong(UnitHWND,GCL_HCURSOR,(long)GPC.CursorArr.GetCursor(pos)->GetHCURSOR());
					break;
				case 82: /*GetClassCursor*/
					{
						HCURSOR hcur;
						hcur=(HCURSOR)GetClassLong(UnitHWND,GCL_HCURSOR);
						const char *tmpName=GPC.CursorArr.GetCursorNameByHCUR(hcur);
						if (tmpName==NULL || *tmpName==0)
						{
							CString tmps;
							tmps.Format("%ld",(DWORD)hcur);
							GPCursor *tmpCur=GPC.CursorArr.CreateCursor(tmps);
							if (tmpCur) tmpCur->SetHCURSOR(hcur);
							tmpName=GPC.CursorArr.GetCursorNameByHCUR(hcur);
						}
						if (oStr) strcpy(oStr,tmpName);
					}
					break;
				case 83: /*RestoreClassCursor*/
					SetClassLong(UnitHWND,GCL_HCURSOR,(long)m_OldHCURSOR);
					break;
				case 84: /*SetDragName*/
					m_DragName=pos;
					break;

				case 85: /*SetDropName*/
				case 86: /*AddDropName*/
				case 87: /*DeleteDropName*/
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						char *pos1=pos333;
						switch(nfunc)
						{
						case 85: /*SetDropName*/
							if (m_DropNamesArray) m_DropNamesArray->ResetArray();
							break;
						case 86: /*AddDropName*/
						case 87: /*DeleteDropName*/
							break;
						}
						while(pos1 && *pos1)
						{
							char *pos2=pos1;
							while(*pos2 && *pos2!=GPC.DelimiterIn1) pos2++;

							if (*pos2) *pos2=0;
							else pos2=NULL;

							switch(nfunc)
							{
							case 85: /*SetDropName*/
							case 86: /*AddDropName*/
								if (!m_DropNamesArray)
								{
									m_DropNamesArray=new GP_RarefiedArr<CString>;
									m_DropNamesArray->SetInitValue(CString(""));
								}
								if (m_DropNamesArray) m_DropNamesArray->AddItem(pos1);
								break;
							case 87: /*DeleteDropName*/
								if (m_DropNamesArray) m_DropNamesArray->RemoveItemByVal(pos1);
								break;
							}
							pos1=pos2;
							if (pos1) pos1++;
						}
						delete[] pos333;
					}
					break;
				case 88: /*SetDropDelay*/
					m_nDelayInterval = atoipos;
					retint=m_nDelayInterval;
					break;
				case 89: /*SetDropScrollInterval*/
					retint=m_nScrollInterval;
					m_nScrollInterval = atoipos;
					break;
				case 90: /*SetDropScrollMargin*/
					retint=m_nScrollMargin;
					m_nScrollMargin = atoipos;
					break;
				case 91: /*SetNextParent*/
					GPC.NextParentFromOLE=UnitHWND;
					break;
				case 92: /*SizerAdd*/ //"Name,Type,Size,MinParentSize,MaxParentSize"
					if (!m_SizerArray)
						m_SizerArray=new CGPWndSizerArr(UnitHWND);
					retint=(int)m_SizerArray->AddSizer(pos);
					break;
				case 93: /*SizerRemove*/ //"Name"
					if (!m_SizerArray)
						m_SizerArray=new CGPWndSizerArr(UnitHWND);
					retint=(int)m_SizerArray->RemoveSizer(pos);
					break;
				case 94: /*SizerSet*/ //"Name,Type,Size,MinParentSize,MaxParentSize"
					if (!m_SizerArray)
						m_SizerArray=new CGPWndSizerArr(UnitHWND);
					retint=(int)m_SizerArray->SetSizer(pos);
					break;
				case 95: /*SetWindowText*/
					switch(UnitType)
					{
					case UT_CONTROL:
						{
							CString tmps=pos;
							BSTR tmpBSTR=tmps.AllocSysString();
							retint=::SendMessage(UnitHWND,GPM_AX_SETWINDOWTEXT,0,(LPARAM)(&tmpBSTR));
							::SysFreeString(tmpBSTR);
						}
						break;
					default:
						retint=::SetWindowText(UnitHWND,pos);
						break;
					}
					break;
				case 96: /*SizerSetIcon*/
					if (m_SizerArray)
						retint=(int)m_SizerArray->SetSizerIcon(pos);
					break;
				case 97: /*SizerSetRgn*/
					if (m_SizerArray)
						retint=(int)m_SizerArray->SetSizerRgn(pos);
					break;
				case 98: /*SizerSetBrush*/
					if (m_SizerArray)
						retint=(int)m_SizerArray->SetSizerBrush(pos);
					break;
				case 99: /*KeyDown*/
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						char *pos1=pos333;
						if (*pos1)
						{
							DWORD lParam=0,wParam=0;
							while(*pos1==' ') pos1++;
							m_LastScanf=sscanf(pos1,*pos1=='&'?"&%X":"%ld",lParam);
							{
								UINT i=0;
								char *tmps=new char [(int)strlen(pos1)+10];
								strcpy(tmps,pos1);
								_strupr(tmps);
								strcat(tmps,"|");
								if (*pos1)
									for(i=0;i<GP_HotKey::nTypeHotkey && strstr(tmps,GP_HotKey:: aVKName[i])==NULL;i++);

								if (i<GP_HotKey::nTypeHotkey || *pos1==0)
								{
									UINT j;
									for(j=0;j<GP_HotKey::nTypeModifiers && strstr(tmps,GP_HotKey::aVKMODName[j])==NULL;j++);
									if (*pos1) wParam=GP_HotKey:: aVKUINT[i];
									if (j<GP_HotKey::nTypeModifiers) wParam|=GP_HotKey::aVKMODUINT[j];
									::SendMessage(UnitHWND,WM_KEYDOWN,wParam,lParam);
								}
								delete[] tmps;
							}
						}
						delete[] pos333;
					}
					break;
				case 100: /*SetWindowTextEx*/
					switch(UnitType)
					{
					case UT_COMBOBOX:
						if ((((GPComboBoxEx *)UnitPtr)->GetStyle()&CBS_DROPDOWNLIST)==CBS_DROPDOWNLIST)
						{
							int ind=((GPComboBoxEx *)UnitPtr)->FindStringExact(0,pos);
							if (ind!=CB_ERR)
								((GPComboBoxEx *)UnitPtr)->SetCurSel(ind);
						}
						else
							((GPComboBoxEx *)UnitPtr)->SetWindowText(pos);
						break;
					case UT_COMBOBOXEX:
						if ((((GPComboBox *)UnitPtr)->GetStyle()&CBS_DROPDOWNLIST)==CBS_DROPDOWNLIST)
						{
							int ind=((GPComboBox *)UnitPtr)->FindStringExact(0,pos);
							if (ind!=CB_ERR)
								((GPComboBox *)UnitPtr)->SetCurSel(ind);
						}
						else
							((GPComboBox *)UnitPtr)->SetWindowText(pos);
						break;
					case UT_STATUSBARCTRL:
						((GPStatusBarCtrl *)UnitPtr)->SetText(pos,0,0);
						break;
					case UT_STATUSBAR:
						((GPStatusBar *)UnitPtr)->SetPaneText(0,pos);
						break;
					case UT_DATETIMECTRL:
						{
							char *tmp=new char [(int)strlen(pos)+50];
							strcpy(tmp,"SetTime ");
							strcat(tmp,pos);
							char *tmppos=tmp;
							while(*tmppos)
							{
								if (*tmppos>'9' || *tmppos<'0') *tmppos=',';
								tmppos++;
							}
							strcat(tmp,",0,0,0,0,0,0,0,0");
							retint=((GPDateTimeCtrl*)UnitPtr)->DoMethod(tmp,oStr);
							delete[] tmp;
						}
						break;
					case UT_MONTHCAL:
						{
							char *tmp=new char [(int)strlen(pos)+50];
							strcpy(tmp,"SetTime ");
							strcat(tmp,pos);
							char *tmppos=tmp;
							while(*tmppos)
							{
								if (*tmppos>'9' || *tmppos<'0') *tmppos=',';
								tmppos++;
							}
							strcat(tmp,",0,0,0,0,0,0,0,0");
							retint=((GPMonthCalCtrl*)UnitPtr)->DoMethod(tmp,oStr);
							delete[] tmp;
						}
						break;
					case UT_TREECTRL:
						{
							HTREEITEM ti=((GPTree*)UnitPtr)->GetSelectedItem();
							if (ti)	retint=((GPTree*)UnitPtr)->SetItemText(ti,pos);
						}
						break;
					case UT_TABCTRL:
						if ((retint=((GPTabCtrl*)UnitPtr)->GetCurSel())>=0)
						{
							char *pos333=new char [(int)strlen(pos)+2];
							strcpy(pos333,pos);
							TCITEM tci={0};
							tci.mask=TCIF_TEXT;
							tci.pszText=pos333;
							retint=((GPTabCtrl*)UnitPtr)->SetItem(retint,&tci);
							delete[] pos333;
						}
						break;
					case UT_SLIDER:		((GPSlider*)UnitPtr)->SetPos(atoipos);
						break;
					case UT_SPINBUTTON:
						retint=((GPSpinButton*)UnitPtr)->SetPos(atoipos);
						break;
					case UT_SCROLLBAR:
						retint=((GPScrollBar*)UnitPtr)->SetScrollPos(atoipos);
						break;
					case UT_PROGRESS:
						retint=((GPProgress*)UnitPtr)->SetPos(atoipos);
						break;
					case UT_LISTBOX:
						{
							char *tmp=new char [(int)strlen(pos)+50];
							strcpy(tmp,"SelectionDoMethod SetItemText ");
							strcat(tmp,pos);
							retint=((GPListBox*)UnitPtr)->DoMethod(tmp,oStr);
							delete[] tmp;
						}
						break;
					case UT_CHECKLISTBOX:
						{
							char *tmp=new char [(int)strlen(pos)+50];
							strcpy(tmp,"SelectionDoMethod SetItemText ");
							strcat(tmp,pos);
							retint=((GPChLBox*)UnitPtr)->DoMethod(tmp,oStr);
							delete[] tmp;
						}
						break;
					case UT_DRAGLISTBOX:
						{
							char *tmp=new char [(int)strlen(pos)+50];
							strcpy(tmp,"SelectionDoMethod SetItemText ");
							strcat(tmp,pos);
							retint=((GPDrLBox*)UnitPtr)->DoMethod(tmp,oStr);
							delete[] tmp;
						}
						break;
					case UT_LISTCTRL:
						{
							char *tmp=new char [(int)strlen(pos)+50];
							strcpy(tmp,"SelectionSetItemText ");
							strcat(tmp,pos);
							retint=((GPListCtr*)UnitPtr)->DoMethod(tmp,oStr);
							delete[] tmp;
						}
						break;
					case UT_FLEXGRID:
						((GPCMSFlexGrid *)UnitPtr)->SetText(pos);
						break;
					case UT_WEBBROWSER:
						retint=::SetWindowText(UnitHWND,pos);
						break;
					case UT_EDITOR:
					case UT_RTF:
					case UT_EDIT:
						((GPEdit *)UnitPtr)->SetSel(0,-1);
						((GPEdit *)UnitPtr)->ReplaceSel("");
						if ((::GetWindowLong(UnitHWND,GWL_STYLE)&ES_MULTILINE)==ES_MULTILINE)
						{
							char *pos333=new char [(int)strlen(pos)+2];
							strcpy(pos333,pos);
							char *pos2=pos333;
							while(*pos2)
							{
								if (*pos2==GPC.DelimiterIn1)	*pos2=1;
								pos2++;
							}
							char *tmp=new char [(int)strlen(pos333)+50];
							strcpy(tmp,"ReplaceSel ");
							strcat(tmp,pos333);
							retint=((GPListCtr*)UnitPtr)->DoMethod(tmp,oStr);
							delete[] tmp;
							delete[] pos333;
						}
						else	((GPEdit *)UnitPtr)->ReplaceSel(pos);
						break;
					case UT_CONTROL:
						{
							CString tmps=pos;
							BSTR tmpBSTR=tmps.AllocSysString();
							::SendMessage(UnitHWND,GPM_AX_SETWINDOWTEXTEX,0,(LPARAM)(&tmpBSTR));
							::SysFreeString(tmpBSTR);
						}
						break;
					case UT_STATIC:
						{
							char *pos333=new char [(int)strlen(pos)+2];
							strcpy(pos333,pos);
							char *pos2=pos333;
							while(pos2 && *pos2)
							{
								if (*pos2==1) *pos2=10;
								pos2++;
							}
							retint=::SetWindowText(UnitHWND,pos333);	
							delete[] pos333;
						}

						break;

						// standard
					case UT_FRAMEBAR:
					case UT_HEADER:
					case UT_DLGBAR:
					case UT_DRAW:
					case UT_BUTTON:
					case UT_ANIMAT:
					case UT_TOOLBARCTRL:
					case UT_TOOLBAR:
					case UT_DIALOGBAR:
					case UT_REBARCTRL:
					case UT_REBAR:
					case UT_MAINDLGSCR: /*cwnd*/
					case UT_ANIBUTTON:
					case UT_BBUTTON:
					case UT_ANISTATIC:
						retint=::SetWindowText(UnitHWND,pos);		break;
					}// end TypeUnit Switch
					break;
				case 101: /*SetParamDelimiter*/
					if (oStr) strcpy(oStr,m_ParamDelimiter);
					m_ParamDelimiter=pos;
					break;
				case 102: /*AutoSizingReinitMySize*/
					if (AUSI) AUSI->ReinitSize(UnitHWND);
					break;
				case 103: /*GetChildsText*/
					if (oStr)
					{
						UINT LastI=1;
						UINT mLevel=atoi(pos);
						char *resStr=oStr;
						UINT i;
						for(i=1;i<(*GPU)->m_NGPUNIT;i++)
							if (GPU[i] && GPU[i]->UnitHWND)
								switch(GPU[i]->UnitType)
								{
								case GPUnit::UT_MAINDLGSCR:
								case GPUnit::UT_DRAW:
								case GPUnit::UT_ANIMAT:
								case GPUnit::UT_WEBBROWSER:
								case GPUnit::UT_REBAR:
								case GPUnit::UT_TOOLBAR:
								case GPUnit::UT_REBARCTRL:
								case GPUnit::UT_HEADER:
									if (mLevel<5) break;
								case GPUnit::UT_DLGBAR:
								case GPUnit::UT_FRAMEBAR:
								case GPUnit::UT_DIALOGBAR:
								case GPUnit::UT_ANISTATIC:
								case GPUnit::UT_STATIC:
									if (mLevel<4) break;
								case GPUnit::UT_STATUSBARCTRL:
								case GPUnit::UT_TOOLBARCTRL:
								case GPUnit::UT_STATUSBAR:
									if (mLevel<3) break;
								case GPUnit::UT_TREECTRL:
								case GPUnit::UT_LISTBOX:
								case GPUnit::UT_CHECKLISTBOX:
								case GPUnit::UT_DRAGLISTBOX:
								case GPUnit::UT_LISTCTRL:
								case GPUnit::UT_FLEXGRID:
									if (mLevel<2) break;
								case GPUnit::UT_ANIBUTTON:
								case GPUnit::UT_SCROLLBAR:
								case GPUnit::UT_SPINBUTTON:
								case GPUnit::UT_BUTTON:
								case GPUnit::UT_BBUTTON:
								case GPUnit::UT_TABCTRL:
								case GPUnit::UT_PROGRESS:
								case GPUnit::UT_SLIDER:
								case GPUnit::UT_CONTROL:
									if (mLevel<1) break;
								case GPUnit::UT_DATETIMECTRL:
								case GPUnit::UT_RTF:
								case GPUnit::UT_EDITOR:
								case GPUnit::UT_EDIT:
								case GPUnit::UT_COMBOBOX:
								case GPUnit::UT_MONTHCAL:
								case GPUnit::UT_COMBOBOXEX:
									try
									{
										HWND tmpParent=GPU[i]->UnitHWND;
										while(tmpParent && (tmpParent=::GetParent(tmpParent)) && tmpParent!=UnitHWND);

										if (tmpParent==UnitHWND)
										{
											for(LastI;LastI<i;LastI++)
												*(resStr++)='\x7F';
											*resStr=0;

											GPU[i]->DoWindowMethod("GetWindowTextEx",resStr);
											while(*resStr)
											{
												if (*resStr==0x7)  *resStr=0x2;
												else
													if (*resStr<0x6)  (*resStr)++;
													else
														if (*resStr==0x7F)  *resStr=0x07;
												resStr++;
											}
										}
									}
									catch(...)
									{
										GPC.m_ErrReport.GPWriteErrorLog("GPUnit", "DoWindowMethod 5116",iStr);
									}
									break;
								}
					}
					break;
				case 104: /*LockWindowUpdate*/
					retint=::LockWindowUpdate(UnitHWND);
					break;
				case 105: /*UnLockWindowUpdate*/
					retint=::LockWindowUpdate(NULL);
					break;
				case 106: /*DrawAnimatedRects*/
					{
						RECT rm={0},rn={0};
						DWORD style=0;
						m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d,%d,%d,%d,%d",&rm.left,&rm.top,&rm.right,&rm.bottom,&rn.left,&rn.top,&rn.right,&rn.bottom,&style);
						if (style==0) style=strstr(pos,"OPEN")?IDANI_OPEN:IDANI_CAPTION;
						retint=DrawAnimatedRects(UnitHWND,style,&rm,&rn);
					}
					break;
				case 107: /*RedrawWindow*/
					{
						RECT rm={0};
						DWORD style=0;
						m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d",&rm.left,&rm.top,&rm.right,&rm.bottom,&style);
						UINT i;
						for(i=0;i<GPUnit::uNRedrawFlag;i++)
							if (strstr(pos,GPUnit::aRedrawFlagName[i]))
								style|=GPUnit::aRedrawFlagUINT[i];

						retint=RedrawWindow(UnitHWND,&rm,NULL,style);
					}
					break;
				case 108: /*UpdateWindow*/
					retint=UpdateWindow(UnitHWND);
					break;
				case 109: /*ValidateRect*/
					{
						RECT rm={0};
						m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&rm.left,&rm.top,&rm.right,&rm.bottom);
						retint=ValidateRect(UnitHWND,&rm);
					}
					break;
	#ifdef W_95
	#else
				case 110: /*GetWindowInfo*/
					if (oStr)
					{
						WINDOWINFO pwi={0};
						pwi.cbSize=sizeof(pwi);
						if ((retint=GetWindowInfo(UnitHWND,&pwi)))
						{
							char *TMPST=new char [2000];
							*TMPST=0;TMPST[1000]=0;
							sprintf(oStr,"%d\x7%d\x7%d\x7%d\x7F%d\x7%d\x7%d\x7%d\x7F%s\x7F%s\x7F%d\x7F%d\x7%d\x7F%d\x7F",
								pwi.rcWindow.left,pwi.rcWindow.top,pwi.rcWindow.right,pwi.rcWindow.bottom,
								pwi.rcClient.left,pwi.rcClient.top,pwi.rcClient.right,pwi.rcClient.bottom,
								StyleToString(UnitType,pwi.dwStyle,TMPST,""),
								StyleExToString(pwi.dwExStyle,TMPST+1000,""),
								pwi.dwWindowStatus,
								pwi.cxWindowBorders,
								pwi.cyWindowBorders,
								pwi.wCreatorVersion
								);

							GetClassName(UnitHWND,oStr+(int)strlen(oStr),1000);
							delete[] TMPST;
						}

					}
					break;
	#endif
				case 111: /*GetClassName*/
					if (oStr)
						retint=::GetClassName(UnitHWND,oStr,1000);
					break;
				case 112: /*GetObjectType*/
					if (oStr)
						strcpy(oStr,GPUnit::aTypeUnit[UnitType]);
					break;
				case 113: /*MoveWindowEx DeltaXtl,DeltaYtl,DeltaXbr,DeltaYbr,bRepaint"*/
					{
						int DeltaXtl=0,DeltaYtl=0,DeltaXbr=0,DeltaYbr=0;
						BOOL bRepaint=TRUE;
						retint=0;
						m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d",&DeltaXtl,&DeltaYtl,&DeltaXbr,&DeltaYbr,&bRepaint);
						if (DeltaXtl || DeltaYtl || DeltaXbr || DeltaYbr)
						{
							CRect re;
							::GetWindowRect(UnitHWND,&re);
							if ((::GetWindowLong(UnitHWND,GWL_STYLE)&WS_POPUP)!=WS_POPUP)
							{
								CPoint po(0,0);
								ClientToScreen(::GetParent(UnitHWND),&po);
								re-=po;
							}
							re.top+=DeltaYtl;
							re.bottom+=DeltaYbr;
							re.left+=DeltaXtl;
							re.right+=DeltaXbr;
							retint=::MoveWindow(UnitHWND,re.left,re.top,re.Width(),re.Height(),bRepaint);
						}
					}
					break;

				case 114: /*ChangeWindowSize DeltaCX,DeltaCY,bRepaint,FixPoint"*/
				case 115: /*SetWindowSize DeltaCX,DeltaCY,bRepaint,FixPoint"*/
					{

						int DeltaCX=0,DeltaCY=0;
						BOOL bRepaint=TRUE;
						retint=0;
						m_LastScanf=sscanf(pos,"%d,%d,%d",&DeltaCX,&DeltaCY,&bRepaint);
						if (nfunc==115)
						{
							if (DeltaCX<0) DeltaCX=0;
							if (DeltaCY<0) DeltaCY=0;
						}

						if (DeltaCX || DeltaCY)
						{
							CRect re;
							::GetWindowRect(UnitHWND,&re);
							if ((::GetWindowLong(UnitHWND,GWL_STYLE)&WS_POPUP)!=WS_POPUP)
							{
								CPoint po(0,0);
								ClientToScreen(::GetParent(UnitHWND),&po);
								re-=po;
							}
							if (nfunc==114)
							{
								if (strchr(pos,'R') || strchr(pos,'r'))
									re.left-=DeltaCX;
								else
									re.right+=DeltaCX;

								if (strchr(pos,'B') || strchr(pos,'b'))
									re.top-=DeltaCY;
								else
									re.bottom+=DeltaCY;
							}
							else
							{
								if (strchr(pos,'R') || strchr(pos,'r'))
								{
									if (DeltaCX) re.left=re.right-DeltaCX;
								}
								else
								{
									if (DeltaCX) re.right=re.left+DeltaCX;
								}
								if (strchr(pos,'B') || strchr(pos,'b'))
								{
									if (DeltaCY) re.top=re.bottom-DeltaCY;
								}
								else
								{
									if (DeltaCY) re.bottom=re.top+DeltaCY;
								}
							}

							retint=::MoveWindow(UnitHWND,re.left,re.top,re.Width(),re.Height(),bRepaint);
							retint=::InvalidateRect(UnitHWND,re,1);
						}
					}
					break;
				case 116: /*AutoSizingByActualSize*/
					if (GPC.m_UpdateSizeNow==0)
					{
						GPC.m_UpdateSizeNow=1;
						::SendMessage(UnitHWND,GPM_SETAUTOSIZE,(WPARAM)UnitHWND,0);
					}
					break;

				case 117: /*DoChildsMethod*/
				case 118: /*DoChildsMethodEx*/
					if (oStr)
					{
						m_WarningsIgnore=1;
						UINT LastI=1;
						char *resStr=oStr;
						UINT i;
						for(i=1;i<(*GPU)->m_NGPUNIT;i++)
							if (GPU[i] && GPU[i]->UnitHWND && GPU[i]->UnitHWND!=UnitHWND)
								try
								{
									HWND tmpParent=GPU[i]->UnitHWND;
									if (nfunc==117)
									{
										if (tmpParent) tmpParent=::GetParent(tmpParent);
									}
									else
										if (GPU[i]->IsChildOfThis(UnitHWND)) tmpParent=UnitHWND;

									if (tmpParent==UnitHWND)
									{
										*resStr=0;

										if (GPU[i]->DoMethod(pos,resStr+i-LastI))
										{
											for(;LastI<i;LastI++) *(resStr++)='\x7F';
	
											while(*resStr)
											{
												if (*resStr==0x7)  *resStr=0x2;
												else
												if (*resStr==0x7F)  *resStr=0x1;
												else
												if (*resStr<0x7)  *resStr=*resStr+1;
												resStr++;
											}
										}
										else *resStr=0;
									}
								}
								catch(...)
								{
									GPC.m_ErrReport.GPWriteErrorLog("GPUnit", "DoWindowMethod 5333",iStr);
								}
						m_WarningsIgnore=0;

					}
					break;
				case 120: /*UnsubclassWindow*/
					if (m_WindowLessFlag && UnitHWND)
					{
						try
						{
							switch(UnitType)
							{
							case UT_MAINDLGSCR: /*cwnd*/
								retint=NULL;
								break;
							case UT_DRAW:			retint=(int)((GPDrawWnd *)UnitPtr)->UnsubclassWindow();		break;
							case UT_DATETIMECTRL:	retint=(int)((GPDateTimeCtrl *)UnitPtr)->UnsubclassWindow();	break;
							case UT_MONTHCAL:		retint=(int)((GPMonthCalCtrl *)UnitPtr)->UnsubclassWindow();	break;
							case UT_DLGBAR:			retint=(int)((GPDlgBar *)UnitPtr)->UnsubclassWindow();		break;
							case UT_FRAMEBAR:		retint=(int)((GPFrameBar *)UnitPtr)->UnsubclassWindow();		break;
							case UT_RTF: 			retint=(int)((GP_RTF*)UnitPtr)->UnsubclassWindow();			break;
							case UT_EDITOR: 		retint=(int)((GPScintilla*)UnitPtr)->UnsubclassWindow();		break;
							case UT_CONTROL: 		retint=(int)((GP_Control*)UnitPtr)->UnsubclassWindow();		break;
							case UT_TREECTRL:		retint=(int)((GPTree*)UnitPtr)->UnsubclassWindow();			break;
							case UT_HEADER:			retint=(int)((GPHeader*)UnitPtr)->UnsubclassWindow();		break;
							case UT_SLIDER:			retint=(int)((GPSlider*)UnitPtr)->UnsubclassWindow();		break;
							case UT_TABCTRL:		retint=(int)((GPTabCtrl*)UnitPtr)->UnsubclassWindow();		break;
							case UT_SPINBUTTON:		retint=(int)((GPSpinButton*)UnitPtr)->UnsubclassWindow();	break;
							case UT_BUTTON:			retint=(int)((GPButton *)UnitPtr)->UnsubclassWindow();		break;
							case UT_ANIBUTTON:		retint=(int)((GPAniButton *)UnitPtr)->UnsubclassWindow();	break;
							case UT_BBUTTON:		retint=(int)((GPBButton*)UnitPtr)->UnsubclassWindow();		break;
							case UT_STATIC:			retint=(int)((GPStatic *)UnitPtr)->UnsubclassWindow();		break;
							case UT_ANISTATIC:		retint=(int)((GPAniStatic *)UnitPtr)->UnsubclassWindow();	break;
							case UT_EDIT:			retint=(int)((GPEdit *)UnitPtr)->UnsubclassWindow();			break;
							case UT_LISTBOX:		retint=(int)((GPListBox *)UnitPtr)->UnsubclassWindow();		break;
							case UT_COMBOBOX:		retint=(int)((GPComboBox *)UnitPtr)->UnsubclassWindow();		break;
							case UT_COMBOBOXEX:		retint=(int)((GPComboBoxEx *)UnitPtr)->UnsubclassWindow();		break;
							case UT_SCROLLBAR:		retint=(int)((GPScrollBar *)UnitPtr)->UnsubclassWindow();	break;
							case UT_PROGRESS:		retint=(int)((GPProgress *)UnitPtr)->UnsubclassWindow();		break;
							case UT_ANIMAT:			retint=(int)((GPAnimate *)UnitPtr)->UnsubclassWindow();		break;
							case UT_CHECKLISTBOX:	retint=(int)((GPChLBox *)UnitPtr)->UnsubclassWindow();		break;
							case UT_DRAGLISTBOX:	retint=(int)((GPDrLBox *)UnitPtr)->UnsubclassWindow();		break;
							case UT_LISTCTRL: 		retint=(int)((GPListCtr *)UnitPtr)->UnsubclassWindow();		break;
							case UT_STATUSBARCTRL: 	retint=(int)((GPStatusBarCtrl *)UnitPtr)->UnsubclassWindow();break;
							case UT_TOOLBARCTRL: 	retint=(int)((GPToolBarCtrl *)UnitPtr)->UnsubclassWindow();	break;
							case UT_STATUSBAR: 		retint=(int)((GPStatusBar *)UnitPtr)->UnsubclassWindow();	break;
							case UT_TOOLBAR: 		retint=(int)((GPToolBar *)UnitPtr)->UnsubclassWindow();		break;
							case UT_DIALOGBAR: 		retint=(int)((GPDialogBar *)UnitPtr)->UnsubclassWindow();	break;
							case UT_REBARCTRL: 		retint=(int)((GPReBarCtrl *)UnitPtr)->UnsubclassWindow();	break;
							case UT_REBAR:	 		retint=(int)((GPReBar *)UnitPtr)->UnsubclassWindow();		break;
							case UT_FLEXGRID:		retint=(int)((GPCMSFlexGrid *)UnitPtr)->UnsubclassWindow();	break;
							case UT_WEBBROWSER:		retint=(int)((GPWebBrowser2 *)UnitPtr)->UnsubclassWindow();	break;
							}// end TypeUnit Switch

							if (retint) UnitHWND=NULL;
						}
						catch(...)
						{
							GPC.m_ErrReport.GPWriteErrorLog("GPUnit", "DoWindowMethod 5395",iStr);
						}
					}
					break;
				case 119: /*SubclassWindow*/
					retint=0;
					if (m_WindowLessFlag && UnitPtr)
					{
						//if (UnitHWND) ((CWnd *)UnitPtr)->UnsubclassWindow();
						//UnitHWND=NULL;
						const char *objNm=strchr(pos,',');
						HWND subclHWND=NULL;
						if (objNm++)
						{
							GPUNITINFO ui;
							if (atoipos || *pos=='0')
								GPC.FindObject(atoipos,objNm,ui);
							else
								GPC.FindObject(pos,objNm,ui);
							subclHWND=ui.hWnd;
						}
						else
							if (atoipos) subclHWND=(HWND)atoipos;

						if (subclHWND)
						{
							try
							{
								switch(UnitType)
								{
								case UT_MAINDLGSCR: /*cwnd*/
									retint=0;
									break;
								case UT_DRAW:			retint=((GPDrawWnd *)UnitPtr)->SubclassWindow(subclHWND);		break;
								case UT_DATETIMECTRL:	retint=((GPDateTimeCtrl *)UnitPtr)->SubclassWindow(subclHWND);	break;
								case UT_MONTHCAL:		retint=((GPMonthCalCtrl *)UnitPtr)->SubclassWindow(subclHWND);	break;
								case UT_DLGBAR:			retint=((GPDlgBar *)UnitPtr)->SubclassWindow(subclHWND);		break;
								case UT_FRAMEBAR:		retint=((GPFrameBar *)UnitPtr)->SubclassWindow(subclHWND);		break;
								case UT_RTF: 			retint=((GP_RTF*)UnitPtr)->SubclassWindow(subclHWND);			break;
								case UT_EDITOR: 		retint=((GPScintilla*)UnitPtr)->SubclassWindow(subclHWND);		break;
								case UT_CONTROL: 		retint=((GP_Control*)UnitPtr)->SubclassWindow(subclHWND);		break;
								case UT_TREECTRL:		retint=((GPTree*)UnitPtr)->SubclassWindow(subclHWND);			break;
								case UT_HEADER:			retint=((GPHeader*)UnitPtr)->SubclassWindow(subclHWND);		break;
								case UT_SLIDER:			retint=((GPSlider*)UnitPtr)->SubclassWindow(subclHWND);		break;
								case UT_TABCTRL:		retint=((GPTabCtrl*)UnitPtr)->SubclassWindow(subclHWND);		break;
								case UT_SPINBUTTON:		retint=((GPSpinButton*)UnitPtr)->SubclassWindow(subclHWND);	break;
								case UT_BUTTON:			retint=((GPButton *)UnitPtr)->SubclassWindow(subclHWND);		break;
								case UT_ANIBUTTON:		retint=((GPAniButton *)UnitPtr)->SubclassWindow(subclHWND);	break;
								case UT_BBUTTON:		retint=((GPBButton*)UnitPtr)->SubclassWindow(subclHWND);		break;
								case UT_STATIC:			retint=((GPStatic *)UnitPtr)->SubclassWindow(subclHWND);		break;
								case UT_ANISTATIC:		retint=((GPAniStatic *)UnitPtr)->SubclassWindow(subclHWND);	break;
								case UT_EDIT:			retint=((GPEdit *)UnitPtr)->SubclassWindow(subclHWND);			break;
								case UT_LISTBOX:		retint=((GPListBox *)UnitPtr)->SubclassWindow(subclHWND);		break;
								case UT_COMBOBOX:		retint=((GPComboBox *)UnitPtr)->SubclassWindow(subclHWND);		break;
								case UT_COMBOBOXEX:		retint=((GPComboBoxEx *)UnitPtr)->SubclassWindow(subclHWND);		break;
								case UT_SCROLLBAR:		retint=((GPScrollBar *)UnitPtr)->SubclassWindow(subclHWND);	break;
								case UT_PROGRESS:		retint=((GPProgress *)UnitPtr)->SubclassWindow(subclHWND);		break;
								case UT_ANIMAT:			retint=((GPAnimate *)UnitPtr)->SubclassWindow(subclHWND);		break;
								case UT_CHECKLISTBOX:	retint=((GPChLBox *)UnitPtr)->SubclassWindow(subclHWND);		break;
								case UT_DRAGLISTBOX:	retint=((GPDrLBox *)UnitPtr)->SubclassWindow(subclHWND);		break;
								case UT_LISTCTRL: 		retint=((GPListCtr *)UnitPtr)->SubclassWindow(subclHWND);		break;
								case UT_STATUSBARCTRL: 	retint=((GPStatusBarCtrl *)UnitPtr)->SubclassWindow(subclHWND);break;
								case UT_TOOLBARCTRL: 	retint=((GPToolBarCtrl *)UnitPtr)->SubclassWindow(subclHWND);	break;
								case UT_STATUSBAR: 		retint=((GPStatusBar *)UnitPtr)->SubclassWindow(subclHWND);	break;
								case UT_TOOLBAR: 		retint=((GPToolBar *)UnitPtr)->SubclassWindow(subclHWND);		break;
								case UT_DIALOGBAR: 		retint=((GPDialogBar *)UnitPtr)->SubclassWindow(subclHWND);	break;
								case UT_REBARCTRL: 		retint=((GPReBarCtrl *)UnitPtr)->SubclassWindow(subclHWND);	break;
								case UT_REBAR:	 		retint=((GPReBar *)UnitPtr)->SubclassWindow(subclHWND);		break;
								case UT_FLEXGRID:		retint=((GPCMSFlexGrid *)UnitPtr)->SubclassWindow(subclHWND);	break;
								case UT_WEBBROWSER:		retint=((GPWebBrowser2 *)UnitPtr)->SubclassWindow(subclHWND);	break;
								}// end TypeUnit Switch

								if (retint) UnitHWND=subclHWND;
							}
							catch(...)
							{
								GPC.m_ErrReport.GPWriteErrorLog("GPUnit", "DoWindowMethod 5474",iStr);
							}
						}
					}
					break;
				case 121: /*GetHWND*/
					retint=(int)UnitHWND;
					break;
				case 122: /*DoMethods*/
					{
						int nMet=0;
						char *tmpresult=NULL;
						char *posostr=oStr;
						char *tmpmet=new char [50000];
						if (posostr) 
						{
							tmpresult=new char [TMP_STR_OUT_LEN];
							*oStr=0;
						}

						while(*strcpy(tmpmet,ExtractField(pos,++nMet,"\x1")))
						{
							if (posostr)
							{
								if (posostr!=oStr) *(posostr++)='\x7F';
								*posostr=0;
								*tmpresult=0;
							}
							if (DoMethod(tmpmet,tmpresult) && posostr)
							{
								char *posres=tmpresult;
								while(*posostr=*(posres++))
									if (*posostr=='\x7F') *(posostr++)='\x1';
									else
									if (*posostr=='\x7') *(posostr++)='\x2';
									else
									if (*posostr<'\x7') (*(posostr++))++;
									else posostr++;
							}
						}
						if (posostr) delete[] tmpresult;
						delete[] tmpmet;
					}
					break;
				case 123: /*GetClassStyle*/
					if (oStr)
					{
						retint=GetClassLong(UnitHWND,GCL_STYLE);
						UINT i;
						for(i=0;i<GPUnit::uNClassStyles;i++)
						{
							if ((retint&GPUnit::uArrClassStyles[i])==GPUnit::uArrClassStyles[i])
							{
								if (*oStr) strcat(oStr,"|");
								strcat(oStr,GPUnit::cArrClassStyles[i]);
							}
						}
					}
					break;
				case 124: /*SetClassStyle ClassStyle*/
					{
						UINT uClassStyle=atoipos;
						char *tmps=new char [(int)strlen(pos)+10];
						strcpy(tmps,pos);
						_strupr(tmps);
						UINT i;
						for(i=0;i<GPUnit::uNClassStyles;i++)
							if (strstr(tmps,GPUnit::cArrClassStyles[i]+3))
								uClassStyle|=GPUnit::uArrClassStyles[i];

						retint=SetClassLong(UnitHWND,GCL_STYLE,uClassStyle);
					}
					break;
				case 125: /*SetDirectOutput bOnOff,_CRON|_BSON| */
					{
						if (atoipos)
						{
							switch(UnitType)
							{
								case UT_MAINDLGSCR: 	break;
								case UT_DRAW:			break;
								case UT_DATETIMECTRL:	break;
								case UT_MONTHCAL:		break;
								case UT_DLGBAR:			break;
								case UT_FRAMEBAR:		break;
								case UT_RTF: 			break;
								case UT_EDITOR: 		break;
								case UT_TREECTRL:		break;
								case UT_HEADER:			break;
								case UT_SLIDER:			break;
								case UT_TABCTRL:		break;
								case UT_SPINBUTTON:		break;
								case UT_BUTTON:			break;
								case UT_ANIBUTTON:		break;
								case UT_BBUTTON:		break;
								case UT_STATIC:			break;
								case UT_ANISTATIC:		break;
								case UT_EDIT:			break;
								case UT_LISTBOX:		((GPListBox *)UnitPtr)->m_LCDOflag=0;		break;
								case UT_COMBOBOX:		((GPComboBox *)UnitPtr)->m_LCDOflag=0;		break;
								case UT_COMBOBOXEX:		((GPComboBoxEx *)UnitPtr)->m_LCDOflag=0;	break;
								case UT_SCROLLBAR:		break;
								case UT_PROGRESS:		((GPProgress *)UnitPtr)->m_csDOString="";	break;
								case UT_ANIMAT:			break;
								case UT_CHECKLISTBOX:	((GPChLBox *)UnitPtr)->m_LCDOflag=0;		break;
								case UT_DRAGLISTBOX:	((GPDrLBox *)UnitPtr)->m_LCDOflag=0;		break;
								case UT_LISTCTRL:
									((GPListCtr *)UnitPtr)->m_DOSubItem=0;
									((GPListCtr *)UnitPtr)->m_LCDOflag=0;
									break;
								case UT_STATUSBARCTRL: 	break;
								case UT_TOOLBARCTRL: 	break;
								case UT_STATUSBAR: 		break;
								case UT_TOOLBAR: 		break;
								case UT_DIALOGBAR: 		break;
								case UT_REBARCTRL: 		break;
								case UT_REBAR:	 		break;
								case UT_FLEXGRID:		break;
								case UT_WEBBROWSER:		break;
							}// end TypeUnit Switch

							if (GPC.DirecOutputArray.Find((DWORD)this)==0xFFFFFFFF)
								GPC.DirecOutputArray.AddItem((DWORD)this);
							m_DirectOutputFlag=0x1;
							CString tmps=pos;
							tmps.MakeUpper();

							if (tmps.Find("_CRON",0)>=0)		m_DirectOutputFlag|=0x2;
							if (tmps.Find("_BSON",0)>=0)		m_DirectOutputFlag|=0x4;
							if (tmps.Find("_AMON",0)>=0)		m_DirectOutputFlag|=0x8;
							if (tmps.Find("_VMON",0)>=0)		m_DirectOutputFlag|=0x10;
							if (tmps.Find("_SVMON",0)>=0)		m_DirectOutputFlag|=0x20;
							if (tmps.Find("_TABOFF",0)>=0)		m_DirectOutputFlag|=0x40;
							if (tmps.Find("_VISIBLE",0)>=0)		m_DirectOutputFlag|=0x80;
							if (tmps.Find("_SVVISIBLE",0)>=0)	m_DirectOutputFlag|=0x100;
							if (tmps.Find("_NOEMPTY",0)>=0)		m_DirectOutputFlag|=0x200;
						}
						else 
						{
							m_DirectOutputFlag=0;
							GPC.DirecOutputArray.RemoveItemByVal((DWORD)this);
						}
						switch(UnitType)
						{
							case UT_CONTROL:
								::SendMessage(UnitHWND,GPM_AX_SETDIRECTINPUT,atoipos,m_DirectOutputFlag);
								break;
						}
					}
					break;
				case 126: /*GetDirectOutput*/
					if (oStr)
					{
						sprintf(oStr,"%d\x7F%s%s%s%s%s%s%s%s%s",
							m_DirectOutputFlag&0x1,
							(m_DirectOutputFlag&0x2)?"_CRON|":"",
							(m_DirectOutputFlag&0x4)?"_BSON|":"",
							(m_DirectOutputFlag&0x8)?"_AMON|":"",
							(m_DirectOutputFlag&0x10)?"_VMON|":"",
							(m_DirectOutputFlag&0x20)?"_SVMON|":"",
							(m_DirectOutputFlag&0x40)?"_TABOFF|":"",
							(m_DirectOutputFlag&0x80)?"_VISIBLE|":"",
							(m_DirectOutputFlag&0x100)?"_SVVISIBLE|":"",
							(m_DirectOutputFlag&0x200)?"_NOEMPTY|":""
							);
					}
					break;
				case 127: /*SetHScrollMask*/
				case 128: /*SetVScrollMask*/
					if (GPMSG)
					{
						retint=(nfunc==127)?GPMSG->m_HSCROLLMASK:GPMSG->m_VSCROLLMASK;
						DWORD newMask=0xFFFFFFFF;
						if (*pos)
						{
							if (atoipos!=0) newMask=(DWORD)atoipos;
							else
							{
								const char *names1[]={"LINEUP",  "LINEDOWN", "PAGEUP",  "PAGEDOWN", "THUMBPOSITION","THUMBTRACK","TOP", "BOTTOM","ENDSCROLL",};
								const char *names2[]={"LINELEFT","LINERIGHT","PAGELEFT","PAGERIGHT","THUMBPOSITION","THUMBTRACK","LEFT","RIGHT", "ENDSCROLL",};
								DWORD tmpmask[]={0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80,0x100,0x200,0x400,};
								const char **cRequest=(nfunc==127)?names2:names1;
								CString tmps="_";
								int i;
								for(i=1;i<9 && tmps!="";i++)
								{									
									tmps=ExtractField(pos,i,"|");
									if (tmps!="")
									{
										int j;
										for(j=0;j<9 && cRequest[j]!=tmps;j++);
										if (j<9) newMask^=tmpmask[j];
									}
								}
							}
						}
						if (nfunc==127)
							GPMSG->m_HSCROLLMASK=newMask;
						else
							GPMSG->m_VSCROLLMASK=newMask;
					}
					break;
				case 129: /*SetScrollTimeout*/
					if (GPMSG)
					{
						if (oStr) sprintf(oStr,"%d",GPMSG->m_MessageDelay1);
						GPMSG->m_MessageDelay1=atoipos;
					}
					break;
				case 130: /*SetKeyProc VKey,[newVK],[Method1][char(2)Method2][....]*/
					if (*pos)
					{
						CString csSRCKey=ExtractField(pos,1,",");
						if (csSRCKey!="")
						{
							DWORD dwSRCKey=0;
							dwSRCKey=GP_HotKey::StringFromToHotKey(csSRCKey,dwSRCKey);
							if (dwSRCKey && HIWORD(dwSRCKey))
							{
								if (!m_KeyRedefine) m_KeyRedefine= new GP_RarefiedArr<GPKEYPROC>;
								if (m_KeyRedefine)
								{
									DWORD dwDSTKey=0;
									dwDSTKey=GP_HotKey::StringFromToHotKey(ExtractField(pos,2,","),dwDSTKey);
									(*m_KeyRedefine)[dwSRCKey].dwSrcVK=dwSRCKey;
									(*m_KeyRedefine)[dwSRCKey].dwDstVK=dwDSTKey;
									const char *ffield=FindField(pos,2,";");
									(*m_KeyRedefine)[dwSRCKey].csMethods=ffield?ffield:"";
								}
							}
						}
					}
					break;
				case 131: /*DeleteKeyProc [VKey]*/
					if (m_KeyRedefine)
					{
						if (*pos)
						{
							DWORD dwSRCKey=0;
							dwSRCKey=GP_HotKey::StringFromToHotKey(pos,dwSRCKey);
							m_KeyRedefine->RemoveItem(dwSRCKey);
						}
						else
						{
							delete m_KeyRedefine;
							m_KeyRedefine=NULL;
						}
					}
					break;
				case 132: /*SetCheckPoint*/
					SetCheckPoint();
					break;
				case 133: /*GetCurrentValue*/
					if (oStr) strcpy(oStr,GetCurrentValue());
					break;
				case 134: /*GetCurrentValueCRC*/
					if (oStr) sprintf(oStr,"%ld",GetCurrentValueCRC());
					break;
				case 135: /*GetChangedValue*/
					if (oStr) strcpy(oStr,GetChangedValue(atoipos || !*pos));
					break;
				case 136: /*SetValChangeCheckPoint*/
					{
						DWORD oldCRC=m_LastValChangeCRC;
						SetValChangeCheckPoint();
						if (oStr) sprintf(oStr,"%X\x7F%X",oldCRC,m_LastValChangeCRC);
					}
					break;
				case 137: /*SetIgnoreSelChangeOnTAB*/
					retint=m_IgnoreSelectionOnTAB;
					m_IgnoreSelectionOnTAB=atoipos;
					break;
				case 138: /*GetCommonStyle*/
					if (oStr)
					{
						int i;
						for(i=0;i<N_UNITCOMMON_STYLES;i++)
							if ((aUnitCommonStyleUINT[i]&UnitCommonStyles)==aUnitCommonStyleUINT[i])	strcat(oStr,aUnitCommonStyleName[i]);
					}
					break;
				case 139: /*MoveWindowRelative [DialogName],[ObjectName],[X],[Y],[CX],[CY]*/
					if (UnitHWND)
					{
						CString csDlgName=ExtractField(pos,1,",");
						CString csObjName=ExtractField(pos,2,",");
						GPUnit **refGPUtmp=NULL;
						if (csDlgName=="")
							refGPUtmp=GPU;
						else
						if (csDlgName=="-1")
							refGPUtmp=GPC.m_Document->a_GPObjDialogDesktop->GPU;
						else
						{
							DWORD dwEnd=MAX_OBJDLG;
							DWORD i=0;
							if (csDlgName[0]>='0' && csDlgName[0]<='9')
							{
								i=atoi(csDlgName);
								if (i<MAX_OBJDLG)
								{
									if (GPC.m_Document->a_GPObjType[i]==0)
									{
										if (GPC.m_Document->a_GPObjDialog[i] && GPC.m_Document->a_GPObjDialog[i]->GPU 
											&& *(GPC.m_Document->a_GPObjDialog[i]->GPU) )
											csDlgName=(*(GPC.m_Document->a_GPObjDialog[i]->GPU))->m_ObjName;
									}
									else
									{
										if (GPC.m_Document->a_GPObjFrame[i] && GPC.m_Document->a_GPObjFrame[i]->GPU 
											&& *(GPC.m_Document->a_GPObjFrame[i]->GPU))
											csDlgName=(*(GPC.m_Document->a_GPObjFrame[i]->GPU))->m_ObjName;
									}
									dwEnd=i+1;
								}

							}
							if (i<MAX_OBJDLG)
							{
								for(;i<dwEnd && !refGPUtmp;i++)
									if (GPC.m_Document->a_GPObjType[i]==0)
									{
										if (GPC.m_Document->a_GPObjDialog[i] && GPC.m_Document->a_GPObjDialog[i]->GPU 
											&& *(GPC.m_Document->a_GPObjDialog[i]->GPU) 
											&& (*(GPC.m_Document->a_GPObjDialog[i]->GPU))->m_ObjName==csDlgName) refGPUtmp=GPC.m_Document->a_GPObjDialog[i]->GPU;
									}
									else
									{
										if (GPC.m_Document->a_GPObjFrame[i] && GPC.m_Document->a_GPObjFrame[i]->GPU 
											&& *(GPC.m_Document->a_GPObjFrame[i]->GPU) 
											&& (*(GPC.m_Document->a_GPObjFrame[i]->GPU))->m_ObjName==csDlgName) refGPUtmp=GPC.m_Document->a_GPObjFrame[i]->GPU;
									}
							}
						}

						if (refGPUtmp)
						{
							GPUnit *GPUtmp=NULL;
							if (csObjName=="")	csObjName=m_ObjName;

							if (csObjName!="")
							{
								DWORD dwEnd=(*refGPUtmp)->m_NGPUNIT;
								DWORD i=0;
								if (csObjName[0]>='0' && csObjName[0]<='9')
								{
									i=atoi(csObjName);
									if (i<(*refGPUtmp)->m_NGPUNIT) GPUtmp=refGPUtmp[i];
								}
								else
									for(i=0;i<(*refGPUtmp)->m_NGPUNIT && !GPUtmp;i++)
										if (refGPUtmp[i] && refGPUtmp[i]->m_ObjName==csObjName) GPUtmp=refGPUtmp[i];
							}

							if (GPUtmp && GPUtmp->UnitHWND)
							{
								RECT re;
								::GetWindowRect(GPUtmp->UnitHWND,&re);
								RECT curRect;
								::GetWindowRect(UnitHWND,&curRect);

								CString csTmp=FindField(pos,3,",");
								CString csTmpTmp;
								csTmpTmp.Format("%d",re.top);
								csTmp.Replace("T",csTmpTmp);
								csTmpTmp.Format("%d",re.bottom);
								csTmp.Replace("B",csTmpTmp);
								csTmpTmp.Format("%d",re.left);
								csTmp.Replace("L",csTmpTmp);
								csTmpTmp.Format("%d",re.right);
								csTmp.Replace("R",csTmpTmp);

								csTmpTmp.Format("%d",curRect.left);
								csTmp.Replace("X",csTmpTmp);
								csTmpTmp.Format("%d",curRect.top);
								csTmp.Replace("Y",csTmpTmp);
								csTmpTmp.Format("%d",curRect.right-curRect.left);
								csTmp.Replace("W",csTmpTmp);
								csTmpTmp.Format("%d",curRect.bottom-curRect.top);
								csTmp.Replace("H",csTmpTmp);
								csTmp.Replace(" ","");

								char *strresult=new char [csTmp.GetLength()*4+1000];
								strcpy(strresult,csTmp);
								int i;
								char arrChOp[] ={'*','+',};
								char arrChOp2[]={'/','-',};
								for(i=0;i<2;i++)
								{
									char *posOp=strresult;
									if (*posOp) posOp++;
									while(*posOp)
										if ((*posOp==arrChOp[i] || *posOp==arrChOp2[i]) && posOp[-1]!=',')
										{
											char chOp=*(posOp++);
											char *chstrt=posOp-2;
											char *chend=posOp;
											while(*chstrt && chstrt!=strresult && ((*chstrt>='0' && *chstrt<='9') ||  *chstrt=='.')) chstrt--;
											if (chstrt!=strresult && *chstrt!='-') chstrt++;
											while(*chend && ((*chend>='0' && *chend<='9') ||  *chend=='.')) chend++;
											double d1=atof(chstrt);
											double d2=atof(posOp);
											switch(chOp)
											{
											case '*':
												d1*=d2;
												break;
											case '/':
												if (d2>-0.0000001 && d2<0.0000001)	d1=0;
												else								d1/=d2;
												break;
											case '+':
												d1+=d2;
												break;
											case '-':
												d1-=d2;
												break;
											}
											char cResult[50];
											int resLen=sprintf(cResult,"%15.15g",d1);

											if (chend-chstrt<=resLen)
											{
												char *tp=chend;
												while(*(tp++));
												while(tp--!=chend) *(tp+resLen)=*tp;
												chend+=resLen;
											}
											strcpy(chstrt,cResult);
											strcat(chstrt,chend);
											char *posOp2=chstrt;
											char *posOp3=chstrt;
											while((*(posOp3)=*(posOp2++)))	if (*posOp3!=' ') posOp3++;
											
											posOp2=chstrt;
											posOp3=chstrt;
											
											while((*(posOp3)=*(posOp2++)))
											{
												if (*posOp3=='+' && (*posOp2=='+' || *posOp2=='-')) {;}
												else
													if (*posOp3=='-' && *posOp2=='+') {posOp2++;posOp3++;}
												else
													if (*posOp3=='-' && *posOp2=='-') {posOp2++;*(posOp3++)='+';}
												else
													posOp3++;

											}
											i--;
											break;
										}
										else posOp++;
								}

								int x=curRect.left,y=curRect.top,cx=curRect.right-curRect.left,cy=curRect.bottom-curRect.top;
								csTmpTmp=ExtractField(strresult,1,",");
								if (csTmpTmp!="") x=atoi(csTmpTmp);
								csTmpTmp=ExtractField(strresult,2,",");
								if (csTmpTmp!="") y=atoi(csTmpTmp);
								csTmpTmp=ExtractField(strresult,3,",");
								if (csTmpTmp!="") cx=atoi(csTmpTmp);
								csTmpTmp=ExtractField(strresult,4,",");
								if (csTmpTmp!="") cy=atoi(csTmpTmp);
								delete[] strresult;
								if ((::GetWindowLong(UnitHWND,GWL_STYLE)&WS_CHILD)==WS_CHILD)
								{
									HWND m_ParentHWND=::GetParent(UnitHWND);
									POINT po;
									po.x=x;
									po.y=y;
									::ScreenToClient(m_ParentHWND,&po);
									x=po.x;
									y=po.y;
								}
								::MoveWindow(UnitHWND,x,y,cx,cy,TRUE);
							}
						}
					}
					break;
				case 140: /*SetScrollPosFlag dwScrollFlags*/
				case 141: /*GetScrollPosFlag */
					{
						const char *ccFlagNames[]={"AUTOPOS"};
						DWORD dwFlag[]={0x01,};
						DWORD i;
						if (oStr)
						{
							for(i=0;i<1;i++)
								if ((dwScrollFlags&dwFlag[i])==dwFlag[i])
								{
									if (*oStr) strcat(oStr,"|");
									strcat(oStr,ccFlagNames[i]);
								}
						}
						if (nfunc==140)
						{
							dwScrollFlags=0;
							for(i=0;i<1;i++)
								if (strstr(pos,ccFlagNames[i]))
									dwScrollFlags|=dwFlag[i];
						}
					}
					break;
				case 142: /*SetWindowTheme ClassName*/
		#ifdef W_95
		#else
			#ifdef W_NT
			#else
				#ifdef W_98
				#else
					#ifdef W_2000
					#else
					{
						CString tmps=pos;
						BSTR bstr=tmps.AllocSysString();
						SetWindowTheme(UnitHWND,NULL, bstr);
						SysFreeString(bstr);
					}
					#endif
				#endif
			#endif
		#endif
					break;
				case 143: /*SetDrawContext DrawContextName*/
					if (oStr) strcpy(oStr,m_DrawContextName);
					m_DrawContextName=pos;
					break;
				case 144: /*ODCMethod MethodName MethodParameters*/
					if (!m_ODC) m_ODC=new CODContext;
					if (m_ODC) m_ODC->DoMethod(pos,oStr);
					break;

		#ifdef W_95
		#else
			#ifdef W_NT
			#else
				#ifdef W_98
				#else
					case 145: /*SetLayeredWindowAttributes [COLORKEY|ALPHA],[R,G,B,A]or[Color]or[HEX()]*/
						{
							CString tmpCS=ExtractField(pos,1,",");
							tmpCS.MakeUpper();
							ARGB clr=CODContextItem::TranlateColor(FindField(pos,2,","));
							::SetLayeredWindowAttributes(UnitHWND,(COLORREF)(clr&0xFFFFFF),(BYTE)((clr/0x1000000)&0xFF),
								(tmpCS.Find("C")<0?0:LWA_COLORKEY)|(tmpCS.Find("A")<0?0:LWA_ALPHA));
						}
						break;
				#endif
			#endif
		#endif
				case 147: /*SetWndEditMode Mode*/
					{
						::KillTimer(UnitHWND,DLGEDITOR_TIMER_ID);
						retint=dwWndEditFlag;
						GPU[0]->dwWndEditFlag|=DLGED_STATENEEDREDRAW;
						dwWndEditFlag=atoipos;
						if ((dwWndEditFlag&DLGED_MODEEDIT))
							::SetTimer(UnitHWND,DLGEDITOR_TIMER_ID,100,NULL);
					}
					break;
				case 148: /*GetWndEditMode Mode*/
					retint=dwWndEditFlag;
					break;



				case 12345678:
				default: if (oStr)	sprintf(oStr,ErrObjSub,met);FRet=FALSE;break;
				}
				if (oStr && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
			}
		}
	}
	catch(...)
	{
		CString tmpss;
		DWORD dwErr=GetLastError();
		tmpss.Format("%d >> %s >> ",dwErr,iStr);

		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
		);
		if (dwErr) tmpss+=(LPTSTR)lpMsgBuf;
		GPC.m_ErrReport.GPWriteErrorLog("GPUnit DoWindowMethod 6003", UnitInfoToString("\x01"),tmpss);
		FRet=FALSE;
		LocalFree( lpMsgBuf );
	}
	return FRet;
}

char * GPUnit::GetSizingStyle()
{
	char * ret= "NNNN";
	HWND tmp=AUSI->GetResizingOwner(UnitHWND);
	if (tmp) ret=AUSI->GetSizingStyle(UnitHWND);
	else
	{
		int i=0;
		for(i=0;(UINT)i<(*GPU)->m_NGPUNIT && tmp==NULL;i++)
			if (GPU[i] && tmp==NULL && GPU[i]->UnitHWND && (GPU[i]->UnitType==UT_FRAMEBAR || GPU[i]->UnitType==UT_DLGBAR)) 
			{
				if (GPU[i]->UnitType==UT_FRAMEBAR)
				{
					tmp=((GPFrameBar *)GPU[i]->UnitPtr)->DlgAutoSize->GetResizingOwner(UnitHWND);
					if (tmp) ret=((GPFrameBar *)GPU[i]->UnitPtr)->DlgAutoSize->GetSizingStyle(UnitHWND);
				}
				else
					if (GPU[i]->UnitType==UT_DLGBAR)
					{
						tmp=((GPDlgBar *)(GPU[i]->UnitPtr))->DlgAutoSize->GetResizingOwner(UnitHWND);
						if (tmp) ret=((GPDlgBar *)(GPU[i]->UnitPtr))->DlgAutoSize->GetSizingStyle(UnitHWND);
					}
			}
	}

	return ret;
}

void GPUnit::GPUpdateUnit()
{
	if (UnitHWND)
	{
		if ((::GetWindowLong(UnitHWND,GWL_STYLE)&WS_CHILD)==WS_CHILD)
		{
			InvalidateGPUnit();
		}
		else
		{
			InvalidateGPUnit();
		}
		if ((::GetWindowLong(UnitHWND,GWL_STYLE)&WS_CHILD)==WS_CHILD)
		{

			CRect re2;
			CRect re;
			::GetClientRect(::GetParent(UnitHWND),&re);
			::ClientToScreen(::GetParent(UnitHWND),((LPPOINT)&re));
			::ClientToScreen(::GetParent(UnitHWND),((LPPOINT)&re)+1);
			::GetWindowRect(UnitHWND,&re2);
			re2.OffsetRect(-re.TopLeft());
			re2.right++;
			::MoveWindow(UnitHWND,re2.left,re2.top,re2.Width(),re2.Height(),TRUE);
			re2.right--;
			::MoveWindow(UnitHWND,re2.left,re2.top,re2.Width(),re2.Height(),TRUE);
			if (NoUpdateParent==FALSE)
			{
				if ((::GetWindowLong(UnitHWND,GWL_STYLE)&WS_CHILD)==WS_CHILD)
					CWnd::FromHandle(::GetParent(UnitHWND))->Invalidate();
			}
		}
		else
		{
			CRect re2;
			::GetWindowRect(UnitHWND,&re2);
			re2.right++;
			::MoveWindow(UnitHWND,re2.left,re2.top,re2.Width(),re2.Height(),TRUE);
			re2.right--;
			::MoveWindow(UnitHWND,re2.left,re2.top,re2.Width(),re2.Height(),TRUE);

	///////////////////		UnitHWND->Invalidate();
			if ((::GetWindowLong(UnitHWND,GWL_STYLE)&WS_CHILD)==WS_CHILD)
				CWnd::FromHandle(::GetParent(UnitHWND))->Invalidate();
		}

	}
}

void GPUnit::DelAllHotkey()
{
	if (UnitPtr && UnitHotkey) delete UnitHotkey;
	UnitHotkey=NULL;
}

BOOL GPUnit::DelHotkey(UINT iId, const char *iHotkeyName)
{
	if (UnitPtr && UnitHotkey) UnitHotkey->DelHotkey(iId,iHotkeyName);
	return TRUE;
}

BOOL GPUnit::AddHotkey(char *nm_VK, UINT iId, const char *seq)
{
	if (UnitPtr)
	{
		if (!UnitHotkey) UnitHotkey=new GP_HotKey(this);
		if (UnitHotkey) UnitHotkey->AddHotkey(nm_VK,iId,seq);
	}

return TRUE;
}

void GPUnit::UpdateGroup(int SelectedItem, UINT iStyle)
{
	if (m_UpdateGroupFlag)
	{
		m_UpdateGroupFlag=0;
		UINT nunit;
		UINT id=UnitId&0xFFFF;
		BOOL flg=((SelectedItem&0x1000)==0x1000);
		SelectedItem=((SelectedItem|0x1000)^0x1000);
		if (GPU && GPU[0] && GPU[0]->UnitHWND)
		{
			for(nunit=1;nunit<(*GPU)->m_NGPUNIT;nunit++)
				if ((UnitId&0xFFFF)!=nunit && GPU[nunit] && GPU[nunit]->GroupNum && GPU[nunit]->UnitHWND)
				{
					HWND nunitHWND=GPU[nunit]->UnitHWND;
					UINT cmpstl=::GetWindowLong(nunitHWND,GWL_STYLE);
					BOOL VISSTATE=(cmpstl&WS_VISIBLE)	==WS_VISIBLE;
					char strtmp[350];
					char *GPUGN=GPU[nunit]->GroupNum;

					sprintf(strtmp,",%d,",id);
					if (strstr(GPUGN,strtmp))
					{
						m_UpdateGroupFlag=1;
						if ((iStyle&WS_VISIBLE)==0	&& VISSTATE)
							GPU[nunit]->GPSetProperty("DELSTYLE=WS_VISIBLE");
					}
					else
					{
						int i;
						char *cmpstr[10];
						sprintf(strtmp,",%d.@,%d.-,@,%d.*,@,%d.%d,",id,id,id,id,SelectedItem);
						for(cmpstr[0]=strtmp,i=1;i<4;i++)
							{cmpstr[i]=strchr(cmpstr[i-1],'@');*(cmpstr[i]++)=0;}

						if (strstr(GPUGN,cmpstr[0]))
						{
							m_UpdateGroupFlag=1;
							BOOL result=FALSE;
							if (SelectedItem==-123456)	result=(strstr(GPUGN,cmpstr[1])!=NULL);
							else
								if ((result=(strstr(GPUGN,cmpstr[2])!=NULL))==FALSE)
									result=(strstr(GPUGN,cmpstr[3])!=NULL);

							if (flg==FALSE && result!=TRUE && VISSTATE)
								GPU[nunit]->GPSetProperty("DELSTYLE=WS_VISIBLE");
						}
						else
						{
							sprintf(strtmp,",U%d.@,U%d.-,@,U%d.*,@,U%d.%d,",id,id,id,id,SelectedItem);
							for(cmpstr[0]=strtmp,i=1;i<4;i++)
								{cmpstr[i]=strchr(cmpstr[i-1],'@');*(cmpstr[i]++)=0;}

							if (strstr(GPUGN,cmpstr[0]))
							{
								m_UpdateGroupFlag=1;
								BOOL result=FALSE;
								if (SelectedItem==-123456)	result=(strstr(GPUGN,cmpstr[1])!=NULL);
								else
									if ((result=(strstr(GPUGN,cmpstr[2])!=NULL))==FALSE)
										result=(strstr(GPUGN,cmpstr[3])!=NULL);

								if (result==TRUE && VISSTATE)
										GPU[nunit]->GPSetProperty("DELSTYLE=WS_VISIBLE");
							}
							else
							{
								for(i=0;i<4;i++) *(cmpstr[i]+1)='V';

								if (strstr(GPUGN,cmpstr[0]))
								{
									m_UpdateGroupFlag=1;
									BOOL result=FALSE;
									if (SelectedItem==-123456)	result=(strstr(GPUGN,cmpstr[1])!=NULL);
									else
										if ((result=(strstr(GPUGN,cmpstr[2])!=NULL))==FALSE)
											result=(strstr(GPUGN,cmpstr[3])!=NULL);

									if (flg==FALSE && result!=TRUE && VISSTATE)
										GPU[nunit]->GPSetProperty("DELSTYLE=WS_VISIBLE");
								}
								else
								{
									for(i=0;i<4;i++) *(cmpstr[i]+1)='E';
									if (strstr(GPUGN,cmpstr[0])==NULL)
									{
										for(i=0;i<4;i++) *(cmpstr[i]+1)='D';
										if (strstr(GPUGN,cmpstr[0])==NULL)
										{
											for(i=0;i<4;i++) *(cmpstr[i]+1)='I';
											if (strstr(GPUGN,cmpstr[0]))
											{
												m_UpdateGroupFlag=1;
												BOOL result=FALSE;
												if (SelectedItem==-123456)	result=(strstr(GPUGN,cmpstr[1])!=NULL);
												else
													if ((result=(strstr(GPUGN,cmpstr[2])!=NULL))==FALSE)
														result=(strstr(GPUGN,cmpstr[3])!=NULL);

												if (result==TRUE && VISSTATE)
													GPU[nunit]->GPSetProperty("DELSTYLE=WS_VISIBLE");
											}
										}
									}
								}
							}
						}
					}
				}


			for(nunit=1;nunit<(*GPU)->m_NGPUNIT;nunit++)
				if (GPU[nunit] && GPU[nunit]->GroupNum && GPU[nunit]->UnitHWND)
				{
					UINT cmpstl=::GetWindowLong(GPU[nunit]->UnitHWND,GWL_STYLE);
					BOOL DISSTATE=(cmpstl&WS_DISABLED)	==WS_DISABLED;
					BOOL VISSTATE=(cmpstl&WS_VISIBLE)	==WS_VISIBLE;
					char strtmp[150];
					char *GPUGN=GPU[nunit]->GroupNum;

					sprintf(strtmp,",%d,",id);
					if (strstr(GPUGN,strtmp))
					{
						m_UpdateGroupFlag=1;
						if ((iStyle&WS_DISABLED)==0 && DISSTATE)							GPU[nunit]->GPSetProperty("DELSTYLE=WS_DISABLED");
						if ((iStyle&WS_GROUP)==0	&& (cmpstl&WS_GROUP)==WS_GROUP)			GPU[nunit]->GPSetProperty("DELSTYLE=WS_GROUP");
						if ((iStyle&WS_TABSTOP)==0	&& (cmpstl&WS_TABSTOP)==WS_TABSTOP)		GPU[nunit]->GPSetProperty("DELSTYLE=WS_TABSTOP");
						if ((iStyle&WS_DISABLED)==WS_DISABLED && !DISSTATE)				GPU[nunit]->GPSetProperty("ADDSTYLE=WS_DISABLED");
						if ((iStyle&WS_GROUP)==WS_GROUP && (cmpstl&WS_GROUP)==0)		GPU[nunit]->GPSetProperty("ADDSTYLE=WS_GROUP");
						if ((iStyle&WS_TABSTOP)==WS_TABSTOP && (cmpstl&WS_TABSTOP)==0)	GPU[nunit]->GPSetProperty("ADDSTYLE=WS_TABSTOP");
						if ((iStyle&WS_VISIBLE)==WS_VISIBLE && !VISSTATE)				GPU[nunit]->GPSetProperty("ADDSTYLE=WS_VISIBLE");
					}
					else
					{
						int i;
						char *cmpstr[4];
						sprintf(strtmp,",%d.@,%d.-,@,%d.*,@,%d.%d,",id,id,id,id,SelectedItem);
						for(cmpstr[0]=strtmp,i=1;i<4;i++)
							{cmpstr[i]=strchr(cmpstr[i-1],'@');*(cmpstr[i]++)=0;}

						if (strstr(GPUGN,cmpstr[0]))
						{
							m_UpdateGroupFlag=1;
							BOOL result=FALSE;
							if (SelectedItem==-123456)	result=(strstr(GPUGN,cmpstr[1])!=NULL);
							else
								if ((result=(strstr(GPUGN,cmpstr[2])!=NULL))==FALSE)
									result=(strstr(GPUGN,cmpstr[3])!=NULL);

							if (flg==FALSE || result==TRUE)
							{
								if (result==TRUE && DISSTATE)	GPU[nunit]->GPSetProperty("DELSTYLE=WS_DISABLED");
								if (result==TRUE && !VISSTATE)	GPU[nunit]->GPSetProperty("ADDSTYLE=WS_VISIBLE");
								if (result!=TRUE && !DISSTATE)	GPU[nunit]->GPSetProperty("ADDSTYLE=WS_DISABLED");
							}
						}
						else
						{
							sprintf(strtmp,",U%d.@,U%d.-,@,U%d.*,@,U%d.%d,",id,id,id,id,SelectedItem);
							for(cmpstr[0]=strtmp,i=1;i<4;i++)
								{cmpstr[i]=strchr(cmpstr[i-1],'@');*(cmpstr[i]++)=0;}

							if (strstr(GPUGN,cmpstr[0]))
							{
								m_UpdateGroupFlag=1;
								BOOL result=FALSE;
								if (SelectedItem==-123456)	result=(strstr(GPUGN,cmpstr[1])!=NULL);
								else
									if ((result=(strstr(GPUGN,cmpstr[2])!=NULL))==FALSE)
										result=(strstr(GPUGN,cmpstr[3])!=NULL);

								if (flg==FALSE || result==TRUE)
								{
									if (result==TRUE && !DISSTATE)	GPU[nunit]->GPSetProperty("ADDSTYLE=WS_DISABLED");
									if (result!=TRUE && DISSTATE)	GPU[nunit]->GPSetProperty("DELSTYLE=WS_DISABLED");
									if (result!=TRUE && !VISSTATE)	GPU[nunit]->GPSetProperty("ADDSTYLE=WS_VISIBLE");
								}
							}
							else
							{
								for(i=0;i<4;i++) *(cmpstr[i]+1)='V';

								if (strstr(GPUGN,cmpstr[0]))
								{
									m_UpdateGroupFlag=1;
									BOOL result=FALSE;
									if (SelectedItem==-123456)	result=(strstr(GPUGN,cmpstr[1])!=NULL);
									else
										if ((result=(strstr(GPUGN,cmpstr[2])!=NULL))==FALSE)
											result=(strstr(GPUGN,cmpstr[3])!=NULL);

									if (result==TRUE && !VISSTATE)	GPU[nunit]->GPSetProperty("ADDSTYLE=WS_VISIBLE");
								}
								else
								{
									for(i=0;i<4;i++) *(cmpstr[i]+1)='E';
									if (strstr(GPUGN,cmpstr[0]))
									{
										m_UpdateGroupFlag=1;
										BOOL result=FALSE;
										if (SelectedItem==-123456)	result=(strstr(GPUGN,cmpstr[1])!=NULL);
										else
											if ((result=(strstr(GPUGN,cmpstr[2])!=NULL))==FALSE)
												result=(strstr(GPUGN,cmpstr[3])!=NULL);

										if (flg==FALSE || result==TRUE)
										{
											if (result==TRUE && DISSTATE)	GPU[nunit]->GPSetProperty("DELSTYLE=WS_DISABLED");
											if (result!=TRUE && !DISSTATE)	GPU[nunit]->GPSetProperty("ADDSTYLE=WS_DISABLED");
										}

									}
									else
									{
										for(i=0;i<4;i++) *(cmpstr[i]+1)='D';
										if (strstr(GPUGN,cmpstr[0]))
										{
											m_UpdateGroupFlag=1;
											BOOL result=FALSE;
											if (SelectedItem==-123456)	result=(strstr(GPUGN,cmpstr[1])!=NULL);
											else
												if ((result=(strstr(GPUGN,cmpstr[2])!=NULL))==FALSE)
													result=(strstr(GPUGN,cmpstr[3])!=NULL);

											if (flg==FALSE || result==TRUE)
											{
												if (result==TRUE && !DISSTATE)	GPU[nunit]->GPSetProperty("ADDSTYLE=WS_DISABLED");
												if (result!=TRUE && DISSTATE)	GPU[nunit]->GPSetProperty("DELSTYLE=WS_DISABLED");
											}
										}
										else
										{
											for(i=0;i<4;i++) *(cmpstr[i]+1)='I';
											if (strstr(GPUGN,cmpstr[0]))
											{
												m_UpdateGroupFlag=1;
												BOOL result=FALSE;
												if (SelectedItem==-123456)	result=(strstr(GPUGN,cmpstr[1])!=NULL);
												else
													if ((result=(strstr(GPUGN,cmpstr[2])!=NULL))==FALSE)
														result=(strstr(GPUGN,cmpstr[3])!=NULL);

												if (flg==FALSE)
													if (result!=TRUE && !VISSTATE)	GPU[nunit]->GPSetProperty("ADDSTYLE=WS_VISIBLE");
											}
										}
									}
								}
							}
						}
					}
				}
		}
	}
}



UINT GPUnit::DoControlBarMethod(CControlBar *CBObj, const char *iStr, char *oStr)
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
		for(nfunc=0;nfunc<uNControlBarMethod && _stricmp(met,cArrControlBarMethod[nfunc])!=0;nfunc++);

	if (nfunc<uNControlBarMethod) nfunc+=200;

	int retint=-123456;
	int atoipos=atoi(pos);

	try
	{
		if (CBObj)
		switch(nfunc)
		{
		case 200: /*CBGetBarStyle*/
			if (oStr)
				GetObjStlStr(oStr, CBObj->GetBarStyle(), N_CTRLBAR_STYLES,  aCtrlBarStyleName, aCtrlBarStyleUINT, aCtrlBarStyleMask);
			break;
		case 201: /*CBEnableDocking*/
		case 202: /*CBSetBarStyle*/
			{
				UINT stl=0;
				int i;
				for(i=0;i<N_CTRLBAR_STYLES;i++)
					if (strstr(pos,aCtrlBarStyleName[i])) stl|=aCtrlBarStyleUINT[i];

				if (nfunc==1)	CBObj->EnableDocking(stl);
				else			CBObj->SetBarStyle(stl);
			}
			break;
		case 203: /*CBGetBorders*/
			if (oStr)
			{
				CRect re=CBObj->GetBorders();
				sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
			}
			break;
		case 204: /*CBSetBorders*/
			{
				int cxLeft=0,cyTop=0,cxRight=0,cyBottom=0;
				m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&cxLeft,&cyTop,&cxRight,&cyBottom);
				CBObj->SetBorders( cxLeft, cyTop, cxRight, cyBottom);
			}
			break;
		case 205: /*CBGetCount*/		retint=CBObj->GetCount();break;
		case 206: /*CBIsFloating*/	retint=CBObj->IsFloating();break;
		case 207: /*CBCalcFixedLayout*/
			if (oStr)
			{
				BOOL bStretch,bHorz;
				m_LastScanf=sscanf(pos,"%d,%d",&bStretch,&bHorz);
				CSize sz=CBObj->CalcFixedLayout(bStretch,bHorz);
				sprintf(oStr,"%d\x7F%d",sz.cx,sz.cy);
			}
			break;
		case 208: /*CBCalcDynamicLayout*/ // nLength,ModeName
			if (oStr)
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
	
				int nLength=atoipos;
				DWORD dwMode=0;
				DWORD ModeDWORD[7]={LM_STRETCH,LM_HORZ,LM_MRUWIDTH,LM_HORZDOCK,LM_VERTDOCK,LM_LENGTHY,LM_COMMIT,};
				char *ModeName[7]={"LM_STRETCH","LM_HORZ|","LM_MRUWIDTH","LM_HORZDOCK","LM_VERTDOCK","LM_LENGTHY","LM_COMMIT",};

				strcat(pos333,"|");
				_strupr(pos333);
				int i;
				for(i=0; i<7;i++)
					if (strstr(pos333,ModeName[i])==0)
						dwMode|=ModeDWORD[i];

				CSize sz=CBObj->CalcDynamicLayout(nLength,dwMode);
				sprintf(oStr,"%d\x7F%d",sz.cx,sz.cy);
				delete[] pos333;
			}
			break;
		default: if (oStr)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL; break;
		}
	}catch(...)
	{
		char *str=new char [200+(int)strlen(pos)];
		#ifdef RUS
			sprintf(str,"Ошибка выполнения метода %s %s",met,pos);
			CBObj->MessageBox(str,"Ошибка метода");
		#else
			sprintf(str,"Error execution of method %s %s",met,pos);
			CBObj->MessageBox(str,"Error execution");
		#endif
		if (oStr) strcpy(oStr,str);
		nfunc=0xFFFFFFFFL;
		GPC.m_ErrReport.GPWriteErrorLog("GPUnit", "DoControlBarMethod",iStr);
		delete[] str;
	}
	if (oStr && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
	return nfunc;
}


void GPUnit::TranslatePenStyle(const char *iStr, UINT *uPenStyle, UINT *uWidth, COLORREF *cColor)
{
	char *pos= new char [strlen(iStr)+10];
	strcpy(pos,iStr);
	_strupr(pos);
	strcat(pos,"|");

	*uPenStyle=0;
	*uWidth=1;
	*cColor=0;
	int R=0,G=0,B=0;

	char *lpstl[17]={"_SOLID","_DASH|","_DOT","_DASHDOT|","_DASHDOTDOT","_NULL","_INSIDEFRAME","_GEOMETRIC","_COSMETIC","_ALTERNATE","_USERSTYLE","_ENDCAP_ROUND","_ENDCAP_SQUARE","_ENDCAP_FLAT","_JOIN_BEVEL","_JOIN_MITER","_JOIN_ROUND",};
	UINT  uistl[17]={PS_SOLID,PS_DASH,PS_DOT, PS_DASHDOT,PS_DASHDOTDOT,PS_NULL,PS_INSIDEFRAME,PS_GEOMETRIC,PS_COSMETIC,PS_ALTERNATE,PS_USERSTYLE,PS_ENDCAP_ROUND,PS_ENDCAP_SQUARE,PS_ENDCAP_FLAT,PS_JOIN_BEVEL,PS_JOIN_MITER,PS_JOIN_ROUND,};
	int i;

	m_LastScanf=sscanf(pos,"%d,%d,%d,%d",uWidth,&R,&G,&B);
	*cColor=RGB(R,G,B);

	for(i=0;i<17;i++)
		if (strstr(pos,lpstl[i]))
			*uPenStyle|=uistl[i];

	delete[] pos;
}

void GPUnit::SendDropEvent(const char *iDestStr, PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	if (GPMSG && GPMSG->FindInActive("OnDrop"))
	{
		CString tmp;
		CString tmpKey;

		if ((GetAsyncKeyState(VK_RWIN)&0xFF00)) tmpKey+="VK_RWIN|";
		else
		if ((GetAsyncKeyState(VK_LWIN)&0xFF00)) tmpKey+="VK_LWIN|";

		if ((GetAsyncKeyState(VK_LSHIFT)&0xFF00)) tmpKey+="VK_LSHIFT|";
		else
		if ((GetAsyncKeyState(MOD_SHIFT)&0xFF00)) tmpKey+="MOD_SHIFT|";

		if ((GetAsyncKeyState(VK_RCONTROL)&0xFF00)) tmpKey+="VK_RCONTROL|";
		else
		if ((GetAsyncKeyState(VK_LCONTROL)&0xFF00)) tmpKey+="VK_LCONTROL|";
		else
		if ((GetAsyncKeyState(VK_CONTROL)&0xFF00)) tmpKey+="VK_CONTROL|";

		if ((GetAsyncKeyState(VK_RMENU)&0xFF00)) tmpKey+="VK_RMENU|";
		else
		if ((GetAsyncKeyState(VK_LMENU)&0xFF00)) tmpKey+="VK_LMENU|";
		else
		if ((GetAsyncKeyState(MOD_ALT)&0xFF00)) tmpKey+="MOD_ALT|";

		tmp.Format("%s\x7F%s\x7F%c\x7F%d\x7F%s\x7F%d\x7F%s\x7F%s\x7F%d\x7%d\x7F%d\x7F%s",
					(LPCTSTR)pDrDrStruct->DragName,
					iDestStr,
					pDrDrStruct->IdDlg<0xFFFFFFFF?'D':'S',
					pDrDrStruct->IdDlg<0xFFFFFFFF?pDrDrStruct->IdDlg+1:pDrDrStruct->IdScr+1,
					(LPCSTR)pDrDrStruct->DlgScrName,
					pDrDrStruct->IdObj,
					(LPCSTR)pDrDrStruct->ObjName,
					(LPCSTR)tmpKey,
					point->x,
					point->y,
					pDrDrStruct->hWndDrag,
					(LPCTSTR)pDrDrStruct->MessageSting);

		GPMSG->GPSendObjEvent(UnitHWND,UnitId,"OnDrop",tmp);
	}
}

void GPUnit::SendDropHoverEvent(const char *iDestStr, PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	if (GPMSG && GPMSG->FindInActive("OnDragHover"))
	{
		CString tmp;
		tmp.Format("%s\x7F%s\x7F%c\x7F%d\x7F%s\x7F%d\x7F%s\x7F%d\x7F%d\x7F%d\x7F%s",
					(LPCTSTR)pDrDrStruct->DragName,
					iDestStr,
					pDrDrStruct->IdDlg<0xFFFFFFFF?'D':'S',
					pDrDrStruct->IdDlg<0xFFFFFFFF?pDrDrStruct->IdDlg+1:pDrDrStruct->IdScr+1,
					(LPCSTR)pDrDrStruct->DlgScrName,
					pDrDrStruct->IdObj,
					(LPCSTR)pDrDrStruct->ObjName,
					point->x,
					point->y,
					pDrDrStruct->hWndDrag,
					(LPCTSTR)pDrDrStruct->MessageSting);

		GPMSG->GPSendObjEvent(UnitHWND,UnitId,"OnDragHover",tmp);
	}
}

void GPUnit::SendDropMoveEvent(const char *iDestStr, PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	if (GPMSG && GPMSG->FindInActive("OnDragHover"))
	{
		CString tmp;
		tmp.Format("%s\x7F%s\x7F%c\x7F%d\x7F%s\x7F%d\x7F%s\x7F%d\x7F%d\x7F%d\x7F%s",
					(LPCTSTR)pDrDrStruct->DragName,
					iDestStr,
					pDrDrStruct->IdDlg<0xFFFFFFFF?'D':'S',
					pDrDrStruct->IdDlg<0xFFFFFFFF?pDrDrStruct->IdDlg+1:pDrDrStruct->IdScr+1,
					(LPCSTR)pDrDrStruct->DlgScrName,
					pDrDrStruct->IdObj,
					(LPCSTR)pDrDrStruct->ObjName,
					point->x,
					point->y,
					pDrDrStruct->hWndDrag,
					(LPCTSTR)pDrDrStruct->MessageSting);

		GPMSG->GPSendObjEvent(UnitHWND,UnitId,"OnDragMove",tmp);
	}
}

UINT GPUnit::GPNCHitTest(CPoint point, UINT BaseRet)
{
	UINT ret=BaseRet;

	if (m_NCHITTESTflag!=0 && (ret==HTTRANSPARENT || ret==HTNOWHERE || ret==HTERROR))
	{
		RECT re1,re2;
		::GetWindowRect(UnitHWND,&re1);
		::GetClientRect(UnitHWND,&re2);
		::ClientToScreen(UnitHWND,((LPPOINT)&re2));
		::ClientToScreen(UnitHWND,((LPPOINT)&re2)+1);
		int b1=0;
		if (point.y<=re2.top)  b1+=2;
		else
			if (point.y>=re2.bottom)  b1+=1;

		if (point.x<=re2.left)  b1+=8;
		else
			if (point.x>=re2.right)  b1+=4;

		UINT mret[16]={	HTCLIENT,HTBOTTOM,HTTOP,HTTRANSPARENT,HTRIGHT,HTBOTTOMRIGHT,HTTOPRIGHT,HTTRANSPARENT,
						HTLEFT,HTBOTTOMLEFT,HTTOPLEFT,HTTRANSPARENT,HTTRANSPARENT,HTTRANSPARENT,HTTRANSPARENT,HTTRANSPARENT,};
		UINT uStyle=::GetWindowLong(UnitHWND,GWL_STYLE);
		int brdWidth=re2.left-re1.left;

		if ((uStyle&WS_MINIMIZE)==WS_MINIMIZE)
		{
			b1=2;
			brdWidth=3;
			re2.top=re2.bottom=re1.bottom-brdWidth;
			re2.right=re1.right;
		}
		ret=mret[b1];
		if (b1==2 && point.y>re1.top+brdWidth)
		{
			int cmpHeight=re2.top-re1.top-brdWidth;
			if ((uStyle&WS_CAPTION)==WS_CAPTION)
			{
				ret=HTCAPTION;
				if ((::GetWindowLong(UnitHWND,GWL_EXSTYLE)&WS_EX_TOOLWINDOW)==WS_EX_TOOLWINDOW)
				{
					if (point.x>re2.right-brdWidth) ret=HTCLOSE;
				}
				else
				{
					if (point.x>re2.right-cmpHeight) ret=HTCLOSE;
					else
						if (point.x>re2.right-cmpHeight-cmpHeight)
						{
							if ((uStyle&WS_MAXIMIZEBOX)==WS_MAXIMIZEBOX) ret=HTMAXBUTTON;
						}
						else
							if (point.x>re2.right-cmpHeight-cmpHeight-cmpHeight)
							{
								if ((uStyle&WS_MINIMIZEBOX)==WS_MINIMIZEBOX) ret=HTMINBUTTON;
							}
							else
								if (point.x<re2.left+cmpHeight) ret=HTSYSMENU;
				}
			}
		}
		else if (b1!=0 && (uStyle&WS_THICKFRAME)!=WS_THICKFRAME) ret=HTBORDER;

		#ifdef W_95
		#else
			if (b1==0)
			{
				MENUBARINFO mbi={0};
				mbi.cbSize=sizeof(mbi);
				if (GetMenuBarInfo(UnitHWND,OBJID_MENU,0,&mbi) && point.y<re2.top+mbi.rcBar.bottom-mbi.rcBar.top)
					ret=HTMENU;
			}
		#endif
	}
	return ret;
}

void GPUnit::OffsetWndPoint(LPPOINT point)
{
	if (UnitHWND)
	{
		RECT re1;
		::GetWindowRect(UnitHWND,&re1);
		::ScreenToClient(UnitHWND,(LPPOINT)&re1);
		point->x-=re1.left;
		point->y-=re1.top;
	}
}

CString GPUnit::UnitInfoToString(PGPUNITINFO ui, const char * delim)
{
	CString ret;
	ret.Format("%ld%s%ld%s%ld%s%ld%s%ld%s%ld%s%ld%s%ld%s",
		ui->IdDlg,		delim,
		ui->IdObj,		delim,
		ui->IdDlg2,	delim,
		ui->IdObj2,	delim,
		ui->hWnd,		delim,
		ui->hWnd2,	delim,
		ui->ObjType,	delim,
		ui->ObjType2,	delim
		);
	ret+=ui->ObjName;
	return ret;
}

CString GPUnit::UnitInfoToString(const char * delim)
{
	GPUNITINFO ui;
	return UnitInfoToString(GetUnitInfo(ui),delim);
}

PGPUNITINFO GPUnit::GetUnitInfo(GPUNITINFO & ui)
{
	ui.IdDlg=(UnitId/0x10000)&0xFF;
	ui.IdObj=UnitId&0xFFFF;
	ui.IdDlg2=0;
	ui.IdObj2=0;
	ui.hWnd=UnitHWND;
	ui.hWnd2=0;
	ui.ObjName=m_ObjName;
	ui.ObjType=UnitType;
	ui.ObjType2=0;

	return &ui;
}

CString GPUnit::UnitInfoToString2(PGPUNITINFO ui, const char * delim)
{
	CString ret;
	ret.Format("%ld%s%ld%s%ld%s%ld%s%ld%s%ld",
		ui->IdDlg+1,		delim,
		ui->IdObj,		delim,
		ui->IdDlg2+1,	delim,
		ui->IdObj2,	delim,
		ui->hWnd,		delim,
		ui->hWnd2
		);
	return ret;
}

CString GPUnit::UnitInfoToString2Ex(PGPUNITINFO ui, const char * delim)
{
	CString ret;
	CString ret1,ret2;
	ret.Format("%ld%s%ld%s%ld%s%ld%s%ld%s%ld%s",
		ui->IdDlg+1,		delim,
		ui->IdObj,		delim,
		ui->IdDlg2+1,	delim,
		ui->IdObj2,	delim,
		ui->hWnd,		delim,
		ui->hWnd2,		delim
		);

	char cmd[250];
	sprintf(cmd,"D,%d,%d;GetWindowText",ui->IdDlg,ui->IdObj);
	char *oStr=GPC.StrTmpOut; *oStr=0;
	GPC.m_Document->DoObjectMethod(cmd,oStr,0);
	ret+=oStr;
	ret+=delim;

	sprintf(cmd,"D,%d,%d;GetWindowText",ui->IdDlg2,ui->IdObj2);
	*oStr=0;
	GPC.m_Document->DoObjectMethod(cmd,oStr,0);
	ret+=oStr;
	
	return ret;
}

void GPUnit::UpdateSizerSize()
{
	if (m_SizerArray)
		m_SizerArray->UpdateSizers();
}

const CString GPUnit::GetObjectName()
{
	if (m_ObjName=="") m_ObjName.Format("%d",UnitId&0xFFFF);
	return m_ObjName;
}

void GPUnit::AutoSetAutoSizing(UINT iParam)
{
	if (AUSI) AUSI->DeleteAll();

	UINT nActiv=0,i,j;
	for(i=1;i<(*GPU)->m_NGPUNIT;i++)
		if (GPU[i]) nActiv++;

	CRect *re=new CRect [nActiv+1];
	CString *sz=new CString [nActiv+1];
	UINT *num=new UINT [nActiv+1];
	UINT *id=new UINT [nActiv+1];
	UINT *mi=new UINT [nActiv+1];

	for(j=0,i=1;i<(*GPU)->m_NGPUNIT;i++)
		if (GPU[i])
		{
			::GetWindowRect(GPU[i]->UnitHWND,&re[j]);
			id[j]=i;
			num[j]=j;
			j++;
		}


	if (nActiv)
	{
		qsRectYByNum(re,num,0,nActiv-1);

		UINT LastSZ=-1;
		UINT FirstSZ=-1;
		for(i=0;i<nActiv;i++)
		{
			switch(GPU[id[num[i]]]->UnitType)
			{
			case UT_BUTTON:
				if ((::GetWindowLong(GPU[id[num[i]]]->UnitHWND,GWL_STYLE)&BS_GROUPBOX)!=BS_GROUPBOX)
					break;
				{
					UINT k;
					for(k=0;k<nActiv;k++)
					if (k!=i)
					{
						switch(GPU[id[num[k]]]->UnitType)
						{
						case UT_EDIT:
							if (GPU[id[num[k]]]->UnitType==UT_EDIT)
							if ((::GetWindowLong(GPU[id[num[k]]]->UnitHWND,GWL_STYLE)&WS_VSCROLL)!=WS_VSCROLL)
								break;
						case UT_RTF:
						case UT_EDITOR:
						case UT_TREECTRL:
						case UT_TABCTRL:
						case UT_LISTBOX:
						case UT_PROGRESS:
						case UT_CHECKLISTBOX:
						case UT_DRAGLISTBOX:
						case UT_LISTCTRL:
						case UT_FLEXGRID:
						case UT_CONTROL:
						case UT_WEBBROWSER:
							if (re[num[i]].PtInRect(re[num[k]].TopLeft()) && re[num[i]].PtInRect(re[num[k]].BottomRight()))
								k=nActiv;
							break;
						}
					}
					if (k==nActiv) break;
				}
			case UT_EDIT:
				if (GPU[id[num[i]]]->UnitType==UT_EDIT)
				if ((::GetWindowLong(GPU[id[num[i]]]->UnitHWND,GWL_STYLE)&WS_VSCROLL)!=WS_VSCROLL)
					break;
			case UT_RTF:
			case UT_EDITOR:
			case UT_TREECTRL:
			case UT_TABCTRL:
			case UT_LISTBOX:
			case UT_PROGRESS:
			case UT_CHECKLISTBOX:
			case UT_DRAGLISTBOX:
			case UT_LISTCTRL:
			case UT_FLEXGRID:
			case UT_CONTROL:
			case UT_WEBBROWSER:
				if (FirstSZ==-1) FirstSZ=i;
				LastSZ=i;
				break;
			}
			sz[num[i]]="NNNN";
			mi[num[i]]=0;
		}

		if (LastSZ!=-1)
		{
			for(i=0;i<nActiv;i++)
			{
				switch(GPU[id[num[i]]]->UnitType)
				{
				case UT_BUTTON:
					if ((::GetWindowLong(GPU[id[num[i]]]->UnitHWND,GWL_STYLE)&BS_GROUPBOX)!=BS_GROUPBOX)
					{
						if (i && i>FirstSZ)
						{
							sz[num[i]]="ENEN";
							mi[num[i]]=id[num[FirstSZ]];
						}
						break;
					}
				case UT_EDIT:
					if (GPU[id[num[i]]]->UnitType==UT_EDIT)
						if ((::GetWindowLong(GPU[id[num[i]]]->UnitHWND,GWL_STYLE)&WS_VSCROLL)!=WS_VSCROLL)
						{
							if (i && i>FirstSZ)
							{
								sz[num[i]]="ENEN";
								mi[num[i]]=id[num[FirstSZ]];
							}
							break;
						}
				case UT_RTF:
				case UT_EDITOR:
				case UT_TREECTRL:
				case UT_TABCTRL:
				case UT_LISTBOX:
				case UT_PROGRESS:
				case UT_CHECKLISTBOX:
				case UT_DRAGLISTBOX:
				case UT_LISTCTRL:
				case UT_FLEXGRID:
				case UT_CONTROL:
				case UT_WEBBROWSER:
					if (i==FirstSZ && i==LastSZ)
						sz[num[i]]="NNEN";
					else
					if (i==FirstSZ)
					{
						if (re[num[i]].bottom>re[num[LastSZ]].top)
							sz[num[i]]="NNEN";
						else
							sz[num[i]]="NNPN";
					}
					else
					if (i==LastSZ)
					{
						if (re[num[i]].top<re[num[FirstSZ]].bottom)
						{sz[num[i]]=sz[num[FirstSZ]];sz[num[i]].SetAt(2,'E');}
						else
							sz[num[i]]="PNEN";
					}
					else
						sz[num[i]]="PNPN";
					FirstSZ=i;
					break;
				default:
					if (i && i>FirstSZ)
					{
						sz[num[i]]="ENEN";
						mi[num[i]]=id[num[FirstSZ]];
					}
					break;
				}
			}
		}
		else
		{
			CRect retmp;
			::GetWindowRect(AUSI->GetMainItem()->ItemHWND,&retmp);
			AUSI->SetMaxSize(AUSI->GetMainItem()->ItemHWND,-11111,retmp.Height());
		}

		qsRectXByNum(re,num,0,nActiv-1);

		for(i=0;i<nActiv;i++)
		{
			for(j=0;j<nActiv;j++)
				if (j!=i/* && num[j]!=mi[num[i]]*/)
					switch(GPU[id[num[j]]]->UnitType)
					{
					case UT_ANISTATIC:
					case UT_STATIC:
					case UT_DRAW:
					case UT_ANIMAT:
					case UT_DATETIMECTRL:
					case UT_MONTHCAL:
					case UT_SPINBUTTON:
					case UT_ANIBUTTON:
					case UT_BBUTTON:
					case UT_MAINDLGSCR:
						break;
					case UT_BUTTON:
						if ((::GetWindowLong(GPU[id[num[i]]]->UnitHWND,GWL_STYLE)&BS_GROUPBOX)!=BS_GROUPBOX)
							break;
					default:
						if (re[num[j]].top<re[num[i]].bottom && re[num[j]].bottom>re[num[i]].top)
						{
							if (re[num[i]].left>re[num[j]].left)
							{
								if (re[num[i]].right<re[num[j]].right)
								{
									sz[num[i]].SetAt(1,sz[num[j]][1]);
									sz[num[i]].SetAt(3,sz[num[j]][3]);
								}
								else
									sz[num[i]].SetAt(1,'P');
							}
							else
							if (re[num[i]].left<re[num[j]].left)
							{
								if (re[num[i]].right<re[num[j]].left)
								{
									sz[num[i]].SetAt(3,'P');
									sz[num[j]].SetAt(1,'P');
								}
								else
									sz[num[i]].SetAt(3,sz[num[j]][1]);
							}
						}
						break;
					}

					switch(GPU[id[num[i]]]->UnitType)
					{
					case UT_BUTTON:
						if ((::GetWindowLong(GPU[id[num[i]]]->UnitHWND,GWL_STYLE)&BS_GROUPBOX)==BS_GROUPBOX)
						{
							if (sz[num[i]][3]=='N' && sz[num[i]][1]=='P')
								sz[num[i]].SetAt(3,'E');
							else
							if (sz[num[i]][3]=='N' && sz[num[i]][1]=='N')
								sz[num[i]].SetAt(3,'E');
							break;
						}
					case UT_ANISTATIC:
					case UT_DRAW:
					case UT_STATIC:
					case UT_ANIMAT:
					case UT_DATETIMECTRL:
					case UT_MONTHCAL:
					case UT_SPINBUTTON:
					case UT_ANIBUTTON:
					case UT_BBUTTON:
					case UT_MAINDLGSCR:
						if (sz[num[i]][1]=='N') sz[num[i]].SetAt(3,'N');
						else
						if (sz[num[i]][3]=='N' && sz[num[i]][1]=='P')
							{sz[num[i]].SetAt(1,'E');sz[num[i]].SetAt(3,'E');}
						else
						if (sz[num[i]][1]=='P') sz[num[i]].SetAt(3,'P');
						else
						if (sz[num[i]][3]=='P') sz[num[i]].SetAt(1,'P');
						break;
					default:
						if (sz[num[i]][3]=='N' && sz[num[i]][1]=='P')
							sz[num[i]].SetAt(3,'E');
						else
						if (sz[num[i]][3]=='N' && sz[num[i]][1]=='N')
							sz[num[i]].SetAt(3,'E');
						break;
					}
		}

		for(i=0;i<nActiv;i++)
			if (mi[num[i]]==0 && sz[num[i]]!="NNNN")
					AUSI->AddWnd(GPU[id[num[i]]]->UnitHWND,AUSI->GetMainItem()->ItemHWND,sz[num[i]]);

		for(i=0;i<nActiv;i++)
			if (mi[num[i]] && sz[num[i]]!="NNNN")
					AUSI->AddWnd(GPU[id[num[i]]]->UnitHWND,GPU[mi[num[i]]]->UnitHWND,sz[num[i]]);

	}
	delete[] re;
	delete[] sz;
	delete[]  num;
	delete[]  mi;
	delete[]  id;
}

void GPUnit::AutoSizingPause()
{
	if (AUSI) AUSI->AutoSizingPause();
}

void GPUnit::AutoSizingResume()
{
	if (AUSI) AUSI->AutoSizingResume();
}

void GPUnit::AutoSizingReset()
{
	if (AUSI) AUSI->Reset();
}

void GPUnit::AutoSizingReinitSize()
{
	if (AUSI)	AUSI->ReinitSize();
}

DWORD GPUnit::StringToStyle(const char *iStr)
{
	DWORD retStl=0;
	UINT i;
	for(i=0;i<N_WND_STYLES;i++)
		if (strstr(iStr,aWndStyleName[i]))
			retStl|=aWndStyleUINT[i];

	for(i=0;i<N_COMCTRL_STYLES;i++)
		if (strstr(iStr,aComCtrlStyleName[i]))
			retStl|=aComCtrlStyleUINT[i];

	for(i=0;i<N_CTRLBAR_STYLES;i++)
		if (strstr(iStr,aCtrlBarStyleName[i]))
			retStl|=aCtrlBarStyleUINT[i];


	switch(UnitType)
	{
	case UT_MAINDLGSCR:
	case UT_FRAMEBAR:
	case UT_DLGBAR:
		for(i=0;i<N_DLG_STYLES;i++)
			if (strstr(iStr,aDlgStyleName[i]))
				retStl|=aDlgStyleUINT[i];
		break;
	case UT_DATETIMECTRL:
		for(i=0;i<N_DATETIME_STYLES;i++)
			if (strstr(iStr,aDateTimeStyleName[i]))
				retStl|=aDateTimeStyleUINT[i];
		break;
	case UT_MONTHCAL:
		for(i=0;i<N_MONTHCAL_STYLES;i++)
			if (strstr(iStr,aMonthCalStyleName[i]))
				retStl|=aMonthCalStyleUINT[i];
		break;
	case UT_RTF:
		for(i=0;i<N_RTF_STYLES;i++)
			if (strstr(iStr,aRTFStyleName[i]))
				retStl|=aRTFStyleUINT[i];
		break;
	case UT_EDITOR:
		break;
	case UT_TREECTRL:
		for(i=0;i<N_TREECTRL_STYLES;i++)
			if (strstr(iStr,aTreeCtrlStyleName[i]))
				retStl|=aTreeCtrlStyleUINT[i];
		break;
	case UT_HEADER:
		for(i=0;i<N_HEADER_STYLES;i++)
			if (strstr(iStr,aHeaderStyleName[i]))
				retStl|=aHeaderStyleUINT[i];
		break;
	case UT_STATUSBARCTRL:
		for(i=0;i<N_STATUSBARCTRL_STYLES;i++)
			if (strstr(iStr,aStatusBarCtrlStyleName[i]))
				retStl|=aStatusBarCtrlStyleUINT[i];
		break;
	case UT_REBARCTRL:
		for(i=0;i<N_REBARCTRL_STYLES;i++)
			if (strstr(iStr,aReBarCtrlStyleName[i]))
				retStl|=aReBarCtrlStyleUINT[i];
		break;
	case UT_REBAR:
		for(i=0;i<N_REBARCTRL_STYLES;i++)
			if (strstr(iStr,aReBarCtrlStyleName[i]))
				retStl|=aReBarCtrlStyleUINT[i];
		break;
	case UT_STATUSBAR:
		for(i=0;i<N_STATUSBARCTRL_STYLES;i++)
			if (strstr(iStr,aStatusBarCtrlStyleName[i]))
				retStl|=aStatusBarCtrlStyleUINT[i];
		break;
	case UT_TOOLBARCTRL:
		for(i=0;i<N_TOOLBARCTRL_STYLES;i++)
			if (strstr(iStr,aToolBarCtrlStyleName[i]))
				retStl|=aToolBarCtrlStyleUINT[i];
		break;
	case UT_TOOLBAR:
		for(i=0;i<N_TOOLBARCTRL_STYLES;i++)
			if (strstr(iStr,aToolBarCtrlStyleName[i]))
				retStl|=aToolBarCtrlStyleUINT[i];
		break;
	case UT_SLIDER:
		for(i=0;i<N_SLIDER_STYLES;i++)
			if (strstr(iStr,aSliderStyleName[i]))
				retStl|=aSliderStyleUINT[i];
		break;
	case UT_TABCTRL:
		for(i=0;i<N_TAB_STYLES;i++)
			if (strstr(iStr,aTabStyleName[i]))
				retStl|=aTabStyleUINT[i];
		break;
	case UT_SPINBUTTON:
		for(i=0;i<N_SPIN_STYLES;i++)
			if (strstr(iStr,aSpinStyleName[i]))
				retStl|=aSpinStyleUINT[i];
		break;
	case UT_STATIC:
	case UT_ANISTATIC:
		for(i=0;i<N_STATIC_STYLES;i++)
			if (strstr(iStr,aStaticStyleName[i]))
				retStl|=aStaticStyleUINT[i];
		break;
	case UT_EDIT:
		for(i=0;i<N_EDIT_STYLES;i++)
			if (strstr(iStr,aEditStyleName[i]))
				retStl|=aEditStyleUINT[i];
		break;
	case UT_BBUTTON:
	case UT_ANIBUTTON:
	case UT_BUTTON:
		for(i=0;i<N_BUTTON_STYLES;i++)
			if (strstr(iStr,aButtonStyleName[i]))
				retStl|=aButtonStyleUINT[i];
		break;
	case UT_DRAGLISTBOX:
	case UT_CHECKLISTBOX:
	case UT_LISTBOX:
		for(i=0;i<N_LISTBOX_STYLES;i++)
			if (strstr(iStr,aListBoxStyleName[i]))
				retStl|=aListBoxStyleUINT[i];
		break;
	case UT_COMBOBOX:
		for(i=0;i<N_COMBOBOX_STYLES;i++)
			if (strstr(iStr,aComboBoxStyleName[i]))
				retStl|=aComboBoxStyleUINT[i];
		break;
	case UT_COMBOBOXEX:
		for(i=0;i<N_COMBOBOXEX_STYLES;i++)
			if (strstr(iStr,aComboBoxExStyleName[i]))
				retStl|=aComboBoxExStyleUINT[i];
		break;
	case UT_SCROLLBAR:
		for(i=0;i<N_SCROLL_STYLES;i++)
			if (strstr(iStr,aScrollStyleName[i]))
				retStl|=aScrollStyleUINT[i];
		break;
	case UT_PROGRESS:
		for(i=0;i<N_PROGRESS_STYLES;i++)
			if (strstr(iStr,aProgressStyleName[i]))
				retStl|=aProgressStyleUINT[i];
		break;
	case UT_ANIMAT:
		for(i=0;i<N_ANIMATION_STYLES;i++)
			if (strstr(iStr,aAnimationStyleName[i]))
				retStl|=aAnimationStyleUINT[i];
		break;
	case UT_LISTCTRL:
		for(i=0;i<N_LISTCTRL_STYLES;i++)
			if (strstr(iStr,aListCtrlStyleName[i]))
				retStl|=aListCtrlStyleUINT[i];
		break;
	}// end TypeUnit Switch
	return retStl;
}
DWORD GPUnit::StringToStyleEx(const char *iStr)
{
	DWORD retStl=0;
	UINT i;
	for(i=0;i<N_WND_EX_STYLES;i++)
		if (strstr(iStr,aWndExStyleName[i]))
			retStl|=aWndExStyleUINT[i];
	return retStl;
}

const char * GPUnit::StyleToString(DWORD UnitType, DWORD style, char *iStr, const char *Delimiter)
{
	UINT i;

	for(i=0;i<N_WND_STYLES;i++)
		if ((style&aWndStyleUINT[i])==aWndStyleUINT[i])
		{
			if (*iStr) strcat(iStr,Delimiter);
			strcat(iStr,aWndStyleName[i]);
		}

	switch(UnitType)
	{
	case UT_STATUSBARCTRL:
	case UT_REBARCTRL:
	case UT_REBAR:
	case UT_STATUSBAR:
	case UT_TOOLBARCTRL:
	case UT_TOOLBAR:
		for(i=0;i<N_COMCTRL_STYLES;i++)
			if ((style&aComCtrlStyleUINT[i])==aComCtrlStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aComCtrlStyleName[i]);
			}
		for(i=0;i<N_CTRLBAR_STYLES;i++)
			if ((style&aCtrlBarStyleUINT[i])==aCtrlBarStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aCtrlBarStyleName[i]);
			}
		break;
	}

	switch(UnitType)
	{
	case UT_MAINDLGSCR:
	case UT_FRAMEBAR:
	case UT_DLGBAR:
		for(i=0;i<N_DLG_STYLES;i++)
			if ((style&aDlgStyleUINT[i])==aDlgStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aDlgStyleName[i]);
			}
		break;
	case UT_DATETIMECTRL:
		for(i=0;i<N_DATETIME_STYLES;i++)
			if ((style&aDateTimeStyleUINT[i])==aDateTimeStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aDateTimeStyleName[i]);
			}
		break;
	case UT_MONTHCAL:
		for(i=0;i<N_MONTHCAL_STYLES;i++)
			if ((style&aMonthCalStyleUINT[i])==aMonthCalStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aMonthCalStyleName[i]);
			}
		break;
	case UT_RTF:
		for(i=0;i<N_RTF_STYLES;i++)
			if ((style&aRTFStyleUINT[i])==aRTFStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aRTFStyleName[i]);
			}
		break;
	case UT_EDITOR:
		break;
	case UT_TREECTRL:
		for(i=0;i<N_TREECTRL_STYLES;i++)
			if ((style&aTreeCtrlStyleUINT[i])==aTreeCtrlStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aTreeCtrlStyleName[i]);
			}
		break;
	case UT_HEADER:
		for(i=0;i<N_HEADER_STYLES;i++)
			if ((style&aHeaderStyleUINT[i])==aHeaderStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aHeaderStyleName[i]);
			}
		break;
	case UT_STATUSBARCTRL:
		for(i=0;i<N_STATUSBARCTRL_STYLES;i++)
			if ((style&aStatusBarCtrlStyleUINT[i])==aStatusBarCtrlStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aStatusBarCtrlStyleName[i]);
			}
		break;
	case UT_REBARCTRL:
		for(i=0;i<N_REBARCTRL_STYLES;i++)
			if ((style&aReBarCtrlStyleUINT[i])==aReBarCtrlStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aReBarCtrlStyleName[i]);
			}
		break;
	case UT_REBAR:
		for(i=0;i<N_REBARCTRL_STYLES;i++)
			if ((style&aReBarCtrlStyleUINT[i])==aReBarCtrlStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aReBarCtrlStyleName[i]);
			}
		break;
	case UT_STATUSBAR:
		for(i=0;i<N_STATUSBARCTRL_STYLES;i++)
			if ((style&aStatusBarCtrlStyleUINT[i])==aStatusBarCtrlStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aStatusBarCtrlStyleName[i]);
			}
		break;
	case UT_TOOLBARCTRL:
		for(i=0;i<N_TOOLBARCTRL_STYLES;i++)
			if ((style&aToolBarCtrlStyleUINT[i])==aToolBarCtrlStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aToolBarCtrlStyleName[i]);
			}
		break;
	case UT_TOOLBAR:
		for(i=0;i<N_TOOLBARCTRL_STYLES;i++)
			if ((style&aToolBarCtrlStyleUINT[i])==aToolBarCtrlStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aToolBarCtrlStyleName[i]);
			}
		break;
	case UT_SLIDER:
		for(i=0;i<N_SLIDER_STYLES;i++)
			if ((style&aSliderStyleUINT[i])==aSliderStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aSliderStyleName[i]);
			}
		break;
	case UT_TABCTRL:
		for(i=0;i<N_TAB_STYLES;i++)
			if ((style&aTabStyleUINT[i])==aTabStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aTabStyleName[i]);
			}
		break;
	case UT_SPINBUTTON:
		for(i=0;i<N_SPIN_STYLES;i++)
			if ((style&aSpinStyleUINT[i])==aSpinStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aSpinStyleName[i]);
			}
		break;
	case UT_STATIC:
	case UT_ANISTATIC:
		for(i=0;i<N_STATIC_STYLES;i++)
			if ((style&aStaticStyleUINT[i])==aStaticStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aStaticStyleName[i]);
			}
		break;
	case UT_EDIT:
		for(i=0;i<N_EDIT_STYLES;i++)
			if ((style&aEditStyleUINT[i])==aEditStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aEditStyleName[i]);
			}
		break;
	case UT_BBUTTON:
	case UT_ANIBUTTON:
	case UT_BUTTON:
		for(i=0;i<N_BUTTON_STYLES;i++)
			if ((style&aButtonStyleUINT[i])==aButtonStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aButtonStyleName[i]);
			}
		break;
	case UT_DRAGLISTBOX:
	case UT_CHECKLISTBOX:
	case UT_LISTBOX:
		for(i=0;i<N_LISTBOX_STYLES;i++)
			if ((style&aListBoxStyleUINT[i])==aListBoxStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aListBoxStyleName[i]);
			}
		break;
	case UT_COMBOBOX:
		for(i=0;i<N_COMBOBOX_STYLES;i++)
			if ((style&aComboBoxStyleUINT[i])==aComboBoxStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aComboBoxStyleName[i]);
			}
		break;
	case UT_COMBOBOXEX:
		for(i=0;i<N_COMBOBOXEX_STYLES;i++)
			if ((style&aComboBoxExStyleUINT[i])==aComboBoxExStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aComboBoxExStyleName[i]);
			}
		break;
	case UT_SCROLLBAR:
		for(i=0;i<N_SCROLL_STYLES;i++)
			if ((style&aScrollStyleUINT[i])==aScrollStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aScrollStyleName[i]);
			}
		break;
	case UT_PROGRESS:
		for(i=0;i<N_PROGRESS_STYLES;i++)
			if ((style&aProgressStyleUINT[i])==aProgressStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aProgressStyleName[i]);
			}
		break;
	case UT_ANIMAT:
		for(i=0;i<N_ANIMATION_STYLES;i++)
			if ((style&aAnimationStyleUINT[i])==aAnimationStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aAnimationStyleName[i]);
			}
		break;
	case UT_LISTCTRL:
		for(i=0;i<N_LISTCTRL_STYLES;i++)
			if ((style&aListCtrlStyleUINT[i])==aListCtrlStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aListCtrlStyleName[i]);
			}

		break;
	}// end TypeUnit Switch
	return iStr;
}


const char * GPUnit::StyleExToString(DWORD UnitType, DWORD style, char *iStr, const char *Delimiter)
{
	UINT i;
	switch(UnitType)
	{
	case UT_RTF:
		for(i=0;i<N_RTF_EX_STYLES;i++)
			if ((style&aRTFExStyleUINT[i])==aRTFExStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aRTFExStyleName[i]);
			}
		break;
	case UT_EDITOR:
		break;
	case UT_TOOLBARCTRL:
		for(i=0;i<N_TOOLBARCTRL_EX_STYLES;i++)
			if ((style&aToolBarCtrlExStyleUINT[i])==aToolBarCtrlExStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aToolBarCtrlExStyleName[i]);
			}
		break;
	case UT_TOOLBAR:
		for(i=0;i<N_TOOLBARCTRL_EX_STYLES;i++)
			if ((style&aToolBarCtrlExStyleUINT[i])==aToolBarCtrlExStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aToolBarCtrlExStyleName[i]);
			}
		break;
	case UT_TABCTRL:
		for(i=0;i<N_TAB_EX_STYLES;i++)
			if ((style&aTabExStyleUINT[i])==aTabExStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aTabExStyleName[i]);
			}
		break;
	case UT_COMBOBOXEX:
		for(i=0;i<N_COMBOBOXEX_EX_STYLES;i++)
			if ((style&aComboBoxExExStyleUINT[i])==aComboBoxExExStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aComboBoxExExStyleName[i]);
			}
		break;
	case UT_LISTCTRL:
		for(i=0;i<N_LISTCTRL_EX_STYLES;i++)
			if ((style&aListCtrlExStyleUINT[i])==aListCtrlExStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aListCtrlExStyleName[i]);
			}
	case UT_TREECTRL:
		for(i=0;i<N_TREECTRL_EX_STYLES;i++)
			if ((style&aTreeCtrlExStyleUINT[i])==aTreeCtrlExStyleUINT[i])
			{
				if (*iStr) strcat(iStr,Delimiter);
				strcat(iStr,aTreeCtrlExStyleName[i]);
			}

		break;
	}// end TypeUnit Switch
	return iStr;
}

const char * GPUnit::StyleExToString(DWORD style, char *iStr, const char *Delimiter)
{
	UINT i;
	for(i=0;i<N_WND_EX_STYLES;i++)
		if ((style&aWndExStyleUINT[i])==aWndExStyleUINT[i])
		{
			if (*iStr) strcat(iStr,Delimiter);
			strcat(iStr,aWndExStyleName[i]);
		}
	return iStr;
}


void GPUnit::InvalidateGPUnit()
{
	if (UnitHWND)
	{
		RECT re={0};
		POINT po={0};
		::GetWindowRect(UnitHWND,&re);
		HWND hp=NULL;


		if ((GetWindowLong(UnitHWND,GWL_STYLE)&WS_POPUP)==WS_POPUP)
		{
			CRect re2;
			::GetWindowRect(UnitHWND,&re2);
			re2.right++;
			::MoveWindow(UnitHWND,re2.left,re2.top,re2.Width(),re2.Height(),TRUE);
			re2.right--;
			::MoveWindow(UnitHWND,re2.left,re2.top,re2.Width(),re2.Height(),TRUE);

	///////////////////		UnitHWND->Invalidate();
		//	CWnd::FromHandle(UnitHWND)->GetParent()->Invalidate();
		}
		else
		{
			hp=::GetParent(UnitHWND);
			if (hp) hp=UnitHWND;
			::ScreenToClient((HWND)hp,&po);
			re.top+=po.y;
			re.bottom+=po.y;
			re.left+=po.x;
			re.right+=po.x;
			::RedrawWindow(hp,&re,NULL,RDW_ALLCHILDREN|RDW_ERASE|RDW_FRAME|RDW_INTERNALPAINT|RDW_INVALIDATE);
		}
	}
}

BOOL GPUnit::IsChildOfThis(HWND iHWND)
{
	HWND cmpHWND=UnitHWND;
	while((cmpHWND=::GetParent(cmpHWND))!=iHWND && cmpHWND);
	return iHWND==cmpHWND;
}


void GPUnit::CheckGroups(UINT iUnitId)
{
	UINT nunit;
	if (iUnitId==0)
	{
		for(nunit=1;nunit<(*GPU)->m_NGPUNIT;nunit++)
			if (GPU[nunit]) GPU[nunit]->m_UpdateGroupFlag=0;

		for(nunit=1;nunit<(*GPU)->m_NGPUNIT;nunit++)
			if (GPU[nunit] && GPU[nunit]->GroupNum && *GPU[nunit]->GroupNum)
				CheckGroups(nunit);
	}
	else
		if (iUnitId<(*GPU)->m_NGPUNIT && GPU[iUnitId])
		{
			char *pos;
			for(nunit=1;nunit<(*GPU)->m_NGPUNIT;nunit++)
				if (GPU[nunit] && GPU[nunit]->GroupNum && *GPU[nunit]->GroupNum)
				{
					pos=GPU[nunit]->GroupNum;
					while(GPU[nunit]->m_UpdateGroupFlag==0 && *pos)
						if (*pos>='0' && *pos<='9')
						{
							if ((UINT)atoi(pos)==iUnitId) GPU[nunit]->m_UpdateGroupFlag=1;
							while(*pos && ((*pos>='0' && *pos<='9') || *pos=='.')) pos++;
						}
						else pos++;
				}


			if ((pos=GPU[iUnitId]->GroupNum))
				while(*pos)
					if (*pos>='0' && *pos<='9')
					{
						UINT tmpId=atoi(pos);
						if (tmpId>0 && tmpId<(*GPU)->m_NGPUNIT && GPU[tmpId]) GPU[tmpId]->m_UpdateGroupFlag=1;
						while(*pos && ((*pos>='0' && *pos<='9') || *pos=='.')) pos++;
					}
					else pos++;
		}
}

int GPUnit::GetObjectIdByName(const char *iName)
{
	int ret=-1;

	if (iName)
	{
		if (*iName=='0' && atoi(iName)==0) ret=0;
		else
		if ((ret=atoi(iName))==0)
		{
			char *pname=new char [(int)strlen(iName)+10];
			strcpy(pname,iName);
			char *pos2=strchr(pname,';');
			if (pos2) *pos2=0;
			pos2=strchr(pname,' ');
			if (pos2) *pos2=0;
			ret=-1;
			int iUt;
			for(iUt=0;(UINT)iUt<(*GPU)->m_NGPUNIT && ret<0;iUt++)
				if (GPU[iUt] && GPU[iUt]->m_ObjName.CompareNoCase(pname)==0) ret=iUt;

			delete[] pname;
		}
		if (ret<0 || (UINT)ret>(*GPU)->m_NGPUNIT || GPU==NULL || GPU[ret]==NULL) ret=-1;
	}
	return ret;
}

int GPUnit::GetObjectIdByHWND(HWND iHWND)
{
	int ret=-1;
	if (iHWND)
	{
		int iUt;
		for(iUt=0;(UINT)iUt<(*GPU)->m_NGPUNIT && ret<0;iUt++)
			if (GPU[iUt] && GPU[iUt]->UnitHWND==iHWND) ret=iUt;
	}
	return ret;
}

DWORD GPUnit::ChildCtlColor(GPUnit **iGPU, HDC hDC, HWND iUHWND, HBRUSH & ihbr, HBRUSH ihbrStd, DWORD iType)
{
	DWORD ret=0;
	if (hDC && iGPU && iUHWND)
	{
		if (ihbr==NULL) ihbr=ihbrStd;
		UINT i;
		for(i=0;i<(*iGPU)->m_NGPUNIT;i++)
			if (iGPU[i] && iGPU[i]->UnitHWND==iUHWND)
			{
				if (iGPU[i]->m_BkgMode!=-1) ::SetBkMode(hDC,iGPU[i]->m_BkgMode);
				if (iGPU[i]->m_bkgSrc==-1) ihbr=ihbrStd;
				if (iGPU[i]->m_bkgSrc<(*iGPU)->m_NGPUNIT && iGPU[iGPU[i]->m_bkgSrc] && iGPU[iGPU[i]->m_bkgSrc]->UnitHWND)
				{
					if (iGPU[i]->m_clrBkgnd!=-1)
						::SetBkColor(hDC, iGPU[i]->m_clrBkgnd);
					else
						if (iGPU[iGPU[i]->m_bkgSrc]->m_clrBkgnd!=-1)
							::SetBkColor(hDC, iGPU[iGPU[i]->m_bkgSrc]->m_clrBkgnd);

					if (iGPU[i]->m_clrText!=-1)
						::SetTextColor(hDC, iGPU[i]->m_clrText);
					else
						if (iGPU[iGPU[i]->m_bkgSrc]->m_clrText!=-1)
							::SetTextColor(hDC, iGPU[iGPU[i]->m_bkgSrc]->m_clrText);
						
					if (iGPU[i]->m_brBkgnd)
						ihbr=(HBRUSH)(*iGPU[i]->m_brBkgnd);
					else
						if (iGPU[iGPU[i]->m_bkgSrc]->m_brBkgnd)
							ihbr=(HBRUSH)(*iGPU[iGPU[i]->m_bkgSrc]->m_brBkgnd);
				}
				else
				{
					if (iGPU[i]->m_clrBkgnd!=-1)	::SetBkColor(hDC, iGPU[i]->m_clrBkgnd);
					if (iGPU[i]->m_clrText!=-1)		::SetTextColor(hDC, iGPU[i]->m_clrText);
					if (iGPU[i]->m_brBkgnd) 
						ihbr=(HBRUSH)(*iGPU[i]->m_brBkgnd);
				}
				break;
			}
	}
	return ret;
}


DWORD GPUnit::AddDirectOutputChar(char iChar)
{
	if ((m_DirectOutputFlag&0x1))
	{
		if (!(m_DirectOutputFlag&0x2) && ((m_LastDIChar==10 && iChar==13) || (m_LastDIChar==13 && iChar==10)))
		{
		}
		else
		{
			switch(UnitType)
			{
				case UT_RTF: 			((GP_RTF*)UnitPtr)->AddChar(iChar,m_DirectOutputFlag);			break;
				case UT_EDITOR: 		((GPScintilla*)UnitPtr)->AddChar(iChar,m_DirectOutputFlag);		break;
				case UT_STATIC:			((GPStatic *)UnitPtr)->AddChar(iChar,m_DirectOutputFlag);		break;
				case UT_ANISTATIC:		((GPAniStatic *)UnitPtr)->AddChar(iChar,m_DirectOutputFlag);	break;
				case UT_EDIT:			((GPEdit *)UnitPtr)->AddChar(iChar,m_DirectOutputFlag);			break;
				case UT_LISTBOX:		((GPListBox *)UnitPtr)->AddChar(iChar,m_DirectOutputFlag);		break;
				case UT_COMBOBOX:		((GPComboBox *)UnitPtr)->AddChar(iChar,m_DirectOutputFlag);		break;
				case UT_COMBOBOXEX:		((GPComboBoxEx *)UnitPtr)->AddChar(iChar,m_DirectOutputFlag);	break;
				case UT_PROGRESS:		((GPProgress *)UnitPtr)->AddChar(iChar,m_DirectOutputFlag);		break;
				case UT_CHECKLISTBOX:	((GPChLBox *)UnitPtr)->AddChar(iChar,m_DirectOutputFlag);		break;
				case UT_DRAGLISTBOX:	((GPDrLBox *)UnitPtr)->AddChar(iChar,m_DirectOutputFlag);		break;
				case UT_LISTCTRL: 		((GPListCtr *)UnitPtr)->AddChar(iChar,m_DirectOutputFlag);		break;
				case UT_FLEXGRID:		((GPCMSFlexGrid *)UnitPtr)->AddChar(iChar,m_DirectOutputFlag);	break;
				case UT_WEBBROWSER:		((GPWebBrowser2 *)UnitPtr)->AddChar(iChar,m_DirectOutputFlag);	break;
				case UT_CONTROL:		((GP_Control *)UnitPtr)->AddChar(iChar,m_DirectOutputFlag);		break;
			}
			m_LastDIChar=iChar;
		}
	}
	return m_DirectOutputFlag;
}

const CString GPUnit::GetChangedValue(BOOL bRecursive /*bRecursive = TRUE*/)
{
	CString ret="";
	if (UnitPtr && UnitHWND)
		switch(UnitType)
		{
		case UT_MAINDLGSCR:
			{
				UINT lastI=1;
				UINT i;
				for(i=1; i<(*GPU)->m_NGPUNIT;i++)
					if (GPU[i])
					{
						CString tmpRet=GPU[i]->GetCurrentValue(FALSE);
						DWORD curCRC=calc_CRC16((const BYTE *)((const char *)tmpRet));
						if (curCRC!=GPU[i]->m_LastCRC)
						{
							char tpmss[25];
							while(i>lastI++) ret+="\x7F";
							ret+=_ltoa(curCRC,tpmss,16);
							ret+="\x7";
							tmpRet.Replace(4,6);
							tmpRet.Replace(3,5);
							tmpRet.Replace(2,4);
							tmpRet.Replace(1,3);
							tmpRet.Replace(7,4);
							tmpRet.Replace(127,3);
							ret+=tmpRet;
						}
					}
			}
			break;
		case UT_FRAMEBAR:
		case UT_DLGBAR:
			if (bRecursive)
			{
				UINT lastI=1;
				UINT i;
				for(i=1;i<(*GPU)->m_NGPUNIT;i++)
					if (GPU[i] && GPU[i]->UnitHWND && GPU[i]->UnitHWND!=UnitHWND)
						try
						{
							HWND tmpParent=GPU[i]->UnitHWND;
							if (GPU[i]->IsChildOfThis(UnitHWND)) tmpParent=UnitHWND;
							if (tmpParent==UnitHWND)
							{
								CString tmpRet=GPU[i]->GetCurrentValue(FALSE);
								DWORD curCRC=calc_CRC16((const BYTE *)((const char *)tmpRet));
								if (curCRC!=GPU[i]->m_LastCRC)
								{
									char tpmss[25];
									while(i>lastI++) ret+="\x7F";
									ret+=_ltoa(curCRC,tpmss,16);
									ret+="\x7";
									tmpRet.Replace(4,6);
									tmpRet.Replace(3,5);
									tmpRet.Replace(2,4);
									tmpRet.Replace(1,3);
									tmpRet.Replace(7,4);
									tmpRet.Replace(127,3);
									ret+=tmpRet;
								}
							}
						}
						catch(...)
						{
							GPC.m_ErrReport.GPWriteErrorLog("GPUnit", "GetChangedValue","");
						}
				break;
			}
		default:
			{
				CString tmpRet=GetCurrentValue(bRecursive);
				DWORD curCRC=calc_CRC16((const BYTE *)((const char *)tmpRet));
				if (curCRC!=m_LastCRC)
				{
					char tpmss[25];
					ret+=_ltoa(curCRC,tpmss,16);
					ret+="\x7F";
					tmpRet.Replace(5,6);
					tmpRet.Replace(4,5);
					tmpRet.Replace(3,4);
					tmpRet.Replace(2,3);
					tmpRet.Replace(1,2);
					tmpRet.Replace(7,3);
					tmpRet.Replace(127,2);
					ret=tmpRet;
				}
			}
			break;
	}

	return ret;

}
const CString GPUnit::GetCurrentValue(BOOL bRecursive /*bRecursive = TRUE*/)
{
	CString ret="";
	try
	{
		if (UnitPtr && UnitHWND)
			switch(UnitType)
			{
			case UT_MAINDLGSCR:
				{
					UINT lastI=1;
					UINT i;
					for(i=1; i<(*GPU)->m_NGPUNIT;i++)
						if (GPU[i])
						{
							while(i>lastI++) ret+="\x7F";
							CString tmpRet=GPU[i]->GetCurrentValue(FALSE);
							tmpRet.Replace(5,6);
							tmpRet.Replace(4,5);
							tmpRet.Replace(3,4);
							tmpRet.Replace(2,3);
							tmpRet.Replace(1,2);
							tmpRet.Replace(7,3);
							tmpRet.Replace(127,2);
							ret+=tmpRet;
						}
				}
				break;
			case UT_FRAMEBAR:
			case UT_DLGBAR:
				if (bRecursive)
				{
					UINT lastI=1;
					UINT i;
					for(i=1;i<(*GPU)->m_NGPUNIT;i++)
						if (GPU[i] && GPU[i]->UnitHWND && GPU[i]->UnitHWND!=UnitHWND)
							try
							{
								HWND tmpParent=GPU[i]->UnitHWND;
								if (GPU[i]->IsChildOfThis(UnitHWND)) tmpParent=UnitHWND;
								if (tmpParent==UnitHWND)
								{
									while(i>lastI++) ret+="\x7F";
									CString tmpRet=GPU[i]->GetCurrentValue(FALSE);
									tmpRet.Replace(5,6);
									tmpRet.Replace(4,5);
									tmpRet.Replace(3,4);
									tmpRet.Replace(2,3);
									tmpRet.Replace(1,2);
									tmpRet.Replace(7,3);
									tmpRet.Replace(127,2);
									ret+=tmpRet;
								}
							}
							catch(...)
							{
								GPC.m_ErrReport.GPWriteErrorLog("GPUnit", "GetCurrentValue","");
							}
				}
				else 
					((CWnd *)UnitPtr)->GetWindowText(ret);
				break;
			case UT_CONTROL:
				{
					BSTR mbstrResult=ret.AllocSysString();
					::SendMessage(((GP_Control *)UnitPtr)->tmpWnd->m_hWnd,GPM_AX_GETVALUE,0,(LPARAM)(&mbstrResult));
					ret=mbstrResult;
					::SysFreeString(mbstrResult);
				}
				break;
			case UT_HEADER:
				{
					int nItems=((GPHeader *)UnitPtr)->GetItemCount();
					ret.Format("%d",nItems);
					HD_TEXTFILTER hdtf={0};
					HDITEM hdi={0};
					hdi.type=HDFT_ISSTRING;
					hdi.mask=HDI_FILTER|HDI_WIDTH|HDI_ORDER|HDI_TEXT;
					hdi.pvFilter=&hdtf;

					char tmps[2000];
					char tmps2[2000];
					hdtf.cchTextMax=1990;
					hdi.cchTextMax=1990;
					hdtf.pszText=tmps;
					hdi.pszText=tmps2;
					CString tmpCS;

					int i;
					for(i=0;i<nItems;i++)
					{
						*hdtf.pszText=*hdi.pszText=0;
						((GPHeader *)UnitPtr)->GetItem(i,&hdi);
						tmpCS.Format("\x7F%d\x7%d\x7%s\x7%s",hdi.iOrder,hdi.cxy,hdi.pszText,hdtf.pszText);
						ret+=tmpCS;
					}
				}
				break;
			case UT_DRAW:
			case UT_ANIMAT:
				break;
			case UT_RTF:
				{
					DWORD textLen=((GP_RTF*)UnitPtr)->GetTextLength();
					char *tmps=new char [textLen+textLen+10];
					((GPEdit*)UnitPtr)->DoMethod("GetAllText",tmps);
					ret+=tmps;
					delete[] tmps;
				}
				break;
			case UT_EDIT:
				{
					DWORD //textLen=((GPEdit*)UnitPtr)->GetTextLength();
					textLen=::GetWindowTextLength(UnitHWND);

					char *tmps=new char [textLen+textLen+10];
					((GPEdit*)UnitPtr)->DoMethod("GetAllText",tmps);
					ret+=tmps;
					delete[] tmps;
				}
				break;
			case UT_EDITOR:
				{
					char *tmps=NULL;
					((GPScintilla*)UnitPtr)->GetText(&tmps);
					if (tmps)
					{
						ret=tmps;
						delete[] tmps;
					}
				}
				break;	
			case UT_DATETIMECTRL: 
			case UT_MONTHCAL:	
			case UT_TREECTRL:	
			case UT_SLIDER: 	
			case UT_TABCTRL: 	
			case UT_SPINBUTTON:	
			case UT_COMBOBOX: 	
			case UT_COMBOBOXEX:	
			case UT_SCROLLBAR: 	
			case UT_PROGRESS: 	
			case UT_WEBBROWSER:	
			case UT_FLEXGRID:
				{
					char *oStr=new char [2000];
					*oStr=0;
					switch(UnitType)
					{
					case UT_DATETIMECTRL: 	((GPDateTimeCtrl *)UnitPtr)->DoMethod("GetTime",oStr);	break;
					case UT_MONTHCAL:		((GPMonthCalCtrl *)UnitPtr)->DoMethod("GetCurSel",oStr);	break;
					case UT_TREECTRL:		((GPTree*)UnitPtr)->DoMethod("GetSelectedItem",oStr);	break;
					case UT_SLIDER: 		((GPSlider*)UnitPtr)->DoMethod("GetPos",oStr);			break;
					case UT_TABCTRL: 		((GPTabCtrl*)UnitPtr)->DoMethod("GetCurSel",oStr);		break;
					case UT_SPINBUTTON:		((GPSpinButton*)UnitPtr)->DoMethod("GetPos",oStr);		break;
					case UT_COMBOBOX:
						((GPComboBox*)UnitPtr)->DoMethod("GetCurSel",oStr);
						if (!*oStr) ((GPComboBox*)UnitPtr)->DoMethod("GetEditText",oStr);
						break;
					case UT_COMBOBOXEX:
						((GPComboBoxEx*)UnitPtr)->DoMethod("GetCurSel",oStr);
						if (!*oStr) ((GPComboBox*)UnitPtr)->DoMethod("GetEditText",oStr);
						break;
					case UT_SCROLLBAR: 		((GPScrollBar*)UnitPtr)->DoMethod("GetScrollPos",oStr);	break;
					case UT_PROGRESS: 		((GPProgress*)UnitPtr)->DoMethod("GetPos",oStr);			break;
					case UT_WEBBROWSER:		((GPWebBrowser2 *)UnitPtr)->DoMethod("GetLocationName",oStr);	break;
					case UT_FLEXGRID:		strcpy(oStr,(LPCTSTR)((GPCMSFlexGrid *)UnitPtr)->GetText());	break;
					}
					ret=oStr;
					delete[] oStr;
				}
				break;
			case UT_LISTBOX: 	
			case UT_CHECKLISTBOX:
			case UT_DRAGLISTBOX:
			case UT_LISTCTRL: 	
				{
					char *oStr=new char [100000];
					*oStr=0;
					switch(UnitType)
					{
					case UT_LISTBOX: 		((GPListBox*)UnitPtr)->DoMethod("GetSelItems",oStr);	break;
					case UT_CHECKLISTBOX:	((GPChLBox*)UnitPtr)->DoMethod("GetChecked",oStr);	break;
					case UT_DRAGLISTBOX:	((GPDrLBox*)UnitPtr)->DoMethod("GetSelectedItem",oStr);	break;
					case UT_LISTCTRL: 		((GPListCtr*)UnitPtr)->	DoMethod("GetSelected",oStr);	break;
					}
					ret=oStr;
					delete[] oStr;
				}
				break;

			case UT_ANISTATIC:
			case UT_ANIBUTTON:
			case UT_BBUTTON:
			case UT_STATIC:
			case UT_BUTTON:
			case UT_STATUSBARCTRL:
			case UT_TOOLBARCTRL:
			case UT_STATUSBAR:
			case UT_DIALOGBAR:
			case UT_REBARCTRL:
			case UT_TOOLBAR:
			default:
				((CWnd *)UnitPtr)->GetWindowText(ret);
				break;
		}// end TypeUnit Switch
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPUnit", "GetCurrentValue",UnitInfoToString("\x01"));
	}

	return ret;
}

DWORD GPUnit::GetCurrentValueCRC()
{
	return calc_CRC16((const BYTE *)((const char *)GetCurrentValue()));
}

void GPUnit::SetCheckPoint()
{
	m_LastCRC=GetCurrentValueCRC();
}
void GPUnit::SetValChangeCheckPoint()
{
	m_csLastValueForValChange=GetCurrentValue();
	m_LastValChangeCRC= calc_CRC16((const BYTE *)((const char *)m_csLastValueForValChange));
}

DWORD GPUnit::SelectionAction(DWORD action, LPRECT lpRe)
{
	CRect crect;
	CRect crect2;
	RECT re2={0};
	DWORD ret=0;
	DWORD i;
	BOOL bCmpRect=((action&DLGED_SELACTUSERECT)==DLGED_SELACTUSERECT);
	action&=(0xFFFFFFFF^DLGED_SELACTUSERECT);
	if (!lpRe) bCmpRect=FALSE;
	else
	{
		crect2=*lpRe;
		crect2.NormalizeRect();
		if (crect2.Width()<1) crect2.right++;
		if (crect2.Height()<1) crect2.bottom++;
	}

	switch(action)
	{
	case DLGED_SELACTADD:
		{
			for(i=1;i<(*GPU)->m_NGPUNIT;i++)
				if (GPU[i] && GPU[i]->UnitHWND && ::GetParent(GPU[i]->UnitHWND)==UnitHWND)
				{
					if (bCmpRect) ::GetWindowRect(GPU[i]->UnitHWND,&re2);
					if (!bCmpRect || crect.IntersectRect(&crect2,&re2))
					{
						ret=i;
						GPU[i]->dwWndEditFlag|=DLGED_STATESELECTED;
					}
				}
			if (ret) SelectionAction(DLGED_SELACTSETMAIN|DLGED_SELACTUSERECT,&crect2);
		}
		break;
	case DLGED_SELACTREM:		
		{
			DWORD dwLastSelected=0;
			for(i=1;i<(*GPU)->m_NGPUNIT && !ret;i++)
				if (GPU[i] && GPU[i]->UnitHWND && ::GetParent(GPU[i]->UnitHWND)==UnitHWND
					&& (GPU[i]->dwWndEditFlag&DLGED_STATESELECTED))
				{
					if (bCmpRect) GetWindowRect(GPU[i]->UnitHWND,&re2);
					if (!bCmpRect || crect.IntersectRect(&crect2,&re2))
					{
						GPU[i]->dwWndEditFlag&=(0xFFFFFFFF^(DLGED_STATEMAJOR|DLGED_STATESELECTED));
						dwLastSelected=i;
					}
				}
		}
		break;
	case DLGED_SELACTCLR:		
		for(i=1;i<(*GPU)->m_NGPUNIT;i++)
			if (GPU[i] && GPU[i]->UnitHWND && ::GetParent(GPU[i]->UnitHWND)==UnitHWND)
			{
				if (bCmpRect) GetWindowRect(GPU[i]->UnitHWND,&re2);
				if (!bCmpRect || crect.IntersectRect(&crect2,&re2))
				{
					GPU[i]->dwWndEditFlag&=(0xFFFFFFFF^(DLGED_STATEMAJOR|DLGED_STATESELECTED));
				}
			}
		break;
	case DLGED_SELACTINV:		
		{
			DWORD dwLastSelected=0;
			for(i=1;i<(*GPU)->m_NGPUNIT && !ret;i++)
				if (GPU[i] && GPU[i]->UnitHWND && ::GetParent(GPU[i]->UnitHWND)==UnitHWND)
				{
					if (bCmpRect) GetWindowRect(GPU[i]->UnitHWND,&re2);
					if (!bCmpRect || crect.IntersectRect(&crect2,&re2))
					{
						GPU[i]->dwWndEditFlag^=DLGED_STATESELECTED;
						GPU[i]->dwWndEditFlag&=(0xFFFFFFFF^DLGED_STATEMAJOR);
					}
				}
		}
		break;
	case DLGED_SELACTALLADD:
		for(i=1;i<(*GPU)->m_NGPUNIT;i++)
			if (GPU[i] && GPU[i]->UnitHWND && ::GetParent(GPU[i]->UnitHWND)==UnitHWND)
			{
				GPU[ret=i]->dwWndEditFlag|=DLGED_STATESELECTED;
			}
		break;
	case DLGED_SELACTALLREM:		
		for(i=1;i<(*GPU)->m_NGPUNIT;i++)
			if (GPU[i] && GPU[i]->UnitHWND && ::GetParent(GPU[i]->UnitHWND)==UnitHWND)
			{
				GPU[ret=i]->dwWndEditFlag&=(0xFFFFFFFF^(DLGED_STATEMAJOR|DLGED_STATESELECTED));
			}
		break;
	case DLGED_SELACTSETMAIN:
		{
			HWND parentHWND=::GetParent(UnitHWND);
			for(i=1;i<(*GPU)->m_NGPUNIT && !ret;i++)
				if (GPU[i] && GPU[i]->UnitHWND && ::GetParent(GPU[i]->UnitHWND)==parentHWND)
				{
					if (bCmpRect) GetWindowRect(GPU[i]->UnitHWND,&re2);
					if ((!bCmpRect || crect.IntersectRect(&crect2,&re2)) && (GPU[i]->dwWndEditFlag&DLGED_STATESELECTED))
					{
						GPU[ret=i]->dwWndEditFlag|=DLGED_STATEMAJOR;
					}
				}
			for(;i<(*GPU)->m_NGPUNIT;i++)
				if (GPU[i] && GPU[i]->UnitHWND && ::GetParent(GPU[i]->UnitHWND)==parentHWND)
				{
					if (bCmpRect) GetWindowRect(GPU[i]->UnitHWND,&re2);
					if ((!bCmpRect || crect.IntersectRect(&crect2,&re2)) && (GPU[i]->dwWndEditFlag&DLGED_STATESELECTED))
					{
						GPU[ret=i]->dwWndEditFlag&=(0xFFFFFFFF^DLGED_STATEMAJOR);
					}
				}
		}
		break;
	case DLGED_SELACTFINDMAIN:	
		for(i=1;i<(*GPU)->m_NGPUNIT && !ret;i++)
			if (GPU[i] && GPU[i]->UnitHWND && ::GetParent(GPU[i]->UnitHWND)==UnitHWND && (GPU[i]->dwWndEditFlag&DLGED_STATEMAJOR) && (GPU[i]->dwWndEditFlag&DLGED_STATESELECTED))
				 ret=i;
		break;
	}
	return ret;
}

LRESULT GPUnit::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
//	TRACE("%X %X %X %d %d\n",message,wParam,lParam,UnitType, UnitId);

	if ((dwWndEditFlag&DLGED_MODEEDIT)) 
	{
		switch(message)
		{
		case WM_LBUTTONDOWN:
			if ((wParam&MK_SHIFT)==MK_SHIFT)
			{
			}
			reMouseSelection.right=reMouseSelection.left=LOWORD(lParam);
			reMouseSelection.bottom=reMouseSelection.top=HIWORD(lParam);
			::ClientToScreen(UnitHWND,(LPPOINT)(&reMouseSelection));
			{
				RECT tmpre;
				::GetWindowRect(UnitHWND,&tmpre);
				if (tmpre.bottom>HIWORD(lParam) || tmpre.top<HIWORD(lParam) || tmpre.right>LOWORD(lParam) || tmpre.left<LOWORD(lParam))
					::ReleaseCapture();
			}
			if (GPU && *GPU) GPU[0]->dwWndEditFlag|=DLGED_STATENEEDREDRAW;
			::SetCapture(UnitHWND);
			break;
		case WM_LBUTTONUP:
			reMouseSelection.right=LOWORD(lParam);
			reMouseSelection.bottom=HIWORD(lParam);
			::ClientToScreen(UnitHWND,((LPPOINT)(&reMouseSelection))+1);
			if (GPU && *GPU)
			{
				switch((wParam&(MK_CONTROL|MK_SHIFT)))
				{
				case MK_CONTROL:
					SelectionAction(DLGED_SELACTINV|DLGED_SELACTUSERECT,&reMouseSelection);
					break;
				case MK_SHIFT:
					SelectionAction(DLGED_SELACTADD|DLGED_SELACTUSERECT,&reMouseSelection);
					break;
				}
				GPU[0]->dwWndEditFlag|=DLGED_STATENEEDREDRAW;
			}

	//		::SetCapture(UnitHWND);
			break;
		case WM_MOUSEMOVE:
			if ((wParam&MK_LBUTTON)==MK_LBUTTON)
			{
				reMouseSelection.right=LOWORD(lParam);
				reMouseSelection.bottom=HIWORD(lParam);
				::ClientToScreen(UnitHWND,((LPPOINT)(&reMouseSelection))+1);
				if (GPU && *GPU) GPU[0]->dwWndEditFlag|=DLGED_MODESELECTION;
				if (GPU && *GPU) GPU[0]->dwWndEditFlag|=DLGED_STATENEEDREDRAW;
			}
			::SetCapture(UnitHWND);
			break;
		case WM_NCMOUSEMOVE:
		case WM_NOTIFY:
			break;

		case WM_TIMER:
			if (wParam==DLGEDITOR_TIMER_ID && GPU && *GPU)
			{
				::KillTimer(UnitHWND,DLGEDITOR_TIMER_ID);
				if ((GPU[0]->dwWndEditFlag&DLGED_STATENEEDREDRAW))
				{
					Pen mPenParent(Color(200,255,111,0),4);
					Pen mPenSelected(Color(200,111,111,255),4);
					Pen mPenSelectedMain(Color(200,0,111,255),4);
					Pen mPenSelection(Color(200,111,0,111),2);
					Pen mPenNumbers(Color(255,255,100,100),1);
					RECT re={0};
					::GetClientRect(UnitHWND,&re);
					::RedrawWindow(UnitHWND,&re,NULL,RDW_ERASE);
					Graphics gr(UnitHWND);

					gr.DrawRectangle(&mPenParent,0,0,re.right,re.bottom);

					Font fnttmp(L"Arial",10);
					SolidBrush m_br(Color(255,255,0,0));
					LinearGradientBrush m_brGR(PointF(0,0),PointF(5,5),Color(180,222,222,100),Color(180,100,222,222));
					PointF po_f;

				
					DWORD i;
					WCHAR wcst[20];
					char tmps[20];

					for(i=1;i<(*GPU)->m_NGPUNIT;i++)
						if (GPU[i] && GPU[i]->UnitHWND && ::GetParent(GPU[i]->UnitHWND)==UnitHWND && (GPU[i]->dwWndEditFlag&(DLGED_STATEMAJOR|DLGED_STATESELECTED)))
						{
							::GetWindowRect(GPU[i]->UnitHWND,&re);
							::ScreenToClient(UnitHWND,(LPPOINT)(&re));
							::ScreenToClient(UnitHWND,((LPPOINT)(&re))+1);
							
							if ((GPU[i]->dwWndEditFlag&DLGED_STATEMAJOR))
							{
								gr.DrawRectangle(&mPenSelectedMain,re.left,re.top,re.right-re.left+1,re.bottom-re.top+1);
							}
							else
							if ((GPU[i]->dwWndEditFlag&DLGED_STATESELECTED))
							{
								gr.DrawRectangle(&mPenSelected,re.left,re.top,re.right-re.left+1,re.bottom-re.top+1);
							}
						}
					for(i=1;i<(*GPU)->m_NGPUNIT;i++)
						if (GPU[i] && GPU[i]->UnitHWND)
						{
							::GetWindowRect(GPU[i]->UnitHWND,&re);
							::ScreenToClient(UnitHWND,(LPPOINT)(&re));
							po_f.X=(REAL)re.left;
							po_f.Y=(REAL)re.top;
							int n=sprintf(tmps,"%d",i);
							gr.FillRectangle(&m_brGR,po_f.X,po_f.Y,20.,15.);
							gr.DrawRectangle(&mPenNumbers,po_f.X,po_f.Y,20.,15.);

							MultiByteToWideChar(CP_ACP, 0,tmps , -1, wcst, 10);
							gr.DrawString(wcst,n,&fnttmp,po_f,&m_br);

						}

				}
				GPU[0]->dwWndEditFlag&=(0xFFFFFFFF^DLGED_STATENEEDREDRAW);
				::SetTimer(UnitHWND,DLGEDITOR_TIMER_ID,100,NULL);
			}
			break;
		}
		switch(message)
		{
		case WM_MOUSEMOVE:
		case WM_NCMOUSEMOVE:
		case WM_NOTIFY:
			break;
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
			{
				RECT re={0};
				::GetClientRect(UnitHWND,&re);
				::InvalidateRect(UnitHWND,&re,1);
			}
			break;

		case WM_TIMER:
			break;
		}
	}
	else
	{
		switch(message)
		{
		case WM_LBUTTONDOWN:
			if (GPU && *GPU) GPU[0]->dwWndEditFlag|=DLGED_STATENEEDREDRAW;
			if ((wParam&MK_CONTROL)!=MK_CONTROL)
			{
				reMouseSelection.right=reMouseSelection.left=LOWORD(lParam);
				reMouseSelection.bottom=reMouseSelection.top=HIWORD(lParam);
			}
			break;
		case WM_LBUTTONUP:
			if (GPU && *GPU) GPU[0]->dwWndEditFlag|=DLGED_STATENEEDREDRAW;
			reMouseSelection.right=LOWORD(lParam);
			reMouseSelection.bottom=HIWORD(lParam);
			break;
		case WM_MOUSEMOVE:
			if (GPU && *GPU) GPU[0]->dwWndEditFlag|=DLGED_STATENEEDREDRAW;
			if ((wParam&MK_LBUTTON)==MK_LBUTTON)
			{
				reMouseSelection.right=LOWORD(lParam);
				reMouseSelection.bottom=HIWORD(lParam);
			}
			break;

		case WM_SIZE:
		case WM_SIZECHILD:
		case WM_SIZEPARENT:
		case WM_PAINT:
		//case WM_NCPAINT:
		//case WM_NCMOUSEMOVE:
		case WM_NOTIFY:
			if (GPU && *GPU) GPU[0]->dwWndEditFlag|=DLGED_STATENEEDREDRAW;
			break;
		}
	}


	switch(message)
	{
	case WM_MOUSEWHEEL:
		if (GPMSG->FindInActive("OnLockWheel"))
		{
			char str[1500];
			char *poslast=str;
			CRect re;
			::GetWindowRect(UnitHWND,re);
			POINT po1={lParam&0xFFFF,lParam/0x10000};
			int isinrect=re.PtInRect(po1);
			::ScreenToClient(UnitHWND,&po1);
			short wDistanse=HIWORD(wParam);
			poslast+=sprintf(poslast,"%d\x7%d\x7F%d\x7%d\x7F%d\x7F%d\x7F",
				    (UINT)(lParam&0xFFFF),(UINT)(lParam/0x10000),
					po1.x,po1.y,
					wDistanse,
					isinrect
				);
			isinrect=(wParam&0xFFFF);
			DWORD keyfl[]={MK_CONTROL,MK_LBUTTON,MK_MBUTTON,MK_RBUTTON,MK_SHIFT,MK_XBUTTON1,MK_XBUTTON2,};
			char *keyflname[]={"MK_CONTROL","MK_LBUTTON","MK_MBUTTON","MK_RBUTTON","MK_SHIFT","MK_XBUTTON1","MK_XBUTTON2",};

			int nn;
			for(nn=0;nn<7;nn++)
				if ((isinrect&keyfl[nn])==keyfl[nn])
				{
					if (*poslast) strcat(poslast,"|");
					strcat(poslast,keyflname[nn]);
				}

			GPMSG->GPSendObjEvent(UnitHWND, UnitId,"OnLockWheel",str);
			return TRUE;
		}
		if (GPUnit::MouseWheelProc(wParam, lParam)) return TRUE;
		break;
		
	case WM_DRAWITEM:
		if (UnitType!=UT_CHECKLISTBOX && lParam)
		{
			LPDRAWITEMSTRUCT lpds=(LPDRAWITEMSTRUCT) lParam;
			if (lpds->CtlType==ODT_MENU)
			{
				GPC.m_View->m_ODContextsArray->PaintByDRAWITEMSTRUCT(this, wParam, lpds, GPC.m_View->m_GPMenu);
				return TRUE;
			}
			else
				if (lpds->CtlID==(UnitId&0x7FFFFFF)+50000)
				{
					GPC.m_View->m_ODContextsArray->PaintByDRAWITEMSTRUCT(this, wParam, lpds, GPC.m_View->m_GPMenu);
					return TRUE;
				}
		}
		break;

	case WM_MEASUREITEM:
		if (UnitType!=UT_CHECKLISTBOX && lParam)
		{
			LPMEASUREITEMSTRUCT lpds=(LPMEASUREITEMSTRUCT) lParam;
			if (lpds->CtlType==ODT_MENU)
				return GPC.m_View->m_ODContextsArray->MeasureItem(this, wParam, lpds, GPC.m_View->m_GPMenu);
			else
				if (lpds->CtlID==(UnitId&0x7FFFFFF)+50000)
					return GPC.m_View->m_ODContextsArray->MeasureItem(this, wParam, lpds, GPC.m_View->m_GPMenu);
		}
		break;

	case WM_DESTROY:
		if (m_ptrUnitValChange==this) 
		{
			m_ptrUnitValChange=NULL;
//				TRACE("m_ptrUnitValChange=NULL WM_DESTROY %s\n",UnitInfoToString("\x01") );
		}
		break;
	case WM_SYSCHAR:
		return 1;
	case WM_SYSKEYDOWN:
		SendMessage(UnitHWND,GPM_PROCHOTKEY, wParam,lParam);
		break;
	case GPM_SETFOCUSTOWND:
		if (::GetFocus()!=(HWND)wParam && ::IsWindow((HWND)wParam)) ::SetFocus((HWND)wParam);
		break;
	case WM_TIMER:
		if (GPMSG)
		{
			GPMSG->ProcMessagerTimer(wParam,UnitHWND);
			if (::IsWindow(UnitHWND))
			{
				if (wParam>=20000 && wParam<20020)
				{
					UINT nId=wParam-20000;
					BOOL delMsg=FALSE;
					if ((delMsg=(--iArrTimerCount[nId]==0 || iArrTimerCount[nId]==0-iArrTimerCount[nId+20])))
						::KillTimer(UnitHWND,wParam);
					char str[100];
					sprintf(str,"%d\x7F%ld\x7F%ld",nId,(iArrTimerCount[nId]&0x10000000)?0-iArrTimerCount[nId]:iArrTimerCount[nId],iArrTimerCount[nId+20]);
					GPMSG->GPSendObjEvent(UnitHWND, UnitId,"OnTimer",str);
					if (delMsg) GPDeleteMessage("ONTIMER");
				}
			}
		}
		break;

	case WM_SETFONT:
		if ((UnitId)&0xFFFF)
		{
			if (wParam)
			{
				CFont *tmp=((CWnd *)UnitPtr)->GetFont( );
				if (tmp)
				{
					if ((HFONT)(*tmp)!=(HFONT)wParam)
					{
						if (UnitFont)
						{
							delete UnitFont;
							UnitFont=NULL;
						}
					}
					else return 1;
				}
				else
				{
					if (GPU && *GPU && GPU[0]->UnitFont && (HFONT)(*(GPU[0]->UnitFont))!=(HFONT)wParam) 
					{
						SetFont(GPU[0]->UnitFont);
						return 1;
					}
				}
			}
			else
			{
				if (UnitFont)
				{
					delete UnitFont;
					UnitFont=NULL;
				}
				if (GPU && *GPU && GPU[0]->UnitFont)
					SetFont(GPU[0]->UnitFont);
				else
					SetFont(CWnd::FromHandle(GetParent(UnitHWND))->GetFont());
				return 1;
			}

		}

		break;
	case GPM_GETOBJECTNAME:
		if (wParam && lParam)
		{
			if (m_ObjName=="")
				sprintf((char *)lParam,"%d",(UnitId&0xFFFF));
			else
			{
				strncpy((char *)lParam,m_ObjName,wParam);
				if ((DWORD)m_ObjName.GetLength()>wParam) ((char *)lParam)[wParam]=0;
			}
		}
		break;
	case WM_SETFOCUS:
		{
			if (m_ptrUnitValChange && m_ptrUnitValChange!=this) m_ptrUnitValChange->SendOnValChangeEvent(0);
			if ((m_dwValChangeFlag&0x1) && UnitHWND && ::IsWindow(UnitHWND)) 
			{
				m_ptrUnitValChange=this;
//				TRACE("m_ptrUnitValChange=this %s\n",UnitInfoToString("\x01") );
				SetValChangeCheckPoint();
			}
			else 
			{
				m_ptrUnitValChange=NULL;
//				TRACE("m_ptrUnitValChange=NULL WM_SETFOCUS %s\n",UnitInfoToString("\x01") );
			}
		}
		break;
	case WM_KILLFOCUS:
		{
			if (m_ptrUnitValChange) m_ptrUnitValChange->SendOnValChangeEvent(0);
			m_ptrUnitValChange=NULL;
//			TRACE("m_ptrUnitValChange=NULL WM_KILLFOCUS %s\n",UnitInfoToString("\x01") );
		}
		break;
	case WM_MOUSEACTIVATE:
		{
			if (m_ptrUnitValChange)
			{
				if (m_ptrUnitValChange!=this)
					m_ptrUnitValChange->SendOnValChangeEvent(0);
				else 
					if (::GetFocus()==UnitHWND) return 1;
			}
			
		}
		break;
	case WM_MENUCOMMAND:
		{
			if (m_ptrUnitValChange)
			{
				m_ptrUnitValChange->SendOnValChangeEvent(0);
			}
		}
		break;
	case WM_SYSCOMMAND:
		{
			if (m_ptrUnitValChange && m_ptrUnitValChange!=this)
			{
				m_ptrUnitValChange->SendOnValChangeEvent(0);
			}
		}
		break;
	case EM_SETSEL:
		if (m_IgnoreSelectionOnTAB && (m_IgnoreMessages&0x00000001))
		{
			m_IgnoreMessages&=(0xFFFFFFFF^0x00000001);
			if (!(m_IgnoreSelectionOnTAB&0x2)) ::PostMessage(UnitHWND,message,-2,-1);
			return 1;
		}
		m_IgnoreMessages&=(0xFFFFFFFF^0x00000001);
		break;
	case GPN_DRAWMOVE:
/*
		if (lParam && ((PDRAWMOVE)lParam)->hWndMove)
		{
			PDRAWMOVE pdm=(PDRAWMOVE)lParam;
			CRect re(0,0,0,0);
			if ((UINT)pdm->nRect < pdm->pODContext->m_nRectArray) re=pdm->pODContext->m_RectArr[lParam];
				else
				if (pdm->nRect < 0 && (UINT)(-pdm->nRect-1)*4< pdm->pODContext->m_nDoubleArray)
				{
					int nRect;
					re.left=(int)pdm->pODContext->m_DoubleArr[nRect=(-pdm->nRect-1)*4];
					re.top=(int)pdm->pODContext->m_DoubleArr[nRect+1];
					re.right=(int)pdm->pODContext->m_DoubleArr[nRect+2];
					re.bottom=(int)pdm->pODContext->m_DoubleArr[nRect+3];
				}
			if (!re.IsRectEmpty())
				::MoveWindow(pdm->hWndMove,re.left,re.top,re.Width(),re.Height(),TRUE);
		}
		*/
		break;
	case GPM_DOMETHOD:
		if (lParam)
		{
			char *strMeth=(char *) lParam;
			if (*strMeth) DoMethod(strMeth,NULL);
			delete []strMeth;
		}
		break;
	}

	return 0;
}

BOOL GPUnit::DefPreTranslateMessage(MSG *pMsg)
{
	// return 1 if need dispatch
	if (GPC.m_Twain && GPC.m_Twain->m_hWnd==UnitHWND)
		GPC.m_Twain->ProcessMessage(*pMsg);

	switch(pMsg->message)
	{
	case WM_GETDLGCODE:
		TRACE("WM_GETDLGCODE %d %d\n",UnitType, UnitId);
		break;
	case WM_KEYDOWN:
		if (pMsg->wParam==9)
			m_IgnoreMessages|=0x00000001;
		else 
			m_IgnoreMessages&=(0xFFFFFFFF^0x00000001);

		//TRACE("WM_KEYDOWN DefPreTranslateMessage %X %X %X %X\n",UnitHWND,pMsg->hwnd,pMsg->wParam,pMsg->lParam);
		if (m_KeyRedefine)
		{
			DWORD ModWinIsPressed=(GetAsyncKeyState(VK_RWIN)&0xFF00)!=0 || (GetAsyncKeyState(VK_LWIN)&0xFF00)!=0?MOD_WIN:0;
			DWORD ShiftIsPressed=(GetAsyncKeyState(MOD_SHIFT)&0xFF00)!=0 || (GetAsyncKeyState(VK_RSHIFT)&0xFF00)!=0 || (GetAsyncKeyState(VK_LSHIFT)&0xFF00)!=0?MOD_SHIFT:0;
			DWORD CtrlIsPressed=(GetAsyncKeyState(VK_CONTROL)&0xFF00)!=0 || (GetAsyncKeyState(VK_RCONTROL)&0xFF00)!=0 || (GetAsyncKeyState(VK_LCONTROL)&0xFF00)!=0?MOD_CONTROL:0;
			DWORD AltIsPressed=(GetAsyncKeyState(MOD_ALT)&0xFF00)!=0 || (GetAsyncKeyState(VK_RMENU)&0xFF00)!=0 || (GetAsyncKeyState(VK_LMENU)&0xFF00)!=0 ?MOD_ALT:0;

			DWORD CurVk=pMsg->wParam*0x10000+ShiftIsPressed+CtrlIsPressed+ModWinIsPressed+AltIsPressed;

			if (m_KeyRedefine->IsIdInArray(CurVk))
			{
				CString curMethodStrArr=(*m_KeyRedefine)[CurVk].csMethods;
				CString ccTmp;
				DWORD resultKey=(*m_KeyRedefine)[CurVk].dwDstVK;
				if (curMethodStrArr!="")
					GPC.m_Document->DoAnyMethodScript(curMethodStrArr,UnitId,ccTmp);

				if (!resultKey) return 0;
				pMsg->wParam=HIWORD(resultKey);
			}
		}
		break;
	}
	return 1;
}

void GPUnit::SendOnValChangeEvent(DWORD iType)
{
	CString csCurValue=GetCurrentValue();
	DWORD dwCurCRC=calc_CRC16((const BYTE *)((const char *)csCurValue));


	if (m_LastValChangeCRC!=dwCurCRC)
	{
		const char *ccArrTypes[]={"OBJECT","HOTKEY","MOUSEACTIVATE","MENU","","","","",};
		if (GPMSG->FindInActive("OnValChange"))
		{
			CString csSend;
			csSend.Format("%s\x7F%X\x7F%X\x7F\x7F\x7F",ccArrTypes[iType&7],dwCurCRC,m_LastValChangeCRC);
			csSend+=csCurValue;
			GPMSG->GPSendObjEvent(UnitHWND, UnitId,"OnValChange",(LPCSTR)csSend);
		}

		if (GPMSG->FindInActive("OnValChangeEx"))
		{
			CString csSend;
			csSend.Format("%s\x7F%X\x7F%X\x7F\x7F\x7F",ccArrTypes[iType&7],dwCurCRC,m_LastValChangeCRC);
			CString csTMP=csCurValue;
			csTMP.Replace(0x5,0x6);
			csTMP.Replace(0x4,0x5);
			csTMP.Replace(0x3,0x4);
			csTMP.Replace(0x2,0x3);
			csTMP.Replace(0x1,0x2);
			csTMP.Replace(0x7F,0x2);
			csSend+=csTMP+"\x7F";
			csTMP=m_csLastValueForValChange;
			csTMP.Replace(0x5,0x6);
			csTMP.Replace(0x4,0x5);
			csTMP.Replace(0x3,0x4);
			csTMP.Replace(0x2,0x3);
			csTMP.Replace(0x1,0x2);
			csTMP.Replace(0x7F,0x2);
			csSend+=csTMP;
			GPMSG->GPSendObjEvent(UnitHWND, UnitId,"OnValChangeEx",(LPCSTR)csSend);
		}
		m_csLastValueForValChange=csCurValue;
		m_LastValChangeCRC=dwCurCRC;
	}
}


BOOL GPUnit::MouseWheelProc(WPARAM wParam, LPARAM lParam)
{
	BOOL ret=FALSE;
	POINT po;
	GetCursorPos(&po);
	HWND scrlWnd=::WindowFromPoint(po);
	if (scrlWnd)
	{
		int i=0;
		DWORD dwStl=0;
		while(i++<5 && !((dwStl=::GetWindowLong(scrlWnd,GWL_STYLE))&(WS_VSCROLL|WS_HSCROLL)))
		{
			scrlWnd=::GetParent(scrlWnd);
		}

		{
			WPARAM tmpWparam=0;
			short sDelta=HIWORD(wParam);
			int postmp=0;
			int nTimes=1;
			DWORD dwTypes[]={
					SB_LINEUP,SB_PAGEUP,SB_TOP,
					SB_LINEDOWN,SB_PAGEDOWN,SB_BOTTOM,
				};
			if (sDelta<0)
			{
				postmp+=3;
				sDelta=-sDelta;
			}
			switch(LOWORD(wParam))
			{
			case MK_CONTROL|MK_SHIFT:
				postmp+=2;
				break;
			case MK_CONTROL:
				postmp+=1;
				break;
			case MK_SHIFT:
				postmp+=1;
				nTimes=3;
				break;
			default:
				nTimes=3;
				break;
			}
			ret=TRUE;
			for(i=0;i<nTimes;i++)
				::SendMessage(scrlWnd,(dwStl&WS_VSCROLL)||!(dwStl&WS_HSCROLL)?WM_VSCROLL:WM_HSCROLL,dwTypes[postmp],NULL);
		}
	}
	return ret;
}