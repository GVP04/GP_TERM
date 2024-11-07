// DllImport.h: interface for the DllImport class.
//
//////////////////////////////////////////////////////////////////////
#ifndef _DLLIMPORT_H_
#define _DLLIMPORT_H_

#if !defined(AFX_DLLIMPORT_H__A1CFFE4C_3C8D_4E0B_8E63_AC75E08BAA7D__INCLUDED_)
#define AFX_DLLIMPORT_H__A1CFFE4C_3C8D_4E0B_8E63_AC75E08BAA7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Afxtempl.h"

typedef BOOL (_stdcall *EXE_RaiseEvent)(void* pDllParams, const char* pEventName, const char* pEventData);
typedef BOOL (_stdcall *EXE_GetData)(void* pDllParams, char** pDataBuff);
typedef BOOL (_stdcall *EXE_FreeMemoryBuffer)(void* pDllParams, char** pDataBuff);

// Направления передачи данных из Dll и в Dll
enum enDllMsgDirectionType
{
	iDllMsgFromServer = 1,	// Направление передачи из DllServer в DllImport
	iDllMsgToServer = 2	// Направление передачи из DllImport в DllServer
};

// Типы сообщений
enum enDllMsgType
{
	iDllMsgDoMethod = 1,		// 1 - DoMethod
	iDllMsgData = 2,		// 2 - Data
	iDllMsgEvent = 4,		// 4 - Event
	iDllMsgUnload = 8,		// 8 - Unload
	iDllMsgUnloadNow = 16		// 16 - Unload Now
};

// Типы объектов COM
enum enCOMObjectType
{
	iCOMDll = 1,		// Dll
	iCOMExe = 2			// EXE
};

//  Структура для стартовой инициализации Dll
struct sctDllStartParams
{
	CString csDllFileName;			    // Имя файла с Dll
	int *piReturn;
	void* pDllServer;					// Ссылка на объект класса DllServer
	void* pDll;							// Ссылка на объект класса DllImport
	//void* pDllThread;					// Поток, в котором создан объект класса DllImport
	EXE_RaiseEvent pFuncRaiseEvent;		// Ссылка на функцию, обрабатывающую события от Dll
	EXE_GetData pFuncGetData;			// Ссылка на функцию, обрабатывающую загрузку данных в Dll
	EXE_FreeMemoryBuffer pFuncFreeMemoryBuffer;			// Ссылка на функцию, освобождающую буффер данных на сервере
	int iDllPos;						// Порядковый номер объекта класса DllImport в списке в классе DllServer
	int iStatus;						// Статус Dll(загружена/не загружена/неудачная загрузка)
	HWND hwndParent;					// Дескриптор родительского окна
	int iCOMType;						// Тип COM объекта
	CRITICAL_SECTION csDllMsg;
	CString csName;						// Unique name 
	CString csSubroutineName;			// Name of server subroutine (events)
};

//  Структура для передачи данных из Dll и в Dll
struct sctDllExchangeBuff
{
	void* pDllParams;		// Параметры для правильной передачи данных
	int iDirection;			// Направление передачи(1 - из DllServer в DllImport;2 - из DllImport в DllServer)
	int iMsgType;			// Тип сообщения(1 - DoMethod;2 - Data;4 - Event)
	char* strMsgName;		// Имя сообщения
	char* strMsgBuff;		// Буффер с сообщением
	char** pstrMsgRet;		// Буффер возврата сообщения
	HANDLE m_hEventMsg;		// Дескриптор сообщения, для сигнала после передачи
	static void FreeExchangeBuff(sctDllExchangeBuff** ppsctDllExchangeBuff, BOOL bFreeMsgName = TRUE, BOOL bFreeMsgBuff = TRUE, BOOL bFreeMsgRet = FALSE)
	{
		sctDllExchangeBuff* psctDllExchangeBuff = (*ppsctDllExchangeBuff);

		if (bFreeMsgName == TRUE)
		{
			delete psctDllExchangeBuff->strMsgName;
			psctDllExchangeBuff->strMsgName = NULL;
		}
		if (bFreeMsgBuff == TRUE)
		{
			delete psctDllExchangeBuff->strMsgBuff;
			psctDllExchangeBuff->strMsgBuff = NULL;
		}
		if ((bFreeMsgRet == TRUE) && (psctDllExchangeBuff->pstrMsgRet != NULL) && (*(psctDllExchangeBuff->pstrMsgRet) != NULL))
		{
			delete (*(psctDllExchangeBuff->pstrMsgRet)); 
			*(psctDllExchangeBuff->pstrMsgRet) = NULL;
		}
		if (psctDllExchangeBuff->m_hEventMsg != NULL)
			SetEvent(psctDllExchangeBuff->m_hEventMsg); 
		delete psctDllExchangeBuff;
		(*ppsctDllExchangeBuff) = NULL;
	}
};

typedef BOOL (_stdcall *DLL_Init)(void*, EXE_RaiseEvent, EXE_GetData, EXE_FreeMemoryBuffer);
typedef BOOL (_stdcall *DLL_Terminate)(void);
typedef BOOL (_stdcall *DLL_DoMethod)(const char* pFuncName, const char* pFuncParam, char** ppRetVal);
typedef BOOL (_stdcall *DLL_FreeMemoryBuffer)(char** ppRetVal);

class DllImport  
{
public:
	DllImport();
	DllImport(sctDllStartParams* pDllStartParams);
	virtual ~DllImport();
	BOOL Load();
	BOOL Unload();
	BOOL DoMethod(const char* pFuncName, const char* pFuncParam, char** ppRetVal);
	BOOL SetData(const char* pDataBuff);
	BOOL GetData(char** pDataBuff);
	BOOL AddMsg(sctDllExchangeBuff* psctDllMsg);
	sctDllExchangeBuff* GetMsg(BOOL bRemoveMsg);
	sctDllExchangeBuff* GetMsg(enDllMsgDirectionType iDllMsgDirection, enDllMsgType iDllMsgType, BOOL bRemoveMsg);
	BOOL RemoveAllMsg();
private:
	CList<sctDllExchangeBuff*,sctDllExchangeBuff*> m_lstDllsMsgs;
	sctDllStartParams* m_pStartParams;
	HINSTANCE m_hinstDllLib;
	DLL_Init m_pFuncInit;
	DLL_Terminate m_pFuncTerminate;
	DLL_DoMethod m_pFuncDoMethod;
	DLL_FreeMemoryBuffer m_pFuncFreeMemoryBuffer;
	char *m_pDataBuff;
};

#endif // !defined(AFX_DLLIMPORT_H__A1CFFE4C_3C8D_4E0B_8E63_AC75E08BAA7D__INCLUDED_)
 
#endif // _DLLIMPORT_H_
