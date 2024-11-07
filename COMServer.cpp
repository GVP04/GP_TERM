// COMServer.cpp: implementation of the CCOMServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "COMServer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

UINT COMFunc(void* pDllStartParamsIN)
{
	sctDllExchangeBuff* pBuffTmp; 
	sctDllStartParams m_COMStartParams;
	m_COMStartParams=*((sctDllStartParams*)pDllStartParamsIN);

	DllImport dllImportTmp = DllImport(&m_COMStartParams);

	CComObject<CCOMImport>* pCOMImportTmp = NULL;
	int i = 0;

	if (SUCCEEDED(CComObject<CCOMImport>::CreateInstance(&pCOMImportTmp)))
	{
		if (pCOMImportTmp->Load((sctDllStartParams*)&m_COMStartParams))
		{
			InitializeCriticalSection(&(m_COMStartParams.csDllMsg));
			m_COMStartParams.pDll = pCOMImportTmp;
			*m_COMStartParams.piReturn=m_COMStartParams.iDllPos;
			((CCOMServer *)m_COMStartParams.pDllServer)->m_lstCOMsStartParams[m_COMStartParams.iDllPos]=(&m_COMStartParams);
			m_COMStartParams.iStatus=((sctDllStartParams*)pDllStartParamsIN)->iStatus = 1;

			while(1)
			{
				Sleep(10);
				pBuffTmp = pCOMImportTmp->GetMsg(TRUE);
				if (pBuffTmp != NULL)
				{
					i++;
					if ((pBuffTmp->iDirection == iDllMsgFromServer) && (pBuffTmp->iMsgType == iDllMsgDoMethod))
					{
						// Выполнение метода (DoMethod)
						pCOMImportTmp->DoMethod(pBuffTmp->strMsgName, pBuffTmp->strMsgBuff, pBuffTmp->pstrMsgRet);
						if (pBuffTmp->m_hEventMsg)		SetEvent(pBuffTmp->m_hEventMsg);
						else							sctDllExchangeBuff::FreeExchangeBuff(&pBuffTmp, TRUE, TRUE, TRUE);
					}
					else
					if ((pBuffTmp->iDirection == iDllMsgFromServer) && (pBuffTmp->iMsgType == iDllMsgData))
					{
						// Передача данных от сервера
						pCOMImportTmp->SetData(pBuffTmp->strMsgBuff);
						sctDllExchangeBuff::FreeExchangeBuff(&pBuffTmp, TRUE, TRUE, FALSE);
					}
					else
					if ((pBuffTmp->iDirection == iDllMsgFromServer) && ((pBuffTmp->iMsgType == iDllMsgUnload) || (pBuffTmp->iMsgType == iDllMsgUnloadNow)))
					{
						// Выход и выгрузка Dll
						pCOMImportTmp->Unload();
						((sctDllStartParams*)pDllStartParamsIN)->pDll = NULL;
						if (pBuffTmp->m_hEventMsg) SetEvent(pBuffTmp->m_hEventMsg);
						sctDllExchangeBuff::FreeExchangeBuff(&pBuffTmp, TRUE, TRUE, TRUE);
						break;
					}
				}
				// Немедленный выход и выгрузка
				pBuffTmp = pCOMImportTmp->GetMsg(iDllMsgFromServer,iDllMsgUnloadNow, TRUE);
				if (pBuffTmp != NULL)
				{
					// Выход и выгрузка Dll
					pCOMImportTmp->Unload();
					((sctDllStartParams*)pDllStartParamsIN)->pDll = NULL;
					if (pBuffTmp->m_hEventMsg) SetEvent(pBuffTmp->m_hEventMsg);
					sctDllExchangeBuff::FreeExchangeBuff(&pBuffTmp, TRUE, TRUE, TRUE);
					break;
				}
			}
		}
		else
		{
			m_COMStartParams.iStatus=((sctDllStartParams*)pDllStartParamsIN)->iStatus = -1;
		}
		pCOMImportTmp->Release();
		pCOMImportTmp=NULL;
	}
	else
	{
		((sctDllStartParams*)pDllStartParamsIN)->iStatus = -2;
	}
	return m_COMStartParams.iStatus;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCOMServer::CCOMServer()
{
	InitializeCriticalSection(&m_csEvents);
	InitializeCriticalSection(&m_csData);
	m_hEventDoMethod = CreateEvent( 
        NULL,			    // no security attributes
        TRUE,		        // manual-reset event
        FALSE,				// initial state is signaled
        "DoMethodEvent"		// object name
        );
	sctDllStartParams *defParam=NULL;
	m_lstCOMsStartParams.SetInitValue(defParam);
}

CCOMServer::~CCOMServer()
{

	// Остановка всех потоков
	UnloadAll();
	DeleteCriticalSection(&m_csData);
	DeleteCriticalSection(&m_csEvents);
	CloseHandle(m_hEventDoMethod);
}

int CCOMServer::LoadDll(const char* strProgID, HWND hwndParent, const char *ccExtName, const char *ccSubroutineName)
{
	int ret=-1;
	if (!*ccExtName || GetIdByName(ccExtName)<0)
	{
		sctDllStartParams mCOMStartParams;
		static int tmpCntr;
		tmpCntr++;

		mCOMStartParams.csName=ccExtName;
		if (!*ccExtName || (*ccExtName>='0' && *ccExtName<='9'))	mCOMStartParams.csName.Format("_%d",tmpCntr);


		mCOMStartParams.csSubroutineName=ccSubroutineName;
		mCOMStartParams.csDllFileName = strProgID;
		mCOMStartParams.pDllServer = (void*)this;
		mCOMStartParams.piReturn = &ret;
		mCOMStartParams.pDll = NULL;
		mCOMStartParams.iStatus = 0;
		mCOMStartParams.iDllPos = tmpCntr;
		mCOMStartParams.hwndParent = hwndParent;
		mCOMStartParams.iCOMType = iCOMDll;
		mCOMStartParams.pFuncRaiseEvent = RaiseEvent;
		mCOMStartParams.pFuncGetData = NULL; 
		mCOMStartParams.pFuncFreeMemoryBuffer = NULL;

		if (AfxBeginThread(COMFunc,(void*)&mCOMStartParams))
		{
			while(mCOMStartParams.iStatus == 0) Sleep(5);
		}
	}
	return ret;
}

int CCOMServer::LoadExe(const char* strProgID, HWND hwndParent, const char *ccExtName, const char *ccSubroutineName)
{
	int ret=-1;
	if (!*ccExtName || GetIdByName(ccExtName)<0)
	{
		sctDllStartParams mCOMStartParams;
		static int tmpCntr;
		tmpCntr++;

		mCOMStartParams.csName=ccExtName;
		if (!*ccExtName || (*ccExtName>='0' && *ccExtName<='9'))	mCOMStartParams.csName.Format("_%d",tmpCntr);


		mCOMStartParams.csSubroutineName=ccSubroutineName;
		mCOMStartParams.csDllFileName = strProgID;
		mCOMStartParams.pDllServer = (void*)this;
		mCOMStartParams.piReturn = &ret;
		mCOMStartParams.pDll = NULL;
		mCOMStartParams.iStatus = 0;
		mCOMStartParams.iDllPos = tmpCntr;
		mCOMStartParams.hwndParent = hwndParent;
		mCOMStartParams.iCOMType = iCOMExe;
		mCOMStartParams.pFuncRaiseEvent = RaiseEvent;
		mCOMStartParams.pFuncGetData = NULL; 
		mCOMStartParams.pFuncFreeMemoryBuffer = NULL;

		if (AfxBeginThread(COMFunc,(void*)&mCOMStartParams))
		{
			while(mCOMStartParams.iStatus == 0) Sleep(5);
		}
	}
	return ret;
}

BOOL CCOMServer::Unload(const char *ccExtName)
{
	int id=GetIdByName(ccExtName);
	return id<0?FALSE:Unload(id);
}

BOOL CCOMServer::Unload(int iDllIndex)
{
	sctDllStartParams* pCOMStartParams;
	sctDllExchangeBuff* pDllUnload;
	CComObject<CCOMImport>* pCOMImportTmp;
	BOOL bRes = FALSE;

	// Поиск нужной Dll
	if (!m_lstCOMsStartParams.IsIdInArray(iDllIndex)
	 || !(pCOMStartParams = m_lstCOMsStartParams[iDllIndex])) return FALSE;

	pCOMImportTmp = (CComObject<CCOMImport>*)pCOMStartParams->pDll; 
	// Выгрузка Dll
	pDllUnload = new sctDllExchangeBuff;
	pDllUnload->pDllParams = (void*)pCOMImportTmp;
	pDllUnload->iDirection = iDllMsgFromServer;
	// pDllUnload->iMsgType = iDllMsgUnload;
	pDllUnload->iMsgType = iDllMsgUnloadNow;
	pDllUnload->strMsgName = NULL;		// Имя сообщения
	pDllUnload->strMsgBuff = NULL;		// Буффер с сообщением
	pDllUnload->pstrMsgRet = NULL;

	ResetEvent(m_hEventDoMethod);
	pDllUnload->m_hEventMsg = m_hEventDoMethod;

	// Выполнение останова
	bRes = TRUE;
	pCOMImportTmp->AddMsg(pDllUnload);
	WaitForSingleObjectEx(m_hEventDoMethod, INFINITE, TRUE);
	ResetEvent(m_hEventDoMethod);
	return bRes;
}

// Остановка всех потоков
BOOL CCOMServer::UnloadAll()
{
	if (m_lstCOMsStartParams.GetCount() > 0)
	{
		m_lstCOMsStartParams.SelectFirst();
		do
		{
			Unload(m_lstCOMsStartParams.GetSelectedId());
		}
		while(m_lstCOMsStartParams.SelectNext()!=0xFFFFFFFF);
		m_lstCOMsStartParams.ResetArray();
	}
	return TRUE;
}

BOOL CCOMServer::DoMethod(int iDllIndex, const char* pFuncName, const char* pFuncParam, char** ppRetVal, BOOL bWaitDoMethod)
{
	sctDllStartParams* pCOMStartParams;
	sctDllExchangeBuff* pDllDoMethod;
	CComObject<CCOMImport>* pCOMImportTmp;
	BOOL bRes = FALSE;

	// Поиск нужной Dll
	if (!m_lstCOMsStartParams.IsIdInArray(iDllIndex)
	 || !(pCOMStartParams = m_lstCOMsStartParams[iDllIndex])) return FALSE;

	pCOMImportTmp = (CComObject<CCOMImport>*)pCOMStartParams->pDll; 
	// Передача данных в Dll
	pDllDoMethod = new sctDllExchangeBuff;
	pDllDoMethod->pDllParams = (void*)pCOMImportTmp;
	pDllDoMethod->iDirection = iDllMsgFromServer;
	pDllDoMethod->iMsgType = iDllMsgDoMethod;
	if (pFuncName != NULL)
	{
		pDllDoMethod->strMsgName = new char[(int)strlen(pFuncName) + 1];
		strcpy(pDllDoMethod->strMsgName, pFuncName);			// Имя сообщения
	}
	else
		pDllDoMethod->strMsgName = NULL;
	if (pFuncParam != NULL)
	{
		pDllDoMethod->strMsgBuff = new char[(int)strlen(pFuncParam) + 1];
		strcpy(pDllDoMethod->strMsgBuff, pFuncParam);		// Буффер с сообщением
	}
	else
		pDllDoMethod->strMsgBuff = NULL;
	pDllDoMethod->pstrMsgRet = ppRetVal;
	pDllDoMethod->m_hEventMsg = NULL;
	if (bWaitDoMethod)
	{
		ResetEvent(m_hEventDoMethod);
		pDllDoMethod->m_hEventMsg = m_hEventDoMethod;
	}
	// Выполнение метода
	//bRes = pCOMImportTmp->DoMethod(pFuncName, pFuncParam, ppRetVal);
	bRes = TRUE;

	pCOMImportTmp->AddMsg(pDllDoMethod);

	if (bWaitDoMethod)
	{
		WaitForSingleObjectEx(m_hEventDoMethod, INFINITE, TRUE);
		ResetEvent(m_hEventDoMethod);
		sctDllExchangeBuff::FreeExchangeBuff(&pDllDoMethod, TRUE, TRUE, FALSE);
	}
	//pDllDoMethod->strMsgRet;		// Буффер возврата сообщения
	return bRes;
}

BOOL CCOMServer::SetData(int iDllIndex, const char*pDataBuff)
{
	BOOL bRes = FALSE;
	sctDllStartParams* pCOMStartParams;
	sctDllExchangeBuff* pDllSetData;
	CComObject<CCOMImport>* pCOMImportTmp;

	// Поиск нужной Dll
	if (!m_lstCOMsStartParams.IsIdInArray(iDllIndex)
	 || !(pCOMStartParams = m_lstCOMsStartParams[iDllIndex])) return FALSE;

	EnterCriticalSection(&m_csData);
	__try 
	{
		pCOMImportTmp = (CComObject<CCOMImport>*)pCOMStartParams->pDll; 
		// Передача данных в Dll
		pDllSetData = new sctDllExchangeBuff;
		pDllSetData->pDllParams = (void*)pCOMImportTmp;
		pDllSetData->iDirection = iDllMsgFromServer;
		pDllSetData->iMsgType = iDllMsgData;
		pDllSetData->strMsgName = NULL;			// Имя сообщения
		pDllSetData->strMsgBuff = new char[(int)strlen(pDataBuff) + 1];
		strcpy(pDllSetData->strMsgBuff, pDataBuff);		// Буффер с сообщением
		pDllSetData->pstrMsgRet = NULL;
		pDllSetData->m_hEventMsg = NULL;

		// Передача данных
		bRes = TRUE;
		pCOMImportTmp->AddMsg(pDllSetData);
	}
	__finally 
	{
		;
	}
	LeaveCriticalSection(&m_csData);
	return bRes;
}

int CCOMServer::GetIdByName(const char *ccName)
{
	int ret=-1;

	if (m_lstCOMsStartParams.GetCount() > 0)
	{
		m_lstCOMsStartParams.SelectFirst();
		while(m_lstCOMsStartParams.GetSelected()->csName!=ccName)
			m_lstCOMsStartParams.SelectNext();

		ret=m_lstCOMsStartParams.GetSelectedId();
	}
	return ret;
}

const sctDllStartParams * CCOMServer::GetStartParamsByName(const char *ccName)
{
	sctDllStartParams *ret=NULL;

	int id=GetIdByName(ccName);
	if (id>0) ret=m_lstCOMsStartParams[id];

	return ret;
}

BOOL _stdcall CCOMServer::RaiseEvent(void* pCOMParams, const char* pEventName, const char* pEventData)
{
	BOOL bRes = FALSE;
	sctDllStartParams* pCOMTmp = (sctDllStartParams*)pCOMParams;
	CCOMServer* pCOMServerTmp;

	if (pCOMTmp != NULL && pCOMTmp->pDllServer != NULL)
	{
		pCOMServerTmp = (CCOMServer*)pCOMTmp->pDllServer;
		EnterCriticalSection(&(pCOMServerTmp->m_csEvents));
		__try 
		{
			GPMessage::GPSendComEvent(pCOMTmp,pEventName,pEventData);
			bRes = TRUE;
		}
		__finally 
		{
			;
		}
		LeaveCriticalSection(&(pCOMServerTmp->m_csEvents));
	}
	return bRes;
}
