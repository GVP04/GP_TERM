// DlgEditKeywords.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgEditKeywords.h"
#include "GPScintilla.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEditKeywords dialog


CDlgEditKeywords::CDlgEditKeywords(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEditKeywords::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEditKeywords)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_LexerType=0;
	m_CurItem=0;
	m_curSubType=0;
	m_TypeKeyword=0;
}


void CDlgEditKeywords::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEditKeywords)
	DDX_Control(pDX, IDC_BUTTONADD2, m_BtnAddAppendKW);
	DDX_Control(pDX, IDC_BUTTONDELETE2, m_BtnDeleteAppendKW);
	DDX_Control(pDX, IDC_STATIC1, m_StaticAppend);
	DDX_Control(pDX, IDC_EDIT2, m_EditAppendText);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	DDX_Control(pDX, IDC_COMBO1, m_Combo);
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEditKeywords, CDialog)
	//{{AFX_MSG_MAP(CDlgEditKeywords)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeComboType)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedListKeywords)
	ON_BN_CLICKED(IDC_BUTTONDELETE, OnButtondelete)
	ON_BN_CLICKED(IDC_BUTTONADD, OnButtonadd)
	ON_BN_CLICKED(IDC_BUTTONUPDATE, OnButtonupdate)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST1, OnEndlabeleditListKeywords)
	ON_BN_CLICKED(IDC_BUTTONADD2, OnButtonaddAppendKW)
	ON_BN_CLICKED(IDC_BUTTONDELETE2, OnButtondeleteAppendKW)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEditAppendKW)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEditKeywords message handlers

BOOL CDlgEditKeywords::OnCommand(WPARAM wParam, LPARAM lParam)
{
	BOOL TypeRet=TRUE;
	if (wParam!=1/* || lParam*/) TypeRet=FALSE;

	HWND tmpf=::GetFocus();
	if (TypeRet && tmpf)
	{
		if (tmpf==::GetDlgItem(m_hWnd,IDOK)) TypeRet=FALSE;
		else
		{
			if (tmpf==m_Edit.m_hWnd)
				OnButtonupdate();
			else
			{
				HWND tmpnext=::GetNextDlgTabItem(m_hWnd,tmpf,FALSE);
				if (tmpnext)
					GotoDlgCtrl(CWnd::FromHandle(tmpnext));
			}
		}
	}
	return TypeRet?TRUE:CDialog::OnCommand(wParam, lParam);
}

BOOL CDlgEditKeywords::OnInitDialog()
{
	CDialog::OnInitDialog();

	UpdateCtrls();
	return TRUE;
}

void CDlgEditKeywords::OnCancel()
{

	CDialog::OnCancel();
}

void CDlgEditKeywords::OnOK()
{
	UpdateSeqArray();
	SaveKeywords();
	CDialog::OnOK();
}

void CDlgEditKeywords::OnSelchangeComboType()
{
	int curSel=m_Combo.GetCurSel();
	if (curSel!=CB_ERR)
	{
		m_curSubType=m_Combo.GetItemData(curSel);
		UpdateCtrls();
		m_List.SetFocus();
	}
}

void CDlgEditKeywords::OnItemchangedListKeywords(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if ((pNMListView->uNewState&LVIS_SELECTED)==LVIS_SELECTED)
	{
		m_CurItem=pNMListView->iItem;
		m_Edit.SetSel(0,-1,TRUE);
		m_Edit.ReplaceSel((LPCSTR)m_List.GetItemText(m_CurItem,0),TRUE);
		m_List.EnsureVisible(m_CurItem,FALSE);
	}

	*pResult = 0;
}

void CDlgEditKeywords::OnButtondelete()
{
	m_List.DeleteItem(m_CurItem);
	if (m_CurItem>=m_List.GetItemCount())
		m_CurItem=m_List.GetItemCount()-1;

	if (m_CurItem<0) m_CurItem=0;

	m_List.SetItemState(m_CurItem,LVIS_SELECTED,LVIS_SELECTED);
	m_List.EnsureVisible(m_CurItem,FALSE);
	UpdateSeqArray();
}

