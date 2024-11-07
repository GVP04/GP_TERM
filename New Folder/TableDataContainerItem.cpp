// TableDataContainerItem.cpp: implementation of the CTableDataContainerItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "TableDataContainerItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTableDataContainerItem::CTableDataContainerItem(int iDefImage)
{
	m_defImage=iDefImage;
	Items=NULL;
	dwItemsCount=0;
	dwArrayCount=0;
}

CTableDataContainerItem::~CTableDataContainerItem()
{
	DeleteAllItems();
	dwItemsCount=0;
	dwArrayCount=0;
	if (Items) delete[] Items;
	Items=NULL;
}

DWORD CTableDataContainerItem::InsertItem(DWORD dwBefore, const char *iText, int iImage, DWORD iState, DWORD iStyle)
{
	if (iImage==-11) iImage=m_defImage;
	SetItemsCount(dwItemsCount+1);
	if (dwBefore<dwItemsCount)
	{
		DWORD i=dwItemsCount-1;
		VTABLEITEM *tmpItem=Items[i];
		for(;i>dwBefore;i--) Items[i]=Items[i-1];
		Items[i]=tmpItem;
	}
	return dwItemsCount;
}

DWORD CTableDataContainerItem::AddItem(const char *iText, int iImage, DWORD iState, DWORD iStyle)
{
	return InsertItem(-1,iText,iImage,iState,iStyle);
}

DWORD CTableDataContainerItem::DeleteItem(DWORD dwItemID)
{
	if (Items && dwItemID<dwItemsCount)
	{
		if (Items[dwItemID]) delete Items[dwItemID];
		Items[dwItemID]=NULL;
		DWORD i=dwItemID+1;
		for(;i<dwItemsCount;i++)
			Items[i-1]=Items[i];

		Items[--i]=NULL;
		dwItemsCount--;
		if ((dwItemsCount+10)*8<dwArrayCount) FreeExtra();
	}

	return dwItemsCount;
}

DWORD CTableDataContainerItem::DeleteAllItems()
{
	if (Items)
	{
		DWORD i;
		for(i=0;i<dwItemsCount;i++)
			if (Items[i]) {delete Items[i];Items[i]=NULL;}
		dwItemsCount=0;
	}

	return dwItemsCount;
}

DWORD CTableDataContainerItem::GetCount()
{
	return dwItemsCount;
}

DWORD CTableDataContainerItem::SetItemsCount(DWORD dwNewCount)
{
	DWORD i=0;
	if (dwItemsCount!=dwNewCount)
	{
		if (dwNewCount>dwArrayCount)
		{
			dwArrayCount=dwNewCount+10;
			VTABLEITEM **tmpItem= new VTABLEITEM * [dwArrayCount];
			if (Items)
			{
				for(;i<dwItemsCount;i++)
					tmpItem[i]=Items[i];
				delete[] Items;

			}
			Items=tmpItem;
			for(;i<dwArrayCount;i++) Items[i]=NULL;
		}
		if (dwItemsCount<dwNewCount)
			for(i=dwItemsCount;i<dwNewCount;i++)
			{
				Items[i]=new VTABLEITEM;
				Items[i]->nImage=0;
				Items[i]->dwState=0;
				Items[i]->dwStyle=0;
			}
		else
			for(i=dwNewCount+1;i<dwItemsCount;i++)
				if (Items[i])
				{
					delete Items[i];
					Items[i]=NULL;
				}
	}

	return dwItemsCount=dwNewCount;
}

DWORD CTableDataContainerItem::FreeExtra()
{
	if (Items && (dwItemsCount+10)*8<dwArrayCount)
	{
		dwArrayCount=dwItemsCount+10;
		VTABLEITEM **tmpItem= new VTABLEITEM * [dwArrayCount];
		DWORD i=0;
		for(;i<dwArrayCount;i++)
			tmpItem[i]=Items[i];
		delete[] Items;
		Items=tmpItem;
	}
	return dwItemsCount;
}

PVTABLEITEM CTableDataContainerItem::GetItem(DWORD dwItemId)
{
	PVTABLEITEM ret=NULL;
	if (Items && dwItemId<dwItemsCount && Items[dwItemId]) ret=Items[dwItemId];
	return ret;
}


CTableDataContainerItem & CTableDataContainerItem::operator= (const CTableDataContainerItem &iCTableDataContainerItem)
{
	if (this!=&iCTableDataContainerItem && &iCTableDataContainerItem)
	{
		if (dwItemsCount==iCTableDataContainerItem.dwItemsCount)
		{
		}
		else
		{
			DeleteAllItems();
			SetItemsCount(iCTableDataContainerItem.dwItemsCount);
		}
		if (Items)
		{
			DWORD i;
			for(i=0; i<dwItemsCount;i++)
			{
				PVTABLEITEM dst=Items[i];
				if (Items[i])
				{
					PVTABLEITEM src=iCTableDataContainerItem.Items[i];

					dst->dwState=src->dwState;
					dst->dwStyle=src->dwStyle;
					dst->nImage =src->nImage;
					dst->csText =src->csText;
				}
			}
		}
	}
	return *this;
}
