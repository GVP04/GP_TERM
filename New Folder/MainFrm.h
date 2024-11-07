// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__1509E7B0_DD4C_11D3_970D_0080AD863699__INCLUDED_)
#define AFX_MAINFRM_H__1509E7B0_DD4C_11D3_970D_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GPStatusBar.h"
class GPToolBar;
class GPReBar;
class GPDialogBar;

#define BRIZICON_TIMER_ID	  10014
#define BRIZICON_TIMER_IDHIDE	  10015


class CMainFrame : public CFrameWnd
{

	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void CheckAndUpdateBars(DWORD dwFlags = 0);
	void UpdateAndRecalc();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	GPStatusBar m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CToolBar    m_wndDevToolBar;
	CReBar      m_wndReBar;
	CDialogBar  m_wndDlgBar;
	CImageList	m_ilToolBar;
	CImageList	m_ilDevToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg BOOL OnQueryEndSession();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnViewStatusBar();
	afx_msg void OnViewToolbar();
	afx_msg void OnUpdateTranslateTcl(CCmdUI* pCmdUI);
	afx_msg void OnUpdateKeyblock(CCmdUI* pCmdUI);
	afx_msg void OnEnterIdle(UINT nWhy, CWnd* pWho);
	afx_msg void OnViewDevtoolbar();
	afx_msg void OnUpdateViewDevtoolbar(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewToolbar(CCmdUI* pCmdUI);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnFullcontextmenu();
	afx_msg void OnStatistic();
	afx_msg void OnUpdateStatistic(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__1509E7B0_DD4C_11D3_970D_0080AD863699__INCLUDED_)
