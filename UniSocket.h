// UniSocket.h: interface for the CUniSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNISOCKET_H__E28DA242_2D3E_4D81_95DE_2D47492C299E__INCLUDED_)
#define AFX_UNISOCKET_H__E28DA242_2D3E_4D81_95DE_2D47492C299E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class GP_comm;

#define DLL_SSH_LGXF_OVR  1		       /* existing logfile overwrite */
#define DLL_SSH_LGXF_APN  0		       /* existing logfile append */
#define DLL_SSH_LGXF_ASK -1		       /* existing logfile ask */
#define DLL_SSH_LGTYP_NONE  0		       /* logmode: no logging */
#define DLL_SSH_LGTYP_ASCII 1		       /* logmode: pure ascii */
#define DLL_SSH_LGTYP_DEBUG 2		       /* logmode: all chars of traffic */
#define DLL_SSH_LGTYP_PACKETS 3		       /* logmode: SSH data packets */


enum {
    /*
     * SSH-2 key exchange algorithms
     */
    DLL_SSH_KEX_WARN,
    DLL_SSH_KEX_DHGROUP1,
    DLL_SSH_KEX_DHGROUP14,
    DLL_SSH_KEX_DHGEX,
    DLL_SSH_KEX_MAX
};

enum {
    /*
     * SSH ciphers (both SSH-1 and SSH-2)
     */
    DLL_SSH_CIPHER_WARN,		       /* pseudo 'cipher' */
    DLL_SSH_CIPHER_3DES,
    DLL_SSH_CIPHER_BLOWFISH,
    DLL_SSH_CIPHER_AES,			       /* (SSH-2 only) */
    DLL_SSH_CIPHER_DES,
    DLL_SSH_CIPHER_MAX			       /* no. ciphers (inc warn) */
};

enum {
    /*
     * Proxy types.
     */
    DLL_SSH_PROXY_NONE, DLL_SSH_PROXY_SOCKS4, DLL_SSH_PROXY_SOCKS5,
    DLL_SSH_PROXY_HTTP, DLL_SSH_PROXY_TELNET, DLL_SSH_PROXY_CMD
};


enum {
    /*
     * Network address types. Used for specifying choice of IPv4/v6
     * in config; also used in proxy.c to indicate whether a given
     * host name has already been resolved or will be resolved at
     * the proxy end.
     */
    DLL_SSH_ADDRTYPE_UNSPEC, DLL_SSH_ADDRTYPE_IPV4, DLL_SSH_ADDRTYPE_IPV6, DLL_SSH_ADDRTYPE_NAME
};

/*
 * X11 auth mechanisms we know about.
 */
enum {
    DLL_SSH_X11_NO_AUTH,
    DLL_SSH_X11_MIT,                           /* MIT-MAGIC-COOKIE-1 */
    DLL_SSH_X11_XDM,			       /* XDM-AUTHORIZATION-1 */
    DLL_SSH_X11_NAUTHS
};

struct DLL_SSH_Filename {char path[FILENAME_MAX];};
typedef struct DLL_SSH_Filename DLL_SSH_Filename;
struct DLL_SSH_config_tag {
    /* Basic options */
    char host[512];
    int port;
    int protocol;
    int addressfamily;
    int close_on_exit;
    int warn_on_close;
    int ping_interval;		       /* in seconds */
    int tcp_nodelay;
    int tcp_keepalives;
    /* Proxy options */
    char proxy_exclude_list[512];
    int proxy_dns;
    int even_proxy_localhost;
    int proxy_type;
    char proxy_host[512];
    int proxy_port;
    char proxy_username[128];
    char proxy_password[128];
    char proxy_telnet_command[512];
    /* SSH options */
    char remote_cmd[512];
    char remote_cmd2[512];	       /* fallback if the first fails
					* (used internally for scp) */
    char *remote_cmd_ptr;	       /* might point to a larger command
				        * but never for loading/saving */
    char *remote_cmd_ptr2;	       /* might point to a larger command
				        * but never for loading/saving */
    int nopty;
    int compression;
    int ssh_kexlist[DLL_SSH_KEX_MAX]; //int ssh_kexlist[KEX_MAX];
    int ssh_rekey_time;		       /* in minutes */
    char ssh_rekey_data[16];
    int agentfwd;
    int change_username;	       /* allow username switching in SSH-2 */
    int ssh_cipherlist[DLL_SSH_CIPHER_MAX]; //int ssh_cipherlist[CIPHER_MAX];
    DLL_SSH_Filename keyfile;
    int sshprot;		       /* use v1 or v2 when both available */
    int ssh2_des_cbc;		       /* "des-cbc" unrecommended SSH-2 cipher */
    int try_tis_auth;
    int try_ki_auth;
    int ssh_subsys;		       /* run a subsystem rather than a command */
    int ssh_subsys2;		       /* fallback to go with remote_cmd2 */
    int ssh_no_shell;		       /* avoid running a shell */
    /* Telnet options */
    char termtype[32];
    char termspeed[32];
    char environmt[1024];	       /* VAR\tvalue\0VAR\tvalue\0\0 */
    char username[100];
    char localusername[100];
    /* Keyboard options */
    int telnet_keyboard;
    int telnet_newline;
    /* Terminal options */
    int width, height;
    DLL_SSH_Filename logfilename;
    int logtype;
    int logxfovr;
    int logflush;
    int logomitpass;
    int logomitdata;
    /* X11 forwarding */
    int x11_forward;
    char x11_display[128];
    int x11_auth;
    /* port forwarding */
    int lport_acceptall; /* accept conns from hosts other than localhost */
    int rport_acceptall; /* same for remote forwarded ports (SSH-2 only) */
    /*
     * The port forwarding string contains a number of
     * NUL-terminated substrings, terminated in turn by an empty
     * string (i.e. a second NUL immediately after the previous
     * one). Each string can be of one of the following forms:
     * 
     *   [LR]localport\thost:port
     *   [LR]localaddr:localport\thost:port
     *   Dlocalport
     *   Dlocaladdr:localport
     */
    char portfwd[1024];
    /* SSH bug compatibility modes */
    int sshbug_ignore1, sshbug_plainpw1, sshbug_rsa1,
	sshbug_hmac2, sshbug_derivekey2, sshbug_rsapad2,
	sshbug_pksessid2, sshbug_rekey2;
};
typedef struct DLL_SSH_config_tag DLL_SSH_Config;

