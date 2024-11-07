// FontPlus.h: interface for the CFontPlus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FontPlus_H__60A8D5E3_A0FB_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_FontPlus_H__60A8D5E3_A0FB_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFontPlus  
{
public:
	CFontPlus( const FontFamily *family, REAL emSize, INT style, Unit unit);
	CFontPlus( HDC hdc, const LOGFONTA *logfont);
	CFontPlus( HDC hdc);
	CFontPlus(HDC hdc, const char *ccIstr);
	CFontPlus(const char *ccIstr);
	Font *m_Font;
	virtual UINT DoMethod(const char *iStr, char *oStr);

	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];

//	const static char *ccA[];
//	const static DWORD iA[];

	const static char *ccAFontStyle[];
	const static DWORD iAFontStyle[];

	virtual ~CFontPlus();
	CString CreationString;
};

#endif // !defined(AFX_FontPlus_H__60A8D5E3_A0FB_11D4_970E_0080AD863699__INCLUDED_)
