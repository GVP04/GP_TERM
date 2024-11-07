// GPDlgCommtype.cpp : implementation file
//

#include "stdafx.h"
#include "GP_term.h"
#include "GPDlgCommtype.h"
#include "GP_TermView.h"
#include "GPDlgNewValue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPDlgCommtype dialog


GPDlgCommtype::GPDlgCommtype(CWnd* pParent /*=NULL*/)
	: CDialog(GPDlgCommtype::IDD, pParent)
{
	//{{AFX_DATA_INIT(GPDlgCommtype)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void GPDlgCommtype::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GPDlgCommtype)
	DDX_Control(pDX, IDC_LIST1, m_ListConnections);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GPDlgCommtype, CDialog)
	//{{AFX_MSG_MAP(GPDlgCommtype)
	ON_NOTIFY(LVN_DELETEALLITEMS, IDC_LIST1, OnDeleteallitemsList1)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST1, OnDeleteitemList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_WM_SIZE()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTONDELETE, OnButtondelete)
	ON_BN_CLICKED(IDC_BUTTONDEFAULT, OnButtondefault)
	ON_BN_CLICKED(IDC_BUTTONTEST, OnButtontest)
	ON_BN_CLICKED(IDC_BUTTONADDCOM, OnButtonaddcom)
	ON_BN_CLICKED(IDC_BUTTONADDSOCKET, OnButtonaddsocket)
	ON_BN_CLICKED(IDC_BUTTONADDCOPY, OnButtonaddcopy)
	ON_BN_CLICKED(IDC_BUTTONIMPORT, OnButtonimport)
	ON_BN_CLICKED(IDC_BUTTONEXPORT, OnButtonexport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPDlgCommtype message handlers

void GPDlgCommtype::OnOK() 
{
	AfxGetApp()->WriteProfileString(GPC.cs_RegTermViewSetName, "StartComm",cs_m_DefConnectionName);
	CString tmps;
	GetDlgItemText(IDC_EDITLISTENPORT,tmps);
	AfxGetApp()->WriteProfileInt(GPC.cs_RegTermViewSetName, "ListenPort",atoi(tmps));
	GetDlgItemText(IDC_EDITLISTENDELAY,tmps);
	AfxGetApp()->WriteProfileInt(GPC.cs_RegTermViewSetName, "ListenTime",atoi(tmps));
	CDialog::OnOK();
}

BOOL GPDlgCommtype::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CRect re;
	GetWindowRect(re);
	AUSI.AddSetMain(m_hWnd);
	AUSI.SetMinSize(m_hWnd,re.Width(),re.Height());
	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDC_LIST1)				,m_hWnd,"NNEE");

	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDOK)					,m_hWnd,"EEEE");
	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTONDELETE)		,m_hWnd,"EEEE");
	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTONADDCOM)		,m_hWnd,"EEEE");
	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTONADDSOCKET)	,m_hWnd,"EEEE");
	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTONIMPORT)		,m_hWnd,"EEEE");
	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTONADDCOPY)		,m_hWnd,"EEEE");
	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTONTEST)			,m_hWnd,"EEEE");

	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDC_STATICLISTENPORT)	,m_hWnd,"ENEN");
	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDC_STATICLISTENTIME)	,m_hWnd,"ENEN");
	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDC_EDITLISTENPORT)		,m_hWnd,"ENEN");
	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDC_EDITLISTENDELAY)	,m_hWnd,"ENEN");
	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTONDEFAULT)		,m_hWnd,"ENEN");
	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTONEXPORT)		,m_hWnd,"ENEN");

