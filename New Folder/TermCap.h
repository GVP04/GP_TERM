// TermCap.h: interface for the CTermCap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TERMCAP_H__8AF6DFC8_3158_4EE4_8279_465EF4CFF4D8__INCLUDED_)
#define AFX_TERMCAP_H__8AF6DFC8_3158_4EE4_8279_465EF4CFF4D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TERMCAP_ESCPOOLLENGTH		1024
#define TERMCAP_SEQLENGTH			16
#define TERMCAP_MASKFLAGENABLE	0x0001

#define TCET_BYTE	0
#define TCET_DIGIT	1
#define TCET_MOD256MINUSSP	2
#define TCET_MOD256	3
#define TCET_MOD90MINUSSP	4
#define TCET_MOD256MINUS1	5
#define TCET_MOD256MINUS31	6
#define TCET_HEXDIGIT	7

#define TCEST_IDWND		'W'
#define TCEST_IDSCR		'S'
#define TCEST_OBJTYPE	'T'
#define TCEST_Y			'Y'
#define TCEST_Y2		'y'
#define TCEST_X			'X'
#define TCEST_X2		'x'
#define TCEST_LENGTH	'L'
#define TCEST_COLOR		'C'
#define TCEST_COLOR_R	'R'
#define TCEST_COLOR_G	'G'
#define TCEST_COLOR_B	'B'

#define TCKA_NONE		0x00
#define TCKA_UP			0x01
#define TCKA_DOWN		0x02
#define TCKA_LEFT		0x04
#define TCKA_RIGHT		0x08
#define TCKA_DELETE		0x10
#define TCKA_BACKSPACE	0x20


typedef struct _TERMCAPITEMSEQ
{
	DWORD dwSeqLen;
	unsigned char ch[TERMCAP_SEQLENGTH];
	unsigned char chType[TERMCAP_SEQLENGTH];
} TERMCAPITEMSEQ, *PTERMCAPITEMSEQ;

typedef struct _TERMCAPESCITEM
{
	DWORD dwTermId;
	DWORD dwFlags;
	DWORD dwSearchFlags;
	DWORD dwCommand;
	CString TermcapName;
	CString Description;
	CString GroupName;
	TERMCAPITEMSEQ seq;
} TERMCAPESCITEM, *PTERMCAPESCITEM;

typedef struct _TERMCAPKBDITEM
{
	DWORD dwTermId;
	DWORD dwFlags;
	CString csAction;
	DWORD dwVirtualKey;
	CString Description;
	CString Seq;
} TERMCAPKBDITEM, *PTERMCAPKBDITEM;

typedef struct _TERMCAPESCVARS
{
	DWORD IdWnd;
	DWORD IdScr;
	DWORD typeUnit;
	int Length;
	int Pos_Y;
	int Pos_Y2;
	int Pos_X;
	int Pos_X2;
	int R;
	int G;
	int B;
	COLORREF ClrRef;
	int Unknown;
} TERMCAPESCVARS, *PTERMCAPESCVARS;

typedef struct _TERMCAPTERMINALITEM
{
	DWORD dwTermId;
	DWORD dwFlags;
	CString TerminalName;
	CString AlternateNames;
	CString Description;
} TERMCAPTERMINALITEM, *PTERMCAPTERMINALITEM;

class CTermCap  
{
	friend class CDlgTermcapKbd;
	friend class CDlgTermcapEsc;
	friend class CDlgTermcapEscLine;
	friend class CDlgTermcapTerminal;
	friend class CDlgTermcap;
	friend class GPDlgCommtype;
	friend class CGP_TermView;
	friend class CDldTermcapVideo;

public:
	DWORD SetAVArray(DWORD *idwArrai, DWORD dwItemsCount);
	DWORD GetVAttrTable(DWORD **pdwArr);
	DWORD LoadTermCapVAttr(const char *iName);
	DWORD SaveTermCapVAttr(const char *iName);
	const DWORD *GetVAttrByCmdId(DWORD cmdID);

	const PTERMCAPESCITEM GetEscItemById(DWORD dwID, DWORD dwTermID);
	const char *GetTerminalNameById(DWORD dwId);
	UINT GetTerminalIdByName(const char *iName);
	virtual DWORD SelectTerminal(int x, int y);
	TERMCAPESCVARS m_Vars;
	DWORD FillComboTerminalType(HWND ihWnd, DWORD iSelId  = -1);
	int FindEscSequense();
	int AddByteToEscPool(BYTE iByte);
	int AddArrayToEscPool(const BYTE *iByte, DWORD iLen);
	void ClearEscPool();
	UINT GetEscPoolLen();
	const char * GetEscPool();
	PTERMCAPESCITEM TranslateFoundEsc();
	PTERMCAPESCITEM GetFoundEsc();

