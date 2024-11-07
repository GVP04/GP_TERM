// COMServer.h: interface for the CCOMServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMSERVER_H__197276CA_9F99_4229_8E88_BBC6DC110A36__INCLUDED_)
#define AFX_COMSERVER_H__197276CA_9F99_4229_8E88_BBC6DC110A36__INCLUDED_

#include "COMImport.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCOMServer  
{
public:
	const sctDllStartParams * GetStartParamsByName(const char *ccName);
	int GetIdByName(const char *ccName);
	CCOMServer();
	virtual ~CCOMServer();
	int LoadDll(const char* strProgID, HWND hwndParent, const char *ccExtName, const char *ccSubroutineName);
	int LoadExe(const char* strProgID, HWND hwndParent, const char *ccExtName, const char *ccSubroutineName);
	BOOL Unload(int iCOMIndex);
	BOOL Unload(const char *ccExtName);
	BOOL UnloadAll();
	BOOL DoMethod(int iCOMIndex, const char* pFuncName, const char* pFuncParam, char** ppRetVal, BOOL bWaitDoMethod);
	BOOL SetData(int iCOMIndex, const char*pDataBuff);
	static BOOL _stdcall RaiseEvent(void* pCOMParams, const char* pEventName, const char* pEventData);
	CRITICAL_SECTION m_csEvents;
	CRITICAL_SECTION m_csData;
	HANDLE m_hEventDoMethod;
	GP_RarefiedArr<sctDllStartParams*> m_lstCOMsStartParams;
};

#endif // !defined(AFX_COMSERVER_H__197276CA_9F99_4229_8E88_BBC6DC110A36__INCLUDED_)
