// GPDlgDebug.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPDlgDebug.h"
#include "GP_TermView.h"
#include "GPDlgViewSTable.h"
#include "GPDlgNewValue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPDlgDebug dialog


GPDlgDebug::GPDlgDebug(CWnd* pParent /*=NULL*/)
	: CDialog(GPDlgDebug::IDD, pParent)
{
	//{{AFX_DATA_INIT(GPDlgDebug)
	//}}AFX_DATA_INIT
	m_RTFPrg=NULL;
}

GPDlgDebug::~GPDlgDebug()
{
	if (m_RTFPrg!=NULL) delete m_RTFPrg;
	m_RTFPrg=NULL;
}

void GPDlgDebug::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GPDlgDebug)
	DDX_Control(pDX, IDC_CHECKAUTOUPDATE, m_chkAUpdate);
	DDX_Control(pDX, IDC_STATICWATCH, m_statWath);
	DDX_Control(pDX, IDC_STATICSTACK, m_statStack);
	DDX_Control(pDX, IDC_BUTTONDEL, m_btnDel);
	DDX_Control(pDX, IDC_BUTTONADD, m_btnAdd);
	DDX_Control(pDX, IDC_BTNUPDATE, m_btnUpdate);
	DDX_Control(pDX, IDC_BTNGO, m_btnGo);
	DDX_Control(pDX, IDC_BTNBREAK, m_btnBreak);
	DDX_Control(pDX, IDC_LISTVARS, m_ListWatch);
	DDX_Control(pDX, IDC_BTNVARTABLE, m_btnVarTable);
	DDX_Control(pDX, IDC_EDITNPRGLINE, m_EditNPrgLine);
	DDX_Control(pDX, IDC_LISTSTACK, m_ListStack);
	DDX_Control(pDX, IDC_EDITNGO, m_EditNGO);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GPDlgDebug, CDialog)
	//{{AFX_MSG_MAP(GPDlgDebug)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTNGO, OnBtngo)
	ON_BN_CLICKED(IDC_BTNBREAK, OnBtnbreak)
	ON_BN_CLICKED(IDC_BTNUPDATE, OnBtnupdate)
	ON_BN_CLICKED(IDC_BTNVARTABLE, OnBtnvartable)
	ON_BN_CLICKED(IDC_BUTTONADD, OnButtonadd)
	ON_BN_CLICKED(IDC_BUTTONDEL, OnButtondel)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTVARS, OnDblclkListvars)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPDlgDebug message handlers

void GPDlgDebug::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	AUSI.UpdateSize();
}

BOOL GPDlgDebug::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_RTFPrg=new CRichEditCtrl;
	m_RTFPrg->Create(ES_MULTILINE|ES_AUTOVSCROLL|ES_AUTOHSCROLL|ES_NOHIDESEL|ES_READONLY|WS_VISIBLE|WS_CHILD|WS_BORDER|WS_VSCROLL|WS_HSCROLL|WS_TABSTOP,CRect(2,3,490,205),this,IDC_RICHEDITPRG);

	AUSI.AddSetMain(this->m_hWnd);
	AUSI.AddWnd(m_btnAdd,this->m_hWnd	,"MNMN");
	AUSI.AddWnd(m_btnBreak,this->m_hWnd	,"NENE");
	AUSI.AddWnd(m_btnDel,this->m_hWnd	,"MNMN");
	AUSI.AddWnd(m_btnGo,this->m_hWnd	,"NENE");
	AUSI.AddWnd(m_chkAUpdate,this->m_hWnd	,"NENE");
	AUSI.AddWnd(m_btnUpdate,this->m_hWnd	,"NENE");
	AUSI.AddWnd(m_btnVarTable,this->m_hWnd	,"NENE");
	AUSI.AddWnd(m_EditNGO,this->m_hWnd	,"NENE");
	AUSI.AddWnd(m_EditNPrgLine,this->m_hWnd	,"NENE");
	AUSI.AddWnd(m_ListStack,this->m_hWnd	,"MNEN");
	AUSI.AddWnd(m_ListWatch,this->m_hWnd	,"MNEE");
	AUSI.AddWnd(m_statStack,this->m_hWnd	,"MNMN");
	AUSI.AddWnd(m_statWath,this->m_hWnd	,"MNMN");
	AUSI.AddWnd(m_RTFPrg->m_hWnd,this->m_hWnd	,"NNME");

	m_chkAUpdate.SetCheck(1);
	m_ListStack.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_ListStack.InsertColumn(0,"SubRoutine/Prg",LVCFMT_LEFT,140,0);
	m_ListStack.InsertColumn(1,"LN",LVCFMT_RIGHT,30,0);

	m_ListWatch.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_ListWatch.InsertColumn(0,"Variable",LVCFMT_LEFT,140,0);
	m_ListWatch.InsertColumn(1,"U",LVCFMT_RIGHT,30,0);
	m_ListWatch.InsertColumn(2,"Value",LVCFMT_RIGHT,200,0);

	m_EditNPrgLine.SetWindowText("5");
	SetTimer(1,2000,NULL);

	return TRUE;
}

