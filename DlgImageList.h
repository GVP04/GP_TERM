#if !defined(AFX_DLGIMAGELIST_H__3A12D1FE_0573_4F66_8584_290FB8B31ED5__INCLUDED_)
#define AFX_DLGIMAGELIST_H__3A12D1FE_0573_4F66_8584_290FB8B31ED5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgImageList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgImageList dialog

class CDlgImageList : public CDialog
{
// Construction
public:
	void ResetILList();
	CDlgImageList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgImageList)
	enum { IDD = IDD_DLGVIEWIMAGELISTS };
	CEdit	m_EditResult;
	CButton	m_BtnAdd;
	CButton	m_btnDelete;
	CButton	m_btnExecute;
	CStatic	m_StatParams;
	CComboBox	m_ComboImageLists;
	CEdit	m_EditParams;
	CComboBox	m_ComboMethods;
	CListCtrl	m_IList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgImageList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgImageList)
	afx_msg void OnBtnadd();
	afx_msg void OnBtndelete();
	afx_msg void OnBtnexecute();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeComboimagelists();
	afx_msg void OnSelchangeCombomethods();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	static CString m_csLastDirSave;
	static CString m_csLastDirLoad;
	static CString m_csLastDirAdd;
	void ReSetImageList();
	GPImageList * m_CurImageList;
	void FillIListList();
	GP_AutoSizing AUSI;
	CToolBarCtrl m_ToolBar;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIMAGELIST_H__3A12D1FE_0573_4F66_8584_290FB8B31ED5__INCLUDED_)
