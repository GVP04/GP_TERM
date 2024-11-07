#if !defined(AFX_DLGTERMCAP_H__8C1B1A4F_7D12_45F2_AAE2_693DD2D2D73B__INCLUDED_)
#define AFX_DLGTERMCAP_H__8C1B1A4F_7D12_45F2_AAE2_693DD2D2D73B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTermcap.h : header file
//
#include "TermCap.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTermcap dialog
class CDlgTermcapKbd;
class CDlgTermcapEsc;
class CDlgTermcapTerminal;

class CDlgTermcap : public CDialog
{
// Construction
public:
	CDlgTermcap(CWnd* pParent = NULL);   // standard constructor
	~CDlgTermcap();

// Dialog Data
	//{{AFX_DATA(CDlgTermcap)
	enum { IDD = IDD_DLGTERMCAP };
	CComboBox	m_ComboTerminal;
	CTabCtrl	m_Tab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTermcap)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTermcap)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonclose();
	afx_msg void OnButtonsave();
	afx_msg void OnButtonapply();
	afx_msg void OnButtonload();
	afx_msg void OnButtonadd();
	afx_msg void OnButtondelete();
	afx_msg void OnSelchangeComboTerminal();
	afx_msg void OnButtonbrowseTC();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	virtual void UpdateAll();
	CDlgTermcapKbd *m_DlgTermcapKbd;
	CDlgTermcapEsc *m_DlgTermcapEsc;
	CDlgTermcapTerminal *m_DlgTermcapTerminal;
	GP_AutoSizing *DlgAutoSize;
	CTermCap m_TmpTermCap;
	DWORD m_dwUpdateFlag;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTERMCAP_H__8C1B1A4F_7D12_45F2_AAE2_693DD2D2D73B__INCLUDED_)