void GPDlgDebug::OnTimer(UINT nIDEvent) 
{
	ModifyStyle(WS_DISABLED,0);
	CDialog::OnTimer(nIDEvent);
}

void GPDlgDebug::OnBtngo() 
{
	BeginWaitCursor();
	EnterCriticalSection(&GPC.m_View->m_CSInputSema);
	EnterCriticalSection(&GPC.m_View->m_CSRemap);
	try
	{
		CString tmpStr,SendStr;
		m_EditNGO.GetWindowText(tmpStr);
		SendStr="e"+tmpStr+"\r";
		BOOL fi=atoi(tmpStr)!=0;
		m_Comm.GPSendBlock(SendStr,SendStr.GetLength());
		Sleep(100);
		m_Comm.GPSendBlock("g\r",2);
		int cntbrk=0;
		char buff[100];
		if (m_chkAUpdate.GetCheck()!=0)
		{
			while(cntbrk<500)
			{
				if (m_Comm.GPRead(buff,1)>0)
				{
					if (*buff=='g')	
					{
						m_Comm.GPRead(buff,3);
						break;
					}

				}
				else	Sleep(50);
				cntbrk++;
			}
			if (fi) FillData();
		}
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPDlgDebug", "OnBtngo","");
	}
	LeaveCriticalSection(&GPC.m_View->m_CSRemap);
	LeaveCriticalSection(&GPC.m_View->m_CSInputSema);
	EndWaitCursor();
}

void GPDlgDebug::OnBtnbreak() 
{
	BeginWaitCursor();
	CString SendStr;
	EnterCriticalSection(&GPC.m_View->m_CSInputSema);
	EnterCriticalSection(&GPC.m_View->m_CSRemap);
	try
	{
		char tmpss[]={GPC.BreakChar,0};
		m_Comm.GPSendBlock(tmpss,1);
		Sleep(500);
		SendStr.Format("debug\r");
		m_Comm.GPSendBlock(SendStr,SendStr.GetLength());
		int cntbrk=0;
		char buff[100];
		while(cntbrk<500)
		{
			if (m_Comm.GPRead(buff,1)>0)
			{
				if (*buff=='!')
				{
					AfxMessageBox("Warning. Debuger in ! mode");
					cntbrk=123456;
					break;
				}
				if (*buff=='*')	
				{
					Sleep(100);
					while(m_Comm.GPRead(buff,95)>0);
					break;
				}

			}
			else	Sleep(10);
			cntbrk++;
		}
		if (cntbrk<500) FillData();
		else if (cntbrk!=123456) AfxMessageBox("No Debugger",MB_OK|MB_APPLMODAL|MB_ICONSTOP);
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPDlgDebug", "OnBtnbreak","");
	}
	LeaveCriticalSection(&GPC.m_View->m_CSRemap);
	LeaveCriticalSection(&GPC.m_View->m_CSInputSema);
	EndWaitCursor();
}

