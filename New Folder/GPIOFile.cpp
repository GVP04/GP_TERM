// GPIOFile.cpp: implementation of the GPIOFile class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "GPIOFile.h"
#include "GP_term.h"
#include "GP_TermView.h"
#include "GP_TermDoc.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const UINT GPIOFile::uNMethods=58;
const char *GPIOFile::cArrMethods[]={
/*00*/	"GetType","OpenComFile","CloseHandle","SetStyle","GetStyle",
/*05*/	"SetSubName","GetSubName","Read","Write","WriteStr",
/*10*/	"WriteChar","ReadStr","ReadChar","WriteBlock","ReadBlock",
/*15*/	"SetDCB","GetDCB","SetCommState","PurgeComm","FlushFileBuffers",
/*20*/	"ClearCommBreak","BuildCommDCB","BuildCommTimeouts","SetTimeouts","GetTimeouts",
/*25*/	"ClearCommError","CommConfigDialog","GetCommConfig","EscapeCommFunction","GetCommMask",
/*30*/	"SetCommMask","GetCommModemStatus","GetCommProperties","GetCommState","GetDefaultCommConfig",
/*35*/	"SetCommBreak","SetCommConfig","SetDefaultCommConfig","SetupComm","TransmitCommChar",
/*40*/	"SetErrorMode","CancelIo","GetFileInformation","LockFile","GetFileSizeEx",
/*45*/	"GetFileType","UnlockFile","SetFileValidData","SetFileShortName","SetEndOfFile",
/*50*/	"SetFilePointer","ReadDirectoryChanges","SetBookMark","DeleteBookMark","GetCRC16",
/*55*/	"MoveBookMark","ClearReadBuffer","GetArrCRC16","","",
/*60*/	"","","","","",
/*65*/	"","","","","",
/*70*/	"","","","","",
	};

const char *GPIOFile::cArrMethodsParams[]={
/*00*/	"","ComName, param","","Style","",
/*05*/	"SubName","","nBytes","Data[char(1)Descr]","String",
/*10*/	"CharCode[,Count]","nStr","","ChCode^ChCode^...","nByte",
/*15*/	"DCBPAR1=;DCBPAR2=;......","","","Flag","",
/*20*/	"","DCBString","","[RInterval,RMultiplier,RConstant,WMultiplier,WConstant]","",
/*25*/	"","[FileName]","[FileName]","EscFunction","",
/*30*/	"Mask","","","","",
/*35*/	"ComConfigStr","ComConfig","[FileName],ComConfig","dwInQueue,dwOutQueue","CharCode[,Count]",
/*40*/	"ErrorMode","","","FileOffset,NumberOfBytes","",
/*45*/	"","FileOffset,NumberOfBytes","FileValidDataLen","FileShortName","",
/*50*/	"Position,BEGIN or CURRENT or END","nFiles,bSubDir,FILE_NAME|DIR_NAME|ATTRIBUTES|SIZE|WRITE|ACCESS|CREATION|SECURITY","","","start,Length[,PrevSumm[,CRCType]]",
/*55*/	"uDeltaPlus","","CRCType,PrevSumm,DataType,DataArr","","",
/*60*/	"","","","","",
/*65*/	"","","","","",
/*70*/	"","","","","",
	};

const UINT GPIOFile::uNFileType=2;
const char *GPIOFile::cArrFileType[2]={
	"FT_NONE","FT_COM",/*"","","",*/
	};
const UINT GPIOFile::uArrFileType[2]={
	FT_NONE,FT_COM,
	};


const UINT GPIOFile::uNDesAccess=17;
const char *GPIOFile::cArrDesAccess[]={
	"DELETE","READ_CONTROL","WRITE_DAC","WRITE_OWNER","SYNCHRONIZE",
	"STANDARD_RIGHTS_REQUIRED","STANDARD_RIGHTS_READ","STANDARD_RIGHTS_WRITE","STANDARD_RIGHTS_EXECUTE","STANDARD_RIGHTS_ALL",
	"SPECIFIC_RIGHTS_ALL","ACCESS_SYSTEM_SECURITY","MAXIMUM_ALLOWED","GENERIC_READ","GENERIC_WRITE",
	"GENERIC_EXECUTE","GENERIC_ALL",
	"",
	};
const UINT GPIOFile::uArrDesAccess[]={
	DELETE,READ_CONTROL,WRITE_DAC,WRITE_OWNER,SYNCHRONIZE,
	STANDARD_RIGHTS_REQUIRED,STANDARD_RIGHTS_READ,STANDARD_RIGHTS_WRITE,STANDARD_RIGHTS_EXECUTE,STANDARD_RIGHTS_ALL,
	SPECIFIC_RIGHTS_ALL,ACCESS_SYSTEM_SECURITY,MAXIMUM_ALLOWED,GENERIC_READ,GENERIC_WRITE,
	GENERIC_EXECUTE,GENERIC_ALL,
	STANDARD_RIGHTS_ALL,
	};



const UINT GPIOFile::uNFShare=3;
const char *GPIOFile::cArrFShare[3]={
	"FILE_SHARE_READ","FILE_SHARE_WRITE","FILE_SHARE_DELETE",
	};
const UINT GPIOFile::uArrFShare[3]={
	FILE_SHARE_READ,FILE_SHARE_WRITE,FILE_SHARE_DELETE,
	};

const UINT GPIOFile::uNCreationDisposition=5;
const char *GPIOFile::cArrCreationDisposition[5]={
	"CREATE_NEW","CREATE_ALWAYS","OPEN_EXISTING","OPEN_ALWAYS","TRUNCATE_EXISTING",
	};
const UINT GPIOFile::uArrCreationDisposition[5]={
	CREATE_NEW,CREATE_ALWAYS,OPEN_EXISTING,OPEN_ALWAYS,TRUNCATE_EXISTING,
	};

const UINT GPIOFile::uNFlagsAndAttributes=60;
const char *GPIOFile::cArrFlagsAndAttributes[60]={
	"FILE_ATTRIBUTE_READONLY","FILE_ATTRIBUTE_DIRECTORY","FILE_ATTRIBUTE_SYSTEM","FILE_ATTRIBUTE_HIDDEN","FILE_ATTRIBUTE_ARCHIVE",
	"FILE_ATTRIBUTE_VIRTUAL","FILE_ATTRIBUTE_DEVICE","FILE_ATTRIBUTE_NORMAL","FILE_ATTRIBUTE_TEMPORARY","FILE_ATTRIBUTE_SPARSE_FILE",
	"FILE_ATTRIBUTE_REPARSE_POINT","FILE_ATTRIBUTE_COMPRESSED","FILE_ATTRIBUTE_OFFLINE","FILE_ATTRIBUTE_NOT_CONTENT_INDEXED","FILE_ATTRIBUTE_ENCRYPTED",
	"FA_READONLY","FA_DIRECTORY","FA_SYSTEM","FA_HIDDEN","FA_ARCHIVE",
	"FA_ARCHIVE","FA_DEVICE","FA_NORMAL","FA_TEMPORARY","FA_SPARSE_FILE",
	"FA_REPARSE_POINT","FA_COMPRESSED","FA_OFFLINE","FA_NOT_CONTENT_INDEXED","FA_ENCRYPTED",
	"FILE_FLAG_WRITE_THROUGH","FILE_FLAG_OVERLAPPED","FILE_FLAG_NO_BUFFERING","FILE_FLAG_RANDOM_ACCESS","FILE_FLAG_SEQUENTIAL_SCAN",
	"FILE_FLAG_DELETE_ON_CLOSE","FILE_FLAG_BACKUP_SEMANTICS","FILE_FLAG_POSIX_SEMANTICS","FILE_FLAG_OPEN_REPARSE_POINT","FILE_FLAG_OPEN_NO_RECALL",
	"FF_WRITE_THROUGH","FF_OVERLAPPED","FF_NO_BUFFERING","FF_RANDOM_ACCESS","FF_SEQUENTIAL_SCAN",
	"FF_DELETE_ON_CLOSE","FF_BACKUP_SEMANTICS","FF_POSIX_SEMANTICS","FF_OPEN_REPARSE_POINT","FF_OPEN_NO_RECALL",
	"FILE_FLAG_FIRST_PIPE_INSTANCE","FF_FIRST_PIPE_INSTANCE","SECURITY_ANONYMOUS","SECURITY_IDENTIFICATION","SECURITY_IMPERSONATION",
	"SECURITY_DELEGATION","SECURITY_CONTEXT_TRACKING","SECURITY_EFFECTIVE_ONLY","SECURITY_SQOS_PRESENT","SECURITY_VALID_SQOS_FLAGS",
	};

#define FILE_ATTRIBUTE_READONLY             0x00000001  
#define FILE_ATTRIBUTE_HIDDEN               0x00000002  
#define FILE_ATTRIBUTE_SYSTEM               0x00000004  
#define FILE_ATTRIBUTE_DIRECTORY            0x00000010  
#define FILE_ATTRIBUTE_ARCHIVE              0x00000020  
#define FILE_ATTRIBUTE_DEVICE               0x00000040  
#define FILE_ATTRIBUTE_NORMAL               0x00000080  
#define FILE_ATTRIBUTE_TEMPORARY            0x00000100  
#define FILE_ATTRIBUTE_SPARSE_FILE          0x00000200  
#define FILE_ATTRIBUTE_REPARSE_POINT        0x00000400  
#define FILE_ATTRIBUTE_COMPRESSED           0x00000800  
#define FILE_ATTRIBUTE_OFFLINE              0x00001000  
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED  0x00002000  
#define FILE_ATTRIBUTE_ENCRYPTED            0x00004000  
#define FILE_ATTRIBUTE_VIRTUAL              0x00010000  


const UINT GPIOFile::uArrFlagsAndAttributes[60]={
	FILE_ATTRIBUTE_READONLY,FILE_ATTRIBUTE_DIRECTORY,FILE_ATTRIBUTE_SYSTEM,FILE_ATTRIBUTE_HIDDEN,FILE_ATTRIBUTE_ARCHIVE,
	FILE_ATTRIBUTE_VIRTUAL,FILE_ATTRIBUTE_DEVICE,FILE_ATTRIBUTE_NORMAL,FILE_ATTRIBUTE_TEMPORARY,FILE_ATTRIBUTE_SPARSE_FILE,
	FILE_ATTRIBUTE_REPARSE_POINT,FILE_ATTRIBUTE_COMPRESSED,FILE_ATTRIBUTE_OFFLINE,FILE_ATTRIBUTE_NOT_CONTENT_INDEXED,FILE_ATTRIBUTE_ENCRYPTED,
	FILE_ATTRIBUTE_READONLY,FILE_ATTRIBUTE_DIRECTORY,FILE_ATTRIBUTE_SYSTEM,FILE_ATTRIBUTE_HIDDEN,FILE_ATTRIBUTE_ARCHIVE,
	FILE_ATTRIBUTE_VIRTUAL,FILE_ATTRIBUTE_DEVICE,FILE_ATTRIBUTE_NORMAL,FILE_ATTRIBUTE_TEMPORARY,FILE_ATTRIBUTE_SPARSE_FILE,
	FILE_ATTRIBUTE_REPARSE_POINT,FILE_ATTRIBUTE_COMPRESSED,FILE_ATTRIBUTE_OFFLINE,FILE_ATTRIBUTE_NOT_CONTENT_INDEXED,FILE_ATTRIBUTE_ENCRYPTED,
	FILE_FLAG_WRITE_THROUGH,FILE_FLAG_OVERLAPPED,FILE_FLAG_NO_BUFFERING,FILE_FLAG_RANDOM_ACCESS,FILE_FLAG_SEQUENTIAL_SCAN,
	FILE_FLAG_DELETE_ON_CLOSE,FILE_FLAG_BACKUP_SEMANTICS,FILE_FLAG_POSIX_SEMANTICS,FILE_FLAG_OPEN_REPARSE_POINT,FILE_FLAG_OPEN_NO_RECALL,
	FILE_FLAG_WRITE_THROUGH,FILE_FLAG_OVERLAPPED,FILE_FLAG_NO_BUFFERING,FILE_FLAG_RANDOM_ACCESS,FILE_FLAG_SEQUENTIAL_SCAN,
	FILE_FLAG_DELETE_ON_CLOSE,FILE_FLAG_BACKUP_SEMANTICS,FILE_FLAG_POSIX_SEMANTICS,FILE_FLAG_OPEN_REPARSE_POINT,FILE_FLAG_OPEN_NO_RECALL,
	FILE_FLAG_FIRST_PIPE_INSTANCE,FILE_FLAG_FIRST_PIPE_INSTANCE,SECURITY_ANONYMOUS,SECURITY_IDENTIFICATION,SECURITY_IMPERSONATION,
	SECURITY_DELEGATION,SECURITY_CONTEXT_TRACKING,SECURITY_EFFECTIVE_ONLY,SECURITY_SQOS_PRESENT,SECURITY_VALID_SQOS_FLAGS,
	};


