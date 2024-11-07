// GP_Term.h : main header file for the GP_TERM application
//

#if !defined(AFX_GP_TERM_H__1509E7AB_DD4C_11D3_970D_0080AD863699__INCLUDED_)
#define AFX_GP_TERM_H__1509E7AB_DD4C_11D3_970D_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#define ALPHA_SHIFT 24
#define RED_SHIFT   16
#define GREEN_SHIFT 8
#define BLUE_SHIFT  0
#define ALPHA_MASK  ((ARGB) 0xff << ALPHA_SHIFT)

#define MAKEARGB(a, r, g, b) \
                (((ARGB) ((a) & 0xff) << ALPHA_SHIFT)| \
                 ((ARGB) ((r) & 0xff) << RED_SHIFT)  | \
                 ((ARGB) ((g) & 0xff) << GREEN_SHIFT)| \
                 ((ARGB) ((b) & 0xff) << BLUE_SHIFT))


#include "resource.h"       // main symbols
#include "GP_Term_i.h"
#include "GP_QSort.h"
#include "PenExt.h"
#include "PenPlus.h"
#include "MatrixPlus.h"
#include "BitmapPlus.h"
#include "FontExt.h"
#include "BrushExt.h"
#include "RgnExt.h"
#include "FontPlus.h"
#include "BrushPlus.h"
#include "GraphicsPathPlus.h"
#include "RgnPlus.h"
#include "StringFormatPlus.h"
#include "GP_RarefiedArr.h"
#include "GPFont.h"
#include "GP_comm.h"
#include "GPMessage.h"
#include "GPCurrent.h"
#include "GPTextArray.h"
#include "GPMenu.h"
#include "GP_AutoSizing.h"
#include "TermCap.h"



typedef struct _INDEXARR
{
	int Index1;
	int Index2;
	int Index3;
	int Index4;
} INDEXARR, *PINDEXARR;

#define GP_ARGTYPE_NONE			0x00000000
#define GP_ARGTYPE_METHOD		0x00000001
#define GP_ARGTYPE_VARIABLE		0x00000002
#define GP_ARGTYPE_TEXT			0x00000003
#define GP_ARGTYPE_DECNUMBER	0x00000004
#define GP_ARGTYPE_HEXNUMBER	0x00000005
#define GP_ARGTYPE_OCTNUMBER	0x00000006
#define GP_ARGTYPE_BINNUMBER	0x00000007
#define GP_ARGTYPE_DATE			0x00000008
#define GP_ARGTYPE_IF			0x00000009
#define GP_ARGTYPE_LABEL		0x00000010
#define GP_ARGTYPE_KEYWORD		0x00000011
#define GP_ARGTYPE_NEXTCOMMAND	0x00000012
#define GP_ARGTYPE_PLUSPLUS		0x00000013
#define GP_ARGTYPE_MINUMINUS	0x00000014
#define GP_ARGTYPE_ARITHMPLUS	0x00000100
#define GP_ARGTYPE_ARITHMMINUS	0x00000101
#define GP_ARGTYPE_ARITHMMUL	0x00000102
#define GP_ARGTYPE_ARITHMDIV	0x00000103

#define GP_ARGTYPE_TYPEMASK		0x00000FFF

#define GP_ARGTYPE_DYNARRAY		0x00010000
#define GP_ARGTYPE_FORMAT		0x00020000
#define GP_ARGTYPE_BRACE		0x00040000
#define GP_ARGTYPE_EXTRACT		0x00080000

typedef struct _ARGPOSITIONS
{
	DWORD ArgType;
	int Start;
	int End;

	int StartName;
	int StartDAIndex;
	int StartSubstring;
	int StartFormat;
	int StartBrace;

	int EndName;
	int EndDAIndex;
	int EndSubstring;
	int EndFormat;
	int EndBrace;
} ARGPOSITIONS, *PARGPOSITIONS;


