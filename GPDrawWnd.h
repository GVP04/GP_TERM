#if !defined(AFX_GPDRAWWND_H__B96B0B22_8ED7_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_GPDRAWWND_H__B96B0B22_8ED7_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPDrawWnd.h : header file
//
#include "GP_HotKey.h"
#include "GPUnit.h"

/////////////////////////////////////////////////////////////////////////////
// GPDrawWnd window

typedef struct _DRAWITEMDATA
{
	CPoint po1;
	CPoint po2;
	CRect re1;
	CRect re2;
	COLORREF clr1;
	COLORREF clr2;
} DRAWITEMDATA, *PDRAWITEMDATA;

typedef struct _DRAWITEMDATATEXT
{
	CRect re;
	CPoint po;
	CString text;
	UINT flags;
	UINT flags2;
	int nBrush;
} DRAWITEMDATATEXT, *PDRAWITEMDATATEXT;

typedef struct _DRAWITEMDATASTR
{
	CString text;
	CString format;
	int nSourse;
	UINT nDest;
} DRAWITEMDATASTR, *PDRAWITEMDATASTR;

typedef struct _DRAWITEMDATANUM
{
	int i1;
	int i2;
	int i3;
	int i4;
	union {	double d1;	int id1;};
	union {	double d2;	int id2;};
	union {	double d3;	int id3;};
	union {	double d4;	int id4;};
} DRAWITEMDATANUM, *PDRAWITEMDATANUM;

typedef struct _DRAWITEMDATAPRG
{
	union {	double d1;	int i1;};
	union {	double d2;	int i2;};
	union {	double d3;	int i3;};
	union {	double d4;	int i4;};
	union {	double d5;	int i5;};
	PDRAWITEMDATANUM DIDNum;
	PDRAWITEMDATA DID;
	PDRAWITEMDATATEXT DIDText;
	int counter;
	int PrevJOB;
	int NextJOB;
	CPoint PrevOffset;
	CPoint PrevPosition;
	CPoint QurentPosition;
	CPoint QurentOffset;
	BOOL IsRun;
} DRAWITEMDATAPRG, *PDRAWITEMDATAPRG;

typedef struct _DRAWITEMDATAMATH
{
	int nArg;
	int nResults;
	int iFunction;
	int iArgType[16];
	double dConst[16];
	int iArgAdress[16];
	int iResultsArr[16];
	int iResultsType[16];
} DRAWITEMDATAMATH, *PDRAWITEMDATAMATH;

typedef struct _DRAWTIMER
{
	int nTimer;
	int nDelay;
	double dValue;
	double dDelta;
	double dStop;
	BOOL bRedraw;
	BOOL bisRun;
} DRAWTIMER, *PDRAWTIMER;

#define TIMER_DRAW_START_ID		19000


class GPDrawWnd : public CWnd
{
	friend class GPUnit;
	friend class CDlgDrawEdit;

// Construction
public:
	DWORD HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);
	GPDrawWnd(UINT iUnitId, GPUnit ** iGPU);
	UINT GPSetProperty(char *iStr);
