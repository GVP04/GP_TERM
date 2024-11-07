// GPMessage.h: interface for the GPMessage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPMESSAGE_H__ED10A581_B9B8_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GPMESSAGE_H__ED10A581_B9B8_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAXMMESAGER		32
#include "COMServer.h"

class GPUnit;

typedef struct _MMESSAGERSTRUCT
{
	void *DestUnit;
	CString OnProperty;
	CString OffProperty;
	CString OffMethods;
	CString OnMethods;
	CString OnMsgStr;
	CString OffMsgStr;
	CString OnMsgStrInit;
	CString OffMsgStrInit;
	UINT OnMessage;
	UINT OffMessage;
	UINT OnTimerDeleay;
	UINT OffTimerDeleay;
} MMESSAGERSTRUCT, *PMMESSAGERSTRUCT;


class GPMessage  
{
	friend class CDlgDialogEditor;
public:
	void SetReferGPU(GPUnit **newGPU);
	DWORD m_MessageDelay1;
	DWORD m_LastTick1;
	DWORD m_HSCROLLMASK;
	DWORD m_VSCROLLMASK;
	const char * GetActiveMessages();
	UINT ProcMessagerTimer(UINT TimId, HWND uHWND);
	void AddMMesager(void *DestUnit, const char *OnProperty, const char *OffProperty, const char *OnMethods, const char *OffMethods, const char *OnMsgStr, const char *OffMsgStr, const char *OnMessage, const char *OffMessage, UINT OnTimerDeleay, UINT OffTimerDeleay);
	void DelMMesager(void *DestUnit, const char *OnMessage);
	void DelAllMMesager();
	CEdit * m_OutputEdit;
	void DelAllMessages();
	UINT GPSendObjMessage(HWND uHWND, UINT iIdObj, UINT message, WPARAM wParam, LPARAM lParam);

	static UINT GPSendDllEvent(sctDllStartParams *pDllParams, const char *EvName, const char *EvBody);
	static UINT GPSendComEvent(sctDllStartParams *pDllParams, const char *EvName, const char *EvBody);

	UINT GPSendObjEvent(HWND uHWND, UINT iIdObj, const char *EvName, const char *EvBody);
	UINT GPSendDlgEvent(HWND uHWND, UINT iIdObj, const char *EvName, const char *EvBody);
	UINT GPSendMenuMessage(UINT iType, UINT id, UINT iIdMessage);
	void DelMessage(const char *Mes);
	char * FindInActive(const char *Mes);
	char * FindInMessages(const char *Mes);
	char * FindInEvents(const char *Mes);
	void AddMessage(const char *Mes);
	GPMessage(const char *iListAllEvents, GPUnit **iGPU, UINT iUnitId);
	virtual ~GPMessage();

private:
	GPUnit **GPU;
	void UpdateMessagerState(const char *iMessage, UINT iFlg);
	void ProcMessagerState(HWND uHWND, UINT iMessage);
	UINT MessagerState;
	void DoMessagerSub(void *gpunit, CString &iSubs);
	PMMESSAGERSTRUCT m_MMessager;
	UINT FLGiIdObj;
	UINT LastIdObj;
	UINT m_UnitId;
	UINT FLGmessage;
	WPARAM FLGwParam;
	LPARAM FLGlParam;
	GP_RarefiedArr<CString> *SeqArray;
	GP_RarefiedArr<CString> *AnswArray;
	GP_RarefiedArr<CString> *ScriptArray;
	UINT RetNCHITTEST;
	char *CurME_List;
	char *E_List;
};

#endif // !defined(AFX_GPMESSAGE_H__ED10A581_B9B8_11D2_B27D_00600840D054__INCLUDED_)