void GPDlgDebug::FillData()
{
	char buff[1000];
	char *tmpstr=new char [10000];
	*tmpstr=0;
	m_ListStack.DeleteAllItems();
	while(m_Comm.GPRead(buff,950)>0) Sleep(1);


	m_Comm.GPSendBlock("?\r",2);
	*buff=0;
	int cntr=0;
	do
	{
		if (m_Comm.GPRead(buff,1)<=0) Sleep(1);
		else	if (*buff==' ') break;
		cntr++;
	}
	while(cntr<5000);

	char *pos=tmpstr;
	cntr=0;
	do
	{
		if (m_Comm.GPRead(buff,1)<=0) *buff=1;
		else
			if (*buff!=13) {*(pos++)=*buff; cntr++;}
			else *(pos++)=0;
	}while(cntr<9900 && *buff!=13 && *buff!=10 && *buff!=0);


	char *postmp=tmpstr;
	while(*postmp==' ') postmp++;
	while(*postmp!=0 && *postmp!=' ') postmp++;
	if (*postmp!=0) *(postmp++)=0;
	while(*postmp!=0 && *postmp!=' ') postmp++;
	int nItem=-1;
	nItem=m_ListStack.InsertItem(100000,DosToAnsi(tmpstr));
	m_CurLine=atoi(postmp);
	sprintf(buff,"%d",m_CurLine);
	m_ListStack.SetItemText(nItem,1,buff);
	
	while(m_Comm.GPRead(buff,950)>0) Sleep(1);

	m_Comm.GPSendBlock("s\r",2);
	*buff=0;
	cntr=0;
	int cntr2=0;
	do
	{
		if (m_Comm.GPRead(buff,1)<=0) Sleep(1);
		if (*buff==' ') cntr2++;
		cntr++;
	}
	while(cntr2<2 && cntr<5000);

	pos=tmpstr;
	cntr2=0;
	cntr=0;
	do
	{
		if (m_Comm.GPRead(buff,1)<=0) {*buff=1;cntr2++;Sleep(10);}
		else
			if (*buff!=13) {*(pos++)=*buff; cntr++;}
			else *(pos++)=0;
	}while(cntr2<500 && cntr<9900 && *buff!=13 && *buff!=10 && *buff!=0);

	if (cntr2<500)
	{

		postmp=tmpstr;
		nItem=-1;
		while(*postmp!=0)
		{
			pos=postmp;
			while(*pos!=0 && *pos!=' ') pos++;
			
			if (*pos!=0 && pos[1]!=0 && pos[1]!=13 && pos[1]!=10 && (pos[1]!=' ' || (pos[1]==' ' && nItem<0)))
			{
				*(pos++)=0;
				if (*pos==' ') pos++;
				nItem=m_ListStack.InsertItem(100000,DosToAnsi(postmp));
			}
			else
			{
				if (*pos!=0)
				{
					*(pos++)=0;
					if (*pos==' ') pos++;
				}
				if (nItem>=0)
					m_ListStack.SetItemText(nItem,1,DosToAnsi(postmp));
			}
			postmp=pos;
		}


		CString tmpCTrr;
		m_EditNPrgLine.GetWindowText(tmpCTrr);
		int nDelta=atoi(tmpCTrr);
		while(m_Comm.GPRead(buff,950)>0) Sleep(1);

		tmpCTrr.Format("l%d-%d\r",m_CurLine-nDelta<=0?1:m_CurLine-nDelta,m_CurLine+nDelta);
		m_Comm.GPSendBlock(tmpCTrr,tmpCTrr.GetLength());

		m_RTFPrg->SetSel(0,-1);

		cntr=0;
		do
		{
			*buff=' ';
			if (m_Comm.GPRead(buff,1)<=0) Sleep(1);
			cntr++;
		}
		while(*buff>=' ' && cntr<5000);

		do
		{
			*buff=' ';
			if (m_Comm.GPRead(buff,1)<=0) Sleep(1);
			cntr++;
		}
		while(*buff<' ' && cntr<5000);

		int CRcnt=0;
		buff[1]=0;
		if (*buff>' ') m_RTFPrg->ReplaceSel(buff);

		do
			if (m_Comm.GPRead(buff,1)<=0) {Sleep(1);cntr++;}
			else
			{
				if (*buff==13) 	CRcnt++;
				if (*buff!=13 && *buff!=10 && *buff!=0)
				{
					if (CRcnt!=0) m_RTFPrg->ReplaceSel("\n");
					CRcnt=0;
					m_RTFPrg->ReplaceSel(DosToAnsi(buff));
				}
			}
		while(cntr<2000 && CRcnt<2);

		int nl=m_CurLine-nDelta<=0?m_CurLine:nDelta;
		m_RTFPrg->SetSel(m_RTFPrg->LineIndex(nl-7),m_RTFPrg->LineIndex(nl-6));
		m_RTFPrg->SetSel(m_RTFPrg->LineIndex(nl+7),m_RTFPrg->LineIndex(nl+8));
		m_RTFPrg->SetSel(m_RTFPrg->LineIndex(nl),m_RTFPrg->LineIndex(nl+1));
	}

	{
		int nWatch=m_ListWatch.GetItemCount();
		if (nWatch>0)
		{
			while(m_Comm.GPRead(buff,950)>0) Sleep(1);
			CString VarName;
			CString tmpCTrr;
			int i;
			for(i=0;i<nWatch;i++)
			{
				VarName=m_ListWatch.GetItemText(i,0);
				tmpCTrr="/"+VarName;
				AnsiToDos(tmpCTrr,tmpCTrr,0);
				m_Comm.GPSendBlock(tmpCTrr,tmpCTrr.GetLength());
				int cnt=0;
				while(m_Comm.GPRead(buff,950)<=0 && cnt<500) {Sleep(5);cnt++;}
				if (cnt>500) break;
				while(m_Comm.GPRead(buff,950)>0) Sleep(10);
				m_Comm.GPSendBlock("\r",1);
				*buff=0;
				cnt=0;
				int nRead=0;
				while((nRead=m_Comm.GPRead(buff,950))<=0 && cnt<500) {Sleep(5);cnt++;}
				if (cnt>500) break;
				cnt=0;
				while(*buff!=' ' && m_Comm.GPRead(buff,1)>0 && cnt<500) {Sleep(1);cnt++;}
				VarName="";cnt=0;
				if (cnt>500) break;
				do
				{
					buff[nRead]=0;
					VarName+=buff;
					*buff=0;
				}
				while((nRead=m_Comm.GPRead(buff,950))>0);
				if (VarName.GetLength()>0)	VarName.Delete(VarName.GetLength()-1,1);
				if (VarName.GetLength()>0)	VarName.Delete(0,1);
				DosToAnsi(VarName,VarName);
				m_ListWatch.SetItemText(i,2,VarName);
				m_Comm.GPSendBlock("\r",1);
				cnt=0;
				while(m_Comm.GPRead(buff,950)<=0 && cnt<500) {Sleep(50);cnt++;}
				if (cnt>500) break;
				while(m_Comm.GPRead(buff,950)>0) Sleep(10);
			}
		}
	}


	Sleep(50);
	while(m_Comm.GPRead(buff,950)>0) Sleep(100);


	delete[] tmpstr;
}

