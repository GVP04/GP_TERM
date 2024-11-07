// WndPrint.h: interface for the WndPrint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WNDPRINT_H__9E921907_BBB0_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_WNDPRINT_H__9E921907_BBB0_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class WndPrint  
{
public:
	WndPrint(HWND hWnd);
	virtual ~WndPrint();
	BOOL PrintWindowToDC(int Dlg,int Paper,int Orient);
	static void TranslateParam(const char *iStr, int &Dlg,int &Paper,int &Orient);
private:
	HWND m_hWnd;
	HDC WndPrint::GetPrinterDC(void);
	HPALETTE WndPrint::GetSystemPalette();
	HBITMAP WndPrint::Create24BPPDIBSection(HDC hDC, int iWidth, int iHeight);
};

#endif // !defined(AFX_WNDPRINT_H__9E921907_BBB0_11D4_970E_0080AD863699__INCLUDED_)
