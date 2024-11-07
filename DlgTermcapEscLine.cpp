// DlgTermcapEscLine.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgTermcapEscLine.h"
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
// CDlgTermcapEscLine dialog


CDlgTermcapEscLine::CDlgTermcapEscLine(CTermCap *i_pTermCap, PTERMCAPESCITEM ipEscItem, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTermcapEscLine::IDD, pParent)
{
	m_pTermCap=i_pTermCap;
	m_pEscItem=ipEscItem;

	//{{AFX_DATA_INIT(CDlgTermcapEscLine)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgTermcapEscLine::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTermcapEscLine)
	DDX_Control(pDX, IDC_COMBOESCVALUE2, m_ComboEscValue2);
	DDX_Control(pDX, IDC_COMBOESCVALUE, m_ComboEscValue);
	DDX_Control(pDX, IDC_COMBOESCTYPE, m_ComboEscType);
	DDX_Control(pDX, IDC_COMBO1, m_ComboId);
	DDX_Control(pDX, IDC_CHECK1, m_CheckEnable);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_EDIT3, m_EditGroup);
	DDX_Control(pDX, IDC_EDIT2, m_EditTCName);
	DDX_Control(pDX, IDC_EDIT1, m_EditDescription);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTermcapEscLine, CDialog)
	//{{AFX_MSG_MAP(CDlgTermcapEscLine)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTONUP2, OnButtonup2)
	ON_BN_CLICKED(IDC_BUTTONUP, OnButtonup)
	ON_BN_CLICKED(IDC_BUTTONINSERT, OnButtoninsert)
	ON_BN_CLICKED(IDC_BUTTONDOWN2, OnButtondown2)
	ON_BN_CLICKED(IDC_BUTTONDOWN, OnButtondown)
	ON_BN_CLICKED(IDC_BUTTONADD, OnButtonadd)
	ON_BN_CLICKED(IDC_BUTTONDELETE, OnButtondelete)
	ON_BN_CLICKED(IDC_CHECK1, OnCheckEnable)
	ON_CBN_CLOSEUP(IDC_COMBO1, OnCloseupComboId)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeComboID)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickListEsc)
	ON_CBN_CLOSEUP(IDC_COMBOESCVALUE, OnCloseupComboescvalue)
	ON_CBN_CLOSEUP(IDC_COMBOESCTYPE, OnCloseupComboesctype)
	ON_CBN_CLOSEUP(IDC_COMBOESCVALUE2, OnCloseupComboescvalue2)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEditDescription)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEditTCName)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEditGroup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTermcapEscLine message handlers

BOOL CDlgTermcapEscLine::OnInitDialog() 
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

	CString tmps;
	int itm;
	UINT i;

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_List.InsertColumn(0,"TYPE",LVCFMT_LEFT,70,0);
	m_List.InsertColumn(1,"VALUE",LVCFMT_LEFT,172,0);
	m_List.GetHeaderCtrl()->ModifyStyle(0,HDS_BUTTONS);
	
	if (m_pTermCap && m_pTermCap->m_ArrEsc)
	{
		m_ComboId.ResetContent();
		for(i=0;i<m_pTermCap->m_uArrEscCount;i++)
			if (m_pTermCap->m_ArrEsc[i] && m_pTermCap->m_ArrEsc[i]->dwTermId==0)
			{
				tmps.Format("%6.6d - ",m_pTermCap->m_ArrEsc[i]->dwCommand);
				tmps+=m_pTermCap->m_ArrEsc[i]->Description;
				itm=m_ComboId.AddString(tmps);
				if (itm!=CB_ERR)	m_ComboId.SetItemData(itm,m_pTermCap->m_ArrEsc[i]->dwCommand);
			}

		DWORD oldID=(DWORD)-1;
		itm=0;
		while(itm<m_ComboId.GetCount())
		{
			DWORD newID=m_ComboId.GetItemData(itm);
			if (newID==oldID)
				m_ComboId.DeleteString(itm);
			else
			{
				oldID=newID;
				itm++;
			}
		}
	}

	m_ComboEscValue.ResetContent();

	for(i=0;i<255;i++)
	{
		char t[10];
		strcpy(t,cArrBytesName[i]);
		DosToAnsi(t);
		tmps.Format("%3.3d %s (%s)",i,cArrBytesName[i],t);
		itm=m_ComboEscValue.AddString(tmps);
		if (itm!=CB_ERR)	m_ComboEscValue.SetItemData(itm,i);
	}

	m_ComboEscType.ResetContent();
	for(i=0;i<CTermCap::uNEscTypes;i++)
	{
		itm=m_ComboEscType.AddString(CTermCap::cArrEscTypesDescr[i]);
		if (itm!=CB_ERR)	m_ComboEscType.SetItemData(itm,CTermCap::uEscTypes[i]);
	}

	m_ComboEscValue2.ResetContent();
	for(i=0;i<CTermCap::uNEscSubTypes;i++)
	{
		itm=m_ComboEscValue2.AddString(CTermCap::cArrEscSubTypesDescr[i]);
		if (itm!=CB_ERR)	m_ComboEscValue2.SetItemData(itm,CTermCap::uEscSubTypes[i]);
	}
	
	UpdateInfo();

	return TRUE;
}

