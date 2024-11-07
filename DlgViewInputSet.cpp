// DlgViewInputSet.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgViewInputSet.h"
#include "DlgEditKeywords.h"
#include "Scintilla\Scintilla.h"
#include "Scintilla\SciLexer.h"
#include "DlgKeyEditor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgViewInputSet dialog


CDlgViewInputSet::CDlgViewInputSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewInputSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgViewInputSet)
	//}}AFX_DATA_INIT
	m_dwInputSet=0;
	m_DlgViewInputPtr=NULL;
	m_csSoftBreakSeq=NULL;
	m_dwKeyBreak=NULL;
	m_dwKeySoftBreak=NULL;
	m_dwKeyExecute=NULL;
	m_Lock=FALSE;
	m_CurLexer=78;
	DlgAutoSize=NULL;
	m_dwTabSize=8;
	m_dwIndentSize=0;
}

CDlgViewInputSet::~CDlgViewInputSet()
{
	if (DlgAutoSize)
		delete DlgAutoSize;
	DlgAutoSize=NULL;
}

void CDlgViewInputSet::OnDestroy()
{
	if (DlgAutoSize)
		delete DlgAutoSize;
	DlgAutoSize=NULL;
	CDialog::OnDestroy();
}


void CDlgViewInputSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgViewInputSet)
	DDX_Control(pDX, IDC_COMBOINDENTATION, m_ComboIndentation);
	DDX_Control(pDX, IDC_COMBOTAB, m_ComboTab);
	DDX_Control(pDX, IDC_COMBOLEXER, m_ComboLexer);
	DDX_Control(pDX, IDC_LISTVIEWSET, m_lcListViewSet);
	DDX_Control(pDX, IDC_COMBO4, m_ComboBreak);
	DDX_Control(pDX, IDC_COMBO3, m_ComboSoftBreak);
	DDX_Control(pDX, IDC_COMBO1, m_ComboVK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgViewInputSet, CDialog)
	//{{AFX_MSG_MAP(CDlgViewInputSet)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTNFONTCOLOR, OnBtnfontcolor)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeComboVK)
	ON_BN_CLICKED(IDC_CHECK1, OnCheckCtrl)
	ON_BN_CLICKED(IDC_CHECK4, OnCheckShift)
	ON_BN_CLICKED(IDC_CHECK5, OnCheckAlt)
	ON_BN_CLICKED(IDC_CHECK2, OnCheckCtrlSB)
	ON_BN_CLICKED(IDC_CHECK6, OnCheckShiftSB)
	ON_BN_CLICKED(IDC_CHECK7, OnCheckAltSB)
	ON_CBN_SELCHANGE(IDC_COMBO3, OnSelchangeComboSB)
	ON_CBN_SELCHANGE(IDC_COMBO4, OnSelchangeComboBreak)
	ON_BN_CLICKED(IDC_CHECK9, OnCheckBreakAlt)
	ON_BN_CLICKED(IDC_CHECK8, OnCheckBreakShift)
	ON_BN_CLICKED(IDC_CHECK3, OnCheckBreakCtrl)
	ON_EN_CHANGE(IDC_EDITSB, OnChangeEditsb)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTVIEWSET, OnItemchangedListviewset)
	ON_BN_CLICKED(IDC_BUTTONBROWSE, OnButtonbrowse)
	ON_EN_CHANGE(IDC_EDITSRVFILE, OnChangeEditsrvfile)
	ON_EN_CHANGE(IDC_EDITSRVFILE2, OnChangeEditsrvItem)
	ON_EN_CHANGE(IDC_EDITCLFILE, OnChangeEditclfile)
	ON_BN_CLICKED(IDC_BUTTONKEYWORDS, OnButtonkeywords)
	ON_CBN_SELCHANGE(IDC_COMBOLEXER, OnSelchangeCombolexer)
	ON_BN_CLICKED(IDC_BUTTONKEYWORDS2, OnButtonkeywords2)
	ON_BN_CLICKED(IDC_BUTTONEDITKEY, OnButtoneditkey)
	ON_CBN_SELCHANGE(IDC_COMBOINDENTATION, OnSelchangeComboindentation)
	ON_CBN_SELCHANGE(IDC_COMBOTAB, OnSelchangeCombotab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgViewInputSet message handlers

BOOL CDlgViewInputSet::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_Lock=TRUE;
	m_DlgViewInputPtr->m_CDlgViewInputSetPtr=this;

	m_dwInputSet=AfxGetApp()->GetProfileInt("SEP_INPUT_SET", "INPUT_SET",0x9DB);
	m_CurLexer=AfxGetApp()->GetProfileInt("SEP_INPUT_SET", "m_CurLexer",78);

	DlgAutoSize=new GP_AutoSizing;
	DlgAutoSize->AddSetMain(this->m_hWnd);

	m_ComboBreak.ResetContent();
	m_ComboSoftBreak.ResetContent();
	m_ComboVK.ResetContent();
	CString tmps;
	DWORD tmpBreak=0;
	DWORD tmpSoftBreak=0;
	CString tmpSoftBreakSeq="24";
	DWORD tmpExec=0;
	if (m_DlgViewInputPtr)
	{
		m_dwKeyBreak=&(m_DlgViewInputPtr->m_Editor->m_dwKeyBreak);
		m_dwKeySoftBreak=&(m_DlgViewInputPtr->m_Editor->m_dwKeySoftBreak);
		m_csSoftBreakSeq=&(m_DlgViewInputPtr->m_Editor->m_csSoftBreakSeq);
		m_dwKeyExecute=&(m_DlgViewInputPtr->m_Editor->m_dwKeyExecute);
		LoadKeys();
		tmpBreak=m_DlgViewInputPtr->m_Editor->m_dwKeyBreak;
		tmpSoftBreak=m_DlgViewInputPtr->m_Editor->m_dwKeySoftBreak;
		tmpSoftBreakSeq=m_DlgViewInputPtr->m_Editor->m_csSoftBreakSeq;
		tmpExec=m_DlgViewInputPtr->m_Editor->m_dwKeyExecute;
		if ((m_dwInputSet&CDVIS_AUTOLOAD)==CDVIS_AUTOLOAD)
			m_DlgViewInputPtr->SendMessage(WM_COMMAND,SCCMND_LOADCLIENT,NULL);
		SetDlgItemText(IDC_EDITCLFILE,m_DlgViewInputPtr->m_Editor->m_csDefClFileName);
		SetDlgItemText(IDC_EDITSRVFILE,m_DlgViewInputPtr->m_Editor->m_csDefSrvFileName);
		SetDlgItemText(IDC_EDITSRVFILE2,m_DlgViewInputPtr->m_Editor->m_csDefSrvItemName);
	}

	SetDlgItemText(IDC_EDITSB,tmpSoftBreakSeq);

	int i;
	for(i=0;i<GP_N_TYPE_HOTKEY;i++)
	{
		tmps=GP_HotKey::aVKName[i];
		tmps.Replace("|","");
		m_ComboSoftBreak.AddString(tmps);
		m_ComboBreak.AddString(tmps);
		int nItem=m_ComboVK.AddString(tmps);
		m_ComboBreak.SetItemData(nItem,GP_HotKey:: aVKUINT[i]);
		m_ComboSoftBreak.SetItemData(nItem,GP_HotKey:: aVKUINT[i]);
		m_ComboVK.SetItemData(nItem,GP_HotKey::aVKUINT[i]);
		if ((tmpBreak/0x10000)==GP_HotKey::aVKUINT[i])
			m_ComboBreak.SetCurSel(nItem);
		if ((tmpSoftBreak/0x10000)==GP_HotKey::aVKUINT[i])
			m_ComboSoftBreak.SetCurSel(nItem);
		if ((tmpExec/0x10000)==GP_HotKey::aVKUINT[i])
			m_ComboVK.SetCurSel(nItem);
	}

	CheckDlgButton(IDC_CHECK9,(tmpBreak&MOD_ALT)==MOD_ALT);
	CheckDlgButton(IDC_CHECK3,(tmpBreak&MOD_CONTROL)==MOD_CONTROL);
	CheckDlgButton(IDC_CHECK8,(tmpBreak&MOD_SHIFT)==MOD_SHIFT);

	CheckDlgButton(IDC_CHECK7,(tmpSoftBreak&MOD_ALT)==MOD_ALT);
	CheckDlgButton(IDC_CHECK2,(tmpSoftBreak&MOD_CONTROL)==MOD_CONTROL);
	CheckDlgButton(IDC_CHECK6,(tmpSoftBreak&MOD_SHIFT)==MOD_SHIFT);

	CheckDlgButton(IDC_CHECK5,(tmpExec&MOD_ALT)==MOD_ALT);
	CheckDlgButton(IDC_CHECK1,(tmpExec&MOD_CONTROL)==MOD_CONTROL);
	CheckDlgButton(IDC_CHECK4,(tmpExec&MOD_SHIFT)==MOD_SHIFT);


	m_lcListViewSet.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);