//cs_m_DefConnectionName="2";
	try
	{
		cs_m_DefConnectionName=AfxGetApp()->GetProfileString(GPC.cs_RegTermViewSetName, "StartComm","2");
	}
	catch(...)	{;}

	if (cs_m_DefConnectionName=="" || cs_m_DefConnectionName[0]<32)
	{
		cs_m_DefConnectionName.Format("%d",AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "StartComm",2));
		AfxGetApp()->WriteProfileString(GPC.cs_RegTermViewSetName, "StartComm",cs_m_DefConnectionName);
	}

	SetDlgItemInt(IDC_EDITLISTENPORT,AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "ListenPort",0),FALSE);
	SetDlgItemInt(IDC_EDITLISTENDELAY,AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "ListenTime",10),FALSE);

	m_ListConnections.ModifyStyle(0,LVS_SHOWSELALWAYS|LVS_SINGLESEL|LVS_SHAREIMAGELISTS);
	m_ListConnections.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);

	#ifdef RUS
		m_ListConnections.InsertColumn(0,"Наименование",LVCFMT_LEFT,110);
		m_ListConnections.InsertColumn(1,"Тип",LVCFMT_CENTER,60);
		m_ListConnections.InsertColumn(2,"Адрес",LVCFMT_CENTER,90);
		m_ListConnections.InsertColumn(3,"Порт",LVCFMT_CENTER,50);
		m_ListConnections.InsertColumn(4,"Telnet",LVCFMT_CENTER,47);
		m_ListConnections.InsertColumn(5,"SSH",LVCFMT_CENTER,50);
		m_ListConnections.InsertColumn(6,"Терминал",LVCFMT_CENTER,70);
		m_ListConnections.InsertColumn(7,"Описание соединения",LVCFMT_LEFT,100);
		m_ListConnections.InsertColumn(8,"Текст в меню",LVCFMT_LEFT,100);
		m_ListConnections.InsertColumn(9,"При подключении к серверу",LVCFMT_LEFT,150);
		m_ListConnections.InsertColumn(10,"При завершении сеанса",LVCFMT_LEFT,150);
	#else
		m_ListConnections.InsertColumn(0,"Connection Name",LVCFMT_LEFT,110);
		m_ListConnections.InsertColumn(1,"Type",LVCFMT_CENTER,60);
		m_ListConnections.InsertColumn(2,"Address",LVCFMT_CENTER,90);
		m_ListConnections.InsertColumn(3,"Port",LVCFMT_CENTER,50);
		m_ListConnections.InsertColumn(4,"Telnet",LVCFMT_CENTER,47);
		m_ListConnections.InsertColumn(5,"SSH",LVCFMT_CENTER,50);
		m_ListConnections.InsertColumn(6,"Terminal",LVCFMT_CENTER,70);
		m_ListConnections.InsertColumn(7,"Description",LVCFMT_LEFT,100);
		m_ListConnections.InsertColumn(8,"Menu Item",LVCFMT_LEFT,100);
		m_ListConnections.InsertColumn(9,"Login script",LVCFMT_LEFT,150);
		m_ListConnections.InsertColumn(10,"Logout script",LVCFMT_LEFT,150);
	#endif

	int ILnum=0;
	if ((ILnum=GPC.GetImageListId("MISCS"))>=0)
		m_ListConnections.SetImageList(&(GPC.a_GPImageList[ILnum].m_IL),LVSIL_SMALL);
	else
	{
		CString ssss;
		#ifdef BRIZ
			#ifdef RUS
				ssss="Отсутствует файл списков изображений IMAGELISTS\\MISCS.GIL. Пожалуйста, установите рабочую папку программы полностью.";
			#else
				ssss="There is no file of imagelists (IMAGELISTS\\MISCS.GIL). Please, setup BRIZ working folder completely.";
			#endif
		#else
			ssss="Отсутствует файл списков изображений IMAGELISTS\\MISCS.GIL. Пожалуйста, установите рабочую папку программы полностью.";
		#endif

		AfxMessageBox(ssss,MB_ICONEXCLAMATION|MB_APPLMODAL|MB_OK,0);
	}

	FillConnectionsList(ExtractField(m_Comm.GPSectionName,2,"\\"));
	return TRUE;
}

int GPDlgCommtype::AddListItem(const char *iName)
{
	GP_comm *tmpcomm=new GP_comm(0);

	tmpcomm->GPSectionName.Format("COMSETLIST\\%s",iName);
	tmpcomm->load_dcb(TRUE);
	
	int iItem=m_ListConnections.InsertItem(m_ListConnections.GetItemCount(),iName);
	m_ListConnections.SetItemData(iItem,(DWORD)tmpcomm);

	return iItem;
}

void GPDlgCommtype::OnDeleteallitemsList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nItems=m_ListConnections.GetItemCount();
	int i;
	for(i=0;i<nItems;i++)
	{
		GP_comm *tmp=(GP_comm *)m_ListConnections.GetItemData(i);
		if (tmp)
		{
			m_ListConnections.SetItemData(i,NULL);
			delete[] tmp;
			tmp=NULL;
		}
	}
	*pResult = 0;
}

