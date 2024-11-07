#if !defined(AFX_DLGERRORS_H__8C6906D5_48A5_454C_A45E_961CA0A1AC37__INCLUDED_)
#define AFX_DLGERRORS_H__8C6906D5_48A5_454C_A45E_961CA0A1AC37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgErrors.h : header file
//
#include "GP_AutoSizing.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgErrors dialog

class CDlgErrors : public CDialog
{
// Construction
public:
	CDlgErrors(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgErrors)
	enum { IDD = IDD_DLGERRORS };
	CButton	m_BtnClear;
	CTabCtrl	m_Tab;
	CListCtrl	m_List4;
	CListCtrl	m_List3;
	CListCtrl	m_List2;
	CListCtrl	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgErrors)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	GP_AutoSizing AUSI;

	// Generated message map functions
	//{{AFX_MSG(CDlgErrors)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonClear();
	afx_msg void OnButtonReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGERRORS_H__8C6906D5_48A5_454C_A45E_961CA0A1AC37__INCLUDED_)
