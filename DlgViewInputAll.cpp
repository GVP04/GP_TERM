// DlgViewInputAll.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgViewInputAll.h"
#include "GPDlgBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgViewInputAll dialog


CDlgViewInputAll::CDlgViewInputAll(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewInputAll::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgViewInputAll)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_LastIVSize=100;
	m_Height=AfxGetApp()->GetProfileInt("SEP_OUTPUT_SET", "HEIGHT_SET",200);
	m_csLastParentSize.cx=0;
	m_csLastParentSize.cy=0;
	DlgAutoSize=NULL;
	m_SizeNow=FALSE;
	m_DlgViewOutputPtr=NULL;
	m_BarOutputSet=NULL;
	m_BarInputSet=NULL;
	m_SizeCursor=LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_CURSOR_HO_SIZEB));
}

CDlgViewInputAll::~CDlgViewInputAll()
{
	if (m_hWnd) DestroyWindow();
	if (DlgAutoSize)
		delete DlgAutoSize;
	DlgAutoSize=NULL;

}

void CDlgViewInputAll::OnDestroy()
{
	AfxGetApp()->WriteProfileInt("SEP_OUTPUT_SET", "HEIGHT_SET",m_Height);

	if (DlgAutoSize)
		delete DlgAutoSize;
	DlgAutoSize=NULL;
	if (m_BarOutputSet)
	{
		m_BarOutputSet->DestroyWindow();
		delete m_BarOutputSet;
	}
	m_BarOutputSet=NULL;
	if (m_BarInputSet)
	{
		m_BarInputSet->DestroyWindow();
		delete m_BarInputSet;
	}
	m_BarInputSet=NULL;
	CDialog::OnDestroy();
}

void CDlgViewInputAll::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgViewInputAll)
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgViewInputAll, CDialog)
	//{{AFX_MSG_MAP(CDlgViewInputAll)
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgViewInputAll message handlers

void CDlgViewInputAll::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if (DlgAutoSize)
		try{DlgAutoSize->UpdateSize();}catch(...){GPC.m_ErrReport.GPWriteErrorLog("CDlgViewInputAll", "OnSize","");}
}

BOOL CDlgViewInputAll::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect re;
	m_Tab.GetClientRect(&re);
	re.InflateRect(-2,-21,-2,-2);
	CRect retmp=re;
	retmp.InflateRect(-2,-2,-2,-2);

	m_BarInputSet=new GPDlgBar(123456,"");
	m_BarOutputSet=new GPDlgBar(123457,"");

	m_BarInputSet->CreateDlgBar(WS_EX_CLIENTEDGE,"",WS_CHILD,retmp,&m_Tab,123456,"",GPC.m_GUISet.Scale);
	m_BarOutputSet->CreateDlgBar(WS_EX_CLIENTEDGE,"",WS_CHILD,retmp,&m_Tab,123457,"",GPC.m_GUISet.Scale);

	m_DlgViewOutputSet.m_DlgViewOutputPtr=m_DlgViewOutputPtr;

	m_DlgViewInput.Create(IDD_DLGVIEWINPUT,CWnd::FromHandle(m_Tab.m_hWnd));
	m_DlgViewInput.MoveWindow(re,FALSE);
	m_DlgViewInputSet.Create(IDD_DLGVIEWINPUTSET,m_BarInputSet);
	m_DlgViewInputSet.GetWindowRect(&retmp);
	m_DlgViewInputSet.MoveWindow(&retmp,FALSE);
	m_BarInputSet->ScreenToClient(&retmp);
	m_DlgViewOutputSet.Create(IDD_DLGVIEWOUTPUTSET,m_BarOutputSet);
	m_DlgViewOutputSet.GetWindowRect(&retmp);
	m_BarOutputSet->ScreenToClient(&retmp);
	m_DlgViewOutputSet.MoveWindow(&retmp,FALSE);

	char metstr[250];
	sprintf(metstr,"AddScroller Input,HWND=%d,15,5,150,70",(UINT)(m_DlgViewInputSet.m_hWnd));
	m_BarInputSet->DoMethod(metstr,NULL);
	sprintf(metstr,"AddScroller Output,HWND=%d,15,5,150,70",(UINT)(m_DlgViewOutputSet.m_hWnd));
	m_BarOutputSet->DoMethod(metstr,NULL);

	m_DlgViewInput.ShowWindow(SW_SHOW);
	m_DlgViewInputSet.ShowWindow(SW_SHOW);
	m_DlgViewOutputSet.ShowWindow(SW_SHOW);

	DlgAutoSize=new GP_AutoSizing;
	DlgAutoSize->AddSetMain(this->m_hWnd);
	DlgAutoSize->AddWnd(m_Tab.m_hWnd,this->m_hWnd,"NNEE");
	DlgAutoSize->AddWnd(m_DlgViewInput.m_hWnd,this->m_hWnd,"NNEE");
	DlgAutoSize->AddWnd(m_BarInputSet->m_hWnd,this->m_hWnd,"NNEE");
	DlgAutoSize->AddWnd(m_BarOutputSet->m_hWnd,this->m_hWnd,"NNEE");


