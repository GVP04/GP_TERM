#if !defined(AFX_DLGSEPARATEVIEW_H__21EE04EB_084B_465C_94BB_DB865630CE31__INCLUDED_)
#define AFX_DLGSEPARATEVIEW_H__21EE04EB_084B_465C_94BB_DB865630CE31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSeparateView.h : header file
//
#include "DlgViewInputAll.h"
#include "DlgViewOutput.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgSeparateView dialog

class CDlgSeparateView : public CDialog
{
friend class CGP_TermView;
friend class GPCurrent;

// Construction
public:
	BOOL DoMethod(const char *iMethod, char **oStr);
	void SetPartsParent(HWND hParent);
	void ResetParent();
	void SetViewMode(UINT iMode);
	CDlgSeparateView(CWnd* pParent = NULL);   // standard constructor
	char *AppendStringToOutput(const char *iStr);
	int AppendCharToOutput(char iCh, DWORD dwDelayFlag);
	CRect m_FrameLastSize;
	void FrameSizeMove();
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];

// Dialog Data
	//{{AFX_DATA(CDlgSeparateView)
	enum { IDD = IDD_DLGSEPARATEVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSeparateView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSeparateView)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	UINT m_ViewMode;
	void ResizeDialogs(CSize & sz);
	CDlgViewInputAll m_DlgViewInputAll;
	CDlgViewOutput m_DlgViewOutput;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSEPARATEVIEW_H__21EE04EB_084B_465C_94BB_DB865630CE31__INCLUDED_)
