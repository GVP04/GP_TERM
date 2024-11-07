#if !defined(AFX_DLGKEYEDITOR_H__125C2087_5660_4E7D_994F_D13423315BD0__INCLUDED_)
#define AFX_DLGKEYEDITOR_H__125C2087_5660_4E7D_994F_D13423315BD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgKeyEditor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgKeyEditor dialog

class CDlgKeyEditor : public CDialog
{
// Construction
public:
	CString m_FileName;
	void UpdateListItem(int iItem,DWORD iKey);
	CDlgKeyEditor(CWnd* pParent = NULL);   // standard constructor
	~CDlgKeyEditor();
// Dialog Data
	//{{AFX_DATA(CDlgKeyEditor)
	enum { IDD = IDD_DLGKEYEDITOR };
	CComboBox	m_ComboKey;
	CListCtrl	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgKeyEditor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgKeyEditor)
	afx_msg void OnButtonOk();
	afx_msg void OnButtonCancel();
	afx_msg void OnButtondel();
	afx_msg void OnButtonadd();
	afx_msg void OnCloseupComboKey();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnClickListKeys(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickListKey(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	DWORD m_SortFlag;
	GP_AutoSizing *DlgAutoSize;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGKEYEDITOR_H__125C2087_5660_4E7D_994F_D13423315BD0__INCLUDED_)
