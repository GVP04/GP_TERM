// DlgViewSystemMethods.cpp : implementation file
//
#include "stdafx.h"
#include "gp_term.h"
#include "GP_TermView.h"
#include "GP_TermDoc.h"
#include "DlgViewSystemMethods.h"
#include "Iphlpapi.h"
#include "GPContextMenu.h"
#include "DlgNotepadSet.h"
#include "ProcMonitor.h"

#include "GPCurrent.h"
#include "GPUnit.h"
#include "GPFrameWnd.h"
#include "GP_comm.h"
#include "GPChLBox.h"
#include "GPDrLBox.h"
#include "GPStatic.h"
#include "GPAniStatic.h"
#include "GPEdit.h"
#include "GPButton.h"
#include "GPAniButton.h"
#include "GPBButton.h"
#include "GPListBox.h"
#include "GPComboBox.h"
#include "GPComboBoxEx.h"
#include "GPScrollBar.h"
#include "GPProgress.h"
#include "GPAnimate.h"
#include "GPListCtr.h"
#include "GPDateTimeCtrl.h"
#include "GPMonthCalCtrl.h"
#include "GPSpinButton.h"
#include "GPTabCtrl.h"
#include "GPSlider.h"
#include "GPHeader.h"
#include "GPTree.h"
#include "GP_RTF.h"
#include "GPDlgBar.h"
#include "GPFrameBar.h"
#include "GPStatusBarCtrl.h"
#include "GPStatusBar.h"
#include "GPToolBarCtrl.h"
#include "GPToolBar.h"
#include "GPDialogBar.h"
#include "GPReBarCtrl.h"
#include "GPReBar.h"
#include "GPObjDialog.h"
#include "GPDrawWnd.h"
#include "gpmsflexgrid.h"
#include "GPWebBrowser2.h"
#include "GPScintilla.h"
#include "GPToolTipCtrl.h"
#include "GP_Control.h"
#include "Security.h"



#define GAA_FLAG_SKIP_UNICAST       0x0001
#define GAA_FLAG_SKIP_ANYCAST       0x0002
#define GAA_FLAG_SKIP_MULTICAST     0x0004
#define GAA_FLAG_SKIP_DNS_SERVER    0x0008
#define GAA_FLAG_INCLUDE_PREFIX     0x0010
#define GAA_FLAG_SKIP_FRIENDLY_NAME 0x0020
#define PROTO_IP_OTHER      1
#define PROTO_IP_LOCAL      2
#define PROTO_IP_NETMGMT    3
#define PROTO_IP_ICMP       4
#define PROTO_IP_EGP        5
#define PROTO_IP_GGP        6
#define PROTO_IP_HELLO      7
#define PROTO_IP_RIP        8
#define PROTO_IP_IS_IS      9
#define PROTO_IP_ES_IS      10
#define PROTO_IP_CISCO      11
#define PROTO_IP_BBN        12
#define PROTO_IP_OSPF       13
#define PROTO_IP_BGP        14
#define PROTO_IP_MSDP        9
#define PROTO_IP_IGMP       10
#define PROTO_IP_BGMP       11
#define PROTO_IP_VRRP               112
#define PROTO_IP_BOOTP              9999    // 0x0000270F
#define PROTO_IP_NT_AUTOSTATIC      10002   // 0x00002712
#define PROTO_IP_DNS_PROXY          10003   // 0x00002713
#define PROTO_IP_DHCP_ALLOCATOR     10004   // 0x00002714
#define PROTO_IP_NAT                10005   // 0x00002715
#define PROTO_IP_NT_STATIC          10006   // 0x00002716
#define PROTO_IP_NT_STATIC_NON_DOD  10007   // 0x00002717
#define PROTO_IP_DIFFSERV           10008   // 0x00002718
#define PROTO_IP_MGM                10009   // 0x00002719
#define PROTO_IP_ALG                10010   // 0x0000271A
#define PROTO_IP_H323               10011   // 0x0000271B
#define PROTO_IP_FTP                10012   // 0x0000271C
#define PROTO_IP_DTP                10013   // 0x0000271D
#define PROTO_TYPE_UCAST            0
#define PROTO_TYPE_MCAST            1
#define PROTO_TYPE_MS0              2
#define PROTO_TYPE_MS1              3
#define IPX_PROTOCOL_BASE   0x0001ffff
#define IPX_PROTOCOL_RIP    IPX_PROTOCOL_BASE + 1
#define IPX_PROTOCOL_SAP    IPX_PROTOCOL_BASE + 2
#define IPX_PROTOCOL_NLSP   IPX_PROTOCOL_BASE + 3
#define AF_ATM          22  
#define AF_INET6        23  
#define AF_CLUSTER      24  
#define AF_12844        25  
#define AF_IRDA         26  
#define AF_NETDES       28  
                            
#define AF_TCNPROCESS   29
#define AF_TCNMESSAGE   30
#define AF_ICLFXBM      31

char CDlgViewSystemMethods::tmpRetStr[256];

DWORD adwSSPServiceFlags[]={SERVICE_RUNS_IN_SYSTEM_PROCESS,0,};
const char *acSSPServiceFlags[]={"SERVICE_RUNS_IN_SYSTEM_PROCESS","",};

DWORD adwSSPControlsAccepted[]={
	SERVICE_ACCEPT_STOP,SERVICE_ACCEPT_PAUSE_CONTINUE,SERVICE_ACCEPT_SHUTDOWN,SERVICE_ACCEPT_PARAMCHANGE,SERVICE_ACCEPT_NETBINDCHANGE,
	SERVICE_ACCEPT_HARDWAREPROFILECHANGE,SERVICE_ACCEPT_POWEREVENT,SERVICE_ACCEPT_SESSIONCHANGE,0,
};
const char *acSSPControlsAccepted[]={
	"ACCEPT_STOP","ACCEPT_PAUSE_CONTINUE","ACCEPT_SHUTDOWN","ACCEPT_PARAMCHANGE","ACCEPT_NETBINDCHANGE",
	"ACCEPT_HARDWAREPROFILECHANGE","ACCEPT_POWEREVENT","ACCEPT_SESSIONCHANGE","",
};

DWORD adwSSPServiceType[]={
	SERVICE_KERNEL_DRIVER,SERVICE_FILE_SYSTEM_DRIVER,SERVICE_ADAPTER,SERVICE_RECOGNIZER_DRIVER,SERVICE_DRIVER,
	SERVICE_WIN32_OWN_PROCESS,SERVICE_WIN32_SHARE_PROCESS,SERVICE_WIN32,SERVICE_INTERACTIVE_PROCESS,0,
};

const char *acSSPServiceType[]={
	"KERNEL_DRIVER","FILE_SYSTEM_DRIVER","ADAPTER","RECOGNIZER_DRIVER","DRIVER",
	"WIN32_OWN_PROCESS","WIN32_SHARE_PROCESS","WIN32","INTERACTIVE_PROCESS","",
};

DWORD adwSSPCurrentState[]={
	SERVICE_STOPPED,SERVICE_START_PENDING,SERVICE_STOP_PENDING,SERVICE_RUNNING,SERVICE_CONTINUE_PENDING,
	SERVICE_PAUSE_PENDING,SERVICE_PAUSED,0,
};

const char *acSSPCurrentState[]={
	"STOPPED","START_PENDING","STOP_PENDING","RUNNING","CONTINUE_PENDING",
	"PAUSE_PENDING","PAUSED","",
};

DWORD adwSSPServiceState[]={
	SERVICE_ACTIVE,SERVICE_INACTIVE,SERVICE_STATE_ALL,0,
};

const char *acSSPServiceState[]={
	"ACTIVE","INACTIVE","ALL","",
};

DWORD adwSCMDesiredAccess[]={
	SC_MANAGER_ALL_ACCESS,SC_MANAGER_CREATE_SERVICE,SC_MANAGER_CONNECT,SC_MANAGER_ENUMERATE_SERVICE,
	SC_MANAGER_LOCK,SC_MANAGER_MODIFY_BOOT_CONFIG,SC_MANAGER_QUERY_LOCK_STATUS,0,
};

const char *acSCMDesiredAccess[]={
	"ALL_ACCESS","CREATE_SERVICE","CONNECT","ENUMERATE_SERVICE",
	"LOCK","MODIFY_BOOT_CONFIG","QUERY_LOCK_STATUS","",
};

DWORD adwPIPortType[]={
	PORT_TYPE_WRITE,PORT_TYPE_READ,PORT_TYPE_REDIRECTED,PORT_TYPE_NET_ATTACHED,0,
};
const char *acPIPortType[]={
	"PORT_TYPE_WRITE","PORT_TYPE_READ","PORT_TYPE_REDIRECTED","PORT_TYPE_NET_ATTACHED","",
};

const char *CDlgViewSystemMethods::chMetricsNames[]={
	"SM_ARRANGE","SM_CLEANBOOT","SM_CMETRICS","SM_CMONITORS","SM_CMOUSEBUTTONS",
	"SM_CXBORDER","SM_CXCURSOR","SM_CXDLGFRAME","SM_CXDOUBLECLK","SM_CXDRAG",
	"SM_CXEDGE","SM_CXFIXEDFRAME","SM_CXFOCUSBORDER","SM_CXFRAME","SM_CXFULLSCREEN",
	"SM_CXHSCROLL","SM_CXHTHUMB","SM_CXICON","SM_CXICONSPACING","SM_CXMAXIMIZED",
	"SM_CXMAXTRACK","SM_CXMENUCHECK","SM_CXMENUSIZE","SM_CXMIN","SM_CXMINIMIZED",
	"SM_CXMINSPACING","SM_CXMINTRACK","SM_CXSCREEN","SM_CXSIZE","SM_CXSIZEFRAME",
	"SM_CXSMICON","SM_CXSMSIZE","SM_CXVIRTUALSCREEN","SM_CXVSCROLL","SM_CYBORDER",
	"SM_CYCAPTION","SM_CYCURSOR","SM_CYDLGFRAME","SM_CYDOUBLECLK","SM_CYDRAG",
	"SM_CYEDGE","SM_CYFIXEDFRAME","SM_CYFOCUSBORDER","SM_CYFRAME","SM_CYFULLSCREEN",
	"SM_CYHSCROLL","SM_CYICON","SM_CYICONSPACING","SM_CYKANJIWINDOW","SM_CYMAXIMIZED",
	"SM_CYMAXTRACK","SM_CYMENU","SM_CYMENUCHECK","SM_CYMENUSIZE","SM_CYMIN",
	"SM_CYMINIMIZED","SM_CYMINSPACING","SM_CYMINTRACK","SM_CYSCREEN","SM_CYSIZE",
	"SM_CYSIZEFRAME","SM_CYSMCAPTION","SM_CYSMICON","SM_CYSMSIZE","SM_CYVIRTUALSCREEN",
	"SM_CYVSCROLL","SM_CYVTHUMB","SM_DBCSENABLED","SM_DEBUG","SM_IMMENABLED",
	"SM_MEDIACENTER","SM_MENUDROPALIGNMENT","SM_MIDEASTENABLED","SM_MOUSEPRESENT","SM_MOUSEWHEELPRESENT",
	"SM_NETWORK","SM_PENWINDOWS","SM_REMOTECONTROL","SM_REMOTESESSION","SM_SAMEDISPLAYFORMAT",
	"SM_SECURE","SM_SHOWSOUNDS","SM_SHUTTINGDOWN","SM_SLOWMACHINE","SM_SWAPBUTTON",
	"SM_TABLETPC","SM_XVIRTUALSCREEN","SM_XVIRTUALSCREEN","SM_YVIRTUALSCREEN","SM_CXPADDEDBORDER",
	"SM_STARTER","SM_SERVERR2","SM_MOUSEHORIZONTALWHEELPRESENT","SM_CXPADDEDBORDER","SM_CARETBLINKINGENABLED",
	"","","","","",
	"","","","","",
};

DWORD CDlgViewSystemMethods::uMetricsNames[]={
	SM_ARRANGE,SM_CLEANBOOT,SM_CMETRICS,SM_CMONITORS,SM_CMOUSEBUTTONS,
	SM_CXBORDER,SM_CXCURSOR,SM_CXDLGFRAME,SM_CXDOUBLECLK,SM_CXDRAG,
	SM_CXEDGE,SM_CXFIXEDFRAME,SM_CXFOCUSBORDER,SM_CXFRAME,SM_CXFULLSCREEN,
	SM_CXHSCROLL,SM_CXHTHUMB,SM_CXICON,SM_CXICONSPACING,SM_CXMAXIMIZED,
	SM_CXMAXTRACK,SM_CXMENUCHECK,SM_CXMENUSIZE,SM_CXMIN,SM_CXMINIMIZED,
	SM_CXMINSPACING,SM_CXMINTRACK,SM_CXSCREEN,SM_CXSIZE,SM_CXSIZEFRAME,
	SM_CXSMICON,SM_CXSMSIZE,SM_CXVIRTUALSCREEN,SM_CXVSCROLL,SM_CYBORDER,
	SM_CYCAPTION,SM_CYCURSOR,SM_CYDLGFRAME,SM_CYDOUBLECLK,SM_CYDRAG,
	SM_CYEDGE,SM_CYFIXEDFRAME,SM_CYFOCUSBORDER,SM_CYFRAME,SM_CYFULLSCREEN,
	SM_CYHSCROLL,SM_CYICON,SM_CYICONSPACING,SM_CYKANJIWINDOW,SM_CYMAXIMIZED,
	SM_CYMAXTRACK,SM_CYMENU,SM_CYMENUCHECK,SM_CYMENUSIZE,SM_CYMIN,
	SM_CYMINIMIZED,SM_CYMINSPACING,SM_CYMINTRACK,SM_CYSCREEN,SM_CYSIZE,
	SM_CYSIZEFRAME,SM_CYSMCAPTION,SM_CYSMICON,SM_CYSMSIZE,SM_CYVIRTUALSCREEN,
	SM_CYVSCROLL,SM_CYVTHUMB,SM_DBCSENABLED,SM_DEBUG,SM_IMMENABLED,
	SM_MEDIACENTER,SM_MENUDROPALIGNMENT,SM_MIDEASTENABLED,SM_MOUSEPRESENT,SM_MOUSEWHEELPRESENT,
	SM_NETWORK,SM_PENWINDOWS,SM_REMOTECONTROL,SM_REMOTESESSION,SM_SAMEDISPLAYFORMAT,
	SM_SECURE,SM_SHOWSOUNDS,SM_SHUTTINGDOWN,SM_SLOWMACHINE,SM_SWAPBUTTON,
	SM_TABLETPC,SM_XVIRTUALSCREEN,SM_XVIRTUALSCREEN, SM_YVIRTUALSCREEN, SM_CXPADDEDBORDER,
	SM_STARTER ,SM_SERVERR2, SM_MOUSEHORIZONTALWHEELPRESENT, SM_CXPADDEDBORDER, SM_CARETBLINKINGENABLED,
	0, 0, 0, 0,0, 
	0, 0, 0, 0,0, 
};

const char *CDlgViewSystemMethods::chColorNames[]={
	"COLOR_3DDKSHADOW","COLOR_3DFACE","COLOR_3DHIGHLIGHT","COLOR_3DHILIGHT","COLOR_3DLIGHT",
	"COLOR_3DSHADOW","COLOR_ACTIVEBORDER","COLOR_ACTIVECAPTION","COLOR_APPWORKSPACE","COLOR_BACKGROUND",
	"COLOR_BTNFACE","COLOR_BTNFACE","COLOR_BTNHIGHLIGHT","COLOR_BTNHILIGHT","COLOR_BTNSHADOW",
	"COLOR_BTNTEXT","COLOR_CAPTIONTEXT","COLOR_DESKTOP","COLOR_GRADIENTACTIVECAPTION","COLOR_GRADIENTINACTIVECAPTION",
	"COLOR_GRAYTEXT","COLOR_HIGHLIGHT","COLOR_HIGHLIGHTTEXT","COLOR_HOTLIGHT","COLOR_INACTIVEBORDER",
	"COLOR_INACTIVECAPTION","COLOR_INACTIVECAPTIONTEXT","COLOR_INFOBK","COLOR_INFOTEXT","COLOR_MENU",
	"COLOR_MENUBAR","COLOR_MENUHILIGHT","COLOR_MENUTEXT","COLOR_SCROLLBAR","COLOR_WINDOW",
	"COLOR_WINDOWFRAME","COLOR_WINDOWTEXT","",

};

DWORD CDlgViewSystemMethods::uColorNames[]={
	COLOR_3DDKSHADOW,COLOR_3DFACE,COLOR_3DHIGHLIGHT,COLOR_3DHILIGHT,COLOR_3DLIGHT,
	COLOR_3DSHADOW,COLOR_ACTIVEBORDER,COLOR_ACTIVECAPTION,COLOR_APPWORKSPACE,COLOR_BACKGROUND,
	COLOR_BTNFACE,COLOR_BTNFACE,COLOR_BTNHIGHLIGHT,COLOR_BTNHILIGHT,COLOR_BTNSHADOW,
	COLOR_BTNTEXT,COLOR_CAPTIONTEXT,COLOR_DESKTOP,COLOR_GRADIENTACTIVECAPTION,COLOR_GRADIENTINACTIVECAPTION,
	COLOR_GRAYTEXT,COLOR_HIGHLIGHT,COLOR_HIGHLIGHTTEXT,COLOR_HOTLIGHT,COLOR_INACTIVEBORDER,
	COLOR_INACTIVECAPTION,COLOR_INACTIVECAPTIONTEXT,COLOR_INFOBK,COLOR_INFOTEXT,COLOR_MENU,
	COLOR_MENUBAR,COLOR_MENUHILIGHT,COLOR_MENUTEXT,COLOR_SCROLLBAR,COLOR_WINDOW,
	COLOR_WINDOWFRAME,COLOR_WINDOWTEXT,0,
};

const char *CDlgViewSystemMethods::cArrMethods[]={
/*00*/	"DnsHostToCompName","GetComputerName",			"GetComputerObjectName",	"GetUserName",				"TranslateName",
/*05*/	"GetIpAddrTable",		"AddIPAddress",			"CreateIpForwardEntry",		"CreateIpNetEntry",			"CreateProxyArpEntry",
/*10*/	"DeleteIPAddress",		"DeleteIpForwardEntry",	"DeleteIpNetEntry",			"DeleteProxyArpEntry",		"FlushIpNetTable",
/*15*/	"GetAdapterIndex",		"GetAdaptersAddresses",	"GetGUIObjectsTypes",		"GetGUIObjectStyles",		"GetGUIObjectMethods",
/*20*/	"GetGUIObjectCommonMethods","GetGUIObjectExStyles","GetWindowsStyles",		"GetWindowsExStyles",		"GetWindowsEvents",
/*25*/	"GetGUIObjectEvents",	"StartCapture",			"ContinueCapture",			"StopCapture",				"SetAdmState",
/*30*/	"GetAdmState",			"SetBreakChar",			"GetBreakChar",				"GetDialogsList",			"DeleteAllDialogs",
/*35*/	"QueryPerformance",		"GetCommonStyles",		"SplitFile",				"GetWindowsDirectory",		"GetSystemDirectory",
/*40*/	"GetSystemWindowsDirectory",	"GetSystemInfo","DeleteAllScreenObjects",	"ParseCmdLine",				"EnumPrinters",
/*45*/	"DeviceCapabilities",	"EnumDisplayDevices",	"EnumDisplaySettings",		"GetSystemMetrics",			"GetSysColor",
/*50*/	"GetSysColorBrush",		"SetSysColors",			"AddMonitor",				"AddPort",					"AddPrinterConnection",
/*55*/	"AddPrintProcessor",	"ConfigurePort",		"DeleteMonitor",			"DeletePort",				"DeletePrinterConnection",
/*60*/	"DeletePrinterDriver",	"DeletePrinterDriverEx","DeletePrintProcessor",		"DeletePrintProvidor",		"GetDefaultPrinter",
/*65*/	"GetPrinterDriverDirectory","GetPrintProcessorDirectory","SetDefaultPrinter",	"SetPort",				"EnumPorts",
/*70*/	"EnumMonitors",			"EnumPrinterDrivers",	"EnumPrintProcessorDatatypes",	"EnumPrintProcessors",	"AddPrintProvidor",
/*75*/	"AddPrinterDriver",		"AddPrinterDriverEx",	"EnumServicesStatusEx",		"OpenSCManager",			"CloseSCManager",
/*80*/	"SetScript",			"DeleteScript",			"DoScript",					"DeleteVariable",			"SetVariable",
/*85*/	"GetWSTime",			"AddPrinter",			"ExecScript",				"EncodeFilePCSRV",			"EncodeFileSRVPC",
/*90*/	"GetODCList",			"CreateODContext",		"DeleteODContext",			"LoadODContext",			"DoODCMethod",
/*95*/	"CapturingPageSetup",	"SlavePrintPageSetup",	"NotepadSetup",				"ShellExecuteEx",			"ProcMonitorStart",
/*100*/	"ProcMonitorModify",	"ProcMonitorSetState",	"GetTerminalVersion",		"GetCurrentProcessId",		"ProcGetList",
/*105*/	"ProcGetListModules",	"ProcGetInfo",			"AllowSetForegroundWindow",	"LockSetForegroundWindow",	"ActivateKeyboardLayout",
/*110*/	"GetKeyboardLayoutList","LoadKeyboardLayout",	"UnloadKeyboardLayout",		"GetKeyboardLayoutName",	"GetKeyboardLayout",
/*115*/	"SetTerminalRect",		"GetTerminalRect",		"GetMethods",				"CapturePreview",			"CapturePreviewSetupDialog",
/*120*/	"",	"",	"",	"",	"",
/*125*/	"",	"",	"",	"",	"",
/*130*/	"",	"",	"",	"",	"",
/*135*/	"",	"",	"",	"",	"",
	};


