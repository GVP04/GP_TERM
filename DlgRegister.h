#if !defined(AFX_DLGREGISTER_H__D41156B3_789B_4DC1_B0DA_253E9D7A8EEE__INCLUDED_)
#define AFX_DLGREGISTER_H__D41156B3_789B_4DC1_B0DA_253E9D7A8EEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRegister.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRegister dialog

class CDlgRegister : public CDialog
{
// Construction
public:
	UINT UpdateRegList();
	CDlgRegister(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRegister)
	enum { IDD = IDD_DIALOGREGISTER };
	CListCtrl	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRegister)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	long IsRegisterInROT(IBindCtx* pBind,IRunningObjectTable* prot,BSTR* iStr);
	// Generated message map functions
	//{{AFX_MSG(CDlgRegister)
	afx_msg void OnButtonunreg();
	afx_msg void OnButtonreg();
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREGISTER_H__D41156B3_789B_4DC1_B0DA_253E9D7A8EEE__INCLUDED_)
