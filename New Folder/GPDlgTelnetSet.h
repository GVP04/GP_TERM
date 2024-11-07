#if !defined(AFX_GPDLGTELNETSET_H__1A4D0521_FEFA_11D2_87EF_F529B13A5E4D__INCLUDED_)
#define AFX_GPDLGTELNETSET_H__1A4D0521_FEFA_11D2_87EF_F529B13A5E4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPDlgTelnetSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GPDlgTelnetSet dialog
#include "GP_comm.h"

class GPDlgTelnetSet : public CDialog
{
// Construction
private:
	int m_AdvancedMode;
	GP_comm *GPc;

public:
	void SetAdvancedMode(int iMode);
	GPDlgTelnetSet(GP_comm *iGPc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(GPDlgTelnetSet)
	enum { IDD = IDD_DIALOGTELSET };
	CComboBox	m_ComboShutDown;
	CComboBox	m_ComboSvcWait;
	CEdit	m_EditName;
	CButton	m_btnAdvanced;
	CComboBox	m_ComboType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPDlgTelnetSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(GPDlgTelnetSet)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombotermtype();
	afx_msg void OnButtondelimiters();
	afx_msg void OnButtonadvanced();
	afx_msg void OnButtonssh();
	afx_msg void OnChangeEditname();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPDLGTELNETSET_H__1A4D0521_FEFA_11D2_87EF_F529B13A5E4D__INCLUDED_)
