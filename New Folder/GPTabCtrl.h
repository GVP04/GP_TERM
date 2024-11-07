#if !defined(AFX_GPTABCTRL_H__EB29BB81_B9B8_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GPTABCTRL_H__EB29BB81_B9B8_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPTabCtrl.h : header file
//
#include "GP_HotKey.h"
#include "GPUnit.h"

/////////////////////////////////////////////////////////////////////////////
// GPTabCtrl window

class GPTabCtrl : public CTabCtrl
{
	friend class GPUnit;

// Construction
public:
	DWORD HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);
	static const char *aPaneStyle[5];
	static const UINT  uPaneStyle[5];
	GPTabCtrl(UINT iUnitId);
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
	//{{AFX_VIRTUAL(GPTabCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~GPTabCtrl();

	// Generated message map functions
protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	//{{AFX_MSG(GPTabCtrl)
	afx_msg void ParentNotify(UINT message, LPARAM lParam);
	afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGetobject(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemory(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFocusChange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedCapture(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClose();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	int m_LastHiLight;
	GPUnit **referGPU;
	UINT UnitId;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPTABCTRL_H__EB29BB81_B9B8_11D2_B27D_00600840D054__INCLUDED_)
