#if !defined(AFX_GPHEADER_H__1419F143_B9B8_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GPHEADER_H__1419F143_B9B8_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPHeader.h : header file
//
#include "GP_HotKey.h"
#include "GPUnit.h"

/////////////////////////////////////////////////////////////////////////////
// GPHeader window

class GPHeader : public CHeaderCtrl
{
	friend class GPUnit;
	friend class GPListCtr;

// Construction
public:
	GPHeader(UINT iUnitId);
// Attributes
public:
	DWORD HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPHeader)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~GPHeader();
	UINT DoMethod(const char *iStr, char *oStr);
	UINT GPSetProperty(const char *iStr);
	// Generated message map functions
protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	//{{AFX_MSG(GPHeader)
	afx_msg void OnTrack(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemdblclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBegintrack(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndtrack(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDividerdblclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnddrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchanging(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFILTERCHANGE(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFILTERBTNCLICK(NMHDR* pNMHDR, LRESULT* pResult);
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
	GPUnit **referGPU;
	UINT UnitId;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPHEADER_H__1419F143_B9B8_11D2_B27D_00600840D054__INCLUDED_)
