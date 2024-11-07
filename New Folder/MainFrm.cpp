// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "GP_Term.h"
#include "Splash.h"
#include "MainFrm.h"
#include "GP_TermDoc.h"
#include "GPStatusBarCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HRESULT ModifyPrivilege(LPCTSTR szPrivilege,BOOL fEnable);

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)


BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_QUERYENDSESSION()
	ON_WM_SHOWWINDOW()
	ON_WM_HELPINFO()
	ON_COMMAND(ID_VIEW_STATUS_BAR, OnViewStatusBar)
	ON_COMMAND(ID_VIEW_TOOLBAR, OnViewToolbar)
	ON_UPDATE_COMMAND_UI(ID_TRANSLATE_TCL, OnUpdateTranslateTcl)
	ON_UPDATE_COMMAND_UI(ID_KEYBLOCK, OnUpdateKeyblock)
	ON_WM_ENTERIDLE()
	ON_COMMAND(ID_VIEW_DEVTOOLBAR, OnViewDevtoolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DEVTOOLBAR, OnUpdateViewDevtoolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR, OnUpdateViewToolbar)
	ON_WM_DROPFILES()
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_COMMAND(ID_FULLCONTEXTMENU, OnFullcontextmenu)
	ON_COMMAND(IDM_STATISTIC, OnStatistic)
	ON_UPDATE_COMMAND_UI(IDM_STATISTIC, OnUpdateStatistic)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_OVR,
	ID_PROTERTFIELDS,
	ID_KEYBLOCK,
	ID_TRANSLATE_TCL,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_SCREENSIZE,
	ID_TERMINALTYPE,
};

//#define ID_INDICATOR_EXT                0xE700  // extended selection indicator
//#define ID_INDICATOR_CAPS               0xE701  // cap lock indicator
//#define ID_INDICATOR_NUM                0xE702  // num lock indicator
//#define ID_INDICATOR_SCRL               0xE703  // scroll lock indicator
//#define ID_INDICATOR_OVR                0xE704  // overtype mode indicator
//#define ID_INDICATOR_REC                0xE705  // record mode indicator
//#define ID_INDICATOR_KANA               0xE706  // kana lock indicator



/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	FRDlg =NULL; 
	CSplashWnd::ShowSplashScreen(this);
	m_WaitAll=CreateEvent(NULL, TRUE, FALSE, "m_WaitAll");
}

