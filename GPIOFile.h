// GPIOFile.h: interface for the GPIOFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPIOFILE_H__D049FCC9_8876_4B15_926D_9AF4E0FDA309__INCLUDED_)
#define AFX_GPIOFILE_H__D049FCC9_8876_4B15_926D_9AF4E0FDA309__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define FT_NONE			0x00000000
#define FT_COM			0x00000001



#define FT_MESSAGE		0x00010000
#define FT_SENDDATA		0x00020000
#define FT_CONVERT		0x00040000
#define FT_ERRORREPORT	0x00080000

#define FT_DEC			0x00100000
#define FT_HEX			0x00200000
#define FT_OCT			0x00400000
#define FT_SYMBOL		0x00800000
#define FT_DELIMITER	0x01000000

#define FT_DATAMASK		0x00F00000

#include "GPInputPool.h"

typedef struct _GPCOPYINFO
{
	UINT IdCopy;
	DWORD ReturnFlag;
	DWORD dwCopyFlags;
	CString SrcName;
	CString EventType;
	CString DstName;
	CString SubRoutine;
	BOOL bCancel;
	HWND *m_EventsEditor;
	DWORD dwSkip;
	DWORD dwCurEnter;

} GPCOPYINFO, *PGPCOPYINFO;

typedef struct _GPDIRCHANGEINFO
{
	UINT IdCopy;
	CString SrcName;
	CString SubRoutine;
	BOOL bCancel;
	HWND *m_EventsEditor;
	DWORD dwSkip;
	DWORD m_EventsFilter;
	DWORD dwCurEnter;
	HANDLE Handle;

} GPDIRCHANGEINFO, *PGPDIRCHANGEINFO;

UINT ComEventFn(LPVOID pParam);

class GPIOFile  
{
friend UINT ComEventFn(LPVOID pParam);
public:
	void SendCommEvent(DWORD dwEvtMask);
	HWND m_EventsEditor;
	UINT WriteDataByHandle(const char *Str1,const char *Str2);
	UINT GetDataToBuffer(char **cBuffer, UINT uLen);
	void DoRead();
	GPIOFile(const char *iName);
	virtual ~GPIOFile();

	UINT GetType();
	UINT DoMethod(const char *iStr, char **oStr);
	const CString GetName();

