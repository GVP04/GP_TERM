#if !defined(AFX_GP_CONTROL_H__A2860801_D5A5_11D4_AB17_004854899618__INCLUDED_)
#define AFX_GP_CONTROL_H__A2860801_D5A5_11D4_AB17_004854899618__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GP_Control.h : header file
//
#include "GP_HotKey.h"
#include "GPUnit.h"
#include "GPContainer.h"

/////////////////////////////////////////////////////////////////////////////
// GP_Control window

class GP_Control : public CWnd
{
	friend class GPUnit;
	friend class CGPContainer;
	friend LRESULT APIENTRY ActiveXSubclassProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam) ;
// Construction
public:
	GP_Control(UINT iUnitId);
	DWORD HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);
	CGPContainer *tmpWnd;

// Attributes
public:
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GP_Control)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	DWORD m_dwLastMessage;
	int AddChar(char iChar, DWORD iFlags);
	virtual ~GP_Control();
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
	UINT DoMethod(const char *iStr, char *oStr);
	UINT GPSetProperty(char *iStr);

	const static UINT uNTypes;
	const static char *cArrTypes[];
	const static UINT uArrTypes[];


	// Generated message map functions
protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	//{{AFX_MSG(GP_Control)
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	GPUnit **referGPU;
	UINT UnitId;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GP_CONTROL_H__A2860801_D5A5_11D4_AB17_004854899618__INCLUDED_)
