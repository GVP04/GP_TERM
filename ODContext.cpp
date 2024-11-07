// ODContext.cpp: implementation of the CODContext class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "gp_termDoc.h"
#include "GPUnit.h"
#include "ODContext.h"
#include "ODContextItem.h"
#include <math.h>
#include <float.h>
#include "WndPrint.h"
#include "GP_QScroll.h"
#include "DlgDrawEdit.h"
#include "GPListBox.h"
#include "GPComboBox.h"
#include "GPButton.h"
#include "GPStatic.h"
#include "GPHeader.h"
#include "GPTabCtrl.h"
#include "GP_TermView.h"
#include "DlgViewSystemMethods.h"
#include "GPListCtr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

GP_RarefiedArr<DRAWTIMERPLUS> CODContext::m_AllDrawTimers; 

VOID CALLBACK DrawTimerProc( HWND hwnd,    UINT uMsg,    UINT_PTR idEvent,    DWORD dwTime)
{
	PDRAWTIMERPLUS m_timer=CODContext::GetTimerByProcId(idEvent);
	if (m_timer)
	{
		CODContext *mContext=(CODContext *)m_timer->pODContext;
		if (mContext)
		{
			mContext->m_uRedrawFlag=1;
			m_timer->dValue+=m_timer->dDelta;
			if (mContext->m_bAutoRedraw || m_timer->bRedraw) mContext->InvalidateDependentWindows();
			if (m_timer->dValue>m_timer->dStop)	KillTimer(NULL,idEvent);
		}
	}
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char *CODContext::cArrMethods[]={
/*00*/	"SetPen","ClonePen","SetPenBrush","DoPenMethod","SetBrush",
/*05*/	"CloneBrush","DoBrushMethod","SetPoint","SetRect","DeleteItem",
/*10*/	"DeleteItems","AddItem","SetItem","InsertItem","InsertEmpty",
/*15*/	"AddItems","SetItems","SetText","SetInt","SetREAL",
/*20*/	"SetColor","ScrollPoint","ScrollRect","ScrollPen","ScrollBrush",
/*25*/	"ScrollItem","ScrollInt","ScrollREAL","ScrollColor","ScrollText",
/*30*/	"SetTimer","KillTimer","SetFont","ScrollFont","DoFontMethod",
/*35*/	"SetRegion","DoRegionMethod","ScrollRegion","CloneRegion","SetRegionFromPath",
/*40*/	"SetRegionFromRect","SetPath","DoPathMethod","ScrollPath","ClonePath",
/*45*/	"SetStringFormat","DoStringFormatMethod","ScrollStringFormat","CloneStringFormat","SetBitmap",
/*50*/	"SetBitmapFromFile","SetBitmapFromIL","SetBitmapIndirect","SetBitmapFromResource","DoBitmapMethod",
/*55*/	"ScrollBitmap","CloneBitmap","CloneBitmapR","Print","PrnName",
/*60*/	"PrnMargins","PrnWinExt","PrnWinOrg","PrnVieExt","PrnVieOrg",
/*65*/	"LogSize","Redraw","SetAutoRedraw","SetEraseBkg","SetMatrix",
/*70*/	"DoMatrixMethod","ScrollMatrix","CloneMatrix","LoadImageList","DoILBitmapMethod",
/*75*/	"ModifyColor","GetInt","GetREAL","GetString","GetRect",
/*80*/	"GetPoint","GetColor","GetMatrix","Execute","SetString",
/*85*/	"","","","","",
/*90*/	"","","","","",
/*95*/	"","","","","",
	};

const char *CODContext::cArrMethodsParams[]={
/*00*/	"nPen,[Width],R,G,B,A","nPen,[Width],SrcContext,nSrcPen","nPen,[Width],BrushContext,nBrush","nPen,PenMethodString","nBrush, Params",
/*05*/	"nBrush,SrcContext,nSrcPen","nBrush,BrushMethodString","nPoint,X,Y","nRect,X,Y,Width,Height","nItem",
/*10*/	"StartItem,EndItem","ItemDescription","nItem,ItemDescription","nItem,ItemDescription","nItem",
/*15*/	"ItemDescription","","Index,Text","Index,Value","Index,Value",
/*20*/	"Index,R,G,B,A","nBegin,nEnd,nTime","nBegin,nEnd,nTime","nBegin,nEnd,nTime","nBegin,nEnd,nTime",
/*25*/	"nBegin,nEnd,nTime","nBegin,nEnd,nTime","nBegin,nEnd,nTime","nBegin,nEnd,nTime","nBegin,nEnd,nTime",
/*30*/	"nTimer,nDelay,dValue,dDelta,dStop,bRedraw","nTimer","nFont,FontDescription","nBegin,nEnd,nTime","nFont,FontMethodString",
/*35*/	"nRegion,RegionDescription","nRegion,RegionMethodString","nBegin,nEnd,nTime","nRegion,SrcContext,nSrcRegion","nRegion,SrcContext,nSrcPath",
/*40*/	"nRegion,SrcContext,nSrcRect","nPath,PathDescription","nPath,PathMethodString","nBegin,nEnd,nTime","nBitmap,SrcContext,nSrcPath",
/*45*/	"nStringFormat,FormatFlags,language","nStringFormat,StringFormatMethodString","nBegin,nEnd,nTime","nStringFormat,SrcContext,nSrcStringFormat","nBitmap,width,height,format",
/*50*/	"nBitmap,Filename,useIcm","nBitmap,ILname,nImage","nBitmap,.....","nBitmap,.....","nBitmap,BitmapMethodString",
/*55*/	"nBegin,nEnd,nTime","nBitmap,SrcContext,nSrcBitmap,X,Y,CX,CY,PixelFormat","nBitmap,SrcContext,nSrcBitmap,SrcRectContext,nRect,PixelFormat","","Name",
/*60*/	"","","","","",
/*65*/	"","","","","nMatrix,MatrixDescription",
/*70*/	"nMatrix,MatrixMethodString","nBegin,nEnd,nTime","nMatrix,SrcContext,nSrcMatrix","ListName,FileName[,bUseIcm]","ILBitmapName,BitmapMethodString",
/*75*/	"nColor,operation,R,G,B,A","[StartID-EndID]|[ID1,ID2,...,IDn]","[StartID-EndID]|[ID1,ID2,...,IDn]","[StartID-EndID]|[ID1,ID2,...,IDn]","[StartID-EndID]|[ID1,ID2,...,IDn]",
/*80*/	"[StartID-EndID]|[ID1,ID2,...,IDn]","[StartID-EndID]|[ID1,ID2,...,IDn]","[StartID-EndID]|[ID1,ID2,...,IDn]","[IDSCR=;][IDDLG=;][IDOBJ=;][RECT=;]","Index,Text",
/*85*/	"","","","","",
/*90*/	"","","","","",
/*95*/	"","","","","",
	};

#define DU_NSTACK		50

const char *CODContext::ccANamedColors[]={
	"AliceBlue",		"AntiqueWhite",		"Aqua",				"Aquamarine",			"Azure",	
	"Beige",			"Bisque",			"Black",			"BlanchedAlmond",		"Blue",	
	"BlueViolet",		"Brown",			"BurlyWood",		"CadetBlue",			"Chartreuse",	
	"Chocolate",		"Coral",			"CornflowerBlue",	"Cornsilk",				"Crimson",	
	"Cyan",				"DarkBlue",			"DarkCyan",			"DarkGoldenrod",		"DarkGray",	
	"DarkGreen",		"DarkKhaki",		"DarkMagenta",		"DarkOliveGreen",		"DarkOrange",	
	"DarkOrchid",		"DarkRed",			"DarkSalmon",		"DarkSeaGreen",			"DarkSlateBlue",	
	"DarkSlateGray",	"DarkTurquoise",	"DarkViolet",		"DeepPink",				"DeepSkyBlue",	
	"DimGray",			"DodgerBlue",		"Firebrick",		"FloralWhite",			"ForestGreen",	
	"Fuchsia",			"Gainsboro",		"GhostWhite",		"Gold",					"Goldenrod",	
	"Gray",				"Green",			"GreenYellow",		"Honeydew",				"HotPink",
	"IndianRed",		"Indigo",			"Ivory",			"Khaki",				"Lavender",	
	"LavenderBlush",	"LawnGreen",		"LemonChiffon",		"LightBlue",			"LightCoral",	
	"LightCyan",		"LightGoldenrodYellow",	"LightGray",	"LightGreen",			"LightPink",	
	"LightSalmon",		"LightSeaGreen",	"LightSkyBlue",		"LightSlateGray",		"LightSteelBlue",	
	"LightYellow",		"Lime",				"LimeGreen",		"Linen",				"Magenta",	
	"Maroon",			"MediumAquamarine",	"MediumBlue",		"MediumOrchid",			"MediumPurple",	
	"MediumSeaGreen",	"MediumSlateBlue",	"MediumSpringGreen",	"MediumTurquoise",	"MediumVioletRed",	
	"MidnightBlue",		"MintCream",		"MistyRose",		"Moccasin",				"NavajoWhite",	
	"Navy",				"OldLace",			"Olive",			"OliveDrab",			"Orange",	
	"OrangeRed",		"Orchid",			"PaleGoldenrod",	"PaleGreen",			"PaleTurquoise",	
	"PaleVioletRed",	"PapayaWhip",		"PeachPuff",		"Peru",					"Pink",	
	"Plum",				"PowderBlue",		"Purple",			"Red",					"RosyBrown",	
	"RoyalBlue",		"SaddleBrown",		"Salmon",			"SandyBrown",			"SeaGreen",	
	"SeaShell",			"Sienna",			"Silver",			"SkyBlue",				"SlateBlue",	
	"SlateGray",		"Snow",				"SpringGreen",		"SteelBlue",			"Tan",	
	"Teal",				"Thistle",			"Tomato",			"Transparent",			"Turquoise",	
	"Violet",			"Wheat",			"White",			"WhiteSmoke",			"Yellow",	
	"YellowGreen",		"",	"",	"",	"",	
	};
const DWORD CODContext::iANamedColors[]={
	Color::AliceBlue,		Color::AntiqueWhite,	Color::Aqua,			Color::Aquamarine,			Color::Azure,
	Color::Beige,			Color::Bisque,			Color::Black,			Color::BlanchedAlmond,		Color::Blue,
	Color::BlueViolet,		Color::Brown,			Color::BurlyWood,		Color::CadetBlue,			Color::Chartreuse,
	Color::Chocolate,		Color::Coral,			Color::CornflowerBlue,	Color::Cornsilk,			Color::Crimson,
	Color::Cyan,			Color::DarkBlue,		Color::DarkCyan,		Color::DarkGoldenrod,		Color::DarkGray,
	Color::DarkGreen,		Color::DarkKhaki,		Color::DarkMagenta,		Color::DarkOliveGreen,		Color::DarkOrange,
	Color::DarkOrchid,		Color::DarkRed,			Color::DarkSalmon,		Color::DarkSeaGreen,		Color::DarkSlateBlue,
	Color::DarkSlateGray,	Color::DarkTurquoise,	Color::DarkViolet,		Color::DeepPink,			Color::DeepSkyBlue,
	Color::DimGray,			Color::DodgerBlue,		Color::Firebrick,		Color::FloralWhite,			Color::ForestGreen,
	Color::Fuchsia,			Color::Gainsboro,		Color::GhostWhite,		Color::Gold,				Color::Goldenrod,
	Color::Gray,			Color::Green,			Color::GreenYellow,		Color::Honeydew,			Color::HotPink,
	Color::IndianRed,		Color::Indigo,			Color::Ivory,			Color::Khaki,				Color::Lavender,
	Color::LavenderBlush,	Color::LawnGreen,		Color::LemonChiffon,	Color::LightBlue,			Color::LightCoral,
	Color::LightCyan,		Color::LightGoldenrodYellow,	Color::LightGray,	Color::LightGreen,		Color::LightPink,
	Color::LightSalmon,		Color::LightSeaGreen,	Color::LightSkyBlue,	Color::LightSlateGray,		Color::LightSteelBlue,
	Color::LightYellow,		Color::Lime,			Color::LimeGreen,		Color::Linen,				Color::Magenta,
	Color::Maroon,			Color::MediumAquamarine,	Color::MediumBlue,	Color::MediumOrchid,		Color::MediumPurple,
	Color::MediumSeaGreen,	Color::MediumSlateBlue,	Color::MediumSpringGreen,	Color::MediumTurquoise,	Color::MediumVioletRed,
	Color::MidnightBlue,	Color::MintCream,		Color::MistyRose,		Color::Moccasin,			Color::NavajoWhite,
	Color::Navy,			Color::OldLace,			Color::Olive,			Color::OliveDrab,			Color::Orange,
	Color::OrangeRed,		Color::Orchid,			Color::PaleGoldenrod,	Color::PaleGreen,			Color::PaleTurquoise,
	Color::PaleVioletRed,	Color::PapayaWhip,		Color::PeachPuff,		Color::Peru,				Color::Pink,
	Color::Plum,			Color::PowderBlue,		Color::Purple,			Color::Red,					Color::RosyBrown,
	Color::RoyalBlue,		Color::SaddleBrown,		Color::Salmon,			Color::SandyBrown,			Color::SeaGreen,
	Color::SeaShell,		Color::Sienna,			Color::Silver,			Color::SkyBlue,				Color::SlateBlue,
	Color::SlateGray,		Color::Snow,			Color::SpringGreen,		Color::SteelBlue,			Color::Tan,
	Color::Teal,			Color::Thistle,			Color::Tomato,			Color::Transparent,			Color::Turquoise,
	Color::Violet,			Color::Wheat,			Color::White,			Color::WhiteSmoke,			Color::Yellow,
	Color::YellowGreen,
	Color::Purple,			Color::Purple,			Color::Purple,			Color::Purple,
	};


CODContext::CODContext()
{
	m_CurHDC=NULL;
	m_MeasureFlag=0;
	m_ContextName.Format("%X",this);
	m_CurHWND=NULL;
	m_clrBkgnd.SetFromCOLORREF(::GetSysColor(COLOR_WINDOW));
	m_uRedrawFlag=1;
	m_hDCBitmap=NULL;
	m_bAutoRedraw=FALSE;
	m_bEraseBkg=FALSE;
	m_CurDialogGPU=NULL;
	ZeroMemory(m_TMArr,sizeof(m_TMArr));
	
	
	UINT i;

	m_nDrawArray=100;
	m_nDraw=0;
	m_ArrDrawItems=new CODContextItem * [m_nDrawArray];
	for(i=0;i<m_nDrawArray;i++)	m_ArrDrawItems[i]=NULL;

	m_nPenArray=20;
	m_PenArr=new CPenPlus * [m_nPenArray];
	for(i=0;i<m_nPenArray;i++)	m_PenArr[i]=NULL;

	m_nBrushArray=20;
	m_BrushArr=new CBrushPlus * [m_nBrushArray];
	for(i=0;i<m_nBrushArray;i++)	m_BrushArr[i]=NULL;

	m_nRgnArray=20;
	m_RgnArr=new CRgnPlus * [m_nRgnArray];
	for(i=0;i<m_nRgnArray;i++)	m_RgnArr[i]=NULL;

	m_nMatrixArray=20;
	m_MatrixArr=new CMatrixPlus * [m_nMatrixArray];
	for(i=0;i<m_nMatrixArray;i++)	m_MatrixArr[i]=NULL;

	m_nGraphPathArray=20;
	m_GraphPathArr=new CGraphicsPathPlus * [m_nGraphPathArray];
	for(i=0;i<m_nGraphPathArray;i++)	m_GraphPathArr[i]=NULL;

	m_nFontArray=20;
	m_FontArr=new CFontPlus * [m_nFontArray];
	for(i=0;i<m_nFontArray;i++)	m_FontArr[i]=NULL;

	m_nStringFormatArray=20;
	m_StringFormatArr=new CStringFormatPlus * [m_nStringFormatArray];
	for(i=0;i<m_nStringFormatArray;i++)	m_StringFormatArr[i]=NULL;

	m_nPointArray=200;
	m_PointArr=new PointF[m_nPointArray];

	m_nRectArray=200;
	m_RectArr=new RectF[m_nRectArray];

	m_nStringArray=200;
	m_StringArr=new CString[m_nStringArray];

	m_nRGBArray=50;
	m_RGBArr=new Color [m_nRGBArray];

	m_RGBArr[0].SetFromCOLORREF(GetSysColor(COLOR_WINDOW));
	m_RGBArr[1].SetFromCOLORREF(GetSysColor(COLOR_WINDOWTEXT));
	m_RGBArr[2].SetFromCOLORREF(GetSysColor(COLOR_HIGHLIGHT));
	m_RGBArr[3].SetFromCOLORREF(GetSysColor(COLOR_HIGHLIGHTTEXT));
	m_RGBArr[4].SetFromCOLORREF(GetSysColor(COLOR_MENU));
	m_RGBArr[5].SetFromCOLORREF(GetSysColor(COLOR_MENUTEXT));
	m_RGBArr[6].SetFromCOLORREF(GetSysColor(COLOR_MENUHILIGHT));
	m_RGBArr[7].SetFromCOLORREF(GetSysColor(COLOR_MENUBAR));
	m_RGBArr[8].SetFromCOLORREF(GetSysColor(COLOR_GRAYTEXT));
	m_RGBArr[9].SetFromCOLORREF(GetSysColor(COLOR_HOTLIGHT));

	m_nIntArray=500;
	m_IntArr=new int [m_nIntArray];
	for(i=0;i<m_nIntArray;i++)	m_IntArr[i]=0;

	m_nREALArray=500;
	m_REALArr=new REAL [m_nREALArray];
	for(i=0;i<m_nREALArray;i++)	m_REALArr[i]=0;

	m_nBitmapArray=40;
	m_BitmapArr=new CBitmapPlus *[m_nBitmapArray];
	for(i=0;i<m_nBitmapArray;i++)	m_BitmapArr[i]=NULL;

	m_nILBitmap=40;
	m_ILBitmap=new CBitmapPlus *[m_nILBitmap];
	for(i=0;i<m_nILBitmap;i++)	m_ILBitmap[i]=NULL;

	m_LogSize.cx=m_LogSize.cy=0;
	m_PrintWinExt=m_PrintVieExt=CSize(-12345,-12345);
	m_PrintWinOrg=m_PrintVieOrg=Point(-12345,-12345);
	m_PrintMargins.SetRect(2000,2000,2000,2000);
	m_DrawName="";
}

CODContext::~CODContext()
{
	ResetContext();

	if (m_ArrDrawItems)	delete[]  m_ArrDrawItems;

	m_nDraw=0;
	m_nDrawArray=0;
	m_ArrDrawItems=NULL;

	if (m_REALArr)	delete[] m_REALArr;
	m_nREALArray=0;	m_REALArr=NULL;

	if (m_PenArr)	delete[] m_PenArr;
	m_nPenArray=0;	m_PenArr=NULL;

	if (m_BrushArr!=NULL)	delete[] m_BrushArr;
	m_nBrushArray=0;	m_BrushArr=NULL;

	if (m_RgnArr!=NULL)	delete[] m_RgnArr;
	m_nRgnArray=0;	m_RgnArr=NULL;

	if (m_MatrixArr!=NULL)	delete[] m_MatrixArr;
	m_nMatrixArray=0;	m_MatrixArr=NULL;

	if (m_GraphPathArr!=NULL)	delete[] m_GraphPathArr;
	m_nGraphPathArray=0;	m_GraphPathArr=NULL;

	if (m_FontArr!=NULL)	delete[] m_FontArr;
	m_nFontArray=0;	m_FontArr=NULL;

	if (m_StringFormatArr!=NULL)	delete[] m_StringFormatArr;
	m_nStringFormatArray=0;	m_StringFormatArr=NULL;

	if (m_PointArr!=NULL)	delete[]  m_PointArr;
	m_nPointArray=0;	m_PointArr=NULL;

	if (m_RectArr!=NULL)	delete[]  m_RectArr;
	m_nRectArray=0;	m_RectArr=NULL;

	if (m_StringArr!=NULL)	delete[]  m_StringArr;
	m_nStringArray=0;	m_StringArr=NULL;

	if (m_RGBArr!=NULL)		delete[] m_RGBArr;
	m_nRGBArray=0; m_RGBArr=NULL;

	if (m_IntArr)		delete[] m_IntArr;
	m_nIntArray=0;	m_IntArr=NULL;

	if (m_BitmapArr)	delete[] m_BitmapArr;
	m_nBitmapArray=0; m_BitmapArr=NULL;

	if (m_ILBitmap)	delete[] m_ILBitmap;
	m_nILBitmap=0; m_ILBitmap=NULL;
}

void CODContext::InitDRAWTIMERPLUS(PDRAWTIMERPLUS pdid, CODContext *pODContext)
{
	pdid->pODContext=(LPARAM)pODContext;
	pdid->dwTimerProcId=0;
	pdid->nTimer=0;
	pdid->nDelay=1000;
	pdid->dValue=0;
	pdid->dDelta=1;
	pdid->dStop=(REAL)9.9e37;
	pdid->bRedraw=TRUE;
}

void CODContext::ResetContext()
{
	KillDrawTimer(-1, this);
	DeletePaintObj();
	UINT i;
	for(i=0;i<m_nDrawArray;i++)	DestroyItem(i);
	m_nDraw=0;

	if (m_REALArr)	for(i=0;i<m_nREALArray;i++)	m_REALArr[i]=0;


	if (m_PenArr)
		for(i=0;i<m_nPenArray;i++)
			if (m_PenArr[i])
			{
				try{delete m_PenArr[i];}catch(...){;}
				m_PenArr[i]=NULL;
			}

	if (m_BrushArr)
		for(i=0;i<m_nBrushArray;i++)
			if (m_BrushArr[i])
			{
				try{delete m_BrushArr[i];}catch(...){;}
				m_BrushArr[i]=NULL;
			}


	if (m_RgnArr)
		for(i=0;i<m_nRgnArray;i++)
			if (m_RgnArr[i])
			{
				try{delete m_RgnArr[i];}catch(...){;}
				m_RgnArr[i]=NULL;
			}

	if (m_MatrixArr)
		for(i=0;i<m_nMatrixArray;i++)
			if (m_MatrixArr[i])
			{
				try{delete m_MatrixArr[i];}catch(...){;}
				m_MatrixArr[i]=NULL;
			}

	if (m_GraphPathArr)
		for(i=0;i<m_nGraphPathArray;i++)
			if (m_GraphPathArr[i])
			{
				try{delete m_GraphPathArr[i];}catch(...){;}
				m_GraphPathArr[i]=NULL;
			}

	if (m_FontArr)
		for(i=0;i<m_nFontArray;i++)
			if (m_FontArr[i])
			{
				try{delete m_FontArr[i];}catch(...){;}
				m_FontArr[i]=NULL;
			}

	if (m_StringFormatArr)
		for(i=0;i<m_nStringFormatArray;i++)
			if (m_StringFormatArr[i])
			{
				try{delete m_StringFormatArr[i];}catch(...){;}
				m_StringFormatArr[i]=NULL;
			}

	if (m_PointArr)		for(i=0;i<m_nPointArray;i++) m_PointArr[i].X=m_PointArr[i].Y=0;

	if (m_RectArr)
		for(i=0;i<m_nRectArray;i++)
			m_RectArr[i].X=m_RectArr[i].Y=m_RectArr[i].Width=m_RectArr[i].Height=0;

	if (m_StringArr)	for(i=0;i<m_nStringArray;i++) m_StringArr[i]="";

	if (m_RGBArr)		for(i=0;i<m_nRGBArray;i++) m_RGBArr[i]=0;

	if (m_IntArr)		for(i=0;i<m_nIntArray;i++) m_IntArr[i]=0;

	if (m_BitmapArr)
		for(i=0;i<m_nBitmapArray;i++)
			if (m_BitmapArr[i])
			{
				try{delete m_BitmapArr[i];}catch(...){;}
				m_BitmapArr[i]=NULL;
			}

	if (m_ILBitmap)
		for(i=0;i<m_nILBitmap;i++)
			if (m_ILBitmap[i])
			{
				try{delete m_ILBitmap[i];}catch(...){;}
				m_ILBitmap[i]=NULL;
			}
}

UINT CODContext::DoMethod(const char *iStr, char *oStr)
{
	int nfunc=0;
	char met[150];
	strncpy(met,iStr,145);
	met[145]=0;
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int retint=-123456; 
	int atoipos=atoi(pos);
//	const char *pos2=pos;
//	while(*pos2 && *pos2!=',' && *pos2!='=') pos2++;
//	if (*pos2!=0) pos2++;


	if (*met>='0' && *met<='9') nfunc=atoi(met);
	else
	{
		static const char *sccArrMethods[sizeof(cArrMethods)/sizeof(char *)];
		static DWORD scdMethodsId[sizeof(cArrMethods)/sizeof(char *)];
		static int uNMethods;
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

	switch(nfunc)
	{
	case 0: //SetPen nPen,[Width],R,G,B,A
	case 1: //ClonePen nPen,[Width],SrcContext,nSrcPen
	case 2: //SetPenBrush nPen,[Width],BrushContext,nBrush
		if (atoipos>=0 && atoipos<1000)
		{
			if ((UINT)atoipos>=m_nPenArray)
			{
				CPenPlus **tmp=new CPenPlus * [atoipos+1];
				UINT i;
				for( i=0; i<m_nPenArray;i++)
					tmp[i]=m_PenArr[i];
				m_nPenArray=atoipos+1;
				for(;i<m_nPenArray;i++)
					tmp[i]=NULL;
				delete[] m_PenArr;
				m_PenArr=tmp;
			}
			CString Field2=ExtractField(pos,2,",");
			REAL m_Width=(REAL)atof(Field2);
			if (m_PenArr[atoipos]) 
			{
				delete m_PenArr[atoipos]; 
				m_PenArr[atoipos]=NULL; 
			}
			if (Field2!="NULL")
			{
				const char *pos2=FindField(pos,3,",");
				if (!pos2) pos2="";
				switch(nfunc)
				{
				case 0: //SetPen nPen,[Width],R,G,B,A
					m_PenArr[atoipos]=new CPenPlus(this,(pos2=strchr(pos,','))?++pos2:"", m_Width);
					break;
				case 1: //ClonePen SrcContext,nSrcPen
					{
						CString ContName=ExtractField(pos2,1,",");
						CODContext *ocontext=(ContName=="")?this:GPC.m_View->m_ODContextsArray->GetContext(ContName);
						UINT nPen=atoi(ExtractField(pos,2,","));
						if (nPen < ocontext->m_nPenArray && ocontext->m_PenArr[nPen])
						{
							m_PenArr[atoipos]->SetPen(ocontext->m_PenArr[nPen]->m_Pen->Clone());
							if (m_Width!=0) m_PenArr[atoipos]->m_Pen->SetWidth(m_Width);
						}
					}
					break;
				case 2: //SetPenBrush BrushContext,nBrush
					{
						CString ContName=ExtractField(pos2,1,",");
						CODContext *ocontext=(ContName=="")?this:GPC.m_View->m_ODContextsArray->GetContext(ContName);
						UINT nBrush=atoi(ExtractField(pos,2,","));
						Brush *pBr=NULL;
						if (nBrush < ocontext->m_nBrushArray && ocontext->m_BrushArr[nBrush])
						{
							m_PenArr[atoipos]=new CPenPlus(this, ocontext->m_BrushArr[nBrush]->m_Brush,m_Width);
						}
						else m_PenArr[atoipos]=new CPenPlus(this, &SolidBrush(Color(255,0,0,0)),m_Width);
					}
					break;
				}
			}
		}
		break;
	case 3: //DoPenMethod nPen,PenMethodString
		if (atoipos>=0 && (UINT)atoipos<m_nPenArray && m_PenArr[atoipos] && (pos=strchr(pos,','))) 
			m_PenArr[atoipos]->DoMethod(++pos,oStr);
		break;
	case 4: //SetBrush nBrush, Params
	case 5: //CloneBrush nBrush,SrcContext,nSrcBrush
		if (atoipos>=0 && atoipos<1000)
		{
			if ((UINT)atoipos>=m_nBrushArray)
			{
				CBrushPlus **tmp=new CBrushPlus * [atoipos+10];
				UINT i;
				for( i=0; i<m_nBrushArray;i++)
					tmp[i]=m_BrushArr[i];
				m_nBrushArray=atoipos+10;
				for(;i<m_nBrushArray;i++)
					tmp[i]=NULL;
				delete[] m_BrushArr;
				m_BrushArr=tmp;
			}
			if (m_BrushArr[atoipos]) 
			{
				delete m_BrushArr[atoipos]; 
				m_BrushArr[atoipos]=NULL; 
			}

			const char *pos2=FindField(pos,2,",");
			if (pos2 && ExtractField(pos,2,",")!="NULL")
			{
				if (nfunc==4)
					m_BrushArr[atoipos]=new CBrushPlus(this, pos2);
				else
				{
					CString ContName=ExtractField(pos2,1,",");
					CODContext *ocontext=(ContName=="")?this:GPC.m_View->m_ODContextsArray->GetContext(ContName);
					UINT nBrush=atoi(ExtractField(pos,2,","));
					if (nBrush < ocontext->m_nBrushArray && ocontext->m_BrushArr[nBrush])
						m_BrushArr[atoipos]=new CBrushPlus(this, ocontext->m_BrushArr[nBrush]);
				}
			}
		}
		break;
	case 6: //DoBrushMethod nBrush,BrushMethodString
		if (atoipos>=0 && (UINT)atoipos<m_nBrushArray && m_BrushArr[atoipos] && (pos=strchr(pos,','))) 
			m_BrushArr[atoipos]->DoMethod(++pos,oStr);
		break;
	case 7: //SetPoint nPoint,
		{
			const char *postmp=strstr(pos,"..");
			int istrt=atoipos;
			int iend=atoipos;
			if (postmp!=NULL)
			{
				while(*postmp!=0 && *postmp=='.') postmp++;
				iend=atoi(postmp);
			}
			PointF po(0,0);
			const char *curpos=FindField(pos,2,",");

			if (istrt>=0)
			{
				int nPos;
				for(nPos=istrt;nPos<=iend;nPos++)
				{
					if (curpos)
					{
						m_LastScanf=sscanf(curpos,"%g,%g",&po.X,&po.Y);
						curpos=strchr(curpos,GPC.DelimiterIn1);
						if (curpos) curpos++;
					}
					if ((UINT)nPos>=m_nPointArray)
					{
						PointF *tmp=new PointF [nPos+10];
						UINT i;
						for( i=0; i<m_nPointArray;i++)
							tmp[i]=m_PointArr[i];
						m_nPointArray=nPos+10;
						for(;i<m_nPointArray;i++)
							tmp[i].X=tmp[i].Y=0;
						delete[]  m_PointArr;
						m_PointArr=tmp;
					}
					m_PointArr[nPos]=po;
				}
			}
			else
			{
				char str[200];
				int nPos;
				for(nPos=istrt;nPos>=iend;nPos--)
				{
					if (curpos!=NULL)
					{
						m_LastScanf=sscanf(curpos,"%g,%g",&po.X,&po.Y);
						curpos=strchr(curpos,GPC.DelimiterIn1);
						if (curpos!=NULL) curpos++;
					}
					sprintf(str,"SetREAL %d,%g",(-nPos-1)*2,po.X);
					DoMethod(str,NULL);
					sprintf(str,"SetREAL %d,%g",(-nPos-1)*2+1,po.Y);
					DoMethod(str,NULL);
				}
			}
		}
		break;
	case 8: //SetRect
		{
			const char *postmp=strstr(pos,"..");
			int istrt=atoipos;
			int iend=atoipos;
			if (postmp!=NULL)
			{
				while(*postmp!=0 && *postmp=='.') postmp++;
				iend=atoi(postmp);
			}
			RectF re(0,0,0,0);
			const char *curpos=FindField(pos,2,",");

			if (istrt>=0)
			{
				int nPos;
				for(nPos=istrt;nPos<=iend;nPos++)
				{
					if (curpos!=NULL)
					{
						m_LastScanf=sscanf(curpos,"%g,%g,%g,%g",&re.X,&re.Y,&re.Width,&re.Height);
						curpos=strchr(curpos,GPC.DelimiterIn1);
						if (curpos!=NULL) curpos++;
					}

					if ((UINT)nPos>=m_nRectArray)
					{
						RectF *tmp=new RectF [nPos+10];
						UINT i;
						for( i=0; i<m_nRectArray;i++)
							tmp[i]=m_RectArr[i];
						m_nRectArray=nPos+10;
						for(;i<m_nRectArray;i++)
							tmp[i].X=tmp[i].Y=tmp[i].Width=tmp[i].Height=0;
						delete[]  m_RectArr;
						m_RectArr=tmp;
					}
					m_RectArr[nPos]=re;
				}
			}
			else
			{
				int nPos;
				for(nPos=istrt;nPos>=iend;nPos--)
					if (curpos!=NULL)
					{
						m_LastScanf=sscanf(curpos,"%d,%d,%d,%d",&re.X,&re.Y,&re.Width,&re.Height);
						curpos=strchr(curpos,GPC.DelimiterIn1);
						if (curpos!=NULL) curpos++;
					}
			}
		}
		break;
	case 9: //DeleteItem nItem
		retint=DeleteItem(atoipos);
		break;
	case 10: //DeleteItems StartItem,EndItem
		{
			UINT uStart=0,uEnd=0;
			int iEnd=m_nDraw;
			m_LastScanf=sscanf(pos,"%d,%d",&uStart,&iEnd);
			if (iEnd<0 || (UINT)iEnd>=m_nDraw) uEnd=m_nDraw-1;
			else uEnd=(UINT)iEnd;
			if (uStart<m_nDraw)
			{
				UINT i;
				for(i=uEnd-1;i>=uStart && i<=uEnd;i--)
					retint=DeleteItem(i);
			}
		}
		break;
	case 11: //AddItem ItemDescription
		{
			InsertEmptyItem(m_nDraw,1);
			SetItem(m_nDraw-1,pos);
			retint=m_nDraw;
		}
		break;
	case 12: //SetItem nItem,ItemDescription
		if (atoipos>=0 && atoipos<32000)
		{
			const char *pos2=FindField(pos,2,",");
			if (pos2) 
			{
				if ((UINT)atoipos>=m_nDraw) InsertEmptyItem(atoipos,1);
				SetItem(atoipos,pos2);
			}
		}
		break;
	case 13: //InsertItem nItem,ItemDescription
		if (atoipos>=0 && atoipos<32000)
		{
			const char *pos2=FindField(pos,2,",");
			if (pos2) 
			{
				InsertEmptyItem(atoipos,1);
				SetItem(atoipos,pos2);
			}
			retint=m_nDraw;
		}
		break;
	case 14: //InsertEmpty nItem
		{
			int iPos=0;
			UINT uCount=1;
			m_LastScanf=sscanf(pos,"%d,%d",&iPos,&uCount);
			if (iPos<0) iPos=m_nDraw;
			if (uCount==0 || uCount>5000) uCount=5000;
			InsertEmptyItem(iPos,uCount);
			retint=m_nDraw;
		}
		break;
	case 15: //AddItems ItemDescription
	case 16: //SetItems
		{
			char *str=new char [(int)strlen(pos)+10];
			char tmpstr[1000];
			strcpy(str,pos);
			char *pos22=str;
			while(pos22!=NULL && *pos22!=0)
			{
				char *postmp=strchr(pos22,GPC.DelimiterIn1);
				if (postmp!=NULL) *(postmp++)=0;
				strcpy(tmpstr,nfunc==15?"AddItem ":"SetItem ");
				strncpy(tmpstr+8,pos22,990);
				tmpstr[998]=0;
				DoMethod(tmpstr,NULL);
				pos22=postmp;
			}
			delete[] str;
			retint=m_nDraw;
		}
		break;
	case 17: //SetText Index,Text
	case 84: //SetString Index,Text
		if (atoipos>=0 && atoipos<10000)
		{
			const char *pos2=FindField(pos,2,",");
			if (!pos2) pos2="";
			if ((UINT)atoipos>=m_nStringArray)
			{
				CString *tmp=new CString [atoipos+10];
				UINT i;
				for( i=0; i<m_nStringArray;i++)
					tmp[i]=m_StringArr[i];
				m_nStringArray=atoipos+10;
				for(;i<m_nStringArray;i++)
					tmp[i]="";
				delete[]  m_StringArr;
				m_StringArr=tmp;
			}
			m_StringArr[atoipos]=pos2;
		}
		break;
	case 18: //SetInt Index,Value
		if (atoipos>=0 && atoipos<100000)
		{
			const char *postmp=strstr(pos,"..");
			int istrt=atoipos;
			int iend=atoipos;
			if (postmp!=NULL)
			{
				while(*postmp!=0 && *postmp=='.') postmp++;
				iend=atoi(postmp);
			}
			int tmpint=0;
			const char *curpos=FindField(pos,2,",");

			int nPos;
			for(nPos=istrt;nPos<=iend;nPos++)
			{
				if (curpos!=NULL)
				{
					if (*curpos=='S' && curpos[1]=='M' && curpos[2]=='_')
					{
						char tmpss[100];
						strncpy(tmpss,curpos,90);
						char *tmpp=strchr(tmpss,GPC.DelimiterIn1);
						if (tmpp) *tmpp=0;
						int nc;
						for(nc=0;*CDlgViewSystemMethods::chMetricsNames[nc] && _stricmp(CDlgViewSystemMethods::chMetricsNames[nc],tmpss)!=0;nc++);
						tmpint=::GetSystemMetrics(CDlgViewSystemMethods::uMetricsNames[nc]);
					}
					else 
						tmpint=atoi(curpos);
					curpos=strchr(curpos,GPC.DelimiterIn1);
					if (curpos!=NULL) curpos++;
				}

				if ((UINT)nPos>=m_nIntArray)
				{
					int *tmp=new int [nPos+10];
					UINT i;
					for( i=0; i<m_nRectArray;i++)
						tmp[i]=m_IntArr[i];
					m_nIntArray=nPos+10;
					for(;i<m_nIntArray;i++)
						tmp[i]=0;
					delete[]  m_IntArr;
					m_IntArr=tmp;
				}
				m_IntArr[nPos]=tmpint;
			}
		}
		break;
	case 19: //SetREAL Index,Value
		if (atoipos>=0 && atoipos<100000)
		{
			const char *postmp=strstr(pos,"..");
			int istrt=atoipos;
			int iend=atoipos;
			if (postmp!=NULL)
			{
				while(*postmp!=0 && *postmp=='.') postmp++;
				iend=atoi(postmp);
			}
			REAL tmpdou=0;
			const char *curpos=FindField(pos,2,",");

			int nPos;
			for(nPos=istrt;nPos<=iend;nPos++)
			{
				if (curpos!=NULL)
				{
					tmpdou=(REAL)atof(curpos);
					curpos=strchr(curpos,GPC.DelimiterIn1);
					if (curpos!=NULL) curpos++;
				}
				if ((UINT)nPos>=m_nREALArray)
				{
					REAL *tmp=new REAL [nPos+10];
					UINT i;
					for( i=0; i<m_nREALArray;i++)
						tmp[i]=m_REALArr[i];
					m_nREALArray=nPos+10;
					for(;i<m_nREALArray;i++)
						tmp[i]=0;
					delete[] m_REALArr;
					m_REALArr=tmp;
				}
				m_REALArr[nPos]=tmpdou;
			}
		}
		break;
	case 20: //SetColor Index,R,G,B,A
		if (atoipos>=0 && atoipos<1000)
		{
			if ((UINT)atoipos>=m_nRGBArray)
			{
				Color *tmp=new Color[atoipos+10];
				UINT i;
				for( i=0; i<m_nRGBArray;i++)
					tmp[i]=m_RGBArr[i];
				m_nRGBArray=atoipos+10;
				for(;i<m_nRGBArray;i++)
					tmp[i]=0;
				delete[] m_RGBArr;
				m_RGBArr=tmp;
			}

			const char *pos2=FindField(pos,2,",");
			if (!pos2) pos2="";
			if (strncmp(pos2,"COLOR_",6)==0 || strncmp(pos2,"CLR",3)==0)
			{
				//CLR(...)
				PDCIPARAMETER mparam=NULL;
				DCParamType pta[]={DCPT_COLOR,DCPT_NONE};
				UINT tmpNParams=0;
				CODContextItem::TranslateParams(pos2,pta,this,&(mparam),&tmpNParams);
				if (mparam)
				{
					if ((mparam[0].dwParamType&DCPT_TYPEMASK)==DCPT_COLOR)
					{
						CODContextItem::PrepareParameter(this,&(mparam[0]));
						m_RGBArr[atoipos]=*(mparam[0].m_pColor);
					}
					CODContextItem::ResetParameters(&mparam,&tmpNParams);
					delete []mparam;
				}
			}
			else
			if (*pos2>64 && *pos2<=127)
			{
				int nc=0;
				for(nc=0;*CODContext::ccANamedColors[nc] && _stricmp(CODContext::ccANamedColors[nc],pos2)!=0;nc++);
				m_RGBArr[atoipos].SetValue(CODContext::iANamedColors[nc]);
			}
			else
			if (*pos2=='0' && (pos2[1]=='x' || pos2[1]=='X'))
			{
				DWORD c=0;
				m_LastScanf=sscanf(pos2+2,"%X",&c);
				m_RGBArr[atoipos].SetValue(c);
			}
			else
				m_RGBArr[atoipos]=CODContext::GetColorFromString(this, pos2);
		}
		break;
	case 21: //ScrollPoint nBegin,nEnd,nTime
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nPointArray) nEnd=m_nPointArray-1;
			qscroll(m_PointArr,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 22: //ScrollRect nBegin,nEnd,nTime
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nRectArray) nEnd=m_nRectArray-1;
			qscroll(m_RectArr,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 23: //ScrollPen nBegin,nEnd,nTime
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nPenArray) nEnd=m_nPenArray-1;
			qscroll((void **)m_PenArr,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 24: //ScrollBrush nBegin,nEnd,nTime
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nBrushArray) nEnd=m_nBrushArray-1;
			qscroll((void **)m_BrushArr,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 25: //ScrollItem nBegin,nEnd,nTime
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nDrawArray) nEnd=m_nDrawArray-1;
			qscroll((void **)m_ArrDrawItems,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 26: //ScrollInt nBegin,nEnd,nTime
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nIntArray) nEnd=m_nIntArray-1;
			qscroll(m_IntArr,nBegin,nEnd,nTime,uEvery);	
		}
		break;
	case 27: //ScrollREAL nBegin,nEnd,nTime
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nREALArray) nEnd=m_nREALArray-1;
			qscroll(m_REALArr,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 28: //ScrollColor nBegin,nEnd,nTime
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nRGBArray) nEnd=m_nRGBArray-1;
			qscroll(m_RGBArr,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 29: //ScrollText nBegin,nEnd,nTime
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nStringArray) nEnd=m_nStringArray-1;
			qscroll(m_StringArr,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 30: //SetTimer nTimer,nDelay,dValue,dDelta,dStop,bRedraw
		{
			DRAWTIMERPLUS tmp={0};
			InitDRAWTIMERPLUS(&tmp, this);
			m_LastScanf=sscanf(pos,"%d,%d,%lg,%lg,%lg,%d",&tmp.nTimer,&tmp.nDelay,&tmp.dValue,&tmp.dDelta,&tmp.dStop,&tmp.bRedraw);
			if (tmp.nTimer>=0)
			{
				KillDrawTimer(tmp.nTimer, this);
				tmp.dwTimerProcId=SetTimer(NULL,0,tmp.nDelay,&DrawTimerProc);
				m_AllDrawTimers[tmp.dwTimerProcId]=tmp;
			}
		}
		break;
	case 31: //KillTimer nTimer
		KillDrawTimer(atoipos, this);
		break;
	case 32: //SetFont nFont,FontDescription
		if (atoipos>=0 && atoipos<200)
		{
			const char *pos2=FindField(pos,2,",");
			if (pos2)
			{
				if ((UINT)atoipos>=m_nFontArray)
				{
					CFontPlus **tmp=new CFontPlus * [atoipos+1];
					UINT i;
					for( i=0; i<m_nFontArray;i++)
						tmp[i]=m_FontArr[i];
					m_nFontArray=atoipos+1;
					for(;i<m_nFontArray;i++)
						tmp[i]=NULL;
					delete[] m_FontArr;
					m_FontArr=tmp;
				}
				if (m_FontArr[atoipos]) 
				{
					delete m_FontArr[atoipos]; 
					m_FontArr[atoipos]=NULL; 
				}
				m_FontArr[atoipos]=new CFontPlus(pos2);
			}
		}
		break;
	case 33: //ScrollFont nBegin,nEnd,nTime
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nFontArray) nEnd=m_nFontArray-1;
			qscroll((void **)m_FontArr,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 34: //DoFontMethod nFont,FontMethodString
		if (atoipos>=0 && (UINT)atoipos<m_nFontArray && m_FontArr[atoipos] && (pos=strchr(pos,','))) 
			m_FontArr[atoipos]->DoMethod(++pos,oStr);
		break;
	case 35: //SetRegion nRegion,RegionDescription
		if (atoipos>=0 && atoipos<500)
		{
			if ((UINT)atoipos>=m_nRgnArray)
			{
				CRgnPlus **tmp=new CRgnPlus * [atoipos+1];
				UINT i;
				for( i=0; i<m_nRgnArray;i++)
					tmp[i]=m_RgnArr[i];
				m_nRgnArray=atoipos+1;
				for(;i<m_nRgnArray;i++)
					tmp[i]=NULL;
				delete[] m_RgnArr;
				m_RgnArr=tmp;
			}

			if (m_RgnArr[atoipos]) delete m_RgnArr[atoipos];
			m_RgnArr[atoipos]=NULL;
			if (*pos) m_RgnArr[atoipos]=new CRgnPlus(this, FindField(pos,2,",")); 
		}
		break;
	case 36: //DoRegionMethod nRegion,RegionMethodString
		if (atoipos>=0 && (UINT)atoipos<m_nRgnArray && m_RgnArr[atoipos] && (pos=strchr(pos,','))) 
			m_RgnArr[atoipos]->DoMethod(++pos,oStr);
		break;
	case 37: //ScrollRegion nBegin,nEnd,nTime
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nRgnArray) nEnd=m_nRgnArray-1;
			qscroll((void **)m_RgnArr,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 38: //CloneRegion nRegion,SrcContext,nSrcRegion
	case 39: //SetRegionFromPath nRegion,SrcContext,nSrcPath
	case 40: //SetRegionFromRect nRegion,SrcContext,nSrcRect
		if (atoipos>=0 && atoipos<1000)
		{
			const char *pos2=FindField(pos,2,",");
			if (pos2) 
			{
				if ((UINT)atoipos>=m_nRgnArray)
				{
					CRgnPlus **tmp=new CRgnPlus * [atoipos+1];
					UINT i;
					for( i=0; i<m_nRgnArray;i++)
						tmp[i]=m_RgnArr[i];
					m_nRgnArray=atoipos+1;
					for(;i<m_nRgnArray;i++)
						tmp[i]=NULL;
					delete[] m_RgnArr;
					m_RgnArr=tmp;
				}
				if (m_RgnArr[atoipos]) delete m_RgnArr[atoipos];
				m_RgnArr[atoipos]=NULL;

				CString ContName=ExtractField(pos2,1,",");
				CODContext *ocontext=(ContName=="")?this:GPC.m_View->m_ODContextsArray->GetContext(ContName);
				UINT nRgn=atoi(ExtractField(pos2,2,","));
				if (nfunc==38)
				{
					if (nRgn < ocontext->m_nRgnArray && ocontext->m_RgnArr[nRgn])
					m_RgnArr[atoipos]=new CRgnPlus(this, ocontext->m_RgnArr[nRgn]);
				}
				else
				if (nfunc==39)
				{
					if (nRgn < ocontext->m_nGraphPathArray && ocontext->m_GraphPathArr[nRgn])
					m_RgnArr[atoipos]=new CRgnPlus(this, ocontext->m_GraphPathArr[nRgn]->m_GraphicsPath);
				}
				else
				if (nfunc==40)
				{
					int inRect=(int)nRgn;
					if (inRect<0 && (UINT)(-inRect-1)*4<m_nREALArray)
					{
						RectF Re(0,0,0,0);
						Re.X=m_REALArr[-inRect-1];
						Re.Y=m_REALArr[-inRect];
						Re.Width=m_REALArr[-inRect+1];
						Re.Height=m_REALArr[-inRect+2];
						m_RgnArr[atoipos]=new CRgnPlus(this, Re);
					}
					else
					if (nRgn < ocontext->m_nRectArray)
						m_RgnArr[atoipos]=new CRgnPlus(this, ocontext->m_RectArr[nRgn]);
				}
			}
		}
		break;
	case 41: //SetPath nPath, PathDescription
		if (atoipos>=0 && atoipos<500)
		{
			if ((UINT)atoipos>=m_nGraphPathArray)
			{
				CGraphicsPathPlus **tmp=new CGraphicsPathPlus * [atoipos+1];
				UINT i;
				for( i=0; i<m_nGraphPathArray;i++)
					tmp[i]=m_GraphPathArr[i];
				m_nGraphPathArray=atoipos+1;
				for(;i<m_nGraphPathArray;i++)
					tmp[i]=NULL;
				delete[] m_GraphPathArr;
				m_GraphPathArr=tmp;
			}

			if (m_GraphPathArr[atoipos]) delete m_GraphPathArr[atoipos];
			m_GraphPathArr[atoipos]=NULL;
			if (*pos) m_GraphPathArr[atoipos]=new CGraphicsPathPlus(this, FindField(pos,2,",")); 
		}
		break;
	case 42: //DoPathMethod nPath,PathMethodString
		if (atoipos>=0 && (UINT)atoipos<m_nGraphPathArray && m_GraphPathArr[atoipos] && (pos=strchr(pos,','))) 
			m_GraphPathArr[atoipos]->DoMethod(++pos,oStr);
		break;
	case 43: //ScrollPath nBegin,nEnd,nTime
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nGraphPathArray) nEnd=m_nGraphPathArray-1;
			qscroll((void **)m_GraphPathArr,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 44: //ClonePath nPath,SrcContext,nSrcPath
		if (atoipos>=0 && atoipos<1000)
		{
			const char *pos2=FindField(pos,2,",");
			if (pos2) 
			{
				if ((UINT)atoipos>=m_nGraphPathArray)
				{
					CGraphicsPathPlus **tmp=new CGraphicsPathPlus * [atoipos+1];
					UINT i;
					for( i=0; i<m_nGraphPathArray;i++)
						tmp[i]=m_GraphPathArr[i];
					m_nGraphPathArray=atoipos+1;
					for(;i<m_nGraphPathArray;i++)
						tmp[i]=NULL;
					delete[] m_GraphPathArr;
					m_GraphPathArr=tmp;
				}
				if (m_GraphPathArr[atoipos]) delete m_GraphPathArr[atoipos];
				m_GraphPathArr[atoipos]=NULL;

				CString ContName=ExtractField(pos2,1,",");
				CODContext *ocontext=(ContName=="")?this:GPC.m_View->m_ODContextsArray->GetContext(ContName);
				UINT nGraf=atoi(ExtractField(pos,2,","));
				if (nGraf < ocontext->m_nGraphPathArray && ocontext->m_GraphPathArr[nGraf])
					m_GraphPathArr[atoipos]=new CGraphicsPathPlus(this, ocontext->m_GraphPathArr[nGraf]->m_GraphicsPath->Clone());
			}
		}
		break;
	case 45: //SetStringFormat nStringFormat,FormatFlags,language
		if (atoipos>=0 && atoipos<500)
		{
			if ((UINT)atoipos>=m_nStringFormatArray)
			{
				CStringFormatPlus **tmp=new CStringFormatPlus * [atoipos+1];
				UINT i;
				for( i=0; i<m_nStringFormatArray;i++)
					tmp[i]=m_StringFormatArr[i];
				m_nStringFormatArray=atoipos+1;
				for(;i<m_nStringFormatArray;i++)
					tmp[i]=NULL;
				delete[] m_StringFormatArr;
				m_StringFormatArr=tmp;
			}

			if (m_StringFormatArr[atoipos]) delete m_StringFormatArr[atoipos];
			m_StringFormatArr[atoipos]=NULL;
			if (*pos) m_StringFormatArr[atoipos]=new CStringFormatPlus(this, FindField(pos,2,",")); 
		}
		break;
	case 46: //DoStringFormatMethod nStringFormat,PathMethodString
		if (atoipos>=0 && (UINT)atoipos<m_nStringFormatArray && m_StringFormatArr[atoipos] && (pos=strchr(pos,','))) 
			m_StringFormatArr[atoipos]->DoMethod(++pos,oStr);
		break;
	case 47: //ScrollStringFormat nBegin,nEnd,nTime
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nStringFormatArray) nEnd=m_nStringFormatArray-1;
			qscroll((void **)m_StringFormatArr,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 48: //CloneStringFormat nStringFormat,SrcContext,nSrcStringFormat
		if (atoipos>=0 && atoipos<1000)
		{
			const char *pos2=FindField(pos,2,",");
			if (pos2) 
			{
				if ((UINT)atoipos>=m_nStringFormatArray)
				{
					CStringFormatPlus **tmp=new CStringFormatPlus * [atoipos+1];
					UINT i;
					for( i=0; i<m_nStringFormatArray;i++)
						tmp[i]=m_StringFormatArr[i];
					m_nStringFormatArray=atoipos+1;
					for(;i<m_nStringFormatArray;i++)
						tmp[i]=NULL;
					delete[] m_StringFormatArr;
					m_StringFormatArr=tmp;
				}
				if (m_StringFormatArr[atoipos]) delete m_StringFormatArr[atoipos];
				m_StringFormatArr[atoipos]=NULL;

				CString ContName=ExtractField(pos2,1,",");
				CODContext *ocontext=(ContName=="")?this:GPC.m_View->m_ODContextsArray->GetContext(ContName);
				UINT nGraf=atoi(ExtractField(pos,2,","));
				if (nGraf < ocontext->m_nStringFormatArray && ocontext->m_StringFormatArr[nGraf])
					m_StringFormatArr[atoipos]=new CStringFormatPlus(this, ocontext->m_StringFormatArr[nGraf]->m_StringFormat->Clone());
			}
		}
		break;
	case 49: //SetBitmap  nBitmap,width,height,format
	case 50: //SetBitmapFromFile nBitmap,Filename,useIcm
	case 51: //SetBitmapFromIL nBitmap,ILname,nImage
	case 52: //SetBitmapIndirect nBitmap,.....
	case 53: //SetBitmapFromResource nBitmap,.....
		if (atoipos>=0 && atoipos<500)
		{
			const char *pos2=FindField(pos,2,",");
			if (pos2)
			{
				if ((UINT)atoipos>=m_nBitmapArray)
				{
					CBitmapPlus **tmp=new CBitmapPlus * [atoipos+1];
					UINT i;
					for( i=0; i<m_nBitmapArray;i++)
						tmp[i]=m_BitmapArr[i];
					m_nBitmapArray=atoipos+1;
					for(;i<m_nBitmapArray;i++)
						tmp[i]=NULL;
					delete[] m_BitmapArr;
					m_BitmapArr=tmp;
				}

				if (m_BitmapArr[atoipos]) delete m_BitmapArr[atoipos];
				m_BitmapArr[atoipos]=NULL;
				switch(nfunc)
				{
				case 49: //SetBitmap  nBitmap,width,height,format
				case 50: //SetBitmapFromFile nBitmap,Filename,useIcm
				case 51: //SetBitmapFromIL nBitmap,ILname,nImage
				case 52: //SetBitmapIndirect nBitmap,.....
				case 53: //SetBitmapFromResource nBitmap,.....
					if (*pos) m_BitmapArr[atoipos]=new CBitmapPlus(this,nfunc-49, pos2); 
					break;
				}
			}
		}
		break;
	case 54: //DoBitmapMethod nBitmap,BitmapMethodString
		if (atoipos>=0 && (UINT)atoipos<m_nBitmapArray && m_BitmapArr[atoipos] && (pos=strchr(pos,','))) 
			m_BitmapArr[atoipos]->DoMethod(++pos,oStr);
		break;
	case 55: //ScrollBitmap nBegin,nEnd,nTime
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nBitmapArray) nEnd=m_nBitmapArray-1;
			qscroll((void **)m_BitmapArr,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 56: //CloneBitmap nBitmap,SrcContext,nSrcBitmap,X,Y,CX,CY,PixelFormat
	case 57: //CloneBitmapR nBitmap,SrcContext,nSrcBitmap,SrcRectContext,nRect,PixelFormat
		if (atoipos>=0 && atoipos<1000)
		{
			const char *pos2=FindField(pos,2,",");
			if (pos2)
			{
				if ((UINT)atoipos>=m_nBitmapArray)
				{
					CBitmapPlus **tmp=new CBitmapPlus * [atoipos+1];
					UINT i;
					for( i=0; i<m_nBitmapArray;i++)
						tmp[i]=m_BitmapArr[i];
					m_nBitmapArray=atoipos+1;
					for(;i<m_nBitmapArray;i++)
						tmp[i]=NULL;
					delete[] m_BitmapArr;
					m_BitmapArr=tmp;
				}
				if (m_BitmapArr[atoipos]) delete m_BitmapArr[atoipos];
				m_BitmapArr[atoipos]=NULL;

				CString ContName=ExtractField(pos2,1,",");
				CODContext *ocontext=(ContName=="")?this:GPC.m_View->m_ODContextsArray->GetContext(ContName);
				UINT nGraf=atoi(ExtractField(pos2,2,","));
				if (nGraf < ocontext->m_nBitmapArray && ocontext->m_BitmapArr[nGraf])
				{
					const char *pos3=FindField(pos2,3,",");
					if (pos3 && *pos3)
					{
						RectF re(0,0,16,16);
						PixelFormat pixelFormat=PixelFormat32bppARGB;
						const char *pos4="";
						if (nfunc==56)//X,Y,CX,CY,PixelFormat
						{
							pos4=FindField(pos3,5,",");
							sscanf(pos3,"%g,%g,%g,%g",&re.X,&re.Y,&re.Width,&re.Height);
						}
						else //SrcRectContext,nRect,PixelFormat
						{
							pos4=FindField(pos3,3,",");
							ContName=ExtractField(pos3,1,",");
							CODContext *ocontext=(ContName=="")?this:GPC.m_View->m_ODContextsArray->GetContext(ContName);
							UINT nRect=atoi(ExtractField(pos3,2,","));
							if (nRect < ocontext->m_nRectArray) re=ocontext->m_RectArr[nRect];
						}
						if (pos4 && *pos4)
						{
							if (*pos4>='0' && *pos4<='9') pixelFormat=atoi(pos4);
							else
							{
								int i;
								for(i=0;*CBitmapPlus::ccAPixelFormat[i] && _stricmp(pos3,CBitmapPlus::ccAPixelFormat[i])!=0;i++);
								pixelFormat=CBitmapPlus::iAPixelFormat[i];
							}
						}
						m_BitmapArr[atoipos]=new CBitmapPlus(this, ocontext->m_BitmapArr[nGraf]->m_Bitmap->Clone(re,pixelFormat),FALSE);
					}
				}
			}
		}
		break;
	case 58: //Print
		{
			int Dlg=0,Paper=-12345,Orient=-12345;
			WndPrint::TranslateParam(pos, Dlg,Paper,Orient);
			CRect re;
			::GetClientRect(m_CurHWND,&re);
			RectF tmprect((REAL)re.left,(REAL)re.top,(REAL)re.Width(),(REAL)re.Height());
			PrintDrawWnd(Dlg,Orient,Paper,tmprect,NULL);
		}
		break;
	case 59: //PrnName	m_DrawName=pos;	
		break;
	case 60: //PrnMargins
		m_PrintMargins=CRect(2000,2000,2000,2000);
		m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&m_PrintMargins.left,&m_PrintMargins.top,&m_PrintMargins.right,&m_PrintMargins.bottom);
		break;
	case 61: //PrnWinExt
		m_PrintWinExt=CSize(-12345,-12345);
		m_LastScanf=sscanf(pos,"%d,%d",&m_PrintWinExt.cx,&m_PrintWinExt.cy);
		break;
	case 62: //PrnWinOrg
		m_PrintWinOrg=Point(-12345,-12345);
		m_LastScanf=sscanf(pos,"%d,%d",&m_PrintWinOrg.X,&m_PrintWinOrg.Y);
		break;
	case 63: //PrnVieExt
		m_PrintVieExt=CSize(-12345,-12345);
		m_LastScanf=sscanf(pos,"%d,%d",&m_PrintVieExt.cx,&m_PrintVieExt.cy);
		break;
	case 64: //PrnVieOrg
		m_PrintVieOrg=Point(-12345,-12345);
		m_LastScanf=sscanf(pos,"%d,%d",&m_PrintVieOrg.X,&m_PrintVieOrg.Y);
		break;
	case 65: //LogSize
		if (oStr)	sprintf(oStr,"%d\x7F%d",m_LogSize.cx,m_LogSize.cy);
		m_LogSize.cx=m_LogSize.cy=0;
		m_LastScanf=sscanf(pos,"%d,%d",&m_LogSize.cx,&m_LogSize.cy);
		break;
	case 66: //Redraw
		{
			int nWnd=m_AllDrawHWND.SelectFirst();
			m_uRedrawFlag=1;
			while(nWnd>=0)
			{
				HWND tmpHWND=m_AllDrawHWND.GetSelected();
				if (::IsWindow(tmpHWND))
				{
					CWnd::FromHandle(tmpHWND)->Invalidate();
					nWnd=m_AllDrawHWND.SelectNext();
				}
				else m_AllDrawHWND.RemoveSelected();
			}
		}
		break;
	case 67: //SetAutoRedraw
		retint=m_bAutoRedraw;
		m_bAutoRedraw=atoi(pos);
		break;
	case 68: //SetEraseBkg
		retint=m_bEraseBkg;
		m_bEraseBkg=atoi(pos);
		break;
	case 69: //SetMatrix nMatrix,MatrixDescription
		if (atoipos>=0 && atoipos<500)
		{
			if ((UINT)atoipos>=m_nMatrixArray)
			{
				CMatrixPlus **tmp=new CMatrixPlus * [atoipos+1];
				UINT i;
				for( i=0; i<m_nMatrixArray;i++)
					tmp[i]=m_MatrixArr[i];
				m_nMatrixArray=atoipos+1;
				for(;i<m_nMatrixArray;i++)
					tmp[i]=NULL;
				delete[] m_MatrixArr;
				m_MatrixArr=tmp;
			}

			if (m_MatrixArr[atoipos]) delete m_MatrixArr[atoipos];
			m_MatrixArr[atoipos]=NULL;
			if (*pos) m_MatrixArr[atoipos]=new CMatrixPlus(this, FindField(pos,2,",")); 
		}
		break;
	case 70: //DoMatrixMethod nFont,FontMethodString
		if (atoipos>=0 && (UINT)atoipos<m_nMatrixArray && m_MatrixArr[atoipos] && (pos=strchr(pos,','))) 
			m_MatrixArr[atoipos]->DoMethod(++pos,oStr);
		break;
	case 71: //ScrollMatrix nBegin,nEnd,nTime
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nMatrixArray) nEnd=m_nMatrixArray-1;
			qscroll((void **)m_MatrixArr,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 72: //CloneMatrix nMatrix,SrcContext,nSrcMatrix
		if (atoipos>=0 && atoipos<1000)
		{
			if ((UINT)atoipos>=m_nMatrixArray)
			{
				CMatrixPlus **tmp=new CMatrixPlus * [atoipos+1];
				UINT i;
				for( i=0; i<m_nMatrixArray;i++)
					tmp[i]=m_MatrixArr[i];
				m_nMatrixArray=atoipos+1;
				for(;i<m_nMatrixArray;i++)
					tmp[i]=NULL;
				delete[] m_MatrixArr;
				m_MatrixArr=tmp;
			}
			if (m_MatrixArr[atoipos]) delete m_MatrixArr[atoipos];
			m_MatrixArr[atoipos]=NULL;
			const char *pos2=FindField(pos,2,",");
			if (pos2)
			{
				CString ContName=ExtractField(pos2,1,",");
				CODContext *ocontext=(ContName=="")?this:GPC.m_View->m_ODContextsArray->GetContext(ContName);
				UINT nMatrix=atoi(ExtractField(pos,2,","));
				if (nMatrix < ocontext->m_nMatrixArray && ocontext->m_MatrixArr[nMatrix])
					m_MatrixArr[atoipos]=new CMatrixPlus(this, ocontext->m_MatrixArr[nMatrix]->m_Matrix);
			}
		}
		break;
	case 73: //LoadImageList ListName,FileName,bUseIcm
		{
			CString CSListName=ExtractField(pos,1,",");
			CString CSFileName=ExtractField(pos,2,",");
			DWORD dwUseIcm=atoi(ExtractField(pos,3,","));
			if (CSFileName!="" && CSListName!="")
			{
				UINT i,j;
				for(i=0;i<m_nILBitmap && (m_ILBitmap[i]==NULL || m_ILBitmap[i]->CreationString!=CSListName);i++);
				if (i<m_nILBitmap && m_ILBitmap[i]) 
				{
					delete m_ILBitmap[i];
					m_ILBitmap[i]=NULL;
				}
				for(i=0;i<m_nILBitmap && m_ILBitmap[i];i++);
				if (i>=m_nILBitmap)
				{
					CBitmapPlus **tmp=new CBitmapPlus * [i+10];
					for( j=0; j<m_nILBitmap;j++)
						tmp[j]=m_BitmapArr[j];
					m_nILBitmap=i+10;
					for(;i<m_nILBitmap;j++) tmp[j]=NULL;
					delete[] m_ILBitmap;
					m_ILBitmap=tmp;
				}
				CString tmpFname=CSFileName;

				if ((j=_access(tmpFname,0))!=0) tmpFname="IMAGELISTS\\"+CSFileName;
				if (j!=0 && (j=_access(tmpFname,0))!=0) tmpFname="IMAGELISTS\\"+CSFileName+".TIFF";
				if (j!=0 && (j=_access(tmpFname,0))!=0)
				{
					GPImageList *MainIl=NULL;
					int ImgLId=GPC.GetImageListId(CSFileName);
					if (ImgLId>=0) MainIl=&(GPC.a_GPImageList[ImgLId]);
					if (MainIl==NULL)
					{
						ImgLId=GPC.GetImageListId("");
						MainIl=&(GPC.a_GPImageList[ImgLId]);
						if (MainIl) MainIl->LoadList(CSFileName);
					}
					if (MainIl)
					{
						CBitmapPlus *tmpB=MainIl->GetBitmap();
						if (tmpB && tmpB->m_Bitmap)
						{
							m_ILBitmap[i]=new CBitmapPlus(this,tmpB->m_Bitmap,TRUE); 
							m_ILBitmap[i]->CreationString=CSFileName;
						}
					}
				}
				else
				if (j==0 || _access(tmpFname,0)==0) 
				{
					BSTR bs=tmpFname.AllocSysString();
					m_ILBitmap[i]=new CBitmapPlus(this,bs,dwUseIcm); 
					::SysFreeString(bs);
					if (m_ILBitmap[i])
					{
						if (!m_ILBitmap[i]->m_Bitmap) 
						{
							delete m_ILBitmap[i];
							m_ILBitmap[i]=NULL;
						}
						else m_ILBitmap[i]->CreationString=CSFileName;
					}
				}
			}
		}
		break;
	case 74: //DoILBitmapMethod ILBitmapName,BitmapMethodString
		{
			CString CSListName=ExtractField(pos,1,",");
			if (CSListName!="")
			{
				UINT i;
				for(i=0;i<m_nILBitmap && (m_ILBitmap[i]==NULL || m_ILBitmap[i]->CreationString!=CSListName);i++);
				if (i<m_nILBitmap && m_ILBitmap[i] && (pos=strchr(pos,',')))
					m_ILBitmap[i]->DoMethod(++pos,oStr);
			}
		}
		break;
	case 75: //ModifyColor nColor,operation,R,G,B,A
		if (atoipos>=0 && (UINT)atoipos<m_nRGBArray)
		{
			const char *op=FindField(pos,2,",");
			const char *op2=FindField(pos,3,",");
			if (op && op2 && *op2)
			{
				REAL R1=0,G1=0,B1=0,A1=0;
				sscanf(op2,"%g,%g,%g,%g",&R1,&G1,&B1,&A1);
				REAL R=m_RGBArr[atoipos].GetRed(),G=m_RGBArr[atoipos].GetGreen(),B=m_RGBArr[atoipos].GetBlue(),A=m_RGBArr[atoipos].GetAlpha();

				switch(*op)
				{
				case '+':	R+=R1;	G+=G1;	B+=B1;	A+=A1;	break;
				case '-':	R-=R1;	G-=G1;	B-=B1;	A-=A1;	break;
				case '*':	R*=R1;	G*=G1;	B*=B1;	A*=A1;	break;
				case '/':
					if (R1!=0) R/=R1;
					if (G1!=0) G/=G1;
					if (B1!=0) B/=B1;
					if (A1!=0) A/=A1;
					break;
				case '&':
					{
						INT tmp,tmp1;
						tmp=(INT)R;tmp1=(INT)R1; tmp&=tmp1; R=(REAL)tmp;
						tmp=(INT)G;tmp1=(INT)G1; tmp&=tmp1; G=(REAL)tmp;
						tmp=(INT)B;tmp1=(INT)B1; tmp&=tmp1; B=(REAL)tmp;
						tmp=(INT)A;tmp1=(INT)A1; tmp&=tmp1; A=(REAL)tmp;
					}
					break;
				case '|':
					{
						INT tmp,tmp1;
						tmp=(INT)R;tmp1=(INT)R1; tmp|=tmp1; R=(REAL)tmp;
						tmp=(INT)G;tmp1=(INT)G1; tmp|=tmp1; G=(REAL)tmp;
						tmp=(INT)B;tmp1=(INT)B1; tmp|=tmp1; B=(REAL)tmp;
						tmp=(INT)A;tmp1=(INT)A1; tmp|=tmp1; A=(REAL)tmp;
					}
					break;
				case '^':
					{
						INT tmp,tmp1;
						tmp=(INT)R;tmp1=(INT)R1; tmp^=tmp1; R=(REAL)tmp;
						tmp=(INT)G;tmp1=(INT)G1; tmp^=tmp1; G=(REAL)tmp;
						tmp=(INT)B;tmp1=(INT)B1; tmp^=tmp1; B=(REAL)tmp;
						tmp=(INT)A;tmp1=(INT)A1; tmp^=tmp1; A=(REAL)tmp;
					}
					break;
				}
				if (R>255) R=255; if (R<0) R=0; 
				if (G>255) G=255; if (G<0) G=0; 
				if (B>255) B=255; if (B<0) B=0; 
				if (A>255) A=255; if (A<0) A=0; 
				m_RGBArr[atoipos].SetValue(Color::MakeARGB((BYTE)A,(BYTE)R,(BYTE)G,(BYTE)B));
			}
		}
		break;
	case 76: //GetInt [StartID-EndID]|[ID1,ID2,...,IDn]
	case 77: //GetREAL [StartID-EndID]|[ID1,ID2,...,IDn]
	case 78: //GetString [StartID-EndID]|[ID1,ID2,...,IDn]
	case 79: //GetRect [StartID-EndID]|[ID1,ID2,...,IDn]
	case 80: //GetPoint [StartID-EndID]|[ID1,ID2,...,IDn]
	case 81: //GetColor [StartID-EndID]|[ID1,ID2,...,IDn]
	case 82: //GetMatrix [StartID-EndID]|[ID1,ID2,...,IDn]
		if (oStr)
		{
			DWORD dwnArrItems=0;
			switch(nfunc)
			{
			case 76: //GetInt
				dwnArrItems=m_nIntArray;
				break;
			case 77: //GetREAL
				dwnArrItems=m_nREALArray;
				break;
			case 78: //GetString
				dwnArrItems=m_nStringArray;
				break;
			case 79: //GetRect
				dwnArrItems=m_nRectArray;
				break;
			case 80: //GetPoint
				dwnArrItems=m_nPointArray;
				break;
			case 81: //GetColor
				dwnArrItems=m_nRGBArray;
				break;
			case 82: //GetMatrix
				dwnArrItems=m_nMatrixArray;
				break;
			}
			DWORD *dwIDx=NULL;
			int nItems=1;
			int i;
			{
				const char *postmp;
				if ((postmp=strchr(pos,'-')))
				{
					int dwStart=atoi(pos),dwEnd=atoi(++postmp);
					if (dwStart<0)
					{
						dwStart=0;
						dwEnd=dwnArrItems-1;
					}
					if (dwEnd<0 || (DWORD)dwEnd>=dwnArrItems) dwEnd=dwnArrItems-1;
					nItems=dwEnd-dwStart+1;
					dwIDx=new DWORD [nItems];
					for(i=0;i<nItems;i++) dwIDx[i]=dwStart+i;
				}
				else
				{
					postmp=pos;
					while(*postmp)
						if (*(postmp++)==',') nItems++;
					dwIDx=new DWORD [nItems];
					DWORD *drTMP=dwIDx;
					postmp=pos;
					while(postmp)
					{
						*drTMP=atoi(postmp);
						if (*drTMP>=dwnArrItems) *drTMP=0;
						postmp=strchr(postmp,',');
						if (postmp) postmp++;
					}
				}
			}
			char *posout=oStr;
			int i2;
			for(i2=0;i2<nItems;i2++)
			{
				if (i2) {*(posout++)=0x7F; *posout=0;}
				i=dwIDx[i2];
				switch(nfunc)
				{
				case 76: //GetInt
					posout+=sprintf(posout,"%d",m_IntArr[i]);
					break;
				case 77: //GetREAL
					posout+=sprintf(posout,"%g",m_REALArr[i]);
					break;
				case 78: //GetString
					strcpy(posout,m_StringArr[i]);
					while(*posout)
					{
						if (*posout==0x7F) *posout=0x07;
						else
						if (*posout==0x07) *posout=0x03;
						else
						if (*posout>=0x01 && *posout<0x05) *posout=*posout+1;
						posout++;
					}
					break;
				case 79: //GetRect
					posout+=sprintf(posout,"%g\x7%g\x7%g\x7%g",m_RectArr[i].X,m_RectArr[i].Y,m_RectArr[i].Width,m_RectArr[i].Height);
					break;
				case 80: //GetPoint
					posout+=sprintf(posout,"%g\x7%g",m_PointArr[i].X,m_PointArr[i].Y);
					break;
				case 81: //GetColor
					posout+=sprintf(posout,"%d\x7%d\x7%d\x7%d",m_RGBArr[i].GetR(),m_RGBArr[i].GetG(),m_RGBArr[i].GetB(),m_RGBArr[i].GetA());
					break;
				case 82: //GetMatrix
					{
						REAL m[]={0,0,0,0,0,0,0,0,};
						m_MatrixArr[i]->m_Matrix->GetElements(m);
						posout+=sprintf(posout,"%g\x7%g\x7%g\x7%g\x7%g\x7%g",m[0],m[1],m[2],m[3],m[4],m[5]);
					}
					break;
				}
			}
			if (dwIDx) delete []dwIDx;

		}
		break;
	case 83: //Execute [IDSCR=;][IDDLG=;][IDOBJ=;][RECT=;]
		{
			HWND mHWND=NULL;
			DWORD IDScr=-1;
			DWORD IDDlg=-1;
			CString tmpCSIDSCR=ExtractField(ExtractField(pos,2,"IDSCR="),1,";");
			CString tmpCSIDDLG=ExtractField(ExtractField(pos,2,"IDDLG="),1,";");
			CString tmpCSIDOBJ=ExtractField(ExtractField(pos,2,"IDOBJ="),1,";");
			CString tmpCSRECT=ExtractField(ExtractField(pos,2,"RECT="),1,";");

			if (tmpCSIDSCR!="")
			{
				GPScreen *s=GPC.m_Document->GetScreenById(atoi(tmpCSIDSCR));
				if (tmpCSIDOBJ!="" && s)
				{
					s->GPActiveWindow()->GetUnitByName(tmpCSIDOBJ);
				}
				else
					mHWND=GPC.m_hViewWnd;
			}
			else
			if (tmpCSIDDLG!="")
			{
				GPUNITINFO Ui;
				if (GPC.m_Document->FindObject(tmpCSIDDLG, tmpCSIDOBJ, Ui))
					mHWND=Ui.hWnd;
			}
			if (!mHWND) mHWND=GPC.m_hViewWnd;
			if (mHWND)
			{
				RectF re(0,0,0,0);
				RECT reTmp;
				::GetClientRect(mHWND,&reTmp);
				re.Width=(REAL)(reTmp.right+1);
				re.Height=(REAL)(reTmp.bottom+1);
				if (tmpCSRECT!="")
				{
					CString tmpCS;
					tmpCS=ExtractField(tmpCSRECT,1,",");
					if (tmpCS!="") re.X=(REAL)atoi(tmpCS);
					tmpCS=ExtractField(tmpCSRECT,2,",");
					if (tmpCS!="") re.Y=(REAL)atoi(tmpCS);
					tmpCS=ExtractField(tmpCSRECT,3,",");
					if (tmpCS!="") re.Width=(REAL)atoi(tmpCS);
					tmpCS=ExtractField(tmpCSRECT,4,",");
					if (tmpCS!="") re.Height=(REAL)atoi(tmpCS);
				}
				HDC tmpDC=::GetDC(mHWND);
				if (tmpDC)
				{
					PaintToCDC(CDC::FromHandle(tmpDC),re,NULL);
					::ReleaseDC(mHWND, tmpDC);
				}
			}
		}
		break;


//	case 69: //ShowEditDialog
//		{
//			CDlgDrawEdit dlg(this,this);
//			dlg.DoModal();
//		}
//		break;


	default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
	}

	if (oStr && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);

