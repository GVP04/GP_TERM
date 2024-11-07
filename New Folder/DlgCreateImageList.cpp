// DlgCreateImageList.cpp : implementation file
//

#include "stdafx.h"
#include "GP_Term.h"
#include "DlgCreateImageList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateImageList dialog


CDlgCreateImageList::CDlgCreateImageList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCreateImageList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCreateImageList)
	m_EdY = 0;
	m_EdX = 0;
	m_EdInit = 0;
	m_EdDelta = 0;
	m_S2 = FALSE;
	m_S3 = FALSE;
	m_S4 = FALSE;
	m_S5 = FALSE;
	m_S6 = FALSE;
	m_S7 = FALSE;
	m_S8 = FALSE;
	m_S9 = FALSE;
	m_S10 = FALSE;
	m_Name = _T("noname");
	//}}AFX_DATA_INIT
}


void CDlgCreateImageList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCreateImageList)
	DDX_Control(pDX, IDC_OK, m_BtnOk);
	DDX_Control(pDX, IDC_SPIN4, m_SP4);
	DDX_Control(pDX, IDC_SPIN3, m_SP3);
	DDX_Control(pDX, IDC_SPIN2, m_SP2);
	DDX_Control(pDX, IDC_SPIN1, m_SP1);
	DDX_Text(pDX, IDC_EDIT2, m_EdY);
	DDV_MinMaxUInt(pDX, m_EdY, 0, 1000);
	DDX_Text(pDX, IDC_EDIT1, m_EdX);
	DDV_MinMaxUInt(pDX, m_EdX, 0, 1000);
	DDX_Text(pDX, IDC_EDIT3, m_EdInit);
	DDV_MinMaxUInt(pDX, m_EdInit, 0, 1000);
	DDX_Text(pDX, IDC_EDIT4, m_EdDelta);
	DDV_MinMaxUInt(pDX, m_EdDelta, 0, 32);
	DDX_Check(pDX, IDC_CHECK2, m_S2);
	DDX_Check(pDX, IDC_CHECK3, m_S3);
	DDX_Check(pDX, IDC_CHECK4, m_S4);
	DDX_Check(pDX, IDC_CHECK5, m_S5);
	DDX_Check(pDX, IDC_CHECK6, m_S6);
	DDX_Check(pDX, IDC_CHECK7, m_S7);
	DDX_Check(pDX, IDC_CHECK8, m_S8);
	DDX_Text(pDX, IDC_EDIT5, m_Name);
	DDX_Check(pDX, IDC_CHECK10, m_S10);
	DDX_Check(pDX, IDC_CHECK9, m_S9);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCreateImageList, CDialog)
	//{{AFX_MSG_MAP(CDlgCreateImageList)
	ON_BN_CLICKED(IDC_OK, OnOk)
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEditName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateImageList message handlers

BOOL CDlgCreateImageList::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_SP1.SetRange32(0,1000);
	m_SP2.SetRange32(0,1000);
	m_SP3.SetRange32(0,1000);
	m_SP4.SetRange32(0,32);

	SetCreateFlag(dwCreateFlag);

	::SetFocus(::GetDlgItem(m_hWnd,IDC_EDIT5));

	return TRUE;
}

LRESULT CDlgCreateImageList::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	return CDialog::WindowProc(message, wParam, lParam);
}

BOOL CDlgCreateImageList::OnCommand(WPARAM wParam, LPARAM lParam)
{
	BOOL TypeRet=TRUE;
	if (wParam!=1/* || lParam*/) TypeRet=FALSE;

	HWND tmpf=::GetFocus();
	if (TypeRet && tmpf)
	{
		if (tmpf==::GetDlgItem(m_hWnd,IDC_OK))
		{
			if ((m_BtnOk.GetStyle()&WS_DISABLED)!=WS_DISABLED) CDialog::OnOK();
			else	TypeRet=FALSE;
		}
		else
		{
			HWND tmpnext=::GetNextDlgTabItem(m_hWnd,tmpf,FALSE);
			if (tmpnext)
				GotoDlgCtrl(CWnd::FromHandle(tmpnext));
		}
	}
	return TypeRet?TRUE:CDialog::OnCommand(wParam, lParam);
}

