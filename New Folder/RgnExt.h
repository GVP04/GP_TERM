// RgnExt.h: interface for the CRgnExt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RGNEXT_H__5277F6E5_AF5D_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_RGNEXT_H__5277F6E5_AF5D_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRgnExt : public CRgn  
{
public:
	CRgnExt();
	virtual ~CRgnExt();
	CString CreationString;
};

#endif // !defined(AFX_RGNEXT_H__5277F6E5_AF5D_11D4_970E_0080AD863699__INCLUDED_)