char * GetDblStr(char *oStr, char *oStr2, BYTE *Arr, UINT Len);
char * GetDecStr(char *oStr, BYTE *Arr,   UINT Len);
char * GetOctStr(char *oStr, BYTE *Arr,   UINT Len);
char * GetHexStr(char *oStr, BYTE *Arr,   UINT Len);
BYTE * GetDblArr(BYTE *Arr,  const char *oStr, const char *oStr2);
BYTE * GetDecArr(BYTE *Arr,  const char *oStr);
BYTE * GetOctArr(BYTE *Arr,  const char *oStr);
BYTE * GetHexArr(BYTE *Arr,  const char *oStr);
BYTE * convHexToByteArr(const char *iDataSrc, BYTE *ArrDataDst);

char *fgetsEx(char * iStr, int nchar, FILE *fl);
char *DelimitersDown(char *iStr);
int DEVMODEToString(PDEVMODE ipDM, char *oStr);

typedef struct _MAT_ARGS
{
	int AsInt[100];
	double AsDouble[100];
	DWORD dwOperation[100];
	DWORD dwCount;
} MAT_ARGS, *PMAT_ARGS;
double CalcMathString(const char *iString);
MAT_ARGS &CalcArithmeticString(const char *iString, MAT_ARGS &pMA);



char *FindFile(const char *ccFileName, char **oStr, DWORD dwAttributes, DWORD dwDateType, CTime &MinTime, CTime &MaxTime, int nMaxBytes);
char *FindFileRecursive(const char *ccFileName, char **oStr, DWORD dwAttributes, DWORD dwDateType, CTime &MinTime, CTime &MaxTime, int nMaxBytes);
char *FindImages(const char *ccFileName, char **oStr, DWORD dwAttributes, DWORD dwDateType, CTime &MinTime, CTime &MaxTime, const char *ccILName = NULL, int nImage = 0);
char *FindImagesRecursive(const char *ccFileName, char **oStr, DWORD dwAttributes, DWORD dwDateType, CTime &MinTime, CTime &MaxTime, const char *ccILName = NULL, int nImage = 0);
char *RemoveFile(const char *ccFileName, char **oStr, DWORD dwAttributes, DWORD dwDateType, CTime &MinTime, CTime &MaxTime);
BOOL GPDeleteDir(const char * iDir);
BOOL GPCopyDir(const char * sDir, const char * dDir);
void GPCommonDlg(char *iInitString, char *oStr);
void FileBinToText(char *names, char *named);
void FileTexToBin(char *names, char *named);
char * ReplaceSpec(char *pos);
char * DosToAnsi(char *str);
char * DosToAnsiMB(char *str);
BOOL LoadPalette(const char *FileName,UINT *cF, UINT *cB);
char * AnsiToDos(char *str, int flag);
char * AnsiToDosMB(char *str, int flag);
void AnsiToDos(const char *tmp, CString &str, int flag);
void AnsiToDosMB(const char *tmp, CString &str, int flag);
void DosToAnsi(const char *tmp, CString &str);
void DosToAnsiMB(const char *tmp, CString &str);
BYTE * AnsiToDos(BYTE *Arr, int flag, UINT Len);
BYTE * DosToAnsi(BYTE *Arr, UINT Len);
const char *GetFileName(const char *fname);
BOOL TranslLOGFONT(LOGFONT & lftmp, const char *pos);
BOOL TranslLOGFONTtoString(char *pos,LOGFONT & lftmp);
BOOL TranslLOGFONT2(LOGFONT & lftmp, const char *pos);
BOOL TranslTextAlignment(UINT & tmpAlign, char *pos);
void GPSetBrushProperty(LOGBRUSH *lb, const char *iStr);
void GPGetBrushString(LOGBRUSH *lb, char *iStr);
void GPSetBrush(HWND iHWND, CBrush **bru, LOGBRUSH *lb, UINT BkgColor);
void GPSetBrush(HWND iHWND, CBrushExt **bru, LOGBRUSH *lb, UINT BkgColor, const char *iStr);
int StringToClip(const char *str);
void GPRecalcOffsetRect(HWND *Current, HWND *Owner, CRect *Re);
UINT SetObjStlCheck(CCheckListBox *m_ListUnitStl, UINT stl, int nn,const char **lpstl,const UINT *uistl,const UINT *uimask,UINT add = 0);
UINT GetObjStlStr(char *m_StlStr, UINT Stl, int nn,const char **lpstl,const UINT *uistl,const UINT *uimask);
UINT GPRecalcWndRect(CRect *QurentRect, CRect *EtalonRect,CRect *InitialRect, CRect *CompareRect,char *SizingStyle);
UINT ShadowColor(UINT & incolor);
void ReadColor127();
void OptimColor(CDC *dc, UINT & iFRG, UINT & iBKG);
long ConvertToString(const VARIANT FAR* vArray,CString &oStr, CString DelimeterStr);
long ConvertToArray(const CString &iStr, VARIANT FAR* vArray,CString DelimeterStr, DWORD dwArrayType);
long ConvVariantToString( const VARIANT FAR& iArray, CString &Line, const char * DelimeterStr);
long StringToArrayEx(LPCTSTR iString, VARIANT FAR* oArray, const char *strdelim);
long ArrayToStringEx(const VARIANT FAR* vArray,CString &oStr,const char *DelimetersArray);
DWORD StringFromToWindowStyles(const char *iWindowStyles, DWORD & convWindowStyles);
DWORD StringFromToWindowStylesEx(const char *iWindowStylesEx, DWORD & convWindowStylesEx);
int RunExcelMacro(char *name, char *args);
UINT GPExcelMacro(char *iLine);
void qsCharLine(const char **Item, int left, int right);
void qsCharILine(const char **Item, int left, int right);
void qsCharLineAndDWORD(const char **Item, DWORD *dwItem, int left, int right);
void qsCharILineAndDWORD(const char **Item, DWORD *dwItem, int left, int right);
void qsBSTRLine(BSTR *Item, int left, int right);
void qsBSTRILine(BSTR *Item, int left, int right);
void qsVARIANTI(VARIANT *Item, int left, int right);
void qsVARIANT(VARIANT *Item, int left, int right);
int CompareIntASC(const void *arg1, const void *arg2);
int CompareIntDES(const void *arg1, const void *arg2);
void ClearItemsData(CCheckListBox *lb);
void qsRectXByNum(CRect *RectArr,UINT *NUMs, int left, int right);
void qsRectYByNum(CRect *RectArr,UINT *NUMs, int left, int right);
UINT StringToArray(CString &iStr, VARIANT FAR* vArray, CString &DelimeterStr,VARTYPE arrType, UINT type);
int GetInputCodePage();
DWORD FindInSortArrayIC(const char *ccFindWhat, const char **ccArray, DWORD dwItems);
DWORD FindInSortArray(const char *ccFindWhat, const char **ccArray, DWORD dwItems);
char *DwordToStringValue(char cDelim, DWORD dwValue, char *cStr, DWORD *dwArray, const char **ccArray);
char *DwordToStringMask(char cDelim, DWORD dwValue, char *cStr, DWORD *dwArray, const char **ccArray);
DWORD StringToDword(const char *cStr, const char **ccArray, DWORD *dwArray);

