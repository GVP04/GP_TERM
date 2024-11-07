// EditorPrintSettings.cpp: implementation of the CEditorPrintSettings class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "EditorPrintSettings.h"
#include "GPScintilla.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEditorPrintSettings::CEditorPrintSettings()
{
	m_Magnification=0;
	m_LoadFlag=0;
	LoadSettings();
}

CEditorPrintSettings::~CEditorPrintSettings()
{
}

const char * CEditorPrintSettings::GetFormatedHeaderString(int Page)
{
	return GetFormatedString(csheaderFormat,Page);
}
const char * CEditorPrintSettings::GetFormatedFooterString(int Page)
{
	return GetFormatedString(csfooterFormat,Page);
}

const char * CEditorPrintSettings::GetFormatedString(const char *iFormat, int Page)
{
	static CString tmps;
	tmps=iFormat;
	CString tmpsrep;
	tmpsrep.Format("%d",Page);
	tmps.Replace("&p",tmpsrep);
	int pos;
	CTime mtm=CTime::GetCurrentTime();

	while((pos=tmps.Find("&d(",0))>=0)
	{
		tmpsrep="";
		if (pos>0) tmpsrep=tmps.Mid(0,pos);
		int pos2=tmps.Find( ")" , pos);
		if (pos2>=0)
		{
			CString formats=tmps.Mid(pos+3,pos2-pos-3);
			tmps=tmpsrep+mtm.Format(formats)+tmps.Mid(pos2+1);
		}
	}

	tmps.Replace("&s1",ExtractField(csAdditionalString,1,"\x2"));
	tmps.Replace("&s2",ExtractField(csAdditionalString,2,"\x2"));
	tmps.Replace("&s3",ExtractField(csAdditionalString,3,"\x2"));
	tmps.Replace("&s4",ExtractField(csAdditionalString,4,"\x2"));
	tmps.Replace("&s5",ExtractField(csAdditionalString,5,"\x2"));
	tmps.Replace("&s6",ExtractField(csAdditionalString,6,"\x2"));
	tmps.Replace("&s7",ExtractField(csAdditionalString,7,"\x2"));
	tmps.Replace("&s8",ExtractField(csAdditionalString,8,"\x2"));
	tmps.Replace("&s9",ExtractField(csAdditionalString,9,"\x2"));

	return tmps;
}

#include "DlgEditorPrintSetup.h"

DWORD CEditorPrintSettings::SetupDlg()
{
	DWORD ret=0;
	CDlgEditorPrintSetup dlg(this);

	if ((ret=dlg.DoModal())==IDOK)
		SaveSettings();
	
	return ret;
}

void CEditorPrintSettings::SaveSettings(DWORD iflag)
{
	CWinApp *app=AfxGetApp();
	csheaderStyle=GPScintilla::StyleInfoToStringEx(sdHeader);
	csfooterStyle=GPScintilla::StyleInfoToStringEx(sdFooter);
	app->WriteProfileInt(		"EDITOR", "m_PrintLineNumber",m_PrintLineNumber	);
	app->WriteProfileInt(		"EDITOR", "m_Magnification",m_Magnification	);
	app->WriteProfileString(	"EDITOR", "csheaderFormat",	csheaderFormat	);
	app->WriteProfileString(	"EDITOR", "csfooterFormat",	csfooterFormat	);
	app->WriteProfileString(	"EDITOR", "csheaderStyle",	csheaderStyle	);
	app->WriteProfileString(	"EDITOR", "csfooterStyle",	csfooterStyle	);

	app->WriteProfileInt(		"EDITOR", "m_UseHeader	",	m_UseHeader		);
	app->WriteProfileInt(		"EDITOR", "m_UseFooter	",	m_UseFooter		);
	app->WriteProfileInt(		"EDITOR", "m_UseSelectio",	m_UseSelection	);
	app->WriteProfileInt(		"EDITOR", "m_UseWordWrap",	m_UseWordWrap	);
}

void CEditorPrintSettings::LoadSettings(DWORD iflag)
{
	if (m_LoadFlag==0 || iflag)
	{
		CWinApp *app=AfxGetApp();
		if (app && GPC.m_Document)
		{
			m_PrintLineNumber=app->GetProfileInt(	"EDITOR", "m_PrintLineNumber",1);
			m_Magnification	=app->GetProfileInt(	"EDITOR", "m_Magnification",0);
			csheaderFormat	=app->GetProfileString(	"EDITOR", "csheaderFormat",	"");
			csfooterFormat	=app->GetProfileString(	"EDITOR", "csfooterFormat",	"");
			csheaderStyle	=app->GetProfileString(	"EDITOR", "csheaderStyle",	"");
			csfooterStyle	=app->GetProfileString(	"EDITOR", "csfooterStyle",	"");
			GPScintilla::StringToStyleInfo(csheaderStyle,  sdHeader);
			GPScintilla::StringToStyleInfo(csfooterStyle,  sdFooter);

			m_UseHeader		=app->GetProfileInt(	"EDITOR", "m_UseHeader",0);
			m_UseFooter		=app->GetProfileInt(	"EDITOR", "m_UseFooter",0);
			m_UseSelection	=app->GetProfileInt(	"EDITOR", "m_UseSelection",0);
			m_UseWordWrap	=app->GetProfileInt(	"EDITOR", "m_UseWordWrap",1);
			m_LoadFlag=1;
		}
	}
}


void CEditorPrintSettings::SetHeaderStyle(const char *iStyle)
{
	csheaderStyle=iStyle;
	GPScintilla::StringToStyleInfo(csheaderStyle, sdHeader);
}

void CEditorPrintSettings::SetFooterStyle(const char *iStyle)
{
	csfooterStyle=iStyle;
	GPScintilla::StringToStyleInfo(csfooterStyle,  sdFooter);
}

const char * CEditorPrintSettings::GetHeaderStyle()
{
	return csheaderStyle;
}

const char * CEditorPrintSettings::GetFooterStyle()
{
	return csfooterStyle;
}

DWORD CEditorPrintSettings::PSetupDlg() 
{
	DWORD ret=0;
	PAGESETUPDLG pdlg = {0};
	pdlg.lStructSize=sizeof(PAGESETUPDLG);

	pdlg.hwndOwner = GPC.m_hViewWnd;
	pdlg.hInstance = AfxGetInstanceHandle();

	if (pagesetupMargin.left != 0 || pagesetupMargin.right != 0 ||
	        pagesetupMargin.top != 0 || pagesetupMargin.bottom != 0) {
		pdlg.Flags = PSD_MARGINS;

		pdlg.rtMargin.left = pagesetupMargin.left;
		pdlg.rtMargin.top = pagesetupMargin.top;
		pdlg.rtMargin.right = pagesetupMargin.right;
		pdlg.rtMargin.bottom = pagesetupMargin.bottom;
	}

	if ((ret=PageSetupDlg(&pdlg)))
	{
		pagesetupMargin.left = pdlg.rtMargin.left;
		pagesetupMargin.top = pdlg.rtMargin.top;
		pagesetupMargin.right = pdlg.rtMargin.right;
		pagesetupMargin.bottom = pdlg.rtMargin.bottom;
	}
	return ret;
}