const UINT GPIOFile::uNIOStyle=9;
const char *GPIOFile::cArrIOStyle[9]={
	"FT_MESSAGE","FT_SENDDATA","FT_CONVERT","FT_ERRORREPORT","FT_DEC",
	"FT_HEX","FT_OCT","FT_SYMBOL","FT_DELIMITER",
	};
const UINT GPIOFile::uArrIOStyle[9]={
	FT_MESSAGE,FT_SENDDATA,FT_CONVERT,FT_ERRORREPORT,FT_DEC,
	FT_HEX,FT_OCT,FT_SYMBOL,FT_DELIMITER,
	};

const UINT GPIOFile::uNCError=11;
const char *GPIOFile::cArrCError[15]={
	"CE_BREAK","CE_DNS","CE_FRAME","CE_IOE","CE_MODE",
	"CE_OOP","CE_OVERRUN","CE_PTO","CE_RXOVER","CE_RXPARITY",
	"CE_TXFULL","","","","",
	};
const UINT GPIOFile::uArrCError[11]={
	CE_BREAK,CE_DNS,CE_FRAME,CE_IOE,CE_MODE,
	CE_OOP,CE_OVERRUN,CE_PTO,CE_RXOVER,CE_RXPARITY,
	CE_TXFULL,
	};

// CE_BREAK|CE_DNS|CE_FRAME|CE_IOE|CE_MODE|CE_OOP|CE_OVERRUN|CE_PTO|CE_RXOVER|CE_RXPARITY|CE_TXFULL

const UINT GPIOFile::uNCEvents=13;
const char *GPIOFile::cArrCEvents[13]={
	"EV_RXCHAR","EV_RXFLAG","EV_TXEMPTY","EV_CTS","EV_DSR",
	"EV_RLSD","EV_BREAK","EV_ERR","EV_RING","EV_PERR",
	"EV_RX80FULL","EV_EVENT1","EV_EVENT2",
	};
const UINT GPIOFile::uArrCEvents[13]={
	EV_RXCHAR,EV_RXFLAG,EV_TXEMPTY,EV_CTS,EV_DSR,
	EV_RLSD,EV_BREAK,EV_ERR,EV_RING,EV_PERR,
	EV_RX80FULL,EV_EVENT1,EV_EVENT2,
	};
//EV_RXCHAR|EV_RXFLAG|EV_TXEMPTY|EV_CTS|EV_DSR|EV_RLSD|EV_BREAK|EV_ERR|EV_RING|EV_PERR|EV_RX80FULL|EV_EVENT1|EV_EVENT2

const UINT GPIOFile::uNCMStatus=4;
const char *GPIOFile::cArrCMStatus[4]={
	"MS_CTS_ON","MS_DSR_ON","MS_RING_ON","MS_RLSD_ON",
	};
const UINT GPIOFile::uArrCMStatus[4]={
	MS_CTS_ON,MS_DSR_ON,MS_RING_ON,MS_RLSD_ON,
	};

const UINT GPIOFile::uNBAUD=20;
const char *GPIOFile::cArrBAUD[20]={
	"BAUD_075","BAUD_110","BAUD_134_5","BAUD_150","BAUD_300",
	"BAUD_600","BAUD_1200","BAUD_1800","BAUD_2400","BAUD_4800",
	"BAUD_7200","BAUD_9600","BAUD_14400","BAUD_19200","BAUD_38400",
	"BAUD_56K","BAUD_128K","BAUD_115200","BAUD_57600","BAUD_USER",
	};
const UINT GPIOFile::uArrBAUD[20]={
	BAUD_075,BAUD_110,BAUD_134_5,BAUD_150,BAUD_300,
	BAUD_600,BAUD_1200,BAUD_1800,BAUD_2400,BAUD_4800,
	BAUD_7200,BAUD_9600,BAUD_14400,BAUD_19200,BAUD_38400,
	BAUD_56K,BAUD_128K,BAUD_115200,BAUD_57600,BAUD_USER,
	};

const UINT GPIOFile::uNProvSubType=13;
const char *GPIOFile::cArrProvSubType[13]={
	"PST_UNSPECIFIED","PST_RS232","PST_PARALLELPORT","PST_RS422","PST_RS423",
	"PST_RS449","PST_MODEM","PST_FAX","PST_SCANNER","PST_NETWORK_BRIDGE",
	"PST_LAT","PST_TCPIP_TELNET","PST_X25",
	};
const UINT GPIOFile::uArrProvSubType[13]={
	PST_UNSPECIFIED,PST_RS232,PST_PARALLELPORT,PST_RS422,PST_RS423,
	PST_RS449,PST_MODEM,PST_FAX,PST_SCANNER,PST_NETWORK_BRIDGE,
	PST_LAT,PST_TCPIP_TELNET,PST_X25,
	};

const UINT GPIOFile::uNProvCap=10;
const char *GPIOFile::cArrProvCap[10]={
	"PCF_DTRDSR","PCF_RTSCTS","PCF_RLSD","PCF_PARITY_CHECK","PCF_XONXOFF",
	"PCF_SETXCHAR","PCF_TOTALTIMEOUTS","PCF_INTTIMEOUTS","PCF_SPECIALCHARS","PCF_16BITMODE",
	};
const UINT GPIOFile::uArrProvCap[10]={
	PCF_DTRDSR,PCF_RTSCTS,PCF_RLSD,PCF_PARITY_CHECK,PCF_XONXOFF,
	PCF_SETXCHAR,PCF_TOTALTIMEOUTS,PCF_INTTIMEOUTS,PCF_SPECIALCHARS,PCF_16BITMODE,
	};

const UINT GPIOFile::uNSettableParams=8;
const char *GPIOFile::cArrSettableParams[8]={
	"SP_PARITY","SP_BAUD","SP_DATABITS","SP_STOPBITS","SP_STOPBITS",
	"SP_HANDSHAKING","SP_PARITY_CHECK","SP_RLSD",
	};
const UINT GPIOFile::uArrSettableParams[8]={
	SP_PARITY,SP_BAUD,SP_DATABITS,SP_STOPBITS,SP_STOPBITS,
	SP_HANDSHAKING,SP_PARITY_CHECK,SP_RLSD,
	};

const UINT GPIOFile::uNSettableData=6;
const char *GPIOFile::cArrSettableData[6]={
	"DATABITS_5","DATABITS_6","DATABITS_7","DATABITS_8","DATABITS_16",
	"DATABITS_16X",
	};
const UINT GPIOFile::uArrSettableData[6]={
	DATABITS_5,DATABITS_6,DATABITS_7,DATABITS_8,DATABITS_16,
	DATABITS_16X,
	};

const UINT GPIOFile::uNSettableStopParity=8;
const char *GPIOFile::cArrSettableStopParity[8]={
	"STOPBITS_10","STOPBITS_15","STOPBITS_20","PARITY_NONE","PARITY_ODD",
	"PARITY_EVEN","PARITY_MARK","PARITY_SPACE",
	};
const UINT GPIOFile::uArrSettableStopParity[8]={
	STOPBITS_10,STOPBITS_15,STOPBITS_20,PARITY_NONE,PARITY_ODD,
	PARITY_EVEN,PARITY_MARK,PARITY_SPACE,
	};

const UINT GPIOFile::uNFAction=5;
const char *GPIOFile::cArrFAction[5]={
	"FILE_ACTION_ADDED","FILE_ACTION_REMOVED","FILE_ACTION_MODIFIED","FILE_ACTION_RENAMED_OLD_NAME","FILE_ACTION_RENAMED_NEW_NAME",
	};
const UINT GPIOFile::uArrFAction[5]={
	FILE_ACTION_ADDED,FILE_ACTION_REMOVED,FILE_ACTION_MODIFIED,FILE_ACTION_RENAMED_OLD_NAME,FILE_ACTION_RENAMED_NEW_NAME,
	};

const UINT GPIOFile::uNFileEncryptStatus=10;
const char *GPIOFile::cArrFileEncryptStatus[]={
	"FILE_ENCRYPTABLE","FILE_IS_ENCRYPTED","FILE_SYSTEM_ATTR","FILE_ROOT_DIR","FILE_SYSTEM_DIR",
	"FILE_UNKNOWN","FILE_SYSTEM_NOT_SUPPORT","FILE_USER_DISALLOWED","FILE_READ_ONLY","FILE_DIR_DISALLOWED",
	};
const UINT GPIOFile::uArrFileEncryptStatus[]={
	FILE_ENCRYPTABLE,FILE_IS_ENCRYPTED,FILE_SYSTEM_ATTR,FILE_ROOT_DIR,FILE_SYSTEM_DIR,
	FILE_UNKNOWN,FILE_SYSTEM_NOT_SUPPORT,FILE_USER_DISALLOWED,FILE_READ_ONLY,FILE_DIR_DISALLOWED,
	};

const UINT GPIOFile::uNFBinaryType=7;
const char *GPIOFile::cArrFBinaryType[]={
	"SCS_32BIT_BINARY","SCS_DOS_BINARY","SCS_WOW_BINARY","SCS_PIF_BINARY","SCS_POSIX_BINARY",
	"SCS_OS216_BINARY","SCS_64BIT_BINARY",
	};
const UINT GPIOFile::uArrFBinaryType[]={
	SCS_32BIT_BINARY,SCS_DOS_BINARY,SCS_WOW_BINARY,SCS_PIF_BINARY,SCS_POSIX_BINARY,
	SCS_OS216_BINARY,SCS_64BIT_BINARY,
	};

const UINT GPIOFile::uNFMoveFlag=6;
const char *GPIOFile::cArrFMoveFlag[6]={
	"REPLACE_EXISTING","COPY_ALLOWED","DELAY_UNTIL_REBOOT","WRITE_THROUGH","CREATE_HARDLINK",
	"FAIL_IF_NOT_TRACKABLE",
	};
const UINT GPIOFile::uArrFMoveFlag[6]={
	MOVEFILE_REPLACE_EXISTING,MOVEFILE_COPY_ALLOWED,MOVEFILE_DELAY_UNTIL_REBOOT,MOVEFILE_WRITE_THROUGH,MOVEFILE_CREATE_HARDLINK,
	MOVEFILE_FAIL_IF_NOT_TRACKABLE,
	};

const UINT GPIOFile::uNDriveType=7;
const char *GPIOFile::cArrDriveType[7]={
	"DRIVE_UNKNOWN","DRIVE_NO_ROOT_DIR","DRIVE_REMOVABLE","DRIVE_FIXED","DRIVE_REMOTE",
	"DRIVE_CDROM","DRIVE_RAMDISK",
	};
const UINT GPIOFile::uArrDriveType[7]={
	DRIVE_UNKNOWN,DRIVE_NO_ROOT_DIR,DRIVE_REMOVABLE,DRIVE_FIXED,DRIVE_REMOTE,
	DRIVE_CDROM,DRIVE_RAMDISK,
	};

const UINT GPIOFile::uNDeviceFlag=5;
const char *GPIOFile::cArrDeviceFlag[5]={
	"DDD_RAW_TARGET_PATH","DDD_REMOVE_DEFINITION","DDD_EXACT_MATCH_ON_REMOVE","DDD_NO_BROADCAST_SYSTEM","DDD_LUID_BROADCAST_DRIVE",
	};
