#if !defined(AFX_COMPORTSETINGS_H__C543C9A5_BA80_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_COMPORTSETINGS_H__C543C9A5_BA80_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComPortSetings.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComPortSetings dialog
#include "GP_comm.h"

class CComPortSetings : public CDialog
{
// Construction
public:
	BYTE GetbTTYItem(int idControl, char ** szString, DWORD * pTable, int iNumItems);
	DWORD GetdwTTYItem(int idControl, char ** szString, DWORD * pTable, int iNumItems);
	CComPortSetings(GP_comm *iGPc);   // standard constructor
	GP_comm *GPc;
// Dialog Data
	//{{AFX_DATA(CComPortSetings)
	enum { IDD = IDD_COM_SETINGS };
	CComboBox	m_ComboShutDown;
	CEdit	m_EditName;
	CComboBox	m_ComboType;
	CButton	m_CheckLockEcho;
	CEdit	m_LimXON;
	CEdit	m_CharXON;
	CEdit	m_LimXOFF;
	CEdit	m_CharXOFF;
	CEdit	m_CharEVENT;
	CEdit	m_CharERROR;
	CEdit	m_CharEOF;
	UINT	m_vEOF;
	UINT	m_vERROR;
	UINT	m_vEVENT;
	UINT	m_vXOFF;
	UINT	m_vLXOFF;
	UINT	m_vXON;
	UINT	m_LXON;
	UINT	m_PackSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComPortSetings)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CComPortSetings)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangePortcombo();
	afx_msg void OnSelchangeCombotermtype();
	afx_msg void OnButtondelimiters();
	afx_msg void OnChangeEditname();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPORTSETINGS_H__C543C9A5_BA80_11D2_B27D_00600840D054__INCLUDED_)
