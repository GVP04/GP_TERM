// GPRegion.h: interface for the GPRegion class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPREGION_H__6FC4E840_3E2C_48AE_BDC8_38AE239254C7__INCLUDED_)
#define AFX_GPREGION_H__6FC4E840_3E2C_48AE_BDC8_38AE239254C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class GPRegion  
{
public:
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
	const CString SetName(const char *iName);
	const CString GetName();
	GPRegion(const char *iName);
	virtual ~GPRegion();
	HRGN CreateCombineRgn(HRGN hrgnSrc1, HRGN hrgnSrc2, int fnCombineMode);
	HRGN CombineRgn(HRGN hrgnSrc1,int fnCombineMode);
	HRGN CreateEllipticRgn(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect);
	HRGN CreateEllipticRgnIndirect(CONST RECT *lprc);
	HRGN CreatePolygonRgn(CONST POINT *lppt, int cPoints, int fnPolyFillMode);
	HRGN CreatePolyPolygonRgn(CONST POINT *lppt, CONST INT *lpPolyCounts, int nCount, int fnPolyFillMode);
	HRGN CreateRectRgn(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect);
	HRGN CreateRectRgnIndirect(CONST RECT *lprc);
	HRGN CreateRoundRectRgn(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nWidthEllipse, int nHeightEllipse);
	HRGN ExtCreateRegion(CONST XFORM *lpXform, DWORD nCount, CONST RGNDATA *lpRgnData);
	HRGN SetRectRgn(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect);
	BOOL EqualRgn(HRGN hrgnSrc);
	BOOL FillRgn(HDC hdc, HBRUSH hbr);
	BOOL FrameRgn(HDC hdc, HBRUSH hbr, int nWidth, int nHeight);
	DWORD GetRegionData(DWORD dwCount, LPRGNDATA lpRgnData);
	int GetRgnBox(LPRECT lprc);
	BOOL InvertRgn(HDC hdc);
	int OffsetRgn(int nXOffset, int nYOffset);
	BOOL PaintRgn(HDC hdc);
	BOOL PtInRegion(int X, int Y);
	BOOL RectInRegion(CONST RECT *lprc);
	virtual UINT DoMethod(const char *iStr, char *oStr, void *GPRArray);
	long TranslateCombineMode(const char * iStr);
	HRGN GetHRGN();
private:
	HRGN m_rgn;
	CString Name;
};

#endif // !defined(AFX_GPREGION_H__6FC4E840_3E2C_48AE_BDC8_38AE239254C7__INCLUDED_)
