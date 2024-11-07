// GPNotifyEdit.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPNotifyEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGPNotifyEdit

CGPNotifyEdit::CGPNotifyEdit()
{
	m_hNotifyWnd=NULL;
	m_UpdateFlag=0;
}

CGPNotifyEdit::~CGPNotifyEdit()
{
}


BEGIN_MESSAGE_MAP(CGPNotifyEdit, CEdit)
	//{{AFX_MSG_MAP(CGPNotifyEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_SHOWWINDOW()
	ON_WM_ACTIVATE()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGPNotifyEdit message handlers

void CGPNotifyEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (PtInEdit(point)==0)
	{
		ReleaseMyCapture();
	}
	else 
		CEdit::OnLButtonDown(nFlags, point);
}

void CGPNotifyEdit::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if (PtInEdit(point)==0)
	{
		ReleaseMyCapture();
	}
	else 
		CEdit::OnRButtonDown(nFlags, point);
}

HWND CGPNotifyEdit::SetNotifyWnd(HWND hWnd)
{
	HWND ret=m_hNotifyWnd;
	if (hWnd) m_hNotifyWnd=hWnd;
	return ret;
}

DWORD CGPNotifyEdit::PtInEdit(CPoint point)
{
	if (m_hWnd && m_hNotifyWnd==NULL)
		m_hNotifyWnd=::GetParent(m_hWnd);
	CRect re;
	GetWindowRect(&re);
	ScreenToClient(&re);
	return re.PtInRect(point);
}

void CGPNotifyEdit::OnSetFocus(CWnd* pOldWnd) 
{
	m_UpdateFlag=1;
	CEdit::OnSetFocus(pOldWnd);
	ModifyStyle(0,WS_VISIBLE);
	GetParent()->Invalidate();
	SetMyCapture();
}

void CGPNotifyEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);
	ReleaseMyCapture();
}

void CGPNotifyEdit::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CEdit::OnShowWindow(bShow, nStatus);
	
	if (m_hWnd && m_hNotifyWnd==NULL)
		m_hNotifyWnd=::GetParent(m_hWnd);
	
}

void CGPNotifyEdit::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CEdit::OnActivate(nState, pWndOther, bMinimized);
	SetMyCapture();	
}

void CGPNotifyEdit::OnMouseMove(UINT nFlags, CPoint point) 
{
	SetMyCapture();
	CEdit::OnMouseMove(nFlags, point);
}

void CGPNotifyEdit::SetMyCapture()
{
	if (::GetCapture()!=m_hWnd) ::SetCapture(m_hWnd);
}

void CGPNotifyEdit::ReleaseMyCapture()
{
	if (m_UpdateFlag)
	{
		m_UpdateFlag=0;
		if (::GetCapture()==m_hWnd) ::ReleaseCapture();
		ModifyStyle(WS_VISIBLE,0);
		GetParent()->Invalidate();
		CString tmps;
		GetWindowText(tmps);
		::SendMessage(m_hNotifyWnd,GPNE_ENDEDIT,0,((LPARAM)(LPCSTR)tmps));
	}
}
