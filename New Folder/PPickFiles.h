// PPickFiles.h: interface for the CPPickFiles class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PPICKFILES_H__C4DCC4C9_60E9_4DF4_8DD5_22E90864BF07__INCLUDED_)
#define AFX_PPICKFILES_H__C4DCC4C9_60E9_4DF4_8DD5_22E90864BF07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PPickFile.h"

class CPPickFiles : public CObject  
{
//	DECLARE_DYNAMIC( CPPickFiles )
	DECLARE_SERIAL(CPPickFiles)
public:
	UINT FillTree(CTreeCtrl * iTree);
	void Sort();
	CPPickFiles();
	virtual ~CPPickFiles();
	CPPickFile * GetFile(const char *iFileVarName);
	CPPickFile * AddFile(const char *iFileVarName);
	UINT GetFileId(const char *iFileVarName);
	UINT DeleteFile(const char *iFileVarName);
	UINT GetFilesCount();
	CPPickFiles * GetGroup(const char *iGroupName);
	CPPickFiles * AddGroup(const char *iGroupName);
	UINT GetGroupId(const char *iGroupName);
	UINT DeleteGroup(const char *iGroupName);
	UINT GetGroupsCount();
	CString GroupName;
	void Serialize( CArchive& archive );

private:
	void qsFiles(int left, int right);
	void qsGroups(int left, int right);
	CString GetFileVarName(UINT uNFile);
	CString GetGroupName(UINT uNGroup);
	CPPickFile **m_FilesArray;
	CPPickFiles **m_GroupsArray;
	UINT m_uMaxFiles;
	UINT m_uNFiles;
	UINT m_uMaxGroups;
	UINT m_uNGroups;

};

#endif // !defined(AFX_PPICKFILES_H__C4DCC4C9_60E9_4DF4_8DD5_22E90864BF07__INCLUDED_)
