// GP_TermView.cpp : implementation of the CGP_TermView class
//

#include "stdafx.h"
#include "GP_Term.h"
#include "math.h"

#include "GP_TermDoc.h"
#include "CntrItem.h"
#include "GP_TermView.h"
#include "Dlg_OLESet.h"
#include "DlgMethods.h"
#include "GPToolTipCtrl.h"
#include "GP_RTF.h"
#include "GPContextMenu.h"
#include "DlgContextMenu.h"
#include "DlgFontSet.h"
#include "DlgGUISet.h"
#include "DlgNewSession.h"
#include "DldTermcapVideo.h"
#include "DlgLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGP_TermView

GPFont FontTable,PrintFontTable;

typedef struct _FINDWNDBYPROC
{
	DWORD dwProcID;
	HWND hwReturn;
	DWORD dwRetStyle;
	BOOL ret;
} FINDWNDBYPROC, *PFINDWNDBYPROC;


BOOL CGP_TermView::BeepFlag;
BOOL CGP_TermView::FlagBufferKeb;
BOOL CGP_TermView::m_CRLFflag;
BOOL CGP_TermView::m_CRLFflag2;
BOOL CGP_TermView::m_TCLvisible=TRUE;
BOOL CGP_TermView::SlaveVisible;
DWORD CGP_TermView::m_UseContextMenu;
int CGP_TermView::m_ListenTime;
UINT CGP_TermView::CursorTimerDelay=200;
UINT CGP_TermView::KeybBufferSize;
UINT CGP_TermView::LockRemappingFlag;
UINT CGP_TermView::m_HIDEVIEWMODE;
UINT CGP_TermView::m_MaxIdle;
UINT CGP_TermView::m_PrintTransp;
UINT CGP_TermView::m_uLockBeep;
UINT CGP_TermView::m_ViewMode=GPVIEWMODE_TERMINAL;
UINT CGP_TermView::PrintLiningStyle;
UINT CGP_TermView::KeybLockDelay;

IMPLEMENT_DYNCREATE(CGP_TermView, CFormView)

BEGIN_MESSAGE_MAP(CGP_TermView, CFormView)
	//{{AFX_MSG_MAP(CGP_TermView)
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_CHAR()
	ON_WM_ERASEBKGND()
	ON_WM_HELPINFO()
	ON_COMMAND(ID_COMSETTINGSDLG, OnComsettingsdlg)
	ON_COMMAND(KEYALTF1, OnKEYALTF1)
	ON_COMMAND(KEYALTF10, OnKEYALTF10)
	ON_COMMAND(KEYALTF11, OnKEYALTF11)
	ON_COMMAND(KEYALTF12, OnKEYALTF12)
	ON_COMMAND(KEYALTF2, OnKEYALTF2)
	ON_COMMAND(KEYALTF3, OnKEYALTF3)
	ON_COMMAND(KEYALTF5, OnKEYALTF5)
	ON_COMMAND(KEYALTF6, OnKEYALTF6)
	ON_COMMAND(KEYALTF7, OnKEYALTF7)
	ON_COMMAND(KEYALTF9, OnKEYALTF9)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDBLCLK()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_KEYBLOCK, OnKeyblock)
	ON_COMMAND(ID_TRANSLATE_TCL, OnTranslateTcl)
	ON_COMMAND(ID_DEFCOLOR, OnDefcolor)
	ON_COMMAND(ID_BUTTONCALC, OnButtoncalc)
	ON_COMMAND(ID_COLORDLG127, OnColordlg127)
	ON_COMMAND(ID_STARTNEWSESSION, OnStartNewSession)
	ON_UPDATE_COMMAND_UI(ID_STARTNEWSESSION , OnUpdateStartNewSession)
	ON_COMMAND(ID_SENTINITSTR, OnSentinitstr)
	ON_COMMAND(ID_MENUADM, OnMenuadm)
	ON_UPDATE_COMMAND_UI(ID_MENUADM , OnUpdateOnMenuadm)
	ON_COMMAND(ID_ALT_B, OnAltBCom)
	ON_UPDATE_COMMAND_UI(ID_ALT_B, OnUpdateAltBCom)
	ON_COMMAND(KEYB_ALTB, OnAltb)
	ON_COMMAND(ID_TERM_SETTINGS, OnTermSettings)
	ON_COMMAND(ID_TERM_FONT_LOCAL_SETTINGS, OnFontLocaleSettings)
	ON_COMMAND(ID_TERM_GUI_SETTINGS, OnGUISettings)
	ON_COMMAND(ID_RECONNECT, OnReconnect)
	ON_UPDATE_COMMAND_UI(ID_RECONNECT, OnUpdateReconnect)
	ON_UPDATE_COMMAND_UI(ID_TERM_SETTINGS, OnUpdateReconnect)
	ON_UPDATE_COMMAND_UI(ID_COMSETTINGSDLG, OnUpdateReconnect)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_CLSSCR, OnClsscr)
	ON_COMMAND(ID_REMOVEALLMENU, OnRemoveallmenu)
	ON_COMMAND(ID_REMOVEALLOBJ, OnRemoveallobj)
	ON_COMMAND(ID_DUMPCLEAR, OnDumpclear)
	ON_COMMAND(ID_DUMPPREVIEW, OnDumppreview)
	ON_COMMAND(ID_DUMPSTARTSTOP, OnDumpstartstop)
	ON_UPDATE_COMMAND_UI(ID_DUMPSTARTSTOP, OnUpdateDumpstartstop)
	ON_UPDATE_COMMAND_UI(ID_DUMPCLEAR, OnUpdateDumpclear)
	ON_UPDATE_COMMAND_UI(ID_DUMPPREVIEW, OnUpdateDumppreview)
	ON_COMMAND(ID_DUMPSETTINGS, OnDumpsettings)
	ON_COMMAND(ID_LASTTPRINT, OnLasttprint)
	ON_COMMAND(ID_LASTTPRINTVIEW, OnLasttprintview)
	ON_UPDATE_COMMAND_UI(ID_LASTTPRINT, OnUpdateLasttprint)
	ON_COMMAND(ID_PAGESETUP, OnPageSetup)
	ON_UPDATE_COMMAND_UI(ID_PAGESETUP, OnUpdatePageSetup)
	ON_UPDATE_COMMAND_UI(ID_LASTTPRINTVIEW, OnUpdateLasttprintview)
	ON_WM_KEYDOWN()
	ON_COMMAND(IDVK_F10, OnF10)
	ON_COMMAND(ID_TANDEMONOFF, OnTandemonoff)
	ON_UPDATE_COMMAND_UI(ID_TANDEMONOFF, OnUpdateTandemonoff)
	ON_COMMAND(ID_CLSSCR0, OnClsscr0)
	ON_COMMAND(ID_CREATEDLG, OnCreatedlg)
	ON_UPDATE_COMMAND_UI(ID_CREATEDLG, OnUpdateCreatedlg)
	ON_WM_CLOSE()
	ON_COMMAND(ID_OLESETTINGSDLG, OnOlesettingsdlg)
	ON_COMMAND(ID_TERM_HIDE, OnTermHide)
	ON_COMMAND(ID_REMOVEALLDLG, OnRemovealldlg)
	ON_COMMAND(ID_HELP, OnHelp)
	ON_COMMAND(ID_HELP_FINDER, OnHelpFinder)
	ON_COMMAND(ID_CREATEFRAME, OnCreateframe)
	ON_COMMAND(KEYALTF8, OnKEYALTF8)
	ON_COMMAND(KEYSHF10, OnKEYSHF10)
	ON_COMMAND(IDM_SHOWDLGMETHODS, OnShowdlgmethods)
	ON_COMMAND(IDM_DLGVIEWSPR, OnDlgviewspr)
	ON_UPDATE_COMMAND_UI(IDM_DLGVIEWSPR, OnUpdateDlgviewspr)
	ON_COMMAND(IDM_DLGDEBUGER, OnDlgdebuger)
	ON_COMMAND(IDM_DLGERRORS, OnDlgErrors)
	ON_COMMAND(IDM_FILEDIALOG, OnFiledialog)
	ON_UPDATE_COMMAND_UI(IDM_DLGDEBUGER, OnUpdateDlgdebuger)
	ON_UPDATE_COMMAND_UI(IDM_DLGERRORS, OnUpdateDlgdebuger)
	ON_UPDATE_COMMAND_UI(ID_CREATEFRAME, OnUpdateCreateframe)
	ON_UPDATE_COMMAND_UI(ID_REMOVEALLDLG, OnUpdateRemovealldlg)
	ON_UPDATE_COMMAND_UI(ID_REMOVEALLOBJ, OnUpdateRemoveallobj)
	ON_COMMAND(ID_BREAKSLAVE, OnBreakslave)
	ON_UPDATE_COMMAND_UI(ID_BREAKSLAVE, OnUpdateBreakslave)
	ON_COMMAND(ID_DUMPSOCKERROR, OnDumpsockerror)
	ON_UPDATE_COMMAND_UI(ID_DUMPSOCKERROR, OnUpdateDumpsockerror)
	ON_COMMAND(ID_BEGINSLAVE, OnBeginslave)
	ON_UPDATE_COMMAND_UI(ID_BEGINSLAVE, OnUpdateBeginslave)
	ON_COMMAND(ID_ENDSLAVE, OnEndslave)
	ON_UPDATE_COMMAND_UI(ID_ENDSLAVE, OnUpdateEndslave)
	ON_COMMAND(IDM_NOHIDEOUTPUT, OnNohideoutput)
	ON_UPDATE_COMMAND_UI(IDM_NOHIDEOUTPUT, OnUpdateNohideoutput)
	ON_COMMAND(IDM_REGISTERTERM, OnRegisterterm)
	ON_UPDATE_COMMAND_UI(IDM_REGISTERTERM, OnUpdateRegisterterm)
	ON_COMMAND(ID_DESKTOPDLG, OnDesktopdlg)
	ON_UPDATE_COMMAND_UI(ID_DESKTOPDLG, OnUpdateDesktopdlg)
	ON_COMMAND(ID_SCROBJDLG, OnScrObjdlg)
	ON_UPDATE_COMMAND_UI(ID_SCROBJDLG, OnUpdateScrObjdlg)
	ON_COMMAND(IDM_DLGVIEWIOFILE, OnDlgviewiofile)
	ON_UPDATE_COMMAND_UI(IDM_DLGVIEWIOFILE, OnUpdateDlgviewiofile)
	ON_COMMAND(IDM_DLGVIEWFSMETHODS, OnDlgviewFSMethods)
	ON_UPDATE_COMMAND_UI(IDM_DLGVIEWFSMETHODS, OnUpdateDlgviewFSMethods)
	ON_COMMAND(ID_CONTEXT_HELP, OnContextHelp)
	ON_COMMAND(IDM_DLGVIEWREGMETHODS, OnDlgviewregmethods)
	ON_UPDATE_COMMAND_UI(IDM_DLGVIEWREGMETHODS, OnUpdateDlgviewregmethods)
	ON_COMMAND(ID_EDIT_SCREEN_TO_CB, OnEditScreenToCb)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SCREEN_TO_CB, OnUpdateEditScreenToCb)
	ON_WM_KEYUP()
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_DUMPCAPTURECLEAR, OnDumpcaptureclear)
	ON_COMMAND(ID_DUMPCAPTUREPREVIEW, OnDumpcapturepreview)
	ON_COMMAND(ID_DUMPCAPTUREPREVIEWSETUP, OnDumpcapturepreviewsetup)
	ON_COMMAND(ID_SLAVEPRINTPAGESETUP, OnSlavePrintPageSetup)
	ON_COMMAND(ID_DUMPCAPTURESTARTSTOP, OnDumpcapturestartstop)
	ON_UPDATE_COMMAND_UI(ID_DUMPCAPTURECLEAR, OnUpdateDumpcaptureclear)
	ON_UPDATE_COMMAND_UI(ID_DUMPCAPTUREPREVIEW, OnUpdateDumpcapturepreview)
	ON_UPDATE_COMMAND_UI(ID_DUMPCAPTURESTARTSTOP, OnUpdateDumpcapturestartstop)
	ON_UPDATE_COMMAND_UI(ID_DUMPCAPTUREPREVIEWSETUP, OnUpdateDumpcapturepreviewsetup)
	ON_UPDATE_COMMAND_UI(ID_SLAVEPRINTPAGESETUP, OnUpdateSlavePrintPageSetup)
	ON_COMMAND(ID_DUMPCAPTURESTOP, OnDumpcapturestop)
	ON_UPDATE_COMMAND_UI(ID_DUMPCAPTURESTOP, OnUpdateDumpcapturestop)
	ON_COMMAND(ID_DUMPSTOP, OnDumpstop)
	ON_UPDATE_COMMAND_UI(ID_DUMPSTOP, OnUpdateDumpstop)
	ON_COMMAND(IDM_SEPARATEVIEWMODE, OnSeparateviewmode)
	ON_UPDATE_COMMAND_UI(IDM_SEPARATEVIEWMODE, OnUpdateSeparateviewmode)
	ON_COMMAND(IDM_SEPARATEVIEWINFRAME, OnSeparateviewinframe)
	ON_UPDATE_COMMAND_UI(IDM_SEPARATEVIEWINFRAME, OnUpdateSeparateviewinframe)
	ON_UPDATE_COMMAND_UI(ID_CLSSCR0, OnUpdateClsscr0)
	ON_COMMAND(IDM_DLGVIEWIMAGELISTS, OnDlgviewimagelists)
	ON_UPDATE_COMMAND_UI(IDM_DLGVIEWIMAGELISTS, OnUpdateDlgviewimagelists)
	ON_COMMAND(IDM_TERMCAP, OnTermcap)
	ON_COMMAND(IDM_TERMCAPAV, OnTermcapAV)
	ON_UPDATE_COMMAND_UI(IDM_TERMCAP, OnUpdateTermcap)
	ON_UPDATE_COMMAND_UI(IDM_TERMCAPAV, OnUpdateTermcapAV)
	ON_COMMAND(IDM_ENABLECONTEXTMENU, OnEnablecontextmenu)
	ON_UPDATE_COMMAND_UI(IDM_ENABLECONTEXTMENU, OnUpdateEnablecontextmenu)
	ON_COMMAND(IDM_EDITCONTEXTMENU, OnEditcontextmenu)
	ON_UPDATE_COMMAND_UI(IDM_EDITCONTEXTMENU, OnUpdateEditcontextmenu)
	ON_UPDATE_COMMAND_UI(ID_FULLCONTEXTMENU, OnUpdateFullcontextmenu)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDM_DLGVIEWCMMETHODS, OnDlgviewContextMenuMethods)
	ON_UPDATE_COMMAND_UI(IDM_DLGVIEWCMMETHODS, OnUpdateDlgviewContextMenuMethods)
	ON_COMMAND(IDM_DLGVIEWSYSMETHODS, OnDlgviewsysmethods)
	ON_UPDATE_COMMAND_UI(IDM_DLGVIEWSYSMETHODS, OnUpdateDlgviewsysmethods)
	ON_UPDATE_COMMAND_UI(ID_TERM_HIDE, OnUpdateTermHide)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SCRSIZE79X24, ID_SCRSIZECUSTOM, OnUpdateScreenSizeMenu)
	ON_COMMAND_RANGE(ID_SCRSIZE79X24, ID_SCRSIZECUSTOM, OnScreenSizeMenu )
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_WINDOWGRID, OnWindowGrid)
	ON_UPDATE_COMMAND_UI(ID_WINDOWGRID , OnUpdateWindowGrid)
	ON_WM_SIZING()
	ON_WM_MOUSEWHEEL()
	END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGP_TermView construction/destruction


CGP_TermView::CGP_TermView()
	: CFormView(CGP_TermView::IDD)
{
	dwWindowGrid=0;
	m_ODContextsArray=NULL;
	//{{AFX_DATA_INIT(CGP_TermView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_CaptureFlags=0;
	m_dwParseInitStrFlag=0;
	m_DlgSeparateViewInFrame=NULL;
	esc_pointer=0;
	ListenSock=NULL;
	m_OutputCharDelay=0;

	InputBuffer	=new char [NBINREADPOOL+10000];
	CurLenIB2=DEFNIB2;
	InputBuffer2=new char [CurLenIB2+10000];

//	strcpy(InputBuffer2,"OpenEx ;FILEDSN=vfplan");
//	GPC.GPODBC_DB.OpenGPDB(InputBuffer2);
//
	iLastCommand=0;
	dwXMouseMode=0;
	poXmouseLast.X=poXmouseLast.Y=0;

	pPreviewBitmap=NULL;
	m_CaptureFile=NULL;
	m_MouseSelectionMode=0;
	CommFnIsRun=FALSE;
	CommFn2IsRun=FALSE;
	CommFn3IsRun=FALSE;
	RefreshThreadIsRun=FALSE;
	m_LastActivity=CTime::GetCurrentTime();

	slave_nbcur=0;
	m_AUSI = NULL;
	GPFRD = NULL;
	LastProcKey=0;
	GPC.m_View=this;
	m_pSelection = NULL;
	m_StopPaint=FALSE;
	m_StopWorking=FALSE;


	InitializeCriticalSection(&m_CSRefresh);
	InitializeCriticalSection(&m_CSRemap);
	InitializeCriticalSection(&m_CSInputSema);

	m_pProcMonitor= new CProcMonitor(&m_CSRemap);

	LockPos=0;
	UnitHotkey=NULL;
	int i;
	m_GPMenu=NULL;

	alt_press=FALSE;
	AutoDecodFT=false;
	m_MaxIdle=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "MaxIdle",0);


	GPC.m_GUISet.FontName=AfxGetApp()->GetProfileString("GUISET", "m_FontName",GPC.m_GUISet.FontName);
	GPC.m_GUISet.CharSet=AfxGetApp()->GetProfileInt("GUISET", "m_CurFontCharSet",GPC.m_GUISet.CharSet);
	GPC.m_GUISet.Scale=AfxGetApp()->GetProfileInt("GUISET", "Scale",GPC.m_GUISet.Scale);

	GPC.m_GUISet.PointSize=AfxGetApp()->GetProfileInt("GUISET", "POINTSIZE",GPC.m_GUISet.PointSize);
	GPC.m_GUISet.Weight=AfxGetApp()->GetProfileInt("GUISET", "WEIGHT",GPC.m_GUISet.Weight);
	GPC.m_GUISet.Italic=AfxGetApp()->GetProfileInt("GUISET", "ITALIC",GPC.m_GUISet.Italic);
	GPC.m_GUISet.UseDefault=AfxGetApp()->GetProfileInt("GUISET", "CHECKDEFAULT",GPC.m_GUISet.UseDefault);

	#ifdef RUS
		GPC.m_CurCodePage=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_CurCodePage",1251);
	#else
		GPC.m_CurCodePage=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_CurCodePage",1252);
	#endif

	GPC.m_CurMBInvert=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "MBINVERT",-1);

	GPC.m_CompositingQuality=(CompositingQuality)AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_CompositingQuality",0);
	GPC.m_InterpolationMode=(InterpolationMode)AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_InterpolationMode",0);
	GPC.m_PixelOffsetMode=(PixelOffsetMode)AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_PixelOffsetMode",0);
	GPC.m_SmoothingMode=(SmoothingMode)AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_SmoothingMode",0);
	GPC.m_TextContrast=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_TextContrast",0);
	GPC.m_TextRenderingHint=(TextRenderingHint)AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_TextRenderingHint",0);
	GPC.m_TextContrast=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_TextContrast",0);
	GPC.m_Language=(TextRenderingHint)AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_Language",0);
	GPC.m_SubLanguage=(TextRenderingHint)AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_SubLanguage",0);


	if (GPC.m_CurMBInvert==-1)
	{
		char tmpss[]={198,81,165,208,0,};
		unsigned short tmpShort[5];

		GPC.m_CurMBInvert= (MultiByteToWideChar(
		  950, // code page
		  MB_PRECOMPOSED,         // character-type options
		  tmpss, // string to map
		  4,       // number of bytes in string
		  (LPWSTR)tmpShort,  // wide-character buffer
		  4       // size of buffer
		  ))?1:0;
	}

	KeybLockDelay=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "KeybLockDelay",150);
	GPC.EnableSlavePrint=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "SLAVEPRINT",0);
	GPC.EnableSlavePrintCHARVIEW=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "SLAVEPRINTCHARVIEW",1);

	GPC.BreakChar=(char)AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "BreakChar",127);
	m_UseContextMenu=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "ContextMenu",0);

	FlagBufferKeb=(AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_CheckKeybBuff",1)==1)?true:false;
	KeybBuffer=new char [GP_KEYBBUFFSIZE+1000];

	m_HIDEVIEWMODE=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_HideView",0);

	iSkip_0=0;
	iSkip_10=0;
	iSkip_13=0;
	HalfIntensity=false;
	GPC.AjCheckState=0;

	RemappingInputInProc=false;

	forcounter=string_ptr=log_flag=inputnbyte=0;
	curent_inputbyte=-1;
	name_curent=new char [DEFNIB2+100];

	stopchar=123456;
	SendPickFlProgressDlg=NULL;
	OldMouse=false;


	next_job=0;	job_flag=0;

	for(i=0;i<GP_NFILES;i++) aGP_File[i]=NULL;

	strncpy(GPC.contmenuFileName,AfxGetApp()->GetProfileString(GPC.cs_RegTermViewSetName, "CONTEXTMENUFILE",GPC.contmenuFileName),250);
	GPC.contmenuFileName[250]=0;
	m_csOldTermCapFileName=m_csCurentTermCapFileName=GPC.TermCapFileName;
	OldPaletteFile=CurentPaletteFile="";

	FILE *tmp;
	tmp=fopen(GPC.TermCapFileName,"rb");
	if (tmp) fclose(tmp);
	else
	{
		char sdrive[25],sdir[500], sfname[50], sext[10];
		_splitpath( AfxGetApp()->m_pszHelpFilePath, sdrive,sdir, sfname, sext );
		sprintf(GPC.TermCapFileName,"%s%sTERMCAP.TXT",sdrive,sdir);
	}

}

CGP_TermView::~CGP_TermView()
{
	GPC.m_View=NULL;
	if (m_pProcMonitor) delete m_pProcMonitor;

	try{
	if (GPC.m_pContextMenu) delete GPC.m_pContextMenu;
	}catch(...){;}
	GPC.m_pContextMenu=NULL;


	if (m_ODContextsArray) delete m_ODContextsArray;
	m_ODContextsArray=NULL;

	if (ListenSock) delete ListenSock;
	ListenSock=NULL;

	if (m_DlgSeparateViewInFrame) delete m_DlgSeparateViewInFrame;
	m_DlgSeparateViewInFrame=NULL;

	int cntr=0;
	while(cntr++<100 && (CommFnIsRun || CommFn2IsRun || CommFn3IsRun))
		Sleep(100);

	if (GPFRD!=NULL) delete GPFRD;
	GPFRD=NULL;

	if (UnitHotkey!=NULL) delete UnitHotkey;
	UnitHotkey=NULL;

	int i;
	for(i=0;i<GP_NFILES;i++)
		if (aGP_File[i]!=NULL) {delete aGP_File[i];aGP_File[i]=NULL;}

	if (m_GPMenu!=NULL) delete m_GPMenu;
	m_GPMenu=NULL;

	delete[] KeybBuffer;

	if (InputBuffer!=NULL) delete[] InputBuffer;
	InputBuffer=NULL;
	if (InputBuffer2!=NULL) delete[] InputBuffer2;
	InputBuffer2=NULL;
	if (name_curent!=NULL) delete[] name_curent;
	name_curent=NULL;
	DeleteCriticalSection(&m_CSInputSema);
	DeleteCriticalSection(&m_CSRemap);
	if (m_AUSI!=NULL) delete m_AUSI;
	m_AUSI=NULL;
	m_AUSI=NULL;

	if (SendPickFlProgressDlg!=NULL)
	{
		delete SendPickFlProgressDlg;
		SendPickFlProgressDlg=NULL;
	}

	if (m_CaptureFile) fclose(m_CaptureFile);
	m_CaptureFile=NULL;

	DeleteCriticalSection(&m_CSRefresh);

}

void CGP_TermView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGP_TermView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

#include "GPEdit.h"