CMainFrame::~CMainFrame()
{
	if (FRDlg !=NULL) delete FRDlg; 
	CloseHandle(m_WaitAll);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	strncpy(GPC.TermCapFileName,AfxGetApp()->GetProfileString(GPC.cs_RegTermViewSetName, "TERMCAPFILE","TERMCAP.TXT"),250);
	GPC.TermCapFileName[250]=0;
	m_TermCap.Load(GPC.TermCapFileName);


	HKEY tmpKew=NULL;
	HKEY tmpKewList=NULL;
	HKEY tmpMain=NULL;
	CString ssss;
	DWORD dwDisp=0;
	ssss.Format("Software\\%s\\%s\\COMSETLIST",AfxGetApp()->m_pszRegistryKey,AfxGetApp()->m_pszAppName);
	::RegOpenKeyEx(HKEY_CURRENT_USER,ssss,0,KEY_ALL_ACCESS,&tmpKew);
	if (!tmpKew)
	{
		ssss.Format("Software\\%s\\%s\\COMSET2",AfxGetApp()->m_pszRegistryKey,AfxGetApp()->m_pszAppName);
		::RegOpenKeyEx(HKEY_CURRENT_USER,ssss,0,KEY_ALL_ACCESS,&tmpKew);
		if (tmpKew)
		{
			RegCloseKey(tmpKew);
			tmpKew=NULL;
			#ifdef BRIZ
				#ifdef RUS
					ssss="Программа обнаружила старый формат конфигурации сессий. Рекомендуется сохранить предыдущее описание \n HKEY_CURRENT_USER\\Software\\INFOTOOLS Applications\\BRIZ_RUS \n Продолжить ?";
				#else
					ssss="The program has found out an old format of a configuration of sessions. It is recommended to keep the previous configuration \n HKEY_CURRENT_USER\\Software\\INFOTOOLS Applications\\BRIZ_RUS \n Continue?";
				#endif
			#else
				ssss="Программа обнаружила старый формат конфигурации сессий. Рекомендуется сохранить предыдущее описание \nHKEY_CURRENT_USER\\Software\\Local AppWizard-Generated Applications\\GP_term\n Продолжить ?";
			#endif

			if (AfxMessageBox(ssss,MB_ICONQUESTION|MB_APPLMODAL|MB_OKCANCEL,0)!=IDOK)
			{
				return -1;
			}
			
			ssss.Format("Software\\%s\\%s",AfxGetApp()->m_pszRegistryKey,AfxGetApp()->m_pszAppName);
			RegCreateKeyEx(HKEY_CURRENT_USER,ssss,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&tmpMain,&dwDisp);
			dwDisp=0;
			RegCreateKeyEx(tmpMain,"COMSETLIST",0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&tmpKewList,&dwDisp);
			//FormatMessage(  FORMAT_MESSAGE_FROM_SYSTEM, (const void *)FORMAT_MESSAGE_FROM_HMODULE, dwDisp, 0, ccc, 2000, NULL);

			if (tmpKewList) 
			{
				const char *subKeyOld[]={"COMSET0","COMSET1","COMSET2","COMSET3","COMSET4","COMSET5",};
				const char *tmpFileName=".\\regtemp.reg";

				int i;
				for(i=0;i<6;i++)
				{
					tmpKew=NULL;
					::RegOpenKeyEx(tmpMain,subKeyOld[i],0,KEY_ALL_ACCESS,&tmpKew);
					if (tmpKew)
					{
						RegCloseKey(tmpKew);
						DeleteFile(tmpFileName);
						ssss.Format("Software\\%s\\%s\\%s",AfxGetApp()->m_pszRegistryKey,AfxGetApp()->m_pszAppName,subKeyOld[i]);
						ExportRegistryKey(ssss,tmpFileName);
						ssss.Format("Software\\%s\\%s\\COMSETLIST\\%d",AfxGetApp()->m_pszRegistryKey,AfxGetApp()->m_pszAppName,i);
						ImportRegistryKey(ssss,tmpFileName);

						::RegOpenKeyEx(tmpKewList,subKeyOld[i]+6,0,KEY_ALL_ACCESS,&tmpKew);
						if (tmpKew)
						{
							DWORD dwTmpData=i<2?GPCT_COMPORT:GPCT_SOCKET;
							::RegSetValueEx(tmpKew, "com_type", 0, REG_DWORD, (LPBYTE) &dwTmpData, sizeof(DWORD));
							RegCloseKey(tmpKew);
							tmpKew=NULL;
							//if (!dwDisp) RegDeleteKey(tmpMain,subKeyOld[i]);
						}
						DeleteFile(tmpFileName);
					}
				}
			}
			RegCloseKey(tmpMain);
		}
	}
	else RegCloseKey(tmpKew);



	GPC.ParseCommandLine(0x0003,GetCommandLine());

	GPC.dw_StartFlags|=(AfxGetApp()->GetProfileInt(m_Comm.GPSectionName, "m_HideTerminal",0));

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	GPC.m_ErrReport.dwErrorMask=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_ErrReport.dwErrorMask", GPC.m_ErrReport.dwErrorMask);
	GPC.m_BarVisibleFlag=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "BarViewSet",3);
	GPC.m_curOutScrBkg=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_curOutScrBkg",8);

	if (!m_wndToolBar.CreateEx(
		this,
		0,
		CBRS_GRIPPER|CBRS_SIZE_DYNAMIC |WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_BORDER_ANY,
		CRect(1,1,1,1)
		) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle()|CBRS_TOOLTIPS | CBRS_FLYBY|CBRS_BORDER_3D);

	if (!m_wndDevToolBar.CreateEx(
		this,
		0,
		CBRS_GRIPPER|CBRS_SIZE_DYNAMIC |WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_BORDER_ANY,
		CRect(1,1,1,1)
		) ||
		!m_wndDevToolBar.LoadToolBar(IDR_DEVTOOLBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndDevToolBar.SetBarStyle(m_wndDevToolBar.GetBarStyle()|CBRS_TOOLTIPS | CBRS_FLYBY|CBRS_BORDER_3D);

    HBITMAP hbmDev = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
        MAKEINTRESOURCE(IDB_BITMAPTBDEV),
        IMAGE_BITMAP,
        0,0, // cx,cy
        LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS );
    CBitmap bmDev;
    bmDev.Attach(hbmDev);

    // Create image list and set in toolbar.
    // Must use ILC_COLOR8 for 256-color images!
    //
    m_ilDevToolBar.Create(16,16, ILC_COLOR8, 4, 4);
    m_ilDevToolBar.Add(&bmDev,(CBitmap*)NULL);
    m_wndDevToolBar.GetToolBarCtrl().SetImageList(&m_ilDevToolBar);


//////////////	m_wndDevToolBar.SetBarStyle((m_wndDevToolBar.GetBarStyle() & ~CBRS_HIDE_INPLACE)|CBRS_GRIPPER);

    HBITMAP hbm = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
        MAKEINTRESOURCE(IDB_BITMAPTBMF),
        IMAGE_BITMAP,
        0,0, // cx,cy
        LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS );
    CBitmap bm;
    bm.Attach(hbm);

    // Create image list and set in toolbar.
    // Must use ILC_COLOR8 for 256-color images!
    //
    m_ilToolBar.Create(16,16, ILC_COLOR8, 4, 4);
    m_ilToolBar.Add(&bm,(CBitmap*)NULL);
    m_wndToolBar.GetToolBarCtrl().SetImageList(&m_ilToolBar);
	UINT ids[]={
		ID_EDIT_SCREEN_TO_CB,	ID_EDIT_PASTE,	ID_FULLCONTEXTMENU,	ID_SEPARATOR,	IDM_SEPARATEVIEWMODE,
		IDM_SEPARATEVIEWINFRAME,	ID_SEPARATOR,	ID_FILE_PRINT,	ID_SEPARATOR,	ID_BUTTONCALC,
		ID_SEPARATOR,	ID_TERM_SETTINGS,	ID_COMSETTINGSDLG,	ID_SEPARATOR,	ID_HELP_FINDER,
		ID_APP_ABOUT,	ID_SEPARATOR,
	};
	m_wndToolBar.SetButtons(ids,16);



	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME,CBRS_ALIGN_TOP|CBRS_GRIPPER|WS_CHILD, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if (!m_wndReBar.Create(this) /*||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar)*/)
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}
	m_wndReBar.SetBarStyle((m_wndReBar.GetBarStyle() & ~CBRS_HIDE_INPLACE)|CBRS_GRIPPER);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips

	m_wndDlgBar.SetBarStyle(m_wndDlgBar.GetBarStyle()|CBRS_TOOLTIPS | CBRS_FLYBY|CBRS_BORDER_3D);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndDevToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndDlgBar.EnableDocking(CBRS_ALIGN_ANY);

//	GPC.m_BarVisibleFlag=15;

	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndDevToolBar);
	DockControlBar(&m_wndDlgBar);

	try
	{LoadBarState("GPTERMBAR");}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CMainFrame", "OnCreate","");
	}


	UpdateAndRecalc();
	ModifyPrivilege(SE_BACKUP_NAME, TRUE);
	ModifyPrivilege(SE_RESTORE_NAME , TRUE);

	int iVers=AfxGetApp()->GetProfileInt("Version","Counter",-1);
	if (iVers==-1)
	{
		RecalcLayout();
		m_wndDevToolBar.Invalidate();
		AfxGetApp()->WriteProfileInt("Version","Counter",1);
		SaveBarState("GPTERMBAR");
	}

	UpdateAndRecalc();

	m_Comm.ListenPort=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "ListenPort",0);
	m_Comm.ListenTime=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "ListenTime",10);

	GPC.ParseCommandLine(0x0018,GetCommandLine());


#ifdef BRIZ
		{
			HMENU m = ::GetSystemMenu(m_hWnd, FALSE);
			::InsertMenu(m,0,MF_BYPOSITION|MF_SEPARATOR, 0, 0);
			::InsertMenu(m,0, MF_BYPOSITION|MF_ENABLED, ID_BRIZMENUSHOW, "BRIZ main menu");
		}