const char *CDlgViewSystemMethods::cArrMethodsParams[]={
/*00*/	"DnsHost",	"ComputerNameFormat",	"ObjectNameFormat",	"uNameType",	"sNameType,dNameType,sName",
/*05*/	"",	"Address,IpMask,IfIndex",	"IPDest,IPMask,IPNextHop,ForwardProto,Policy,IfIndex,Type,Age,NextHopAS,Metric1,Metric2,Metric3,Metric4,Metric5",	"Index,PhysAddr,IpAddr,Type",	"IPAddress, IPMask, IfIndex",
/*10*/	"NTEContext",	"IPDest,IPMask,IPNextHop,Policy,IfIndex",	"Index,IpAddr",	"IPAddress, IPMask, IfIndex",	"IfIndex",
/*15*/	"AdapterName",	"",	"",	"iObjType",	"iObjType",
/*20*/	"",	"iObjType",	"",	"",	"",
/*25*/	"iObjType",	"FileName,_VISIBLE",	"FileName,_VISIBLE",	"",	"dwNewState",
/*30*/	"",	"iCharCode",	"",	"",	"",
/*35*/	"",	"",	"FileName,PartSize[,BINARY]",	"",	"",
/*40*/	"",	"",	"",	"CmdLine",	"Flags, Name, Level",
/*45*/	"PrinterName, Port, Type",	"[DeviceName], [DevNum][,bGetSettings]",	"DeviceName[,mode1,mode2,....]",	"nIndex[;nIndex2[;nIndex3...]]",	"nIndex[;nIndex2[;nIndex3...]]",
/*50*/	"nIndex[;nIndex2[;nIndex3...]]",	"nIndex=R,G,B[;nIndex2=R,G,B[;nIndex3=R,G,B...]]",	"SrvName,[level],MonitName,Environment,DLLName",	"SrvName,[Parent],MonitName",	"Name",
/*55*/	"SrvName,Environment,PathName,PrintProcessorName",	"SrvName,[Parent],PortName",	"SrvName,Environment,MonitName",	"SrvName,[Parent],PortName",	"Name",
/*60*/	"SrvName,Environment,DriverName",	"[SrvName],Environment,DriverName,options,version",	"SrvName,Environment,ProcName",	"SrvName,Environment,ProvidorName",	"",
/*65*/	"[SrvName][,Environment]",	"[SrvName][,Environment]",	"PrinterName",	"[SrvName],PortName,Status,StatusText,Severity",	"[SrvName],level=1",
/*70*/	"[SrvName],level=1",	"[SrvName],[Environment],level=1",	"[SrvName],[ProcName]",	"[SrvName],[Environment]",	"[SrvName],level=1,PROVIDOR_INFO_level",
/*75*/	"[SrvName],level=2,PROVIDOR_INFO_level",	"[SrvName],level=2,PROVIDOR_INFO_level,FileCopyFlags",	"[InfoLevel=0],ServiceType,ServiceState",	"[MachineName],[DatabaseName],DesiredAccess,GroupName",	"",
/*80*/	"ScriptName,Script",	"ScriptName[,ScriptName2[,..]]",	"[DefScrDlg],[DefObject],ScriptBody",	"VarName[,VarName2[,..]]",	"VariableName,Value",
/*85*/	"",	"[SrvName], PRINTER_INFO_2",	"ScriptName[,DefDlg[,DefObject]]",	"SrcFileName,DstFileName",	"SrcFileName,DstFileName",
/*90*/	"",		"ODCName",		"ODCName",			"ODCName,FileName",		"ODCName,MethodName[ Parameters]",
/*95*/	"Parameters",	"Parameters",	"Parameters",	"[VERB=][;FILE=][;CLASSNANE=][;CLASSKEY=][;DIR=][;SHOW=][;HOTKEY=][;FLAG=][;PARAM=]",	"[IDPROC=][;IDSCR=][;IDDLG=][;NELAPSE=][;STATE=]",
/*100*/	"[IDPROC=][;IDSCR=][;IDDLG=][;NELAPSE=][;STATE=]",	"[IDPROC=][;IDSCR=][;IDDLG=]",	"",	"",	"[Context]",
/*105*/	"IdProc,[Context]",	"IdProc",	"IdProc",	"LockCode",	"KLH",
/*110*/	"",	"KLID, Flags",	"KLH",	"",	"[IdThread]",
/*115*/	"[X],[y],[CX],[CY]",	"",	"",	"",	"",
/*120*/	"",	"",	"",	"",	"",
/*125*/	"",	"",	"",	"",	"",
/*130*/	"",	"",	"",	"",	"",
/*135*/	"",	"",	"",	"",	"",
	};


/*
GetAdaptersInfo 
GetBestInterface 
GetBestRoute 
GetFriendlyIfIndex 
GetIcmpStatistics 
GetIfEntry 
GetIfTable 
GetInterfaceInfo 
GetIpForwardTable 
GetIpNetTable 
GetIpStatistics 
GetNetworkParams 
GetNumberOfInterfaces 
GetPerAdapterInfo 
GetRTTAndHopCount 
GetTcpStatistics 
GetTcpTable 
GetUdpStatistics 
GetUdpTable 
GetUniDirectionalAdapterInfo 
IpReleaseAddress 
IpRenewAddress 
NotifyAddrChange 
NotifyRouteChange 
SendARP 
SetIfEntry 
SetIpForwardEntry 
SetIpNetEntry 
SetIpStatistics 
SetIpTTL 
SetTcpEntry 
UnenableRouter 
EnableRouter 
IcmpCloseHandle
IcmpCreateFile 
IcmpParseReplies 
IcmpSendEcho 
IcmpSendEcho2 
GetExtendedTcpTable 
GetExtendedUdpTable 
GetOwnerModuleFromTcpEntry 
GetOwnerModuleFromTcp6Entry 
GetOwnerModuleFromUdpEntry 
GetOwnerModuleFromUdpEntry 
*/


CDlgViewSystemMethods::CDlgViewSystemMethods(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewSystemMethods::IDD, pParent)
{
	*tmpRetStr=0;
	//{{AFX_DATA_INIT(CDlgViewSystemMethods)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgViewSystemMethods::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgViewSystemMethods)
	DDX_Control(pDX, IDC_COMBOMETHODS, m_ComboMethods);
	DDX_Control(pDX, IDC_BTNEXECUTE, m_btnExecute);
	DDX_Control(pDX, IDC_EDITPARAMS, m_EditParams);
	DDX_Control(pDX, IDC_EDITRESULT, m_EditResult);
	DDX_Control(pDX, IDC_STATICPARAMS, m_StatParams);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgViewSystemMethods, CDialog)
	//{{AFX_MSG_MAP(CDlgViewSystemMethods)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTNEXECUTE, OnBtnexecute)
	ON_CBN_SELCHANGE(IDC_COMBOMETHODS, OnSelchangeCombomethods)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgViewSystemMethods message handlers

BOOL CDlgViewSystemMethods::OnInitDialog()
{
	CDialog::OnInitDialog();
	UINT i;
	for(i=0;*CDlgViewSystemMethods::cArrMethods[i];i++)
		m_ComboMethods.AddString(CDlgViewSystemMethods::cArrMethods[i]);

	m_ComboMethods.SetCurSel(0);
	OnSelchangeCombomethods();

	AUSI.AddSetMain(this->m_hWnd);
	AUSI.AddWnd(m_btnExecute.m_hWnd,this->m_hWnd	,"NENE");

	AUSI.AddWnd(m_ComboMethods.m_hWnd,this->m_hWnd	,"NNNE");
	AUSI.AddWnd(m_EditParams.m_hWnd,this->m_hWnd	,"NNNE");
	AUSI.AddWnd(m_StatParams.m_hWnd,this->m_hWnd	,"NNNE");
	AUSI.AddWnd(m_EditResult.m_hWnd,this->m_hWnd	,"NNEE");

	AUSI.SetMinSize(this->m_hWnd,450,150);

	GPC.SetIconFromIL(m_hWnd, "SEPVIEW", 44);

	return TRUE;
}

void CDlgViewSystemMethods::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	AUSI.UpdateSize();
}

void CDlgViewSystemMethods::OnBtnexecute()
{
	m_EditResult.SetWindowText("");
	CString str;
	CString strMeth;
	CString strParam;
	m_ComboMethods.GetWindowText(strMeth);
	m_EditParams.GetWindowText(strParam);
	str=strMeth+" "+strParam;

	char *oStr=new char [150000];
	*oStr=0;
	CDlgViewSystemMethods::DoMethod(str,oStr);
	m_EditResult.SetWindowText(oStr);
	delete[] oStr;
}

void CDlgViewSystemMethods::OnSelchangeCombomethods()
{
	CString str;
	m_ComboMethods.GetWindowText(str);
	UINT i;
	for(i=0;*CDlgViewSystemMethods::cArrMethods[i];i++)
		if (str==CDlgViewSystemMethods::cArrMethods[i]) break;
	m_StatParams.SetWindowText(CDlgViewSystemMethods::cArrMethodsParams[i]);
}

void CDlgViewSystemMethods::OnDestroy()
{
	CDialog::OnDestroy();
}

BOOL CDlgViewSystemMethods::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (wParam!=1 || lParam!=0) return CDialog::OnCommand(wParam, lParam);

	if (wParam==1)
	{
		HWND fcs=::GetFocus();
		if (fcs==::GetDlgItem(m_hWnd,IDC_EDITPARAMS) || fcs==::GetDlgItem(m_hWnd,IDC_BTNEXECUTE))
			OnBtnexecute();
	}

	return CDialog::OnCommand(wParam, lParam);
}

