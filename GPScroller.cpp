// GPScroller.cpp: implementation of the CGPScroller class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPScroller.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGPScroller::CGPScroller(const char *iName, HWND im_hWnd, HWND im_ScrollhWnd, DWORD idwFlags)
{
	dwFlags=idwFlags;
	m_hWnd=im_hWnd;
	m_ScrollhWnd=im_ScrollhWnd;
	CurPoint.x=0;
	CurPoint.y=0;
	DeltaX=8;
	DeltaY=8;
	nPageX=15;
	nPageY=15;
	Name=iName;
}

CGPScroller::CGPScroller(const char *iName, HWND im_hWnd, HWND im_ScrollhWnd, int iDeltaX,int iDeltaY, int inPageX, int inPageY, DWORD idwFlags)
{
	dwFlags=idwFlags;
	m_hWnd=im_hWnd;
	m_ScrollhWnd=im_ScrollhWnd;
	DeltaX=iDeltaX;
	DeltaY=iDeltaY;
	nPageX=inPageX;
	nPageY=inPageY;
	Name=iName;
}

CGPScroller::~CGPScroller()
{

}

void CGPScroller::SetScroller(int iDeltaX,int iDeltaY, int inPageX, int inPageY, DWORD idwFlags)
{
	dwFlags=idwFlags;
	DeltaX=iDeltaX;
	DeltaY=iDeltaY;
	nPageX=inPageX;
	nPageY=inPageY;
	UpdatePosition();
}

const CString CGPScroller::GetName()
{
	return Name;
}

void CGPScroller::UpdatePosition()
{
	CRect reME;
	CRect reChild;
	if (nPageY==0) nPageY=15;
	
	GetClientRect(m_hWnd,&reME);
	GetWindowRect(m_ScrollhWnd,&reChild);

	SCROLLINFO si={0};
	si.cbSize=sizeof(si);
	si.fMask=SIF_PAGE|SIF_POS|SIF_RANGE;
	si.nMin=0;

	si.nMax=reChild.Height();
	si.nPage=reME.Height();
	if (CurPoint.y<0 ) CurPoint.y=0;
	if (CurPoint.y>reChild.Height()-reME.Height() ) CurPoint.y=reChild.Height()-reME.Height();
	if (CurPoint.y<0 ) CurPoint.y=0;
	si.nPos=CurPoint.y;

	::SetScrollInfo(m_hWnd,SB_VERT,&si,TRUE);

	si.nMax=reChild.Width();
	si.nPage=reME.Width();
	
	if (CurPoint.x<0 ) CurPoint.x=0;
	if (CurPoint.x>reChild.Width()-reME.Width() ) CurPoint.x=reChild.Width()-reME.Width();
	if (CurPoint.x<0 ) CurPoint.x=0;
	si.nPos=CurPoint.x;

	::SetScrollInfo(m_hWnd,SB_HORZ,&si,TRUE);
	::MoveWindow(m_ScrollhWnd,-CurPoint.x,-CurPoint.y,reChild.Width(),reChild.Height(),TRUE);
}

void CGPScroller::SetScrollerPos(int iX,int iY)
{
	CurPoint.x=iX;
	CurPoint.y=iY;
	UpdatePosition();
}

void CGPScroller::OnScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
	OnHScroll(nSBCode, nPos, pScrollBar);
	OnVScroll(nSBCode, nPos, pScrollBar);
}

void CGPScroller::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
	CRect reME;
	CRect reChild;
	if (nPageY==0) nPageY=15;
	
	GetClientRect(m_hWnd,&reME);
	GetWindowRect(m_ScrollhWnd,&reChild);

	SCROLLINFO si={0};
	si.cbSize=sizeof(si);
	si.fMask=SIF_PAGE|SIF_POS|SIF_RANGE;
	si.nMin=0;
	si.nMax=reChild.Height();
	si.nPage=reME.Height();

	switch(nSBCode)
	{
	case SB_LEFT://Scroll to far left
		CurPoint.y=reChild.Height()-reME.Height();	break;
	case SB_LINELEFT://Scroll left
		CurPoint.y-=DeltaY;							break;
	case SB_RIGHT://Scroll to far right
		CurPoint.y=0;								break;
	case SB_LINERIGHT://Scroll right
		CurPoint.y+=DeltaY;							break;
	case SB_PAGELEFT://Scroll one page left.
		CurPoint.y-=si.nPage*10/nPageY;				break;
	case SB_PAGERIGHT://Scroll one page right
		CurPoint.y+=si.nPage*10/nPageY;				break;
	case SB_THUMBPOSITION://   Scroll to absolute position. The current position is specified by the nPos parameter.
		CurPoint.y=nPos;							break;
	case SB_THUMBTRACK://   Drag scroll box to specified position. The current position is specified by the 
		CurPoint.y=nPos;							break;
	}
	
	if (CurPoint.y<0 ) CurPoint.y=0;
	if (CurPoint.y>reChild.Height()-reME.Height() ) CurPoint.y=reChild.Height()-reME.Height();
	si.nPos=CurPoint.y;

	if (pScrollBar)
		pScrollBar->SetScrollInfo(&si);
	else
		::SetScrollInfo(m_hWnd,SB_VERT,&si,TRUE);
	::MoveWindow(m_ScrollhWnd,-CurPoint.x,-CurPoint.y,reChild.Width(),reChild.Height(),TRUE);
}

