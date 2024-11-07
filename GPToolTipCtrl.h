#if !defined(AFX_GPTOOLTIPCTRL_H__0BE74791_01CB_45D1_8001_CFABB8E470AA__INCLUDED_)
#define AFX_GPTOOLTIPCTRL_H__0BE74791_01CB_45D1_8001_CFABB8E470AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPToolTipCtrl.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CGPToolTipCtrl window
class GPMessage;

class CGPToolTipCtrl : public CToolTipCtrl
{
// Construction
public:
	CGPToolTipCtrl();

// Attributes
public:
	const static UINT uNToolTipMethods;
	const static char *cArrToolTipMethods[];
	const static char *cArrToolTipMethodsParams[];

	const static UINT uNToolTipMethodsAll;
	const static char *cArrToolTipMethodsAll[];
	const static char *cArrToolTipMethodsParamsAll[];

// Operations
public:
	static DWORD StringFromToToolTipFlags(const char *iToolTipFlags, DWORD & convToolTipFlags);
	static DWORD StringFromToToolTipStyles(const char *iToolTipStyles, DWORD & convToolTipStyles);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGPToolTipCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	DWORD m_CreationStyle;
	virtual UINT GPCreate(HWND ihWnd, UINT iIdScrDlg, const char *iStileString, GPUnit **iGPU);
	BOOL DoMethod(const char *iStr, char *oStr, HWND ihWnd);
	virtual ~CGPToolTipCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGPToolTipCtrl)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	HWND m_PopupHWND;
	POINT m_PopupPoint;
	HWND mainHWND;
	UINT m_IdScrDlg;
	GPMessage *GPMSG;
	GPUnit **GPU;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPTOOLTIPCTRL_H__0BE74791_01CB_45D1_8001_CFABB8E470AA__INCLUDED_)