const UINT GPIOFile::uArrDeviceFlag[5]={
	DDD_RAW_TARGET_PATH,DDD_REMOVE_DEFINITION,DDD_EXACT_MATCH_ON_REMOVE,DDD_NO_BROADCAST_SYSTEM,DDD_LUID_BROADCAST_DRIVE,
	};

const UINT GPIOFile::uNFileNotifChange=8;
const char *GPIOFile::cArrFileNotifChange[8]={
	"FNC_FILE_NAME","FNC_DIR_NAME","FNC_ATTRIBUTES","FNC_SIZE","FNC_LAST_WRITE",
	"FNC_LAST_ACCESS","FNC_CREATION","FNC_SECURITY",
	};
const UINT GPIOFile::uArrFileNotifChange[8]={
	FILE_NOTIFY_CHANGE_FILE_NAME,FILE_NOTIFY_CHANGE_DIR_NAME,FILE_NOTIFY_CHANGE_ATTRIBUTES,FILE_NOTIFY_CHANGE_SIZE,FILE_NOTIFY_CHANGE_LAST_WRITE,
	FILE_NOTIFY_CHANGE_CREATION,FILE_NOTIFY_CHANGE_LAST_ACCESS,FILE_NOTIFY_CHANGE_SECURITY,
	};


/*
const UINT GPIOFile::uNxxxx=;
const char *GPIOFile::cArrxxxx[]={
	"","","","","",
	};
const UINT GPIOFile::uArrxxxx[]={
	,,,,,
	};
*/

VOID CALLBACK mDeleteFunc(
  HWND hwnd,        // handle to destination window
  UINT uMsg,        // message
  ULONG_PTR dwData, // application-defined value
  LRESULT lResult   // result of message processing
)
{
	if (dwData) 
		delete[] (char *)dwData;

}


void GPIOFile::SendCommEvent(DWORD dwEvtMask)
{
	EnterCriticalSection(&GPC.m_View->m_CSRemap);
	EnterCriticalSection(&m_CSEditor);
	try
	{
		UINT i;
		for(i=0;i<GPIOFile::uNCEvents;i++)
			if ((dwEvtMask&GPIOFile::uArrCEvents[i])==GPIOFile::uArrCEvents[i])
			{
				char ms[100];
				sprintf(ms,"%c%c%d%c%s%c%s%c%s%c%s\r",
					250,
					250,
					54,0xFE,
					"EVENT",0xFE,
					(LPCSTR)m_csSubName,0xFE,
					(LPCSTR)m_csName,0xFE,
					GPIOFile::cArrCEvents[i]);
				if (m_EventsEditor && ::IsWindow(m_EventsEditor)) 
				{
					char *CallbackStr=new char [200];
					strcpy(CallbackStr,ms);
					::PostMessage(m_EventsEditor,GPM_SETANDDELETESTRING,(WPARAM)CallbackStr,(LPARAM)CallbackStr);
					::PostMessage(m_EventsEditor,GPM_SETANDDELETESTRING,0,(LPARAM)"\r\n");
				}
				m_Comm.GPSendSafeBlock(ms,(int)strlen(ms));
			}
	}catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPIOFile", "SendCommEvent","");
	}
	LeaveCriticalSection(&m_CSEditor);
	LeaveCriticalSection(&GPC.m_View->m_CSRemap);
}

UINT ComEventFn(LPVOID pParam)
{
	GPIOFile *GPIOF=(GPIOFile *)pParam;
	HANDLE m_WaitIOFileEvent;
	m_WaitIOFileEvent=CreateEvent(NULL, TRUE, TRUE, "m_WaitIOFileEvent");
	GPIOF->m_IOFileEventsStopped=0;

	do
	{
		try
		{
			if (GPIOF->m_HANDLE && GPIOF->m_HANDLE!=INVALID_HANDLE_VALUE)
				switch(GPIOF->m_Type)
				{
				case FT_COM:
					{
						DWORD dwEvtMask=0;
						if (WaitCommEvent(GPIOF->m_HANDLE, &dwEvtMask, &GPIOF->ove)) 
							GPIOF->SendCommEvent(dwEvtMask);
						else
						{
							if (GetLastError()==ERROR_IO_PENDING)
							{
								UINT i=0;
								DWORD WaitResult=0;

								while((WaitResult=WaitForSingleObject(GPIOF->ove.hEvent,50))==WAIT_TIMEOUT && !m_StopWorking && !GPIOF->m_IOFileStop)
								{
									i++;
								}

								if (WaitResult!=WAIT_TIMEOUT)
									GPIOF->SendCommEvent(dwEvtMask);
							}
						}
					}
					break;
				default:
					break;
				}

			ResetEvent(m_WaitIOFileEvent);
			WaitForSingleObject(m_WaitIOFileEvent,25);

		}catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("GLOBAL GPIOFile", "ComEventFn","");
		}
	}
	while(!m_StopWorking && !GPIOF->m_IOFileStop);

	GPIOF->m_IOFileStop=0;
	GPIOF->m_IOFileEventsStopped=1;

	if (m_WaitIOFileEvent) CloseHandle(m_WaitIOFileEvent);
	m_WaitIOFileEvent=NULL;

	return 0;
}


GPIOFile::GPIOFile(const char *iName)
{
	InitializeCriticalSection(&m_CSEditor);
	m_EventsEditor=NULL;
	m_Style=m_Type=0;
	m_csName=iName;
	m_HANDLE=NULL;
	m_csSubName="";
	m_csFileName="";
	m_EventThread=NULL;
	m_IOFileStop=0;
	m_IOFileEventsStopped=1;

	FillMemory(&dcb,sizeof(dcb),0);

	dcb.DCBlength=sizeof(dcb);
	dcb.BaudRate		= 115200;
	dcb.ByteSize		= 8;
	dcb.EofChar			= 0;
	dcb.ErrorChar		= 32;
	dcb.EvtChar			= 0;
	dcb.fAbortOnError	= 0;
	dcb.fBinary			= 1;
	dcb.fDsrSensitivity = 0;
	dcb.fDtrControl		= DTR_CONTROL_DISABLE;
	dcb.fDummy2			= 0;
	dcb.fErrorChar		= 0;
	dcb.fInX			= 0;
	dcb.fNull			= 0;
	dcb.fOutX			= 0;
	dcb.fOutxCtsFlow	= 0;
	dcb.fOutxDsrFlow	= 0;
	dcb.fRtsControl		= RTS_CONTROL_DISABLE;
	dcb.fTXContinueOnXoff = 0;
	dcb.Parity			= NOPARITY;
	dcb.fParity			= 0;
	dcb.StopBits		= ONESTOPBIT;
	dcb.wReserved1		= 0;
	dcb.XoffChar		= 14;
	dcb.XoffLim			= 1024;
	dcb.XonChar			= 15;
	dcb.XonLim			= 1024;
//    WORD wReserved;       /* Not currently used              */
	cto.ReadIntervalTimeout=123456789;

	FillMemory(&ovr,sizeof(ovr),0);
	FillMemory(&ovw,sizeof(ovw),0);
	FillMemory(&ove,sizeof(ove),0);

	ovr.hEvent=CreateEvent(
    NULL,   // no security attributes 
    TRUE,  // auto reset event 
    FALSE,  // not signaled 
    NULL    // no name 
    );
	ovw.hEvent=CreateEvent(
    NULL,   // no security attributes 
    TRUE,  // auto reset event 
    FALSE,  // not signaled 
    NULL    // no name 
    );
	ove.hEvent=CreateEvent(
    NULL,   // no security attributes 
    TRUE,  // auto reset event 
    FALSE,  // not signaled 
    NULL    // no name 
    );
}

GPIOFile::~GPIOFile()
{
	StopComEvents();

	if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
		DoMethod("CloseHandle",NULL);
	m_HANDLE=NULL;

	if (ovr.hEvent)
		CloseHandle(ovr.hEvent);
	ovr.hEvent=NULL;

	if (ovw.hEvent)
		CloseHandle(ovw.hEvent);
	ovw.hEvent=NULL;

	if (ove.hEvent)
		CloseHandle(ove.hEvent);
	ove.hEvent=NULL;

	DeleteCriticalSection(&m_CSEditor);
}

const CString GPIOFile::GetName()
{
	return m_csName;
}

UINT GPIOFile::GetType()
{
	return m_Type;
}