#ifdef RUS
	m_lcListViewSet.InsertColumn(0,"Наименование",LVCFMT_LEFT,200,0);
	char * arrNM2[32]={
		"Загрузить при старте","Сохранить по завершении","Прямой ввод","Номера строк","Пробельные символы","Показывать EOL","Отображать всю строку","Цветовая подсветка",
		"Блокировать клавиши","Use Tabs","Line Indentation","Indentation Guides","Backspace Unindent","","","",
		"","","","","","","","",
		"","","","","","","","",
#else
	m_lcListViewSet.InsertColumn(0,"Name",LVCFMT_LEFT,200,0);
	char * arrNM2[32]={
		"Auto Load","Auto Save","Direct input","Line Numbers","White Space","View EOL","Line wrapping","Colorise",
		"Lock Keys","Use Tabs","Line Indentation","Indentation Guides","Backspace Unindent","","","",
		"","","","","","","","",
		"","","","","","","","",
#endif
	};


	for(i=0;i<13;i++)
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

	m_Lock=FALSE;

	UpdateInputSettings(-1);

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
	m_dwTabSize=AfxGetApp()->GetProfileInt("SEP_INPUT_SET", "TABSIZE",0x8);
	m_ComboTab.SetCurSel(m_dwTabSize-1);
	OnSelchangeCombotab();
	m_dwIndentSize=AfxGetApp()->GetProfileInt("SEP_INPUT_SET", "INDENTSIZE",0x0);
	m_ComboIndentation.SetCurSel(m_dwIndentSize);
	OnSelchangeComboindentation();
	return TRUE;
}

