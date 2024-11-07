#if !defined(AFX_GPDLGVIEWMPVAR_H__FB48C953_A44B_4D0A_8C78_2E16C334CE67__INCLUDED_)
#define AFX_GPDLGVIEWMPVAR_H__FB48C953_A44B_4D0A_8C78_2E16C334CE67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPDlgViewMPVar.h : header file
//
#include "GP_AutoSizing.h"

/////////////////////////////////////////////////////////////////////////////
// GPDlgViewMPVar dialog

class GPDlgViewMPVar : public CDialog
{
// Construction
public:
	void UpdateTabs();
	GPDlgViewMPVar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(GPDlgViewMPVar)
	enum { IDD = IDD_DIALOGVIEWVARS };
	CListCtrl	m_ListObjName;
	CListCtrl	m_ListNamedData;
	CListCtrl	m_ListInput;
	CListCtrl	m_ListScrData;
	CListCtrl	m_ListDlgData;
	CListCtrl	m_ListScrObjMP;
	CListCtrl	m_ListDlgObjMP;
	CListCtrl	m_ListScrObjHot;
	CListCtrl	m_ListDlgObjHot;
	CListCtrl	m_ListScrHot;
	CListCtrl	m_ListDlgHot;
	CListCtrl	m_ListScrMenu;
	CListCtrl	m_ListDlgMenu;
	CListCtrl	m_ListScrMp;
	CListCtrl	m_ListDlgMp;
	CListCtrl	m_List2;
	CButton	m_btUpdate;
	CListCtrl	m_List1;
	CTabCtrl	m_Tab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPDlgViewMPVar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GPDlgViewMPVar)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeTabvar(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnupdate();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDblclkList13(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList14(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListnameddata(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	GP_AutoSizing AUSI;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPDLGVIEWMPVAR_H__FB48C953_A44B_4D0A_8C78_2E16C334CE67__INCLUDED_)
