// DlgFontSet.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgFontSet.h"
#include "GPFontList.h"
#include "GP_TermDoc.h"
#include "GP_TermView.h"
#include "DlgCodeco.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFontSet dialog


CDlgFontSet::CDlgFontSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFontSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFontSet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bLockUpdate=TRUE;
	families=NULL;
	m_CompositingQuality=GPC.m_CompositingQuality;
	m_InterpolationMode=GPC.m_InterpolationMode;
	m_PixelOffsetMode=GPC.m_PixelOffsetMode;
	m_SmoothingMode=GPC.m_SmoothingMode;
	m_TextContrast=GPC.m_TextContrast;
	m_TextRenderingHint=GPC.m_TextRenderingHint;
	m_Language=GPC.m_Language;
	m_SubLanguage=GPC.m_SubLanguage;
	m_CurCodePage=GPC.m_CurCodePage;

	m_FontDX=GPScreen::ScrFontDeltaX;
	m_FontDY=GPScreen::ScrFontDeltaY;
	m_FontOX=GPScreen::ScrFontOfsetX;
	m_FontOY=GPScreen::ScrFontOfsetY;

}
CDlgFontSet::~CDlgFontSet()
{
	if (families) delete [] ((BYTE*)families);
	families=NULL;
}

void CDlgFontSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFontSet)
	DDX_Control(pDX, IDC_COMBOFONT, m_FontCombo);
	DDX_Control(pDX, IDC_COMBOLANGUAGE, m_ComboLanguage);
	DDX_Control(pDX, IDC_COMBOSUBLANGUAGE, m_ComboSubLanguage);
	DDX_Control(pDX, IDC_COMBOCP, m_ComboCP);
	DDX_Control(pDX, IDC_COMBOCOMPOSITINGQUALITY, m_ComboCompositingQuality);
	DDX_Control(pDX, IDC_COMBOINTERPOLATIONMODE, m_ComboInterpolationMode);
	DDX_Control(pDX, IDC_COMBOPIXELOFFSETMODE, m_ComboPixelOffsetMode);
	DDX_Control(pDX, IDC_COMBOSMOOTHINGMODE, m_ComboSmoothingMode);
	DDX_Control(pDX, IDC_COMBOTEXTCONTRAST, m_ComboTextContrast);
	DDX_Control(pDX, IDC_COMBOTEXTRENDERINGHINT, m_ComboTextRenderingHint);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgFontSet, CDialog)
	//{{AFX_MSG_MAP(CDlgFontSet)
	ON_BN_CLICKED(IDC_BUTTON5, OnButtonCodeco)
	ON_BN_CLICKED(IDC_BUTTONCOLORS2, OnButtonTestScreen)
	ON_CBN_SELCHANGE(IDC_COMBOFONT, OnSelchangeCombofont)
	ON_CBN_SELCHANGE(IDC_COMBOLANGUAGE, OnSelchangeCombofont)
	ON_CBN_SELCHANGE(IDC_COMBOSUBLANGUAGE, OnSelchangeCombofont)
	ON_CBN_SELCHANGE(IDC_COMBOCP, OnSelchangeCombofont)
	ON_CBN_SELCHANGE(IDC_COMBOCOMPOSITINGQUALITY, OnSelchangeCombofont)
	ON_CBN_SELCHANGE(IDC_COMBOINTERPOLATIONMODE, OnSelchangeCombofont)
	ON_CBN_SELCHANGE(IDC_COMBOPIXELOFFSETMODE, OnSelchangeCombofont)
	ON_CBN_SELCHANGE(IDC_COMBOSMOOTHINGMODE, OnSelchangeCombofont)
	ON_CBN_SELCHANGE(IDC_COMBOTEXTCONTRAST, OnSelchangeCombofont)
	ON_CBN_SELCHANGE(IDC_COMBOTEXTRENDERINGHINT, OnSelchangeCombofont)
	ON_BN_CLICKED(IDC_BUTTONGRAPH, OnButtongraph)
	ON_EN_CHANGE(IDC_EDITFONTOX, &CDlgFontSet::OnEnChangeEditfont)
	ON_EN_CHANGE(IDC_EDITFONTOY, &CDlgFontSet::OnEnChangeEditfont)
	ON_EN_CHANGE(IDC_EDITFONTDX, &CDlgFontSet::OnEnChangeEditfont)
	ON_EN_CHANGE(IDC_EDITFONTDY, &CDlgFontSet::OnEnChangeEditfont)
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFontSet message handlers

