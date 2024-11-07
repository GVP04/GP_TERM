// DlgGPScintillaFind.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgGPScintillaFind.h"
#include "GPScintilla.h"
#include "Scintilla\Scintilla.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGPScintillaFind dialog


CDlgGPScintillaFind::CDlgGPScintillaFind(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGPScintillaFind::IDD, pParent)
{
	GPScintilla *iv=NULL;
	EditorsArray.SetInitValue(iv);
	//{{AFX_DATA_INIT(CDlgGPScintillaFind)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_LastSelStart=-1;
	m_LastSelEnd=-1;
}

CDlgGPScintillaFind::~CDlgGPScintillaFind()
{
}


void CDlgGPScintillaFind::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGPScintillaFind)
	DDX_Control(pDX, IDC_BUTTONEX, m_BtnEx);
	DDX_Control(pDX, IDC_CHECKSELECTION, m_CheckSelection);
	DDX_Control(pDX, IDC_COMBOREPLACE, m_ComboReplace);
	DDX_Control(pDX, IDC_COMBOFIND, m_ComboFind);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGPScintillaFind, CDialog)
	//{{AFX_MSG_MAP(CDlgGPScintillaFind)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTONEX, OnButtonex)
	ON_CBN_EDITCHANGE(IDC_COMBOFIND, OnEditchangeCombofind)
	ON_CBN_EDITCHANGE(IDC_COMBOREPLACE, OnEditchangeComboreplace)
	ON_BN_CLICKED(IDC_CHECKSELECTION, OnCheckselection)
	ON_CBN_SELCHANGE(IDC_COMBOFIND, OnEditchangeCombofind)
	ON_CBN_SELCHANGE(IDC_COMBOREPLACE, OnEditchangeComboreplace)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGPScintillaFind message handlers

BOOL CDlgGPScintillaFind::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_csFindStrings=AfxGetApp()->GetProfileString(GPC.cs_RegTermViewSetName, "FindStrings","");
	m_csReplaceStrings=AfxGetApp()->GetProfileString(GPC.cs_RegTermViewSetName, "ReplaceStrings","");
	SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOREPOSITION|SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOSIZE);

		unsigned char BtnsStyle[]={
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
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
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
		};

		DWORD BtnsStrings[]={0,1,2,3,4,5,6,7,8,9,10,11,12,};
		DWORD BtnsImage[]={27,26,31,32,19,20,30,28,29,33,7,8,9,};
		DWORD BtnsCommands[]={
			SCFINDCMND_FINDPREV,
			SCFINDCMND_FINDNEXT,
			SCFINDCMND_REPLACE,
			SCFINDCMND_REPLACEALL,
			SCFINDCMND_UNDO,
			SCFINDCMND_REDO,
			SCFINDCMND_HIDEMATCHED,
			SCFINDCMND_HIDEUNMATCHED,
			SCFINDCMND_SHOWALL,
			SCFINDCMND_MARKMATHED,
		};



#ifndef _VC80_UPGRADE
	m_ToolBar.CreateEx(0,TOOLBARCLASSNAME,NULL,
		CCS_TOP|CCS_NODIVIDER|CCS_NORESIZE|CCS_NOPARENTALIGN|
		TBSTYLE_SEP|TBSTYLE_AUTOSIZE|TBSTYLE_LIST|TBSTYLE_TOOLTIPS|TBSTYLE_WRAPABLE|
		WS_CHILD|WS_VISIBLE,
		CRect(250,0,300,112),this,12346,NULL);
#else
	m_ToolBar.CreateEx(0,CCS_TOP|CCS_NODIVIDER|CCS_NORESIZE|CCS_NOPARENTALIGN|
		TBSTYLE_SEP|TBSTYLE_AUTOSIZE|TBSTYLE_LIST|TBSTYLE_TOOLTIPS|TBSTYLE_WRAPABLE|
		WS_CHILD|WS_VISIBLE,
		CRect(250,0,300,112),this,12346);
