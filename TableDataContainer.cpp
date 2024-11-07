// TableDataContainer.cpp: implementation of the CTableDataContainer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "TableDataContainer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTableDataContainer::CTableDataContainer()
{
	m_DefImage=-1;
	InitializeCriticalSection(&m_CSTableDataContainer);
	m_ItemsCount=0;
	m_FirstID=0;
	m_ReqFirstID=0;
	m_RequestCount=0;
	m_PrereadCountInitial=m_PrereadCount=5;
	m_SubItemsCount=0;
	m_ItemsArray=NULL;
	m_LastReqTick=GetTickCount();
	m_LastReqFirstID=0;
	m_LastReqLastID=0;
	m_MinAvID=0;
	m_MaxAvID=0;
	m_BulkCountInitial=m_BulkCount=100;
	SetItemCount(1000);
}


CTableDataContainer::~CTableDataContainer()
{
	EnterCriticalSection(&m_CSTableDataContainer);
	if (m_ItemsArray)
	{
		DWORD i;
		for(i=0;i<m_ItemsCount;i++)
			if (m_ItemsArray[i])
			{
				delete m_ItemsArray[i];
				m_ItemsArray[i]=NULL;
			}
		delete[] m_ItemsArray;
		m_ItemsArray=NULL;
	}
	LeaveCriticalSection(&m_CSTableDataContainer);
	DeleteCriticalSection(&m_CSTableDataContainer);
}

DWORD CTableDataContainer::SetItemText(DWORD dwID, DWORD dwSubId, const char *iText)
{
	EnterCriticalSection(&m_CSTableDataContainer);
	DWORD ret=0xFFFFFFFF;
	PVTABLEITEM pSI=GetCreateSubItem(dwID,dwSubId);
	if (pSI)
	{
		pSI->csText=iText;
		ret=pSI->csText.GetLength();
	}
	LeaveCriticalSection(&m_CSTableDataContainer);
	return ret;
}

DWORD CTableDataContainer::SetItemImage(DWORD dwID, DWORD dwSubId, DWORD dwImage)
{
	DWORD ret=0xFFFFFFFF;
	EnterCriticalSection(&m_CSTableDataContainer);
	PVTABLEITEM pSI=GetCreateSubItem(dwID,dwSubId);
	ret=m_DefImage;
	if (pSI)
	{
		ret=pSI->nImage;
		pSI->nImage=dwImage;
	}
	LeaveCriticalSection(&m_CSTableDataContainer);
	return ret;
}

DWORD CTableDataContainer::SetItemState(DWORD dwID, DWORD dwSubId, DWORD dwState)
{
	DWORD ret=0xFFFFFFFF;
	EnterCriticalSection(&m_CSTableDataContainer);
	PVTABLEITEM pSI=GetCreateSubItem(dwID,dwSubId);
	if (pSI)
	{
		ret=pSI->dwState;
		pSI->dwState=dwState;
	}
	LeaveCriticalSection(&m_CSTableDataContainer);
	return ret;
}

DWORD CTableDataContainer::SetItemStyle(DWORD dwID, DWORD dwSubId, DWORD dwStyle)
{
	EnterCriticalSection(&m_CSTableDataContainer);
	DWORD ret=0xFFFFFFFF;
	PVTABLEITEM pSI=GetCreateSubItem(dwID,dwSubId);
	if (pSI)
	{
		ret=pSI->dwStyle;
		pSI->dwStyle=dwStyle;
	}
	LeaveCriticalSection(&m_CSTableDataContainer);
	return ret;
}

DWORD CTableDataContainer::SetItem(DWORD dwID, const CTableDataContainerItem *pItem)
{
	EnterCriticalSection(&m_CSTableDataContainer);
	DWORD ret=0xFFFFFFFF;
	CTableDataContainerItem * pSI=GetCreateItem(dwID);
	if (pSI)
	{
		if (pItem) *pSI=*pItem;
		else
		{
			delete[] pSI;
			pSI=NULL;
		}
		ret=(DWORD)pSI;
	}
	LeaveCriticalSection(&m_CSTableDataContainer);
	return ret;
}

