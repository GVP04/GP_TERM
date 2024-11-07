// GPScreen.cpp: implementation of the GPScreen class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GP_term.h"
#include "GPScreen.h"
#include "GP_TermDoc.h"
#include "GP_TermView.h"
#include "ODContextItem.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

REAL GPScreen::ScrLeftBorder;
REAL GPScreen::ScrRightBorder;
REAL GPScreen::ScrTopBorder;
REAL GPScreen::ScrBottomBorder;

REAL GPScreen::ScrLeftPageMargin;
REAL GPScreen::ScrRightPageMargin;
REAL GPScreen::ScrTopPageMargin;
REAL GPScreen::ScrBottomPageMargin;

REAL GPScreen::ScrFontDeltaX;
REAL GPScreen::ScrFontDeltaY;

REAL GPScreen::ScrFontOfsetX;
REAL GPScreen::ScrFontOfsetY;

REAL GPScreen::ScrScaleHeightToWidth;

DWORD GPScreen::ScrPrintBorders;
DWORD GPScreen::ScrPrintInvert;

DWORD GPScreen::ScrSizeScaleFlags;

DWORD GPScreen::ScrScaleFlags;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const UINT GPScreen::uNMethods=105;
const char *GPScreen::cArrMethods[]={
/*00*/		"SetBorders",		"GetBorders",		"SetPageMargins",		"GetPageMargins",		"SetBkgColor",
/*05*/		"GetBkgColor",		"Invalidate",		"Redraw",				"SetFrgColor",			"GetFrgColor",
/*10*/		"SetChrStyle",		"GetChrStyle",		"ModifyChrStyle",		"GetScreenSize",		"GetMethods",
/*15*/		"DrawCharRect",		"DrawCharLine",		"FillCharRect",			"CharShadow",			"GetBordersColor",
/*20*/		"SetBordersColor",	"DeleteAllObjects",	"SetExPrefixPosition",	"GetNearestChars",		"RedrawRect",
/*25*/		"CharOutW",			"CharOutAW",		"DelLine",				"InsertLine",			"InsertChar",
/*30*/		"DelChar",			"GetActiveWindow",	"CreateWindow",			"WndSetState",			"WndForward",
/*35*/		"WndBackward",		"SelectWindow",		"DeleteWindow",			"LoadScrRgn",			"GetScrScrollState",
/*40*/		"SetScrScrollState","LineOut",			"GetCursorState",		"SetCursorState",		"SetChrSpace",
/*45*/		"GetChrSpace",		"SetChrColorIndex",	"SetBkgColorIndex",		"GetChrColorIndex",		"GetBkgColorIndex",
/*50*/		"SetReverseVideo",	"GetReverseVideo",	"ClearScreen",			"InvalidateScreenBorder","ClearEndOfScreen",
/*55*/		"ClearEndOfLine",	"CursorMoveCR",		"CursorMoveLF",			"SetCursorPosition",	"GetCursorPosition",
/*60*/		"CursorMoveUp",		"CursorMoveDown",	"CursorMoveRight",		"CursorMoveLeft",		"ScrollDown",
/*65*/		"ScrollUp",			"ScrollLeft",		"ScrollRight",			"GetBlinkPoints",		"DeleteSaveScrRgn",
/*70*/		"CopySaveScrRgn",	"UpdateSaveScrRgn",	"SaveScrRgn",			"EnableScrSaving",		"ScrPrint",
/*75*/		"ScreenToBitmap",	"SetViewSize",		"IsScrSaveEnable",		"IsScrViewEnable",		"GetCharPosByWndPos",
/*80*/		"SetNeedRedraw",	"SetNeedRepaint",	"RepaintRect",			"GetScreenContent",		"SetScreenContent",
/*85*/		"SetFontTune",		"GetFontTune",		"SetHeightToWidth",		"GetHeightToWidth",		"SetPrintBorders",
/*90*/		"GetPrintBorders",	"SetPrintInvert",	"GetPrintInvert",		"SetScaleFlags",		"GetScaleFlags",
/*95*/		"GetBordersActual",	"ModifyBkgColor",	"ModifyFrgColor",		"ModifyTermCmdMask",	"ClearToBeginOfLine",
/*100*/		"CharOutGRUC",		"SetConvFlags",		"GetConvFlags",			"SetInsertMode",		"GetInsertMode",
/*105*/		"",	"",	"",	"",	"",
/*110*/		"",	"",	"",	"",	"",
/*115*/		"",	"",	"",	"",	"",
	};

const char *GPScreen::cArrMethodsParams[]={
/*00*/		"[Left],[Right],[Top],[Bottom]",	"",	"[Left],[Right],[Top],[Bottom]",	"",	"color[;X,Y,CX,CY]",
/*05*/		"",		"[X,Y,CX,CY]",	"[X,Y,CX,CY]",	"color[;X,Y,CX,CY]",	"",
/*10*/		"Style[,X,Y,CX,CY]",	"",	"StyleToDelete[,[StyleToAdd][,X,Y,CX,CY]]",	"",	"[Type]",
/*15*/		"X,Y,Width,Height[,CharOrType]",	"X1,Y1,X2,Y2[,CharOrType]",	"X,Y,Width,Height,CharCode",	"X,Y,Width,Height,ScaleFrg[,ScaleBkg]",	"",
/*20*/		"color","","[X,Y]","","[X,Y,CX,CY]",
/*25*/		"[X],[Y],CharCode1[,CharCode2[,CharCode3[,...]]]",	"[X],[Y],CharCode1[,CharCode2[,CharCode3[,...]]]","[nLine][,nTimes]",	"[nLine][,nTimes]","[X],[Y][,nTimes[,CharCode]]",
/*30*/		"[X],[Y][,nTimes]","","Width,Height[,X,Y,CX,CY][,ID]",	"WindowId,State",	"WindowId",
/*35*/		"WindowId",	"WindowId",	"WindowId",	"WindowId,X,Y",	"",
/*40*/		"State",	"X,Y;CharLine",	"",	"State",	"CharCode",
/*45*/		"",	"ColorIndex",	"ColorIndex",	"",	"",
/*50*/		"bReverse",	"",	"",	"",	"",
/*55*/		"",	"nTimes",	"nTimes",	"[X],[Y]",	"",
/*60*/		"nTimes",	"nTimes",	"nTimes",	"nTimes",	"nTimes",
/*65*/		"nTimes",	"nTimes",	"nTimes",	"",		"RgnNum",
/*70*/		"RgnNum[,X,Y]",	"RgnNum",	"RgnNum[,X,Y,CX,CY]",	"bEnable",	"[TypeDlg],[Orient],[Paper][,[],[],[LeftPageMargin],[RightPageMargin],[TopPageMargin],[BottomPageMargin],[ScaleHeightToWidth],[ScaleFlags],[PrintBorders],[Invert]]",
/*75*/		"ContextName,BitmapId,BitmapWidth,BitmapHeight,format,dwFlags",	"[CX],[CY]",	"",	"",	"X,Y",
/*80*/		"bNeed",	"bNeed",	"[X,Y[,CX,CY]]",	"Type[,X,Y,CX,CY]",	"Type[,X,Y,CX,CY];Content",
/*85*/		"[OffsetX],[OffsetY],[DCX][,DCY]",	"Scale",	"",	"dwFlags",	"",
/*90*/		"",	"dwFlags",	"",	"dwFlags",	"",
/*95*/		"",	"[R],[G],[B],[A]",	"[R],[G],[B],[A]",	"[MaskToDelete][,MaskToAdd]",	"",
/*100*/		"UCode",	"Flags",	"",	"",	"bOnOff",
/*105*/		"",	"",	"",	"",	"",
/*110*/		"",	"",	"",	"",	"",
/*115*/		"",	"",	"",	"",	"",
	};


DWORD GPScreen::dwGRConvFlags[]=
		{
	/*128*/  0xFFFFFFFF,0xFFFFFFFF,	/*129*/  0xFFFFFFFF,0xFFFFFFFF,	/*130*/  0xFFFFFFFF,0xFFFFFFFF,
	/*131*/  0x00000000,0x00000000,	/*132*/  0xFFFFFFFF,0xFFFFFFFF,	/*133*/  0xFFFFFFFF,0xFFFFFFFF,
	/*134*/  0xFFFFFFFF,0xFFFFFFFF,	/*135*/  0xFFFFFFFF,0xFFFFFFFF,	/*136*/  0xFFFFFFFF,0xFFFFFFFF,
	/*137*/  0xFFFFFFFF,0xFFFFFFFF,	/*138*/  0xFFFFFFFF,0xFFFFFFFF,	/*139*/  0xFFFFFFFF,0xFFFFFFFF,
	/*140*/  0xFFFFFFFF,0xFFFFFFFF,	/*141*/  0x00000000,0x00000000,	/*142*/  0x00000000,0x00000000,
	/*143*/  0x00000000,0x00000000,	/*144*/  0x00000000,0x00000000,	/*145*/  0xFFFFFFFF,0xFFFFFFFF,
	/*146*/  0xFFFFFFFF,0xFFFFFFFF,	/*147*/  0xFFFFFFFF,0xFFFFFFFF,	/*148*/  0xFFFFFFFF,0xFFFFFFFF,
	/*149*/  0xFFFFFFFF,0xFFFFFFFF,	/*150*/  0xFFFFFFFF,0xFFFFFFFF,	/*151*/  0xFFFFFFFF,0xFFFFFFFF,
	/*152*/  0xFFFFFFFF,0xFFFFFFFF,	/*153*/  0xFFFFFFFF,0xFFFFFFFF,	/*154*/  0x00000000,0x00000000,
	/*155*/  0x00000000,0x00000000,	/*156*/  0xFFFFFFFF,0xFFFFFFFF,	/*157*/  0xFFFFFFFF,0xFFFFFFFF,
	/*158*/  0xFFFFFFFF,0xFFFFFFFF,	/*159*/  0x00000000,0x00000000,	/*160*/  0x00000000,0x00000000,
	/*161*/  0x00000000,0x00000000,	/*162*/  0x00000000,0x00000000,	/*163*/  0x00000000,0x00000000,
	/*164*/  0x00000000,0x00000000,	/*165*/  0x00000000,0x00000000,	/*166*/  0x00000000,0x00000000,
	/*167*/  0x00000000,0x00000000,	/*168*/  0x00000000,0x00000000,	/*169*/  0x00000000,0x00000000,
	/*170*/  0x00000000,0x00000000,	/*171*/  0x00000000,0x00000000,	/*172*/  0x00000000,0x00000000,
	/*173*/  0x00000000,0x00000000,	/*174*/  0x00000000,0x00000000,	/*175*/  0x00000000,0x00000000,
	/*176*/  0x00000000,0x00000000,	/*177*/  0x00000000,0x00000000,	/*178*/  0x00000000,0x00000000,
	/*179*/  0x00000000,0x00000000,	/*180*/  0x00000000,0x00000000,	/*181*/  0x00000000,0x00000000,
	/*182*/  0x00000000,0x00000000,	/*183*/  0x00000000,0x00000000,	/*184*/  0x00000000,0x00000000,
	/*185*/  0x00000000,0x00000000,	/*186*/  0xFFFFFFFF,0xFFFFFFFF,	/*187*/  0x0F000F00,0x0F000000,
	/*188*/  0x00000000,0x00000000,	/*189*/  0x00000000,0x00000000,	/*190*/  0x00000000,0x00000000,
	/*191*/  0xFFFFFFFF,0xFFFFFFFF,	/*192*/  0xFFFFFFFF,0xFFFFFFFF,	/*193*/  0xFFFFFFFF,0xFFFFFFFF,
	/*194*/  0xFFFFFFFF,0xFFFFFFFF,	/*195*/  0x00000000,0x00000000,	/*196*/  0xFFFFFFFF,0xFFFFFFFF,
	/*197*/  0xFFFFFFFF,0xFFFFFFFF,	/*198*/  0xFFFFFFFF,0xFFFFFFFF,	/*199*/  0xFFFFFFFF,0xFFFFFFFF,
	/*200*/  0xFFFFFFFF,0xFFFFFFFF,	/*201*/  0xFFFFFFFF,0xFFFFFFFF,	/*202*/  0xFFFFFFFF,0xFFFFFFFF,
	/*203*/  0xFFFFFFFF,0xFFFFFFFF,	/*204*/  0xFFFFFFFF,0xFFFFFFFF,	/*205*/  0x00000000,0x00000000,
	/*206*/  0x00000000,0x00000000,	/*207*/  0x00000000,0x00000000,	/*208*/  0x00000000,0x00000000,
	/*209*/  0xFFFFFFFF,0xFFFFFFFF,	/*210*/  0xFFFFFFFF,0xFFFFFFFF,	/*211*/  0xFFFFFFFF,0xFFFFFFFF,
	/*212*/  0xFFFFFFFF,0xFFFFFFFF,	/*213*/  0xFFFFFFFF,0xFFFFFFFF,	/*214*/  0xFFFFFFFF,0xFFFFFFFF,
	/*215*/  0xFFFFFFFF,0xFFFFFFFF,	/*216*/  0xFFFFFFFF,0xFFFFFFFF,	/*217*/  0xFFFFFFFF,0xFFFFFFFF,
	/*218*/  0x00000000,0x00000000,	/*219*/  0x00000000,0x00000000,	/*220*/  0xFFFFFFFF,0xFFFFFFFF,
	/*221*/  0xFFFFFFFF,0xFFFFFFFF,	/*222*/  0xFFFFFFFF,0xFFFFFFFF,	/*223*/  0x00000000,0x00000000,
	/*224*/  0x00000000,0x00000000,	/*225*/  0x00000000,0x00000000,	/*226*/  0x00000000,0x00000000,
	/*227*/  0x00000000,0x00000000,	/*228*/  0x00000000,0x00000000,	/*229*/  0x00000000,0x00000000,
	/*230*/  0x00000000,0x00000000,	/*231*/  0x00000000,0x00000000,	/*232*/  0x00000000,0x00000000,
	/*233*/  0x00000000,0x00000000,	/*234*/  0x00000000,0x00000000,	/*235*/  0x00000000,0x00000000,
	/*236*/  0x00000000,0x00000000,	/*237*/  0x00000000,0x00000000,	/*238*/  0x00000000,0x00000000,
	/*239*/  0x00000000,0x00000000,	/*240*/  0x00000000,0x00000000,	/*241*/  0x00000000,0x00000000,
	/*242*/  0x00000000,0x00000000,	/*243*/  0x00000000,0x00000000,	/*244*/  0x00000000,0x00000000,
	/*245*/  0x00000000,0x00000000,	/*246*/  0x00000000,0x00000000,	/*247*/  0x00000000,0x00000000,
	/*248*/  0x00000000,0x00000000,	/*249*/  0x00000000,0x00000000,	/*250*/  0xFFFFFFFF,0xFFFFFFFF,
	/*251*/  0xFFFFFFFF,0xFFFFFFFF,	/*252*/  0x00000000,0x00000000,	/*253*/  0x00000000,0x00000000,
	/*254*/  0x00000000,0x00000000,	/*255*/  0xFFFFFFFF,0xFFFFFFFF,
};



