#if !defined(AFX_DLGVIEWINPUTSET_H__5C4DD3AF_187E_4D65_B020_382951E01710__INCLUDED_)
#define AFX_DLGVIEWINPUTSET_H__5C4DD3AF_187E_4D65_B020_382951E01710__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgViewInputSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgViewInputSet dialog
#include "DlgViewInput.h"

#define CDVIS_AUTOLOAD			0x00000001
#define CDVIS_AUTOSAVE			0x00000002
#define CDVIS_DIRECTINPUT		0x00000004
#define CDVIS_LINENUMBERS		0x00000008
#define CDVIS_VIEWWHITESPACE	0x00000010
#define CDVIS_VIEWEOL			0x00000020
#define CDVIS_LINEWRAPPING		0x00000040
#define CDVIS_COLORISELEX		0x00000080
#define CDVIS_LOCKKEYS			0x00000100
#define CDVIS_USETABS			0x00000200
#define CDVIS_LINEINDENTATION	0x00000400
#define CDVIS_INDENTATIONGUIDES	0x00000800
#define CDVIS_BAKSPACEUNINDENT	0x00001000


class CDlgViewInputSet : public CDialog
{
// Construction
public:
	DWORD m_dwTabSize;
	DWORD m_dwIndentSize;
	DWORD m_CurLexer;
	void UpdateInputSettings(UINT iType);
	void UpdateCtrls();
	void LoadKeys();
	void SaveKeys();
	UINT FontColorDlg(UINT iType);
	CDlgViewInputSet(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgViewInputSet();
	CDlgViewInput *m_DlgViewInputPtr;
	DWORD m_dwInputSet;
// Dialog Data
	//{{AFX_DATA(CDlgViewInputSet)
	enum { IDD = IDD_DLGVIEWINPUTSET };
	CComboBox	m_ComboIndentation;
	CComboBox	m_ComboTab;
	CComboBox	m_ComboLexer;
	CListCtrl	m_lcListViewSet;
	CComboBox	m_ComboBreak;
	CComboBox	m_ComboSoftBreak;
	CComboBox	m_ComboVK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgViewInputSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgViewInputSet)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnBtnfontcolor();
	afx_msg void OnSelchangeComboVK();
	afx_msg void OnCheckCtrl();
	afx_msg void OnCheckShift();
	afx_msg void OnCheckAlt();
	afx_msg void OnCheckCtrlSB();
	afx_msg void OnCheckShiftSB();
	afx_msg void OnCheckAltSB();
	afx_msg void OnSelchangeComboSB();
	afx_msg void OnSelchangeComboBreak();
	afx_msg void OnCheckBreakAlt();
	afx_msg void OnCheckBreakShift();
	afx_msg void OnCheckBreakCtrl();
	afx_msg void OnChangeEditsb();
	afx_msg void OnItemchangedListviewset(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonbrowse();
	afx_msg void OnChangeEditsrvfile();
	afx_msg void OnChangeEditsrvItem();
	afx_msg void OnChangeEditclfile();
	afx_msg void OnButtonkeywords();
	afx_msg void OnSelchangeCombolexer();
	afx_msg void OnButtonkeywords2();
	afx_msg void OnButtoneditkey();
	afx_msg void OnSelchangeComboindentation();
	afx_msg void OnSelchangeCombotab();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	GP_AutoSizing *DlgAutoSize;
	DWORD *m_dwKeyBreak;
	DWORD *m_dwKeySoftBreak;
	DWORD *m_dwKeyExecute;
	CString *m_csSoftBreakSeq;
	BOOL m_Lock;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIEWINPUTSET_H__5C4DD3AF_187E_4D65_B020_382951E01710__INCLUDED_)
