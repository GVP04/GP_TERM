#if !defined(AFX_DLGGUISET_H__6FCD1AF6_FB83_4763_AB5E_8976D5C8E589__INCLUDED_)
#define AFX_DLGGUISET_H__6FCD1AF6_FB83_4763_AB5E_8976D5C8E589__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGUISet.h : header file
//
#include "GPObjDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgGUISet dialog

class CDlgGUISet : public CDialog
{
// Construction
public:
	void MoveExampleDlg();
	GPObjDialog * m_GPObjDialog;
	void DeleteTestDialog();
	void CreateTestDialog();
	void CreateTestDialogCh();
	void UpdateScrView();
	CDlgGUISet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGUISet)
	enum { IDD = IDD_DLGGUISET };
	CComboBox	m_ComboCharset;
	CSliderCtrl	m_ScaleSlider;
	CComboBox	m_FontCombo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGUISet)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGUISet)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnCustomdrawSliderScale(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeCombocharcet();
	afx_msg void OnSelchangeCombofont();
	afx_msg void OnCheckdefault();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void FillFontCombo();
	LOGFONT m_Logfont;
	DWORD m_LastScale;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGUISET_H__6FCD1AF6_FB83_4763_AB5E_8976D5C8E589__INCLUDED_)
