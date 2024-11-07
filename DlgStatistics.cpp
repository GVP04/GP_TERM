// DlgStatistics.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgStatistics.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgStatistics dialog


CDlgStatistics::CDlgStatistics(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStatistics::IDD, pParent)
{
	m_cBuff=new char [500];
	*m_cBuff=0;
	m_stSessionStart=::GetTickCount();
	ClearInfo();
	//{{AFX_DATA_INIT(CDlgStatistics)
	//}}AFX_DATA_INIT
}

CDlgStatistics::~CDlgStatistics()
{
	delete[] m_cBuff;
	m_cBuff=NULL;
}

void CDlgStatistics::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgStatistics)
	DDX_Control(pDX, IDC_LIST18, m_ListFiles);
	DDX_Control(pDX, IDC_LIST17, m_ListOle);
	DDX_Control(pDX, IDC_LIST16, m_ListSession);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	DDX_Control(pDX, IDC_LIST1, m_ListTerminal);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgStatistics, CDialog)
	//{{AFX_MSG_MAP(CDlgStatistics)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTONCLEAR, OnButtonclear)
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgStatistics message handlers

BOOL CDlgStatistics::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_Tab.InsertItem(0,"Session");
	m_Tab.SetCurSel(0);
	m_Tab.InsertItem(1,"Terminal");
	m_Tab.InsertItem(2,"Files");
	m_Tab.InsertItem(3,"COM");

	UpdateTabs();

	m_ListSession.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ListTerminal.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ListFiles.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ListOle.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_ListSession.InsertColumn(0,"TYPE",LVCFMT_LEFT,200,0);
	m_ListSession.InsertColumn(1,"VALUE",LVCFMT_LEFT,222,0);

	m_ListTerminal.InsertColumn(0,"TYPE",LVCFMT_LEFT,200,0);
	m_ListTerminal.InsertColumn(1,"VALUE",LVCFMT_LEFT,222,0);

	m_ListFiles.InsertColumn(0,"TYPE",LVCFMT_LEFT,200,0);
	m_ListFiles.InsertColumn(1,"VALUE",LVCFMT_LEFT,222,0);

	m_ListOle.InsertColumn(0,"TYPE",LVCFMT_LEFT,200,0);
	m_ListOle.InsertColumn(1,"VALUE",LVCFMT_LEFT,222,0);
#ifdef RUS
	m_ListSession.InsertItem(1000,"Время работы");
	m_ListSession.InsertItem(1000,"Принято байт");
	m_ListSession.InsertItem(1000,"Передано байт");
	m_ListSession.InsertItem(1000,"Обработано Esc последовательностей");
	m_ListSession.InsertItem(1000,"Неизвестных Esc последовательностей");

	m_ListTerminal.InsertItem(1000,"Операций отображения");
	m_ListTerminal.InsertItem(1000,"Обработано сообщений");
	m_ListTerminal.InsertItem(1000,"Отправлено сообщений");
	m_ListTerminal.InsertItem(1000,"Отправлено сообщений меню");
	m_ListTerminal.InsertItem(1000,"Создано символьных экранов");
	m_ListTerminal.InsertItem(1000,"Удалено символьных экранов");
	m_ListTerminal.InsertItem(1000,"Создано символьных окон");
	m_ListTerminal.InsertItem(1000,"Удалено символьных окон");
	m_ListTerminal.InsertItem(1000,"Создано popup меню");
	m_ListTerminal.InsertItem(1000,"Удалено popup меню");
	m_ListTerminal.InsertItem(1000,"Создано меню");
	m_ListTerminal.InsertItem(1000,"Удалено меню");
	m_ListTerminal.InsertItem(1000,"Создано диалогов");
	m_ListTerminal.InsertItem(1000,"Удалено диалогов");
	m_ListTerminal.InsertItem(1000,"Создано фреймов");
	m_ListTerminal.InsertItem(1000,"Удалено фреймов");
	m_ListTerminal.InsertItem(1000,"Создано объектов");
	m_ListTerminal.InsertItem(1000,"Удалено объектов");
	m_ListTerminal.InsertItem(1000,"Создано справочников");
	m_ListTerminal.InsertItem(1000,"Удалено справочников");
	m_ListTerminal.InsertItem(1000,"Создано списков");
	m_ListTerminal.InsertItem(1000,"Удалено списков");
	m_ListTerminal.InsertItem(1000,"Выполнено методов объектов");
	m_ListTerminal.InsertItem(1000,"Выполнено функций объектов");
	m_ListTerminal.InsertItem(1000,"Выполнено методов справочников");
	m_ListTerminal.InsertItem(1000,"Выполнено функций справочников");

	m_ListFiles.InsertItem(1000,"Открыто файлов");
	m_ListFiles.InsertItem(1000,"Закрыто файлов");
	m_ListFiles.InsertItem(1000,"Прочитано байт");
	m_ListFiles.InsertItem(1000,"Записано байт");
	m_ListFiles.InsertItem(1000,"Скопировано файлов");
	m_ListFiles.InsertItem(1000,"Удалено файлов");


	m_ListOle.InsertItem(1000,"Выполнено методов");
	m_ListOle.InsertItem(1000,"Затрачено времени");
	m_ListOle.InsertItem(1000,"Затрачено времени сервером");
	m_ListOle.InsertItem(1000,"Операций чтения");
	m_ListOle.InsertItem(1000,"Прочитано элементов");
	m_ListOle.InsertItem(1000,"Операций записи");
	m_ListOle.InsertItem(1000,"Записано элементов");
	m_ListOle.InsertItem(1000,"Серверних TCL команд");
	m_ListOle.InsertItem(1000,"Серверных процедур");
	m_ListOle.InsertItem(1000,"Затрачено времени TCL");
	m_ListOle.InsertItem(1000,"Затрачено времени SUB");
