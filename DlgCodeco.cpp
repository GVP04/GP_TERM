// DlgCodeco.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgCodeco.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCodeco dialog

const char *CDlgCodeco::CodecoFileName="CODECO.TXT";


const DWORD CDlgCodeco::nLang=77;
const DWORD CDlgCodeco::nSubLang=93;

const WORD CDlgCodeco::wArrLang[]={
		LANG_NEUTRAL,LANG_INVARIANT,LANG_AFRIKAANS,LANG_ALBANIAN,LANG_ARABIC,
		LANG_ARMENIAN,LANG_ASSAMESE,LANG_AZERI,LANG_BASQUE,LANG_BELARUSIAN,
		LANG_BENGALI,LANG_BULGARIAN,LANG_CATALAN,LANG_CHINESE,LANG_CROATIAN,
		LANG_CZECH,LANG_DANISH,LANG_DIVEHI,LANG_DUTCH,LANG_ENGLISH,
		LANG_ESTONIAN,LANG_FAEROESE,LANG_FARSI,LANG_FINNISH,LANG_FRENCH,
		LANG_GALICIAN,LANG_GEORGIAN,LANG_GERMAN,LANG_GREEK,LANG_GUJARATI,
		LANG_HEBREW,LANG_HINDI,LANG_HUNGARIAN,LANG_ICELANDIC,LANG_INDONESIAN,
		LANG_ITALIAN,LANG_JAPANESE,LANG_KANNADA,LANG_KASHMIRI,LANG_KAZAK,
		LANG_KONKANI,LANG_KOREAN,LANG_KYRGYZ,LANG_LATVIAN,LANG_LITHUANIAN,
		LANG_MACEDONIAN,LANG_MALAY,LANG_MALAYALAM,LANG_MANIPURI,LANG_MARATHI,
		LANG_MONGOLIAN,LANG_NEPALI,LANG_NORWEGIAN,LANG_ORIYA,LANG_POLISH,
		LANG_PORTUGUESE,LANG_PUNJABI,LANG_ROMANIAN,LANG_RUSSIAN,LANG_SANSKRIT,
		LANG_SERBIAN,LANG_SINDHI,LANG_SLOVAK,LANG_SLOVENIAN,LANG_SPANISH,
		LANG_SWAHILI,LANG_SWEDISH,LANG_SYRIAC,LANG_TAMIL,LANG_TATAR,
		LANG_TELUGU,LANG_THAI,LANG_TURKISH,LANG_UKRAINIAN,LANG_URDU,
		LANG_UZBEK,LANG_VIETNAMESE,
		LANG_NEUTRAL,
		};
const WORD CDlgCodeco::wArrSubLang[]={
		SUBLANG_NEUTRAL,SUBLANG_DEFAULT,SUBLANG_SYS_DEFAULT,LANG_ARABIC*0x100+SUBLANG_ARABIC_SAUDI_ARABIA,LANG_ARABIC*0x100+SUBLANG_ARABIC_IRAQ,
		LANG_ARABIC*0x100+SUBLANG_ARABIC_EGYPT,LANG_ARABIC*0x100+SUBLANG_ARABIC_LIBYA,LANG_ARABIC*0x100+SUBLANG_ARABIC_ALGERIA,LANG_ARABIC*0x100+SUBLANG_ARABIC_MOROCCO,LANG_ARABIC*0x100+SUBLANG_ARABIC_TUNISIA,
		LANG_ARABIC*0x100+SUBLANG_ARABIC_OMAN,LANG_ARABIC*0x100+SUBLANG_ARABIC_YEMEN,LANG_ARABIC*0x100+SUBLANG_ARABIC_SYRIA,LANG_ARABIC*0x100+SUBLANG_ARABIC_JORDAN,LANG_ARABIC*0x100+SUBLANG_ARABIC_LEBANON,
		LANG_ARABIC*0x100+SUBLANG_ARABIC_KUWAIT,LANG_ARABIC*0x100+SUBLANG_ARABIC_UAE,LANG_ARABIC*0x100+SUBLANG_ARABIC_BAHRAIN,LANG_ARABIC*0x100+SUBLANG_ARABIC_QATAR,LANG_AZERI*0x100+SUBLANG_AZERI_LATIN,
		LANG_AZERI*0x100+SUBLANG_AZERI_CYRILLIC,LANG_CHINESE*0x100+SUBLANG_CHINESE_TRADITIONAL,LANG_CHINESE*0x100+SUBLANG_CHINESE_SIMPLIFIED,LANG_CHINESE*0x100+SUBLANG_CHINESE_HONGKONG,LANG_CHINESE*0x100+SUBLANG_CHINESE_SINGAPORE,
		LANG_CHINESE*0x100+SUBLANG_CHINESE_MACAU,LANG_DUTCH*0x100+SUBLANG_DUTCH,LANG_DUTCH*0x100+SUBLANG_DUTCH_BELGIAN,LANG_ENGLISH*0x100+SUBLANG_ENGLISH_US,LANG_ENGLISH*0x100+SUBLANG_ENGLISH_UK,
		LANG_ENGLISH*0x100+SUBLANG_ENGLISH_AUS,LANG_ENGLISH*0x100+SUBLANG_ENGLISH_CAN,LANG_ENGLISH*0x100+SUBLANG_ENGLISH_NZ,LANG_ENGLISH*0x100+SUBLANG_ENGLISH_EIRE,LANG_ENGLISH*0x100+SUBLANG_ENGLISH_SOUTH_AFRICA,
		LANG_ENGLISH*0x100+SUBLANG_ENGLISH_JAMAICA,LANG_ENGLISH*0x100+SUBLANG_ENGLISH_CARIBBEAN,LANG_ENGLISH*0x100+SUBLANG_ENGLISH_BELIZE,LANG_ENGLISH*0x100+SUBLANG_ENGLISH_TRINIDAD,LANG_ENGLISH*0x100+SUBLANG_ENGLISH_ZIMBABWE,
		LANG_ENGLISH*0x100+SUBLANG_ENGLISH_PHILIPPINES,LANG_FRENCH*0x100+SUBLANG_FRENCH,LANG_FRENCH*0x100+SUBLANG_FRENCH_BELGIAN,LANG_FRENCH*0x100+SUBLANG_FRENCH_CANADIAN,LANG_FRENCH*0x100+SUBLANG_FRENCH_SWISS,
		LANG_FRENCH*0x100+SUBLANG_FRENCH_LUXEMBOURG,LANG_FRENCH*0x100+SUBLANG_FRENCH_MONACO,LANG_GERMAN*0x100+SUBLANG_GERMAN,LANG_GERMAN*0x100+SUBLANG_GERMAN_SWISS,LANG_GERMAN*0x100+SUBLANG_GERMAN_AUSTRIAN,
		LANG_GERMAN*0x100+SUBLANG_GERMAN_LUXEMBOURG,LANG_GERMAN*0x100+SUBLANG_GERMAN_LIECHTENSTEIN,LANG_ITALIAN*0x100+SUBLANG_ITALIAN,LANG_ITALIAN*0x100+SUBLANG_ITALIAN_SWISS,LANG_KASHMIRI*0x100+SUBLANG_KASHMIRI_SASIA,
		LANG_KASHMIRI*0x100+SUBLANG_KASHMIRI_INDIA,LANG_KOREAN*0x100+SUBLANG_KOREAN,LANG_LITHUANIAN*0x100+SUBLANG_LITHUANIAN,LANG_MALAY*0x100+SUBLANG_MALAY_MALAYSIA,LANG_MALAY*0x100+SUBLANG_MALAY_BRUNEI_DARUSSALAM,
		LANG_NEPALI*0x100+SUBLANG_NEPALI_INDIA,LANG_NORWEGIAN*0x100+SUBLANG_NORWEGIAN_BOKMAL,LANG_NORWEGIAN*0x100+SUBLANG_NORWEGIAN_NYNORSK,LANG_PORTUGUESE*0x100+SUBLANG_PORTUGUESE,LANG_PORTUGUESE*0x100+SUBLANG_PORTUGUESE_BRAZILIAN,
		LANG_SERBIAN*0x100+SUBLANG_SERBIAN_LATIN,LANG_SERBIAN*0x100+SUBLANG_SERBIAN_CYRILLIC,LANG_SPANISH*0x100+SUBLANG_SPANISH,LANG_SPANISH*0x100+SUBLANG_SPANISH_MEXICAN,LANG_SPANISH*0x100+SUBLANG_SPANISH_MODERN,
		LANG_SPANISH*0x100+SUBLANG_SPANISH_GUATEMALA,LANG_SPANISH*0x100+SUBLANG_SPANISH_COSTA_RICA,LANG_SPANISH*0x100+SUBLANG_SPANISH_PANAMA,LANG_SPANISH*0x100+SUBLANG_SPANISH_DOMINICAN_REPUBLIC,LANG_SPANISH*0x100+SUBLANG_SPANISH_VENEZUELA,
		LANG_SPANISH*0x100+SUBLANG_SPANISH_COLOMBIA,LANG_SPANISH*0x100+SUBLANG_SPANISH_PERU,LANG_SPANISH*0x100+SUBLANG_SPANISH_ARGENTINA,LANG_SPANISH*0x100+SUBLANG_SPANISH_ECUADOR,LANG_SPANISH*0x100+SUBLANG_SPANISH_CHILE,
		LANG_SPANISH*0x100+SUBLANG_SPANISH_URUGUAY,LANG_SPANISH*0x100+SUBLANG_SPANISH_PARAGUAY,LANG_SPANISH*0x100+SUBLANG_SPANISH_BOLIVIA,LANG_SPANISH*0x100+SUBLANG_SPANISH_EL_SALVADOR,LANG_SPANISH*0x100+SUBLANG_SPANISH_HONDURAS,
		LANG_SPANISH*0x100+SUBLANG_SPANISH_NICARAGUA,LANG_SPANISH*0x100+SUBLANG_SPANISH_PUERTO_RICO,LANG_SWEDISH*0x100+SUBLANG_SWEDISH,LANG_SWEDISH*0x100+SUBLANG_SWEDISH_FINLAND,LANG_URDU*0x100+SUBLANG_URDU_PAKISTAN,
		LANG_URDU*0x100+SUBLANG_URDU_INDIA,LANG_UZBEK*0x100+SUBLANG_UZBEK_LATIN,LANG_UZBEK*0x100+SUBLANG_UZBEK_CYRILLIC,
		SUBLANG_NEUTRAL,
		};

