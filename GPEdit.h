#if !defined(AFX_GPEDIT_H__906CF2C1_B9B8_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GPEDIT_H__906CF2C1_B9B8_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPEdit.h : header file
//
#include "GP_HotKey.h"
#include "GPUnit.h"

/////////////////////////////////////////////////////////////////////////////
// GPEdit window

class GPEdit : public CEdit
{
	friend class GPUnit;

// Construction
public:
	GPEdit(UINT iUnitId);

// Attributes
public:
	DWORD HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);
	const static char *cNoeditChars;
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
////////////	BOOL m_bInsertMode;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetDefSel();
	DWORD m_dwTextMode;
	DWORD GetTextLength();
	DWORD m_AddOnlyFlag;
	DWORD GetCRC16forText();
	DWORD m_AlwaysOnchange;
	DWORD m_LastChangedCRC;
	DWORD m_DOflags;
	int AddChar(char iChar, DWORD iFlags);
	BOOL SetreferGPU(GPUnit **iGPU);
	long PrevMaskPosition(int & iPosition);
	long NextMaskPosition(int & iPosition);
	void ClearMaskText();
	virtual ~GPEdit();
	UINT DoMethod(const char *iStr, char *oStr);
	UINT GPSetProperty(const char *iStr);

	// Generated message map functions
protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	//{{AFX_MSG(GPEdit)
	afx_msg void OnHscroll();
	afx_msg void OnChange();
	afx_msg void OnErrspace();
	afx_msg void OnMaxtext();
	afx_msg void OnNotifySetfocus();
	afx_msg void OnUpdate();
	afx_msg void OnALIGN_LTR_EC();
	afx_msg void OnALIGN_RTL_EC();
	afx_msg void OnVscroll();
	afx_msg void ParentNotify(UINT message, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnNotifyKillfocus();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bAutoFocus;
	UINT MaskFlag;
	UINT m_EnableContextMenu;
	UINT AutoWidthMin,AutoWidthMax,AutoWidthDelta;
	UINT m_uCurVP;
	void OnChangeVP();
	GPUnit **referGPU;
	char *CharSpec;
	char *MaskSpec;
	int FloatPoint;
	UINT UnitId;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPEDIT_H__906CF2C1_B9B8_11D2_B27D_00600840D054__INCLUDED_)