void GPDlgCommtype::OnDeleteitemList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView)
	{
		GP_comm *tmp=(GP_comm *)m_ListConnections.GetItemData(pNMListView->iItem);
		if (tmp)
		{
			m_ListConnections.SetItemData(pNMListView->iItem,NULL);
			delete[] tmp;
			tmp=NULL;
		}
	}
	*pResult = 0;
}

void GPDlgCommtype::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	if (lpnmitem)
	{
		GP_comm *tmpcommS=(GP_comm *)m_ListConnections.GetItemData(lpnmitem->iItem);
		if (tmpcommS)
		{
			GP_comm *tmpcomm=new GP_comm(0);
			tmpcomm->GPSectionName=tmpcommS->GPSectionName;
			tmpcomm->load_dcb(TRUE);
			int res=IDCANCEL;
			switch(tmpcomm->Get_commType())
			{
			case GPCT_COMPORT:
				{
					CComPortSetings	dlg(tmpcomm);
					res=dlg.DoModal();
				}
				break;
			case GPCT_SOCKET:
				{
					GPDlgTelnetSet	dlg(tmpcomm);
					res=dlg.DoModal();
				}
				break;
			}
			if (res==IDOK)
			{
				CString csLastSection=ExtractField(tmpcomm->GPSectionName,2,"\\");
				FillConnectionsList(csLastSection);
			}
			delete tmpcomm;
		}
	}	
	*pResult = 0;
}

void GPDlgCommtype::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	AUSI.UpdateSize();
}

void GPDlgCommtype::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if ((pNMListView->uNewState&LVIS_SELECTED)==LVIS_SELECTED)
	{
		EnableUIObjects(TRUE);
	}

	if ((pNMListView->uOldState&LVIS_SELECTED)==LVIS_SELECTED && (pNMListView->uNewState&LVIS_SELECTED)!=LVIS_SELECTED)
	{
		EnableUIObjects(FALSE);
	}

	*pResult = 0;
}

void GPDlgCommtype::EnableUIObjects(BOOL m_bEnabled)
{
	::EnableWindow(::GetDlgItem(m_hWnd,IDC_BUTTONADDCOPY)	,m_bEnabled);
	::EnableWindow(::GetDlgItem(m_hWnd,IDC_BUTTONEXPORT)	,m_bEnabled);
	::EnableWindow(::GetDlgItem(m_hWnd,IDC_BUTTONDELETE)	,m_bEnabled);
	::EnableWindow(::GetDlgItem(m_hWnd,IDC_BUTTONADDCOPY)	,m_bEnabled);
	::EnableWindow(::GetDlgItem(m_hWnd,IDC_BUTTONDEFAULT)	,m_bEnabled);
	::EnableWindow(::GetDlgItem(m_hWnd,IDC_BUTTONTEST)		,m_bEnabled);
}

void GPDlgCommtype::OnButtondelete() 
{
	POSITION posit = m_ListConnections.GetFirstSelectedItemPosition();
	if (posit)
	{
		int iItem = m_ListConnections.GetNextSelectedItem(posit);
		GP_comm *tmpcomm=(GP_comm *)m_ListConnections.GetItemData(iItem);
		if (tmpcomm)
		{
			CString csTmpName;
			csTmpName.Format("Delete connection - %s ?", ExtractField(tmpcomm->GPSectionName,2,"\\"));
			if (AfxMessageBox(csTmpName,MB_ICONQUESTION|MB_APPLMODAL|MB_OKCANCEL,0)==IDOK)
			{
				HKEY tmpKew=NULL;
				csTmpName.Format("Software\\%s\\%s\\COMSETLIST",AfxGetApp()->m_pszRegistryKey,AfxGetApp()->m_pszAppName);
				::RegOpenKeyEx(HKEY_CURRENT_USER,csTmpName,0,KEY_ALL_ACCESS,&tmpKew);
				if (tmpKew) 
				{
					RegDeleteKey(tmpKew,ExtractField(tmpcomm->GPSectionName,2,"\\"));
					RegCloseKey(tmpKew);
					if (cs_m_DefConnectionName==ExtractField(tmpcomm->GPSectionName,2,"\\")) cs_m_DefConnectionName="";
				}
				m_ListConnections.DeleteItem(iItem);
				EnableUIObjects(FALSE);
			}
		}
	}
	DefineDefaultItem();
}