#endif

	m_ToolBar.SetExtendedStyle(TBSTYLE_EX_MIXEDBUTTONS);

	m_ToolBar.SetButtonSize(CSize(16,16));
	m_ToolBar.SetImageList(&GPC.a_GPImageList[GPC.GetImageListId("SEPVIEW")].m_IL);
	m_ToolBar.SetDisabledImageList(&GPC.a_GPImageList[GPC.GetImageListId("SEPVIEWDIS")].m_IL);

	TBBUTTON tbt={0};
	int i;
	for(i=0;i<SCFINDTOOLBAR_NBTNS;i++)
	{
		tbt.iBitmap=BtnsImage[i];
		tbt.idCommand=BtnsCommands[i];
		tbt.iString=BtnsStrings[i];
		tbt.dwData=NULL;
		tbt.fsState=BtnsState[i];
		tbt.fsStyle=BtnsStyle[i];
		m_ToolBar.InsertButton(i,&tbt);
	}

	m_ToolBar.AddStrings(
#ifdef RUS
"Найти предыдущее\0Найти следующее\0Заменить\0Заменить все\0Отменить\0Повторить\
\0Скрыть строки с найденным текстом\0Скрыть строки не содержащие найденный текст\0Показать все строки\0Закладки на найденный текст\0 \0 \0 \0 \0 \0 \0"
#else
"Find Previous\0Find Next\0Replace\0Replace All\0Undo\0Redo\
\0Hide Matched Lines\0Hide Unmatched Lines\0Show All\0Bookmark Matched\0 \0 \0 \0 \0 \0 \0"
#endif
			);

	m_ComboFind.ResetContent();
	m_ComboFind.LimitText(1000);
	m_ComboReplace.ResetContent();
	m_ComboReplace.LimitText(1000);

	CString tmps;

	const char *pos=m_csFindStrings;
	do
		if (*pos && *pos!=1)
			m_ComboFind.AddString(ExtractField(pos,1,"\x1"));
	while(*(pos=FindField(pos,2,"\x1")));

	pos=m_csReplaceStrings;
	do
		if (*pos && *pos!=1)
			m_ComboReplace.AddString(ExtractField(pos,1,"\x1"));
	while(*(pos=FindField(pos,2,"\x1")));

	m_ComboFind.SetCurSel(0);
	m_ComboReplace.SetCurSel(0);
	OnEditchangeCombofind();

	return TRUE;
}

void CDlgGPScintillaFind::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);


}

void CDlgGPScintillaFind::OnTimer(UINT nIDEvent)
{

	CDialog::OnTimer(nIDEvent);
}

LRESULT CDlgGPScintillaFind::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	return CDialog::WindowProc(message, wParam, lParam);
}