UINT GPIOFile::DoMethod(const char *iStr, char **oStr)
{
	char met[150];
	CString smallStr="";
	strncpy(met,iStr,145);
	met[145]=0;
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc=0;

	int retint=-123456; 
	int atoipos=atoi(pos);
	
	if (*met>='0' && *met<='9') nfunc=atoi(met);
	else
	{
		static const char *sccArrMethods[sizeof(cArrMethods)/sizeof(char *)];
		static DWORD scdMethodsId[sizeof(cArrMethods)/sizeof(char *)];
		if (!*sccArrMethods)
		{
			DWORD i;
			for(i=0;i<uNMethods;i++)
			{
				sccArrMethods[i]=cArrMethods[i];
				scdMethodsId[i]=i;
			}
			qsCharILineAndDWORD(sccArrMethods, scdMethodsId, 0, uNMethods-1);
			scdMethodsId[i]=i;
		}
		nfunc=scdMethodsId[FindInSortArrayIC(met, sccArrMethods, uNMethods)];
	}
try
{
	switch(nfunc)
	{
	case 0: /*GetType*/		smallStr=FileTypeToString(GetType());		break;
	case 1: /*OpenComFile ComName, param*/
		{
			if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE) DoMethod("CloseHandle",NULL);

			char *FileName=new char [(int)strlen(pos)+10];
			strcpy(FileName,pos);
			char *posparam=strchr(FileName,',');
			if (posparam) *(posparam++)=0;
			else			posparam="";
			DWORD dwDesiredAccess=StringToDesAccess(posparam);	// access mode
			DWORD dwShareMode=StringToFShare(posparam);			// share mode
			SECURITY_ATTRIBUTES SecurityAttributes={0};		// SD
			SecurityAttributes.nLength=sizeof(SecurityAttributes);
			// Set NULL
			DWORD dwCreationDisposition=OPEN_EXISTING;			// how to create

			DWORD dwFlagsAndAttributes=StringToFlagsAndAttributes(posparam);	// file attributes

			m_csFileName=FileName;
			m_HANDLE=CreateFile(FileName, dwDesiredAccess, dwShareMode, NULL, dwCreationDisposition, dwFlagsAndAttributes|FILE_FLAG_OVERLAPPED, NULL);


			if (m_HANDLE==INVALID_HANDLE_VALUE || m_HANDLE==NULL)
			{
				m_HANDLE=NULL;
				GetLastError();
				smallStr.Format("-1%c%d",0xFE,GetLastError());
			}
			else
			{
				m_Type=FT_COM;
				retint=SetCommState(m_HANDLE,&dcb);
				COMSTAT cs;
				DWORD ner;
				ClearCommError(m_HANDLE,&ner,&cs);

				retint=(int)m_HANDLE;
				if (cto.ReadIntervalTimeout==123456789)
					GetCommTimeouts(m_HANDLE,&cto);

				StopComEvents();
				m_EventThread=AfxBeginThread(ComEventFn,(LPVOID)this);
			}

			delete[] FileName;
		}
		break;
	case 2: /*CloseHandle*/
		StopComEvents();
		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
		{
			if (CloseHandle(m_HANDLE))
			{
				retint=1;
				m_Type=0;
			}
			else
				smallStr.Format("-1%c%d",0xFE,GetLastError());
		}
		m_HANDLE=NULL;
		break;
	case 3: /*SetStyle*/
		smallStr=IOStyleToString(m_Style);
		m_Style=StringToIOStyle(pos);
		break;
	case 4: /*GetStyle*/
		smallStr=IOStyleToString(m_Style);
		break;
	case 5: /*SetSubName*/
		smallStr=m_csSubName;
		m_csSubName=pos;
		break;
	case 6: /*GetSubName*/
		smallStr=m_csSubName;
		break;
	case 7: /*Read*/
		if (atoipos!=0)
			if (oStr)
				GetDataToBuffer(oStr,atoipos);
			else
			{
				char *tmps;
				GetDataToBuffer(&tmps,atoipos);
				if (tmps) delete[] tmps;
			}
		break;
	case 8: /*Write*/
		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
		{
			const char *pos2=strchr(pos,1);
			if (pos2++==NULL) pos2="";
			retint=WriteDataByHandle(ExtractField(pos,1,","),pos2);
		}
		break;
	case 9: /*WriteStr*/
		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
		{
			DWORD realWrite=0; 
			retint = WriteFile(m_HANDLE,pos,(int)strlen(pos),&realWrite,&ovw);
			WriteFile(m_HANDLE,"\r",1,&realWrite,&ovw);
		}
		break;
	case 10: /*WriteChar code,count*/
	case 38: /*TransmitCommChar code,count*/

		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
		{
			int count=1,code=0;
			m_LastScanf=sscanf(pos,"%d,%d",&code,&count);
			DWORD realWrite=0; 
			char tmp[20];
			*tmp=(char)atoipos;
			if (nfunc==10)
			{
				while(count-->0)
					WriteFile(m_HANDLE,(LPCVOID)tmp,1,&realWrite,&ovw);
			}
			else
			{
				while(count-->0)
					TransmitCommChar(m_HANDLE,tmp[0]);
			}
		}
		break;
	case 11: /*ReadStr*/
		{
			if (atoipos<=0) atoipos=1;
			int nStr=atoipos;

			while(atoipos-->0)
			{
				char *tmps=NULL;
				int nRead=m_Pool.GetString(&tmps);

				if (nRead==123456789)
				{
					if (nStr==1 || atoipos==nStr-1)	smallStr="-1";
					else
						if (oStr)
						{
							*oStr=new char [10+smallStr.GetLength()]; 
							sprintf(*oStr,"%d%c",nStr-atoipos-1,0xFE);
							strcat(*oStr,smallStr);
						}
					atoipos=0;
				}
				else
					if (tmps)
					{
						tmps[nRead]=0;
						if ((m_Style&FT_CONVERT)==FT_CONVERT)
							AnsiToDos((BYTE *)tmps,0,nRead);
						if (atoipos<nStr-1) smallStr+="\xFE";
						smallStr+=tmps;
					}
				if (tmps) delete[] tmps;
			}
		}
		break;
	case 12: /*ReadChar*/
		{
			BYTE oByte=0;
			if (m_Pool.GetByte(&oByte)) retint=oByte;
		}
		break;
	case 13: /*WriteBlock ChCode^ChCode^...*/
		{
			const char *pos2=pos;
			UINT nBytes=0;
			while(pos2++ && *pos2)
				if ((pos2=strchr(pos2,GPC.DelimiterIn1))) nBytes++;

			if (nBytes)
			{
				BYTE *arr=new BYTE [nBytes+10];
				BYTE *arrpos=arr;
				pos2=pos;
				while(pos2 && *pos2)
				{
					*(arrpos++)=(char)atoi(pos2);
					if ((pos2=strchr(pos2,GPC.DelimiterIn1))) pos2++;
				}
				DWORD realWrite;
				WriteFile(m_HANDLE,(LPCVOID)arr,nBytes,&realWrite,&ovw);
				delete[] arr;
			}
		}
		break;
	case 14: /*ReadBlock nByte*/
		{
			BYTE *Arr=NULL;
			UINT nRead=m_Pool.GetData(&Arr,atoipos);
			if (nRead && oStr)
			{
				*oStr=new char [nRead*4+2];
				char *tmp=*oStr;
				if ((m_Style&FT_CONVERT)==FT_CONVERT)	AnsiToDos(Arr,0,nRead);
				UINT i;
				for(i=0;i<nRead;i++)
					tmp+=sprintf(tmp,"%d%c",Arr[i],0xFE);
			}
			if (Arr) delete[] Arr;
		}
		break;
	case 15: /*SetDCB*/
		retint=-1;
		{
			char *tmps= new char [(int)strlen(pos)+10];
			strcpy(tmps,pos);
			_strupr(tmps);
			char *fnd;
			if ((fnd=strstr(tmps,"BAUDRATE=")))			dcb.BaudRate	=atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"FBINARY=")))			dcb.fBinary		=atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"FPARITY=")))			dcb.fParity		=atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"FOUTXCTSFLOW=")))		dcb.fOutxCtsFlow=atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"FOUTXDSRFLOW=")))		dcb.fOutxDsrFlow=atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"FERRORCHAR=")))		dcb.fErrorChar	=atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"FDTRCONTROL=")))		dcb.fDtrControl	=atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"FDSRSENSITIVITY=")))	dcb.fDsrSensitivity=atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"FTXCONTINUEONXOFF="))) dcb.fTXContinueOnXoff=atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"FOUTX=")))			dcb.fOutX		=atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"FINX=")))				dcb.fInX		=atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"FNULL=")))			dcb.fNull		=atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"FRTSCONTROL=")))		dcb.fRtsControl	=atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"FABORTONERROR=")))	dcb.fAbortOnError=atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"FDUMMY2=")))			dcb.fDummy2		=atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"WRESERVED1=")))		dcb.wReserved1	=(char)atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"XONLIM=")))			dcb.XonLim		=(char)atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"XOFFLIM=")))			dcb.XoffLim		=(char)atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"BYTESIZE=")))			dcb.ByteSize	=(char)atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"PARITY=")))			dcb.Parity		=(char)atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"STOPBITS=")))			dcb.StopBits	=(char)atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"XONCHAR=")))			dcb.XonChar		=(char)atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"XOFFCHAR=")))			dcb.XoffChar	=(char)atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"ERRORCHAR=")))		dcb.ErrorChar	=(char)atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"EOFCHAR=")))			dcb.EofChar		=(char)atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"EVTCHAR=")))			dcb.EvtChar		=(char)atoi(strchr(fnd,'=')+1);
			delete[] tmps;
			if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
				retint=SetCommState(m_HANDLE,&dcb);
		}
		break;
	case 16: /*GetDCB*/
	case 33: /*GetCommState*/
		retint=-1;
		{
			DCB dcbtmp=dcb;
			if (nfunc==33 && m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE) GetCommState(m_HANDLE,&dcbtmp);
			smallStr.Format(
				"BaudRate@ByteSize@EofChar@ErrorChar@EvtChar@fAbortOnError@fBinary@fDsrSensitivity@fDtrControl@fDummy2@fErrorChar@fInX@fNull@fOutX@fOutxCtsFlow@fOutxDsrFlow@fRtsControl@fTXContinueOnXoff@Parity@fParity@StopBits@wReserved1@XoffChar@XoffLim@XonChar@XonLim%c%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d",
				0xFE,
				dcbtmp.BaudRate,	dcbtmp.ByteSize,		dcbtmp.EofChar,	dcbtmp.ErrorChar,
				dcbtmp.EvtChar,	dcbtmp.fAbortOnError,	dcbtmp.fBinary,	dcbtmp.fDsrSensitivity,
				dcbtmp.fDtrControl,dcbtmp.fDummy2,		dcbtmp.fErrorChar,	dcbtmp.fInX,
				dcbtmp.fNull,		dcbtmp.fOutX,			dcbtmp.fOutxCtsFlow,dcbtmp.fOutxDsrFlow,
				dcbtmp.fRtsControl,dcbtmp.fTXContinueOnXoff,dcbtmp.Parity,	dcbtmp.fParity,
				dcbtmp.StopBits,	dcbtmp.wReserved1,		dcbtmp.XoffChar,	dcbtmp.XoffLim,
				dcbtmp.XonChar,	dcbtmp.XonLim);
			smallStr.Replace('@',0xFD);
		}
		break;
	case 17: /*SetCommState*/
		retint=-1;
		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
			retint=SetCommState(m_HANDLE,&dcb);
		break;
	case 18: /*PurgeComm*/
		retint=-1;
		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
		{
			char *tmps= new char [(int)strlen(pos)+10];
			strcpy(tmps,pos);
			_strupr(tmps);
			char *fnd;
			DWORD flag=0;

			if ((fnd=strstr(tmps,"TXABORT")))	flag|=PURGE_TXABORT;
			if ((fnd=strstr(tmps,"RXABORT")))	flag|=PURGE_RXABORT;
			if ((fnd=strstr(tmps,"TXCLEAR")))	flag|=PURGE_TXCLEAR;
			if ((fnd=strstr(tmps,"RXCLEAR")))	flag|=PURGE_RXCLEAR;
			retint=PurgeComm(m_HANDLE,flag);
		}
		break;
	case 19: /*FlushFileBuffers*/
		retint=-1;
		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
			retint=FlushFileBuffers(m_HANDLE);
		break;
	case 20: /*ClearCommBreak*/
		retint=-1;
		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
			retint=ClearCommBreak(m_HANDLE);
		break;
	case 21: /*BuildCommDCB*/
		retint=BuildCommDCB(pos,&dcb);
		break;
	case 22: /*BuildCommTimeouts*/
		{
			DCB tmpd={0};
			retint=BuildCommDCBAndTimeouts(pos,&tmpd,&cto);
		}
		break;
	case 23: /*SetTimeouts*/
		retint=-1;
		{
			if (*pos)
				m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d",
					&cto.ReadIntervalTimeout,
					&cto.ReadTotalTimeoutMultiplier,
					&cto.ReadTotalTimeoutConstant,
					&cto.WriteTotalTimeoutMultiplier,
					&cto.WriteTotalTimeoutConstant);
			if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE && cto.ReadIntervalTimeout!=123456789)
				retint=SetCommTimeouts(m_HANDLE,&cto);
		}
		break;
	case 24: /*GetTimeouts*/
		retint=-1;
		if (cto.ReadIntervalTimeout==123456789 && m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
			GetCommTimeouts(m_HANDLE,&cto);
		smallStr.Format("%d%c%d%c%d%c%d%c%d",
			cto.ReadIntervalTimeout,0xFE,
			cto.ReadTotalTimeoutMultiplier,0xFE,
			cto.ReadTotalTimeoutConstant,0xFE,
			cto.WriteTotalTimeoutMultiplier,0xFE,
			cto.WriteTotalTimeoutConstant);
		break;
	case 25: /*ClearCommError*/
		retint=-1;
		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
		{
			COMSTAT stat={0};
			DWORD nerr=0;
			ClearCommError(m_HANDLE,&nerr,&stat);
			smallStr.Format("%d%c%s%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d",
				nerr,0xFE,
				(LPCSTR)CErrorToString(nerr),0xFE,
				stat.fCtsHold,0xFE,
				stat.fDsrHold,0xFE,
				stat.fRlsdHold,0xFE,
				stat.fXoffHold,0xFE,
				stat.fXoffSent,0xFE,
				stat.fEof,0xFE,
				stat.fTxim,0xFE,
				stat.fReserved,0xFE,
				m_Pool.GetReadLength(),0xFE,
				stat.cbOutQue);
		}
		break;
	case 26: /*CommConfigDialog*/
	case 27: /*GetCommConfig*/
	case 34: /*GetDefaultCommConfig*/
		{
			CString tmpname=m_csFileName;
			if (*pos) tmpname=pos;
			COMMCONFIG CC={0};
			DWORD sz=CC.dwSize=sizeof(CC);
			CC.dcb=dcb;
			if (
				nfunc==26?CommConfigDialog(tmpname,GPC.m_hViewWnd,&CC)
				:nfunc==34?GetDefaultCommConfig(tmpname,&CC,&sz)
				:m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE?GetCommConfig(m_HANDLE,&CC,&sz):FALSE)
			{
				smallStr.Format(
					"%d#%d#%d#%d#BaudRate@ByteSize@EofChar@ErrorChar@EvtChar@fAbortOnError@fBinary@fDsrSensitivity@fDtrControl@fDummy2@fErrorChar@fInX@fNull@fOutX@fOutxCtsFlow@fOutxDsrFlow@fRtsControl@fTXContinueOnXoff@Parity@fParity@StopBits@wReserved1@XoffChar@XoffLim@XonChar@XonLim%c%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d@%d",
					CC.wVersion,CC.dwProviderSubType,CC.dwProviderOffset,CC.dwProviderSize,
					0xFE,
					dcb.BaudRate,	dcb.ByteSize,		dcb.EofChar,	dcb.ErrorChar,
					dcb.EvtChar,	dcb.fAbortOnError,	dcb.fBinary,	dcb.fDsrSensitivity,
					dcb.fDtrControl,dcb.fDummy2,		dcb.fErrorChar,	dcb.fInX,
					dcb.fNull,		dcb.fOutX,			dcb.fOutxCtsFlow,dcb.fOutxDsrFlow,
					dcb.fRtsControl,dcb.fTXContinueOnXoff,dcb.Parity,	dcb.fParity,
					dcb.StopBits,	dcb.wReserved1,		dcb.XoffChar,	dcb.XoffLim,
					dcb.XonChar,	dcb.XonLim);
				smallStr.Replace('@',0xFD);
				smallStr.Replace('#',0xFE);
			}
			else smallStr=nfunc==27?"CANCEL":"ERROR";
		}
		break;
	case 28: /*EscapeCommFunction*/
		retint=-1;
		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
		{
			DWORD FunctionN=atoipos;
			DWORD uarr[]={SETXOFF,SETXON,SETRTS,CLRRTS,SETDTR,CLRDTR,RESETDEV,SETBREAK,CLRBREAK,};
			char *carr[]={"SETXOFF","SETXON","SETRTS","CLRRTS","SETDTR","CLRDTR","RESETDEV","SETBREAK","CLRBREAK",};
			UINT i;
			for(i=0;i<9 && _stricmp(pos,carr[i])!=0;i++);

			if (i<9) FunctionN=uarr[i];

			retint=EscapeCommFunction(m_HANDLE,FunctionN);
		}
		break;
	case 29: /*GetCommMask*/
		retint=-1;
		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
		{
			DWORD EM=0;
			GetCommMask(m_HANDLE,&EM);
			smallStr=CEventsToString(EM);
		}
		break;
	case 30: /*SetCommMask*/
		retint=-1;
		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
			retint=SetCommMask(m_HANDLE,StringToCEvents(pos));
		break;
	case 31: /*GetCommModemStatus*/
		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
		{
			DWORD MS=0;
			if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)	GetCommModemStatus(m_HANDLE,&MS);
			smallStr=CMStatusToString(MS);
		}
		break;
	case 32: /*GetCommProperties*/
		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
		{
			CString tmpname=m_csFileName;
			if (*pos) tmpname=pos;
			COMMPROP CP={0};
			if (GetCommProperties(m_HANDLE,&CP))
			{
				smallStr.Format("PacketLength@PacketVersion@ServiceMask@Reserved1@MaxTxQueue@MaxRxQueue@MaxBaud@ProvSubType@ProvCapabilities@SettableParams@SettableBaud@SettableData@SettableStopParity@CurrentTxQueue@CurrentRxQueue@ProvSpec1@ProvSpec2@ProvChar@#%d@%d@%d@%d@%d@%d@%s@%s@%s@%s@%s@%s@%s@%d@%d@%d@%d@%d",
						CP.wPacketLength,
						CP.wPacketVersion,
						CP.dwServiceMask,
						CP.dwReserved1,
						CP.dwMaxTxQueue,
						CP.dwMaxRxQueue,
						(LPCSTR)BAUDToString(CP.dwMaxBaud),
						(LPCSTR)ProvSubTypeToString(CP.dwProvSubType),
						(LPCSTR)ProvCapToString(CP.dwProvCapabilities),
						(LPCSTR)SettableParamsToString(CP.dwSettableParams),
						(LPCSTR)BAUDToString(CP.dwSettableBaud),
						(LPCSTR)SettableDataToString(CP.wSettableData),
						(LPCSTR)SettableStopParityToString(CP.wSettableStopParity),
						CP.dwCurrentTxQueue,
						CP.dwCurrentRxQueue,
						CP.dwProvSpec1,
						CP.dwProvSpec2,
						CP.wcProvChar
						);
						//	PST_MODEM	MODEMDEVCAPS
				smallStr.Replace('@',0xFD);
				smallStr.Replace('#',0xFE);
			}
		}
		break;
	case 35: /*SetCommBreak*/
		retint=-1;
		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
			retint=SetCommBreak(m_HANDLE);
		break;
	case 36: /*SetCommConfig*/
	case 37: /*SetDefaultCommConfig*/
		retint=-1;
		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
		{
			DCB tmpdcb=dcb;
			COMMCONFIG CC;
			CC.dwSize=sizeof(CC);
			CString nm="SetDCB ";
			nm+=pos;
			DoMethod(nm,NULL);
			CC.dcb=dcb;
			dcb=tmpdcb;
			if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
				retint=SetCommState(m_HANDLE,&dcb);

			CC.wVersion=0;
			CC.wcProviderData[0]=0;
			CC.dwProviderSubType=0;
			CC.dwProviderSize=0;
			CC.dwProviderOffset=0;

			char *tmps= new char [(int)strlen(pos)+10];
			strcpy(tmps,pos);
			_strupr(tmps);
			char *fnd;
			if ((fnd=strstr(tmps,"VERSION=")))			CC.wVersion			=(unsigned short)atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"PROVIDERDATA=")))		CC.wcProviderData[0]=(unsigned short)atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"PROVIDERSUBTYPE=")))	CC.dwProviderSubType=atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"PROVIDERSIZE=")))		CC.dwProviderSize	=atoi(strchr(fnd,'=')+1);
			if ((fnd=strstr(tmps,"PROVIDEROFFSET=")))	CC.dwProviderOffset	=atoi(strchr(fnd,'=')+1);
			delete[] tmps;
			if (nfunc==37)
			{
				nm=ExtractField(pos,1,",");
				if (nm.GetLength()>15) nm=m_csFileName;
				SetDefaultCommConfig((LPCSTR)nm,&CC,CC.dwSize);
			}
			else 
			if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
				retint=SetCommConfig(m_HANDLE,&CC,CC.dwSize);
		}
		break;
	case 39: /*SetupComm*/
		retint=-1;
		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
		{
			DWORD dwInQueue=1000;  // size of input buffer
			DWORD dwOutQueue=1000;  // size of output buffer
			m_LastScanf=sscanf(pos,"%d,%d",&dwInQueue,&dwOutQueue);
			retint=SetupComm(m_HANDLE,dwInQueue,dwOutQueue);
		}
		break;
	case 40: /*SetErrorMode*/
		{
			char *typeName[]={
				"SEM_FAILCRITICALERRORS","SEM_NOALIGNMENTFAULTEXCEPT","SEM_NOGPFAULTERRORBOX","SEM_NOOPENFILEERRORBOX",
			};
			UINT typeFlag[]={
				SEM_FAILCRITICALERRORS,SEM_NOALIGNMENTFAULTEXCEPT,SEM_NOGPFAULTERRORBOX,SEM_NOOPENFILEERRORBOX,
			};
			UINT type=0;
			if (*pos)
			{
				if (*pos>='0' && *pos<='9') type=atoipos;
				else
				{
					UINT i;
					for(i=0;i<4 && type==0;i++)
						if (_stricmp(pos,typeName[i])==0) type=typeFlag[i];
				}
			}
			retint=SetErrorMode(type);
		}
		break;
	#ifdef W_95
	#else
		case 41: /*CancelIo*/
			retint=-1;
			if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
				retint=CancelIo(m_HANDLE);
			break;
	#endif
	case 42: /*GetFileInformation*/
		retint=-1;
		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
		{
			BY_HANDLE_FILE_INFORMATION bhi={0};
			SYSTEMTIME CreationTime={0}; 
			SYSTEMTIME LastAccessTime={0}; 
			SYSTEMTIME LastWriteTime={0}; 
			retint=GetFileInformationByHandle(m_HANDLE,&bhi);
			FileTimeToSystemTime(&(bhi.ftCreationTime),&CreationTime);
			FileTimeToSystemTime(&(bhi.ftLastAccessTime),&LastAccessTime);
			FileTimeToSystemTime(&(bhi.ftLastWriteTime),&LastWriteTime);

			__int64 i64Size=0;

			i64Size=bhi.nFileSizeHigh;
			i64Size<<=32;
			i64Size+=bhi.nFileSizeLow;

			__int64 i64ID=0;

			i64ID=bhi.nFileSizeHigh;
			i64ID<<=32;
			i64ID+=bhi.nFileSizeLow;

			smallStr.Format("%d%c%s%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%I64d%c%d%c%I64d",
				retint,0xFE,
				(LPCSTR)FileAttributesToString(bhi.dwFileAttributes),0xFE,
				CreationTime.wYear,0xFD,CreationTime.wMonth,0xFD,CreationTime.wDay,0xFD,CreationTime.wHour,0xFD,CreationTime.wMinute,0xFD,CreationTime.wSecond,0xFD,CreationTime.wMilliseconds,0xFE,
				LastAccessTime.wYear,0xFD,LastAccessTime.wMonth,0xFD,LastAccessTime.wDay,0xFD,LastAccessTime.wHour,0xFD,LastAccessTime.wMinute,0xFD,LastAccessTime.wSecond,0xFD,LastAccessTime.wMilliseconds,0xFE,
				LastWriteTime.wYear,0xFD,LastWriteTime.wMonth,0xFD,LastWriteTime.wDay,0xFD,LastWriteTime.wHour,0xFD,LastWriteTime.wMinute,0xFD,LastWriteTime.wSecond,0xFD,LastWriteTime.wMilliseconds,0xFE,
				bhi.dwVolumeSerialNumber,0xFE,
				i64Size,0xFE,
				bhi.nNumberOfLinks,0xFE,
				i64ID
				);
		}
		break;
	case 43: /*GetFileSize*/
		retint=-1;
		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
		{
			LARGE_INTEGER i6;
			i6.QuadPart=0;
			#ifdef W_95
				i6.LowPart= GetFileSize (m_HANDLE, (unsigned long *)& (i6.HighPart)) ; 
				smallStr.Format("%I64d",i6.QuadPart);
			#else
				#ifdef W_NT
					i6.LowPart= GetFileSize (m_HANDLE, (unsigned long *)&(i6.HighPart)) ; 
					smallStr.Format("%I64d",i6.QuadPart);
				#else
					#ifdef W_98
						i6.LowPart= GetFileSize (m_HANDLE, (unsigned long *)& (i6.HighPart)) ; 
						smallStr.Format("%I64d",i6.QuadPart);
					#else
						if (GetFileSizeEx(m_HANDLE,&i6))
							smallStr.Format("%I64d",i6.QuadPart);
						else
							retint=-1;
					#endif
				#endif
			#endif
		}
		else retint=-1;
		break;
	case 44: /*LockFile*/
	case 46: /*UnlockFile*/
		retint=-1;
		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
		{
			LARGE_INTEGER FileOffset;
			LARGE_INTEGER NumberOfBytes;
			NumberOfBytes.QuadPart=0;
			FileOffset.QuadPart=0;
			m_LastScanf=sscanf(pos,"%I64d,%I64d",&FileOffset.QuadPart,&NumberOfBytes.QuadPart);
			if (nfunc==44)
				retint=LockFile(m_HANDLE,FileOffset.LowPart,FileOffset.HighPart,NumberOfBytes.LowPart,NumberOfBytes.HighPart);
			else
				retint=UnlockFile(m_HANDLE,FileOffset.LowPart,FileOffset.HighPart,NumberOfBytes.LowPart,NumberOfBytes.HighPart);
		}
		break;
	case 45: /*GetFileType*/
		retint=-1;
		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
		{
			DWORD type=GetFileType(m_HANDLE);
			if (type==0) smallStr+="FILE_TYPE_UNKNOWN|";
			if ((type&FILE_TYPE_DISK)==FILE_TYPE_DISK) smallStr+="FILE_TYPE_DISK|";
			if ((type&FILE_TYPE_CHAR)==FILE_TYPE_CHAR) smallStr+="FILE_TYPE_CHAR|";
			if ((type&FILE_TYPE_PIPE)==FILE_TYPE_PIPE) smallStr+="FILE_TYPE_PIPE|";
			if ((type&FILE_TYPE_REMOTE)==FILE_TYPE_REMOTE) smallStr+="FILE_TYPE_REMOTE|";
		}
		break;

	case 47: /*SetFileValidData*/
		retint=-1;
		#ifdef W_95
		#else
			#ifdef W_NT
			#else
				#ifdef W_98
				#else
					#ifdef W_2000
					#else
						if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
						{
							__int64 FileValidDataLen=0;
							m_LastScanf=sscanf(pos,"%I64d",&FileValidDataLen);
							retint=SetFileValidData(m_HANDLE,FileValidDataLen);
						}
					#endif
				#endif
			#endif
		#endif
		break;

	case 48: /*SetFileShortName*/
		retint=-1;
		#ifdef W_95
		#else
			#ifdef W_NT
			#else
				#ifdef W_98
				#else
					#ifdef W_2000
					#else
						if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
							retint=SetFileShortName(m_HANDLE,pos);
					#endif
				#endif
			#endif
		#endif
		break;
	case 49: /*SetEndOfFile*/
		retint=-1;
		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
			retint=SetEndOfFile(m_HANDLE);
		break;
	case 50: /*SetFilePointer*/
		retint=-1;
		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
		{
			LARGE_INTEGER FilePointer;
			FilePointer.QuadPart=0;
			m_LastScanf=sscanf(pos,"%I64d",&FilePointer.QuadPart);
			DWORD dwMoveMethod=FILE_BEGIN;
			smallStr=ExtractField(pos,2,",");
			if ((dwMoveMethod=atoi(smallStr))==0)
			{
				if (smallStr.FindOneOf("BbGgIi")>=0) dwMoveMethod=FILE_BEGIN;
				if (smallStr.FindOneOf("UuCcRrTt")>=0) dwMoveMethod=FILE_CURRENT;
				if (smallStr.FindOneOf("Dd")>=0) dwMoveMethod=FILE_CURRENT;
			}
			retint=SetFilePointer(m_HANDLE,FilePointer.LowPart,&FilePointer.HighPart,dwMoveMethod);
		}
		break;
	#ifdef W_95
	#else
	case 51: /*ReadDirectoryChanges*/
		retint=-1;
		if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE && oStr)
		{
			BOOL bWatchSubtree=0;
			LPVOID lpBuffer=NULL;
			DWORD nBufferLength=0;
			DWORD dwNotifyFilter=0;
			DWORD BytesReturned=0;
			m_LastScanf=sscanf(pos,"%d,%d,%d",&nBufferLength,&bWatchSubtree,&dwNotifyFilter);
			if (nBufferLength && nBufferLength<1000) nBufferLength*=1000;
			else nBufferLength=1000;
			lpBuffer=new char [nBufferLength];
			if (lpBuffer)
			{
				dwNotifyFilter|=StringToFileNotifChange(ExtractField(pos,3,","));
				if (strstr(pos,"file_name")	|| strstr(pos,"FILE_NAME")	)	dwNotifyFilter|=FILE_NOTIFY_CHANGE_FILE_NAME;
				if (strstr(pos,"dir_name")	|| strstr(pos,"DIR_NAME")	)	dwNotifyFilter|=FILE_NOTIFY_CHANGE_DIR_NAME;
				if (strstr(pos,"attributes")|| strstr(pos,"ATTRIBUTES")	)	dwNotifyFilter|=FILE_NOTIFY_CHANGE_ATTRIBUTES;
				if (strstr(pos,"size")		|| strstr(pos,"SIZE")		)	dwNotifyFilter|=FILE_NOTIFY_CHANGE_SIZE;
				if (strstr(pos,"write")		|| strstr(pos,"WRITE")		)	dwNotifyFilter|=FILE_NOTIFY_CHANGE_LAST_WRITE;
				if (strstr(pos,"access")	|| strstr(pos,"ACCESS")		)	dwNotifyFilter|=FILE_NOTIFY_CHANGE_LAST_ACCESS;
				if (strstr(pos,"creation")	|| strstr(pos,"CREATION")	)	dwNotifyFilter|=FILE_NOTIFY_CHANGE_CREATION;
				if (strstr(pos,"security")	|| strstr(pos,"SECURITY")	)	dwNotifyFilter|=FILE_NOTIFY_CHANGE_SECURITY;

				if ((retint=ReadDirectoryChangesW(m_HANDLE,lpBuffer,nBufferLength,bWatchSubtree,dwNotifyFilter,&BytesReturned,NULL,NULL) && BytesReturned))
				{
					DWORD len=0;
					FILE_NOTIFY_INFORMATION *FNI;
					UINT nElements=0;
					FNI=(FILE_NOTIFY_INFORMATION *)(((BYTE *)lpBuffer)+len);

					while(len<BytesReturned)
					{
						FNI=(FILE_NOTIFY_INFORMATION *)(((BYTE *)lpBuffer)+len);
						len+=FNI->NextEntryOffset;
						nElements++;
					}


					*oStr=new char [BytesReturned+nElements*32];
					char *tmp=*oStr;
					len=0;
					while(len<BytesReturned)
					{
						if (len) {*(tmp++)='\x7F';*tmp=0;}
						FNI=(FILE_NOTIFY_INFORMATION *)(((BYTE *)lpBuffer)+len);
						if (FNI->FileNameLength<=BytesReturned-len)
						{
							CString tmpstr=FNI->FileName;
							strncpy(tmp,tmpstr,FNI->FileNameLength);
							tmp+=FNI->FileNameLength;
							*tmp=0;
						}
						*(tmp++)='\x07';
						*tmp=0;
						strcpy(tmp,FActionToString(FNI->Action));
						while(*tmp) tmp++;
						len+=FNI->NextEntryOffset;
					}
				}
				delete[] lpBuffer;
			}
		}
		break;
	#endif
	case 52: /*SetBookMark*/
		{
			retint=m_Pool.SetBookMarkFlag(1);
		}
		break;
	case 53: /*DeleteBookMark*/
		{
			m_Pool.GetBookMarkFlag();
		}
		break;
	case 54: /*GetCRC16*/
		{
			int start=0,Length=0,CRCType=0;
			DWORD PrevSumm=0;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&start,&Length,&PrevSumm,&CRCType);
			DWORD crc=m_Pool.GetCRC16(start,Length,PrevSumm,CRCType);
			smallStr.Format("%d%c%d%c%d%c%d",(crc/0x1000000)&0xFF,0xFE,(crc/0x10000)&0xFF,0xFE,(crc/0x100)&0xFF,0xFE,crc&0xFF);
		}
		break;
	case 55: /*MoveBookMark*/
		if (atoipos)
			retint=m_Pool.MoveBookMark(atoipos);
		break;
	case 56: /*ClearReadBuffer*/
		m_Pool.Init(65520);
		break;
	case 57: /*GetArrCRC16*/
		if (oStr)
		{
			GPC.m_Document->DoFileSystemMethod(iStr,oStr);
			if (*oStr) AnsiToDos(*oStr,0);
		}
		break;


	default:
		GPC.m_ErrReport.GPWriteWarnLog2("IOFile", "Unknown Method",iStr);
		if (oStr!=NULL)
		{
			*oStr=new char [1000];
			sprintf(*oStr,ErrObjSub,met); nfunc=0xFFFFFFFFL; 
		}
		break;
	}
}catch(...)
{
	char *str=new char [(int)strlen(pos)+1000];
	#ifdef RUS
		sprintf(str,"Ошибка выполнения метода %s %s",met,pos);
		::MessageBox(GPC.m_hViewWnd,str,"Ошибка метода",MB_OK|MB_ICONEXCLAMATION);
	#else
		sprintf(str,"Error execution of method %s %s",met,pos);
		::MessageBox(GPC.m_hViewWnd,str,"Error execution",MB_OK|MB_ICONEXCLAMATION);
	#endif
	nfunc=0xFFFFFFFFL;
	GPC.m_ErrReport.GPWriteErrorLog("GPIOFile", "DoMethod",iStr);
	if (oStr!=NULL && *oStr==0)
		*oStr=str;
	else
		delete[] str;
}

	if (oStr!=NULL && *oStr==0)
	{
		if (smallStr!="")
		{
			*oStr=new char [smallStr.GetLength()+10];
			strcpy(*oStr,smallStr);
		}
		else
		if (retint!=-123456)
		{
			*oStr=new char [1000];
			sprintf(*oStr,"%d",retint);
		}
	}

	return nfunc;
}


