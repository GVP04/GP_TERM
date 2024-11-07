// GPHandleArray.cpp: implementation of the CGPHandleArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPHandleArray.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGPHandleArray::CGPHandleArray()
{
	m_uMaxHandle=50;
	m_Array =new HANDLEARRAYITEM * [m_uMaxHandle];
	UINT i;
	for(i=0; i<m_uMaxHandle;i++) m_Array[i]=NULL;
	m_uNHandle=0;

	InitValue.uSize=TMPValue.uSize=sizeof(HANDLEARRAYITEM);
	InitValue.csName=TMPValue.csName="";
	InitValue.dwId=TMPValue.dwId=-1;
	InitValue.dwItemData=TMPValue.dwItemData=0;
	InitValue.handle=TMPValue.handle=0;
	InitValue.uType=TMPValue.uType=HANDLER_TYPE_VOID;
}

CGPHandleArray::~CGPHandleArray()
{
	if (m_Array!=NULL)
	{
		UINT i;
		for(i=0; i<m_uMaxHandle;i++)
			if (m_Array[i]!=NULL) 
			{
				FreeHandle(i);
				delete m_Array[i];
				m_Array[i]=NULL;
			}
		delete[] m_Array;
		m_Array=NULL;
	}
	m_uNHandle=0;
}

HANDLEARRAYITEM * CGPHandleArray::AddEmpty()
{
	UINT newID=FindItemByName("");
	if (newID==0xFFFFFFFF)
	{
		UINT i;
		while((m_uNHandle>=m_uMaxHandle-1 && m_uMaxHandle<0x1000) || m_uMaxHandle==0)
		{
			HANDLEARRAYITEM ** tmp2=new HANDLEARRAYITEM * [m_uNHandle+10];
			for(i=0; i<m_uMaxHandle;i++)
				tmp2[i]=m_Array[i];
			m_uMaxHandle=m_uNHandle+10;
			delete[] m_Array;
			for(; i<m_uMaxHandle;i++)
				tmp2[i]=NULL;
			m_Array=tmp2;
		}
		for(newID=0; newID<m_uMaxHandle;newID++)
			if (m_Array[newID]==NULL)
			{
				m_Array[newID]=new HANDLEARRAYITEM;
				ResetItem(m_Array[newID]);
				m_uNHandle++;
				break;
			}
	}
	return m_Array[newID];
}

HANDLEARRAYITEM & CGPHandleArray::CreateHandle(const char *HandleName)
{
	UINT Id=FindItemByName(HandleName);
	HANDLEARRAYITEM *it=NULL;
	if (Id==0xFFFFFFFF) it=AddEmpty();
	else it=m_Array[Id];

	ResetItem(it);
	it->csName=HandleName;

	return *it;
}

HANDLEARRAYITEM & CGPHandleArray::CreateHandle(HANDLEARRAYITEM & iValue)
{
	UINT Id=FindItemByName(iValue.csName);
	HANDLEARRAYITEM *it=NULL;
	if (Id==0xFFFFFFFF) it=AddEmpty();
	else it=m_Array[Id];

	ResetItem(it);

	it->uSize		=iValue.uSize;
	it->csName		=iValue.csName;
	it->dwId		=iValue.dwId;
	it->dwItemData	=iValue.dwItemData;
	it->handle		=iValue.handle;

	return *it;
}

UINT CGPHandleArray::DeleteHandle(const char *HandleName)
{
	UINT Id=FindItemByName(HandleName);
	if (Id!=0xFFFFFFFF)
	{
		FreeHandle(Id);
		delete m_Array[Id];
		UINT j;
		for(j=Id+1;j<m_uNHandle;j++)
			m_Array[j-1]=m_Array[j];
		m_uNHandle--;
		m_Array[m_uNHandle]=NULL;
	}
	return GetCount();
}

UINT CGPHandleArray::GetCount()
{
	return m_uNHandle;
}

UINT CGPHandleArray::FindItemByHANDLE(HANDLE iHandle)
{
	UINT ret = -1;
	if (m_Array!=NULL)
	{
		UINT i;
		for(i=0; i<m_uNHandle;i++)
			if (m_Array[i]!=NULL && m_Array[i]->handle==iHandle)
			{
				ret=i;
				break;
			}
	}
	return ret;
}

UINT CGPHandleArray::FindItemByName(const char *iName)
{
	UINT ret = -1;
	if (m_Array!=NULL)
	{
		UINT i;
		for(i=0; i<m_uNHandle;i++)
			if (m_Array[i]!=NULL && m_Array[i]->csName==iName)
			{
				ret=i;
				break;
			}
	}
	return ret;
}

void CGPHandleArray::ResetItem(HANDLEARRAYITEM *iItem)
{
	iItem->uSize		=InitValue.uSize;
	iItem->csName		=InitValue.csName;
	iItem->dwId			=InitValue.dwId;
	iItem->dwItemData	=InitValue.dwItemData;
	iItem->handle		=InitValue.handle;
	iItem->uType		=InitValue.uType;
}

void CGPHandleArray::FreeHandle(UINT iId)
{
	if (iId<m_uNHandle && m_Array[iId] && m_Array[iId]->handle)
		FreeHandle(*m_Array[iId]);
}

void CGPHandleArray::FreeHandle(HANDLEARRAYITEM &iItem)
{
	if (iItem.handle)
	{
		try
		{
			switch(iItem.uType)
			{
			case HANDLER_TYPE_HKEY:
				::RegCloseKey((HKEY)iItem.handle);
				break;
			case HANDLER_TYPE_HKEY_PREDEF:
				break;
			default:
				break;
			}
			iItem.handle=NULL;
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("CGPHandleArray", "FreeHandle","");
		}
	}
}

const CString CGPHandleArray::EnumHandlers(UINT iIndex)
{
	CString ret="";
	if (iIndex<m_uNHandle && m_Array && m_Array[iIndex])
		ret=m_Array[iIndex]->csName;

	return ret;
}
