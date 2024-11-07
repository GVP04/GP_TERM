// DlgTermcapEsc.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgTermcapEsc.h"
#include "DlgTermcapEscLine.h"
#include "GP_TermView.h"
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
// CDlgTermcapEsc dialog
int CALLBACK TermcapEscCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	int col=lParamSort&0xFFFF;
	int ret=lParam1-lParam2;
	PTERMCAPESCITEM ItemData1=(PTERMCAPESCITEM)lParam1;
	PTERMCAPESCITEM ItemData2=(PTERMCAPESCITEM)lParam2;

	if (ItemData1 && ItemData2)
	{
		switch(col)
		{
		case 0:	ret=ItemData1->dwFlags-ItemData2->dwFlags;					break;
		case 1:	ret=ItemData1->dwCommand-ItemData2->dwCommand;				break;
		case 2:	ret=strcmp(ItemData1->TermcapName,ItemData2->TermcapName);	break;
		case 3:	ret=strcmp(ItemData1->GroupName,ItemData2->GroupName);		break;
		case 4:	ret=strcmp((const char *)ItemData1->seq.ch,(const char *)ItemData2->seq.ch);			break;
		case 5:	ret=strcmp(ItemData1->Description,ItemData2->Description);	break;
		}

		int i;
		for(i=0;i<6 && ret==0;i++)
			if (i!=col)
				switch(i)
				{
				case 0:	ret=ItemData1->dwFlags-ItemData2->dwFlags;					break;
				case 1:	ret=ItemData1->dwCommand-ItemData2->dwCommand;				break;
				case 2:	ret=strcmp(ItemData1->TermcapName,ItemData2->TermcapName);	break;
				case 3:	ret=strcmp(ItemData1->GroupName,ItemData2->GroupName);		break;
				case 4:	ret=strcmp((const char *)ItemData1->seq.ch,(const char *)ItemData2->seq.ch);			break;
				case 5:	ret=strcmp(ItemData1->Description,ItemData2->Description);	break;
				}
	}
	return lParamSort&0xFFFF0000?-ret:ret;
}



CDlgTermcapEsc::CDlgTermcapEsc(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTermcapEsc::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTermcapEsc)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	DlgAutoSize=NULL;
	m_pTermCap=NULL;
	m_dwUpdateFlag=0;
	m_SortFlag=0;
	m_LastColumn=0;
}

CDlgTermcapEsc::~CDlgTermcapEsc()
{
	if (DlgAutoSize)
		delete DlgAutoSize;
}

void CDlgTermcapEsc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTermcapEsc)
	DDX_Control(pDX, IDC_COMBO2, m_ComboCopyTerm);
	DDX_Control(pDX, IDC_COMBO1, m_ComboIdCommand);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTermcapEsc, CDialog)
	//{{AFX_MSG_MAP(CDlgTermcapEsc)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON2, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON3, OnButtonCopyEsc)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickListEsc)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, OnColumnclickListEsc)
	ON_CBN_CLOSEUP(IDC_COMBO1, OnCloseupComboIdCommand)
	ON_CBN_CLOSEUP(IDC_COMBO2, OnCloseupComboCopyEsc)
	ON_BN_CLICKED(IDC_BUTTON4, OnButtonEditor)
	ON_BN_CLICKED(IDC_BUTTONTEST, OnButtontest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTermcapEsc message handlers

void CDlgTermcapEsc::OnDestroy() 
{
	if (DlgAutoSize)
		delete DlgAutoSize;

	DlgAutoSize=NULL;
	CDialog::OnDestroy();
}

BOOL CDlgTermcapEsc::OnInitDialog() 
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

	m_Edit.SetParent(&m_List);
	m_Edit.SetNotifyWnd(m_hWnd);

	m_List.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_List.InsertColumn(0,"v",LVCFMT_LEFT,28,0);
	m_List.InsertColumn(1,"Cmnd",LVCFMT_LEFT,50,0);
	m_List.InsertColumn(2,"TCName",LVCFMT_LEFT,45,0);
	m_List.InsertColumn(3,"Group",LVCFMT_LEFT,45,0);
	m_List.InsertColumn(4,"Sequence",LVCFMT_LEFT,150,0);
	m_List.InsertColumn(5,"Description",LVCFMT_LEFT,300,0);
	m_List.GetHeaderCtrl()->ModifyStyle(0,HDS_BUTTONS);
	m_List.SetImageList(&GPC.a_GPImageList[GPC.GetImageListId("MISCS")].m_IL,LVSIL_SMALL);

	DlgAutoSize=new GP_AutoSizing;
	DlgAutoSize->AddSetMain(m_hWnd);
	DlgAutoSize->SetMinSize(m_hWnd,200,150);
	DlgAutoSize->AddWnd(m_List.m_hWnd,this->m_hWnd,"NNEE");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTON1),this->m_hWnd,"EEEE");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTON2),this->m_hWnd,"EEEE");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTON3),this->m_hWnd,"EEEE");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTON4),this->m_hWnd,"EEEE");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_STATIC1),this->m_hWnd,"ENEN");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_EDITPARAMS),this->m_hWnd,"ENEE");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTONTEST),this->m_hWnd,"EEEE");
	DlgAutoSize->AddWnd(m_ComboCopyTerm,this->m_hWnd,"EEEE");

	if (m_pTermCap && m_pTermCap->m_ArrEsc)
	{
		m_ComboIdCommand.ResetContent();
		CString tmps;
		UINT i;
		int itm;
		for(i=0;i<m_pTermCap->m_uArrEscCount;i++)
			if (m_pTermCap->m_ArrEsc[i] && m_pTermCap->m_ArrEsc[i]->dwTermId==0)
			{
				tmps.Format("%6.6d - ",m_pTermCap->m_ArrEsc[i]->dwCommand);
				tmps+=m_pTermCap->m_ArrEsc[i]->Description;
				itm=m_ComboIdCommand.AddString(tmps);
				if (itm!=CB_ERR)	m_ComboIdCommand.SetItemData(itm,m_pTermCap->m_ArrEsc[i]->dwCommand);
			}

		DWORD oldID=(DWORD)-1;
		itm=0;
		while(itm<m_ComboIdCommand.GetCount())
		{
			DWORD newID=m_ComboIdCommand.GetItemData(itm);
			if (newID==oldID)
				m_ComboIdCommand.DeleteString(itm);
			else
			{
				oldID=newID;
				itm++;
			}
		}
	}
	m_dwUpdateFlag=0;
	return TRUE;
}

