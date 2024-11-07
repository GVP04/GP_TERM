// GPContextMenu.h: interface for the CGPContextMenu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPCONTEXTMENU_H__C380AAB9_1DBE_4046_ABED_43624C08CBEF__INCLUDED_)
#define AFX_GPCONTEXTMENU_H__C380AAB9_1DBE_4046_ABED_43624C08CBEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define GPCM_ID_START	35000
#define GPCM_N_ID		2000
#define GPCM_ID_END		GPCM_ID_START+GPCM_N_ID-1

class GPMenu;

class CGPContextMenu  
{
friend class CDlgContextMenu;
public:
	BOOL GetFileName(CString & iInitDir, CString & iFileName, DWORD iFlags);
	DWORD SetODCForMenu(CODContext *ipContext, HMENU ihPopup);
	UINT GetMenuPosition(const char *iName);
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];

	int DoMethod(const char *iStrMethod, char *oStr);
	UINT GetCount();
	static DWORD StringFromToTPMFlags(const char *iTPMFlags, DWORD & convTPMFlags);
	static CString ExtractWord(const char *iStr, int nLine, int nWord, const char *Delimiter = " ", DWORD flag = 0);
	static CString ConvertToOutput(const char *iStr, const char *iClip = NULL);
	CGPContextMenu & operator= (const CGPContextMenu &iCGPContextMenu);
	HMENU m_Menu;
	UINT LoadMenu(FILE *iFile, HMENU mnu);
	UINT SaveMenu(FILE *iFile, HMENU mnu, int iLevel);
	virtual void DeleteAllItems();
	virtual DWORD Load(const char *iName);
	virtual BOOL Save(const char *iName);
	virtual DWORD GetFreeCommand();
	virtual DWORD GetFreeSubMenuId();
	static PGPMENUINFO ClearItem(PGPMENUINFO iItem);
	DWORD AddItem();
	PGPMENUINFO FindItemByName(const char *iName);
	PGPMENUINFO FindItemByData(DWORD dwData);
	PGPMENUINFO FindItemByCommand(DWORD dwCommand);
	PGPMENUINFO FindItemBySubMenuId(DWORD dwSubMenuId);
	PGPMENUINFO FindItemByData(HMENU ihPopupMenu, DWORD dwData);
	int FindPositionByData(HMENU ihPopupMenu, DWORD dwData);

	DWORD GetMenuItemData(HMENU ihPopupMenu, int position);

	CGPContextMenu(GPMenu *pGPMenu);
	virtual ~CGPContextMenu();
	GPMenu *m_pGPMenu;
	virtual BOOL FillTree(HWND TreeHWND, BOOL bCopy);
	virtual UINT FillTree(HWND TreeHWND, HTREEITEM iTreeItem, HMENU mnu, BOOL bCopy);

private:
	virtual UINT AddFromOther(const CGPContextMenu *iArr, HMENU iHMENU, HMENU destHMENU);
	DWORD *m_ArrayIdMenuInfo;
	UINT m_nArr;
	UINT m_nMaxArr;
	UINT DeleteItem(PGPMENUINFO iItem);
	UINT DeleteItem(UINT iItem);
};

#endif // !defined(AFX_GPCONTEXTMENU_H__C380AAB9_1DBE_4046_ABED_43624C08CBEF__INCLUDED_)