BOOL CDlgFontSet::OnInitDialog() 
{
	INT i;
	CDialog::OnInitDialog();
	CWinApp *app=AfxGetApp();
	m_CurFontName=app->GetProfileString(GPC.cs_RegTermViewSetName, "m_FontName","Courier new");
	m_FontCombo.ResetContent();
	InstalledFontCollection ifc;
	INT nFamilies=ifc.GetFamilyCount();
	families= (FontFamily *) new BYTE [nFamilies*sizeof(FontFamily)+1000];
	INT nFound=0;
	ifc.GetFamilies(nFamilies,families,&nFound);
	int curSel=0;
	for(i=0;i<nFound;i++)
	{
		WCHAR familyName[LF_FACESIZE];
		families[i].GetFamilyName(familyName);
		CString tmpCS(familyName);
		int curitem=::SendMessageW(m_FontCombo.m_hWnd,CB_ADDSTRING,0,(LPARAM)familyName);
		if (curitem!=LB_ERR)
		{
			if (_stricmp(tmpCS,m_CurFontName)==0) curSel=i;
			m_FontCombo.SetItemData(curitem,i);
		}
	}
	if (curSel>=0) m_FontCombo.SetCurSel(curSel);

	for(i=0;i<(int)GPC.dwnCP;i++)
	{
		CPINFOEXW cpiex={0};
		if (::GetCPInfoExW(GPC.dwCodePages[i],0,&cpiex))
		{
			int curitem=::SendMessageW(m_ComboCP.m_hWnd,CB_ADDSTRING,0,(LPARAM)cpiex.CodePageName);
			m_ComboCP.SetItemData(curitem,cpiex.CodePage);
			if (cpiex.CodePage==m_CurCodePage)
				m_ComboCP.SetCurSel(curitem);
		}
	}

	CheckDlgButton(IDC_CHECKWIDEON2POS,GPC.m_WideOn2Pos);

	CheckDlgButton(IDC_USEMBCONV,GPC.m_USEMBCONV);
	CheckDlgButton(IDC_USEMBCONV2,GPC.m_USEMBCONV2);
	CheckDlgButton(IDC_USEMBCONV3,GPC.m_USEMBCONV3);

	m_CurInvert=GPC.m_CurMBInvert;
	if (m_CurInvert==-1)
	{
		char tmpss[]={198,81,165,208,0,};
		unsigned short tmpShort[5];

		m_CurInvert= (MultiByteToWideChar(
		  950, // code page
		  MB_PRECOMPOSED,         // character-type options
		  tmpss, // string to map
		  4,       // number of bytes in string
		  (LPWSTR)tmpShort,  // wide-character buffer
		  4       // size of buffer
		  ))?1:0;
	}

	CheckDlgButton(IDC_CHECKINVERT,m_CurInvert);

	const char *ccCompositingQuality[]={
		"Default","High Speed","High Quality","Gamma Corrected","Assume Linear",
		"",
	};
	const CompositingQuality aCompositingQuality[]={
		CompositingQualityDefault,CompositingQualityHighSpeed,CompositingQualityHighQuality,CompositingQualityGammaCorrected,CompositingQualityAssumeLinear,
		CompositingQualityDefault,
	};

	for(i=0;*ccCompositingQuality[i];i++)
	{
		int newitem=m_ComboCompositingQuality.AddString(ccCompositingQuality[i]);
		if (newitem!=CB_ERR) 
		{
			m_ComboCompositingQuality.SetItemData(newitem,aCompositingQuality[i]);
			if (aCompositingQuality[i]==m_CompositingQuality) m_ComboCompositingQuality.SetCurSel(newitem);
		}
	}
        
	const char *ccInterpolationMode[]={
		"Default","Low Quality","High Quality","Bilinear","Bicubic",
		"Nearest Neighbor","High Quality Bilinear","High Quality Bicubic","",
	};
	const InterpolationMode aInterpolationMode[]={
		InterpolationModeDefault,InterpolationModeLowQuality,InterpolationModeHighQuality,InterpolationModeBilinear,InterpolationModeBicubic,
		InterpolationModeNearestNeighbor,InterpolationModeHighQualityBilinear,InterpolationModeHighQualityBicubic,InterpolationModeDefault,
	};
	for(i=0;*ccInterpolationMode[i];i++)
	{
		int newitem=m_ComboInterpolationMode.AddString(ccInterpolationMode[i]);
		if (newitem!=CB_ERR) 
		{
			m_ComboInterpolationMode.SetItemData(newitem,aInterpolationMode[i]);
			if (aInterpolationMode[i]==m_InterpolationMode) m_ComboInterpolationMode.SetCurSel(newitem);
		}
	}

	const char *ccPixelOffsetMode[]={
		"Default","High Speed","High Quality","None","Half",
		"",
	};
	const PixelOffsetMode aPixelOffsetMode[]={
		PixelOffsetModeDefault,PixelOffsetModeHighSpeed,PixelOffsetModeHighQuality,PixelOffsetModeNone,PixelOffsetModeHalf,
		PixelOffsetModeDefault,
	};

	for(i=0;*ccPixelOffsetMode[i];i++)
	{
		int newitem=m_ComboPixelOffsetMode.AddString(ccPixelOffsetMode[i]);
		if (newitem!=CB_ERR) 
		{
			m_ComboPixelOffsetMode.SetItemData(newitem,aPixelOffsetMode[i]);
			if (aPixelOffsetMode[i]==m_PixelOffsetMode) m_ComboPixelOffsetMode.SetCurSel(newitem);
		}
	}

	const char *ccSmoothingMode[]={
		"Default","High Speed","High Quality","None","AntiAlias",
		"AntiAlias8x4","AntiAlias8x8","",
	};
	const SmoothingMode aSmoothingMode[]={
		SmoothingModeDefault,SmoothingModeHighSpeed,SmoothingModeHighQuality,SmoothingModeNone,SmoothingModeAntiAlias,
		SmoothingModeAntiAlias8x4,SmoothingModeAntiAlias8x8,SmoothingModeDefault,
	};

	for(i=0;*ccSmoothingMode[i];i++)
	{
		int newitem=m_ComboSmoothingMode.AddString(ccSmoothingMode[i]);
		if (newitem!=CB_ERR) 
		{
			m_ComboSmoothingMode.SetItemData(newitem,aSmoothingMode[i]);
			if (aSmoothingMode[i]==m_SmoothingMode) m_ComboSmoothingMode.SetCurSel(newitem);
		}
	}

 
	const char *ccTextContrast[]={
		"0","1","2","3","4",
		"5","6","7","8","9",
		"10","11","12",
		"",
	};
	const DWORD aTextContrast[]={
		0,1,2,3,4,
		5,6,7,8,9,
		10,11,12,
		0,
	};

	for(i=0;*ccTextContrast[i];i++)
	{
		int newitem=m_ComboTextContrast.AddString(ccTextContrast[i]);
		if (newitem!=CB_ERR) 
		{
			m_ComboTextContrast.SetItemData(newitem,aTextContrast[i]);
			if (aTextContrast[i]==m_TextContrast) m_ComboTextContrast.SetCurSel(newitem);
		}
	}



	const char *ccTextRenderingHint[]={
		"System Default","Single Bit Per Pixel Grid Fit","Single Bit Per Pixel","AntiAlias Grid Fit","AntiAlias",
		"ClearType Grid Fit","",
	};
	const TextRenderingHint aTextRenderingHint[]={
		TextRenderingHintSystemDefault,TextRenderingHintSingleBitPerPixelGridFit,TextRenderingHintSingleBitPerPixel,TextRenderingHintAntiAliasGridFit,TextRenderingHintAntiAlias,
		TextRenderingHintClearTypeGridFit,TextRenderingHintSystemDefault,
	};

	for(i=0;*ccTextRenderingHint[i];i++)
	{
		int newitem=m_ComboTextRenderingHint.AddString(ccTextRenderingHint[i]);
		if (newitem!=CB_ERR) 
		{
			m_ComboTextRenderingHint.SetItemData(newitem,aTextRenderingHint[i]);
			if (aTextRenderingHint[i]==m_TextRenderingHint) m_ComboTextRenderingHint.SetCurSel(newitem);
		}
	}
  
	for(i=0;*CDlgCodeco::cArrLangName[i];i++)
	{
		int tmpint=m_ComboLanguage.AddString( CDlgCodeco::cArrLangName[i]);
		m_ComboLanguage.SetItemData(tmpint,CDlgCodeco::wArrLang[i]);
		if (CDlgCodeco::wArrLang[i]==m_Language)
			m_ComboLanguage.SetCurSel(tmpint);
	}

	for(i=0;*CDlgCodeco::cArrSubLangName[i];i++)
	{
		int tmpint=m_ComboSubLanguage.AddString( CDlgCodeco::cArrSubLangName[i]);
		m_ComboSubLanguage.SetItemData(tmpint,CDlgCodeco::wArrSubLang[i]);
		if (CDlgCodeco::wArrSubLang[i]==m_SubLanguage)
			m_ComboSubLanguage.SetCurSel(tmpint);
	}

	GPScreen *scr=GPC.m_Document->GetMainScreen();

	scr->SaveScr(GPMAX_NSAVEDREGION-2);
	SetDlgItemText(IDC_EDITLOCALE,app->GetProfileString(GPC.cs_RegTermViewSetName, "LOCALESTR",(LPCSTR)GPC.csLocaleStr));

	CString tmpCS;
	tmpCS.Format("%g",m_FontDX);
	SetDlgItemText(IDC_EDITFONTDX,tmpCS);
	tmpCS.Format("%g",m_FontDY);
	SetDlgItemText(IDC_EDITFONTDY,tmpCS);
	tmpCS.Format("%g",m_FontOX);
	SetDlgItemText(IDC_EDITFONTOX,tmpCS);
	tmpCS.Format("%g",m_FontOY);
	SetDlgItemText(IDC_EDITFONTOY,tmpCS);

	m_bLockUpdate=FALSE;
	return TRUE;
}

