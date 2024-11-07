// DlgTermcap.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgTermcap.h"
#include "DlgTermcapEsc.h"
#include "DlgTermcapKbd.h"
#include "DlgTermcapTerminal.h"
#include "GP_TermView.h"
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
//#include "TermCap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TE_UPDATE_TIMER		0x10

/////////////////////////////////////////////////////////////////////////////
// CDlgTermcap dialog


CDlgTermcap::CDlgTermcap(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTermcap::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTermcap)
	//}}AFX_DATA_INIT
	DlgAutoSize=NULL;
	m_DlgTermcapKbd=NULL;
	m_DlgTermcapEsc=NULL;
	m_DlgTermcapTerminal=NULL;
}

CDlgTermcap::~CDlgTermcap()
{
	if (DlgAutoSize)
		delete DlgAutoSize;
	DlgAutoSize=NULL;
	if (m_DlgTermcapKbd) delete m_DlgTermcapKbd;
	m_DlgTermcapKbd=NULL;
	if (m_DlgTermcapEsc) delete m_DlgTermcapEsc;
	m_DlgTermcapEsc=NULL;
	if (m_DlgTermcapTerminal) delete m_DlgTermcapTerminal;
	m_DlgTermcapTerminal=NULL;
}



void CDlgTermcap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTermcap)
	DDX_Control(pDX, IDC_COMBO1, m_ComboTerminal);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTermcap, CDialog)
	//{{AFX_MSG_MAP(CDlgTermcap)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab)
	ON_BN_CLICKED(IDC_BUTTONCLOSE, OnButtonclose)
	ON_BN_CLICKED(IDC_BUTTONSAVE, OnButtonsave)
	ON_BN_CLICKED(IDC_BUTTONAPPLY, OnButtonapply)
	ON_BN_CLICKED(IDC_BUTTONLOAD, OnButtonload)
	ON_BN_CLICKED(IDC_BUTTONADD, OnButtonadd)
	ON_BN_CLICKED(IDC_BUTTONDELETE, OnButtondelete)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeComboTerminal)
	ON_BN_CLICKED(IDC_BUTTONBROWSETC, OnButtonbrowseTC)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTermcap message handlers

BOOL CDlgTermcap::DestroyWindow()
{
	return CDialog::DestroyWindow();
}

BOOL CDlgTermcap::OnCommand(WPARAM wParam, LPARAM lParam)
{
	BOOL TypeRet=TRUE;
	if (wParam==1) TypeRet=FALSE;
	if (wParam==2)
	{
		TypeRet=FALSE;
		OnButtonclose();
	}

	return TypeRet?CDialog::OnCommand(wParam, lParam):TRUE;
}

LRESULT CDlgTermcap::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	return CDialog::WindowProc(message, wParam, lParam);
}

BOOL CDlgTermcap::OnInitDialog()
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
	m_TmpTermCap=m_TermCap;
	if (m_TmpTermCap.CurrentTerminal==NULL && m_TmpTermCap.m_ArrTerminal)
		m_TmpTermCap.CurrentTerminal=m_TmpTermCap.m_ArrTerminal[0];

	m_DlgTermcapKbd=new CDlgTermcapKbd;
	m_DlgTermcapEsc=new CDlgTermcapEsc;
	m_DlgTermcapTerminal=new CDlgTermcapTerminal;

	m_DlgTermcapKbd->m_pTermCap=&m_TmpTermCap;
	m_DlgTermcapEsc->m_pTermCap=&m_TmpTermCap;
	m_DlgTermcapTerminal->m_pTermCap=&m_TmpTermCap;

	m_DlgTermcapKbd->Create(IDD_DLGTERMCAP_KBD,&m_Tab);
	m_DlgTermcapEsc->Create(IDD_DLGTERMCAP_ESC,&m_Tab);
	m_DlgTermcapTerminal->Create(IDD_DLGTERMCAP_TERMINAL,&m_Tab);

	SetTimer(TE_UPDATE_TIMER,500,NULL);

	CRect re;
	CRect re2;
	m_Tab.GetClientRect(&re);
	re.top+=23;
	re.bottom-=3;
	re.left+=3;
	re.right-=3;

	m_DlgTermcapKbd->MoveWindow(&re);
	m_DlgTermcapEsc->MoveWindow(&re);
	m_DlgTermcapTerminal->MoveWindow(&re);

	DlgAutoSize=new GP_AutoSizing;
	DlgAutoSize->AddSetMain(m_hWnd);
	DlgAutoSize->SetMinSize(m_hWnd,440,330);

	DlgAutoSize->AddWnd(m_DlgTermcapKbd->m_hWnd,m_hWnd,"NNEE");
	DlgAutoSize->AddWnd(m_DlgTermcapEsc->m_hWnd,m_hWnd,"NNEE");
	DlgAutoSize->AddWnd(m_DlgTermcapTerminal->m_hWnd,m_hWnd,"NNEE");
	DlgAutoSize->AddWnd(m_Tab.m_hWnd,m_hWnd,"NNEE");
