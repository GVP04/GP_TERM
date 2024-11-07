// PPickFileAttribute.h: interface for the CPPickFileAttribute class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PPICKFILEATTRIBUTE_H__CD66FE40_4AC0_4E95_BEBB_A362030F47A7__INCLUDED_)
#define AFX_PPICKFILEATTRIBUTE_H__CD66FE40_4AC0_4E95_BEBB_A362030F47A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPPickFileAttribute : public CObject  
{
//	DECLARE_DYNAMIC( CPPickFileAttribute )
public:
	CPPickFileAttribute();
	virtual ~CPPickFileAttribute();

	CString AttributeName;
	void Serialize( CArchive& archive );

	DECLARE_SERIAL(CPPickFileAttribute)

};


#endif // !defined(AFX_PPICKFILEATTRIBUTE_H__CD66FE40_4AC0_4E95_BEBB_A362030F47A7__INCLUDED_)