#else
	 m_ListSession. InsertItem (1000, "Operating time");
	 m_ListSession. InsertItem (1000, "Is accepted byte");
	 m_ListSession. InsertItem (1000, "Transferred bytes");
	 m_ListSession. InsertItem (1000, "Processed Esc sequences");
	 m_ListSession. InsertItem (1000, "Unknown Esc sequences");

	 m_ListTerminal. InsertItem (1000,"Operations of display");
	 m_ListTerminal. InsertItem (1000,"Processed messages");
	 m_ListTerminal. InsertItem (1000,"Sent messages");
	 m_ListTerminal. InsertItem (1000,"Sent messages of the menu");
	 m_ListTerminal. InsertItem (1000,"Created symbolical screens");
	 m_ListTerminal. InsertItem (1000,"Removed symbolical screens");
	 m_ListTerminal. InsertItem (1000,"Created symbolical windows");
	 m_ListTerminal. InsertItem (1000,"Removed symbolical windows");
	 m_ListTerminal. InsertItem (1000,"Created popup the menu");
	 m_ListTerminal. InsertItem (1000,"Removed popup the menu");
	 m_ListTerminal. InsertItem (1000,"Created by the menu");
	 m_ListTerminal. InsertItem (1000,"Removed the menu");
	 m_ListTerminal. InsertItem (1000,"Created dialogues");
	 m_ListTerminal. InsertItem (1000,"Removed dialogues");
	 m_ListTerminal. InsertItem (1000,"Created frames");
	 m_ListTerminal. InsertItem (1000,"Removed frames");
	 m_ListTerminal. InsertItem (1000,"Created objects");
	 m_ListTerminal. InsertItem (1000,"Removed objects");
	 m_ListTerminal. InsertItem (1000,"Created Tables");
	 m_ListTerminal. InsertItem (1000,"Removed Tables");
	 m_ListTerminal. InsertItem (1000,"Created lists");
	 m_ListTerminal. InsertItem (1000,"Removed lists");
	 m_ListTerminal. InsertItem (1000,"Executed methods of objects");
	 m_ListTerminal. InsertItem (1000,"Executed functions of objects");
	 m_ListTerminal. InsertItem (1000,"Executed methods of Tables");
	 m_ListTerminal. InsertItem (1000,"Executed functions of Tables");

	 m_ListFiles. InsertItem (1000,"Opened files");
	 m_ListFiles. InsertItem (1000,"Closed files");
	 m_ListFiles. InsertItem (1000,"Read by byte");
	 m_ListFiles. InsertItem (1000,"Written down by byte");
	 m_ListFiles. InsertItem (1000,"Copied files");
	 m_ListFiles. InsertItem (1000,"Removed files");


	 m_ListOle. InsertItem (1000,"Executed methods");
	 m_ListOle. InsertItem (1000,"Spent time");
	 m_ListOle. InsertItem (1000,"Spent time by a server");
	 m_ListOle. InsertItem (1000,"Operations of reading");
	 m_ListOle. InsertItem (1000,"Read elements");
	 m_ListOle. InsertItem (1000,"Operations of item");
	 m_ListOle. InsertItem (1000,"Written down elements");
	 m_ListOle. InsertItem (1000,"Server TCL commands");
	 m_ListOle. InsertItem (1000,"Server procedures");
	 m_ListOle. InsertItem (1000,"Spent time by TCL");
	 m_ListOle. InsertItem (1000,"Spent time by SUB");
