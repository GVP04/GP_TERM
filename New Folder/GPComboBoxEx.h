#if !defined(AFX_GPCOMBOBOXEX_H__906CF2C4_B9B8_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GPCOMBOBOXEX_H__906CF2C4_B9B8_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPComboBoxEx.h : header file
//
#include "GP_HotKey.h"
#include "GPUnit.h"

/////////////////////////////////////////////////////////////////////////////
// GPComboBoxEx window

class GPComboBoxEx : public CComboBoxEx
{
	friend class GPUnit;

// Construction
public:
	GPComboBoxEx(UINT iUnitId);

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
	//{{AFX_VIRTUAL(GPComboBoxEx)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	DWORD m_LCDOflag;
	int AddChar(char iChar, DWORD iFlags);
	virtual ~GPComboBoxEx();
	UINT DoMethod(const char *iStr, char *oStr);
	UINT GPSetProperty(char *iStr);

	// Generated message map functions
protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	//{{AFX_MSG(GPComboBoxEx)
	afx_msg void ParentNotify(UINT message, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bAutoFocus;
	UINT m_DefSelImage;
	UINT m_DefIndent;
	UINT m_DefLPARAM;
	UINT m_DefOverlay;
	UINT m_DefImage;
	UINT m_uMaxDroppedHeight;
	UINT m_uMinDroppedHeight;
	GPUnit **referGPU;
	UINT UnitId;
	UINT m_MinListWidth;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPCOMBOBOXEX_H__906CF2C4_B9B8_11D2_B27D_00600840D054__INCLUDED_)
