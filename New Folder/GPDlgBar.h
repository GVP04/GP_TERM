#if !defined(AFX_GPDLGBAR_H__6204B301_B9B8_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GPDLGBAR_H__6204B301_B9B8_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPDlgBar.h : header file
//

#include "GP_HotKey.h"
#include "GPUnit.h"
#include "GPScroller.h"

/////////////////////////////////////////////////////////////////////////////
// GPDlgBar dialog

class GPDlgBar : public CDialog
{
	friend class GPUnit;

// Construction
public:
	HGLOBAL  a_GPObjDialogHG;
	DWORD HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);
	GPDlgBar(UINT iUnitId, const char *iiStr);   // standard constructor
	virtual ~GPDlgBar();
	BOOL CreateDlgBar(UINT iStyleEx, const char *Capt,UINT iStyle,CRect ir,CWnd *ParentCWnd,UINT iUnitId, const char *iInitStr, UINT iScale);

// Dialog Data
	//{{AFX_DATA(GPDlgBar)
	enum { IDD = IDR_MAINFRAME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPDlgBar)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Attributes
public:
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
	GP_AutoSizing *DlgAutoSize;
	CGPScroller * GetScroller(const char *iStr, HWND iScrHwnd);
	UINT DeleteScroller(const char *iStr);

// Implementation
public:
	void UpdateScrollers();
	UINT DoMethod(const char *iStr, char *oStr);
	UINT GPSetProperty(char *iStr);

protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	// Generated message map functions
	//{{AFX_MSG(GPDlgBar)
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bAutoFocus;
	char *initialStr;
	DWORD m_dwFlashFlag;
	CGPScroller **ScrollerArr;
	UINT nScroller;
	UINT nMaxScroller;
	int *iRepositionArray;
	UINT nUnitENTIRE;
	GPUnit **referGPU;
	char *CharSpec;
	UINT FloatPoint;
	UINT UnitId;
protected:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPDLGBAR_H__6204B301_B9B8_11D2_B27D_00600840D054__INCLUDED_)
