// CDlgOLESet.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "Dlg_OLESet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOLESet dialog


CDlgOLESet::CDlgOLESet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOLESet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOLESet)
	m_WTCL = 0;
	m_WSUB = 0;
	m_WFRead = 0;
	m_WSystem = 0;
	m_WMM = 0;
	m_WInput = 0;
	m_WFWrite = 0;
	m_WFOther = 0;
	m_CTCL = 0;
	m_CSystem = 0;
	m_CSUB = 0;
	m_CMM = 0;
	m_CInput = 0;
	m_CFWrite = 0;
	m_CFRead = 0;
	m_CFOther = 0;
	m_tFOther = 0;
	m_tFRead = 0;
	m_tFWrite = 0;
	m_tInput = 0;
	m_tMM = 0;
	m_tSUB = 0;
	m_tSystem = 0;
	m_tTCL = 0;
	//}}AFX_DATA_INIT
}


void CDlgOLESet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOLESet)
	DDX_Control(pDX, IDC_SPINWAITFOTHER, m_sWFOther);
	DDX_Control(pDX, IDC_SPINWAITTCL, m_sWTCL);
	DDX_Control(pDX, IDC_SPINWAITSUB, m_sWSUB);
	DDX_Control(pDX, IDC_SPINWAITINPUT, m_sWInput);
	DDX_Control(pDX, IDC_SPINWAITFREAD, m_sWFRead);
	DDX_Control(pDX, IDC_SPINWAITFWRITE, m_sWFWrite);
	DDX_Control(pDX, IDC_SPINWAITSYSTEM, m_sWSystem);
	DDX_Control(pDX, IDC_SPINWAITMM, m_sWMM);
	DDX_Control(pDX, IDC_SPINCNTTCL, m_sCTCL);
	DDX_Control(pDX, IDC_SPINCNTSUB, m_sCSUB);
	DDX_Control(pDX, IDC_SPINCNTFREAD, m_sCFRead);
	DDX_Control(pDX, IDC_SPINCNTFWRITE, m_sCFWrite);
	DDX_Control(pDX, IDC_SPINCNTFOTHER, m_sCFOther);
	DDX_Control(pDX, IDC_SPINCNTINPUT, m_sCInput);
	DDX_Control(pDX, IDC_SPINCNTSYSTEM, m_sCSystem);
	DDX_Control(pDX, IDC_SPINCNTMM, m_sCMM);
	DDX_Text(pDX, IDC_EDWAITTCL, m_WTCL);
	DDV_MinMaxUInt(pDX, m_WTCL, 1, 10000);
	DDX_Text(pDX, IDC_EDWAITSUB, m_WSUB);
	DDV_MinMaxUInt(pDX, m_WSUB, 1, 10000);
	DDX_Text(pDX, IDC_EDWAITFREAD, m_WFRead);
	DDV_MinMaxUInt(pDX, m_WFRead, 1, 10000);
	DDX_Text(pDX, IDC_EDWAITSYSTEM, m_WSystem);
	DDV_MinMaxUInt(pDX, m_WSystem, 1, 10000);
	DDX_Text(pDX, IDC_EDWAITMM, m_WMM);
	DDV_MinMaxUInt(pDX, m_WMM, 1, 10000);
	DDX_Text(pDX, IDC_EDWAITINPUT, m_WInput);
	DDV_MinMaxUInt(pDX, m_WInput, 1, 10000);
	DDX_Text(pDX, IDC_EDWAITFWRITE, m_WFWrite);
	DDV_MinMaxUInt(pDX, m_WFWrite, 1, 10000);
	DDX_Text(pDX, IDC_EDWAITFOTHER, m_WFOther);
	DDV_MinMaxUInt(pDX, m_WFOther, 1, 10000);
	DDX_Text(pDX, IDC_EDCNTTCL, m_CTCL);
	DDV_MinMaxUInt(pDX, m_CTCL, 5, 10000);
	DDX_Text(pDX, IDC_EDCNTSYSTEM, m_CSystem);
	DDV_MinMaxUInt(pDX, m_CSystem, 5, 100000);
	DDX_Text(pDX, IDC_EDCNTSUB, m_CSUB);
	DDV_MinMaxUInt(pDX, m_CSUB, 5, 100000);
	DDX_Text(pDX, IDC_EDCNTMM, m_CMM);
	DDV_MinMaxUInt(pDX, m_CMM, 5, 500);
	DDX_Text(pDX, IDC_EDCNTINPUT, m_CInput);
	DDV_MinMaxUInt(pDX, m_CInput, 5, 100000);
	DDX_Text(pDX, IDC_EDCNTFWRITE, m_CFWrite);
	DDV_MinMaxUInt(pDX, m_CFWrite, 5, 100000);
	DDX_Text(pDX, IDC_EDCNTFREAD, m_CFRead);
	DDV_MinMaxUInt(pDX, m_CFRead, 5, 100000);
	DDX_Text(pDX, IDC_EDCNTFOTHER, m_CFOther);
	DDV_MinMaxUInt(pDX, m_CFOther, 5, 100000);
	DDX_Text(pDX, IDC_EDCNTFOTHER2, m_tFOther);
	DDX_Text(pDX, IDC_EDCNTFREAD2, m_tFRead);
	DDX_Text(pDX, IDC_EDCNTFWRITE2, m_tFWrite);
	DDX_Text(pDX, IDC_EDCNTINPUT2, m_tInput);
	DDX_Text(pDX, IDC_EDCNTMM2, m_tMM);
	DDX_Text(pDX, IDC_EDCNTSUB2, m_tSUB);
	DDX_Text(pDX, IDC_EDCNTSYSTEM2, m_tSystem);
	DDX_Text(pDX, IDC_EDCNTTCL2, m_tTCL);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOLESet, CDialog)
	//{{AFX_MSG_MAP(CDlgOLESet)
	ON_EN_UPDATE(IDC_EDCNTFOTHER, OnUpdateEdcntfother)
	ON_EN_UPDATE(IDC_EDCNTFWRITE, OnUpdateEdcntfwrite)
	ON_EN_UPDATE(IDC_EDCNTINPUT, OnUpdateEdcntinput)
	ON_EN_UPDATE(IDC_EDCNTMM, OnUpdateEdcntmm)
	ON_EN_UPDATE(IDC_EDCNTSUB, OnUpdateEdcntsub)
	ON_EN_UPDATE(IDC_EDCNTSYSTEM, OnUpdateEdcntsystem)
	ON_EN_UPDATE(IDC_EDCNTTCL, OnUpdateEdcnttcl)
	ON_EN_UPDATE(IDC_EDCNTFREAD, OnUpdateEdcntfread)
	ON_EN_UPDATE(IDC_EDWAITFOTHER, OnUpdateEdcntfother)
	ON_EN_UPDATE(IDC_EDWAITFREAD, OnUpdateEdcntfread)
	ON_EN_UPDATE(IDC_EDWAITFWRITE, OnUpdateEdcntfwrite)
	ON_EN_UPDATE(IDC_EDWAITINPUT, OnUpdateEdcntinput)
	ON_EN_UPDATE(IDC_EDWAITMM, OnUpdateEdcntmm)
	ON_EN_UPDATE(IDC_EDWAITSUB, OnUpdateEdcntsub)
	ON_EN_UPDATE(IDC_EDWAITSYSTEM, OnUpdateEdcntsystem)
	ON_EN_UPDATE(IDC_EDWAITTCL, OnUpdateEdcnttcl)
	ON_BN_CLICKED(IDC_BUTOLEDEFLOAD, OnButoledefload)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOLESet message handlers

