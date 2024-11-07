// DlgSeparateViewInFrame.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgSeparateViewInFrame.h"
#include "DlgViewInputAll.h"
#include "DlgViewOutput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSeparateViewInFrame dialog


CDlgSeparateViewInFrame::CDlgSeparateViewInFrame(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSeparateViewInFrame::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSeparateViewInFrame)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_DlgViewInputAll=NULL;
	m_DlgViewOutput=NULL;
}


void CDlgSeparateViewInFrame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSeparateViewInFrame)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSeparateViewInFrame, CDialog)
	//{{AFX_MSG_MAP(CDlgSeparateViewInFrame)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSeparateViewInFrame message handlers

BOOL CDlgSeparateViewInFrame::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}

void CDlgSeparateViewInFrame::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	FrameSizeMove();

	if (m_hWnd && cx>0 && cy>0)
	{
		if (m_DlgViewInputAll && m_DlgViewOutput && m_DlgViewInputAll->m_hWnd && m_DlgViewOutput->m_hWnd)
		{
			CSize tmpsz(cx,cy);
//			tmpsz=sz;
			m_DlgViewInputAll->SetSize(tmpsz);
			m_DlgViewOutput->SetSize(tmpsz);
		}
	}

}

void CDlgSeparateViewInFrame::OnDestroy()
{
	if (m_DlgViewInputAll && m_DlgViewInputAll->m_hWnd)
	{
		if (::GetParent(m_DlgViewInputAll->m_hWnd)==m_hWnd)
			::DestroyWindow(m_DlgViewInputAll->m_hWnd);
	}
	if (m_DlgViewOutput && m_DlgViewOutput->m_hWnd)
	{
		if (::GetParent(m_DlgViewOutput->m_hWnd)==m_hWnd)
			::DestroyWindow(m_DlgViewOutput->m_hWnd);
	}

	CDialog::OnDestroy();

}

void CDlgSeparateViewInFrame::FrameSizeMove()
{
	if (m_hWnd)
	{
		CRect re;
		::GetClientRect(GPC.m_hViewWnd,&re);
		if (re!=m_FrameLastSize)
			MoveWindow(&re);
		if (m_DlgViewOutput && m_DlgViewInputAll) m_FrameLastSize=re;
		ResizeDialogs(re.Size());
	}
}

void CDlgSeparateViewInFrame::ResizeDialogs(CSize &sz)
{
	if (m_hWnd && sz.cx>0 && sz.cy>0)
	{
		if (m_DlgViewInputAll && m_DlgViewOutput && m_DlgViewInputAll->m_hWnd && m_DlgViewOutput->m_hWnd)
		{
			CSize tmpsz;
			tmpsz=sz;
			m_DlgViewInputAll->SetSize(tmpsz);
			m_DlgViewOutput->SetSize(tmpsz);
		}
	}
}


LRESULT CDlgSeparateViewInFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == GPN_UPDATESIZE)
	{
		switch(wParam)
		{
		case SCCMND_WNDSIZE+0x10000:
			m_DlgViewInputAll->SwitchIVSize(SCCMND_WNDSIZE);
			break;
		case SCCMND_WNDSIZE2+0x10000:
			m_DlgViewInputAll->SwitchIVSize(SCCMND_WNDSIZE2);
			break;
		default:
			{
				CRect re;
				::GetClientRect(m_hWnd,&re);
				OnSize(0,re.Width(),re.Height());
			}
		}
	}

	return CDialog::WindowProc(message, wParam, lParam);
}

BOOL CDlgSeparateViewInFrame::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if ((wParam==1 || wParam==2) && lParam==0) return TRUE;

	return CDialog::OnCommand(wParam, lParam);
}