typedef int (_stdcall *DLL_SSH_Start_Session)(int inst, int hwndInst);
typedef void (_stdcall *DLL_SSH_Close_Session)(void);
typedef void (_stdcall *DLL_SSH_ldisc_send)(char *buf, int len, int interactive);
typedef int (_stdcall *DLL_SSH_WndProc)(UINT message, WPARAM wParam, LPARAM lParam);
typedef int (_stdcall *DLL_SSH_Read_Buffer)(char *data, int len);
typedef BOOL (_stdcall *DLL_SSH_IsSessionClose)();
typedef int (_stdcall *DLL_SSH_GetLastError)(int *iErrorType, char *strError, int nStrError);
typedef int (_stdcall *DLL_SSH_GetCiphers)(char **ciphers, int nBuff);
typedef int (_stdcall *DLL_SSH_GetKEXs)(char **kexes, int nBuff);
typedef DLL_SSH_Config (_stdcall *DLL_SSH_GetConfig)();
typedef void (_stdcall *DLL_SSH_SetConfig)(DLL_SSH_Config cfgTmp);
typedef int (_stdcall *DLL_SSH_GetCurrentCipher)();
typedef int (_stdcall *DLL_SSH_GetCurrentKEX)();

class CUniSocket  
{
friend class GPCurrent;
public:
	CUniSocket();
	int Send(const void *repl, int outp);
	int Receive(const void *inputbuf,int nread);
	virtual void Close();
	int InitUniSocket(const char *iHost, int iPort);
	CUniSocket(GP_comm *iMasterComm);
	virtual ~CUniSocket();
	const GP_comm *m_MasterComm;
	int SendMessageToDLL(UINT message, WPARAM wParam, LPARAM lParam);
	BOOL IsSessionClose();
	int GetLastError(int *iErrorType, char *strError, int nStrError);
	int GetCiphers(char **ciphers, int nBuff);
	int GetKEXs(char **kexes, int nBuff);
	DLL_SSH_Config GetConfig();
	void SetConfig(DLL_SSH_Config cfgTmp);
	int GetCurrentCipher();
	int GetCurrentKEX();
private:
	HINSTANCE hinstSSHLib;
	BOOL PrepareSSHLibrary();
	DLL_SSH_Start_Session pStart_Session;
	DLL_SSH_Close_Session pClose_Session;
	DLL_SSH_ldisc_send pSend;
	DLL_SSH_WndProc pDLL_WndProc;
	DLL_SSH_Read_Buffer pRead_Buffer;
	DLL_SSH_IsSessionClose pIsSessionClose;
	DLL_SSH_GetLastError pGetLastError;
	DLL_SSH_GetCiphers	pGetCiphers;
	DLL_SSH_GetKEXs	pGetKEXs;
	DLL_SSH_GetConfig pGetConfig;
	DLL_SSH_SetConfig pSetConfig;
	DLL_SSH_GetCurrentCipher pGetCurrentCipher;
	DLL_SSH_GetCurrentKEX pGetCurrentKEX;
};

#endif // !defined(AFX_UNISOCKET_H__E28DA242_2D3E_4D81_95DE_2D47492C299E__INCLUDED_)