const char *CTableDataContainer::GetItemText(DWORD dwID, DWORD dwSubId)
{
	EnterCriticalSection(&m_CSTableDataContainer);
	PVTABLEITEM pSI=GetSubItem(dwID,dwSubId);
	LeaveCriticalSection(&m_CSTableDataContainer);
	return pSI?pSI->csText:"";
}

int CTableDataContainer::SetDefImage(int iDefImage)
{
	int ret=m_DefImage;
	m_DefImage=iDefImage;
	return ret;
}
int CTableDataContainer::GetDefImage()
{
	return m_DefImage;
}

DWORD CTableDataContainer::GetItemImage(DWORD dwID, DWORD dwSubId)
{
	EnterCriticalSection(&m_CSTableDataContainer);
	PVTABLEITEM pSI=GetSubItem(dwID,dwSubId);
	LeaveCriticalSection(&m_CSTableDataContainer);
	return pSI?pSI->nImage:m_DefImage;
}


DWORD CTableDataContainer::GetItemState(DWORD dwID, DWORD dwSubId)
{
	EnterCriticalSection(&m_CSTableDataContainer);
	PVTABLEITEM pSI=GetSubItem(dwID,dwSubId);
	LeaveCriticalSection(&m_CSTableDataContainer);
	return pSI?pSI->dwState:0;
}

DWORD CTableDataContainer::GetItemStyle(DWORD dwID, DWORD dwSubId)
{
	EnterCriticalSection(&m_CSTableDataContainer);
	PVTABLEITEM pSI=GetSubItem(dwID,dwSubId);
	LeaveCriticalSection(&m_CSTableDataContainer);
	return pSI?pSI->dwStyle:0;
}

PVTABLEITEM CTableDataContainer::GetCreateSubItem(DWORD dwID, DWORD dwSubId)
{
	EnterCriticalSection(&m_CSTableDataContainer);
	CTableDataContainerItem *pItem=GetCreateItem(dwID);
	LeaveCriticalSection(&m_CSTableDataContainer);
	return pItem?pItem->GetItem(dwSubId):NULL;
}

CTableDataContainerItem * CTableDataContainer::GetCreateItem(DWORD dwID)
{
	EnterCriticalSection(&m_CSTableDataContainer);
	CTableDataContainerItem *ret=GetItem(dwID);
	if (ret==NULL)
	{
		if (dwID>=m_FirstID && dwID<m_FirstID+m_ItemsCount)
		{
			ret=m_ItemsArray[dwID-m_FirstID];
			if (ret==NULL) ret=m_ItemsArray[dwID-m_FirstID]=new CTableDataContainerItem(m_DefImage);
			if (ret) ret->SetItemsCount(m_SubItemsCount);
		}
		else
			if (dwID>=m_MinAvID && dwID<=m_MaxAvID)
			{
				DWORD dwNewFirst=dwID;
				if (dwNewFirst>=m_FirstID+m_ItemsCount)
				{
					dwNewFirst=dwNewFirst+m_BulkCount/2-m_ItemsCount;
				}
				else
				{
					if (dwNewFirst-m_MinAvID>m_BulkCount/2) dwNewFirst-=m_BulkCount/2;
					else dwNewFirst=m_MinAvID;
				}
				SetFirstID(dwNewFirst);
				ret=GetCreateItem(dwID);
			}
	}
	LeaveCriticalSection(&m_CSTableDataContainer);
	return ret;
}

PVTABLEITEM CTableDataContainer::GetSubItem(DWORD dwID, DWORD dwSubId)
{
	EnterCriticalSection(&m_CSTableDataContainer);
	CTableDataContainerItem *pItem=GetItem(dwID);
	LeaveCriticalSection(&m_CSTableDataContainer);
	return pItem?pItem->GetItem(dwSubId):NULL;
}

