#if !defined(AFX_DLG_OLESET_H__3D2FCEC4_F8C7_11D3_970D_0080AD863699__INCLUDED_)
#define AFX_DLG_OLESET_H__3D2FCEC4_F8C7_11D3_970D_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_OLESet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOLESet dialog

class CDlgOLESet : public CDialog
{
// Construction
public:
	CDlgOLESet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOLESet)
	enum { IDD = IDD_DIALOGOLESET };
	CSpinButtonCtrl	m_sWTCL;
	CSpinButtonCtrl	m_sWSUB;
	CSpinButtonCtrl	m_sWFRead;
	CSpinButtonCtrl	m_sWSystem;
	CSpinButtonCtrl	m_sWMM;
	CSpinButtonCtrl	m_sWInput;
	CSpinButtonCtrl	m_sWFWrite;
	CSpinButtonCtrl	m_sWFOther;
	CSpinButtonCtrl	m_sCTCL;
	CSpinButtonCtrl	m_sCSystem;
	CSpinButtonCtrl	m_sCSUB;
	CSpinButtonCtrl	m_sCMM;
	CSpinButtonCtrl	m_sCInput;
	CSpinButtonCtrl	m_sCFWrite;
	CSpinButtonCtrl	m_sCFRead;
	CSpinButtonCtrl	m_sCFOther;
	UINT	m_WTCL;
	UINT	m_WSUB;
	UINT	m_WFRead;
	UINT	m_WSystem;
	UINT	m_WMM;
	UINT	m_WInput;
	UINT	m_WFWrite;
	UINT	m_WFOther;
	UINT	m_CTCL;
	UINT	m_CSystem;
	UINT	m_CSUB;
	UINT	m_CMM;
	UINT	m_CInput;
	UINT	m_CFWrite;
	UINT	m_CFRead;
	UINT	m_CFOther;
	UINT	m_tFOther;
	UINT	m_tFRead;
	UINT	m_tFWrite;
	UINT	m_tInput;
	UINT	m_tMM;
	UINT	m_tSUB;
	UINT	m_tSystem;
	UINT	m_tTCL;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOLESet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOLESet)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdateEdcntfother();
	afx_msg void OnUpdateEdcntfwrite();
	afx_msg void OnUpdateEdcntinput();
	afx_msg void OnUpdateEdcntmm();
	afx_msg void OnUpdateEdcntsub();
	afx_msg void OnUpdateEdcntsystem();
	afx_msg void OnUpdateEdcnttcl();
	afx_msg void OnUpdateEdcntfread();
	afx_msg void OnButoledefload();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_OLESET_H__3D2FCEC4_F8C7_11D3_970D_0080AD863699__INCLUDED_)