int CDlgViewSystemMethods::DoMethod(const char *iStr, char *oStr)
{
	char met[150];
	const char *pos;
	strncpy(met,iStr,145);
	met[145]=0;
	pos=strchr(iStr,' ');
	if (pos++==NULL) pos="";
	else
		*strchr(met,' ')=0;

	UINT nfunc=0;
	int retint=-123456;
	int atoipos=atoi(pos);
	if (pos[1]=='X' || pos[1]=='x') sscanf(pos+2,"%X",&atoipos);

	if (*met>='0' && *met<='9') nfunc=atoi(met);
	else
	{
		static const char *sccArrMethods[sizeof(cArrMethods)/sizeof(char *)];
		static DWORD scdMethodsId[sizeof(cArrMethods)/sizeof(char *)];
		static DWORD uNMethods;
		if (!*sccArrMethods)
		{
			for(uNMethods=0;*CDlgViewSystemMethods::cArrMethods[uNMethods];uNMethods++)
			{
				sccArrMethods[uNMethods]=cArrMethods[uNMethods];
				scdMethodsId[uNMethods]=uNMethods;
			}
			qsCharILineAndDWORD(sccArrMethods, scdMethodsId, 0, uNMethods-1);
			scdMethodsId[uNMethods]=uNMethods;
		}
		nfunc=scdMethodsId[FindInSortArrayIC(met, sccArrMethods, uNMethods)];
	}

	try
	{
		switch(nfunc)
		{
		case 0: // DnsHostToCompName DnsHost
			if (oStr)
			{
			#ifdef W_95
				strcpy(oStr,"Need Windows 2000/XP");
			#else
				#ifdef W_NT
					strcpy(oStr,"Need Windows 2000/XP");
				#else
					#ifdef W_98
						strcpy(oStr,"Need Windows 2000/XP");
					#else
						DWORD dwSize=500;
						DnsHostnameToComputerName(pos,oStr,&dwSize);
					#endif
				#endif
			#endif
			}
			break;
		case 1: // GetComputerName ComputerNameFormat
		case 2: // GetComputerObjectName ObjectNameFormat
		case 3: // GetUserName uNameType
			if (oStr)
			{
				*oStr=0;
				unsigned long nLen=MAX_COMPUTERNAME_LENGTH + 5000;

				switch(nfunc)
				{
				#ifdef W_95
					case 1: /*GetComputerName*/
						GetComputerName(oStr,&nLen);
						break;
					case 2: /*GetComputerObjectName*/
						strcpy(oStr,"Old Windows");
						break;
					case 3: /*GetUserName*/
						//retint=
							GetUserName (oStr,&nLen);
						//if (!retint) retint=GetLastError();
						break;
				#else
					#ifdef W_NT
						case 1: /*GetComputerName*/
							GetComputerName(oStr,&nLen);	
							break;
						case 2: /*GetComputerObjectName*/
							strcpy(oStr,"Old Windows");
							break;
						case 3: /*GetUserName*/
							//retint=
								GetUserName (oStr,&nLen);
							//if (!retint) retint=GetLastError();
							break;
					#else
						#ifdef W_98
							case 1: /*GetComputerName*/
								GetComputerName(oStr,&nLen);
								break;
							case 2: /*GetComputerObjectName*/
								strcpy(oStr,"Old Windows");
								break;
							case 3: /*GetUserName*/
								//retint=
									GetUserName (oStr,&nLen);
								//if (!retint) retint=GetLastError();
								break;
						#else
							case 1: /*GetComputerName*/
								GetComputerNameEx((_COMPUTER_NAME_FORMAT)atoipos,oStr,&nLen);
								break;
							case 2: /*GetComputerObjectName*/
								GetComputerObjectName((EXTENDED_NAME_FORMAT)atoipos,oStr,&nLen);
								break;
							case 3: /*GetUserName*/
								//retint=
									GetUserNameEx ((EXTENDED_NAME_FORMAT)atoipos,oStr,&nLen);
								//if (!retint) retint=GetLastError();
								break;
						#endif
					#endif
				#endif
				}
			}
			break;
		case 4: // TranslateName sNameType,dNameType,sName
			if (oStr)
			{
				int sType=0,dType=0;
				*oStr=0;
				m_LastScanf=sscanf(pos,"%d,%d,%s",&sType,&dType,oStr);

				#ifdef W_95
					if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
				#else
					#ifdef W_NT
						if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
					#else
						#ifdef W_98
							if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
						#else
							ULONG sz=900;
							TranslateName(oStr,(EXTENDED_NAME_FORMAT)sType,(EXTENDED_NAME_FORMAT)dType,oStr,&sz);
						#endif
					#endif
				#endif
			}
			break;
		case 5: // GetIpAddrTable
			if (oStr)
			{
			#ifdef W_95
				strcpy(oStr,"W982000XP");
			#else
				*oStr=0;
				char *buff=new char [10000];
				ZeroMemory(buff, 10000);
				PMIB_IPADDRTABLE pIpAddrTable=(PMIB_IPADDRTABLE)buff;
				ULONG dwSize=10000;
				::GetIpAddrTable(pIpAddrTable, &dwSize, 1);
				char *posOut=oStr;
				char tmps[200];
				UINT i;
				for(i=0;i<pIpAddrTable->dwNumEntries;i++)
				{
					*tmps=0;
					CDlgViewSystemMethods::StringFromToAddrTypes(tmps, pIpAddrTable->table[i].wType);
					if (i) *(posOut++)=127,*posOut=0;
					char a1[32],a2[32],a3[32];
					strcpy(a1,IPAddrToString(pIpAddrTable->table[i].dwAddr));
					strcpy(a2,IPAddrToString(pIpAddrTable->table[i].dwMask));
					strcpy(a3,IPAddrToString(pIpAddrTable->table[i].dwBCastAddr));

					posOut+=sprintf(posOut,"%d\x7%s\x7%s\x7%s\x7%d\x7%s\x7%d",
						pIpAddrTable->table[i].dwIndex,
						a1,a2,a3,
						pIpAddrTable->table[i].dwReasmSize,
						tmps,
						pIpAddrTable->table[i].unused1
						);
				}
				delete[] buff;
			#endif
			}
			break;
		case 6: // AddIPAddress
			{
				#ifdef W_95
					if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
				#else
					#ifdef W_NT
						if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
					#else
						#ifdef W_98
							if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
						#else
							IPAddr Address=StringToIPAddr(ExtractField(pos,1,","));
							IPAddr IpMask=StringToIPAddr(ExtractField(pos,2,","));
							DWORD IfIndex=atoi(ExtractField(pos,3,","));
							ULONG NTEContext=0;
							ULONG NTEInstance=0;
							retint=AddIPAddress(Address, IpMask, IfIndex, &NTEContext, &NTEInstance);
							if (oStr)
								sprintf(oStr,"%d\x7F%d\x7F%d",retint,NTEContext,NTEInstance);
						#endif
					#endif
				#endif
			}
			break;
		case 7: // CreateIpForwardEntry
			#ifdef W_95
			#else
				{
					MIB_IPFORWARDROW fr={0};
					fr.dwForwardDest=StringToIPAddr(ExtractField(pos,1,","));
					fr.dwForwardMask=StringToIPAddr(ExtractField(pos,2,","));
					fr.dwForwardNextHop=StringToIPAddr(ExtractField(pos,3,","));
					fr.dwForwardProto=StringFromToProtocolId(ExtractField(pos,4,","), fr.dwForwardProto);
					const char *ff=FindField(pos,5,",");
					if (ff)
						m_LastScanf=sscanf(ff,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
							&(fr.dwForwardPolicy),&(fr.dwForwardIfIndex),&(fr.dwForwardType),
							&(fr.dwForwardAge),&(fr.dwForwardNextHopAS),&(fr.dwForwardMetric1),
							&(fr.dwForwardMetric2),&(fr.dwForwardMetric3),&(fr.dwForwardMetric4),
							&(fr.dwForwardMetric5));

					retint=CreateIpForwardEntry(&fr);
				}
			#endif
			break;
		case 8: // CreateIpNetEntry
			#ifdef W_95
			#else
				{
					MIB_IPNETROW fr={0};
					fr.dwIndex=atoipos;
					CString phad=CGPContextMenu::ConvertToOutput(ExtractField(pos,2,","),"");
					fr.dwPhysAddrLen=phad.GetLength();

					UINT i;
					for(i=0;i<fr.dwPhysAddrLen && i<MAXLEN_PHYSADDR;i++)
						fr.bPhysAddr[i]=phad.GetAt(i);

					fr.dwAddr=StringToIPAddr(ExtractField(pos,3,","));
					fr.dwType=atoi(ExtractField(pos,4,","));

					retint=CreateIpNetEntry(&fr);
				}
			#endif
			break;

		case 9: // CreateProxyArpEntry
			#ifdef W_95
				if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
			#else
				#ifdef W_NT
					if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
				#else
					#ifdef W_98
						if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
					#else
						retint=CreateProxyArpEntry(StringToIPAddr(ExtractField(pos,1,",")),StringToIPAddr(ExtractField(pos,2,",")),atoi(ExtractField(pos,3,",")));
					#endif
				#endif
			#endif
			break;
		case 10: // DeleteIPAddress
			#ifdef W_95
				if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
			#else
				#ifdef W_NT
					if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
				#else
					#ifdef W_98
						if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
					#else
						retint=DeleteIPAddress(atoipos);
					#endif
				#endif
			#endif
			break;
		case 11: // DeleteIpForwardEntry
			#ifdef W_95
			#else
				{
					MIB_IPFORWARDROW fr={0};
					fr.dwForwardDest=StringToIPAddr(ExtractField(pos,1,","));
					fr.dwForwardMask=StringToIPAddr(ExtractField(pos,2,","));
					fr.dwForwardNextHop=StringToIPAddr(ExtractField(pos,3,","));
					const char *ff=FindField(pos,4,",");
					if (ff) m_LastScanf=sscanf(ff,"%d,%d",&(fr.dwForwardPolicy),&(fr.dwForwardIfIndex));

					retint=DeleteIpForwardEntry(&fr);
				}
			#endif
			break;
		case 12: // DeleteIpNetEntry
			#ifdef W_95
			#else
				{
					MIB_IPNETROW fr={0};
					fr.dwIndex=atoipos;
					fr.dwAddr=StringToIPAddr(ExtractField(pos,2,","));
					retint=DeleteIpNetEntry(&fr);
				}
			#endif
			break;

		case 13: // DeleteProxyArpEntry
			#ifdef W_95
				if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
			#else
				#ifdef W_NT
					if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
				#else
					#ifdef W_98
						if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
					#else
						retint=DeleteProxyArpEntry(StringToIPAddr(ExtractField(pos,1,",")),StringToIPAddr(ExtractField(pos,2,",")),atoi(ExtractField(pos,3,",")));
					#endif
				#endif
			#endif
			break;
		case 14: // FlushIpNetTable
			#ifdef W_95
				if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
			#else
				#ifdef W_NT
					if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
				#else
					#ifdef W_98
						if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
					#else
						retint=FlushIpNetTable(atoipos);
					#endif
				#endif
			#endif
			break;
		case 15: // GetAdapterIndex
			if (oStr)
			{
				#ifdef W_95
					if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
				#else
					#ifdef W_NT
						if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
					#else
						#ifdef W_98
							if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
						#else
							ULONG IfIndex=0xFFFFFFFF;
							CString tmps=pos;
							BSTR tmpbstr=tmps.AllocSysString();
							retint=-1;
							if (GetAdapterIndex(tmpbstr,&IfIndex)== NO_ERROR) retint=IfIndex;
							::SysFreeString(tmpbstr);
						#endif
					#endif
				#endif
			}
			break;
		case 16: // GetAdaptersAddresses
			#ifdef W_95
				if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
			#else
				#ifdef W_NT
					if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
				#else
					#ifdef W_98
						if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
					#else
						if (oStr)
						{
							DWORD AddrFamily=0;
							DWORD AddrFlags=0;
							AddrFamily=StringFromToAddrFamily(ExtractField(pos,1,","),AddrFamily);
							AddrFlags=StringFromToAddrFlags(ExtractField(pos,2,","),AddrFlags);
							ULONG OutBufLen=0;
			//				GetAdaptersAddresses(AddrFamily,AddrFlags,NULL,NULL,&OutBufLen);
							retint=-1;
		/*					if (OutBufLen && OutBufLen<1000000)
							{
								char *buff=new char [OutBufLen+1000];
								char *ret=oStr;
								ZeroMemory(buff, OutBufLen);
								PIP_ADAPTER_ADDRESSES pAddr=(PIP_ADAPTER_ADDRESSES)buff;
								if (GetAdaptersAddresses(AddrFamily,AddrFlags,NULL,pAddr,&OutBufLen)==ERROR_SUCCESS)
								{
									while(pAddr)
									{
										ret+=spintf(ret,"",

										pAddr->





		typedef struct _IP_ADAPTER_ADDRESSES {
		  union {
			ULONGLONG Alignment
			struct {
				ULONG Length;
				DWORD IfIndex;
			}
		  }
		  struct _IP_ADAPTER_ADDRESSES* Next;
		  PCHAR AdapterName;
		  PIP_ADAPTER_UNICAST_ADDRESS   FirstUnicastAddress;
		  PIP_ADAPTER_ANYCAST_ADDRESS   FirstAnycastAddress;
		  PIP_ADAPTER_MULTICAST_ADDRESS FirstMulticastAddress;
		  PIP_ADAPTER_DNS_SERVER_ADDRESS FirstDnsServerAddress;
		  PWCHAR DnsSuffix;
		  PWCHAR Description;
		  PWCHAR FriendlyName;
		  BYTE PhysicalAddress [MAX_ADAPTER_ADDRESS_LENGTH];
		  DWORD PhysicalAddressLength;
		  DWORD Flags;
		  DWORD Mtu;
		  DWORD IfType;
		  IF_OPER_STATUS OperStatus;
		} IP_ADAPTER_ADDRESSES, *PIP_ADAPTER_ADDRESSES;


										pAddr=pAddr->Next;
									}
								}
								delete[] buff;
							}
		*/	
						}
					#endif
				#endif
			#endif
			break;
		case 17: // GetGUIObjectsTypes
			if (oStr)
			{
				*oStr=0;
				char *postmp=oStr;
				UINT i;
				for(i=1;*GPUnit::aTypeUnit[i];i++)
				{
					if (i>1) *(postmp++)='\x7F';
					strcpy(postmp,GPUnit::aTypeUnit[i]);
					postmp+=(int)strlen(GPUnit::aTypeUnit[i]);
				}
			}
			break;
		case 18: // GetGUIObjectStyles
			if (oStr)
			{
				if (*pos)
				{
					*oStr=0;
					char *postmp=oStr;
					UINT i;
					char cmpname[50];
					strncpy(cmpname,pos,45);
					cmpname[45]=0;
					UINT j;
					for(j=1;*GPUnit::aTypeUnit[j];j++)
						if (strcmp(cmpname,GPUnit::aTypeUnit[j])==0)
						{
							UINT nMeth=0;
							const char **cMeth=NULL;
							const UINT *uMeth=NULL;
							nMeth=0;
							switch(GPUnit::auTypeUnit[j])
							{
							case GPUnit::UT_MAINDLGSCR:
								cMeth=aDlgStyleName;
								uMeth=aDlgStyleUINT;
								nMeth=N_DLG_STYLES;
								break;
							case GPUnit::UT_DATETIMECTRL:
								cMeth=aDateTimeStyleName;
								uMeth=aDateTimeStyleUINT;
								nMeth=N_DATETIME_STYLES;
								break;
							case GPUnit::UT_MONTHCAL:
								cMeth=aMonthCalStyleName;
								uMeth=aMonthCalStyleUINT;
								nMeth=N_MONTHCAL_STYLES;
								break;
							case GPUnit::UT_DLGBAR:
							case GPUnit::UT_FRAMEBAR:
								cMeth=aDlgStyleName;
								uMeth=aDlgStyleUINT;
								nMeth=N_DLG_STYLES;
								break;
							case GPUnit::UT_RTF:
								cMeth=aRTFStyleName;
								uMeth=aRTFStyleUINT;
								nMeth=N_RTF_STYLES;
								break;
							case GPUnit::UT_TREECTRL:
								cMeth=aTreeCtrlStyleName;
								uMeth=aTreeCtrlStyleUINT;
								nMeth=N_TREECTRL_STYLES;
								break;
							case GPUnit::UT_HEADER:
								cMeth=aHeaderStyleName;
								uMeth=aHeaderStyleUINT;
								nMeth=N_HEADER_STYLES;
								break;
							case GPUnit::UT_REBARCTRL:
								cMeth=aReBarCtrlStyleName;
								uMeth=aReBarCtrlStyleUINT;
								nMeth=N_REBARCTRL_STYLES;
								break;
							case GPUnit::UT_REBAR:
								cMeth=aReBarCtrlStyleName;
								uMeth=aReBarCtrlStyleUINT;
								nMeth=N_REBARCTRL_STYLES;
								break;
							case GPUnit::UT_STATUSBARCTRL:
								cMeth=aStatusBarCtrlStyleName;
								uMeth=aStatusBarCtrlStyleUINT;
								nMeth=N_STATUSBARCTRL_STYLES;
								break;
							case GPUnit::UT_STATUSBAR:
								cMeth=aStatusBarStyleName;
								uMeth=aStatusBarStyleUINT;
								nMeth=N_STATUSBAR_STYLES;
								break;
							case GPUnit::UT_DIALOGBAR:
								cMeth=aCtrlBarStyleName;
								uMeth=aCtrlBarStyleUINT;
								nMeth=N_CTRLBAR_STYLES;
								break;
							case GPUnit::UT_TOOLBARCTRL:
								cMeth=aToolBarCtrlStyleName;
								uMeth=aToolBarCtrlStyleUINT;
								nMeth=N_TOOLBARCTRL_STYLES;
								break;
							case GPUnit::UT_TOOLBAR:
								cMeth=aToolBarCtrlStyleName;
								uMeth=aToolBarCtrlStyleUINT;
								nMeth=N_TOOLBARCTRL_STYLES;
								break;
							case GPUnit::UT_SLIDER:
								cMeth=aSliderStyleName;
								uMeth=aSliderStyleUINT;
								nMeth=N_SLIDER_STYLES;
								break;
							case GPUnit::UT_TABCTRL:
								cMeth=aTabStyleName;
								uMeth=aTabStyleUINT;
								nMeth=N_TAB_STYLES;
								break;
							case GPUnit::UT_SPINBUTTON:
								cMeth=aSpinStyleName;
								uMeth=aSpinStyleUINT;
								nMeth=N_SPIN_STYLES;
								break;
							case GPUnit::UT_BBUTTON:
							case GPUnit::UT_BUTTON:
							case GPUnit::UT_ANIBUTTON:
								cMeth=aButtonStyleName;
								uMeth=aButtonStyleUINT;
								nMeth=N_BUTTON_STYLES;
								break;
							case GPUnit::UT_STATIC:
							case GPUnit::UT_ANISTATIC:
								cMeth=aStaticStyleName;
								uMeth=aStaticStyleUINT;
								nMeth=N_STATIC_STYLES;
								break;
							case GPUnit::UT_EDIT:
								cMeth=aEditStyleName;
								uMeth=aEditStyleUINT;
								nMeth=N_EDIT_STYLES;
								break;
							case GPUnit::UT_COMBOBOX:
								cMeth=aComboBoxStyleName;
								uMeth=aComboBoxStyleUINT;
								nMeth=N_COMBOBOX_STYLES;
								break;
							case GPUnit::UT_COMBOBOXEX:
								cMeth=aComboBoxExStyleName;
								uMeth=aComboBoxExStyleUINT;
								nMeth=N_COMBOBOXEX_STYLES;
								break;
							case GPUnit::UT_SCROLLBAR:
								cMeth=aScrollStyleName;
								uMeth=aScrollStyleUINT;
								nMeth=N_SCROLL_STYLES;
								break;
							case GPUnit::UT_PROGRESS:
								cMeth=aProgressStyleName;
								uMeth=aProgressStyleUINT;
								nMeth=N_PROGRESS_STYLES;
								break;
							case GPUnit::UT_ANIMAT:
								cMeth=aAnimationStyleName;
								uMeth=aAnimationStyleUINT;
								nMeth=N_ANIMATION_STYLES;
								break;
							case GPUnit::UT_LISTBOX:
							case GPUnit::UT_CHECKLISTBOX:
							case GPUnit::UT_DRAGLISTBOX:
								cMeth=aListBoxStyleName;
								uMeth=aListBoxStyleUINT;
								nMeth=N_LISTBOX_STYLES;
								break;
							case GPUnit::UT_LISTCTRL:
								cMeth=aListCtrlStyleName;
								uMeth=aListCtrlStyleUINT;
								nMeth=N_LISTCTRL_STYLES;
								break;
							case GPUnit::UT_EDITOR:
							case GPUnit::UT_FLEXGRID:
							case GPUnit::UT_WEBBROWSER:
							case GPUnit::UT_DRAW:
							case GPUnit::UT_CONTROL:
							default:
								break;
							}
							for(i=0;i<nMeth;i++)
							{
								if (postmp!=oStr) *(postmp++)=1;
								postmp+=sprintf(postmp,"%s\x2%lu",cMeth[i],uMeth[i]);
							}

							nMeth=0;
							switch(GPUnit::auTypeUnit[j])
							{
							case GPUnit::UT_DATETIMECTRL:
								cMeth=aMonthCalStyleName;
								uMeth=aMonthCalStyleUINT;
								nMeth=N_MONTHCAL_STYLES;
								break;
							case GPUnit::UT_HEADER:
								cMeth=aComCtrlStyleName;
								uMeth=aComCtrlStyleUINT;
								nMeth=N_COMCTRL_STYLES;
								break;
							case GPUnit::UT_REBARCTRL:
								cMeth=aComCtrlStyleName;
								uMeth=aComCtrlStyleUINT;
								nMeth=N_COMCTRL_STYLES;
								break;
							case GPUnit::UT_REBAR:
								cMeth=aCtrlBarStyleName;
								uMeth=aCtrlBarStyleUINT;
								nMeth=N_CTRLBAR_STYLES;
								break;
							case GPUnit::UT_STATUSBARCTRL:
								cMeth=aComCtrlStyleName;
								uMeth=aComCtrlStyleUINT;
								nMeth=N_COMCTRL_STYLES;
								break;
							case GPUnit::UT_STATUSBAR:
								cMeth=aCtrlBarStyleName;
								uMeth=aCtrlBarStyleUINT;
								nMeth=N_CTRLBAR_STYLES;
								break;
							case GPUnit::UT_TOOLBARCTRL:
								cMeth=aComCtrlStyleName;
								uMeth=aComCtrlStyleUINT;
								nMeth=N_COMCTRL_STYLES;
								break;
							case GPUnit::UT_TOOLBAR:
								cMeth=aCtrlBarStyleName;
								uMeth=aCtrlBarStyleUINT;
								nMeth=N_CTRLBAR_STYLES;
								break;
							}
							for(i=0;i<nMeth;i++)
							{
								if (postmp!=oStr) *(postmp++)=1;
								postmp+=sprintf(postmp,"%s\x2%lu",cMeth[i],uMeth[i]);
							}
						}
				}
				else
				{
					char *tmpstr=new char [150000];
					char *postmp=oStr;
					UINT i;
					for(i=1;*GPUnit::aTypeUnit[i];i++)
					{
						*tmpstr=0;
						char tmpmet[200];
						sprintf(tmpmet,"GetGUIObjectStyles %s",GPUnit::aTypeUnit[i]);
						CDlgViewSystemMethods::DoMethod(tmpmet,tmpstr);
						if (i>1) *(postmp++)=127;
						strcpy(postmp,tmpstr);
						postmp+=(int)strlen(postmp);
					}
					delete[] tmpstr;
				}
			}
			break;
		case 19: // GetGUIObjectMethods
			if (oStr)
			{
				if (*pos)
				{
					*oStr=0;
					char *postmp=oStr;
					UINT i;
					char cmpname[50];
					strncpy(cmpname,pos,45);
					UINT j;
					for(j=1;*GPUnit::aTypeUnit[j];j++)
						if (strcmp(cmpname,GPUnit::aTypeUnit[j])==0)
						{
							UINT nMeth=0;
							const char **cMethParams=NULL;
							const char **cMeth=NULL;

							switch(GPUnit::auTypeUnit[j])
							{
								case GPUnit::UT_MAINDLGSCR:
									nMeth=CGPToolTipCtrl::uNToolTipMethods;
									cMeth=CGPToolTipCtrl::cArrToolTipMethods;
									cMethParams=CGPToolTipCtrl::cArrToolTipMethodsParams;
								default:
									nMeth=CGPToolTipCtrl::uNToolTipMethodsAll;
									cMeth=CGPToolTipCtrl::cArrToolTipMethodsAll;
									cMethParams=CGPToolTipCtrl::cArrToolTipMethodsParamsAll;
									break;
							}

							for(i=0;i<nMeth;i++)
							{
								if (postmp!=oStr) *(postmp++)=1;
								postmp+=sprintf(postmp,"%s\x2%s",cMeth[i],cMethParams[i]);
							}

							nMeth=0;
							switch(GPUnit::auTypeUnit[j])
							{
								case GPUnit::UT_MAINDLGSCR:
									cMeth=GPFrameWnd::cArrMethods;
									cMethParams=GPFrameWnd::cArrMethodsParams;
									nMeth=GPFrameWnd::uNMethods;
								case GPUnit::UT_ANIBUTTON:
									cMeth=GPButton::cArrMethods;
									cMethParams=GPButton::cArrMethodsParams;
									nMeth=GPButton::uNMethods;
									break;
								case GPUnit::UT_ANISTATIC:
									cMeth=GPStatic::cArrMethods;
									cMethParams=GPStatic::cArrMethodsParams;
									nMeth=GPStatic::uNMethods;
									break;
								case GPUnit::UT_STATUSBAR:
									cMeth=GPUnit::cArrControlBarMethod;
									cMethParams=GPUnit::cArrControlBarMethodParams;
									nMeth=GPUnit::uNControlBarMethod;
									break;
								case GPUnit::UT_REBAR:
									cMeth=GPUnit::cArrControlBarMethod;
									cMethParams=GPUnit::cArrControlBarMethodParams;
									nMeth=GPUnit::uNControlBarMethod;
									break;
								case GPUnit::UT_TOOLBAR:
									cMeth=GPUnit::cArrControlBarMethod;
									cMethParams=GPUnit::cArrControlBarMethodParams;
									nMeth=GPUnit::uNControlBarMethod;
									break;
								case GPUnit::UT_DIALOGBAR:
									cMeth=GPUnit::cArrControlBarMethod;
									cMethParams=GPUnit::cArrControlBarMethodParams;
									nMeth=GPUnit::uNControlBarMethod;
									break;
							}
							for(i=0;i<nMeth;i++)
							{
								if (postmp!=oStr) *(postmp++)=1;
								postmp+=sprintf(postmp,"%s\x2%s",cMeth[i],cMethParams[i]);
							}
							nMeth=0;


							switch(GPUnit::auTypeUnit[j])
							{
								case GPUnit::UT_MAINDLGSCR:
									cMeth=GPObjDialog::cArrMethods;
									cMethParams=GPObjDialog::cArrMethodsParams;
									nMeth=GPObjDialog::uNMethods;
									break;
								case GPUnit::UT_DATETIMECTRL:
									cMeth=GPDateTimeCtrl::cArrMethods;
									cMethParams=GPDateTimeCtrl::cArrMethodsParams;
									nMeth=GPDateTimeCtrl::uNMethods;
									break;
								case GPUnit::UT_MONTHCAL:
									cMeth=GPMonthCalCtrl::cArrMethods;
									cMethParams=GPMonthCalCtrl::cArrMethodsParams;
									nMeth=GPMonthCalCtrl::uNMethods;
									break;
								case GPUnit::UT_DLGBAR:
									cMeth=GPDlgBar::cArrMethods;
									cMethParams=GPDlgBar::cArrMethodsParams;
									nMeth=GPDlgBar::uNMethods;
									break;
								case GPUnit::UT_FRAMEBAR:
									cMeth=GPFrameBar::cArrMethods;
									cMethParams=GPFrameBar::cArrMethodsParams;
									nMeth=GPFrameBar::uNMethods;
									break;
								case GPUnit::UT_RTF:
									cMeth=GP_RTF::cArrMethods;
									cMethParams=GP_RTF::cArrMethodsParams;
									nMeth=GP_RTF::uNMethods;
									break;
								case GPUnit::UT_EDITOR:
									cMeth=GPScintilla::cArrMethods;
									cMethParams=GPScintilla::cArrMethodsParams;
									nMeth=GPScintilla::uNMethods;
									break;
								case GPUnit::UT_CONTROL:
									cMeth=GP_Control::cArrMethods;
									cMethParams=GP_Control::cArrMethodsParams;
									nMeth=GP_Control::uNMethods;
									break;
								case GPUnit::UT_TREECTRL:
									cMeth=GPTree::cArrMethods;
									cMethParams=GPTree::cArrMethodsParams;
									nMeth=GPTree::uNMethods;
									break;
								case GPUnit::UT_HEADER:
									cMeth=GPHeader::cArrMethods;
									cMethParams=GPHeader::cArrMethodsParams;
									nMeth=GPHeader::uNMethods;
									break;
								case GPUnit::UT_SLIDER:
									cMeth=GPSlider::cArrMethods;
									cMethParams=GPSlider::cArrMethodsParams;
									nMeth=GPSlider::uNMethods;
									break;
								case GPUnit::UT_TABCTRL:
									cMeth=GPTabCtrl::cArrMethods;
									cMethParams=GPTabCtrl::cArrMethodsParams;
									nMeth=GPTabCtrl::uNMethods;
									break;
								case GPUnit::UT_SPINBUTTON:
									cMeth=GPSpinButton::cArrMethods;
									cMethParams=GPSpinButton::cArrMethodsParams;
									nMeth=GPSpinButton::uNMethods;
									break;
								case GPUnit::UT_BUTTON:
									cMeth=GPButton::cArrMethods;
									cMethParams=GPButton::cArrMethodsParams;
									nMeth=GPButton::uNMethods;
									break;
								case GPUnit::UT_ANIBUTTON:
									cMeth=GPAniButton::cArrMethods;
									cMethParams=GPAniButton::cArrMethodsParams;
									nMeth=GPAniButton::uNMethods;
									break;
								case GPUnit::UT_BBUTTON:
									cMeth=GPBButton::cArrMethods;
									cMethParams=GPBButton::cArrMethodsParams;
									nMeth=GPBButton::uNMethods;
									break;
								case GPUnit::UT_STATIC:
									cMeth=GPStatic::cArrMethods;
									cMethParams=GPStatic::cArrMethodsParams;
									nMeth=GPStatic::uNMethods;
									break;
								case GPUnit::UT_ANISTATIC:
									cMeth=GPAniStatic::cArrMethods;
									cMethParams=GPAniStatic::cArrMethodsParams;
									nMeth=GPAniStatic::uNMethods;
									break;
								case GPUnit::UT_EDIT:
									cMeth=GPEdit::cArrMethods;
									cMethParams=GPEdit::cArrMethodsParams;
									nMeth=GPEdit::uNMethods;
									break;
								case GPUnit::UT_LISTBOX:
									cMeth=GPListBox::cArrMethods;
									cMethParams=GPListBox::cArrMethodsParams;
									nMeth=GPListBox::uNMethods;
									break;
								case GPUnit::UT_COMBOBOX:
									cMeth=GPComboBox::cArrMethods;
									cMethParams=GPComboBox::cArrMethodsParams;
									nMeth=GPComboBox::uNMethods;
									break;
								case GPUnit::UT_COMBOBOXEX:
									cMeth=GPComboBoxEx::cArrMethods;
									cMethParams=GPComboBoxEx::cArrMethodsParams;
									nMeth=GPComboBoxEx::uNMethods;
									break;
								case GPUnit::UT_SCROLLBAR:
									cMeth=GPScrollBar::cArrMethods;
									cMethParams=GPScrollBar::cArrMethodsParams;
									nMeth=GPScrollBar::uNMethods;
									break;
								case GPUnit::UT_PROGRESS:
									cMeth=GPProgress::cArrMethods;
									cMethParams=GPProgress::cArrMethodsParams;
									nMeth=GPProgress::uNMethods;
									break;
								case GPUnit::UT_ANIMAT:
									cMeth=GPAnimate::cArrMethods;
									cMethParams=GPAnimate::cArrMethodsParams;
									nMeth=GPAnimate::uNMethods;
									break;
								case GPUnit::UT_CHECKLISTBOX:
									cMeth=GPChLBox::cArrMethods;
									cMethParams=GPChLBox::cArrMethodsParams;
									nMeth=GPChLBox::uNMethods;
									break;
								case GPUnit::UT_DRAGLISTBOX:
									cMeth=GPDrLBox::cArrMethods;
									cMethParams=GPDrLBox::cArrMethodsParams;
									nMeth=GPDrLBox::uNMethods;
									break;
								case GPUnit::UT_LISTCTRL:
									cMeth=GPListCtr::cArrMethods;
									cMethParams=GPListCtr::cArrMethodsParams;
									nMeth=GPListCtr::uNMethods;
									break;
								case GPUnit::UT_REBARCTRL:
									cMeth=GPReBarCtrl::cArrMethods;
									cMethParams=GPReBarCtrl::cArrMethodsParams;
									nMeth=GPReBarCtrl::uNMethods;
									break;
								case GPUnit::UT_REBAR:
									cMeth=GPReBar::cArrMethods;
									cMethParams=GPReBar::cArrMethodsParams;
									nMeth=GPReBar::uNMethods;
									break;
								case GPUnit::UT_STATUSBARCTRL:
									cMeth=GPStatusBarCtrl::cArrMethods;
									cMethParams=GPStatusBarCtrl::cArrMethodsParams;
									nMeth=GPStatusBarCtrl::uNMethods;
									break;
								case GPUnit::UT_TOOLBARCTRL:
									cMeth=GPToolBarCtrl::cArrMethods;
									cMethParams=GPToolBarCtrl::cArrMethodsParams;
									nMeth=GPToolBarCtrl::uNMethods;
									break;
								case GPUnit::UT_STATUSBAR:
									cMeth=GPStatusBar::cArrMethods;
									cMethParams=GPStatusBar::cArrMethodsParams;
									nMeth=GPStatusBar::uNMethods;
									break;
								case GPUnit::UT_TOOLBAR:
									cMeth=GPToolBar::cArrMethods;
									cMethParams=GPToolBar::cArrMethodsParams;
									nMeth=GPToolBar::uNMethods;
									break;
								case GPUnit::UT_DIALOGBAR:
									cMeth=GPDialogBar::cArrMethods;
									cMethParams=GPDialogBar::cArrMethodsParams;
									nMeth=GPDialogBar::uNMethods;
									break;
								case GPUnit::UT_DRAW:
									cMeth=GPDrawWnd::cArrMethods;
									cMethParams=GPDrawWnd::cArrMethodsParams;
									nMeth=GPDrawWnd::uNMethods;
									break;
								case GPUnit::UT_FLEXGRID:
									cMeth=GPCMSFlexGrid::cArrMethods;
									cMethParams=GPCMSFlexGrid::cArrMethodsParams;
									nMeth=GPCMSFlexGrid::uNMethods;
									break;
								case GPUnit::UT_WEBBROWSER:
									cMeth=GPWebBrowser2::cArrMethods;
									cMethParams=GPWebBrowser2::cArrMethodsParams;
									nMeth=GPWebBrowser2::uNMethods;
									break;
							}
							for(i=0;i<nMeth;i++)
							{
								if (postmp!=oStr) *(postmp++)=1;
								postmp+=sprintf(postmp,"%s\x2%s",cMeth[i],cMethParams[i]);
							}
							break;
						}
				}
				else
				{
					char *tmpstr=new char [100000];
					char *postmp=oStr;
					UINT i;
					for(i=1;*GPUnit::aTypeUnit[i];i++)
					{
						*tmpstr=0;
						char tmpmet[200];
						sprintf(tmpmet,"GetGUIObjectMethods %s",GPUnit::aTypeUnit[i]);
						CDlgViewSystemMethods::DoMethod(tmpmet,tmpstr);
						if (i>1) *(postmp++)=127;
						strcpy(postmp,tmpstr);
						postmp+=(int)strlen(postmp);
					}

					delete[] tmpstr;
				}
			}
			break;
		case 20: // GetGUIObjectCommonMethods
			if (oStr)
			{
				char *postmp=oStr;
				UINT i;
				for(i=0;i<GPUnit::uNMethods;i++)
				{
					if (i>0) *(postmp++)=1;
					postmp+=sprintf(postmp,"%s\x2%s",GPUnit::cArrMethods[i],GPUnit::cArrMethodsParams[i]);
				}
			}
			break;
		case 21: // GetGUIObjectExStyles
			if (oStr)
			{
				if (*pos)
				{
					*oStr=0;
					char *postmp=oStr;
					UINT i;
					char cmpname[50];
					strncpy(cmpname,pos,45);
					UINT j;
					for(j=1;*GPUnit::aTypeUnit[j];j++)
						if (strcmp(cmpname,GPUnit::aTypeUnit[j])==0)
						{
							UINT nMeth=0;
							const char **cMeth=NULL;
							const UINT *uMeth=NULL;

							nMeth=0;
							switch(GPUnit::auTypeUnit[j])
							{
							case GPUnit::UT_TREECTRL:
								cMeth=aTreeCtrlExStyleName;
								uMeth=aTreeCtrlExStyleUINT;
								nMeth=N_TREECTRL_EX_STYLES;
								break;
							case GPUnit::UT_RTF:
								cMeth=aRTFExStyleName;
								uMeth=aRTFExStyleUINT;
								nMeth=N_RTF_EX_STYLES;
								break;
							case GPUnit::UT_TABCTRL:
								cMeth=aTabExStyleName;
								uMeth=aTabExStyleUINT;
								nMeth=N_TAB_EX_STYLES;
								break;
							case GPUnit::UT_COMBOBOXEX:
								cMeth=aComboBoxExExStyleName;
								uMeth=aComboBoxExExStyleUINT;
								nMeth=N_COMBOBOXEX_EX_STYLES;
								break;
							case GPUnit::UT_LISTCTRL:
								cMeth=aListCtrlExStyleName;
								uMeth=aListCtrlExStyleUINT;
								nMeth=N_LISTCTRL_EX_STYLES;
								break;
							case GPUnit::UT_TOOLBAR:
							case GPUnit::UT_TOOLBARCTRL:
								cMeth=aToolBarCtrlExStyleName;
								uMeth=aToolBarCtrlExStyleUINT;
								nMeth=N_TOOLBARCTRL_EX_STYLES;
								break;
							}
							for(i=0;i<nMeth;i++)
							{
								if (postmp!=oStr) *(postmp++)=1;
								postmp+=sprintf(postmp,"%s\x2%lu",cMeth[i],uMeth[i]);
							}
						}
				}
				else
				{
					char *tmpstr=new char [50000];
					char *postmp=oStr;
					UINT i;
					for(i=1;*GPUnit::aTypeUnit[i];i++)
					{
						*tmpstr=0;
						char tmpmet[200];
						sprintf(tmpmet,"GetGUIObjectExStyles %s",GPUnit::aTypeUnit[i]);
						CDlgViewSystemMethods::DoMethod(tmpmet,tmpstr);
						if (i>1) *(postmp++)=127;
						strcpy(postmp,tmpstr);
						postmp+=(int)strlen(postmp);
					}
					delete[] tmpstr;
				}
			}
			break;
		case 22: //GetWindowsStyles 
			if (oStr)
			{
				*oStr=0;
				char *postmp=oStr;
				UINT i;
				for(i=0;i<N_WND_STYLES;i++)
				{
					if (postmp!=oStr) *(postmp++)=1;
					postmp+=sprintf(postmp,"%s\x2%lu",aWndStyleName[i],aWndStyleUINT[i]);
				}
			}
			break;
		case 23: // GetWindowsExStyles
			if (oStr)
			{
				*oStr=0;
				char *postmp=oStr;
				UINT i;
				for(i=0;i<N_WND_EX_STYLES;i++)
				{
					if (postmp!=oStr) *(postmp++)=1;
					postmp+=sprintf(postmp,"%s\x2%lu",aWndExStyleName[i],aWndExStyleUINT[i]);
				}
			}
			break;
		case 24: // GetWindowsEvents",
			if (oStr)
			{
				char *postmp=oStr;
				UINT i;
				for(i=0;i<N_WND_MESSAGE;i++)
				{
					if (postmp!=oStr) *(postmp++)=1;
					postmp+=sprintf(postmp,"%s\x2%lu",alpmes[i],auimes[i]);
				}

			}
			break;
		case 25: // GetGUIObjectEvents
			if (oStr)
			{
				if (*pos)
				{
					*oStr=0;
					char cmpname[50];
					strncpy(cmpname,pos,45);
					UINT j;
					for(j=1;*GPUnit::aTypeUnit[j];j++)
						if (strcmp(cmpname,GPUnit::aTypeUnit[j])==0)
						{
							strcpy(oStr,aUnitMessage[j]);
							if (*oStr) strcat(oStr,aUnitCommonMessages);
							char *cMeth=oStr;
							while(*(++cMeth))
								if (*cMeth==',') *cMeth=1;
						}
				}
				else
				{
					char *tmpstr=new char [50000];
					char *postmp=oStr;
					UINT i;
					for(i=1;*GPUnit::aTypeUnit[i];i++)
					{
						*tmpstr=0;
						char tmpmet[200];
						sprintf(tmpmet,"GetGUIObjectEvents %s",GPUnit::aTypeUnit[i]);
						CDlgViewSystemMethods::DoMethod(tmpmet,tmpstr);
						if (i>1) *(postmp++)=127;
						strcpy(postmp,tmpstr);
						postmp+=(int)strlen(postmp);
					}
					delete[] tmpstr;
				}
			}


			break;
		case 26: // StartCapture
		case 27: // ContinueCapture
			{
				if (GPC.m_View->m_CaptureFile) 
				{
					fclose(GPC.m_View->m_CaptureFile);
					GPC.m_View->m_CaptureFile=NULL;
				}
				CString fname=ExtractField(pos,1,",");
				if (fname=="") fname="capture.txt";
				GPC.m_View->m_CaptureFile=fopen(fname,(nfunc==26)?"wt":"at");
				retint=(int)GPC.m_View->m_CaptureFile;
				GPC.m_View->m_CaptureFlags=0;
				if (ExtractField(pos,2,",").Find("_VISIBLE",0)>=0) GPC.m_View->m_CaptureFlags|=0x1;
				if (retint==NULL) 
				{
					char *msgt=new char [(int)strlen(pos)+500];
					#ifdef RUS
						sprintf(msgt,"Невозможно открыть файл - %s",(LPCSTR)ExtractField(pos,1,","));
						AfxGetMainWnd()->MessageBox(msgt,"Ошибка открытия файла");
					#else
						sprintf(msgt,"Can't open file - %s",(LPCSTR)ExtractField(pos,1,","));
						AfxGetMainWnd()->MessageBox(msgt,"Capturing error");
					#endif
					delete[] msgt;
				}

			}
			break;
		case 28: // StopCapture
			if (GPC.m_View->m_CaptureFile) 
			{
				fclose(GPC.m_View->m_CaptureFile);
				GPC.m_View->m_CaptureFile=NULL;
			}
			break;

		case 29: // SetAdmState
			GPC.AdmIsOn=(atoipos!=0)?1:0;
			GPC.m_View->m_GPMenu->Fill_mArrMenu(FALSE);
			GPC.m_View->UpdateMenuByAdm();
			break;

		case 30: // GetAdmState
			retint=GPC.AdmIsOn;
			break;

		case 31: // SetBreakChar
			GPC.BreakChar=atoipos;
			break;

		case 32: // GetBreakChar
			retint=GPC.BreakChar;
			break;

		case 33: // GetDialogsList
			if (oStr)
			{
				char *posout=oStr;
				UINT i;
				for(i=0;i<MAX_OBJDLG;i++)
					if (GPC.m_Document->a_GPObjType[i]==0)
					{
						if (GPC.m_Document->a_GPObjDialog[i])
						{
							if (posout!=oStr) *(posout++)=0x7F;
							posout+=sprintf(posout,"%d\x7%s",i,(LPCSTR)GPC.m_Document->a_GPObjDialog[i]->GPU[0]->m_ObjName);
						}
					}
					else
					{
						if (GPC.m_Document->a_GPObjFrame[i])
						{
							if (posout!=oStr) *(posout++)=0x7;
							posout+=sprintf(posout,"%d\x7%s",i,(LPCSTR)GPC.m_Document->a_GPObjFrame[i]->GPU[0]->m_ObjName);
						}
					}
			}
			break;

		case 34: // DeleteAllDialogs
			GPC.m_Document->RemoveAllDlg();
			break;
		case 35: // QueryPerformance
			if (oStr)
			{
				__int64 li1=0;
				__int64 li2=0;
				QueryPerformanceFrequency((LARGE_INTEGER *)&li1);
				QueryPerformanceCounter((LARGE_INTEGER *)&li2);
				sprintf(oStr,"%I64d%c%I64d",li1,0x7F,li2);
			}
			break;

		case 36: //GetCommonStyles 
			if (oStr)
			{
				*oStr=0;
				char *postmp=oStr;
				UINT i;
				for(i=0;i<N_UNITCOMMON_STYLES;i++)
				{
					if (postmp!=oStr) *(postmp++)=1;
					postmp+=sprintf(postmp,"%s\x2%lu",aUnitCommonStyleName[i],aUnitCommonStyleUINT[i]);
				}
			}
		case 37: //SplitFile FileName,PartSize[,BINARY]
			{
				FILE *src=NULL;
				CString flName=ExtractField(pos,1,",");
				CString flNameDst;
				size_t fSize=atoi(ExtractField(pos,2,","));
				BOOL bBinary=(ExtractField(pos,3,",")=="BINARY");
				if (fSize<65500) fSize=65500;
				int blckSize=fSize;
				if (blckSize>64000) blckSize=64000;
				if ((src=fopen(flName,bBinary?"rb":"rt")))
				{
					char *tmps=new char [blckSize+1000];
					int FileNum=0;
					FILE *dst=NULL;
					if (bBinary)
					{
						size_t curlen=0;
						size_t nread;
						while((nread=fread(tmps, sizeof(char), blckSize, src)))
						{
							while(nread)
							{
								if (!dst) 
								{
									flNameDst.Format("%s_part_%5.5d",(LPCSTR)flName,FileNum);
									dst=fopen(flNameDst,bBinary?"wb":"wt");
								}
								size_t nwrite=curlen+(nread>fSize?fSize-curlen:nread);
								curlen+=nwrite;
								nread-=nwrite;

								if (dst) fwrite(tmps, sizeof(char), nwrite, dst);

								if (curlen>=fSize)
								{
									if (dst) fclose(dst);
									dst=NULL;
									FileNum++;
									curlen=0;
								}
							}
						}
					}
					else
					{
						size_t curlen=0;
						int nread;
						while(fgets(tmps, blckSize, src))
						{
							nread=(int)strlen(tmps);
							if(nread)
							{
								if (!dst) 
								{
									flNameDst.Format("%s_part_%5.5d",(LPCSTR)flName,FileNum);
									dst=fopen(flNameDst,bBinary?"wb":"wt");
								}
								curlen+=nread;
								if (dst) fprintf(dst,"%s",tmps);
								if (curlen>=fSize)
								{
									if (dst) fclose(dst);
									dst=NULL;
									FileNum++;
									curlen=0;
								}
							}
						}
					}

					if (dst) fclose(dst);
					dst=NULL;

					delete[] tmps;
					fclose(src);
					src=NULL;
					retint=FileNum;
				}
			}
			break;


		case 38:/* GetWindowsDirectory*/
			if (oStr)	GetWindowsDirectory(oStr,900);
			break;
		case 39:/* GetSystemDirectory*/
			if (oStr)	GetSystemDirectory(oStr,900);
			break;
		case 40:/* GetSystemWindowsDirectory*/
			#ifdef W_95
				if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
			#else
				#ifdef W_NT
					if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
				#else
					#ifdef W_98
						if (oStr) strcpy(oStr,"Required version for W2000 or WXP");
					#else
						if (oStr)	GetSystemWindowsDirectory(oStr,900);
					#endif
				#endif
			#endif

			break;
		case 41:/* GetSystemInfo*/
			if (oStr)	
			{
				SYSTEM_INFO m_SystemInfo={0};
				GetSystemInfo(&m_SystemInfo);
				char *prar[5]={"INTEL","MIPS","ALPHA","PPC","UNKNOWN",};
				WORD wprar[5]={PROCESSOR_ARCHITECTURE_INTEL,PROCESSOR_ARCHITECTURE_MIPS,PROCESSOR_ARCHITECTURE_ALPHA,PROCESSOR_ARCHITECTURE_PPC,PROCESSOR_ARCHITECTURE_UNKNOWN,};
				int i333;
				for(i333=0;i333<5 && m_SystemInfo.wProcessorArchitecture!=wprar[i333];i333++);
				if (i333>=5) i333=4;

				sprintf(oStr,"%d\x7F%s\x7F%X\x7F%X\x7F%X\x7F%X\x7F%X\x7F%X\x7F%X\x7F%X\x7F%X",
					m_SystemInfo.dwOemId,
					prar[i333],
					m_SystemInfo.dwPageSize,
					(DWORD)m_SystemInfo.lpMinimumApplicationAddress,
					(DWORD)m_SystemInfo.lpMaximumApplicationAddress,
					m_SystemInfo.dwActiveProcessorMask,
					m_SystemInfo.dwNumberOfProcessors,
					m_SystemInfo.dwAllocationGranularity,
					m_SystemInfo.wProcessorArchitecture,
					m_SystemInfo.wProcessorLevel,
					m_SystemInfo.wProcessorRevision
					);

				break;
			}
			break;
		case 42:/*DeleteAllScreenObjects*/
			GPC.m_Document->GetMainScreen()->DeleteAllObjects();
			break;
		case 43:/*ParseCmdLine CmdLine*/
			if (*pos) GPC.ParseCommandLine(0xFFFFFFFF^0x000E,pos);
			break;
		case 44:/*EnumPrinters Flags, Name, Level */
			if (oStr)
			{
				DWORD adwFlagsAtt[]={
					PRINTER_ATTRIBUTE_QUEUED,PRINTER_ATTRIBUTE_DIRECT,PRINTER_ATTRIBUTE_DEFAULT,PRINTER_ATTRIBUTE_SHARED,PRINTER_ATTRIBUTE_NETWORK,
					PRINTER_ATTRIBUTE_HIDDEN,PRINTER_ATTRIBUTE_LOCAL,PRINTER_ATTRIBUTE_ENABLE_DEVQ,PRINTER_ATTRIBUTE_KEEPPRINTEDJOBS,PRINTER_ATTRIBUTE_DO_COMPLETE_FIRST,
					PRINTER_ATTRIBUTE_WORK_OFFLINE,PRINTER_ATTRIBUTE_ENABLE_BIDI,PRINTER_ATTRIBUTE_RAW_ONLY,PRINTER_ATTRIBUTE_PUBLISHED,PRINTER_ATTRIBUTE_FAX,
					PRINTER_ATTRIBUTE_TS,
				};
				char *acFlagsAtt[]={
					"QUEUED","DIRECT","DEFAULT","SHARED","NETWORK",
					"HIDDEN","LOCAL","ENABLE_DEVQ","KEEPPRINTEDJOBS","DO_COMPLETE_FIRST",
					"WORK_OFFLINE","ENABLE_BIDI","RAW_ONLY","PUBLISHED","FAX",
					"TS",
				};
				DWORD adwFlags[]={PRINTER_ENUM_LOCAL,PRINTER_ENUM_NAME,PRINTER_ENUM_SHARED,PRINTER_ENUM_DEFAULT,PRINTER_ENUM_CONNECTIONS,PRINTER_ENUM_NETWORK,PRINTER_ENUM_REMOTE,};
				const char *acFlags[]={"LOCAL","NAME","SHARED","DEFAULT","CONNECTIONS","NETWORK","REMOTE",};
				char *posout=oStr;
				DWORD dwLevel;
				dwLevel=atoi(ExtractField(pos,3,","));
				DWORD i;
				if (atoipos==-1)
				{
					const char *pos2=strchr(pos,',');
					if (!pos2) pos2="";
					char *methStr=new char [(int)strlen(pos2)+100];
					for(i=0;i<7;i++)
					{
						if (i) *(posout++)=127;
						posout+=sprintf(posout,"%s\x1",acFlags[i]);

						*posout=0;
						sprintf(methStr,"%s %s%s",cArrMethods[nfunc],acFlags[i],pos2);
						DoMethod(methStr,posout);
						posout=DelimitersDown(posout);
					}
					delete [] methStr;
				}
				else
				if (dwLevel==-1)
				{
					char *methStr=new char [(int)strlen(pos)+100];
					sprintf(methStr,"%s %s",cArrMethods[nfunc],pos);
					for(i=1;i<6;i++)
						if (i!=3)
						{
							char *pos2=strchr(strchr(methStr,',')+1,',');
							sprintf(++pos2,"%d",i);
							if (i) *(posout++)=127;
							*posout=0;
							DoMethod(methStr,posout);
							posout=DelimitersDown(posout);
						}
					delete [] methStr;
				}
				else
				{
					if (dwLevel==0 || dwLevel>5 || dwLevel==3) dwLevel=1;
					BYTE *byPrinterEnum=NULL;
					DWORD dwFlag=0;
					DWORD cbBuf=0;
					DWORD cbNeeded=0;
					DWORD cnReturned=0;
					char name[1000];
					char *pname=name;
					CString csTmp;
					csTmp=ExtractField(pos,1,",");	csTmp.MakeUpper();
					dwFlag=atoi(csTmp);
					if (csTmp!="")
						for(i=0;i<7;i++)
							if (csTmp.Find(acFlags[i],0)>=0) dwFlag|=adwFlags[i];

					strncpy(name,ExtractField(pos,2,","),990);		name[990]=0;
					if (!*name) pname=NULL;
					while(*name==' ') strcpy(name, name+1);

					::EnumPrinters(dwFlag,pname,dwLevel,byPrinterEnum,cbBuf,&cbNeeded,&cnReturned);

					if (cbNeeded)
					{
						cbBuf=cbNeeded+10;
						byPrinterEnum=new BYTE [cbBuf];
						::EnumPrinters(dwFlag,pname,dwLevel,byPrinterEnum,cbBuf,&cbNeeded,&cnReturned);
						int j;
						switch(dwLevel)
						{
							case 1:
								{
									PRINTER_INFO_1 *pPI=(PRINTER_INFO_1 *) byPrinterEnum;
									DWORD adwFlags2[]={
										PRINTER_ENUM_EXPAND,PRINTER_ENUM_CONTAINER,PRINTER_ENUM_ICON1,PRINTER_ENUM_ICON2,
										PRINTER_ENUM_ICON3,PRINTER_ENUM_ICON4,PRINTER_ENUM_ICON5,PRINTER_ENUM_ICON6,
										PRINTER_ENUM_ICON7,PRINTER_ENUM_ICON8,PRINTER_ENUM_HIDE,};
									char *acFlags2[]={"EXPAND","CONTAINER","ICON1","ICON2","ICON3","ICON4","ICON5","ICON6","ICON7","ICON8","HIDE",};
									for(i=0;i<cnReturned;i++,pPI++)
									{
										if (i) *(posout++)=127;
										posout+=sprintf(posout,"%8.8X\x2",pPI->Flags);

										for(*posout=0,j=0;j<11;j++)
											if ((pPI->Flags&adwFlags2[j])==adwFlags2[j])
											{
												if (*posout) strcat(posout++,"|");
												strcpy(posout,acFlags2[j]);
											}
										while(*posout) posout++;
										posout+=sprintf(posout,"\x1%s\x1%s\x1%s",pPI->pDescription?pPI->pDescription:"",pPI->pName?pPI->pName:"",pPI->pComment?pPI->pComment:"");
									}
								}
								break;
							case 2:
								{
									DWORD adwStatusAtt[]={
										PRINTER_STATUS_PAUSED,PRINTER_STATUS_ERROR,PRINTER_STATUS_PENDING_DELETION,PRINTER_STATUS_PAPER_JAM,PRINTER_STATUS_PAPER_OUT,
										PRINTER_STATUS_MANUAL_FEED,PRINTER_STATUS_PAPER_PROBLEM,PRINTER_STATUS_OFFLINE,PRINTER_STATUS_IO_ACTIVE,PRINTER_STATUS_BUSY,
										PRINTER_STATUS_PRINTING,PRINTER_STATUS_OUTPUT_BIN_FULL,PRINTER_STATUS_NOT_AVAILABLE,PRINTER_STATUS_WAITING,PRINTER_STATUS_PROCESSING,
										PRINTER_STATUS_INITIALIZING,PRINTER_STATUS_WARMING_UP,PRINTER_STATUS_TONER_LOW,PRINTER_STATUS_NO_TONER,PRINTER_STATUS_PAGE_PUNT,
										PRINTER_STATUS_USER_INTERVENTION,PRINTER_STATUS_OUT_OF_MEMORY,PRINTER_STATUS_DOOR_OPEN,PRINTER_STATUS_SERVER_UNKNOWN,PRINTER_STATUS_POWER_SAVE,
									};
									char *acStatusAtt[]={
										"PAUSED","ERROR","PENDING_DELETION","PAPER_JAM","PAPER_OUT",
										"MANUAL_FEED","PAPER_PROBLEM","OFFLINE","IO_ACTIVE","BUSY",
										"PRINTING","OUTPUT_BIN_FULL","NOT_AVAILABLE","WAITING","PROCESSING",
										"INITIALIZING","WARMING_UP","TONER_LOW","NO_TONER","PAGE_PUNT",
										"USER_INTERVENTION","OUT_OF_MEMORY","DOOR_OPEN","SERVER_UNKNOWN","POWER_SAVE",
									};
									PRINTER_INFO_2 *pPI=(PRINTER_INFO_2 *) byPrinterEnum;
									for(i=0;i<cnReturned;i++)
									{
										if (i) *(posout++)=127;
										posout+=sprintf(posout,"%8.8X\x2",pPI->Status);

										for(*posout=0,j=0;j<25;j++)
											if ((pPI->Status&adwStatusAtt[j])==adwStatusAtt[j])
											{
												if (*posout) strcat(posout++,"|");
												strcpy(posout,acStatusAtt[j]);
											}
										while(*posout) posout++;
										*(posout++)=0x1;
										for(*posout=0,j=0;j<16;j++)
											if ((pPI->Attributes&adwFlagsAtt[j])==adwFlagsAtt[j])
											{
												if (*posout) strcat(posout++,"|");
												strcpy(posout,acFlagsAtt[j]);
											}
										while(*posout) posout++;

										posout+=sprintf(posout,"\x1%s\x1%s\x1%s\x1%s\x1%s\x1%s\x1%s\x1%s\x1%s\x1%s\x1%s\x1%d\x1%d\x1%d\x1%d\x1%d\x1%d\x1",
											pPI->pServerName?pPI->pServerName:"",
											pPI->pPrinterName?pPI->pPrinterName:"",
											pPI->pShareName?pPI->pShareName:"",
											pPI->pPortName?pPI->pPortName:"",
											pPI->pDriverName?pPI->pDriverName:"",
											pPI->pComment?pPI->pComment:"",
											pPI->pLocation?pPI->pLocation:"",
											pPI->pSepFile?pPI->pSepFile:"",
											pPI->pPrintProcessor?pPI->pPrintProcessor:"",
											pPI->pDatatype?pPI->pDatatype:"",
											pPI->pParameters?pPI->pParameters:"",
											pPI->Priority,
											pPI->DefaultPriority,
											pPI->StartTime,
											pPI->UntilTime,
											pPI->cJobs,
											pPI->AveragePPM
											);
										DEVMODEToString(pPI->pDevMode,posout);
										DelimitersDown(posout);
										DelimitersDown(posout);
											//  PSECURITY_DESCRIPTOR pSecurityDescriptor; 
									}
								}
								break;
							case 4:
								{
									PRINTER_INFO_4 *pPI=(PRINTER_INFO_4 *) byPrinterEnum;
									for(i=0;i<cnReturned;i++,pPI++)
									{
										if (i) *(posout++)=127;
										posout+=sprintf(posout,"%s\x1%s\x1",pPI->pPrinterName?pPI->pPrinterName:"",pPI->pServerName?pPI->pServerName:"");
										posout+=sprintf(posout,"%8.8X\x2",pPI->Attributes);

										for(*posout=0,j=0;j<16;j++)
											if ((pPI->Attributes&adwFlagsAtt[j])==adwFlagsAtt[j])
											{
												if (*posout) strcat(posout++,"|");
												strcpy(posout,acFlagsAtt[j]);
											}
										while(*posout) posout++;
									}
								}
								break;
							case 5:
								{
									PRINTER_INFO_5 *pPI=(PRINTER_INFO_5 *) byPrinterEnum;
									for(i=0;i<cnReturned;i++,pPI++)
									{
										if (i) *(posout++)=127;
										posout+=sprintf(posout,"%s\x1%s\x1",
											pPI->pPrinterName?pPI->pPrinterName:"",
											pPI->pPortName?pPI->pPortName:""
											);
										posout+=sprintf(posout,"%8.8X\x2",pPI->Attributes);

										for(*posout=0,j=0;j<16;j++)
											if ((pPI->Attributes&adwFlagsAtt[j])==adwFlagsAtt[j])
											{
												if (*posout) strcat(posout++,"|");
												strcpy(posout,acFlagsAtt[j]);
											}
										while(*posout) posout++;
										posout+=sprintf(posout,"\x1%d\x1%d",
											pPI->DeviceNotSelectedTimeout,
											pPI->TransmissionRetryTimeout
											);
									}
								}
								break;
						}
						delete [] byPrinterEnum;
					}
				}					
			}
			break;
		case 45:/*DeviceCapabilities Name, Port, Type    //Samsung SCX-4100 Series,USB002,-1 */
			if (oStr)
			{
				CString printerName=ExtractField(pos,1,",");
				CString PortName=ExtractField(pos,2,",");
				CString TypName=ExtractField(pos,3,",");
				char *tmpresult=new char [32000];
				WORD *tmpw=(WORD *)tmpresult;
				DWORD *tmpdw=(DWORD *)tmpresult;
				LONG *tmpLONG=(LONG *)tmpresult;
				char *acStatusAtt[]={
					"NULL",
					"DC_FIELDS","DC_PAPERS","DC_PAPERSIZE","DC_MINEXTENT","DC_MAXEXTENT",
					"DC_BINS","DC_DUPLEX","DC_SIZE","DC_EXTRA","DC_VERSION",
					"DC_DRIVER","DC_BINNAMES","DC_ENUMRESOLUTIONS","DC_FILEDEPENDENCIES","DC_TRUETYPE",
					"DC_PAPERNAMES","DC_ORIENTATION","DC_COPIES","DC_BINADJUST","DC_EMF_COMPLIANT",
					"DC_DATATYPE_PRODUCED","DC_COLLATE","DC_MANUFACTURER","DC_MODEL","DC_PERSONALITY",
					"DC_PRINTRATE","DC_PRINTRATEUNIT","DC_PRINTERMEM","DC_MEDIAREADY","DC_STAPLE",
					"DC_PRINTRATEPPM","DC_COLORDEVICE","DC_NUP","DC_MEDIATYPENAMES","DC_MEDIATYPES",
					"",
				};
				int nItems=0;
				WORD dwDoIt[]={0,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0,	0,};
				int j,k;

				if (atoi(TypName)==-1 || TypName=="")
				{
					for(j=1;*acStatusAtt[j];j++) dwDoIt[nItems++]=j;
				}
				else
					for(j=1;*acStatusAtt[j];j++)
					{
						CString tmpname=ExtractField(TypName,j,"|");
						if (tmpname!="")
						{
							dwDoIt[j]=0;
							for(k=1;*acStatusAtt[k] && acStatusAtt[k]!=tmpname;k++);
							if (*acStatusAtt[k]) dwDoIt[j]=k;
							else
								dwDoIt[j]=atoi(tmpname);
						}
					}

				char *posout=oStr;
				for(j=0;dwDoIt[j];j++)
				{
					if (j) *(posout++)=0x7F;
					posout+=sprintf(posout,"%s\x1",dwDoIt[j]>0 && dwDoIt[j]<36?acStatusAtt[dwDoIt[j]]:acStatusAtt[0]);
					tmpdw[0]=0;
					int ret;
					try
					{
						ret=DeviceCapabilities(printerName,PortName,dwDoIt[j], dwDoIt[j]!=DC_TRUETYPE?tmpresult:NULL,NULL);
					}catch(...)
					{
						ret=-1;
						strcpy(posout,"DeviceCapabilities ERROR");
						while(*posout) posout++;
					}
					if (ret>=0)
					{
						switch(dwDoIt[j])
						{
						case DC_FIELDS: 
							posout+=sprintf(posout,"%X",ret);	break;
							break;
						case DC_PAPERSIZE: 
							{
								POINT *po=(POINT *)tmpresult;
								for(k=0;k<ret;k++)
								{
									if (k) *(posout++)=0x2;
									posout+=sprintf(posout,"%d\x03%d",po[k].x,po[k].y);
								}
								break;
							}
						case DC_MINEXTENT:    
						case DC_MAXEXTENT:
							posout+=sprintf(posout,"%d\x03%d",LOWORD(ret),HIWORD(ret));
							break;
						case DC_PAPERS:    
						case DC_BINS:
							for(k=0;k<ret;k++)
							{
								if (k) *(posout++)=0x2;
								posout+=sprintf(posout,"%d",tmpw[k]);
							}
							break;
						case DC_BINNAMES:
							for(k=0;k<ret;k++)
							{
								if (k) *(posout++)=0x2;
								posout+=sprintf(posout,"%s",tmpresult+24*k);
							}
							break;
						case DC_ENUMRESOLUTIONS:  
							for(k=0;k<ret;k++)
							{
								if (k) *(posout++)=0x2;
								posout+=sprintf(posout,"%d\x03%d",tmpLONG[k*2],tmpLONG[k*2+1]);
							}
							break;
						case DC_PAPERNAMES:
						case DC_MEDIAREADY:   
						case DC_MEDIATYPENAMES: 
						case DC_FILEDEPENDENCIES:  
							for(k=0;k<ret;k++)
							{
								if (k) *(posout++)=0x2;
								strcpy(posout,tmpresult+64*k);
								posout[64]=0;
								while(*posout) posout++;
							}
							break;
						case DC_PERSONALITY: 
							for(k=0;k<ret;k++)
							{
								if (k) *(posout++)=0x2;
								strcpy(posout,tmpresult+32*k);
								posout[32]=0;
								while(*posout) posout++;
							}
							break;
						case DC_VERSION: 
						case DC_TRUETYPE:  
						case DC_STAPLE:  
						case DC_SIZE:   
						case DC_PRINTRATEUNIT:  
						case DC_PRINTRATEPPM: 
						case DC_PRINTRATE: 
						case DC_PRINTERMEM:  
						case DC_ORIENTATION:
						case DC_MODEL:  
						case DC_MANUFACTURER:
						case DC_EXTRA: 
						case DC_EMF_COMPLIANT: 
						case DC_DUPLEX:   
						case DC_DATATYPE_PRODUCED: 
						case DC_DRIVER: 
						case DC_COPIES:
						case DC_COLORDEVICE:  
						case DC_COLLATE:   
						case DC_BINADJUST: 
							posout+=sprintf(posout,"%d",ret);
							break;
						case DC_NUP:  
						case DC_MEDIATYPES:
							for(k=0;k<ret;k++)
							{
								if (k) *(posout++)=0x2;
								posout+=sprintf(posout,"%d",tmpdw[k]);
							}
							break;
						default:
							posout+=sprintf(posout,"%d\x03%d\x03%d",ret,*tmpdw,*tmpw);
							break;
						}
					}
					else posout+=sprintf(posout,"%d",ret);

				}
				delete [] tmpresult;
			}
			break;
	#ifdef W_95
	#else
		case 46:/*EnumDisplayDevices DeviceName, DevNum    */
			if (oStr)
			{
				CString csTmp=ExtractField(pos,2,",");
				BOOL bDSettings=atoi(ExtractField(pos,3,","));
				int DevNum=atoi(csTmp);
				if (csTmp=="") DevNum=-1;
				csTmp=ExtractField(pos,1,",");
				DISPLAY_DEVICE ddDisplayDevice; 
				ddDisplayDevice.cb=sizeof(DISPLAY_DEVICE);
				char *posout=oStr;
				DWORD adwStatusAtt[]={
					DISPLAY_DEVICE_ACTIVE,DISPLAY_DEVICE_ATTACHED,DISPLAY_DEVICE_PRIMARY_DEVICE,DISPLAY_DEVICE_MIRRORING_DRIVER,
					DISPLAY_DEVICE_VGA_COMPATIBLE,DISPLAY_DEVICE_REMOVABLE,DISPLAY_DEVICE_MODESPRUNED,DISPLAY_DEVICE_REMOTE,
					DISPLAY_DEVICE_DISCONNECT,
				};
				char *acStatusAtt[]={
					"DISPLAY_DEVICE_ACTIVE","DISPLAY_DEVICE_ATTACHED","DISPLAY_DEVICE_PRIMARY_DEVICE","DISPLAY_DEVICE_MIRRORING_DRIVER",
					"DISPLAY_DEVICE_VGA_COMPATIBLE","DISPLAY_DEVICE_REMOVABLE","DISPLAY_DEVICE_MODESPRUNED","DISPLAY_DEVICE_REMOTE",
					"DISPLAY_DEVICE_DISCONNECT",
				};

				int i;
				for(i=(DevNum<0)?0:DevNum; EnumDisplayDevices(csTmp!=""?(LPCTSTR)csTmp:NULL,i,&ddDisplayDevice,0) && (DevNum<0 || i==DevNum);i++)
				{
					int j;
					if (*oStr) *(posout++)=0x7F;
					posout+=sprintf(posout,"%s\x1%s\x1%8.8X",ddDisplayDevice.DeviceName,ddDisplayDevice.DeviceString,ddDisplayDevice.StateFlags);

					for(*posout=0,j=0;j<9;j++)
						if ((ddDisplayDevice.StateFlags&adwStatusAtt[j])==adwStatusAtt[j])
						{
							if (*posout) strcat(posout,"|");
							strcat(posout,acStatusAtt[j]);
						}
					while(*posout) posout++;
					
					if (ddDisplayDevice.cb>178)
						posout+=sprintf(posout,"%s\x1%s",ddDisplayDevice.DeviceID,ddDisplayDevice.DeviceKey);
					else
					{
						*(posout++)=0x1;
						*posout=0;
					}
					char *tmps=new char [1000+(int)strlen(ddDisplayDevice.DeviceName)];
					sprintf(tmps,"EnumDisplayDevices %s,-1",ddDisplayDevice.DeviceName);
					*(posout++)=0x1;
					*posout=0;
					DoMethod(tmps,posout);
					DelimitersDown(posout);
					posout=DelimitersDown(posout);
					if (bDSettings)
					{
						sprintf(tmps,"EnumDisplaySettings %s",ddDisplayDevice.DeviceName);
						*(posout++)=0x1;
						*posout=0;
						DoMethod(tmps,posout);
						DelimitersDown(posout);
						posout=DelimitersDown(posout);
					}

					delete [] tmps;
				}
			}
			break;
	#endif
		case 47:/*EnumDisplaySettings DeviceName*/
			if (oStr)
			{
				if (*pos)
				{
					char *devname=new char [(int)strlen(pos)+100];
					strcpy(devname,ExtractField(pos,1,","));
					char *pdev=devname;
					if (!*devname) pdev=NULL;
					char *posout=oStr;
					DEVMODE mdm={0};
					mdm.dmSize=sizeof(DEVMODE);
					strcpy(posout,"ENUM_REGISTRY_SETTINGS\x1ENUM_CURRENT_SETTINGS\x7F");
					while(*posout) posout++;
					EnumDisplaySettings(pdev,ENUM_REGISTRY_SETTINGS,&mdm);
					DEVMODEToString(&mdm,posout);
					posout=DelimitersDown(posout);
					while(*posout) posout++;
					*(posout++)=0x7F;
					*posout=0;
					EnumDisplaySettings(pdev,ENUM_CURRENT_SETTINGS,&mdm);
					DEVMODEToString(&mdm,posout);
					posout=DelimitersDown(posout);

					const char *posmode=strchr(pos,',');
					if (posmode && *(++posmode))
					{
						if (atoi(posmode)<0)
						{
							int i;
							for(i=0; EnumDisplaySettings(pdev,i,&mdm) && i<5;i++)
							{
								*(posout++)=0x7F;
								*posout=0;
								DEVMODEToString(&mdm,posout);
								posout=DelimitersDown(posout);
							}
						}
						else
						{
							while(posmode)
							{
								*(posout++)=0x7F;
								*posout=0;
								if (EnumDisplaySettings(pdev,atoi(posmode),&mdm))
								{
									DEVMODEToString(&mdm,posout);
									posout=DelimitersDown(posout);
								}
								posmode=strchr(posmode,',');
								if (posmode) posmode++;
							}
						}
					}
					delete [] devname;

				}
				else strcpy(oStr,"ERROR - Empty Device Name");

			}
			break;
			 

		case 48: /* GetSystemMetrics nIndex[;nIndex...]*/
			if (oStr)
			{
				int i,nIndex=-1;
				char *postxt=oStr;
				if (atoipos==-1 || !*pos)
				{
					for(nIndex=0;nIndex<100;nIndex++)
					{
						if (nIndex) *(postxt++)=0x7F;
						*postxt=0;
						postxt+=sprintf(postxt,"%s\x1%d",chMetricsNames[nIndex],GetSystemMetrics(nIndex));
					}
				}
				else
				{
					CString tmppos;
					for(i=0;(tmppos=ExtractField(pos,i,";"))!="";i++)
					{
						int j;
						if ((nIndex=atoi(tmppos))==0 && tmppos[0]!='0')
						{
							for(j=0,nIndex=-1;j<100 && nIndex==-1;j++)
								if (tmppos==chMetricsNames[j]) nIndex=uMetricsNames[j];
						}
						if (i) *(postxt++)=0x7F;
						*postxt=0;
						postxt+=sprintf(postxt,"%d",GetSystemMetrics(nIndex));
					}
				}
			}
			break;
		case 49: /*GetSysColor nIndex[;nIndex...]*/
			if (oStr)
			{
				int i,nIndex=-1;
				COLORREF clr=0;
				char *postxt=oStr;
				if (atoipos==-1 || !*pos)
				{
					for(nIndex=0;nIndex<37;nIndex++)
					{
						if (nIndex) *(postxt++)=0x7F;
						*postxt=0;
						clr=GetSysColor(uColorNames[nIndex]);
						postxt+=sprintf(postxt,"%s\x1%d\x07%d\x07%d",chColorNames[nIndex],GetRValue(clr),GetGValue(clr),GetBValue(clr));
					}
				}
				else
				{
					CString tmppos;
					for(i=0;(tmppos=ExtractField(pos,i,";"))!="";i++)
					{
						int j;
						if ((nIndex=atoi(tmppos))==0 && tmppos[0]!='0')
						{
							for(nIndex=-1,j=0;j<37 && nIndex==-1;j++)
								if (tmppos==chColorNames[j]) nIndex=uColorNames[j];
						}
						if (i) *(postxt++)=0x7F;
						*postxt=0;
						clr=GetSysColor(nIndex);
						postxt+=sprintf(postxt,"%d\x07%d\x07%d",GetRValue(clr),GetGValue(clr),GetBValue(clr));
					}
				}
			}
			break;
		case 50: /*GetSysColorBrush nIndex[;nIndex...]*/
			if (oStr)
			{
				int i,nIndex=-1;
				char *postxt=oStr;
				if (atoipos==-1 || !*pos)
				{
					for(nIndex=0;nIndex<37;nIndex++)
					{
						if (nIndex) *(postxt++)=0x7F;
						*postxt=0;
						LOGBRUSH LogBrush={0};
						HBRUSH hbru=GetSysColorBrush(nIndex);
						postxt+=sprintf(postxt,"%s\x1",chColorNames[nIndex]);
						if (hbru)
						{
							CBrush::FromHandle(hbru)->GetLogBrush(&LogBrush);
							GPGetBrushString(&LogBrush,postxt);
						}
						else strcpy(postxt,"NULL");
						while(*postxt) postxt++;
					}
				}
				else
				{
					CString tmppos;
					for(i=0;(tmppos=ExtractField(pos,i,";"))!="";i++)
					{
						int j;
						for(j=0;j<37 && nIndex==-1;j++)
							if (tmppos==chColorNames[j]) nIndex=uColorNames[j];
						if (i) *(postxt++)=0x7F;
						*postxt=0;
						LOGBRUSH LogBrush={0};
						CBrush::FromHandle(GetSysColorBrush(nIndex))->GetLogBrush(&LogBrush);
						GPGetBrushString(&LogBrush,postxt);
						while(*postxt) postxt++;
					}
				}
			}
			break;
		case 51: /*SetSysColors nIndex=R,G,B[;nIndex=R,G,B]*/
			{
				CString tmppos;
				int mR,mG,mB;
				COLORREF retrgb=0;
				DWORD a_rgb[30];
				int	  a_ind[30];
				int ni=0;
				for(ni=0;(tmppos=ExtractField(pos,ni,";"))!="" && ni<29;ni++)
				{
					CString csIndex=ExtractField(tmppos,1,",");
					int nIndex=atoi(csIndex);
					if (csIndex[0]!='0' && nIndex!=0)
					{
						int i;
						for(i=0,nIndex=-1;i<37 && nIndex==-1;i++)
							if (csIndex==chColorNames[i]) nIndex=uColorNames[i];
					}
					a_ind[ni]=nIndex;
					retrgb=GetSysColor(nIndex);
					mR=GetRValue(retrgb);
					mG=GetGValue(retrgb);
					mB=GetBValue(retrgb);
					csIndex=ExtractField(tmppos,2,"=");
					m_LastScanf=sscanf(csIndex,"%d,%d,%d",&mR,&mG,&mB);
					a_rgb[ni]=RGB(mR,mG,mB);
				}
				if (ni>0)	retint=SetSysColors(ni,a_ind,a_rgb);
			}
			break;
		case 52: /*AddMonitor SrvName,[level],MonitName,Environment,DLLName*/
			{
				char *buff= new char [(int)strlen(pos)+10];
				strcpy(buff,pos);
				MONITOR_INFO_2 mi={0};
				char *postmp=buff;
				int level=2;
				mi.pDLLName="";
				mi.pEnvironment="";
				mi.pName="";
				if ((postmp=strchr(postmp,',')))
				{
					*(postmp++)=0;
					if (*postmp>='0' && *postmp<='9')  level=atoi(postmp);
					if ((postmp=strchr(postmp,',')))
					{
						*(postmp++)=0;
						mi.pName=postmp;
						if ((postmp=strchr(postmp,',')))
						{
							*(postmp++)=0;
							mi.pEnvironment=postmp;
							if ((postmp=strchr(postmp,',')))
							{
								*(postmp++)=0;
								mi.pDLLName=postmp;
							}
						}
					}
				} 
				retint=AddMonitor(*buff?buff:NULL,level,(LPBYTE)&mi);
				delete [] buff;
			}
			break;
		case 53: /*AddPort SrvName,[Parent],MonitName*/
		case 56: /*ConfigurePort SrvName,[Parent],PortName*/
		case 58: /*DeletePort  SrvName,[Parent],PortName*/
			{
				GPUNITINFO iUi;
				GPC.m_Document->FindObject(ExtractField(pos,2,","), "0",iUi);
				HWND tmpHWND=(iUi.hWnd)?iUi.hWnd:GPC.m_hViewWnd;
				char *nm=new char [10000];
				strcpy(nm,ExtractField(pos,1,","));
				strcpy(nm+5000,ExtractField(pos,3,","));
				switch(nfunc)
				{
				case 53: retint=AddPort(*nm?NULL:nm,tmpHWND,nm+5000); break;
				case 56: retint=ConfigurePort(*nm?NULL:nm,tmpHWND,nm+5000); break;
				case 58: retint=DeletePort(*nm?NULL:nm,tmpHWND,nm+5000); break;
				}
				delete [] nm;
			}
			break;
		case 54: /*AddPrinterConnection Name*/
		case 59: /*DeletePrinterConnection Name*/
			{
				char *nm=new char [10000];
				strcpy(nm,pos);
				switch(nfunc)
				{
				case 54: retint=AddPrinterConnection(nm); break;
				case 59: retint=DeletePrinterConnection(nm); break;
				}
				delete [] nm;
			}
			break;
		case 55: /*AddPrintProcessor SrvName,Environment,PathName,PrintProcessorName*/
			{
				char *buff= new char [(int)strlen(pos)+10];
				strcpy(buff,pos);
				char *postmp=buff;
				char *Environment="",*PathName="",*PrintProcessorName="";
				if ((postmp=strchr(postmp,',')))
				{
					*(postmp++)=0;
					if ((postmp=strchr(postmp,',')))
					{
						*(postmp++)=0;
						Environment=postmp;
						if ((postmp=strchr(postmp,',')))
						{
							*(postmp++)=0;
							PathName=postmp;
							if ((postmp=strchr(postmp,',')))
							{
								*(postmp++)=0;
								PrintProcessorName=postmp;
							}
						}
					}
				} 
				if (!*Environment) Environment=NULL;
				retint=AddPrintProcessor(*buff?buff:NULL,Environment,PathName,PrintProcessorName);
				delete [] buff;
			}
			break;
		case 57: /*DeleteMonitor SrvName,Environment,MonitName*/
		case 60: /*DeletePrinterDriver SrvName,Environment,DriverName*/
		case 62: /*DeletePrintProcessor SrvName,Environment,ProcName*/
		case 63: /*DeletePrintProvidor SrvName,Environment,ProvidorName*/
			{
				char *buff= new char [(int)strlen(pos)+10];
				strcpy(buff,pos);
				char *postmp=buff;
				char *Environment="",*MonitName="";
				if ((postmp=strchr(postmp,',')))
				{
					*(postmp++)=0;
					if ((postmp=strchr(postmp,',')))
					{
						*(postmp++)=0;
						Environment=postmp;
						if ((postmp=strchr(postmp,',')))
						{
							*(postmp++)=0;
							MonitName=postmp;
						}
					}
				} 
				if (!*Environment) Environment=NULL;
				switch(nfunc)
				{
				case 57:	retint=DeleteMonitor(*buff?buff:NULL,Environment,MonitName);break;
				case 60:	retint=DeletePrinterDriver(*buff?buff:NULL,Environment,MonitName);break;
				case 62:	retint=DeletePrintProcessor(*buff?buff:NULL,Environment,MonitName);break;
				case 63:	retint=DeletePrintProvidor(*buff?buff:NULL,Environment,MonitName);break;
				}
				delete [] buff;
			}
			break;
		#ifdef W_95
		#else
			#ifdef W_98
			#else
				#ifdef W_NT
				#else
					case 61: /*DeletePrinterDriverEx SrvName,Environment,DriverName,options,version*/
						{
							char *buff= new char [(int)strlen(pos)+10];
							strcpy(buff,pos);
							char *postmp=buff;
							char *Environment="",*DriverName="";
							DWORD options=0,version=0;
							if ((postmp=strchr(postmp,',')))
							{
								*(postmp++)=0;
								if ((postmp=strchr(postmp,',')))
								{
									*(postmp++)=0;
									Environment=postmp;
									if ((postmp=strchr(postmp,',')))
									{
										*(postmp++)=0;
										DriverName=postmp;
										if ((postmp=strchr(postmp,',')))
										{
											*(postmp++)=0;
											char *posoptions=postmp;
											if ((postmp=strchr(postmp,',')))
											{
												version=atoi(++postmp);
											}
											_strupr(posoptions);
											if (strstr(posoptions,"SP")) options|=DPD_DELETE_SPECIFIC_VERSION ;
											if (strstr(posoptions,"UN")) options|=DPD_DELETE_UNUSED_FILES;
											if (strstr(posoptions,"AL")) options|=DPD_DELETE_ALL_FILES ;
										}
									}
								}
							} 
							if (!*Environment) Environment=NULL;
							retint=DeletePrinterDriverEx(*buff?buff:NULL,Environment,DriverName,options,version);
							delete [] buff;
						}
						break;
				#endif
			#endif
		#endif
		case 64: /*GetDefaultPrinter*/
			if (oStr)
			{

		#ifdef W_95
					::GetProfileString(TEXT("Windows"),TEXT("Device"),_T(",,,"),oStr, 1000);
		#else
			#ifdef W_98
					::GetProfileString(TEXT("Windows"),TEXT("Device"),_T(",,,"),oStr, 1000);
			#else
				#ifdef W_NT
					::GetProfileString(TEXT("Windows"),TEXT("Device"),_T(",,,"),oStr, 1000);
				#else
				{
					DWORD nb=5000;
					GetDefaultPrinter(oStr,&nb);
				}
				break;
				#endif
			#endif
		#endif


			}
			break;
		case 65: /*GetPrinterDriverDirectory SrvName,Environment*/
		case 66: /*GetPrintProcessorDirectory SrvName,Environment*/
			if (oStr)
			{
				char *buff= new char [(int)strlen(pos)+10];
				strcpy(buff,pos);
				char *postmp=buff;
				char *Environment="";
				DWORD bn=0;
				if ((postmp=strchr(postmp,',')))
				{
					*(postmp++)=0;
					Environment=postmp;
				} 
				BOOL ret=FALSE;
				if (!*Environment) Environment=NULL;
				switch(nfunc)
				{
				case 65: ret=GetPrinterDriverDirectory(*buff?buff:NULL,Environment,1,(unsigned char *)oStr,5000,&bn); break;
				case 66: ret=GetPrintProcessorDirectory(*buff?buff:NULL,Environment,1,(unsigned char *)oStr,5000,&bn); break;
				}
				if (!ret) strcpy(oStr,"!!!Error");
				delete [] buff;
			}
			break;
		case 67: /*SetDefaultPrinter Name*/
		#ifdef W_95
					if (oStr) ::GetProfileString(TEXT("Windows"),TEXT("Device"),_T(",,,"),oStr, 1000);
					::WriteProfileString(TEXT("Windows"),TEXT("Device"),pos );
					::SendNotifyMessage(HWND_BROADCAST,WM_WININICHANGE,0,(LPARAM)TEXT("Windows\\Device"));
		#else
			#ifdef W_98
					if (oStr) ::GetProfileString(TEXT("Windows"),TEXT("Device"),_T(",,,"),oStr, 1000);
					::WriteProfileString(TEXT("Windows"),TEXT("Device"),pos );
					::SendNotifyMessage(HWND_BROADCAST,WM_WININICHANGE,0,(LPARAM)TEXT("Windows\\Device"));
			#else
				#ifdef W_NT
					if (oStr) ::GetProfileString(TEXT("Windows"),TEXT("Device"),_T(",,,"),oStr, 1000);
					::WriteProfileString(TEXT("Windows"),TEXT("Device"),pos );
					::SendNotifyMessage(HWND_BROADCAST,WM_WININICHANGE,0,(LPARAM)TEXT("Windows\\Device"));
				#else
				{
					DWORD nb=5000;
					if (oStr) GetDefaultPrinter(oStr,&nb);
					if (!SetDefaultPrinter(pos) && oStr) strcpy(oStr,"!!!Error");
				}
				break;
				#endif
			#endif
		#endif

		#ifdef W_95
		#else
			#ifdef W_98
			#else
				case 68: /*SetPort [SrvName],PortName,Status,StatusText,Severity*/
					{
						PORT_INFO_3 mPortInfo={0};
						char *buff= new char [(int)strlen(pos)+10];
						strcpy(buff,pos);
						char *postmp=buff;
						char *PortName="";
						DWORD bn=0;
						if ((postmp=strchr(postmp,',')))
						{
							*(postmp++)=0;
							PortName=postmp;
							if ((postmp=strchr(postmp,',')))
							{
								*(postmp++)=0;
								StringFromToPORT_INFO_3(postmp, NULL, mPortInfo);
							} 
						} 
						retint=SetPort(*buff?buff:NULL,PortName,3,(LPBYTE)&mPortInfo);
					}
					break;
			#endif
		#endif
		case 69: /*EnumPorts [SrvName],level=1*/
		case 70: /*EnumMonitors [SrvName],level=1*/
			if (oStr)
			{
				char *buff= new char [(int)strlen(pos)+10];
				strcpy(buff,pos);
				char *postmp=buff;
				int level=1;
				if ((postmp=strchr(postmp,',')))
				{
					*(postmp++)=0;
					level=atoi(postmp);
					if (level!=2) level=1;
				} 
				DWORD nStruct=0,nBytes=0;
				switch(nfunc)
				{
				case 69:
					{
						EnumPorts(*buff?buff:NULL,level,NULL,0,&nBytes,&nStruct);
						if (nBytes)
						{
							DWORD i;
							BYTE *tmps=new BYTE [nBytes+100];
							EnumPorts(*buff?buff:NULL,level,tmps,nBytes+100,&nBytes,&nStruct);
							char *posout=oStr;
							for(i=0;i<nStruct;i++)
							{
								if (i) *(posout++)=0x7F;
								*posout=0;
								switch(level)
								{
								case 1:
									{
										PORT_INFO_1 *mPortInfo=(PORT_INFO_1 *)tmps;
										strcpy(posout,(mPortInfo[i].pName)?mPortInfo[i].pName:"");
									}
									break;
								case 2:
									{
										PORT_INFO_2 *mPortInfo2=(PORT_INFO_2 *)tmps;
										posout+=sprintf(posout,"%s\x1%s\x1%s\x1",
											mPortInfo2[i].pPortName?mPortInfo2[i].pPortName:"",
											mPortInfo2[i].pMonitorName?mPortInfo2[i].pMonitorName:"",
											mPortInfo2[i].pDescription?mPortInfo2[i].pDescription:""
											);
										DwordToStringMask(0,mPortInfo2[i].fPortType,posout,adwPIPortType,acPIPortType);
									}
									break;
								}
								while(*posout) posout++;
							}
							delete [] tmps;
						}
					}
					break;
				case 70:
					{
						EnumMonitors(*buff?buff:NULL,level,NULL,0,&nBytes,&nStruct);
						if (nBytes)
						{
							DWORD i;
							BYTE *tmps=new BYTE [nBytes+100];
							EnumMonitors(*buff?buff:NULL,level,tmps,nBytes+100,&nBytes,&nStruct);
							char *posout=oStr;
							for(i=0;i<nStruct;i++)
							{
								if (i) *(posout++)=0x7F;
								*posout=0;
								switch(level)
								{
								case 1:
									{
										MONITOR_INFO_1 *mPortInfo=(MONITOR_INFO_1 *)tmps;
										strcpy(posout,(mPortInfo[i].pName)?mPortInfo[i].pName:"");
									}
									break;
								case 2:
									{
										MONITOR_INFO_2 *mPortInfo=(MONITOR_INFO_2 *)tmps;
										posout+=sprintf(posout,"%s\x1%s\x1%s",
											mPortInfo[i].pName?mPortInfo[i].pName:"",
											mPortInfo[i].pEnvironment?mPortInfo[i].pEnvironment:"",
											mPortInfo[i].pDLLName?mPortInfo[i].pDLLName:""
											);
									}
									break;
								}
								while(*posout) posout++;
							}
							delete [] tmps;
						}
					}
					break;
				}
				delete [] buff;
			}
			break;
		case 71: /*EnumPrinterDrivers [SrvName],[Environment],level=1*/
			if (oStr)
			{
				char *Environment="";
				char *buff= new char [(int)strlen(pos)+10];
				strcpy(buff,pos);
				char *postmp=buff;
				int level=1;
				if ((postmp=strchr(postmp,',')))
				{
					*(postmp++)=0;
					Environment=postmp;
					if ((postmp=strchr(postmp,',')))
					{
						*(postmp++)=0;
						level=atoi(postmp);
						if (level<1 || level>6 ) level=1;
					} 
				} 
				DWORD nStruct=0,nBytes=0;
				if (!*Environment) Environment=NULL;
				EnumPrinterDrivers(*buff?buff:NULL,Environment,level,NULL,0,&nBytes,&nStruct);
				if (nBytes)
				{
					DWORD i;
					BYTE *tmps=new BYTE [nBytes+100];
					EnumPrinterDrivers(*buff?buff:NULL,Environment,level,tmps,nBytes+100,&nBytes,&nStruct);
					char *posout=oStr;
					for(i=0;i<nStruct;i++)
					{
						if (i) *(posout++)=0x7F;
						*posout=0;
						switch(level)
						{
						case 1:
							{
								DRIVER_INFO_1 *mPortInfo=(DRIVER_INFO_1 *)tmps;
								strcpy(posout,(mPortInfo[i].pName)?mPortInfo[i].pName:"");
							}
							break;
						case 2:
							{
								DRIVER_INFO_2 *mPortInfo=(DRIVER_INFO_2 *)tmps;
								posout+=sprintf(posout,"%X\x1%s\x1%s\x1%s\x1%s\x1%s",
									mPortInfo[i].cVersion,
									mPortInfo[i].pName?mPortInfo[i].pName:"",
									mPortInfo[i].pEnvironment?mPortInfo[i].pEnvironment:"",
									mPortInfo[i].pDriverPath?mPortInfo[i].pDriverPath:"",
									mPortInfo[i].pDataFile?mPortInfo[i].pDataFile:"",
									mPortInfo[i].pConfigFile?mPortInfo[i].pConfigFile:""
									);
							}
							break;
						case 3:
							{
								DRIVER_INFO_3 *mPortInfo=(DRIVER_INFO_3 *)tmps;
								posout+=sprintf(posout,"%X\x1%s\x1%s\x1%s\x1%s\x1%s\x1%s\x1%s\x1%s\x1%s",
									mPortInfo[i].cVersion,
									mPortInfo[i].pName?mPortInfo[i].pName:"",
									mPortInfo[i].pEnvironment?mPortInfo[i].pEnvironment:"",
									mPortInfo[i].pDriverPath?mPortInfo[i].pDriverPath:"",
									mPortInfo[i].pDataFile?mPortInfo[i].pDataFile:"",
									mPortInfo[i].pConfigFile?mPortInfo[i].pConfigFile:"",
									mPortInfo[i].pHelpFile?mPortInfo[i].pHelpFile:"",
									mPortInfo[i].pDependentFiles?mPortInfo[i].pDependentFiles:"",
									mPortInfo[i].pMonitorName?mPortInfo[i].pMonitorName:"",
									mPortInfo[i].pDefaultDataType?mPortInfo[i].pDefaultDataType:""
									);
							}
							break;
						case 4:
							{
								DRIVER_INFO_4 *mPortInfo=(DRIVER_INFO_4 *)tmps;
								posout+=sprintf(posout,"%X\x1%s\x1%s\x1%s\x1%s\x1%s\x1%s\x1%s\x1%s\x1%s\x1%s",
									mPortInfo[i].cVersion,
									mPortInfo[i].pName?mPortInfo[i].pName:"",
									mPortInfo[i].pEnvironment?mPortInfo[i].pEnvironment:"",
									mPortInfo[i].pDriverPath?mPortInfo[i].pDriverPath:"",
									mPortInfo[i].pDataFile?mPortInfo[i].pDataFile:"",
									mPortInfo[i].pConfigFile?mPortInfo[i].pConfigFile:"",
									mPortInfo[i].pHelpFile?mPortInfo[i].pHelpFile:"",
									mPortInfo[i].pDependentFiles?mPortInfo[i].pDependentFiles:"",
									mPortInfo[i].pMonitorName?mPortInfo[i].pMonitorName:"",
									mPortInfo[i].pDefaultDataType?mPortInfo[i].pDefaultDataType:"",
									mPortInfo[i].pszzPreviousNames?mPortInfo[i].pszzPreviousNames :""
									);
							}
							break;
						case 5:
							{
								DRIVER_INFO_5 *mPortInfo=(DRIVER_INFO_5 *)tmps;
								posout+=sprintf(posout,"%X\x1%s\x1%s\x1%s\x1%s\x1%s\x1%X\x1%X\x1%X",
									mPortInfo[i].cVersion,
									mPortInfo[i].pName?mPortInfo[i].pName:"",
									mPortInfo[i].pEnvironment?mPortInfo[i].pEnvironment:"",
									mPortInfo[i].pDriverPath?mPortInfo[i].pDriverPath:"",
									mPortInfo[i].pDataFile?mPortInfo[i].pDataFile:"",
									mPortInfo[i].pConfigFile?mPortInfo[i].pConfigFile:"",
									mPortInfo[i].dwDriverAttributes,
									mPortInfo[i].dwConfigVersion,
									mPortInfo[i].dwDriverVersion
									);
							}
							break;
						case 6:
							{
								DRIVER_INFO_6 *mPortInfo=(DRIVER_INFO_6 *)tmps;
								SYSTEMTIME st={0};
								posout+=sprintf(posout,"%X\x1%s\x1%s\x1%s\x1%s\x1%s\x1%s\x1%s\x1%s\x1%s\x1%s",
									mPortInfo[i].cVersion,
									mPortInfo[i].pName?mPortInfo[i].pName:"",
									mPortInfo[i].pEnvironment?mPortInfo[i].pEnvironment:"",
									mPortInfo[i].pDriverPath?mPortInfo[i].pDriverPath:"",
									mPortInfo[i].pDataFile?mPortInfo[i].pDataFile:"",
									mPortInfo[i].pConfigFile?mPortInfo[i].pConfigFile:"",
									mPortInfo[i].pHelpFile?mPortInfo[i].pHelpFile:"",
									mPortInfo[i].pDependentFiles?mPortInfo[i].pDependentFiles:"",
									mPortInfo[i].pMonitorName?mPortInfo[i].pMonitorName:"",
									mPortInfo[i].pDefaultDataType?mPortInfo[i].pDefaultDataType:"",
									mPortInfo[i].pszzPreviousNames?mPortInfo[i].pszzPreviousNames:""
									);
								FileTimeToSystemTime(&mPortInfo[i].ftDriverDate,&st);
								posout+=sprintf(posout,"\x1%d\x2%d\x2%d\x2%d\x2%d\x2%d\x2%d\x2%d\x1",
									mPortInfo[i].ftDriverDate.dwLowDateTime,
									mPortInfo[i].ftDriverDate.dwHighDateTime,
									st.wYear,
									st.wMonth,
									st.wDay,
									st.wHour,
									st.wMinute,
									st.wSecond
									);
								posout+=sprintf(posout,"%8.8X%8.8X\x1%s\x1%s\x1%s\x1%s",
									((DWORD *)(&mPortInfo[i].dwlDriverVersion))[0],
									((DWORD *)(&mPortInfo[i].dwlDriverVersion))[1],
									mPortInfo[i].pszMfgName?mPortInfo[i].pszMfgName:"",
									mPortInfo[i].pszOEMUrl?mPortInfo[i].pszOEMUrl:"",
									mPortInfo[i].pszHardwareID?mPortInfo[i].pszHardwareID:"",
									mPortInfo[i].pszProvider?mPortInfo[i].pszProvider:""
									);
							}
							break;
						}
						while(*posout) posout++;
					}
					delete [] tmps;
				}
				delete [] buff;
			}
			break;
		case 72: /*EnumPrintProcessorDatatypes [SrvName],[ProcName]*/
			if (oStr)
			{
				char *ProcName="";
				char *buff= new char [(int)strlen(pos)+10];
				strcpy(buff,pos);
				char *postmp=buff;
				if ((postmp=strchr(postmp,',')))
				{
					*(postmp++)=0;
					ProcName=postmp;
					if ((postmp=strchr(postmp,',')))
					{
						*(postmp++)=0;
					} 
				} 
				char *posout=oStr;
				DWORD nStruct=0,nBytes=0;
				if (!*ProcName) 
				{
					CString tmps="EnumPrintProcessors ";
					tmps+=buff;
					char *buff2=new char [20000];
					*buff2=0;
					DoMethod(tmps,buff2);
					int i=0;
					while((tmps=ExtractField(buff2,++i,"\x7F"))!="")
					{
						CString tmpcom="EnumPrintProcessorDatatypes ";
						tmpcom+=buff;
						tmpcom+=","+tmps;
						if (*oStr) *(posout++)=0x7F;
						strcpy(posout,tmps);
						while(*posout) posout++;
						DoMethod(tmpcom,posout);
						posout=DelimitersDown(posout);
					}
					delete []buff2;
				}
				else
				{
					EnumPrintProcessorDatatypes(*buff?buff:NULL,ProcName,1,NULL,0,&nBytes,&nStruct);
					if (nBytes)
					{
						DWORD i;
						BYTE *tmps=new BYTE [nBytes+100];
						EnumPrintProcessorDatatypes(*buff?buff:NULL,ProcName,1,tmps,nBytes+100,&nBytes,&nStruct);
						for(i=0;i<nStruct;i++)
						{
							if (i) *(posout++)=0x7F;
							*posout=0;
							DATATYPES_INFO_1 *mPortInfo=(DATATYPES_INFO_1 *)tmps;
							strcpy(posout,(mPortInfo[i].pName)?mPortInfo[i].pName:"");
							while(*posout) posout++;
						}
						delete [] tmps;
					}
				}
				delete [] buff;
			}
			break;
		case 73: /*EnumPrintProcessors [SrvName],[Environment]*/
			if (oStr)
			{
				char *Environment="";
				char *buff= new char [(int)strlen(pos)+10];
				strcpy(buff,pos);
				char *postmp=buff;
				if ((postmp=strchr(postmp,',')))
				{
					*(postmp++)=0;
					Environment=postmp;
					if ((postmp=strchr(postmp,','))) *(postmp++)=0;
				} 
				DWORD nStruct=0,nBytes=0;
				if (!*Environment) Environment=NULL;
				EnumPrintProcessors(*buff?buff:NULL,Environment,1,NULL,0,&nBytes,&nStruct);
				if (nBytes)
				{
					DWORD i;
					BYTE *tmps=new BYTE [nBytes+100];
					EnumPrintProcessors(*buff?buff:NULL,Environment,1,tmps,nBytes+100,&nBytes,&nStruct);
					char *posout=oStr;
					for(i=0;i<nStruct;i++)
					{
						if (i) *(posout++)=0x7F;
						*posout=0;
						PRINTPROCESSOR_INFO_1 *mPortInfo=(PRINTPROCESSOR_INFO_1 *)tmps;
						strcpy(posout,(mPortInfo[i].pName)?mPortInfo[i].pName:"");
						while(*posout) posout++;
					}
					delete [] tmps;
				}
				delete [] buff;
			}
			break;
		case 74: /*AddPrintProvidor [SrvName],level=1,PROVIDOR_INFO_level]*/
			{
				char *buff= new char [(int)strlen(pos)+10];
				int level=1;
				strcpy(buff,pos);
				char *postmp=buff;
				char *ptr1="",*ptr2="",*ptr3="";
				if ((postmp=strchr(postmp,',')))
				{
					*(postmp++)=0;
					level=atoi(postmp);
					if (level<1 || level>2 ) level=1;
					if ((postmp=strchr(postmp,',')))
					{
						*(postmp++)=0;
						ptr1=postmp;
						if ((postmp=strchr(postmp,',')))
						{
							*(postmp++)=0;
							ptr2=postmp;
							if ((postmp=strchr(postmp,',')))
							{
								*(postmp++)=0;
								ptr3=postmp;
								if ((postmp=strchr(postmp,',')))
								{
									*(postmp++)=0;
								}
							}
						}
					}
				} 
				switch(level)
				{
				case 1:
					{
						PROVIDOR_INFO_1 pi={0};
						pi.pName=ptr1;
						pi.pEnvironment=ptr2;
						pi.pDLLName=ptr3;
						retint=AddPrintProvidor(*buff?buff:NULL,level,(LPBYTE)&pi);
						break;
					}
				case 2:
					{
						PROVIDOR_INFO_2 pi={0};
						pi.pOrder=ptr1;
						retint=AddPrintProvidor(*buff?buff:NULL,level,(LPBYTE)&pi);
						break;
					}
				}
				delete [] buff;
			}
			break;
		case 75: /*AddPrinterDriver [SrvName],level=2,PROVIDOR_INFO_level*/
		#ifdef W_95
		#else
			#ifdef W_98
			#else
				#ifdef W_NT
				#else
					case 76: /*AddPrinterDriverEx [SrvName],level=2,PROVIDOR_INFO_level,FileCopyFlags*/
				#endif
			#endif
		#endif
			{
				char *buff= new char [(int)strlen(pos)+100];
				const char *postmp=pos;
				char *bufftmp=buff;
				char *ptrstr[20];
				int i=0;
				ptrstr[i++]=buff;
				do
				{
					*bufftmp=*postmp;
					if (*postmp==',' || *postmp=='\x7F') 
					{
						*(bufftmp++)=0;
						*(bufftmp++)=0;
						*bufftmp=0;
						ptrstr[i++]=bufftmp;
					}
					else bufftmp++;
					postmp++;
				}
				while(i<20 && *postmp);

				int level=atoi(ptrstr[1]);
				if (level<2 || level>6 || level==5) level=2;
				BYTE *barray=new BYTE [sizeof(DRIVER_INFO_6)+16];
				char *copyflags=(level==6)?ptrstr[19]:(level==4)?ptrstr[13]:(level==3)?ptrstr[12]:ptrstr[8];
				switch(level)
				{
				case 6:
					{
						PDRIVER_INFO_6 di=(PDRIVER_INFO_6)barray;
						SYSTEMTIME st={0};
						m_LastScanf=sscanf(ptrstr[13],"%d/%d/%d/%d/%d/%d",&st.wYear,&st.wMonth,&st.wDay,&st.wHour,&st.wMinute,&st.wSecond);
						SystemTimeToFileTime(&st,&di->ftDriverDate);
						m_LastScanf=sscanf(ptrstr[14],"%8.8X%8.8X",((DWORD *)&di->dwlDriverVersion),((DWORD *)&di->dwlDriverVersion)+1);
						di->pszMfgName=ptrstr[15];
						di->pszOEMUrl=ptrstr[16];
						di->pszHardwareID=ptrstr[17];
						di->pszProvider=ptrstr[18];
					}
				case 4:
					{
						PDRIVER_INFO_4 di=(PDRIVER_INFO_4)barray;
						di->pszzPreviousNames=ptrstr[12];
					}
				case 3:
					{
						PDRIVER_INFO_3 di=(PDRIVER_INFO_3)barray;
						di->pHelpFile=ptrstr[8];
						di->pDependentFiles=ptrstr[9];
						di->pMonitorName=(*ptrstr[10])?ptrstr[10]:NULL;
						di->pDefaultDataType=ptrstr[11];
						bufftmp=ptrstr[9];
						while(*bufftmp)
						{
							if (*bufftmp=='|' || *bufftmp=='\x1') *bufftmp=0;
							bufftmp++;
						}
					}
				case 2:
					{
						PDRIVER_INFO_2 di=(PDRIVER_INFO_2)barray;
						di->cVersion=atoi(ptrstr[2]);
						di->pName=ptrstr[3];
						di->pEnvironment=ptrstr[4];
						di->pDriverPath=ptrstr[5];
						di->pDataFile=ptrstr[6];
						di->pConfigFile=ptrstr[7];
					}
					break;
				}

				switch(nfunc)
				{
				case 75:
					retint=AddPrinterDriver(*ptrstr[0]?ptrstr[0]:NULL,level,barray);
					break;
				#ifdef W_95
				#else
					#ifdef W_98
					#else

						#ifdef W_NT
						#else
							case 76:
								{
									_strupr(copyflags);
									DWORD dwCPFlags=atoi(copyflags);
									if (strstr(copyflags,"AL")) dwCPFlags|=APD_COPY_ALL_FILES;
									if (strstr(copyflags,"DI")) dwCPFlags|=APD_COPY_FROM_DIRECTORY;
									if (strstr(copyflags,"NE")) dwCPFlags|=APD_COPY_NEW_FILES;
									if (strstr(copyflags,"DO")) dwCPFlags|=APD_STRICT_DOWNGRADE;
									if (strstr(copyflags,"UP")) dwCPFlags|=APD_STRICT_UPGRADE;

									retint=AddPrinterDriverEx(*ptrstr[0]?ptrstr[0]:NULL,level,barray,dwCPFlags);
								}
								break;
						#endif
					#endif
				#endif

				}
				delete [] barray;
				delete [] buff;
			}
			break;
		#ifdef W_95
		#else
			#ifdef W_98
			#else
			case 77: /*EnumServicesStatusEx [InfoLevel=0],ServiceType,ServiceState*/
				if (oStr)
				{
					if (!GPC.m_SC_HANDLE) DoMethod("OpenSCManager",NULL);
					if (GPC.m_SC_HANDLE)
					{
						DWORD InfoLevel=atoi(pos);
						DWORD ServiceType=0;
						DWORD ServiceState=0;
						CString csTmps;
						ServiceType=StringToDword(ExtractField(pos,2,","), acSSPServiceType, adwSSPServiceType);
						ServiceState=StringToDword(ExtractField(pos,3,","), acSSPServiceState, adwSSPServiceState);
							
						if (!ServiceType) ServiceType=SERVICE_WIN32;
						if (!ServiceState) ServiceState=SERVICE_ACTIVE;

						csTmps=ExtractField(pos,4,",");
						DWORD cbBytesNeeded=0;
						DWORD ServicesReturned=0;
						DWORD ResumeHandle=0;
						EnumServicesStatusEx(
								GPC.m_SC_HANDLE, (SC_ENUM_TYPE)InfoLevel, ServiceType, ServiceState,
								NULL, 0, &cbBytesNeeded, &ServicesReturned, &ResumeHandle,
								(csTmps=="")?NULL:((csTmps==" ")?"":(LPCSTR)csTmps)
								);

						if (cbBytesNeeded)
						{
							BYTE *baArray=new BYTE [cbBytesNeeded+1000];
							BYTE *baTmpArray=new BYTE [5000];
							DWORD i;
							char *posout=oStr;
							EnumServicesStatusEx(
									GPC.m_SC_HANDLE, (SC_ENUM_TYPE)InfoLevel, ServiceType, ServiceState,
									baArray, cbBytesNeeded+1000, &cbBytesNeeded, &ServicesReturned, &ResumeHandle,
									(csTmps=="")?NULL:((csTmps==" ")?"":(LPCSTR)csTmps)
									);

							for(i=0;i<ServicesReturned;i++)
							{
								ENUM_SERVICE_STATUS_PROCESS *enu=((ENUM_SERVICE_STATUS_PROCESS *)baArray)+i;
								if (i) *(posout++)='\x7F';
								posout+=sprintf(posout,"%s\x1%s",enu->lpServiceName,enu->lpDisplayName);

								posout=DwordToStringMask(0x1,enu->ServiceStatusProcess.dwServiceType,posout,adwSSPServiceType,acSSPServiceType);
								posout=DwordToStringValue(0x1,enu->ServiceStatusProcess.dwCurrentState,posout,adwSSPCurrentState,acSSPCurrentState);
								posout=DwordToStringValue(0x1,enu->ServiceStatusProcess.dwControlsAccepted,posout,adwSSPControlsAccepted,acSSPControlsAccepted);

								posout+=sprintf(posout,"\x1%d\x1%d\x1%d\x1%d\x1%d\x1",
								enu->ServiceStatusProcess.dwWin32ExitCode,
								enu->ServiceStatusProcess.dwServiceSpecificExitCode,
								enu->ServiceStatusProcess.dwCheckPoint,
								enu->ServiceStatusProcess.dwWaitHint,
								enu->ServiceStatusProcess.dwProcessId
								);

								posout=DwordToStringValue(0x1,enu->ServiceStatusProcess.dwServiceFlags,posout,adwSSPServiceFlags,acSSPServiceFlags);
								while(*posout) posout++;
								*(posout++)=0x1;
								*posout=0;

								SC_HANDLE tmpHandle= OpenService( GPC.m_SC_HANDLE, enu->lpServiceName,SERVICE_QUERY_CONFIG);
								if (tmpHandle)
								{
									DWORD cbBytesNeeded2=0;
									LPQUERY_SERVICE_CONFIG lpqscBuf=(LPQUERY_SERVICE_CONFIG)baTmpArray; 
									int ii;
 									if (QueryServiceConfig(tmpHandle, lpqscBuf, 4096, &cbBytesNeeded2)) 
									{
										posout+=sprintf(posout,"%d\x1%d\x1%s\x1%s\x1%s\x1%d\x1",
										lpqscBuf->dwStartType,
										lpqscBuf->dwErrorControl,
										(lpqscBuf->lpBinaryPathName)?lpqscBuf->lpBinaryPathName:"",
										(lpqscBuf->lpLoadOrderGroup)?lpqscBuf->lpLoadOrderGroup:"",
										(lpqscBuf->lpServiceStartName)?lpqscBuf->lpServiceStartName:"",
										lpqscBuf->dwTagId
										);

										char *tmppos=lpqscBuf->lpDependencies;
										while(tmppos && *tmppos)
										{
											strcpy(posout,tmppos);
											while(*posout) posout++;
											while(*(tmppos++));
											if (*tmppos) *(posout++)=0x2;
											*posout=0;
										}
									}
									else posout+=sprintf(posout,"\x1\x1\x1\x1\x1\x1");


									for(ii=1;ii<8;ii++)
									{
				#ifdef W_NT
				#else
										if ( QueryServiceConfig2(tmpHandle, ii, baTmpArray, 4096, &cbBytesNeeded2)) 
										{
											switch(ii)
											{
											case SERVICE_CONFIG_DESCRIPTION:
												{
													LPSERVICE_DESCRIPTION pStruct=(LPSERVICE_DESCRIPTION)baTmpArray;
													strcpy(posout,(pStruct->lpDescription)?pStruct->lpDescription:"");
												}
												break;
											case SERVICE_CONFIG_FAILURE_ACTIONS:
												{
													LPSERVICE_FAILURE_ACTIONS pStruct=(LPSERVICE_FAILURE_ACTIONS)baTmpArray;
													posout+=sprintf(posout,"%d\x1%s\x1%s\x1",
														pStruct->dwResetPeriod,
														(pStruct->lpRebootMsg)?pStruct->lpRebootMsg:"",
														(pStruct->lpCommand )?(*(pStruct->lpCommand ))?pStruct->lpCommand :"deleted command":"same command"
													);
													DWORD j;
													for(j=0;j<pStruct->cActions;j++)
													{
														if (j) {*(posout++)=0x2;*posout=0;}
														posout+=sprintf(posout,"%d\x3%d",pStruct->lpsaActions[j].Type,pStruct->lpsaActions[j].Delay);
													}
												}
												break;

											case SERVICE_CONFIG_DELAYED_AUTO_START_INFO:
												{
													LPSERVICE_DELAYED_AUTO_START_INFO pStruct=(LPSERVICE_DELAYED_AUTO_START_INFO)baTmpArray;
													posout+=sprintf(posout,"%d",pStruct->fDelayedAutostart); 
												}
												break;
											case SERVICE_CONFIG_FAILURE_ACTIONS_FLAG:
												{
													LPSERVICE_FAILURE_ACTIONS_FLAG pStruct=(LPSERVICE_FAILURE_ACTIONS_FLAG)baTmpArray;
													posout+=sprintf(posout,"%d",pStruct->fFailureActionsOnNonCrashFailures); 
												}
												break;
											case SERVICE_CONFIG_PRESHUTDOWN_INFO:
												{
													LPSERVICE_PRESHUTDOWN_INFO pStruct=(LPSERVICE_PRESHUTDOWN_INFO)baTmpArray;
													posout+=sprintf(posout,"%d",pStruct->dwPreshutdownTimeout); 
												}
												break;
											case SERVICE_CONFIG_REQUIRED_PRIVILEGES_INFO:
												{
													LPSERVICE_REQUIRED_PRIVILEGES_INFO pStruct=(LPSERVICE_REQUIRED_PRIVILEGES_INFO)baTmpArray;
													char *tmppos=pStruct->pmszRequiredPrivileges;
													while(tmppos && *tmppos)
													{
														strcpy(posout,tmppos);
														while(*posout) posout++;
														while(*(tmppos++));
														if (*tmppos) *(posout++)=0x2;
														*posout=0;
													}
												}
												break;
											case SERVICE_CONFIG_SERVICE_SID_INFO:
												{
													LPSERVICE_SID_INFO pStruct=(LPSERVICE_SID_INFO)baTmpArray;
													posout+=sprintf(posout,"%d",pStruct->dwServiceSidType); 
												}
												break;
											}
										}
										else 
				#endif
											
											if (ii==SERVICE_CONFIG_FAILURE_ACTIONS) posout+=sprintf(posout,"\x1\x1\x1");

										while(*posout) posout++;
										*(posout++)=0x1;
										*posout=0;
									}

									CloseServiceHandle(tmpHandle);
								}
								else posout+=sprintf(posout,"\x1\x1\x1\x1\x1\x1\x1\x1\x1\x1\x1\x1\x1\x1\x1\x1\x1");
							}
							delete [] baTmpArray;
							delete [] baArray;
						}
					}
				}
				break;
			#endif
		#endif
		case 78: /*OpenSCManager [MachineName],[DatabaseName],DesiredAccess*/
			{
				if (GPC.m_SC_HANDLE) DoMethod("CloseSCManager",NULL);
				DWORD dwFlags=0;
				dwFlags=StringToDword(ExtractField(pos,3,","),acSCMDesiredAccess,adwSCMDesiredAccess);

				if (!dwFlags) dwFlags=GENERIC_READ;

				CString csMachine=ExtractField(pos,1,",");
				CString csDatabase=ExtractField(pos,2,",");
				GPC.m_SC_HANDLE=OpenSCManager((csMachine=="")?NULL:(LPCSTR)csMachine,(csDatabase=="")?NULL:(LPCSTR)csDatabase,dwFlags);
				retint=0;
				if (!GPC.m_SC_HANDLE) retint=GetLastError();
			}
			break;
		case 79: /*CloseSCManager*/
			{
				if (GPC.m_SC_HANDLE) CloseServiceHandle(GPC.m_SC_HANDLE);
				GPC.m_SC_HANDLE=NULL;
			}
			break;
		case 80: /*SetScript ScriptName,Script*/
		case 84: /*SetVariable VariableName,Value*/
			{
				CString *varSpr= (CString *)GPC.SprVariables.FindItemExact(0,ExtractField(pos,1,","));
				const char *scrPos=strchr(pos,',');
				if (!(scrPos++)) scrPos="";
				if (!*scrPos)
				{
					if (varSpr) GPC.SprVariables.DeleteItem(GPC.SprVariables.uPosition);
				}
				else
				{
					if (!varSpr)
					{
						GPC.SprVariables.InsertEmpty(0,1);
						GPC.SprVariables.SetItem(0,ExtractField(pos,1,","));
						GPC.SprVariables.SetSubItem(0,1,scrPos);
					}
					else varSpr[1]=scrPos;
				}
			}
			break;
		case 81: /*DeleteScript ScriptName[,ScriptName2[,..]]*/
		case 83: /*DeleteVariable VarName[,VarName2[,..]]*/
			{
				int i=0;
				CString tmpName;
				CString *varSpr;
				while((tmpName=ExtractField(pos,++i,","))!="")
					if ((varSpr=(CString *)GPC.SprVariables.FindItemExact(0,tmpName)))
						GPC.SprVariables.DeleteItem(GPC.SprVariables.uPosition);
			}
			break;
		case 82: /*DoScript [DefScrDlg],[DefObject],ScriptBody*/
			{
				const char *scriptpos=FindField(pos,3,",");
				if (scriptpos && *scriptpos)
				{
					CString tmpRes;
					DWORD dwDefObjId=0;
					CString csScrDlg=ExtractField(pos,1,",");
					CString csObject=ExtractField(pos,2,",");
					UINT tmpDlgId=0;
					UINT tmpObjId=0;
					BOOL ScrFlag=FALSE;

					if  (csScrDlg!="" && csScrDlg[0]=='S' && (csScrDlg.GetLength()<2 || (csScrDlg[1]>='0' && csScrDlg[1]<='9'))) 
					{
						ScrFlag=TRUE;
						csScrDlg=csScrDlg.Mid(1,100);
					}

					if (csScrDlg!="" && ((csScrDlg[0]>='0' && csScrDlg[0]<='9') || csScrDlg[0]>='-')) tmpDlgId=atoi(csScrDlg);
					else
						if ((tmpDlgId= GPC.m_Document->FindDlg(csScrDlg))<MAX_OBJDLG)
						{
							GPUNITINFO Ui;
							tmpObjId=GPC.m_Document->FindObject(tmpDlgId, csObject, Ui);
						}
						else tmpDlgId=0;

					dwDefObjId=tmpDlgId*0x10000+tmpObjId;
					if (ScrFlag) dwDefObjId|=IS_DLG_UNIT;

					GPC.m_Document->DoAnyMethodScript(scriptpos,dwDefObjId,tmpRes);
					if (oStr) strcpy(oStr,tmpRes);
				}
			}
			break;
		case 85: /*GetWSTime*/
			if (oStr)
			{
				CTime WSTime=CTime::GetCurrentTime();
				sprintf(oStr,"%I64d\x7F%2.2d\x7F%2.2d\x7F%2.2d\x7F%2.2d\x7F%2.2d\x7F%2.2d",
					WSTime.GetTime(), WSTime.GetSecond(), WSTime.GetMinute(), WSTime.GetHour(), WSTime.GetDay(), WSTime.GetMonth(),WSTime.GetYear());
			}
			break;

		case 86: /*AddPrinter [SrvName], PRINTER_INFO_2*/
			{
				PRINTER_INFO_2 pi={0};
				int i;
				if (1) i++;
			}
			break;
		case 87: /*ExecScript ScriptName[,DefDlg[,DefObject]]*/
			{
				CString *varSpr= (CString *)GPC.SprVariables.FindItemExact(0,ExtractField(pos,1,","));
				if (varSpr)
				{
					CString tmpRes;
					DWORD dwDefObjId=0;
					CString csScrDlg=ExtractField(pos,2,",");
					CString csObject=ExtractField(pos,3,",");
					UINT tmpDlgId=0;
					UINT tmpObjId=0;
					BOOL ScrFlag=FALSE;

					if  (csScrDlg[0]=='S' && csScrDlg[1]>='0' && csScrDlg[1]<='9') 
					{
						ScrFlag=TRUE;
						csScrDlg=csScrDlg.Mid(1,100);
					}

					if ((csScrDlg[0]>='0' && csScrDlg[0]<='9') || csScrDlg[0]>='-') tmpDlgId=atoi(csScrDlg);
					else
						if ((tmpDlgId= GPC.m_Document->FindDlg(csScrDlg))<MAX_OBJDLG)
						{
							GPUNITINFO Ui;
							tmpObjId=GPC.m_Document->FindObject(tmpDlgId, csObject, Ui);
						}
						else tmpDlgId=0;

					dwDefObjId=tmpDlgId*0x10000+tmpObjId;
					if (ScrFlag) dwDefObjId|=IS_DLG_UNIT;

					GPC.m_Document->DoAnyMethodScript(varSpr[1],dwDefObjId,tmpRes);
					if (oStr) strcpy(oStr,tmpRes);
				}
			}
			break;
		case 88: /*EncodeFilePCSRV SrcFileName,DstFileName*/
		case 89: /*EncodeFileSRVPC SrcFileName,DstFileName*/
			{
				CString csSrcFile=ExtractField(pos,1,",");
				FILE *src=fopen(csSrcFile,"rb");
				if (src)
				{
					CString csDstFile=ExtractField(pos,2,",");
					FILE *dst=fopen(csDstFile,"wb");
					if (dst)
					{
						int c;
						BYTE bArr[2]={0,0};
						if (nfunc==88)
						{
							while((c=fgetc(src))!=EOF)
							{
								*bArr=c;
								AnsiToDos(bArr,0,1);
								fputc(*bArr,dst);
							}
						}
						else
						{
							while((c=fgetc(src))!=EOF)
							{
								*bArr=c;
								DosToAnsi(bArr,1);
								fputc(*bArr,dst);
							}
						}
						fclose(dst);
					}
					fclose(src);
				}
			}
			break;
		case 90: /*GetODCList*/
			if (oStr)
				strcpy(oStr,GPC.m_View->m_ODContextsArray->EnumContextrs(0));
			break;
		case 91: /*CreateODContext ODCName*/
			retint=(int)GPC.m_View->m_ODContextsArray->CreateContext(pos);
			break;
		case 92: /*DeleteODContext ODCName*/
			retint=(int)GPC.m_View->m_ODContextsArray->DeleteContext(pos);
			break;
		case 93: /*LoadODContext ODCName,FileName*/
			retint=(int)GPC.m_View->m_ODContextsArray->LoadContext(ExtractField(pos,1,","),ExtractField(pos,2,","));
			break;
		case 94: /*DoODCMethod ODCName,MethodName[ Parameters]*/
			if (GPC.m_View->m_ODContextsArray) retint=GPC.m_View->m_ODContextsArray->DoContextMethod(pos,oStr);
			break;
		case 95: /*CapturingPageSetup Parameters*/
		case 96: /*SlavePrintPageSetup Parameters*/
		case 97: /*NotepadSetup Parameters*/
			{
				const char *ccSectionName=(nfunc==95)?"NotepadCaptureDumpSet":(nfunc==96)?"SlavePrintPageSetup":"";
				CString csOldNotepadSet;
				CString csArr[50];
				if (*ccSectionName) CDlgNotepadSet::GetNotepadTypeSettings(ccSectionName,csOldNotepadSet);
				else
					CDlgNotepadSet::GetNotepadSettings(csOldNotepadSet);

				CString csSrc=pos;
				csSrc.Replace(";;","\x3");
				csSrc.Replace(";","\x1");
				csSrc.Replace("\x3",";");

				int i,j;
				for(i=0;*CDlgNotepadSet::cArrEntryName[i];i++)
					csArr[i]=ExtractField(csOldNotepadSet,i+1,"\x7F");

				CString csField;
				CString csCmp;
					
				for(j=1;(csField=ExtractField(csSrc,j,"\x1"))!="";j++)
					if ((csCmp=ExtractField(csField,1,"="))!="")
					{
						for(i=0;*CDlgNotepadSet::cArrEntryName[i] && _stricmp(csCmp,CDlgNotepadSet::cArrEntryName[i]);i++);
						if (*CDlgNotepadSet::cArrEntryName[i])
							csArr[i]=FindField(csField,2,"=");
					}

				CString csNewNotepadSet="";
				if (oStr) *oStr=0;
				char *tmpoStr=oStr;

				for(i=0;*CDlgNotepadSet::cArrEntryName[i];i++)
				{
					if (oStr && csArr[i]!="")
					{
						csCmp=csArr[i];
						csCmp.Replace(";",";;");
						tmpoStr+=sprintf(tmpoStr,"%s=%s;",CDlgNotepadSet::cArrEntryName[i],csArr[i]);
					}
					if (i)	csNewNotepadSet+="\x7F"+csArr[i];
					else csNewNotepadSet=csArr[0];
				}

				if (csOldNotepadSet!=csNewNotepadSet)	
				{
					if (*ccSectionName) CDlgNotepadSet::SetNotepadTypeSettings(ccSectionName,csNewNotepadSet);
					else CDlgNotepadSet::SetNotepadSettings(csNewNotepadSet);
				}

			}
			break;
		case 98: //ShellExecuteEx [VERB=][;FILE=][;CLASSNANE=][;CLASSKEY=][;DIR=][;SHOW=][;HOTKEY=][;FLAG=][;PARAM=][;IDSCR=][;IDDLG=][;NELAPSE=]
		case 99: //ProcMonitorStart [IDPROC=][;IDSCR=][;IDDLG=][;NELAPSE=]
		case 100: //ProcMonitorModify [IDPROC=][;IDSCR=][;IDDLG=][;NELAPSE=][;STATE=]
		case 101: //ProcMonitorSetState IDPROC=[;IDSCR=][;IDDLG=][;STATE=]
			{
				char *srcpos=new char [strlen(pos)+100];
				strcpy(srcpos,pos);
				SHELLEXECUTEINFO ShExecInfo={0};
				GPPROCMONITOR procMon={0};
				procMon.dwDlgId=-1;
				procMon.dwScrId=-1;
				procMon.dwElapse=-1;
				procMon.dwProcID=-1;
				ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
				ShExecInfo.lpParameters = NULL;
				int i,j;

				char *com[]={
					"VERB=","FILE=","CLASSNANE=","CLASSKEY=","DIR=",
					"SHOW=","HOTKEY=","FLAG=","PARAM=",
					"IDPROC=","IDSCR=","IDDLG=","NELAPSE=","FIELDS=",
					"SUBNAME=","STATE=",
					"",
				};
				char *poss[40],*tmppos;

				for(i=0;*com[i];i++)
					poss[i]=strstr(srcpos,com[i]);

				for(i=0;*com[i];i++)
					if (poss[i]!=NULL)
					{
						poss[i]+=(int)strlen(com[i]);
						if ((tmppos=strchr(poss[i],';'))!=NULL) *tmppos=0;
					}

				for(i=0;*com[i];i++)
					if (poss[i]!=NULL)
					switch(i)
					{
					case 0:/*VERB*/		ShExecInfo.lpVerb=poss[i];		break;
					case 1:/*FILE*/		ShExecInfo.lpFile=poss[i];		break;
					case 2:/*CLASSNANE*/
						ShExecInfo.lpClass=poss[i];
						ShExecInfo.fMask|=SEE_MASK_CLASSNAME;
						break;
					case 3:/*CLASSKEY*/
						break;
					case 4:/*DIR*/		ShExecInfo.lpDirectory=poss[i];	break;
					case 5:/*SHOW*/
						for(j=0;j<N_WND_SHOW_STYLES;j++)
							if (_stricmp(aWndShowStyleName[j],poss[i])==0)
							{
								ShExecInfo.nShow=aWndShowStyleUINT[j];
								break;
							}
						break;
					case 6:/*HOTKEY*/
						{
							UINT VirtualKey=0,ModifierFlag=0;
							m_LastScanf=sscanf(poss[i],"%d,%d",&VirtualKey,&ModifierFlag);
							ShExecInfo.dwHotKey=VirtualKey+ModifierFlag*0x10000;
							ShExecInfo.fMask|=SEE_MASK_HOTKEY;
						}
						break;
					case 7:/*FLAG*/
						{
							char *nmflg[]={
								"_CONNECTNETDRV","_DOENVSUBST","_FLAG_DDEWAIT","_FLAG_NO_UI",
								"_NOCLOSEPROCESS","_NO_CONSOLE","_UNICODE","_ICON",
								"_NOZONECHECKS","_ASYNCOK","_HMONITOR","_NOQUERYCLASSSTORE",
								"_WAITFORINPUTIDLE","_FLAG_LOG_USAGE","_IDLIST","_INVOKEIDLIST",
								"_NOASYNC","_CLASSKEY",
								"",
							};
							UINT  uiflg[]={
								SEE_MASK_CONNECTNETDRV,SEE_MASK_DOENVSUBST,SEE_MASK_FLAG_DDEWAIT,SEE_MASK_FLAG_NO_UI,
								SEE_MASK_NOCLOSEPROCESS,SEE_MASK_NO_CONSOLE,SEE_MASK_UNICODE,0x00000010/*SEE_MASK_ICON*/,
								SEE_MASK_NOZONECHECKS,SEE_MASK_ASYNCOK,SEE_MASK_HMONITOR,SEE_MASK_NOQUERYCLASSSTORE,
								SEE_MASK_WAITFORINPUTIDLE,SEE_MASK_FLAG_LOG_USAGE,SEE_MASK_IDLIST,SEE_MASK_INVOKEIDLIST,
								SEE_MASK_NOASYNC,SEE_MASK_CLASSKEY,
								0,
							};

							for(j=0;*nmflg[j];j++)
								if (strstr(poss[i],nmflg[j])!=NULL)
									ShExecInfo.fMask|=uiflg[j];
						}
						break;
					case 8:/*PARAM*/		ShExecInfo.lpParameters=poss[i];		break;
					case 9:/*IDPROC*/		procMon.dwProcID=atoi(poss[i]);			break;
					case 10:/*IDSCR*/		procMon.dwScrId=atoi(poss[i]);			break;
					case 11:/*IDDLG*/		procMon.dwDlgId=atoi(poss[i]);			break;
					case 12:/*NELAPSE*/		
						procMon.dwElapse=atoi(poss[i]);
						if (procMon.dwElapse<100) procMon.dwElapse=1000;
						break;
					case 13:/*FIELDS*/		procMon.dwFields=atoi(poss[i]);			break;
					case 14:/*SUBNAME*/		strncpy(procMon.subName,poss[i],sizeof(procMon.subName)-2);
					case 15:/*STATE*/		procMon.dwState=atoi(poss[i]);			break;
						break;
					}
				switch(nfunc)
				{
				case 98: //ShellExecuteEx [VERB=][;FILE=][;CLASSNANE=][;CLASSKEY=][;DIR=][;SHOW=][;HOTKEY=][;FLAG=][;PARAM=]
					ShExecInfo.hwnd = GPC.m_hViewWnd;
					ShExecInfo.hInstApp = NULL;
					procMon.dwProcID=retint=ShellExecuteEx(&ShExecInfo);
					if (!*procMon.subName) break;
				case 99: //ProcMonitorStart [IDPROC=][;IDSCR=][;IDDLG=][;NELAPSE=]
					if (GPC.m_View->m_pProcMonitor) GPC.m_View->m_pProcMonitor->StartMonitor(procMon);
					break;
				case 100: //ProcMonitorModify [IDPROC=][;IDSCR=][;IDDLG=][;NELAPSE=][;STATE=]
					if (GPC.m_View->m_pProcMonitor) GPC.m_View->m_pProcMonitor->ModifyMonitor(procMon);
					break;
				case 101: //ProcMonitorSetState IDPROC=[;IDSCR=][;IDDLG=][;STATE=]
					if (GPC.m_View->m_pProcMonitor)
						GPC.m_View->m_pProcMonitor->SetState(procMon.dwProcID,procMon.dwDlgId,procMon.dwScrId,procMon.dwState);
					break;
				}
				delete []srcpos;
			}
			break;
		case 102: //GetTerminalVersion
			if (oStr) strcpy(oStr,m_TermVersion);
			break;
		case 103: //GetCurrentProcessId
			retint=GetCurrentProcessId();
			break;
		case 104: //ProcGetList [Context]
			if (oStr) CProcMonitor::GetProcList(oStr, 50000, pos);
			break;
		case 105: //ProcGetListModules IdProc,[Context]
			if (oStr)
				CProcMonitor::GetProcModulesList(atoi(pos),oStr, 50000);
			break;
		case 106: //ProcGetInfo IdProc
			if (oStr) CProcMonitor::GetProcessDescription(atoi(pos),oStr);
			break;
	#ifdef W_95
	#else
		#ifdef W_98
		#else
			#ifdef W_NT
			#else
			case 107: //AllowSetForegroundWindow IdProc
				retint=AllowSetForegroundWindow(atoi(pos));
				break;
			case 108: //LockSetForegroundWindow LockCode
				retint=LockSetForegroundWindow(atoi(pos));
				break;
			#endif
		#endif
	#endif
		case 109: //ActivateKeyboardLayout KLH
			retint=(int)ActivateKeyboardLayout((HKL)atoipos,0);
			break;
		case 110: //GetKeyboardLayoutList 
			if (oStr)
			{
				char *pout=oStr;
				HKL tmpHKL[1000];
				int nRet=GetKeyboardLayoutList(999,tmpHKL);
				int i;
				for(i=0;i<nRet;i++)
				{
					if (i) {*(pout++)=0x7F;*pout=0;}
					pout+=sprintf(pout,"%8.8X",tmpHKL[i]);
				}
			}
			break;
		case 111: //LoadKeyboardLayout KLID, Flags
			{
				DWORD dwType[]={
						KLF_ACTIVATE,KLF_SUBSTITUTE_OK,KLF_REORDER,KLF_REPLACELANG,KLF_NOTELLSHELL,
						KLF_SETFORPROCESS,KLF_SHIFTLOCK,KLF_RESET,KLF_ACTIVATE,
					};
				const char *ccType[]={
						"ACTIVATE","SUBSTITUTE_OK","REORDER","REPLACELANG","NOTELLSHELL",
						"SETFORPROCESS","SHIFTLOCK","RESET","",
					};
				CString tmpCS=pos;
				tmpCS.MakeUpper();
				int i;
				for(i=0;*ccType[i] && tmpCS.Find(ccType[i])<0;i++);
				retint=(int)LoadKeyboardLayout(ExtractField(pos,1,","),dwType[i]);
			}
			break;
		case 112: //UnloadKeyboardLayout KLH
			retint=UnloadKeyboardLayout((HKL)atoipos);
			break;
		case 113: //GetKeyboardLayoutName
			if (oStr) retint=GetKeyboardLayoutName(oStr);
			break;
		case 114: //GetKeyboardLayout [IdThread]
			if (oStr) sprintf(oStr,"%8.8X",GetKeyboardLayout(atoipos));
			break;
		case 115: //SetTerminalRect [X],[y],[CX],[CY]
			{
				RECT re;
				CString tmpCS;
				AfxGetMainWnd()->GetWindowRect(&re);
				tmpCS=ExtractField(pos,1,",");
				if (tmpCS!="") re.left=atoi(tmpCS);
				tmpCS=ExtractField(pos,2,",");
				if (tmpCS!="") re.top=atoi(tmpCS);
				tmpCS=ExtractField(pos,3,",");
				if (tmpCS!="") re.right=re.left+atoi(tmpCS)-1;
				tmpCS=ExtractField(pos,4,",");
				if (tmpCS!="") re.bottom=re.top+atoi(tmpCS)-1;
				AfxGetMainWnd()->MoveWindow(&re);
			}
		case 116: //GetTerminalRect
			if (oStr)
			{
				RECT re;
				AfxGetMainWnd()->GetWindowRect(&re);
				sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right-re.left+1,re.bottom-re.top+1);
			}
			break;
		case 117: //GetMethods
			if (oStr)
			{
				*oStr=0;
				int i;
				char *posout=oStr;
				for(i=0;*CDlgViewSystemMethods::cArrMethods[i];i++)
				{
					if (i) *(posout++)=0x7F;
					posout+=sprintf(posout,"%s\x7%s",CDlgViewSystemMethods::cArrMethods[i],CDlgViewSystemMethods::cArrMethodsParams[i]);
				}
			}
			break;
		case 118: //CapturePreview
			GPC.m_View->OnDumpcapturepreview();
			break;
		case 119: //CapturePreviewSetupDialog
			GPC.m_View->OnDumpcapturepreviewsetup();
			break;


/*
PMIB_TCPTABLE pTcpTable;
DWORD dwRetVal;
pTcpTable = (MIB_TCPTABLE*) malloc(sizeof(MIB_TCPTABLE));
DWORD dwSize1 = 0;

// Make an initial call to GetTcpTable to
// get the necessary size into the dwSize1 variable
if (GetTcpTable(pTcpTable, &dwSize1, TRUE) == ERROR_INSUFFICIENT_BUFFER) {
  GlobalFree(pTcpTable);
  pTcpTable = (MIB_TCPTABLE*) malloc ((UINT) dwSize1);
}

// Make a second call to GetTcpTable to get
// the actual data we require
if ((dwRetVal = GetTcpTable(pTcpTable, &dwSize1, TRUE)) == NO_ERROR) {
  for (int i = 0; i < (int) pTcpTable->dwNumEntries; i++) {
    TRACE("State: %ld\n", pTcpTable->table[i].dwState);
  }
}

else {
  printf("\tCall to GetTcpTable failed.\n");
		
  LPVOID lpMsgBuf;
		
  if (FormatMessage( 
    FORMAT_MESSAGE_ALLOCATE_BUFFER | 
    FORMAT_MESSAGE_FROM_SYSTEM | 
    FORMAT_MESSAGE_IGNORE_INSERTS,
    NULL,
    dwRetVal,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
    (LPTSTR) &lpMsgBuf,
    0,
    NULL ))
  {
    printf("\tError: %s", lpMsgBuf);
  }
  LocalFree( lpMsgBuf );
}


*/

		default: 
			GPC.m_ErrReport.GPWriteWarnLog2("CDlgViewSystemMethods", "Unknown Method",iStr);
			if (oStr)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;
			break;
		}
	}catch(...)
	{
		char *str=new char [200+(int)strlen(pos)];
		#ifdef RUS
			sprintf(str,"Ошибка выполнения метода %s %s",met,pos);
			AfxGetMainWnd()->MessageBox(str,"Ошибка метода");
		#else
			sprintf(str,"Error execution of method %s %s",met,pos);
			AfxGetMainWnd()->MessageBox(str,"Error execution");
		#endif
		if (oStr) strcpy(oStr,str);
		nfunc=0xFFFFFFFFL;
		GPC.m_ErrReport.GPWriteErrorLog("CDlgViewSystemMethods", "DoMethod",iStr);
		delete[] str;
	}

	if (oStr && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
	return nfunc;
}

