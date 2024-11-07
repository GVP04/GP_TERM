// DlgViewFSMethods.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgViewFSMethods.h"
#include "GP_TermDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgViewFSMethods dialog


CDlgViewFSMethods::CDlgViewFSMethods(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewFSMethods::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgViewFSMethods)
	//}}AFX_DATA_INIT
}

void CDlgViewFSMethods::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgViewFSMethods)
	DDX_Control(pDX, IDC_BUTTONMORE, m_BtnMore);
	DDX_Control(pDX, IDC_BTNDELETETEXT, m_BtnClearEvents);
	DDX_Control(pDX, IDC_STATIC5, m_StaticEvents);
	DDX_Control(pDX, IDC_EDITEVENTS, m_EditEvents);
	DDX_Control(pDX, IDC_STATICPARAMS, m_StatParams);
	DDX_Control(pDX, IDC_EDITRESULT, m_EditResult);
	DDX_Control(pDX, IDC_EDITPARAMS, m_EditParams);
	DDX_Control(pDX, IDC_BTNEXECUTE, m_btnExecute);
	DDX_Control(pDX, IDC_COMBOMETHODS, m_ComboMethods);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgViewFSMethods, CDialog)
	//{{AFX_MSG_MAP(CDlgViewFSMethods)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTNEXECUTE, OnBtnexecute)
	ON_CBN_SELCHANGE(IDC_COMBOMETHODS, OnSelchangeCombomethods)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTNDELETETEXT, OnBtndeletetext)
	ON_BN_CLICKED(IDC_BUTTONMORE, OnButtonmore)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgViewFSMethods message handlers

BOOL CDlgViewFSMethods::OnInitDialog()
{
	CDialog::OnInitDialog();
	UINT i;
	for(i=0;*CGP_TermDoc::cArrFSMethods[i];i++)
		m_ComboMethods.AddString(CGP_TermDoc::cArrFSMethods[i]);

	m_ComboMethods.SetCurSel(0);
	OnSelchangeCombomethods();

	AUSI.AddSetMain(this->m_hWnd);
	AUSI.AddWnd(m_btnExecute.m_hWnd,this->m_hWnd	,"NENE");
	AUSI.AddWnd(m_BtnMore.m_hWnd,this->m_hWnd		,"NENE");

	AUSI.AddWnd(m_ComboMethods.m_hWnd,this->m_hWnd	,"NNNE");
	AUSI.AddWnd(m_EditParams.m_hWnd,this->m_hWnd	,"NNNE");
	AUSI.AddWnd(m_StatParams.m_hWnd,this->m_hWnd	,"NNNE");
	AUSI.AddWnd(m_EditResult.m_hWnd,this->m_hWnd	,"NNPE");
	AUSI.AddWnd(m_StaticEvents.m_hWnd,this->m_hWnd	,"PNPN");
	AUSI.AddWnd(m_BtnClearEvents.m_hWnd,this->m_hWnd,"PNPN");
	AUSI.AddWnd(m_EditEvents.m_hWnd,this->m_hWnd	,"PNEE");


	AUSI.SetMinSize(this->m_hWnd,500,150);
	GPC.m_Document->GPCOPYHWND=this->m_hWnd;
	SetTimer(1,2000,NULL);

	return TRUE;
}

void CDlgViewFSMethods::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	AUSI.UpdateSize();
}

void CDlgViewFSMethods::OnBtnexecute()
{
	m_EditResult.SetWindowText("");
	CString str;
	CString strMeth;
	CString strParam;
	m_ComboMethods.GetWindowText(strMeth);
	m_EditParams.GetWindowText(strParam);
	str=strMeth+" "+strParam;

	char *oStr=NULL;
	GPC.m_Document->DoFileSystemMethod(str,&oStr);
	if (oStr)
	{
		m_csLastResult=oStr;
		m_EditResult.SetWindowText(oStr);
		delete[] oStr;
	}
}

void CDlgViewFSMethods::OnSelchangeCombomethods()
{
	CString str;
	m_ComboMethods.GetWindowText(str);
	UINT i;
	for(i=0;*CGP_TermDoc::cArrFSMethods[i];i++)
		if (str==CGP_TermDoc::cArrFSMethods[i]) break;
	m_StatParams.SetWindowText(CGP_TermDoc::cArrFSMethodsParams[i]);
}

void CDlgViewFSMethods::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);
	switch(nIDEvent)
	{
	case 1:
		ModifyStyle(WS_DISABLED,0);
		break;
	}

}

void CDlgViewFSMethods::OnBtndeletetext()
{
	m_EditEvents.SetSel(0,-1);
	m_EditEvents.ReplaceSel("");
}

LRESULT CDlgViewFSMethods::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case GPM_SETANDDELETESTRING:
		if (lParam)
		{
			m_EditEvents.SetSel(-1,-1);
			m_EditEvents.ReplaceSel((char *)lParam);
			if (wParam!=0)
				delete[] (char *)lParam;
		}
	}

	return CDialog::WindowProc(message, wParam, lParam);
}

#include "DlgViewItem.h"

void CDlgViewFSMethods::OnButtonmore()
{
	CDlgViewItem dlg(m_csLastResult,127,7,this);
	dlg.DoModal();
}


void CDlgViewFSMethods::OnDestroy()
{
	GPC.m_Document->GPCOPYHWND=NULL;
	CDialog::OnDestroy();
}

BOOL CDlgViewFSMethods::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (wParam!=1 || lParam!=0) return CDialog::OnCommand(wParam, lParam);

	if (wParam==1) OnBtnexecute();

	return FALSE;
}
