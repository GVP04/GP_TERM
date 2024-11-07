#if !defined(AFX_DLDTERMCAPVIDEO_H__96F98F41_79D7_4C5B_BE32_A1C6D2BD5085__INCLUDED_)
#define AFX_DLDTERMCAPVIDEO_H__96F98F41_79D7_4C5B_BE32_A1C6D2BD5085__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DldTermcapVideo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDldTermcapVideo dialog

class CDldTermcapVideo : public CDialog
{
// Construction
public:
	CDldTermcapVideo(CWnd* pParent = NULL);   // standard constructor
   	~CDldTermcapVideo();

// Dialog Data
	//{{AFX_DATA(CDldTermcapVideo)
	enum { IDD = IDD_DIALOGCMDMIXER };
	CComboBox	m_ComboTerminal;
	CComboBox	m_ComboFrg;
	CComboBox	m_ComboBkg;
	CListCtrl	m_ListCommands;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDldTermcapVideo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDldTermcapVideo)
	virtual void OnOK();
	afx_msg void ComposeSequence();
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnCancel();
	afx_msg void OnSelchangeComboterminal();
	virtual BOOL OnInitDialog();
	afx_msg void OnApply();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	GP_RarefiedArr<CString> m_CmdNamesArray;
	DWORD *m_VAttrTable;
	DWORD m_VAttrTableCount;
	DWORD m_VAttrTableMax;
	void UpdateListFromArray();
	void UpdateListItemFromArray(int iItemId);
	void UpdateObjectsFromArray(DWORD cmdID, DWORD dwTermId);
	BOOL m_LockUpdate;
	DWORD *GetVAttrByCmdId(DWORD cmdID, DWORD dwTermId);
	DWORD m_CurTerminalId;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLDTERMCAPVIDEO_H__96F98F41_79D7_4C5B_BE32_A1C6D2BD5085__INCLUDED_)
