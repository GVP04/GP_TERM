// DlgScreenSize.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgScreenSize.h"
#include "GP_TermDoc.h"
#include "GP_TermView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgScreenSize dialog


CDlgScreenSize::CDlgScreenSize(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgScreenSize::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgScreenSize)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgScreenSize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgScreenSize)
	DDX_Control(pDX, IDC_COMBO2, m_ComboCommand);
	DDX_Control(pDX, IDC_COMBO1, m_ComboSize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgScreenSize, CDialog)
	//{{AFX_MSG_MAP(CDlgScreenSize)
	ON_BN_CLICKED(IDC_BUTTON1, OnApply)
	ON_BN_CLICKED(IDC_BUTTON2, OnButtonDeleteSize)
	ON_BN_CLICKED(IDC_BUTTON9, OnButtonDeleteCommand)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgScreenSize message handlers

BOOL CDlgScreenSize::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString tmps,tmps2;
	Size czCurSize=GPC.m_Document->GetActiveScrSize();
	csCurSize.Format("%d x %d",czCurSize.Width,czCurSize.Height);
	m_ComboSize.SetWindowText(csCurSize);

	tmps=AfxGetApp()->GetProfileString(m_Comm.GPSectionName, "SCRSIZELIST",csCurSize);
	int i=1;
	while((tmps2=ExtractField(tmps,i++,"\x01"))!="")
	{
		czCurSize=GetSizeFromString(tmps2);
		if (czCurSize.Width>3)
		{
			tmps2.Format("%d x %d",czCurSize.Width,czCurSize.Height);
			m_ComboSize.AddString(tmps2);
		}
	}

	csCurCommand=AfxGetApp()->GetProfileString(m_Comm.GPSectionName, "SCRSIZECOMMAND","term %X,%Y");	
	m_ComboCommand.SetWindowText(csCurCommand);

	tmps=AfxGetApp()->GetProfileString(m_Comm.GPSectionName, "SCRSIZECOMMANDLIST",csCurCommand);
	i=1;
	while((tmps2=ExtractField(tmps,i++,"\x01"))!="")
	{
		m_ComboCommand.AddString(tmps2);
	}
	
	return TRUE; 
}

void CDlgScreenSize::OnOK() 
{
	if (VerifyData(TRUE))
	{
		SaveSettings();
		SetScreenSize();
		CDialog::OnOK();
	}
}

void CDlgScreenSize::OnCancel() 
{
	CDialog::OnCancel();
}

void CDlgScreenSize::OnApply() 
{
	if (VerifyData(TRUE))
	{
		SaveSettings();
		SetScreenSize();
	}
}

BOOL CDlgScreenSize::VerifyData(BOOL bShowMessage)
{
	BOOL ret=TRUE;
	CString tmps;
	CString tmps2;
	CString csMsg;
	Size sz;
	m_ComboSize.GetWindowText(tmps);
	sz=GetSizeFromString(tmps);
	if (sz.Width>3)
	{
		tmps2.Format("%d x %d",sz.Width,sz.Height);
		if (m_ComboSize.FindStringExact(0,tmps2)==CB_ERR)
			m_ComboSize.AddString(tmps2);

		m_ComboSize.SetWindowText(tmps2);
	}
	else
	{
		ret=FALSE;
		csMsg="Wrong screen size: "+tmps;
	}

	m_ComboCommand.GetWindowText(tmps);
	tmps.Replace("        "," ");
	tmps.Replace("    "," ");
	tmps.Replace("  "," ");
	tmps.Replace("  "," ");
	tmps2=tmps;
	tmps2.MakeUpper();
	if (tmps2.Find("%X",0)>0 && tmps2.Find("%Y",0)>0 && tmps2.Find("X%Y",0)<0 && tmps2.Find("Y%X",0)<0)
	{
		if (tmps2!=" " && tmps2!="" && m_ComboCommand.FindStringExact(0,tmps2)==CB_ERR)
			m_ComboCommand.AddString(tmps);
		m_ComboCommand.SetWindowText(tmps);
	}
	else
	{
		ret=FALSE;
		if (csMsg!="") csMsg+="\n";
		csMsg+="Wrong command: "+tmps;
	}

	if (!ret && bShowMessage)
		AfxMessageBox(csMsg,MB_ICONEXCLAMATION|MB_OK);

	return ret;
}