void CDlgViewInputSet::UpdateCtrls()
{
	DWORD tmpMsk=1;

	int i;
	for(i=0;i<32;i++)
	{
		int cc=m_lcListViewSet.GetCheck(i);
		if ((cc==0 && (tmpMsk&m_dwInputSet)) || ((tmpMsk&m_dwInputSet)==0 && cc))
			m_lcListViewSet.SetCheck(i,(tmpMsk&m_dwInputSet)!=0);
		tmpMsk+=tmpMsk;
	}
}

void CDlgViewInputSet::UpdateInputSettings(UINT iType)
{
	UINT istart=iType;
	UINT iend=iType+1;
	if (iType>31) istart=0,iend=32;
	UINT i;
	for(i=istart;i<iend;i++)
		switch(i)
		{
		case 0://AutoLoad
			break;
		case 1://AutoSave
			if (m_DlgViewInputPtr)
				m_DlgViewInputPtr->m_Editor->m_AutoSaveFlag=
					((m_dwInputSet&CDVIS_AUTOSAVE)==CDVIS_AUTOSAVE)?1:0;
			break;
		case 2://CDVIS_DIRECTINPUT
			if (m_DlgViewInputPtr)
			{
				m_DlgViewInputPtr->m_Editor->m_DirectInputFlag=
					((m_dwInputSet&CDVIS_DIRECTINPUT)==CDVIS_DIRECTINPUT)?1:0;
				m_DlgViewInputPtr->UpdateTB();
			}
			break;
		case 3://Line Numbers
			if (m_DlgViewInputPtr && m_DlgViewInputPtr->m_Editor)
				m_DlgViewInputPtr->m_Editor->ScMethod(SCI_SETMARGINWIDTHN,0,((m_dwInputSet&CDVIS_LINENUMBERS)==CDVIS_LINENUMBERS)?40:0);
			break;
		case 4://White Space
			if (m_DlgViewInputPtr && m_DlgViewInputPtr->m_Editor)
				m_DlgViewInputPtr->m_Editor->ScMethod(SCI_SETVIEWWS,(m_dwInputSet&CDVIS_VIEWWHITESPACE)==CDVIS_VIEWWHITESPACE?1:0,0);
			break;
		case 5://View EOL
			if (m_DlgViewInputPtr && m_DlgViewInputPtr->m_Editor)
				m_DlgViewInputPtr->m_Editor->ScMethod(SCI_SETVIEWEOL,(m_dwInputSet&CDVIS_VIEWEOL)==CDVIS_VIEWEOL,0);
			break;
		case 6://Line wrapping
			if (m_DlgViewInputPtr && m_DlgViewInputPtr->m_Editor)
				m_DlgViewInputPtr->m_Editor->ScMethod(SCI_SETWRAPMODE,(m_dwInputSet&CDVIS_LINEWRAPPING)==CDVIS_LINEWRAPPING?1:0,0);
			break;
		case 7://COLORISE LEX
			OnSelchangeCombolexer();
			break;
		case 8://Lock Keys
			if (m_DlgViewInputPtr)
				m_DlgViewInputPtr->m_Editor->m_LockKeysFlag=
					((m_dwInputSet&CDVIS_LOCKKEYS)==CDVIS_LOCKKEYS)?1:0;
			break;
		case 9://CDVIS_USETABS
			if (m_DlgViewInputPtr && m_DlgViewInputPtr->m_Editor)
				m_DlgViewInputPtr->m_Editor->ScMethod(SCI_SETUSETABS,(m_dwInputSet&CDVIS_USETABS)==CDVIS_USETABS?1:0,0);
			break;
		case 10://CDVIS_LINEINDENTATION
			if (m_DlgViewInputPtr && m_DlgViewInputPtr->m_Editor)
				m_DlgViewInputPtr->m_Editor->ScMethod(SCI_SETTABINDENTS,(m_dwInputSet&CDVIS_LINEINDENTATION)==CDVIS_LINEINDENTATION?1:0,0);
			break;
		case 11://CDVIS_INDENTATIONGUIDES
			if (m_DlgViewInputPtr && m_DlgViewInputPtr->m_Editor)
				m_DlgViewInputPtr->m_Editor->ScMethod(SCI_SETINDENTATIONGUIDES,(m_dwInputSet&CDVIS_INDENTATIONGUIDES)==CDVIS_INDENTATIONGUIDES?1:0,0);
			break;
		case 12://CDVIS_BAKSPACEUNINDENT
			if (m_DlgViewInputPtr && m_DlgViewInputPtr->m_Editor)
				m_DlgViewInputPtr->m_Editor->ScMethod(SCI_SETBACKSPACEUNINDENTS,(m_dwInputSet&CDVIS_BAKSPACEUNINDENT)==CDVIS_BAKSPACEUNINDENT?1:0,0);
			break;
		}
}