	const static UINT uNEscTypes;
	const static char *cArrEscTypes[];
	const static char *cArrEscTypesDescr[];
	const static DWORD uEscTypes[];

	const static UINT uNEscSubTypes;
	const static char *cArrEscSubTypes[];
	const static char *cArrEscSubTypesDescr[];
	const static DWORD uEscSubTypes[];

	const static UINT uNKbdActions;
	const static char *cArrKbdActions[];
	const static char *cArrKbdActionsDescr[];
	const static DWORD uKbdActions[];

	static int CompareEscSeq(const PTERMCAPITEMSEQ s1, const PTERMCAPITEMSEQ s2);
	UINT NormaliseKbd();
	UINT NormaliseEsc();
	UINT CopyKbd(DWORD SrcTermId, DWORD DstTermId);
	DWORD GetVacTerminalId();
	virtual BOOL DeleteTerminal(DWORD dwTermId);
	BOOL GetFileName(CString &iInitDir, CString &iFileName, DWORD iFlags, HWND iHWNDPARENT);
	virtual BOOL ChangeTerminalId(DWORD iOldId,DWORD iNewId);
	CTermCap & operator= (const CTermCap &iCTermCap);

	DWORD GetCurrentTerminalId();
	DWORD SetCurrentTerminalId(DWORD dwNewId);
	PTERMCAPTERMINALITEM GetCurrentTerminal();

	void ResetEscArray();
	void ResetKbdArray();
	void ResetTerminalArray();

	virtual UINT DeleteEscItems(TERMCAPESCITEM & iTem);
	virtual UINT DeleteEscItem(PTERMCAPESCITEM iItem);

	virtual UINT DeleteKbdItems(TERMCAPKBDITEM & iTem);
	virtual UINT DeleteKbdItem(PTERMCAPKBDITEM iItem);

	virtual UINT DeleteTerminalItems(TERMCAPTERMINALITEM & iTem);
	virtual UINT DeleteTerminalItem(PTERMCAPTERMINALITEM iItem);

	virtual void ClearEscItem(TERMCAPESCITEM & iTem);
	virtual void ClearKbdItem(TERMCAPKBDITEM & iTem);
	virtual void ClearTerminalItem(TERMCAPTERMINALITEM & iTem);

	UINT GetEscCount();
	UINT GetKbdCount();
	UINT GetTerminalCount();

	virtual PTERMCAPESCITEM AddEscItem();
	virtual PTERMCAPKBDITEM AddKbdItem();
	virtual PTERMCAPTERMINALITEM AddTerminalItem();

	static const char *TCFileName;

	virtual BOOL Save(const char *fName);
	virtual DWORD Load(const char *fName);

	CTermCap();
	virtual ~CTermCap();

private:
	UINT m_dwFindPos;
	UINT m_EscPoolLength;
	void ClearVars();
	char EscPool[TERMCAP_ESCPOOLLENGTH];
	virtual UINT DeleteTerminalItemByNum(DWORD iItem);
	virtual UINT DeleteKbdItemByNum(DWORD iItem);
	virtual UINT DeleteEscItemByNum(DWORD iItem);
	DWORD GetTerminalNumById(DWORD dwId);
	PTERMCAPTERMINALITEM CurrentTerminal;
	PTERMCAPESCITEM FoundEsc;
	TERMCAPESCITEM **m_ArrEsc;
	TERMCAPKBDITEM **m_ArrKbd;
	TERMCAPTERMINALITEM **m_ArrTerminal;
	void DeleteEscArray();
	UINT m_uMaxEscArr;
	UINT m_uArrEscCount;
	void DeleteKbdArray();
	UINT m_uMaxKbdArr;
	UINT m_uArrKbdCount;
	void DeleteTerminalArray();
	UINT m_uMaxTerminalArr;
	UINT m_uArrTerminalCount;
	DWORD *pdwVattrArray;
	DWORD dwVattrArrayCount;
	DWORD dwVattrArrayMax;
};

#endif // !defined(AFX_TERMCAP_H__8AF6DFC8_3158_4EE4_8279_465EF4CFF4D8__INCLUDED_)