void CDlgTermcapEsc::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	if (DlgAutoSize)
		try{DlgAutoSize->UpdateSize();}catch(...){			GPC.m_ErrReport.GPWriteErrorLog("CDlgTermcapEsc", "OnSize","");}
}


BOOL CDlgTermcapEsc::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	BOOL TypeRet=TRUE;
	if (wParam==1) TypeRet=FALSE;

	return TypeRet?CDialog::OnCommand(wParam, lParam):TRUE;
}


void CDlgTermcapEsc::OnButtonAdd() 
{
	int itm;
	PTERMCAPESCITEM pEsc=GetCurrentEsc(itm);
	if (m_pTermCap)
	{
		PTERMCAPESCITEM pEscNew=m_pTermCap->AddEscItem();
		if (pEscNew && pEsc) *pEscNew=*pEsc;
		UpdateListItem(-1, pEscNew);
		m_dwUpdateFlag=1;
	}
}

void CDlgTermcapEsc::OnButtonDelete() 
{
	if (m_pTermCap && MessageBox("Delete Sequence?","Termcap Editor",MB_ICONQUESTION|MB_YESNO)==IDYES)
	{
		PTERMCAPESCITEM pEsc;
		int itm,lastItm=-1;

		while((pEsc=GetCurrentEsc(itm)))
		{
			lastItm=itm;
			m_pTermCap->DeleteEscItem(pEsc);
			m_List.DeleteItem(itm);
		}

		if (lastItm!=-1 && !m_List.SetItemState(lastItm,LVIS_SELECTED,LVIS_SELECTED))
			m_List.SetItemState(--lastItm,LVIS_SELECTED,LVIS_SELECTED);
		m_dwUpdateFlag=1;
	}
}

void CDlgTermcapEsc::OnCloseupComboCopyEsc() 
{
	m_ComboCopyTerm.ModifyStyle(WS_VISIBLE,0);
	Invalidate();
	int sel=m_ComboCopyTerm.GetCurSel();
	if (sel!=CB_ERR && m_pTermCap && m_pTermCap->m_ArrEsc && m_pTermCap->CurrentTerminal) 
	{
		UINT copyId=m_ComboCopyTerm.GetItemData(sel);
		int itm;
		POSITION pos=m_List.GetFirstSelectedItemPosition();
		while(pos)
		{
			itm=m_List.GetNextSelectedItem(pos);
			PTERMCAPESCITEM pEsc=(PTERMCAPESCITEM)m_List.GetItemData(itm);
			if (pEsc)
			{
				UINT i;
				for(i=0;i<m_pTermCap->m_uArrEscCount;i++)
					if (m_pTermCap->m_ArrEsc[i] && m_pTermCap->m_ArrEsc[i]->dwTermId==copyId && pEsc->dwCommand==m_pTermCap->m_ArrEsc[i]->dwCommand)
					{
						*pEsc=*(m_pTermCap->m_ArrEsc[i]);
						pEsc->dwTermId=m_pTermCap->CurrentTerminal->dwTermId;
						i=m_pTermCap->m_uArrEscCount;
						m_dwUpdateFlag=1;
					}
			}
		}
		UpdateInfo();
	}
}

