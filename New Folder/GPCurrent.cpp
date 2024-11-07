// GPCurrent.cpp: implementation of the GPCurrent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GP_term.h"
#include <stdio.h>
#include <io.h>
#include <direct.h>
#include "GPFrameWnd.h"
#include "GPFrameBar.h"
#include "DlgMethods.h"
#include "GPToolTipCtrl.h"
#include "GPContextMenu.h"
#include "UniSocket.h"
#include "DlgViewSystemMethods.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#include "ListMaker.h"

const DWORD GPCurrent::uArrPower[]={
	0x00000001,0x00000002,0x00000004,0x00000008,
	0x00000010,0x00000020,0x00000040,0x00000080,
	0x00000100,0x00000200,0x00000400,0x00000800,
	0x00001000,0x00002000,0x00004000,0x00008000,
	0x00010000,0x00020000,0x00040000,0x00080000,
	0x00100000,0x00200000,0x00400000,0x00800000,
	0x01000000,0x02000000,0x04000000,0x08000000,
	0x10000000,0x20000000,0x40000000,0x80000000,
};

const UINT GPCurrent::uNRegistryMethods=26;
const char *GPCurrent::cArrRegistryMethods[45]={
/*00*/	"RegCloseKey","RegConnectRegistry","RegCreateKeyEx","RegDeleteKey","RegDeleteValue",
/*05*/	"RegDisablePredefinedCache","RegEnumKeyEx","RegEnumValue","RegFlushKey","RegGetKeySecurity",
/*10*/	"RegLoadKey","RegNotifyChangeKeyValue","RegOpenCurrentUser","RegOpenKeyEx","RegOpenUserClassesRoot",
/*15*/	"RegOverridePredefKey","RegQueryInfoKey","RegQueryMultipleValues","RegQueryValueEx","RegReplaceKey",
/*20*/	"RegRestoreKey","RegSaveKey","RegSetKeySecurity","RegSetValueEx","RegUnLoadKey",
/*25*/	"RegSaveKeyEx","","","","",
/*30*/	"","","","","",
/*35*/	"","","","","",
/*40*/	"","","","","",
	};

const char *GPCurrent::cArrRegistryMethodsParams[45]={
/*00*/	"","PredefKey,MachineName","ParentKey,SubKeyName,Class,Options,samDesired,Disposition","SubKeyName","ValueName",
/*05*/	"","startId,EndId","startId,EndId","","",
/*10*/	"SubKey,File","bWatchSubtree,dwNotifyFilter,nTimes,NotifySub","samDesired","OpenKey,SubkeyName,samDesired","UserTokenHandle,samDesired",
/*15*/	"PredefKey","","SubKeyName1^SubKeyName2^...","ValueName","SubKeyName,NewFile,OldFile",
/*20*/	"File,dwFlags","FileName","","ValueName,Type,DelimiterCode,Data","SubKeyName",
/*25*/	"FileName,Flags","","","","",
/*30*/	"","","","","",
/*35*/	"","","","","",
/*40*/	"","","","","",
	};


#include "GP_TermView.h"

UINT RegistryNotifWaitThreadFn(LPVOID pParam)
{
	PGPNOTIFYTHREADSTRUCT pGPNS=(PGPNOTIFYTHREADSTRUCT)pParam;
	UINT ret=(UINT)-1;
	GPC.nNotifyThreads++;
	if (pGPNS)
	{
		AnsiToDos(pGPNS->csInfo,pGPNS->csInfo,1);
		AnsiToDos(pGPNS->csSubName,pGPNS->csSubName,1);

		while(pGPNS->m_StopWorking==FALSE && pGPNS->hEvent && pGPNS->nTimes)
		{
			DWORD res=WaitForSingleObject(pGPNS->hEvent, 200);
			if (res!=WAIT_TIMEOUT)
			{
				if (res==WAIT_OBJECT_0)
				{
					EnterCriticalSection(&GPC.m_View->m_CSRemap);
					try
					{
						CString ms;
						ms.Format("%c%c%d%c%s%c%s%c%s\r",
									250,
									250,
									56,0xFE,
									"REGEVENT",0xFE,
									(LPCSTR)pGPNS->csSubName,0xFE,
									(LPCSTR)pGPNS->csInfo
									);
						m_Comm.GPSendSafeBlock(ms,ms.GetLength());
					}catch(...)
					{
						GPC.m_ErrReport.GPWriteErrorLog("GLOBAL GPCurrent", "RegistryNotifWaitThreadFn 100","");
					}
					LeaveCriticalSection(&GPC.m_View->m_CSRemap);
					if (pGPNS->nTimes!=-1) pGPNS->nTimes--;
				}
				else
				{
					if (pGPNS->m_StopWorking==FALSE)
					{
						EnterCriticalSection(&GPC.m_View->m_CSRemap);
						try
						{
							CString ms;
							ms.Format("%c%c%d%c%s%c%s%c%s\r",
										250,
										250,
										56,0xFE,
										"REGEVENTERROR",0xFE,
										(LPCSTR)pGPNS->csSubName,0xFE,
										(LPCSTR)pGPNS->csInfo
										);
							m_Comm.GPSendSafeBlock(ms,ms.GetLength());
						}catch(...)
						{
							GPC.m_ErrReport.GPWriteErrorLog("GLOBAL GPCurrent", "RegistryNotifWaitThreadFn 124","");
						}
						LeaveCriticalSection(&GPC.m_View->m_CSRemap);
					}
					pGPNS->nTimes=0;
				}
			}
		}

		if (pGPNS->hEvent && (pGPNS->autoDelete&GPNTS_DELETE_EVENT))
			CloseHandle(pGPNS->hEvent);

		if ((pGPNS->autoDelete&GPNTS_DELETE_STRUCT))
			delete[] pGPNS;
	}

	if (GPC.nNotifyThreads>0) GPC.nNotifyThreads--;

	return ret;
}

#include "DlgCodeco.h"

void calc_table16(ULONG *t16);

BOOL CALLBACK MyEnumCodePagesProc(LPTSTR lpCodePageString)
{
	DWORD dwCPtoAdd=atoi(lpCodePageString);
	if (dwCPtoAdd)
	{
		DWORD nCP=0;
		while(nCP<GPC.dwnCP && dwCPtoAdd!=GPC.dwCodePages[nCP]) nCP++;
		if (nCP==GPC.dwnCP)
		{
			if ((GPC.dwnCP%500)==0 && GPC.dwnCP)
			{
				DWORD *tmp=new DWORD [GPC.dwnCP+505];
				for(nCP=0;nCP<GPC.dwnCP;nCP++) tmp[nCP]=GPC.dwCodePages[nCP];
				delete[] GPC.dwCodePages;
				GPC.dwCodePages=tmp;
			}
			GPC.dwCodePages[GPC.dwnCP++]=dwCPtoAdd;
		}
	}
	return TRUE;
}

GPCurrent::GPCurrent()
{
	m_uPixelPerPoint=4;
	m_CompositingQuality=CompositingQualityDefault;
	m_InterpolationMode=InterpolationModeDefault;
	m_PixelOffsetMode=PixelOffsetModeDefault;
	m_SmoothingMode=SmoothingModeDefault;
	m_TextContrast=0;
	m_TextRenderingHint=TextRenderingHintSystemDefault;
	m_Language=LANG_NEUTRAL;
	m_SubLanguage=SUBLANG_NEUTRAL;
	#ifdef RUS
		GPC.csLocaleStr=".1251";
		m_CurCodePage=1251;
	#else
		GPC.csLocaleStr="";
		m_CurCodePage=1252;
	#endif

	csODCTerminalMenuName="TerminalMenu";
	m_SC_HANDLE=NULL;
	m_dwAltFlag=0;
	dw_LoginDialogFlags_temporary=0;
	dw_StartFlags=0;
	cs_RegTermViewSetName="TERMVIEWSET";
	dw_ScriptWaitFlag=0;
	chWideDosAnsi3=NULL;
	chWideAnsiDos3=NULL;
	ZeroMemory(&m_CONV3PCSRV, sizeof(GPCONV3));
	ZeroMemory(&m_CONV3SRVPC, sizeof(GPCONV3));

	m_USEMBCONV3=0;

	dwGraphDecodeArray=new DWORD [256];
	LoadGraphCodeco();

	dwnCP=0;
	dwCodePages= new DWORD [1505];
	EnumSystemCodePages(MyEnumCodePagesProc,CP_INSTALLED/*CP_SUPPORTED*/);
	if (dwnCP) qs(dwCodePages,0,dwnCP-1);
	dwGraphFlag=0;
	LOGFONT m_tmpLogfont;
	GetObject(GetStockObject(SYSTEM_FONT), sizeof (m_tmpLogfont), &m_tmpLogfont);

	m_GUISet.FontName=m_tmpLogfont.lfFaceName;
	m_GUISet.CharSet=m_tmpLogfont.lfCharSet;
	m_GUISet.Scale=100;
	m_GUISet.Weight=400;
	m_GUISet.Italic=0;
	m_GUISet.PointSize=8;
	m_GUISet.UseDefault=1;

	m_WideOn2Pos=1;
	m_USEMBCONV=1;
	m_USEMBCONV2=1;
	dwMBReposition=0;

	calc_table16(tcrc16);
	SprVariables.Create("RuntimeVariables",2);

	setlocale( LC_ALL, GPC.csLocaleStr );
	setlocale( LC_NUMERIC, "English_USA.1252");
	m_CurMBInvert=0;
	m_curOutScrBkg=8;

	DelimiterIn1='^';
	DelimiterIn2=']';
	DelimiterIn3='\\';
	DelimiterIn4=4;
	DelimiterIn5=5;
	DelimiterIn6=6;
	DelimiterSrc1='^';
	DelimiterSrc2=']';
	DelimiterSrc3='\\';
	DelimiterSrc4=4;
	DelimiterSrc5=5;
	DelimiterSrc6=6;
	csDelimiterIn1="^";
	csDelimiterIn2="]";
	csDelimiterIn3="\\";
	csDelimiterIn4="\x4";
	csDelimiterIn5="\x5";
	csDelimiterIn6="\x6";
	GDIPtoken=NULL;
	GdiplusStartupInput gdisu;
	GdiplusStartup(&GDIPtoken,&gdisu,NULL);

	EnableSlavePrint=1;
	EnableSlavePrintCHARVIEW=1;

	DlgStatistics=new CDlgStatistics;
	strcpy(contmenuFileName,"CONTMENU.TXT");
	BreakChar=127;
	m_SystemType=0;
	nNotifyThreads=0;
	m_BarVisibleFlag=3;
	m_pContextMenu=NULL;

	OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
	GetVersionEx(&osvi);
	switch(osvi.dwPlatformId)
	{
	case VER_PLATFORM_WIN32_WINDOWS:
		if (osvi.dwMajorVersion > 4 || osvi.dwMinorVersion ==90)
			m_SystemType=0x10;
		else
		if (osvi.dwMajorVersion > 4 || osvi.dwMinorVersion > 0)
			m_SystemType=0x20;
		else
			m_SystemType=0x00;
		break;
	case VER_PLATFORM_WIN32_NT:
		if ( osvi.dwMajorVersion < 4 )
			m_SystemType=0x01;
		else
		if ( osvi.dwMajorVersion == 4 )
			m_SystemType=0x21;
		else
			if (osvi.dwMinorVersion==0)
			m_SystemType=0x31;
			else
			m_SystemType=0x41;
		break;
	default:
		m_SystemType=0x0;

	}

	if (osvi.dwMajorVersion<5 || (osvi.dwMajorVersion==5 && osvi.dwMinorVersion!=1))
	{// <XP
		CDlgViewSystemMethods::uColorNames[30]=COLOR_BTNFACE;
		CDlgViewSystemMethods::uColorNames[31]=COLOR_HIGHLIGHT;

		CDlgViewSystemMethods::uMetricsNames[12]=SM_CXBORDER;
		CDlgViewSystemMethods::uMetricsNames[42]=SM_CXBORDER;
	}

	if (osvi.dwMajorVersion<6)
	{
		CDlgViewSystemMethods::uMetricsNames[94]=SM_CXBORDER;
	}

	m_DragDrop.DragName="";
	m_DragDrop.IdDlg=0xFFFFFFFF;
	m_DragDrop.IdObj=0xFFFFFFFF;
	m_DragDrop.IdScr=0xFFFFFFFF;
	m_DragDrop.MessageSting="";
	m_DragDrop.pImageList=NULL;
	m_DragDrop.hWndDrag=NULL;
	m_DragDrop.hWndLast=NULL;

	#ifdef RUS
		#ifdef BRIZ
			strcpy(TermTip,"Графический PICK терминал 'BRIZ'");
		#else
			strcpy(TermTip,"Терминал Интегрированной базы данных");
		#endif
	#else
		strcpy(TermTip,"Graphic PICK terminal 'BRIZ'");
	#endif

	termCaption=TermTip;
	termCaptionInit=termCaption;

	uLastMessage=0;
	uLastWparam=0;
	uLastLparam=0;

	m_bWaitCursor=FALSE;
	NextParentFromOLE=NULL;
	CListMaker ml;
	ml.CreateList("list1");
	m_bInsertMode=FALSE;
	m_DlgMethods=NULL;
	BlockControl=FALSE;
	long i;
	m_uCurrInputBlock=0;
	m_uCurrOutputBlock=0;

	for(i=0;i<300;i++)
		arrInputBlocks[i]="GPCIO";
	for(i=0;i<100;i++)
		arrOutputBlocks[i]="GPCIO";

	CDlgCodeco::FillDefaultDosAnsiArrays(chAnsiDos,chDosAnsi,chWideAnsiDos,chWideDosAnsi,chWideAnsiDos2,chWideDosAnsi2);
	CDlgCodeco::LoadDosAnsiArrays(chAnsiDos,chDosAnsi,chWideAnsiDos,chWideDosAnsi,chWideAnsiDos2,chWideDosAnsi2);

	AjCheckState=0;
	EasyTCL=false;
	StrTmpOut=new char [TMP_STR_OUT_LEN+10000];
	m_MuteProc=CreateMutex(NULL,TRUE,NULL);
//	m_MuteProc=CreateSemaphore(NULL,1,1,NULL);
	StopEventsFlag=0;
	m_Document=NULL;
	m_View=NULL;
	GPMSG= new GPMessage("",NULL,0);
	m_ScrToolTip=NULL;
	ClearOUTTCL();
	ClearOUTSUB();

	SAFEARRAYBOUND sab={0};
	sab.lLbound=0;
	sab.cElements=2;
	DelimArr1.Create(VT_BSTR,1,&sab);
	sab.cElements=3;
	DelimArr2.Create(VT_BSTR,1,&sab);
	sab.cElements=4;
	DelimArr3.Create(VT_BSTR,1,&sab);
	sab.cElements=5;
	DelimArr4.Create(VT_BSTR,1,&sab);

	for(i=0;i<5;i++)
	{
		CString tmps;
		tmps.Format("%c",i+1);
		BSTR *pBSTR;
		DelimArr4.PtrOfIndex(&i,((void **)&pBSTR));
		tmps.SetSysString(pBSTR);
		if (i<4)
		{
			DelimArr3.PtrOfIndex(&i,((void **)&pBSTR));
			tmps.SetSysString(pBSTR);
			if (i<3)
			{
				DelimArr2.PtrOfIndex(&i,((void **)&pBSTR));
				tmps.SetSysString(pBSTR);
				if (i<2)
				{
					DelimArr1.PtrOfIndex(&i,((void **)&pBSTR));
					tmps.SetSysString(pBSTR);
				}
			}
		}
	}


	a_GPImageList.SetSize(64);
	TCLinProgress=FALSE;
//	m_WaitTCL	=CreateMutex(NULL, FALSE, NULL);
//	m_WaitEndTCL=CreateMutex(NULL, FALSE, NULL);
//	m_WaitSUB	=CreateMutex(NULL, FALSE, NULL);
//	m_WaitEndSUB=CreateMutex(NULL, FALSE, NULL);

	m_WaitTCL	=FALSE;
	m_WaitEndTCL=FALSE;
	m_WaitSUB	=FALSE;
	m_WaitEndSUB=FALSE;

#ifdef BRIZ
	AdmIsOn=1;
#else
	AdmIsOn=0;
#endif
	Flags=0;
	m_hViewWnd=NULL;

	BlinkValue=0;

	if (!_getcwd(app_path,127)) *app_path=0;
	HomeDrive=_getdrive();
	TermCapFileName[0]=0;


	DefFrgColor=RGB(255,255,255);
	DefBkgColor=RGB(0,0,0);
	DefFrgColorInd=7;
	DefBkgColorInd=0;

	ModeSendToDos=0;
	ModeSendToPick=0;

	{
		PHANDLEARRAYITEM pi;
		const char *keyName[]={
		"HKEY_CLASSES_ROOT","HKEY_CURRENT_CONFIG","HKEY_CURRENT_USER","HKEY_DYN_DATA","HKEY_LOCAL_MACHINE",
		"HKEY_PERFORMANCE_DATA","HKEY_PERFORMANCE_NLSTEXT","HKEY_PERFORMANCE_TEXT","HKEY_USERS",
		};
		const HKEY  keyList[]={
		HKEY_CLASSES_ROOT,HKEY_CURRENT_CONFIG,HKEY_CURRENT_USER,HKEY_DYN_DATA,HKEY_LOCAL_MACHINE,
		HKEY_PERFORMANCE_DATA,HKEY_PERFORMANCE_NLSTEXT,HKEY_PERFORMANCE_TEXT,HKEY_USERS,
		};

		for(i=0;i<9;i++)
		{
			pi=&m_HandlerArray.CreateHandle(keyName[i]);
			pi->uType=HANDLER_TYPE_HKEY_PREDEF;
			pi->handle=keyList[i];
		}
	}

}

