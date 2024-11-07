// GP_comm.cpp: implementation of the GP_comm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GP_term.h"
#include "GP_termDoc.h"
#include "GP_termView.h"
#include "UniSocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define tno_BINARY			0
#define tno_ECHO			1
#define tno_RECONNECTION    2
#define tno_GOAHEAD			3
#define tno_MESSAGE			4
#define tno_STATUS			5
#define tno_TIMING			6
#define tno_TRANSECHO		7
#define tno_LINEWIDTH		8
#define tno_PAGESIZE		9
#define tno_CRDISP			10
#define tno_HT				11
#define tno_HTDISP			12
#define tno_FFDISP			13
#define tno_VT				14
#define tno_VTDISP			15
#define tno_LFDISP			16
#define tno_EASCII			17
#define tno_LOGOUT			18
#define tno_BYTEMACRO		19
#define tno_DATAENTRY		20
#define tno_SUPDUP			21
#define tno_SUPDUPOUTPUT	22
#define tno_SENDLOCATION	23
#define tno_TERMINALTYPE	24
#define tno_ENDOFRECORD		25
#define tno_TACACS			26
#define tno_OUTPUTMARKING	27
#define tno_LOCATIONNUMBER	28
#define	tno_3270REGIME		29			/* 3270 regime */
#define	tno_X3PAD			30			/* X.3 PAD */
#define	tno_NAWS			31			/* window size */
#define	tno_TSPEED			32			/* terminal speed */
#define	tno_LFLOW			33			/* remote flow control */
#define tno_LINEMODE		34			/* Linemode option */
#define tno_XDISPLOC		35			/* X Display Location */
#define tno_OLD_ENVIRON		36			/* Old - Environment variables */
#define	tno_AUTHENTICATION	37			/* Authenticate */
#define	tno_ENCRYPT			38			/* Encryption option */
#define tno_NEW_ENVIRON		39			/* New - Environment variables */
#define tno_EXTENDEDOL		255


#define tn_EOR			239				/* end of record (transparent mode) */
#define tn_ABORT		238				/* Abort process */
#define tn_SUSP			237				/* Suspend process */
#define tn_xEOF			236				/* End of file: EOF is already used... */
#define tn_SE			240
#define tn_NOP			241
#define tn_DATAMARK		242
#define tn_BREAK		243
#define tn_INTERRUPTP	244
#define tn_ABORTOUTPUT	245
#define tn_AYT			246
#define tn_ERASECHAR	247
#define tn_ERASELINE	248
#define tn_GOAHEAD		249
#define tn_SB			250
#define tn_WILL			251
#define tn_WONT			252
#define tn_DO			253
#define tn_DONT			254
#define tn_IAC			255
#define tn_IS			0
#define tn_SEND			1


UINT CommunicateFnNULL(LPVOID pParam);

GP_comm::GP_comm(int flgDump)
{
	hSockToDelete=NULL;
	m_TerminalID=0;
	FillMemory(&ovr,sizeof(ovr),0);
	FillMemory(&ovw,sizeof(ovw),0);

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

	GPSectionName="COMSETLIST\\2";
	com_type=GPCT_SOCKET;

	m_uLockEventsEcho=1;
	m_flgDump=flgDump;
	SendFlag=GPCSF_SEND;
	InitializeCriticalSection(&m_CS);
	logf=NULL;
	maxBLOCK=0;
	TandemFlag=FALSE;
	nCharDump=nLineDump=0;
	LastSendChar=LastReadChar=0;
	DelayBeforeSendChar=2;
	DelayBeforeSendLine=2;
	DelayBeforeSendBlock=2;
	DelayAfterSendChar=2;
	DelayAfterSendLine=2;
	DelayAfterSendBlock=2;
	strcpy(DumpFileName,"DUMP.LOG");
	m_FileErrorLog=NULL;
	ErrorLogFileName="SOCKERROR.LOG";
	m_uId=0;

	UniSocket=NULL;
	hComm=NULL;
	hSock=NULL;
	dwUseSSH=0;
	FillMemory(&dcb,sizeof(dcb),0);
	dcb.DCBlength=sizeof(dcb);
	m_DumpPrefix="        :";
}

void GP_comm::Set_comm(const char *i_comname, DWORD dwFlags)
{
	GPSectionName="COMSETLIST\\";
	GPSectionName+=i_comname;
	GPClose();
	load_dcb(dwFlags);
}

GP_comm::~GP_comm()
{
	GPClose();

	if (logf!=NULL) GPStopDump();
	EndErrorLog();

	if (ovr.hEvent)
		CloseHandle(ovr.hEvent);
	ovr.hEvent=NULL;

	if (ovw.hEvent)
		CloseHandle(ovw.hEvent);
	ovw.hEvent=NULL;


	DeleteCriticalSection(&m_CS);
}

#include "GPDlgCommtype.h"

