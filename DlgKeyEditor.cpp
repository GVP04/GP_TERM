// DlgKeyEditor.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgKeyEditor.h"
#include "GP_HotKey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgKeyEditor dialog
int CALLBACK LockKeyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	int col=lParamSort&0xFFFF;
	int ret=0;
	switch(col)
	{
	case 0:
		ret=(lParam1&0x1000)-(lParam2&0x1000);
		break;
	case 1:
	case 2:
	case 3:
	case 4:
		ret=(lParam1&GP_HotKey::aVKMODUINT[col-1])-(lParam2&GP_HotKey::aVKMODUINT[col-1]);
		break;
	case 5:
		ret=strcmp(GP_HotKey::GetKeyName(lParam1),GP_HotKey::GetKeyName(lParam2));
		break;
	}

	int i;
	for(i=5;i>=0 && ret==0;i--)
		if (i!=col)
			switch(i)
			{
			case 0:
				ret=(lParam1&0x1000)-(lParam2&0x1000);
				break;
			case 1:
			case 2:
			case 3:
			case 4:
				ret=(lParam1&GP_HotKey::aVKMODUINT[i-1])-(lParam2&GP_HotKey::aVKMODUINT[i-1]);
				break;
			case 5:
				ret=strcmp(GP_HotKey::GetKeyName(lParam1),GP_HotKey::GetKeyName(lParam2));
				break;
			}

	return lParamSort&0xFFFF0000?-ret:ret;
}


CDlgKeyEditor::CDlgKeyEditor(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKeyEditor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgKeyEditor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	DlgAutoSize=NULL;
	m_FileName="SVOLockKeys.txt";
	m_SortFlag=0;
}


CDlgKeyEditor::~CDlgKeyEditor()
{
	if (DlgAutoSize)
		delete DlgAutoSize;
	DlgAutoSize=NULL;
}


void CDlgKeyEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKeyEditor)
	DDX_Control(pDX, IDC_COMBO1, m_ComboKey);
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgKeyEditor, CDialog)
	//{{AFX_MSG_MAP(CDlgKeyEditor)
	ON_BN_CLICKED(IDC_BUTTONOK, OnButtonOk)
	ON_BN_CLICKED(IDC_BUTTONCANCEL, OnButtonCancel)
	ON_BN_CLICKED(IDC_BUTTONDEL, OnButtondel)
	ON_BN_CLICKED(IDC_BUTTONADD, OnButtonadd)
	ON_CBN_CLOSEUP(IDC_COMBO1, OnCloseupComboKey)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickListKeys)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, OnColumnclickListKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgKeyEditor message handlers

void CDlgKeyEditor::OnButtonCancel()
{
	CDialog::OnCancel();
}

void CDlgKeyEditor::OnButtonOk()
{
	int nItems=m_List.GetItemCount();
	if (m_FileName!="" && nItems)
	{
		FILE *fl=fopen(m_FileName,"wt");
		if (fl)
		{
			char str[500];
			int i;
			for(i=0;i<nItems;i++)
			{
				DWORD key=m_List.GetItemData(i);
				str[0]='-';
				str[1]=',';
				str[2]=0;
				if ((key&0x1000)) str[0]='+';
				key&=(0xFFFFFFFF^0x1000);
				GP_HotKey::StringFromToHotKey(str+2,key);
				strcat(str,"\n");
				fputs(str,fl);
			}
			fclose(fl);
		}
	}

	CDialog::OnOK();
}

void CDlgKeyEditor::OnButtondel()
{
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if (pos)
	{
	  int nItem = m_List.GetNextSelectedItem(pos);
	  if (nItem>=0) m_List.DeleteItem(nItem);
	}
}

void CDlgKeyEditor::OnButtonadd()
{
	int nItem=m_List.InsertItem(10000,"");
	m_List.EnsureVisible(nItem,FALSE);
	if (nItem>=0)
		UpdateListItem(nItem,0x1000+VK_NONAME*0x10000);
}

