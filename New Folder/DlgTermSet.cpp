// DlgTermSet.cpp : implementation file
//

#include "stdafx.h"
#include "GP_term.h"
#include "DlgTermSet.h"
#include "GPFontList.h"
#include "GP_TermDoc.h"
#include "GP_TermView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTermSet dialog


CDlgTermSet::CDlgTermSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTermSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTermSet)
	//}}AFX_DATA_INIT
	m_curOutScrBkg=GPC.m_curOutScrBkg;
}

void CDlgTermSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTermSet)
	DDX_Control(pDX, IDC_COMBODEFBKGCOLOR2, m_OutScrBkgColorCombo);
	DDX_Control(pDX, IDC_COMBODEFCHRCOLOR, m_DefFrgClr);
	DDX_Control(pDX, IDC_COMBODEFBKGCOLOR, m_DefBkgClr);
	DDX_Control(pDX, IDC_COMBOSIZINGMODE, m_SizingModeCombo);
	DDX_Control(pDX, IDC_CHECKEXIT, m_CheckExit);
	DDX_Control(pDX, IDC_CHECKEXIT3, m_CheckExitPrg);
	DDX_Control(pDX, IDC_CHECKKEYBUF, m_CheckKeybBuff);
	DDX_Control(pDX, IDC_CHECKBEEP, m_CheckBeep);
	DDX_Control(pDX, IDC_CHECKPRINT, m_CheckPrint);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTermSet, CDialog)
	//{{AFX_MSG_MAP(CDlgTermSet)
	ON_BN_CLICKED(IDC_BUTTONCOLORS, OnButtoncolors)
	ON_BN_CLICKED(IDC_BUTTONCOLORS3, OnButtoncolorsOutScrBkg)
	ON_BN_CLICKED(IDC_BUTTONERRORS, OnButtonerrors)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTermSet message handlers


