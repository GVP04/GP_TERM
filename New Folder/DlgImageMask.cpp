// DlgImageMask.cpp : implementation file
//

#include "stdafx.h"
#include "GP_Term.h"
#include "DlgImageMask.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgImageMask dialog


CDlgImageMask::CDlgImageMask(const GPImageList * iList, const char *iFiles, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgImageMask::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgImageMask)
	m_EdG = 0;
	m_EdB = 0;
	m_EdR = 0;
	//}}AFX_DATA_INIT
	Files=iFiles;
	IList=new GPImageList;
	*IList=*iList;
}

CDlgImageMask::~CDlgImageMask()
{
	if (IList) delete IList;
}

void CDlgImageMask::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgImageMask)
	DDX_Control(pDX, IDC_LIST2, m_List2);
	DDX_Control(pDX, IDC_SPIN3, m_SB);
	DDX_Control(pDX, IDC_SPIN2, m_SG);
	DDX_Control(pDX, IDC_SPIN1, m_SR);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Text(pDX, IDC_EDIT2, m_EdG);
	DDV_MinMaxUInt(pDX, m_EdG, 0, 255);
	DDX_Text(pDX, IDC_EDIT3, m_EdB);
	DDV_MinMaxUInt(pDX, m_EdB, 0, 255);
	DDX_Text(pDX, IDC_EDIT1, m_EdR);
	DDV_MinMaxUInt(pDX, m_EdR, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgImageMask, CDialog)
	//{{AFX_MSG_MAP(CDlgImageMask)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	ON_BN_CLICKED(IDC_OK, OnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgImageMask message handlers

void CDlgImageMask::OnChangeEdit1()
{
	FillList();
}

void CDlgImageMask::OnChangeEdit2()
{
	FillList();

}

void CDlgImageMask::OnChangeEdit3()
{
	FillList();

}

BOOL CDlgImageMask::OnInitDialog()
{
	CDialog::OnInitDialog();
	AutoSizing.AddSetMain(m_hWnd);
	AutoSizing.AddWnd(m_List.m_hWnd,m_hWnd,"NNEE");
	AutoSizing.AddWnd(GetDlgItem(IDC_EDIT1)->m_hWnd,m_hWnd,"ENEN");
	AutoSizing.AddWnd(GetDlgItem(IDC_EDIT2)->m_hWnd,m_hWnd,"ENEN");
	AutoSizing.AddWnd(GetDlgItem(IDC_EDIT3)->m_hWnd,m_hWnd,"ENEN");
	AutoSizing.AddWnd(GetDlgItem(IDC_STATICR)->m_hWnd,m_hWnd,"ENEN");
	AutoSizing.AddWnd(GetDlgItem(IDC_STATICG)->m_hWnd,m_hWnd,"ENEN");
	AutoSizing.AddWnd(GetDlgItem(IDC_STATICB)->m_hWnd,m_hWnd,"ENEN");
	AutoSizing.AddWnd(m_SR.m_hWnd,m_hWnd,"ENEN");
	AutoSizing.AddWnd(m_SG.m_hWnd,m_hWnd,"ENEN");
	AutoSizing.AddWnd(m_SB.m_hWnd,m_hWnd,"ENEN");
	AutoSizing.AddWnd(m_List2.m_hWnd,m_hWnd,"ENEE");
	AutoSizing.AddWnd(GetDlgItem(IDC_CANCEL)->m_hWnd,m_hWnd,"EEEE");
	AutoSizing.AddWnd(GetDlgItem(IDC_OK)->m_hWnd,m_hWnd,"EEEE");
	AutoSizing.SetMinSize(m_hWnd,500,400);

	m_SR.SetRange32(0,255);
	m_SG.SetRange32(0,255);
	m_SB.SetRange32(0,255);

	//m_List.ModifyStyle(LVS_ICON|LVS_REPORT|LVS_SMALLICON|LVS_LIST,LVS_ICON);

	FillList();

	return TRUE;
}

void CDlgImageMask::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (((nType)==SIZE_RESTORED || (nType)==SIZE_MAXIMIZED) && AutoSizing.GetItemCount()>0)
		AutoSizing.UpdateSize();

}

void CDlgImageMask::FillList()
{
	if (m_List.m_hWnd)
	{
		IList->m_IL.SetImageCount(0);
		m_List.DeleteAllItems();
		m_List2.SetBkColor(RGB(GetDlgItemInt(IDC_EDIT1),GetDlgItemInt(IDC_EDIT2),GetDlgItemInt(IDC_EDIT3)));
		m_List2.Invalidate();

		if (Files)
		{
			const char *pos=Files+(int)strlen(Files);
			if (*pos==0 && pos[1]==0)
				AddImg(Files);
			else
			{
				while(*(pos++));
				while(*pos)
				{
					AddImg(Files+CString("\\")+CString(pos));
					while(*(pos++));
				}
			}
		}

		m_List.SetImageList(&IList->m_IL, LVSIL_SMALL       );
		m_List.SetImageList(&IList->m_IL, LVSIL_STATE       );
		m_List.SetImageList(&IList->m_IL, LVSIL_NORMAL      );
		m_List.Invalidate();
	}
}

void CDlgImageMask::AddImg(CString flanme)
{
	if (/*(flanme.Find(".bmp",0)>0 || flanme.Find(".BMP",0)>0) &&*/ IList->m_IL.m_hImageList)
	{
		int m_CX=0;
		int m_CY=0;
		ImageList_GetIconSize(IList->m_IL.m_hImageList,&m_CX,&m_CY);
		if (IList->AddFromFile(flanme,0,m_List2.GetBkColor()))
		{
			int nItem=IList->m_IL.GetImageCount()-1;
			int pos=-1;
			int pos2;
			while((pos2=flanme.Find("\\",++pos))>=0)
				pos=pos2;

			if (nItem>=0)
			{
				char name[250];sprintf(name,"%4.4d - %s",nItem,(const char*)flanme.Right(flanme.GetLength()-pos));
				LVITEM lvi={0};
				lvi.mask=LVIF_IMAGE|LVIF_TEXT;
				lvi.iItem =nItem;
				lvi.iSubItem  =0;
				lvi.cchTextMax =4;
				lvi.pszText =name;
				lvi.iImage =nItem;

				m_List.InsertItem(&lvi);
			}
		}
	}
}

void CDlgImageMask::OnPaint()
{
	CPaintDC dc(this); // device context for painting
}


void CDlgImageMask::OnCancel()
{
	CDialog::OnCancel();
}

void CDlgImageMask::OnOk()
{
	CDialog::OnOK();
}

BOOL CDlgImageMask::OnCommand(WPARAM wParam, LPARAM lParam)
{
	BOOL TypeRet=TRUE;
	if (wParam!=1)
		TypeRet=FALSE;

	if (wParam==1)
	{
		HWND tmpf=::GetFocus();
		if (tmpf==::GetDlgItem(m_hWnd,IDC_OK))
		{
			CDialog::OnOK();
		}
		else
		{
			HWND tmpnext=::GetNextDlgTabItem(m_hWnd,tmpf,FALSE);
			if (tmpnext)
				GotoDlgCtrl(CWnd::FromHandle(tmpnext));
		}
	}
	return TypeRet?TRUE:CDialog::OnCommand(wParam, lParam);
}
