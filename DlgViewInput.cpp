// DlgViewInput.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgViewInput.h"
#include "GP_TermView.h"
#include "DlgViewInputSet.h"
#include "Scintilla\Scintilla.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
// CDlgViewInput dialog


CDlgViewInput::CDlgViewInput(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgViewInput)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_CDlgViewInputSetPtr=NULL;
	m_Editor=new GPViewInput(123456);
	m_uSelectionFlag=0;
	m_Editor->m_csDefClFileName="TS.TXT";
	m_Editor->m_csDefSrvFileName="TS";
	m_Editor->m_csDefSrvItemName="@user";
	DlgAutoSize=NULL;
}

CDlgViewInput::~CDlgViewInput()
{
	if (DlgAutoSize)
		delete DlgAutoSize;
	DlgAutoSize=NULL;
	if (m_Editor)
		delete m_Editor;
	m_Editor=NULL;
}

void CDlgViewInput::OnDestroy()
{
	AfxGetApp()->WriteProfileString("SEP_OUTPUT_SET","m_csDefClFileName",m_Editor->m_csDefClFileName);
	AfxGetApp()->WriteProfileString("SEP_OUTPUT_SET","m_csDefSrvFileName",m_Editor->m_csDefSrvFileName);
	AfxGetApp()->WriteProfileString("SEP_OUTPUT_SET","m_csDefSrvItemName",m_Editor->m_csDefSrvItemName);

	if (DlgAutoSize)
		delete DlgAutoSize;
	DlgAutoSize=NULL;

	CDialog::OnDestroy();
}

void CDlgViewInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgViewInput)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgViewInput, CDialog)
	//{{AFX_MSG_MAP(CDlgViewInput)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgViewInput message handlers