/*	switch(nfunc)
	{
	case 0: //SetPen
	case 10: //SetBPen
	case 1: //SetBrush
	case 2: //SetPoint
	case 3: //SetRect
	case 4: //SetFont
	case 5: //DeleteItem
	case 6: //DeleteItems
	case 7: //AddItem
	case 8: //SetItem
	case 9: //InsertItem
	case 12: //SetColor
	case 13: //AddItems
	case 29: //SetItems
	case 14: //SetIcon
	case 15: //SetText
	case 84: //SetText
	case 16: //SetInt
	case 17: //SetREAL
	case 18: //ScrollPoint //nBegin,nEnd,nTime
	case 19: //ScrollRect
	case 20: //ScrollPen
	case 21: //ScrollBrush
	case 22: //ScrollFont
	case 23: //ScrollItem
	case 24: //ScrollInt
	case 25: //ScrollREAL
	case 26: //ScrollIcon
	case 27: //ScrollColor
	case 28: //ScrollText
	case 30: //SetRegion
	case 31: //OffsetRgn
	case 32: //OffsetRgnP
	case 40: //LogSize
	case 43: //SetPenWidth nPen,Width
	case 44: //SetPenColor nPen,R,G,B
	case 46: //SetAutoRedraw
		m_uRedrawFlag=TRUE;
		break;
	}

	*/
	return nfunc;
}

