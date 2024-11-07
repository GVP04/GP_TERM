// DlgContextMenu.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgContextMenu.h"
#include "Scintilla\Scintilla.h"
#include "GPMenu.h"
#include "GP_TermView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CMCMD_TEST			0x0101
#define CMCMD_LOAD			0x0102
#define CMCMD_SAVE			0x0103
#define CMCMD_APPLY			0x0104
#define CMCMD_CURRENT		0x0105
#define CMCMD_ADDMENU		0x0106
#define CMCMD_ADDSUBMENU	0x0107
#define CMCMD_ADDSEPARATOR	0x0108
#define CMCMD_DELETEMENU	0x0109
#define CMCMD_MOVEUP		0x010A
#define CMCMD_MOVEDOWN		0x010B
#define CMCMD_MOVELEFT		0x010C
#define CMCMD_MOVERIGHT		0x010D
/////////////////////////////////////////////////////////////////////////////
// CDlgContextMenu dialog

CString CDlgContextMenu::LastContextMenuFile="";

CDlgContextMenu::CDlgContextMenu(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgContextMenu::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgContextMenu)
	//}}AFX_DATA_INIT
	m_Menu=new CGPContextMenu(GPC.m_View->m_GPMenu);
	DlgAutoSize=NULL;
	if (CDlgContextMenu::LastContextMenuFile=="")
		CDlgContextMenu::LastContextMenuFile=GPC.contmenuFileName;
	m_dwUpdateFlag=0;
	if (GPC.m_pContextMenu)
		*m_Menu=*GPC.m_pContextMenu;
}

CDlgContextMenu::~CDlgContextMenu()
{
	if (DlgAutoSize)
		delete DlgAutoSize;
	DlgAutoSize=NULL;
	if (m_Menu) delete m_Menu;
	m_Menu=NULL;
}


void CDlgContextMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgContextMenu)
	DDX_Control(pDX, IDC_EDIT16, m_edName);
	DDX_Control(pDX, IDC_EDIT6, m_edClip);
	DDX_Control(pDX, IDC_EDIT5, m_edDescription);
	DDX_Control(pDX, IDC_EDIT4, m_edOutput);
	DDX_Control(pDX, IDC_EDIT3, m_edText);
	DDX_Control(pDX, IDC_EDIT1, m_edId);
	DDX_Control(pDX, IDC_TREE1, m_Tree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgContextMenu, CDialog)
	//{{AFX_MSG_MAP(CDlgContextMenu)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnSelchangedTree)
	ON_NOTIFY(TVN_DELETEITEM, IDC_TREE1, OnDeleteitemTree)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEditId)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEditText)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeEditOutput)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEditDescription)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeEditClip)
	ON_EN_CHANGE(IDC_EDIT16, OnChangeEditName)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgContextMenu message handlers

LRESULT CDlgContextMenu::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	return CDialog::WindowProc(message, wParam, lParam);
}