GPScreen::GPScreen(UINT iScrId, Size &iScreenSize, UINT iScrState, UINT iChrStyle)
{
	uScrollLineStart=0;
	uScrollLineEnd=0xFFFFFFFF;
	ScrConvFlags=1;

	dwOldCommandMask=0;

	LeftBorderSafe=LeftBorderC=GPScreen::ScrLeftBorder;
	RightBorderSafe=RightBorderC=GPScreen::ScrRightBorder;
	TopBorderSafe=TopBorderC=GPScreen::ScrTopBorder;
	BottomBorderSafe=BottomBorderC=GPScreen::ScrBottomBorder;

	LeftPageMargin=GPScreen::ScrLeftPageMargin;
	RightPageMargin=GPScreen::ScrRightPageMargin;
	TopPageMargin=GPScreen::ScrTopPageMargin;
	BottomPageMargin=GPScreen::ScrBottomPageMargin;

	FontDeltaX=GPScreen::ScrFontDeltaX;
	FontDeltaY=GPScreen::ScrFontDeltaY;

	FontOfsetX=GPScreen::ScrFontOfsetX;
	FontOfsetY=GPScreen::ScrFontOfsetY;

	ScaleHeightToWidth=GPScreen::ScrScaleHeightToWidth;

	PrintBorders=GPScreen::ScrPrintBorders;
	PrintInvert=GPScreen::ScrPrintInvert;
	SizeScaleFlags=GPScreen::ScrSizeScaleFlags;
	ScaleFlags=GPScreen::ScrScaleFlags;

	dwNeedRedraw=0;
	ScreenBitmap=NULL;
	ScreenPrintBitmap=NULL;
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwCreateScr++;
	ScrId=iScrId;
	ActiveWindow=0;
	ScrState=iScrState;
	ChrStyle=iChrStyle;
	aSavedScr=NULL;
	aGPWindow=NULL;
	aGPWindowRgnSaved=NULL;
	ScreenSize=iScreenSize;
	if (ScreenSize.Width<=0) ScreenSize.Width=80;
	if (ScreenSize.Height<=0) ScreenSize.Height=25;
	nall=ScreenSize.Width * ScreenSize.Height;
	ScreenViewRect.X=ScreenViewRect.Y=0;
	ScreenViewRect.Width=ScreenSize.Width;
	ScreenViewRect.Height=ScreenSize.Height;

	aGPWindowRgnSaved=new GPWindow * [GPMAX_NSAVEDREGION+1];
	if (aGPWindowRgnSaved)
		ZeroMemory(aGPWindowRgnSaved,sizeof(GPWindow *)*(GPMAX_NSAVEDREGION+1));

	aGPWindow=new GPWindow * [GPMAX_NWINDOW+1];
	if (aGPWindow)
	{
		ZeroMemory(aGPWindow,sizeof(GPWindow *)*(GPMAX_NWINDOW+1));
		InvPoints=new DWORD [nall+10];
		ZeroMemory(InvPoints,nall*sizeof(DWORD));
		aGPWindow[0]=new GPWindow(this,0,ScreenSize,ScreenViewRect,ScrState,ChrStyle,dwOldCommandMask);
	}

	WndNumbers=new UINT [GPMAX_NWINDOW+1];
	if (WndNumbers)
		ZeroMemory(WndNumbers,sizeof(UINT)*(GPMAX_NWINDOW+1));
}

GPScreen::~GPScreen()
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwDeleteScr++;
	UINT i;
	if (aSavedScr)
	{
		for(i=0;i<=GPMAX_SAVESCR;i++)
			if (aSavedScr[i]) {delete aSavedScr[i];aSavedScr[i]=NULL;}
		delete[] aSavedScr; aSavedScr=NULL;
	}

	if (aGPWindow)
	{
		for(i=0;i<=GPMAX_NWINDOW;i++)
			if (aGPWindow[i]) {delete aGPWindow[i];aGPWindow[i]=NULL;}
		delete[] aGPWindow; aGPWindow=NULL;
	}

	if (aGPWindowRgnSaved)
	{
		for(i=0;i<=GPMAX_NSAVEDREGION;i++)
			if (aGPWindowRgnSaved[i])
			{
				delete aGPWindowRgnSaved[i];
				aGPWindowRgnSaved[i]=NULL;
			}
		delete[] aGPWindowRgnSaved; aGPWindowRgnSaved=NULL;
	}

	if (WndNumbers)
		delete[] WndNumbers;
	if (InvPoints)
		delete[] InvPoints;
	
	if (ScreenBitmap) delete ScreenBitmap;
	ScreenBitmap=NULL;
	if (ScreenPrintBitmap) delete ScreenPrintBitmap;
	ScreenPrintBitmap=NULL;
}

