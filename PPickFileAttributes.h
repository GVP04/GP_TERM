// PPickFileAttributes.h: interface for the CPPickFileAttributes class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PPICKFILEATTRIBUTES_H__ED48361F_0DA6_4A20_B28B_04B6F7709490__INCLUDED_)
#define AFX_PPICKFILEATTRIBUTES_H__ED48361F_0DA6_4A20_B28B_04B6F7709490__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PPickFileAttribute.h"

class CPPickFileAttributes : public CObject  
{
//	DECLARE_DYNAMIC( CPPickFileAttributes )
	DECLARE_SERIAL(CPPickFileAttributes)
public:
	CPPickFileAttributes();
	virtual ~CPPickFileAttributes();
	CPPickFileAttribute * GetAttribute(const char *AttributeName);
	CPPickFileAttribute * AddAttribute(const char *AttributeName);
	UINT GetFileId(const char *iAttributeName);
	UINT DeleteAttribute(const char *AttributeName);
	UINT GetCount();
	void Serialize( CArchive& archive );

private:
	CString GetAttributeName(UINT uNAttribute);
	CPPickFileAttribute **m_Array;
	UINT m_uMaxAttributes;
	UINT m_uNAttributes;

};

#endif // !defined(AFX_PPICKFILEATTRIBUTES_H__ED48361F_0DA6_4A20_B28B_04B6F7709490__INCLUDED_)