DWORD CDlgViewSystemMethods::StringFromToAddrTypes(const char *iOption, unsigned short & convOption)
{
	UINT nOptions=5;
	const char *OptionName[]={
	"PRIMARY","DYNAMIC","DISCONNECTED","DELETED","TRANSIENT",
	};
	const DWORD  uOptionList[]={
	MIB_IPADDR_PRIMARY,MIB_IPADDR_DYNAMIC,MIB_IPADDR_DISCONNECTED,MIB_IPADDR_DELETED,MIB_IPADDR_TRANSIENT,
	};

	if (iOption)
	{
		if (*iOption)
		{
			char *tmps=new char [(int)strlen(iOption)+100];
			strcpy(tmps,iOption);
			_strupr(tmps);
			convOption=atoi(tmps);
			UINT i;
			for(i=0;i<nOptions;i++)
				if (strstr(tmps,OptionName[i]))
					convOption|=uOptionList[i];
			delete[] tmps;
		}
		else
		{
			UINT convSD=convOption;
			UINT i;
			for(i=0;i<nOptions;i++)
				if ((convSD&uOptionList[i])==uOptionList[i])
				{
					if (*iOption) strcat((char *)iOption,"|");
					strcat((char *)iOption,OptionName[i]);
					convSD^=uOptionList[i];
				}
				if (convSD) sprintf((char *)iOption+(int)strlen(iOption),"%s%d",*iOption?"|":"",convSD);
		}
	}
	return convOption;
}

