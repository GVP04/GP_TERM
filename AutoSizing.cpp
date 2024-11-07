// AutoSizing.cpp : Implementation of CAutoSizing
#include "stdafx.h"
#include "GP_Term.h"
#include "AutoSizing.h"

/////////////////////////////////////////////////////////////////////////////
// CAutoSizing

STDMETHODIMP CAutoSizing::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] =
	{
		&IID_IAutoSizing
	};
	int i;
	for(i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CAutoSizing::get_nItem(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal=ASizingClass.GetItemCount();
	return S_OK;
}

STDMETHODIMP CAutoSizing::AddWnd(OLE_HANDLE ihWnd, OLE_HANDLE hWndMain, BSTR iString)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CString tmp(iString);
	tmp.MakeUpper();

	ASizingClass.AddWnd((HWND)ihWnd, (HWND)hWndMain,(LPCTSTR)tmp);

	return S_OK;
}

STDMETHODIMP CAutoSizing::AddSetMain(OLE_HANDLE ihWndMain)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASizingClass.AddSetMain((HWND)ihWndMain);
	return S_OK;
}

STDMETHODIMP CAutoSizing::DeleteWnd(OLE_HANDLE ihWnd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASizingClass.DeleteWnd((HWND)ihWnd);
	return S_OK;
}

STDMETHODIMP CAutoSizing::Reset()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASizingClass.Reset();
	return S_OK;
}

STDMETHODIMP CAutoSizing::SetMinPos(OLE_HANDLE ihWnd, long MinTop, long MinLeft, long MinBottom, long MinRight)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASizingClass.SetMinPos((HWND)ihWnd, MinTop, MinLeft, MinBottom, MinRight);
	return S_OK;
}

STDMETHODIMP CAutoSizing::SetMaxPos(OLE_HANDLE ihWnd, long MaxTop, long MaxLeft, long MaxBottom, long MaxRight)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASizingClass.SetMinPos((HWND)ihWnd, MaxTop, MaxLeft, MaxBottom, MaxRight);
	return S_OK;
}

STDMETHODIMP CAutoSizing::UpdateSize()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASizingClass.UpdateSize();

	return S_OK;
}

STDMETHODIMP CAutoSizing::SetMaxSize(OLE_HANDLE ihWnd, long iMaxWidth, long iMaxHeight)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASizingClass.SetMaxSize((HWND)ihWnd, iMaxWidth, iMaxHeight);
	return S_OK;
}

STDMETHODIMP CAutoSizing::SetMinSize(OLE_HANDLE ihWnd, long iMinWidth, long iMinHeight)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASizingClass.SetMinSize((HWND)ihWnd, iMinWidth, iMinHeight);
	return S_OK;
}

STDMETHODIMP CAutoSizing::SetNewStyle(OLE_HANDLE ihWnd, BSTR NewStyle)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CString tmp(NewStyle);
	tmp.MakeUpper();
	ASizingClass.SetNewStyle((HWND)ihWnd,(LPCTSTR)tmp);
	return S_OK;
}

STDMETHODIMP CAutoSizing::ReinitSize(OLE_HANDLE ihWnd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASizingClass.ReinitSize((HWND)ihWnd);
	return S_OK;
}

STDMETHODIMP CAutoSizing::SetNewSize(OLE_HANDLE ihWnd, long Top, long Left, long Bottom, long Right)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASizingClass.SetNewSize((HWND)ihWnd,CRect( Top, Left, Bottom, Right));

	return S_OK;
}

STDMETHODIMP CAutoSizing::DeleteWndEx(OLE_HANDLE ihWnd, OLE_HANDLE ownerHWND)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASizingClass.DeleteWndEx((HWND)ihWnd,(HWND)ownerHWND);
	return S_OK;
}

STDMETHODIMP CAutoSizing::AutoSizingPause()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASizingClass.AutoSizingPause();

	return S_OK;
}

STDMETHODIMP CAutoSizing::AutoSizingResume()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASizingClass.AutoSizingResume();

	return S_OK;
}

STDMETHODIMP CAutoSizing::ReinitAll()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASizingClass.ReinitSize();

	return S_OK;
}
