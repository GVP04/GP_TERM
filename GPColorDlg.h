#if !defined(AFX_GPCOLORDLG_H__A84BE401_106A_11D3_87EE_947CD033931D__INCLUDED_)
#define AFX_GPCOLORDLG_H__A84BE401_106A_11D3_87EE_947CD033931D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPColorDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGPDlgColor127 dialog

class CGPDlgColor127 : public CDialog
{
// Construction
public:
	CGPDlgColor127(CWnd* pParent = NULL);   // standard constructor
	~CGPDlgColor127() {;}

private:
	void GPSetCheck();
	void InvWorkArea();
	void SetSpinners(DWORD iFlag = 0);
	UINT cF[16];
	UINT cB[8];
	UINT cur_cF;
	UINT cur_cB;
	CButton *mbtF[16];
	CButton *mbtB[8];

public:
	static const char *aColorName[8];
	static const char *aIntensityName[2];
	static const char *aForeBackName[2];

private:
	CString OldFileName;
// Dialog Data
	//{{AFX_DATA(CGPDlgColor127)
	enum { IDD = IDD_DIALOGCOLOR };
	CButton	m_r9;
	CButton	m_r8;
	CButton	m_r7;
	CButton	m_r6;
	CButton	m_r5;
	CButton	m_r4;
	CButton	m_r3;
	CButton	m_r24;
	CButton	m_r23;
	CButton	m_r22;
	CButton	m_r21;
	CButton	m_r20;
	CButton	m_r2;
	CButton	m_r19;
	CButton	m_r18;
	CButton	m_r17;
	CButton	m_r16;
	CButton	m_r15;
	CButton	m_r14;
	CButton	m_r13;
	CButton	m_r12;
	CButton	m_r11;
	CButton	m_r10;
	CButton	m_r1;
	CSliderCtrl	m_BlueSpinFon;
	CSliderCtrl	m_GreenSpinFon;
	CSliderCtrl	m_RedSpinFon;
	CSliderCtrl	m_BlueSpin;
	CSliderCtrl	m_GreenSpin;
	CSliderCtrl	m_RedSpin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGPDlgColor127)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGPDlgColor127)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnOK();
	afx_msg void OnReleasedcaptureSlider5(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSlider6(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSlider7(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSlider8(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSlider10(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSlider9(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRadio1();
	afx_msg void OnRadio10();
	afx_msg void OnRadio11();
	afx_msg void OnRadio12();
	afx_msg void OnRadio13();
	afx_msg void OnRadio14();
	afx_msg void OnRadio15();
	afx_msg void OnRadio16();
	afx_msg void OnRadio17();
	afx_msg void OnRadio18();
	afx_msg void OnRadio19();
	afx_msg void OnRadio2();
	afx_msg void OnRadio20();
	afx_msg void OnRadio21();
	afx_msg void OnRadio22();
	afx_msg void OnRadio23();
	afx_msg void OnRadio24();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	afx_msg void OnRadio7();
	afx_msg void OnRadio8();
	afx_msg void OnRadio9();
	afx_msg void OnButtoninvert();
	afx_msg void OnButtondefault();
	afx_msg void OnButtonload();
	afx_msg void OnButtonsave();
	afx_msg void OnButtonbkgdlg();
	afx_msg void OnButtonfrgdlg();
	afx_msg void OnCustomdrawSlider5(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider6(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider7(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider8(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider9(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider10(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPCOLORDLG_H__A84BE401_106A_11D3_87EE_947CD033931D__INCLUDED_)
