// ComPortSetings.cpp : implementation file
//

#include "stdafx.h"
#include "GP_term.h"
#include "ComPortSetings.h"
#include "GP_TermView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CComPortSetings dialog
char *  szComPort[] =			{  "COM1", "COM2", "COM3","COM4"  };
char *  szBaud[] =				{ "110", "300", "600", "1200", "2400", "4800", "9600", "14400", "19200","38400", "56000", "57600", "115200", "128000", "256000"};
DWORD   BaudTable[] =			{ CBR_110, CBR_300, CBR_600, CBR_1200, CBR_2400,CBR_4800, CBR_9600, CBR_14400, CBR_19200, CBR_38400,CBR_56000, CBR_57600, CBR_115200, CBR_128000, CBR_256000	} ;
char *  szParity[] =			{ "None", "Even", "Odd", "Mark", "Space" };
DWORD   ParityTable[] =			{  NOPARITY, EVENPARITY, ODDPARITY, MARKPARITY, SPACEPARITY  } ;
char *  szStopBits[] =			{  "1", "1.5", "2"  };
DWORD   StopBitsTable[] =		{ ONESTOPBIT, ONE5STOPBITS, TWOSTOPBITS } ;
char *  szDTRControlStrings[] =	{ "Enable", "Disable", "Handshake" };
DWORD   DTRControlTable[] =		{ DTR_CONTROL_ENABLE, DTR_CONTROL_DISABLE, DTR_CONTROL_HANDSHAKE };
char *  szRTSControlStrings[] =	{ "Enable", "Disable", "Handshake", "Toggle" };
DWORD   RTSControlTable[] =		{ RTS_CONTROL_ENABLE, RTS_CONTROL_DISABLE,RTS_CONTROL_HANDSHAKE, RTS_CONTROL_TOGGLE };
DWORD   EventFlagsTable[] =		{ EV_BREAK, EV_CTS, EV_DSR, EV_ERR, EV_RING, EV_RLSD, EV_RXCHAR, EV_RXFLAG, EV_TXEMPTY};


CComPortSetings::CComPortSetings(GP_comm *iGPc)	: CDialog(CComPortSetings::IDD)
{
	//{{AFX_DATA_INIT(CComPortSetings)
	m_vEOF = 0;
	m_vERROR = 0;
	m_vEVENT = 0;
	m_vXOFF = 0;
	m_vLXOFF = 64;
	m_vXON = 0;
	m_LXON = 64;
	m_PackSize = 0;
	//}}AFX_DATA_INIT
	GPc=iGPc;
}


void CComPortSetings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComPortSetings)
	DDX_Control(pDX, IDC_COMBOSHUTDOWN, m_ComboShutDown);
	DDX_Control(pDX, IDC_EDITNAME, m_EditName);
	DDX_Control(pDX, IDC_COMBOTERMTYPE, m_ComboType);
	DDX_Control(pDX, IDC_CHECKLOCKECHO, m_CheckLockEcho);
	DDX_Control(pDX, IDC_EDITXONLIM, m_LimXON);
	DDX_Control(pDX, IDC_EDITXONCHAR, m_CharXON);
	DDX_Control(pDX, IDC_EDITXOFFLIM, m_LimXOFF);
	DDX_Control(pDX, IDC_EDITXOFFCHAR, m_CharXOFF);
	DDX_Control(pDX, IDC_EDITEVENTCHAR, m_CharEVENT);
	DDX_Control(pDX, IDC_EDITERRORCHAR, m_CharERROR);
	DDX_Control(pDX, IDC_EDITEOFCHAR, m_CharEOF);
	DDX_Text(pDX, IDC_EDITEOFCHAR, m_vEOF);
	DDV_MinMaxUInt(pDX, m_vEOF, 0, 255);
	DDX_Text(pDX, IDC_EDITERRORCHAR, m_vERROR);
	DDV_MinMaxUInt(pDX, m_vERROR, 0, 255);
	DDX_Text(pDX, IDC_EDITEVENTCHAR, m_vEVENT);
	DDV_MinMaxUInt(pDX, m_vEVENT, 0, 255);
	DDX_Text(pDX, IDC_EDITXOFFCHAR, m_vXOFF);
	DDV_MinMaxUInt(pDX, m_vXOFF, 0, 255);
	DDX_Text(pDX, IDC_EDITXOFFLIM, m_vLXOFF);
	DDV_MinMaxUInt(pDX, m_vLXOFF, 64, 65535);
	DDX_Text(pDX, IDC_EDITXONCHAR, m_vXON);
	DDV_MinMaxUInt(pDX, m_vXON, 0, 255);
	DDX_Text(pDX, IDC_EDITXONLIM, m_LXON);
	DDV_MinMaxUInt(pDX, m_LXON, 64, 65535);
	DDX_Text(pDX, IDC_EDITPACKETSIZE, m_PackSize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CComPortSetings, CDialog)
	//{{AFX_MSG_MAP(CComPortSetings)
	ON_CBN_SELCHANGE(IDC_COMBOTERMTYPE, OnSelchangeCombotermtype)
	ON_BN_CLICKED(IDC_BUTTONDELIMITERS, OnButtondelimiters)
	ON_EN_CHANGE(IDC_EDITNAME, OnChangeEditname)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComPortSetings message handlers

