// UniSocket.cpp: implementation of the CUniSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "UniSocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
extern __declspec(dllimport) int _stdcall DLL_Start_Session(int inst, int hwndInst);
extern __declspec(dllimport) _stdcall DLL_Close_Session(void);
extern __declspec(dllimport) void _stdcall DLL_lpage_send(int codepage, char *buf, int len, int interactive);
extern __declspec(dllimport) void _stdcall DLL_luni_send(char *buf, int len, int interactive);
extern __declspec(dllimport) void _stdcall DLL_ldisc_send(char *buf, int len, int interactive);
extern __declspec(dllimport) int _stdcall DLL_WndProc(UINT message, WPARAM wParam, LPARAM lParam);
extern __declspec(dllimport) int _stdcall DLL_Read_Buffer(char *data, int len);

extern __declspec(dllimport) void _stdcall DLL_Send_Unicode(int iCodePage, wchar_t * widebuf, int len, int interactive);
//extern __declspec(dllimport) int _stdcall DLL_Read_Unicode(int iCodePage, wchar_t * widebuf, int wlen);
//extern __declspec(dllimport) int _stdcall DLL_Read_Unicode(int iCodePage, LPOLESTR widebuf, int wlen);
extern __declspec(dllimport) int _stdcall DLL_Read_Unicode(int iCodePage, char *widebuf, int wlen);
*/

CUniSocket::CUniSocket()
{
	PrepareSSHLibrary();
}

CUniSocket::CUniSocket(GP_comm *iMasterComm)
{
	DLL_SSH_Config cfg;

	m_MasterComm=iMasterComm;
	PrepareSSHLibrary();

	// Testing
/*	{
		char **ppTmp;
		char *pTmp;
		int i;

		pTmp = new char[600];
		ppTmp = new char *[6];
		for(i = 0; i < 6; i++) ppTmp[i] = new char[200];
		GetCiphers(ppTmp,6);
		strcpy(pTmp, "");
		for(i = 0; i < 5; i++) 
		{
			strcat(pTmp, ppTmp[i]);
			strcat(pTmp,"\n");
		}
		AfxMessageBox(pTmp);
		for(i = 0; i < 6; i++) delete[] ppTmp[i];
		delete[] ppTmp;
		delete[] pTmp;
	}
*/

	cfg.ssh_subsys = 0;	       /* FIXME: load this properly */
	cfg.remote_cmd_ptr = NULL;
	cfg.remote_cmd_ptr2 = NULL;
	strcpy(cfg.host, iMasterComm->GPGetHostName()); /* hostname */
	strcpy(cfg.logfilename.path, "dll_ssh.log");
	cfg.logtype = 0;
	cfg.logxfovr = DLL_SSH_LGXF_ASK;
	cfg.logflush = 1;
	cfg.logomitpass= 1;
	cfg.logomitdata = 0;
	cfg.protocol = 0;// default_protocol;
	cfg.port = iMasterComm->GetPortNumber(); // 22; // iMasterComm->GetHostPort(); // default_port; ( дл€ SSH только 22 порт)
	/* Address family selection */
	cfg.addressfamily = DLL_SSH_ADDRTYPE_UNSPEC;
	/* This is two values for backward compatibility with 0.50/0.51 */
	cfg.ping_interval = 0;
	cfg.tcp_nodelay = 1;
	cfg.tcp_keepalives = 0;
	strcpy(cfg.termtype, "xterm");
	strcpy(cfg.termspeed,"38400,38400");

	/* proxy settings */
	strcpy(cfg.proxy_exclude_list, "");
	cfg.proxy_dns = (2)%3;
	cfg.even_proxy_localhost = 0;
	cfg.proxy_type = -1;
	cfg.proxy_type = DLL_SSH_PROXY_NONE;
	strcpy(cfg.proxy_host, "proxy");
	cfg.proxy_port = 80;
	strcpy(cfg.proxy_username, "");
	strcpy(cfg.proxy_password, "");
	strcpy(cfg.proxy_telnet_command, "connect %host %port\\n");
	strcpy(cfg.environmt, "");
	strcpy(cfg.username, "");
	strcpy(cfg.localusername, "");
	cfg.nopty = 0;
	cfg.compression = 0;
	cfg.agentfwd = 0;
	cfg.change_username = 0;
	cfg.ssh_cipherlist[0] = 3; cfg.ssh_cipherlist[1] = 4; cfg.ssh_cipherlist[2] = 1;
	cfg.ssh_cipherlist[3] = 2; cfg.ssh_cipherlist[4] = 0;
		//default_kexes = "dh-group14-sha1,dh-group1-sha1,WARN,dh-gex-sha1";
		//default_kexes = "dh-gex-sha1,dh-group14-sha1,dh-group1-sha1,WARN";
	cfg.ssh_kexlist[0] = 3;cfg.ssh_kexlist[1] = 2;
	cfg.ssh_kexlist[2] = 1;cfg.ssh_kexlist[3] = 0;
	cfg.ssh_rekey_time = 60;
	strcpy(cfg.ssh_rekey_data, "1G");
	cfg.sshprot = 2;
	cfg.ssh2_des_cbc = 0;
	cfg.try_tis_auth = 0;
	cfg.try_ki_auth = 1;
	cfg.ssh_no_shell = 0;
	strcpy(cfg.keyfile.path, "");
	strcpy(cfg.remote_cmd, "");
	/*
	 * The empty default for LineCodePage will be converted later
	 * into a plausible default for the locale.
	 */
	cfg.x11_forward = 0;
	strcpy(cfg.x11_display, "");
	cfg.x11_auth = DLL_SSH_X11_MIT;
	cfg.lport_acceptall = 0;
	cfg.rport_acceptall = 0;
	*(cfg.portfwd) = '\0';
	cfg.sshbug_ignore1 = 2;
	cfg.sshbug_plainpw1 = 2;
	cfg.sshbug_rsa1 = 2;
	cfg.sshbug_hmac2 = 2;
	cfg.sshbug_derivekey2 = 2;
	cfg.sshbug_rsapad2 = 2;
	cfg.sshbug_pksessid2 = 2;
	cfg.sshbug_rekey2 = 2;
	SetConfig(cfg);
}

