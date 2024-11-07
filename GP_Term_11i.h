

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Tue May 30 16:35:49 2006
 */
/* Compiler settings for C:\myprojects\GP_TERM\GP_Term.odl:
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


#ifndef __IGP_RTF_FWD_DEFINED__
#define __IGP_RTF_FWD_DEFINED__
typedef interface IGP_RTF IGP_RTF;
#endif 	/* __IGP_RTF_FWD_DEFINED__ */


#ifndef __GPRTF_FWD_DEFINED__
#define __GPRTF_FWD_DEFINED__

#ifdef __cplusplus
typedef class GPRTF GPRTF;
#else
typedef struct GPRTF GPRTF;
#endif /* __cplusplus */

#endif 	/* __GPRTF_FWD_DEFINED__ */


#ifndef __IGPDrawWnd_FWD_DEFINED__
#define __IGPDrawWnd_FWD_DEFINED__
typedef interface IGPDrawWnd IGPDrawWnd;
#endif 	/* __IGPDrawWnd_FWD_DEFINED__ */


#ifndef __GPDrawWnd_FWD_DEFINED__
#define __GPDrawWnd_FWD_DEFINED__

#ifdef __cplusplus
typedef class GPDrawWnd GPDrawWnd;
#else
typedef struct GPDrawWnd GPDrawWnd;
#endif /* __cplusplus */

#endif 	/* __GPDrawWnd_FWD_DEFINED__ */


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


#ifndef __ICDlgClientFiles_FWD_DEFINED__
#define __ICDlgClientFiles_FWD_DEFINED__
typedef interface ICDlgClientFiles ICDlgClientFiles;
#endif 	/* __ICDlgClientFiles_FWD_DEFINED__ */


#ifndef __CDlgClientFiles_FWD_DEFINED__
#define __CDlgClientFiles_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgClientFiles CDlgClientFiles;
#else
typedef struct CDlgClientFiles CDlgClientFiles;
#endif /* __cplusplus */

#endif 	/* __CDlgClientFiles_FWD_DEFINED__ */


#ifndef __IDlgProject_FWD_DEFINED__
#define __IDlgProject_FWD_DEFINED__
typedef interface IDlgProject IDlgProject;
#endif 	/* __IDlgProject_FWD_DEFINED__ */


#ifndef __DlgProject_FWD_DEFINED__
#define __DlgProject_FWD_DEFINED__

#ifdef __cplusplus
typedef class DlgProject DlgProject;
#else
typedef struct DlgProject DlgProject;
#endif /* __cplusplus */

#endif 	/* __DlgProject_FWD_DEFINED__ */


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


