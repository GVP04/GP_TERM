#if !defined(AFX_DLGCONTEXTMENU_H__E83E341B_9AFC_4E52_B9FA_6C62FE3C0864__INCLUDED_)
#define AFX_DLGCONTEXTMENU_H__E83E341B_9AFC_4E52_B9FA_6C62FE3C0864__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgContextMenu.h : header file
//
#include "GPContextMenu.h"
#include "GPScintilla.h"	// Added by ClassView
/////////////////////////////////////////////////////////////////////////////
// CDlgContextMenu dialog


class CDlgContextMenu : public CDialog
{
// Construction
public:
	static CString m_GetWndText(HWND iHWND);
	static CString LastContextMenuFile;
	CDlgContextMenu(CWnd* pParent = NULL);   // standard constructor
	~CDlgContextMenu();

// Dialog Data
	//{{AFX_DATA(CDlgContextMenu)
	enum { IDD = IDD_DLGEDITCONTEXTMENU };
	CEdit	m_edName;
	CEdit	m_edClip;
	CEdit	m_edDescription;
	CEdit	m_edOutput;
	CEdit	m_edText;
	CEdit	m_edId;
	CTreeCtrl	m_Tree;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgContextMenu)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgContextMenu)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitemTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditId();
	afx_msg void OnChangeEditText();
	afx_msg void OnChangeEditOutput();
	afx_msg void OnChangeEditDescription();
	afx_msg void OnChangeEditClip();
	afx_msg void OnChangeEditName();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CToolBarCtrl m_ToolBar;
	GP_AutoSizing *DlgAutoSize;
	CGPContextMenu *m_Menu;
	GPMenu *m_GPMenu;

private:
	GPScintilla m_edOutputResult;
	DWORD m_dwUpdateFlag;
	UINT MenuFromTree(HTREEITEM iItem, HMENU iHMENU);
	void CopyChildren(HTREEITEM hDestParent, HTREEITEM hSrc);
	HTREEITEM CopyTree(HTREEITEM hDestParent, HTREEITEM hSrc, HTREEITEM insAfter);
	HTREEITEM MoveTree(HTREEITEM hDestParent, HTREEITEM hSrc, HTREEITEM insAfter);
	BOOL IsChildOf(HTREEITEM hItem1/*child*/, HTREEITEM hItem2/*parent*/);
	BOOL InitAndReload();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCONTEXTMENU_H__E83E341B_9AFC_4E52_B9FA_6C62FE3C0864__INCLUDED_)
