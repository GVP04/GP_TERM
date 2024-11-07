// GPWndPropertyArrayItem.h: interface for the CGPWndPropertyArrayItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPWNDPROPERTYARRAYITEM_H__A3C1FB9E_1681_4D57_A871_FE47E9007E7A__INCLUDED_)
#define AFX_GPWNDPROPERTYARRAYITEM_H__A3C1FB9E_1681_4D57_A871_FE47E9007E7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct _GPPAITEM
{
	DWORD OnAddStyle;
	DWORD OnAddStyleEx;
	DWORD OnDelStyle;
	DWORD OnDelStyleEx;
	DWORD OffAddStyle;
	DWORD OffAddStyleEx;
	DWORD OffDelStyle;
	DWORD OffDelStyleEx;
} GPPAITEM, *PGPPAITEM;

#define GPPAI_ALLWINDOWS	GPRA_ALLITEMS

class CGPWndPropertyArrayItem : public CObject  
{
public:
	UINT AddWnd(HWND iHWND, GPPAITEM & Styles);
	UINT DeleteWnd(HWND iHWND);
	UINT SetWnd(HWND iHWND, GPPAITEM & Styles);
	UINT WndAddStyles(HWND iHWND, GPPAITEM & Styles);
	UINT WndDelStyles(HWND iHWND, GPPAITEM & Styles);
	UINT WndClearStyles(HWND iHWND, GPPAITEM & Styles);
	UINT GetCount();
	void SetOnStyles();
	void SetOffStyles();
	CGPWndPropertyArrayItem();
	virtual ~CGPWndPropertyArrayItem();
	CGPWndPropertyArrayItem & operator= (const CGPWndPropertyArrayItem &iGPPAI);
	GPPAITEM & operator[](UINT nItem);

private:
	GP_RarefiedArr<GPPAITEM> ArrStyles;
};

#endif // !defined(AFX_GPWNDPROPERTYARRAYITEM_H__A3C1FB9E_1681_4D57_A871_FE47E9007E7A__INCLUDED_)
