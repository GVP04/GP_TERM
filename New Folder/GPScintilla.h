#if !defined(AFX_GPSCINTILLA_H__050454B0_1585_4FA1_9033_F12FD83A7003__INCLUDED_)
#define AFX_GPSCINTILLA_H__050454B0_1585_4FA1_9033_F12FD83A7003__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPScintilla.h : header file
//
#include "GP_HotKey.h"
#include "GPUnit.h"
#include "EditorPrintSettings.h"

/////////////////////////////////////////////////////////////////////////////
// GPScintilla window
#define SC_REPLACE_ALL			0x0000
#define SC_REPLACE_SELECTION	0x0001
#define SC_REPLACE_START		0x0010
#define SC_REPLACE_END			0x0020
#define SC_REPLACE_SCROLL		0x0100


#define SC_REPLACE_POSITIONMASK	0x00FF

#define SC_SAVE_ALL				0x0000
#define SC_SAVE_REPLACE			0x0000
#define SC_SAVE_APPEND			0x0020
#define SC_SAVE_SELECTION		0x0001

#define SC_SORT_ASC		0x0000
#define SC_SORT_DESC	0x0001
#define SC_SORT_WORDS	0x0010
#define SC_SORT_PARA	0x0000
#define SC_SORT_DEFAULT	0x0000
#define SC_SORT_ASNUM	0x0100
#define SC_SORT_ASFLOAT	0x0200
#define SC_SORT_UNIQUE	0x1000

#define GPSC_MARKER_0	0	
#define GPSC_MARKER_1	1	
#define GPSC_MARKER_2	2	
#define GPSC_MARKER_3	3	
#define GPSC_MARKER_4	4	
#define GPSC_MARKER_5	5	
#define GPSC_MARKER_6	6	
#define GPSC_MARKER_7	7	
#define GPSC_MARKER_8	8	
#define GPSC_MARKER_9	9	
#define GPSC_MARKER_10	10
#define GPSC_MARKER_11	11
#define GPSC_MARKER_12	12
#define GPSC_MARKER_13	13
#define GPSC_MARKER_14	14
#define GPSC_MARKER_15	15
#define GPSC_MARKER_16	16
#define GPSC_MARKER_17	17
#define GPSC_MARKER_18	18
#define GPSC_MARKER_19	19
#define GPSC_MARKER_20	20
#define GPSC_MARKER_21	21
#define GPSC_MARKER_22	22
#define GPSC_MARKER_23	23
#define GPSC_MARKER_24	24
#define GPSC_MARKER_25	25
#define GPSC_MARKER_26	26
#define GPSC_MARKER_27	27
#define GPSC_MARKER_28	28
#define GPSC_MARKER_29	29
#define GPSC_MARKER_30	30
#define GPSC_MARKER_31	31
#define GPSC_MARKER_32	32

#define SCCMND_BREAK				0x0100
#define SCCMND_SOFTBREAK			0x0101
#define SCCMND_DIRECTINPUT			0x0102
#define SCCMND_PRINT				0x0110

#define SCCMND_EXECUTE				0x0200
#define SCCMND_EXECUTEREPEAT		0x0201
#define SCCMND_EXECUTEENTER			0x0202

#define SCCMND_SAVECLIENT			0x0300
#define SCCMND_SAVESERVER			0x0301
#define SCCMND_SAVESELCLIENT		0x0302
#define SCCMND_SAVESELSERVER		0x0303
#define SCCMND_SAVECLIENTAS			0x0310
#define SCCMND_SAVESERVERAS			0x0311
#define SCCMND_SAVESELCLIENTAS		0x0312
#define SCCMND_SAVESELSERVERAS		0x0313

