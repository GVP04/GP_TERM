#if !defined(AFX_GP_DLGSETTING_H__C63F2321_B9B8_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GP_DLGSETTING_H__C63F2321_B9B8_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GP_DlgSetting.h : header file
//
#include "GPUnit.h"
#include "GPWindow.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgDialogEditor dialog

class CDlgDialogEditor : public CDialog
{
// Construction
public:
	DWORD m_UpdateFlags;
	void UpdateCheckEvents();
	UINT uStlOE;
	UINT uStlO;
	UINT uStlComO;
	UINT uStlWE;
	void UpdateEditDlg();
	void GetObjStyleStr(UINT id, char *StrStl);
	BOOL GetCreationString(UINT Id, char *str);
	BOOL GetMessagesString(UINT Id, char *str);
	void FillObjList(UINT Type);
	void UpdateChecks(int Type);
	void UpdateTabs();
	CDlgDialogEditor(GPWindow* iGPOw, CWnd* pParent = NULL);  
	CDlgDialogEditor(GPFrameWnd* iGPOd, CWnd* pParent = NULL);  
	CDlgDialogEditor(GPObjDialog* iGPOd, CWnd* pParent = NULL);   
   	~CDlgDialogEditor();

	GPWindow* GPOw;
	GPObjDialog* GPOd;
	GPFrameWnd* GPOf;
// Dialog Data
	//{{AFX_DATA(CDlgDialogEditor)
	enum { IDD = IDD_DIALOGOBJECTS };
	CButton	m_ChkWINDOWLESS;
	CButton	m_BtMessToClip;
	CButton	m_btFRGDlg;
	CButton	m_btBrushDlg;
	CButton	m_btBKGDlg;
	CEdit	m_edFRG;
	CEdit	m_edBrush;
	CEdit	m_edBKG;
	CComboBox	m_cbBrushType;
	CComboBox	m_cbBrushStyle;
	CButton	m_btFRG;
	CButton	m_btBRUSH;
	CButton	m_btBKG;
	CButton	m_btClearAllTextEv;
	CButton	m_BtClAllEvents;
	CCheckListBox	m_ListEvents;
	CEdit	m_EditEventsOutput;
	CStatic	m_StaticProperty;
	CEdit	m_EditProperty;
	CButton	m_BtDoProperty;
	CEdit	m_EditParams;
	CEdit	m_EditResult;
	CEdit	m_EditParamsHelp;
	CButton	m_BtExecute;
	CComboBox	m_ComboMethods;
	CButton	m_CheckAutoSel;
	CButton	m_ChecOnTop;
	CEdit	m_EditWSE;
	CEdit	m_EditWS;
	CEdit	m_EditOSE;
	CEdit	m_EditOS;
	CEdit	m_EditGroup;
	CStatic	m_StaticOwner;
	CStatic	m_StaticGroup;
	CComboBox	m_ComboOwner;
	CListBox	m_ListUnitType;
	CStatic	m_StaticToolTip;
	CEdit	m_EditToolTip;
	CButton	m_BtCreatToClip;
	CEdit	m_EditText;
	CStatic	m_StaticText;
	CStatic	m_StaticSizing;
	CEdit	m_EditSizing;
	CComboBox	m_ComboSizing;
	CStatic	m_SOS;
	CStatic	m_Stat4;
	CStatic	m_Stat3;
	CStatic	m_Stat2;
	CStatic	m_Stat1;
	CStatic	m_StaticSize;
	CButton	m_btdelete;
	CEdit	m_ed6;
	CEdit	m_ed5;
	CEdit	m_ed2;
	CEdit	m_ed1;
	CTabCtrl	m_Tabs;
	CCheckListBox	m_ListUnitStl;
	CCheckListBox	m_WSList;
	CSpinButtonCtrl	m_sw;
	CSpinButtonCtrl	m_sh;
	CSpinButtonCtrl	m_st;
	CSpinButtonCtrl	m_sl;
	CListBox	m_LUnit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDialogEditor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDialogEditor)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeListunit();
	afx_msg void OnDblclkListunit();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit5();
	afx_msg void OnChangeEdit6();
	afx_msg void OnButtondelte();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListusestl();
	afx_msg void OnDblclkListusestl2();
	afx_msg void OnButtonupdate();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSelchangeCombosizing();
	afx_msg void OnChangeEditsizing();
	afx_msg void OnChangeEdittext();
	afx_msg void OnButtoncreatoclip();
	afx_msg void OnChangeEdittooltip();
	afx_msg void OnDblclkListunittype();
	afx_msg void OnKillfocusListunittype();
	afx_msg void OnButtonbuffall();
	afx_msg void OnSelchangeComboowner();
	afx_msg void OnKillfocusEditgroup();
	afx_msg void OnChecktopmost();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCheckselect();
	afx_msg void OnSelchangeCombomethods();
	afx_msg void OnButtonexecute();
	afx_msg void OnClose();
	afx_msg void OnBtndoproperty();
	afx_msg void OnDblclkListevents();
	afx_msg void OnBtnclallev();
	afx_msg void OnBtnclalltext();
	afx_msg void OnBtnfrgdlg();
	afx_msg void OnBtnfrg();
	afx_msg void OnBtnbrush();
	afx_msg void OnBtnbrushdlg();
	afx_msg void OnBtnbkg();
	afx_msg void OnBtnbkgdlg();
	afx_msg void OnButtonmessagetoclip();
	afx_msg void OnCheckwindowless();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	GPUnit **RefGPU;
	UINT uStlW;
	int xWindowProc,yWindowProc;
	BOOL NoUpdateTxt;
	GPUnit *CurUnit;
	BOOL m_SizeFlag;
	BOOL m_PosFlag;
	BOOL m_UpdSize;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GP_DLGSETTING_H__C63F2321_B9B8_11D2_B27D_00600840D054__INCLUDED_)
