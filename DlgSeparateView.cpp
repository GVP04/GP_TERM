// DlgSeparateView.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgSeparateView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSeparateView dialog

const UINT CDlgSeparateView::uNMethods=6;
const char *CDlgSeparateView::cArrMethods[]={
	"GetInputText","SetInputText","GetOutputText","SetOutputText","InputEditorMethod",
	"OutputEditorMethod","","","","",
	"","","","","",
	};
const char *CDlgSeparateView::cArrMethodsParams[]={
	"flag","flag,Text","flag","flag,Text","Method Params",
	"Method Params","","","","",
	"","","","","",
	};

CDlgSeparateView::CDlgSeparateView(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSeparateView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSeparateView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSeparateView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSeparateView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSeparateView, CDialog)
	//{{AFX_MSG_MAP(CDlgSeparateView)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSeparateView message handlers

BOOL CDlgSeparateView::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_DlgViewInputAll.m_DlgViewOutputPtr=&m_DlgViewOutput;
	m_DlgViewInputAll.m_DlgViewOutputSet.m_DlgViewOutputPtr=&m_DlgViewOutput;
	m_DlgViewInputAll.m_DlgViewInputSet.m_DlgViewInputPtr=&m_DlgViewInputAll.m_DlgViewInput;

	if (m_DlgViewOutput.m_hWnd==NULL)
	{
		m_DlgViewOutput.Create(IDD_DLGVIEWOUTPUT,this);
		m_DlgViewOutput.ShowWindow(SW_SHOW);
	}

	if (m_DlgViewInputAll.m_hWnd==NULL)
	{
		m_DlgViewInputAll.Create(IDD_DLGVIEWINPUTALL,this);
		m_DlgViewInputAll.ShowWindow(SW_SHOW);
	}

	m_DlgViewInputAll.m_DlgViewOutputSet.SetMinMaxLen(m_DlgViewOutput.m_nMaxOutputLen,m_DlgViewOutput.m_nOutputLenDecr);
	FrameSizeMove();

	m_DlgViewOutput.m_Editor->m_HWNDDuplicateInput=
		m_DlgViewInputAll.m_DlgViewInput.m_Editor->m_hWnd;

	return TRUE;
}

void CDlgSeparateView::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	ResizeDialogs(CSize(cx,cy));
}

char *CDlgSeparateView::AppendStringToOutput(const char *iStr)
{
	char *ret=(char *)iStr;
	if ((m_DlgViewInputAll.m_DlgViewOutputSet.m_dwOutputSet)&CDVOS_ENABLEOUTPUT)
	{
		char *tmps=new char [(int)strlen(iStr)+10];
		DWORD ChMask=m_DlgViewInputAll.m_DlgViewOutputSet.GetCharMask();
		char *pos=tmps;
		char *dostr=tmps;
		while(*iStr)
		{
			*pos=*(iStr++);
			if (*pos<32 && *pos>=0)
			{
				if ((GPCurrent::uArrPower[*pos]&ChMask)!=0) pos++;
			}
			else pos++;
		}
		*pos=0;
		m_DlgViewOutput.AppendStringToOutput(dostr);
		delete[] tmps;
	}
	return ret;
}

int CDlgSeparateView::AppendCharToOutput(char iCh, DWORD dwDelayFlag)
{
	int ret=1000;
	if ((m_DlgViewInputAll.m_DlgViewOutputSet.m_dwOutputSet)&CDVOS_ENABLEOUTPUT)
	{
		if (iCh<32 && iCh>=0)
		{
			DWORD ChMask=m_DlgViewInputAll.m_DlgViewOutputSet.GetCharMask();
			if ((GPCurrent::uArrPower[iCh]&ChMask)==0) ret=0;
		}
		if (ret)
			ret=m_DlgViewOutput.AppendCharToOutput(iCh,dwDelayFlag);
	}
	return ret;
}


void CDlgSeparateView::ResizeDialogs(CSize &sz)
{
	if (m_hWnd && sz.cx>0 && sz.cy>0)
	{
		if (m_DlgViewInputAll.m_hWnd && m_DlgViewOutput.m_hWnd)
		{
			CSize tmpsz;
			tmpsz=sz;
			m_DlgViewInputAll.SetSize(tmpsz);
			m_DlgViewOutput.SetSize(tmpsz);
		}
	}
}

LRESULT CDlgSeparateView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == GPN_UPDATESIZE)
	{
		switch(wParam)
		{
		case SCCMND_WNDSIZE+0x10000:
			m_DlgViewInputAll.SwitchIVSize(SCCMND_WNDSIZE);
			break;
		case SCCMND_WNDSIZE2+0x10000:
			m_DlgViewInputAll.SwitchIVSize(SCCMND_WNDSIZE2);
			break;
		default:
			{
				CRect re;
				::GetClientRect(m_hWnd,&re);
				OnSize(0,re.Width(),re.Height());
			}
		}
	}
	return CDialog::WindowProc(message, wParam, lParam);
}

void CDlgSeparateView::OnClose()
{
	if (m_DlgViewOutput)
		m_DlgViewOutput.m_Editor->CloseFindDialog();
	::SendMessage(GPC.m_hViewWnd/*::GetParent(m_hWnd)*/,GPM_SWCLOSE,0,0);
	CDialog::OnClose();
}