void GPDlgCommtype::OnButtondefault() 
{
	POSITION posit = m_ListConnections.GetFirstSelectedItemPosition();
	if (posit)
	{
		int iItem = m_ListConnections.GetNextSelectedItem(posit);
		GP_comm *tmpcomm=(GP_comm *)m_ListConnections.GetItemData(iItem);
		if (tmpcomm) cs_m_DefConnectionName=ExtractField(tmpcomm->GPSectionName,2,"\\");
	}
	DefineDefaultItem();
}

int GPDlgCommtype::UpdateListItem(int iItem)
{
	int mStart=iItem,mEnd=iItem+1;

	if (iItem==-123456)
	{
		mStart=0,mEnd=m_ListConnections.GetItemCount();
	}
	else
		if (iItem<0 || iItem>=m_ListConnections.GetItemCount())
		{
			mEnd=-1;mStart=0;
			POSITION posit = m_ListConnections.GetFirstSelectedItemPosition();
			if (posit)
			{
				iItem = m_ListConnections.GetNextSelectedItem(posit);
				mStart=iItem;
				mEnd=iItem+1;
			}
		}

	for(iItem=mStart;iItem<mEnd;iItem++)
	{
		GP_comm *tmpcomm=(GP_comm *)m_ListConnections.GetItemData(iItem);
		if (tmpcomm)
		{
			CString csTmp;
			if (tmpcomm->Get_commType()==GPCT_COMPORT)
			{
				m_ListConnections.SetItemText(iItem,1,"COM");
				m_ListConnections.SetItemText(iItem,2,tmpcomm->GetComport());
			}
			else
			{
				m_ListConnections.SetItemText(iItem,1,"Socket");
				m_ListConnections.SetItemText(iItem,2,tmpcomm->GPGetHostName());
				csTmp.Format("%d",tmpcomm->GetPortNumber());
				m_ListConnections.SetItemText(iItem,3,csTmp);

				csTmp.Format("%d",tmpcomm->dwUseSSH);
				m_ListConnections.SetItemText(iItem,5,csTmp);

			}
			m_ListConnections.SetItem(iItem,0,LVIF_IMAGE,NULL,cs_m_DefConnectionName==ExtractField(tmpcomm->GPSectionName,2,"\\")?4:-1,0,0,(DWORD)tmpcomm);

			m_ListConnections.SetItemText(iItem,4,tmpcomm->GetTelnetFlag()==0?"":"Y");
			
			m_ListConnections.SetItemText(iItem,6,m_TermCap.GetTerminalNameById(tmpcomm->m_TerminalID));

			m_ListConnections.SetItemText(iItem,7,AfxGetApp()->GetProfileString(tmpcomm->GPSectionName, "TERMTITLE",""));
			m_ListConnections.SetItemText(iItem,8,tmpcomm->GetComment());
			m_ListConnections.SetItemText(iItem,9,tmpcomm->GetInitStr());
			m_ListConnections.SetItemText(iItem,10,tmpcomm->GetEndStr());
		}
		else
		{
			int i;
			for(i=1;i<11;i++)
				m_ListConnections.SetItemText(iItem,i,"");
		}
	}

	return iItem;
}
int GPDlgCommtype::UpdateListItem(const char *iName)
{
	int i,nItems=m_ListConnections.GetItemCount();
	int ret=-1;
	if (iName && *iName)
	for(i=0;i<nItems && ret<0;i++)
		if (m_ListConnections.GetItemText(i,0)==iName) 
			ret=UpdateListItem(i);
	return 0;
}


int GPDlgCommtype::FillConnectionsList(const char *ccSelection)
{
	int ret=-1;
	m_ListConnections.DeleteAllItems();
	HKEY curKey=NULL;
	char cListKey[200];
	sprintf(cListKey,"Software\\%s\\%s\\COMSETLIST",AfxGetApp()->m_pszRegistryKey,AfxGetApp()->m_pszAppName);
	::RegOpenKeyEx(HKEY_CURRENT_USER,cListKey,0,KEY_ALL_ACCESS,&curKey);
	if (curKey)
	{
		char skName[510];
		char nmClass[256];
		int i=0;
		*skName=0;
		*nmClass=0;
		DWORD lenName=480;
		DWORD lenClass=250;
		FILETIME ft={0};
		while(RegEnumKeyEx(curKey,i++,skName,&lenName,NULL,nmClass,&lenClass,&ft)!=ERROR_NO_MORE_ITEMS)
		{
			skName[lenName]=0;
			nmClass[lenClass]=0;
			
			int iItem=AddListItem(skName);
			UpdateListItem(iItem);
			if (strcmp(skName,ccSelection)==0)
				m_ListConnections.SetItemState(ret=iItem,LVIS_SELECTED,LVIS_SELECTED);

			lenName=480;
			lenClass=250;
		}

		RegCloseKey(curKey);
		curKey=NULL;
	}
	EnableUIObjects(ret>=0);

	return ret;
}

