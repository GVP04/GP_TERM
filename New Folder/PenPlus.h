// PenPlus.h: interface for the CPenPlus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PenPlus_H__60A8D5E1_A0FB_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_PenPlus_H__60A8D5E1_A0FB_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CODContext;

class CPenPlus
{
public:
	Pen *m_Pen;
	DWORD m_dwType;
	virtual UINT DoMethod(const char *iStr, char *oStr);
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
	const static char *ccALineCap[];
	const static DWORD iALineCap[];
	const static char *ccADashStyle[];
	const static DWORD iADashStyle[];
	const static char *ccADashCap[];
	const static DWORD iADashCap[];
	const static char *ccALineJoin[];
	const static DWORD iALineJoin[];

	CODContext *p_Context;
	Brush *m_DefBrush;
	virtual ~CPenPlus();
	CPenPlus(CODContext *ip_Context, const Color &color, REAL width);
	CPenPlus(CODContext *ip_Context, const Brush *brush, REAL width);
	CPenPlus(CODContext *ip_Context, IN const char *iStr, REAL width);
	CString CreationString;
	const Pen *SetPen(Pen *pPen);
};

#endif // !defined(AFX_PenPlus_H__60A8D5E1_A0FB_11D4_970E_0080AD863699__INCLUDED_)
