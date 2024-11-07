#if !defined(AFX_DLGVIEWINPUT_H__02320177_293B_4CA9_8F46_3C7DBDC364F0__INCLUDED_)
#define AFX_DLGVIEWINPUT_H__02320177_293B_4CA9_8F46_3C7DBDC364F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgViewInput.h : header file
//
#include "GPViewInput.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgViewInput dialog
#define IVTOOLBAR_NBTNS				29

class CDlgViewInputSet;

class CDlgViewInput : public CDialog
{
	friend class CDlgSeparateView;
	friend class CDlgViewInputSet;
// Construction
public:
	CDlgViewInputSet *m_CDlgViewInputSetPtr;
	void UpdateTB();
	char *AppendStringToInput(const char *iStr);
	int AppendCharToInput(char iCh);
	CDlgViewInput(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgViewInput();

// Dialog Data
	//{{AFX_DATA(CDlgViewInput)
	enum { IDD = IDD_DLGVIEWINPUT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgViewInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgViewInput)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CToolBarCtrl m_ToolBar;
	GPViewInput *m_Editor;
	GP_AutoSizing *DlgAutoSize;
	UINT m_uSelectionFlag;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIEWINPUT_H__02320177_293B_4CA9_8F46_3C7DBDC364F0__INCLUDED_)
