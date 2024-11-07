#if !defined(AFX_GPTREE_H__3310CE63_B9B8_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GPTREE_H__3310CE63_B9B8_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPTree.h : header file
//
#include "GP_HotKey.h"
#include "GPUnit.h"

/////////////////////////////////////////////////////////////////////////////
// GPTree window
#define TVIF_PARENT 0x1000

#include "GPWndPropertyArray.h"


class GPTree : public CTreeCtrl
{
	friend class GPUnit;

// Construction
public:
	GPTree(UINT iUnitId);
	UINT DoMethod(const char *iStr, char *oStr);
	UINT GPSetProperty(char *iStr);
	DWORD m_HelperMode;
// Attributes
public:
	const static CString StateToString(UINT iState);
	static UINT StringToState(const char* iStr);

	const static UINT nTVIS;
	const static UINT maskTVIS;
	const static char *TVISName[];
	const static UINT TVISUINT[];

	const static UINT nTVISEx;
	const static UINT maskTVISEx;
	const static char *TVISNameEx[];
	const static UINT TVISUINTEx[];

	const static UINT nTVGN;
	const static UINT TVGNUINT[];
	const static char *TVGNName[];

	const static UINT nTVIF;
	const static UINT maskTVIF;
	const static UINT TVIFUINT[];
	const static char *TVIFName[];

	const static UINT nTVE;
	const static char *TVEName[];
	const static UINT TVEUINT[];

	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPTree)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	UINT GetChildList(HTREEITEM hParent, HTREEITEM *hTreeArray, UINT nLevels, HTREEITEM hTreeStop);
	BOOL m_bDragROOT;
	BOOL ItemString(HTREEITEM iIt, char *str, char iDelimeter = 0x7f);
	BOOL ItemString(HTREEITEM iIt, char *oStr, char iDelimeter, const DWORD *iFields);
	virtual ~GPTree();
	DWORD GetExtendedStyle();
	DWORD SetExtendedStyle(DWORD dwStyle);

	// Generated message map functions
protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	HTREEITEM HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);
	BOOL IsItemExpanded (HTREEITEM hItem);
	void CopyChildren (HTREEITEM hDest, HTREEITEM hSrc, UINT nDelta);
	void CopyChildren (HTREEITEM hDest, HTREEITEM hSrc);
	void CopyTree (HTREEITEM hDest, HTREEITEM hSrc, int iDelta);
	void MoveTree (HTREEITEM hDest, HTREEITEM hSrc);
	BOOL IsChildOf (HTREEITEM hItem1, HTREEITEM hItem2);
	BOOL m_bDragging;
	HTREEITEM m_hDragItem;

	//{{AFX_MSG(GPTree)
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocus(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemory(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRdblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReturn(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocus(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginrdrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSingleExpand(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGetInfotip(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void ParentNotify(UINT message, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_ClearDropHilight;
	GPUnit **referGPU;
	UINT UnitId;
	GP_RarefiedArr<HTREEITEM> ItemIdArray;
	UINT oldState;
	CGPWndPropertyArray *GPPA_Image;
	CGPWndPropertyArray *GPPA_SelImage;
	CGPWndPropertyArray *GPPA_lValue;
	CGPWndPropertyArray *GPPA_IdItem;
	CGPWndPropertyArray *GPPA_IdParent;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPTREE_H__3310CE63_B9B8_11D2_B27D_00600840D054__INCLUDED_)
