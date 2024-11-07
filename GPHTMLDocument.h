// GPHTMLDocument.h: interface for the GPHTMLDocument class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPHTMLDOCUMENT_H__BD9C845A_B405_4EAE_BD2E_D7A73082FDFE__INCLUDED_)
#define AFX_GPHTMLDOCUMENT_H__BD9C845A_B405_4EAE_BD2E_D7A73082FDFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// IHTMLDocument wrapper class

class GPHTMLDocument : public COleDispatchDriver
{
public:
	GPHTMLDocument() {}		// Calls COleDispatchDriver default constructor
	GPHTMLDocument(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	GPHTMLDocument(const GPHTMLDocument& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}
	virtual ~GPHTMLDocument();


// Attributes
public:

// Operations
public:
	LPDISPATCH GetAll();
	LPDISPATCH GetBody();
	LPDISPATCH GetActiveElement();
	LPDISPATCH GetImages();
	LPDISPATCH GetApplets();
	LPDISPATCH GetLinks();
	LPDISPATCH GetForms();
	LPDISPATCH GetAnchors();
	void SetTitle(LPCTSTR lpszNewValue);
	CString GetTitle();
	LPDISPATCH GetScripts();
	LPDISPATCH GetSelection();
	CString GetReadyState();
	LPDISPATCH GetFrames();
	LPDISPATCH GetEmbeds();
	LPDISPATCH GetPlugins();
	void SetAlinkColor(const VARIANT& newValue);
	VARIANT GetAlinkColor();
	void SetBgColor(const VARIANT& newValue);
	VARIANT GetBgColor();
	void SetFgColor(const VARIANT& newValue);
	VARIANT GetFgColor();
	void SetLinkColor(const VARIANT& newValue);
	VARIANT GetLinkColor();
	void SetVlinkColor(const VARIANT& newValue);
	VARIANT GetVlinkColor();
	CString GetReferrer();
	LPDISPATCH GetLocation();
	CString GetLastModified();
	void SetUrl(LPCTSTR lpszNewValue);
	CString GetUrl();
	void SetDomain(LPCTSTR lpszNewValue);
	CString GetDomain();
	void SetCookie(LPCTSTR lpszNewValue);
	CString GetCookie();
	void SetDefaultCharset(LPCTSTR lpszNewValue);
	CString GetDefaultCharset();
	CString GetMimeType();
	CString GetFileSize();
	CString GetFileCreatedDate();
	CString GetFileModifiedDate();
	CString GetFileUpdatedDate();
	CString GetSecurity();
	CString GetProtocol();
	CString GetNameProp();
	// method 'write' not emitted because of invalid return type or parameter type
	// method 'writeln' not emitted because of invalid return type or parameter type
	LPDISPATCH open(LPCTSTR url, const VARIANT& name, const VARIANT& features, const VARIANT& replace);
	void close();
	void clear();
	BOOL queryCommandSupported(LPCTSTR cmdID);
	BOOL queryCommandEnabled(LPCTSTR cmdID);
	BOOL queryCommandState(LPCTSTR cmdID);
	BOOL queryCommandIndeterm(LPCTSTR cmdID);
	CString queryCommandText(LPCTSTR cmdID);
	VARIANT queryCommandValue(LPCTSTR cmdID);
	BOOL execCommand(LPCTSTR cmdID, BOOL showUI, const VARIANT& value);
	BOOL execCommandShowHelp(LPCTSTR cmdID);
	LPDISPATCH createElement(LPCTSTR eTag);
	void SetOnhelp(const VARIANT& newValue);
	VARIANT GetOnhelp();
	void SetOnclick(const VARIANT& newValue);
	VARIANT GetOnclick();
	void SetOndblclick(const VARIANT& newValue);
	VARIANT GetOndblclick();
	void SetOnkeyup(const VARIANT& newValue);
	VARIANT GetOnkeyup();
	void SetOnkeydown(const VARIANT& newValue);
	VARIANT GetOnkeydown();
	void SetOnkeypress(const VARIANT& newValue);
	VARIANT GetOnkeypress();
	void SetOnmouseup(const VARIANT& newValue);
	VARIANT GetOnmouseup();
	void SetOnmousedown(const VARIANT& newValue);
	VARIANT GetOnmousedown();
	void SetOnmousemove(const VARIANT& newValue);
	VARIANT GetOnmousemove();
	void SetOnmouseout(const VARIANT& newValue);
	VARIANT GetOnmouseout();
	void SetOnmouseover(const VARIANT& newValue);
	VARIANT GetOnmouseover();
	void SetOnreadystatechange(const VARIANT& newValue);
	VARIANT GetOnreadystatechange();
	void SetOnafterupdate(const VARIANT& newValue);
	VARIANT GetOnafterupdate();
	void SetOnrowexit(const VARIANT& newValue);
	VARIANT GetOnrowexit();
	void SetOnrowenter(const VARIANT& newValue);
	VARIANT GetOnrowenter();
	void SetOndragstart(const VARIANT& newValue);
	VARIANT GetOndragstart();
	void SetOnselectstart(const VARIANT& newValue);
	VARIANT GetOnselectstart();
	LPDISPATCH elementFromPoint(long x, long y);
	LPDISPATCH GetParentWindow();
	LPDISPATCH GetStyleSheets();
	void SetOnbeforeupdate(const VARIANT& newValue);
	VARIANT GetOnbeforeupdate();
	void SetOnerrorupdate(const VARIANT& newValue);
	VARIANT GetOnerrorupdate();
	CString toString();
	LPDISPATCH createStyleSheet(LPCTSTR bstrHref, long lIndex);

};
/////////////////////////////////////////////////////////////////////////////
// IHTMLElementDefaults wrapper class
#endif // !defined(AFX_GPHTMLDOCUMENT_H__BD9C845A_B405_4EAE_BD2E_D7A73082FDFE__INCLUDED_)