const Size CDlgScreenSize::GetSizeFromString(const char *iStr)
{
	Size ret(-1,-1);
	if (iStr)
	{
		while(*iStr && (*iStr<'0' || *iStr>'9')) iStr++;

		if (*iStr) ret.Width=atoi(iStr);

		while(*iStr && *iStr>='0' && *iStr<='9') iStr++;
		while(*iStr && (*iStr<'0' || *iStr>'9')) iStr++;

		if (*iStr) ret.Height=atoi(iStr);

		if (ret.Height<4 || ret.Height>1000 || ret.Width<4 || ret.Width>4000)
		{
			 ret.Width=-1;
			 ret.Height=-1;
		}
	}
	return ret;
}

void CDlgScreenSize::OnButtonDeleteSize() 
{
	CString tmps2;
	m_ComboSize.GetWindowText(tmps2);
	int nItem=m_ComboSize.FindStringExact(0,tmps2);
	if (nItem!=CB_ERR)	m_ComboSize.DeleteString(nItem);
	SaveSettings();
	m_ComboSize.SetWindowText("");
}

void CDlgScreenSize::OnButtonDeleteCommand() 
{
	CString tmps2;
	m_ComboCommand.GetWindowText(tmps2);
	int nItem=m_ComboCommand.FindStringExact(0,tmps2);
	if (nItem!=CB_ERR)	m_ComboCommand.DeleteString(nItem);
	SaveSettings();
	m_ComboCommand.SetWindowText("");
}

void CDlgScreenSize::SaveSettings()
{
	CString tmps;
	CString tmps2;
	int nItems;
	int i;
	nItems=m_ComboSize.GetCount();
	tmps="";
	if (nItems!=CB_ERR)
		for(i=0;i<nItems;i++)
		{
			m_ComboSize.GetLBText(i,tmps2);
			if (i) tmps+="\x01";
			tmps+=tmps2;
		}
	AfxGetApp()->WriteProfileString(m_Comm.GPSectionName, "SCRSIZELIST",tmps);

	nItems=m_ComboCommand.GetCount();
	tmps="";
	if (nItems!=CB_ERR)
		for(i=0;i<nItems;i++)
		{
			m_ComboCommand.GetLBText(i,tmps2);
			if (i) tmps+="\x01";
			tmps+=tmps2;
		}
	AfxGetApp()->WriteProfileString(m_Comm.GPSectionName, "SCRSIZECOMMANDLIST",tmps);
	m_ComboCommand.GetWindowText(tmps);
	AfxGetApp()->WriteProfileString(m_Comm.GPSectionName, "SCRSIZECOMMAND",tmps);	
}

void CDlgScreenSize::SetScreenSize()
{
	CString tmps;
	Size sz;
	m_ComboSize.GetWindowText(tmps);
	sz=GetSizeFromString(tmps);
	if (sz.Width>3)
	{
		GPC.m_Document->ResizeActiveScr(sz);
		m_ComboCommand.GetWindowText(tmps);
		char cVal[100];
		sprintf(cVal,"%d",sz.Width);
		tmps.Replace("%x",cVal);
		tmps.Replace("%X",cVal);
		sprintf(cVal,"%d",sz.Height);
		tmps.Replace("%y",cVal);
		tmps.Replace("%Y",cVal);
		tmps+="\r";
		GPC.cs_ScriptLine+="\\w250;"+tmps; 
		GPC.m_View->DoScriptCommand();
	}
}