BOOL CDlgTermSet::OnInitDialog()
{
	CDialog::OnInitDialog();
	CWinApp *app=AfxGetApp();

	int nColors=m_DefBkgClr.GetCount();
	CString cstmps;
	int i;
	for(i=0;i<nColors;i++)
	{
		m_DefBkgClr.GetLBText(i,cstmps);
		m_OutScrBkgColorCombo.AddString(cstmps);
	}
	m_OutScrBkgColorCombo.AddString("DIALOG");
	m_OutScrBkgColorCombo.AddString("MENU");
	cstmps.Format("COLOR %d,%d,%d",GetRValue(m_curOutScrBkg),GetGValue(m_curOutScrBkg),GetBValue(m_curOutScrBkg));
	m_OutScrBkgColorCombo.AddString("COLOR");

	m_OutScrBkgColorCombo.SetCurSel((m_curOutScrBkg>=0 && m_curOutScrBkg<=9)?m_curOutScrBkg:10);

	SetDlgItemText(IDC_EDITTITLE,app->GetProfileString(GPC.cs_RegTermViewSetName, "TERMTITLE",(LPCSTR)GPC.termCaptionInit));

	m_CheckPrint.SetCheck	(app->GetProfileInt(GPC.cs_RegTermViewSetName, "m_PrintDlg",1));
	m_DefFrgClr.SetCurSel	(app->GetProfileInt(GPC.cs_RegTermViewSetName, "m_DefFrgClr",7));
	m_DefBkgClr.SetCurSel	(app->GetProfileInt(GPC.cs_RegTermViewSetName, "m_DefBkgClr",0));

	m_CheckExitPrg.SetCheck	(app->GetProfileInt(GPC.cs_RegTermViewSetName, "m_CheckExitPrg",1));
	m_CheckExit.SetCheck	(app->GetProfileInt(GPC.cs_RegTermViewSetName, "m_CheckExit",1));
	m_CheckBeep.SetCheck	(app->GetProfileInt(GPC.cs_RegTermViewSetName, "m_CheckBeep",1));

	CheckDlgButton(IDC_RESTORESIZE,app->GetProfileInt(GPC.cs_RegTermViewSetName, "IDC_RESTORESIZE",0));
#ifdef BRIZ
	CheckDlgButton(IDC_MULTISESSIONENABLE,app->GetProfileInt(GPC.cs_RegTermViewSetName, "STERMENABLE",0));
#else
	CheckDlgButton(IDC_MULTISESSIONENABLE,app->GetProfileInt(GPC.cs_RegTermViewSetName, "STERMENABLE",1));
#endif
	CheckDlgButton(IDC_MULTISESSIONWARNING,app->GetProfileInt(GPC.cs_RegTermViewSetName, "STERMWARNING",1));
	CheckDlgButton(IDC_CHECKSLAVEPRINT,GPC.EnableSlavePrint=app->GetProfileInt(GPC.cs_RegTermViewSetName, "SLAVEPRINT",0));
	CheckDlgButton(IDC_CHECKSLAVEPRINTCHARVIEW,GPC.EnableSlavePrintCHARVIEW=app->GetProfileInt(GPC.cs_RegTermViewSetName, "SLAVEPRINTCHARVIEW",1));
	CheckDlgButton(IDC_CHECKSLAVEPRINTASTEXT,app->GetProfileInt(GPC.cs_RegTermViewSetName, "PRINTASTXT",0));


	m_CheckKeybBuff.SetCheck(app->GetProfileInt(GPC.cs_RegTermViewSetName, "m_CheckKeybBuff",1));
	SetDlgItemInt(IDC_EDITDELAY,app->GetProfileInt(GPC.cs_RegTermViewSetName, "KeybLockDelay",150));
	SetDlgItemInt(IDC_EDITDELAY2,app->GetProfileInt(GPC.cs_RegTermViewSetName, "MaxIdle",0));
	SetDlgItemInt(IDC_EDITDELAYCURSOR,app->GetProfileInt(GPC.cs_RegTermViewSetName, "CursorDelay",200));
	SetDlgItemInt(IDC_EDITBREAKCHAR,app->GetProfileInt(GPC.cs_RegTermViewSetName, "BreakChar",127));

	SetDlgItemText(IDC_EDITTITLE,app->GetProfileString(GPC.cs_RegTermViewSetName, "TERMTITLE",(LPCSTR)GPC.termCaptionInit));
	SetDlgItemText(IDC_EDITTITLE2,app->GetProfileString(GPC.cs_RegTermViewSetName, "MSGBOXTITLE",(LPCSTR)GPC.MsgBoxCaptionInit));
	SetDlgItemText(IDC_EDITTITLE3,app->GetProfileString(GPC.cs_RegTermViewSetName, "ERRBOXTITLE",(LPCSTR)GPC.ErrBoxCaptionInit));

	CheckDlgButton(IDC_SHOWSPLASH,app->GetProfileInt(GPC.cs_RegTermViewSetName, "ShowSplash",1));

	cstmps.Format("%g",GPScreen::ScrLeftBorder);
	SetDlgItemText(IDC_EDITBORDERL,(LPCSTR)cstmps);
	cstmps.Format("%g",GPScreen::ScrRightBorder);
	SetDlgItemText(IDC_EDITBORDERR,(LPCSTR)cstmps);
	cstmps.Format("%g",GPScreen::ScrTopBorder);
	SetDlgItemText(IDC_EDITBORDERT,(LPCSTR)cstmps);
	cstmps.Format("%g",GPScreen::ScrBottomBorder);
	SetDlgItemText(IDC_EDITBORDERB,(LPCSTR)cstmps);

	const char *ccSZNames[]={
		"Left(L) only",	"Right(R) only",	"LR only",
		"Top(T) only",	"Bottom(B) only",	"TB only",
		"LT only",		"LB only",			"LTB only",
		"RT only",		"RB only",			"RTB only",
		"LRT only",		"LRB only",			"All",
		"Safe",	"","",
		};
	DWORD eV[]={
		GPScreen::SSM_LEFT,		GPScreen::SSM_RIGHT,		GPScreen::SSM_SIZE_X,
		GPScreen::SSM_TOP,		GPScreen::SSM_BOTTOM,		GPScreen::SSM_SIZE_Y,

		GPScreen::SSM_TOP|GPScreen::SSM_LEFT,	GPScreen::SSM_BOTTOM|GPScreen::SSM_LEFT,	GPScreen::SSM_SIZE_Y|GPScreen::SSM_LEFT,
		GPScreen::SSM_TOP|GPScreen::SSM_RIGHT,	GPScreen::SSM_BOTTOM|GPScreen::SSM_RIGHT,	GPScreen::SSM_SIZE_Y|GPScreen::SSM_RIGHT,
		GPScreen::SSM_TOP|GPScreen::SSM_SIZE_X,	GPScreen::SSM_BOTTOM|GPScreen::SSM_SIZE_X,	GPScreen::SSM_SIZE_XY,
		GPScreen::SSM_SAFE,
		};

	for(i=0;*ccSZNames[i];i++)
	{
		int nItem=m_SizingModeCombo.AddString(ccSZNames[i]);
		m_SizingModeCombo.SetItemData(nItem,(DWORD)eV[i]);
		if (eV[i]==GPScreen::ScrSizeScaleFlags) m_SizingModeCombo.SetCurSel(nItem);
	}

	return TRUE;
}

