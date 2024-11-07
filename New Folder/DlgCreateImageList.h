#if !defined(AFX_DLGCREATE_H__32EB0801_2BF6_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_DLGCREATE_H__32EB0801_2BF6_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCreateImageList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateImageList dialog

class CDlgCreateImageList : public CDialog
{
// Construction
public:
	DWORD GetCreateFlag();
	DWORD SetCreateFlag(DWORD idwCreateFlag);
	CDlgCreateImageList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCreateImageList)
	enum { IDD = IDD_DLGCREATEIMAGELIST };
	CButton	m_BtnOk;
	CSpinButtonCtrl	m_SP4;
	CSpinButtonCtrl	m_SP3;
	CSpinButtonCtrl	m_SP2;
	CSpinButtonCtrl	m_SP1;
	UINT	m_EdY;
	UINT	m_EdX;
	UINT	m_EdInit;
	UINT	m_EdDelta;
	BOOL	m_S2;
	BOOL	m_S3;
	BOOL	m_S4;
	BOOL	m_S5;
	BOOL	m_S6;
	BOOL	m_S7;
	BOOL	m_S8;
	CString	m_Name;
	BOOL	m_S10;
	BOOL	m_S9;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCreateImageList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCreateImageList)
	virtual BOOL OnInitDialog();
	afx_msg void OnCancel();
	afx_msg void OnOk();
	afx_msg void OnChangeEditName();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	DWORD dwCreateFlag;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCREATE_H__32EB0801_2BF6_11D4_970E_0080AD863699__INCLUDED_)
