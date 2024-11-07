// GPMessage.cpp: implementation of the GPMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GP_term.h"
#include "GP_TermDoc.h"

// in "GP_term.h" #include "GPMessage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#ifndef WM_QUERY3DCONTROLS
	#define WM_QUERY3DCONTROLS  0x036F  // lResult != 0 if 3D controls wanted
#endif


const UINT aHitTestResUINT[26]={HTBORDER,HTBOTTOM,HTBOTTOMLEFT,HTBOTTOMRIGHT,HTCAPTION,HTCLIENT,HTCLOSE,HTERROR,HTGROWBOX,HTHELP,HTHSCROLL,HTLEFT,HTMENU,HTMAXBUTTON,HTMINBUTTON,HTNOWHERE,HTREDUCE,HTRIGHT,HTSIZE,HTSYSMENU,HTTOP,HTTOPLEFT,HTTOPRIGHT,HTTRANSPARENT,HTVSCROLL,HTZOOM,};
const char *aHitTestResName[26]={"HTBORDER","HTBOTTOM","HTBOTTOMLEFT","HTBOTTOMRIGHT","HTCAPTION","HTCLIENT","HTCLOSE","HTERROR","HTGROWBOX","HTHELP","HTHSCROLL","HTLEFT","HTMENU","HTMAXBUTTON","HTMINBUTTON","HTNOWHERE","HTREDUCE","HTRIGHT","HTSIZE","HTSYSMENU","HTTOP","HTTOPLEFT","HTTOPRIGHT","HTTRANSPARENT","HTVSCROLL","HTZOOM",};

const char *alpmes[N_WND_MESSAGE]={
							"WM_NULL","WM_CREATE","WM_DESTROY","WM_MOVE","WM_SIZE",
							"WM_ACTIVATE","WM_SETFOCUS","WM_KILLFOCUS","WM_ENABLE","WM_SETREDRAW",
							"WM_SETTEXT","WM_GETTEXT","WM_GETTEXTLENGTH","WM_PAINT","WM_CLOSE",
							"WM_QUERYENDSESSION","WM_QUIT","WM_QUERYOPEN","WM_ERASEBKGND","WM_SYSCOLORCHANGE",
							"WM_ENDSESSION","WM_SHOWWINDOW","WM_WININICHANGE","WM_SETTINGCHANGE","WM_DEVMODECHANGE",
							"WM_ACTIVATEAPP","WM_FONTCHANGE","WM_TIMECHANGE","WM_CANCELMODE","WM_SETCURSOR",
							"WM_MOUSEACTIVATE","WM_CHILDACTIVATE","WM_QUEUESYNC","WM_GETMINMAXINFO","WM_PAINTICON",
							"WM_ICONERASEBKGND","WM_NEXTDLGCTL","WM_SPOOLERSTATUS","WM_DRAWITEM","WM_MEASUREITEM",
							"WM_DELETEITEM","WM_VKEYTOITEM","WM_CHARTOITEM","WM_SETFONT","WM_GETFONT",
							"WM_SETHOTKEY","WM_GETHOTKEY","WM_QUERYDRAGICON","WM_COMPAREITEM",
#if(WINVER >= 0x0500)
							"WM_GETOBJECT",
#endif /* WINVER >= 0x0500 */
							"WM_COMPACTING","WM_COMMNOTIFY","WM_WINDOWPOSCHANGING","WM_WINDOWPOSCHANGED","WM_POWER",
							"WM_COPYDATA","WM_CANCELJOURNAL","WM_NOTIFY","WM_INPUTLANGCHANGEREQUEST","WM_INPUTLANGCHANGE",
							"WM_TCARD","WM_HELP","WM_USERCHANGED","WM_NOTIFYFORMAT","WM_CONTEXTMENU",
							"WM_STYLECHANGING","WM_STYLECHANGED","WM_DISPLAYCHANGE","WM_GETICON","WM_SETICON",
							"WM_NCCREATE","WM_NCDESTROY","WM_NCCALCSIZE","WM_NCHITTEST","WM_NCPAINT",
							"WM_NCACTIVATE","WM_GETDLGCODE","WM_SYNCPAINT","WM_NCMOUSEMOVE","WM_NCLBUTTONDOWN",
							"WM_NCLBUTTONUP","WM_NCLBUTTONDBLCLK","WM_NCRBUTTONDOWN","WM_NCRBUTTONUP","WM_NCRBUTTONDBLCLK",
							"WM_NCMBUTTONDOWN","WM_NCMBUTTONUP","WM_NCMBUTTONDBLCLK","WM_KEYFIRST","WM_KEYDOWN",
							"WM_KEYUP","WM_CHAR","WM_DEADCHAR","WM_SYSKEYDOWN","WM_SYSKEYUP",
							"WM_SYSCHAR","WM_SYSDEADCHAR","WM_KEYLAST","WM_IME_STARTCOMPOSITION","WM_IME_ENDCOMPOSITION",
							"WM_IME_COMPOSITION","WM_IME_KEYLAST","WM_INITDIALOG","WM_COMMAND","WM_SYSCOMMAND",
							"WM_TIMER","WM_HSCROLL","WM_VSCROLL","WM_INITMENU","WM_INITMENUPOPUP",
							"WM_MENUSELECT","WM_MENUCHAR","WM_ENTERIDLE",
#if(WINVER >= 0x0500)
							"WM_MENURBUTTONUP","WM_MENUDRAG","WM_MENUGETOBJECT","WM_UNINITMENUPOPUP","WM_MENUCOMMAND",
#endif /* WINVER >= 0x0500 */
							"WM_CTLCOLORMSGBOX","WM_CTLCOLOREDIT",
							"WM_CTLCOLORLISTBOX","WM_CTLCOLORBTN","WM_CTLCOLORDLG","WM_CTLCOLORSCROLLBAR","WM_CTLCOLORSTATIC",
							"WM_MOUSEFIRST","WM_MOUSEMOVE","WM_LBUTTONDOWN","WM_LBUTTONUP","WM_LBUTTONDBLCLK",
							"WM_RBUTTONDOWN","WM_RBUTTONUP","WM_RBUTTONDBLCLK","WM_MBUTTONDOWN","WM_MBUTTONUP",
							"WM_MBUTTONDBLCLK","WM_MOUSEWHEEL","WM_MOUSELAST","WM_PARENTNOTIFY","WM_ENTERMENULOOP",
							"WM_EXITMENULOOP","WM_NEXTMENU","WM_SIZING","WM_CAPTURECHANGED","WM_MOVING",
							"WM_POWERBROADCAST","WM_DEVICECHANGE","WM_MDICREATE","WM_MDIDESTROY","WM_MDIACTIVATE",
							"WM_MDIRESTORE","WM_MDINEXT","WM_MDIMAXIMIZE","WM_MDITILE","WM_MDICASCADE",
							"WM_MDIICONARRANGE","WM_MDIGETACTIVE","WM_MDISETMENU","WM_ENTERSIZEMOVE","WM_EXITSIZEMOVE",
							"WM_DROPFILES","WM_MDIREFRESHMENU","WM_IME_SETCONTEXT","WM_IME_NOTIFY","WM_IME_CONTROL",
							"WM_IME_COMPOSITIONFULL","WM_IME_SELECT","WM_IME_CHAR",
#if(WINVER >= 0x0500)
							"WM_IME_REQUEST",
#endif /* WINVER >= 0x0500 */
							"WM_IME_KEYDOWN",
							"WM_IME_KEYUP","WM_MOUSEHOVER","WM_MOUSELEAVE","WM_CUT","WM_COPY",
							"WM_PASTE","WM_CLEAR","WM_UNDO","WM_RENDERFORMAT","WM_RENDERALLFORMATS",
							"WM_DESTROYCLIPBOARD","WM_DRAWCLIPBOARD","WM_PAINTCLIPBOARD","WM_VSCROLLCLIPBOARD","WM_SIZECLIPBOARD",
							"WM_ASKCBFORMATNAME","WM_CHANGECBCHAIN","WM_HSCROLLCLIPBOARD","WM_QUERYNEWPALETTE","WM_PALETTEISCHANGING",
							"WM_PALETTECHANGED","WM_HOTKEY","WM_PRINT","WM_PRINTCLIENT","WM_HANDHELDFIRST",
							"WM_HANDHELDLAST","WM_AFXFIRST","WM_AFXLAST","WM_PENWINFIRST","WM_PENWINLAST",
							"WM_QUERYAFXWNDPROC","WM_SIZEPARENT","WM_SETMESSAGESTRING","WM_IDLEUPDATECMDUI","WM_INITIALUPDATE",
							"WM_COMMANDHELP","WM_HELPHITTEST","WM_EXITHELPMODE","WM_RECALCPARENT","WM_SIZECHILD",
							"WM_KICKIDLE","WM_QUERYCENTERWND","WM_DISABLEMODAL","WM_FLOATSTATUS","WM_ACTIVATETOPLEVEL",
							"WM_QUERY3DCONTROLS","WM_RESERVED_0370","WM_RESERVED_0371","WM_RESERVED_0372","WM_SOCKET_NOTIFY",
							"WM_SOCKET_DEAD","WM_POPMESSAGESTRING","WM_HELPPROMPTADDR","WM_OCC_LOADFROMSTREAM","WM_OCC_LOADFROMSTORAGE",
							"WM_OCC_INITNEW","WM_OCC_LOADFROMSTREAM_EX","WM_OCC_LOADFROMSTORAGE_EX","WM_QUEUE_SENTINEL","WM_RESERVED_037C",
							"WM_RESERVED_037D","WM_RESERVED_037E","WM_FORWARDMSG","WM_MOUSEINSIDE","WM_NCMOUSEHOVER",
							};

