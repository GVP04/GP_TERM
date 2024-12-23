#if !defined(AFX_GPSTATUSBARCTRL_H__DB48A1C2_54AE_11D4_A239_F20ED4B7B314__INCLUDED_)
#define AFX_GPSTATUSBARCTRL_H__DB48A1C2_54AE_11D4_A239_F20ED4B7B314__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPStatusBarCtrl.h : header file
//
#include "GP_HotKey.h"
#include "GPUnit.h"

/////////////////////////////////////////////////////////////////////////////
// GPStatusBarCtrl window

class GPStatusBarCtrl : public CStatusBarCtrl
{
	friend class GPUnit;
	friend class GPStatusBar;

// Construction
public:
	DWORD HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);
	GPStatusBarCtrl(UINT iUnitId);
	static const UINT uNPaneStyle;
	static const char *aSBCPaneStyle[];
	static const UINT  uSBCPaneStyle[];


// Attributes
public:
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
// Operations
public:
	virtual UINT DoMethod(const char *iStr, char *oStr);
	UINT GPSetProperty(char *iStr);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPStatusBarCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	static int HitTest(HWND iHWND, POINT po);
	static void OptimizeSize(HWND iHWND, int nPart, UINT uFlag=0);
	virtual ~GPStatusBarCtrl();

	// Generated message map functions
protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	//{{AFX_MSG(GPStatusBarCtrl)
	afx_msg void OnParentNotify(UINT message, LPARAM lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
protected:
	GPUnit **referGPU;
	UINT UnitId;
	HBITMAP hbp;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPSTATUSBARCTRL_H__DB48A1C2_54AE_11D4_A239_F20ED4B7B314__INCLUDED_)
