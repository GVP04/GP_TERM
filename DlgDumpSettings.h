#if !defined(AFX_DLGDUMPSETTINGS_H__8D01F961_B9B8_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_DLGDUMPSETTINGS_H__8D01F961_B9B8_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDumpSettings.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDumpSettings dialog

class CDlgDumpSettings : public CDialog
{
// Construction
public:
	CDlgDumpSettings(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDumpSettings)
	enum { IDD = IDD_DIALOGDUMPSETTINGS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDumpSettings)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDumpSettings)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonViewSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDUMPSETTINGS_H__8D01F961_B9B8_11D2_B27D_00600840D054__INCLUDED_)