#define SCCMND_LOADCLIENT			0x0400
#define SCCMND_LOADCLIENTFROM		0x0401
#define SCCMND_LOADSERVER			0x0402
#define SCCMND_LOADSERVERFROM		0x0403
#define SCCMND_LOADINSCLIENT		0x0410
#define SCCMND_LOADINSCLIENTFROM	0x0411
#define SCCMND_LOADINSSERVER		0x0412
#define SCCMND_LOADINSSERVERFROM	0x0413

#define SCCMND_ZOOMIN				0x0500
#define SCCMND_ZOOMOUT				0x0501
#define SCCMND_MARKERADD			0x0502
#define SCCMND_MARKERTYPENEXT		0x0503
#define SCCMND_MARKERNEXT			0x0504
#define SCCMND_MARKERPREV			0x0505
#define SCCMND_MARKERDELETEALL		0x0506

#define SCCMND_SORTASC				0x0600
#define SCCMND_SORTDESC				0x0601
#define SCCMND_SORTWORDSASC			0x0602
#define SCCMND_SORTWORDSDESC		0x0603
#define SCCMND_SORTUNIQUETASC		0x0608
#define SCCMND_SORTUNIQUETDESC		0x0609
#define SCCMND_SORTUNIQUETWORDSASC	0x060A
#define SCCMND_SORTUNIQUETWORDSDESC	0x060B

#define SCCMND_REDO					0x0700
#define SCCMND_UNDO					0x0701
#define SCCMND_FINDDIALOG			0x0702
#define SCCMND_FINDNEXT				0x0703
#define SCCMND_FINDPREV				0x0704
#define SCCMND_WNDSIZE				0x0705
#define SCCMND_WNDSIZE2				0x0706
#define SCCMND_FINDEXMENU1			0x0710
#define SCCMND_FINDEXMENU2			0x0711
#define SCCMND_FINDEXMENU3			0x0712
#define SCCMND_FINDEXMENU4			0x0713
#define SCCMND_FINDEXMENU5			0x0714
#define SCCMND_FINDEXMENU6			0x0715
#define SCCMND_FINDEXMENU7			0x0716
#define SCCMND_FINDEXMENU8			0x0717
#define SCCMND_FINDEXMENU9			0x0718
#define SCCMND_FINDEXMENU10			0x0719
#define SCCMND_FINDEXMENU11			0x071A
#define SCCMND_FINDEXMENU12			0x071B
#define SCCMND_FINDEXMENU13			0x071C
#define SCCMND_FINDEXMENU14			0x071D
#define SCCMND_FINDEXMENU15			0x071E
#define SCCMND_FINDEXMENU16			0x071F



#define SCCMND_TYPEMASK				0x0F00
#define SCCMND_TYPEBREAK			0x0100
#define SCCMND_TYPEEXECUTE			0x0200
#define SCCMND_TYPESAVE				0x0300
#define SCCMND_TYPELOAD				0x0400
#define SCCMND_TYPEMISC				0x0500
#define SCCMND_TYPESORT				0x0600
#define SCCMND_TYPEEDIT				0x0700

#define GPSC_STYLETYPEMASK			0xFFFF0000
#define GPSC_STYLETYPESTYLE			0x00000000
#define GPSC_STYLETYPEMARKER		0x00010000
#define GPSC_STYLETYPEINDIC			0x00020000

#define MARGIN_SCRIPT_FOLD_INDEX 0x0001

class CDlgGPScintillaFind;


