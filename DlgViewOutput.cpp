// DlgViewOutput.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgViewOutput.h"
#include "GPToolBarCtrl.h"
#include "DlgViewOutputSet.h"
#include "Scintilla\Scintilla.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgViewOutput dialog

#define CDVO_TIMER_1			0x1
#define CDVO_TIMER_2			0x2
#define CDVO_TIMER_SIZECHECK	0x10

CDlgViewOutput::CDlgViewOutput(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewOutput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgViewOutput)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_CDlgViewOutputSetPtr=NULL;
	m_csLastParentSize.cx=0;
	m_csLastParentSize.cy=0;
	DlgAutoSize=NULL;
	m_Editor=new GPViewOutput(123456);
	m_uSelectionFlag=0;
	m_RedirectInput=0;
	m_InDataFlag=0;
	InitializeCriticalSection(&m_CSOutputView);
	m_Delay1=200;
	m_Delay2=400;
	m_LastTransfer=0;
 	m_nMaxOutputLen=2000;
	m_nOutputLenDecr=1500;

	m_nMaxOutputLen=AfxGetApp()->GetProfileInt("SEP_OUTPUT_SET", "m_nMaxOutputLen",500000);
	m_nOutputLenDecr=AfxGetApp()->GetProfileInt("SEP_OUTPUT_SET", "m_nOutputLenDecr",75);

	m_Editor->m_csDefClFileName="OUTPUT.TXT";
	m_Editor->m_csDefSrvFileName="TS";
	m_Editor->m_csDefSrvItemName="OUTPUT@user";
}

CDlgViewOutput::~CDlgViewOutput()
{
	if (DlgAutoSize)
		delete DlgAutoSize;
	DlgAutoSize=NULL;
	if (m_Editor)
		delete m_Editor;
	m_Editor=NULL;
	DeleteCriticalSection(&m_CSOutputView);
}

void CDlgViewOutput::OnDestroy()
{
	if (m_Editor && m_Editor->m_hWnd)
		m_Editor->CloseFindDialog();

	if (DlgAutoSize)
		delete DlgAutoSize;
	DlgAutoSize=NULL;
	CDialog::OnDestroy();
}

void CDlgViewOutput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgViewOutput)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgViewOutput, CDialog)
	//{{AFX_MSG_MAP(CDlgViewOutput)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgViewOutput message handlers

BOOL CDlgViewOutput::OnInitDialog()
{
	CDialog::OnInitDialog();
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

		DWORD BtnsStrings[]={0,1,21,-1,16,17,-1,7,-1,8,9,-1,10,11,12,13,14,-1,15,18,-1,19,20,};
		DWORD BtnsImage[]={10,2,50,-1,19,20,-1,6,-1,11,12,-1,13,14,15,17,21,-1,18,24,-1,34,35,};
		DWORD BtnsCommands[]={
			SCCMND_LOADCLIENT,
			SCCMND_SAVECLIENT,
			SCCMND_PRINT,
			0,
			SCCMND_UNDO,
			SCCMND_REDO,
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
		re.top+=1;
		re.bottom=re.top+24;
#ifndef _VC80_UPGRADE
		m_ToolBar.CreateEx(0,TOOLBARCLASSNAME,NULL,CCS_NODIVIDER|CCS_NORESIZE|CCS_NOPARENTALIGN|TBSTYLE_FLAT|TBSTYLE_LIST|TBSTYLE_TOOLTIPS|WS_CHILD|WS_VISIBLE|TBSTYLE_TRANSPARENT,re,this,12346,NULL);
#else
		m_ToolBar.CreateEx(0,CCS_NODIVIDER|CCS_NORESIZE|CCS_NOPARENTALIGN|TBSTYLE_FLAT|TBSTYLE_LIST|TBSTYLE_TOOLTIPS|WS_CHILD|WS_VISIBLE|TBSTYLE_TRANSPARENT,re,this,12346);
#endif
		m_ToolBar.SetExtendedStyle(TBSTYLE_EX_DRAWDDARROWS|TBSTYLE_EX_MIXEDBUTTONS);
		DlgAutoSize->AddWnd(m_ToolBar.m_hWnd,this->m_hWnd,"NNNE");

		m_ToolBar.AddStrings(
#ifdef RUS
"Загрузить\0Сохранить\
\0 \0 \0 \0 \0 \
\0Прямой ввод\
\0Увеличить\0Уменьшить\
\0Добавить/удалить закладку (Ctrl+F2)\0Предыдущая закладка (Shift+F2)\0Следующая закладка (F2)\0Удалить все закладки\0Сменить тип закладки (Ctrl+Shift+F2)\
\0Сортировать абзацы\
\0UNDO\0REDO\
\0Найти/Заменить\0Максимальный размер окна вывода\0Увеличить размер окна ввода\0Печатать\0 \0 \0"
#else
"Load\0Save\
\0 \0 \0 \0 \0 \
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
		for(i=0;i<OVTOOLBAR_NBTNS;i++)
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
		re.top+=24;
		m_Editor->CreateEx(WS_EX_CLIENTEDGE,"Scintilla","",WS_CHILD|WS_VISIBLE,re,this,12347,NULL);
		DlgAutoSize->AddWnd(m_Editor->m_hWnd,this->m_hWnd,"NNEE");
	}

	m_Editor->StringToStyle(AfxGetApp()->GetProfileString("SEP_OUTPUT_SET","OUTPUT_STYLES",""),"\x01");
	m_Editor->ScMethod(SCI_SETUNDOCOLLECTION,0,0);

	SetTimer(CDVO_TIMER_SIZECHECK,5000,NULL);

	return TRUE;
}

void CDlgViewOutput::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if (DlgAutoSize)
		try{DlgAutoSize->UpdateSize();}catch(...){GPC.m_ErrReport.GPWriteErrorLog("CDlgViewOutput", "OnSize","");}
}

