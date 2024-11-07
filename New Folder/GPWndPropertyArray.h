// GPWndPropertyArray.h: interface for the CGPWndPropertyArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPWNDPROPERTYARRAY_H__31483A44_E3C3_47E6_BCEA_D94DC0E676E7__INCLUDED_)
#define AFX_GPWNDPROPERTYARRAY_H__31483A44_E3C3_47E6_BCEA_D94DC0E676E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GPWndPropertyArrayItem.h"

class CGPWndPropertyArray : public CObject  
{
	DECLARE_SERIAL(CGPWndPropertyArray)
public:
	CGPWndPropertyArray();
	virtual ~CGPWndPropertyArray();
	void Serialize( CArchive& archive );



	int GetIdsList(CString & iStr, const char *iDelimiter);

	CGPWndPropertyArrayItem &operator[](UINT nItem)
	{
		if (nItem==-1) return defItem;
		return m_Array[nItem];
	}

	void SetOnStyles(DWORD iId);
	void SetOffStyles(DWORD iId);

private:
	GP_RarefiedArr<CGPWndPropertyArrayItem> m_Array;
	UINT m_LastSet;
	CGPWndPropertyArrayItem defItem;
};

#endif // !defined(AFX_GPWNDPROPERTYARRAY_H__31483A44_E3C3_47E6_BCEA_D94DC0E676E7__INCLUDED_)