DWORD CDlgViewSystemMethods::StringFromToProtocolId(const char *iOption, DWORD & convOption)
{
	UINT nOptions=31;
	const char *OptionName[]={
	"IP_OTHER","IP_LOCAL","IP_NETMGMT","IP_ICMP","IP_EGP",
	"IP_GGP","IP_HELLO","IP_RIP","IP_IS_IS","IP_ES_IS",
	"IP_CISCO","IP_BBN","IP_OSPF","IP_BGP","IP_BOOTP",
	"IP_NT_AUTOSTATIC","IP_NT_STATIC","IP_NT_STATIC_NON_DOD","IP_MSDP","IP_IGMP",
	"IP_BGMP","IP_VRRP","IP_DNS_PROXY","IP_DHCP_ALLOCATOR","IP_NAT",
	"IP_DIFFSERV","IP_MGM","IP_ALG","IP_H323","IP_FTP",
	"IP_DTP",
	};
	const DWORD  uOptionList[]={
	PROTO_IP_OTHER,PROTO_IP_LOCAL,PROTO_IP_NETMGMT,PROTO_IP_ICMP,PROTO_IP_EGP,
	PROTO_IP_GGP,PROTO_IP_HELLO,PROTO_IP_RIP,PROTO_IP_IS_IS,PROTO_IP_ES_IS,
	PROTO_IP_CISCO,PROTO_IP_BBN,PROTO_IP_OSPF,PROTO_IP_BGP,PROTO_IP_BOOTP,
	PROTO_IP_NT_AUTOSTATIC,PROTO_IP_NT_STATIC,PROTO_IP_NT_STATIC_NON_DOD,PROTO_IP_MSDP,PROTO_IP_IGMP,
	PROTO_IP_BGMP,PROTO_IP_VRRP,PROTO_IP_DNS_PROXY,PROTO_IP_DHCP_ALLOCATOR,PROTO_IP_NAT,
	PROTO_IP_DIFFSERV,PROTO_IP_MGM,PROTO_IP_ALG,PROTO_IP_H323,PROTO_IP_FTP,
	PROTO_IP_DTP,
	};

	if (iOption)
	{
		if (*iOption)
		{
			char *tmps=new char [(int)strlen(iOption)+100];
			strcpy(tmps,iOption);
			_strupr(tmps);
			convOption=atoi(tmps);
			UINT i;
			for(i=0;i<nOptions;i++)
				if (strcmp(tmps,OptionName[i]))
					convOption=uOptionList[i];
			delete[] tmps;
		}
		else
		{
			UINT convSD=convOption;
			UINT i;
			for(i=0;i<nOptions;i++)
				if (convSD==uOptionList[i])
				{
					strcpy((char *)iOption,OptionName[i]);
					convSD=0;
					break;
				}
				if (convSD) sprintf((char *)iOption,"%d",convSD);
		}
	}
	return convOption;
}

