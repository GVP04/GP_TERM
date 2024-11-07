

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0499 */
/* at Tue Jan 08 22:15:29 2008
 */
/* Compiler settings for .\GP_Term.odl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __GP_Term_i_h__
#define __GP_Term_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IGP_Term_FWD_DEFINED__
#define __IGP_Term_FWD_DEFINED__
typedef interface IGP_Term IGP_Term;
#endif 	/* __IGP_Term_FWD_DEFINED__ */


#ifndef __IGPTInterface_FWD_DEFINED__
#define __IGPTInterface_FWD_DEFINED__
typedef interface IGPTInterface IGPTInterface;
#endif 	/* __IGPTInterface_FWD_DEFINED__ */


#ifndef __Document_FWD_DEFINED__
#define __Document_FWD_DEFINED__

#ifdef __cplusplus
typedef class Document Document;
#else
typedef struct Document Document;
#endif /* __cplusplus */

#endif 	/* __Document_FWD_DEFINED__ */


#ifndef __IMSFlexGridSink_FWD_DEFINED__
#define __IMSFlexGridSink_FWD_DEFINED__
typedef interface IMSFlexGridSink IMSFlexGridSink;
#endif 	/* __IMSFlexGridSink_FWD_DEFINED__ */


#ifndef __MSFlexGridSink_FWD_DEFINED__
#define __MSFlexGridSink_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSFlexGridSink MSFlexGridSink;
#else
typedef struct MSFlexGridSink MSFlexGridSink;
#endif /* __cplusplus */

#endif 	/* __MSFlexGridSink_FWD_DEFINED__ */


#ifndef __IWebBrowser2Sink_FWD_DEFINED__
#define __IWebBrowser2Sink_FWD_DEFINED__
typedef interface IWebBrowser2Sink IWebBrowser2Sink;
#endif 	/* __IWebBrowser2Sink_FWD_DEFINED__ */


#ifndef __WebBrowser2Sink_FWD_DEFINED__
#define __WebBrowser2Sink_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebBrowser2Sink WebBrowser2Sink;
#else
typedef struct WebBrowser2Sink WebBrowser2Sink;
#endif /* __cplusplus */

#endif 	/* __WebBrowser2Sink_FWD_DEFINED__ */


#ifndef ___IGPTInterfaceEvents_FWD_DEFINED__
#define ___IGPTInterfaceEvents_FWD_DEFINED__
typedef interface _IGPTInterfaceEvents _IGPTInterfaceEvents;
#endif 	/* ___IGPTInterfaceEvents_FWD_DEFINED__ */


#ifndef __IAutoSizing_FWD_DEFINED__
#define __IAutoSizing_FWD_DEFINED__
typedef interface IAutoSizing IAutoSizing;
#endif 	/* __IAutoSizing_FWD_DEFINED__ */


#ifndef __GPTInterface_FWD_DEFINED__
#define __GPTInterface_FWD_DEFINED__

#ifdef __cplusplus
typedef class GPTInterface GPTInterface;
#else
typedef struct GPTInterface GPTInterface;
#endif /* __cplusplus */

#endif 	/* __GPTInterface_FWD_DEFINED__ */


#ifndef ___IAutoSizingEvents_FWD_DEFINED__
#define ___IAutoSizingEvents_FWD_DEFINED__
typedef interface _IAutoSizingEvents _IAutoSizingEvents;
#endif 	/* ___IAutoSizingEvents_FWD_DEFINED__ */


#ifndef __IConnector_FWD_DEFINED__
#define __IConnector_FWD_DEFINED__
typedef interface IConnector IConnector;
#endif 	/* __IConnector_FWD_DEFINED__ */


#ifndef __ICOMImport_FWD_DEFINED__
#define __ICOMImport_FWD_DEFINED__
typedef interface ICOMImport ICOMImport;
#endif 	/* __ICOMImport_FWD_DEFINED__ */


#ifndef __AutoSizing_FWD_DEFINED__
#define __AutoSizing_FWD_DEFINED__

#ifdef __cplusplus
typedef class AutoSizing AutoSizing;
#else
typedef struct AutoSizing AutoSizing;
#endif /* __cplusplus */

