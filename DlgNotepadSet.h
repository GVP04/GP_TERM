#if !defined(AFX_DLGNOTEPADSET_H__07A61DC0_F0CC_49D5_B3B8_DF8B5D309B0B__INCLUDED_)
#define AFX_DLGNOTEPADSET_H__07A61DC0_F0CC_49D5_B3B8_DF8B5D309B0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNotepadSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNotepadSet dialog

class CDlgNotepadSet : public CDialog
{
// Construction
public:
	static void GetNotepadSettings(CString &csResult);
	static void GetNotepadTypeSettings(const char * iSection,CString &csResult);
	static void SetNotepadTypeSettings(const char * iSection, CString &csNewSet);
	static void SetNotepadSettings(CString &csNewSet);
	CString m_csSectionName;
	CDlgNotepadSet(CWnd* pParent = NULL);   // standard constructor
	static const UINT uNEntryes;
	static const char *cArrEntryName[];
	static const DWORD uArrEntryType[];
	static const DWORD uArrIDS[];

// Dialog Data
	//{{AFX_DATA(CDlgNotepadSet)
	enum { IDD = IDD_DIALOGNOTEPADSET };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNotepadSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNotepadSet)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBtnupdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNOTEPADSET_H__07A61DC0_F0CC_49D5_B3B8_DF8B5D309B0B__INCLUDED_)