#ifdef RUS
	m_Tab.InsertItem(1,"Редактор ввода",1);
	m_Tab.InsertItem(2,"Настройка ввода",2);
	m_Tab.InsertItem(3,"Настройка вывода",3);
#else
	m_Tab.InsertItem(1,"Input Editor",1);
	m_Tab.InsertItem(2,"Input Setup",2);
	m_Tab.InsertItem(3,"Output Setup",3);
#endif
	UpdateTabs();

	return TRUE;
}

void CDlgViewInputAll::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult)
{
	UpdateTabs();
	*pResult = 0;
}

void CDlgViewInputAll::UpdateTabs()
{
	m_DlgViewInput.ModifyStyle(WS_VISIBLE,0);
	m_BarInputSet->ModifyStyle(WS_VISIBLE,0);
	m_BarOutputSet->ModifyStyle(WS_VISIBLE,0);
	switch(m_Tab.GetCurSel())
	{
	case 0:
		m_DlgViewInput.ModifyStyle(0,WS_VISIBLE);
		break;
	case 1:
		m_BarInputSet->ModifyStyle(0,WS_VISIBLE);
		break;
	case 2:
		m_BarOutputSet->ModifyStyle(0,WS_VISIBLE);
		break;
	}
	Invalidate();
}

void CDlgViewInputAll::SetSize(CSize &csValidSize)
{
	if (m_csLastParentSize!=csValidSize)
		MoveWindow(0,csValidSize.cy-m_Height,csValidSize.cx,m_Height);

	m_csLastParentSize=csValidSize;
	csValidSize.cy-=m_Height;
}



void CDlgViewInputAll::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDown(nFlags, point);
	if (point.y<5 && point.y>=0)
	{
		SetCursor(m_SizeCursor);
		m_SizeNow=TRUE;
		SetCapture();
	}
}

void CDlgViewInputAll::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_SizeNow)
	{
		ReleaseCapture();
		SetCursor(NULL);
	}
	m_SizeNow=FALSE;

	CDialog::OnLButtonUp(nFlags, point);
}

void CDlgViewInputAll::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_SizeNow || (point.y<5 && point.y>=0))
		SetCursor(m_SizeCursor);
	if (m_SizeNow)
	{
		CRect re;
		GetParent()->GetClientRect(&re);
		GetParent()->ClientToScreen(&re);
		CPoint po2=point;
		::ClientToScreen(m_hWnd,&po2);

		if (re.PtInRect(po2))
		{
			CRect mRe;
			GetClientRect(&mRe);
			ClientToScreen(&mRe);
			mRe.top=po2.y;
			UpdateIVSize(mRe.Height());
		}
	}
	CDialog::OnMouseMove(nFlags, point);
}

void CDlgViewInputAll::SwitchIVSize(DWORD cmd)
{
	int tmplastSize=m_LastIVSize;
	switch(cmd)
	{
	case SCCMND_WNDSIZE:
		UpdateIVSize(0);
		break;
	case SCCMND_WNDSIZE2:
		{
			CRect tmpre;
			m_DlgViewInputSet.GetWindowRect(&tmpre);
			UpdateIVSize(tmpre.Height());
		}
		break;
	case 0:
	case 1:
	case 3:
		UpdateIVSize(m_LastIVSize);
		break;
	}
	m_LastIVSize=tmplastSize;

}

void CDlgViewInputAll::UpdateIVSize(int iHeighht)
{
	m_LastIVSize=m_Height;
	m_Height=iHeighht;
	m_csLastParentSize.cx=0;
	if (m_Height<56 && m_Height>5) m_Height=56;
	GetParent()->SendMessage(GPN_UPDATESIZE,m_Height,0);
}

BOOL CDlgViewInputAll::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	POINT po={0};
	GetCursorPos(&po);
	::ScreenToClient(m_hWnd,&po);
	if (po.y<5 && po.y>=0)
		SetCursor(m_SizeCursor);

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

LRESULT CDlgViewInputAll::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message==GPN_UPDATESIZE)
		GetParent()->SendMessage(GPN_UPDATESIZE,wParam,0);
	return CDialog::WindowProc(message, wParam, lParam);
}

BOOL CDlgViewInputAll::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if ((wParam==1 || wParam==2) && lParam==0) return TRUE;

	return CDialog::OnCommand(wParam, lParam);
}

void CDlgViewInputAll::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	SwitchIVSize(0);
	CDialog::OnLButtonDblClk(nFlags, point);
}
