// DlgViewRegMethods.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgViewRegMethods.h"
#include "GP_TermDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgViewRegMethods dialog


CDlgViewRegMethods::CDlgViewRegMethods(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewRegMethods::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgViewRegMethods)
	//}}AFX_DATA_INIT
}

void CDlgViewRegMethods::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgViewRegMethods)
	DDX_Control(pDX, IDC_BUTTONMORE, m_BtnMore);
	DDX_Control(pDX, IDC_STATICPARAMS, m_StatParams);
	DDX_Control(pDX, IDC_EDITRESULT, m_EditResult);
	DDX_Control(pDX, IDC_EDITPARAMS, m_EditParams);
	DDX_Control(pDX, IDC_BTNEXECUTE, m_btnExecute);
	DDX_Control(pDX, IDC_COMBOMETHODS, m_ComboMethods);
	DDX_Control(pDX, IDC_COMBOIOFILES, m_ComboVars);
	DDX_Control(pDX, IDC_BTNADD, m_BtnAddVar);
	DDX_Control(pDX, IDC_BTNDELETE, m_btnDelete);
	//}}AFX_DATA_MAP
}



BEGIN_MESSAGE_MAP(CDlgViewRegMethods, CDialog)
	//{{AFX_MSG_MAP(CDlgViewRegMethods)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTNEXECUTE, OnBtnexecute)
	ON_CBN_SELCHANGE(IDC_COMBOMETHODS, OnSelchangeCombomethods)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTONMORE, OnButtonmore)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTNDELETE, OnBtndelete)
	ON_BN_CLICKED(IDC_BTNADD, OnBtnadd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgViewRegMethods message handlers

BOOL CDlgViewRegMethods::OnInitDialog()
{
	CDialog::OnInitDialog();
	FillIVarsList();

	m_ComboMethods.ResetContent();
	UINT i;
	for(i=0;i<GPCurrent::uNRegistryMethods;i++)
		m_ComboMethods.AddString(GPCurrent::cArrRegistryMethods[i]);


	m_ComboMethods.SetCurSel(0);
	OnSelchangeCombomethods();

	AUSI.AddSetMain(this->m_hWnd);
	AUSI.AddWnd(m_btnExecute.m_hWnd,this->m_hWnd	,"NENE");
	AUSI.AddWnd(m_BtnMore.m_hWnd,this->m_hWnd		,"NENE");

	AUSI.AddWnd(m_ComboMethods.m_hWnd,this->m_hWnd	,"NNNE");
	AUSI.AddWnd(m_EditParams.m_hWnd,this->m_hWnd	,"NNNE");
	AUSI.AddWnd(m_StatParams.m_hWnd,this->m_hWnd	,"NNNE");
	AUSI.AddWnd(m_EditResult.m_hWnd,this->m_hWnd	,"NNPE");
	AUSI.AddWnd(m_btnDelete.m_hWnd,this->m_hWnd		,"NENE");
	AUSI.AddWnd(m_BtnAddVar.m_hWnd,this->m_hWnd	,"NENE");
	AUSI.AddWnd(m_ComboVars.m_hWnd,this->m_hWnd	,"NNNE");

	AUSI.SetMinSize(this->m_hWnd,500,150);

	GPC.m_Document->GPCOPYHWND=this->m_hWnd;
	SetTimer(1,2000,NULL);

	return TRUE;
}

void CDlgViewRegMethods::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	AUSI.UpdateSize();
}

void CDlgViewRegMethods::OnBtnexecute()
{
	m_EditResult.SetWindowText("");
	CString str;
	CString strVar;
	CString strMeth;
	CString strParam;
	m_ComboVars.GetWindowText(strVar);
	m_ComboMethods.GetWindowText(strMeth);
	m_EditParams.GetWindowText(strParam);
	str=strVar+";"+strMeth+" "+strParam;

	char *oStr=NULL;
	GPC.DoRegistryMethod((char *)((const char *)str),&oStr);
	if (oStr)
	{
		m_csLastResult=oStr;
		m_EditResult.SetWindowText(oStr);
		delete[] oStr;
	}
}

void CDlgViewRegMethods::OnSelchangeCombomethods()
{
	CString str;
	m_ComboMethods.GetWindowText(str);
	UINT i;
	for(i=0;i<GPCurrent::uNRegistryMethods;i++)
		if (str==GPCurrent::cArrRegistryMethods[i]) break;
	m_StatParams.SetWindowText(GPCurrent::cArrRegistryMethodsParams[i]);
}

void CDlgViewRegMethods::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);
	switch(nIDEvent)
	{
	case 1:
		ModifyStyle(WS_DISABLED,0);
		break;
	}

}

#include "DlgViewItem.h"

void CDlgViewRegMethods::OnButtonmore()
{
	CDlgViewItem dlg(m_csLastResult,127,7,this);
	dlg.DoModal();
}


void CDlgViewRegMethods::OnDestroy()
{
	GPC.m_Document->GPCOPYHWND=NULL;
	CDialog::OnDestroy();
}

BOOL CDlgViewRegMethods::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (wParam!=1 || lParam!=0) return CDialog::OnCommand(wParam, lParam);

	if (wParam==1) OnBtnexecute();

	return FALSE;
}

#include "GPDlgNewValue.h"

void CDlgViewRegMethods::OnBtnadd()
{
	GPDlgNewValue dlg("");
	if (dlg.DoModal()==IDOK && dlg.m_NewValue!="")
	{
		GPC.m_HandlerArray.DeleteHandle(dlg.m_NewValue);
		GPC.m_HandlerArray.CreateHandle(dlg.m_NewValue);
		FillIVarsList();
		UINT Id=m_ComboVars.FindStringExact(0,dlg.m_NewValue);
		if (Id!=CB_ERR)	m_ComboVars.SetCurSel(Id);
	}
}
void CDlgViewRegMethods::FillIVarsList()
{
	UINT nHandlers=GPC.m_HandlerArray.GetCount();
	m_ComboVars.ResetContent();

	UINT i;
	for(i=0;i<nHandlers;i++)
	{
		CString nm=GPC.m_HandlerArray.EnumHandlers(i);
		if ((GPC.m_HandlerArray[nm].uType&(HANDLER_TYPE_HKEY|HANDLER_TYPE_HKEY_PREDEF)) || GPC.m_HandlerArray[nm].uType==HANDLER_TYPE_VOID)
				m_ComboVars.AddString(nm);
	}
}

void CDlgViewRegMethods::OnBtndelete()
{
	UINT id=m_ComboVars.GetCurSel();
	if (id!=CB_ERR)
	{
		CString RegVarName;
		m_ComboVars.GetWindowText(RegVarName);
		HKEY tmpHKEY=NULL;
		if (RegVarName!="" && GPC.StringFromToHKEY(RegVarName,tmpHKEY)==NULL)
		{
			GPC.m_HandlerArray.DeleteHandle(RegVarName);
			m_ComboVars.DeleteString(id);
			m_ComboVars.Invalidate();
		}
	}
}

