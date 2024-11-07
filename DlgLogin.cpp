// DlgLogin.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//+ 0x0001 - Enable empty password
//+ 0x0002 - Close terminal
//+ 0x0004 - 30 sec timelife
//+ 0x0008 - 120 sec timelife
//+ 0x0010 - Don't reset the timer by keyboard
//+ 0x0020 - Don't show progress
//+ 0x0040 - Don't send empty password
//+ 0x0080 - Account Name
//+ 0x0100 - Account Name & Account Password
//+ 0x0200 - Only three try on 3*30(120/150) seconds
//+ 0x0400 - Remember user/account IDs
//+ 0x0800 - Remember user/account password
//+ 0x1000 - Hide terminal while login 
//+ 0x2000 - Hide terminal after login

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin dialog


CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLogin)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_DlgFlags=0;
	m_MaxInputTime=0xFFFF;
	m_CurrentInputTime=0;
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLogin)
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialog)
	//{{AFX_MSG_MAP(CDlgLogin)
	ON_EN_CHANGE(IDC_EDITUSERID, OnChangeEdituserid)
	ON_EN_CHANGE(IDC_EDITPASSWORD, OnChangeEditpassword)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDITUSERID2, OnChangeEdituserid2)
	ON_EN_CHANGE(IDC_EDITPASSWORD2, OnChangeEditpassword2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin message handlers

BOOL CDlgLogin::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if ((m_DlgFlags&0x1000)) AfxGetMainWnd()->ShowWindow(SW_HIDE);

	OnChangeEditpassword();
	::SetFocus(::GetDlgItem(m_hWnd,IDC_EDITUSERID));
	::SetForegroundWindow(::GetDlgItem(m_hWnd,IDC_EDITUSERID));
	::SetWindowText(::GetDlgItem(m_hWnd,IDC_STATICDESCRIPTION),GPC.termCaption);

	int num=0;
	if ((num=GPC.GetImageListId("MISCS"))>=0)
	{
		HICON tmpHICON=GPC.a_GPImageList[num].m_IL.ExtractIcon(80);
		IMAGEINFO ii={0};
		GPC.a_GPImageList[num].m_IL.GetImageInfo(80,&ii);
		DestroyIcon(SetIcon(tmpHICON,ii.rcImage.bottom-ii.rcImage.top>16));
	}

	int delta=0;
	HWND tmpHWND;
	if (!(m_DlgFlags&0x080) || !(m_DlgFlags&0x100)) 
	{
		delta=25;
		tmpHWND=::GetDlgItem(m_hWnd,IDC_STATIC2);
		::SetWindowLong(tmpHWND,GWL_STYLE,::GetWindowLong(tmpHWND,GWL_STYLE)&(0xFFFFFFFF^WS_VISIBLE));
		tmpHWND=::GetDlgItem(m_hWnd,IDC_EDITPASSWORD2);
		::SetWindowLong(tmpHWND,GWL_STYLE,::GetWindowLong(tmpHWND,GWL_STYLE)&(0xFFFFFFFF^WS_VISIBLE));

	}
	if (!(m_DlgFlags&0x80)) 
	{
		delta=63;
		tmpHWND=::GetDlgItem(m_hWnd,IDC_EDITUSERID2);
		::SetWindowLong(tmpHWND,GWL_STYLE,::GetWindowLong(tmpHWND,GWL_STYLE)&(0xFFFFFFFF^WS_VISIBLE));
		tmpHWND=::GetDlgItem(m_hWnd,IDC_STATIC1);
		::SetWindowLong(tmpHWND,GWL_STYLE,::GetWindowLong(tmpHWND,GWL_STYLE)&(0xFFFFFFFF^WS_VISIBLE));
	}

	RECT re={0};
	::GetWindowRect(m_Progress.m_hWnd,&re);
	re.top-=delta;
	re.bottom-=delta;
	ScreenToClient(&re);
	::MoveWindow(m_Progress.m_hWnd,re.left,re.top,re.right-re.left,re.bottom-re.top,TRUE);
	::GetWindowRect(::GetDlgItem(m_hWnd,IDC_STATICDESCRIPTION),&re);
	re.top-=delta;
	re.bottom-=delta;
	ScreenToClient(&re);
	::MoveWindow(::GetDlgItem(m_hWnd,IDC_STATICDESCRIPTION),re.left,re.top,re.right-re.left,re.bottom-re.top,TRUE);

	::GetWindowRect(m_hWnd,&re);
	re.bottom-=delta;

	::MoveWindow(m_hWnd,re.left,re.top,re.right-re.left,re.bottom-re.top,TRUE);


	time_t tLast=AfxGetApp()->GetProfileInt("TEMP","S10",0);
	time_t tCurrent=CTime::GetCurrentTime().GetTime();
	int nTimes=AfxGetApp()->GetProfileInt("TEMP","S11",0);
	if (tCurrent-tLast>200)
	{
		nTimes=0;
	}

	if ((m_DlgFlags&(0x200))) 
	{
		if (nTimes==0) AfxGetApp()->WriteProfileInt("TEMP","S10",(int)tCurrent);
		nTimes++;
		if (!(m_DlgFlags&(0x04+0x08))) m_DlgFlags|=0x04;
		if (nTimes>2) m_DlgFlags|=0x02;
		if (nTimes>3) OnCancel();
	}
	else nTimes=0;

	AfxGetApp()->WriteProfileInt("TEMP","S11",nTimes);

	if ((m_DlgFlags&(0x04+0x08))) 
	{
		m_MaxInputTime=0;
		if ((m_DlgFlags&0x04)) m_MaxInputTime+=120;
		if ((m_DlgFlags&0x08)) m_MaxInputTime+=480;
		if (!(m_DlgFlags&0x20)) m_Progress.ModifyStyle(0,WS_VISIBLE);
	}

	m_Progress.SetRange32(0,m_MaxInputTime);
	m_Progress.SetPos(m_MaxInputTime);

	if ((m_DlgFlags&0x400)) 
		::SetWindowText(::GetDlgItem(m_hWnd,IDC_EDITUSERID)		,AfxGetApp()->GetProfileString("TEMP","S1",""));
	if ((m_DlgFlags&0x800))
		::SetWindowText(::GetDlgItem(m_hWnd,IDC_EDITPASSWORD)	,AfxGetApp()->GetProfileString("TEMP","S2",""));
	if ((m_DlgFlags&0x400))
		::SetWindowText(::GetDlgItem(m_hWnd,IDC_EDITUSERID2)	,AfxGetApp()->GetProfileString("TEMP","S3",""));
	if ((m_DlgFlags&0x800))
		::SetWindowText(::GetDlgItem(m_hWnd,IDC_EDITPASSWORD2)	,AfxGetApp()->GetProfileString("TEMP","S4",""));

	SetTimer(1,250,NULL);

	return FALSE;
}