class GPScintilla : public CWnd
{
	friend class GPUnit;
	friend class CDlgEditColor;
// Construction
public:
	void Print(DWORD showDialog, const char *ccAdditionalData);
	int SelectWord(int Position);
	void CloseFindDialog();
	BOOL SaveOnServerSide(const char *FileName, const char *ItemName, DWORD SaveFlags);
	BOOL LoadFromServerSide(const char *FileName, const char *ItemName, DWORD SaveFlags);
	GPScintilla(UINT iUnitId);
	GPScintilla();
	void SetLineColPositionText();
	int (*Scincillafn)(void*,int Message,int wParam,int lParam);
	int ScMethod(int Message,int wParam,int lParam);
	void * Scincillaptr;
	static CEditorPrintSettings EditorPrintSettings;

// Attributes
public:
	BOOL m_bTrackMousePos;
	DWORD m_AutoIndentFlag;
	CString LinePrefix;
	CString ColumnPrefix;
	CString CharPrefix;
	BOOL LoadColors(DWORD LexerType, const char * cFileName = NULL);
	void SetStyleInfo(GPSCSTYLESET & GPCS);
	const static CString StyleInfoToString(GPSCSTYLESET & GPCS);
	const static CString StyleInfoToStringEx(GPSCSTYLESET & GPCS);
	BOOL GetStyleInfo(UINT iStyle, GPSCSTYLESET & GPCS);
	const static GPSCSTYLESET * StringToStyleInfo(const char *iStyle, GPSCSTYLESET & GPCS);
	UINT StringToStyle(const char *iStyle,const char * delimiter);
	void SetAStyle(int style, COLORREF fore, COLORREF back=0xFFFFFF, int size=-1, const char *face=0);
	DWORD HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);

	static DWORD StringFromToReplaceStyle(const char *iReplaceStyle, DWORD & convReplaceStyle);
	static DWORD StringFromToSaveStyle(const char *iReplaceStyle, DWORD & convReplaceStyle);


	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];

	const static UINT uN0Methods;
	const static char *cArr0Methods[];
	const static UINT  uArr0Methods[];

	const static UINT uNStyles;
	const static char *cArrStyles[];
	const static UINT  uArrStyles[];

	const static UINT uNKeybMethods;
	const static char *cArrKeybMethods[];
	const static UINT  uArrKeybMethods[];

	const static UINT uNMarkerMask;
	const static char *cArrMarkerMask[];
	const static UINT  uArrMarkerMask[];

	const static UINT uNKeybDef;
	const static char *cArrKeybDef[];
	const static UINT  uArrKeybDef[];

	const static UINT uNSearchFlags;
	const static char *cArrSearchFlags[];
	const static UINT  uArrSearchFlags[];

	const static UINT uNcaretPolicy;
	const static char *cArrcaretPolicy[];
	const static UINT  uArrcaretPolicy[];

	const static UINT uNWSpaceStyle;
	const static char *cArrWSpaceStyle[];
	const static UINT  uArrWSpaceStyle[];

	const static UINT uNCursorType;
	const static char *cArrCursorType[];
	const static int  uArrCursorType[];

	const static UINT uNEOLMode;
	const static char *cArrEOLMode[];
	const static UINT  uArrEOLMode[];

	const static UINT uNMarginType;
	const static char *cArrMarginType[];
	const static UINT  uArrMarginType[];
	
	const static UINT uNMarginMask;
	const static char *cArrMarginMask[];
	const static UINT  uArrMarginMask[];
	
	const static UINT uNCodePage;
	const static char *cArrCodePage[];
	const static UINT  uArrCodePage[];
	
	const static UINT uNMark;
	const static char *cArrMark[];
	const static UINT  uArrMark[];
	
	const static UINT uNMarkNum;
	const static char *cArrMarkNum[];
	const static UINT  uArrMarkNum[];
	
	const static UINT uNIndicator;
	const static char *cArrIndicator[];
	const static UINT  uArrIndicator[];
	
	const static UINT uNPrintMode;
	const static char *cArrPrintMode[];
	const static UINT  uArrPrintMode[];
	
	const static UINT uNWrapMode;
	const static char *cArrWrapMode[];
	const static UINT  uArrWrapMode[];
	
	const static UINT uNFoldFlag;
	const static char *cArrFoldFlag[];
	const static UINT  uArrFoldFlag[];
	
	const static UINT uNCacheMode;
	const static char *cArrCacheMode[];
	const static UINT  uArrCacheMode[];
	
	const static UINT uNEdgeMode;
	const static char *cArrEdgeMode[];
	const static UINT  uArrEdgeMode[];
	
	const static UINT uNLexer;
	const static char *cArrLexer[];
	const static UINT  uArrLexer[];
	
	const static UINT uNStyleType;
	const static char *cArrStyleType[];
	const static UINT  uArrStyleType[];
	
	const static UINT uNCharSet;
	const static char *cArrCharSet[];
	const static UINT  uArrCharSet[];

	const static UINT uNCaseType;
	const static char *cArrCaseType[];
	const static UINT  uArrCaseType[];

	const static UINT uNVisiblePolicy;
	const static char *cArrVisiblePolicy[];
	const static UINT  uArrVisiblePolicy[];

	const static UINT uNFoldLevel;
	const static char *cArrFoldLevel[];
	const static UINT  uArrFoldLevel[];
	
	const static char *SepViewKeyWordsDef;
	const static char *pbKeyWords;
	const static char *gpKeyWords;
	const static char *fsKeyWords;

	CString SepViewKeyWords;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPScintilla)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	DWORD m_DOflags;
	int AddChar(char iChar, DWORD iFlags);
	int CheckEnteredLength(int iLen);
	int GetWordsList(int iMinLen, char **oBuff);

	BOOL MarginClick(int position, int modifiers);
	void Expand(int &line, BOOL doExpand, BOOL force = FALSE, int visLevels = 0, int level = -1);
	void FoldAll();
	DWORD m_ProcHK;
	DWORD LoadLockKeys();
	CString m_FileNameLK;
	DWORD ShowFindDialog(DWORD dwFlags);
	DWORD m_LockKeysFlag;
	DWORD m_AutoSaveFlag;
	DWORD m_CurMarkerType;
	static HMENU SCCreatePopupMenu(DWORD iMenuType);
	UINT m_DirectInputFlag;
	static UINT GetLexerId(const char *iLexerName);
	static const char *  GetLexerName(DWORD iLexerID);
	void SortText(DWORD sortFlag);
	BOOL LoadKeywords(UINT uLexerType);
	BOOL SaveKeywords(UINT uLexerType);
	CString m_csLastFileName;
	BOOL SaveText(CString &fName, UINT uFlag);
	BOOL LoadText(CString &fName, UINT uFlag);
	UINT SetText(const char *iText, UINT uFlag);
	UINT GetSelText(char **EditText);
	UINT GetText(char **EditText);
	UINT GetText(char **EditText, DWORD flags);
	void SetUseWSColors(BOOL bFore, BOOL bBack);
	int AppendChar(char iCh, UINT SelectionFlag);
	char * AppendString(const char *iCh, UINT SelectionFlag);
	BYTE * AppendBlock(const BYTE *iCh, UINT uBlockLen, UINT SelectionFlag);
	const char * Replace1To13(char *iStr);
	BOOL InitFnPtr;
	virtual ~GPScintilla();
	BOOL SetreferGPU(GPUnit **iGPU);
	UINT DoMethod(const char *iStr, char *oStr);
	UINT GPSetProperty(char *iStr);
	CString m_csDefClFileName;
	CString m_csDefSrvFileName;
	CString m_csDefSrvItemName;
	CString m_csLastSrvFileName;
	CString m_csLastSrvItemName;

	// Generated message map functions
protected:
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	//{{AFX_MSG(GPScintilla)
	afx_msg void OnClose();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bAutoFocus;
	char * m_autocList;
	void PseudoConstructor(UINT iUnitId);
	GP_RarefiedArr<DWORD> *m_ArrLockKey;
	static CDlgGPScintillaFind * m_FindDlg;
	UINT m_EnableContextMenu;
	GPUnit **referGPU;
	UINT UnitId;
	int CharObjId;
	int LineObjId;
	int ColumnObjId;
	int lastSelPos;
	char *m_PBdelim1;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPSCINTILLA_H__050454B0_1585_4FA1_9033_F12FD83A7003__INCLUDED_)
