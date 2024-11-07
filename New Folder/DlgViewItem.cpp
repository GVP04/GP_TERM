// DlgViewItem.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgViewItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgViewItem dialog


CDlgViewItem::CDlgViewItem(CString &iStr, char Delim1, char Delim2, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewItem::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgViewItem)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	SrcStr=iStr;
	DelimAM=Delim1;
	DelimVM=Delim2;
}


void CDlgViewItem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgViewItem)
	DDX_Control(pDX, IDC_LIST1, m_ListItem);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgViewItem, CDialog)
	//{{AFX_MSG_MAP(CDlgViewItem)
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgViewItem message handlers

BOOL CDlgViewItem::OnInitDialog()
{
	CDialog::OnInitDialog();

	int iposVM=0;
	int iposAM=0;
	int nVM=0;
	int nVMtmp=0;
	char strfind[10];
	strfind[0]=DelimAM;
	strfind[1]=0;
	strfind[5]=DelimVM;
	strfind[6]=0;
	iposAM=SrcStr.Find(strfind,0);
	if (iposAM<0) iposAM=SrcStr.GetLength()-1;

	while((iposVM=SrcStr.Find(strfind+5,iposVM))>=0)
		if (++iposVM>iposAM)
		{
			if (nVMtmp>nVM) nVM=nVMtmp;
			nVMtmp=0;
			iposAM=SrcStr.Find(strfind,++iposAM);
			if (iposAM<0) iposAM=SrcStr.GetLength()-1;
		}
		else nVMtmp++;


	if (nVMtmp>nVM) nVM=nVMtmp;
	nVM++;
	nVM++;
	m_ListItem.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_ListItem.InsertColumn(0,"AM",LVCFMT_LEFT,40,0);
	int i;
	for(i=0;i<nVM;i++)
	{
		char strtmp[10];
		sprintf(strtmp,"V%3.3d",i+1);
		m_ListItem.InsertColumn(i+1,strtmp,LVCFMT_LEFT,55,0);
	}

	AUSI.AddSetMain(this->m_hWnd);
	AUSI.AddWnd(m_ListItem.m_hWnd,this->m_hWnd	,"NNEE");
	AUSI.SetMinSize(this->m_hWnd,250,100);

	int nItem=-1,it=0,vm;
	char *tmpSrcStr=new char [SrcStr.GetLength()+10];
	strcpy(tmpSrcStr,SrcStr);
	char *PosAM,*PosVM;
	char *nextPosAM,*nextPosVM;
	PosAM=tmpSrcStr;

	while(PosAM && *PosAM!=0)
	{
		nextPosAM=strchr(PosAM,DelimAM);
		if (nextPosAM) *(nextPosAM++)=0;
		PosVM=PosAM;
		vm=0;
		while(PosVM && *PosVM!=0)
		{
			nextPosVM=strchr(PosVM,DelimVM);
			if (nextPosVM) *(nextPosVM++)=0;

			if (vm==0)
			{
				char str[100];
				sprintf(str,"A%3.3d",it+1);
				nItem=m_ListItem.InsertItem(100000,str);
			}

			if (nItem>=0)
				m_ListItem.SetItemText(nItem,vm+1,PosVM);

			if ((PosVM=nextPosVM)) *(--nextPosVM)=1;
			vm++;
		}
		if ((PosAM=nextPosAM)) *(--nextPosAM)=6;
		it++;
	}
	delete[] tmpSrcStr;


	return TRUE;
}

void CDlgViewItem::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	AUSI.UpdateSize();
}

void CDlgViewItem::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	if (lpnmitem)
	{
		CString str;
		str=m_ListItem.GetItemText(lpnmitem->iItem,lpnmitem->iSubItem);
		if (str!="" && (str.Find(DelimAM==GPC.DelimiterIn1?GPC.DelimiterIn3:(char)(DelimAM+2))>=0 || str.Find(DelimVM==GPC.DelimiterIn2?(char)251:(char)(DelimVM+2))>=0))
		{
			CDlgViewItem dlg(str,DelimAM==GPC.DelimiterIn1?GPC.DelimiterIn3:(char)(DelimAM+2),DelimVM==GPC.DelimiterIn2?(char)251:(char)(DelimVM+2));
			dlg.DoModal();
		}
	}
	*pResult = 0;
}
