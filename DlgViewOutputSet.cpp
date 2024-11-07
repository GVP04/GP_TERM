// DlgViewOutputSet.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgViewOutputSet.h"
#include "Scintilla\Scintilla.h"
#include "Scintilla\SciLexer.h"
#include "DlgEditKeywords.h"
#include "DlgKeyEditor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgViewOutputSet dialog


CDlgViewOutputSet::CDlgViewOutputSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewOutputSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgViewOutputSet)
	//}}AFX_DATA_INIT
	m_dwTabSize=8;
	m_dwIndentSize=0;
	m_dwLowSymbolMask=0xFFFFFFFF;
	m_dwOutputSet=0;
	m_Lock=FALSE;
	m_nMaxOutputLen=NULL;
	m_nOutputLenDecr=NULL;
	m_DlgViewOutputPtr=NULL;
	m_CurLexer=78;
	DlgAutoSize=NULL;
}

CDlgViewOutputSet::~CDlgViewOutputSet()
{
	if (DlgAutoSize)
		delete DlgAutoSize;
	DlgAutoSize=NULL;
}

void CDlgViewOutputSet::OnDestroy()
{
	if (DlgAutoSize)
		delete DlgAutoSize;
	DlgAutoSize=NULL;
	CDialog::OnDestroy();
}

void CDlgViewOutputSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgViewOutputSet)
	DDX_Control(pDX, IDC_COMBOINDENTATION, m_ComboIndentation);
	DDX_Control(pDX, IDC_COMBOTAB, m_ComboTab);
	DDX_Control(pDX, IDC_COMBOLEXER, m_ComboLexer);
	DDX_Control(pDX, IDC_LISTVIEWSET, m_lcListViewSet);
	DDX_Control(pDX, IDC_LISTSYMBOL, m_lcListSymbol);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgViewOutputSet, CDialog)
	//{{AFX_MSG_MAP(CDlgViewOutputSet)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTSYMBOL, OnItemchangedListsymbol)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTVIEWSET, OnItemchangedListviewset)
	ON_EN_CHANGE(IDC_EDITMAXLEN, OnChangeEditmaxlen)
	ON_EN_CHANGE(IDC_EDITMAXLEN2, OnChangeEditmaxlen2)
	ON_BN_CLICKED(IDC_BTNFONTCOLOR, OnBtnfontcolor)
	ON_BN_CLICKED(IDC_BUTTONKEYWORDS, OnButtonkeywords)
	ON_CBN_SELCHANGE(IDC_COMBOLEXER, OnSelchangeCombolexer)
	ON_BN_CLICKED(IDC_BUTTONBROWSE, OnButtonbrowse)
	ON_EN_CHANGE(IDC_EDITSRVFILE, OnChangeEditsrvfile)
	ON_EN_CHANGE(IDC_EDITSRVFILE2, OnChangeEditsrvItem)
	ON_EN_CHANGE(IDC_EDITCLFILE, OnChangeEditclfile)
	ON_BN_CLICKED(IDC_BUTTONEDITKEY, OnButtoneditkey)
	ON_CBN_SELCHANGE(IDC_COMBOTAB, OnSelchangeCombotab)
	ON_CBN_SELCHANGE(IDC_COMBOINDENTATION, OnSelchangeComboindentation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgViewOutputSet message handlers

BOOL CDlgViewOutputSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	CWinApp *AApp=AfxGetApp();
	m_Lock=TRUE;
	m_DlgViewOutputPtr->m_CDlgViewOutputSetPtr=this;
	m_dwLowSymbolMask=AApp->GetProfileInt("SEP_OUTPUT_SET", "CHARFILTER",0xFFFFFE7E);
	m_dwOutputSet=AApp->GetProfileInt("SEP_OUTPUT_SET", "OUTPUT_SET",0xE79F);
	m_CurLexer=AfxGetApp()->GetProfileInt("SEP_OUTPUT_SET", "m_CurLexer",78);




	m_lcListViewSet.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);
#ifdef RUS
	m_lcListViewSet.InsertColumn(0,"Наименование",LVCFMT_LEFT,160,0);
#else
	m_lcListViewSet.InsertColumn(0,"Name",LVCFMT_LEFT,160,0);
#endif

	m_lcListSymbol.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);
#ifdef RUS
	m_lcListSymbol.InsertColumn(0,"Ключ",LVCFMT_LEFT,50,0);
	m_lcListSymbol.InsertColumn(1,"Код",LVCFMT_LEFT,50,0);