void CDlgFontSet::OnOK() 
{
	CGP_TermView *tmp=(CGP_TermView *)GPC.m_View;
	CWinApp *app=AfxGetApp();

	app->WriteProfileString(GPC.cs_RegTermViewSetName, "m_FontName",m_CurFontName);

	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_CurCodePage",GPC.m_CurCodePage=m_CurCodePage);
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "MBINVERT",GPC.m_CurMBInvert=IsDlgButtonChecked(IDC_CHECKINVERT)?1:0);
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_WideOn2Pos",GPC.m_WideOn2Pos=IsDlgButtonChecked(IDC_CHECKWIDEON2POS)?1:0);

	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV",GPC.m_USEMBCONV=IsDlgButtonChecked(IDC_USEMBCONV)?1:0);
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV2",GPC.m_USEMBCONV2=IsDlgButtonChecked(IDC_USEMBCONV2)?1:0);
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV3",GPC.m_USEMBCONV3=IsDlgButtonChecked(IDC_USEMBCONV3)?1:0);

	GetDlgItemText(IDC_EDITLOCALE,GPC.csLocaleStr);
	app->WriteProfileString(GPC.cs_RegTermViewSetName, "LOCALESTR",(LPCSTR)GPC.csLocaleStr);
	setlocale( LC_ALL, GPC.csLocaleStr );
	setlocale( LC_NUMERIC, "English_USA.1252");

	GPC.m_CompositingQuality=	m_CompositingQuality;
	GPC.m_InterpolationMode=	m_InterpolationMode;
	GPC.m_PixelOffsetMode=		m_PixelOffsetMode;
	GPC.m_SmoothingMode=		m_SmoothingMode;
	GPC.m_TextContrast=			m_TextContrast;
	GPC.m_TextRenderingHint=	m_TextRenderingHint;
	GPC.m_Language=				m_Language;
	GPC.m_SubLanguage=			m_SubLanguage;

	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_CompositingQuality",GPC.m_CompositingQuality	);
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_InterpolationMode",GPC.m_InterpolationMode	);
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_PixelOffsetMode",GPC.m_PixelOffsetMode		);
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_SmoothingMode",GPC.m_SmoothingMode			);
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_TextContrast",GPC.m_TextContrast				);
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_TextRenderingHint",GPC.m_TextRenderingHint	);
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_Language",GPC.m_Language						);
	app->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_SubLanguage",GPC.m_SubLanguage				);

	GPScreen *s=GPC.m_Document->GetMainScreen();
	GPWindow *w=s->GPActiveWindow();

	s->FontDeltaX=GPScreen::ScrFontDeltaX=m_FontDX;
	s->FontDeltaY=GPScreen::ScrFontDeltaY=m_FontDY;
	s->FontOfsetX=GPScreen::ScrFontOfsetX=m_FontOX;
	s->FontOfsetY=GPScreen::ScrFontOfsetY=m_FontOY;

	CString tmpCS;
	tmpCS.Format("%g",GPScreen::ScrFontDeltaX);
	app->WriteProfileString(GPC.cs_RegTermViewSetName, "ScrFontDeltaX",tmpCS);
	tmpCS.Format("%g",GPScreen::ScrFontDeltaY);
	app->WriteProfileString(GPC.cs_RegTermViewSetName, "ScrFontDeltaY",tmpCS);
	tmpCS.Format("%g",GPScreen::ScrFontOfsetX);
	app->WriteProfileString(GPC.cs_RegTermViewSetName, "ScrFontOfsetX",tmpCS);
	tmpCS.Format("%g",GPScreen::ScrFontOfsetY);
	app->WriteProfileString(GPC.cs_RegTermViewSetName, "ScrFontOfsetY",tmpCS);

	w->m_CompositingQuality=GPC.m_CompositingQuality;
	w->m_InterpolationMode=	GPC.m_InterpolationMode;
	w->m_PixelOffsetMode=	GPC.m_PixelOffsetMode;
	w->m_SmoothingMode=		GPC.m_SmoothingMode;
	w->m_TextContrast=		GPC.m_TextContrast;
	w->m_TextRenderingHint= GPC.m_TextRenderingHint;
	w->m_Language= GPC.m_Language;
	w->m_SubLanguage= GPC.m_SubLanguage;


	s->RestoreScr(GPMAX_NSAVEDREGION-2);

	CDialog::OnOK();
}

