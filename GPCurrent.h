// GPCurrent.h: interface for the GPCurrent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPCURRENT_H__31E40C07_1CBA_11D3_B27E_00600840D054__INCLUDED_)
#define AFX_GPCURRENT_H__31E40C07_1CBA_11D3_B27E_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define GP_CUR_EXITFLAG				0x0001
#define GP_CUR_COMMFLAG				0x0002
#define GP_CUR_ADDITIONALLOOP		0x0004
#define GP_CUR_LOCKCOM				0x0008

#define GP_NIMAGELIST		64

#include "GPImageList.h"
#include "GPODBC_Database.h"
#include "GPCDAOWorkspace.h"
#include "GPSprArray.h"
#include "ListMaker.h"
#include "GPOLEExcel1.h"
#include "GPRegionArr.h"
#include "GPCursorArr.h"
#include "GPIOFileArray.h"
#include "GPHandleArray.h"
#include "DlgStatistics.h"
#include "ErrReport.h"
#include "ODContextArray.h"
#include "GPScript.h"
#include "GPTwain.h"

class CDlgMethods;
class GPUnit;
class CGPToolTipCtrl;

#define GPNTS_DELETE_EVENT		0x0001
#define GPNTS_DELETE_STRUCT		0x0002


#define GP_STRTFLG_HIDE				0x0001
#define GP_STRTFLG_HIDEONCE			0x0002
#define GP_STRTFLG_SHOWLOGINDIALOG	0x0004



typedef struct _GPNOTIFYTHREADSTRUCT
{
	HANDLE hEvent;
	BOOL *m_StopWorking;
	CString csSubName;
	CString csInfo;
	HANDLE hHahdle;
	UINT nTimes;
	DWORD autoDelete;
} GPNOTIFYTHREADSTRUCT, *PGPNOTIFYTHREADSTRUCT;

typedef struct _GPDRAGDROPSTRUCT
{
	UINT IdDlg;
	UINT IdScr;
	CString DlgScrName;
	UINT IdObj;
	CString ObjName;
	CString DragName;
	CString MessageSting;
	CImageList *pImageList;
	HWND hWndDrag;
	HWND hWndLast;
} GPDRAGDROPSTRUCT, *PGPDRAGDROPSTRUCT;

typedef struct _GPSCSTYLESET
{
	UINT msize;
	COLORREF frg;
	COLORREF bkg;
	UINT id;
	UINT fontSize;
	UINT underline;
	UINT bold;
	UINT italic;
	UINT visible;
	UINT EOLFilled;
	UINT Case;
	UINT CharacterSet;
	UINT HOTSPOT;
	CString styleName;
	CString StyleDescription;
	CString fontName;
} GPSCSTYLESET, *PGPSCSTYLESET;

typedef struct _GPUNITINFO
{
	UINT IdDlg;
	UINT IdObj;
	UINT IdDlg2;
	UINT IdObj2;
	CString ObjName;
	HWND hWnd;
	HWND hWnd2;
	UINT ObjType;
	UINT ObjType2;
} GPUNITINFO, *PGPUNITINFO;

struct OLESETTINGS
{
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
};

class CGP_TermView;
class CGP_TermDoc;
class CGPContextMenu;

typedef struct _GPGUISET
{
	CString FontName;
	unsigned short CharSet;
	DWORD Scale;
	WORD Weight;
	BYTE Italic;
	WORD PointSize;
	DWORD UseDefault;
}GPGUISET,*PGPGUISET;

typedef struct _GPCONV3
{
	DWORD dwState;
	DWORD dwType;
	DWORD dwCP;
	DWORD dwConv;
	DWORD dwLang;
	DWORD dwSubLang;
	DWORD dwSort;
	LCID lng;
}GPCONV3,*PGPCONV3;


class GPCurrent
{
public:
	CGPTwain *m_Twain;
	SC_HANDLE m_SC_HANDLE;
	DWORD m_dwAltFlag;
	int ParseCommandLine(DWORD dwFlags, const char *iCmdLine);
	CString cs_RegTermViewSetName;
	CString cs_ScriptLine;
	CGPScript m_GPScript;