#endif

	SetTimer(BRIZICON_TIMER_ID, 1000, NULL);
	
	if ((GPC.dw_StartFlags&GP_STRTFLG_HIDE)) SetTimer(BRIZICON_TIMER_IDHIDE, 1, NULL);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

#include "GP_TermDoc.h"
#include "GP_TermView.h"

void CMainFrame::OnClose() 
{
// Выход из программы с посылкой брейка
// OnClose() 
	static int BreakFlag;
	if ((GPC.Flags&GP_CUR_ADDITIONALLOOP)==GP_CUR_ADDITIONALLOOP)
	{
		#ifdef RUS
			if ((GPC.Flags&GP_CUR_EXITFLAG)==GP_CUR_EXITFLAG || MessageBox("В данный момент выполняется COM метод.\n Закончить работу с базой данных?",GPC.MsgBoxCaption,MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2)==IDYES)	
		#else
			if ((GPC.Flags&GP_CUR_EXITFLAG)==GP_CUR_EXITFLAG || MessageBox("COM methods now running.\nClose Program in any case?",GPC.MsgBoxCaption,MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2)==IDYES)	
		#endif
			{
				GPC.Flags|=GP_CUR_LOCKCOM;
				//AfxThrowOleDispatchException(1010,IDS_GPOLEEXEPTION1010);
				::SetTimer(GPC.m_hViewWnd, LOCKCOM_TIMER_ID, 10000, NULL);
			}
	}
	else
	{
		BOOL doClose=FALSE;
		if (BreakFlag==0)
		{
			BreakFlag=1;
			ResetEvent(m_WaitAll);

			//if (AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "IDC_RESTORESIZE",0))
			{
				CRect re;
				GetWindowRect(&re);
				DWORD curStyle=GetWindowLong(m_hWnd,GWL_STYLE);
				if (re.Width()>200 && re.Height()>200 && (curStyle&WS_MINIMIZE)!=WS_MINIMIZE && (curStyle&WS_MAXIMIZE)!=WS_MAXIMIZE)
				{
					AfxGetApp()->WriteProfileInt(GPC.cs_RegTermViewSetName, "RESTORESIZEX",	re.left);
					AfxGetApp()->WriteProfileInt(GPC.cs_RegTermViewSetName, "RESTORESIZEY",	re.top);
					AfxGetApp()->WriteProfileInt(GPC.cs_RegTermViewSetName, "RESTORESIZECX",	re.Width());
					AfxGetApp()->WriteProfileInt(GPC.cs_RegTermViewSetName, "RESTORESIZECY",	re.Height());
				}
			}

			if ((GPC.Flags&GP_CUR_COMMFLAG)==GP_CUR_COMMFLAG)
			{
				if ((GPC.Flags&GP_CUR_EXITFLAG)==GP_CUR_EXITFLAG)
				{
					doClose=TRUE;
				}
				else
				{
					if (
						AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_CheckExitPrg",1) &&  
						#ifdef RUS
							MessageBox("Потеряна связь с сервером\n Закончить работу с базой данных?",
						#else
							MessageBox("Connection lost\n Close program?",
						#endif
						GPC.ErrBoxCaption,MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON1)!=IDYES)
								{m_Comm.GPClose();}
					else
					{
						doClose=TRUE;
					}
				}
			}
			else
			#ifdef RUS
				if ((GPC.Flags&GP_CUR_EXITFLAG)==GP_CUR_EXITFLAG || MessageBox("Закончить работу с базой данных?",GPC.MsgBoxCaption,MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2)==IDYES)	
			#else
				if ((GPC.Flags&GP_CUR_EXITFLAG)==GP_CUR_EXITFLAG || MessageBox("Close Program?",GPC.MsgBoxCaption,MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2)==IDYES)	
			#endif
			{
				GPC.m_Document->RemoveAllDlg();
				if (AfxGetApp()->GetProfileInt(m_Comm.GPSectionName, "m_DontSendStopSeq",0))
				{
					doClose=TRUE;
				}
				else
				{
					if (*m_Comm.GetEndStr()==0)
					{
						m_Comm.GPSendChar(GPC.BreakChar);
						Sleep(1000);
						m_Comm.GPSendLine("exit\r");
						m_Comm.GPSendLine("logout\r");
						if (m_Comm.Get_commType()==GPCT_COMPORT || (GPC.Flags&GP_CUR_EXITFLAG)!=GP_CUR_EXITFLAG)
						{
							m_StopWorking=TRUE;
							if (m_Comm.Get_commType()==GPCT_SOCKET)
							{
								UINT nCount=0;
								int nByte=0;
								CGP_TermView * mvi=(CGP_TermView *)GPC.m_View;

								while(BreakFlag && m_Comm.IsConnected() && (nByte=m_Comm.GPRead(mvi->InputBuffer,10000))!=1234567890 && nCount++<3000)
								{

									MSG msg;
 
									while (PeekMessage(&msg, m_hWnd,  0, 0, PM_REMOVE)) 
									if (msg.message!=WM_CLOSE && msg.message!=WM_QUIT)
									{ 
										TranslateMessage(&msg); 
										DispatchMessage(&msg); 
									} 

									if (nByte>0)
									{
										mvi->RemappingInput(nByte);
										UpdateWindow();
									}
									if (nCount==500)
									{
										m_Comm.GPSendChar('\r');
										Sleep(200);
										m_Comm.GPSendLine("end\r");
										m_Comm.GPSendLine("exit\r");
										m_Comm.GPSendLine("logout\r");
										m_Comm.GPSendLine("Qq\r");
									}
									else
									if (nCount==1000)
									{
										m_Comm.GPSendChar(GPC.BreakChar);
										Sleep(200);
										m_Comm.GPSendLine("end\r");
										m_Comm.GPSendLine("exit\r");
										m_Comm.GPSendLine("logout\r");
										m_Comm.GPSendLine("Qq\r");
										m_Comm.GPSendChar('\r');
									}
									else
									if (nCount==1500)
									{
										m_Comm.GPSendLine("end\r");
										m_Comm.GPSendLine("exit\r");
										m_Comm.GPSendLine("logout\r");
										m_Comm.GPSendLine("Qq\r");
										m_Comm.GPSendChar('\r');
										m_Comm.GPSendLine("exit\r");
									}
									Sleep(3);
								}
							}
							doClose=TRUE;
							//CFrameWnd::OnClose();
						}
					}
					else
					{
						if (m_Comm.Get_commType()==GPCT_COMPORT || (GPC.Flags&GP_CUR_EXITFLAG)!=GP_CUR_EXITFLAG)
						{
							m_StopWorking=TRUE;
							if (m_Comm.Get_commType()==GPCT_SOCKET && AfxGetApp()->GetProfileInt(m_Comm.GPSectionName, "m_DontSendStopSeq",0)==0)
							{
								UINT nCount=0;
								int nByte=0;
								CGP_TermView * mvi=(CGP_TermView *)GPC.m_View;
								GPC.cs_ScriptLine=m_Comm.GetEndStr();
								mvi->DoScriptCommand();

								while(m_Comm.IsConnected() && (nByte=m_Comm.GPRead(mvi->InputBuffer,10000))!=1234567890 && nCount++<3000)
								{
									if (nByte>0)
									{
										mvi->RemappingInput(nByte);
										UpdateWindow();
									}
									Sleep(5);
								}
							}
							doClose=TRUE;
							//CFrameWnd::OnClose();
						}
					}
				}
			}
			if (doClose)
			{
			#ifdef W_95
			#else
			#ifdef W_NT
			#else
	        #ifdef W_98
			#else
				CString tmpCS=AfxGetApp()->GetProfileString(m_Comm.GPSectionName, "SHDNSVC","");
				tmpCS=tmpCS.Trim();
				int nTermInst=0;
				if (tmpCS!="")
				{
					IMoniker* pmon;
					IBindCtx* pBind;
					IRunningObjectTable* prot;
					HRESULT hr;
					LPOLESTR pName;
					IEnumMoniker *pem;
					hr=::CreateBindCtx(0,&pBind);
					if (SUCCEEDED(hr))
					{
						hr = pBind->GetRunningObjectTable (&prot);
						if (SUCCEEDED(hr))
						{
							hr = prot->EnumRunning(&pem);
							if (SUCCEEDED(hr))
							{
								pem->Reset();
								ULONG fetched;
								while(nTermInst<2 && pem->Next(1, &pmon, &fetched) == S_OK)
								{
									hr=pmon->GetDisplayName(pBind, NULL, &pName);
									if (!wcsncmp(L"GPT_",pName,4))
										nTermInst++;
									pmon->Release();
								}
								pem->Release();
							}
							prot->Release();
						}
						pBind->Release();
					}
					if (nTermInst<2)
					{
						SC_HANDLE schSCManager=OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);
						SC_HANDLE schService;
						SERVICE_STATUS_PROCESS ssStatus; 
						DWORD dwTickCount=0;
						DWORD dwBytesNeeded;
						if (schSCManager)
						{
							schService = OpenService(schSCManager, tmpCS, SERVICE_ALL_ACCESS); 
							if (	schService
									&& QueryServiceStatusEx(schService, SC_STATUS_PROCESS_INFO,(LPBYTE)&ssStatus, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded )
									&& ssStatus.dwCurrentState != SERVICE_STOPPED) 
							{
								switch(ssStatus.dwCurrentState)
								{
								case SERVICE_PAUSE_PENDING:
									while (dwTickCount++<50 && ssStatus.dwCurrentState == SERVICE_PAUSE_PENDING) 
									{ 
										Sleep( 500 );
										if (!QueryServiceStatusEx(schService,SC_STATUS_PROCESS_INFO,(LPBYTE)&ssStatus, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded ) )
											ssStatus.dwCurrentState=SERVICE_STOPPED;
									}
									dwTickCount=0;
								case SERVICE_PAUSED:
								case SERVICE_STOPPED:
									break;
								case SERVICE_START_PENDING:
								case SERVICE_CONTINUE_PENDING:
									while (dwTickCount++<50 && (ssStatus.dwCurrentState == SERVICE_START_PENDING || ssStatus.dwCurrentState == SERVICE_CONTINUE_PENDING)) 
									{ 
										Sleep( 500 );
										if (!QueryServiceStatusEx(schService,SC_STATUS_PROCESS_INFO,(LPBYTE)&ssStatus, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded ) )
											ssStatus.dwCurrentState=SERVICE_STOPPED;
									}
								default:
									//SERVICE_RUNNING
									dwTickCount=0;
									if (ssStatus.dwCurrentState != SERVICE_STOP_PENDING)
									{
										CString tmpMsg;
										tmpMsg.Format("Stop service %s?",tmpCS);
										if (AfxGetApp()->GetProfileInt(m_Comm.GPSectionName, "CHECKSVCASK",0)
											&& AfxMessageBox(tmpMsg,MB_YESNO|MB_APPLMODAL|MB_ICONQUESTION|MB_DEFBUTTON1)!=IDYES)
												dwTickCount=1000000;
										else	ControlService(schService,SERVICE_CONTROL_STOP,(LPSERVICE_STATUS)&ssStatus);
									}

									while (dwTickCount++<50 && ssStatus.dwCurrentState != SERVICE_STOPPED) 
									{ 
										Sleep( 500 );
										if (!QueryServiceStatusEx(schService,SC_STATUS_PROCESS_INFO,(LPBYTE)&ssStatus, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded ) )
											ssStatus.dwCurrentState=SERVICE_STOPPED;
									}
									dwTickCount=0;
									break;
								}
								CloseServiceHandle(schService); 
							}

						}
						CloseServiceHandle(schSCManager);
					}
				}
			#endif
			#endif
			#endif

				NOTIFYICONDATA tnd;
				tnd.cbSize=sizeof(tnd);
				tnd.hWnd=AfxGetMainWnd()->m_hWnd;
				tnd.uID=IDR_GP_TERTYPE;
				tnd.uFlags=NIF_MESSAGE;
				tnd.uCallbackMessage=GPM_NOTFYTASKBAR;
				Shell_NotifyIcon(NIM_DELETE,&tnd);

				GPC.m_Document->RemoveAllDlg();
				m_StopWorking=TRUE;
				CFrameWnd::OnClose();

				DWORD dwSHUTDOWN=AfxGetApp()->GetProfileInt(m_Comm.GPSectionName, "m_ShutdownFlags",0x1000);
				if ((dwSHUTDOWN&0x1)==0x1) 
				{
					DWORD dwType[]={EWX_LOGOFF,EWX_POWEROFF,EWX_REBOOT,EWX_SHUTDOWN,};
					DWORD dwSubType[]={0,EWX_FORCE,EWX_FORCEIFHUNG,};
					DWORD tmpDW=(dwSHUTDOWN/0x100)&0x3;
			#ifdef W_95
						ExitWindowsEx(dwType[(dwSHUTDOWN/0x10)&0x3]|dwSubType[tmpDW],SHTDN_REASON_MAJOR_APPLICATION|SHTDN_REASON_MINOR_MAINTENANCE);
			#else
				#ifdef W_98
						ExitWindowsEx(dwType[(dwSHUTDOWN/0x10)&0x3]|dwSubType[tmpDW],SHTDN_REASON_MAJOR_APPLICATION|SHTDN_REASON_MINOR_MAINTENANCE);
				#else

					if (tmpDW<3)
					{
						ExitWindowsEx(dwType[(dwSHUTDOWN/0x10)&0x3]|dwSubType[tmpDW],SHTDN_REASON_MAJOR_APPLICATION|SHTDN_REASON_MINOR_MAINTENANCE);
					}
					else
					{
						#ifdef W_95
						#else
							#ifdef W_NT
							#else
								#ifdef W_98
								#else
									LockWorkStation();
								#endif
							#endif
						#endif
					}
				#endif
			#endif
				}
			}
			SetEvent(m_WaitAll);
		}
		BreakFlag=0;
	}
}


