// GPDlgViewMPVar.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPDlgViewMPVar.h"
#include "GP_TermDoc.h"
#include "GP_TermView.h"
#include "GPDlgNewValue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPDlgViewMPVar dialog


GPDlgViewMPVar::GPDlgViewMPVar(CWnd* pParent /*=NULL*/)
	: CDialog(GPDlgViewMPVar::IDD, pParent)
{
	//{{AFX_DATA_INIT(GPDlgViewMPVar)
	//}}AFX_DATA_INIT
}


void GPDlgViewMPVar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GPDlgViewMPVar)
	DDX_Control(pDX, IDC_LISTOBJNAME, m_ListObjName);
	DDX_Control(pDX, IDC_LISTNAMEDDATA, m_ListNamedData);
	DDX_Control(pDX, IDC_LIST15, m_ListInput);
	DDX_Control(pDX, IDC_LIST14, m_ListScrData);
	DDX_Control(pDX, IDC_LIST13, m_ListDlgData);
	DDX_Control(pDX, IDC_LIST12, m_ListScrObjMP);
	DDX_Control(pDX, IDC_LIST11, m_ListDlgObjMP);
	DDX_Control(pDX, IDC_LIST10, m_ListScrObjHot);
	DDX_Control(pDX, IDC_LIST9, m_ListDlgObjHot);
	DDX_Control(pDX, IDC_LIST8, m_ListScrHot);
	DDX_Control(pDX, IDC_LIST7, m_ListDlgHot);
	DDX_Control(pDX, IDC_LIST6, m_ListScrMenu);
	DDX_Control(pDX, IDC_LIST5, m_ListDlgMenu);
	DDX_Control(pDX, IDC_LIST4, m_ListScrMp);
	DDX_Control(pDX, IDC_LIST3, m_ListDlgMp);
	DDX_Control(pDX, IDC_LIST2, m_List2);
	DDX_Control(pDX, IDC_BTNUPDATE, m_btUpdate);
	DDX_Control(pDX, IDC_LIST1, m_List1);
	DDX_Control(pDX, IDC_TABVAR, m_Tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GPDlgViewMPVar, CDialog)
	//{{AFX_MSG_MAP(GPDlgViewMPVar)
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABVAR, OnSelchangeTabvar)
	ON_BN_CLICKED(IDC_BTNUPDATE, OnBtnupdate)
	ON_WM_TIMER()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST13, OnDblclkList13)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST14, OnDblclkList14)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTNAMEDDATA, OnDblclkListnameddata)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnDblclkList2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPDlgViewMPVar message handlers

