// FontExt.h: interface for the CFontExt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FONTEXT_H__60A8D5E3_A0FB_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_FONTEXT_H__60A8D5E3_A0FB_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFontExt : public CFont  
{
public:
	CFontExt();
	virtual ~CFontExt();
	CString CreationString;
};

#endif // !defined(AFX_FONTEXT_H__60A8D5E3_A0FB_11D4_970E_0080AD863699__INCLUDED_)
