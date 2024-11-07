#if !defined(AFX_DLGVIEWREGMETHODS_H__227D948D_5B69_42B8_B890_7B6981AA9297__INCLUDED_)
#define AFX_DLGVIEWREGMETHODS_H__227D948D_5B69_42B8_B890_7B6981AA9297__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgViewRegMethods.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgViewRegMethods dialog

class CDlgViewRegMethods : public CDialog
{
// Construction
public:
	CString m_csLastResult;
	CDlgViewRegMethods(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgViewRegMethods)
	enum { IDD = IDD_DIALOGVIEWREGMETHODS };
	CButton	m_BtnMore;
	CStatic	m_StatParams;
	CEdit	m_EditResult;
	CEdit	m_EditParams;
	CButton	m_btnExecute;
	CComboBox	m_ComboMethods;
	CComboBox	m_ComboVars;
	CButton	m_BtnAddVar;
	CButton	m_btnDelete;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgViewRegMethods)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	void FillIVarsList();

	// Generated message map functions
	//{{AFX_MSG(CDlgViewRegMethods)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBtnexecute();
	afx_msg void OnSelchangeCombomethods();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonmore();
	afx_msg void OnDestroy();
	afx_msg void OnBtnadd();
	afx_msg void OnBtndelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	GP_AutoSizing AUSI;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIEWREGMETHODS_H__227D948D_5B69_42B8_B890_7B6981AA9297__INCLUDED_)
