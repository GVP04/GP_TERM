#if !defined(AFX_GPDLGVIEWSTABLE_H__D507276D_499D_402B_B09A_6C704CF321B9__INCLUDED_)
#define AFX_GPDLGVIEWSTABLE_H__D507276D_499D_402B_B09A_6C704CF321B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPDlgViewSTable.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGPDlgViewSTable dialog

class CGPDlgViewSTable : public CDialog
{
	friend UINT UpdTbl(LPVOID pParam);
// Construction
public:
	CGPDlgViewSTable(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGPDlgViewSTable)
	enum { IDD = IDD_DIALOGSMBTABLE };
	CButton	m_btnNewValue;
	CButton	m_btnUpdate;
	CListCtrl	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGPDlgViewSTable)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	GP_AutoSizing AUSI;

	// Generated message map functions
	//{{AFX_MSG(CGPDlgViewSTable)
	afx_msg void OnButtonupd();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonnewvalue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPDLGVIEWSTABLE_H__D507276D_499D_402B_B09A_6C704CF321B9__INCLUDED_)