const char *CDlgCodeco::cArrLangName[]={
		" NEUTRAL","INVARIANT","AFRIKAANS","ALBANIAN","ARABIC",
		"ARMENIAN","ASSAMESE","AZERI","BASQUE","BELARUSIAN",
		"BENGALI","BULGARIAN","CATALAN","CHINESE","CROATIAN",
		"CZECH","DANISH","DIVEHI","DUTCH","ENGLISH",
		"ESTONIAN","FAEROESE","FARSI","FINNISH","FRENCH",
		"GALICIAN","GEORGIAN","GERMAN","GREEK","GUJARATI",
		"HEBREW","HINDI","HUNGARIAN","ICELANDIC","INDONESIAN",
		"ITALIAN","JAPANESE","KANNADA","KASHMIRI","KAZAK",
		"KONKANI","KOREAN","KYRGYZ","LATVIAN","LITHUANIAN",
		"MACEDONIAN","MALAY","MALAYALAM","MANIPURI","MARATHI",
		"MONGOLIAN","NEPALI","NORWEGIAN","ORIYA","POLISH",
		"PORTUGUESE","PUNJABI","ROMANIAN","RUSSIAN","SANSKRIT",
		"SERBIAN","SINDHI","SLOVAK","SLOVENIAN","SPANISH",
		"SWAHILI","SWEDISH","SYRIAC","TAMIL","TATAR",
		"TELUGU","THAI","TURKISH","UKRAINIAN","URDU",
		"UZBEK","VIETNAMESE",
		"",
		};