BOOL CGP_TermView::PreCreateWindow(CREATESTRUCT& cs)
{
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CGP_TermView::OnInitialUpdate()
{
	UINT m_ViewModeTmp=0;
	m_ViewMode|=(m_ViewModeTmp=AfxGetApp()->GetProfileInt("SEP_OUTPUT_SET", "m_ViewMode",0x10000))&0xFFFF0000;

	m_AUSI = new GP_AutoSizing;
	m_AUSI->AddSetMain(this->m_hWnd);

	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout(FALSE);
//	ResizeParentToFit();


	if (AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "IDC_RESTORESIZE",0))
	{
		CRect re;
		re.left=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "RESTORESIZEX",0);
		re.top=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "RESTORESIZEY",0);
		re.right=re.left+AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "RESTORESIZECX",0);
		re.bottom=re.top+AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "RESTORESIZECY",0);

		if (re.Width()>200 && re.Height()>200)
		{
			GetParentFrame()->MoveWindow(&re,TRUE);
			//RecalcLayout();
		}
	}



	m_OperationId=0;

	// TODO: remove this code when final selection model code is written
	m_pSelection = NULL;    // initialize selection

	//Active documents should always be activated
	COleDocument* pDoc = (COleDocument*) GetDocument();
	if (pDoc != NULL)
	{
		// activate the first one
		POSITION posItem = pDoc->GetStartPosition();
		if (posItem != NULL)
		{
			CDocItem* pItem = pDoc->GetNextItem(posItem);

			// only if it's an Active document
			COleDocObjectItem *pDocObjectItem =
				DYNAMIC_DOWNCAST(COleDocObjectItem, pItem);

			if (pDocObjectItem != NULL)
			{
				pDocObjectItem->DoVerb(OLEIVERB_SHOW, this);
			}
		}
	}

	SafeInit();

	if (m_Comm.Get_commType()==GPCT_COMPORT && *m_Comm.GetInitStr()!=0)
	{
		GPC.cs_ScriptLine=m_Comm.GetInitStr();
		DoScriptCommand();
	}

//	if (*m_Comm.GetInitStr()!=0)
//		SetTimer( SCRIPT_TIMER_ID, 1000, NULL);
#ifndef BRIZ
	static int FlgAdmMenu;
	if (GPC.AdmIsOn && !FlgAdmMenu)
	{
		FlgAdmMenu=1;
		CMenu *tmp=AfxGetMainWnd()->GetMenu();
		if (tmp!=NULL)
		{
			CMenu *tmp2=tmp->GetSubMenu(0);
			if (tmp2!=NULL)
			{
				CMenu *tmp3=tmp2->GetSubMenu(1);
				if (tmp3!=NULL)
				{
					CMenu *tmp4=tmp3->GetSubMenu(0);
					if (tmp4!=NULL)
#ifdef RUS
						tmp->InsertMenu(2,MF_BYPOSITION|MF_POPUP,(UINT)tmp4->m_hMenu,"Администратор");
#else
						tmp->InsertMenu(2,MF_BYPOSITION|MF_POPUP,(UINT)tmp4->m_hMenu,"Admin");
#endif
					tmp4=tmp3->GetSubMenu(1);
					if (tmp4!=NULL)
#ifdef RUS
						tmp->InsertMenu(3,MF_BYPOSITION|MF_POPUP,(UINT)tmp4->m_hMenu,"Разработчик");
#else
						tmp->InsertMenu(3,MF_BYPOSITION|MF_POPUP,(UINT)tmp4->m_hMenu,"Developer");
#endif
				}
			}
		}
		m_GPMenu->InitTermMenuList();
	}
#endif

	UpdateMenuByAdm();
	AfxGetMainWnd()->DrawMenuBar();

	if ((m_ViewModeTmp&GPVIEWMODE_TYPEMASK)==GPVIEWMODE_SEPARATE)
		OnSeparateviewmode();
}

/////////////////////////////////////////////////////////////////////////////
// CGP_TermView printing

void CGP_TermView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
// CGP_TermView printing

	if (m_PrintTransp==TRANSPRINT || m_PrintTransp==DUMPPRINT)
	{
		FILE *tmp=fopen(m_PrintTransp==TRANSPRINT?"prnt.txt":m_Comm.GetDumpFileName(),"rb");
		if (tmp!=NULL)
		{
			int c;
			UINT pos=1;
			if (PrintLiningStyle==0)
			{
				while(pInfo->m_nCurPage>pos && (c=fgetc(tmp))!=EOF)
					if (c==12) pos++;
			}
			else
			{
				char str[1100];
				int ii;
				while(pInfo->m_nCurPage>pos && fgets(str,1000,tmp)!=NULL)
				{
					for(ii=1;ii<65 && fgets(str,1000,tmp)!=NULL;ii++);
					pos++;
				}
			}

			int tmpnl=0;
			while((c=fgetc(tmp))!=EOF && c!=12 && (PrintLiningStyle==0 || tmpnl<65))
			if (c==27)
			{
				fgetc(tmp);	fgetc(tmp);
				int c3=fgetc(tmp),c4=0;
				if (c3!='@') c4=fgetc(tmp);
				if (c4=='O')
					if (c3>'0')
					{
						DEVMODE* dm=pInfo->m_pPD->GetDevMode( );
						dm->dmOrientation=DMORIENT_LANDSCAPE ;//DEVMODE *dm
						pDC->ResetDC(dm);
					}
					else
					{
						DEVMODE* dm=pInfo->m_pPD->GetDevMode( );
						dm->dmOrientation=DMORIENT_PORTRAIT ;//DEVMODE *dm
						pDC->ResetDC(dm);
					}
			}
			if (c==10) tmpnl++;

			fclose(tmp);
		}
	}

	CFormView::OnPrepareDC(pDC, pInfo);
}



BOOL CGP_TermView::OnPreparePrinting(CPrintInfo* pInfo)
{
	KillTimer( PRINT_JOB_TIMER_ID);
	int np=1;
	if (m_PrintTransp==TRANSPRINT || m_PrintTransp==DUMPPRINT)
	{
		FILE *tmp=fopen(m_PrintTransp==TRANSPRINT?"prnt.txt":m_Comm.GetDumpFileName(),"rb");
		if (tmp==NULL) return FALSE;
		int c,nl=1,nc=1,maxl=30,maxc=76;
		while((c=fgetc(tmp))!=EOF)
		{
			if (c==12)
			{
				if (nl>maxl) maxl=nl;
				np++;nl=0;
			}

			if (c==10 || c==12)
			{
				if (nc>maxc) maxc=nc;
				nc=1; nl++;
			}
			else
				if (c==27)
				{
					fgetc(tmp);	fgetc(tmp);
					if (fgetc(tmp)!='@')	fgetc(tmp);
				}
				else	if (c!=7)	nc++;
		}
		if (nl>maxl) maxl=nl;
		if (nl<4 && np>1) np--;

		PrintLiningStyle=0;
		if (maxl>80 && np<2) {np=maxl/65+1;maxl=65;PrintLiningStyle=1;}

		GPScreen **pr=&GetDocument()->ScrPrn;
		if (*pr!=NULL) delete *pr;
		*pr=new GPScreen(0,Size(maxc,maxl),0,0);
		(*pr)->SetChrColor(0,0);
		(*pr)->SetBkgColor(RGB(255,255,255),0);

		fclose(tmp);
	}

	pInfo->SetMaxPage(np);

	if (!CView::DoPreparePrinting(pInfo))
	{
		SetTimer( PRINT_JOB_TIMER_ID, PRINT_JOB_TIMER_DELAY, NULL);
		return FALSE;
	}

	if (!COleDocObjectItem::OnPreparePrinting(this, pInfo))
	{
		SetTimer( PRINT_JOB_TIMER_ID, PRINT_JOB_TIMER_DELAY, NULL);
		return FALSE;
	}

	return TRUE;
}

void CGP_TermView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	if (pPreviewBitmap) delete pPreviewBitmap;
	pPreviewBitmap=NULL;
	CFormView::OnBeginPrinting(pDC, pInfo);
}

void CGP_TermView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
//	if (m_PrintTransp>=TRANSPRINT)
		SetTimer( PRINT_JOB_TIMER_ID, PRINT_JOB_TIMER_DELAY, NULL);
//	else	if (LockRemappingFlag>0) LockRemappingFlag--;
	CFormView::OnEndPrinting(pDC, pInfo);
	if (pPreviewBitmap) delete pPreviewBitmap;
	pPreviewBitmap=NULL;
	if (m_PrintTransp!=TRANSPRINT && m_PrintTransp!=DUMPPRINT)
	{
		CGP_TermDoc* doc=GetDocument( );
		if (doc)
		{
			GPScreen *s=doc->GetScreenById(m_PrintTransp);
			s->ScreenPrintBitmap;
			if (s->ScreenPrintBitmap) delete s->ScreenPrintBitmap;
			s->ScreenPrintBitmap=NULL;
		}
	}

}

void CGP_TermView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	if (m_PrintTransp==TRANSPRINT || m_PrintTransp==DUMPPRINT)
	{
		FILE *tmp=fopen(m_PrintTransp==TRANSPRINT?"prnt.txt":m_Comm.GetDumpFileName(),"rb");
		if (tmp!=NULL)
		{
			int c;
			UINT pos=1;

			if (PrintLiningStyle==0)
			{
				while(pInfo->m_nCurPage>pos && (c=fgetc(tmp))!=EOF)
					if (c==12) pos++;
			}
			else
			{
				char str[1100];
				int ii;
				while(pInfo->m_nCurPage>pos && fgets(str,1000,tmp)!=NULL)
				{
					for(ii=1;ii<65 && fgets(str,1000,tmp)!=NULL;ii++);
					pos++;
				}
			}

			GPScreen *pr=GetDocument()->ScrPrn;
			pr->SetBkgColor(RGB(255,255,255),0);
			pr->SetChrColor(0,0);
			pr->ClearScreen();
			pr->SetCursorPosition(0,0);
			int tmpnl=0;

			while((c=fgetc(tmp))!=EOF && c!=12 && (PrintLiningStyle==0 || tmpnl<65))
				if (c!=27)	{if (c!=7)	pr->CharOutAW((char)c);	if (PrintLiningStyle!=0 && c==10) tmpnl++;}
				else
				{
					UINT Stl=pr->GetChrStyle()|GP_FNT_OPAQUE;
					fgetc(tmp);	fgetc(tmp);
					int c3=fgetc(tmp),c4=0;
					if (c3!='@') c4=fgetc(tmp);
					if (c3>'0' && c3!='@')
					{
						switch(c4)
						{
						case 'B': Stl|=GP_FNT_BOLD;		break;//bold
						case 'S': Stl|=GP_FNT_ITALIC;	break;//ital
						case 'D': Stl|=GP_FNT_UNDERLINE;break;//und
						}
					}
					else
					{
						switch(c4)
						{
						case 'B': Stl&=(GP_FNT_BOLD^0xFFFFFFFF);break;//bold
						case 'S': Stl&=(GP_FNT_ITALIC^0xFFFFFFFF);break;//ital
						case 0:	  Stl&=(GP_FNT_UNDERLINE^0xFFFFFFFF);break;
						}
					}
					pr->SetChrStyle(Stl,0);
				}

			fclose(tmp);
			pr->ScrPrint(pDC,pInfo);
		}
	}
	else
	{
		CGP_TermDoc* doc=GetDocument( ) ;
		doc->GetScreenById(m_PrintTransp)->ScrPrint(pDC,pInfo);
	}

	if(pInfo->m_bDocObject)
		COleDocObjectItem::OnPrint(this, pInfo, TRUE);
	else
		CView::OnPrint(pDC, pInfo);


}

void CGP_TermView::OnDestroy()
{
	if (m_ODContextsArray) delete m_ODContextsArray;
	m_ODContextsArray=NULL;

	if (m_DlgSeparateView.m_hWnd)
	{
		m_DlgSeparateView.ResetParent();
		::DestroyWindow(m_DlgSeparateView.m_hWnd);
		if (m_DlgSeparateViewInFrame)
		{
			m_DlgSeparateViewInFrame->m_DlgViewInputAll=NULL;
			m_DlgSeparateViewInFrame->m_DlgViewOutput=NULL;
		}
	}

	if (m_DlgSeparateViewInFrame)
	{
		if (m_DlgSeparateViewInFrame->m_hWnd)
			m_DlgSeparateViewInFrame->DestroyWindow();
		delete m_DlgSeparateViewInFrame;
		m_DlgSeparateViewInFrame=NULL;
	}

	CFormView::OnDestroy();
	GPC.m_hViewWnd=NULL;

	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
	{
	  pActiveItem->Deactivate();
	  ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
	}
}


/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands

BOOL CGP_TermView::IsSelected(const CObject* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CGP_TermCntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced.

	// TODO: implement this function that tests for a selected OLE client item

	return pDocItem == m_pSelection;
}

void CGP_TermView::OnInsertObject()
{
	// Invoke the standard Insert Object dialog box to obtain information
	//  for new CGP_TermCntrItem object.
	COleInsertDialog dlg;
	if (dlg.DoModal(COleInsertDialog::DocObjectsOnly) != IDOK)
		return;

	BeginWaitCursor();

	CGP_TermCntrItem* pItem = NULL;
	TRY
	{
		// Create new item connected to this document.
		CGP_TermDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CGP_TermCntrItem(pDoc);
		ASSERT_VALID(pItem);

		// Initialize the item from the dialog data.
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // any exception will do
		ASSERT_VALID(pItem);

		pItem->DoVerb(OLEIVERB_SHOW, this);

		ASSERT_VALID(pItem);

		// As an arbitrary user interface design, this sets the selection
		//  to the last item inserted.

		// TODO: reimplement selection as appropriate for your application

		m_pSelection = pItem;   // set selection to last inserted item
		pDoc->UpdateAllViews(NULL);
	}
	CATCH(CException, e)
	{
		if (pItem != NULL)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

	EndWaitCursor();
}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation.
void CGP_TermView::OnCancelEditCntr()
{
	// Close any in-place active item on this view.
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place.
void CGP_TermView::OnSetFocus(CWnd* pOldWnd)
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// need to set focus to this item if it is in the same view
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL)
		{
			pWnd->SetFocus();   // don't call the base class
			return;
		}
	}
	CFormView::OnSetFocus(pOldWnd);
}

BOOL CGP_TermView::GetOptimalSize(int &cx, int &cy)
{
	BOOL ret=FALSE;
	EnterCriticalSection(&m_CSRefresh);
	try
	{
		GPScreen *s=GetDocument()->GetMainScreen();
		if (!s)
		{
			GetDocument()->InitIfNone();
			s=GetDocument()->GetMainScreen();
		}
		if (s)
		{
			REAL tmp1=s->LeftBorderSafe,tmp2=s->RightBorderSafe,tmp3=s->TopBorderSafe,tmp4=s->BottomBorderSafe;
			int oldCX=cx,oldCY=cy;
			s->CalcSafeBorder(&cx, &cy, &tmp1, &tmp2, &tmp3, &tmp4);
			ret=(cx!=oldCX || cy!=oldCY ||
				tmp1!=s->LeftBorderSafe || tmp2!=s->RightBorderSafe || 
				tmp3!=s->TopBorderSafe || tmp4!=s->BottomBorderSafe);
		}
	}catch(...)
	{;}
	LeaveCriticalSection(&m_CSRefresh);

	return ret;
}


void CGP_TermView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);

	if (pActiveItem != NULL)
		pActiveItem->SetItemRects();


	{
		CGP_TermDoc* doc=GetDocument( ) ;
		doc->InitIfNone();

		if (m_DlgSeparateViewInFrame && m_DlgSeparateViewInFrame->m_hWnd && (m_ViewMode&GPVIEWMODE_INFRAME) && (m_ViewMode&GPVIEWMODE_SEPARATE))
			m_DlgSeparateViewInFrame->FrameSizeMove();

		m_OperationId=0;
		if (m_AUSI && m_AUSI->GetItemCount())
		{
			//LockWindowUpdate();
			m_AUSI->UpdateSize();
			//UnlockWindowUpdate();
		}
	}


//////////////	CRect re; GetWindowRect(&re);
//////////////	GetDocument()->GetMainScreen()->ResizingUnits(&re);
}

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CGP_TermView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CGP_TermView diagnostics

#ifdef _DEBUG
void CGP_TermView::AssertValid() const
{
	CFormView::AssertValid();
}

void CGP_TermView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CGP_TermDoc* CGP_TermView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGP_TermDoc)));
	return (CGP_TermDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGP_TermView message handlers

void CGP_TermView::OnTimer(UINT nIDEvent)
{
	KillTimer( nIDEvent);
	CFormView::OnTimer(nIDEvent);
	if (m_MaxIdle)
	{
		UINT min = (UINT)((CTime::GetCurrentTime().GetTime()-m_LastActivity.GetTime())/60);
		if (m_MaxIdle<=min)
		{
			GPC.Flags|=GP_CUR_EXITFLAG;
			AfxGetApp()->GetMainWnd()->PostMessage(WM_CLOSE);
		}
	}

	switch(nIDEvent)
	{
	case LISTEN_TIMER_ID:
		{
			if (ListenSock==NULL) BeginListen();
			if (ListenSock && m_ListenTime>0)
			{
				m_ListenTime--;
				if (ListenSock->Listen() && !m_StopWorking && ListenSock->Accept(*(m_Comm.hSock)))
				{
					m_Comm.m_TelnetFlag&=(0xFFFFFFFF^0x1);
					m_Comm.m_ConnectionFlag&=(0xFFFFFFFF^0x10000);
					m_ListenTime=-1;
				}
			}
		
			if (m_ListenTime>0)
				SetTimer( LISTEN_TIMER_ID, 100, NULL);
			else 
			{
				if (ListenSock) delete ListenSock;
				ListenSock=NULL;
			}

		}
		break;

	case PRINT_JOB_TIMER_ID:
		if (m_PrintTransp>=TRANSPRINT) m_PrintTransp=0;
		if (LockRemappingFlag>0) LockRemappingFlag--;
		break;

	case CURSOR_TIMER_ID:
		{
			SetTimer( CURSOR_TIMER_ID, CursorTimerDelay, NULL);
			GPScreen *s=GetDocument()->GetMainScreen();
			if (s->GetCursorState())
			{
				GPWindow *w=s->GPActiveWindow();
				HDC mdc=::GetDC(m_hWnd);
				if (mdc)
				{
					static DWORD dwCntr;
					Point cpo=s->GetCursorPosition();
					Graphics gr(mdc);
					gr.TranslateTransform(s->LeftBorderSafe*s->CharPlaceSize.Width,s->TopBorderSafe*s->CharPlaceSize.Height,MatrixOrderPrepend);

					const char *ccName="Cursor";
					CODContext *ocontext=m_ODContextsArray->GetContext(ccName);
					if (ocontext->m_ContextName!=ccName)
					{
						ocontext=m_ODContextsArray->CreateContext(ccName);
						ocontext->DoMethod("SetBrush 0,SolidColor,CLR(COLOR_WINDOW)",NULL);
						ocontext->DoMethod("SetBrush 1,SolidColor,CLR(COLOR_WINDOW)",NULL);
						ocontext->DoMethod("SetPen 0,CLR(COLOR_HOTLIGHT)",NULL);
						ocontext->DoMethod("SetPen 1,CLR(COLOR_HOTLIGHT)",NULL);
						ocontext->DoMethod("SetInt 1,0",NULL);

						ocontext->DoMethod("AddItem SET,INT(IDX(10)),INT(0)",NULL);
						ocontext->DoMethod("AddItem IF,INT(IDX(0)),&,INT(HEX(2))",NULL);
						ocontext->DoMethod("AddItem SET,INT(IDX(10)),INT(1)",NULL);
						ocontext->DoMethod("AddItem ENDIF",NULL);
						ocontext->DoMethod("AddItem IF,INT(IDX(1)),=,INT(0)",NULL);
						ocontext->DoMethod("AddItem FILLRECTANGLE,BRUSH(REF(10)),RECT(IDX(3))",NULL);
						ocontext->DoMethod("AddItem ENDIF",NULL);
						ocontext->DoMethod("AddItem IF,INT(IDX(1)),=,INT(1)",NULL);
						ocontext->DoMethod("AddItem FILLRECTANGLE,BRUSH(REF(10)),RECT(IDX(2))",NULL);
						ocontext->DoMethod("AddItem ENDIF",NULL);
						ocontext->DoMethod("AddItem IF,INT(IDX(1)),=,INT(2)",NULL);
						ocontext->DoMethod("AddItem DRAWRECTANGLE,PEN(REF(10)),RECT(IDX(2))",NULL);
						ocontext->DoMethod("AddItem ENDIF",NULL);
					}
					RectF reClient;
					DWORD curColor=s->GetChrColor();
					int r=GetRValue(curColor),g=GetGValue(curColor),b=GetBValue(curColor);
					int maxVal=r;
					if (g>maxVal) maxVal=g;
					if (b>maxVal) maxVal=b;

					if ((curColor&0xFF000000)) ocontext->m_RGBArr[4].SetValue(curColor);
					else ocontext->m_RGBArr[4].SetFromCOLORREF(curColor);
					if (maxVal)
						curColor=(curColor&0xFF000000)|RGB(r*255/maxVal,g*255/maxVal,b*255/maxVal);
					else
						curColor=(curColor&0xFF000000)|0xFFFFFF;
				
					if ((curColor&0xFF000000)) ocontext->m_RGBArr[0].SetValue(curColor);
					else ocontext->m_RGBArr[0].SetFromCOLORREF(curColor);

					ARGB argb=ocontext->m_RGBArr[0].GetValue();
					ocontext->m_RGBArr[6].SetValue((argb&0xFF000000)|(0xFFFFFF^argb));
					ocontext->m_RGBArr[8].SetValue(argb&0xFF000000);

					DWORD curColorBkg=s->GetBkgColor();
					if ((curColorBkg&0xFF000000)) ocontext->m_RGBArr[1].SetValue(curColorBkg);
					else ocontext->m_RGBArr[1].SetFromCOLORREF(curColorBkg);

					if (!dwCntr)
					{
						ocontext->m_RGBArr[2]=ocontext->m_RGBArr[0];
						ocontext->m_RGBArr[3]=ocontext->m_RGBArr[1];
						w->RepaintWndPos(cpo);
					}

					if (ocontext->m_BrushArr[0] && ocontext->m_BrushArr[0]->m_Brush)
						((SolidBrush *)ocontext->m_BrushArr[0]->m_Brush)->SetColor(ocontext->m_RGBArr[2]);
					if (ocontext->m_BrushArr[1] && ocontext->m_BrushArr[1]->m_Brush)
						((SolidBrush *)ocontext->m_BrushArr[1]->m_Brush)->SetColor(ocontext->m_RGBArr[3]);
					if (ocontext->m_PenArr[0] && ocontext->m_PenArr[0]->m_Pen)
						ocontext->m_PenArr[0]->m_Pen->SetColor(ocontext->m_RGBArr[2]);
					if (ocontext->m_PenArr[1] && ocontext->m_PenArr[1]->m_Pen)
						ocontext->m_PenArr[1]->m_Pen->SetColor(ocontext->m_RGBArr[3]);

					ocontext->m_IntArr[0]=dwCntr;
					RECT clRect;
					::GetClientRect(m_hWnd,&clRect);
					ocontext->m_RectArr[0].X=(REAL)(clRect.left*100);
					ocontext->m_RectArr[0].Y=(REAL)(clRect.top*100);
					ocontext->m_RectArr[0].Width=(REAL)((clRect.right-clRect.left+1)*100);
					ocontext->m_RectArr[0].Height=(REAL)((clRect.bottom-clRect.top+1)*100);

					ocontext->m_RectArr[1].X=(REAL)w->GetWndViewRect().X;
					ocontext->m_RectArr[1].Y=(REAL)w->GetWndViewRect().Y;
					ocontext->m_RectArr[1].Width=(REAL)w->GetWndViewRect().Width;
					ocontext->m_RectArr[1].Height=(REAL)w->GetWndViewRect().Height;

					ocontext->m_PointArr[0].X=(REAL)cpo.X;
					ocontext->m_PointArr[0].Y=(REAL)cpo.Y;

					ocontext->m_PointArr[1].X=(REAL)(cpo.X+w->GetWndViewRect().X-w->GPWndViewOfset.X);
					ocontext->m_PointArr[1].Y=(REAL)(cpo.Y+w->GetWndViewRect().Y-w->GPWndViewOfset.Y);

					ocontext->m_RectArr[2].X=ocontext->m_PointArr[1].X*100;
					ocontext->m_RectArr[2].Y=ocontext->m_PointArr[1].Y*100;
					ocontext->m_RectArr[2].Width=100;
					ocontext->m_RectArr[2].Height=100;

					ocontext->m_RectArr[3].X=ocontext->m_PointArr[1].X*100+3;
					ocontext->m_RectArr[3].Y=ocontext->m_PointArr[1].Y*100+85;
					ocontext->m_RectArr[3].Width=94;
					ocontext->m_RectArr[3].Height=10;

					gr.ScaleTransform(s->CharPlaceSize.Width/(REAL)100,s->CharPlaceSize.Height/(REAL)100);
					ocontext->PaintToGraphics(gr,reClient,NULL);
					dwCntr=ocontext->m_IntArr[0]+1;

				}
				::ReleaseDC(m_hWnd,mdc);
			}
		}
		break;

	case LOCKCOM_TIMER_ID:
		GPC.Flags&=(GP_CUR_LOCKCOM^0xFFFFFFFF);
		break;

	case KEYBLOCK_TIMER_ID:
		//
		if (KeybBufferSize>0 && FlagBufferKeb) m_Comm.GPSendBlock(KeybBuffer,KeybBufferSize);
		KeybBufferSize=0;
		GPC.AjCheckState=0;
		break;

	case SCRIPTOUT_TIMER_ID:
		DoScriptCommand();
		break;

	case PORT_TIMER_ID:
		DoRemappingInput();
		SetTimer( PORT_TIMER_ID, PORT_TIMER_DELAY, NULL);
		break;

	case REFRESH_TIMER_ID:
		GPC.BlinkValue=(GPC.BlinkValue+0x40000000)&0xFF000000;
		RefreshBlink();
		SetTimer( REFRESH_TIMER_ID, REFRESH_TIMER_DELAY, NULL);
		break;

	// SSH Dll
	case SSH_TIMING_TIMER_ID:
		m_Comm.SendMessageToDLL(WM_TIMER, SSH_TIMING_TIMER_ID, 0);
		break;
	}
}


void CGP_TermView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if (m_DlgSeparateViewInFrame==NULL || m_DlgSeparateViewInFrame->m_hWnd==NULL || !m_DlgSeparateViewInFrame->IsWindowVisible())
	{
		EnterCriticalSection(&m_CSRefresh);
		try
		{
			CGP_TermDoc* doc=GetDocument();
			GPScreen *scr=doc->GetMainScreen();
			if (scr && !scr->ScreenBitmap) scr->CreateScreenBitmap(TRUE);

			if (scr && scr->ScreenBitmap) 
			{
					Graphics gr(dc.m_hDC);
					CRect rrr1;
					::GetClipBox(dc.m_hDC,&rrr1);
					RectF RectClip((REAL)rrr1.left,(REAL)rrr1.top,(REAL)rrr1.Width(),(REAL)rrr1.Height());
					gr.DrawImage(scr->ScreenBitmap,RectClip.X,RectClip.Y,RectClip.X,RectClip.Y,RectClip.Width,RectClip.Height,UnitPixel);
				//	gr.DrawImage(scr->ScreenBitmap,0,0);
					if ((dwWindowGrid&0x1))
					{
						gr.TranslateTransform((REAL)(floor(scr->LeftBorderSafe*scr->CharPlaceSize.Width*1000+0.49)/1000),(REAL)(floor(scr->TopBorderSafe*scr->CharPlaceSize.Height*1000+0.49)/1000),MatrixOrderPrepend);
						Pen mp1(Color(208, 255,100,100),1);
						Pen mp2(Color(208, 255,100,200),1);
						Pen mp3(Color(208, 255,200,100),1);
						REAL X1,X2,Y1,Y2;
						INT nRows=scr->GetScreenSize().Height;
						INT nCols=scr->GetScreenSize().Width;
						INT x,y;
						X1=0;	X2=(REAL)nCols*scr->CharPlaceSize.Width;
						for(y=0;y<nRows;y++)
							if ((y%5)==0)
							{
								Y1=Y2=(REAL)y*scr->CharPlaceSize.Height;
								if ((y%20)==0)
									gr.DrawLine(&mp1,X1,Y1,X2,Y2);
								else
								if ((y%10)==0)
									gr.DrawLine(&mp2,X1,Y1,X2,Y2);
								else
									gr.DrawLine(&mp3,X1,Y1,X2,Y2);
							}

						Y1=0; Y2=(REAL)nRows*scr->CharPlaceSize.Height;
						for(x=0;x<nCols;x++)
							if ((x%5)==0)
							{
								X1=X2=(REAL)x*scr->CharPlaceSize.Width;
								if ((x%20)==0)
									gr.DrawLine(&mp1,X1,Y1,X2,Y2);
								else
								if ((x%10)==0)
									gr.DrawLine(&mp2,X1,Y1,X2,Y2);
								else
									gr.DrawLine(&mp3,X1,Y1,X2,Y2);
							}
					}

			}
		}catch(...)
		{;}
		LeaveCriticalSection(&m_CSRefresh);
//		doc->GetMainScreen()->ScrPaint(&dc);
	}
}

