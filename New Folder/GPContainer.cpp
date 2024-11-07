// GPContainer.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPContainer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGPContainer

CGPContainer::CGPContainer()
{
}

CGPContainer::~CGPContainer()
{
}


BEGIN_MESSAGE_MAP(CGPContainer, CWnd)
	//{{AFX_MSG_MAP(CGPContainer)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGPContainer message handlers


void CGPContainer::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}

BOOL CGPContainer::OnDraw(CDC* pDC, CSize& rSize)
{
	// Remove this if you use rSize
	return TRUE;
}
