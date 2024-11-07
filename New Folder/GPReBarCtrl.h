#if !defined(AFX_GPREBARCTRL_H__DB48A1C2_59AE_11D4_A239_F21ED4B7B114__INCLUDED_)
#define AFX_GPREBARCTRL_H__DB48A1C2_59AE_11D4_A239_F21ED4B7B114__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPStatusBarCtrl.h : header file
//
#include "GP_HotKey.h"
#include "GPUnit.h"

/////////////////////////////////////////////////////////////////////////////
// GPReBarCtrl window

class GPReBarCtrl : public CReBarCtrl
{
	friend class GPUnit;

// Construction
public:
	DWORD HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);
	GPReBarCtrl(UINT iUnitId);


// Attributes
public:
	const static UINT uNBandStyle;
	static const char *aBandStyle[];
	static const UINT  uBandStyle[];

	const static UINT uNBandMask;
	static const char *aBandMask[];
	static const UINT  uBandMask[];

	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
// Operations
public:
	virtual UINT DoMethod(const char *iStr, char *oStr);
	UINT GPSetProperty(char *iStr);
	static const char * ReTranslateBandStyle(UINT iType);
	static const UINT TranslateBandStyle(const char * iStr);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPReBarCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~GPReBarCtrl();

	// Generated message map functions
protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	//{{AFX_MSG(GPReBarCtrl)
	afx_msg void OnParentNotify(UINT message, LPARAM lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
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

#endif // !defined(AFX_GPREBARCTRL_H__DB48A1C2_59AE_11D4_A239_F21ED4B7B114__INCLUDED_)
