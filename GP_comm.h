// GP_comm.h: interface for the GP_comm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GP_COMM_H__57D3C2A1_14DD_11D3_B27E_00600840D054__INCLUDED_)
#define AFX_GP_COMM_H__57D3C2A1_14DD_11D3_B27E_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define GPC_DUMPOUTBLOCK	0x00000001
#define GPC_DUMPOUT			0x00000002
#define GPC_DUMPOUTCHAR		0x00000004
#define GPC_DUMPOUTDEC		0x00000008
#define GPC_DUMPOUTHEX		0x00000010
#define GPC_DUMPIN			0x00000020
#define GPC_DUMPINCHAR		0x00000040
#define GPC_DUMPINDEC		0x00000080
#define GPC_DUMPINHEX		0x00000100
#define GPC_DUMPREM			0x00000200
#define GPC_DUMPREMCHAR		0x00000400
#define GPC_DUMPREMDEC		0x00000800
#define GPC_DUMPREMHEX		0x00001000
#define GPC_DUMPREMID		0x00002000
#define GPC_DUMPSPACE		0x00004000
#define GPC_DUMPCRLF		0x00008000
#define GPC_DUMPORIENT		0x00010000


#define GPCT_COMPORT		0x0000
#define GPCT_SOCKET			0x0002

#define GPCSF_SEND			0x0000
#define GPCSF_DONTSEND		0x1000


#include "GPInputPool.h"
#include "GPAsyncSocket.h"

class CUniSocket;  

class GP_comm  
{
friend class GPCurrent;
friend class CGP_TermDoc;
friend class CGP_TermView;
friend UINT CommunicateFnConnect(LPVOID pParam);

public:
	static int ChechAndDelete( const char *iConnectionName);
	void LoadDelimiters();
	void SaveDelimiters();
	int DelimiterIn1;
	int DelimiterIn2;
	int DelimiterIn3;
	int DelimiterIn4;
	int DelimiterIn5;
	int DelimiterIn6;
	int DelimiterSrc1;
	int DelimiterSrc2;
	int DelimiterSrc3;
	int DelimiterSrc4;
	int DelimiterSrc5;
	int DelimiterSrc6;

	DWORD m_TerminalID;
	DWORD dwUseSSH;
	UINT m_ConnectionFlag;
	UINT ListenTime;
	UINT ListenPort;
	UINT AddTerminalType(UINT iId, const char *iName);
	CString m_DumpPrefix;
	UINT m_uId;
	UINT m_uLockEventsEcho;
	BOOL IsErrorLog();
	void EndErrorLog();
	void StartErrorLog();
	int SendFlag;
	int GetPortNumber();
	void SetPortNumber(int iPortN);
	UINT GetBlockSize();
	UINT SetBlockSize(UINT iSize);
	BOOL IsConnected();
	int SendSequens(const char *iSeq);
	BOOL TandemFlag;
	const char * GetDumpFileName();
	const char * SetDumpFileName(const char *iName);
	UINT GetDumpMode();
	void SetDumpMode(UINT mode);
	void PrintDmp(UINT iCh, int iId, UINT iType);
	BOOL IsDumping();
	void GPStopDump();
	void GPStartDump();
	void GPContinueDump();
	char LastReadChar;
	char LastSendChar;
	UINT GPSendDWord(UINT iWord);
	UINT GPSendWord(UINT iWord);
	void GPInitialConnect();
	UINT GPRead(char *inputbuf,UINT nread);
	GP_comm(int flgDump);
	virtual ~GP_comm();
	void Set_comm(const char *i_comname, DWORD dwFlags);
	void SetComport(const char *icomport);
	void SetInitStr(const char *iInitStr);
	void SetEndStr(const char *iEndStr);
	void SetComment(const char *iGPcomment);
	UINT SetmaxBLOCK(UINT umaxBLOCK);
	void SetdcbBaudRate(UINT BaudRate);
	void SetdcbByteSize(UINT ByteSize);
	void SetdcbEofChar(UINT EofChar);
	void SetdcbErrorChar(UINT ErrorChar);
	void SetdcbEvtChar(UINT EvtChar);
	void SetdcbfAbortOnError(BOOL fAbortOnError);
	void SetdcbfBinary(BOOL fBinary);
	void SetdcbfDsrSensitivity(BOOL fDsrSensitivity);
	void SetdcbfDtrControl(UINT fDtrControl);
	void SetdcbfErrorChar(BOOL fErrorChar);
	void SetdcbfInX(BOOL fInX);
	void SetdcbfNull(BOOL fNull);
	void SetdcbfOutX(BOOL fOutX);
	void SetdcbfOutxCtsFlow(BOOL fOutxCtsFlow);
	void SetdcbfOutxDsrFlow(BOOL fOutxDsrFlow);
	void SetdcbfRtsControl(UINT fRtsControl);
	void SetdcbfTXContinueOnXoff(BOOL fTXContinueOnXoff);
	void SetdcbParity(UINT Parity);
	void SetdcbfParity(BOOL fParity);
	void SetdcbStopBits(UINT StopBits);
	void SetdcbXoffChar(UINT XoffChar);
	void SetdcbXoffLim(UINT XoffLim);
	void SetdcbXonChar(UINT XonChar);
	void SetdcbXonLim(UINT XonLim);
	void SetDelayBeforeSendChar(UINT iDelayBeforeSendChar);
	void SetDelayBeforeSendLine(UINT iDelayBeforeSendLine);
	void SetDelayBeforeSendBlock(UINT iDelayBeforeSendBlock);
	void SetDelayAfterSendChar(UINT iDelayAfterSendChar);
	void SetDelayAfterSendLine(UINT iDelayAfterSendLine);
	void SetDelayAfterSendBlock(UINT iDelayAfterSendBlock);
	UINT SetLockEventsEcho(UINT iLockEventsEcho)
	{
		UINT tmp=m_uLockEventsEcho;
		m_uLockEventsEcho=iLockEventsEcho;
		return tmp;
	}

