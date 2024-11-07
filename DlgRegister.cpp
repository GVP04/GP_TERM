// DlgRegister.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgRegister.h"
#include "GP_TermDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRegister dialog


CDlgRegister::CDlgRegister(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRegister::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRegister)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRegister)
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRegister, CDialog)
	//{{AFX_MSG_MAP(CDlgRegister)
	ON_BN_CLICKED(IDC_BUTTONUNREG, OnButtonunreg)
	ON_BN_CLICKED(IDC_BUTTONREG, OnButtonreg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRegister message handlers

void CDlgRegister::OnButtonunreg()
{
	CString str;
	GetDlgItemText(IDC_EDITUNREG,str);
	GPC.m_Document->UnRegisterGPTermInROT(str);
	UpdateRegList();
}

void CDlgRegister::OnButtonreg()
{
	CString str;
	GetDlgItemText(IDC_EDITREG,str);
	GPC.m_Document->RegisterGPTermInROT(str);
	UpdateRegList();
}

void CDlgRegister::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	char str[2000];
	str[100]=0;

	if ((pNMListView->uNewState&LVIS_SELECTED)==LVIS_SELECTED)
	{
		if (m_List.GetItemText(pNMListView->iItem,0,str,1900)<=0) *str=0;
		SetDlgItemText(IDC_EDITUNREG,str);
	}
	*pResult = 0;
}

BOOL CDlgRegister::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
#ifdef RUS
	m_List.InsertColumn(0,"Имя регистрации",LVCFMT_RIGHT,200,0);
#else
	m_List.InsertColumn(0,"Registered names",LVCFMT_RIGHT,200,0);
#endif
	UpdateRegList();
	return TRUE;
}

UINT CDlgRegister::UpdateRegList()
{
	m_List.DeleteAllItems();
	UINT ret=(UINT)-1;
	IBindCtx* pBindCtx;
 	IRunningObjectTable* prot;
	HRESULT hr = CreateBindCtx (0, &pBindCtx);

	if (SUCCEEDED(hr))
	{
		ret++;
 		hr = pBindCtx->GetRunningObjectTable (&prot);
		if (SUCCEEDED(hr))
		{
			int IdReg=0;
			while (IdReg!=MAX_REGISTERROT)
			{
				if ((m_dwReg[IdReg]!=0xFFFFFFFF) && m_dwRegStr[IdReg]!="")
				{
					m_List.InsertItem(0,m_dwRegStr[IdReg]);
					ret++;
				}
				IdReg++;
			}
			prot->Release();
		}
		pBindCtx->Release();
	}
	return ret;
}

