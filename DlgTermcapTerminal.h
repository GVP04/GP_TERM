#if !defined(AFX_DLGTERMCAPTERMINAL_H__709B76D5_A671_4B0D_B26F_6A073F2A06FF__INCLUDED_)
#define AFX_DLGTERMCAPTERMINAL_H__709B76D5_A671_4B0D_B26F_6A073F2A06FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTermcapTerminal.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTermcapTerminal dialog
#include "TermCap.h"

class CDlgTermcapTerminal : public CDialog
{
	friend class CDlgTermcap;
// Construction
public:
	void UpdateInfo();
	CDlgTermcapTerminal(CWnd* pParent = NULL);   // standard constructor
	~CDlgTermcapTerminal();

// Dialog Data
	//{{AFX_DATA(CDlgTermcapTerminal)
	enum { IDD = IDD_DLGTERMCAP_TERMINAL };
	CEdit	m_EditDescription;
	CEdit	m_EditNames;
	CEdit	m_EditName;
	CComboBox	m_ComboId;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTermcapTerminal)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTermcapTerminal)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnChangeEditDescription();
	afx_msg void OnChangeEditNames();
	afx_msg void OnChangeEditName();
	afx_msg void OnSelchangeComboId();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	DWORD m_dwUpdateFlag;
	CTermCap *m_pTermCap;
	GP_AutoSizing *DlgAutoSize;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTERMCAPTERMINAL_H__709B76D5_A671_4B0D_B26F_6A073F2A06FF__INCLUDED_)
