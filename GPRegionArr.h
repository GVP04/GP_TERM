// GPRegionArr.h: interface for the GPRegionArr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPREGIONARR_H__0AE199FE_6479_48C6_BB97_80D2E3BC493A__INCLUDED_)
#define AFX_GPREGIONARR_H__0AE199FE_6479_48C6_BB97_80D2E3BC493A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GPRegion.h"

class GPRegionArr  
{
public:
	void DeleteAll();
	GPRegionArr();
	virtual ~GPRegionArr();
	UINT DoMethod(const char *iRgnName, const char *iStr, char *oStr);
	const char * GetRgnName(UINT uNRgn);
	UINT GetCount();
	UINT GPDeleteRgn(const char * RgnName);
	GPRegion * CreateRgn(const char * RgnName);
	GPRegion * GetRgn(const char * RgnName);

private:
	UINT GetRgnId(const char * iRgnName);
	GPRegion **m_Array;
	UINT m_uMaxRgn;
	UINT m_uNRgn;
};

#endif // !defined(AFX_GPREGIONARR_H__0AE199FE_6479_48C6_BB97_80D2E3BC493A__INCLUDED_)
