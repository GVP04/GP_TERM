// GPDlgPageSetup.cpp : implementation file
//

#include "stdafx.h"
#include "GP_term.h"
#include "GPDlgPageSetup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPDlgPageSetup dialog


GPDlgPageSetup::GPDlgPageSetup(CWnd* pParent /*=NULL*/)
	: CDialog(GPDlgPageSetup::IDD, pParent)
{
	//{{AFX_DATA_INIT(GPDlgPageSetup)
	//}}AFX_DATA_INIT
}


void GPDlgPageSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GPDlgPageSetup)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GPDlgPageSetup, CDialog)
	//{{AFX_MSG_MAP(GPDlgPageSetup)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK2, &GPDlgPageSetup::OnBnClickedOk2)
	ON_BN_CLICKED(IDC_BUTTONPSETUP, &GPDlgPageSetup::OnBnClickedButtonpsetup)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
//////////
// GPDlgPageSetup message handlers
#include "GP_TermView.h"
#include "GP_TermDoc.h"

BOOL GPDlgPageSetup::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GPScreen *s=GPC.m_Document->GetActiveScreen();

	HWND hw=::GetDlgItem(m_hWnd,IDC_COMBO1);

	
	int i;
	for(i=1;i<17;i++)
	{
		char tmpcc[]={0,0,0,};
		if (i>9) {tmpcc[0]='1';tmpcc[1]=i%10+'0';} 
		else tmpcc[0]=i+'0';
		::SendMessage(hw,CB_ADDSTRING,0,(LPARAM)tmpcc);
	}

	if (GPC.m_uPixelPerPoint<1 || GPC.m_uPixelPerPoint>16) GPC.m_uPixelPerPoint=2;

	::SendMessage(hw,CB_SETCURSEL,GPC.m_uPixelPerPoint-1,0);

	CString tmpSC;
	tmpSC.Format("%g",s->LeftPageMargin);
	SetDlgItemText(IDC_EDITLEFT,tmpSC);
	tmpSC.Format("%g",s->RightPageMargin);
	SetDlgItemText(IDC_EDITRIGHT,tmpSC);
	tmpSC.Format("%g",s->TopPageMargin);
	SetDlgItemText(IDC_EDITTOP,tmpSC);
	tmpSC.Format("%g",s->BottomPageMargin);
	SetDlgItemText(IDC_EDITBOTTOM,tmpSC);
	tmpSC.Format("%g",s->ScaleHeightToWidth);
	SetDlgItemText(IDC_EDITHW,tmpSC);

	CheckDlgButton(IDC_CHECKPRINTBORDERS,s->PrintBorders);
	CheckDlgButton(IDC_CHECKINVERT,s->PrintInvert);

	CheckDlgButton(IDC_RADIOFITTOPAGE,(s->ScaleFlags&0x7)==0);
	CheckDlgButton(IDC_RADIOASONSCREEN,(s->ScaleFlags&0x7)==1);
	CheckDlgButton(IDC_RADIOCUSTOM,(s->ScaleFlags&0x7)==2);

	return TRUE;
}

void GPDlgPageSetup::OnOK() 
{
	GPScreen *s=GPC.m_Document->GetActiveScreen();

	CString tmpSC;
	GetDlgItemText(IDC_EDITLEFT,tmpSC);
	s->LeftPageMargin=(REAL)atof(tmpSC);
	GetDlgItemText(IDC_EDITRIGHT,tmpSC);
	s->RightPageMargin=(REAL)atof(tmpSC);
	GetDlgItemText(IDC_EDITTOP,tmpSC);
	s->TopPageMargin=(REAL)atof(tmpSC);
	GetDlgItemText(IDC_EDITBOTTOM,tmpSC);
	s->BottomPageMargin=(REAL)atof(tmpSC);
	GetDlgItemText(IDC_EDITHW,tmpSC);
	s->ScaleHeightToWidth=(REAL)atof(tmpSC);
	s->PrintBorders=IsDlgButtonChecked(IDC_CHECKPRINTBORDERS);
	s->PrintInvert=IsDlgButtonChecked(IDC_CHECKINVERT);

	s->ScaleFlags=IsDlgButtonChecked(IDC_RADIOASONSCREEN)?1:IsDlgButtonChecked(IDC_RADIOCUSTOM)?2:0;

	GPC.m_uPixelPerPoint=::SendMessage(::GetDlgItem(m_hWnd,IDC_COMBO1),CB_GETCURSEL,0,0)+1;
	if (GPC.m_uPixelPerPoint<1 || GPC.m_uPixelPerPoint>16) GPC.m_uPixelPerPoint=2;

	CDialog::OnOK();
}