void CDlgViewOutput::SetSize(CSize &csValidSize)
{
	if (csValidSize!=m_csLastParentSize)
		MoveWindow(0,0,csValidSize.cx,csValidSize.cy);

	m_csLastParentSize=csValidSize;
	csValidSize.cx=0;
	csValidSize.cy=0;
}

int CDlgViewOutput::AppendCharToOutput(char iCh, DWORD dwDelayFlag)
{
	EnterCriticalSection(&m_CSOutputView);
		if ((dwDelayFlag&0x1))
		{
			KillTimer(1);
			KillTimer(2);
		}
		BYTE tmp[20];
		*tmp=(BYTE)iCh;
		m_Pool.FillFromArray(tmp,1);
		if ((dwDelayFlag&0x1))
		{
			m_InDataFlag=0;
			SetTimer(++m_InDataFlag,25,NULL);
		}
		else
		{
			if (m_InDataFlag==0)
				SetTimer(++m_InDataFlag,m_Delay1,NULL);
			else
			if (m_InDataFlag==1)
			{
				KillTimer(m_InDataFlag);
				SetTimer(++m_InDataFlag,m_Delay2,NULL);
			}
		}
	LeaveCriticalSection(&m_CSOutputView);
	return iCh;
}

char *CDlgViewOutput::AppendStringToOutput(const char *iStr)
{
	EnterCriticalSection(&m_CSOutputView);
		m_Pool.FillFromArray((BYTE *)iStr,(int)strlen(iStr));
		m_Pool.FillFromArray((BYTE *)"\n",1);
		if (m_InDataFlag==0)
		{
			m_InDataFlag++;
			SetTimer(CDVO_TIMER_1,m_Delay1,NULL);
		}
		else
		if (m_InDataFlag==1)
		{
			KillTimer(CDVO_TIMER_1);
			m_InDataFlag=2;
			SetTimer(CDVO_TIMER_2,m_Delay2,NULL);
		}
	LeaveCriticalSection(&m_CSOutputView);
	return (char *)iStr;
}

LRESULT CDlgViewOutput::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_RedirectInput && message==WM_KEYDOWN)
		return 1;
	return CDialog::WindowProc(message, wParam, lParam);
}

void CDlgViewOutput::OnTimer(UINT nIDEvent)
{
	EnterCriticalSection(&m_CSOutputView);
		switch(nIDEvent)
		{
		case CDVO_TIMER_1:
		case CDVO_TIMER_2:
			{
				KillTimer(nIDEvent);
				UINT len=m_Pool.GetReadLength();
				BYTE *blk=new BYTE [len+5];

				len=m_Pool.GetData(&blk,len);

				if (m_Editor && len)
				{
					blk[len]=0;
					m_Editor->AppendBlock(blk,len,m_uSelectionFlag);
				}

				UINT nTr=m_Pool.GetTransferedLen();
				if (nTr<m_LastTransfer) m_LastTransfer=0;
				if ((nTr-m_LastTransfer)>1000000)
				{
					m_LastTransfer=nTr;
					m_Pool.FreeExtra();
				}

				delete[] blk;
				m_InDataFlag=0;
			}
			break;
		case CDVO_TIMER_SIZECHECK:
			if (m_Editor->GetTextLength()>m_nMaxOutputLen)
			{
				m_Editor->SetTextLengthFromEnd((m_nMaxOutputLen*m_nOutputLenDecr)/100);
			}
			break;
		}
		CDialog::OnTimer(nIDEvent);
	LeaveCriticalSection(&m_CSOutputView);
}

BOOL CDlgViewOutput::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if ((wParam==1 || wParam==2) && lParam==0) return TRUE;

	if ((HWND)lParam==m_ToolBar.m_hWnd || (m_Editor && (HWND)lParam==m_Editor->m_hWnd) || lParam==NULL)
	{
		switch(LOWORD(wParam))
		{
		case SCCMND_PRINT:
			if (m_Editor)
				m_Editor->Print(3,"");
			break;
		case SCCMND_DIRECTINPUT:
			m_Editor->m_DirectInputFlag=m_ToolBar.IsButtonChecked(SCCMND_DIRECTINPUT);
			if (m_CDlgViewOutputSetPtr)
			{
				m_CDlgViewOutputSetPtr->m_dwOutputSet&=(0xFFFFFFFF^CDVOS_DIRECTINPUT);
				if (m_Editor->m_DirectInputFlag)
					m_CDlgViewOutputSetPtr->m_dwOutputSet|=CDVOS_DIRECTINPUT;
				m_CDlgViewOutputSetPtr->UpdateCtrls();
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
			GetParent()->SendMessage(GPN_UPDATESIZE,SCCMND_WNDSIZE+0x10000,0);
			break;
		case SCCMND_WNDSIZE2:
			GetParent()->SendMessage(GPN_UPDATESIZE,SCCMND_WNDSIZE2+0x10000,0);
			break;
		default:
			break;
		}
	}

	return CDialog::OnCommand(wParam, lParam);
}

BOOL CDlgViewOutput::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
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

void CDlgViewOutput::UpdateTB()
{
	m_ToolBar.CheckButton(SCCMND_DIRECTINPUT,m_Editor->m_DirectInputFlag!=0);
}

void CDlgViewOutput::CloseFindDialog()
{
	m_Editor->CloseFindDialog();
}