// static fn
const CString GPIOFile::FileTypeToString(UINT iFileType)
{
	CString ret;
	if (iFileType==0)
	{
		ret=cArrFileType[0];
	}
	else
	{
		UINT i;
		for(i=0;i<uNFileType;i++)
			if (uArrFileType[i] && (iFileType&uArrFileType[i])==uArrFileType[i])
			{
				if (ret=="") ret=cArrFileType[i];
				else {ret+="|";ret+=cArrFileType[i];}
			}
	}
	return ret;
}

UINT GPIOFile::StringToFileType(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNFileType;i++)
			ret|=uArrFileType[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNFileType;i++)
			if (tmps.Find(cArrFileType[i],0)>=0) ret|=uArrFileType[i];
	}

	return ret;
}

const CString GPIOFile::DesAccessToString(UINT iDesAccess)
{
	CString ret;
	UINT i;
	for(i=0;i<uNDesAccess;i++)
		if ((iDesAccess&uArrDesAccess[i])==uArrDesAccess[i])
		{
			if (ret=="") ret=cArrDesAccess[i];
			else {ret+="|";ret+=cArrDesAccess[i];}
		}
	return ret;
}

UINT GPIOFile::StringToDesAccess(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNDesAccess;i++)
			ret|=uArrDesAccess[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNDesAccess;i++)
			if (tmps.Find(cArrDesAccess[i],0)>=0)
				ret|=uArrDesAccess[i];
	}

	return ret;
}

