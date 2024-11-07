// GPMenu.h: interface for the GPMenu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPMENU_H__DFBFFC41_B9B8_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GPMENU_H__DFBFFC41_B9B8_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MenuCustom.h"


#define MENU_ID_START			38000
#define MENU_ID_COUNT			1500
#define MENU_ID_END				39500
#define HOTKEY_ID_START			39501
#define HOTKEY_ID_COUNT			490
#define HOTKEY_ID_END			39991
//#define TOOLBAR_ID_START		40000
//#define TOOLBAR_ID_COUNT		100
//#define TOOLBAR_ID_END		40099


/*
#define MENU_ID_START			38000
#define MENU_ID_COUNT			1500
#define MENU_ID_END				MENU_ID_START+MENU_ID_COUNT
#define HOTKEY_ID_START			MENU_ID_END+1
#define HOTKEY_ID_COUNT			500
#define HOTKEY_ID_END			HOTKEY_ID_START+HOTKEY_ID_COUNT
*/


#define MENU_POPUP_START			10
#define MENU_POPUP_COUNT			1000

typedef struct _GPMENUINFO
{
	DWORD dwCmd;
	DWORD dwFlags;
	DWORD dwPopupId;
	DWORD dwData;
	DWORD dwPtr;
	HMENU hMenu;
	HMENU hSubMenu;
	CString csText;
	CString csContext;
	CString csOut;
	CString csDescription;
	CString csName;
	CString csImageList;
	DWORD dwImage;
} GPMENUINFO, *PGPMENUINFO;


class GPMenu  
{
public:
	static DWORD m_dwODCMENUID;
	GP_RarefiedArr<GPMENUINFO> MENUINFOArray;
	DWORD RegisterMenuItem(DWORD dwPopupId, DWORD dwItemId, const char *ccContext, const char *Text, DWORD dwFlags, HMENU ihMenu);
	DWORD RegisterMenuItem(GPMENUINFO &iGPMenuInfo);
	DWORD UnRegisterMenuItem(DWORD dwRegItemId);
	DWORD SetODCForTerminalMenu(CODContext *ipContext, HMENU ihPopup, DWORD dwFlags);
	static DWORD TranslateMenuFlags(DWORD dwCurFlag, const char *ccFlags);
	void InitTermMenuList();
	BOOL IsTerminalMenu(HMENU  ihMenu);
	UINT FindMenuItem(UINT iIdItem, UINT *oIdPopup,UINT *oPos,CString *oName, UINT nMaxItem);
	void ReleaseHBMP();
	UINT GPTranslateMenuItemInfo(char *iFlags, MENUITEMINFO *mi);
	UINT GPTranslateMenuInfo(char *iFlags, MENUINFO *mi);
	BOOL EnablePopup(UINT IdPopup, UINT nFlags);
	BOOL GPTrackPopupMenu(UINT IdPopup, UINT nFlags, int CX, int CY, CRect *re);
	BOOL GPCreateTrackMenu(UINT IdPopup, char *posfg);
	void GPDrawMenuBar();
	BOOL GPRemoveByCom(UINT IdItem);
	BOOL GPEnableByPos(UINT IdPopup, UINT PosItem, char *posflg);
	BOOL GPEnableByCom(UINT IdItem, char *posflg);
	BOOL GPCheckByPos(UINT IdPopup, UINT PosItem, char *posflg);
	BOOL GPCheckByCom(UINT IdItem, char *posflg);
	BOOL GPCheckRadio(UINT IdPopup, UINT PosItem, UINT PosItemStart,  UINT PosItemEnd);
	BOOL GPAppendSeparator(UINT IdPopup);
	BOOL GPInsertSeparator(UINT IdPopup, UINT PosItem);
	BOOL GPRemoveByPos(UINT IdPopup, UINT PosItem);
	BOOL GPModifyByPos(UINT IdPopup, UINT PosItem, char *posflg, char *postxt);
	BOOL GPModifyByCom(UINT IdItem, char *posflg, char *postxt);
	BOOL GPInsertMenu(UINT IdPopup, UINT PosItem, UINT IdItem, char *posflg, char *postxt);
	BOOL GPAppendMenu(UINT IdPopup, UINT IdItem, char *posflg, char *postxt);
	BOOL GPCreatePopupMenu(UINT IdMenu, UINT IdPopup, UINT PosItem, char *iText, char *iFlag);
	UINT GPEditMenuFlags(UINT iId, char *Flags);
	UINT GPSetMenuFlags(UINT iId, char *Flags);
	BOOL DoUpdateUserMenu(UINT nID,CCmdUI *pCmdUI);
	BOOL OnCommandUserMenu(UINT idDlg, UINT nID);
	void Fill_mArrMenu(BOOL DelAll);
	UINT *m_ArrMenuState;
	CMenuCustom *m_ArrPopupMenu[MENU_POPUP_COUNT];
	GPMenu(HWND owner,UINT iType);
	virtual ~GPMenu();

private:
	UINT GPTypeMenu;
	HWND MenuOwner;

};

#endif // !defined(AFX_GPMENU_H__DFBFFC41_B9B8_11D2_B27D_00600840D054__INCLUDED_)