void CDlgLogin::OnCancel() 
{
	char tmps[]={13,0,};
	if (!(GPC.Flags&GP_CUR_EXITFLAG))
	{
		m_Comm.GPSendBlock(tmps,1);
		if (!(m_DlgFlags&0x040))	m_Comm.GPSendBlock(tmps,1);
		if (!(m_DlgFlags&0x080))	m_Comm.GPSendBlock(tmps,1);
		if (!(m_DlgFlags&0x100))	m_Comm.GPSendBlock(tmps,1);
	}

	if ((m_DlgFlags&0x02) && !(GPC.Flags&GP_CUR_EXITFLAG))
	{
		GPC.Flags|=GP_CUR_EXITFLAG;
		AfxGetMainWnd()->PostMessage(WM_CLOSE,0,0);
	}

	if ((m_DlgFlags&0x2000)) AfxGetMainWnd()->ShowWindow(SW_HIDE);
	CDialog::OnCancel();
}

void CDlgLogin::OnOK() 
{
	char UserName[256]={250,0,0,0};
	char password[256]={250,0,0,0};
	char AccName[256]={250,0,0,0};
	char Accpassword[256]={250,0,0,0};
	char tmps[]={13,0,};

	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDITUSERID),EM_GETLINE,0,(LPARAM)UserName);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDITPASSWORD),EM_GETLINE,0,(LPARAM)password);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDITUSERID2),EM_GETLINE,0,(LPARAM)AccName);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDITPASSWORD2),EM_GETLINE,0,(LPARAM)Accpassword);

	AnsiToDos(UserName,0);
	AnsiToDos(password,0);
	AnsiToDos(AccName,0);
	AnsiToDos(Accpassword,0);
	m_Comm.GPSendBlock(UserName,(int)strlen(UserName));
	m_Comm.GPSendBlock(tmps,1);
	if ((m_DlgFlags&0x400)) AfxGetApp()->WriteProfileString("TEMP","S1",UserName);
	
	if (!(m_DlgFlags&0x40) || *password)
	{
		Sleep(200);
		m_Comm.GPSendBlock(password,(int)strlen(password));
		m_Comm.GPSendBlock(tmps,1);
		if ((m_DlgFlags&0x800)) AfxGetApp()->WriteProfileString("TEMP","S2",password);
	}

	if ((m_DlgFlags&0x80))
		if (!(m_DlgFlags&0x40) || *AccName)
		{
			Sleep(500);
			m_Comm.GPSendBlock(AccName,(int)strlen(AccName));
			m_Comm.GPSendBlock(tmps,1);
			if ((m_DlgFlags&0x400)) AfxGetApp()->WriteProfileString("TEMP","S3",AccName);
		}

	if ((m_DlgFlags&0x100))
		if (!(m_DlgFlags&0x40) || *Accpassword)
		{
			Sleep(200);
			m_Comm.GPSendBlock(Accpassword,(int)strlen(Accpassword));
			m_Comm.GPSendBlock(tmps,1);
			if ((m_DlgFlags&0x800)) AfxGetApp()->WriteProfileString("TEMP","S4",Accpassword);
		}
	
	if ((m_DlgFlags&0x2000)) AfxGetMainWnd()->ShowWindow(SW_HIDE);
	CDialog::OnOK();
}

