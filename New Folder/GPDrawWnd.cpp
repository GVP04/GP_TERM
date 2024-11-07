// GPDrawWnd.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPDrawWnd.h"
#include <math.h>
#include <float.h>
#include "GP_QScroll.h"
#include "WndPrint.h"
#include "ODContextItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPDrawWnd
const UINT GPDrawWnd::uNMethods=48;
const char *GPDrawWnd::cArrMethods[]={
		"SetPen","SetBrush","SetPoint","SetRect","SetFont",
		"DeleteItem","DeleteItems","AddItem","SetItem","InsertItem",
		"SetBPen","InsertEmpty","SetColor","AddItems","SetIcon",
		"SetText","SetInt","SetDouble","ScrollPoint","ScrollRect",
		"ScrollPen","ScrollBrush","ScrollFont","ScrollItem","ScrollInt",
		"ScrollDouble","ScrollIcon","ScrollColor","ScrollText","SetItems",
		"SetRegion","OffsetRgn","OffsetRgnP","Print","PrnSetName",
		"PrnMargins","PrnWinExt","PrnWinOrg","PrnVieExt","PrnVieOrg",
		"LogSize","SetTimer","KillTimer","SetPenWidth","SetPenColor",
		"Redraw","SetAutoRedraw","SetEraseBkg","","",
		"","","","","",
	};
const char *GPDrawWnd::cArrMethodsParams[]={
		"nPen,uWidth,R,G,B,STYLE","nBrush,R,G,B,STYLE  OR  nBrush,nImage,ImageListName","nPoint,pox,poy","nRect,top,left,bottom,right","nFont,LOGFONTSTRING",
		"uItem","uItem,uItemCount  OR  uItem,-1","SETITEMSTRING","uItem,SETITEMSTRING","uItem,SETITEMSTRING",
		"nPen,nBrush","uInsertPos,uInsertCount","nColor,R,G,B","SETITEMSTRING^SETITEMSTRING^....","nIcon,nImage,ImageListName",
		"nText,TEXT","nInt,int","nDouble,double","nBegin,nEnd,nTime=1,nEvery=1","nBegin,nEnd,nTime=1,nEvery=1",
		"nBegin,nEnd,nTime=1,nEvery=1","nBegin,nEnd,nTime=1,nEvery=1","nBegin,nEnd,nTime=1,nEvery=1","nBegin,nEnd,nTime=1,nEvery=1","nBegin,nEnd,nTime=1,nEvery=1",
		"nBegin,nEnd,nTime=1,nEvery=1","nBegin,nEnd,nTime=1,nEvery=1","nBegin,nEnd,nTime=1,nEvery=1","nBegin,nEnd,nTime=1,nEvery=1","nItem,SETITEMSTRING^nItem,SETITEMSTRING^....",
		"nRegion,SETREGIONSTRING","nRegion,dx,dy","nRegion,nPoint","bDlg,bOrientation,icPaper","DrawName",
		"Left,Top,Righr,Bottom","x,y","x,y","x,y","x,y",
		"x,y","nTimer,nDelay,dValue,dDelta,dStop,bRedraw","nTimer","nPen,Width","nPen,R,G,B",
		"","bValue","bValue","","",
		"","","","","",
	};

const UINT GPDrawWnd::uNArrFn=59;


const UINT GPDrawWnd::uNUnitType=180;
const char *GPDrawWnd::cArrUnitType[]={
		"NONE",			"FRG",			"BKG",			"PEN",			"BRUSH",
		"FONT",			"MOVE",			"MOVER",		"MOVEP",		"BKMODE",
		"PFMODE",		"ROP2",			"SBLTMODE",		"COLORADJ",		"MAPMODE",
		"VPORTORG",		"VPORTEXT",		"BRUSHORG",		"STOCKOBJ",		"WINDOWORG",
		"WINDOWEXT",	"LINETO",		"LINETOP",		"ARC",			"ARCTO",
		"ARCRPP",		"ARCRPPTO",		"ANGLEARC",		"ANGLEARCP",	"ARCDIRECTION",
		"POLYLINE",		"POLYLINETO",	"POLYLINEP",	"POLYLINEPTO",	"POLYPOLY",
		"POLYPOLYP",	"POLYBEZIER",	"POLYBEZIERP",	"POLYBEZIERTO",	"POLYBEZIERPTO",
		"FILLRECT",		"FILLRECTR",	"FRAMERECT",	"FRAMERECTR",	"INVERTRECT",
		"INVERTRECTR",	"ICON",			"ICONP",		"FILLSRECT",	"FILLSRECTR",
		"3DRECT",		"3DRECTR",		"EDGE",			"EDGER",		"FRAMECTRL",
		"FRAMECTRLR",	"STATETEXT",	"STATETEXTR",	"STATEICON",	"STATEICONR",
		"CHORD",		"CHORDRP",		"FOCUSRECT",	"FOCUSRECTR",	"ELLIPSE",	
		"ELLIPSER",		"PIE",			"PIERP",		"POLYGON",		"POLYGONP",	
		"PPOLYGON",		"PPOLYGONP",	"RECT",			"RECTR",		"ROUNDRECT",
		"ROUNDRECTR",	"PIXEL",		"PIXELPC",		"FLOODFILL",	"FLOODFILLPC",	
		"EXTFLOODFILL",	"EXTFLOODFILLPC","TEXTOUT",		"TEXTOUTPT",	"EXTTEXTOUT",
		"EXTTEXTOUTP",	"TABTEXTOUT",	"TABTEXTOUTP",	"TEXT",			"TEXTR",
		"TEXTALIGN",	"TEXTJUST",		"CHAREXTRA",	"MAPPERFLAGS",	"ABORTPATH",
		"BEGINPATH",	"CLOSEFIGURE",	"ENDPATH",		"FILLPATH",		"FLATTENPATH",
		"SELECTCLIPPATH","SETMITERLIMIT","STROKEFILLPATH","STROKEPATH",	"WIDENPATH",
		"ARROW",		"ARROWTO",		"ARROWP",		"ARROWPTO",		"OFFSET",
		"OFFSETP",		"CLONE",		"CLONETO",		"CLONEC",		"CLONECTO",
		"GOTO",			"GOSUB",		"RETURN",		"SETINT",		"SETDOUBLE",
		"SETPOINT",		"SETRECT",		"SETCOLOR",		"SETREGION",	"COPYREGION",
		"COMBINEREGION","OFFSETREGION",	"OFFSETPREGION","REGIONFROMPATH","FILLRGN",	
		"FRAMERGN",		"INVERTRGN",	"PAINTRGN",		"BOUNDSRECT",	"BOUNDSRECTR",
		"GETCLIPBOX",	"GETBOUNDSR",	"SELCLIPREGION","EXCLRECT",		"EXCLRECTR",
		"EXCLUPDRGN",	"INCLRECT",		"INCLRECTR",	"OFFSETCREGION","OFFSETPCREGION",
		"IFGOTO",		"IFGOSUB",		"ARITHMETIC",	"MATH",			"SETRGB",
		"SETPENCOLOR",	"GETWINDOWRECT","GETCLIENTRECT",	"MOVEWINDOW",	"RECTOFFSET",
		"RECTOFFSETR",	"RECTOFFSETP",	"RECTHEIGHT",	"RECTWIDTH",	"RECTISNULL",
		"RECTISEMPTY",	"RECTCENTER",	"RECTPTIN",		"RECTEQUAL",	"RECTINFLATE",
		"RECTDEFLATE",	"RECTNORMALIZE","RECTSUBSTR",	"RECTINTERS",	"RECTUNION",
		"RECTOFFSETRM",	"RECTOFFSETPM",	"SCRTOCL",		"CLTOSCR",		"STRCAT",
		"STRCATS",		"ITOSTR",		"DTOSTR",		"TTOSTR",		"PENWIDTH",
		"","","","","",
	};
const UINT GPDrawWnd::uArrUnitType[]={
		DUT_NONE,		DUT_FRG,		DUT_BKG,		DUT_PEN,		DUT_BRUSH,
		DUT_FONT,		DUT_MOVE,		DUT_MOVER,		DUT_MOVEP,		BUT_BKMODE,
		DUT_PFILLMODE,	DUT_ROP2,		DUT_SBLTMODE,	DUT_COLORADJ,	DUT_MAPMODE,
		DUT_VPORTORG,	DUT_VPORTEXT,	DUT_BRUSHORG,	DUT_STOCKOBJ,	DUT_WINDOWORG,
		DUT_WINDOWEXT,	DUT_LINETO,		DUT_LINETOP,	DUT_ARC,		DUT_ARCTO,
		DUT_ARCRPP,		DUT_ARCRPPTO,	DUT_ANGLEARC,	DUT_ANGLEARCP,	DUT_ARCDIRECTION,
		DUT_POLYLINE,	DUT_POLYLINETO,	DUT_POLYLINEP,	DUT_POLYLINEPTO,DUT_POLYPOLY,
		DUT_POLYPOLYP,	DUT_POLYBEZIER,	DUT_POLYBEZIERP,DUT_POLYBEZIERTO,DUT_POLYBEZIERPTO,
		DUT_FILLRECT,	DUT_FILLRECTR,	DUT_FRAMERECT,	DUT_FRAMERECTR,	DUT_INVERTRECT,
		DUT_INVERTRECTR,DUT_ICON,		DUT_ICONP,		DUT_FILLSRECT,	DUT_FILLSRECTR,
		DUT_3DRECT,		DUT_3DRECTR,	DUT_EDGE,		DUT_EDGER,		DUT_FRAMECTRL,
		DUT_FRAMECTRLR,	DUT_STATETEXT,	DUT_STATETEXTR,	DUT_STATEICON,	DUT_STATEICONR,
		DUT_CHORD,		DUT_CHORDRP,	DUT_FOCUSRECT,	DUT_FOCUSRECTR,	DUT_ELLIPSE,
		DUT_ELLIPSER,	DUT_PIE,		DUT_PIERP,		DUT_POLYGON,	DUT_POLYGONP,
		DUT_PPOLYGON,	DUT_PPOLYGONP,	DUT_RECT,		DUT_RECTR,		DUT_ROUNDRECT,
		DUT_ROUNDRECTR,	DUT_PIXEL,		DUT_PIXELPC,	DUT_FLOODFILL,	DUT_FLOODFILLPC,
		DUT_EXTFLOODFILL,DUT_EXTFLOODFILLPC,DUT_TEXTOUT,DUT_TEXTOUTPT,	DUT_EXTTEXTOUT,
		DUT_EXTTEXTOUTP,DUT_TABTEXTOUT,	DUT_TABTEXTOUTP,DUT_TEXT,		DUT_TEXTR,
		DUT_TEXTALIGN,	DUT_TEXTJUST,	DUT_CHAREXTRA,	DUT_MAPPERFLAGS,DUT_ABORTPATH,
		DUT_BEGINPATH,	DUT_CLOSEFIGURE,DUT_ENDPATH,	DUT_FILLPATH,	DUT_FLATTENPATH,
		DUT_SELECTCLIPPATH,DUT_SETMITERLIMIT,DUT_STROKEFILLPATH,DUT_STROKEPATH,DUT_WIDENPATH,
		DUT_ARROW,		DUT_ARROWTO,	DUT_ARROWP,		DUT_ARROWPTO,	DUT_OFFSET,
		DUT_OFFSETP,	DUT_CLONE,		DUT_CLONETO,	DUT_CLONEC,		DUT_CLONECTO,
		DUT_GOTO,		DUT_GOSUB,		DUT_RETURN,		DUT_SETINT,		DUT_SETDOUBLE,
		DUT_SETPOINT,	DUT_SETRECT,	DUT_SETCOLOR,	DUT_SETREGION,	DUT_COPYREGION,
		DUT_COMBINEREGION,DUT_OFFSETREGION,DUT_OFFSETPREGION,DUT_REGIONFROMPATH,DUT_FILLRGN,
		DUT_FRAMERGN,	DUT_INVERTRGN,	DUT_PAINTRGN,	DUT_BOUNDSRECT,	DUT_BOUNDSRECTR,
		DUT_GETCLIPBOX,	DUT_GETBOUNDSR,	DUT_SELCLIPREGION,DUT_EXCLRECT,	DUT_EXCLRECTR,
		DUT_EXCLUPDRGN,	DUT_INCLRECT,	DUT_INCLRECTR,	DUT_OFFSETCREGION,DUT_OFFSETPCREGION,
		DUT_IFGOTO,		DUT_IFGOSUB,	DUT_ARITHMETIC,	DUT_MATH,		DUT_SETRGB,
		DUT_SETPENCOLOR,DUT_GETWINDOWRECT,DUT_GETCLIENTRECT,DUT_MOVEWINDOW,DUT_RECTOFFSET,
		DUT_RECTOFFSETR,DUT_RECTOFFSETP,	DUT_RECTHEIGHT,	DUT_RECTWIDTH,	DUT_RECTISNULL,
		DUT_RECTISEMPTY,DUT_RECTCENTER,		DUT_RECTPTIN,	DUT_RECTEQUAL,	DUT_RECTINFLATE,
		DUT_RECTDEFLATE,DUT_RECTNORMALIZE,	DUT_RECTSUBSTR,	DUT_RECTINTERS,	DUT_RECTUNION,
		DUT_RECTOFFSETRM,DUT_RECTOFFSETPM,DUT_SCRTOCL,	DUT_CLTOSCR,	DUT_STRCAT,
		DUT_STRCATS,	DUT_ITOSTR,		DUT_DTOSTR,		DUT_TTOSTR,		DUT_PENWIDTH,
		0,0,0,0,0,
	};

#define DU_NSTACK		50

GPDrawWnd::GPDrawWnd(UINT iUnitId, GPUnit **iGPU)
{
	referGPU=iGPU;
	m_uRedrawFlag=1;
	m_hDCBitmap=NULL;
	m_bAutoRedraw=FALSE;
	m_bEraseBkg=FALSE;
	UnitId=iUnitId;
	
	referGPU[UnitId&0xFFFF]->m_clrText= GetSysColor(COLOR_WINDOWTEXT);
	referGPU[UnitId&0xFFFF]->m_clrBkgnd=GetSysColor(COLOR_WINDOW);

	UINT i;

	m_nDrawArray=100;
	m_nDraw=0;
	m_ArrDrawType=new UINT  [m_nDrawArray];
	m_ArrDrawWParam=new WPARAM [m_nDrawArray];
	m_ArrDrawLParam=new LPARAM [m_nDrawArray];
	m_ArrDrawInitString=new CString [m_nDrawArray];

	for(i=0;i<m_nDrawArray;i++)
	{
		m_ArrDrawType[i]=0;
		m_ArrDrawWParam[i]=0;
		m_ArrDrawLParam[i]=0;
		m_ArrDrawInitString[i]="";
	}

	m_nPenArray=20;
	m_PenArr=new CPenExt * [m_nPenArray];
	for(i=0;i<m_nPenArray;i++)
		m_PenArr[i]=NULL;

	m_nBrushArray=20;
	m_BrushArr=new CBrushExt * [m_nBrushArray];
	for(i=0;i<m_nBrushArray;i++)
		m_BrushArr[i]=NULL;

	m_nRgnArray=20;
	m_RgnArr=new CRgnExt * [m_nRgnArray];
	for(i=0;i<m_nRgnArray;i++)
		m_RgnArr[i]=NULL;

	m_nFontArray=20;
	m_FontArr=new CFontExt * [m_nFontArray];
	for(i=0;i<m_nFontArray;i++)
		m_FontArr[i]=NULL;

	m_nPointArray=20;
	m_PointArr=new CPoint[m_nPointArray];
	for(i=0;i<m_nPointArray;i++)
		m_PointArr[i].x=m_PointArr[i].y=0;

	m_nRectArray=20;
	m_RectArr=new CRect[m_nRectArray];
	for(i=0;i<m_nRectArray;i++)
		m_RectArr[i].SetRect(0,0,0,0);

	m_nStringArray=20;
	m_StringArr=new CString[m_nStringArray];
	for(i=0;i<m_nStringArray;i++)
		m_StringArr[i]="";

	m_nRGBArray=50;
	m_RGBArr=new COLORREF [m_nRGBArray];
	for(i=0;i<m_nRGBArray;i++)
		m_RGBArr[i]=0;

	m_nIntArray=50;
	m_IntArr=new int [m_nIntArray];
	for(i=0;i<m_nIntArray;i++)
		m_IntArr[i]=0;

	m_nDoubleArray=50;
	m_DoubleArr=new double [m_nDoubleArray];
	for(i=0;i<m_nDoubleArray;i++)
		m_DoubleArr[i]=0;

	m_nIconArray=20;
	m_IconArr=new HICON [m_nIconArray];
	m_IconArrString=new CString [m_nIconArray];
	for(i=0;i<m_nIconArray;i++)
	{
		m_IconArr[i]=NULL;
		m_IconArrString[i]="";
	}

	m_LogSize.cx=m_LogSize.cy=0;
	m_PrintWinExt=m_PrintVieExt=CSize(-12345,-12345);
	m_PrintWinOrg=m_PrintVieOrg=CPoint(-12345,-12345);
	m_PrintMargins=CRect(2000,2000,2000,2000);
	m_DrawName="";

	m_nDrTimerArray=16;
	m_DrTimerArr=new DRAWTIMER [m_nDrTimerArray];
	for(i=0;i<m_nDrTimerArray;i++)
		InitDRAWTIMER(m_DrTimerArr+i);

	EnableAutomation();
}

GPDrawWnd::~GPDrawWnd()
{
	DeletePaintObj();

	UINT i;

	if (m_DoubleArr!=NULL)	delete[] m_DoubleArr;
	m_nDoubleArray=0;
	m_DoubleArr=NULL;

	if (m_DrTimerArr!=NULL)	delete[]  m_DrTimerArr;
	m_DrTimerArr=NULL;

	for(i=0;i<m_nDrawArray;i++)
		DestroyItem(i);

	if (m_ArrDrawInitString!=NULL)	delete[]  m_ArrDrawInitString;
	if (m_ArrDrawWParam!=NULL)	delete[] m_ArrDrawWParam;
	if (m_ArrDrawLParam!=NULL)	delete[] m_ArrDrawLParam;
	if (m_ArrDrawType!=NULL)	delete[] m_ArrDrawType;

	m_nDraw=0;
	m_nDrawArray=0;
	m_ArrDrawInitString=NULL;
	m_ArrDrawWParam=NULL;
	m_ArrDrawLParam=NULL;
	m_ArrDrawType=NULL;

	if (m_PenArr!=NULL)
	{
		for(i=0;i<m_nPenArray;i++)
			if (m_PenArr[i]!=NULL)
			{
				m_PenArr[i]->DeleteObject();
				delete m_PenArr[i];
				m_PenArr[i]=NULL;
			}
		delete[] m_PenArr;
	}
	m_nPenArray=0;
	m_PenArr=NULL;

	if (m_BrushArr!=NULL)
	{
		for(i=0;i<m_nBrushArray;i++)
			if (m_BrushArr[i]!=NULL)
			{
				m_BrushArr[i]->DeleteObject();
				delete m_BrushArr[i];
				m_BrushArr[i]=NULL;
			}
		delete[] m_BrushArr;
	}
	m_nBrushArray=0;
	m_BrushArr=NULL;

	if (m_RgnArr!=NULL)
	{
		for(i=0;i<m_nRgnArray;i++)
			if (m_RgnArr[i]!=NULL)
			{
				m_RgnArr[i]->DeleteObject();
				delete m_RgnArr[i];
				m_RgnArr[i]=NULL;
			}
		delete[] m_RgnArr;
	}
	m_nRgnArray=0;
	m_RgnArr=NULL;

	if (m_FontArr!=NULL)
	{
		for(i=0;i<m_nFontArray;i++)
			if (m_FontArr[i]!=NULL)
			{
				m_FontArr[i]->DeleteObject();
				delete m_FontArr[i];
				m_FontArr[i]=NULL;
			}
		delete[] m_FontArr;
	}
	m_nFontArray=0;
	m_FontArr=NULL;

	if (m_PointArr!=NULL)	delete[]  m_PointArr;
	m_nPointArray=0;
	m_PointArr=NULL;

	if (m_RectArr!=NULL)	delete[]  m_RectArr;
	m_nRectArray=0;
	m_RectArr=NULL;

	if (m_StringArr!=NULL)	delete[]  m_StringArr;
	m_nStringArray=0;
	m_StringArr=NULL;

	if (m_RGBArr!=NULL)		delete[] m_RGBArr;
	m_nRGBArray=0;
	m_RGBArr=NULL;

	if (m_IntArr!=NULL)		delete[] m_IntArr;
	m_nIntArray=0;
	m_IntArr=NULL;

	if (m_IconArr!=NULL)
	{
		for(i=0;i<m_nIconArray;i++)
			if (m_IconArr[i]!=NULL)
			{
				DestroyIcon(m_IconArr[i]);
				m_IconArr[i]=NULL;
			}
		delete[] m_IconArr;
	}
	if (m_IconArrString!=NULL)	delete[]  m_IconArrString;
	m_IconArrString=NULL;
	m_IconArr=NULL;
	m_nIconArray=0;

}

BEGIN_MESSAGE_MAP(GPDrawWnd, CWnd)
	//{{AFX_MSG_MAP(GPDrawWnd)
	ON_WM_PARENTNOTIFY_REFLECT()
	ON_WM_CLOSE()
	ON_WM_SIZING()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_NCHITTEST()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPDrawWnd message handlers