////////////////////////////*********************************
DWORD ExportRegistryKey(const char *ccRegKeyName, const char *ccFileName);
DWORD ImportRegistryKey(const char *ccRegKeyName, const char *ccFileName);
char * RemoveCharFromString(char *iStr, char iChar);
char * ReplaceChar(char *Str, char cOld, char cNew);
char * ReplaceChar(char *Str, char cOld, char cNew, char cStop);
long ConvertStringToString(CString &iStr,CString &oStr);//my function
long GetIndexSubString(const CString & iString, const CString & SubString, long Occurence);
long CountOccurence(const CString & iString, const CString & OccurString);
const CString ExtractField(const char * iStr, int FieldNum, const char * delim);
const char *FindField(const char * iStr, int FieldNum, const char * delim);
const char *FindFieldEx(const char * iStr, int FieldNum, const char * delim);
const CString SetMVField(CString & iStr, const char *iNewValue, int FieldNum, int iCharPos, int iStrSubLen, const char * delim);
const CString SetSubField(CString & iStr, const char *iNewValue, int FieldNum,int FieldNum2, int iCharPos, int iStrSubLen, const char * delim, const char * delim2);
PINDEXARR TranslateIndexes(const char *iNewValue, PINDEXARR oResult);
DWORD ExtractScriptPart(const char *iValue, PARGPOSITIONS pPositions);

#define	PICKPROJ_SCHEMA			0x0010
#define	PICKPROJFILE_SCHEMA		0x0010
#define	PICKPROJATTR_SCHEMA		0x0010