const UINT  auimes[N_WND_MESSAGE]={
							WM_NULL,WM_CREATE,WM_DESTROY,WM_MOVE,WM_SIZE,
							WM_ACTIVATE,WM_SETFOCUS,WM_KILLFOCUS,WM_ENABLE,WM_SETREDRAW,
							WM_SETTEXT,WM_GETTEXT,WM_GETTEXTLENGTH,WM_PAINT,WM_CLOSE,
							WM_QUERYENDSESSION,WM_QUIT,WM_QUERYOPEN,WM_ERASEBKGND,WM_SYSCOLORCHANGE,
							WM_ENDSESSION,WM_SHOWWINDOW,WM_WININICHANGE,WM_SETTINGCHANGE,WM_DEVMODECHANGE,
							WM_ACTIVATEAPP,WM_FONTCHANGE,WM_TIMECHANGE,WM_CANCELMODE,WM_SETCURSOR,
							WM_MOUSEACTIVATE,WM_CHILDACTIVATE,WM_QUEUESYNC,WM_GETMINMAXINFO,WM_PAINTICON,
							WM_ICONERASEBKGND,WM_NEXTDLGCTL,WM_SPOOLERSTATUS,WM_DRAWITEM,WM_MEASUREITEM,
							WM_DELETEITEM,WM_VKEYTOITEM,WM_CHARTOITEM,WM_SETFONT,WM_GETFONT,
							WM_SETHOTKEY,WM_GETHOTKEY,WM_QUERYDRAGICON,WM_COMPAREITEM,
#if(WINVER >= 0x0500)
							WM_GETOBJECT,
#endif /* WINVER >= 0x0500 */
							WM_COMPACTING,WM_COMMNOTIFY,WM_WINDOWPOSCHANGING,WM_WINDOWPOSCHANGED,WM_POWER,
							WM_COPYDATA,WM_CANCELJOURNAL,WM_NOTIFY,WM_INPUTLANGCHANGEREQUEST,WM_INPUTLANGCHANGE,
							WM_TCARD,WM_HELP,WM_USERCHANGED,WM_NOTIFYFORMAT,WM_CONTEXTMENU,
							WM_STYLECHANGING,WM_STYLECHANGED,WM_DISPLAYCHANGE,WM_GETICON,WM_SETICON,
							WM_NCCREATE,WM_NCDESTROY,WM_NCCALCSIZE,WM_NCHITTEST,WM_NCPAINT,
							WM_NCACTIVATE,WM_GETDLGCODE,WM_SYNCPAINT,WM_NCMOUSEMOVE,WM_NCLBUTTONDOWN,
							WM_NCLBUTTONUP,WM_NCLBUTTONDBLCLK,WM_NCRBUTTONDOWN,WM_NCRBUTTONUP,WM_NCRBUTTONDBLCLK,
							WM_NCMBUTTONDOWN,WM_NCMBUTTONUP,WM_NCMBUTTONDBLCLK,WM_KEYFIRST,WM_KEYDOWN,
							WM_KEYUP,WM_CHAR,WM_DEADCHAR,WM_SYSKEYDOWN,WM_SYSKEYUP,
							WM_SYSCHAR,WM_SYSDEADCHAR,WM_KEYLAST,WM_IME_STARTCOMPOSITION,WM_IME_ENDCOMPOSITION,
							WM_IME_COMPOSITION,WM_IME_KEYLAST,WM_INITDIALOG,WM_COMMAND,WM_SYSCOMMAND,
							WM_TIMER,WM_HSCROLL,WM_VSCROLL,WM_INITMENU,WM_INITMENUPOPUP,
							WM_MENUSELECT,WM_MENUCHAR,WM_ENTERIDLE,
#if(WINVER >= 0x0500)
	WM_MENURBUTTONUP,WM_MENUDRAG,WM_MENUGETOBJECT,WM_UNINITMENUPOPUP,WM_MENUCOMMAND,
#endif /* WINVER >= 0x0500 */
							WM_CTLCOLORMSGBOX,WM_CTLCOLOREDIT,
							WM_CTLCOLORLISTBOX,WM_CTLCOLORBTN,WM_CTLCOLORDLG,WM_CTLCOLORSCROLLBAR,WM_CTLCOLORSTATIC,
							WM_MOUSEFIRST,WM_MOUSEMOVE,WM_LBUTTONDOWN,WM_LBUTTONUP,WM_LBUTTONDBLCLK,
							WM_RBUTTONDOWN,WM_RBUTTONUP,WM_RBUTTONDBLCLK,WM_MBUTTONDOWN,WM_MBUTTONUP,
							WM_MBUTTONDBLCLK,WM_MOUSEWHEEL,WM_MOUSELAST,WM_PARENTNOTIFY,WM_ENTERMENULOOP,
							WM_EXITMENULOOP,WM_NEXTMENU,WM_SIZING,WM_CAPTURECHANGED,WM_MOVING,
							WM_POWERBROADCAST,WM_DEVICECHANGE,WM_MDICREATE,WM_MDIDESTROY,WM_MDIACTIVATE,
							WM_MDIRESTORE,WM_MDINEXT,WM_MDIMAXIMIZE,WM_MDITILE,WM_MDICASCADE,
							WM_MDIICONARRANGE,WM_MDIGETACTIVE,WM_MDISETMENU,WM_ENTERSIZEMOVE,WM_EXITSIZEMOVE,
							WM_DROPFILES,WM_MDIREFRESHMENU,WM_IME_SETCONTEXT,WM_IME_NOTIFY,WM_IME_CONTROL,
							WM_IME_COMPOSITIONFULL,WM_IME_SELECT,WM_IME_CHAR,
#if(WINVER >= 0x0500)
							WM_IME_REQUEST,
#endif /* WINVER >= 0x0500 */
							WM_IME_KEYDOWN,
							WM_IME_KEYUP,WM_MOUSEHOVER,WM_MOUSELEAVE,WM_CUT,WM_COPY,
							WM_PASTE,WM_CLEAR,WM_UNDO,WM_RENDERFORMAT,WM_RENDERALLFORMATS,
							WM_DESTROYCLIPBOARD,WM_DRAWCLIPBOARD,WM_PAINTCLIPBOARD,WM_VSCROLLCLIPBOARD,WM_SIZECLIPBOARD,
							WM_ASKCBFORMATNAME,WM_CHANGECBCHAIN,WM_HSCROLLCLIPBOARD,WM_QUERYNEWPALETTE,WM_PALETTEISCHANGING,
							WM_PALETTECHANGED,WM_HOTKEY,WM_PRINT,WM_PRINTCLIENT,WM_HANDHELDFIRST,
							WM_HANDHELDLAST,WM_AFXFIRST,WM_AFXLAST,WM_PENWINFIRST,WM_PENWINLAST,

							WM_QUERYAFXWNDPROC,WM_SIZEPARENT,WM_SETMESSAGESTRING,WM_IDLEUPDATECMDUI,WM_INITIALUPDATE,
							WM_COMMANDHELP,WM_HELPHITTEST,WM_EXITHELPMODE,WM_RECALCPARENT,WM_SIZECHILD,
							WM_KICKIDLE,WM_QUERYCENTERWND,WM_DISABLEMODAL,WM_FLOATSTATUS,WM_ACTIVATETOPLEVEL,
							WM_QUERY3DCONTROLS,WM_RESERVED_0370,WM_RESERVED_0371,WM_RESERVED_0372,WM_SOCKET_NOTIFY,
							WM_SOCKET_DEAD,WM_POPMESSAGESTRING,WM_HELPPROMPTADDR,WM_OCC_LOADFROMSTREAM,WM_OCC_LOADFROMSTORAGE,
							WM_OCC_INITNEW,WM_OCC_LOADFROMSTREAM_EX,WM_OCC_LOADFROMSTORAGE_EX,WM_QUEUE_SENTINEL,WM_RESERVED_037C,
							WM_RESERVED_037D,WM_RESERVED_037E,WM_FORWARDMSG,0x12345678,WM_NCMOUSEHOVER,
							};
//     returning 123456  ; unsupported 123444 ; UNKNOWN 123333 ; 
//     ÎÁÐÀÁÀÒÛÂÀÅÒÑß ÎÒÄÅËÜÍÎ 123555
//		case 0: /*NULL*/ 
//		case 1: /*CREATESTRUCT*/
//		case 2: /*low word | high word   off lparam*/
//		case 3: /*HANDLE in lparam*/
//		case 4: /*HANDLE in wparam*/
//		case 5: /*not used must be zero*/
//		case 6: /*text in lparam*/
//      case 7: /*ULONG in lparam*/
//		case 8: /*HANDLE in wparam AND low word | high word   off lparam*/
//		case 9: /*LPDRAWITEMSTRUCT in lparam*/
//		case 10: /*LPMEASUREITEMSTRUCT in lparam*/
//		case 11: /*LPDELETEITEMSTRUCT in lparam*/
//		case 12: /*LPCOMPAREITEMSTRUCT in lparam*/
//		case 13: /*WINDOWPOS  in lparam*/
//		case 14: /*HANDLE in wparam and PCOPYDATASTRUCT */
//		case 15: /*NMHDR  in lparam*/
//		case 16: /*HKL in lparam */
//		case 17: /*HELPINFO  in lparam*/
//		case 18: /*HANDLE in wparam AND ULONG  in lparam*/
//		case 19: /*ULONG in wparam AND STYLESTRUCT in lparam*/
//		case 20: /*HICON in lparam*/
//		case 21: /*LPNCCALCSIZE_PARAMS in lparam*/
//		case 22: /*LPMSG in lparam*/
//		case 23: /*POINTS in lparam*/
//		case 24: /*HANDLE in wparam AND HANDLE in lparam*/
//		case 25: /*MDINEXTMENU in lparam*/
//		case 26: /*LPRECT in lparam*/
//		case 27: /*LPMDICREATESTRUCT in lparam*/
//		case 28: /*LPUINT OR BOOL in lparam*/    
//		case 29: /*HANDLE in wparam AND PAINTSTRUCT in lparam*/
//		case 30: /*HANDLE in wparam AND LPRECT in lparam*/
//		case 31: /*Scroll message*/
//		case 32: /*MOUSEWHEEL*/