#else
	m_lcListSymbol.InsertColumn(0,"Name",LVCFMT_LEFT,50,0);
	m_lcListSymbol.InsertColumn(1,"Code",LVCFMT_LEFT,50,0);
#endif

	char * arrNM[32]={
		"NUL","SOH","STX","ETX","EOT","ENQ","ACK","BEL",
		"BS","HT","LF","VT","FF","CR","SO","SI",
		"DLE","DC1","DC2","DC3","DC4","NAK","SYN","ETB",
		"CAN","EM","SUB","ESC","FS","GS","RS","US",
	};

	int i;
	for(i=0;i<32;i++)
	{
		int nItem=m_lcListSymbol.InsertItem(i,arrNM[i]);
		char tmps[100];
		sprintf(tmps,"%2.2d %2.2X",i,i);
		m_lcListSymbol.SetItemText(nItem,1,tmps);
	}


	char * arrNM2[32]={
#ifdef RUS
		"Разрешить вывод","Не редактировать вывод","AutoScroll","Нумерация строк","Пробельные символы","Показывать EOL","Показывать всю строку","Цветовая подсветка",
		"Auto Load/Save","Прямой ввод","Блокировать клавиши","Дублировать прямой ввод","Use Tabs","Line Indentation","Indentation Guides","Backspace Unindent",
		"","","","","","","","",
		"","","","","","","","",
#else
		"Enable Output","ReadOnly","AutoScroll","Line Numbers","White Space","View EOL","Line wrapping","Colorise",
		"Auto Load/Save","Direct input","Lock Keys","Duplicate Direct Input","Use Tabs","Line Indentation","Indentation Guides","Backspace Unindent",
		"","","","","","","","",
		"","","","","","","","",
#endif
	};


	for(i=0;i<16;i++)
	{
		m_lcListViewSet.InsertItem(i,arrNM2[i]);
	}

	for(i=0;*GPScintilla::cArrLexer[i];i++)
	{
		int nItem=m_ComboLexer.AddString( GPScintilla::cArrLexer[i]);
		m_ComboLexer.SetItemData(nItem,GPScintilla::uArrLexer[i]);
		if (m_CurLexer==GPScintilla::uArrLexer[i])
			m_ComboLexer.SetCurSel(nItem);

	}

	UpdateCtrls();


	DlgAutoSize=new GP_AutoSizing;
	DlgAutoSize->AddSetMain(this->m_hWnd);
	DlgAutoSize->AddWnd(m_lcListSymbol.m_hWnd,m_hWnd,"NNEN");
	DlgAutoSize->AddWnd(m_lcListViewSet.m_hWnd,m_hWnd,"NNEN");

	if ((m_dwOutputSet&CDVOS_AUTOLOADSAVE)==CDVOS_AUTOLOADSAVE)
	{
		m_DlgViewOutputPtr->SendMessage(WM_COMMAND,SCCMND_LOADCLIENT,NULL);
		COleDateTime tm=COleDateTime::GetCurrentTime();
		CString tmp1=tm.Format("==================== SESSION %#c ====================");
		char buff[500];
		char *pos=buff;
		const char *pos2=tmp1;
		while(*(pos2++) && pos-buff<480) *(pos++)='=';
		*pos=0;
		m_DlgViewOutputPtr->m_Editor->AppendString("",0);
		m_DlgViewOutputPtr->m_Editor->AppendString(buff,0);
		m_DlgViewOutputPtr->m_Editor->AppendString(tmp1,0);
		m_DlgViewOutputPtr->m_Editor->AppendString(buff,0);
	}
	SetDlgItemText(IDC_EDITCLFILE,m_DlgViewOutputPtr->m_Editor->m_csDefClFileName);
	SetDlgItemText(IDC_EDITSRVFILE,m_DlgViewOutputPtr->m_Editor->m_csDefSrvFileName);
	SetDlgItemText(IDC_EDITSRVFILE2,m_DlgViewOutputPtr->m_Editor->m_csDefSrvItemName);


	m_Lock=FALSE;

	m_ComboIndentation.ResetContent();
	m_ComboTab.ResetContent();

	for(i=0;i<16;i++)
	{
		char ctmps[20];
		sprintf(ctmps,"%d",i);
		m_ComboIndentation.AddString(ctmps);
		sprintf(ctmps,"%d",i+1);
		m_ComboTab.AddString(ctmps);
	}
	m_dwTabSize=AfxGetApp()->GetProfileInt("SEP_OUTPUT_SET", "TABSIZE",0x8);
	m_ComboTab.SetCurSel(m_dwTabSize-1);
	OnSelchangeCombotab();
	m_dwIndentSize=AfxGetApp()->GetProfileInt("SEP_OUTPUT_SET", "INDENTSIZE",0x0);
	m_ComboIndentation.SetCurSel(m_dwIndentSize);
	OnSelchangeComboindentation();

	UpdateOutputSettings(-1);

	return TRUE;
}

