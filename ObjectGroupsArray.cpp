// ObjectGroupsArray.cpp: implementation of the CObjectGroupsArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "ObjectGroupsArray.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC( CObjectGroupsArray , CObject )

CObjectGroupsArray::CObjectGroupsArray()
{
	m_uMaxObjectGroups=10;
	m_Array =new OBJECTGROUPITEM * [m_uMaxObjectGroups];
	UINT i;
	for(i=0; i<m_uMaxObjectGroups;i++)
		m_Array[i]=NULL; 
	m_uNObjectGroups=0;
}

CObjectGroupsArray::~CObjectGroupsArray()
{
	if (m_Array)
	{
		DeleteAll();
		delete[] m_Array;
		m_Array=NULL;
	}
	m_uNObjectGroups=0;
}

OBJECTGROUPITEM * CObjectGroupsArray::CreateObjectGroups(const char * ObjectGroupsName,  const GPUnit *pGPUnit)
{
	OBJECTGROUPITEM *ret=NULL;

	return ret;
}

UINT CObjectGroupsArray::DeleteObjectGroups(const char *ObjectGroupsName)
{
	if (m_Array)
	{
		UINT i,j;
		for(i=0,j=0; i<m_uNObjectGroups;i++)
			if (m_Array[i] && m_Array[i]->csGroupName==ObjectGroupsName)	delete m_Array[i];
			else  m_Array[j++]=m_Array[i];

		m_uNObjectGroups=j;
		for(;j<i;j++)
			m_Array[j]=NULL;

	}
	return m_uNObjectGroups;
}

UINT CObjectGroupsArray::DeleteObjectGroups(const GPUnit *pGPUnit)
{
	if (m_Array)
	{
		UINT i,j;
		for(i=0,j=0; i<m_uNObjectGroups;i++)
			if (m_Array[i] && m_Array[i]->pUnit==pGPUnit)	delete m_Array[i];
			else  m_Array[j++]=m_Array[i];

		m_uNObjectGroups=j;
		for(;j<i;j++)
			m_Array[j]=NULL;

	}
	return m_uNObjectGroups;
}

UINT CObjectGroupsArray::DeleteObjectGroups(const char * ObjectGroupsName, const GPUnit *pGPUnit)
{
	if (m_Array)
	{
		UINT i,j;
		for(i=0,j=0; i<m_uNObjectGroups;i++)
			if (m_Array[i] && m_Array[i]->pUnit==pGPUnit && m_Array[i]->csGroupName==ObjectGroupsName)	delete m_Array[i];
			else  m_Array[j++]=m_Array[i];

		m_uNObjectGroups=j;
		for(;j<i;j++)
			m_Array[j]=NULL;

	}
	return m_uNObjectGroups;
}

UINT CObjectGroupsArray::GetCount()
{
	return m_uNObjectGroups;
}

void CObjectGroupsArray::DeleteAll()
{
	if (m_Array)
	{
		UINT i;
		for(i=0; i<m_uMaxObjectGroups;i++)
			if (m_Array[i]) 
			{
				delete m_Array[i];
				m_Array[i]=NULL;
			}
	}
	m_uNObjectGroups=0;
}
/*
void CObjectGroupsArray::AddObjectGroups(const char *iStrObjectGroups, GPUnit *pGPUnit)
{
}

*/