void GP_comm::load_dcb(BOOL Flg)
{
	if (GPSectionName!="temporary")
	{
		EnterCriticalSection(&m_CS);
		try
		{
			CWinApp* pApp = AfxGetApp();
			pApp->GetProfileString(GPSectionName, "COMMENT","");

	//		if (strcmp(pApp->GetProfileString(GPSectionName, "COMMENT","initial"),"initial")==0 && Flg==FALSE)
	//		{
	//			GPDlgCommtype dlgc;
	//			dlgc.DoModal();
	//		}

			Set_commType(pApp->GetProfileInt(GPSectionName, "com_type",com_type));

			GPcomment=pApp->GetProfileString(GPSectionName, "COMMENT","");
	#ifdef BRIZ
			InitStr=pApp->GetProfileString(GPSectionName, "InitStr","dm\\ndm\\n");
	#else
			InitStr=pApp->GetProfileString(GPSectionName, "InitStr","pickvm\\n");
	#endif
			EndStr=pApp->GetProfileString(GPSectionName, "EndStr","");

			m_TerminalID	 = pApp->GetProfileInt(GPSectionName, "TerminalID"	,0);

			DumpMode	 = pApp->GetProfileInt(GPSectionName, "DumpMode"	,7);
			maxnLineDump = pApp->GetProfileInt(GPSectionName, "maxnLineDump",40);
			maxnCharDump = pApp->GetProfileInt(GPSectionName, "maxnCharDump",120);
			maxBLOCK	 = pApp->GetProfileInt(GPSectionName, "maxnComBlock",0);
			LoadDelimiters();
			dwUseSSH	= pApp->GetProfileInt(GPSectionName, "SSHFlag",0);

			switch(com_type)
			{
			case GPCT_COMPORT:
				strcpy(GPcomport,pApp->GetProfileString(GPSectionName, "COMPORT","COM1"));
				dcb.BaudRate		= pApp->GetProfileInt(GPSectionName, "BaudRate",38400);
				dcb.ByteSize		= (unsigned char)pApp->GetProfileInt(GPSectionName, "ByteSize",8);
				dcb.EofChar			= (char)pApp->GetProfileInt(GPSectionName, "EofChar",0);
				dcb.ErrorChar		= (char)pApp->GetProfileInt(GPSectionName, "ErrorChar",32);
				dcb.EvtChar			= (char)pApp->GetProfileInt(GPSectionName, "EvtChar",0);
				dcb.fAbortOnError	= pApp->GetProfileInt(GPSectionName, "fAbortOnError",0);
				dcb.fBinary			= pApp->GetProfileInt(GPSectionName, "fBinary",1);
				dcb.fDsrSensitivity = pApp->GetProfileInt(GPSectionName, "fDsrSensitivity",0);
				dcb.fDtrControl		= pApp->GetProfileInt(GPSectionName, "fDtrControl",DTR_CONTROL_DISABLE);
				dcb.fDummy2			= pApp->GetProfileInt(GPSectionName, "fDummy2",0);
				dcb.fErrorChar		= pApp->GetProfileInt(GPSectionName, "fErrorChar",0);
				dcb.fInX			= pApp->GetProfileInt(GPSectionName, "fInX",0);
				dcb.fNull			= pApp->GetProfileInt(GPSectionName, "fNull",0);
				dcb.fOutX			= pApp->GetProfileInt(GPSectionName, "fOutX",0);
				dcb.fOutxCtsFlow	= pApp->GetProfileInt(GPSectionName, "fOutxCtsFlow",0);
				dcb.fOutxDsrFlow	= pApp->GetProfileInt(GPSectionName, "fOutxDsrFlow",0);
				dcb.fRtsControl		= pApp->GetProfileInt(GPSectionName, "fRtsControl",RTS_CONTROL_DISABLE);
				dcb.fTXContinueOnXoff = pApp->GetProfileInt(GPSectionName, "fTXContinueOnXoff",0);
				dcb.Parity			= (unsigned char)pApp->GetProfileInt(GPSectionName, "Parity",NOPARITY);
				dcb.fParity			= pApp->GetProfileInt(GPSectionName, "fParity",0);
				dcb.StopBits		= (unsigned char)pApp->GetProfileInt(GPSectionName, "StopBits",ONESTOPBIT);
		//		dcb.wReserved		= pApp->GetProfileInt(GPSectionName, "wReserved",0);
				dcb.wReserved1		= (WORD)pApp->GetProfileInt(GPSectionName, "wReserved1",0);
				dcb.XoffChar		= (char)pApp->GetProfileInt(GPSectionName, "XoffChar",14);
				dcb.XoffLim			= (WORD)pApp->GetProfileInt(GPSectionName, "XoffLim",32536);
				dcb.XonChar			= (char)pApp->GetProfileInt(GPSectionName, "XonChar",15);
				dcb.XonLim			= (WORD)pApp->GetProfileInt(GPSectionName, "XonLim",32536);
				m_TelnetFlag		= pApp->GetProfileInt(GPSectionName, "TelnetFlag",0);
				break;
			case GPCT_SOCKET:
	#ifdef BRIZ
				GPHostName=pApp->GetProfileString(GPSectionName, "HostName","127.0.0.1");
	#else
				GPHostName=pApp->GetProfileString(GPSectionName, "HostName","10.100.0.7");
	#endif
				DelayBeforeSendChar	=pApp->GetProfileInt(GPSectionName, "DelayBeforeSendChar",	0);
				DelayBeforeSendLine	=pApp->GetProfileInt(GPSectionName, "DelayBeforeSendLine",	0);
				DelayBeforeSendBlock=pApp->GetProfileInt(GPSectionName, "DelayBeforeSendBlock",	0);
				DelayAfterSendChar	=pApp->GetProfileInt(GPSectionName, "DelayAfterSendChar",	0);
				DelayAfterSendLine	=pApp->GetProfileInt(GPSectionName, "DelayAfterSendLine",	0);
				DelayAfterSendBlock	=pApp->GetProfileInt(GPSectionName, "DelayAfterSendBlock",	0);
				PortNum				=pApp->GetProfileInt(GPSectionName, "PortNumber",	23);
				m_TelnetFlag		=pApp->GetProfileInt(GPSectionName, "TelnetFlag",0xFFFFFFFF);

				if (dwUseSSH && UniSocket)
				{
					DLL_SSH_Config mcfg=UniSocket->GetConfig();

					mcfg.sshprot=pApp->GetProfileInt(GPSectionName,"SSH_PROTOCOL",2);
					mcfg.change_username=pApp->GetProfileInt(GPSectionName,"SSH_ALLOWUSERCHANGE",0);
					mcfg.compression=pApp->GetProfileInt(GPSectionName,"SSH_ENABLECOMPRESSION",0);
					mcfg.nopty=pApp->GetProfileInt(GPSectionName,"SSH_DONTPTERMINAL",0);
					mcfg.agentfwd=pApp->GetProfileInt(GPSectionName,"SSH_AGENTFORWARDING",0);
					strcpy(mcfg.host, GPHostName);
					mcfg.port = PortNum; 

					mcfg.x11_auth=pApp->GetProfileInt(GPSectionName,"SSH_X11_MIT_XDM",DLL_SSH_X11_MIT);
					strncpy(mcfg.remote_cmd,pApp->GetProfileString(GPSectionName, "SSH_EDITREMOTECOMMAND",""),511);
					mcfg.remote_cmd[511]=0;
					mcfg.try_tis_auth=pApp->GetProfileInt(GPSectionName,"SSH_CHECKTISAUTO",0);
					mcfg.try_ki_auth=pApp->GetProfileInt(GPSectionName,"SSH_CHECKKEYBOARDAUTO",0);
					strncpy(mcfg.keyfile.path,pApp->GetProfileString(GPSectionName, "SSH_EDITPRIVATEKEYFILE",""),FILENAME_MAX);
					mcfg.keyfile.path[FILENAME_MAX-1]=0;
					mcfg.x11_forward=pApp->GetProfileInt(GPSectionName,"SSH_CHECKFORWARDX11",0);
					strncpy(mcfg.x11_display,pApp->GetProfileString(GPSectionName, "SSH_EDITXLOCATION",""),127);
					mcfg.x11_display[127]=0;

					mcfg.ssh_no_shell=pApp->GetProfileInt(GPSectionName,"SSH_DONTCOMMAND",0);

					mcfg.lport_acceptall=pApp->GetProfileInt(GPSectionName,"SSH_CHECKCONFROMOTHERHOSTS",0);
					mcfg.rport_acceptall=pApp->GetProfileInt(GPSectionName,"SSH_CHECKREMOTEPORTDOSAME",0);

 
					mcfg.portfwd;
					CString csTmp=AfxGetApp()->GetProfileString(GPSectionName,	"SSH_FORWARDPORTS","");
					CString csTmp2;
					int i=0;
					char *pportfwd=mcfg.portfwd;
					int pfcmplen=1023;
					char *m_lastpportfwd=pportfwd;
					while((csTmp2=ExtractField(csTmp,++i,"\x01"))!="")
					{
						if (csTmp2.GetLength()<1024-(m_lastpportfwd-mcfg.portfwd))
						{
							CString cs2=ExtractField(csTmp2,1,"\x02");
							if (cs2=="Remote")		strcpy(pportfwd,"[R]");
							else
							if (cs2=="Dynamic")	strcpy(pportfwd,"[D]");
							else				strcpy(pportfwd,"[L]");

							pportfwd+=(int)strlen(pportfwd);
							cs2=ExtractField(csTmp2,2,"\x02");
							if (cs2=="IPv4")	strcpy(pportfwd,"[4]");
							else
							if (cs2=="IPv6")	strcpy(pportfwd,"[6]");
							else				strcpy(pportfwd,"[A]");

							pportfwd+=(int)strlen(pportfwd);
							strcpy(pportfwd,ExtractField(csTmp2,3,"\x02"));
							pportfwd+=(int)strlen(pportfwd);
							cs2=ExtractField(csTmp2,4,"\x02");
							if (cs2!="") 
							{
								*(pportfwd++)=':';
								strcpy(pportfwd,cs2);
							}
							pportfwd+=(int)strlen(pportfwd);
							m_lastpportfwd=pportfwd+1;
						}
					}
					*m_lastpportfwd=0;

					mcfg.ssh_rekey_time=pApp->GetProfileInt(GPSectionName,"SSH_REKEY_TIME",0);
					DWORD nData=pApp->GetProfileInt(GPSectionName,"SSH_REKEY_DATA",0);
					if (nData>999)
						sprintf(mcfg.ssh_rekey_data,"%dG",nData/1000);
					else
						sprintf(mcfg.ssh_rekey_data,"%dM",nData);

					DWORD tmpDW=pApp->GetProfileInt(GPSectionName,"SSH_CIPHERS",DLL_SSH_KEX_DHGEX+DLL_SSH_KEX_DHGROUP1*0x8+DLL_SSH_KEX_DHGROUP14*0x40+DLL_SSH_KEX_WARN*0x200);
					for(i=0;i<DLL_SSH_CIPHER_MAX;i++)
					{
						mcfg.ssh_cipherlist[i]=tmpDW&0x7;
						tmpDW/=0x8;
					}

					
					tmpDW=	pApp->GetProfileInt(GPSectionName,"SSH_KEXES",DLL_SSH_CIPHER_3DES+DLL_SSH_CIPHER_BLOWFISH*0x8+DLL_SSH_CIPHER_DES*0x40+DLL_SSH_CIPHER_AES*0x200+DLL_SSH_CIPHER_WARN*0x1000);

					for(i=0;i<DLL_SSH_KEX_MAX;i++)
					{
						mcfg.ssh_kexlist[i]=tmpDW&0x7;
						tmpDW/=0x8;
					}


					mcfg.ssh2_des_cbc=	pApp->GetProfileInt(GPSectionName,"SSH2_DES_CBC",0);
					UniSocket->SetConfig(mcfg);
				}
				break;
			}


			if (pApp->GetProfileInt(GPSectionName, "ErrorLogging",	0)!=0)
				StartErrorLog();

			SetLockEventsEcho(pApp->GetProfileInt(GPSectionName, "LockEventsEcho",	0));
			m_DumpPrefix=pApp->GetProfileString(GPSectionName, "m_DumpPrefix","        :");
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "Load_dcb",GPSectionName);
		}


		ChechAndDelete(ExtractField(GPSectionName,2,"\\"));

		LeaveCriticalSection(&m_CS);
	}
}

void GP_comm::write_dcb()
{
	EnterCriticalSection(&m_CS);
	try
	{
		CWinApp* pApp = AfxGetApp();

		if (GPcomment=="initial") GPcomment="";
		pApp->WriteProfileInt	(GPSectionName, "com_type",com_type);

		pApp->WriteProfileString(GPSectionName, "COMMENT",GPcomment);
		pApp->WriteProfileString(GPSectionName, "InitStr",InitStr);
		pApp->WriteProfileString(GPSectionName, "EndStr",EndStr);

		pApp->WriteProfileInt	(GPSectionName, "TerminalID",m_TerminalID);

		pApp->WriteProfileInt	(GPSectionName, "DumpMode",DumpMode);
		pApp->WriteProfileInt	(GPSectionName, "maxnLineDump",maxnLineDump);
		pApp->WriteProfileInt	(GPSectionName, "maxnCharDump",maxnCharDump);
		pApp->WriteProfileInt	(GPSectionName, "maxnComBlock",maxBLOCK);
		SaveDelimiters();

		switch(com_type)
		{
		case GPCT_COMPORT:
			pApp->WriteProfileString(GPSectionName, "COMPORT",GPcomport);
			pApp->WriteProfileInt(GPSectionName, "BaudRate",dcb.BaudRate);
			pApp->WriteProfileInt(GPSectionName, "ByteSize",dcb.ByteSize);
			pApp->WriteProfileInt(GPSectionName, "EofChar",dcb.EofChar);
			pApp->WriteProfileInt(GPSectionName, "ErrorChar",dcb.ErrorChar);
			pApp->WriteProfileInt(GPSectionName, "EvtChar",dcb.EvtChar);
			pApp->WriteProfileInt(GPSectionName, "fAbortOnError",dcb.fAbortOnError);
			pApp->WriteProfileInt(GPSectionName, "fBinary",dcb.fBinary);
			pApp->WriteProfileInt(GPSectionName, "fDsrSensitivity",dcb.fDsrSensitivity);
			pApp->WriteProfileInt(GPSectionName, "fDtrControl",dcb.fDtrControl);
			pApp->WriteProfileInt(GPSectionName, "fDummy2",dcb.fDummy2);
			pApp->WriteProfileInt(GPSectionName, "fErrorChar",dcb.fErrorChar);
			pApp->WriteProfileInt(GPSectionName, "fInX",dcb.fInX);
			pApp->WriteProfileInt(GPSectionName, "fNull",dcb.fNull);
			pApp->WriteProfileInt(GPSectionName, "fOutX",dcb.fOutX);
			pApp->WriteProfileInt(GPSectionName, "fOutxCtsFlow",dcb.fOutxCtsFlow);
			pApp->WriteProfileInt(GPSectionName, "fOutxDsrFlow",dcb.fOutxDsrFlow);
			pApp->WriteProfileInt(GPSectionName, "fRtsControl",dcb.fRtsControl);
			pApp->WriteProfileInt(GPSectionName, "fTXContinueOnXoff",dcb.fTXContinueOnXoff);
			pApp->WriteProfileInt(GPSectionName, "Parity",dcb.Parity);
			pApp->WriteProfileInt(GPSectionName, "fParity",dcb.fParity);
			pApp->WriteProfileInt(GPSectionName, "StopBits",dcb.StopBits);
	//		pApp->WriteProfileInt(GPSectionName, "wReserved",dcb.wReserved);
			pApp->WriteProfileInt(GPSectionName, "wReserved1",dcb.wReserved1);
			pApp->WriteProfileInt(GPSectionName, "XoffChar",dcb.XoffChar);
			pApp->WriteProfileInt(GPSectionName, "XoffLim",dcb.XoffLim);
			pApp->WriteProfileInt(GPSectionName, "XonChar",dcb.XonChar);
			pApp->WriteProfileInt(GPSectionName, "XonLim",dcb.XonLim);
			break;
		case GPCT_SOCKET:
			pApp->WriteProfileString(GPSectionName, "HostName",GPHostName);
			pApp->WriteProfileInt(GPSectionName, "DelayBeforeSendChar",	DelayBeforeSendChar);
			pApp->WriteProfileInt(GPSectionName, "DelayBeforeSendLine",	DelayBeforeSendLine);
			pApp->WriteProfileInt(GPSectionName, "DelayBeforeSendBlock",DelayBeforeSendBlock);
			pApp->WriteProfileInt(GPSectionName, "DelayAfterSendChar",	DelayAfterSendChar);
			pApp->WriteProfileInt(GPSectionName, "DelayAfterSendLine",	DelayAfterSendLine);
			pApp->WriteProfileInt(GPSectionName, "DelayAfterSendBlock",	DelayAfterSendBlock);
			pApp->WriteProfileInt(GPSectionName, "PortNumber",	PortNum);
			break;
		}

		pApp->WriteProfileInt(GPSectionName, "ErrorLogging",IsErrorLog());
		pApp->WriteProfileInt(GPSectionName, "LockEventsEcho",GetLockEventsEcho());
		pApp->WriteProfileString(GPSectionName, "m_DumpPrefix",(LPCSTR)m_DumpPrefix);
		pApp->WriteProfileInt(GPSectionName, "TelnetFlag",m_TelnetFlag);
		pApp->WriteProfileInt(GPSectionName, "SSHFlag",dwUseSSH);
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "write_dcb","");
	}

	LeaveCriticalSection(&m_CS);
}


