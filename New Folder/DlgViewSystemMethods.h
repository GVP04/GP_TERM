#if !defined(AFX_DLGVIEWSYSTEMMETHODS_H__E4F6F7B0_CE12_4C9E_81BB_C8ACDB073BD6__INCLUDED_)
#define AFX_DLGVIEWSYSTEMMETHODS_H__E4F6F7B0_CE12_4C9E_81BB_C8ACDB073BD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgViewSystemMethods.h : header file
//
#include "Winspool.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgViewSystemMethods dialog

class CDlgViewSystemMethods : public CDialog
{
// Construction
public:
	static void StringFromToPORT_INFO_3(const char *iOption, char *oOption, PORT_INFO_3 & iPORT_INFO_3);
	static DWORD StringFromToAddrFlags(const char *iOption, DWORD & convOption);
	static DWORD StringFromToAddrFamily(const char *iOption, DWORD & convOption);
	static DWORD StringFromToAddrTypes(const char *iOption, unsigned short & convOption);
	static DWORD StringToIPAddr(const char *iIPAddr);
	static DWORD StringFromToProtocolId(const char *iOption, DWORD & convOption);
	static char *IPAddrToString(DWORD iIPAddr);
	CDlgViewSystemMethods(CWnd* pParent = NULL);   // standard constructor

	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];

	const static char *chColorNames[];
	static DWORD uColorNames[];

	const static char *chMetricsNames[];
	static DWORD uMetricsNames[];



	static int DoMethod(const char *iStrMethod, char *oStr);

// Dialog Data
	//{{AFX_DATA(CDlgViewSystemMethods)
	enum { IDD = IDD_DIALOGVIEWSYSTEMMETH };
	CComboBox	m_ComboMethods;
	CButton	m_btnExecute;
	CEdit	m_EditParams;
	CEdit	m_EditResult;
	CStatic	m_StatParams;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgViewSystemMethods)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgViewSystemMethods)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBtnexecute();
	afx_msg void OnSelchangeCombomethods();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	GP_AutoSizing AUSI;
	static char tmpRetStr[];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIEWSYSTEMMETHODS_H__E4F6F7B0_CE12_4C9E_81BB_C8ACDB073BD6__INCLUDED_)
