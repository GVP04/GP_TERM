// GPIOFileArray.h: interface for the GPIOFileArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPIOFILEARRAY_H__44075D3F_0ABE_49CD_8AC0_F314C456075D__INCLUDED_)
#define AFX_GPIOFILEARRAY_H__44075D3F_0ABE_49CD_8AC0_F314C456075D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GPIOFile.h"

class GPIOFileArray  
{
public:
	BOOL SetEventEditor(const char *iFileName, HWND iEditor);
	void ClearEventEditiors();
	void ReadIOFiles();
	GPIOFileArray();

	virtual ~GPIOFileArray();
	UINT DoMethod(const char *iIOFileName, const char *iStr, char ** oStr);
	UINT GetArrayDescr(CString &str);
	const char * GetIOFileName(UINT uNIOFile);
	UINT GetCount();
	UINT DeleteIOFile(const char * IOFileName);
	GPIOFile * CreateIOFile(const char * IOFileName);
	GPIOFile * GetIOFile(const char * IOFileName);

private:
	UINT GetIOFileId(const char * iIOFileName);
	GPIOFile **m_Array;
	UINT m_uMaxIOFile;
	UINT m_uNIOFile;

};

#endif // !defined(AFX_GPIOFILEARRAY_H__44075D3F_0ABE_49CD_8AC0_F314C456075D__INCLUDED_)
