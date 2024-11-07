// GP_HotKey.cpp: implementation of the GP_HotKey class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GP_HotKey.h"
#include "GPUnit.h"
#include "GP_termDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

UINT GP_HotKey::nTypeModifiers=5;
UINT GP_HotKey::nTypeHotkey=GP_N_TYPE_HOTKEY;

const char * GP_HotKey:: aVKName[GP_N_TYPE_HOTKEY]={

	"VK_LBUTTON|","VK_RBUTTON|","VK_CANCEL|","VK_MBUTTON|","VK_XBUTTON1|","VK_XBUTTON2|","VK_BACK|","VK_TAB|",
	"VK_CLEAR|","VK_RETURN|","VK_SHIFT|","VK_CONTROL|","VK_MENU|","VK_PAUSE|","VK_CAPITAL|","VK_KANA|",
	"VK_HANGUL|","VK_JUNJA|","VK_FINAL|","VK_HANJA|","VK_KANJI|","VK_ESCAPE|","VK_CONVERT|","VK_NONCONVERT|",
	"VK_ACCEPT|","VK_MODECHANGE|","VK_SPACE|","VK_PRIOR|","VK_NEXT|","VK_END|","VK_HOME|","VK_LEFT|",
	"VK_UP|","VK_RIGHT|","VK_DOWN|","VK_SELECT|","VK_PRINT|","VK_EXECUTE|","VK_SNAPSHOT|","VK_INSERT|",
	"VK_DELETE|","VK_HELP|","VK_0|","VK_1|","VK_2|","VK_3|","VK_4|","VK_5|",
	"VK_6|","VK_7|","VK_8|","VK_9|","VK_:|","VK_A|","VK_B|","VK_C|",
	"VK_D|","VK_E|","VK_F|","VK_G|","VK_H|","VK_I|","VK_J|","VK_K|",
	"VK_L|","VK_M|","VK_N|","VK_O|","VK_P|","VK_Q|","VK_R|","VK_S|",
	"VK_T|","VK_U|","VK_V|","VK_W|","VK_X|","VK_Y|","VK_Z|","VK_LWIN|",
	"VK_RWIN|","VK_APPS|","VK_SLEEP|","VK_NUMPAD0|","VK_NUMPAD1|","VK_NUMPAD2|","VK_NUMPAD3|","VK_NUMPAD4|",
	"VK_NUMPAD5|","VK_NUMPAD6|","VK_NUMPAD7|","VK_NUMPAD8|","VK_NUMPAD9|","VK_MULTIPLY|","VK_ADD|","VK_SEPARATOR|",
	"VK_SUBTRACT|","VK_DECIMAL|","VK_DIVIDE|","VK_F1|","VK_F2|","VK_F3|","VK_F4|","VK_F5|",
	"VK_F6|","VK_F7|","VK_F8|","VK_F9|","VK_F10|","VK_F11|","VK_F12|","VK_F13|",
	"VK_F14|","VK_F15|","VK_F16|","VK_F17|","VK_F18|","VK_F19|","VK_F20|","VK_F21|",
	"VK_F22|","VK_F23|","VK_F24|","VK_NUMLOCK|","VK_SCROLL|","VK_LSHIFT|","VK_RSHIFT|","VK_LCONTROL|",
	"VK_RCONTROL|","VK_LMENU|","VK_RMENU|","VK_BROWSER_BACK|","VK_BROWSER_FORWARD|","VK_BROWSER_REFRESH|","VK_BROWSER_STOP|",
	"VK_BROWSER_SEARCH|","VK_BROWSER_FAVORITES|","VK_BROWSER_HOME|","VK_VOLUME_MUTE|","VK_VOLUME_DOWN|","VK_VOLUME_UP|","VK_MEDIA_NEXT_TRACK|","VK_MEDIA_PREV_TRACK|",
	"VK_MEDIA_STOP|","VK_MEDIA_PLAY_PAUSE|","VK_LAUNCH_MAIL|","VK_LAUNCH_MEDIA_SELECT|","VK_LAUNCH_APP1|","VK_LAUNCH_APP2|","VK_OEM_1|","VK_OEM_PLUS|",
	"VK_OEM_COMMA|","VK_OEM_MINUS|","VK_OEM_PERIOD|","VK_OEM_2|","VK_OEM_3|","VK_OEM_4|","VK_OEM_5|","VK_OEM_6|",
	"VK_OEM_7|","VK_OEM_8|","VK_OEM_102|","VK_PROCESSKEY|","VK_PACKET|","VK_ATTN|","VK_CRSEL|","VK_EXSEL|",
	"VK_EREOF|","VK_PLAY|","VK_ZOOM|","VK_NONAME|","VK_PA1|","VK_OEM_CLEAR|",
};