GPCurrent::~GPCurrent()
{
	if (m_SC_HANDLE) CloseServiceHandle(m_SC_HANDLE);
	m_SC_HANDLE=NULL;

	if (DlgStatistics) 
	{
		if (DlgStatistics->m_hWnd) DlgStatistics->DestroyWindow();
		delete DlgStatistics;
		DlgStatistics=NULL;
	}

	try{
	if (m_pContextMenu) delete m_pContextMenu;
	}catch(...){;}
	m_pContextMenu=NULL;

	if (m_DragDrop.pImageList) delete m_DragDrop.pImageList;
	m_DragDrop.pImageList=NULL;

	if (m_DlgMethods!=NULL)
	{
		try
		{
			m_DlgMethods->DestroyWindow();
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("GPCurrent", "~GPCurrent 508","");
		}
		try
		{
			delete m_DlgMethods;
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("GPCurrent", "~GPCurrent 516","");
		}
		m_DlgMethods = NULL;
	}
	if (GPMSG!=NULL) delete GPMSG;
	if (m_ScrToolTip!=NULL) delete m_ScrToolTip;
	m_ScrToolTip=NULL;
	if (m_MuteProc!=NULL) CloseHandle(m_MuteProc);
	delete[] StrTmpOut;
	StrTmpOut=NULL;
	
	delete[] dwCodePages;
	dwCodePages=NULL;

	if (dwGraphDecodeArray) delete[] dwGraphDecodeArray;
	dwGraphDecodeArray=NULL;

	SetMBConv3(0,0);

	a_GPImageList.RemoveAll();

	GdiplusShutdown(GDIPtoken);

}

void GPCurrent::LoadOLESettings()
{
	CWinApp *tmp=AfxGetApp();
	
	if (tmp!=NULL)
	{
		m_OLESETTINGS.m_WTCL	=tmp->GetProfileInt("OLESETTINGS", "WAITTCL"	,70	);
		m_OLESETTINGS.m_WSUB	=tmp->GetProfileInt("OLESETTINGS", "WAITSUB"	,70	);
		m_OLESETTINGS.m_WFRead	=tmp->GetProfileInt("OLESETTINGS", "WAITFREAD"	,70	);
		m_OLESETTINGS.m_WSystem	=tmp->GetProfileInt("OLESETTINGS", "WAITSYSTEM"	,70	);
		m_OLESETTINGS.m_WMM		=tmp->GetProfileInt("OLESETTINGS", "WAITMM"		,70	);
		m_OLESETTINGS.m_WInput	=tmp->GetProfileInt("OLESETTINGS", "WAITINPUT"	,70	);
		m_OLESETTINGS.m_WFWrite	=tmp->GetProfileInt("OLESETTINGS", "WAITFWRITE"	,70	);
		m_OLESETTINGS.m_WFOther	=tmp->GetProfileInt("OLESETTINGS", "WAITFOTHER"	,70	);
		m_OLESETTINGS.m_CTCL	=tmp->GetProfileInt("OLESETTINGS", "CNTTCL"		,5000	);
		m_OLESETTINGS.m_CSystem	=tmp->GetProfileInt("OLESETTINGS", "CNTSYSTEM"	,600	);
		m_OLESETTINGS.m_CSUB	=tmp->GetProfileInt("OLESETTINGS", "CNTSUB"		,5000	);
		m_OLESETTINGS.m_CMM		=tmp->GetProfileInt("OLESETTINGS", "CNTMM"		,600	);
		m_OLESETTINGS.m_CInput	=tmp->GetProfileInt("OLESETTINGS", "CNTINPUT"	,5000	);
		m_OLESETTINGS.m_CFWrite	=tmp->GetProfileInt("OLESETTINGS", "CNTFWRITE"	,5000	);
		m_OLESETTINGS.m_CFRead	=tmp->GetProfileInt("OLESETTINGS", "CNTFREAD"	,5000	);
		m_OLESETTINGS.m_CFOther	=tmp->GetProfileInt("OLESETTINGS", "CNTFOTHER"	,5000	);
	}
}

void GPCurrent::InitialLoad()
{
	if (_access("IMAGELISTS",0)!=0)
	{
		char sfname[550];
		if (_access("C:\\AP",0)==0) strcpy(sfname,"C:\\AP");
		else
		if (_access("C:\\Program Files\\GP_TERM",0)==0) strcpy(sfname,"C:\\Program Files\\GP_TERM");
		else
		if (_access("D:\\Program Files\\GP_TERM",0)==0) strcpy(sfname,"D:\\Program Files\\GP_TERM");
		else strcpy(sfname,"C:\\AP");
		_chdrive(*sfname-'A'+1);
		_chdir(sfname);
	}
	a_GPImageList[0].LoadList("WL");
	a_GPImageList[1].LoadList("WS");
	a_GPImageList[2].LoadList("ARROWSL");
	a_GPImageList[3].LoadList("ARROWSS");
	a_GPImageList[4].LoadList("TLBR_W95");
	a_GPImageList[5].LoadList("TRAFIKL");
	a_GPImageList[6].LoadList("TRAFIKS");
	a_GPImageList[7].LoadList("WRITINGL");
	a_GPImageList[8].LoadList("WRITINGS");
	a_GPImageList[9].LoadList("MISCL");
	a_GPImageList[10].LoadList("MISCS");
	a_GPImageList[11].LoadList("FLAGL");
	a_GPImageList[12].LoadList("FLAGS");
	a_GPImageList[13].LoadList("OFFICEL");
	a_GPImageList[14].LoadList("OFFICES");

	HBITMAP hbmDev = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BITMAPSEPVIEW),
		IMAGE_BITMAP,
		0,0, // cx,cy
		LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS );
	CBitmap bmDev;
	bmDev.Attach(hbmDev);

	a_GPImageList[15].CreateIL("SEPVIEW",16,16,20,ILC_COLOR8);
	a_GPImageList[15].m_IL.Add(&bmDev,(CBitmap*)NULL);


	HBITMAP hbmDevDis = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BITMAPSEPVIEWDIS),
		IMAGE_BITMAP,
		0,0, // cx,cy
		LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS );
	CBitmap bmDevDis;
	bmDevDis.Attach(hbmDevDis);

	a_GPImageList[16].CreateIL("SEPVIEWDIS",16,16,20,ILC_COLOR8);
	a_GPImageList[16].m_IL.Add(&bmDevDis,(CBitmap*)NULL);
	m_ErrReport.Init();
}

int GPCurrent::GetImageListId(CString Name)
{
	int i=0;
	while(i<GP_NIMAGELIST && a_GPImageList[i].ILName!=Name) i++;

	if (i>=GP_NIMAGELIST && Name!="")
	{
		GPImageList *MainIl=NULL;
		i=GPC.GetImageListId("");
		MainIl=&(GPC.a_GPImageList[i]);
		if (MainIl)	
		{
			MainIl->LoadList(Name);
			if (MainIl->m_IL.m_hImageList && MainIl->m_IL.GetImageCount()<1) 
			{
				MainIl->DeleteList();
				i=GP_NIMAGELIST;
			}
		}
	}

	return i<GP_NIMAGELIST?i:-1; 
}

int GPCurrent::FindImageList(CImageList *iList)
{
	int i=0;
	while(i<GP_NIMAGELIST && a_GPImageList[i].m_IL.m_hImageList!=iList->m_hImageList) i++;
	
	return i<GP_NIMAGELIST?i:-1; 
}

#include "GP_TermView.h"

void GPCurrent::WaitFor_m_MuteProc()
{

	while(WaitForSingleObject(m_MuteProc,100)==WAIT_TIMEOUT)
		((CGP_TermView *)m_View)->DoRemappingInput();
}

void GPCurrent::Release_m_MuteProc()
{
	ReleaseMutex(m_MuteProc);
}

void GPCurrent::ClearOUTTCL()
{
	TCLOutputString="";
	TCLOutputString2="";
}

void GPCurrent::ClearOUTSUB()
{
	SUBOutputString="";
	SUBOutputString2="";
}

const char * GPCurrent::AddToOUTTCL(const char *iStr)
{
	if (*iStr==13)
	{
		long len2=TCLOutputString2.GetLength();
		if (len2>0 && TCLOutputString2.GetAt(len2-1)!=13)
			TCLOutputString2+=iStr;

		if (len2>1000)
		{
			TCLOutputString+=TCLOutputString2;
			TCLOutputString2="";
		}
	}
	else TCLOutputString2+=iStr;

	return TCLOutputString;
}

const char * GPCurrent::AddToOUTSUB(const char *iStr)
{
	SUBOutputString2+=iStr;
	if (SUBOutputString2.GetLength()>1000)
	{
		SUBOutputString+=SUBOutputString2;
		SUBOutputString2="";
	}
	return SUBOutputString;
}

const char * GPCurrent::GetOUTTCL()
{
	if (TCLOutputString2.GetLength()>0 && TCLOutputString2.GetAt(TCLOutputString2.GetLength()-1)==13)
	{
		TCLOutputString+=TCLOutputString2;
		TCLOutputString2="";
	}
	long len=TCLOutputString.GetLength();
	if (len>0 && TCLOutputString.GetAt(--len)==13) TCLOutputString.Delete(len,1);
	
	return TCLOutputString;
}

const char * GPCurrent::GetOUTSUB()
{
	if (SUBOutputString2.GetLength()>0)
	{
		SUBOutputString+=SUBOutputString2;
		SUBOutputString2="";
	}

/*	long len=SUBOutputString.GetLength();
	if (len>0)
	{
		if (SUBOutputString.GetAt(--len)==13) SUBOutputString.Delete(len,1);
		else
		{
			int newpos=SUBOutputString.ReverseFind(13);
			if (newpos<0)
			{
				SUBOutputString2=SUBOutputString;
				SUBOutputString="";
			}
			else
			{
				SUBOutputString2=SUBOutputString.Right(len-newpos);
				SUBOutputString.Delete(newpos,len-newpos+1);
			}
		}
	}
*/
	return SUBOutputString;
}

UINT GPCurrent::GetOUTSUBLen()
{
	GetOUTSUB();
	return SUBOutputString.GetLength();
}

UINT GPCurrent::GetOUTTCLLen()
{
	GetOUTTCL();
	return TCLOutputString.GetLength();
}

const char * GPCurrent::DosToAnsiOUTSUB()
{
	GetOUTSUB();
	DosToAnsiMB((LPCTSTR)SUBOutputString,SUBOutputString);
	return SUBOutputString;
}

const char * GPCurrent::DosToAnsiOUTTCL()
{
	GetOUTTCL();
	DosToAnsiMB((LPCTSTR)TCLOutputString,TCLOutputString);
	return TCLOutputString;
}

#include "GP_TermDoc.h"

BOOL GPCurrent::FindObject(HWND im_hWnd, GPUNITINFO &iUi)
{
	BOOL ret=FALSE;
	GPUNITINFO ui;
	ret=((CGP_TermDoc *)m_Document)->FindObject(im_hWnd,iUi);
	return ret;
}

BOOL GPCurrent::FindObject(const char *cDlgName, const char *cObjName, GPUNITINFO &iUi)
{
	BOOL ret=FALSE;
	GPUNITINFO ui;
	ret=((CGP_TermDoc *)m_Document)->FindObject(cDlgName,cObjName,iUi);
	return ret;
}

BOOL GPCurrent::FindObject(UINT uIdDlg, const char *cObjName, GPUNITINFO &iUi)
{
	BOOL ret=FALSE;
	GPUNITINFO ui;
	ret=((CGP_TermDoc *)m_Document)->FindObject(uIdDlg,cObjName,iUi);
	return ret;
}

UINT GPCurrent::FindDlg(const char *cDlgName1base )
{
	return ((CGP_TermDoc *)m_Document)->FindDlg(cDlgName1base);
}

GPUnit * GPCurrent::GetDlgObject(UINT IdDlg, UINT IdObject)
{
	return ((CGP_TermDoc *)m_Document)->GetDlgUnit(IdDlg,IdObject);
}