void CDlgCreateImageList::OnCancel()
{
	CDialog::OnCancel();
}

void CDlgCreateImageList::OnOk()
{
	GetCreateFlag();
	CDialog::OnOK();
}

void CDlgCreateImageList::OnChangeEditName()
{
	CString tmps;
	GetDlgItemText(IDC_EDIT5,tmps);
	if (tmps=="")
		m_BtnOk.ModifyStyle(0,WS_DISABLED);
	else
		m_BtnOk.ModifyStyle(WS_DISABLED,0);
	m_BtnOk.Invalidate();
}

DWORD CDlgCreateImageList::GetCreateFlag()
{
	if (m_hWnd)
	{
		dwCreateFlag=0;
		if (::IsDlgButtonChecked(m_hWnd,IDC_CHECK2))	dwCreateFlag|=ILC_COLOR4;
		if (::IsDlgButtonChecked(m_hWnd,IDC_CHECK3))	dwCreateFlag|=ILC_COLOR8;
		if (::IsDlgButtonChecked(m_hWnd,IDC_CHECK4))	dwCreateFlag|=ILC_COLOR16;
		if (::IsDlgButtonChecked(m_hWnd,IDC_CHECK5))	dwCreateFlag|=ILC_COLOR24;
		if (::IsDlgButtonChecked(m_hWnd,IDC_CHECK6))	dwCreateFlag|=ILC_COLOR32;
		if (::IsDlgButtonChecked(m_hWnd,IDC_CHECK7))	dwCreateFlag|=ILC_COLORDDB;
		if (::IsDlgButtonChecked(m_hWnd,IDC_CHECK8))	dwCreateFlag|=ILC_MASK;
		if (::IsDlgButtonChecked(m_hWnd,IDC_CHECK9))	dwCreateFlag|=ILC_MIRROR;
		if (::IsDlgButtonChecked(m_hWnd,IDC_CHECK10))	dwCreateFlag|=ILC_PERITEMMIRROR;
	}
	return dwCreateFlag;
}

DWORD CDlgCreateImageList::SetCreateFlag(DWORD idwCreateFlag)
{
	DWORD ret=dwCreateFlag;
	dwCreateFlag=idwCreateFlag;

	if (m_hWnd)
	{
		::CheckDlgButton(m_hWnd,IDC_CHECK2,(dwCreateFlag&ILC_COLOR4)==ILC_COLOR4);
		::CheckDlgButton(m_hWnd,IDC_CHECK3,(dwCreateFlag&ILC_COLOR8)==ILC_COLOR8);
		::CheckDlgButton(m_hWnd,IDC_CHECK4,(dwCreateFlag&ILC_COLOR16)==ILC_COLOR16);
		::CheckDlgButton(m_hWnd,IDC_CHECK5,(dwCreateFlag&ILC_COLOR24)==ILC_COLOR24);
		::CheckDlgButton(m_hWnd,IDC_CHECK6,(dwCreateFlag&ILC_COLOR32)==ILC_COLOR32);
		::CheckDlgButton(m_hWnd,IDC_CHECK7,(dwCreateFlag&ILC_COLORDDB)==ILC_COLORDDB);
		::CheckDlgButton(m_hWnd,IDC_CHECK8,(dwCreateFlag&ILC_MASK)==ILC_MASK);
		::CheckDlgButton(m_hWnd,IDC_CHECK9,(dwCreateFlag&ILC_MIRROR)==ILC_MIRROR);
		::CheckDlgButton(m_hWnd,IDC_CHECK10,(dwCreateFlag&ILC_PERITEMMIRROR)==ILC_PERITEMMIRROR);
	}

	return ret;
}
