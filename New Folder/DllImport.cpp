// DllImport.cpp: implementation of the DllImport class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "DllImport.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DllImport::DllImport()
{
	m_hinstDllLib = NULL;
	m_pFuncInit = NULL;
	m_pFuncTerminate = NULL;
	m_pFuncDoMethod = NULL;
	m_pDataBuff = NULL;
}

DllImport::DllImport(sctDllStartParams* pDllStartParams)
{
	m_pStartParams = pDllStartParams;
	m_pDataBuff = NULL;
}

DllImport::~DllImport()
{
	if (m_pDataBuff != NULL) delete m_pDataBuff;
	m_pDataBuff=NULL;
	if (m_hinstDllLib) Unload();
}

BOOL DllImport::Load()
{
	BOOL bRes = FALSE;

	if (m_pStartParams != NULL && m_pStartParams->csDllFileName != "")
	{
		// Unload();
		try
		{
			m_hinstDllLib = LoadLibrary(m_pStartParams->csDllFileName);
		}
		catch(...)
		{
			m_hinstDllLib = NULL;
		}
		if (m_hinstDllLib) 
		{ 
			m_pFuncInit = (DLL_Init) GetProcAddress(m_hinstDllLib, "Init");
			m_pFuncTerminate = (DLL_Terminate) GetProcAddress(m_hinstDllLib, "Terminate");
			m_pFuncDoMethod = (DLL_DoMethod) GetProcAddress(m_hinstDllLib, "DoMethod");
			m_pFuncFreeMemoryBuffer = (DLL_FreeMemoryBuffer) GetProcAddress(m_hinstDllLib, "FreeMemoryBuffer");
			bRes = (m_pFuncInit != NULL) && (m_pFuncTerminate != NULL) && \
				(m_pFuncDoMethod != NULL) && (m_pFuncFreeMemoryBuffer != NULL);
			if (!bRes)
			{
				FreeLibrary(m_hinstDllLib);
				m_hinstDllLib = NULL;
			}
			else
				bRes = (m_hinstDllLib)?m_pFuncInit(m_pStartParams, m_pStartParams->pFuncRaiseEvent, m_pStartParams->pFuncGetData, m_pStartParams->pFuncFreeMemoryBuffer):0;
		}
	}
	return bRes;
}

BOOL DllImport::Unload()
{
	BOOL bRes = TRUE;
	if (m_hinstDllLib != NULL) 
	{
		bRes = (m_hinstDllLib)?m_pFuncTerminate():0;
		FreeLibrary(m_hinstDllLib);
	}
	m_hinstDllLib = NULL;
	RemoveAllMsg();
	return bRes;
}

BOOL DllImport::DoMethod(const char* pFuncName, const char* pFuncParam, char** ppRetVal)
{
	int iRes = -1;
	char *pRetBuff = NULL;

	if (ppRetVal != NULL)
	{
		iRes = (m_hinstDllLib)?m_pFuncDoMethod(pFuncName, pFuncParam, &pRetBuff):0;
		if (pRetBuff)
		{
			(*ppRetVal) = new char[(int)strlen(pRetBuff) + 1];
			strcpy((*ppRetVal), pRetBuff);
			iRes = (m_hinstDllLib)?m_pFuncFreeMemoryBuffer(&pRetBuff):0;
		}
	}
	else
		iRes = (m_hinstDllLib)?m_pFuncDoMethod(pFuncName, pFuncParam, ppRetVal):0;
	return iRes;
}

BOOL DllImport::SetData(const char* pDataBuff)
{
	// Необходимо сохранить данные, пришедшие от сервера(pDataBuff)
	//............................................................
	int iDataLen = (int)strlen(pDataBuff) + 1;
	char *strTmp;
	
	if (iDataLen > 1)
		if (m_pDataBuff != NULL)
		{
			strTmp = new char[iDataLen + (int)strlen(m_pDataBuff)];
			strcpy(strTmp, m_pDataBuff);
			strcat(strTmp, pDataBuff);
			delete m_pDataBuff;
			m_pDataBuff = strTmp;
		}
		else
		{
			m_pDataBuff = new char[iDataLen];
			strcpy(m_pDataBuff, pDataBuff);
		}
	return TRUE;
}