void CDlgFontSet::OnCancel() 
{
	GPScreen *s=GPC.m_Document->GetMainScreen();
	CWinApp *app=AfxGetApp();
	FontTable.InitFontTable(app->GetProfileString(GPC.cs_RegTermViewSetName, "m_FontName","Courier new"),s);
	GPWindow *w=s->GPActiveWindow();

	s->FontDeltaX=GPScreen::ScrFontDeltaX=(REAL)atof(app->GetProfileString(GPC.cs_RegTermViewSetName, "ScrFontDeltaX","0"));
	s->FontDeltaY=GPScreen::ScrFontDeltaY=(REAL)atof(app->GetProfileString(GPC.cs_RegTermViewSetName, "ScrFontDeltaY","0"));
	s->FontOfsetX=GPScreen::ScrFontOfsetX=(REAL)atof(app->GetProfileString(GPC.cs_RegTermViewSetName, "ScrFontOfsetX","0"));
	s->FontOfsetY=GPScreen::ScrFontOfsetY=(REAL)atof(app->GetProfileString(GPC.cs_RegTermViewSetName, "ScrFontOfsetY","0"));

	w->m_CompositingQuality=GPC.m_CompositingQuality;
	w->m_InterpolationMode=	GPC.m_InterpolationMode;
	w->m_PixelOffsetMode=	GPC.m_PixelOffsetMode;
	w->m_SmoothingMode=		GPC.m_SmoothingMode;
	w->m_TextContrast=		GPC.m_TextContrast;
	w->m_TextRenderingHint= GPC.m_TextRenderingHint;
	w->m_Language=			GPC.m_Language;
	w->m_SubLanguage=		GPC.m_SubLanguage;

	s->RestoreScr(GPMAX_NSAVEDREGION-2);

	CDialog::OnCancel();
}

