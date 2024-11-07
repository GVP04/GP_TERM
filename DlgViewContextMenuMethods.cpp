// DlgViewContextMenuMethods.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgViewContextMenuMethods.h"
#include "GPContextMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgViewContextMenuMethods dialog


CDlgViewContextMenuMethods::CDlgViewContextMenuMethods(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewContextMenuMethods::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgViewContextMenuMethods)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgViewContextMenuMethods::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgViewContextMenuMethods)
	DDX_Control(pDX, IDC_BTNEXECUTE2, m_btnExecute2);
	DDX_Control(pDX, IDC_COMBOMETHODS, m_ComboMethods);
	DDX_Control(pDX, IDC_BTNEXECUTE, m_btnExecute);
	DDX_Control(pDX, IDC_EDITPARAMS, m_EditParams);
	DDX_Control(pDX, IDC_EDITRESULT, m_EditResult);
	DDX_Control(pDX, IDC_STATICPARAMS, m_StatParams);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgViewContextMenuMethods, CDialog)
	//{{AFX_MSG_MAP(CDlgViewContextMenuMethods)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTNEXECUTE, OnBtnexecute)
	ON_CBN_SELCHANGE(IDC_COMBOMETHODS, OnSelchangeCombomethods)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTNEXECUTE2, OnBtnexecute2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgViewContextMenuMethods message handlers

BOOL CDlgViewContextMenuMethods::OnInitDialog()
{
	CDialog::OnInitDialog();
	UINT i;
	for(i=0;i<CGPContextMenu::uNMethods;i++)
		m_ComboMethods.AddString(CGPContextMenu::cArrMethods[i]);

	m_ComboMethods.SetCurSel(0);
	OnSelchangeCombomethods();

	AUSI.AddSetMain(this->m_hWnd);
	AUSI.AddWnd(m_btnExecute.m_hWnd,this->m_hWnd	,"NENE");
	AUSI.AddWnd(m_btnExecute2.m_hWnd,this->m_hWnd	,"NENE");

	AUSI.AddWnd(m_ComboMethods.m_hWnd,this->m_hWnd	,"NNNE");
	AUSI.AddWnd(m_EditParams.m_hWnd,this->m_hWnd	,"NNNE");
	AUSI.AddWnd(m_StatParams.m_hWnd,this->m_hWnd	,"NNNE");
	AUSI.AddWnd(m_EditResult.m_hWnd,this->m_hWnd	,"NNEE");

	AUSI.SetMinSize(this->m_hWnd,450,150);

	GPC.SetIconFromIL(m_hWnd, "SEPVIEW", 44);

	return TRUE;
}

void CDlgViewContextMenuMethods::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	AUSI.UpdateSize();
}

void CDlgViewContextMenuMethods::OnBtnexecute()
{
	m_EditResult.SetWindowText("");
	CString str;
	CString strMeth;
	CString strParam;
	m_ComboMethods.GetWindowText(strMeth);
	m_EditParams.GetWindowText(strParam);
	str=strMeth+" "+strParam;

	char *oStr=new char [50000];
	*oStr=0;
	GPC.m_pContextMenu->DoMethod(str,oStr);
	m_EditResult.SetWindowText(oStr);
	delete[] oStr;
}

void CDlgViewContextMenuMethods::OnSelchangeCombomethods()
{
	CString str;
	m_ComboMethods.GetWindowText(str);
	UINT i;
	for(i=0;i<CGPContextMenu::uNMethods;i++)
		if (str==CGPContextMenu::cArrMethods[i]) break;
	m_StatParams.SetWindowText(CGPContextMenu::cArrMethodsParams[i]);
}

void CDlgViewContextMenuMethods::OnDestroy()
{
	CDialog::OnDestroy();
}

BOOL CDlgViewContextMenuMethods::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (wParam!=1 || lParam!=0) return CDialog::OnCommand(wParam, lParam);

	if (wParam==1)
	{
		HWND fcs=::GetFocus();
		if (fcs==::GetDlgItem(m_hWnd,IDC_EDITPARAMS) || fcs==::GetDlgItem(m_hWnd,IDC_BTNEXECUTE))
			OnBtnexecute();
		else
		if (fcs==::GetDlgItem(m_hWnd,IDC_EDITPARAMS) || fcs==::GetDlgItem(m_hWnd,IDC_BTNEXECUTE2))
			OnBtnexecute2();
	}

	return CDialog::OnCommand(wParam, lParam);
}

void CDlgViewContextMenuMethods::OnBtnexecute2()
{
	if (GPC.m_pContextMenu && GPC.m_pContextMenu->m_Menu)
	{
		RECT re={0};
		m_btnExecute2.GetWindowRect(&re);
		TrackPopupMenu(GPC.m_pContextMenu->m_Menu,TPM_RIGHTBUTTON|TPM_TOPALIGN|TPM_LEFTALIGN|TPM_HORNEGANIMATION,re.left,re.bottom,0,GPC.m_hViewWnd,NULL);
	}
}
