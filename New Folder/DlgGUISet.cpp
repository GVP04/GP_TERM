// DlgGUISet.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgGUISet.h"
#include "GPFontList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGUISet dialog


CDlgGUISet::CDlgGUISet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGUISet::IDD, pParent)
{
	m_LastScale=0;
	m_GPObjDialog=NULL;
	//{{AFX_DATA_INIT(CDlgGUISet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgGUISet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGUISet)
	DDX_Control(pDX, IDC_COMBOCHARCET, m_ComboCharset);
	DDX_Control(pDX, IDC_SLIDER1, m_ScaleSlider);
	DDX_Control(pDX, IDC_COMBOFONT, m_FontCombo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGUISet, CDialog)
	//{{AFX_MSG_MAP(CDlgGUISet)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, OnCustomdrawSliderScale)
	ON_CBN_SELCHANGE(IDC_COMBOCHARCET, OnSelchangeCombocharcet)
	ON_CBN_SELCHANGE(IDC_COMBOFONT, OnSelchangeCombofont)
	ON_BN_CLICKED(IDC_CHECKDEFAULT, OnCheckdefault)
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_EN_CHANGE(IDC_EDITITALIC, CreateTestDialogCh)
	ON_EN_CHANGE(IDC_EDITPOINTSIZE, CreateTestDialogCh)
	ON_EN_CHANGE(IDC_EDITWEIGHT, CreateTestDialogCh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGUISet message handlers

BOOL CDlgGUISet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int i;
	strcpy(m_Logfont.lfFaceName, GPC.m_GUISet.FontName);
	m_Logfont.lfCharSet=(unsigned char)GPC.m_GUISet.CharSet;

	for(i=0;i<18;i++)
	{
		int newitem=m_ComboCharset.AddString(clfCharSet[i]);
		if (newitem!=CB_ERR) 
		{
			if (ulfCharSet[i]==m_Logfont.lfCharSet) m_ComboCharset.SetCurSel(newitem);
			m_ComboCharset.SetItemData(newitem,ulfCharSet[i]);
		}
	}

	for(i=0;i<255;i++)
	{
		CString tmpCS;
		tmpCS.Format("%d", i);
		int newitem=m_ComboCharset.AddString(tmpCS);
		if (newitem!=CB_ERR) 
		{
			m_ComboCharset.SetItemData(newitem,i);
		}
	}

	m_ScaleSlider.SetRange(3,30);
	m_ScaleSlider.SetPos(GPC.m_GUISet.Scale/10);
	SetDlgItemInt(IDC_EDITPOINTSIZE,GPC.m_GUISet.PointSize);
	SetDlgItemInt(IDC_EDITWEIGHT,m_Logfont.lfWeight=GPC.m_GUISet.Weight);
	SetDlgItemInt(IDC_EDITITALIC,m_Logfont.lfItalic=(unsigned char)GPC.m_GUISet.Italic);
	CheckDlgButton(IDC_CHECKDEFAULT,GPC.m_GUISet.UseDefault);
	FillFontCombo();

	CreateTestDialog();
	return TRUE;
}

void CDlgGUISet::OnCancel() 
{
	CDialog::OnCancel();
}

void CDlgGUISet::OnOK() 
{
	CWinApp *app=AfxGetApp();
	m_FontCombo.GetWindowText(GPC.m_GUISet.FontName);
	app->WriteProfileString("GUISET", "m_FontName",GPC.m_GUISet.FontName);
	app->WriteProfileInt("GUISET", "m_CurFontCharSet",GPC.m_GUISet.CharSet=m_Logfont.lfCharSet);
	app->WriteProfileInt("GUISET", "Scale",GPC.m_GUISet.Scale=m_ScaleSlider.GetPos()*10);

	app->WriteProfileInt("GUISET", "POINTSIZE",GPC.m_GUISet.PointSize=GetDlgItemInt(IDC_EDITPOINTSIZE));
	app->WriteProfileInt("GUISET", "WEIGHT",GPC.m_GUISet.Weight=GetDlgItemInt(IDC_EDITWEIGHT));
	app->WriteProfileInt("GUISET", "ITALIC",GPC.m_GUISet.Italic=GetDlgItemInt(IDC_EDITITALIC));
	app->WriteProfileInt("GUISET", "CHECKDEFAULT",GPC.m_GUISet.UseDefault=IsDlgButtonChecked(IDC_CHECKDEFAULT));

	CDialog::OnOK();
}

void CDlgGUISet::OnCustomdrawSliderScale(NMHDR* pNMHDR, LRESULT* pResult)
{
	DWORD tmpScale=m_LastScale;
	SetDlgItemInt(IDC_STATIC1,tmpScale=m_ScaleSlider.GetPos()*10);
	*pResult = 0;
	if (m_LastScale!=tmpScale) CreateTestDialog();
	m_LastScale=tmpScale;
}

void CDlgGUISet::FillFontCombo()
{
	LOGFONT mlf;
	memset(&mlf,0,sizeof(mlf));
	mlf.lfCharSet=m_Logfont.lfCharSet;
	CGPFontList fl(mlf);
	fl.FillComboBox(m_FontCombo.m_hWnd,GPFL_CLEAR|GPFL_NOSCRIPT,0);
	int pos=m_FontCombo.FindStringExact(0,m_Logfont.lfFaceName);
	if (pos>=0) m_FontCombo.SetCurSel(pos);
}

void CDlgGUISet::OnSelchangeCombocharcet() 
{
	int cursel=m_ComboCharset.GetCurSel();
	if (cursel!=CB_ERR) m_Logfont.lfCharSet=(unsigned char)m_ComboCharset.GetItemData(cursel);
	else m_Logfont.lfCharSet=DEFAULT_CHARSET;
	FillFontCombo();
	if (!IsDlgButtonChecked(IDC_CHECKDEFAULT))	CreateTestDialog();
}

void CDlgGUISet::OnSelchangeCombofont() 
{
	m_FontCombo.GetWindowText(m_Logfont.lfFaceName,LF_FACESIZE-1);
	if (!IsDlgButtonChecked(IDC_CHECKDEFAULT))	CreateTestDialog();
}

void CDlgGUISet::CreateTestDialogCh()
{
	if (!IsDlgButtonChecked(IDC_CHECKDEFAULT))	CreateTestDialog();
}
void CDlgGUISet::CreateTestDialog()
{
	HWND focusHWND=::GetFocus();
	DeleteTestDialog();
	GPGUISET m_tmpGUISet;
	LOGFONT m_tmpLogfont;
	GetObject(GetStockObject(SYSTEM_FONT), sizeof (m_tmpLogfont), &m_tmpLogfont);

	m_tmpGUISet.UseDefault=IsDlgButtonChecked(IDC_CHECKDEFAULT);

	m_FontCombo.GetWindowText(m_tmpGUISet.FontName);
	if (m_tmpGUISet.UseDefault) m_tmpGUISet.FontName="MS Sans Serif";//m_tmpLogfont.lfFaceName;

	m_tmpGUISet.CharSet=m_Logfont.lfCharSet;
	if (m_tmpGUISet.UseDefault) m_tmpGUISet.CharSet=m_tmpLogfont.lfCharSet;

	m_tmpGUISet.Scale=m_ScaleSlider.GetPos()*10;

	m_tmpGUISet.PointSize=GetDlgItemInt(IDC_EDITPOINTSIZE);
	if (m_tmpGUISet.UseDefault) m_tmpGUISet.PointSize=8;

	m_tmpGUISet.Weight=GetDlgItemInt(IDC_EDITWEIGHT);
	if (m_tmpGUISet.UseDefault) m_tmpGUISet.Weight=400;
	m_tmpGUISet.Italic=GetDlgItemInt(IDC_EDITITALIC);
	if (m_tmpGUISet.UseDefault) m_tmpGUISet.Italic=0;


	CRect iRe;
	GetWindowRect(&iRe);
	iRe.left=iRe.right+5;
	iRe.right=iRe.left+250;
	iRe.bottom=iRe.top+200;

	DWORD tmpScale=m_tmpGUISet.Scale;
	char tmpStyle[1000];
	sprintf(tmpStyle,"SCALE=%d;",m_tmpGUISet.Scale);
	strcat(tmpStyle,"TEXT=Dialog Example;STYLE=WS_CAPTION|WS_BORDER|WS_POPUPWINDOW|DS_ABSALIGN|DS_SETFONT|WS_EX_CONTROLPARENT|WS_EX_WINDOWEDGE;TOOLTIP=Tooltip sample;");
	m_GPObjDialog=new GPObjDialog(0,tmpStyle,this);
	if (m_GPObjDialog)
	{
		HGLOBAL m_HGTemplate = GlobalAlloc(GMEM_ZEROINIT, 256);
		GPDLGTEMPLATEEX *lpdt;
		lpdt = (GPDLGTEMPLATEEX *)GlobalLock(m_HGTemplate);

		lpdt->style =WS_CAPTION|WS_BORDER|WS_POPUPWINDOW|DS_ABSALIGN|DS_SETFONT|DS_3DLOOK;
		lpdt->exStyle = WS_EX_CONTROLPARENT|WS_EX_WINDOWEDGE;
		lpdt->cDlgItems = 0;  // number of controls

		lpdt->dlgVer=1;
		lpdt->signature=0xFFFF;
		lpdt->helpID =0;
		lpdt->menu=0;
		lpdt->windowClass=0;
		lpdt->title[0]=0;
		MultiByteToWideChar (CP_ACP, 0,m_tmpGUISet.FontName , -1, lpdt->typeface, 32);

		lpdt->pointsize =m_tmpGUISet.PointSize;
		lpdt->pointsize =(unsigned short)((lpdt->pointsize * tmpScale)/100);

		lpdt->x  =(short)(iRe.left*697/1046);
		lpdt->y =(short)(iRe.top*450/731);
		lpdt->cx = (short)(iRe.Width()*697/1046);
		lpdt->cy = (short)(iRe.Height()*450/731);

		lpdt->weight  = (unsigned short)m_tmpGUISet.Weight;
		lpdt->italic  = m_tmpGUISet.Italic;
		lpdt->charset = (unsigned char)m_tmpGUISet.CharSet;

		GlobalUnlock(m_HGTemplate);
		m_GPObjDialog->CreateIndirect ((GPDLGTEMPLATEEX *)m_HGTemplate);
		CRect reReq;
		m_GPObjDialog->GetWindowRect(&reReq);
		m_GPObjDialog->MoveWindow(iRe.left,iRe.top,iRe.Width()*m_tmpGUISet.Scale/100,iRe.Height()*m_tmpGUISet.Scale/100);
		CRect reCur;
		m_GPObjDialog->GetWindowRect(&reCur);

		sprintf(tmpStyle,"STYLE=WS_VISIBLE;TEXT=Initial size 250x200;RECT=5,1,240,17;");
		m_GPObjDialog->CreateUnit(GPUnit::UT_STATIC,1,tmpStyle,m_GPObjDialog->m_hWnd);

		sprintf(tmpStyle,"STYLE=WS_VISIBLE;TEXT=Current size %dx%d;RECT=5,19,240,35;",reCur.Width(),reCur.Height());
		m_GPObjDialog->CreateUnit(GPUnit::UT_STATIC,2,tmpStyle,m_GPObjDialog->m_hWnd);
		sprintf(tmpStyle,"STYLE=WS_VISIBLE;TEXT=Required by font %dx%d;RECT=5,37,240,53;",reReq.Width(),reReq.Height());
		m_GPObjDialog->CreateUnit(GPUnit::UT_STATIC,3,tmpStyle,m_GPObjDialog->m_hWnd);

		sprintf(tmpStyle,"STYLE=WS_VISIBLE|WS_EX_CLIENTEDGE;TEXT=Type any example here;RECT=2,57,240,75;");
		m_GPObjDialog->CreateUnit(GPUnit::UT_EDIT,4,tmpStyle,m_GPObjDialog->m_hWnd);

		sprintf(tmpStyle,"STYLE=WS_VISIBLE;TEXT=Button;RECT=5,80,120,100;");
		m_GPObjDialog->CreateUnit(GPUnit::UT_BUTTON,5,tmpStyle,m_GPObjDialog->m_hWnd);

		m_GPObjDialog->ShowWindow(SW_SHOW);
		EnableWindow();
		GlobalFree(m_HGTemplate);
		MoveExampleDlg();
	}
	::SetFocus(focusHWND);
}

void CDlgGUISet::DeleteTestDialog()
{
	if (m_GPObjDialog)
	{
		if (m_GPObjDialog->m_hWnd) m_GPObjDialog->DestroyWindow();
		delete m_GPObjDialog;
		m_GPObjDialog=NULL;
	}
}

BOOL CDlgGUISet::DestroyWindow() 
{
	DeleteTestDialog();
	
	return CDialog::DestroyWindow();
}

void CDlgGUISet::OnCheckdefault() 
{
	CreateTestDialog();
}

void CDlgGUISet::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	MoveExampleDlg();
}

void CDlgGUISet::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	MoveExampleDlg();
}

void CDlgGUISet::MoveExampleDlg()
{
	if (m_GPObjDialog && m_GPObjDialog->m_hWnd)
	{
		RECT re={0};
		RECT reP={0};
		GetWindowRect(&reP);
		m_GPObjDialog->GetWindowRect(&re);
		re.right=reP.right+5+re.right-re.left;
		re.left=reP.right+5;
		re.bottom=reP.top+re.bottom-re.top;
		re.top=reP.top;
		m_GPObjDialog->MoveWindow(&re);
	}
}

