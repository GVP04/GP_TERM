// GPDlgFindReplace.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPDlgFindReplace.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPDlgFindReplace dialog


GPDlgFindReplace::GPDlgFindReplace(UINT iIdDlg, CWnd* pParent /*=NULL*/)
	: CDialog(GPDlgFindReplace::IDD, pParent)
{
	GPMSG=new GPMessage("OnClose,FindNext,FindPrev,Replace,ReplaceAll,OnUpDown,OnWordCheck,OnCaseCheck,OnClipCheck,OnSelCheck,OnReplaceChange,OnReplaceSelChange,OnFindChange,OnFindSelChange,OnEnter,OnLockEnter,OnTab,OnBackTab,OnLockTab,OnLockBackTab,",NULL,0);
	IdDlg=iIdDlg;
	//{{AFX_DATA_INIT(GPDlgFindReplace)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

GPDlgFindReplace::~GPDlgFindReplace()
{
	if (GPMSG!=NULL) delete GPMSG;
	GPMSG=NULL;
}

void GPDlgFindReplace::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GPDlgFindReplace)
	DDX_Control(pDX, IDC_RADIOUP, m_RadioUp);
	DDX_Control(pDX, IDC_CHECKCAPS, m_CheckCaps);
	DDX_Control(pDX, IDC_CHECKCLIPBOARD, m_CheckClip);
	DDX_Control(pDX, IDC_CHECKSELECTION, m_CheckSel);
	DDX_Control(pDX, IDC_CHECKWORD, m_CheckWord);
	DDX_Control(pDX, IDC_COMBOFIND, m_ComboFind);
	DDX_Control(pDX, IDC_COMBOREPLACE, m_ComboReplace);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GPDlgFindReplace, CDialog)
	//{{AFX_MSG_MAP(GPDlgFindReplace)
	ON_BN_CLICKED(IDC_BUTTONFINDNEXT, OnButtonfindnext)
	ON_BN_CLICKED(IDC_BUTTONFINDPREV, OnButtonfindprev)
	ON_BN_CLICKED(IDC_BUTTONREPLACE, OnButtonreplace)
	ON_BN_CLICKED(IDC_BUTTONREPLACEALL, OnButtonreplaceall)
	ON_BN_CLICKED(IDC_CHECKCAPS, OnCheckcaps)
	ON_BN_CLICKED(IDC_CHECKCLIPBOARD, OnCheckclipboard)
	ON_BN_CLICKED(IDC_CHECKSELECTION, OnCheckselection)
	ON_BN_CLICKED(IDC_CHECKWORD, OnCheckword)
	ON_CBN_SELCHANGE(IDC_COMBOFIND, OnSelchangeCombofind)
	ON_CBN_EDITCHANGE(IDC_COMBOFIND, OnEditchangeCombofind)
	ON_CBN_EDITCHANGE(IDC_COMBOREPLACE, OnEditchangeComboreplace)
	ON_CBN_SELCHANGE(IDC_COMBOREPLACE, OnSelchangeComboreplace)
	ON_BN_CLICKED(IDC_RADIODOWN, OnRadioup)
	ON_BN_CLICKED(IDC_RADIOUP, OnRadioup)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPDlgFindReplace message handlers

void GPDlgFindReplace::OnButtonfindnext() 
{
	CString strF,strR,str;
	m_ComboReplace.GetWindowText(strR);
	m_ComboFind.GetWindowText(strF);
	str.Format("%s\x7F%s\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d",m_RadioUp.GetCheck(),m_CheckCaps.GetCheck(),m_CheckClip.GetCheck(),m_CheckSel.GetCheck(),m_CheckWord.GetCheck());
	GPMSG->GPSendDlgEvent(m_hWnd, IdDlg,"OnFindNext",str);
}

void GPDlgFindReplace::OnButtonfindprev() 
{
	CString strF,strR,str;
	m_ComboReplace.GetWindowText(strR);
	m_ComboFind.GetWindowText(strF);
	str.Format("%s\x7F%s\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d",m_RadioUp.GetCheck(),m_CheckCaps.GetCheck(),m_CheckClip.GetCheck(),m_CheckSel.GetCheck(),m_CheckWord.GetCheck());
	GPMSG->GPSendDlgEvent(m_hWnd, IdDlg,"OnFindPrev",str);
}

void GPDlgFindReplace::OnButtonreplace() 
{
	CString strF,strR,str;
	m_ComboReplace.GetWindowText(strR);
	m_ComboFind.GetWindowText(strF);
	str.Format("%s\x7F%s\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d",m_RadioUp.GetCheck(),m_CheckCaps.GetCheck(),m_CheckClip.GetCheck(),m_CheckSel.GetCheck(),m_CheckWord.GetCheck());
	GPMSG->GPSendDlgEvent(m_hWnd, IdDlg,"OnReplace",str);
}