	// static members
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];

	const static UINT uNFileType;
	const static char *cArrFileType[];
	const static UINT uArrFileType[];
	const static CString FileTypeToString(UINT iFileType);
	static UINT StringToFileType(const char *iStr);

	const static UINT uNDesAccess;
	const static char *cArrDesAccess[];
	const static UINT uArrDesAccess[];
	const static CString DesAccessToString(UINT iDesAccess);
	static UINT StringToDesAccess(const char *iStr);

	const static UINT uNFShare;
	const static char *cArrFShare[];
	const static UINT uArrFShare[];
	const static CString FShareToString(UINT iFShare);
	static UINT StringToFShare(const char *iStr);

	const static UINT uNCreationDisposition;
	const static char *cArrCreationDisposition[];
	const static UINT uArrCreationDisposition[];
	const static CString CreationDispositionToString(UINT iCreationDisposition);
	static UINT StringToCreationDisposition(const char *iStr);

	const static UINT uNFlagsAndAttributes;
	const static char *cArrFlagsAndAttributes[];
	const static UINT uArrFlagsAndAttributes[];
	const static CString FlagsAndAttributesToString(UINT iFlagsAndAttributes);
	static UINT StringToFlagsAndAttributes(const char *iStr);
	const static CString FileAttributesToString(UINT iAttributes);

	const static UINT uNIOStyle;
	const static char *cArrIOStyle[];
	const static UINT uArrIOStyle[];
	const static CString IOStyleToString(UINT iIOStyle);
	static UINT StringToIOStyle(const char *iStr);
	
	const static UINT uNCError;
	const static char *cArrCError[];
	const static UINT uArrCError[];
	const static CString CErrorToString(UINT iCError);
	static UINT StringToCError(const char *iStr);

	const static UINT uNCEvents;
	const static char *cArrCEvents[];
	const static UINT uArrCEvents[];
	const static CString CEventsToString(UINT iCEvents);
	static UINT StringToCEvents(const char *iStr);

	const static UINT uNCMStatus;
	const static char *cArrCMStatus[];
	const static UINT uArrCMStatus[];
	const static CString CMStatusToString(UINT iCMStatus);
	static UINT StringToCMStatus(const char *iStr);

	const static UINT uNBAUD;
	const static char *cArrBAUD[];
	const static UINT uArrBAUD[];
	const static CString BAUDToString(UINT iBAUD);
	static UINT StringToBAUD(const char *iStr);

	const static UINT uNProvSubType;
	const static char *cArrProvSubType[];
	const static UINT uArrProvSubType[];
	const static CString ProvSubTypeToString(UINT iProvSubType);
	static UINT StringToProvSubType(const char *iStr);

	const static UINT uNProvCap;
	const static char *cArrProvCap[];
	const static UINT uArrProvCap[];
	const static CString ProvCapToString(UINT iProvCap);
	static UINT StringToProvCap(const char *iStr);

	const static UINT uNSettableParams;
	const static char *cArrSettableParams[];
	const static UINT uArrSettableParams[];
	const static CString SettableParamsToString(UINT iSettableParams);
	static UINT StringToSettableParams(const char *iStr);

	const static UINT uNSettableData;
	const static char *cArrSettableData[];
	const static UINT uArrSettableData[];
	const static CString SettableDataToString(UINT iSettableData);
	static UINT StringToSettableData(const char *iStr);
	
	const static UINT uNSettableStopParity;
	const static char *cArrSettableStopParity[];
	const static UINT uArrSettableStopParity[];
	const static CString SettableStopParityToString(UINT iSettableStopParity);
	static UINT StringToSettableStopParity(const char *iStr);

	const static UINT uNFAction;
	const static char *cArrFAction[];
	const static UINT uArrFAction[];
	const static CString FActionToString(UINT iFAction);
	static UINT StringToFAction(const char *iStr);

	const static UINT uNFileEncryptStatus;
	const static char *cArrFileEncryptStatus[];
	const static UINT uArrFileEncryptStatus[];
	const static CString FileEncryptStatusToString(UINT iFileEncryptStatus);
	static UINT StringToFileEncryptStatus(const char *iStr);

	const static UINT uNFBinaryType;
	const static char *cArrFBinaryType[];
	const static UINT uArrFBinaryType[];
	const static CString FBinaryTypeToString(UINT iFBinaryType);
	static UINT StringToFBinaryType(const char *iStr);

	const static UINT uNFMoveFlag;
	const static char *cArrFMoveFlag[];
	const static UINT uArrFMoveFlag[];
	const static CString FMoveFlagToString(UINT iFMoveFlag);
	static UINT StringToFMoveFlag(const char *iStr);

	const static UINT uNDriveType;
	const static char *cArrDriveType[];
	const static UINT uArrDriveType[];
	const static CString DriveTypeToString(UINT iDriveType);
	static UINT StringToDriveType(const char *iStr);
	
	const static UINT uNDeviceFlag;
	const static char *cArrDeviceFlag[];
	const static UINT uArrDeviceFlag[];
	const static CString DeviceFlagToString(UINT iDeviceFlag);
	static UINT StringToDeviceFlag(const char *iStr);

	const static UINT uNFileNotifChange;
	const static char *cArrFileNotifChange[];
	const static UINT uArrFileNotifChange[];
	const static CString FileNotifChangeToString(UINT iFileNotifChange);
	static UINT StringToFileNotifChange(const char *iStr);
	
	/*
	const static UINT uNxxxx;
	const static char *cArrxxxx[];
	const static UINT uArrxxxx[];
	const static CString xxxxToString(UINT ixxxx);
	static UINT StringToxxxx(const char *iStr);
	*/

	const static CString FA_DATAToString(WIN32_FILE_ATTRIBUTE_DATA & iFA_DATA);
	const static CString FF_DATAToString(WIN32_FIND_DATA & iFF_DATA);

private:
	void StopComEvents();
	UINT m_IOFileStop;
	UINT m_IOFileEventsStopped;
	CWinThread* m_EventThread;
	OVERLAPPED ovr;
	OVERLAPPED ovw;
	OVERLAPPED ove;
	HANDLE m_HANDLE;
	CGPInputPool m_Pool;
	CString m_csFileName;
	CString m_csName;
	CString m_csSubName;
	UINT m_Type;
	UINT m_Style;
	DCB dcb;
	COMMTIMEOUTS cto;
	CRITICAL_SECTION m_CSEditor;
};

#endif // !defined(AFX_GPIOFILE_H__D049FCC9_8876_4B15_926D_9AF4E0FDA309__INCLUDED_)