BOOL CGP_TermView::OnScrollBy(CSize sizeScroll, BOOL bDoScroll)
{
	CPoint pp=GetDeviceScrollPosition();
	return CFormView::OnScrollBy(sizeScroll, bDoScroll);
}

#include <math.h>

void CGP_TermView::RefreshBlink()
{
	GPScreen *scr=GetDocument()->GetMainScreen();
	Size ScrSize=scr->GetScreenSize();
	int nall;
	if ((nall=ScrSize.Width*ScrSize.Height)>0)
	{
		CRect currect;
		char *mscr=new char [nall];
		ZeroMemory(mscr,nall*sizeof(char));
		scr->GetBlinkPoints(mscr);
		int pos=0;
		while(pos<nall)
		{
			if (mscr[pos]==2) scr->RedrawPoint(pos);
			pos++;
		}
		delete[] mscr;
	}
}


BOOL CGP_TermView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
//	return CFormView::OnEraseBkgnd(pDC);
}

void CGP_TermView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if 	(!LastProcKey/*!=(nChar&0x1FF)*/)	KSendChar((char)nChar);
	LastProcKey=0;

	if (nChar==(unsigned char)GPC.BreakChar && GPC.AjCheckState==0 && SendPickFlProgressDlg!=NULL)
	{
		SendPickFlProgressDlg->GPClose();
		delete SendPickFlProgressDlg;
		SendPickFlProgressDlg=NULL;
	}
//		CFormView::OnChar(nChar, nRepCnt, nFlags);
}

BOOL CGP_TermView::OnHelpInfo(HELPINFO* pHelpInfo)
{
	return TRUE;
//	return CFormView::OnHelpInfo(pHelpInfo);
}


BOOL CGP_TermView::SendChar(char ch)
{
	if (m_Comm.TandemFlag==TRUE) return FALSE;
	return  (GPC.AdmIsOn || ch!=GPC.BreakChar)? m_Comm.GPSendChar(ch) : FALSE;
}

UINT CGP_TermView::SendWord(UINT ch)
{
	return m_Comm.GPSendWord(ch);
}

UINT CGP_TermView::SendDWord(UINT ch)
{
	return m_Comm.GPSendDWord(ch);
}


BOOL CGP_TermView::KSendChar(char ch)
{
	ch=GPC.chAnsiDos[(unsigned char)ch];

	if (m_Comm.TandemFlag==TRUE)
	{
		m_Comm.TandemFlag=FALSE;
		SendChar(ch);
		if (ch==13 && m_CRLFflag!=FALSE) SendChar(10);
		m_Comm.TandemFlag=TRUE;
	}
	else
		if (GPC.AjCheckState==0)
		{
			SendChar(ch);
			if (ch==13 && m_CRLFflag!=FALSE) SendChar(10);
		}
	else
	{
		if (KeybBufferSize<GP_KEYBBUFFSIZE) KeybBuffer[KeybBufferSize++]=ch;
		if (KeybBufferSize<GP_KEYBBUFFSIZE && ch==13 && m_CRLFflag!=FALSE) KeybBuffer[KeybBufferSize++]=10;

		if (BeepFlag)
		{
			if (PlaySound("ding.wav", NULL, SND_ASYNC)==FALSE) MessageBeep( 0xFFFFFFFF);   // sound type);( 2000,  150);
		}
		return FALSE;
	}
return  TRUE;
}

void CGP_TermView::OnComsettingsdlg()
{
	GPDlgCommtype dlgc;
	dlgc.DoModal();
}

void CGP_TermView::OnKEYALTF1()		{SendPredefKey(VK_F1,((GPC.EasyTCL==false)?0:MOD_EASYTCL)|MOD_ALT,0);}
void CGP_TermView::OnKEYALTF2()		{SendPredefKey(VK_F2,((GPC.EasyTCL==false)?0:MOD_EASYTCL)|MOD_ALT,0);}
void CGP_TermView::OnKEYALTF3()		{SendPredefKey(VK_F3,((GPC.EasyTCL==false)?0:MOD_EASYTCL)|MOD_ALT,0);}
/*void CGP_TermView::OnKEYALTF4()	{KSendChar(2);KSendChar(51);}*/
void CGP_TermView::OnKEYALTF5()		{SendPredefKey(VK_F5,((GPC.EasyTCL==false)?0:MOD_EASYTCL)|MOD_ALT,0);}
void CGP_TermView::OnKEYALTF6()		{SendPredefKey(VK_F6,((GPC.EasyTCL==false)?0:MOD_EASYTCL)|MOD_ALT,0);}
void CGP_TermView::OnKEYALTF7()		{SendPredefKey(VK_F7,((GPC.EasyTCL==false)?0:MOD_EASYTCL)|MOD_ALT,0);}
void CGP_TermView::OnKEYALTF8()		{SendPredefKey(VK_F8,((GPC.EasyTCL==false)?0:MOD_EASYTCL)|MOD_ALT,0);}
void CGP_TermView::OnKEYALTF9()		{SendPredefKey(VK_F9,((GPC.EasyTCL==false)?0:MOD_EASYTCL)|MOD_ALT,0);}
void CGP_TermView::OnKEYALTF10()	{SendPredefKey(VK_F10,((GPC.EasyTCL==false)?0:MOD_EASYTCL)|MOD_ALT,0);}
void CGP_TermView::OnKEYALTF11()	{SendPredefKey(VK_F11,((GPC.EasyTCL==false)?0:MOD_EASYTCL)|MOD_ALT,0);}
void CGP_TermView::OnKEYALTF12()	{SendPredefKey(VK_F12,((GPC.EasyTCL==false)?0:MOD_EASYTCL)|MOD_ALT,0);}
void CGP_TermView::OnKEYSHF10()		{SendPredefKey(VK_F10,((GPC.EasyTCL==false)?0:MOD_EASYTCL)|MOD_SHIFT,0);}

#include "GPFontList.h"

int CGP_TermView::PrepareXMouseState(int iState)
{
	int b1=0;
	if ((iState&MK_LBUTTON)==MK_LBUTTON) b1=0;
	else
	if ((iState&MK_MBUTTON)==MK_MBUTTON) b1=1;
	else
	if ((iState&MK_RBUTTON)==MK_RBUTTON) b1=2;

	if ((iState&MK_SHIFT)==MK_SHIFT) b1|=0x4;
	if ((GetAsyncKeyState(VK_RMENU)&0xFF00)
		|| (GetAsyncKeyState(VK_LMENU)&0xFF00)
		)  b1|=0x8;
	if ((iState&MK_CONTROL)==MK_CONTROL) b1|=0x10;
	if ((iState&MK_XBUTTON1)==MK_XBUTTON1) b1|=0x20;
	if ((iState&MK_XBUTTON2)==MK_XBUTTON2) b1|=0x40;

	return b1;
}

int CGP_TermView::XMouseAction(DWORD dwAction, UINT nFlags, CPoint point)
{
	int ret=0;
	if (dwXMouseMode&GP_XMOUSE_MASK_DEC)
	{
		GPScreen *scr=GetDocument()->GetMainScreen();
		Point poCurrent=scr->GetCharPosByWndPos(Point(point.x,point.y));
		char tmps[250];
		*tmps=0;
		int cc=0x20;

		switch(dwAction&GP_XMOUSE_ACTION_MASK)
		{
		case GP_XMOUSE_ACTION_WHEELFBKW:
			cc++;
		case GP_XMOUSE_ACTION_WHEELFRWD:
			{
				cc+=4;
				switch(dwXMouseMode&GP_XMOUSE_MASK_DEC)
				{
				case GP_XMOUSE_X10:
				case GP_XMOUSE_VT200:
				case GP_XMOUSE_BTN_EVENT:
				case GP_XMOUSE_ANY_EVENT:
					sprintf(tmps,"\033[M%c%c%c",PrepareXMouseState(nFlags)&0xFFFFFFF8+cc,poXmouseFirst.X+0x21,poXmouseFirst.Y+0x21);
					ret+=m_Comm.GPSendBlock(tmps,6);
					//TRACE("%X %s\n",PrepareXMouseState(nFlags),tmps);
					break;
				case GP_XMOUSE_VT200_HIGHLIGHT:
					break;
				}
			}
			break;
		case GP_XMOUSE_ACTION_DBLCLK:
			if (GP_XMOUSE_INACTION&dwXMouseMode)
			{
				switch(dwXMouseMode&GP_XMOUSE_MASK_DEC)
				{
				case GP_XMOUSE_BTN_EVENT:
				case GP_XMOUSE_ANY_EVENT:
				case GP_XMOUSE_VT200:
					sprintf(tmps,"\033[M%c%c%c",PrepareXMouseState(nFlags)|0x3+0x20,poXmouseFirst.X+0x21,poXmouseFirst.Y+0x21);
					ret+=m_Comm.GPSendBlock(tmps,6);
					//TRACE("%X %s\n",PrepareXMouseState(nFlags),tmps);
					break;
				case GP_XMOUSE_VT200_HIGHLIGHT:
					break;
				}
				dwXMouseMode&=(0xFFFFFFFF^GP_XMOUSE_INACTION);
				ret+=XMouseAction(GP_XMOUSE_ACTION_PRESS,  nFlags, point);
			}
			break;
		case GP_XMOUSE_ACTION_PRESS:
			poXmouseFirst=poCurrent;
			dwXMouseMode|=GP_XMOUSE_INACTION;
			switch(dwXMouseMode&GP_XMOUSE_MASK_DEC)
			{
			case GP_XMOUSE_X10:
				dwXMouseMode&=(0xFFFFFFFF^GP_XMOUSE_INACTION);
			case GP_XMOUSE_BTN_EVENT:
			case GP_XMOUSE_ANY_EVENT:
			case GP_XMOUSE_VT200:
				sprintf(tmps,"\033[M%c%c%c",PrepareXMouseState(nFlags)+0x20,poXmouseFirst.X+0x21,poXmouseFirst.Y+0x21);
				ret+=m_Comm.GPSendBlock(tmps,6);
				//TRACE("%X %s\n",PrepareXMouseState(nFlags),tmps);
				break;
			case GP_XMOUSE_VT200_HIGHLIGHT:
				break;
			}
			poXmouseLast=poXmouseFirst;
			break;
		case GP_XMOUSE_ACTION_RELEASE:
			if (GP_XMOUSE_INACTION&dwXMouseMode)
			{
				switch(dwXMouseMode&GP_XMOUSE_MASK_DEC)
				{
				case GP_XMOUSE_BTN_EVENT:
				case GP_XMOUSE_ANY_EVENT:
				case GP_XMOUSE_VT200:
					sprintf(tmps,"\033[M%c%c%c",PrepareXMouseState(nFlags)|0x3+0x20,poCurrent.X+0x21,poCurrent.Y+0x21);
					ret+=m_Comm.GPSendBlock(tmps,6);
					//TRACE("%X %s\n",PrepareXMouseState(nFlags),tmps);
					break;
				case GP_XMOUSE_VT200_HIGHLIGHT:
					break;
				}
				dwXMouseMode&=(0xFFFFFFFF^GP_XMOUSE_INACTION);
				poXmouseLast=poCurrent;
			}
			break;
		case GP_XMOUSE_ACTION_MOVE:
			if (GP_XMOUSE_INACTION&dwXMouseMode)
			{
				Point po1=poXmouseFirst;
				Point po2=poCurrent;
				if (poXmouseLast.X!=po2.X || poXmouseLast.Y!=po2.Y)
				{
					switch(dwXMouseMode&GP_XMOUSE_MASK_DEC)
					{
					case GP_XMOUSE_X10:
					case GP_XMOUSE_VT200:
						break;
					case GP_XMOUSE_BTN_EVENT:
					case GP_XMOUSE_ANY_EVENT:
						sprintf(tmps,"\033[M%c%c%c",PrepareXMouseState(nFlags)+0x40,poCurrent.X+0x21,poCurrent.Y+0x21);
						ret+=m_Comm.GPSendBlock(tmps,6);
						//TRACE("%X %s\n",PrepareXMouseState(nFlags),tmps);
						break;
					case GP_XMOUSE_VT200_HIGHLIGHT:
						break;
					}
					poXmouseLast=po2;
				}
			}
			break;
		}
	}

	return ret;
}

void CGP_TermView::OnMouseMove(UINT nFlags, CPoint point)
{
	MouseLastPoint=point;
	MouseLastFlag=nFlags;
	XMouseAction(GP_XMOUSE_ACTION_MOVE, nFlags, point);

	if (m_MouseSelectionMode)
	{
		EnterCriticalSection(&m_CSRefresh);
		try
		{
			GPScreen *scr=GetDocument()->GetMainScreen();
			Point po1=m_SelectionStartPoint;
			Point po2=scr->GetCharPosByWndPos(Point(point.x,point.y));

			Rect resel(po1.X,po1.Y,po2.X-po1.X,po2.Y-po1.Y);
			if (resel.Width<0){resel.X+=resel.Width;resel.Width=-resel.Width;}
			if (resel.Height<0){resel.Y+=resel.Height;resel.Height=-resel.Height;}
			resel.Width++;
			resel.Height++;
			//scr->ResetSelection();
			scr->SetSelection(resel);
			SetMouseSelectionCursor();
			m_SelectionLastPoint=po2;
		}catch(...)
		{;}
		LeaveCriticalSection(&m_CSRefresh);
	}

	CFormView::OnMouseMove(nFlags, point);
}



void CGP_TermView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	MouseLastPoint=point;
	MouseLastFlag=nFlags;
	XMouseAction(GP_XMOUSE_ACTION_DBLCLK, nFlags, point);

	if (OldMouse && GPC.AjCheckState==0)
	{
		SendChar(255);
		switch(MouseLastFlag)
		{
		case MK_CONTROL|MK_LBUTTON: SendChar(47); break;
		case MK_SHIFT|MK_LBUTTON:	SendChar(44); break;
		case MK_LBUTTON:			SendChar(41); break;
		default:					SendChar(41); break;
		}
		Point poCh=GetDocument()->GetMainScreen()->GetCharPosByWndPos(Point(point.x,point.y));
		SendChar((char)(poCh.X+' '));
		SendChar((char)(poCh.Y+' '));
	}

	CFormView::OnLButtonDblClk(nFlags, point);
}

void CGP_TermView::OnLButtonDown(UINT nFlags, CPoint point)
{
	MouseLastPoint=point;
	MouseLastFlag=nFlags;
	XMouseAction(GP_XMOUSE_ACTION_PRESS, nFlags, point);

	if (OldMouse && GPC.AjCheckState==0)
	{
		SendChar(255);
		switch(MouseLastFlag)
		{
		case MK_CONTROL|MK_LBUTTON: SendChar(57); break;
		case MK_SHIFT|MK_LBUTTON:	SendChar(54); break;
		case MK_LBUTTON:			SendChar(51); break;
		default:					SendChar(51); break;
		}
		Point poCh=GetDocument()->GetMainScreen()->GetCharPosByWndPos(Point(point.x,point.y));
		SendChar((char)(poCh.X+' '));
		SendChar((char)(poCh.Y+' '));
	}
	else
	if ((GetAsyncKeyState(VK_SHIFT)&0xFF00)!=0 || (GetAsyncKeyState(VK_CONTROL)&0xFF00)!=0)
	{
		m_MouseSelectionMode=1;
		m_SelectionStartPoint=GetDocument()->GetMainScreen()->GetCharPosByWndPos(Point(point.x,point.y));
		m_SelectionLastPoint=m_SelectionStartPoint;
		//GetDocument()->GetMainScreen()->ResetSelection();
		GetDocument()->GetMainScreen()->SetSelection(Rect(m_SelectionStartPoint.X,m_SelectionStartPoint.Y,1,1));
		SetCapture();
		SetMouseSelectionCursor();
		//Invalidate();
	}
	CFormView::OnLButtonDown(nFlags, point);
}



void CGP_TermView::OnLButtonUp(UINT nFlags, CPoint point)
{
	MouseLastPoint=point;
	MouseLastFlag=nFlags;
	XMouseAction(GP_XMOUSE_ACTION_RELEASE, nFlags, point);

	Point poCh=GetDocument()->GetMainScreen()->GetCharPosByWndPos(Point(point.x,point.y));

	if (OldMouse && GPC.AjCheckState==0)
	{
		SendChar(255);
		switch(MouseLastFlag)
		{
		case MK_CONTROL|MK_LBUTTON: SendChar(67); break;
		case MK_SHIFT|MK_LBUTTON:	SendChar(64); break;
		case MK_LBUTTON:			SendChar(61); break;
		default:					SendChar(61); break;
		}
		SendChar((char)(poCh.X+' '));
		SendChar((char)(poCh.Y+' '));
	}

	if (m_MouseSelectionMode)
	{
		m_MouseSelectionMode=0;
		::ReleaseCapture();
		::SetCursor(::LoadCursor(NULL,IDC_ARROW));
		Rect selRect(m_SelectionStartPoint,Size(poCh.X-m_SelectionStartPoint.X+1,poCh.Y-m_SelectionStartPoint.Y+1));

		GetDocument()->GetMainScreen()->ResetSelection();
		CString csTmp;
		GetScreenText(csTmp, selRect);

		if ((nFlags&MK_CONTROL)==MK_CONTROL)
			StringToClip(csTmp);

		if ((nFlags&MK_SHIFT)==MK_SHIFT && csTmp.GetLength())
		{
			AnsiToDos(csTmp,csTmp,1);
			m_Comm.GPSendBlock(csTmp,csTmp.GetLength());
		}
	}

	CFormView::OnLButtonUp(nFlags, point);
}

void CGP_TermView::OnMButtonDblClk(UINT nFlags, CPoint point)
{
	MouseLastPoint=point;
	MouseLastFlag=nFlags;
	XMouseAction(GP_XMOUSE_ACTION_DBLCLK, nFlags, point);

	if (OldMouse && GPC.AjCheckState==0)
	{
		SendChar(255);
		switch(MouseLastFlag)
		{
		case MK_CONTROL|MK_MBUTTON: SendChar(49); break;
		case MK_SHIFT|MK_MBUTTON:	SendChar(46); break;
		case MK_MBUTTON:			SendChar(43); break;
		default:					SendChar(43); break;
		}
		Point poCh=GetDocument()->GetMainScreen()->GetCharPosByWndPos(Point(point.x,point.y));
		SendChar((char)(poCh.X+' '));
		SendChar((char)(poCh.Y+' '));
	}
	CFormView::OnMButtonDblClk(nFlags, point);
}

void CGP_TermView::OnMButtonDown(UINT nFlags, CPoint point)
{
	MouseLastPoint=point;
	MouseLastFlag=nFlags;
	XMouseAction(GP_XMOUSE_ACTION_PRESS, nFlags, point);
	if (OldMouse && GPC.AjCheckState==0)
	{
		SendChar(255);
		switch(MouseLastFlag)
		{
		case MK_CONTROL|MK_MBUTTON: SendChar(59); break;
		case MK_SHIFT|MK_MBUTTON:	SendChar(56); break;
		case MK_MBUTTON:			SendChar(53); break;
		default:					SendChar(53); break;
		}
		Point poCh=GetDocument()->GetMainScreen()->GetCharPosByWndPos(Point(point.x,point.y));
		SendChar((char)(poCh.X+' '));
		SendChar((char)(poCh.Y+' '));
	}
	CFormView::OnMButtonDown(nFlags, point);
}

void CGP_TermView::OnMButtonUp(UINT nFlags, CPoint point)
{
	MouseLastPoint=point;
	MouseLastFlag=nFlags;
	XMouseAction(GP_XMOUSE_ACTION_RELEASE, nFlags, point);

	if (OldMouse && GPC.AjCheckState==0)
	{
		SendChar(255);
		switch(MouseLastFlag)
		{
		case MK_CONTROL|MK_MBUTTON: SendChar(69); break;
		case MK_SHIFT|MK_MBUTTON:	SendChar(66); break;
		case MK_MBUTTON:			SendChar(63); break;
		default:					SendChar(63); break;
		}
		Point poCh=GetDocument()->GetMainScreen()->GetCharPosByWndPos(Point(point.x,point.y));
		SendChar((char)(poCh.X+' '));
		SendChar((char)(poCh.Y+' '));
	}
	CFormView::OnMButtonUp(nFlags, point);
}

void CGP_TermView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	MouseLastPoint=point;
	MouseLastFlag=nFlags;
	XMouseAction(GP_XMOUSE_ACTION_DBLCLK, nFlags, point);

	if (OldMouse && GPC.AjCheckState==0)
	{
		SendChar(255);
		switch(MouseLastFlag)
		{
		case MK_CONTROL|MK_RBUTTON: SendChar(48); break;
		case MK_SHIFT|MK_RBUTTON:	SendChar(45); break;
		case MK_RBUTTON:			SendChar(42); break;
		default:					SendChar(42); break;
		}
		Point poCh=GetDocument()->GetMainScreen()->GetCharPosByWndPos(Point(point.x,point.y));
		SendChar((char)(poCh.X+' '));
		SendChar((char)(poCh.Y+' '));
	}
	CFormView::OnRButtonDblClk(nFlags, point);
}

