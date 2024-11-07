// GPHandleArray.h: interface for the CGPHandleArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPHANDLEARRAY_H__F19EED91_ABAE_4292_BB16_BADE9A0D486D__INCLUDED_)
#define AFX_GPHANDLEARRAY_H__F19EED91_ABAE_4292_BB16_BADE9A0D486D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct _HANDLEARRAYITEM
{
	UINT uSize;
	UINT uType;
	HANDLE handle;
	DWORD dwId;
	DWORD dwItemData;
	CString csName;
} HANDLEARRAYITEM, *PHANDLEARRAYITEM;

#define HANDLER_TYPE_VOID	0x0000
#define HANDLER_TYPE_HKEY	0x0001
#define HANDLER_TYPE_HKEY_PREDEF	0x0002

class CGPHandleArray  
{
public:
	const CString EnumHandlers(UINT iIndex);
	UINT GetCount();
	UINT DeleteHandle(const char * HandleName);
	HANDLEARRAYITEM & CreateHandle(const char * HandleName);
	HANDLEARRAYITEM & CreateHandle(HANDLEARRAYITEM & iValue);
	CGPHandleArray();
	virtual ~CGPHandleArray();
	HANDLEARRAYITEM &operator[](HANDLE nHandle)
	{
		if (nHandle==(HANDLE)-1) return InitValue;
		UINT Id=FindItemByHANDLE(nHandle);
		if (Id==0xFFFFFFFFL) return TMPValue;
		return *m_Array[Id];
	}
	HANDLEARRAYITEM &operator[](const char *iName)
	{
		if (*iName==0) return InitValue;
		UINT Id=FindItemByName(iName);
		if (Id==0xFFFFFFFFL) return TMPValue;
		return *m_Array[Id];
	}

	void ResetItem(HANDLEARRAYITEM *iItem);
	static void FreeHandle(HANDLEARRAYITEM &iItem);

private:
	void FreeHandle(UINT iId);
	HANDLEARRAYITEM * AddEmpty();
	UINT FindItemByHANDLE(HANDLE iHandle);
	UINT FindItemByName(const char *iName);
	HANDLEARRAYITEM **m_Array;
	HANDLEARRAYITEM InitValue;
	HANDLEARRAYITEM TMPValue;
	UINT m_uMaxHandle;
	UINT m_uNHandle;
};

#endif // !defined(AFX_GPHANDLEARRAY_H__F19EED91_ABAE_4292_BB16_BADE9A0D486D__INCLUDED_)