UINT GPScreen::DoMethod(const char *iStr, char *oStr)
{
	int nfunc=0;
	char met[150];
	strncpy(met,iStr,145);
	met[145]=0;
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	GPWindow *wActive=GPActiveWindow();


	int retint=-123456; 
	int atoipos=atoi(pos);
	const char *pos2=pos;
	while(*pos2!=0 && *pos2!=',' && *pos2!='=') pos2++;
	if (*pos2!=0) pos2++;

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

	switch(nfunc)
	{
	case  0: // SetBorders [Left],[Right],[Top],[Bottom]
		{
			REAL *rCurrent[]={&LeftBorderC,&RightBorderC,&TopBorderC,&BottomBorderC,};
			REAL *rCurrentSafe[]={&LeftBorderSafe,&RightBorderSafe,&TopBorderSafe,&BottomBorderSafe,};
			REAL rDefault[]={GPScreen::ScrLeftBorder,GPScreen::ScrRightBorder,GPScreen::ScrTopBorder,GPScreen::ScrBottomBorder,};
			int i;
			for(i=0;i<4;i++)
			{
				CString tmpCS=ExtractField(pos,i+1,",");
				tmpCS=tmpCS.Trim();
				if (tmpCS!="")
				{
					tmpCS.MakeUpper();
					if (tmpCS[0]=='D') *rCurrentSafe[i]=*rCurrent[i]=rDefault[i];
					else *rCurrentSafe[i]=*rCurrent[i]=(REAL)atof(tmpCS);
				}
			}
			RECT re;
			::GetClientRect(GPC.m_hViewWnd,&re);
			SetViewSize(re.right-re.left+1,re.bottom-re.top+1);
			if (this==GPC.m_Document->GetMainScreen())
				::PostMessage(GPC.m_hViewWnd,GPM_MFUPDATESIZE,0,0);
			//RedrawScr();
		}
	case  1: // GetBorders
		if (oStr) sprintf(oStr,"%g\x7F%g\x7F%g\x7F%g",LeftBorderC,RightBorderC,TopBorderC,BottomBorderC);
		break; 
	case  2: // SetPageMargins [Left],[Right],[Top],[Bottom]
		{
			REAL *rCurrent[]={&LeftPageMargin,&RightPageMargin,&TopPageMargin,&BottomPageMargin,};
			REAL rDefault[]={GPScreen::ScrLeftPageMargin,GPScreen::ScrRightPageMargin,GPScreen::ScrTopPageMargin,GPScreen::ScrBottomPageMargin,};
			int i;
			for(i=0;i<4;i++)
			{
				CString tmpCS=ExtractField(pos,i+1,",");
				tmpCS=tmpCS.Trim();
				if (tmpCS!="")
				{
					tmpCS.MakeUpper();
					if (tmpCS[0]=='D') *rCurrent[i]=rDefault[i];
					else *rCurrent[i]=(REAL)atof(tmpCS);
				}
			}
		}
	case  3: // GetPageMargins
		if (oStr) sprintf(oStr,"%g\x7F%g\x7F%g\x7F%g",LeftPageMargin,RightPageMargin,TopPageMargin,BottomPageMargin);
		break; 
	case  4: // SetBkgColor color[;X,Y,CX,CY]
		{
			const char *posRect=FindField(pos,2,";");
			if (posRect && *posRect)
				aGPWindow[0]->DoMethod(iStr,oStr);
			else
			{
				ARGB newColor=CODContextItem::TranlateColor(pos);
				if (newColor==0x10101) newColor=GPC.DefBkgColor;
				SetBkgColor(newColor,0);
			}
		}
		break; 
	case  5: // GetBkgColor
		if (oStr) 
		{
			Color clr(GetBkgColor());
			sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",clr.GetRed(),clr.GetGreen(),clr.GetBlue(),clr.GetAlpha());
		}
		break; 
	case  6: // Invalidate [X,Y,CX,CY]
		if (*pos)
		{
			Rect re(0,0,ScreenSize.Width,ScreenSize.Height);
			sscanf(pos,"%d,%d,%d,%d",&re.X,&re.Y,&re.Width,&re.Height);
			RepaintRect(re);
		}
		else RepaintScr();
		break; 
	case  7: // Redraw [X,Y,CX,CY]
		{
			Rect re(0,0,ScreenSize.Width,ScreenSize.Height);
			if (*pos)
				sscanf(pos,"%d,%d,%d,%d",&re.X,&re.Y,&re.Width,&re.Height);
			RedrawRect(re);
			SetNeedRedraw();
		}
		break; 
	case  8: // SetFrgColor color[;X,Y,CX,CY]
		{
			const char *posRect=FindField(pos,2,";");
			if (posRect && *posRect)
				aGPWindow[0]->DoMethod(iStr,oStr);
			else
			{
				ARGB newColor=CODContextItem::TranlateColor(pos);
				if (newColor==0x10101) newColor=GPC.DefFrgColor;
				SetChrColor(newColor,0);
			}
		}
		break; 
	case  9: // GetFrgColor
		if (oStr) 
		{
			Color clr(GetChrColor());
			sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",clr.GetRed(),clr.GetGreen(),clr.GetBlue(),clr.GetAlpha());
		}
		break; 
	case  10: // SetChrStyle Style[,X,Y,CX,CY]
		{
			const char *posRect=FindField(pos,2,",");
			if (posRect && *posRect)
				aGPWindow[0]->DoMethod(iStr,oStr);
			else
				SetChrStyle(GPFont::TranslateCharStyle(pos),0);
		}
		break; 
	case  11: // GetChrStyle
		if (oStr)
			strcpy(oStr,GPFont::TranslateCharStyle(GetChrStyle()));
		break; 
	case  12: // ModifyChrStyle StyleToDelete[,[StyleToAdd][,X,Y,CX,CY]]
		{
			const char *posRect=FindField(pos,3,",");
			if (posRect && *posRect)
				aGPWindow[0]->DoMethod(iStr,oStr);
			else
			{
				DWORD newStlToDelete=GPFont::TranslateCharStyle(ExtractField(pos,1,","));
				DWORD newStlToAdd=GPFont::TranslateCharStyle(ExtractField(pos,2,","));
				DWORD dwCurStyle=GetChrStyle();
				dwCurStyle=(dwCurStyle&(0xFFFFFFFF^newStlToDelete))|newStlToAdd;
				SetChrStyle(dwCurStyle,0);
			}
		}
		break; 
	case  13: // GetScreenSize
		if (oStr) sprintf(oStr,"%d\x7F%d",ScreenSize.Width,ScreenSize.Height);
		break; 
	case  14: // GetMethods [Type]
		if (oStr)
		{
			int i;
			char *posout=oStr;
			for(i=0;*GPScreen::cArrMethods[i];i++)
			{
				if (i) *(posout++)=0x7F;
				if (atoipos)
					posout+=sprintf(posout,"%s\x7%s",GPScreen::cArrMethods[i],GPScreen::cArrMethodsParams[i]);
				else
					posout+=sprintf(posout,"%s",GPScreen::cArrMethods[i]);
			}
		}
		break; 
	case  19: // GetBordersColor
		if (oStr) 
		{
			Color clr;
			clr.SetFromCOLORREF(GPC.m_curOutScrBkg);
			sprintf(oStr,"%d\x7F%d\x7F%d",clr.GetRed(),clr.GetGreen(),clr.GetBlue());
		}
		break; 
	case  20: // SetBordersColor color
		{
			const char *posRect=FindField(pos,2,",");
			Color clr(CODContextItem::TranlateColor(pos));
			COLORREF newColor=clr.ToCOLORREF();
			if (newColor==0x10101)
				newColor=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_curOutScrBkg",8);
			GPC.m_curOutScrBkg=newColor;
		}
		break; 
	case  21: // DeleteAllObjects
		DeleteAllObjects();
		RedrawScr();
		SetNeedRedraw();
		break; 
	case  22: // SetExPrefixPosition [X,Y]
		if (!*pos) SetExPerfixPosition();
		else 
		if (wActive) wActive->DoMethod(iStr,oStr);
		break; 
	case  23: // GetNearestChars [X,Y]
	case  25: // CharOutW [X],[Y],CharCode1[,CharCode2[,CharCode3[,...]]]
	case  26: // CharOutAW [X],[Y],CharCode1[,CharCode2[,CharCode3[,...]]]
	case  29: // InsertChar  [X],[Y][,nTimes[,CharCode]]
	case  30: // DelChar [X],[Y][,nTimes]
	case  15: // DrawCharRect X,Y,Width,Height[,CharOrType]
	case  16: // DrawCharLine X1,Y1,X2,Y2[,CharOrType]
	case  17: // FillCharRect X,Y,Width,Height,CharCode
	case  18: // CharShadow X,Y,Width,Height,ScaleFrg[,ScaleBkg]
	case  38: // LoadScrRgn WindowId,X,Y
	case  39: // GetScrScrollState
	case  40: // SetScrScrollState State
	case  41: // LineOut X,Y;CharLine
	case  42: // GetCursorState
	case  43: // SetCursorState State
	case  44: // SetChrSpace CharCode
	case  45: // GetChrSpace
	case  46: // SetChrColorIndex
	case  47: // SetBkgColorIndex
	case  48: // GetChrColorIndex
	case  49: // GetBkgColorIndex
	case  50: // SetReverseVideo
	case  51: // GetReverseVideo
	case  55: // ClearEndOfLine
	case  56: // CursorMoveCR nTimes
	case  57: // CursorMoveLF nTimes
	case  58: // SetCursorPosition [X],[Y]
	case  59: // GetCursorPosition
	case  60: // CursorMoveUp nTimes
	case  61: // CursorMoveDown nTimes
	case  62: // CursorMoveRight nTimes
	case  63: // CursorMoveLeft nTimes
	case  64: // ScrollDown nTimes
	case  65: // ScrollUp nTimes
	case  66: // ScrollLeft nTimes
	case  67: // ScrollRight nTimes
	case  96: // ModifyBkgColor [R],[G],[B],[A]
	case  97: // ModifyFrgColor [R],[G],[B],[A]
	case  99: // ClearToBeginOfLine
	case  100: // CharOutGRUC UCode
	case  103: // SetInsertMode
	case  104: // GetInsertMode bOnOff
		if (wActive) wActive->DoMethod(iStr,oStr);
		break; 
	case  24: // RedrawRect [X,Y,CX,CY]
		{
			Rect re(0,0,ScreenSize.Width,ScreenSize.Height);
			sscanf(pos,"%d,%d,%d,%d",&re.X,&re.Y,&re.Width,&re.Height);
			RedrawRect(re);
		}
		break; 
	case  27: // DelLine [nLine][,nTimes]
		{
			int posScr=*pos?atoi(pos):wActive->GetCursorPosition().Y;
			int nTimes=atoi(FindField(pos,2,","));
			if (nTimes>ScreenSize.Height) nTimes=ScreenSize.Height-1;
			while(nTimes-->0)
				DelLine(posScr);
		}
		break; 
	case  28: // InsertLine [nLine][,nTimes]
		{
			int posScr=*pos?atoi(pos):wActive->GetCursorPosition().Y;
			int nTimes=atoi(FindField(pos,2,","));
			if (nTimes>ScreenSize.Height) nTimes=ScreenSize.Height-1;
			while(nTimes-->0)
				InsertLine(posScr);
		}
		break; 
	case  31: // GetActiveWindow
		retint=ActiveWindow;
		break; 
	case  32: // CreateWindow Width,Height[,X,Y,CX,CY][,ID]
		{
			Size sz(10,10);
			sscanf(pos,"%d,%d",&sz.Width,&sz.Height);
			Rect re(0,0,sz.Width,sz.Height);
			const char *tmppos=FindField(pos,3,",");
			if (tmppos && *tmppos)	sscanf(tmppos,"%d,%d,%d,%d",&re.X,&re.Y,&re.Width,&re.Height);
			retint=GPCreateWindow(sz, re, atoi(FindField(pos,7,",")));
		}
		break; 
	case  33: // WndSetState WindowId,State
		WndSetState(atoipos,atoi(FindField(pos,2,",")));
		break; 
	case  34: // WndForward WindowId
		WndForward(atoipos);
		break; 
	case  35: // WndBackward WindowId
		WndBackward(atoipos);
		break; 
	case  36: // SelectWindow WindowId
		SelectWindow(atoipos);
		break; 
	case  37: // DeleteWindow WindowId
		DeleteWindow(atoipos);
		break; 
	case  52: // ClearScreen
		ClearScreen();
		break; 
	case  53: // InvalidateScreenBorder
		InvalidateScreenBorder();
		break; 
	case  54: // ClearEndOfScreen
		if (wActive) wActive->DoMethod("ClearEndOfWindow",oStr);
		break; 
	case  68: // GetBlinkPoints
		if (oStr)
		{
			GetBlinkPoints(oStr);
			oStr[nall]=0;
			char *pout=oStr;
			UINT i;
			for(i=0;i<nall;i++,pout++)
				if (*pout==0) *pout=' ';
				else *pout='1';
		}
		break; 
	case  69: // DeleteSaveScrRgn
		DeleteSaveScrRgn(atoipos);
		break; 
	case  70: // CopySaveScrRgn RgnNum[,X,Y]
		{
			int RgnNum=0;
			Point po=GetCursorPosition();
			sscanf(pos,"%d,%d,%d",&RgnNum,&po.X,&po.Y);
			CopySaveScrRgn(RgnNum,po);
		}
		break; 
	case  71: // UpdateSaveScrRgn RgnNum
		UpdateSaveScrRgn(atoipos);
		break; 
	case  72: // SaveScrRgn RgnNum[,X,Y,CX,CY]
		{
			Rect re(0,0,ScreenSize.Width,ScreenSize.Height);
			const char *tmppos=FindField(pos,2,",");
			if (tmppos && *tmppos)	sscanf(tmppos,"%d,%d,%d,%d",&re.X,&re.Y,&re.Width,&re.Height);
			retint=SaveScrRgn(re, atoipos);
		}
		break; 
	case  73: // EnableScrSaving
		EnableScrSaving(atoipos);
		break; 
	case  74: // ScrPrint [TypeDlg],[Orient],[Paper][,[],[],[LeftPageMargin],[RightPageMargin],[TopPageMargin],[BottomPageMargin],[ScaleHeightToWidth],[ScaleFlags],[PrintBorders],[Invert]]
		ScrPrint(pos);
		break; 
	case  75: // ScreenToBitmap ContextName,BitmapId,BitmapWidth,BitmapHeight,format,dwFlags
		{
			CODContext *ocontext=GPC.m_View->m_ODContextsArray->GetContext(ExtractField(pos,1,","));
			if (ocontext)
			{
				Rect re(0,0,ScreenSize.Width,ScreenSize.Height);
				DWORD dwFlags=atoi(ExtractField(pos,3,","));
				int iBmpId=0;
				CString tmpCS;
				tmpCS=ExtractField(pos,2,",");
				if (tmpCS!="") iBmpId=atoi(tmpCS);
				tmpCS=ExtractField(pos,3,",");
				if (tmpCS!="") re.Width=atoi(tmpCS);
				tmpCS=ExtractField(pos,4,",");
				if (tmpCS!="") re.Height=atoi(tmpCS);

				CBitmapPlus *mbmp=ScreenToBitmap(re.Width,re.Height,CBitmapPlus::TranslatePixelFormat(ExtractField(pos,5,",")),dwFlags);
				ocontext->SetBitmap(iBmpId,mbmp);
			}
		}
		break; 
	case  76: // SetViewSize [CX],[CY]
		{
			Size sz=ScreenSize;
			CString tmpCS;
			tmpCS=ExtractField(pos,1,",");
			if (tmpCS!="") sz.Width=atoi(tmpCS);
			tmpCS=ExtractField(pos,2,",");
			if (tmpCS!="") sz.Height=atoi(tmpCS);
			SetViewSize(sz.Width,sz.Height);
		}
		break; 
	case  77: // IsScrSaveEnable
		retint=IsScrSaveEnable();
		break; 
	case  78: // IsScrViewEnable
		retint=IsScrViewEnable();
		break; 
	case  79: // GetCharPosByWndPos X,Y
		if (oStr)
		{
			Point po(0,0);
			sscanf(pos,"%d,%d",&po.X,&po.Y);
			Point poret=GetCharPosByWndPos(po);
			sprintf(oStr,"%d\x7F%d",poret.X,poret.Y);
		}
		break; 
	case  80: // SetNeedRedraw bNeed
		SetNeedRedraw(atoipos);
		break; 
	case  81: // SetNeedRepaint bNeed
		SetNeedRepaint(atoipos);
		break; 
	case  82: // RepaintRect [X,Y[,CX,CY]]
		{
			Rect re(0,0,ScreenSize.Width,ScreenSize.Height);
			const char *tmppos=FindField(pos,2,",");
			sscanf(pos,"%d,%d,%d,%d",&re.X,&re.Y,&re.Width,&re.Height);
			RepaintRect(re);
		}
		break; 
	case  83: // GetScreenContent Type[,X,Y,CX,CY]
	case  84: // SetScreenContent Type[,X,Y,CX,CY];Content
		if (wActive)
		{
			CString tmpCS=(nfunc==83)?"GetWindowContent ":"SetWindowContent ";
			tmpCS+=pos;
			wActive->DoMethod(tmpCS,oStr);
		}
		break; 
	case  85: // SetFontTune [OffsetX],[OffsetY],[DCX][,DCY]
		{
			CString csTMP;
			csTMP=ExtractField(pos,1,",");
			csTMP.MakeUpper();
			if (csTMP[0]=='D') FontOfsetX=GPScreen::ScrFontOfsetX;
			else
			if (csTMP!="") FontOfsetX=(REAL)atof(csTMP);

			csTMP=ExtractField(pos,2,",");
			csTMP.MakeUpper();
			if (csTMP[0]=='D') FontOfsetY=GPScreen::ScrFontOfsetY;
			else
			if (csTMP!="") FontOfsetY=(REAL)atof(csTMP);

			csTMP=ExtractField(pos,3,",");
			csTMP.MakeUpper();
			if (csTMP[0]=='D') FontDeltaX=GPScreen::ScrFontDeltaX;
			else
			if (csTMP!="") FontDeltaX=(REAL)atof(csTMP);

			csTMP=ExtractField(pos,4,",");
			csTMP.MakeUpper();
			if (csTMP[0]=='D') FontDeltaY=GPScreen::ScrFontDeltaY;
			else
			if (csTMP!="") FontDeltaY=(REAL)atof(csTMP);
		}
	case  86: // GetFontTune
		if (oStr)
			sprintf(oStr,"%g\x7f%g\x7f%g\x7f%g\x7f%g\x7f%g\x7f%g\x7f%g",
			FontOfsetX,FontOfsetY,FontDeltaX,FontDeltaY,
			GPScreen::ScrFontOfsetX,GPScreen::ScrFontOfsetY,GPScreen::ScrFontDeltaX,GPScreen::ScrFontDeltaY
			);
		break; 
	case  87: // SetHeightToWidth Scale
		ScaleHeightToWidth=(REAL)atof(pos);
		if (oStr) sprintf(oStr,"%g",ScaleHeightToWidth);
		break; 
	case  88: // GetHeightToWidth
		if (oStr) sprintf(oStr,"%g",ScaleHeightToWidth);
		break; 
	case  89: // SetPrintBorders dwFlags
		retint=PrintBorders;
		PrintBorders=atoipos;
		break; 
	case  90: // GetPrintBorders
		retint=PrintBorders;
		break; 
	case  91: // SetPrintInvert dwFlags
		retint=PrintInvert;
		PrintInvert=atoipos;
		break; 
	case  92: // GetPrintInvert
		retint=PrintInvert;
		break; 
	case  93: // SetScaleFlags dwFlags
		retint=SizeScaleFlags;
		SizeScaleFlags=atoipos;
		break; 
	case  94: // GetScaleFlags
		retint=SizeScaleFlags;
		break; 
	case 95: // GetBordersActual
		if (oStr) sprintf(oStr,"%g\x7F%g\x7F%g\x7F%g",LeftBorderSafe,RightBorderSafe,TopBorderSafe,BottomBorderSafe);
		break; 
	case 98: // ModifyTermCmdMask [MaskToDelete][,MaskToAdd]
		if (wActive)
		{
			DWORD dwOldMask=wActive->dwOldCommandMask;
			wActive->dwOldCommandMask=dwOldCommandMask;
			wActive->DoMethod(iStr,oStr);
			dwOldCommandMask=wActive->dwOldCommandMask;
			wActive->dwOldCommandMask=dwOldMask;
			wActive->DoMethod(iStr,NULL);
		}
		break; 

		if (oStr) sprintf(oStr,"%g\x7F%g\x7F%g\x7F%g",LeftBorderSafe,RightBorderSafe,TopBorderSafe,BottomBorderSafe);
		break; 
	case 101: //SetConvFlags Flags
		{
			retint=ScrConvFlags;
			int ScrConvFlags=atoipos;
			if (*pos=='0' && (pos[1]&0x1F)==('X'&0x1F))
				sscanf(pos+2,"%X",&ScrConvFlags);
		}
		break; 
	case 102: //GetConvFlags
		retint=ScrConvFlags;
		break; 


	default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
	}
	if (oStr && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);

	return nfunc;
}