BOOL CODContext::InsertEmptyItem(UINT uItemBefore, UINT uCount)
{
	UINT newCount=m_nDrawArray;
	UINT i;

	if (uItemBefore>=m_nDrawArray || m_nDraw+uCount>=m_nDrawArray)
		newCount=m_nDrawArray+uCount+50;

	if (newCount>m_nDrawArray)
	{
		CODContextItem **tmpT=new  CODContextItem * [newCount];

		for(i=0; i<m_nDrawArray;i++)
			tmpT[i]=m_ArrDrawItems[i];

		m_nDrawArray=newCount;
		for(;i<m_nDrawArray;i++)
			tmpT[i]=NULL;

		delete[]  m_ArrDrawItems;
		m_ArrDrawItems=tmpT;
	}

	if (uItemBefore<m_nDraw)
		for(i=m_nDrawArray-1;i>=uItemBefore+uCount;i--)
			m_ArrDrawItems[i]=m_ArrDrawItems[i-uCount];

	for(i=uItemBefore;i<uItemBefore+uCount;i++)
		m_ArrDrawItems[i]=NULL;

	if (m_nDraw<=uItemBefore) m_nDraw=uItemBefore;
	m_nDraw+=uCount;

	return TRUE;
}

UINT CODContext::DeleteItem(UINT nItem)
{
	if (nItem<m_nDraw)
	{
		UINT i;
		DestroyItem(nItem);

		for(i=nItem;i<m_nDraw;i++)
			m_ArrDrawItems[i]=m_ArrDrawItems[i+1];

		m_ArrDrawItems[m_nDraw]=NULL;

		m_nDraw--;
	}
	return m_nDraw;
}