BOOL CDlgContextMenu::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect clRect;
	GetClientRect(&clRect);

	{
		unsigned char BtnsStyle[]={
			BTNS_AUTOSIZE|BTNS_BUTTON|BTNS_SHOWTEXT|BTNS_DROPDOWN,
			TBSTYLE_SEP   ,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			TBSTYLE_SEP   ,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			TBSTYLE_SEP   ,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
		};

		unsigned char BtnsState[]={
			TBSTATE_ENABLED,
			0,
			TBSTATE_ENABLED,TBSTATE_ENABLED,TBSTATE_ENABLED,TBSTATE_ENABLED,
			0,
			TBSTATE_ENABLED,TBSTATE_ENABLED,TBSTATE_ENABLED,TBSTATE_ENABLED,
			0,
			TBSTATE_ENABLED,TBSTATE_ENABLED,TBSTATE_ENABLED,TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
		};

		DWORD BtnsStrings[]={0,(DWORD)-1,1,2,3,4,(DWORD)-1,5,6,12,7,(DWORD)-1,8,9,10,11,};
		DWORD BtnsImage[]={0,(DWORD)-1,10,5,7,13,(DWORD)-1,46,45,49,47,(DWORD)-1,41,40,42,43,};
		DWORD BtnsCommands[]={
			CMCMD_TEST,
				0,
			CMCMD_LOAD,		CMCMD_SAVE,		CMCMD_APPLY,	CMCMD_CURRENT,
				0,
			CMCMD_ADDMENU,	CMCMD_ADDSUBMENU,CMCMD_ADDSEPARATOR,CMCMD_DELETEMENU,
			0,
			CMCMD_MOVEUP,	CMCMD_MOVEDOWN,	CMCMD_MOVELEFT,	CMCMD_MOVERIGHT,
		};


		CRect re=clRect;
		re.bottom=re.top+25;
#ifndef _VC80_UPGRADE
		m_ToolBar.CreateEx(0,TOOLBARCLASSNAME,NULL,CCS_NORESIZE|CCS_NOPARENTALIGN|TBSTYLE_FLAT|TBSTYLE_LIST|TBSTYLE_TOOLTIPS|WS_CHILD|WS_VISIBLE|TBSTYLE_TRANSPARENT,re,this,12346,NULL);
#else
		m_ToolBar.CreateEx(0,CCS_NORESIZE|CCS_NOPARENTALIGN|TBSTYLE_FLAT|TBSTYLE_LIST|TBSTYLE_TOOLTIPS|WS_CHILD|WS_VISIBLE|TBSTYLE_TRANSPARENT,re,this,12346);
#endif

		m_ToolBar.SetExtendedStyle(TBSTYLE_EX_DRAWDDARROWS|TBSTYLE_EX_MIXEDBUTTONS);
		m_ToolBar.AddStrings(
#ifdef RUS
"Тест\0Загрузить\0Сохранить\0Применить\0Как текущее\0Вставить меню\0Вставить выпадающее меню\0Удалить меню\
\0Переместить вверх\0Переместить вниз\0Переместить влево\0Переместить вправо\
\0Добавить разделитель\0 \0 \0 \0 \0"
#else
"Test\0Load\0Save\0Apply\0As Current\0Insert Menu Item\0Insert Submenu\0Delete Menu\
\0Move Menu Item Up\0Move Menu Item Down\0Move Menu Item Left\0Move Menu Item Right\
\0Add Separator\0 \0 \0 \0 \0"
#endif
			);

		m_ToolBar.SetButtonSize(CSize(16,16));
		m_ToolBar.SetImageList(&GPC.a_GPImageList[GPC.GetImageListId("SEPVIEW")].m_IL);
		m_ToolBar.SetDisabledImageList(&GPC.a_GPImageList[GPC.GetImageListId("SEPVIEWDIS")].m_IL);

		TBBUTTON tbt={0};
		int i;
		for(i=0;i<16;i++)
		{
			tbt.iBitmap=BtnsImage[i];
			tbt.idCommand=BtnsCommands[i];
			tbt.iString=BtnsStrings[i];
			tbt.dwData=NULL;
			tbt.fsState=BtnsState[i];
			tbt.fsStyle=BtnsStyle[i];
			m_ToolBar.InsertButton(i,&tbt);
		}
	}

	CRect re(287,232,548,345);
	m_edOutputResult.CreateEx(WS_EX_CLIENTEDGE,"Scintilla","",WS_CHILD|WS_VISIBLE,re,this,12486,NULL);

	m_edOutputResult.ScMethod(SCI_SETREADONLY,TRUE,0);
	m_edOutputResult.ScMethod(SCI_SETVIEWWS,1,0);
	m_edOutputResult.ScMethod(SCI_SETVIEWEOL,TRUE,0);
	m_edOutputResult.ScMethod(SCI_SETWRAPMODE,1,0);
	m_edOutputResult.ScMethod(SCI_SETINDENTATIONGUIDES,1,0);

	DlgAutoSize=new GP_AutoSizing;
	DlgAutoSize->AddSetMain(m_hWnd);
	DlgAutoSize->SetMinSize(m_hWnd,clRect.Width()-100,clRect.Height()-50);

	DlgAutoSize->AddWnd(m_ToolBar.m_hWnd,this->m_hWnd,"NNNE");
	DlgAutoSize->AddWnd(m_Tree.m_hWnd,m_hWnd,"NNEP");
	DlgAutoSize->AddWnd(m_edName.m_hWnd,m_hWnd,"NPNE");
	DlgAutoSize->AddWnd(m_edText.m_hWnd,m_hWnd,"NPNE");
	DlgAutoSize->AddWnd(m_edDescription.m_hWnd,m_hWnd,"NPNE");
	DlgAutoSize->AddWnd(m_edOutput.m_hWnd,m_hWnd,"NPNE");

	DlgAutoSize->AddWnd(m_edOutputResult.m_hWnd,m_hWnd,"NPEE");
	DlgAutoSize->AddWnd(m_edClip.m_hWnd,m_hWnd,"NPNE");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_STATIC1),m_hWnd,"NPEE");

	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_STATIC2),m_hWnd,"NPNP");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_STATIC3),m_hWnd,"NPNP");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_STATIC4),m_hWnd,"NPNP");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_STATIC5),m_hWnd,"NPNP");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_STATIC6),m_hWnd,"NPNP");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_STATIC7),m_hWnd,"NPNP");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_EDITCONTEXTMENU),m_hWnd,"ENEN");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_STATICAL),m_hWnd,"ENEN");
	DlgAutoSize->AddWnd(::GetDlgItem(m_hWnd,IDC_BUTTON3),m_hWnd,"ENEN");

	m_edId.SendMessage(EM_SETCUEBANNER,0,(LPARAM)(L"ID"));
	m_edText.SendMessage(EM_SETCUEBANNER,0,(LPARAM)(L"Enter Menu text"));
	m_edDescription.SendMessage(EM_SETCUEBANNER,0,(LPARAM)(L"Enter Menu Description"));
	m_edOutput.SendMessage(EM_SETCUEBANNER,0,(LPARAM)(L"Enter Output string"));

	CWinApp *app=AfxGetApp();
	SetDlgItemText(IDC_EDITCONTEXTMENU,app->GetProfileString(GPC.cs_RegTermViewSetName, "CONTEXTMENUFILE",GPC.contmenuFileName));


	m_Menu->FillTree(m_Tree.m_hWnd,TRUE);
	OnSelchangedTree(NULL,NULL);

	return TRUE;
}