const char *CDlgCodeco::cArrSubLangName[]={
		" NEUTRAL"," DEFAULT","SYS_DEFAULT","ARABIC_SAUDI_ARABIA","ARABIC_IRAQ",
		"ARABIC_EGYPT","ARABIC_LIBYA","ARABIC_ALGERIA","ARABIC_MOROCCO","ARABIC_TUNISIA",
		"ARABIC_OMAN","ARABIC_YEMEN","ARABIC_SYRIA","ARABIC_JORDAN","ARABIC_LEBANON",
		"ARABIC_KUWAIT","ARABIC_UAE","ARABIC_BAHRAIN","ARABIC_QATAR","AZERI_LATIN",
		"AZERI_CYRILLIC","CHINESE_TRADITIONAL","CHINESE_SIMPLIFIED","CHINESE_HONGKONG","CHINESE_SINGAPORE",
		"CHINESE_MACAU","DUTCH","DUTCH_BELGIAN","ENGLISH_US","ENGLISH_UK",
		"ENGLISH_AUS","ENGLISH_CAN","ENGLISH_NZ","ENGLISH_EIRE","ENGLISH_SOUTH_AFRICA",
		"ENGLISH_JAMAICA","ENGLISH_CARIBBEAN","ENGLISH_BELIZE","ENGLISH_TRINIDAD","ENGLISH_ZIMBABWE",
		"ENGLISH_PHILIPPINES","FRENCH","FRENCH_BELGIAN","FRENCH_CANADIAN","FRENCH_SWISS",
		"FRENCH_LUXEMBOURG","FRENCH_MONACO","GERMAN","GERMAN_SWISS","GERMAN_AUSTRIAN",
		"GERMAN_LUXEMBOURG","GERMAN_LIECHTENSTEIN","ITALIAN","ITALIAN_SWISS","KASHMIRI_SASIA",
		"KASHMIRI_INDIA","KOREAN","LITHUANIAN","MALAY_MALAYSIA","MALAY_BRUNEI_DARUSSALAM",
		"NEPALI_INDIA","NORWEGIAN_BOKMAL","NORWEGIAN_NYNORSK","PORTUGUESE","PORTUGUESE_BRAZILIAN",
		"SERBIAN_LATIN","SERBIAN_CYRILLIC","SPANISH","SPANISH_MEXICAN","SPANISH_MODERN",
		"SPANISH_GUATEMALA","SPANISH_COSTA_RICA","SPANISH_PANAMA","SPANISH_DOMINICAN_REPUBLIC","SPANISH_VENEZUELA",
		"SPANISH_COLOMBIA","SPANISH_PERU","SPANISH_ARGENTINA","SPANISH_ECUADOR","SPANISH_CHILE",
		"SPANISH_URUGUAY","SPANISH_PARAGUAY","SPANISH_BOLIVIA","SPANISH_EL_SALVADOR","SPANISH_HONDURAS",
		"SPANISH_NICARAGUA","SPANISH_PUERTO_RICO","SWEDISH","SWEDISH_FINLAND","URDU_PAKISTAN",
		"URDU_INDIA","UZBEK_LATIN","UZBEK_CYRILLIC",
		"",
		};



CDlgCodeco::CDlgCodeco(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCodeco::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCodeco)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	DlgAutoSize=NULL;

	m_ConvArr[0]=m_chDosAnsi;
	m_ConvArr[1]=m_chAnsiDos;
	m_ConvArr[2]=m_chWideDosAnsi;
	m_ConvArr[3]=m_chWideAnsiDos;
	m_ConvArr[4]=m_chWideDosAnsi2;
	m_ConvArr[5]=m_chWideAnsiDos2;
	nLists=6;
}

CDlgCodeco::~CDlgCodeco()
{
	if (DlgAutoSize)
		delete DlgAutoSize;
	DlgAutoSize=NULL;
}