void CDlgTermcapEsc::OnButtonCopyEsc()
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

void CDlgTermcapEsc::OnClickListEsc(NMHDR* pNMHDR, LRESULT* pResult) 
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
			PTERMCAPESCITEM ItemData=(PTERMCAPESCITEM)m_List.GetItemData(nmItem->iItem);

			if (ItemData)
				switch(nmItem->iSubItem)
				{
				case 0: //dwFlags
					ItemData->dwFlags^=0x1;
					UpdateListItem(nmItem->iItem,ItemData);
					break;
				case 1: //dwCommand
					{
						CRect re,re2;
						char txt[210];
						m_List.GetSubItemRect(nmItem->iItem,nmItem->iSubItem,LVIR_BOUNDS,re);
						m_List.ClientToScreen(&re);
						m_List.GetClientRect(&re2);
						m_List.ClientToScreen(&re2);
						if (re2.right<re.right) re.right=re2.right;
						ScreenToClient(&re);
						re.bottom+=200;

						m_List.GetItemText(nmItem->iItem,nmItem->iSubItem,txt,200);
						DWORD id=atoi(txt);
						int nItems=m_ComboIdCommand.GetCount();
						int i;
						for(i=0;i<nItems && m_ComboIdCommand.GetItemData(i)!=id;i++);

						if (i>=nItems) i=0;
						m_ComboIdCommand.SetCurSel(i);

						re.top-=4;
						m_ComboIdCommand.MoveWindow(&re);
						m_ComboIdCommand.SetDroppedWidth(280);
						m_ComboIdCommand.ModifyStyle(0,WS_VISIBLE,1);
						m_ComboIdCommand.BringWindowToTop();
						m_ComboIdCommand.ShowDropDown();
					}
					break;
				case 2://TermcapName
					SetEscEditor(nmItem->iItem,nmItem->iSubItem,ItemData->TermcapName);
					break;
				case 3://GroupName
					SetEscEditor(nmItem->iItem,nmItem->iSubItem,ItemData->GroupName);
					break;
				case 4://seq
					{
						CString csSeq;
						char str[25];
						UINT j;
						for(j=0;j<ItemData->seq.dwSeqLen;j++)
						{
							sprintf(str," %d %3.3d",ItemData->seq.chType[j],ItemData->seq.ch[j]);
							csSeq+=str;
						}
						SetEscEditor(nmItem->iItem,nmItem->iSubItem,(LPCSTR)csSeq);
					}
					break;
				case 5://Description
					SetEscEditor(nmItem->iItem,nmItem->iSubItem,ItemData->Description);
					break;
				}
		}
	}
	*pResult = 0;
}

UINT CDlgTermcapEsc::SetEscEditor(int Item, int SubItem, const char *txt)
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
		m_Edit.SetWindowText(txt);
		re.top-=3;
		m_Edit.MoveWindow(&re);
		m_Edit.ModifyStyle(0,WS_VISIBLE,1);
		m_Edit.BringWindowToTop();
		m_Edit.Invalidate();
		m_Edit.SetFocus();
	}
	return ret;
}


void CDlgTermcapEsc::OnColumnclickListEsc(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if ((m_SortFlag&0xFFFF)==(DWORD)pNMListView->iSubItem)
		m_SortFlag^=0x10000;

	m_SortFlag=(m_SortFlag&0xFFFF0000)+pNMListView->iSubItem;

	m_List.SortItems(&TermcapEscCompareProc,m_SortFlag);

	*pResult = 0;
}

void CDlgTermcapEsc::UpdateInfo()
{
	m_List.DeleteAllItems();
	if (m_pTermCap && m_pTermCap->m_ArrEsc && m_pTermCap->CurrentTerminal)
	{
		UINT i;
		for(i=0;i<m_pTermCap->m_uArrEscCount;i++)
			if (m_pTermCap->m_ArrEsc[i] && m_pTermCap->m_ArrEsc[i]->dwTermId==m_pTermCap->CurrentTerminal->dwTermId)
				UpdateListItem(m_List.InsertItem(i,""),m_pTermCap->m_ArrEsc[i]);
	}

}

