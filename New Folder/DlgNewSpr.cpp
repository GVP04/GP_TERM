// DlgNewSpr.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgNewSpr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNewSpr dialog


CDlgNewSpr::CDlgNewSpr(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNewSpr::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNewSpr)
	m_nFields = 0;
	m_SprName = _T("");
	//}}AFX_DATA_INIT
}


void CDlgNewSpr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNewSpr)
	DDX_Text(pDX, IDC_EDITNFIELDS, m_nFields);
	DDV_MinMaxUInt(pDX, m_nFields, 1, 1000);
	DDX_Text(pDX, IDC_EDITNAME, m_SprName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNewSpr, CDialog)
	//{{AFX_MSG_MAP(CDlgNewSpr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNewSpr message handlers