void CDlgCodeco::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCodeco)
	DDX_Control(pDX, IDC_COMBOSRVPC, m_Combo3SrvPC);
	DDX_Control(pDX, IDC_COMBOPCSRV, m_Combo3PCSrv);
	DDX_Control(pDX, IDC_LIST6, m_CodeListWideToServer2);
	DDX_Control(pDX, IDC_LIST5, m_CodeListWideToPC2);
	DDX_Control(pDX, IDC_COMBO6, m_ComboWideToServer2);
	DDX_Control(pDX, IDC_COMBO5, m_ComboWideToPC2);
	DDX_Control(pDX, IDC_LIST4, m_CodeListWideToServer);
	DDX_Control(pDX, IDC_COMBO4, m_ComboWideToServer);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Control(pDX, IDC_COMBO1, m_ComboToPC);
	DDX_Control(pDX, IDC_COMBO2, m_ComboToServer);
	DDX_Control(pDX, IDC_COMBO3, m_ComboWideToPC);
	DDX_Control(pDX, IDC_LIST1, m_CodeListToPC);
	DDX_Control(pDX, IDC_LIST2, m_CodeListToServer);
	DDX_Control(pDX, IDC_LIST3, m_CodeListWideToPC);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCodeco, CDialog)
	//{{AFX_MSG_MAP(CDlgCodeco)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTNDEF, OnBtndef)
	ON_BN_CLICKED(IDC_BTNLOAD, OnBtnload)
	ON_BN_CLICKED(IDC_BTNSAVE, OnBtnsave)
	ON_BN_CLICKED(IDC_OK, OnOk)
	ON_BN_CLICKED(IDC_BTNCURRENT, OnBtncurrent)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_CBN_CLOSEUP(IDC_COMBO1, OnCloseupCombo)
	ON_CBN_CLOSEUP(IDC_COMBO2, OnCloseupCombo)
	ON_CBN_CLOSEUP(IDC_COMBO3, OnCloseupCombo)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, OnClickList)
	ON_NOTIFY(NM_CLICK, IDC_LIST3, OnClickList)
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	ON_CBN_CLOSEUP(IDC_COMBO4, OnCloseupCombo)
	ON_CBN_CLOSEUP(IDC_COMBO5, OnCloseupCombo)
	ON_CBN_CLOSEUP(IDC_COMBO6, OnCloseupCombo)
	ON_NOTIFY(NM_CLICK, IDC_LIST4, OnClickList)
	ON_NOTIFY(NM_CLICK, IDC_LIST5, OnClickList)
	ON_NOTIFY(NM_CLICK, IDC_LIST6, OnClickList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCodeco message handlers

BOOL CDlgCodeco::OnInitDialog()
{
	CDialog::OnInitDialog();
	mlists[0]=&m_CodeListToPC;
	mlists[1]=&m_CodeListToServer;
	mlists[2]=&m_CodeListWideToPC;
	mlists[3]=&m_CodeListWideToServer;
	mlists[4]=&m_CodeListWideToPC2;
	mlists[5]=&m_CodeListWideToServer2;
	mcompos[0]=&m_ComboToPC;
	mcompos[1]=&m_ComboToServer;
	mcompos[2]=&m_ComboWideToPC;
	mcompos[3]=&m_ComboWideToServer;
	mcompos[4]=&m_ComboWideToPC2;
	mcompos[5]=&m_ComboWideToServer2;


	DlgAutoSize=new GP_AutoSizing;
	DlgAutoSize->AddSetMain(m_hWnd);
	DlgAutoSize->SetMinSize(m_hWnd,700,350);
	DlgAutoSize->AddWnd(m_tab.m_hWnd,m_hWnd,"NNNE");

	UINT j;
	for(j=0;j<nLists;j++)
	{
		mlists[j]->ShowWindow(SW_HIDE);
		mcompos[j]->ShowWindow(SW_HIDE);
		mcompos[j]->ResetContent();
		mlists[j]->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
		mlists[j]->InsertColumn(0,"Source code",LVCFMT_LEFT,100,0);
		mlists[j]->InsertColumn(1,"Current",LVCFMT_LEFT,100,0);
		mlists[j]->InsertColumn(2,"Default",LVCFMT_LEFT,100,0);
		mlists[j]->InsertColumn(3,"New value",LVCFMT_LEFT,100,0);
		mlists[j]->GetHeaderCtrl()->ModifyStyle(0,HDS_BUTTONS);
		DlgAutoSize->AddWnd(mlists[j]->m_hWnd,m_hWnd,"NNEE");
	}
	mlists[0]->ShowWindow(SW_SHOW);

	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BTNLOAD),m_hWnd,"NENE");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BTNSAVE),m_hWnd,"NENE");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BTNDEF),m_hWnd,"NENE");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BTNCURRENT),m_hWnd,"NENE");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_OK),m_hWnd,"EEEE");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_CANCEL),m_hWnd,"EEEE");

	m_tab.InsertItem(0,"SRV to PC");
	m_tab.InsertItem(1,"PC to SRV");
	m_tab.InsertItem(2,"Wide1 SRV to PC");
	m_tab.InsertItem(3,"Wide1 PC to SRV");
	m_tab.InsertItem(4,"Wide2 SRV to PC");
	m_tab.InsertItem(5,"Wide2 PC to SRV");
	m_tab.InsertItem(6,"Additional conversion");
	m_tab.SetCurSel(0);

	OnBtncurrent(-1);

	CString tmpstr;
	const char *fmt_s="%3.3d   %2.2X   %s";
	const char *fmt_c="%3.3d   %2.2X   %c";

	UINT i;
	for(j=0;j<256;j++)
	{
		if (j<33)
			tmpstr.Format(fmt_s,j,j,cArrBytesName[j]);
		else
			tmpstr.Format(fmt_c,j,j,j);
		for(i=0;i<nLists;i++)
		{
			mlists[i]->InsertItem(j,tmpstr);
			mcompos[i]->AddString(tmpstr);
		}
	}

	const char *ccTmpstr[]={"None","Use Multibyte to Wide string conversion","Use LCMapString function","Combined MB then LC","Combined LC then MB",};
	const DWORD dwConv[]={GPC.MBC3_NONE,GPC.MBC3_MBTOWIDECHAR,GPC.MBC3_LCMAPSTRING,GPC.MBC3_MBLC,GPC.MBC3_LCMB,};

	for(i=0;i<5;i++)
	{
		j=m_Combo3PCSrv.AddString(ccTmpstr[i]);
		m_Combo3PCSrv.SetItemData(j,dwConv[i]);
		if (GPC.m_CONV3PCSRV.dwType==dwConv[i]) m_Combo3PCSrv.SetCurSel(j);
		j=m_Combo3SrvPC.AddString(ccTmpstr[i]);
		m_Combo3SrvPC.SetItemData(j,dwConv[i]);
		if (GPC.m_CONV3SRVPC.dwType==dwConv[i]) m_Combo3SrvPC.SetCurSel(j);
	}

	DWORD ids[14]={
		IDC_COMBOWIDTHSRVPC,IDC_COMBOWIDTHPCSRV,IDC_CHECKBRSRVPC,IDC_CHECKBRPCSRV,
		IDC_COMBOLNGSRVPC,IDC_COMBOLNGPCSRV,IDC_COMBOSUBLNGSRVPC,IDC_COMBOSUBLNGPCSRV,
		IDC_COMBOCONVSRVPC,IDC_COMBOCONVPCSRV,IDC_COMBOCASESRVPC,IDC_COMBOCASEPCSRV,
		IDC_EDITCPPCSRV,IDC_EDITCPSRVPC,
	};
	//#define LCMAP_LINGUISTIC_CASING   0x01000000  // use linguistic rules for casing

	for(i=0;i<14;i++)
	{
		HWND ctlHwnd=::GetDlgItem(m_hWnd,ids[i]);
		if (ctlHwnd)
		{
			int tmpint;
			switch(ids[i])
			{
			case IDC_COMBOLNGSRVPC:
			case IDC_COMBOLNGPCSRV:
				for(j=0;j<nLang;j++)
				{
					tmpint=::SendMessage(ctlHwnd,CB_ADDSTRING,0,(LPARAM)cArrLangName[j]);
					::SendMessage(ctlHwnd,CB_SETITEMDATA,tmpint,wArrLang[j]);
					if ((ids[i]==IDC_COMBOLNGSRVPC && wArrLang[j]==GPC.m_CONV3SRVPC.dwLang)
						|| (ids[i]==IDC_COMBOLNGPCSRV && wArrLang[j]==GPC.m_CONV3PCSRV.dwLang))
						::SendMessage(ctlHwnd,CB_SETCURSEL,tmpint,0);
				}
				break;
			case IDC_COMBOSUBLNGSRVPC:
			case IDC_COMBOSUBLNGPCSRV:
				for(j=0;j<nSubLang;j++)
				{
					tmpint=::SendMessage(ctlHwnd,CB_ADDSTRING,0,(LPARAM)cArrSubLangName[j]);
					::SendMessage(ctlHwnd,CB_SETITEMDATA,tmpint,wArrSubLang[j]);
					if ((ids[i]==IDC_COMBOSUBLNGSRVPC && wArrSubLang[j]==GPC.m_CONV3SRVPC.dwSubLang)
						|| (ids[i]==IDC_COMBOSUBLNGPCSRV && wArrSubLang[j]==GPC.m_CONV3PCSRV.dwSubLang))
						::SendMessage(ctlHwnd,CB_SETCURSEL,tmpint,0);
				}
				break;
			case IDC_COMBOWIDTHSRVPC:
			case IDC_COMBOWIDTHPCSRV:
				{
					char *cArr[]={" None","HALFWIDTH","FULLWIDTH",};
					DWORD dwArr[]={0,LCMAP_HALFWIDTH,LCMAP_FULLWIDTH,};
					for(j=0;j<3;j++)
					{
						tmpint=::SendMessage(ctlHwnd,CB_ADDSTRING,0,(LPARAM)cArr[j]);
						::SendMessage(ctlHwnd,CB_SETITEMDATA,tmpint,dwArr[j]);
						if ((ids[i]==IDC_COMBOWIDTHSRVPC && dwArr[j]==(GPC.m_CONV3SRVPC.dwConv&dwArr[j]))
							|| (ids[i]==IDC_COMBOWIDTHPCSRV && dwArr[j]==(GPC.m_CONV3PCSRV.dwConv&dwArr[j])))
							::SendMessage(ctlHwnd,CB_SETCURSEL,tmpint,0);
					}
				}

				break;
			case IDC_COMBOCASESRVPC:
			case IDC_COMBOCASEPCSRV:
				{
					char *cArr[]={" None","LOWERCASE","UPPERCASE",};
					DWORD dwArr[]={0,LCMAP_LOWERCASE,LCMAP_UPPERCASE,};
					for(j=0;j<3;j++)
					{
						tmpint=::SendMessage(ctlHwnd,CB_ADDSTRING,0,(LPARAM)cArr[j]);
						::SendMessage(ctlHwnd,CB_SETITEMDATA,tmpint,dwArr[j]);
						if ((ids[i]==IDC_COMBOCASESRVPC && dwArr[j]==(GPC.m_CONV3SRVPC.dwConv&dwArr[j]))
							|| (ids[i]==IDC_COMBOCASEPCSRV && dwArr[j]==(GPC.m_CONV3PCSRV.dwConv&dwArr[j])))
							::SendMessage(ctlHwnd,CB_SETCURSEL,tmpint,0);
					}
				}
				break;
			case IDC_COMBOCONVSRVPC:
			case IDC_COMBOCONVPCSRV:
				{
					char *cArr[]={" None","HIRAGANA","KATAKANA","SIMPLIFIED_CHINESE","TRADITIONAL_CHINESE",};
					DWORD dwArr[]={0,LCMAP_HIRAGANA,LCMAP_KATAKANA,LCMAP_SIMPLIFIED_CHINESE,LCMAP_TRADITIONAL_CHINESE};
					for(j=0;j<5;j++)
					{
						tmpint=::SendMessage(ctlHwnd,CB_ADDSTRING,0,(LPARAM)cArr[j]);
						::SendMessage(ctlHwnd,CB_SETITEMDATA,tmpint,dwArr[j]);
						if ((ids[i]==IDC_COMBOCONVSRVPC && dwArr[j]==(GPC.m_CONV3SRVPC.dwConv&dwArr[j]))
							|| (ids[i]==IDC_COMBOCONVPCSRV && dwArr[j]==(GPC.m_CONV3PCSRV.dwConv&dwArr[j])))
							::SendMessage(ctlHwnd,CB_SETCURSEL,tmpint,0);
					}
				}
				break;
			case IDC_CHECKBRSRVPC:
				::CheckDlgButton(m_hWnd,ids[i],(LCMAP_BYTEREV&GPC.m_CONV3SRVPC.dwConv)==LCMAP_BYTEREV);
				break;
			case IDC_CHECKBRPCSRV:
				::CheckDlgButton(m_hWnd,ids[i],(LCMAP_BYTEREV&GPC.m_CONV3PCSRV.dwConv)==LCMAP_BYTEREV);
				break;
			case IDC_EDITCPSRVPC:
				::SetDlgItemInt(m_hWnd,ids[i],GPC.m_CONV3SRVPC.dwCP,FALSE);
				break;
			case IDC_EDITCPPCSRV:
				::SetDlgItemInt(m_hWnd,ids[i],GPC.m_CONV3PCSRV.dwCP,FALSE);
				break;
			}
		}
	}


	FillList(-1);

	OnSelchangeTab1(NULL, (LRESULT*) &i);

	return TRUE;
}