void CDlgViewOutputSet::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if (DlgAutoSize)
		try{DlgAutoSize->UpdateSize();}catch(...){GPC.m_ErrReport.GPWriteErrorLog("CDlgViewOutputSet", "OnSize","");}
}

void CDlgViewOutputSet::OnItemchangedListsymbol(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (m_Lock==FALSE)
	{
		NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

		if (((pNMListView->uNewState^pNMListView->uOldState)&0x3000)!=0)
		{
			if ((pNMListView->uNewState&0x1000))
				m_dwLowSymbolMask&=(0xFFFFFFFFF^GPCurrent::uArrPower[(pNMListView->iItem)%32]);
			else
				m_dwLowSymbolMask|=GPCurrent::uArrPower[(pNMListView->iItem)%32];
		}
		AfxGetApp()->WriteProfileInt("SEP_OUTPUT_SET", "CHARFILTER",m_dwLowSymbolMask);
	}

	*pResult = 0;
}

void CDlgViewOutputSet::OnItemchangedListviewset(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (m_Lock==FALSE)
	{
		NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

		if (((pNMListView->uNewState^pNMListView->uOldState)&0x3000)!=0)
		{
			if ((pNMListView->uNewState&0x1000))
				m_dwOutputSet&=(0xFFFFFFFFF^GPCurrent::uArrPower[(pNMListView->iItem)%32]);
			else
				m_dwOutputSet|=GPCurrent::uArrPower[(pNMListView->iItem)%32];
		}
		UpdateOutputSettings(pNMListView->iItem);
		AfxGetApp()->WriteProfileInt("SEP_OUTPUT_SET", "OUTPUT_SET",m_dwOutputSet);
	}
	*pResult = 0;
}