BOOL CDlgViewInput::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Editor->m_csDefClFileName=AfxGetApp()->GetProfileString("SEP_OUTPUT_SET","m_csDefClFileName",m_Editor->m_csDefClFileName);
	m_Editor->m_csDefSrvFileName=AfxGetApp()->GetProfileString("SEP_OUTPUT_SET","m_csDefSrvFileName",m_Editor->m_csDefSrvFileName);
	m_Editor->m_csDefSrvItemName=AfxGetApp()->GetProfileString("SEP_OUTPUT_SET","m_csDefSrvItemName",m_Editor->m_csDefSrvItemName);

	DlgAutoSize=new GP_AutoSizing;
	DlgAutoSize->AddSetMain(this->m_hWnd);

	CRect clRect;
	GetClientRect(&clRect);

	{
		unsigned char BtnsStyle[]={
			BTNS_AUTOSIZE|BTNS_BUTTON|/*BTNS_SHOWTEXT|*/BTNS_DROPDOWN,
			BTNS_AUTOSIZE|BTNS_BUTTON|/*BTNS_SHOWTEXT|*/BTNS_DROPDOWN,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			TBSTYLE_SEP   ,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			TBSTYLE_SEP   ,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			TBSTYLE_SEP   ,
			BTNS_AUTOSIZE|BTNS_BUTTON|BTNS_CHECK,
			TBSTYLE_SEP   ,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			TBSTYLE_SEP   ,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			TBSTYLE_SEP   ,
			BTNS_AUTOSIZE|BTNS_BUTTON|BTNS_DROPDOWN,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			TBSTYLE_SEP   ,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
		};

		unsigned char BtnsState[]={
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			0,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			0,
			TBSTATE_ENABLED,
			0,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			0,
			TBSTATE_ENABLED,
			0,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			0,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			0,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			0,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
		};

		DWORD BtnsStrings[]={0,1,21,-1,16,17,-1,2,3,4,5,6,-1,7,-1,8,9,-1,10,11,12,13,14,-1,15,18,-1,19,20,};
		DWORD BtnsImage[]={10,2,50,-1,19,20,-1,9,8,7,0,1,-1,6,-1,11,12,-1,13,14,15,17,21,-1,18,24,-1,34,35,};
		DWORD BtnsCommands[]={
			SCCMND_LOADCLIENT,
			SCCMND_SAVECLIENT,
			SCCMND_PRINT,
			0,
			SCCMND_UNDO,
			SCCMND_REDO,
			0,
			SCCMND_EXECUTE,
			SCCMND_EXECUTEREPEAT,
			SCCMND_EXECUTEENTER,
			SCCMND_BREAK,
			SCCMND_SOFTBREAK,
			0,
			SCCMND_DIRECTINPUT,
			0,
			SCCMND_ZOOMIN,
			SCCMND_ZOOMOUT,
			0,
			SCCMND_MARKERADD,
			SCCMND_MARKERPREV,
			SCCMND_MARKERNEXT,
			SCCMND_MARKERDELETEALL,
			SCCMND_MARKERTYPENEXT,
			0,
			SCCMND_SORTASC,
			SCCMND_FINDDIALOG,
			0,
			SCCMND_WNDSIZE,
			SCCMND_WNDSIZE2,
		};


		CRect re=clRect;
		re.bottom=re.top+25;
#ifndef _VC80_UPGRADE
		m_ToolBar.CreateEx(0,TOOLBARCLASSNAME,NULL,CCS_NORESIZE|CCS_NOPARENTALIGN|TBSTYLE_FLAT|TBSTYLE_LIST|TBSTYLE_TOOLTIPS|WS_CHILD|WS_VISIBLE|TBSTYLE_TRANSPARENT,re,this,12346,NULL);
#else
		m_ToolBar.CreateEx(0,CCS_NORESIZE|CCS_NOPARENTALIGN|TBSTYLE_FLAT|TBSTYLE_LIST|TBSTYLE_TOOLTIPS|WS_CHILD|WS_VISIBLE|TBSTYLE_TRANSPARENT,re,this,12346);
#endif
		m_ToolBar.SetExtendedStyle(TBSTYLE_EX_DRAWDDARROWS|TBSTYLE_EX_MIXEDBUTTONS);
		DlgAutoSize->AddWnd(m_ToolBar.m_hWnd,this->m_hWnd,"NNNE");
		m_ToolBar.AddStrings(
#ifdef RUS
"Загрузить\0Сохранить\
\0Выполнить\0Повторить\0Enter\0Прервать\0Закончить\
\0Прямой ввод\
\0Увеличить\0Уменьшить\
\0Добавить/удалить закладку (Ctrl+F2)\0Предыдущая закладка (Shift+F2)\0Следующая закладка (F2)\0Удалить все закладки\0Сменить тип закладки (Ctrl+Shift+F2)\
\0Сортировать абзацы\
\0UNDO\0REDO\
\0Найти/Заменить\0Максимальный размер окна вывода\0Увеличить размер окна ввода\0Печатать\0 \0 \0"
#else
"Load\0Save\
\0Execute\0Repeat\0Enter\0Break\0Soft Break\
\0Direct Input\
\0ZoomIn\0ZoomOut\
\0Add/Delete Bookmark (Ctrl+F2)\0Previous Bookmark (Shift+F2)\0Next Bookmark (F2)\0Delete all Bookmarks\0Change Bookmark Type (Ctrl+Shift+F2)\
\0Sort paragraph\
\0UNDO\0REDO\
\0Find & Replace\0Maximize Size Of Output Window\0Enrarge Input Window\0Print\0 \0 \0 \0 \0 \0 \0 \0 \0"
#endif
			);

		m_ToolBar.SetButtonSize(CSize(16,16));
		m_ToolBar.SetImageList(&GPC.a_GPImageList[GPC.GetImageListId("SEPVIEW")].m_IL);
		m_ToolBar.SetDisabledImageList(&GPC.a_GPImageList[GPC.GetImageListId("SEPVIEWDIS")].m_IL);

		TBBUTTON tbt={0};
		int i;
		for(i=0;i<IVTOOLBAR_NBTNS;i++)
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

	if (m_Editor)
	{
		CRect re=clRect;
		re.top+=26;
		m_Editor->CreateEx(WS_EX_CLIENTEDGE,"Scintilla","",WS_CHILD|WS_VISIBLE,re,this,12346,NULL);
		DlgAutoSize->AddWnd(m_Editor->m_hWnd,this->m_hWnd,"NNEE");
	}

	return TRUE;
}

