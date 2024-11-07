// DlgGraphCode.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgGraphCode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGraphCode dialog


CDlgGraphCode::CDlgGraphCode(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGraphCode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGraphCode)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgGraphCode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGraphCode)
	DDX_Control(pDX, IDC_LIST1, m_ListCurrent);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Control(pDX, IDC_LIST3, m_ListSample);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGraphCode, CDialog)
	//{{AFX_MSG_MAP(CDlgGraphCode)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST3, OnDblclkListChars)
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkListCurrent)
	ON_BN_CLICKED(IDC_BUTTON1, OnInvisibleStop)
	ON_BN_CLICKED(IDC_BUTTON6, OnVisibleStop)
	ON_BN_CLICKED(IDC_BUTTON8, OnInvisible)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGraphCode message handlers

BOOL CDlgGraphCode::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int i;
	CString sss=" ";
	LVITEMW litem={0}; 
	litem.mask=LVIF_TEXT|LVIF_PARAM;

	HDC m_HDC=::GetDC(GPC.m_hViewWnd);
	LOGFONT lf;
	if (m_HDC)
	{
		Graphics gr(m_HDC);
		FontTable.GetFont(0)->GetLogFontA(&gr,&lf);
	}
	lf.lfHeight=20;
	::ReleaseDC(GPC.m_hViewWnd,m_HDC);
	m_FontCpy.CreateFontIndirect(&lf);

	m_ListSample.SetFont(&m_FontCpy);
	::SendMessage(m_ListSample.m_hWnd,LVM_SETUNICODEFORMAT ,1,0);
 	::SendMessage(m_ListSample.m_hWnd,LVM_SETCOLUMNWIDTH,0,25);

	m_ListCurrent.SetFont(&m_FontCpy);
	::SendMessage(m_ListCurrent.m_hWnd,LVM_SETUNICODEFORMAT ,1,0);


	ShowWindow(SW_SHOW);
	m_ListCurrent.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_ListCurrent.InsertColumn(0,"code",LVCFMT_LEFT,100,0);
	m_ListCurrent.InsertColumn(1,"new",LVCFMT_LEFT,170,0);
	m_ListCurrent.InsertColumn(2,"current",LVCFMT_LEFT,170,0);


	for(i=0;i<256;i++)
	{
		sss.Format("%3.3d %c ",i,i);
		litem.pszText=sss.AllocSysString();
		litem.iSubItem=0;
		litem.lParam=GPC.dwGraphDecodeArray[i];
		litem.iItem=i;
		::SendMessageW(m_ListCurrent.m_hWnd,LVM_INSERTITEMW,i,(LPARAM)(&litem));
		::SysFreeString(litem.pszText);
		switch(GPC.dwGraphDecodeArray[i])
		{
		case 0xFFFF:
			sss="Inv stop";
			break;
		case 0xFFFE:
			sss="Vis stop";
			break;
		case 0xFFFD:
			sss="Invisible";
			break;
		default :
			sss.Format("%5.5d %c   ",GPC.dwGraphDecodeArray[i],GPC.dwGraphDecodeArray[i]);
			break;
		}
		litem.pszText=sss.AllocSysString();
		if (GPC.dwGraphDecodeArray[i]<0xFFFD) litem.pszText[6]=(WCHAR)(litem.lParam&0xFFFF);

		litem.iSubItem=1;
		::SendMessageW(m_ListCurrent.m_hWnd,LVM_SETITEMTEXTW,i,(LPARAM)(&litem));
		litem.iSubItem=2;
		::SendMessageW(m_ListCurrent.m_hWnd,LVM_SETITEMTEXTW,i,(LPARAM)(&litem));
		::SysFreeString(litem.pszText);
	}

	sss=" ";
	litem.pszText=sss.AllocSysString();
	
	m_Progress.SetRange(0,0x400);
	int nItems=0;
	litem.iSubItem=0;


	for(i=0; i<0x400; i++)
	{
		m_Progress.SetPos(i);
		DWORD j;
		BOOL isPresent=FALSE;
		BOOL bUseChar=FALSE;
		litem.pszText[0]=i*0x40+0x20;
		char buff[50];
		DWORD dwSuppCP=0;
		for(j=0;j<GPC.dwnCP && !isPresent;j++)
		{
			bUseChar=FALSE;
			*buff=0;
			isPresent=(WideCharToMultiByte( dwSuppCP=GPC.dwCodePages[j], WC_NO_BEST_FIT_CHARS, litem.pszText, 1, buff, 10, "`", &bUseChar) && !bUseChar && *buff && *buff!=' ');

		}

		if (isPresent)
			for(j=0;j<0x40;j++)
			{
				int k=i*0x40+j;
				bUseChar=FALSE;
				litem.pszText[0]=k;
				litem.iItem=nItems;
				litem.lParam=k;
				::SendMessageW(m_ListSample.m_hWnd,LVM_INSERTITEMW,nItems++,(LPARAM)(&litem));
			}
	}

	m_Progress.ModifyStyle(WS_VISIBLE,0);
	m_ListSample.ShowWindow(SW_SHOW);
	::SysFreeString(litem.pszText);

	::SendMessage(m_ListSample.m_hWnd,LVM_SETCOLUMNWIDTH ,0,LVSCW_AUTOSIZE);
	::SendMessage(m_ListCurrent.m_hWnd,LVM_SETCOLUMNWIDTH ,0,LVSCW_AUTOSIZE);
	::SendMessage(m_ListCurrent.m_hWnd,LVM_SETCOLUMNWIDTH ,1,LVSCW_AUTOSIZE);
	::SendMessage(m_ListCurrent.m_hWnd,LVM_SETCOLUMNWIDTH ,2,LVSCW_AUTOSIZE);

	::SendMessage(m_ListCurrent.m_hWnd,LVM_SETCOLUMNWIDTH ,0,LVSCW_AUTOSIZE);

	i=::SendMessage(m_ListCurrent.m_hWnd,LVM_GETCOLUMNWIDTH ,0,0);
	i+=::SendMessage(m_ListCurrent.m_hWnd,LVM_GETCOLUMNWIDTH ,1,0);
	i+=::SendMessage(m_ListCurrent.m_hWnd,LVM_GETCOLUMNWIDTH ,2,0);
	if (i>100)
	{
		CRect re;
		m_ListCurrent.GetWindowRect(&re);
		ScreenToClient(&re);
		i=re.right=re.left+i+20;
		m_ListCurrent.MoveWindow(re);
		m_ListSample.GetWindowRect(&re);
		ScreenToClient(&re);
		re.left=i+10;
		m_ListSample.MoveWindow(re);
	}

	AUSI.AddSetMain(this->m_hWnd);
	AUSI.AddWnd(m_ListCurrent.m_hWnd,this->m_hWnd	,"NNEN");
	AUSI.AddWnd(m_ListSample.m_hWnd,this->m_hWnd		,"NNEE");
	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDOK),this->m_hWnd		,"EEEE");
	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDCANCEL),this->m_hWnd		,"EEEE");
	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTON1),this->m_hWnd		,"ENEN");
	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTON6),this->m_hWnd		,"ENEN");
	AUSI.AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTON8),this->m_hWnd		,"ENEN");

	return TRUE;
}