void CDlgCodeco::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (DlgAutoSize)
	{
		try
		{
			GPC.m_ErrReport.GPWriteErrorLog("CDlgCodeco", "OnSize","387");
			DlgAutoSize->UpdateSize();
		}
		catch(...){;}
	}
}

void CDlgCodeco::OnDestroy()
{
	if (DlgAutoSize)
		delete DlgAutoSize;

	DlgAutoSize=NULL;

	CDialog::OnDestroy();
}

LRESULT CDlgCodeco::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	return CDialog::WindowProc(message, wParam, lParam);
}

BOOL CDlgCodeco::OnCommand(WPARAM wParam, LPARAM lParam)
{
	BOOL TypeRet=TRUE;
	if (wParam==1) TypeRet=FALSE;

	return TypeRet?CDialog::OnCommand(wParam, lParam):TRUE;
}

void CDlgCodeco::OnBtndef()
{
	char ptmpDA[256],ptmpAD[256],ptmpWideDA[256],ptmpWideAD[256],ptmpWideDA2[256],ptmpWideAD2[256];
	char *pptmpDA[]={ptmpDA,ptmpAD,ptmpWideDA,ptmpWideAD,ptmpWideDA2,ptmpWideAD2,};
	int nIdx=m_tab.GetCurSel();
	pptmpDA[nIdx]=m_ConvArr[nIdx];
	FillDefaultDosAnsiArrays(pptmpDA[1],pptmpDA[0],pptmpDA[3],pptmpDA[2],pptmpDA[5],pptmpDA[4]);
	FillList(m_tab.GetCurSel());
}

void CDlgCodeco::OnBtnload()
{
	char ptmpDA[256],ptmpAD[256],ptmpWideDA[256],ptmpWideAD[256],ptmpWideDA2[256],ptmpWideAD2[256];
	char *pptmpDA[]={ptmpDA,ptmpAD,ptmpWideDA,ptmpWideAD,ptmpWideDA2,ptmpWideAD2,};
	int nIdx=m_tab.GetCurSel();
	pptmpDA[nIdx]=m_ConvArr[nIdx];
	LoadDosAnsiArrays(pptmpDA[1],pptmpDA[0],pptmpDA[3],pptmpDA[2],pptmpDA[5],pptmpDA[4]);
	FillList(m_tab.GetCurSel());
}

void CDlgCodeco::OnBtnsave()
{
	SaveDosAnsiArrays(m_chAnsiDos,m_chDosAnsi,m_chWideAnsiDos,m_chWideDosAnsi,m_chWideAnsiDos2,m_chWideDosAnsi2);
}

void CDlgCodeco::OnCancel()
{
	CDialog::OnCancel();
}

