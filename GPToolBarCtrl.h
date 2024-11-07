#if !defined(AFX_GPTOOLBARCTRL_H__DB48A1C1_54AE_11D4_A239_F20ED4B7B314__INCLUDED_)
#define AFX_GPTOOLBARCTRL_H__DB48A1C1_54AE_11D4_A239_F20ED4B7B314__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPToolBarCtrl.h : header file
//
#include "GP_HotKey.h"
#include "GPUnit.h"
#include "GPMenu.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// GPToolBarCtrl window

class GPToolBarCtrl : public CToolBarCtrl
{
	friend class GPUnit;

	// Construction
public:
	DWORD HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);
	GPToolBarCtrl(UINT iUnitId);
	static const UINT  uBtnState[8];
	static const char *cBtnState[8];
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
	//{{AFX_VIRTUAL(GPToolBarCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	int aPopupMenuInd[TOOLBAR_ID_COUNT];
	GPMenu ** RefDlgGPMenu;
	void SetDropDownMenu(GPMenu **iDlgGPMenu);
	static void GPTranslateTBCtrlState(const char *oStr, UINT & iState);
	static void GPTranslateTBCtrlStyle(const char *oStr, UINT & iStyle);
	static void GPTranslateTBCtrlState(UINT iState, char *oStr);
	static void GPTranslateTBCtrlStyle(UINT iStyle, char *oStr);
	virtual ~GPToolBarCtrl();

	// Generated message map functions
protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	//{{AFX_MSG(GPToolBarCtrl)
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

#endif // !defined(AFX_GPTOOLBARCTRL_H__DB48A1C1_54AE_11D4_A239_F20ED4B7B314__INCLUDED_)
