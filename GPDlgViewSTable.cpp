// GPDlgViewSTable.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPDlgViewSTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGPDlgViewSTable dialog
#include "GP_TermView.h"


CGPDlgViewSTable::CGPDlgViewSTable(CWnd* pParent /*=NULL*/)
	: CDialog(CGPDlgViewSTable::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGPDlgViewSTable)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGPDlgViewSTable::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGPDlgViewSTable)
	DDX_Control(pDX, IDC_BUTTONNEWVALUE, m_btnNewValue);
	DDX_Control(pDX, IDC_BUTTONUPD, m_btnUpdate);
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGPDlgViewSTable, CDialog)
	//{{AFX_MSG_MAP(CGPDlgViewSTable)
	ON_BN_CLICKED(IDC_BUTTONUPD, OnButtonupd)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_BUTTONNEWVALUE, OnButtonnewvalue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGPDlgViewSTable message handlers

void CGPDlgViewSTable::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	AUSI.UpdateSize();
}

BOOL CGPDlgViewSTable::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetTimer(1,2000,NULL);

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_List.InsertColumn(0,"Variables",LVCFMT_LEFT,150,0);
	m_List.InsertColumn(1,"Set",LVCFMT_RIGHT,30,0);
	m_List.InsertColumn(2,"Value",LVCFMT_LEFT,500,0);

	AUSI.AddSetMain(this->m_hWnd);
	AUSI.AddWnd(m_List.m_hWnd,this->m_hWnd	,"NNEE");
	AUSI.AddWnd(m_btnUpdate.m_hWnd,this->m_hWnd		,"EEEE");
	AUSI.AddWnd(m_btnNewValue.m_hWnd,this->m_hWnd	,"ENEN");

	OnButtonupd();
	return TRUE;
}

void CGPDlgViewSTable::OnTimer(UINT nIDEvent) 
{
	CDialog::OnTimer(nIDEvent);
	ModifyStyle(WS_DISABLED,0);
}

void CGPDlgViewSTable::OnButtonupd() 
{
	CString StrVar;
	CString StrValue;
	EnterCriticalSection(&GPC.m_View->m_CSInputSema);
	EnterCriticalSection(&GPC.m_View->m_CSRemap);

	try
	{
		char buff[1000];
		m_List.DeleteAllItems();
		while(m_Comm.GPRead(buff,950)>0) Sleep(10);

		m_Comm.GPSendBlock("/*\r",3);

		int cntbrk=0;
		int CRcnt=0;
		buff[1]=0;
		BOOL flgCol=FALSE;
		int nItem=-123456;
		while(cntbrk<100 && CRcnt<2)
		{
			int nread;
			if ((nread=m_Comm.GPRead(buff,980))<=0) {Sleep(50);cntbrk++;}
			else
			{
				buff[nread]=0;
				char b2[5];
				b2[1]=0;
				int nb;
				for(nb=0;nb<nread;nb++)
				{
					if (buff[nb]==13) 	
					{
						if (StrVar!="" && nItem!=-123456)
						{
							if (StrVar.GetLength()==1 || StrVar[1]!=' ')
							{
								DosToAnsi(StrVar,StrVar);
								DosToAnsi(StrValue,StrValue);
								nItem=m_List.InsertItem(100000,StrVar);
								m_List.SetItemText(nItem,2,StrValue);
							}
							else	m_List.SetItemText(nItem,1,"U");
						}
						else nItem=-1;
						StrVar="";
						StrValue="";
						CRcnt++;
					}
					if (buff[nb]!=13 && buff[nb]!=10 && buff[nb]!=0)
					{
						if (CRcnt!=0) 
						{
							StrVar="";
							StrValue="";
							flgCol=FALSE;
							CRcnt=0;
						}
						if (!flgCol && (buff[nb]=='=' || buff[nb]==' ')) flgCol=TRUE;
						else
						{
							b2[0]=buff[nb];
							if (flgCol) StrValue+=b2;
							else		StrVar+=b2;
						}
					}
				}
			}
		}

		while(m_Comm.GPRead(buff,950)>0) Sleep(10);
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGPDlgViewSTable", "OnButtonupd","");
	}
	LeaveCriticalSection(&GPC.m_View->m_CSRemap);
	LeaveCriticalSection(&GPC.m_View->m_CSInputSema);
}

#include "DlgViewItem.h"


void CGPDlgViewSTable::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	if (lpnmitem)
	{
		CString str;
		str=m_List.GetItemText(lpnmitem->iItem,lpnmitem->iSubItem);
		char wof[3]={0};
		wof[0]=GPC.DelimiterIn1;
		wof[1]=GPC.DelimiterIn2;
		if (str!="" && str.FindOneOf(wof)>=0)
		{
			CDlgViewItem dlg(str,GPC.DelimiterIn1,GPC.DelimiterIn2);
			dlg.DoModal();
		}
	}
	*pResult = 0;
}

#include "GPDlgNewValue.h"

void CGPDlgViewSTable::OnButtonnewvalue() 
{
	int Sel=m_List.GetSelectionMark();

	if (Sel>=0)
	{
		CString str;
		str=m_List.GetItemText(Sel,2);
		GPDlgNewValue dlg(str);
		if (dlg.DoModal()==IDOK)
		{
			EnterCriticalSection(&GPC.m_View->m_CSInputSema);
			EnterCriticalSection(&GPC.m_View->m_CSRemap);
			try
			{
				CString sedS;
				CString varName=m_List.GetItemText(Sel,0);
				varName.Replace(" ","");
				sedS="/"+varName+"\r";
				AnsiToDos(sedS,sedS,0);
				m_Comm.GPSendBlock(sedS,sedS.GetLength());
				Sleep(100);
				sedS=dlg.m_NewValue+"\r";
				AnsiToDos(sedS,sedS,0);
				m_Comm.GPSendBlock(sedS,sedS.GetLength());
				m_List.SetItemText(Sel,2,dlg.m_NewValue);

				char buff[1000];
				while(m_Comm.GPRead(buff,950)>0) Sleep(100);
			}
			catch(...)
			{
				GPC.m_ErrReport.GPWriteErrorLog("CGPDlgViewSTable", "OnButtonnewvalue","");
			}

			LeaveCriticalSection(&GPC.m_View->m_CSRemap);
			LeaveCriticalSection(&GPC.m_View->m_CSInputSema);

		}
	}
}
