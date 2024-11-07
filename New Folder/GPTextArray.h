// GPTextArray.h: interface for the GPTextArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPTEXTARRAY_H__D0BA3361_B9B8_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GPTEXTARRAY_H__D0BA3361_B9B8_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define GPTAC_STRING	0
#define GPTAC_NUMERIC	1


class GPTextArray  
{
public:
	DWORD GetItemData(UINT nItem);
	BOOL SetItemData(UINT nItem,DWORD iData);
	void * GetItem(UINT num);
	void ClearAll();
	char * SetItem(UINT ItemNumber, const char *NewValue);
	int CompareItems( UINT num1, UINT num2, UINT Type);
	UINT GetItemCount();
	BOOL DeleteItem(UINT ItemNumber);
	char * InsertItem(UINT ItemNumber, const char *NewItem);
	char * AddItem(char *NewItem);
	GPTextArray(UINT n);
	GPTextArray();
	virtual ~GPTextArray();
	CString csItemData;

private:
	DWORD * ItemData;
	UINT nItems;
	char ** CharArray;
};

#endif // !defined(AFX_GPTEXTARRAY_H__D0BA3361_B9B8_11D2_B27D_00600840D054__INCLUDED_)