#include "DlgCodeco.h"
void CDlgFontSet::OnButtonCodeco()
{
	CDlgCodeco dlg(this);
	dlg.DoModal();
}

void CDlgFontSet::OnButtonTestScreen() 
{
	GPScreen *scr=GPC.m_Document->GetMainScreen();
	GPWindow *wnd=scr->GPGetWindowByNum(0);

	unsigned short * WndChar=wnd->WndChar;	
	UINT * WndChrRGB=wnd->WndChrRGB;
	UINT * WndBkgRGB=wnd->WndBkgRGB;
	UINT * WndChrStyle=wnd->WndChrStyle;

	int m_curMB2SP=IsDlgButtonChecked(IDC_CHECKWIDEON2POS)?1:0;

	int nChars=(wnd->nall-224)/256;
	if (nChars==0) nChars=1;
	int delta=256/nChars;
	if (delta==0) delta=1;
	DWORD ch=32;
	UINT i;
	for(i=0;i<wnd->nall;i++)
	{
		if (i>=224)
		{
			//ch=(i&0xFF)+(i/0x10)*0x100;
			*(WndChar++)=(m_curMB2SP && (i&1))?0:(unsigned short)ch;
			*(WndChrStyle++)=0;
			*(WndChrRGB++)=RGB(((i+500)/4)%256,((i+1500)/8)%256,((i+4000)/16)%256);
			*(WndBkgRGB++)=RGB(((i)/9)%256,((i)/3)%256,((i)/1)%256);
			ch+=delta;
		}
		else
		{
			*(WndChar++)=(unsigned short)ch;
			*(WndChrStyle++)=(ch>175 && ch<224)?GP_FNT_CODE:0;
			*(WndChrRGB++)=RGB(((i+500)/4)%256,((i+1500)/8)%256,((i+4000)/16)%256);
			*(WndBkgRGB++)=RGB(((i)/9)%256,((i)/3)%256,((i)/1)%256);
			ch++;
		}
	}
	UpdateScrView();
}

