// StringFormatPlus.h: interface for the CStringFormatPlus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_StringFormatPlus_H__60A8D5E2_A0FB_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_StringFormatPlus_H__60A8D5E2_A0FB_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CODContext;

class CStringFormatPlus 
{
public:
	virtual UINT DoMethod(const char *iStr, char *oStr);
	CODContext *p_Context;
    CStringFormatPlus(CODContext *ip_Context, INT formatFlags, LANGID language);
    CStringFormatPlus(CODContext *ip_Context, StringFormat *pStringFormat);
    CStringFormatPlus(CODContext *ip_Context, const char *iStr);

	const StringFormat *SetStringFormat(StringFormat *pStringFormat);

	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];

//	const static char *ccA[];
//	const static xxxx iA[];

	const static char *ccAStringFormatFlags[];
	const static DWORD iAStringFormatFlags[];

	const static char *ccAStringAlignment[];
	const static Gdiplus::StringAlignment iAStringAlignment[];

	const static char *ccAStringDigitSubstitute[];
	const static Gdiplus::StringDigitSubstitute iAStringDigitSubstitute[];

	const static char *ccAHotkeyPrefix[];
	const static Gdiplus::HotkeyPrefix iAHotkeyPrefix[];

	const static char *ccAStringTrimming[];
	const static Gdiplus::StringTrimming iAStringTrimming[];

	virtual ~CStringFormatPlus();
	CString CreationString;
	StringFormat *m_StringFormat;
};

#endif // !defined(AFX_StringFormatPlus_H__60A8D5E2_A0FB_11D4_970E_0080AD863699__INCLUDED_)
