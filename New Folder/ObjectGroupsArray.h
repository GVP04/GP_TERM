// ObjectGroupsArray.h: interface for the CObjectGroupsArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ObjectGroupsARRAY_H__8C4BAFE9_3238_4529_87D3_FA2C28609834__INCLUDED_)
#define AFX_ObjectGroupsARRAY_H__8C4BAFE9_3238_4529_87D3_FA2C28609834__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GPUnit.h"

typedef struct _OBJECTGROUPITEM
{
	CString csGroupName;
	GPUnit *pUnit;
} OBJECTGROUPITEM, *POBJECTGROUPITEM;

class CObjectGroupsArray : public CObject 
{
	DECLARE_DYNAMIC( CObjectGroupsArray )
public:
	BOOL IsObjectGroups(CString *Item);
	CObjectGroupsArray();
	virtual ~CObjectGroupsArray();
	void DeleteAll();
	UINT GetCount();
	UINT DeleteObjectGroups(const char * ObjectGroupsName);
	UINT DeleteObjectGroups(const char * ObjectGroupsName, const GPUnit *pGPUnit);
	UINT DeleteObjectGroups(const GPUnit *pGPUnit);
	OBJECTGROUPITEM * CreateObjectGroups(const char * ObjectGroupsName,  const GPUnit *pGPUnit);

private:
	OBJECTGROUPITEM **m_Array;
	UINT m_uMaxObjectGroups;
	UINT m_uNObjectGroups;
};

#endif // !defined(AFX_ObjectGroupsARRAY_H__8C4BAFE9_3238_4529_87D3_FA2C28609834__INCLUDED_)