#define DWORD_MINUS_ONE			0xFFFFFFFF
#define DWORD_MINUS_TWO			0xFFFFFFFE

extern const char *m_TermVersion;

extern GPFont FontTable,PrintFontTable;
extern int m_LastScanf;
extern GPCurrent GPC;
extern GP_comm m_Comm;
extern CTermCap m_TermCap;

extern const char *hexchars;
extern const DWORD hexValues[];


#define MAX_REGISTERROT 100
extern DWORD m_dwReg[];
extern CString m_dwRegStr[];


//#define WM_USER                         0x0400
// GP_TERM Custom message #define
#define	GPM_NEXTCELL		WM_USER+431
#define	GPM_ESCCELL			WM_USER+432
#define	GPM_DELCELL			WM_USER+433
#define	GPM_UPDATELVEDITOR	WM_USER+434
#define	GPM_GETOBJECTNAME	WM_USER+435
#define	GPM_DOMETHOD		WM_USER+436
#define	GPM_INVALIDATE		WM_USER+437
#define	GPM_UPDATESCROLLER	WM_USER+438

#define	GPN_CLOSEDLGMETHODS	WM_USER+440
#define	GPN_CLOSEDLGPICKSUB	WM_USER+441
#define	GPM_DODLGMETHOD		WM_USER+442
#define	GPM_PROCHOTKEY		WM_USER+443
//#define	GPM_NOTIFYUPDATE	WM_USER+444

#define	GPM_NOTFYTASKBAR	WM_USER+450
#define	GPN_UPDATESIZE		WM_USER+451
#define	GPN_SETENTIRE		WM_USER+452
#define	GPN_DRAWMOVE		WM_USER+453
#define	GPM_NETCRASH		WM_USER+454
#define	GPM_CLIENTKILLFOCUS	WM_USER+455
#define	GPM_CLIENTSETFOCUS	WM_USER+456
#define	GPM_SETAUTOSIZE		WM_USER+457
#define	GPM_SETANDDELETESTRING	WM_USER+458
#define	GPM_SETFOCUSTOWND	WM_USER+459
#define	GPM_MFUPDATEBARS	WM_USER+460
#define	GPM_MFUPDATESIZE	WM_USER+461

// GVP DRAG&DROP
#define	GPM_DRAGMOUSEMOVE	WM_USER+463
#define	GPM_DROPITEMS		WM_USER+464
#define GPM_DRAGMOUSEHOVER	WM_USER+465
#define GPM_DRAGMOUSELEAVE	WM_USER+466

//SeparateView
#define GPM_SWCLOSE			WM_USER+470

//ActiveX in GUI
#define GPM_AX_DOMETHOD			WM_USER+489
#define GPM_AX_FIREEVENT		WM_USER+490
#define GPM_AX_DATAFROMSERVER	WM_USER+491
#define GPM_AX_DATATOSERVER		WM_USER+492
#define GPM_AX_GETMETHODS		WM_USER+493
#define GPM_AX_GETEVENTS		WM_USER+494
#define GPM_AX_ADDEVENT			WM_USER+495
#define GPM_AX_DELEVENT			WM_USER+496
#define GPM_AX_SETREGNAME		WM_USER+497
#define GPM_AX_CHARFROMSERVER	WM_USER+498
#define GPM_AX_DELALLEVENTS		WM_USER+499
#define GPM_AX_SETWINDOWTEXT	WM_USER+500
#define GPM_AX_GETWINDOWTEXT	WM_USER+501
#define GPM_AX_GETWINDOWTEXTEX	WM_USER+502
#define GPM_AX_SETWINDOWTEXTEX	WM_USER+503
#define GPM_AX_SETDIRECTINPUT	WM_USER+504
#define GPM_AX_GETGUIOBJECTSLIST	WM_USER+505
#define GPM_AX_GETVALUE			WM_USER+506
#define GPM_AX_SETVALUE			WM_USER+507


#define AX_FLAG_NORETURNVALUE	0x0001

typedef struct _AX_METHOD
{
	DWORD cbSize;
	BSTR MethodName;
	BSTR Parameters;
	BSTR RetStr;
	DWORD MethodFlags;
	DWORD ErrorNum;
} AX_METHOD, *PAX_METHOD;

