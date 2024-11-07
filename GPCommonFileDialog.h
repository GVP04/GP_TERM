#if !defined(AFX_GPCOMMONFILEDIALOG_H__154A94C4_0B9C_11D4_970D_0080AD863699__INCLUDED_)
#define AFX_GPCOMMONFILEDIALOG_H__154A94C4_0B9C_11D4_970D_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPCommonFileDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GPCommonFileDialog dialog

class GPCommonFileDialog : public CFileDialog
{
	DECLARE_DYNAMIC(GPCommonFileDialog)

public:
	GPCommonFileDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

protected:
	//{{AFX_MSG(GPCommonFileDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPCOMMONFILEDIALOG_H__154A94C4_0B9C_11D4_970D_0080AD863699__INCLUDED_)