#ifdef RUS
	m_Tab.InsertItem(0,"Описание терминала",0);
	m_Tab.InsertItem(1,"Esc последовательности",0);
	m_Tab.InsertItem(2,"Назначение клавиш",0);
//	m_Tab.InsertItem(3,"Сравнение",0);
#else
	m_Tab.InsertItem(0,"Terminal Info",0);
	m_Tab.InsertItem(1,"Esc Sequence",0);
	m_Tab.InsertItem(2,"Keyboard Strings",0);
//	m_Tab.InsertItem(3,"Summary",0);
#endif


	DlgAutoSize->AddWnd(m_ComboTerminal.m_hWnd,m_hWnd,"ENEN");

	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTONADD),m_hWnd,"ENEN");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTONDELETE),m_hWnd,"ENEN");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTONAPPLY),m_hWnd,"ENEN");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTONLOAD),m_hWnd,"ENEN");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTONSAVE),m_hWnd,"ENEN");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_STATIC10),m_hWnd,"ENEN");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_STATIC11),m_hWnd,"ENEN");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_EDITKBD),m_hWnd,"ENEN");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTONBROWSETC),m_hWnd,"ENEN");

	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTONCLOSE),m_hWnd,"EEEE");

	m_ComboTerminal.ResetContent();

	if (m_TmpTermCap.m_ArrTerminal)
	{
		UINT i;
		for(i=0;i<m_TmpTermCap.m_uArrTerminalCount;i++)
			if (m_TmpTermCap.m_ArrTerminal[i])
			{
				int itm=m_ComboTerminal.AddString(m_TmpTermCap.m_ArrTerminal[i]->TerminalName);
				if (itm!=CB_ERR)
				{
					m_ComboTerminal.SetItemData(itm,m_TmpTermCap.m_ArrTerminal[i]->dwTermId);
					if (m_TmpTermCap.CurrentTerminal && m_TmpTermCap.CurrentTerminal->dwTermId==m_TmpTermCap.m_ArrTerminal[i]->dwTermId)
						m_ComboTerminal.SetCurSel(itm);
				}
			}
	}
	CWinApp *app=AfxGetApp();
	SetDlgItemText(IDC_EDITKBD,app->GetProfileString(GPC.cs_RegTermViewSetName, "TERMCAPFILE","TERMCAP.TXT"));


	LRESULT res=NULL;
	m_Tab.SetCurSel(0);
	m_Tab.ModifyStyle(0,WS_CLIPSIBLINGS);
	OnSelchangeTab(NULL,&res);
	UpdateAll();

	m_dwUpdateFlag=0;
	if (m_DlgTermcapTerminal) m_DlgTermcapTerminal->m_dwUpdateFlag=0;
	if (m_DlgTermcapEsc) m_DlgTermcapEsc->m_dwUpdateFlag=0;
	if (m_DlgTermcapKbd) m_DlgTermcapKbd->m_dwUpdateFlag=0;

	return TRUE;
}

void CDlgTermcap::OnSize(UINT nType, int cx, int cy)
{
	BOOL DOIT=TRUE;
	if (DlgAutoSize)
		DOIT=DlgAutoSize->CheckMainSize(m_hWnd,nType,&cx, &cy);
	if (DOIT) CDialog::OnSize(nType, cx, cy);
	else Invalidate();

	if (DlgAutoSize)
		try{DlgAutoSize->UpdateSize();}catch(...){GPC.m_ErrReport.GPWriteErrorLog("CDlgTermcap", "OnSize","");
}
}

void CDlgTermcap::OnDestroy()
{
	if (DlgAutoSize)
		delete DlgAutoSize;

	DlgAutoSize=NULL;

	CDialog::OnDestroy();
}


