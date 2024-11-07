// DlgTermcapKbd.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgTermcapKbd.h"
#include "GP_HotKey.h"
#ifdef W_95
#else
	#ifdef W_NT
	#else
		#ifdef W_98
		#else
			#ifdef W_2000
			#else
#include "uxtheme.h"
			#endif
		#endif
	#endif
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTermcapKbd dialog
int CALLBACK TermcapKeyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	int col=lParamSort&0xFFFF;
	int ret=lParam1-lParam2;
	PTERMCAPKBDITEM ItemData1=(PTERMCAPKBDITEM)lParam1;
	PTERMCAPKBDITEM ItemData2=(PTERMCAPKBDITEM)lParam2;

	if (ItemData1 && ItemData2)
	{
		switch(col)
		{
		case 0:
			ret=(ItemData1->dwVirtualKey&0x1000)-(ItemData2->dwVirtualKey&0x1000);
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			ret=(ItemData1->dwVirtualKey&GP_HotKey::aVKMODUINT[col-1])-(ItemData2->dwVirtualKey&GP_HotKey::aVKMODUINT[col-1]);
			break;
		case 6:
			ret=strcmp(GP_HotKey::GetKeyName(ItemData1->dwVirtualKey),GP_HotKey::GetKeyName(ItemData2->dwVirtualKey));
			break;
		case 7:
			ret=strcmp(ItemData1->Seq,ItemData2->Seq);
			break;
		case 8:
			ret=strcmp(ItemData1->Description,ItemData2->Description);
			break;
		}

		int i;
		for(i=8;i>=0 && ret==0;i--)
			if (i!=col)
				switch(i)
				{
				case 0:
					ret=(ItemData1->dwVirtualKey&0x1000)-(ItemData2->dwVirtualKey&0x1000);
					break;
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
					ret=(ItemData1->dwVirtualKey&GP_HotKey::aVKMODUINT[i-1])-(ItemData2->dwVirtualKey&GP_HotKey::aVKMODUINT[i-1]);
					break;
				case 6:
					ret=strcmp(GP_HotKey::GetKeyName(ItemData1->dwVirtualKey),GP_HotKey::GetKeyName(ItemData2->dwVirtualKey));
					break;
				case 7:
					ret=strcmp(ItemData1->Seq,ItemData2->Seq);
					break;
				case 8:
					ret=strcmp(ItemData1->Description,ItemData2->Description);
					break;
				}
	}
	return lParamSort&0xFFFF0000?-ret:ret;
}


CDlgTermcapKbd::CDlgTermcapKbd(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTermcapKbd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTermcapKbd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	DlgAutoSize=NULL;
	m_pTermCap=NULL;
	m_dwUpdateFlag=0;
	m_SortFlag=0;
	m_LastColumn=7;
}

CDlgTermcapKbd::~CDlgTermcapKbd()
{
	if (DlgAutoSize)
		delete DlgAutoSize;
}

void CDlgTermcapKbd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTermcapKbd)
	DDX_Control(pDX, IDC_COMBOACTION, m_ComboAction);
	DDX_Control(pDX, IDC_COMBO2, m_ComboCopyTerm);
	DDX_Control(pDX, IDC_EDIT1, m_EditSeq);
	DDX_Control(pDX, IDC_COMBO1, m_ComboKey);
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTermcapKbd, CDialog)
	//{{AFX_MSG_MAP(CDlgTermcapKbd)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_CBN_CLOSEUP(IDC_COMBO1, OnCloseupComboKey)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickListKeys)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, OnColumnclickListKey)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON2, OnButtonDelete)
	ON_CBN_CLOSEUP(IDC_COMBO2, OnCloseupComboCopyKbd)
	ON_BN_CLICKED(IDC_BUTTON3, OnButtonCopyKbd)
	ON_CBN_CLOSEUP(IDC_COMBOACTION, OnCloseupComboaction)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTermcapKbd message handlers

void CDlgTermcapKbd::OnDestroy()
{
	if (DlgAutoSize)
		delete DlgAutoSize;

	DlgAutoSize=NULL;

	CDialog::OnDestroy();
}

