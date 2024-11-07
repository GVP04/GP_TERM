// ProgressDialog.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "ProgressDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ProgressDialog dialog


ProgressDialog::ProgressDialog(CWnd* pParent /*=NULL*/)
	: CDialog(ProgressDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(ProgressDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ProgressDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ProgressDialog)
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ProgressDialog, CDialog)
	//{{AFX_MSG_MAP(ProgressDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ProgressDialog message handlers

void ProgressDialog::SetProgressRange(int iStart, int iEnd)
{
	m_Progress.SetRange32(iStart,iEnd);
}

void ProgressDialog::SetProgressPos(int iPos)
{
	m_Progress.SetPos(iPos);
}