void CDlgContextMenu::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (DlgAutoSize)
		try{DlgAutoSize->UpdateSize();}catch(...){	GPC.m_ErrReport.GPWriteErrorLog("CDlgContextMenu", "OnSize","245");}
}

void CDlgContextMenu::OnDestroy()
{
	if (DlgAutoSize)
		delete DlgAutoSize;
	DlgAutoSize=NULL;
	if (m_Tree.m_hWnd) m_Tree.DeleteAllItems();

	m_edOutputResult.DestroyWindow();

	CDialog::OnDestroy();
}

BOOL CDlgContextMenu::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (m_hWnd)
	{
		HTREEITEM tsel=m_Tree.GetSelectedItem();
		BOOL bSelChange=TRUE;

		switch(LOWORD(wParam))
		{
		case CMCMD_TEST:
			break;
		case CMCMD_LOAD:
		case CMCMD_SAVE:
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
				*opf.lpstrFile=0;
				opf.nMaxFile =4900;

				opf.lpstrFile[GetDlgItemText(IDC_EDITKBD,opf.lpstrFile,4500)]=0;
				opf.Flags =OFN_DONTADDTORECENT|OFN_CREATEPROMPT|OFN_ENABLESIZING|OFN_EXPLORER|OFN_NOCHANGEDIR|OFN_SHOWHELP|OFN_LONGNAMES|OFN_PATHMUSTEXIST;
				#ifdef RUS
					opf.lpstrFilter="Текстовые файлы (*.txt)\x0*.txt\x0Все файлы\x0*.*\x0";
					opf.lpstrTitle="Выбор файла описания контекстных меню";
				#else
					opf.lpstrFilter="Text Files (*.txt)\x0*.txt\x0 All Files\x0*.*\x0";
					opf.lpstrTitle="Select User Menu File";
				#endif
				opf.lpstrDefExt="TXT";

				switch(LOWORD(wParam))
				{
				case CMCMD_LOAD:
					if (GetOpenFileName(&opf))
					{
						CDlgContextMenu::LastContextMenuFile=opf.lpstrFile;
						m_Menu->Load(CDlgContextMenu::LastContextMenuFile);
						m_Menu->FillTree(m_Tree.m_hWnd,TRUE);
					}
					break;
				case CMCMD_SAVE:
					if (GetSaveFileName(&opf))
					{
						CWinApp *app=AfxGetApp();
						GetDlgItemText(IDC_EDITCONTEXTMENU,GPC.contmenuFileName,250);
						app->WriteProfileString(GPC.cs_RegTermViewSetName, "CONTEXTMENUFILE",GPC.contmenuFileName);
						MenuFromTree(TVI_ROOT,m_Menu->m_Menu);
						CDlgContextMenu::LastContextMenuFile=opf.lpstrFile;
						m_Menu->Save(CDlgContextMenu::LastContextMenuFile);
					}
					break;
				}
				delete[] opf.lpstrFile;
			}
			break;
		case CMCMD_APPLY:
			{
				CWinApp *app=AfxGetApp();
				GetDlgItemText(IDC_EDITCONTEXTMENU,GPC.contmenuFileName,250);
				app->WriteProfileString(GPC.cs_RegTermViewSetName, "CONTEXTMENUFILE",GPC.contmenuFileName);
				MenuFromTree(TVI_ROOT,m_Menu->m_Menu);
				*GPC.m_pContextMenu=*m_Menu;
			}
			break;
		case CMCMD_CURRENT:
			*m_Menu=*GPC.m_pContextMenu;
			m_Menu->FillTree(m_Tree.m_hWnd,TRUE);
			break;
		case CMCMD_ADDSEPARATOR:
			{
				HTREEITEM tafter=TVI_LAST;
				HTREEITEM tparent=TVI_ROOT;
				if (tsel)
				{
					tparent=m_Tree.GetParentItem(tsel);
					tafter=tsel;
				}
				HTREEITEM netItem=m_Tree.InsertItem("------- SEPARATOR -------",tparent,tafter);
				m_Tree.SetItemData(netItem,0);
			}
			break;
		case CMCMD_ADDMENU:
			{
				PGPMENUINFO it=new GPMENUINFO;
				if (it)
				{
					CGPContextMenu::ClearItem(it);
					HTREEITEM tafter=TVI_LAST;
					HTREEITEM tparent=TVI_ROOT;
					if (tsel)
					{
						tparent=m_Tree.GetParentItem(tsel);
						tafter=tsel;
					}
					it->csText.Format("Menu %d",(DWORD)it);
					it->dwCmd=m_Menu->GetFreeCommand();
					if (it->dwCmd==0) it->dwCmd=2;
					HTREEITEM netItem=m_Tree.InsertItem(it->csText,tparent,tafter);
					m_Tree.SetItemData(netItem,(DWORD)it);
				}
			}
			break;
		case CMCMD_ADDSUBMENU:
			{
				PGPMENUINFO it=new GPMENUINFO;
				if (it)
				{
					CGPContextMenu::ClearItem(it);
					HTREEITEM tafter=TVI_LAST;
					HTREEITEM tparent=TVI_ROOT;
					if (tsel)
					{
						tparent=m_Tree.GetParentItem(tsel);
						tafter=tsel;
					}
					it->csText.Format("SubMenu %d",(DWORD)it);
					HTREEITEM netItem=m_Tree.InsertItem(it->csText,tparent,tafter);
					it->hSubMenu=(HMENU)-1;
					it->dwCmd=m_Menu->GetFreeSubMenuId();
					m_Tree.SetItemData(netItem,(DWORD)it);

					it=new GPMENUINFO;
					CGPContextMenu::ClearItem(it);
					it->dwCmd=m_Menu->GetFreeCommand();
					it->csText.Format("Menu %d",(DWORD)it);
					netItem=m_Tree.InsertItem(it->csText,netItem,TVI_LAST);
					m_Tree.SetItemData(netItem,(DWORD)it);
				}
			}
			break;
		case CMCMD_DELETEMENU:
			if (tsel)
				m_Tree.DeleteItem(tsel);
			break;
		case CMCMD_MOVEUP:
			if (tsel)
			{
				HTREEITEM dest=m_Tree.GetNextItem(tsel,TVGN_PREVIOUS);
				HTREEITEM parent=m_Tree.GetParentItem(tsel);
				if (dest==NULL)
				{
					dest=parent;
					if (dest!=TVI_ROOT) parent=m_Tree.GetParentItem(dest);
				}
				else
				{
					dest=m_Tree.GetNextItem(dest,TVGN_PREVIOUS);
					if (dest==NULL)	dest=TVI_FIRST;
				}
				if (dest && dest!=TVI_ROOT)
					m_Tree.SelectItem(MoveTree(parent,tsel,dest));
			}
			break;
		case CMCMD_MOVEDOWN:
			if (tsel)
			{
				HTREEITEM dest=m_Tree.GetNextItem(tsel,TVGN_NEXT);
				HTREEITEM parent=m_Tree.GetParentItem(tsel);
				if (dest)
					m_Tree.SelectItem(MoveTree(parent,tsel,dest));
			}
			break;
		case CMCMD_MOVELEFT:
			if (tsel)
			{
				HTREEITEM dest=m_Tree.GetParentItem(tsel);
				HTREEITEM parent=TVI_ROOT;

				if (dest!=TVI_ROOT)
					parent=m_Tree.GetParentItem(dest);

				if (dest && dest!=TVI_ROOT)
					m_Tree.SelectItem(MoveTree(parent,tsel,dest));
			}
			break;
		case CMCMD_MOVERIGHT:
			if (tsel)
			{
				HTREEITEM dest=tsel;
				while((dest=m_Tree.GetNextItem(dest,TVGN_NEXT)) && m_Tree.ItemHasChildren(dest)==FALSE);
				if (dest==NULL)
				{
					dest=tsel;
					while((dest=m_Tree.GetNextItem(dest,TVGN_PREVIOUS)) && m_Tree.ItemHasChildren(dest)==FALSE);
				}
				if (dest) m_Tree.SelectItem(MoveTree(dest,tsel,TVI_FIRST));
			}
			break;
		default:
			bSelChange=FALSE;
			break;
		}
		if (bSelChange) OnSelchangedTree(NULL,NULL);
	}

	return CDialog::OnCommand(wParam, lParam);
}

