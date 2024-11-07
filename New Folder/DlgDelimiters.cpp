// DlgDelimiters.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgDelimiters.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDelimiters dialog


CDlgDelimiters::CDlgDelimiters(GP_comm *imComm, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDelimiters::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDelimiters)
	m_IN1 = 0;
	m_IN2 = 0;
	m_IN3 = 0;
	m_IN4 = 0;
	m_IN5 = 0;
	m_IN6 = 0;
	m_OUT1 = 0;
	m_OUT2 = 0;
	m_OUT3 = 0;
	m_OUT5 = 0;
	m_OUT4 = 0;
	m_OUT6 = 0;
	//}}AFX_DATA_INIT
	mComm=imComm;
}


void CDlgDelimiters::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDelimiters)
	DDX_Text(pDX, IDC_EDITINPUT1, m_OUT1);
	DDV_MinMaxUInt(pDX, m_OUT1, 0, 255);
	DDX_Text(pDX, IDC_EDITINPUT2, m_OUT2);
	DDV_MinMaxUInt(pDX, m_OUT2, 0, 255);
	DDX_Text(pDX, IDC_EDITINPUT3, m_OUT3);
	DDV_MinMaxUInt(pDX, m_OUT3, 0, 255);
	DDX_Text(pDX, IDC_EDITINPUT4, m_OUT5);
	DDV_MinMaxUInt(pDX, m_OUT5, 0, 255);
	DDX_Text(pDX, IDC_EDITINPUT5, m_OUT4);
	DDV_MinMaxUInt(pDX, m_OUT4, 0, 255);
	DDX_Text(pDX, IDC_EDITINPUT6, m_OUT6);
	DDV_MinMaxUInt(pDX, m_OUT6, 0, 255);
	DDX_Text(pDX, IDC_EDITOUTPUT1, m_IN1);
	DDV_MinMaxUInt(pDX, m_IN1, 0, 255);
	DDX_Text(pDX, IDC_EDITOUTPUT2, m_IN2);
	DDV_MinMaxUInt(pDX, m_IN2, 0, 255);
	DDX_Text(pDX, IDC_EDITOUTPUT3, m_IN3);
	DDV_MinMaxUInt(pDX, m_IN3, 0, 255);
	DDX_Text(pDX, IDC_EDITOUTPUT5, m_IN4);
	DDV_MinMaxUInt(pDX, m_IN4, 0, 255);
	DDX_Text(pDX, IDC_EDITOUTPUT4, m_IN5);
	DDV_MinMaxUInt(pDX, m_IN5, 0, 255);
	DDX_Text(pDX, IDC_EDITOUTPUT6, m_IN6);
	DDV_MinMaxUInt(pDX, m_IN6, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDelimiters, CDialog)
	//{{AFX_MSG_MAP(CDlgDelimiters)
	ON_EN_CHANGE(IDC_EDITINPUT1, OnChangeEditinput)
	ON_BN_CLICKED(IDC_BUTTON7, OnButtonQM)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonD3)
	ON_EN_CHANGE(IDC_EDITINPUT2, OnChangeEditinput)
	ON_EN_CHANGE(IDC_EDITINPUT3, OnChangeEditinput)
	ON_EN_CHANGE(IDC_EDITINPUT4, OnChangeEditinput)
	ON_EN_CHANGE(IDC_EDITINPUT5, OnChangeEditinput)
	ON_EN_CHANGE(IDC_EDITINPUT6, OnChangeEditinput)
	ON_EN_CHANGE(IDC_EDITOUTPUT1, OnChangeEditinput)
	ON_EN_CHANGE(IDC_EDITOUTPUT2, OnChangeEditinput)
	ON_EN_CHANGE(IDC_EDITOUTPUT3, OnChangeEditinput)
	ON_EN_CHANGE(IDC_EDITOUTPUT4, OnChangeEditinput)
	ON_EN_CHANGE(IDC_EDITOUTPUT5, OnChangeEditinput)
	ON_EN_CHANGE(IDC_EDITOUTPUT6, OnChangeEditinput)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDelimiters message handlers