	CString cs_ScriptWaitLine;
	CString cs_ScriptWaitLineCurrent;
	DWORD dw_LoginDialogFlags_temporary;
	DWORD dw_ScriptWaitFlag;
	DWORD dw_StartFlags;
	const static enum Conv3TypeEnum
	{
	MBC3_NONE=0,
	MBC3_MBTOWIDECHAR=1,
	MBC3_LCMAPSTRING=2,
	MBC3_MBLC=4,
	MBC3_LCMB=8,
	};


	DWORD MBConv3SrwPC(const char *pcSrc, char *pcDst);
	DWORD MBConv3PCSrw(const char *pcSrc, char *pcDst);
	DWORD GetMBConv3SrwPC();
	DWORD GetMBConv3PCSrw();
	DWORD SetMBConv3(DWORD dwSrwPC, DWORD dwPCSrv);
	DWORD m_USEMBCONV3;
	GPCONV3 m_CONV3PCSRV;
	GPCONV3 m_CONV3SRVPC;
	DWORD LoadGraphCodeco();
	DWORD SaveGraphCodeco();
	DWORD * dwGraphDecodeArray;
	DWORD dwnCP;
	DWORD * dwCodePages;
	DWORD dwGraphFlag;
	GPGUISET m_GUISet;
	CString m_TermRegName;
	CGPSpr SprVariables;
	DWORD dwMBReposition;
	ULONG tcrc16[20];
	DWORD m_WideOn2Pos;
	DWORD m_USEMBCONV;
	DWORD m_USEMBCONV2;
	DWORD m_CurMBInvert;
	DWORD m_CurCodePage;

	CompositingQuality	m_CompositingQuality;
	InterpolationMode	m_InterpolationMode;
	PixelOffsetMode		m_PixelOffsetMode;
	SmoothingMode		m_SmoothingMode;
	DWORD				m_TextContrast;
	TextRenderingHint	m_TextRenderingHint;
	DWORD				m_Language;
	DWORD				m_SubLanguage;


	COLORREF m_curOutScrBkg;
	ULONG_PTR GDIPtoken;
	GP_RarefiedArr<DWORD> DirecOutputArray;
	DWORD EnableSlavePrint;
	DWORD EnableSlavePrintCHARVIEW;
	CString csLocaleStr;
	int DelimiterIn1;
	int DelimiterIn2;
	int DelimiterIn3;
	int DelimiterIn4;
	int DelimiterIn5;
	int DelimiterIn6;
	CString csDelimiterIn1;
	CString csDelimiterIn2;
	CString csDelimiterIn3;
	CString csDelimiterIn4;
	CString csDelimiterIn5;
	CString csDelimiterIn6;
	int DelimiterSrc1;
	int DelimiterSrc2;
	int DelimiterSrc3;
	int DelimiterSrc4;
	int DelimiterSrc5;
	int DelimiterSrc6;
	DWORD m_SSHFlags;
	CDlgStatistics *DlgStatistics;
	BOOL SetIconFromIL(HWND iHWND, const char *iILName, int iImageNum);
	CGPContextMenu *m_pContextMenu;
	CString csODCTerminalMenuName;
	void SaveBarVisibleFlag();
	DWORD m_BarVisibleFlag;
	UINT StringToRegData(BYTE **ArrData, DWORD dwDataType, const char *iData, char Delimiter);
	UINT RegDataToString(BYTE *iData, UINT uDataLen, DWORD dwDataType, char *outPut);
	const static DWORD uArrPower[];
	const static UINT uNRegistryMethods;
	const static char *cArrRegistryMethods[];
	const static char *cArrRegistryMethodsParams[];

	static HKEY StringFromToHKEY(const char *iKey, HKEY & convKey);
	static UINT StringFromToKEYOPTION(const char *iOption, UINT & convOption);
	static UINT StringFromToSamDesired(const char *iSamDesired, UINT & convSamDesired);
	static DWORD StringFromToRegNotify(const char *iSamDesired, DWORD & convSamDesired);
	static DWORD StringFromToCreateDisp(const char *iSamDesired, DWORD & convSamDesired);
	static DWORD StringFromToValueType(const char *iSamDesired, DWORD & convSamDesired);
	static DWORD StringFromToRestoreOption(const char *iSamDesired, DWORD & convSamDesired);
	static DWORD StringFromToSaveOption(const char *iSamDesired, DWORD & convSamDesired);