UINT GPDrawWnd::DoMethod(const char *iStr, char *oStr)
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
	case 0: /*SetPen*/
	case 10: /*SetBPen*/
		if (atoipos>=0 && atoipos<1000)
		{
			if ((UINT)atoipos>=m_nPenArray)
			{
				CPenExt **tmp=new CPenExt * [atoipos+1];
				UINT i;
				for( i=0; i<m_nPenArray;i++)
					tmp[i]=m_PenArr[i];
				m_nPenArray=atoipos+1;
				for(;i<m_nPenArray;i++)
					tmp[i]=NULL;
				delete[] m_PenArr;
				m_PenArr=tmp;
			}
			if (m_PenArr[atoipos]!=NULL) 
			{
				m_PenArr[atoipos]->DeleteObject();
				delete m_PenArr[atoipos]; 
				m_PenArr[atoipos]=NULL; 
			}
			UINT uPenStyle=0,uWidth=0;
			COLORREF cColor=0;
			if (strlen(pos2)>0)
			{
				GPUnit::TranslatePenStyle(pos2,&uPenStyle,&uWidth,&cColor);
				UINT nBrush=GetRValue(cColor);
				LOGBRUSH LogBrush={0};
				m_PenArr[atoipos]=new CPenExt;
				if (nfunc==10 && nBrush>=0 && nBrush<m_nBrushArray && m_BrushArr[nBrush]!=NULL)
					m_BrushArr[nBrush]->GetLogBrush(&LogBrush);
				else
					LogBrush.lbColor=cColor;

				m_PenArr[atoipos]->Attach(ExtCreatePen(uPenStyle,uWidth,&LogBrush,0,NULL));
				m_PenArr[atoipos]->CreationString=pos2;
			}
		}
		break;
	case 1: /*SetBrush*/
		if (atoipos>=0 && atoipos<1000)
		{
			if ((UINT)atoipos>=m_nBrushArray)
			{
				CBrushExt **tmp=new CBrushExt * [atoipos+1];
				UINT i;
				for( i=0; i<m_nBrushArray;i++)
					tmp[i]=m_BrushArr[i];
				m_nBrushArray=atoipos+1;
				for(;i<m_nBrushArray;i++)
					tmp[i]=NULL;
				delete[] m_BrushArr;
				m_BrushArr=tmp;
			}
			if (m_BrushArr[atoipos]!=NULL) 
			{
				m_BrushArr[atoipos]->DeleteObject();
				delete m_BrushArr[atoipos]; 
				m_BrushArr[atoipos]=NULL; 
			}

			if (strlen(pos2)>3)
			{
				m_BrushArr[atoipos]=new CBrushExt;

				LOGBRUSH tmplb={0};
				GPSetBrushProperty(&tmplb,pos2);
				GPSetBrush(m_hWnd,&m_BrushArr[atoipos],&tmplb,referGPU[UnitId&0xFFFF]->m_clrBkgnd,pos2);
				m_BrushArr[atoipos]->CreationString=pos2;
			}
		}
		break;
	case 2: /*SetPoint*/
		{
			const char *postmp=strstr(pos,"..");
			int istrt=atoipos;
			int iend=atoipos;
			if (postmp!=NULL)
			{
				while(*postmp!=0 && *postmp=='.') postmp++;
				iend=atoi(postmp);
			}
			CPoint po(0,0);
			const char *curpos=pos2;

			if (istrt>=0)
			{
				int nPos;
				for(nPos=istrt;nPos<=iend;nPos++)
				{
					if (curpos!=NULL)
					{
						m_LastScanf=sscanf(curpos,"%d,%d",&po.x,&po.y);
						curpos=strchr(curpos,GPC.DelimiterIn1);
						if (curpos!=NULL) curpos++;
					}
					if ((UINT)nPos>=m_nPointArray)
					{
						CPoint *tmp=new CPoint [nPos+10];
						UINT i;
						for( i=0; i<m_nPointArray;i++)
							tmp[i]=m_PointArr[i];
						m_nPointArray=nPos+10;
						for(;i<m_nPointArray;i++)
							tmp[i].x=tmp[i].y=0;
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
						m_LastScanf=sscanf(curpos,"%d,%d",&po.x,&po.y);
						curpos=strchr(curpos,GPC.DelimiterIn1);
						if (curpos!=NULL) curpos++;
					}
					sprintf(str,"SetDouble %d,%d",(-nPos-1)*2,po.x);
					DoMethod(str,NULL);
					sprintf(str,"SetDouble %d,%d",(-nPos-1)*2+1,po.y);
					DoMethod(str,NULL);
				}
			}
		}
		break;
	case 3: /*SetRect*/
		{
			const char *postmp=strstr(pos,"..");
			int istrt=atoipos;
			int iend=atoipos;
			if (postmp!=NULL)
			{
				while(*postmp!=0 && *postmp=='.') postmp++;
				iend=atoi(postmp);
			}
			CRect re(0,0,0,0);
			const char *curpos=pos2;

			if (istrt>=0)
			{
				int nPos;
				for(nPos=istrt;nPos<=iend;nPos++)
				{
					if (curpos!=NULL)
					{
						m_LastScanf=sscanf(curpos,"%d,%d,%d,%d",&re.left,&re.top,&re.right,&re.bottom);
						curpos=strchr(curpos,GPC.DelimiterIn1);
						if (curpos!=NULL) curpos++;
					}

					if ((UINT)nPos>=m_nRectArray)
					{
						CRect *tmp=new CRect [nPos+10];
						UINT i;
						for( i=0; i<m_nRectArray;i++)
							tmp[i]=m_RectArr[i];
						m_nRectArray=nPos+10;
						for(;i<m_nRectArray;i++)
							tmp[i].SetRect(0,0,0,0);
						delete[]  m_RectArr;
						m_RectArr=tmp;
					}
					m_RectArr[nPos]=re;
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
						m_LastScanf=sscanf(curpos,"%d,%d,%d,%d",&re.left,&re.top,&re.right,&re.bottom);
						curpos=strchr(curpos,GPC.DelimiterIn1);
						if (curpos!=NULL) curpos++;
					}
					sprintf(str,"SetDouble %d,%d",(-nPos-1)*4,re.left);
					DoMethod(str,NULL);
					sprintf(str,"SetDouble %d,%d",(-nPos-1)*4+1,re.top);
					DoMethod(str,NULL);
					sprintf(str,"SetDouble %d,%d",(-nPos-1)*4+2,re.right);
					DoMethod(str,NULL);
					sprintf(str,"SetDouble %d,%d",(-nPos-1)*4+3,re.bottom);
					DoMethod(str,NULL);
				}
			}
		}
		break;
	case 4: /*SetFont*/
		if (atoipos>=0 && atoipos<200)
		{
			if ((UINT)atoipos>=m_nFontArray)
			{
				CFontExt **tmp=new CFontExt * [atoipos+1];
				UINT i;
				for( i=0; i<m_nFontArray;i++)
					tmp[i]=m_FontArr[i];
				m_nFontArray=atoipos+1;
				for(;i<m_nFontArray;i++)
					tmp[i]=NULL;
				delete[] m_FontArr;
				m_FontArr=tmp;
			}
			if (m_FontArr[atoipos]!=NULL) 
			{
				m_FontArr[atoipos]->DeleteObject();
				delete m_FontArr[atoipos]; 
				m_FontArr[atoipos]=NULL; 
			}
			if (strlen(pos2)>5)
			{
				m_FontArr[atoipos]=new CFontExt;

				LOGFONT lf={0};
				TranslLOGFONT(lf,pos2);
				m_FontArr[atoipos]->CreateFontIndirect(&lf);
				m_FontArr[atoipos]->CreationString=pos2;
			}
		}
		break;
	case 5: /*DeleteItem*/
		retint=DeleteItem(atoipos);
		break;
	case 6: /*DeleteItems*/
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
	case 7: /*AddItem*/
		{
			InsertEmptyItem(m_nDraw,1);
			SetItem(m_nDraw-1,pos);
			retint=m_nDraw;
		}
		break;
	case 8: /*SetItem*/
		if (atoipos>=0 && atoipos<32000)
		{
			if ((UINT)atoipos>=m_nDraw) InsertEmptyItem(atoipos,1);
			SetItem(atoipos,pos2);
		}
		break;
	case 9: /*InsertItem*/
		if (atoipos>=0 && atoipos<32000)
		{
			InsertEmptyItem(atoipos,1);
			SetItem(atoipos,pos2);
			retint=m_nDraw;
		}
		break;
	case 11: /*InsertEmpty*/
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
	case 12: /*SetColor*/
		if (atoipos>=0 && atoipos<1000)
		{
			if ((UINT)atoipos>=m_nRGBArray)
			{
				COLORREF *tmp=new COLORREF [atoipos+10];
				UINT i;
				for( i=0; i<m_nRGBArray;i++)
					tmp[i]=m_RGBArr[i];
				m_nRGBArray=atoipos+10;
				for(;i<m_nRGBArray;i++)
					tmp[i]=0;
				delete[] m_RGBArr;
				m_RGBArr=tmp;
			}

			UINT R=0,G=0,B=0;
			m_LastScanf=sscanf(pos2,"%d,%d,%d",&R,&G,&B);
			m_RGBArr[atoipos]=RGB(R,G,B);
		}
		break;
	case 13: /*AddItems*/
	case 29: /*SetItems*/
		{
			char *str=new char [strlen(pos)+10];
			char tmpstr[1000];
			strcpy(str,pos);
			char *pos22=str;
			while(pos22!=NULL && *pos22!=0)
			{
				char *postmp=strchr(pos22,GPC.DelimiterIn1);
				if (postmp!=NULL) *(postmp++)=0;
				strcpy(tmpstr,nfunc==13?"AddItem ":"SetItem ");
				strncpy(tmpstr+8,pos22,990);
				tmpstr[998]=0;
				DoMethod(tmpstr,NULL);
				pos22=postmp;
			}
			delete[] str;
			retint=m_nDraw;
		}
		break;
	case 14: /*SetIcon*/
		if (atoipos>=0 && atoipos<500)
		{
			if ((UINT)atoipos>=m_nIconArray)
			{
				HICON *tmp=new HICON [atoipos+10];
				CString *tmpS=new CString [atoipos+10];
				UINT i;
				for( i=0; i<m_nIconArray;i++)
				{
					tmp[i]=m_IconArr[i];
					tmpS[i]=m_IconArrString[i];
				}
				m_nIconArray=atoipos+10;
				for(;i<m_nIconArray;i++)
				{
					tmp[i]=NULL;
					tmpS[i]="";
				}
				delete[] m_IconArr;
				delete[] m_IconArrString;
				m_IconArr=tmp;
				m_IconArrString=tmpS;
			}
			if (m_IconArr[atoipos]!=NULL) 
				DestroyIcon(m_IconArr[atoipos]);

			int nIcon=0,nImage=0;
			char name[200];*name=0;
			m_LastScanf=sscanf(pos,"%d,%d,%s",&nIcon,&nImage,name);
			m_IconArrString[nIcon]=pos;

			if (*name==0) strcpy(name,"MISCS");

			GPImageList *SMainIl;
			int ImgLId;
			if ((ImgLId=GPC.GetImageListId(name))>=0 && (SMainIl=&(GPC.a_GPImageList[ImgLId]))!=NULL)
				m_IconArr[nIcon]=(HICON)	SMainIl->m_IL.ExtractIcon(nImage);
		}
		break;
	case 15: /*SetText*/
		if (atoipos>=0 && atoipos<10000)
		{
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
	case 16: /*SetInt*/
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
			const char *curpos=pos2;

			int nPos;
			for(nPos=istrt;nPos<=iend;nPos++)
			{
				if (curpos!=NULL)
				{
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
	case 17: /*SetDouble*/
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
			double tmpdou=0;
			const char *curpos=pos2;

			int nPos;
			for(nPos=istrt;nPos<=iend;nPos++)
			{
				if (curpos!=NULL)
				{
					tmpdou=atof(curpos);
					curpos=strchr(curpos,GPC.DelimiterIn1);
					if (curpos!=NULL) curpos++;
				}
				if ((UINT)nPos>=m_nDoubleArray)
				{
					double *tmp=new double [nPos+10];
					UINT i;
					for( i=0; i<m_nDoubleArray;i++)
						tmp[i]=m_DoubleArr[i];
					m_nDoubleArray=nPos+10;
					for(;i<m_nDoubleArray;i++)
						tmp[i]=0;
					delete[] m_DoubleArr;
					m_DoubleArr=tmp;
				}
				m_DoubleArr[nPos]=tmpdou;
			}
		}
		break;
	case 18: /*ScrollPoint*/ //nBegin,nEnd,nTime
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nPointArray) nEnd=m_nPointArray-1;
			qscroll(m_PointArr,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 19: /*ScrollRect*/
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nRectArray) nEnd=m_nRectArray-1;
			qscroll(m_RectArr,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 20: /*ScrollPen*/
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nPenArray) nEnd=m_nPenArray-1;
			qscroll((void **)m_PenArr,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 21: /*ScrollBrush*/
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nBrushArray) nEnd=m_nBrushArray-1;
			qscroll((void **)m_BrushArr,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 22: /*ScrollFont*/
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nFontArray) nEnd=m_nFontArray-1;
			qscroll((void **)m_FontArr,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 23: /*ScrollItem*/
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nDrawArray) nEnd=m_nDrawArray-1;
			qscroll(m_ArrDrawLParam,nBegin,nEnd,nTime,uEvery);
			qscroll(m_ArrDrawWParam,nBegin,nEnd,nTime,uEvery);
			qscroll(m_ArrDrawType,nBegin,nEnd,nTime,uEvery);
			qscroll(m_ArrDrawInitString,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 24: /*ScrollInt*/
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nIntArray) nEnd=m_nIntArray-1;
			qscroll(m_IntArr,nBegin,nEnd,nTime,uEvery);	
		}
		break;
	case 25: /*ScrollDouble*/
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nDoubleArray) nEnd=m_nDoubleArray-1;
			qscroll(m_DoubleArr,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 26: /*ScrollIcon*/
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nIconArray) nEnd=m_nIconArray-1;
			qscroll(m_IconArr,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 27: /*ScrollColor*/
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nRGBArray) nEnd=m_nRGBArray-1;
			qscroll(m_RGBArr,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 28: /*ScrollText*/
		{
			UINT nBegin=0,nEnd=0,uEvery=1;
			int nTime=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&nBegin,&nEnd,&nTime,&uEvery);
			if (nEnd>=m_nStringArray) nEnd=m_nStringArray-1;
			qscroll(m_StringArr,nBegin,nEnd,nTime,uEvery);
		}
		break;
	case 30: /*SetRegion*/
		if (atoipos>=0 && atoipos<500)
		{
			if ((UINT)atoipos>=m_nRgnArray)
			{
				CRgnExt **tmp=new CRgnExt * [atoipos+1];
				UINT i;
				for( i=0; i<m_nRgnArray;i++)
					tmp[i]=m_RgnArr[i];
				m_nRgnArray=atoipos+1;
				for(;i<m_nRgnArray;i++)
					tmp[i]=NULL;
				delete[] m_RgnArr;
				m_RgnArr=tmp;
			}
			if (m_RgnArr[atoipos]!=NULL) 
			{
				m_RgnArr[atoipos]->DeleteObject();
				delete m_RgnArr[atoipos]; 
				m_RgnArr[atoipos]=NULL; 
			}

			if (strlen(pos2)>3)
			{
				const char *cType[13]={
						"RECT","ELLIPTIC","POLYGON","ALTPOLYGON","POLYPOLYGON",
						"ALTPOLYPOLYGON","ROUNDRECT","COPY","FROMRECT","COMBINE_AND",
						"COMBINE_DIFF","COMBINE_OR","COMBINE_XOR",
					};
				char *buff=new char [strlen(pos2)+10];
				strcpy(buff,pos2);
				_strupr(buff);
				char *pos3=strchr(buff,',');
//				if (pos3!=NULL) pos3=strchr(++pos3,',');
				if (pos3==NULL) pos3="";
				else *(pos3++)=0;

				int i;
				for(i=0;i<13 && strcmp(cType[i],buff)!=0;i++);

				if (i<13) m_RgnArr[atoipos]=new CRgnExt;

				if (m_RgnArr[atoipos]!=NULL)
				{
					switch(i)
					{
					case 0: //RECT
					case 1: //ELLIPTIC
						{
							CRect re(0,0,0,0);
							m_LastScanf=sscanf(pos3,"%d,%d,%d,%d",&re.left,&re.top,&re.right,&re.bottom);
							switch(i)
							{
							case 0: //RECT
								m_RgnArr[atoipos]->CreateRectRgnIndirect(re);
								break;
							case 1: //ELLIPTIC
								m_RgnArr[atoipos]->CreateEllipticRgnIndirect(re);
								break;
							}
						}
						break;
					case 2: //POLYGON
					case 3: //ALTPOLYGON
						{
							char *posp=pos3;
							int nPo=0;
							do		nPo++;
							while((posp=strchr(++posp,GPC.DelimiterIn1))!=NULL);
							POINT *lpobase=new POINT [nPo];
							POINT *lpo=lpobase;
							posp=pos3;
							posp--;
							do	
							{
								lpo->x=lpo->y=0;
								m_LastScanf=sscanf(++posp,"%d,%d",&lpo->x,&lpo->y);
								lpo++;
							}
							while((posp=strchr(posp,GPC.DelimiterIn1))!=NULL);

							switch(i)
							{
							case 2: //POLYGON
								m_RgnArr[atoipos]->CreatePolygonRgn(lpobase,nPo,WINDING);
								break;
							case 3: //ALTPOLYGON
								m_RgnArr[atoipos]->CreatePolygonRgn(lpobase,nPo,ALTERNATE);
								break;
							}
							delete[]  lpobase;
						}
						break;
					case 4: //POLYPOLYGON
					case 5: //ALTPOLYPOLYGON
						{
							const char *posp=pos3;
							int nSeries=0,nAll=0;
							do		nAll++;
							while((posp=strchr(++posp,';'))!=NULL);
							posp=pos3;

							nSeries=nAll;

							do		nAll++;
							while((posp=strchr(++posp,GPC.DelimiterIn1))!=NULL);

							nAll--;
							POINT *lpobase=new POINT [nAll];
							POINT *lpo=lpobase;

							char *pos4=pos3;
							pos4--;
							LPINT plpCnt,lpCnt=new INT [nAll];
							plpCnt=lpCnt;

							do	
							{
								posp=pos4++;
								*plpCnt=0;
								char *posNULL=strchr(pos4,';');
								if (posNULL!=NULL) *posNULL=0;
								do	
								{
									lpo->x=lpo->y=0;
									m_LastScanf=sscanf(++posp,"%d,%d",&lpo->x,&lpo->y);
									*plpCnt=*plpCnt+1;
									lpo++;
								}
								while((posp=strchr(posp,GPC.DelimiterIn1))!=NULL);
								plpCnt++;
								if (posNULL!=NULL) *posNULL=';';
							}
							while((pos4=strchr(pos4,';'))!=NULL);

							switch(i)
							{
							case 4: //POLYPOLYGON
								m_RgnArr[atoipos]->CreatePolyPolygonRgn(lpobase,lpCnt,nSeries,WINDING);
								break;
							case 5: //ALTPOLYPOLYGON
								m_RgnArr[atoipos]->CreatePolyPolygonRgn(lpobase,lpCnt,nSeries,ALTERNATE);
								break;
							}

							delete[] lpCnt;
							delete[]  lpobase;
						}
						break;
					case 6: //ROUNDRECT
						{
							CRect re(0,0,0,0);
							int iWidth=0,iHeight=0;
							m_LastScanf=sscanf(pos3,"%d,%d,%d,%d,%d,%d",&re.left,&re.top,&re.right,&re.bottom,&iWidth,&iHeight);
							m_RgnArr[atoipos]->CreateRoundRectRgn(re.left,re.top,re.right,re.bottom,iWidth,iHeight);
						}
						break;
					case 7: //COPY
						{
							UINT nCopy=atoi(pos3);
							if (nCopy<m_nRgnArray && m_RgnArr[nCopy]!=NULL)
							{
								m_RgnArr[atoipos]->CreateRectRgn(0,0,1,1);
								m_RgnArr[atoipos]->CopyRgn(m_RgnArr[nCopy]);
							}
							else 
							{
								delete m_RgnArr[atoipos];
								m_RgnArr[atoipos]=NULL;
							}
						}
						break;
					case 8: //FROMRECT
						{
							int nRect=atoi(pos3);
							if (nRect>=0 && (UINT)nRect<m_nRectArray)
								m_RgnArr[atoipos]->CreateRectRgnIndirect(m_RectArr[nRect]);
							else
								if (nRect<0 && (UINT)(-nRect-1)*4<m_nDoubleArray)
									m_RgnArr[atoipos]->CreateRectRgn((int)m_DoubleArr[-nRect-1],(int)m_DoubleArr[-nRect],(int)m_DoubleArr[-nRect+1],(int)m_DoubleArr[-nRect+2]);
								else
								{
									delete m_RgnArr[atoipos];
									m_RgnArr[atoipos]=NULL;
								}
						}
						break;
					case 9:  //COMBINE_AND
					case 10: //COMBINE_DIFF
					case 11: //COMBINE_OR
					case 12: //COMBINE_XOR
						{
							int nRgn1=0,nRgn2=0;
							m_LastScanf=sscanf(pos3,"%d,%d",&nRgn1,&nRgn2);
							m_RgnArr[atoipos]->CreateRectRgn(0,0,0,0);
							if ((UINT)nRgn1<m_nRgnArray && (UINT)nRgn2<m_nRgnArray && m_RgnArr[nRgn1]!=NULL && m_RgnArr[nRgn2]!=NULL)
							{
								switch(i)
								{
								case 9:  //COMBINE_AND
									m_RgnArr[atoipos]->CombineRgn(m_RgnArr[nRgn1],m_RgnArr[nRgn2],RGN_AND);break;
								case 10: //COMBINE_DIFF
									m_RgnArr[atoipos]->CombineRgn(m_RgnArr[nRgn1],m_RgnArr[nRgn2],RGN_DIFF);break;
								case 11: //COMBINE_OR
									m_RgnArr[atoipos]->CombineRgn(m_RgnArr[nRgn1],m_RgnArr[nRgn2],RGN_OR);break;
								case 12: //COMBINE_XOR
									m_RgnArr[atoipos]->CombineRgn(m_RgnArr[nRgn1],m_RgnArr[nRgn2],RGN_XOR);break;
								}
							}
							else
							if (m_RgnArr[atoipos]!=NULL)
							{
								m_RgnArr[atoipos]->DeleteObject();
								delete m_RgnArr[atoipos];
								m_RgnArr[atoipos]=NULL;
							}
						}
						break;
					}
					m_RgnArr[atoipos]->CreationString=pos2;
				}
				delete[] buff;
			}
		}
		break;
	case 31: /*OffsetRgn*/
		{
			int nRegion=0,dx=0,dy=0;
			m_LastScanf=sscanf(pos,"%d,%d,%d",&nRegion,&dx,&dy);
			if ((UINT)nRegion<m_nRgnArray && m_RgnArr[nRegion]!=NULL)
				m_RgnArr[nRegion]->OffsetRgn(dx,dy);
		}
		break;
	case 32: /*OffsetRgnP*/
		{
			int nRegion=0,nPoint=0;
			m_LastScanf=sscanf(pos,"%d,%d",&nRegion,&nPoint);
			if ((UINT)nRegion<m_nRgnArray && m_RgnArr[nRegion]!=NULL)
			{
				if (nPoint>=0 && (UINT)nPoint<m_nPointArray)
					m_RgnArr[nRegion]->OffsetRgn(m_PointArr[nPoint]);
				else 
					if (nPoint<0 && (UINT)(-nPoint-1)*2<m_nDoubleArray)
						m_RgnArr[nRegion]->OffsetRgn((int)m_DoubleArr[-nPoint-1],(int)m_DoubleArr[-nPoint]);
			}
		}
		break;
	case 33: /*Print*/
		{
			int Dlg=0,Paper=-12345,Orient=-12345;
			WndPrint::TranslateParam(pos, Dlg,Paper,Orient);
			PrintDrawWnd(Dlg,Orient,Paper);
		}
		break;
	case 34: /*PrnName*/	m_DrawName=pos;		break;
	case 35: /*PrnMargins*/
		m_PrintMargins=CRect(2000,2000,2000,2000);
		m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&m_PrintMargins.left,&m_PrintMargins.top,&m_PrintMargins.right,&m_PrintMargins.bottom);
		break;
	case 36: /*PrnWinExt*/
		m_PrintWinExt=CSize(-12345,-12345);
		m_LastScanf=sscanf(pos,"%d,%d",&m_PrintWinExt.cx,&m_PrintWinExt.cy);
		break;
	case 37: /*PrnWinOrg*/
		m_PrintWinOrg=CPoint(-12345,-12345);
		m_LastScanf=sscanf(pos,"%d,%d",&m_PrintWinOrg.x,&m_PrintWinOrg.y);
		break;
	case 38: /*PrnVieExt*/
		m_PrintVieExt=CSize(-12345,-12345);
		m_LastScanf=sscanf(pos,"%d,%d",&m_PrintVieExt.cx,&m_PrintVieExt.cy);
		break;
	case 39: /*PrnVieOrg*/
		m_PrintVieOrg=CPoint(-12345,-12345);
		m_LastScanf=sscanf(pos,"%d,%d",&m_PrintVieOrg.x,&m_PrintVieOrg.y);
		break;
	case 40: /*LogSize*/
		if (oStr)	sprintf(oStr,"%d\x7F%d",m_LogSize.cx,m_LogSize.cy);
		m_LogSize.cx=m_LogSize.cy=0;
		m_LastScanf=sscanf(pos,"%d,%d",&m_LogSize.cx,&m_LogSize.cy);
		break;
	case 41: /*SetTimer "nTimer,nDelay,dValue,dDelta,dStop,bRedraw"*/
		{
			DRAWTIMER tmp={0};
			InitDRAWTIMER(&tmp);
			m_LastScanf=sscanf(pos,"%d,%d,%lg,%lg,%lg,%d",&tmp.nTimer,&tmp.nDelay,&tmp.dValue,&tmp.dDelta,&tmp.dStop,&tmp.bRedraw);
			if ((UINT)tmp.nTimer<m_nDrTimerArray)
			{
				if (m_DrTimerArr[tmp.nTimer].bisRun==TRUE)
				{
					m_DrTimerArr[tmp.nTimer].bisRun=FALSE;
					KillTimer(tmp.nTimer+TIMER_DRAW_START_ID);
				}

				m_DrTimerArr[tmp.nTimer]=tmp;
				SetTimer(tmp.nTimer+TIMER_DRAW_START_ID,tmp.nDelay,NULL);
			}
		}
		break;
	case 42: /*KillTimer nTimer*/
		if ((UINT)atoipos<m_nDrTimerArray && m_DrTimerArr[atoipos].bisRun==TRUE)
		{
			m_DrTimerArr[atoipos].bisRun=FALSE;
			KillTimer(m_DrTimerArr[atoipos].nTimer+TIMER_DRAW_START_ID);
		}
		break;
	case 43: /*SetPenWidth nPen,Width*/
		if ((UINT)atoipos<=m_nPenArray && m_PenArr[atoipos]!=NULL)
		{
			char *tmps=new char [m_PenArr[atoipos]->CreationString.GetLength()+50];
			int w=1;
			m_LastScanf=sscanf(m_PenArr[atoipos]->CreationString,"%d,%s",&w,tmps);
			m_PenArr[atoipos]->CreationString.Format("SetPen %d,%d,%s",atoipos,w,tmps);
			strcpy(tmps,m_PenArr[atoipos]->CreationString);
			DoMethod(tmps,NULL);
			delete[] tmps;
		}
		break;
	case 44: /*SetPenColor nPen,R,G,B*/
		if ((UINT)atoipos<m_nPenArray && m_PenArr[atoipos]!=NULL)
		{
			char *tmps=new char [m_PenArr[atoipos]->CreationString.GetLength()+50];
			int w,r,g,b;
			w=r=g=b=0;
			m_LastScanf=sscanf(m_PenArr[atoipos]->CreationString,"%d,%d,%d,%d,%s",&w,&r,&g,&b,tmps);
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&atoipos,&r,&g,&b);
			m_PenArr[atoipos]->CreationString.Format("SetPen %d,%d,%d,%d,%d,%s",atoipos,w,r,g,b,tmps);
			strcpy(tmps,m_PenArr[atoipos]->CreationString);
			DoMethod(tmps,NULL);
			delete[] tmps;
		}
		break;
	case 45: /*Redraw*/
		m_uRedrawFlag=1;
		Invalidate();
		break;
	case 46: /*SetAutoRedraw*/
		retint=m_bAutoRedraw;
		m_bAutoRedraw=atoi(pos);
		break;
	case 47: /*SetEraseBkg*/
		retint=m_bEraseBkg;
		m_bEraseBkg=atoi(pos);
		break;

	default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
	}

	switch(nfunc)
	{
	case 0: /*SetPen*/
	case 10: /*SetBPen*/
	case 1: /*SetBrush*/
	case 2: /*SetPoint*/
	case 3: /*SetRect*/
	case 4: /*SetFont*/
	case 5: /*DeleteItem*/
	case 6: /*DeleteItems*/
	case 7: /*AddItem*/
	case 8: /*SetItem*/
	case 9: /*InsertItem*/
	case 12: /*SetColor*/
	case 13: /*AddItems*/
	case 29: /*SetItems*/
	case 14: /*SetIcon*/
	case 15: /*SetText*/
	case 16: /*SetInt*/
	case 17: /*SetDouble*/
	case 18: /*ScrollPoint*/ //nBegin,nEnd,nTime
	case 19: /*ScrollRect*/
	case 20: /*ScrollPen*/
	case 21: /*ScrollBrush*/
	case 22: /*ScrollFont*/
	case 23: /*ScrollItem*/
	case 24: /*ScrollInt*/
	case 25: /*ScrollDouble*/
	case 26: /*ScrollIcon*/
	case 27: /*ScrollColor*/
	case 28: /*ScrollText*/
	case 30: /*SetRegion*/
	case 31: /*OffsetRgn*/
	case 32: /*OffsetRgnP*/
	case 40: /*LogSize*/
	case 43: /*SetPenWidth nPen,Width*/
	case 44: /*SetPenColor nPen,R,G,B*/
	case 46: /*SetAutoRedraw*/
		m_uRedrawFlag=TRUE;
		break;
	}








	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
	return nfunc;
}

UINT GPDrawWnd::GPSetProperty(char *iStr)
{
	char *iValue=new char [strlen(iStr)+5];
	strcpy(iValue,iStr);
	UINT ret=1;
	char *pos=strchr(iValue,'=');

	if (pos!=NULL && m_hWnd)
	{
		char *prop[]={ "TEXT", "ADDSTYLE", "DELSTYLE","STYLE",};
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
					break;
			case 1: // ADDSTYLE
			case 2: // DELSTYLE
			case 3: // STYLE
				ret=2;
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

void GPDrawWnd::InitDRAWITEMDATA(PDRAWITEMDATA pdid)
{
	pdid->po1.x=pdid->po1.y=0;
	pdid->po2.x=pdid->po2.y=0;
	pdid->re1.SetRect(0,0,0,0);
	pdid->re2.SetRect(0,0,0,0);
	pdid->clr1=0;
	pdid->clr2=0;
}

void GPDrawWnd::InitDRAWITEMDATANUM(PDRAWITEMDATANUM pdid)
{
	pdid->i1=pdid->i2=pdid->i3=pdid->i4=0;
	pdid->d1=pdid->d2=pdid->d3=pdid->d4=0;
}
void GPDrawWnd::InitDRAWTIMER(PDRAWTIMER pdid)
{
	pdid->nTimer=0;
	pdid->nDelay=1000;
	pdid->dValue=0;
	pdid->dDelta=1;
	pdid->dStop=9.9e300;
	pdid->bRedraw=TRUE;
	pdid->bisRun=FALSE;
}
void GPDrawWnd::InitDRAWITEMDATAMATH(PDRAWITEMDATAMATH pdid)
{
	pdid->iFunction=0;
	pdid->nArg=0;
	pdid->nResults=0;
	int i;
	for(i=0;i<16;i++)
	{
		pdid->iArgAdress[i]=0;
		pdid->iArgType[i]=0;
		pdid->dConst[i]=0;
		pdid->iResultsArr[i]=0;
		pdid->iResultsType[i]=0;
	}
}
void GPDrawWnd::InitDRAWITEMDATATEXT(PDRAWITEMDATATEXT pdid)
{
	pdid->re.SetRect(0,0,0,0);
	pdid->po.x=pdid->po.y=0;
	pdid->text="";
	pdid->flags=0;
	pdid->flags2=0;
	pdid->nBrush=-1;
}
void GPDrawWnd::InitDRAWITEMDATASTR(PDRAWITEMDATASTR pdid)
{
	pdid->text="";
	pdid->format="";
	pdid->nSourse=0;
	pdid->nDest=0;
}
void GPDrawWnd::InitDRAWITEMDATAPRG(PDRAWITEMDATAPRG pdid)
{
	pdid->QurentOffset=pdid->PrevOffset=pdid->PrevPosition=pdid->QurentPosition=CPoint(0,0);
	pdid->d1=pdid->d2=pdid->d3=pdid->d4=pdid->d5=0;
	pdid->counter=0;
	pdid->DIDNum=NULL;
	pdid->DIDText=NULL;
	pdid->DID=NULL;
	pdid->IsRun=FALSE;
	pdid->NextJOB=pdid->PrevJOB=-1;
}


long GPDrawWnd::TranslateETO(const char * iStr)
{
	const char *nm[8]={
			"ETO_OPAQUE","ETO_CLIPPED","ETO_GLYPH_INDEX","ETO_RTLREADING","ETO_NUMERICSLOCAL",
			"ETO_NUMERICSLATIN","ETO_IGNORELANGUAGE","ETO_PDY",
		};
	const UINT uin[8]={
			ETO_OPAQUE,ETO_CLIPPED,ETO_GLYPH_INDEX,ETO_RTLREADING,ETO_NUMERICSLOCAL,
			ETO_NUMERICSLATIN,ETO_IGNORELANGUAGE,ETO_PDY,
		};
	long ret=0;
	char *buff=new char [strlen(iStr)+10];
	strcpy(buff,iStr);
	_strupr(buff);

	int i;
	for(i=0;i<8;i++)
		if (strstr(buff,nm[i])!=NULL)
			ret|=uin[i];

	if (ret==0) ret=ETO_OPAQUE;

	delete[] buff;
	return ret;
}

long GPDrawWnd::TranslateDT(const char * iStr)
{
	const char *nm[24]={
			"DT_TOP","DT_LEFT","DT_CENTER","DT_RIGHT","DT_VCENTER",
			"DT_BOTTOM","DT_WORDBREAK","DT_SINGLELINE","DT_EXPANDTABS","DT_TABSTOP",
			"DT_NOCLIP","DT_EXTERNALLEADING","DT_CALCRECT","DT_NOPREFIX","DT_INTERNAL",
			"DT_EDITCONTROL","DT_PATH_ELLIPSIS","DT_END_ELLIPSIS","DT_MODIFYSTRING","DT_RTLREADING",
			"DT_WORD_ELLIPSIS","DT_NOFULLWIDTHCHARBREAK","DT_PREFIXONLY","TA_UPDATECP",
		};
	const UINT uin[24]={
			DT_TOP,DT_LEFT,DT_CENTER,DT_RIGHT,DT_VCENTER,
			DT_BOTTOM,DT_WORDBREAK,DT_SINGLELINE,DT_EXPANDTABS,DT_TABSTOP,
			DT_NOCLIP,DT_EXTERNALLEADING,DT_CALCRECT,DT_NOPREFIX,DT_INTERNAL,
			DT_EDITCONTROL,DT_PATH_ELLIPSIS,DT_END_ELLIPSIS,DT_MODIFYSTRING,DT_RTLREADING,
			DT_WORD_ELLIPSIS,DT_NOFULLWIDTHCHARBREAK,DT_PREFIXONLY,TA_UPDATECP,
		};
	long ret=0;
	char *buff=new char [strlen(iStr)+10];
	strcpy(buff,iStr);
	_strupr(buff);

	int i;
	for(i=0;i<24;i++)
		if (strstr(buff,nm[i])!=NULL)
			ret|=uin[i];

	if (ret==0) ret=DT_LEFT;

	delete[] buff;
	return ret;
}

#include "DlgDrawEdit.h"

void GPDrawWnd::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	if (((point.x>4 || point.y>4) && ((MK_CONTROL|MK_SHIFT)&nFlags)!=(MK_CONTROL|MK_SHIFT)))
		CWnd::OnLButtonDblClk(nFlags, point);
	else
	{
		CDlgDrawEdit dlg(this,this);
		dlg.DoModal();
	}
}

void GPDrawWnd::ParentNotify(UINT message, LPARAM lParam) 
{
	char txt[100];
	if (message==WM_CREATE || message==WM_DESTROY)
		sprintf(txt,"%d\x7F%d\x7F%X",message/0x10000,(message&0xFFFF),lParam/0x10000);
	else
		sprintf(txt,"%d\x7F%d\x7F%d\x7F%d",message/0x10000,(message&0xFFFF),lParam/0x10000,(lParam&0xFFFF));
	if (referGPU!=NULL)	
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"ParentNotify",txt);
}

LRESULT GPDrawWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
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

	LRESULT lr;
	if ((message==WM_SETCURSOR && GPC.m_bWaitCursor)||(m_bEraseBkg==FALSE && message==WM_ERASEBKGND))
		lr=FALSE;
	else lr=CWnd::WindowProc(message, wParam, lParam);


	if (message==GPN_DRAWMOVE && wParam!=NULL)
	{
		CRect re(0,0,0,0);
		if ((UINT)lParam<m_nRectArray) re=m_RectArr[lParam];
			else
			if (lParam<0 && (UINT)(-lParam-1)*4<m_nDoubleArray)
			{
				int nRect;
				re.left=(int)m_DoubleArr[nRect=(-lParam-1)*4];
				re.top=(int)m_DoubleArr[nRect+1];
				re.right=(int)m_DoubleArr[nRect+2];
				re.bottom=(int)m_DoubleArr[nRect+3];
			}
		if (!re.IsRectEmpty())
			::MoveWindow((HWND)wParam,re.left,re.top,re.Width(),re.Height(),TRUE);
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
	return lr;
}

