#if !defined(AFX_DLGNEWSESSION_H__B46A2B4E_573F_467C_86FE_515AC5A7EE31__INCLUDED_)
#define AFX_DLGNEWSESSION_H__B46A2B4E_573F_467C_86FE_515AC5A7EE31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNewSession.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNewSession dialog

class CDlgNewSession : public CDialog
{
private:
	GP_AutoSizing AUSI;
// Construction
public:
	CDlgNewSession(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNewSession)
	enum { IDD = IDD_DIALOGNEWSESSION };
	CListCtrl	m_ListConnections;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNewSession)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNewSession)
	afx_msg void OnButtonlisten();
	afx_msg void OnStartNewSession();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDblclkListSessions(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNEWSESSION_H__B46A2B4E_573F_467C_86FE_515AC5A7EE31__INCLUDED_)