UINT GPCurrent::DoRegistryMethod(const char *iStr, char **oStr)
{
	CString HandleName=ExtractField(iStr,1,";");
	PHANDLEARRAYITEM m_Item=NULL;
	HKEY predefKey=NULL;
	if (HandleName!="") StringFromToHKEY(HandleName,predefKey);
	if (predefKey==NULL) m_Item=&m_HandlerArray[(LPCSTR)HandleName];
	int nfunc=-1;

	iStr=strchr(iStr,';');

	if (iStr++)
	{
		char met[150];
		CString smallStr="";
		strncpy(met,iStr,145);
		met[145]=0;
		const char *pos=strchr(iStr,' ');
		if (pos++) *strchr(met,' ')=0;
		else		pos="";	

		int retint=-123456; 
		int atoipos=atoi(pos);
		
		if (*met>='0' && *met<='9') nfunc=atoi(met);
		else
			for(nfunc=0;nfunc<uNRegistryMethods && _stricmp(met,cArrRegistryMethods[nfunc])!=0;nfunc++); 

		if (m_Item || predefKey || nfunc==5)
		{
			try
			{
				switch(nfunc)
				{
				case 0: /*RegCloseKey*/
					if (m_Item && m_Item->handle)
					{
						retint=RegCloseKey((HKEY)m_Item->handle);
						m_Item->handle=NULL;
						m_Item->uType=HANDLER_TYPE_VOID;
					}
					break;
				case 1: /*RegConnectRegistry*/
					if (m_Item)
					{
						retint=-1;
						if (m_Item->handle) m_HandlerArray.FreeHandle(*m_Item);
						m_Item->handle=NULL;
						HKEY remKey=NULL;
						CString fld1=ExtractField(pos,1,",");
						if (fld1!="") StringFromToHKEY(fld1,remKey);
						m_Item->uType=HANDLER_TYPE_VOID;
						if (remKey)
						{
							retint=RegConnectRegistry(ExtractField(pos,2,","),remKey,(HKEY *)&m_Item->handle);
							m_Item->uType=HANDLER_TYPE_HKEY;
						}
					}
					break;
				case 2: /*RegCreateKeyEx*/
					if (m_Item)
					{
						if (m_Item->handle) m_HandlerArray.FreeHandle(*m_Item);
						HKEY hKey=NULL;
						CString fld1=ExtractField(pos,1,",");
						if (fld1!="") StringFromToHKEY(fld1,hKey);
						if (hKey==NULL) m_HandlerArray[fld1].handle;
						m_Item->uType=HANDLER_TYPE_VOID;
						if (hKey)
						{
							UINT KeyOptions=0;
							DWORD CreateDisp=0;
							char tmpClass[250];
							strncpy(tmpClass,ExtractField(pos,3,","),248);
							tmpClass[248]=0;
							CString fld4=ExtractField(pos,4,",");
							if (fld4=="") fld4="qwerty";
							CString fld5=ExtractField(pos,5,",");
							if (fld5=="") fld5="qwerty";
							retint=RegCreateKeyEx(
								hKey,
								ExtractField(pos,2,","),
								0,
								tmpClass,
								StringFromToKEYOPTION(fld4,KeyOptions),
								StringFromToSamDesired(fld5,KeyOptions),
								NULL,
								(HKEY *)&m_Item->handle,
								&CreateDisp
								);
							char tmpCreateDisp[250];
							*tmpCreateDisp=0;
							StringFromToCreateDisp(tmpCreateDisp,CreateDisp);
							smallStr.Format("%d\x7F%s",retint,tmpCreateDisp);
							if (m_Item->handle)
								m_Item->uType=HANDLER_TYPE_HKEY;
						}
					}
					break;
				case 3: /*RegDeleteKey*/
					if (predefKey || (m_Item && m_Item->handle))
						retint=RegDeleteKey(predefKey?predefKey:(HKEY)m_Item->handle,pos);
					break;
				case 4: /*RegDeleteValue*/
					if (predefKey || (m_Item && m_Item->handle))
						retint=RegDeleteValue(predefKey?predefKey:(HKEY)m_Item->handle,pos);
					break;
				case 5: /*RegDisablePredefinedCache*/
					#ifdef W_95
					#else
						#ifdef W_NT
						#else
							#ifdef W_98
							#else
								RegDisablePredefinedCache();
							#endif
						#endif
					#endif
					break;
				case 6: /*RegEnumKeyEx*/
					if ((predefKey || (m_Item && m_Item->handle)) && oStr)
					{
						HKEY curKey=predefKey?predefKey:(HKEY)m_Item->handle;
						int start=0,end=1000;
						m_LastScanf=sscanf(pos,"%d,%d",&start,&end);
						if (*oStr==NULL) *oStr=new char [50000];
						**oStr=0;
						int len=50000;
						int curlen=0;
						char skName[510];
						char nmClass[256];
						FILETIME ft={0};
						int i;
						for(i=start;i<=end;i++)
						{
							*skName=0;
							*nmClass=0;
							DWORD lenName=480;
							DWORD lenClass=250;
							if (RegEnumKeyEx(curKey,i,skName,&lenName,NULL,nmClass,&lenClass,&ft)!=ERROR_NO_MORE_ITEMS)
							{
								skName[lenName]=0;
								nmClass[lenClass]=0;
								if (curlen>len-1000)
								{
									len+=50000;
									char *tmp=new char [len];
									strcpy(tmp,*oStr);
									delete[] *oStr;
									*oStr=tmp;
								}
								SYSTEMTIME LastTime={0}; 
								FileTimeToSystemTime(&ft,&LastTime);

								curlen+=sprintf(*oStr+curlen,"%s%s\x7%s\x7%d\x7%d\x7%d\x7%d\x7%d\x7%d\x7%d",
								curlen?"\x7F":"",
								skName,
								nmClass,
								LastTime.wYear,LastTime.wMonth,LastTime.wDay,LastTime.wHour,LastTime.wMinute,LastTime.wSecond,LastTime.wMilliseconds
								);
							}
							else break;
						}
					}
					break;
				case 7: /*RegEnumValue*/
					if ((predefKey || (m_Item && m_Item->handle)) && oStr)
					{
						HKEY curKey=predefKey?predefKey:(HKEY)m_Item->handle;
						int start=0,end=1000;
						m_LastScanf=sscanf(pos,"%d,%d",&start,&end);
						if (*oStr==NULL) *oStr=new char [100000];
						**oStr=0;
						UINT len=100000;
						UINT curlen=0;
						BYTE *byteData = new BYTE [100000];
						char skName[500];

						int i;
						for(i=start;i<=end;i++)
						{
							*skName=0;
							DWORD lenName=480;
							DWORD lenData=100000;
							DWORD dwType=0;
							*byteData=0;
							if (RegEnumValue(curKey,i,skName,&lenName,NULL,&dwType,byteData,&lenData)==ERROR_SUCCESS)
							{
								skName[lenName]=0;
								byteData[lenData]=0;
								while(curlen+lenData+lenData+lenName+10>len)
								{
									len+=50000;
									char *tmp=new char [len];
									strcpy(tmp,*oStr);
									delete[] *oStr;
									*oStr=tmp;
								}
								char dataType[50];
								*dataType=0;
								StringFromToValueType(dataType,dwType);
								curlen+=sprintf(*oStr+curlen,"%s%s\x7%s\x7",curlen?"\x7F":"",skName,dataType);
								curlen+=RegDataToString(byteData,lenData,dwType,*oStr+curlen);
								*(*oStr+curlen)=0;
							}
							else break;
						}
						delete[] byteData;
					}
					break;
				case 8: /*RegFlushKey*/
					if (predefKey || (m_Item && m_Item->handle))
						retint=RegFlushKey(predefKey?predefKey:(HKEY)m_Item->handle);
					break;
				case 10: /*RegLoadKey*/
					retint=-1;
					if (predefKey || (m_Item && m_Item->handle))
						retint=RegLoadKey(predefKey?predefKey:(HKEY)m_Item->handle,ExtractField(pos,1,","),ExtractField(pos,2,","));
					break;
				case 11: /*RegNotifyChangeKeyValue bWatchSubtree,dwNotifyFilter,nTimes,NotifySub,InfoText*/
					if ((predefKey || (m_Item && m_Item->handle)) && nNotifyThreads<64)
					{
						PGPNOTIFYTHREADSTRUCT mns=new GPNOTIFYTHREADSTRUCT;
						mns->autoDelete=GPNTS_DELETE_STRUCT|GPNTS_DELETE_EVENT;
						mns->csInfo=ExtractField(pos,5,",");
						mns->csSubName=ExtractField(pos,4,",");
						mns->nTimes=atoi(ExtractField(pos,3,","));
						BOOL bWatchSubtree=atoi(ExtractField(pos,1,","));
						DWORD dwNotifyFilter=0;
						CString fld2=ExtractField(pos,2,",");
						if (fld2=="") fld2="qwerty";

						dwNotifyFilter=StringFromToRegNotify(fld2,dwNotifyFilter);
						mns->hEvent=CreateEvent(NULL, TRUE, FALSE, NULL);
						mns->hHahdle=predefKey?predefKey:m_Item->handle;
						LONG retNotify=-1;

						if (mns->hEvent) retNotify=RegNotifyChangeKeyValue(predefKey?predefKey:(HKEY)m_Item->handle,bWatchSubtree,dwNotifyFilter,mns->hEvent,TRUE);
						if (mns->hEvent==NULL || retNotify!=ERROR_SUCCESS || AfxBeginThread(RegistryNotifWaitThreadFn,(LPVOID)mns)==NULL)
						{
							CloseHandle(mns->hEvent);
							delete mns;
						}
					}
					break;
				#ifdef W_95
				#else
					#ifdef W_NT
					#else
						#ifdef W_98
						#else
							case 12: /*RegOpenCurrentUser*/
								if (m_Item)
								{
									retint=-1;
									if (m_Item->handle) m_HandlerArray.FreeHandle(*m_Item);
									m_Item->handle=NULL;
									m_Item->uType=HANDLER_TYPE_VOID;
									UINT samDesired=0;

									if ((retint=RegOpenCurrentUser(StringFromToSamDesired(*pos?pos:"qwerty",samDesired),(HKEY *)&m_Item->handle))==ERROR_SUCCESS)
										m_Item->uType=HANDLER_TYPE_HKEY;
								}
								break;
						#endif
					#endif
				#endif
				case 13: /*RegOpenKeyEx OpenKey,SubkeyName,samDesired*/
					{
						if (*oStr==NULL) *oStr=new char [1000];
						**oStr=0;
						HKEY remKey=NULL;
						CString fld1=ExtractField(pos,1,",");
						if (fld1=="") fld1="qwerty";
						if (StringFromToHKEY(fld1,remKey)==NULL && m_HandlerArray[fld1].uType==(HANDLER_TYPE_HKEY|HANDLER_TYPE_HKEY_PREDEF))
							remKey=(HKEY)(m_HandlerArray[ExtractField(pos,1,",")].handle);
						if (m_Item)
						{
							if (m_Item->handle) m_HandlerArray.FreeHandle(*m_Item);
							m_Item->handle=NULL;
							m_Item->uType=HANDLER_TYPE_VOID;
							UINT samDesired=0;
							CString fld3=ExtractField(pos,3,",");
							if (fld3=="") fld1="qwerty";
							StringFromToSamDesired(fld3,samDesired);

							if (remKey)
							{
								retint=RegOpenKeyEx(remKey,ExtractField(pos,2,","),0,samDesired,(HKEY *)(&(m_Item->handle)));
								if (m_Item->handle) m_Item->uType=HANDLER_TYPE_HKEY;
								sprintf(*oStr,"%d",(DWORD)m_Item->handle);
							}
						}
					}
					break;
				#ifdef W_95
				#else
					#ifdef W_NT
					#else
						#ifdef W_98
						#else
							case 14: /*RegOpenUserClassesRoot*/
								if (m_Item)
								{
									retint=-1;
									if (m_Item->handle) m_HandlerArray.FreeHandle(*m_Item);
									m_Item->handle=NULL;
									m_Item->uType=HANDLER_TYPE_VOID;
									UINT samDesired=0;
									HANDLE UserToken=m_HandlerArray[ExtractField(pos,1,",")].handle;
									CString fld2=ExtractField(pos,2,",");
									if (fld2=="") fld2="qwerty";

									if ((retint=RegOpenUserClassesRoot(UserToken,StringFromToSamDesired(fld2,samDesired),0,(HKEY *)&m_Item->handle))==ERROR_SUCCESS)
										m_Item->uType=HANDLER_TYPE_HKEY;
								}
								break;
							case 15: /*RegOverridePredefKey*/
								retint=-1;
								if (m_Item && m_Item->handle && m_Item->uType==HANDLER_TYPE_HKEY)
								{
									HKEY remKey=NULL;
									CString fld1=ExtractField(pos,1,",");
									if (fld1=="") fld1="qwerty";
									StringFromToHKEY(fld1,remKey);
									if (remKey)
										retint=RegOverridePredefKey(remKey,(HKEY)m_Item->handle);
								}
								break;
						#endif
					#endif
				#endif

				case 16: /*RegQueryInfoKey*/
					retint=-1;
					if (predefKey || (m_Item && m_Item->handle))
					{
						char m_Class[550];
						*m_Class=0;
						DWORD cClass=512;
						DWORD Reserved=0;
						DWORD cSubKeys=0;
						DWORD cMaxSubKeyLen=0;
						DWORD cMaxClassLen=0;
						DWORD cValues=0;           
						DWORD cMaxValueNameLen=0;
						DWORD cMaxValueLen=0;
						DWORD cbSecurityDescriptor=0;
						FILETIME ftLastWriteTime={0};


						retint=RegQueryInfoKey(predefKey?predefKey:(HKEY)(m_Item->handle),
							m_Class,
							&cClass,               // size of class buffer
							&Reserved,             // reserved
							&cSubKeys,             // number of subkeys
							&cMaxSubKeyLen,        // longest subkey name
							&cMaxClassLen,         // longest class string
							&cValues,              // number of value entries
							&cMaxValueNameLen,     // longest value name
							&cMaxValueLen,         // longest value data
							&cbSecurityDescriptor, // descriptor length
							&ftLastWriteTime     // last write time
							);

						if (retint==ERROR_SUCCESS)
						{
							SYSTEMTIME LastTime={0}; 
							FileTimeToSystemTime(&ftLastWriteTime,&LastTime);

							smallStr.Format("%s\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7%d\x7%d\x7%d\x7%d\x7%d\x7%d",
								m_Class,
								&cSubKeys,             // number of subkeys
								&cMaxSubKeyLen,        // longest subkey name
								&cMaxClassLen,         // longest class string
								&cValues,              // number of value entries
								&cMaxValueNameLen,     // longest value name
								&cMaxValueLen,         // longest value data
								&cbSecurityDescriptor, // descriptor length
								&Reserved,             // reserved
								LastTime.wYear,LastTime.wMonth,LastTime.wDay,LastTime.wHour,LastTime.wMinute,LastTime.wSecond,LastTime.wMilliseconds
								);
						}
					}

					break;
				case 17: /*RegQueryMultipleValues SubKeyName1^SubKeyName2^...*/
					retint=-1;
					if (oStr && *pos && (predefKey || (m_Item && m_Item->handle)))
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						int lenpos=0;
						char *postmp=pos333;
						UINT nValues=1;
						while(*(postmp++))
						{
							if ((*postmp==GPC.DelimiterIn1 || *postmp==',') && postmp[1] && postmp[1]!=GPC.DelimiterIn1 && postmp[1]!=',') nValues++;
							lenpos++;
						}

						UINT i;
						VALENT *arr=new VALENT [nValues];
						postmp=pos333;
						for(i=0;i<nValues && *postmp;i++)
						{
							arr[i].ve_type=arr[i].ve_valuelen=arr[i].ve_valueptr=0;
							arr[i].ve_valuename=postmp;
							while(*postmp && *postmp!=GPC.DelimiterIn1 && *postmp!=',') postmp++;
							if (*postmp)
								*(postmp++)=0;
						}

						DWORD RetLen=0;
						RegQueryMultipleValues(predefKey?predefKey:(HKEY)(m_Item->handle),arr,nValues,NULL,&RetLen);
						{
							char *RetArr=new char [RetLen+100+nValues*8];
							if ((retint=RegQueryMultipleValues(predefKey?predefKey:(HKEY)(m_Item->handle),arr,nValues,RetArr,&RetLen))==ERROR_SUCCESS)
							{
								if (*oStr) delete[] *oStr;
								*oStr=new char [RetLen+RetLen+nValues*50+lenpos+1000];
								**oStr=0;
								char *posOUT=*oStr;

								char vType[100];
								for(i=0;i<nValues && *postmp;i++)
								{
									if (i) {*(posOUT++)=127;*posOUT=0;}
									*vType=0;
									StringFromToValueType(vType,arr[i].ve_type);
									posOUT+=sprintf(posOUT,"%s\x7%s\x7",arr[i].ve_valuename,vType);
									posOUT+=RegDataToString((BYTE *)(arr[i].ve_valueptr),arr[i].ve_valuelen,arr[i].ve_type,posOUT);
									*posOUT=0;
								}
							}
							delete[] RetArr;
						}
						delete[] pos333;
					}
					break;
				case 18: /*RegQueryValueEx ValueName*/
					retint=-1;
					if (oStr && *pos && (predefKey || (m_Item && m_Item->handle)))
					{
						DWORD dwReserved=0;	// reserved
						DWORD dwType=0;		// type buffer
						BYTE *cData=0;			// data buffer
						DWORD cbData=0;		// size of data buffer
						if ((retint=RegQueryValueEx(predefKey?predefKey:(HKEY)(m_Item->handle),pos,&dwReserved,&dwType,NULL,&cbData))==ERROR_SUCCESS && cbData>0 && cbData<2000000)
						{
							cData=new BYTE [cbData+100];

							if ((retint=RegQueryValueEx(predefKey?predefKey:(HKEY)(m_Item->handle),pos,&dwReserved,&dwType,cData,&cbData))==ERROR_SUCCESS)
							{
								if (*oStr==NULL) *oStr=new char [100000];
								**oStr=0;
								StringFromToValueType(*oStr,dwType);
								strcat(*oStr,"\x7F");
								char *tmppos=*oStr+(int)strlen(*oStr);
								tmppos[RegDataToString(cData,cbData,dwType,tmppos)]=0;
							}
							delete[] cData;
						}
					}
					break;
				case 19: /*RegReplaceKey SubKeyName,NewFile,OldFile*/
					retint=-1;
					if (*pos && (predefKey || (m_Item && m_Item->handle)) && *FindField(pos,3,","))
						retint=RegReplaceKey(
							predefKey?predefKey:(HKEY)(m_Item->handle),
							ExtractField(pos,1,","),
							ExtractField(pos,2,","),
							ExtractField(pos,3,","));
					break;
				#ifdef W_95
				#else
					#ifdef W_98
					#else
						case 20: /*RegRestoreKey File,dwFlags*/
							retint=-1;
							if (*pos && (predefKey || (m_Item && m_Item->handle)))
							{
								DWORD dwFlags=0;
								CString fld2=ExtractField(pos,2,",");
								if (fld2=="") fld2="qwerty";
								retint=RegRestoreKey(
									predefKey?predefKey:(HKEY)(m_Item->handle),
									ExtractField(pos,1,","),
									StringFromToRestoreOption(fld2,dwFlags));
							}
							break;
					#endif
				#endif

				case 21: /*RegSaveKey*/
					retint=-1;
					if (*pos && (predefKey || (m_Item && m_Item->handle)))
						retint=RegSaveKey(predefKey?predefKey:(HKEY)(m_Item->handle),pos,NULL);
					break;
				case 23: /*RegSetValueEx ValueName,Type,DelimiterCode,Data*/
					retint=-1;
					if (*pos && (predefKey || (m_Item && m_Item->handle)))
					{
						DWORD dwType=0;
						CString fld2=ExtractField(pos,2,",");
						if (fld2=="") fld2="qwerty";
						StringFromToValueType(fld2,dwType);
						BYTE *ArrData=NULL;
						const char *posfield=FindField(pos,4,",");
						DWORD cbData=StringToRegData(&ArrData, dwType, posfield?posfield:"",(char)atoi(ExtractField(pos,3,",")));

						retint=RegSetValueEx(
						  predefKey?predefKey:(HKEY)(m_Item->handle),
						  ExtractField(pos,1,","), // value name
						  0,        // reserved
						  dwType,   // value type
						  ArrData,  // value data
						  cbData    // size of value data
						);

						if (ArrData) delete[] ArrData;
					}
					break;
				case 24: /*RegUnLoadKey*/
					retint=-1;
					if (*pos && (predefKey || (m_Item && m_Item->handle)))
						retint=RegUnLoadKey(predefKey?predefKey:(HKEY)(m_Item->handle),pos);
					break;

				#ifdef W_95
				#else
					#ifdef W_NT
					#else
						#ifdef W_98
						#else
							#ifdef W_2000
							#else
								case 25: /*RegSaveKeyEx*/
									retint=-1;
									if (*pos && (predefKey || (m_Item && m_Item->handle)))
									{
										DWORD dwFlags=0;
										CString fld2=ExtractField(pos,2,",");
										if (fld2=="") fld2="qwerty";
										retint=RegSaveKeyEx(
											predefKey?predefKey:(HKEY)(m_Item->handle),
											ExtractField(pos,1,","),
											NULL,
											StringFromToSaveOption(fld2,dwFlags));
									}
									break;
							#endif
						#endif
					#endif
				#endif

				case 9: /*RegGetKeySecurity*/
				case 22: /*RegSetKeySecurity*/
				default:
					GPC.m_ErrReport.GPWriteWarnLog2("System Registry", "Unknown Method",iStr);
					if (oStr!=NULL)
					{
						*oStr=new char [1000];
						sprintf(*oStr,ErrObjSub,met); nfunc=0xFFFFFFFFL; 
					}
					break;
				}
			}catch(...)
			{
				char *str=new char [(int)strlen(pos)+1000];
				#ifdef RUS
					sprintf(str,"Ошибка выполнения метода %s %s",met,pos);
					::MessageBox(GPC.m_hViewWnd,str,"Ошибка метода",MB_OK|MB_ICONEXCLAMATION);
				#else
					sprintf(str,"Error execution of method %s %s",met,pos);
					::MessageBox(GPC.m_hViewWnd,str,"Error execution",MB_OK|MB_ICONEXCLAMATION);
				#endif
				nfunc=0xFFFFFFFFL;
				GPC.m_ErrReport.GPWriteErrorLog("GPCurrent", "DoRegistryMethod",iStr);
				if (oStr!=NULL && *oStr==0)
					*oStr=str;
				else
					delete[] str;
			}

			if (oStr!=NULL && *oStr==0)
			{
				if (smallStr!="")
				{
					*oStr=new char [smallStr.GetLength()+10];
					strcpy(*oStr,smallStr);
				}
				else
				if (retint!=-123456)
				{
					*oStr=new char [1000];
					sprintf(*oStr,"%d",retint);
				}
			}
		}
	}

	return nfunc;

}

