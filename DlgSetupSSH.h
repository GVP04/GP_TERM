#if !defined(AFX_DLGSETUPSSH_H__73598A6D_B81F_4302_B8F5_0EEBB9780B6F__INCLUDED_)
#define AFX_DLGSETUPSSH_H__73598A6D_B81F_4302_B8F5_0EEBB9780B6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetupSSH.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSetupSSH dialog

class CDlgSetupSSH : public CDialog
{
// Construction
public:
	int m_CurSubItem;
	int m_CurItem;
	CDlgSetupSSH(const char *iSectionName, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSetupSSH)
	enum { IDD = IDD_DIALOGSSH };
	CListBox	m_ListPolicy;
	CListBox	m_ListEncription;
	CEdit	m_EditList;
	CListCtrl	m_ListForfardPorts;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSetupSSH)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSetupSSH)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonadd();
	afx_msg void OnButtondelete();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEdit1();
	afx_msg void OnKillfocusEdit1();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonup();
	afx_msg void OnButtonup2();
	afx_msg void OnButtondown();
	afx_msg void OnButtondown2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_SectionName;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETUPSSH_H__73598A6D_B81F_4302_B8F5_0EEBB9780B6F__INCLUDED_)