CTableDataContainerItem * CTableDataContainer::GetItem(DWORD dwID)
{
	EnterCriticalSection(&m_CSTableDataContainer);
	PrepareRequest(dwID);
	CTableDataContainerItem *ret=NULL;
	DWORD dwItemNum=dwID-m_FirstID;
	if (m_ItemsArray && dwItemNum<m_ItemsCount)  ret=m_ItemsArray[dwItemNum];
	LeaveCriticalSection(&m_CSTableDataContainer);
	return ret;
}

DWORD CTableDataContainer::SetItemCount(DWORD dwCount, BOOL bEnd)
{
	EnterCriticalSection(&m_CSTableDataContainer);
	m_BulkCount=m_BulkCountInitial;
	m_PrereadCount=m_PrereadCountInitial;
	if (m_ItemsCount!=dwCount)
	{
		CTableDataContainerItem **tmpArray;
		tmpArray=new CTableDataContainerItem * [dwCount];
		DWORD i=0;
		if (m_ItemsArray)
		{
			if (bEnd)
			{
				for(i=0;i<m_ItemsCount && i<dwCount;i++)
				{
					tmpArray[i]=m_ItemsArray[i];
					m_ItemsArray[i]=NULL;
				}
				for(;i<m_ItemsCount;i++)
					if (m_ItemsArray[i])
					{
						delete m_ItemsArray[i];
						m_ItemsArray[i]=NULL;
					}
				delete[] m_ItemsArray;
				m_ItemsArray=tmpArray;
				m_ItemsCount=dwCount;
				for(;i<m_ItemsCount;i++) m_ItemsArray[i]=NULL;
			}
			else
			{
				if (dwCount>m_ItemsCount)
				{
					DWORD delta=dwCount-m_ItemsCount;
					if (delta<=m_FirstID)
					{
						for(i=0;i<delta;i++) tmpArray[i]=NULL;
						for(;i<dwCount;i++)
						{
							tmpArray[i]=m_ItemsArray[i-delta];
							m_ItemsArray[i-delta]=NULL;
						}
						m_FirstID-=delta;
					}
					else
					{
						for(i=0;i<m_FirstID;i++) tmpArray[i]=NULL;

						for(i=0;i<m_ItemsCount;i++)
						{
							tmpArray[i+m_FirstID]=m_ItemsArray[i];
							m_ItemsArray[i]=NULL;
						}
						for(i=m_ItemsCount+m_FirstID;i<dwCount;i++) tmpArray[i]=NULL;
						m_FirstID=0;
					}
				}
				else
				{
					DWORD delta=m_ItemsCount-dwCount;
					m_FirstID+=delta;
					for(i=0;i<delta;i++) m_ItemsArray[i]=NULL;

					for(i=0;i<dwCount;i++)
					{
						tmpArray[i]=m_ItemsArray[i+delta];
						m_ItemsArray[i+delta]=NULL;
					}
				}
				delete[] m_ItemsArray;
				m_ItemsArray=tmpArray;
				m_ItemsCount=dwCount;
			}
		}
		else
		{
			m_ItemsArray=tmpArray;
			m_ItemsCount=dwCount;
			for(;i<m_ItemsCount;i++)
				m_ItemsArray[i]=NULL;
		}
	}
	CheckDimensions();
	LeaveCriticalSection(&m_CSTableDataContainer);
	return m_ItemsCount;
}

DWORD CTableDataContainer::GetItemCount()
{
	return m_ItemsCount;
}

DWORD CTableDataContainer::SetColumnCount(DWORD dwColumnCount)
{
	EnterCriticalSection(&m_CSTableDataContainer);
	if (m_SubItemsCount!=dwColumnCount)
	{
		m_SubItemsCount=dwColumnCount;
		if (m_ItemsArray)
		{
			DWORD i;
			for(i=0; i<m_ItemsCount; i++)
				if (m_ItemsArray[i])
					m_ItemsArray[i]->SetItemsCount(m_SubItemsCount);
		}
	}
	LeaveCriticalSection(&m_CSTableDataContainer);
	return m_SubItemsCount;
}

DWORD CTableDataContainer::GetColumnCount()
{
	return m_SubItemsCount;
}