void CDlgFontSet::OnSelchangeCombofont() 
{
	m_FontCombo.GetWindowText(m_CurFontName);

	int sel;
	m_CompositingQuality=CompositingQualityDefault;
	sel=m_ComboCompositingQuality.GetCurSel();
	if (sel!=CB_ERR) m_CompositingQuality=(CompositingQuality)m_ComboCompositingQuality.GetItemData(sel);

	m_InterpolationMode=InterpolationModeDefault;
	sel=m_ComboInterpolationMode.GetCurSel();
	if (sel!=CB_ERR) m_InterpolationMode=(InterpolationMode)m_ComboInterpolationMode.GetItemData(sel);

	m_PixelOffsetMode=PixelOffsetModeDefault;
	sel=m_ComboPixelOffsetMode.GetCurSel();
	if (sel!=CB_ERR) m_PixelOffsetMode=(PixelOffsetMode)m_ComboPixelOffsetMode.GetItemData(sel);

	m_SmoothingMode=SmoothingModeDefault;
	sel=m_ComboSmoothingMode.GetCurSel();
	if (sel!=CB_ERR) m_SmoothingMode=(SmoothingMode)m_ComboSmoothingMode.GetItemData(sel);

	m_TextContrast=0;
	sel=m_ComboTextContrast.GetCurSel();
	if (sel!=CB_ERR) m_TextContrast=m_ComboTextContrast.GetItemData(sel);

	m_TextRenderingHint=TextRenderingHintSystemDefault;
	sel=m_ComboTextRenderingHint.GetCurSel();
	if (sel!=CB_ERR) m_TextRenderingHint=(TextRenderingHint)m_ComboTextRenderingHint.GetItemData(sel);

	m_Language=LANG_NEUTRAL;
	sel=m_ComboLanguage.GetCurSel();
	if (sel!=CB_ERR) m_Language=m_ComboLanguage.GetItemData(sel);

	m_SubLanguage=SUBLANG_NEUTRAL;
	sel=m_ComboSubLanguage.GetCurSel();
	if (sel!=CB_ERR) m_SubLanguage=m_ComboSubLanguage.GetItemData(sel);

	m_CurCodePage=CP_ACP;
	sel=m_ComboCP.GetCurSel();
	if (sel!=CB_ERR) m_CurCodePage=m_ComboCP.GetItemData(sel);


	UpdateScrView();
}