BOOL CDlgTermcapKbd::OnInitDialog()
{
	CDialog::OnInitDialog();
	#ifdef W_95
	#else
		#ifdef W_NT
		#else
			#ifdef W_98
			#else
				#ifdef W_2000
				#else
				EnableThemeDialogTexture(m_hWnd,ETDT_USETABTEXTURE);
				Invalidate();
				#endif
			#endif
		#endif
	#endif

	m_EditSeq.SetParent(&m_List);
	m_EditSeq.SetNotifyWnd(m_hWnd);
	m_ComboAction.ResetContent();
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

	for(i=0;i<CTermCap::uNKbdActions;i++)
	{
		if (CTermCap::uKbdActions[i]==TCKA_NONE)
			m_ComboAction.AddString("");
		else
			m_ComboAction.AddString(CTermCap::cArrKbdActions[i]);
	}

	m_List.SetExtendedStyle(LVS_EX_SUBITEMIMAGES|LVS_EX_GRIDLINES);
	m_List.InsertColumn(0,"v",LVCFMT_LEFT,28,0);
	m_List.InsertColumn(1,"alt",LVCFMT_LEFT,25,0);
	m_List.InsertColumn(2,"ctrl",LVCFMT_LEFT,27,0);
	m_List.InsertColumn(3,"shif",LVCFMT_LEFT,29,0);
	m_List.InsertColumn(4,"win",LVCFMT_LEFT,29,0);
	m_List.InsertColumn(5,"etcl",LVCFMT_LEFT,29,0);
	m_List.InsertColumn(6,"Virtual Key",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(7,"Output String",LVCFMT_LEFT,100,0);
	m_List.InsertColumn(8,"Action",LVCFMT_LEFT,50,0);
	m_List.InsertColumn(9,"Description",LVCFMT_LEFT,250,0);
	m_List.GetHeaderCtrl()->ModifyStyle(0,HDS_BUTTONS);
	m_List.SetImageList(&GPC.a_GPImageList[GPC.GetImageListId("MISCS")].m_IL,LVSIL_SMALL);

	DlgAutoSize=new GP_AutoSizing;
	DlgAutoSize->AddSetMain(m_hWnd);
	DlgAutoSize->SetMinSize(m_hWnd,200,150);
	DlgAutoSize->AddWnd(m_List.m_hWnd,this->m_hWnd,"NNEE");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTON1),this->m_hWnd,"EEEE");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTON2),this->m_hWnd,"EEEE");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTON3),this->m_hWnd,"EEEE");

	m_dwUpdateFlag=0;

	return TRUE;
}

void CDlgTermcapKbd::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if (DlgAutoSize)
		try{DlgAutoSize->UpdateSize();}catch(...){			GPC.m_ErrReport.GPWriteErrorLog("CDlgTermcapKbd", "OnSize","");}
}

BOOL CDlgTermcapKbd::OnCommand(WPARAM wParam, LPARAM lParam)
{
	BOOL TypeRet=TRUE;
	if (wParam==1)
	{
		if (::GetFocus()==m_EditSeq.m_hWnd)
		{
			::SetFocus(m_List.m_hWnd);
			int itm;
			PTERMCAPKBDITEM CurrentKbd=GetCurrentKbd(itm);
			if (CurrentKbd)
			{
				if (m_LastColumn==8)
					m_List.SetItemState(itm++,LVIS_SELECTED,0);

				if (m_List.SetItemState(itm,LVIS_SELECTED,LVIS_SELECTED))
					SetSeqEditor(itm,m_LastColumn==7?8:7,NULL);
			}

		}
		TypeRet=FALSE;
	}

	if (wParam==2)
	{
		TypeRet=FALSE;
		if (::GetFocus()==m_EditSeq.m_hWnd)
		{
			int itm;
			PTERMCAPKBDITEM CurrentKbd=GetCurrentKbd(itm);
			if (CurrentKbd)
			{
				m_EditSeq.SetWindowText(CurrentKbd->Seq);
				::SetFocus(m_List.m_hWnd);
			}
		}
	}

	return TypeRet?CDialog::OnCommand(wParam, lParam):TRUE;
}

void CDlgTermcapKbd::UpdateInfo()
{
	m_List.DeleteAllItems();
	if (m_pTermCap && m_pTermCap->m_ArrKbd && m_pTermCap->CurrentTerminal)
	{
		UINT i;
		for(i=0;i<m_pTermCap->m_uArrKbdCount;i++)
			if (m_pTermCap->m_ArrKbd[i] && m_pTermCap->m_ArrKbd[i]->dwTermId==m_pTermCap->CurrentTerminal->dwTermId)
			{
				int itm=m_List.InsertItem(i,"");
				UpdateListItem(itm,m_pTermCap->m_ArrKbd[i]);
			}
	}
}

void CDlgTermcapKbd::UpdateListItem(int iItem, PTERMCAPKBDITEM iItemData)
{
	m_List.SetItemData(iItem,(DWORD)iItemData);
	if (iItemData)
	{
		LVITEM it={0};
		it.mask=LVIF_IMAGE|LVIF_TEXT;
		it.pszText="";
		it.iItem=iItem;
		DWORD iKey=iItemData->dwVirtualKey;

		it.iImage=((iItemData->dwFlags&0x1)!=0x1)?100:4;
		m_List.SetItem(&it);

		int j;
		for(j=0;j<5;j++)
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

		it.pszText=(char *)((LPCSTR)iItemData->Seq);
		it.iImage=-1;
		it.iSubItem++;
		m_List.SetItem(&it);

		it.pszText=(char *)((LPCSTR)iItemData->csAction);
		it.iImage=-1;
		it.iSubItem++;
		m_List.SetItem(&it);

		it.pszText=(char *)((LPCSTR)iItemData->Description);
		it.iImage=-1;
		it.iSubItem++;
		m_List.SetItem(&it);
	}
}

