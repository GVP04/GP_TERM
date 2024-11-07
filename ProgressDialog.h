#if !defined(AFX_PROGRESSDIALOG_H__AF9AB567_9485_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_PROGRESSDIALOG_H__AF9AB567_9485_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ProgressDialog dialog

class ProgressDialog : public CDialog
{
// Construction
public:
	void SetProgressPos(int iPos);
	void SetProgressRange(int iStart, int iEnd);
	ProgressDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ProgressDialog)
	enum { IDD = IDD_DIALOGPROGRESS };
	CProgressCtrl	m_Progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ProgressDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ProgressDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSDIALOG_H__AF9AB567_9485_11D4_970E_0080AD863699__INCLUDED_)