const UINT  auimesparam[N_WND_MESSAGE]={
							0,1,0,0,2,				3,4,4,0,5,				6,3,5,4,123456,
							7,123456,123456,4,0,	7,7,0,6,6,				7,0,0,0,8,
							8,0,0,3,3,				4,7,2,9,10,				11,3,3,8,123456,
							123456,123456,123456,12,
#if(WINVER >= 0x0500)
							7,
#endif /* WINVER >= 0x0500 */
							0,123444,13,13,0,		14,0,15,16,16,			7,17,0,18,8,
							19,19,2,0,20,			1,0,211,2,3,			0,22,0,23,23,
							23,23,23,23,23,			23,23,23,123333,7,		7,7,7,7,7,
							7,7,123333,0,0,			7,123333,7,3,2,			123555,31,31,3,8,
							3,3,3,
#if(WINVER >= 0x0500)
	123333,123333,123333,123333,123333,
#endif /* WINVER >= 0x0500 */
							123444,24,
							24,24,24,24,24,			123333,2,2,2,2,			2,2,2,2,2,
							2,32,123333,3,0,			0,25,26,3,26,			7,7,27,4,24,
							4,7,4,0,0,				0,28,24,0,0,			4,0,7,7,7,
							0,16,7,
#if(WINVER >= 0x0500)
							7,
#endif /* WINVER >= 0x0500 */
							7,
							7,7,7,0,0,				0,0,0,7,0,				0,0,29,8,30,
							6,24,8,0,4,
							4,2,18,18,123333,
							123333,123333,123333,123333,123333,
							123333,123333,123333,123333,123333,
							123333,123333,123333,123333,123333,
							123333,123333,123333,123333,123333,
							123333,123333,123333,123333,123333,
							123333,123333,123333,123333,123333,
							123333,123333,123333,123333,123333,
							123333,123333,123333,123333,123333,
							};



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPMessage::GPMessage(const char *iListAllEvents, GPUnit **iGPU, UINT iUnitId)
{
	m_UnitId=iUnitId;
	m_MessageDelay1=0;
	m_LastTick1=0;
	m_HSCROLLMASK=0xFFFFFFFF;
	m_VSCROLLMASK=0xFFFFFFFF;
	GPU=iGPU;
	FLGiIdObj=FLGmessage=FLGwParam=FLGlParam=0;
	m_OutputEdit=NULL;
	m_MMessager=NULL;
	MessagerState=0;

	RetNCHITTEST=0;
	ScriptArray=AnswArray=SeqArray=NULL;
	E_List=new char [(int)strlen(iListAllEvents)+(int)strlen(aUnitCommonMessages)+10];
	strcpy(E_List,iListAllEvents);
	if (*E_List) strcat(E_List,aUnitCommonMessages);
	_strupr(E_List);
	CurME_List=new char [10];
	*CurME_List=0;
}

GPMessage::~GPMessage()
{
	if (m_MMessager!=NULL)	delete[]  m_MMessager;
	m_MMessager=NULL;

	if (E_List!=NULL)		delete E_List;
	E_List=NULL;

	if (SeqArray!=NULL)		delete SeqArray;
	SeqArray=NULL;

	if (ScriptArray!=NULL)	delete ScriptArray;
	ScriptArray=NULL;

	if (AnswArray!=NULL)	delete AnswArray;
	AnswArray=NULL;

	if (CurME_List!=NULL) 	delete[] CurME_List;
	CurME_List=NULL;
}
void GPMessage::SetReferGPU(GPUnit **newGPU)
{
	GPU=newGPU;
}
void GPMessage::AddMessage(const char *iMesArr)
{
	char *tmpmes=new char [(int)strlen(iMesArr)+100];
	strcpy(tmpmes,iMesArr);
	char *Mes;
	Mes=tmpmes;

	while(Mes && *Mes)
	{
		char *posMesTmp=strchr(Mes,'\x1');
		if (posMesTmp)
			*(posMesTmp++)=0;

		char *pos=NULL;
		char *posScript=strchr(tmpmes,'\x2');
		if (posScript) *(posScript++)=0;
		else posScript="";

		char *poseq=strchr(Mes,'=');
		if (poseq!=NULL) *(poseq++)=0;
		else poseq="";

		if (FindInActive(Mes)) DelMessage(Mes);

		if ((pos=FindInMessages(Mes))) 
		{
			UpdateMessagerState(Mes,1);
			if (poseq!=NULL)
			{
				if (strcmp(Mes,"WM_NCHITTEST")==0)
				{
					RetNCHITTEST=0;
					int i;
					for(i=0;i<26;i++) 
						if (_stricmp(poseq,aHitTestResName[i])==0) 
							{RetNCHITTEST=aHitTestResUINT[i];break;}
				}
			}
		}
		else pos=FindInEvents(Mes);

		if ((Mes && *Mes=='_') || (pos && FindInActive(Mes)==NULL)) 
		{
			char *tmp=new char [(int)strlen(CurME_List)+(int)strlen(Mes)+2];
			sprintf(tmp,"%s%s,",CurME_List,Mes);
			delete[] CurME_List;
			CurME_List=tmp;
			_strupr(CurME_List);
			if ((*poseq || *posScript) && strcmp(Mes,"WM_NCHITTEST")!=0)
			{
				if (ScriptArray==NULL) ScriptArray=new GP_RarefiedArr<CString>(5,"");
				if (SeqArray==NULL) SeqArray=new GP_RarefiedArr<CString>(5,"");
				if (AnswArray==NULL) AnswArray=new GP_RarefiedArr<CString>(5,"");
				(*ScriptArray)[ScriptArray->GetItemCount()]=posScript;
				char *tmpMes=new char [(int)strlen(Mes)+10];
				strcpy(tmpMes,Mes);
				_strupr(tmpMes);
				(*SeqArray)[SeqArray->GetItemCount()]=tmpMes;
				delete [] tmpMes;
				(*AnswArray)[AnswArray->GetItemCount()]=poseq;
			}
			if (GPU && GPU[m_UnitId&0xFFFF] && Mes && *Mes=='_')
			{
				AX_NAMES ev;
				ev.cbSize=sizeof(AX_NAMES);
				CString evname=Mes;
				CString evdescr="";
				ev.NamesArr=evname.AllocSysString();
				ev.DescriptionsArr=evdescr.AllocSysString();
				::SendMessage(GPU[m_UnitId&0xFFFF]->UnitHWND,GPM_AX_ADDEVENT,0,(LPARAM)(&ev));
				::SysFreeString(ev.DescriptionsArr);
				::SysFreeString(ev.NamesArr);
			}

		}
		Mes=posMesTmp;
	}
	delete[] tmpmes;
}

char * GPMessage::FindInEvents(const char *Mes)
{
	char tmp[100];
	strncpy(tmp,Mes,95);
	tmp[95]=0;
	strcat(tmp,",");
	_strupr(tmp);
#ifdef _DEBUG
//	TRACE( "CurME_List = %s  , Mes = %s\n", CurME_List, Mes );
#endif //_DEBUG
	return strstr(E_List,tmp);
}

char * GPMessage::FindInMessages(const char *Mes)
{
	int i;
	for(i=0;i<N_WND_MESSAGE && _stricmp(Mes,alpmes[i])!=0;i++);
		char *pos=(i!=N_WND_MESSAGE)?(char *)alpmes[i]:NULL;
#ifdef _DEBUG
//	TRACE( "WndMes = %s\n", CurME_List, Mes );
#endif //_DEBUG
	return pos;
}

char * GPMessage::FindInActive(const char *Mes)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwMessages++;
	char tmp[100];
	strncpy(tmp,Mes,95);
	tmp[95]=0;
	strcat(tmp,",");
	_strupr(tmp);
#ifdef _DEBUG
//	TRACE( "CurME_List = %s  , Mes = %s\n", CurME_List, Mes );
#endif //_DEBUG
	return strstr(CurME_List,tmp);
}

void GPMessage::DelMessage(const char *iMesArr)
{
	char *tmpmes=new char [(int)strlen(iMesArr)+100];
	strcpy(tmpmes,iMesArr);
	char *Mes;
	Mes=tmpmes;

	while(Mes && *Mes)
	{
		char *posMesTmp=strchr(Mes,'\x1');
		if (posMesTmp)
			*(posMesTmp++)=0;

		char *pos=FindInActive(Mes),*pos2;
		if (pos!=NULL && (pos2=strchr(pos,','))!=NULL) 
		{
			UpdateMessagerState(Mes,0);
			if (SeqArray!=NULL)
			{
				char tmpEv[100];
				strncpy(tmpEv,Mes,98);
				tmpEv[98]=0;
				_strupr(tmpEv);
				UINT Id=SeqArray->GetIdByVal(tmpEv);
				if (Id!=0xFFFFFFFFL)
				{
					if (ScriptArray) ScriptArray->RemoveItem(Id);
					if (AnswArray) AnswArray->RemoveItem(Id);
					if (SeqArray) SeqArray->RemoveItem(Id);
				}
			}


			if (strcmp(pos,"WM_NCHITTEST")==0) RetNCHITTEST=0;

			if (GPU && GPU[m_UnitId&0xFFFF] && pos && *pos=='_')
			{
				AX_NAMES ev;
				ev.cbSize=sizeof(AX_NAMES);
				CString evname=pos;
				evname=evname.Left(evname.Find(','));
				CString evdescr="";
				ev.NamesArr=evname.AllocSysString();
				ev.DescriptionsArr=evdescr.AllocSysString();
				::SendMessage(GPU[m_UnitId&0xFFFF]->UnitHWND,GPM_AX_DELEVENT,0,(LPARAM)(&ev));
				::SysFreeString(ev.DescriptionsArr);
				::SysFreeString(ev.NamesArr);
			}
			strcpy(pos,++pos2);
		}
		Mes=posMesTmp;
	}
	delete[] tmpmes;
}


