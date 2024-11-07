#if !defined(AFX_DLGVIEWOUTPUTSET_H__8CE4F0AF_25E4_4CDF_991E_6E0148F84E7D__INCLUDED_)
#define AFX_DLGVIEWOUTPUTSET_H__8CE4F0AF_25E4_4CDF_991E_6E0148F84E7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgViewOutputSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgViewOutputSet dialog
#define CDVOS_ENABLEOUTPUT		0x00000001
#define CDVOS_NOREADONLYOUTPUT	0x00000002
#define CDVOS_AUTOSCROLL		0x00000004
#define CDVOS_LINENUMBERS		0x00000008
#define CDVOS_VIEWWHITESPACE	0x00000010
#define CDVOS_VIEWEOL			0x00000020
#define CDVOS_LINEWRAPPING		0x00000040
#define CDVOS_COLORISELEX		0x00000080
#define CDVOS_AUTOLOADSAVE		0x00000100
#define CDVOS_DIRECTINPUT		0x00000200
#define CDVOS_LOCKKEYS			0x00000400
#define CDVOS_DUPLICATEINPUT	0x00000800
#define CDVOS_USETABS			0x00001000
#define CDVOS_LINEINDENTATION	0x00002000
#define CDVOS_INDENTATIONGUIDES	0x00004000
#define CDVOS_BAKSPACEUNINDENT	0x00008000

#include "DlgViewOutput.h"

class CDlgViewOutputSet : public CDialog
{
// Construction
public:
	DWORD m_dwTabSize;
	DWORD m_dwIndentSize;
	DWORD m_CurLexer;
	void UpdateOutputSettings(UINT iType);
	UINT FontColorDlg(UINT iType);
	void SetMinMaxLen(UINT & uMax, UINT & uPercent);
	UINT *m_nMaxOutputLen;
	UINT *m_nOutputLenDecr;
	void UpdateCtrls();
	DWORD SetCharMask(DWORD idwMask);
	DWORD GetCharMask();
	DWORD m_dwLowSymbolMask;
	DWORD m_dwOutputSet;
	CDlgViewOutputSet(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgViewOutputSet();
	CDlgViewOutput *m_DlgViewOutputPtr;

// Dialog Data
	//{{AFX_DATA(CDlgViewOutputSet)
	enum { IDD = IDD_DLGVIEWOUTPUTSET };
	CComboBox	m_ComboIndentation;
	CComboBox	m_ComboTab;
	CComboBox	m_ComboLexer;
	CEdit	m_EditLenMax;
	CEdit	m_EditLenPercent;
	CListCtrl	m_lcListViewSet;
	CListCtrl	m_lcListSymbol;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgViewOutputSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgViewOutputSet)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnItemchangedListsymbol(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListviewset(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditmaxlen();
	afx_msg void OnChangeEditmaxlen2();
	afx_msg void OnBtnfontcolor();
	afx_msg void OnButtonkeywords();
	afx_msg void OnSelchangeCombolexer();
	afx_msg void OnButtonbrowse();
	afx_msg void OnChangeEditsrvfile();
	afx_msg void OnChangeEditsrvItem();
	afx_msg void OnChangeEditclfile();
	afx_msg void OnButtoneditkey();
	afx_msg void OnSelchangeCombotab();
	afx_msg void OnSelchangeComboindentation();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_Lock;
	GP_AutoSizing *DlgAutoSize;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIEWOUTPUTSET_H__8CE4F0AF_25E4_4CDF_991E_6E0148F84E7D__INCLUDED_)