/* header files for imported files */
#include "oaidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


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
            /* [iid_is][out] */ void **ppvObject);
        
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
            /* [in] */ UINT cNames,
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
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGP_Term_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGP_Term_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGP_Term_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IGP_Term_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IGP_Term_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IGP_Term_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

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
            VARIANT *iArray,
            BSTR *oString,
            BSTR *DelimiterString) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StringToArray( 
            BSTR *iString,
            VARIANT *oArray,
            BSTR *DelimString) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConvertToPICK( 
            BSTR *iString) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConvertFromPICK( 
            BSTR *iString) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CountOccur( 
            BSTR iString,
            BSTR SubString,
            long *Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IndexSubString( 
            BSTR iString,
            BSTR SubString,
            long Occurence,
            long *Position) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGPTInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGPTInterface * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
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
            /* [in] */ UINT cNames,
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
            VARIANT *iArray,
            BSTR *oString,
            BSTR *DelimiterString);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StringToArray )( 
            IGPTInterface * This,
            BSTR *iString,
            VARIANT *oArray,
            BSTR *DelimString);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ConvertToPICK )( 
            IGPTInterface * This,
            BSTR *iString);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ConvertFromPICK )( 
            IGPTInterface * This,
            BSTR *iString);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CountOccur )( 
            IGPTInterface * This,
            BSTR iString,
            BSTR SubString,
            long *Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IndexSubString )( 
            IGPTInterface * This,
            BSTR iString,
            BSTR SubString,
            long Occurence,
            long *Position);
        
        END_INTERFACE
    } IGPTInterfaceVtbl;

    interface IGPTInterface
    {
        CONST_VTBL struct IGPTInterfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGPTInterface_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGPTInterface_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGPTInterface_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGPTInterface_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IGPTInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IGPTInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IGPTInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IGPTInterface_ArrayToString(This,iArray,oString,DelimiterString)	\
    (This)->lpVtbl -> ArrayToString(This,iArray,oString,DelimiterString)

#define IGPTInterface_StringToArray(This,iString,oArray,DelimString)	\
    (This)->lpVtbl -> StringToArray(This,iString,oArray,DelimString)

#define IGPTInterface_ConvertToPICK(This,iString)	\
    (This)->lpVtbl -> ConvertToPICK(This,iString)

#define IGPTInterface_ConvertFromPICK(This,iString)	\
    (This)->lpVtbl -> ConvertFromPICK(This,iString)

#define IGPTInterface_CountOccur(This,iString,SubString,Result)	\
    (This)->lpVtbl -> CountOccur(This,iString,SubString,Result)

#define IGPTInterface_IndexSubString(This,iString,SubString,Occurence,Position)	\
    (This)->lpVtbl -> IndexSubString(This,iString,SubString,Occurence,Position)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGPTInterface_ArrayToString_Proxy( 
    IGPTInterface * This,
    VARIANT *iArray,
    BSTR *oString,
    BSTR *DelimiterString);


void __RPC_STUB IGPTInterface_ArrayToString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGPTInterface_StringToArray_Proxy( 
    IGPTInterface * This,
    BSTR *iString,
    VARIANT *oArray,
    BSTR *DelimString);


void __RPC_STUB IGPTInterface_StringToArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGPTInterface_ConvertToPICK_Proxy( 
    IGPTInterface * This,
    BSTR *iString);


void __RPC_STUB IGPTInterface_ConvertToPICK_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGPTInterface_ConvertFromPICK_Proxy( 
    IGPTInterface * This,
    BSTR *iString);


void __RPC_STUB IGPTInterface_ConvertFromPICK_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGPTInterface_CountOccur_Proxy( 
    IGPTInterface * This,
    BSTR iString,
    BSTR SubString,
    long *Result);


void __RPC_STUB IGPTInterface_CountOccur_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGPTInterface_IndexSubString_Proxy( 
    IGPTInterface * This,
    BSTR iString,
    BSTR SubString,
    long Occurence,
    long *Position);


void __RPC_STUB IGPTInterface_IndexSubString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGPTInterface_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Document;

#ifdef __cplusplus

class DECLSPEC_UUID("1509E7A6-DD4C-11D3-970D-0080AD863699")
Document;
#endif

#ifndef __IGP_RTF_DISPINTERFACE_DEFINED__
#define __IGP_RTF_DISPINTERFACE_DEFINED__

/* dispinterface IGP_RTF */
/* [uuid] */ 


EXTERN_C const IID DIID_IGP_RTF;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("416CB5A7-3492-11D4-A239-CA7E3E8A8717")
    IGP_RTF : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IGP_RTFVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGP_RTF * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGP_RTF * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGP_RTF * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IGP_RTF * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IGP_RTF * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IGP_RTF * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IGP_RTF * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IGP_RTFVtbl;

    interface IGP_RTF
    {
        CONST_VTBL struct IGP_RTFVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGP_RTF_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGP_RTF_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGP_RTF_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGP_RTF_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IGP_RTF_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IGP_RTF_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IGP_RTF_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IGP_RTF_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_GPRTF;

#ifdef __cplusplus

class DECLSPEC_UUID("416CB5A9-3492-11D4-A239-CA7E3E8A8717")
GPRTF;
#endif

#ifndef __IGPDrawWnd_DISPINTERFACE_DEFINED__
#define __IGPDrawWnd_DISPINTERFACE_DEFINED__

/* dispinterface IGPDrawWnd */
/* [uuid] */ 


EXTERN_C const IID DIID_IGPDrawWnd;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B96B0B21-8ED7-11D4-970E-0080AD863699")
    IGPDrawWnd : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IGPDrawWndVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGPDrawWnd * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGPDrawWnd * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGPDrawWnd * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IGPDrawWnd * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IGPDrawWnd * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IGPDrawWnd * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IGPDrawWnd * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IGPDrawWndVtbl;

    interface IGPDrawWnd
    {
        CONST_VTBL struct IGPDrawWndVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGPDrawWnd_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGPDrawWnd_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGPDrawWnd_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGPDrawWnd_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IGPDrawWnd_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IGPDrawWnd_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IGPDrawWnd_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IGPDrawWnd_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_GPDrawWnd;

#ifdef __cplusplus

class DECLSPEC_UUID("B96B0B23-8ED7-11D4-970E-0080AD863699")
GPDrawWnd;
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
            /* [iid_is][out] */ void **ppvObject);
        
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
            /* [in] */ UINT cNames,
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
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMSFlexGridSink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMSFlexGridSink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMSFlexGridSink_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMSFlexGridSink_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMSFlexGridSink_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMSFlexGridSink_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IMSFlexGridSink_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MSFlexGridSink;

#ifdef __cplusplus

class DECLSPEC_UUID("EC3F7A38-C5FA-4379-92FB-4DEE4B54A247")
MSFlexGridSink;
#endif

#ifndef __ICDlgClientFiles_DISPINTERFACE_DEFINED__
#define __ICDlgClientFiles_DISPINTERFACE_DEFINED__

/* dispinterface ICDlgClientFiles */
/* [uuid] */ 


EXTERN_C const IID DIID_ICDlgClientFiles;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C3D93C3B-E18B-4714-BB1C-5500D3A9AA46")
    ICDlgClientFiles : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ICDlgClientFilesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICDlgClientFiles * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICDlgClientFiles * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICDlgClientFiles * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICDlgClientFiles * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICDlgClientFiles * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICDlgClientFiles * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICDlgClientFiles * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } ICDlgClientFilesVtbl;

    interface ICDlgClientFiles
    {
        CONST_VTBL struct ICDlgClientFilesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICDlgClientFiles_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICDlgClientFiles_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICDlgClientFiles_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICDlgClientFiles_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICDlgClientFiles_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICDlgClientFiles_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICDlgClientFiles_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ICDlgClientFiles_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CDlgClientFiles;

#ifdef __cplusplus

class DECLSPEC_UUID("D0BC6CB6-39D8-402D-8CD7-C4032CB1A52A")
CDlgClientFiles;
#endif

#ifndef __IDlgProject_DISPINTERFACE_DEFINED__
#define __IDlgProject_DISPINTERFACE_DEFINED__

/* dispinterface IDlgProject */
/* [uuid] */ 


EXTERN_C const IID DIID_IDlgProject;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("283127EF-0A8C-4A13-8C44-A26A6241F2BC")
    IDlgProject : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgProjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgProject * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgProject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgProject * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgProject * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgProject * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgProject * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgProject * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgProjectVtbl;

    interface IDlgProject
    {
        CONST_VTBL struct IDlgProjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgProject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgProject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgProject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgProject_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgProject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgProject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgProject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgProject_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_DlgProject;

#ifdef __cplusplus

class DECLSPEC_UUID("2781C1AB-630F-4A27-95BB-E3F708F23D93")
DlgProject;
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
            /* [iid_is][out] */ void **ppvObject);
        
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
            /* [in] */ UINT cNames,
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
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebBrowser2Sink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebBrowser2Sink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebBrowser2Sink_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebBrowser2Sink_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebBrowser2Sink_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebBrowser2Sink_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

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
            /* [iid_is][out] */ void **ppvObject);
        
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
            /* [in] */ UINT cNames,
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
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IGPTInterfaceEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IGPTInterfaceEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IGPTInterfaceEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IGPTInterfaceEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IGPTInterfaceEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IGPTInterfaceEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

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
            /* external definition not present */ OLE_HANDLE ihWnd,
            /* external definition not present */ OLE_HANDLE hWndMain,
            BSTR iString) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddSetMain( 
            /* external definition not present */ OLE_HANDLE ihWndMain) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteWnd( 
            /* external definition not present */ OLE_HANDLE ihWnd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateSize( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMinPos( 
            /* external definition not present */ OLE_HANDLE ihWnd,
            long MinTop,
            long MinLeft,
            long MinBottom,
            long MinRight) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMaxPos( 
            /* external definition not present */ OLE_HANDLE ihWnd,
            long MaxTop,
            long MaxLeft,
            long MaxBottom,
            long MaxRight) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMaxSize( 
            /* external definition not present */ OLE_HANDLE ihWnd,
            long iMaxWidth,
            long iMaxHeight) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMinSize( 
            /* external definition not present */ OLE_HANDLE ihWnd,
            long iMinWidth,
            long iMinHeight) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetNewStyle( 
            /* external definition not present */ OLE_HANDLE ihWnd,
            BSTR NewStyle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReinitSize( 
            /* external definition not present */ OLE_HANDLE ihWnd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetNewSize( 
            /* external definition not present */ OLE_HANDLE ihWnd,
            long Top,
            long Left,
            long Bottom,
            long Right) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteWndEx( 
            /* external definition not present */ OLE_HANDLE ihWnd,
            /* external definition not present */ OLE_HANDLE ownerHWND) = 0;
        
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
            /* [iid_is][out] */ void **ppvObject);
        
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
            /* [in] */ UINT cNames,
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
            /* external definition not present */ OLE_HANDLE ihWnd,
            /* external definition not present */ OLE_HANDLE hWndMain,
            BSTR iString);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddSetMain )( 
            IAutoSizing * This,
            /* external definition not present */ OLE_HANDLE ihWndMain);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteWnd )( 
            IAutoSizing * This,
            /* external definition not present */ OLE_HANDLE ihWnd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IAutoSizing * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateSize )( 
            IAutoSizing * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetMinPos )( 
            IAutoSizing * This,
            /* external definition not present */ OLE_HANDLE ihWnd,
            long MinTop,
            long MinLeft,
            long MinBottom,
            long MinRight);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetMaxPos )( 
            IAutoSizing * This,
            /* external definition not present */ OLE_HANDLE ihWnd,
            long MaxTop,
            long MaxLeft,
            long MaxBottom,
            long MaxRight);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetMaxSize )( 
            IAutoSizing * This,
            /* external definition not present */ OLE_HANDLE ihWnd,
            long iMaxWidth,
            long iMaxHeight);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetMinSize )( 
            IAutoSizing * This,
            /* external definition not present */ OLE_HANDLE ihWnd,
            long iMinWidth,
            long iMinHeight);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetNewStyle )( 
            IAutoSizing * This,
            /* external definition not present */ OLE_HANDLE ihWnd,
            BSTR NewStyle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReinitSize )( 
            IAutoSizing * This,
            /* external definition not present */ OLE_HANDLE ihWnd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetNewSize )( 
            IAutoSizing * This,
            /* external definition not present */ OLE_HANDLE ihWnd,
            long Top,
            long Left,
            long Bottom,
            long Right);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteWndEx )( 
            IAutoSizing * This,
            /* external definition not present */ OLE_HANDLE ihWnd,
            /* external definition not present */ OLE_HANDLE ownerHWND);
        
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
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAutoSizing_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAutoSizing_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAutoSizing_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAutoSizing_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAutoSizing_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAutoSizing_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAutoSizing_get_nItem(This,pVal)	\
    (This)->lpVtbl -> get_nItem(This,pVal)