BOOL CMainFrame::OnQueryEndSession() 
{
	BOOL ret=TRUE;
	DWORD dwSHUTDOWN=AfxGetApp()->GetProfileInt(m_Comm.GPSectionName, "m_ShutdownFlags",0x1000);
	GPC.m_ErrReport.GPWriteWarnLog("Windows System", "Query End Session","");
	if ((dwSHUTDOWN&0x1000)==0x1000) 
	{
		ret=FALSE;
	}
	
	return ret;
}


void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CFrameWnd::OnShowWindow(bShow, nStatus);
}

LRESULT CMainFrame::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	BOOL bDoDefault=TRUE;
	LRESULT lr=FALSE;

	switch(message)
	{
	//case WM_QUERYENDSESSION:
	//	break;

#ifdef BRIZ
	case WM_SYSCOMMAND:
		if (wParam==ID_BRIZMENUSHOW)
		{
			UpdateDialogControls(this,FALSE);
			HMENU tmpMenu=::GetMenu(m_hWnd);
			HMENU p;
			p = ::CreatePopupMenu();
			UINT nItems=::GetMenuItemCount(tmpMenu);
			UINT i;
			for(i=0;i<nItems;i++)
			{
				char tmps[222];
				::GetMenuString(tmpMenu,i,tmps,200,MF_BYPOSITION);
				HMENU tmpContext=::GetSubMenu(tmpMenu,i);
				if (tmpContext)
					::AppendMenu(p, MF_BYPOSITION|MF_POPUP | MF_ENABLED | MF_STRING, (UINT) tmpContext, tmps);
				else
					::AppendMenu(p, MF_ENABLED, ::GetMenuItemID(tmpMenu,i), tmps);
			}

			POINT po={0};
			GetCursorPos(&po);
			::TrackPopupMenu(p,TPM_VERNEGANIMATION|TPM_VERNEGANIMATION|TPM_LEFTALIGN|TPM_BOTTOMALIGN,po.x,po.y,0,GPC.m_hViewWnd,NULL);

			for(i=0;i<nItems;i++)
				::RemoveMenu(p,0,MF_BYPOSITION);
			::DestroyMenu(p);
		}
		break;
#endif
	case GPM_NOTFYTASKBAR:
		if (lParam==WM_LBUTTONDBLCLK && wParam==IDR_GP_TERTYPE)
		{
			ShowWindow(SW_RESTORE);
			SetForegroundWindow();
			if (GPC.m_hViewWnd!=NULL) 
				::SetFocus(GPC.m_hViewWnd);
		}
		else
		if (lParam==WM_RBUTTONUP && wParam==IDR_GP_TERTYPE)
			::PostMessage(m_hWnd,WM_SYSCOMMAND,ID_BRIZMENUSHOW,NULL);
		break;
	}
	return (bDoDefault)?CFrameWnd::DefWindowProc(message, wParam, lParam):lr;
}

