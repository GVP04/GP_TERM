#if !defined(AFX_GPDLGFINDREPLACE_H__EF5A193C_51A5_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_GPDLGFINDREPLACE_H__EF5A193C_51A5_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPDlgFindReplace.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GPDlgFindReplace dialog

class GPDlgFindReplace : public CDialog
{
// Construction
public:
	UINT IdDlg;
	int DoMethod(const char *iStr,char *oStr);
	GPDlgFindReplace(UINT iIdDlg, CWnd* pParent = NULL);   // standard constructor
	~GPDlgFindReplace();
// Dialog Data
	//{{AFX_DATA(GPDlgFindReplace)
	enum { IDD = IDD_DIALOGFINDREPLACE };
	CButton	m_RadioUp;
	CButton	m_CheckCaps;
	CButton	m_CheckClip;
	CButton	m_CheckSel;
	CButton	m_CheckWord;
	CComboBox	m_ComboFind;
	CComboBox	m_ComboReplace;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPDlgFindReplace)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	GPMessage *GPMSG;
	// Generated message map functions
	//{{AFX_MSG(GPDlgFindReplace)
	afx_msg void OnButtonfindnext();
	afx_msg void OnButtonfindprev();
	afx_msg void OnButtonreplace();
	afx_msg void OnButtonreplaceall();
	afx_msg void OnCheckcaps();
	afx_msg void OnCheckclipboard();
	afx_msg void OnCheckselection();
	afx_msg void OnCheckword();
	afx_msg void OnSelchangeCombofind();
	afx_msg void OnEditchangeCombofind();
	afx_msg void OnEditchangeComboreplace();
	afx_msg void OnSelchangeComboreplace();
	afx_msg void OnRadioup();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPDLGFINDREPLACE_H__EF5A193C_51A5_11D4_970E_0080AD863699__INCLUDED_)