void CDlgSeparateView::SetViewMode(UINT iMode)
{
	if ((iMode&GPVIEWMODE_PLACEMASK)!=(m_ViewMode&GPVIEWMODE_PLACEMASK))
	{
		DWORD sremove=0,sadd=0;
		DWORD delta=WS_SIZEBOX|WS_DLGFRAME|WS_CAPTION;
		if ((iMode&GPVIEWMODE_PLACEMASK))
		{
			sremove=delta;
			::SetParent(m_hWnd,GPC.m_hViewWnd);
		}
		else
		{
			sadd=delta;
			::SetParent(m_hWnd,::GetDesktopWindow());
		}
		ModifyStyle(sremove,sadd);
	}
	m_ViewMode=iMode;
	FrameSizeMove();
}

void CDlgSeparateView::FrameSizeMove()
{
	if ((m_ViewMode&GPVIEWMODE_INFRAME))
	{
		CRect re;
		::GetClientRect(GPC.m_hViewWnd,&re);
		if (re!=m_FrameLastSize)
			MoveWindow(&re);
		m_FrameLastSize=re;
	}
	else
	{
		CRect re;
		GetClientRect(&re);
		ResizeDialogs(re.Size());
	}
}

void CDlgSeparateView::ResetParent()
{
	::SetParent(m_DlgViewInputAll.m_hWnd,m_hWnd);
	::SetParent(m_DlgViewOutput.m_hWnd,m_hWnd);
}

void CDlgSeparateView::SetPartsParent(HWND hParent)
{
	::SetParent(m_DlgViewInputAll.m_hWnd,hParent);
	::SetParent(m_DlgViewOutput.m_hWnd,hParent);
}

BOOL CDlgSeparateView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if ((wParam==1 || wParam==2) && lParam==0) return TRUE;

	return CDialog::OnCommand(wParam, lParam);
}

BOOL CDlgSeparateView::DoMethod(const char *iMethod, char **oStr)
{
	BOOL FRet=FALSE;
	try
	{
		if (m_DlgViewInputAll.m_hWnd && m_DlgViewOutput.m_hWnd && m_DlgViewInputAll.m_DlgViewInput.m_hWnd)
		{
			char met[150];
			strncpy(met,iMethod,145);
			met[145]=0;
			const char *pos=strchr(iMethod,' ');
			if (pos++) *strchr(met,' ')=0;
			else		pos="";	

			int nfunc=0;
			int retint=-123456;
			int atoipos=atoi(pos);

			if (*met>='0' && *met<='9') nfunc=atoi(met);
			else
				for(nfunc=0;nfunc<CDlgSeparateView::uNMethods && _stricmp(met,CDlgSeparateView::cArrMethods[nfunc])!=0;nfunc++);

			FRet=TRUE;

			switch(nfunc)
			{
			case 0: /*GetInputText flag*/
				if (oStr)
				{
					DWORD flags=0;
					GPScintilla::StringFromToSaveStyle(*pos?pos:"qwerty",flags);
					m_DlgViewInputAll.m_DlgViewInput.m_Editor->GetText(oStr,flags);
				}
				break;
			case 1: /*SetInputText flag,Text*/
				{
					DWORD flags=0;
					char *postmp=new char [(int)strlen(pos)+10];
					strcpy(postmp,pos);
					GPScintilla::StringFromToReplaceStyle(*postmp?postmp:"qwerty",flags);
					char *posText=strchr(postmp,',');
					if (posText) *(posText++)=0;
					else posText="";
					char *pos2=posText;
					while(*pos2)
					{
						if (*pos2==127) *pos2=13;
						pos2++;
					}
					m_DlgViewInputAll.m_DlgViewInput.m_Editor->SetText(posText,flags);
					delete[] postmp;
				}
				break;
			case 2: /*GetOutputText flag*/
				if (oStr)
				{
					DWORD flags=0;
					GPScintilla::StringFromToSaveStyle(*pos?pos:"qwerty",flags);
					m_DlgViewOutput.m_Editor->GetText(oStr,flags);
				}
				break;
			case 3: /*SetOutputText flag,Text*/
				{
					DWORD flags=0;
					char *postmp=new char [(int)strlen(pos)+10];
					strcpy(postmp,pos);
					GPScintilla::StringFromToReplaceStyle(*postmp?postmp:"qwerty",flags);
					char *posText=strchr(postmp,',');
					if (posText) *(posText++)=0;
					else posText="";
					char *pos2=posText;
					while(*pos2)
					{
						if (*pos2==127) *pos2=13;
						pos2++;
					}
					m_DlgViewOutput.m_Editor->SetText(posText,flags);
					delete[] postmp;
				}
				break;
			case 4: /*InputEditorMethod*/
				{
					char *result=NULL;
					if (oStr) *oStr=result=new char [TMP_STR_OUT_LEN+100];
					m_DlgViewInputAll.m_DlgViewInput.m_Editor->DoMethod(pos,result);
				}
				break;
			case 5: /*OutputEditorMethod*/
				{
					char *result=NULL;
					if (oStr) *oStr=result=new char [TMP_STR_OUT_LEN+100];
					m_DlgViewOutput.m_Editor->DoMethod(pos,result);
				}
				break;

			default:
				GPC.m_ErrReport.GPWriteWarnLog2("CDlgSeparateView", "Unknown Method",iMethod);

				if (*oStr)
				{
					*oStr=new char [2000];
					sprintf(*oStr,ErrObjSub,met);
				}
				FRet=FALSE;break;
			}
			if (oStr && *oStr==NULL && retint!=-123456)
			{
				*oStr=new char [200];
				sprintf(*oStr,"%d",retint);
			}
		}
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CDlgSeparateView", "DoMethod",iMethod);
		FRet=FALSE;
	}

	return FRet;
}