BOOL DllImport::GetData(char** pDataBuff)
{
	*pDataBuff = m_pDataBuff;
	m_pDataBuff = NULL;
	return TRUE;
}


BOOL DllImport::AddMsg(sctDllExchangeBuff* psctDllMsg)
{
	EnterCriticalSection(&(m_pStartParams->csDllMsg));
	__try 
	{
		m_lstDllsMsgs.AddTail(psctDllMsg);
	}
	__finally 
	{
		;
	}
	LeaveCriticalSection(&(m_pStartParams->csDllMsg));
	return TRUE;
}

sctDllExchangeBuff* DllImport::GetMsg(enDllMsgDirectionType iDllMsgDirection, enDllMsgType iDllMsgType, BOOL bRemoveMsg)
{
	sctDllExchangeBuff* psctDllMsg = NULL;
	int i = 0, iCount = 0;
	POSITION posTmp;
	EnterCriticalSection(&(m_pStartParams->csDllMsg));
	__try 
	{
		iCount = m_lstDllsMsgs.GetCount();
		if (iCount > 0)
		{
			i = 0; 
			posTmp = m_lstDllsMsgs.GetHeadPosition(); 
			if (posTmp != NULL)
				while (i < iCount)
				{
					psctDllMsg = m_lstDllsMsgs.GetAt(posTmp);
					if ((psctDllMsg != NULL) && (psctDllMsg->iDirection == iDllMsgDirection) && (psctDllMsg->iMsgType == iDllMsgType))
					{
						if (bRemoveMsg)
							m_lstDllsMsgs.RemoveAt(posTmp); 
						i = iCount + 100;
					}
					m_lstDllsMsgs.GetNext(posTmp);
					//posTmp++;
					i++;
				}
		}
	}
	__finally 
	{
		;
	}
	LeaveCriticalSection(&(m_pStartParams->csDllMsg));
	return (i < (iCount + 100))?NULL:psctDllMsg;
}

sctDllExchangeBuff* DllImport::GetMsg(BOOL bRemoveMsg)
{
	sctDllExchangeBuff* psctDllMsg = NULL;
	int iCount = 0;
	POSITION posTmp;
	EnterCriticalSection(&(m_pStartParams->csDllMsg));
	__try 
	{
		iCount = m_lstDllsMsgs.GetCount();
		if (iCount > 0)
		{
			posTmp = m_lstDllsMsgs.GetHeadPosition(); 
			if (posTmp != NULL)
			{
				psctDllMsg = m_lstDllsMsgs.GetAt(posTmp);
				if (bRemoveMsg)
					m_lstDllsMsgs.RemoveAt(posTmp); 
			}
		}
	}
	__finally 
	{
		;
	}
	LeaveCriticalSection(&(m_pStartParams->csDllMsg));
	return psctDllMsg;
}

BOOL DllImport::RemoveAllMsg()
{
	int i, iCount;
	sctDllExchangeBuff* psctDllMsg;
	EnterCriticalSection(&(m_pStartParams->csDllMsg));
	__try 
	{
		iCount = m_lstDllsMsgs.GetCount();
		if (iCount > 0)
			for (i = 0; i < iCount; i++)
			{
				psctDllMsg = m_lstDllsMsgs.GetHead(); 
				m_lstDllsMsgs.RemoveHead();
				sctDllExchangeBuff::FreeExchangeBuff(&psctDllMsg, TRUE, TRUE, TRUE);
			}
	}
	__finally 
	{
		;
	}
	LeaveCriticalSection(&(m_pStartParams->csDllMsg));
	return TRUE;
}