void CGP_TermView::OnRButtonDown(UINT nFlags, CPoint point)
{
	MouseLastPoint=point;
	MouseLastFlag=nFlags;
	XMouseAction(GP_XMOUSE_ACTION_PRESS, nFlags, point);

	if (OldMouse && GPC.AjCheckState==0)
	{
		SendChar(255);
		switch(MouseLastFlag)
		{
		case MK_CONTROL|MK_RBUTTON: SendChar(58); break;
		case MK_SHIFT|MK_RBUTTON:	SendChar(55); break;
		case MK_RBUTTON:			SendChar(52); break;
		default:					SendChar(52); break;
		}
		Point poCh=GetDocument()->GetMainScreen()->GetCharPosByWndPos(Point(point.x,point.y));
		SendChar((char)(poCh.X+' '));
		SendChar((char)(poCh.Y+' '));
	}
	CFormView::OnRButtonDown(nFlags, point);
}

void CGP_TermView::OnRButtonUp(UINT nFlags, CPoint point)
{
	MouseLastPoint=point;
	MouseLastFlag=nFlags;
	XMouseAction(GP_XMOUSE_ACTION_RELEASE, nFlags, point);

	if (OldMouse && GPC.AjCheckState==0)
	{
		SendChar(255);
		switch(MouseLastFlag)
		{
		case MK_CONTROL|MK_RBUTTON: SendChar(68); break;
		case MK_SHIFT|MK_RBUTTON:	SendChar(65); break;
		case MK_RBUTTON:			SendChar(62); break;
		default:					SendChar(62); break;
		}
		Point poCh=GetDocument()->GetMainScreen()->GetCharPosByWndPos(Point(point.x,point.y));
		SendChar((char)(poCh.X+' '));
		SendChar((char)(poCh.Y+' '));
	}
	CFormView::OnRButtonUp(nFlags, point);
}

// Обработка сообщения на переключение в режим блокировки передачи клавиатуры на сервер
void CGP_TermView::OnKeyblock()
{
	if (GPC.AjCheckState>0) GPC.AjCheckState=123456;
	iSkip_0=0;
	iSkip_10=0;
	iSkip_13=0;
	SetKeybLock();
}

// Обработка сообщения на переключение в режим трансляции Легкий TCL
void CGP_TermView::OnTranslateTcl()
{
	if (GPC.EasyTCL==true) GPC.EasyTCL=false; else GPC.EasyTCL=true;
}

void CGP_TermView::OnDefcolor()
{
// Обработка сообщения на установку цветов по умолчанию
// void CGP_TermView::OnDefcolor()
	HalfIntensity=false;
	GPScreen *s=GetDocument()->GetMainScreen();
	s->SetChrColorIndex(GPC.DefFrgColorInd,0);
	s->SetBkgColorIndex(GPC.DefBkgColorInd,0);
	s->RecolorScr(GPC.DefFrgColor,GPC.DefBkgColor);
}


void CGP_TermView::OnButtoncalc()
{
	CWnd *cw;
	if ((cw=FindWindow("SciCalc",NULL))==NULL
#ifdef RUS
		&& (cw=FindWindow(NULL,"Калькулятор"))==NULL
#else
		&& (cw=FindWindow(NULL,"Calc"))==NULL
#endif
		&& (cw=FindWindow(NULL,"Calc"))==NULL)	_spawnlp(_P_NOWAIT,"calc.exe","calc.exe",NULL);
	else
	{
		cw->SetForegroundWindow();
	}
}

void CGP_TermView::OnColordlg127()
{
	CGPDlgColor127 dlg;
	if (dlg.DoModal()==IDOK) ReadColor127();
}


void CGP_TermView::OnStartNewSession()
{
	CDlgNewSession dlg;
	dlg.DoModal();
}

void CGP_TermView::OnUpdateStartNewSession(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CGP_TermView::OnUpdateOnMenuadm(CCmdUI* pCmdUI)
{
	const char *ccnewtext="";
	if (GPC.AdmIsOn)
#ifdef RUS
		ccnewtext="Закрыть режим\x3 MAINIL\x3 37";
	else
		ccnewtext="Открыть режим\x3 MAINIL\x3 37";
#else
		ccnewtext="Disable administrator features\x3 MAINIL\x3 37";
	else
		ccnewtext="Enable administrator features\x3 MAINIL\x3 37";
#endif

	if (!pCmdUI->m_pMenu)
		pCmdUI->SetText(ccnewtext);
	else
	{
		MENUITEMINFO mii={0};
		mii.cbSize=sizeofMENUITEMINFO;
		mii.fMask=MIIM_DATA;
		if (::GetMenuItemInfo(pCmdUI->m_pMenu->m_hMenu,pCmdUI->m_nIndex,TRUE,&mii))
			m_GPMenu->MENUINFOArray[mii.dwItemData].csText=ccnewtext;
	}

//	pCmdUI->Enable(TRUE);
}

void CGP_TermView::OnSentinitstr()
{
	GPC.cs_ScriptLine=m_Comm.GetInitStr();
	GPC.cs_ScriptWaitLine="";
	GPC.cs_ScriptWaitLineCurrent="";
	GPC.dw_ScriptWaitFlag=0;
	if (GPC.cs_ScriptLine!="")	DoScriptCommand();
}

void CGP_TermView::OnMenuadm()
{
	GPAdmIsOn dlg(&(GPC.AdmIsOn));
	dlg.DoModal();
	m_GPMenu->Fill_mArrMenu(FALSE);
//#ifdef BRIZ
//	GPC.AdmIsOn=1;
//#endif
#ifdef BRIZ
	AfxGetApp()->WriteProfileInt(GPC.cs_RegTermViewSetName, "BRIZINITA",GPC.AdmIsOn);
#else
	AfxGetApp()->WriteProfileInt(GPC.cs_RegTermViewSetName, "INITA",GPC.AdmIsOn);
#endif
	UpdateMenuByAdm();
}

void CGP_TermView::SetKeybLock()
{
	KillTimer( KEYBLOCK_TIMER_ID);
	if (GPC.AjCheckState>120000) SetTimer( KEYBLOCK_TIMER_ID, KeybLockDelay, NULL);
	else GPC.AjCheckState++;
}

BOOL CGP_TermView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	if (pHandlerInfo==NULL)
	{
		if (nCode == CN_COMMAND)
		{
			if (nID>=MENU_ID_START && nID<=MENU_ID_END && m_GPMenu!=NULL)
			{
				m_GPMenu->OnCommandUserMenu(0,nID-MENU_ID_START);
				return TRUE;
			}
			if (nID>=GPCM_ID_START && nID<=GPCM_ID_END && GPC.m_pContextMenu)
			{
				PGPMENUINFO cm=GPC.m_pContextMenu->FindItemByCommand(nID);
				if (cm)
				{
					GPC.cs_ScriptLine=cm->csOut;
					GPC.cs_ScriptWaitLine="";
					GPC.cs_ScriptWaitLineCurrent="";
					GPC.dw_ScriptWaitFlag=0;
					DoScriptCommand();
				}
			}
		}
		else
		if (nCode == CN_UPDATE_COMMAND_UI)
		{
			if (m_GPMenu)
			{
				if (pExtra && ((CCmdUI*)pExtra)->m_pSubMenu==NULL)
				{
					if (nID>=MENU_ID_START && nID<=MENU_ID_END)
					{
						m_GPMenu->DoUpdateUserMenu(nID-MENU_ID_START, (CCmdUI*)pExtra);
						return TRUE;
					}
					
				}
				else
				{
					if (m_GPMenu->DoUpdateUserMenu(nID-MENU_ID_START, (CCmdUI*)pExtra)==TRUE)
						return TRUE;
				}
			}
			if ((nID>=GPCM_ID_START && nID<=GPCM_ID_END && pExtra) || (nID>=0x1000 && nID<=0x1100))
			{
				((CCmdUI*)pExtra)->Enable();
				return TRUE;
			}
		}
	}
	return CFormView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CGP_TermView::OnAltb()
{
	OnAltBCom();
}

void CGP_TermView::OnAltBCom()
{
	if (GPC.AjCheckState==0 && SendPickFlProgressDlg!=NULL)
	{
		SendPickFlProgressDlg->GPClose();
		delete SendPickFlProgressDlg;
		SendPickFlProgressDlg=NULL;
	}
	if (GPC.AjCheckState==0)	SendChar(GPC.BreakChar);
}

void CGP_TermView::OnTermSettings()
{
	CDlgTermSet Dlg;
	if (Dlg.DoModal()==IDOK && m_hWnd)
	{
		GPScreen *s=GetDocument()->GetMainScreen();
		if (!s)	GetDocument()->InitIfNone();
		s=GetDocument()->GetMainScreen();

		s->LeftBorderC=s->LeftBorderSafe=GPScreen::ScrLeftBorder;
		s->RightBorderC=s->RightBorderSafe=GPScreen::ScrRightBorder;
		s->TopBorderC=s->TopBorderSafe=GPScreen::ScrTopBorder;
		s->BottomBorderC=s->BottomBorderSafe=GPScreen::ScrBottomBorder;

		s->SetBkgColor(GPC.DefBkgColor,0);
		s->SetChrColor(GPC.DefFrgColor,0);

		RECT re;
		::GetClientRect(m_hWnd,&re);
		s->SetViewSize(re.right-re.left+1,re.bottom-re.top+1);
		::PostMessage(m_hWnd,GPM_INVALIDATE,0,0);
	}
	KeybLockDelay=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "KeybLockDelay",150);
}

void CGP_TermView::OnFontLocaleSettings()
{
	CDlgFontSet Dlg;
	Dlg.DoModal();
	Invalidate();
}

void CGP_TermView::OnGUISettings()
{
	CDlgGUISet Dlg;
	Dlg.DoModal();
}

void CGP_TermView::OnReconnect()
{
	BOOL bDo=TRUE;
#ifdef RUS
	if (m_Comm.IsConnected() && (bDo=(AfxMessageBox("Вы действительно хотите прервать текущее соединение?",MB_ICONQUESTION|MB_APPLMODAL|MB_OKCANCEL,0)==IDOK)))
#else
	if (m_Comm.IsConnected() && (bDo=(AfxMessageBox("Are You want discard currend connection?",MB_ICONQUESTION|MB_APPLMODAL|MB_OKCANCEL,0)==IDOK)))
#endif
	{
		char *str=new char [12000];
		m_Comm.GPSendChar(GPC.BreakChar);
		m_Comm.GPRead(str,10000);
		Sleep(800);
		m_Comm.GPRead(str,10000);
		m_Comm.GPSendLine("exit\r");
		Sleep(800);
		m_Comm.GPRead(str,10000);
		delete[] str;
		m_Comm.GPClose();
	}
	if (bDo)
	{
		if (m_Comm.GPSectionName!="temporary")
			m_Comm.Set_comm(ExtractField(m_Comm.GPSectionName,2,"\\"),0);
		SafeInit();
	}
}

void CGP_TermView::OnUpdateReconnect(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GPC.AdmIsOn);
}

void CGP_TermView::OnUpdateAltBCom(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GPC.AdmIsOn && GPC.AjCheckState==0);
}

void CGP_TermView::OnEditPaste()
{
// get text from the clipboard
	HANDLE hClipData;                        /* handle to clip data  */
	LPSTR  lpClipData;                           /* pointers to clip data */

	if (OpenClipboard())
	{
		if (!(hClipData = GetClipboardData(CF_TEXT)))    CloseClipboard();
		else
		{
			char *str=new char [GlobalSize(hClipData)];
			if (!(lpClipData = (char *)GlobalLock(hClipData))) CloseClipboard();
			else
			{
				strcpy(str, lpClipData);
				GlobalUnlock(hClipData);
				CloseClipboard();
				AnsiToDos(str,1);
				char *pos=str;
				while(*pos!=0)
				{
					switch(*pos)
					{
					case 13:
					case 10: m_Comm.GPSendChar(*pos); Sleep(200);break;
					default: 
						m_Comm.GPSendChar(*pos); 
						break;
					}
					pos++;
				}
			}
			delete[] str;
		}
	}
}

void CGP_TermView::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}
#include "MainFrm.h"

void CGP_TermView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView)
{
	CFormView::OnEndPrintPreview(pDC, pInfo, point, pView);
	((CMainFrame *)AfxGetMainWnd())->UpdateAndRecalc();
}

void CGP_TermView::OnClsscr()
{
	GetDocument()->GetMainScreen()->ClearScreen();
	GetDocument()->GetMainScreen()->SetCursorPosition(0,0);
}

void CGP_TermView::OnRemoveallmenu()
{
	m_GPMenu->Fill_mArrMenu(TRUE);
	AfxGetMainWnd()->DrawMenuBar();
}

void CGP_TermView::OnRemoveallobj()
{
	GetDocument()->GetMainScreen()->DeleteAllObjects();
}

void CGP_TermView::OnDumpclear()
{
	if (m_Comm.IsDumping()==TRUE) 	m_Comm.GPStopDump();
	m_Comm.GPStartDump();
}

#include "DlgNotepadSet.h"

void CGP_TermView::OnDumppreview()
{
	if (m_Comm.IsDumping()==TRUE) m_Comm.GPStopDump();

	CString csNotepadDumpSet="";
	CString csNotepadSet="";
	CDlgNotepadSet::GetNotepadSettings(csNotepadSet);
	CDlgNotepadSet::GetNotepadTypeSettings("NotepadDumpSet",csNotepadDumpSet);
	if (csNotepadDumpSet=="")			csNotepadDumpSet=csNotepadSet;
	if (csNotepadSet!=csNotepadDumpSet)	CDlgNotepadSet::SetNotepadSettings(csNotepadDumpSet);

	SHELLEXECUTEINFO ExecInfo={0};
	ExecInfo.cbSize=sizeof(ExecInfo);
	ExecInfo.fMask=0x00000010/*SEE_MASK_ICON*/;
	ExecInfo.hwnd=m_hWnd;
	ExecInfo.lpVerb="open";
	ExecInfo.lpFile="NOTEPAD.EXE";
	ExecInfo.lpParameters=m_Comm.GetDumpFileName();
	ExecInfo.nShow=SW_SHOW;

	if (::ShellExecuteEx(&ExecInfo)==FALSE)
	{
		ExecInfo.lpFile=m_Comm.GetDumpFileName();
		ExecInfo.lpVerb="edit";
		ExecInfo.lpParameters=NULL;
		::ShellExecuteEx(&ExecInfo);
	}

	if (csNotepadSet!=csNotepadDumpSet)
		CDlgNotepadSet::SetNotepadSettings(csNotepadSet);
}

void CGP_TermView::OnDumpstartstop()
{
	m_Comm.GPContinueDump();
}

void CGP_TermView::OnUpdateDumpstartstop(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_Comm.IsDumping()!=TRUE);
}

void CGP_TermView::OnUpdateDumpclear(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_Comm.IsDumping()!=TRUE);
}

void CGP_TermView::OnDumpstop()
{
	m_Comm.GPStopDump();
}

void CGP_TermView::OnUpdateDumpstop(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_Comm.IsDumping());
}

void CGP_TermView::OnUpdateDumppreview(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_Comm.IsDumping()==FALSE && _access(m_Comm.GetDumpFileName(),4)==0);
}

void CGP_TermView::OnDumpsettings()
{
	CDlgDumpSettings	Dlg;
	Dlg.DoModal();
}

void CGP_TermView::OnLasttprint()
{
	if (AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "PRINTASTXT",0))
	{
		CString csNotepadDumpSet="";
		CString csNotepadSet="";
		CDlgNotepadSet::GetNotepadSettings(csNotepadSet);
		CDlgNotepadSet::GetNotepadTypeSettings("SlavePrintPageSetup",csNotepadDumpSet);
		if (csNotepadDumpSet=="")			csNotepadDumpSet=csNotepadSet;
		if (csNotepadSet!=csNotepadDumpSet)	CDlgNotepadSet::SetNotepadSettings(csNotepadDumpSet);

		SHELLEXECUTEINFO ShExecInfo={0};
		ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		ShExecInfo.fMask=0x00000010/*SEE_MASK_ICON*/|SEE_MASK_NOASYNC|SEE_MASK_NOCLOSEPROCESS;
		ShExecInfo.lpParameters = NULL;
		ShExecInfo.lpFile="NOTEPAD.EXE";
		ShExecInfo.hwnd=m_hWnd;
		char tmpcwd[500];
		*tmpcwd=0;
		_getcwd(tmpcwd,490);
		ShExecInfo.lpDirectory=tmpcwd;
		ShExecInfo.lpVerb="open";
		ShExecInfo.nShow=SW_HIDE;
		ShExecInfo.lpParameters=" /p \"prnt.txt\"";
		if (::ShellExecuteEx(&ShExecInfo)==FALSE)
		{
			ShExecInfo.lpParameters=NULL;
			ShExecInfo.lpFile="prnt.txt";
			ShExecInfo.lpVerb="print";
			::ShellExecuteEx(&ShExecInfo);
		}
		if (ShExecInfo.hProcess) 
		{
			DWORD dwExCode=STILL_ACTIVE;
			DWORD cntr=0;
			while(cntr++<1000 && ::GetExitCodeProcess(ShExecInfo.hProcess,&dwExCode) && dwExCode)
				Sleep(10);
		}

		if (csNotepadSet!=csNotepadDumpSet)
			CDlgNotepadSet::SetNotepadSettings(csNotepadSet);
	}
	else
	{
		m_PrintTransp=TRANSPRINT;
		SendMessage(WM_COMMAND,ID_FILE_PRINT);
	}
}

void CGP_TermView::OnLasttprintview()
{
	m_PrintTransp=TRANSPRINT;
	SendMessage(WM_COMMAND,ID_FILE_PRINT_PREVIEW);
}

void CGP_TermView::OnUpdateLasttprint(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(_access("prnt.txt",4)==0);
}

void CGP_TermView::OnUpdateLasttprintview(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(_access("prnt.txt",4)==0);
}

#include "GPDlgPageSetup.h"

void CGP_TermView::OnPageSetup()
{
	GPDlgPageSetup dlg;
	dlg.DoModal();
}

void CGP_TermView::OnUpdatePageSetup(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CGP_TermView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	LastProcKey=0;
	if (m_MouseSelectionMode && nRepCnt<2)	SetMouseSelectionCursor();

	if ((nFlags== 1 || nFlags==16385)  && nChar==27 && next_job==-53 && forcounter>3) forcounter=123456;
	else
	if (nFlags==27 && nChar==1 && next_job==-53 && forcounter>3) forcounter=123456;

	if (SendPredefKey(nChar&0x1FF,((GPC.EasyTCL==false)?0:MOD_EASYTCL)
		|(((GetAsyncKeyState(VK_CONTROL)&0xFF00)==0)?0:MOD_CONTROL)
		|(((GetAsyncKeyState(VK_SHIFT)&0xFF00)==0)?0:MOD_SHIFT)
		|(((GetAsyncKeyState(VK_RWIN)&0xFF00)==0 && (GetAsyncKeyState(VK_LWIN)&0xFF00)==0)?0:MOD_WIN)
		|(((alt_press)==0)?0:MOD_ALT)
		,nFlags)==0)
		CFormView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CGP_TermView::OnF10()
{
	SendPredefKey(VK_F10,(GPC.EasyTCL==false)?0:MOD_EASYTCL,0);
}

void CGP_TermView::OnTandemonoff()
{
	if (m_Comm.TandemFlag==FALSE) m_Comm.TandemFlag=TRUE; else m_Comm.TandemFlag=FALSE;
}

void CGP_TermView::OnUpdateTandemonoff(CCmdUI* pCmdUI)
{
//#ifdef BRIZ
//	pCmdUI->Enable(TRUE);
//#else
    if (pCmdUI->m_pSubMenu != NULL)
	{
        pCmdUI->m_pMenu->EnableMenuItem(pCmdUI->m_nIndex,
            MF_BYPOSITION | (GPC.AdmIsOn ? MF_ENABLED : MF_GRAYED));
	}
//#endif
	pCmdUI->SetCheck(m_Comm.TandemFlag);
}

void CGP_TermView::OnClsscr0()
{
	GetDocument()->GetActiveScreen()->ClearScreen();
	GetDocument()->SelectScreen(0);
	GetDocument()->SetMainScreen(0);
	GetDocument()->GetMainScreen()->ClearScreen();
}

void CGP_TermView::OnCreateframe()
{
	int IdDlg;
	for(IdDlg=0;IdDlg<MAX_OBJDLG && GetDocument()->a_GPObjDialog[IdDlg]!=NULL || GetDocument()->a_GPObjFrame[IdDlg]!=NULL;IdDlg++);
	char strinit[1100];
	*strinit=0;

	FILE *tmp=fopen("Create.ini","rt");
	if (tmp!=NULL)
	{
		char tmpstr[1000];
		const char  *m_CmpStr="CREATION STRING FOR _FRAME";
		int cmplen=(int)strlen(m_CmpStr);
		*tmpstr=0;

		while(!*tmpstr && fgets(tmpstr,990,tmp)!=NULL)
		{
			tmpstr[cmplen]=0;
			_strupr(tmpstr);
			if (strcmp(m_CmpStr,tmpstr)==0)
			{
				cmplen=sprintf(strinit,"%d,-1,%s",IdDlg,tmpstr+cmplen+1);
				if (cmplen && strinit[--cmplen]<' ') strinit[cmplen]=0;
				if (cmplen && strinit[--cmplen]<' ') strinit[cmplen]=0;
				break;
			}
		}
		fclose(tmp);
	}
	if (!*strinit)
		sprintf(strinit,"%d,-1,STYLE=WS_VISIBLE|WS_EX_CLIENTEDGE|WS_OVERLAPPEDWINDOW;RECT=20,20,350,350",IdDlg);



	if (IdDlg<MAX_OBJDLG)
	{
		CreateObjFrame(IdDlg,strinit);
		GetDocument()->a_GPObjFrame[IdDlg]->RunEditor();
	}
}

void CGP_TermView::OnCreatedlg()
{
	int IdDlg;
	for(IdDlg=0;IdDlg<MAX_OBJDLG && GetDocument()->a_GPObjDialog[IdDlg] || GetDocument()->a_GPObjFrame[IdDlg]!=NULL;IdDlg++);
	char strinit[1100];
	*strinit=0;

	FILE *tmp=fopen("Create.ini","rt");
	if (tmp!=NULL)
	{
		char tmpstr[1000];
		const char  *m_CmpStr="CREATION STRING FOR _DIALOG";
		int cmplen=(int)strlen(m_CmpStr);
		*tmpstr=0;

		while(!*tmpstr && fgets(tmpstr,990,tmp)!=NULL)
		{
			tmpstr[cmplen]=0;
			_strupr(tmpstr);
			if (strcmp(m_CmpStr,tmpstr)==0)
			{
				cmplen=sprintf(strinit,"%d,-1,%s",IdDlg,tmpstr+cmplen+1);
				if (cmplen && strinit[--cmplen]<' ') strinit[cmplen]=0;
				if (cmplen && strinit[--cmplen]<' ') strinit[cmplen]=0;
				break;
			}
		}
		fclose(tmp);
	}
	if (!*strinit)
		sprintf(strinit,"%d,-1,STYLE=WS_VISIBLE|DS_CENTER|DS_NOMODAL|WS_OVERLAPPEDWINDOW|DS_SETFONT;RECT=0,0,150,150",IdDlg);

	if (IdDlg<MAX_OBJDLG)
	{
		CreateObjDlg(IdDlg,strinit);
		if (GetDocument()->a_GPObjDialog[IdDlg])
		GetDocument()->a_GPObjDialog[IdDlg]->RunEditor();
	}
}

void CGP_TermView::OnUpdateCreatedlg(CCmdUI* pCmdUI)
{
//#ifdef BRIZ
//	pCmdUI->Enable(TRUE);
//#else
	pCmdUI->Enable(GPC.AdmIsOn);
    if (pCmdUI->m_pSubMenu != NULL)
	{
        pCmdUI->m_pMenu->EnableMenuItem(pCmdUI->m_nIndex,
            MF_BYPOSITION | (GPC.AdmIsOn ? MF_ENABLED : MF_GRAYED));
	}
//#endif
}

BOOL CALLBACK SvcEnumChildProc(HWND hwnd,    LPARAM lParam)
{
	PFINDWNDBYPROC pF=(PFINDWNDBYPROC)lParam;
	BOOL ret=TRUE;
	DWORD dwProcID=0;
	GetWindowThreadProcessId(hwnd,&dwProcID);
	if (pF->dwProcID==dwProcID)
	{
		pF->dwRetStyle=::GetWindowLong(hwnd,GWL_STYLE);
		pF->hwReturn=hwnd;
		pF->ret=TRUE;
		ret=FALSE;
	}
	return ret;
}


void CGP_TermView::SafeInit()
{
	CString tmpCS;
	GPScreen *s=GetDocument()->GetMainScreen();
	tmpCS=AfxGetApp()->GetProfileString(GPC.cs_RegTermViewSetName, "m_FontName","Courier new");
	FontTable.InitFontTable(tmpCS,s);
	PrintFontTable.InitFontTable(tmpCS,s);

	GPC.m_uPixelPerPoint=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_uPixelPerPoint",2);

	#ifdef W_95
	#else
		#ifdef W_98
		#else

		tmpCS=AfxGetApp()->GetProfileString(m_Comm.GPSectionName, "STUPSVC","");
		tmpCS=tmpCS.Trim();
		if (tmpCS!="")
		{
			CString csParams=AfxGetApp()->GetProfileString(m_Comm.GPSectionName, "STUPSVCPARAMS","");
			UINT m_SvcWaitOption=AfxGetApp()->GetProfileInt(m_Comm.GPSectionName, "STUPSVCWAIT",1);


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
						&& ssStatus.dwCurrentState != SERVICE_RUNNING) 
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
						ControlService(schService,SERVICE_CONTROL_CONTINUE,(LPSERVICE_STATUS)&ssStatus);
					case SERVICE_CONTINUE_PENDING:
						while (dwTickCount++<50 && ssStatus.dwCurrentState == SERVICE_CONTINUE_PENDING) 
						{ 
							Sleep( 500 );
							if (!QueryServiceStatusEx(schService,SC_STATUS_PROCESS_INFO,(LPBYTE)&ssStatus, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded ) )
								ssStatus.dwCurrentState=SERVICE_STOPPED;
						}
						dwTickCount=0;
						break;
					case SERVICE_START_PENDING:
						if (m_SvcWaitOption)
							while (dwTickCount++<50 && ssStatus.dwCurrentState == SERVICE_START_PENDING) 
							{ 
								Sleep( 500 );
								if (!QueryServiceStatusEx(schService,SC_STATUS_PROCESS_INFO,(LPBYTE)&ssStatus, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded ) )
									ssStatus.dwCurrentState=SERVICE_STOPPED;
							}
						dwTickCount=0;
						break;
					case SERVICE_STOP_PENDING:
						while (dwTickCount++<50 && ssStatus.dwCurrentState == SERVICE_STOP_PENDING) 
						{ 
							Sleep( 500 );
							if (!QueryServiceStatusEx(schService,SC_STATUS_PROCESS_INFO,(LPBYTE)&ssStatus, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded ) )
								ssStatus.dwCurrentState=SERVICE_STOPPED;
						}
						dwTickCount=0;
					//case SERVICE_STOPPED:
					default:
						{
							char *args=NULL;
							char *aargs[20]={0};
							DWORD dwNArgs=0;
							if (csParams!="")
							{
								args=new char [csParams.GetLength()+tmpCS.GetLength()+1000];
								aargs[dwNArgs++]=args;
								strcpy(args,tmpCS);
								char *tmpOut=args;
								while(*tmpOut) tmpOut++;
								tmpOut++;
								const char *srcParam=csParams;
								while(*srcParam && *srcParam!='"') srcParam++;
								if (*srcParam=='"') srcParam++;
								aargs[dwNArgs]=tmpOut;
								while(*srcParam)
								{
									if (*srcParam=='\\' && (srcParam[1]=='\\' || srcParam[1]=='"'))
									{
										srcParam++;
										*(tmpOut++)=*(srcParam++);
									}
									else
									if (*srcParam=='"')
									{
										*(tmpOut++)=0;
										while(*(++srcParam) && *srcParam!='"');
										if (*srcParam=='"') srcParam++;
										aargs[++dwNArgs]=tmpOut;
									}
									else *(tmpOut++)=*(srcParam++);
								}
								aargs[++dwNArgs]=NULL;
								*(tmpOut++)=0;
							}

							ssStatus.dwCurrentState= SERVICE_STOP;
							if (StartService(schService, dwNArgs,dwNArgs?(LPCSTR *)aargs:NULL)) 
							{
								if (QueryServiceStatusEx(schService, SC_STATUS_PROCESS_INFO,(LPBYTE)&ssStatus, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded ) && m_SvcWaitOption)  
								{
									while (dwTickCount++<30 && ssStatus.dwCurrentState != SERVICE_RUNNING) 
									{ 
										Sleep( 500 );
										if (!QueryServiceStatusEx(schService,SC_STATUS_PROCESS_INFO,(LPBYTE)&ssStatus, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded ) )
											ssStatus.dwCurrentState=SERVICE_STOPPED;
									} 
								}
							}
							if (args) delete []args;
							FINDWNDBYPROC fwp={0};
							fwp.dwProcID=ssStatus.dwProcessId;
							if (m_SvcWaitOption>1 && ssStatus.dwCurrentState != SERVICE_STOPPED)
							{
								BOOL bWait=TRUE;
								dwTickCount=0;
								do
								{
									fwp.hwReturn=NULL;
									fwp.ret=FALSE;
									EnumChildWindows(::GetDesktopWindow(),  SvcEnumChildProc, (LPARAM)(&fwp));
									switch(m_SvcWaitOption)
									{
									case 0://Not
										break;
									case 1://SStart
										break;
									case 2://Wnd Destroy
										if (!fwp.ret) bWait=FALSE;
										break;
									case 3://Wnd Hide
										if (fwp.ret || (fwp.ret && (fwp.dwRetStyle&WS_VISIBLE)!=WS_VISIBLE)) bWait=FALSE;
										break;
									case 4://Wnd Show
										if (fwp.ret && (fwp.dwRetStyle&WS_VISIBLE)==WS_VISIBLE) bWait=FALSE;
										break;
									}
									if (bWait) Sleep(100);
								}
								while(bWait && dwTickCount++<300);
							}
						}
						break;
					}

					CloseServiceHandle(schService); 

					if (ssStatus.dwCurrentState != SERVICE_RUNNING) 
					{
						csParams.Format("Service '%s' not started. \nCurrent State: %d\nExit Code: %d\nService Specific Exit Code: %d\nCheck Point: %d\nWait Hint: %d\n",
							 tmpCS,ssStatus.dwCurrentState, ssStatus.dwWin32ExitCode, 
							 ssStatus.dwServiceSpecificExitCode, ssStatus.dwCheckPoint, ssStatus.dwWaitHint);
						AfxMessageBox(csParams);
					}
				}

			}
			CloseServiceHandle(schSCManager);
		}