void CDlgViewInputSet::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if (DlgAutoSize)
		try{DlgAutoSize->UpdateSize();}catch(...){GPC.m_ErrReport.GPWriteErrorLog("CDlgViewInputSet", "OnSize","");}
}

BOOL CDlgViewInputSet::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if ((wParam==1 || wParam==2) && lParam==0) return TRUE;

	return CDialog::OnCommand(wParam, lParam);
}

void CDlgViewInputSet::OnBtnfontcolor()
{
	FontColorDlg(0);
}

#include "DlgEditorColor.h"
#define NARRTMP	10

UINT CDlgViewInputSet::FontColorDlg(UINT iType)
{
	UINT ret=IDCANCEL;
	if (m_DlgViewInputPtr && m_DlgViewInputPtr->m_Editor && m_DlgViewInputPtr->m_Editor->m_hWnd && iType==0)
	{
		CDlgEditorColor dlg;
		dlg.SetEditor((GPScintilla *)m_DlgViewInputPtr->m_Editor);
		dlg.LoadColors(m_CurLexer);

		if ((ret=dlg.DoModal())==IDOK)
		{
			dlg.SaveColors(m_CurLexer);
			m_DlgViewInputPtr->m_Editor->LoadColors(m_CurLexer);
		}
	}

	return ret;
}

