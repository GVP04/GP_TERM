// GP_HotKey.h: interface for the GP_HotKey class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GP_HOTKEY_H__5B508601_B9B8_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GP_HOTKEY_H__5B508601_B9B8_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// #define GP_N_TYPE_HOTKEY 136

#define GP_N_TYPE_HOTKEY 173
#define MOD_EASYTCL       0x0100

class GPUnit;


class GP_HotKey
{
public:
	static const char * GetModifierName(DWORD iModifier);
	static const char * GetKeyName(DWORD iKey);
	static DWORD StringFromToHotKey(const char *ioStr,DWORD &dwHotKey);
	BOOL GetHotKey(UINT iId, CString &oName, CString &oModifier, CString &oSeq);
	static const UINT aVKUINT[GP_N_TYPE_HOTKEY];
	static const char *aVKName[GP_N_TYPE_HOTKEY];
	static const UINT aVKMODUINT[5];
	static const char *aVKMODName[5];
	static UINT nTypeHotkey;
	static UINT nTypeModifiers;

	BOOL SendHotkeyMessage(UINT message, UINT wParam, UINT lParam);
	void DelAllHotkey();
	BOOL DelHotkey(UINT iId, const char *iHotkeyName);
	BOOL AddHotkey(char *nm_VK, UINT iId, const char *seq);
	GP_HotKey(GPUnit *iptrGPUnit);
	virtual ~GP_HotKey();

private:
	UINT VK[GP_N_TYPE_HOTKEY];
	UINT ID[GP_N_TYPE_HOTKEY];
	char *Seq[GP_N_TYPE_HOTKEY];
	HWND OwnerWnd;
	GPUnit *ptrGPUnit;
};

#endif // !defined(AFX_GP_HOTKEY_H__5B508601_B9B8_11D2_B27D_00600840D054__INCLUDED_)