void CDlgTermcapEsc::UpdateListItem(int iItem, PTERMCAPESCITEM iItemData)
{
	if (iItemData)
	{
		CString csSeq;
		int itmCur;
		GetCurrentEsc(itmCur);
		if (iItem==-1)
			iItem=m_List.InsertItem(itmCur+1,"");

		m_List.SetItemData(iItem,(DWORD)iItemData);

		LVITEM it={0};
		it.mask=LVIF_IMAGE|LVIF_TEXT;
		it.pszText="";
		it.iItem=iItem;

		char str[50];

		int i;
		for(i=0;i<6;i++)
		{
			it.iImage=-1;
			switch(i)
			{
			case 0:		it.iImage=((iItemData->dwFlags&0x1)!=0x1)?100:4;			break;
			case 1:
				it.pszText=str;
				sprintf(str,"%6.6d",iItemData->dwCommand);
				break;
			case 2:		it.pszText=(char *)((LPCSTR)iItemData->TermcapName);		break;
			case 3:		it.pszText=(char *)((LPCSTR)iItemData->GroupName);			break;
			case 4:
				{
					UINT j;
					for(j=0;j<iItemData->seq.dwSeqLen;j++)
					{
						sprintf(str," %d %3.3d",iItemData->seq.chType[j],iItemData->seq.ch[j]);
						csSeq+=str;
					}
					it.pszText=(char *)((LPCSTR)csSeq);
				}
				break;
			case 5:		it.pszText=(char *)((LPCSTR)iItemData->Description);		break;
			}

			it.iSubItem=i;
			m_List.SetItem(&it);
		}
	}
}

void CDlgTermcapEsc::OnCloseupComboIdCommand() 
{
	m_ComboIdCommand.ShowWindow(SW_HIDE);
	int sel=m_ComboIdCommand.GetCurSel();
	if (sel!=CB_ERR)
	{
		CString txt;
		DWORD ItemId=m_ComboIdCommand.GetItemData(sel);
		txt.Format("%6.6d",ItemId);

		int itm;
		POSITION pos=m_List.GetFirstSelectedItemPosition();
		while(pos)
		{
			itm=m_List.GetNextSelectedItem(pos);
			PTERMCAPESCITEM pEsc=(PTERMCAPESCITEM)m_List.GetItemData(itm);
			if (pEsc)
			{
				m_List.SetItemText(itm,1,txt);
				pEsc->dwCommand=ItemId;
				m_dwUpdateFlag=1;
			}
		}
		Invalidate();
	}
}

LRESULT CDlgTermcapEsc::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if (message==GPNE_ENDEDIT)
	{
		const char *txt=(const char *)lParam;
		if (txt)
		{
			int itm;
			POSITION pos=m_List.GetFirstSelectedItemPosition();
			while(pos)
			{
				itm=m_List.GetNextSelectedItem(pos);
				PTERMCAPESCITEM ItemData=(PTERMCAPESCITEM)m_List.GetItemData(itm);
				if (ItemData)
				{
					switch(m_LastColumn)
					{
					case 2:
						ItemData->TermcapName=txt;
						break;
					case 3:
						ItemData->GroupName=txt;
						break;
					case 4:
						{
							const char *cpos=txt;
							ItemData->seq.dwSeqLen=0;
							while(*cpos && ItemData->seq.dwSeqLen<TERMCAP_SEQLENGTH)
							{
								while(*cpos && (*cpos<'0' || *cpos>'9')) cpos++;
								if (*cpos)
								{
									ItemData->seq.chType[ItemData->seq.dwSeqLen]=atoi(cpos);
									while(*cpos && *cpos>='0' && *cpos<='9') cpos++;
									while(*cpos && (*cpos<'0' || *cpos>'9')) cpos++;
									if (*cpos)
									{
										ItemData->seq.ch[ItemData->seq.dwSeqLen++]=atoi(cpos);
										while(*cpos && *cpos>='0' && *cpos<='9') cpos++;
									}
								}
							}
						}
						break;
					case 5:
						ItemData->Description=txt;
						break;
					}
					UpdateListItem(itm,ItemData);
				}
			}
		}
	}
	return CDialog::WindowProc(message, wParam, lParam);
}

PTERMCAPESCITEM CDlgTermcapEsc::GetCurrentEsc(int & itm)
{
	itm=-1;
	PTERMCAPESCITEM ret=NULL;
	POSITION pos=m_List.GetFirstSelectedItemPosition();
	if (pos)
	{
		itm=m_List.GetNextSelectedItem(pos);
		ret=(PTERMCAPESCITEM)m_List.GetItemData(itm);
	}
	return ret;
}


void CDlgTermcapEsc::OnButtonEditor() 
{
	int itm=0;
	CDlgTermcapEscLine dlg(m_pTermCap,GetCurrentEsc(itm));
	m_dwUpdateFlag=1;
	dlg.DoModal();
	UpdateInfo();
}


void CDlgTermcapEsc::OnButtontest() 
{
	EnterCriticalSection(&(GPC.m_View->m_CSRemap));
	CString tmps;
	GetDlgItemText(IDC_EDITPARAMS,tmps);
	int itm=0;
	PTERMCAPESCITEM pItm=GetCurrentEsc(itm);
	if (pItm)
		GPC.m_View->EmulateRemappingInput(pItm->dwCommand, tmps, tmps.GetLength());
	LeaveCriticalSection(&(GPC.m_View->m_CSRemap));
}