CUniSocket::~CUniSocket()
{
	Close();
	if (!hinstSSHLib) FreeLibrary(hinstSSHLib);
}

int CUniSocket::InitUniSocket(const char *iHost, int iPort)
{
//	if (iHost && *iHost) strcpy(cfg.host,iHost);
//	cfg.port=iPort;

	return (pStart_Session)?pStart_Session((int)(AfxGetInstanceHandle()), (int)(GPC.m_hViewWnd)):0;
}

void CUniSocket::Close()
{
	if (hinstSSHLib) pClose_Session();
}

int CUniSocket::Send(const void *repl, int outp)
{
	if (hinstSSHLib) pSend((char *) repl, outp, 0);
	return 0;
}

int CUniSocket::SendMessageToDLL(UINT message, WPARAM wParam, LPARAM lParam)
{
	return (hinstSSHLib)?pDLL_WndProc(message, wParam, lParam):0;
}

int CUniSocket::Receive(const void *inputbuf,int nread)
{
	/*int iRes;
	static int sss;
   if (sss)
//	TRACE("Start Receive!%d\n",nread);
   sss=1;
	iRes = pRead_Buffer((char *) inputbuf, nread);
	sss=0;
	//TRACE("Stop Receive!%d\n",iRes);
	return iRes;*/
	return (hinstSSHLib)?pRead_Buffer((char *) inputbuf, nread):1234567890;
}

BOOL CUniSocket::IsSessionClose()
{
	return (hinstSSHLib)?pIsSessionClose():TRUE;
}

int CUniSocket::GetLastError(int *iErrorType, char *strError, int nStrError)
{
	return (hinstSSHLib)?pGetLastError(iErrorType, strError, nStrError):123456;
}

int CUniSocket::GetCiphers(char **ciphers, int nBuff)
{
	return (hinstSSHLib)?pGetCiphers(ciphers, nBuff):0;
}

int CUniSocket::GetKEXs(char **kexes, int nBuff)
{
	return (hinstSSHLib)?pGetKEXs(kexes, nBuff):0;
}