DWORD CDlgViewSystemMethods::StringToIPAddr(const char *iIPAddr)
{
	DWORD ret=0;
	DWORD a1=0,a2=0,a3=0,a4=0;
	if (iIPAddr) m_LastScanf=sscanf(iIPAddr,"%d.%d.%d.%d",&a1,&a2,&a3,&a4);
	ret=(a1&0xFF)+(a2&0xFF)*0x100+(a3&0xFF)*0x10000+(a4&0xFF)*0x1000000;
	return ret;
}

char *CDlgViewSystemMethods::IPAddrToString(DWORD iIPAddr)
{
	tmpRetStr[0]=0;
	sprintf(tmpRetStr,"%d.%d.%d.%d",(iIPAddr)&0xFF,(iIPAddr/0x100)&0xFF,(iIPAddr/0x10000)&0xFF,(iIPAddr/0x1000000)&0xFF);
	return tmpRetStr;
}

DWORD CDlgViewSystemMethods::StringFromToAddrFamily(const char *iOption, DWORD & convOption)
{
	UINT nOptions=33;
	const char *OptionName[]={
		"AF_UNIX","AF_INET","AF_IMPLINK","AF_PUP","AF_CHAOS",
		"AF_NS","AF_IPX","AF_ISO","AF_OSI","AF_ECMA",
		"AF_DATAKIT","AF_CCITT","AF_SNA","AF_DECnet","AF_DLI",
		"AF_LAT","AF_HYLINK","AF_APPLETALK","AF_NETBIOS","AF_VOICEVIEW",
		"AF_FIREFOX","AF_UNKNOWN1","AF_BAN","AF_ATM","AF_INET6",
		"AF_CLUSTER","AF_12844","AF_IRDA","AF_NETDES","AF_TCNPROCESS",
		"AF_TCNMESSAGE","AF_ICLFXBM","AF_UNSPEC",
	};
	const DWORD  uOptionList[]={
		AF_UNIX,AF_INET,AF_IMPLINK,AF_PUP,AF_CHAOS,
		AF_NS,AF_IPX,AF_ISO,AF_OSI,AF_ECMA,
		AF_DATAKIT,AF_CCITT,AF_SNA,AF_DECnet,AF_DLI,
		AF_LAT,AF_HYLINK,AF_APPLETALK,AF_NETBIOS,AF_VOICEVIEW,
		AF_FIREFOX,AF_UNKNOWN1,AF_BAN,AF_ATM,AF_INET6,
		AF_CLUSTER,AF_12844,AF_IRDA,AF_NETDES,AF_TCNPROCESS,
		AF_TCNMESSAGE,AF_ICLFXBM,AF_UNSPEC,
	};

	if (iOption)
	{
		if (*iOption)
		{
			char *tmps=new char [(int)strlen(iOption)+100];
			strcpy(tmps,iOption);
			_strupr(tmps);
			convOption=atoi(tmps);
			UINT i;
			for(i=0;i<nOptions;i++)
				if (strcmp(tmps,OptionName[i]))
					convOption=uOptionList[i];
			delete[] tmps;
		}
		else
		{
			UINT convSD=convOption;
			UINT i;
			for(i=0;i<nOptions;i++)
				if (convSD==uOptionList[i])
				{
					strcpy((char *)iOption,OptionName[i]);
					convSD=0;
					break;
				}
				if (convSD) sprintf((char *)iOption,"%d",convSD);
		}
	}
	return convOption;
}