void CDlgViewOutputSet::UpdateOutputSettings(UINT iType)
{
	UINT istart=iType;
	UINT iend=iType+1;
	if (iType>31) istart=0,iend=32;
	UINT i;
	for(i=istart;i<iend;i++)
		switch(i)
		{
		case 0://Enable Outbut
			break;
		case 1://ReadOnly
			if (m_DlgViewOutputPtr && m_DlgViewOutputPtr->m_Editor)
				m_DlgViewOutputPtr->m_Editor->ScMethod(SCI_SETREADONLY,(m_dwOutputSet&CDVOS_NOREADONLYOUTPUT)==CDVOS_NOREADONLYOUTPUT,0);
			break;
		case 2://AutoScroll
			if (m_DlgViewOutputPtr)
				if ((m_dwOutputSet&CDVOS_AUTOSCROLL)==CDVOS_AUTOSCROLL)
					m_DlgViewOutputPtr->m_uSelectionFlag|=0x1;
				else
					m_DlgViewOutputPtr->m_uSelectionFlag&=(0xFFFFFFFF^0x1);
			break;
		case 3://Line Numbers
			if (m_DlgViewOutputPtr && m_DlgViewOutputPtr->m_Editor)
				m_DlgViewOutputPtr->m_Editor->ScMethod(SCI_SETMARGINWIDTHN,0,((m_dwOutputSet&CDVOS_LINENUMBERS)==CDVOS_LINENUMBERS)?40:0);
			break;
		case 4://White Space
			if (m_DlgViewOutputPtr && m_DlgViewOutputPtr->m_Editor)
				m_DlgViewOutputPtr->m_Editor->ScMethod(SCI_SETVIEWWS,(m_dwOutputSet&CDVOS_VIEWWHITESPACE)==CDVOS_VIEWWHITESPACE?1:0,0);
			break;
		case 5://View EOL
			if (m_DlgViewOutputPtr && m_DlgViewOutputPtr->m_Editor)
				m_DlgViewOutputPtr->m_Editor->ScMethod(SCI_SETVIEWEOL,(m_dwOutputSet&CDVOS_VIEWEOL)==CDVOS_VIEWEOL,0);
			break;
		case 6://Line wrapping
			if (m_DlgViewOutputPtr && m_DlgViewOutputPtr->m_Editor)
				m_DlgViewOutputPtr->m_Editor->ScMethod(SCI_SETWRAPMODE,(m_dwOutputSet&CDVOS_LINEWRAPPING)==CDVOS_LINEWRAPPING?1:0,0);
			break;
		case 7://COLORISE LEX
			OnSelchangeCombolexer();
		case 8://CDVOS_AUTOLOADSAVE
			if (m_DlgViewOutputPtr)
				m_DlgViewOutputPtr->m_Editor->m_AutoSaveFlag=
					((m_dwOutputSet&CDVOS_AUTOLOADSAVE)==CDVOS_AUTOLOADSAVE)?1:0;
			break;
		case 9://CDVOS_DIRECTINPUT
			if (m_DlgViewOutputPtr)
			{
				m_DlgViewOutputPtr->m_Editor->m_DirectInputFlag=
					((m_dwOutputSet&CDVOS_DIRECTINPUT)==CDVOS_DIRECTINPUT)?1:0;
				m_DlgViewOutputPtr->UpdateTB();
			}
			break;
		case 10://CDVOS_LOCKKEYS
			if (m_DlgViewOutputPtr)
				m_DlgViewOutputPtr->m_Editor->m_LockKeysFlag=
					((m_dwOutputSet&CDVOS_LOCKKEYS)==CDVOS_LOCKKEYS)?1:0;
			break;
		case 11://CDVOS_DUPLICATEINPUT
			if (m_DlgViewOutputPtr)
				m_DlgViewOutputPtr->m_Editor->m_DuplicateInputFlag=
					((m_dwOutputSet&CDVOS_DUPLICATEINPUT)==CDVOS_DUPLICATEINPUT)?1:0;
			break;
		case 12://CDVOS_USETABS
			if (m_DlgViewOutputPtr && m_DlgViewOutputPtr->m_Editor)
				m_DlgViewOutputPtr->m_Editor->ScMethod(SCI_SETUSETABS,(m_dwOutputSet&CDVOS_USETABS)==CDVOS_USETABS?1:0,0);
			break;
		case 13://CDVOS_LINEINDENTATION
			if (m_DlgViewOutputPtr && m_DlgViewOutputPtr->m_Editor)
				m_DlgViewOutputPtr->m_Editor->ScMethod(SCI_SETTABINDENTS,(m_dwOutputSet&CDVOS_LINEINDENTATION)==CDVOS_LINEINDENTATION?1:0,0);
			break;
		case 14://CDVOS_INDENTATIONGUIDES
			if (m_DlgViewOutputPtr && m_DlgViewOutputPtr->m_Editor)
				m_DlgViewOutputPtr->m_Editor->ScMethod(SCI_SETINDENTATIONGUIDES,(m_dwOutputSet&CDVOS_INDENTATIONGUIDES)==CDVOS_INDENTATIONGUIDES?1:0,0);
			break;
		case 15://CDVOS_BAKSPACEUNINDENT
			if (m_DlgViewOutputPtr && m_DlgViewOutputPtr->m_Editor)
				m_DlgViewOutputPtr->m_Editor->ScMethod(SCI_SETBACKSPACEUNINDENTS,(m_dwOutputSet&CDVOS_BAKSPACEUNINDENT)==CDVOS_BAKSPACEUNINDENT?1:0,0);
			break;
		}
}

DWORD CDlgViewOutputSet::GetCharMask()
{
	return m_dwLowSymbolMask;
}

DWORD CDlgViewOutputSet::SetCharMask(DWORD idwMask)
{
	DWORD ret=m_dwLowSymbolMask;
	m_dwLowSymbolMask=idwMask;
	return ret;
}

