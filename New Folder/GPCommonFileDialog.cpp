// GPCommonFileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPCommonFileDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPCommonFileDialog

IMPLEMENT_DYNAMIC(GPCommonFileDialog, CFileDialog)

GPCommonFileDialog::GPCommonFileDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
}


BEGIN_MESSAGE_MAP(GPCommonFileDialog, CFileDialog)
	//{{AFX_MSG_MAP(GPCommonFileDialog)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL GPCommonFileDialog::OnInitDialog() 
{
	CFileDialog::OnInitDialog();
	SetTimer(1,10,0);	
	SetForegroundWindow();
	return TRUE;
}

void GPCommonFileDialog::OnTimer(UINT nIDEvent) 
{
	KillTimer(nIDEvent);
	CFileDialog::OnTimer(nIDEvent);

	CWnd *tmp;
	CString str;
	CRect re;
	GetClientRect(&re);
	ClientToScreen(&re);
	int i,j,endy=re.top+500;

	for(i=re.left;i<re.left+500;i+=50)
		for(j=re.top;j<endy;j+=10)
			if ((tmp=WindowFromPoint(CPoint(i,j)))!=NULL)
			{
				tmp->GetWindowText(str);
				if (str=="Open_Dir")
				{
					tmp->EnableWindow(FALSE);
					break;
				}
			}
}
