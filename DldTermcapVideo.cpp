// DldTermcapVideo.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DldTermcapVideo.h"
#include "GP_termView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDldTermcapVideo dialog


CDldTermcapVideo::CDldTermcapVideo(CWnd* pParent /*=NULL*/)
	: CDialog(CDldTermcapVideo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDldTermcapVideo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_VAttrTable=NULL;
	m_VAttrTableCount=0;
	m_VAttrTableMax=0;
	m_LockUpdate=TRUE;
	m_CurTerminalId=m_TermCap.GetCurrentTerminalId();
}


CDldTermcapVideo::~CDldTermcapVideo()
{
	if (m_VAttrTable) delete[] m_VAttrTable;
	m_VAttrTable=NULL;
}


void CDldTermcapVideo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDldTermcapVideo)
	DDX_Control(pDX, IDC_COMBOTERMINAL, m_ComboTerminal);
	DDX_Control(pDX, IDC_COMBOFRG, m_ComboFrg);
	DDX_Control(pDX, IDC_COMBOBKG, m_ComboBkg);
	DDX_Control(pDX, IDC_LIST1, m_ListCommands);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDldTermcapVideo, CDialog)
	//{{AFX_MSG_MAP(CDldTermcapVideo)
	ON_BN_CLICKED(IDC_CHECKBLINK, ComposeSequence)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_CBN_SELCHANGE(IDC_COMBOTERMINAL, OnSelchangeComboterminal)
	ON_BN_CLICKED(IDC_CHECKBOLD, ComposeSequence)
	ON_BN_CLICKED(IDC_CHECKFULL, ComposeSequence)
	ON_BN_CLICKED(IDC_CHECKGRAPH, ComposeSequence)
	ON_BN_CLICKED(IDC_CHECKITALIC, ComposeSequence)
	ON_BN_CLICKED(IDC_CHECKOPAQUE, ComposeSequence)
	ON_BN_CLICKED(IDC_CHECKUNDERLINE, ComposeSequence)
	ON_BN_CLICKED(IDC_CHECKREVERSE, ComposeSequence)
	ON_BN_CLICKED(IDC_CHECKALLOFF, ComposeSequence)
	ON_CBN_SELCHANGE(IDC_COMBOBKG, ComposeSequence)
	ON_CBN_SELCHANGE(IDC_COMBOFRG, ComposeSequence)
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDldTermcapVideo message handlers
BOOL CDldTermcapVideo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_VAttrTableCount=m_TermCap.GetVAttrTable(&m_VAttrTable);
	m_VAttrTableMax=m_VAttrTableCount;


	m_ListCommands.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_ListCommands.InsertColumn(0,"Command",LVCFMT_LEFT,150,0);
	m_ListCommands.InsertColumn(1,"ID",LVCFMT_RIGHT,60,0);
	m_ListCommands.InsertColumn(2,"Sequence of commands",LVCFMT_LEFT,500,0);
	
	m_CmdNamesArray[0]="Not used";
	m_CmdNamesArray[100]="Blink on";
	m_CmdNamesArray[101]="Blink off";
	m_CmdNamesArray[102]="Bold on";
	m_CmdNamesArray[103]="Bold off";
	m_CmdNamesArray[104]="Underline on";
	m_CmdNamesArray[105]="Underline off";
	m_CmdNamesArray[106]="Half intensity";
	m_CmdNamesArray[107]="Full intensity";
	m_CmdNamesArray[110]="Bkg - WHITE";
	m_CmdNamesArray[111]="Bkg - BROWN";
	m_CmdNamesArray[112]="Bkg - MAGENTA";
	m_CmdNamesArray[113]="Bkg - RED";
	m_CmdNamesArray[114]="Bkg - CYAN";
	m_CmdNamesArray[115]="Bkg - GREEN";
	m_CmdNamesArray[116]="Bkg - BLUE";
	m_CmdNamesArray[117]="Bkg - BLACK";
	m_CmdNamesArray[118]="Reverse color";
	m_CmdNamesArray[120]="Frg - WHITE";
	m_CmdNamesArray[121]="Frg - BROWN";
	m_CmdNamesArray[122]="Frg - MAGENTA";
	m_CmdNamesArray[123]="Frg - RED";
	m_CmdNamesArray[124]="Frg - CYAN";
	m_CmdNamesArray[125]="Frg - GREEN";
	m_CmdNamesArray[126]="Frg - BLUE";
	m_CmdNamesArray[127]="Frg - BLACK";
	m_CmdNamesArray[128]="Opaque off";
	m_CmdNamesArray[129]="Opaque on";
	m_CmdNamesArray[130]="Italic off";
	m_CmdNamesArray[131]="Italic on";
	m_CmdNamesArray[2001]="Graphic on";
	m_CmdNamesArray[2002]="Graphic off";
	m_CmdNamesArray[111111]="All attributes off";


	int idx,i;

	DWORD dwAllIdx[]={0,100,101,102,103,104,105,106,107,110,111,112,113,114,115,116,117,118,120,121,122,
		123,124,125,126,127,128,129,130,131,2001,2002,111111,};

	for(i=1;i<33;i++)
	{
		idx=m_ListCommands.InsertItem(i,m_CmdNamesArray[dwAllIdx[i]]);
		char tmps[100];
		sprintf(tmps,"%5.5d",dwAllIdx[i]);
		m_ListCommands.SetItemText(idx,1,tmps);
		m_ListCommands.SetItemData(idx,dwAllIdx[i]);
	}

	DWORD bkgIds[]={0,110,111,112,113,114,115,116,117,};
	DWORD frgIds[]={0,120,121,122,123,124,125,126,127,};
	for(i=0;i<9;i++)
	{
		idx=m_ComboBkg.AddString(m_CmdNamesArray[bkgIds[i]]);
		m_ComboBkg.SetItemData(idx,bkgIds[i]);
		idx=m_ComboFrg.AddString(m_CmdNamesArray[frgIds[i]]);
		m_ComboFrg.SetItemData(idx,frgIds[i]);
	}

	m_TermCap.FillComboTerminalType(m_ComboTerminal.m_hWnd,m_CurTerminalId);
	UpdateListFromArray();
	m_LockUpdate=FALSE;
	m_ListCommands.SetItemState(0,LVIS_SELECTED,LVIS_SELECTED);
	return TRUE;
}

