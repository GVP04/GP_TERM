// PickProject.h: interface for the CPickProject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PICKPROJECT_H__D94D211B_3110_4CEF_B83E_5269C271528C__INCLUDED_)
#define AFX_PICKPROJECT_H__D94D211B_3110_4CEF_B83E_5269C271528C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PPickFiles.h"

class CPickProject : public CObject  
{
	friend class CDlgProject;
	friend class CDlgProjectPickFiles;

//	DECLARE_DYNAMIC( CPickProject )
	DECLARE_SERIAL(CPickProject)

public:
	BOOL SetModifyed(BOOL ibNewState);
	CString ProjectPickFileName;
	CString ProjectFileName;
	BOOL IsModifyed();
	BOOL SaveProject(const char *FileName);
	BOOL LoadProject(const char *FileName);
	CPickProject();
	virtual ~CPickProject();
	void Serialize( CArchive& archive );


private:
	BOOL m_bModified;
	CPPickFiles *m_PPickFiles;
};

#endif // !defined(AFX_PICKPROJECT_H__D94D211B_3110_4CEF_B83E_5269C271528C__INCLUDED_)