void GPScreen::SetViewSize(int cx, int cy)
{
	EnterCriticalSection(&GPC.m_View->m_CSRefresh);
	try
	{
	CalcSafeBorder(&cx, &cy);
	ScreenViewRect.Width=cx;
	ScreenViewRect.Height=cy;
	CharPlaceSize.Width=((REAL)ScreenViewRect.Width)/((REAL)ScreenSize.Width+LeftBorderSafe+RightBorderSafe);
	CharPlaceSize.Height=((REAL)ScreenViewRect.Height)/((REAL)ScreenSize.Height+TopBorderSafe+BottomBorderSafe);

	CreateScreenBitmap(FALSE);
	RedrawScr();
	SetNeedRedraw();
	}catch(...)
	{;}
	LeaveCriticalSection(&GPC.m_View->m_CSRefresh);
}

void GPScreen::CalcSafeBorder(int *cx, int *cy)
{
	CalcSafeBorder(cx, cy, &LeftBorderSafe, &RightBorderSafe, &TopBorderSafe, &BottomBorderSafe);
}

void GPScreen::CalcSafeBorder(int *cx, int *cy, REAL *rLeft, REAL *rRight, REAL *rTop, REAL *rBottom)
{
	int nCharPixelX=(int)(((REAL)*cx)/((REAL)ScreenSize.Width+LeftBorderC+RightBorderC));
	int nCharPixelY=(int)(((REAL)*cy)/((REAL)ScreenSize.Height+TopBorderC+BottomBorderC));
	int ScreenPixelsTmpX=ScreenSize.Width*nCharPixelX;
	int ScreenPixelsTmpY=ScreenSize.Height*nCharPixelY;

	*rLeft=LeftBorderC;
	*rRight=RightBorderC;
	*rTop=TopBorderC;
	*rBottom=BottomBorderC;

	switch((SizeScaleFlags&SSM_SIZE_X))
	{
	case SSM_SAFE:
		*rLeft=ceil((REAL)nCharPixelX*LeftBorderC)/(REAL)nCharPixelX;
		*rRight=ceil((REAL)nCharPixelX*RightBorderC)/(REAL)nCharPixelX;
		*cx=nCharPixelX*ScreenSize.Width+(int)ceil((*rLeft)*(REAL)nCharPixelX)+(int)ceil((*rRight)*(REAL)nCharPixelX);
		break;
	case SSM_LEFT:
		*rRight=ceil((REAL)nCharPixelX*RightBorderC)/(REAL)nCharPixelX;
		*rLeft=floor((((REAL)*cx-(REAL)ScreenPixelsTmpX-(REAL)ceil((REAL)nCharPixelX*RightBorderC))))/(REAL)nCharPixelX;
		break;
	case SSM_RIGHT:
		*rLeft=ceil((REAL)nCharPixelX*LeftBorderC)/(REAL)nCharPixelX;
		*rRight=floor((((REAL)*cx-(REAL)ScreenPixelsTmpX-(REAL)ceil((REAL)nCharPixelX*LeftBorderC))))/(REAL)nCharPixelX;
		break;
	case SSM_SIZE_X:
		break;
	}

	switch(SizeScaleFlags&SSM_SIZE_Y)
	{
	case SSM_SAFE:
		*rTop=ceil((REAL)nCharPixelY*TopBorderC)/(REAL)nCharPixelY;
		*rBottom=ceil((REAL)nCharPixelY*BottomBorderC)/(REAL)nCharPixelY;
		*cy=nCharPixelY*ScreenSize.Height+(int)ceil((*rTop)*(REAL)nCharPixelY)+(int)ceil((*rBottom)*(REAL)nCharPixelY);
		break;
	case SSM_TOP:
		*rBottom=ceil((REAL)nCharPixelY*BottomBorderC)/(REAL)nCharPixelY;
		*rTop=floor((((REAL)*cy-(REAL)ScreenPixelsTmpY-(REAL)ceil((REAL)nCharPixelY*BottomBorderC))))/(REAL)nCharPixelY;
		break;
	case SSM_BOTTOM:
		*rTop=ceil((REAL)nCharPixelY*TopBorderC)/(REAL)nCharPixelY;
		*rBottom=floor((((REAL)*cy-(REAL)ScreenPixelsTmpY-(REAL)ceil((REAL)nCharPixelY*TopBorderC))))/(REAL)nCharPixelY;
		break;
	case SSM_SIZE_Y:
		break;
	}
}

void GPScreen::SaveScr(UINT n)
{
	SaveScrRgn(Rect(Point(0,0),ScreenSize),n);
}

void GPScreen::DeleteWindow(UINT iWndId)
{
// Удаление окна с идентификатором iWndId
//void GPScreen::DeleteWindow(UINT iWndId)
	UINT num=GetWindowNum(iWndId);
	if (num!=0 || iWndId==0)
	{
		delete aGPWindow[num];
		if (ActiveWindow==num) ActiveWindow=0;
		else if (ActiveWindow>num) ActiveWindow--;
		int i;
		for(i=num+1;i<GPMAX_NWINDOW;i++) aGPWindow[i-1]=aGPWindow[i];
		aGPWindow[i]=NULL;
	}
}


void GPScreen::ScrPrint(CDC *sdc, CPrintInfo* pInfo)
{
// Функция печати экрана
//void GPScreen::ScrPrint(CDC *sdc, CPrintInfo* pInfo);
	Rect ss(0,0,sdc->GetDeviceCaps(HORZRES   ),sdc->GetDeviceCaps(VERTRES   ));
	Rect bmpRect=ss;
	if (GPC.m_uPixelPerPoint<1 || GPC.m_uPixelPerPoint>16) GPC.m_uPixelPerPoint=2;
	DWORD dwMapMode=sdc->GetMapMode();
	sdc->SetMapMode(MM_LOMETRIC);
	POINT poLT;
	POINT poRB;
	DEVMODE *dm=pInfo->m_pPD->GetDevMode();
	REAL ScaleHeightToWidthTMP=ScaleHeightToWidth;

	poLT.x=(LONG)(((dm->dmOrientation!=2)?LeftPageMargin:BottomPageMargin)*(REAL)100);
	poLT.y=-(LONG)(((dm->dmOrientation!=2)?TopPageMargin:LeftPageMargin)*(REAL)100);
	sdc->LPtoDP(&poLT);
	poRB.x=(LONG)(((dm->dmOrientation!=2)?RightPageMargin:TopPageMargin)*(REAL)100);
	poRB.y=-(LONG)(((dm->dmOrientation!=2)?BottomPageMargin:RightPageMargin)*(REAL)100);
	sdc->LPtoDP(&poRB);
	sdc->SetMapMode(dwMapMode);


	LONG devLeftMargin=sdc->GetDeviceCaps(PHYSICALOFFSETX);
	poLT.x-=devLeftMargin;
	if (poLT.x<0) poLT.x=0;

	LONG devTopMargin=sdc->GetDeviceCaps(PHYSICALOFFSETY);
	poLT.y-=devTopMargin;
	if (poLT.y<0) poLT.y=0;

	LONG devWidth=sdc->GetDeviceCaps(PHYSICALWIDTH);
	LONG devRightMargin=devWidth-devLeftMargin-ss.Width;
	poRB.x-=devRightMargin;
	if (poRB.x<0) poRB.x=0;

	LONG devHeight=sdc->GetDeviceCaps(PHYSICALHEIGHT);
	LONG devBottomMargin=devHeight-devTopMargin-ss.Height;
	poRB.y-=devBottomMargin;
	if (poRB.y<0) poRB.y=0;

	bmpRect.Width=(ss.Width-poLT.x-poRB.x)/GPC.m_uPixelPerPoint;
	bmpRect.Height=(ss.Height-poLT.y-poRB.y)/GPC.m_uPixelPerPoint;


	try
	{
		//CalcSafeBorder(&cx, &cy);
		ScreenViewRect.Width=bmpRect.Width;
		ScreenViewRect.Height=bmpRect.Height;
		if (PrintBorders)
		{
			CharPlacePrintSize.Width=((REAL)ScreenViewRect.Width)/((REAL)ScreenSize.Width+LeftBorderSafe+RightBorderSafe);
			CharPlacePrintSize.Height=((REAL)ScreenViewRect.Height)/((REAL)ScreenSize.Height+TopBorderSafe+BottomBorderSafe);
		}
		else
		{
			CharPlacePrintSize.Width=((REAL)ScreenViewRect.Width)/((REAL)ScreenSize.Width);
			CharPlacePrintSize.Height=((REAL)ScreenViewRect.Height)/((REAL)ScreenSize.Height);
		}


	}catch(...)
	{;}

	PrintFontTable.InitFontTable(PrintFontTable.familyName,this);

	switch((ScaleFlags&0x7))
	{
	case 1://AS ON SCREEN
		if (CharPlaceSize.Height>1 && CharPlaceSize.Width>1)
			ScaleHeightToWidth=CharPlaceSize.Height/CharPlaceSize.Width;
		else
			ScaleHeightToWidth=CharPlacePrintSize.Height/CharPlacePrintSize.Width;

	case 2://CUSTOM
		{
			REAL tmpScale;
			if (PrintBorders)
				tmpScale=(REAL)bmpRect.Height*((REAL)ScreenSize.Width+LeftBorderSafe+RightBorderSafe)/((REAL)ScreenSize.Height+TopBorderSafe+BottomBorderSafe)/(REAL)bmpRect.Width;
			else
				tmpScale=(REAL)bmpRect.Height*((REAL)ScreenSize.Width)/((REAL)ScreenSize.Height)/(REAL)bmpRect.Width;

			if (tmpScale>ScaleHeightToWidth)
				bmpRect.Height=(INT)((REAL)bmpRect.Height*(ScaleHeightToWidth/tmpScale));
			else
				bmpRect.Width=(INT)((REAL)bmpRect.Width*(tmpScale/ScaleHeightToWidth));
		}
		break;
	default: //fit to paper
		break;
	}

	try
	{
		//CalcSafeBorder(&cx, &cy);
		ScreenViewRect.Width=bmpRect.Width;
		ScreenViewRect.Height=bmpRect.Height;
		if (PrintBorders)
		{
			CharPlacePrintSize.Width=((REAL)ScreenViewRect.Width)/((REAL)ScreenSize.Width+LeftBorderSafe+RightBorderSafe);
			CharPlacePrintSize.Height=((REAL)ScreenViewRect.Height)/((REAL)ScreenSize.Height+TopBorderSafe+BottomBorderSafe);
		}
		else
		{
			CharPlacePrintSize.Width=((REAL)ScreenViewRect.Width)/((REAL)ScreenSize.Width);
			CharPlacePrintSize.Height=((REAL)ScreenViewRect.Height)/((REAL)ScreenSize.Height);
		}


	}catch(...)
	{;}

//	ss.Y+=TopPageMargin;
//	ss.X+=LeftPageMargin;
//	ss.Height-=TopPageMargin+BottomPageMargin;
//	ss.Width-=LeftPageMargin+RightPageMargin;

	CBitmapPlus *mBitmap=NULL;
	Graphics gr1(sdc->m_hDC);
	gr1.SetCompositingQuality(CompositingQualityHighQuality);
	gr1.SetInterpolationMode( InterpolationModeHighQuality );
	gr1.SetPixelOffsetMode(PixelOffsetModeHighQuality);
	gr1.SetTextContrast(0);
	//	gr1.SetCompositingMode(CompositingModeSourceCopy);
	//	gr1.SetSmoothingMode(SmoothingModeHighQuality);
	//	gr1.SetTextRenderingHint(TextRenderingHintAntiAlias );

	gr1.Clear(Color(255,255,255,255));
	if (!pInfo->m_bPreview)
	{
		mBitmap=ScreenToPrintBitmap(bmpRect.Width,bmpRect.Height,PixelFormat32bppARGB,
									(PrintBorders!=0?1:0)
									|(PrintInvert!=0?2:0)
									);
	}
	else
	{
		if (!GPC.m_View->pPreviewBitmap) GPC.m_View->pPreviewBitmap=ScreenToPrintBitmap(bmpRect.Width,bmpRect.Height,PixelFormat32bppARGB,
																				(PrintBorders!=0?1:0)
																				|(PrintInvert!=0?2:0)
																				);
		mBitmap=GPC.m_View->pPreviewBitmap;
	}

	if (mBitmap)
	{
		//gr1.ResetTransform();
		if (!pInfo->m_bPreview) 
		{
			REAL TransX=mBitmap->m_Bitmap->GetHorizontalResolution()/gr1.GetDpiX();
			REAL TransY=mBitmap->m_Bitmap->GetVerticalResolution()/gr1.GetDpiY();
			gr1.ScaleTransform(TransX,TransY);
		}

		gr1.ScaleTransform((REAL)GPC.m_uPixelPerPoint,(REAL)GPC.m_uPixelPerPoint);
		gr1.DrawImage(mBitmap->m_Bitmap,poLT.x,poLT.y);

		if (!pInfo->m_bPreview) delete mBitmap;
	}
	ScaleHeightToWidth=ScaleHeightToWidthTMP;

}