DWORD CTableDataContainer::InsertColumn(DWORD dwBefore)
{
	EnterCriticalSection(&m_CSTableDataContainer);
	m_SubItemsCount++;
	if (m_ItemsArray)
	{
		DWORD i;
		for(i=0; i<m_ItemsCount; i++)
			if (m_ItemsArray[i]) m_ItemsArray[i]->InsertItem(dwBefore);
	}
	LeaveCriticalSection(&m_CSTableDataContainer);
	return m_SubItemsCount;
}

DWORD CTableDataContainer::DeleteColumn(DWORD dwColumn)
{
	EnterCriticalSection(&m_CSTableDataContainer);
	if (m_SubItemsCount)
	if (m_ItemsArray)
	{
		DWORD i;
		for(i=0; i<m_ItemsCount; i++)
			if (m_ItemsArray[i]) m_ItemsArray[i]->DeleteItem(dwColumn);
	}
	LeaveCriticalSection(&m_CSTableDataContainer);
	return m_SubItemsCount;
}

DWORD CTableDataContainer::SetFirstID(DWORD dwFirstID)
{
	EnterCriticalSection(&m_CSTableDataContainer);
	DWORD ret=m_FirstID;
	if (dwFirstID<m_MinAvID) dwFirstID=m_MinAvID;
	if (dwFirstID+m_ItemsCount>=m_MaxAvID) dwFirstID=m_MaxAvID+1-m_ItemsCount;

	if (m_ItemsArray && dwFirstID!=m_FirstID)
	{
		DWORD i;
		if (dwFirstID>m_FirstID)
		{
			DWORD delta=dwFirstID-m_FirstID;
			if (delta>=m_ItemsCount)
			{
				for(i=0;i<m_ItemsCount ;i++)
					if (m_ItemsArray[i])
					{
						delete m_ItemsArray[i];
						m_ItemsArray[i]=NULL;
					}
			}
			else
			{
				for(i=0;i<delta;i++)
					if (m_ItemsArray[i])
					{
						delete m_ItemsArray[i];
						m_ItemsArray[i]=NULL;
					}

				for(i=0;i+delta<m_ItemsCount ;i++)
				{
					m_ItemsArray[i]=m_ItemsArray[i+delta];
					m_ItemsArray[i+delta]=NULL;
				}
			}
		}
		else
		{
			DWORD delta=m_FirstID-dwFirstID;
			if (delta>=m_ItemsCount)
			{
				for(i=0;i<m_ItemsCount ;i++)
					if (m_ItemsArray[i])
					{
						delete m_ItemsArray[i];
						m_ItemsArray[i]=NULL;
					}
			}
			else
			{
				for(i=m_ItemsCount-1;i>delta;i--)
				{
					if (m_ItemsArray[i]) delete m_ItemsArray[i];
					m_ItemsArray[i]=m_ItemsArray[i-delta];
					m_ItemsArray[i-delta]=NULL;
				}

				for(i=m_ItemsCount-delta;i<delta;i++)
					if (m_ItemsArray[i]) 
					{
						delete m_ItemsArray[i];
						m_ItemsArray[i]=NULL;
					}
			}
		}
		m_FirstID=dwFirstID;
	}
	LeaveCriticalSection(&m_CSTableDataContainer);
	return ret;
}

DWORD CTableDataContainer::GetFirstID()
{
	return m_FirstID;
}

DWORD CTableDataContainer::GetRequest(DWORD & dwStartFromID, DWORD & dwLength)
{
	EnterCriticalSection(&m_CSTableDataContainer);
	dwStartFromID=m_ReqFirstID;
	dwLength=m_RequestCount; 
	DWORD ret=m_LastReqTick;
	m_LastReqTick=GetTickCount();
	LeaveCriticalSection(&m_CSTableDataContainer);
	return ret;
}