void CODContext::DestroyItem(UINT nItem)
{
	if (nItem<m_nDraw)
	{
		if (m_ArrDrawItems[nItem]) delete m_ArrDrawItems[nItem];
		m_ArrDrawItems[nItem]=NULL;
	}
}

BOOL CODContext::SetItem(UINT nItem, const char *cctmpiStr)
{
	BOOL ret=FALSE;
	if (nItem<m_nDraw)
	{
		if (m_ArrDrawItems[nItem]) delete m_ArrDrawItems[nItem];
		m_ArrDrawItems[nItem]=CODContextItem::SetItem(this,cctmpiStr);
		ret=TRUE;
	}
	return ret;
}

void CODContext::Paint(CPaintDC &dc, CRect &ClientRe, HBRUSH hbrBkgnd) 
{

	HBITMAP hOldBitmap;       // Handle to the old bitmap

	// Create a memory device context compatible with the device. 
	CRect re;
	dc.GetClipBox(&re);
	CDC DCMem;
	DCMem.CreateCompatibleDC (&dc);
	if (m_hDCBitmap==NULL)
	{
		m_hDCBitmap=::CreateCompatibleBitmap (dc.m_hDC, ClientRe.Width(),ClientRe.Height());
//	   ::BitBlt (DCMem.m_hDC, re.left,re.top,re.Width(),re.Height(), dc.m_hDC , re.left,re.top, SRCCOPY);
	}

	// Select the new bitmap object into the memory device context. 
	hOldBitmap = (HBITMAP)DCMem.SelectObject (m_hDCBitmap);
	if (m_uRedrawFlag)
	{
		RectF tmprect((REAL)ClientRe.left,(REAL)ClientRe.top,(REAL)ClientRe.Width(),(REAL)ClientRe.Height());
		PaintToCDC(&DCMem, tmprect, hbrBkgnd);
		m_uRedrawFlag=0;
	}

   ::BitBlt (dc.m_hDC, re.left,re.top,re.Width(),re.Height(), DCMem.m_hDC, re.left,re.top, SRCCOPY);

	// Select the old bitmap back into the device context.
	DCMem.SelectObject (hOldBitmap);
}