BOOL GPDrawWnd::PreTranslateMessage(MSG* pMsg) 
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
	
	return CWnd::PreTranslateMessage(pMsg);
}

void GPDrawWnd::OnClose() 
{
	if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClose","");
//	CWnd::OnClose();
}

void GPDrawWnd::OnSizing(UINT fwSide, LPRECT pRect) 
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

	if (EnableSz) CWnd::OnSizing(fwSide, pRect);

	GetParent()->SendMessage(GPN_UPDATESIZE);
}



HBRUSH GPDrawWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CWnd::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}

BOOL GPDrawWnd::InsertEmptyItem(UINT uItemBefore, UINT uCount)
{
	UINT newCount=m_nDrawArray;
	UINT i;

	if (uItemBefore>=m_nDrawArray || m_nDraw+uCount>=m_nDrawArray)
		newCount=m_nDrawArray+uCount+50;

	if (newCount>m_nDrawArray)
	{
		UINT *tmpT=new UINT  [newCount];
		WPARAM *tmpWP=new WPARAM [newCount];
		LPARAM *tmpLP=new LPARAM [newCount];
		CString *tmpIS=new CString [newCount];

		for(i=0; i<m_nDrawArray;i++)
		{
			tmpIS[i]=m_ArrDrawInitString[i];
			tmpT[i]=m_ArrDrawType[i];
			tmpWP[i]=m_ArrDrawWParam[i];
			tmpLP[i]=m_ArrDrawLParam[i];
		}
		m_nDrawArray=newCount;
		for(;i<m_nDrawArray;i++)
		{
			tmpIS[i]="";
			tmpT[i]=DUT_NONE;
			tmpWP[i]=NULL;
			tmpLP[i]=NULL;
		}

		delete[]  m_ArrDrawInitString;
		delete[] m_ArrDrawWParam;
		delete[] m_ArrDrawLParam;
		delete[] m_ArrDrawType;
		m_ArrDrawInitString=tmpIS;
		m_ArrDrawType=tmpT;
		m_ArrDrawWParam=tmpWP;
		m_ArrDrawLParam=tmpLP;
	}

	if (uItemBefore<m_nDraw)
		for(i=m_nDrawArray-1;i>=uItemBefore+uCount;i--)
		{
			m_ArrDrawInitString[i]=m_ArrDrawInitString[i-uCount];
			m_ArrDrawType[i]=m_ArrDrawType[i-uCount];
			m_ArrDrawWParam[i]=m_ArrDrawWParam[i-uCount];
			m_ArrDrawLParam[i]=m_ArrDrawLParam[i-uCount];
		}

	for(i=uItemBefore;i<uItemBefore+uCount;i++)
		{
			m_ArrDrawInitString[i]="";
			m_ArrDrawType[i]=DUT_NONE;
			m_ArrDrawWParam[i]=NULL;
			m_ArrDrawLParam[i]=NULL;
		}

	if (m_nDraw<=uItemBefore) m_nDraw=uItemBefore;
	m_nDraw+=uCount;

	return TRUE;
}

UINT GPDrawWnd::DeleteItem(UINT nItem)
{
	UINT i;

	if (nItem<m_nDraw)
	{
		DestroyItem(nItem);

		for(i=nItem;i<m_nDraw;i++)
		{
			m_ArrDrawInitString[i]=m_ArrDrawInitString[i+1];
			m_ArrDrawType[i]=m_ArrDrawType[i+1];
			m_ArrDrawWParam[i]=m_ArrDrawWParam[i+1];
			m_ArrDrawLParam[i]=m_ArrDrawLParam[i+1];
		}

		m_ArrDrawInitString[m_nDraw]="";
		m_ArrDrawType[m_nDraw]=DUT_NONE;
		m_ArrDrawWParam[m_nDraw]=NULL;
		m_ArrDrawLParam[m_nDraw]=NULL;

		m_nDraw--;
	}
	return m_nDraw;
}

void GPDrawWnd::DestroyItem(UINT nItem)
{
	if (nItem<m_nDraw)
	{
		switch(m_ArrDrawType[nItem])
		{
		case DUT_COLORADJ:
			if (m_ArrDrawLParam[nItem]!=NULL)
			{
				delete (COLORADJUSTMENT *) m_ArrDrawLParam[nItem];
				m_ArrDrawLParam[nItem]=NULL;
			}
			break;
		case DUT_ARC:
		case DUT_ARCTO:
		case DUT_FILLRECT: 
		case DUT_FRAMERECT: 
		case DUT_INVERTRECT: 
		case DUT_FILLSRECT: 
		case DUT_EDGE:
		case DUT_STATEICON:
		case DUT_STATEICONR:
		case DUT_CHORD:
		case DUT_CHORDRP:
		case DUT_PIE:
		case DUT_PIERP:
		case DUT_ROUNDRECT:
		case DUT_ROUNDRECTR:
		case DUT_PIXEL:
		case DUT_FLOODFILL:
		case DUT_EXTFLOODFILL:
		case DUT_FRAMECTRL:
			if (m_ArrDrawLParam[nItem]!=NULL)
			{
				delete (PDRAWITEMDATA) m_ArrDrawLParam[nItem];
				m_ArrDrawLParam[nItem]=NULL;
			}
			break;
		case DUT_ANGLEARC:
		case DUT_ANGLEARCP:
		case DUT_3DRECTR:
		case DUT_EDGER:
		case DUT_ARCRPP:
		case DUT_ARCRPPTO:
		case DUT_ARROW:
		case DUT_ARROWTO:
		case DUT_ARROWP:
		case DUT_ARROWPTO:
		case DUT_OFFSETREGION:
		case DUT_COMBINEREGION:
		case DUT_FRAMERGN:
		case DUT_ARITHMETIC: 
		case DUT_SETRGB: 
		case DUT_IFGOTO:
		case DUT_IFGOSUB:
		case DUT_FRAMECTRLR:
			if (m_ArrDrawLParam[nItem]!=NULL)
			{
				delete (PDRAWITEMDATANUM) m_ArrDrawLParam[nItem];
				m_ArrDrawLParam[nItem]=NULL;
			}
			break;
		case DUT_CLONE:
		case DUT_CLONETO:
		case DUT_CLONEC:
		case DUT_CLONECTO:
			if (m_ArrDrawLParam[nItem]!=NULL)
			{
				if (((PDRAWITEMDATAPRG) m_ArrDrawLParam[nItem])->DID!=NULL)
					delete ((PDRAWITEMDATAPRG) m_ArrDrawLParam[nItem])->DID;
				((PDRAWITEMDATAPRG) m_ArrDrawLParam[nItem])->DID=NULL;

				if (((PDRAWITEMDATAPRG) m_ArrDrawLParam[nItem])->DIDNum!=NULL)
					delete ((PDRAWITEMDATAPRG) m_ArrDrawLParam[nItem])->DIDNum;
				((PDRAWITEMDATAPRG) m_ArrDrawLParam[nItem])->DIDNum=NULL;

				if (((PDRAWITEMDATAPRG) m_ArrDrawLParam[nItem])->DIDText!=NULL)
					delete ((PDRAWITEMDATAPRG) m_ArrDrawLParam[nItem])->DIDText;
				((PDRAWITEMDATAPRG) m_ArrDrawLParam[nItem])->DIDText=NULL;

				delete (PDRAWITEMDATAPRG) m_ArrDrawLParam[nItem];
				m_ArrDrawLParam[nItem]=NULL;
			}
			break;
		case DUT_POLYLINE:
		case DUT_POLYLINETO:
		case DUT_POLYPOLY:
		case DUT_POLYPOLYP:
		case DUT_POLYBEZIER:
		case DUT_POLYBEZIERTO:
		case DUT_POLYGON:
		case DUT_PPOLYGON:
		case DUT_PPOLYGONP:
			if (m_ArrDrawLParam[nItem]!=NULL)
			{
				delete[]  (POINT *) m_ArrDrawLParam[nItem];
				m_ArrDrawLParam[nItem]=NULL;
			}
			break;
		case DUT_POLYLINEP:
		case DUT_POLYLINEPTO:
		case DUT_POLYBEZIERP:
		case DUT_POLYBEZIERPTO:
		case DUT_POLYGONP:
			if (m_ArrDrawLParam[nItem]!=NULL)
			{
				delete (int *) m_ArrDrawLParam[nItem];
				m_ArrDrawLParam[nItem]=NULL;
			}
			break;
		case DUT_STATETEXT:
		case DUT_STATETEXTR:
		case DUT_TEXTOUT:
		case DUT_TEXT:
		case DUT_TEXTR:
			if (m_ArrDrawLParam[nItem]!=NULL)
			{
				delete (PDRAWITEMDATATEXT) m_ArrDrawLParam[nItem];
				m_ArrDrawLParam[nItem]=NULL;
			}
			break;
		case DUT_FOCUSRECT:
		case DUT_ELLIPSE:
		case DUT_RECT:
			if (m_ArrDrawLParam[nItem]!=NULL)
			{
				delete (LPRECT) m_ArrDrawLParam[nItem];
				m_ArrDrawLParam[nItem]=NULL;
			}
			break;
		case DUT_EXTTEXTOUT:
		case DUT_EXTTEXTOUTP:
		case DUT_TABTEXTOUT:
		case DUT_TABTEXTOUTP:
			if (m_ArrDrawLParam[nItem]!=NULL)
			{
				delete (PDRAWITEMDATATEXT) m_ArrDrawLParam[nItem];
				m_ArrDrawLParam[nItem]=NULL;
			}
			if (m_ArrDrawWParam[nItem]!=NULL)
			{
				delete (LPINT) m_ArrDrawWParam[nItem];
				m_ArrDrawWParam[nItem]=NULL;
			}
			break;
		case DUT_SETMITERLIMIT:
			if (m_ArrDrawLParam[nItem]!=NULL)
			{
				delete (float *) m_ArrDrawLParam[nItem];
				m_ArrDrawLParam[nItem]=NULL;
			}
			break;
		case DUT_SETDOUBLE:
			if (m_ArrDrawLParam[nItem]!=NULL)
			{
				delete 	(double *) m_ArrDrawLParam[nItem];
				m_ArrDrawWParam[nItem]=NULL;
			}
			break;
		case DUT_SETPOINT:
			if (m_ArrDrawLParam[nItem]!=NULL)
			{
				delete 	(CPoint *) m_ArrDrawLParam[nItem];
				m_ArrDrawWParam[nItem]=NULL;
			}
			break;
		case DUT_SETRECT:
		case DUT_BOUNDSRECT:
		case DUT_EXCLRECT:
			if (m_ArrDrawLParam[nItem]!=NULL)
			{
				delete 	(CRect *) m_ArrDrawLParam[nItem];
				m_ArrDrawWParam[nItem]=NULL;
			}
			break;
		case DUT_MATH: 
			if (m_ArrDrawLParam[nItem]!=NULL)
			{
				delete 	(PDRAWITEMDATAMATH) m_ArrDrawLParam[nItem];
				m_ArrDrawWParam[nItem]=NULL;
			}
			break;
		case DUT_STRCAT:	
		case DUT_ITOSTR:	
		case DUT_DTOSTR:	
		case DUT_TTOSTR:	
			if (m_ArrDrawLParam[nItem]!=NULL)
			{
				delete 	(PDRAWITEMDATASTR) m_ArrDrawLParam[nItem];
				m_ArrDrawWParam[nItem]=NULL;
			}
			break;

		case DUT_NONE:
			break;
		default:
			break;
		}

		m_ArrDrawInitString[nItem]="";
		m_ArrDrawType[nItem]=DUT_NONE;
		m_ArrDrawWParam[nItem]=0;
		m_ArrDrawLParam[nItem]=0;
	}
}