void CDlgCodeco::OnOk()
{
	int i;
	for(i=0;i<256;i++)
	{
		GPC.chAnsiDos[i]=m_chAnsiDos[i];
		GPC.chDosAnsi[i]=m_chDosAnsi[i];
		GPC.chWideAnsiDos[i]=m_chWideAnsiDos[i];
		GPC.chWideDosAnsi[i]=m_chWideDosAnsi[i];
		GPC.chWideAnsiDos2[i]=m_chWideAnsiDos2[i];
		GPC.chWideDosAnsi2[i]=m_chWideDosAnsi2[i];
	}
	SaveDosAnsiArrays(m_chAnsiDos,m_chDosAnsi,m_chWideAnsiDos,m_chWideDosAnsi,m_chWideAnsiDos2,m_chWideDosAnsi2);


	GPC.m_CONV3PCSRV.dwType=m_Combo3PCSrv.GetItemData(m_Combo3PCSrv.GetCurSel());
	GPC.m_CONV3SRVPC.dwType=m_Combo3SrvPC.GetItemData(m_Combo3SrvPC.GetCurSel());

	AfxGetApp()->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV3PCSRV",GPC.m_CONV3PCSRV.dwType);
	AfxGetApp()->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV3SRVPC",GPC.m_CONV3SRVPC.dwType);

	DWORD ids[14]={
		IDC_COMBOWIDTHSRVPC,IDC_COMBOWIDTHPCSRV,IDC_CHECKBRSRVPC,IDC_CHECKBRPCSRV,
		IDC_COMBOLNGSRVPC,IDC_COMBOLNGPCSRV,IDC_COMBOSUBLNGSRVPC,IDC_COMBOSUBLNGPCSRV,
		IDC_COMBOCONVSRVPC,IDC_COMBOCONVPCSRV,IDC_COMBOCASESRVPC,IDC_COMBOCASEPCSRV,
		IDC_EDITCPPCSRV,IDC_EDITCPSRVPC,
	};
	//#define LCMAP_LINGUISTIC_CASING   0x01000000  // use linguistic rules for casing

	for(i=0;i<14;i++)
	{
		HWND ctlHwnd=::GetDlgItem(m_hWnd,ids[i]);
		if (ctlHwnd)
		{
			int tmpint;
			switch(ids[i])
			{
			case IDC_COMBOLNGSRVPC:
			case IDC_COMBOLNGPCSRV:
			case IDC_COMBOSUBLNGSRVPC:
			case IDC_COMBOSUBLNGPCSRV:
			case IDC_COMBOWIDTHSRVPC:
			case IDC_COMBOWIDTHPCSRV:
			case IDC_COMBOCASESRVPC:
			case IDC_COMBOCASEPCSRV:
			case IDC_COMBOCONVSRVPC:
			case IDC_COMBOCONVPCSRV:
				{
					tmpint=::SendMessage(ctlHwnd,CB_GETCURSEL,0,0);
					tmpint=::SendMessage(ctlHwnd,CB_GETITEMDATA,tmpint,0);
					switch(ids[i])
					{
					case IDC_COMBOLNGSRVPC:
						GPC.m_CONV3SRVPC.dwLang=tmpint;
						break;
					case IDC_COMBOLNGPCSRV:
						GPC.m_CONV3PCSRV.dwLang=tmpint;
						break;
					case IDC_COMBOSUBLNGSRVPC:
						GPC.m_CONV3SRVPC.dwSubLang=tmpint;
						break;
					case IDC_COMBOSUBLNGPCSRV:
						GPC.m_CONV3PCSRV.dwSubLang=tmpint;
						break;
					case IDC_COMBOWIDTHSRVPC:
						GPC.m_CONV3SRVPC.dwConv=(GPC.m_CONV3SRVPC.dwConv&(0xFFFFFFFF^(LCMAP_HALFWIDTH|LCMAP_FULLWIDTH)))|tmpint;
						break;
					case IDC_COMBOWIDTHPCSRV:
						GPC.m_CONV3PCSRV.dwConv=(GPC.m_CONV3PCSRV.dwConv&(0xFFFFFFFF^(LCMAP_HALFWIDTH|LCMAP_FULLWIDTH)))|tmpint;
						break;
					case IDC_COMBOCASESRVPC:
						GPC.m_CONV3SRVPC.dwConv=(GPC.m_CONV3SRVPC.dwConv&(0xFFFFFFFF^(LCMAP_LOWERCASE|LCMAP_UPPERCASE)))|tmpint;
						break;
					case IDC_COMBOCASEPCSRV:
						GPC.m_CONV3PCSRV.dwConv=(GPC.m_CONV3PCSRV.dwConv&(0xFFFFFFFF^(LCMAP_LOWERCASE|LCMAP_UPPERCASE)))|tmpint;
						break;
					case IDC_COMBOCONVSRVPC:
						GPC.m_CONV3SRVPC.dwConv=(GPC.m_CONV3SRVPC.dwConv&(0xFFFFFFFF^(LCMAP_HIRAGANA|LCMAP_KATAKANA|LCMAP_SIMPLIFIED_CHINESE|LCMAP_TRADITIONAL_CHINESE)))|tmpint;
						break;
					case IDC_COMBOCONVPCSRV:
						GPC.m_CONV3PCSRV.dwConv=(GPC.m_CONV3PCSRV.dwConv&(0xFFFFFFFF^(LCMAP_HIRAGANA|LCMAP_KATAKANA|LCMAP_SIMPLIFIED_CHINESE|LCMAP_TRADITIONAL_CHINESE)))|tmpint;
						break;
					}
				}
				break;
			case IDC_CHECKBRSRVPC:
				GPC.m_CONV3SRVPC.dwConv=(GPC.m_CONV3SRVPC.dwConv&(0xFFFFFFFF^LCMAP_BYTEREV))|(::IsDlgButtonChecked(m_hWnd,ids[i])?LCMAP_BYTEREV:0);
				break;
			case IDC_CHECKBRPCSRV:
				GPC.m_CONV3PCSRV.dwConv=(GPC.m_CONV3PCSRV.dwConv&(0xFFFFFFFF^LCMAP_BYTEREV))|(::IsDlgButtonChecked(m_hWnd,ids[i])?LCMAP_BYTEREV:0);
				break;
			case IDC_EDITCPSRVPC:
				GPC.m_CONV3SRVPC.dwCP=::GetDlgItemInt(m_hWnd,ids[i],NULL,FALSE);
				break;
			case IDC_EDITCPPCSRV:
				GPC.m_CONV3PCSRV.dwCP=::GetDlgItemInt(m_hWnd,ids[i],NULL,FALSE);
				break;
			}
		}
	}

	AfxGetApp()->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV3PCSRV_CP",GPC.m_CONV3PCSRV.dwCP);
	AfxGetApp()->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV3SRVPC_CP",GPC.m_CONV3SRVPC.dwCP);

	AfxGetApp()->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV3PCSRV_CONV",GPC.m_CONV3PCSRV.dwConv);
	AfxGetApp()->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV3SRVPC_CONV",GPC.m_CONV3SRVPC.dwConv);

	AfxGetApp()->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV3PCSRV_LANG",GPC.m_CONV3PCSRV.dwLang);
	AfxGetApp()->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV3SRVPC_LANG",GPC.m_CONV3SRVPC.dwLang);

	AfxGetApp()->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV3PCSRV_SUBLANG",GPC.m_CONV3PCSRV.dwSubLang);
	AfxGetApp()->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV3SRVPC_SUBLANG",GPC.m_CONV3SRVPC.dwSubLang);

	GPC.SetMBConv3(GPC.m_CONV3SRVPC.dwType,GPC.m_CONV3PCSRV.dwType);

	CDialog::OnOK();
}

void CDlgCodeco::OnBtncurrent()
{
	OnBtncurrent(m_tab.GetCurSel());
}

