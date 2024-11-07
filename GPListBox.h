#if !defined(AFX_GPLISTBOX_H__906CF2C3_B9B8_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GPLISTBOX_H__906CF2C3_B9B8_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPListBox.h : header file
//
#include "GP_HotKey.h"
#include "GPUnit.h"

/////////////////////////////////////////////////////////////////////////////
// GPListBox window

class GPListBox : public CListBox
{
	friend class GPUnit;

// Construction
public:
	BOOL SetreferGPU(GPUnit **iGPU);
	GPListBox(UINT iUnitId);
// Attributes
public:
	DWORD HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
	GP_RarefiedArr<CString> *ItemDataArray;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPListBox)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	DWORD m_LCDOflag;
	int AddChar(char iChar, DWORD iFlags);
	char * GetSelectedItem(char *iStr);
	virtual ~GPListBox();
	UINT DoMethod(const char *iStr, char *oStr);
	UINT GPSetProperty(const char *iStr);

	// Generated message map functions
protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	//{{AFX_MSG(GPListBox)
	afx_msg void OnSelchange();
	afx_msg void OnErrspace();
	afx_msg void OnNotifyKillfocus();
	afx_msg void OnSelcancel();
	afx_msg void OnNotifySetfocus();
	afx_msg void ParentNotify(UINT message, LPARAM lParam);
	afx_msg int CharToItem(UINT nChar, UINT nIndex);
	afx_msg void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
	afx_msg int VKeyToItem(UINT nKey, UINT nIndex);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnDblclk();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bAutoFocus;
	GPUnit **referGPU;
	UINT UnitId;
	int m_LastHighLight;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPLISTBOX_H__906CF2C3_B9B8_11D2_B27D_00600840D054__INCLUDED_)
