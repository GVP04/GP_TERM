#if !defined(AFX_GPNOTIFYEDIT_H__E9BA0904_7955_49EF_A8DB_BE9AB42A1A49__INCLUDED_)
#define AFX_GPNOTIFYEDIT_H__E9BA0904_7955_49EF_A8DB_BE9AB42A1A49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPNotifyEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGPNotifyEdit window

#define GPNE_ENDEDIT	WM_USER+1000

class CGPNotifyEdit : public CEdit
{
// Construction
public:
	CGPNotifyEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGPNotifyEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	DWORD PtInEdit(CPoint point);
	HWND SetNotifyWnd(HWND hWnd);
	virtual ~CGPNotifyEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGPNotifyEdit)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	DWORD m_UpdateFlag;
	void ReleaseMyCapture();
	void SetMyCapture();
	HWND m_hNotifyWnd;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPNOTIFYEDIT_H__E9BA0904_7955_49EF_A8DB_BE9AB42A1A49__INCLUDED_)
