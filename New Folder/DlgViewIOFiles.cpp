// DlgViewIOFiles.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgViewIOFiles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgViewIOFiles dialog


CDlgViewIOFiles::CDlgViewIOFiles(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewIOFiles::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgViewIOFiles)
	//}}AFX_DATA_INIT
}


void CDlgViewIOFiles::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgViewIOFiles)
	DDX_Control(pDX, IDC_BUTTONMORE, m_BtnMore);
	DDX_Control(pDX, IDC_BTNDELETETEXT, m_BtnClearEvents);
	DDX_Control(pDX, IDC_BTNADD, m_BtnAddIOFile);
	DDX_Control(pDX, IDC_STATIC5, m_StaticEvents);
	DDX_Control(pDX, IDC_EDITEVENTS, m_EditEvents);
	DDX_Control(pDX, IDC_STATICPARAMS, m_StatParams);
	DDX_Control(pDX, IDC_EDITRESULT, m_EditResult);
	DDX_Control(pDX, IDC_EDITPARAMS, m_EditParams);
	DDX_Control(pDX, IDC_BTNEXECUTE, m_btnExecute);
	DDX_Control(pDX, IDC_BTNDELETE, m_btnDelete);
	DDX_Control(pDX, IDC_COMBOMETHODS, m_ComboMethods);
	DDX_Control(pDX, IDC_COMBOIOFILES, m_ComboIOFiles);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgViewIOFiles, CDialog)
	//{{AFX_MSG_MAP(CDlgViewIOFiles)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBOIOFILES, OnSelchangeComboiofiles)
	ON_BN_CLICKED(IDC_BTNDELETE, OnBtndelete)
	ON_BN_CLICKED(IDC_BTNADD, OnBtnadd)
	ON_BN_CLICKED(IDC_BTNEXECUTE, OnBtnexecute)
	ON_CBN_SELCHANGE(IDC_COMBOMETHODS, OnSelchangeCombomethods)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTNDELETETEXT, OnBtndeletetext)
	ON_BN_CLICKED(IDC_BUTTONMORE, OnButtonmore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgViewIOFiles message handlers

BOOL CDlgViewIOFiles::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetTimer(1,2000,NULL);

	FillIOFileList();

	UINT i;
	for(i=0;i<GPIOFile::uNMethods;i++)
		m_ComboMethods.AddString(GPIOFile::cArrMethods[i]);

	m_ComboIOFiles.SetCurSel(0);
	OnSelchangeComboiofiles();

	m_ComboMethods.SetCurSel(0);
	OnSelchangeCombomethods();
	m_EditParams.SetWindowText("COM2,GENERIC_READ|GENERIC_WRITE");

	AUSI.AddSetMain(this->m_hWnd);
	AUSI.AddWnd(m_btnExecute.m_hWnd,this->m_hWnd	,"NENE");
	AUSI.AddWnd(m_btnDelete.m_hWnd,this->m_hWnd		,"NENE");
	AUSI.AddWnd(m_BtnAddIOFile.m_hWnd,this->m_hWnd	,"NENE");
	AUSI.AddWnd(m_BtnMore.m_hWnd,this->m_hWnd		,"NENE");

	AUSI.AddWnd(m_ComboIOFiles.m_hWnd,this->m_hWnd	,"NNNE");
	AUSI.AddWnd(m_ComboMethods.m_hWnd,this->m_hWnd	,"NNNE");
	AUSI.AddWnd(m_EditParams.m_hWnd,this->m_hWnd	,"NNNE");
	AUSI.AddWnd(m_StatParams.m_hWnd,this->m_hWnd	,"NNNE");
	AUSI.AddWnd(m_EditResult.m_hWnd,this->m_hWnd	,"NNPE");
	AUSI.AddWnd(::GetDlgItem(this->m_hWnd,IDC_STATIC5),this->m_hWnd	,"PNPN");
	AUSI.AddWnd(m_EditEvents.m_hWnd,this->m_hWnd	,"PNEE");

	AUSI.AddWnd(m_BtnClearEvents.m_hWnd,this->m_hWnd,"EEEE");

	AUSI.SetMinSize(this->m_hWnd,500,150);


	return TRUE;
}

void CDlgViewIOFiles::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	AUSI.UpdateSize();
}

