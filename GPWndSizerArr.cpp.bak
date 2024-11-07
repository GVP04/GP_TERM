// GPWndSizerArr.cpp: implementation of the CGPWndSizerArr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPWndSizerArr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGPWndSizerArr::CGPWndSizerArr(HWND iParentHWND)
{
	m_ParentHwnd=iParentHWND;
	m_nGrow=4;
	m_nMaxSizers=16;
	m_nSizers=0;
	m_Array=new CGPWndSizer * [m_nMaxSizers];
	UINT i;
	for(i=0;i<m_nMaxSizers;i++)
		m_Array[i]=NULL;
}

CGPWndSizerArr::~CGPWndSizerArr()
{
	if (m_Array)
	{
		UINT i;
		for(i=0;i<m_nMaxSizers;i++)
			if (m_Array[i])
			{
				delete m_Array[i];
				m_Array[i]=NULL;
			}
		delete[] m_Array;
		m_Array=NULL;
	}
}

HWND CGPWndSizerArr::AddSizer(const char *iStr)
{
	HWND ret=NULL;
	 //"Name,Type,Size,MinParentSize,MaxParentSize"
	CString name=ExtractField(iStr,1,",");
	if (name!="")
	{
		UINT ns=GetSizerId(name);
		if (ns>=m_nSizers)
		{
			ns=m_nSizers;
			while(m_nSizers>=m_nMaxSizers-1 || m_nMaxSizers==0)
			{
				CGPWndSizer **m_Arraytmp=new CGPWndSizer *[m_nMaxSizers+m_nGrow];
				UINT i;
				for(i=0;i<m_nMaxSizers;i++)
					m_Arraytmp[i]=m_Array[i];
				m_nMaxSizers+=m_nGrow;
				for(;i<m_nMaxSizers;i++)
					m_Arraytmp[i]=NULL;
				delete[] m_Array;
				m_Array=m_Arraytmp;
			}
			m_nSizers++;
			m_Array[ns]=new CGPWndSizer(m_ParentHwnd,60000+ns);
			m_Array[ns]->SetName(name);
		}
		if (ns<m_nSizers && m_Array[ns])
		{
			m_Array[ns]->SetSizer(iStr+name.GetLength()+1);
			ret=m_Array[ns]->m_hWnd;
		}
	}

	return ret;
}

HWND CGPWndSizerArr::SetSizer(const char *iStr)
{
	HWND ret=NULL;
	 //"Name,Type,Size,MinParentSize,MaxParentSize"
	CString name=ExtractField(iStr,1,",");
	if (name!="")
	{
		UINT ns=GetSizerId(name);
		if (ns<m_nSizers)
			m_Array[ns]->SetSizer(iStr+name.GetLength()+1);
		ret=m_Array[ns]->m_hWnd;
	}

	return ret;
}

UINT CGPWndSizerArr::RemoveSizer(const char *iName)
{
	UINT ns=GetSizerId(iName);
	if (ns<m_nSizers)
	{
		delete m_Array[ns];
		m_Array[ns]=NULL;
		m_nSizers--;
		UINT i;
		for(i=ns;i<m_nSizers;i++)
			m_Array[i]=m_Array[i+1];
		m_Array[i]=NULL;
	}

	return m_nSizers;
}

UINT CGPWndSizerArr::GetSizerId(const char *iName)
{
	UINT ret=-1;
	if (m_Array)
	{
		UINT i;
		for(i=0;i<m_nSizers && ret==-1;i++)
			if (m_Array[i] && m_Array[i]->GetName()==iName)
				ret=i;
	}
	return ret;
}

UINT CGPWndSizerArr::SetGrow(UINT newGrow)
{
	UINT ret=m_nGrow;
	if (newGrow && newGrow<200)
		m_nGrow=newGrow;
	return ret;
}

UINT CGPWndSizerArr::GetGrow()
{
	return m_nGrow;
}

void CGPWndSizerArr::UpdateSizers()
{
	UINT i;
	for(i=0;i<m_nSizers ;i++)
		if (m_Array[i]) m_Array[i]->UpdateSizer();
}

void CGPWndSizerArr::UpdateSizer(const char *iName)
{
	UINT id=GetSizerId(iName);
	if (m_Array[id] && id<m_nSizers)
			m_Array[id]->UpdateSizer();
}

HWND CGPWndSizerArr::SetSizerIcon(const char *iStr)
{
	HWND ret=NULL;
	 //"Name,ILName,nImage"
	CString name=ExtractField(iStr,1,",");
	if (name!="")
	{
		UINT ns=GetSizerId(name);
		if (ns<m_nSizers)
		{
			ret=m_Array[ns]->m_hWnd;
			m_Array[ns]->SetSizerIcon(iStr+name.GetLength()+1);
		}
	}

	return ret;
}

HWND CGPWndSizerArr::SetSizerRgn(const char *iStr)
{
	HWND ret=NULL;
	 //"Name,RegionName"
	CString name=ExtractField(iStr,1,",");
	if (name!="")
	{
		UINT ns=GetSizerId(name);
		if (ns<m_nSizers)
		{
			ret=m_Array[ns]->m_hWnd;
			m_Array[ns]->SetSizerRgn(iStr+name.GetLength()+1);
		}
	}

	return ret;
}

HWND CGPWndSizerArr::SetSizerBrush(const char *iStr)
{
	HWND ret=NULL;
	 //"Name,BRUSH_AS_PROPERTY_BRUSH"
	CString name=ExtractField(iStr,1,",");
	if (name!="")
	{
		UINT ns=GetSizerId(name);
		if (ns<m_nSizers)
		{
			ret=m_Array[ns]->m_hWnd;
			m_Array[ns]->SetSizerBrush(iStr+name.GetLength()+1);
		}
	}

	return ret;
}