BOOL GPDlgViewMPVar::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_Tab.ModifyStyle(0,TCS_BUTTONS);
	SetTimer(1,2000,NULL);

	AUSI.AddSetMain(this->m_hWnd);
	AUSI.AddWnd(m_Tab.m_hWnd,this->m_hWnd	,"NNNE");
	AUSI.AddWnd(m_List1.m_hWnd,this->m_hWnd	,"NNEE");
	AUSI.AddWnd(m_List2.m_hWnd,this->m_hWnd	,"NNEE");
	AUSI.AddWnd(m_ListDlgMp.m_hWnd,this->m_hWnd	,"NNEE");
	AUSI.AddWnd(m_ListScrMp.m_hWnd,this->m_hWnd	,"NNEE");
	AUSI.AddWnd(m_ListDlgMenu.m_hWnd,this->m_hWnd	,"NNEE");
	AUSI.AddWnd(m_ListScrMenu.m_hWnd,this->m_hWnd	,"NNEE");
	AUSI.AddWnd(m_ListDlgHot.m_hWnd,this->m_hWnd	,"NNEE");
	AUSI.AddWnd(m_ListScrHot.m_hWnd,this->m_hWnd	,"NNEE");
	AUSI.AddWnd(m_ListDlgObjHot.m_hWnd,this->m_hWnd	,"NNEE");
	AUSI.AddWnd(m_ListScrObjHot.m_hWnd,this->m_hWnd	,"NNEE");
	AUSI.AddWnd(m_ListDlgObjMP.m_hWnd,this->m_hWnd	,"NNEE");
	AUSI.AddWnd(m_ListScrObjMP.m_hWnd,this->m_hWnd	,"NNEE");
	AUSI.AddWnd(m_ListDlgData.m_hWnd,this->m_hWnd	,"NNEE");
	AUSI.AddWnd(m_ListScrData.m_hWnd,this->m_hWnd	,"NNEE");
	AUSI.AddWnd(m_ListObjName.m_hWnd,this->m_hWnd	,"NNEE");
	AUSI.AddWnd(m_ListNamedData.m_hWnd,this->m_hWnd	,"NNEE");
	AUSI.AddWnd(m_ListInput.m_hWnd,this->m_hWnd	,"NNEE");
	AUSI.AddWnd(m_btUpdate.m_hWnd,this->m_hWnd	,"NENE");

	AUSI.SetMinSize(this->m_hWnd,270,150);
	

	m_Tab.InsertItem(0,"Variables");
	m_Tab.InsertItem(1,"Files");
	m_Tab.InsertItem(2,"DlgMP");
	m_Tab.InsertItem(3,"ScrMP");
	m_Tab.InsertItem(4,"DlgMnu");
	m_Tab.InsertItem(5,"ScrMnu");
	m_Tab.InsertItem(6,"DlgHKey");
	m_Tab.InsertItem(7,"ScrHKey");
	m_Tab.InsertItem(8,"DlgObjHK");
	m_Tab.InsertItem(9,"ScrObjHK");
	m_Tab.InsertItem(10,"DlgObjMP");
	m_Tab.InsertItem(11,"ScrObjMP");
	m_Tab.InsertItem(12,"DlgData");
	m_Tab.InsertItem(13,"ScrData");
	m_Tab.InsertItem(14,"Input");
	m_Tab.InsertItem(15,"NmData");
	m_Tab.InsertItem(16,"ObjName");

	m_List1.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_List1.InsertColumn(0,"Variable",LVCFMT_LEFT,100,0);
	m_List1.InsertColumn(1,"Value",LVCFMT_LEFT,200,0);

	m_List2.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_List2.InsertColumn(0,"File ID",LVCFMT_LEFT,40,0);
	m_List2.InsertColumn(1,"File Name",LVCFMT_LEFT,200,0);

	m_ListDlgMp.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_ListDlgMp.InsertColumn(0,"Dlg ID",LVCFMT_LEFT,40,0);
	m_ListDlgMp.InsertColumn(1,"Message",LVCFMT_LEFT,120,0);
	m_ListDlgMp.InsertColumn(2,"Subroutine",LVCFMT_LEFT,150,0);

	m_ListScrMp.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_ListScrMp.InsertColumn(0,"Dlg ID",LVCFMT_LEFT,40,0);
	m_ListScrMp.InsertColumn(1,"Message",LVCFMT_LEFT,120,0);
	m_ListScrMp.InsertColumn(2,"Subroutine",LVCFMT_LEFT,150,0);

	m_ListDlgMenu.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_ListDlgMenu.InsertColumn(0,"DlgID",LVCFMT_LEFT,40,0);
	m_ListDlgMenu.InsertColumn(1,"PopID",LVCFMT_LEFT,40,0);
	m_ListDlgMenu.InsertColumn(2,"MenuID",LVCFMT_LEFT,45,0);
	m_ListDlgMenu.InsertColumn(3,"Pos",LVCFMT_LEFT,35,0);
	m_ListDlgMenu.InsertColumn(4,"MenuItem Name ",LVCFMT_LEFT,200,0);
	m_ListDlgMenu.InsertColumn(5,"Subroutine",LVCFMT_LEFT,150,0);

	m_ListScrMenu.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_ListScrMenu.InsertColumn(0,"PopID",LVCFMT_LEFT,40,0);
	m_ListScrMenu.InsertColumn(1,"MenuID",LVCFMT_LEFT,45,0);
	m_ListScrMenu.InsertColumn(2,"Pos",LVCFMT_LEFT,35,0);
	m_ListScrMenu.InsertColumn(3,"MenuItem Name ",LVCFMT_LEFT,200,0);
	m_ListScrMenu.InsertColumn(4,"Subroutine",LVCFMT_LEFT,150,0);

	m_ListDlgHot.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_ListDlgHot.InsertColumn(0,"DlgID",LVCFMT_LEFT,40,0);
	m_ListDlgHot.InsertColumn(1,"HotID",LVCFMT_LEFT,40,0);
	m_ListDlgHot.InsertColumn(2,"Key Name",LVCFMT_LEFT,100,0);
	m_ListDlgHot.InsertColumn(3,"Modifiers",LVCFMT_LEFT,100,0);
	m_ListDlgHot.InsertColumn(4,"Hot Seq",LVCFMT_LEFT,100,0);
	m_ListDlgHot.InsertColumn(5,"Subroutine",LVCFMT_LEFT,150,0);

	m_ListScrHot.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_ListScrHot.InsertColumn(0,"HotID",LVCFMT_LEFT,40,0);
	m_ListScrHot.InsertColumn(1,"Key Name",LVCFMT_LEFT,100,0);
	m_ListScrHot.InsertColumn(2,"Modifiers",LVCFMT_LEFT,100,0);
	m_ListScrHot.InsertColumn(3,"Hot Seq",LVCFMT_LEFT,100,0);
	m_ListScrHot.InsertColumn(4,"Subroutine",LVCFMT_LEFT,150,0);

	m_ListDlgObjHot.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_ListDlgObjHot.InsertColumn(0,"DlgID",LVCFMT_LEFT,40,0);
	m_ListDlgObjHot.InsertColumn(1,"ObjID",LVCFMT_LEFT,40,0);
	m_ListDlgObjHot.InsertColumn(2,"HotID",LVCFMT_LEFT,40,0);
	m_ListDlgObjHot.InsertColumn(3,"Key Name",LVCFMT_LEFT,100,0);
	m_ListDlgObjHot.InsertColumn(4,"Modifiers",LVCFMT_LEFT,100,0);
	m_ListDlgObjHot.InsertColumn(5,"Hot Seq",LVCFMT_LEFT,100,0);
	m_ListDlgObjHot.InsertColumn(6,"Subroutine",LVCFMT_LEFT,150,0);

	m_ListScrObjHot.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_ListScrObjHot.InsertColumn(0,"ObjID",LVCFMT_LEFT,40,0);
	m_ListScrObjHot.InsertColumn(1,"HotID",LVCFMT_LEFT,40,0);
	m_ListScrObjHot.InsertColumn(2,"Key Name",LVCFMT_LEFT,100,0);
	m_ListScrObjHot.InsertColumn(3,"Modifiers",LVCFMT_LEFT,100,0);
	m_ListScrObjHot.InsertColumn(4,"Hot Seq",LVCFMT_LEFT,100,0);
	m_ListScrObjHot.InsertColumn(5,"Subroutine",LVCFMT_LEFT,150,0);

	m_ListDlgObjMP.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_ListDlgObjMP.InsertColumn(0,"DlgID",LVCFMT_LEFT,40,0);
	m_ListDlgObjMP.InsertColumn(1,"ObjID",LVCFMT_LEFT,40,0);
	m_ListDlgObjMP.InsertColumn(2,"ObjName",LVCFMT_LEFT,100,0);
	m_ListDlgObjMP.InsertColumn(3,"Status",LVCFMT_LEFT,40,0);
	m_ListDlgObjMP.InsertColumn(4,"Message",LVCFMT_LEFT,120,0);
	m_ListDlgObjMP.InsertColumn(5,"Subroutine",LVCFMT_LEFT,150,0);
	
	m_ListScrObjMP.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_ListScrObjMP.InsertColumn(0,"ScrID",LVCFMT_LEFT,40,0);
	m_ListScrObjMP.InsertColumn(1,"ObjID",LVCFMT_LEFT,40,0);
	m_ListScrObjMP.InsertColumn(2,"ObjName",LVCFMT_LEFT,100,0);
	m_ListScrObjMP.InsertColumn(3,"Status",LVCFMT_LEFT,40,0);
	m_ListScrObjMP.InsertColumn(4,"Message",LVCFMT_LEFT,120,0);
	m_ListScrObjMP.InsertColumn(5,"Subroutine",LVCFMT_LEFT,150,0);
	
	m_ListDlgData.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_ListDlgData.InsertColumn(0,"DlgID",LVCFMT_LEFT,40,0);
	m_ListDlgData.InsertColumn(1,"DataId",LVCFMT_LEFT,40,0);

	m_ListScrData.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_ListScrData.InsertColumn(0,"ScrID",LVCFMT_LEFT,40,0);
	m_ListScrData.InsertColumn(1,"DataId",LVCFMT_LEFT,40,0);

	m_ListInput.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_ListInput.InsertColumn(0,"Num",LVCFMT_LEFT,40,0);
	m_ListInput.InsertColumn(1,"Input Value",LVCFMT_LEFT,340,0);

	m_ListNamedData.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_ListNamedData.InsertColumn(0,"Name",LVCFMT_LEFT,40,0);
	m_ListNamedData.InsertColumn(1,"Value",LVCFMT_LEFT,340,0);

	m_ListObjName.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_ListObjName.InsertColumn(0,"Dlg",LVCFMT_LEFT,60,0);
	m_ListObjName.InsertColumn(1,"Obj Name",LVCFMT_LEFT,140,0);
	m_ListObjName.InsertColumn(2,"Obj Id",LVCFMT_RIGHT,40,0);

	UpdateTabs();

	return TRUE;
}