	UINT DoRegistryMethod(const char *iStr, char **oStr);
	CGPHandleArray m_HandlerArray;
	char BreakChar;
	UINT m_SystemType;
	UINT m_UpdateSizeNow;
	GPDRAGDROPSTRUCT m_DragDrop;
	UINT uLastMessage;
	WPARAM uLastWparam;
	LPARAM uLastLparam;
	BOOL m_bWaitCursor;
	char TermTip[256];
	CString termCaption;
	CString termCaptionInit;
	CString MsgBoxCaptionInit;
	CString MsgBoxCaption;
	CString ErrBoxCaptionInit;
	CString ErrBoxCaption;

	GPRegionArr RegionArr;
	GPCursorArr CursorArr;
	HWND NextParentFromOLE;
	GPOLEExcel	GPXL;
	CListMaker m_ListMaker;
	BOOL m_bInsertMode;
	const char * DosToAnsiOUTTCL();
	const char * DosToAnsiOUTSUB();
	UINT GetOUTTCLLen();
	UINT GetOUTSUBLen();
	const char * GetOUTSUB();
	const char * GetOUTTCL();
	const char * AddToOUTSUB(const char *iStr);
	const char * AddToOUTTCL(const char * iStr);
	void ClearOUTSUB();
	void ClearOUTTCL();
	CGPSprArray m_SprArray;
	GPIOFileArray m_IOFileArray;
	CDlgMethods *m_DlgMethods;
	BOOL BlockControl;
	UINT m_uCurrInputBlock;
	CString arrInputBlocks[300];
	UINT m_uCurrOutputBlock;
	CString arrOutputBlocks[100];
	UINT AjCheckState;
	char contmenuFileName[256];
	char TermCapFileName[256];
	bool EasyTCL;
	char chDosAnsi [256];
	char chWideDosAnsi [256];
	char chWideDosAnsi2 [256];
	char *chWideDosAnsi3;

	char chAnsiDos [256];
	char chWideAnsiDos [256];
	char chWideAnsiDos2 [256];
	char *chWideAnsiDos3;
	char * StrTmpOut;
	GPODBC_Database GPODBC_DB;
	GPCDAOWorkspace GPDAO_WS;
	void Release_m_MuteProc();
	void WaitFor_m_MuteProc();
	HANDLE m_MuteProc;
	int FindImageList(CImageList *iList);
	int GetImageListId(CString Name);
	void InitialLoad();
		CArray<GPImageList,GPImageList> a_GPImageList;
	int StopEventsFlag;
	void LoadOLESettings();

	BOOL FindObject(HWND im_hWnd, GPUNITINFO &iUi);

	BOOL FindObject(const char *cDlgName, const char *cObjName, GPUNITINFO & iUi);
	BOOL FindObject(UINT uIdDlg, const char *cObjName, GPUNITINFO & iUi);
	UINT FindDlg(const char *cDlgName1base/*1base*/);
	GPUnit * GetDlgObject(UINT IdDlg, UINT IdObject);
	
	CString TCLOutputString;
	CString SUBOutputString;
	CString TCLOutputString2;
	CString SUBOutputString2;
	CGP_TermDoc *m_Document;
	CGP_TermView *m_View;
	BOOL TCLinProgress;
	BOOL m_WaitTCL;
	BOOL m_WaitEndTCL;
	BOOL m_WaitSUB;
	BOOL m_WaitEndSUB;
	OLESETTINGS m_OLESETTINGS;

	COleSafeArray DelimArr1;
	COleSafeArray DelimArr2;
	COleSafeArray DelimArr3;
	COleSafeArray DelimArr4;

	CGPToolTipCtrl *m_ScrToolTip;
	GPMessage *GPMSG;
	UINT Flags;
	BOOL AdmIsOn;
	HWND m_hViewWnd;
	int HomeDrive;
	int BlinkValue;
	char app_path[128];

	UINT m_uPixelPerPoint;

	UINT DefFrgColor;
	UINT DefBkgColor;
	UINT DefFrgColorInd;
	UINT DefBkgColorInd;

	UINT Frg_Color;
	UINT Bkg_Color;
	UINT Bkg_Mode;
	UINT Chr_ColorInd;	
	UINT Bkg_ColorInd;	

	UINT ModeSendToDos;
	UINT ModeSendToPick;

	GPCurrent();
	virtual ~GPCurrent();
	UINT nNotifyThreads;
	CErrReport m_ErrReport;
};

#endif // !defined(AFX_GPCURRENT_H__31E40C07_1CBA_11D3_B27E_00600840D054__INCLUDED_)
