#if !defined(AFX_DLGVIEWIOFILES_H__227D948D_5B69_42B8_B890_7B6981AA9297__INCLUDED_)
#define AFX_DLGVIEWIOFILES_H__227D948D_5B69_42B8_B890_7B6981AA9297__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgViewIOFiles.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgViewIOFiles dialog

class CDlgViewIOFiles : public CDialog
{
// Construction
public:
	CString m_csLastResult;
	void FillIOFileList();
	CDlgViewIOFiles(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgViewIOFiles)
	enum { IDD = IDD_DIALOGVIEWIOFILES };
	CButton	m_BtnMore;
	CButton	m_BtnClearEvents;
	CButton	m_BtnAddIOFile;
	CStatic	m_StaticEvents;
	CEdit	m_EditEvents;
	CStatic	m_StatParams;
	CEdit	m_EditResult;
	CEdit	m_EditParams;
	CButton	m_btnExecute;
	CButton	m_btnDelete;
	CComboBox	m_ComboMethods;
	CComboBox	m_ComboIOFiles;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgViewIOFiles)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgViewIOFiles)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeComboiofiles();
	afx_msg void OnBtndelete();
	afx_msg void OnBtnadd();
	afx_msg void OnBtnexecute();
	afx_msg void OnSelchangeCombomethods();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtndeletetext();
	afx_msg void OnButtonmore();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	GP_AutoSizing AUSI;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIEWIOFILES_H__227D948D_5B69_42B8_B890_7B6981AA9297__INCLUDED_)
