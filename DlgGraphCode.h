#if !defined(AFX_DLGGRAPHCODE_H__55D27AB9_6CBD_4456_B135_00DC8F8BF976__INCLUDED_)
#define AFX_DLGGRAPHCODE_H__55D27AB9_6CBD_4456_B135_00DC8F8BF976__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGraphCode.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CDlgGraphCode dialog

class CDlgGraphCode : public CDialog
{
// Construction
public:
	void SetUnicodeCharCode(unsigned short usCode);
	CFont m_FontCpy;
	CDlgGraphCode(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGraphCode)
	enum { IDD = IDD_DIALOGGRAPHCODE };
	CListCtrl	m_ListCurrent;
	CProgressCtrl	m_Progress;
	CListCtrl	m_ListSample;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGraphCode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementation
protected:
	GP_AutoSizing AUSI;
	// Generated message map functions
	//{{AFX_MSG(CDlgGraphCode)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListChars(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDblclkListCurrent(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnInvisibleStop();
	afx_msg void OnVisibleStop();
	afx_msg void OnInvisible();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGRAPHCODE_H__55D27AB9_6CBD_4456_B135_00DC8F8BF976__INCLUDED_)
