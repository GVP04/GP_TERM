// GPCommonFontDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPCommonFontDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPCommonFontDlg

IMPLEMENT_DYNAMIC(GPCommonFontDlg, CFontDialog)

GPCommonFontDlg::GPCommonFontDlg(LPLOGFONT lplfInitial, DWORD dwFlags, CDC* pdcPrinter, CWnd* pParentWnd) : 
	CFontDialog(lplfInitial, dwFlags, pdcPrinter, pParentWnd)
{
}


BEGIN_MESSAGE_MAP(GPCommonFontDlg, CFontDialog)
	//{{AFX_MSG_MAP(GPCommonFontDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL GPCommonFontDlg::OnInitDialog() 
{
	CFontDialog::OnInitDialog();
	
	SetForegroundWindow();
	
	return TRUE;
}
