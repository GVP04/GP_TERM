// DllServer.cpp: implementation of the DllServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "DllServer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

UINT DllFunc(void* pDllStartParamsIN)
{
	sctDllExchangeBuff* pBuffTmp; 
	sctDllStartParams m_DllStartParams;
	m_DllStartParams=*((sctDllStartParams*)pDllStartParamsIN);

	DllImport dllImportTmp = DllImport(&m_DllStartParams);

	int i = 0;

	if (dllImportTmp.Load())
	{
		InitializeCriticalSection(&(m_DllStartParams.csDllMsg));
		m_DllStartParams.pDll = &dllImportTmp;
		*m_DllStartParams.piReturn=m_DllStartParams.iDllPos;
		m_DllStartParams.iStatus=((sctDllStartParams*)pDllStartParamsIN)->iStatus = 1;
		((DllServer *)m_DllStartParams.pDllServer)->m_lstDllsStartParams[m_DllStartParams.iDllPos]=(&m_DllStartParams);

		while(1)
		{
			Sleep(10);
			pBuffTmp = dllImportTmp.GetMsg(TRUE);
			if (pBuffTmp != NULL)
			{
				i++;
				if ((pBuffTmp->iDirection == iDllMsgFromServer) && (pBuffTmp->iMsgType == iDllMsgDoMethod))
				{
					// Выполнение метода (DoMethod)
					dllImportTmp.DoMethod(pBuffTmp->strMsgName, pBuffTmp->strMsgBuff, pBuffTmp->pstrMsgRet);
					if (pBuffTmp->m_hEventMsg != NULL)
						SetEvent(pBuffTmp->m_hEventMsg);
					else
						sctDllExchangeBuff::FreeExchangeBuff(&pBuffTmp, TRUE, TRUE, TRUE);
				}
				else
				if ((pBuffTmp->iDirection == iDllMsgFromServer) && (pBuffTmp->iMsgType == iDllMsgData))
				{
					// Передача данных от сервера
					dllImportTmp.SetData(pBuffTmp->strMsgBuff);
					sctDllExchangeBuff::FreeExchangeBuff(&pBuffTmp, TRUE, TRUE, FALSE);
				}
				else
				if ((pBuffTmp->iDirection == iDllMsgFromServer) && ((pBuffTmp->iMsgType == iDllMsgUnload) || (pBuffTmp->iMsgType == iDllMsgUnloadNow)))
				{
					// Выход и выгрузка Dll
					dllImportTmp.Unload();
					m_DllStartParams.pDll = NULL;
					SetEvent(pBuffTmp->m_hEventMsg);
					sctDllExchangeBuff::FreeExchangeBuff(&pBuffTmp, TRUE, TRUE, TRUE);
					break;
				}
			}
			// Немедленный выход и выгрузка
			pBuffTmp = dllImportTmp.GetMsg(iDllMsgFromServer,iDllMsgUnloadNow, TRUE);
			if (pBuffTmp)
			{
				// Выход и выгрузка Dll
				dllImportTmp.Unload();
				m_DllStartParams.pDll = NULL;
				SetEvent(pBuffTmp->m_hEventMsg);
				sctDllExchangeBuff::FreeExchangeBuff(&pBuffTmp, TRUE, TRUE, TRUE);
				break;
			}
		}
		DeleteCriticalSection(&(m_DllStartParams.csDllMsg));
	}
	else
		m_DllStartParams.iStatus=((sctDllStartParams*)pDllStartParamsIN)->iStatus = -1;

	return m_DllStartParams.iStatus;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DllServer::DllServer()
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
	m_lstDllsStartParams.SetInitValue(defParam);
}

DllServer::~DllServer()
{

	// Остановка всех потоков
	UnloadAll();
	DeleteCriticalSection(&m_csData);
	DeleteCriticalSection(&m_csEvents);
}

