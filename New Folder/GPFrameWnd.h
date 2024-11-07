#if !defined(AFX_GPFRAMEWND_H__0428D486_4F36_11D4_A239_AD1C73BEB556__INCLUDED_)
#define AFX_GPFRAMEWND_H__0428D486_4F36_11D4_A239_AD1C73BEB556__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPFrameWnd.h : header file
//

#include "GPUnit.h"
#include "GPScroller.h"

class CGPToolTipCtrl;
class CDlgDialogEditor;
/////////////////////////////////////////////////////////////////////////////
// GPFrameWnd frame

class GPFrameWnd : public CFrameWnd
{
friend class CDlgViewSystemMethods;
friend class CDlgDialogEditor;
friend class CGP_TermView;
friend class GPDlgViewMPVar;
friend class CGP_TermDoc;
friend class GPUnit;
friend class CODContextArray;

	DECLARE_DYNCREATE(GPFrameWnd)

protected:
	GPFrameWnd();           // protected constructor used by dynamic creation

// Construction
public:
	void RunEditor();
	CGPScroller * GetScroller(const char *iStr, HWND iScrHwnd);
	UINT DeleteScroller(const char *iStr);
	void UpdateScrollers();
	DWORD HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
	BOOL GPCreate(UINT iId, const char *iiStr, CWnd* pParent );
	CDlgDialogEditor *m_CDlgDialogEditor;
	BOOL AskExit();
	GPUnit * GetUnit(UINT iUnitId);
	void DelAllHotkey();
	BOOL DelHotkey(UINT iId, const char *iHotkeyName);
	BOOL AddHotkey(char *nm_VK, UINT iId, const char *seq);
	BOOL DeleteDlgMenu();
	GPMenu *CreateDlgMenu();
	CMenu *DlgMenu;
	GPMenu *DlgGPMenu;
	void GPDeleteAllMessage();
	void GPDeleteMessage(char *mes);
	void GPAddMessage(char *mes);
	GPUnit *GetUnitById(UINT Id);
	void DoDlgMethod(const char *iStr, char *oStr);
	void GPEndDlg();
	void DoMethod(UINT iId, const char *iStr,char *oStr);
	UINT CreateUnit(UINT iType, UINT iId, const char *iInit, HWND pParentWnd);
	void DeleteUnit(UINT iId, BOOL bReport);
	char *iStr;
	DWORD GetObjIdByHWND(HWND iHWND);
// Implementation
private:
	CGPScroller **ScrollerArr;
	UINT nScroller;
	UINT nMaxScroller;
	UINT nUnitENTIRE;
	GP_AutoSizing *DlgAutoSize;
	void ClearDialog();
	CGPToolTipCtrl *m_ToolTip;
	GPUnit **GPU;
	UINT IdDlg;
	UINT m_NGPUNITmax;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPFrameWnd)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	virtual BOOL DestroyWindow();
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();

// Implementation
public:
	virtual ~GPFrameWnd();

	// Generated message map functions
	//{{AFX_MSG(GPFrameWnd)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPFRAMEWND_H__0428D486_4F36_11D4_A239_AD1C73BEB556__INCLUDED_)