const UINT GP_HotKey:: aVKUINT[GP_N_TYPE_HOTKEY]={
	VK_LBUTTON,VK_RBUTTON,VK_CANCEL,VK_MBUTTON,VK_XBUTTON1,VK_XBUTTON2,VK_BACK,VK_TAB,
	VK_CLEAR,VK_RETURN,VK_SHIFT,VK_CONTROL,VK_MENU,VK_PAUSE,VK_CAPITAL,VK_KANA,
	VK_HANGUL,VK_JUNJA,VK_FINAL,VK_HANJA,VK_KANJI,VK_ESCAPE,VK_CONVERT,VK_NONCONVERT,
	VK_ACCEPT,VK_MODECHANGE,VK_SPACE,VK_PRIOR,VK_NEXT,VK_END,VK_HOME,VK_LEFT,
	VK_UP,VK_RIGHT,VK_DOWN,VK_SELECT,VK_PRINT,VK_EXECUTE,VK_SNAPSHOT,VK_INSERT,
	VK_DELETE,VK_HELP,0x30,0x31,0x32,0x33,0x34,0x35,
	0x36,0x37,0x38,0x39,0x40,0x41,0x42,0x43,
	0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,
	0x4C,0x4D,0x4E,0x4F,0x50,0x51,0x52,0x53,
	0x54,0x55,0x56,0x57,0x58,0x59,0x5A,VK_LWIN,
	VK_RWIN,VK_APPS,VK_SLEEP,VK_NUMPAD0,VK_NUMPAD1,VK_NUMPAD2,VK_NUMPAD3,VK_NUMPAD4,
	VK_NUMPAD5,VK_NUMPAD6,VK_NUMPAD7,VK_NUMPAD8,VK_NUMPAD9,VK_MULTIPLY,VK_ADD,VK_SEPARATOR,
	VK_SUBTRACT,VK_DECIMAL,VK_DIVIDE,VK_F1,VK_F2,VK_F3,VK_F4,VK_F5,
	VK_F6,VK_F7,VK_F8,VK_F9,VK_F10,VK_F11,VK_F12,VK_F13
	,VK_F14,VK_F15,VK_F16,VK_F17,VK_F18,VK_F19,VK_F20,VK_F21,
	VK_F22,VK_F23,VK_F24,VK_NUMLOCK,VK_SCROLL,VK_LSHIFT,VK_RSHIFT,VK_LCONTROL,
	VK_RCONTROL,VK_LMENU,VK_RMENU,VK_BROWSER_BACK,VK_BROWSER_FORWARD,VK_BROWSER_REFRESH,VK_BROWSER_STOP,
	VK_BROWSER_SEARCH,VK_BROWSER_FAVORITES,VK_BROWSER_HOME,VK_VOLUME_MUTE,VK_VOLUME_DOWN,VK_VOLUME_UP,VK_MEDIA_NEXT_TRACK,VK_MEDIA_PREV_TRACK,
	VK_MEDIA_STOP,VK_MEDIA_PLAY_PAUSE,VK_LAUNCH_MAIL,VK_LAUNCH_MEDIA_SELECT,VK_LAUNCH_APP1,VK_LAUNCH_APP2,VK_OEM_1,VK_OEM_PLUS,
	VK_OEM_COMMA,VK_OEM_MINUS,VK_OEM_PERIOD,VK_OEM_2,VK_OEM_3,VK_OEM_4,VK_OEM_5,VK_OEM_6,
	VK_OEM_7,VK_OEM_8,VK_OEM_102,VK_PROCESSKEY,VK_PACKET,	VK_ATTN,VK_CRSEL,VK_EXSEL,
	VK_EREOF,VK_PLAY,VK_ZOOM,VK_NONAME,VK_PA1,VK_OEM_CLEAR,
};

const UINT GP_HotKey::aVKMODUINT[5]={MOD_ALT,MOD_CONTROL,MOD_SHIFT,MOD_WIN,MOD_EASYTCL};

const char * GP_HotKey::aVKMODName[5]={"MOD_ALT|","MOD_CONTROL|","MOD_SHIFT|","MOD_WIN|","MOD_EASYTCL|"};


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//#define MOD_ALT         0x0001
//#define MOD_CONTROL     0x0002
//#define MOD_SHIFT       0x0004
//#define MOD_WIN         0x0008
//#define MOD_EASYTCL     0x0100