void CDlgTermcapEscLine::UpdateInfo()
{
	int i;

	if (m_pTermCap && m_pTermCap->CurrentTerminal)
	{
		UINT i2;
		for(i2=0;i2<m_pTermCap->m_uArrEscCount && m_pEscItem==NULL;i2++)
			if (m_pTermCap->m_ArrEsc[i2] && m_pTermCap->CurrentTerminal->dwTermId==m_pTermCap->m_ArrEsc[i2]->dwTermId)
				m_pEscItem=m_pTermCap->m_ArrEsc[i2];
	}

	if (m_pEscItem)
	{
		int ci=GetCurEscSubItem();
		if (ci<0) ci=0;
		m_EditGroup.SetWindowText(m_pEscItem->GroupName);
		m_EditTCName.SetWindowText(m_pEscItem->TermcapName);
		m_EditDescription.SetWindowText(m_pEscItem->Description);
		m_CheckEnable.SetCheck(m_pEscItem->dwFlags&0x1);

		int nId=m_ComboId.GetCount();
		for(i=0;i<nId;i++)
			if (m_ComboId.GetItemData(i)==m_pEscItem->dwCommand)
				m_ComboId.SetCurSel(i),i=nId;

		nId=m_List.GetItemCount();
		if ((UINT)nId!=m_pEscItem->seq.dwSeqLen)
		{
			m_List.DeleteAllItems();
			nId=m_pEscItem->seq.dwSeqLen;
			for(i=0;i<nId;i++)
				m_List.InsertItem(i,"");
		}

		char tmps[20];

		for(i=0;i<nId;i++)
		{
			const char *pos=NULL;
			if (m_pEscItem->seq.chType[i]>=CTermCap::uNEscTypes)
			{
				sprintf((char *)(pos=tmps),"%d",m_pEscItem->seq.chType[i]);
			}
			else pos=CTermCap::cArrEscTypesDescr[m_pEscItem->seq.chType[i]];
			m_List.SetItemText(i,0,pos);

			switch(m_pEscItem->seq.chType[i])
			{
			case TCET_DIGIT:
			case TCET_HEXDIGIT:
			case TCET_MOD256MINUSSP:
			case TCET_MOD256MINUS31:
			case TCET_MOD256:
			case TCET_MOD90MINUSSP:
			case TCET_MOD256MINUS1:
				{
					pos=NULL;
					UINT j;
					for(j=0;j<CTermCap::uNEscSubTypes && pos==NULL;j++)
						if (m_pEscItem->seq.ch[i]==CTermCap::uEscSubTypes[j])
							pos=CTermCap::cArrEscSubTypesDescr[j];
					if (pos==NULL) pos="UNKNOWN";
				}
				break;
			case TCET_BYTE:
			default:
				pos=cArrBytesName[m_pEscItem->seq.ch[i]];
				break;
			}
			m_List.SetItemText(i,1,pos);
		}
		m_List.SetItemState(ci,LVIS_SELECTED,LVIS_SELECTED);
	}
	else
		m_List.DeleteAllItems();
}

void CDlgTermcapEscLine::OnDestroy() 
{
	CDialog::OnDestroy();
}