BOOL GPDrawWnd::SetItem(UINT nItem, const char *cctmpiStr)
{
	char *iStr=new char [strlen(cctmpiStr)+100];
	strcpy(iStr,cctmpiStr);
	BOOL ret=FALSE;
	m_ArrDrawInitString[nItem]=iStr;
	if (nItem<m_nDraw)
	{
		char ctype[50];
		int smespace=0;
		strncpy(ctype,iStr,45);
		ctype[45]=0;
		char *pos=strchr(ctype,'=');
		if (pos==NULL) pos="";
		else	
		{
			*(pos++)=0;
			pos=strchr(iStr,'=');  //????const GVP????
			pos++;
		}
		while(ctype[smespace]==' ') smespace++;

		UINT ui;
		for(ui=0;ui<uNUnitType && _stricmp(ctype+smespace,cArrUnitType[ui])!=0;ui++); 

		if (ui<uNUnitType)
		{
			DestroyItem(nItem);
			m_ArrDrawInitString[nItem]=iStr;
			ret=TRUE;
			m_ArrDrawType[nItem]=uArrUnitType[ui];
			switch(uArrUnitType[ui])
			{
			case DUT_BKG: 
			case DUT_FRG:
				if (strncmp(pos,"CLR",3)==0)
					m_ArrDrawWParam[nItem]=0xFF000000+atoi(pos+3);
				else
				{
					UINT R=0,G=0,B=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d",&R,&G,&B);
					m_ArrDrawWParam[nItem]=RGB(R,G,B);
				}
				break;
			case DUT_PEN:
			case DUT_BRUSH: 
			case DUT_FONT:
				m_ArrDrawWParam[nItem]=atoi(pos);
				break;
			case DUT_MOVE:
				{
					WORD x=0,y=0;
					m_LastScanf=sscanf(pos,"%d,%d",&x,&y);
					m_ArrDrawWParam[nItem]=MAKEWPARAM(x,y);
				}
				break;
			case DUT_MOVER:
				{
					WORD x=0,y=0;
					UINT nRect=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d",&nRect,&x,&y);
					m_ArrDrawWParam[nItem]=MAKEWPARAM(x,y);
					m_ArrDrawLParam[nItem]=nRect;
				}
				break;
			case DUT_MOVEP:
				m_ArrDrawWParam[nItem]=atoi(pos);
				break;
			case BUT_BKMODE:
				m_ArrDrawWParam[nItem]=(_strnicmp(pos,"TRA",3)==0)?TRANSPARENT:OPAQUE; 
				break;
			case DUT_PFILLMODE:
				m_ArrDrawWParam[nItem]=(_strnicmp(pos,"WIN",3)==0)?WINDING:ALTERNATE; 
				break;
			case DUT_ROP2:
				{
					const char *nm[16]={
						"BLACK","WHITE","NOP","NOT","COPYPEN",
						"NOTCOPYPEN","MERGEPENNOT","MASKPENNOT","MERGENOTPEN","MASKNOTPEN",
						"MERGEPEN","NOTMERGEPEN","MASKPEN","NOTMASKPEN","XORPEN",
						"NOTXORPEN",
						};
					const int  iType[16]={
						R2_BLACK,R2_WHITE,R2_NOP,R2_NOT,R2_COPYPEN,
						R2_NOTCOPYPEN,R2_MERGEPENNOT,R2_MASKPENNOT,R2_MERGENOTPEN,R2_MASKNOTPEN,
						R2_MERGEPEN,R2_NOTMERGEPEN,R2_MASKPEN,R2_NOTMASKPEN,R2_XORPEN,
						R2_NOTXORPEN,
						};
					int i;
					for(i=0;i<16 && _stricmp(pos,nm[i])!=0;i++);
					if (i>=16) i=0;
					m_ArrDrawWParam[nItem]=iType[i];
				}
				break;
			case DUT_SBLTMODE:
				{
					const char *nm[9]={
						"BLACKONWHITE","WHITEONBLACK","COLORONCOLOR","HALFTONE","MAXSTRETCHBLTMODE",
						"STRETCH_ANDSCANS","STRETCH_ORSCANS","STRETCH_DELETESCANS","STRETCH_HALFTONE",
						};
					const int  iType[9]={
						BLACKONWHITE,WHITEONBLACK,COLORONCOLOR,HALFTONE,MAXSTRETCHBLTMODE,
						STRETCH_ANDSCANS,STRETCH_ORSCANS,STRETCH_DELETESCANS,STRETCH_HALFTONE
						};
					int i;
					for(i=0;i<9 && _stricmp(pos,nm[i])!=0;i++);
					if (i>=9) i=0;
					m_ArrDrawWParam[nItem]=iType[i];
				}
				break;
			case DUT_COLORADJ:
				{
					const char *nm[13]={
						"_EQUAL_ENERGY","_A","_B","_C","_D50",
						"_D55","_D65","_D75","_F2","_TURNGSTEN",
						"_DAYLIGHT","_FLUORESCENT","_NTSC",
						};
					const int  iType[13]={
						0/*ILLUMINANT_EQUAL_ENERGY*/,ILLUMINANT_A,ILLUMINANT_B,ILLUMINANT_C,ILLUMINANT_D50,
						ILLUMINANT_D55,ILLUMINANT_D65,ILLUMINANT_D75,ILLUMINANT_F2,9/*ILLUMINANT_TURNGSTEN*/,
						ILLUMINANT_DAYLIGHT,ILLUMINANT_FLUORESCENT,ILLUMINANT_NTSC,
						};
					COLORADJUSTMENT *lp=new COLORADJUSTMENT;
					m_ArrDrawLParam[nItem]=(WPARAM)lp;
					lp->caSize=sizeof(*lp);
					lp->caFlags=0;
					lp->caIlluminantIndex=0;
					lp->caRedGamma=10000;
					lp->caGreenGamma=10000;
					lp->caBlueGamma=10000;
					lp->caReferenceBlack=0;
					lp->caReferenceWhite=6000;
					lp->caContrast=0;
					lp->caBrightness=0;
					lp->caColorfulness=0;
					lp->caRedGreenTint=0;

					if (strstr(pos,"NEGATIVE")!=NULL) lp->caFlags=CA_NEGATIVE;
					else 
						if (strstr(pos,"LOG_FILTER")!=NULL) lp->caFlags=CA_LOG_FILTER;

					int i;
					for(i=0;i<13 && strstr(pos,nm[i])!=0;i++);
					if (i>=13) i=0;
					lp->caIlluminantIndex=iType[i];

					m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d,%d,%d,%d,%d",
							&lp->caRedGamma,
							&lp->caGreenGamma,
							&lp->caBlueGamma,
							&lp->caReferenceBlack,
							&lp->caReferenceWhite,
							&lp->caContrast,
							&lp->caBrightness,
							&lp->caColorfulness,
							&lp->caRedGreenTint
							);
				}
				break;
			case DUT_MAPMODE: 
				{
					const char *nm[11]={
						"MM_TEXT","MM_LOMETRIC","MM_HIMETRIC","MM_LOENGLISH","MM_HIENGLISH",
						"MM_TWIPS","MM_ISOTROPIC","MM_ANISOTROPIC","MM_MIN","MM_MAX",
						"MM_MAX_FIXEDSCALE",
						};
					const int  iType[11]={
						MM_TEXT,MM_LOMETRIC,MM_HIMETRIC,MM_LOENGLISH,MM_HIENGLISH,
						MM_TWIPS,MM_ISOTROPIC,MM_ANISOTROPIC,MM_MIN,MM_MAX,
						MM_MAX_FIXEDSCALE,
						};
					int i;
					for(i=0;i<11 && _stricmp(pos,nm[i])!=0;i++);
					if (i>=11) i=0;
					m_ArrDrawWParam[nItem]=iType[i];
				}
				break;
			case DUT_VPORTORG:
			case DUT_VPORTEXT:
			case DUT_BRUSHORG:
			case DUT_WINDOWORG:
			case DUT_WINDOWEXT:
			case DUT_LINETO:
				{
					WORD x=0,y=0;
					m_LastScanf=sscanf(pos,"%d,%d",&x,&y);
					m_ArrDrawWParam[nItem]=MAKEWPARAM(x,y);
				}
				break;
			case DUT_STOCKOBJ:
				{
					const char  * nm[]={
						"WHITE_BRUSH","LTGRAY_BRUSH","GRAY_BRUSH","DKGRAY_BRUSH","BLACK_BRUSH",
						"NULL_BRUSH","WHITE_PEN","BLACK_PEN","NULL_PEN","OEM_FIXED_FONT",
						"ANSI_FIXED_FONT","ANSI_VAR_FONT","SYSTEM_FONT","DEVICE_DEFAULT_FONT","DEFAULT_PALETTE",
						"SYSTEM_FIXED_FONT","DEFAULT_GUI_FONT","DC_BRUSH","DC_PEN",
						};
					int i;
					for(i=0;i<19 && _stricmp(pos,nm[i])!=0;i++);
					if (i>=19) i=0;
					m_ArrDrawWParam[nItem]=i;
				}
				break;
			case DUT_LINETOP:
				m_ArrDrawWParam[nItem]=atoi(pos);
				break;
			case DUT_ARCTO:
			case DUT_ARC:
				{
					PDRAWITEMDATA did=new DRAWITEMDATA;
					InitDRAWITEMDATA(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d,%d,%d,%d",
						&did->re1.left,&did->re1.top,&did->re1.right,&did->re1.bottom,
						&did->po1.x,&did->po1.y,&did->po2.x,&did->po2.y
						);
				}
				break;
			case DUT_ARCRPP:
			case DUT_ARCRPPTO:
				{
					PDRAWITEMDATANUM did=new DRAWITEMDATANUM;
					InitDRAWITEMDATANUM(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					m_LastScanf=sscanf(pos,"%d,%d,%d",&did->i3,&did->i1,&did->i2);
				}
				break;
			case DUT_ANGLEARC:
				{
					PDRAWITEMDATANUM did=new DRAWITEMDATANUM;
					InitDRAWITEMDATANUM(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%lg,%lg",&did->i1,&did->i2,&did->i3,&did->d1,&did->d2);
				}
				break;
			case DUT_ANGLEARCP:
				{
					PDRAWITEMDATANUM did=new DRAWITEMDATANUM;
					InitDRAWITEMDATANUM(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					m_LastScanf=sscanf(pos,"%d,%d,%lg,%lg",&did->i1,&did->i3,&did->d1,&did->d2);
				}
				break;
			case DUT_ARCDIRECTION:
					m_ArrDrawLParam[nItem]=strstr(pos,"COU")==NULL?AD_CLOCKWISE:AD_COUNTERCLOCKWISE;
				break;
			case DUT_POLYLINE:
			case DUT_POLYLINETO:
			case DUT_POLYBEZIER:
			case DUT_POLYBEZIERTO:
			case DUT_POLYGON:
				{
					char *pos2=pos;
					do		m_ArrDrawWParam[nItem]++;
					while((pos2=strchr(++pos2,GPC.DelimiterIn1))!=NULL);
					POINT *lpo=new POINT [m_ArrDrawWParam[nItem]];
					m_ArrDrawLParam[nItem]=(LPARAM)lpo;
					pos2=pos;
					pos2--;
					do	
					{
						lpo->x=lpo->y=0;
						m_LastScanf=sscanf(++pos2,"%d,%d",&lpo->x,&lpo->y);
						lpo++;
					}
					while((pos2=strchr(pos2,GPC.DelimiterIn1))!=NULL);
				}
				break;
			case DUT_POLYLINEP:
			case DUT_POLYLINEPTO:
			case DUT_POLYBEZIERP:
			case DUT_POLYBEZIERPTO:
			case DUT_POLYGONP:
				if (strstr(pos,"...")==NULL)
				{
					char *pos2=pos;
					do		m_ArrDrawWParam[nItem]++;
					while((pos2=strchr(++pos2,GPC.DelimiterIn1))!=NULL);
					int *lpi=new int [m_ArrDrawWParam[nItem]];
					m_ArrDrawLParam[nItem]=(LPARAM)lpi;
					pos2=pos;
					pos2--;
					do	
					{
						*lpi=atoi(++pos2);
						lpi++;
					}
					while((pos2=strchr(pos2,GPC.DelimiterIn1))!=NULL);
				}
				else
				{
					int iStart=atoi(pos);
					int iEnd=atoi(strstr(pos,"...")+3);
					if (abs(iEnd-iStart)>0)
					{
						int *lpi=new int [abs(iEnd-iStart)+1];
						m_ArrDrawLParam[nItem]=(LPARAM)lpi;
						if (iEnd>0)
						{
							m_ArrDrawWParam[nItem]=iEnd-iStart+1;
							int i;
							for(i=iStart;i<=iEnd;lpi++,i++)
								*lpi=i;
						}
						else
						{
							m_ArrDrawWParam[nItem]=-iEnd+iStart+1;
							int i;
							for(i=iStart;i>=iEnd;lpi++,i--)
								*lpi=i;
						}
					}
				}
				break;
			case DUT_POLYPOLY:
			case DUT_PPOLYGON:
				{
					char *pos2=pos;
					int nAll=0;
					do		nAll++;
					while((pos2=strchr(++pos2,';'))!=NULL);
					pos2=pos;

					m_ArrDrawWParam[nItem]=nAll;

					do		nAll++;
					while((pos2=strchr(++pos2,GPC.DelimiterIn1))!=NULL);

					nAll--;
					m_ArrDrawWParam[nItem]+=nAll*0x10000;
					POINT *lpo=new POINT [nAll*2];

					m_ArrDrawLParam[nItem]=(LPARAM)lpo;
					char *pos3=pos;
					pos3--;
					POINT *lpoCnt=&lpo[nAll];
					do	
					{
						pos2=pos3++;
						lpoCnt->x=0;
						char *posNULL=strchr(pos3,';');
						if (posNULL!=NULL) *posNULL=0;
						do	
						{
							lpo->x=lpo->y=0;
							m_LastScanf=sscanf(++pos2,"%d,%d",&lpo->x,&lpo->y);
							lpoCnt->x++;
							lpo++;
						}
						while((pos2=strchr(pos2,GPC.DelimiterIn1))!=NULL);
						lpoCnt++;
						if (posNULL!=NULL) *posNULL=';';
					}
					while((pos3=strchr(pos3,';'))!=NULL);
				}
				break;
			case DUT_POLYPOLYP:
			case DUT_PPOLYGONP:
				{
					char *pos2=pos;
					int nAll=0;
					do		nAll++;
					while((pos2=strchr(++pos2,';'))!=NULL);
					pos2=pos;

					m_ArrDrawWParam[nItem]=nAll;

					do		nAll++;
					while((pos2=strchr(++pos2,GPC.DelimiterIn1))!=NULL);

					nAll--;
					m_ArrDrawWParam[nItem]+=nAll*0x10000;
					POINT *lpo=new POINT [nAll*2];

					m_ArrDrawLParam[nItem]=(LPARAM)lpo;
					char *pos3=pos;
					pos3--;
					lpo+=m_ArrDrawLParam[nItem];
					POINT *lpoCnt=lpo;
					do	
					{
						pos2=pos3++;
						char *posNULL=strchr(pos3,';');
						if (posNULL!=NULL) *posNULL=0;
						do	
						{
							lpo->x=lpo->y=0;
							lpo->y=atoi(++pos2);
							lpoCnt->x++;
							lpo++;
						}
						while((pos2=strchr(pos2,GPC.DelimiterIn1))!=NULL);
						lpoCnt++;
						if (posNULL!=NULL) *posNULL=';';
					}
					while((pos3=strchr(pos3,';'))!=NULL);
				}
				break;
			case DUT_FILLRECT: 
			case DUT_FRAMERECT: 
			case DUT_INVERTRECT: 
				{
					PDRAWITEMDATA did=new DRAWITEMDATA;
					InitDRAWITEMDATA(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d",
						&did->re1.left,&did->re1.top,&did->re1.right,&did->re1.bottom,
						&m_ArrDrawWParam[nItem]
						);
				}
				break;
			case DUT_FILLRECTR: 
			case DUT_FRAMERECTR: 
			case DUT_INVERTRECTR: 
				m_LastScanf=sscanf(pos,"%d,%d",&m_ArrDrawLParam[nItem],&m_ArrDrawWParam[nItem]);
				break;
			case DUT_ICON: 
				{
					int x=0,y=0,nIcon=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d",&x,&y,&nIcon);
					m_ArrDrawWParam[nItem]=MAKEWPARAM(x,y);
					m_ArrDrawLParam[nItem]=nIcon; 
				}
				break;
			case DUT_ICONP: 
				m_LastScanf=sscanf(pos,"%d,%d",&m_ArrDrawWParam[nItem],&m_ArrDrawLParam[nItem]);
				break;
			case DUT_FILLSRECT: 
				{
					PDRAWITEMDATA did=new DRAWITEMDATA;
					InitDRAWITEMDATA(did);
					int R=0,G=0,B=0;
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d,%d,%d",
						&did->re1.left,&did->re1.top,&did->re1.right,&did->re1.bottom,
						&R,&G,&B
						);
					did->clr1=RGB(R,G,B);
				}
				break;
			case DUT_FILLSRECTR: 
				m_LastScanf=sscanf(pos,"%d,%d",&m_ArrDrawWParam[nItem],&m_ArrDrawLParam[nItem]);
				break;
			case DUT_3DRECT: 
				{
					PDRAWITEMDATA did=new DRAWITEMDATA;
					InitDRAWITEMDATA(did);
					int R=0,G=0,B=0,R2=0,G2=0,B2=0;
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
						&did->re1.left,&did->re1.top,&did->re1.right,&did->re1.bottom,
						&R,&G,&B,&R2,&G2,&B2
						);
					did->clr1=RGB(R,G,B);
					did->clr2=RGB(R2,G2,B2);
				}
				break;
			case DUT_3DRECTR:
				{
					PDRAWITEMDATANUM did=new DRAWITEMDATANUM;
					InitDRAWITEMDATANUM(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					m_LastScanf=sscanf(pos,"%d,%d,%d",&did->i1,&did->i2,&did->i3);
				}
				break;
			case DUT_EDGE:
			case DUT_EDGER:
				{
					const char *nm[15]={
						"BUMP","ETCHED","RAISED","SUNKEN","LEFT",
						"TOP","RIGHT","BOTTOM","RECT","DIAGONAL",
						"MIDDLE","SOFT","ADJUST","FLAT","MONO",
						};
					const UINT  uia[15]={
						EDGE_BUMP,EDGE_ETCHED,EDGE_RAISED,EDGE_SUNKEN,BF_LEFT,
						BF_TOP,BF_RIGHT,BF_BOTTOM,BF_RECT,BF_DIAGONAL,
						BF_MIDDLE,BF_SOFT,BF_ADJUST,BF_FLAT,BF_MONO,
						};

					UINT nEdge=0,nFlags=0;

					int i;
					for(i=0;i<15;i++)
						if (strstr(pos,nm[i])!=NULL)
							if (i<4)	nEdge|=uia[i];
							else		nFlags|=uia[i];

					CRect re(0,0,0,0);
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&re.left,&re.top,&re.right,&re.bottom);
					if (uArrUnitType[ui]==DUT_EDGE )
					{
						PDRAWITEMDATA did=new DRAWITEMDATA;
						InitDRAWITEMDATA(did);
						m_ArrDrawLParam[nItem]=(LPARAM)did;
						did->re1=re;
						did->clr1=nEdge;
						did->clr2=nFlags;
					}
					else
					{
						PDRAWITEMDATANUM did=new DRAWITEMDATANUM;
						InitDRAWITEMDATANUM(did);
						m_ArrDrawLParam[nItem]=(LPARAM)did;
						did->i1=re.left;
						did->i2=nEdge;
						did->i3=nFlags;
					}
				}
				break;
			case DUT_FRAMECTRL:
				{
					PDRAWITEMDATA did=new DRAWITEMDATA;
					InitDRAWITEMDATA(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d,%d",
						&did->re1.left,&did->re1.top,&did->re1.right,&did->re1.bottom,
						&did->clr1,&did->clr2
						);
				}
				break;
			case DUT_FRAMECTRLR:
				{
					PDRAWITEMDATANUM did=new DRAWITEMDATANUM;
					InitDRAWITEMDATANUM(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					m_LastScanf=sscanf(pos,"%d,%d,%d",&did->i1,&did->i2,&did->i3);
				}
				break;
			case DUT_STATETEXT:
			case DUT_STATETEXTR:
			case DUT_STATEICON:
			case DUT_STATEICONR:
				{
					UINT flg=0;

					const char *nm[7]={"NORMAL","UNION","DISABLED","RIGHT","MONO","HIDEPREFIX","PREFIXONLY",};
					const UINT uinm[8]={DSS_NORMAL,DSS_UNION,DSS_DISABLED,DSS_RIGHT,DSS_MONO,DSS_HIDEPREFIX,DSS_PREFIXONLY,DSS_NORMAL,}; 

					int i;
					for(i=0;i<7 && strstr(pos,nm[i])==NULL;i++);
					flg=uinm[i];

					switch(uArrUnitType[ui])
					{
					case DUT_STATETEXT:
					case DUT_STATETEXTR:
						{
							PDRAWITEMDATATEXT did=new DRAWITEMDATATEXT;
							InitDRAWITEMDATATEXT(did);
							m_ArrDrawLParam[nItem]=(LPARAM)did;
							char *postxt=strchr(pos,';');
							if (postxt++==NULL) postxt="";
							did->text=postxt;
							if (strstr(pos,"PREFIX")!=NULL) did->flags2=0x1;
							did->flags=flg;
							
							switch(uArrUnitType[ui])
							{
							case DUT_STATETEXT:
								m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d",&did->re.left,&did->re.top,&did->re.right,&did->re.bottom,&did->nBrush);
								break;
							case DUT_STATETEXTR:
								m_LastScanf=sscanf(pos,"%d,%d",&did->re.left,&did->nBrush);
								break;
							}
						}
						break;
					case DUT_STATEICON:
					case DUT_STATEICONR:
						{
							PDRAWITEMDATA did=new DRAWITEMDATA;
							InitDRAWITEMDATA(did);
							m_ArrDrawLParam[nItem]=(LPARAM)did;
							did->clr1=flg;
							
							switch(uArrUnitType[ui])
							{
							case DUT_STATEICON:
								m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d,%d",&did->re1.left,&did->re1.top,&did->re1.right,&did->re1.bottom,&did->re2.left,&did->clr2);
								break;
							case DUT_STATEICONR:
								m_LastScanf=sscanf(pos,"%d,%d,%d",&did->re1.left,&did->re2.left,&did->clr2);
								break; // nRect,nIcon,nBrush
							}
						}
						break;
					}
					break;
				}
			case DUT_CHORD:
			case DUT_CHORDRP:
			case DUT_PIE:
			case DUT_PIERP:
				{
					PDRAWITEMDATA did=new DRAWITEMDATA;
					InitDRAWITEMDATA(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					
					switch(uArrUnitType[ui])
					{
					case DUT_CHORD:
					case DUT_PIE:
						m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d,%d,%d,%d",
							&did->re1.left,&did->re1.top,&did->re1.right,&did->re1.bottom,
							&did->po1.x,&did->po1.y,&did->po2.x,&did->po2.y
							);
						break;
					case DUT_CHORDRP:
					case DUT_PIERP:
						m_LastScanf=sscanf(pos,"%d,%d,%d",&did->re1.left,&did->po1.x,&did->po2.x);
						break; // nRect,nIcon,nBrush
					}
				}
				break;
			case DUT_FOCUSRECT:
			case DUT_ELLIPSE:
			case DUT_RECT:
				{
					LPRECT lpr=new RECT;
					lpr->bottom=lpr->top=lpr->left=lpr->right=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&lpr->left,&lpr->top,&lpr->right,&lpr->bottom);
					m_ArrDrawLParam[nItem]=(LPARAM)lpr;
				}
				break;
			case DUT_ELLIPSER:
			case DUT_FOCUSRECTR:
			case DUT_RECTR:
				m_ArrDrawLParam[nItem]=atoi(pos);
				break;
			case DUT_ROUNDRECT:
			case DUT_ROUNDRECTR:
				{
					PDRAWITEMDATA did=new DRAWITEMDATA;
					InitDRAWITEMDATA(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					
					switch(uArrUnitType[ui])
					{
					case DUT_ROUNDRECT:
						m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d,%d",
							&did->re1.left,&did->re1.top,&did->re1.right,&did->re1.bottom,
							&did->po1.x,&did->po1.y
							);
						break;
					case DUT_ROUNDRECTR:
						m_LastScanf=sscanf(pos,"%d,%d",&did->re1.left,&did->po1.x);
						break; // nRect,nPoint,
					}
				}
				break;
			case DUT_PIXEL:
			case DUT_FLOODFILL:
			case DUT_EXTFLOODFILL:
				{
					PDRAWITEMDATA did=new DRAWITEMDATA;
					InitDRAWITEMDATA(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					int R=0,G=0,B=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d",&did->po1.x,&did->po1.y,&R,&G,&B);
					did->clr1=RGB(R,G,B);
				}
				break;
			case DUT_PIXELPC:
			case DUT_FLOODFILLPC:
			case DUT_EXTFLOODFILLPC:
			case DUT_TEXTOUTPT:
				{
					int nPo=0,nClr=0;
					m_LastScanf=sscanf(pos,"%d,%d",&nPo,&nClr);
					m_ArrDrawWParam[nItem]=MAKEWPARAM(nPo,nClr);
				}
				break;
			case DUT_TEXTOUT:
				{
					PDRAWITEMDATATEXT did=new DRAWITEMDATATEXT;
					InitDRAWITEMDATATEXT(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					char *postxt=strchr(pos,',');
					if (postxt!=NULL) postxt=strchr(++postxt,',');
					if (postxt++==NULL) postxt="";
					did->text=postxt;
					m_LastScanf=sscanf(pos,"%d,%d",&did->po.x,&did->po.y);
				}
				break;
			case DUT_EXTTEXTOUT://x,y,left,top,right,bottom,flags;arrWidths;TEXT
			case DUT_EXTTEXTOUTP://nPoint,nRect,nText,flags;arrWidths
			case DUT_TABTEXTOUT://x,y,nTabPositions,nTabOrigin;arrWidths;TEXT
			case DUT_TABTEXTOUTP://nPoint,nText,nTabPositions,nTabOrigin;arrWidths
				{
					PDRAWITEMDATATEXT did=new DRAWITEMDATATEXT;
					InitDRAWITEMDATATEXT(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					switch(uArrUnitType[ui])
					{
					case DUT_EXTTEXTOUT:
						m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d,%d,%d",
							&did->po.x,&did->po.y,
							&did->re.left,&did->re.top,&did->re.right,&did->re.bottom,
							&did->flags
							);
						if (did->flags==0) did->flags=TranslateETO(pos);
						break;
					case DUT_EXTTEXTOUTP:
						m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&did->po.x,&did->re.left,&did->re.top,&did->flags);
						if (did->flags==0) did->flags=TranslateETO(pos);
						break;
					case DUT_TABTEXTOUT:
					case DUT_TABTEXTOUTP:
						m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&did->po.x,&did->po.y,&did->re.left,&did->re.top);
						break;
					}

					char *posArr=strchr(pos,';');
					char *postxt=posArr;
					if (posArr++==NULL) posArr="";
					postxt=strchr(posArr,';');
					if (postxt++==NULL) postxt="";
					did->text=postxt;
					if (*posArr!=0 && *posArr!=';')
					{
						int nArr=did->text.GetLength();
						if (nArr>0)
						{
							LPINT lpi=new INT [nArr+5];
							m_ArrDrawWParam[nItem]=(WPARAM)lpi;
							int i=0;
							while(posArr!=NULL && *posArr!=0 && *posArr!=';')
							{
								lpi[i++]=atoi(posArr);
								while(*posArr!=GPC.DelimiterIn1 && *posArr!=',' && *posArr!=';' && *posArr!=0) posArr++;
								if (*posArr==GPC.DelimiterIn1 || *posArr==',') posArr++;
							}
						}
					}
				}
				break; 
			case DUT_TEXT://left,top,right,bottom,flags;TEXT
			case DUT_TEXTR://nRect,nText,flags
				{
					PDRAWITEMDATATEXT did=new DRAWITEMDATATEXT;
					InitDRAWITEMDATATEXT(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					switch(uArrUnitType[ui])
					{
					case DUT_TEXT:
						m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d",
							&did->re.left,&did->re.top,&did->re.right,&did->re.bottom,
							&did->flags
							);
						break;
					case DUT_TEXTR:
						m_LastScanf=sscanf(pos,"%d,%d,%d",&did->po.x,&did->po.y,&did->flags);
						break;
					}

					if (did->flags==0) did->flags=TranslateDT(pos);
					char *postxt=strchr(pos,';');
					if (postxt++==NULL) postxt="";
					did->text=postxt;
				}
				break; 
			case DUT_TEXTALIGN:
				{
					const char *nm[9]={
						"TA_NOUPDATECP","TA_UPDATECP","TA_LEFT","TA_RIGHT","TA_CENTER",
						"TA_TOP","TA_BOTTOM","TA_BASELINE","TA_RTLREADING",
						};
					const UINT uin[9]={
						TA_NOUPDATECP,TA_UPDATECP,TA_LEFT,TA_RIGHT,TA_CENTER,
						TA_TOP,TA_BOTTOM,TA_BASELINE,TA_RTLREADING,
						};

					char *buff=new char [strlen(pos)+10];
					strcpy(buff,iStr);
					_strupr(pos);

					int i;
					for(i=0;i<9;i++)
						if (strstr(buff,nm[i])!=NULL)
							m_ArrDrawWParam[nItem]|=uin[i];
					delete[] buff;
				}
				break; 
			case DUT_TEXTJUST:
				m_LastScanf=sscanf(pos,"%d,%d",m_ArrDrawWParam+nItem,m_ArrDrawLParam+nItem);
				break; 
			case DUT_CHAREXTRA:
			case DUT_MAPPERFLAGS:
			case DUT_ABORTPATH:	
			case DUT_BEGINPATH:	
			case DUT_CLOSEFIGURE:
			case DUT_ENDPATH:	
			case DUT_FILLPATH:	
			case DUT_FLATTENPATH:		
				break;
			case DUT_SELECTCLIPPATH:
				{
					int Type=-1;
					m_LastScanf=sscanf(pos,"%d",&Type);
					if (Type<0)
					{
						Type=RGN_AND;
						if (strstr(pos,"_AND")!=NULL) Type=RGN_AND;
						else
							if (strstr(pos,"_DIFF")!=NULL) Type=RGN_DIFF;
							else
								if (strstr(pos,"_OR")!=NULL) Type=RGN_OR;
								else
									if (strstr(pos,"_XOR")!=NULL) Type=RGN_XOR;
					}
					m_ArrDrawWParam[nItem]=Type;
				}
				break; 
			case DUT_SETMITERLIMIT:	
				{
					m_ArrDrawLParam[nItem]=(LPARAM)new float;
					*((float *)m_ArrDrawLParam[nItem])=(float)atof(pos);
				}
				break;
			case DUT_STROKEFILLPATH:
			case DUT_STROKEPATH:	
			case DUT_WIDENPATH:		
				break;
			case DUT_OFFSET:
				m_LastScanf=sscanf(pos,"%d,%d",m_ArrDrawWParam+nItem,m_ArrDrawLParam+nItem);
				break;
			case DUT_OFFSETP:
				m_ArrDrawWParam[nItem]=atoi(pos);
				break;
			case DUT_ARROW:
			case DUT_ARROWTO:
				{//x,y,Width,Length,type,dPart
					PDRAWITEMDATANUM did=new DRAWITEMDATANUM;
					InitDRAWITEMDATANUM(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d,%lg",&did->i1,&did->i2,&did->i3,&did->i4,&did->id4,&did->d1);
				}
				break;
			case DUT_ARROWP:
			case DUT_ARROWPTO:
				{//nPoint,Width,Length,type,dPart
					PDRAWITEMDATANUM did=new DRAWITEMDATANUM;
					InitDRAWITEMDATANUM(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%lg",&did->i1,&did->i3,&did->i4,&did->id4,&did->d1);
				}
				break;
			case DUT_CLONE:
			case DUT_CLONETO:
			case DUT_CLONEC:
			case DUT_CLONECTO:
				{//nItem,nTime,dx,dy,dxMulty,dyMulty
					m_ArrDrawLParam[nItem]=(LPARAM)new DRAWITEMDATAPRG;
					InitDRAWITEMDATAPRG((PDRAWITEMDATAPRG)m_ArrDrawLParam[nItem]);
					PDRAWITEMDATANUM did=new DRAWITEMDATANUM;
					InitDRAWITEMDATANUM(did);
					((PDRAWITEMDATAPRG)m_ArrDrawLParam[nItem])->DIDNum=did;
					did->d1=did->d2=did->d3=did->d4=1;
					m_LastScanf=sscanf(pos,"%d,%d,%lg,%lg,%lg,%lg",&did->i1,&did->i2,&did->d1,&did->d2,&did->d3,&did->d4);
				}
				break;
			case DUT_GOTO://Adress
			case DUT_GOSUB://Adress
				switch(*pos)
				{
				case '-': // offset
				case '+':
					m_ArrDrawWParam[nItem]=0x1;
					m_ArrDrawLParam[nItem]=atoi(pos);
					break;
				case '&': // direct
					m_ArrDrawWParam[nItem]=0x2;
					m_ArrDrawLParam[nItem]=atoi(pos+1);
					break;
				case '@': // offset
					m_ArrDrawWParam[nItem]=0x4;
					m_ArrDrawLParam[nItem]=atoi(pos+1);
					break;
				default:// direct
					m_ArrDrawWParam[nItem]=0x0;
					m_ArrDrawLParam[nItem]=atoi(pos);
					break;
				}
				break;
			case DUT_RETURN: break;
			case DUT_SETINT:
				{
					char *str=new char [strlen(pos)+20];
					sprintf(str,"SetInt %s",pos);
					DoMethod(str,NULL);
					if ((UINT)atoi(pos)<m_nIntArray)
					{
						m_ArrDrawWParam[nItem]=atoi(pos);
						m_ArrDrawLParam[nItem]=m_IntArr[m_ArrDrawWParam[nItem]];
					}
					delete[] str;
				}
				break;
			case DUT_SETDOUBLE:
				{
					char *str=new char [strlen(pos)+20];
					sprintf(str,"SetDouble %s",pos);
					DoMethod(str,NULL);
					if ((UINT)atoi(pos)<m_nDoubleArray)
					{
						m_ArrDrawWParam[nItem]=atoi(pos);
						m_ArrDrawLParam[nItem]=(LPARAM) new double;
						*((double *)m_ArrDrawLParam[nItem])=m_DoubleArr[m_ArrDrawWParam[nItem]];
					}
					delete[] str;
				}
				break;
			case DUT_SETPOINT:
				{
					char *str=new char [strlen(pos)+20];
					sprintf(str,"SetPoint %s",pos);
					DoMethod(str,NULL);
					m_ArrDrawWParam[nItem]=atoi(pos);
					m_ArrDrawLParam[nItem]=(LPARAM) new CPoint(m_PointArr[m_ArrDrawWParam[nItem]]);
					delete[] str;
				}
				break;
			case DUT_SETRECT:
				{
					char *str=new char [strlen(pos)+20];
					sprintf(str,"SetRect %s",pos);
					DoMethod(str,NULL);
					m_ArrDrawWParam[nItem]=atoi(pos);
					m_ArrDrawLParam[nItem]=(LPARAM) new CRect(m_RectArr[m_ArrDrawWParam[nItem]]);
					delete[] str;
				}
				break;
			case DUT_SETCOLOR:
				{
					char *str=new char [strlen(pos)+20];
					sprintf(str,"SetColor %s",pos);
					DoMethod(str,NULL);
					if ((UINT)atoi(pos)<m_nRGBArray)
					{
						m_ArrDrawWParam[nItem]=atoi(pos);
						m_ArrDrawLParam[nItem]=m_RGBArr[m_ArrDrawWParam[nItem]];
					}
					delete[] str;
				}
				break;
			case DUT_SETREGION:
				{
					char *str=new char [strlen(pos)+20];
					sprintf(str,"SetRegion %s",pos);
					DoMethod(str,NULL);
					if ((UINT)atoi(pos)<m_nRgnArray)
						m_ArrDrawWParam[nItem]=atoi(pos);
					delete[] str;
				}
				break;
			case DUT_COPYREGION:
			case DUT_OFFSETPREGION:
				m_LastScanf=sscanf(pos,"%d,%d",m_ArrDrawWParam+nItem,m_ArrDrawLParam+nItem);
				break;
			case DUT_REGIONFROMPATH:
				m_ArrDrawWParam[nItem]=atoi(pos);
				break;
			case DUT_OFFSETREGION:
				{//nRgn,dx,dy
					PDRAWITEMDATANUM did=new DRAWITEMDATANUM;
					InitDRAWITEMDATANUM(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					m_LastScanf=sscanf(pos,"%d,%d,%d",&did->i1,&did->i2,&did->i3);
				}
				break;
			case DUT_COMBINEREGION:
				{//nRgn,nRgn1,nRgn2,Style
					PDRAWITEMDATANUM did=new DRAWITEMDATANUM;
					InitDRAWITEMDATANUM(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&did->i1,&did->i2,&did->i3,&did->i4);
					_strupr(pos);
					if (strstr(pos,"_AND")!=NULL) did->i4=RGN_AND;
					else
						if (strstr(pos,"_COPY")!=NULL) did->i4=RGN_COPY;
						else
							if (strstr(pos,"_DIFF")!=NULL) did->i4=RGN_DIFF;
							else
								if (strstr(pos,"_OR")!=NULL) did->i4=RGN_OR;
								else
									if (strstr(pos,"_XOR")!=NULL) did->i4=RGN_XOR;
				}
				break;
			case DUT_FILLRGN://nRgn,nBrush
				m_LastScanf=sscanf(pos,"%d,%d",m_ArrDrawWParam+nItem,m_ArrDrawLParam+nItem);
				break;
			case DUT_FRAMERGN:
				{//nRgn,nBrush,xWidth,yWidth
					PDRAWITEMDATANUM did=new DRAWITEMDATANUM;
					InitDRAWITEMDATANUM(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&did->i1,&did->i2,&did->i3,&did->i4);
				}
				break;
			case DUT_INVERTRGN://nRgn
			case DUT_PAINTRGN:
				m_ArrDrawWParam[nItem]=atoi(pos);
				break;
			case DUT_BOUNDSRECT://left,top,right,bottom,Flags
			case DUT_BOUNDSRECTR://nRect,Flags
				{
					if (strstr(pos,"RESET")!=NULL)				m_ArrDrawWParam[nItem]=DCB_RESET;
					else
						if (strstr(pos,"ACCUMULATE")!=NULL)		m_ArrDrawWParam[nItem]=DCB_ACCUMULATE;
						else
							if (strstr(pos,"ENABLE")!=NULL)		m_ArrDrawWParam[nItem]=DCB_ENABLE;
							else
								if (strstr(pos,"DISABLE")!=NULL) m_ArrDrawWParam[nItem]=DCB_DISABLE;
								else							m_ArrDrawWParam[nItem]=DCB_RESET;

					switch(uArrUnitType[ui])
					{
					case DUT_BOUNDSRECT:
						{
							CRect *re=new CRect(0,0,0,0);
							m_ArrDrawLParam[nItem]=(LPARAM)re;
							m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&re->left,&re->top,&re->right,&re->bottom);
						}
						break;
					case DUT_BOUNDSRECTR:
						m_ArrDrawLParam[nItem]=atoi(pos);
						break;
					}
				}
				break;
			case DUT_GETCLIPBOX:
			case DUT_GETBOUNDSR:
				m_ArrDrawWParam[nItem]=atoi(pos);
				break;
			case DUT_SELCLIPREGION://nRgn,Style
				m_LastScanf=sscanf(pos,"%d,%d",m_ArrDrawWParam+nItem,m_ArrDrawLParam+nItem);
				_strupr(pos);
				if (strstr(pos,"_AND")!=NULL) m_ArrDrawLParam[nItem]=RGN_AND;
				else
					if (strstr(pos,"_COPY")!=NULL) m_ArrDrawLParam[nItem]=RGN_COPY;
					else
						if (strstr(pos,"_DIFF")!=NULL) m_ArrDrawLParam[nItem]=RGN_DIFF;
						else
							if (strstr(pos,"_OR")!=NULL) m_ArrDrawLParam[nItem]=RGN_OR;
							else
								if (strstr(pos,"_XOR")!=NULL) m_ArrDrawLParam[nItem]=RGN_XOR;
				break;
			case DUT_EXCLRECT:
			case DUT_INCLRECT:
				{
					CRect *re=new CRect(0,0,0,0);
					m_ArrDrawLParam[nItem]=(LPARAM)re;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&re->left,&re->top,&re->right,&re->bottom);
				}
				break;
			case DUT_INCLRECTR:
			case DUT_EXCLRECTR:
			case DUT_EXCLUPDRGN:
				m_ArrDrawLParam[nItem]=atoi(pos);
				break;
			case DUT_OFFSETCREGION://dx,dy
				m_LastScanf=sscanf(pos,"%d,%d",m_ArrDrawWParam+nItem,m_ArrDrawLParam+nItem);
				break;
			case DUT_OFFSETPCREGION:
				m_ArrDrawLParam[nItem]=atoi(pos);
				break;
			case DUT_IFGOTO:
			case DUT_IFGOSUB:
				{
					PDRAWITEMDATANUM did=new DRAWITEMDATANUM;
					InitDRAWITEMDATANUM(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					_strupr(pos);
					if (strchr(pos,'=')!=NULL) did->id3|=0x1;
					if (strchr(pos,'<')!=NULL) did->id3|=0x2;
					if (strchr(pos,'>')!=NULL) did->id3|=0x4;
					if (strchr(pos,'#')!=NULL) did->id3|=0x6;
					char *ptmp=pos;
					while(*ptmp!=0 && *ptmp!='D' && *ptmp!='I' && *ptmp!='C' && *ptmp!='T') ptmp++;
					if (*ptmp!=0) 
						switch(*(ptmp++))
						{
						case 'D':	did->i1|=0x100; break;
						case 'I':	did->i1|=0x200; break;
						case 'C':	did->i1|=0x400; break;
						case 'T':	did->i1|=0x800; break;
						}
					did->d1=atof(ptmp);

					while(*ptmp!=0 && *ptmp!='D' && *ptmp!='I' && *ptmp!='C' && *ptmp!='T') ptmp++;
					if (*ptmp!=0) 
						switch(*(ptmp++))
						{
						case 'D':	did->i2|=0x100; break;
						case 'I':	did->i2|=0x200; break;
						case 'C':	did->i2|=0x400; break;
						case 'T':	did->i2|=0x800; break;
						}
					did->d2=atof(ptmp);

					while(*ptmp!=0 && *ptmp!=',' && *ptmp!=';' && *ptmp!=GPC.DelimiterIn1) ptmp++;
					if (*ptmp!=0) 
						switch(*(++ptmp))
						{
						case '-': // offset
						case '+':
							did->id4=0x1;
							did->i4=atoi(ptmp);
							break;
						case '&': // direct
							did->id4=0x2;
							did->i4=atoi(ptmp+1);
							break;
						case '@': // offset
							did->id4=0x4;
							did->i4=atoi(ptmp+1);
							break;
						default:// direct
							did->id4=0x0;
							did->i4=atoi(ptmp);
							break;
						}

				}
				break;
			case DUT_ARITHMETIC: 
				{
					PDRAWITEMDATANUM did=new DRAWITEMDATANUM;
					InitDRAWITEMDATANUM(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					_strupr(pos);
					char t1=0,t2=0,op=0;
					m_LastScanf=sscanf(pos,"%c%lg%c%c%lg",&t1,&did->d1,&op,&t2,&did->d2);
					switch(op)
					{
					case '+':	did->i3|=0x0001;	break;
					case '-':	did->i3|=0x0002;	break;
					case '*':	did->i3|=0x0004;	break;
					case '/':	did->i3|=0x0008;	break;
					case '=':	did->i3|=0x0010;	break;
					case '|':	did->i3|=0x0020;	break;
					case '&':	did->i3|=0x0040;	break;
					case '%':	did->i3|=0x0080;	break;
					case '!':	did->i3|=0x0100;	break;
					case '~':	did->i3|=0x0200;	break;
					}
					switch(t1)
					{
					case 'D': did->i1|=0x100;	break;
					case 'I': did->i1|=0x200;	break;
					case 'T': did->i1|=0x800;	break;
					}
					switch(t2)
					{
					case 'D': did->i2|=0x100;	break;
					case 'I': did->i2|=0x200;	break;
					case 'C': did->i2|=0x400;	break;
					case 'T': did->i2|=0x800;	break;
					}
				}
				break;
			case DUT_MATH: 
				{
					PDRAWITEMDATAMATH did=new DRAWITEMDATAMATH;
					InitDRAWITEMDATAMATH(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					_strupr(pos);
					char *posFn=strchr(pos,'=');
					if (posFn!=NULL)
					{
						*(posFn++)=0;
						char *posArg=strchr(posFn,'(');
						if (posArg!=NULL && *pos!=0)
						{
							*(posArg++)=0;
							int nFn=0;
							for(nFn=0;nFn<uNArrFn && strcmp(posFn,CODContextItem::ccAMathFunction[nFn])!=0;nFn++);
							if (nFn<uNArrFn && nFn>0)
							{
								char *tmp=pos;
								did->iFunction=nFn;
								for(did->nResults=0,tmp=pos;*tmp!=0 && did->nResults<16;did->nResults++)
								{
									switch(*tmp)
									{
									case 'D':
										did->iResultsType[did->nResults]=0x100;
										did->iResultsArr[did->nResults]=atoi(++tmp);
										break;
									case 'I':
										did->iResultsType[did->nResults]=0x200;
										did->iResultsArr[did->nResults]=atoi(++tmp);
										break;
									case 'T':
										did->iResultsType[did->nResults]=0x800;
										did->iResultsArr[did->nResults]=atoi(++tmp);
										break;
									}
									while (*tmp!=0 && *tmp!=',') tmp++;
									if (*tmp==',') tmp++;
								}

								for(did->nArg=0,tmp=posArg;*tmp!=0 && did->nArg<16;did->nArg++)
								{
									switch(*tmp)
									{
									case 'D':
										did->iArgType[did->nArg]=0x100;
										did->iArgAdress[did->nArg]=atoi(++tmp);
										break;
									case 'I': 
										did->iArgType[did->nArg]=0x200;	
										did->iArgAdress[did->nArg]=atoi(++tmp);
										break;
									case 'C': 
										did->iArgType[did->nArg]=0x400;	
										did->dConst[did->nArg]=atof(++tmp);
										break;
									case 'T': 
										did->iArgType[did->nArg]=0x800;	
										did->iArgAdress[did->nArg]=atoi(++tmp);
										break;
									}
									while (*tmp!=0 && *tmp!=',') tmp++;
									if (*tmp==',') tmp++;
								}
							}
						}
					}
				}
				break;
			case DUT_SETRGB: //  TNNN,TNNN,TNNN
				{
					PDRAWITEMDATANUM did=new DRAWITEMDATANUM;
					InitDRAWITEMDATANUM(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					_strupr(pos);
					char *ptmp=pos;
					did->i4=atoi(ptmp);
//					while(*ptmp!=0 && *ptmp!=',' && *ptmp!=';' && *ptmp!=GPC.DelimiterIn1) ptmp++;

					while(*ptmp!=0 && *ptmp!='D' && *ptmp!='I' && *ptmp!='C' && *ptmp!='T') ptmp++;
					if (*ptmp!=0) 
					{
						if (*ptmp=='D') did->i1|=0x100;
						else
						if (*ptmp=='I') did->i1|=0x200;
						else
						if (*ptmp=='C') did->i1|=0x400;
						else
						if (*ptmp=='T') did->i1|=0x800;
						ptmp++;
					}
					did->id1=atoi(ptmp);
					while(*ptmp!=0 && *ptmp!='D' && *ptmp!='I' && *ptmp!='C' && *ptmp!='T') ptmp++;
					if (*ptmp!=0) 
					{
						if (*ptmp=='D') did->i2|=0x100;
						else
						if (*ptmp=='I') did->i2|=0x200;
						else
						if (*ptmp=='C') did->i2|=0x400;
						else
						if (*ptmp=='T') did->i2|=0x800;
						ptmp++;
					}
					did->id2=atoi(ptmp);
					while(*ptmp!=0 && *ptmp!='D' && *ptmp!='I' && *ptmp!='C' && *ptmp!='T') ptmp++;
					if (*ptmp!=0) 
					{
						if (*ptmp=='D') did->i3|=0x100;
						else
						if (*ptmp=='I') did->i3|=0x200;
						else
						if (*ptmp=='C') did->i3|=0x400;
						else
						if (*ptmp=='T') did->i3|=0x800;
						ptmp++;
					}
					did->id3=atoi(ptmp);
				}
				break;
			case DUT_SETPENCOLOR: //nPen,nColor
			case DUT_PENWIDTH: //nPen,Width
				m_LastScanf=sscanf(pos,"%d,%d",m_ArrDrawWParam+nItem,m_ArrDrawLParam+nItem);
				break;
			case DUT_GETWINDOWRECT: //nRect,nObject
			case DUT_GETCLIENTRECT: //nRect,nObject
				m_ArrDrawWParam[nItem]=-1;
				m_ArrDrawLParam[nItem]=-1;
				m_LastScanf=sscanf(pos,"%d,%d",m_ArrDrawWParam+nItem,m_ArrDrawLParam+nItem);
				break;
			case DUT_MOVEWINDOW: //nObject,nRect
				m_ArrDrawWParam[nItem]=-1;
				m_ArrDrawLParam[nItem]=-1;
				m_LastScanf=sscanf(pos,"%d,%d",m_ArrDrawLParam+nItem,m_ArrDrawWParam+nItem);
				break;
			case DUT_RECTOFFSETP:	//nRect,nPoint
			case DUT_RECTOFFSETPM:	//nRect,nPoint
			case DUT_RECTCENTER:	//nRect,nPoint
			case DUT_RECTOFFSETR:	//nRect,nRectOff
			case DUT_RECTOFFSETRM:	//nRect,nRectOff
			case DUT_RECTSUBSTR:	//nRect,nRectSub
			case DUT_RECTINTERS:	//nRect,nRectInter
			case DUT_RECTUNION:		//nRect,nRectUnion
				m_LastScanf=sscanf(pos,"%d,%d",m_ArrDrawWParam+nItem,m_ArrDrawLParam+nItem);
				break;
			case DUT_RECTHEIGHT:	//nRect,Res
			case DUT_RECTWIDTH:		//nRect,Res
			case DUT_RECTISNULL:	//nRect,Res
			case DUT_RECTISEMPTY:	//nRect,Res
				{
					char c=0;
					int nRect=0,Res=0;
					m_LastScanf=sscanf(pos,"%d,%c%d",&nRect,&c,&Res);
					m_ArrDrawWParam[nItem]=nRect;
					c&=0xDF;
					switch(c)
					{
					case 'I':	m_ArrDrawLParam[nItem]=0x2000000;	break;
					case 'D':	m_ArrDrawLParam[nItem]=0x1000000;	break;
					}
					m_ArrDrawLParam[nItem]+=(Res&0xFFFF);
				}
				break;
			case DUT_RECTPTIN:		//nRect,nPoint,Res
			case DUT_RECTEQUAL:		//nRect,nRect,Res
				{
					char c=0;
					int nRect=0,nPoint=0,Res=0;
					m_LastScanf=sscanf(pos,"%d,%d,%c%d",&nRect,&nPoint,&c,&Res);
					m_ArrDrawWParam[nItem]=(nRect&0xFFFF)+(nPoint<<16);
					c|=0x20;
					switch(c)
					{
					case 'I':	m_ArrDrawLParam[nItem]=0x2000000;	break;
					case 'D':	m_ArrDrawLParam[nItem]=0x1000000;	break;
					}
					m_ArrDrawLParam[nItem]+=(Res&0xFFFF);
				}
				break;

			case DUT_RECTINFLATE:	//nRect,dx,dy
			case DUT_RECTDEFLATE:	//nRect,dx,dy
			case DUT_RECTOFFSET:	//nRect,dx,dy
				{
					int nRect=0,dx=0,dy=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d",&nRect,&dx,&dy);
					m_ArrDrawWParam[nItem]=nRect;
					m_ArrDrawLParam[nItem]=(dx&0xFFFF)+(dy<<16);
				}
				break;
			case DUT_RECTNORMALIZE:	//nRect
					m_ArrDrawWParam[nItem]=atoi(pos);
				break;
			case DUT_SCRTOCL:	//nRect,nObject
			case DUT_CLTOSCR:	//nRect,nObject
				m_ArrDrawWParam[nItem]=-1;
				m_ArrDrawLParam[nItem]=-1;
				m_LastScanf=sscanf(pos,"%d,%d",m_ArrDrawWParam+nItem,m_ArrDrawLParam+nItem);
				break;
			case DUT_STRCATS:	//nStrDest,nStrSource
				m_ArrDrawWParam[nItem]=-1;
				m_ArrDrawLParam[nItem]=-1;
				m_LastScanf=sscanf(pos,"%d,%d",m_ArrDrawWParam+nItem,m_ArrDrawLParam+nItem);
				break;
			case DUT_STRCAT:	//nStrDest,TEXT
				{
					PDRAWITEMDATASTR did=new DRAWITEMDATASTR;
					InitDRAWITEMDATASTR(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					char *ptmp=pos;
					did->nDest=atoi(pos);
					while(*ptmp!=0 && *ptmp!=',' && *ptmp!=';' && *ptmp!=':') ptmp++;
					if (*ptmp!=0) ptmp++;
					did->text=ptmp;
				}
				break;
			case DUT_ITOSTR:	//nStrDest,nInt,STRFORMAT
			case DUT_DTOSTR:	//nStrDest,nDouble,STRFORMAT
			case DUT_TTOSTR:	//nStrDest,nDouble,STRFORMAT
				{
					PDRAWITEMDATASTR did=new DRAWITEMDATASTR;
					InitDRAWITEMDATASTR(did);
					m_ArrDrawLParam[nItem]=(LPARAM)did;
					char *ptmp=pos;
					did->nDest=atoi(ptmp);
					while(*ptmp!=0 && *ptmp!=',' && *ptmp!=';' && *ptmp!=':') ptmp++;
					if (*ptmp!=0) ptmp++;
					did->nSourse=atoi(ptmp);
					while(*ptmp!=0 && *ptmp!=',' && *ptmp!=';' && *ptmp!=':') ptmp++;
					if (*ptmp!=0) ptmp++;
					did->format=ptmp;
				}
				break;

				

			case DUT_NONE: break;
			default:	ret=FALSE;
				m_ArrDrawType[nItem]=DUT_NONE;
				break;
			}
		}
		else m_ArrDrawType[nItem]=DUT_NONE;
	}
	delete[] iStr;
	return ret;
}

void GPDrawWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	HBITMAP hOldBitmap;       // Handle to the old bitmap

	// Create a memory device context compatible with the device. 
	CRect re;
	dc.GetClipBox(&re);
	CDC DCMem;
	DCMem.CreateCompatibleDC (&dc);
	if (m_hDCBitmap==NULL)
	{
		CRect ClientRe;
		GetClientRect(&ClientRe);
		m_hDCBitmap=::CreateCompatibleBitmap (dc.m_hDC, ClientRe.Width(),ClientRe.Height());
//	   ::BitBlt (DCMem.m_hDC, re.left,re.top,re.Width(),re.Height(), dc.m_hDC , re.left,re.top, SRCCOPY);
	}

	// Select the new bitmap object into the memory device context. 
	hOldBitmap = (HBITMAP)DCMem.SelectObject (m_hDCBitmap);
	if (m_uRedrawFlag)
	{
		PaintToCDC(&DCMem);
		m_uRedrawFlag=0;
	}

   ::BitBlt (dc.m_hDC, re.left,re.top,re.Width(),re.Height(), DCMem.m_hDC, re.left,re.top, SRCCOPY);

	// Select the old bitmap back into the device context.
	DCMem.SelectObject (hOldBitmap);
}

void GPDrawWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void GPDrawWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void GPDrawWnd::PaintToCDC(CDC *pDC)
{
	CPoint LocOffset(0,0);
	int m_Stack[DU_NSTACK];
	UINT m_StackPos;
	for(m_StackPos=0;m_StackPos<DU_NSTACK;m_StackPos++) m_Stack[m_StackPos]=-1; 
	*m_Stack=100000;
	m_StackPos=0;
	int nOperations=0;

	CBrush *oldBrush=NULL;
	CPen *oldPen=NULL;
	CFont *oldFont=NULL;
	int oldBkMode=-123456;
	int oldPfMode=-123456;
	int oldROP2Mode=-123456;
	int oldMapMode=-123456;

//	if (m_bEraseBkg)
	{
		CRect re;
		GetClientRect(&re);
		if (referGPU[UnitId&0xFFFF]->m_brBkgnd!=NULL)
			pDC->FillRect(&re,referGPU[UnitId&0xFFFF]->m_brBkgnd);
		else pDC->FillSolidRect(&re,referGPU[UnitId&0xFFFF]->m_clrBkgnd);
	}
	
	int tmpint;
	UINT i;
	UINT NextJob=0xFFFFFFFF;
	for(i=0,nOperations=0;i<m_nDraw && nOperations<100000;i++,nOperations++)
	{
		switch(m_ArrDrawType[i])
		{
		case DUT_BKG: 
		case DUT_FRG:
			{
				COLORREF clr=0;
				if ((m_ArrDrawWParam[i]&0xFF000000)==0xFF000000)
				{
					UINT nARR=m_ArrDrawWParam[i]&0xFFFFFF;
					if (nARR<m_nRGBArray) clr=m_RGBArr[nARR];
				}
				else clr=m_ArrDrawWParam[i];
				if (m_ArrDrawType[i]==DUT_BKG)	pDC->SetBkColor(clr);
				else							pDC->SetTextColor(clr);
			}
			break;
		case DUT_PEN:
			if (m_ArrDrawWParam[i]>=0 && m_ArrDrawWParam[i]<m_nPenArray && m_PenArr[m_ArrDrawWParam[i]]!=NULL)
			{
				if (oldPen==NULL)	oldPen=	pDC->SelectObject(m_PenArr[m_ArrDrawWParam[i]]);
				else						pDC->SelectObject(m_PenArr[m_ArrDrawWParam[i]]);
			}
			break;
		case DUT_BRUSH: 
			if (m_ArrDrawWParam[i]>=0 && m_ArrDrawWParam[i]<m_nBrushArray && m_BrushArr[m_ArrDrawWParam[i]]!=NULL)
			{
				if (oldBrush==NULL)	oldBrush=	pDC->SelectObject(m_BrushArr[m_ArrDrawWParam[i]]);
				else							pDC->SelectObject(m_BrushArr[m_ArrDrawWParam[i]]);
			}
			break;
		case DUT_FONT:
			if (m_ArrDrawWParam[i]>=0 && m_ArrDrawWParam[i]<m_nFontArray && m_FontArr[m_ArrDrawWParam[i]]!=NULL)
			{
				if (oldFont==NULL)	oldFont=	pDC->SelectObject(m_FontArr[m_ArrDrawWParam[i]]);
				else							pDC->SelectObject(m_FontArr[m_ArrDrawWParam[i]]);
			}
			break;
		case DUT_MOVE:
			pDC->MoveTo(LOWORD(m_ArrDrawWParam[i])+LocOffset.x,HIWORD(m_ArrDrawWParam[i])+LocOffset.y);
			break;
		case DUT_MOVER:
			if (m_ArrDrawLParam[i]>=0 && (UINT)m_ArrDrawLParam[i]<m_nRectArray)
			{
				CPoint po(LOWORD(m_ArrDrawWParam[i]),HIWORD(m_ArrDrawWParam[i]));
				po.x=m_RectArr[m_ArrDrawLParam[i]].left+po.x*m_RectArr[m_ArrDrawLParam[i]].Width()/1024;
				po.y=m_RectArr[m_ArrDrawLParam[i]].top+po.y*m_RectArr[m_ArrDrawLParam[i]].Height()/1024;
				pDC->MoveTo(po+LocOffset);
			}
			else
			if (m_ArrDrawLParam[i]<0 && (UINT)(-m_ArrDrawLParam[i]-1)*4<m_nDoubleArray)
			{
				int nArr=(-m_ArrDrawLParam[i]-1)*4;
				CPoint po(LOWORD(m_ArrDrawWParam[i]),HIWORD(m_ArrDrawWParam[i]));
				po.x=(long)(m_DoubleArr[nArr  ]+po.x*(abs((int)(m_DoubleArr[nArr  ]-m_DoubleArr[nArr+2])))/1024);
				po.y=(long)(m_DoubleArr[nArr+1]+po.y*(abs((int)(m_DoubleArr[nArr+1]-m_DoubleArr[nArr+3])))/1024);
				pDC->MoveTo(po+LocOffset);
			}
			break;
		case DUT_MOVEP:
			if (m_ArrDrawWParam[i]<m_nPointArray)
				pDC->MoveTo(m_PointArr[m_ArrDrawWParam[i]]+LocOffset);
			else
			if ((int)m_ArrDrawWParam[i]<0 && (UINT)((-(int)m_ArrDrawWParam[i]-1)*2)<m_nDoubleArray)
				pDC->MoveTo(int(m_DoubleArr[(-((int)m_ArrDrawWParam[i])-1)*2])+LocOffset.x,int(m_DoubleArr[(-((int)m_ArrDrawWParam[i])-1)*2+1])+LocOffset.y);
			break;
		case BUT_BKMODE:
			tmpint=pDC->SetBkMode(m_ArrDrawWParam[i]);
			if (oldBkMode==-123456)	oldBkMode=tmpint;
			break;
		case DUT_PFILLMODE:
			tmpint=pDC->SetPolyFillMode(m_ArrDrawWParam[i]);
			if (oldPfMode==-123456)	oldPfMode=tmpint;
			break;
		case DUT_ROP2:
			tmpint=pDC->SetROP2(m_ArrDrawWParam[i]);
			if (oldROP2Mode==-123456)	oldROP2Mode=tmpint;
			break;
		case DUT_SBLTMODE:
			pDC->SetStretchBltMode(m_ArrDrawWParam[i]);
			break;
		case DUT_COLORADJ:
			if (m_ArrDrawLParam[i]!=NULL)
				pDC->SetColorAdjustment((COLORADJUSTMENT *)m_ArrDrawLParam[i]);
			break;
		case DUT_MAPMODE: 
			tmpint=pDC->SetMapMode(m_ArrDrawWParam[i]);
			if (oldMapMode==-123456)	oldMapMode=tmpint;
			break;
		case DUT_VPORTORG:
			pDC->SetViewportOrg(LOWORD(m_ArrDrawWParam[i]),HIWORD(m_ArrDrawWParam[i]));
			break;
		case DUT_VPORTEXT:
			pDC->SetViewportExt(LOWORD(m_ArrDrawWParam[i]),HIWORD(m_ArrDrawWParam[i]));
			break;
		case DUT_BRUSHORG:
			pDC->SetBrushOrg(LOWORD(m_ArrDrawWParam[i]),HIWORD(m_ArrDrawWParam[i]));
			break;
		case DUT_WINDOWORG:
			pDC->SetWindowOrg(LOWORD(m_ArrDrawWParam[i]),HIWORD(m_ArrDrawWParam[i]));
			break;
		case DUT_WINDOWEXT:
			pDC->SetWindowExt(LOWORD(m_ArrDrawWParam[i]),HIWORD(m_ArrDrawWParam[i]));
			break;
		case DUT_STOCKOBJ:
			pDC->SelectStockObject(m_ArrDrawWParam[i]);
			break;
		case DUT_LINETO:
			pDC->LineTo(LOWORD(m_ArrDrawWParam[i])+LocOffset.x,HIWORD(m_ArrDrawWParam[i])+LocOffset.y);
			break;
		case DUT_LINETOP:
			if (m_ArrDrawWParam[i]<m_nPointArray)
				pDC->LineTo(m_PointArr[m_ArrDrawWParam[i]]+LocOffset);
			else
			if ((int)m_ArrDrawWParam[i]<0 && (UINT)(-((int)m_ArrDrawWParam[i]))*2<m_nDoubleArray)
				pDC->LineTo(int(m_DoubleArr[(-((int)m_ArrDrawWParam[i])-1)*2])+LocOffset.x,int(m_DoubleArr[(-((int)m_ArrDrawWParam[i])-1)*2+1])+LocOffset.y);
			break;
		case DUT_ARC:
		case DUT_ARCTO:
			if (m_ArrDrawLParam[i]!=NULL)
			{
				CRect re=((PDRAWITEMDATA)m_ArrDrawLParam[i])->re1;
				re.OffsetRect(LocOffset);
				CPoint po1=((PDRAWITEMDATA)m_ArrDrawLParam[i])->po1+LocOffset;
				CPoint po2=((PDRAWITEMDATA)m_ArrDrawLParam[i])->po2+LocOffset;
				if (m_ArrDrawType[i]==DUT_ARC)	pDC->Arc(&re,po1,po2);
				else							pDC->ArcTo(&re,po1,po2);
			}
			break;
		case DUT_ARCRPP:
		case DUT_ARCRPPTO:
			if (m_ArrDrawLParam[i]!=NULL)
			{
				PDRAWITEMDATANUM did=(PDRAWITEMDATANUM)m_ArrDrawLParam[i];
				CPoint po1(0,0);
				CPoint po2(0,0);
				CRect re(0,0,0,0);

				if ((UINT)did->i1<m_nPointArray) po1=m_PointArr[did->i1];
				else
				if ((UINT)((-did->i1-1)*2)<m_nDoubleArray)
				{
					po1.x=(int)m_DoubleArr[(-did->i1-1)*2];
					po1.y=(int)m_DoubleArr[(-did->i1-1)*2+1];
				}

				if ((UINT)did->i2<m_nPointArray) po2=m_PointArr[did->i2];
				else
				if ((UINT)((-did->i2-1)*2)<m_nDoubleArray)
				{
					po2.x=(int)m_DoubleArr[(-did->i2-1)*2];
					po2.y=(int)m_DoubleArr[(-did->i2-1)*2+1];
				}

				if ((UINT)did->i3<m_nRectArray) re=m_RectArr[did->i3];
				else
				if ((UINT)((-did->i3-1)*4)<m_nDoubleArray)
				{
					re.left=(int)m_DoubleArr[(-did->i3-1)*4];
					re.top=(int)m_DoubleArr[(-did->i3-1)*4+1];
					re.right=(int)m_DoubleArr[(-did->i3-1)*4+2];
					re.bottom=(int)m_DoubleArr[(-did->i3-1)*4+3];
				}
				
				po1+=LocOffset;
				po2+=LocOffset;
				re.OffsetRect(LocOffset);
				switch(m_ArrDrawType[i])
				{
				case DUT_ARCRPP:	pDC->Arc(&re,po1,po2);	 break;
				case DUT_ARCRPPTO:	pDC->ArcTo(&re,po1,po2); break;
				}
			}
			break;
		case DUT_ANGLEARC:
			if (m_ArrDrawLParam[i]!=NULL)
			{
				PDRAWITEMDATANUM did=(PDRAWITEMDATANUM)m_ArrDrawLParam[i];
				pDC->AngleArc(did->i1+LocOffset.x,did->i2+LocOffset.y,did->i3,(float)did->d1,(float)did->d2);
			}
			break;
		case DUT_ANGLEARCP:
			if (m_ArrDrawLParam[i]!=NULL)
			{
				PDRAWITEMDATANUM did=(PDRAWITEMDATANUM)m_ArrDrawLParam[i];
				CPoint po(0,0);
				if (did->i1>=0 && (UINT)did->i1<m_nPointArray) po=m_PointArr[did->i1];
				else
				if ((UINT)((-did->i1-1)*2)<m_nDoubleArray)
				{
					po.x=(int)m_DoubleArr[(-did->i1-1)*2];
					po.y=(int)m_DoubleArr[(-did->i1-1)*2+1];
				}
				po+=LocOffset;
				pDC->AngleArc(po.x,po.y,did->i3,(float)did->d1,(float)did->d2);
			}
			break;
		case DUT_ARCDIRECTION:
			pDC->SetArcDirection(m_ArrDrawLParam[i]);
			break;
		case DUT_POLYLINE:
		case DUT_POLYLINETO:
		case DUT_POLYGON:
		case DUT_POLYBEZIER:
		case DUT_POLYBEZIERTO:
			if (m_ArrDrawLParam[i]!=NULL)
			{
				POINT *lpo=(POINT *)m_ArrDrawLParam[i];
				UINT j;
				for(j=0;j<m_ArrDrawWParam[i];j++) 
				{
					lpo[j].x+=LocOffset.x;
					lpo[j].y+=LocOffset.y;
				}
				switch(m_ArrDrawType[i])
				{
				case DUT_POLYLINE:		pDC->Polyline(lpo,m_ArrDrawWParam[i]);		break;
				case DUT_POLYLINETO:	pDC->PolylineTo(lpo,m_ArrDrawWParam[i]);		break;
				case DUT_POLYGON:		pDC->Polygon(lpo,m_ArrDrawWParam[i]);			break;
				case DUT_POLYBEZIER:	pDC->PolyBezier(lpo,m_ArrDrawWParam[i]);		break;
				case DUT_POLYBEZIERTO:	pDC->PolyBezierTo(lpo,m_ArrDrawWParam[i]);	break;
				}
				for(j=0;j<m_ArrDrawWParam[i];j++) 
				{
					lpo[j].x-=LocOffset.x;
					lpo[j].y-=LocOffset.y;
				}
			}
			break;

		case DUT_POLYLINEP:
		case DUT_POLYLINEPTO:
		case DUT_POLYGONP:
		case DUT_POLYBEZIERP:
		case DUT_POLYBEZIERPTO:
			if (m_ArrDrawLParam[i]!=NULL && m_ArrDrawWParam[i]>0 && m_ArrDrawWParam[i]<5000)
			{
				POINT *po=new POINT [m_ArrDrawWParam[i]+2];

				int j;
				for(j=0;j<(int)m_ArrDrawWParam[i];j++)
				{
					po[j].x=po[j].y=0;
					if ((UINT)((int *)m_ArrDrawLParam[i])[j]<m_nPointArray)
					{
						po[j].x=m_PointArr[((int *)m_ArrDrawLParam[i])[j]].x+LocOffset.x;
						po[j].y=m_PointArr[((int *)m_ArrDrawLParam[i])[j]].y+LocOffset.y;
					}
					else
					if ((UINT)((-((int *)m_ArrDrawLParam[i])[j]-1)*2)<m_nDoubleArray)
					{
						po[j].x=(int)m_DoubleArr[(-((int *)m_ArrDrawLParam[i])[j]-1)*2]+LocOffset.x;
						po[j].y=(int)m_DoubleArr[(-((int *)m_ArrDrawLParam[i])[j]-1)*2+1]+LocOffset.y;
					}
				}
				switch(m_ArrDrawType[i])
				{
				case DUT_POLYLINEP:		pDC->Polyline(po,m_ArrDrawWParam[i]);		break;
				case DUT_POLYLINEPTO:	pDC->PolylineTo(po,m_ArrDrawWParam[i]);	break;
				case DUT_POLYBEZIERP:	pDC->PolyBezier(po,m_ArrDrawWParam[i]);	break;
				case DUT_POLYBEZIERPTO:	pDC->PolyBezierTo(po,m_ArrDrawWParam[i]);	break;
				case DUT_POLYGONP:		pDC->Polygon(po,m_ArrDrawWParam[i]);		break;
				}
				delete[]  po;
			}
			break;
		case DUT_POLYPOLY:
			if (m_ArrDrawLParam[i]!=NULL && (UINT)m_ArrDrawWParam[i]>0)
			{
				UINT nAll=m_ArrDrawWParam[i]&0xFFFF;
				UINT nPoints=m_ArrDrawWParam[i]/0x10000;

				POINT *lpo=(POINT *)m_ArrDrawLParam[i];

				DWORD *m_dw=new DWORD [nAll];
				UINT j;
				for(j=0;j<nAll;j++)
					m_dw[j]=lpo[j+(m_ArrDrawWParam[i]/0x10000)].x;

				for(j=0;j<nPoints;j++) 
				{
					lpo[j].x+=LocOffset.x;
					lpo[j].y+=LocOffset.y;
				}
				
				pDC->PolyPolyline(lpo,m_dw,nAll);	

				for(j=0;j<nPoints;j++) 
				{
					lpo[j].x-=LocOffset.x;
					lpo[j].y-=LocOffset.y;
				}

				delete[] m_dw;
			}
			break;
		case DUT_PPOLYGON:
			if (m_ArrDrawLParam[i]!=NULL && (UINT)m_ArrDrawWParam[i]>0)
			{
				UINT nAll=m_ArrDrawWParam[i]&0xFFFF;
				UINT nPoints=m_ArrDrawWParam[i]/0x10000;

				POINT *lpo=(POINT *)m_ArrDrawLParam[i];

				int *m_dw=new int [nAll];
				UINT j;
				for(j=0;j<nAll;j++)
					m_dw[j]=lpo[j+(m_ArrDrawWParam[i]/0x10000)].x;

				for(j=0;j<nPoints;j++) 
				{
					lpo[j].x+=LocOffset.x;
					lpo[j].y+=LocOffset.y;
				}
		
				pDC->PolyPolygon(lpo,m_dw,nAll);

				for(j=0;j<nPoints;j++) 
				{
					lpo[j].x-=LocOffset.x;
					lpo[j].y-=LocOffset.y;
				}

				delete[] m_dw;
			}
			break;
		case DUT_POLYPOLYP:
			if (m_ArrDrawLParam[i]!=NULL && (UINT)m_ArrDrawWParam[i]>0)
			{
				POINT *po;
				UINT nAll=m_ArrDrawWParam[i]&0xFFFF;
				UINT nPoints=m_ArrDrawWParam[i]/0x10000;
				DWORD *m_dw=new DWORD [nAll];
				POINT *lpo=(POINT *)m_ArrDrawLParam[i];

				UINT j;
				for(j=0;j<nAll;j++)
					m_dw[j]=lpo[j+nPoints].x;

				for(j=0;j<nPoints;j++)
				{
					po=lpo+j+nPoints;
					lpo[j].x=0;
					lpo[j].y=0;
					if ((UINT)po->y<m_nPointArray)
					{
						lpo[j].x=m_PointArr[po->y].x+LocOffset.x;
						lpo[j].y=m_PointArr[po->y].y+LocOffset.y;
					}
					else
					if ((UINT)((-po->y-1)*2)<m_nDoubleArray)
					{
						lpo[j].x=(int)m_DoubleArr[(-po->y-1)*2]+LocOffset.x;
						lpo[j].y=(int)m_DoubleArr[(-po->y-1)*2+1]+LocOffset.y;
					}
				}
				pDC->PolyPolyline(lpo,m_dw,nAll);	
				delete[] m_dw;
			}
			break;
		case DUT_PPOLYGONP:
			if (m_ArrDrawLParam[i]!=NULL && (UINT)m_ArrDrawWParam[i]>0)
			{
				POINT *po;
				UINT nAll=m_ArrDrawWParam[i]&0xFFFF;
				UINT nPoints=m_ArrDrawWParam[i]/0x10000;
				INT *m_dw=new INT [nAll];
				POINT *lpo=(POINT *)m_ArrDrawLParam[i];

				UINT j;
				for(j=0;j<nAll;j++)
					m_dw[j]=lpo[j+nPoints].x;

				for(j=0;j<nPoints;j++)
				{
					po=lpo+j+nPoints;
					lpo[j].x=0;
					lpo[j].y=0;
					if ((UINT)po->y<m_nPointArray)
					{
						lpo[j].x=m_PointArr[po->y].x+LocOffset.x;
						lpo[j].y=m_PointArr[po->y].y+LocOffset.y;
					}
					else
					if ((UINT)((-po->y-1)*2)<m_nDoubleArray)
					{
						lpo[j].x=(int)m_DoubleArr[(-po->y-1)*2]+LocOffset.x;
						lpo[j].y=(int)m_DoubleArr[(-po->y-1)*2+1]+LocOffset.y;
					}
				}
				pDC->PolyPolygon(lpo,m_dw,nAll);
				delete[] m_dw;
			}
			break;
		case DUT_FILLRECT: 
		case DUT_FRAMERECT: 
			if (m_ArrDrawLParam[i]!=NULL && (UINT)m_ArrDrawWParam[i]<m_nBrushArray && m_BrushArr[m_ArrDrawWParam[i]]!=NULL)
			{
				CRect re=((PDRAWITEMDATA)m_ArrDrawLParam[i])->re1;
				re.OffsetRect(LocOffset);
				switch(m_ArrDrawType[i])
				{
				case DUT_FILLRECT:		pDC->FillRect(&re,m_BrushArr[m_ArrDrawWParam[i]]);	break;
				case DUT_FRAMERECT:		pDC->FrameRect(&re,m_BrushArr[m_ArrDrawWParam[i]]);	break;
				}
			}
			break;
		case DUT_FILLRECTR: 
			if ((UINT)m_ArrDrawWParam[i]<m_nBrushArray && m_BrushArr[m_ArrDrawWParam[i]]!=NULL)
			{
				CRect re(0,0,0,0);
				if ((UINT)m_ArrDrawLParam[i]<m_nRectArray)
					re=m_RectArr[m_ArrDrawLParam[i]];
				else
				if ((UINT)((-m_ArrDrawLParam[i]-1)*4)<m_nDoubleArray)
				{
					re.left=(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4];
					re.top=(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4+1];
					re.bottom=(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4+2];
					re.right=(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4+3];
				}

				re.OffsetRect(LocOffset);
				switch(m_ArrDrawType[i])
				{
				case DUT_FILLRECTR:		pDC->FillRect(&re,m_BrushArr[m_ArrDrawWParam[i]]);	break;
				case DUT_FRAMERECTR:	pDC->FrameRect(&re,m_BrushArr[m_ArrDrawWParam[i]]);	break;
				}
			}
			break;
		case DUT_INVERTRECT: 
			if (m_ArrDrawLParam[i]!=NULL)
			{
				CRect re=((PDRAWITEMDATA)m_ArrDrawLParam[i])->re1;
				re.OffsetRect(LocOffset);
				pDC->InvertRect(&re);
			}
			break;
		case DUT_INVERTRECTR: 
			{
				CRect re(0,0,0,0);
				if ((UINT)m_ArrDrawLParam[i]<m_nRectArray)
					re=m_RectArr[m_ArrDrawLParam[i]];
				else
				if ((UINT)((-m_ArrDrawLParam[i]-1)*4)<m_nDoubleArray)
				{
					re.left=(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4];
					re.top=(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4+1];
					re.bottom=(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4+2];
					re.right=(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4+3];
				}
				re.OffsetRect(LocOffset);
				pDC->InvertRect(&re);
			}
			break;
		case DUT_ICON:
			if ((UINT)m_ArrDrawLParam[i]<m_nIconArray && m_IconArr[m_ArrDrawLParam[i]]!=NULL)
				pDC->DrawIcon(LOWORD(m_ArrDrawWParam[i])+LocOffset.x,HIWORD(m_ArrDrawWParam[i])+LocOffset.y,m_IconArr[m_ArrDrawLParam[i]]);
			break;
		case DUT_ICONP:
			if ((UINT)m_ArrDrawLParam[i]<m_nIconArray && m_IconArr[m_ArrDrawLParam[i]]!=NULL)
			{
				if ((UINT)m_ArrDrawWParam[i]<m_nPointArray)
					pDC->DrawIcon(m_PointArr[m_ArrDrawWParam[i]]+LocOffset,m_IconArr[m_ArrDrawLParam[i]]);
				else
				if ((UINT)((-((int)m_ArrDrawWParam[i])-1)*2)<m_nDoubleArray)
					pDC->DrawIcon(CPoint((int)m_DoubleArr[(-((int)m_ArrDrawWParam[i])-1)*2],(int)m_DoubleArr[(-((int)m_ArrDrawWParam[i])-1)*2+1])+LocOffset,m_IconArr[m_ArrDrawLParam[i]]);
			}
			break;
		case DUT_FILLSRECT: 
		case DUT_3DRECT: 
		case DUT_EDGE:
		case DUT_FRAMECTRL:
		case DUT_PIE:
		case DUT_ROUNDRECT:
		case DUT_CHORD:
			if (m_ArrDrawLParam[i]!=NULL)
			{
				CRect re=((PDRAWITEMDATA)m_ArrDrawLParam[i])->re1;
				re.OffsetRect(LocOffset);
				switch(m_ArrDrawType[i])
				{
				case DUT_FILLSRECT: 
					pDC->FillSolidRect(&re,((PDRAWITEMDATA)m_ArrDrawLParam[i])->clr1);
					break;
				case DUT_3DRECT: 
					pDC->Draw3dRect(&re,((PDRAWITEMDATA)m_ArrDrawLParam[i])->clr1,((PDRAWITEMDATA)m_ArrDrawLParam[i])->clr2);
					break;
				case DUT_EDGE:
					pDC->DrawEdge(&re,((PDRAWITEMDATA)m_ArrDrawLParam[i])->clr1,((PDRAWITEMDATA)m_ArrDrawLParam[i])->clr2);
					break;
				case DUT_FRAMECTRL:
					pDC->DrawFrameControl(&re,((PDRAWITEMDATA)m_ArrDrawLParam[i])->clr1,((PDRAWITEMDATA)m_ArrDrawLParam[i])->clr2);
					break;
				case DUT_PIE:
					pDC->Pie( &re, ((PDRAWITEMDATA)m_ArrDrawLParam[i])->po1+LocOffset, ((PDRAWITEMDATA)m_ArrDrawLParam[i])->po2+LocOffset);
					break;
				case DUT_ROUNDRECT:
					pDC->RoundRect(&re,((PDRAWITEMDATA)m_ArrDrawLParam[i])->po1+LocOffset);
					break;
				case DUT_CHORD:
					pDC->Chord( &re,((PDRAWITEMDATA)m_ArrDrawLParam[i])->po1+LocOffset, ((PDRAWITEMDATA)m_ArrDrawLParam[i])->po2+LocOffset);
					break;
				}
			}
			break;
		case DUT_PIERP:
		case DUT_CHORDRP://sscanf(pos,"%d,%d,%d",&did->re1.left,&did->po1.x,&did->po2.x);
			if (m_ArrDrawLParam[i]!=NULL)
			{
				PDRAWITEMDATA did=(PDRAWITEMDATA)m_ArrDrawLParam[i];
				CRect re(0,0,0,0);

				if ((UINT)did->re1.left<m_nRectArray)
					re=m_RectArr[did->re1.left];
				else
					if ((UINT)((-did->re1.left-1)*4)<m_nDoubleArray)
					{
						re.left=(int)m_DoubleArr[(-did->re1.left-1)*4];
						re.top=(int)m_DoubleArr[(-did->re1.left-1)*4+1];
						re.bottom=(int)m_DoubleArr[(-did->re1.left-1)*4+2];
						re.right=(int)m_DoubleArr[(-did->re1.left-1)*4+3];
					}
				re.OffsetRect(LocOffset);

				CPoint po1(LocOffset);
				if ((UINT)did->po1.x<m_nPointArray) po1=m_PointArr[did->po1.x];
				else
				if ((UINT)((-did->po1.x-1)*2)<m_nDoubleArray)
				{
					po1.x+=(int)m_DoubleArr[(-did->po1.x-1)*2];
					po1.y+=(int)m_DoubleArr[(-did->po1.x-1)*2+1];
				}

				CPoint po2(LocOffset);
				if ((UINT)did->po2.x<m_nPointArray) po2=m_PointArr[did->po2.x];
				else
				if ((UINT)((-did->po2.x-1)*2)<m_nDoubleArray)
				{
					po2.x+=(int)m_DoubleArr[(-did->po2.x-1)*2];
					po2.y+=(int)m_DoubleArr[(-did->po2.x-1)*2+1];
				}

				switch(m_ArrDrawType[i])
				{
				case DUT_PIERP: 
					pDC->Pie( &re,po1,po2);
					break;
				case DUT_CHORDRP: 
					pDC->Chord( &re,po1,po2);
					break;
				}
			}
			break;
		case DUT_ROUNDRECTR:
			if (m_ArrDrawLParam[i]!=NULL)
			{
				PDRAWITEMDATA did=(PDRAWITEMDATA)m_ArrDrawLParam[i];
				CRect re(0,0,0,0);
				if ((UINT)did->re1.left<m_nRectArray)	re=m_RectArr[did->re1.left];
				else
					if ((UINT)((-did->re1.left-1)*4)<m_nDoubleArray)
					{
						re.left=(int)m_DoubleArr[(-did->re1.left-1)*4];
						re.top=(int)m_DoubleArr[(-did->re1.left-1)*4+1];
						re.bottom=(int)m_DoubleArr[(-did->re1.left-1)*4+2];
						re.right=(int)m_DoubleArr[(-did->re1.left-1)*4+3];
					}
				re.OffsetRect(LocOffset);

				CPoint po1(LocOffset);
				if ((UINT)did->po1.x<m_nPointArray) po1=m_PointArr[did->po1.x];
				else
				if ((UINT)((-did->po1.x-1)*2)<m_nDoubleArray)
				{
					po1.x+=(int)m_DoubleArr[(-did->po1.x-1)*2];
					po1.y+=(int)m_DoubleArr[(-did->po1.x-1)*2+1];
				}
				pDC->RoundRect( &re,po1);
			}
			break;
		case DUT_FILLSRECTR: 
			{
				CRect re(0,0,0,0);
				COLORREF clr=0;
				if (m_ArrDrawWParam[i]<m_nRectArray)	re=m_RectArr[m_ArrDrawWParam[i]];
				else
					if ((UINT)((-((int)m_ArrDrawWParam[i])-1)*4)<m_nDoubleArray)
					{
						re.left  =(int)m_DoubleArr[(-((int)m_ArrDrawWParam[i])-1)*4];
						re.top   =(int)m_DoubleArr[(-((int)m_ArrDrawWParam[i])-1)*4+1];
						re.bottom=(int)m_DoubleArr[(-((int)m_ArrDrawWParam[i])-1)*4+2];
						re.right =(int)m_DoubleArr[(-((int)m_ArrDrawWParam[i])-1)*4+3];
					}
				re.OffsetRect(LocOffset);

				if ((UINT)m_ArrDrawLParam[i]<m_nRGBArray) clr=m_RGBArr[m_ArrDrawLParam[i]];

				pDC->FillSolidRect(&re,clr);
			}
			break;
		case DUT_3DRECTR: 
			if (m_ArrDrawLParam[i]!=NULL)
			{
				PDRAWITEMDATANUM did=(PDRAWITEMDATANUM)m_ArrDrawLParam[i];
				CRect re(0,0,0,0);
				COLORREF clr1=0;
				COLORREF clr2=0;
				if ((UINT)did->i1<m_nRectArray)	re=m_RectArr[did->i1];
				else
					if ((UINT)((-did->i1-1)*4)<m_nDoubleArray)
					{
						re.left  =(int)m_DoubleArr[(-did->i1-1)*4];
						re.top   =(int)m_DoubleArr[(-did->i1-1)*4+1];
						re.bottom=(int)m_DoubleArr[(-did->i1-1)*4+2];
						re.right =(int)m_DoubleArr[(-did->i1-1)*4+3];
					}
				re.OffsetRect(LocOffset);

				if ((UINT)did->i2<m_nRGBArray) clr1=m_RGBArr[did->i2];
				if ((UINT)did->i3<m_nRGBArray) clr2=m_RGBArr[did->i3];

				pDC->Draw3dRect(&re,clr1,clr2);
			}
			break;
		case DUT_EDGER:
		case DUT_FRAMECTRLR:
			if (m_ArrDrawLParam[i]!=NULL)
			{
				PDRAWITEMDATANUM did=(PDRAWITEMDATANUM)m_ArrDrawLParam[i];
				CRect re(0,0,0,0);
				if ((UINT)did->i1<m_nRectArray)	re=m_RectArr[did->i1];
				else
					if ((UINT)((-did->i1-1)*4)<m_nDoubleArray)
					{
						re.left  =(int)m_DoubleArr[(-did->i1-1)*4];
						re.top   =(int)m_DoubleArr[(-did->i1-1)*4+1];
						re.bottom=(int)m_DoubleArr[(-did->i1-1)*4+2];
						re.right =(int)m_DoubleArr[(-did->i1-1)*4+3];
					}
				re.OffsetRect(LocOffset);
				switch(m_ArrDrawType[i])
				{
				case DUT_EDGER:
					pDC->DrawEdge(&re,did->i2,did->i3);
					break;
				case DUT_FRAMECTRLR:
					pDC->DrawFrameControl(&re,did->i2,did->i3);
					break;
				}
			}
			break;
		case DUT_STATETEXT:
			{
				PDRAWITEMDATATEXT did=(PDRAWITEMDATATEXT)m_ArrDrawLParam[i];
				if (did!=NULL)
					pDC->DrawState(
							did->re.TopLeft()+LocOffset,
							did->re.Size(),
							did->text,
							did->flags|DST_TEXT,
							did->flags2,
							0,
							(did->nBrush<0 || (UINT)did->nBrush>m_nBrushArray)?NULL:m_BrushArr[did->nBrush]
						);
			}
			break;
		case DUT_STATETEXTR:
			if (m_ArrDrawLParam[i]!=NULL)
			{
				PDRAWITEMDATATEXT did=(PDRAWITEMDATATEXT)m_ArrDrawLParam[i];
				if ((UINT)did->re.left<m_nRectArray)
					pDC->DrawState(
							m_RectArr[did->re.left].TopLeft()+LocOffset,
							m_RectArr[did->re.left].Size(),
							did->text,
							did->flags|DST_TEXT,
							did->flags2,
							0,
							(did->nBrush<0 || (UINT)did->nBrush>m_nBrushArray)?NULL:m_BrushArr[did->nBrush]
						);
				else
				if ((UINT)(-did->re.left-1)*4<m_nDoubleArray)
					pDC->DrawState(
							CPoint((int)m_DoubleArr[(-did->re.left-1)*4],(int)m_DoubleArr[(-did->re.left-1)*4+1])+LocOffset,
							CSize((int)m_DoubleArr[(-did->re.left-1)*4+2]-(int)m_DoubleArr[(-did->re.left-1)*4],(int)m_DoubleArr[(-did->re.left-1)*4+3]-(int)m_DoubleArr[(-did->re.left-1)*4+1]),
							did->text,
							did->flags|DST_TEXT,
							did->flags2,
							0,
							(did->nBrush<0 || (UINT)did->nBrush>m_nBrushArray)?NULL:m_BrushArr[did->nBrush]
						);
				}
			break;
		case DUT_STATEICON:// nRect,nIcon,nBrush
			{
				PDRAWITEMDATA did=(PDRAWITEMDATA)m_ArrDrawLParam[i];
				if (did!=NULL && (UINT) did->re2.left<m_nIconArray)
					pDC->DrawState(
							did->re1.TopLeft()+LocOffset,
							did->re1.Size(),
							m_IconArr[did->re2.left],
							did->clr1|DST_ICON,
							(did->clr2<0 || (UINT)did->clr2>m_nBrushArray)?NULL:m_BrushArr[did->clr2]
						);
			}
			break;
		case DUT_STATEICONR:
			if (m_ArrDrawLParam[i]!=NULL)
			{
				PDRAWITEMDATA did=(PDRAWITEMDATA)m_ArrDrawLParam[i];
				if ((UINT) did->re2.left<m_nIconArray && (UINT)did->re1.left<m_nRectArray)
					pDC->DrawState(
							m_RectArr[did->re1.left].TopLeft()+LocOffset,
							m_RectArr[did->re1.left].Size(),
							m_IconArr[did->re2.left],
							did->clr1|DST_ICON,
							(did->clr2<0 || (UINT)did->clr2>m_nBrushArray)?NULL:m_BrushArr[did->clr2]
						);
				else
				if ((UINT) did->re2.left<m_nIconArray && (UINT)(-did->re1.left-1)*4<m_nDoubleArray)
					pDC->DrawState(
							CPoint((int)m_DoubleArr[(-did->re1.left-1)*4],(int)m_DoubleArr[(-did->re1.left-1)*4+1])+LocOffset,
							CSize((int)m_DoubleArr[(-did->re1.left-1)*4+2]-(int)m_DoubleArr[(-did->re1.left-1)*4],(int)m_DoubleArr[(-did->re1.left-1)*4+3]-(int)m_DoubleArr[(-did->re1.left-1)*4+1]),
							m_IconArr[did->re2.left],
							did->clr1|DST_ICON,
							(did->clr2<0 || (UINT)did->clr2>m_nBrushArray)?NULL:m_BrushArr[did->clr2]
						);
			}
			break;
		case DUT_FOCUSRECT:
		case DUT_ELLIPSE:
		case DUT_RECT:
			if (m_ArrDrawLParam[i]!=NULL)
			{
				CRect re=(LPRECT)m_ArrDrawLParam[i];
				re.OffsetRect(LocOffset);
				switch(m_ArrDrawType[i])
				{
				case DUT_FOCUSRECT:	pDC->DrawFocusRect(re);	break;
				case DUT_ELLIPSE:	pDC->Ellipse(re);			break;
				case DUT_RECT:		pDC->Rectangle(re);		break;
				}
			}
			break;
		case DUT_FOCUSRECTR:
		case DUT_ELLIPSER:
		case DUT_RECTR:
			{
				CRect re(0,0,0,0);
				 if ((UINT)m_ArrDrawLParam[i]<m_nRectArray)
					re=m_RectArr[m_ArrDrawLParam[i]];
				 else
					if ((UINT)((-m_ArrDrawLParam[i]-1)*4)<m_nDoubleArray)
					{
						re.left  =(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4];
						re.top   =(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4+1];
						re.bottom=(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4+2];
						re.right =(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4+3];
					}
				re.OffsetRect(LocOffset);
				switch(m_ArrDrawType[i])
				{
				case DUT_FOCUSRECTR:	pDC->DrawFocusRect(re);	break;
				case DUT_ELLIPSER:		pDC->Ellipse(re);			break;
				case DUT_RECTR:			pDC->Rectangle(re);		break;
				}
			 }
			break;
		case DUT_PIXEL:
			if (m_ArrDrawLParam[i]!=NULL)
				pDC->SetPixelV(((PDRAWITEMDATA)m_ArrDrawLParam[i])->po1+LocOffset,((PDRAWITEMDATA)m_ArrDrawLParam[i])->clr1);
			break;
		case DUT_FLOODFILL:
			if (m_ArrDrawLParam[i]!=NULL)
				pDC->FloodFill(((PDRAWITEMDATA)m_ArrDrawLParam[i])->po1.x+LocOffset.x,((PDRAWITEMDATA)m_ArrDrawLParam[i])->po1.y+LocOffset.y,((PDRAWITEMDATA)m_ArrDrawLParam[i])->clr1);
			break;
		case DUT_EXTFLOODFILL:
			if (m_ArrDrawLParam[i]!=NULL)
				pDC->ExtFloodFill(((PDRAWITEMDATA)m_ArrDrawLParam[i])->po1.x+LocOffset.x,((PDRAWITEMDATA)m_ArrDrawLParam[i])->po1.y+LocOffset.y,((PDRAWITEMDATA)m_ArrDrawLParam[i])->clr1,FLOODFILLSURFACE);
			break;
		case DUT_PIXELPC:
		case DUT_FLOODFILLPC:
		case DUT_EXTFLOODFILLPC:
			{
				int nPo=LOWORD(m_ArrDrawWParam[i]),nClr=HIWORD(m_ArrDrawWParam[i]);
				CPoint po(0,0);
				COLORREF clr=0;
				if ((UINT)nPo<m_nPointArray) po=m_PointArr[nPo];
				else 
					if ((UINT)((-nPo-1)*2)<m_nDoubleArray)
					{
						po.x =(int)m_DoubleArr[(-nPo-1)*2];
						po.y =(int)m_DoubleArr[(-nPo-1)*2+1];
					}

				if ((UINT)nClr<m_nRGBArray) clr=m_RGBArr[nClr];
				po+=LocOffset;

				switch(m_ArrDrawType[i])
				{
				case DUT_PIXELPC:			pDC->SetPixelV(po,clr);			break;
				case DUT_FLOODFILLPC:		pDC->FloodFill(po.x,po.y,clr);	break;
				case DUT_EXTFLOODFILLPC:	pDC->ExtFloodFill(po.x,po.y,clr,FLOODFILLSURFACE);	break;
				}
			}
			break;
		case DUT_TEXTOUT:
			{
				PDRAWITEMDATATEXT did=(PDRAWITEMDATATEXT)m_ArrDrawLParam[i];
				if (did!=NULL)
					pDC->TextOut(did->po.x+LocOffset.x,did->po.y+LocOffset.y,did->text);
			}
			break;
		case DUT_TEXTOUTPT:
			{
				int nPo=LOWORD(m_ArrDrawWParam[i]),nTxt=HIWORD(m_ArrDrawWParam[i]);
				CPoint po(0,0);
				if ((UINT)nPo<m_nPointArray) po=m_PointArr[nPo];
				else 
					if ((UINT)((-nPo-1)*2)<m_nDoubleArray)
					{
						po.x =(int)m_DoubleArr[(-nPo-1)*2];
						po.y =(int)m_DoubleArr[(-nPo-1)*2+1];
					}
				po+=LocOffset;

				if ((UINT)nTxt<m_nStringArray)
					pDC->TextOut(po.x,po.y,m_StringArr[nTxt]);
			}
			break;
		case DUT_EXTTEXTOUT://x,y,left,top,right,bottom,flags;arrWidths;TEXT
			{
				PDRAWITEMDATATEXT did=(PDRAWITEMDATATEXT)m_ArrDrawLParam[i];
				if (did!=NULL)
				{
					CRect re=did->re;
					re.OffsetRect(LocOffset);
					pDC->ExtTextOut(did->po.x+LocOffset.x,did->po.y+LocOffset.y,did->flags,&re,did->text,(LPINT)m_ArrDrawWParam[i]);
				}
			}
			break;
		case DUT_EXTTEXTOUTP://nPoint,nRect,nText,flags;arrWidths;TEXT
			if (m_ArrDrawLParam[i]!=NULL)
			{
				PDRAWITEMDATATEXT did=(PDRAWITEMDATATEXT)m_ArrDrawLParam[i];
				CPoint po(0,0);
				CRect re(0,0,0,0);
				if ((UINT)did->po.x<m_nPointArray) po=m_PointArr[did->po.x];
				else 
					if ((UINT)((-did->po.x-1)*2)<m_nDoubleArray)
					{
						po.x =(int)m_DoubleArr[(-did->po.x-1)*2];
						po.y =(int)m_DoubleArr[(-did->po.x-1)*2+1];
					}

				if ((UINT)did->re.left<m_nRectArray)
					re=m_RectArr[did->re.left];
				 else
					if ((UINT)((-did->re.left-1)*4)<m_nDoubleArray)
					{
						re.left  =(int)m_DoubleArr[(-did->re.left-1)*4];
						re.top   =(int)m_DoubleArr[(-did->re.left-1)*4+1];
						re.bottom=(int)m_DoubleArr[(-did->re.left-1)*4+2];
						re.right =(int)m_DoubleArr[(-did->re.left-1)*4+3];
					}

				po+=LocOffset;
				re.OffsetRect(LocOffset);
				if ((UINT)did->re.top<m_nStringArray)
					pDC->ExtTextOut(
						po.x,po.y,did->flags,&re,
						m_StringArr[did->re.top],
						(LPINT)m_ArrDrawWParam[i]);
			}
			break;
		case DUT_TABTEXTOUT://x,y,nTabPositions,nTabOrigin;arrWidths;TEXT
			//sscanf(pos,"%d,%d,%d,%d",&did->po.x,&did->po.y,&did->re.left,&did->re.top);
			{
				PDRAWITEMDATATEXT did=(PDRAWITEMDATATEXT)m_ArrDrawLParam[i];
				if (did!=NULL)
					pDC->TabbedTextOut(did->po.x+LocOffset.x,did->po.y+LocOffset.y,did->text,did->re.left,(LPINT)m_ArrDrawWParam[i],did->re.top);
			}
			break;
		case DUT_TABTEXTOUTP://nPoint,nText,nTabPositions,nTabOrigin;arrWidths
			if (m_ArrDrawLParam[i]!=NULL)
			{//sscanf(pos,"%d,%d,%d,%d",&did->po.x,&did->po.y,&did->re.left,&did->re.top);
				PDRAWITEMDATATEXT did=(PDRAWITEMDATATEXT)m_ArrDrawLParam[i];
				if ((UINT)did->po.y<m_nStringArray)
				{
					CPoint po(0,0);
					if ((UINT)did->po.x<m_nPointArray) po=m_PointArr[did->po.x];
					else 
						if ((UINT)((-did->po.x-1)*2)<m_nDoubleArray)
						{
							po.x =(int)m_DoubleArr[(-did->po.x-1)*2];
							po.y =(int)m_DoubleArr[(-did->po.x-1)*2+1];
						}
					po+=LocOffset;

					pDC->TabbedTextOut(
						po.x,po.y,
						m_StringArr[did->po.y],
						did->re.left,
						(LPINT)m_ArrDrawWParam[i],
						did->re.top);
				}
			}
			break;
		case DUT_TEXT://left,top,right,bottom,flags;TEXT
			{
				PDRAWITEMDATATEXT did=(PDRAWITEMDATATEXT)m_ArrDrawLParam[i];
				if (did!=NULL)
				{
					CRect re=did->re;
					re.OffsetRect(LocOffset);
					pDC->DrawText(did->text,&re,did->flags);
				}
			}
			break;
		case DUT_TEXTR://nRect,nText,flags
			if (m_ArrDrawLParam[i]!=NULL)
			{	//sscanf(pos,"%d,%d,%d",&did->po.x,&did->po.y,&did->flags);
				PDRAWITEMDATATEXT did=(PDRAWITEMDATATEXT)m_ArrDrawLParam[i];
				if ((UINT)did->po.y<m_nStringArray)
				{
					CRect re(0,0,0,0);
					if ((UINT)did->po.x<m_nRectArray)
						re=m_RectArr[did->po.x];
					 else
						if ((UINT)((-did->po.x-1)*4)<m_nDoubleArray)
						{
							re.left  =(int)m_DoubleArr[(-did->po.x-1)*4];
							re.top   =(int)m_DoubleArr[(-did->po.x-1)*4+1];
							re.bottom=(int)m_DoubleArr[(-did->po.x-1)*4+2];
							re.right =(int)m_DoubleArr[(-did->po.x-1)*4+3];
						}
					re.OffsetRect(LocOffset);
					pDC->DrawText(m_StringArr[did->po.y],re,did->flags);
				}
			}
			break;
		case DUT_TEXTALIGN:		pDC->SetTextAlign(m_ArrDrawWParam[i]);			break;
		case DUT_TEXTJUST:		pDC->SetTextJustification(m_ArrDrawWParam[i],m_ArrDrawLParam[i]);		break; 
		case DUT_CHAREXTRA:		pDC->SetTextCharacterExtra(m_ArrDrawWParam[i]);	break; 
		case DUT_MAPPERFLAGS:	pDC->SetMapperFlags(m_ArrDrawWParam[i]);			break; 
		case DUT_ABORTPATH:			pDC->AbortPath();		break;
		case DUT_BEGINPATH:			pDC->BeginPath();		break;
		case DUT_CLOSEFIGURE:		pDC->CloseFigure();	break;
		case DUT_ENDPATH:			pDC->EndPath();		break;
		case DUT_FILLPATH:			pDC->FillPath();		break;
		case DUT_FLATTENPATH:		pDC->FlattenPath();	break;
		case DUT_SELECTCLIPPATH:	pDC->SelectClipPath(m_ArrDrawWParam[i]);	break;
		case DUT_SETMITERLIMIT:	
			if (m_ArrDrawLParam[i]!=NULL)
				pDC->SetMiterLimit(*((float *)m_ArrDrawLParam[i]));
			break;
		case DUT_STROKEFILLPATH:	pDC->StrokeAndFillPath();	break;
		case DUT_STROKEPATH:		pDC->StrokePath();		break;
		case DUT_WIDENPATH:			pDC->WidenPath();			break;
		case DUT_OFFSET:
			LocOffset.x=m_ArrDrawWParam[i];
			LocOffset.y=m_ArrDrawLParam[i];
			break;
		case DUT_OFFSETP:
			if ((UINT)m_ArrDrawWParam[i]<m_nPointArray)	LocOffset=m_PointArr[m_ArrDrawWParam[i]];
			break;
		case DUT_ARROW:
		case DUT_ARROWTO://x,y,Width,Length,type,dPart
		case DUT_ARROWP:
		case DUT_ARROWPTO://nPoint,Width,Length,type,dPart
			if (m_ArrDrawLParam[i]!=NULL)
			{
				PDRAWITEMDATANUM did=(PDRAWITEMDATANUM) m_ArrDrawLParam[i];
				CPoint endpos(0,0);
				CPoint curpos=pDC->GetCurrentPosition();
				switch(m_ArrDrawType[i])
				{
				case DUT_ARROW:	
				case DUT_ARROWTO:	
					endpos.x=did->i1+LocOffset.x;
					endpos.y=did->i2+LocOffset.y;
					break;
				case DUT_ARROWP:	
				case DUT_ARROWPTO:	
					if ((UINT)did->i1<m_nPointArray)
						endpos=m_PointArr[did->i1]+LocOffset;
					else
						if ((UINT)((-did->i1-1)*2)<m_nDoubleArray)
						{
							endpos.x =(int)m_DoubleArr[(-did->i1-1)*2]+LocOffset.x;
							endpos.y =(int)m_DoubleArr[(-did->i1-1)*2+1]+LocOffset.y;
						}
					break;
				}
				int len=(int)sqrt((double)((curpos.x-endpos.x)*(curpos.x-endpos.x)+(curpos.y-endpos.y)*(curpos.y-endpos.y)));
				if (len<did->i3 || len<=0) break;

				CPoint LineStart=curpos;
				CPoint LineEnd=endpos;
				LineEnd.x-=(long)((did->i3*did->d1*(endpos.x-curpos.x))/len);
				LineEnd.y-=(long)((did->i3*did->d1*(endpos.y-curpos.y))/len);
				if ((did->id4&0x10)==0x10)
				{
					LineStart.x+=(long)((did->i3*did->d1*(endpos.x-curpos.x))/len);
					LineStart.y+=(long)((did->i3*did->d1*(endpos.y-curpos.y))/len);
				}
				pDC->MoveTo(LineStart);
				pDC->LineTo(LineEnd);
				POINT po[6];
				int nPo=4;
				po[0].x=LineEnd.x;
				po[0].y=LineEnd.y;
				switch(did->id4&0xF)
				{
				case 0: // normal
					po[2].x=endpos.x;
					po[2].y=endpos.y;
					po[1].x=endpos.x-((did->i3*(endpos.x-curpos.x))/len)+((did->i4*(endpos.y-curpos.y))/len/2);
					po[1].y=endpos.y-((did->i3*(endpos.y-curpos.y))/len)-((did->i4*(endpos.x-curpos.x))/len/2);
					po[3].x=endpos.x-((did->i3*(endpos.x-curpos.x))/len)-((did->i4*(endpos.y-curpos.y))/len/2);
					po[3].y=endpos.y-((did->i3*(endpos.y-curpos.y))/len)+((did->i4*(endpos.x-curpos.x))/len/2);
					break;
				case 1: // quadro
					po[1].x=endpos.x-((did->i3*(endpos.x-curpos.x))/len)+((did->i4*(endpos.y-curpos.y))/len/2);
					po[1].y=endpos.y-((did->i3*(endpos.y-curpos.y))/len)-((did->i4*(endpos.x-curpos.x))/len/2);
					po[3].x=endpos.x;
					po[3].y=endpos.y;
					po[5].x=endpos.x-((did->i3*(endpos.x-curpos.x))/len)-((did->i4*(endpos.y-curpos.y))/len/2);
					po[5].y=endpos.y-((did->i3*(endpos.y-curpos.y))/len)+((did->i4*(endpos.x-curpos.x))/len/2);
					po[2].x=po[1].x+(po[3].x-po[0].x);
					po[2].y=po[1].y+(po[3].y-po[0].y);
					po[4].x=po[5].x+(po[3].x-po[0].x);
					po[4].y=po[5].y+(po[3].y-po[0].y);
					nPo=6;
					break;
				default:
					po[0].x=po[1].x=po[2].x=po[3].x=LineEnd.x;
					po[0].y=po[1].y=po[2].y=po[3].y=LineEnd.y;
					break;
				}
				pDC->Polygon(po,nPo);
 
				if ((did->id4&0x10)==0x10)
				{
					po[0].x=LineStart.x;
					po[0].y=LineStart.y;
					switch(did->id4&0xF)
					{
					case 0: // normal
						po[2].x=curpos.x;
						po[2].y=curpos.y;
						po[1].x=curpos.x+((did->i3*(endpos.x-curpos.x))/len)+((did->i4*(endpos.y-curpos.y))/len/2);
						po[1].y=curpos.y+((did->i3*(endpos.y-curpos.y))/len)-((did->i4*(endpos.x-curpos.x))/len/2);
						po[3].x=curpos.x+((did->i3*(endpos.x-curpos.x))/len)-((did->i4*(endpos.y-curpos.y))/len/2);
						po[3].y=curpos.y+((did->i3*(endpos.y-curpos.y))/len)+((did->i4*(endpos.x-curpos.x))/len/2);
						break;
					case 1: // quadro
						po[1].x=curpos.x+((did->i3*(endpos.x-curpos.x))/len)+((did->i4*(endpos.y-curpos.y))/len/2);
						po[1].y=curpos.y+((did->i3*(endpos.y-curpos.y))/len)-((did->i4*(endpos.x-curpos.x))/len/2);
						po[3].x=curpos.x;
						po[3].y=curpos.y;
						po[5].x=curpos.x+((did->i3*(endpos.x-curpos.x))/len)-((did->i4*(endpos.y-curpos.y))/len/2);
						po[5].y=curpos.y+((did->i3*(endpos.y-curpos.y))/len)+((did->i4*(endpos.x-curpos.x))/len/2);
						po[2].x=po[1].x+(po[3].x-po[0].x);
						po[2].y=po[1].y+(po[3].y-po[0].y);
						po[4].x=po[5].x+(po[3].x-po[0].x);
						po[4].y=po[5].y+(po[3].y-po[0].y);
						nPo=6;
						break;
					default:
						po[0].x=po[1].x=po[2].x=po[3].x=curpos.x;
						po[0].y=po[1].y=po[2].y=po[3].y=curpos.y;
						break;
					}
					pDC->Polygon(po,nPo);
				}

				
				switch(m_ArrDrawType[i])
				{
				case DUT_ARROWP:	
				case DUT_ARROW:	
					pDC->MoveTo(curpos);
					break;
				case DUT_ARROWPTO:	
				case DUT_ARROWTO:	
					pDC->MoveTo(endpos);
					break;
				}
			}
			break;
		case DUT_CLONE:
		case DUT_CLONETO:
		case DUT_CLONEC:
		case DUT_CLONECTO:
			if (m_ArrDrawLParam[i]!=NULL)
			{//nItem,nTime,dx,dy,dxMulty,dyMulty
				PDRAWITEMDATAPRG did=(PDRAWITEMDATAPRG)m_ArrDrawLParam[i];
				if (did->DIDNum!=NULL)
				{
					if (did->IsRun==FALSE)
					{
						did->IsRun=TRUE;
						did->PrevJOB=NextJob;
						did->counter=0;
						did->d1=0;
						did->d2=0;
						did->QurentOffset=did->PrevOffset=LocOffset;
						did->PrevPosition=pDC->GetCurrentPosition();
						did->QurentPosition=did->PrevPosition+did->PrevOffset;
					}

					if (did->counter>=did->DIDNum->i2)
					{// end clone
						switch(m_ArrDrawType[i])
						{
						case DUT_CLONE:	
						case DUT_CLONEC:	
							break;
						case DUT_CLONETO:	
						case DUT_CLONECTO:	
							pDC->MoveTo(did->PrevPosition);
							break;
						}
						NextJob=did->PrevJOB;
						did->IsRun=FALSE;
						LocOffset=did->PrevOffset;
						did->counter=0;
						did->d1=0;
						did->d2=0;
					}
					else
					{
						if (did->counter>0)
						{
							did->d1+=did->DIDNum->d1*pow(did->DIDNum->d3,did->counter);
							did->d2+=did->DIDNum->d2*pow(did->DIDNum->d4,did->counter);
							did->QurentPosition=did->PrevPosition+did->PrevOffset;
							did->QurentPosition.x+=(long)did->d1;
							did->QurentPosition.y+=(long)did->d2;
							switch(m_ArrDrawType[i])
							{
							case DUT_CLONE:	
							case DUT_CLONETO:	
								pDC->MoveTo(did->QurentPosition);
								break;
							case DUT_CLONEC:	
							case DUT_CLONECTO:	
								break;
							}
						}
						LocOffset.x=(long)(did->PrevOffset.x+did->d1);
						LocOffset.y=(long)(did->PrevOffset.y+did->d2);
						NextJob=i;		
						i=did->DIDNum->i1-1;
						did->counter++;
						continue;
					}
				}
			}
			break;
		case DUT_GOTO://Adress
			NextJob=0x10000000;
			switch(m_ArrDrawWParam[i])
			{
			case 0x1://'-''+' offset
				NextJob=i+m_ArrDrawLParam[i];
				break;
			case 0x2://'&' direct
				if ((UINT)m_ArrDrawLParam[i]<m_nIntArray)
					NextJob=m_IntArr[m_ArrDrawLParam[i]];
				break;
			case 0x4://'@' offset
				if ((UINT)m_ArrDrawLParam[i]<m_nIntArray)
					NextJob=i+m_IntArr[m_ArrDrawLParam[i]];
				break;
			case 0x0:// direct
				NextJob=m_ArrDrawLParam[i];
				break;
			}
			if (NextJob==i) NextJob=0x10000000;
			break;
		case DUT_GOSUB://Adress
			{
				NextJob=0x10000000;
				switch(m_ArrDrawWParam[i])
				{
				case 0x1://'-''+' offset
					NextJob=i+m_ArrDrawLParam[i];
					break;
				case 0x2://'&' direct
					if ((UINT)m_ArrDrawLParam[i]<m_nIntArray)
						NextJob=m_IntArr[m_ArrDrawLParam[i]];
					break;
				case 0x4://'@' offset
					if ((UINT)m_ArrDrawLParam[i]<m_nIntArray)
						NextJob=i+m_IntArr[m_ArrDrawLParam[i]];
					break;
				case 0x0:// direct
					NextJob=m_ArrDrawLParam[i];
					break;
				}

				if (NextJob==i) NextJob=0x10000000;

				if (m_StackPos<DU_NSTACK-1)	m_Stack[++m_StackPos]=i+1;
				else NextJob=0x10000000;
			}
			break;

		case DUT_RETURN:
			if (m_StackPos==0) NextJob=0x10000000;
			else NextJob=m_Stack[m_StackPos--];
			break;
		case DUT_SETINT:
				m_IntArr[m_ArrDrawWParam[i]]=(int)m_ArrDrawLParam[i];
				break;
		case DUT_SETDOUBLE:
			if (m_ArrDrawLParam[i]!=NULL)
				m_DoubleArr[m_ArrDrawWParam[i]]=*((double *)m_ArrDrawLParam[i]);
			break;
		case DUT_SETPOINT:
			if (m_ArrDrawLParam[i]!=NULL)
				m_PointArr[m_ArrDrawWParam[i]]=*((CPoint *)m_ArrDrawLParam[i]);
			break;
		case DUT_SETRECT:
			if (m_ArrDrawLParam[i]!=NULL)
				m_RectArr[m_ArrDrawWParam[i]]=*((CRect *)m_ArrDrawLParam[i]);
			break;
		case DUT_SETCOLOR:
			if (m_ArrDrawWParam[i]<m_nRGBArray)
				m_RGBArr[m_ArrDrawWParam[i]]=(COLORREF)m_ArrDrawLParam[i];
			break;
		case DUT_SETREGION:
			if (m_ArrDrawWParam[i]<m_nRgnArray && m_RgnArr[m_ArrDrawWParam[i]]!=NULL)
			{
				char *str=new char [strlen(m_RgnArr[m_ArrDrawWParam[i]]->CreationString)+20];
				sprintf(str,"SetRegion %s",(LPCSTR)m_RgnArr[m_ArrDrawWParam[i]]->CreationString);
				DoMethod(str,NULL);
				delete[] str;
			}
			break;
		case DUT_COPYREGION:
			if (m_ArrDrawWParam[i]<m_nRgnArray && m_RgnArr[m_ArrDrawWParam[i]]!=NULL &&
				(UINT)m_ArrDrawLParam[i]<m_nRgnArray && m_RgnArr[m_ArrDrawLParam[i]]!=NULL)
					m_RgnArr[m_ArrDrawWParam[i]]->CopyRgn(m_RgnArr[m_ArrDrawLParam[i]]);
			break;
		case DUT_OFFSETREGION:
			if (m_ArrDrawLParam[i]!=NULL)
			{
				PDRAWITEMDATANUM did=(PDRAWITEMDATANUM)m_ArrDrawLParam[i];
				if ((UINT)did->i1<m_nRgnArray && m_RgnArr[did->i1]!=NULL)
					m_RgnArr[did->i1]->OffsetRgn(did->i2,did->i3);
			}
			break;
		case DUT_OFFSETPREGION:
			if (m_ArrDrawWParam[i]<m_nRgnArray && m_RgnArr[m_ArrDrawWParam[i]]!=NULL)
			{
				if (m_ArrDrawLParam[i]>=0)
				{
					if ((UINT)m_ArrDrawLParam[i]<m_nPointArray)
						m_RgnArr[m_ArrDrawWParam[i]]->OffsetRgn(m_PointArr[m_ArrDrawLParam[i]]);
				}
				else
					if ((UINT)(-m_ArrDrawLParam[i]-1)*2<m_nDoubleArray)
						m_RgnArr[m_ArrDrawWParam[i]]->OffsetRgn((int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*2],(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*2+1]);
			}
			break;
		case DUT_REGIONFROMPATH:
			{
				if (m_ArrDrawWParam[i]>500) break;
				if (m_ArrDrawWParam[i]>=m_nRgnArray)
				{
					CRgnExt **tmp=new CRgnExt * [m_ArrDrawWParam[i]+1];
					UINT i22;
					for( i22=0; i22<m_nRgnArray;i22++)
						tmp[i22]=m_RgnArr[i22];
					m_nRgnArray=m_ArrDrawWParam[i22]+1;
					for(;i22<m_nRgnArray;i22++)
						tmp[i22]=NULL;
					delete[] m_RgnArr;
					m_RgnArr=tmp;
				}
				else 
					if (m_RgnArr[m_ArrDrawWParam[i]]!=NULL) 
					{
						m_RgnArr[m_ArrDrawWParam[i]]->DeleteObject();
						delete m_RgnArr[m_ArrDrawWParam[i]]; 
						m_RgnArr[m_ArrDrawWParam[i]]=NULL; 
					}
				m_RgnArr[m_ArrDrawWParam[i]]=new CRgnExt;
				m_RgnArr[m_ArrDrawWParam[i]]->CreationString.Format("%d,/*FORMPATH*/",m_ArrDrawWParam[i]);
				m_RgnArr[m_ArrDrawWParam[i]]->CreateFromPath(pDC);
			}
			break;
		case DUT_COMBINEREGION:
			if (m_ArrDrawLParam[i]!=NULL)
			{//nRgn,nRgnWith,Style
				PDRAWITEMDATANUM did=(PDRAWITEMDATANUM)m_ArrDrawLParam[i];
				if ((UINT)did->i1<m_nRgnArray && m_RgnArr[did->i1]!=NULL
					&& (UINT)did->i2<m_nRgnArray && m_RgnArr[did->i2]!=NULL
					 && (UINT)did->i3<m_nRgnArray && m_RgnArr[did->i3]!=NULL)
					m_RgnArr[did->i1]->CombineRgn(m_RgnArr[did->i2],m_RgnArr[did->i3],did->i4);
			}
			break;
		case DUT_FILLRGN://nRgn,nBrush
			if (m_ArrDrawWParam[i]<m_nRgnArray && m_RgnArr[m_ArrDrawWParam[i]]!=NULL
				&& (UINT)m_ArrDrawLParam[i]<m_nBrushArray && m_BrushArr[m_ArrDrawLParam[i]]!=NULL)
				pDC->FillRgn(m_RgnArr[m_ArrDrawWParam[i]],m_BrushArr[m_ArrDrawLParam[i]]);
			break;
		case DUT_FRAMERGN:
			if (m_ArrDrawLParam[i]!=NULL)
			{//nRgn,nBrush,xWidth,yWidth
				PDRAWITEMDATANUM did=(PDRAWITEMDATANUM)m_ArrDrawLParam[i];
				if ((UINT)did->i1<m_nRgnArray && m_RgnArr[did->i1]!=NULL
					&& (UINT)did->i2<m_nBrushArray && m_BrushArr[did->i2]!=NULL)
					pDC->FrameRgn(m_RgnArr[did->i1],m_BrushArr[did->i2],did->i3,did->i4);
			}
			break;
		case DUT_INVERTRGN://nRgn
			if (m_ArrDrawWParam[i]<m_nRgnArray && m_RgnArr[m_ArrDrawWParam[i]]!=NULL)
				pDC->InvertRgn(m_RgnArr[m_ArrDrawWParam[i]]);
			break;
		case DUT_PAINTRGN://nRgn
			if (m_ArrDrawWParam[i]<m_nRgnArray && m_RgnArr[m_ArrDrawWParam[i]]!=NULL)
				pDC->PaintRgn(m_RgnArr[m_ArrDrawWParam[i]]);
			break;
		case DUT_BOUNDSRECT://
			if (m_ArrDrawLParam[i]!=NULL)
				pDC->SetBoundsRect((CRect *)m_ArrDrawLParam[i],m_ArrDrawWParam[i]);
			break;
		case DUT_BOUNDSRECTR:
			if (m_ArrDrawLParam[i]>=0 && (UINT)m_ArrDrawLParam[i]<m_nRectArray)
				pDC->SetBoundsRect(m_RectArr[m_ArrDrawLParam[i]],m_ArrDrawWParam[i]);
			else
			if (m_ArrDrawLParam[i]<0 && (UINT)(-m_ArrDrawLParam[i])*4<m_nDoubleArray)
				pDC->SetBoundsRect(
						CRect(	(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4],
								(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4+1],
								(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4+2],
								(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4+3]),
								m_ArrDrawWParam[i]);
			break;
		case DUT_GETCLIPBOX:
		case DUT_GETBOUNDSR:
			{
				CRect re;
				switch(m_ArrDrawType[i])
				{
				case DUT_GETCLIPBOX:
					pDC->GetClipBox(re);break;
				case DUT_GETBOUNDSR:
					pDC->GetBoundsRect(re,DCB_RESET);break;
				}

				if (m_ArrDrawWParam[i]<m_nRectArray)
					m_RectArr[m_ArrDrawWParam[i]]=re;
				else
				if ((UINT)(-((int)m_ArrDrawWParam[i]))*4-1<m_nDoubleArray)
				{
					m_DoubleArr[(-(int)m_ArrDrawWParam[i]-1)*4]=re.left;
					m_DoubleArr[(-(int)m_ArrDrawWParam[i]-1)*4+1]=re.top;
					m_DoubleArr[(-(int)m_ArrDrawWParam[i]-1)*4+2]=re.right;
					m_DoubleArr[(-(int)m_ArrDrawWParam[i]-1)*4+3]=re.bottom;
				}
			}
			break;
		case DUT_SELCLIPREGION:
			if (m_ArrDrawWParam[i]<m_nRgnArray && m_RgnArr[m_ArrDrawWParam[i]]!=NULL)
				pDC->SelectClipRgn(m_RgnArr[m_ArrDrawWParam[i]],m_ArrDrawLParam[i]);
			else
				pDC->SelectClipRgn(NULL);
			break;
		case DUT_EXCLRECT:
			if (m_ArrDrawLParam[i]!=NULL)
				pDC->ExcludeClipRect((CRect *)m_ArrDrawLParam[i]);
			break;
		case DUT_EXCLRECTR:
			if (m_ArrDrawLParam[i]>=0 && (UINT)m_ArrDrawLParam[i]<m_nRectArray)
				pDC->ExcludeClipRect(m_RectArr[m_ArrDrawLParam[i]]);
			else
			if (m_ArrDrawLParam[i]<0 && (UINT)(-m_ArrDrawLParam[i])*4<m_nDoubleArray)
				pDC->ExcludeClipRect(
						CRect(	(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4],
								(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4+1],
								(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4+2],
								(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4+3])
								);
			break;
		case DUT_EXCLUPDRGN:
			if (referGPU!=NULL && (UINT)m_ArrDrawLParam[i]<(*referGPU)->m_NGPUNIT && referGPU[m_ArrDrawLParam[i]]->UnitHWND!=NULL)
				pDC->ExcludeUpdateRgn(CWnd::FromHandle(referGPU[m_ArrDrawLParam[i]]->UnitHWND));
			break;
		case DUT_INCLRECT:
			if (m_ArrDrawLParam[i]!=NULL)
				pDC->IntersectClipRect((CRect *)m_ArrDrawLParam[i]);
			break;
		case DUT_INCLRECTR:
			if (m_ArrDrawLParam[i]>=0 && (UINT)m_ArrDrawLParam[i]<m_nRectArray)
				pDC->IntersectClipRect(m_RectArr[m_ArrDrawLParam[i]]);
			else
			if (m_ArrDrawLParam[i]<0 && (UINT)(-m_ArrDrawLParam[i])*4<m_nDoubleArray)
				pDC->IntersectClipRect(
						CRect(	(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4],
								(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4+1],
								(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4+2],
								(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*4+3])
								);
			break;
		case DUT_OFFSETCREGION://dx,dy
			pDC->OffsetClipRgn(m_ArrDrawWParam[i],m_ArrDrawLParam[i]);
			break;
		case DUT_OFFSETPCREGION:
			if (m_ArrDrawLParam[i]>=0 && (UINT)m_ArrDrawLParam[i]<m_nPointArray)
				pDC->OffsetClipRgn(m_PointArr[m_ArrDrawLParam[i]].x,m_PointArr[m_ArrDrawLParam[i]].y);
			else
			if (m_ArrDrawLParam[i]<0 && (UINT)(-m_ArrDrawLParam[i])*2<m_nDoubleArray)
				pDC->OffsetClipRgn(
						(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*2],
						(int)m_DoubleArr[(-m_ArrDrawLParam[i]-1)*2+1]
						);
			break;
		case DUT_IFGOTO:
		case DUT_IFGOSUB:
			if (m_ArrDrawLParam[i]!=NULL)
			{
				double d1=0.,d2=0.;
				PDRAWITEMDATANUM did=(PDRAWITEMDATANUM)m_ArrDrawLParam[i];
				switch(did->i1)
				{
				case 0x100:
					if ((UINT)did->d1<m_nDoubleArray)
						d1=m_DoubleArr[(UINT)did->d1];
					break;
				case 0x200:
					if ((UINT)did->d1<m_nIntArray)
						d1=m_IntArr[(UINT)did->d1];
					break;
				case 0x800:
					if ((UINT)did->d1<m_nDrTimerArray)
						d1=m_DrTimerArr[(UINT)did->d1].dValue;
					break;
				case 0x400:
				case 0x0:
					d1=did->d1;	break;
				}
				switch(did->i2)
				{
				case 0x100:
					if ((UINT)did->d2<m_nDoubleArray)
						d2=m_DoubleArr[(UINT)did->d2];
					break;
				case 0x200:
					if ((UINT)did->d2<m_nIntArray)
						d2=m_IntArr[(UINT)did->d2];
					break;
				case 0x800:
					if ((UINT)did->d2<m_nDrTimerArray)
						d2=m_DrTimerArr[(UINT)did->d2].dValue;
					break;
				case 0x400:
				case 0x0:
					d2=did->d2;	break;
				}

				BOOL res=FALSE;
				switch(did->id3)
				{
				case 0x1: res=(d1==d2); break;
				case 0x2: res=(d1<d2);	break;
				case 0x3: res=(d1<=d2); break;
				case 0x4: res=(d1>d2); break;
				case 0x5: res=(d1>=d2); break;
				case 0x6: res=(d1!=d2); break;
				}

				if (res)
					switch(m_ArrDrawType[i])
					{
					case DUT_IFGOTO:
						NextJob=0x10000000;
						switch(did->id4)
						{
						case 0x1://'-''+' offset
							NextJob=i+did->i4;
							break;
						case 0x2://'&' direct
							if ((UINT)did->i4<m_nIntArray)
								NextJob=m_IntArr[did->i4];
							break;
						case 0x4://'@' offset
							if ((UINT)did->i4<m_nIntArray)
								NextJob=i+m_IntArr[did->i4];
							break;
						case 0x0:// direct
							NextJob=did->i4;
							break;
						}
						if (NextJob==i) NextJob=0x10000000;
						break;
					case DUT_IFGOSUB:
						NextJob=0x10000000;
						switch(did->id4)
						{
						case 0x1://'-''+' offset
							NextJob=i+did->i4;
							break;
						case 0x2://'&' direct
							if ((UINT)did->i4<m_nIntArray)
								NextJob=m_IntArr[did->i4];
							break;
						case 0x4://'@' offset
							if ((UINT)did->i4<m_nIntArray)
								NextJob=i+m_IntArr[did->i4];
							break;
						case 0x0:// direct
							NextJob=did->i4;
							break;
						}

						if (NextJob==i) NextJob=0x10000000;

						if (m_StackPos<DU_NSTACK-1)	m_Stack[++m_StackPos]=i+1;
						else NextJob=0x10000000;
						break;
					}
			}
			break;
		case DUT_ARITHMETIC: 
			if (m_ArrDrawLParam[i]!=NULL)
			{
				PDRAWITEMDATANUM did=(PDRAWITEMDATANUM)m_ArrDrawLParam[i];
				int *i_dst=NULL;
				double *d_dst=NULL,d_oper=0;

				switch(did->i1)
				{
				case 0x100: 
					if ((UINT)did->d1<m_nDoubleArray)
						d_dst=m_DoubleArr+(UINT)did->d1;
					break;
				case 0x200: 
					if ((UINT)did->d1<m_nIntArray)
						i_dst=m_IntArr+(UINT)did->d1;
					break;
				case 0x800: 
					if ((UINT)did->d1<m_nDrTimerArray)
						d_dst=&m_DrTimerArr[(UINT)did->d1].dValue;
					break;
				}

				switch(did->i2)
				{
				case 0x100: 
					if ((UINT)did->d2<m_nDoubleArray)
						d_oper=m_DoubleArr[(UINT)did->d2];
					break;
				case 0x200: 
					if ((UINT)did->d2<m_nIntArray)
						d_oper=m_IntArr[(UINT)did->d2];
					break;
				case 0x400:
					d_oper=did->d2;	
					break;
				case 0x800: 
					if ((UINT)did->d2<m_nDrTimerArray)
						d_oper=m_DrTimerArr[(UINT)did->d2].dValue;
					break;
				}

				switch(did->i3)
				{
				case 0x0001:/*'+'*/	
					if (d_dst!=NULL) *d_dst+=d_oper;
					else if (i_dst!=NULL) *i_dst+=(int)d_oper;
					break;
				case 0x0002:/*'-'*/	
					if (d_dst!=NULL) *d_dst-=d_oper;
					else if (i_dst!=NULL) *i_dst-=(int)d_oper;
					break;
				case 0x0004:/*'*'*/	
					if (d_dst!=NULL) *d_dst*=d_oper;
					else if (i_dst!=NULL) *i_dst*=(int)d_oper;
					break;
				case 0x0008:/*'/'*/	
					if (d_oper!=0)
					{
						if (d_dst!=NULL) *d_dst/=d_oper;
						else if (i_dst!=NULL) *i_dst/=(int)d_oper;
					}
					break;
				case 0x0010:/*'='*/	
					if (d_dst!=NULL) *d_dst=d_oper;
					else if (i_dst!=NULL) *i_dst=(int)d_oper;
					break;
				case 0x0020:/*'|'*/	
					if (d_dst!=NULL) *d_dst=((int)*d_dst)|((int)d_oper);
					else if (i_dst!=NULL) *i_dst|=(int)d_oper;
					break;
				case 0x0040:/*'&'*/	
					if (d_dst!=NULL) *d_dst=((int)*d_dst)&((int)d_oper);
					else if (i_dst!=NULL) *i_dst&=(int)d_oper;
					break;
				case 0x0080:/*'%'*/	
					if (d_dst!=NULL) *d_dst=((int)*d_dst)^((int)d_oper);
					else if (i_dst!=NULL) *i_dst^=(int)d_oper;
					break;
				case 0x0100:/*'!'*/	
					if (d_dst!=NULL) *d_dst=!((int)d_oper);
					else if (i_dst!=NULL) *i_dst=!(int)d_oper;
					break;
				case 0x0200:/*'~'*/	
					if (d_dst!=NULL) *d_dst=pow(*d_dst,d_oper);
					else if (i_dst!=NULL) *i_dst*=(int)pow(*d_dst,d_oper);
					break;
				}
			}
			break;
		case DUT_MATH: 
			if (m_ArrDrawLParam[i]!=NULL)
			{
				PDRAWITEMDATAMATH did= (PDRAWITEMDATAMATH)m_ArrDrawLParam[i];
				if (did->nResults!=0 && did->iFunction!=0)
				{
					int ires[16];
					int iresType[16];
					double dres[16];
					int iArg[16];
					double dArg[16];
					int i22;
					for(i22=0;i22<16;i22++)
					{
						ires[i22]=iArg[i22]=0;dres[i22]=dArg[i22]=0;
						iresType[i22]=0x100;	
						if (i22<did->nArg)
							switch(did->iArgType[i22])
							{
							case 0x100:
								if ((UINT)did->iArgAdress[i22]<m_nDoubleArray)
								{
									iArg[i22]=(int)m_DoubleArr[did->iArgAdress[i22]];
									dArg[i22]=m_DoubleArr[did->iArgAdress[i22]];
								}
								break;
							case 0x200:
								if ((UINT)did->iArgAdress[i22]<m_nIntArray)
								{
									iArg[i22]=m_IntArr[did->iArgAdress[i22]];
									dArg[i22]=m_IntArr[did->iArgAdress[i22]];
								}
								break;
							case 0x400:
								iArg[i22]=(int)did->dConst[i22];
								dArg[i22]=did->dConst[i22];
								break;
							case 0x800:
								if ((UINT)did->iArgAdress[i22]<m_nDrTimerArray)
								{
									iArg[i22]=(int)m_DrTimerArr[did->iArgAdress[i22]].dValue;
									dArg[i22]=m_DrTimerArr[did->iArgAdress[i22]].dValue;
								}
								break;
							}
					}
					
					switch(did->iFunction)
					{
					case  1:  /*ABS*/	
						iresType[0]=0x200;
						ires[0]=abs(iArg[0]);
						break;
					case  2:  /*ACOS*/
						if (dArg[0]>=-1 && dArg[0]<=1)
							dres[0]=acos(dArg[0]);
						break;
					case  3:  /*ASIN*/
						if (dArg[0]>=-1 && dArg[0]<=1)
							dres[0]=asin(dArg[0]);
						break;
					case  4:  /*ATAN*/		dres[0]=atan(dArg[0]);				break;
					case  5:  /*ATAN2*/		dres[0]=atan2(dArg[0],dArg[1]);		break;
					case  6:  /*BESSEL_j0*/	dres[0]=_j0(dArg[0]);				break;
					case  7:  /*BESSEL_j1*/	dres[0]=_j1(dArg[0]);				break;
					case  8:  /*BESSEL_jn*/	dres[0]=_jn(iArg[0],dArg[1]);		break;
					case  9:  /*BESSEL_y0*/ dres[0]=_y0(dArg[0]);				break;
					case 10:  /*BESSEL_y1*/ dres[0]=_y1(dArg[0]);				break;
					case 11:  /*BESSEL_yn*/ dres[0]=_yn(iArg[0],dArg[1]);		break;
					case 12:  /*CABS*/
						{
						   struct _complex number = {dArg[0],dArg[1]};
						   dres[0] = _cabs( number );
						}
						break;
					case 13:  /*CEIL*/		dres[0]=ceil(dArg[0]);				break;
					case 14:  /*CHGSIGN*/	dres[0]=_chgsign(dArg[0]);			break;
					case 15:  /*CLEAR87*/
						iresType[0]=0x200;
						ires[0]=_clear87();
						break;
					case 16:  /*CLEARFP*/
						iresType[0]=0x200;
						ires[0]=_clearfp();
						break;
					case 17:  /*CONTROL87*/
						iresType[0]=0x200;
						ires[0]=_control87(iArg[0],iArg[1]);
						break;
					case 18:  /*CONTROLFP*/
						iresType[0]=0x200;
						ires[0]=_controlfp(iArg[0],iArg[1]);
						break;
					case 19:  /*COPYSIGN*/	dres[0]=_copysign(dArg[0],dArg[1]);	break;
					case 20:  /*COS*/		dres[0]=cos(dArg[0]);				break;
					case 21:  /*COSH*/		dres[0]=cosh(dArg[0]);				break;
					case 22:  /*DIV*/
						{
							div_t retdiv;
							retdiv=div(iArg[0],iArg[1]);
							iresType[0]=0x200;
							ires[0]=retdiv.quot;
							iresType[1]=0x200;
							ires[1]=retdiv.rem;
						}
						break;
					case 23:  /*EXP*/		dres[0]=exp(dArg[0]);				break;
					case 24:  /*FABS*/		dres[0]=fabs(dArg[0]);				break;
					case 25:  /*FINITE*/
						iresType[0]=0x200;
						ires[0]=_finite(dArg[0]);
						break;
					case 26:  /*FLOOR*/		dres[0]=floor(dArg[0]);				break;
					case 27:  /*FMOD*/		dres[0]=fmod(dArg[0],dArg[0]);		break;
					case 28:  /*FPCLASS*/
						iresType[0]=0x200;
						ires[0]=_fpclass(dArg[0]);
						break;
					case 29:  /*FPRESET*/
						iresType[0]=0;
						_fpreset();
						break;
					case 30:  /*FREXP*/
						iresType[1]=0x200;
						dres[0]=frexp(dArg[0],ires+1);
						break;
					case 31:  /*HYPOT*/		dres[0]=_hypot(dArg[0],dArg[1]);	break;
					case 32:  /*ISNAN*/
						iresType[0]=0x200;
						ires[0]=_isnan(dArg[0]);
						break;
					case 33:  /*LABS*/
						iresType[0]=0x200;
						ires[0]=labs(iArg[0]);
						break;
					case 34:  /*LDEXP*/		dres[0]=ldexp(dArg[0],iArg[1]);		break;
					case 35:  /*LDIV*/
						{
							ldiv_t retdiv;
							retdiv=ldiv(iArg[0],iArg[1]);
							iresType[0]=0x200;
							ires[0]=retdiv.quot;
							iresType[1]=0x200;
							ires[1]=retdiv.rem;
						}
						break;
					case 36:  /*LOG*/		dres[0]=log(dArg[0]);			break;
					case 37:  /*LOG10*/		dres[0]=log10(dArg[0]);			break;
					case 38:  /*LOGB*/		dres[0]=_logb(dArg[0]);			break;
					case 39:  /*LROTL*/
						iresType[0]=0x200;
						ires[0]=_lrotl(iArg[0],iArg[1]);
						break;
					case 40:  /*LROTR*/
						iresType[0]=0x200;
						ires[0]=_lrotr(iArg[0],iArg[1]);
						break;
					case 41:  /*MAX*/
						dres[0]=(dArg[0]>dArg[1])?dArg[0]:dArg[1];
						break;
					case 42:  /*MIN*/
						dres[0]=(dArg[0]<dArg[1])?dArg[0]:dArg[1];
						break;
					case 43:  /*MODF*/		dres[0]=modf(dArg[0],dres+1);			break;
					case 44:  /*NEXTAFTER*/	dres[0]=_nextafter(dArg[0],dArg[1]);	break;
					case 45:  /*POW*/		dres[0]=pow(dArg[0],dArg[1]);			break;
					case 46:  /*RAND*/
						iresType[0]=0x200;
						ires[0]=rand();
						break;
					case 47:  /*ROTL*/
						iresType[0]=0x200;
						ires[0]=_rotl(iArg[0],iArg[1]);
						break;
					case 48:  /*ROTR*/
						iresType[0]=0x200;
						ires[0]=_rotr(iArg[0],iArg[1]);
						break;
					case 49:  /*SCALB*/		dres[0]=_scalb(dArg[0],iArg[1]);	break;
					case 50:  /*SIN*/		dres[0]=sin(dArg[0]);			break;
					case 51:  /*SINH*/		dres[0]=sinh(dArg[0]);			break;
					case 52:  /*SQRT*/
						if (dArg[0]>=0)		dres[0]=sqrt(dArg[0]);	
						break;
					case 53:  /*SRAND*/		srand(iArg[0]);				break;
					case 54:  /*STATUS87*/
						iresType[0]=0x200;
						ires[0]=_status87();
						break;
					case 55:  /*STATUSFP*/
						iresType[0]=0x200;
						ires[0]=_statusfp();
						break;
					case 56:  /*TAN*/		dres[0]=tan(dArg[0]);			break;
					case 57:  /*TANH*/		dres[0]=tanh(dArg[0]);			break;
					}

					for(i22=0;i22<did->nResults;i22++)
						if (iresType[i22]==0x100)
							switch(did->iResultsType[i22])
							{
							case 0x100:
								if ((UINT)did->iResultsArr[i22]<m_nDoubleArray)	m_DoubleArr[did->iResultsArr[i22]]=dres[i22];
								break;
							case 0x200:
								if ((UINT)did->iResultsArr[i22]<m_nIntArray)		m_IntArr[did->iResultsArr[i22]]=(int)dres[i22];
								break;
							case 0x800:
								if ((UINT)did->iResultsArr[i22]<m_nDrTimerArray)	m_DrTimerArr[did->iResultsArr[i22]].dValue=ires[i22];
								break;
							}
						else
						if (iresType[i22]==0x200)
							switch(did->iResultsType[i22])
							{
							case 0x100:
								if ((UINT)did->iResultsArr[i22]<m_nDoubleArray)	m_DoubleArr[did->iResultsArr[i22]]=ires[i22];
								break;
							case 0x200:
								if ((UINT)did->iResultsArr[i22]<m_nIntArray)		m_IntArr[did->iResultsArr[i22]]=ires[i22];
								break;
							case 0x800:
								if ((UINT)did->iResultsArr[i22]<m_nDrTimerArray)	m_DrTimerArr[did->iResultsArr[i22]].dValue=ires[i22];
								break;
							}
				}
			}
			break;
		case DUT_SETRGB: //  TNNN,TNNN,TNNN
			if (m_ArrDrawLParam[i]!=NULL)
			{
				PDRAWITEMDATANUM did=(PDRAWITEMDATANUM)m_ArrDrawLParam[i];
				int c1=0,c2=0,c3=0;
				switch(did->i1)
				{
				case 0x100:
					if ((UINT)did->id1<m_nDoubleArray)	c1=(int)m_DoubleArr[did->id1];
					break;
				case 0x200:
					if ((UINT)did->id1<m_nIntArray)		c1=m_IntArr[did->id1];
					break;
				case 0x800:
					if ((UINT)did->id1<m_nDrTimerArray)	c1=(int)m_DrTimerArr[did->id1].dValue;
					break;
				default:	c1=did->id1;break;
				}
				switch(did->i2)
				{
				case 0x100:
					if ((UINT)did->id2<m_nDoubleArray)	c2=(int)m_DoubleArr[did->id2];
					break;
				case 0x200:
					if ((UINT)did->id2<m_nIntArray)		c2=m_IntArr[did->id2];
					break;
				case 0x800:
					if ((UINT)did->id2<m_nDrTimerArray)	c2=(int)m_DrTimerArr[did->id2].dValue;
					break;
				default:	c2=did->id2;break;
				}
				switch(did->i3)
				{
				case 0x100:
					if ((UINT)did->id3<m_nDoubleArray)	c3=(int)m_DoubleArr[did->id3];
					break;
				case 0x200:
					if ((UINT)did->id3<m_nIntArray)		c3=m_IntArr[did->id3];
					break;
				case 0x800:
					if ((UINT)did->id3<m_nDrTimerArray)	c3=(int)m_DrTimerArr[did->id3].dValue;
					break;
				default:	c3=did->id3;break;
				}

				if ((UINT)did->i4<m_nRGBArray)	m_RGBArr[did->i4]=RGB(c1,c2,c3);
			}
			break;
		case DUT_SETPENCOLOR:
			if (m_ArrDrawWParam[i]<m_nPenArray && m_PenArr[m_ArrDrawWParam[i]]!=0 && (UINT)m_ArrDrawLParam[i]<m_nRGBArray)
			{
				BOOL repFlg=FALSE;
				if (pDC->GetCurrentPen()==m_PenArr[m_ArrDrawWParam[i]])
				{
					pDC->SelectObject(oldPen);
					repFlg=TRUE;
				}
				char tmps[100];
				int r,g,b;
				r=GetRValue(m_RGBArr[m_ArrDrawLParam[i]]);
				g=GetGValue(m_RGBArr[m_ArrDrawLParam[i]]);
				b=GetBValue(m_RGBArr[m_ArrDrawLParam[i]]);
				sprintf(tmps,"44 %d,%d,%d,%d",m_ArrDrawWParam[i],r,g,b);
				DoMethod(tmps,NULL);
				if (repFlg) oldPen=pDC->SelectObject(m_PenArr[m_ArrDrawWParam[i]]);
			}
			break;
		case DUT_PENWIDTH:
			if (m_ArrDrawWParam[i]<m_nPenArray && m_PenArr[m_ArrDrawWParam[i]]!=0)
			{
				BOOL repFlg=FALSE;
				if (pDC->GetCurrentPen()==m_PenArr[m_ArrDrawWParam[i]])
				{
					pDC->SelectObject(oldPen);
					repFlg=TRUE;
				}
				char tmps[100];
				sprintf(tmps,"43 %d,%d",m_ArrDrawWParam[i],m_ArrDrawLParam[i]);
				DoMethod(tmps,NULL);
				if (repFlg) oldPen=pDC->SelectObject(m_PenArr[m_ArrDrawWParam[i]]);
			}
			break;
		case DUT_GETWINDOWRECT: //nRect,nObject
		case DUT_GETCLIENTRECT: //nRect,nObject
		case DUT_MOVEWINDOW: //nObject,nRect
			{
				HWND hw=NULL;
				int nRect=m_ArrDrawWParam[i];
				switch(m_ArrDrawLParam[i])
				{
				case -1:	hw=m_hWnd;	break;
				case -2:	hw=GetDesktopWindow()->m_hWnd;	break;
				default:	if (m_ArrDrawLParam[i]>=0 && referGPU && (UINT)m_ArrDrawLParam[i]<(*referGPU)->m_NGPUNIT && referGPU[m_ArrDrawLParam[i]]!=NULL)
								hw=referGPU[m_ArrDrawLParam[i]]->UnitHWND;
					break;
				}
				if (hw!=NULL)
				{
					CRect re(0,0,0,0);
					switch(m_ArrDrawType[i])
					{
					case DUT_GETWINDOWRECT:		::GetWindowRect(hw,&re);	break;
					case DUT_GETCLIENTRECT:		::GetClientRect(hw,&re);	break;
					case DUT_MOVEWINDOW:		break;
					}

					if (m_ArrDrawType[i]==DUT_MOVEWINDOW)	PostMessage(GPN_DRAWMOVE,(WPARAM)hw,(LPARAM)nRect);
					else
					if ((UINT)nRect<m_nRectArray) m_RectArr[nRect]=re;
						else
						if (nRect<0 && (UINT)(-nRect-1)*4<m_nDoubleArray)
						{
							m_DoubleArr[nRect=(-nRect-1)*4]=re.left;
							m_DoubleArr[nRect+1]=re.top;
							m_DoubleArr[nRect+2]=re.right;
							m_DoubleArr[nRect+3]=re.bottom;
						}
				}
			}
			break;
		case DUT_RECTOFFSETP:	//nRect,nPoint
		case DUT_RECTCENTER:	//nRect,nPoint
		case DUT_RECTOFFSETR:	//nRect,nRectOff
		case DUT_RECTOFFSETRM:	//nRect,nRectOff
		case DUT_RECTOFFSETPM:	//nRect,nRectOff
		case DUT_RECTSUBSTR:	//nRect,nRectSub
		case DUT_RECTINTERS:	//nRect,nRectInter
		case DUT_RECTUNION:		//nRect,nRectUnion
		case DUT_RECTHEIGHT:	//nRect,Res
		case DUT_RECTWIDTH:		//nRect,Res
		case DUT_RECTISNULL:	//nRect,Res
		case DUT_RECTISEMPTY:	//nRect,Res
		case DUT_RECTINFLATE:	//nRect,dx,dy
		case DUT_RECTDEFLATE:	//nRect,dx,dy
		case DUT_RECTOFFSET:	//nRect,dx,dy
		case DUT_RECTNORMALIZE:	//nRect
		case DUT_RECTEQUAL:		//nRect,nRect,Res
			{
				int nRect=m_ArrDrawWParam[i];
				int n2=m_ArrDrawLParam[i];
				int n2dP=(-n2-1)*2;
				int n2dR=n2dP*2;
				int iDou=0;
				CRect re(0,0,0,0);

				if (m_ArrDrawType[i]==DUT_RECTPTIN || m_ArrDrawType[i]==DUT_RECTEQUAL)
					nRect=m_ArrDrawWParam[i]/0x10000;

				if ((UINT)nRect<m_nRectArray) re=m_RectArr[nRect];
				else
				if (nRect<0 && (UINT)(-nRect-1)*4<m_nDoubleArray)
				{
					iDou=1;
					re.left		=(int)m_DoubleArr[nRect=(-nRect-1)*4];
					re.top		=(int)m_DoubleArr[nRect+1];
					re.right	=(int)m_DoubleArr[nRect+2];
					re.bottom	=(int)m_DoubleArr[nRect+3];
				}
				else iDou=2;

				switch(m_ArrDrawType[i])
				{
				case DUT_RECTOFFSETP:	//nRect,nPoint
					if ((UINT)n2<m_nPointArray)		re.OffsetRect(m_PointArr[n2]);
					else
						if ((UINT)n2dP<m_nDoubleArray)
							re.OffsetRect((int)m_DoubleArr[n2dP],(int)m_DoubleArr[n2dP+1]);
					break;
				case DUT_RECTOFFSETPM:	//nRect,nPoint
					if ((UINT)n2<m_nPointArray)		re.OffsetRect(-m_PointArr[n2]);
					else
						if ((UINT)n2dP<m_nDoubleArray)
							re.OffsetRect(-(int)m_DoubleArr[n2dP],-(int)m_DoubleArr[n2dP+1]);
					break;
				case DUT_RECTCENTER:	//nRect,nPoint
					iDou=2;
					if ((UINT)n2<m_nPointArray) m_PointArr[n2]=re.CenterPoint();
					else
						if ((UINT)n2dP<m_nDoubleArray)
						{
							m_DoubleArr[n2dP]=re.CenterPoint().x;
							m_DoubleArr[n2dP+1]=re.CenterPoint().y;
						}
					break;
				case DUT_RECTOFFSETR:	//nRect,nRectOff
				case DUT_RECTOFFSETRM:	//nRect,nRectOff
				case DUT_RECTSUBSTR:	//nRect,nRectSub
				case DUT_RECTINTERS:	//nRect,nRectInter
				case DUT_RECTUNION:		//nRect,nRectUnion
					{
						CRect re2(0,0,0,0);
						if ((UINT)n2<m_nRectArray)	re2=m_RectArr[n2];
						else
							if ((UINT)n2dR<m_nDoubleArray)
								re2.SetRect((int)m_DoubleArr[n2dR],(int)m_DoubleArr[n2dR+1],(int)m_DoubleArr[n2dR+2],(int)m_DoubleArr[n2dR+3]);
						switch(m_ArrDrawType[i])
						{
						case DUT_RECTOFFSETR:	re.OffsetRect(re2.TopLeft());	break;
						case DUT_RECTOFFSETRM:	re.OffsetRect(-re2.TopLeft());	break;
						case DUT_RECTSUBSTR:	re.SubtractRect(re,re2);		break;
						case DUT_RECTINTERS:	re.IntersectRect(re,re2);		break;
						case DUT_RECTUNION:		re.UnionRect(re,re2);			break;
						}
					}
					break;
				case DUT_RECTHEIGHT:	//nRect,Res
				case DUT_RECTWIDTH:		//nRect,Res
				case DUT_RECTISNULL:	//nRect,Res
				case DUT_RECTISEMPTY:	//nRect,Res
					{
						iDou=2;
						int iRes=0;
						switch(m_ArrDrawType[i])
						{
						case DUT_RECTHEIGHT:	iRes=re.Height();		break;
						case DUT_RECTWIDTH:		iRes=re.Width();		break;
						case DUT_RECTISNULL:	iRes=re.IsRectNull();	break;
						case DUT_RECTISEMPTY:	iRes=re.IsRectEmpty();	break;
						}
						switch(n2>>16)
						{
						case 0x100:
							if (UINT(n2&0xFFFF)<m_nDoubleArray)
								m_DoubleArr[n2&0xFFFF]=iRes;
							break;
						case 0x200:
							if (UINT(n2&0xFFFF)<m_nIntArray)
								m_IntArr[n2&0xFFFF]=iRes;
							break;
						}
					}
					break;
				case DUT_RECTINFLATE:	//nRect,dx,dy
					re.InflateRect(CSize(n2&0xFFFF,n2>>16));	break;
				case DUT_RECTDEFLATE:	//nRect,dx,dy
					re.DeflateRect(CSize(n2&0xFFFF,n2>>16));	break;
				case DUT_RECTOFFSET:	//nRect,dx,dy
					re.OffsetRect(n2&0xFFFF,n2>>16);			break;
				case DUT_RECTNORMALIZE:	//nRect
					re.NormalizeRect();
					break;
				}

				switch(iDou)
				{
					case 0:	m_RectArr[nRect]=re; break;
					case 1:
						m_DoubleArr[nRect  ]=re.left;
						m_DoubleArr[nRect+1]=re.top;
						m_DoubleArr[nRect+2]=re.right;
						m_DoubleArr[nRect+3]=re.bottom;
						break;
				}
			}
			break;
		case DUT_SCRTOCL:	//nRect,nObject
		case DUT_CLTOSCR:	//nRect,nObject
			{
				HWND hw=NULL;
				switch(m_ArrDrawLParam[i])
				{
				case -1:	hw=m_hWnd;	break;
				case -2:	hw=GetDesktopWindow()->m_hWnd;	break;
				default:	if (m_ArrDrawLParam[i]>=0 && referGPU && (UINT)m_ArrDrawLParam[i]<(*referGPU)->m_NGPUNIT && referGPU[m_ArrDrawLParam[i]]!=NULL)
								hw=referGPU[m_ArrDrawLParam[i]]->UnitHWND;
					break;
				}
				if (hw!=NULL)
				{
					if (m_ArrDrawWParam[i]<m_nRectArray)
						switch(m_ArrDrawType[i])
						{
						case DUT_SCRTOCL:
							::ScreenToClient(hw,((LPPOINT)&m_RectArr[m_ArrDrawWParam[i]])); 
							::ScreenToClient(hw,((LPPOINT)&m_RectArr[m_ArrDrawWParam[i]])+1);
							break;
						case DUT_CLTOSCR:
							::ClientToScreen(hw,((LPPOINT)&m_RectArr[m_ArrDrawWParam[i]])); 
							::ClientToScreen(hw,((LPPOINT)&m_RectArr[m_ArrDrawWParam[i]])+1);
						}
					else
					if ((int)m_ArrDrawWParam[i]<0)
					{
						int nRect=m_ArrDrawWParam[i];
						nRect=(-nRect-1)*4;
						if ((UINT)nRect<m_nDoubleArray)
						{
							CRect re((int)m_DoubleArr[nRect],(int)m_DoubleArr[nRect+1],(int)m_DoubleArr[nRect+2],(int)m_DoubleArr[nRect+3]);
							switch(m_ArrDrawType[i])
							{
							case DUT_SCRTOCL:
								::ScreenToClient(hw,((LPPOINT)&re)); 
								::ScreenToClient(hw,((LPPOINT)&re)+1);
								break;
							case DUT_CLTOSCR:
								::ClientToScreen(hw,((LPPOINT)&re)); 
								::ClientToScreen(hw,((LPPOINT)&re)+1);
								break;
							}
							m_DoubleArr[nRect  ]=re.left;
							m_DoubleArr[nRect+1]=re.top;
							m_DoubleArr[nRect+2]=re.right;
							m_DoubleArr[nRect+3]=re.bottom;
						}
					}
				}
			}
			break;
		case DUT_STRCATS:	//nStrDest,nStrSource
			if (m_ArrDrawWParam[i]<m_nStringArray && (UINT)m_ArrDrawLParam[i]<m_nStringArray)
				m_StringArr[m_ArrDrawWParam[i]]+=m_StringArr[m_ArrDrawLParam[i]];
			break;
		case DUT_STRCAT:	//nStrDest,TEXT
			if (m_ArrDrawLParam[i]!=NULL && ((PDRAWITEMDATASTR)m_ArrDrawLParam[i])->nDest<m_nStringArray)
				m_StringArr[m_ArrDrawWParam[i]]+=((PDRAWITEMDATASTR)m_ArrDrawLParam[i])->text;
			break;
		case DUT_ITOSTR:	//nStrDest,nInt,STRFORMAT
			if (m_ArrDrawLParam[i]!=NULL)
			{
				PDRAWITEMDATASTR did=(PDRAWITEMDATASTR)m_ArrDrawLParam[i];
				if ((UINT)did->nSourse<m_nIntArray && did->nDest<m_nStringArray)
				{
					if (did->format.Find("%",0)>=0)
						try
						{
						m_StringArr[did->nDest].Format(did->format,m_IntArr[did->nSourse]);
						}catch(...)
						{
							GPC.m_ErrReport.GPWriteErrorLog("GPDrawWnd", "PaintToCDC 5751","");
							AfxMessageBox("ERROR draw 5711",MB_OK);
						}
					else
						m_StringArr[did->nDest]=did->format;
				}
			}
			break;
		case DUT_DTOSTR:	//nStrDest,nDouble,STRFORMAT
			if (m_ArrDrawLParam[i]!=NULL)
			{
				PDRAWITEMDATASTR did=(PDRAWITEMDATASTR)m_ArrDrawLParam[i];
				if ((UINT)did->nSourse<m_nDoubleArray && did->nDest<m_nStringArray)
				{
					if (did->format.Find("%",0)>=0)
						try
						{
						m_StringArr[did->nDest].Format(did->format,m_DoubleArr[did->nSourse]);
						}catch(...)
					{
							GPC.m_ErrReport.GPWriteErrorLog("GPDrawWnd", "PaintToCDC 5773","");
							AfxMessageBox("ERROR draw 5727",MB_OK);;
						}
					else
						m_StringArr[did->nDest]=did->format;
				}
			}
			break;
		case DUT_TTOSTR:	//nStrDest,nDouble,STRFORMAT
			if (m_ArrDrawLParam[i]!=NULL)
			{
				PDRAWITEMDATASTR did=(PDRAWITEMDATASTR)m_ArrDrawLParam[i];
				if ((UINT)did->nSourse<m_nDrTimerArray && did->nDest<m_nStringArray)
				{
					if (did->format.Find("%",0)>=0)
						try
						{
							m_StringArr[did->nDest].Format(did->format,m_DrTimerArr[did->nSourse].dValue);
						}catch(...)
					{
							GPC.m_ErrReport.GPWriteErrorLog("GPDrawWnd", "PaintToCDC 5792","");
							AfxMessageBox("ERROR draw 5743",MB_OK);;
						}
					else
						m_StringArr[did->nDest]=did->format;
				}
			}
			break;



		case DUT_NONE: break;
		default:
			break;
		}
		if (NextJob<0xFFFFFFF0)
		{
			i=NextJob-1;
			NextJob=0xFFFFFFFF;
		}
	}

	if (oldBkMode!=-123456)	pDC->SetBkMode(oldBkMode);
	if (oldPfMode!=-123456)	pDC->SetPolyFillMode(oldPfMode);
	if (oldROP2Mode!=-123456)	pDC->SetROP2(oldROP2Mode);
	if (oldMapMode!=-123456)	pDC->SetMapMode(oldMapMode);

	if (oldPen!=NULL)	pDC->SelectObject(oldPen);
	if (oldBrush!=NULL)	pDC->SelectObject(oldBrush);
	if (oldFont!=NULL)	pDC->SelectObject(oldFont);
}

void GPDrawWnd::SetPrintAlign(CDC *pDC, HDC hdcPrn)
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
			CRect re;
			GetWindowRect(&re);
			lsz=re.Size();
		}
		CSize lTLmarg=TLmarg;
		CSize lBRmarg=BRmarg;
		pDC->DPtoLP(&lTLmarg);
		pDC->DPtoLP(&lBRmarg);
		pDC->SetWindowExt(lsz.cx+(lTLmarg.cx+lBRmarg.cx)/2,lsz.cy+(lTLmarg.cy+lBRmarg.cy)/2);
	}

	if (m_PrintWinOrg.x!=-12345)
		pDC->SetWindowOrg(m_PrintWinOrg);

	if (m_PrintVieExt.cx!=-12345)
		pDC->SetViewportExt(m_PrintVieExt);
	else
		pDC->SetViewportExt(cxPage, cyPage) ;

	if (m_PrintVieOrg.x!=-12345)
		pDC->SetViewportOrg(m_PrintVieOrg);
	else
		pDC->SetViewportOrg (TLmarg.cx,TLmarg.cy) ;
} 

void GPDrawWnd::PrintDrawWnd(int Dlg,int Orient,int Paper)
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
		SetPrintAlign(pDC, hdcPrn);// set the printing alignment
		PaintToCDC(pDC);
		pDC->EndPage();            // end a page

		pDC->EndDoc();             // end a print job

		pDC->Detach();             // detach the printer DC
		delete pDC;
	}

	delete printDlg;
}