void CDlgViewInputSet::OnSelchangeComboVK()
{
	if (m_dwKeyExecute)
	{
		*m_dwKeyExecute=((*m_dwKeyExecute&(MOD_CONTROL|MOD_SHIFT|MOD_ALT))|(0x10000*m_ComboVK.GetItemData(m_ComboVK.GetCurSel())));
		SaveKeys();
	}
}

void CDlgViewInputSet::OnCheckCtrl()
{
	if (m_dwKeyExecute)
	{
		*m_dwKeyExecute^=MOD_CONTROL;
		SaveKeys();
	}
}

void CDlgViewInputSet::OnCheckShift()
{
	if (m_dwKeyExecute)
	{
		*m_dwKeyExecute^=MOD_SHIFT;
		SaveKeys();
	}
}

void CDlgViewInputSet::OnCheckAlt()
{
	if (m_dwKeyExecute)
	{
		*m_dwKeyExecute^=MOD_ALT;
		SaveKeys();
	}
}

LRESULT CDlgViewInputSet::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	return CDialog::WindowProc(message, wParam, lParam);
}

void CDlgViewInputSet::OnSelchangeComboSB()
{
	if (m_dwKeySoftBreak)
	{
		*m_dwKeySoftBreak=(*m_dwKeySoftBreak&(MOD_CONTROL|MOD_SHIFT|MOD_ALT)|(0x10000*m_ComboSoftBreak.GetItemData(m_ComboSoftBreak.GetCurSel())));
		SaveKeys();
	}
}

void CDlgViewInputSet::OnCheckCtrlSB()
{
	if (m_dwKeySoftBreak)
	{
		*m_dwKeySoftBreak^=MOD_CONTROL;
		SaveKeys();
	}
}

void CDlgViewInputSet::OnCheckShiftSB()
{
	if (m_dwKeySoftBreak)
	{
		*m_dwKeySoftBreak^=MOD_SHIFT;
		SaveKeys();
	}
}

void CDlgViewInputSet::OnCheckAltSB()
{
	if (m_dwKeySoftBreak)
	{
		*m_dwKeySoftBreak^=MOD_ALT;
		SaveKeys();
	}
}

void CDlgViewInputSet::SaveKeys()
{
	AfxGetApp()->WriteProfileInt("SEP_OUTPUT_SET","KEY_EXECUTE",*m_dwKeyExecute);
	AfxGetApp()->WriteProfileInt("SEP_OUTPUT_SET","KEY_BREAK",*m_dwKeyBreak);
	AfxGetApp()->WriteProfileInt("SEP_OUTPUT_SET","KEY_SOFTBREAK",*m_dwKeySoftBreak);
	AfxGetApp()->WriteProfileString("SEP_OUTPUT_SET","KEY_SOFTBREAKSEQ",*m_csSoftBreakSeq);
}

void CDlgViewInputSet::LoadKeys()
{
	if (m_dwKeyExecute)
		*m_dwKeyExecute=AfxGetApp()->GetProfileInt("SEP_OUTPUT_SET","KEY_EXECUTE",*m_dwKeyExecute);
	if (m_dwKeyBreak)
		*m_dwKeyBreak=AfxGetApp()->GetProfileInt("SEP_OUTPUT_SET","KEY_BREAK",*m_dwKeyBreak);
	if (m_dwKeySoftBreak)
		*m_dwKeySoftBreak=AfxGetApp()->GetProfileInt("SEP_OUTPUT_SET","KEY_SOFTBREAK",*m_dwKeySoftBreak);
	if (m_csSoftBreakSeq)
		*m_csSoftBreakSeq=AfxGetApp()->GetProfileString("SEP_OUTPUT_SET","KEY_SOFTBREAKSEQ","24");
}


void CDlgViewInputSet::OnSelchangeComboBreak()
{
	if (m_dwKeyBreak)
	{
		*m_dwKeyBreak=(*m_dwKeyBreak&(MOD_CONTROL|MOD_SHIFT|MOD_ALT)|(0x10000*m_ComboBreak.GetItemData(m_ComboBreak.GetCurSel())));
		SaveKeys();
	}
}

void CDlgViewInputSet::OnCheckBreakAlt()
{
	if (m_dwKeyBreak)
	{
		*m_dwKeyBreak^=MOD_ALT;
		SaveKeys();
	}
}

