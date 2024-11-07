#if !defined(AFX_GPADMISON_H__ADD8D803_1994_11D3_B27E_00600840D054__INCLUDED_)
#define AFX_GPADMISON_H__ADD8D803_1994_11D3_B27E_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPAdmIsOn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GPAdmIsOn dialog

class GPAdmIsOn : public CDialog
{
private:
	BOOL *Status;

// Construction
public:
	void UpdOk();
	GPAdmIsOn(BOOL *iStatus, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(GPAdmIsOn)
	enum { IDD = IDD_DIALOGADMISON };
	CButton	m_Ok;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPAdmIsOn)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GPAdmIsOn)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnKillfocusEdit1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPADMISON_H__ADD8D803_1994_11D3_B27E_00600840D054__INCLUDED_)
