// GPDlgNewValue.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPDlgNewValue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPDlgNewValue dialog


GPDlgNewValue::GPDlgNewValue(CString iOldValue, CWnd* pParent /*=NULL*/)
	: CDialog(GPDlgNewValue::IDD, pParent)
{
	//{{AFX_DATA_INIT(GPDlgNewValue)
	m_NewValue = iOldValue;
	//}}AFX_DATA_INIT
	OldValue=iOldValue;
}


void GPDlgNewValue::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GPDlgNewValue)
	DDX_Text(pDX, IDC_EDIT1, m_NewValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GPDlgNewValue, CDialog)
	//{{AFX_MSG_MAP(GPDlgNewValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPDlgNewValue message handlers

BOOL GPDlgNewValue::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if (OldValue=="AddItemDlg") 
	{
		SetWindowText("Add new variable");
		m_NewValue=	"";
	}
	else
	if (OldValue=="AddIOFileDlg") 
	{
		SetWindowText("Add new IOFile");
		m_NewValue=	"";
	}
	else		m_NewValue=	OldValue;
	UpdateData(FALSE);

	return TRUE;
}

void GPDlgNewValue::OnOK() 
{
	UpdateData();	
	CDialog::OnOK();
}
