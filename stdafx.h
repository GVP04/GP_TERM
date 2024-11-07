// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__1509E7AE_DD4C_11D3_970D_0080AD863699__INCLUDED_)
#define AFX_STDAFX_H__1509E7AE_DD4C_11D3_970D_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define OEMRESOURCE 

#include <afxpriv.h>

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#include <afxtempl.h>


#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#include <afxdocob.h>
#include "MyGdiplus.h"
  using namespace Gdiplus;
//#include <Wingdi.h>
#include <locale.h>

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <Winsock2.h>		// MFC socket extensions
#include <afxsock.h>		// MFC socket extensions
	#define _ATL_APARTMENT_THREADED
#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
class CGP_TermModule : public CComModule
{
public:
	LONG Unlock();
	LONG Lock();
	DWORD dwThreadID;
};
extern CGP_TermModule _Module;
#include <atlcom.h>
#include <wininet.h>
#include <afx.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__1509E7AE_DD4C_11D3_970D_0080AD863699__INCLUDED_)