void GPDrawWnd::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent>=TIMER_DRAW_START_ID && nIDEvent<TIMER_DRAW_START_ID+m_nDrTimerArray)
	{
		m_uRedrawFlag=1;
		if (m_bAutoRedraw) Invalidate();
		UINT nTm=nIDEvent-TIMER_DRAW_START_ID;
		m_DrTimerArr[nTm].dValue+=m_DrTimerArr[nTm].dDelta;
		if (m_DrTimerArr[nTm].bRedraw) Invalidate();
		if (m_DrTimerArr[nTm].dValue>m_DrTimerArr[nTm].dStop)
		{
			KillTimer(nIDEvent);
			m_DrTimerArr[nTm].bisRun=FALSE;
		}
		else	m_DrTimerArr[nTm].bisRun=TRUE;
	}

	CWnd::OnTimer(nIDEvent);
}

void GPDrawWnd::DeletePaintObj()
{
	if (m_hDCBitmap) DeleteObject(m_hDCBitmap);
	m_hDCBitmap=NULL;
}

void GPDrawWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	DeletePaintObj();
	m_uRedrawFlag=TRUE;

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
	}
}

BOOL GPDrawWnd::OnEraseBkgnd(CDC* pDC) 
{
	BOOL ret=m_bEraseBkg;
	if (m_bEraseBkg) 
		ret=CWnd::OnEraseBkgnd(pDC);
	
	return ret;
}

