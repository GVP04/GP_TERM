// PenExt.h: interface for the CPenExt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PENEXT_H__60A8D5E1_A0FB_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_PENEXT_H__60A8D5E1_A0FB_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPenExt : public CPen  
{
public:
	CPenExt();
	CPenExt(int nPenStyle, int nWidth, COLORREF crColor );
	CPenExt(int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush);
	virtual ~CPenExt();
	CString CreationString;
};

#endif // !defined(AFX_PENEXT_H__60A8D5E1_A0FB_11D4_970E_0080AD863699__INCLUDED_)