BOOL CMainFrame::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	return CFrameWnd::OnHelpInfo(pHelpInfo);
}

void CMainFrame::OnViewStatusBar() 
{
	GPC.m_BarVisibleFlag^=0x2;
	CheckAndUpdateBars();
}

void CMainFrame::OnViewToolbar() 
{
	GPC.m_BarVisibleFlag^=0x1;
	CheckAndUpdateBars();
}

void CMainFrame::OnViewDevtoolbar() 
{
	if (GPC.AdmIsOn)
	{
		GPC.m_BarVisibleFlag^=0x4;
		CheckAndUpdateBars();
	}
	else
	if ((GPC.m_BarVisibleFlag&0x4)) 
	{
		GPC.m_BarVisibleFlag&=(0xFFFFFFFF^0x4);
		CheckAndUpdateBars();
	}
}

void CMainFrame::OnUpdateTranslateTcl(CCmdUI* pCmdUI) 
{
	try
	{
		if (pCmdUI->m_pMenu) GPC.m_View->UpdateMenuByAdm();
		if (!GPC.AdmIsOn && (GPC.m_BarVisibleFlag&0x4)) 
		{
			GPC.m_BarVisibleFlag&=(0xFFFFFFFF^0x4);
			CheckAndUpdateBars();
		}
		pCmdUI->SetCheck(GPC.EasyTCL);

		const char *ccnewtext="";
		if (GPC.EasyTCL)
			ccnewtext="ETCL ON\x3 MAINIL\x3 29";
		else
			ccnewtext="ETCL OFF\x3 MAINIL\x3 29";

		if (!pCmdUI->m_pMenu)
			pCmdUI->SetText(ExtractField(ccnewtext,1,"\x3"));
		else
		{
			MENUITEMINFO mii={0};
			mii.cbSize=sizeofMENUITEMINFO;
			mii.fMask=MIIM_DATA;
			if (::GetMenuItemInfo(pCmdUI->m_pMenu->m_hMenu,pCmdUI->m_nIndex,TRUE,&mii))
				GPC.m_View->m_GPMenu->MENUINFOArray[mii.dwItemData].csText=ccnewtext;
		}

	}catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CMainFrame", "OnUpdateTranslateTcl","");
	}
}