BOOL CDlgGPScintillaFind::OnCommand(WPARAM wParam, LPARAM lParam)
{

	BOOL Commandret=TRUE;

	if (((HWND)lParam)==m_ToolBar.m_hWnd)
	{
		GPScintilla *ed=EditorsArray.GetSelected();
		if (ed)
		{
			switch(LOWORD(wParam))
			{
			case SCFINDCMND_FINDNEXT:
				{
					int ret=-1;
					UpdateCombos();
					CString src=GetSearchText();
					DWORD flg=GetSearchFlags()&SCFIND_SELECTIONMASK;

					int start=ed->ScMethod(SCI_GETSELECTIONSTART,0,0);
					int end=ed->ScMethod(SCI_GETSELECTIONEND,0,0);

					if (start!=m_LastSelStart || end!=m_LastSelEnd)
						ed->ScMethod(SCI_SEARCHANCHOR,0,0);

					ret=ed->ScMethod(SCI_SEARCHNEXT,flg,(int)((LPCSTR)src));
					if (ret>=0)
					{
						start=ed->ScMethod(SCI_GETSELECTIONSTART,0,0);
						end=ed->ScMethod(SCI_GETSELECTIONEND,0,0);
						ed->ScMethod(SCI_GOTOPOS,start,0);
						ed->ScMethod(SCI_ENSUREVISIBLE,ed->ScMethod(SCI_LINEFROMPOSITION,start,0),0);
						ed->ScMethod(SCI_SETSELECTIONSTART,start+1,0);
						ed->ScMethod(SCI_SEARCHANCHOR,0,0);
						ed->ScMethod(SCI_SETSELECTIONSTART,start,0);
						ed->ScMethod(SCI_SETSELECTIONEND,end,0);
					}
					else
					{
						ed->ScMethod(SCI_SETSELECTIONSTART,0,0);
						ed->ScMethod(SCI_SEARCHANCHOR,0,0);
						ed->ScMethod(SCI_SETSELECTIONSTART,start,0);
						ed->ScMethod(SCI_SETSELECTIONEND,end,0);
						ret=ed->ScMethod(SCI_SEARCHNEXT,flg,(int)((LPCSTR)src));
						if (ret>=0)
						{
							start=ed->ScMethod(SCI_GETSELECTIONSTART,0,0);
							end=ed->ScMethod(SCI_GETSELECTIONEND,0,0);
							ed->ScMethod(SCI_GOTOPOS,start,0);
							ed->ScMethod(SCI_ENSUREVISIBLE,ed->ScMethod(SCI_LINEFROMPOSITION,start,0),0);
							ed->ScMethod(SCI_SETSELECTIONSTART,start+1,0);
							ed->ScMethod(SCI_SEARCHANCHOR,0,0);
							ed->ScMethod(SCI_SETSELECTIONSTART,start,0);
							ed->ScMethod(SCI_SETSELECTIONEND,end,0);
						}
					}
					m_LastSelStart=start;
					m_LastSelEnd=end;

					if (ret==-1) MessageBeep(MB_ICONASTERISK);
				}
				break;
			case SCFINDCMND_FINDPREV:
				{
					int ret=-1;
					UpdateCombos();
					CString src=GetSearchText();
					DWORD flg=GetSearchFlags()&SCFIND_SELECTIONMASK;

					int start=ed->ScMethod(SCI_GETSELECTIONSTART,0,0);
					int end=ed->ScMethod(SCI_GETSELECTIONEND,0,0);

					if (start!=m_LastSelStart || end!=m_LastSelEnd)
						ed->ScMethod(SCI_SEARCHANCHOR,0,0);

					ret=ed->ScMethod(SCI_SEARCHPREV,flg,(int)((LPCSTR)src));
					if (ret>=0)
					{
						start=ed->ScMethod(SCI_GETSELECTIONSTART,0,0);
						end=ed->ScMethod(SCI_GETSELECTIONEND,0,0);
						ed->ScMethod(SCI_GOTOPOS,start,0);
						ed->ScMethod(SCI_ENSUREVISIBLE,ed->ScMethod(SCI_LINEFROMPOSITION,start,0),0);
						if (start==0)
						{
							int nchars=ed->ScMethod(SCI_GETLENGTH,0,0)-1;
							if (nchars<0) nchars=0;
							ed->ScMethod(SCI_SETSELECTIONSTART,nchars,0);
							ed->ScMethod(SCI_SETSELECTIONEND,nchars,0);
							ed->ScMethod(SCI_SEARCHANCHOR,0,0);
						}
						else
							ed->ScMethod(SCI_SETSELECTIONSTART,start-1,0);
						ed->ScMethod(SCI_SEARCHANCHOR,0,0);
						ed->ScMethod(SCI_SETSELECTIONSTART,start,0);
						ed->ScMethod(SCI_SETSELECTIONEND,end,0);
					}
					else
					{
						int nchars=ed->ScMethod(SCI_GETLENGTH,0,0)-1;
						if (nchars<0) nchars=0;
						ed->ScMethod(SCI_SETSELECTIONSTART,nchars,0);
						ed->ScMethod(SCI_SETSELECTIONEND,nchars,0);
						ed->ScMethod(SCI_SEARCHANCHOR,0,0);
						ed->ScMethod(SCI_SETSELECTIONSTART,start,0);
						ed->ScMethod(SCI_SETSELECTIONEND,end,0);
						ret=ed->ScMethod(SCI_SEARCHPREV,flg,(int)((LPCSTR)src));
						if (ret>=0)
						{
							start=ed->ScMethod(SCI_GETSELECTIONSTART,0,0);
							end=ed->ScMethod(SCI_GETSELECTIONEND,0,0);
							ed->ScMethod(SCI_GOTOPOS,start,0);
							ed->ScMethod(SCI_ENSUREVISIBLE,ed->ScMethod(SCI_LINEFROMPOSITION,start,0),0);
							if (start==0)
							{
								nchars=ed->ScMethod(SCI_GETLENGTH,0,0)-1;
								if (nchars<0) nchars=0;
								ed->ScMethod(SCI_SETSELECTIONSTART,nchars,0);
								ed->ScMethod(SCI_SETSELECTIONEND,nchars,0);
								ed->ScMethod(SCI_SEARCHANCHOR,0,0);
							}
							else
								ed->ScMethod(SCI_SETSELECTIONSTART,start-1,0);
							ed->ScMethod(SCI_SEARCHANCHOR,0,0);
							ed->ScMethod(SCI_SETSELECTIONSTART,start,0);
							ed->ScMethod(SCI_SETSELECTIONEND,end,0);
						}
					}
					m_LastSelStart=start;
					m_LastSelEnd=end;

					if (ret==-1) MessageBeep(MB_ICONASTERISK);
				}
				break;
			case SCFINDCMND_REPLACE:
				{
					int rOnly=ed->ScMethod(SCI_GETREADONLY,0,0);
					if (rOnly) ed->ScMethod(SCI_SETREADONLY,0,0);
					int ret=-1;
					UpdateCombos();
					CString src=GetSearchText();
					CString rpl=GetReplaceText();
					DWORD flg=GetSearchFlags()&SCFIND_SELECTIONMASK;

					int start=ed->ScMethod(SCI_GETSELECTIONSTART,0,0);
					int end=ed->ScMethod(SCI_GETSELECTIONEND,0,0);

					if (start!=m_LastSelStart-1 || end!=m_LastSelEnd)
						ed->ScMethod(SCI_SEARCHANCHOR,0,0);

					ret=ed->ScMethod(SCI_SEARCHNEXT,flg,(int)((LPCSTR)src));
					if (ret>=0)
					{
						start=ed->ScMethod(SCI_GETSELECTIONSTART,0,0);
						end=ed->ScMethod(SCI_GETSELECTIONEND,0,0);
						ed->ScMethod(SCI_TARGETFROMSELECTION,0,0);
						end=start+ed->ScMethod(SCI_REPLACETARGET,-1,(int)((LPCSTR)rpl));
						ed->ScMethod(SCI_GOTOPOS,start,0);
						ed->ScMethod(SCI_ENSUREVISIBLE,ed->ScMethod(SCI_LINEFROMPOSITION,start,0),0);
						ed->ScMethod(SCI_SETSELECTIONSTART,start+1,0);
						ed->ScMethod(SCI_SEARCHANCHOR,0,0);
						ed->ScMethod(SCI_SETSELECTIONSTART,start,0);
						ed->ScMethod(SCI_SETSELECTIONEND,end,0);
					}
					else
					{
						ed->ScMethod(SCI_SETSELECTIONSTART,0,0);
						ed->ScMethod(SCI_SEARCHANCHOR,0,0);
						ed->ScMethod(SCI_SETSELECTIONSTART,start,0);
						ed->ScMethod(SCI_SETSELECTIONEND,end,0);
						ret=ed->ScMethod(SCI_SEARCHNEXT,flg,(int)((LPCSTR)src));
						if (ret>=0)
						{
							start=ed->ScMethod(SCI_GETSELECTIONSTART,0,0);
							end=ed->ScMethod(SCI_GETSELECTIONEND,0,0);
							ed->ScMethod(SCI_TARGETFROMSELECTION,0,0);
							end=start+ed->ScMethod(SCI_REPLACETARGET,-1,(int)((LPCSTR)rpl));
							ed->ScMethod(SCI_GOTOPOS,start,0);
							ed->ScMethod(SCI_ENSUREVISIBLE,ed->ScMethod(SCI_LINEFROMPOSITION,start,0),0);
							ed->ScMethod(SCI_SETSELECTIONSTART,start+1,0);
							ed->ScMethod(SCI_SEARCHANCHOR,0,0);
							ed->ScMethod(SCI_SETSELECTIONSTART,start,0);
							ed->ScMethod(SCI_SETSELECTIONEND,end,0);
						}
					}
					m_LastSelStart=start;
					m_LastSelEnd=end;

					if (rOnly) ed->ScMethod(SCI_SETREADONLY,1,0);
					if (ret==-1) MessageBeep(MB_ICONASTERISK);
				}
				break;
			case SCFINDCMND_REPLACEALL:
				{
					int rOnly=ed->ScMethod(SCI_GETREADONLY,0,0);
					if (rOnly) ed->ScMethod(SCI_SETREADONLY,0,0);
					int ret=-1;
					UpdateCombos();
					CString src=GetSearchText();
					CString rpl=GetReplaceText();
					DWORD flg=GetSearchFlags()&SCFIND_SELECTIONMASK;
					ed->ScMethod(SCI_SETSEARCHFLAGS,flg,0);

					int start=ed->ScMethod(SCI_GETSELECTIONSTART,0,0);
					int end=ed->ScMethod(SCI_GETSELECTIONEND,0,0);
					if (m_CheckSelection.GetCheck()==0)
					{
						start=0;
						end=ed->ScMethod(SCI_GETLENGTH,0,0)-1;
						if (end<0) end=0;
					}

					int lensrc=src.GetLength();
					do
					{
						ed->ScMethod(SCI_SETTARGETSTART,start,0);
						ed->ScMethod(SCI_SETTARGETEND,end,0);

						ret=ed->ScMethod(SCI_SEARCHINTARGET,lensrc,(int)((LPCSTR)src));

						if (ret>=0)
						{
							int t_start=ed->ScMethod(SCI_GETTARGETSTART,0,0);
							int t_end=ed->ScMethod(SCI_GETTARGETEND,0,0);
							int len=ed->ScMethod(SCI_REPLACETARGET,-1,(int)((LPCSTR)rpl));
							start=t_start+len;
							end+=len-t_end+t_start;
						}
					}
					while(ret>=0);

					if (rOnly) ed->ScMethod(SCI_SETREADONLY,1,0);
					m_LastSelStart=-1;
					m_LastSelEnd=-1;
				}
				break;
			case SCFINDCMND_HIDEMATCHED:
			case SCFINDCMND_HIDEUNMATCHED:
			case SCFINDCMND_MARKMATHED:
				{
					int ret=-1;
					UpdateCombos();
					CString src=GetSearchText();
					DWORD flg=GetSearchFlags()&SCFIND_SELECTIONMASK;

					int start=ed->ScMethod(SCI_GETSELECTIONSTART,0,0);
					int end=ed->ScMethod(SCI_GETSELECTIONEND,0,0);
					ed->ScMethod(SCI_SETSELECTIONSTART,0,0);
					ed->ScMethod(SCI_SETSELECTIONEND,0,0);
					ed->ScMethod(SCI_SEARCHANCHOR,0,0);
					int lastFind=0;

					do
					{
						ret=ed->ScMethod(SCI_SEARCHNEXT,flg,(int)((LPCSTR)src));
						int findline=ret>=0?ed->ScMethod(SCI_LINEFROMPOSITION,ret,0):0;
						switch(LOWORD(wParam))
						{
						case SCFINDCMND_HIDEMATCHED:
							if (ret>=0)
								ed->ScMethod(SCI_HIDELINES,findline,findline);
							break;
						case SCFINDCMND_MARKMATHED:
							if (ret>=0)
								ed->ScMethod(SCI_MARKERADD,findline,ed->m_CurMarkerType);
							break;
						case SCFINDCMND_HIDEUNMATCHED:
							if (ret>=0)
							{
								if (findline!=lastFind)
								{
									ed->ScMethod(SCI_HIDELINES,lastFind,findline-1);
									lastFind=findline;
								}
								lastFind++;
							}
							else
							{
								int endline=ed->ScMethod(SCI_GETLINECOUNT,0,0);
								if (endline>0) endline--;
								ed->ScMethod(SCI_HIDELINES,lastFind,endline);
							}
							break;
						}

						if (ret!=-1)
						{
							int endline=ed->ScMethod(SCI_GETLINECOUNT,0,0);
							int ln=findline;
							ln++;
							if (ln>=endline) ret=-1;
							else
							{
								start=ed->ScMethod(SCI_POSITIONFROMLINE,ln,0);
								ed->ScMethod(SCI_SETSELECTIONSTART,start,0);
								ed->ScMethod(SCI_SEARCHANCHOR,0,0);
							}
						}
					}
					while(ret>=0);

					ed->ScMethod(SCI_SETSELECTIONSTART,start,0);
					ed->ScMethod(SCI_SETSELECTIONEND,end,0);
					m_LastSelStart=-1;
					m_LastSelEnd=-1;

					if (ret==-1) MessageBeep(MB_ICONASTERISK);
				}
				break;
			case SCFINDCMND_SHOWALL:
				{
					int endline=ed->ScMethod(SCI_GETLINECOUNT,0,0)-1;
					if (endline<0) endline=0;
					ed->ScMethod(SCI_SHOWLINES,0,endline);
				}
				break;
			case SCFINDCMND_ONTOP:
				break;
			case SCFINDCMND_UNDO:
				ed->ScMethod(SCI_UNDO,0,0);
				break;
			case SCFINDCMND_REDO:
				ed->ScMethod(SCI_REDO,0,0);
				break;
			}
		}
	}
	else
	if (wParam==1)
	{
		HWND tmpf=::GetFocus();
		if (tmpf)
		{
			CString m_Find,m_Replace;
			GetDlgItemText(IDC_COMBOFIND,m_Find);
			GetDlgItemText(IDC_COMBOREPLACE,m_Replace);
			if (tmpf==::GetDlgItem(m_hWnd,IDC_BUTTONFIND) && m_Find!="")
			{
			//	return CDialog::OnCommand(wParam, lParam);
			}
			else
			if (tmpf==::GetDlgItem(m_hWnd,IDC_BUTTONREPLACE) && m_Find!="" && m_Replace!="")
			{
	//			return CDialog::OnCommand(wParam, lParam);
			}
			else
			{
				HWND tmpnext=::GetNextDlgTabItem(m_hWnd,tmpf,FALSE);
				if (tmpnext)
					GotoDlgCtrl(CWnd::FromHandle(tmpnext));
			}
		}
	}
	else
	switch(LOWORD(wParam))
	{
	case SCCMND_FINDEXMENU1:
	case SCCMND_FINDEXMENU2:
	case SCCMND_FINDEXMENU3:
	case SCCMND_FINDEXMENU4:
	case SCCMND_FINDEXMENU5:
	case SCCMND_FINDEXMENU6:
	case SCCMND_FINDEXMENU7:
	case SCCMND_FINDEXMENU8:
	case SCCMND_FINDEXMENU9:
	case SCCMND_FINDEXMENU10:
	case SCCMND_FINDEXMENU11:
	case SCCMND_FINDEXMENU12:
	case SCCMND_FINDEXMENU13:
		{
			const char *addstr[]=
				{
					".",
					"\\(",
					"\\)",
					"\\N",
					"\\<",
					"\\>",
					"\\x",
					"[]",
					"[^]",
					"^",
					"$",
					"*",
					"+",
				};

			CString tmps=GetSearchText();
			tmps+=addstr[LOWORD(wParam)-SCCMND_FINDEXMENU1];
			SetFindText(tmps);
		}
		break;
	default:
		Commandret= CDialog::OnCommand(wParam, lParam);
		break;
	}
	return Commandret;
}