void CDlgTermcapKbd::OnCloseupComboKey()
{
	m_ComboKey.ShowWindow(SW_HIDE);
	int sel=m_ComboKey.GetCurSel();
	if (sel!=CB_ERR)
	{
		CString txt;
		m_ComboKey.GetLBText(sel,txt);
		int nItem = 0;
		PTERMCAPKBDITEM ItemData=GetCurrentKbd(nItem);
		if (ItemData)
		{
			m_List.SetItemText(nItem,6,txt);
			DWORD tmpkey=0;
			txt+="|";
			ItemData->dwVirtualKey=(ItemData->dwVirtualKey&0x0000FFFF)+GP_HotKey::StringFromToHotKey(txt,tmpkey);
			m_dwUpdateFlag=1;
		}
		Invalidate();
	}
}

void CDlgTermcapKbd::OnClickListKeys(NMHDR* pNMHDR, LRESULT* pResult)
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
			PTERMCAPKBDITEM ItemData=(PTERMCAPKBDITEM)m_List.GetItemData(nmItem->iItem);

			if (ItemData)
				switch(nmItem->iSubItem)
				{
				case 0:
					ItemData->dwFlags^=0x1;
					UpdateListItem(nmItem->iItem,ItemData);
					break;
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
					ItemData->dwVirtualKey^=GP_HotKey::aVKMODUINT[nmItem->iSubItem-1];
					UpdateListItem(nmItem->iItem,ItemData);
					break;
				case 6:
					{
						CRect re,re2;
						char txt[210];
						m_List.GetSubItemRect(nmItem->iItem,nmItem->iSubItem,LVIR_BOUNDS,re);
						m_List.ClientToScreen(&re);
						m_List.GetClientRect(&re2);
						m_List.ClientToScreen(&re2);
						if (re2.right<re.right) re.right=re2.right;
						ScreenToClient(&re);

						m_List.GetItemText(nmItem->iItem,nmItem->iSubItem,txt,200);
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
				case 7:
					SetSeqEditor(nmItem->iItem,nmItem->iSubItem,ItemData->Seq);
					break;
				case 8:
					{
						CRect re,re2;
						char txt[210];
						m_List.GetSubItemRect(nmItem->iItem,nmItem->iSubItem,LVIR_BOUNDS,re);
						m_List.ClientToScreen(&re);
						m_List.GetClientRect(&re2);
						m_List.ClientToScreen(&re2);
						if (re2.right<re.right) re.right=re2.right;
						ScreenToClient(&re);

						m_List.GetItemText(nmItem->iItem,nmItem->iSubItem,txt,200);
						re.bottom+=200;
						int fnd=m_ComboAction.FindStringExact(0,txt);
						if (fnd!=CB_ERR) m_ComboAction.SetCurSel(fnd);

						re.top-=4;
						m_ComboAction.MoveWindow(&re);
						m_ComboAction.SetDroppedWidth(180);
						m_ComboAction.ModifyStyle(0,WS_VISIBLE,1);
						m_ComboAction.BringWindowToTop();
						m_ComboAction.ShowDropDown();
					}
					break;
				case 9:
					SetSeqEditor(nmItem->iItem,nmItem->iSubItem,ItemData->Description);
					break;
				}
		}
	}
	*pResult = 0;
}

void CDlgTermcapKbd::OnColumnclickListKey(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if ((m_SortFlag&0xFFFF)==(DWORD)pNMListView->iSubItem)
		m_SortFlag^=0x10000;

	m_SortFlag=(m_SortFlag&0xFFFF0000)+pNMListView->iSubItem;

	m_List.SortItems(&TermcapKeyCompareProc,m_SortFlag);

	*pResult = 0;
}

LRESULT CDlgTermcapKbd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message==GPNE_ENDEDIT)
	{
		const char *txt=(const char *)lParam;
		if (txt)
		{
			int itm;
			PTERMCAPKBDITEM ItemData=GetCurrentKbd(itm);
			if (ItemData)
			{
				switch(m_LastColumn)
				{
				case 7:
					ItemData->Seq=txt;
					m_dwUpdateFlag=1;
					break;
				case 8:
					ItemData->Description=txt;
					m_dwUpdateFlag=1;
					break;
				}
				UpdateListItem(itm,ItemData);
			}
		}
	}
	return CDialog::WindowProc(message, wParam, lParam);
}