BOOL CDlgContextMenu::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	LPNMHDR nm=(LPNMHDR)lParam;
	if (nm)
	{
		if (nm->hwndFrom==m_ToolBar.m_hWnd)
		{
			switch(nm->code)
			{
			case TBN_DROPDOWN:
				{
					MenuFromTree(TVI_ROOT,m_Menu->m_Menu);
					LPNMTOOLBAR nmtb=(LPNMTOOLBAR)lParam;
					TBBUTTON tbb={0};
					int nItem=m_ToolBar.CommandToIndex(nmtb->iItem);
					if (nItem>=0)
					{
						m_ToolBar.GetButton(nItem,&tbb);
						CRect re;
						m_ToolBar.GetItemRect(nItem,&re);
						m_ToolBar.ClientToScreen(&re);
						::TrackPopupMenu(m_Menu->m_Menu,0,re.right-15,re.bottom,0,GPC.m_hViewWnd,NULL);
					}
				}
				break;
			}
		}
	}

	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CDlgContextMenu::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	//NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	HTREEITEM sel=m_Tree.GetSelectedItem();

	if (sel)
	{
		PGPMENUINFO mi=&(m_Menu->m_pGPMenu->MENUINFOArray[m_Tree.GetItemData(sel)]);
		if (mi)
		{
			m_dwUpdateFlag=0;
			m_edDescription.SetWindowText(mi->csDescription);
			m_edName.SetWindowText(mi->csName);
			m_edOutput.SetWindowText(mi->csOut);
			m_edText.SetWindowText(mi->csText);

			char tid[100];
			sprintf(tid,"%d",mi->dwCmd);
			m_edId.SetWindowText(tid);

			if (mi->dwCmd==0)
			{
				m_edDescription.SetReadOnly(TRUE);
				m_edId.SetReadOnly(TRUE);
				m_edOutput.SetReadOnly(TRUE);
				m_edText.SetReadOnly(TRUE);
			}
			else
			if (mi->hSubMenu)
			{
				m_edOutput.SetReadOnly(TRUE);

				m_edDescription.SetReadOnly(FALSE);
				m_edId.SetReadOnly(FALSE);
				m_edText.SetReadOnly(FALSE);
			}
			else
			{
				m_edId.SetReadOnly(TRUE);

				m_edDescription.SetReadOnly(FALSE);
				m_edOutput.SetReadOnly(FALSE);
				m_edText.SetReadOnly(FALSE);
			}


			m_dwUpdateFlag=(DWORD)-1;
		}

		m_ToolBar.EnableButton(CMCMD_DELETEMENU,TRUE);
		//up
		HTREEITEM dest=m_Tree.GetNextItem(sel,TVGN_PREVIOUS);
		if (dest==NULL)
			dest=m_Tree.GetParentItem(sel);
		else
		{
			dest=m_Tree.GetNextItem(dest,TVGN_PREVIOUS);
			if (dest==NULL)	dest=TVI_FIRST;
		}
		m_ToolBar.EnableButton(CMCMD_MOVEUP,dest && dest!=TVI_ROOT);

		dest=m_Tree.GetNextItem(sel,TVGN_NEXT);
		m_ToolBar.EnableButton(CMCMD_MOVEDOWN,dest!=NULL);

		dest=m_Tree.GetParentItem(sel);
		m_ToolBar.EnableButton(CMCMD_MOVELEFT,dest && dest!=TVI_ROOT);

		dest=sel;
		while((dest=m_Tree.GetNextItem(dest,TVGN_NEXT)) && m_Tree.ItemHasChildren(dest)==FALSE);
		if (dest==NULL)
		{
			dest=sel;
			while((dest=m_Tree.GetNextItem(dest,TVGN_PREVIOUS)) && m_Tree.ItemHasChildren(dest)==FALSE);
		}
		m_ToolBar.EnableButton(CMCMD_MOVERIGHT,dest!=NULL);
	}
	else
	{
		m_ToolBar.EnableButton(CMCMD_DELETEMENU,FALSE);
		m_ToolBar.EnableButton(CMCMD_MOVEUP,FALSE);
		m_ToolBar.EnableButton(CMCMD_MOVEDOWN,FALSE);
		m_ToolBar.EnableButton(CMCMD_MOVELEFT,FALSE);
		m_ToolBar.EnableButton(CMCMD_MOVERIGHT,FALSE);

		if (m_dwUpdateFlag)
		{
			m_dwUpdateFlag=0;

			m_edDescription.SetWindowText("");
			m_edId.SetWindowText("");
			m_edOutput.SetWindowText("");
			m_edText.SetWindowText("");

			m_edId.SetReadOnly(TRUE);
			m_edOutput.SetReadOnly(TRUE);
			m_edText.SetReadOnly(TRUE);
			m_edDescription.SetReadOnly(TRUE);

			m_dwUpdateFlag=(DWORD)-1;
		}
	}
	OnChangeEditClip();
}

