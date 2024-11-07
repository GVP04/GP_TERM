#if !defined(AFX_GPSTATIC_H__E03B68C1_B9B8_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GPSTATIC_H__E03B68C1_B9B8_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPStatic.h : header file
//
#include "GP_HotKey.h"
#include "GPUnit.h"
/////////////////////////////////////////////////////////////////////////////
// GPStatic window

class GPStatic : public CStatic
{
	friend class GPUnit;

// Construction
public:
	DWORD HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);
	GPStatic(UINT iUnitId);
// Attributes
public:
	HBITMAP hbmtodelete;
	HICON hicontodelete;
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPStatic)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	int AddChar(char iChar, DWORD iFlags);
	virtual ~GPStatic();
	virtual UINT DoMethod(const char *iStr, char *oStr);
	UINT GPSetProperty(char *iStr);

	// Generated message map functions
protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	//{{AFX_MSG(GPStatic)
	afx_msg void OnClicked();
	afx_msg void OnDblClk();
	afx_msg void OnEnable();
	afx_msg void OnDisable();
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
protected:
	GPUnit **referGPU;
	UINT UnitId;
	HBITMAP hbp;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPSTATIC_H__E03B68C1_B9B8_11D2_B27D_00600840D054__INCLUDED_)