void CMainFrame::OnUpdateKeyblock(CCmdUI* pCmdUI) 
{
	try
	{
		m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_TERMINALTYPE),GPC.m_View && m_TermCap.GetCurrentTerminal()?m_TermCap.GetCurrentTerminal()->TerminalName:"UNKNOWN");
		GPStatusBarCtrl::OptimizeSize(m_wndStatusBar.GetStatusBarCtrl().m_hWnd,-1);
	}catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CMainFrame", "OnUpdateKeyblock","");
	}

	try
	{
		if (GPC.m_Document)
		{
			Size sz=GPC.m_Document->GetActiveScrSize();
			char tmps[100];
			sprintf(tmps,"%dx%d",sz.Width,sz.Height);
			m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_SCREENSIZE),tmps);
			GPStatusBarCtrl::OptimizeSize(m_wndStatusBar.GetStatusBarCtrl().m_hWnd,-1);
		}
	}catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CMainFrame", "OnUpdateKeyblock","");
	}
	

	GPC.m_ErrReport.SetIcon(m_hWnd,0);

	try
	{
		m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_OVR),GPC.m_bInsertMode?"OVR":"INS");
		CMenu *mmnu=GetMenu();
		if (mmnu)
		{
			const char *ccnewtext="";
			if (GPC.AjCheckState==0)
			#ifdef RUS
					ccnewtext="Заблокировать клавиатуру\x3 MAINIL\x3 28";
				else
					ccnewtext="Разблокировать клавиатуру\x3 MAINIL\x3 28";
			#else
					ccnewtext="Lock Keyboard\x3 MAINIL\x3 28";
				else
					ccnewtext="Unlock Keyboard\x3 MAINIL\x3 28";
			#endif

			MENUITEMINFO mii={0};
			mii.cbSize=sizeofMENUITEMINFO;
			mii.fMask=MIIM_DATA;
			if (::GetMenuItemInfo(mmnu->m_hMenu,ID_KEYBLOCK,FALSE,&mii))
				GPC.m_View->m_GPMenu->MENUINFOArray[mii.dwItemData].csText=ccnewtext;
		}
		m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_KEYBLOCK),GPC.AjCheckState==0?"":"LOCK");
	}catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CMainFrame", "OnUpdateKeyblock 788","");
	}


	try
	{
		GPScreen *s;
		GPWindow *w;
		if (GPC.m_Document && (s=GPC.m_Document->GetActiveScreen()) && (w=s->GPActiveWindow()))
		{
			const char *ccTxt="    ";
			if (w->m_ProtectedModeFlag) ccTxt="PROTECTED MODE";
			if (w->m_ProtectedFieldModeFlag) ccTxt="PROTECTED FIELDS";
			m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_PROTERTFIELDS),ccTxt);
		}
	}catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CMainFrame", "OnUpdateKeyblock 805","");
	}


}

void CMainFrame::OnEnterIdle(UINT nWhy, CWnd* pWho) 
{
	CFrameWnd::OnEnterIdle(nWhy, pWho);
}


void CMainFrame::OnUpdateViewDevtoolbar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_wndDevToolBar.GetStyle()&WS_VISIBLE)==WS_VISIBLE);
}

void CMainFrame::OnUpdateViewToolbar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_wndToolBar.GetStyle()&WS_VISIBLE)==WS_VISIBLE);

}

void CMainFrame::UpdateAndRecalc()
{
	LoadBarState("GPTERMBAR");

	if ((GPC.m_BarVisibleFlag&0x1))
	{
		m_wndToolBar.ModifyStyle(0,WS_VISIBLE,SWP_FRAMECHANGED);
		m_wndToolBar.Invalidate();
	}
	else
		m_wndToolBar.ModifyStyle(WS_VISIBLE,0,SWP_FRAMECHANGED);

	if ((GPC.m_BarVisibleFlag&0x2))
	{
		m_wndStatusBar.ModifyStyle(0,WS_VISIBLE,SWP_FRAMECHANGED);
		m_wndStatusBar.Invalidate();
	}
	else
		m_wndStatusBar.ModifyStyle(WS_VISIBLE,0,SWP_FRAMECHANGED);

	if ((GPC.m_BarVisibleFlag&0x4))
	{
		m_wndDevToolBar.ModifyStyle(0,WS_VISIBLE,SWP_FRAMECHANGED);
		m_wndDevToolBar.Invalidate();
	}
	else
		m_wndDevToolBar.ModifyStyle(WS_VISIBLE,0,SWP_FRAMECHANGED);

	if ((GPC.m_BarVisibleFlag&0x8))
	{
		m_wndDlgBar.ModifyStyle(0,WS_VISIBLE,SWP_FRAMECHANGED);
		m_wndDlgBar.Invalidate();
	}
	else
		m_wndDlgBar.ModifyStyle(WS_VISIBLE,0,SWP_FRAMECHANGED);

	RecalcLayout();	
	Invalidate();
}

void CMainFrame::OnDropFiles(HDROP hDropInfo) 
{

	//CFrameWnd::OnDropFiles(hDropInfo);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	RecalcLayout();
	::PostMessage(GPC.m_hViewWnd,GPM_MFUPDATESIZE,0,nType);
}

void CMainFrame::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CFrameWnd::OnSizing(fwSide, pRect);
	RecalcLayout();
	::PostMessage(GPC.m_hViewWnd,GPM_MFUPDATESIZE,1,fwSide);
}