BOOL CDlgGPScintillaFind::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{

	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CDlgGPScintillaFind::OnDestroy()
{
	int nItems,i;
	CString tmps;

	nItems=m_ComboFind.GetCount();
	m_csFindStrings="";

	for(i=0;i<nItems;i++)
	{
		m_ComboFind.GetLBText(i,tmps);
		if (tmps!="")
		{
			if (m_csFindStrings!="") m_csFindStrings+="\x1";
			m_csFindStrings+=tmps;
		}
	}

	nItems=m_ComboReplace.GetCount();
	m_csReplaceStrings="";

	for(i=0;i<nItems;i++)
	{
		m_ComboReplace.GetLBText(i,tmps);
		if (tmps!="")
		{
			if (m_csReplaceStrings!="") m_csReplaceStrings+="\x1";
			m_csReplaceStrings+=tmps;
		}
	}

	AfxGetApp()->WriteProfileString(GPC.cs_RegTermViewSetName, "FindStrings",m_csFindStrings);
	AfxGetApp()->WriteProfileString(GPC.cs_RegTermViewSetName, "ReplaceStrings",m_csReplaceStrings);
	CDialog::OnDestroy();
}

UINT CDlgGPScintillaFind::AddRef(GPScintilla * iRef)
{
	if (iRef) EditorsArray[(DWORD)iRef]=iRef;
	return EditorsArray.GetCount();
}

UINT CDlgGPScintillaFind::DelRef(GPScintilla * iRef)
{
	EditorsArray.RemoveItem((DWORD)iRef);
	return EditorsArray.GetCount();
}

UINT CDlgGPScintillaFind::SetCurrentEditor(GPScintilla * iRef)
{
	if (iRef && iRef->m_hWnd)
	{
		EditorsArray.SelectItem((DWORD)iRef);
	}

	return EditorsArray.GetCount();
}

void CDlgGPScintillaFind::OnButtonex()
{
	HMENU m_Menu=::CreatePopupMenu();
	if (m_Menu)
	{
		#ifdef RUS
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU1,". Любой символ");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU2,"\\( Начало области для маркировки соответствия");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU3,"\\) Конец области для маркировки соответствия");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU4,"\\n Любая цифра");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU5,"\\< Начало слова");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU6,"\\> Конец слова");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU7,"\\x Символ x");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU8,"[...] Любые символы");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU9,"[^...] Дополнение символов в наборе");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU10,"^ Начало строки");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU11,"$ Конец строки");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU12,"* 0 или больше раз");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU13,"+ 1 или больше раз");
		#else
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU1,". Matches any character");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU2,"\\( start of a region for tagging a match");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU3,"\\) end of a tagged region");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU4,"\\n Any Number");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU5,"\\< start of a word");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU6,"\\> end of a word");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU7,"\\x character x");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU8,"[...] any of the characters");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU9,"[^...] The complement of the characters in the set");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU10,"^ the start of a line");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU11,"$ the end of a line");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU12,"* 0 or more times");
			::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_FINDEXMENU13,"+ 1 or more times");
		#endif

		CRect re;
		m_BtnEx.GetWindowRect(&re);
		::TrackPopupMenu(m_Menu,0,re.right,re.top,0,m_hWnd,NULL);
	}
}