BOOL CDlgContextMenu::IsChildOf(HTREEITEM hItem1/*child*/, HTREEITEM hItem2/*parent*/)
{
	HTREEITEM hParent = hItem1;
	BOOL ret=FALSE;
	while((hParent = m_Tree.GetParentItem(hParent)) != NULL && !ret)
		ret=(hParent == hItem2);

	return ret;
}

HTREEITEM CDlgContextMenu::MoveTree(HTREEITEM hDestParent, HTREEITEM hSrc, HTREEITEM insAfter)
{
	HTREEITEM ret=hSrc;
	if (IsChildOf(hDestParent,hSrc)==FALSE)
	{
		ret=CopyTree(hDestParent, hSrc, insAfter);
		m_Tree.DeleteItem(hSrc);
	}
	return ret;
}

HTREEITEM CDlgContextMenu::CopyTree(HTREEITEM hDestParent, HTREEITEM hSrc, HTREEITEM insAfter)
{
	HTREEITEM ret=hSrc;
	int nImage, nSelectedImage;
	m_Tree.GetItemImage(hSrc, nImage, nSelectedImage);
	CString string = m_Tree.GetItemText(hSrc);

	HTREEITEM hNewItem = m_Tree.InsertItem(string, nImage, nSelectedImage, hDestParent, insAfter);

	if (hNewItem)
	{
		ret=hNewItem;
		PGPMENUINFO it=new GPMENUINFO;
		CGPContextMenu::ClearItem(it);
		PGPMENUINFO itOld=&(m_Menu->m_pGPMenu->MENUINFOArray[m_Tree.GetItemData(hSrc)]);

		if (itOld)	*it=*itOld;
		m_Tree.SetItemData(hNewItem,(DWORD)it);
		if (m_Tree.ItemHasChildren(hSrc))
			CopyChildren(hNewItem, hSrc);
	}
	return ret;
}

