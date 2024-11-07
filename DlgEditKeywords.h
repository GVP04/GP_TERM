#if !defined(AFX_DLGEDITKEYWORDS_H__9BA5DBF0_1B58_4BFB_85F1_8A9DBEB37B2F__INCLUDED_)
#define AFX_DLGEDITKEYWORDS_H__9BA5DBF0_1B58_4BFB_85F1_8A9DBEB37B2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEditKeywords.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgEditKeywords dialog
#define DEK_KEYWORD			0
#define DEK_KEYWORDAPPEND	1

class CDlgEditKeywords : public CDialog
{
// Construction
public:
	UINT SetTypeKeyword(UINT iTypeKeyword);
	void SetKeywordText(const char *text);
	void FindAndSelect(const char *text);
	BOOL SaveKeywords();
	UINT LoadKeywords();
	void UpdateCtrls();
	const char * GetLexerName();
	DWORD GetLexerType();
	DWORD SetLexerType(const char *cType);
	DWORD SetLexerType(DWORD iType);
	CDlgEditKeywords(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgEditKeywords)
	enum { IDD = IDD_DLGKEYWORDS };
	CButton	m_BtnAddAppendKW;
	CButton	m_BtnDeleteAppendKW;
	CStatic	m_StaticAppend;
	CEdit	m_EditAppendText;
	CEdit	m_Edit;
	CComboBox	m_Combo;
	CListCtrl	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEditKeywords)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgEditKeywords)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelchangeComboType();
	afx_msg void OnItemchangedListKeywords(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtondelete();
	afx_msg void OnButtonadd();
	afx_msg void OnButtonupdate();
	afx_msg void OnEndlabeleditListKeywords(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonaddAppendKW();
	afx_msg void OnButtondeleteAppendKW();
	afx_msg void OnChangeEditAppendKW();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	UINT UpdateSeqArray();
	void ResetVisibility();
	UINT m_TypeKeyword;
	int m_CurItem;
	CString m_LexerName;
	DWORD m_LexerType;
	DWORD m_curSubType;
	GP_RarefiedArr<CString> SeqArray;
	GP_RarefiedArr<CString> SeqArrayAppend;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEDITKEYWORDS_H__9BA5DBF0_1B58_4BFB_85F1_8A9DBEB37B2F__INCLUDED_)