void GPDrawWnd::OnDragMouseHover() 
{
	if (referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(GPC.m_DragDrop.DragName)<0xFFFFFFFFL)
	{
		// Reset the timer.
		::SetTimer (GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nScrollInterval, NULL);

		// Get the current cursor position and window height.
		DWORD dwPos = ::GetMessagePos ();
		CPoint point (LOWORD (dwPos), HIWORD (dwPos));
		ScreenToClient (&point);

		CRect rect;
		GetClientRect (rect);
		int cy = rect.Height ();

		referGPU[UnitId&0xFFFF]->SendDropHoverEvent("",&GPC.m_DragDrop,&point);

		// Scroll the window if the cursor is near the top or bottom.
		if (point.y >= 0 && point.y <= referGPU[UnitId&0xFFFF]->m_nScrollMargin)
		{
			GPC.m_DragDrop.pImageList->DragShowNolock (FALSE);
			SendMessage (WM_VSCROLL, MAKEWPARAM (SB_LINEUP, 0), NULL);
			GPC.m_DragDrop.pImageList->DragShowNolock (TRUE);
			// Kill the timer if the window did not scroll, or redraw the drop target highlight if the window did scroll.
			if (GetScrollPos(SB_VERT))
				::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);
				else 
					HighlightDropTarget(&GPC.m_DragDrop, point);
		}
		else
			if (point.y >= cy - referGPU[UnitId&0xFFFF]->m_nScrollMargin && point.y <= cy) 
			{
				GPC.m_DragDrop.pImageList->DragShowNolock (FALSE);
				SendMessage (WM_VSCROLL, MAKEWPARAM (SB_LINEDOWN, 0), NULL);
				GPC.m_DragDrop.pImageList->DragShowNolock (TRUE);
				// Kill the timer if the window did not scroll, or redraw the drop target highlight if the window did scroll.
				if (GetScrollPos(SB_HORZ)) ::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);
				else 
					HighlightDropTarget(&GPC.m_DragDrop, point);
			}
			else ::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);
	}
}