void CDlgFontSet::UpdateScrView()
{
	GPScreen *s=GPC.m_Document->GetMainScreen();
	if (s)
	{
		GPWindow *w=s->GPActiveWindow();
		w->m_CompositingQuality=m_CompositingQuality;
		w->m_InterpolationMode=m_InterpolationMode;
		w->m_PixelOffsetMode=m_PixelOffsetMode;
		w->m_SmoothingMode=m_SmoothingMode;
		w->m_TextContrast=m_TextContrast;
		w->m_TextRenderingHint=m_TextRenderingHint;
		w->m_Language=m_Language;
		w->m_SubLanguage=m_SubLanguage;
		w->m_CurCodePage=m_CurCodePage;
		s->FontDeltaX=m_FontDX;
		s->FontDeltaY=m_FontDY;
		s->FontOfsetX=m_FontOX;
		s->FontOfsetY=m_FontOY;

		FontTable.InitFontTable(m_CurFontName,s);
		w->RedrawWnd();
	}
}

#include "DlgGraphCode.h"

void CDlgFontSet::OnButtongraph() 
{
	CDlgGraphCode dlg;
	dlg.DoModal();
}

void CDlgFontSet::OnEnChangeEditfont()
{
	if (!m_bLockUpdate)
	{
		KillTimer(10);

		CString tmpCS;
		GetDlgItemText(IDC_EDITFONTDX,tmpCS);
		m_FontDX=(REAL)atof(tmpCS);
		GetDlgItemText(IDC_EDITFONTDY,tmpCS);
		m_FontDY=(REAL)atof(tmpCS);
		GetDlgItemText(IDC_EDITFONTOX,tmpCS);
		m_FontOX=(REAL)atof(tmpCS);
		GetDlgItemText(IDC_EDITFONTOY,tmpCS);
		m_FontOY=(REAL)atof(tmpCS);

		SetTimer(10,500,NULL);
	}
}


void CDlgFontSet::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(nIDEvent);
	switch(nIDEvent)
	{
	case 10:
		UpdateScrView();
		break;
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}