UINT GPMessage::GPSendMenuMessage(UINT iType, UINT id, UINT iIdMessage)
{
	UINT ret=0;
	if (GPC.StopEventsFlag==0) 
	{
		if (GPUnit::m_ptrUnitValChange) (GPUnit::m_ptrUnitValChange)->SendOnValChangeEvent(3);
		char str[50];
		sprintf(str,"%c%c%c%d%c%5.5d\r",250,250,iType==0?49:55,id+1,254,iIdMessage);
		GPC.WaitFor_m_MuteProc();
		if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwMessagesMenu++;
		ret=m_Comm.GPSendSafeBlock(str,(int)strlen(str));
		GPC.Release_m_MuteProc();
		if (m_OutputEdit!=NULL)
		{
			try
			{
				m_OutputEdit->ReplaceSel("\r\nMENU ");
				char *pos=str;
				while(*pos!=0)
				{
					if (*pos==254) *pos=GPC.DelimiterIn1;
					else
					if (*pos==253) *pos=GPC.DelimiterIn2;
					pos++;
				}
				m_OutputEdit->ReplaceSel(DosToAnsi(str));
			}
			catch(...)
			{
				GPC.m_ErrReport.GPWriteErrorLog("GPMessage", "GPSendMenuMessage","");
				m_OutputEdit=NULL;
			}
		}
		return ret;
	}
	else return  ret;
}

UINT GPMessage::GPSendDlgEvent(HWND uHWND, UINT iIdObj, const char *EvName, const char *EvBody)
{
	return GPSendObjEvent(uHWND, (iIdObj*0x10000)|IS_DLG_UNIT,EvName,EvBody);
}


UINT GPMessage::GPSendDllEvent(sctDllStartParams *pDllParams, const char *EvName, const char *EvBody)
{
	UINT len=0;
	if (GPC.StopEventsFlag==0) 
	{
		CString ms;
		if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwDllMessagesSend++;
		ms.Format("   %s\x7F%s\x7F%s\x7F%s\r",pDllParams->csName,pDllParams->csSubroutineName,EvName,EvBody);
		AnsiToDos(ms,ms,1);
		ms.SetAt(0,250);
		ms.SetAt(1,250);
		ms.SetAt(2,60);
		GPC.WaitFor_m_MuteProc();
		len=m_Comm.GPSendSafeBlock(ms,ms.GetLength());
		GPC.Release_m_MuteProc();
	}
	return 0;
}
UINT GPMessage::GPSendComEvent(sctDllStartParams *pDllParams, const char *EvName, const char *EvBody)
{
	UINT len=0;
	if (GPC.StopEventsFlag==0) 
	{
		CString ms;
		if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwCOMMessagesSend++;
		ms.Format("   %s\x7F%s\x7F%s\x7F%s\r",pDllParams->csName,pDllParams->csSubroutineName,EvName,EvBody);
		AnsiToDos(ms,ms,1);
		ms.SetAt(0,250);
		ms.SetAt(1,250);
		ms.SetAt(2,61);
		GPC.WaitFor_m_MuteProc();
		len=m_Comm.GPSendSafeBlock(ms,ms.GetLength());
		GPC.Release_m_MuteProc();
	}
	return 0;
}


UINT GPMessage::GPSendObjEvent(HWND uHWND, UINT iIdObj, const char *EvName, const char *EvBody)
{
	UINT len=0;
	LastIdObj=iIdObj;

	if (m_MMessager!=NULL)
	{
		UINT nMes;
		BOOL onM=FALSE,offM=FALSE;
		for(nMes=0; nMes<MAXMMESAGER;nMes++)
			if (m_MMessager[nMes].DestUnit!=NULL)
			{
				onM=m_MMessager[nMes].OnMsgStr==EvName;
				offM=m_MMessager[nMes].OffMsgStr==EvName;
				if (onM || offM)
				{
					if (onM)
					{
						KillTimer(uHWND,10200+nMes);
						KillTimer(uHWND,10000+nMes);
						if (m_MMessager[nMes].OnTimerDeleay==0)
						{
							if (m_MMessager[nMes].OnProperty!="")	((GPUnit *)m_MMessager[nMes].DestUnit)->GPSetProperty(m_MMessager[nMes].OnProperty);
							if (m_MMessager[nMes].OnMethods!="") DoMessagerSub(m_MMessager[nMes].DestUnit,m_MMessager[nMes].OnMethods);
						}
						else SetTimer(uHWND,10000+nMes,m_MMessager[nMes].OnTimerDeleay,NULL);

						if (m_MMessager[nMes].OffTimerDeleay!=0)
							SetTimer(uHWND,10200+nMes,m_MMessager[nMes].OffTimerDeleay,NULL);
					}
					if (offM)
					{
						KillTimer(uHWND,10200+nMes);
						KillTimer(uHWND,10000+nMes);
						if (m_MMessager[nMes].OffProperty!="")	((GPUnit *)m_MMessager[nMes].DestUnit)->GPSetProperty(m_MMessager[nMes].OffProperty);
						if (m_MMessager[nMes].OffMethods!="") DoMessagerSub(m_MMessager[nMes].DestUnit,m_MMessager[nMes].OffMethods);
					}
				}
			}
	}

	if (GPC.StopEventsFlag==0 && FindInActive(EvName)) 
	{
		BOOL ans=FALSE;
		if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwMessagesSend++;

		if (SeqArray && AnswArray)
		{
			char tmpEv[100];
			strncpy(tmpEv,EvName,98);
			tmpEv[98]=0;
			_strupr(tmpEv);
			UINT Id=SeqArray->GetIdByVal(tmpEv);
			if (Id!=0xFFFFFFFFL && (*AnswArray)[Id]!="")
			{
				ans=TRUE;

				GPC.WaitFor_m_MuteProc();
				m_Comm.SendSequens((LPCTSTR)(*AnswArray)[Id]);
				GPC.Release_m_MuteProc();	
				if (m_OutputEdit)
				{
					try
					{
						m_OutputEdit->ReplaceSel("\r\nOBJANSWER ");
						m_OutputEdit->ReplaceSel(EvName);
						m_OutputEdit->ReplaceSel(" ");
						m_OutputEdit->ReplaceSel((LPCTSTR)(*AnswArray)[Id]);
					}
					catch(...)
					{
						CString cstmps=EvName;
						cstmps+=EvBody;
						GPC.m_ErrReport.GPWriteErrorLog("GPMessage", "GPSendObjEvent 555",cstmps);
						m_OutputEdit=NULL;
					}
				}
			}
		}

		if (ans==FALSE)
		{
			CString ms;
			if (SeqArray && ScriptArray)
			{
				ms.Format("\x7F\x7F\x7F%d\x7F%d\x7F%s\x7F%s",((iIdObj/0x10000)&0xFF),iIdObj&0xFFFF,EvName,EvBody);
				char tmpEv[100];
				strncpy(tmpEv,EvName,98);
				tmpEv[98]=0;
				_strupr(tmpEv);
				UINT Id=SeqArray->GetIdByVal(tmpEv);
				if (Id!=0xFFFFFFFFL && (*ScriptArray)[Id]!="")
						GPC.m_Document->DoAnyMethodScript((*ScriptArray)[Id],iIdObj,ms);
				ms+="\r";
			}
			else
			{
				ms.Format("  %c%d\x7F%d\x7F%s\x7F%s\r",(iIdObj&IS_DLG_UNIT)==0?'2':'3',((iIdObj/0x10000)&0xFF),iIdObj&0xFFFF,EvName,EvBody);
			}
			if (ms[2]==0x7F) ms.SetAt(2,(iIdObj&IS_DLG_UNIT)==0?'2':'3');
			AnsiToDos(ms,ms,1);
			ms.SetAt(0,250);
			ms.SetAt(1,250);
			GPC.WaitFor_m_MuteProc();
			len=m_Comm.GPSendSafeBlock(ms,ms.GetLength());
			GPC.Release_m_MuteProc();

			if (m_OutputEdit)
			{
				try
				{
					m_OutputEdit->ReplaceSel("\r\nEVENT ");
					ms.Replace(254,GPC.DelimiterIn1);
					ms.Replace(253,GPC.DelimiterIn2);
					DosToAnsi(ms,ms);
					m_OutputEdit->ReplaceSel(ms);
				}
				catch(...)
				{
					CString cstmps=EvName;
					cstmps+=EvBody;
					GPC.m_ErrReport.GPWriteErrorLog("GPMessage", "GPSendObjEvent 609",cstmps);
					m_OutputEdit=NULL;
				}
			}
		}
	}

	return 0;
}