GP_HotKey::GP_HotKey(GPUnit *iptrGPUnit)
{
	ptrGPUnit=iptrGPUnit;
	OwnerWnd=iptrGPUnit->UnitHWND;

	int i;
	for(i=0;i<GP_N_TYPE_HOTKEY;i++)
	{
		VK[i]=ID[i]=0xFFFFFFFF;
		Seq[i]=NULL;
	}
}

GP_HotKey::~GP_HotKey()
{
	DelAllHotkey();
}

BOOL GP_HotKey::AddHotkey(char *nm_VK, UINT iId, const char *iSeq)
{
	int i;
	BOOL ret=FALSE;
	char str[250];strncpy(str,nm_VK,225);str[225]=0;
	strcat(str,"|");

	for(i=0;i<GP_N_TYPE_HOTKEY && strstr(str,aVKName[i])==NULL;i++);
	if (i<GP_N_TYPE_HOTKEY)
	{
		ret=TRUE;
		UINT Modif=0;
		UINT j;
		for(j=0;j<nTypeModifiers;j++)
			if (strstr(str,aVKMODName[j])!=NULL) Modif|=aVKMODUINT[j];

		Modif+=0x10000*aVKUINT[i];

		for(i=0;i<GP_N_TYPE_HOTKEY && Modif!=VK[i];i++);

		if (i<GP_N_TYPE_HOTKEY && ID[i]!=0xFFFFFFFF)
		{
//			UnregisterHotKey(OwnerWnd,ID[i]);
			VK[i]=ID[i]=0xFFFFFFFF;
			if (Seq[i]) delete[] Seq[i];
			Seq[i]=NULL;
		}

		for(i=0;i<GP_N_TYPE_HOTKEY && VK[i]!=0xFFFFFFFF;i++);

		if (i!=GP_N_TYPE_HOTKEY)
		{
			VK[i]=Modif;
			ID[i]=HOTKEY_ID_START+(iId%HOTKEY_ID_COUNT);
//			if ((ret=RegisterHotKey(OwnerWnd,ID[i],Modif%0x10000,Modif/0x10000))==FALSE) VK[i]=ID[i]=0xFFFFFFFF;
			if (iSeq && *iSeq)
			{
				Seq[i]=new char[(int)strlen(iSeq)+10];
				strcpy(Seq[i],iSeq);
			}
		}
	}

	if (ret==FALSE)
	{
#ifdef RUS
	sprintf(str,"ќшибка задани€ гор€чей клавиши %s ID=%d", nm_VK,iId);
	MessageBox(AfxGetMainWnd()->m_hWnd,str,GPC.ErrBoxCaption,MB_OK |MB_ICONEXCLAMATION);
#else
	sprintf(str,"HotKey create Error %s ID=%d", nm_VK,iId);
	MessageBox(AfxGetMainWnd()->m_hWnd,str,GPC.ErrBoxCaption,MB_OK |MB_ICONEXCLAMATION);
#endif
	}
	return ret;
}

BOOL GP_HotKey::DelHotkey(UINT iId, const char *iHotkeyName)
{
	int i;
	BOOL ret=FALSE;

	iId%=HOTKEY_ID_COUNT;
	iId+=HOTKEY_ID_START;

	if (iHotkeyName && *iHotkeyName)
	{
		char str[250];strncpy(str,iHotkeyName,225);str[225]=0;
		strcat(str,"|");
		_strupr(str);

		for(i=0;i<GP_N_TYPE_HOTKEY && strstr(str,aVKName[i])==NULL;i++);
		if (i<GP_N_TYPE_HOTKEY)
		{
			iId=0;
			UINT j;
			for(j=0;j<nTypeModifiers;j++)
				if (strstr(str,aVKMODName[j])!=NULL) iId|=aVKMODUINT[j];

			iId+=0x10000*aVKUINT[i];
		}
		for(i=0;i<GP_N_TYPE_HOTKEY && VK[i]!=iId;i++);
	}
	else
		for(i=0;i<GP_N_TYPE_HOTKEY && ID[i]!=iId;i++);

	if (i<GP_N_TYPE_HOTKEY)
	{
		ret=TRUE;
		UnregisterHotKey(OwnerWnd,ID[i]);
		VK[i]=ID[i]=0xFFFFFFFF;
		if (Seq[i]) delete[] Seq[i];
		Seq[i]=NULL;
	}

	return ret;
}

