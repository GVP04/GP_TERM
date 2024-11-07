#if !defined(AFX_GPDLGVIEWSPR_H__881BDC7A_20F2_416E_8B29_D785FAA52899__INCLUDED_)
#define AFX_GPDLGVIEWSPR_H__881BDC7A_20F2_416E_8B29_D785FAA52899__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPDlgViewSpr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GPDlgViewSpr dialog
#include "GP_AutoSizing.h"

class GPDlgViewSpr : public CDialog
{
// Construction
public:
	void ReFillData();
	GPDlgViewSpr(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(GPDlgViewSpr)
	enum { IDD = IDD_DIALOGVIEWSPR };
	CButton	m_BtGroup;
	CListCtrl	m_ListFilters;
	CButton	m_BtExecute;
	CComboBox	m_ComboMethods;
	CEdit	m_EditParams;
	CEdit	m_EditResult;
	CStatic	m_StatParams;
	CStatic	m_Stat3;
	CStatic	m_Stat2;
	CStatic	m_Stat1;
	CListCtrl	m_SprListView;
	CComboBox	m_ComboSpr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPDlgViewSpr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GPDlgViewSpr)
	afx_msg void OnSelchangeCombo1();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBtnexecute();
	afx_msg void OnSelchangeCombomethods();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtnadd();
	afx_msg void OnBtndelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	GP_AutoSizing AUSI;
private:
	void FillSprList(const char *SelName);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPDLGVIEWSPR_H__881BDC7A_20F2_416E_8B29_D785FAA52899__INCLUDED_)
