#if !defined(AFX_DLGVIEWCONTEXTMENUMETHODS_H__E4F6F7B0_CE12_4C9E_81BB_C8ACDB073BD6__INCLUDED_)
#define AFX_DLGVIEWCONTEXTMENUMETHODS_H__E4F6F7B0_CE12_4C9E_81BB_C8ACDB073BD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgViewContextMenuMethods.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgViewContextMenuMethods dialog

class CDlgViewContextMenuMethods : public CDialog
{
// Construction
public:
	CDlgViewContextMenuMethods(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgViewContextMenuMethods)
	enum { IDD = IDD_DIALOGVIEWCONTMENUMETH };
	CButton	m_btnExecute2;
	CComboBox	m_ComboMethods;
	CButton	m_btnExecute;
	CEdit	m_EditParams;
	CEdit	m_EditResult;
	CStatic	m_StatParams;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgViewContextMenuMethods)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgViewContextMenuMethods)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBtnexecute();
	afx_msg void OnSelchangeCombomethods();
	afx_msg void OnDestroy();
	afx_msg void OnBtnexecute2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	GP_AutoSizing AUSI;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIEWCONTEXTMENUMETHODS_H__E4F6F7B0_CE12_4C9E_81BB_C8ACDB073BD6__INCLUDED_)