void GPDlgPageSetup::OnBnClickedOk2()
{
	CWinApp *app=AfxGetApp();

	CString tmpSC;
	GetDlgItemText(IDC_EDITLEFT,tmpSC);
	GPScreen::ScrLeftPageMargin=(REAL)atof(tmpSC);
	tmpSC.Format("%g",GPScreen::ScrLeftPageMargin);
	app->WriteProfileString(GPC.cs_RegTermViewSetName, "ScrLeftPageMargin",(LPCSTR)tmpSC);

	GetDlgItemText(IDC_EDITRIGHT,tmpSC);
	GPScreen::ScrRightPageMargin=(REAL)atof(tmpSC);
	tmpSC.Format("%g",GPScreen::ScrRightPageMargin);
	app->WriteProfileString(GPC.cs_RegTermViewSetName, "ScrRightPageMargin",(LPCSTR)tmpSC);

	GetDlgItemText(IDC_EDITTOP,tmpSC);
	GPScreen::ScrTopPageMargin=(REAL)atof(tmpSC);
	tmpSC.Format("%g",GPScreen::ScrTopPageMargin);
	app->WriteProfileString(GPC.cs_RegTermViewSetName, "ScrTopPageMargin",(LPCSTR)tmpSC);

	GetDlgItemText(IDC_EDITBOTTOM,tmpSC);
	GPScreen::ScrBottomPageMargin=(REAL)atof(tmpSC);
	tmpSC.Format("%g",GPScreen::ScrBottomPageMargin);
	app->WriteProfileString(GPC.cs_RegTermViewSetName, "ScrBottomPageMargin",(LPCSTR)tmpSC);

	GetDlgItemText(IDC_EDITHW,tmpSC);
	GPScreen::ScrScaleHeightToWidth=(REAL)atof(tmpSC);
	tmpSC.Format("%g",GPScreen::ScrScaleHeightToWidth);
	app->WriteProfileString(GPC.cs_RegTermViewSetName, "ScrScaleHeightToWidth",(LPCSTR)tmpSC);
	
	
	GPScreen::ScrPrintBorders=IsDlgButtonChecked(IDC_CHECKPRINTBORDERS);
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "ScrPrintBorders",GPScreen::ScrPrintBorders);

	GPScreen::ScrPrintInvert=IsDlgButtonChecked(IDC_CHECKINVERT);
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "ScrPrintInvert",GPScreen::ScrPrintInvert);

	GPScreen::ScrScaleFlags=IsDlgButtonChecked(IDC_RADIOASONSCREEN)?1:IsDlgButtonChecked(IDC_RADIOCUSTOM)?2:0;
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "ScrScaleFlags",GPScreen::ScrScaleFlags);

	GPC.m_uPixelPerPoint=::SendMessage(::GetDlgItem(m_hWnd,IDC_COMBO1),CB_GETCURSEL,0,0)+1;
	if (GPC.m_uPixelPerPoint<1 || GPC.m_uPixelPerPoint>16) GPC.m_uPixelPerPoint=2;
	AfxGetApp()->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_uPixelPerPoint",GPC.m_uPixelPerPoint);
}

void GPDlgPageSetup::OnBnClickedButtonpsetup()
{
	AfxGetMainWnd()->SendMessage(WM_COMMAND,ID_FILE_PRINT_SETUP,0);
}