DWORD CDlgViewSystemMethods::StringFromToAddrFlags(const char *iOption, DWORD & convOption)
{
	UINT nOptions=6;
	const char *OptionName[]={
	"SKIP_UNICAST","SKIP_ANYCAST","SKIP_MULTICAST","SKIP_DNS_SERVER","INCLUDE_PREFIX","SKIP_FRIENDLY_NAME",
	};
	const DWORD  uOptionList[]={
	GAA_FLAG_SKIP_UNICAST,GAA_FLAG_SKIP_ANYCAST,GAA_FLAG_SKIP_MULTICAST,GAA_FLAG_SKIP_DNS_SERVER,GAA_FLAG_INCLUDE_PREFIX,GAA_FLAG_SKIP_FRIENDLY_NAME,
	};


	if (iOption)
	{
		if (*iOption)
		{
			char *tmps=new char [(int)strlen(iOption)+100];
			strcpy(tmps,iOption);
			_strupr(tmps);
			convOption=atoi(tmps);
			UINT i;
			for(i=0;i<nOptions;i++)
				if (strstr(tmps,OptionName[i]))
					convOption|=uOptionList[i];
			delete[] tmps;
		}
		else
		{
			UINT convSD=convOption;
			UINT i;
			for(i=0;i<nOptions;i++)
				if ((convSD&uOptionList[i])==uOptionList[i])
				{
					if (*iOption) strcat((char *)iOption,"|");
					strcat((char *)iOption,OptionName[i]);
					convSD^=uOptionList[i];
				}
				if (convSD) sprintf((char *)iOption+(int)strlen(iOption),"%s%d",*iOption?"|":"",convSD);
		}
	}
	return convOption;
}