	UINT GetdcbBaudRate()	{return dcb.BaudRate;}
	UINT GetdcbByteSize()	{return dcb.ByteSize;}

	UINT GetdcbEofChar()	{return dcb.EofChar;}
	UINT GetdcbErrorChar()	{return dcb.ErrorChar;}
	UINT GetdcbEvtChar()	{return dcb.EvtChar;}
	BOOL GetdcbfAbortOnError()	{return dcb.fAbortOnError;}
	BOOL GetdcbfBinary()	{return dcb.fBinary;}
	BOOL GetdcbfDsrSensitivity()	{return dcb.fDsrSensitivity;}
	UINT GetdcbfDtrControl()	{return dcb.fDtrControl;}
	BOOL GetdcbfErrorChar()	{return dcb.fErrorChar;}
	BOOL GetdcbfInX()	{return dcb.fInX;}
	BOOL GetdcbfNull()	{return dcb.fNull;}
	BOOL GetdcbfOutX()	{return dcb.fOutX;}
	BOOL GetdcbfOutxCtsFlow()	{return dcb.fOutxCtsFlow;}
	BOOL GetdcbfOutxDsrFlow()	{return dcb.fOutxDsrFlow;}
	UINT GetdcbfRtsControl()	{return dcb.fRtsControl;}
	BOOL GetdcbfTXContinueOnXoff()	{return dcb.fTXContinueOnXoff;}
	UINT GetdcbParity()	{return dcb.Parity;}
	BOOL GetdcbfParity()	{return dcb.fParity;}
	UINT GetdcbStopBits()	{return dcb.StopBits;}
	UINT GetdcbXoffChar()	{return dcb.XoffChar;}
	UINT GetdcbXoffLim()	{return dcb.XoffLim;}
	UINT GetdcbXonChar()	{return dcb.XonChar;}
	UINT GetdcbXonLim()	{return dcb.XonLim;}
	UINT GetLockEventsEcho()	{return m_uLockEventsEcho;}
	UINT GetDelayBeforeSendChar()	{return DelayBeforeSendChar;}
	UINT GetDelayBeforeSendLine()	{return DelayBeforeSendLine;}
	UINT GetDelayBeforeSendBlock()	{return DelayBeforeSendBlock;}
	UINT GetDelayAfterSendChar()	{return DelayAfterSendChar;}
	UINT GetDelayAfterSendLine()	{return DelayAfterSendLine;}
	UINT GetDelayAfterSendBlock()	{return DelayAfterSendBlock;}
	char *GetComport()	{return GPcomport;}
	const CString GetInitStr()	{return InitStr;}
	const CString GetEndStr()	{return EndStr;}
	const CString GetComment()	{return GPcomment;}
	UINT Get_commType()	{return com_type;}
	UINT Set_commType(UINT iNewType)	{	UINT ret=com_type;	if (iNewType==GPCT_COMPORT) com_type=GPCT_COMPORT; else com_type=GPCT_SOCKET;	return ret;	}
	void GPSetHostName(const char *iHostName)	{GPHostName=iHostName;}
	const CString GPGetHostName()	{return GPHostName;}
	
	void load_dcb(BOOL Flg = FALSE);
	void write_dcb();
	void GPClose();
	BOOL GPConnect();
	BOOL GPSendChar(const char ch);
	UINT GPSendLine(const char *ch);
	UINT GPSendBlock(const char *ch, UINT nByte, BOOL BlType = 0);
	UINT GPSendSafeBlock(const char *ch, UINT nByte, BOOL BlType = 0);
	UINT maxnCharDump,maxnLineDump;
	CString GPSectionName;

	UINT GetTelnetFlag(){return m_TelnetFlag;}
	UINT SetTelnetFlag(UINT iTelnetFlag);
	CGPInputPool *AltInputAccess();
	void AltInputRelease();
	
	int SendMessageToDLL(UINT message, WPARAM wParam, LPARAM lParam); //For SSH DLL
private:
	CGPInputPool m_AlternateInput;
	UINT m_TelnetFlag;
	OVERLAPPED ovw;
	OVERLAPPED ovr;
	FILE * m_FileErrorLog;
	UINT ErrDispRead(const char *pread, int nByte);
	UINT ErrDispWrite(const char *pwrite, int nByte);
	int PortNum;
	CRITICAL_SECTION m_CS;
	UINT maxBLOCK;
	char DumpFileName[FILENAME_MAX+10];
	char * ErrorLogFileName;
	UINT DumpMode;
	UINT oldTypeComm,nCharDump,nLineDump;
	FILE * logf;
	CString InitStr;
	CString EndStr;
	CString GPcomment;
	CString GPHostName;
	UINT com_type;
	HANDLE hComm;
	CGPAsyncSocket *hSock;
	CGPAsyncSocket *hSockToDelete;
	CUniSocket *UniSocket;
	DCB dcb;
	char GPcomport[20];
	UINT DelayBeforeSendChar;
	UINT DelayBeforeSendLine;
	UINT DelayBeforeSendBlock;
	UINT DelayAfterSendChar;
	UINT DelayAfterSendLine;
	UINT DelayAfterSendBlock;
	int m_flgDump;
};

#endif // !defined(AFX_GP_COMM_H__57D3C2A1_14DD_11D3_B27E_00600840D054__INCLUDED_)