void CDlgTermcap::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (m_DlgTermcapKbd && m_DlgTermcapKbd->m_hWnd)
		m_DlgTermcapKbd->ShowWindow(SW_HIDE);
	if (m_DlgTermcapEsc && m_DlgTermcapEsc->m_hWnd)
		m_DlgTermcapEsc->ShowWindow(SW_HIDE);
	if (m_DlgTermcapTerminal && m_DlgTermcapTerminal->m_hWnd)
		m_DlgTermcapTerminal->ShowWindow(SW_HIDE);

	switch(m_Tab.GetCurSel())
	{
	case 0:
		if (m_DlgTermcapTerminal && m_DlgTermcapTerminal->m_hWnd)
		{
			m_DlgTermcapTerminal->ShowWindow(SW_SHOW);
			m_dwUpdateFlag+=m_DlgTermcapTerminal->m_dwUpdateFlag;
			m_DlgTermcapTerminal->m_dwUpdateFlag=0;
		}
		break;
	case 1:
		if (m_DlgTermcapEsc && m_DlgTermcapEsc->m_hWnd)
		{
			m_DlgTermcapEsc->ShowWindow(SW_SHOW);
			m_dwUpdateFlag+=m_DlgTermcapEsc->m_dwUpdateFlag;
			m_DlgTermcapEsc->m_dwUpdateFlag=0;
		}
		break;
	case 2:
		if (m_DlgTermcapKbd && m_DlgTermcapKbd->m_hWnd)
		{
			m_DlgTermcapKbd->ShowWindow(SW_SHOW);
			m_dwUpdateFlag+=m_DlgTermcapKbd->m_dwUpdateFlag;
			m_DlgTermcapKbd->m_dwUpdateFlag=0;
		}
		break;
	default:
		break;
	}
	*pResult = 0;
}

void CDlgTermcap::OnButtonclose() 
{
	CWinApp *app=AfxGetApp();
	CString iFile;
	GetDlgItemText(IDC_EDITKBD,iFile);
	if  (  iFile!=GPC.TermCapFileName 
		|| m_dwUpdateFlag
		|| (m_DlgTermcapTerminal && m_DlgTermcapTerminal->m_dwUpdateFlag)
		|| (m_DlgTermcapEsc && m_DlgTermcapEsc->m_dwUpdateFlag)
		|| (m_DlgTermcapKbd && m_DlgTermcapKbd->m_dwUpdateFlag)
		)
	{
		CString iDir;
		switch(MessageBox("Save changes?","Termcap Editor",MB_ICONQUESTION|MB_YESNOCANCEL))
		{
		case IDYES:
			if  (	m_dwUpdateFlag
				|| (m_DlgTermcapTerminal && m_DlgTermcapTerminal->m_dwUpdateFlag)
				|| (m_DlgTermcapEsc && m_DlgTermcapEsc->m_dwUpdateFlag)
				|| (m_DlgTermcapKbd && m_DlgTermcapKbd->m_dwUpdateFlag)
				)
			{
				m_TmpTermCap.GetFileName(iDir,iFile,TRUE,m_hWnd);
				m_TmpTermCap.Save(iFile);
			}
			if (GPC.TermCapFileName !=iFile)

			{
				strncpy(GPC.TermCapFileName,iFile,255);
				GPC.TermCapFileName[255]=0;
				
				app->WriteProfileString(GPC.cs_RegTermViewSetName, "TERMCAPFILE",GPC.TermCapFileName);
			}

			OnCancel();
			break;

		case IDNO:
			OnCancel();
			break;
		case IDCANCEL:
			break;
		}
	}
	else OnCancel();
}

void CDlgTermcap::OnButtonsave() 
{
	CString iDir;
	CString iFile=m_TmpTermCap.TCFileName;
	if (m_TmpTermCap.GetFileName(iDir,iFile,TRUE,m_hWnd))
		m_TmpTermCap.Save(iFile);

	OnSelchangeComboTerminal();
	m_dwUpdateFlag=0;
	if (m_DlgTermcapTerminal) m_DlgTermcapTerminal->m_dwUpdateFlag=0;
	if (m_DlgTermcapEsc) m_DlgTermcapEsc->m_dwUpdateFlag=0;
	if (m_DlgTermcapKbd) m_DlgTermcapKbd->m_dwUpdateFlag=0;
}

void CDlgTermcap::OnButtonapply() 
{
	m_TermCap=m_TmpTermCap;
}

void CDlgTermcap::OnButtonload() 
{
	CString iDir;
	CString iFile=m_TmpTermCap.TCFileName;
	if (m_TmpTermCap.GetFileName(iDir,iFile,FALSE,m_hWnd)) 
	{
		m_TmpTermCap.Load(iFile);
		UpdateAll();
		m_dwUpdateFlag=0;
		if (m_DlgTermcapTerminal) m_DlgTermcapTerminal->m_dwUpdateFlag=0;
		if (m_DlgTermcapEsc) m_DlgTermcapEsc->m_dwUpdateFlag=0;
		if (m_DlgTermcapKbd) m_DlgTermcapKbd->m_dwUpdateFlag=0;
	}
}

