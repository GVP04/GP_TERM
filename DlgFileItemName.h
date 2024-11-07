#if !defined(AFX_DLGFILEITEMNAME_H__4745D988_70E2_4241_A5B6_C66BCDFF09D7__INCLUDED_)
#define AFX_DLGFILEITEMNAME_H__4745D988_70E2_4241_A5B6_C66BCDFF09D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFileItemName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFileItemName dialog

class CDlgFileItemName : public CDialog
{
// Construction
public:
	const CString SetItemName(const char * iName);
	const CString SetFileName(const char * iName);
	const CString GetItemName();
	const CString GetFileName();
	CDlgFileItemName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFileItemName)
	enum { IDD = IDD_DLGFILEITEMNAME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFileItemName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFileItemName)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_ItemName;
	CString m_FileName;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFILEITEMNAME_H__4745D988_70E2_4241_A5B6_C66BCDFF09D7__INCLUDED_)