void CDlgGPScintillaFind::UpdateComboFind()
{
	CString tmps;
	m_ComboFind.GetWindowText(tmps);
	if (tmps!="")
	{
		if (m_ComboFind.FindStringExact(0,tmps)==CB_ERR)
			m_ComboFind.InsertString(0,tmps);
	}
}

void CDlgGPScintillaFind::UpdateComboReplace()
{
	CString tmps;
	m_ComboReplace.GetWindowText(tmps);
	if (tmps!="")
	{
		if (m_ComboReplace.FindStringExact(0,tmps)==CB_ERR)
			m_ComboReplace.InsertString(0,tmps);
	}
}

void CDlgGPScintillaFind::UpdateCombos()
{
	UpdateComboFind();
	UpdateComboReplace();
	OnEditchangeCombofind();
}

void CDlgGPScintillaFind::OnEditchangeCombofind()
{
	CString tmp;
	m_ComboFind.GetWindowText(tmp);
	BOOL enbl=tmp!="";
	m_ToolBar.EnableButton(SCFINDCMND_FINDNEXT,enbl);
	m_ToolBar.EnableButton(SCFINDCMND_FINDPREV,enbl);
	m_ToolBar.EnableButton(SCFINDCMND_HIDEMATCHED,enbl);
	m_ToolBar.EnableButton(SCFINDCMND_HIDEUNMATCHED,enbl);
	m_ToolBar.EnableButton(SCFINDCMND_REPLACE,enbl);
	m_ToolBar.EnableButton(SCFINDCMND_REPLACEALL,enbl);

	OnEditchangeComboreplace();
}

