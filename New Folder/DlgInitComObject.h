#if !defined(AFX_DLGINITCOMOBJECT_H__9C3F5AE1_D745_11D4_AB17_004854899618__INCLUDED_)
#define AFX_DLGINITCOMOBJECT_H__9C3F5AE1_D745_11D4_AB17_004854899618__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInitComObject.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInitComObject dialog

class CDlgInitComObject : public CDialog
{
// Construction
public:
	CDlgInitComObject(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInitComObject)
	enum { IDD = IDD_DLGCONTROLINIT };
	CString	m_EditCLSID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInitComObject)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInitComObject)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINITCOMOBJECT_H__9C3F5AE1_D745_11D4_AB17_004854899618__INCLUDED_)