void CDlgViewInput::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if (DlgAutoSize)
		try{DlgAutoSize->UpdateSize();}catch(...){GPC.m_ErrReport.GPWriteErrorLog("CDlgViewInput", "OnSize","");}
}

int CDlgViewInput::AppendCharToInput(char iCh)
{
	int ret=iCh;
	if (m_Editor)
		ret=m_Editor->AppendChar(iCh,m_uSelectionFlag);

	return ret;
}

char *CDlgViewInput::AppendStringToInput(const char *iStr)
{
	char * ret=(char *)iStr;
	if (m_Editor)
		ret=m_Editor->AppendString(iStr,m_uSelectionFlag);

	return ret;
}

BOOL CDlgViewInput::OnCommand(WPARAM wParam, LPARAM lParam)
{
	UINT command=(wParam&0xFFFF);
	if ((command==1 || command==2) && lParam==0) return TRUE;

	if ((HWND)lParam==m_ToolBar.m_hWnd || (m_Editor && (HWND)lParam==m_Editor->m_hWnd) || lParam==NULL)
	{
		//int cm=m_ToolBar.CommandToIndex(LOWORD(wParam));

		switch(LOWORD(wParam))
		{
		case SCCMND_PRINT:
			if (m_Editor)
				m_Editor->Print(3,"");
			break;
		case SCCMND_BREAK:
			if (GPC.AjCheckState==0)
				GPC.m_View->SendChar(GPC.BreakChar);
			break;
		case SCCMND_SOFTBREAK:
			if (m_Editor->m_csSoftBreakSeq!="")
			{
				CString fld=" ";
				int i;
				for(i=1;i<100 && fld!="";i++)
				{
					fld=ExtractField(m_Editor->m_csSoftBreakSeq,i," ");
					if (fld!="")
					{
						char c=atoi(fld);
						GPC.m_View->SendChar(c);
					}
				}
			}
			break;
		case SCCMND_EXECUTE:
			if (m_Editor)
				m_Editor->ExecCurent();
			m_ToolBar.EnableButton(SCCMND_EXECUTEREPEAT);
			break;
		case SCCMND_EXECUTEREPEAT:
			if (m_Editor)
				m_Editor->ExecuteLast();
			break;
		case SCCMND_EXECUTEENTER:
			GPC.m_View->SendChar('\r');
			break;
		case SCCMND_DIRECTINPUT:
			m_Editor->m_DirectInputFlag=m_ToolBar.IsButtonChecked(SCCMND_DIRECTINPUT);
			if (m_CDlgViewInputSetPtr)
			{
				m_CDlgViewInputSetPtr->m_dwInputSet&=(0xFFFFFFFF^CDVIS_DIRECTINPUT);
				if (m_Editor->m_DirectInputFlag)
					m_CDlgViewInputSetPtr->m_dwInputSet|=CDVIS_DIRECTINPUT;
				m_CDlgViewInputSetPtr->UpdateCtrls();
			}
			break;
		case SCCMND_SAVECLIENT:
			m_Editor->SaveText(m_Editor->m_csDefClFileName,SC_SAVE_ALL|SC_SAVE_REPLACE);
			break;
		case SCCMND_SAVESERVER:
			m_Editor->SaveOnServerSide(m_Editor->m_csDefSrvFileName, m_Editor->m_csDefSrvItemName,SC_SAVE_ALL|SC_SAVE_REPLACE);
			break;
		case SCCMND_SAVESELCLIENT:
			m_Editor->SaveText(m_Editor->m_csDefClFileName,SC_SAVE_SELECTION|SC_SAVE_REPLACE);
			break;
		case SCCMND_SAVESELSERVER:
			m_Editor->SaveOnServerSide(m_Editor->m_csDefSrvFileName, m_Editor->m_csDefSrvItemName,SC_SAVE_SELECTION|SC_SAVE_REPLACE);
			break;
		case SCCMND_SAVECLIENTAS:
			{
				CString name="";
				m_Editor->SaveText(name,SC_SAVE_ALL|SC_SAVE_REPLACE);
			}
			break;
		case SCCMND_SAVESERVERAS:
			{
				CString name="";
				CString name2="";
				m_Editor->SaveOnServerSide(name,name2,SC_SAVE_ALL|SC_SAVE_REPLACE);
			}
			break;
		case SCCMND_SAVESELCLIENTAS:
			{
				CString name="";
				m_Editor->SaveText(name,SC_SAVE_SELECTION|SC_SAVE_REPLACE);
			}
			break;
		case SCCMND_SAVESELSERVERAS:
			{
				CString name="";
				CString name2="";
				m_Editor->SaveOnServerSide(name,name2,SC_SAVE_SELECTION|SC_SAVE_REPLACE);
			}
			break;
		case SCCMND_LOADCLIENT:
			m_Editor->LoadText(m_Editor->m_csDefClFileName,SC_REPLACE_ALL);
			break;
		case SCCMND_LOADCLIENTFROM:
			{
				CString name="";
				m_Editor->LoadText(name,SC_REPLACE_ALL);
			}
			break;
		case SCCMND_LOADSERVER:
			m_Editor->LoadFromServerSide(m_Editor->m_csDefSrvFileName, m_Editor->m_csDefSrvItemName,SC_REPLACE_ALL);
			break;
		case SCCMND_LOADSERVERFROM:
			{
				CString name="";
				CString name2="";
				m_Editor->LoadFromServerSide(name,name2,SC_REPLACE_ALL);
			}
			break;
		case SCCMND_LOADINSCLIENT:
			m_Editor->LoadText(m_Editor->m_csDefClFileName,SC_REPLACE_SELECTION|SC_REPLACE_SCROLL);
			break;
		case SCCMND_LOADINSCLIENTFROM:
			{
				CString name="";
				m_Editor->LoadText(name,SC_REPLACE_SELECTION|SC_REPLACE_SCROLL);
			}
			break;
		case SCCMND_LOADINSSERVER:
			m_Editor->LoadFromServerSide(m_Editor->m_csDefSrvFileName, m_Editor->m_csDefSrvItemName,SC_REPLACE_SELECTION|SC_REPLACE_SCROLL);
			break;
		case SCCMND_LOADINSSERVERFROM:
			{
				CString name="";
				CString name2="";
				m_Editor->LoadFromServerSide(name,name2,SC_REPLACE_SELECTION|SC_REPLACE_SCROLL);
			}
			break;
		case SCCMND_ZOOMIN:		m_Editor->ScMethod(SCI_ZOOMIN,0,0);		break;
		case SCCMND_ZOOMOUT:	m_Editor->ScMethod(SCI_ZOOMOUT,0,0);	break;
		case SCCMND_MARKERADD:
			{
				int position=m_Editor->ScMethod(SCI_GETCURRENTPOS,0,0);
				int curline=m_Editor->ScMethod(SCI_LINEFROMPOSITION,position,0);
				if ((m_Editor->ScMethod(SCI_MARKERGET,curline,0)&GPScintilla::uArrMarkerMask[m_Editor->m_CurMarkerType])!=GPScintilla::uArrMarkerMask[m_Editor->m_CurMarkerType])
					m_Editor->ScMethod(SCI_MARKERADD,curline,m_Editor->m_CurMarkerType);
				else
				{
					position=m_Editor->ScMethod(SCI_GETCURRENTPOS,0,0);
					curline=m_Editor->ScMethod(SCI_LINEFROMPOSITION,position,0);
					m_Editor->ScMethod(SCI_MARKERDELETE,curline,m_Editor->m_CurMarkerType);
				}
			}
			break;
		case SCCMND_MARKERTYPENEXT:
			{
				TBBUTTONINFO tbbi={0};

				tbbi.cbSize=sizeof(tbbi);
				tbbi.dwMask=TBIF_COMMAND|TBIF_IMAGE;
				tbbi.idCommand=SCCMND_MARKERTYPENEXT;

				m_Editor->m_CurMarkerType=(++m_Editor->m_CurMarkerType)%3;
				m_ToolBar.GetButtonInfo(SCCMND_MARKERTYPENEXT,&tbbi);
				tbbi.iImage=21+m_Editor->m_CurMarkerType;
				m_ToolBar.SetButtonInfo(SCCMND_MARKERTYPENEXT,&tbbi);
			}
			break;
		case SCCMND_MARKERNEXT:
		case SCCMND_MARKERPREV:
			{
				int position=m_Editor->ScMethod(SCI_GETCURRENTPOS,0,0);
				int curline=m_Editor->ScMethod(SCI_LINEFROMPOSITION,position,0);
				int nLines=m_Editor->ScMethod(SCI_GETLINECOUNT,0,0);

				if (LOWORD(wParam)==SCCMND_MARKERNEXT)
				{
					curline++;
					if (curline==nLines) curline=0;
					curline=m_Editor->ScMethod(SCI_MARKERNEXT,curline,GPScintilla::uArrMarkerMask[m_Editor->m_CurMarkerType]);
					if (curline<0)
						curline=m_Editor->ScMethod(SCI_MARKERNEXT,0,GPScintilla::uArrMarkerMask[m_Editor->m_CurMarkerType]);
				}
				else
				{
					curline--;
					if (curline<0) curline=nLines-1;
					curline=m_Editor->ScMethod(SCI_MARKERPREVIOUS,curline,GPScintilla::uArrMarkerMask[m_Editor->m_CurMarkerType]);
					if (curline<0)
						curline=m_Editor->ScMethod(SCI_MARKERPREVIOUS,nLines-1,GPScintilla::uArrMarkerMask[m_Editor->m_CurMarkerType]);
				}

				if (curline<0)
					MessageBeep(MB_ICONASTERISK);
				else
					m_Editor->ScMethod(SCI_GOTOLINE,curline,0);
			}
			break;
		case SCCMND_MARKERDELETEALL:
			m_Editor->ScMethod(SCI_MARKERDELETEALL,m_Editor->m_CurMarkerType,0);
			break;
		case SCCMND_SORTASC:
			m_Editor->SortText(SC_SORT_ASC|SC_SORT_PARA);
			break;
		case SCCMND_SORTDESC:
			m_Editor->SortText(SC_SORT_DESC|SC_SORT_PARA);
			break;
		case SCCMND_SORTWORDSASC:
			m_Editor->SortText(SC_SORT_ASC|SC_SORT_WORDS);
			break;
		case SCCMND_SORTWORDSDESC:
			m_Editor->SortText(SC_SORT_DESC|SC_SORT_WORDS);
			break;
		case SCCMND_SORTUNIQUETASC:
			m_Editor->SortText(SC_SORT_ASC|SC_SORT_PARA|SC_SORT_UNIQUE);
			break;
		case SCCMND_SORTUNIQUETDESC:
			m_Editor->SortText(SC_SORT_DESC|SC_SORT_PARA|SC_SORT_UNIQUE);
			break;
		case SCCMND_SORTUNIQUETWORDSASC:
			m_Editor->SortText(SC_SORT_ASC|SC_SORT_WORDS|SC_SORT_UNIQUE);
			break;
		case SCCMND_SORTUNIQUETWORDSDESC:
			m_Editor->SortText(SC_SORT_DESC|SC_SORT_WORDS|SC_SORT_UNIQUE);
			break;
		case SCCMND_REDO:
			m_Editor->ScMethod(SCI_REDO,0,0);
			break;
		case SCCMND_UNDO:
			m_Editor->ScMethod(SCI_UNDO,0,0);
			break;
		case SCCMND_FINDDIALOG:
			m_Editor->ShowFindDialog(1);
			break;
		case SCCMND_WNDSIZE:
			GetParent()->GetParent()->SendMessage(GPN_UPDATESIZE,SCCMND_WNDSIZE+0x10000,0);
			break;
		case SCCMND_WNDSIZE2:
			GetParent()->GetParent()->SendMessage(GPN_UPDATESIZE,SCCMND_WNDSIZE2+0x10000,0);
			break;
		default:
			break;
		}
	}

	return CDialog::OnCommand(wParam, lParam);
}