void GP_HotKey::DelAllHotkey()
{
	int i;

	for(i=0;i<GP_N_TYPE_HOTKEY;i++)
	{
		if (ID[i]!=0xFFFFFFFF) UnregisterHotKey(OwnerWnd,ID[i]);
		VK[i]=ID[i]=0xFFFFFFFF;
		if (Seq[i]) delete[] Seq[i];
		Seq[i]=NULL;
	}
}


BOOL GP_HotKey::SendHotkeyMessage(UINT message, UINT wParam, UINT lParam)
{
//	idHotKey = (int) wParam;              // identifier of hot key
//	fuModifiers = (UINT) LOWORD(lParam);  // key-modifier flags
//	uVirtKey = (UINT) HIWORD(lParam);
//	UINT idvk= ((UINT) LOWORD(lParam))+ ((UINT) HIWORD(lParam))*0x10000;

	BOOL ret=FALSE;
	int i;

//#define MOD_ALT         0x0001
//#define MOD_CONTROL     0x0002
//#define MOD_SHIFT       0x0004
//#define MOD_WIN         0x0008

	if (message==WM_KEYDOWN || message==WM_SYSKEYDOWN)
	{
		UINT ModWinIsPressed=(GetAsyncKeyState(VK_RWIN)&0xFF00)!=0 || (GetAsyncKeyState(VK_LWIN)&0xFF00)!=0?1:0;
		UINT ShiftIsPressed=(GetAsyncKeyState(MOD_SHIFT)&0xFF00)!=0 || (GetAsyncKeyState(VK_RSHIFT)&0xFF00)!=0 || (GetAsyncKeyState(VK_LSHIFT)&0xFF00)!=0?1:0;
		UINT CtrlIsPressed=(GetAsyncKeyState(VK_CONTROL)&0xFF00)!=0 || (GetAsyncKeyState(VK_RCONTROL)&0xFF00)!=0 || (GetAsyncKeyState(VK_LCONTROL)&0xFF00)!=0?1:0;
		UINT AltIsPressed=(GetAsyncKeyState(MOD_ALT)&0xFF00)!=0 || (GetAsyncKeyState(VK_RMENU)&0xFF00)!=0 || (GetAsyncKeyState(VK_LMENU)&0xFF00)!=0 ?1:0;

		UINT CurVk=wParam*0x10000+ShiftIsPressed*MOD_SHIFT+CtrlIsPressed*MOD_CONTROL+ModWinIsPressed*MOD_WIN+AltIsPressed*MOD_ALT;

		for(i=0;i<GP_N_TYPE_HOTKEY && !ret;i++)
			if (ID[i]!=0xFFFFFFFF && VK[i]!=0xFFFFFFFF && VK[i]==CurVk)
			{
				if (GPUnit::m_ptrUnitValChange) (GPUnit::m_ptrUnitValChange)->SendOnValChangeEvent(1);

				if (!Seq[i] || !*Seq[i] || *Seq[i]!='=')
				{
					CString csStr;
					csStr.Format("  %c%d\x7F%d\x7F%3.3d\x7F",(ptrGPUnit->UnitId<0x10000000)?52:53,((ptrGPUnit->UnitId/0x10000)&0xFFF)+1,(ptrGPUnit->UnitId&0xFFFF),ID[i]-HOTKEY_ID_START);
					UINT j;
					for(j=0;j<GP_N_TYPE_HOTKEY;j++)
						if ((VK[i]/0x10000)==aVKUINT[j]) { csStr+=aVKName[j]; break; }

					for(j=0;j<nTypeModifiers;j++)
						if ((VK[i]&aVKMODUINT[j])==aVKMODUINT[j]) csStr+=aVKMODName[j];

					HWND tmpHWND=::GetFocus();
					if (tmpHWND)
					{
						GPUNITINFO ui;
						if (GPC.FindObject(tmpHWND,ui))
						{
							CString csTmp;
							csTmp.Format("\x7F%d\x7F%d\x7F%s",ui.IdDlg+1,ui.IdObj,(LPCSTR)ui.ObjName);
							csStr+=csTmp;
						}
					}
					if (Seq[i])
						GPC.m_Document->DoAnyMethodScript(Seq[i],ptrGPUnit->UnitId,csStr);


					AnsiToDos(csStr,csStr,1);
					csStr.SetAt(0,250);
					csStr.SetAt(1,250);
					m_Comm.GPSendBlock(csStr,csStr.GetLength());
					m_Comm.GPSendBlock("\r",1);
				}
				else
					if (Seq[i] && *Seq[i]=='=') 
					{
						if (*(Seq[i]+1) && *(Seq[i]+1)!=2)
							m_Comm.SendSequens(ExtractField(Seq[i]+1,1,"\x2"));

						const char *ccScript;
						if ((ccScript=strchr(Seq[i],2)))
						{
							CString csStr;
							GPC.m_Document->DoAnyMethodScript(ccScript,ptrGPUnit->UnitId,csStr);
							if (csStr!="")
							{
								AnsiToDos(csStr,csStr,1);
								csStr.SetAt(0,250);
								csStr.SetAt(1,250);
								m_Comm.GPSendBlock(csStr,csStr.GetLength());
								m_Comm.GPSendBlock("\r",1);
							}
						}
					}
				ret=TRUE;
			}
	}

	return ret;
}