void CDlgOLESet::OnOK()
{
	CWinApp *tmp=AfxGetApp();
	tmp->WriteProfileInt( "OLESETTINGS", "WAITTCL"		,GPC.m_OLESETTINGS.m_WTCL	=m_WTCL		);
	tmp->WriteProfileInt( "OLESETTINGS", "WAITSUB"		,GPC.m_OLESETTINGS.m_WSUB	=m_WSUB		);
	tmp->WriteProfileInt( "OLESETTINGS", "WAITFREAD"	,GPC.m_OLESETTINGS.m_WFRead	=m_WFRead	);
	tmp->WriteProfileInt( "OLESETTINGS", "WAITSYSTEM"	,GPC.m_OLESETTINGS.m_WSystem=m_WSystem	);
	tmp->WriteProfileInt( "OLESETTINGS", "WAITMM"		,GPC.m_OLESETTINGS.m_WMM	=m_WMM		);
	tmp->WriteProfileInt( "OLESETTINGS", "WAITINPUT"	,GPC.m_OLESETTINGS.m_WInput	=m_WInput	);
	tmp->WriteProfileInt( "OLESETTINGS", "WAITFWRITE"	,GPC.m_OLESETTINGS.m_WFWrite=m_WFWrite	);
	tmp->WriteProfileInt( "OLESETTINGS", "WAITFOTHER"	,GPC.m_OLESETTINGS.m_WFOther=m_WFOther	);
	tmp->WriteProfileInt( "OLESETTINGS", "CNTTCL"		,GPC.m_OLESETTINGS.m_CTCL	=m_CTCL		);
	tmp->WriteProfileInt( "OLESETTINGS", "CNTSYSTEM"	,GPC.m_OLESETTINGS.m_CSystem=m_CSystem	);
	tmp->WriteProfileInt( "OLESETTINGS", "CNTSUB"		,GPC.m_OLESETTINGS.m_CSUB	=m_CSUB		);
	tmp->WriteProfileInt( "OLESETTINGS", "CNTMM"		,GPC.m_OLESETTINGS.m_CMM	=m_CMM		);
	tmp->WriteProfileInt( "OLESETTINGS", "CNTINPUT"		,GPC.m_OLESETTINGS.m_CInput	=m_CInput	);
	tmp->WriteProfileInt( "OLESETTINGS", "CNTFWRITE"	,GPC.m_OLESETTINGS.m_CFWrite=m_CFWrite	);
	tmp->WriteProfileInt( "OLESETTINGS", "CNTFREAD"		,GPC.m_OLESETTINGS.m_CFRead	=m_CFRead	);
	tmp->WriteProfileInt( "OLESETTINGS", "CNTFOTHER"	,GPC.m_OLESETTINGS.m_CFOther=m_CFOther	);

	CDialog::OnOK();
}

