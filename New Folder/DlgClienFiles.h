#if !defined(AFX_DLGCLIENFILES_H__C23516B4_ED20_4CF8_B3F5_B10A5049DB17__INCLUDED_)
#define AFX_DLGCLIENFILES_H__C23516B4_ED20_4CF8_B3F5_B10A5049DB17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgClienFiles.h : header file
//
#include "GP_AutoSizing.h"
#include "GP_File.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgClientFiles dialog

class CDlgClientFiles : public CDialog
{
// Construction
public:
	CDlgClientFiles(GP_File **FileArr, UINT nFiles, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgClientFiles)
	enum { IDD = IDD_DLGCLIENTFILES };
	CListCtrl	m_FileList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgClientFiles)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgClientFiles)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	GP_AutoSizing AUSI;
	void UpdateFileInfo(UINT nFile);
	GP_File **m_FileArr;
	UINT m_nFiles;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCLIENFILES_H__C23516B4_ED20_4CF8_B3F5_B10A5049DB17__INCLUDED_)