//	SetDlgItemText(IDC_EDITSVCNAME2,	AfxGetApp()->GetProfileString(GPc->GPSectionName, "SHDNSVC",""));
//	CheckDlgButton(IDC_CHECKSVCASK,		AfxGetApp()->GetProfileInt(GPc->GPSectionName, "CHECKSVCASK",0));

		#endif
	#endif


	if (!m_ODContextsArray) m_ODContextsArray=new CODContextArray;
	GPC.m_WideOn2Pos=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_WideOn2Pos",1);
#ifdef BRIZ
	int cc=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "BRIZINITA",1);
#else
	int cc=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "INITA",0);
#endif

//#ifdef BRIZ
//	GPC.AdmIsOn=1;
//#else
	GPC.AdmIsOn=(cc==1)?1:0;
//#endif

	int nc;
	#ifdef RUS
		nc=0;
	#else
		nc=1;
	#endif
	GPC.m_USEMBCONV=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV",nc);
	GPC.m_USEMBCONV2=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV2",nc);
	GPC.m_USEMBCONV3=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV3",0);
	GPC.m_CONV3PCSRV.dwType=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV3PCSRV",GPC.MBC3_NONE);
	GPC.m_CONV3SRVPC.dwType=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV3SRVPC",GPC.MBC3_NONE);

	GPC.m_CONV3PCSRV.dwCP=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV3PCSRV_CP",GPC.m_CurCodePage);
	GPC.m_CONV3SRVPC.dwCP=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV3SRVPC_CP",GPC.m_CurCodePage);

	GPC.m_CONV3PCSRV.dwConv=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV3PCSRV_CONV",(GPC.m_CurMBInvert)?LCMAP_BYTEREV:0);
	GPC.m_CONV3SRVPC.dwConv=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV3SRVPC_CONV",(GPC.m_CurMBInvert)?LCMAP_BYTEREV:0);

	GPC.m_CONV3PCSRV.dwLang=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV3PCSRV_LANG",LANG_NEUTRAL);
	GPC.m_CONV3SRVPC.dwLang=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV3SRVPC_LANG",LANG_NEUTRAL);

	GPC.m_CONV3PCSRV.dwSubLang=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV3PCSRV_SUBLANG",SUBLANG_NEUTRAL);
	GPC.m_CONV3SRVPC.dwSubLang=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_USEMBCONV3SRVPC_SUBLANG",SUBLANG_NEUTRAL);

	GPC.SetMBConv3(GPC.m_CONV3SRVPC.dwType,GPC.m_CONV3PCSRV.dwType);

	m_TermCap.SetCurrentTerminalId(m_Comm.m_TerminalID);
	m_CRLFflag=AfxGetApp()->GetProfileInt(m_Comm.GPSectionName, "m_CheckCRLF",0);
	m_CRLFflag2=AfxGetApp()->GetProfileInt(m_Comm.GPSectionName, "m_CheckCRLF2",0);
	GPC.m_dwAltFlag=AfxGetApp()->GetProfileInt(m_Comm.GPSectionName, "dwAltFlag",0);

	GPC.ParseCommandLine(0x0044,GetCommandLine());

	for(nc=0;nc<5 && m_Comm.IsConnected()==FALSE;nc++)
	{
		m_Comm.GPConnect();
		Sleep(AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "InitDelay",500));
		if (m_Comm.Get_commType()==GPCT_COMPORT) nc=5;
	}

	tmpCS=AfxGetApp()->GetProfileString(m_Comm.GPSectionName, "TERMTITLE","");
	if (tmpCS!="") GPC.termCaptionInit=GPC.termCaption=tmpCS;
	GetDocument()->SetTitle(GPC.termCaption);

	tmpCS=AfxGetApp()->GetProfileString(m_Comm.GPSectionName, "MSGBOXTITLE","");
	if (tmpCS!="") GPC.MsgBoxCaptionInit=GPC.MsgBoxCaption=tmpCS;
	
	tmpCS=AfxGetApp()->GetProfileString(m_Comm.GPSectionName, "ERRBOXTITLE","");
	if (tmpCS!="") GPC.ErrBoxCaptionInit=GPC.ErrBoxCaption=tmpCS;


	GPC.DelimiterIn1=m_Comm.DelimiterIn1;
	GPC.csDelimiterIn1.Format("%c",GPC.DelimiterIn1);
	GPC.DelimiterIn2=m_Comm.DelimiterIn2;
	GPC.csDelimiterIn2.Format("%c",GPC.DelimiterIn2);
	GPC.DelimiterIn3=m_Comm.DelimiterIn3;
	GPC.csDelimiterIn3.Format("%c",GPC.DelimiterIn3);
	GPC.DelimiterIn4=m_Comm.DelimiterIn4;
	GPC.csDelimiterIn4.Format("%c",GPC.DelimiterIn4);
	GPC.DelimiterIn5=m_Comm.DelimiterIn5;
	GPC.csDelimiterIn5.Format("%c",GPC.DelimiterIn5);
	GPC.DelimiterIn6=m_Comm.DelimiterIn6;
	GPC.csDelimiterIn6.Format("%c",GPC.DelimiterIn6);

	GPC.DelimiterSrc1=m_Comm.DelimiterSrc1;
	GPC.DelimiterSrc2=m_Comm.DelimiterSrc2;
	GPC.DelimiterSrc3=m_Comm.DelimiterSrc3;
	GPC.DelimiterSrc4=m_Comm.DelimiterSrc4;
	GPC.DelimiterSrc5=m_Comm.DelimiterSrc5;
	GPC.DelimiterSrc6=m_Comm.DelimiterSrc6;
	
	if (!CommFnIsRun)
		AfxBeginThread(CommunicateFn,(LPVOID)this);

	if (!CommFn3IsRun)
		AfxBeginThread(CommunicateFnIO,(LPVOID)this);

	if (!RefreshThreadIsRun)
		AfxBeginThread(RefreshThreadFn,(LPVOID)this);


	Sleep(AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "InitDelay",500));

	GPC.EasyTCL=true;
	OnTranslateTcl();

	ReadColor127();

	if (GPC.m_ScrToolTip==NULL)
	{
		GPC.m_ScrToolTip=new CGPToolTipCtrl;
		GPC.m_ScrToolTip->GPCreate(this->m_hWnd,0,NULL,NULL);
		GPC.m_ScrToolTip->Activate(TRUE);
	}

	EnableToolTips(TRUE);
	EnableTrackingToolTips(TRUE);

	CursorTimerDelay=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "CursorDelay",200);

	GPC.DefFrgColorInd=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_DefFrgClr",7);
	GPC.DefFrgColor=cFEtalon[GPC.DefFrgColorInd];
	s->SetChrColorIndex(GPC.DefFrgColorInd,0);
	GPC.DefBkgColorInd=AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_DefBkgClr",0);
	GPC.DefBkgColor=cBEtalon[GPC.DefBkgColorInd];
	s->SetBkgColorIndex(GPC.DefBkgColorInd,0);

	KillTimer(CURSOR_TIMER_ID);
	SetTimer( CURSOR_TIMER_ID, CursorTimerDelay, NULL);
	KillTimer(REFRESH_TIMER_ID);
	SetTimer( REFRESH_TIMER_ID, REFRESH_TIMER_DELAY, NULL);
	KillTimer(PORT_TIMER_ID);
	SetTimer( PORT_TIMER_ID, PORT_TIMER_DELAY, NULL);

	BeepFlag=true;
	if (AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_CheckBeep",1)!=1)	BeepFlag=false;

	if (m_GPMenu==NULL)	m_GPMenu=new GPMenu(GPC.m_hViewWnd,0);
	m_GPMenu->Fill_mArrMenu(FALSE);
	m_ViewMode&=(0xFFFF0000|GPVIEWMODE_TERMINAL);
	CreateInputOutputDlg();

	m_ODContextsArray->LoadContext("Default", "");
	m_ODContextsArray->LoadContext("DefaultMenu", "");
	m_ODContextsArray->pTerminalMenuContext=m_ODContextsArray->LoadContext(GPC.csODCTerminalMenuName, "");
	if (!m_ODContextsArray->pTerminalMenuContext)
		AfxMessageBox("Can't load OwnerDraw context for terminal menu \"ODC\\TerminalMenu.ODC\"! The standard menu will be used.",MB_OK|MB_APPLMODAL|MB_ICONEXCLAMATION);
	m_ODContextsArray->LoadContext("CustomMenu", "");
 	m_ODContextsArray->LoadContext("Cursor", "");


	CMenu *tmpMenu=AfxGetMainWnd()->GetMenu();
	if (tmpMenu)
	{
		HMENU tmpContext=::GetSubMenu(tmpMenu->m_hMenu,1);
		if (tmpContext)
		{
			int nItems=::GetMenuItemCount(tmpContext);
			int insPos=-1;
			int m;
			for(m=0;m<nItems && insPos==-1;m++)
			{
				DWORD id=::GetMenuItemID(tmpContext,m);
				if (id==IDM_ENABLECONTEXTMENU) insPos=++m;

				if (id==-1 || insPos>=0)
				{
					if (!GPC.m_pContextMenu && m_GPMenu)
					{
						GPC.m_pContextMenu=new CGPContextMenu(m_GPMenu);
						if (GPC.m_pContextMenu) GPC.m_pContextMenu->Load(GPC.contmenuFileName);
					}
					if (GPC.m_pContextMenu && ::GetSubMenu(tmpContext,m)==GPC.m_pContextMenu->m_Menu)
					{
						::RemoveMenu(tmpContext,m,MF_BYPOSITION);
						insPos=m;
					}
				}
			}
			if (insPos<0) insPos=nItems;

			MENUITEMINFO mi={0};
			//mi.cbSize=sizeofMENUITEMINFO;
			mi.cbSize=sizeof(MENUITEMINFO);
			#ifdef W_95
				mi.fMask=MIIM_SUBMENU|MIIM_TYPE;
				mi.fType=MFT_STRING;
			#else
				#ifdef W_NT
					mi.fMask=MIIM_SUBMENU|MIIM_TYPE;
					mi.fType=MFT_STRING;
				#else
					mi.fMask=MIIM_SUBMENU|MIIM_STRING;
				#endif
			#endif

			#ifdef RUS
				mi.dwTypeData="Контекстное меню";
			#else
				mi.dwTypeData="User Menu";
			#endif
			mi.cch=(int)strlen((LPCSTR)mi.dwTypeData);
			mi.hSubMenu=GPC.m_pContextMenu->m_Menu;
			m=::InsertMenuItem(tmpContext,insPos,TRUE,&mi);
			if (!GPC.m_pContextMenu && m_GPMenu)
			{
				GPC.m_pContextMenu=new CGPContextMenu(m_GPMenu);
				if (GPC.m_pContextMenu) GPC.m_pContextMenu->Load(GPC.contmenuFileName);
			}
		}
	}

	m_GPMenu->SetODCForTerminalMenu(m_ODContextsArray->pTerminalMenuContext, m_GPMenu->m_ArrPopupMenu[0]->m_hMenu,0);

	//login dialog
	//GPC.ParseCommandLine(0x0020,GetCommandLine());

	GPC.ParseCommandLine(0xFFF020,GetCommandLine());

	tmpCS=AfxGetApp()->GetProfileString(m_Comm.GPSectionName, "CMDLINE","");
	
	if (tmpCS!="") GPC.ParseCommandLine(0xFFFFFFF0,tmpCS);

	m_dwParseInitStrFlag=1;
}