void GPScreen::ResetSelection()
{
	int i;
	for(i=GPMAX_NWINDOW-1;i>=0;i--)
		if(aGPWindow[i])
			aGPWindow[i]->ResetSelection();
}

void GPScreen::ScrToBuffer(unsigned short *buff, Rect & boundRect)
{
	int i;
	for(i=GPMAX_NWINDOW-1;i>=0;i--)
		if(aGPWindow[i])
			aGPWindow[i]->WndToBuffer(buff,boundRect,ScreenSize);
}

BOOL GPScreen::IsScrSaveEnable()
{
	return aSavedScr!=NULL;
}

BOOL GPScreen::IsScrViewEnable()
{
	return (aGPWindow && aGPWindow[0]) ? aGPWindow[0]->IsWndViewEnable():FALSE;
}

void GPScreen::EnableScrSaving(BOOL st)
{

	UINT i;
	if (st && aSavedScr==NULL)
	{
		aSavedScr=new GPScreen * [GPMAX_SAVESCR+1];
		if (aSavedScr) for(i=0;i<GPMAX_SAVESCR+1;i++) aSavedScr[i]=NULL;
	}
	else
	if (!st && aSavedScr)
	{
		for(i=0;i<GPMAX_SAVESCR;i++)
			if (aSavedScr[i]) {delete aSavedScr[i];aSavedScr[i]=NULL;}
		delete[] aSavedScr; aSavedScr=NULL;
	}
}

Size GPScreen::GetScreenSize()
{
	return ScreenSize;
}

int GPScreen::SaveScrRgn(Rect &SaveRgn,int NumberRgn)
{
	if (NumberRgn<0 || NumberRgn>GPMAX_NSAVEDREGION)
		for(NumberRgn=0;NumberRgn<GPMAX_NSAVEDREGION && aGPWindowRgnSaved[NumberRgn];NumberRgn++);

	if (aGPWindowRgnSaved[NumberRgn])
		delete aGPWindowRgnSaved[NumberRgn];


	aGPWindowRgnSaved[NumberRgn]=
		new GPWindow(this,NumberRgn,Size(SaveRgn.Width,SaveRgn.Height),SaveRgn,0,0,0);

	aGPWindowRgnSaved[NumberRgn]->GPCopyRgn(aGPWindow[0],SaveRgn,Point(0,0));

	return NumberRgn;
}

void GPScreen::DeleteSaveScrRgn(int NumberRgn)
{
	if (aGPWindowRgnSaved[NumberRgn])
		delete aGPWindowRgnSaved[NumberRgn];
	aGPWindowRgnSaved[NumberRgn]=NULL;
}

void GPScreen::CopySaveScrRgn(int NumberRgn,Point &pnt_to)
{
	if (aGPWindowRgnSaved[NumberRgn])
	{
		aGPWindow[0]->GPCopyRgn
			(aGPWindowRgnSaved[NumberRgn],aGPWindowRgnSaved[NumberRgn]->GetWndRect(),pnt_to);
		Rect tmp=aGPWindowRgnSaved[NumberRgn]->GetWndRect();
		tmp.Offset(pnt_to);
		aGPWindow[0]->RedrawRect(tmp);
	}
}

void GPScreen::UpdateSaveScrRgn(int NumberRgn)
{
	if (aGPWindowRgnSaved[NumberRgn])
	{
		Rect re;
		aGPWindowRgnSaved[NumberRgn]->GetWndViewRect(re);
		aGPWindow[0]->GPCopyRgn(aGPWindowRgnSaved[NumberRgn],re,Point(re.X,re.Y));
	}
}

void GPScreen::GetBlinkPoints(char *mscr)
{
	int i;
	for(i=GPMAX_NWINDOW-1;i>=0;i--)
		if (aGPWindow[i] && aGPWindow[i]->IsWndViewEnable())
			aGPWindow[i]->GetBlinkPoints(mscr,ScreenSize.Width);
}


BOOL GPScreen::GetScrScrollState()
{	return aGPWindow[ActiveWindow]->ScrollWnd;}

void GPScreen::SetScrScrollState(BOOL state)
{aGPWindow[ActiveWindow]->ScrollWnd=state;}

UINT GPScreen::GetWindowNum(UINT iWndId)
{
	int i;
	for(i=0;i<GPMAX_NWINDOW;i++) if (aGPWindow[i] && aGPWindow[i]->WndId==iWndId) break;
	return (i==GPMAX_NWINDOW) ? 0:i;
}


char GPScreen::SelectWindow(UINT iWndId)
{
	UINT num=GetWindowNum(iWndId);
	if (num!=0 || iWndId==0)
	{
		ActiveWindow=num;
		return '1';
	}
	return '0';
}

void GPScreen::WndForwardOne(UINT iWndId)
{
// Поместить окно вперед на одну позицию
//void GPScreen::WndForwardOne(UINT iWndId)
	UINT num=GetWindowNum(iWndId);
	if (num!=0)
	{
		UINT num2;
		for(num2=num+1;num2<GPMAX_NWINDOW && aGPWindow[num2]==NULL;num2++);
		if (num2!=GPMAX_NWINDOW)
		{
			GPWindow *tmp=aGPWindow[num2];
			aGPWindow[num2]=aGPWindow[num];
			aGPWindow[num]=tmp;
			if (ActiveWindow==num) ActiveWindow=num2;
			else
			if (ActiveWindow==num2) ActiveWindow=num;
		}
	}
}

void GPScreen::WndBackwardOne(UINT iWndId)
{
// Поместить окно назад на одну позицию
//void GPScreen::WndBackwardOne(UINT iWndId)
	UINT num=GetWindowNum(iWndId);
	if (num!=0)
	{
		UINT num2;
		for(num2=num-1;num2>GPMAX_NWINDOW && aGPWindow[num2]==NULL;num2--);
		if (num2!=0)
		{
			GPWindow *tmp=aGPWindow[num2];
			aGPWindow[num2]=aGPWindow[num];
			aGPWindow[num]=tmp;
			if (ActiveWindow==num) ActiveWindow=num2;
			else
			if (ActiveWindow==num2) ActiveWindow=num;
		}
	}
}

void GPScreen::WndForward(UINT iWndId)
{
// Поместить окно впереди всех
//void GPScreen::WndForward(UINT iWndId)
	UINT num=GetWindowNum(iWndId);
	if (num!=0)
	{
		UINT num2;
		for(num2=GPMAX_NWINDOW-1;num2>num && aGPWindow[num2]==NULL;num2--);
		if (num2!=num)
		{
			GPWindow *tmp=aGPWindow[num2];
			aGPWindow[num2]=aGPWindow[num];
			aGPWindow[num]=tmp;
			if (ActiveWindow==num) ActiveWindow=num2;
			else
			if (ActiveWindow==num2) ActiveWindow=num;
		}
	}
}

void GPScreen::WndBackward(UINT iWndId)
{
// Поместить окно позади всех (кроме 0)
//void GPScreen::WndBackward(UINT iWndId)
	UINT num=GetWindowNum(iWndId);
	if (num!=0)
	{
		UINT num2;
		for(num2=1;num2<num && aGPWindow[num2]==NULL;num2++);
		if (num2!=num)
		{
			GPWindow *tmp=aGPWindow[num2];
			aGPWindow[num2]=aGPWindow[num];
			aGPWindow[num]=tmp;
			if (ActiveWindow==num) ActiveWindow=num2;
			else
			if (ActiveWindow==num2) ActiveWindow=num;
		}
	}
}

UINT GPScreen::GPCreateWindow(Size &iGPWndSize, Rect &iGPWndViewRect, UINT IdWnd /*= 0*/)
{
// Создание окна в экране
	int i;
	if (IdWnd==0)
		for(i=1;i<GPMAX_NWINDOW && aGPWindow[i];i++);
	else
	{
		for(i=1;i<GPMAX_NWINDOW;i++)
			if (aGPWindow[i] && aGPWindow[i]->WndId==IdWnd) break;

		if (i!=GPMAX_NWINDOW)
		{
			delete aGPWindow[i];
			aGPWindow[i]=NULL;
		}
		else
		{
			for(i=1;i<GPMAX_NWINDOW && aGPWindow[i];i++);
			if (i!=GPMAX_NWINDOW)
			{
				aGPWindow[i]=new GPWindow(this,IdWnd,iGPWndSize,iGPWndViewRect,GP_WND_SAVE,0,dwOldCommandMask);
			}
		}
	}

	if (i!=GPMAX_NWINDOW)
	{
		char arrId[GPMAX_NWINDOW];

		int j;
		for(j=1;j<GPMAX_NWINDOW;j++)
			arrId[j]=0;

		for( j=1;j<GPMAX_NWINDOW;j++)
			if (aGPWindow[j]) arrId[aGPWindow[j]->WndId]=1;

		for( j=1;j<GPMAX_NWINDOW && arrId[j]!=0;j++);

		aGPWindow[i]=new GPWindow(this, j,iGPWndSize,iGPWndViewRect,GP_WND_SAVE,0,dwOldCommandMask);
	}
	else i=0;
	return i;
}

void GPScreen::WndSetState(UINT iWndId,UINT iWndState)
{
// Установка состояния и свойств окна
//0b -
//1b - Visible
//void GPScreen::WndSetState(UINT iWndId,UINT iWndState)
	UINT num=GetWindowNum(iWndId);
	aGPWindow[num]->SetViewState((iWndState&2)!=0?GP_WND_VIEW:0);
}

GPWindow * GPScreen::GPGetWindowByNum(UINT iNum)
{
	return aGPWindow[iNum];
}

GPWindow * GPScreen::GPGetWindowById(UINT iNum)
{
	return aGPWindow[GetWindowNum(iNum)];
}

void GPScreen::RecolorScr(UINT iFrg, UINT iBkg)
{
	int i;
	for(i=GPMAX_NWINDOW-1;i>=0;i--)
		if(aGPWindow[i]) aGPWindow[i]->RecolorWnd(iFrg,iBkg);
}

void GPScreen::TextBox(Rect re,int type)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->TextBox(re,type);
}

void GPScreen::TextVerLine(int x, int y, int typ, int len)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->TextVerLine(x, y, typ, len);
}

void GPScreen::TextHorLine(int x, int y, int typ, int len)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->TextHorLine(x, y, typ, len);
}

BOOL GPScreen::GetCursorState()
{
	return aGPWindow[ActiveWindow]->CursorVisible;
}