void CODContext::PaintToCDC(CDC *ppDC, RectF &ClientRe, HBRUSH hbrBkgnd)
{
	Graphics mGr(ppDC->m_hDC);
	PaintToGraphics(mGr, ClientRe, hbrBkgnd);
}

void CODContext::PaintToGraphics(Graphics &mGr, RectF &ClientRe, HBRUSH hbrBkgnd)
{
	Point LocOffset(0,0);
	int m_Stack[DU_NSTACK];
	UINT m_StackPos;
	for(m_StackPos=0;m_StackPos<DU_NSTACK;m_StackPos++) m_Stack[m_StackPos]=-1; 
	*m_Stack=100000;
	m_StackPos=0;
	int nOperations=0;

	UINT i;
	UINT NextJob=0xFFFFFFFF;

	for(i=0,nOperations=0;i<m_nDraw && nOperations<100000;i++,nOperations++)
	{
 		DCUnitAction m_action=m_ArrDrawItems[i]->DoAction(&mGr);
		switch(m_action)
		{
		case DCUA_GOTO:
		case DCUA_GOSUB:
			{
				NextJob=0x10000000;
				UINT j;
				for(j=0;j<m_nDraw && NextJob==0x10000000;j++)
					if (m_ArrDrawItems[j]->m_Type==DCUT_LABEL && *(m_ArrDrawItems[j]->m_Parameters->m_pCString)==*(m_ArrDrawItems[i]->m_Parameters->m_pCString)) NextJob=j+1;

				if (m_action==DCUA_GOSUB)
				{
					if (m_StackPos<DU_NSTACK-1)	m_Stack[++m_StackPos]=i+1;
					else NextJob=0x10000000;
				}
			}
			break;
		case DCUA_RETURN:
			if (m_StackPos==0) NextJob=0x10000000;
			else NextJob=m_Stack[m_StackPos--];
			break;
		case DCUA_GOTOELSE:
			{
				NextJob=0x10000000;
				UINT j;
				UINT uLevel=0;
				for(j=i+1;j<m_nDraw && NextJob==0x10000000;j++)
					switch(m_ArrDrawItems[j]->m_Type)
					{
					case  DCUT_IF: uLevel++; break;
					case  DCUT_ELSE:
						if (uLevel==0) NextJob=j+1;
						break;
					case  DCUT_ENDIF:
						if (uLevel) uLevel--;
						else		NextJob=j+1;
						break;
					}
			}
			break;
		case DCUA_GOTOENDIF:
			{
				NextJob=0x10000000;
				UINT j;
				UINT uLevel=0;
				for(j=i+1;j<m_nDraw && NextJob==0x10000000;j++)
					switch(m_ArrDrawItems[j]->m_Type)
					{
					case  DCUT_IF: uLevel++; break;
					case  DCUT_ENDIF:
						if (uLevel) uLevel--;
						else		NextJob=j+1;
						break;
					}
			}
			break;







		case DCUA_NONE:
			break;
		default:
			break;
		}

		if (NextJob<0xFFFFFFF0)
		{
			i=NextJob-1;
			NextJob=0xFFFFFFFF;
		}
	}
}