void CDlgViewSystemMethods::StringFromToPORT_INFO_3(const char *iStr, char *oStr, PORT_INFO_3 & iPORT_INFO_3)
{
	UINT nOptions=12;
	const char *OptionName[]={
	"","OFFLINE","PAPER_JAM","PAPER_OUT","OUTPUT_BIN_FULL",
	"PAPER_PROBLEM","NO_TONER","DOOR_OPEN","USER_INTERVENTION","OUT_OF_MEMORY",
	"TONER_LOW","WARMING_UP","POWER_SAVE","",
	};

	const char *SeverityName[]={
	"","TYPE_ERROR","TYPE_WARNING","TYPE_INFO",
	};

	static char szStatus[200];
	
	if (iStr)
	{
		char *delim=(strchr(iStr,'\x7F'))?"\x7F":",";
		CString csStatus=ExtractField(iStr,1,delim);
		iPORT_INFO_3.dwStatus=0;
		*szStatus=0;
		if (csStatus!="")
		{
			int j;
			for(j=1;j<=12 && csStatus!=OptionName[j];j++);
			if (j<=12) iPORT_INFO_3.dwStatus=j;
		}
		strncpy(szStatus,ExtractField(iStr,2,delim),199);
		szStatus[199]=0;
		iPORT_INFO_3.pszStatus=szStatus;
		csStatus=ExtractField(iStr,3,delim);
		iPORT_INFO_3.dwSeverity=0;
		if (csStatus!="")
		{
			int j;
			for(j=1;j<=3 && csStatus!=SeverityName[j];j++);
			if (j<=3) iPORT_INFO_3.dwSeverity=j;
		}
	}

	if (oStr)
	{
		sprintf(oStr,"%s\x7F%s\x7F%s",
			iPORT_INFO_3.dwStatus<=12?szStatus:"",
			iPORT_INFO_3.pszStatus?iPORT_INFO_3.pszStatus:"",
			iPORT_INFO_3.dwSeverity<=3?SeverityName[iPORT_INFO_3.dwSeverity]:""
			);
	}
}


