#if !defined(AFX_GPOBJDIALOG_H__CEEB3561_B9B8_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GPOBJDIALOG_H__CEEB3561_B9B8_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPObjDialog.h : header file
//

#include "GPUnit.h"
#include "GPScroller.h"

//#define ID_DELAY_TIMER_ID	991
//#define ID_DELAY_TIMER_DELAY	2000 // DEFINE in "GPUnit.h"

/////////////////////////////////////////////////////////////////////////////
// GPObjDialog dialog
class CGPToolTipCtrl;
class CDlgDialogEditor;

class GPObjDialog : public CDialog
{
friend class CDlgViewSystemMethods;
friend class CDlgDialogEditor;
friend class GPDlgViewMPVar;
friend class CGP_TermView;
friend class CGP_TermDoc;
friend class GPUnit;
friend class CODContextArray;
// Construction
public:
	DWORD GetObjIdByHWND(HWND iHWND);
	void RunEditor();
	BOOL AttachHWND(HWND iHWND);
	DWORD HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];

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
	GPObjDialog(UINT iId,const char *iiStr, CWnd* pParent = NULL);   // standard constructor
	~GPObjDialog();
	char *initialStr;
	CGPScroller * GetScroller(const char *iStr, HWND iScrHwnd);
	UINT DeleteScroller(const char *iStr);
	void UpdateScrollers();

// Dialog Data

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPObjDialog)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	// Generated message map functions
	//{{AFX_MSG(GPObjDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pNewWnd);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CGPScroller **ScrollerArr;
	UINT nScroller;
	UINT nMaxScroller;
	int *iRepositionArray;
	UINT nUnitENTIRE;
	GP_AutoSizing *DlgAutoSize;
	void ClearDialog();
	CGPToolTipCtrl *m_ToolTip;
	GPUnit **GPU;
	UINT IdDlg;
	UINT m_NGPUNITmax;
protected:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPOBJDIALOG_H__CEEB3561_B9B8_11D2_B27D_00600840D054__INCLUDED_)
