// GPCommonColorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPCommonColorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPCommonColorDlg

IMPLEMENT_DYNAMIC(GPCommonColorDlg, CColorDialog)

GPCommonColorDlg::GPCommonColorDlg(COLORREF clrInit, DWORD dwFlags, CWnd* pParentWnd) :
	CColorDialog(clrInit, dwFlags, pParentWnd)
{
}


BEGIN_MESSAGE_MAP(GPCommonColorDlg, CColorDialog)
	//{{AFX_MSG_MAP(GPCommonColorDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL GPCommonColorDlg::OnInitDialog() 
{
	CColorDialog::OnInitDialog();
	SetForegroundWindow();
	
	return TRUE;
}
