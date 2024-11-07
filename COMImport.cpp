// COMImport.cpp : Implementation of CCOMImport
#include "stdafx.h"
#include "gp_term.h"
#include "COMImport.h"

/////////////////////////////////////////////////////////////////////////////
// CCOMImport

CCOMImport::CCOMImport()
{
	::CoInitialize(NULL);
	m_iFuncInit = -1;
	m_iFuncTerminate = -1;
	m_iFuncDoMethodW = -1;
	m_pDataBuff = NULL;
	m_pDisp = NULL;

	/*
	ITypeLib *pTypeLib;
	HRESULT hr;
	hr = LoadTypeLibEx(L"GPTermConnect2.tlb", REGKIND_REGISTER, &pTypeLib);
	if(SUCCEEDED(hr))
	{
		pTypeLib->Release();
	} */
}

CCOMImport::~CCOMImport()
{
	if (m_pDataBuff != NULL)
		delete m_pDataBuff;
	if (m_pDisp != NULL) 
	{
		if (m_pStartParams->iCOMType != iCOMDll)
			m_pDisp->Release();
		m_pDisp = NULL;
	}
	//Unload();
	RemoveAllMsg();
	::CoFreeUnusedLibraries();
	::CoUninitialize();
}

BOOL CCOMImport::Load(sctDllStartParams* pDllStartParams)
{
	HRESULT hr;
	BOOL bRes = FALSE;
	BSTR bstrTmp = NULL;
	OLECHAR FAR* szMemberInit = L"Init";
	OLECHAR FAR* szMemberTerminate = L"Terminate";
	OLECHAR FAR* szMemberDoMethodA = L"DoMethodA";
	OLECHAR FAR* szMemberDoMethodW = L"DoMethodW";
	//IDispatch *pDisp = this;

	m_pStartParams = pDllStartParams;

	if (m_pStartParams != NULL && m_pStartParams->csDllFileName != "")
	{
		// Unload();
		try
		{
			bstrTmp = m_pStartParams->csDllFileName.AllocSysString();
			hr = ::CLSIDFromProgID(bstrTmp, &m_clsidCOM);
			if (bstrTmp != NULL)
				::SysFreeString(bstrTmp);
			if (SUCCEEDED(hr))
			{
				if (m_pStartParams->iCOMType == iCOMDll) 
					hr = CoCreateInstance(m_clsidCOM, NULL, CLSCTX_INPROC_SERVER, __uuidof(IDispatch), (void**)&m_pDisp);
				else
					hr = CoCreateInstance(m_clsidCOM, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IDispatch), (void**)&m_pDisp);
				if (SUCCEEDED(hr))
				{
					bRes = SUCCEEDED(m_pDisp->GetIDsOfNames(IID_NULL, &szMemberInit, 1, LOCALE_SYSTEM_DEFAULT, &m_iFuncInit)) && \
							SUCCEEDED(m_pDisp->GetIDsOfNames(IID_NULL, &szMemberTerminate, 1, LOCALE_SYSTEM_DEFAULT, &m_iFuncTerminate)) && \
							SUCCEEDED(m_pDisp->GetIDsOfNames(IID_NULL, &szMemberDoMethodW, 1, LOCALE_SYSTEM_DEFAULT, &m_iFuncDoMethodW));
				}
			}
		}
		catch(...)
		{
			m_pDisp = NULL;
		}
		if (m_pDisp) 
		{ 
			bRes = (m_iFuncInit >= 0) && (m_iFuncTerminate >= 0) && (m_iFuncDoMethodW >=0);
			if (!bRes)
			{
				m_pDisp->Release(); 
				m_pDisp = NULL;
			}
			else
			{
				VARIANT* varArrParams = new VARIANT[2];

				{
					char strTmp2[256];
					sprintf(strTmp2, "CCOMImport::Load.this: %d, hwndParent: %d", (DWORD)((IDispatch *)this), ((long) m_pStartParams->hwndParent));
					//::MessageBox(NULL, strTmp2, "", 1); 
				}

				//IDispatch *pDispTmp = (IDispatch *)this;

				((IDispatch *)this)->AddRef();
				CMemUtils::MEM_CopyDispatchToVariant(&(varArrParams[1]), this);
				//CMemUtils::MEM_CopyPDispatchToVariant(&(varArrParams[1]), &(pDispTmp));
				CMemUtils::MEM_CopyLongToVariant(&(varArrParams[0]), ((long) m_pStartParams->hwndParent));
				DISPPARAMS params = {varArrParams, NULL, 2, 0};
				hr = m_pDisp->Invoke(m_iFuncInit, IID_NULL, 0, DISPATCH_METHOD, &params, NULL, NULL, NULL);
				VariantClear(&(varArrParams[0]));
				VariantClear(&(varArrParams[1]));
				delete []varArrParams;
			}
		}
	}
	return bRes;
}