typedef struct _AX_NAMES
{
	DWORD cbSize;
	BSTR NamesArr;
	BSTR DescriptionsArr;
} AX_NAMES, *PAX_NAMES;


//SSH Dll
#define WM_SSH_XUSER			(WM_USER + 0x2000)
#define WM_SSH_AGENT_CALLBACK	(WM_SSH_XUSER + 4)
#define WM_SSH_NETEVENT			(WM_SSH_XUSER + 5)
#define WM_SSH_BACKENDEVENT		(WM_SSH_XUSER + 6)


//////////// end GP_TERM Custom message #define

// view mode
#define GPVIEWMODE_TERMINAL		0x00000000
#define GPVIEWMODE_SEPARATE		0x00000001
#define GPVIEWMODE_INFRAME		0x00010000
#define GPVIEWMODE_PLACEMASK	0xFFFF0000
#define GPVIEWMODE_TYPEMASK		0x0000FFFF

// Flash Flags

#define FLASH_ON_FOCUS		0x0001
#define FLASH_ON_FOREGROUND	0x0002

// Define IDs

#define TOOLBAR_ID_START		10000
#define TOOLBAR_ID_COUNT		500
#define TOOLBAR_ID_END			10499

// Define TIMERs

#define CLICK_TIMER_ID			100
#define AUTOCLICK_TIMER_ID		101
#define RAUTOCLICK_TIMER_ID		102
#define CLICK_TIMER_DELAY		1200
#define DRAG_TIMER_ID			103
#define VIRTUAL_LIST_TIMER_ID	104
#define DLGEDITOR_TIMER_ID		105


#define	GP_BKGFILL			1
#define	GP_RECTCLIP			2
#define	GP_RECTFILL			4
#define	GP_LEFT				8
#define	GP_RIGHT			16
#define	GP_CENTER			32
#define	GP_TOP				64
#define	GP_BOTTOM			128
#define	GP_VCENTER			256
#define	GP_BASELINE			512
#define	GP_UPDATECP			1024
#define	GP_END_ELLIPSIS		2048
#define	GP_EXPANDTABS		4096
#define	GP_EXTERNALLEADING	8192
#define	GP_PATH_ELLIPSIS	16364
#define	GP_SINGLELINE		32728
#define	GP_TABSTOP			65536
#define	GP_WORDBREAK	   131072

#define TMP_STR_OUT_LEN 1500000 

#define N_WND_STYLES			22
extern const char *aWndStyleName[];
extern const UINT  aWndStyleUINT[];
extern const UINT  aWndStyleMask[];

#define WS_WINDOWLESS			0xFFFFFFFF

#define N_WND_EX_STYLES			27
extern const char *aWndExStyleName[];
extern const UINT  aWndExStyleUINT[];
extern const UINT  aWndExStyleMask[];

#define N_UNITCOMMON_STYLES			3
extern const char *aUnitCommonStyleName[];
extern const UINT  aUnitCommonStyleUINT[];
extern const UINT  aUnitCommonStyleMask[];

#define	UCS_CRAM		0x0001
#define	UCS_CRVM		0x0002
#define	UCS_CRSVM		0x0004
#define	UCS_CR_MASK		UCS_CRAM|UCS_CRVM|UCS_CRSVM


#define N_WND_SHOW_STYLES		13
extern const char *aWndShowStyleName[];
extern const UINT  aWndShowStyleUINT[];
extern const UINT  aWndShowStyleMask[];

#define N_DLG_STYLES			15
extern const char *aDlgStyleName[];
extern const UINT  aDlgStyleUINT[];
extern const UINT  aDlgStyleMask[];

#define N_COMCTRL_STYLES		8
extern const char *aComCtrlStyleName[];
extern const UINT  aComCtrlStyleUINT[];
extern const UINT  aComCtrlStyleMask[];

#define N_CTRLBAR_STYLES		27
extern const char *aCtrlBarStyleName[];
extern const UINT  aCtrlBarStyleUINT[];
extern const UINT  aCtrlBarStyleMask[];

#define N_DRAWTEXT_FLAGS		24
extern const char *aDrawTextFlagName[];
extern const UINT  aDrawTextFlagUINT[];


