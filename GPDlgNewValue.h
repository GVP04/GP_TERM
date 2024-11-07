#if !defined(AFX_GPDLGNEWVALUE_H__0CABAA16_2F62_49DB_8B91_0B1E4BF1181D__INCLUDED_)
#define AFX_GPDLGNEWVALUE_H__0CABAA16_2F62_49DB_8B91_0B1E4BF1181D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPDlgNewValue.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GPDlgNewValue dialog

class GPDlgNewValue : public CDialog
{
// Construction
public:
	CString OldValue;
	GPDlgNewValue(CString iOldValue, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(GPDlgNewValue)
	enum { IDD = IDD_DIALOGNEWVALUE };
	CString	m_NewValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPDlgNewValue)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GPDlgNewValue)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPDLGNEWVALUE_H__0CABAA16_2F62_49DB_8B91_0B1E4BF1181D__INCLUDED_)
