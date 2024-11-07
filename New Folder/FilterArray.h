// FilterArray.h: interface for the CFilterArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILTERARRAY_H__8C4BAFE9_3238_4522_87D3_FA2C28609834__INCLUDED_)
#define AFX_FILTERARRAY_H__8C4BAFE9_3238_4522_87D3_FA2C28609834__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct _SPRFILTERITEM
{
	UINT nField;
	UINT uCompare;
	UINT uLogOperation;
	CString csFilter;
	CString csName;
} SPRFILTERITEM, *PSPRFILTERITEM;



class CFilterArray : public CObject 
{
	DECLARE_DYNAMIC( CFilterArray )
public:
	const CString GetFilter(UINT iField);
	BOOL IsItemInFilter(CString *Item, UINT nItem);
	UINT SetFilter(UINT nItem, const char * iStr, UINT LogType = 0);
	CFilterArray();
	virtual ~CFilterArray();
	void DeleteAll();
	const char * GetFilterName(UINT uNFilter);
	UINT GetCount();
	UINT DeleteFilter(const char * FilterName);
	UINT DeleteFilter(UINT FieldNum);
	const SPRFILTERITEM * GetFilter(const char * FilterName);

private:
	SPRFILTERITEM * CreateFilter(UINT nItem);
	UINT GetFilterId(const char * iFilterName);
	SPRFILTERITEM **m_Array;
	UINT m_uMaxFilter;
	UINT m_uNFilter;
};

#endif // !defined(AFX_FILTERARRAY_H__8C4BAFE9_3238_4522_87D3_FA2C28609834__INCLUDED_)
