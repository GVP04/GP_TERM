#if !defined(AFX_DLGSTATISTICS_H__EAD2AEAD_9243_4F83_9931_CA38F1874112__INCLUDED_)
#define AFX_DLGSTATISTICS_H__EAD2AEAD_9243_4F83_9931_CA38F1874112__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgStatistics.h : header file
//
#include "GP_Term.h"
#include "GP_AutoSizing.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgStatistics dialog
typedef struct _STAT_SESSION
{
	DWORD dwBytesSend;
	DWORD dwBytesRead;
	DWORD dwGBytesSend;
	DWORD dwGBytesRead;
	DWORD dwEscSeq;
	DWORD dwEscUnknSeq;
} STAT_SESSION, *PSTAT_SESSION;

typedef struct _STAT_TERMINAL
{
	DWORD dwChOutput;
	DWORD dwCreateMenu;
	DWORD dwDeleteMenu;
	DWORD dwCreatePopupMenu;
	DWORD dwDeletePopupMenu;
	DWORD dwCreateDlg;
	DWORD dwDeleteDlg;
	DWORD dwCreateFrm;
	DWORD dwDeleteFrm;
	DWORD dwCreateObj;
	DWORD dwDeleteObj;
	DWORD dwCreateSpr;
	DWORD dwDeleteSpr;
	DWORD dwCreateList;
	DWORD dwDeleteList;
	DWORD dwCreateScr;
	DWORD dwDeleteScr;
	DWORD dwCreateWnd;
	DWORD dwDeleteWnd;
	DWORD dwMessages;
	DWORD dwMessagesMenu;
	DWORD dwMessagesSend;
	DWORD dwNMethodsSubObj;
	DWORD dwNMethodsFnObj;
	DWORD dwNMethodsSubSpr;
	DWORD dwNMethodsFnSpr;
	DWORD dwCOMMessagesSend;
	DWORD dwDllMessagesSend;
} STAT_TERMINAL, *PSTAT_TERMINAL;

typedef struct _STAT_OLE
{
	DWORD dwNMethods;
	DWORD dwMethodsTime;
	DWORD dwServerTime;
	DWORD dwNTimesServerRead;
	DWORD dwNItemsServerRead;
	DWORD dwNTimesServerWrite;
	DWORD dwNItemsServerWrite;
	DWORD dwNTimesTCL;
	DWORD dwNTimesSUB;
	DWORD dwTCLTime;
	DWORD dwSUBTime;
} STAT_OLE, *PSTAT_OLE;

typedef struct _STAT_FILES
{
	DWORD dwOpen;
	DWORD dwClose;
	DWORD dwRead;
	DWORD dwGRead;
	DWORD dwWrite;
	DWORD dwGWrite;
	DWORD dwCopy;
	DWORD dwDelete;
}	
 STAT_FILES, *PSTAT_FILES;


class CDlgStatistics : public CDialog
{
// Construction
public:
	void SAddSendCount(DWORD iCnt);
	void SAddReadCount(DWORD iCnt);
	void SAddFReadCount(DWORD iCnt);
	void SAddFWriteCount(DWORD iCnt);
	void SOleStartSUB();
	void SOleEndSUB();
	void SOleStartTCL();
	void SOleEndTCL();
	void SOleStartMethod();
	void SOleEndMethod();
	void SOleStartServer();
	void SOleEndServer();

	static char * FormatLength(char *iSTr, DWORD iDW1, DWORD iDW2);
	static char * FormatMSeconds(char *iStr, DWORD iMS);
	STAT_SESSION	m_STAT_SESSION;
	STAT_TERMINAL	m_STAT_TERMINAL;
	STAT_OLE		m_STAT_OLE;
	STAT_FILES		m_STAT_FILES;
	CDlgStatistics(CWnd* pParent = NULL);   // standard constructor
	~CDlgStatistics();
// Dialog Data
	//{{AFX_DATA(CDlgStatistics)
	enum { IDD = IDD_DLGSTATISTICS };
	CListCtrl	m_ListFiles;
	CListCtrl	m_ListOle;
	CListCtrl	m_ListSession;
	CTabCtrl	m_Tab;
	CListCtrl	m_ListTerminal;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgStatistics)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgStatistics)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonclear();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	char * m_cBuff;
	void UpdateTabs();
	void UpdateInfo();
	GP_AutoSizing DlgAutoSize;
	DWORD m_stSessionStart;
	void ClearInfo();
	DWORD dwTicksStartSUB;
	DWORD dwTicksStartTCL;
	DWORD dwTicksStartMethod;
	DWORD dwTicksStartServer;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSTATISTICS_H__EAD2AEAD_9243_4F83_9931_CA38F1874112__INCLUDED_)