void GPDlgDebug::OnBtnupdate() 
{
	BeginWaitCursor();
	EnterCriticalSection(&GPC.m_View->m_CSInputSema);
	EnterCriticalSection(&GPC.m_View->m_CSRemap);
	try
	{
		FillData();
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPDlgDebug", "OnBtnupdate","");
	}
	LeaveCriticalSection(&GPC.m_View->m_CSRemap);
	LeaveCriticalSection(&GPC.m_View->m_CSInputSema);
	EndWaitCursor();
}

void GPDlgDebug::OnBtnvartable() 
{
	m_btnVarTable.ModifyStyle(0,WS_DISABLED);
	CGPDlgViewSTable dlg;
	dlg.DoModal();
	m_btnVarTable.ModifyStyle(WS_DISABLED,0);
}

void GPDlgDebug::OnButtonadd() 
{
	int Sel=m_ListWatch.GetSelectionMark();
	CString str;
	str=m_ListWatch.GetItemText(Sel,2);
	GPDlgNewValue dlg("AddItemDlg");
	if (dlg.DoModal()==IDOK)
		m_ListWatch.InsertItem(Sel+1,dlg.m_NewValue);
}

void GPDlgDebug::OnButtondel() 
{
	int Sel=0;
	while((Sel=m_ListWatch.GetNextItem(Sel-1,LVNI_SELECTED|LVNI_ALL))>=0)
		m_ListWatch.DeleteItem(Sel);
}


void GPDlgDebug::OnDblclkListvars(NMHDR* pNMHDR, LRESULT* pResult) 
{
	BeginWaitCursor();
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	if (lpnmitem)
	{
		CString str;
		str=m_ListWatch.GetItemText(lpnmitem->iItem,0);
		if (str!="")
		{
			str=m_ListWatch.GetItemText(lpnmitem->iItem,2);
			GPDlgNewValue dlg(str);
			if (dlg.DoModal()==IDOK && str!=dlg.m_NewValue)
			{
				EnterCriticalSection(&GPC.m_View->m_CSInputSema);
				EnterCriticalSection(&GPC.m_View->m_CSRemap);
				try
				{
					m_ListWatch.SetItemText(lpnmitem->iItem,2,dlg.m_NewValue);

					str="/"+m_ListWatch.GetItemText(lpnmitem->iItem,0)+"\r";
					AnsiToDos(str,str,0);
					m_Comm.GPSendBlock(str,str.GetLength());
					Sleep(250);
					str=dlg.m_NewValue+"\r";
					AnsiToDos(str,str,0);
					m_Comm.GPSendBlock(str,str.GetLength());
					int cnt=0;
					char buff[100];
					while(m_Comm.GPRead(buff,95)<=0 && cnt<500) {Sleep(50);cnt++;}
					while(m_Comm.GPRead(buff,95)>0) Sleep(10);
				}
				catch(...)
				{
					GPC.m_ErrReport.GPWriteErrorLog("GPDlgDebug", "OnDblclkListvars","");
				}
				LeaveCriticalSection(&GPC.m_View->m_CSRemap);
				LeaveCriticalSection(&GPC.m_View->m_CSInputSema);
			}
		}
	}
	*pResult = 0;
	EndWaitCursor();
}

BOOL GPDlgDebug::DestroyWindow() 
{
	return CDialog::DestroyWindow();
}
