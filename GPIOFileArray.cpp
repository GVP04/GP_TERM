// GPIOFileArray.cpp: implementation of the GPIOFileArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GPIOFileArray.h"
#include "GP_Term.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPIOFileArray::GPIOFileArray()
{
	m_uMaxIOFile=8;
	m_Array =new GPIOFile * [m_uMaxIOFile];
	UINT i;
	for(i=0; i<m_uMaxIOFile;i++) m_Array[i]=NULL;
	m_uNIOFile=0;
}

GPIOFileArray::~GPIOFileArray()
{
	if (m_Array!=NULL)
	{
		UINT i;
		for(i=0; i<m_uMaxIOFile;i++)
			if (m_Array[i]!=NULL) 
			{
				delete m_Array[i];
				m_Array[i]=NULL;
			}
		delete[] m_Array;
		m_Array=NULL;
	}
	m_uNIOFile=0;
}

GPIOFile * GPIOFileArray::GetIOFile(const char *IOFileName)
{
	GPIOFile * tmp=NULL;
	UINT i;
	if (m_Array!=NULL)
		for(i=0; i<m_uNIOFile;i++)
			if (m_Array[i]!=NULL && strcmp(m_Array[i]->GetName(),IOFileName)==0)
			{
				tmp=m_Array[i];
				break;
			}
	return tmp;
}

GPIOFile * GPIOFileArray::CreateIOFile(const char *IOFileName)
{
	GPIOFile * tmp=GetIOFile(IOFileName);
	if (tmp!=NULL) DeleteIOFile(IOFileName);

	while((m_uNIOFile>=m_uMaxIOFile-1 && m_uMaxIOFile<0x1000) || m_uMaxIOFile==0)
	{
		GPIOFile ** tmp2=new GPIOFile * [m_uNIOFile+10];
		UINT i;
		for(i=0; i<m_uMaxIOFile;i++)
			tmp2[i]=m_Array[i];
		m_uMaxIOFile=m_uNIOFile+10;
		delete[] m_Array;
		for(; i<m_uMaxIOFile;i++)
			tmp2[i]=NULL;
		m_Array=tmp2;
	}

	if (m_uNIOFile<m_uMaxIOFile)
		tmp=m_Array[m_uNIOFile++]=new GPIOFile(IOFileName);

	return tmp;
}

UINT GPIOFileArray::DeleteIOFile(const char *IOFileName)
{
	UINT i;
	if (m_Array!=NULL)
		for(i=0; i<m_uNIOFile;i++)
			if (m_Array[i]!=NULL && strcmp(m_Array[i]->GetName(),IOFileName)==0)
			{
				delete m_Array[i];
				UINT j;
				for(j=i+1;j<m_uNIOFile;j++)
					m_Array[j-1]=m_Array[j];
				m_uNIOFile--;
				m_Array[m_uNIOFile]=NULL;
				break;
			}
	return m_uNIOFile;
}

UINT GPIOFileArray::GetCount()
{
	return m_uNIOFile;
}

const char * GPIOFileArray::GetIOFileName(UINT uNIOFile)
{
	const char *ret="";
	if (m_Array!=NULL && uNIOFile<m_uNIOFile && m_Array[uNIOFile]!=NULL)
		ret=m_Array[uNIOFile]->GetName();
	return ret;
}

UINT GPIOFileArray::GetArrayDescr(CString &str)
{
	UINT ret=0,i;
	str="";
	CString tmp;

	if (m_Array!=NULL)
		for(i=0,ret=0;i<m_uNIOFile;i++)
			if (m_Array[i]!=NULL)
			{
				if ((ret++)>0) str+="\0x7F";
				str+=tmp;
			}
	return ret;
}


UINT GPIOFileArray::DoMethod(const char *iIOFileName, const char *iStr, char ** oStr)
{
	UINT ret=-1;
	UINT IOFileid=GetIOFileId(iIOFileName);
	if (IOFileid<m_uNIOFile && m_Array[IOFileid]!=NULL) ret=m_Array[IOFileid]->DoMethod(iStr,oStr);
	else
		GPC.m_ErrReport.GPWriteWarnLog2("IOFile cant find", iIOFileName, iStr);

	return ret;
}

UINT GPIOFileArray::GetIOFileId(const char *iIOFileName)
{
	UINT ret = -1;
	if (m_Array!=NULL)
	{
		UINT i;
		for(i=0; i<m_uNIOFile;i++)
			if (m_Array[i]!=NULL && strcmp(m_Array[i]->GetName(),iIOFileName)==0)
			{
				ret=i;
				break;
			}
	}
	return ret;
}

void GPIOFileArray::ReadIOFiles()
{
	if (m_Array!=NULL)
	{
		UINT i;
		for(i=0; i<m_uNIOFile;i++)
			if (m_Array[i]!=NULL)
				m_Array[i]->DoRead();
	}
}

void GPIOFileArray::ClearEventEditiors()
{
	if (m_Array!=NULL)
	{
		UINT i;
		for(i=0; i<m_uNIOFile;i++)
			if (m_Array[i]!=NULL)
				m_Array[i]->m_EventsEditor=NULL;
	}
}

BOOL GPIOFileArray::SetEventEditor(const char *iFileName, HWND iEditor)
{
	BOOL ret=FALSE;
	if (*iFileName)
	{
		UINT nFile=GetIOFileId(iFileName);
		if (nFile<m_uNIOFile && m_Array[nFile]!=NULL)
		{
			m_Array[nFile]->m_EventsEditor=iEditor;
			ret=TRUE;
		}
	}
	else
	{
		UINT nFile=GetIOFileId(iFileName);
		for(nFile=0;nFile<m_uNIOFile;nFile++)
		if (m_Array[nFile])
		{
			m_Array[nFile]->m_EventsEditor=iEditor;
			ret=TRUE;
		}
	}
	return ret;
}
