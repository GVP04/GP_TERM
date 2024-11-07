// PenExt.cpp: implementation of the CPenExt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "PenExt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPenExt::CPenExt()
{

}
CPenExt::CPenExt(int nPenStyle, int nWidth, COLORREF crColor )
	:CPen(nPenStyle, nWidth, crColor)
{

}
CPenExt::CPenExt(int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush)
	:CPen(nPenStyle, nWidth, pLogBrush)
{

}

CPenExt::~CPenExt()
{

}
