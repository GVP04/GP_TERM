#if !defined(AFX_DLGDRAWEDIT_H__A4B595C1_A03D_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_DLGDRAWEDIT_H__A4B595C1_A03D_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDrawEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDrawEdit dialog
#include "GPDrawWnd.h"

class CDlgDrawEdit : public CDialog
{
// Construction
public:
	void ReloadEdit();
	CDlgDrawEdit(GPDrawWnd *iDrawUnit,CWnd* pParent = NULL);   // standard constructor
	~CDlgDrawEdit();

// Dialog Data
	//{{AFX_DATA(CDlgDrawEdit)
	enum { IDD = IDD_DIALOGDRAWEDIT };
	CButton	m_BtReload;
	CEdit	m_EditRegion;
	CEdit	m_EditURect;
	CEdit	m_EditUPoint;
	CEdit	m_EditInt;
	CEdit	m_EditDouble;
	CButton	m_BtRedraw;
	CEdit	m_EditBrush;
	CEdit	m_EditPen;
	CEdit	m_EditFont;
	CTabCtrl	m_Tab;
	CEdit	m_EditText;
	CEdit	m_EditRect;
	CEdit	m_EditPoint;
	CEdit	m_EditItems;
	CEdit	m_EditIcon;
	CEdit	m_EditColor;
	CButton	m_btColor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDrawEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	GPDrawWnd *DrawUnit;
	GP_AutoSizing *DlgAutoSize;
	void UpdateTabs();
	// Generated message map functions
	//{{AFX_MSG(CDlgDrawEdit)
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtcolor();
	afx_msg void OnButtonRedraw();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButtonreload();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDRAWEDIT_H__A4B595C1_A03D_11D4_970E_0080AD863699__INCLUDED_)
