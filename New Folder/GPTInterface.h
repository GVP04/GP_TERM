	
// GPTInterface.h : Declaration of the CGPTInterface

#ifndef __GPTINTERFACE_H_
#define __GPTINTERFACE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGPTInterface
class ATL_NO_VTABLE CGPTInterface : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CGPTInterface, &CLSID_GPTInterface>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CGPTInterface>,
	public IDispatchImpl<IGPTInterface, &IID_IGPTInterface, &LIBID_GP_Term>
{
public:
	CGPTInterface()
	{
		m_pUnkMarshaler = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_GPTINTERFACE)
DECLARE_GET_CONTROLLING_UNKNOWN()

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CGPTInterface)
	COM_INTERFACE_ENTRY(IGPTInterface)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CGPTInterface)
END_CONNECTION_POINT_MAP()


	HRESULT FinalConstruct()
	{
		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

	void FinalRelease()
	{
		m_pUnkMarshaler.Release();
	}

	CComPtr<IUnknown> m_pUnkMarshaler;

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IGPTInterface
public:
	STDMETHOD(IndexSubString)(BSTR iString, BSTR SubString, long Occurence, long * Position);
	STDMETHOD(CountOccur)(BSTR iString, BSTR SubString, long * Result);
	STDMETHOD(ConvertFromPICK)(BSTR *iString);
	STDMETHOD(ConvertToPICK)(BSTR *iString);
	STDMETHOD(StringToArray)(BSTR *iString, VARIANT *oArray, BSTR *DelimString);
	STDMETHOD(ArrayToString)(VARIANT* iArray, BSTR* oString, BSTR* DelimiterString);
};

#endif //__GPTINTERFACE_H_