UINT GPMessage::GPSendObjMessage(HWND uHWND, UINT iIdObj, UINT message, WPARAM wParam, LPARAM lParam)
{
	UINT ret=0;
	{
		UINT len=0;
		LastIdObj=iIdObj;
		ProcMessagerState(uHWND,message);
		BOOL bSendFlag=TRUE;
		if (GPC.StopEventsFlag==0 && (FLGlParam!=lParam || FLGwParam!=wParam|| FLGmessage!=message|| FLGiIdObj!=iIdObj)) 
		{
			if (message==WM_HELP) ret=1;
			if (message==WM_KEYDOWN && (wParam==VK_RETURN || wParam==VK_TAB))
			{
				if (GPUnit::m_ptrUnitValChange) (GPUnit::m_ptrUnitValChange)->SendOnValChangeEvent(0);
				char *oStr=new char [10000];
				*oStr=0;
				if (GPU && GPU[iIdObj&0xFFFF]) GPU[iIdObj&0xFFFF]->DoMethod("GetWindowText",oStr);
				switch(wParam)
				{
				case VK_RETURN:
					if ((GetAsyncKeyState(VK_CONTROL)&0xFF00))
					{

						if (FindInActive("OnCtrlEnter")!=NULL)
							GPSendObjEvent(uHWND,iIdObj,"OnCtrlEnter",oStr);

						if (FindInActive("OnLockCtrlEnter")!=NULL)
						{
							GPSendObjEvent(uHWND,iIdObj,"OnLockCtrlEnter",oStr);
							ret=1;
						}
					}
					else
					{
						if (FindInActive("OnEnter")!=NULL)
							GPSendObjEvent(uHWND,iIdObj,"OnEnter",oStr);

						if (FindInActive("OnLockEnter")!=NULL)
						{
							GPSendObjEvent(uHWND,iIdObj,"OnLockEnter",oStr);
							ret=1;
						}
					}
					break;
				case VK_TAB:
					if ((GetAsyncKeyState(VK_SHIFT)&0xFF00)!=0)
					{
						if (FindInActive("OnLockBackTab")!=NULL)
						{
							GPSendObjEvent(uHWND,iIdObj,"OnLockBackTab",oStr);
							ret=1;
						}
						if (FindInActive("OnBackTab")!=NULL)
							GPSendObjEvent(uHWND,iIdObj,"OnBackTab",oStr);
					}
					else
					{
						if (FindInActive("OnLockTab")!=NULL)
						{
							GPSendObjEvent(uHWND,iIdObj,"OnLockTab",oStr);
							ret=1;
						}
						if (FindInActive("OnTab")!=NULL)
							GPSendObjEvent(uHWND,iIdObj,"OnTab",oStr);
					}
					break;
				}
				delete[] oStr;
			}
			FLGiIdObj=FLGmessage=FLGwParam=FLGlParam=0;
			if (*CurME_List)
			{
				int i;
				for(i=0;i<N_WND_MESSAGE ;i++)
					if (auimes[i]==message && FindInActive(alpmes[i])!=NULL)
					{
						if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwMessagesSend++;
						BOOL ans=FALSE;
						if (message==WM_NCHITTEST)	len=RetNCHITTEST;
						else
						if (SeqArray && AnswArray)
						{
							char tmpEv[100];
							strncpy(tmpEv,alpmes[i],98);
							tmpEv[98]=0;
							_strupr(tmpEv);
							UINT Id=SeqArray->GetIdByVal(tmpEv);
							if (Id!=0xFFFFFFFFL && (*AnswArray)[Id]!="")
							{
								ans=TRUE;
								if (m_OutputEdit!=NULL)
								{
									try
									{
										m_OutputEdit->ReplaceSel("\r\nOBJWMANSWER ");
										m_OutputEdit->ReplaceSel(alpmes[i]);
										m_OutputEdit->ReplaceSel(" ");
										m_OutputEdit->ReplaceSel((LPCTSTR)(*AnswArray)[Id]);
									}
									catch(...)
									{
										GPC.m_ErrReport.GPWriteErrorLog("GPMessage", "GPSendObjMessage","");
										m_OutputEdit=NULL;
									}
								}

								if (GPC.uLastMessage!=message || GPC.uLastWparam!=wParam || GPC.uLastLparam!=lParam)
								{
									GPC.WaitFor_m_MuteProc();
									m_Comm.SendSequens((LPCTSTR)(*AnswArray)[Id]);
									GPC.Release_m_MuteProc();	
								}
							}
						}

						if (ans==FALSE)
						{
							char *poslast=new char [50000];
							CString ms;
							ms.Format("\x7F\x7F\x7F%d\x7F%d\x7F%s\x7F%d\x7F",((iIdObj/0x10000)&0xFF),iIdObj&0xFFFF,alpmes[i],wParam);
					// îáðàáîòêà lParam
							switch(auimesparam[i])
							{
							case 0: /*NULL*/ 
								break;
							case 1: /*CREATESTRUCT*/
								{
									CREATESTRUCT *stru=(LPCREATESTRUCT) lParam;
									if (stru!=NULL)	 
									{
									char name[500]; strcpy(name,stru->lpszName);
									sprintf(poslast,"%X%c%X%c%X%c%X%c%d%c%d%c%d%c%d%c%ld%c%s%c%s%c%ld",
										(DWORD)stru->lpCreateParams,7,(DWORD)stru->hInstance,7,(DWORD)stru->hMenu,7,(DWORD)stru->hwndParent,
										7,stru->cy,7,stru->cx,7,stru->y,7,stru->x,7,stru->style,
										7,name,7,stru->lpszClass,7,stru->dwExStyle);
									}
								}
								break;
							case 2: /*low word | high word   off lparam*/
								sprintf(poslast,"%d%c%d",(UINT)(lParam&0xFFFF),7,(UINT)(lParam/0x10000));
								break;
							case 3: /*HANDLE in lparam*/
								sprintf(poslast,"%X",lParam);
								break;
							case 4: /*HANDLE in wparam*/
								sprintf(poslast,"%X",wParam);
								break;
							case 5: /*not used must be zero*/
								break;
							case 6: /*text in lparam*/
								strcpy(poslast,(char *)lParam);
								break;
							case 7: /*ULONG in lparam*/
								sprintf(poslast,"%ld",lParam);
								break;
							case 8: /*HANDLE in wparam AND low word | high word   off lparam*/
								sprintf(poslast,"%X%c%d%c%d",wParam,7,(UINT)(lParam&0xFFFF),7,(UINT)(lParam/0x10000));
								break;
							case 9: /*LPDRAWITEMSTRUCT*/
								sprintf(poslast,"%X",lParam);
								break;
							case 10: /*LPMEASUREITEMSTRUCT*/
								sprintf(poslast,"%X",lParam);
								break;
							case 11: /*LPDELETEITEMSTRUCT*/
								sprintf(poslast,"%X",lParam);
								break;
							case 12: /*LPCOMPAREITEMSTRUCT*/
								sprintf(poslast,"%X",lParam);
								break;
							case 13: /*WINDOWPOS*/
								{
									WINDOWPOS *stru=(LPWINDOWPOS) lParam;
									char strst[250];*strst=0;
									int i22;
									for(i22=0;i22<N_WINDOWPOS_STYLES;i22++)
										if ((stru->flags&aWindowPosStyleUINT[i22])==aWindowPosStyleUINT[i22]) strcat(strst,aWindowPosStyleName[i22]);

									if (stru!=NULL)	 
									sprintf(poslast,"%X%c%X%c%d%c%d%c%d%c%d%c%ld%c%s",(DWORD)stru->hwnd,7,(DWORD)stru->hwndInsertAfter,
										7,stru->x,7,stru->y,7,stru->cx,7,stru->cy,7,stru->flags,7,strst);
								}
								break;
							case 14: /*HANDLE in wparam and PCOPYDATASTRUCT */
								{
									COPYDATASTRUCT *stru=(COPYDATASTRUCT *) lParam;
									if (stru!=NULL)	 
									sprintf(poslast,"%X%c%ld%c%ld%c%X",wParam,7,stru->dwData,7,stru->cbData,7,(DWORD)stru->lpData);
								}
								break;
							case 15: /*NMHDR */
								{
									NMHDR *stru=(LPNMHDR) lParam;
									if (stru!=NULL)	 
									sprintf(poslast,"%X%c%ld%c%ld",(DWORD)stru->hwndFrom,7,stru->idFrom,7,stru->code);
								}
								break;
							case 16: /*HKL*/
								sprintf(poslast,"%X",lParam);
								break;
							case 17: /*HELPINFO */
								{
									HELPINFO *stru=(LPHELPINFO) lParam;
									if (stru!=NULL)	 
									sprintf(poslast,"%ld%c%d%c%d%c%X%c%ld%c%d%c%d",stru->cbSize,7,stru->iContextType,7,stru->iCtrlId,
										7,(DWORD)stru->hItemHandle,7,stru->dwContextId,7,stru->MousePos.x,7,stru->MousePos.y);
								}
								break;
							case 18: /*HANDLE in wparam AND ULONG  in lparam*/
								sprintf(poslast,"%X%c%ld",wParam,7,lParam);
								break;
							case 19: /*ULONG in wparam AND STYLESTRUCT in lparam*/
								{
									STYLESTRUCT *stru=(LPSTYLESTRUCT) lParam;
									if (stru!=NULL)	 
									sprintf(poslast,"%ld%c%ld%c%ld",wParam,7,stru->styleOld,7,stru->styleNew);
								}
								break;
							case 20: /*HICON*/
								sprintf(poslast,"%X",lParam);
								break;
							case 21: /*LPNCCALCSIZE_PARAMS*/
								if (wParam==TRUE)
								{
									NCCALCSIZE_PARAMS *stru=(NCCALCSIZE_PARAMS *) lParam;
									if (stru!=NULL)	 
									sprintf(poslast,"%ld%c%ld%c%ld%c%ld%c%ld%c%ld%c%ld%c%ld%c%ld%c%ld%c%ld%c%ld%c%X%c%X%c%d%c%d%c%d%c%d%c%ld",
										stru->rgrc[0].left,7,stru->rgrc[0].top,7,stru->rgrc[0].right,7,stru->rgrc[0].bottom,7,
										stru->rgrc[1].left,7,stru->rgrc[1].top,7,stru->rgrc[1].right,7,stru->rgrc[1].bottom,7,
										stru->rgrc[2].left,7,stru->rgrc[2].top,7,stru->rgrc[2].right,7,stru->rgrc[2].bottom,7,
										(DWORD)stru->lppos->hwnd,7,(DWORD)stru->lppos->hwndInsertAfter,7,stru->lppos->x,7,stru->lppos->y,7,
										stru->lppos->cx,7,stru->lppos->cy,7,stru->lppos->flags);
								}
								else
								{
									RECT  *stru=(LPRECT) lParam;
									if (stru!=NULL)	 
									sprintf(poslast,"%ld%c%ld%c%ld%c%ld",stru->left,7,stru->top,7,stru->right,7,stru->bottom);
								}
								break;
							case 22: /*LPMSG*/
								{
									MSG *stru=(LPMSG) lParam;
									if (stru!=NULL)	 
									sprintf(poslast,"%X%c%ld%c%ld%c%X%c%ld%c%d%c%d",(DWORD)stru->hwnd,7,stru->message,7,stru->wParam,7,stru->lParam,7,stru->time,7,stru->pt.x,7,stru->pt.y);
								}
								break;
							case 23: /*POINTS*/
								sprintf(poslast,"%d%c%d",LOWORD(lParam),7,HIWORD(lParam));
								break;
							case 24: /*HANDLE in wparam AND HANDLE in lparam*/
								sprintf(poslast,"%X%c%X",wParam,7,lParam);
								break;
							case 25: /*MDINEXTMENU*/
								{
									MDINEXTMENU *stru=(LPMDINEXTMENU) lParam;
									if (stru!=NULL)	 
									sprintf(poslast,"%X%c%X%c%X",(DWORD)stru->hmenuIn,7,(DWORD)stru->hmenuNext,7,(DWORD)stru->hwndNext);
								}
								break;
							case 26: /*LPRECT*/
								{
									RECT *stru=(LPRECT) lParam;
									if (stru!=NULL)	 
									sprintf(poslast,"%d%c%d%c%d%c%d",stru->left,7,stru->top,7,stru->right,7,stru->bottom);
								}
								break;
							case 27: /*MDICREATESTRUCT*/
								{
									MDICREATESTRUCT *stru=(MDICREATESTRUCT *) lParam;
									if (stru!=NULL)	 
									{
									char name[500]; strcpy(name,stru->szTitle);
									sprintf(poslast,"%s%c%s%c%X%c%d%c%d%c%d%c%d%c%ld%c%ld",
										stru->szClass,7,name,7,(DWORD)stru->hOwner,7,
										stru->x,7,stru->y,7,stru->cx,7,stru->cy,7,stru->style,7,stru->lParam);
									}
								}
								break;
							case 28: /*LPUINT OR BOOL*/    
								{
									BOOL *stru=(LPBOOL) lParam;
									if (stru!=NULL)	 sprintf(poslast,"%d",*stru);
								}
								break;
							case 29: /*HANDLE in wparam AND PAINTSTRUCT*/
								{
									PAINTSTRUCT *stru=(PAINTSTRUCT *) lParam;
									if (stru!=NULL)	 
									sprintf(poslast,"%X%c%d%c%d%c%d%c%d%c%d%c%d%c%d%c%d",
										(DWORD)stru->hdc,7,stru->fErase,7,stru->rcPaint.left,7,
										stru->rcPaint.top,7,stru->rcPaint.right,7,stru->rcPaint.bottom,7,
										/*stru->fRestore*/0,7,/*stru->fIncUpdate*/0,7,/*stru->rgbReserved*/0);
								}
								break;
							case 30: /*HANDLE in wparam AND LPRECT*/
								{
									RECT *stru=(LPRECT) lParam;
									if (stru!=NULL)	 
									sprintf(poslast,"%X%c%d%c%d%c%d%c%d",wParam,7,stru->left,7,stru->top,7,stru->right,7,stru->bottom);
								}
								break;
							case 31: /*SCROLL MESSAGE*/
								{
									DWORD dwCurrTick=GetTickCount();
									if (dwCurrTick>=m_LastTick1+m_MessageDelay1)
										GPC.uLastMessage=0;

									if (GPC.uLastMessage!=message) m_LastTick1=dwCurrTick;

									DWORD dwRequest=LOWORD(wParam);
									DWORD dwPosition=HIWORD(wParam);
									char tmpstmp[100]; *tmpstmp=0;
									const char *cRequest=tmpstmp;
									if (dwRequest<=8)
									{
										DWORD tmpmask[]={0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80,0x100,0x200,0x400,};

										switch(message)
										{
										case WM_VSCROLL:
											{
												const char *names[]=
													{"LINEUP","LINEDOWN","PAGEUP","PAGEDOWN","THUMBPOSITION",
														"THUMBTRACK","TOP","BOTTOM","ENDSCROLL",};
												cRequest=names[dwRequest];
												bSendFlag=(m_VSCROLLMASK&tmpmask[dwRequest])==tmpmask[dwRequest];
											}
											break;
										case WM_HSCROLL:
											{
												const char *names[]=
													{"LINELEFT","LINERIGHT","PAGELEFT","PAGERIGHT","THUMBPOSITION",
														"THUMBTRACK","LEFT","RIGHT","ENDSCROLL",};
												cRequest=names[dwRequest];
												bSendFlag=(m_HSCROLLMASK&tmpmask[dwRequest])==tmpmask[dwRequest];
											}
											break;
										}

									}
									else sprintf(tmpstmp,"%d",dwRequest);

									char cLPARAM[500];*cLPARAM=0;
									if (lParam)
									{
										cLPARAM[400]=0;
										SCROLLINFO si={0};
										si.cbSize=sizeof(SCROLLINFO);
										si.fMask=SIF_ALL;
										::SendMessage((HWND)lParam,SBM_GETSCROLLINFO,0,(LPARAM)&si);
										if (bSendFlag)
										{
											::SendMessage((HWND)lParam,GPM_GETOBJECTNAME,99,(LPARAM)(cLPARAM+400));
											sprintf(cLPARAM,"%d\x7%d\x7%d\x7%d\x7%d\x7F%s",si.nMin,si.nMax,si.nPos,si.nPage,si.nTrackPos,cLPARAM+400);
										}
										if (GPU && GPU[m_UnitId&0xFFFF] && (GPU[m_UnitId&0xFFFF]->dwScrollFlags&0x01))
										{
											int dwNewAutoPos=si.nPos;

											switch(dwRequest)
											{
											case 0://LINEUP
												if (si.nPos>si.nMin) dwNewAutoPos=si.nPos-1;
												break;
											case 1://LINEDOWN
												if (si.nPos<si.nMax) dwNewAutoPos=si.nPos+1;
												break;
											case 2://PAGEUP
												if (si.nPos>si.nMin) 
													if (si.nMin+(int)si.nPage>si.nPos) dwNewAutoPos=si.nMin;
													else dwNewAutoPos=si.nPos-si.nPage;
												break;
											case 3://PAGEDOWN
												if (si.nPos<si.nMax) 
													if (si.nPos+(int)si.nPage>si.nMax) dwNewAutoPos=si.nMax;
													else dwNewAutoPos=si.nPos+si.nPage;
												break;
											case 4://THUMBPOSITION
												dwNewAutoPos=si.nTrackPos;
												break;
											case 5://THUMBTRACK
												dwNewAutoPos=si.nTrackPos;
												break;
											case 6://TOP
												dwNewAutoPos=si.nMax;
												break;
											case 7://BOTTOM
												dwNewAutoPos=si.nMin;
												break;
											case 8://ENDSCROLL
												dwNewAutoPos=si.nPos;
												break;
											}

											::SendMessage((HWND)lParam,SBM_SETPOS,dwNewAutoPos,FALSE);
										}

									}
									sprintf(poslast,"%X\x7F%s\x7F%d\x7F%s",wParam,cRequest,dwPosition,cLPARAM);
								}
								break;
							case 32: /*WM_MOUSEWHEEL*/
								{
									CRect re;
									::GetWindowRect(uHWND,re);
									POINT po1={lParam&0xFFFF,lParam/0x10000};
									int isinrect=re.PtInRect(po1);
									::ScreenToClient(uHWND,&po1);
									short wDistanse=HIWORD(wParam);
									sprintf(poslast,"%d%c%d%c%d%c%d%c%d%c%d%c",
										    (UINT)(lParam&0xFFFF),7,(UINT)(lParam/0x10000),
											127,po1.x,7,po1.y,
											127,wDistanse,
											127,isinrect,127
										);
									isinrect=(wParam&0xFFFF);
									DWORD keyfl[]={MK_CONTROL,MK_LBUTTON,MK_MBUTTON,MK_RBUTTON,MK_SHIFT,MK_XBUTTON1,MK_XBUTTON2,};
									char *keyflname[]={"MK_CONTROL","MK_LBUTTON","MK_MBUTTON","MK_RBUTTON","MK_SHIFT","MK_XBUTTON1","MK_XBUTTON2",};

									int nn;
									for(nn=0;nn<7;nn++)
										if ((isinrect&keyfl[nn])==keyfl[nn])
											strcat(poslast,keyflname[nn]);

									GPC.uLastMessage=0;
								}
								break;
							}

							ms+=poslast;

							if (SeqArray && ScriptArray)
							{
								UINT Id=SeqArray->GetIdByVal(alpmes[i]);
								if (Id!=0xFFFFFFFFL && (*ScriptArray)[Id]!="")
										GPC.m_Document->DoAnyMethodScript((*ScriptArray)[Id],iIdObj,ms);
							}
							ms+="\r";
							if (ms[2]==0x7F) ms.SetAt(2,(iIdObj&IS_DLG_UNIT)==0?'2':'3');
							AnsiToDos(ms,ms,1);
							ms.SetAt(0,250);
							ms.SetAt(1,250);

							GPC.WaitFor_m_MuteProc();

							FLGiIdObj=iIdObj;
							FLGmessage=message;
							FLGwParam=wParam;
							FLGlParam=lParam;

							if (bSendFlag && (GPC.uLastMessage!=message || GPC.uLastWparam!=wParam || GPC.uLastLparam!=lParam))
								len=m_Comm.GPSendSafeBlock(ms,ms.GetLength());

							GPC.Release_m_MuteProc();	
							if (bSendFlag && (GPC.uLastMessage!=message || GPC.uLastWparam!=wParam || GPC.uLastLparam!=lParam) && m_OutputEdit!=NULL)
							{
								try
								{
									m_OutputEdit->ReplaceSel("\r\nWMEVENT ");
									ms.Replace(254,GPC.DelimiterIn1);
									ms.Replace(253,GPC.DelimiterIn2);
									DosToAnsi(ms,ms);
									m_OutputEdit->ReplaceSel(ms);
								}
								catch(...)
								{
									GPC.m_ErrReport.GPWriteErrorLog("GPMessage", "GPSendObjMessage","");
									m_OutputEdit=NULL;
								}
							}
							delete[] poslast;
							GPC.uLastMessage=message;
							GPC.uLastWparam=wParam;
							GPC.uLastLparam=lParam;
						}
						break;
					}
			}
			if (m_MMessager)
			{
				UINT nMes;
				BOOL onM=FALSE,offM=FALSE;
				for(nMes=0; nMes<MAXMMESAGER;nMes++)
					if (m_MMessager[nMes].DestUnit!=NULL)
					{
						onM=m_MMessager[nMes].OnMessage==message;
						offM=m_MMessager[nMes].OffMessage==message;
						if (onM || offM)
						{
							BOOL proc=TRUE;
							int posre=0;
							while(offM && (posre=m_MMessager[nMes].OffMsgStr.Find("RECT=",posre))>=0)
							{
								CRect re;
								POINT po={0};
								m_LastScanf=sscanf(m_MMessager[nMes].OffMsgStr.Right(posre+=5),"%d,%d,%d,%d",&re.left,&re.top,&re.right,&re.bottom);
								switch(message)
								{
								case WM_LBUTTONDBLCLK: //client
								case WM_LBUTTONDOWN:
								case WM_LBUTTONUP:
								case WM_MBUTTONDBLCLK:
								case WM_MBUTTONDOWN:
								case WM_MBUTTONUP:
								case WM_RBUTTONDBLCLK:
								case WM_RBUTTONDOWN:
								case WM_RBUTTONUP:
								case WM_MOUSEHOVER:
								case WM_MOUSEMOVE:
	//							case WM_XBUTTONDBLCLK:	case WM_XBUTTONDOWN:	case WM_XBUTTONUP:
									po.x=LOWORD(lParam);po.y=HIWORD(lParam);
									proc=re.PtInRect(po);
									break;
								case WM_MOUSEWHEEL:
								case WM_NCMOUSEMOVE:
								case WM_NCLBUTTONDBLCLK:
								case WM_NCLBUTTONDOWN:
								case WM_NCLBUTTONUP:
								case WM_NCMBUTTONDBLCLK:
								case WM_NCMBUTTONDOWN:
								case WM_NCMBUTTONUP:
								case WM_NCRBUTTONDBLCLK:
								case WM_NCRBUTTONDOWN:
								case WM_NCRBUTTONUP:
	//							case WM_NCMOUSEHOVER:	case WM_NCXBUTTONDBLCLK:	case WM_NCXBUTTONDOWN:	case WM_NCXBUTTONUP:
									po.x=LOWORD(lParam);po.y=HIWORD(lParam);
									ScreenToClient(uHWND,&po);
									proc=re.PtInRect(po);
									break;
								}
								if (proc==TRUE) break;
							}
							if (offM) offM=proc;

							proc=TRUE;
							posre=0;
							while(onM && (posre=m_MMessager[nMes].OnMsgStr.Find("RECT=",posre))>=0)
							{
								CRect re;
								POINT po={0};
								m_LastScanf=sscanf(m_MMessager[nMes].OnMsgStr.Right(posre+=5),"%d,%d,%d,%d",&re.left,&re.top,&re.right,&re.bottom);
								switch(message)
								{
								case WM_LBUTTONDBLCLK: //client
								case WM_LBUTTONDOWN:
								case WM_LBUTTONUP:
								case WM_MBUTTONDBLCLK:
								case WM_MBUTTONDOWN:
								case WM_MBUTTONUP:
								case WM_RBUTTONDBLCLK:
								case WM_RBUTTONDOWN:
								case WM_RBUTTONUP:
								case WM_MOUSEHOVER:
								case WM_MOUSEMOVE:
	//							case WM_XBUTTONDBLCLK:	case WM_XBUTTONDOWN:	case WM_XBUTTONUP:
									po.x=LOWORD(lParam);po.y=HIWORD(lParam);
									proc=re.PtInRect(po);
									break;
								case WM_MOUSEWHEEL:
								case WM_NCMOUSEMOVE:
								case WM_NCLBUTTONDBLCLK:
								case WM_NCLBUTTONDOWN:
								case WM_NCLBUTTONUP:
								case WM_NCMBUTTONDBLCLK:
								case WM_NCMBUTTONDOWN:
								case WM_NCMBUTTONUP:
								case WM_NCRBUTTONDBLCLK:
								case WM_NCRBUTTONDOWN:
								case WM_NCRBUTTONUP:
	//							case WM_NCMOUSEHOVER:	case WM_NCXBUTTONDBLCLK:	case WM_NCXBUTTONDOWN:	case WM_NCXBUTTONUP:
									po.x=LOWORD(lParam);po.y=HIWORD(lParam);
									ScreenToClient(uHWND,&po);
									proc=re.PtInRect(po);
									break;
								}
								if (proc==TRUE) break;
							}
							if (onM) onM=proc;

							if (onM)
							{
								KillTimer(uHWND,10200+nMes);
								KillTimer(uHWND,10000+nMes);
								if (m_MMessager[nMes].OnTimerDeleay==0)
								{
									if (m_MMessager[nMes].OnProperty!="")	((GPUnit *)m_MMessager[nMes].DestUnit)->GPSetProperty(m_MMessager[nMes].OnProperty);
									if (m_MMessager[nMes].OnMethods!="") DoMessagerSub(m_MMessager[nMes].DestUnit,m_MMessager[nMes].OnMethods);
								}
								else SetTimer(uHWND,10000+nMes,m_MMessager[nMes].OnTimerDeleay,NULL);

								if (m_MMessager[nMes].OffTimerDeleay!=0)
									SetTimer(uHWND,10200+nMes,m_MMessager[nMes].OffTimerDeleay,NULL);
							}
							if (offM)
							{
								KillTimer(uHWND,10200+nMes);
								KillTimer(uHWND,10000+nMes);
								if (m_MMessager[nMes].OffProperty!="")	((GPUnit *)m_MMessager[nMes].DestUnit)->GPSetProperty(m_MMessager[nMes].OffProperty);
								if (m_MMessager[nMes].OffMethods!="") DoMessagerSub(m_MMessager[nMes].DestUnit,m_MMessager[nMes].OffMethods);
							}
						}
					}
			}
		}
	}
	return ret;
}

