// WebBrowser2Sink.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPWebBrowser2Sink.h"
#include "GPWebBrowser2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPWebBrowser2Sink

IMPLEMENT_DYNCREATE(GPWebBrowser2Sink, CCmdTarget)

GPWebBrowser2Sink::GPWebBrowser2Sink()
{
	EnableAutomation();
}

GPWebBrowser2Sink::~GPWebBrowser2Sink()
{
}


void GPWebBrowser2Sink::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(GPWebBrowser2Sink, CCmdTarget)
	//{{AFX_MSG_MAP(GPWebBrowser2Sink)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(GPWebBrowser2Sink, CCmdTarget)
	//{{AFX_DISPATCH_MAP(GPWebBrowser2Sink)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "StatusTextChange", 102, OnStatusTextChangeExplorer, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "ProgressChange", 108, OnProgressChangeExplorer, VT_EMPTY, VTS_I4 VTS_I4)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "CommandStateChange", 105, OnCommandStateChangeExplorer, VT_EMPTY, VTS_I4 VTS_BOOL)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "DownloadBegin", 106, OnDownloadBeginExplorer, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "DownloadComplete", 104, OnDownloadCompleteExplorer, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "TitleChange", 113, OnTitleChangeExplorer, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "PropertyChange", 112, OnPropertyChangeExplorer, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "BeforeNavigate2", 250, OnBeforeNavigate2Explorer, VT_EMPTY, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "NewWindow2", 251, OnNewWindow2Explorer, VT_EMPTY, VTS_PDISPATCH VTS_PBOOL)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "NavigateComplete2", 252, OnNavigateComplete2Explorer, VT_EMPTY, VTS_DISPATCH VTS_PVARIANT)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "DocumentComplete", 259, OnDocumentCompleteExplorer, VT_EMPTY, VTS_DISPATCH VTS_PVARIANT)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "OnQuit", 253, OnOnQuitExplorer, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "OnVisible", 254, OnOnVisibleExplorer, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "OnToolBar", 255, OnOnToolBarExplorer, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "OnMenuBar", 256, OnOnMenuBarExplorer, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "OnStatusBar", 257, OnOnStatusBarExplorer, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "OnFullScreen", 258, OnOnFullScreenExplorer, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "OnTheaterMode", 260, OnOnTheaterModeExplorer, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "WindowSetResizable", 262, OnWindowSetResizableExplorer, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "WindowSetLeft", 264, OnWindowSetLeftExplorer, VT_EMPTY, VTS_I4)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "WindowSetTop", 265, OnWindowSetTopExplorer, VT_EMPTY, VTS_I4)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "WindowSetWidth", 266, OnWindowSetWidthExplorer, VT_EMPTY, VTS_I4)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "WindowSetHeight", 267, OnWindowSetHeightExplorer, VT_EMPTY, VTS_I4)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "WindowClosing", 263, OnWindowClosingExplorer, VT_EMPTY, VTS_BOOL VTS_PBOOL)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "SetSecureLockIcon", 269, OnSetSecureLockIconExplorer, VT_EMPTY, VTS_I4)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "ClientToHostWindow", 268, OnClientToHostWindowExplorer, VT_EMPTY, VTS_PI4 VTS_PI4)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "FileDownload", 270, OnFileDownloadExplorer, VT_EMPTY, VTS_PBOOL)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "NavigateError", 271, OnNavigateErrorExplorer, VT_EMPTY, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "PrintTemplateInstantiation", 225, OnPrintTemplateInstantiationExplorer, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "PrintTemplateTeardown", 226, OnPrintTemplateTeardownExplorer, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "UpdatePageStatus", 227, OnUpdatePageStatusExplorer, VT_EMPTY, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT)
	DISP_FUNCTION_ID(GPWebBrowser2Sink, "PrivacyImpactedStateChange", 272, OnPrivacyImpactedStateChangeExplorer, VT_EMPTY, VTS_BOOL)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IWebBrowser2Sink to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.
// {6B13E51E-75CF-4061-9250-4B2E65BE657F}
const IID GPWebBrowser2Sink::DIID_DGPWebBrowserEvents2 =
{ 0x6b13e51e, 0x75cf, 0x4061, { 0x92, 0x50, 0x4b, 0x2e, 0x65, 0xbe, 0x65, 0x7f } };

BEGIN_INTERFACE_MAP(GPWebBrowser2Sink, CCmdTarget)
	INTERFACE_PART(GPWebBrowser2Sink, DIID_DWebBrowserEvents2, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPWebBrowser2Sink message handlers
void GPWebBrowser2Sink::SetGPWebBrowser(GPWebBrowser2 *pt)
{
	m_ptrGPWebBrowser=pt;
}


void GPWebBrowser2Sink::OnStatusTextChangeExplorer(LPCTSTR Text) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnStatusTextChangeExplorer(Text);
}

void GPWebBrowser2Sink::OnProgressChangeExplorer(long Progress, long ProgressMax) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnProgressChangeExplorer(Progress, ProgressMax);
}

void GPWebBrowser2Sink::OnCommandStateChangeExplorer(long Command, BOOL Enable) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnCommandStateChangeExplorer(Command, Enable);
}

