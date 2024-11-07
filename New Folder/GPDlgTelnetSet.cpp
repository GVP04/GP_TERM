// GPDlgTelnetSet.cpp : implementation file
//

#include "stdafx.h"
#include "GP_term.h"
#include "GPDlgTelnetSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPDlgTelnetSet dialog


GPDlgTelnetSet::GPDlgTelnetSet(GP_comm *iGPc, CWnd* pParent /*=NULL*/)
	: CDialog(GPDlgTelnetSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(GPDlgTelnetSet)
	//}}AFX_DATA_INIT
	m_AdvancedMode=0;
	GPc=iGPc;
}


void GPDlgTelnetSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GPDlgTelnetSet)
	DDX_Control(pDX, IDC_COMBOSHUTDOWN, m_ComboShutDown);
	DDX_Control(pDX, IDC_COMBOSVCWAIT, m_ComboSvcWait);
	DDX_Control(pDX, IDC_EDITNAME, m_EditName);
	DDX_Control(pDX, IDC_BUTTONADVANCED, m_btnAdvanced);
	DDX_Control(pDX, IDC_COMBOTERMTYPE, m_ComboType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GPDlgTelnetSet, CDialog)
	//{{AFX_MSG_MAP(GPDlgTelnetSet)
	ON_CBN_SELCHANGE(IDC_COMBOTERMTYPE, OnSelchangeCombotermtype)
	ON_BN_CLICKED(IDC_BUTTONDELIMITERS, OnButtondelimiters)
	ON_BN_CLICKED(IDC_BUTTONADVANCED, OnButtonadvanced)
	ON_BN_CLICKED(IDC_BUTTONSSH, OnButtonssh)
	ON_EN_CHANGE(IDC_EDITNAME, OnChangeEditname)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
