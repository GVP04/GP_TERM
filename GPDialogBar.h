#if !defined(AFX_GPDIALOGBAR_H__DB48A9C2_54AE_18D4_A239_F20ED4B7B314__INCLUDED_)
#define AFX_GPDIALOGBAR_H__DB48A9C2_54AE_18D4_A239_F20ED4B7B314__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPDialogBar.h : header file
//
#include "GP_HotKey.h"
#include "GPUnit.h"

/////////////////////////////////////////////////////////////////////////////
// GPDialogBar window

class GPDialogBar : public CDialogBar
{
	friend class GPUnit;

// Construction
public:
	GPDialogBar(UINT iUnitId);
	UINT indicators[32];
// Attributes
public:
	DWORD HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
// Operations
public:
	virtual UINT DoMethod(const char *iStr, char *oStr);
	UINT GPSetProperty(char *iStr);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPDialogBar)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~GPDialogBar();

	// Generated message map functions
protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	//{{AFX_MSG(GPDialogBar)
	afx_msg void OnParentNotify(UINT message, LPARAM lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnNcHitTest(CPoint point);
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

#endif // !defined(AFX_GPDIALOGBAR_H__DB48A9C2_54AE_18D4_A239_F20ED4B7B314__INCLUDED_)