BOOL CComPortSetings::OnInitDialog()
{
	CDialog::OnInitDialog();

	DWORD wCount, wMaxel ,wPosition;
    char szBuffer[ 500];

    for(wCount = 0; wCount < 4; wCount++)
	{
		wPosition=SendDlgItemMessage(IDC_PORTCOMBO,CB_ADDSTRING, 0,(LPARAM)(LPSTR) szComPort[wCount]) ;
		if (strcmp(GPc->GetComport(),szComPort[wCount])==0)  SendDlgItemMessage( IDC_PORTCOMBO, CB_SETCURSEL,(WPARAM) wPosition,0L);
	}

	wMaxel=sizeof( BaudTable ) / sizeof( BaudTable[ 0 ] );
    for(wCount = 0; wCount < wMaxel; wCount++)
	{
		wPosition=SendDlgItemMessage(IDC_BAUDCOMBO,CB_ADDSTRING, 0,(LPARAM)(LPSTR) szBaud[wCount]) ;
		if (GPc->GetdcbBaudRate()==BaudTable[wCount])  SendDlgItemMessage( IDC_BAUDCOMBO, CB_SETCURSEL,(WPARAM) wPosition,0L);
	}

	wMaxel=sizeof( ParityTable ) / sizeof( ParityTable[ 0 ] );
    for(wCount = 0; wCount < wMaxel; wCount++)
	{
		wPosition=SendDlgItemMessage(IDC_PARITYCOMBO,CB_ADDSTRING, 0,(LPARAM)(LPSTR) szParity[wCount]) ;
		if (GPc->GetdcbParity()==ParityTable[wCount])  SendDlgItemMessage( IDC_PARITYCOMBO, CB_SETCURSEL,(WPARAM) wPosition,0L);
	}

	wMaxel=sizeof( StopBitsTable ) / sizeof( StopBitsTable[ 0 ] );
    for(wCount = 0; wCount < wMaxel; wCount++)
	{
		wPosition=SendDlgItemMessage(IDC_STOPBITSCOMBO,CB_ADDSTRING, 0,(LPARAM)(LPSTR) szStopBits[wCount]) ;
		if (GPc->GetdcbStopBits()==StopBitsTable[wCount])  SendDlgItemMessage( IDC_STOPBITSCOMBO, CB_SETCURSEL,(WPARAM) wPosition,0L);
	}

    for(wCount = 5; wCount < 9; wCount++)
	{
		wsprintf( szBuffer, "%d", wCount ) ;
		wPosition=SendDlgItemMessage(IDC_DATABITSCOMBO,CB_ADDSTRING, 0,(LPARAM) (LPSTR) szBuffer) ;
		if (GPc->GetdcbByteSize()==wCount)  SendDlgItemMessage( IDC_DATABITSCOMBO, CB_SETCURSEL,(WPARAM) wPosition,0L);
	}

    for(wCount = 0; wCount < 3; wCount++)
	{
		wPosition=SendDlgItemMessage(IDC_DTRCONTROL,CB_ADDSTRING, 0,(LPARAM)(LPSTR) szDTRControlStrings[wCount]) ;
		if (GPc->GetdcbfDtrControl()==DTRControlTable[wCount])  SendDlgItemMessage( IDC_DTRCONTROL, CB_SETCURSEL,(WPARAM) wPosition,0L);
	}

    for(wCount = 0; wCount < 4; wCount++)
	{
		wPosition=SendDlgItemMessage(IDC_RTSCONTROL,CB_ADDSTRING, 0,(LPARAM)(LPSTR) szRTSControlStrings[wCount]) ;
		if (GPc->GetdcbfRtsControl()==RTSControlTable[wCount])  SendDlgItemMessage( IDC_RTSCONTROL, CB_SETCURSEL,(WPARAM) wPosition,0L);
	}


	CheckDlgButton(IDC_CHECKHIDDEN			, AfxGetApp()->GetProfileInt(GPc->GPSectionName, "m_HideTerminal",0));
	CheckDlgButton(IDC_CHECKDISABLEALT		, AfxGetApp()->GetProfileInt(GPc->GPSectionName, "dwAltFlag",0));

	CheckDlgButton(IDC_CHECKABORTONERROR	, GPc->GetdcbfAbortOnError());
	CheckDlgButton(IDC_CHECKBINARY			, GPc->GetdcbfBinary());
	CheckDlgButton(IDC_CHECKDSRSENSITIVITY	, GPc->GetdcbfDsrSensitivity());
	CheckDlgButton(IDC_CHECKERRORCHAR		, GPc->GetdcbfErrorChar());
	CheckDlgButton(IDC_CHECKINX				, GPc->GetdcbfInX());
	CheckDlgButton(IDC_CHECKNULLREPLACE		, GPc->GetdcbfNull());
	CheckDlgButton(IDC_CHECKOUTX			, GPc->GetdcbfOutX());
	CheckDlgButton(IDC_CHECKUOTXCTSFLOW		, GPc->GetdcbfOutxCtsFlow());
	CheckDlgButton(IDC_CHECKUOTXDSRFLOW		, GPc->GetdcbfOutxDsrFlow());
	CheckDlgButton(IDC_CHECKTXCONTONXOFF	, GPc->GetdcbfTXContinueOnXoff());
	CheckDlgButton(IDC_CHECKPARITY			, GPc->GetdcbfParity());
	CheckDlgButton(IDC_CHECKCRLF			, AfxGetApp()->GetProfileInt(GPc->GPSectionName, "m_CheckCRLF",1));
	CheckDlgButton(IDC_CHECKCRLF2			, AfxGetApp()->GetProfileInt(GPc->GPSectionName, "m_CheckCRLF2",0));
	CheckDlgButton(IDC_CHECKLOCKECHO		, GPc->GetLockEventsEcho());

	DWORD dwSHUTDOWN=AfxGetApp()->GetProfileInt(GPc->GPSectionName, "m_ShutdownFlags",0x1000);

	CheckDlgButton(IDC_CHECKLOCKEND			, (dwSHUTDOWN&0x1000)==0x1000);
	CheckDlgButton(IDC_CHECKLOCKEND2		, (dwSHUTDOWN&0x0001)==0x0001);

	m_ComboShutDown.AddString("LOGOFF");
	m_ComboShutDown.AddString("POWEROFF");
	m_ComboShutDown.AddString("REBOOT");
	m_ComboShutDown.AddString("SHUTDOWN");

	m_ComboShutDown.AddString("FORCE_LOGOFF");
	m_ComboShutDown.AddString("FORCE_POWEROFF");
	m_ComboShutDown.AddString("FORCE_REBOOT");
	m_ComboShutDown.AddString("FORCE_SHUTDOWN");

	m_ComboShutDown.AddString("FORCEIFHUNG_LOGOFF");
	m_ComboShutDown.AddString("FORCEIFHUNG_POWEROFF");
	m_ComboShutDown.AddString("FORCEIFHUNG_REBOOT");
	m_ComboShutDown.AddString("FORCEIFHUNG_SHUTDOWN");

	m_ComboShutDown.AddString("LOCKWORKSTATION");


	m_ComboShutDown.SetCurSel(((dwSHUTDOWN/0x10)&0x3)+ ((dwSHUTDOWN/0x100)&0x3)*4);


	m_CharEOF.LimitText(3);
	m_CharERROR.LimitText(3);
	m_CharEVENT.LimitText(3);
	m_CharXOFF.LimitText(3);
	m_CharXON.LimitText(3);
	m_LimXON.LimitText(5);
	m_LimXOFF.LimitText(5);

	SetDlgItemInt(IDC_EDITXONLIM,	GPc->GetdcbXonLim());
	SetDlgItemInt(IDC_EDITXONCHAR,	GPc->GetdcbXonChar());
	SetDlgItemInt(IDC_EDITXOFFLIM,	GPc->GetdcbXoffLim());
	SetDlgItemInt(IDC_EDITXOFFCHAR, GPc->GetdcbXoffChar());
	SetDlgItemInt(IDC_EDITEVENTCHAR,GPc->GetdcbEvtChar());
	SetDlgItemInt(IDC_EDITERRORCHAR,GPc->GetdcbErrorChar());
	SetDlgItemInt(IDC_EDITEOFCHAR,	GPc->GetdcbEofChar());
	SetDlgItemInt(IDC_EDITPACKETSIZE,	GPc->GetBlockSize());

	SetDlgItemText(IDC_EDITCOMMENT,GPc->GetComment());
	SetDlgItemText(IDC_EDITINITSTR,GPc->GetInitStr());
	SetDlgItemText(IDC_EDITINITSTR2,GPc->GetEndStr());

	CheckDlgButton(IDC_CHECKTELNET, (GPc->GetTelnetFlag()&0x1)!=0);

	SetDlgItemText(IDC_EDITCMDLINE, AfxGetApp()->GetProfileString(GPc->GPSectionName, "CMDLINE",""));
	SetDlgItemText(IDC_EDITTITLE, AfxGetApp()->GetProfileString(GPc->GPSectionName, "TERMTITLE",""));
	SetDlgItemText(IDC_EDITTITLE2,AfxGetApp()->GetProfileString(GPc->GPSectionName, "MSGBOXTITLE",""));
	SetDlgItemText(IDC_EDITTITLE3,AfxGetApp()->GetProfileString(GPc->GPSectionName, "ERRBOXTITLE",""));

	m_TermCap.FillComboTerminalType(::GetDlgItem(m_hWnd,IDC_COMBOTERMTYPE),GPc->m_TerminalID);

	SetDlgItemInt(IDC_EDITROWS,AfxGetApp()->GetProfileInt(GPc->GPSectionName, "INITROWS",25));
	SetDlgItemInt(IDC_EDITCOLUMNS,AfxGetApp()->GetProfileInt(GPc->GPSectionName, "INITCOLUMNS",80));

	SetDlgItemText(IDC_EDITNAME,ExtractField(GPc->GPSectionName, 2 ,"\\"));


	return TRUE;
}