PTERMCAPKBDITEM CDlgTermcapKbd::GetCurrentKbd(int & itm)
{
	itm=-1;
	PTERMCAPKBDITEM ret=NULL;
	POSITION pos=m_List.GetFirstSelectedItemPosition();
	if (pos)
	{
		itm=m_List.GetNextSelectedItem(pos);
		ret=(PTERMCAPKBDITEM)m_List.GetItemData(itm);
	}
	return ret;
}

UINT CDlgTermcapKbd::SetSeqEditor(int Item, int SubItem, const char *txt)
{
	CRect re;
	UINT ret=0;
	m_LastColumn=SubItem;
	m_List.EnsureVisible(Item,FALSE);
	if ((ret=m_List.GetSubItemRect(Item,SubItem,LVIR_BOUNDS,re)))
	{
		char txt2[600];
		if (txt==NULL)
			m_List.GetItemText(Item,SubItem,(char *)(txt=txt2),590);
		m_EditSeq.SetWindowText(txt);
		re.top-=3;
		m_EditSeq.MoveWindow(&re);
		m_EditSeq.ModifyStyle(0,WS_VISIBLE,1);
		m_EditSeq.BringWindowToTop();
		m_EditSeq.Invalidate();
		m_EditSeq.SetFocus();
	}
	return ret;
}

void CDlgTermcapKbd::OnButtonAdd()
{
	if (m_pTermCap)
	{
		PTERMCAPKBDITEM pkbd=m_pTermCap->AddKbdItem();
		pkbd->dwTermId=m_pTermCap->CurrentTerminal->dwTermId;
		int itm=m_List.InsertItem(m_List.GetItemCount(),"");
		m_List.EnsureVisible(itm,FALSE);
		UpdateListItem(itm,pkbd);
		m_dwUpdateFlag=1;
	}
}

void CDlgTermcapKbd::OnButtonDelete()
{
	int itm;
	PTERMCAPKBDITEM pkbd=GetCurrentKbd(itm);
	if (m_pTermCap && pkbd && MessageBox("Delete key?","Termcap Editor",MB_ICONQUESTION|MB_YESNO)==IDYES)
	{
		if (pkbd)
		{
			m_pTermCap->DeleteKbdItem(pkbd);
			m_List.DeleteItem(itm);
			if (!m_List.SetItemState(itm,LVIS_SELECTED,LVIS_SELECTED))
				m_List.SetItemState(--itm,LVIS_SELECTED,LVIS_SELECTED);
		}
		m_dwUpdateFlag=1;
	}
}

void CDlgTermcapKbd::OnCloseupComboCopyKbd()
{
	m_ComboCopyTerm.ModifyStyle(WS_VISIBLE,0);
	Invalidate();
	int sel=m_ComboCopyTerm.GetCurSel();
	if (sel!=CB_ERR && m_pTermCap) 
	{
		m_pTermCap->CopyKbd(m_ComboCopyTerm.GetItemData(sel),m_pTermCap->CurrentTerminal->dwTermId);
		m_dwUpdateFlag=1;
		UpdateInfo();
	}
}

void CDlgTermcapKbd::OnButtonCopyKbd()
{
	m_ComboCopyTerm.ResetContent();

	if (m_pTermCap && m_pTermCap->m_ArrTerminal)
	{
		UINT i;
		for(i=0;i<m_pTermCap->m_uArrTerminalCount;i++)
			if (m_pTermCap->m_ArrTerminal[i] && m_pTermCap->m_ArrTerminal[i]->dwTermId!=m_pTermCap->CurrentTerminal->dwTermId)
			{
				int itm=m_ComboCopyTerm.AddString(m_pTermCap->m_ArrTerminal[i]->TerminalName);
				if (itm!=CB_ERR)
					m_ComboCopyTerm.SetItemData(itm,m_pTermCap->m_ArrTerminal[i]->dwTermId);
			}

		m_ComboCopyTerm.ModifyStyle(0,WS_VISIBLE);
		m_ComboCopyTerm.SetFocus();
		m_ComboCopyTerm.ShowDropDown();
		m_dwUpdateFlag=1;
	}
}

void CDlgTermcapKbd::OnCloseupComboaction() 
{
	m_ComboAction.ShowWindow(SW_HIDE);
	int sel=m_ComboAction.GetCurSel();
	if (sel!=CB_ERR)
	{
		CString txt;
		m_ComboAction.GetLBText(sel,txt);
		int nItem = 0;
		PTERMCAPKBDITEM ItemData=GetCurrentKbd(nItem);
		if (ItemData)
		{
			m_List.SetItemText(nItem,8,txt);
			ItemData->csAction=txt;
			m_dwUpdateFlag=1;
		}
		Invalidate();
	}
}