//////////
// GPDlgTelnetSet message handlers
#include "GP_TermView.h"
void GPDlgTelnetSet::OnOK() 
{
	CString csTmpName;
	m_EditName.GetWindowText(csTmpName);
	CString csTmpSectionName;
	csTmpSectionName.Format("COMSETLIST\\%s",csTmpName);

	BOOL bDoIt=TRUE;
	if (AfxGetApp()->GetProfileInt(csTmpSectionName, "com_type",0xFFFFFFFF)!=0xFFFFFFFF)
	{
		#ifdef RUS
			csTmpName= "Перезаписать информацию о соединении - " + csTmpName + " ?";
		#else
			csTmpName= "Overwrite connection " + csTmpName + " ?";
		#endif
		bDoIt=(AfxMessageBox(csTmpName,MB_ICONQUESTION|MB_APPLMODAL|MB_OKCANCEL,0)==IDOK);
	}

	if (bDoIt)
	{
		GPc->GPSectionName=csTmpSectionName;
		char ha[1255];
		GetDlgItemText(IDC_IPADDRESS1,ha,250);
		GPc->GPSetHostName(ha);
		GetDlgItemText(IDC_EDITINITSTR,ha,990);
		GPc->SetInitStr(ha);
		GetDlgItemText(IDC_EDITINITSTR2,ha,990);
		GPc->SetEndStr(ha);
		GetDlgItemText(IDC_EDITCOMMENT,ha,990);
		GPc->SetComment(ha);

		GPc->SetDelayBeforeSendChar (GetDlgItemInt(IDC_EDITDBSC));
		GPc->SetDelayBeforeSendLine (GetDlgItemInt(IDC_EDITDBSL));
		GPc->SetDelayBeforeSendBlock(GetDlgItemInt(IDC_EDITDBSB));
		GPc->SetDelayAfterSendChar  (GetDlgItemInt(IDC_EDITDASC));
		GPc->SetDelayAfterSendLine  (GetDlgItemInt(IDC_EDITDASL));
		GPc->SetDelayAfterSendBlock (GetDlgItemInt(IDC_EDITDASB));
		GPc->SetPortNumber(GetDlgItemInt(IDC_EDITPORT));
		GPc->SetLockEventsEcho(IsDlgButtonChecked(IDC_CHECKLOCKECHO));
		GPc->SetTelnetFlag(IsDlgButtonChecked(IDC_CHECKTELNET)?1:0);
		GPc->dwUseSSH=IsDlgButtonChecked(IDC_CHECKSSH)?1:0;

		if (GPC.m_View)
		{
			int sel=m_ComboType.GetCurSel();
			if (sel!=CB_ERR)
			{
				int newtype=m_ComboType.GetItemData(sel);
				if (newtype!=CB_ERR)
				{
					AfxGetApp()->WriteProfileInt(GPc->GPSectionName, "TerminalType",newtype);
					if (GPc->GPSectionName==m_Comm.GPSectionName)
						m_TermCap.SetCurrentTerminalId(newtype);
				}
			}

			if ( GPC.m_View && m_Comm.GPSectionName==GPc->GPSectionName)
			{
				GPC.m_View->m_CRLFflag=IsDlgButtonChecked(IDC_CHECKCRLF);
				GPC.m_View->m_CRLFflag2=IsDlgButtonChecked(IDC_CHECKCRLF2);
			}
			AfxGetApp()->WriteProfileInt(GPc->GPSectionName, "m_CheckCRLF",IsDlgButtonChecked(IDC_CHECKCRLF));
			AfxGetApp()->WriteProfileInt(GPc->GPSectionName, "m_CheckCRLF2",IsDlgButtonChecked(IDC_CHECKCRLF2));
		}
		GPc->write_dcb();

		int tmpInt=GetDlgItemInt(IDC_EDITROWS);
		if (tmpInt>1 && tmpInt<512)
			AfxGetApp()->WriteProfileInt(GPc->GPSectionName, "INITROWS",tmpInt);
		tmpInt=GetDlgItemInt(IDC_EDITCOLUMNS);
		if (tmpInt>1 && tmpInt<1024)
			AfxGetApp()->WriteProfileInt(GPc->GPSectionName, "INITCOLUMNS",tmpInt);

		AfxGetApp()->WriteProfileInt(GPc->GPSectionName, "InitDelay",GetDlgItemInt(IDC_EDITINITDALAY));
		AfxGetApp()->WriteProfileInt(GPc->GPSectionName, "m_DontSendStopSeq",IsDlgButtonChecked(IDC_CHECKTELNET2)?1:0);
		
		AfxGetApp()->WriteProfileInt(GPc->GPSectionName, "m_HideTerminal",IsDlgButtonChecked(IDC_CHECKHIDDEN)?1:0);
		AfxGetApp()->WriteProfileInt(GPc->GPSectionName, "dwAltFlag",IsDlgButtonChecked(IDC_CHECKDISABLEALT)?1:0);

		CString tmpCS;
		GetDlgItemText(IDC_EDITCMDLINE,tmpCS);
		AfxGetApp()->WriteProfileString(GPc->GPSectionName, "CMDLINE",(LPCSTR)tmpCS);


		GetDlgItemText(IDC_EDITTITLE,tmpCS);
		AfxGetApp()->WriteProfileString(GPc->GPSectionName, "TERMTITLE",(LPCSTR)tmpCS);

		GetDlgItemText(IDC_EDITTITLE2,tmpCS);
		AfxGetApp()->WriteProfileString(GPc->GPSectionName, "MSGBOXTITLE",(LPCSTR)tmpCS);

		GetDlgItemText(IDC_EDITTITLE3,tmpCS);
		AfxGetApp()->WriteProfileString(GPc->GPSectionName, "ERRBOXTITLE",(LPCSTR)tmpCS);

		DWORD dwSHUTDOWN=0;

		if (IsDlgButtonChecked(IDC_CHECKLOCKEND	)) dwSHUTDOWN|=0x1000;
		if (IsDlgButtonChecked(IDC_CHECKLOCKEND2)) dwSHUTDOWN|=0x0001;
		tmpInt=m_ComboShutDown.GetCurSel();
		dwSHUTDOWN|=((tmpInt%4)*0x10+(tmpInt/4)*0x100);
		AfxGetApp()->WriteProfileInt(GPc->GPSectionName, "m_ShutdownFlags",dwSHUTDOWN);

		GetDlgItemText(IDC_EDITSVCNAME,tmpCS);
		AfxGetApp()->WriteProfileString(GPc->GPSectionName, "STUPSVC",(LPCSTR)tmpCS);
		GetDlgItemText(IDC_EDITSVCPARAMS,tmpCS);
		AfxGetApp()->WriteProfileString(GPc->GPSectionName, "STUPSVCPARAMS",(LPCSTR)tmpCS);
		GetDlgItemText(IDC_EDITSVCNAME2,tmpCS);
		AfxGetApp()->WriteProfileString(GPc->GPSectionName, "SHDNSVC",(LPCSTR)tmpCS);
		tmpInt=m_ComboSvcWait.GetCurSel();
		AfxGetApp()->WriteProfileInt(GPc->GPSectionName, "STUPSVCWAIT",tmpInt);

		AfxGetApp()->WriteProfileInt(GPc->GPSectionName, "CHECKSVCASK",IsDlgButtonChecked(IDC_CHECKSVCASK)?1:0);

		CDialog::OnOK();
	}
}