BOOL GPScreen::SetInsertMode(BOOL bOnOff)
{
	return aGPWindow[ActiveWindow]->SetInsertMode(bOnOff);
}

BOOL GPScreen::GetInsertMode()
{
	return aGPWindow[ActiveWindow]->GetInsertMode();
}

void GPScreen::ShadowOld(Rect &re,int type)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->ShadowOld(re,type);
}

Point GPScreen::GetCursorPosition()
{
	return aGPWindow[ActiveWindow]->GetCursorPosition();
}

void GPScreen::GetCursorPosition(Point &cur)
{
	aGPWindow[ActiveWindow]->GetCursorPosition(cur);
}

void GPScreen::CharLine(Point &pos1, Point &pos2,unsigned short Ch)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->CharLine(pos1,pos2,Ch);
}

void GPScreen::RecolorString(int posX,int posY,int LineLength)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->RecolorString(posX, posY, LineLength);
}

BOOL GPScreen::LoadScrRgn(const char *name, Point &topleft)
{
	return aGPWindow[ActiveWindow]->LoadScrRgn(name,topleft);
}

void GPScreen::SetCursorState(BOOL state)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->CursorVisible=state;
}

unsigned short  GPScreen::SetChrSpace(UINT newSpace)
{
	return aGPWindow[ActiveWindow]->SetChrSpace( newSpace);
}

unsigned short  GPScreen::GetChrSpace()
{
	return aGPWindow[ActiveWindow]->GetChrSpace();
}

UINT GPScreen::SetChrStyle(UINT newStyle, DWORD dwMask)
{
	return aGPWindow[ActiveWindow]->SetChrStyle(ChrStyle=newStyle,dwMask);
}

UINT GPScreen::GetChrStyle()
{
	return aGPWindow[ActiveWindow]->GetChrStyle();
}

UINT GPScreen::SetChrColor(UINT newcolor, DWORD dwMask)
{
	return aGPWindow[ActiveWindow]->SetChrColor( newcolor, dwMask);
}

UINT GPScreen::SetBkgColor(UINT newcolor, DWORD dwMask)
{
	return aGPWindow[ActiveWindow]->SetBkgColor(newcolor, dwMask);
}

UINT GPScreen::SetChrColorIndex(UINT newcolorIndex, DWORD dwMask)
{
	return aGPWindow[ActiveWindow]->SetChrColorIndex(newcolorIndex, dwMask);
}

UINT GPScreen::SetBkgColorIndex(UINT newcolorIndex, DWORD dwMask)
{
	return aGPWindow[ActiveWindow]->SetBkgColorIndex(newcolorIndex, dwMask);
}

BOOL GPScreen::SetReverseVideo(BOOL bReverse, DWORD dwMask)
{
	return aGPWindow[ActiveWindow]->SetReverseVideo(bReverse, dwMask);
}

BOOL GPScreen::GetReverseVideo()
{
	return aGPWindow[ActiveWindow]->GetReverseVideo();
}

UINT GPScreen::GetChrColorIndex()
{
	return aGPWindow[ActiveWindow]->GetChrColorIndex();
}

UINT GPScreen::GetBkgColorIndex()
{
	return aGPWindow[ActiveWindow]->GetBkgColorIndex();
}


UINT GPScreen::GetChrColor()
{
	return aGPWindow[ActiveWindow]->GetChrColor();
}

UINT GPScreen::GetBkgColor()
{
	return aGPWindow[ActiveWindow]->GetBkgColor();
}

void GPScreen::ClearScreen()
{
	Graphics grbmp(ScreenBitmap);
	DWORD tmpClr=GetBkgColor();
	Color tmpBkg;
	if ((tmpClr&0xFF000000))
		tmpBkg.SetValue(tmpClr);
	else
		tmpBkg.SetFromCOLORREF(tmpClr);
	grbmp.Clear(tmpBkg);

	ClearScreenBorder(grbmp);

	int i;
	for(i=GPMAX_NWINDOW-1;i>=0;i--)
		if(aGPWindow[i]) 
			aGPWindow[i]->ClearWnd();

	if (IsScrViewEnable()) GPC.m_View->Invalidate();
}

void GPScreen::InvalidateScreenBorder()
{
	RECT re;
	RECT reclient;
	GPC.m_View->GetClientRect(&reclient);

	if (LeftBorderSafe>0)
	{
		re.left=0;
		re.top=0;
		re.right=(LONG)(LeftBorderSafe*CharPlaceSize.Width+CharPlaceSize.Width);
		re.bottom=reclient.bottom;
		GPC.m_View->InvalidateRect(&re);
	}
	if (RightBorderSafe>0)
	{
		re.left=reclient.right-(LONG)(RightBorderSafe*CharPlaceSize.Width+CharPlaceSize.Width);
		re.top=0;
		re.right=reclient.right+(LONG)CharPlaceSize.Width;
		re.bottom=reclient.bottom+(LONG)CharPlaceSize.Height;
		GPC.m_View->InvalidateRect(&re);
	}
	if (TopBorderSafe>0)
	{
		re.left=(LONG)(LeftBorderSafe*CharPlaceSize.Width-CharPlaceSize.Width);
		re.top=0;
		re.right=reclient.right-(LONG)(RightBorderSafe*CharPlaceSize.Width-CharPlaceSize.Width);
		re.bottom=(LONG)(TopBorderSafe*CharPlaceSize.Height+CharPlaceSize.Height);
		GPC.m_View->InvalidateRect(&re);
	}
	if (BottomBorderSafe>0)
	{
		re.left=(LONG)(LeftBorderSafe*CharPlaceSize.Width-CharPlaceSize.Width);
		re.top=reclient.bottom-(LONG)(BottomBorderSafe*CharPlaceSize.Height+CharPlaceSize.Height);
		re.right=reclient.right-(LONG)(RightBorderSafe*CharPlaceSize.Width-CharPlaceSize.Width);
		re.bottom=reclient.bottom+(LONG)CharPlaceSize.Height;
		GPC.m_View->InvalidateRect(&re);
	}
}

void GPScreen::ClearScreenBorder(Graphics & grbmp)
{
	COLORREF tmpCLRREF=	GPC.m_curOutScrBkg;
	Color tmpBkg;

	if (tmpCLRREF<=7)
	{
		tmpCLRREF=cBEtalon[tmpCLRREF];

	}
	else
		if (tmpCLRREF==8) tmpCLRREF=::GetSysColor(COLOR_3DFACE);
	else
		if (tmpCLRREF==9) tmpCLRREF=::GetSysColor(COLOR_MENU);

	if ((tmpCLRREF&0xFF000000)) tmpBkg.SetValue(tmpCLRREF);
	else tmpBkg.SetFromCOLORREF(tmpCLRREF);

	SolidBrush bkgBorderBrush(tmpBkg);

	if (LeftBorderSafe>0)
	{
		grbmp.FillRectangle(&bkgBorderBrush,
			RectF(
				0,
				0,
				LeftBorderSafe*CharPlaceSize.Width,
				(TopBorderSafe+BottomBorderSafe+(REAL)ScreenSize.Height)*CharPlaceSize.Height));
	}
	if (RightBorderSafe>0)
	{
		grbmp.FillRectangle(&bkgBorderBrush,
			RectF(
				(LeftBorderSafe+(REAL)ScreenSize.Width)*CharPlaceSize.Width,
				0,
				RightBorderSafe*CharPlaceSize.Width,
				(TopBorderSafe+BottomBorderSafe+(REAL)ScreenSize.Height)*CharPlaceSize.Height));
	}
	if (TopBorderSafe>0)
	{
		grbmp.FillRectangle(&bkgBorderBrush,
			RectF(
				LeftBorderSafe*CharPlaceSize.Width,
				0,
				((REAL)ScreenSize.Width)*CharPlaceSize.Width,
				TopBorderSafe*CharPlaceSize.Height));
	}
	if (BottomBorderSafe>0)
	{
		grbmp.FillRectangle(&bkgBorderBrush,
			RectF(
				LeftBorderSafe*CharPlaceSize.Width,
				(TopBorderSafe+(REAL)ScreenSize.Height)*CharPlaceSize.Height,
				((REAL)ScreenSize.Width)*CharPlaceSize.Width,
				BottomBorderSafe*CharPlaceSize.Height));
	}
}

void GPScreen::ClearEndOfScreen()
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->ClearEndOfWnd();
}

void GPScreen::ClearEndOfLine()
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->ClearEndOfLine();
}

void GPScreen::ClearToBeginOfLine()
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->ClearToBeginOfLine();
}

void GPScreen::CursorMoveCR()
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->CursorMoveCR();
}

void GPScreen::CursorMoveLF()
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->CursorMoveLF();
}

void GPScreen::CharOut(int x, int y, unsigned short ch)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->CharOut(x, y, ch);
}

void GPScreen::CharOut(unsigned short ch)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->CharOut(ch);
}

void GPScreen::CharOutAW(int x, int y, char ch)
{
	if (aGPWindow[ActiveWindow])
	{
		if (GPC.m_USEMBCONV)
			aGPWindow[ActiveWindow]->CharOutAW(x, y, ch);
		else
			aGPWindow[ActiveWindow]->CharOutAW(x, y, ch);
	}
}

void GPScreen::CharOutAW(char ch)
{
	if (ch==10) CursorMoveDown();
	else
	if (aGPWindow[ActiveWindow])
	{
		if (GPC.m_USEMBCONV)
			aGPWindow[ActiveWindow]->CharOutAW(ch);
		else
			aGPWindow[ActiveWindow]->CharOut(ch);
	}
}

void GPScreen::CharOutGRUC(unsigned short ch)
{
	if (aGPWindow[ActiveWindow])
			aGPWindow[ActiveWindow]->CharOutGRUC(ch);
}

void GPScreen::LineOut(int x, int y, unsigned short *line, DWORD LineLen)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->LineOut(x, y, line, LineLen);
}

void GPScreen::LineOut(unsigned short *line, DWORD LineLen)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->LineOut(line,LineLen);
}

void GPScreen::SetCursorPosition(int x, int y)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->SetCursorPosition(x,y);
}

void GPScreen::SetCursorPosition(Point &newPoint)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->SetCursorPosition(newPoint);
}

void GPScreen::CursorMoveUp()
{
	if (aGPWindow[ActiveWindow]) 
	{
		if ((UINT)GetCursorPosition().Y>uScrollLineStart)
			aGPWindow[ActiveWindow]->CursorMoveUp();
		else
			ScrollDown(1);
	}
}

void GPScreen::CursorMoveDown()
{
	if (aGPWindow[ActiveWindow]) 
	{
		if ((UINT)GetCursorPosition().Y<uScrollLineEnd)
			aGPWindow[ActiveWindow]->CursorMoveDown();
		else
			ScrollUp(1);
	}
}

void GPScreen::CursorMoveRight()
{
	if (aGPWindow[ActiveWindow]) 
	{
		if (GetCursorPosition().X+1<ScreenSize.Width)
			aGPWindow[ActiveWindow]->CursorMoveRight();
		else
		{
			CursorMoveCR();
			CursorMoveLF();
		}
	}
}

void GPScreen::CursorMoveLeft()
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->CursorMoveLeft();
}

void GPScreen::ScrollDown(UINT ntime)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->ScrollDown(ntime);
}

void GPScreen::ScrollUp(UINT ntime)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->ScrollUp(ntime);
}

void GPScreen::ScrollDown()
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->ScrollDown();
}

void GPScreen::ScrollUp()
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->ScrollUp();
}

void GPScreen::ScrollLeft(UINT ntime)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->ScrollLeft(ntime);
}

void GPScreen::ScrollRight(UINT ntime)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->ScrollRight(ntime);
}

void GPScreen::ScrollLeft()
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->ScrollLeft();
}

void GPScreen::DelChar(Point &pos)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->DelChar(pos);
}

void GPScreen::InsertChar(Point &pos)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->InsertChar(pos);
}

void GPScreen::DoTab(DWORD dwFlags)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->DoTab(dwFlags);
}

void GPScreen::SetTABStopPos(DWORD dwFlags)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->SetTABStopPos(dwFlags);
}

void GPScreen::SetTABStopPos(UINT posX, DWORD dwFlags)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->SetTABStopPos(posX, dwFlags);
}


void GPScreen::InsertLine(int pos)
{
	UINT tmpStartScroll=uScrollLineStart;
	uScrollLineStart=pos;
	ScrollRange(1,1);
	uScrollLineStart=tmpStartScroll;
	//if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->InsertLine(pos);
}

void GPScreen::DelLine(int pos)
{
	UINT tmpStartScroll=uScrollLineStart;
	uScrollLineStart=pos;
	ScrollRange(1,0);
	uScrollLineStart=tmpStartScroll;

//	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->DelLine(pos);
}

void GPScreen::DelChar(UINT nTimes)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->DelChar(nTimes);
}

void GPScreen::InsertChar(UINT nTimes)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->InsertChar(nTimes);
}

