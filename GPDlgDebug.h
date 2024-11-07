#if !defined(AFX_GPDLGDEBUG_H__3176AE4F_BE35_4CF4_9AE3_62A8F916DEE4__INCLUDED_)
#define AFX_GPDLGDEBUG_H__3176AE4F_BE35_4CF4_9AE3_62A8F916DEE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPDlgDebug.h : header file
//
#include "GP_AutoSizing.h"

/////////////////////////////////////////////////////////////////////////////
// GPDlgDebug dialog

class GPDlgDebug : public CDialog
{
// Construction
public:
	GPDlgDebug(CWnd* pParent = NULL);   // standard constructor
	~GPDlgDebug();
// Dialog Data
	//{{AFX_DATA(GPDlgDebug)
	enum { IDD = IDD_DIALOGDEBUG };
	CButton	m_chkAUpdate;
	CStatic	m_statWath;
	CStatic	m_statStack;
	CButton	m_btnDel;
	CButton	m_btnAdd;
	CButton	m_btnUpdate;
	CButton	m_btnGo;
	CButton	m_btnBreak;
	CListCtrl	m_ListWatch;
	CButton	m_btnVarTable;
	CEdit	m_EditNPrgLine;
	CListCtrl	m_ListStack;
	CEdit	m_EditNGO;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPDlgDebug)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GPDlgDebug)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtngo();
	afx_msg void OnBtnbreak();
	afx_msg void OnBtnupdate();
	afx_msg void OnBtnvartable();
	afx_msg void OnButtonadd();
	afx_msg void OnButtondel();
	afx_msg void OnDblclkListvars(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void FillData();
	CRichEditCtrl *m_RTFPrg;
	GP_AutoSizing AUSI;
	int m_CurLine;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPDLGDEBUG_H__3176AE4F_BE35_4CF4_9AE3_62A8F916DEE4__INCLUDED_)