#include "GPContextMenu.h"

void CMainFrame::OnFullcontextmenu() 
{
	RECT re={0};
	m_wndToolBar.GetToolBarCtrl().GetRect(ID_FULLCONTEXTMENU,&re);
	m_wndToolBar.GetToolBarCtrl().ClientToScreen(&re);
	TrackPopupMenu(GPC.m_pContextMenu->m_Menu,TPM_RIGHTBUTTON|TPM_TOPALIGN|TPM_LEFTALIGN|TPM_HORNEGANIMATION,re.right,re.bottom,0,GPC.m_hViewWnd,NULL);
}


BOOL CMainFrame::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	LPNMHDR pnmh = (LPNMHDR) lParam;
	if (pnmh)
	{
		LPNMMOUSE lpn=(LPNMMOUSE)lParam;
		switch(pnmh->code)
		{
		case NM_CLICK:
			if (pnmh->hwndFrom==m_wndStatusBar.m_hWnd)
			{
				switch(lpn->dwItemSpec)
				{
				case 0://ID_SEPARATOR
					break;
				case 1://ID_INDICATOR_OVR
					break;
				case 2://PROTECTED FIELD ID_PROTERTFIELDS
					try
					{
						GPScreen *s;
						GPWindow *w;
						if (GPC.m_Document && (s=GPC.m_Document->GetActiveScreen()) && (w=s->GPActiveWindow()))
						{
							if (w->m_ProtectedModeFlag)
							{
								w->m_ProtectedModeFlag=0;
								w->m_ProtectedFieldModeFlag=0;
								w->SetStyleToChars(GP_FNT_FIXED, 0, 0xFFFF);
							}
							else
							{
								w->m_ProtectedModeFlag|=GP_FNT_FIXED;
								w->m_ProtectedFieldModeFlag|=GP_FNT_FIXED;
								w->SetStyleToChars( 0, GP_FNT_FIXED, ' ');
							}
						}
					}catch(...)
					{
						GPC.m_ErrReport.GPWriteErrorLog("CMainFrame", "OnNotify","");
					}
					break;
				case 3: // LOCK ID_KEYBLOCK
					GPC.AjCheckState=1-GPC.AjCheckState;
					break;
				case 4: // ETCL ID_TRANSLATE_TCL
					GPC.EasyTCL=GPC.EasyTCL?false:true;
					break;
				case 5:// ID_INDICATOR_CAPS
					break;
				case 6:// ID_INDICATOR_NUM
					break;
				case 7:// ID_SCREENSIZE
					{
						CMenu *tmpMain=AfxGetMainWnd()->GetMenu();
						if (tmpMain) 
						{
							int pos;
							CMenu *tmpTrack=NULL;
							for(pos=tmpMain->GetMenuItemCount()-1;pos>=0 && !tmpTrack;pos--)
							{
								CMenu *tmpm=tmpMain->GetSubMenu(pos);
								if (tmpm)
								{
									int pos2;
									for(pos2=tmpm->GetMenuItemCount()-1;pos2>=0 && !tmpTrack;pos2--)
									{
										CMenu *tmpm2=tmpm->GetSubMenu(pos2);
										if (tmpm2)
										{
											int pos3;
											for(pos3=tmpm2->GetMenuItemCount()-1;pos3>=0 && !tmpTrack;pos3--)
												if (tmpm2->GetMenuItemID(pos3)==ID_SCRSIZE79X24)  tmpTrack=tmpm2;
										}
										else 
											if (tmpm->GetMenuItemID(pos2)==ID_SCRSIZE80X25)  tmpTrack=tmpm;
									}
								}
							}
							if (tmpTrack)
							{
								RECT re={0};
								m_wndStatusBar.GetItemRect(m_wndStatusBar.CommandToIndex(ID_SCREENSIZE),&re);
								m_wndStatusBar.ClientToScreen(&re);
								tmpTrack->TrackPopupMenu(TPM_LEFTALIGN,re.left,re.top,GPC.m_View);
							}
						}
					}
					break;
				case 0xfffffffe: 
					{
						RECT re={0};
						m_wndStatusBar.GetItemRect(m_wndStatusBar.CommandToIndex(ID_TERMINALTYPE),&re);
						if (re.top<=lpn->pt.y && re.bottom>=lpn->pt.y && re.left<=lpn->pt.x && re.right+20>=lpn->pt.x)
						{
							m_wndStatusBar.ClientToScreen(&re);
							DWORD newId=m_TermCap.SelectTerminal(re.left,re.top);
							if (newId!=DWORD_MINUS_ONE)
								m_TermCap.SetCurrentTerminalId(newId);
						}
					}
					break;

				case 8: // TERMINAL ID_TERMINALTYPE
					{
						RECT re={0};
						m_wndStatusBar.GetItemRect(m_wndStatusBar.CommandToIndex(ID_TERMINALTYPE),&re);
						m_wndStatusBar.ClientToScreen(&re);
						DWORD newId=m_TermCap.SelectTerminal(re.left,re.top);
						if (newId!=DWORD_MINUS_ONE)
							m_TermCap.SetCurrentTerminalId(newId);
					}
					break;
				}
			}
			break;
		default:
			break;
		}
	}
	return CFrameWnd::OnNotify(wParam, lParam, pResult);
}

void CMainFrame::OnStatistic() 
{
	if (GPC.DlgStatistics)
	{
		if (GPC.DlgStatistics->m_hWnd==NULL) GPC.DlgStatistics->Create(IDD_DLGSTATISTICS,this);
		if (GPC.DlgStatistics->m_hWnd)
			GPC.DlgStatistics->ShowWindow(SW_SHOW);
	}
}

void CMainFrame::OnUpdateStatistic(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
}

void CMainFrame::OnDestroy() 
{
	if (m_ilToolBar.m_hImageList)
		m_ilToolBar.DeleteImageList();
	if (m_ilDevToolBar.m_hImageList)
		m_ilDevToolBar.DeleteImageList();
	CFrameWnd::OnDestroy();
}

LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch(message)
	{
	case WM_DRAWITEM:
		if (lParam)
		{
			LPDRAWITEMSTRUCT lpds=(LPDRAWITEMSTRUCT) lParam;
			if (lpds->CtlType==ODT_MENU)
			{
				GPUnit *gpu=GPC.m_Document->GetMainScreen()->GPGetWindowByNum(0)->GetUnitByNum(0);
				if (gpu)
				{
					GPC.m_View->m_ODContextsArray->PaintByDRAWITEMSTRUCT(gpu, wParam, lpds, GPC.m_View->m_GPMenu);
					return TRUE;
				}
			}
			else
			{
				GPUnit *gpu=GPC.m_Document->GetMainScreen()->GPGetWindowByNum(0)->GetUnitByNum(lpds->CtlID%50000);
				if (gpu && gpu->UnitType!=GPUnit::UT_CHECKLISTBOX)
				{
					GPC.m_View->m_ODContextsArray->PaintByDRAWITEMSTRUCT(gpu, wParam, lpds, GPC.m_View->m_GPMenu);
					return TRUE;
				}
			}
		}
		break;

	case WM_MEASUREITEM:
		if (lParam)
		{
			LPMEASUREITEMSTRUCT lpds=(LPMEASUREITEMSTRUCT) lParam;
			if (lpds->CtlType==ODT_MENU)
			{
				GPUnit *gpu=GPC.m_Document->GetMainScreen()->GPGetWindowByNum(0)->GetUnitByNum(0);
				if (gpu)
				{
					return GPC.m_View->m_ODContextsArray->MeasureItem(gpu, wParam, lpds, GPC.m_View->m_GPMenu);
				}
			}
			else
			{
				HWND ctrlHWND=::GetDlgItem(m_hWnd,lpds->CtlID);
				if (ctrlHWND)
				{
					GPUnit *gpu=GPC.m_Document->GetMainScreen()->GPGetWindowByNum(0)->GetUnitByNum(lpds->CtlID%50000);
					if (gpu && gpu->UnitType!=GPUnit::UT_CHECKLISTBOX)
					{
						return GPC.m_View->m_ODContextsArray->MeasureItem(gpu, wParam, lpds, GPC.m_View->m_GPMenu);
					}
				}
			}
		}
		break;

	case GPM_MFUPDATEBARS:
		CheckAndUpdateBars();
		return 0;
		break;

	case WM_TIMER:
		switch(wParam)
		{
		case BRIZICON_TIMER_IDHIDE:
		case BRIZICON_TIMER_ID:
			{
				if (wParam==BRIZICON_TIMER_IDHIDE) KillTimer(BRIZICON_TIMER_IDHIDE);
				static BOOL bLastShowState;
				BOOL bVisible=::IsWindowVisible(m_hWnd);
				if (bVisible!=bLastShowState || !bVisible)
				{
					NOTIFYICONDATA tnd;
					tnd.cbSize=sizeof(tnd);
					tnd.hWnd=AfxGetMainWnd()->m_hWnd;
					tnd.uID=IDR_GP_TERTYPE;
					tnd.uCallbackMessage=GPM_NOTFYTASKBAR;
					tnd.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP;
					lstrcpyn(tnd.szTip,GPC.TermTip,sizeof(tnd.szTip));

					SYSTEMTIME mst={0};
					GetSystemTime(&mst);
					if (( GPC.m_ErrReport.dwErrorFlag & GPC.m_ErrReport.dwErrorMask) && (mst.wSecond&0x1))
						tnd.hIcon= GPC.m_ErrReport.hiWarn;
					else
						tnd.hIcon= GPC.m_ErrReport.hiNormal;

					if (bVisible) Shell_NotifyIcon(NIM_DELETE,&tnd);

					if ((!bVisible && bLastShowState) || wParam==BRIZICON_TIMER_IDHIDE)
						Shell_NotifyIcon(NIM_ADD,&tnd);
					else
						if (!bVisible)	Shell_NotifyIcon(NIM_MODIFY,&tnd);

					bLastShowState=bVisible;
				}
			}
			break;
		}
		break;
	}
	
	return CFrameWnd::WindowProc(message, wParam, lParam);
}

void CMainFrame::ActivateFrame(int nCmdShow) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (!(GPC.dw_StartFlags&GP_STRTFLG_HIDEONCE) && (GPC.dw_StartFlags&GP_STRTFLG_HIDE)) nCmdShow=0;
	GPC.dw_StartFlags|=GP_STRTFLG_HIDEONCE;
	CFrameWnd::ActivateFrame(nCmdShow);
}

void CMainFrame::CheckAndUpdateBars(DWORD dwFlags)
{
	DWORD dwstl;
	BOOL bupdate=FALSE;

	dwstl=m_wndStatusBar.GetStyle()&WS_VISIBLE;
	if ((dwstl && !(GPC.m_BarVisibleFlag&0x2)) || (!dwstl && (GPC.m_BarVisibleFlag&0x2)))
	{
		m_wndStatusBar.ModifyStyle(dwstl,dwstl^WS_VISIBLE,SWP_FRAMECHANGED);
		bupdate=TRUE;
	}

	dwstl=m_wndToolBar.GetStyle()&WS_VISIBLE;
	if ((dwstl && !(GPC.m_BarVisibleFlag&0x1)) || (!dwstl && (GPC.m_BarVisibleFlag&0x1)))
	{
		m_wndToolBar.ModifyStyle(dwstl,dwstl^WS_VISIBLE,SWP_FRAMECHANGED);
		bupdate=TRUE;
	}

	dwstl=m_wndDevToolBar.GetStyle()&WS_VISIBLE;
	if ((dwstl && !(GPC.m_BarVisibleFlag&0x4)) || (!dwstl && (GPC.m_BarVisibleFlag&0x4)))
	{
		m_wndDevToolBar.ModifyStyle(dwstl,dwstl^WS_VISIBLE,SWP_FRAMECHANGED);
		bupdate=TRUE;
	}

	if (bupdate || (dwFlags&0x0001))
	{
		RecalcLayout();	
		Invalidate();
		m_wndStatusBar.Invalidate();
		m_wndToolBar.Invalidate();
		m_wndDevToolBar.Invalidate();
		SaveBarState("GPTERMBAR");
		GPC.SaveBarVisibleFlag();
	}
}
