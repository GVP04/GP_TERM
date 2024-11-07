// AutoSizing.h : Declaration of the CAutoSizing

#ifndef __AUTOSIZING_H_
#define __AUTOSIZING_H_

#include "resource.h"       // main symbols
#include "GP_AutoSizing.h"

/////////////////////////////////////////////////////////////////////////////
// CAutoSizing

class ATL_NO_VTABLE CAutoSizing : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAutoSizing, &CLSID_AutoSizing>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CAutoSizing>,
	public IDispatchImpl<IAutoSizing, &IID_IAutoSizing, &LIBID_GP_Term>
{
public:
	CAutoSizing()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_AUTOSIZING)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAutoSizing)
	COM_INTERFACE_ENTRY(IAutoSizing)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CAutoSizing)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IAutoSizing
public:
	STDMETHOD(ReinitAll)();
	STDMETHOD(AutoSizingResume)();
	STDMETHOD(AutoSizingPause)();
	STDMETHOD(DeleteWndEx)(OLE_HANDLE ihWnd,OLE_HANDLE ownerHWND);
	STDMETHOD(SetNewSize)(OLE_HANDLE ihWnd, long Top, long Left, long Bottom, long Right);
	STDMETHOD(ReinitSize)(OLE_HANDLE ihWnd);
	STDMETHOD(SetNewStyle)(OLE_HANDLE ihWnd, BSTR NewStyle);
	STDMETHOD(SetMinSize)(OLE_HANDLE ihWnd, long iMinWidth, long iMinHeight);
	STDMETHOD(SetMaxSize)(OLE_HANDLE ihWnd, long iMaxWidth, long iMaxHeight);
	STDMETHOD(SetMaxPos)(OLE_HANDLE ihWnd, long MaxTop, long MaxLeft, long MaxBottom, long MaxRight);
	STDMETHOD(SetMinPos)(OLE_HANDLE ihWnd, long MinTop, long MinLeft, long MinBottom, long MinRight);
	STDMETHOD(UpdateSize)();
	STDMETHOD(Reset)();
	STDMETHOD(DeleteWnd)(OLE_HANDLE ihWnd);
	STDMETHOD(AddSetMain)(OLE_HANDLE ihWndMain);
	STDMETHOD(AddWnd)(OLE_HANDLE ihWnd, OLE_HANDLE hWndMain, BSTR iString);
	STDMETHOD(get_nItem)(/*[out, retval]*/ long *pVal);
private:
	GP_AutoSizing ASizingClass;
	};

#endif //__AUTOSIZING_H_
