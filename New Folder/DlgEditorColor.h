#if !defined(AFX_DLGEDITORCOLOR_H__2D633FC8_F095_468D_A055_E534D4C75A20__INCLUDED_)
#define AFX_DLGEDITORCOLOR_H__2D633FC8_F095_468D_A055_E534D4C75A20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEditorColor.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CDlgEditorColor dialog
class GPScintilla;

class CDlgEditorColor : public CDialog
{
// Construction
public:
	void SetEditor(GPScintilla *iEditor);
	UINT GetColorsCount();
	UINT FindClrInPalette(COLORREF clr);
	BOOL m_bUpdateClr;
	void SetItemInList(UINT nItem, UINT nColorArr);
	void SetImageInList(UINT nImage, COLORREF clr, COLORREF clrHatch = -1);
	void UpdateColors();
	BOOL LoadColors(DWORD LexerType, const char * cFileName = NULL);
	BOOL SaveColors(DWORD LexerType, const char * cFileName = NULL);
	BOOL SetColors(const GPSCSTYLESET *iArray, UINT nColors);
	UINT GetColors(GPSCSTYLESET *iArray);
	CDlgEditorColor(CWnd* pParent = NULL);   // standard constructor
	~CDlgEditorColor();

// Dialog Data
	//{{AFX_DATA(CDlgEditorColor)
	enum { IDD = IDD_DIALOGEDITORCLR };
	CStatic	m_StaticRGB;
	CSliderCtrl	m_SliderFrg;
	CSliderCtrl	m_SliderBkg;
	CListCtrl	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEditorColor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgEditorColor)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual void OnOK();
	afx_msg void OnApply();
	afx_msg void OnButtonFont();
	afx_msg void OnDblclkListStyles(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCustomdrawSliderbkg(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSliderfrg(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListColors(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeCombofont();
	afx_msg void OnCheckbold();
	afx_msg void OnCheckitalic();
	afx_msg void OnCheckunderline();
	afx_msg void OnChangeEditcharset();
	afx_msg void OnChangeEditfontsize();
	afx_msg void OnCheckvisible();
	afx_msg void OnSelchangeCombocase();
	afx_msg void OnCheckhotspot();
	afx_msg void OnCheckeolfilled();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	GPSCSTYLESET *m_ColorArr;
private:
	int m_CurListSel;
	CImageList m_ILMixed;
	UINT m_nColors;
	GPScintilla *m_Scintilla;
	ICONINFO iiEtalon;
	HICON hiEtalon;
	HICON hiRGB;
	BYTE *arrRGB;
	GP_AutoSizing AUSI;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEDITORCOLOR_H__2D633FC8_F095_468D_A055_E534D4C75A20__INCLUDED_)