void CDlgTermcapEscLine::OnButtonup2() 
{
	if (m_pEscItem && m_pTermCap && m_pTermCap->CurrentTerminal && m_pTermCap->m_uArrEscCount)
	{
		UINT i;
		for(i=0;i<m_pTermCap->m_uArrEscCount && m_pEscItem!=m_pTermCap->m_ArrEsc[i];i++);

		m_pEscItem=NULL;

		for(i==0?i=m_pTermCap->m_uArrEscCount-1:i--;i<m_pTermCap->m_uArrEscCount && m_pEscItem==NULL;i--)
			if (m_pTermCap->m_ArrEsc[i] && m_pTermCap->CurrentTerminal->dwTermId==m_pTermCap->m_ArrEsc[i]->dwTermId)
				m_pEscItem=m_pTermCap->m_ArrEsc[i];

		for(i=m_pTermCap->m_uArrEscCount-1;i<m_pTermCap->m_uArrEscCount && m_pEscItem==NULL;i--)
			if (m_pTermCap->m_ArrEsc[i] && m_pTermCap->CurrentTerminal->dwTermId==m_pTermCap->m_ArrEsc[i]->dwTermId)
				m_pEscItem=m_pTermCap->m_ArrEsc[i];
	}

	UpdateInfo();
}

void CDlgTermcapEscLine::OnButtondown2() 
{
	if (m_pEscItem && m_pTermCap && m_pTermCap->CurrentTerminal && m_pTermCap->m_uArrEscCount)
	{
		UINT i;
		for(i=0;i<m_pTermCap->m_uArrEscCount && m_pEscItem!=m_pTermCap->m_ArrEsc[i];i++);

		m_pEscItem=NULL;

		for(i++;i<m_pTermCap->m_uArrEscCount && m_pEscItem==NULL;i++)
			if (m_pTermCap->m_ArrEsc[i] && m_pTermCap->CurrentTerminal->dwTermId==m_pTermCap->m_ArrEsc[i]->dwTermId)
				m_pEscItem=m_pTermCap->m_ArrEsc[i];

		for(i=0;i<m_pTermCap->m_uArrEscCount && m_pEscItem==NULL;i++)
			if (m_pTermCap->m_ArrEsc[i] && m_pTermCap->CurrentTerminal->dwTermId==m_pTermCap->m_ArrEsc[i]->dwTermId)
				m_pEscItem=m_pTermCap->m_ArrEsc[i];
	}
	UpdateInfo();
}

void CDlgTermcapEscLine::OnButtonup() 
{
	int ci=GetCurEscSubItem();
	if (ci>0)
	{
		unsigned char tmp;
		tmp=m_pEscItem->seq.ch[ci];
		m_pEscItem->seq.ch[ci]=m_pEscItem->seq.ch[ci-1];
		m_pEscItem->seq.ch[ci-1]=tmp;
		tmp=m_pEscItem->seq.chType[ci];
		m_pEscItem->seq.chType[ci]=m_pEscItem->seq.chType[ci-1];
		m_pEscItem->seq.chType[ci-1]=tmp;
		m_List.SetItemState(ci-1,LVIS_SELECTED,LVIS_SELECTED);
	}
	UpdateInfo();
}

void CDlgTermcapEscLine::OnButtondown() 
{
	int ci=GetCurEscSubItem();
	if (ci>=0 && m_pEscItem->seq.dwSeqLen>1 && (UINT)ci<m_pEscItem->seq.dwSeqLen-1)
	{
		unsigned char tmp;
		tmp=m_pEscItem->seq.ch[ci];
		m_pEscItem->seq.ch[ci]=m_pEscItem->seq.ch[ci+1];
		m_pEscItem->seq.ch[ci+1]=tmp;
		tmp=m_pEscItem->seq.chType[ci];
		m_pEscItem->seq.chType[ci]=m_pEscItem->seq.chType[ci+1];
		m_pEscItem->seq.chType[ci+1]=tmp;
		m_List.SetItemState(ci+1,LVIS_SELECTED,LVIS_SELECTED);
	}
	UpdateInfo();
}