void GPDlgFindReplace::OnButtonreplaceall() 
{
	CString strF,strR,str;
	m_ComboReplace.GetWindowText(strR);
	m_ComboFind.GetWindowText(strF);
	str.Format("%s\x7F%s\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d",m_RadioUp.GetCheck(),m_CheckCaps.GetCheck(),m_CheckClip.GetCheck(),m_CheckSel.GetCheck(),m_CheckWord.GetCheck());
	GPMSG->GPSendDlgEvent(m_hWnd, IdDlg,"OnReplaceAll",str);
}

void GPDlgFindReplace::OnCheckcaps() 
{
	char str[500];
	sprintf(str,"%d",m_CheckCaps.GetCheck());
	GPMSG->GPSendDlgEvent(m_hWnd, IdDlg,"OnCaseCheck",str);
}

void GPDlgFindReplace::OnCheckclipboard() 
{
	char str[500];
	sprintf(str,"%d",m_CheckClip.GetCheck());
	GPMSG->GPSendDlgEvent(m_hWnd, IdDlg,"OnClipCheck",str);
}

void GPDlgFindReplace::OnCheckselection() 
{
	char str[500];
	sprintf(str,"%d",m_CheckSel.GetCheck());
	GPMSG->GPSendDlgEvent(m_hWnd, IdDlg,"OnSelCheck",str);
}

void GPDlgFindReplace::OnCheckword() 
{
	char str[500];
	sprintf(str,"%d",m_CheckWord.GetCheck());
	GPMSG->GPSendDlgEvent(m_hWnd, IdDlg,"OnWordCheck",str);
}

void GPDlgFindReplace::OnSelchangeCombofind() 
{
	char str[500];
	int id= m_ComboFind.GetCurSel();
	if (id>=0) 
	{
		int l=m_ComboFind.GetLBText( id, str+20);
		if (l!=CB_ERR)	*(str+20+l)=0;
	}
	else *(str+20)=0;
	sprintf(str,"%d\x7F%s",id,str+20);
	GPMSG->GPSendDlgEvent(m_hWnd, IdDlg,"OnFindSelChange",str);
}

void GPDlgFindReplace::OnEditchangeCombofind() 
{
	char str[500];
	str[m_ComboFind.GetWindowText(str,500)]=0;
	GPMSG->GPSendDlgEvent(m_hWnd, IdDlg,"OnFindChange","");
}

void GPDlgFindReplace::OnEditchangeComboreplace() 
{
	char str[500];
	str[m_ComboReplace.GetWindowText(str,500)]=0;
	GPMSG->GPSendDlgEvent(m_hWnd, IdDlg,"OnReplaceChange",str);
}

void GPDlgFindReplace::OnSelchangeComboreplace() 
{
	char str[500];
	int id= m_ComboReplace.GetCurSel();
	if (id>=0) 
	{
		int l=m_ComboReplace.GetLBText( id, str+20);
		if (l!=CB_ERR)	*(str+20+l)=0;
	}
	else *(str+20)=0;
	sprintf(str,"%d\x7F%s",id,str+20);
	GPMSG->GPSendDlgEvent(m_hWnd, IdDlg,"OnReplaceSelChange",str);
}

void GPDlgFindReplace::OnRadioup() 
{
	char str[500];
	sprintf(str,"%d",m_RadioUp.GetCheck());
	GPMSG->GPSendDlgEvent(m_hWnd, IdDlg,"OnUpDown",str);
}

BOOL GPDlgFindReplace::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_RadioUp.SetCheck(0);
	m_CheckCaps.SetCheck(0);
	m_CheckClip.SetCheck(0);
	m_CheckSel.SetCheck(0);
	m_CheckWord.SetCheck(0);

	return TRUE;  
}

BOOL GPDlgFindReplace::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if ((wParam!=1 && wParam!=2) || lParam!=0)
		return CDialog::OnCommand(wParam, lParam);

	if (wParam==1 || wParam==2) GPMSG->GPSendDlgEvent(m_hWnd, IdDlg,"OnClose","");

	return TRUE;
}

BOOL GPDlgFindReplace::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
		if (nCode == CN_COMMAND && (nID==IDOK || nID==IDCANCEL)) return FALSE;
	
	return CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


