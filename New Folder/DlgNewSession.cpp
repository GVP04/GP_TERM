// DlgNewSession.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgNewSession.h"
#include "GP_TermView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNewSession dialog


CDlgNewSession::CDlgNewSession(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNewSession::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNewSession)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CDlgNewSession::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNewSession)
	DDX_Control(pDX, IDC_LIST1, m_ListConnections);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNewSession, CDialog)
	//{{AFX_MSG_MAP(CDlgNewSession)
	ON_BN_CLICKED(IDC_BUTTONLISTEN, OnButtonlisten)
	ON_BN_CLICKED(IDOK, OnStartNewSession)
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkListSessions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNewSession message handlers

BOOL CDlgNewSession::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CRect re;
	GetWindowRect(re);
	AUSI.AddSetMain(m_hWnd);
	AUSI.SetMinSize(m_hWnd,re.Width(),re.Height());
	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDC_LIST1)				,m_hWnd,"NNEE");

	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDOK)					,m_hWnd,"EEEE");

	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDC_STATICLISTENPORT)	,m_hWnd,"ENEN");
	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDC_EDITLISTENPORT)		,m_hWnd,"ENEN");
	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTONLISTEN)		,m_hWnd,"ENEN");
	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDC_EDITROTNAME)		,m_hWnd,"ENEN");
	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDC_STATICROT)			,m_hWnd,"ENEN");

	SetDlgItemInt(IDC_EDITLISTENPORT,AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "ListenPort",0),FALSE);

	m_ListConnections.ModifyStyle(0,LVS_SHOWSELALWAYS|LVS_SINGLESEL);
	m_ListConnections.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);

	#ifdef RUS
		m_ListConnections.InsertColumn(0,"Наименование",LVCFMT_LEFT,110);
		m_ListConnections.InsertColumn(1,"Тип",LVCFMT_CENTER,60);
		m_ListConnections.InsertColumn(2,"Адрес",LVCFMT_CENTER,90);
		m_ListConnections.InsertColumn(3,"Порт",LVCFMT_CENTER,50);
		m_ListConnections.InsertColumn(4,"Telnet",LVCFMT_CENTER,47);
		m_ListConnections.InsertColumn(5,"SSH",LVCFMT_CENTER,50);
		m_ListConnections.InsertColumn(6,"Терминал",LVCFMT_CENTER,70);
		m_ListConnections.InsertColumn(7,"Описание соединения",LVCFMT_LEFT,100);
		m_ListConnections.InsertColumn(8,"Текст в меню",LVCFMT_LEFT,100);
		m_ListConnections.InsertColumn(9,"При подключении к серверу",LVCFMT_LEFT,150);
		m_ListConnections.InsertColumn(10,"При завершении сеанса",LVCFMT_LEFT,150);
	#else
		m_ListConnections.InsertColumn(0,"Connection Name",LVCFMT_LEFT,110);
		m_ListConnections.InsertColumn(1,"Type",LVCFMT_CENTER,60);
		m_ListConnections.InsertColumn(2,"Address",LVCFMT_CENTER,90);
		m_ListConnections.InsertColumn(3,"Port",LVCFMT_CENTER,50);
		m_ListConnections.InsertColumn(4,"Telnet",LVCFMT_CENTER,47);
		m_ListConnections.InsertColumn(5,"SSH",LVCFMT_CENTER,50);
		m_ListConnections.InsertColumn(6,"Terminal",LVCFMT_CENTER,70);
		m_ListConnections.InsertColumn(7,"Description",LVCFMT_LEFT,100);
		m_ListConnections.InsertColumn(8,"Menu Item",LVCFMT_LEFT,100);
		m_ListConnections.InsertColumn(9,"Login script",LVCFMT_LEFT,150);
		m_ListConnections.InsertColumn(10,"Logout script",LVCFMT_LEFT,150);
	#endif

	HKEY curKey=NULL;
	char cListKey[200];
	sprintf(cListKey,"Software\\%s\\%s\\COMSETLIST",AfxGetApp()->m_pszRegistryKey,AfxGetApp()->m_pszAppName);
	::RegOpenKeyEx(HKEY_CURRENT_USER,cListKey,0,KEY_ALL_ACCESS,&curKey);
	if (curKey)
	{
		char skName[510];
		char nmClass[256];
		int i=0;
		*skName=0;
		*nmClass=0;
		DWORD lenName=480;
		DWORD lenClass=250;
		FILETIME ft={0};
		while(RegEnumKeyEx(curKey,i++,skName,&lenName,NULL,nmClass,&lenClass,&ft)!=ERROR_NO_MORE_ITEMS)
		{
			skName[lenName]=0;
			nmClass[lenClass]=0;
			GP_comm *tmpcomm=new GP_comm(0);

			tmpcomm->GPSectionName.Format("COMSETLIST\\%s",skName);
			tmpcomm->load_dcb(TRUE);
	
			int iItem=m_ListConnections.InsertItem(m_ListConnections.GetItemCount(),skName);

			CString csTmp;
			if (tmpcomm->Get_commType()==GPCT_COMPORT)
			{
				m_ListConnections.SetItemText(iItem,1,"COM");
				m_ListConnections.SetItemText(iItem,2,tmpcomm->GetComport());
			}
			else
			{
				m_ListConnections.SetItemText(iItem,1,"Socket");
				m_ListConnections.SetItemText(iItem,2,tmpcomm->GPGetHostName());
				csTmp.Format("%d",tmpcomm->GetPortNumber());
				m_ListConnections.SetItemText(iItem,3,csTmp);

				csTmp.Format("%d",tmpcomm->dwUseSSH);
				m_ListConnections.SetItemText(iItem,5,csTmp);
			}

			m_ListConnections.SetItemText(iItem,4,tmpcomm->GetTelnetFlag()==0?"":"Y");
			m_ListConnections.SetItemText(iItem,6,m_TermCap.GetTerminalNameById(tmpcomm->m_TerminalID));

			m_ListConnections.SetItemText(iItem,7,AfxGetApp()->GetProfileString(tmpcomm->GPSectionName, "TERMTITLE",""));
			m_ListConnections.SetItemText(iItem,8,tmpcomm->GetComment());
			m_ListConnections.SetItemText(iItem,9,tmpcomm->GetInitStr());
			m_ListConnections.SetItemText(iItem,10,tmpcomm->GetEndStr());
	
			if (strcmp(skName,ExtractField(m_Comm.GPSectionName,2,"\\"))==0)
				m_ListConnections.SetItemState(iItem,LVIS_SELECTED,LVIS_SELECTED);

			lenName=480;
			lenClass=250;
			delete tmpcomm;
		}

		RegCloseKey(curKey);
		curKey=NULL;
	}
	
	return TRUE;
}

