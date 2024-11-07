

#if !defined(AFX_GPTOOLBAR_H__DB48A1C1_54AE_11D4_A239_F20ED4B7B314__INCLUDED_)
#define AFX_GPTOOLBAR_H__DB48A1C1_54AE_11D4_A239_F20ED4B7B314__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPToolBar.h : header file
//
#include "GP_HotKey.h"
#include "GPUnit.h"
#include "GPMenu.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// GPToolBar window

class GPToolBar : public CToolBar
{
	friend class GPUnit;

	// Construction
public:
	DWORD HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);
	GPToolBar(UINT iUnitId);

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
	//{{AFX_VIRTUAL(GPToolBar)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	int aPopupMenuInd[TOOLBAR_ID_COUNT];
	GPMenu ** RefDlgGPMenu;
	void SetDropDownMenu(GPMenu **iDlgGPMenu);
	static void GPTranslateTBState(const char *oStr, UINT & iState);
	static void GPTranslateTBStyle(const char *oStr, UINT & iStyle);
	static void GPTranslateTBStyle(UINT iStyle, char *oStr);
	static void GPTranslateTBState(UINT iState, char *oStr);
	virtual ~GPToolBar();

	// Generated message map functions
protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	//{{AFX_MSG(GPToolBar)
	afx_msg void OnParentNotify(UINT message, LPARAM lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
protected:
	GPTextArray *aToolTipArr;
	BOOL m_bEnableMultiClick;
	BOOL m_EnableClick;
	GPUnit **referGPU;
	UINT UnitId;
	HBITMAP hbp;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPTOOLBAR_H__DB48A1C1_54AE_11D4_A239_F20ED4B7B314__INCLUDED_)
