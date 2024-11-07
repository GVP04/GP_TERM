// MenuCustom.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "MenuCustom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMenuCustom

CMenuCustom::CMenuCustom()
{
	m_dwViewType=1;
	m_dwMenuStyle=0;
	m_hMenu=NULL;
	m_PopupMenuState=MFS_ENABLED;
	m_PopupMenuINIT=NULL;
}

CMenuCustom::~CMenuCustom()
{
}



/////////////////////////////////////////////////////////////////////////////
// CMenuCustom message handlers
