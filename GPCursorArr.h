// GPCursorArr.h: interface for the GPCursorArr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPCursorARR_H__0AE199FE_6479_48C6_BB97_80D2E3BC493A__INCLUDED_)
#define AFX_GPCursorARR_H__0AE199FE_6479_48C6_BB97_80D2E3BC493A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GPCursor.h"

class GPCursorArr  
{
public:
	void DeleteAll();
	GPCursorArr();
	virtual ~GPCursorArr();
	UINT DoMethod(const char *iCursorName, const char *iStr, char *oStr);
	const char * GetCursorName(UINT uNCursor);
	const char * GetCursorNameByHCUR(HCURSOR hCur);
	UINT GetCount();
	UINT DeleteCursor(const char * CursorName);
	GPCursor * CreateCursor(const char * CursorName);
	GPCursor * GetCursor(const char * CursorName);

private:
	UINT GetCursorId(const char * iCursorName);
	GPCursor **m_Array;
	UINT m_uMaxCursor;
	UINT m_uNCursor;
};

#endif // !defined(AFX_GPCursorARR_H__0AE199FE_6479_48C6_BB97_80D2E3BC493A__INCLUDED_)
