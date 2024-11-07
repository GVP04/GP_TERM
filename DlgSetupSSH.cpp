// DlgSetupSSH.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgSetupSSH.h"
#include "UniSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSetupSSH dialog


CDlgSetupSSH::CDlgSetupSSH(const char *iSectionName, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetupSSH::IDD, pParent)
{
	m_SectionName=iSectionName;
	m_CurItem=-1;
	m_CurSubItem=0;

	//{{AFX_DATA_INIT(CDlgSetupSSH)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSetupSSH::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSetupSSH)
	DDX_Control(pDX, IDC_LISTPOLICY, m_ListPolicy);
	DDX_Control(pDX, IDC_LISTENCRIPTION, m_ListEncription);
	DDX_Control(pDX, IDC_EDIT1, m_EditList);
	DDX_Control(pDX, IDC_LIST1, m_ListForfardPorts);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSetupSSH, CDialog)
	//{{AFX_MSG_MAP(CDlgSetupSSH)
	ON_BN_CLICKED(IDC_BUTTONADD, OnButtonadd)
	ON_BN_CLICKED(IDC_BUTTONDELETE, OnButtondelete)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_BUTTONUP, OnButtonup)
	ON_BN_CLICKED(IDC_BUTTONUP2, OnButtonup2)
	ON_BN_CLICKED(IDC_BUTTONDOWN, OnButtondown)
	ON_BN_CLICKED(IDC_BUTTONDOWN2, OnButtondown2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSetupSSH message handlers

BOOL CDlgSetupSSH::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int tmpInt=AfxGetApp()->GetProfileInt(m_SectionName,"SSH_PROTOCOL",2);
	
	CheckDlgButton(IDC_RADIOSSH1,tmpInt!=2);
	CheckDlgButton(IDC_RADIOSSH2,tmpInt==2);

	tmpInt=AfxGetApp()->GetProfileInt(m_SectionName,"SSH_X11_MIT_XDM",DLL_SSH_X11_MIT);
	CheckDlgButton(IDC_RADIO_MIT,tmpInt==DLL_SSH_X11_MIT);
	CheckDlgButton(IDC_RADIO_XDM,tmpInt==DLL_SSH_X11_XDM);

	CheckDlgButton(IDC_CHECKCHANGEUSER,AfxGetApp()->GetProfileInt(m_SectionName,"SSH_ALLOWUSERCHANGE",0));
	CheckDlgButton(IDC_CHECKCOMPRESSION,AfxGetApp()->GetProfileInt(m_SectionName,"SSH_ENABLECOMPRESSION",0));
	CheckDlgButton(IDC_CHECKDONTCOMMAND,AfxGetApp()->GetProfileInt(m_SectionName,"SSH_DONTCOMMAND",0));
	CheckDlgButton(IDC_CHECKPSEUDOTERM,AfxGetApp()->GetProfileInt(m_SectionName,"SSH_DONTPTERMINAL",0));
	CheckDlgButton(IDC_CHECKFORWARD,AfxGetApp()->GetProfileInt(m_SectionName,"SSH_AGENTFORWARDING",0));

	SetDlgItemText(IDC_EDITREMOTECOMMAND		,AfxGetApp()->GetProfileString(m_SectionName,	"SSH_EDITREMOTECOMMAND",""));
	CheckDlgButton(IDC_CHECKTISAUTO				,AfxGetApp()->GetProfileInt(m_SectionName,	"SSH_CHECKTISAUTO",0));
	CheckDlgButton(IDC_CHECKKEYBOARDAUTO		,AfxGetApp()->GetProfileInt(m_SectionName,	"SSH_CHECKKEYBOARDAUTO",0));
	SetDlgItemText(IDC_EDITPRIVATEKEYFILE		,AfxGetApp()->GetProfileString(m_SectionName,	"SSH_EDITPRIVATEKEYFILE",""));
	CheckDlgButton(IDC_CHECKFORWARDX11			,AfxGetApp()->GetProfileInt(m_SectionName,	"SSH_CHECKFORWARDX11",0));
	SetDlgItemText(IDC_EDITXLOCATION			,AfxGetApp()->GetProfileString(m_SectionName,	"SSH_EDITXLOCATION",""));
	CheckDlgButton(IDC_CHECKCONFROMOTHERHOSTS	,AfxGetApp()->GetProfileInt(m_SectionName,	"SSH_CHECKCONFROMOTHERHOSTS",0));
	CheckDlgButton(IDC_CHECKREMOTEPORTDOSAME	,AfxGetApp()->GetProfileInt(m_SectionName,	"SSH_CHECKREMOTEPORTDOSAME",0));

	::SetParent(m_EditList.m_hWnd,m_ListForfardPorts.m_hWnd);
	m_ListForfardPorts.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ListForfardPorts.InsertColumn(0,"Type",LVCFMT_RIGHT,55,0);
	m_ListForfardPorts.InsertColumn(1,"IPv",LVCFMT_LEFT,40,0);
	m_ListForfardPorts.InsertColumn(2,"Src port",LVCFMT_LEFT,215,0);
	m_ListForfardPorts.InsertColumn(3,"Destination",LVCFMT_RIGHT,75,0);

	CString csTmp=AfxGetApp()->GetProfileString(m_SectionName,	"SSH_FORWARDPORTS","");
	CString csTmp2;
	int i=0;
	while((csTmp2=ExtractField(csTmp,++i,"\x01"))!="")
	{
		int itm=m_ListForfardPorts.InsertItem(i,ExtractField(csTmp2,1,"\x02"));
		m_ListForfardPorts.SetItemText(itm,1,ExtractField(csTmp2,2,"\x02"));
		m_ListForfardPorts.SetItemText(itm,2,ExtractField(csTmp2,3,"\x02"));
		m_ListForfardPorts.SetItemText(itm,3,ExtractField(csTmp2,4,"\x02"));
	}


	SetDlgItemInt(IDC_EDITMINUTES	,AfxGetApp()->GetProfileInt(m_SectionName,"SSH_REKEY_TIME",0));
	SetDlgItemInt(IDC_EDITMAXDATA	,AfxGetApp()->GetProfileInt(m_SectionName,"SSH_REKEY_DATA",0));
	CheckDlgButton(IDC_CHECKSINGLEDES	,AfxGetApp()->GetProfileInt(m_SectionName,	"SSH2_DES_CBC",0));

	char *txtciphers[]={"-- warn below here --","3DES","Blowfish","DES","AES (SSH-2 only)",};
	DWORD dwciphers[]={DLL_SSH_CIPHER_WARN,DLL_SSH_CIPHER_3DES,DLL_SSH_CIPHER_BLOWFISH,DLL_SSH_CIPHER_DES,DLL_SSH_CIPHER_AES,};
	char *txtkexes[]={"-- warn below here --","Diffie-Hellman group 1","Diffie-Hellman group 14","Diffie-Hellman group exchange",};
	DWORD dwkexes[]={DLL_SSH_KEX_WARN,DLL_SSH_KEX_DHGROUP1,DLL_SSH_KEX_DHGROUP14,DLL_SSH_KEX_DHGEX,};

	DWORD tmpDW=AfxGetApp()->GetProfileInt(m_SectionName,"SSH_CIPHERS",DLL_SSH_CIPHER_3DES+DLL_SSH_CIPHER_BLOWFISH*0x8+DLL_SSH_CIPHER_DES*0x40+DLL_SSH_CIPHER_AES*0x200+DLL_SSH_CIPHER_WARN*0x1000);
	for(i=0;i<DLL_SSH_CIPHER_MAX;i++)
	{
		int itm=m_ListEncription.AddString(txtciphers[tmpDW&0x7]);
		m_ListEncription.SetItemData(itm,tmpDW&0x7);
		tmpDW/=0x8;
	}

	
	tmpDW=	AfxGetApp()->GetProfileInt(m_SectionName,"SSH_KEXES",DLL_SSH_KEX_DHGEX+DLL_SSH_KEX_DHGROUP1*0x8+DLL_SSH_KEX_DHGROUP14*0x40+DLL_SSH_KEX_WARN*0x200);
	for(i=0;i<DLL_SSH_KEX_MAX;i++)
	{
		int itm=m_ListPolicy.AddString(txtkexes[tmpDW&0x7]);
		m_ListPolicy.SetItemData(itm,tmpDW&0x7);
		tmpDW/=0x8;
	}

	return TRUE; 
}

