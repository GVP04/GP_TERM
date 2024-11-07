// PPickFile.h: interface for the CPPickFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PPICKFILE_H__0DEAD29A_6FCE_4F92_83BD_674E17B21E9E__INCLUDED_)
#define AFX_PPICKFILE_H__0DEAD29A_6FCE_4F92_83BD_674E17B21E9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PPickFileAttributes.h"

class CPPickFile : public CObject  
{
//	DECLARE_DYNAMIC( CPPickFile )
	DECLARE_SERIAL(CPPickFile)
public:
	CString AccountName;
	CString FileVarName;
	CString PickFileName;
	CString PickFileDataName;
	CPPickFile();
	virtual ~CPPickFile();
	CPPickFileAttributes *m_PPickFileAttributes;
	void Serialize( CArchive& archive );

};

#endif // !defined(AFX_PPICKFILE_H__0DEAD29A_6FCE_4F92_83BD_674E17B21E9E__INCLUDED_)
