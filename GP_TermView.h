// GP_TermView.h : interface of the CGP_TermView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GP_TERMVIEW_H__1509E7B4_DD4C_11D3_970D_0080AD863699__INCLUDED_)
#define AFX_GP_TERMVIEW_H__1509E7B4_DD4C_11D3_970D_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GPScreen.h"
#include "SendPickFlProgress.h"
#include "GPColorDlg.h"
#include "GPAdmIsOn.h"
#include "GPObjDialog.h"
#include "GPFrameWnd.h"
#include "ComPortSetings.h"
#include "DlgTermSet.h"
#include "DlgDumpSettings.h"
#include "GPDlgCommtype.h"
#include "GP_File.h"
#include <stdio.h>
#include <io.h>
#include <direct.h>
#include <process.h>
#include "GP_AutoSizing.h"	
#include "GPDlgFindReplace.h"
#include "DlgSeparateView.h"
#include "DlgSeparateViewInFrame.h"
#include "TermCap.h"
#include "ProcMonitor.h"

#define REFRESH_TIMER_ID      10000
#define PORT_TIMER_ID         10001
#define BAKGROUND_ERASE_TIMER 10002
#define SCRIPTOUT_TIMER_ID    10003
#define KEYBLOCK_TIMER_ID     10004
#define CURSOR_TIMER_ID		  10005
#define PRINT_JOB_TIMER_ID	  10006
#define LICENSE_TIMER_ID	  10010
#define DELAY_TIMER_ID		  10011
#define LISTEN_TIMER_ID		  10012
#define LOCKCOM_TIMER_ID	  10013


#define REFRESH_TIMER_DELAY    1000
#define PORT_TIMER_DELAY		 20
#define BAKGROUND_ERASE_DELAY  1000
#define DLGDOMODAL_DELAY		  1
#define PRINT_JOB_TIMER_DELAY   800

// SSH Dll
#define SSH_TIMING_TIMER_ID 1234

#define GPVIEW_USECONTEXTMENU	0x10000

#define TRANSPRINT			1234567
#define DUMPPRINT			1234568

#define AJ_WRITEDOS				0
#define R03WRITEDOS				1
#define R03READDOS				2
#define AJ_READDOS				3
#define AJ_READNEW				4

#define GP_KEYBBUFFSIZE		10000
#define GP_NFILES			50

#define NBINREADPOOL 50000
#define DEFNIB2 10000

class CGP_TermCntrItem;

class CGP_TermView : public CFormView
{
friend class CGPTInterface;
friend class CGP_TermDoc;
friend class GPListCtr;
friend class GPCMSFlexGrid;
friend class GPWebBrowser2;
friend class CDlgTermSet;
friend class GPDlgViewMPVar;
friend class CMainFrame;
friend class GPWindow;
friend class CDlgViewSystemMethods;
friend class GPCurrent;
friend class GPUnit;
friend class CDlgContextMenu;

protected: // create from serialization only
	CGP_TermView();
	DECLARE_DYNCREATE(CGP_TermView)

public:
	GPDlgFindReplace *GPFRD;
	friend UINT CommunicateFn(LPVOID pParam);
	friend UINT CommunicateFnIO(LPVOID pParam);
	friend UINT CommunicateFn2(LPVOID pParam);
	friend UINT RefreshThreadFn(LPVOID pParam);
	friend UINT MTPaint(LPVOID pParam);
	//{{AFX_DATA(CGP_TermView)
	enum{ IDD = IDD_GP_TERM_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	enum GP_XMOUSE
	{
		//type
		GP_XMOUSE_X10				=    0x00000001,
		GP_XMOUSE_VT200				=    0x00000002,
		GP_XMOUSE_VT200_HIGHLIGHT	=    0x00000004,
		GP_XMOUSE_BTN_EVENT			=    0x00000008,
		GP_XMOUSE_ANY_EVENT			=    0x00000010,
		GP_XMOUSE_MASK_DEC			=    0x000000FF,

		//state
		GP_XMOUSE_INACTION			=    0x00010000,