// Attributes
public:
	const static enum DrawUnitTypeEnum
	{
	DUT_NONE=0,			DUT_FRG=1,				DUT_BKG=2,			DUT_PEN=3,			DUT_BRUSH=4,
	DUT_FONT=5,			DUT_MOVE=6,				DUT_MOVER=7,		DUT_MOVEP=8,		BUT_BKMODE=9,
	DUT_PFILLMODE=10,	DUT_ROP2=11,			DUT_SBLTMODE=12,	DUT_COLORADJ=13,	DUT_MAPMODE=14,
	DUT_VPORTORG=15,	DUT_VPORTEXT=16,		DUT_BRUSHORG=17,	DUT_STOCKOBJ=18,	DUT_WINDOWORG=19,
	DUT_WINDOWEXT=20,	DUT_LINETO=21,			DUT_LINETOP=22,		DUT_ARC=23,			DUT_ARCTO=24,
	DUT_ARCRPP=25,		DUT_ARCRPPTO=26,		DUT_ANGLEARC=27,	DUT_ANGLEARCP=28,	DUT_ARCDIRECTION=29,
	DUT_POLYLINE=30,	DUT_POLYLINETO=31,		DUT_POLYLINEP=32,	DUT_POLYLINEPTO=33,	DUT_POLYPOLY=34,
	DUT_POLYPOLYP=35,	DUT_POLYBEZIER=36,		DUT_POLYBEZIERP=37,	DUT_POLYBEZIERTO=38,DUT_POLYBEZIERPTO=39,
	DUT_FILLRECT=40,	DUT_FILLRECTR=41,		DUT_FRAMERECT=42,	DUT_FRAMERECTR=43,	DUT_INVERTRECT=44,
	DUT_INVERTRECTR=45,	DUT_ICON=46,			DUT_ICONP=47,		DUT_FILLSRECT=48,	DUT_FILLSRECTR=49,
	DUT_3DRECT=50,		DUT_3DRECTR=51,			DUT_EDGE=52,		DUT_EDGER=53,		DUT_FRAMECTRL=54,
	DUT_FRAMECTRLR=55,	DUT_STATETEXT=56,		DUT_STATETEXTR=57,	DUT_STATEICON=58,	DUT_STATEICONR=59,
	DUT_CHORD=60,		DUT_CHORDRP=61,			DUT_FOCUSRECT=62,	DUT_FOCUSRECTR=63,	DUT_ELLIPSE=64,
	DUT_ELLIPSER=65,	DUT_PIE=66,				DUT_PIERP=67,		DUT_POLYGON=68,		DUT_POLYGONP=69,
	DUT_PPOLYGON=70,	DUT_PPOLYGONP=71,		DUT_RECT=72,		DUT_RECTR=73,		DUT_ROUNDRECT=74,
	DUT_ROUNDRECTR=75,	DUT_PIXEL=76,			DUT_PIXELPC=77,		DUT_FLOODFILL=78,	DUT_FLOODFILLPC=79,
	DUT_EXTFLOODFILL=80,DUT_EXTFLOODFILLPC=81,	DUT_TEXTOUT=82,		DUT_TEXTOUTPT=83,	DUT_EXTTEXTOUT=84,
	DUT_EXTTEXTOUTP=85,	DUT_TABTEXTOUT=86,		DUT_TABTEXTOUTP=87,	DUT_TEXT=88,		DUT_TEXTR=89,
	DUT_TEXTALIGN=90,	DUT_TEXTJUST=91,		DUT_CHAREXTRA=92,	DUT_MAPPERFLAGS=93,	DUT_ABORTPATH=94,
	DUT_BEGINPATH=95,	DUT_CLOSEFIGURE=96,		DUT_ENDPATH=97,		DUT_FILLPATH=98,	DUT_FLATTENPATH=99,
	DUT_SELECTCLIPPATH=100,DUT_SETMITERLIMIT=101,DUT_STROKEFILLPATH=102,DUT_STROKEPATH=103,DUT_WIDENPATH=104,
	DUT_ARROW=105,		DUT_ARROWTO=106,		DUT_ARROWP=107,		DUT_ARROWPTO=108,	DUT_OFFSET=109,
	DUT_OFFSETP=110,	DUT_CLONE=111,			DUT_CLONETO=112,	DUT_CLONEC=113,		DUT_CLONECTO=114,
	DUT_GOTO=115,		DUT_GOSUB=116,			DUT_RETURN=117,		DUT_SETINT=118,		DUT_SETDOUBLE=119,
	DUT_SETPOINT=120,	DUT_SETRECT=121,		DUT_SETCOLOR=122,	DUT_SETREGION=123,	DUT_COPYREGION=124,
	DUT_COMBINEREGION=125,DUT_OFFSETREGION=126, DUT_OFFSETPREGION=127,DUT_REGIONFROMPATH=128,DUT_FILLRGN=129,
	DUT_FRAMERGN=130,	DUT_INVERTRGN=131,		DUT_PAINTRGN=132,	DUT_BOUNDSRECT=133,	DUT_BOUNDSRECTR=134,
	DUT_GETCLIPBOX=135,	DUT_GETBOUNDSR=136,		DUT_SELCLIPREGION=137,DUT_EXCLRECT=138,	DUT_EXCLRECTR=139,
	DUT_EXCLUPDRGN=140,	DUT_INCLRECT=141,		DUT_INCLRECTR=142,	DUT_OFFSETCREGION=143,DUT_OFFSETPCREGION=144,
	DUT_IFGOTO=145,		DUT_IFGOSUB=146,		DUT_ARITHMETIC=147,	DUT_MATH=148,		DUT_SETRGB=149,
	DUT_SETPENCOLOR=150,DUT_GETWINDOWRECT=151,	DUT_GETCLIENTRECT=152,DUT_MOVEWINDOW=153,DUT_RECTOFFSET=154,
	DUT_RECTOFFSETR=155,DUT_RECTOFFSETP=156,	DUT_RECTHEIGHT=157,	DUT_RECTWIDTH=158,	DUT_RECTISNULL=159,
	DUT_RECTISEMPTY=160,DUT_RECTCENTER=161,		DUT_RECTPTIN=162,	DUT_RECTEQUAL=163,	DUT_RECTINFLATE=164,
	DUT_RECTDEFLATE=165,DUT_RECTNORMALIZE=166,	DUT_RECTSUBSTR=167,	DUT_RECTINTERS=168,	DUT_RECTUNION=169,
	DUT_RECTOFFSETRM=170,DUT_RECTOFFSETPM=171,	DUT_SCRTOCL=172,	DUT_CLTOSCR=173,	DUT_STRCAT=174,
	DUT_STRCATS=175,	DUT_ITOSTR=176,			DUT_DTOSTR=177,		DUT_TTOSTR=178,		DUT_PENWIDTH=179,
	};

	const static UINT uNArrFn;
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
	const static UINT uNUnitType;
	const static char *cArrUnitType[];
	const static UINT uArrUnitType[];
	static long TranslateETO(const char * iStr);
	static long GPDrawWnd::TranslateDT(const char * iStr);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPDrawWnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	CSize m_LogSize;
	CString m_DrawName;
	CRect m_PrintMargins;
	CSize m_PrintWinExt;
	CSize m_PrintVieExt;
	CPoint m_PrintWinOrg;
	CPoint m_PrintVieOrg;
	void SetPrintAlign(CDC *pDC, HDC hdcPrn);
	void PrintDrawWnd(int Dlg,int Orient,int Paper);
	void PaintToCDC(CDC *pDC);
	static void InitDRAWITEMDATATEXT(PDRAWITEMDATATEXT pdid);
	static void InitDRAWITEMDATA(PDRAWITEMDATA pdid);
	static void InitDRAWITEMDATANUM(PDRAWITEMDATANUM pdid);
	static void InitDRAWITEMDATAPRG(PDRAWITEMDATAPRG pdid);
	static void InitDRAWITEMDATAMATH(PDRAWITEMDATAMATH pdid);
	static void InitDRAWITEMDATASTR(PDRAWITEMDATASTR pdid);
	static void InitDRAWTIMER(PDRAWTIMER pdid);
	void DestroyItem(UINT nItem);
	BOOL SetItem(UINT nItem, const char * iStr);
	BOOL InsertEmptyItem(UINT uItemBefore, UINT uCount);
	UINT DeleteItem(UINT nItem);
	virtual ~GPDrawWnd();
	virtual UINT DoMethod(const char *iStr, char *oStr);

	// Generated message map functions
protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	//{{AFX_MSG(GPDrawWnd)
	afx_msg void ParentNotify(UINT message, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	HBITMAP m_hDCBitmap;
	UINT m_uRedrawFlag;
	BOOL m_bEraseBkg;
	BOOL m_bAutoRedraw;
	void DeletePaintObj();
	CPoint OffsetPoint;
	UINT m_nDrawArray;
	UINT m_nDraw;
	UINT *m_ArrDrawType;
	WPARAM *m_ArrDrawWParam;
	LPARAM *m_ArrDrawLParam;
	CString *m_ArrDrawInitString;
	CPenExt **m_PenArr;
	UINT m_nPenArray;
	CBrushExt **m_BrushArr;
	UINT m_nBrushArray;
	CFontExt **m_FontArr;
	UINT m_nFontArray;
	CRgnExt **m_RgnArr;
	UINT m_nRgnArray;
	CPoint *m_PointArr;
	UINT m_nPointArray;
	CRect  *m_RectArr;
	UINT m_nRectArray;
	COLORREF *m_RGBArr;
	UINT m_nRGBArray;
	HICON *m_IconArr;
	CString *m_IconArrString;
	UINT m_nIconArray;
	CString  *m_StringArr;
	UINT m_nStringArray;
	int  *m_IntArr;
	UINT m_nIntArray;
	double  *m_DoubleArr;
	UINT m_nDoubleArray;

	DRAWTIMER *m_DrTimerArr;
	UINT m_nDrTimerArray;

	GPUnit **referGPU;
	UINT UnitId;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPDRAWWND_H__B96B0B22_8ED7_11D4_970E_0080AD863699__INCLUDED_)
