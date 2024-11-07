// GraphicsPathPlus.h: interface for the CGraphicsPathPlus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GraphicsPathPlus_H__60A8D5E2_A0FB_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_GraphicsPathPlus_H__60A8D5E2_A0FB_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CODContext;

class CGraphicsPathPlus 
{
public:
	virtual UINT DoMethod(const char *iStr, char *oStr);
	CODContext *p_Context;
    CGraphicsPathPlus(CODContext *ip_Context, const Point *points,  const BYTE *types, INT count,  FillMode fillMode);
    CGraphicsPathPlus(CODContext *ip_Context, FillMode fillMode);
    CGraphicsPathPlus(CODContext *ip_Context, const char *iStr);
    CGraphicsPathPlus(CODContext *ip_Context, const PointF *points, const BYTE *types, INT count, FillMode fillMode);
    CGraphicsPathPlus(CODContext *ip_Context, GraphicsPath *pGraphicsPath);

	const GraphicsPath *SetGraphicsPath(GraphicsPath *pGraphicsPath);

	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];

	const static char *ccAFillMode[];
	const static DWORD iAFillMode[];

	const static char *ccAWarpMode[];
	const static DWORD iAWarpMode[];

	const static char *ccAPointType[];
	const static DWORD iAPointType[];


	virtual ~CGraphicsPathPlus();
	CString CreationString;
	GraphicsPath *m_GraphicsPath;
};

#endif // !defined(AFX_GraphicsPathPlus_H__60A8D5E2_A0FB_11D4_970E_0080AD863699__INCLUDED_)
