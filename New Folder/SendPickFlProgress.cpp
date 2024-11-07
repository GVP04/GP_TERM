// SendPickFlProgress.cpp : implementation file
//

#include "stdafx.h"
#include "GP_term.h"
#include "SendPickFlProgress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SendPickFlProgress dialog


SendPickFlProgress::SendPickFlProgress(CWnd* pParent /*=NULL*/)
	: CDialog(SendPickFlProgress::IDD, pParent)
{
	//{{AFX_DATA_INIT(SendPickFlProgress)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SendPickFlProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SendPickFlProgress)
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SendPickFlProgress, CDialog)
	//{{AFX_MSG_MAP(SendPickFlProgress)
	ON_WM_CHAR()
	ON_WM_CLOSE()
	ON_COMMAND(ID_ALT_B, OnAltB)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SendPickFlProgress message handlers

BOOL SendPickFlProgress::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_progress.SetStep(1);
	return TRUE;
}

void SendPickFlProgress::OnOK() 
{
//	CDialog::OnOK();
}

void SendPickFlProgress::OnCancel() 
{
//	CDialog::OnCancel();
}

void SendPickFlProgress::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	//CDialog::OnChar(nChar, nRepCnt, nFlags);
}

void SendPickFlProgress::GPClose()
{
	CDialog::OnClose();
}

void SendPickFlProgress::OnClose() 
{
	GPClose();
}

void SendPickFlProgress::OnAltB() 
{
#ifdef BRIZ
	if (AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "BRIZINITA",1) &&
#else
	if (AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "INITA",0) &&
#endif
#ifdef RUS
	MessageBox("Остановить процесс передачи данных?",GPC.MsgBoxCaption,MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2)==IDYES) GPClose();
#else
	MessageBox("Stop sending data?",GPC.MsgBoxCaption,MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2)==IDYES) GPClose();
#endif
}

void SendPickFlProgress::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
#ifdef RUS
	if (point.x<2 && point.y<2 && MessageBox("Закрыть диалог без сохранения данных?",GPC.MsgBoxCaption,MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2)==IDYES) GPClose();
#else
	if (point.x<2 && point.y<2 && MessageBox("Close Dialog and discard changes?",GPC.MsgBoxCaption,MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2)==IDYES) GPClose();
#endif
	else	CDialog::OnLButtonDblClk(nFlags, point);
}

void SendPickFlProgress::OnTimer(UINT nIDEvent) 
{
	CDialog::OnTimer(nIDEvent);
}