void CDlgSetupSSH::OnOK() 
{
	CString tmpCS;
	int nItems=m_ListForfardPorts.GetItemCount();
	int i;

	tmpCS="";
	BOOL ret=TRUE;
	for(i=0;i<nItems && ret;i++)
	{
		if (tmpCS!="") tmpCS+="\x1";
		CString tmpItem;
		tmpItem=m_ListForfardPorts.GetItemText(i,0);
		tmpCS+=tmpItem;

		tmpItem=m_ListForfardPorts.GetItemText(i,1);
		tmpCS+="\x2"+tmpItem;

		tmpItem=m_ListForfardPorts.GetItemText(i,2);
		tmpItem.Replace(" ","");
		if (tmpItem=="") ret=FALSE;
		tmpCS+="\x2"+tmpItem;
		tmpItem=m_ListForfardPorts.GetItemText(i,3);
		tmpItem.Replace(" ","");
		tmpCS+="\x2"+tmpItem;
	}

	if (ret)
	{
		tmpCS=tmpCS.Left(1023);
		AfxGetApp()->WriteProfileString(m_SectionName,"SSH_FORWARDPORTS",tmpCS);
		tmpCS="";
		AfxGetApp()->WriteProfileInt(m_SectionName,"SSH_PROTOCOL",IsDlgButtonChecked(IDC_RADIOSSH1)?1:2);

		AfxGetApp()->WriteProfileInt(m_SectionName,"SSH_X11_MIT_XDM",IsDlgButtonChecked(IDC_RADIO_MIT)?DLL_SSH_X11_MIT:DLL_SSH_X11_XDM);

		AfxGetApp()->WriteProfileInt(m_SectionName,"SSH_ALLOWUSERCHANGE",IsDlgButtonChecked(IDC_CHECKCHANGEUSER));
		AfxGetApp()->WriteProfileInt(m_SectionName,"SSH_DONTCOMMAND",IsDlgButtonChecked(IDC_CHECKDONTCOMMAND));
		AfxGetApp()->WriteProfileInt(m_SectionName,"SSH_ENABLECOMPRESSION",IsDlgButtonChecked(IDC_CHECKCOMPRESSION));
		AfxGetApp()->WriteProfileInt(m_SectionName,"SSH_DONTPTERMINAL",IsDlgButtonChecked(IDC_CHECKPSEUDOTERM));
		AfxGetApp()->WriteProfileInt(m_SectionName,"SSH_AGENTFORWARDING",IsDlgButtonChecked(IDC_CHECKFORWARD));

		AfxGetApp()->WriteProfileInt(m_SectionName,"SSH_TISAUTO"			,IsDlgButtonChecked(IDC_CHECKTISAUTO));
		AfxGetApp()->WriteProfileInt(m_SectionName,"SSH_KEYBOARDAUTO"		,IsDlgButtonChecked(IDC_CHECKKEYBOARDAUTO));
		AfxGetApp()->WriteProfileInt(m_SectionName,"SSH_FORWARDX11"			,IsDlgButtonChecked(IDC_CHECKFORWARDX11));
		AfxGetApp()->WriteProfileInt(m_SectionName,"SSH_CONFROMOTHERHOSTS"	,IsDlgButtonChecked(IDC_CHECKCONFROMOTHERHOSTS));
		AfxGetApp()->WriteProfileInt(m_SectionName,"SSH_REMOTEPORTDOSAME"	,IsDlgButtonChecked(IDC_CHECKREMOTEPORTDOSAME));

		AfxGetApp()->WriteProfileInt(m_SectionName,"SSH_REKEY_TIME"	,GetDlgItemInt(IDC_EDITMINUTES));
		AfxGetApp()->WriteProfileInt(m_SectionName,"SSH_REKEY_DATA"	,GetDlgItemInt(IDC_EDITMAXDATA));

		GetDlgItemText(IDC_EDITREMOTECOMMAND,tmpCS);
		tmpCS=tmpCS.Left(510);
		AfxGetApp()->WriteProfileString(m_SectionName,"SSH_EDITREMOTECOMMAND"	,tmpCS);
		
		GetDlgItemText(IDC_EDITXLOCATION,tmpCS);
		tmpCS=tmpCS.Left(127);
		AfxGetApp()->WriteProfileString(m_SectionName,"SSH_EDITXLOCATION"	,tmpCS);
		
		GetDlgItemText(IDC_EDITPRIVATEKEYFILE,tmpCS);
		AfxGetApp()->WriteProfileString(m_SectionName,"SSH_EDITPRIVATEKEYFILE"	,tmpCS);

		AfxGetApp()->WriteProfileInt(m_SectionName,"SSH2_DES_CBC"	,IsDlgButtonChecked(IDC_CHECKSINGLEDES));

		DWORD tmpDW=0,dwMulty=1;
		for(i=0;i<DLL_SSH_CIPHER_MAX;i++)
		{
			tmpDW+=dwMulty*m_ListEncription.GetItemData(i);
			dwMulty*=0x8;
		}
		AfxGetApp()->WriteProfileInt(m_SectionName,"SSH_CIPHERS"	,tmpDW);

		tmpDW=0;dwMulty=1;
		for(i=0;i<DLL_SSH_KEX_MAX;i++)
		{
			tmpDW+=dwMulty*m_ListPolicy.GetItemData(i);
			dwMulty*=0x8;
		}
		AfxGetApp()->WriteProfileInt(m_SectionName,"SSH_KEXES"	,tmpDW);
	
		CDialog::OnOK();
	}
	else
		MessageBox("Port must be not empty.");
}