#define IAutoSizing_AddWnd(This,ihWnd,hWndMain,iString)	\
    (This)->lpVtbl -> AddWnd(This,ihWnd,hWndMain,iString)

#define IAutoSizing_AddSetMain(This,ihWndMain)	\
    (This)->lpVtbl -> AddSetMain(This,ihWndMain)

#define IAutoSizing_DeleteWnd(This,ihWnd)	\
    (This)->lpVtbl -> DeleteWnd(This,ihWnd)

#define IAutoSizing_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IAutoSizing_UpdateSize(This)	\
    (This)->lpVtbl -> UpdateSize(This)

#define IAutoSizing_SetMinPos(This,ihWnd,MinTop,MinLeft,MinBottom,MinRight)	\
    (This)->lpVtbl -> SetMinPos(This,ihWnd,MinTop,MinLeft,MinBottom,MinRight)

#define IAutoSizing_SetMaxPos(This,ihWnd,MaxTop,MaxLeft,MaxBottom,MaxRight)	\
    (This)->lpVtbl -> SetMaxPos(This,ihWnd,MaxTop,MaxLeft,MaxBottom,MaxRight)

#define IAutoSizing_SetMaxSize(This,ihWnd,iMaxWidth,iMaxHeight)	\
    (This)->lpVtbl -> SetMaxSize(This,ihWnd,iMaxWidth,iMaxHeight)