DWORD CTableDataContainer::SetPrereadCount(DWORD dwPrereadCount)
{
	EnterCriticalSection(&m_CSTableDataContainer);
	DWORD ret=m_PrereadCount;
	if (dwPrereadCount==0) dwPrereadCount=5;
	m_PrereadCountInitial=m_PrereadCount=dwPrereadCount;

	CheckDimensions();
	
	PrepareRequest(m_LastAccessID);
	LeaveCriticalSection(&m_CSTableDataContainer);
	return ret;
}

DWORD CTableDataContainer::GetPrereadCount()
{
	return m_PrereadCount;
}

DWORD CTableDataContainer::GetLastReqTick()
{
	return m_LastReqTick;
}

DWORD CTableDataContainer::GetLastAccessID()
{
	return m_LastAccessID;
}

DWORD CTableDataContainer::GetMinAvID()
{
	return m_MinAvID;
}

DWORD CTableDataContainer::GetMaxAvID()
{
	return m_MaxAvID;
}

DWORD CTableDataContainer::SetMinAvID(DWORD dwMinAvID)
{
	EnterCriticalSection(&m_CSTableDataContainer);
	m_BulkCount=m_BulkCountInitial;
	m_PrereadCount=m_PrereadCountInitial;
	if (dwMinAvID>m_MaxAvID) dwMinAvID=m_MaxAvID;
	m_MinAvID=dwMinAvID;
	if (m_LastAccessID<m_MinAvID) m_LastAccessID=m_MinAvID;
	if (m_LastAccessID>m_MaxAvID) m_LastAccessID=m_MaxAvID;

	CheckDimensions();
	
	PrepareRequest(m_LastAccessID);
	LeaveCriticalSection(&m_CSTableDataContainer);
	return m_MinAvID;
}

DWORD CTableDataContainer::SetMaxAvID(DWORD dwMaxAvID)
{
	EnterCriticalSection(&m_CSTableDataContainer);
	m_BulkCount=m_BulkCountInitial;
	m_PrereadCount=m_PrereadCountInitial;

	if (dwMaxAvID<m_MinAvID) dwMaxAvID=m_MinAvID;
	m_MaxAvID=dwMaxAvID;
	if (m_LastAccessID<m_MinAvID) m_LastAccessID=m_MinAvID;
	if (m_LastAccessID>m_MaxAvID) m_LastAccessID=m_MaxAvID;
	CheckDimensions();
	PrepareRequest(m_LastAccessID);
	LeaveCriticalSection(&m_CSTableDataContainer);
	return m_MaxAvID;
}

DWORD CTableDataContainer::GetBulkCount()
{
	return m_BulkCount;
}

DWORD CTableDataContainer::SetBulkCount(DWORD dwBulkCount)
{
	EnterCriticalSection(&m_CSTableDataContainer);
	DWORD ret=m_BulkCount;
	m_BulkCountInitial=m_BulkCount=dwBulkCount;
	CheckDimensions();
	LeaveCriticalSection(&m_CSTableDataContainer);
	return ret;
}

