#if !defined(AFX_GPPROGRESS_H__906CF2C6_B9B8_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GPPROGRESS_H__906CF2C6_B9B8_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPProgress.h : header file
//
#include "GP_HotKey.h"
#include "GPUnit.h"

/////////////////////////////////////////////////////////////////////////////
// GPProgress window

class GPProgress : public CProgressCtrl
{
	friend class GPUnit;

// Construction
public:
	GPProgress(UINT iUnitId);

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
	//{{AFX_VIRTUAL(GPProgress)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString m_csDOString;
	int AddChar(char iChar, DWORD iFlags);
	virtual ~GPProgress();
	UINT DoMethod(const char *iStr, char *oStr);
	UINT GPSetProperty(char *iStr);

	// Generated message map functions
protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	//{{AFX_MSG(GPProgress)
	afx_msg void OnOutofmemory(NMHDR* pNMHDR, LRESULT* pResult);
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
	int m_LastHiPos;
	GPUnit **referGPU;
	UINT UnitId;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPPROGRESS_H__906CF2C6_B9B8_11D2_B27D_00600840D054__INCLUDED_)
