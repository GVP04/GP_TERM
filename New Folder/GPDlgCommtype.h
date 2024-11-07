#if !defined(AFX_GPDLGCOMMTYPE_H__EF9C45E1_FE84_11D2_87EF_C06F2265B066__INCLUDED_)
#define AFX_GPDLGCOMMTYPE_H__EF9C45E1_FE84_11D2_87EF_C06F2265B066__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPDlgCommtype.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GPDlgCommtype dialog
#include "ComPortSetings.h"
#include "GPDlgTelnetSet.h"
#include "GP_AutoSizing.h"	// Added by ClassView

class GPDlgCommtype : public CDialog
{
// Construction
private:
	GP_AutoSizing AUSI;

public:
	CString csOldFileName;
	static BOOL ChechAndDelete(const char *CommKeName);
	int DefineDefaultItem();
	CString cs_m_DefConnectionName;
	int FillConnectionsList(const char *ccSelection);
	int UpdateListItem(int iItem);
	void EnableUIObjects(BOOL m_bEnabled);
	int UpdateListItem(const char *iName);
	int AddListItem(const char *iName);
	GPDlgCommtype(CWnd* pParent =NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(GPDlgCommtype)
	enum { IDD = IDD_DIALOGCOMMTYPE };
	CListCtrl	m_ListConnections;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPDlgCommtype)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GPDlgCommtype)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeleteallitemsList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitemList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtondelete();
	afx_msg void OnButtondefault();
	afx_msg void OnButtontest();
	virtual void OnOK();
	afx_msg void OnButtonaddcom();
	afx_msg void OnButtonaddsocket();
	afx_msg void OnButtonaddcopy();
	afx_msg void OnButtonimport();
	afx_msg void OnButtonexport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPDLGCOMMTYPE_H__EF9C45E1_FE84_11D2_87EF_C06F2265B066__INCLUDED_)
