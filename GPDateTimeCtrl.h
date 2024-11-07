#if !defined(AFX_GPDATETIMECTRL_H__8E96E6A1_B9B8_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GPDATETIMECTRL_H__8E96E6A1_B9B8_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPDateTimeCtrl.h : header file
//
#include "GP_HotKey.h"
#include "GPUnit.h"

/////////////////////////////////////////////////////////////////////////////
// GPDateTimeCtrl window

class GPDateTimeCtrl : public CDateTimeCtrl
{
	friend class GPUnit;

// Construction
public:
	DWORD HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);
	GPDateTimeCtrl(UINT iUnitId);
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
	//{{AFX_VIRTUAL(GPDateTimeCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	UINT MCStyle;
	CString FormatStr;
	virtual ~GPDateTimeCtrl();

	// Generated message map functions
protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	//{{AFX_MSG(GPDateTimeCtrl)
	afx_msg void OnCloseup(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDropdown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFormat(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFormatquery(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUserstring(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnWmkeydown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocus(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocus(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void ParentNotify(UINT message, LPARAM lParam);
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
	GPDateTimeCtrl * ObjHigh;
	GPDateTimeCtrl * ObjLow;
	GPUnit **referGPU;
	UINT UnitId;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPDATETIMECTRL_H__8E96E6A1_B9B8_11D2_B27D_00600840D054__INCLUDED_)
