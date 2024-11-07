#if !defined(AFX_DLGVIEWINPUTALL_H__BC066151_09E4_41B6_B4E0_5F20FAA81111__INCLUDED_)
#define AFX_DLGVIEWINPUTALL_H__BC066151_09E4_41B6_B4E0_5F20FAA81111__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgViewInputAll.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgViewInputAll dialog
#include "DlgViewInput.h"
#include "DlgViewInputSet.h"
#include "DlgViewOutputSet.h"
#include "DlgViewOutput.h"

class GPDlgBar;



class CDlgViewInputAll : public CDialog
{
	friend class CDlgSeparateView;
	friend class GPCurrent;
// Construction
public:
	void UpdateIVSize(int iHeighht);
	void SwitchIVSize(DWORD cmd);
	void SetSize(CSize &csValidSize);
	void UpdateTabs();
	CDlgViewInputAll(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgViewInputAll();

// Dialog Data
	//{{AFX_DATA(CDlgViewInputAll)
	enum { IDD = IDD_DLGVIEWINPUTALL };
	CTabCtrl	m_Tab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgViewInputAll)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgViewInputAll)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_LastIVSize;
	BOOL m_SizeNow;
	HCURSOR m_SizeCursor;
	GP_AutoSizing *DlgAutoSize;
	CSize m_csLastParentSize;
	int m_Height;
	CDlgViewInput m_DlgViewInput;
	CDlgViewInputSet m_DlgViewInputSet;
	CDlgViewOutputSet m_DlgViewOutputSet;
	GPDlgBar *m_BarOutputSet;
	GPDlgBar *m_BarInputSet;
	CDlgViewOutput *m_DlgViewOutputPtr;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIEWINPUTALL_H__BC066151_09E4_41B6_B4E0_5F20FAA81111__INCLUDED_)