#endif


	DlgAutoSize.AddSetMain(m_hWnd);
	DlgAutoSize.AddWnd(m_ListSession.m_hWnd,m_hWnd,"NNEE");
	DlgAutoSize.AddWnd(m_ListTerminal.m_hWnd,m_hWnd,"NNEE");
	DlgAutoSize.AddWnd(m_ListFiles.m_hWnd,m_hWnd,"NNEE");
	DlgAutoSize.AddWnd(m_ListOle.m_hWnd,m_hWnd,"NNEE");
	DlgAutoSize.AddWnd(::GetDlgItem(m_hWnd,IDOK),m_hWnd,"EEEE");
	DlgAutoSize.AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTONCLEAR),m_hWnd,"EEEE");

	UpdateInfo();

	SetTimer(1,2500,NULL);

	return TRUE;
}

void CDlgStatistics::OnTimer(UINT nIDEvent) 
{
	UpdateInfo();
	CDialog::OnTimer(nIDEvent);
}

void CDlgStatistics::UpdateInfo()
{
	if (m_hWnd && IsWindowVisible())
	{
		CString txt;
		CTime m_time;
		m_ListSession.SetItemText(0,1,FormatMSeconds(m_cBuff,::GetTickCount()-m_stSessionStart));
		m_ListSession.SetItemText(1,1,FormatLength(m_cBuff,m_STAT_SESSION.dwBytesRead,m_STAT_SESSION.dwGBytesRead));
		m_ListSession.SetItemText(2,1,FormatLength(m_cBuff,m_STAT_SESSION.dwBytesSend,m_STAT_SESSION.dwGBytesSend));
		m_ListSession.SetItemText(3,1,FormatLength(m_cBuff,m_STAT_SESSION.dwEscSeq,0));
		m_ListSession.SetItemText(4,1,FormatLength(m_cBuff,m_STAT_SESSION.dwEscUnknSeq,0));
		
		m_ListTerminal.SetItemText( 0,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwChOutput,0));
		m_ListTerminal.SetItemText( 1,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwMessages,0));
		m_ListTerminal.SetItemText( 2,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwMessagesSend,0));
		m_ListTerminal.SetItemText( 3,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwMessagesMenu,0));
		m_ListTerminal.SetItemText( 4,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwCreateScr,0));
		m_ListTerminal.SetItemText( 5,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwDeleteScr,0));
		m_ListTerminal.SetItemText( 6,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwCreateDlg,0));
		m_ListTerminal.SetItemText( 7,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwDeleteDlg,0));
		m_ListTerminal.SetItemText( 8,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwCreatePopupMenu,0));
		m_ListTerminal.SetItemText( 9,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwDeletePopupMenu,0));
		m_ListTerminal.SetItemText(10,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwCreateMenu,0));
		m_ListTerminal.SetItemText(11,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwDeleteMenu,0));
		m_ListTerminal.SetItemText(12,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwCreateDlg,0));
		m_ListTerminal.SetItemText(13,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwDeleteDlg,0));
		m_ListTerminal.SetItemText(14,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwCreateFrm,0));
		m_ListTerminal.SetItemText(15,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwDeleteFrm,0));
		m_ListTerminal.SetItemText(16,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwCreateObj,0));
		m_ListTerminal.SetItemText(17,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwDeleteObj,0));
		m_ListTerminal.SetItemText(18,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwCreateSpr,0));
		m_ListTerminal.SetItemText(19,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwDeleteSpr,0));
		m_ListTerminal.SetItemText(20,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwCreateList,0));
		m_ListTerminal.SetItemText(21,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwDeleteList,0));
		m_ListTerminal.SetItemText(22,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwNMethodsSubObj,0));
		m_ListTerminal.SetItemText(23,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwNMethodsFnObj,0));
		m_ListTerminal.SetItemText(24,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwNMethodsSubSpr,0));
		m_ListTerminal.SetItemText(25,1,FormatLength(m_cBuff,m_STAT_TERMINAL.dwNMethodsFnSpr,0));

		m_ListFiles.SetItemText( 0,1,FormatLength(m_cBuff,m_STAT_FILES.dwOpen,0));
		m_ListFiles.SetItemText( 1,1,FormatLength(m_cBuff,m_STAT_FILES.dwClose,0));
		m_ListFiles.SetItemText( 2,1,FormatLength(m_cBuff,m_STAT_FILES.dwRead,m_STAT_FILES.dwGRead));
		m_ListFiles.SetItemText( 3,1,FormatLength(m_cBuff,m_STAT_FILES.dwWrite,m_STAT_FILES.dwGWrite));
		m_ListFiles.SetItemText( 4,1,FormatLength(m_cBuff,m_STAT_FILES.dwCopy,0));
		m_ListFiles.SetItemText( 5,1,FormatLength(m_cBuff,m_STAT_FILES.dwDelete,0));

		m_ListOle.SetItemText( 0,1,FormatLength(m_cBuff,m_STAT_OLE.dwNMethods,0));
		m_ListOle.SetItemText( 1,1,FormatMSeconds(m_cBuff,m_STAT_OLE.dwMethodsTime));
		m_ListOle.SetItemText( 2,1,FormatMSeconds(m_cBuff,m_STAT_OLE.dwServerTime));
		m_ListOle.SetItemText( 3,1,FormatLength(m_cBuff,m_STAT_OLE.dwNTimesServerRead,0));
		m_ListOle.SetItemText( 4,1,FormatLength(m_cBuff,m_STAT_OLE.dwNItemsServerRead,0));
		m_ListOle.SetItemText( 5,1,FormatLength(m_cBuff,m_STAT_OLE.dwNTimesServerWrite,0));
		m_ListOle.SetItemText( 6,1,FormatLength(m_cBuff,m_STAT_OLE.dwNItemsServerWrite,0));
		m_ListOle.SetItemText( 7,1,FormatLength(m_cBuff,m_STAT_OLE.dwNTimesTCL,0));
		m_ListOle.SetItemText( 8,1,FormatLength(m_cBuff,m_STAT_OLE.dwNTimesSUB,0));
		m_ListOle.SetItemText( 9,1,FormatMSeconds(m_cBuff,m_STAT_OLE.dwTCLTime));
		m_ListOle.SetItemText(10,1,FormatMSeconds(m_cBuff,m_STAT_OLE.dwSUBTime));
	}
}