		//action
		GP_XMOUSE_ACTION_PRESS		=    0x01000000,
		GP_XMOUSE_ACTION_RELEASE	=    0x02000000,
		GP_XMOUSE_ACTION_MOVE		=    0x04000000,
		GP_XMOUSE_ACTION_DBLCLK		=    0x08000000,
		GP_XMOUSE_ACTION_WHEELFRWD	=    0x10000000,
		GP_XMOUSE_ACTION_WHEELFBKW	=    0x20000000,
		GP_XMOUSE_ACTION_MASK		=    0xFF000000,
	};

// Attributes
public:
	CGP_TermDoc* GetDocument();
	// m_pSelection holds the selection to the current CGP_TermCntrItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not CGP_TermCntrItem objects.  This selection
	//  mechanism is provided just to help you get started.

	// TODO: replace this selection mechanism with one appropriate to your app.
	CGP_TermCntrItem* m_pSelection;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGP_TermView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL IsSelected(const CObject* pDocItem) const;// Container support
	virtual BOOL OnScrollBy(CSize sizeScroll, BOOL bDoScroll = TRUE);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	int XMouseAction(DWORD dwAction, UINT nFlags, CPoint point);
	static int PrepareXMouseState(int iState);
	static UINT m_PrintTransp;
	GPMenu *m_GPMenu;
	CODContextArray *m_ODContextsArray;
	void UpdateMenuByAdm();
	BOOL AddCharToDirectInput(char cChar, GPScreen *s);
	DWORD m_dwParseInitStrFlag;
	DWORD GetScreenText(CString &oStr,Rect & re);
	DWORD DoScriptCommand();
	int DoAdditionalMessageLoop();
	HBITMAP sysCaretBitmap;
	DWORD m_OutputCharDelay;
	static int m_ListenTime;
	virtual void BeginListen();
	virtual UINT EmulateRemappingInput(int iJob, const char *iStr, UINT nByte);
	CString m_csOldTermCapFileName;
	CString m_csCurentTermCapFileName;
	CTime m_LastActivity;
	static UINT m_uLockBeep;
	UINT SendStringToPICK(char *oStr);
	static BOOL m_CRLFflag;
	static BOOL m_CRLFflag2;
	CString OldPaletteFile;
	CString CurentPaletteFile;
	UINT SendPredefKey(UINT nChar, UINT nModif, UINT nFlg);
	GP_AutoSizing *m_AUSI;
	void CreateObjDlg(UINT iId, char *iInitStr);
	void CreateObjFrame(UINT iId, char *iInitStr);
	void DoRemappingInput();
	CRITICAL_SECTION m_CSRefresh;
	CRITICAL_SECTION m_CSRemap;
	CRITICAL_SECTION m_CSInputSema;
	static BOOL m_TCLvisible;
	static UINT PrintLiningStyle;
//	void DelAllHotkey();
//	BOOL DelHotkey(UINT iId, const char *iHotkeyName);
//	BOOL AddHotkey(char *nm_VK, UINT iId, const char *seq);
	static UINT KeybLockDelay;
	static BOOL BeepFlag;
	void SetKeybLock();
	BOOL InsMode;
	BOOL KSendChar(char ch);
	UINT SendWord(UINT ch);
	UINT SendDWord(UINT ch);
	BOOL SendChar(char ch);
	void RefreshBlink();
	int m_OperationId;
	virtual ~CGP_TermView();
	DWORD dwWindowGrid;
	CBitmapPlus *pPreviewBitmap;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	int iLastCommand;
	CProcMonitor *m_pProcMonitor;
	CGPAsyncSocket *ListenSock;
	int esc_pointer;
	static DWORD m_UseContextMenu;
	void CreateInputOutputDlgInFrame();
	void DeleteInputOutputDlgInFrame();
	CDlgSeparateViewInFrame *m_DlgSeparateViewInFrame;
	CDlgSeparateView m_DlgSeparateView;
	void CreateInputOutputDlg();
	static UINT m_ViewMode;
	FILE * m_CaptureFile;
	DWORD m_CaptureFlags;
	void SetMouseSelectionCursor();
	Point m_SelectionLastPoint;
	Point m_SelectionStartPoint;
	DWORD m_MouseSelectionMode;
	static UINT m_MaxIdle;
	BOOL CommFnIsRun;
	BOOL CommFn2IsRun;
	BOOL CommFn3IsRun;
	BOOL RefreshThreadIsRun;
	static UINT m_HIDEVIEWMODE;
	static BOOL SlaveVisible;
	int slave_nbcur;
	UINT LastProcKey;
//	CWinThread *m_PPaintThread;
	int CurLenIB2;
	UINT LockPos;
	GP_HotKey *UnitHotkey;
	GP_File *aGP_File[GP_NFILES];
	BOOL alt_press;
	static UINT CursorTimerDelay;
	BOOL AutoDecodFT;
	static UINT LockRemappingFlag;
	static BOOL FlagBufferKeb;
	char *KeybBuffer;
	static UINT KeybBufferSize;
	UINT iSkip_0;
	UINT iSkip_10;
	UINT iSkip_13;
	int ReadDos();
	int WriteDos();
	UINT MouseLastFlag;
	CPoint MouseLastPoint;
	BOOL OldMouse;
	DWORD dwXMouseMode;
	Point poXmouseFirst;
	Point poXmouseLast;
	BOOL LoadScrRgn(char *name,Point topleft);
	int DoEscSeq(int esc_variant);
	int job_flag,next_job;
	char *InputBuffer;
	char *InputBuffer2;
	SendPickFlProgress *SendPickFlProgressDlg;
	UINT RemappingInput(int nbyte);
	int stopchar;
	char *name_curent;
	int string_ptr,inputnbyte,curent_inputbyte,forcounter,log_flag;
	BOOL RemappingInputInProc;
	BOOL HalfIntensity;
	BOOL GetOptimalSize(int &cx, int &cy);

// Generated message map functions
protected:
	DWORD HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point);
	void OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point);
	void OnDragMouseHover();
	void SafeInit();
	//{{AFX_MSG(CGP_TermView)
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInsertObject();
	afx_msg void OnCancelEditCntr();
	afx_msg void OnCancelEditSrvr();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnComsettingsdlg();
	afx_msg void OnKEYALTF1();
	afx_msg void OnKEYALTF10();
	afx_msg void OnKEYALTF11();
	afx_msg void OnKEYALTF12();
	afx_msg void OnKEYALTF2();
	afx_msg void OnKEYALTF3();
	afx_msg void OnKEYALTF5();
	afx_msg void OnKEYALTF6();
	afx_msg void OnKEYALTF7();
	afx_msg void OnKEYALTF9();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyblock();
	afx_msg void OnTranslateTcl();
	afx_msg void OnDefcolor();
	afx_msg void OnButtoncalc();
	afx_msg void OnColordlg127();
	afx_msg void OnStartNewSession();
	afx_msg void OnUpdateStartNewSession(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOnMenuadm(CCmdUI* pCmdUI);
	afx_msg void OnSentinitstr();
	afx_msg void OnMenuadm();
	afx_msg void OnAltBCom();
	afx_msg void OnUpdateAltBCom(CCmdUI* pCmdUI);
	afx_msg void OnAltb();
	afx_msg void OnTermSettings();
	afx_msg void OnFontLocaleSettings();
	afx_msg void OnGUISettings();
	afx_msg void OnReconnect();
	afx_msg void OnUpdateReconnect(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnClsscr();
	afx_msg void OnRemoveallmenu();
	afx_msg void OnRemoveallobj();
	afx_msg void OnDumpclear();
	afx_msg void OnDumppreview();
	afx_msg void OnDumpstartstop();
	afx_msg void OnUpdateDumpstartstop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDumpclear(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDumppreview(CCmdUI* pCmdUI);
	afx_msg void OnDumpsettings();
	afx_msg void OnLasttprint();
	afx_msg void OnLasttprintview();
	afx_msg void OnUpdateLasttprint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLasttprintview(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePageSetup(CCmdUI* pCmdUI);
	afx_msg void OnPageSetup();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnF10();
	afx_msg void OnTandemonoff();
	afx_msg void OnUpdateTandemonoff(CCmdUI* pCmdUI);
	afx_msg void OnClsscr0();
	afx_msg void OnCreatedlg();
	afx_msg void OnUpdateCreatedlg(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnOlesettingsdlg();
	afx_msg void OnTermHide();
	afx_msg void OnRemovealldlg();
	afx_msg void OnHelp();
	afx_msg void OnHelpFinder();
	afx_msg void OnCreateframe();
	afx_msg void OnKEYALTF8();
	afx_msg void OnKEYSHF10();
	afx_msg void OnShowdlgmethods();
	afx_msg void OnDlgviewspr();
	afx_msg void OnUpdateDlgviewspr(CCmdUI* pCmdUI);
	afx_msg void OnDlgdebuger();
	afx_msg void OnDlgErrors();
	afx_msg void OnFiledialog();
	afx_msg void OnUpdateDlgdebuger(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCreateframe(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRemovealldlg(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRemoveallobj(CCmdUI* pCmdUI);
	afx_msg void OnBreakslave();
	afx_msg void OnUpdateBreakslave(CCmdUI* pCmdUI);
	afx_msg void OnDumpsockerror();
	afx_msg void OnUpdateDumpsockerror(CCmdUI* pCmdUI);
	afx_msg void OnBeginslave();
	afx_msg void OnUpdateBeginslave(CCmdUI* pCmdUI);
	afx_msg void OnEndslave();
	afx_msg void OnUpdateEndslave(CCmdUI* pCmdUI);
	afx_msg void OnNohideoutput();
	afx_msg void OnUpdateNohideoutput(CCmdUI* pCmdUI);
	afx_msg void OnRegisterterm();
	afx_msg void OnUpdateRegisterterm(CCmdUI* pCmdUI);
	afx_msg void OnDesktopdlg();
	afx_msg void OnUpdateDesktopdlg(CCmdUI* pCmdUI);
	afx_msg void OnScrObjdlg();
	afx_msg void OnUpdateScrObjdlg(CCmdUI* pCmdUI);
	afx_msg void OnDlgviewiofile();
	afx_msg void OnUpdateDlgviewiofile(CCmdUI* pCmdUI);
	afx_msg void OnDlgviewFSMethods();
	afx_msg void OnUpdateDlgviewFSMethods(CCmdUI* pCmdUI);
	afx_msg void OnContextHelp();
	afx_msg void OnDlgviewregmethods();
	afx_msg void OnUpdateDlgviewregmethods(CCmdUI* pCmdUI);
	afx_msg void OnEditScreenToCb();
	afx_msg void OnUpdateEditScreenToCb(CCmdUI* pCmdUI);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnDumpcaptureclear();
	afx_msg void OnDumpcapturepreview();
	afx_msg void OnDumpcapturepreviewsetup();
	afx_msg void OnSlavePrintPageSetup();
	afx_msg void OnDumpcapturestartstop();
	afx_msg void OnUpdateDumpcaptureclear(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDumpcapturepreview(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDumpcapturestartstop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDumpcapturepreviewsetup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSlavePrintPageSetup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateScriptStop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateScriptExecute(CCmdUI* pCmdUI);
	afx_msg void OnScriptStop();
	afx_msg void OnScriptExecute();
	afx_msg void OnDumpcapturestop();
	afx_msg void OnUpdateDumpcapturestop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateScreenSizeMenu(CCmdUI* pCmdUI);
	afx_msg void OnScreenSizeMenu(UINT nID);
	afx_msg void OnUpdateWindowGrid(CCmdUI* pCmdUI);
	afx_msg void OnWindowGrid();
	afx_msg void OnDumpstop();
	afx_msg void OnUpdateDumpstop(CCmdUI* pCmdUI);
	afx_msg void OnSeparateviewmode();
	afx_msg void OnUpdateSeparateviewmode(CCmdUI* pCmdUI);
	afx_msg void OnSeparateviewinframe();
	afx_msg void OnUpdateSeparateviewinframe(CCmdUI* pCmdUI);
	afx_msg void OnUpdateClsscr0(CCmdUI* pCmdUI);
	afx_msg void OnDlgviewimagelists();
	afx_msg void OnUpdateDlgviewimagelists(CCmdUI* pCmdUI);
	afx_msg void OnTermcap();
	afx_msg void OnUpdateTermcap(CCmdUI* pCmdUI);
	afx_msg void OnTermcapAV();
	afx_msg void OnUpdateTermcapAV(CCmdUI* pCmdUI);
	afx_msg void OnEnablecontextmenu();
	afx_msg void OnUpdateEnablecontextmenu(CCmdUI* pCmdUI);
	afx_msg void OnEditcontextmenu();
	afx_msg void OnUpdateEditcontextmenu(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFullcontextmenu(CCmdUI* pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnDlgviewContextMenuMethods();
	afx_msg void OnUpdateDlgviewContextMenuMethods(CCmdUI* pCmdUI);
	afx_msg void OnDlgviewsysmethods();
	afx_msg void OnUpdateDlgviewsysmethods(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTermHide(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // debug version in GP_TermView.cpp
inline CGP_TermDoc* CGP_TermView::GetDocument()
   { return (CGP_TermDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GP_TERMVIEW_H__1509E7B4_DD4C_11D3_970D_0080AD863699__INCLUDED_)
