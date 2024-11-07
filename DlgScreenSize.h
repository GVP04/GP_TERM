#if !defined(AFX_DLGSCREENSIZE_H__72AE4709_5B29_40B1_9C8A_0EF068806D90__INCLUDED_)
#define AFX_DLGSCREENSIZE_H__72AE4709_5B29_40B1_9C8A_0EF068806D90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgScreenSize.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgScreenSize dialog

class CDlgScreenSize : public CDialog
{
// Construction
public:
	void SetScreenSize();
	void SaveSettings();
	static const Size GetSizeFromString(const char *iStr);
	CDlgScreenSize(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgScreenSize)
	enum { IDD = IDD_DLGSCREENSIZE };
	CComboBox	m_ComboCommand;
	CComboBox	m_ComboSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgScreenSize)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL VerifyData(BOOL bShowMessage);
	CString csCurSize;
	CString csCurCommand;

	// Generated message map functions
	//{{AFX_MSG(CDlgScreenSize)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnApply();
	afx_msg void OnButtonDeleteSize();
	afx_msg void OnButtonDeleteCommand();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSCREENSIZE_H__72AE4709_5B29_40B1_9C8A_0EF068806D90__INCLUDED_)
