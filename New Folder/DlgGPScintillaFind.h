#if !defined(AFX_DLGGPSCINTILLAFIND_H__2150F14C_6CF5_4784_B078_91ACCFAB6F17__INCLUDED_)
#define AFX_DLGGPSCINTILLAFIND_H__2150F14C_6CF5_4784_B078_91ACCFAB6F17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGPScintillaFind.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGPScintillaFind dialog
class GPScintilla;

#define SCFINDTOOLBAR_NBTNS		10
#define SCFINDCMND_FINDNEXT			0x0010
#define SCFINDCMND_FINDPREV			0x0020
#define SCFINDCMND_REPLACE			0x0030
#define SCFINDCMND_REPLACEALL		0x0040
#define SCFINDCMND_HIDEMATCHED		0x0100
#define SCFINDCMND_HIDEUNMATCHED	0x0200
#define SCFINDCMND_SHOWALL			0x0300
#define SCFINDCMND_MARKMATHED		0x0400
#define SCFINDCMND_ONTOP			0x1000
#define SCFINDCMND_UNDO				0x2000
#define SCFINDCMND_REDO				0x3000

#define SCFIND_SELECTION 0x100
#define SCFIND_SELECTIONMASK 0xFFFFFFFF^0x100


class CDlgGPScintillaFind : public CDialog
{
// Construction
public:
	void UpdateComboReplace();
	void UpdateComboFind();
	void SetFindText(const char *iText);
	int m_LastSelEnd;
	int m_LastSelStart;
	const CString GetReplaceText();
	const CString GetSearchText();
	DWORD GetSearchFlags();
	void UpdateCombos();
	CString m_csReplaceStrings;
	CString m_csFindStrings;
	UINT AddRef(GPScintilla * iRef);
	UINT DelRef(GPScintilla * iRef);
	UINT SetCurrentEditor(GPScintilla * iRef);
	CDlgGPScintillaFind(CWnd* pParent = NULL);   // standard constructor
	~CDlgGPScintillaFind();   // standard destructor
	DWORD SetSearchFlags(DWORD dwFlg);
	void SetReplaceText(const char *iText);
	void DoReplaceAll();

// Dialog Data
	//{{AFX_DATA(CDlgGPScintillaFind)
	enum { IDD = IDD_DLGSCFIND };
	CButton	m_BtnEx;
	CButton	m_CheckSelection;
	CComboBox	m_ComboReplace;
	CComboBox	m_ComboFind;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGPScintillaFind)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGPScintillaFind)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnButtonex();
	afx_msg void OnEditchangeCombofind();
	afx_msg void OnEditchangeComboreplace();
	afx_msg void OnCheckselection();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	GP_RarefiedArr<GPScintilla *> EditorsArray;
	CToolBarCtrl m_ToolBar;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGPSCINTILLAFIND_H__2150F14C_6CF5_4784_B078_91ACCFAB6F17__INCLUDED_)