void CDlgViewOutputSet::UpdateCtrls()
{
	DWORD tmpMsk=1;
	int i;
	for(i=0;i<32;i++)
	{
		int cc=m_lcListSymbol.GetCheck(i);
		if ((cc==0 && (tmpMsk&m_dwLowSymbolMask)) || ((tmpMsk&m_dwLowSymbolMask)==0 && cc))
			m_lcListSymbol.SetCheck(i,(tmpMsk&m_dwLowSymbolMask)!=0);
		tmpMsk+=tmpMsk;
	}

	tmpMsk=1;
	for(i=0;i<32;i++)
	{
		int cc=m_lcListViewSet.GetCheck(i);
		if ((cc==0 && (tmpMsk&m_dwOutputSet)) || ((tmpMsk&m_dwOutputSet)==0 && cc))
			m_lcListViewSet.SetCheck(i,(tmpMsk&m_dwOutputSet)!=0);
		tmpMsk+=tmpMsk;
	}
}

BOOL CDlgViewOutputSet::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if ((wParam==1 || wParam==2) && lParam==0) return TRUE;

	return CDialog::OnCommand(wParam, lParam);
}


void CDlgViewOutputSet::SetMinMaxLen(UINT &uMax, UINT &uPercent)
{
	m_nMaxOutputLen=&uMax;
	m_nOutputLenDecr=&uPercent;
	SetDlgItemInt(IDC_EDITMAXLEN,uMax,FALSE);

	if (uPercent>100) uPercent=100;
	SetDlgItemInt(IDC_EDITMAXLEN2,uPercent,FALSE);
}

void CDlgViewOutputSet::OnChangeEditmaxlen()
{
	UINT tmp=GetDlgItemInt(IDC_EDITMAXLEN,NULL,FALSE);
	if (tmp<1024)
	{
		tmp=1024;
		SetDlgItemInt(IDC_EDITMAXLEN,tmp,FALSE);
	}
	if (m_nMaxOutputLen) *m_nMaxOutputLen=tmp;
	AfxGetApp()->WriteProfileInt("SEP_OUTPUT_SET", "m_nMaxOutputLen",tmp);
}

void CDlgViewOutputSet::OnChangeEditmaxlen2()
{
	UINT tmp=GetDlgItemInt(IDC_EDITMAXLEN2,NULL,FALSE);
	if (tmp>100)
	{
		tmp=100;
		SetDlgItemInt(IDC_EDITMAXLEN2,tmp,FALSE);
	}
	if (m_nOutputLenDecr) *m_nOutputLenDecr=tmp;
	AfxGetApp()->WriteProfileInt("SEP_OUTPUT_SET", "m_nOutputLenDecr",tmp);
}


void CDlgViewOutputSet::OnBtnfontcolor()
{
	FontColorDlg(0);
}

#include "DlgEditorColor.h"

UINT CDlgViewOutputSet::FontColorDlg(UINT iType)
{
	UINT ret=IDCANCEL;
	if (m_DlgViewOutputPtr && m_DlgViewOutputPtr->m_Editor && m_DlgViewOutputPtr->m_Editor->m_hWnd && iType==0)
	{
		CDlgEditorColor dlg;
		dlg.SetEditor((GPScintilla *)m_DlgViewOutputPtr->m_Editor);
		dlg.LoadColors(m_CurLexer);

		if ((ret=dlg.DoModal())==IDOK)
		{
			dlg.SaveColors(m_CurLexer);
			m_DlgViewOutputPtr->m_Editor->LoadColors(m_CurLexer);
		}
	}

	return ret;
}

LRESULT CDlgViewOutputSet::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	return CDialog::WindowProc(message, wParam, lParam);
}

void CDlgViewOutputSet::OnButtonkeywords()
{
	CDlgEditKeywords dlg;
	dlg.SetLexerType(m_CurLexer);
	if (dlg.DoModal()==IDOK && m_DlgViewOutputPtr && m_DlgViewOutputPtr->m_Editor)
		m_DlgViewOutputPtr->m_Editor->LoadKeywords(m_CurLexer);
}

