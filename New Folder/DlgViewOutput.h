#if !defined(AFX_DLGVIEWOUTPUT_H__F90C0F4E_3331_4E7C_AB9A_9626595CEB50__INCLUDED_)
#define AFX_DLGVIEWOUTPUT_H__F90C0F4E_3331_4E7C_AB9A_9626595CEB50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgViewOutput.h : header file
//
#include "GPViewOutput.h"
#include "GPInputPool.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgViewOutput dialog

#define OVTOOLBAR_NBTNS				23

class CDlgViewOutputSet;

class CDlgViewOutput : public CDialog
{
friend class CDlgSeparateView;
friend class CDlgViewOutputSet;
// Construction
public:
	void CloseFindDialog();
	CDlgViewOutputSet * m_CDlgViewOutputSetPtr;
	void UpdateTB();
	UINT m_nOutputLenDecr;
	UINT m_RedirectInput;
	char *AppendStringToOutput(const char *iStr);
	int AppendCharToOutput(char iCh, DWORD dwDelayFlag);
	void SetSize(CSize & csValidSize);
	CDlgViewOutput(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgViewOutput();

// Dialog Data
	//{{AFX_DATA(CDlgViewOutput)
	enum { IDD = IDD_DLGVIEWOUTPUT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgViewOutput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgViewOutput)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	UINT m_nMaxOutputLen;
	UINT m_LastTransfer;
	UINT m_Delay1;
	UINT m_Delay2;
	UINT m_InDataFlag;
	GP_AutoSizing *DlgAutoSize;
	CToolBarCtrl m_ToolBar;
	CSize m_csLastParentSize;
	GPViewOutput *m_Editor;
	UINT m_uSelectionFlag;
	CGPInputPool m_Pool;
	CRITICAL_SECTION m_CSOutputView;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIEWOUTPUT_H__F90C0F4E_3331_4E7C_AB9A_9626595CEB50__INCLUDED_)