int GPDlgFindReplace::DoMethod(const char *iStr, char *oStr)
{
	char met[150];
	strncpy(met,iStr,145);
	met[145]=0;
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc=0;
	int retint=-123456; 
	int AtoiPos=atoi(pos);

	char *fn[15]={
		"GetState","SetState","AddComboFind","AddComboReplace","DelComboFind",
		"DelComboReplace","GetCountComboFind","GetCountComboReplace","SetMessages","InsertComboFind",
		"InsertComboReplace","GetComboFind","GetComboReplace","GetItemComboFind","GetItemComboReplace",
	};

	if (*met>='0' && *met<='9') nfunc=atoi(met);
	else
		for(nfunc=0;nfunc<15 && _stricmp(met,fn[nfunc])!=0;nfunc++); 

	switch(nfunc)
	{
	case 0: /*GetState*/
		if (oStr!=NULL)
		{
			sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F",m_RadioUp.GetCheck(),m_CheckCaps.GetCheck(),m_CheckClip.GetCheck(),m_CheckSel.GetCheck(),m_CheckWord.GetCheck());
			char str[500];
			str[m_ComboFind.GetWindowText(str,500)]=0;
			strcat(oStr,str);strcat(oStr,"\x7F");
			str[m_ComboReplace.GetWindowText(str,500)]=0;
			strcat(oStr,str);
		}
		break;
	case 1: /*SetState*/	
		{
			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
			char *pos1=pos333;
			char *pos2;
			int tmpchar;
			int nParam=0;
			while(*pos1!=0 && nParam<7)
			{
				pos2=pos1;
				while(*pos2!=0 && *pos2!=',' && *pos2!=';' && *pos2!=' ' && *pos2!='|') pos2++;
				tmpchar=*pos2;
				*pos2=0;
				switch(nParam)
				{
				case 0:/*IDC_RADIOUP*/			m_RadioUp.SetCheck(atoi(pos1));		break;
				case 1:/*IDC_CHECKCAPS*/		m_CheckCaps.SetCheck(atoi(pos1));	break;
				case 2:/*IDC_CHECKCLIPBOARD*/	m_CheckClip.SetCheck(atoi(pos1));	break;
				case 3:/*IDC_CHECKSELECTION*/	m_CheckSel.SetCheck(atoi(pos1));		break;
				case 4:/*IDC_CHECKWORD*/		m_CheckWord.SetCheck(atoi(pos1));	break;
				case 5:/*IDC_COMBOFIND*/		m_ComboFind.SetWindowText(pos1);		break;
				case 6:/*IDC_COMBOREPLACE*/		m_ComboReplace.SetWindowText(pos1);	break;
				}
				nParam++;
				if (tmpchar==0) break;
				pos1=++pos2;
			}
			delete[] pos333;
		}
		break;
	case 2: /*AddComboFind*/			m_ComboFind.AddString(pos);				break;
	case 3: /*AddComboReplace*/			m_ComboReplace.AddString(pos);			break;
	case 4: /*DelComboFind*/
		if (AtoiPos<0)	m_ComboFind.ResetContent();
		else			m_ComboFind.DeleteString(AtoiPos);
		break;
	case 5: /*DelComboReplace*/	
		if (AtoiPos<0)	m_ComboReplace.ResetContent();
		else			m_ComboReplace.DeleteString(AtoiPos);
		break;
	case 6: /*GetCountComboFind*/		retint=m_ComboFind.GetCount();			break;
	case 7: /*GetCountComboReplace*/	retint=m_ComboReplace.GetCount();		break;
	case 8: /*SetMessages*/
		{
			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
			GPMSG->DelAllMessages();
			char *pos1=pos333;
			char *pos2;
			while(*pos1!=0)
			{
				pos2=pos1;
				while(*pos2!=0 && *pos2!=',' && *pos2!=';' && *pos2!=' ' && *pos2!='|') pos2++;
				if (*pos2==0)
				{
					GPMSG->AddMessage(pos1);
					break;
				}
				*pos2=0;
				GPMSG->AddMessage(pos1);
				pos1=++pos2;
			}
			delete[] pos333;
		}
		break;
	case 9: /*InsertComboFind*/		m_ComboFind.InsertString(0,pos);			break;
	case 10: /*InsertComboReplace*/	m_ComboReplace.InsertString(0,pos);			break;
	case 11: /*GetComboFind*/	
	case 12: /*GetComboReplace*/	
		if (oStr!=NULL)
		{
			int nItem;
			if (nfunc==10)	nItem=m_ComboFind.GetCount();
			else			nItem=m_ComboReplace.GetCount();
			if (nItem!=CB_ERR)
			{
				CString tmp;
				int i;
				for(i=0;i<nItem;i++)
				{
					if (nfunc==10)	m_ComboFind.GetLBText(i,tmp);
					else			m_ComboReplace.GetLBText(i,tmp);
					if (i==0) strcat(oStr,"\x7F");
					strcat(oStr,tmp);
				}
			}
		}
		break;
	case 13: /*GetItemComboFind*/	
		if (oStr!=NULL && AtoiPos>=0)
		{
			int l=m_ComboFind.GetLBText(AtoiPos,oStr);
			if (l!=CB_ERR) oStr[l]=0;		
		}
		break;
	case 14: /*GetItemComboReplace*/	
		if (oStr!=NULL && AtoiPos>=0)
		{
			int l=m_ComboReplace.GetLBText(AtoiPos,oStr);
			if (l!=CB_ERR) oStr[l]=0;		
		}
		break;
	default:
		GPC.m_ErrReport.GPWriteWarnLog2("GPDlgFindReplace", "Unknown Method",iStr);
		if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met); nfunc=0xFFFFFFFFL; 
		break;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
	return nfunc;
}

void GPDlgFindReplace::OnDestroy() 
{
	if (GetParent()->m_hWnd!=GPC.m_hViewWnd)
	{
		::SetParent(m_hWnd,GPC.m_hViewWnd);
		ShowWindow(SW_HIDE);
	}
	else
	CDialog::OnDestroy();
}