void GPDrawWnd::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point) 
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

		DWORD bDropTarget=0xFFFFFFFF;
		BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
		// Highlight the drop target if the cursor is over an item.
		if (mDrop)
			bDropTarget = HighlightDropTarget(pDrDrStruct, CPoint(*point));
		// Modify the cursor to provide visual feedback to the user. Note: It's important to do this AFTER the call to DragMove.
		::SetCursor (bDropTarget==0xFFFFFFFF ?
			AfxGetApp()->LoadStandardCursor (IDC_NO) 
			: (HCURSOR) ::GetClassLong (m_hWnd, GCL_HCURSOR));

		referGPU[UnitId&0xFFFF]->SendDropMoveEvent("",pDrDrStruct,point);
		
		if (mDrop)
			::SetTimer (pDrDrStruct->hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nDelayInterval, NULL);
	}
}

void GPDrawWnd::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point) 
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && referGPU)
	{
		::ScreenToClient(m_hWnd,point);
		referGPU[UnitId&0xFFFF]->SendDropEvent("",pDrDrStruct,point);
	}
}

DWORD GPDrawWnd::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	return 0;
}

LRESULT GPDrawWnd::OnNcHitTest(CPoint point) 
{
	LRESULT ret=CWnd::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

#include "GP_TermDoc.h"

void GPDrawWnd::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd::OnKillFocus(pNewWnd);
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

void GPDrawWnd::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);
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