void CDlgContextMenu::CopyChildren(HTREEITEM hDestParent, HTREEITEM hSrc)
{
	HTREEITEM hItem = m_Tree.GetChildItem(hSrc);

	if (hItem != NULL)
		do
		{
			int nImage, nSelectedImage;
			m_Tree.GetItemImage(hItem, nImage, nSelectedImage);
			CString string = m_Tree.GetItemText(hItem);
			HTREEITEM hNewItem = m_Tree.InsertItem(string, nImage, nSelectedImage, hDestParent);
			if (hNewItem)
			{
				PGPMENUINFO itOld=&(m_Menu->m_pGPMenu->MENUINFOArray[m_Tree.GetItemData(hItem)]);
				PGPMENUINFO it=new GPMENUINFO;
				CGPContextMenu::ClearItem(it);
				if (itOld)	*it=*itOld;
				m_Tree.SetItemData(hNewItem,(DWORD)it);
			}
			if (m_Tree.ItemHasChildren(hItem))
				CopyChildren(hNewItem, hItem);

		}
		while((hItem = m_Tree.GetNextSiblingItem(hItem)));
}


void CDlgContextMenu::OnDeleteitemTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	if (pNMTreeView)
	{
		if (pNMTreeView->itemOld.hItem)
		{
			PGPMENUINFO cmi=&(m_Menu->m_pGPMenu->MENUINFOArray[m_Tree.GetItemData(pNMTreeView->itemOld.hItem)]);
			if (cmi) delete cmi;
		}
	}
	*pResult = 0;
}