#define N_WINDOWPOS_STYLES		15
extern const char *aWindowPosStyleName[];
extern const UINT  aWindowPosStyleUINT[];

#define N_LISTCTRL_STYLES		17
extern const char *aListCtrlStyleName[];
extern const UINT  aListCtrlStyleUINT[];
extern const UINT  aListCtrlStyleMask[];

#define N_LISTCTRL_EX_STYLES	30
extern const char *aListCtrlExStyleName[];
extern const UINT  aListCtrlExStyleUINT[];
extern const UINT  aListCtrlExStyleMask[];

#define N_ANIMATION_STYLES		4
extern const char *aAnimationStyleName[];
extern const UINT  aAnimationStyleUINT[];
extern const UINT  aAnimationStyleMask[];

#define N_PROGRESS_STYLES		4
extern const char *aProgressStyleName[];
extern const UINT  aProgressStyleUINT[];
extern const UINT  aProgressStyleMask[];

#define N_SCROLL_STYLES			10
extern const char *aScrollStyleName[];
extern const UINT  aScrollStyleUINT[];
extern const UINT  aScrollStyleMask[];

#define N_COMBOBOX_STYLES		13
extern const char *aComboBoxStyleName[];
extern const UINT  aComboBoxStyleUINT[];
extern const UINT  aComboBoxStyleMask[];

#define N_COMBOBOXEX_STYLES		13
extern const char *aComboBoxExStyleName[];
extern const UINT  aComboBoxExStyleUINT[];
extern const UINT  aComboBoxExStyleMask[];

#define N_COMBOBOXEX_EX_STYLES		6
extern const char *aComboBoxExExStyleName[];
extern const UINT  aComboBoxExExStyleUINT[];
extern const UINT  aComboBoxExExStyleMask[];

#define N_LISTBOX_STYLES		17
extern const char *aListBoxStyleName[];
extern const UINT  aListBoxStyleUINT[];
extern const UINT  aListBoxStyleMask[];

#define N_BUTTON_STYLES		24
extern const char *aButtonStyleName[];
extern const UINT  aButtonStyleUINT[];
extern const UINT  aButtonStyleMask[];

#define N_EDIT_STYLES		14
extern const char *aEditStyleName[];
extern const UINT  aEditStyleUINT[];
extern const UINT  aEditStyleMask[];

#define N_RTF_STYLES		22
extern const char *aRTFStyleName[];
extern const UINT  aRTFStyleUINT[];
extern const UINT  aRTFStyleMask[];

#define N_RTF_EX_STYLES		1
extern const char *aRTFExStyleName[];
extern const UINT  aRTFExStyleUINT[];
extern const UINT  aRTFExStyleMask[];

#define N_STATIC_STYLES		31
extern const char *aStaticStyleName[];
extern const UINT  aStaticStyleUINT[];
extern const UINT  aStaticStyleMask[];

#define N_DATETIME_STYLES		7
extern const char *aDateTimeStyleName[];
extern const UINT  aDateTimeStyleUINT[];
extern const UINT  aDateTimeStyleMask[];

#define N_MONTHCAL_STYLES		8
extern const char *aMonthCalStyleName[];
extern const UINT  aMonthCalStyleUINT[];
extern const UINT  aMonthCalStyleMask[];

#define N_SPIN_STYLES			9
extern const char *aSpinStyleName[];
extern const UINT  aSpinStyleUINT[];
extern const UINT  aSpinStyleMask[];

#define N_TAB_STYLES			17
extern const char *aTabStyleName[];
extern const UINT  aTabStyleUINT[];
extern const UINT  aTabStyleMask[];

#define N_TAB_EX_STYLES			2
extern const char *aTabExStyleName[];
extern const UINT  aTabExStyleUINT[];
extern const UINT  aTabExStyleMask[];

#define N_SLIDER_STYLES			15
extern const char *aSliderStyleName[];
extern const UINT  aSliderStyleUINT[];
extern const UINT  aSliderStyleMask[];

#define N_HEADER_STYLES			10
extern const char *aHeaderStyleName[];
extern const UINT  aHeaderStyleUINT[];
extern const UINT  aHeaderStyleMask[];