void CDlgGraphCode::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	AUSI.UpdateSize();
}

void CDlgGraphCode::OnOK() 
{
	int i;
	for(i=0;i<256;i++)
		GPC.dwGraphDecodeArray[i]=m_ListCurrent.GetItemData(i);

	GPC.SaveGraphCodeco();

	CDialog::OnOK();
}

void CDlgGraphCode::OnCancel() 
{
	CDialog::OnCancel();
}

void CDlgGraphCode::OnDblclkListCurrent(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	if (lpnmitem)
	{
		LVFINDINFO fi={0};
		fi.flags=LVFI_PARAM;
		fi.lParam=m_ListCurrent.GetItemData(lpnmitem->iItem);
		int iFind=m_ListSample.FindItem(&fi);
		m_ListSample.EnsureVisible(iFind,FALSE);
		m_ListSample.SetItemState(iFind,LVIS_SELECTED,LVIS_SELECTED);
	}
	*pResult = 0;
}

void CDlgGraphCode::OnDblclkListChars(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	if (lpnmitem)
		SetUnicodeCharCode((unsigned short)m_ListSample.GetItemData(lpnmitem->iItem));

	*pResult = 0;
}


void CDlgGraphCode::OnInvisibleStop() 
{
	SetUnicodeCharCode(0xFFFF);
}

void CDlgGraphCode::OnVisibleStop() 
{
	SetUnicodeCharCode(0xFFFE);
}

void CDlgGraphCode::OnInvisible() 
{
	SetUnicodeCharCode(0xFFFD);
}


void CDlgGraphCode::SetUnicodeCharCode(unsigned short usCode)
{
	LVITEMW litem={0}; 
	POSITION pos = m_ListCurrent.GetFirstSelectedItemPosition();
	while(pos)
		if ((litem.iItem = m_ListCurrent.GetNextSelectedItem(pos))>=0)
		{
			CString sss;
			litem.mask=LVIF_TEXT;
			litem.iSubItem=1;
			litem.lParam=usCode;
			switch(usCode)
			{
			case 0xFFFF:
				sss="Inv stop";
				break;
			case 0xFFFE:
				sss="Vis stop";
				break;
			case 0xFFFD:
				sss="Invisible";
				break;
			default :
				sss.Format("%5.5d %c",usCode,usCode);
				break;
			}

			litem.pszText=sss.AllocSysString();
			if (usCode<0xFFFD) litem.pszText[6]=(WCHAR)(litem.lParam&0xFFFF);

			::SendMessageW(m_ListCurrent.m_hWnd,LVM_SETITEMTEXTW,litem.iItem,(LPARAM)(&litem));
			m_ListCurrent.SetItemData(litem.iItem,litem.lParam);
			::SysFreeString(litem.pszText);
		}
}

