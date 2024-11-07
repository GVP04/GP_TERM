/// Connector.cpp : Implementation of CConnector
#include "stdafx.h"
#include "GP_Term.h"
#include "Connector.h"
#include  <io.h>
#include  <stdio.h>
#include  <stdlib.h>

/////////////////////////////////////////////////////////////////////////////
// CConnector
BOOL GetTerminalEx(BSTR iStr, LPDISPATCH *ppDisp)
{
	BOOL ret=FALSE;

	IMoniker* pmon;
	IBindCtx* pBind;
	IRunningObjectTable* prot;
	HRESULT hr;
	LPUNKNOWN pUnk;
	LPDISPATCH pDisp=NULL;
	LPOLESTR pName;
	IEnumMoniker *pem;


	hr=::CreateBindCtx(0,&pBind);
	if (SUCCEEDED(hr))
	{
		hr = pBind->GetRunningObjectTable (&prot);
		if (SUCCEEDED(hr))
		{
		    hr = prot->EnumRunning(&pem);
			if (SUCCEEDED(hr))
			{
				pem->Reset();

				 // Churn through enumeration.
				ULONG fetched;
				while(pem->Next(1, &pmon, &fetched) == S_OK && !ret)
				{
					// Get DisplayName.
					hr=pmon->GetDisplayName(pBind, NULL, &pName);
					if (!wcscmp(iStr,pName))
					{
						hr=prot->GetObject(pmon,&pUnk);
						if (SUCCEEDED(hr))
						{
							hr=pUnk->QueryInterface(IID_IDispatch,(void**)&pDisp);
							pUnk->Release();
							ret=TRUE;
						}
					}
					pmon->Release();
				}
				pem->Release();
			}
			prot->Release();
		}
		pBind->Release();
	}
	*ppDisp=pDisp;

	return ret;
}

STDMETHODIMP CConnector::GetTerminal(BSTR* iStr, LPDISPATCH *ppDisp)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CString csTmp(*iStr);
	CString csRegName=ExtractField(ExtractField(csTmp,1,";"),1,",");
	const char *pCmd=FindField(csTmp,2,";");
	CString csCmdLine=pCmd?pCmd:"";
	char *byteData=NULL;
#ifdef BRIZ
	if (csRegName=="") csRegName.Format("BRIZ%X",(DWORD)AfxGetInstanceHandle());
#else
	if (csRegName=="") csRegName.Format("GP_TERM%X",(DWORD)AfxGetInstanceHandle());
#endif

	BSTR bstName=csRegName.AllocSysString();
	if (csRegName=="" || !GetTerminalEx(bstName, ppDisp))
	{
		char *tmps=new char [csRegName.GetLength()+csCmdLine.GetLength()+500];
		try
		{
			SHELLEXECUTEINFO ExecInfo={0};
			ExecInfo.cbSize=sizeof(ExecInfo);
			ExecInfo.fMask=SEE_MASK_FLAG_DDEWAIT|SEE_MASK_FLAG_NO_UI;
			ExecInfo.lpVerb="open";
			HKEY m_HKEY=NULL;
			if (::RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Classes\\CLSID\\{213787A1-BDFC-424A-A8E5-2319ABA9E25D}\\LocalServer32",0,KEY_READ,&m_HKEY)==ERROR_SUCCESS || m_HKEY)
			{
				DWORD cbData;
				DWORD Type;
				if (RegQueryValueEx(m_HKEY,"",NULL,&Type,(BYTE *)byteData,&cbData)==ERROR_SUCCESS)
				{
					byteData=new char [2*cbData+100];
					if (RegQueryValueEx(m_HKEY,"",NULL,&Type,(BYTE *)byteData,&cbData)==ERROR_SUCCESS)
					{
						byteData[cbData]=0;
						ExecInfo.lpFile=byteData;
					}
				}
			}
			if (csRegName=="")
			{
				SYSTEMTIME st={0};
				GetSystemTime(&st);
				csRegName.Format("%d_%d_%d_%d",st.wYear,st.wMonth,st.wDay,st.wMilliseconds);
			}

			sprintf(tmps,"-REGTERM%s %s",(LPCSTR)csRegName,(LPCSTR)csCmdLine);
			ExecInfo.lpParameters=tmps;
			if (ExecInfo.lpFile && ::ShellExecuteEx(&ExecInfo))
			{
				int i=0;
				do
					Sleep(50);
				while(++i<200 && !GetTerminalEx(bstName, ppDisp));
			}
		}
		catch(...){;}
		delete []tmps;
	}


	if (byteData) delete [] byteData;
	::SysFreeString(bstName);
	return S_OK;
}

