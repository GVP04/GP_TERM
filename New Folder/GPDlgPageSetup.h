#if !defined(AFX_GPDlgPageSetup_H__1A4D0521_FEFA_11D2_87EF_F529B13A5E4D__INCLUDED_)
#define AFX_GPDlgPageSetup_H__1A4D0521_FEFA_11D2_87EF_F529B13A5E4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPDlgPageSetup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GPDlgPageSetup dialog
#include "GP_comm.h"

class GPDlgPageSetup : public CDialog
{
// Construction
private:

public:
	GPDlgPageSetup(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(GPDlgPageSetup)
	enum { IDD = IDD_DIALOGPAGESETUP };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPDlgPageSetup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(GPDlgPageSetup)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedButtonpsetup();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPDlgPageSetup_H__1A4D0521_FEFA_11D2_87EF_F529B13A5E4D__INCLUDED_)