void CODContext::SetPrintAlign(CDC *pDC, HDC hdcPrn, RectF &ClientRect)
{
	short cxPage, cyPage;

	cxPage = ::GetDeviceCaps (hdcPrn, HORZRES) ;
	cyPage = ::GetDeviceCaps (hdcPrn, VERTRES) ;

	pDC->SetMapMode (MM_ISOTROPIC);

	CSize TLmarg=m_PrintMargins.TopLeft();
	CSize BRmarg=m_PrintMargins.BottomRight();

	pDC->HIMETRICtoDP(&TLmarg);
	pDC->HIMETRICtoDP(&BRmarg);


	if (m_PrintWinExt.cx!=-12345)
		pDC->SetWindowExt(m_PrintWinExt);
	else
	{
		CSize lsz=m_LogSize;
		if (m_LogSize.cx<=0 || m_LogSize.cy<=0)
		{
			lsz.cx=(LONG)ClientRect.Width;
			lsz.cy=(LONG)ClientRect.Height;
		}
		CSize lTLmarg=TLmarg;
		CSize lBRmarg=BRmarg;
		pDC->DPtoLP(&lTLmarg);
		pDC->DPtoLP(&lBRmarg);
		pDC->SetWindowExt(lsz.cx+(lTLmarg.cx+lBRmarg.cx)/2,lsz.cy+(lTLmarg.cy+lBRmarg.cy)/2);
	}
/*
	if (m_PrintWinOrg.X!=-12345)
		pDC->SetWindowOrg(m_PrintWinOrg);

	if (m_PrintVieExt.cx!=-12345)
		pDC->SetViewportExt(m_PrintVieExt);
	else
		pDC->SetViewportExt(cxPage, cyPage) ;

	if (m_PrintVieOrg.X!=-12345)
		pDC->SetViewportOrg(m_PrintVieOrg);
	else
		pDC->SetViewportOrg (TLmarg.cx,TLmarg.cy) ;
		*/
} 