void CDlgEditKeywords::OnButtonadd()
{
	m_List.EnsureVisible(m_CurItem,FALSE);
	const char *tmp="KeywordList_NewItem";
	m_List.InsertItem(m_CurItem,tmp);
	FindAndSelect(tmp);
	m_List.SetFocus();
	m_List.EditLabel(m_CurItem);

}

void CDlgEditKeywords::OnButtonupdate()
{
	char *tmps=new char [1000];
	tmps[m_Edit.GetLine(0,tmps,990)]=0;

	SetKeywordText(tmps);
	m_List.SortItems(NULL,0);
	FindAndSelect(tmps);
	m_List.SetFocus();

	delete[] tmps;

}

DWORD CDlgEditKeywords::SetLexerType(DWORD iType)
{
	DWORD ret=m_LexerType;
	int i=0;

	for(i=0;*GPScintilla::cArrLexer[i] && GPScintilla::uArrLexer[i]!=iType;i++);

	if (*GPScintilla::cArrLexer[i])
	{
		m_LexerType=iType;
		m_LexerName=GPScintilla::cArrLexer[i];
		m_curSubType=0;
		LoadKeywords();
	}
	else
		ret=-1;

	return ret;
}

DWORD CDlgEditKeywords::SetLexerType(const char *cType)
{
	DWORD ret=m_LexerType;
	UINT i=GPScintilla::GetLexerId(cType);

	if ((int)i>=0 && *GPScintilla::cArrLexer[i])
	{
		m_LexerName=cType;
		m_LexerType=GPScintilla::uArrLexer[i];
		m_curSubType=0;
		LoadKeywords();
	}
	else
		ret=-1;

	return ret;
}

DWORD CDlgEditKeywords::GetLexerType()
{
	return m_LexerType;
}

const char * CDlgEditKeywords::GetLexerName()
{
	return m_LexerName;
}


void CDlgEditKeywords::UpdateCtrls()
{
	if (m_hWnd)
	{
		if (m_Combo.GetCount()<=0)
		{
			m_Combo.ResetContent();
			char *posname=new char [1000];
			int CurNum=SeqArray.SelectFirst();
			while(CurNum!=0xFFFFFFFFL)
			{
				int itm=0;

				sprintf(posname,"%s,%d",m_LexerName==""?"APPENDKEYWORDS":(LPCSTR)m_LexerName,CurNum);
				itm=m_Combo.AddString(posname);
				m_Combo.SetItemData(itm,CurNum);

				CurNum=SeqArray.SelectNext();
			}
			delete[] posname;
		}

		m_List.DeleteAllItems();
		m_CurItem=0;

		if (m_Combo.GetCurSel()!=CB_ERR)
		{
			CString tmps;
			int nfld=0;
			CString LastKW="";
			do
			{
				tmps=ExtractField(SeqArray[m_curSubType],++nfld," ");
				if (tmps!="" && tmps!=LastKW)
				{
					m_List.InsertItem(0,tmps);
					LastKW=tmps;
				}

			}
			while(tmps!="");

			if (m_TypeKeyword==DEK_KEYWORDAPPEND)
				m_EditAppendText.SetWindowText(SeqArrayAppend[m_curSubType]);
			m_List.SetItemState(m_CurItem,LVIS_SELECTED,LVIS_SELECTED);
			m_List.SortItems(NULL,0);
			m_List.EnsureVisible(0,FALSE);
		}
		else
		{
			m_curSubType=0;
			m_Combo.SetCurSel(0);
			OnSelchangeComboType();
		}
	}
	ResetVisibility();
}