void CDldTermcapVideo::OnApply() 
{
	m_TermCap.SetAVArray(m_VAttrTable,m_VAttrTableCount);
}


void CDldTermcapVideo::OnOK() 
{
	OnApply();
	m_TermCap.SaveTermCapVAttr("");
	CDialog::OnOK();
}

void CDldTermcapVideo::OnCancel() 
{
	CDialog::OnCancel();
}

void CDldTermcapVideo::ComposeSequence() 
{
	POSITION pos=m_ListCommands.GetFirstSelectedItemPosition();
	if (pos)
	{
		int nSelItem = m_ListCommands.GetNextSelectedItem(pos);
		DWORD curCommandId=m_ListCommands.GetItemData(nSelItem);
		DWORD *VAttrByCmdId=GetVAttrByCmdId(curCommandId, m_CurTerminalId);

		if (VAttrByCmdId)
		{
			if (VAttrByCmdId[1]!=m_CurTerminalId)
			{
				if (!m_VAttrTableMax || m_VAttrTableCount>=m_VAttrTableMax-1)
				{
					DWORD *tmpDword=new DWORD [(m_VAttrTableMax+100)*20];
					ZeroMemory(tmpDword, sizeof(DWORD)*(m_VAttrTableMax+100)*20);
					if (m_VAttrTable)
					{
						CopyMemory(tmpDword,m_VAttrTable,20*m_VAttrTableMax*sizeof(DWORD));
						delete[] m_VAttrTable;
					}
					m_VAttrTableMax+=100;
					m_VAttrTable=tmpDword;
					VAttrByCmdId=m_VAttrTable+m_VAttrTableCount*20;
					*VAttrByCmdId=curCommandId;
					VAttrByCmdId[1]=m_CurTerminalId;
					m_VAttrTableCount++;
				}
			}

			VAttrByCmdId+=2;
			DWORD tmpCmdId=0;

			switch(::IsDlgButtonChecked(m_hWnd,IDC_CHECKALLOFF))
			{
			case 0:	break;
			case 1:	*(VAttrByCmdId++)=111111; break;
			default:  break;
			}

			int i;
			i=m_ComboBkg.GetCurSel();
			if (i!=CB_ERR)
			{
				tmpCmdId=m_ComboBkg.GetItemData(i);
				if (tmpCmdId) *(VAttrByCmdId++)=tmpCmdId;
			}
			i=m_ComboFrg.GetCurSel();
			if (i!=CB_ERR)
			{
				tmpCmdId=m_ComboFrg.GetItemData(i);
				if (tmpCmdId) *(VAttrByCmdId++)=tmpCmdId;
			}

			switch(::IsDlgButtonChecked(m_hWnd,IDC_CHECKFULL))
			{
			case 0:	*(VAttrByCmdId++)=106; break;
			case 1:	*(VAttrByCmdId++)=107; break;
			default:  break;
			}

			switch(::IsDlgButtonChecked(m_hWnd,IDC_CHECKBLINK))
			{
			case 0:	*(VAttrByCmdId++)=101; break;
			case 1:	*(VAttrByCmdId++)=100; break;
			default:  break;
			}

			switch(::IsDlgButtonChecked(m_hWnd,IDC_CHECKBOLD))
			{
			case 0:	*(VAttrByCmdId++)=103; break;
			case 1:	*(VAttrByCmdId++)=102; break;
			default:  break;
			}

			switch(::IsDlgButtonChecked(m_hWnd,IDC_CHECKITALIC))
			{
			case 0:	*(VAttrByCmdId++)=130; break;
			case 1:	*(VAttrByCmdId++)=131; break;
			default:  break;
			}

			switch(::IsDlgButtonChecked(m_hWnd,IDC_CHECKUNDERLINE))
			{
			case 0:	*(VAttrByCmdId++)=105; break;
			case 1:	*(VAttrByCmdId++)=104; break;
			default:  break;
			}

			switch(::IsDlgButtonChecked(m_hWnd,IDC_CHECKGRAPH))
			{
			case 0:	*(VAttrByCmdId++)=2002; break;
			case 1:	*(VAttrByCmdId++)=2001; break;
			default:  break;
			}

			switch(::IsDlgButtonChecked(m_hWnd,IDC_CHECKOPAQUE))
			{
			case 0:	*(VAttrByCmdId++)=128; break;
			case 1:	*(VAttrByCmdId++)=129; break;
			default:  break;
			}

			switch(::IsDlgButtonChecked(m_hWnd,IDC_CHECKREVERSE))
			{
			case 0:	break;
			case 1:	*(VAttrByCmdId++)=118; break;
			default:  break;
			}

			*VAttrByCmdId=0;
		}
		UpdateListFromArray();
	}
}