BOOL GP_HotKey::GetHotKey(UINT iId, CString &oName, CString &oModifier, CString &oSeq)
{
	BOOL ret=FALSE;
	UINT i;
	UINT findId=HOTKEY_ID_START+(iId%HOTKEY_ID_COUNT);
	for(i=0;i<GP_N_TYPE_HOTKEY && ID[i]!=findId;i++)
		;
	oName="";
	oModifier="";
	oSeq="";

	if (i<GP_N_TYPE_HOTKEY)
	{
		ret=TRUE;
		UINT j;
		for(j=0;j<nTypeModifiers;j++)
			if ((VK[i]&aVKMODUINT[j])==aVKMODUINT[j])
			{oModifier+=aVKMODName[j];oModifier+=" ";}

			UINT k;
		for(k=0;k<GP_N_TYPE_HOTKEY && (VK[i]/0x10000)!=aVKUINT[k];k++);

		if (k<GP_N_TYPE_HOTKEY)	oName=aVKName[k];
		oSeq=Seq[i];
	}

	return ret;
}


DWORD GP_HotKey::StringFromToHotKey(const char *ioStr, DWORD &dwHotKey)
{
	if (ioStr)
	{
		UINT i;
		if (*ioStr)
		{
			char *tmps=new char [(int)strlen(ioStr)+100];
			strcpy(tmps,ioStr);
			strcat(tmps,"|");
			_strupr(tmps);
			RemoveCharFromString(tmps,' ');

			dwHotKey=atoi(tmps);
			for(i=0;i<GP_HotKey::nTypeModifiers;i++)
				if (strstr(tmps,GP_HotKey::aVKMODName[i]))
					dwHotKey|=GP_HotKey::aVKMODUINT[i];

			for(i=0;i<GP_HotKey::nTypeHotkey;i++)
				if (strstr(tmps,GP_HotKey::aVKName[i]))
				{
					dwHotKey|=(GP_HotKey::aVKUINT[i]*0x10000);
					break;
				}

			delete[] tmps;
		}
		else
		{
			UINT convSD=dwHotKey;
			for(i=0;i<GP_HotKey::nTypeModifiers;i++)
				if ((convSD&GP_HotKey::aVKMODUINT[i])==GP_HotKey::aVKMODUINT[i])
				{
					//if (*ioStr) strcat((char *)ioStr,"|");
					strcat((char *)ioStr,GP_HotKey::aVKMODName[i]);
					convSD^=GP_HotKey::aVKMODUINT[i];
				}
			for(i=0;i<GP_HotKey::nTypeHotkey;i++)
				if (convSD==GP_HotKey::aVKUINT[i]*0x10000)
				{
					//if (*ioStr) strcat((char *)ioStr,"|");
					strcat((char *)ioStr,GP_HotKey::aVKName[i]);
					convSD^=(GP_HotKey::aVKUINT[i]*0x10000);
					break;
				}

			if (convSD) sprintf((char *)ioStr+(int)strlen(ioStr),"%s%d",*ioStr?"|":"",convSD);
		}
	}

	return dwHotKey;
}

const char * GP_HotKey::GetKeyName(DWORD iKey)
{
	const char *ret="";
	iKey/=0x10000;
	UINT i;
	for(i=0;i<GP_HotKey::nTypeHotkey && iKey!=GP_HotKey::aVKUINT[i];i++);

	if (i<GP_HotKey::nTypeHotkey) ret=GP_HotKey::aVKName[i];

	return ret;
}

const char * GP_HotKey::GetModifierName(DWORD iModifier)
{
	const char *ret="";
	iModifier&=0xFFFF;
	UINT i;
	for(i=0;i<GP_HotKey::nTypeModifiers && iModifier!=GP_HotKey::aVKMODUINT[i];i++);

	if (i<GP_HotKey::nTypeModifiers) ret=GP_HotKey::aVKMODName[i];

	return ret;
}