void CODContext::PrintDrawWnd(int Dlg,int Orient,int Paper, RectF &ClientRect, HBRUSH hbrBkgnd)
{
	HDC    hdcPrn=NULL;

	// Instantiate a CPrintDialog.
	CPrintDialog *printDlg =
		new CPrintDialog(FALSE, PD_ALLPAGES | PD_RETURNDC|(Dlg==1?0:PD_RETURNDEFAULT), NULL);

	// Initialize some of the fields in PRINTDLG structure.
	printDlg->m_pd.nMinPage = printDlg->m_pd.nMaxPage = 1;
	printDlg->m_pd.nFromPage = printDlg->m_pd.nToPage = 1;

	printDlg->DoModal();
	DEVMODE* dm=printDlg->GetDevMode( );
	BOOL ResetFlg=FALSE;

	if (dm)
	{
		if (Orient==0 && dm->dmOrientation!=DMORIENT_PORTRAIT)
		{
			dm->dmOrientation=DMORIENT_PORTRAIT;
			ResetFlg=TRUE;
		}
		if (Orient==1 && dm->dmOrientation!=DMORIENT_LANDSCAPE)
		{
			dm->dmOrientation=DMORIENT_LANDSCAPE;
			ResetFlg=TRUE;
		}

		if (dm->dmPaperSize!=Paper && Paper!=-12345)
		{
			dm->dmPaperSize=Paper;
			ResetFlg=TRUE;
		}
	}

	// Display Windows print dialog box.

	// Obtain a handle to the device context.
	hdcPrn = printDlg->GetPrinterDC();
	if (hdcPrn != NULL)
	{
		CDC *pDC = new CDC;
		
		pDC->Attach (hdcPrn);      // attach a printer DC
		if (ResetFlg==TRUE) pDC->ResetDC(dm);

		pDC->StartDoc(m_DrawName==""?"GP_TERM.DRAW":m_DrawName);  
		pDC->StartPage();          // begin a new page
		SetPrintAlign(pDC, hdcPrn, ClientRect);// set the printing alignment
		PaintToCDC(pDC,ClientRect, hbrBkgnd);
		pDC->EndPage();            // end a page

		pDC->EndDoc();             // end a print job

		pDC->Detach();             // detach the printer DC
		delete pDC;
	}

	delete printDlg;
}


void CODContext::DeletePaintObj()
{
	if (m_hDCBitmap) DeleteObject(m_hDCBitmap);
	m_hDCBitmap=NULL;
}

void CODContext::KillDrawTimer(int iTimerId, CODContext *pContext) 
{
	int TimerId=m_AllDrawTimers.SelectFirst();
	while(TimerId>=0)
	{
		PDRAWTIMERPLUS pDT=NULL;
		pDT=&m_AllDrawTimers.GetSelected();
		if ((!pContext || pDT->pODContext==(LPARAM)pContext) && (iTimerId==-1 || pDT->nTimer==iTimerId))
		{
			KillTimer(NULL,pDT->dwTimerProcId);
			if (iTimerId<0) m_AllDrawTimers.RemoveSelected();
		}
		else TimerId=m_AllDrawTimers.SelectNext();
	}
}

DRAWTIMERPLUS CODContext::GetDrawTimer(int iTimerId) 
{
	static DRAWTIMERPLUS tmpRet;
	int TimerId=m_AllDrawTimers.SelectFirst();

	PDRAWTIMERPLUS pDT=NULL;
	while(TimerId>=0)
	{
		pDT=&m_AllDrawTimers.GetSelected();
		if (pDT->pODContext==(LPARAM)this && pDT->nTimer==iTimerId)
		{
			TimerId=-1;
			tmpRet=*pDT;
		}
		else TimerId=m_AllDrawTimers.SelectNext();
	}
	return tmpRet;
}


PDRAWTIMERPLUS CODContext::GetTimerById(int iTimerId)
{
	PDRAWTIMERPLUS pDTRet=NULL;
	int TimerId=m_AllDrawTimers.SelectFirst();
	while(!pDTRet && TimerId>=0)
	{
		PDRAWTIMERPLUS pDT=&m_AllDrawTimers.GetSelected();
		if (pDT->pODContext==(LPARAM)this && (pDT->nTimer==iTimerId))
			pDTRet=pDT;
		else 
			TimerId=m_AllDrawTimers.SelectNext();
	}

	return pDTRet;
}

PDRAWTIMERPLUS CODContext::GetTimerByProcId(DWORD idwTimerProcId)
{
	PDRAWTIMERPLUS pDTRet=NULL;
	int TimerId=m_AllDrawTimers.SelectFirst();
	while(!pDTRet && TimerId>=0)
	{
		PDRAWTIMERPLUS pDT=&m_AllDrawTimers.GetSelected();
		if (pDT->dwTimerProcId==idwTimerProcId)
			pDTRet=pDT;
		else 
			TimerId=m_AllDrawTimers.SelectNext();
	}

	return pDTRet;
}

void CODContext::InvalidateDependentWindows()
{
	int nWnd=m_AllDrawHWND.SelectFirst();
	m_uRedrawFlag=1;

	while(nWnd>=0)
	{
		HWND tmpHWND=m_AllDrawHWND.GetSelected();
		if (::IsWindow(tmpHWND))
		{
			CWnd::FromHandle(tmpHWND)->Invalidate();
			nWnd=m_AllDrawHWND.SelectNext();
		}
		else m_AllDrawHWND.RemoveSelected();
	}
}