#define N_TREECTRL_STYLES			16
extern const char *aTreeCtrlStyleName[];
extern const UINT  aTreeCtrlStyleUINT[];
extern const UINT  aTreeCtrlStyleMask[];

#define N_TREECTRL_EX_STYLES			10
extern const char *aTreeCtrlExStyleName[];
extern const UINT  aTreeCtrlExStyleUINT[];
extern const UINT  aTreeCtrlExStyleMask[];

#define N_RTF_OPTIONS				9
extern const char *aRTFOptionName[];
extern const UINT  aRTFOptionUINT[];
extern const UINT  aRTFOptionMask[];

#define N_STATUSBARCTRL_STYLES			7
extern const char *aStatusBarCtrlStyleName[];
extern const UINT  aStatusBarCtrlStyleUINT[];
extern const UINT  aStatusBarCtrlStyleMask[];

#define N_STATUSBAR_STYLES			7
extern const char *aStatusBarStyleName[];
extern const UINT  aStatusBarStyleUINT[];
extern const UINT  aStatusBarStyleMask[];

#define N_TOOLBARCTRL_STYLES			17
extern const char *aToolBarCtrlStyleName[];
extern const UINT  aToolBarCtrlStyleUINT[];
extern const UINT  aToolBarCtrlStyleMask[];

#define N_TOOLBARCTRL_EX_STYLES			4
extern const char *aToolBarCtrlExStyleName[];
extern const UINT  aToolBarCtrlExStyleUINT[];
extern const UINT  aToolBarCtrlExStyleMask[];

#define N_REBARCTRL_STYLES			8
extern const char *aReBarCtrlStyleName[];
extern const UINT  aReBarCtrlStyleUINT[];
extern const UINT  aReBarCtrlStyleMask[];

#define N_OLECMDID			52
extern const char *aOLECMDIDName[];
extern const UINT  aOLECMDIDUINT[];


extern char *clfCharSet[];
extern UINT  ulfCharSet[];
extern char *clfOutPrecision[];
extern UINT  ulfOutPrecision[];
extern char *clfClipPrecision[];
extern UINT  ulfClipPrecision[];
extern char *clfQuality[];
extern UINT  ulfQuality[];
extern char *clfPitchAndFamily[];
extern UINT  ulfPitchAndFamily[];

extern const char *cArrBytesName[];

extern const char *aUnitCommonMessages;
extern const char *aUnitMessage[];

extern HANDLE m_WaitAll;


#if(WINVER >= 0x0500)
#define N_WND_MESSAGE		235
#else
#define N_WND_MESSAGE		228
#endif /* WINVER >= 0x0500 */

#define IS_DLG_UNIT			0x10000000

extern const char *ErrObjSub;
extern const char *alpmes[];
extern const UINT  auimes[];
extern const UINT  auimesparam[];
extern BOOL m_StopPaint;
extern BOOL m_StopWorking;
extern CFindReplaceDialog *FRDlg;

#ifdef W_95
#define sizeofMENUITEMINFO sizeof(MENUITEMINFO);
#else
#define sizeofMENUITEMINFO sizeof(MENUITEMINFO);
//-sizeof(HBITMAP);
#endif


typedef struct {  
  WORD      dlgVer; 
  WORD      signature; 
  DWORD     helpID; 
  DWORD     exStyle; 
  DWORD     style; 
  WORD      cDlgItems; 
  short     x; 
  short     y; 
  short     cx; 
  short     cy; 
  short		menu; 
  short		windowClass; 
  WCHAR     title[1]; 
// The following members exist only if the style member is 
// set to DS_SETFONT or DS_SHELLFONT.
  WORD     pointsize; 
  WORD     weight; 
  BYTE     italic;
  BYTE     charset; 
  WCHAR     typeface[32];  
} GPDLGTEMPLATEEX; 

/////////////////////////////////////////////////////////////////////////////
// CGP_TermApp:
// See GP_Term.cpp for the implementation of this class
//

class CGP_TermApp : public CWinApp
{
friend class CGPTInterface;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CGP_TermApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGP_TermApp)
	public:
	virtual BOOL InitInstance();
		virtual int ExitInstance();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CGP_TermApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bATLInited;
private:
	BOOL InitATL();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GP_TERM_H__1509E7AB_DD4C_11D3_970D_0080AD863699__INCLUDED_)