DLL_SSH_Config CUniSocket::GetConfig()
{
	return pGetConfig();
}

void CUniSocket::SetConfig(DLL_SSH_Config cfgTmp)
{
	if (hinstSSHLib) pSetConfig(cfgTmp);
	return;
}

int CUniSocket::GetCurrentCipher()
{
	return (hinstSSHLib)?pGetCurrentCipher():0;
}

int CUniSocket::GetCurrentKEX()
{
	return (hinstSSHLib)? pGetCurrentKEX():0;
}

BOOL CUniSocket::PrepareSSHLibrary()
{
	BOOL bRes = FALSE;

	try
	{
		hinstSSHLib = LoadLibrary("MySSH3.dll");
	}
	catch(...)
	{
		hinstSSHLib = NULL;
	}
	//hinstSSHLib = LoadLibrary("C:\\PAI\\SSH\\MySSH\\MySSH3\\Debug\\MySSH3.dll");
	if (hinstSSHLib) 
    { 
		pStart_Session = (DLL_SSH_Start_Session) GetProcAddress(hinstSSHLib, "DLL_Start_Session");
		pClose_Session = (DLL_SSH_Close_Session) GetProcAddress(hinstSSHLib, "DLL_Close_Session");
		pSend = (DLL_SSH_ldisc_send) GetProcAddress(hinstSSHLib, "DLL_ldisc_send");
		pDLL_WndProc = (DLL_SSH_WndProc) GetProcAddress(hinstSSHLib, "DLL_WndProc");
		pRead_Buffer = (DLL_SSH_Read_Buffer) GetProcAddress(hinstSSHLib, "DLL_Read_Buffer");
		pIsSessionClose = (DLL_SSH_IsSessionClose) GetProcAddress(hinstSSHLib, "DLL_IsSessionClose");
		pGetLastError = (DLL_SSH_GetLastError) GetProcAddress(hinstSSHLib, "DLL_GetLastError");
		pGetCiphers = (DLL_SSH_GetCiphers) GetProcAddress(hinstSSHLib, "DLL_GetCiphers");
		pGetKEXs = (DLL_SSH_GetKEXs) GetProcAddress(hinstSSHLib, "DLL_GetKEXs");
		pGetConfig = (DLL_SSH_GetConfig) GetProcAddress(hinstSSHLib, "DLL_GetConfig");
		pSetConfig = (DLL_SSH_SetConfig) GetProcAddress(hinstSSHLib, "DLL_SetConfig");
		pGetCurrentCipher = (DLL_SSH_GetCurrentCipher) GetProcAddress(hinstSSHLib, "DLL_GetCurrentCipher");
		pGetCurrentKEX = (DLL_SSH_GetCurrentKEX) GetProcAddress(hinstSSHLib, "DLL_GetCurrentKEX");
		bRes= ((pStart_Session) && (pClose_Session != NULL) && (pSend != NULL) && \
			(pDLL_WndProc) && (pRead_Buffer != NULL) && (pIsSessionClose != NULL) && \
			(pGetLastError) && (pGetCiphers != NULL) && (pGetKEXs != NULL) && \
			(pGetConfig) && (pSetConfig != NULL) && (pGetCurrentCipher != NULL) && \
			(pGetCurrentKEX));

		if (!bRes) 
		{
			FreeLibrary(hinstSSHLib);
			hinstSSHLib = NULL;
		}
    }
	else
	{
		pStart_Session = NULL;
		pClose_Session = NULL;
		pSend = NULL;
		pDLL_WndProc = NULL;
		pRead_Buffer = NULL;
		pIsSessionClose = NULL;
		pGetLastError = NULL;
		pGetCiphers = NULL;
		pGetKEXs = NULL;
		pGetConfig = NULL;
		pSetConfig = NULL;
		pGetCurrentCipher = NULL;
		pGetCurrentKEX = NULL;

#ifdef RUS
		AfxMessageBox("Ќевозможно загрузить библиотеку SSH.");
#else
		AfxMessageBox("Can't load SSH library.");
#endif
	}

	return bRes;
}