const CString GPIOFile::FShareToString(UINT iFShare)
{
	CString ret;
	UINT i;
	for(i=0;i<uNFShare;i++)
		if ((iFShare&uArrFShare[i])==uArrFShare[i])
		{
			if (ret=="") ret=cArrFShare[i];
			else {ret+="|";ret+=cArrFShare[i];}
		}
	return ret;
}

UINT GPIOFile::StringToFShare(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNFShare;i++)
			ret|=uArrFShare[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNFShare;i++)
			if (tmps.Find(cArrFShare[i],0)>=0) ret|=uArrFShare[i];
	}

	return ret;
}

const CString GPIOFile::CreationDispositionToString(UINT iCreationDisposition)
{
	CString ret;
	UINT i;
	for(i=0;i<uNCreationDisposition;i++)
		if ((iCreationDisposition&uArrCreationDisposition[i])==uArrCreationDisposition[i])
		{
			if (ret=="") ret=cArrCreationDisposition[i];
			else {ret+="|";ret+=cArrCreationDisposition[i];}
		}
	return ret;
}

UINT GPIOFile::StringToCreationDisposition(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNCreationDisposition;i++)
			ret|=uArrCreationDisposition[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNCreationDisposition;i++)
			if (tmps.Find(cArrCreationDisposition[i],0)>=0) ret|=uArrCreationDisposition[i];
	}

	return ret;
}

const CString GPIOFile::FlagsAndAttributesToString(UINT iFlagsAndAttributes)
{
	CString ret;
	UINT i;
	for(i=0;i<uNFlagsAndAttributes;i++)
		if ((iFlagsAndAttributes&uArrFlagsAndAttributes[i])==uArrFlagsAndAttributes[i])
		{
			if (ret=="") ret=cArrFlagsAndAttributes[i];
			else {ret+="|";ret+=cArrFlagsAndAttributes[i];}
		}
	return ret;
}

const CString GPIOFile::FileAttributesToString(UINT iAttributes)
{
	CString ret;
	UINT i;
	for(i=0;i<15;i++)
		if ((iAttributes&uArrFlagsAndAttributes[i])==uArrFlagsAndAttributes[i])
		{
			if (ret=="") ret=cArrFlagsAndAttributes[i];
			else {ret+="|";ret+=cArrFlagsAndAttributes[i];}
		}
	return ret;
}

UINT GPIOFile::StringToFlagsAndAttributes(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNFlagsAndAttributes;i++)
			ret|=uArrFlagsAndAttributes[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNFlagsAndAttributes;i++)
			if (tmps.Find(cArrFlagsAndAttributes[i],0)>=0) ret|=uArrFlagsAndAttributes[i];
	}

	return ret;
}

