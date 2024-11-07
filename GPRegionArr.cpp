// GPRegionArr.cpp: implementation of the GPRegionArr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPRegionArr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPRegionArr::GPRegionArr()
{
	m_uMaxRgn=50;
	m_Array =new GPRegion * [m_uMaxRgn];
	UINT i;
	for(i=0; i<m_uMaxRgn;i++) m_Array[i]=NULL;
	m_uNRgn=0;
}

GPRegionArr::~GPRegionArr()
{
	if (m_Array!=NULL)
	{
		UINT i;
		for(i=0; i<m_uMaxRgn;i++)
			if (m_Array[i]!=NULL) 
			{
				delete m_Array[i];
				m_Array[i]=NULL;
			}
		delete[] m_Array;
		m_Array=NULL;
	}
	m_uNRgn=0;
}

GPRegion * GPRegionArr::GetRgn(const char *RgnName)
{
	GPRegion * tmp=NULL;
	UINT i;
	if (m_Array!=NULL)
		for(i=0; i<m_uNRgn;i++)
			if (m_Array[i]!=NULL && strcmp(m_Array[i]->GetName(),RgnName)==0)
			{
				tmp=m_Array[i];
				break;
			}
	return tmp;
}
GPRegion * GPRegionArr::CreateRgn(const char *RgnName)
{
	GPRegion * tmp=GetRgn(RgnName);
	if (tmp!=NULL) GPDeleteRgn(RgnName);

	while((m_uNRgn>=m_uMaxRgn-1 && m_uMaxRgn<0x1000) || m_uMaxRgn==0)
	{
		GPRegion ** tmp2=new GPRegion * [m_uNRgn+10];
		UINT i;
		for(i=0; i<m_uMaxRgn;i++)
			tmp2[i]=m_Array[i];
		m_uMaxRgn=m_uNRgn+10;
		delete[] m_Array;
		for(; i<m_uMaxRgn;i++)
			tmp2[i]=NULL;
		m_Array=tmp2;
	}

	if (m_uNRgn<m_uMaxRgn)
		tmp=m_Array[m_uNRgn++]=new GPRegion(RgnName);

	return tmp;
}

UINT GPRegionArr::GPDeleteRgn(const char *RgnName)
{
	UINT i;
	if (m_Array!=NULL)
		for(i=0; i<m_uNRgn;i++)
			if (m_Array[i]!=NULL && strcmp(m_Array[i]->GetName(),RgnName)==0)
			{
				delete m_Array[i];
				UINT j;
				for(j=i+1;j<m_uNRgn;j++)
					m_Array[j-1]=m_Array[j];
				m_uNRgn--;
				m_Array[m_uNRgn]=NULL;
				break;
			}
	return m_uNRgn;
}

UINT GPRegionArr::GetCount()
{
	return m_uNRgn;
}
const char * GPRegionArr::GetRgnName(UINT uNRgn)
{
	const char *ret="";
	if (m_Array!=NULL && uNRgn<m_uNRgn && m_Array[uNRgn]!=NULL)
		ret=m_Array[uNRgn]->GetName();
	return ret;
}

UINT GPRegionArr::GetRgnId(const char *iRgnName)
{
	UINT ret = -1;
	if (m_Array!=NULL)
	{
		UINT i;
		for(i=0; i<m_uNRgn;i++)
			if (m_Array[i]!=NULL && strcmp(m_Array[i]->GetName(),iRgnName)==0)
			{
				ret=i;
				break;
			}
	}
	return ret;
}

UINT GPRegionArr::DoMethod(const char *iRgnName, const char *iStr, char *oStr)
{
	UINT ret=-1;
	UINT Rgnid=GetRgnId(iRgnName);
	if (Rgnid<m_uNRgn && m_Array[Rgnid]!=NULL) ret=m_Array[Rgnid]->DoMethod(iStr,oStr,(void *)this);
	else
		GPC.m_ErrReport.GPWriteWarnLog2("GPRegion can't find", iRgnName, iStr);

	return ret;
}

void GPRegionArr::DeleteAll()
{
	if (m_Array!=NULL)
	{
		UINT i;
		for(i=0; i<m_uMaxRgn;i++)
			if (m_Array[i]!=NULL) 
			{
				delete m_Array[i];
				m_Array[i]=NULL;
			}
	}
	m_uNRgn=0;
}
