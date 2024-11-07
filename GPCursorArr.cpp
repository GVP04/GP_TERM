// GPCursorArr.cpp: implementation of the GPCursorArr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPCursorArr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPCursorArr::GPCursorArr()
{
	m_uMaxCursor=50;
	m_Array =new GPCursor * [m_uMaxCursor];
	UINT i;
	for(i=0; i<m_uMaxCursor;i++) m_Array[i]=NULL;
	m_uNCursor=0;
}

GPCursorArr::~GPCursorArr()
{
	if (m_Array!=NULL)
	{
		UINT i;
		for(i=0; i<m_uMaxCursor;i++)
			if (m_Array[i]!=NULL) 
			{
				delete m_Array[i];
				m_Array[i]=NULL;
			}
		delete[] m_Array;
		m_Array=NULL;
	}
	m_uNCursor=0;
}

GPCursor * GPCursorArr::GetCursor(const char *CursorName)
{
	GPCursor * tmp=NULL;
	UINT i;
	if (m_Array!=NULL)
		for(i=0; i<m_uNCursor;i++)
			if (m_Array[i]!=NULL && strcmp(m_Array[i]->GetName(),CursorName)==0)
			{
				tmp=m_Array[i];
				break;
			}
	return tmp;
}
GPCursor * GPCursorArr::CreateCursor(const char *CursorName)
{
	GPCursor * tmp=GetCursor(CursorName);
	if (tmp!=NULL) DeleteCursor(CursorName);

	while((m_uNCursor>=m_uMaxCursor-1 && m_uMaxCursor<0x1000) || m_uMaxCursor==0)
	{
		GPCursor ** tmp2=new GPCursor * [m_uNCursor+10];
		UINT i;
		for(i=0; i<m_uMaxCursor;i++)
			tmp2[i]=m_Array[i];
		m_uMaxCursor=m_uNCursor+10;
		delete[] m_Array;
		for(; i<m_uMaxCursor;i++)
			tmp2[i]=NULL;
		m_Array=tmp2;
	}

	if (m_uNCursor<m_uMaxCursor)
		tmp=m_Array[m_uNCursor++]=new GPCursor(CursorName);

	return tmp;
}

UINT GPCursorArr::DeleteCursor(const char *CursorName)
{
	UINT i;
	if (m_Array!=NULL)
		for(i=0; i<m_uNCursor;i++)
			if (m_Array[i]!=NULL && strcmp(m_Array[i]->GetName(),CursorName)==0)
			{
				delete m_Array[i];
				UINT j;
				for(j=i+1;j<m_uNCursor;j++)
					m_Array[j-1]=m_Array[j];
				m_uNCursor--;
				m_Array[m_uNCursor]=NULL;
				break;
			}
	return m_uNCursor;
}

UINT GPCursorArr::GetCount()
{
	return m_uNCursor;
}
const char * GPCursorArr::GetCursorName(UINT uNCursor)
{
	const char *ret="";
	if (m_Array!=NULL && uNCursor<m_uNCursor && m_Array[uNCursor]!=NULL)
		ret=m_Array[uNCursor]->GetName();
	return ret;
}

const char * GPCursorArr::GetCursorNameByHCUR(HCURSOR hCur)
{
	const char *ret="";
	if (m_Array!=NULL)
	{
		UINT i;
		for(i=0; i<m_uNCursor;i++)
			if (m_Array[i]!=NULL && m_Array[i]->GetHCURSOR()==hCur)
			{
				ret=m_Array[i]->GetName();
				break;
			}
	}
	return ret;
}

UINT GPCursorArr::GetCursorId(const char *iCursorName)
{
	UINT ret = -1;
	if (m_Array!=NULL)
	{
		UINT i;
		for(i=0; i<m_uNCursor;i++)
			if (m_Array[i]!=NULL && strcmp(m_Array[i]->GetName(),iCursorName)==0)
			{
				ret=i;
				break;
			}
	}
	return ret;
}

UINT GPCursorArr::DoMethod(const char *iCursorName, const char *iStr, char *oStr)
{
	UINT ret=-1;
	UINT Cursorid=GetCursorId(iCursorName);
	if (Cursorid<m_uNCursor && m_Array[Cursorid])
		ret=m_Array[Cursorid]->DoMethod(iStr,oStr,(void *)this);
	else
		GPC.m_ErrReport.GPWriteWarnLog2("GPCursor can't find", iCursorName,iStr);

	return ret;
}

void GPCursorArr::DeleteAll()
{
	if (m_Array!=NULL)
	{
		UINT i;
		for(i=0; i<m_uMaxCursor;i++)
			if (m_Array[i]!=NULL) 
			{
				delete m_Array[i];
				m_Array[i]=NULL;
			}
	}
	m_uNCursor=0;
}
