#if !defined(AFX_GPBBUTTON_H__8FE066A1_B9B8_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GPBBUTTON_H__8FE066A1_B9B8_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPBButton.h : header file
//
#include "GP_HotKey.h"
#include "GPUnit.h"

/////////////////////////////////////////////////////////////////////////////
// GPBButton window

class GPBButton : public CBitmapButton
{
	friend class GPUnit;

// Construction
public:
	DWORD HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);
	GPBButton(UINT iUnitId);
	UINT DoMethod(const char *iStr, char *oStr);
	UINT GPSetProperty(char *iStr);
// Attributes
public:
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPButton)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString m_StateText;
	UINT m_uAutoClickDelay;
	virtual ~GPBButton();

	// Generated message map functions
protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();

	//{{AFX_MSG(GPBButton)
	afx_msg void OnClicked();
	afx_msg void OnDoubleclicked();
	afx_msg void OnPaintM();
	afx_msg void OnHiliteM();
	afx_msg void OnUnhiliteM();
	afx_msg void OnDisableM();
	afx_msg void OnSetFocusM();
	afx_msg void OnKillFocusM();
	afx_msg void ParentNotify(UINT message, LPARAM lParam);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bEnableMultiClick;
	BOOL m_EnableClick;
	UINT MouseLBState;
	DWORD OldState;
	GPUnit **referGPU;
	UINT UnitId;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPBBUTTON_H__8FE066A1_B9B8_11D2_B27D_00600840D054__INCLUDED_)
