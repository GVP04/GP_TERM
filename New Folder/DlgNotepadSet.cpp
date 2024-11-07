// DlgNotepadSet.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgNotepadSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNotepadSet dialog

const UINT CDlgNotepadSet::uNEntryes=27;
const char *CDlgNotepadSet::cArrEntryName[]={
		"lfEscapement",	"lfOrientation",	"lfWeight",	"lfItalic",	"lfUnderline",
		"lfStrikeOut",	"lfCharSet",	"lfOutPrecision",	"lfClipPrecision",	"lfQuality",
		"lfPitchAndFamily",	"iPointSize",	"fWrap",	"StatusBar",	"fSaveWindowPositions",
		"lfFaceName",	"szHeader",	"szTrailer",	"iMarginTop",	"iMarginBottom",
		"iMarginLeft",	"iMarginRight",	"fMLE_is_broken",	"iWindowPosX",	"iWindowPosY",
		"iWindowPosDX",	"iWindowPosDY", 
		"",
	};

const DWORD CDlgNotepadSet::uArrIDS[]={
	IDC_EDIT11,IDC_EDIT8,IDC_EDIT9,0,0,
	0,IDC_EDIT7,IDC_EDIT12,IDC_EDIT13,IDC_EDIT14,
	IDC_EDIT15,IDC_EDIT10,IDC_CHECK1,IDC_CHECK2,0,
	IDC_EDIT4,IDC_EDIT1,IDC_EDIT2,IDC_EDIT18,IDC_EDIT19,
	IDC_EDIT20,IDC_EDIT21,IDC_CHECK3,IDC_EDIT22,IDC_EDIT23,
	IDC_EDIT24,IDC_EDIT25, 
	0,
	};

const DWORD CDlgNotepadSet::uArrEntryType[]={
	REG_DWORD,REG_DWORD,REG_DWORD,REG_DWORD,REG_DWORD,
	REG_DWORD,REG_DWORD,REG_DWORD,REG_DWORD,REG_DWORD,
	REG_DWORD,REG_DWORD,REG_DWORD,REG_DWORD,REG_DWORD,
	REG_SZ,REG_SZ,REG_SZ,REG_DWORD,REG_DWORD,
	REG_DWORD,REG_DWORD,REG_DWORD,REG_DWORD,REG_DWORD,
	REG_DWORD,REG_DWORD,
	REG_DWORD,
	};

//HKEY_CURRENT_USER,Software\Microsoft\Notepad,KEY_ALL_ACCESS



CDlgNotepadSet::CDlgNotepadSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNotepadSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNotepadSet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_csSectionName="NotepadDumpSet";
}


void CDlgNotepadSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNotepadSet)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNotepadSet, CDialog)
	//{{AFX_MSG_MAP(CDlgNotepadSet)
	ON_BN_CLICKED(IDC_BTNUPDATE, OnBtnupdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNotepadSet message handlers

BOOL CDlgNotepadSet::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString csSet="";
	CDlgNotepadSet::GetNotepadTypeSettings(m_csSectionName,csSet);
	if (csSet=="")	CDlgNotepadSet::GetNotepadSettings(csSet);

	int i;
	for(i=0;i<27;i++)
		if (CDlgNotepadSet::uArrIDS[i])
			switch(CDlgNotepadSet::uArrIDS[i])
			{
			case IDC_CHECK1:
			case IDC_CHECK2:
			case IDC_CHECK3:
				CheckDlgButton(CDlgNotepadSet::uArrIDS[i],atoi(ExtractField(csSet,i+1,"\x7F")));
				break;
			default:
				SetDlgItemText(CDlgNotepadSet::uArrIDS[i],ExtractField(csSet,i+1,"\x7F"));
				break;
			}

	return TRUE;
}

void CDlgNotepadSet::OnOK()
{
	HWND fHWND=::GetFocus();
	if (fHWND)
	{
		fHWND=::GetNextDlgTabItem(m_hWnd,fHWND,FALSE);
		if (fHWND) ::SetFocus(fHWND);
	}
}

void CDlgNotepadSet::OnCancel()
{
	CDialog::OnCancel();
}

void CDlgNotepadSet::OnBtnupdate()
{
	CString result="";
	CString field;
	int i;
	for(i=0;i<27;i++)
	{
		switch(CDlgNotepadSet::uArrIDS[i])
		{
		case 0:
			field="0";
			break;
		case IDC_CHECK1:
		case IDC_CHECK2:
		case IDC_CHECK3:
			field.Format("%d",IsDlgButtonChecked(uArrIDS[i]));
			break;
		default:
			GetDlgItemText(CDlgNotepadSet::uArrIDS[i],field);
			break;
		}
		if (i) result+="\x7F";
		result+=field;
	}

	CDlgNotepadSet::SetNotepadTypeSettings(m_csSectionName,result);

	CDialog::OnOK();
}

void CDlgNotepadSet::GetNotepadSettings(CString &csResult)
{
//HKEY_CURRENT_USER,Software\Microsoft\Notepad,KEY_ALL_ACCESS
	csResult="";
	HKEY m_HKEY=NULL;
	if (::RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\Microsoft\\Notepad",0,KEY_READ,&m_HKEY)==ERROR_SUCCESS || m_HKEY)
	{
		BYTE byteData[500];
		DWORD cbData;
		DWORD Type;
		CString field;
		int i;
		for(i=0;i<27;i++)
		{
			field="";
			cbData=450;

			if (CDlgNotepadSet::uArrIDS[i] && RegQueryValueEx(m_HKEY,CDlgNotepadSet::cArrEntryName[i],NULL,&Type,byteData,&cbData)==ERROR_SUCCESS)
			{
				byteData[cbData]=0;
				if (Type==REG_SZ) field=byteData;
				else field.Format("%d",*((DWORD *)byteData));
			}
			else field="0";

			if (i) csResult+="\x7F";
			csResult+=field;
		}
		::RegCloseKey(m_HKEY);
	}
}

void CDlgNotepadSet::SetNotepadSettings(CString &csNewSet)
{
	HKEY m_HKEY=NULL;
	if (::RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\Microsoft\\Notepad",0,KEY_WRITE,&m_HKEY)==ERROR_SUCCESS || m_HKEY)
	{
		int i;
		for(i=0;i<27;i++)
			if (CDlgNotepadSet::uArrIDS[i])
			{
				BYTE byteData[500];
				DWORD cbData;
				CString field=ExtractField(csNewSet,i+1,"\x7F");
				if (CDlgNotepadSet::uArrEntryType[i]==REG_SZ)
				{
					strncpy((char *)byteData,field,450);
					byteData[450]=0;
					cbData=(int)strlen((char *)byteData);
					RegSetValueEx(m_HKEY,CDlgNotepadSet::cArrEntryName[i],0,REG_SZ,byteData,cbData);
				}
				else
				{
					*((DWORD *)byteData)=atoi(field);
					cbData=4;
					RegSetValueEx(m_HKEY,CDlgNotepadSet::cArrEntryName[i],0,REG_DWORD,byteData,cbData);
				}
			}

		::RegCloseKey(m_HKEY);
	}
}

void CDlgNotepadSet::GetNotepadTypeSettings(const char * iSection, CString &csResult)
{
	csResult=AfxGetApp()->GetProfileString(GPC.cs_RegTermViewSetName,iSection,"");
}

void CDlgNotepadSet::SetNotepadTypeSettings(const char * iSection, CString &csNewSet)
{
	AfxGetApp()->WriteProfileString(GPC.cs_RegTermViewSetName,iSection,csNewSet);
}
