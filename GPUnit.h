// GPUnit.h: interface for the GPUnit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPUNIT_H__CAC53B23_CBDD_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GPUNIT_H__CAC53B23_CBDD_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mmsystem.h"
#include "GPCurrent.h"
#include "GP_HotKey.h"
#include "GPWndSizerArr.h"
#include "ODContext.h"

void calc_CRC16(ULONG *t16, ULONG *crc,BYTE nextbyte);
DWORD calc_CRC16(const BYTE *iArray, DWORD dwArrLen = 0, ULONG PrevCRC = 0, ULONG *table16 = NULL);

typedef struct _GPKEYPROC
{
	DWORD dwSrcVK;
	DWORD dwDstVK;
	CString csMethods;
} GPKEYPROC, *PGPKEYPROC;

extern int m_LastScanf;
extern GPCurrent GPC;
extern UINT cFEtalon[];
extern UINT cBEtalon[];

#define NINITIALUNITS 256
#define GP_NPROPERTY 36

#define GPUA_TOP		0x1
#define GPUA_BOTTOM		0x2
#define GPUA_LEFT		0x4
#define GPUA_RIGHT		0x8
#define GPUA_ENTIRE		0x10

#define ID_DELAY_TIMER_ID	991
#define ID_DELAY_TIMER_DELAY	1000

#define DLGED_MODEEDIT			0x00000001
#define DLGED_MODESELECTION		0x00000002
#define DLGED_MODEMASK			0x0000FFFF
#define DLGED_STATEMASK			0xFFFF0000
#define DLGED_STATENEEDREDRAW	0x00010000
#define DLGED_STATESELECTED		0x00020000
#define DLGED_STATEMAJOR		0x00040000

#define DLGED_SELACTADD			0x0001
#define DLGED_SELACTREM			0x0002
#define DLGED_SELACTCLR			0x0004
#define DLGED_SELACTINV			0x0005
#define DLGED_SELACTALLADD		0x0006
#define DLGED_SELACTALLREM		0x0007
#define DLGED_SELACTSETMAIN		0x0008
#define DLGED_SELACTFINDMAIN	0x0009
#define DLGED_SELACTUSERECT		0x1000


typedef struct _DRAWMOVE
{
	int nRect;
	HWND hWndMove;
	CODContext *pODContext;
} DRAWMOVE, *PDRAWMOVE;


class CGPToolTipCtrl;

class GPUnit  
{
friend class CODContextItem;
friend class CDlgViewSystemMethods;
friend class GPWebBrowser2;
friend class CGP_TermView;
friend class CGP_TermDoc;
friend class CDlgDialogEditor;
friend class GPObjDialog;
friend class GPFrameWnd;
friend class GPChLBox;
friend class GPDrLBox;
friend class GPStatic;
friend class GPAniStatic;
friend class GPEdit;
friend class GPButton;
friend class GPAniButton;
friend class GPBButton;
friend class GPListBox;
friend class GPComboBox;
friend class GPComboBoxEx;
friend class GPScrollBar;
friend class GPProgress;
friend class GPAnimate;
friend class GPListCtr;
friend class GPDateTimeCtrl;
friend class GPMonthCalCtrl;
friend class GPSpinButton;
friend class GPTabCtrl;
friend class GPSlider;
friend class GPHeader;
friend class GPTree;
friend class GP_RTF;
friend class GPDlgBar;
friend class GPFrameBar;
friend class GPStatusBar;
friend class GPToolBar;
friend class GPStatusBarCtrl;
friend class GPToolBarCtrl;
friend class GPDialogBar;
friend class GPReBarCtrl;
friend class GPReBar;
friend class GPDrawWnd;
friend class GP_Control;
friend class GPDlgViewMPVar;
friend class GPCMSFlexGrid;
friend class GPScintilla;
friend class CODContextArray;
friend class CODContext;
friend class GPWindow;

public:
	static RECT reMouseSelection;
	static GPUnit *m_ptrUnitValChange;
	static CString m_csLastValueForValChange;
	DWORD  m_dwValChangeFlag;
	MSG* m_CurPreMessage;
	MSG  m_CurMessage;
	UINT m_BkgMode;
	UINT m_clrText;
	UINT m_clrBkgnd;
	CBrush *m_brBkgnd;
	LOGBRUSH lb;
	DWORD dwWndEditFlag;

public:
	void SetReferGPU(GPUnit **newGPU);
	CString m_DrawContextName;
	CODContext *m_ODC;
	DWORD dwScrollFlags;
	DWORD UnitCommonStyles;
	DWORD m_IgnoreSelectionOnTAB;
	static DWORD m_IgnoreMessages;
	static DWORD m_WarningsIgnore;
	static BOOL MouseWheelProc(WPARAM wParam, LPARAM lParam);

