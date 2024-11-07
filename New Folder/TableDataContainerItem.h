// TableDataContainerItem.h: interface for the CTableDataContainerItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABLEDATACONTAINERITEM_H__D55DCFC5_90F7_427A_9436_F0CC76A8D1B9__INCLUDED_)
#define AFX_TABLEDATACONTAINERITEM_H__D55DCFC5_90F7_427A_9436_F0CC76A8D1B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct _VTABLEITEM
{
	int nImage;
	DWORD dwState;
	DWORD dwStyle;
	CString csText;
} VTABLEITEM, *PVTABLEITEM;

class CTableDataContainerItem  
{
public:
	CTableDataContainerItem(int iDefImage);
	virtual ~CTableDataContainerItem();

	DWORD InsertItem(DWORD dwBefore, const char *iText = "", int iImage = -11, DWORD iState = 0, DWORD iStyle = 0);
	DWORD AddItem(const char *iText = "", int iImage = -11, DWORD iState = 0, DWORD iStyle = 0);
	DWORD DeleteItem(DWORD dwItemID);
	DWORD DeleteAllItems();
	DWORD GetCount();
	DWORD SetItemsCount(DWORD dwNewCount);
	DWORD FreeExtra();
	PVTABLEITEM GetItem(DWORD dwItemId);
	CTableDataContainerItem & operator= (const CTableDataContainerItem &iCTableDataContainerItem);

private:
	VTABLEITEM **Items;
	DWORD dwItemsCount;
	DWORD dwArrayCount;
	int m_defImage;
};

#endif // !defined(AFX_TABLEDATACONTAINERITEM_H__D55DCFC5_90F7_427A_9436_F0CC76A8D1B9__INCLUDED_)