DWORD CTableDataContainer::PrepareRequest(DWORD dwItemID)
{
	EnterCriticalSection(&m_CSTableDataContainer);
	if (dwItemID>m_MaxAvID) dwItemID=m_MaxAvID;
	if (dwItemID<m_MinAvID) dwItemID=m_MinAvID;
	if (m_ItemsArray && m_LastAccessID!=dwItemID)
	{
		DWORD dwItemIDcmp=dwItemID;
		DWORD dwDelta=m_BulkCount/2;
		if (dwItemIDcmp<m_MinAvID+dwDelta) dwItemIDcmp=m_MinAvID+dwDelta;
		if (dwItemIDcmp>m_MaxAvID-dwDelta) dwItemIDcmp=m_MaxAvID-dwDelta;

		m_ReqFirstID=dwItemIDcmp-dwDelta;
		m_RequestCount=m_BulkCount;
		DWORD m_tmpLastID=m_FirstID+m_ItemsCount-1;



		if (m_ReqFirstID<m_FirstID)
		{
			if (m_ReqFirstID+m_PrereadCount>m_FirstID)
			{  // don't need extra request
				m_ReqFirstID=m_FirstID;
				while(m_RequestCount>0 && m_ItemsArray[m_ReqFirstID+m_RequestCount-m_FirstID-1]) m_RequestCount--;
			}
			else
			{
				while(m_ReqFirstID>m_MinAvID && m_ReqFirstID+m_RequestCount-1>m_FirstID && m_ItemsArray[m_ReqFirstID+m_RequestCount-m_FirstID-1]) m_ReqFirstID--;
			}
		}
		else
		if (m_ReqFirstID+m_RequestCount>m_tmpLastID)
		{
			if (m_ReqFirstID+m_RequestCount-m_PrereadCount<m_tmpLastID)
			{  // don't need extra request

				while(m_ReqFirstID<m_tmpLastID && m_ItemsArray[m_ReqFirstID-m_FirstID]) m_ReqFirstID++;
				m_RequestCount=m_tmpLastID-m_ReqFirstID;

			}
			else
			{
				while(m_ReqFirstID<m_tmpLastID && m_ItemsArray[m_ReqFirstID-m_FirstID]) m_ReqFirstID++;
			}
		}
		else
		if (m_ItemsArray[m_ReqFirstID-m_FirstID])
		{
			while(m_ReqFirstID+m_RequestCount-1<m_tmpLastID && m_ItemsArray[m_ReqFirstID-m_FirstID] && m_ItemsArray[m_ReqFirstID+m_RequestCount-1-m_FirstID]==NULL) m_ReqFirstID++;
			while(m_RequestCount>0 && m_ItemsArray[m_ReqFirstID+m_RequestCount-1-m_FirstID]) m_RequestCount--;
		}
		else
		if (m_ItemsArray[m_ReqFirstID+m_RequestCount-m_FirstID])
		{
			while(m_ReqFirstID>m_FirstID && m_ItemsArray[m_ReqFirstID-m_FirstID]==NULL && m_ItemsArray[m_ReqFirstID+m_RequestCount-1-m_FirstID]) m_ReqFirstID--;
			while(m_RequestCount>0 && m_ItemsArray[m_ReqFirstID+m_RequestCount-1-m_FirstID]) m_RequestCount--;
		}

	}
	m_LastAccessID=dwItemID;
	LeaveCriticalSection(&m_CSTableDataContainer);
	return m_ItemsCount;
}

DWORD CTableDataContainer::ResetData()
{
	EnterCriticalSection(&m_CSTableDataContainer);
	if (m_ItemsArray)
	{
		DWORD i;
		for(i=0;i<m_ItemsCount;i++)
			if (m_ItemsArray[i])
			{
				delete m_ItemsArray[i];
				m_ItemsArray[i]=NULL;
			}
		delete[] m_ItemsArray;
		m_ItemsArray=NULL;
	}
	DWORD oldCount=m_ItemsCount;
	m_ItemsCount=0;
	m_FirstID=0;
	m_ReqFirstID=0;
	m_RequestCount=0;
	m_LastReqFirstID=0;
	m_LastReqLastID=0;
	m_MinAvID=0;
	m_MaxAvID=0;
	SetItemCount(oldCount?oldCount:1000, FALSE);

	LeaveCriticalSection(&m_CSTableDataContainer);
	return m_ItemsCount;
}

DWORD CTableDataContainer::CheckDimensions()
{
	if (m_BulkCount>m_ItemsCount/2) m_BulkCount=m_ItemsCount/2;
	if (m_PrereadCount>m_ItemsCount/4) m_PrereadCount=m_ItemsCount/4;
	if (m_BulkCount>(m_MaxAvID-m_MinAvID)/2) m_BulkCount=(m_MaxAvID-m_MinAvID)/2;
	if (m_PrereadCount>(m_MaxAvID-m_MinAvID)/4) m_PrereadCount=(m_MaxAvID-m_MinAvID)/4;

	if (!m_PrereadCount)m_PrereadCount=1;
	if (!m_BulkCount) m_BulkCount=1;
	return (m_BulkCountInitial!=m_BulkCount || m_PrereadCountInitial!=m_PrereadCount);
}
