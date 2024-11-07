// GPDlgViewSpr.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPDlgViewSpr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPDlgViewSpr dialog


GPDlgViewSpr::GPDlgViewSpr(CWnd* pParent /*=NULL*/)
	: CDialog(GPDlgViewSpr::IDD, pParent)
{
	//{{AFX_DATA_INIT(GPDlgViewSpr)
	//}}AFX_DATA_INIT
}


void GPDlgViewSpr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GPDlgViewSpr)
	DDX_Control(pDX, IDC_GROUP, m_BtGroup);
	DDX_Control(pDX, IDC_LISTFILTERS, m_ListFilters);
	DDX_Control(pDX, IDC_BTNEXECUTE, m_BtExecute);
	DDX_Control(pDX, IDC_COMBOMETHODS, m_ComboMethods);
	DDX_Control(pDX, IDC_EDITPARAMS, m_EditParams);
	DDX_Control(pDX, IDC_EDITRESULT, m_EditResult);
	DDX_Control(pDX, IDC_STATICPARAMS, m_StatParams);
	DDX_Control(pDX, IDC_STATIC3, m_Stat3);
	DDX_Control(pDX, IDC_STATIC2, m_Stat2);
	DDX_Control(pDX, IDC_STATIC1, m_Stat1);
	DDX_Control(pDX, IDC_LIST1, m_SprListView);
	DDX_Control(pDX, IDC_COMBO1, m_ComboSpr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GPDlgViewSpr, CDialog)
	//{{AFX_MSG_MAP(GPDlgViewSpr)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTNEXECUTE, OnBtnexecute)
	ON_CBN_SELCHANGE(IDC_COMBOMETHODS, OnSelchangeCombomethods)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTNADD, OnBtnadd)
	ON_BN_CLICKED(IDC_BTNDELETE, OnBtndelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPDlgViewSpr message handlers

void GPDlgViewSpr::OnSelchangeCombo1() 
{
	m_SprListView.DeleteAllItems();
	CString sprname;
	m_ComboSpr.GetWindowText(sprname);
	CGPSpr *spr;
	
	if (sprname=="SCRIPTS") spr=&GPC.SprVariables;
	else					spr=GPC.m_SprArray.GetSpr(sprname);

	int nCol=m_SprListView.GetHeaderCtrl()->GetItemCount();
	while(nCol>=0)
		m_SprListView.DeleteColumn(nCol--);
	
	if (spr!=NULL)
	{
		nCol=spr->GetNField();
		m_ListFilters.InsertColumn(0,sprname,LVCFMT_LEFT,100,0);
		int i;
		for(i=0;i<nCol;i++)
		{
			sprname.Format("F%d",i);
			m_SprListView.InsertColumn(i,sprname,LVCFMT_LEFT,100,i);
			m_ListFilters.InsertColumn(i+1,sprname,LVCFMT_LEFT,100,i);
		}
	}
	ReFillData();
}

void GPDlgViewSpr::OnCancel() 
{
	CDialog::OnCancel();
}

BOOL GPDlgViewSpr::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetTimer(1,2000,NULL);

	UINT i;
	for(i=0;i<CGPSpr::uNMethods;i++)
		m_ComboMethods.AddString(CGPSpr::cArrMethods[i]);

	m_ComboMethods.SetCurSel(0);
	OnSelchangeCombomethods();

	FillSprList("");
	
	m_SprListView.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_ListFilters.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);

	AUSI.AddSetMain(this->m_hWnd);
	AUSI.AddWnd(m_SprListView.m_hWnd,this->m_hWnd	,"NNEE");
	AUSI.AddWnd(m_BtExecute.m_hWnd,this->m_hWnd		,"EEEE");
	AUSI.AddWnd(m_ComboMethods.m_hWnd,this->m_hWnd	,"ENEE");
	AUSI.AddWnd(m_EditParams.m_hWnd,this->m_hWnd	,"ENEE");
	AUSI.AddWnd(m_EditResult.m_hWnd,this->m_hWnd	,"ENEE");
	AUSI.AddWnd(m_Stat1.m_hWnd,this->m_hWnd			,"ENEN");
	AUSI.AddWnd(m_Stat2.m_hWnd,this->m_hWnd			,"ENEN");
	AUSI.AddWnd(m_Stat3.m_hWnd,this->m_hWnd			,"ENEN");
	AUSI.AddWnd(m_StatParams.m_hWnd,this->m_hWnd	,"ENEE");
	AUSI.AddWnd(m_BtGroup.m_hWnd,this->m_hWnd		,"ENEE");
	AUSI.AddWnd(m_ListFilters.m_hWnd,this->m_hWnd	,"ENEE");
	AUSI.SetMinSize(this->m_hWnd,570,150);

	GPC.SetIconFromIL(m_hWnd, "OFFICES", 10);

	return TRUE;  
}

void GPDlgViewSpr::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	AUSI.UpdateSize();	
}