void CDlgViewInputSet::OnCheckBreakShift()
{
	if (m_dwKeyBreak)
	{
		*m_dwKeyBreak^=MOD_SHIFT;
		SaveKeys();
	}
}

void CDlgViewInputSet::OnCheckBreakCtrl()
{
	if (m_dwKeyBreak)
	{
		*m_dwKeyBreak^=MOD_CONTROL;
		SaveKeys();
	}
}

void CDlgViewInputSet::OnChangeEditsb()
{
	UINT arr[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
	UINT nItems=0;
	int i;
	CString tmps;
	CString tmpscmp;
	GetDlgItemText(IDC_EDITSB,tmps);
	tmpscmp=tmps;
	tmps+=" ";
	int len=tmps.GetLength();
	if (len>0)
		for(i=0;i<len;i++)
			if (i==0)
			{
				if (tmps[0]<'0' || tmps[0]>'9') tmps.Delete(i--,1),len--;
			}
			else
				if ((tmps[i]<'0' || tmps[i]>'9') && (tmps[i-1]<'0' || tmps[i-1]>'9')) tmps.Delete(i--,1),len--;


	len=tmps.GetLength();
	for(i=0;i<len;i++)
	{
		if (tmps[i]<='9' && tmps[i]>='0')
			arr[nItems]=arr[nItems]*10+tmps[i]-'0';
		else
		{
			if (arr[nItems]>256) arr[nItems]=(arr[nItems]%100)+200;
			nItems++;
		}
	}
	tmps="";
	if (nItems>0)
	{
		char t[50];
		for(i=0;(UINT)i<nItems;i++)
		{
			sprintf(t,i==0?"%d":" %d",arr[i]);
			tmps+=t;
		}
	}

	if (tmps!=tmpscmp)
	{
		if ((tmps.GetLength()!=tmpscmp.GetLength()-1) || tmpscmp[tmpscmp.GetLength()-1]!=' ')
		{
			DWORD start=0,end=0;
			::SendMessage(::GetDlgItem(m_hWnd,IDC_EDITSB),EM_GETSEL,(WPARAM)&start,(LPARAM)&end);
			if (start>0) start--,end--;
			SetDlgItemText(IDC_EDITSB,tmps);
			::SendMessage(::GetDlgItem(m_hWnd,IDC_EDITSB),EM_SETSEL,start,end);
		}
	}
	if (m_csSoftBreakSeq) *m_csSoftBreakSeq=tmps;
	SaveKeys();
}

void CDlgViewInputSet::OnItemchangedListviewset(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (m_Lock==FALSE)
	{
		NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

		if (((pNMListView->uNewState^pNMListView->uOldState)&0x3000)!=0)
		{
			if ((pNMListView->uNewState&0x1000))
				m_dwInputSet&=(0xFFFFFFFFF^GPCurrent::uArrPower[(pNMListView->iItem)%32]);
			else
				m_dwInputSet|=GPCurrent::uArrPower[(pNMListView->iItem)%32];
		}
		UpdateInputSettings(pNMListView->iItem);
		AfxGetApp()->WriteProfileInt("SEP_INPUT_SET", "INPUT_SET",m_dwInputSet);
	}
	*pResult = 0;
}

void CDlgViewInputSet::OnButtonbrowse()
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
	strcpy(opf.lpstrFile,m_DlgViewInputPtr->m_Editor->m_csDefClFileName);
	opf.nMaxFile =4900;
	opf.Flags =OFN_DONTADDTORECENT|OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_NOCHANGEDIR|OFN_PATHMUSTEXIST|OFN_NOCHANGEDIR|OFN_SHOWHELP;

	if (GetSaveFileName(&opf))
	{
		m_DlgViewInputPtr->m_Editor->m_csDefClFileName=opf.lpstrFile;
		SetDlgItemText(IDC_EDITCLFILE,m_DlgViewInputPtr->m_Editor->m_csDefClFileName);
	}
	delete[] opf.lpstrFile;
}

void CDlgViewInputSet::OnChangeEditsrvfile()
{
	if (m_DlgViewInputPtr && !m_Lock)
		GetDlgItemText(IDC_EDITSRVFILE,m_DlgViewInputPtr->m_Editor->m_csDefSrvFileName);
}

