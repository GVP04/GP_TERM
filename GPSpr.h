// GPSpr.h: interface for the CGPSpr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPSPR_H__29588905_D1DE_11D4_AB17_004854899618__INCLUDED_)
#define AFX_GPSPR_H__29588905_D1DE_11D4_AB17_004854899618__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define GPSPRFILL_COMBOBOX  1
#define GPSPRFILL_LISTBOX   2
#define GPSPRFILL_LISTCTRL  3
#define GPSPRFILL_COMLISTCTRL  4
#define GPSPRFILL_COMBOBOXEX  5

#define GPSPRFILL_USEDATA	0x10000

#include "FilterArray.h"

class CGPSpr  
{
friend class CGPSprArray;
public:
	const CString GetSort(UINT iField);
	const CString GetFilter(UINT iField);
	long ReplaceObjectEx(LPDISPATCH lpDisp, long StartItem, long EndItem, char *ItemsFlags, const char *Params);
	long ReplaceObjectEx(HWND ihWnd, UINT ObjType, long StartItem, long EndItem, char *ItemsFlags, const char *Params);
	long FillByArray(const VARIANT FAR& KeyArray, long nField, VARIANT FAR* RetArray);
	long ReplaceObject(HWND ihWnd, UINT ObjType, const char *Params);
	long FillObject(LPDISPATCH lpDisp, const char *Params, long FillType);
	long FillObject(HWND ihWnd, UINT ObjType, const char *Params, long FillType);
	long GetSprInfo(VARIANT *SprInfo, DWORD dwArrayType);
	UINT GetCount();
	CString * FindNextItem(UINT inField, const CString &iValue);
	CString * FindNextItemExact(UINT inField, const CString &iValue);
	CString * FindItem(UINT inField, const CString &iValue);
	CString * FindItemExact(UINT inField, const CString &iValue);
	CString * FindNextItem(UINT inField, const char *iValue);
	CString * FindNextItemExact(UINT inField, const char *iValue);
	CString * FindItem(UINT inField, const char *iValue);
	CString * FindItemExact(UINT inField, const char *iValue);

	CString * FindNextItemF(UINT inField, const CString &iValue);
	CString * FindNextItemExactF(UINT inField, const CString &iValue);
	CString * FindItemF(UINT inField, const CString &iValue);
	CString * FindItemExactF(UINT inField, const CString &iValue);
	CString * FindNextItemF(UINT inField, const char *iValue);
	CString * FindNextItemExactF(UINT inField, const char *iValue);
	CString * FindItemF(UINT inField, const char *iValue);
	CString * FindItemExactF(UINT inField, const char *iValue);

	BOOL IsItemInFilter(UINT nItem);
	CString * GetNextItem();
	UINT uPosition;
	void MoveFirst();
	const static enum SortOptionsEnum
	{
		GPS_ASCENDING=0,	GPS_DESCENDING=0x1,		GPS_USEFILTER=0x2,		GPS_USEPRIOR=0x4,
	};                                                                                                                                                                                                  
	const static enum SortOptionsMaskEnum
	{
		GPS_SORTORDERMASK=0x0001,	GPS_USEFILTERMASK=0x0002,	GPS_USEPRIORMASK=0x0004,
	};

	void SortSprAsNum(CString **Item, UINT *Flds, int left, int right, UINT Options);
	void SortSpr(CString **Item, UINT *Flds, int left, int right, UINT Options);
	void SetSortPriorItem(UINT nItem,const char *iStr);
	void SetSortPrior(const char *iStr);
	void SetFilterItem(UINT nItem, const char *iStr);
	void SetFilter(const char *iStr);
	CString RetCString;
	CString * GetItem(UINT nItem);
	CString * GetSubItem(UINT nItem,UINT nSubItem);
	UINT DeleteItem(UINT nItem);
	UINT SetItem(UINT nItem,const char *iStr);
	UINT SetSubItem(UINT nItem,UINT nSubItem,const char *iStr);
	UINT InsertEmpty(UINT inBefore, UINT iCount);
	void Destroy();
	const char * GetName();
	UINT GetNItem();
	UINT GetNField();
	BOOL Create(const char * iName,UINT inField);
	UINT DoMethod(const char *iStr, char ** oStr);
	CGPSpr();
	virtual ~CGPSpr();

	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];

private:
	long GetItemAsArray(UINT nItem, VARIANT FAR* RetArray);
	CString * SortPriorArray;
	CFilterArray m_FilterArray;
	CString SprName;
	CString ** CSprArr;
	UINT nFields;
	UINT nSpr;
	UINT nmaxSpr;
};

#endif // !defined(AFX_GPSPR_H__29588905_D1DE_11D4_AB17_004854899618__INCLUDED_)
