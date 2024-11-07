#if !defined(AFX_SENDPICKFLPROGRESS_H__26B77C64_F74C_11D2_B27E_00600840D054__INCLUDED_)
#define AFX_SENDPICKFLPROGRESS_H__26B77C64_F74C_11D2_B27E_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SendPickFlProgress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SendPickFlProgress dialog

class SendPickFlProgress : public CDialog
{
// Construction
public:
	void GPClose();
	SendPickFlProgress(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SendPickFlProgress)
	enum { IDD = IDD_DIALOGSENDFILE };
	CProgressCtrl	m_progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SendPickFlProgress)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SendPickFlProgress)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnClose();
	afx_msg void OnAltB();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDPICKFLPROGRESS_H__26B77C64_F74C_11D2_B27E_00600840D054__INCLUDED_)