#include "GP_TermView.h"

void CComPortSetings::OnOK()
{
	CString csTmpName;
	m_EditName.GetWindowText(csTmpName);
	CString csTmpSectionName;
	csTmpSectionName.Format("COMSETLIST\\%s",csTmpName);

	BOOL bDoIt=TRUE;
	if (AfxGetApp()->GetProfileInt(csTmpSectionName, "com_type",0xFFFFFFFF)!=0xFFFFFFFF)
	{
		#ifdef RUS
			csTmpName= "Перезаписать информацию о соединении - " + csTmpName + " ?";
		#else
			csTmpName= "Overwrite connection " + csTmpName + " ?";
		#endif
		bDoIt=(AfxMessageBox(csTmpName,MB_ICONQUESTION|MB_APPLMODAL|MB_OKCANCEL,0)==IDOK);
	}


	if (bDoIt)
	{
		GPc->GPSectionName=csTmpSectionName;


		char tmptxt[1000];
		GetDlgItemText(IDC_PORTCOMBO, tmptxt, sizeof(tmptxt));
		GPc->SetComport			(	tmptxt);
		GPc->SetdcbBaudRate		( GetdwTTYItem( IDC_BAUDCOMBO, szBaud, BaudTable,sizeof(BaudTable)/sizeof(BaudTable[0])));
		GPc->SetdcbParity		( GetbTTYItem(  IDC_PARITYCOMBO, szParity, ParityTable, sizeof(ParityTable)/sizeof(ParityTable[0])));
		GPc->SetdcbStopBits		( GetbTTYItem(  IDC_STOPBITSCOMBO, szStopBits, StopBitsTable, sizeof(StopBitsTable)/sizeof(StopBitsTable[0])));
		GPc->SetdcbfDtrControl	( GetbTTYItem(  IDC_DTRCONTROL, szDTRControlStrings, DTRControlTable, sizeof(DTRControlTable)/sizeof(DTRControlTable[0])));
		GPc->SetdcbfRtsControl	( GetbTTYItem(  IDC_RTSCONTROL, szRTSControlStrings, RTSControlTable, sizeof(RTSControlTable)/sizeof(RTSControlTable[0])));
		GPc->SetdcbByteSize		( GetDlgItemInt(IDC_DATABITSCOMBO, NULL, FALSE));
		GPc->SetBlockSize		( GetDlgItemInt(IDC_EDITPACKETSIZE, NULL, FALSE));


		if ( GPC.m_View && m_Comm.GPSectionName==GPc->GPSectionName)
		{
			((CGP_TermView *)GPC.m_View)->m_CRLFflag=IsDlgButtonChecked(IDC_CHECKCRLF);
			((CGP_TermView *)GPC.m_View)->m_CRLFflag2=IsDlgButtonChecked(IDC_CHECKCRLF2);
		}
		AfxGetApp()->WriteProfileInt(GPc->GPSectionName, "m_CheckCRLF",IsDlgButtonChecked(IDC_CHECKCRLF));
		AfxGetApp()->WriteProfileInt(GPc->GPSectionName, "m_CheckCRLF2",IsDlgButtonChecked(IDC_CHECKCRLF2));

		if (IsDlgButtonChecked(IDC_CHECKABORTONERROR	)==0)
			GPc->SetdcbfAbortOnError(FALSE);		else GPc->SetdcbfAbortOnError(TRUE);
		if (IsDlgButtonChecked(IDC_CHECKPARITY	)==0)
			GPc->SetdcbfParity(FALSE);				else GPc->SetdcbfParity(TRUE);
		if (IsDlgButtonChecked(IDC_CHECKBINARY			)==0)
			GPc->SetdcbfBinary(FALSE);				else GPc->SetdcbfBinary(TRUE);
		if (IsDlgButtonChecked(IDC_CHECKDSRSENSITIVITY	)==0)
			GPc->SetdcbfDsrSensitivity(FALSE);		else GPc->SetdcbfDsrSensitivity(TRUE);
		if (IsDlgButtonChecked(IDC_CHECKERRORCHAR		)==0)
			GPc->SetdcbfErrorChar(FALSE);			else GPc->SetdcbfErrorChar(TRUE);
		if (IsDlgButtonChecked(IDC_CHECKINX				)==0)
			GPc->SetdcbfInX(FALSE);					else GPc->SetdcbfInX(TRUE);
		if (IsDlgButtonChecked(IDC_CHECKNULLREPLACE		)==0)
			GPc->SetdcbfNull(FALSE);				else GPc->SetdcbfNull(TRUE);
		if (IsDlgButtonChecked(IDC_CHECKOUTX			)==0)
			GPc->SetdcbfOutX(FALSE);				else GPc->SetdcbfOutX(TRUE);
		if (IsDlgButtonChecked(IDC_CHECKUOTXCTSFLOW		)==0)
			GPc->SetdcbfOutxCtsFlow(FALSE);			else GPc->SetdcbfOutxCtsFlow(TRUE);
		if (IsDlgButtonChecked(IDC_CHECKUOTXDSRFLOW		)==0)
			GPc->SetdcbfOutxDsrFlow(FALSE);			else GPc->SetdcbfOutxDsrFlow(TRUE);
		if (IsDlgButtonChecked(IDC_CHECKTXCONTONXOFF	)==0)
			GPc->SetdcbfTXContinueOnXoff(FALSE);	else GPc->SetdcbfTXContinueOnXoff(TRUE);

		GPc->SetdcbXonLim		(GetDlgItemInt(IDC_EDITXONLIM	));
		GPc->SetdcbXonChar		(GetDlgItemInt(IDC_EDITXONCHAR	));
		GPc->SetdcbXoffLim		(GetDlgItemInt(IDC_EDITXOFFLIM	));
		GPc->SetdcbXoffChar		(GetDlgItemInt(IDC_EDITXOFFCHAR	));
		GPc->SetdcbEvtChar		(GetDlgItemInt(IDC_EDITEVENTCHAR));
		GPc->SetdcbErrorChar	(GetDlgItemInt(IDC_EDITERRORCHAR));
		GPc->SetdcbEofChar		(GetDlgItemInt(IDC_EDITEOFCHAR	));

		CString tmpCS;
		GetDlgItemText(IDC_EDITCMDLINE,tmpCS);
		AfxGetApp()->WriteProfileString(GPc->GPSectionName, "CMDLINE",(LPCSTR)tmpCS);

		GetDlgItemText(IDC_EDITTITLE,tmpCS);
		AfxGetApp()->WriteProfileString(GPc->GPSectionName, "TERMTITLE",(LPCSTR)tmpCS);

		GetDlgItemText(IDC_EDITTITLE2,tmpCS);
		AfxGetApp()->WriteProfileString(GPc->GPSectionName, "MSGBOXTITLE",(LPCSTR)tmpCS);

		GetDlgItemText(IDC_EDITTITLE3,tmpCS);
		AfxGetApp()->WriteProfileString(GPc->GPSectionName, "ERRBOXTITLE",(LPCSTR)tmpCS);

		AfxGetApp()->WriteProfileInt(GPc->GPSectionName, "m_HideTerminal",IsDlgButtonChecked(IDC_CHECKHIDDEN)?1:0);
		AfxGetApp()->WriteProfileInt(GPc->GPSectionName, "dwAltFlag",IsDlgButtonChecked(IDC_CHECKDISABLEALT)?1:0);

		GetDlgItemText(IDC_EDITINITSTR,tmptxt,990);
		GPc->SetInitStr(tmptxt);
		GetDlgItemText(IDC_EDITINITSTR2,tmptxt,990);
		GPc->SetEndStr(tmptxt);
		GetDlgItemText(IDC_EDITCOMMENT,tmptxt,990);
		GPc->SetComment(tmptxt);

		GPc->SetLockEventsEcho(IsDlgButtonChecked(IDC_CHECKLOCKECHO));
		GPc->SetTelnetFlag(IsDlgButtonChecked(IDC_CHECKTELNET)?1:0);

		{
			int sel=m_ComboType.GetCurSel();
			if (sel!=CB_ERR)
			{
				int newtype=m_ComboType.GetItemData(sel);
				if (newtype!=CB_ERR)
				{
					if (m_Comm.GPSectionName==GPc->GPSectionName)
						m_TermCap.SetCurrentTerminalId(newtype);
					AfxGetApp()->WriteProfileInt(GPc->GPSectionName, "TerminalType",newtype);
				}
			}
		}

		GPc->write_dcb();

		int tmpInt=GetDlgItemInt(IDC_EDITROWS);
		if (tmpInt>1 && tmpInt<512)
			AfxGetApp()->WriteProfileInt(GPc->GPSectionName, "INITROWS",tmpInt);
		tmpInt=GetDlgItemInt(IDC_EDITCOLUMNS);
		if (tmpInt>1 && tmpInt<1024)
			AfxGetApp()->WriteProfileInt(GPc->GPSectionName, "INITCOLUMNS",tmpInt);

		DWORD dwSHUTDOWN=0;

		if (IsDlgButtonChecked(IDC_CHECKLOCKEND	)) dwSHUTDOWN|=0x1000;
		if (IsDlgButtonChecked(IDC_CHECKLOCKEND2)) dwSHUTDOWN|=0x0001;
			
		tmpInt=m_ComboShutDown.GetCurSel();
		dwSHUTDOWN|=((tmpInt%4)*0x10+(tmpInt/4)*0x100);

		AfxGetApp()->WriteProfileInt(GPc->GPSectionName, "m_ShutdownFlags",dwSHUTDOWN);


		if (m_Comm.GPSectionName==GPc->GPSectionName) 
		{
			m_Comm.GPClose();
			m_Comm.load_dcb(TRUE);
			m_Comm.GPConnect();
		}
		CDialog::OnOK();
	}
}



