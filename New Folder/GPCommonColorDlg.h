#if !defined(AFX_GPCOMMONCOLORDLG_H__154A94C6_0B9C_11D4_970D_0080AD863699__INCLUDED_)
#define AFX_GPCOMMONCOLORDLG_H__154A94C6_0B9C_11D4_970D_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPCommonColorDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GPCommonColorDlg dialog

class GPCommonColorDlg : public CColorDialog
{
	DECLARE_DYNAMIC(GPCommonColorDlg)

public:
	GPCommonColorDlg(COLORREF clrInit = 0, DWORD dwFlags = 0,
			CWnd* pParentWnd = NULL);

protected:
	//{{AFX_MSG(GPCommonColorDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPCOMMONCOLORDLG_H__154A94C6_0B9C_11D4_970D_0080AD863699__INCLUDED_)
