#if !defined(AFX_DLGVIEWITEM_H__1FF79F58_70D0_444C_8107_91391E4CACD5__INCLUDED_)
#define AFX_DLGVIEWITEM_H__1FF79F58_70D0_444C_8107_91391E4CACD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgViewItem.h : header file
//
#include "GP_AutoSizing.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgViewItem dialog

class CDlgViewItem : public CDialog
{
// Construction
public:
	CDlgViewItem(CString &iStr, char Delim1, char Delim2, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgViewItem)
	enum { IDD = IDD_DIALOGVIEWITEM };
	CListCtrl	m_ListItem;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgViewItem)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString SrcStr;
	char DelimAM;
	char DelimVM; 
	GP_AutoSizing AUSI;
	// Generated message map functions
	//{{AFX_MSG(CDlgViewItem)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIEWITEM_H__1FF79F58_70D0_444C_8107_91391E4CACD5__INCLUDED_)
