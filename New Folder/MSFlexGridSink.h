#if !defined(AFX_MSFLEXGRIDSINK_H__BD8CCE8E_D9A7_42CA_B049_5DBF8B8997D6__INCLUDED_)
#define AFX_MSFLEXGRIDSINK_H__BD8CCE8E_D9A7_42CA_B049_5DBF8B8997D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MSFlexGridSink.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CMSFlexGridSink command target

class CMSFlexGridSink : public CCmdTarget
{
	friend class GPCMSFlexGrid;
	DECLARE_DYNCREATE(CMSFlexGridSink)

	CMSFlexGridSink();           // protected constructor used by dynamic creation
// Attributes
public:
	static const IID IID_IMSFlexGridSink;

// Operations
public:
	void SetGPMSFlex(void *pt);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSFlexGridSink)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
	virtual ~CMSFlexGridSink();

protected:

//	void OnClickMsflexgrid();

	// Generated message map functions
	//{{AFX_MSG(CMSFlexGridSink)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CMSFlexGridSink)
	afx_msg void OnClickMsflexgrid();
	afx_msg void OnKeyDownMsflexgrid(short FAR* KeyCode, short Shift);
	afx_msg void OnDblClickMsflexgrid();
	afx_msg void OnKeyPressMsflexgrid(short FAR* KeyAscii);
	afx_msg void OnKeyUpMsflexgrid(short FAR* KeyCode, short Shift);
	afx_msg void OnMouseDownMsflexgrid(short Button, short Shift, long x, long y);
	afx_msg void OnMouseMoveMsflexgrid(short Button, short Shift, long x, long y);
	afx_msg void OnMouseUpMsflexgrid(short Button, short Shift, long x, long y);
	afx_msg void OnSelChangeMsflexgrid();
	afx_msg void OnRowColChangeMsflexgrid();
	afx_msg void OnEnterCellMsflexgrid();
	afx_msg void OnLeaveCellMsflexgrid();
	afx_msg void OnScrollMsflexgrid();
	afx_msg void OnCompareMsflexgrid(long Row1, long Row2, short FAR* Cmp);
	afx_msg void OnOLEStartDragMsflexgrid(LPDISPATCH FAR* Data, long FAR* AllowedEffects);
	afx_msg void OnOLEGiveFeedbackMsflexgrid(long FAR* Effect, BOOL FAR* DefaultCursors);
	afx_msg void OnOLESetDataMsflexgrid(LPDISPATCH FAR* Data, short FAR* DataFormat);
	afx_msg void OnOLECompleteDragMsflexgrid(long FAR* Effect);
	afx_msg void OnOLEDragOverMsflexgrid(LPDISPATCH FAR* Data, long FAR* Effect, short FAR* Button, short FAR* Shift, float FAR* x, float FAR* y, short FAR* State);
	afx_msg void OnOLEDragDropMsflexgrid(LPDISPATCH FAR* Data, long FAR* Effect, short FAR* Button, short FAR* Shift, float FAR* x, float FAR* y);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	void * m_ptrGPMSFlex;
};
//	afx_msg void OnClickMsflexgrid();

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSFLEXGRIDSINK_H__BD8CCE8E_D9A7_42CA_B049_5DBF8B8997D6__INCLUDED_)