BOOL CDlgViewInput::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
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
					LPNMTOOLBAR nmtb=(LPNMTOOLBAR)lParam;
					TBBUTTON tbb={0};
					int nItem=m_ToolBar.CommandToIndex(nmtb->iItem);
					if (nItem>=0)
					{
						m_ToolBar.GetButton(nItem,&tbb);
						CRect re;
						m_ToolBar.GetItemRect(nItem,&re);
						m_ToolBar.ClientToScreen(&re);
						switch((tbb.idCommand&SCCMND_TYPEMASK))
						{
						case SCCMND_TYPEMISC:
							break;
						case SCCMND_TYPEBREAK:
							break;
						case SCCMND_TYPEEXECUTE:
							break;
						case SCCMND_TYPESAVE:
						case SCCMND_TYPELOAD:
						case SCCMND_TYPESORT:
							{
								HMENU m_Menu=GPScintilla::SCCreatePopupMenu((tbb.idCommand&SCCMND_TYPEMASK));
								if (m_Menu)
								{
									::TrackPopupMenu(m_Menu,0,re.right-15,re.bottom,0,m_hWnd,NULL);
									if (m_Menu) ::DestroyMenu(m_Menu);
								}
							}
							break;
						}
					}
				}
				break;
			}
		}
	}

	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CDlgViewInput::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	DWORD modifKey=0;
	BOOL DoBase=TRUE;

	if ((GetAsyncKeyState(VK_RWIN)&0xFF00) || (GetAsyncKeyState(VK_LWIN)&0xFF00))		modifKey|=MOD_WIN;
	if ((GetAsyncKeyState(VK_LSHIFT)&0xFF00) || (GetAsyncKeyState(MOD_SHIFT)&0xFF00))	modifKey|=MOD_SHIFT;
	if ((GetAsyncKeyState(VK_CONTROL)&0xFF00) || (GetAsyncKeyState(VK_RCONTROL)&0xFF00) || (GetAsyncKeyState(VK_LCONTROL)&0xFF00)) modifKey|=MOD_CONTROL;
	if ((GetAsyncKeyState(MOD_ALT)&0xFF00) || (GetAsyncKeyState(VK_RMENU)&0xFF00) || (GetAsyncKeyState(VK_LMENU)&0xFF00)) modifKey|=MOD_ALT;

	switch(nChar)
	{
	case VK_F2:
		if (modifKey==0)			DoBase=FALSE,OnCommand(SCCMND_MARKERNEXT,0);
		if (modifKey==MOD_CONTROL)	DoBase=FALSE,OnCommand(SCCMND_MARKERADD,0);
		if (modifKey==MOD_SHIFT)	DoBase=FALSE,OnCommand(SCCMND_MARKERPREV,0);
		if (modifKey==(MOD_SHIFT|MOD_CONTROL))	DoBase=FALSE,OnCommand(SCCMND_MARKERTYPENEXT,0);
		break;
	}


	if (DoBase) CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

LRESULT CDlgViewInput::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{

	return CDialog::WindowProc(message, wParam, lParam);
}

void CDlgViewInput::UpdateTB()
{
	m_ToolBar.CheckButton(SCCMND_DIRECTINPUT,m_Editor->m_DirectInputFlag!=0);
}