void CDlgViewIOFiles::OnSelchangeComboiofiles()
{
	CString IOFilesname;
	m_ComboIOFiles.GetWindowText(IOFilesname);

	GPC.m_IOFileArray.ClearEventEditiors();
	GPC.m_IOFileArray.SetEventEditor(IOFilesname,m_hWnd);
}

void CDlgViewIOFiles::OnBtndelete()
{
	UINT id=m_ComboIOFiles.GetCurSel();
	if (id!=CB_ERR)
	{
		CString IOFilesname;
		m_ComboIOFiles.GetWindowText(IOFilesname);
		if (IOFilesname!="")
			GPC.m_IOFileArray.DeleteIOFile(IOFilesname);
		m_ComboIOFiles.DeleteString(id);
		m_ComboIOFiles.Invalidate();
	}
}


#include "GPDlgNewValue.h"

void CDlgViewIOFiles::OnBtnadd()
{
	GPDlgNewValue dlg("AddIOFileDlg");
	if (dlg.DoModal()==IDOK && dlg.m_NewValue!="")
	{
		GPC.m_IOFileArray.DeleteIOFile(dlg.m_NewValue);
		GPC.m_IOFileArray.CreateIOFile(dlg.m_NewValue);
		FillIOFileList();
		UINT Id=m_ComboIOFiles.FindStringExact(0,dlg.m_NewValue);
		if (Id!=CB_ERR)	m_ComboIOFiles.SetCurSel(Id);
	}
}

void CDlgViewIOFiles::OnBtnexecute()
{
	m_EditResult.SetWindowText("");
	CString str;
	CString strMeth;
	CString strParam;
	m_ComboMethods.GetWindowText(strMeth);
	m_EditParams.GetWindowText(strParam);
	str=strMeth+" "+strParam;

	m_ComboIOFiles.GetWindowText(strParam);
	GPIOFile *IOFile=GPC.m_IOFileArray.GetIOFile(strParam);
	if (IOFile)
	{
		char *oStr=NULL;
		IOFile->DoMethod(str,&oStr);
		if (oStr)
		{
			m_csLastResult=oStr;
			m_EditResult.SetWindowText(oStr);
			delete[] oStr;
		}
	}
}

void CDlgViewIOFiles::OnSelchangeCombomethods()
{
	CString str;
	m_ComboMethods.GetWindowText(str);
	UINT i;
	for(i=0;i<GPIOFile::uNMethods;i++)
		if (str==GPIOFile::cArrMethods[i]) break;
	m_StatParams.SetWindowText(GPIOFile::cArrMethodsParams[i]);
}

void CDlgViewIOFiles::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);
	ModifyStyle(WS_DISABLED,0);
}

void CDlgViewIOFiles::FillIOFileList()
{
	m_ComboIOFiles.ResetContent();
	UINT nFiles=GPC.m_IOFileArray.GetCount();
	UINT i;
	for(i=0;i<nFiles;i++)
		m_ComboIOFiles.AddString(GPC.m_IOFileArray.GetIOFileName(i));
}

void CDlgViewIOFiles::OnBtndeletetext()
{
	m_EditEvents.SetSel(0,-1);
	m_EditEvents.ReplaceSel("");
}

LRESULT CDlgViewIOFiles::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{

	switch(message)
	{
	case GPM_SETANDDELETESTRING:
		if (lParam)
		{
			m_EditEvents.SetSel(-1,-1);
			m_EditEvents.ReplaceSel((char *)lParam);
			if (wParam!=0)
				delete[] (char *)lParam;
		}
	}

	return CDialog::WindowProc(message, wParam, lParam);
}

#include "DlgViewItem.h"

void CDlgViewIOFiles::OnButtonmore()
{
	CDlgViewItem dlg(m_csLastResult,127,7,this);
	dlg.DoModal();
}

BOOL CDlgViewIOFiles::DestroyWindow()
{
	GPC.m_IOFileArray.ClearEventEditiors();
	return CDialog::DestroyWindow();
}

BOOL CDlgViewIOFiles::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (wParam!=1 || lParam!=0) return CDialog::OnCommand(wParam, lParam);

	if (wParam==1) OnBtnexecute();

	return FALSE;
}