BOOL CCOMImport::Unload()
{
	BOOL bRes = TRUE;
	if (m_pDisp != NULL) 
	{
		DISPPARAMS params = {NULL, NULL, 0, 0};
		m_pDisp->Invoke(m_iFuncTerminate, IID_NULL, 0, DISPATCH_METHOD, &params, NULL, NULL, NULL);
		m_pDisp->Release();
		//m_pDisp = NULL;
	}
	else
	{
		RemoveAllMsg();
	}
	return bRes;
}

BOOL CCOMImport::DoMethod(const char* pFuncName, const char* pFuncParam, char** ppRetVal)
{
	int iRes = -1;
	char *pRetBuff = NULL;
	VARIANT* varArrParams = new VARIANT[2];
	VARIANT varResult;
	BSTR bstr1 = NULL, bstr2 = NULL;
	HRESULT hr;


	if (pFuncName != NULL)
		bstr1 = CMemUtils::MEM_AnsiToBSTR(pFuncName);
	CMemUtils::MEM_CopyBstrToVariant(&(varArrParams[1]), bstr1);
	if (pFuncParam != NULL)
		bstr2 = CMemUtils::MEM_AnsiToBSTR(pFuncParam);
	CMemUtils::MEM_CopyBstrToVariant(&(varArrParams[0]), bstr2);
	DISPPARAMS params = {varArrParams, NULL, 2, 0};
	hr = m_pDisp->Invoke(m_iFuncDoMethodW, IID_NULL, 0, DISPATCH_METHOD, &params, &varResult, NULL, NULL);

	if (bstr1 != NULL)
	{
		SysFreeString(bstr1);
		V_BSTR(&(varArrParams[0])) = NULL;
	}
	if (bstr2 != NULL)
	{
		SysFreeString(bstr2);
		V_BSTR(&(varArrParams[1])) = NULL;
	}
	VariantClear(&(varArrParams[0]));
	VariantClear(&(varArrParams[1]));
	delete []varArrParams;
	bstr1 = V_BSTR(&varResult);
	if (ppRetVal != NULL)
		(*ppRetVal) = CMemUtils::MEM_BSTRToAnsi(bstr1);
	if (bstr1 != NULL)
	{
		::SysFreeString(bstr1);
		V_BSTR(&varResult) = NULL;
	}
	if (V_VT(&varResult) != VT_EMPTY)
		VariantClear(&varResult);
	return iRes;
}

BOOL CCOMImport::SetData(const char* pDataBuff)
{
	// Необходимо сохранить данные, пришедшие от сервера(pDataBuff)
	//............................................................
	int iDataLen = (int)strlen(pDataBuff) + 1;
	
	if (iDataLen > 1)
		if (m_pDataBuff != NULL)
		{
			char *strTmp;
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

BOOL CCOMImport::AddMsg(sctDllExchangeBuff* psctDllMsg)
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

sctDllExchangeBuff* CCOMImport::GetMsg(enDllMsgDirectionType iDllMsgDirection, enDllMsgType iDllMsgType, BOOL bRemoveMsg)
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

sctDllExchangeBuff* CCOMImport::GetMsg(BOOL bRemoveMsg)
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

BOOL CCOMImport::RemoveAllMsg()
{
	int i, iCount;
	sctDllExchangeBuff* psctDllMsg;
	EnterCriticalSection(&(m_pStartParams->csDllMsg));
	__try 
	{
		iCount = m_lstDllsMsgs.GetCount();
		if (iCount > 0)
		{
			for (i = 0; i < iCount; i++)
			{
				psctDllMsg = m_lstDllsMsgs.GetHead(); 
				m_lstDllsMsgs.RemoveHead();
				sctDllExchangeBuff::FreeExchangeBuff(&psctDllMsg, TRUE, TRUE, TRUE);
			}
		}
		}
	__finally 
	{
		;
	}
	LeaveCriticalSection(&(m_pStartParams->csDllMsg));
	return TRUE;
}


STDMETHODIMP CCOMImport::RaiseEvent(BSTR pEventName, BSTR pEventParam)
{
	char *strEventName = NULL, *strEventParam = NULL;

	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (pEventName != NULL)
	{
		strEventName = CMemUtils::MEM_BSTRToAnsi(pEventName);
		::SysFreeString(pEventName);
	}
	if (pEventParam != NULL)
	{
		strEventParam = CMemUtils::MEM_BSTRToAnsi(pEventParam);
		::SysFreeString(pEventParam);
	}
	m_pStartParams->pFuncRaiseEvent((void *)m_pStartParams, strEventName, strEventParam);
	if (strEventName != NULL)
		delete strEventName;
	if (strEventParam != NULL)
		delete strEventParam;
	return S_OK;
}

STDMETHODIMP CCOMImport::GetData(BSTR *ppRetVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (ppRetVal != NULL)
	{
		(*ppRetVal) = NULL;
		if (m_pDataBuff != NULL)
		{
			(*ppRetVal) = CMemUtils::MEM_AnsiToBSTR(m_pDataBuff);
			delete m_pDataBuff;
			m_pDataBuff = NULL;
		}
	}
	return S_OK;
}