int GPDlgCommtype::DefineDefaultItem()
{
	int ret=-1,nItems=m_ListConnections.GetItemCount();
	int i;
	if (cs_m_DefConnectionName=="" && nItems>0)
	{
		GP_comm *tmpcomm=(GP_comm *)m_ListConnections.GetItemData(0);
		if (tmpcomm) cs_m_DefConnectionName=ExtractField(tmpcomm->GPSectionName,2,"\\");
	}

	for(i=0;i<nItems;i++)
	{
		GP_comm *tmpcomm=(GP_comm *)m_ListConnections.GetItemData(i);
		if (tmpcomm)
			m_ListConnections.SetItem(i,0,LVIF_IMAGE,NULL,cs_m_DefConnectionName==ExtractField(tmpcomm->GPSectionName,2,"\\")?4:-1,0,0,(DWORD)tmpcomm);
	}

	return ret;
}

void GPDlgCommtype::OnButtonaddcom() 
{
	int res=IDCANCEL;
	GP_comm *tmpcomm=new GP_comm(0);
	tmpcomm->Set_commType(GPCT_COMPORT);
	tmpcomm->GPSectionName="COMSETLIST\\New_comport";
	tmpcomm->load_dcb(TRUE);
	CComPortSetings	dlg(tmpcomm);
	res=dlg.DoModal();
	if (tmpcomm)
	{
		ChechAndDelete("New_comport");
		FillConnectionsList(ExtractField(tmpcomm->GPSectionName,2,"\\"));
		delete tmpcomm;
	}
}

void GPDlgCommtype::OnButtonaddsocket() 
{
	int res=IDCANCEL;
	GP_comm *tmpcomm=new GP_comm(0);
	tmpcomm->GPSectionName="COMSETLIST\\New_socket";
	tmpcomm->Set_commType(GPCT_SOCKET);
	tmpcomm->load_dcb(TRUE);
	GPDlgTelnetSet	dlg(tmpcomm);
	res=dlg.DoModal();
	if (tmpcomm)
	{
		ChechAndDelete("New_comport");
		FillConnectionsList(ExtractField(tmpcomm->GPSectionName,2,"\\"));
		delete tmpcomm;
	}
}

void GPDlgCommtype::OnButtonaddcopy() 
{
	POSITION posit = m_ListConnections.GetFirstSelectedItemPosition();
	if (posit)
	{
		int iItem = m_ListConnections.GetNextSelectedItem(posit);
		GP_comm *tmpcommS=(GP_comm *)m_ListConnections.GetItemData(iItem);
		if (tmpcommS)
		{
			int res=IDCANCEL;
			GP_comm *tmpcomm=new GP_comm(0);
			tmpcomm->GPSectionName=tmpcommS->GPSectionName;
			tmpcomm->load_dcb(TRUE);
			tmpcomm->GPSectionName.Replace("\\","\\Copy_");
			switch(tmpcomm->Get_commType())
			{
			case GPCT_COMPORT:
				{
					CComPortSetings	dlg(tmpcomm);
					res=dlg.DoModal();
				}
				break;
			case GPCT_SOCKET:
				{
					GPDlgTelnetSet	dlg(tmpcomm);
					res=dlg.DoModal();
				}
				break;
			}
			if (res==IDOK)
			{
				CString csLastSection=ExtractField(tmpcomm->GPSectionName,2,"\\");
				FillConnectionsList(csLastSection);
			}
			delete tmpcomm;
		}
	}	
}

BOOL GPDlgCommtype::ChechAndDelete(const char *CommKeName)
{
	return GP_comm::ChechAndDelete(CommKeName);
}