void GPMessage::DelAllMessages()
{
	if (ScriptArray!=NULL && SeqArray!=NULL && AnswArray!=NULL)
	{
		delete ScriptArray;
		delete AnswArray;
		delete SeqArray;
		ScriptArray=AnswArray=SeqArray=NULL;
	}
	if (m_UnitId && GPU && GPU[m_UnitId&0xFFFF] && GPU[m_UnitId&0xFFFF]->UnitType==GPUnit::UT_CONTROL && GPU[m_UnitId&0xFFFF]->UnitHWND)
		::SendMessage(GPU[m_UnitId&0xFFFF]->UnitHWND,GPM_AX_DELALLEVENTS,0,0);

	*CurME_List=0;
	RetNCHITTEST=0;
}


void GPMessage::AddMMesager(void *DestUnit, const char *OnProperty, const char *OffProperty, const char *OnMethods, const char *OffMethods, const char *OnMsgStr, const char *OffMsgStr, const char *OnMessage, const char *OffMessage, UINT OnTimerDeleay, UINT OffTimerDeleay)
{
	if (DestUnit!=NULL)
	{
		UINT i;
		if (m_MMessager==NULL) 
		{
			m_MMessager=new MMESSAGERSTRUCT [MAXMMESAGER];
			for(i=0; i<MAXMMESAGER;i++)
			{
				m_MMessager[i].DestUnit=NULL;
				m_MMessager[i].OnProperty="";
				m_MMessager[i].OffProperty="";
				m_MMessager[i].OnMethods="";
				m_MMessager[i].OffMethods="";
				m_MMessager[i].OnMsgStr="";
				m_MMessager[i].OffMsgStr="";
				m_MMessager[i].OnMsgStrInit="";
				m_MMessager[i].OffMsgStrInit="";
				m_MMessager[i].OnMessage=0;
				m_MMessager[i].OffMessage=0;
				m_MMessager[i].OnTimerDeleay=0;
				m_MMessager[i].OffTimerDeleay=0;
			}
		}

		for(i=0; i<MAXMMESAGER && m_MMessager[i].DestUnit!=NULL;i++);

		if (i<MAXMMESAGER)
		{
			m_MMessager[i].DestUnit=DestUnit;
			m_MMessager[i].OnProperty=OnProperty;
			m_MMessager[i].OffProperty=OffProperty;
			m_MMessager[i].OnMethods=OnMethods;
			m_MMessager[i].OffMethods=OffMethods;
			m_MMessager[i].OnMsgStrInit=OnMsgStr;
			m_MMessager[i].OffMsgStrInit=OffMsgStr;
			m_MMessager[i].OnTimerDeleay=OnTimerDeleay;
			m_MMessager[i].OffTimerDeleay=OffTimerDeleay;
			m_MMessager[i].OnMessage=0;
			m_MMessager[i].OffMessage=0;

			UINT nMes;
			char ms[100];
			strncpy(ms,OnMessage,90);
			ms[90]=0;
			_strupr(ms);
			char *pos=strchr(ms,';');
			if (pos!=NULL) *pos=0;
			m_MMessager[i].OnMsgStr=ms;

			for(nMes=0;nMes<N_WND_MESSAGE && strcmp(ms,alpmes[nMes])!=0;nMes++);
			if (nMes<N_WND_MESSAGE) m_MMessager[i].OnMessage=auimes[nMes];
			
			strncpy(ms,OffMessage,90);
			ms[90]=0;
			_strupr(ms);
			pos=strchr(ms,';');
			if (pos!=NULL) *pos=0;
			m_MMessager[i].OffMsgStr=ms;

			for(nMes=0;nMes<N_WND_MESSAGE && strcmp(ms,alpmes[nMes])!=0;nMes++);
			if (nMes<N_WND_MESSAGE) m_MMessager[i].OffMessage=auimes[nMes];
		}
	}
}

