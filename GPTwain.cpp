// GPTwain.cpp : implementation file
//

#include "stdafx.h"
#include "GP_Term.h"
#include "GPTwain.h"


// CGPTwain
IMPLEMENT_DYNAMIC( CGPTwain , CObject )

CGPTwain::CGPTwain()
{
}

CGPTwain::~CGPTwain()
{
}

// CGPTwain member functions

#ifdef _DEBUG
void CGPTwain::AssertValid() const
{
	CObject::AssertValid();
}

void CGPTwain::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG



void CGPTwain::CopyImage(HANDLE hBitmap,TW_IMAGEINFO& info)
{
}