void CDlgSetupSSH::OnButtonadd() 
{
	int nItem=m_ListForfardPorts.InsertItem(1000,"Local");
	m_ListForfardPorts.SetItemText(nItem,1,"Auto");
	m_ListForfardPorts.SetItemText(nItem,2,"");
	m_ListForfardPorts.SetItemText(nItem,3,"");
}

void CDlgSetupSSH::OnButtondelete() 
{
	POSITION posit = m_ListForfardPorts.GetFirstSelectedItemPosition();

	if (posit)
	{
		int nItem = m_ListForfardPorts.GetNextSelectedItem(posit);
		m_ListForfardPorts.DeleteItem(nItem);
	}
}

void CDlgSetupSSH::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
    LPNMITEMACTIVATE lpnmitem =(LPNMITEMACTIVATE) pNMHDR;
	LVHITTESTINFO htinfo={0};
	htinfo.pt=lpnmitem->ptAction;
	htinfo.iItem=-1;
	m_ListForfardPorts.SubItemHitTest(&htinfo);

	if (htinfo.iItem>=0)
	{
		CString csSIText=m_ListForfardPorts.GetItemText(htinfo.iItem,htinfo.iSubItem);
		switch(htinfo.iSubItem)
		{
		case 0:
		case 1:
			OnKillfocusEdit1();
			break;
		case 2:
		case 3:
			{
				if (m_CurItem>=0) OnKillfocusEdit1();
				m_EditList.SetWindowText(csSIText);
				m_EditList.SetSel(0,-1);
				CRect crItem;
				m_ListForfardPorts.GetSubItemRect(htinfo.iItem,htinfo.iSubItem,LVIR_BOUNDS,crItem);
				crItem.top--;
				crItem.left--;
				m_EditList.MoveWindow(crItem);
				m_EditList.ModifyStyle(0,WS_VISIBLE);
				::SetFocus(m_EditList.m_hWnd);
				m_CurItem=htinfo.iItem;
				m_CurSubItem=htinfo.iSubItem;
			}
			break;
		}
	}
	*pResult = 0;
}