void CDlgLogin::OnChangeEdituserid() 
{
	OnChangeEditpassword();
}

void CDlgLogin::OnChangeEditpassword() 
{
	char tmpsUser[256]={250,0,0,0};
	char tmpsPassword[256]={250,0,0,0};
	char tmpsUser2[256]={250,0,0,0};
	char tmpsPassword2[256]={250,0,0,0};
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDITUSERID),EM_GETLINE,0,(LPARAM)tmpsUser);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDITPASSWORD),EM_GETLINE,0,(LPARAM)tmpsPassword);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDITUSERID2),EM_GETLINE,0,(LPARAM)tmpsUser2);
	::SendMessage(::GetDlgItem(m_hWnd,IDC_EDITPASSWORD2),EM_GETLINE,0,(LPARAM)tmpsPassword2);

	::EnableWindow(::GetDlgItem(m_hWnd,IDOK),*tmpsUser && (*tmpsPassword || (m_DlgFlags&0x01)) && (*tmpsUser2 || !(m_DlgFlags&0x080)) && (*tmpsPassword2  || (m_DlgFlags&0x01) || !(m_DlgFlags&0x100)));
	m_CurrentInputTime=0;
}

void CDlgLogin::OnChangeEdituserid2() 
{
	OnChangeEditpassword();
}

void CDlgLogin::OnChangeEditpassword2() 
{
	OnChangeEditpassword();
}


BOOL CDlgLogin::PreTranslateMessage(MSG* pMsg) 
{

	if (pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN)
	{
		if (!::IsWindowEnabled(::GetDlgItem(m_hWnd,IDOK)) && ::GetFocus()!=::GetDlgItem(m_hWnd,IDCANCEL))
			pMsg->wParam=VK_TAB;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgLogin::OnTimer(UINT nIDEvent) 
{
	KillTimer(nIDEvent);
	m_CurrentInputTime++;
	m_Progress.SetPos(m_MaxInputTime-m_CurrentInputTime);
	if (m_CurrentInputTime>=m_MaxInputTime)
	{
		OnCancel();
	}
	SetTimer(nIDEvent,250,NULL);

	CDialog::OnTimer(nIDEvent);
}