int DllServer::Load(const char* strDllFileName, const char *ccExtName, const char *ccSubroutineName)
{
	int ret=-1;
	if (*ccExtName && GetIdByName(ccExtName)) Unload(ccExtName);
	
	if (!*ccExtName || GetIdByName(ccExtName)<0)
	{

		sctDllStartParams mDllStartParams;
		static int tmpCntr;
		tmpCntr++;

		mDllStartParams.csName=ccExtName;
		if (!*ccExtName || (*ccExtName>='0' && *ccExtName<='9'))	mDllStartParams.csName.Format("_%d",tmpCntr);

		mDllStartParams.csSubroutineName=ccSubroutineName;
		mDllStartParams.csDllFileName = strDllFileName;
		mDllStartParams.pDllServer = (void*)this;
		mDllStartParams.piReturn = &ret;
		mDllStartParams.pDll = NULL;
		mDllStartParams.iStatus = 0;
		mDllStartParams.iDllPos = tmpCntr;
		mDllStartParams.pFuncRaiseEvent = RaiseEvent;
		mDllStartParams.pFuncGetData = GetData; 
		mDllStartParams.pFuncFreeMemoryBuffer = FreeMemoryBuffer;

		if (AfxBeginThread(DllFunc,(void*)(&mDllStartParams)))
		{
			while(mDllStartParams.iStatus == 0) Sleep(5);
		}

	}
	return ret;
}

BOOL DllServer::Unload(const char *ccExtName)
{
	int id=GetIdByName(ccExtName);
	return id<0?FALSE:Unload(id);
}

BOOL DllServer::Unload(int iDllIndex)
{
	sctDllStartParams* pDllStartParams;
	sctDllExchangeBuff* pDllUnload;
	DllImport* pDllImportTmp;
	BOOL bRes = FALSE;

	// Поиск нужной Dll
	if (!m_lstDllsStartParams.IsIdInArray(iDllIndex)
	 || !(pDllStartParams = m_lstDllsStartParams[iDllIndex])) return FALSE;

	pDllImportTmp = (DllImport*)pDllStartParams->pDll; 
	// Выгрузка Dll
	pDllUnload = new sctDllExchangeBuff;
	pDllUnload->pDllParams = (void*)pDllImportTmp;
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
	pDllImportTmp->AddMsg(pDllUnload);
	WaitForSingleObjectEx(m_hEventDoMethod, INFINITE, TRUE);
	ResetEvent(m_hEventDoMethod);

	m_lstDllsStartParams.RemoveItem(iDllIndex);
	return bRes;
}

// Остановка всех потоков
BOOL DllServer::UnloadAll()
{
	if (m_lstDllsStartParams.GetCount() > 0)
	{
		m_lstDllsStartParams.SelectFirst();
		do
		{
			Unload(m_lstDllsStartParams.GetSelectedId());
		}
		while(m_lstDllsStartParams.SelectNext()!=0xFFFFFFFF);
		m_lstDllsStartParams.ResetArray();
	}
	return TRUE;
}

BOOL DllServer::DoMethod(int iDllIndex, const char* pFuncName, const char* pFuncParam, char** ppRetVal, BOOL bWaitDoMethod)
{
	sctDllStartParams* pDllStartParams;
	sctDllExchangeBuff* pDllDoMethod;
	DllImport* pDllImportTmp;
	BOOL bRes = FALSE;

	// Поиск нужной Dll
	if (!m_lstDllsStartParams.IsIdInArray(iDllIndex)
	 || !(pDllStartParams = m_lstDllsStartParams[iDllIndex])) return FALSE;

	pDllImportTmp = (DllImport*)pDllStartParams->pDll; 
	// Передача данных в Dll
	pDllDoMethod = new sctDllExchangeBuff;
	pDllDoMethod->pDllParams = (void*)pDllImportTmp;
	pDllDoMethod->iDirection = iDllMsgFromServer;
	pDllDoMethod->iMsgType = iDllMsgDoMethod;
	pDllDoMethod->strMsgName = new char[(int)strlen(pFuncName) + 1];
	strcpy(pDllDoMethod->strMsgName, pFuncName);			// Имя сообщения
	pDllDoMethod->strMsgBuff = new char[(int)strlen(pFuncParam) + 1];
	strcpy(pDllDoMethod->strMsgBuff, pFuncParam);		// Буффер с сообщением
	pDllDoMethod->pstrMsgRet = ppRetVal;
	pDllDoMethod->m_hEventMsg = NULL;
	if (bWaitDoMethod)
	{
		ResetEvent(m_hEventDoMethod);
		pDllDoMethod->m_hEventMsg = m_hEventDoMethod;
	}
	// Выполнение метода
	//bRes = pDllImportTmp->DoMethod(pFuncName, pFuncParam, ppRetVal);
	bRes = TRUE;

	pDllImportTmp->AddMsg(pDllDoMethod);

	if (bWaitDoMethod)
	{
		WaitForSingleObjectEx(m_hEventDoMethod, INFINITE, TRUE);
		ResetEvent(m_hEventDoMethod);
		sctDllExchangeBuff::FreeExchangeBuff(&pDllDoMethod, TRUE, TRUE, FALSE);
	}
	//pDllDoMethod->strMsgRet;		// Буффер возврата сообщения
	return bRes;
}