void CDlgTermcapEscLine::OnButtoninsert() 
{
	if (m_pEscItem)
	{
		int ci=GetCurEscSubItem();
		if (ci<0) ci=0;
		int i;
		for(i=TERMCAP_SEQLENGTH-1;i>ci;i--)
		{
			m_pEscItem->seq.ch[i]=m_pEscItem->seq.ch[i-1];
			m_pEscItem->seq.chType[i]=m_pEscItem->seq.chType[i-1];
		}

		m_pEscItem->seq.ch[i]=m_pEscItem->seq.chType[i]=0;
		if (m_pEscItem->seq.dwSeqLen<TERMCAP_SEQLENGTH) m_pEscItem->seq.dwSeqLen++;
	}
	UpdateInfo();
}

void CDlgTermcapEscLine::OnButtonadd() 
{
	if (m_pEscItem && m_pEscItem->seq.dwSeqLen<TERMCAP_SEQLENGTH-1)
	{
		m_pEscItem->seq.ch[m_pEscItem->seq.dwSeqLen]=0;
		m_pEscItem->seq.chType[m_pEscItem->seq.dwSeqLen++]=0;
	}
	UpdateInfo();
}

void CDlgTermcapEscLine::OnButtondelete() 
{
	int ci=GetCurEscSubItem();
	if (ci>=0)
	{
		int i;
		for(i=ci;i<TERMCAP_SEQLENGTH-2;i++)
		{
			m_pEscItem->seq.ch[i]=m_pEscItem->seq.ch[i+1];
			m_pEscItem->seq.chType[i]=m_pEscItem->seq.chType[i+1];
		}
		m_pEscItem->seq.ch[TERMCAP_SEQLENGTH-1]=0;
		m_pEscItem->seq.chType[TERMCAP_SEQLENGTH-1]=0;
		if (m_pEscItem->seq.dwSeqLen>0)	m_pEscItem->seq.dwSeqLen--;
	}
	UpdateInfo();
}

void CDlgTermcapEscLine::OnCheckEnable() 
{
	if (m_pEscItem)
		m_pEscItem->dwFlags=((m_pEscItem->dwFlags&0xFFFFFFFE)|m_CheckEnable.GetCheck());
}

void CDlgTermcapEscLine::OnCloseupComboId() 
{
	OnSelchangeComboID();
}

int CDlgTermcapEscLine::GetCurEscSubItem()
{
	int ret=-1;
	POSITION pos=m_List.GetFirstSelectedItemPosition();
	if (pos && m_pEscItem)
		ret=m_List.GetNextSelectedItem(pos);
	return ret;
}

void CDlgTermcapEscLine::OnSelchangeComboID() 
{
	int cs=m_ComboId.GetCurSel();
	if (m_pEscItem && cs!=CB_ERR)
		m_pEscItem->dwCommand=m_ComboId.GetItemData(cs);
}

void CDlgTermcapEscLine::OnClickListEsc(NMHDR* pNMHDR, LRESULT* pResult) 
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
			CRect re,re2;
			m_List.GetSubItemRect(nmItem->iItem,nmItem->iSubItem,LVIR_BOUNDS,re);
			if (nmItem->iSubItem==0)
			{
				m_List.GetSubItemRect(nmItem->iItem,nmItem->iSubItem+1,LVIR_BOUNDS,re2);
				re.right=re2.left;
			}
			m_List.ClientToScreen(&re);
			m_List.GetClientRect(&re2);
			m_List.ClientToScreen(&re2);
			if (re2.right<re.right) re.right=re2.right;
			ScreenToClient(&re);
			re.bottom+=200;
			re.top-=4;
			int i;
			int nCb=0;


			switch(nmItem->iSubItem)
			{
			case 0:
				nCb=m_ComboEscType.GetCount();
				if (nCb!=CB_ERR)
				{
					for(i=0;i<nCb;i++)
						if (m_ComboEscType.GetItemData(i)==m_pEscItem->seq.chType[nmItem->iItem])
							m_ComboEscType.SetCurSel(i),i+=1111;
					m_ComboEscType.MoveWindow(&re);
					m_ComboEscType.SetDroppedWidth(180);
					m_ComboEscType.ModifyStyle(0,WS_VISIBLE,1);
					m_ComboEscType.BringWindowToTop();
					m_ComboEscType.ShowDropDown();
				}
				break;
			case 1:
				{
					CComboBox *pCb=NULL;
					switch(m_pEscItem->seq.chType[nmItem->iItem])
					{
					case TCET_DIGIT:
					case TCET_HEXDIGIT:
					case TCET_MOD256MINUSSP:
					case TCET_MOD256MINUS31:
					case TCET_MOD256:
					case TCET_MOD90MINUSSP:
					case TCET_MOD256MINUS1:
						pCb=&m_ComboEscValue2;
						break;
					case TCET_BYTE:
					default:
						pCb=&m_ComboEscValue;
						break;
					}
					if (pCb)
					{
						nCb=pCb->GetCount();
						if (nCb!=CB_ERR)
						{
							for(i=0;i<nCb;i++)
								if (pCb->GetItemData(i)==m_pEscItem->seq.ch[nmItem->iItem])
									pCb->SetCurSel(i),i+=1111;

							pCb->MoveWindow(&re);
							pCb->SetDroppedWidth(180);
							pCb->ModifyStyle(0,WS_VISIBLE,1);
							pCb->BringWindowToTop();
							pCb->ShowDropDown();
						}
					}
					break;
				}
				break;
			}
		}
	}
	*pResult = 0;
}