void CDlgKeyEditor::OnCloseupComboKey()
{
	m_ComboKey.ShowWindow(SW_HIDE);
	int sel=m_ComboKey.GetCurSel();
	if (sel!=CB_ERR)
	{
		CString txt;
		m_ComboKey.GetLBText(sel,txt);
		POSITION pos = m_List.GetFirstSelectedItemPosition();
		if (pos)
		{
			int nItem = m_List.GetNextSelectedItem(pos);
			if (nItem>=0)
			{
				m_List.SetItemText(nItem,5,txt);
				DWORD key=m_List.GetItemData(nItem),tmpkey=0;
				txt+="|";
				key=(key&0x0000FFFF)+GP_HotKey::StringFromToHotKey(txt,tmpkey);
				m_List.SetItemData(nItem,key);
			}
		}
	}
}

void CDlgKeyEditor::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (DlgAutoSize)
		try{DlgAutoSize->UpdateSize();}catch(...){			GPC.m_ErrReport.GPWriteErrorLog("CDlgKeyEditor", "OnSize","188");}
}

BOOL CDlgKeyEditor::OnInitDialog()
{
	CDialog::OnInitDialog();

	DlgAutoSize=new GP_AutoSizing;
	DlgAutoSize->AddSetMain(this->m_hWnd);
	DlgAutoSize->SetMinSize(this->m_hWnd,200,150);

	m_List.SetExtendedStyle(LVS_EX_SUBITEMIMAGES|LVS_EX_GRIDLINES);
	m_List.InsertColumn(0,"v",LVCFMT_LEFT,18,0);
	m_List.InsertColumn(1,"Alt",LVCFMT_LEFT,25,0);
	m_List.InsertColumn(2,"Ctrl",LVCFMT_LEFT,27,0);
	m_List.InsertColumn(3,"Shif",LVCFMT_LEFT,30,0);
	m_List.InsertColumn(4,"Win",LVCFMT_LEFT,35,0);
	m_List.InsertColumn(5,"Key",LVCFMT_LEFT,250,0);
	m_List.GetHeaderCtrl()->ModifyStyle(0,HDS_BUTTONS);
	m_List.SetImageList(&GPC.a_GPImageList[GPC.GetImageListId("MISCS")].m_IL,LVSIL_SMALL);

	DlgAutoSize->AddWnd(m_List.m_hWnd,this->m_hWnd,"NNEE");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTONOK),this->m_hWnd,"EEEE");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTONCANCEL),this->m_hWnd,"EEEE");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTONDEL),this->m_hWnd,"NENE");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTONADD),this->m_hWnd,"NENE");

	if (m_FileName!="")
	{
		FILE *fl=fopen(m_FileName,"rt");
		if (fl)
		{
			char str[500];
			int nItems=0;
			while(fgets(str,490,fl))
			{
				DWORD hotkey=0;
				strcat(str,"|");
				GP_HotKey::StringFromToHotKey(str,hotkey);
				if (*str=='+')
					hotkey|=0x1000;
	
				if ((hotkey&0xFFFF0000))
				{
					int itm=m_List.InsertItem(nItems++,"");
					UpdateListItem(itm,hotkey);
				}
			}
			fclose(fl);
		}
	}

	m_ComboKey.ResetContent();
	UINT i;
	char tmpstr[200];

	for(i=0;i<GP_HotKey::nTypeHotkey;i++)
	{
		strcpy(tmpstr,GP_HotKey::aVKName[i]);
		char *tmppos=strchr(tmpstr,'|');
		if (tmppos) *tmppos=0;
		m_ComboKey.AddString(tmpstr);
	}

	return TRUE;
}

LRESULT CDlgKeyEditor::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	return CDialog::WindowProc(message, wParam, lParam);
}

BOOL CDlgKeyEditor::OnCommand(WPARAM wParam, LPARAM lParam)
{
	BOOL TypeRet=TRUE;
	if (wParam==1  || wParam==2) TypeRet=FALSE;

	return TypeRet?CDialog::OnCommand(wParam, lParam):TRUE;
}

void CDlgKeyEditor::OnDestroy()
{
	if (DlgAutoSize)
		delete DlgAutoSize;

	DlgAutoSize=NULL;

	CDialog::OnDestroy();
}