void CDlgViewOutputSet::OnSelchangeCombolexer()
{
	int cursel=m_ComboLexer.GetCurSel();
	if (cursel!=CB_ERR)
	{
		m_CurLexer=m_ComboLexer.GetItemData(cursel);
		AfxGetApp()->WriteProfileInt("SEP_OUTPUT_SET", "m_CurLexer",m_CurLexer);
		if (m_DlgViewOutputPtr && (m_dwOutputSet&CDVOS_COLORISELEX)==CDVOS_COLORISELEX)
		{
			m_DlgViewOutputPtr->m_Editor->LoadKeywords(m_CurLexer);

			if ((m_dwOutputSet&CDVOS_COLORISELEX)==CDVOS_COLORISELEX)
			{
				m_DlgViewOutputPtr->m_Editor->ScMethod(SCI_SETLEXER,m_CurLexer,0);
				m_DlgViewOutputPtr->m_Editor->LoadColors(m_CurLexer);
				m_DlgViewOutputPtr->m_Editor->ScMethod(SCI_COLOURISE,0,-1);
			}
		}
	}
	if (m_DlgViewOutputPtr && m_DlgViewOutputPtr->m_Editor && (m_dwOutputSet&CDVOS_COLORISELEX)!=CDVOS_COLORISELEX)
	{
		m_DlgViewOutputPtr->m_Editor->ScMethod(SCI_SETLEXER,SCLEX_NULL,0);
		m_DlgViewOutputPtr->m_Editor->ScMethod(SCI_COLOURISE,0,-1);
	}
}

void CDlgViewOutputSet::OnButtonbrowse()
{
	OPENFILENAME opf={0};
	#ifdef W_95
		opf.lStructSize=OPENFILENAME_SIZE_VERSION_400;
	#else
		#ifdef W_NT
			opf.lStructSize=OPENFILENAME_SIZE_VERSION_400;
		#else
			opf.lStructSize=sizeof(OPENFILENAME);
		#endif
	#endif
	opf.hwndOwner=m_hWnd;
	opf.lpstrFile = new char [1000];
	strcpy(opf.lpstrFile,m_DlgViewOutputPtr->m_Editor->m_csDefClFileName);
	opf.nMaxFile =4900;
	opf.Flags =OFN_DONTADDTORECENT|OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_NOCHANGEDIR|OFN_PATHMUSTEXIST|OFN_NOCHANGEDIR|OFN_SHOWHELP;

	if (GetSaveFileName(&opf))
	{
		m_DlgViewOutputPtr->m_Editor->m_csDefClFileName=opf.lpstrFile;
		SetDlgItemText(IDC_EDITCLFILE,m_DlgViewOutputPtr->m_Editor->m_csDefClFileName);
	}
	delete[] opf.lpstrFile;
}

void CDlgViewOutputSet::OnChangeEditsrvfile()
{
	if (m_DlgViewOutputPtr && !m_Lock)
		GetDlgItemText(IDC_EDITSRVFILE,m_DlgViewOutputPtr->m_Editor->m_csDefSrvFileName);
}

void CDlgViewOutputSet::OnChangeEditsrvItem()
{
	if (m_DlgViewOutputPtr && !m_Lock)
		GetDlgItemText(IDC_EDITSRVFILE2,m_DlgViewOutputPtr->m_Editor->m_csDefSrvItemName);
}

void CDlgViewOutputSet::OnChangeEditclfile()
{
	if (m_DlgViewOutputPtr && !m_Lock)
		GetDlgItemText(IDC_EDITCLFILE,m_DlgViewOutputPtr->m_Editor->m_csDefClFileName);
}

void CDlgViewOutputSet::OnButtoneditkey()
{
	CDlgKeyEditor dlg;
	dlg.m_FileName=m_DlgViewOutputPtr->m_Editor->m_FileNameLK;
	if (dlg.DoModal()==IDOK)
		m_DlgViewOutputPtr->m_Editor->LoadLockKeys();
}

void CDlgViewOutputSet::OnSelchangeCombotab()
{
	int sel=m_ComboTab.GetCurSel();
	if (sel!=CB_ERR) m_dwTabSize=sel+1;
	AfxGetApp()->WriteProfileInt("SEP_OUTPUT_SET", "TABSIZE",m_dwTabSize);
	if (m_DlgViewOutputPtr && m_DlgViewOutputPtr->m_Editor)
		m_DlgViewOutputPtr->m_Editor->ScMethod(SCI_SETTABWIDTH,m_dwTabSize,0);
}

void CDlgViewOutputSet::OnSelchangeComboindentation()
{
	int sel=m_ComboIndentation.GetCurSel();
	if (sel!=CB_ERR) m_dwIndentSize=sel;
	AfxGetApp()->WriteProfileInt("SEP_OUTPUT_SET", "INDENTSIZE",m_dwIndentSize);
	if (m_DlgViewOutputPtr && m_DlgViewOutputPtr->m_Editor)
		m_DlgViewOutputPtr->m_Editor->ScMethod(SCI_SETINDENT,m_dwIndentSize,0);
}