void CODContext::PaintByDRAWITEMSTRUCT(GPUnit *gpuRes, WPARAM wParam, LPDRAWITEMSTRUCT lPDiStruct, GPMenu *pMenu, LPARAM lParam)
{
	m_IntArr[0]=(gpuRes->UnitId/0x10000)&0xFF;
	m_IntArr[1]= gpuRes->UnitId&0xFFFF;
	m_IntArr[2]=(gpuRes->UnitId)&0xFF;;
	m_IntArr[3]=lPDiStruct->CtlType;
	m_IntArr[4]=lPDiStruct->CtlID;
	m_IntArr[5]=lPDiStruct->itemID;
	m_IntArr[6]=lPDiStruct->itemAction;
	m_IntArr[7]=lPDiStruct->itemState;

	//TRACE ("%x %x\n",m_IntArr[6],m_IntArr[7]);

	m_IntArr[8]=(int)lPDiStruct->hwndItem;
	m_IntArr[9]=(int)(m_CurHDC=lPDiStruct->hDC);
	m_IntArr[10]=lPDiStruct->itemData;

	m_IntArr[11]=m_MeasureFlag;
	if (m_MeasureFlag)
	{
		m_RectArr[1].X=m_RectArr[1].Y=0;
		m_RectArr[1].Width=(REAL)m_MeasureStruct.itemWidth;
		m_RectArr[1].Height=(REAL)m_MeasureStruct.itemHeight;
	}
	m_IntArr[14]=-1;

	m_RectArr[0].X=(REAL)lPDiStruct->rcItem.left;
	m_RectArr[0].Y=(REAL)lPDiStruct->rcItem.top;
	if (lPDiStruct->rcItem.right || lPDiStruct->rcItem.left)
			m_RectArr[0].Width=(REAL)(lPDiStruct->rcItem.right-lPDiStruct->rcItem.left+1);
	else	m_RectArr[0].Width=0;

	if (lPDiStruct->rcItem.bottom || lPDiStruct->rcItem.top)
			m_RectArr[0].Height=(REAL)(lPDiStruct->rcItem.bottom-lPDiStruct->rcItem.top+1);
	else	m_RectArr[0].Height=0;

	if (lPDiStruct->hwndItem)
	{
		RECT retmp={0};
		::GetWindowRect(lPDiStruct->hwndItem,&retmp);
		m_RectArr[2].X=(REAL)retmp.left;
		m_RectArr[2].Y=(REAL)retmp.top;
		m_RectArr[2].Width=(REAL)(retmp.right-retmp.left+1);
		m_RectArr[2].Height=(REAL)(retmp.bottom-retmp.top+1);
		::GetClientRect(lPDiStruct->hwndItem,&retmp);
		m_RectArr[3].X=(REAL)retmp.left;
		m_RectArr[3].Y=(REAL)retmp.top;
		m_RectArr[3].Width=(REAL)(retmp.right-retmp.left+1);
		m_RectArr[3].Height=(REAL)(retmp.bottom-retmp.top+1);
	}
	m_StringArr[0]="";
	m_RectArr[4]=m_RectArr[0];
	m_RectArr[4].X=m_RectArr[4].Y=0;

	if (lPDiStruct->CtlType==ODT_LISTVIEW)
	{
		if (m_IntArr[11])
		{
			CRect re;
			m_RectArr[7]=m_RectArr[0];

			m_CurHDC=lPDiStruct->hDC;
			if (gpuRes->m_brBkgnd)
				PaintToCDC(CDC::FromHandle(lPDiStruct->hDC),m_RectArr[0],(HBRUSH)gpuRes->m_brBkgnd->m_hObject);
			else
				PaintToCDC(CDC::FromHandle(lPDiStruct->hDC),m_RectArr[0],NULL);
		
			m_MeasureStruct.itemWidth+=(UINT)m_RectArr[1].Width;
			m_MeasureStruct.itemHeight=(UINT)m_RectArr[1].Height;
			m_RectArr[0]=m_RectArr[7];
		}
		else
		if (lPDiStruct->hwndItem)
		{
			if (((int)lPDiStruct->itemID)>=0)
			{
				int nSubItem;
				CHeaderCtrl *tmphc=((GPListCtr *)gpuRes->UnitPtr)->GetHeaderCtrl();
				int nItems=(tmphc)?tmphc->GetItemCount():1;
				int *OrderArray=new int[nItems+1];
				*OrderArray=0;
				((GPListCtr *)gpuRes->UnitPtr)->GetColumnOrderArray(OrderArray,nItems);
				CRect re;
				char *tmpstr=new char [10000];
				m_RectArr[7]=m_RectArr[0];
				int lastRight=0;
				for(nSubItem=0;nSubItem<nItems;nSubItem++)
				{
					((GPListCtr *)gpuRes->UnitPtr)->GetSubItemRect((int)lPDiStruct->itemID,OrderArray[nSubItem],LVIR_BOUNDS,re);
					if (OrderArray[nSubItem]==0)
					{
						re.left=lastRight;
						re.right=re.left+((GPListCtr *)gpuRes->UnitPtr)->GetColumnWidth(OrderArray[nSubItem])+1;
					}
					lastRight=re.right;

					if (re.right>0 && re.left<m_RectArr[3].Width && re.top<m_RectArr[3].Height)
					{
						m_RectArr[4].X=(REAL)re.left;
						m_RectArr[4].Y=(REAL)re.top;
						m_RectArr[4].Width=(REAL)re.Width();
						m_RectArr[4].Height=(REAL)re.Height();
						m_RectArr[0]=m_RectArr[4];
						((GPListCtr *)gpuRes->UnitPtr)->GetSubItemRect((int)lPDiStruct->itemID,OrderArray[nSubItem],LVIR_ICON,re);
						m_RectArr[5].X=(REAL)re.left;
						m_RectArr[5].Y=(REAL)re.top;
						m_RectArr[5].Width=(REAL)re.Width();
						m_RectArr[5].Height=(REAL)re.Height();
						((GPListCtr *)gpuRes->UnitPtr)->GetSubItemRect((int)lPDiStruct->itemID,OrderArray[nSubItem],LVIR_LABEL,re);
						m_RectArr[6].X=(REAL)re.left;
						m_RectArr[6].Y=(REAL)re.top;
						m_RectArr[6].Width=(REAL)re.Width();
						m_RectArr[6].Height=(REAL)re.Height();

						LVITEM lvi={0};
						*tmpstr=0;
						lvi.mask=LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM|LVIF_STATE|LVIF_INDENT|LVIF_NORECOMPUTE|LVIF_GROUPID|LVIF_COLUMNS;//|LVIF_COLFMT;
						lvi.iItem=(int)lPDiStruct->itemID;
						lvi.iSubItem=OrderArray[nSubItem];
						lvi.stateMask=0xFFFF;
						lvi.cchTextMax=9990;
						lvi.pszText=tmpstr;
						((GPListCtr *)gpuRes->UnitPtr)->GetItem(&lvi);

						m_IntArr[20]=OrderArray[nSubItem];
						m_IntArr[21]=lvi.state;
						m_IntArr[22]=lvi.iImage;
						m_IntArr[23]=lvi.iGroupId;
						m_IntArr[24]=lvi.iIndent;
						m_IntArr[25]=lvi.lParam;

						m_StringArr[0]=tmpstr;
						char *tmppos=tmpstr;
						int i;
						for(i=50;i<60;i++)
							if (tmppos)
							{
								char *t2=strchr(tmppos,3);
								if (t2)
								{
									*(t2++)=0;
									if (lPDiStruct->CtlType==ODT_MENU)
										while(*t2<=32 && *t2>0) t2++;
								}
								m_StringArr[i]=tmppos;
								m_IntArr[i]=atoi(tmppos);
								if ((i==51 && !*tmppos) || (i==52 && !*tmppos))
									m_IntArr[52]=-1;
								m_REALArr[i]=(REAL)atof(tmppos);
								tmppos=t2;
							}
							else 
							{
								m_StringArr[i]="";
								m_IntArr[i]=0;
								m_REALArr[i]=0;
							}
					}

					m_CurHDC=lPDiStruct->hDC;
					if (gpuRes->m_brBkgnd)
						PaintToCDC(CDC::FromHandle(lPDiStruct->hDC),m_RectArr[0],(HBRUSH)gpuRes->m_brBkgnd->m_hObject);
					else
						PaintToCDC(CDC::FromHandle(lPDiStruct->hDC),m_RectArr[0],NULL);
				}
				m_RectArr[0]=m_RectArr[7];
				delete []tmpstr;
				delete []OrderArray;
			}
		}
	}
	else
	{
		switch(lPDiStruct->CtlType)
		{
		case ODT_MENU:
			{
				MENUITEMINFO mi={0};
				mi.cbSize=sizeofMENUITEMINFO;
				mi.fMask=MIIM_CHECKMARKS|MIIM_DATA|MIIM_ID|MIIM_STATE|MIIM_SUBMENU|MIIM_TYPE;
				::GetMenuItemInfo((HMENU)lPDiStruct->hwndItem,lPDiStruct->itemID,FALSE,&mi);
				m_IntArr[30]=mi.fType;
				m_IntArr[31]=mi.fState;
				m_IntArr[32]=mi.wID;
				m_IntArr[33]=(int)mi.hSubMenu;
				m_IntArr[34]=(int)mi.hbmpChecked;
				m_IntArr[35]=(int)mi.hbmpUnchecked;
				m_IntArr[36]=mi.dwItemData;
				m_IntArr[37]=(int)mi.dwTypeData;
				m_IntArr[38]=mi.cch;
				m_IntArr[39]=(int)mi.hbmpItem;

				m_IntArr[40]=1;
				m_IntArr[41]=0;
				if (lParam)
				{
					PGPMENUINFO gpmi=(PGPMENUINFO)lParam;
					m_IntArr[40]=gpmi->dwFlags;
					m_StringArr[0]=gpmi->csText;
					if (gpmi->dwPopupId<MENU_POPUP_COUNT)
						m_IntArr[41]=pMenu->m_ArrPopupMenu[gpmi->dwPopupId]->m_dwMenuStyle;
				}
				else  
					m_StringArr[0]="";
				if (pMenu && mi.wID>MENU_ID_START && mi.wID<MENU_ID_END)
				{
					if ((pMenu->m_ArrMenuState[mi.wID-MENU_ID_START]&MFS_DEFAULT)==MFS_DEFAULT)
						m_IntArr[7]|=ODS_DEFAULT;
				}
				if (m_IntArr[11])
				{
					if (!m_IntArr[5] && m_StringArr[0]=="") m_IntArr[30]|=0x800;
				}
			}
			break;
		case ODT_LISTBOX:
			if (((int)lPDiStruct->itemID)>=0 && lPDiStruct->hwndItem)
				((GPListBox *)gpuRes->UnitPtr)->GetText(lPDiStruct->itemID,m_StringArr[0]);
			else m_StringArr[0]="Measure string";
			break;
		case ODT_COMBOBOX:
			if (lPDiStruct->hwndItem)
			{
				((GPComboBox *)gpuRes->UnitPtr)->GetLBText(lPDiStruct->itemID,m_StringArr[0]);
				((GPComboBox *)gpuRes->UnitPtr)->GetWindowText(m_StringArr[1]);
			}
			else m_StringArr[0]="Measure string";
			break;
		case ODT_BUTTON:
			if (lPDiStruct->hwndItem)
			{
				((GPButton *)gpuRes->UnitPtr)->GetWindowText(m_StringArr[0]);
				m_IntArr[30]=((GPButton *)gpuRes->UnitPtr)->GetState();
			}
			else m_StringArr[0]="Measure string";
			break;
		case ODT_STATIC:
			if (lPDiStruct->hwndItem)
			{
				((GPStatic *)gpuRes->UnitPtr)->GetWindowText(m_StringArr[0]);
			}
			else m_StringArr[0]="Measure string";
			break;
		case ODT_HEADER:
			if (lPDiStruct->hwndItem)
			{
				HDITEM hdi={0};
				HDTEXTFILTER hf={0};
				
				hdi.mask=HDI_FORMAT|HDI_FILTER|HDI_IMAGE|HDI_LPARAM|HDI_ORDER|HDI_TEXT|HDI_WIDTH;
				hdi.pszText=new char [10000];
				*hdi.pszText=0;
				hdi.pvFilter=&hf;
				hf.pszText=hdi.pszText+9000;
				hdi.type=HDFT_ISSTRING;
				*hf.pszText=0;
				hf.cchTextMax=990;
				((GPHeader *)gpuRes->UnitPtr)->GetItem(lPDiStruct->itemID,&hdi);
				m_IntArr[30]=hdi.cxy;
				m_StringArr[0]=hdi.pszText;
				m_IntArr[31]=hdi.fmt;
				m_IntArr[32]=hdi.lParam;
				m_IntArr[33]=hdi.iImage;
				m_IntArr[34]=hdi.iOrder;
				m_IntArr[35]=hdi.type;
				m_StringArr[1]=hf.pszText;
				delete []hdi.pszText;
			}
			break;
		case ODT_TAB:
			if (lPDiStruct->hwndItem)
			{
				TCITEM hdi={0};
				hdi.mask=TCIF_IMAGE|TCIF_PARAM|TCIF_RTLREADING|TCIF_STATE|TCIF_TEXT;
				hdi.pszText=new char [10000];
				*hdi.pszText=0;
				hdi.cchTextMax=9990;
				hdi.dwStateMask=TCIS_BUTTONPRESSED|TCIS_HIGHLIGHTED;
				((GPTabCtrl *)gpuRes->UnitPtr)->GetItem(lPDiStruct->itemID,&hdi);
				m_IntArr[30]=hdi.dwState;
				m_StringArr[0]=hdi.pszText;
				m_IntArr[31]=hdi.iImage;
				m_IntArr[32]=hdi.lParam;

				delete []hdi.pszText;
			}
			break;
		default:
			if (lPDiStruct->hwndItem)
				((CWnd *)gpuRes->UnitPtr)->GetWindowText(m_StringArr[0]);
			else m_StringArr[0]="Measure string";
			break;
		}

		{
			char *tmpstr=new char [m_StringArr[0].GetLength()+10];
			strcpy(tmpstr,m_StringArr[0]);
			char *tmppos=tmpstr;
			int i;

			for(i=50;i<60;i++)
				if (tmppos)
				{
					char *t2=strchr(tmppos,3);
					if (t2)
					{
						*(t2++)=0;
						if (lPDiStruct->CtlType==ODT_MENU)
							while(*t2<=32 && *t2>0) t2++;
					}
					m_StringArr[i]=tmppos;
					m_IntArr[i]=atoi(tmppos);
					if ((i==51 && !*tmppos) || (i==52 && !*tmppos))
						m_IntArr[52]=-1;
					m_REALArr[i]=(REAL)atof(tmppos);
					tmppos=t2;
				}
				else 
				{
					m_StringArr[i]="";
					m_IntArr[i]=0;
					m_REALArr[i]=0;
				}
			delete []tmpstr;
		}

		m_CurHDC=lPDiStruct->hDC;
		if (gpuRes->m_brBkgnd)
			PaintToCDC(CDC::FromHandle(lPDiStruct->hDC),m_RectArr[0],(HBRUSH)gpuRes->m_brBkgnd->m_hObject);
		else
			PaintToCDC(CDC::FromHandle(lPDiStruct->hDC),m_RectArr[0],NULL);

		if (m_IntArr[11])
		{
			if (lPDiStruct->CtlType==ODT_MENU)
			{
				if ((UINT)m_RectArr[1].Width<1) m_RectArr[1].Width=1;
				if ((UINT)m_RectArr[1].Height<1) m_RectArr[1].Height=1;
			}
			m_MeasureStruct.itemWidth =(UINT)m_RectArr[1].Width;
			m_MeasureStruct.itemHeight=(UINT)m_RectArr[1].Height;
		}
	}
}

int CODContext::GetIntByRef(DWORD ref)
{
	DWORD dwId=GetIdFromRef(ref);
	return (dwId<m_nIntArray)?m_IntArr[dwId]:0;
}
REAL CODContext::GetREALByRef(DWORD ref)
{
	DWORD dwId=GetIdFromRef(ref);
	return (dwId<m_nREALArray)?m_REALArr[dwId]:0;
}
Color CODContext::GetColorByRef(DWORD ref)
{
	DWORD dwId=GetIdFromRef(ref);
	return (dwId<m_nRGBArray)?m_RGBArr[dwId]:ref;
}
DWORD CODContext::GetIdFromRef(DWORD dwFlg)
{
	DWORD ret=-1;
	if ((dwFlg&0xF0000000)==0xE0000000)
	{
		UINT nARR=dwFlg&0xFFFFFF;
		switch((dwFlg&0x0F000000))
		{
		case 0x0F000000://CLR
			if (nARR<m_nRGBArray) ret=nARR;
			break;
		case 0x0E000000://INT
			if (nARR<m_nIntArray) ret=nARR;
			break;
		case 0x0D000000://DBL
			if (nARR<m_nREALArray) ret=nARR;
			break;
		case 0x0C000000://@CLR
///////////////////////			if (nARR<m_nRGBArray && m_RGBArr[nARR]<m_nRGBArray) ret=m_RGBArr[nARR];
			break;
		case 0x0B000000://@INT
			if (nARR<m_nIntArray && ((UINT)m_IntArr[nARR])<m_nRGBArray) ret=(DWORD)m_IntArr[nARR];
			break;
		case 0x0A000000://@DBL
			if (nARR<m_nREALArray && m_REALArr[nARR]<m_nRGBArray) ret=(DWORD)m_REALArr[nARR];
			break;
		default:
			if (nARR<m_nRGBArray) ret=nARR;
			break;
		}
	}
	else ret=dwFlg;

	return ret;
}

DWORD CODContext::ParseId(const char *iParam)
{
	DWORD ret=0;
	if (strncmp(iParam,"CLR",3)==0)
		ret=0xEF000000+atoi(iParam+3);
	else
	if (strncmp(iParam,"INT",3)==0)
		ret=0xEE000000+atoi(iParam+3);
	else
	if (strncmp(iParam,"DBL",3)==0)
		ret=0xED000000+((DWORD)atoi(iParam+3));
	else
	if (strncmp(iParam,"@CLR",4)==0)
		ret=0xEC000000+atoi(iParam+4);
	else
	if (strncmp(iParam,"@INT",4)==0)
		ret=0xEB000000+atoi(iParam+4);
	else
	if (strncmp(iParam,"@DBL",4)==0)
		ret=0xEA000000+atoi(iParam+4);
	else ret=atoi(iParam);

	return ret;
}

CODContext *CODContext::SaveContext(const char * ccFileName)
{

	return this;
}

ARGB CODContext::GetColorFromString(CODContext *iContext, const char *iStr)
{
	ARGB ret=Color::MakeARGB(255,0,0,0);

	if (*iStr=='0' && (iStr[1]=='x' || iStr[1]=='X'))
	{
		DWORD c=0;
		sscanf(iStr+2,"%X",&ret);
	}
	else
	if (*iStr>='0' && *iStr<='9' && !strchr(iStr,','))
	{
		ret=atoi(iStr);
	}
	else
	if (*iStr>='0' && *iStr<='9')
	{
		int R=0,G=0,B=0,A=255;
		sscanf(iStr,"%d,%d,%d,%d",&R,&G,&B,&A);
		ret=Color::MakeARGB(A,R,G,B);
	}
	else
	if (iContext)
	{
		//CLR(...)
		PDCIPARAMETER mparam=NULL;
		DCParamType pta[]={DCPT_COLOR,DCPT_NONE};
		DCParamType pta2[]={DCPT_VARTYPE,DCPT_NONE};
		UINT tmpNParams=0;
		CODContextItem::TranslateParams(iStr,pta,iContext,&(mparam),&tmpNParams);
		if (!mparam || !tmpNParams || mparam->dwParamType==DCPT_NONE)
			CODContextItem::TranslateParams(iStr,pta2,iContext,&(mparam),&tmpNParams);
		if (mparam)
		{
			if (iContext) CODContextItem::PrepareParameter(iContext,&(mparam[0]));
			if ((mparam[0].dwParamType&DCPT_TYPEMASK)==DCPT_COLOR)
			{
				if (mparam[0].m_pColor) ret=mparam[0].m_pColor->GetValue();
			}
			else
			if ((mparam[0].dwParamType&DCPT_TYPEMASK)==DCPT_INTEGER)
			{
				ret=mparam[0].m_int;
			}

			CODContextItem::ResetParameters(&mparam,&tmpNParams);
			delete []mparam;
		}
	}
	return ret;
}

CBitmapPlus *CODContext::GetBitmap(DWORD dwBitmapId)
{
	CBitmapPlus *ret=NULL;
	if (m_BitmapArr && dwBitmapId<m_nBitmapArray) ret=m_BitmapArr[dwBitmapId];

	return ret;
}

CBitmapPlus *CODContext::SetBitmap(DWORD dwBitmapId, CBitmapPlus *iBitmap)
{
	if (m_BitmapArr && dwBitmapId<m_nBitmapArray)
	{
		if (m_BitmapArr[dwBitmapId]) delete m_BitmapArr[dwBitmapId];
		m_BitmapArr[dwBitmapId]=iBitmap;
	}
	return GetBitmap(dwBitmapId);
}