void GPScreen::InsertLine(UINT nTimes)
{
	UINT tmpStartScroll=uScrollLineStart;
	uScrollLineStart=GetCursorPosition().Y;
	ScrollRange(nTimes,1);
	uScrollLineStart=tmpStartScroll;
//	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->InsertLine(nTimes);
}

void GPScreen::DelLine(UINT nTimes)
{
	UINT tmpStartScroll=uScrollLineStart;
	uScrollLineStart=GetCursorPosition().Y;
	ScrollRange(nTimes,0);
	uScrollLineStart=tmpStartScroll;
//	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->DelLine(nTimes);
}

void GPScreen::SetSelection(Rect &re)
{
	int i;
	for(i=GPMAX_NWINDOW-1;i>=0;i--)
		if(aGPWindow[i]) aGPWindow[i]->SetSelection(re,ScreenSize);
}

void GPScreen::CharOut(const unsigned short *iBuff, DWORD iLength)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->CharOut(iBuff,iLength);
}

void GPScreen::CharOutAW(const char *iBuff, DWORD iLength)
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->CharOutAW(iBuff,iLength);
}

DWORD GPScreen::RestoreScr(int nSaved)
{
	CopySaveScrRgn(nSaved,Point(0,0));
	return 0;
}

GPWindow *  GPScreen::GPActiveWindow()
{
	GPWindow *ret=NULL;
	if (ActiveWindow<nall) ret=aGPWindow[ActiveWindow];
	return ret;
}

DWORD GPScreen::GetNearestChars(PNEAREST9X9 iNC)
{
	DWORD ret=0;
	GPWindow *w=GPActiveWindow();
	if (w) ret=w->GetNearestChars(iNC);
	return ret;
}

void  GPScreen::SetExPerfixPosition()
{
	GPWindow *w=GPActiveWindow();
	if (w) w->SetExPerfixPosition();
}

void GPScreen::DeleteAllObjects()
{
	if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->DeleteAllObjects();
}

const Point GPScreen::GetCharPosByWndPos(Point & iPos)
{
	Point ret;
	ret.X=(INT)(((REAL)(iPos.X-ScreenViewRect.X))/CharPlaceSize.Width-LeftBorderSafe);
	ret.Y=(INT)(((REAL)(iPos.Y-ScreenViewRect.Y))/CharPlaceSize.Height-TopBorderSafe);
	if (ret.X<0) ret.X=0;
	if (ret.Y<0) ret.Y=0;
	return ret;
}


BOOL GPScreen::GetNeedRedraw()
{
	return ((dwNeedRedraw&1)==1);
}

BOOL GPScreen::GetNeedRepaint()
{
	return ((dwNeedRedraw&2)==2);
}

void GPScreen::SetNeedRedraw(BOOL bNeed)
{
	if (bNeed)
		dwNeedRedraw|=1;
	else
	{
		dwNeedRedraw=dwNeedRedraw&(0xFFFFFFFF^1)|0x2;
	}
}

void GPScreen::SetNeedRepaint(BOOL bNeed)
{
	if (bNeed)
		dwNeedRedraw|=2;
	else
		dwNeedRedraw&=(0xFFFFFFFF^2);
}

void GPScreen::RedrawScr()
{
	Rect re(0,0,ScreenSize.Width,ScreenSize.Height);
	RedrawRect(re);
}

void GPScreen::RedrawRect(Rect &refrect)
{
	refrect.Intersect(Rect(0,0,ScreenSize.Width,ScreenSize.Height));
	if (!refrect.IsEmptyArea())
	{
		EnterCriticalSection(&GPC.m_View->m_CSRefresh);
		try
		{
			int posy,posx,delta=ScreenSize.Width-refrect.Width;
			int pos=refrect.X+refrect.Y*ScreenSize.Width;
			for(posy=0;posy<refrect.Height;posy++,pos+=delta)
				for(posx=0;posx<refrect.Width;posx++)
					InvPoints[pos++]|=1;

			SetNeedRedraw();
		}catch(...)
		{;}
		LeaveCriticalSection(&GPC.m_View->m_CSRefresh);
	}
}

void GPScreen::RepaintScr()
{
	Rect re(0,0,ScreenSize.Width,ScreenSize.Height);
	RepaintRect(re);
}

void GPScreen::RepaintRect(Rect &refrect)
{
	refrect.Intersect(Rect(0,0,ScreenSize.Width,ScreenSize.Height));
	if (!refrect.IsEmptyArea())
	{
		EnterCriticalSection(&GPC.m_View->m_CSRefresh);
		try
		{
			int posy,posx,delta=ScreenSize.Width-refrect.Width;
			int pos=refrect.X+refrect.Y*refrect.Width;
			for(posy=0;posy<refrect.Height;posy++,pos+=delta)
				for(posx=0;posx<refrect.Width;posx++)
					InvPoints[pos++]|=2;

			SetNeedRepaint();
		}catch(...)
		{;}
		LeaveCriticalSection(&GPC.m_View->m_CSRefresh);
	}
}

void GPScreen::RedrawPoint(DWORD pos)
{
	if (pos<nall)
	{
		EnterCriticalSection(&GPC.m_View->m_CSRefresh);
		try
		{
		InvPoints[pos]|=1;
		SetNeedRedraw();
		}catch(...)
		{;}
		LeaveCriticalSection(&GPC.m_View->m_CSRefresh);
	}
}

void GPScreen::RepaintPoint(DWORD pos)
{
	if (pos<nall)
	{
		EnterCriticalSection(&GPC.m_View->m_CSRefresh);
		try
		{
		InvPoints[pos]|=2;
		SetNeedRepaint();
		}catch(...)
		{;}
		LeaveCriticalSection(&GPC.m_View->m_CSRefresh);
	}
}

void GPScreen::RedrawScreen()
{
	if (IsScrViewEnable())
	{
		if (!ScreenBitmap) CreateScreenBitmap(TRUE);

		Graphics gr(ScreenBitmap);
		ClearScreenBorder(gr);

		gr.TranslateTransform(LeftBorderSafe*CharPlaceSize.Width,TopBorderSafe*CharPlaceSize.Height,MatrixOrderPrepend);
		gr.ScaleTransform(CharPlaceSize.Width/(REAL)100,CharPlaceSize.Height/(REAL)100);
		int i;
		for(i=GPMAX_NWINDOW-1;i>=0;i--)
			if(aGPWindow[i])
				aGPWindow[i]->WndPaint(gr);
	}
}

void GPScreen::CreateScreenBitmap(BOOL bClear)
{
	if (ScreenBitmap) delete ScreenBitmap;

	Graphics gr(GPC.m_hViewWnd);
	RECT tmpRect;
	::GetClientRect(GPC.m_hViewWnd,&tmpRect);
	ScreenBitmap=new Bitmap(tmpRect.right-tmpRect.left+1,tmpRect.bottom-tmpRect.top+1,&gr);
	if (bClear) ClearScreen();
}

void GPScreen::CreateScreenPrintBitmap(INT Width, INT Height)
{
	if (ScreenPrintBitmap) delete ScreenPrintBitmap;
	Graphics gr(GPC.m_hViewWnd);
	ScreenPrintBitmap=new Bitmap(Width, Height, &gr);
}


DWORD GPScreen::GetInvPoint(DWORD pos)
{
	DWORD ret=0;
	if (pos<nall) ret=InvPoints[pos];
	return ret;
}

CBitmapPlus *GPScreen::ScreenToBitmap(INT Width, INT Height, PixelFormat oPixelFormat, DWORD dwFlags)
{
	CBitmapPlus *mBitmap=NULL;

//	ss.Y+=GPC.topMargin;
//	ss.X+=GPC.leftMargin;
//	ss.Height-=GPC.topMargin+GPC.bottomMargin;
//	ss.Width-=GPC.leftMargin+GPC.rightMargin;
	

	if (!ScreenBitmap) CreateScreenBitmap(TRUE);

	{
		mBitmap=new CBitmapPlus(GPC.m_View->m_ODContextsArray->GetContext(""),Width,Height,oPixelFormat);

		Graphics gr(mBitmap->m_Bitmap);
		//gr.SetCompositingMode(gr1.GetCompositingMode());
		//	gr.SetCompositingQuality(gr1.GetCompositingQuality());
		//	gr.SetInterpolationMode(gr1.GetInterpolationMode());
		//	gr.SetPixelOffsetMode(gr1.GetPixelOffsetMode());
		//gr.SetSmoothingMode(gr1.GetSmoothingMode());
		//	gr.SetTextContrast(gr1.GetTextContrast());
		//gr.SetTextRenderingHint(gr1.GetTextRenderingHint());


		Unit un=UnitPixel;
		RectF scrRe;
		ScreenBitmap->GetBounds(&scrRe,&un);
		if ((dwFlags&0x1)==0)// w/o borders
		{
			gr.ScaleTransform(
				Width/(scrRe.Width-CharPlaceSize.Width*(LeftBorderSafe+RightBorderSafe)),
				Height/(scrRe.Height-CharPlaceSize.Height*(TopBorderSafe+BottomBorderSafe))
				);
			gr.ScaleTransform(CharPlaceSize.Width/(REAL)100,CharPlaceSize.Height/(REAL)100);
		}
		else
		{
			gr.ScaleTransform(Width/scrRe.Width,Height/scrRe.Height);
			gr.TranslateTransform(LeftBorderSafe*CharPlaceSize.Width,TopBorderSafe*CharPlaceSize.Height,MatrixOrderPrepend);
			gr.ScaleTransform(CharPlaceSize.Width/(REAL)100,CharPlaceSize.Height/(REAL)100);
		}

		int i;
		for(i=GPMAX_NWINDOW-1;i>=0;i--)
			if(aGPWindow[i])
				aGPWindow[i]->WndPrint(gr);
	}

	if ((dwFlags&0x2))
	{
		CBitmapPlus *mBitmap2=new CBitmapPlus(GPC.m_View->m_ODContextsArray->GetContext(""),Width,Height,oPixelFormat);
		Graphics gr1(mBitmap2->m_Bitmap);

		ColorMatrix cm;
		int i;
		for(i=0;i<5;i++)
		  cm.m[i][0]=cm.m[i][1]=cm.m[i][2]=cm.m[i][3]=cm.m[i][4]=0;

		cm.m[0][0]=cm.m[1][1]=cm.m[2][2]=(REAL)-1;//0.99;
		cm.m[3][3]=cm.m[4][4]=(REAL)1;
		cm.m[4][0]=cm.m[4][1]=cm.m[4][2]=(REAL)1;//0.04;

		ImageAttributes ia;
		ia.SetColorMatrix(&cm);

		gr1.DrawImage(mBitmap->m_Bitmap,Rect(0,0,Width,Height),0,0,Width,Height,UnitPixel,&ia);
		delete mBitmap;
		mBitmap=mBitmap2;
	}
	return mBitmap;
}

CBitmapPlus *GPScreen::ScreenToPrintBitmap(INT Width, INT Height, PixelFormat oPixelFormat, DWORD dwFlags)
{
	CBitmapPlus *mBitmap=NULL;

	if (!ScreenPrintBitmap) CreateScreenPrintBitmap(Width, Height);

	{
		mBitmap=new CBitmapPlus(GPC.m_View->m_ODContextsArray->GetContext(""),Width,Height,oPixelFormat);

		Graphics gr(mBitmap->m_Bitmap);
		//gr.SetCompositingMode(gr1.GetCompositingMode());
		//	gr.SetCompositingQuality(gr1.GetCompositingQuality());
		//	gr.SetInterpolationMode(gr1.GetInterpolationMode());
		//	gr.SetPixelOffsetMode(gr1.GetPixelOffsetMode());
		//gr.SetSmoothingMode(gr1.GetSmoothingMode());
		//	gr.SetTextContrast(gr1.GetTextContrast());
		//gr.SetTextRenderingHint(gr1.GetTextRenderingHint());


		Unit un=UnitPixel;
		RectF scrRe;
		ScreenPrintBitmap->GetBounds(&scrRe,&un);
		if ((dwFlags&0x1)==0)// w/o borders
		{
			gr.ScaleTransform(
				Width/(scrRe.Width-CharPlacePrintSize.Width*(LeftBorderSafe+RightBorderSafe)),
				Height/(scrRe.Height-CharPlacePrintSize.Height*(TopBorderSafe+BottomBorderSafe))
				);
			gr.ScaleTransform(CharPlacePrintSize.Width/(REAL)100,CharPlacePrintSize.Height/(REAL)100);
		}
		else
		{
			gr.ScaleTransform(Width/scrRe.Width,Height/scrRe.Height);
			gr.TranslateTransform(LeftBorderSafe*CharPlacePrintSize.Width,TopBorderSafe*CharPlacePrintSize.Height,MatrixOrderPrepend);
			gr.ScaleTransform(CharPlacePrintSize.Width/(REAL)100,CharPlacePrintSize.Height/(REAL)100);
		}

		int i;
		for(i=GPMAX_NWINDOW-1;i>=0;i--)
			if(aGPWindow[i])
				aGPWindow[i]->WndPrint(gr);
	}

	if ((dwFlags&0x2))
	{
		CBitmapPlus *mBitmap2=new CBitmapPlus(GPC.m_View->m_ODContextsArray->GetContext(""),Width,Height,oPixelFormat);
		Graphics gr1(mBitmap2->m_Bitmap);

		ColorMatrix cm;
		int i;
		for(i=0;i<5;i++)
		  cm.m[i][0]=cm.m[i][1]=cm.m[i][2]=cm.m[i][3]=cm.m[i][4]=0;

		cm.m[0][0]=cm.m[1][1]=cm.m[2][2]=(REAL)-1;//0.99;
		cm.m[3][3]=cm.m[4][4]=(REAL)1;
		cm.m[4][0]=cm.m[4][1]=cm.m[4][2]=(REAL)1;//0.04;

		ImageAttributes ia;
		ia.SetColorMatrix(&cm);

		gr1.DrawImage(mBitmap->m_Bitmap,Rect(0,0,Width,Height),0,0,Width,Height,UnitPixel,&ia);
		delete mBitmap;
		mBitmap=mBitmap2;
	}
	return mBitmap;
}