void GPDlgViewMPVar::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	AUSI.UpdateSize();
}

void GPDlgViewMPVar::OnTimer(UINT nIDEvent) 
{
	ModifyStyle(WS_DISABLED,0);
	CDialog::OnTimer(nIDEvent);
}


void GPDlgViewMPVar::UpdateTabs()
{
	m_List1.ModifyStyle(WS_VISIBLE, 0);
	m_List2.ModifyStyle(WS_VISIBLE, 0);
	m_ListDlgMp.ModifyStyle(WS_VISIBLE, 0);
	m_ListScrMp.ModifyStyle(WS_VISIBLE, 0);
	m_ListDlgMenu.ModifyStyle(WS_VISIBLE, 0);
	m_ListScrMenu.ModifyStyle(WS_VISIBLE, 0);
	m_ListDlgHot.ModifyStyle(WS_VISIBLE, 0);
	m_ListScrHot.ModifyStyle(WS_VISIBLE, 0);
	m_ListDlgObjHot.ModifyStyle(WS_VISIBLE, 0);
	m_ListScrObjHot.ModifyStyle(WS_VISIBLE, 0);
	m_ListDlgObjMP.ModifyStyle(WS_VISIBLE, 0);
	m_ListScrObjMP.ModifyStyle(WS_VISIBLE, 0);
	m_ListDlgData.ModifyStyle(WS_VISIBLE, 0);
	m_ListScrData.ModifyStyle(WS_VISIBLE, 0);
	m_ListInput.ModifyStyle(WS_VISIBLE, 0);
	m_ListNamedData.ModifyStyle(WS_VISIBLE, 0);
	m_ListObjName.ModifyStyle(WS_VISIBLE, 0);

	switch(m_Tab.GetCurSel())
	{
	case 0:		m_List1.ModifyStyle(0,WS_VISIBLE);			break;
	case 1:		m_List2.ModifyStyle(0,WS_VISIBLE);			break;
	case 2:		m_ListDlgMp.ModifyStyle(0,WS_VISIBLE);		break;
	case 3:		m_ListScrMp.ModifyStyle(0,WS_VISIBLE);		break;
	case 4:		m_ListDlgMenu.ModifyStyle(0,WS_VISIBLE);	break;
	case 5:		m_ListScrMenu.ModifyStyle(0,WS_VISIBLE);	break;
	case 6:		m_ListDlgHot.ModifyStyle(0,WS_VISIBLE);		break;
	case 7:		m_ListScrHot.ModifyStyle(0,WS_VISIBLE);		break;
	case 8:		m_ListDlgObjHot.ModifyStyle(0,WS_VISIBLE);	break;
	case 9:		m_ListScrObjHot.ModifyStyle(0,WS_VISIBLE);	break;
	case 10:	m_ListDlgObjMP.ModifyStyle(0,WS_VISIBLE);	break;
	case 11:	m_ListScrObjMP.ModifyStyle(0,WS_VISIBLE);	break;
	case 12:	m_ListDlgData.ModifyStyle(0,WS_VISIBLE);	break;
	case 13:	m_ListScrData.ModifyStyle(0,WS_VISIBLE);	break;
	case 14:	m_ListInput.ModifyStyle(0,WS_VISIBLE);		break;
	case 15:	m_ListNamedData.ModifyStyle(0,WS_VISIBLE);	break;
	case 16:	m_ListObjName.ModifyStyle(0,WS_VISIBLE);	break;
	}
	Invalidate();
}