void GPDlgCommtype::OnButtonimport() 
{
	GPDlgNewValue dlg("new_connection");
	if (dlg.DoModal()==IDOK)
	{
		OPENFILENAME opf={0};
		#ifdef W_95
			opf.lStructSize=OPENFILENAME_SIZE_VERSION_400;
		#else
			#ifdef W_NT
				opf.lStructSize=OPENFILENAME_SIZE_VERSION_400;
			#else
				opf.lStructSize=sizeof(OPENFILENAME);
			#endif
		#endif
		opf.hwndOwner=m_hWnd;
		opf.lpstrFile = new char [5000];
		strcpy(opf.lpstrFile,csOldFileName);
		opf.nMaxFile =4900;
		opf.Flags =OFN_DONTADDTORECENT|OFN_HIDEREADONLY|OFN_ENABLESIZING|OFN_EXPLORER|OFN_FILEMUSTEXIST|OFN_LONGNAMES|OFN_NOCHANGEDIR|OFN_PATHMUSTEXIST|OFN_NOCHANGEDIR|OFN_SHOWHELP;
		#ifdef RUS
			opf.lpstrFilter="Файл раздела системного реестра (*.reg)\x0*.reg\x0";
			opf.lpstrTitle="Импорт описания соединения";
		#else
			opf.lpstrFilter="System registry file(*.reg)\x0*.reg\x0";
			opf.lpstrTitle="Import connection";
		#endif

		opf.lpstrDefExt="reg";
		if (GetOpenFileName(&opf))
		{
			csOldFileName=opf.lpstrFile;
			CString ssss;
			ssss.Format("Software\\%s\\%s\\COMSETLIST\\%s",AfxGetApp()->m_pszRegistryKey,AfxGetApp()->m_pszAppName,dlg.m_NewValue);
			ImportRegistryKey(ssss,csOldFileName);
			FillConnectionsList(dlg.m_NewValue);
		}
		delete[] opf.lpstrFile;
	}
}

void GPDlgCommtype::OnButtonexport() 
{
	POSITION posit = m_ListConnections.GetFirstSelectedItemPosition();
	if (posit)
	{
		int iItem = m_ListConnections.GetNextSelectedItem(posit);
		GP_comm *tmpcommS=(GP_comm *)m_ListConnections.GetItemData(iItem);
		if (tmpcommS)
		{
			CString ssss;
			ssss.Format("Software\\%s\\%s\\%s",AfxGetApp()->m_pszRegistryKey,AfxGetApp()->m_pszAppName,tmpcommS->GPSectionName);

			OPENFILENAME opf={0};
			#ifdef W_95
				opf.lStructSize=OPENFILENAME_SIZE_VERSION_400;
			#else
				#ifdef W_NT
					opf.lStructSize=OPENFILENAME_SIZE_VERSION_400;
				#else
					opf.lStructSize=sizeof(OPENFILENAME);
				#endif
			#endif
			opf.hwndOwner=m_hWnd;
			opf.lpstrFile = new char [5000];
			strcpy(opf.lpstrFile,csOldFileName);
			opf.nMaxFile =4900;
			opf.Flags =OFN_DONTADDTORECENT|OFN_HIDEREADONLY|OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_PATHMUSTEXIST|OFN_NOCHANGEDIR|OFN_SHOWHELP;
			#ifdef RUS
				opf.lpstrFilter="Файл раздела системного реестра (*.reg)\x0*.reg\x0";
				opf.lpstrTitle="Экспорт описания соединения";
			#else
				opf.lpstrFilter="System registry file(*.reg)\x0*.reg\x0";
				opf.lpstrTitle="Export connection";
			#endif
			opf.lpstrDefExt="reg";

			if (GetSaveFileName(&opf))
			{
				csOldFileName=opf.lpstrFile;
				ExportRegistryKey(ssss , csOldFileName);
			}
			delete[] opf.lpstrFile;
		}
	}
}

void GPDlgCommtype::OnButtontest() 
{
	POSITION posit = m_ListConnections.GetFirstSelectedItemPosition();
	if (posit)
	{
		int iItem = m_ListConnections.GetNextSelectedItem(posit);
		CString sectionName=m_ListConnections.GetItemText(iItem,0);
		if (sectionName!="")
		{
			CString csCommand="-COMMNUM"+sectionName;
			#ifdef BRIZ
				_spawnlp(_P_NOWAIT,"BRIZ.exe","BRIZ.exe",csCommand,NULL);
			#else
				_spawnlp(_P_NOWAIT,"GP_term.exe","GP_term.exe",csCommand,NULL);
			#endif
		}
	}
}