void CDlgCodeco::OnBtncurrent(int iType)
{
	int i;
	char *ppGPCtmp[]={GPC.chDosAnsi,GPC.chAnsiDos,GPC.chWideDosAnsi,GPC.chWideAnsiDos,GPC.chWideDosAnsi2,GPC.chWideAnsiDos2,};
	int j;
	for(j=0;(DWORD)j<nLists;j++)
		if (iType==j || iType==-1)
			for(i=0;i<256;i++)
				m_ConvArr[j][i]=ppGPCtmp[j][i];

	FillList(iType);
}

void CDlgCodeco::FillList(DWORD iType)
{
	CString tmpstr;
	const char *fmt_s="%3.3d   %2.2X   %s";
	const char *fmt_c="%3.3d   %2.2X   %c";
	int j;

	char ptmpDA[256],ptmpAD[256],ptmpWideDA[256],ptmpWideAD[256],ptmpWideDA2[256],ptmpWideAD2[256];
	FillDefaultDosAnsiArrays(ptmpAD,ptmpDA,ptmpWideAD,ptmpWideDA,ptmpWideAD2,ptmpWideDA2);
	char *pptmp[]={ptmpDA,ptmpAD,ptmpWideDA,ptmpWideAD,ptmpWideDA2,ptmpWideAD2,};
	char *ppGPCtmp[]={GPC.chDosAnsi,GPC.chAnsiDos,GPC.chWideDosAnsi,GPC.chWideAnsiDos,GPC.chWideDosAnsi2,GPC.chWideAnsiDos2,};

	DWORD i;
	for(i=0;i<nLists;i++)
		if (iType==i || iType==-1)
			for(j=0;j<256;j++)
			{
				if (ppGPCtmp[i][j]<33)
					tmpstr.Format(fmt_s,ppGPCtmp[i][j],ppGPCtmp[i][j],cArrBytesName[ppGPCtmp[i][j]]);
				else
					tmpstr.Format(fmt_c,ppGPCtmp[i][j],ppGPCtmp[i][j],ppGPCtmp[i][j]);
				mlists[i]->SetItemText(j,1,tmpstr);

				if (pptmp[i][j]<33)
					tmpstr.Format(fmt_s,pptmp[i][j],pptmp[i][j],cArrBytesName[pptmp[i][j]]);
				else
					tmpstr.Format(fmt_c,pptmp[i][j],pptmp[i][j],pptmp[i][j]);
				mlists[i]->SetItemText(j,2,tmpstr);

				if (m_ConvArr[i][j]<33)
					tmpstr.Format(fmt_s,m_ConvArr[i][j],m_ConvArr[i][j],cArrBytesName[m_ConvArr[i][j]]);
				else
					tmpstr.Format(fmt_c,m_ConvArr[i][j],m_ConvArr[i][j],m_ConvArr[i][j]);
				mlists[i]->SetItemText(j,3,tmpstr);
			}
}

void CDlgCodeco::FillDefaultDosAnsiArrays(char *iAnsiDos, char *iDosAnsi, char *iWideAnsiDos, char *iWideDosAnsi, char *iWideAnsiDos2, char *iWideDosAnsi2)
{
	int i;
	#ifdef BRIZ						
		char cDA[16]={168,184,170,186,175,191,161,162,176,149,183,171,185,164,166,174,};
	#else
		char cDA[16]={168,184,170,186,175,191,185,162,176,149,183,171,161,164,166,174,};
	#endif
	
	//	#ifndef BRIZ						
	//		iAnsiDos[247]=252;
	//	#endif
	//	#ifndef BRIZ						
	//		iAnsiDos[252]=247;
	//	#endif
	
	
	if (iAnsiDos)
	{
		for(i=0;i<256;i++)
			iAnsiDos[i]=(char)i;

		for(i=0;i<256;i++)
			if(i>=128 && i<=175) iAnsiDos[i+64]=(char)i;
				else
					if(i>=224 && i<=239) iAnsiDos[i+16]=(char)i;
					else
					if(i>=240 && i<=255)
						iAnsiDos[cDA[i-240]]=(char)i;
	}
	if (iDosAnsi)
	{
		for(i=0;i<256;i++)
			iDosAnsi[i]=(char)i;

		for(i=0;i<256;i++)
			if(i>=128 && i<=175) iDosAnsi[i]=(char)(i+64);
				else
					if(i>=224 && i<=239) iDosAnsi[i]=(char)(i+16);
					else
					if(i>=240 && i<=255)
						iDosAnsi[i]=cDA[i-240];
	}

	if (iWideAnsiDos)
		for(i=0;i<256;i++)
			iWideAnsiDos[i]=0;

	if (iWideDosAnsi)
		for(i=0;i<256;i++)
			iWideDosAnsi[i]=0;

	if (iWideAnsiDos2)
		for(i=0;i<256;i++)
			iWideAnsiDos2[i]=i;

	if (iWideDosAnsi2)
		for(i=0;i<256;i++)
			iWideDosAnsi2[i]=i;
}

BOOL CDlgCodeco::LoadDosAnsiArrays(char *iAnsiDos, char *iDosAnsi, char *iWideAnsiDos, char *iWideDosAnsi, char *iWideAnsiDos2, char *iWideDosAnsi2)
{
	BOOL ret=FALSE;

	FILE *tmp=fopen(CDlgCodeco::CodecoFileName,"rt");
	if (tmp)
	{
		char str[1000];
		while(fgets(str,990,tmp))
			if ((int)strlen(str)>3)
			{
				int c1=-1,c2=-1,c3=-1,c4=-1,c5=-1,c6=-1,num=-1;
				m_LastScanf=sscanf(str,"%d,%d,%d,%d,%d,%d,%d",&num,&c1,&c2,&c3,&c4,&c5,&c6);

				if (num>=0 && num<=255)
				{
					if(c1>=0 && c1<=255 && iAnsiDos)
					{
						iAnsiDos[num]=(char)c1;
						ret=TRUE;
					}
					if(c2>=0 && c2<=255 && iDosAnsi)
					{
						iDosAnsi[num]=(char)c2;
						ret=TRUE;
					}
					if(c3>=0 && c3<=255 && iWideAnsiDos)
					{
						iWideAnsiDos[num]=(char)c3;
						ret=TRUE;
					}
					if(c4>=0 && c4<=255 && iWideDosAnsi)
					{
						iWideDosAnsi[num]=(char)c4;
						ret=TRUE;
					}

					if(c5>=0 && c5<=255 && iWideAnsiDos2)
					{
						iWideAnsiDos2[num]=(char)c5;
						ret=TRUE;
					}
					if(c6>=0 && c6<=255 && iWideDosAnsi2)
					{
						iWideDosAnsi2[num]=(char)c6;
						ret=TRUE;
					}
				}
			}
		fclose(tmp);
	}
	return ret;
}