const CString GPIOFile::IOStyleToString(UINT iIOStyle)
{
	CString ret;
	UINT i;
	for(i=0;i<uNIOStyle;i++)
		if ((iIOStyle&uArrIOStyle[i])==uArrIOStyle[i])
		{
			if (ret=="") ret=cArrIOStyle[i];
			else {ret+="|";ret+=cArrIOStyle[i];}
		}
	return ret;
}

UINT GPIOFile::StringToIOStyle(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNIOStyle;i++)
			ret|=uArrIOStyle[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNIOStyle;i++)
			if (tmps.Find(cArrIOStyle[i],0)>=0) ret|=uArrIOStyle[i];
	}

	return ret;
}

const CString GPIOFile::CErrorToString(UINT iCError)
{
	CString ret;
	UINT i;
	for(i=0;i<uNCError;i++)
		if ((iCError&uArrCError[i])==uArrCError[i])
		{
			if (ret=="") ret=cArrCError[i];
			else {ret+="|";ret+=cArrCError[i];}
		}
	return ret;
}

UINT GPIOFile::StringToCError(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNCError;i++)
			ret|=uArrCError[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNCError;i++)
			if (tmps.Find(cArrCError[i],0)>=0) ret|=uArrCError[i];
	}

	return ret;
}

const CString GPIOFile::CEventsToString(UINT iCEvents)
{
	CString ret;
	UINT i;
	for(i=0;i<uNCEvents;i++)
		if ((iCEvents&uArrCEvents[i])==uArrCEvents[i])
		{
			if (ret=="") ret=cArrCEvents[i];
			else {ret+="|";ret+=cArrCEvents[i];}
		}
	return ret;
}

UINT GPIOFile::StringToCEvents(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNCEvents;i++)
			ret|=uArrCEvents[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNCEvents;i++)
			if (tmps.Find(cArrCEvents[i],0)>=0)
				ret|=uArrCEvents[i];
	}

	return ret;
}

const CString GPIOFile::CMStatusToString(UINT iCMStatus)
{
	CString ret;
	UINT i;
	for(i=0;i<uNCMStatus;i++)
		if ((iCMStatus&uArrCMStatus[i])==uArrCMStatus[i])
		{
			if (ret=="") ret=cArrCMStatus[i];
			else {ret+="|";ret+=cArrCMStatus[i];}
		}
	return ret;
}

UINT GPIOFile::StringToCMStatus(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNCMStatus;i++)
			ret|=uArrCMStatus[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNCMStatus;i++)
			if (tmps.Find(cArrCMStatus[i],0)>=0) ret|=uArrCMStatus[i];
	}

	return ret;
}

const CString GPIOFile::BAUDToString(UINT iBAUD)
{
	CString ret;
	UINT i;
	for(i=0;i<uNBAUD;i++)
		if ((iBAUD&uArrBAUD[i])==uArrBAUD[i])
		{
			if (ret=="") ret=cArrBAUD[i];
			else {ret+="|";ret+=cArrBAUD[i];}
		}
	return ret;
}

UINT GPIOFile::StringToBAUD(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNBAUD;i++)	ret|=uArrBAUD[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNBAUD;i++)
			if (tmps.Find(cArrBAUD[i],0)>=0) ret|=uArrBAUD[i];
	}
	return ret;
}

const CString GPIOFile::ProvSubTypeToString(UINT iProvSubType)
{
	CString ret;
	UINT i;
	for(i=0;i<uNProvSubType;i++)
		if ((iProvSubType&uArrProvSubType[i])==uArrProvSubType[i])
		{
			if (ret=="") ret=cArrProvSubType[i];
			else {ret+="|";ret+=cArrProvSubType[i];}
		}
	return ret;
}

UINT GPIOFile::StringToProvSubType(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNProvSubType;i++)	ret|=uArrProvSubType[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNProvSubType;i++)
			if (tmps.Find(cArrProvSubType[i],0)>=0) ret|=uArrProvSubType[i];
	}
	return ret;
}

const CString GPIOFile::ProvCapToString(UINT iProvCap)
{
	CString ret;
	UINT i;
	for(i=0;i<uNProvCap;i++)
		if ((iProvCap&uArrProvCap[i])==uArrProvCap[i])
		{
			if (ret=="") ret=cArrProvCap[i];
			else {ret+="|";ret+=cArrProvCap[i];}
		}
	return ret;
}

UINT GPIOFile::StringToProvCap(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNProvCap;i++)	ret|=uArrProvCap[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNProvCap;i++)
			if (tmps.Find(cArrProvCap[i],0)>=0) ret|=uArrProvCap[i];
	}
	return ret;
}

const CString GPIOFile::SettableParamsToString(UINT iSettableParams)
{
	CString ret;
	UINT i;
	for(i=0;i<uNSettableParams;i++)
		if ((iSettableParams&uArrSettableParams[i])==uArrSettableParams[i])
		{
			if (ret=="") ret=cArrSettableParams[i];
			else {ret+="|";ret+=cArrSettableParams[i];}
		}
	return ret;
}

UINT GPIOFile::StringToSettableParams(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNSettableParams;i++)	ret|=uArrSettableParams[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNSettableParams;i++)
			if (tmps.Find(cArrSettableParams[i],0)>=0) ret|=uArrSettableParams[i];
	}
	return ret;
}

const CString GPIOFile::SettableDataToString(UINT iSettableData)
{
	CString ret;
	UINT i;
	for(i=0;i<uNSettableData;i++)
		if ((iSettableData&uArrSettableData[i])==uArrSettableData[i])
		{
			if (ret=="") ret=cArrSettableData[i];
			else {ret+="|";ret+=cArrSettableData[i];}
		}
	return ret;
}

UINT GPIOFile::StringToSettableData(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNSettableData;i++)	ret|=uArrSettableData[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNSettableData;i++)
			if (tmps.Find(cArrSettableData[i],0)>=0) ret|=uArrSettableData[i];
	}
	return ret;
}

const CString GPIOFile::SettableStopParityToString(UINT iSettableStopParity)
{
	CString ret;
	UINT i;
	for(i=0;i<uNSettableStopParity;i++)
		if ((iSettableStopParity&uArrSettableStopParity[i])==uArrSettableStopParity[i])
		{
			if (ret=="") ret=cArrSettableStopParity[i];
			else {ret+="|";ret+=cArrSettableStopParity[i];}
		}
	return ret;
}

UINT GPIOFile::StringToSettableStopParity(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNSettableStopParity;i++)	ret|=uArrSettableStopParity[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNSettableStopParity;i++)
			if (tmps.Find(cArrSettableStopParity[i],0)>=0) ret|=uArrSettableStopParity[i];
	}
	return ret;
}

const CString GPIOFile::FActionToString(UINT iFAction)
{
	CString ret;
	UINT i;
	for(i=0;i<uNFAction;i++)
		if ((iFAction&uArrFAction[i])==uArrFAction[i])
		{
			if (ret=="") ret=cArrFAction[i];
			else {ret+="|";ret+=cArrFAction[i];}
		}
	return ret;
}

UINT GPIOFile::StringToFAction(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNFAction;i++)	ret|=uArrFAction[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNFAction;i++)
			if (tmps.Find(cArrFAction[i],0)>=0) ret|=uArrFAction[i];
	}
	return ret;
}

const CString GPIOFile::FileEncryptStatusToString(UINT iFileEncryptStatus)
{
	CString ret;
	UINT i;
	for(i=0;i<uNFileEncryptStatus;i++)
		if ((iFileEncryptStatus&uArrFileEncryptStatus[i])==uArrFileEncryptStatus[i])
		{
			if (ret=="") ret=cArrFileEncryptStatus[i];
			else {ret+="|";ret+=cArrFileEncryptStatus[i];}
		}
	return ret;
}

UINT GPIOFile::StringToFileEncryptStatus(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNFileEncryptStatus;i++)	ret|=uArrFileEncryptStatus[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNFileEncryptStatus;i++)
			if (tmps.Find(cArrFileEncryptStatus[i],0)>=0) ret|=uArrFileEncryptStatus[i];
	}
	return ret;
}

const CString GPIOFile::FBinaryTypeToString(UINT iFBinaryType)
{
	CString ret;
	UINT i;
	for(i=1;i<uNFBinaryType && ret=="";i++)
		if (iFBinaryType==uArrFBinaryType[i])
			ret=cArrFBinaryType[i];

	if (ret=="") ret=cArrFBinaryType[0];

	return ret;
}

UINT GPIOFile::StringToFBinaryType(const char* iStr)
{
	UINT ret=0;
	if (iStr)
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNFBinaryType && ret;i++)
			if (tmps.Find(cArrFBinaryType[i],0)>=0) ret=uArrFBinaryType[i];
	}
	return ret;
}

const CString GPIOFile::DriveTypeToString(UINT iDriveType)
{
	CString ret;
	UINT i;
	for(i=1;i<uNDriveType && ret=="";i++)
		if (iDriveType==uArrDriveType[i])
			ret=cArrDriveType[i];

	if (ret=="") ret=cArrDriveType[0];

	return ret;
}

UINT GPIOFile::StringToDriveType(const char* iStr)
{
	UINT ret=0;
	if (iStr)
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNDriveType && ret;i++)
			if (tmps.Find(cArrDriveType[i],0)>=0) ret=uArrDriveType[i];
	}
	return ret;
}

const CString GPIOFile::FMoveFlagToString(UINT iFMoveFlag)
{
	CString ret;
	UINT i;
	for(i=0;i<uNFMoveFlag;i++)
		if ((iFMoveFlag&uArrFMoveFlag[i])==uArrFMoveFlag[i])
		{
			if (ret=="") ret=cArrFMoveFlag[i];
			else {ret+="|";ret+=cArrFMoveFlag[i];}
		}
	return ret;
}

UINT GPIOFile::StringToFMoveFlag(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNFMoveFlag;i++)	ret|=uArrFMoveFlag[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNFMoveFlag;i++)
			if (tmps.Find(cArrFMoveFlag[i],0)>=0) ret|=uArrFMoveFlag[i];
	}
	return ret;
}

const CString GPIOFile::DeviceFlagToString(UINT iDeviceFlag)
{
	CString ret;
	UINT i;
	for(i=0;i<uNDeviceFlag;i++)
		if ((iDeviceFlag&uArrDeviceFlag[i])==uArrDeviceFlag[i])
		{
			if (ret=="") ret=cArrDeviceFlag[i];
			else {ret+="|";ret+=cArrDeviceFlag[i];}
		}
	return ret;
}

UINT GPIOFile::StringToDeviceFlag(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNDeviceFlag;i++)	ret|=uArrDeviceFlag[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNDeviceFlag;i++)
			if (tmps.Find(cArrDeviceFlag[i],0)>=0) ret|=uArrDeviceFlag[i];
	}
	return ret;
}

const CString GPIOFile::FileNotifChangeToString(UINT iFileNotifChange)
{
	CString ret;
	UINT i;
	for(i=0;i<uNFileNotifChange;i++)
		if ((iFileNotifChange&uArrFileNotifChange[i])==uArrFileNotifChange[i])
		{
			if (ret=="") ret=cArrFileNotifChange[i];
			else {ret+="|";ret+=cArrFileNotifChange[i];}
		}
	return ret;
}

UINT GPIOFile::StringToFileNotifChange(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNFileNotifChange;i++)	ret|=uArrFileNotifChange[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNFileNotifChange;i++)
			if (tmps.Find(cArrFileNotifChange[i],0)>=0) ret|=uArrFileNotifChange[i];
	}
	return ret;
}

/*
const CString GPIOFile::xxxxToString(UINT ixxxx)
{
	CString ret;
	UINT i;
	for(i=0;i<uNxxxx;i++)
		if ((ixxxx&uArrxxxx[i])==uArrxxxx[i])
		{
			if (ret=="") ret=cArrxxxx[i];
			else {ret+="|";ret+=cArrxxxx[i];}
		}
	return ret;
}

UINT GPIOFile::StringToxxxx(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
	UINT i;
		for(i=0;i<uNxxxx;i++)	ret|=uArrxxxx[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

  UINT i;
		for(i=0;i<uNxxxx;i++)
			if (tmps.Find(cArrxxxx[i],0)>=0) ret|=uArrxxxx[i];
	}
	return ret;
}
*/