#endif 	/* __AutoSizing_FWD_DEFINED__ */


#ifndef __Connector_FWD_DEFINED__
#define __Connector_FWD_DEFINED__

#ifdef __cplusplus
typedef class Connector Connector;
#else
typedef struct Connector Connector;
#endif /* __cplusplus */

#endif 	/* __Connector_FWD_DEFINED__ */


#ifndef __COMImport_FWD_DEFINED__
#define __COMImport_FWD_DEFINED__

#ifdef __cplusplus
typedef class COMImport COMImport;
#else
typedef struct COMImport COMImport;
#endif /* __cplusplus */

#endif 	/* __COMImport_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __GP_Term_LIBRARY_DEFINED__
#define __GP_Term_LIBRARY_DEFINED__

/* library GP_Term */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_GP_Term;

#ifndef __IGP_Term_DISPINTERFACE_DEFINED__
#define __IGP_Term_DISPINTERFACE_DEFINED__

/* dispinterface IGP_Term */
/* [uuid] */ 


EXTERN_C const IID DIID_IGP_Term;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("1509E7A8-DD4C-11D3-970D-0080AD863699")
    IGP_Term : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IGP_TermVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGP_Term * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGP_Term * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGP_Term * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IGP_Term * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IGP_Term * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IGP_Term * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IGP_Term * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IGP_TermVtbl;

    interface IGP_Term
    {
        CONST_VTBL struct IGP_TermVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGP_Term_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGP_Term_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGP_Term_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGP_Term_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IGP_Term_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IGP_Term_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IGP_Term_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IGP_Term_DISPINTERFACE_DEFINED__ */


#ifndef __IGPTInterface_INTERFACE_DEFINED__
#define __IGPTInterface_INTERFACE_DEFINED__

/* interface IGPTInterface */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IGPTInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1509E7E3-DD4C-11D3-970D-0080AD863699")
    IGPTInterface : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ArrayToString( 
            /* [in] */ VARIANT *iArray,
            BSTR *oString,
            /* [in] */ BSTR *DelimiterString) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StringToArray( 
            /* [in] */ BSTR *iString,
            VARIANT *oArray,
            /* [in] */ BSTR *DelimString) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConvertToPICK( 
            /* [out][in] */ BSTR *iString) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConvertFromPICK( 
            /* [out][in] */ BSTR *iString) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CountOccur( 
            /* [in] */ BSTR iString,
            /* [in] */ BSTR SubString,
            /* [out][in] */ long *COResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IndexSubString( 
            /* [in] */ BSTR iString,
            /* [in] */ BSTR SubString,
            /* [in] */ long Occurence,
            long *Position) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGPTInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGPTInterface * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGPTInterface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGPTInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IGPTInterface * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IGPTInterface * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IGPTInterface * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IGPTInterface * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ArrayToString )( 
            IGPTInterface * This,
            /* [in] */ VARIANT *iArray,
            BSTR *oString,
            /* [in] */ BSTR *DelimiterString);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StringToArray )( 
            IGPTInterface * This,
            /* [in] */ BSTR *iString,
            VARIANT *oArray,
            /* [in] */ BSTR *DelimString);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ConvertToPICK )( 
            IGPTInterface * This,
            /* [out][in] */ BSTR *iString);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ConvertFromPICK )( 
            IGPTInterface * This,
            /* [out][in] */ BSTR *iString);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CountOccur )( 
            IGPTInterface * This,
            /* [in] */ BSTR iString,
            /* [in] */ BSTR SubString,
            /* [out][in] */ long *COResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IndexSubString )( 
            IGPTInterface * This,
            /* [in] */ BSTR iString,
            /* [in] */ BSTR SubString,
            /* [in] */ long Occurence,
            long *Position);
        
        END_INTERFACE
    } IGPTInterfaceVtbl;

    interface IGPTInterface
    {
        CONST_VTBL struct IGPTInterfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGPTInterface_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGPTInterface_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGPTInterface_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGPTInterface_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IGPTInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IGPTInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IGPTInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IGPTInterface_ArrayToString(This,iArray,oString,DelimiterString)	\
    ( (This)->lpVtbl -> ArrayToString(This,iArray,oString,DelimiterString) ) 

#define IGPTInterface_StringToArray(This,iString,oArray,DelimString)	\
    ( (This)->lpVtbl -> StringToArray(This,iString,oArray,DelimString) ) 

#define IGPTInterface_ConvertToPICK(This,iString)	\
    ( (This)->lpVtbl -> ConvertToPICK(This,iString) ) 

#define IGPTInterface_ConvertFromPICK(This,iString)	\
    ( (This)->lpVtbl -> ConvertFromPICK(This,iString) ) 

#define IGPTInterface_CountOccur(This,iString,SubString,COResult)	\
    ( (This)->lpVtbl -> CountOccur(This,iString,SubString,COResult) ) 

#define IGPTInterface_IndexSubString(This,iString,SubString,Occurence,Position)	\
    ( (This)->lpVtbl -> IndexSubString(This,iString,SubString,Occurence,Position) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGPTInterface_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Document;

#ifdef __cplusplus

class DECLSPEC_UUID("1509E7A6-DD4C-11D3-970D-0080AD863699")
Document;
#endif

#ifndef __IMSFlexGridSink_DISPINTERFACE_DEFINED__
#define __IMSFlexGridSink_DISPINTERFACE_DEFINED__

/* dispinterface IMSFlexGridSink */
/* [uuid] */ 


EXTERN_C const IID DIID_IMSFlexGridSink;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("023F1A59-24CA-4585-BAD4-F1C8663A8938")
    IMSFlexGridSink : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IMSFlexGridSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMSFlexGridSink * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMSFlexGridSink * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMSFlexGridSink * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMSFlexGridSink * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMSFlexGridSink * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMSFlexGridSink * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMSFlexGridSink * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IMSFlexGridSinkVtbl;

    interface IMSFlexGridSink
    {
        CONST_VTBL struct IMSFlexGridSinkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMSFlexGridSink_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMSFlexGridSink_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMSFlexGridSink_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMSFlexGridSink_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMSFlexGridSink_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMSFlexGridSink_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMSFlexGridSink_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IMSFlexGridSink_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MSFlexGridSink;

#ifdef __cplusplus

class DECLSPEC_UUID("EC3F7A38-C5FA-4379-92FB-4DEE4B54A247")
MSFlexGridSink;
#endif

#ifndef __IWebBrowser2Sink_DISPINTERFACE_DEFINED__
#define __IWebBrowser2Sink_DISPINTERFACE_DEFINED__

/* dispinterface IWebBrowser2Sink */
/* [uuid] */ 


EXTERN_C const IID DIID_IWebBrowser2Sink;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("6B13E51E-75CF-4061-9250-4B2E65BE657F")
    IWebBrowser2Sink : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IWebBrowser2SinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWebBrowser2Sink * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWebBrowser2Sink * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWebBrowser2Sink * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWebBrowser2Sink * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWebBrowser2Sink * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWebBrowser2Sink * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWebBrowser2Sink * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IWebBrowser2SinkVtbl;

    interface IWebBrowser2Sink
    {
        CONST_VTBL struct IWebBrowser2SinkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebBrowser2Sink_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWebBrowser2Sink_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWebBrowser2Sink_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWebBrowser2Sink_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWebBrowser2Sink_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWebBrowser2Sink_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWebBrowser2Sink_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IWebBrowser2Sink_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WebBrowser2Sink;

#ifdef __cplusplus

class DECLSPEC_UUID("A772A6D7-1EFD-4CF5-925B-062BBB5DB75A")
WebBrowser2Sink;
#endif

#ifndef ___IGPTInterfaceEvents_DISPINTERFACE_DEFINED__
#define ___IGPTInterfaceEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IGPTInterfaceEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IGPTInterfaceEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("1509E7E5-DD4C-11D3-970D-0080AD863699")
    _IGPTInterfaceEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IGPTInterfaceEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IGPTInterfaceEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IGPTInterfaceEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IGPTInterfaceEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IGPTInterfaceEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IGPTInterfaceEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IGPTInterfaceEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IGPTInterfaceEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IGPTInterfaceEventsVtbl;

    interface _IGPTInterfaceEvents
    {
        CONST_VTBL struct _IGPTInterfaceEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IGPTInterfaceEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IGPTInterfaceEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IGPTInterfaceEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IGPTInterfaceEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IGPTInterfaceEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IGPTInterfaceEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IGPTInterfaceEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IGPTInterfaceEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IAutoSizing_INTERFACE_DEFINED__
#define __IAutoSizing_INTERFACE_DEFINED__

/* interface IAutoSizing */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAutoSizing;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("97DC5723-F341-11D3-970D-0080AD863699")
    IAutoSizing : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_nItem( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddWnd( 
            /* [in] */ /* external definition not present */ OLE_HANDLE ihWnd,
            /* [in] */ /* external definition not present */ OLE_HANDLE hWndMain,
            /* [in] */ BSTR iString) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddSetMain( 
            /* [in] */ /* external definition not present */ OLE_HANDLE ihWndMain) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteWnd( 
            /* [in] */ /* external definition not present */ OLE_HANDLE ihWnd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateSize( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMinPos( 
            /* [in] */ /* external definition not present */ OLE_HANDLE ihWnd,
            /* [in] */ long MinTop,
            /* [in] */ long MinLeft,
            /* [in] */ long MinBottom,
            /* [in] */ long MinRight) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMaxPos( 
            /* [in] */ /* external definition not present */ OLE_HANDLE ihWnd,
            /* [in] */ long MaxTop,
            /* [in] */ long MaxLeft,
            /* [in] */ long MaxBottom,
            /* [in] */ long MaxRight) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMaxSize( 
            /* [in] */ /* external definition not present */ OLE_HANDLE ihWnd,
            /* [in] */ long iMaxWidth,
            /* [in] */ long iMaxHeight) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMinSize( 
            /* [in] */ /* external definition not present */ OLE_HANDLE ihWnd,
            /* [in] */ long iMinWidth,
            /* [in] */ long iMinHeight) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetNewStyle( 
            /* [in] */ /* external definition not present */ OLE_HANDLE ihWnd,
            /* [in] */ BSTR NewStyle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReinitSize( 
            /* [in] */ /* external definition not present */ OLE_HANDLE ihWnd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetNewSize( 
            /* [in] */ /* external definition not present */ OLE_HANDLE ihWnd,
            /* [in] */ long Top,
            /* [in] */ long Left,
            /* [in] */ long Bottom,
            /* [in] */ long Right) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteWndEx( 
            /* [in] */ /* external definition not present */ OLE_HANDLE ihWnd,
            /* [in] */ /* external definition not present */ OLE_HANDLE ownerHWND) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AutoSizingPause( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AutoSizingResume( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReinitAll( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAutoSizingVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAutoSizing * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAutoSizing * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAutoSizing * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAutoSizing * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAutoSizing * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAutoSizing * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAutoSizing * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_nItem )( 
            IAutoSizing * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddWnd )( 
            IAutoSizing * This,
            /* [in] */ /* external definition not present */ OLE_HANDLE ihWnd,
            /* [in] */ /* external definition not present */ OLE_HANDLE hWndMain,
            /* [in] */ BSTR iString);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddSetMain )( 
            IAutoSizing * This,
            /* [in] */ /* external definition not present */ OLE_HANDLE ihWndMain);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteWnd )( 
            IAutoSizing * This,
            /* [in] */ /* external definition not present */ OLE_HANDLE ihWnd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IAutoSizing * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateSize )( 
            IAutoSizing * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetMinPos )( 
            IAutoSizing * This,
            /* [in] */ /* external definition not present */ OLE_HANDLE ihWnd,
            /* [in] */ long MinTop,
            /* [in] */ long MinLeft,
            /* [in] */ long MinBottom,
            /* [in] */ long MinRight);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetMaxPos )( 
            IAutoSizing * This,
            /* [in] */ /* external definition not present */ OLE_HANDLE ihWnd,
            /* [in] */ long MaxTop,
            /* [in] */ long MaxLeft,
            /* [in] */ long MaxBottom,
            /* [in] */ long MaxRight);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetMaxSize )( 
            IAutoSizing * This,
            /* [in] */ /* external definition not present */ OLE_HANDLE ihWnd,
            /* [in] */ long iMaxWidth,
            /* [in] */ long iMaxHeight);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetMinSize )( 
            IAutoSizing * This,
            /* [in] */ /* external definition not present */ OLE_HANDLE ihWnd,
            /* [in] */ long iMinWidth,
            /* [in] */ long iMinHeight);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetNewStyle )( 
            IAutoSizing * This,
            /* [in] */ /* external definition not present */ OLE_HANDLE ihWnd,
            /* [in] */ BSTR NewStyle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReinitSize )( 
            IAutoSizing * This,
            /* [in] */ /* external definition not present */ OLE_HANDLE ihWnd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetNewSize )( 
            IAutoSizing * This,
            /* [in] */ /* external definition not present */ OLE_HANDLE ihWnd,
            /* [in] */ long Top,
            /* [in] */ long Left,
            /* [in] */ long Bottom,
            /* [in] */ long Right);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteWndEx )( 
            IAutoSizing * This,
            /* [in] */ /* external definition not present */ OLE_HANDLE ihWnd,
            /* [in] */ /* external definition not present */ OLE_HANDLE ownerHWND);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AutoSizingPause )( 
            IAutoSizing * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AutoSizingResume )( 
            IAutoSizing * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReinitAll )( 
            IAutoSizing * This);
        
        END_INTERFACE
    } IAutoSizingVtbl;

    interface IAutoSizing
    {
        CONST_VTBL struct IAutoSizingVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAutoSizing_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAutoSizing_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAutoSizing_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAutoSizing_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAutoSizing_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAutoSizing_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAutoSizing_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IAutoSizing_get_nItem(This,pVal)	\
    ( (This)->lpVtbl -> get_nItem(This,pVal) ) 

#define IAutoSizing_AddWnd(This,ihWnd,hWndMain,iString)	\
    ( (This)->lpVtbl -> AddWnd(This,ihWnd,hWndMain,iString) ) 

#define IAutoSizing_AddSetMain(This,ihWndMain)	\
    ( (This)->lpVtbl -> AddSetMain(This,ihWndMain) ) 

#define IAutoSizing_DeleteWnd(This,ihWnd)	\
    ( (This)->lpVtbl -> DeleteWnd(This,ihWnd) ) 

#define IAutoSizing_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IAutoSizing_UpdateSize(This)	\
    ( (This)->lpVtbl -> UpdateSize(This) ) 

#define IAutoSizing_SetMinPos(This,ihWnd,MinTop,MinLeft,MinBottom,MinRight)	\
    ( (This)->lpVtbl -> SetMinPos(This,ihWnd,MinTop,MinLeft,MinBottom,MinRight) ) 

#define IAutoSizing_SetMaxPos(This,ihWnd,MaxTop,MaxLeft,MaxBottom,MaxRight)	\
    ( (This)->lpVtbl -> SetMaxPos(This,ihWnd,MaxTop,MaxLeft,MaxBottom,MaxRight) ) 

#define IAutoSizing_SetMaxSize(This,ihWnd,iMaxWidth,iMaxHeight)	\
    ( (This)->lpVtbl -> SetMaxSize(This,ihWnd,iMaxWidth,iMaxHeight) ) 

#define IAutoSizing_SetMinSize(This,ihWnd,iMinWidth,iMinHeight)	\
    ( (This)->lpVtbl -> SetMinSize(This,ihWnd,iMinWidth,iMinHeight) ) 

#define IAutoSizing_SetNewStyle(This,ihWnd,NewStyle)	\
    ( (This)->lpVtbl -> SetNewStyle(This,ihWnd,NewStyle) ) 

#define IAutoSizing_ReinitSize(This,ihWnd)	\
    ( (This)->lpVtbl -> ReinitSize(This,ihWnd) ) 

#define IAutoSizing_SetNewSize(This,ihWnd,Top,Left,Bottom,Right)	\
    ( (This)->lpVtbl -> SetNewSize(This,ihWnd,Top,Left,Bottom,Right) ) 

#define IAutoSizing_DeleteWndEx(This,ihWnd,ownerHWND)	\
    ( (This)->lpVtbl -> DeleteWndEx(This,ihWnd,ownerHWND) ) 

#define IAutoSizing_AutoSizingPause(This)	\
    ( (This)->lpVtbl -> AutoSizingPause(This) ) 

#define IAutoSizing_AutoSizingResume(This)	\
    ( (This)->lpVtbl -> AutoSizingResume(This) ) 

#define IAutoSizing_ReinitAll(This)	\
    ( (This)->lpVtbl -> ReinitAll(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAutoSizing_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_GPTInterface;

#ifdef __cplusplus

class DECLSPEC_UUID("1509E7E4-DD4C-11D3-970D-0080AD863699")
GPTInterface;
#endif

#ifndef ___IAutoSizingEvents_DISPINTERFACE_DEFINED__
#define ___IAutoSizingEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IAutoSizingEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IAutoSizingEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("97DC5725-F341-11D3-970D-0080AD863699")
    _IAutoSizingEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IAutoSizingEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IAutoSizingEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IAutoSizingEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IAutoSizingEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IAutoSizingEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IAutoSizingEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IAutoSizingEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IAutoSizingEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IAutoSizingEventsVtbl;

    interface _IAutoSizingEvents
    {
        CONST_VTBL struct _IAutoSizingEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IAutoSizingEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IAutoSizingEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IAutoSizingEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IAutoSizingEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IAutoSizingEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IAutoSizingEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IAutoSizingEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IAutoSizingEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IConnector_INTERFACE_DEFINED__
#define __IConnector_INTERFACE_DEFINED__

/* interface IConnector */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IConnector;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7633D795-5289-4E2E-9652-D4EB8E2CB009")
    IConnector : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTerminal( 
            /* [in] */ BSTR *iStr,
            /* [retval][out] */ LPDISPATCH *ppDisp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IConnectorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IConnector * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IConnector * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IConnector * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IConnector * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IConnector * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IConnector * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IConnector * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTerminal )( 
            IConnector * This,
            /* [in] */ BSTR *iStr,
            /* [retval][out] */ LPDISPATCH *ppDisp);
        
        END_INTERFACE
    } IConnectorVtbl;

    interface IConnector
    {
        CONST_VTBL struct IConnectorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IConnector_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IConnector_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IConnector_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IConnector_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IConnector_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IConnector_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IConnector_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IConnector_GetTerminal(This,iStr,ppDisp)	\
    ( (This)->lpVtbl -> GetTerminal(This,iStr,ppDisp) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IConnector_INTERFACE_DEFINED__ */


#ifndef __ICOMImport_INTERFACE_DEFINED__
#define __ICOMImport_INTERFACE_DEFINED__

/* interface ICOMImport */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICOMImport;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DCCFE5DA-4873-4C23-AB69-5E4DBF1792C6")
    ICOMImport : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ICOMImportVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICOMImport * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICOMImport * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICOMImport * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICOMImport * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICOMImport * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICOMImport * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICOMImport * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } ICOMImportVtbl;

    interface ICOMImport
    {
        CONST_VTBL struct ICOMImportVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICOMImport_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICOMImport_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICOMImport_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICOMImport_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICOMImport_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICOMImport_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICOMImport_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICOMImport_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_AutoSizing;

#ifdef __cplusplus

class DECLSPEC_UUID("97DC5724-F341-11D3-970D-0080AD863699")
AutoSizing;
#endif

EXTERN_C const CLSID CLSID_Connector;

#ifdef __cplusplus

class DECLSPEC_UUID("213787A1-BDFC-424A-A8E5-2319ABA9E25D")
Connector;
#endif

EXTERN_C const CLSID CLSID_COMImport;

#ifdef __cplusplus

class DECLSPEC_UUID("1FC4AF30-8426-4C47-A9A7-839204386C5E")
COMImport;
#endif
#endif /* __GP_Term_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