UINT CommunicateFn(LPVOID pParam)
{
	CGP_TermView *th=(CGP_TermView *)pParam;
	th->CommFnIsRun=TRUE;
	try
	{
		char * InputPool;
		char * ReadPool;
		InputPool=new char [NBINREADPOOL+10000];
		ReadPool=new char [NBINREADPOOL+10000];
		UINT curpos=0;
		unsigned long nre=0;
		UINT i;

		Sleep(500);
		HANDLE m_WaitComm;
		//CFile tmp;
		//tmp.Open("TMP.LOG",CFile::modeWrite|CFile::shareExclusive   |CFile::typeText   );
		m_WaitComm=CreateEvent(NULL, TRUE, TRUE, "m_WaitComm");
		int WFlag=0;

		do
		{
			EnterCriticalSection(&th->m_CSInputSema);
			try
			{
				nre=0;
				if ((m_Comm.m_ConnectionFlag&0x10000)==0 && curpos<NBINREADPOOL &&  (nre=m_Comm.GPRead(ReadPool,NBINREADPOOL-curpos))>0)
				{
					//			tmp.Write("ReadPool\n",9);
					//			tmp.Write(th->ReadPool,nre);
					if (nre!=1234567890)
					{
						WFlag=1;
						for(i=0;curpos<NBINREADPOOL && i<nre;i++,curpos++)
							InputPool[curpos]=ReadPool[i];
					}
					else
					{
						LeaveCriticalSection(&th->m_CSInputSema);
						nre=0;
						if (AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_CheckExit",1)==0)
							GPC.Flags|=GP_CUR_EXITFLAG;

						if ((GPC.Flags&GP_CUR_EXITFLAG)!=GP_CUR_EXITFLAG && AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_CheckLostLine",1)==1)
						{
						#ifdef RUS
							AfxGetMainWnd()->MessageBox("Потеряна связь с сервером",GPC.ErrBoxCaption,MB_OK|MB_ICONERROR|MB_SYSTEMMODAL);
						#else
							AfxGetMainWnd()->MessageBox("Connection lost",GPC.ErrBoxCaption,MB_OK|MB_ICONERROR|MB_SYSTEMMODAL);
						#endif
						}

						::SendMessage(GPC.m_hViewWnd,GPM_NETCRASH,0,0);

						GPC.Flags|=GP_CUR_COMMFLAG;

						if (WaitForSingleObject(m_WaitAll,1500)==WAIT_TIMEOUT )
						{
							if (WFlag)
								AfxGetApp()->GetMainWnd()->PostMessage(WM_CLOSE);
							break;
						}
						else
						{
							AfxGetApp()->GetMainWnd()->PostMessage(WM_CLOSE);
							break;
						}

					}
				}
			}
			catch(...)
			{
				GPC.m_ErrReport.GPWriteErrorLog("GLOBAL CGP_TermView", "CommunicateFn","2434");
			}
			LeaveCriticalSection(&th->m_CSInputSema);

			EnterCriticalSection(&th->m_CSRemap);
			try
			{
				GPC.m_IOFileArray.ReadIOFiles();

				if (curpos>0)
				{
					if (th->LockPos==0)
					{
						for(;th->LockPos<curpos;th->LockPos++)
							th->InputBuffer[th->LockPos]=InputPool[th->LockPos];
						curpos=0;
					}
					else
					{
						UINT i=0;
						for(;th->LockPos<NBINREADPOOL-1 && i<curpos;th->LockPos++,i++)
							th->InputBuffer[th->LockPos]=InputPool[i];
						UINT tmpcurpos=0;
						for(;i<curpos;tmpcurpos++,i++)
							InputPool[tmpcurpos]=InputPool[i];
						curpos=tmpcurpos;
					}
				}
			}
			catch(...)
			{
				GPC.m_ErrReport.GPWriteErrorLog("GLOBAL CGP_TermView", "CommunicateFn","2455");
			}
			LeaveCriticalSection(&th->m_CSRemap);

			ResetEvent(m_WaitComm);
			WaitForSingleObject(m_WaitComm,25);

		}	while(!m_StopWorking);

		//tmp.Close();
		if (m_WaitComm) CloseHandle(m_WaitComm);
		m_WaitComm=NULL;
		if (InputPool!=NULL) delete[] InputPool;
		InputPool=NULL;
		if (ReadPool!=NULL) delete[] ReadPool;
		ReadPool=NULL;
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GLOBAL CGP_TermView", "CommunicateFn","2474");
	}
	th->CommFnIsRun=FALSE;

	return 0;
}

UINT RefreshThreadFn(LPVOID pParam)
{
	CGP_TermView *th=(CGP_TermView *)pParam;
	th->RefreshThreadIsRun=TRUE;
	HANDLE m_WaitRefresh;
	m_WaitRefresh=CreateEvent(NULL, TRUE, TRUE, "m_WaitRefresh");
	CGP_TermDoc *m_Doc=th->GetDocument();
	do
	{
		EnterCriticalSection(&th->m_CSRefresh);
		try
		{
			GPScreen *scr=m_Doc->GetMainScreen();
			if (scr)
			{
				if (scr->GetNeedRedraw())
				{
					scr->SetNeedRedraw(FALSE);
					scr->RedrawScreen();
					scr->InvalidateScreenBorder();
				}

				if (scr->GetNeedRepaint())
				{
					scr->SetNeedRepaint(FALSE);
					Size sc=scr->GetScreenSize();
					int *nlefts=new int [2*sc.Height];
					int *nrights=nlefts+sc.Height;
					FillMemory(nlefts,2*sizeof(int)*sc.Height,128);
					int x,y;
					int posy=0;
					for(y=0,posy=0;y<sc.Height;posy+=sc.Width,y++)
					{
						for(x=0;x<sc.Width && !(scr->InvPoints[posy+x]&0x2);x++);
						if (x<sc.Width) 
						{
							int xStop=nlefts[y]=x;
							for(x=sc.Width-1;x>xStop && !(scr->InvPoints[posy+x]&0x2);x--);
							nrights[y]=x;
						}
					}

					for(y=0;y<sc.Height;y++)
						if (nrights[y]!=-2139062144)
						{
							RECT refrect;
							refrect.bottom=refrect.top=y;
							refrect.left=nlefts[y];
							refrect.right=nrights[y];
							for(y++;y<sc.Height && nrights[y]!=-2139062144;y++)
							{
								refrect.bottom=y;
								if (refrect.left>nlefts[y]) refrect.left=nlefts[y];
								if (refrect.right<nrights[y]) refrect.right=nrights[y];
							}
							int x2,y2;
							int pos2=refrect.top*sc.Width+refrect.left;
							int delta2=sc.Width-refrect.right+refrect.left-1;
							for(y2=refrect.top;y2<=refrect.bottom;y2++,pos2+=delta2)
								for(x2=refrect.left;x2<=refrect.right;x2++,pos2++)
									scr->InvPoints[pos2]&=(0xFFFFFFFF^0x2);

							refrect.top=(LONG)(((REAL)(refrect.top-1))*scr->CharPlaceSize.Height+scr->TopBorderSafe*scr->CharPlaceSize.Height);
							refrect.bottom=(LONG)(((REAL)(refrect.bottom+2))*scr->CharPlaceSize.Height+scr->TopBorderSafe*scr->CharPlaceSize.Height);
							refrect.left=(LONG)(((REAL)(refrect.left-1))*scr->CharPlaceSize.Width+scr->LeftBorderSafe*scr->CharPlaceSize.Width);
							refrect.right=(LONG)(((REAL)(refrect.right+2))*scr->CharPlaceSize.Width+scr->LeftBorderSafe*scr->CharPlaceSize.Width);
							::InvalidateRect(th->m_hWnd,&refrect,FALSE);
						}
					delete []nlefts;
				}
			}
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("GLOBAL CGP_TermView", "RefreshThreadFn","");
		}
		LeaveCriticalSection(&th->m_CSRefresh);
		ResetEvent(m_WaitRefresh);
		WaitForSingleObject(m_WaitRefresh,75);
	}
	while(!m_StopWorking);

	if (m_WaitRefresh) CloseHandle(m_WaitRefresh);
	m_WaitRefresh=NULL;
	th->RefreshThreadIsRun=FALSE;
	return 0;
}

UINT CommunicateFnIO(LPVOID pParam)
{
	CGP_TermView *th=(CGP_TermView *)pParam;
	th->CommFn3IsRun=TRUE;
	Sleep(500);
	HANDLE m_WaitIOFile;
	m_WaitIOFile=CreateEvent(NULL, TRUE, TRUE, "m_WaitIOFile");
	do
	{
		try
		{
			GPC.m_IOFileArray.ReadIOFiles();
			ResetEvent(m_WaitIOFile);
			WaitForSingleObject(m_WaitIOFile,100);
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("GLOBAL CGP_TermView", "CommunicateFnIO","");
		}
	}
	while(!m_StopWorking);

	if (m_WaitIOFile) CloseHandle(m_WaitIOFile);
	m_WaitIOFile=NULL;
	th->CommFn3IsRun=FALSE;

	return 0;
}

void CGP_TermView::DoRemappingInput()
{
	EnterCriticalSection(&m_CSRemap);
	try
	{
		if (LockRemappingFlag==0 && RemappingInputInProc==false && LockPos>0)
		{
			RemappingInputInProc=true;
			int nLeave=RemappingInput(LockPos);
			if (nLeave>0 && LockPos!=nLeave)
			{
				int delta=LockPos-nLeave;
				int i;
				for(i=0;i<nLeave;i++)
					InputBuffer[i]=InputBuffer[i+delta];
			}
			else
			if (nLeave<0)
			{
				nLeave=0;
			}
			LockPos=nLeave;
			RemappingInputInProc=false;
		}
	}
	catch(...)
	{

		char tmps[2000];
		sprintf(tmps,"ERROR GP_TermView.cpp(2616)  %d",GetLastError());

		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
		);

		GPC.m_ErrReport.GPWriteErrorLog("CGP_TermView", "DoRemappingInput",(const char *)lpMsgBuf);
		LocalFree( lpMsgBuf );
		
		RemappingInputInProc=false;
	}
	LeaveCriticalSection(&m_CSRemap);
}


void CGP_TermView::OnClose()
{
}

void CGP_TermView::OnOlesettingsdlg()
{
	CDlgOLESet dlg;
	dlg.DoModal();
}

void CGP_TermView::OnTermHide()
{
	AfxGetMainWnd()->ShowWindow(AfxGetMainWnd()->IsWindowVisible()?SW_HIDE:SW_RESTORE);
}

void CGP_TermView::OnRemovealldlg()
{
	GetDocument()->RemoveAllDlg();
}

void CGP_TermView::CreateObjDlg(UINT iId, char *iInitStr)
{
	int IdParent=0;
	int IdDlg=iId;
	m_LastScanf=sscanf(iInitStr,"%d,%d",&IdDlg,&IdParent);

	CWnd *tmpParent=CWnd::FromHandle(GPC.m_hViewWnd);
	if (GPC.NextParentFromOLE!=NULL) tmpParent=CWnd::FromHandle(GPC.NextParentFromOLE);

	GetDocument()->a_GPObjType[IdDlg]=0;
	if (IdParent>=0 && IdParent<MAX_OBJDLG && IdParent!=IdDlg)
	{
		if (GetDocument()->a_GPObjType[IdParent]==0)
		{
			if (GetDocument()->a_GPObjDialog[IdParent]!=NULL && GPC.NextParentFromOLE==NULL)
				tmpParent=CWnd::FromHandle(GetDocument()->a_GPObjDialog[IdParent]->m_hWnd);
		}
		else
		{
			if (GetDocument()->a_GPObjFrame[IdParent]!=NULL && GPC.NextParentFromOLE==NULL)
				tmpParent=CWnd::FromHandle(GetDocument()->a_GPObjFrame[IdParent]->m_hWnd);
		}
	}

	GPC.NextParentFromOLE=NULL;
	UINT iS=0,iSex=0,PN=0;
	CRect iRe(50,50,150,100);
	char Capt[1000];*Capt=0;
	char m_CLSID[1000];*m_CLSID=0;
	DWORD tmpScale=GPC.m_GUISet.Scale;
	GPUnit::GetInitParam(NULL,0,iInitStr,iS,iSex,iRe,Capt,&PN,m_CLSID,tmpScale);
	BOOL visflg=FALSE;
	if ((iS&WS_VISIBLE)==WS_VISIBLE)
	{
		visflg=TRUE;
		iS^=WS_VISIBLE;
		char *tmppos=strstr(iInitStr,"WS_VISIBLE");
		if (tmppos!=NULL) *tmppos='_';
	}

	if (GetDocument()->a_GPObjDialog[IdDlg]==NULL && GetDocument()->a_GPObjFrame[IdDlg]==NULL)
	{
		GPObjDialog *dlg=NULL;
		dlg=GetDocument()->a_GPObjDialog[IdDlg]=new GPObjDialog(IdDlg,iInitStr,tmpParent);

		if (dlg)
		{
			GPDLGTEMPLATEEX *lpdt;
			lpdt = (GPDLGTEMPLATEEX *)GlobalLock(GetDocument()->a_GPObjDialogHG[IdDlg]);
			lpdt->style = iS;

			if ((lpdt->style&WS_POPUP)!=WS_POPUP && (lpdt->style&WS_CHILD)!=WS_CHILD)
				lpdt->style|=WS_POPUP;
			lpdt->exStyle = iSex;
			lpdt->cDlgItems = 0;  // number of controls

			LOGFONT lftmp={0};
			TranslLOGFONT2(lftmp,iInitStr);

			lpdt->dlgVer=1;
			lpdt->signature=0xFFFF;
			lpdt->helpID =0;
			lpdt->menu=0;
			lpdt->windowClass=0;
			lpdt->title[0]=0;

			lpdt->pointsize =GPC.m_GUISet.UseDefault?8:GPC.m_GUISet.PointSize;
			lpdt->pointsize =(unsigned short)((lpdt->pointsize * tmpScale)/100);

			lpdt->x  =(short)(iRe.left*697*8/1046/lpdt->pointsize);
			lpdt->y =(short)(iRe.top*450*8/731/lpdt->pointsize);
			lpdt->cx = (short)(iRe.Width()*697*8/1046/lpdt->pointsize);
			lpdt->cy = (short)(iRe.Height()*450*8/731/lpdt->pointsize);

			lpdt->weight  =(unsigned short)lftmp.lfWeight;
			lpdt->italic  =lftmp.lfItalic;
			lpdt->charset  =lftmp.lfCharSet;
			MultiByteToWideChar (CP_ACP, 0, lftmp.lfFaceName , -1, lpdt->typeface, 32);

			if (GetDocument()->a_GPObjDialogHG[IdDlg]) GlobalUnlock(GetDocument()->a_GPObjDialogHG[IdDlg]);
			dlg->CreateIndirect ((GPDLGTEMPLATEEX *)GetDocument()->a_GPObjDialogHG[IdDlg],tmpParent);

			if (strstr(iInitStr,"DS_NOMODAL")==NULL && dlg->m_hWnd!=GPC.m_hViewWnd &&
				dlg->m_hWnd!=::GetDesktopWindow() && dlg->m_hWnd!=AfxGetMainWnd()->m_hWnd)
				{
					::EnableWindow(::GetParent(dlg->m_hWnd),FALSE);
					::EnableWindow(dlg->m_hWnd,TRUE);
				}

			if (visflg!=FALSE)
			{
				//ShowWindow((iStyle&WS_VISIBLE)==WS_VISIBLE?SW_SHOW:SW_HIDE);
				dlg->ShowWindow(SW_SHOW);
			}

			if (LockRemappingFlag>0) LockRemappingFlag--;
			SendChar('1');
		}
		else
		{
			GPC.m_ErrReport.GPWriteErrorLog2("Cant create dialog",iInitStr ,"");
			SendChar('0');
		}
	}
	else 
	{
		GPC.m_ErrReport.GPWriteErrorLog2("Dialog already exist",iInitStr ,"");
		SendChar('0');
	}

}

void CGP_TermView::CreateObjFrame(UINT iId, char *iInitStr)
{

	GPFrameWnd *dlg;
	if (GetDocument()->a_GPObjFrame[iId]==NULL && GetDocument()->a_GPObjDialog[iId]==NULL)
	{
		GetDocument()->a_GPObjFrame[iId]=dlg=new GPFrameWnd;
		GetDocument()->a_GPObjType[iId]=1;
		CWnd *tmp;
		if (GPC.NextParentFromOLE!=NULL) tmp=CWnd::FromHandle(GPC.NextParentFromOLE);
			else tmp=this;

		GPC.NextParentFromOLE=NULL;
		dlg->GPCreate(iId,iInitStr,tmp);
		//ShowWindow((iStyle&WS_VISIBLE)==WS_VISIBLE?SW_SHOW:SW_HIDE);
		//if ((iStyle&WS_VISIBLE)==WS_VISIBLE) dlg->ShowWindow(SW_SHOW);

		if (LockRemappingFlag>0) LockRemappingFlag--;
		SendChar('1');
	}
	else 
	{
		GPC.m_ErrReport.GPWriteErrorLog2("Frame already exist",iInitStr ,"");
		SendChar('0');
	}

}

void CGP_TermView::OnHelp()
{
#ifdef BRIZ
	_spawnlp(_P_DETACH, "HH", "HH", "BRIZ.chm", NULL );
#else
	_spawnlp(_P_DETACH, "HH", "HH", "GP_term.chm", NULL );
#endif

}

void CGP_TermView::OnHelpFinder()
{
#ifdef BRIZ
	_spawnlp(_P_DETACH, "HH", "HH", "BRIZ.chm", NULL );
#else
	_spawnlp(_P_DETACH, "HH", "HH", "GP_term.chm", NULL );
#endif
}

UINT CGP_TermView::SendPredefKey(UINT nChar, UINT nModif, UINT nFlg)
{
	UINT ret=0;
	UINT j=0;
	m_OutputCharDelay=1;

	if (m_TermCap.m_ArrKbd)
	{
		GPC.dwMBReposition=0;

		DWORD TermId=0;
		if (m_TermCap.CurrentTerminal) TermId=m_TermCap.CurrentTerminal->dwTermId;

		for(j=0;j<m_TermCap.m_uArrKbdCount;j++)
			if (m_TermCap.m_ArrKbd[j] && m_TermCap.m_ArrKbd[j]->dwTermId==TermId && (m_TermCap.m_ArrKbd[j]->dwFlags&0x1))
			{
				if (m_TermCap.m_ArrKbd[j]->dwVirtualKey==((nChar*0x10000)|nModif))
				{
					int ntimes=1;
					CString actionafter="";
					if (m_TermCap.m_ArrKbd[j]->csAction!="")
					{
						UINT i;
						for(i=0;i<CTermCap::uNKbdActions && CTermCap::cArrKbdActions[i]!=m_TermCap.m_ArrKbd[j]->csAction;i++);
						if (i<CTermCap::uNKbdActions)
						{
							NEAREST9X9 m_nearest={0};
							GetDocument()->GetMainScreen()->GetNearestChars(&m_nearest);
							switch(CTermCap::uKbdActions[i])
							{
							case TCKA_NONE:
								break;
							case TCKA_UP:
								if (m_nearest.top==0) actionafter="RIGHT";
								break;
							case TCKA_DOWN:
								if (m_nearest.top==0) actionafter="RIGHT";
								break;
							case TCKA_LEFT:
								if (m_nearest.left==0) ntimes++;
								break;
							case TCKA_RIGHT:
								if (m_nearest.right==0) ntimes++;
								break;
							case TCKA_DELETE:
								if (m_nearest.right==0) ntimes++;
								break;
							case TCKA_BACKSPACE:
								if (m_nearest.left==0) ntimes++;
								break;
							}
						}

					}
					while(ntimes-->0 || actionafter!="")
					{
						LastProcKey=1;
						GPC.cs_ScriptLine+=m_TermCap.m_ArrKbd[j]->Seq;
						GPC.cs_ScriptWaitLine="";
						GPC.cs_ScriptWaitLineCurrent="";
						GPC.dw_ScriptWaitFlag=0;
						DoScriptCommand();
						ret=m_TermCap.m_ArrKbd[j]->dwVirtualKey;
						if (actionafter!="" && ntimes==0)
						{
							for(j=0;j<m_TermCap.m_uArrKbdCount && !ntimes;j++)
								if (m_TermCap.m_ArrKbd[j] && m_TermCap.m_ArrKbd[j]->dwTermId==TermId 
									&& m_TermCap.m_ArrKbd[j]->dwFlags&0x1 && m_TermCap.m_ArrKbd[j]->csAction==actionafter)
									ntimes++;

							actionafter="";
						}
					}
					break;
				}
			}
	}
	return GP_HotKey::nTypeHotkey-j;
}

void CGP_TermView::OnShowdlgmethods()
{
	if (GPC.m_DlgMethods==NULL)
	{
		GPC.m_DlgMethods=new CDlgMethods(this);
		GPC.m_DlgMethods->Create(IDD_DLGMETHODS,this);
	}
	GPC.m_DlgMethods->ShowWindow(SW_SHOW);
}

LRESULT CGP_TermView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT lpr=TRUE;
	BOOL retFlag=FALSE;
	switch (message)
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
					m_ODContextsArray->PaintByDRAWITEMSTRUCT(gpu, wParam, lpds, m_GPMenu);
					return TRUE;
				}
			}
			else
			{
				GPUnit *gpu=GPC.m_Document->GetMainScreen()->GPGetWindowByNum(0)->GetUnitByNum(lpds->CtlID%50000);
				if (gpu && gpu->UnitType!=GPUnit::UT_CHECKLISTBOX)
				{
					m_ODContextsArray->PaintByDRAWITEMSTRUCT(gpu, wParam, lpds, m_GPMenu);
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
				//TRACE("%x\t %x\t %x\t %x\t %x\t %x\t \n",lpds->CtlID,lpds->CtlType,lpds->itemData,lpds->itemHeight,lpds->itemID,lpds->itemWidth);
				GPUnit *gpu=GPC.m_Document->GetMainScreen()->GPGetWindowByNum(0)->GetUnitByNum(0);
				if (gpu)
				{
					return m_ODContextsArray->MeasureItem(gpu, wParam, lpds, m_GPMenu);
				}
			}
			else
			{
				HWND ctrlHWND=::GetDlgItem(m_hWnd,lpds->CtlID);
				if (ctrlHWND)
				{
					GPUnit *gpu=GPC.m_Document->GetMainScreen()->GPGetWindowByNum(0)->GetUnitByNum(lpds->CtlID%50000);
					if (gpu)
					{
						return m_ODContextsArray->MeasureItem(gpu, wParam, lpds, m_GPMenu);
					}
				}
			}
		}
		break;
	case GPM_INVALIDATE:
		if (wParam==0) Invalidate();
		else CWnd::FromHandle((HWND)wParam)->Invalidate();
	break;

	case GPM_MFUPDATESIZE:
		if (m_hWnd && !pPreviewBitmap)
		{
			EnterCriticalSection(&m_CSRefresh);
			try
			{
				RECT viewRect;
				::GetClientRect(m_hWnd,&viewRect);
				int oldCx=viewRect.right-viewRect.left+1,oldCy=viewRect.bottom-viewRect.top+1;
				CWnd *m_mainwnd=AfxGetMainWnd();
				if (GPC.m_View->GetOptimalSize(oldCx,oldCy) && m_mainwnd)
				{
					CRect reMain; 
					m_mainwnd->GetWindowRect(&reMain);

					reMain.right+=oldCx-(viewRect.right-viewRect.left+1);
					reMain.bottom+=oldCy-(viewRect.bottom-viewRect.top+1);
					m_mainwnd->MoveWindow(&reMain,TRUE);

				}
				GPScreen *s=GetDocument()->GetMainScreen();
				if (!s)
				{
					GetDocument()->InitIfNone();
					s=GetDocument()->GetMainScreen();
				}
				if (s)
				{
					s->SetViewSize(oldCx,oldCy);
				}
			}catch(...)
			{;}
			LeaveCriticalSection(&m_CSRefresh);
		}
		return 1;

	case WM_SYSCHAR:
		switch(wParam)
		{
		#ifdef RUS
			case 'Ф':
			case 'ф':
			case 'П':
			case 'п':
			case 'В':
			case 'в':
		#else
			case 'f':
			case 'F':
			case 'E':
			case 'e':
			case 'V':
			case 'v':
		#endif
			break;
		default:
			retFlag=TRUE;
			break;
		}
	//	TRACE("WM_SYSCHAR %d %d\n",wParam,lParam);
		
		break;
	case WM_SYSKEYDOWN:
		if (::GetFocus()==m_hWnd)
			SendPredefKey(wParam&0x1FF,((GPC.EasyTCL==false)?0:MOD_EASYTCL)
				|(((GetAsyncKeyState(VK_CONTROL)&0xFF00)==0)?0:MOD_CONTROL)
				|(((GetAsyncKeyState(VK_SHIFT)&0xFF00)==0)?0:MOD_SHIFT)
				|(((GetAsyncKeyState(VK_RWIN)&0xFF00)==0 && (GetAsyncKeyState(VK_LWIN)&0xFF00)==0)?0:MOD_WIN)
				|MOD_ALT
				,lParam);

	//	TRACE("WM_SYSKEYDOWN %d %d\n",wParam,lParam);
		break;

	case WM_IME_CHAR:
		{
			unsigned short outc[5];
			*outc=wParam;

			char tmpsout[10];
			int nBytes=2;
			if (GPC.m_CurMBInvert)
			{
				tmpsout[0]=(BYTE)(wParam);
				tmpsout[1]=(BYTE)(wParam >> 8);
				GPC.MBConv3PCSrw(tmpsout, tmpsout);
				tmpsout[0]=GPC.chWideAnsiDos[tmpsout[0]];
				tmpsout[1]=GPC.chWideAnsiDos2[tmpsout[1]];
			}
			else
			{
				tmpsout[0]=(BYTE)(wParam >> 8);
				tmpsout[1]=(BYTE)(wParam );
				GPC.MBConv3PCSrw(tmpsout, tmpsout);
				tmpsout[0]=GPC.chWideAnsiDos[tmpsout[0]];
				tmpsout[1]=GPC.chWideAnsiDos2[tmpsout[1]];
			}
			if (nBytes)
			{
				GPC.dwMBReposition=tmpsout[0]*256+tmpsout[1];
				GetDocument()->GetMainScreen()->SetExPerfixPosition();
				int i;
				for(i=0;i<nBytes;i++)
				{
					if (m_Comm.TandemFlag==TRUE)
					{
						m_Comm.TandemFlag=FALSE;
						m_Comm.GPSendChar(tmpsout[i]);
						m_Comm.TandemFlag=TRUE;
					}
					else
						if (GPC.AjCheckState==0)
						{
							m_Comm.GPSendChar(tmpsout[i]);
						}
					else
					{
						if (KeybBufferSize<GP_KEYBBUFFSIZE) KeybBuffer[KeybBufferSize++]=tmpsout[i];
						if (BeepFlag)
							if (PlaySound("ding.wav", NULL, SND_ASYNC)==FALSE) MessageBeep( 0xFFFFFFFF);   // sound type);( 2000,  150);
					}
				}
			}
		}
		return 0;

	case WM_IME_COMPOSITION:
		::DefWindowProcW(m_hWnd,message,  wParam,  lParam);
		return 0;

	case WM_IME_ENDCOMPOSITION:
		::DefWindowProcW(m_hWnd,message,  wParam,  lParam);
		return 0;

	case WM_INPUTLANGCHANGEREQUEST:
		return ::DefWindowProc(m_hWnd,message,  wParam,  lParam);
		break;
	case WM_INPUTLANGCHANGE:
		return ::DefWindowProc(m_hWnd,message, wParam,  lParam);
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_APP_EXIT:
		case ID_VIEW_TOOLBAR:
		case ID_VIEW_DEVTOOLBAR:
		case ID_VIEW_STATUS_BAR:
		case ID_APP_ABOUT:
		case IDM_STATISTIC:
			AfxGetMainWnd()->PostMessage(WM_COMMAND,wParam,0);
			retFlag=TRUE;
		break;
		}
		break;

	case WM_INITMENU:
		//TRACE("WM_INITMENU %d %d\n",wParam, lParam);
		AfxGetMainWnd()->PostMessage(message,wParam, lParam);
		break;

	case WM_INITMENUPOPUP:
		AfxGetMainWnd()->PostMessage(message,wParam, lParam);
		//TRACE("WM_INITMENUPOPUP %d %d\n",wParam, lParam);
		break;

	case GPM_SWCLOSE:
		m_ViewMode=((m_ViewMode&0xFFFF0000)|GPVIEWMODE_TERMINAL);
		m_DlgSeparateView.ShowWindow(SW_HIDE);
		break;

	case GPM_NETCRASH:
		AfxGetMainWnd()->ShowWindow(SW_SHOWNORMAL);
		AfxGetMainWnd()->EnableWindow(TRUE);
		GetDocument()->EnableDialogs(FALSE);
		break;

	case GPN_CLOSEDLGMETHODS:
		if (GPC.m_DlgMethods!=NULL)
		{
			try
			{
				GPC.m_DlgMethods->DestroyWindow();
			}
			catch(...)
			{
				char tmps[100];
				sprintf(tmps,"Message %X WPARAM %X LPARAM %X",message, wParam, lParam);
				GPC.m_ErrReport.GPWriteErrorLog("CGP_TermView", "WindowProc 2917",tmps);
			}
			try
			{
				delete GPC.m_DlgMethods;
			}
			catch(...)
			{
				char tmps[100];
				sprintf(tmps,"Message %X WPARAM %X LPARAM %X",message, wParam, lParam);
				GPC.m_ErrReport.GPWriteErrorLog("CGP_TermView", "WindowProc 2926",tmps);
			}
			GPC.m_DlgMethods = NULL;
		}
		break;
	case WM_POWERBROADCAST:
      switch(wParam)
      {
      case PBT_APMBATTERYLOW:
        // Battery is low. This global will be used to determine
		 // whether I/O should be avoided or whether it's okay to
		 // suck up as much power as our app desires.
        break;

      case PBT_APMOEMEVENT:
        // OEM specific events
        break;

      case PBT_APMPOWERSTATUSCHANGE:
        // Computer was docked or undocked, battery life is less
        // than 5 minutes, battery is at less than 10%, battery
        // changed by 3%, etc. We're only interested in whether or
        // not we're on AC. If we're on battery we'll try and be
        // conscientious about how we use power.

        // You can do other interesting things here, for example, if
        // you're performing an operation that you know takes longer
        // than the amount of time (power) remaining for the
        // battery, you can stop the process and inform the user
        // that there is not enough time left to complete the
        // operation.
        break;

      case PBT_APMQUERYSUSPEND:
           // If no data loss or corruption will occur, always return
           // TRUE. If data loss or corruption could occur
        // check the high bit of lParam before displaying any
        // user interface elements.
        // If the user doesn't reply in a reasonable
        // amount of time the system will suspend so DON'T DO THIS
        // unless you have to.
		  return BROADCAST_QUERY_DENY;

      case PBT_APMQUERYSUSPENDFAILED:
        // We didn't do anything in our PBT_APMQUERYSUSPEND so no
        // action is necessary here. If we had done something in
        // our PBT_APMQUERYSUSPEND notification it would be
        // necessary to undo it here.
        break;

      case PBT_APMRESUMEAUTOMATIC:
        // We would process this notification if we handled
        // something like a resume caused by an incoming network
        // request, by a modem ring, etc. We DO NOT want to handle
        // this the same way that PBT_APMRESUMESUSPEND is handled
        // because at this point there is no user interaction. As
        // soon as Windows detects user interaction (mouse move,
        // keyboard, etc.) it will notify us with a
        // PBT_RESUMESUSPEND notification.
        break;

      case PBT_APMRESUMECRITICAL:
           // This notification means the system was suspended without
           // the application receiving any suspend messages. The
           // app needs to reestablish any network connections
           // reopen any files and attempt to restore any known
       // context. The app must also attempt to detect any data
           // loss or corruption and notify the user.
           break;

      case PBT_APMRESUMESUSPEND:
         // Reestablish any network connections saved in the suspend
       // function and/or reopen any files and seek to the
       // previously saved position(s).
         // If the files are local then the state of the files will be
       // saved, Be aware that this would require that you keep
       // track of which files are local and which are out on the
       // network.
       break;

      case PBT_APMSUSPEND:
           // Save the necessary info for reestablishing network
        // connections and/or close all files and save information
        // necessary to reestablish the state for each file (file
        // path/name, file pointer position, etc.).

        break;
      }
      break;

	case GPM_DRAGMOUSELEAVE:
		break;
	case GPM_DRAGMOUSEMOVE:
		OnMouseDragMove((PGPDRAGDROPSTRUCT)wParam,(LPPOINT)lParam);
		break;
	case GPM_DRAGMOUSEHOVER:
		OnDragMouseHover();
		break;
	case GPM_DROPITEMS:
		OnDragLButtonUp((PGPDRAGDROPSTRUCT)wParam,(LPPOINT)lParam);
		break;

	//SSH Dll
	case WM_SSH_AGENT_CALLBACK:
		m_Comm.SendMessageToDLL(WM_SSH_AGENT_CALLBACK, wParam, lParam);
		break;
	case WM_SSH_NETEVENT:
		m_Comm.SendMessageToDLL(WM_SSH_NETEVENT, wParam, lParam);
		break;
	case WM_SSH_BACKENDEVENT:
		//m_Comm.GPRead(); 
		break;

	default:
		break;
	}

	if (!retFlag)
	{
		if (message==WM_SETCURSOR && GPC.m_bWaitCursor) lpr=FALSE;
		else 
		{
			try
			{
				if (IsWindow(m_hWnd))
				{
					if (!GPC.m_hViewWnd) GPC.m_hViewWnd=m_hWnd;
					if (message==WM_CONTEXTMENU)
					{
						POINT po={0};
						::GetCursorPos(&po);
						if (::WindowFromPoint(po)==m_hWnd)
							lpr=CFormView::WindowProc(message, wParam, lParam);
					}
					else
					lpr=CFormView::WindowProc(message, wParam, lParam);
				}
				else lpr=NULL;
			}
			catch(...)
			{
				lpr=NULL;
			}
		}
	}

	return lpr;
}