void CDlgGPScintillaFind::OnEditchangeComboreplace()
{
	/*
	CString tmp;
	CString tmp2;
	m_ComboReplace.GetWindowText(tmp);
	m_ComboFind.GetWindowText(tmp2);
	m_ToolBar.EnableButton(SCFINDCMND_REPLACE,tmp!="" && tmp2!="");
	m_ToolBar.EnableButton(SCFINDCMND_REPLACEALL,tmp!="" && tmp2!="");
	*/
}

DWORD CDlgGPScintillaFind::GetSearchFlags()
{
	DWORD ret=0;

	if (::IsDlgButtonChecked(m_hWnd,IDC_CHECKMATCHCASE))	ret|=SCFIND_MATCHCASE;
	if (::IsDlgButtonChecked(m_hWnd,IDC_CHECKWHOLEWORD))	ret|=SCFIND_WHOLEWORD;
	if (::IsDlgButtonChecked(m_hWnd,IDC_CHECKWORDSTART))	ret|=SCFIND_WORDSTART;
	if (::IsDlgButtonChecked(m_hWnd,IDC_CHECKREGEXP))		ret|=SCFIND_REGEXP;
	if (::IsDlgButtonChecked(m_hWnd,IDC_CHECKPOSIX))		ret|=SCFIND_POSIX;
	if (::IsDlgButtonChecked(m_hWnd,IDC_CHECKSELECTION))	ret|=SCFIND_SELECTION;

	return ret;
}