DWORD GPScreen::ScrPrint(const char *iStrParams)
{
	DWORD ret=0;

	UINT TypeDlg,Orient,Paper;
	DWORD tmpPrintBorders=0xFFFFFFFF;
	DWORD tmpPrintInvert=0xFFFFFFFF;
	DWORD tmpScaleFlags=0xFFFFFFFF;
	REAL tmpleftMargin=-12345,
		 tmprightMargin=-12345,
		 tmptopMargin=-12345,
		 tmpbottomMargin=-12345,
		 tmpScaleHeightToWidth=-12345;
	m_LastScanf=sscanf(iStrParams,"%d,%d,%d",&TypeDlg,&Orient,&Paper);

	CString csTMP;
	csTMP=ExtractField(iStrParams,4,",");
	csTMP.MakeUpper();
	if (csTMP[0]=='D') tmpleftMargin=GPScreen::ScrLeftPageMargin;
	else
	if (csTMP!="") tmpleftMargin=(REAL)atof(csTMP);

	csTMP=ExtractField(iStrParams,5,",");
	csTMP.MakeUpper();
	if (csTMP[0]=='D') tmprightMargin=GPScreen::ScrRightPageMargin;
	else
	if (csTMP!="") tmprightMargin=(REAL)atof(csTMP);

	csTMP=ExtractField(iStrParams,6,",");
	csTMP.MakeUpper();
	if (csTMP[0]=='D') tmptopMargin=GPScreen::ScrTopPageMargin;
	else
	if (csTMP!="") tmptopMargin=(REAL)atof(csTMP);

	csTMP=ExtractField(iStrParams,7,",");
	csTMP.MakeUpper();
	if (csTMP[0]=='D') tmpbottomMargin=GPScreen::ScrBottomPageMargin;
	else
	if (csTMP!="") tmpbottomMargin=(REAL)atof(csTMP);

	csTMP=ExtractField(iStrParams,8,",");
	csTMP.MakeUpper();
	if (csTMP[0]=='D') tmpScaleHeightToWidth=GPScreen::ScrScaleHeightToWidth;
	else
	if (csTMP!="") tmpScaleHeightToWidth=(REAL)atof(csTMP);

	csTMP=ExtractField(iStrParams,9,",");
	csTMP.MakeUpper();
	if (csTMP[0]=='D') tmpScaleFlags=GPScreen::ScrScaleFlags;
	else
	if (csTMP!="") tmpScaleFlags=atoi(csTMP);

	csTMP=ExtractField(iStrParams,10,",");
	csTMP.MakeUpper();
	if (csTMP[0]=='D') tmpPrintBorders=GPScreen::ScrPrintBorders;
	else
	if (csTMP!="") tmpPrintBorders=atoi(csTMP);

	csTMP=ExtractField(iStrParams,11,",");
	csTMP.MakeUpper();
	if (csTMP[0]=='D') tmpPrintInvert=GPScreen::ScrPrintInvert;
	else
	if (csTMP!="") tmpPrintInvert=atoi(csTMP);

	GPC.m_View->m_PrintTransp=ScrId;
	if (tmpleftMargin!=-12345)		LeftPageMargin=tmpleftMargin;
	if (tmprightMargin!=-12345)		RightPageMargin=tmprightMargin;
	if (tmptopMargin!=-12345)		TopPageMargin=tmptopMargin;
	if (tmpbottomMargin!=-12345)	BottomPageMargin=tmpbottomMargin;
	if (tmpScaleHeightToWidth!=-12345)	ScaleHeightToWidth=tmpScaleHeightToWidth;
	if (tmpPrintBorders!=0xFFFFFFFF)	PrintBorders=tmpPrintBorders;
	if (tmpScaleFlags!=0xFFFFFFFF)	ScaleFlags=tmpScaleFlags;
	if (tmpPrintInvert!=0xFFFFFFFF)	PrintInvert=tmpPrintInvert;

	PRINTDLG pd;
	pd.hDevMode=NULL;
	AfxGetApp()->GetPrinterDeviceDefaults(&pd);
	DEVMODE *dm=(DEVMODE *)LocalLock(pd.hDevMode);
	dm->dmOrientation=(Orient)==0?DMORIENT_PORTRAIT:DMORIENT_LANDSCAPE;
	UINT ufp[41]={DMPAPER_A4,DMPAPER_A3,DMPAPER_A4SMALL,DMPAPER_LETTER,DMPAPER_LEGAL,DMPAPER_CSHEET,DMPAPER_DSHEET,DMPAPER_ESHEET,DMPAPER_LETTERSMALL,DMPAPER_TABLOID,DMPAPER_LEDGER,DMPAPER_STATEMENT,DMPAPER_EXECUTIVE,DMPAPER_A5,DMPAPER_B4,DMPAPER_B5,DMPAPER_FOLIO,DMPAPER_QUARTO,DMPAPER_10X14,DMPAPER_11X17,DMPAPER_NOTE ,DMPAPER_ENV_9,DMPAPER_ENV_10 ,DMPAPER_ENV_11 ,DMPAPER_ENV_12 ,DMPAPER_ENV_14 ,DMPAPER_ENV_DL ,DMPAPER_ENV_C5 ,DMPAPER_ENV_C3 ,DMPAPER_ENV_C4 ,DMPAPER_ENV_C6 ,DMPAPER_ENV_C65,DMPAPER_ENV_B4 ,DMPAPER_ENV_B5 ,DMPAPER_ENV_B6 ,DMPAPER_ENV_ITALY,DMPAPER_ENV_MONARCH ,DMPAPER_ENV_PERSONAL,DMPAPER_FANFOLD_US,DMPAPER_FANFOLD_STD_GERMAN,DMPAPER_FANFOLD_LGL_GERMAN,};
	dm->dmPaperSize=ufp[Paper%41];
	LocalUnlock(pd.hDevMode);
	::SendMessage(GPC.m_hViewWnd,WM_COMMAND,(TypeDlg&2)==2?ID_FILE_PRINT_PREVIEW:(TypeDlg&1)==0?ID_FILE_PRINT_DIRECT:ID_FILE_PRINT,0);

	return ret;
}

const char *GPScreen::cArrCommandMask[]={
		"UNDERLINE",	"STRIKE",		"ITALIC",	"BOLD",		"SELECTION",
		"FIXED",		"TRANSPARENT",	"CODE",		"BLINK",	"LIGHT",	  
		"SHADOW",		"CLR",			"CLRFRG",	"CLRBKG",	"STYLES",
		"STYLESOLD",	"STYLESNEW",	"REVERSE",	"ALL",		"",
		"",
		};

const DWORD GPScreen::uArrCommandMask[]={
		GP_SCRMASK_UNDERLINE,	GP_SCRMASK_STRIKE,		GP_SCRMASK_ITALIC,	GP_SCRMASK_BOLD,	GP_SCRMASK_SELECTION,
		GP_SCRMASK_FIXED,		GP_SCRMASK_OPAQUE,		GP_SCRMASK_CODE,	GP_SCRMASK_BLINK,	GP_SCRMASK_LIGHT,
		GP_SCRMASK_SHADOW,		GP_SCRMASK_CLR,			GP_SCRMASK_CLRFRG,	GP_SCRMASK_CLRBKG,	GP_SCRMASK_STYLES,
		GP_SCRMASK_STYLESOLD,	GP_SCRMASK_STYLESNEW,	GP_SCRMASK_REVERSE,	GP_SCRMASK_ALL,		0,
		0,
		};

const DWORD GPScreen::uArrCommandMaskM[]={
		GP_SCRMASK_STYLESOLD,	GP_SCRMASK_STYLESNEW,	GP_SCRMASK_STYLESNEW,	GP_SCRMASK_STYLESOLD,	GP_SCRMASK_STYLESNEW,
		GP_SCRMASK_STYLESOLD,	GP_SCRMASK_STYLESNEW,	GP_SCRMASK_CODE,		GP_SCRMASK_STYLESOLD,	GP_SCRMASK_LIGHT,
		GP_SCRMASK_STYLESNEW,	GP_SCRMASK_ALL,			GP_SCRMASK_CLR,			GP_SCRMASK_CLR,			GP_SCRMASK_ALL,
		GP_SCRMASK_STYLES,		GP_SCRMASK_STYLES,		GP_SCRMASK_STYLESOLD,	GP_SCRMASK_ALL,			0,
		0,
		};

DWORD GPScreen::TranslateScrCmdMask(const char *iStr)
{
	CString tmpCS=ExtractField(iStr,1,",");
	DWORD ret=atoi(tmpCS);
	tmpCS.MakeUpper();
	int i;
	if (tmpCS!="")
		for(i=0;*GPScreen::cArrCommandMask[i];i++)
			if (tmpCS.Find(GPScreen::cArrCommandMask[i])>=0)
				ret|=GPScreen::uArrCommandMask[i];
	return ret;
}

char *GPScreen::TranslateScrCmdMask(char *iStr, DWORD dwMask)
{
	*iStr=0;
	int i;

	for(i=0;*GPScreen::cArrCommandMask[i];i++)
		if ((dwMask&GPScreen::uArrCommandMask[i])==GPScreen::uArrCommandMask[i] &&
			(GPScreen::uArrCommandMaskM[i]==GPScreen::uArrCommandMask[i] || 
			 (dwMask&GPScreen::uArrCommandMaskM[i])!=GPScreen::uArrCommandMaskM[i]
			))
			{
				if (*iStr) strcat(iStr,"|");
				strcat(iStr,GPScreen::cArrCommandMask[i]);
			}

	return iStr;
}


void GPScreen::SaveCursorPosition()
{
	GPWindow *w=GPActiveWindow();
	if (w) w->SaveCursorPosition();
}

void GPScreen::RestoreCursorPosition()
{
	GPWindow *w=GPActiveWindow();
	if (w) w->RestoreCursorPosition();
}

void GPScreen::SetScrollRange(UINT uStart, UINT uEnd)
{
	uScrollLineStart=uStart;
	if (uStart) uScrollLineStart--;
	uScrollLineEnd=uEnd;
	if (uEnd) uScrollLineEnd--;
}

void GPScreen::ScrollRange(UINT nTimes, UINT uDirection)
{
	if (nTimes)
	{
		if (uScrollLineEnd>(UINT)ScreenSize.Height) uScrollLineEnd=ScreenSize.Height-1;
		if (nTimes> uScrollLineEnd-uScrollLineStart) 
		{
			if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->ClearRect(Rect(0,uScrollLineStart,ScreenSize.Width,nTimes));
		}
		else
		{
			if ((uDirection&0x0001)) //Backward
			{
				UINT pos1=uScrollLineStart;
				UINT pos2=nTimes+pos1;
				UINT pos3=uScrollLineEnd<(UINT)ScreenSize.Height?uScrollLineEnd:ScreenSize.Height-1;
				SaveScrRgn(Rect(0,pos1,ScreenSize.Width,pos3-pos2+1),256);
				CopySaveScrRgn(256,Point(0,pos2));
				if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->ClearRect(Rect(0,pos1,ScreenSize.Width,nTimes));
			}
			else
			{
				UINT pos1=uScrollLineStart;
				UINT pos2=nTimes+pos1;
				UINT pos3=uScrollLineEnd<(UINT)ScreenSize.Height?uScrollLineEnd:ScreenSize.Height-1;
				SaveScrRgn(Rect(0,pos2,ScreenSize.Width,pos3-pos2+1),256);
				CopySaveScrRgn(256,Point(0,pos1));
				if (aGPWindow[ActiveWindow]) aGPWindow[ActiveWindow]->ClearRect(Rect(0,pos3-nTimes+1,ScreenSize.Width,nTimes));
			}
		}
	}

}

