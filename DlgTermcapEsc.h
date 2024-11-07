#if !defined(AFX_DLGTERMCAPESC_H__B6ABB99E_5A19_4F31_B8E0_13F38BA6BCA6__INCLUDED_)
#define AFX_DLGTERMCAPESC_H__B6ABB99E_5A19_4F31_B8E0_13F38BA6BCA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTermcapEsc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTermcapEsc dialog
#include "TermCap.h"
#include "GPNotifyEdit.h"

class CDlgTermcapEsc : public CDialog
{
	friend class CDlgTermcap;
// Construction
public:
	void UpdateInfo();
	CDlgTermcapEsc(CWnd* pParent = NULL);   // standard constructor
	~CDlgTermcapEsc();

// Dialog Data
	//{{AFX_DATA(CDlgTermcapEsc)
	enum { IDD = IDD_DLGTERMCAP_ESC };
	CComboBox	m_ComboCopyTerm;
	CComboBox	m_ComboIdCommand;
	CGPNotifyEdit	m_Edit;
	CListCtrl	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTermcapEsc)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTermcapEsc)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonCopyEsc();
	afx_msg void OnClickListEsc(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickListEsc(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCloseupComboIdCommand();
	afx_msg void OnCloseupComboCopyEsc();
	afx_msg void OnButtonEditor();
	afx_msg void OnButtontest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	PTERMCAPESCITEM GetCurrentEsc(int & itm);
	UINT SetEscEditor(int Item, int SubItem, const char *txt);
	void UpdateListItem(int iItem, PTERMCAPESCITEM iItemData);
	DWORD m_SortFlag;
	DWORD m_dwUpdateFlag;
	CTermCap *m_pTermCap;
	GP_AutoSizing *DlgAutoSize;
	DWORD m_LastColumn;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTERMCAPESC_H__B6ABB99E_5A19_4F31_B8E0_13F38BA6BCA6__INCLUDED_)