	DWORD SelectionAction(DWORD action, LPRECT lpRe);

	void SendOnValChangeEvent(DWORD iType);
	void SetCheckPoint();
	void SetValChangeCheckPoint();
	BOOL DefPreTranslateMessage(MSG* pMsg);
	DWORD m_Scale;
	int m_LastDIChar;
	DWORD AddDirectOutputChar(char iChar);
	DWORD m_DirectOutputFlag;
	DWORD m_bkgSrc;
	int GetObjectIdByName(const char *iName);
	int GetObjectIdByHWND(HWND iHWND);
	DWORD m_UpdateGroupFlag;
	BOOL IsChildOfThis(HWND iHWND);
	void InvalidateGPUnit();
	DWORD StringToStyle(const char *iStr);
	DWORD StringToStyleEx(const char *iStr);
	CString m_ParamDelimiter;
	void AutoSetAutoSizing(UINT iParam);
	void AutoSizingPause();
	void AutoSizingResume();
	void AutoSizingReset();
	void AutoSizingReinitSize();

	const CString GetObjectName();
	void UpdateSizerSize();
	PGPUNITINFO GetUnitInfo(GPUNITINFO & ui);
	static CString UnitInfoToString(PGPUNITINFO ui, const char * delim);
	static CString UnitInfoToString2(PGPUNITINFO ui, const char * delim);
	static CString UnitInfoToString2Ex(PGPUNITINFO ui, const char * delim);

	static const char *StyleExToString(DWORD UnitType, DWORD style, char *iStr, const char *Delimiter);
	static const char *StyleExToString(DWORD style, char *iStr, const char *Delimiter);
	static const char *StyleToString(DWORD UnitType, DWORD style, char *iStr, const char *Delimiter);

	
	static DWORD ChildCtlColor(GPUnit **iGPU, HDC hDC, HWND iUHWND, HBRUSH & ihbr, HBRUSH ihbrStd, DWORD iType);

	CString UnitInfoToString(const char * delim);
	void OffsetWndPoint(LPPOINT point);
	UINT m_NCHITTESTflag;
	UINT GPNCHitTest(CPoint point, UINT BaseRet);
	HCURSOR m_OldHCURSOR;

	const static enum UnitTypeEnum
	{
	UT_MAINDLGSCR=0,	
	UT_CONTROL,
	UT_DRAW,		
	UT_ANISTATIC,	
	UT_ANIBUTTON,
	UT_FRAMEBAR,
	UT_DATETIMECTRL,
	UT_DLGBAR,
	UT_RTF,
	UT_TREECTRL,
	UT_HEADER,	
	UT_SLIDER,
	UT_TABCTRL,
	UT_SPINBUTTON,
	UT_BBUTTON,
	UT_STATIC,
	UT_EDIT,		
	UT_BUTTON,
	UT_LISTBOX,
	UT_COMBOBOX,
	UT_SCROLLBAR,
	UT_PROGRESS,
	UT_ANIMAT,
	UT_CHECKLISTBOX,
	UT_DRAGLISTBOX,
	UT_LISTCTRL,	
	UT_STATUSBARCTRL,
	UT_TOOLBARCTRL,
	UT_STATUSBAR,
	UT_TOOLBAR,
	UT_DIALOGBAR,
	UT_REBARCTRL,
	UT_REBAR,
	UT_FLEXGRID,	
	UT_MONTHCAL,
	UT_WEBBROWSER,
	UT_COMBOBOXEX,
	UT_EDITOR,
	};