void GP_comm::GPClose()
{
	EnterCriticalSection(&m_CS);
	try
	{
		if (hComm!=NULL) {CloseHandle(hComm); hComm=NULL;}
		if (hSock!=NULL) 
		{
			if ((m_ConnectionFlag&0x1)==0)
				hSock->Close();
			delete hSock;
			hSock=NULL;
		}
		if (UniSocket!=NULL) 
		{
			if ((m_ConnectionFlag&0x1)==0)
				UniSocket->Close();
			delete UniSocket;
			UniSocket=NULL;
		}
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "GPClose","480");
	}
	if (hSockToDelete)
	{
		try
		{
			hSockToDelete->Close();
			delete hSockToDelete;
			hSockToDelete=NULL;
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "GPClose","492");
		}
	}
	LeaveCriticalSection(&m_CS);
}


BOOL GP_comm::GPConnect()
{
	load_dcb();
	BOOL ret=TRUE;

//	GPStartDump();

	EnterCriticalSection(&m_CS);
	try
	{
		if (m_ConnectionFlag==0)
		{
			switch(com_type)
			{
			case GPCT_COMPORT:
				if (hComm==NULL) hComm=CreateFile(GPcomport,GENERIC_READ|GENERIC_WRITE,0,0,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,0);
				if (hComm==INVALID_HANDLE_VALUE || !SetCommState(hComm,&dcb))
		#ifdef RUS
					{	hComm=NULL; MessageBox(NULL,"Ошибка обращения к порту",GPC.ErrBoxCaption,MB_OK|MB_ICONSTOP|MB_APPLMODAL|MB_SYSTEMMODAL);	ret=FALSE;}
		#else
					{	hComm=NULL; MessageBox(NULL,"IO Error",GPC.ErrBoxCaption,MB_OK|MB_ICONSTOP|MB_APPLMODAL|MB_SYSTEMMODAL);	ret=FALSE;}
		#endif

				break;
			case GPCT_SOCKET:
				if (dwUseSSH)
				{
					if (UniSocket!=NULL) 
					{
						UniSocket->Close();
						delete UniSocket;
					}
					UniSocket=new CUniSocket(this);
					UniSocket->InitUniSocket(GPHostName,PortNum);
				}
				else
				{
					if (hSock!=NULL) 
					{
						hSock->Close();
						delete hSock;
					}
					hSock=new CGPAsyncSocket;
					hSock->Create();
					if (hSock->Connect(GPHostName,PortNum)<=0) ret=FALSE;
					else
					{
						char cc[]={0xFF, 0xFB, 0x1F, /*0xFF, 0xFB, 0x18,*/ 0xFF, 0xFB, 0x27};
						hSock->Send(cc,sizeof(cc),0);

					}
				}
				break;
			}
		}
		else
		{
			m_ConnectionFlag|=0x10000;
			if (hSock)
			{
				if (hSockToDelete)
				{
					try
					{
						hSockToDelete->Close();
						delete hSockToDelete;
						hSockToDelete=NULL;
					}
					catch(...)
					{
						GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "GPConnect","563");
					}
				}
				AfxBeginThread(CommunicateFnNULL,(LPVOID)hSock);
				hSockToDelete=hSock;
			}

			hSock=new CGPAsyncSocket;
			GPC.m_View->BeginListen();
		}
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "GPConnect","576");
	}

	LeaveCriticalSection(&m_CS);
	return ret;
}

CGPInputPool *GP_comm::AltInputAccess()
{
	EnterCriticalSection(&m_CS);
	return &m_AlternateInput;
}
void GP_comm::AltInputRelease()
{
	LeaveCriticalSection(&m_CS);
}