void CDlgStatistics::ClearInfo()
{
	dwTicksStartSUB=0;
	dwTicksStartTCL=0;
	dwTicksStartMethod=0;
	dwTicksStartServer=0;
	ZeroMemory(&m_STAT_SESSION,sizeof(STAT_SESSION));
	ZeroMemory(&m_STAT_TERMINAL,sizeof(STAT_TERMINAL));
	ZeroMemory(&m_STAT_OLE,sizeof(STAT_OLE));
	ZeroMemory(&m_STAT_FILES,sizeof(STAT_FILES));
}

void CDlgStatistics::OnButtonclear() 
{
	ClearInfo();
	UpdateInfo();
}

void CDlgStatistics::OnSize(UINT nType, int cx, int cy) 
{
	BOOL DOIT=TRUE;
	if (nType!=SIZE_MINIMIZED && m_hWnd)
	{
		DOIT=DlgAutoSize.CheckMainSize(m_hWnd,nType,&cx, &cy);
		if (DOIT) CDialog::OnSize(nType, cx, cy);
		else Invalidate();

		try{DlgAutoSize.UpdateSize();}catch(...){			GPC.m_ErrReport.GPWriteErrorLog("CDlgStatistics", "OnSize","");}
	}
}

void CDlgStatistics::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateTabs();
	
	*pResult = 0;
}