void CDlgTermSet::OnOK()
{
	CGP_TermView *tmp=(CGP_TermView *)GPC.m_View;
	CWinApp *app=AfxGetApp();
	GPScreen *s=GPC.m_Document->GetMainScreen();

	int nItem=m_SizingModeCombo.GetCurSel();
	s->SizeScaleFlags=GPScreen::ScrSizeScaleFlags=m_SizingModeCombo.GetItemData(nItem);
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "ScrSizeScaleFlags",GPScreen::ScrSizeScaleFlags);

	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_PrintDlg",m_CheckPrint.GetCheck());

	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_DefFrgClr",GPC.DefFrgColorInd=m_DefFrgClr.GetCurSel());
	s->SetChrColorIndex(GPC.DefFrgColorInd,0);
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_DefBkgClr",GPC.DefBkgColorInd=m_DefBkgClr.GetCurSel());
	s->SetBkgColorIndex(GPC.DefBkgColorInd,0);

	GPC.DefFrgColor=cFEtalon[GPC.DefFrgColorInd];
	GPC.DefBkgColor=cBEtalon[GPC.DefBkgColorInd];

	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_CheckExitPrg",m_CheckExitPrg.GetCheck());
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_CheckExit",m_CheckExit.GetCheck());
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_CheckBeep",tmp->BeepFlag=m_CheckBeep.GetCheck()!=0);
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_CheckKeybBuff",tmp->FlagBufferKeb=m_CheckKeybBuff.GetCheck()!=0);
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "KeybLockDelay",tmp->KeybLockDelay=GetDlgItemInt(IDC_EDITDELAY));
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "MaxIdle",tmp->m_MaxIdle=GetDlgItemInt(IDC_EDITDELAY2));
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "CursorDelay",tmp->CursorTimerDelay=GetDlgItemInt(IDC_EDITDELAYCURSOR));
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "BreakChar",GPC.BreakChar=(char)GetDlgItemInt(IDC_EDITBREAKCHAR));

	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "PRINTASTXT",IsDlgButtonChecked(IDC_CHECKSLAVEPRINTASTEXT));

	CString cstmps;
	char tmpcs[100];
	GetDlgItemText(IDC_EDITBORDERL,tmpcs,90); 
	GPScreen::ScrLeftBorder=(REAL)atof(tmpcs);
	cstmps.Format("%.5g",GPScreen::ScrLeftBorder);
	app->WriteProfileString(GPC.cs_RegTermViewSetName, "ScrLeftBorder",(LPCSTR)cstmps);

	GetDlgItemText(IDC_EDITBORDERR,tmpcs,90);
	GPScreen::ScrRightBorder=(REAL)atof(tmpcs);
	cstmps.Format("%.5g",GPScreen::ScrRightBorder);
	app->WriteProfileString(GPC.cs_RegTermViewSetName, "ScrRightBorder",(LPCSTR)cstmps);

	GetDlgItemText(IDC_EDITBORDERT,tmpcs,90);
	GPScreen::ScrTopBorder=(REAL)atof(tmpcs);
	cstmps.Format("%.5g",GPScreen::ScrTopBorder);
	app->WriteProfileString(GPC.cs_RegTermViewSetName, "ScrTopBorder",(LPCSTR)cstmps);

	GetDlgItemText(IDC_EDITBORDERB,tmpcs,90);
	GPScreen::ScrBottomBorder=(REAL)atof(tmpcs);
	cstmps.Format("%.5g",GPScreen::ScrBottomBorder);
	app->WriteProfileString(GPC.cs_RegTermViewSetName, "ScrBottomBorder",(LPCSTR)cstmps);


	int colrsel=m_OutScrBkgColorCombo.GetCurSel();
	if (colrsel==10) GPC.m_curOutScrBkg=m_curOutScrBkg;
	else GPC.m_curOutScrBkg=colrsel;

	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_curOutScrBkg",  GPC.m_curOutScrBkg);

	GetDlgItemText(IDC_EDITTITLE,GPC.termCaptionInit);
	app->WriteProfileString(GPC.cs_RegTermViewSetName, "TERMTITLE",(LPCSTR)GPC.termCaptionInit);

	GetDlgItemText(IDC_EDITTITLE2,GPC.MsgBoxCaptionInit);
	app->WriteProfileString(GPC.cs_RegTermViewSetName, "MSGBOXTITLE",(LPCSTR)GPC.MsgBoxCaptionInit);

	GetDlgItemText(IDC_EDITTITLE3,GPC.ErrBoxCaptionInit);
	app->WriteProfileString(GPC.cs_RegTermViewSetName, "ERRBOXTITLE",(LPCSTR)GPC.ErrBoxCaptionInit);

	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "IDC_RESTORESIZE",	IsDlgButtonChecked(IDC_RESTORESIZE)?1:0);
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "STERMENABLE",	IsDlgButtonChecked(IDC_MULTISESSIONENABLE)?1:0);
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "STERMWARNING",	IsDlgButtonChecked(IDC_MULTISESSIONWARNING)?1:0);

	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "ShowSplash",	IsDlgButtonChecked(IDC_SHOWSPLASH)?1:0);
	
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "SLAVEPRINT",	GPC.EnableSlavePrint=IsDlgButtonChecked(IDC_CHECKSLAVEPRINT)?1:0);
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "SLAVEPRINTCHARVIEW",	GPC.EnableSlavePrintCHARVIEW=IsDlgButtonChecked(IDC_CHECKSLAVEPRINTCHARVIEW)?1:0);
	::PostMessage(GPC.m_hViewWnd,GPM_MFUPDATESIZE,0,0);

	CDialog::OnOK();
}

#include "GPColorDlg.h"

void CDlgTermSet::OnButtoncolors()
{
	CGPDlgColor127 dlg;
	if (dlg.DoModal()==IDOK) ReadColor127();
}

void CDlgTermSet::OnCancel()
{
	CDialog::OnCancel();
}

void CDlgTermSet::OnButtoncolorsOutScrBkg() 
{
	if (m_OutScrBkgColorCombo.GetCurSel()==10)
	{
		CColorDialog dlg (m_curOutScrBkg<=9?cBEtalon[m_curOutScrBkg]:m_curOutScrBkg,CC_FULLOPEN|CC_ANYCOLOR, this);
		if (dlg.DoModal()==IDOK)
		{
			m_curOutScrBkg=dlg.GetColor();

			CString cstmps;
			cstmps.Format("COLOR %d,%d,%d",GetRValue(m_curOutScrBkg),GetGValue(m_curOutScrBkg),GetBValue(m_curOutScrBkg));

			m_OutScrBkgColorCombo.DeleteString(10);
			m_OutScrBkgColorCombo.AddString(cstmps);
			m_OutScrBkgColorCombo.SetCurSel(10);
		}
	}
}

void CDlgTermSet::OnButtonerrors() 
{
	
}