BOOL CDlgOLESet::OnInitDialog()
{
	CDialog::OnInitDialog();
	CWinApp *tmp=AfxGetApp();

	SetDlgItemInt( IDC_EDWAITTCL	,m_WTCL		=tmp->GetProfileInt("OLESETTINGS", "WAITTCL"	,50		));
	SetDlgItemInt( IDC_EDWAITSUB	,m_WSUB		=tmp->GetProfileInt("OLESETTINGS", "WAITSUB"	,50		));
	SetDlgItemInt( IDC_EDWAITFREAD	,m_WFRead	=tmp->GetProfileInt("OLESETTINGS", "WAITFREAD"	,50		));
	SetDlgItemInt( IDC_EDWAITSYSTEM	,m_WSystem	=tmp->GetProfileInt("OLESETTINGS", "WAITSYSTEM"	,50		));
	SetDlgItemInt( IDC_EDWAITMM		,m_WMM		=tmp->GetProfileInt("OLESETTINGS", "WAITMM"		,50		));
	SetDlgItemInt( IDC_EDWAITINPUT	,m_WInput	=tmp->GetProfileInt("OLESETTINGS", "WAITINPUT"	,60		));
	SetDlgItemInt( IDC_EDWAITFWRITE	,m_WFWrite	=tmp->GetProfileInt("OLESETTINGS", "WAITFWRITE"	,50		));
	SetDlgItemInt( IDC_EDWAITFOTHER	,m_WFOther	=tmp->GetProfileInt("OLESETTINGS", "WAITFOTHER"	,50		));
	SetDlgItemInt( IDC_EDCNTTCL		,m_CTCL		=tmp->GetProfileInt("OLESETTINGS", "CNTTCL"		,5000	));
	SetDlgItemInt( IDC_EDCNTSYSTEM	,m_CSystem	=tmp->GetProfileInt("OLESETTINGS", "CNTSYSTEM"	,1000	));
	SetDlgItemInt( IDC_EDCNTSUB		,m_CSUB		=tmp->GetProfileInt("OLESETTINGS", "CNTSUB"		,5000	));
	SetDlgItemInt( IDC_EDCNTMM		,m_CMM		=tmp->GetProfileInt("OLESETTINGS", "CNTMM"		,600	));
	SetDlgItemInt( IDC_EDCNTINPUT	,m_CInput	=tmp->GetProfileInt("OLESETTINGS", "CNTINPUT"	,5000	));
	SetDlgItemInt( IDC_EDCNTFWRITE	,m_CFWrite	=tmp->GetProfileInt("OLESETTINGS", "CNTFWRITE"	,5000	));
	SetDlgItemInt( IDC_EDCNTFREAD	,m_CFRead	=tmp->GetProfileInt("OLESETTINGS", "CNTFREAD"	,5000	));
	SetDlgItemInt( IDC_EDCNTFOTHER	,m_CFOther	=tmp->GetProfileInt("OLESETTINGS", "CNTFOTHER"	,5000	));

	m_sWFOther	.SetRange32(1, 10000);
	m_sWTCL		.SetRange32(1, 10000);
	m_sWSUB		.SetRange32(1, 10000);
	m_sWInput	.SetRange32(1, 10000);
	m_sWFRead	.SetRange32(1, 10000);
	m_sWFWrite	.SetRange32(1, 10000);
	m_sWSystem	.SetRange32(1, 10000);
	m_sWMM		.SetRange32(1, 10000);
	m_sCTCL		.SetRange32(5, 100000);
	m_sCSUB		.SetRange32(5, 100000);
	m_sCFRead	.SetRange32(5, 100000);
	m_sCFWrite	.SetRange32(5, 100000);
	m_sCFOther	.SetRange32(5, 100000);
	m_sCInput	.SetRange32(5, 100000);
	m_sCSystem	.SetRange32(5, 100000);
	m_sCMM		.SetRange32(5, 5000);

	return TRUE;
}