BOOL CDlgDelimiters::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if (mComm)
	{
		m_IN1=mComm->DelimiterIn1;
		m_IN2=mComm->DelimiterIn2;
		m_IN3=mComm->DelimiterIn3;
		m_IN4=mComm->DelimiterIn4;
		m_IN5=mComm->DelimiterIn5;
		m_IN6=mComm->DelimiterIn6;
		m_OUT1=mComm->DelimiterSrc1;
		m_OUT2=mComm->DelimiterSrc2;
		m_OUT3=mComm->DelimiterSrc3;
		m_OUT5=mComm->DelimiterSrc4;
		m_OUT4=mComm->DelimiterSrc5;
		m_OUT6=mComm->DelimiterSrc6;
	}
	UpdateData(FALSE);
	OnChangeEditinput();
	return TRUE;
}

void CDlgDelimiters::OnCancel() 
{
	CDialog::OnCancel();
}

void CDlgDelimiters::OnOK() 
{
	UpdateData();
	mComm->DelimiterIn1= m_IN1;
	mComm->DelimiterIn2= m_IN2;
	mComm->DelimiterIn3= m_IN3;
	mComm->DelimiterIn4= m_IN4;
	mComm->DelimiterIn5= m_IN5;
	mComm->DelimiterIn6= m_IN6;
	mComm->DelimiterSrc1=m_OUT1;
	mComm->DelimiterSrc2=m_OUT2;
	mComm->DelimiterSrc3=m_OUT3;
	mComm->DelimiterSrc4=m_OUT5;
	mComm->DelimiterSrc5=m_OUT4;
	mComm->DelimiterSrc6=m_OUT6;
	CDialog::OnOK();
}

void CDlgDelimiters::OnChangeEditinput() 
{
	DWORD ids[]={
		IDC_STATIC_1,IDC_STATIC_2,IDC_STATIC_3,IDC_STATIC_4,IDC_STATIC_5,IDC_STATIC_6,
		IDC_STATIC_11,IDC_STATIC_12,IDC_STATIC_13,IDC_STATIC_14,IDC_STATIC_15,IDC_STATIC_16,
	};
	DWORD ide[]={
		IDC_EDITINPUT1,IDC_EDITINPUT2,IDC_EDITINPUT3,IDC_EDITINPUT4,IDC_EDITINPUT5,IDC_EDITINPUT6,
		IDC_EDITOUTPUT1,IDC_EDITOUTPUT2,IDC_EDITOUTPUT3,IDC_EDITOUTPUT4,IDC_EDITOUTPUT5,IDC_EDITOUTPUT6,
	};

	CString tmps;
	char ss[3]={0};
	int i;
	for(i=0;i<12;i++)
	{
		GetDlgItemText(ide[i],tmps);
		ss[0]=atoi(tmps);
		SetDlgItemText(ids[i],ss);
	}
}


void CDlgDelimiters::OnButtonQM() 
{
	m_OUT1=254;
	m_OUT2=253;
	m_OUT3=252;
	m_OUT5=251;
	m_OUT4=250;
	m_OUT6=255;
	m_IN1 =182;
	m_IN2 =181;
	m_IN3 =180;
	m_IN4 =179;
	m_IN5 =178;
	m_IN6 =177;
	UpdateData(FALSE);
	OnChangeEditinput();
}

void CDlgDelimiters::OnButtonD3() 
{
	m_IN1 ='^';
	m_IN2 =']';
	m_IN3 ='\\';
	m_IN4 =4;
	m_IN5 =5;
	m_IN6 =6;
	m_OUT1='^';
	m_OUT2=']';
	m_OUT3='\\';
	m_OUT5=4;
	m_OUT4=5;
	m_OUT6=6;
	UpdateData(FALSE);
	OnChangeEditinput();
}

void CDlgDelimiters::OnButton8() 
{
	m_OUT1=254;
	m_OUT2=253;
	m_OUT3=252;
	m_OUT5=251;
	m_OUT4=250;
	m_OUT6=255;
	m_IN1 =254;
	m_IN2 =253;
	m_IN3 =252;
	m_IN4 =251;
	m_IN5 =250;
	m_IN6 =255;
	UpdateData(FALSE);
	OnChangeEditinput();
}
