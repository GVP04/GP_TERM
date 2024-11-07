// GPHTMLDocument.cpp: implementation of the GPHTMLDocument class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPHTMLDocument.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPHTMLDocument::~GPHTMLDocument()
{

}


/////////////////////////////////////////////////////////////////////////////
// IHTMLDocument properties

/////////////////////////////////////////////////////////////////////////////
// IHTMLDocument operations

LPDISPATCH GPHTMLDocument::GetAll()
{
	LPDISPATCH result;
	InvokeHelper(0x3eb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPHTMLDocument::GetBody()
{
	LPDISPATCH result;
	InvokeHelper(0x3ec, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPHTMLDocument::GetActiveElement()
{
	LPDISPATCH result;
	InvokeHelper(0x3ed, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPHTMLDocument::GetImages()
{
	LPDISPATCH result;
	InvokeHelper(0x3f3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPHTMLDocument::GetApplets()
{
	LPDISPATCH result;
	InvokeHelper(0x3f0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPHTMLDocument::GetLinks()
{
	LPDISPATCH result;
	InvokeHelper(0x3f1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPHTMLDocument::GetForms()
{
	LPDISPATCH result;
	InvokeHelper(0x3f2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPHTMLDocument::GetAnchors()
{
	LPDISPATCH result;
	InvokeHelper(0x3ef, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetTitle(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString GPHTMLDocument::GetTitle()
{
	CString result;
	InvokeHelper(0x3f4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPHTMLDocument::GetScripts()
{
	LPDISPATCH result;
	InvokeHelper(0x3f5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPHTMLDocument::GetSelection()
{
	LPDISPATCH result;
	InvokeHelper(0x3f9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString GPHTMLDocument::GetReadyState()
{
	CString result;
	InvokeHelper(0x3fa, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPHTMLDocument::GetFrames()
{
	LPDISPATCH result;
	InvokeHelper(0x3fb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPHTMLDocument::GetEmbeds()
{
	LPDISPATCH result;
	InvokeHelper(0x3f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPHTMLDocument::GetPlugins()
{
	LPDISPATCH result;
	InvokeHelper(0x3fd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetAlinkColor(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3fe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetAlinkColor()
{
	VARIANT result;
	InvokeHelper(0x3fe, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetBgColor(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(DISPID_BACKCOLOR, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetBgColor()
{
	VARIANT result;
	InvokeHelper(DISPID_BACKCOLOR, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetFgColor(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x8001138a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetFgColor()
{
	VARIANT result;
	InvokeHelper(0x8001138a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetLinkColor(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x400, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetLinkColor()
{
	VARIANT result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetVlinkColor(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3ff, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetVlinkColor()
{
	VARIANT result;
	InvokeHelper(0x3ff, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

CString GPHTMLDocument::GetReferrer()
{
	CString result;
	InvokeHelper(0x403, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPHTMLDocument::GetLocation()
{
	LPDISPATCH result;
	InvokeHelper(0x402, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString GPHTMLDocument::GetLastModified()
{
	CString result;
	InvokeHelper(0x404, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetUrl(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x401, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString GPHTMLDocument::GetUrl()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetDomain(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x405, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString GPHTMLDocument::GetDomain()
{
	CString result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetCookie(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x406, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString GPHTMLDocument::GetCookie()
{
	CString result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetDefaultCharset(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x409, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString GPHTMLDocument::GetDefaultCharset()
{
	CString result;
	InvokeHelper(0x409, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString GPHTMLDocument::GetMimeType()
{
	CString result;
	InvokeHelper(0x411, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString GPHTMLDocument::GetFileSize()
{
	CString result;
	InvokeHelper(0x412, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString GPHTMLDocument::GetFileCreatedDate()
{
	CString result;
	InvokeHelper(0x413, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString GPHTMLDocument::GetFileModifiedDate()
{
	CString result;
	InvokeHelper(0x414, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString GPHTMLDocument::GetFileUpdatedDate()
{
	CString result;
	InvokeHelper(0x415, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString GPHTMLDocument::GetSecurity()
{
	CString result;
	InvokeHelper(0x416, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString GPHTMLDocument::GetProtocol()
{
	CString result;
	InvokeHelper(0x417, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString GPHTMLDocument::GetNameProp()
{
	CString result;
	InvokeHelper(0x418, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPHTMLDocument::open(LPCTSTR url, const VARIANT& name, const VARIANT& features, const VARIANT& replace)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x420, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		url, &name, &features, &replace);
	return result;
}

void GPHTMLDocument::close()
{
	InvokeHelper(0x421, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void GPHTMLDocument::clear()
{
	InvokeHelper(0x422, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL GPHTMLDocument::queryCommandSupported(LPCTSTR cmdID)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x423, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		cmdID);
	return result;
}

BOOL GPHTMLDocument::queryCommandEnabled(LPCTSTR cmdID)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x424, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		cmdID);
	return result;
}

BOOL GPHTMLDocument::queryCommandState(LPCTSTR cmdID)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x425, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		cmdID);
	return result;
}

BOOL GPHTMLDocument::queryCommandIndeterm(LPCTSTR cmdID)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x426, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		cmdID);
	return result;
}

CString GPHTMLDocument::queryCommandText(LPCTSTR cmdID)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x427, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		cmdID);
	return result;
}

VARIANT GPHTMLDocument::queryCommandValue(LPCTSTR cmdID)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x428, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		cmdID);
	return result;
}

BOOL GPHTMLDocument::execCommand(LPCTSTR cmdID, BOOL showUI, const VARIANT& value)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL VTS_VARIANT;
	InvokeHelper(0x429, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		cmdID, showUI, &value);
	return result;
}

BOOL GPHTMLDocument::execCommandShowHelp(LPCTSTR cmdID)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x42a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		cmdID);
	return result;
}

LPDISPATCH GPHTMLDocument::createElement(LPCTSTR eTag)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x42b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		eTag);
	return result;
}

void GPHTMLDocument::SetOnhelp(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x8001177d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetOnhelp()
{
	VARIANT result;
	InvokeHelper(0x8001177d, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetOnclick(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x80011778, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetOnclick()
{
	VARIANT result;
	InvokeHelper(0x80011778, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetOndblclick(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x80011779, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetOndblclick()
{
	VARIANT result;
	InvokeHelper(0x80011779, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetOnkeyup(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x80011776, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetOnkeyup()
{
	VARIANT result;
	InvokeHelper(0x80011776, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetOnkeydown(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x80011775, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetOnkeydown()
{
	VARIANT result;
	InvokeHelper(0x80011775, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetOnkeypress(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x80011777, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetOnkeypress()
{
	VARIANT result;
	InvokeHelper(0x80011777, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetOnmouseup(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x80011773, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetOnmouseup()
{
	VARIANT result;
	InvokeHelper(0x80011773, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetOnmousedown(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x80011772, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetOnmousedown()
{
	VARIANT result;
	InvokeHelper(0x80011772, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetOnmousemove(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x80011774, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetOnmousemove()
{
	VARIANT result;
	InvokeHelper(0x80011774, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetOnmouseout(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x80011771, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetOnmouseout()
{
	VARIANT result;
	InvokeHelper(0x80011771, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetOnmouseover(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x80011770, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetOnmouseover()
{
	VARIANT result;
	InvokeHelper(0x80011770, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetOnreadystatechange(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x80011789, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetOnreadystatechange()
{
	VARIANT result;
	InvokeHelper(0x80011789, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetOnafterupdate(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x80011786, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetOnafterupdate()
{
	VARIANT result;
	InvokeHelper(0x80011786, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetOnrowexit(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x80011782, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetOnrowexit()
{
	VARIANT result;
	InvokeHelper(0x80011782, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetOnrowenter(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x80011783, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetOnrowenter()
{
	VARIANT result;
	InvokeHelper(0x80011783, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetOndragstart(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x80011793, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetOndragstart()
{
	VARIANT result;
	InvokeHelper(0x80011793, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetOnselectstart(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x80011795, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetOnselectstart()
{
	VARIANT result;
	InvokeHelper(0x80011795, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPHTMLDocument::elementFromPoint(long x, long y)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x42c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		x, y);
	return result;
}

LPDISPATCH GPHTMLDocument::GetParentWindow()
{
	LPDISPATCH result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPHTMLDocument::GetStyleSheets()
{
	LPDISPATCH result;
	InvokeHelper(0x42d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetOnbeforeupdate(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x80011785, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetOnbeforeupdate()
{
	VARIANT result;
	InvokeHelper(0x80011785, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPHTMLDocument::SetOnerrorupdate(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x80011796, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPHTMLDocument::GetOnerrorupdate()
{
	VARIANT result;
	InvokeHelper(0x80011796, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

CString GPHTMLDocument::toString()
{
	CString result;
	InvokeHelper(0x42e, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPHTMLDocument::createStyleSheet(LPCTSTR bstrHref, long lIndex)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x42f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		bstrHref, lIndex);
	return result;
}

