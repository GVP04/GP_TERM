#if !defined(AFX_VDLGSEPARATEVIEWINFRAME_H__9CEBE3AE_BA55_4AC8_A243_7C5B71ED128F__INCLUDED_)
#define AFX_VDLGSEPARATEVIEWINFRAME_H__9CEBE3AE_BA55_4AC8_A243_7C5B71ED128F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSeparateViewInFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSeparateViewInFrame dialog
class CDlgViewInputAll;
class CDlgViewOutput;

class CDlgSeparateViewInFrame : public CDialog
{
// Construction
public:
	CDlgSeparateViewInFrame(CWnd* pParent = NULL);   // standard constructor
	CDlgViewInputAll *m_DlgViewInputAll;
	CDlgViewOutput *m_DlgViewOutput;
	void FrameSizeMove();
	CRect m_FrameLastSize;
	void ResizeDialogs(CSize &sz);

// Dialog Data
	//{{AFX_DATA(CDlgSeparateViewInFrame)
	enum { IDD = IDD_DLGVIEWINFRAME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSeparateViewInFrame)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSeparateViewInFrame)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VDLGSEPARATEVIEWINFRAME_H__9CEBE3AE_BA55_4AC8_A243_7C5B71ED128F__INCLUDED_)