BOOL GPDlgTelnetSet::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetAdvancedMode(m_AdvancedMode);

	SetDlgItemText(IDC_IPADDRESS1,GPc->GPGetHostName());

	SetDlgItemText(IDC_EDITCOMMENT,GPc->GetComment());
	SetDlgItemText(IDC_EDITINITSTR,GPc->GetInitStr());
	SetDlgItemText(IDC_EDITINITSTR2,GPc->GetEndStr());
	SetDlgItemInt(IDC_EDITDBSC,GPc->GetDelayBeforeSendChar ());
	SetDlgItemInt(IDC_EDITDBSL,GPc->GetDelayBeforeSendLine ());
	SetDlgItemInt(IDC_EDITDBSB,GPc->GetDelayBeforeSendBlock());
	SetDlgItemInt(IDC_EDITDASC,GPc->GetDelayAfterSendChar  ());
	SetDlgItemInt(IDC_EDITDASL,GPc->GetDelayAfterSendLine  ());
	SetDlgItemInt(IDC_EDITDASB,GPc->GetDelayAfterSendBlock ());
	SetDlgItemInt(IDC_EDITPORT,GPc->GetPortNumber ());
	SetDlgItemInt(IDC_EDITINITDALAY,AfxGetApp()->GetProfileInt(GPc->GPSectionName, "InitDelay",500));
	
	CheckDlgButton(IDC_CHECKLOCKECHO, GPc->GetLockEventsEcho());
	CheckDlgButton(IDC_CHECKSSH, GPc->dwUseSSH);

	CheckDlgButton(IDC_CHECKTELNET, (GPc->GetTelnetFlag()&0x1)!=0);
	CheckDlgButton(IDC_CHECKTELNET2, AfxGetApp()->GetProfileInt(GPc->GPSectionName, "m_DontSendStopSeq",0));
	CheckDlgButton(IDC_CHECKDISABLEALT		, AfxGetApp()->GetProfileInt(GPc->GPSectionName, "dwAltFlag",0));

	m_TermCap.FillComboTerminalType(::GetDlgItem(m_hWnd,IDC_COMBOTERMTYPE),GPc->m_TerminalID);

	SetDlgItemText(IDC_EDITCMDLINE, AfxGetApp()->GetProfileString(GPc->GPSectionName, "CMDLINE",""));
	SetDlgItemText(IDC_EDITTITLE, AfxGetApp()->GetProfileString(GPc->GPSectionName, "TERMTITLE",""));
	SetDlgItemText(IDC_EDITTITLE2,AfxGetApp()->GetProfileString(GPc->GPSectionName, "MSGBOXTITLE",""));
	SetDlgItemText(IDC_EDITTITLE3,AfxGetApp()->GetProfileString(GPc->GPSectionName, "ERRBOXTITLE",""));

	SetDlgItemInt(IDC_EDITROWS,AfxGetApp()->GetProfileInt(GPc->GPSectionName, "INITROWS",25));
	SetDlgItemInt(IDC_EDITCOLUMNS,AfxGetApp()->GetProfileInt(GPc->GPSectionName, "INITCOLUMNS",80));

	SetDlgItemText(IDC_EDITNAME,ExtractField(GPc->GPSectionName, 2 ,"\\"));

	DWORD dwSHUTDOWN=AfxGetApp()->GetProfileInt(GPc->GPSectionName, "m_ShutdownFlags",0x1000);

	CheckDlgButton(IDC_CHECKLOCKEND			, (dwSHUTDOWN&0x1000)==0x1000);
	CheckDlgButton(IDC_CHECKLOCKEND2		, (dwSHUTDOWN&0x0001)==0x0001);

	CheckDlgButton(IDC_CHECKHIDDEN			, AfxGetApp()->GetProfileInt(GPc->GPSectionName, "m_HideTerminal",0));

	CheckDlgButton(IDC_CHECKCRLF			, AfxGetApp()->GetProfileInt(GPc->GPSectionName, "m_CheckCRLF",1));
	CheckDlgButton(IDC_CHECKCRLF2			, AfxGetApp()->GetProfileInt(GPc->GPSectionName, "m_CheckCRLF2",0));


	m_ComboShutDown.AddString("LOGOFF");
	m_ComboShutDown.AddString("POWEROFF");
	m_ComboShutDown.AddString("REBOOT");
	m_ComboShutDown.AddString("SHUTDOWN");

	m_ComboShutDown.AddString("FORCE_LOGOFF");
	m_ComboShutDown.AddString("FORCE_POWEROFF");
	m_ComboShutDown.AddString("FORCE_REBOOT");
	m_ComboShutDown.AddString("FORCE_SHUTDOWN");

	m_ComboShutDown.AddString("FORCEIFHUNG_LOGOFF");
	m_ComboShutDown.AddString("FORCEIFHUNG_POWEROFF");
	m_ComboShutDown.AddString("FORCEIFHUNG_REBOOT");
	m_ComboShutDown.AddString("FORCEIFHUNG_SHUTDOWN");

	m_ComboShutDown.AddString("LOCKWORKSTATION");

	m_ComboShutDown.SetCurSel(((dwSHUTDOWN/0x10)&0x3)+ ((dwSHUTDOWN/0x100)&0x3)*4);

	SetDlgItemText(IDC_EDITSVCNAME,		AfxGetApp()->GetProfileString(GPc->GPSectionName, "STUPSVC",""));
	SetDlgItemText(IDC_EDITSVCPARAMS,	AfxGetApp()->GetProfileString(GPc->GPSectionName, "STUPSVCPARAMS",""));
	SetDlgItemText(IDC_EDITSVCNAME2,	AfxGetApp()->GetProfileString(GPc->GPSectionName, "SHDNSVC",""));
	m_ComboSvcWait.AddString("Not");
	m_ComboSvcWait.AddString("SStart");
	m_ComboSvcWait.AddString("Wnd Destroy");
	m_ComboSvcWait.AddString("Wnd Hide");
	m_ComboSvcWait.AddString("Wnd Show");
	m_ComboSvcWait.SetCurSel(AfxGetApp()->GetProfileInt(GPc->GPSectionName, "STUPSVCWAIT",1));

	CheckDlgButton(IDC_CHECKSVCASK,		AfxGetApp()->GetProfileInt(GPc->GPSectionName, "CHECKSVCASK",0));

	return TRUE;
}