const CString GPIOFile::FA_DATAToString(WIN32_FILE_ATTRIBUTE_DATA & iFA_DATA)
{
	CString ret;

	LARGE_INTEGER FileSize;
	FileSize.LowPart=iFA_DATA.nFileSizeLow;
	FileSize.HighPart=iFA_DATA.nFileSizeHigh;

	SYSTEMTIME CreationTime={0}; 
	SYSTEMTIME LastAccessTime={0}; 
	SYSTEMTIME LastWriteTime={0}; 
	FileTimeToSystemTime(&(iFA_DATA.ftCreationTime),&CreationTime);
	FileTimeToSystemTime(&(iFA_DATA.ftLastAccessTime),&LastAccessTime);
	FileTimeToSystemTime(&(iFA_DATA.ftLastWriteTime),&LastWriteTime);

	ret.Format("%s%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%I64d",
		(LPCSTR)FileAttributesToString(iFA_DATA.dwFileAttributes),0xFE,
		CreationTime.wYear,0xFD,CreationTime.wMonth,0xFD,CreationTime.wDay,0xFD,CreationTime.wHour,0xFD,CreationTime.wMinute,0xFD,CreationTime.wSecond,0xFD,CreationTime.wMilliseconds,0xFE,
		LastAccessTime.wYear,0xFD,LastAccessTime.wMonth,0xFD,LastAccessTime.wDay,0xFD,LastAccessTime.wHour,0xFD,LastAccessTime.wMinute,0xFD,LastAccessTime.wSecond,0xFD,LastAccessTime.wMilliseconds,0xFE,
		LastWriteTime.wYear,0xFD,LastWriteTime.wMonth,0xFD,LastWriteTime.wDay,0xFD,LastWriteTime.wHour,0xFD,LastWriteTime.wMinute,0xFD,LastWriteTime.wSecond,0xFD,LastWriteTime.wMilliseconds,0xFE,
		FileSize.QuadPart
		);

	return ret;
}

const CString GPIOFile::FF_DATAToString(WIN32_FIND_DATA & iFF_DATA)
{
	CString ret;

	LARGE_INTEGER FileSize;
	FileSize.LowPart=iFF_DATA.nFileSizeLow;
	FileSize.HighPart=iFF_DATA.nFileSizeHigh;

	SYSTEMTIME CreationTime={0}; 
	SYSTEMTIME LastAccessTime={0}; 
	SYSTEMTIME LastWriteTime={0}; 
	FileTimeToSystemTime(&(iFF_DATA.ftCreationTime),&CreationTime);
	FileTimeToSystemTime(&(iFF_DATA.ftLastAccessTime),&LastAccessTime);
	FileTimeToSystemTime(&(iFF_DATA.ftLastWriteTime),&LastWriteTime);
	ret.Format("%s%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%I64d%c%s%c%s%c%d%c%d",
		(LPCSTR)FileAttributesToString(iFF_DATA.dwFileAttributes),0xFE,
		CreationTime.wYear,0xFD,CreationTime.wMonth,0xFD,CreationTime.wDay,0xFD,CreationTime.wHour,0xFD,CreationTime.wMinute,0xFD,CreationTime.wSecond,0xFD,CreationTime.wMilliseconds,0xFE,
		LastAccessTime.wYear,0xFD,LastAccessTime.wMonth,0xFD,LastAccessTime.wDay,0xFD,LastAccessTime.wHour,0xFD,LastAccessTime.wMinute,0xFD,LastAccessTime.wSecond,0xFD,LastAccessTime.wMilliseconds,0xFE,
		LastWriteTime.wYear,0xFD,LastWriteTime.wMonth,0xFD,LastWriteTime.wDay,0xFD,LastWriteTime.wHour,0xFD,LastWriteTime.wMinute,0xFD,LastWriteTime.wSecond,0xFD,LastWriteTime.wMilliseconds,0xFE,
		FileSize.QuadPart,0xFE,
		iFF_DATA.cFileName,0xFE,
		iFF_DATA.cAlternateFileName,0xFE,
		iFF_DATA.dwReserved0,0xFE,
		iFF_DATA.dwReserved1
		);

	return ret;
}

void GPIOFile::DoRead()
{
	if (m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
	{
		switch(m_Type)
		{
			case FT_COM:
				{
					COMSTAT cs;
					DWORD ner;
					ClearCommError(m_HANDLE,&ner,&cs);
					UINT nB=0;
					if (cs.cbInQue)
						nB=m_Pool.FillFromHandle(m_HANDLE,&ovr,cs.cbInQue,1);

					if (((m_Style&FT_ERRORREPORT)==FT_ERRORREPORT || m_EventsEditor) && ner )
					{
						EnterCriticalSection(&GPC.m_View->m_CSRemap);
						EnterCriticalSection(&m_CSEditor);
						try
						{
							char *ms=new char [5000];
							sprintf(ms,"%c%c%d%c%s%c%s%c%s%c%s%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d\r",
								250,
								250,
								54,0xFE,
								"ERRORREPORT",0xFE,
								(LPCSTR)m_csSubName,0xFE,
								(LPCSTR)m_csName,0xFE,
								(LPCSTR)CErrorToString(ner),0xFE,
								ner,0xFE,
								cs.fCtsHold,0xFE,
								cs.fDsrHold,0xFE,
								cs.fRlsdHold,0xFE,
								cs.fXoffHold,0xFE,
								cs.fXoffSent,0xFE,
								cs.fEof,0xFE,
								cs.fTxim,0xFE,
								cs.fReserved,0xFE,
								cs.cbInQue,0xFE,
								cs.cbOutQue
								);
							if (m_EventsEditor && ::IsWindow(m_EventsEditor))
							{
								char *CallbackStr=new char [5000];
								strcpy(CallbackStr,ms);
								::PostMessage(m_EventsEditor,GPM_SETANDDELETESTRING,(WPARAM)CallbackStr,(LPARAM)CallbackStr);
								::PostMessage(m_EventsEditor,GPM_SETANDDELETESTRING,0,(LPARAM)"\r\n");
							}
							if ((m_Style&FT_ERRORREPORT)==FT_ERRORREPORT)
							{
								m_Comm.GPSendSafeBlock(ms,(int)strlen(ms));
							}
							delete[] ms;
						}
						catch(...)
						{
							GPC.m_ErrReport.GPWriteErrorLog("GPIOFile", "DoRead 2335","");
						}
						LeaveCriticalSection(&m_CSEditor);
						LeaveCriticalSection(&GPC.m_View->m_CSRemap);
					}

					if (((m_Style&FT_SENDDATA)==FT_SENDDATA || m_EventsEditor) && nB)
					{
						EnterCriticalSection(&GPC.m_View->m_CSRemap);
						EnterCriticalSection(&m_CSEditor);
						try
						{
							char str1[100];
							sprintf(str1,"%c%c%d%c%s%c%s%c%s%c%d",
								250,
								250,
								54,0xFE,
								"DATAIN",0xFE,
								(LPCSTR)m_csSubName,0xFE,
								(LPCSTR)m_csName,0xFE,
								nB);

							if (m_EventsEditor && ::IsWindow(m_EventsEditor))
							{
								char *CallbackStr=new char [1000];
								strcpy(CallbackStr,str1);
								::PostMessage(m_EventsEditor,GPM_SETANDDELETESTRING,(WPARAM)CallbackStr,(LPARAM)CallbackStr);
							}

							if ((m_Style&FT_SENDDATA)==FT_SENDDATA)
								m_Comm.GPSendSafeBlock(str1,(int)strlen(str1));

							char *tmps=NULL;
							UINT nSend=GetDataToBuffer(&tmps,nB);
							if (tmps)
							{
								if (m_EventsEditor)
								{
									char *CallbackStr=new char [nSend+100];
									strcpy(CallbackStr,tmps);
									::PostMessage(m_EventsEditor,GPM_SETANDDELETESTRING,(WPARAM)CallbackStr,(LPARAM)CallbackStr);
								}

								if ((m_Style&FT_SENDDATA)==FT_SENDDATA)
									m_Comm.GPSendSafeBlock(tmps,nSend);
								delete[] tmps;
								tmps=NULL;
							}

							if (m_EventsEditor && ::IsWindow(m_EventsEditor))
							{
								::PostMessage(m_EventsEditor,GPM_SETANDDELETESTRING,0,(LPARAM)"\r\n");
							}
							if ((m_Style&FT_SENDDATA)==FT_SENDDATA)
								m_Comm.GPSendSafeBlock("\r",1);
						}
						catch(...)
						{
							GPC.m_ErrReport.GPWriteErrorLog("GPIOFile", "DoRead","");
						}
						LeaveCriticalSection(&m_CSEditor);
						LeaveCriticalSection(&GPC.m_View->m_CSRemap);
					}
				}
				break;
			default:
				break;
		}
	}
}

UINT GPIOFile::GetDataToBuffer(char **cBuffer, UINT uLen)
{
	BYTE *ms=NULL;
	uLen=m_Pool.GetData(&ms,uLen);
	UINT RetLen=0;

	if (uLen)
	{
		if ((m_Style&FT_CONVERT)==FT_CONVERT)	AnsiToDos(ms,0,uLen);

		switch((m_Style&FT_DATAMASK))
		{
		case FT_DEC:
			*cBuffer=new char [(RetLen=uLen*3)+5];
			**cBuffer=0;
			GetDecStr(*cBuffer,ms,uLen);
			break;
		case FT_HEX:
			*cBuffer=new char [(RetLen=uLen*2)+5];
			**cBuffer=0;
			GetHexStr(*cBuffer,ms,uLen);
			break;
		case FT_OCT:
			*cBuffer=new char [(RetLen=uLen*3)+5];
			**cBuffer=0;
			GetOctStr(*cBuffer,ms,uLen);
			break;
		case FT_SYMBOL:
			*cBuffer =new char [(RetLen=uLen*2)+10];
			**cBuffer=0;
			GetDblStr(*cBuffer,*cBuffer+uLen+1,ms,uLen);
			*cBuffer[uLen]=0xFE;
			*cBuffer[uLen+1]=0;
			break;
		default:
			{
				*cBuffer=new char [(RetLen=uLen)+5];
				**cBuffer=0;
				UINT i;
				for(i=0;i<uLen;i++)
				{
					BYTE c=ms[i];
					if (c==10 || c==13 || c==0) (*cBuffer)[i]=254;
					else						(*cBuffer)[i]=ms[i];
				}
				(*cBuffer)[i]=0;
			}
			break;
		}
	}
	if (ms) delete[] ms;
	return RetLen;
}

UINT GPIOFile::WriteDataByHandle(const char *Str1,const char *Str2)
{
	ULONG uLen=(int)strlen(Str1);

	if (uLen && m_HANDLE && m_HANDLE!=INVALID_HANDLE_VALUE)
	{

		BYTE *tmps=new BYTE [uLen+1];
		switch((m_Style&FT_DATAMASK))
		{
		case FT_DEC:
			GetDecArr(tmps,Str1);
			uLen/=3;
			break;
		case FT_HEX:
			GetHexArr(tmps,Str1);
			uLen/=2;
			break;
		case FT_OCT:
			GetOctArr(tmps,Str1);
			uLen/=3;
			break;
		case FT_SYMBOL:
			GetDblArr(tmps,Str1,Str2);
			break;
		default:
			break;
		}

		if (tmps)
		{
			if ((m_Style&FT_CONVERT)==FT_CONVERT)	DosToAnsi(tmps,uLen);
			WriteFile(m_HANDLE,(LPCVOID)tmps,uLen,&uLen,&ovw);
			delete[] tmps;
		}
	}
	return uLen;
}

void GPIOFile::StopComEvents()
{
	if (m_EventThread && m_IOFileEventsStopped==0)
	{
		m_IOFileStop=1;
		if (ove.hEvent) SetEvent(ove.hEvent);
		UINT cnt=500;
		while(m_IOFileStop && cnt-->10)
			Sleep(10);
	}
}
