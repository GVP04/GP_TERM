// GPSprArray.h: interface for the CGPSprArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPSPRARRAY_H__F19EED91_ABAE_4292_BB16_BADE9A0D486D__INCLUDED_)
#define AFX_GPSPRARRAY_H__F19EED91_ABAE_4292_BB16_BADE9A0D486D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GPSpr.h"

class CGPSprArray  
{
public:
	long ReplaceOblectEx(LPDISPATCH lpDisp, long StartItem, long EndItem, const char *Params);
	long ReplaceOblectEx(HWND ihWnd, UINT ObjType, long StartItem, long EndItem, const char *Params);
	long FillByArray(LPCTSTR SprName, const VARIANT FAR& KeyArray, long nField, VARIANT FAR* RetArray);
	long ReplaceObject(const char *SprName,HWND ihWnd, UINT ObjType, const char *Params);
	long FillObject(const char *SprName,HWND ihWnd, UINT ObjType, const char *Params, long FillType);
	long FillObject(const char *SprName,LPDISPATCH lpDisp, const char *Params, long FillType);
	UINT DoMethod(const char *iSprName, const char *iStr, char ** oStr);
	long GetSprInfos(VARIANT *ListInfo, DWORD dwArrType);
	UINT GetArrayDescr(CString &str);
	const char * GetSprName(UINT uNSpr);
	UINT GetCount();
	UINT DeleteSpr(const char * SprName);
	CGPSpr * CreateSpr(const char * SprName);
	CGPSpr * GetSpr(const char * SprName);
	CGPSprArray();
	virtual ~CGPSprArray();
private:
	UINT GetSprId(const char * iSprName);
	CGPSpr **m_Array;
	UINT m_uMaxSpr;
	UINT m_uNSpr;

};

#endif // !defined(AFX_GPSPRARRAY_H__F19EED91_ABAE_4292_BB16_BADE9A0D486D__INCLUDED_)