UINT CDlgEditKeywords::LoadKeywords()
{
	SeqArray.ResetArray();
	SeqArrayAppend.ResetArray();
	if (m_Combo.m_hWnd) m_Combo.ResetContent();
	FILE *src=NULL;
	m_CurItem=0;

	if (m_LexerName!="" || m_TypeKeyword)
	{
		src=fopen("LexKeywords.txt","rb");
		if (src)
		{
			char *tmps=new char [11000];
			char *posname=tmps+10000;
			CString cmpName;
			switch(m_TypeKeyword)
			{
			case DEK_KEYWORD:
				cmpName=m_LexerName;
				break;
			case DEK_KEYWORDAPPEND:
				cmpName="APPENDKEYWORDS";
				break;
			}

			while(fgetsEx(tmps,9990,src))
			{
				if (ExtractField(tmps,1,",")==cmpName)
				{
					int nSubKey=atoi(ExtractField(tmps,2,","));
					sprintf(posname,"%s,%d",(LPCSTR)cmpName,nSubKey);

					int itm=0;
					if (m_Combo.m_hWnd) itm=m_Combo.AddString(posname);
					if (itm!=CB_ERR)
					{
						if (m_Combo.m_hWnd) m_Combo.SetItemData(itm,nSubKey);
						char *pos2=tmps,*pos3=tmps;
						do
						{
							if (*pos2==' ' && pos3[1]==' ') pos3++;
							else *(pos2++)=*(pos3++);
						}
						while(*pos3);

						switch(m_TypeKeyword)
						{
						case DEK_KEYWORD:
							SeqArray[nSubKey]=FindField(tmps,3,",");
							break;
						case DEK_KEYWORDAPPEND:
							SeqArray[nSubKey]=FindField(ExtractField(tmps,1,"_APPKWDELIM_"),3,",");
							SeqArrayAppend[nSubKey]=ExtractField(tmps,2,"_APPKWDELIM_");
							break;
						}
					}
				}
			}
			if (m_Combo.m_hWnd) m_Combo.SetCurSel(0);
			delete[] tmps;
			fclose(src);
		}
	}

	UpdateCtrls();

	return SeqArray.GetCount();
}

BOOL CDlgEditKeywords::SaveKeywords()
{
	BOOL ret=FALSE;
	int nKeyLists=SeqArray.GetCount();
	if ((m_LexerName!="" || m_TypeKeyword) && nKeyLists)
	{
		FILE *src=NULL;
		FILE *dst=NULL;
		src=fopen("LexKeywords.txt","rt");
		if (src)
		{
			dst=fopen("LexKeywords.tmp","wt");
			if (dst)
			{
				ret=TRUE;
				int CurNum=0;
				char *tmps=new char [10000];
				switch(m_TypeKeyword)
				{
				case DEK_KEYWORD:
					while(fgetsEx(tmps,9990,src))
					{
						if (ExtractField(tmps,1,",")!=m_LexerName)
							fprintf(dst,"%s\n",tmps);
					}

					CurNum=SeqArray.SelectFirst();
					while(CurNum!=0xFFFFFFFFL)
					{
						fprintf(dst,"%s,%d,%s\n",(LPCSTR)m_LexerName,CurNum,(LPCSTR)SeqArray[CurNum]);
						CurNum=SeqArray.SelectNext();
					}
					break;
				case DEK_KEYWORDAPPEND:
					while(fgetsEx(tmps,9990,src))
					{
						if (ExtractField(tmps,1,",")!="APPENDKEYWORDS")
							fprintf(dst,"%s\n",tmps);
					}

					CurNum=SeqArray.SelectFirst();
					while(CurNum!=0xFFFFFFFFL)
					{
						fprintf(dst,"APPENDKEYWORDS,%d,%s_APPKWDELIM_%s\n",CurNum,(LPCSTR)SeqArray[CurNum],(LPCSTR)SeqArrayAppend[CurNum]);
						CurNum=SeqArray.SelectNext();
					}
					break;
				default:
					break;
				}

				fclose(dst);
				delete[] tmps;
			}
			fclose(src);
			if (ret)
			{
				CopyFile("LexKeywords.tmp","LexKeywords.txt",FALSE);
			}
			DeleteFile("LexKeywords.tmp");
		}
	}
	return ret;
}


void CDlgEditKeywords::FindAndSelect(const char *text)
{
	LVFINDINFO fi={0};
    fi.flags=LVFI_STRING;
    fi.psz=text;
    fi.vkDirection=VK_DOWN;

	int n_Item=m_List.FindItem(&fi);
	if (n_Item>=0)
	{
		m_CurItem=n_Item;
		m_List.SetItemState(m_CurItem,LVIS_SELECTED,LVIS_SELECTED);
		m_List.EnsureVisible(m_CurItem,FALSE);
	}
}

