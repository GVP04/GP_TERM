// ODContext.h: interface for the CODContext class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ODCONTEXT_H__8D957D42_5A21_4EC9_8A29_327B6377DC4C__INCLUDED_)
#define AFX_ODCONTEXT_H__8D957D42_5A21_4EC9_8A29_327B6377DC4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GP_Term.h"
//#include "GP_RarefiedArr.h"

typedef struct _DRAWTIMERPLUS
{
	int nTimer;
	int nDelay;
	REAL dValue;
	REAL dDelta;
	REAL dStop;
	BOOL bRedraw;
	DWORD dwTimerProcId;
	LPARAM pODContext;
} DRAWTIMERPLUS, *PDRAWTIMERPLUS;

class GPUnit;  
class GPMenu;  
class CODContextItem;  

class CODContext  
{
	friend VOID CALLBACK DrawTimerProc( HWND hwnd,    UINT uMsg,    UINT_PTR idEvent,    DWORD dwTime);
	friend class CODContextArray;
	friend class GPUnit;
	friend class CRgnPlus;
	friend class CMatrixPlus;
	friend class CBitmapPlus;
	friend class CGraphicsPathPlus;
	friend class CBrushPlus;
	friend class GPDrawWnd;
	friend class CDlgDrawEdit;
	friend class CPenPlus;
	friend class CODContextItem;
	friend class CGP_TermView;
public:
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];

	const static char *ccANamedColors[];
	const static DWORD iANamedColors[];

	PDRAWTIMERPLUS GetTimerById(int iTimerId);
	static PDRAWTIMERPLUS GetTimerByProcId(DWORD idwTimerProcId);
	
	void PaintByDRAWITEMSTRUCT(GPUnit *gpuRes, WPARAM wParam, LPDRAWITEMSTRUCT lPDiStruct, GPMenu *pMenu, LPARAM lParam);

public:
	MEASUREITEMSTRUCT m_MeasureStruct;
	DWORD m_MeasureFlag;
	CString m_ContextName;
	HWND m_CurHWND;
	HDC m_CurHDC;
	GPUnit **m_CurDialogGPU;
	CODContext();
	virtual ~CODContext();
	void Paint(CPaintDC &dc, CRect &ClientRe, HBRUSH hbrBkgnd);
	void InvalidateDependentWindows();
	void ResetContext();

	int GetIntByRef( DWORD ref);
	REAL GetREALByRef( DWORD ref);
	Color GetColorByRef( DWORD ref);
	DWORD GetIdFromRef(DWORD ref);

	CSize m_LogSize;
	CString m_DrawName;
	CRect m_PrintMargins;
	CSize m_PrintWinExt;
	CSize m_PrintVieExt;
	Point m_PrintWinOrg;
	Point m_PrintVieOrg;
	void SetPrintAlign(CDC *pDC, HDC hdcPrn, RectF &ClientRect);
	void PrintDrawWnd(int Dlg,int Orient,int Paper, RectF &ClientRect, HBRUSH hbrBkgnd);
	void PaintToCDC(CDC *pDC, RectF &ClientRe, HBRUSH hbrBkgnd);
	void PaintToGraphics(Graphics &mGr, RectF &ClientRe, HBRUSH hbrBkgnd);
	void DestroyItem(UINT nItem);
	BOOL SetItem(UINT nItem, const char * iStr);
	BOOL InsertEmptyItem(UINT uItemBefore, UINT uCount);
	UINT DeleteItem(UINT nItem);
	virtual UINT DoMethod(const char *iStr, char *oStr);
	Color m_clrBkgnd;
	DRAWTIMERPLUS GetDrawTimer(int iTimerId);
	CBitmapPlus *GetBitmap(DWORD dwBitmapId);
	CBitmapPlus *SetBitmap(DWORD dwBitmapId, CBitmapPlus *iBitmap);

private:
	static void KillDrawTimer(int iTimerId, CODContext *pContext);
	static GP_RarefiedArr<DRAWTIMERPLUS> m_AllDrawTimers; 
	static void InitDRAWTIMERPLUS(PDRAWTIMERPLUS pdid, CODContext *pODContext);
	GP_RarefiedArr<HWND> m_AllDrawHWND; 
	HBITMAP m_hDCBitmap;
	UINT m_uRedrawFlag;
	BOOL m_bEraseBkg;
	BOOL m_bAutoRedraw;
	void DeletePaintObj();
	PointF OffsetPoint;

	UINT m_nDrawArray;
	UINT m_nDraw;
	CODContextItem **m_ArrDrawItems;

	CPenPlus **m_PenArr;					UINT m_nPenArray;
	CBrushPlus **m_BrushArr;				UINT m_nBrushArray;
	PointF *m_PointArr;						UINT m_nPointArray;
	RectF  *m_RectArr;						UINT m_nRectArray;
	CMatrixPlus  **m_MatrixArr;				UINT m_nMatrixArray;
	Color *m_RGBArr;						UINT m_nRGBArray;
	CString  *m_StringArr;					UINT m_nStringArray;
	int  *m_IntArr;							UINT m_nIntArray;
	REAL  *m_REALArr;						UINT m_nREALArray;
	CFontPlus **m_FontArr;					UINT m_nFontArray;
	CRgnPlus **m_RgnArr;					UINT m_nRgnArray;
	CGraphicsPathPlus **m_GraphPathArr;		UINT m_nGraphPathArray;
	CStringFormatPlus **m_StringFormatArr;	UINT m_nStringFormatArray;
	CBitmapPlus **m_BitmapArr;				UINT m_nBitmapArray;
	CBitmapPlus **m_ILBitmap;				UINT m_nILBitmap;

	TEXTMETRIC m_TMArr[10];
public:
	static ARGB GetColorFromString(CODContext *iContext, const char *iStr); 
	DWORD ParseId(const char *iParam);
	CODContext *SaveContext(const char * ccFileName);
};

#endif // !defined(AFX_ODCONTEXT_H__8D957D42_5A21_4EC9_8A29_327B6377DC4C__INCLUDED_)