void CDldTermcapVideo::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if ((pNMListView->uNewState&LVIS_SELECTED)==LVIS_SELECTED)
	{
		UpdateObjectsFromArray(m_ListCommands.GetItemData(pNMListView->iItem),m_CurTerminalId);
	}
	*pResult = 0;
}

void CDldTermcapVideo::OnSelchangeComboterminal() 
{
	int cursel=m_ComboTerminal.GetCurSel();
	if (cursel!=CB_ERR)
		m_CurTerminalId=m_ComboTerminal.GetItemData(cursel);

	UpdateListFromArray();
}


void CDldTermcapVideo::UpdateListFromArray() 
{
	int i;
	int nItems=m_ListCommands.GetItemCount();
	for(i=0;i<nItems;i++)
		UpdateListItemFromArray(i);
}

void CDldTermcapVideo::UpdateListItemFromArray(int iItemId) 
{
	DWORD dwData=m_ListCommands.GetItemData(iItemId);
	const DWORD *VAttrByCmdId=GetVAttrByCmdId(dwData, m_CurTerminalId);
	CString csTmp;
	if (VAttrByCmdId++)
		while(*(++VAttrByCmdId))
		{
			if (csTmp!="") csTmp+=" >> ";
			csTmp+=m_CmdNamesArray[*VAttrByCmdId];
		}

	if (csTmp=="")	csTmp=m_CmdNamesArray[0];
	m_ListCommands.SetItemText(iItemId,2,csTmp);
}