void GPDlgViewMPVar::OnSelchangeTabvar(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateTabs();	
	*pResult = 0;
}

void GPDlgViewMPVar::OnBtnupdate() 
{
	BeginWaitCursor();
	char *strVar=NULL;
	GPC.m_Document->MPGetVariables(&strVar);
	m_List1.DeleteAllItems();
	m_List2.DeleteAllItems();
	m_ListDlgMp.DeleteAllItems();
	m_ListScrMp.DeleteAllItems();
	m_ListDlgMenu.DeleteAllItems();
	m_ListScrMenu.DeleteAllItems();
	m_ListDlgHot.DeleteAllItems();
	m_ListScrHot.DeleteAllItems();
	m_ListDlgObjHot.DeleteAllItems();
	m_ListScrObjHot.DeleteAllItems();
	m_ListDlgObjMP.DeleteAllItems();
	m_ListScrObjMP.DeleteAllItems();
	m_ListDlgData.DeleteAllItems();
	m_ListScrData.DeleteAllItems();
	m_ListInput.DeleteAllItems();
	m_ListNamedData.DeleteAllItems();
	m_ListObjName.DeleteAllItems();

	if (strVar!=NULL)
	{
		int nItem=0,it=0,vm,svm,usvm,susvm,esusvm,IdScrDlg;
		char *PosAM,*nextPosAM;
		char *PosVM,*nextPosVM;
		char *PosSVM,*nextPosSVM;
		char *PosUSVM,*nextPosUSVM;
		char *PosSUSVM,*nextPosSUSVM;
		char *PosESUSVM,*nextPosESUSVM;
		int LastObjId=-1;
		PosAM=strVar;
		CString LastNmObj;

		while(PosAM!=NULL && *PosAM!=0)
		{
			nextPosAM=strchr(PosAM,6);
			if (nextPosAM!=NULL) *(nextPosAM++)=0;
			PosVM=PosAM;
			vm=0;
			while(PosVM!=NULL && *PosVM!=0)
			{
				LastObjId=-1;
				nextPosVM=strchr(PosVM,1);
				if (nextPosVM!=NULL) *(nextPosVM++)=0;
				if (it<18)
				{
					switch(vm)
					{
					case 0:		nItem=m_List1.InsertItem(it,PosVM); break;
					case 1:		m_List1.SetItemText(nItem,1,PosVM); break;
					}
				}
				else
				if(it==18)
				{
					char strtmp[100];
					sprintf(strtmp,"%d",vm+1);
					nItem=m_List2.InsertItem(vm,strtmp); 
					m_List2.SetItemText(nItem,1,PosVM); 
				}
				else
				if(it==25)
				{
					if(vm!=0)
					{
						char strtmp[100];
						sprintf(strtmp,"%d",vm);
						nItem=m_ListInput.InsertItem(vm,strtmp); 
						m_ListInput.SetItemText(nItem,1,PosVM); 
					}
				}
				else
				{
					PosSVM=PosVM;
					svm=0;
					usvm=0;
					while(PosSVM!=NULL && *PosSVM!=0)
					{
						nextPosSVM=strchr(PosSVM,2);
						if (nextPosSVM!=NULL) *(nextPosSVM++)=0;
						if(it==28 && vm!=0)//NamedData
						{
							if (svm==0)
								nItem=m_ListNamedData.InsertItem(100000,PosSVM); 
							else
								m_ListNamedData.SetItemText(nItem,1,PosSVM);
						}
						else
						if(it==29 && vm!=0)//NamedData
						{
							char strtmp[100];
							if (svm==0)
							{
								sprintf(strtmp,"Dlg %d",vm);
								nItem=m_ListObjName.InsertItem(100000,strtmp); 
								if (GPC.m_Document->a_GPObjDialog[vm-1]==NULL 
									&& GPC.m_Document->a_GPObjFrame[vm-1]==NULL )	
								{
										sprintf(strtmp,"Dlg %d ????",vm);
										m_ListObjName.SetItemText(nItem,0,strtmp);
								}
							}
							m_ListObjName.SetItemText(nItem,svm+1,PosSVM);
						}
						else
						if(it==26 && vm==0)//ScrData
						{
							CString tmps;
							tmps=m_List1.GetItemText(10,1);
							int nCol=atoi(tmps);
							int i;
							for(i=0;i<=nCol;i++)
								m_ListScrData.DeleteColumn(1);

							for(i=0;i<nCol;i++)
							{
								tmps.Format("%d",i+1);
								m_ListScrData.InsertColumn(i+1,tmps,LVCFMT_LEFT,55);
							}
						}
						else
						if(it==26 && vm!=0)//ScrData
						{
							char strtmp[100];
							if (svm==0)
							{
								sprintf(strtmp,"Dlg %d",vm);
								nItem=m_ListScrData.InsertItem(100000,strtmp); 
								if (GPC.m_Document->a_GPObjDialog[vm-1]==NULL 
									&& GPC.m_Document->a_GPObjFrame[vm-1]==NULL )	
								{
										sprintf(strtmp,"Dlg %d ????",vm);
										m_ListScrData.SetItemText(nItem,0,strtmp);
								}
							}

							m_ListScrData.SetItemText(nItem,usvm+1,PosSVM);
						}
						else
						if(it==27 && vm==0)//DlgData
						{
							CString tmps;
							tmps=m_List1.GetItemText(10,1);
							int nCol=atoi(tmps);
							int i;
							for(i=0;i<=nCol;i++)
								m_ListDlgData.DeleteColumn(1);

							for(i=0;i<nCol;i++)
							{
								tmps.Format("%d",i+1);
								m_ListDlgData.InsertColumn(i+1,tmps,LVCFMT_LEFT,55);
							}
						}
						else
						if(it==27 && vm!=0)//DlgData
						{
							char strtmp[100];
							if (svm==0)
							{
								sprintf(strtmp,"Dlg %d",vm);
								nItem=m_ListDlgData.InsertItem(100000,strtmp); 
								if (GPC.m_Document->a_GPObjDialog[vm-1]==NULL 
									&& GPC.m_Document->a_GPObjFrame[vm-1]==NULL )	
								{
										sprintf(strtmp,"Dlg %d ????",vm);
										m_ListDlgData.SetItemText(nItem,0,strtmp);
								}
							}
							m_ListDlgData.SetItemText(nItem,svm+1,PosSVM);
						}
						else
						{
							PosUSVM=PosSVM;
							usvm=0;
							while(PosUSVM!=NULL && *PosUSVM!=0)
							{
								nextPosUSVM=strchr(PosUSVM,3);
								if (nextPosUSVM!=NULL) *(nextPosUSVM++)=0;
								if(it==19 && vm!=0)
								{
									IdScrDlg=vm;
									if (svm==0)
									{
										char strtmp[100];
										sprintf(strtmp,"%d",IdScrDlg);
										nItem=m_ListDlgMp.InsertItem(100000,strtmp); 
									}
									else
									{
										if (usvm==0)
										{
											char strtmp[100];
											sprintf(strtmp,"%d",IdScrDlg);
											nItem=m_ListDlgMp.InsertItem(100000,strtmp); 
										}
										m_ListDlgMp.SetItemText(nItem,usvm+1,PosUSVM);
									}
								}
								else
								if(it==20 && vm!=0)
								{
									IdScrDlg=vm;
									if (svm==0)
									{
										char strtmp[100];
										sprintf(strtmp,"%d",IdScrDlg);
										nItem=m_ListScrMp.InsertItem(100000,strtmp); 
									}
									else
									{
										if (usvm==0)
										{
											char strtmp[100];
											sprintf(strtmp,"%d",IdScrDlg);
											nItem=m_ListScrMp.InsertItem(100000,strtmp); 
										}
										m_ListScrMp.SetItemText(nItem,usvm+1,PosUSVM);
									}
								}
								else
								if(it==21 && vm!=0 && vm<3)//ScrMenuMessageMap
								{
									char strtmp[100];
									if (*PosUSVM!=0)
									{
										if (vm==1)//ScrMenuMessageMap(0)  Menu
										{
											UINT idPop[50],PosM[50],nFind=0;
											CString nm[50];
											nFind=GPC.m_View->m_GPMenu->FindMenuItem(svm+1,idPop,PosM,nm,49);
											if (nFind==0)
											{
												nItem=m_ListScrMenu.InsertItem(100000,"???"); 
												sprintf(strtmp,"%d",usvm+1);
												m_ListScrMenu.SetItemText(nItem,1,strtmp);
												m_ListScrMenu.SetItemText(nItem,4,PosUSVM);
											}
											else
											{
												UINT j;
												for(j=0;j<nFind;j++)
												{
													sprintf(strtmp,"%d",idPop[j]);
													nItem=m_ListScrMenu.InsertItem(100000,strtmp); 
													sprintf(strtmp,"%d",usvm+1);
													m_ListScrMenu.SetItemText(nItem,1,strtmp);
													sprintf(strtmp,"%d",PosM[j]);
													m_ListScrMenu.SetItemText(nItem,2,strtmp);
													m_ListScrMenu.SetItemText(nItem,3,(LPCTSTR)nm[j]);
													m_ListScrMenu.SetItemText(nItem,4,PosUSVM);
												}
											}
										}
										else
										if (vm==2)//ScrMenuMessageMap(1)  Hotkey
										{
											CString oName,oModifier,oSeq;
											BOOL nFind=FALSE;
											
											nFind=GPC.m_View->UnitHotkey->GetHotKey(usvm+1,oName,oModifier,oSeq);

											if (!nFind)
											{
												sprintf(strtmp,"%d",usvm+1);
												nItem=m_ListScrHot.InsertItem(100000,strtmp); 
												m_ListScrHot.SetItemText(nItem,1,"???");
												m_ListScrHot.SetItemText(nItem,4,PosUSVM);
											}
											else
												{
													sprintf(strtmp,"%d",usvm+1);
													nItem=m_ListDlgHot.InsertItem(100000,strtmp); 
													m_ListScrHot.SetItemText(nItem,1,(LPCTSTR)oName);
													m_ListScrHot.SetItemText(nItem,2,(LPCTSTR)oModifier);
													m_ListScrHot.SetItemText(nItem,3,(LPCTSTR)oSeq);
													m_ListScrHot.SetItemText(nItem,4,PosUSVM);
												}
										}
									}
								}
								else
								if(it==22 && vm!=0 && svm<2)//DlgMenuMessageMap
								{
									char strtmp[100];
									IdScrDlg=vm;
									if (*PosUSVM!=0 && vm<MAX_OBJDLG)
									{
										if (svm==0)//DlgMenuMessageMap(0)  Menu
										{
											UINT idPop[50],PosM[50],nFind=0;
											CString nm[50];
											if (GPC.m_Document->a_GPObjDialog[vm-1]!=NULL)
												nFind=GPC.m_Document->a_GPObjDialog[vm-1]->DlgGPMenu->FindMenuItem(usvm+1,idPop,PosM,nm,49);
											else
											if (GPC.m_Document->a_GPObjFrame[vm-1]!=NULL)
												nFind=GPC.m_Document->a_GPObjFrame[vm-1]->DlgGPMenu->FindMenuItem(usvm+1,idPop,PosM,nm,49);

											if (nFind==0)
											{
												sprintf(strtmp,"Dlg %d",IdScrDlg);
												nItem=m_ListDlgMenu.InsertItem(100000,strtmp); 
												m_ListDlgMenu.SetItemText(nItem,1,"???");
												sprintf(strtmp,"%d",usvm+1);
												m_ListDlgMenu.SetItemText(nItem,2,strtmp);
												m_ListDlgMenu.SetItemText(nItem,5,PosUSVM);
											}
											else
											{
												UINT j;
												for(j=0;j<nFind;j++)
												{
													sprintf(strtmp,"Dlg %d",IdScrDlg);
													nItem=m_ListDlgMenu.InsertItem(100000,strtmp); 
													sprintf(strtmp,"%d",idPop[j]);
													m_ListDlgMenu.SetItemText(nItem,1,strtmp);
													sprintf(strtmp,"%d",usvm+1);
													m_ListDlgMenu.SetItemText(nItem,2,strtmp);
													sprintf(strtmp,"%d",PosM[j]);
													m_ListDlgMenu.SetItemText(nItem,3,strtmp);
													m_ListDlgMenu.SetItemText(nItem,4,(LPCTSTR)nm[j]);
													m_ListDlgMenu.SetItemText(nItem,5,PosUSVM);
												}
											}
										}
										else
										if (svm==1)//DlgMenuMessageMap(1)  HotKey
										{
											CString oName,oModifier,oSeq;
											BOOL nFind=FALSE;
											
											if (GPC.m_Document->a_GPObjDialog[vm-1])
											{
												if (GPC.m_Document->a_GPObjDialog[vm-1]->GPU && GPC.m_Document->a_GPObjDialog[vm-1]->GPU[0] && GPC.m_Document->a_GPObjDialog[vm-1]->GPU[0]->UnitHotkey)
													nFind=GPC.m_Document->a_GPObjDialog[vm-1]->GPU[0]->UnitHotkey->GetHotKey(usvm+1,oName,oModifier,oSeq);
											}
											else
											if (GPC.m_Document->a_GPObjFrame[vm-1])
											{
												if (GPC.m_Document->a_GPObjFrame[vm-1]->GPU && GPC.m_Document->a_GPObjFrame[vm-1]->GPU[0] && GPC.m_Document->a_GPObjFrame[vm-1]->GPU[0]->UnitHotkey)
													nFind=GPC.m_Document->a_GPObjFrame[vm-1]->GPU[0]->UnitHotkey->GetHotKey(usvm+1,oName,oModifier,oSeq);
											}

											if (!nFind)
											{
												sprintf(strtmp,"Dlg %d",IdScrDlg);
												nItem=m_ListDlgHot.InsertItem(100000,strtmp); 
												m_ListDlgHot.SetItemText(nItem,1,"???");
												sprintf(strtmp,"%d",usvm+1);
												m_ListDlgHot.SetItemText(nItem,2,strtmp);
												m_ListDlgHot.SetItemText(nItem,5,PosUSVM);
											}
											else
												{
													sprintf(strtmp,"Dlg %d",IdScrDlg);
													nItem=m_ListDlgHot.InsertItem(100000,strtmp); 
													sprintf(strtmp,"%d",usvm+1);
													m_ListDlgHot.SetItemText(nItem,1,strtmp);
													m_ListDlgHot.SetItemText(nItem,2,(LPCTSTR)oName);
													m_ListDlgHot.SetItemText(nItem,3,(LPCTSTR)oModifier);
													m_ListDlgHot.SetItemText(nItem,4,(LPCTSTR)oSeq);
													m_ListDlgHot.SetItemText(nItem,5,PosUSVM);
												}
										}
									}
								}
								else
								{
									PosSUSVM=PosUSVM;
									susvm=0;
									while(PosSUSVM!=NULL && *PosSUSVM!=0)
									{
										nextPosSUSVM=strchr(PosSUSVM,4);
										if (nextPosSUSVM!=NULL) *(nextPosSUSVM++)=0;
										if(it==21 && vm==3)//ScrMenuMessageMap
										{
											char strtmp[100];
											if (*PosSUSVM!=0 && svm<MAX_OBJDLG)
											{//ScrMenuMessageMap(2)  Obj Hotkey
												CString oName,oModifier,oSeq;
												BOOL nFind=FALSE;
												GPUnit *tmpu=NULL;
												tmpu=GPC.m_Document->GetMainScreen()->GPGetWindowById(0)->GetUnitById(svm+1);
												if (tmpu!=NULL && tmpu->UnitHotkey!=NULL)
													nFind=tmpu->UnitHotkey->GetHotKey(usvm+1,oName,oModifier,oSeq);

												if (nFind==0)
												{
													sprintf(strtmp,"Obj %d",svm+1);
													nItem=m_ListScrObjHot.InsertItem(100000,strtmp); 
													m_ListScrObjHot.SetItemText(nItem,1,"???");
													sprintf(strtmp,"%d",svm+1);
													m_ListScrObjHot.SetItemText(nItem,2,strtmp);
													m_ListScrObjHot.SetItemText(nItem,6,PosUSVM);
												}
												else
													{
														sprintf(strtmp,"Obj %d",svm+1);
														nItem=m_ListScrObjHot.InsertItem(100000,strtmp); 
														sprintf(strtmp,"%d",usvm+1);
														m_ListScrObjHot.SetItemText(nItem,1,strtmp);
														m_ListScrObjHot.SetItemText(nItem,2,(LPCTSTR)oName);
														m_ListScrObjHot.SetItemText(nItem,3,(LPCTSTR)oModifier);
														m_ListScrObjHot.SetItemText(nItem,4,(LPCTSTR)oSeq);
														m_ListScrObjHot.SetItemText(nItem,5,PosUSVM);
													}
											}
										}
										else
										if(it==22 && vm!=0 && svm==2)//DlgMenuMessageMap
										{
											char strtmp[100];
											IdScrDlg=vm;
											if (*PosSUSVM!=0 && vm<MAX_OBJDLG)
											{//DlgMenuMessageMap(2)  Obj Hotkey
												CString oName,oModifier,oSeq;
												BOOL nFind=FALSE;
												if (GPC.m_Document->a_GPObjDialog[vm-1]!=NULL 
													&& GPC.m_Document->a_GPObjDialog[vm-1]->GPU!=NULL
													&& GPC.m_Document->a_GPObjDialog[vm-1]->GPU[usvm+1]!=NULL
													&& GPC.m_Document->a_GPObjDialog[vm-1]->GPU[usvm+1]->UnitHotkey!=NULL)
														nFind=GPC.m_Document->a_GPObjDialog[vm-1]->GPU[usvm+1]->UnitHotkey->GetHotKey(susvm+1,oName,oModifier,oSeq);
												else
												if (GPC.m_Document->a_GPObjFrame[vm-1]!=NULL 
													&& GPC.m_Document->a_GPObjFrame[vm-1]->GPU!=NULL
													&& GPC.m_Document->a_GPObjFrame[vm-1]->GPU[usvm+1]!=NULL
													&& GPC.m_Document->a_GPObjFrame[vm-1]->GPU[usvm+1]->UnitHotkey!=NULL)
														nFind=GPC.m_Document->a_GPObjFrame[vm-1]->GPU[usvm+1]->UnitHotkey->GetHotKey(susvm+1,oName,oModifier,oSeq);

												if (nFind==0)
												{
													sprintf(strtmp,"Dlg %d",IdScrDlg);
													nItem=m_ListDlgObjHot.InsertItem(100000,strtmp); 
													m_ListDlgObjHot.SetItemText(nItem,1,"???");
													sprintf(strtmp,"%d",usvm+1);
													m_ListDlgObjHot.SetItemText(nItem,2,strtmp);
													m_ListDlgObjHot.SetItemText(nItem,6,PosSUSVM);
												}
												else
													{
														sprintf(strtmp,"Dlg %d",IdScrDlg);
														nItem=m_ListDlgObjHot.InsertItem(100000,strtmp); 
														sprintf(strtmp,"%d",usvm+1);
														m_ListDlgObjHot.SetItemText(nItem,1,strtmp);
														sprintf(strtmp,"%d",susvm+1);
														m_ListDlgObjHot.SetItemText(nItem,2,strtmp);
														m_ListDlgObjHot.SetItemText(nItem,3,(LPCTSTR)oName);
														m_ListDlgObjHot.SetItemText(nItem,4,(LPCTSTR)oModifier);
														m_ListDlgObjHot.SetItemText(nItem,5,(LPCTSTR)oSeq);
														m_ListDlgObjHot.SetItemText(nItem,6,PosSUSVM);
													}
											}
										}
										else
										if(it==23 && vm!=0)//ScrObjMP
										{
											char strtmp[100];
											IdScrDlg=vm;
											if (*PosSUSVM!=0 && vm<MAX_OBJDLG)
											{

												if (susvm==0 && LastObjId!=svm)
												{
													LastObjId=svm;
													sprintf(strtmp,"Scr %d",IdScrDlg);
													nItem=m_ListScrObjMP.InsertItem(100000,strtmp); 
													sprintf(strtmp,"%d",svm+1);
													m_ListScrObjMP.SetItemText(nItem,1,strtmp);
													LastNmObj=PosSUSVM;
													m_ListScrObjMP.SetItemText(nItem,2,LastNmObj);
												}
												else
												if (susvm==0) 
												{
													sprintf(strtmp,"Scr %d",IdScrDlg);
													nItem=m_ListScrObjMP.InsertItem(100000,strtmp); 
													sprintf(strtmp,"%d",svm+1);
													m_ListScrObjMP.SetItemText(nItem,1,strtmp);
													m_ListScrObjMP.SetItemText(nItem,2,LastNmObj);
													m_ListScrObjMP.SetItemText(nItem,4,PosSUSVM);
												}
												else
												if (susvm==1) 
												{
													m_ListScrObjMP.SetItemText(nItem,5,PosSUSVM);
												}
											}
										}
										else
										if(it==24 && vm!=0)//DlgObjMP
										{
											char strtmp[100];
											IdScrDlg=vm;
											if (*PosSUSVM!=0 && vm<MAX_OBJDLG)
											{
												const char 	* status="ERROR";

												if (susvm==0 && LastObjId!=svm)
												{
													if (GPC.m_Document->a_GPObjDialog[vm-1]!=NULL 
														&& GPC.m_Document->a_GPObjDialog[vm-1]->GPU!=NULL
														&& GPC.m_Document->a_GPObjDialog[vm-1]->GPU[svm+1]!=NULL
														&& GPC.m_Document->a_GPObjDialog[vm-1]->GPU[svm+1]->GPMSG!=NULL)
															status="OK";
													else
													if (GPC.m_Document->a_GPObjFrame[vm-1]!=NULL 
														&& GPC.m_Document->a_GPObjFrame[vm-1]->GPU!=NULL
														&& GPC.m_Document->a_GPObjFrame[vm-1]->GPU[svm+1]!=NULL
														&& GPC.m_Document->a_GPObjFrame[vm-1]->GPU[svm+1]->GPMSG!=NULL)
															status="OK";

													LastObjId=svm;
													sprintf(strtmp,"Dlg %d",IdScrDlg);
													nItem=m_ListDlgObjMP.InsertItem(100000,strtmp); 
													sprintf(strtmp,"%d",svm+1);
													m_ListDlgObjMP.SetItemText(nItem,1,strtmp);
													LastNmObj=PosSUSVM;
													m_ListDlgObjMP.SetItemText(nItem,2,LastNmObj);
													m_ListDlgObjMP.SetItemText(nItem,3,status);
												}
												else
												if (susvm==0) 
												{
													if (GPC.m_Document->a_GPObjDialog[vm-1]!=NULL 
														&& GPC.m_Document->a_GPObjDialog[vm-1]->GPU!=NULL
														&& GPC.m_Document->a_GPObjDialog[vm-1]->GPU[svm+1]!=NULL
														&& GPC.m_Document->a_GPObjDialog[vm-1]->GPU[svm+1]->GPMSG!=NULL
														&& GPC.m_Document->a_GPObjDialog[vm-1]->GPU[svm+1]->GPMSG->FindInActive(PosSUSVM)!=NULL)
															status="OK";
													else
													if (GPC.m_Document->a_GPObjFrame[vm-1]!=NULL 
														&& GPC.m_Document->a_GPObjFrame[vm-1]->GPU!=NULL
														&& GPC.m_Document->a_GPObjFrame[vm-1]->GPU[svm+1]!=NULL
														&& GPC.m_Document->a_GPObjFrame[vm-1]->GPU[svm+1]->GPMSG!=NULL
														&& GPC.m_Document->a_GPObjFrame[vm-1]->GPU[svm+1]->GPMSG->FindInActive(PosSUSVM)!=NULL)
															status="OK";

													sprintf(strtmp,"Dlg %d",IdScrDlg);
													nItem=m_ListDlgObjMP.InsertItem(100000,strtmp); 
													sprintf(strtmp,"%d",svm+1);
													m_ListDlgObjMP.SetItemText(nItem,1,strtmp);
													m_ListDlgObjMP.SetItemText(nItem,2,LastNmObj);
													m_ListDlgObjMP.SetItemText(nItem,3,status);
													m_ListDlgObjMP.SetItemText(nItem,4,PosSUSVM);
												}
												else
												if (susvm==1) 
													m_ListDlgObjMP.SetItemText(nItem,5,PosSUSVM);
											}
										}
										else
										{

											PosESUSVM=PosSUSVM;
											esusvm=0;
											while(PosESUSVM!=NULL && *PosESUSVM!=0)
											{
												nextPosESUSVM=strchr(PosESUSVM,5);
												if (nextPosESUSVM!=NULL) *(nextPosESUSVM++)=0;

												if ((PosESUSVM=nextPosESUSVM)!=NULL) *(--nextPosESUSVM)=5;
												esusvm++;
											}
										}

										if ((PosSUSVM=nextPosSUSVM)!=NULL) *(--nextPosSUSVM)=4;
										susvm++;
									}
								}
								if ((PosUSVM=nextPosUSVM)!=NULL) *(--nextPosUSVM)=3;
								usvm++;
							}
						}
						if ((PosSVM=nextPosSVM)!=NULL) *(--nextPosSVM)=2;
						svm++;
					}
				}
				if ((PosVM=nextPosVM)!=NULL) *(--nextPosVM)=1;
				vm++;
			}
			if ((PosAM=nextPosAM)!=NULL) *(--nextPosAM)=6;
			it++;
		}

		delete[] strVar;
	}
	EndWaitCursor();
}

