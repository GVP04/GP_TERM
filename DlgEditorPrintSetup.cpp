// DlgEditorPrintSetup.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgEditorPrintSetup.h"
#include "GPFontList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEditorPrintSetup dialog


CDlgEditorPrintSetup::CDlgEditorPrintSetup(CEditorPrintSettings *i_settings, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEditorPrintSetup::IDD, pParent)
{
	m_settings=i_settings;
	//{{AFX_DATA_INIT(CDlgEditorPrintSetup)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgEditorPrintSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEditorPrintSetup)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEditorPrintSetup, CDialog)
	//{{AFX_MSG_MAP(CDlgEditorPrintSetup)
	ON_BN_CLICKED(IDC_BUTTONPAGESETUP, OnButtonpagesetup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEditorPrintSetup message handlers

BOOL CDlgEditorPrintSetup::OnInitDialog() 
{
	CDialog::OnInitDialog();

	HWND tmph;

	GetDlgItem(IDC_COMBOCASE,&tmph);
	if (tmph)
	{
		::SendMessage(tmph,CB_ADDSTRING,0,(LPARAM)"MIXED");
		::SendMessage(tmph,CB_ADDSTRING,0,(LPARAM)"UPPER");
		::SendMessage(tmph,CB_ADDSTRING,0,(LPARAM)"LOWER");
	}
	GetDlgItem(IDC_COMBOCASE2,&tmph);
	if (tmph)
	{
		::SendMessage(tmph,CB_ADDSTRING,0,(LPARAM)"MIXED");
		::SendMessage(tmph,CB_ADDSTRING,0,(LPARAM)"UPPER");
		::SendMessage(tmph,CB_ADDSTRING,0,(LPARAM)"LOWER");
	}

	GetDlgItem(IDC_COMBOCOLOR,&tmph);
	if (tmph)
	{
		::SendMessage(tmph,CB_ADDSTRING,0,(LPARAM)"NORMAL");
		::SendMessage(tmph,CB_ADDSTRING,0,(LPARAM)"INVERTLIGHT");
		::SendMessage(tmph,CB_ADDSTRING,0,(LPARAM)"BLACKONWHITE");
		::SendMessage(tmph,CB_ADDSTRING,0,(LPARAM)"COLORONWHITE");
		::SendMessage(tmph,CB_ADDSTRING,0,(LPARAM)"COLORONWHITEDEFAULTBG");
	}

	{
		GetDlgItem(IDC_COMBOFONT,&tmph);
		CGPFontList fl;
		if (tmph) fl.FillComboBox(tmph,GPFL_CLEAR|GPFL_NOSCRIPT);
		GetDlgItem(IDC_COMBOFONT2,&tmph);
		if (tmph) fl.FillComboBox(tmph,GPFL_CLEAR|GPFL_NOSCRIPT);
	}

	GetDlgItem(IDC_COMBOMAGNIFICATION,&tmph);
	if (tmph)
	{
		char tmps[100];
		int i;
		for(i=-5;i<6;i++)
		{
			sprintf(tmps,"%d",i);
			::SendMessage(tmph,CB_ADDSTRING,0,(LPARAM)tmps);
		}
	}

	UpdateSelection();
	
	return TRUE;
}

void CDlgEditorPrintSetup::OnCancel() 
{
	CDialog::OnCancel();
}

void CDlgEditorPrintSetup::OnOK() 
{
	HWND tmphwnd=::GetDlgItem(m_hWnd,IDC_COMBOFONT);
	int ret;

	GetDlgItem(IDC_COMBOCASE,&tmphwnd);
	if (tmphwnd && (ret=::SendMessage(tmphwnd,CB_GETCURSEL,0,0))!=CB_ERR)
		m_settings->sdHeader.Case=ret;

	GetDlgItem(IDC_COMBOCASE2,&tmphwnd);
	if (tmphwnd && (ret=::SendMessage(tmphwnd,CB_GETCURSEL,0,0))!=CB_ERR)
		m_settings->sdFooter.Case=ret;

	GetDlgItemText(IDC_COMBOFONT, m_settings->sdHeader.fontName);
	GetDlgItemText(IDC_COMBOFONT2,m_settings->sdFooter.fontName);

	GetDlgItem(IDC_COMBOMAGNIFICATION,&tmphwnd);
	if (tmphwnd && (ret=::SendMessage(tmphwnd,CB_GETCURSEL,0,0)))
		m_settings->m_Magnification=ret-5;

	GetDlgItem(IDC_COMBOCOLOR,&tmphwnd);
	if (tmphwnd && (ret=::SendMessage(tmphwnd,CB_GETCURSEL,0,0)))
		m_settings->m_ColorType=ret;

	
	m_settings->sdHeader.bold		=::IsDlgButtonChecked(m_hWnd,IDC_CHECKBOLD);
	m_settings->sdHeader.italic		=::IsDlgButtonChecked(m_hWnd,IDC_CHECKITALIC);
	m_settings->sdHeader.underline	=::IsDlgButtonChecked(m_hWnd,IDC_CHECKUNDERLINE);
	m_settings->sdHeader.EOLFilled	=::IsDlgButtonChecked(m_hWnd,IDC_CHECKEOLFILLED);

	m_settings->sdFooter.bold		=::IsDlgButtonChecked(m_hWnd,IDC_CHECKBOLD2);
	m_settings->sdFooter.italic		=::IsDlgButtonChecked(m_hWnd,IDC_CHECKITALIC2);
	m_settings->sdFooter.underline	=::IsDlgButtonChecked(m_hWnd,IDC_CHECKUNDERLINE2);
	m_settings->sdFooter.EOLFilled	=::IsDlgButtonChecked(m_hWnd,IDC_CHECKEOLFILLED2);

	m_settings->m_UseHeader		=::IsDlgButtonChecked(m_hWnd,IDC_CHECKHEADER);
	m_settings->m_UseFooter		=::IsDlgButtonChecked(m_hWnd,IDC_CHECKFOOTER);
	m_settings->m_UseSelection	=::IsDlgButtonChecked(m_hWnd,IDC_CHECKSELECTION);
	m_settings->m_UseWordWrap	=::IsDlgButtonChecked(m_hWnd,IDC_CHECKWORDWRAP);
	m_settings->m_PrintLineNumber=::IsDlgButtonChecked(m_hWnd,IDC_CHECKLINENUM);

	m_settings->sdHeader.CharacterSet=GetDlgItemInt(IDC_EDITCHARSET);
	m_settings->sdHeader.fontSize=GetDlgItemInt(IDC_EDITFONTSIZE);
	m_settings->sdFooter.CharacterSet=GetDlgItemInt(IDC_EDITCHARSET2);
	m_settings->sdFooter.fontSize=GetDlgItemInt(IDC_EDITFONTSIZE2);


	GetDlgItemText(IDC_EDITHEADER,m_settings->csheaderFormat);
	GetDlgItemText(IDC_EDITFOOTER,m_settings->csfooterFormat);

	CDialog::OnOK();
}


void CDlgEditorPrintSetup::UpdateSelection()
{
	HWND tmphwnd=::GetDlgItem(m_hWnd,IDC_COMBOFONT);

	GetDlgItem(IDC_COMBOCASE,&tmphwnd);
	if (tmphwnd)
		::SendMessage(tmphwnd,CB_SETCURSEL,m_settings->sdHeader.Case,0);
	GetDlgItem(IDC_COMBOCASE2,&tmphwnd);
	if (tmphwnd)
		::SendMessage(tmphwnd,CB_SETCURSEL,m_settings->sdFooter.Case,0);

	GetDlgItem(IDC_COMBOFONT,&tmphwnd);
	if (tmphwnd)
	{
		int nSel=0;
		nSel=::SendMessage(tmphwnd,CB_FINDSTRINGEXACT,0,(LPARAM)((LPCSTR)(m_settings->sdHeader.fontName)));
		if (nSel==CB_ERR)	nSel=::SendMessage(tmphwnd,CB_FINDSTRING,0,(LPARAM)((LPCSTR)(m_settings->sdHeader.fontName)));
		if (nSel==CB_ERR)	nSel=::SendMessage(tmphwnd,CB_FINDSTRING,0,(LPARAM)"Courier");
		if (nSel==CB_ERR)	nSel=0;
		::SendMessage(tmphwnd,CB_SETCURSEL,(WPARAM)nSel,0);
	}
	GetDlgItem(IDC_COMBOFONT2,&tmphwnd);
	if (tmphwnd)
	{
		int nSel=0;
		nSel=::SendMessage(tmphwnd,CB_FINDSTRINGEXACT,0,(LPARAM)((LPCSTR)(m_settings->sdFooter.fontName)));
		if (nSel==CB_ERR)	nSel=::SendMessage(tmphwnd,CB_FINDSTRING,0,(LPARAM)((LPCSTR)(m_settings->sdFooter.fontName)));
		if (nSel==CB_ERR)	nSel=::SendMessage(tmphwnd,CB_FINDSTRING,0,(LPARAM)"Courier");
		if (nSel==CB_ERR)	nSel=0;
		::SendMessage(tmphwnd,CB_SETCURSEL,(WPARAM)nSel,0);
	}

	GetDlgItem(IDC_COMBOMAGNIFICATION,&tmphwnd);
	if (tmphwnd)
		::SendMessage(tmphwnd,CB_SETCURSEL,(WPARAM)m_settings->m_Magnification+5,0);

	GetDlgItem(IDC_COMBOCOLOR,&tmphwnd);
	if (tmphwnd)
		::SendMessage(tmphwnd,CB_SETCURSEL,(WPARAM)m_settings->m_ColorType,0);

	::CheckDlgButton(m_hWnd,IDC_CHECKBOLD,m_settings->sdHeader.bold);
	::CheckDlgButton(m_hWnd,IDC_CHECKITALIC,m_settings->sdHeader.italic);
	::CheckDlgButton(m_hWnd,IDC_CHECKUNDERLINE,m_settings->sdHeader.underline);
	::CheckDlgButton(m_hWnd,IDC_CHECKEOLFILLED,m_settings->sdHeader.EOLFilled);

	::CheckDlgButton(m_hWnd,IDC_CHECKBOLD2,m_settings->sdFooter.bold);
	::CheckDlgButton(m_hWnd,IDC_CHECKITALIC2,m_settings->sdFooter.italic);
	::CheckDlgButton(m_hWnd,IDC_CHECKUNDERLINE2,m_settings->sdFooter.underline);
	::CheckDlgButton(m_hWnd,IDC_CHECKEOLFILLED2,m_settings->sdFooter.EOLFilled);


	::CheckDlgButton(m_hWnd,IDC_CHECKHEADER,m_settings->m_UseHeader);
	::CheckDlgButton(m_hWnd,IDC_CHECKFOOTER,m_settings->m_UseFooter);
	::CheckDlgButton(m_hWnd,IDC_CHECKSELECTION,m_settings->m_UseSelection);
	::CheckDlgButton(m_hWnd,IDC_CHECKWORDWRAP,m_settings->m_UseWordWrap);
	::CheckDlgButton(m_hWnd,IDC_CHECKLINENUM,m_settings->m_PrintLineNumber);

	CString tmps;
	tmps.Format("%d",m_settings->sdHeader.CharacterSet);
	::SetDlgItemText(m_hWnd,IDC_EDITCHARSET,(LPCSTR)tmps);
	tmps.Format("%d",m_settings->sdHeader.fontSize);
	::SetDlgItemText(m_hWnd,IDC_EDITFONTSIZE,(LPCSTR)tmps);
	tmps.Format("%d",m_settings->sdFooter.CharacterSet);
	::SetDlgItemText(m_hWnd,IDC_EDITCHARSET2,(LPCSTR)tmps);
	tmps.Format("%d",m_settings->sdFooter.fontSize);
	::SetDlgItemText(m_hWnd,IDC_EDITFONTSIZE2,(LPCSTR)tmps);

	::SetDlgItemText(m_hWnd,IDC_EDITHEADER,(LPCSTR)m_settings->csheaderFormat);
	::SetDlgItemText(m_hWnd,IDC_EDITFOOTER,(LPCSTR)m_settings->csfooterFormat);

}

void CDlgEditorPrintSetup::OnButtonpagesetup() 
{
	m_settings->PSetupDlg();
}
