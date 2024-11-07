#if !defined(AFX_DLGVIEWFSMethods_H__227D948D_5B69_42B8_B890_7B6981AA9297__INCLUDED_)
#define AFX_DLGVIEWFSMethods_H__227D948D_5B69_42B8_B890_7B6981AA9297__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgViewFSMethods.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgViewFSMethods dialog

class CDlgViewFSMethods : public CDialog
{
// Construction
public:
	CString m_csLastResult;
	CDlgViewFSMethods(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgViewFSMethods)
	enum { IDD = IDD_DIALOGVIEWFSMETHODS };
	CButton	m_BtnMore;
	CButton	m_BtnClearEvents;
	CStatic	m_StaticEvents;
	CEdit	m_EditEvents;
	CStatic	m_StatParams;
	CEdit	m_EditResult;
	CEdit	m_EditParams;
	CButton	m_btnExecute;
	CComboBox	m_ComboMethods;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgViewFSMethods)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgViewFSMethods)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBtnexecute();
	afx_msg void OnSelchangeCombomethods();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtndeletetext();
	afx_msg void OnButtonmore();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	GP_AutoSizing AUSI;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIEWFSMethods_H__227D948D_5B69_42B8_B890_7B6981AA9297__INCLUDED_)
