// GPAdmIsOn.cpp : implementation file
//

#include "stdafx.h"
#include "GP_term.h"
#include "GPAdmIsOn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPAdmIsOn dialog


GPAdmIsOn::GPAdmIsOn(BOOL *iStatus, CWnd* pParent /*=NULL*/)
	: CDialog(GPAdmIsOn::IDD, pParent)
{
	//{{AFX_DATA_INIT(GPAdmIsOn)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	Status=iStatus;
}


void GPAdmIsOn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GPAdmIsOn)
	DDX_Control(pDX, IDOK, m_Ok);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GPAdmIsOn, CDialog)
	//{{AFX_MSG_MAP(GPAdmIsOn)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPAdmIsOn message handlers

BOOL GPAdmIsOn::OnInitDialog() 
{
	CDialog::OnInitDialog();
	UpdOk();
	OnKillfocusEdit1();
	return TRUE;
}

void GPAdmIsOn::OnOK() 
{
	CDialog::OnOK();
}

void GPAdmIsOn::OnCancel() 
{
	*Status=FALSE;
	CDialog::OnCancel();
}

void GPAdmIsOn::OnKillfocusEdit1() 
{
	char str[20];
	char str2[20];
	GetDlgItemText(IDC_EDIT1,str,19);
	*Status=FALSE;
	
	if ((int)strlen(str)==4)
	{
		CTime tm = CTime::GetCurrentTime();
		sprintf(str2,"%2.2d%2.2d",tm.GetHour(),tm.GetMinute());
		if (str2[0]==str[3] && str2[1]==str[2] && str2[2]==str[1] && str2[3]==str[0]) *Status=TRUE;
	}

	UpdOk();
}

void GPAdmIsOn::UpdOk()
{
	m_Ok.EnableWindow(*Status);
}