	const static enum UnitSubTypeEnum
	{
	UST_DLG=0,			UST_FRAME=1,		UST_SCREEN=2,
	UST_ALLMAIN=3,			
	};

	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];

	const static UINT uNClassStyles;
	const static char *cArrClassStyles[];
	const static UINT  uArrClassStyles[];

	const static UINT uNCCMethods;
	const static char *cArrCCMethods[];
	const static char *cArrCCMethodsParams[];

	const static UINT uNControlBarMethod;
	const static char *cArrControlBarMethod[];
	const static char *cArrControlBarMethodParams[];

	const static UINT uNRedrawFlag;
	const static char *aRedrawFlagName[];
	const static UINT  aRedrawFlagUINT[];

	const static char *aTypeUnit[];
	const static int  auTypeUnit[];
	const static char *cArrAlignSize[5];
	const static UINT  uArrAlignSize[5];
	GP_HotKey *UnitHotkey;
	static int m_UpdateGroupFlagCntr;

	LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	void SendDropMoveEvent(const char *iDestStr,PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void SendDropHoverEvent(const char *iDestStr,PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void SendDropEvent(const char *iDestStr,PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	static void TranslatePenStyle(const char *iStr, UINT *uPenStyle,UINT *uWidth, COLORREF *cColor);
	void UpdateGroup(int SelectedItem, UINT iStyle);
	int CurGroupSelection;
	void DelAllHotkey();
	BOOL DelHotkey(UINT iId, const char *iHotkeyName);
	BOOL AddHotkey(char *nm_VK, UINT iId, const char *seq);
	void GPUpdateUnit();
	char * GetSizingStyle();
	BOOL DoCCMethod(const char *iStr, char *Ostr);
	BOOL DoWindowMethod(const char *iStr, char *Ostr);
	static UINT DoControlBarMethod(CControlBar *CBObj,const char *iStr, char *oStr);
	void SetFont(CFont *fn);
	UINT GetResizeingOwner();
	void GPGetWndRect(CRect *re);
	void GPGetClientRect(CRect *re);
	void GPDeleteAllMessage();
	void GPDeleteMessage(char *mes);
	void GPAddMessage(char *mes);
	UINT DoMethod(const char *iStr,char *oStr);
	void RemappingProperty(const char *iStr);
	UINT GPSetProperty(const char *iValue);
	UINT UnitId;
	GPUnit(UINT iUnitId, UINT iUnitType, const char *iInit, GPUnit **iGPU, CGPToolTipCtrl **ipToolTip, HWND iUnitWnd, GP_AutoSizing *iAUSI);
	virtual ~GPUnit();
	UINT UnitType;
	HWND UnitHWND;
	DWORD m_LastCRC;
	DWORD m_LastValChangeCRC;
	const CString GetCurrentValue(BOOL bRecursive = TRUE);
	const CString GetChangedValue(BOOL bRecursive = TRUE);
	DWORD GetCurrentValueCRC();

private:
	CFont *UnitFont;
	void CheckGroups(UINT iUnitId = 0);
	UINT m_WindowLessFlag;
	CGPWndSizerArr *m_SizerArray;
	GP_RarefiedArr<CString> *m_DropNamesArray;
	GP_RarefiedArr<GPKEYPROC> *m_KeyRedefine;
	GPMessage *GPMSG;
	CString m_DragName;
	CString m_ObjName;
	GP_AutoSizing *AUSI;
	char *GroupNum;
	char * ToolTipText;
	static 	int GetInitParam(GPUnit *mThis, unsigned int UnitType, char *iInit, UINT &InitStyle,  UINT &InitStyleEx, CRect &InitRect, char *iCaption, UINT *ParentNum, char *m_CLSID, DWORD &iScale);
	CGPToolTipCtrl **m_ToolTip;
	GPUnit **GPU;
	void *UnitPtr;
	BOOL NoUpdateParent;
	UINT ParentNum;
	UINT SizStyle;
	UINT *iArrTimerCount;
	int m_nDelayInterval;
	int m_nScrollMargin;
	int m_nScrollInterval;
	UINT m_NGPUNIT;
};

#endif // !defined(AFX_GPUNIT_H__CAC53B23_CBDD_11D2_B27D_00600840D054__INCLUDED_)