HKEY GPCurrent::StringFromToHKEY(const char *iKey, HKEY & convKey)
{
	UINT nOptions=9;
	const char *keyName[]={
	"HKEY_CLASSES_ROOT","HKEY_CURRENT_CONFIG","HKEY_CURRENT_USER","HKEY_DYN_DATA","HKEY_LOCAL_MACHINE",
	"HKEY_PERFORMANCE_DATA","HKEY_PERFORMANCE_NLSTEXT","HKEY_PERFORMANCE_TEXT","HKEY_USERS",
	};
	const HKEY  keyList[]={
	HKEY_CLASSES_ROOT,HKEY_CURRENT_CONFIG,HKEY_CURRENT_USER,HKEY_DYN_DATA,HKEY_LOCAL_MACHINE,
	HKEY_PERFORMANCE_DATA,HKEY_PERFORMANCE_NLSTEXT,HKEY_PERFORMANCE_TEXT,HKEY_USERS,
	};

	if (*iKey)
	{
		convKey=NULL;
		UINT i;
		for(i=0;i<nOptions && convKey==NULL;i++)
			if (_stricmp(iKey,keyName[i])==0)
				convKey=keyList[i];
		if (convKey==NULL) convKey=(HKEY)atoi(iKey);
	}
	else
	if (convKey)
	{
		UINT i;
		for(i=0;i<nOptions && *iKey==0;i++)
			if (convKey==keyList[i])
				strcpy((char *)iKey,keyName[i]);
	}


	return convKey;
}

UINT GPCurrent::StringFromToKEYOPTION(const char *iOption, UINT & convOption)
{
	UINT nOptions=5;
	const char *OptionName[]={
	"REG_OPTION_NON_VOLATILE","REG_OPTION_VOLATILE","REG_OPTION_CREATE_LINK","REG_OPTION_BACKUP_RESTORE","REG_OPTION_OPEN_LINK",
	};
	const UINT  uOptionList[]={
	REG_OPTION_NON_VOLATILE,REG_OPTION_VOLATILE,REG_OPTION_CREATE_LINK,REG_OPTION_BACKUP_RESTORE,REG_OPTION_OPEN_LINK,
	};

	if (*iOption)
	{
		convOption=atoi(iOption);
		UINT i;
		for(i=0;i<nOptions && convOption==NULL;i++)
			if (_stricmp(iOption,OptionName[i])==0)
				convOption=uOptionList[i];
	}
	else
	{
		UINT i;
		for(i=0;i<nOptions && *iOption==0;i++)
			if (convOption==uOptionList[i])
				strcpy((char *)iOption,OptionName[i]);

		if (*iOption==0) sprintf((char *)iOption,"%d",convOption);
	}
	return convOption;
}

UINT GPCurrent::StringFromToSamDesired(const char *iSamDesired, UINT & convSamDesired)
{
	const char *OptionName[]={
	"KEY_ALL_ACCESS","KEY_WRITE","KEY_EXECUTE","KEY_READ","KEY_QUERY_VALUE",
	"KEY_SET_VALUE","KEY_CREATE_SUB_KEY","KEY_ENUMERATE_SUB_KEYS","KEY_NOTIFY","KEY_CREATE_LINK",
	"KEY_WOW64_32KEY","KEY_WOW64_64KEY","KEY_WOW64_RES",
	};
	const UINT  uOptionList[]={
	KEY_ALL_ACCESS,KEY_WRITE,KEY_EXECUTE,KEY_READ,KEY_QUERY_VALUE,
	KEY_SET_VALUE,KEY_CREATE_SUB_KEY,KEY_ENUMERATE_SUB_KEYS,KEY_NOTIFY,KEY_CREATE_LINK,
	KEY_WOW64_32KEY,KEY_WOW64_64KEY,KEY_WOW64_RES,
	};


	if (*iSamDesired)
	{
		char *tmps=new char [(int)strlen(iSamDesired)+100];
		strcpy(tmps,iSamDesired);
		_strupr(tmps);
		convSamDesired=atoi(tmps);
		UINT i;
		for(i=0;i<13;i++)
			if (strstr(tmps,OptionName[i]))
				convSamDesired|=uOptionList[i];
		delete[] tmps;
	}
	else
	{
		UINT convSD=convSamDesired;
		UINT i;
		for(i=0;i<13;i++)
			if ((convSD&uOptionList[i])==uOptionList[i])
			{
				if (*iSamDesired) strcat((char *)iSamDesired,"|");
				strcat((char *)iSamDesired,OptionName[i]);
				convSD^=uOptionList[i];
			}
			if (convSD) sprintf((char *)iSamDesired+(int)strlen(iSamDesired),"%s%d",*iSamDesired?"|":"",convSD);
	}

	return convSamDesired;
}


DWORD GPCurrent::StringFromToRegNotify(const char *iSamDesired, DWORD & convSamDesired)
{
	const char *OptionName[]={
	"REG_NOTIFY_CHANGE_NAME","REG_NOTIFY_CHANGE_ATTRIBUTES","REG_NOTIFY_CHANGE_LAST_SET","REG_NOTIFY_CHANGE_SECURITY",
	};
	const UINT  uOptionList[]={
	REG_NOTIFY_CHANGE_NAME,REG_NOTIFY_CHANGE_ATTRIBUTES,REG_NOTIFY_CHANGE_LAST_SET,REG_NOTIFY_CHANGE_SECURITY,
	};


	if (*iSamDesired)
	{
		char *tmps=new char [(int)strlen(iSamDesired)+100];
		strcpy(tmps,iSamDesired);
		_strupr(tmps);
		convSamDesired=atoi(tmps);
		UINT i;
		for(i=0;i<4;i++)
			if (strstr(tmps,OptionName[i]))
				convSamDesired|=uOptionList[i];
		delete[] tmps;
	}
	else
	{
		UINT convSD=convSamDesired;
		UINT i;
		for(i=0;i<4;i++)
			if ((convSD&uOptionList[i])==uOptionList[i])
			{
				if (*iSamDesired) strcat((char *)iSamDesired,"|");
				strcat((char *)iSamDesired,OptionName[i]);
				convSD^=uOptionList[i];
			}
			if (convSD) sprintf((char *)iSamDesired+(int)strlen(iSamDesired),"%s%d",*iSamDesired?"|":"",convSD);
	}

	return convSamDesired;
}

DWORD GPCurrent::StringFromToCreateDisp(const char *iOption, DWORD & convOption)
{
	UINT nOptions=2;
	const char *OptionName[]={
	"REG_CREATED_NEW_KEY","REG_OPENED_EXISTING_KEY",
	};
	const UINT  uOptionList[]={
	REG_CREATED_NEW_KEY,REG_OPENED_EXISTING_KEY,
	};

	if (*iOption)
	{
		convOption=atoi(iOption);
		UINT i;
		for(i=0;i<nOptions && convOption==NULL;i++)
			if (_stricmp(iOption,OptionName[i])==0)
				convOption=uOptionList[i];
	}
	else
	{
		UINT i;
		for(i=0;i<nOptions && *iOption==0;i++)
			if (convOption==uOptionList[i])
				strcpy((char *)iOption,OptionName[i]);

		if (*iOption==0) sprintf((char *)iOption,"%d",convOption);
	}
	return convOption;
}

DWORD GPCurrent::StringFromToValueType(const char *iOption, DWORD & convOption)
{
	UINT nOptions=12;
	const char *OptionName[]={
	"REG_BINARY","REG_DWORD","REG_DWORD_BIG_ENDIAN","REG_EXPAND_SZ","REG_LINK",
	"REG_MULTI_SZ","REG_NONE","REG_QWORD","REG_RESOURCE_LIST","REG_SZ",
	"REG_RESOURCE_REQUIREMENTS_LIST","REG_FULL_RESOURCE_DESCRIPTOR",
	};
	const DWORD  uOptionList[]={
	REG_BINARY,REG_DWORD,REG_DWORD_BIG_ENDIAN,REG_EXPAND_SZ,REG_LINK,
	REG_MULTI_SZ,REG_NONE,REG_QWORD,REG_RESOURCE_LIST,REG_SZ,
	REG_RESOURCE_REQUIREMENTS_LIST,REG_FULL_RESOURCE_DESCRIPTOR,
	};

	if (*iOption)
	{
		convOption=atoi(iOption);
		UINT i;
		for(i=0;i<nOptions && convOption==NULL;i++)
			if (_stricmp(iOption,OptionName[i])==0)
				convOption=uOptionList[i];
	}
	else
	{
		UINT i;
		for(i=0;i<nOptions && *iOption==0;i++)
			if (convOption==uOptionList[i])
				strcpy((char *)iOption,OptionName[i]);

		if (*iOption==0) sprintf((char *)iOption,"%d",convOption);
	}
	return convOption;
}