void CDlgOLESet::OnUpdateEdcntfother()
{
	m_CFOther	=GetDlgItemInt( IDC_EDCNTFOTHER);
	m_WFOther	=GetDlgItemInt( IDC_EDWAITFOTHER);
	SetDlgItemInt( IDC_EDCNTFOTHER2	,m_CFOther*m_WFOther);
}

void CDlgOLESet::OnUpdateEdcntfread()
{
	m_CFRead	=GetDlgItemInt( IDC_EDCNTFREAD);
	m_WFRead	=GetDlgItemInt( IDC_EDWAITFREAD);
	SetDlgItemInt( IDC_EDCNTFREAD2	,m_WFRead*m_CFRead);
}

void CDlgOLESet::OnUpdateEdcntfwrite()
{
	m_CFWrite	=GetDlgItemInt( IDC_EDCNTFWRITE);
	m_WFWrite	=GetDlgItemInt( IDC_EDWAITFWRITE);
	SetDlgItemInt( IDC_EDCNTFWRITE2	,m_CFWrite*m_WFWrite);
}

void CDlgOLESet::OnUpdateEdcntinput()
{
	m_CInput	=GetDlgItemInt( IDC_EDCNTINPUT);
	m_WInput	=GetDlgItemInt( IDC_EDWAITINPUT);
	SetDlgItemInt( IDC_EDCNTINPUT2	,m_WInput*m_CInput);
}

void CDlgOLESet::OnUpdateEdcntmm()
{
	m_CMM		=GetDlgItemInt( IDC_EDCNTMM);
	m_WMM		=GetDlgItemInt( IDC_EDWAITMM);
	SetDlgItemInt( IDC_EDCNTMM2		,m_WMM*m_CMM);
}

void CDlgOLESet::OnUpdateEdcntsub()
{
	m_CSUB		=GetDlgItemInt( IDC_EDCNTSUB);
	m_WSUB		=GetDlgItemInt( IDC_EDWAITSUB);
	SetDlgItemInt( IDC_EDCNTSUB2	,m_WSUB*m_CSUB);
}

void CDlgOLESet::OnUpdateEdcntsystem()
{
	m_CSystem	=GetDlgItemInt( IDC_EDCNTSYSTEM);
	m_WSystem	=GetDlgItemInt( IDC_EDWAITSYSTEM);
	SetDlgItemInt( IDC_EDCNTSYSTEM2	,m_WSystem*m_CSystem);
}

void CDlgOLESet::OnUpdateEdcnttcl()
{
	m_CTCL		=GetDlgItemInt( IDC_EDCNTTCL);
	m_WTCL		=GetDlgItemInt( IDC_EDWAITTCL);
	SetDlgItemInt( IDC_EDCNTTCL2	,m_WTCL*m_CTCL);
}

void CDlgOLESet::OnButoledefload()
{
	SetDlgItemInt( IDC_EDWAITTCL	,m_WTCL		=50		);
	SetDlgItemInt( IDC_EDWAITSUB	,m_WSUB		=50		);
	SetDlgItemInt( IDC_EDWAITFREAD	,m_WFRead	=50		);
	SetDlgItemInt( IDC_EDWAITSYSTEM	,m_WSystem	=50		);
	SetDlgItemInt( IDC_EDWAITMM		,m_WMM		=50		);
	SetDlgItemInt( IDC_EDWAITINPUT	,m_WInput	=60		);
	SetDlgItemInt( IDC_EDWAITFWRITE	,m_WFWrite	=50		);
	SetDlgItemInt( IDC_EDWAITFOTHER	,m_WFOther	=50		);
	SetDlgItemInt( IDC_EDCNTTCL		,m_CTCL		=3000	);
	SetDlgItemInt( IDC_EDCNTSYSTEM	,m_CSystem	=600	);
	SetDlgItemInt( IDC_EDCNTSUB		,m_CSUB		=3000	);
	SetDlgItemInt( IDC_EDCNTMM		,m_CMM		=600	);
	SetDlgItemInt( IDC_EDCNTINPUT	,m_CInput	=1000	);
	SetDlgItemInt( IDC_EDCNTFWRITE	,m_CFWrite	=8000	);
	SetDlgItemInt( IDC_EDCNTFREAD	,m_CFRead	=8000	);
	SetDlgItemInt( IDC_EDCNTFOTHER	,m_CFOther	=8000	);
}
