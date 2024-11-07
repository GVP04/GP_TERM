// DlgInitComObject.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgInitComObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInitComObject dialog


CDlgInitComObject::CDlgInitComObject(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInitComObject::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInitComObject)
	m_EditCLSID = _T("");
	//}}AFX_DATA_INIT
}


void CDlgInitComObject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInitComObject)
	DDX_Text(pDX, IDC_EDITCLSID, m_EditCLSID);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgInitComObject, CDialog)
	//{{AFX_MSG_MAP(CDlgInitComObject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInitComObject message handlers

void CDlgInitComObject::OnOK()
{
	CDialog::OnOK();
}