void CDlgTermcapEscLine::OnCloseupComboesctype() 
{
	POSITION pos=m_List.GetFirstSelectedItemPosition();
	int cs=m_ComboEscType.GetCurSel();
	if (cs!=CB_ERR && pos && m_pEscItem)
	{
		int itm=m_List.GetNextSelectedItem(pos);
		if ((UINT)itm<m_pEscItem->seq.dwSeqLen)
		{
			if ((m_pEscItem->seq.chType[itm]=(unsigned char)m_ComboEscType.GetItemData(cs))!=TCET_BYTE)
			{
				UINT j;
				for(j=0;j<CTermCap::uNEscSubTypes;j++)
					if (CTermCap::uEscSubTypes[j]==m_pEscItem->seq.ch[itm])	j=-123;
				if (j==CTermCap::uNEscSubTypes) m_pEscItem->seq.ch[itm]=TCEST_LENGTH;
			}
		}
	}
	m_ComboEscType.ShowWindow(SW_HIDE);
	UpdateInfo();
}

void CDlgTermcapEscLine::OnCloseupComboescvalue() 
{
	POSITION pos=m_List.GetFirstSelectedItemPosition();
	int cs=m_ComboEscValue.GetCurSel();
	if (cs!=CB_ERR && pos && m_pEscItem)
	{
		int itm=m_List.GetNextSelectedItem(pos);
		if ((UINT)itm<m_pEscItem->seq.dwSeqLen)
			m_pEscItem->seq.ch[itm]=(unsigned char)m_ComboEscValue.GetItemData(cs);
	}
	m_ComboEscValue.ShowWindow(SW_HIDE);
	UpdateInfo();
}

void CDlgTermcapEscLine::OnCloseupComboescvalue2() 
{
	POSITION pos=m_List.GetFirstSelectedItemPosition();
	int cs=m_ComboEscValue2.GetCurSel();
	if (cs!=CB_ERR && pos && m_pEscItem)
	{
		int itm=m_List.GetNextSelectedItem(pos);
		if ((UINT)itm<m_pEscItem->seq.dwSeqLen)
			m_pEscItem->seq.ch[itm]=(unsigned char)m_ComboEscValue2.GetItemData(cs);
	}
	m_ComboEscValue2.ShowWindow(SW_HIDE);
	UpdateInfo();
}

void CDlgTermcapEscLine::OnChangeEditDescription() 
{
	if (m_pEscItem)
		m_EditDescription.GetWindowText(m_pEscItem->Description);
}

void CDlgTermcapEscLine::OnChangeEditTCName() 
{
	if (m_pEscItem)
		m_EditTCName.GetWindowText(m_pEscItem->TermcapName);
}

void CDlgTermcapEscLine::OnChangeEditGroup() 
{
	if (m_pEscItem)
		m_EditGroup.GetWindowText(m_pEscItem->GroupName);
}
