// DlgClienFiles.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgClienFiles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgClientFiles dialog


CDlgClientFiles::CDlgClientFiles(GP_File **FileArr, UINT nFiles, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgClientFiles::IDD, pParent)
{
	EnableAutomation();
	m_FileArr=FileArr;
	m_nFiles=nFiles;

	//{{AFX_DATA_INIT(CDlgClientFiles)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CDlgClientFiles::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgClientFiles)
	DDX_Control(pDX, IDC_LIST1, m_FileList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgClientFiles, CDialog)
	//{{AFX_MSG_MAP(CDlgClientFiles)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgClientFiles message handlers

BOOL CDlgClientFiles::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetTimer(1,2000,NULL);

	AUSI.AddSetMain(this->m_hWnd);
	AUSI.AddWnd(m_FileList.m_hWnd,this->m_hWnd	,"NNEE");

	AUSI.SetMinSize(this->m_hWnd,270,150);

	m_FileList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_FileList.InsertColumn(0,"Id",LVCFMT_RIGHT,30,0);
	m_FileList.InsertColumn(1,"NAME",LVCFMT_LEFT,300,0);
	m_FileList.InsertColumn(2,"Mode",LVCFMT_LEFT,80,0);
	m_FileList.InsertColumn(3,"ATTR",LVCFMT_RIGHT,80,0);
	m_FileList.InsertColumn(4,"Position",LVCFMT_RIGHT,50,0);
	m_FileList.InsertColumn(5,"Length",LVCFMT_RIGHT,50,0);
	m_FileList.InsertColumn(6,"crTime",LVCFMT_RIGHT,120,0);
	m_FileList.InsertColumn(7,"modTime",LVCFMT_RIGHT,120,0);
	m_FileList.InsertColumn(8,"accTime",LVCFMT_RIGHT,120,0);

	char str[256];
	UINT i;
	for(i=0;i<m_nFiles;i++)
	{
		sprintf(str,"%d",i);
		m_FileList.InsertItem(i,str);
		UpdateFileInfo(i);
	}

	return TRUE;
}

void CDlgClientFiles::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	AUSI.UpdateSize();
}

void CDlgClientFiles::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);
	return;
	GetParent()->ModifyStyle(WS_DISABLED,0);
	ModifyStyle(WS_DISABLED,0);
	UINT i;
	for(i=0;i<m_nFiles;i++)
		try{UpdateFileInfo(i);}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("CDlgClientFiles", "OnTimer","130");
		}
}

void CDlgClientFiles::UpdateFileInfo(UINT nFile)
{
	if (nFile<m_nFiles)
	try
	{
		CFileStatus fst;
		if (m_FileArr[nFile]==NULL)
		{
			m_FileList.SetItemText(nFile,1,"");
			m_FileList.SetItemText(nFile,2,"CLOSE");
			m_FileList.SetItemText(nFile,3,"");
			m_FileList.SetItemText(nFile,4,"");
			m_FileList.SetItemText(nFile,5,"");
			m_FileList.SetItemText(nFile,6,"");
			m_FileList.SetItemText(nFile,7,"");
			m_FileList.SetItemText(nFile,8,"");
		}
		else
		{
			char str[256];
			m_FileArr[nFile]->GetStatus(fst);
			m_FileList.SetItemText(nFile,1,m_FileArr[nFile]->GetFileName());
			m_FileList.SetItemText(nFile,2,"OPEN");
			*str=0;
			if ((fst.m_attribute&0x01)==0) strcat(str,"R");
			if ((fst.m_attribute&0x02)!=0) strcat(str,"H");
			if ((fst.m_attribute&0x04)!=0) strcat(str,"S");
			if ((fst.m_attribute&0x08)!=0) strcat(str,"V");
			if ((fst.m_attribute&0x10)!=0) strcat(str,"D");
			if ((fst.m_attribute&0x20)!=0) strcat(str,"A");
			m_FileList.SetItemText(nFile,3,str);
			if (m_FileArr[nFile]->m_hFile != CFile::hFileNull)
			{
				sprintf(str,"%I64d",m_FileArr[nFile]->GetPosition());
				m_FileList.SetItemText(nFile,4,str);
			}
			sprintf(str,"%I64d",fst.m_size);
			m_FileList.SetItemText(nFile,5,str);
			m_FileList.SetItemText(nFile,6,fst.m_ctime.Format("%d.%m.%Y %H:%M:%S"));
			m_FileList.SetItemText(nFile,7,fst.m_mtime.Format("%d.%m.%Y %H:%M:%S"));
			m_FileList.SetItemText(nFile,8,fst.m_atime.Format("%d.%m.%Y %H:%M:%S"));
		}
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CDlgClientFiles", "UpdateFileInfo","179");
	}
}

void CDlgClientFiles::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	if (lpnmitem)
	{
		if ((UINT)lpnmitem->iItem<m_nFiles)
		{
			if (m_FileArr[lpnmitem->iItem]==NULL)
			{ //open
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
				*opf.lpstrFile=0;
				opf.nMaxFile =4900;
				opf.Flags =OFN_DONTADDTORECENT|OFN_CREATEPROMPT|OFN_ENABLESIZING|OFN_EXPLORER|OFN_NOCHANGEDIR|OFN_SHOWHELP;

				if (GetOpenFileName(&opf) && m_FileArr[lpnmitem->iItem]==NULL)
				{
					m_FileArr[lpnmitem->iItem]=new GP_File();
					m_FileArr[lpnmitem->iItem]->Open(opf.lpstrFile,CFile::modeReadWrite|CFile::shareDenyNone|CFile::typeBinary|CFile::modeCreate);
				}
				delete[] opf.lpstrFile;
			}
			else
			{ //close
				CString str;
#ifdef RUS
				str="Закрыть файл " + m_FileArr[lpnmitem->iItem]->GetFileName()+ " ?";
				if (MessageBox(str,"Закрытие файла",MB_ICONQUESTION|MB_APPLMODAL|MB_YESNO|MB_DEFBUTTON2)==IDYES && m_FileArr[lpnmitem->iItem])
#else
				str="Close file " + m_FileArr[lpnmitem->iItem]->GetFileName()+ " ?";
				if (MessageBox(str,"Closing file",MB_ICONQUESTION|MB_APPLMODAL|MB_YESNO|MB_DEFBUTTON2)==IDYES && m_FileArr[lpnmitem->iItem])
#endif
				{
					delete m_FileArr[lpnmitem->iItem];
					m_FileArr[lpnmitem->iItem]=NULL;
				}
			}
			UpdateFileInfo(lpnmitem->iItem);
		}
	}

	*pResult = 0;
}