const CString CDlgGPScintillaFind::GetSearchText()
{
	CString tmp;
	m_ComboFind.GetWindowText(tmp);
	return tmp;
}

const CString CDlgGPScintillaFind::GetReplaceText()
{
	CString tmp;
	m_ComboReplace.GetWindowText(tmp);
	return tmp;
}

void CDlgGPScintillaFind::SetFindText(const char *iText)
{
	m_ComboFind.SetWindowText(iText);
	UpdateComboFind();
}

void CDlgGPScintillaFind::OnCheckselection()
{
}

DWORD CDlgGPScintillaFind::SetSearchFlags(DWORD dwFlg)
{
	DWORD ret=GetSearchFlags();
	
	::CheckDlgButton(m_hWnd,IDC_CHECKMATCHCASE,	(dwFlg&SCFIND_MATCHCASE)==SCFIND_MATCHCASE);
	::CheckDlgButton(m_hWnd,IDC_CHECKWHOLEWORD,	(dwFlg&SCFIND_WHOLEWORD)==SCFIND_WHOLEWORD);
	::CheckDlgButton(m_hWnd,IDC_CHECKWORDSTART,	(dwFlg&SCFIND_WORDSTART)==SCFIND_WORDSTART);
	::CheckDlgButton(m_hWnd,IDC_CHECKREGEXP,	(dwFlg&SCFIND_REGEXP)==SCFIND_REGEXP);
	::CheckDlgButton(m_hWnd,IDC_CHECKPOSIX,		(dwFlg&SCFIND_POSIX)==SCFIND_POSIX);
	::CheckDlgButton(m_hWnd,IDC_CHECKSELECTION,	(dwFlg&SCFIND_SELECTION)==SCFIND_SELECTION);

	return ret;
}

void CDlgGPScintillaFind::SetReplaceText(const char *iText)
{
	CString tmp;
	m_ComboReplace.SetWindowText(iText);
}

void CDlgGPScintillaFind::DoReplaceAll()
{
	OnCommand(SCFINDCMND_REPLACEALL, (LPARAM)m_ToolBar.m_hWnd );
}

