// RgnPlus.h: interface for the CRgnPlus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RgnPlus_H__5277F6E5_AF5D_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_RgnPlus_H__5277F6E5_AF5D_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CODContext;

class CRgnPlus
{
public:
	CODContext *p_Context;
	CRgnPlus(CODContext *ip_Context);
	CRgnPlus(CODContext *ip_Context, const Rect &rect);
	CRgnPlus(CODContext *ip_Context, const BYTE *regionData,INT size);
	CRgnPlus(CODContext *ip_Context, const GraphicsPath *path);
	CRgnPlus(CODContext *ip_Context, HRGN hRgn);
	CRgnPlus(CODContext *ip_Context, const RectF &rect);
	CRgnPlus(CODContext *ip_Context, const char *iStr);
	CRgnPlus(CODContext *ip_Context, IN const CRgnPlus *iRegion);

	Region *m_Rgn;
	virtual UINT DoMethod(const char *iStr, char *oStr);

	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];

//	const static char *ccA[];
//	const static DWORD iA[];


	virtual ~CRgnPlus();
	CString CreationString;
};

#endif // !defined(AFX_RgnPlus_H__5277F6E5_AF5D_11D4_970E_0080AD863699__INCLUDED_)
