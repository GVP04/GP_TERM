// GPCursor.h: interface for the GPCursor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPCursor_H__6FC4E840_3E2C_48AE_BDC8_38AE239254C7__INCLUDED_)
#define AFX_GPCursor_H__6FC4E840_3E2C_48AE_BDC8_38AE239254C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class GPCursor  
{
public:
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
	const CString SetName(const char *iName);
	const CString GetName();
	GPCursor(const char *iName);
	virtual ~GPCursor();
	HCURSOR CreateFromFile(LPCTSTR lpFileName);
	HCURSOR CreatePredefine(LPCTSTR lpCursorName, int cxDesired, int cyDesired);
	HCURSOR CreateFromImageList(LPCTSTR lpImagelListName, UINT nImage, int xHotSpot, int yHotSpot);
	BOOL GPClipCursor(CONST RECT *lpRect);
	virtual UINT DoMethod(const char *iStr, char *oStr, void *GPRArray);
	HCURSOR GetHCURSOR();
	HCURSOR SetHCURSOR(HCURSOR ihCur);
private:
	HCURSOR m_Cursor;
	CString Name;
};

#endif // !defined(AFX_GPCursor_H__6FC4E840_3E2C_48AE_BDC8_38AE239254C7__INCLUDED_)