void CDlgStatistics::UpdateTabs()
{
	m_ListSession.ModifyStyle(WS_VISIBLE,0);
	m_ListTerminal.ModifyStyle(WS_VISIBLE,0);
	m_ListFiles.ModifyStyle(WS_VISIBLE,0);
	m_ListOle.ModifyStyle(WS_VISIBLE,0);

	switch(m_Tab.GetCurSel())
	{
	case 0:
		m_ListSession.ModifyStyle(0,WS_VISIBLE);
		m_ListSession.Invalidate();
		break;
	case 1:
		m_ListTerminal.ModifyStyle(0,WS_VISIBLE);
		m_ListTerminal.Invalidate();
		break;
	case 2:
		m_ListFiles.ModifyStyle(0,WS_VISIBLE);
		m_ListFiles.Invalidate();
		break;
	case 3:
		m_ListOle.ModifyStyle(0,WS_VISIBLE);
		m_ListOle.Invalidate();
		break;
	}

}

BOOL CDlgStatistics::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	
	return CDialog::OnCommand(wParam, lParam);
}

void CDlgStatistics::OnClose() 
{
	
	CDialog::OnOK();
}

char * CDlgStatistics::FormatMSeconds(char *iStr, DWORD iMS)
{
	if (iStr)
	{
		*iStr=0;
		sprintf(iStr,"%dms (%dd %2.2dh %2.2dm %2.2ds %3.3dms)",iMS,iMS/(3600000*24),(iMS/3600000)%60,(iMS/60000)%60,(iMS/1000)%60,iMS%1000);
	}
	return iStr;
}

char * CDlgStatistics::FormatLength(char *iStr, DWORD iDW1, DWORD iDW2)
{
	if (iStr)
	{
		*iStr=0;
		sprintf(iStr,"00000%9.9d%9.9d",iDW2,iDW1);
		char *pos=iStr;
		while(*pos && *pos<='0') pos++;
		int i=(23-(pos-iStr))%3;
		char *pos2=iStr;
		do
		{
			if (--i<0)
			{
				i=2;
				if (pos2!=iStr) 
					*(pos2++)=' ';
			}
			*(pos2++)=*(pos++);
		}
		while(*pos);
		*pos2=0;
		if (*iStr==0) *iStr='0',iStr[1]=0;

	}
	return iStr;
}

void CDlgStatistics::SAddSendCount(DWORD iCnt)
{
	m_STAT_SESSION.dwBytesSend+=iCnt;
	if (m_STAT_SESSION.dwBytesSend>=1000000000) m_STAT_SESSION.dwBytesSend-=1000000000,m_STAT_SESSION.dwGBytesSend++;
}

void CDlgStatistics::SAddReadCount(DWORD iCnt)
{
	m_STAT_SESSION.dwBytesRead+=iCnt;
	if (m_STAT_SESSION.dwBytesRead>=1000000000) m_STAT_SESSION.dwBytesRead-=1000000000,m_STAT_SESSION.dwGBytesRead++;
}

void CDlgStatistics::SAddFReadCount(DWORD iCnt)
{
	m_STAT_FILES.dwRead+=iCnt;
	if (m_STAT_FILES.dwRead>=1000000000) m_STAT_FILES.dwRead-=1000000000,m_STAT_FILES.dwGRead++;
}

void CDlgStatistics::SAddFWriteCount(DWORD iCnt)
{
	m_STAT_FILES.dwWrite+=iCnt;
	if (m_STAT_FILES.dwWrite>=1000000000) m_STAT_FILES.dwWrite-=1000000000,m_STAT_FILES.dwGWrite++;
}

void CDlgStatistics::SOleStartSUB()
{
	dwTicksStartSUB=::GetTickCount();
}

void CDlgStatistics::SOleEndSUB()
{
	m_STAT_OLE.dwNTimesSUB+=::GetTickCount()-dwTicksStartSUB;
}

void CDlgStatistics::SOleStartTCL()
{
	dwTicksStartTCL=::GetTickCount();
}

void CDlgStatistics::SOleEndTCL()
{
	m_STAT_OLE.dwNTimesTCL+=::GetTickCount()-dwTicksStartTCL;
}

void CDlgStatistics::SOleStartMethod()
{
	dwTicksStartMethod=::GetTickCount();
	m_STAT_OLE.dwNMethods++;
}

void CDlgStatistics::SOleEndMethod()
{
	m_STAT_OLE.dwMethodsTime+=::GetTickCount()-dwTicksStartMethod;
}

void CDlgStatistics::SOleStartServer()
{
	dwTicksStartServer=::GetTickCount();
}

void CDlgStatistics::SOleEndServer()
{
	m_STAT_OLE.dwServerTime+=::GetTickCount()-dwTicksStartServer;
}
