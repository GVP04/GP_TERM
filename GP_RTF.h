#if !defined(AFX_GP_RTF_H__416CB5A8_3492_11D4_A239_CA7E3E8A8717__INCLUDED_)
#define AFX_GP_RTF_H__416CB5A8_3492_11D4_A239_CA7E3E8A8717__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GP_RTF.h : header file
//
#include "GP_HotKey.h"
#include "GPUnit.h"

/////////////////////////////////////////////////////////////////////////////
// GP_RTF window

//#define LINE_COLUMN_TIMER_ID	1
//#define LINE_COLUMN_TIMER_DELAY	500

class GP_RTF : public CRichEditCtrl
{
	friend class GPUnit;
// Construction
public:
	DWORD HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);
	GP_RTF(UINT iUnitId);

// Attributes
public:
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GP_RTF)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	DWORD m_DOflags;
	int AddChar(char iChar, DWORD iFlags);
	UINT m_Indent;
	CString m_TabReplaser;
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
	BOOL m_bTrackMousePos;
	void SetLineColPositionText();
	CString LinePrefix;
	CString ColumnPrefix;
	CString CharPrefix;
	virtual ~GP_RTF();
	UINT DoMethod(const char *iStr, char *oStr);
	UINT GPSetProperty(char *iStr);

	// Generated message map functions
protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	//{{AFX_MSG(GP_RTF)
	afx_msg void OnChange();
	afx_msg void OnErrspace();
	afx_msg void OnHscroll();
	afx_msg void OnMaxtext();
	afx_msg void OnNotifySetfocus();
	afx_msg void OnUpdate();
	afx_msg void OnALIGN_LTR_EC();
	afx_msg void OnALIGN_RTL_EC();
	afx_msg void OnVscroll();
	afx_msg void OnMSGFILTER();
	afx_msg void OnREQUESTRESIZE();
	afx_msg void OnSELCHANGE();
	afx_msg void OnDROPFILES();
	afx_msg void OnPROTECTED();
	afx_msg void OnCORRECTTEXT();
	afx_msg void OnSTOPNOUNDO();
	afx_msg void OnIMECHANGE();
	afx_msg void OnSAVECLIPBOARD();
	afx_msg void OnOLEOPFAILED();
	afx_msg void OnOBJECTPOSITIONS();
	afx_msg void OnDRAGDROPDONE();
	afx_msg void OnPARAGRAPHEXPANDED();
	afx_msg void OnALIGNLTR();
	afx_msg void OnALIGNRTL();
	afx_msg void OnLINK();
	afx_msg void ParentNotify(UINT message, LPARAM lParam);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnNotifyKillfocus();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	UINT AutoWidthMin,AutoWidthMax,AutoWidthDelta;
	UINT m_uCurVP;
	void OnChangeVP();
	UINT CharObjId;
	UINT LineObjId;
	UINT ColumnObjId;
	int lastSelPos;
	GPUnit **referGPU;
	UINT UnitId;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GP_RTF_H__416CB5A8_3492_11D4_A239_CA7E3E8A8717__INCLUDED_)