UINT CDlgContextMenu::MenuFromTree(HTREEITEM iItem, HMENU iHMENU)
{
	if (iItem)
	{
		HMENU mnuForChild=m_Menu->m_Menu;
		BOOL bHasChildren=FALSE;
		if (iItem==TVI_ROOT)
		{
			bHasChildren=m_Tree.GetCount()>0;
			m_Menu->DeleteAllItems();
		}
		else
		{
			bHasChildren=m_Tree.ItemHasChildren(iItem);
			GPMENUINFO MUDst;
			PGPMENUINFO cmisrc=&(m_Menu->m_pGPMenu->MENUINFOArray[m_Tree.GetItemData(iItem)]);
			MENUITEMINFO mi={0};
			mi.cbSize=sizeofMENUITEMINFO;

			if (cmisrc)
			{
				MUDst=*cmisrc;
				MUDst.hMenu=iHMENU;
				mi.dwTypeData=(char *)(LPCSTR)MUDst.csText;
				mi.cch=MUDst.csText.GetLength();

				if (bHasChildren)
				{
					//SUBMENU
					MUDst.hSubMenu=::CreatePopupMenu();
					MUDst.dwCmd=m_Menu->GetFreeSubMenuId();
				#ifdef W_95
					mi.fMask=MIIM_SUBMENU|MIIM_TYPE;
					mi.fType=MFT_STRING;
				#else
					#ifdef W_NT
						mi.fMask=MIIM_SUBMENU|MIIM_TYPE;
						mi.fType=MFT_STRING;
					#else
						mi.fMask=MIIM_SUBMENU|MIIM_STRING;
					#endif
				#endif
					mnuForChild=mi.hSubMenu=MUDst.hSubMenu;
				}
				else
				if (MUDst.dwCmd)
				{
					//MENUITEM
					MUDst.dwCmd=m_Menu->GetFreeCommand();
					#ifdef W_95
						mi.fMask=MIIM_TYPE|MIIM_ID;
						mi.fType=MFT_STRING;
					#else
						#ifdef W_NT
							mi.fMask=MIIM_TYPE|MIIM_ID;
							mi.fType=MFT_STRING;
						#else
							mi.fMask=MIIM_STRING|MIIM_ID;
						#endif
					#endif
					mi.wID=MUDst.dwCmd;
				}
				else
				{
					bHasChildren=FALSE;
					MUDst.hMenu=iHMENU;
					MUDst.csText="SEPARATOR";
					MUDst.csDescription=MUDst.csText;
					MUDst.csName=MUDst.csText;
					MUDst.dwCmd=0;

					#ifdef W_95
						mi.fMask=MIIM_TYPE;
					#else
						#ifdef W_NT
							mi.fMask=MIIM_TYPE;
						#else
							mi.fMask=MIIM_FTYPE;
						#endif
					#endif

					mi.fType=MFT_SEPARATOR;
				}
				DWORD item=m_Menu->AddItem();
				mi.dwItemData=m_Menu->m_ArrayIdMenuInfo[item]=m_Menu->m_pGPMenu->RegisterMenuItem(MUDst);
				::InsertMenuItem(MUDst.hMenu,(DWORD)-1,TRUE,&mi);
			}
		}

		if (bHasChildren)
		{
			HTREEITEM itc=m_Tree.GetChildItem(iItem);
			while(itc)
			{
				MenuFromTree(itc,mnuForChild);
				itc=m_Tree.GetNextSiblingItem(itc);
			}
		}
	}

	return 0;
}