void CDlgNewSession::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	AUSI.UpdateSize();
}

void CDlgNewSession::OnButtonlisten() 
{
	char tmptext[1024];
	*tmptext=0;
	int nChars=::GetWindowText(::GetDlgItem(m_hWnd,IDC_EDITLISTENPORT),tmptext,1000);
	tmptext[nChars]=0;
	if (*tmptext)
	{
		CString csCommand="-LISTEN";
		csCommand+=tmptext;

		#ifdef BRIZ
			_spawnlp(_P_NOWAIT,"BRIZ.exe","BRIZ.exe",csCommand,NULL);
		#else
			_spawnlp(_P_NOWAIT,"GP_term.exe","GP_term.exe",csCommand,NULL);
		#endif
		CDialog::OnOK();
	}

}

void CDlgNewSession::OnStartNewSession() 
{
	POSITION posit = m_ListConnections.GetFirstSelectedItemPosition();
	if (posit)
	{
		int iItem = m_ListConnections.GetNextSelectedItem(posit);
		CString sectionName=m_ListConnections.GetItemText(iItem,0);
		if (sectionName!="")
		{
			CString csCommand="-COMMNUM"+sectionName;
			char tmptext[1024];
			*tmptext=0;
			int nChars=::GetWindowText(::GetDlgItem(m_hWnd,IDC_EDITROTNAME),tmptext,1000);
			tmptext[nChars]=0;

			if (*tmptext) 
			{
				csCommand+=" -REGTERM";
				csCommand+=tmptext;
			}
			#ifdef BRIZ
				_spawnlp(_P_NOWAIT,"BRIZ.exe","BRIZ.exe",csCommand,NULL);
			#else
				_spawnlp(_P_NOWAIT,"GP_term.exe","GP_term.exe",csCommand,NULL);
			#endif
			CDialog::OnOK();
		}
	}

}

void CDlgNewSession::OnDblclkListSessions(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnStartNewSession();
	*pResult = 0;
}
