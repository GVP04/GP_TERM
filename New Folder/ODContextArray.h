// ODContextArray.h: interface for the CODContextArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ODCONTEXTARRAY_H__6AFA2D1E_D3E7_4A72_BFA5_C534F9168552__INCLUDED_)
#define AFX_ODCONTEXTARRAY_H__6AFA2D1E_D3E7_4A72_BFA5_C534F9168552__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ODContext.h"

class CODContextArray  
{
public:
	CODContextArray();
	virtual ~CODContextArray();

	const CString EnumContextrs(UINT iIndex);
	UINT GetCount();
	UINT DeleteContext(const char * ContextName);
	CODContext * CreateContext(const char * ContextName);
	CODContext * CreateContext(CODContext & iValue);
	CODContext * GetContext(const char * ContextName);
	CODContext * LoadContext(const char * ccContextName, const char * ccFileName);
	CODContext * SaveContext(const char * ccContextName, const char * ccFileName);
	int DoContextMethod(const char * ccContextNameMethod, char *oStr);
	int DoContextMethod(const char * ccContextName, const char * ccMethodName, char *oStr);

	void ResetItem(CODContext *iItem);
	void PaintByDRAWITEMSTRUCT(GPUnit *gpuRes, WPARAM wParam, LPDRAWITEMSTRUCT lPDiStruct, GPMenu *pMenu);
	BOOL MeasureItem(GPUnit *gpuRes, WPARAM wParam, LPMEASUREITEMSTRUCT lPDiStruct, GPMenu *pMenu);

	CODContext *pTerminalMenuContext;
private:
	CODContext * AddEmpty();
	UINT FindItemByContext(CODContext *iContext);
	UINT FindItemByName(const char *iName);
	CODContext **m_Array;
	UINT m_uMaxContext;
	UINT m_uNContext;
	UINT m_CurrentContextNum;

};







#endif // !defined(AFX_ODCONTEXTARRAY_H__6AFA2D1E_D3E7_4A72_BFA5_C534F9168552__INCLUDED_)
