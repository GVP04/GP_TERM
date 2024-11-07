// GPTInterface.cpp : Implementation of CGPTInterface
#include "stdafx.h"
#include "GP_Term.h"
#include "GPTInterface.h"
#include "GP_TermDoc.h"
#include "GP_TermView.h"

/////////////////////////////////////////////////////////////////////////////
// CGPTInterface


STDMETHODIMP CGPTInterface::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IGPTInterface
	};
	int i;
	for(i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CGPTInterface::ArrayToString(VARIANT *iArray, BSTR *oString, BSTR *DelimiterString)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CString oStr;
	long ret=-1;
	CString dStr((LPCWSTR)*DelimiterString);
	ret=ConvertToString(iArray,oStr,dStr);
	oStr.SetSysString(oString);

	return S_OK;
}

STDMETHODIMP CGPTInterface::StringToArray(BSTR *iString, VARIANT *oArray, BSTR *DelimString)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 	long ret=-1;
 
 	CString dStr((LPCWSTR)*DelimString);
 	CString iTmp((LPCWSTR)*iString);
 
 	ret=ConvertToArray(iTmp,oArray,dStr,1);

	return S_OK;
}

STDMETHODIMP CGPTInterface::ConvertToPICK(BSTR *iString)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (iString!=NULL && *iString!=NULL)
	{
		CString dStr((LPCWSTR)*iString);
//		dStr.AnsiToOem();
		AnsiToDos((LPCTSTR)dStr,dStr,1);
		dStr.SetSysString(iString);
	}

	return S_OK;
}

STDMETHODIMP CGPTInterface::ConvertFromPICK(BSTR *iString)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 	if (iString!=NULL && *iString!=NULL)
 	{
 		CString dStr((LPCWSTR)*iString);
		DosToAnsi((LPCTSTR)dStr,dStr);
 //		dStr.OemToAnsi();
 		dStr.SetSysString(iString);
 	}

/*	if (GPC.m_Document==NULL)
	{
		CCommandLineInfo cmdInfo;
		AfxGetApp()->ParseCommandLine(cmdInfo);
		cmdInfo.m_strFileName="";
		cmdInfo.m_strDriverName="";
		cmdInfo.m_strPortName="";
		cmdInfo.m_strPrinterName="";
		cmdInfo.m_bShowSplash=0;
		cmdInfo.m_bRunAutomated=0;
		cmdInfo.m_bRunEmbedded=0;
		cmdInfo.m_nShellCommand=CCommandLineInfo::FileNew;

		AfxGetApp()->ProcessShellCommand(cmdInfo);
		((CGP_TermDoc*)GPC.m_Document)->GPOLETermShow(1);

	}
*/
	return S_OK;
}


STDMETHODIMP CGPTInterface::CountOccur(BSTR iString, BSTR SubString, long * Result)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*Result=CountOccurence(iString,SubString);
	return S_OK;
}

STDMETHODIMP CGPTInterface::IndexSubString(BSTR iString, BSTR SubString, long Occurence, long *Position)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*Position=GetIndexSubString(iString, SubString, Occurence);

	return S_OK;
}

