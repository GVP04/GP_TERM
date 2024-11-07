#if !defined(AFX_DLGMETHODS_H__3792CA21_7C03_11D4_A239_966D818E7F36__INCLUDED_)
#define AFX_DLGMETHODS_H__3792CA21_7C03_11D4_A239_966D818E7F36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMethods.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMethods dialog

class CDlgMethods : public CDialog
{
// Construction
public:
	CDlgMethods(CWnd* pParent = NULL);   // standard constructor
	static void FillMethodCombo(int iUnitType,CComboBox *MetCombo, GPUnit *iGPU, DWORD dwSubType);
	static void GetParamStr(int UnitType, UINT MetData,CString &MetName,CString &MetParam);
// Dialog Data
	//{{AFX_DATA(CDlgMethods)
	enum { IDD = IDD_DLGMETHODS };
	CButton	m_CheckParam;
	CEdit	m_Edit;
	CComboBox	m_ComboMethod;
	CComboBox	m_ComboType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMethods)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMethods)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeType();
	afx_msg void OnChangeMethod();
	afx_msg void OnClose();
	afx_msg void OnCheckParam();
	afx_msg void OnButtonBuff();
	afx_msg void OnButtonInsert();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMETHODS_H__3792CA21_7C03_11D4_A239_966D818E7F36__INCLUDED_)
