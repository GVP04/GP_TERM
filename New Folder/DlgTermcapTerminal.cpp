// DlgTermcapTerminal.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgTermcapTerminal.h"
#ifdef W_95
#else
	#ifdef W_NT
	#else
		#ifdef W_98
		#else
			#ifdef W_2000
			#else
#include "uxtheme.h"
			#endif
		#endif
	#endif
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTermcapTerminal dialog


CDlgTermcapTerminal::CDlgTermcapTerminal(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTermcapTerminal::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTermcapTerminal)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	DlgAutoSize=NULL;
	m_pTermCap=NULL;
	m_dwUpdateFlag=0;
}

CDlgTermcapTerminal::~CDlgTermcapTerminal()
{
	if (DlgAutoSize)
		delete DlgAutoSize;
}

void CDlgTermcapTerminal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTermcapTerminal)
	DDX_Control(pDX, IDC_EDIT3, m_EditDescription);
	DDX_Control(pDX, IDC_EDIT2, m_EditNames);
	DDX_Control(pDX, IDC_EDIT1, m_EditName);
	DDX_Control(pDX, IDC_COMBO1, m_ComboId);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTermcapTerminal, CDialog)
	//{{AFX_MSG_MAP(CDlgTermcapTerminal)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEditDescription)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEditNames)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEditName)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeComboId)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTermcapTerminal message handlers

void CDlgTermcapTerminal::OnDestroy() 
{
	if (DlgAutoSize)
		delete DlgAutoSize;

	DlgAutoSize=NULL;

	CDialog::OnDestroy();
}

BOOL CDlgTermcapTerminal::OnInitDialog() 
{
	CDialog::OnInitDialog();
	#ifdef W_95
	#else
		#ifdef W_NT
		#else
			#ifdef W_98
			#else
				#ifdef W_2000
				#else
				EnableThemeDialogTexture(m_hWnd,ETDT_USETABTEXTURE);
				Invalidate();
				#endif
			#endif
		#endif
	#endif

	DlgAutoSize=new GP_AutoSizing;
	DlgAutoSize->AddSetMain(m_hWnd);
	DlgAutoSize->SetMinSize(m_hWnd,200,150);

	DlgAutoSize->AddWnd(m_EditNames.m_hWnd,m_hWnd,"NNNE");
	DlgAutoSize->AddWnd(m_EditDescription.m_hWnd,m_hWnd,"NNEE");

	m_dwUpdateFlag=0;

	return TRUE;
}

void CDlgTermcapTerminal::OnSize(UINT nType, int cx, int cy) 
{
	BOOL DOIT=TRUE;
	if (DlgAutoSize)
		DOIT=DlgAutoSize->CheckMainSize(m_hWnd,nType,&cx, &cy);
	if (DOIT)
		CDialog::OnSize(nType, cx, cy);
	else 
		if (cx>0 && cy>0) Invalidate();

	if (DlgAutoSize)
		try{DlgAutoSize->UpdateSize();}catch(...){			GPC.m_ErrReport.GPWriteErrorLog("", "","");}
}

BOOL CDlgTermcapTerminal::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	BOOL TypeRet=TRUE;
	if (wParam==1) TypeRet=FALSE;

	return TypeRet?CDialog::OnCommand(wParam, lParam):TRUE;
}

void CDlgTermcapTerminal::UpdateInfo()
{

	if (m_pTermCap && m_pTermCap->CurrentTerminal)
	{
		m_dwUpdateFlag=0;
		m_EditDescription.SetWindowText(m_pTermCap->CurrentTerminal->Description);
		m_EditNames.SetWindowText(m_pTermCap->CurrentTerminal->AlternateNames);
		m_EditName.SetWindowText(m_pTermCap->CurrentTerminal->TerminalName);
		m_ComboId.ResetContent();

		char tmps[22];
		int i;
		int ids[256];
		for(i=0;i<256;i++)
		{
			ids[i]=0;
			sprintf(tmps,"%4.4d",i);
			int itm=m_ComboId.AddString(tmps);
			if (itm!=CB_ERR)
				m_ComboId.SetItemData(itm,i);
		}

		m_ComboId.SetCurSel(m_pTermCap->CurrentTerminal->dwTermId);

		UINT k;
		for(k=0;k<m_pTermCap->m_uArrTerminalCount;k++)
			if (m_pTermCap->m_ArrTerminal[k] && m_pTermCap->m_ArrTerminal[k]->dwTermId<256 && m_pTermCap->m_ArrTerminal[k]->dwTermId!=m_pTermCap->CurrentTerminal->dwTermId)
				ids[k]=1;

		for(i=255;i>=0;i--)
			if (ids[i]==1)
				m_ComboId.DeleteString(i);

		if (m_pTermCap->CurrentTerminal->dwTermId==0)
			m_ComboId.ModifyStyle(WS_VISIBLE,0);
		else
			m_ComboId.ModifyStyle(0,WS_VISIBLE);
			
	}
}

void CDlgTermcapTerminal::OnChangeEditDescription() 
{
	if (m_pTermCap && m_pTermCap->CurrentTerminal)
	{
		m_EditDescription.GetWindowText(m_pTermCap->CurrentTerminal->Description);
		m_dwUpdateFlag=1;
	}
}

void CDlgTermcapTerminal::OnChangeEditNames() 
{
	if (m_pTermCap && m_pTermCap->CurrentTerminal)
	{
		m_EditNames.GetWindowText(m_pTermCap->CurrentTerminal->AlternateNames);
		m_dwUpdateFlag=1;
	}
}

void CDlgTermcapTerminal::OnChangeEditName() 
{
	if (m_pTermCap && m_pTermCap->CurrentTerminal)
	{
		m_EditName.GetWindowText(m_pTermCap->CurrentTerminal->TerminalName);
		m_dwUpdateFlag=1;
	}
}

void CDlgTermcapTerminal::OnSelchangeComboId() 
{
	if (m_pTermCap && m_pTermCap->CurrentTerminal)
	{
		DWORD iOldId=m_pTermCap->CurrentTerminal->dwTermId;
		int sel=m_ComboId.GetCurSel();
		if (sel!=CB_ERR)
		{
			DWORD iNewId=m_ComboId.GetItemData(sel);
			m_pTermCap->ChangeTerminalId(iOldId,iNewId);
		}
	}
}
