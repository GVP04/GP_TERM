// DlgErrors.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgErrors.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgErrors dialog


CDlgErrors::CDlgErrors(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgErrors::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgErrors)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgErrors::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgErrors)
	DDX_Control(pDX, IDC_BUTTON1, m_BtnClear);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	DDX_Control(pDX, IDC_LIST4, m_List4);
	DDX_Control(pDX, IDC_LIST3, m_List3);
	DDX_Control(pDX, IDC_LIST2, m_List2);
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgErrors, CDialog)
	//{{AFX_MSG_MAP(CDlgErrors)
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonClear)
	ON_BN_CLICKED(IDC_BUTTON6, OnButtonReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgErrors message handlers

BOOL CDlgErrors::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_List2.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_List3.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_List4.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	
	AUSI.AddSetMain(m_hWnd);
	AUSI.AddWnd(m_List.m_hWnd,m_hWnd	,"NNEE");
	AUSI.AddWnd(m_List2.m_hWnd,m_hWnd	,"NNEE");
	AUSI.AddWnd(m_List3.m_hWnd,m_hWnd	,"NNEE");
	AUSI.AddWnd(m_List4.m_hWnd,m_hWnd	,"NNEE");
	AUSI.AddWnd(m_BtnClear.m_hWnd,m_hWnd	,"NENE");

	HWND tmphwnd=NULL;
	GetDlgItem(IDOK,&tmphwnd);
	if (tmphwnd) AUSI.AddWnd(tmphwnd, m_hWnd, "NENE");
	GetDlgItem(IDCANCEL,&tmphwnd);
	if (tmphwnd) AUSI.AddWnd(tmphwnd, m_hWnd, "NENE");
	GetDlgItem(IDC_BUTTON6,&tmphwnd);
	if (tmphwnd) AUSI.AddWnd(tmphwnd, m_hWnd, "NENE");

	AUSI.SetMinSize(m_hWnd,520,250);

	m_List.InsertColumn(0,"1",LVCFMT_LEFT,150,0);
	m_List.InsertColumn(1,"2",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(2,"3",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(3,"4",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(4,"5",LVCFMT_LEFT,100,0);

	m_List2.InsertColumn(0,"1",LVCFMT_LEFT,150,0);
	m_List2.InsertColumn(1,"2",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(2,"3",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(3,"4",LVCFMT_LEFT,100,0);
	m_List2.InsertColumn(4,"5",LVCFMT_LEFT,100,0);

	m_List3.InsertColumn(0,"1",LVCFMT_LEFT,150,0);
	m_List3.InsertColumn(1,"2",LVCFMT_LEFT,100,0);
	m_List3.InsertColumn(2,"3",LVCFMT_LEFT,100,0);
	m_List3.InsertColumn(3,"4",LVCFMT_LEFT,100,0);
	m_List3.InsertColumn(4,"5",LVCFMT_LEFT,100,0);

	m_List4.InsertColumn(0,"1",LVCFMT_LEFT,150,0);
	m_List4.InsertColumn(1,"2",LVCFMT_LEFT,100,0);
	m_List4.InsertColumn(2,"3",LVCFMT_LEFT,100,0);
	m_List4.InsertColumn(3,"4",LVCFMT_LEFT,100,0);
	m_List4.InsertColumn(4,"5",LVCFMT_LEFT,100,0);

	char tmpsd[100];
	sprintf(tmpsd,"Errors (%d)",GPC.m_SprArray.GetSpr("m_SprErr")->GetCount());
	m_Tab.InsertItem(5,tmpsd);
	sprintf(tmpsd,"Errors DB (%d)",GPC.m_SprArray.GetSpr("m_SprErr2")->GetCount());
	m_Tab.InsertItem(5,tmpsd);
	sprintf(tmpsd,"Warnings (%d)",GPC.m_SprArray.GetSpr("m_SprWarn")->GetCount());
	m_Tab.InsertItem(5,tmpsd);
	sprintf(tmpsd,"Warnings DB (%d)",GPC.m_SprArray.GetSpr("m_SprWarn2")->GetCount());
	m_Tab.InsertItem(5,tmpsd);


	m_Tab.SetCurSel(0);
	m_List.ShowWindow(SW_SHOW);

	strcpy(tmpsd,"0c1c2c3c4,0c1c2c3c4");
	char *postmp=tmpsd;
	while(*(++postmp))
		if (*postmp=='c') *postmp=GPC.DelimiterIn1;

	GPC.m_SprArray.FillObject("m_SprErr",m_List.m_hWnd,GPSPRFILL_LISTCTRL,tmpsd,0);
	GPC.m_SprArray.FillObject("m_SprErr2",m_List2.m_hWnd,GPSPRFILL_LISTCTRL,tmpsd,0);
	GPC.m_SprArray.FillObject("m_SprWarn",m_List3.m_hWnd,GPSPRFILL_LISTCTRL,tmpsd,0);
	GPC.m_SprArray.FillObject("m_SprWarn2",m_List4.m_hWnd,GPSPRFILL_LISTCTRL,tmpsd,0);

	CheckDlgButton(IDC_CHERRORS,(GPC.m_ErrReport.dwErrorMask&EL_INDICERROR1)!=0);
	CheckDlgButton(IDC_CHERRORS2,(GPC.m_ErrReport.dwErrorMask&EL_INDICERROR2)!=0);
	CheckDlgButton(IDC_CHWARNINGS,(GPC.m_ErrReport.dwErrorMask&EL_INDICWARNING1)!=0);
	CheckDlgButton(IDC_CHWARNINGS2,(GPC.m_ErrReport.dwErrorMask&EL_INDICWARNING2)!=0);
	CheckDlgButton(IDC_CHERRORSW,(GPC.m_ErrReport.dwErrorMask&EL_WRITEERROR1)!=0);
	CheckDlgButton(IDC_CHERRORSW2,(GPC.m_ErrReport.dwErrorMask&EL_WRITEERROR2)!=0);
	CheckDlgButton(IDC_CHWARNINGSW,(GPC.m_ErrReport.dwErrorMask&EL_WRITEWARNING1)!=0);
	CheckDlgButton(IDC_CHWARNINGSW2,(GPC.m_ErrReport.dwErrorMask&EL_WRITEWARNING2)!=0);

	return TRUE; 
}

void CDlgErrors::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	AUSI.UpdateSize();
}

void CDlgErrors::OnCancel() 
{	
	CDialog::OnCancel();
}

void CDlgErrors::OnOK() 
{
	GPC.m_ErrReport.dwErrorMask&=(0xFFFFFFFF^(EL_WRITEMASK|EL_INDICMASK));

	GPC.m_ErrReport.dwErrorMask|=IsDlgButtonChecked(IDC_CHERRORS)?		EL_INDICERROR1:0;
	GPC.m_ErrReport.dwErrorMask|=IsDlgButtonChecked(IDC_CHERRORS2)?		EL_INDICERROR2:0;
	GPC.m_ErrReport.dwErrorMask|=IsDlgButtonChecked(IDC_CHWARNINGS)?	EL_INDICWARNING1:0;
	GPC.m_ErrReport.dwErrorMask|=IsDlgButtonChecked(IDC_CHWARNINGS2)?	EL_INDICWARNING2:0;
	GPC.m_ErrReport.dwErrorMask|=IsDlgButtonChecked(IDC_CHERRORSW)?		EL_WRITEERROR1:0;
	GPC.m_ErrReport.dwErrorMask|=IsDlgButtonChecked(IDC_CHERRORSW2)?	EL_WRITEERROR2:0;
	GPC.m_ErrReport.dwErrorMask|=IsDlgButtonChecked(IDC_CHWARNINGSW)?	EL_WRITEWARNING1:0;
	GPC.m_ErrReport.dwErrorMask|=IsDlgButtonChecked(IDC_CHWARNINGSW2)?	EL_WRITEWARNING2:0;

	AfxGetApp()->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_ErrReport.dwErrorMask",	GPC.m_ErrReport.dwErrorMask);

	CDialog::OnOK();
}

void CDlgErrors::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_List.ShowWindow(SW_HIDE);
	m_List2.ShowWindow(SW_HIDE);
	m_List3.ShowWindow(SW_HIDE);
	m_List4.ShowWindow(SW_HIDE);

	switch(m_Tab.GetCurSel())
	{
	case 0:
		m_List.ShowWindow(SW_SHOW);
		m_BtnClear.EnableWindow(m_List.GetItemCount());
		break;
	case 1:
		m_List2.ShowWindow(SW_SHOW);
		m_BtnClear.EnableWindow(m_List2.GetItemCount());
		break;
	case 2:
		m_List3.ShowWindow(SW_SHOW);
		m_BtnClear.EnableWindow(m_List3.GetItemCount());
		break;
	case 3:
		m_List4.ShowWindow(SW_SHOW);
		m_BtnClear.EnableWindow(m_List4.GetItemCount());
		break;
	}

	*pResult = 0;
}

void CDlgErrors::OnButtonClear() 
{
	TCITEM ti={0};
	ti.mask=TCIF_TEXT;

	switch(m_Tab.GetCurSel())
	{
	case 0:
		m_List.DeleteAllItems();
		ti.pszText="Errors (0)";
		m_Tab.SetItem(0,&ti);
		GPC.m_SprArray.DoMethod("m_SprErr","DeleteItem -1",NULL);
		break;
	case 1:
		m_List2.DeleteAllItems();
		ti.pszText="Errors DB (0)";
		m_Tab.SetItem(1,&ti);
		GPC.m_SprArray.DoMethod("m_SprErr2","DeleteItem -1",NULL);
		break;
	case 2:
		m_List3.DeleteAllItems();
		ti.pszText="Warnings (0)";
		m_Tab.SetItem(2,&ti);
		GPC.m_SprArray.DoMethod("m_SprWarn","DeleteItem -1",NULL);
		break;
	case 3:
		m_List4.DeleteAllItems();
		ti.pszText="Warnings DB (0)";
		m_Tab.SetItem(3,&ti);
		GPC.m_SprArray.DoMethod("m_SprWarn2","DeleteItem -1",NULL);
		break;
	}
	OnButtonReset();
}

void CDlgErrors::OnButtonReset() 
{
	switch(m_Tab.GetCurSel())
	{
	case 0:
		GPC.m_ErrReport.dwErrorFlag&=(0xFFFFFFFF^EL_INDICERROR1);
		break;
	case 1:
		GPC.m_ErrReport.dwErrorFlag&=(0xFFFFFFFF^EL_INDICERROR2);
		break;
	case 2:
		GPC.m_ErrReport.dwErrorFlag&=(0xFFFFFFFF^EL_INDICWARNING1);
		break;
	case 3:
		GPC.m_ErrReport.dwErrorFlag&=(0xFFFFFFFF^EL_INDICWARNING2);
		break;
	}
}