DWORD GPCurrent::StringFromToRestoreOption(const char *iOption, DWORD & convOption)
{
	UINT nOptions=4;
	const char *OptionName[]={
	"REG_FORCE_RESTORE","REG_NO_LAZY_FLUSH","REG_REFRESH_HIVE","REG_WHOLE_HIVE_VOLATILE",
	};
	const DWORD  uOptionList[]={
	REG_FORCE_RESTORE,REG_NO_LAZY_FLUSH,REG_REFRESH_HIVE,REG_WHOLE_HIVE_VOLATILE,
	};

	if (*iOption)
	{
		convOption=atoi(iOption);
		UINT i;
		for(i=0;i<nOptions && convOption==NULL;i++)
			if (_stricmp(iOption,OptionName[i])==0)
				convOption=uOptionList[i];
	}
	else
	{
		UINT i;
		for(i=0;i<nOptions && *iOption==0;i++)
			if (convOption==uOptionList[i])
				strcpy((char *)iOption,OptionName[i]);

		if (*iOption==0) sprintf((char *)iOption,"%d",convOption);
	}
	return convOption;
}

DWORD GPCurrent::StringFromToSaveOption(const char *iOption, DWORD & convOption)
{
	UINT nOptions=3;
	const char *OptionName[]={
	"REG_STANDARD_FORMAT","REG_LATEST_FORMAT","REG_NO_COMPRESSION",
	};
	const DWORD  uOptionList[]={
	REG_STANDARD_FORMAT,REG_LATEST_FORMAT,REG_NO_COMPRESSION,
	};

	if (*iOption)
	{
		convOption=atoi(iOption);
		UINT i;
		for(i=0;i<nOptions && convOption==NULL;i++)
			if (_stricmp(iOption,OptionName[i])==0)
				convOption=uOptionList[i];
	}
	else
	{
		UINT i;
		for(i=0;i<nOptions && *iOption==0;i++)
			if (convOption==uOptionList[i])
				strcpy((char *)iOption,OptionName[i]);

		if (*iOption==0) sprintf((char *)iOption,"%d",convOption);
	}
	return convOption;
}

UINT GPCurrent::RegDataToString(BYTE *iData, UINT uDataLen, DWORD dwDataType, char *outPut)
{
	UINT ret=0;
	*outPut=0;

	switch(dwDataType)
	{
	case REG_SZ:
	case REG_EXPAND_SZ:
	case REG_LINK:
	case REG_RESOURCE_LIST:
	case REG_RESOURCE_REQUIREMENTS_LIST:
		strcpy(outPut,(const char *)iData);
		ret=uDataLen;
		break;
	case REG_NONE:
	case REG_BINARY:
	case REG_DWORD:
	case REG_DWORD_BIG_ENDIAN:
	case REG_QWORD:
	case REG_FULL_RESOURCE_DESCRIPTOR:
		{
			char cnvArr[]={
				'0','1','2','3','4','5','6','7',
				'8','9','A','B','C','D','E','F',
			};

			while(uDataLen-->0)
			{
				ret++;ret++;
				*(outPut++)=cnvArr[((*iData)/16)&0xF];
				*(outPut++)=cnvArr[(*(iData++))&0xF];
			}
		}
		break;
	case REG_MULTI_SZ:
		while(*iData)
		{
			int len=(int)strlen(strcpy(outPut,(const char *)iData));
			ret+=len;
			iData+=len;
			iData++;
			outPut+=len;
			if (*iData)
			{
				ret++;
				*(outPut++)=2;
				*(outPut)=0;
			}
		}
		break;
	}
	return ret;
}

UINT GPCurrent::StringToRegData(BYTE **ArrData, DWORD dwDataType, const char *iData, char Delimiter)
{
	UINT ret=(int)strlen(iData);

	*ArrData= new BYTE [ret+256];
	**ArrData=0;

	switch(dwDataType)
	{
	case REG_SZ:
	case REG_EXPAND_SZ:
	case REG_LINK:
	case REG_RESOURCE_LIST:
	case REG_RESOURCE_REQUIREMENTS_LIST:
		strcpy((char *)*ArrData,iData);
		break;
	case REG_NONE:
	case REG_BINARY:
	case REG_DWORD:
	case REG_DWORD_BIG_ENDIAN:
	case REG_QWORD:
	case REG_FULL_RESOURCE_DESCRIPTOR:
		convHexToByteArr(iData,*ArrData);
		ret/=2;
		break;
	case REG_MULTI_SZ:
		{
			BYTE *Dest=*ArrData;
			const char *src=iData;
			while(*src)
			{
				if (*src==Delimiter) *(Dest++)=0;
				else *(Dest++)=*src;
				src++;
			}
			*(Dest++)=0;
			*(Dest++)=0;
			ret+=2;
		}
		break;
	}
	return ret;
}

void GPCurrent::SaveBarVisibleFlag()
{
	AfxGetApp()->WriteProfileInt(cs_RegTermViewSetName, "BarViewSet",m_BarVisibleFlag);
}

BOOL GPCurrent::SetIconFromIL(HWND iHWND, const char *iILName, int iImageNum)
{
	BOOL ret=FALSE;
	if (iHWND && iILName && *iILName)
	{
		int num=0;
		if ((num=this->GetImageListId(iILName))>=0)
		{
			HICON tmpHICON=a_GPImageList[num].m_IL.ExtractIcon(iImageNum);
			if (tmpHICON)
			{
				IMAGEINFO ii={0};
				a_GPImageList[num].m_IL.GetImageInfo(iImageNum,&ii);
				DestroyIcon(CWnd::FromHandle(iHWND)->SetIcon(tmpHICON,ii.rcImage.bottom-ii.rcImage.top>16));
			}
		}
	}

	return ret;
}

DWORD GPCurrent::LoadGraphCodeco()
{
	DWORD ret=0;
	int i;
	DWORD defVal[]=
		{
			0,	1,	2,	3,	4,	5,	6,	7,	8,	9,
			10,	11,	12,	13,	14,	15,	16,	17,	18,	19,
			20,	21,	22,	23,	24,	25,	26,	27,	28,	29,
			30,	31,	32,	33,	34,	35,	36,	37,	38,	39,
			40,	41,	42,	43,	44,	45,	46,	47,	48,	49,
			50,	51,	52,	53,	54,	55,	56,	57,	58,	59,
			60,	61,	62,	63,	64,	65,	66,	67,	68,	69,
			70,	71,	72,	73,	74,	75,	76,	77,	78,	79,
			80,	81,	82,	83,	84,	85,	86,	87,	88,	89,
			90,	91,	92,	93,	94,	32,	15,	9619,	172,	12,
			171,	17,	176,	177,	104,	105,	9496,	9488,	9484,	9492,
			9532,	175,	9472,	9472,	9472,	9472,	9500,	9508,	9524,	9516,
			9474,	8828,	8829,	20,	8800,	163,	183,	127,	128,	129,
			130,	131,	132,	133,	134,	135,	136,	137,	138,	139,
			140,	141,	142,	143,	144,	145,	146,	147,	148,	149,
			150,	151,	152,	153,	154,	155,	156,	157,	158,	159,
			160,	161,	162,	163,	164,	165,	166,	167,	168,	169,
			170,	171,	172,	173,	174,	175,	176,	177,	178,	179,
			180,	181,	182,	183,	184,	185,	186,	187,	188,	189,
			190,	191,	192,	193,	194,	195,	196,	197,	198,	199,
			200,	201,	202,	203,	204,	205,	206,	207,	208,	209,
			210,	211,	212,	213,	214,	215,	216,	217,	218,	219,
			220,	221,	222,	223,	224,	225,	226,	227,	228,	229,
			230,	231,	232,	233,	234,	235,	236,	237,	238,	239,
			240,	241,	242,	243,	244,	245,	246,	247,	248,	249,
			250,	251,	252,	253,	254,	255,
			};

	for(i=0;i<256;i++)
		dwGraphDecodeArray[i]=defVal[i];


	FILE *tmp;
	if ((tmp=fopen("CODECOGRAPH.TXT","rt")))
	{
		char tmpstr[200];
		while(fgets(tmpstr,150,tmp))
			if (*tmpstr>='0' && *tmpstr<='9')
			{
				int idx=0;
				int code=0xFFFF;
				m_LastScanf=sscanf(tmpstr,"%d,%d",&idx,&code);
				if (idx>=0 && idx<256 && code>=0 && code<=0xFFFF)
				{
					GPC.dwGraphDecodeArray[idx]=code;
					ret++;
				}
			}
		fclose(tmp);
	}
	else
	{
		;
	}

	return ret;
}

DWORD GPCurrent::SaveGraphCodeco()
{
	DWORD ret=0;
	FILE *tmp;
	if ((tmp=fopen("CODECOGRAPH.TXT","wt")))
	{
		
		for(ret=0;ret<256;ret++)
			fprintf(tmp,"%d,%d\n",ret,GPC.dwGraphDecodeArray[ret]);
		fclose(tmp);
	}

	return ret;
}

DWORD GPCurrent::SetMBConv3(DWORD dwSrwPC, DWORD dwPCSrv)
{
	if (chWideDosAnsi3) delete[] chWideDosAnsi3;
	chWideDosAnsi3=NULL;
	if (dwSrwPC)
	{
		switch(dwSrwPC)
		{
		case MBC3_MBTOWIDECHAR:
		case MBC3_LCMAPSTRING:
		case MBC3_MBLC:
		case MBC3_LCMB:
			{
/*				chWideDosAnsi3=new char [(0xFE-0xA0)*0x200];
				int i,j;
				char *c=chWideDosAnsi3;
				for (i=0xA1; i<=0xFE; i++)
					for(j=0x00;j<=0xFF;j++)
					{
						*(c++)=i;
						*(c++)=j;
					}
*/			}
			break;

		default: m_CONV3SRVPC.dwType=0;
			break;
		}
	}

	if (chWideAnsiDos3) delete[] chWideAnsiDos3;
	chWideAnsiDos3=NULL;
	if (dwPCSrv)
	{
		switch(dwSrwPC)
		{
		case MBC3_MBTOWIDECHAR:
		case MBC3_LCMAPSTRING:
		case MBC3_MBLC:
		case MBC3_LCMB:
			{
/*				chWideAnsiDos3=new char [(0xFE-0xA0)*0x200];
				int i,j;
				char *c=chWideAnsiDos3;
				for (i=0xA1; i<=0xFE; i++)
					for(j=0x00;j<=0xFF;j++)
					{
						*(c++)=i;
						*(c++)=j;
					}
*/			}
			break;

		default: m_CONV3PCSRV.dwType=0;
			break;
		}
	}
	m_CONV3PCSRV.lng=MAKELCID(MAKELANGID(m_CONV3PCSRV.dwLang,m_CONV3PCSRV.dwSubLang&0xFF),SORT_DEFAULT);
	m_CONV3SRVPC.lng=MAKELCID(MAKELANGID(m_CONV3SRVPC.dwLang,m_CONV3SRVPC.dwSubLang&0xFF),SORT_DEFAULT);

	return m_CONV3SRVPC.dwType+m_CONV3PCSRV.dwType*0x10000;
}

DWORD GPCurrent::GetMBConv3SrwPC()
{
	return m_CONV3SRVPC.dwType;
}

DWORD GPCurrent::GetMBConv3PCSrw()
{
	return m_CONV3PCSRV.dwType;
}


DWORD GPCurrent::MBConv3SrwPC(const char *pcSrc, char *pcDst)
{
	DWORD ret=0;
	*pcDst=*pcSrc;
	pcDst[1]=pcSrc[1];
	if (m_USEMBCONV3 /*&& *pcSrc!=0x7F && pcSrc[1]!=0x7F && (*pcSrc&0xF8) && (pcSrc[1]&0xF8)*/)
	{
		switch(m_CONV3SRVPC.dwType)
		{
		case MBC3_MBTOWIDECHAR:
			{
				unsigned short tmpwstr[10];
				char pppp[]={0x0,0x0,0x0,0x0,0x0,0x0,};
				char ppdd[]={0x0,0x0,0x0,0x0,0x0,0x0,};
				pppp[0]=ppdd[0]=pcSrc[0];
				pppp[1]=ppdd[1]=pcSrc[1];
				if (MultiByteToWideChar(m_CONV3PCSRV.dwCP, 0, pppp, 2, (LPWSTR)tmpwstr, 1) &&
					WideCharToMultiByte(m_CONV3SRVPC.dwCP, 0, (LPWSTR)tmpwstr, 1, ppdd, 2, NULL, FALSE))
				{
					ret=1;
					pcDst[0]=ppdd[0];
					pcDst[1]=ppdd[1];
				}
			}
			break;
		case MBC3_LCMAPSTRING:
			{
				char pppp[]={0x0,0x0,0x0,0x0,0x0,0x0,};
				char ppdd[]={0x0,0x0,0x0,0x0,0x0,0x0,};
				pppp[0]=ppdd[0]=pcSrc[0];
				pppp[1]=ppdd[1]=pcSrc[1];
				if (::LCMapString(m_CONV3SRVPC.lng,m_CONV3SRVPC.dwConv,pppp,2,ppdd,2))
				{
					ret=1;
					pcDst[0]=ppdd[0];
					pcDst[1]=ppdd[1];
				}

			}
			break;

		case MBC3_MBLC:
			{
				unsigned short tmpwstr[10];
				char pppp[]={0x0,0x0,0x0,0x0,0x0,0x0,};
				char ppdd[]={0x0,0x0,0x0,0x0,0x0,0x0,};
				pppp[0]=ppdd[0]=pcSrc[0];
				pppp[1]=ppdd[1]=pcSrc[1];
				if (MultiByteToWideChar(m_CONV3PCSRV.dwCP, 0, pppp, 2, (LPWSTR)tmpwstr, 1) &&
					WideCharToMultiByte(m_CONV3SRVPC.dwCP, 0, (LPWSTR)tmpwstr, 1, pppp, 2, NULL, FALSE) &&
					::LCMapString(m_CONV3SRVPC.lng,m_CONV3SRVPC.dwConv,pppp,2,ppdd,2))
				{
					ret=1;
					pcDst[0]=ppdd[0];
					pcDst[1]=ppdd[1];
				}
			}
			break;
		case MBC3_LCMB:
			{
				char pppp[]={0x0,0x0,0x0,0x0,0x0,0x0,};
				char ppdd[]={0x0,0x0,0x0,0x0,0x0,0x0,};
				pppp[0]=ppdd[0]=pcSrc[0];
				pppp[1]=ppdd[1]=pcSrc[1];

				unsigned short tmpwstr[10];
				if (::LCMapString(m_CONV3SRVPC.lng,m_CONV3SRVPC.dwConv,pppp,2,ppdd,2) &&
					::MultiByteToWideChar(m_CONV3PCSRV.dwCP, 0, ppdd, 2, (LPWSTR)tmpwstr, 1) &&
					::WideCharToMultiByte(m_CONV3SRVPC.dwCP, 0, (LPWSTR)tmpwstr, 1, ppdd, 2, NULL, FALSE))
				{
					ret=1;
					pcDst[0]=ppdd[0];
					pcDst[1]=ppdd[1];
				}

			}
			break;
		}
	}
	return ret;
}

