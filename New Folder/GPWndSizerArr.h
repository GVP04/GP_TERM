// GPWndSizerArr.h: interface for the CGPWndSizerArr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPWNDSIZERARR_H__AC20EE84_DE48_4C28_B26B_031DF741DB6B__INCLUDED_)
#define AFX_GPWNDSIZERARR_H__AC20EE84_DE48_4C28_B26B_031DF741DB6B__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GPWndSizer.h"

class CGPWndSizerArr : public CObject  
{
	friend class GPUnit;
	friend class CDlgDrawEdit;
public:
	void UpdateSizer(const char *iName);
	void UpdateSizers();
	UINT GetGrow();
	UINT SetGrow(UINT newGrow);
	HWND m_ParentHwnd;
	HWND AddSizer(const char * iStr);
	HWND SetSizer(const char * iStr);
	HWND SetSizerIcon(const char * iStr);
	HWND SetSizerRgn(const char * iStr);
	HWND SetSizerBrush(const char * iStr);
	UINT RemoveSizer(const char * iName);
	CGPWndSizerArr(HWND iParentHWND);
	virtual ~CGPWndSizerArr();
private:
	UINT m_nGrow;
	UINT GetSizerId(const char *iName);
	CGPWndSizer **m_Array;
	UINT m_nSizers;
	UINT m_nMaxSizers;
};

#endif // !defined(AFX_GPWNDSIZERARR_H__AC20EE84_DE48_4C28_B26B_031DF741DB6B__INCLUDED_)
