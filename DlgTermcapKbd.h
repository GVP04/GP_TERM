#if !defined(AFX_DLGTERMCAPKBD_H__E99F30DF_60FE_4EA1_B58A_AD2E5BBDE3F6__INCLUDED_)
#define AFX_DLGTERMCAPKBD_H__E99F30DF_60FE_4EA1_B58A_AD2E5BBDE3F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTermcapKbd.h : header file
//
#include "TermCap.h"
#include "GPNotifyEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTermcapKbd dialog

class CDlgTermcapKbd : public CDialog
{
	friend class CDlgTermcap;
// Construction
public:
	UINT SetSeqEditor(int Item, int SubItem, const char *txt);
	void UpdateInfo();
	CDlgTermcapKbd(CWnd* pParent = NULL);   // standard constructor
	~CDlgTermcapKbd();

// Dialog Data
	//{{AFX_DATA(CDlgTermcapKbd)
	enum { IDD = IDD_DLGTERMCAP_KBD };
	CComboBox	m_ComboAction;
	CComboBox	m_ComboCopyTerm;
	CGPNotifyEdit	m_EditSeq;
	CComboBox	m_ComboKey;
	CListCtrl	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTermcapKbd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTermcapKbd)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCloseupComboKey();
	afx_msg void OnClickListKeys(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickListKey(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDelete();
	afx_msg void OnCloseupComboCopyKbd();
	afx_msg void OnButtonCopyKbd();
	afx_msg void OnCloseupComboaction();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	UINT m_LastColumn;
	PTERMCAPKBDITEM GetCurrentKbd(int & itm);
	DWORD m_SortFlag;
	void UpdateListItem(int iItem, PTERMCAPKBDITEM iItemData);
	DWORD m_dwUpdateFlag;
	CTermCap *m_pTermCap;
	GP_AutoSizing *DlgAutoSize;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTERMCAPKBD_H__E99F30DF_60FE_4EA1_B58A_AD2E5BBDE3F6__INCLUDED_)
