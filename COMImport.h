// COMImport.h : Declaration of the CCOMImport

#ifndef __COMIMPORT_H_
#define __COMIMPORT_H_

#include "resource.h"       // main symbols
#include "DLLImport.h"
#include "MemUtils.h"

/////////////////////////////////////////////////////////////////////////////
// CCOMImport
class ATL_NO_VTABLE CCOMImport : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCOMImport, &CLSID_COMImport>,
	public IDispatchImpl<ICOMImport, &IID_ICOMImport, &LIBID_GP_Term>
{
public:

DECLARE_REGISTRY_RESOURCEID(IDR_COMIMPORT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCOMImport)
	COM_INTERFACE_ENTRY(ICOMImport)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ICOMImport
public:
	STDMETHOD(GetData)(/*[out, retval]*/BSTR *ppRetVal);
	STDMETHOD(RaiseEvent)(BSTR pEventName, BSTR pEventParam);
	CCOMImport();
	virtual ~CCOMImport();
	BOOL Load(sctDllStartParams* pDllStartParams);
	BOOL Unload();
	BOOL DoMethod(const char* pFuncName, const char* pFuncParam, char** ppRetVal);
	BOOL SetData(const char* pDataBuff);
	BOOL AddMsg(sctDllExchangeBuff* psctDllMsg);
	sctDllExchangeBuff* GetMsg(BOOL bRemoveMsg);
	sctDllExchangeBuff* GetMsg(enDllMsgDirectionType iDllMsgDirection, enDllMsgType iDllMsgType, BOOL bRemoveMsg);
	BOOL RemoveAllMsg();
private:
	CList<sctDllExchangeBuff*,sctDllExchangeBuff*> m_lstDllsMsgs;
	sctDllStartParams* m_pStartParams;
	IDispatch *m_pDisp; 
	DISPID m_iFuncInit;
	DISPID m_iFuncTerminate;
	DISPID m_iFuncDoMethodW;
	char *m_pDataBuff;
	CLSID m_clsidCOM;
};

#endif //__COMIMPORT_H_