void GPDlgTelnetSet::OnSelchangeCombotermtype() 
{
	DWORD sel=::SendMessage(::GetDlgItem(m_hWnd,IDC_COMBOTERMTYPE),CB_GETCURSEL,0,0);
	if (sel!=CB_ERR)
		GPc->m_TerminalID=::SendMessage(::GetDlgItem(m_hWnd,IDC_COMBOTERMTYPE),CB_GETITEMDATA,sel,0);
}

#include "DlgDelimiters.h"

void GPDlgTelnetSet::OnButtondelimiters() 
{
	CDlgDelimiters dlg(GPc);
	dlg.DoModal();
}

void GPDlgTelnetSet::SetAdvancedMode(int iMode)
{
	m_AdvancedMode=iMode;

	CRect mRe;
	GetWindowRect(&mRe);
	m_btnAdvanced.SetCheck(m_AdvancedMode);

	CRect mRe2;
	::GetWindowRect(::GetDlgItem(m_hWnd,!iMode ? IDOK:IDC_EDITSVCNAME2),&mRe2);

	if (m_AdvancedMode)
		mRe.bottom=mRe2.bottom+20;
	else 
		mRe.bottom=mRe2.bottom+10;

	MoveWindow(&mRe);
}

void GPDlgTelnetSet::OnButtonadvanced() 
{
	m_AdvancedMode=1-m_AdvancedMode;
	SetAdvancedMode(m_AdvancedMode);
}

#include "DlgSetupSSH.h"

void GPDlgTelnetSet::OnButtonssh() 
{
	CDlgSetupSSH mDlg(GPc->GPSectionName);
	mDlg.DoModal();
}

void GPDlgTelnetSet::OnChangeEditname() 
{
	CString tmpName;
	m_EditName.GetWindowText(tmpName);
	if (tmpName.Replace(" ","")
		|| tmpName.Replace("/","")
		|| tmpName.Replace("\x10","")
		|| tmpName.Replace("\x13","")
		|| tmpName.Replace("\\","")	) 
	{
		int iStart=0,iEnd=0;
		m_EditName.GetSel(iStart,iEnd);
		m_EditName.SetWindowText(tmpName);
		if (iStart>0) iStart--;
		m_EditName.SetSel(iStart,iStart);
	}
}