void GPDlgViewSpr::OnSelchangeCombomethods() 
{
	CString str;
	m_ComboMethods.GetWindowText(str);
	UINT i;
	for(i=0;i<CGPSpr::uNMethods;i++)
		if (str==CGPSpr::cArrMethods[i]) break;
	m_StatParams.SetWindowText(CGPSpr::cArrMethodsParams[i]);
}

void GPDlgViewSpr::OnBtnexecute() 
{
	m_EditResult.SetWindowText("");
	CString str;
	CString strMeth;
	CString strParam;
	m_ComboMethods.GetWindowText(strMeth);
	m_EditParams.GetWindowText(strParam);
	str=strMeth+" "+strParam;

	m_ComboSpr.GetWindowText(strParam);
	CGPSpr *spr;
	if (strParam=="SCRIPTS") spr=&GPC.SprVariables;
	else					spr=GPC.m_SprArray.GetSpr(strParam);

	if (spr!=NULL)
	{
		char *oStr=NULL;
		spr->DoMethod(str,&oStr);
		if (oStr!=NULL) 
		{
			m_EditResult.SetWindowText(oStr);
			delete[] oStr;
		}
	}
	if (strMeth.Find("Get",0)<0) ReFillData();
}


void GPDlgViewSpr::ReFillData()
{
	m_SprListView.DeleteAllItems();
	m_ListFilters.DeleteAllItems();
	CString strParam;
	m_ComboSpr.GetWindowText(strParam);
	CGPSpr *spr;
	if (strParam=="SCRIPTS") spr=&GPC.SprVariables;
	else					spr=GPC.m_SprArray.GetSpr(strParam);
	if (spr!=NULL)
	{
		spr->FillObject(m_SprListView.m_hWnd,3,"0^1^2^3^4^5^6^7^8^9^10^11^12^13^14^15^16^17^18^19^20^21^22^23^24^25^26^27^28^29^30^31^32^33^34^35^36^37^38^39,0^1^2^3^4^5^6^7^8^9^10^11^12^13^14^15^16^17^18^19^20^21^22^23^24^25^26^27^28^29^30^31^32^33^34^35^36^37^38^39",0);
		UINT nFld=spr->GetNField();
		UINT i;
		int nItem;

		nItem=m_ListFilters.InsertItem(0,"Filter");
		for(i=0;i<nFld;i++)
			m_ListFilters.SetItemText(nItem,i+1,spr->GetFilter(i));

		nItem=m_ListFilters.InsertItem(2,"SortFilter");
		for(i=0;i<nFld;i++)
			m_ListFilters.SetItemText(nItem,i+1,spr->GetSort(i));
		
	}
}

void GPDlgViewSpr::OnTimer(UINT nIDEvent) 
{
	ModifyStyle(WS_DISABLED,0);
	CDialog::OnTimer(nIDEvent);
}

#include "DlgNewSpr.h"

void GPDlgViewSpr::OnBtnadd() 
{
	CDlgNewSpr dlg;
	if (dlg.DoModal()==IDOK && dlg.m_SprName!="")
	{
		CGPSpr *pSpr=GPC.m_SprArray.CreateSpr(dlg.m_SprName);
		if (pSpr!=NULL) pSpr->Create(dlg.m_SprName,dlg.m_nFields);
		FillSprList(dlg.m_SprName);
	}
}

void GPDlgViewSpr::OnBtndelete() 
{
	CString strspr;
	m_ComboSpr.GetWindowText(strspr);
	if (strspr!="" && strspr!="SCRIPTS")
	{
#ifdef RUS
		CString str="Удалить справочник \""+strspr+"\"";
		if (MessageBox(str,"Удаление справочника",MB_YESNO|MB_APPLMODAL|MB_ICONEXCLAMATION|MB_DEFBUTTON2)==IDYES) 
#else
		CString str="Delete dictionary \""+strspr+"\"";
		if (MessageBox(str,"Delete dictionary",MB_YESNO|MB_APPLMODAL|MB_ICONEXCLAMATION|MB_DEFBUTTON2)==IDYES) 
#endif
		{
			GPC.m_SprArray.DeleteSpr(strspr);
			m_ComboSpr.DeleteString(m_ComboSpr.GetCurSel());
			OnSelchangeCombo1();
			OnSelchangeCombomethods();
		}
	}
}

void GPDlgViewSpr::FillSprList(const char *SelName)
{
	UINT nSpr=GPC.m_SprArray.GetCount();
	m_ComboSpr.ResetContent();
	UINT i;
	for(i=0;i<0x1000 && i<nSpr;i++)
		m_ComboSpr.AddString(GPC.m_SprArray.GetSprName(i));


	m_ComboSpr.AddString("SCRIPTS");

	if (nSpr && *SelName!=0)
	{
		UINT nLine=m_ComboSpr.FindStringExact(0,SelName);
		if (nLine!=CB_ERR)
		{
			m_ComboSpr.SetCurSel(nLine);
			OnSelchangeCombo1();
		}
	}

}

BOOL GPDlgViewSpr::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (wParam!=1 || lParam!=0) return CDialog::OnCommand(wParam, lParam);

	if (wParam==1) OnBtnexecute();
	
	return FALSE;
}