DWORD GPCurrent::MBConv3PCSrw(const char *pcSrc, char *pcDst)
{
	DWORD ret=0;
	*pcDst=*pcSrc;
	pcDst[1]=pcSrc[1];

	if (m_USEMBCONV3/* && *pcSrc!=0x7F && pcSrc[1]!=0x7F && (*pcSrc&0xF8) && (pcSrc[1]&0xF8)*/)
	{
		switch(m_CONV3PCSRV.dwType)
		{
		case MBC3_MBTOWIDECHAR:
			{
				char pppp[]={0x0,0x0,0x0,0x0,0x0,0x0,};
				char ppdd[]={0x0,0x0,0x0,0x0,0x0,0x0,};
				pppp[0]=ppdd[0]=pcSrc[0];
				pppp[1]=ppdd[1]=pcSrc[1];

				unsigned short tmpwstr[10];
				if (MultiByteToWideChar(m_CONV3SRVPC.dwCP, 0, pppp, 2, (LPWSTR)tmpwstr, 1) && 
					WideCharToMultiByte(m_CONV3PCSRV.dwCP, 0, (LPWSTR)tmpwstr, 1, ppdd, 2, NULL, FALSE)) 
					{
						ret=1;
						pcDst[0]=ppdd[0];
						pcDst[1]=ppdd[1];
					}
			}
			break;
		case MBC3_LCMAPSTRING:
			{
				char pppp[]={0x0,0x0,0x0,0x0,0x0,0x0,};
				char ppdd[]={0x0,0x0,0x0,0x0,0x0,0x0,};
				pppp[0]=ppdd[0]=pcSrc[0];
				pppp[1]=ppdd[1]=pcSrc[1];

				if (::LCMapString(m_CONV3PCSRV.lng,m_CONV3PCSRV.dwConv,pppp,2,ppdd,2)) 
				{
					ret=1;
					pcDst[0]=ppdd[0];
					pcDst[1]=ppdd[1];
				}
			}
			break;
		case MBC3_MBLC:
			{
				char pppp[]={0x0,0x0,0x0,0x0,0x0,0x0,};
				char ppdd[]={0x0,0x0,0x0,0x0,0x0,0x0,};
				pppp[0]=ppdd[0]=pcSrc[0];
				pppp[1]=ppdd[1]=pcSrc[1];

				unsigned short tmpwstr[10];
				if (MultiByteToWideChar(m_CONV3SRVPC.dwCP, 0, pppp, 2, (LPWSTR)tmpwstr, 1) && 
					WideCharToMultiByte(m_CONV3PCSRV.dwCP, 0, (LPWSTR)tmpwstr, 1, pppp, 2, NULL, FALSE) &&
					::LCMapString(m_CONV3PCSRV.lng,m_CONV3PCSRV.dwConv,pppp,2,ppdd,2)) 
				{
					ret=1;
					pcDst[0]=ppdd[0];
					pcDst[1]=ppdd[1];
				}
			}
			break;
		case MBC3_LCMB:
			{
				char pppp[]={0x0,0x0,0x0,0x0,0x0,0x0,};
				char ppdd[]={0x0,0x0,0x0,0x0,0x0,0x0,};
				pppp[0]=ppdd[0]=pcSrc[0];
				pppp[1]=ppdd[1]=pcSrc[1];
				unsigned short tmpwstr[10];
				if (::LCMapString(m_CONV3PCSRV.lng,m_CONV3PCSRV.dwConv,pppp,2,ppdd,2) &&
					MultiByteToWideChar(m_CONV3SRVPC.dwCP, 0, ppdd, 2, (LPWSTR)tmpwstr, 1) && 
					WideCharToMultiByte(m_CONV3PCSRV.dwCP, 0, (LPWSTR)tmpwstr, 1, ppdd, 2, NULL, FALSE)) 
				{
					ret=1;
					pcDst[0]=ppdd[0];
					pcDst[1]=ppdd[1];
				}
			}
			break;
		}
	}
	return ret;
}

int GPCurrent::ParseCommandLine(DWORD dwFlags, const char *iCmdLine)
{
	if (*iCmdLine==0) iCmdLine="-INCLUDE=default.cmdline";

	char *tmp=new char [20000];
	strcpy(tmp,iCmdLine);
	strcpy(tmp+10000,tmp);
	_strupr(tmp);
	char *poscl;
	
	while((poscl=strstr(tmp,"-INCLUDE=")) && (int)strlen(tmp)<9500)
	{
		CString newStr;
		*(poscl+10000)=0;
		newStr=tmp+10000;

		CString fname=ExtractField(poscl+10002,2,"\"");
		poscl+=11+fname.GetLength();


		FILE *tmpf=fopen(fname,"rt");
		if (tmpf)
		{
			char tmpfstr[1000];
			while(fgets(tmpfstr,999,tmpf) && newStr.GetLength()<9900)
			{
				char *postmp=tmpfstr+(int)strlen(tmpfstr);
				while(postmp!=tmpfstr && *postmp<=' ') *(postmp--)=0;
				newStr+=tmpfstr;
				newStr+=" ";
			}
			fclose(tmpf);
		}
		newStr+=poscl;
		if (newStr.GetLength()>9990) newStr=newStr.Mid(0,9900);
		strcpy(tmp,newStr);
		strcpy(tmp+10000,tmp);
		_strupr(tmp);
	}


	if ((dwFlags&0x0001))
	{
		if (strstr(tmp,"-HIDE")) GPC.dw_StartFlags|=GP_STRTFLG_HIDE;
	}

	if ((dwFlags&0x0002) && !(dwFlags&0x80000000))
	{

		poscl=strstr(tmp,"-COMMNUM");

		CString tmpCS="";
		try
		{
			tmpCS=AfxGetApp()->GetProfileString(GPC.cs_RegTermViewSetName, "StartComm","2");
		}
		catch(...)
		{
			tmpCS="2";
		}
		if (tmpCS[0]<32)
		{
			tmpCS.Format("%d",AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "StartComm",2));
			AfxGetApp()->WriteProfileString(GPC.cs_RegTermViewSetName, "StartComm",tmpCS);
		}
		if (poscl)
		{
			CString tmpNM=ExtractField(poscl+8,1," ");
			if (tmpNM=="") tmpNM="2";
			m_Comm.Set_comm(tmpNM,0);
		}
		else 
		{
			m_Comm.Set_comm(tmpCS,0);
		}
	}

	if ((dwFlags&0x0004))
	{
		BOOL SectionUpdate=FALSE;
		if ((poscl=strstr(tmp,"-HOST=")))
		{
			SectionUpdate=TRUE;
			m_Comm.GPSetHostName(ExtractField(strchr(poscl+10000,'=')+1,2,"\""));
			if (m_Comm.Get_commType()!=GPCT_SOCKET)	m_Comm.Set_commType(GPCT_SOCKET);
		}
		if ((poscl=strstr(tmp,"-PORT=")))			{SectionUpdate=TRUE;m_Comm.SetPortNumber(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-TELNET="))) 		{SectionUpdate=TRUE;m_Comm.SetTelnetFlag(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-SSH=")))			{SectionUpdate=TRUE;m_Comm.dwUseSSH=atoi(strchr(poscl+10000,'=')+1);}
		if ((poscl=strstr(tmp,"-SSCRIPT="))) 		{SectionUpdate=TRUE;m_Comm.SetInitStr(ExtractField(poscl+10000,2,"\""));}
		if ((poscl=strstr(tmp,"-ESCRIPT=")))		{SectionUpdate=TRUE;m_Comm.SetEndStr(ExtractField(poscl+10000,2,"\""));}
		if ((poscl=strstr(tmp,"-COMMENT="))) 		{SectionUpdate=TRUE;m_Comm.SetComment(ExtractField(poscl+10000,2,"\""));}
		if ((poscl=strstr(tmp,"-DUMP="))) 
		{
			m_Comm.SetDumpMode(atoi(strchr(poscl+10000,'=')+1));
			m_Comm.GPStartDump();
		}

		if ((poscl=strstr(tmp,"-COMPORT="))) 
		{
			SectionUpdate=TRUE;
			m_Comm.SetComport(ExtractField(strchr(poscl+10000,'=')+1,1," "));
			if (m_Comm.Get_commType()!=GPCT_COMPORT)	m_Comm.Set_commType(GPCT_COMPORT);
		}

		if ((poscl=strstr(tmp,"-BAUDRATE="))) {SectionUpdate=TRUE;m_Comm.SetdcbBaudRate(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-FBINARY="))) {SectionUpdate=TRUE;m_Comm.SetdcbfBinary(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-FPARITY="))) {SectionUpdate=TRUE;m_Comm.SetdcbfParity(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-FOUTXCTSFLOW="))) {SectionUpdate=TRUE;m_Comm.SetdcbfOutxCtsFlow(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-FOUTXDSRFLOW="))) {SectionUpdate=TRUE;m_Comm.SetdcbfOutxDsrFlow(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-FERRORCHAR="))) {SectionUpdate=TRUE;m_Comm.SetdcbfErrorChar(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-FDTRCONTROL="))) {SectionUpdate=TRUE;m_Comm.SetdcbfDtrControl(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-FDSRSENSITIVITY="))) {SectionUpdate=TRUE;m_Comm.SetdcbfDsrSensitivity(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-FTXCONTINUEONXOFF="))) {SectionUpdate=TRUE;m_Comm.SetdcbfTXContinueOnXoff(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-FOUTX="))) {SectionUpdate=TRUE;m_Comm.SetdcbfOutX(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-FINX="))) {SectionUpdate=TRUE;m_Comm.SetdcbfInX(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-FNULL="))) {SectionUpdate=TRUE;m_Comm.SetdcbfNull(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-FRTSCONTROL="))) {SectionUpdate=TRUE;m_Comm.SetdcbfRtsControl(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-FABORTONERROR="))) {SectionUpdate=TRUE;m_Comm.SetdcbfAbortOnError(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-XONLIM="))) {SectionUpdate=TRUE;m_Comm.SetdcbXonLim(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-XOFFLIM="))) {SectionUpdate=TRUE;m_Comm.SetdcbXoffLim(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-BYTESIZE="))) {SectionUpdate=TRUE;m_Comm.SetdcbByteSize(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-PARITY="))) {SectionUpdate=TRUE;m_Comm.SetdcbParity(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-STOPBITS="))) {SectionUpdate=TRUE;m_Comm.SetdcbStopBits(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-XONCHAR="))) {SectionUpdate=TRUE;m_Comm.SetdcbXonChar(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-XOFFCHAR="))) {SectionUpdate=TRUE;m_Comm.SetdcbXoffChar(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-ERRORCHAR="))) {SectionUpdate=TRUE;m_Comm.SetdcbErrorChar(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-EOFCHAR="))) {SectionUpdate=TRUE;m_Comm.SetdcbEofChar(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-EVTCHAR="))) {SectionUpdate=TRUE;m_Comm.SetdcbEvtChar(atoi(strchr(poscl+10000,'=')+1));}
		if ((poscl=strstr(tmp,"-CRLF="))) {SectionUpdate=TRUE;CGP_TermView::m_CRLFflag=atoi(strchr(poscl+10000,'=')+1);}
		if ((poscl=strstr(tmp,"-CRCRLF="))) {SectionUpdate=TRUE;CGP_TermView::m_CRLFflag2=atoi(strchr(poscl+10000,'=')+1);}

		if (m_Comm.UniSocket)
		{
			DLL_SSH_Config mcfg=m_Comm.UniSocket->GetConfig();
			BOOL bUpdate=FALSE;

			if ((poscl=strstr(tmp,"-SSH_AGENTFORWARDING="))) {bUpdate=TRUE;mcfg.agentfwd=atoi(strchr(poscl+10000,'=')+1);}
			if ((poscl=strstr(tmp,"-SSH_ALLOWUSERCHANGE="))) {bUpdate=TRUE;mcfg.change_username=atoi(strchr(poscl+10000,'=')+1);}
			//if ((poscl=strstr(tmp,"-SSH_CIPHERS="))) {bUpdate=TRUE;mcfg.=atoi(strchr(poscl+10000,'=')+1);}
			if ((poscl=strstr(tmp,"-SSH_CONFROMOTHERHOSTS="))) {bUpdate=TRUE;mcfg.lport_acceptall=atoi(strchr(poscl+10000,'=')+1);}
			if ((poscl=strstr(tmp,"-SSH_DONTCOMMAND="))) {bUpdate=TRUE;mcfg.ssh_no_shell=atoi(strchr(poscl+10000,'=')+1);}
			if ((poscl=strstr(tmp,"-SSH_DONTPTERMINAL="))) {bUpdate=TRUE;mcfg.nopty=atoi(strchr(poscl+10000,'=')+1);}
			if ((poscl=strstr(tmp,"-SSH_ENABLECOMPRESSION="))) {bUpdate=TRUE;mcfg.compression=atoi(strchr(poscl+10000,'=')+1);}
			if ((poscl=strstr(tmp,"-SSH_FORWARDX11="))) {bUpdate=TRUE;mcfg.x11_forward=atoi(strchr(poscl+10000,'=')+1);}
			//if ((poscl=strstr(tmp,"-SSH_KEXES="))) {bUpdate=TRUE;mcfg.=atoi(strchr(poscl+10000,'=')+1);}
			if ((poscl=strstr(tmp,"-SSH_KEYBOARDAUTO="))) {bUpdate=TRUE;mcfg.try_ki_auth=atoi(strchr(poscl+10000,'=')+1);}
			if ((poscl=strstr(tmp,"-SSH_PROTOCOL="))) {bUpdate=TRUE;mcfg.sshprot=atoi(strchr(poscl+10000,'=')+1);}

			if ((poscl=strstr(tmp,"-SSH_REKEY_DATA=")))
			{
				bUpdate=TRUE;
				DWORD nData=atoi(strchr(poscl+10000,'=')+1);
				if (nData>999)
					sprintf(mcfg.ssh_rekey_data,"%dG",nData/1000);
				else
					sprintf(mcfg.ssh_rekey_data,"%dM",nData);
			}

			if ((poscl=strstr(tmp,"-SSH_REKEY_TIME="))) {bUpdate=TRUE;mcfg.ssh_rekey_time=atoi(strchr(poscl+10000,'=')+1);}
			if ((poscl=strstr(tmp,"-SSH_REMOTEPORTDOSAME="))) {bUpdate=TRUE;mcfg.rport_acceptall=atoi(strchr(poscl+10000,'=')+1);}
			if ((poscl=strstr(tmp,"-SSH_TISAUTH="))) {bUpdate=TRUE;mcfg.try_tis_auth=atoi(strchr(poscl+10000,'=')+1);}
			if ((poscl=strstr(tmp,"-SSH_X11_MIT_XDM="))) {bUpdate=TRUE;mcfg.x11_auth=atoi(strchr(poscl+10000,'=')+1);}
			if ((poscl=strstr(tmp,"-SSH2_DES_CBC="))) {bUpdate=TRUE;mcfg.ssh2_des_cbc=atoi(strchr(poscl+10000,'=')+1);}


			if ((poscl=strstr(tmp,"-SSH_EDITPRIVATEKEYFILE="))) {bUpdate=TRUE;strcpy(mcfg.keyfile.path,ExtractField(poscl+10000,2,"\""));}
			if ((poscl=strstr(tmp,"-SSH_EDITREMOTECOMMAND="))) {bUpdate=TRUE;strcpy(mcfg.remote_cmd,ExtractField(poscl+10000,2,"\""));}
			if ((poscl=strstr(tmp,"-SSH_EDITXLOCATION="))) {bUpdate=TRUE;strcpy(mcfg.x11_display,ExtractField(poscl+10000,2,"\""));}
			//if ((poscl=strstr(tmp,"-SSH_FORWARDPORTS="))) {bUpdate=TRUE;strcpy(mcfg.,ExtractField(poscl+10000,2,"\""));}
			if (bUpdate)
			{
				m_Comm.UniSocket->SetConfig(mcfg);
				SectionUpdate=TRUE;
			}
		}
		if (SectionUpdate) m_Comm.GPSectionName="temporary";

	}

	if ((dwFlags&0x0008))
	{
		poscl=strstr(tmp,"-LISTEN");
		if (poscl)
		{
			m_Comm.m_ConnectionFlag=0x1;
			UINT port=atoi(poscl+7);
			if (port) m_Comm.ListenPort=port;
		}
		else 
			m_Comm.m_ConnectionFlag=0;

		poscl=strstr(tmp,"-LTIME");
		if (poscl)
		{
			UINT utm=atoi(*(poscl+6)=='='?poscl+7:poscl+6);
			if (utm) m_Comm.ListenTime=utm;
		}
	}

	if ((dwFlags&0x0010))
	{
		if ((poscl=strstr(tmp,"-REGTERM")))
		{
			char *tmpsrc=new char [1000];
			strncpy(tmpsrc,poscl+10000+8,900);tmpsrc[900]=0;
			poscl=strchr(tmpsrc,' ');
			if (poscl) *poscl=0;
			m_Document->RegisterGPTermInROT(tmpsrc);
			delete[] tmpsrc;
		}
	}

	if ((dwFlags&0x0020))
	{
		if ((poscl=strstr(tmp,"-ADMMODE=")))
		{
			if (AdmIsOn!=atoi(strchr(poscl+10000,'=')+1))
			{
				AdmIsOn=atoi(strchr(poscl+10000,'=')+1);
				GPC.m_View->m_GPMenu->Fill_mArrMenu(FALSE);
			}
		}
		if ((poscl=strstr(tmp,"-LOGINDLG=")))
		{
			dw_LoginDialogFlags_temporary=atoi(poscl+10);
			if (!(dwFlags&0x000E))
			{
				cs_ScriptLine+="\\l"; 
				if ((dwFlags&0x10000000)) m_View->DoScriptCommand();
			}
			else
			{
				CString csTmp=m_Comm.GetInitStr();
				csTmp+="\\l";
				m_Comm.SetInitStr(csTmp);
				dw_StartFlags|=GP_STRTFLG_SHOWLOGINDIALOG;
			}
		}
	}

	if ((dwFlags&0x0040))
	{
		if ((poscl=strstr(tmp,"-DUMPMODE="))) m_Comm.SetDumpMode(atoi(strchr(poscl+10000,'=')+1));/*		#define GPC_DUMPOUTBLOCK	0x00000001*/
		if ((poscl=strstr(tmp,"-DUMPMAXCHAR="))) m_Comm.maxnCharDump=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-DUMPMAXLINE="))) m_Comm.maxnLineDump=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-DUMPPREFIX="))) m_Comm.m_DumpPrefix=ExtractField(poscl+10000,2,"\"");
		if ((poscl=strstr(tmp,"-DUMPFILENAME="))) 
			m_Comm.SetDumpFileName(ExtractField(poscl+10000,2,"\""));
		if ((poscl=strstr(tmp,"-DUMPONOFF="))) 
			switch(atoi(strchr(poscl+10000,'=')+1))
			{
			case 0:
				m_Comm.GPStopDump();
				break;
			case 2:
				m_Comm.GPContinueDump();
				break;
			default:
				m_Comm.GPStartDump(); 
				break;
			}

		if ((poscl=strstr(tmp,"-DUMPERRONOFF="))) 
			if (atoi(strchr(poscl+10000,'=')+1)) m_Comm.StartErrorLog(); else m_Comm.EndErrorLog();
	}


	if ((dwFlags&0x1000))
	{
		if ((poscl=strstr(tmp,"-DASBLOCK="))) m_Comm.SetDelayAfterSendBlock(atoi(strchr(poscl+10000,'=')+1));
		if ((poscl=strstr(tmp,"-DASCHAR="))) m_Comm.SetDelayAfterSendChar(atoi(strchr(poscl+10000,'=')+1));
		if ((poscl=strstr(tmp,"-DASLINE="))) m_Comm.SetDelayAfterSendLine(atoi(strchr(poscl+10000,'=')+1));
		if ((poscl=strstr(tmp,"-DBSBLOCK="))) m_Comm.SetDelayBeforeSendBlock(atoi(strchr(poscl+10000,'=')+1));
		if ((poscl=strstr(tmp,"-DBSCHAR="))) m_Comm.SetDelayBeforeSendChar(atoi(strchr(poscl+10000,'=')+1));
		if ((poscl=strstr(tmp,"-DBSLINE="))) m_Comm.SetDelayBeforeSendLine(atoi(strchr(poscl+10000,'=')+1));

		if ((poscl=strstr(tmp,"-DELIMITERIN1="))) m_Comm.DelimiterIn1=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-DELIMITERIN2="))) m_Comm.DelimiterIn2=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-DELIMITERIN3="))) m_Comm.DelimiterIn3=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-DELIMITERIN4="))) m_Comm.DelimiterIn4=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-DELIMITERIN5="))) m_Comm.DelimiterIn5=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-DELIMITERIN6="))) m_Comm.DelimiterIn6=atoi(strchr(poscl+10000,'=')+1);

		if ((poscl=strstr(tmp,"-DELIMITEROUT1="))) m_Comm.DelimiterSrc1=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-DELIMITEROUT2="))) m_Comm.DelimiterSrc2=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-DELIMITEROUT3="))) m_Comm.DelimiterSrc3=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-DELIMITEROUT4="))) m_Comm.DelimiterSrc4=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-DELIMITEROUT5="))) m_Comm.DelimiterSrc5=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-DELIMITEROUT6="))) m_Comm.DelimiterSrc6=atoi(strchr(poscl+10000,'=')+1);

		if ((poscl=strstr(tmp,"-EVENTSECHO="))) m_Comm.SetLockEventsEcho(atoi(strchr(poscl+10000,'=')+1));
		if ((poscl=strstr(tmp,"-MAXNCOMBLOCK="))) m_Comm.SetmaxBLOCK(atoi(strchr(poscl+10000,'=')+1));
	}

	if ((dwFlags&0x2000))
	{
		if ((poscl=strstr(tmp,"-ED_MAGNIFICATION="))) GPScintilla::EditorPrintSettings.m_Magnification=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-ED_LINENUMBER="))) GPScintilla::EditorPrintSettings.m_PrintLineNumber=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-ED_FOOTER="))) GPScintilla::EditorPrintSettings.m_UseFooter=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-ED_HEADER="))) GPScintilla::EditorPrintSettings.m_UseHeader=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-ED_SELECTION="))) GPScintilla::EditorPrintSettings.m_UseSelection=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-ED_WORDWRAP="))) GPScintilla::EditorPrintSettings.m_UseWordWrap=atoi(strchr(poscl+10000,'=')+1);

		if ((poscl=strstr(tmp,"-ED_FOOTERFORMAT="))) GPScintilla::EditorPrintSettings.csfooterFormat=ExtractField(poscl+10000,2,"\"");
		if ((poscl=strstr(tmp,"-ED_FOOTERSTYLE="))) GPScintilla::EditorPrintSettings.SetFooterStyle(ExtractField(poscl+10000,2,"\""));
		if ((poscl=strstr(tmp,"-ED_HEADERFORMAT="))) GPScintilla::EditorPrintSettings.csheaderFormat=ExtractField(poscl+10000,2,"\"");
		if ((poscl=strstr(tmp,"-ED_HEADERSTYLE="))) GPScintilla::EditorPrintSettings.SetHeaderStyle(ExtractField(poscl+10000,2,"\""));
	}

	if ((dwFlags&0x4000))
	{
		if ((poscl=strstr(tmp,"-GUI_USEDEFAULT="))) m_GUISet.UseDefault=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-GUI_ITALIC="))) m_GUISet.Italic=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-GUI_CHARSET="))) m_GUISet.CharSet=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-GUI_POINTSIZE="))) m_GUISet.PointSize=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-GUI_SCALE="))) m_GUISet.Scale=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-GUI_WEIGHT="))) m_GUISet.Weight=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-GUI_FONTNAME="))) m_GUISet.FontName=ExtractField(poscl+10000,2,"\"");
	}

	if ((dwFlags&0x4000))
	{
		if ((poscl=strstr(tmp,"-OLE_CNTFOTHER=")))   m_OLESETTINGS.m_CFOther        =atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-OLE_CNTFREAD=")))    m_OLESETTINGS.m_CFRead         =atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-OLE_CNTFWRITE=")))   m_OLESETTINGS.m_CFWrite        =atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-OLE_CNTINPUT=")))    m_OLESETTINGS.m_CInput         =atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-OLE_CNTMM=")))       m_OLESETTINGS.m_CMM            =atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-OLE_CNTSUB=")))      m_OLESETTINGS.m_CSUB           =atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-OLE_CNTSYSTEM=")))   m_OLESETTINGS.m_CSystem        =atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-OLE_CNTTCL=")))      m_OLESETTINGS.m_CTCL           =atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-OLE_WAITFOTHER=")))  m_OLESETTINGS.m_WFOther        =atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-OLE_WAITFREAD=")))   m_OLESETTINGS.m_WFRead         =atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-OLE_WAITFWRITE=")))  m_OLESETTINGS.m_WFWrite        =atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-OLE_WAITINPUT=")))   m_OLESETTINGS.m_WInput         =atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-OLE_WAITMM=")))      m_OLESETTINGS.m_WMM            =atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-OLE_WAITSUB=")))     m_OLESETTINGS.m_WSUB           =atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-OLE_WAITSYSTEM=")))  m_OLESETTINGS.m_WSystem        =atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-OLE_WAITTCL=")))     m_OLESETTINGS.m_WTCL           =atoi(strchr(poscl+10000,'=')+1);
	}