BOOL CGP_TermView::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message==GPN_CLOSEDLGMETHODS)
	{
		if (GPC.m_DlgMethods!=NULL)
		{
			try
			{
				GPC.m_DlgMethods->DestroyWindow();
			}
			catch(...)
			{
				char tmps[100];
				sprintf(tmps,"Message %X WPARAM %X LPARAM %X",pMsg->message, pMsg->wParam, pMsg->lParam);
				GPC.m_ErrReport.GPWriteErrorLog("CGP_TermView", "3094 PreTranslateMessage",tmps);
			}
			try
			{
				delete GPC.m_DlgMethods;
			}
			catch(...)
			{
				char tmps[100];
				sprintf(tmps,"Message %X WPARAM %X LPARAM %X",pMsg->message, pMsg->wParam, pMsg->lParam);
				GPC.m_ErrReport.GPWriteErrorLog("CGP_TermView", "3104 PreTranslateMessage",tmps);
			}
			GPC.m_DlgMethods = NULL;
		}
	}

	if (pMsg->message==WM_SYSKEYDOWN && GPC.m_dwAltFlag)
	{
		if (::GetFocus()==m_hWnd)
			SendPredefKey(pMsg->wParam&0x1FF,((GPC.EasyTCL==false)?0:MOD_EASYTCL)
				|(((GetAsyncKeyState(VK_CONTROL)&0xFF00)==0)?0:MOD_CONTROL)
				|(((GetAsyncKeyState(VK_SHIFT)&0xFF00)==0)?0:MOD_SHIFT)
				|(((GetAsyncKeyState(VK_RWIN)&0xFF00)==0 && (GetAsyncKeyState(VK_LWIN)&0xFF00)==0)?0:MOD_WIN)
				|MOD_ALT
				,pMsg->lParam);

		//TRACE("PreTranslateMessage %d %d\n",pMsg->lParam,pMsg->wParam);
		return 1;
	}
	else
	return CFormView::PreTranslateMessage(pMsg);
}

UINT CGP_TermView::SendStringToPICK(char *ioStr)
{
	UINT ret=0;
	if (ioStr!=NULL && *ioStr)
	{
		char *oStr=new char [(int)strlen(ioStr)+10];
		strcpy(oStr,ioStr);
		AnsiToDos(oStr,1);
		char *postmp=oStr;
		char *postmp2=postmp;
		while(*postmp!=0)
		{
			if (*postmp=='\r' || *postmp=='\n')
			{
				if (*(++postmp)=='\r' || *postmp=='\n') postmp++;
				*(postmp2++)=254;
			}
			else *(postmp2++)=*(postmp++);

		}
		*(postmp2++)='\r';
		*(postmp2++)=0;

		ret=m_Comm.GPSendBlock(oStr,(int)strlen(oStr));
		delete[] oStr;
	}
	else ret=m_Comm.GPSendBlock("\r",1);

	return ret;
}

#include "GPDlgViewSpr.h"

void CGP_TermView::OnDlgviewspr()
{
	GPDlgViewSpr dlg;
	dlg.DoModal();
}

void CGP_TermView::OnUpdateDlgviewspr(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}

#include "DlgErrors.h"

void CGP_TermView::OnDlgErrors()
{
	CDlgErrors dlg;
	dlg.DoModal();
}

void CGP_TermView::OnDlgdebuger()
{
	if (GetDocument()->DlgDebug==NULL)
	{
		GetDocument()->DlgDebug =new GPDlgDebug(this);
		GetDocument()->DlgDebug->Create(IDD_DIALOGDEBUG,this);
	}

	try	{GetDocument()->DlgDebug->ShowWindow(SW_SHOW);}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGP_TermView", "OnDlgdebuger 3169","");
		GetDocument()->DlgDebug =new GPDlgDebug(this);
		GetDocument()->DlgDebug->Create(IDD_DIALOGDEBUG,this);
	}

	try	{GetDocument()->DlgDebug->ShowWindow(SW_SHOW);}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGP_TermView", "OnDlgdebuger 3177","");
	}

	GetDocument()->DlgDebug->SetWindowPos(&CWnd::wndTop,0,0,0,0,SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOSIZE);

}

#include "DlgClienFiles.h"

void CGP_TermView::OnFiledialog()
{
	CDlgClientFiles dlg(aGP_File,GP_NFILES);
	dlg.DoModal();
}

void CGP_TermView::OnUpdateDlgdebuger(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GPC.AdmIsOn);
}

void CGP_TermView::OnUpdateCreateframe(CCmdUI* pCmdUI)
{
	if (pCmdUI->m_pMenu)
		UpdateMenuByAdm();
	else
		pCmdUI->Enable(GPC.AdmIsOn);
}

void CGP_TermView::OnUpdateRemovealldlg(CCmdUI* pCmdUI)
{
	BOOL rem=FALSE;
	if (GPC.AdmIsOn)
	{
		UINT i;
		for(i=0;i<MAX_OBJDLG;i++)
			if (GPC.m_Document->a_GPObjDialog[i]!=NULL || GPC.m_Document->a_GPObjFrame[i]!=NULL)
			{rem=TRUE;break;}
	}
	pCmdUI->Enable(rem);
}

void CGP_TermView::OnUpdateRemoveallobj(CCmdUI* pCmdUI)
{
	BOOL rem=FALSE;
	if (GPC.AdmIsOn)
	{
		GPWindow *wnd=GetDocument()->GetMainScreen()->GPGetWindowByNum(0);
		if (wnd && wnd->WndUnit && wnd->WndUnit[0])
		{
			UINT i;
			for(i=1;i<wnd->WndUnit[0]->m_NGPUNIT;i++)
				if (wnd->WndUnit[i]!=NULL)
				{rem=TRUE;break;}
		}
	}
	pCmdUI->Enable(rem);
}


void CGP_TermView::OnDragMouseHover()
{
}

void CGP_TermView::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
}

void CGP_TermView::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
}

DWORD CGP_TermView::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	return 0;
}


void CGP_TermView::OnBreakslave()
{
	SlaveVisible=FALSE;
	if (SendPickFlProgressDlg)
	{
		SendPickFlProgressDlg->GPClose();
		delete SendPickFlProgressDlg;
		SendPickFlProgressDlg=NULL;
		job_flag=next_job=0;
	}
}

void CGP_TermView::OnUpdateBreakslave(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(SendPickFlProgressDlg!=NULL);
}

void CGP_TermView::OnDumpsockerror()
{
	if (m_Comm.IsErrorLog())
		m_Comm.EndErrorLog();
	else
		m_Comm.StartErrorLog();
}

void CGP_TermView::OnUpdateDumpsockerror(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_Comm.IsErrorLog());
}

void CGP_TermView::OnBeginslave()
{
	job_flag=-1000;
	next_job=-1000;
	slave_nbcur=0;
	SlaveVisible=TRUE;
}

void CGP_TermView::OnUpdateBeginslave(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(SendPickFlProgressDlg==NULL);
}

void CGP_TermView::OnEndslave()
{
	SlaveVisible=FALSE;
	m_Comm.AltInputAccess()->FillFromArray((BYTE *)"\x1C",1);
	m_Comm.AltInputRelease();
/*	if (SendPickFlProgressDlg!=NULL)
	{
		SendPickFlProgressDlg->GPClose();
		delete SendPickFlProgressDlg;
		SendPickFlProgressDlg=NULL;
	}
	m_PrintTransp=TRANSPRINT;
	SendMessage(WM_COMMAND,AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_PrintDlg",1)==0?ID_FILE_PRINT_DIRECT:ID_FILE_PRINT);
	curent_inputbyte=-1;
	inputnbyte=forcounter=0;
	job_flag=0;*/
}

void CGP_TermView::OnUpdateEndslave(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(SendPickFlProgressDlg!=NULL);
}

void CGP_TermView::OnNohideoutput()
{
	m_HIDEVIEWMODE=1-m_HIDEVIEWMODE;
	AfxGetApp()->WriteProfileInt(GPC.cs_RegTermViewSetName, "m_HideView",m_HIDEVIEWMODE);
}

void CGP_TermView::OnUpdateNohideoutput(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_HIDEVIEWMODE!=0);
}

#include "DlgRegister.h"

void CGP_TermView::OnRegisterterm()
{
	CDlgRegister dlg;
	dlg.DoModal();
}

void CGP_TermView::OnUpdateRegisterterm(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}
void CGP_TermView::OnDesktopdlg()
{
	if (GetDocument()->a_GPObjDialogDesktop)
		GetDocument()->a_GPObjDialogDesktop->RunEditor();
}

void CGP_TermView::OnUpdateDesktopdlg(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}

void CGP_TermView::OnScrObjdlg()
{
	GPScreen *scr=GetDocument()->GetMainScreen();
	if (scr && scr->aGPWindow && *(scr->aGPWindow))
		(*(scr->aGPWindow))->RunEditor();
}

void CGP_TermView::OnUpdateScrObjdlg(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}

#include "DlgViewIOFiles.h"

void CGP_TermView::OnDlgviewiofile()
{
	CDlgViewIOFiles dlg;
	dlg.DoModal();
}

void CGP_TermView::OnUpdateDlgviewiofile(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}

#include "DlgViewFSMethods.h"

void CGP_TermView::OnDlgviewFSMethods()
{
	CDlgViewFSMethods dlg;
	dlg.DoModal();
}

void CGP_TermView::OnUpdateDlgviewFSMethods(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}

int CRCTAB_16[]={
			0x0000,  0x1021,  0x2042,  0x3063,  0x4084,  0x50A5,  0x60C6,  0x70E7,
            0x8108,  0x9129,  0xA14A,  0xB16B,  0xC18C,  0xD1AD,  0xE1CE,  0xF1EF,
            0x1231,  0x0210,  0x3273,  0x2252,  0x52B5,  0x4294,  0x72F7,  0x62D6,
            0x9339,  0x8318,  0xB37B,  0xA35A,  0xD3BD,  0xC39C,  0xF3FF,  0xE3DE,
            0x2462,  0x3443,  0x0420,  0x1401,  0x64E6,  0x74C7,  0x44A4,  0x5485,
            0xA56A,  0xB54B,  0x8528,  0x9509,  0xE5EE,  0xF5CF,  0xC5AC,  0xD58D,
            0x3653,  0x2672,  0x1611,  0x0630,  0x76D7,  0x66F6,  0x5695,  0x46B4,
            0xB75B,  0xA77A,  0x9719,  0x8738,  0xF7DF,  0xE7FE,  0xD79D,  0xC7BC,
            0x48C4,  0x58E5,  0x6886,  0x78A7,  0x0840,  0x1861,  0x2802,  0x3823,
            0xC9CC,  0xD9ED,  0xE98E,  0xF9AF,  0x8948,  0x9969,  0xA90A,  0xB92B,
            0x5AF5,  0x4AD4,  0x7AB7,  0x6A96,  0x1A71,  0x0A50,  0x3A33,  0x2A12,
            0xDBFD,  0xCBDC,  0xFBBF,  0xEB9E,  0x9B79,  0x8B58,  0xBB3B,  0xAB1A,
            0x6CA6,  0x7C87,  0x4CE4,  0x5CC5,  0x2C22,  0x3C03,  0x0C60,  0x1C41,
            0xEDAE,  0xFD8F,  0xCDEC,  0xDDCD,  0xAD2A,  0xBD0B,  0x8D68,  0x9D49,
            0x7E97,  0x6EB6,  0x5ED5,  0x4EF4,  0x3E13,  0x2E32,  0x1E51,  0x0E70,
            0xFF9F,  0xEFBE,  0xDFDD,  0xCFFC,  0xBF1B,  0xAF3A,  0x9F59,  0x8F78,
            0x9188,  0x81A9,  0xB1CA,  0xA1EB,  0xD10C,  0xC12D,  0xF14E,  0xE16F,
            0x1080,  0x00A1,  0x30C2,  0x20E3,  0x5004,  0x4025,  0x7046,  0x6067,
            0x83B9,  0x9398,  0xA3FB,  0xB3DA,  0xC33D,  0xD31C,  0xE37F,  0xF35E,
            0x02B1,  0x1290,  0x22F3,  0x32D2,  0x4235,  0x5214,  0x6277,  0x7256,
            0xB5EA,  0xA5CB,  0x95A8,  0x8589,  0xF56E,  0xE54F,  0xD52C,  0xC50D,
            0x34E2,  0x24C3,  0x14A0,  0x0481,  0x7466,  0x6447,  0x5424,  0x4405,
            0xA7DB,  0xB7FA,  0x8799,  0x97B8,  0xE75F,  0xF77E,  0xC71D,  0xD73C,
            0x26D3,  0x36F2,  0x0691,  0x16B0,  0x6657,  0x7676,  0x4615,  0x5634,
            0xD94C,  0xC96D,  0xF90E,  0xE92F,  0x99C8,  0x89E9,  0xB98A,  0xA9AB,
            0x5844,  0x4865,  0x7806,  0x6827,  0x18C0,  0x08E1,  0x3882,  0x28A3,
            0xCB7D,  0xDB5C,  0xEB3F,  0xFB1E,  0x8BF9,  0x9BD8,  0xABBB,  0xBB9A,
            0x4A75,  0x5A54,  0x6A37,  0x7A16,  0x0AF1,  0x1AD0,  0x2AB3,  0x3A92,
            0xFD2E,  0xED0F,  0xDD6C,  0xCD4D,  0xBDAA,  0xAD8B,  0x9DE8,  0x8DC9,
            0x7C26,  0x6C07,  0x5C64,  0x4C45,  0x3CA2,  0x2C83,  0x1CE0,  0x0CC1,
            0xEF1F,  0xFF3E,  0xCF5D,  0xDF7C,  0xAF9B,  0xBFBA,  0x8FD9,  0x9FF8,
            0x6E17,  0x7E36,  0x4E55,  0x5E74,  0x2E93,  0x3EB2,  0x0ED1,  0x1EF0
};

void calc_CRC16DDK(PVOID pBuffer, ULONG ulSize, PULONG pulSeed);
void calc_CRC16(ULONG *t16, ULONG *crc,BYTE nextbyte);


DWORD calcCRC16_Type(UINT CRCType, DWORD PrevSumm, BYTE *tmparr, UINT len)
{
	UINT i;
	switch(CRCType)
	{
	case 2:
		{
			for(i=0;i<len;i++)
				PrevSumm=(CRCTAB_16[(PrevSumm>>8)&0xFF] ^ PrevSumm<<8 ^ tmparr[i])&0xFFFF;
		}
		break;
	case 1:
		{
			for(i=0;i<len;i++)
				calc_CRC16DDK(tmparr+i, 1, &PrevSumm);
		}
		break;
	default:
		{
			for(i=0;i<len;i++)
			calc_CRC16(GPC.tcrc16, &PrevSumm,tmparr[i]);
		}
		break;
	}

	return PrevSumm;
}


void CGP_TermView::OnContextHelp()
{
#ifdef BRIZ
	_spawnlp(_P_DETACH, "HH", "HH", "BRIZ.chm", NULL );
#else
	_spawnlp(_P_DETACH, "HH", "HH", "GP_term.chm", NULL );
#endif
}


#include "DlgViewRegMethods.h"

void CGP_TermView::OnDlgviewregmethods()
{
	CDlgViewRegMethods dlg;
	dlg.DoModal();
}

void CGP_TermView::OnUpdateDlgviewregmethods(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}

void CGP_TermView::OnEditScreenToCb()
{
	Size tmps=GetDocument()->GetMainScreen()->GetScreenSize();
	Rect selRect(0,0,tmps.Width-1,tmps.Height-1);
	CString csTmp;
	GetScreenText(csTmp,selRect);
	StringToClip(csTmp);
}

void CGP_TermView::OnUpdateEditScreenToCb(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}

void CGP_TermView::SetMouseSelectionCursor()
{
	if (m_MouseSelectionMode)
	{
		if ((GetAsyncKeyState(VK_SHIFT)&0xFF00)!=0)
			::SetCursor(::LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_CURSOR_HEDIT)));
		else
		if ((GetAsyncKeyState(VK_CONTROL)&0xFF00)!=0)
			::SetCursor(::LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_CURSOR_HGETLEFT)));
		else
			::SetCursor(::LoadCursor(NULL,IDC_ARROW));
	}

}

void CGP_TermView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (m_MouseSelectionMode)	SetMouseSelectionCursor();
	CFormView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CGP_TermView::OnFilePrintPreview()
{
	CFormView::OnFilePrintPreview();
}

void CGP_TermView::OnDumpcaptureclear()
{
	OnDumpcapturestop();
	m_CaptureFile=fopen("capture.txt","wb");
}

void CGP_TermView::OnDumpcapturestartstop()
{
	OnDumpcapturestop();
	m_CaptureFile=fopen("capture.txt","ab");
}

void CGP_TermView::OnDumpcapturepreview()
{
	OnDumpcapturestop();

	CString csNotepadDumpSet="";
	CString csNotepadSet="";
	CDlgNotepadSet::GetNotepadSettings(csNotepadSet);
	CDlgNotepadSet::GetNotepadTypeSettings("NotepadCaptureDumpSet",csNotepadDumpSet);
	if (csNotepadDumpSet=="")			csNotepadDumpSet=csNotepadSet;
	if (csNotepadSet!=csNotepadDumpSet)	CDlgNotepadSet::SetNotepadSettings(csNotepadDumpSet);

	SHELLEXECUTEINFO ExecInfo={0};
	ExecInfo.cbSize=sizeof(ExecInfo);
	ExecInfo.fMask=0x00000010/*SEE_MASK_ICON*/;
	ExecInfo.hwnd=m_hWnd;
	ExecInfo.lpVerb="open";
	ExecInfo.lpFile="NOTEPAD.EXE";
	ExecInfo.lpParameters="capture.txt";
	ExecInfo.nShow=SW_SHOW;

	if (::ShellExecuteEx(&ExecInfo)==FALSE)
	{
		ExecInfo.lpFile="capture.txt";
		ExecInfo.lpVerb="edit";
		ExecInfo.lpParameters=NULL;
		::ShellExecuteEx(&ExecInfo);
	}

	if (csNotepadSet!=csNotepadDumpSet)
		CDlgNotepadSet::SetNotepadSettings(csNotepadSet);
}

void CGP_TermView::OnDumpcapturepreviewsetup()
{
	CDlgNotepadSet dlg;
	dlg.m_csSectionName="NotepadCaptureDumpSet";
	dlg.DoModal();
}

void CGP_TermView::OnSlavePrintPageSetup()
{
	CDlgNotepadSet dlg;
	dlg.m_csSectionName="SlavePrintPageSetup";
	dlg.DoModal();
}

void CGP_TermView::OnUpdateDumpcaptureclear(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_CaptureFile==NULL);
}

void CGP_TermView::OnUpdateDumpcapturestartstop(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_CaptureFile==NULL);
}

void CGP_TermView::OnUpdateSlavePrintPageSetup(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_CaptureFile==NULL);
}

void CGP_TermView::OnUpdateDumpcapturepreview(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_CaptureFile==NULL);
}

void CGP_TermView::OnUpdateDumpcapturepreviewsetup(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_CaptureFile==NULL);
}

void CGP_TermView::OnUpdateDumpcapturestop(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_CaptureFile!=NULL);
}

void CGP_TermView::OnUpdateScreenSizeMenu(CCmdUI* pCmdUI)
{
/*	switch(pCmdUI->m_nID)
	{
	case ID_SCRSIZE79X24:   mSiz.Width=79; mSiz.Height=24;   break;
	case ID_SCRSIZE79X25:   mSiz.Width=79; mSiz.Height=25;   break;
	case ID_SCRSIZE80X24:   mSiz.Width=80; mSiz.Height=24;   break;
	case ID_SCRSIZE80X25:   mSiz.Width=80; mSiz.Height=25;   break;
	case ID_SCRSIZE80X32:   mSiz.Width=80; mSiz.Height=32;   break;
	case ID_SCRSIZE80X46:   mSiz.Width=80; mSiz.Height=46;   break;
	case ID_SCRSIZE88X24:   mSiz.Width=88; mSiz.Height=24;   break;
	case ID_SCRSIZE88X32:   mSiz.Width=88; mSiz.Height=32;   break;
	case ID_SCRSIZE88X72:   mSiz.Width=88; mSiz.Height=72;   break;
	case ID_SCRSIZE128X24:   mSiz.Width=128; mSiz.Height=24;   break;
	case ID_SCRSIZE128X25:   mSiz.Width=128; mSiz.Height=25;   break;
	case ID_SCRSIZE128X36:   mSiz.Width=128; mSiz.Height=36;   break;
	case ID_SCRSIZE128X46:   mSiz.Width=128; mSiz.Height=46;   break;
	case ID_SCRSIZE128X60:   mSiz.Width=128; mSiz.Height=60;   break;
	case ID_SCRSIZE128X72:   mSiz.Width=128; mSiz.Height=72;   break;
	case ID_SCRSIZE132X24:   mSiz.Width=132; mSiz.Height=24;   break;
	case ID_SCRSIZE132X25:   mSiz.Width=132; mSiz.Height=25;   break;
	case ID_SCRSIZE132X36:   mSiz.Width=132; mSiz.Height=36;   break;
	case ID_SCRSIZE132X46:   mSiz.Width=132; mSiz.Height=46;   break;
	case ID_SCRSIZE132X60:   mSiz.Width=132; mSiz.Height=60;   break;
	case ID_SCRSIZE132X72:   mSiz.Width=132; mSiz.Height=72;   break;
	case ID_SCRSIZECUSTOM:  
		break;
	}
	*/
	Size tmpsz=GetDocument()->GetActiveScrSize();
	pCmdUI->Enable(tmpsz.Height!=-1 && tmpsz.Width!=-1);
}

#include "DlgScreenSize.h"

