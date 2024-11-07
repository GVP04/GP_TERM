// DlgDumpSettings.cpp : implementation file
//

#include "stdafx.h"
#include "GP_term.h"
#include "DlgDumpSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDumpSettings dialog

CDlgDumpSettings::CDlgDumpSettings(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDumpSettings::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDumpSettings)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CDlgDumpSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDumpSettings)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgDumpSettings, CDialog)
	//{{AFX_MSG_MAP(CDlgDumpSettings)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonViewSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDumpSettings message handlers

BOOL CDlgDumpSettings::OnInitDialog()
{
	CDialog::OnInitDialog();

	CheckDlgButton(IDC_CHECKDUMPOUT		,m_Comm.GetDumpMode()&GPC_DUMPOUT		);
	CheckDlgButton(IDC_CHECKDUMPOUTHEX	,m_Comm.GetDumpMode()&GPC_DUMPOUTHEX	);
	CheckDlgButton(IDC_CHECKDUMPOUTDEC	,m_Comm.GetDumpMode()&GPC_DUMPOUTDEC	);
	CheckDlgButton(IDC_CHECKDUMPOUTCHAR	,m_Comm.GetDumpMode()&GPC_DUMPOUTCHAR	);
	CheckDlgButton(IDC_CHECKDUMPIN		,m_Comm.GetDumpMode()&GPC_DUMPIN		);
	CheckDlgButton(IDC_CHECKDUMPINHEX	,m_Comm.GetDumpMode()&GPC_DUMPINHEX		);
	CheckDlgButton(IDC_CHECKDUMPINDEC	,m_Comm.GetDumpMode()&GPC_DUMPINDEC		);
	CheckDlgButton(IDC_CHECKDUMPINCHAR	,m_Comm.GetDumpMode()&GPC_DUMPINCHAR	);
	CheckDlgButton(IDC_CHECKDUMPREM		,m_Comm.GetDumpMode()&GPC_DUMPREM		);
	CheckDlgButton(IDC_CHECKDUMPREMHEX	,m_Comm.GetDumpMode()&GPC_DUMPREMHEX	);
	CheckDlgButton(IDC_CHECKDUMPREMDEC	,m_Comm.GetDumpMode()&GPC_DUMPREMDEC	);
	CheckDlgButton(IDC_CHECKDUMPREMCHAR	,m_Comm.GetDumpMode()&GPC_DUMPREMCHAR	);
	CheckDlgButton(IDC_CHECKDUMPREMID	,m_Comm.GetDumpMode()&GPC_DUMPREMID		);
	CheckDlgButton(IDC_CHECKDUMPSPACE	,m_Comm.GetDumpMode()&GPC_DUMPSPACE		);
	CheckDlgButton(IDC_CHECKDUMPCRLF	,m_Comm.GetDumpMode()&GPC_DUMPCRLF		);
	SetDlgItemInt(IDC_EDITDUMPNLINE,m_Comm.maxnLineDump,FALSE);
	SetDlgItemInt(IDC_EDITDUMPNCHAR,m_Comm.maxnCharDump,FALSE);
	SetDlgItemText(IDC_EDITDUMPREFIX,m_Comm.m_DumpPrefix);

	return TRUE;
}

void CDlgDumpSettings::OnOK()
{
	m_Comm.SetDumpMode(
		(IsDlgButtonChecked(IDC_CHECKDUMPOUT		)==TRUE?GPC_DUMPOUT		:0)|
		(IsDlgButtonChecked(IDC_CHECKDUMPOUTHEX		)==TRUE?GPC_DUMPOUTHEX	:0)|
		(IsDlgButtonChecked(IDC_CHECKDUMPOUTDEC		)==TRUE?GPC_DUMPOUTDEC	:0)|
		(IsDlgButtonChecked(IDC_CHECKDUMPOUTCHAR	)==TRUE?GPC_DUMPOUTCHAR	:0)|
		(IsDlgButtonChecked(IDC_CHECKDUMPIN			)==TRUE?GPC_DUMPIN		:0)|
		(IsDlgButtonChecked(IDC_CHECKDUMPINHEX		)==TRUE?GPC_DUMPINHEX	:0)|
		(IsDlgButtonChecked(IDC_CHECKDUMPINDEC		)==TRUE?GPC_DUMPINDEC	:0)|
		(IsDlgButtonChecked(IDC_CHECKDUMPINCHAR		)==TRUE?GPC_DUMPINCHAR	:0)|
		(IsDlgButtonChecked(IDC_CHECKDUMPREM		)==TRUE?GPC_DUMPREM		:0)|
		(IsDlgButtonChecked(IDC_CHECKDUMPREMHEX		)==TRUE?GPC_DUMPREMHEX	:0)|
		(IsDlgButtonChecked(IDC_CHECKDUMPREMDEC		)==TRUE?GPC_DUMPREMDEC	:0)|
		(IsDlgButtonChecked(IDC_CHECKDUMPREMCHAR	)==TRUE?GPC_DUMPREMCHAR	:0)|
		(IsDlgButtonChecked(IDC_CHECKDUMPREMID		)==TRUE?GPC_DUMPREMID	:0)|
		(IsDlgButtonChecked(IDC_CHECKDUMPSPACE		)==TRUE?GPC_DUMPSPACE	:0)|
		(IsDlgButtonChecked(IDC_CHECKDUMPCRLF		)==TRUE?GPC_DUMPCRLF	:0));

	m_Comm.maxnLineDump=GetDlgItemInt(IDC_EDITDUMPNLINE);
	m_Comm.maxnCharDump=GetDlgItemInt(IDC_EDITDUMPNCHAR);
	GetDlgItemText(IDC_EDITDUMPREFIX,m_Comm.m_DumpPrefix);

	m_Comm.write_dcb();

	CDialog::OnOK();
}

#include "DlgNotepadSet.h"

void CDlgDumpSettings::OnButtonViewSet()
{
	CDlgNotepadSet dlg;
	dlg.m_csSectionName="NotepadDumpSet";
	dlg.DoModal();
}