void CDlgEditKeywords::OnEndlabeleditListKeywords(NMHDR* pNMHDR, LRESULT* pResult)
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	if (pDispInfo)
	{
		if (pDispInfo->item.pszText)
		{
			SetKeywordText(pDispInfo->item.pszText);
			m_Edit.SetSel(0,-1);
			m_Edit.ReplaceSel(pDispInfo->item.pszText);
			FindAndSelect(pDispInfo->item.pszText);
		}
	}
	*pResult = 0;
}

void CDlgEditKeywords::SetKeywordText(const char *text)
{
	m_List.SetItemText(m_CurItem,0,text);
	UpdateSeqArray();
	m_List.SortItems(NULL,0);
	FindAndSelect(text);
}

UINT CDlgEditKeywords::SetTypeKeyword(UINT iTypeKeyword)
{
	UINT ret=m_TypeKeyword;
	switch(iTypeKeyword)
	{
	case DEK_KEYWORD:
		m_TypeKeyword=iTypeKeyword;
		break;
	case DEK_KEYWORDAPPEND:
		m_TypeKeyword=iTypeKeyword;
		LoadKeywords();
		break;
	default:
		break;
	}
	ResetVisibility();
	return ret;
}

void CDlgEditKeywords::ResetVisibility()
{
	if (m_hWnd)
	{
		DWORD delstl=0;
		DWORD addstl=0;
		switch(m_TypeKeyword)
		{
		case DEK_KEYWORD:
			delstl=WS_VISIBLE;
			break;
		case DEK_KEYWORDAPPEND:
			addstl=WS_VISIBLE;
			break;
		default:
			break;
		}
		m_EditAppendText.ModifyStyle(delstl,addstl);
		m_StaticAppend.ModifyStyle(delstl,addstl);
		m_BtnAddAppendKW.ModifyStyle(delstl,addstl);
		m_BtnDeleteAppendKW.ModifyStyle(delstl,addstl);
	}
}

void CDlgEditKeywords::OnButtonaddAppendKW()
{
	int InsItem=0;
	int nItems=m_Combo.GetCount();
	CString tmps="";
	if (nItems>0)
		for(InsItem=0;InsItem<nItems && m_Combo.GetItemData(InsItem)==(DWORD)InsItem;InsItem++);

	tmps.Format("APPENDKEYWORDS,%d",InsItem);
	nItems=m_Combo.InsertString(InsItem,tmps);
	m_Combo.SetItemData(nItems,InsItem);
	SeqArray[InsItem]="";
	SeqArrayAppend[InsItem]="";
	m_Combo.SetCurSel(nItems);
}

void CDlgEditKeywords::OnButtondeleteAppendKW()
{
	int nDelItem=m_Combo.GetCurSel();
	if (nDelItem>=0)
	{
		int Id=m_Combo.GetItemData(nDelItem);
		SeqArray.RemoveItem(Id);
		SeqArrayAppend.RemoveItem(Id);
		m_Combo.DeleteString(nDelItem);
		if (nDelItem) nDelItem--;
		if (nDelItem<m_Combo.GetCount())
			m_Combo.SetCurSel(nDelItem);
		else OnSelchangeComboType();
	}
	else OnSelchangeComboType();
}

void CDlgEditKeywords::OnChangeEditAppendKW()
{
	int nDelItem=m_Combo.GetCurSel();
	if (nDelItem>=0)
	{
		int Id=m_Combo.GetItemData(nDelItem);
		m_EditAppendText.GetWindowText(SeqArrayAppend[Id]);
	}
}

UINT CDlgEditKeywords::UpdateSeqArray()
{
	int nkeys=m_List.GetItemCount();
	SeqArray[m_curSubType]="";
	int i;
	for(i=0;i<nkeys;i++)
	{
		CString tmps=m_List.GetItemText(i,0);
		if (tmps!="")
		{
			if (SeqArray[m_curSubType]!="") SeqArray[m_curSubType]+=" ";
			SeqArray[m_curSubType]+=tmps;
		}
	}
	return (UINT)nkeys;
}
