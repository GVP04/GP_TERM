#if !defined(AFX_DLGTERMCAPESCLINE_H__CF082FA4_7E09_4ECE_9CF1_2D055F2E1BC2__INCLUDED_)
#define AFX_DLGTERMCAPESCLINE_H__CF082FA4_7E09_4ECE_9CF1_2D055F2E1BC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTermcapEscLine.h : header file
//
#include "TermCap.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTermcapEscLine dialog

class CDlgTermcapEscLine : public CDialog
{
// Construction
public:
	CDlgTermcapEscLine(CTermCap *i_pTermCap, PTERMCAPESCITEM ipEscItem, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTermcapEscLine)
	enum { IDD = IDD_DLGTERMCAPESCLINE };
	CComboBox	m_ComboEscValue2;
	CComboBox	m_ComboEscValue;
	CComboBox	m_ComboEscType;
	CButton	m_CheckEnable;
	CListCtrl	m_List;
	CEdit	m_EditGroup;
	CEdit	m_EditTCName;
	CEdit	m_EditDescription;
	CComboBox	m_ComboId;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTermcapEscLine)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTermcapEscLine)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnButtonup2();
	afx_msg void OnButtonup();
	afx_msg void OnButtoninsert();
	afx_msg void OnButtondown2();
	afx_msg void OnButtondown();
	afx_msg void OnButtonadd();
	afx_msg void OnButtondelete();
	afx_msg void OnCheckEnable();
	afx_msg void OnCloseupComboId();
	afx_msg void OnSelchangeComboID();
	afx_msg void OnClickListEsc(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCloseupComboescvalue();
	afx_msg void OnCloseupComboesctype();
	afx_msg void OnCloseupComboescvalue2();
	afx_msg void OnChangeEditDescription();
	afx_msg void OnChangeEditTCName();
	afx_msg void OnChangeEditGroup();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int GetCurEscSubItem();
	void UpdateInfo();
	CTermCap *m_pTermCap;
	PTERMCAPESCITEM m_pEscItem;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTERMCAPESCLINE_H__CF082FA4_7E09_4ECE_9CF1_2D055F2E1BC2__INCLUDED_)
