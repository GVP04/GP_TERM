// DlgFileItemName.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgFileItemName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFileItemName dialog


CDlgFileItemName::CDlgFileItemName(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFileItemName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFileItemName)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgFileItemName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFileItemName)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFileItemName, CDialog)
	//{{AFX_MSG_MAP(CDlgFileItemName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFileItemName message handlers

BOOL CDlgFileItemName::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_hWnd)
	{
		SetDlgItemText(IDC_EDITFILE,m_FileName);
		SetDlgItemText(IDC_EDITITEM,m_ItemName);
	}
	return TRUE;
}

void CDlgFileItemName::OnCancel()
{
	CDialog::OnCancel();
}

void CDlgFileItemName::OnOK()
{
	if (m_hWnd)
	{
		GetDlgItemText(IDC_EDITFILE,m_FileName);
		GetDlgItemText(IDC_EDITITEM,m_ItemName);
	}

	if (m_FileName!="" && m_ItemName!="")
		CDialog::OnOK();
}

const CString CDlgFileItemName::GetFileName()
{
	return m_FileName;
}

const CString CDlgFileItemName::GetItemName()
{
	return m_ItemName;
}

const CString CDlgFileItemName::SetFileName(const char * iName)
{
	CString ret=m_FileName;
	m_FileName=iName;
	if (m_hWnd)
		SetDlgItemText(IDC_EDITFILE,iName);
	return ret;
}

const CString CDlgFileItemName::SetItemName(const char * iName)
{
	CString ret=m_ItemName;
	m_ItemName=iName;
	if (m_hWnd)
		SetDlgItemText(IDC_EDITITEM,iName);
	return ret;
}

BOOL CDlgFileItemName::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (wParam!=1)
		return CDialog::OnCommand(wParam, lParam);

	HWND tmpf=::GetFocus();
	if (tmpf)
	{
		GetDlgItemText(IDC_EDITFILE,m_FileName);
		GetDlgItemText(IDC_EDITITEM,m_ItemName);
		if (tmpf==::GetDlgItem(m_hWnd,IDOK) && m_FileName!="" && m_ItemName!="")
		{
			return CDialog::OnCommand(wParam, lParam);
		}
		else
		{
			HWND tmpnext=::GetNextDlgTabItem(m_hWnd,tmpf,FALSE);
			if (tmpnext)
				GotoDlgCtrl(CWnd::FromHandle(tmpnext));
		}
	}
	return TRUE;
}
