// GPAsyncSocket.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPAsyncSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGPAsyncSocket

CGPAsyncSocket::CGPAsyncSocket()
{
}

CGPAsyncSocket::~CGPAsyncSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CGPAsyncSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CGPAsyncSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CGPAsyncSocket member functions

void CGPAsyncSocket::OnAccept(int nErrorCode) 
{
	CAsyncSocket::OnAccept(nErrorCode);
}

void CGPAsyncSocket::OnClose(int nErrorCode) 
{
	CAsyncSocket::OnClose(nErrorCode);
}

void CGPAsyncSocket::OnConnect(int nErrorCode) 
{
	CAsyncSocket::OnConnect(nErrorCode);
}

void CGPAsyncSocket::OnOutOfBandData(int nErrorCode) 
{
	CAsyncSocket::OnOutOfBandData(nErrorCode);
}

void CGPAsyncSocket::OnReceive(int nErrorCode) 
{
	CAsyncSocket::OnReceive(nErrorCode);
}

void CGPAsyncSocket::OnSend(int nErrorCode) 
{
	CAsyncSocket::OnSend(nErrorCode);
}

int CGPAsyncSocket::Receive(void* lpBuf, int nBufLen, int nFlags) 
{
	return CAsyncSocket::Receive(lpBuf, nBufLen, nFlags);
}

int CGPAsyncSocket::Send(const void* lpBuf, int nBufLen, int nFlags) 
{
	return CAsyncSocket::Send(lpBuf, nBufLen, nFlags);
}
/*
char * CGPAsyncSocket::SSH_Init(char *host, int port, char **realhost, int nodelay)
{
    char *p;

#ifdef MSCRYPTOAPI
    if (crypto_startup() == 0)
	return "Microsoft high encryption pack not installed!";
#endif

    ssh_send_ok = 0;
    ssh_editing = 0;
    ssh_echoing = 0;
    ssh1_throttle_count = 0;
    ssh_overall_bufsize = 0;
    ssh_fallback_cmd = 0;

    p = connect_to_host(host, port, realhost, nodelay);

    return p;
}

char * CGPAsyncSocket::SSH_ConnectToHost(char *host, int port, char **realhost, int nodelay)
{
    static struct plug_function_table fn_table = {
	ssh_closing,
	ssh_receive,
	ssh_sent,
	NULL
    }, *fn_table_ptr = &fn_table;

    SockAddr addr;
    char *err;

    savedhost = smalloc(1 + (int)strlen(host));
    if (!savedhost)
	fatalbox("Out of memory");
    strcpy(savedhost, host);

    if (port < 0)
	port = 22;		       
    savedport = port;

    {
	char buf[200];
	sprintf(buf, "Looking up host \"%.170s\"", host);
	logevent(buf);
    }
    addr = sk_namelookup(host, realhost);
    if ((err = sk_addr_error(addr)))
	return err;

    {
	char buf[200], addrbuf[100];
	sk_getaddr(addr, addrbuf, 100);
	sprintf(buf, "Connecting to %.100s port %d", addrbuf, port);
	logevent(buf);
    }
    s = new_connection(addr, *realhost, port, 0, 1, nodelay, &fn_table_ptr);
    if ((err = sk_socket_error(s))) {
	s = NULL;
	return err;
    }

    return NULL;

}
*/