void CDlgSetupSSH::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
    LPNMITEMACTIVATE lpnmitem =(LPNMITEMACTIVATE) pNMHDR;
	LVHITTESTINFO htinfo={0};
	htinfo.pt=lpnmitem->ptAction;
	htinfo.iItem=-1;
	m_ListForfardPorts.SubItemHitTest(&htinfo);

	if (htinfo.iItem>=0)
	{
		CString csSIText=m_ListForfardPorts.GetItemText(htinfo.iItem,htinfo.iSubItem);
		switch(htinfo.iSubItem)
		{
		case 0:
			{
				if (csSIText=="Local")
					csSIText="Remote";
				else
					if (csSIText=="Remote") csSIText="Dynamic";
				else
					csSIText="Local";
				m_ListForfardPorts.SetItemText(htinfo.iItem,htinfo.iSubItem,csSIText);
			}
			break;
		case 1:
			{
				if (csSIText=="Auto") 
					csSIText="IPv4";
				else
					if (csSIText=="IPv4") csSIText="IPv6";
				else
					csSIText="Auto";
				m_ListForfardPorts.SetItemText(htinfo.iItem,htinfo.iSubItem,csSIText);
			}
			break;
		case 2:
		case 3:
			break;
		}
	}
	*pResult = 0;
}