BOOL DllServer::SetData(int iDllIndex, const char*pDataBuff)
{
	BOOL bRes = FALSE;
	sctDllStartParams* pDllStartParams;
	sctDllExchangeBuff* pDllSetData;
	DllImport* pDllImportTmp;

	// Поиск нужной Dll
	if (!m_lstDllsStartParams.IsIdInArray(iDllIndex)
	 || !(pDllStartParams = m_lstDllsStartParams[iDllIndex])) return FALSE;

	EnterCriticalSection(&m_csData);
	__try 
	{
		pDllImportTmp = (DllImport*)pDllStartParams->pDll; 
		// Передача данных в Dll
		pDllSetData = new sctDllExchangeBuff;
		pDllSetData->pDllParams = (void*)pDllImportTmp;
		pDllSetData->iDirection = iDllMsgFromServer;
		pDllSetData->iMsgType = iDllMsgData;
		pDllSetData->strMsgName = NULL;			// Имя сообщения
		pDllSetData->strMsgBuff = new char[(int)strlen(pDataBuff) + 1];
		strcpy(pDllSetData->strMsgBuff, pDataBuff);		// Буффер с сообщением
		pDllSetData->pstrMsgRet = NULL;
		pDllSetData->m_hEventMsg = NULL;

		// Передача данных
		bRes = TRUE;
		pDllImportTmp->AddMsg(pDllSetData);
	}
	__finally 
	{
		;
	}
	LeaveCriticalSection(&m_csData);
	return bRes;
}

int DllServer::GetIdByName(const char *ccName)
{
	int ret=-1;

	if (m_lstDllsStartParams.GetCount() > 0)
	{
		m_lstDllsStartParams.SelectFirst();
		sctDllStartParams *selParam;
		while((selParam=m_lstDllsStartParams.GetSelected()) &&  selParam->csName!=ccName)
			m_lstDllsStartParams.SelectNext();

		ret=m_lstDllsStartParams.GetSelectedId();
	}
	return ret;
}

const sctDllStartParams * DllServer::GetStartParamsByName(const char *ccName)
{
	sctDllStartParams *ret=NULL;

	int id=GetIdByName(ccName);
	if (id>0) ret=m_lstDllsStartParams[id];

	return ret;
}

BOOL _stdcall DllServer::RaiseEvent(void* pDllParams, const char* pEventName, const char* pEventData)
{
	BOOL bRes = FALSE;
	sctDllStartParams* pDllTmp = (sctDllStartParams*)pDllParams;
	DllServer* pDllServerTmp;

	if (pDllTmp != NULL && pDllTmp->pDllServer != NULL)
	{
		pDllServerTmp = (DllServer*)pDllTmp->pDllServer;
		EnterCriticalSection(&(pDllServerTmp->m_csEvents));
		__try 
		{
			GPMessage::GPSendComEvent(pDllTmp,pEventName,pEventData);
			bRes = TRUE;
		}
		__finally 
		{
			;
		}
		LeaveCriticalSection(&(pDllServerTmp->m_csEvents));
	}
	return bRes;
}
