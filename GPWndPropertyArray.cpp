// GPWndPropertyArray.cpp: implementation of the CGPWndPropertyArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPWndPropertyArray.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL( CGPWndPropertyArray, CObject, 0)

CGPWndPropertyArray::CGPWndPropertyArray()
{
	m_LastSet=-1;
}

CGPWndPropertyArray::~CGPWndPropertyArray()
{

}

void CGPWndPropertyArray::Serialize( CArchive& archive )
{
}

void CGPWndPropertyArray::SetOnStyles(DWORD iId)
{
	if (m_LastSet!=-1 && iId!=m_LastSet) m_Array[m_LastSet].SetOffStyles();
	m_LastSet=iId;
	m_Array[m_LastSet].SetOnStyles();
}

void CGPWndPropertyArray::SetOffStyles(DWORD iId)
{
	if (iId!=-1) 
		m_Array[iId].SetOffStyles();
	else
	{
		m_Array[m_LastSet].SetOffStyles();
		m_LastSet=-1;
	}
}

int CGPWndPropertyArray::GetIdsList(CString & iStr, const char *iDelimiter)
{
	m_Array.GetIdsList(iStr,iDelimiter);
	return m_Array.GetCount();
}