UINT GP_comm::GPRead(char *inputbuf, UINT nread)
{
	UINT nb=0;
	int snb=0;

	EnterCriticalSection(&m_CS);
	try
	{
		UINT nre=m_AlternateInput.GetReadLength();
		if (nre)
		{
			nb=m_AlternateInput.GetData((BYTE **)&inputbuf,nread);
		}
		else
		{
			switch(com_type)
			{
			case GPCT_COMPORT:
				if (hComm!=NULL)
				{
					DWORD nbr=0;
					COMSTAT cs;
					DWORD ner;
					ClearCommError(hComm,&ner,&cs);
					if ((nre=cs.cbInQue)>0)
					{
						GPC.m_View->m_LastActivity=CTime::GetCurrentTime();
						if (nre>nread) nre=nread;
						ReadFile(hComm, inputbuf, nre,  &nbr,	&ovr);
						if (GPC.DlgStatistics) GPC.DlgStatistics->SAddReadCount(nbr);
						if (logf!=NULL)
						{
							UINT itmp;
							for(itmp=0;itmp<nre;itmp++)
								PrintDmp(inputbuf[itmp],1,GPC_DUMPIN);
						}
						LastReadChar=inputbuf[nre-1];
						nb=nre;
					}
				}
				else nb=0;
				break;
			case GPCT_SOCKET:
				if (dwUseSSH)
				{
					if (UniSocket == NULL)
					{
						// end
						snb=1234567890;
						//snb = 0;
					}
					else
					{
						snb = UniSocket->Receive(inputbuf,nread);
						if (UniSocket->IsSessionClose())
						{
							delete UniSocket;
							UniSocket = NULL;
						}
						GPC.m_View->m_LastActivity=CTime::GetCurrentTime();
					}
				}
				else
				{
					if (hSock==NULL) GPConnect();
					if (hSock==NULL)
					{
						// end
						snb=1234567890;
					}
					else
					{
						if ((snb=hSock->Receive(inputbuf,nread))==SOCKET_ERROR)
						{
							GPC.m_View->m_LastActivity=CTime::GetCurrentTime();
							switch(ErrDispRead(inputbuf,snb))
							{
							case WSANOTINITIALISED:	// A successful AfxSocketInit must occur before using this API.
								LeaveCriticalSection(&m_CS);
								return 1234567890;/*end*/
							case WSAENETDOWN:		// The Windows Sockets implementation detected that the network subsystem failed.
								LeaveCriticalSection(&m_CS);
								return 1234567890;/*end*/
							case WSAENOTCONN:		// The socket is not connected.
								LeaveCriticalSection(&m_CS);
								return 1234567890;/*end*/
							case WSAEINPROGRESS:	// A blocking Windows Sockets operation is in progress.
								LeaveCriticalSection(&m_CS);
								return 1234567890;/*end*/
							case WSAENOTSOCK:		// The descriptor is not a socket.
								LeaveCriticalSection(&m_CS);
								return 1234567890;/*end*/
							case WSAEOPNOTSUPP:		// MSG_OOB was specified, but the socket is not of type SOCK_STREAM.
								LeaveCriticalSection(&m_CS);
								return 1234567890;/*end*/
							case WSAESHUTDOWN:		// The socket has been shut down; it is not possible to call Receive on a socket after ShutDown has been invoked with nHow set to 0 or 2.
								LeaveCriticalSection(&m_CS);
								return 1234567890;/*end*/
							case WSAEMSGSIZE:		// The datagram was too large to fit into the specified buffer and was truncated.
								LeaveCriticalSection(&m_CS);
								return 1234567890;/*end*/
							case WSAEINVAL:			// The socket has not been bound with Bind.
								LeaveCriticalSection(&m_CS);
								return 1234567890;/*end*/
							case WSAECONNABORTED:	// The virtual circuit was aborted due to timeout or other failure.
								LeaveCriticalSection(&m_CS);
								return 1234567890;/*end*/
							case WSAECONNRESET:		// The virtual circuit was reset by the remote side.
								LeaveCriticalSection(&m_CS);
								return 1234567890;/*end*/
							case WSAEWOULDBLOCK:	// The socket is marked as nonblocking and the Receive operation would block.
								break;
							}

						}
						if (snb==0) {LeaveCriticalSection(&m_CS);return 1234567890;/*end*/}
						if (snb<0) snb=0; // error
					}
				}

				if (logf!=NULL)
				{
					int itmp;
					for(itmp=0;itmp<snb;itmp++)
						PrintDmp(inputbuf[itmp],1,GPC_DUMPIN);
				}
				nb=snb;
				if ((nb!=0) && (nb!=1234567890))
				{
					UINT i,n255=0,curp,outp;
					if (GPC.DlgStatistics) GPC.DlgStatistics->SAddReadCount(nb);

					if ((m_TelnetFlag&0x1)!=0)
						for(i=0;i<nb;i++) if (inputbuf[i]==tn_IAC) n255++;

					if (n255!=0)
					{
						char *repl=new char [n255*4+256];
						for(i=0,curp=0,outp=0;i<nb;i++)
							if (inputbuf[i]!=tn_IAC) inputbuf[curp++]=inputbuf[i];
							else
							{
								if (inputbuf[++i]==tn_IAC || i>=nb) inputbuf[curp++]=255;
								else
								{
									if (m_flgDump)
									{
										FILE *tmpf;
										tmpf=fopen("telopt.log","a+");
										if (tmpf)
										{
											fprintf(tmpf,"<<< %d %d %d %d %d %d\n",tn_IAC,inputbuf[i],inputbuf[i+1],inputbuf[i+2],inputbuf[i+3],inputbuf[i+4]);
											fclose(tmpf);
										}
									}

									switch(inputbuf[i++])
									{
									case tn_DO:
										switch(inputbuf[i])
										{
										case tno_TERMINALTYPE:
											repl[outp++]=tn_IAC;
											repl[outp++]=tn_WILL;
											repl[outp++]=inputbuf[i];
											if (m_FileErrorLog)  fprintf(m_FileErrorLog,"TELNET_NEGO>>> %d %d %d\n",tn_IAC,tn_WILL,inputbuf[i]);
											break;
										case tno_ECHO:
											repl[outp++]=tn_IAC;
											repl[outp++]=tn_WILL;
											repl[outp++]=inputbuf[i];
											if (m_FileErrorLog)  fprintf(m_FileErrorLog,"TELNET_NEGO>>> %d %d %d\n",tn_IAC,tn_WILL,inputbuf[i]);
											break;
										case tno_NAWS:
											repl[outp++]=tn_IAC;
											repl[outp++]=tn_WILL;
											repl[outp++]=inputbuf[i];
											{
												Size sz=GPC.m_Document->GetActiveScrSize();
												repl[outp++]=tn_IAC;
												repl[outp++]=tn_SB;
												repl[outp++]=tno_NAWS;
												repl[outp++]=(unsigned char)(sz.Width >> 8);
												repl[outp++]=(unsigned char)(sz.Width & 0xFF);
												repl[outp++]=(unsigned char)(sz.Height >> 8);
												repl[outp++]=(unsigned char)(sz.Height & 0xFF);
												repl[outp++]=tn_IAC;
												repl[outp++]=tn_SE;
												if (m_FileErrorLog)  fprintf(m_FileErrorLog,"TELNET_NEGO>>> %d %d %d %d %d %d %d %d %d %d\n",tn_IAC,tn_SB,tno_NAWS,tn_IS,(char)(sz.Width >> 8),sz.Width & 0xFF,(char)(sz.Height >> 8),sz.Height & 0xFF,tn_IAC,tn_SE);
											}

											break;
										default:
											repl[outp++]=tn_IAC;
											if (logf) 
												PrintDmp(tn_IAC,1,GPC_DUMPOUT);
											repl[outp++]=tn_WONT;
											if (logf) 												PrintDmp(tn_WONT,1,GPC_DUMPOUT);
											repl[outp++]=inputbuf[i];
											if (logf) 												PrintDmp(inputbuf[i],1,GPC_DUMPOUT);
											if (m_FileErrorLog)  fprintf(m_FileErrorLog,"TELNET_NEGOdef>>> %d %d %d\n",tn_IAC,tn_WONT,inputbuf[i]);
											break;
										}
										break;
									case tn_WONT:
										switch(inputbuf[i])
										{
											case tno_ECHO:
												repl[outp++]=tn_IAC;
												repl[outp++]=tn_WONT;
												repl[outp++]=inputbuf[i];
												if (m_FileErrorLog)  fprintf(m_FileErrorLog,"TELNET_NEGO>>> %d %d %d\n",tn_IAC,tn_WONT,inputbuf[i]);
												break;
										}
										break;
									case tn_DONT:
										switch(inputbuf[i])
										{
											case tno_ECHO:
												repl[outp++]=tn_IAC;
												repl[outp++]=tn_WONT;
												repl[outp++]=inputbuf[i];
												if (m_FileErrorLog)  fprintf(m_FileErrorLog,"TELNET_NEGO>>> %d %d %d\n",tn_IAC,tn_WONT,inputbuf[i]);
												break;
										}
										break;
									case tn_WILL:
										switch(inputbuf[i])
										{
										case tno_ECHO:
											repl[outp++]=tn_IAC;
											repl[outp++]=tn_DO;
											repl[outp++]=inputbuf[i];
											if (m_FileErrorLog)  fprintf(m_FileErrorLog,"TELNET_NEGOdef>>> %d %d %d\n",tn_IAC,tn_DO,inputbuf[i]);
											break;
										default:
											repl[outp++]=tn_IAC;
											if (logf)	PrintDmp(tn_IAC,1,GPC_DUMPOUT);
											repl[outp++]=tn_DONT;
											if (logf)	PrintDmp(tn_DONT,1,GPC_DUMPOUT);
											repl[outp++]=inputbuf[i];
											if (logf)	PrintDmp(inputbuf[i],1,GPC_DUMPOUT);
											if (m_FileErrorLog)  fprintf(m_FileErrorLog,"TELNET_NEGOdef>>> %d %d %d\n",tn_IAC,tn_DONT,inputbuf[i]);
											break;
										}
										break;
									case tn_SB:
										switch(inputbuf[i])
										{
										case tno_TERMINALTYPE:
											if (inputbuf[i+1]==tn_SEND) i++;
											if (inputbuf[i+1]==tn_IAC) i++;
											if (inputbuf[i+1]==tn_SE) i++;
											repl[outp++]=tn_IAC;
											repl[outp++]=tn_SB;
											repl[outp++]=tno_TERMINALTYPE;
											repl[outp++]=tn_IS;
											if (m_TermCap.GetCurrentTerminal())
												strcpy(repl+outp,m_TermCap.GetCurrentTerminal()->AlternateNames);
											outp+=(int)strlen(repl+outp);
											repl[outp++]=tn_IAC;
											repl[outp++]=tn_SE;
											if (m_FileErrorLog)  fprintf(m_FileErrorLog,"TELNET_NEGO>>> %d %d %d %d\n",tn_IAC,tn_SB,tno_TERMINALTYPE,tn_IS);
											break;

										default:
											if (m_FileErrorLog)  fprintf(m_FileErrorLog,"TELNET_NEGOdef>>>nothing\n");
											break;
										}
										break;
									default:
										repl[outp++]=tn_IAC;
										if (logf)	PrintDmp(tn_IAC,1,GPC_DUMPOUT);
										repl[outp++]=tn_WONT;
										if (logf)	PrintDmp(tn_WONT,1,GPC_DUMPOUT);
										repl[outp++]=inputbuf[i];
										if (logf)	PrintDmp(inputbuf[i],1,GPC_DUMPOUT);
										if (m_FileErrorLog)  fprintf(m_FileErrorLog,"TELNET_NEGOdef>>> %d %d %d\n",tn_IAC,tn_WONT,inputbuf[i]);
										break;
									}

									if (outp>0)
									{
										if (GPC.DlgStatistics) GPC.DlgStatistics->SAddSendCount(outp);

										int tmpnb=SOCKET_ERROR;
										if (dwUseSSH)
										{
											if (UniSocket) tmpnb=UniSocket->Send(repl,outp);
										}
										else
											if (hSock) tmpnb=hSock->Send(repl,outp);

										int nerrcnt=0;
										while(tmpnb==SOCKET_ERROR && ++nerrcnt<50)
										{
											if (GetLastError()!=WSAEWOULDBLOCK)	
											{
												ErrDispWrite(repl,outp); break;
											}
											else
											{
												GPC.m_View->DoRemappingInput();
												GPC.Release_m_MuteProc();
												Sleep(100);
												GPC.m_View->DoRemappingInput();
												GPC.WaitFor_m_MuteProc();
												if (dwUseSSH)
												{
													if (UniSocket) tmpnb=UniSocket->Send(repl,outp);
												}
												else
													if (hSock) tmpnb=hSock->Send(repl,outp);
											}
										}
										if (nerrcnt>=50) ErrDispWrite(repl,outp); 

										if (logf)
										{
											UINT i11;
											for(i11=0;i11<outp;i11++)
												PrintDmp(repl[i11],1,GPC_DUMPOUT);
										}
										outp=0;
									}
								}
							}
						nb=curp;
						delete[] repl;
					}

					if (nb>0) LastReadChar=inputbuf[nb-1];
				}
				break;
			}
		}
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "GPRead","");
	}

	LeaveCriticalSection(&m_CS);
	return nb;
}


BOOL GP_comm::GPSendChar(const char ch)
{
	EnterCriticalSection(&m_CS);
	BOOL ret=FALSE;

	try
	{
		char buff[4];
		buff[0]=ch;

		switch(com_type+SendFlag)
		{
		case GPCT_COMPORT:
			if (hComm!=NULL && TandemFlag==FALSE)
			{
				DWORD nb;
				if (logf && (DumpMode&GPC_DUMPOUT))
					PrintDmp(ch,1,GPC_DUMPOUT);
				WriteFile(hComm,buff,1,&nb,&ovw);
				if (GPC.DlgStatistics) GPC.DlgStatistics->SAddSendCount(nb);
				ret=TRUE;
				LastSendChar=ch;
			}
			break;
		case GPCT_SOCKET:
			if ((hSock || UniSocket) && TandemFlag==FALSE)
			{
				UINT nb=1;
				if (logf && (DumpMode&GPC_DUMPOUT))
					PrintDmp(ch,1,GPC_DUMPOUT);
				if (DelayBeforeSendChar>0) Sleep(DelayBeforeSendChar);
				if (ch==255 && (m_TelnetFlag&0x1)) {buff[1]=255;nb++;}
				int err;
				if (GPC.DlgStatistics) GPC.DlgStatistics->SAddSendCount(nb);
				if ((err=(dwUseSSH)?UniSocket->Send(buff,nb):hSock->Send(buff,nb))==1)	ret=TRUE;
				int nerrcnt=0;
				while(err==SOCKET_ERROR && ++nerrcnt<50)
				{
					if (GetLastError()!=WSAEWOULDBLOCK)	
					{
						ErrDispWrite(buff,nb); break;
					}
					else
					{
						GPC.m_View->DoRemappingInput();
						GPC.Release_m_MuteProc();
						Sleep(100);
						GPC.m_View->DoRemappingInput();
						GPC.WaitFor_m_MuteProc();
						err=(dwUseSSH)?UniSocket->Send(buff,nb):hSock->Send(buff,nb);
					}
				}

				if (nerrcnt>=50) ErrDispWrite(buff,nb);

				LastSendChar=ch;
				if (DelayAfterSendChar>0) Sleep(DelayAfterSendChar);
			}
			break;
		}
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "GPSendChar","");
	}
	GPC.m_View->m_LastActivity=CTime::GetCurrentTime();
	LeaveCriticalSection(&m_CS);

	return ret;
}