#include "DlgViewItem.h"

void GPDlgViewMPVar::OnDblclkList13(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	if (lpnmitem)
	{
		CString str;
		str=m_ListDlgData.GetItemText(lpnmitem->iItem,lpnmitem->iSubItem);
		if (str!="" && str.FindOneOf("\x3\x4")>=0)
		{
			CDlgViewItem dlg(str,3,4);
			dlg.DoModal();
		}
	}
	*pResult = 0;
}

void GPDlgViewMPVar::OnDblclkList14(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	if (lpnmitem)
	{
		CString str;
		str=m_ListDlgData.GetItemText(lpnmitem->iItem,lpnmitem->iSubItem);
		if (str!="" && str.FindOneOf("\x3\x4")>=0)
		{
			CDlgViewItem dlg(str,3,4);
			dlg.DoModal();
		}
	}
	*pResult = 0;
}

void GPDlgViewMPVar::OnDblclkListnameddata(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	if (lpnmitem)
	{
		CString str;
		str=m_ListNamedData.GetItemText(lpnmitem->iItem,lpnmitem->iSubItem);
		if (str!="" && str.FindOneOf("\x2\x3")>=0)
		{
			CDlgViewItem dlg(str,2,3);
			dlg.DoModal();
		}
	}
	*pResult = 0;
}

void GPDlgViewMPVar::OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	if (lpnmitem)
	{
		CString str=m_List2.GetItemText(lpnmitem->iItem,1);
		if (str=="")
		{ //open
			GPDlgNewValue dlg(str);
			if (dlg.DoModal()==IDOK && str!=dlg.m_NewValue)
			{
				GPC.m_Document->GPOLEOpenPICKFile(dlg.m_NewValue);
				OnBtnupdate();
			}
		}
		else
		{ //close
#ifdef RUS
			str="Закрыть файл " + str + " ?";
			if (MessageBox(str,"Закрытие файла",MB_ICONQUESTION|MB_APPLMODAL|MB_YESNO|MB_DEFBUTTON2)==IDYES)
#else
			str="Close file " + str + " ?";
			if (MessageBox(str,"Closing file",MB_ICONQUESTION|MB_APPLMODAL|MB_YESNO|MB_DEFBUTTON2)==IDYES)
#endif
			{
				GPC.m_Document->GPOLEClosePICKFile(lpnmitem->iItem);
				OnBtnupdate();
			}
		}
	}
	
	*pResult = 0;
}
