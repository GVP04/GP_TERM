// TableDataContainer.h: interface for the CTableDataContainer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABLEDATACONTAINER_H__3B143345_2424_466A_A3A0_F74E1A62EAAB__INCLUDED_)
#define AFX_TABLEDATACONTAINER_H__3B143345_2424_466A_A3A0_F74E1A62EAAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TableDataContainerItem.h"

class CTableDataContainer  
{
public:
	DWORD CheckDimensions();
	DWORD ResetData();
	DWORD PrepareRequest(DWORD dwItemID);
	CTableDataContainer();
	virtual ~CTableDataContainer();
	DWORD SetItemText(DWORD dwID, DWORD dwSubId, const char *iText);
	DWORD SetItemImage(DWORD dwID, DWORD dwSubId, DWORD dwImage);
	DWORD SetItemState(DWORD dwID, DWORD dwSubId, DWORD dwState);
	DWORD SetItemStyle(DWORD dwID, DWORD dwSubId, DWORD dwStyle);
	DWORD SetItem(DWORD dwID, const CTableDataContainerItem *pItem);
	const char *GetItemText(DWORD dwID, DWORD dwSubId = 0);
	DWORD GetItemImage(DWORD dwID, DWORD dwSubId = 0);
	DWORD GetItemState(DWORD dwID, DWORD dwSubId = 0);
	DWORD GetItemStyle(DWORD dwID, DWORD dwSubId = 0);
	CTableDataContainerItem * GetItem(DWORD dwID);
	CTableDataContainerItem * GetCreateItem(DWORD dwID);
	PVTABLEITEM GetSubItem(DWORD dwID, DWORD dwSubId = 0);
	PVTABLEITEM GetCreateSubItem(DWORD dwID, DWORD dwSubId = 0);
	DWORD SetItemCount(DWORD dwCount, BOOL bEnd = TRUE);
	DWORD GetItemCount();
	DWORD SetColumnCount(DWORD dwColumnCount);
	DWORD GetColumnCount();
	DWORD InsertColumn(DWORD dwBefore = 0xFFFFFFFF);
	DWORD DeleteColumn(DWORD dwColumn);
	DWORD SetFirstID(DWORD dwFirstID);
	DWORD GetFirstID();
	DWORD SetPageSize(DWORD dwPageSize);
	DWORD GetPageSize();
	DWORD GetRequest(DWORD & dwStartFromID, DWORD & dwLength);
	DWORD SetPrereadCount(DWORD dwPrereadCount);
	DWORD GetPrereadCount();
	DWORD SetCurrentPos(DWORD dwCurrentPos);
	DWORD GetCurrentPos();
	DWORD GetLastReqTick();
	DWORD GetLastAccessID();
	DWORD GetMinAvID();
	DWORD GetMaxAvID();
	DWORD SetMinAvID(DWORD dwMinAvID);
	DWORD SetMaxAvID(DWORD dwMaxAvID);
	DWORD GetBulkCount();
	DWORD SetBulkCount(DWORD dwBulkCount);
	int SetDefImage(int iDefImage);
	int GetDefImage();

private:
	CRITICAL_SECTION m_CSTableDataContainer;
	DWORD m_LastAccessID;
	DWORD m_ItemsCount;
	DWORD m_MinAvID;
	DWORD m_MaxAvID;
	DWORD m_FirstID;
	DWORD m_ReqFirstID;
	DWORD m_RequestCount;
	DWORD m_LastReqFirstID;
	DWORD m_LastReqLastID;
	DWORD m_PrereadCount;
	DWORD m_PrereadCountInitial;
	DWORD m_BulkCount;
	DWORD m_BulkCountInitial;
	DWORD m_SubItemsCount;
	DWORD m_LastReqTick;
	int m_DefImage;
	CTableDataContainerItem **m_ItemsArray;
};

#endif // !defined(AFX_TABLEDATACONTAINER_H__3B143345_2424_466A_A3A0_F74E1A62EAAB__INCLUDED_)