UINT GP_comm::GPSendLine(const char *ch)
{
	UINT ret=0;
	if (TandemFlag==FALSE)
		switch(com_type+SendFlag)
		{
		case GPCT_COMPORT:
			if (hComm!=NULL)
			{
				if (maxBLOCK==0)
				{
					EnterCriticalSection(&m_CS);
					try
					{
						while(*ch!=0 && GPSendChar(*ch)==TRUE)
						{
							ch++;
							ret++;
						}
					}
					catch(...)
					{
						GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "GPSendLine",ch?ch:"");
					}
					LeaveCriticalSection(&m_CS);
				}
				else
				{
					DWORD nb;
					UINT i,nByte=(int)strlen(ch);

					for(i=0;i<nByte;i+=maxBLOCK)
					{
						UINT nbtmp=(i+maxBLOCK>nByte)?nByte-i:maxBLOCK;
						if (WriteFile(hComm,ch+i,nbtmp,&nb,&ovw)==FALSE) break;
						if (GPC.DlgStatistics) GPC.DlgStatistics->SAddSendCount(nb);
						if (logf)
						{
							UINT j;
							for(j=i;j<nbtmp+i;j++)
								PrintDmp(ch[j],1,GPC_DUMPOUTBLOCK);
						}
					}
				}
			}

			break;
		case GPCT_SOCKET:
			if (hSock || UniSocket)
			{
				if (DelayBeforeSendLine>0) Sleep(DelayBeforeSendLine);
				ret=GPSendBlock(ch,(int)strlen(ch));
				if (DelayAfterSendLine>0) Sleep(DelayAfterSendLine);
			}
			break;
		}

	GPC.m_View->m_LastActivity=CTime::GetCurrentTime();
	return  ret;
}

UINT GP_comm::GPSendBlock(const char *ch, UINT nByte, BOOL BlType/* = 0*/)
{
//	char tmps[250];
//	TRACE("%s\n",ch);

	EnterCriticalSection(&m_CS);
	GPC.m_View->m_LastActivity=CTime::GetCurrentTime();
	UINT i=0;
	try
	{
	//TRACE("%s\n",ch);
		if (TandemFlag==FALSE)
			switch(com_type+SendFlag)
			{
			case GPCT_COMPORT:
				if (hComm!=NULL)
				{
					if (maxBLOCK==0)
					{
						for(i=0;i<nByte && GPSendChar(ch[i])==TRUE;i++)
							if (logf)
								PrintDmp(ch[i],1,GPC_DUMPOUTBLOCK);
					}
					else
					{
						DWORD nb;
						for(i=0;i<nByte;i+=maxBLOCK)
						{
							UINT nbtmp=(i+maxBLOCK>nByte)?nByte-i:maxBLOCK;
							if (WriteFile(hComm,ch+i,nbtmp,&nb,&ovw)==FALSE) break;
							if (GPC.DlgStatistics) GPC.DlgStatistics->SAddSendCount(nb);
							if (logf)
							{
								UINT j;
								for(j=i;j<nbtmp+i;j++)
									PrintDmp(ch[j],1,GPC_DUMPOUTBLOCK);
							}
						}
					}
				}
				break;
			case GPCT_SOCKET:
				if ((hSock || UniSocket) && nByte>0)
				{
					UINT n255=0,i2;
					if ((m_TelnetFlag&0x1))
						for(i=0;i<nByte;i++) if (ch[i]==255) n255++;

					if (n255)
					{
						char *buff=new char [nByte+n255+10];
						n255+=nByte;
						for(i2=i=0;i<nByte;i++,i2++)
						{
							if (ch[i]==255) buff[i2++]=255;
							buff[i2]=ch[i];
							if (logf)
								PrintDmp(ch[i],1,GPC_DUMPOUT);
			//				PrintDmp(ch[i],1,GPC_DUMPOUTBLOCK);
						}

						int serr=0;
						if (DelayBeforeSendBlock>0) Sleep(DelayBeforeSendBlock);
						if (BlType==0)
						{
		//					char s10[5]={10,0};
		//					if (LastSendChar==13 && *ch==13) hSock->Send(s10,2);
							serr=(dwUseSSH)?UniSocket->Send(buff,i2):hSock->Send(buff,i2);
						}
						else
							serr=(dwUseSSH)?UniSocket->Send(buff,i2):hSock->Send(buff,i2);

						int nerrcnt=0;
						while(serr==SOCKET_ERROR && ++nerrcnt<50)
						{
							if (GetLastError()!=WSAEWOULDBLOCK)	
							{
								ErrDispWrite(buff,i2); break;
							}
							else
							{
								GPC.m_View->DoRemappingInput();
								GPC.Release_m_MuteProc();
								Sleep(100);
								GPC.m_View->DoRemappingInput();
								GPC.WaitFor_m_MuteProc();
								serr=(dwUseSSH)?UniSocket->Send(buff,i2):hSock->Send(buff,i2);
							}
						}

						if (nerrcnt>=50) ErrDispWrite(buff,i2);





						if (GPC.DlgStatistics) GPC.DlgStatistics->SAddSendCount(i2);

						LastSendChar=buff[i2-1];
						if (DelayAfterSendBlock>0) Sleep(DelayAfterSendBlock);
						if (i<=i2)
						{
							UINT ret;
							for(ret=0,i2=0;i2<i;i2++, ret++)
								if (ch[i2]==255) i2++;
							i=ret;
						}
						delete[] buff;
					}
					else
					{
						if (logf)
							for(i=0;i<nByte;i++)
								PrintDmp(ch[i],1,GPC_DUMPOUT);

						int serr=0;
						if (DelayBeforeSendBlock>0) Sleep(DelayBeforeSendBlock);
						serr=(dwUseSSH)?UniSocket->Send(ch,nByte):hSock->Send(ch,nByte);
						int nerrcnt=0;
						while(serr==SOCKET_ERROR && ++nerrcnt<50)
						{
							if (GetLastError()!=WSAEWOULDBLOCK)	
							{
								ErrDispWrite(ch,nByte); break;
							}
							else
							{
								GPC.m_View->DoRemappingInput();
								GPC.Release_m_MuteProc();
								Sleep(100);
								GPC.m_View->DoRemappingInput();
								GPC.WaitFor_m_MuteProc();
								serr=(dwUseSSH)?UniSocket->Send(ch,nByte):hSock->Send(ch,nByte);
							}
						}
						if (nerrcnt>=50) ErrDispWrite(ch,nByte); 

						if (GPC.DlgStatistics) GPC.DlgStatistics->SAddSendCount(nByte);

						LastSendChar=ch[nByte-1];
						if (DelayAfterSendBlock>0) Sleep(DelayAfterSendBlock);
						i=nByte;
					}
				}
				break;
			}
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "GPSendBlock","");
	}
	LeaveCriticalSection(&m_CS);

	return  i;
}

UINT GP_comm::GPSendSafeBlock(const char *ch, UINT nByte, BOOL BlType/* = 0*/)
{
	UINT ret=0;
	if (GPC.BlockControl!=FALSE)
	{
		char str[100];
		sprintf(str,"%c%c%c%d%c%d",250,250,58,50,0xFE,GPC.m_uCurrOutputBlock);
		GPSendBlock(str,(int)strlen(str));
	}
	ret=GPSendBlock(ch,nByte,BlType);
	if (++GPC.m_uCurrOutputBlock>=100) GPC.m_uCurrOutputBlock=0;
	return ret;
}
void GP_comm::GPInitialConnect()
{
	GPConnect();
}

UINT GP_comm::GPSendWord(UINT iWord)
{
	char str[5];
	str[0]=(char)((iWord/256)%256);
	str[1]=(char)(iWord%256);
	GPSendBlock(str,2);
	return iWord;
}

UINT GP_comm::GPSendDWord(UINT iWord)
{
	char str[5];
	str[0]=(char)((iWord/256/256/256)%256);
	str[1]=(char)((iWord/256/256)%256);
	str[2]=(char)((iWord/256)%256);
	str[3]=(char)(iWord%256);
	GPSendBlock(str,4);
	return iWord;
}

void GP_comm::SetComport(const char *icomport)
{
	EnterCriticalSection(&m_CS);
	try
	{
		strncpy(GPcomport,icomport,20);
		GPcomport[19]=0;
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetComport",icomport);
	}
	LeaveCriticalSection(&m_CS);
}

void GP_comm::SetInitStr(const char *iInitStr)
{
	EnterCriticalSection(&m_CS);
	try
	{
		InitStr=iInitStr;
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetInitStr",iInitStr);
	}
	LeaveCriticalSection(&m_CS);
}

void GP_comm::SetEndStr(const char *iEndStr)
{
	EnterCriticalSection(&m_CS);
	try
	{
		EndStr=iEndStr;
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetEndStr",iEndStr);
	}
	LeaveCriticalSection(&m_CS);
}

void GP_comm::SetComment(const char *iGPcomment)
{
	EnterCriticalSection(&m_CS);
	try
	{
		GPcomment=iGPcomment;
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetComment",iGPcomment);
	}
	LeaveCriticalSection(&m_CS);
}

void GP_comm::SetdcbBaudRate(UINT BaudRate)
{
	EnterCriticalSection(&m_CS);
	try
	{
		dcb.BaudRate=BaudRate;
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetdcbBaudRate","");
	}
	LeaveCriticalSection(&m_CS);
}

void GP_comm::SetdcbByteSize(UINT ByteSize)
{
	EnterCriticalSection(&m_CS);
	try
	{
		dcb.ByteSize=(char)(ByteSize%9);
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetdcbByteSize","");
	}
	LeaveCriticalSection(&m_CS);
}

void GP_comm::SetdcbEofChar(UINT EofChar)
{
	EnterCriticalSection(&m_CS);
	try
	{
		dcb.EofChar=(char)(EofChar%256);
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetdcbEofChar","");
	}
	LeaveCriticalSection(&m_CS);
}

