// DllServer.h: interface for the DllServer class.
//
//////////////////////////////////////////////////////////////////////
#ifndef _DLLSERVER_H_
#define _DLLSERVER_H_

#if !defined(AFX_DLLSERVER_H__BE645F28_12FE_4FD1_AE9C_C0630765422B__INCLUDED_)
#define AFX_DLLSERVER_H__BE645F28_12FE_4FD1_AE9C_C0630765422B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "Afxtempl.h"
#include "DllImport.h"

class DllServer  
{
public:
	const sctDllStartParams * GetStartParamsByName(const char *ccName);
	int GetIdByName(const char *ccName);
	DllServer();
	virtual ~DllServer();
	int Load(const char* strDllFileName, const char *ccExtName, const char *ccSubroutineName);
	BOOL Unload(int iDllIndex);
	BOOL Unload(const char *ccExtName);
	BOOL UnloadAll();
	BOOL DoMethod(int iDllIndex, const char* pFuncName, const char* pFuncParam, char** ppRetVal, BOOL bWaitDoMethod);
	BOOL SetData(int iDllIndex, const char*pDataBuff);
	static BOOL _stdcall RaiseEvent(void* pDllParams, const char* pEventName, const char* pEventData);
	static BOOL _stdcall GetData(void* pDllParams, char** pDataBuff)
	{
		BOOL bRes = FALSE;
		sctDllStartParams* pDllTmp = (sctDllStartParams*)pDllParams;
		DllImport* pDllImportTmp = NULL;
		DllServer* pDllServerTmp = NULL;

		if (pDllTmp != NULL && pDllTmp->pDllServer != NULL && pDllTmp->pDll != NULL)
		{
			pDllServerTmp = (DllServer*)pDllTmp->pDllServer;
			pDllImportTmp = (DllImport*)pDllTmp->pDll;
			bRes = pDllImportTmp->GetData(pDataBuff);
		}
		return bRes;
	}
	static BOOL _stdcall FreeMemoryBuffer(void* pDllParams, char** pDataBuff)
	{
		if (pDataBuff != NULL)
		{
			free(*pDataBuff);
			*pDataBuff = NULL;
		}
		return TRUE;
	}
	CRITICAL_SECTION m_csEvents;
	CRITICAL_SECTION m_csData;
	HANDLE m_hEventDoMethod;
	GP_RarefiedArr<sctDllStartParams*> m_lstDllsStartParams;
};

#endif // !defined(AFX_DLLSERVER_H__BE645F28_12FE_4FD1_AE9C_C0630765422B__INCLUDED_)

#endif // _DLLSERVER_H_

