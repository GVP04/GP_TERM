#if !defined(AFX_GPFRAMEBAR_H__1D23DAC1_5003_11D4_A239_B92492AC2552__INCLUDED_)
#define AFX_GPFRAMEBAR_H__1D23DAC1_5003_11D4_A239_B92492AC2552__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPFrameBar.h : header file
//
#include "GP_HotKey.h"
#include "GPUnit.h"
#include "GPScroller.h"

/////////////////////////////////////////////////////////////////////////////
// GPFrameBar frame

class GPFrameBar : public CFrameWnd
{
friend class GPUnit;

	DECLARE_DYNCREATE(GPFrameBar)
protected:
	GPFrameBar();           // protected constructor used by dynamic creation



// Attributes
public:
	DWORD HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
	BOOL CreateFrameBar(UINT iStyleEx, const char *Capt,UINT iStyle,CRect ir,CWnd *ParentCWnd,UINT iUnitId);
	GP_AutoSizing *DlgAutoSize;
// Implementation
public:
	UINT DoMethod(const char *iStr, char *oStr);
	UINT GPSetProperty(char *iStr);

	CGPScroller * GetScroller(const char *iStr, HWND iScrHwnd);
	UINT DeleteScroller(const char *iStr);
	void UpdateScrollers();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPFrameBar)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~GPFrameBar();
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	// Generated message map functions
	//{{AFX_MSG(GPFrameBar)
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bAutoFocus;
	CGPScroller **ScrollerArr;
	UINT nScroller;
	UINT nMaxScroller;
	UINT nUnitENTIRE;
	GPUnit **referGPU;
	char *CharSpec;
	UINT FloatPoint;
	UINT UnitId;
	DWORD m_dwFlashFlag;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPFRAMEBAR_H__1D23DAC1_5003_11D4_A239_B92492AC2552__INCLUDED_)
