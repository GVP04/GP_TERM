#if !defined(AFX_DLGTERMSET_H__FF953661_1F2B_11D3_B27E_00600840D054__INCLUDED_)
#define AFX_DLGTERMSET_H__FF953661_1F2B_11D3_B27E_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTermSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTermSet dialog

class CDlgTermSet : public CDialog
{
// Construction
public:
	COLORREF m_curOutScrBkg;
	CDlgTermSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTermSet)
	enum { IDD = IDD_DIALOGTERMSET };
	CComboBox	m_OutScrBkgColorCombo;
	CComboBox	m_DefFrgClr;
	CComboBox	m_DefBkgClr;
	CComboBox	m_SizingModeCombo;
	CButton	m_CheckExit;
	CButton	m_CheckExitPrg;
	CButton	m_CheckKeybBuff;
	CButton	m_CheckBeep;
	CButton	m_CheckPrint;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTermSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTermSet)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtoncolors();
	virtual void OnCancel();
	afx_msg void OnButtoncolorsOutScrBkg();
	afx_msg void OnButtonerrors();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTERMSET_H__FF953661_1F2B_11D3_B27E_00600840D054__INCLUDED_)