#define IAutoSizing_SetMinSize(This,ihWnd,iMinWidth,iMinHeight)	\
    (This)->lpVtbl -> SetMinSize(This,ihWnd,iMinWidth,iMinHeight)

#define IAutoSizing_SetNewStyle(This,ihWnd,NewStyle)	\
    (This)->lpVtbl -> SetNewStyle(This,ihWnd,NewStyle)

#define IAutoSizing_ReinitSize(This,ihWnd)	\
    (This)->lpVtbl -> ReinitSize(This,ihWnd)

#define IAutoSizing_SetNewSize(This,ihWnd,Top,Left,Bottom,Right)	\
    (This)->lpVtbl -> SetNewSize(This,ihWnd,Top,Left,Bottom,Right)

#define IAutoSizing_DeleteWndEx(This,ihWnd,ownerHWND)	\
    (This)->lpVtbl -> DeleteWndEx(This,ihWnd,ownerHWND)

#define IAutoSizing_AutoSizingPause(This)	\
    (This)->lpVtbl -> AutoSizingPause(This)

#define IAutoSizing_AutoSizingResume(This)	\
    (This)->lpVtbl -> AutoSizingResume(This)

#define IAutoSizing_ReinitAll(This)	\
    (This)->lpVtbl -> ReinitAll(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAutoSizing_get_nItem_Proxy( 
    IAutoSizing * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IAutoSizing_get_nItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAutoSizing_AddWnd_Proxy( 
    IAutoSizing * This,
    /* external definition not present */ OLE_HANDLE ihWnd,
    /* external definition not present */ OLE_HANDLE hWndMain,
    BSTR iString);


void __RPC_STUB IAutoSizing_AddWnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAutoSizing_AddSetMain_Proxy( 
    IAutoSizing * This,
    /* external definition not present */ OLE_HANDLE ihWndMain);


void __RPC_STUB IAutoSizing_AddSetMain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAutoSizing_DeleteWnd_Proxy( 
    IAutoSizing * This,
    /* external definition not present */ OLE_HANDLE ihWnd);


void __RPC_STUB IAutoSizing_DeleteWnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAutoSizing_Reset_Proxy( 
    IAutoSizing * This);


void __RPC_STUB IAutoSizing_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAutoSizing_UpdateSize_Proxy( 
    IAutoSizing * This);


void __RPC_STUB IAutoSizing_UpdateSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAutoSizing_SetMinPos_Proxy( 
    IAutoSizing * This,
    /* external definition not present */ OLE_HANDLE ihWnd,
    long MinTop,
    long MinLeft,
    long MinBottom,
    long MinRight);


void __RPC_STUB IAutoSizing_SetMinPos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAutoSizing_SetMaxPos_Proxy( 
    IAutoSizing * This,
    /* external definition not present */ OLE_HANDLE ihWnd,
    long MaxTop,
    long MaxLeft,
    long MaxBottom,
    long MaxRight);


void __RPC_STUB IAutoSizing_SetMaxPos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAutoSizing_SetMaxSize_Proxy( 
    IAutoSizing * This,
    /* external definition not present */ OLE_HANDLE ihWnd,
    long iMaxWidth,
    long iMaxHeight);


void __RPC_STUB IAutoSizing_SetMaxSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAutoSizing_SetMinSize_Proxy( 
    IAutoSizing * This,
    /* external definition not present */ OLE_HANDLE ihWnd,
    long iMinWidth,
    long iMinHeight);


void __RPC_STUB IAutoSizing_SetMinSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAutoSizing_SetNewStyle_Proxy( 
    IAutoSizing * This,
    /* external definition not present */ OLE_HANDLE ihWnd,
    BSTR NewStyle);


void __RPC_STUB IAutoSizing_SetNewStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAutoSizing_ReinitSize_Proxy( 
    IAutoSizing * This,
    /* external definition not present */ OLE_HANDLE ihWnd);


void __RPC_STUB IAutoSizing_ReinitSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAutoSizing_SetNewSize_Proxy( 
    IAutoSizing * This,
    /* external definition not present */ OLE_HANDLE ihWnd,
    long Top,
    long Left,
    long Bottom,
    long Right);


void __RPC_STUB IAutoSizing_SetNewSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAutoSizing_DeleteWndEx_Proxy( 
    IAutoSizing * This,
    /* external definition not present */ OLE_HANDLE ihWnd,
    /* external definition not present */ OLE_HANDLE ownerHWND);


void __RPC_STUB IAutoSizing_DeleteWndEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAutoSizing_AutoSizingPause_Proxy( 
    IAutoSizing * This);


void __RPC_STUB IAutoSizing_AutoSizingPause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAutoSizing_AutoSizingResume_Proxy( 
    IAutoSizing * This);


void __RPC_STUB IAutoSizing_AutoSizingResume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAutoSizing_ReinitAll_Proxy( 
    IAutoSizing * This);


void __RPC_STUB IAutoSizing_ReinitAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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
            /* [iid_is][out] */ void **ppvObject);
        
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
            /* [in] */ UINT cNames,
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
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IAutoSizingEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IAutoSizingEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IAutoSizingEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IAutoSizingEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IAutoSizingEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IAutoSizingEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

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
            BSTR *iStr,
            /* [retval][out] */ LPDISPATCH *ppDisp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IConnectorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IConnector * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
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
            /* [in] */ UINT cNames,
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
            BSTR *iStr,
            /* [retval][out] */ LPDISPATCH *ppDisp);
        
        END_INTERFACE
    } IConnectorVtbl;

    interface IConnector
    {
        CONST_VTBL struct IConnectorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IConnector_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IConnector_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IConnector_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IConnector_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IConnector_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IConnector_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IConnector_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IConnector_GetTerminal(This,iStr,ppDisp)	\
    (This)->lpVtbl -> GetTerminal(This,iStr,ppDisp)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IConnector_GetTerminal_Proxy( 
    IConnector * This,
    BSTR *iStr,
    /* [retval][out] */ LPDISPATCH *ppDisp);


void __RPC_STUB IConnector_GetTerminal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IConnector_INTERFACE_DEFINED__ */


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
#endif /* __GP_Term_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


