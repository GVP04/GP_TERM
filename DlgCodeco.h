#if !defined(AFX_DLGCODECO_H__66D20D58_1A39_4FD8_9EB0_748B2E6A0917__INCLUDED_)
#define AFX_DLGCODECO_H__66D20D58_1A39_4FD8_9EB0_748B2E6A0917__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCodeco.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCodeco dialog

class CDlgCodeco : public CDialog
{
// Construction
public:
	static const DWORD nLang;
	static const DWORD nSubLang;
	static const WORD wArrLang[];
	static const WORD wArrSubLang[];
	static const char *cArrLangName[];
	static const char *cArrSubLangName[];

	static const char * CodecoFileName;
	static void FillDefaultDosAnsiArrays(char * iAnsiDos, char *iDosAnsi, char *iWideAnsiDos, char *iWideDosAnsi, char *iWideAnsiDos2, char *iWideDosAnsi2);
	static BOOL LoadDosAnsiArrays(char * iAnsiDos, char *iDosAnsi, char *iWideAnsiDos, char *iWideDosAnsi, char *iWideAnsiDos2, char *iWideDosAnsi2);
	static BOOL SaveDosAnsiArrays(char * iAnsiDos, char *iDosAnsi, char *iWideAnsiDos, char *iWideDosAnsi, char *iWideAnsiDos2, char *iWideDosAnsi2);
	CDlgCodeco(CWnd* pParent = NULL);   // standard constructor
	~CDlgCodeco();   // standard destructor

// Dialog Data
	//{{AFX_DATA(CDlgCodeco)
	enum { IDD = IDD_DLGCODECO };
	CComboBox	m_Combo3SrvPC;
	CComboBox	m_Combo3PCSrv;
	CListCtrl	m_CodeListWideToServer2;
	CListCtrl	m_CodeListWideToPC2;
	CComboBox	m_ComboWideToServer2;
	CComboBox	m_ComboWideToPC2;
	CListCtrl	m_CodeListWideToServer;
	CComboBox	m_ComboWideToServer;
	CTabCtrl	m_tab;
	CComboBox	m_ComboToPC;
	CComboBox	m_ComboToServer;
	CComboBox	m_ComboWideToPC;
	CListCtrl	m_CodeListToPC;
	CListCtrl	m_CodeListToServer;
	CListCtrl	m_CodeListWideToPC;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCodeco)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCodeco)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnBtndef();
	afx_msg void OnBtnload();
	afx_msg void OnBtnsave();
	afx_msg void OnCancel();
	afx_msg void OnOk();
	afx_msg void OnBtncurrent();
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCloseupCombo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void OnBtncurrent(int CurSel);
	void FillList(DWORD iType);
	char m_chAnsiDos[256];
	char m_chDosAnsi[256];
	char m_chWideAnsiDos[256];
	char m_chWideDosAnsi[256];
	char m_chWideAnsiDos2[256];
	char m_chWideDosAnsi2[256];
	GP_AutoSizing *DlgAutoSize;
	CListCtrl *mlists[6];
	CComboBox *mcompos[6];
	char *m_ConvArr[6];
	UINT nLists;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCODECO_H__66D20D58_1A39_4FD8_9EB0_748B2E6A0917__INCLUDED_)
