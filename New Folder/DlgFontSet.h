#if !defined(AFX_DLGFONTSET_H__45A9CB8B_E047_4431_8671_784139DA6831__INCLUDED_)
#define AFX_DLGFONTSET_H__45A9CB8B_E047_4431_8671_784139DA6831__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFontSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFontSet dialog

class CDlgFontSet : public CDialog
{
// Construction
public:
	DWORD m_CurInvert;
	DWORD m_CurCodePage;
	void UpdateScrView();
	CDlgFontSet(CWnd* pParent = NULL);   // standard constructor
	~CDlgFontSet();
// Dialog Data
	//{{AFX_DATA(CDlgFontSet)
	enum { IDD = IDD_DLGFONTSET };
	CComboBox	m_FontCombo;
	CComboBox	m_ComboLanguage;
	CComboBox	m_ComboSubLanguage;
	CComboBox	m_ComboCP;
	CComboBox	m_ComboCompositingQuality;
	CComboBox	m_ComboInterpolationMode;
	CComboBox	m_ComboPixelOffsetMode;
	CComboBox	m_ComboSmoothingMode;
	CComboBox	m_ComboTextContrast;
	CComboBox	m_ComboTextRenderingHint;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFontSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFontSet)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonCodeco();
	afx_msg void OnButtonTestScreen();
	afx_msg void OnSelchangeCombofont();
	afx_msg void OnCheckmcw();
	afx_msg void OnButtongraph();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void FillFontCombo();
	FontFamily *families;
	BOOL m_bLockUpdate;

	CompositingQuality	m_CompositingQuality;
	InterpolationMode	m_InterpolationMode;
	PixelOffsetMode		m_PixelOffsetMode;
	SmoothingMode		m_SmoothingMode;
	DWORD				m_TextContrast;
	TextRenderingHint	m_TextRenderingHint;
	DWORD				m_Language;
	DWORD				m_SubLanguage;
	REAL	m_FontDX;
	REAL	m_FontDY;
	REAL	m_FontOX;
	REAL	m_FontOY;

	CString m_CurFontName;
public:
	afx_msg void OnEnChangeEditfont();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFONTSET_H__45A9CB8B_E047_4431_8671_784139DA6831__INCLUDED_)