BOOL CDlgCodeco::SaveDosAnsiArrays(char *iAnsiDos, char *iDosAnsi, char *iWideAnsiDos, char *iWideDosAnsi, char *iWideAnsiDos2, char *iWideDosAnsi2)
{
	BOOL ret=FALSE;
	if (!iAnsiDos) iAnsiDos=GPC.chAnsiDos;
	if (!iDosAnsi) iDosAnsi=GPC.chDosAnsi;
	if (!iWideAnsiDos) iWideAnsiDos=GPC.chWideAnsiDos;
	if (!iWideDosAnsi) iWideDosAnsi=GPC.chWideDosAnsi;
	if (!iWideAnsiDos2) iWideAnsiDos2=GPC.chWideAnsiDos2;
	if (!iWideDosAnsi2) iWideDosAnsi2=GPC.chWideDosAnsi2;

	char tmpDA[256],tmpAD[256],tmpWideDA[256],tmpWideAD[256],tmpWideDA2[256],tmpWideAD2[256];
	FILE *tmp=NULL;

	DeleteFile(CDlgCodeco::CodecoFileName);

	FillDefaultDosAnsiArrays(tmpAD,tmpDA,tmpWideAD,tmpWideDA,tmpWideAD2,tmpWideDA2);

	int i;
	for(i=0;i<256;i++)
		if (iAnsiDos[i]!=tmpAD[i] || iDosAnsi[i]!=tmpDA[i] || iWideAnsiDos[i]!=tmpWideAD[i] || iWideDosAnsi[i]!=tmpWideDA[i] || iWideAnsiDos2[i]!=tmpWideAD2[i] || iWideDosAnsi2[i]!=tmpWideDA2[i])
		{
			if (tmp==NULL) tmp=fopen(CDlgCodeco::CodecoFileName,"wt");
			if (tmp)
			{
				fprintf(tmp,"%d,%d,%d,%d,%d,%d,%d\n",i,iAnsiDos[i],iDosAnsi[i],iWideAnsiDos[i],iWideDosAnsi[i],iWideAnsiDos2[i],iWideDosAnsi2[i]);
				ret=TRUE;
			}
		}

	if (tmp) fclose(tmp);
	return ret;
}

void CDlgCodeco::OnClickList(NMHDR* pNMHDR, LRESULT* pResult)
{
	DWORD m_Index;
	for(m_Index=0;m_Index<nLists && pNMHDR->hwndFrom!=mlists[m_Index]->m_hWnd;m_Index++);

	LPNMITEMACTIVATE nmItem=(LPNMITEMACTIVATE)pNMHDR;
	if (nmItem && m_Index<nLists)
	{
		if (nmItem->iItem<0)
		{
			LVHITTESTINFO ht={0};
			DWORD pos=::GetMessagePos();
			ht.pt.x=(int)(short)LOWORD(pos);
			ht.pt.y=(int)(short)HIWORD(pos);
			::ScreenToClient(mlists[m_Index]->m_hWnd,&(ht.pt));
			mlists[m_Index]->SubItemHitTest(&ht);
			nmItem->iItem=ht.iItem;
			nmItem->iSubItem=ht.iSubItem;
		}

		if (nmItem->iSubItem==3)
		{
			mlists[m_Index]->SetItemState(nmItem->iItem,LVIS_SELECTED,LVIS_SELECTED);
			mlists[m_Index]->Invalidate();
			CString tmps=mlists[m_Index]->GetItemText(nmItem->iItem,nmItem->iSubItem);

			CRect re,re2;
			mlists[m_Index]->GetSubItemRect(nmItem->iItem,nmItem->iSubItem,LVIR_BOUNDS,re);
			mlists[m_Index]->ClientToScreen(&re);
			mlists[m_Index]->GetClientRect(&re2);
			mlists[m_Index]->ClientToScreen(&re2);
			if (re2.right<re.right) re.right=re2.right;
			ScreenToClient(&re);

			re.bottom+=200;
			int fnd=mcompos[m_Index]->FindString(0,tmps);
			if (fnd!=CB_ERR) mcompos[m_Index]->SetCurSel(fnd);

			re.top-=4;
			mcompos[m_Index]->MoveWindow(&re);
			mcompos[m_Index]->SetDroppedWidth(180);
			mcompos[m_Index]->ModifyStyle(0,WS_VISIBLE,1);
			mcompos[m_Index]->BringWindowToTop();
			mcompos[m_Index]->ShowDropDown();
		}
	}
	*pResult = 0;
}

void CDlgCodeco::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	DWORD i;
	int j;
	for(i=0;i<nLists;i++)
	{
		mlists[i]->ShowWindow(SW_HIDE);
		mcompos[i]->ShowWindow(SW_HIDE);
	}
	DWORD ids[24]={
		IDC_COMBOSRVPC,IDC_COMBOPCSRV,IDC_COMBOWIDTHSRVPC,IDC_COMBOWIDTHPCSRV,
		IDC_COMBOLNGSRVPC,IDC_COMBOLNGPCSRV,IDC_COMBOSUBLNGSRVPC,IDC_COMBOSUBLNGPCSRV,
		IDC_COMBOCONVSRVPC,IDC_COMBOCONVPCSRV,IDC_COMBOCASESRVPC,IDC_COMBOCASEPCSRV,
		IDC_STATIC1,IDC_STATIC2,IDC_STATIC3,IDC_STATIC4,
		IDC_STATIC5,IDC_STATIC6,IDC_CHECKBRSRVPC,IDC_CHECKBRPCSRV,
		IDC_EDITCPPCSRV,IDC_EDITCPSRVPC,IDC_STATIC7,IDC_STATIC8,
	};
	if (m_tab.GetCurSel()==6)
	{
		for (j=0;j<24;j++)
			::ShowWindow(::GetDlgItem(m_hWnd,ids[j]),SW_SHOW);
	}
	else
	{
		for (j=0;j<24;j++)
			::ShowWindow(::GetDlgItem(m_hWnd,ids[j]),SW_HIDE);
		mlists[m_tab.GetCurSel()]->ShowWindow(SW_SHOW);
	}
	
	*pResult = 0;
}

void CDlgCodeco::OnCloseupCombo() 
{
	DWORD m_Index=m_tab.GetCurSel();

	mcompos[m_Index]->ShowWindow(SW_HIDE);
	int sel=mcompos[m_Index]->GetCurSel();
	if (sel!=CB_ERR)
	{
		CString txt;
		mcompos[m_Index]->GetLBText(sel,txt);
		POSITION pos = mlists[m_Index]->GetFirstSelectedItemPosition();
		if (pos)
		{
			int nItem = mlists[m_Index]->GetNextSelectedItem(pos);
			if (nItem>=0)
			{
				m_ConvArr[m_Index][nItem]=(char)atoi(txt);
				FillList(m_Index);
			}
		}
	}
}