void GP_comm::SetdcbErrorChar(UINT ErrorChar)
{
	EnterCriticalSection(&m_CS);
	try
	{
		dcb.ErrorChar=(char)(ErrorChar%256);
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetdcbErrorChar","");
	}
	LeaveCriticalSection(&m_CS);
}

void GP_comm::SetdcbEvtChar(UINT EvtChar)
{
	EnterCriticalSection(&m_CS);
	try
	{
		dcb.EvtChar=(char)(EvtChar%256);
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetdcbEvtChar","");
	}
	LeaveCriticalSection(&m_CS);
}

void GP_comm::SetdcbfAbortOnError(BOOL fAbortOnError)
{
	EnterCriticalSection(&m_CS);
	try
	{
	dcb.fAbortOnError=fAbortOnError;
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetdcbfAbortOnError","");
	}
	LeaveCriticalSection(&m_CS);
}

void GP_comm::SetdcbfBinary(BOOL fBinary)
{
	EnterCriticalSection(&m_CS);
	try
	{
		dcb.fBinary=fBinary;
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetdcbfBinary","");
	}
	LeaveCriticalSection(&m_CS);
}

void GP_comm::SetdcbfDsrSensitivity(BOOL fDsrSensitivity)
{
	EnterCriticalSection(&m_CS);
	try
	{
		dcb.fDsrSensitivity=fDsrSensitivity;
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetdcbfDsrSensitivity","");
	}
	LeaveCriticalSection(&m_CS);
}


void GP_comm::SetdcbfDtrControl(UINT fDtrControl)
{
	EnterCriticalSection(&m_CS);
	try
	{
		dcb.fDtrControl=fDtrControl;
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetdcbfDtrControl","");
	}
	LeaveCriticalSection(&m_CS);
}

void GP_comm::SetdcbfErrorChar(BOOL fErrorChar)
{
	EnterCriticalSection(&m_CS);
	try
	{
		dcb.fErrorChar=fErrorChar;
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetdcbfErrorChar","");
	}
	LeaveCriticalSection(&m_CS);
}

void GP_comm::SetdcbfInX(BOOL fInX)
{
	EnterCriticalSection(&m_CS);
	try
	{
		dcb.fInX=fInX;
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetdcbfInX","");
	}
	LeaveCriticalSection(&m_CS);
}

void GP_comm::SetdcbfNull(BOOL fNull)
{
	EnterCriticalSection(&m_CS);
	try
	{
		dcb.fNull=fNull;
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetdcbfNull","");
	}
	LeaveCriticalSection(&m_CS);
}

void GP_comm::SetdcbfOutX(BOOL fOutX)
{
	EnterCriticalSection(&m_CS);
	try
	{
		dcb.fOutX=fOutX ;
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetdcbfOutX",""); 
	}
	LeaveCriticalSection(&m_CS);
}

void GP_comm::SetdcbfOutxCtsFlow(BOOL fOutxCtsFlow)
{
	dcb.fOutxCtsFlow=fOutxCtsFlow;
}

void GP_comm::SetdcbfOutxDsrFlow(BOOL fOutxDsrFlow)
{
	dcb.fOutxDsrFlow=fOutxDsrFlow;
}

void GP_comm::SetdcbfRtsControl(UINT fRtsControl)
{
	dcb.fRtsControl=fRtsControl;
}

void GP_comm::SetdcbfTXContinueOnXoff(BOOL fTXContinueOnXoff)
{
	dcb.fTXContinueOnXoff=fTXContinueOnXoff;
}

void GP_comm::SetdcbParity(UINT Parity)
{
	dcb.Parity=(unsigned char)Parity;
}

void GP_comm::SetdcbfParity(BOOL fParity)
{
	dcb.fParity=fParity ;
}

void GP_comm::SetdcbStopBits(UINT StopBits)
{
	dcb.StopBits=(unsigned char)StopBits;
}


void GP_comm::SetdcbXoffChar(UINT XoffChar)
{
	dcb.XoffChar=(char)(XoffChar%256);
}

void GP_comm::SetdcbXoffLim(UINT XoffLim)
{
	dcb.XoffLim  =(WORD)(XoffLim);
}

void GP_comm::SetdcbXonChar(UINT XonChar)
{
	dcb.XonChar=(char)(XonChar%256);
}

void GP_comm::SetdcbXonLim(UINT XonLim)
{
	dcb.XonLim=(WORD)XonLim;
}

