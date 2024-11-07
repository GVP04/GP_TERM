#if !defined(AFX_DLGMASK_H__32EB0805_2BF6_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_DLGMASK_H__32EB0805_2BF6_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgImageMask.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgImageMask dialog
class GPImageList;

class CDlgImageMask : public CDialog
{
// Construction
public:
	UINT ILStyle;
	void AddImg(CString flanme);
	void FillList();
	CDlgImageMask(const GPImageList * iList, const char *iFiles, CWnd* pParent = NULL);   // standard constructor
	GPImageList *IList;
	~CDlgImageMask();
// Dialog Data
	//{{AFX_DATA(CDlgImageMask)
	enum { IDD = IDD_DLGIMAGEMASK };
	CListCtrl	m_List2;
	CSpinButtonCtrl	m_SB;
	CSpinButtonCtrl	m_SG;
	CSpinButtonCtrl	m_SR;
	CListCtrl	m_List;
	UINT	m_EdG;
	UINT	m_EdB;
	UINT	m_EdR;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgImageMask)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	GP_AutoSizing AutoSizing;
	const char *Files;
	// Generated message map functions
	//{{AFX_MSG(CDlgImageMask)
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit3();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnIconlarge();
	afx_msg void OnIconlist();
	afx_msg void OnIconsmal();
	afx_msg void OnCancel();
	afx_msg void OnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMASK_H__32EB0805_2BF6_11D4_970E_0080AD863699__INCLUDED_)