DWORD CComPortSetings::GetdwTTYItem(int idControl, char **szString, DWORD *pTable, int iNumItems)
{
/*-----------------------------------------------------------------------------
FUNCTION: GetdwTTYItem(int, char **, DWORD *, int)
PURPOSE: Returns a DWORD item from a dialog control
PARAMETERS:
    idControl - id of control to get data from
    szString  - table of strings that the control displays
    pTable    - table of data associated with strings
    iNumItems - size of table
RETURN:
    DWORD item corresponding to control selection
    0 if item not found correctly
HISTORY:   Date:      Author:     Comment:
	   02/04/99   GVP      apd
-----------------------------------------------------------------------------*/
    int i;
    char szItem[200];

    // Get current selection (a string)
    GetDlgItemText(idControl, szItem, sizeof(szItem));


	//Compare current selection with table to find index of item.
	//If index is found, then return the DWORD item from table.
    for(i = 0; i < iNumItems; i++)
		if (strcmp(szString[i], szItem) == 0)   return pTable[i];

    return 0;

}


BYTE CComPortSetings::GetbTTYItem(int idControl, char **szString, DWORD *pTable, int iNumItems)
{
/*-----------------------------------------------------------------------------
FUNCTION: GetbTTYItem(HWND, int, char **, DWORD *, int)
PURPOSE: Returns a BYTE item from a dialog control
PARAMETERS:
    idControl - id of control to get data from
    szString  - table of strings that the control displays
    pTable    - table of data associated with strings
    iNumItems - size of table
RETURN:
    BYTE item from corresponding to control selection
    0 if item data not found
HISTORY:   Date:      Author:     Comment:
	   02/04/99   GVP      apd
-----------------------------------------------------------------------------*/
    int i;
    char szItem[200];

	// Get current selection (a string)
    GetDlgItemText(idControl, szItem, sizeof(szItem));

	//Compare current selection with table to find index of item.
	//If index is found, then return the BYTE item from table.
    for(i = 0; i < iNumItems; i++)
		if (strcmp(szString[i], szItem) == 0) return (BYTE) pTable[i];

	return 0;
}

void CComPortSetings::OnSelchangeCombotermtype() 
{
	DWORD sel=::SendMessage(::GetDlgItem(m_hWnd,IDC_COMBOTERMTYPE),CB_GETCURSEL,0,0);
	if (sel!=CB_ERR)
		GPc->m_TerminalID=::SendMessage(::GetDlgItem(m_hWnd,IDC_COMBOTERMTYPE),CB_GETITEMDATA,sel,0);
}

#include "DlgDelimiters.h"

void CComPortSetings::OnButtondelimiters() 
{
	CDlgDelimiters dlg(GPc);
	dlg.DoModal();
}

void CComPortSetings::OnChangeEditname() 
{
	CString tmpName;
	m_EditName.GetWindowText(tmpName);
	if (tmpName.Replace(" ","")
		|| tmpName.Replace("/","")
		|| tmpName.Replace("\x10","")
		|| tmpName.Replace("\x13","")
		|| tmpName.Replace("\\","")	) 
	{
		int iStart=0,iEnd=0;
		m_EditName.GetSel(iStart,iEnd);
		m_EditName.SetWindowText(tmpName);
		if (iStart>0) iStart--;
		m_EditName.SetSel(iStart,iStart);
	}
}