void GPWebBrowser2Sink::OnDownloadBeginExplorer() 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnDownloadBeginExplorer();
}

void GPWebBrowser2Sink::OnDownloadCompleteExplorer() 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnDownloadCompleteExplorer();
}

void GPWebBrowser2Sink::OnTitleChangeExplorer(LPCTSTR Text) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnTitleChangeExplorer(Text);
}

void GPWebBrowser2Sink::OnPropertyChangeExplorer(LPCTSTR szProperty) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnPropertyChangeExplorer(szProperty);
}

void GPWebBrowser2Sink::OnBeforeNavigate2Explorer(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Flags, VARIANT FAR* TargetFrameName, VARIANT FAR* PostData, VARIANT FAR* Headers, BOOL FAR* Cancel) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnBeforeNavigate2Explorer(pDisp, URL, Flags, TargetFrameName, PostData, Headers, Cancel);
}

void GPWebBrowser2Sink::OnNewWindow2Explorer(LPDISPATCH FAR* ppDisp, BOOL FAR* Cancel) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnNewWindow2Explorer(ppDisp, Cancel);
}

void GPWebBrowser2Sink::OnNavigateComplete2Explorer(LPDISPATCH pDisp, VARIANT FAR* URL) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnNavigateComplete2Explorer(pDisp, URL);
}

void GPWebBrowser2Sink::OnDocumentCompleteExplorer(LPDISPATCH pDisp, VARIANT FAR* URL) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnDocumentCompleteExplorer(pDisp, URL);
}

void GPWebBrowser2Sink::OnOnQuitExplorer() 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnOnQuitExplorer();
}

void GPWebBrowser2Sink::OnOnVisibleExplorer(BOOL Visible) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnOnVisibleExplorer(Visible);
}

void GPWebBrowser2Sink::OnOnToolBarExplorer(BOOL ToolBar) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnOnToolBarExplorer(ToolBar);
}

void GPWebBrowser2Sink::OnOnMenuBarExplorer(BOOL MenuBar) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnOnMenuBarExplorer(MenuBar);
}

void GPWebBrowser2Sink::OnOnStatusBarExplorer(BOOL StatusBar) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnOnStatusBarExplorer(StatusBar);
}

void GPWebBrowser2Sink::OnOnFullScreenExplorer(BOOL FullScreen) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnOnFullScreenExplorer(FullScreen);
}

void GPWebBrowser2Sink::OnOnTheaterModeExplorer(BOOL TheaterMode) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnOnTheaterModeExplorer(TheaterMode);
}

void GPWebBrowser2Sink::OnWindowSetResizableExplorer(BOOL Resizable) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnWindowSetResizableExplorer(Resizable);
}

void GPWebBrowser2Sink::OnWindowSetLeftExplorer(long Left) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnWindowSetLeftExplorer(Left);
}

void GPWebBrowser2Sink::OnWindowSetTopExplorer(long Top) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnWindowSetTopExplorer(Top);
}

void GPWebBrowser2Sink::OnWindowSetWidthExplorer(long Width) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnWindowSetWidthExplorer(Width);
}

void GPWebBrowser2Sink::OnWindowSetHeightExplorer(long Height) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnWindowSetHeightExplorer(Height);
}

void GPWebBrowser2Sink::OnWindowClosingExplorer(BOOL IsChildWindow, BOOL FAR* Cancel) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnWindowClosingExplorer(IsChildWindow, Cancel);
}

void GPWebBrowser2Sink::OnSetSecureLockIconExplorer(long SecureLockIcon) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnSetSecureLockIconExplorer(SecureLockIcon);
}

void GPWebBrowser2Sink::OnClientToHostWindowExplorer(long FAR* CX, long FAR* CY) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnClientToHostWindowExplorer(CX, CY);
}

void GPWebBrowser2Sink::OnFileDownloadExplorer(BOOL FAR* Cancel) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnFileDownloadExplorer(Cancel);
}

void GPWebBrowser2Sink::OnNavigateErrorExplorer(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Frame, VARIANT FAR* StatusCode, BOOL FAR* Cancel) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnNavigateErrorExplorer(pDisp, URL, Frame, StatusCode, Cancel);
}

void GPWebBrowser2Sink::OnPrintTemplateInstantiationExplorer(LPDISPATCH pDisp) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnPrintTemplateInstantiationExplorer(pDisp);
}

void GPWebBrowser2Sink::OnPrintTemplateTeardownExplorer(LPDISPATCH pDisp) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnPrintTemplateTeardownExplorer(pDisp);
}

void GPWebBrowser2Sink::OnUpdatePageStatusExplorer(LPDISPATCH pDisp, VARIANT FAR* nPage, VARIANT FAR* fDone) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnUpdatePageStatusExplorer(pDisp, nPage, fDone);
}

void GPWebBrowser2Sink::OnPrivacyImpactedStateChangeExplorer(BOOL bImpacted) 
{
	if (m_ptrGPWebBrowser)
		m_ptrGPWebBrowser->OnPrivacyImpactedStateChangeExplorer(bImpacted);
}