void CDlgKeyEditor::UpdateListItem(int iItem, DWORD iKey)
{
	m_List.SetItemData(iItem,iKey);

	LVITEM it={0};
	it.mask=LVIF_IMAGE|LVIF_TEXT;
	it.pszText="";
	it.iItem=iItem;

	it.iImage=((iKey&0x1000)!=0x1000)?100:4;
	m_List.SetItem(&it);

	int j;
	for(j=0;j<4;j++)
	{
		it.iImage=((iKey&GP_HotKey::aVKMODUINT[j])==GP_HotKey::aVKMODUINT[j])*2+38;
		it.iSubItem++;
		m_List.SetItem(&it);
	}

	char str[500];
	*str=0;
	iKey&=0xFFFF0000;
	GP_HotKey::StringFromToHotKey(str,iKey);
	char *tmppos=strchr(str,'|');
	if (tmppos) *tmppos=0;
	it.pszText=str;
	it.iImage=-1;
	it.iSubItem++;
	m_List.SetItem(&it);

}

void CDlgKeyEditor::OnClickListKeys(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE nmItem=(LPNMITEMACTIVATE)pNMHDR;
	if (nmItem)
	{
		if (nmItem->iItem<0)
		{
			LVHITTESTINFO ht={0};
			DWORD pos=::GetMessagePos();
			ht.pt.x=(int)(short)LOWORD(pos);
			ht.pt.y=(int)(short)HIWORD(pos);
			::ScreenToClient(m_List.m_hWnd,&(ht.pt));
			m_List.SubItemHitTest(&ht);
			nmItem->iItem=ht.iItem;
			nmItem->iSubItem=ht.iSubItem;
		}


		if (nmItem->iItem>=0)
		{
			m_List.SetItemState(nmItem->iItem,LVIS_SELECTED,LVIS_SELECTED);
			m_List.Invalidate();
			LVITEM it={0};
			it.mask=LVIF_IMAGE;
			it.iItem=nmItem->iItem;
			it.iSubItem=nmItem->iSubItem;
			m_List.GetItem(&it);
			DWORD tmpKey=m_List.GetItemData(it.iItem);

			switch(it.iSubItem)
			{
			case 0:
				it.iImage=(it.iImage==4)?1000:4;
				tmpKey&=(0xFFFFFFFF^0x1000);
				if (it.iImage==4) tmpKey|=0x1000;
				m_List.SetItem(&it);
				m_List.SetItemData(it.iItem,tmpKey);
				break;
			case 1:
			case 2:
			case 3:
			case 4:
				it.iImage=(it.iImage==38)?40:38;
				tmpKey&=(0xFFFFFFFF^GP_HotKey::aVKMODUINT[it.iSubItem-1]);
				if (it.iImage==40) tmpKey|=GP_HotKey::aVKMODUINT[it.iSubItem-1];
				m_List.SetItem(&it);
				m_List.SetItemData(it.iItem,tmpKey);
				break;
			case 5:
				{
					CRect re,re2;
					char txt[210];
					m_List.GetSubItemRect(it.iItem,it.iSubItem,LVIR_BOUNDS,re);
					m_List.ClientToScreen(&re);
					m_List.GetClientRect(&re2);
					m_List.ClientToScreen(&re2);
					if (re2.right<re.right) re.right=re2.right;
					ScreenToClient(&re);

					m_List.GetItemText(it.iItem,it.iSubItem,txt,200);
					re.bottom+=200;
					int fnd=m_ComboKey.FindStringExact(0,txt);
					if (fnd!=CB_ERR) m_ComboKey.SetCurSel(fnd);

					re.top-=4;
					m_ComboKey.MoveWindow(&re);
					m_ComboKey.SetDroppedWidth(180);
					m_ComboKey.ModifyStyle(0,WS_VISIBLE,1);
					m_ComboKey.BringWindowToTop();
					m_ComboKey.ShowDropDown();
				}
				break;
			}
		}
	}
	*pResult = 0;
}

void CDlgKeyEditor::OnColumnclickListKey(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if ((m_SortFlag&0xFFFF)==(DWORD)pNMListView->iSubItem)
		m_SortFlag^=0x10000;

	m_SortFlag=(m_SortFlag&0xFFFF0000)+pNMListView->iSubItem;

	m_List.SortItems(&LockKeyCompareProc,m_SortFlag);

	*pResult = 0;
}