void CDlgContextMenu::OnChangeEditId()
{
	if (m_dwUpdateFlag)
	{
		HTREEITEM sel=m_Tree.GetSelectedItem();
		if (sel)
		{
			PGPMENUINFO mi=&(m_Menu->m_pGPMenu->MENUINFOArray[m_Tree.GetItemData(sel)]);
			if (mi)
			{
				CString tmps=m_GetWndText(m_edId.m_hWnd);
				mi->dwCmd=atoi(tmps);
			}
		}
	}
}

void CDlgContextMenu::OnChangeEditText()
{
	if (m_dwUpdateFlag)
	{
		HTREEITEM sel=m_Tree.GetSelectedItem();
		if (sel)
		{
			PGPMENUINFO mi=&(m_Menu->m_pGPMenu->MENUINFOArray[m_Tree.GetItemData(sel)]);
			if (mi)
			{
				mi->csText=m_GetWndText(m_edText.m_hWnd);
				m_Tree.SetItemText(sel,mi->csText);
			}
		}
	}
}

void CDlgContextMenu::OnChangeEditOutput()
{
	if (m_dwUpdateFlag)
	{
		HTREEITEM sel=m_Tree.GetSelectedItem();
		if (sel)
		{
			PGPMENUINFO mi=&(m_Menu->m_pGPMenu->MENUINFOArray[m_Tree.GetItemData(sel)]);
			if (mi)
			{
				mi->csOut=m_GetWndText(m_edOutput.m_hWnd);
				OnChangeEditClip();
			}
		}
	}
}

void CDlgContextMenu::OnChangeEditDescription()
{
	if (m_dwUpdateFlag)
	{
		HTREEITEM sel=m_Tree.GetSelectedItem();
		if (sel)
		{
			PGPMENUINFO mi=&(m_Menu->m_pGPMenu->MENUINFOArray[m_Tree.GetItemData(sel)]);
			if (mi) mi->csDescription=m_GetWndText(m_edDescription.m_hWnd);
		}
	}
}

void CDlgContextMenu::OnChangeEditName()
{
	if (m_dwUpdateFlag)
	{
		HTREEITEM sel=m_Tree.GetSelectedItem();
		if (sel)
		{
			PGPMENUINFO mi=&(m_Menu->m_pGPMenu->MENUINFOArray[m_Tree.GetItemData(sel)]);
			if (mi) mi->csName=m_GetWndText(m_edName.m_hWnd);
		}
	}
}

void CDlgContextMenu::OnChangeEditClip()
{
	CString tmps=m_GetWndText(m_edClip.m_hWnd);
	m_edOutputResult.ScMethod(SCI_SETREADONLY,0,0);
	m_edOutputResult.SetText(CGPContextMenu::ConvertToOutput(m_GetWndText(m_edOutput.m_hWnd),tmps),SC_REPLACE_ALL);
	m_edOutputResult.ScMethod(SCI_SETREADONLY,1,0);
}

CString CDlgContextMenu::m_GetWndText(HWND iHWND)
{
	CString tmps;
	if (iHWND)
	{
		int nnn=::GetWindowTextLength(iHWND);
		char *buff=new char [nnn+10];
		if (nnn) nnn=::GetWindowText(iHWND,buff,nnn+2);
		buff[nnn]=0;
		tmps=buff;
		tmps.Replace("\n","\\n");
		tmps.Replace("\r","\\r");
		tmps.Replace("\t","\\t");
		delete[] buff;
	}
	return tmps;
}

void CDlgContextMenu::OnButton3() 
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
	*opf.lpstrFile=0;
	opf.nMaxFile =4900;
	opf.lpstrFile[GetDlgItemText(IDC_EDITKBD,opf.lpstrFile,4500)]=0;
	opf.Flags =OFN_DONTADDTORECENT|OFN_CREATEPROMPT|OFN_ENABLESIZING|OFN_EXPLORER|OFN_NOCHANGEDIR|OFN_SHOWHELP|OFN_LONGNAMES|OFN_PATHMUSTEXIST;

#ifdef RUS
	opf.lpstrFilter="Текстовые файлы (*.txt)\x0*.txt\x0Все файлы\x0*.*\x0";
#else
	opf.lpstrFilter="Text Files (*.txt)\x0*.txt\x0 All Files\x0*.*\x0";
#endif
	opf.lpstrDefExt="TXT";


	if (GetOpenFileName(&opf))
	{
		SetDlgItemText(IDC_EDITCONTEXTMENU,opf.lpstrFile);
	}
	delete[] opf.lpstrFile;

	
}