void GP_comm::SetDelayBeforeSendChar(UINT iDelayBeforeSendChar)
{
	EnterCriticalSection(&m_CS);
	try
	{
		DelayBeforeSendChar=iDelayBeforeSendChar%2000;
	}
	catch(...)
	{GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetDelayBeforeSendChar","");}
	LeaveCriticalSection(&m_CS);
}

void GP_comm::SetDelayBeforeSendLine(UINT iDelayBeforeSendLine)
{
	EnterCriticalSection(&m_CS);
	try
	{
		DelayBeforeSendLine=iDelayBeforeSendLine%2000;
	}
	catch(...)
	{GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetDelayBeforeSendLine",""); }
	LeaveCriticalSection(&m_CS);
}

void GP_comm::SetDelayBeforeSendBlock(UINT iDelayBeforeSendBlock)
{
	EnterCriticalSection(&m_CS);
	try
	{
		DelayBeforeSendBlock=iDelayBeforeSendBlock%2000;
	}
	catch(...)
	{GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetDelayBeforeSendBlock",""); }
	LeaveCriticalSection(&m_CS);
}

void GP_comm::SetDelayAfterSendChar(UINT iDelayAfterSendChar)
{
	EnterCriticalSection(&m_CS);
	try
	{
		DelayAfterSendChar=iDelayAfterSendChar%2000;
	}
	catch(...)
	{GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetDelayAfterSendChar","");}
	LeaveCriticalSection(&m_CS);
}

void GP_comm::SetDelayAfterSendLine(UINT iDelayAfterSendLine)
{
	EnterCriticalSection(&m_CS);
	try
	{
		DelayAfterSendLine=iDelayAfterSendLine%2000;
	}
	catch(...)
	{;GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetDelayAfterSendLine",""); }
	LeaveCriticalSection(&m_CS);
}

void GP_comm::SetDelayAfterSendBlock(UINT iDelayAfterSendBlock)
{
	EnterCriticalSection(&m_CS);
	try
	{
		DelayAfterSendBlock=iDelayAfterSendBlock%2000;
	}
	catch(...)
	{GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetDelayAfterSendBlock","");}
	LeaveCriticalSection(&m_CS);
}

void GP_comm::GPStartDump()
{
	EnterCriticalSection(&m_CS);
	try
	{
		if (logf!=NULL) GPStopDump();
		logf=fopen("dump.log","wt");
		if (logf!=NULL)
			fprintf(logf,"%c(S%cO##START##",27,(DumpMode&GPC_DUMPORIENT)==GPC_DUMPORIENT+'0');
		oldTypeComm=123456;
		nCharDump=10;
		nLineDump=0;
	}
	catch(...)
	{GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "GPStartDump","");}
	LeaveCriticalSection(&m_CS);
}

void GP_comm::GPContinueDump()
{
	EnterCriticalSection(&m_CS);
	try
	{
		if (logf!=NULL) GPStopDump();
		logf=fopen("dump.log","at");
		if (logf!=NULL) fprintf(logf,"%c%c(S%cO##CONTINUE##",12,27,(DumpMode&GPC_DUMPORIENT)==GPC_DUMPORIENT+'0');
		oldTypeComm=123456;
		nCharDump=10;
		nLineDump=0;
	}
	catch(...)
	{GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "GPContinueDump","");  }
	LeaveCriticalSection(&m_CS);
}


void GP_comm::GPStopDump()
{
	EnterCriticalSection(&m_CS);
	try
	{
		if (logf!=NULL)
		{
			fprintf(logf,"\n##STOP##");
			fclose(logf);
		}
		logf=NULL;
	}
	catch(...)
	{GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "GPStopDump","");  }
	LeaveCriticalSection(&m_CS);
}

BOOL GP_comm::IsDumping()
{
	if (logf!=NULL) return TRUE;
	return FALSE;
}

void GP_comm::PrintDmp(UINT iCh, int iId, UINT iType)
{
	if (logf!=NULL && (DumpMode&iType)!=0)
	{
		iCh=GPC.chDosAnsi[iCh&0xFF];

		if (nLineDump>maxnLineDump && maxnLineDump>1) {fprintf(logf,"%c%s",12,(LPCSTR)m_DumpPrefix);nLineDump=0;nCharDump=10;}

		if (oldTypeComm!=iType)
		{
			switch(oldTypeComm=iType)
			{
			case GPC_DUMPIN: /*Input*/
				fprintf(logf,"\n<<<input<<");break;
			case GPC_DUMPOUT: /*Output char*/
				fprintf(logf,"\n>>output>>");break;
			case GPC_DUMPOUTBLOCK: /*Output Block*/
				fprintf(logf,"\n>>outblk>>");break;
			case GPC_DUMPREM: /*Remapping*/
				fprintf(logf,"\n--_remap :");break;
			}
			nCharDump=10;nLineDump++;
		}

		int ChCh='.';
		if (iCh!=0 && iCh!=7 && iCh!=27 && iCh!=12 && iCh!=10 && iCh!=13) ChCh=iCh;

		if (nCharDump>maxnCharDump || ((DumpMode&GPC_DUMPCRLF)!=0 && iCh==10))
		{
			nCharDump=10;
			nLineDump++;
			if (nLineDump>maxnLineDump) {fprintf(logf,"%c",12);nLineDump=0;}
			fprintf(logf,"\n%s",(LPCSTR)m_DumpPrefix);
		}

		if ((DumpMode&iType)!=0)
		{
			int flagout=0;
			switch(oldTypeComm)
			{
			case GPC_DUMPIN: /*Input*/
				if ((DumpMode&GPC_DUMPINDEC)!=0)
				{
					fprintf(logf,"%3.3d",iCh);
					nCharDump+=3;flagout++;
					if ((DumpMode&GPC_DUMPSPACE)!=0) {nCharDump++;fprintf(logf," ");}
				}
				if ((DumpMode&GPC_DUMPINHEX)!=0)
				{
					fprintf(logf,"%2.2X",iCh);
					nCharDump+=2;flagout++;
					if ((DumpMode&GPC_DUMPSPACE)!=0) {nCharDump++;fprintf(logf," ");}
				}
				if ((DumpMode&GPC_DUMPINCHAR)!=0)
				{
					fprintf(logf,"%c",ChCh);
					nCharDump+=1;flagout++;
					if ((DumpMode&GPC_DUMPSPACE)!=0) {nCharDump++;fprintf(logf," ");}
				}
				break;
			case GPC_DUMPOUTBLOCK: /*Output Block*/
			case GPC_DUMPOUT: /*Output char*/
				if ((DumpMode&GPC_DUMPOUTDEC)!=0)
				{
					fprintf(logf,"%3.3d",iCh);
					nCharDump+=3;flagout++;
					if ((DumpMode&GPC_DUMPSPACE)!=0) {nCharDump++;fprintf(logf," ");}
				}
				if ((DumpMode&GPC_DUMPOUTHEX)!=0)
				{
					fprintf(logf,"%2.2X",iCh);
					nCharDump+=2;flagout++;
					if ((DumpMode&GPC_DUMPSPACE)!=0) {nCharDump++;fprintf(logf," ");}
				}
				if ((DumpMode&GPC_DUMPOUTCHAR)!=0)
				{
					fprintf(logf,"%c",ChCh);
					nCharDump+=1;flagout++;
					if ((DumpMode&GPC_DUMPSPACE)!=0) {nCharDump++;fprintf(logf," ");}
				}
				break;
			case GPC_DUMPREM: /*Remapping*/
				if ((DumpMode&GPC_DUMPREMDEC)!=0)
				{
					fprintf(logf,"%3.3d",iCh);
					nCharDump+=3;flagout++;
					if ((DumpMode&GPC_DUMPSPACE)!=0) {nCharDump++;fprintf(logf," ");}
				}
				if ((DumpMode&GPC_DUMPREMHEX)!=0)
				{
					fprintf(logf,"%2.2X",iCh);
					nCharDump+=2;flagout++;
					if ((DumpMode&GPC_DUMPSPACE)!=0) {nCharDump++;fprintf(logf," ");}
				}
				if ((DumpMode&GPC_DUMPREMCHAR)!=0)
				{
					fprintf(logf,"%c",ChCh);
					nCharDump+=1;flagout++;
					if ((DumpMode&GPC_DUMPSPACE)!=0) {nCharDump++;fprintf(logf," ");}
				}
				if ((DumpMode&GPC_DUMPREMID)!=0)
				{
					fprintf(logf,"%+5.5d",iId);
					nCharDump+=6;flagout++;
					if ((DumpMode&GPC_DUMPSPACE)!=0) {nCharDump++;fprintf(logf," ");}
				}
				break;
			}
			if (flagout>1) {fprintf(logf,"|"); nCharDump++;}
			fflush(logf);
		}
	}
}

void GP_comm::SetDumpMode(UINT mode)
{
	EnterCriticalSection(&m_CS);
	try
	{
		DumpMode=0xFFFF&mode;
	}
	catch(...)
	{GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetDumpMode","");}
	LeaveCriticalSection(&m_CS);
}

UINT GP_comm::GetDumpMode()
{
	return DumpMode;
}

const char * GP_comm::GetDumpFileName()
{
	return DumpFileName;
}

const char * GP_comm::SetDumpFileName(const char *iFileName)
{
	GPStopDump();
	strncpy(DumpFileName,iFileName,FILENAME_MAX);
	DumpFileName[FILENAME_MAX]=0;
	GPContinueDump();
	return DumpFileName;
}

int GP_comm::SendSequens(const char *iSeq)
{
	int n=0;
	EnterCriticalSection(&m_CS);
	try
	{
		while(iSeq!=NULL && *iSeq!=0)
		{
			if (*iSeq!='\\')
			{
				n++;
				GPSendChar(*iSeq);
			}
			else
				switch(*(++iSeq))
				{
				case 0:		iSeq--;break;
				case '\\':	GPSendChar('\\');break;
				case 'W':case 'w':	Sleep(1000); break;
				case 'S':case 's':	
					{
						int nTimes=*(++iSeq)-'0';
						if (nTimes<=0) nTimes=1;
						Sleep(nTimes*100); 
					}
					break;
				case 'N':case 'n':	GPSendChar('\n'); Sleep(150); break;
				case 'R':case 'r':	GPSendChar('\r'); Sleep(150); break;
				case 'T':case 't':	GPSendChar(9); break;
				case '0':	if (iSeq[1]=='x' && iSeq[2]>='0' && iSeq[3]>='0' && iSeq[2]<='F' && iSeq[3]<='F')
							{
								int c=0;
								m_LastScanf=sscanf(++iSeq,"%2.2x",&c);
								GPSendChar((const char)c);
								if (c==GPC.BreakChar) Sleep(500);
								Sleep(100);
								iSeq++;
							}
							else iSeq--;
							break;
				case '(':
							{
								int c=atoi(++iSeq);
								GPSendChar((const char)c);
								if (c==GPC.BreakChar) Sleep(500);
								Sleep(100);
								if ((iSeq=strchr(iSeq,')'))==NULL) iSeq--;
							}
							break;
				default: GPSendChar(*(--iSeq));break;
				}

			iSeq++;
		}

	}
	catch(...)
	{GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SendSequens","");}
	LeaveCriticalSection(&m_CS);
	GPC.m_View->m_LastActivity=CTime::GetCurrentTime();
	return n;
}


BOOL GP_comm::IsConnected()
{
	switch(com_type)
	{
	case GPCT_COMPORT:
		if (hComm!=NULL) return TRUE;
		break;
	case GPCT_SOCKET:
		if (hSock && hSock->m_hSocket) return TRUE;
		if (UniSocket) 
			if (!UniSocket->IsSessionClose()) return TRUE;
		break;
	}

	return FALSE;
}

UINT GP_comm::SetBlockSize(UINT iSize)
{
	UINT OldSize=maxBLOCK;
	maxBLOCK=iSize;
	return OldSize;
}

UINT GP_comm::GetBlockSize()
{
	return maxBLOCK;
}

UINT GP_comm::SetmaxBLOCK(UINT umaxBLOCK)
{
	UINT ret=maxBLOCK;
	if (umaxBLOCK) maxBLOCK=umaxBLOCK;
	return ret;
}

void GP_comm::SetPortNumber(int iPortN)
{
	EnterCriticalSection(&m_CS);
	try
	{
		PortNum=iPortN;
	}
	catch(...)
	{GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "SetPortNumber",""); }
	LeaveCriticalSection(&m_CS);
}

int GP_comm::GetPortNumber()	{return PortNum;}

UINT GP_comm::ErrDispWrite(const char *pwrite, int nByte)
{
	char tmps[1000];
	char *pos=tmps;
	if (nByte<0) nByte=5;
	CTime tm=CTime::GetCurrentTime();
	pos+=sprintf(pos,"WRITE at @%d@%s@%d@",m_uId,(LPCSTR)tm.Format("%d.%m.%y - %H:%M:%S "),nByte);
	if (pwrite)
	{
		int i;
		for(i=0;i<10 && i<nByte;i++)
			pos+=sprintf(pos,"%2.2X ",pwrite[i]);
	}

	BOOL bWr=TRUE;

	switch(GetLastError())
	{
	case WSANOTINITIALISED:	//A successful AfxSocketInit must occur before using this API.
		pos+=sprintf(pos,"@A successful AfxSocketInit must occur before using this API.");
		break;
	case WSAENETDOWN:		//The Windows Sockets implementation detected that the network subsystem failed.
		pos+=sprintf(pos,"@The Windows Sockets implementation detected that the network subsystem failed.");
		break;
	case WSAEACCES:			//The requested address is a broadcast address, but the appropriate flag was not set.
		pos+=sprintf(pos,"@The requested address is a broadcast address, but the appropriate flag was not set.");
		break;
	case WSAEINPROGRESS:	//A blocking Windows Sockets operation is in progress.
		pos+=sprintf(pos,"@A blocking Windows Sockets operation is in progress.");
		break;
	case WSAEFAULT:			//The lpBuf argument is not in a valid part of the user address space.
		pos+=sprintf(pos,"@The lpBuf argument is not in a valid part of the user address space.");
		break;
	case WSAENETRESET:		//The connection must be reset because the Windows Sockets implementation dropped it.
		pos+=sprintf(pos,"@The connection must be reset because the Windows Sockets implementation dropped it.");
		break;
	case WSAENOBUFS:		//The Windows Sockets implementation reports a buffer deadlock.
		pos+=sprintf(pos,"@The Windows Sockets implementation reports a buffer deadlock.");
		break;
	case WSAENOTCONN:		//The socket is not connected.
		pos+=sprintf(pos,"@The socket is not connected.");
		break;
	case WSAENOTSOCK:		//The descriptor is not a socket.
		pos+=sprintf(pos,"@The descriptor is not a socket.");
		break;
	case WSAEOPNOTSUPP:		//MSG_OOB was specified, but the socket is not of type SOCK_STREAM.
		pos+=sprintf(pos,"@MSG_OOB was specified, but the socket is not of type SOCK_STREAM.");
		break;
	case WSAESHUTDOWN:		//The socket has been shut down; it is not possible to call Send on a socket after ShutDown has been invoked with nHow set to 1 or 2.
		pos+=sprintf(pos,"@The socket has been shut down; it is not possible to call Send on a socket after ShutDown has been invoked with nHow set to 1 or 2.");
		break;
	case WSAEWOULDBLOCK:	//The socket is marked as nonblocking and the requested operation would block.
		pos+=sprintf(pos,"@The socket is marked as nonblocking and the requested operation would block.");
		break;
	case WSAEMSGSIZE:		//The socket is of type SOCK_DGRAM, and the datagram is larger than the maximum supported by the Windows Sockets implementation.
		pos+=sprintf(pos,"@The socket is of type SOCK_DGRAM, and the datagram is larger than the maximum supported by the Windows Sockets implementation.");
		break;
	case WSAEINVAL:			//The socket has not been bound with Bind.
		pos+=sprintf(pos,"@The socket has not been bound with Bind.");
		break;
	case WSAECONNABORTED:	//The virtual circuit was aborted due to timeout or other failure.
		pos+=sprintf(pos,"@The virtual circuit was aborted due to timeout or other failure.");
		break;
	case WSAECONNRESET:		//The virtual circuit was reset by the remote side.
		pos+=sprintf(pos,"@The virtual circuit was reset by the remote side. ");
		break;
	default:
		bWr=FALSE;
		break;
	}

	if (m_flgDump && m_FileErrorLog && bWr)
	{
		fseek(m_FileErrorLog,0,SEEK_END);
		fprintf(m_FileErrorLog,"%s\n",tmps);
		fflush(m_FileErrorLog);
		Sleep(400);
	}

	return 0;
}

UINT GP_comm::ErrDispRead(const char *pread, int nByte)
{
	char tmps[1000];
	char *pos=tmps;
	if (nByte<0) nByte=5;
	CTime tm=CTime::GetCurrentTime();
	pos+=sprintf(pos,"READ at @%d@%s@%d@",m_uId,(LPCSTR)tm.Format("%d.%m.%y - %H:%M:%S "),nByte);
	if (pread)
	{
		int i;
		for(i=0;i<10 && i<nByte;i++)
			pos+=sprintf(pos,"%2.2X ",pread[i]);
	}
	BOOL bWr=TRUE;
	UINT ret=GetLastError();
	switch(ret)
	{
	case WSANOTINITIALISED:	// A successful AfxSocketInit must occur before using this API.
		pos+=sprintf(pos,"@A successful AfxSocketInit must occur before using this API.");
		break;
	case WSAENETDOWN:		// The Windows Sockets implementation detected that the network subsystem failed.
		pos+=sprintf(pos,"@The Windows Sockets implementation detected that the network subsystem failed.");
		break;
	case WSAENOTCONN:		// The socket is not connected.
		pos+=sprintf(pos,"@The socket is not connected.");
		break;
	case WSAEINPROGRESS:	// A blocking Windows Sockets operation is in progress.
		pos+=sprintf(pos,"@A blocking Windows Sockets operation is in progress.");
		break;
	case WSAENOTSOCK:		// The descriptor is not a socket.
		pos+=sprintf(pos,"@The descriptor is not a socket.");
		break;
	case WSAEOPNOTSUPP:		// MSG_OOB was specified, but the socket is not of type SOCK_STREAM.
		pos+=sprintf(pos,"@MSG_OOB was specified, but the socket is not of type SOCK_STREAM.");
		break;
	case WSAESHUTDOWN:		// The socket has been shut down; it is not possible to call Receive on a socket after ShutDown has been invoked with nHow set to 0 or 2.
		pos+=sprintf(pos,"@The socket has been shut down; it is not possible to call Receive on a socket after ShutDown has been invoked with nHow set to 0 or 2.");
		break;
	case WSAEMSGSIZE:		// The datagram was too large to fit into the specified buffer and was truncated.
		pos+=sprintf(pos,"@The datagram was too large to fit into the specified buffer and was truncated.");
		break;
	case WSAEINVAL:			// The socket has not been bound with Bind.
		pos+=sprintf(pos,"@The socket has not been bound with Bind.");
		break;
	case WSAECONNABORTED:	// The virtual circuit was aborted due to timeout or other failure.
		pos+=sprintf(pos,"@The virtual circuit was aborted due to timeout or other failure.");
		break;
	case WSAECONNRESET:		// The virtual circuit was reset by the remote side.
		pos+=sprintf(pos,"@The virtual circuit was reset by the remote side. ");
		break;
	case WSAEWOULDBLOCK:	// The socket is marked as nonblocking and the Receive operation would block.
		pos+=sprintf(pos,"@The socket is marked as nonblocking and the Receive operation would block.");
		//		break;
	default:
		bWr=FALSE;
		break;
	}

	if (m_flgDump && m_FileErrorLog && bWr)
	{
		fseek(m_FileErrorLog,0,SEEK_END);
		fprintf(m_FileErrorLog,"%s\n",tmps);
		fflush(m_FileErrorLog);
		Sleep(400);
	}

	return ret;
}

void GP_comm::StartErrorLog()
{
	if (m_flgDump)
	{
		AfxGetApp()->WriteProfileInt(GPSectionName, "ErrorLogging",	1);
		if (m_FileErrorLog==NULL)
		{
			if ((m_FileErrorLog=fopen(ErrorLogFileName,"at+"))==NULL)
				m_FileErrorLog=fopen(ErrorLogFileName,"wt+");
			m_uId=(UINT)AfxGetApp()->m_nThreadID;
			if (m_FileErrorLog)
			{
				CTime tm=CTime::GetCurrentTime();
				fseek(m_FileErrorLog,0,SEEK_END);
				fprintf(m_FileErrorLog,"#####START LOG @%d@%s\n",m_uId,(LPCSTR)tm.Format("%d.%m.%y - %H:%M:%S "));
				fflush(m_FileErrorLog);
			}
		}
	}
}

void GP_comm::EndErrorLog()
{
	if (m_flgDump)
	{

		try
		{
			CWinApp* pApp = AfxGetApp();
			if (pApp)
				pApp->WriteProfileInt(GPSectionName, "ErrorLogging",	0);
		}
		catch(...){GPC.m_ErrReport.GPWriteErrorLog("GP_comm", "EndErrorLog","");}
		if (m_FileErrorLog)
		{
			CTime tm=CTime::GetCurrentTime();
			fseek(m_FileErrorLog,0,SEEK_END);
			fprintf(m_FileErrorLog,"#####END LOG @%d@%s\n",m_uId,(LPCSTR)tm.Format("%d.%m.%y - %H:%M:%S "));
			fclose(m_FileErrorLog);
		}
		m_FileErrorLog=NULL;
	}
}

BOOL GP_comm::IsErrorLog()
{
	return m_FileErrorLog!=NULL;
}

UINT GP_comm::SetTelnetFlag(UINT iTelnetFlag)
{
	UINT ret=m_TelnetFlag;
	m_TelnetFlag=iTelnetFlag;
	return ret;
}

UINT CommunicateFnNULL(LPVOID pParam)
{
	CGPAsyncSocket *tSock=(CGPAsyncSocket *)pParam;
	int snb=1;
	char ibuf[210];

	Sleep(1000);
	while(snb && !m_StopWorking)
	{
		Sleep(100);
		switch((snb=tSock->Receive(ibuf,200)))
		{
		case 0:
		case SOCKET_ERROR:
			snb=0;
			break;
		default:
			break;
		}
	}

	if (tSock)
		tSock->ShutDown(2);

	return 0;
}


void GP_comm::LoadDelimiters()
{
	CWinApp* pApp = AfxGetApp();
	DelimiterIn1=pApp->GetProfileInt(GPSectionName, "DelimiterIn1",'^');
	DelimiterIn2=pApp->GetProfileInt(GPSectionName, "DelimiterIn2",']');
	DelimiterIn3=pApp->GetProfileInt(GPSectionName, "DelimiterIn3",'\\');
	DelimiterIn4=pApp->GetProfileInt(GPSectionName, "DelimiterIn4",4);
	DelimiterIn5=pApp->GetProfileInt(GPSectionName, "DelimiterIn5",5);
	DelimiterIn6=pApp->GetProfileInt(GPSectionName, "DelimiterIn6",6);

	DelimiterSrc1=pApp->GetProfileInt(GPSectionName, "DelimiterSrc1",'^');
	DelimiterSrc2=pApp->GetProfileInt(GPSectionName, "DelimiterSrc2",']');
	DelimiterSrc3=pApp->GetProfileInt(GPSectionName, "DelimiterSrc3",'\\');
	DelimiterSrc4=pApp->GetProfileInt(GPSectionName, "DelimiterSrc4",4);
	DelimiterSrc5=pApp->GetProfileInt(GPSectionName, "DelimiterSrc5",5);
	DelimiterSrc6=pApp->GetProfileInt(GPSectionName, "DelimiterSrc6",6);
}

void GP_comm::SaveDelimiters()
{
	CWinApp* pApp = AfxGetApp();

	pApp->WriteProfileInt(GPSectionName, "DelimiterIn1",DelimiterIn1);
	pApp->WriteProfileInt(GPSectionName, "DelimiterIn2",DelimiterIn2);
	pApp->WriteProfileInt(GPSectionName, "DelimiterIn3",DelimiterIn3);
	pApp->WriteProfileInt(GPSectionName, "DelimiterIn4",DelimiterIn4);
	pApp->WriteProfileInt(GPSectionName, "DelimiterIn5",DelimiterIn5);
	pApp->WriteProfileInt(GPSectionName, "DelimiterIn6",DelimiterIn6);

	pApp->WriteProfileInt(GPSectionName, "DelimiterSrc1",DelimiterSrc1);
	pApp->WriteProfileInt(GPSectionName, "DelimiterSrc2",DelimiterSrc2);
	pApp->WriteProfileInt(GPSectionName, "DelimiterSrc3",DelimiterSrc3);
	pApp->WriteProfileInt(GPSectionName, "DelimiterSrc4",DelimiterSrc4);
	pApp->WriteProfileInt(GPSectionName, "DelimiterSrc5",DelimiterSrc5);
	pApp->WriteProfileInt(GPSectionName, "DelimiterSrc6",DelimiterSrc6);
}

//For SSH DLL
int GP_comm::SendMessageToDLL(UINT message, WPARAM wParam, LPARAM lParam)
{
	return UniSocket?UniSocket->SendMessageToDLL(message,wParam,lParam):0;
}

int GP_comm::ChechAndDelete(const char *iConnectionName)
{
	BOOL ret=FALSE;
	CString ssss;
	ssss.Format("Software\\%s\\%s\\COMSETLIST\\%s",AfxGetApp()->m_pszRegistryKey,AfxGetApp()->m_pszAppName,iConnectionName);
	HKEY tmpKey=NULL;
	::RegOpenKeyEx(HKEY_CURRENT_USER,ssss,0,KEY_ALL_ACCESS,&tmpKey);
	if (tmpKey)
	{
		VALENT arr[3];
		char *tmpNames[]={"InitStr","EndStr","TerminalID",};

		int i;
		for(i=0;i<3;i++)
		{
			arr[i].ve_type=arr[i].ve_valuelen=arr[i].ve_valueptr=0;
			arr[i].ve_valuename=tmpNames[i];
		}
		DWORD RetLen=0;
		RegQueryMultipleValues(tmpKey,arr,3,NULL,&RetLen);
		::RegCloseKey(tmpKey);
		if ((ret=RetLen<3))	::RegDeleteKey(HKEY_CURRENT_USER,ssss);
	}
	return ret;
}