DWORD *CDldTermcapVideo::GetVAttrByCmdId(DWORD cmdID, DWORD dwTermId)
{
	static DWORD tmpRet[]={0,0};
	DWORD *ret=tmpRet;
	if (m_VAttrTable)
	{
		DWORD n=0;
		DWORD *ret0=NULL;
		DWORD *retN=NULL;

		for(n=0;n<m_VAttrTableCount;n++)
		{
			DWORD *tmppos=m_VAttrTable+n*20;
			if (*tmppos==cmdID)
			{
				if (tmppos[1]==0) ret0=tmppos;
				if (tmppos[1]==dwTermId) retN=tmppos;
			}
		}
		if (retN) ret=retN;
		else
		if (ret0) ret=ret0;
	}
	return ret;
}

void CDldTermcapVideo::UpdateObjectsFromArray(DWORD cmdID, DWORD dwTermId) 
{
	m_LockUpdate=TRUE;

	m_ComboBkg.SetCurSel(0);
	m_ComboFrg.SetCurSel(0);
	::CheckDlgButton(m_hWnd,IDC_CHECKFULL,2);
	::CheckDlgButton(m_hWnd,IDC_CHECKGRAPH,2);
	::CheckDlgButton(m_hWnd,IDC_CHECKOPAQUE,2);
	::CheckDlgButton(m_hWnd,IDC_CHECKUNDERLINE,2);
	::CheckDlgButton(m_hWnd,IDC_CHECKBLINK,2);
	::CheckDlgButton(m_hWnd,IDC_CHECKBOLD,2);
	::CheckDlgButton(m_hWnd,IDC_CHECKITALIC,2);
	::CheckDlgButton(m_hWnd,IDC_CHECKREVERSE,0);
	::CheckDlgButton(m_hWnd,IDC_CHECKALLOFF,0);

	const DWORD *VAttrByCmdId=GetVAttrByCmdId(cmdID, dwTermId);
	if (VAttrByCmdId++)
		while(*(++VAttrByCmdId))
		{
			switch(*VAttrByCmdId)
			{
			case 0:			break;
			case 100:	::CheckDlgButton(m_hWnd,IDC_CHECKBLINK,1);	break;
			case 101:	::CheckDlgButton(m_hWnd,IDC_CHECKBLINK,0);	break;
			case 102:	::CheckDlgButton(m_hWnd,IDC_CHECKBOLD,1);	break;
			case 103:	::CheckDlgButton(m_hWnd,IDC_CHECKBOLD,0);	break;
			case 104:	::CheckDlgButton(m_hWnd,IDC_CHECKUNDERLINE,1);	break;
			case 105:	::CheckDlgButton(m_hWnd,IDC_CHECKUNDERLINE,0);	break;
			case 106:	::CheckDlgButton(m_hWnd,IDC_CHECKFULL,0);	break;
			case 107:	::CheckDlgButton(m_hWnd,IDC_CHECKFULL,1);	break;
			case 110:		
			case 111:		
			case 112:		
			case 113:		
			case 114:		
			case 115:		
			case 116:		
			case 117:
				m_ComboBkg.SetCurSel(*VAttrByCmdId-110+1);
				break;
			case 118:	::CheckDlgButton(m_hWnd,IDC_CHECKREVERSE,1);
				break;
			case 120:		
			case 121:		
			case 122:		
			case 123:		
			case 124:		
			case 125:		
			case 126:		
			case 127:
				m_ComboFrg.SetCurSel(*VAttrByCmdId-120+1);
				break;
			case 128:	::CheckDlgButton(m_hWnd,IDC_CHECKOPAQUE,0);	break;
			case 129:	::CheckDlgButton(m_hWnd,IDC_CHECKOPAQUE,1);	break;
			case 130:	::CheckDlgButton(m_hWnd,IDC_CHECKITALIC,0);	break;
			case 131:	::CheckDlgButton(m_hWnd,IDC_CHECKITALIC,1);	break;
			case 2001:	::CheckDlgButton(m_hWnd,IDC_CHECKGRAPH,1);	break;
			case 2002:	::CheckDlgButton(m_hWnd,IDC_CHECKGRAPH,0);	break;
			case 111111:	::CheckDlgButton(m_hWnd,IDC_CHECKALLOFF,1);
				break;
			}
		}

	m_LockUpdate=FALSE;
}


