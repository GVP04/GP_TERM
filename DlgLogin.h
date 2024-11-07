#if !defined(AFX_DLGLOGIN_H__2F0DAEDD_85E2_432E_B3F1_38F0E38B048B__INCLUDED_)
#define AFX_DLGLOGIN_H__2F0DAEDD_85E2_432E_B3F1_38F0E38B048B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLogin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin dialog

class CDlgLogin : public CDialog
{
// Construction
public:
	DWORD m_MaxInputTime;
	DWORD m_CurrentInputTime;
	DWORD m_DlgFlags;
	CDlgLogin(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLogin)
	enum { IDD = IDD_DIALOGLOGIN };
	CProgressCtrl	m_Progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLogin)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLogin)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnChangeEdituserid();
	afx_msg void OnChangeEditpassword();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnChangeEdituserid2();
	afx_msg void OnChangeEditpassword2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOGIN_H__2F0DAEDD_85E2_432E_B3F1_38F0E38B048B__INCLUDED_)
