#if !defined(AFX_DLGNEWSPR_H__42D78DB6_563F_459F_B90F_42B170A3557D__INCLUDED_)
#define AFX_DLGNEWSPR_H__42D78DB6_563F_459F_B90F_42B170A3557D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNewSpr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNewSpr dialog

class CDlgNewSpr : public CDialog
{
// Construction
public:
	CDlgNewSpr(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNewSpr)
	enum { IDD = IDD_DIALOGNEWSPR };
	UINT	m_nFields;
	CString	m_SprName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNewSpr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNewSpr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNEWSPR_H__42D78DB6_563F_459F_B90F_42B170A3557D__INCLUDED_)