void CGP_TermView::OnScreenSizeMenu(UINT nID)
{
	Size mSiz(-1,-1);
	switch(nID)
	{
	case ID_SCRSIZE79X24:   mSiz.Width=79; mSiz.Height=24;   break;
	case ID_SCRSIZE79X25:   mSiz.Width=79; mSiz.Height=25;   break;
	case ID_SCRSIZE80X24:   mSiz.Width=80; mSiz.Height=24;   break;
	case ID_SCRSIZE80X25:   mSiz.Width=80; mSiz.Height=25;   break;
	case ID_SCRSIZE80X32:   mSiz.Width=80; mSiz.Height=32;   break;
	case ID_SCRSIZE80X46:   mSiz.Width=80; mSiz.Height=46;   break;
	case ID_SCRSIZE88X24:   mSiz.Width=88; mSiz.Height=24;   break;
	case ID_SCRSIZE88X32:   mSiz.Width=88; mSiz.Height=32;   break;
	case ID_SCRSIZE88X72:   mSiz.Width=88; mSiz.Height=72;   break;
	case ID_SCRSIZE128X24:   mSiz.Width=128; mSiz.Height=24;   break;
	case ID_SCRSIZE128X25:   mSiz.Width=128; mSiz.Height=25;   break;
	case ID_SCRSIZE128X36:   mSiz.Width=128; mSiz.Height=36;   break;
	case ID_SCRSIZE128X46:   mSiz.Width=128; mSiz.Height=46;   break;
	case ID_SCRSIZE128X60:   mSiz.Width=128; mSiz.Height=60;   break;
	case ID_SCRSIZE128X72:   mSiz.Width=128; mSiz.Height=72;   break;
	case ID_SCRSIZE132X24:   mSiz.Width=132; mSiz.Height=24;   break;
	case ID_SCRSIZE132X25:   mSiz.Width=132; mSiz.Height=25;   break;
	case ID_SCRSIZE132X36:   mSiz.Width=132; mSiz.Height=36;   break;
	case ID_SCRSIZE132X46:   mSiz.Width=132; mSiz.Height=46;   break;
	case ID_SCRSIZE132X60:   mSiz.Width=132; mSiz.Height=60;   break;
	case ID_SCRSIZE132X72:   mSiz.Width=132; mSiz.Height=72;   break;
	case ID_SCRSIZECUSTOM:  
		{
			CDlgScreenSize dlg;
			dlg.DoModal();
		}
		break;
	}
	if (mSiz.Width>3)
	{
		CString tmps;
		GetDocument()->ResizeActiveScr(mSiz);
		tmps=AfxGetApp()->GetProfileString(m_Comm.GPSectionName, "SCRSIZECOMMAND","term %X,%Y");	
		char cVal[100];
		sprintf(cVal,"%d",mSiz.Width);
		tmps.Replace("%x",cVal);
		tmps.Replace("%X",cVal);
		sprintf(cVal,"%d",mSiz.Height);
		tmps.Replace("%y",cVal);
		tmps.Replace("%Y",cVal);
		tmps+="\r";
		GPC.cs_ScriptLine+="\\w250;"+tmps;
		DoScriptCommand();
	}
}


void CGP_TermView::OnDumpcapturestop()
{
	if (m_CaptureFile)
	{
		fclose(m_CaptureFile);
		m_CaptureFile=NULL;
	}
}

void CGP_TermView::CreateInputOutputDlg()
{
	if (m_DlgSeparateView.m_hWnd==NULL && m_hWnd)
	{
		m_DlgSeparateView.Create(IDD_DLGSEPARATEVIEW,this);
		m_DlgSeparateView.ModifyStyleEx(0,WS_EX_APPWINDOW);
		m_DlgSeparateView.ShowWindow(SW_HIDE);
		m_DlgSeparateView.SetViewMode(m_ViewMode&0xFFFF);
		m_DlgSeparateView.FrameSizeMove();
	}
}

void CGP_TermView::CreateInputOutputDlgInFrame()
{
	if (m_DlgSeparateViewInFrame==NULL)
		m_DlgSeparateViewInFrame=new CDlgSeparateViewInFrame;
	if (m_DlgSeparateViewInFrame->m_hWnd==NULL)
		m_DlgSeparateViewInFrame->Create(IDD_DLGVIEWINFRAME,this);
}

void CGP_TermView::DeleteInputOutputDlgInFrame()
{
	m_DlgSeparateView.ResetParent();

	if (m_DlgSeparateViewInFrame)
	{
		m_DlgSeparateViewInFrame->m_DlgViewInputAll=NULL;
		m_DlgSeparateViewInFrame->m_DlgViewOutput=NULL;

		if (m_DlgSeparateViewInFrame->m_hWnd)
			m_DlgSeparateViewInFrame->DestroyWindow();
		delete m_DlgSeparateViewInFrame;
		m_DlgSeparateViewInFrame=NULL;
	}
}

void CGP_TermView::OnSeparateviewmode()
{
	switch((m_ViewMode&GPVIEWMODE_TYPEMASK))
	{
	case GPVIEWMODE_TERMINAL:
		if ((m_ViewMode&GPVIEWMODE_INFRAME)==GPVIEWMODE_INFRAME)
		{
			CreateInputOutputDlgInFrame();
			if (m_DlgSeparateViewInFrame->m_hWnd)
			{
				m_DlgSeparateView.SetPartsParent(m_DlgSeparateViewInFrame->m_hWnd);
				m_DlgSeparateViewInFrame->m_DlgViewInputAll=&(m_DlgSeparateView.m_DlgViewInputAll);
				m_DlgSeparateViewInFrame->m_DlgViewOutput=&(m_DlgSeparateView.m_DlgViewOutput);
				m_DlgSeparateViewInFrame->m_FrameLastSize.SetRectEmpty();
				m_DlgSeparateView.ShowWindow(SW_HIDE);
				m_DlgSeparateViewInFrame->ShowWindow(SW_SHOW);
				m_DlgSeparateViewInFrame->FrameSizeMove();
			}
			else
			{
				if (m_DlgSeparateViewInFrame) delete m_DlgSeparateViewInFrame;
				m_DlgSeparateViewInFrame=NULL;
				m_DlgSeparateView.ResetParent();
				m_ViewMode^=GPVIEWMODE_INFRAME;
			}
		}

		m_ViewMode=((m_ViewMode&GPVIEWMODE_PLACEMASK)|GPVIEWMODE_SEPARATE);

		if ((m_ViewMode&GPVIEWMODE_INFRAME)!=GPVIEWMODE_INFRAME)
		{
			m_DlgSeparateView.ResetParent();
			m_DlgSeparateView.FrameSizeMove();
			m_DlgSeparateView.ShowWindow(SW_SHOW);
			m_DlgSeparateView.Invalidate();
		}
		break;
	case GPVIEWMODE_SEPARATE:
		{
			m_ViewMode=((m_ViewMode&GPVIEWMODE_PLACEMASK)|GPVIEWMODE_TERMINAL);
			m_DlgSeparateView.ShowWindow(SW_HIDE);
			m_DlgSeparateView.m_DlgViewOutput.CloseFindDialog();
			DeleteInputOutputDlgInFrame();

			CRect re;
			GetClientRect(&re);
			OnSize(0,re.Width(),re.Height());
			SetFocus();
		}
		break;
	}
	AfxGetApp()->WriteProfileInt("SEP_OUTPUT_SET", "m_ViewMode",m_ViewMode);
}

void CGP_TermView::OnUpdateSeparateviewmode(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GPC.AdmIsOn);
	const char *ccnewtext="";
	switch((m_ViewMode&GPVIEWMODE_TYPEMASK))
	{
	case GPVIEWMODE_TERMINAL:
		#ifdef RUS
			ccnewtext="Раздельный ввод/вывод\x3 MAINIL\x3 21";
		#else
			ccnewtext="Separated View Mode\x3 MAINIL\x3 21";
		#endif
		break;
	case GPVIEWMODE_SEPARATE:
		#ifdef RUS
			ccnewtext="Режим терминала\x3 MAINIL\x3 21";
		#else
			ccnewtext="Simple Terminal Mode\x3 MAINIL\x3 21";
		#endif
		break;
	}
	if (!pCmdUI->m_pMenu)
		pCmdUI->SetText(ccnewtext);
	else
	{
		MENUITEMINFO mii={0};
		mii.cbSize=sizeofMENUITEMINFO;
		mii.fMask=MIIM_DATA;
		if (::GetMenuItemInfo(pCmdUI->m_pMenu->m_hMenu,pCmdUI->m_nIndex,TRUE,&mii))
			m_GPMenu->MENUINFOArray[mii.dwItemData].csText=ccnewtext;
	}

}

void CGP_TermView::OnSeparateviewinframe()
{
	m_ViewMode^=GPVIEWMODE_INFRAME;

	if ((m_ViewMode&GPVIEWMODE_INFRAME)==GPVIEWMODE_INFRAME)
	{
		CreateInputOutputDlgInFrame();
		if (m_DlgSeparateViewInFrame->m_hWnd)
		{
			m_DlgSeparateView.SetPartsParent(m_DlgSeparateViewInFrame->m_hWnd);
			m_DlgSeparateViewInFrame->m_DlgViewInputAll=&(m_DlgSeparateView.m_DlgViewInputAll);
			m_DlgSeparateViewInFrame->m_DlgViewOutput=&(m_DlgSeparateView.m_DlgViewOutput);
			m_DlgSeparateView.ShowWindow(SW_HIDE);
			m_DlgSeparateViewInFrame->m_FrameLastSize.SetRectEmpty();
			m_DlgSeparateViewInFrame->ShowWindow(SW_SHOW);
			m_DlgSeparateViewInFrame->FrameSizeMove();
		}
		else
		{
			if (m_DlgSeparateViewInFrame) delete m_DlgSeparateViewInFrame;
			m_DlgSeparateViewInFrame=NULL;
			m_DlgSeparateView.ResetParent();
			m_ViewMode^=GPVIEWMODE_INFRAME;
		}
	}

	if ((m_ViewMode&GPVIEWMODE_INFRAME)!=GPVIEWMODE_INFRAME)
	{
		m_DlgSeparateView.ResetParent();
		m_DlgSeparateView.FrameSizeMove();
		m_DlgSeparateView.ShowWindow(SW_SHOW);
		m_DlgSeparateView.Invalidate();
		DeleteInputOutputDlgInFrame();
	}
	AfxGetApp()->WriteProfileInt("SEP_OUTPUT_SET", "m_ViewMode",m_ViewMode);
}

void CGP_TermView::OnUpdateSeparateviewinframe(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GPC.AdmIsOn && (m_ViewMode&GPVIEWMODE_SEPARATE)==GPVIEWMODE_SEPARATE);
	pCmdUI->SetCheck((m_ViewMode&GPVIEWMODE_INFRAME)==GPVIEWMODE_INFRAME);
}

void CGP_TermView::OnUpdateClsscr0(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetDocument()->GetActiveScreen()->ScrId!=0 || GetDocument()->GetMainScreen()->ScrId!=0);
}

void CGP_TermView::OnUpdateWindowGrid(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(dwWindowGrid&0x1);
}

void CGP_TermView::OnWindowGrid()
{
	dwWindowGrid^=1;
	Invalidate();
}

#include "DlgImageList.h"

void CGP_TermView::OnDlgviewimagelists()
{
	CDlgImageList dlg;
	dlg.DoModal();
}

void CGP_TermView::OnUpdateDlgviewimagelists(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

#include "DlgTermcap.h"

void CGP_TermView::OnTermcap()
{
	CDlgTermcap dlg;
	dlg.DoModal();
}

void CGP_TermView::OnTermcapAV()
{
	CDldTermcapVideo dlg;
	dlg.DoModal();
}

void CGP_TermView::OnUpdateTermcap(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}

void CGP_TermView::OnUpdateTermcapAV(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}

void CGP_TermView::OnEnablecontextmenu()
{
	m_UseContextMenu^=GPVIEW_USECONTEXTMENU;
	AfxGetApp()->WriteProfileInt(GPC.cs_RegTermViewSetName, "ContextMenu",m_UseContextMenu);
}

void CGP_TermView::OnUpdateEnablecontextmenu(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck((m_UseContextMenu&GPVIEW_USECONTEXTMENU)!=0);
}

void CGP_TermView::OnEditcontextmenu()
{
	CDlgContextMenu dlg(this);
	dlg.DoModal();
}

void CGP_TermView::OnUpdateEditcontextmenu(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}

void CGP_TermView::OnUpdateFullcontextmenu(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GPC.m_pContextMenu && GPC.m_pContextMenu->GetCount());
}

void CGP_TermView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	if (m_UseContextMenu && GPC.m_pContextMenu && GPC.m_pContextMenu->m_Menu)
		TrackPopupMenu(GPC.m_pContextMenu->m_Menu,TPM_RIGHTBUTTON|TPM_TOPALIGN|TPM_LEFTALIGN|TPM_HORNEGANIMATION,point.x,point.y,0,GPC.m_hViewWnd,NULL);
}

#include "DlgViewContextMenuMethods.h"

void CGP_TermView::OnDlgviewContextMenuMethods() 
{
	CDlgViewContextMenuMethods dlg;
	dlg.DoModal();
}

void CGP_TermView::OnUpdateDlgviewContextMenuMethods(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
}

UINT CGP_TermView::EmulateRemappingInput(int iJob, const char *iStr, UINT nByte)
{
	EnterCriticalSection(&(GPC.m_View->m_CSRemap));
	char *tmpInputBuffer=InputBuffer;
	char *tmpInputBuffer2=InputBuffer2;
	char *IB=new char [10000];
	char *IB2=new char [10000];
	InputBuffer=IB;
	InputBuffer2=IB2;
	char *pos=IB;
	UINT i;
	for(i=0;i<nByte;i++)
		InputBuffer[i]=iStr[i];
	InputBuffer[i++]=0;
	int tmp_job_flag=job_flag;
	int tmp_string_ptr=string_ptr;
	int tmp_next_job=next_job;
	if (nByte) job_flag=-1,next_job=-iJob;
	else job_flag=-iJob;

	UINT ret=(nByte)?RemappingInput(i):DoEscSeq(iJob);

	job_flag=tmp_job_flag;
	string_ptr=tmp_string_ptr;
	next_job=tmp_next_job;
	GPC.m_View->InputBuffer2=tmpInputBuffer2;
	GPC.m_View->InputBuffer=tmpInputBuffer;
	delete[] IB;
	delete[] IB2;
	LeaveCriticalSection(&(GPC.m_View->m_CSRemap));

	return ret;
}

void CGP_TermView::BeginListen()
{
	ListenSock=new CGPAsyncSocket;
	ListenSock->Create(m_Comm.ListenPort);
	m_ListenTime=m_Comm.ListenTime*10;
	if (m_ListenTime<10) m_ListenTime=0x10000000;
	
	SetTimer( LISTEN_TIMER_ID, 100, NULL);
}

#include "DlgViewSystemMethods.h"

void CGP_TermView::OnDlgviewsysmethods() 
{
	CDlgViewSystemMethods dlg;
	dlg.DoModal();
}

void CGP_TermView::OnUpdateDlgviewsysmethods(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
}

void CGP_TermView::OnUpdateTermHide(CCmdUI* pCmdUI) 
{
	const char *ccnewtext="";
	if (AfxGetMainWnd()->IsWindowVisible())
#ifdef RUS
		ccnewtext="Скрыть терминал\x3 MAINIL\x3 20";
	else
		ccnewtext="Показать терминал\x3 MAINIL\x3 20";
#else
		ccnewtext="Hide terminal window\x3 MAINIL\x3 20";
	else
		ccnewtext="Restore terminal window\x3 MAINIL\x3 20";
#endif
//		pCmdUI->SetText("Restore terminal window");

	MENUITEMINFO mii={0};
	mii.cbSize=sizeofMENUITEMINFO;
	mii.fMask=MIIM_DATA;
	if (!pCmdUI->m_pMenu)
		pCmdUI->SetText(ccnewtext);
	else
	if (::GetMenuItemInfo(pCmdUI->m_pMenu->m_hMenu,pCmdUI->m_nIndex,TRUE,&mii))
		m_GPMenu->MENUINFOArray[mii.dwItemData].csText=ccnewtext;
}


LRESULT CGP_TermView::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	
	return CFormView::DefWindowProc(message, wParam, lParam);
}

BOOL CGP_TermView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	BOOL ret=CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
	return ret;
}

int CGP_TermView::DoAdditionalMessageLoop()
{
	if ((GPC.Flags&GP_CUR_LOCKCOM)!=GP_CUR_LOCKCOM)
	{
		MSG m_msgCur; 
		GPC.Flags|=GP_CUR_ADDITIONALLOOP;
		CWinApp *mApp=AfxGetApp();
		while (::PeekMessage(&m_msgCur, NULL, NULL, NULL, PM_NOREMOVE))
		{
			 if (!mApp->PumpMessage())	
			 {
				AfxThrowOleDispatchException(1010,IDS_GPOLEEXEPTION1010);
				return -1;
			 }
		}
		GPC.Flags&=(0xFFFFFFFF^GP_CUR_ADDITIONALLOOP);
	}
	return ((GPC.Flags&GP_CUR_LOCKCOM)==GP_CUR_LOCKCOM)?-1:0/*mApp->OnIdle(1)*/;
}

DWORD CGP_TermView::DoScriptCommand()
{
	KillTimer(SCRIPTOUT_TIMER_ID);
	DWORD ret=0;
	DWORD dwDelay=50;
	if (GPC.cs_ScriptLine!="")
	{
		const char *posstrt,*pos=GPC.cs_ScriptLine;
		posstrt=pos;
		int slashcntr=0;
		while(pos && *pos)
		{
			if (*pos=='\\')
			{
				slashcntr=1-slashcntr;
				pos++;
			}
			else
			{
				if (slashcntr)
				{
					switch(*pos)
					{
					case 'l': //login dialog
						{
							CDlgLogin mdlg;
							m_TermCap.TranslateFoundEsc();
							mdlg.m_DlgFlags=GPC.dw_LoginDialogFlags_temporary;
							mdlg.DoModal();
							pos++;
						}
						break;
					case 'w': //wait
					case 's': //synchro
					case 'q': //query
						{
							CString csSendStr=GPC.cs_ScriptLine.Mid(0,pos-posstrt-1);
							if (csSendStr!="")
							{
								AnsiToDosMB(CGPContextMenu::ConvertToOutput(csSendStr,NULL),csSendStr,0);
								m_Comm.GPSendBlock(csSendStr,csSendStr.GetLength(),0);
							}
							switch(*pos)
							{
							case 'w': //wait
								{
									const char *pos2=pos+1;
									while(*pos2>='0' && *pos2<='9') pos2++;
									dwDelay=1000;
									if (*pos2==';')
									{
										if (pos2>pos+1) dwDelay=atoi(pos+1);
										pos=pos2;
										if (*pos) pos++;
									}
									else pos++;
									GPC.cs_ScriptLine=GPC.cs_ScriptLine.Mid(pos-posstrt);
									pos=NULL;
								}
								break;
							case 's'://synchro
								{
									const char *pos2=pos+1;
									while(*pos2 && *pos2!=';') pos2++;
									if (*pos2==';')
									{
										AnsiToDosMB(CGPContextMenu::ConvertToOutput(GPC.cs_ScriptLine.Mid(2,pos2-pos-1),NULL),GPC.cs_ScriptWaitLine,0);
										GPC.cs_ScriptLine=GPC.cs_ScriptLine.Mid(pos2-pos+2);
										GPC.cs_ScriptWaitLineCurrent="";
										GPC.dw_ScriptWaitFlag=1;
										dwDelay=0xFFFFFFFF;
										pos=NULL;
									}
								}
								break;
							case 'q'://query
								break;
							}
						}
						break;

					case 'r':
					case 'n':
						{
							pos++;
							CString csSendStr=GPC.cs_ScriptLine.Mid(0,pos-posstrt);
							GPC.cs_ScriptLine=GPC.cs_ScriptLine.Mid(pos-posstrt);
							AnsiToDosMB(CGPContextMenu::ConvertToOutput(csSendStr,NULL),csSendStr,0);
							m_Comm.GPSendBlock(csSendStr,csSendStr.GetLength(),0);
							pos=NULL;
						}
						break;

					default:
						pos++;
						break;
					}
				}
				else pos++;
				slashcntr=0;
			}
		}
		
		if (pos && !*pos)
		{
			CString csSendStr=GPC.cs_ScriptLine;
			GPC.cs_ScriptLine="";
			AnsiToDosMB(CGPContextMenu::ConvertToOutput(csSendStr,NULL),csSendStr,0);
			m_Comm.GPSendBlock(csSendStr,csSendStr.GetLength(),0);
		}

		if (dwDelay!=0xFFFFFFFF && GPC.cs_ScriptLine!="") SetTimer(SCRIPTOUT_TIMER_ID,dwDelay,NULL);
	}

	return ret;
}

DWORD CGP_TermView::GetScreenText(CString &oStr, Rect & re)
{
	Size tmps=GetDocument()->GetMainScreen()->GetScreenSize();
	int bufLen=tmps.Width*tmps.Height;
	unsigned short *buff = new unsigned short [bufLen+10];
	GetDocument()->GetMainScreen()->ScrToBuffer(buff,re);
	unsigned short *buffp1=buff;
	int mLine;
	char tmpchar[]={0,0,};
	char tmpcharmb[]={0,0,0,0,0,0,0,0,0,0,0,0,};
	int selRectHeght=re.Height;
	int selRectWidth=re.Width;
	if (selRectHeght<=0) selRectHeght=-selRectHeght+2;
	if (selRectWidth<=0) selRectWidth=-selRectWidth+2;

	for(mLine=0;mLine<selRectHeght;mLine++)
	{
		if (mLine)	oStr+="\r\n";

		int LineLen=0;
		int x;
		for(x=0;x<selRectWidth;x++)
			if (*buffp1)
			{
				if (!((*buffp1)&0xFF00))
				{
					*tmpchar=((*(buffp1++))&0xFF);
					oStr+=tmpchar;
				}
				else
				if (!((*buffp1)&0xFF))
				{
					*tmpchar=((*(buffp1++))&0xFF00)/0x100;
					oStr+=tmpchar;
				}
				else
				{
					unsigned short tcb[]={0,0,0,};
					*tcb=*(buffp1++);
					int nChars=WideCharToMultiByte(
					  GPC.m_CurCodePage,            // code page
					  WC_NO_BEST_FIT_CHARS,            // performance and mapping flags
					  (LPCWSTR)tcb,    // wide-character string
					  1,          // number of chars in string
					  tmpcharmb,     // buffer for new string
					  10,          // size of buffer
					  "`",     // default for unmappable chars
					 0  // set when default char used
					);
					tmpcharmb[nChars]=0;
					oStr+=tmpchar;
				}
			}
			else  buffp1++;
	}
	delete[] buff;
	return oStr.GetLength();
}

BOOL CGP_TermView::AddCharToDirectInput(char cChar, GPScreen *s)
{
	BOOL ret=FALSE;
	if (GPC.DirecOutputArray.GetCount())
	{
		ret=TRUE;
		DWORD tmpFlag=0;
		try
		{
			GPC.DirecOutputArray.SelectFirst();
			do
			{
				GPUnit *gpu=(GPUnit *)GPC.DirecOutputArray.GetSelected();
				if (gpu) tmpFlag|=gpu->AddDirectOutputChar(GPC.chDosAnsi[cChar&0xFF]);
			}
			while(GPC.DirecOutputArray.SelectNext()>=0);
		}catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("CGP_TermView", "AddCharToDirectInput","4345");
		}
		if ((tmpFlag&0x80) || (tmpFlag&0x1)==0)
		{
			s->CharOutAW(cChar);
		}
		if ((tmpFlag&0x100) || (tmpFlag&0x1)==0)
			m_DlgSeparateView.AppendCharToOutput(GPC.chDosAnsi[cChar&0xFF],m_OutputCharDelay?1:0);
	}
	return ret;
}

void CGP_TermView::UpdateMenuByAdm()
{
#ifdef BRIZ		
	if (m_GPMenu && m_GPMenu->m_ArrPopupMenu[0])
	{
		DWORD state3=::GetMenuState(m_GPMenu->m_ArrPopupMenu[0]->m_hMenu,3,MF_BYPOSITION);
		DWORD state4=::GetMenuState(m_GPMenu->m_ArrPopupMenu[0]->m_hMenu,4,MF_BYPOSITION);
		if ((((state3|state4)&MFS_GRAYED) && GPC.AdmIsOn) || ((!(state3&MFS_GRAYED)||!(state4&MFS_GRAYED)) && !GPC.AdmIsOn))
		{
			::EnableMenuItem(m_GPMenu->m_ArrPopupMenu[0]->m_hMenu,3,MF_BYPOSITION | (GPC.AdmIsOn ? MF_ENABLED : MF_GRAYED));
			::EnableMenuItem(m_GPMenu->m_ArrPopupMenu[0]->m_hMenu,4,MF_BYPOSITION | (GPC.AdmIsOn ? MF_ENABLED : MF_GRAYED));
			AfxGetMainWnd()->DrawMenuBar();

		}
	}
#endif
}

void CGP_TermView::OnSizing(UINT fwSide, LPRECT pRect)
{
	CFormView::OnSizing(fwSide, pRect);
}

BOOL CGP_TermView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	XMouseAction(zDelta>0?GP_XMOUSE_ACTION_WHEELFRWD:GP_XMOUSE_ACTION_WHEELFBKW,  zDelta/120, pt);

	return CFormView::OnMouseWheel(nFlags, zDelta, pt);
}
