#if !defined(AFX_WEBBROWSER2SINK_H__BD83704E_CE1C_44A0_B7BF_DEDE85A3C2C4__INCLUDED_)
#define AFX_WEBBROWSER2SINK_H__BD83704E_CE1C_44A0_B7BF_DEDE85A3C2C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPWebBrowser2Sink.h : header file
//

class GPWebBrowser2;

/////////////////////////////////////////////////////////////////////////////
// GPWebBrowser2Sink command target

class GPWebBrowser2Sink : public CCmdTarget
{
	friend class GPWebBrowser2;
	DECLARE_DYNCREATE(GPWebBrowser2Sink)

	GPWebBrowser2Sink();           // protected constructor used by dynamic creation
// Attributes
public:
	static const IID DIID_DGPWebBrowserEvents2;

// Operations
public:
	void SetGPWebBrowser(GPWebBrowser2 *pt);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPWebBrowser2Sink)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
	virtual ~GPWebBrowser2Sink();

protected:
	void OnStatusTextChangeExplorer(LPCTSTR Text);
	void OnProgressChangeExplorer(long Progress, long ProgressMax);
	void OnCommandStateChangeExplorer(long Command, BOOL Enable);
	void OnDownloadBeginExplorer();
	void OnDownloadCompleteExplorer();
	void OnTitleChangeExplorer(LPCTSTR Text);
	void OnPropertyChangeExplorer(LPCTSTR szProperty);
	void OnBeforeNavigate2Explorer(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Flags, VARIANT FAR* TargetFrameName, VARIANT FAR* PostData, VARIANT FAR* Headers, BOOL FAR* Cancel);
	void OnNewWindow2Explorer(LPDISPATCH FAR* ppDisp, BOOL FAR* Cancel);
	void OnNavigateComplete2Explorer(LPDISPATCH pDisp, VARIANT FAR* URL);
	void OnDocumentCompleteExplorer(LPDISPATCH pDisp, VARIANT FAR* URL);
	void OnOnQuitExplorer();
	void OnOnVisibleExplorer(BOOL Visible);
	void OnOnToolBarExplorer(BOOL ToolBar);
	void OnOnMenuBarExplorer(BOOL MenuBar);
	void OnOnStatusBarExplorer(BOOL StatusBar);
	void OnOnFullScreenExplorer(BOOL FullScreen);
	void OnOnTheaterModeExplorer(BOOL TheaterMode);
	void OnWindowSetResizableExplorer(BOOL Resizable);
	void OnWindowSetLeftExplorer(long Left);
	void OnWindowSetTopExplorer(long Top);
	void OnWindowSetWidthExplorer(long Width);
	void OnWindowSetHeightExplorer(long Height);
	void OnWindowClosingExplorer(BOOL IsChildWindow, BOOL FAR* Cancel);
	void OnSetSecureLockIconExplorer(long SecureLockIcon);
	void OnClientToHostWindowExplorer(long FAR* CX, long FAR* CY);
	void OnFileDownloadExplorer(BOOL FAR* Cancel);
	void OnNavigateErrorExplorer(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Frame, VARIANT FAR* StatusCode, BOOL FAR* Cancel);
	void OnPrintTemplateInstantiationExplorer(LPDISPATCH pDisp);
	void OnPrintTemplateTeardownExplorer(LPDISPATCH pDisp);
	void OnUpdatePageStatusExplorer(LPDISPATCH pDisp, VARIANT FAR* nPage, VARIANT FAR* fDone);
	void OnPrivacyImpactedStateChangeExplorer(BOOL bImpacted);

	// Generated message map functions
	//{{AFX_MSG(GPWebBrowser2Sink)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(GPWebBrowser2Sink)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	GPWebBrowser2 * m_ptrGPWebBrowser;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEBBROWSER2SINK_H__BD83704E_CE1C_44A0_B7BF_DEDE85A3C2C4__INCLUDED_)