void GPMessage::DoMessagerSub(void *gpunit, CString &iSubs)
{
	if (iSubs!="")
	{
		int iPosEnd=1;
		int iPosStart=0;
		CString sSub;
		while(iPosStart>=0)
		{
			iPosEnd=iSubs.Find(2,iPosStart);
			int len=iPosEnd-iPosStart-1;
			if (len>0)
			{
				sSub=iSubs.Mid(iPosStart,len);
				iPosStart=iPosEnd+1;
			}
			else
			{
				sSub=iSubs.Mid(iPosStart);
				iPosStart=-1;
			}
			if (sSub.GetLength()>0)
			{
				((GPUnit *)gpunit)->DoMethod(sSub.GetBuffer(sSub.GetLength()+1),NULL);
				sSub.ReleaseBuffer();
			}
		}
	}
}

UINT GPMessage::ProcMessagerTimer(UINT TimId, HWND uHWND)
{
	if (m_MMessager!=NULL)
	{
		if ((TimId>=10000 && TimId<10200)||(TimId>=10200 && TimId<10400))
		{
			KillTimer(uHWND,TimId);
			UINT nMes=TimId%200;
			if (nMes<MAXMMESAGER && m_MMessager[nMes].DestUnit!=NULL) 
			{
				if (TimId<10200)
				{
					if (m_MMessager[nMes].OnProperty!="")	((GPUnit *)m_MMessager[nMes].DestUnit)->GPSetProperty(m_MMessager[nMes].OnProperty);
					if (m_MMessager[nMes].OnMethods!="") DoMessagerSub(m_MMessager[nMes].DestUnit,m_MMessager[nMes].OnMethods);
				}
				else
				{
					if (m_MMessager[nMes].OffProperty!="")	((GPUnit *)m_MMessager[nMes].DestUnit)->GPSetProperty(m_MMessager[nMes].OffProperty);
					if (m_MMessager[nMes].OffMethods!="") DoMessagerSub(m_MMessager[nMes].DestUnit,m_MMessager[nMes].OffMethods);
				}
			}
		}
	}
	return 0;
}

