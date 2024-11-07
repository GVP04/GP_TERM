#if !defined(AFX_GPLISTCTR_H__1F8143C1_B9B8_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GPLISTCTR_H__1F8143C1_B9B8_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPListCtr.h : header file
//
#include "GP_HotKey.h"
#include "GPUnit.h"
#include "TableDataContainer.h"

/////////////////////////////////////////////////////////////////////////////
// GPListCtr window

class GPListCtr : public CListCtrl
{
	friend class GPUnit;

// Construction
public:
	GPListCtr(UINT iUnitId);

// Attributes
public:
	DWORD HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
	const static UINT uNGRAlign;
	const static char *cArrGRAlign[];
	const static UINT uArrGRAlign[];
	const static UINT uNLView;
	const static char *cArrLView[];
	const static UINT uArrLView[];
	const static UINT uNIState;
	const static char *cArrIState[];
	const static UINT uArrIState[];
	const static UINT uNIMask;
	const static char *cArrIMask[];
	const static UINT uArrIMask[];
	const static UINT uNGrMask;
	const static char *cArrGrMask[];
	const static UINT uArrGrMask[];
	const static UINT uNGrState;
	const static char *cArrGrState[];
	const static UINT uArrGrState[];

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPListCtr)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	DWORD m_LCDOflag;
	int m_DOSubItem;
	int AddChar(char iChar, DWORD iFlags);
	UINT m_CSFlag;
	const static CString IStateToString(UINT iState);
	const static CString IMaskToString(UINT iMask);
	const static CString GrMaskToString(UINT iMask);
	const static CString GrStateToString(UINT iMask);
	const static CString LViewToString(UINT iLView);
	const static CString GrAlignToString(UINT iAlign);

	static UINT StringToIState(const char *iStr);
	static UINT StringToIMask(const char *iStr);
	static UINT StringToGrMask(const char *iStr);
	static UINT StringToGrState(const char *iStr);
	static UINT StringToLView(const char *iStr);
	static UINT StringToGrAlign(const char *iStr);

	int m_LastDropTarget;
	int m_LastSort;
	void FillNmListViewStr(NM_LISTVIEW *plv, char *str);
	BOOL AutoUpdate;
	void SetSelByEdit(UINT flg=0);
	int nFilterArrayCount;
	BOOL DESCENDSort;
	int SortColumnNumber;
	DWORD m_AutoSortFlag;
	UINT DoMethod(const char *iStr, char *oStr);
	UINT GPSetProperty(char *iStr);
	virtual ~GPListCtr();

	// Generated message map functions
protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	//{{AFX_MSG(GPListCtr)
	afx_msg void OnKillfocus(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemory(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRdblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReturn(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocus(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginrdrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteallitems(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnInsertitem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchanging(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOdfinditem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOdstatechanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnOdcachehint(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBeginScroll(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndScroll(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGetInfotip(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHotTrack(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemActivate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMarqueeBegin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnHdrBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHdrGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHdrItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHdrItemchanging(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHdrTrack(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHdrItemclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHdrItemdblclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHdrBegintrack(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHdrEndtrack(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHdrDividerdblclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHdrFilterChange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHdrFilterBtnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHdrEnddrag(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_DefItemImage;
	DWORD m_dwVLDelay;
	CTableDataContainer *m_VirtualData;
	UINT m_AutoHFilter;
	void UpdateHti();
	void UpdateHtiPosition();
	void ChangeHTI(int deltaVer, int deltaHor);
	int limit_of_images;
	BOOL m_bDragging;
	int m_iDragItem;
	int *iArrPosExOut;
	COleDateTime Cmpd1,Cmpd2;
	UINT lastMask,lastFormat,lastState,lastStateMask,lastFlag;
	CStatic *m_StaticCursor;
	UINT DefEditor;
	BOOL MayBeChangeEdit;
	CString LastEditResult;
	UINT LastEditorID;
	UINT EditorID;
	bool SetEditRect();
	LVHITTESTINFO RBhti;
	LVHITTESTINFO hti;
	LVHITTESTINFO htiPosition;
	LVHITTESTINFO lasthti;
	UINT m_EditInProgr;
	GPUnit **referGPU;
	GPTextArray *FilterArray;
	POSITION selposition;
	UINT UnitId;
	BOOL MSCreateImageList(CImageList *pImageList_tmp, int imagecounter, int count);
	static int CALLBACK mCompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK mCompareFuncNum(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK mCompareFuncDate(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPLISTCTR_H__1F8143C1_B9B8_11D2_B27D_00600840D054__INCLUDED_)
