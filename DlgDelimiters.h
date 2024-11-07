#if !defined(AFX_DLGDELIMITERS_H__C473CEAC_D6D8_46C4_831D_C79C7A6EE7FB__INCLUDED_)
#define AFX_DLGDELIMITERS_H__C473CEAC_D6D8_46C4_831D_C79C7A6EE7FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDelimiters.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDelimiters dialog
class GP_comm;

class CDlgDelimiters : public CDialog
{
// Construction
public:
	CDlgDelimiters(GP_comm *imComm, CWnd* pParent = NULL);   // standard constructor
	GP_comm *mComm;

// Dialog Data
	//{{AFX_DATA(CDlgDelimiters)
	enum { IDD = IDD_DLGDELIMITERS };
	UINT	m_IN1;
	UINT	m_IN2;
	UINT	m_IN3;
	UINT	m_IN4;
	UINT	m_IN5;
	UINT	m_IN6;
	UINT	m_OUT1;
	UINT	m_OUT2;
	UINT	m_OUT3;
	UINT	m_OUT5;
	UINT	m_OUT4;
	UINT	m_OUT6;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDelimiters)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDelimiters)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnChangeEditinput();
	afx_msg void OnButtonQM();
	afx_msg void OnButtonD3();
	afx_msg void OnButton8();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDELIMITERS_H__C473CEAC_D6D8_46C4_831D_C79C7A6EE7FB__INCLUDED_)