void GPMessage::UpdateMessagerState(const char *iMessage, UINT iFlg)
{
	if (strcmp(iMessage,"WM_MOUSELEAVE")==0)
	{
		if (iFlg!=0) // delete
			MessagerState|=0x0001;
		else
			MessagerState&=0xFFFFFFFF-0x00000001;
	}
	else
	if (strcmp(iMessage,"WM_MOUSEINSIDE")==0)
	{
		if (iFlg!=0) // delete
			MessagerState|=0x0004;
		else
			MessagerState&=0xFFFFFFFF-0x00000004;
	}
	else
	if (strcmp(iMessage,"WM_MOUSEHOVER")==0)
	{
		if (iFlg!=0) // delete
			MessagerState|=0x00010;
		else
			MessagerState&=0xFFFFFFFF-0x00000010;
	}
	else
	if (strcmp(iMessage,"WM_NCMOUSELEAVE")==0)
	{
		if (iFlg!=0) // delete
			MessagerState|=0x000100;
		else
			MessagerState&=0xFFFFFFFF-0x00000100;
	}
	else
	if (strcmp(iMessage,"WM_NCMOUSEINSIDE")==0)
	{
		if (iFlg!=0) // delete
			MessagerState|=0x000400;
		else
			MessagerState&=0xFFFFFFFF-0x00000400;
	}
	else
	if (strcmp(iMessage,"WM_NCMOUSEHOVER")==0)
	{
		if (iFlg!=0) // delete
			MessagerState|=0x01000;
		else
			MessagerState&=0xFFFFFFFF-0x00001000;
	}
	

}

void GPMessage::ProcMessagerState(HWND uHWND, UINT iMessage)
{
	switch(iMessage)
	{
	case WM_MOUSEMOVE:
		if ((MessagerState&0x00000001)!=0)
		{
			if ((MessagerState&0x00000002)==0)
			{
				TRACKMOUSEEVENT te={0};
				te.cbSize=sizeof(te);
				te.dwFlags=TME_LEAVE;
				te.hwndTrack=uHWND;
				_TrackMouseEvent(&te);
			}
		}

		if ((MessagerState&0x00000004)!=0)
		{
			if ((MessagerState&0x00000008)==0)
			{
				GPSendObjEvent(uHWND,LastIdObj,"WM_MOUSEINSIDE","");
				TRACKMOUSEEVENT te={0};
				te.cbSize=sizeof(te);
				te.dwFlags=TME_LEAVE;
				te.hwndTrack=uHWND;
				_TrackMouseEvent(&te);

			}
		}

		if ((MessagerState&0x00000010)!=0)
		{
			if ((MessagerState&0x00000020)==0)
			{
				TRACKMOUSEEVENT te={0};
				te.cbSize=sizeof(te);
				te.dwFlags=TME_HOVER;
				te.hwndTrack=uHWND;
				te.dwHoverTime=1000;
				_TrackMouseEvent(&te);

			}
		}

		MessagerState|=0x0002;
		MessagerState|=0x0008;
		MessagerState|=0x0020;
		break;
	case WM_MOUSELEAVE:
		MessagerState&=0xFFFFFFFF-0x00000002-0x00000008-0x00000020;
		break;
	case WM_MOUSEHOVER:
		MessagerState&=0xFFFFFFFF-0x00000020;
		break;

	case WM_NCMOUSEMOVE:
		if ((MessagerState&0x00000100)!=0)
		{
			if ((MessagerState&0x00000200)==0)
			{
				TRACKMOUSEEVENT te={0};
				te.cbSize=sizeof(te);
				te.dwFlags=TME_LEAVE|0x3FFFFFFF/*TME_NONCLIENT*/;
				te.hwndTrack=uHWND;
				_TrackMouseEvent(&te);
			}
		}

		if ((MessagerState&0x00000400)!=0)
		{
			if ((MessagerState&0x00000800)==0)
			{
				GPSendObjEvent(uHWND,LastIdObj,"WM_MOUSEINSIDE","");
				TRACKMOUSEEVENT te={0};
				te.cbSize=sizeof(te);
				te.dwFlags=TME_LEAVE|0x3FFFFFFF/*TME_NONCLIENT*/;
				te.hwndTrack=uHWND;
				_TrackMouseEvent(&te);

			}
		}

		if ((MessagerState&0x00001000)!=0)
		{
			if ((MessagerState&0x00002000)==0)
			{
				TRACKMOUSEEVENT te={0};
				te.cbSize=sizeof(te);
				te.dwFlags=TME_HOVER|0x3FFFFFFF/*TME_NONCLIENT*/;
				te.hwndTrack=uHWND;
				te.dwHoverTime=1000;
				_TrackMouseEvent(&te);

			}
		}

		MessagerState|=0x0200;
		MessagerState|=0x0800;
		MessagerState|=0x2000;
		break;
	case WM_CAPTURECHANGED:
		MessagerState&=0xFFFFFFFF-0x00000200-0x00000800-0x00002000;
		break;
	case 0x00AA:// FIND WM_NCMOUSEHOVER
		MessagerState&=0xFFFFFFFF-0x00002000;
	case 0x00AB:
		MessagerState&=0xFFFFFFFF-0x00002000;
	case 0x00AC:
		MessagerState&=0xFFFFFFFF-0x00002000;
	case 0x00AD:
		MessagerState&=0xFFFFFFFF-0x00002000;
	case 0x00AE:
		MessagerState&=0xFFFFFFFF-0x00002000;
	case 0x00AF:
		MessagerState&=0xFFFFFFFF-0x00002000;
		break;
	
	
	
	}
}


void GPMessage::DelMMesager(void *DestUnit, const char *OnMessage)
{
	UINT nMes;
	if (m_MMessager!=NULL)
		for(nMes=0; nMes<MAXMMESAGER;nMes++)
			if (m_MMessager[nMes].DestUnit!=NULL && m_MMessager[nMes].DestUnit==DestUnit)
			{
				m_MMessager[nMes].DestUnit=NULL;
				m_MMessager[nMes].OnProperty="";
				m_MMessager[nMes].OffProperty="";
				m_MMessager[nMes].OnMethods="";
				m_MMessager[nMes].OffMethods="";
				m_MMessager[nMes].OnMsgStr="";
				m_MMessager[nMes].OffMsgStr="";
				m_MMessager[nMes].OnMsgStrInit="";
				m_MMessager[nMes].OffMsgStrInit="";
				m_MMessager[nMes].OnMessage=0;
				m_MMessager[nMes].OffMessage=0;
				m_MMessager[nMes].OnTimerDeleay=0;
				m_MMessager[nMes].OffTimerDeleay=0;
			}
}

void GPMessage::DelAllMMesager()
{
	if (m_MMessager!=NULL)	delete[]  m_MMessager;
	m_MMessager=NULL;
}

const char * GPMessage::GetActiveMessages()
{
	return CurME_List;
}
