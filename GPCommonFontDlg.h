#if !defined(AFX_GPCOMMONFONTDLG_H__154A94C5_0B9C_11D4_970D_0080AD863699__INCLUDED_)
#define AFX_GPCOMMONFONTDLG_H__154A94C5_0B9C_11D4_970D_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPCommonFontDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GPCommonFontDlg dialog

class GPCommonFontDlg : public CFontDialog
{
	DECLARE_DYNAMIC(GPCommonFontDlg)

public:
	GPCommonFontDlg(LPLOGFONT lplfInitial = NULL,
		DWORD dwFlags = CF_EFFECTS | CF_SCREENFONTS,
		CDC* pdcPrinter = NULL,
		CWnd* pParentWnd = NULL);
#ifndef _AFX_NO_RICHEDIT_SUPPORT
	GPCommonFontDlg(const CHARFORMAT& charformat,
		DWORD dwFlags = CF_SCREENFONTS,
		CDC* pdcPrinter = NULL,
		CWnd* pParentWnd = NULL);
#endif

protected:
	//{{AFX_MSG(GPCommonFontDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPCOMMONFONTDLG_H__154A94C5_0B9C_11D4_970D_0080AD863699__INCLUDED_)