/*
	if ((dwFlags&0x8000))
	{
		if ((poscl=strstr(tmp,"SVI_-=")))   m_OLESETTINGS.m_CFOther        =atoi(strchr(poscl+10000,'=')+1);
		WriteProfileInt("SEP_INPUT_SET","INDENTSIZE",m_dwIndentSize);
		WriteProfileInt("SEP_INPUT_SET","INPUT_SET",m_dwInputSet);
		WriteProfileInt("SEP_INPUT_SET","m_CurLexer",m_CurLexer);
		WriteProfileInt("SEP_INPUT_SET","TABSIZE",m_dwTabSize);
		WriteProfileInt("SEP_OUTPUT_SET","CHARFILTER",m_dwLowSymbolMask);
		WriteProfileInt("SEP_OUTPUT_SET","HEIGHT_SET",m_Height);
		WriteProfileInt("SEP_OUTPUT_SET","INDENTSIZE",m_dwIndentSize);
		WriteProfileInt("SEP_OUTPUT_SET","KEY_BREAK",*m_dwKeyBreak);
		WriteProfileInt("SEP_OUTPUT_SET","KEY_EXECUTE",*m_dwKeyExecute);
		WriteProfileInt("SEP_OUTPUT_SET","KEY_SOFTBREAK",*m_dwKeySoftBreak);
		WriteProfileInt("SEP_OUTPUT_SET","m_CurLexer",m_CurLexer);
		WriteProfileInt("SEP_OUTPUT_SET","m_nMaxOutputLen",tmp);
		WriteProfileInt("SEP_OUTPUT_SET","m_nOutputLenDecr",tmp);
		WriteProfileInt("SEP_OUTPUT_SET","m_ViewMode",m_ViewMode);
		WriteProfileInt("SEP_OUTPUT_SET","m_ViewMode",m_ViewMode);
		WriteProfileInt("SEP_OUTPUT_SET","OUTPUT_SET",m_dwOutputSet);
		WriteProfileInt("SEP_OUTPUT_SET","TABSIZE",m_dwTabSize);
		WriteProfileString("SEP_OUTPUT_SET","KEY_SOFTBREAKSEQ",*m_csSoftBreakSeq);
		WriteProfileString("SEP_OUTPUT_SET","m_csDefClFileName",m_Editor->m_csDefClFileName);
		WriteProfileString("SEP_OUTPUT_SET","m_csDefSrvFileName",m_Editor->m_csDefSrvFileName);
		WriteProfileString("SEP_OUTPUT_SET","m_csDefSrvItemName",m_Editor->m_csDefSrvItemName);
	}
*/
	if ((dwFlags&0x10000))
	{
		if ((poscl=strstr(tmp,"-SHUTDOWNDISABLE=")))
		{
			DWORD dwCurrent=AfxGetApp()->GetProfileInt(m_Comm.GPSectionName,"m_ShutdownFlags",0x1000);
			dwCurrent=(dwCurrent&(0xFFFFFFFF^0x1000))|(atoi(strchr(poscl+10000,'=')+1)?0x1000:0);
			AfxGetApp()->WriteProfileInt(m_Comm.GPSectionName,"m_ShutdownFlags",dwCurrent);
		}
		if ((poscl=strstr(tmp,"-SHUTDOWNFLAGS=")))
		{
			DWORD dwCurrent=AfxGetApp()->GetProfileInt(m_Comm.GPSectionName,"m_ShutdownFlags",0x1000);
			DWORD tmpInt=atoi(strchr(poscl+10000,'=')+1)?0x1000:0;
			dwCurrent=(dwCurrent&0xFFFFF001)|((tmpInt%4)*0x10+(tmpInt/4)*0x100)|0x1;
			AfxGetApp()->WriteProfileInt(m_Comm.GPSectionName,"m_ShutdownFlags",dwCurrent);
		}

		if ((poscl=strstr(tmp,"-TERMCAPFILE=")))
		{
			strncpy(TermCapFileName,ExtractField(poscl+10000,2,"\""),250);
			TermCapFileName[250]=0;
			m_TermCap.Load(TermCapFileName);
		}

		if ((poscl=strstr(tmp,"-EMU=")))
		{
			m_TermCap.SetCurrentTerminalId(m_TermCap.GetTerminalIdByName(ExtractField(strchr(poscl+10000,'=')+1,2,"\"")));
			AfxGetMainWnd()->SendMessage(GPM_MFUPDATEBARS,1);
		}

		if ((poscl=strstr(tmp,"-BKG=")))     
		{
			m_LastScanf=sscanf(strchr(poscl+10000,'=')+1,"%x",&DefBkgColor);
			if (m_Document) m_Document->GetActiveScreen()->SetBkgColor(DefBkgColor,0);

		}
		if ((poscl=strstr(tmp,"-FRG=")))
		{
			m_LastScanf=sscanf(strchr(poscl+10000,'=')+1,"%x",&DefFrgColor);
			if (m_Document) m_Document->GetActiveScreen()->SetChrColor(DefFrgColor,0);
		}
		if ((poscl=strstr(tmp,"-FRGPAL=")))
			m_LastScanf=sscanf(strchr(poscl+10000,'=')+1,"%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x",cFEtalon,cFEtalon+1,cFEtalon+2,cFEtalon+3,cFEtalon+4,cFEtalon+5,cFEtalon+6,cFEtalon+7,cFEtalon+8,cFEtalon+9,cFEtalon+10,cFEtalon+11,cFEtalon+12,cFEtalon+13,cFEtalon+14,cFEtalon+15);
		if ((poscl=strstr(tmp,"-BKGPAL=")))
		{
			m_LastScanf=sscanf(strchr(poscl+10000,'=')+1,"%x,%x,%x,%x,%x,%x,%x,%x",cBEtalon,cBEtalon+1,cBEtalon+2,cBEtalon+3,cBEtalon+4,cBEtalon+5,cBEtalon+6,cBEtalon+7);
			int i;
			for(i=8;i<16;i++)
				cBEtalon[i]=cFEtalon[i];
		}

		if ((poscl=strstr(tmp,"-CMFILE=")))
		{
			strncpy(contmenuFileName,ExtractField(poscl+10000,2,"\""),250);
			contmenuFileName[250]=0;
			if (!m_pContextMenu && m_View && m_View->m_GPMenu) m_pContextMenu=new CGPContextMenu(m_View->m_GPMenu);
			if (m_pContextMenu) m_pContextMenu->Load(contmenuFileName);
		}

		if ((poscl=strstr(tmp,"-ALTKEY="))) m_dwAltFlag=atoi(strchr(poscl+10000,'=')+1);

		if ((poscl=strstr(tmp,"-BREAKCHAR="))) BreakChar=atoi(strchr(poscl+10000,'=')+1);

		if ((poscl=strstr(tmp,"-ENABLECM="))) CGP_TermView::m_UseContextMenu=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-CURSORDELAY="))) CGP_TermView::CursorTimerDelay=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-KEYBLOCKDELAY="))) CGP_TermView::KeybLockDelay=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-KEYBBUFF="))) CGP_TermView::FlagBufferKeb=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-BEEPFLAG="))) CGP_TermView::BeepFlag=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-MAXIDLE="))) CGP_TermView::m_MaxIdle=atoi(strchr(poscl+10000,'=')+1);

		if ((poscl=strstr(tmp,"-CHECKEXIT="))) AfxGetApp()->WriteProfileInt(cs_RegTermViewSetName,"m_CheckExit",atoi(strchr(poscl+10000,'=')+1));
		if ((poscl=strstr(tmp,"-CHECKEXITPRG="))) AfxGetApp()->WriteProfileInt(cs_RegTermViewSetName,"m_CheckExitPrg",atoi(strchr(poscl+10000,'=')+1));
		if ((poscl=strstr(tmp,"-STERMENABLE="))) AfxGetApp()->WriteProfileInt(cs_RegTermViewSetName,"STERMENABLE",atoi(strchr(poscl+10000,'=')+1));
		if ((poscl=strstr(tmp,"-STERMWARNING="))) AfxGetApp()->WriteProfileInt(cs_RegTermViewSetName,"STERMWARNING",atoi(strchr(poscl+10000,'=')+1));
		if ((poscl=strstr(tmp,"-INITDELAY="))) AfxGetApp()->WriteProfileInt(cs_RegTermViewSetName,"InitDelay",atoi(strchr(poscl+10000,'=')+1));

		if ((poscl=strstr(tmp,"-BARVISIBLE="))) 
		{
			m_BarVisibleFlag=atoi(strchr(poscl+10000,'=')+1);
			AfxGetMainWnd()->SendMessage(GPM_MFUPDATEBARS);
		}

		if ((poscl=strstr(tmp,"-NCOLS=")) || (poscl=strstr(tmp,"-NROWS=")))
		{
			Size newsize=m_Document->GetActiveScrSize();
			if ((poscl=strstr(tmp,"-NCOLS="))) newsize.Width=atoi(strchr(poscl+10000,'=')+1);
			if ((poscl=strstr(tmp,"-NROWS="))) newsize.Height=atoi(strchr(poscl+10000,'=')+1);
			m_Document->ResizeActiveScr(newsize);
		}

		if ((poscl=strstr(tmp,"-TERMDEFTITLE=")))
		{
			termCaptionInit=termCaption=ExtractField(poscl+10000,2,"\"");
			m_Document->SetTitle(termCaption);
		}

		if ((poscl=strstr(tmp,"-TERMTITLE=")))
		{
			termCaption=ExtractField(poscl+10000,2,"\"");
			m_Document->SetTitle(termCaption);
		}

		if ((poscl=strstr(tmp,"-ERRBOXDEFTITLE=")))			ErrBoxCaptionInit=ErrBoxCaption=ExtractField(poscl+10000,2,"\"");
		if ((poscl=strstr(tmp,"-ERRBOXTITLE=")))			ErrBoxCaption=ExtractField(poscl+10000,2,"\"");
		if ((poscl=strstr(tmp,"-MSGBOXDEFTITLE=")))			MsgBoxCaptionInit=MsgBoxCaption=ExtractField(poscl+10000,2,"\"");
		if ((poscl=strstr(tmp,"-MSGBOXTITLE=")))			MsgBoxCaption=ExtractField(poscl+10000,2,"\"");
	}
	if ((dwFlags&0x40000))
	{
		BOOL doUpdate=FALSE;
		if ((poscl=strstr(tmp,"-FONTNAME=")))			
		{
			doUpdate=TRUE;
			MultiByteToWideChar(CP_ACP, 0,ExtractField(poscl+10000,2,"\""), -1,  FontTable.familyName, 200);
		}
		
		#ifdef RUS
			DWORD cset=AfxGetApp()->GetProfileInt(cs_RegTermViewSetName, "m_CurFontCharSet",RUSSIAN_CHARSET);
		#else
			DWORD cset=AfxGetApp()->GetProfileInt(cs_RegTermViewSetName, "m_CurFontCharSet",DEFAULT_CHARSET);
		#endif

		if ((poscl=strstr(tmp,"-CURFONTCHARSET="))) {cset=atoi(strchr(poscl+10000,'=')+1);doUpdate=TRUE;}
		if (doUpdate)
		{
			FontTable.InitFontTable(FontTable.familyName,m_Document?m_Document->GetActiveScreen():NULL);
			PrintFontTable.InitFontTable(FontTable.familyName,m_Document?m_Document->GetActiveScreen():NULL);
		}

		if ((poscl=strstr(tmp,"-CURCODEPAGE=")))		m_CurCodePage=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-LOCALESTR=")))	
		{
			csLocaleStr=ExtractField(poscl+10000,2,"\"");
			setlocale( LC_ALL, GPC.csLocaleStr );
		}

		if ((poscl=strstr(tmp,"-MBCONV=")))					m_USEMBCONV				=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-MBCONV2=")))				m_USEMBCONV2			=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-MBCONV3=")))				m_USEMBCONV3			=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-MBCONV3PCSRV=")))			m_CONV3PCSRV.dwType		=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-MBCONV3PCSRV_CONV=")))		m_CONV3PCSRV.dwConv		=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-MBCONV3PCSRV_CP=")))		m_CONV3PCSRV.dwCP		=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-MBCONV3PCSRV_LANG=")))		m_CONV3PCSRV.dwLang		=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-MBCONV3PCSRV_SUBLANG=")))	m_CONV3PCSRV.dwSubLang	=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-MBCONV3SRVPC=")))			m_CONV3SRVPC.dwType		=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-MBCONV3SRVPC_CONV=")))		m_CONV3SRVPC.dwConv		=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-MBCONV3SRVPC_CP=")))		m_CONV3SRVPC.dwCP		=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-MBCONV3SRVPC_LANG=")))		m_CONV3SRVPC.dwLang		=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-MBCONV3SRVPC_SUBLANG=")))	m_CONV3SRVPC.dwSubLang	=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-WIDEON2POS=")))				m_WideOn2Pos			=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-MBSWAP=")))					m_CurMBInvert			=atoi(strchr(poscl+10000,'=')+1);

		if ((poscl=strstr(tmp,"-SCRCQ=")))					m_CompositingQuality	=(CompositingQuality)atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-SCRIM=")))					m_InterpolationMode		=(InterpolationMode	)atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-SCRPOM=")))					m_PixelOffsetMode		=(PixelOffsetMode	)atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-SCRSM=")))					m_SmoothingMode			=(SmoothingMode		)atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-SCRTC=")))					m_TextContrast			=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-SCRTRH=")))					m_TextRenderingHint		=(TextRenderingHint	)atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-SCRLANG=")))				m_Language				=atoi(strchr(poscl+10000,'=')+1);
		if ((poscl=strstr(tmp,"-SCRSUBLANG=")))				m_SubLanguage			=atoi(strchr(poscl+10000,'=')+1);

		if ((poscl=strstr(tmp,"-PPP=")))					m_uPixelPerPoint		=atoi(strchr(poscl+10000,'=')+1);

		BOOL bScrUpdate=FALSE;
		GPScreen *s=NULL;
		if (m_Document) s=m_Document->GetActiveScreen();
		if ((poscl=strstr(tmp,"-PAGELM=")))
		{
			GPScreen::ScrLeftPageMargin=(REAL)atof(strchr(poscl+10000,'=')+1);
			if (s) s->LeftPageMargin=GPScreen::ScrLeftPageMargin;
		}
		if ((poscl=strstr(tmp,"-PAGERM=")))
		{
			GPScreen::ScrRightPageMargin=(REAL)atof(strchr(poscl+10000,'=')+1);
			if (s) s->RightPageMargin=GPScreen::ScrRightPageMargin;
		}
		if ((poscl=strstr(tmp,"-PAGETM=")))
		{
			GPScreen::ScrTopPageMargin=(REAL)atof(strchr(poscl+10000,'=')+1);
			if (s) s->TopPageMargin=GPScreen::ScrTopPageMargin;
		}
		if ((poscl=strstr(tmp,"-PAGEBM=")))
		{
			GPScreen::ScrBottomPageMargin=(REAL)atof(strchr(poscl+10000,'=')+1);
			if (s) s->BottomPageMargin=GPScreen::ScrBottomPageMargin;
		}

		if ((poscl=strstr(tmp,"-SCALEXY=")))
		{
			bScrUpdate=TRUE;
			GPScreen::ScrScaleHeightToWidth=(REAL)atof(strchr(poscl+10000,'=')+1);
			if (s) s->ScaleHeightToWidth=GPScreen::ScrScaleHeightToWidth;
		}

		if ((poscl=strstr(tmp,"-PRINTBORDERS=")))
		{
			GPScreen::ScrPrintBorders=atoi(strchr(poscl+10000,'=')+1);
			if (s) s->PrintBorders=GPScreen::ScrPrintBorders;
		}

		if ((poscl=strstr(tmp,"-PRINTINVERT=")))
		{
			GPScreen::ScrPrintInvert=atoi(strchr(poscl+10000,'=')+1);
			if (s) s->PrintInvert=GPScreen::ScrPrintInvert;
		}

		if ((poscl=strstr(tmp,"-SCRLBORDER=")))
		{
			bScrUpdate=TRUE;
			GPScreen::ScrLeftBorder=(REAL)atof(strchr(poscl+10000,'=')+1);
			if (s) s->LeftBorderC=s->LeftBorderSafe=GPScreen::ScrLeftBorder;
		}
		if ((poscl=strstr(tmp,"-SCRRBORDER=")))
		{
			bScrUpdate=TRUE;
			GPScreen::ScrRightBorder=(REAL)atof(strchr(poscl+10000,'=')+1);
			if (s) s->RightBorderC=s->RightBorderSafe=GPScreen::ScrRightBorder;
		}
		if ((poscl=strstr(tmp,"-SCRTBORDER=")))
		{
			bScrUpdate=TRUE;
			GPScreen::ScrTopBorder=(REAL)atof(strchr(poscl+10000,'=')+1);
			if (s) s->TopBorderC=s->TopBorderSafe=GPScreen::ScrTopBorder;
		}
		if ((poscl=strstr(tmp,"-SCRBBORDER=")))
		{
			bScrUpdate=TRUE;
			GPScreen::ScrBottomBorder=(REAL)atof(strchr(poscl+10000,'=')+1);
			if (s) s->BottomBorderC=s->BottomBorderSafe=GPScreen::ScrBottomBorder;
		}
		if ((poscl=strstr(tmp,"-SCRFONTDX=")))
		{
			bScrUpdate=TRUE;
			GPScreen::ScrFontDeltaX=(REAL)atof(strchr(poscl+10000,'=')+1);
			if (s) s->FontDeltaX=GPScreen::ScrFontDeltaX;
		}
		if ((poscl=strstr(tmp,"-SCRFONTDY=")))
		{
			bScrUpdate=TRUE;
			GPScreen::ScrFontDeltaY=(REAL)atof(strchr(poscl+10000,'=')+1);
			if (s) s->FontDeltaY=GPScreen::ScrFontDeltaY;
		}
		if ((poscl=strstr(tmp,"-SCRFONTOX=")))
		{
			bScrUpdate=TRUE;
			GPScreen::ScrFontOfsetX=(REAL)atof(strchr(poscl+10000,'=')+1);
			if (s) s->FontOfsetX=GPScreen::ScrFontOfsetX;
		}
		if ((poscl=strstr(tmp,"-SCRFONTOY=")))
		{
			bScrUpdate=TRUE;
			GPScreen::ScrFontOfsetY=(REAL)atof(strchr(poscl+10000,'=')+1);
			if (s) s->FontOfsetY=GPScreen::ScrFontOfsetY;
		}
		if (s && bScrUpdate && GPC.m_hViewWnd)
		{
			RECT re;
			::GetClientRect(GPC.m_hViewWnd,&re);
			s->SetViewSize(re.right-re.left+1,re.bottom-re.top+1);
		}
	}

	if ((dwFlags&0x80000))
	{
		if ((poscl=strstr(tmp,"-PRINTDLG=")))			AfxGetApp()->WriteProfileInt(cs_RegTermViewSetName,"m_PrintDlg",atoi(strchr(poscl+10000,'=')+1));
		if ((poscl=strstr(tmp,"-SLAVEPRINT=")))			AfxGetApp()->WriteProfileInt(cs_RegTermViewSetName,"SLAVEPRINT",atoi(strchr(poscl+10000,'=')+1));
		if ((poscl=strstr(tmp,"-SLAVEPRINTCHARVIEW="))) AfxGetApp()->WriteProfileInt(cs_RegTermViewSetName,"SLAVEPRINTCHARVIEW",atoi(strchr(poscl+10000,'=')+1));
		if ((poscl=strstr(tmp,"-SLAVEPRINTASTXT=")))	AfxGetApp()->WriteProfileInt(cs_RegTermViewSetName,"PRINTASTXT",atoi(strchr(poscl+10000,'=')+1));
	}
	if ((dwFlags&0x100000))
	{
		if ((poscl=strstr(tmp,"-CMDLINE=")))
		{
			CString tmpCS=AfxGetApp()->GetProfileString(m_Comm.GPSectionName,"CMDLINE","");
			if (tmpCS!="") GPC.ParseCommandLine(0xFFFFFFFF,tmpCS);
		}
	}
	if ((dwFlags&0x200000))
	{
	}
	if ((dwFlags&0x400000))
	{
	}
	if ((dwFlags&0x800000))
	{
	}


	delete [] tmp;

	return 0;
}
