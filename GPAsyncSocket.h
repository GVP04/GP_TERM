#if !defined(AFX_GPASYNCSOCKET_H__99D33A02_C2A3_44CC_A14A_5FBCC34BFA6B__INCLUDED_)
#define AFX_GPASYNCSOCKET_H__99D33A02_C2A3_44CC_A14A_5FBCC34BFA6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPAsyncSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CGPAsyncSocket command target

class CGPAsyncSocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CGPAsyncSocket();
	virtual ~CGPAsyncSocket();

// Overrides
public:
	static char * SSH_ConnectToHost(char *host, int port, char **realhost, int nodelay);
	static char * SSH_Init(char *host, int port, char **realhost, int nodelay);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGPAsyncSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnOutOfBandData(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);
	virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CGPAsyncSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPASYNCSOCKET_H__99D33A02_C2A3_44CC_A14A_5FBCC34BFA6B__INCLUDED_)