void CDlgViewInputSet::OnChangeEditsrvItem()
{
	if (m_DlgViewInputPtr && !m_Lock)
		GetDlgItemText(IDC_EDITSRVFILE2,m_DlgViewInputPtr->m_Editor->m_csDefSrvItemName);
}

void CDlgViewInputSet::OnChangeEditclfile()
{
	if (m_DlgViewInputPtr && !m_Lock)
		GetDlgItemText(IDC_EDITCLFILE,m_DlgViewInputPtr->m_Editor->m_csDefClFileName);
}

void CDlgViewInputSet::OnButtonkeywords()
{
	CDlgEditKeywords dlg;
	dlg.SetTypeKeyword(DEK_KEYWORD);
	dlg.SetLexerType(m_CurLexer);
	if (dlg.DoModal()==IDOK && m_DlgViewInputPtr && m_DlgViewInputPtr->m_Editor)
		m_DlgViewInputPtr->m_Editor->LoadKeywords(m_CurLexer);
}

void CDlgViewInputSet::OnSelchangeCombolexer()
{
	int cursel=m_ComboLexer.GetCurSel();
	if (cursel!=CB_ERR)
	{
		m_CurLexer=m_ComboLexer.GetItemData(cursel);
		AfxGetApp()->WriteProfileInt("SEP_INPUT_SET", "m_CurLexer",m_CurLexer);
		if (m_DlgViewInputPtr && (m_dwInputSet&CDVIS_COLORISELEX)==CDVIS_COLORISELEX)
		{
			m_DlgViewInputPtr->m_Editor->LoadKeywords(m_CurLexer);

			if ((m_dwInputSet&CDVIS_COLORISELEX)==CDVIS_COLORISELEX)
			{
				m_DlgViewInputPtr->m_Editor->ScMethod(SCI_SETLEXER,m_CurLexer,0);
				m_DlgViewInputPtr->m_Editor->LoadColors(m_CurLexer);
				m_DlgViewInputPtr->m_Editor->ScMethod(SCI_COLOURISE,0,-1);
			}
		}

	}
	if (m_DlgViewInputPtr && m_DlgViewInputPtr->m_Editor && (m_dwInputSet&CDVIS_COLORISELEX)!=CDVIS_COLORISELEX)
	{
		m_DlgViewInputPtr->m_Editor->ScMethod(SCI_SETLEXER,SCLEX_NULL,0);
		m_DlgViewInputPtr->m_Editor->ScMethod(SCI_COLOURISE,0,-1);

	}
}

void CDlgViewInputSet::OnButtonkeywords2()
{
	CDlgEditKeywords dlg;
	dlg.SetTypeKeyword(DEK_KEYWORDAPPEND);
	if (dlg.DoModal()==IDOK && m_DlgViewInputPtr && m_DlgViewInputPtr->m_Editor)
		m_DlgViewInputPtr->m_Editor->LoadAppendKeyWords();
}

void CDlgViewInputSet::OnButtoneditkey()
{
	CDlgKeyEditor dlg;
	dlg.m_FileName=m_DlgViewInputPtr->m_Editor->m_FileNameLK;
	if (dlg.DoModal()==IDOK)
		m_DlgViewInputPtr->m_Editor->LoadLockKeys();
}

void CDlgViewInputSet::OnSelchangeCombotab()
{
	int sel=m_ComboTab.GetCurSel();
	if (sel!=CB_ERR) m_dwTabSize=sel+1;
	AfxGetApp()->WriteProfileInt("SEP_INPUT_SET", "TABSIZE",m_dwTabSize);
	if (m_DlgViewInputPtr && m_DlgViewInputPtr->m_Editor)
		m_DlgViewInputPtr->m_Editor->ScMethod(SCI_SETTABWIDTH,m_dwTabSize,0);
}

void CDlgViewInputSet::OnSelchangeComboindentation()
{
	int sel=m_ComboIndentation.GetCurSel();
	if (sel!=CB_ERR) m_dwIndentSize=sel;
	AfxGetApp()->WriteProfileInt("SEP_INPUT_SET", "INDENTSIZE",m_dwIndentSize);
	if (m_DlgViewInputPtr && m_DlgViewInputPtr->m_Editor)
		m_DlgViewInputPtr->m_Editor->ScMethod(SCI_SETINDENT,m_dwIndentSize,0);
}