void CDlgTermcap::OnButtonadd() 
{
	DWORD newId=m_TmpTermCap.GetVacTerminalId();
	PTERMCAPTERMINALITEM pit=m_TmpTermCap.AddTerminalItem();
	if (pit)
	{
		pit->dwTermId=newId;
		pit->TerminalName.Format("Terminal %3.3d",pit->dwTermId);
		pit->Description.Format("Description Terminal %3.3d",pit->dwTermId);
		int it=m_ComboTerminal.AddString(pit->TerminalName);
		if (it!=CB_ERR)
		{
			m_ComboTerminal.SetItemData(it,pit->dwTermId);
			m_ComboTerminal.SetCurSel(it);
			OnSelchangeComboTerminal();
			m_dwUpdateFlag=1;
		}
	}
}

void CDlgTermcap::OnButtondelete() 
{
	int sel=m_ComboTerminal.GetCurSel();
	if (sel!=CB_ERR)
	{
		m_TmpTermCap.DeleteTerminal(m_ComboTerminal.GetItemData(sel));
		m_ComboTerminal.SetCurSel(0);
		OnSelchangeComboTerminal();
		m_dwUpdateFlag=1;
	}
}

void CDlgTermcap::OnSelchangeComboTerminal() 
{
	int sel=m_ComboTerminal.GetCurSel();
	if (sel!=CB_ERR && m_TmpTermCap.m_ArrTerminal)
	{
		DWORD num=m_TmpTermCap.GetTerminalNumById(m_ComboTerminal.GetItemData(sel));
		m_TmpTermCap.CurrentTerminal=m_TmpTermCap.m_ArrTerminal[0];
		if (num<m_TmpTermCap.m_uArrTerminalCount && m_TmpTermCap.m_ArrTerminal[num])
			m_TmpTermCap.CurrentTerminal=m_TmpTermCap.m_ArrTerminal[num];
	}
	else m_ComboTerminal.SetCurSel(0);

	UpdateAll();
}

void CDlgTermcap::UpdateAll()
{
	if (m_DlgTermcapTerminal) m_dwUpdateFlag+=m_DlgTermcapTerminal->m_dwUpdateFlag;
	if (m_DlgTermcapEsc) m_dwUpdateFlag+=m_DlgTermcapEsc->m_dwUpdateFlag;
	if (m_DlgTermcapKbd) m_dwUpdateFlag+=m_DlgTermcapKbd->m_dwUpdateFlag;

	if (m_DlgTermcapKbd) m_DlgTermcapKbd->UpdateInfo();
	if (m_DlgTermcapEsc) m_DlgTermcapEsc->UpdateInfo();
	if (m_DlgTermcapTerminal) m_DlgTermcapTerminal->UpdateInfo();

	if (m_DlgTermcapTerminal) m_DlgTermcapTerminal->m_dwUpdateFlag=0;
	if (m_DlgTermcapEsc) m_DlgTermcapEsc->m_dwUpdateFlag=0;
	if (m_DlgTermcapKbd) m_DlgTermcapKbd->m_dwUpdateFlag=0;
}

void CDlgTermcap::OnButtonbrowseTC() 
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
	opf.lpstrFile = new char [5000];
	*opf.lpstrFile=0;
	opf.nMaxFile =4900;
	opf.lpstrFile[GetDlgItemText(IDC_EDITKBD,opf.lpstrFile,4500)]=0;
	opf.Flags =OFN_DONTADDTORECENT|OFN_CREATEPROMPT|OFN_ENABLESIZING|OFN_EXPLORER|OFN_NOCHANGEDIR|OFN_SHOWHELP|OFN_LONGNAMES|OFN_PATHMUSTEXIST;

#ifdef RUS
	opf.lpstrFilter="Описания Termcap(*.TXT)\x0*.TXT\x0";
#else
	opf.lpstrFilter="Termcap definition file(*.TXT)\x0*.TXT\x0";
#endif
	opf.lpstrDefExt="TXT";


	if (GetOpenFileName(&opf))
	{
		SetDlgItemText(IDC_EDITKBD,opf.lpstrFile);
	}
	delete[] opf.lpstrFile;
}


void CDlgTermcap::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==TE_UPDATE_TIMER)
	{
		BOOL bEnable=(m_DlgTermcapTerminal && m_DlgTermcapTerminal->m_dwUpdateFlag) ||
		(m_DlgTermcapEsc && m_DlgTermcapEsc->m_dwUpdateFlag) ||
		(m_DlgTermcapKbd && m_DlgTermcapKbd->m_dwUpdateFlag);
		m_ComboTerminal.EnableWindow(!bEnable);
	}
	
	CDialog::OnTimer(nIDEvent);
}