void CGPScroller::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
	CRect reME;
	CRect reChild;
	if (nPageX==0) nPageX=15;
	
	GetClientRect(m_hWnd,&reME);
	GetWindowRect(m_ScrollhWnd,&reChild);

	SCROLLINFO si={0};
	si.cbSize=sizeof(si);
	si.fMask=SIF_PAGE|SIF_POS|SIF_RANGE;
	si.nMin=0;
	si.nMax=reChild.Width();
	si.nPage=reME.Width();

	switch(nSBCode)
	{
	case SB_LEFT://Scroll to far left
		CurPoint.x=reChild.Width()-reME.Width();	break;
	case SB_LINELEFT://Scroll left
		CurPoint.x-=DeltaX;							break;
	case SB_RIGHT://Scroll to far right
		CurPoint.x=0;								break;
	case SB_LINERIGHT://Scroll right
		CurPoint.x+=DeltaX;							break;
	case SB_PAGELEFT://Scroll one page left.
		CurPoint.x-=si.nPage*10/nPageX;				break;
	case SB_PAGERIGHT://Scroll one page right
		CurPoint.x+=si.nPage*10/nPageX;				break;
	case SB_THUMBPOSITION://   Scroll to absolute position. The current position is specified by the nPos parameter.
		CurPoint.x=nPos;							break;
	case SB_THUMBTRACK://   Drag scroll box to specified position. The current position is specified by the 
		CurPoint.x=nPos;							break;
	}
	
	if (CurPoint.x<0 ) CurPoint.x=0;
	if (CurPoint.x>reChild.Width()-reME.Width() ) CurPoint.x=reChild.Width()-reME.Width();
	si.nPos=CurPoint.x;

	if (pScrollBar)
		pScrollBar->SetScrollInfo(&si);
	else
		::SetScrollInfo(m_hWnd,SB_HORZ,&si,TRUE);
	::MoveWindow(m_ScrollhWnd,-CurPoint.x,-CurPoint.y,reChild.Width(),reChild.Height(),TRUE);

}

UINT CGPScroller::EnsureVisible(HWND iHWND)
{
	UINT ret=1;
	try
	{
		if (iHWND)
		{
			ret=2;
			HWND tmpHWND=iHWND;

			while((tmpHWND=::GetParent(tmpHWND)) && tmpHWND!=m_hWnd);
			if (tmpHWND==m_hWnd)
			{
				ret=3;
				CRect re,recur;
				CPoint pocur,po,podelta;
				::GetWindowRect(iHWND,&re);
				po=re.TopLeft();

				::GetClientRect(m_hWnd,&recur);
				pocur.x=pocur.y=0;
				podelta.x=podelta.y=0;
				::ClientToScreen(m_hWnd,&pocur);

				if (pocur.y+recur.Height()<po.y+re.Height()) podelta.y=po.y+re.Height()-pocur.y-recur.Height();
				if (pocur.y>po.y) podelta.y=po.y-pocur.y;

				if (pocur.x+recur.Width()<po.x+re.Width()) podelta.x=po.x+re.Width()-pocur.x-recur.Width();
				if (pocur.x>po.x) podelta.x=po.x-pocur.x;
				
				if (podelta.x || podelta.y)
				{
					ret=0;
					CurPoint+=podelta;
					if (CurPoint.x<0) CurPoint.x=0;
					if (CurPoint.y<0) CurPoint.y=0;
					UpdatePosition();
				}
			}
		}
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGPScroller", "EnsureVisible","");
		ret=-1;
	}
	return ret;
}
