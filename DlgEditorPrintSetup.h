#if !defined(AFX_DLGEDITORPRINTSETUP_H__3BE4DA63_6547_447E_BDC5_1264C3F56CE3__INCLUDED_)
#define AFX_DLGEDITORPRINTSETUP_H__3BE4DA63_6547_447E_BDC5_1264C3F56CE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEditorPrintSetup.h : header file
//
#include "EditorPrintSettings.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgEditorPrintSetup dialog

class CDlgEditorPrintSetup : public CDialog
{
// Construction
public:
	CDlgEditorPrintSetup(CEditorPrintSettings *i_settings, CWnd* pParent = NULL);   // standard constructor
	CEditorPrintSettings *m_settings;

// Dialog Data
	//{{AFX_DATA(CDlgEditorPrintSetup)
	enum { IDD = IDD_DIALOGEDPRINT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEditorPrintSetup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgEditorPrintSetup)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnButtonpagesetup();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void UpdateSelection();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEDITORPRINTSETUP_H__3BE4DA63_6547_447E_BDC5_1264C3F56CE3__INCLUDED_)