void CDlgSetupSSH::OnChangeEdit1() 
{
	CString tmps;
	m_EditList.GetWindowText(tmps);
	m_ListForfardPorts.SetItemText(m_CurItem,m_CurSubItem,tmps);
}

void CDlgSetupSSH::OnKillfocusEdit1() 
{
	if (m_CurItem>=0 && m_CurSubItem>1 && m_CurSubItem<4)
	{
		CString tmps;
		m_EditList.GetWindowText(tmps);
		m_ListForfardPorts.SetItemText(m_CurItem,m_CurSubItem,tmps);
		m_EditList.ModifyStyle(WS_VISIBLE,0);
		m_CurItem=-1;
		m_CurSubItem=0;
	}
}


void CDlgSetupSSH::OnButtonup() 
{
	int sel=m_ListEncription.GetCurSel();
	if (sel!=LB_ERR && sel)
	{
		DWORD itData=m_ListEncription.GetItemData(sel);
		CString csIt;
		m_ListEncription.GetText(sel,csIt);
		m_ListEncription.DeleteString(sel);
		sel=m_ListEncription.InsertString(--sel,csIt);
		m_ListEncription.SetItemData(sel,itData);
		m_ListEncription.SetCurSel(sel);
	}
}

void CDlgSetupSSH::OnButtonup2() 
{
	int sel=m_ListPolicy.GetCurSel();
	if (sel!=LB_ERR && sel)
	{
		DWORD itData=m_ListPolicy.GetItemData(sel);
		CString csIt;
		m_ListPolicy.GetText(sel,csIt);
		m_ListPolicy.DeleteString(sel);
		sel=m_ListPolicy.InsertString(--sel,csIt);
		m_ListPolicy.SetItemData(sel,itData);
		m_ListPolicy.SetCurSel(sel);
	}
}

void CDlgSetupSSH::OnButtondown() 
{
	int sel=m_ListEncription.GetCurSel();
	if (sel!=LB_ERR && sel<m_ListEncription.GetCount()-1)
	{
		DWORD itData=m_ListEncription.GetItemData(sel);
		CString csIt;
		m_ListEncription.GetText(sel,csIt);
		m_ListEncription.DeleteString(sel);
		sel=m_ListEncription.InsertString(++sel,csIt);
		m_ListEncription.SetItemData(sel,itData);
		m_ListEncription.SetCurSel(sel);
	}
}

void CDlgSetupSSH::OnButtondown2() 
{
	int sel=m_ListPolicy.GetCurSel();
	if (sel!=LB_ERR && sel<m_ListPolicy.GetCount()-1)
	{
		DWORD itData=m_ListPolicy.GetItemData(sel);
		CString csIt;
		m_ListPolicy.GetText(sel,csIt);
		m_ListPolicy.DeleteString(sel);
		sel=m_ListPolicy.InsertString(++sel,csIt);
		m_ListPolicy.SetItemData(sel,itData);
		m_ListPolicy.SetCurSel(sel);
	}
}
