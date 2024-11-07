#if !defined(AFX_GPMONTHCALCTRL_H__8E96E6A1_B9B8_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GPMONTHCALCTRL_H__8E96E6A1_B9B8_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPMonthCalCtrl.h : header file
//
#include "GP_HotKey.h"
#include "GPUnit.h"

/////////////////////////////////////////////////////////////////////////////
// GPMonthCalCtrl window

class GPMonthCalCtrl : public CMonthCalCtrl
{
	friend class GPUnit;

// Construction
public:
	DWORD HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);
	GPMonthCalCtrl(UINT iUnitId);
	UINT DoMethod(const char *iStr, char *oStr);
	UINT GPSetProperty(char *iStr);

// Attributes
public:
	const static UINT unClrMask;
	const static char *cArrClrMask[];
	const static UINT uArrClrMask[];
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
	const static UINT uNHTI;
	const static char *cArrHTI[];
	const static UINT uArrHTI[];
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPMonthCalCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~GPMonthCalCtrl();

	// Generated message map functions
protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	//{{AFX_MSG(GPMonthCalCtrl)
	afx_msg void ParentNotify(UINT message, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetdaystate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelect(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcapture(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
private:		
	GPMonthCalCtrl * ObjHigh;
	GPMonthCalCtrl * ObjLow;
	GPUnit **referGPU;
	UINT UnitId;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPMONTHCALCTRL_H__8E96E6A1_B9B8_11D2_B27D_00600840D054__INCLUDED_)
