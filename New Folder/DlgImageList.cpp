// DlgImageList.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgImageList.h"
#include "DlgImageMask.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgImageList dialog
#define ILCMND_NEXT		0x0010
#define ILCMND_PREV		0x0011
#define ILCMND_DELETE	0x0012
#define ILCMND_LIST		0x0013
#define ILCMND_SICON	0x0014
#define ILCMND_LICON	0x0015
#define ILCMND_LOAD		0x0016
#define ILCMND_SAVE		0x0017
#define ILCMND_ADDIMAGE	0x0018

CString CDlgImageList::m_csLastDirSave="IMAGELISTS";
CString CDlgImageList::m_csLastDirLoad="IMAGELISTS";
CString CDlgImageList::m_csLastDirAdd="IMAGELISTS";

CDlgImageList::CDlgImageList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgImageList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgImageList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_CurImageList=NULL;
}


void CDlgImageList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgImageList)
	DDX_Control(pDX, IDC_EDITRESULT, m_EditResult);
	DDX_Control(pDX, IDC_BTNADD, m_BtnAdd);
	DDX_Control(pDX, IDC_BTNDELETE, m_btnDelete);
	DDX_Control(pDX, IDC_BTNEXECUTE, m_btnExecute);
	DDX_Control(pDX, IDC_STATICPARAMS, m_StatParams);
	DDX_Control(pDX, IDC_COMBOIMAGELISTS, m_ComboImageLists);
	DDX_Control(pDX, IDC_EDITPARAMS, m_EditParams);
	DDX_Control(pDX, IDC_COMBOMETHODS, m_ComboMethods);
	DDX_Control(pDX, IDC_LIST1, m_IList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgImageList, CDialog)
	//{{AFX_MSG_MAP(CDlgImageList)
	ON_BN_CLICKED(IDC_BTNADD, OnBtnadd)
	ON_BN_CLICKED(IDC_BTNDELETE, OnBtndelete)
	ON_BN_CLICKED(IDC_BTNEXECUTE, OnBtnexecute)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBOIMAGELISTS, OnSelchangeComboimagelists)
	ON_CBN_SELCHANGE(IDC_COMBOMETHODS, OnSelchangeCombomethods)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgImageList message handlers

BOOL CDlgImageList::OnInitDialog()
{
	CDialog::OnInitDialog();

	FillIListList();

	UINT i;

	for(i=0;i<GPImageList::uNMethods;i++)
		m_ComboMethods.AddString(GPImageList::cArrMethods[i]);

	m_ComboImageLists.SetCurSel(0);
	OnSelchangeComboimagelists();

	m_ComboMethods.SetCurSel(0);
	OnSelchangeCombomethods();


		unsigned char BtnsStyle[]={
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			TBSTYLE_SEP,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			TBSTYLE_SEP   ,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			TBSTYLE_SEP   ,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
			BTNS_AUTOSIZE|BTNS_BUTTON,
		};

		unsigned char BtnsState[]={
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			0,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			0,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			0,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
			TBSTATE_ENABLED,
		};

		DWORD BtnsStrings[]={0,1,-1,2,3,-1,4,8,-1,5,6,7,-1,9,-1,10,11,12,13,14,-1,15,18,-1,19,};
		DWORD BtnsImage[]=	{41,40,-1,10,2,-1,39,48,-1,36,38,37,-1,8,9,-1,};
		DWORD BtnsCommands[]={
			ILCMND_NEXT,
			ILCMND_PREV,
			0,
			ILCMND_LOAD,
			ILCMND_SAVE,
			0,
			ILCMND_DELETE,
			ILCMND_ADDIMAGE,
			0,
			ILCMND_LIST,
			ILCMND_SICON,
			ILCMND_LICON,
			0,
		};


	CRect reToolBar(5,372,250,397);
#ifndef _VC80_UPGRADE
	m_ToolBar.CreateEx(0,TOOLBARCLASSNAME,NULL,CCS_NORESIZE|CCS_NODIVIDER|CCS_NOPARENTALIGN|TBSTYLE_LIST|TBSTYLE_TOOLTIPS|WS_CHILD|WS_VISIBLE|TBSTYLE_TRANSPARENT,reToolBar,this,12346,NULL);
#else
	m_ToolBar.CreateEx(0,CCS_NORESIZE|CCS_NODIVIDER|CCS_NOPARENTALIGN|TBSTYLE_LIST|TBSTYLE_TOOLTIPS|WS_CHILD|WS_VISIBLE|TBSTYLE_TRANSPARENT,reToolBar,this,12346);
#endif
	m_ToolBar.SetExtendedStyle(TBSTYLE_EX_MIXEDBUTTONS);
	m_ToolBar.AddStrings(
						#ifdef RUS
						"Переместить вперед\0Переместить назад\0Загрузить\0Сохранить\0Удалить элемент\0Спиок\0Мелкие значки\0Крупные значки\0Добавить изображение\0 \0"
						#else
						"Move forward\0Move back\0Load\0Save\0Delete Image\0List\0Small Icon\0Icon\0Add Image\0 \0"
						#endif
						);

	m_ToolBar.SetButtonSize(CSize(16,16));
	m_ToolBar.SetImageList(&GPC.a_GPImageList[GPC.GetImageListId("SEPVIEW")].m_IL);
	m_ToolBar.SetDisabledImageList(&GPC.a_GPImageList[GPC.GetImageListId("SEPVIEWDIS")].m_IL);

	TBBUTTON tbt={0};
	for(i=0;i<12;i++)
	{
		tbt.iBitmap=BtnsImage[i];
		tbt.idCommand=BtnsCommands[i];
		tbt.iString=BtnsStrings[i];
		tbt.dwData=NULL;
		tbt.fsState=BtnsState[i];
		tbt.fsStyle=BtnsStyle[i];
		m_ToolBar.InsertButton(i,&tbt);
	}

	AUSI.AddSetMain(this->m_hWnd);
	AUSI.AddWnd(m_btnExecute.m_hWnd		,this->m_hWnd,"NENE");
	AUSI.AddWnd(m_btnDelete.m_hWnd		,this->m_hWnd,"NENE");
	AUSI.AddWnd(m_BtnAdd.m_hWnd			,this->m_hWnd,"NENE");

	AUSI.AddWnd(m_ComboImageLists.m_hWnd,this->m_hWnd,"NNNE");
	AUSI.AddWnd(m_ComboMethods.m_hWnd	,this->m_hWnd,"NNNE");
	AUSI.AddWnd(m_EditParams.m_hWnd		,this->m_hWnd,"NNNE");
	AUSI.AddWnd(m_StatParams.m_hWnd		,this->m_hWnd,"NNNE");
	AUSI.AddWnd(m_EditResult.m_hWnd		,this->m_hWnd,"NNNE");
	AUSI.AddWnd(m_IList.m_hWnd			,this->m_hWnd,"NNEE");
	AUSI.AddWnd(m_ToolBar.m_hWnd		,this->m_hWnd,"ENEN");

	AUSI.SetMinSize(this->m_hWnd,330,321);

	return TRUE;
}

void CDlgImageList::OnDestroy()
{
	CDialog::OnDestroy();
}

void CDlgImageList::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if (m_hWnd)
	{
		try{AUSI.UpdateSize();}catch(...){GPC.m_ErrReport.GPWriteErrorLog("CDlgImageList", "OnSize","199");}
	}
}

#include "DlgCreateImageList.h"

void CDlgImageList::OnBtnadd()
{
	CDlgCreateImageList dlg;
	dlg.SetCreateFlag(ILC_COLORDDB|ILC_MASK|ILC_COLOR8);

	if (dlg.DoModal()!=IDCANCEL)
	{
		if (dlg.m_Name!="")
		{
			int id=GPC.GetImageListId("");
			GPC.a_GPImageList[id].DeleteList();
			DWORD ILStyle=dlg.GetCreateFlag();
			int mCX=dlg.m_EdX;
			int mCY=dlg.m_EdY;

			if (GPC.a_GPImageList[id].m_IL.Create(mCX,mCY,ILStyle,dlg.m_EdInit,dlg.m_EdDelta))
			{
				GPC.a_GPImageList[id].ILName=dlg.m_Name;
				int newitem=m_ComboImageLists.AddString(dlg.m_Name);
				if (newitem!=CB_ERR)
				{
					m_CurImageList=NULL;
					m_ComboImageLists.SetCurSel(newitem);
					OnSelchangeComboimagelists();
				}
			}
		}
	}
}

void CDlgImageList::OnBtndelete()
{
	if (m_CurImageList)
	{
		#ifdef RUS
			if (MessageBox("Выгрузить список изображений?","Редактор списка изображений",MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2)==IDYES)
		#else
			if (MessageBox("Unload ImageList?","ImageList Editor",MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2)==IDYES)
		#endif
		{
			int sel=m_ComboImageLists.GetCurSel();
			if (sel!=CB_ERR)
			{
				m_CurImageList->DeleteList();
				m_CurImageList=NULL;

				m_ComboImageLists.DeleteString(sel);
				if (sel>0) sel--;
				if (m_ComboImageLists.GetCount()>0)
					m_ComboImageLists.SetCurSel(sel);
				OnSelchangeComboimagelists();
			}
		}
	}
}

void CDlgImageList::OnBtnexecute()
{
	m_EditResult.SetWindowText("");
	CString str;
	CString strParam;
	m_ComboMethods.GetWindowText(str);
	m_EditParams.GetWindowText(strParam);
	str+=" "+strParam;

	if (m_CurImageList)
	{
		int nItems=m_CurImageList->m_IL.GetImageCount();
		char *oStr=new char [TMP_STR_OUT_LEN+10];
		if (oStr)
		{
			*oStr=0;
			m_CurImageList->DoMethod(str,oStr);
			m_EditResult.SetWindowText(oStr);
			delete[] oStr;
		}
		if (nItems!=m_CurImageList->m_IL.GetImageCount())
			ResetILList();
		else m_IList.Invalidate();
	}
}

void CDlgImageList::FillIListList()
{
	m_ComboImageLists.ResetContent();
	int i=0;
	while(i<GP_NIMAGELIST)
	{
		if (GPC.a_GPImageList[i].ILName!="")
		{
			int ilid=m_ComboImageLists.AddString(GPC.a_GPImageList[i].ILName);
			if (ilid!=CB_ERR && m_CurImageList && m_CurImageList->ILName==GPC.a_GPImageList[i].ILName)
				m_ComboImageLists.SetCurSel(ilid);
		}
		i++;
	}
}

void CDlgImageList::OnSelchangeComboimagelists()
{
	CString str;
	m_ComboImageLists.GetWindowText(str);
	m_CurImageList=NULL;
	if (str!="")
	{
		DWORD IlId=GPC.GetImageListId(str);
		if (IlId<GP_NIMAGELIST)
			m_CurImageList=&(GPC.a_GPImageList[IlId]);
	}
	ResetILList();
}

void CDlgImageList::OnSelchangeCombomethods()
{
	CString str;
	m_ComboMethods.GetWindowText(str);
	UINT i;
	for(i=0;i<GPImageList::uNMethods;i++)
		if (str==GPImageList::cArrMethods[i]) break;
	m_StatParams.SetWindowText(GPImageList::cArrMethodsParams[i]);
}

void CDlgImageList::ResetILList()
{
	m_IList.DeleteAllItems();
	if (m_CurImageList)
	{
		try
		{
			ReSetImageList();
			int nItems=m_CurImageList->m_IL.GetImageCount();
			int i;
			char str[100];
			for(i=0;i<nItems;i++)
			{
				sprintf(str,"%4.4d",i);
				m_IList.InsertItem(i,str,i);
			}
		}catch(...){;}
	}
}

BOOL CDlgImageList::OnCommand(WPARAM wParam, LPARAM lParam)
{
	BOOL Commandret=TRUE;
	if (wParam==1)
	{
		Commandret=FALSE;
	}
	else
	if (((HWND)lParam)==m_ToolBar.m_hWnd && m_CurImageList)
	{
		try
		{
			switch(LOWORD(wParam))
			{
			case ILCMND_PREV:
				{
					POSITION pos = m_IList.GetFirstSelectedItemPosition();
					int ItmCount=m_IList.GetItemCount();
					int PrevItem=-1;
					int NextItem=-1;
					while(pos)
					{
						int nItem = m_IList.GetNextSelectedItem(pos);
						if (PrevItem<0) PrevItem=nItem;
						NextItem=nItem+1;
						if (NextItem>=0 && NextItem<ItmCount)
						{
							m_CurImageList->m_IL.Copy(PrevItem,NextItem,ILCF_SWAP);
							int nstate=m_IList.GetItemState(NextItem,LVIS_SELECTED);
							if (nstate!=LVIS_SELECTED || pos==NULL)
								PrevItem=-10;
						}
					}
					ReSetImageList();

					pos = m_IList.GetFirstSelectedItemPosition();
					ItmCount=m_IList.GetItemCount();
					PrevItem=-1;
					NextItem=-1;
					while(pos)
					{
						int nItem = m_IList.GetNextSelectedItem(pos);
						if (PrevItem<0) PrevItem=nItem;
						NextItem=nItem+1;
						if (NextItem>=0 && NextItem<ItmCount)
						{
							int nstate=m_IList.GetItemState(NextItem,LVIS_SELECTED);
							if (nstate!=LVIS_SELECTED || pos==NULL)
							{
								m_IList.SetItemState(PrevItem,0,LVIS_SELECTED);
								m_IList.SetItemState(NextItem,LVIS_SELECTED,LVIS_SELECTED);
//								if (pos) m_IList.GetNextSelectedItem(pos);
								PrevItem=-10;
							}
						}
					}
				}
				break;
			case ILCMND_NEXT:
				{
					POSITION pos = m_IList.GetFirstSelectedItemPosition();
					while(pos)
					{
						int nItem = m_IList.GetNextSelectedItem(pos);
						if (nItem>0)
							m_CurImageList->m_IL.Copy(nItem-1,nItem,ILCF_SWAP);
					}
					ReSetImageList();
					pos = m_IList.GetFirstSelectedItemPosition();
					while(pos)
					{
						int nItem = m_IList.GetNextSelectedItem(pos);
						if (nItem>0)
						{
							m_IList.SetItemState(nItem,0,LVIS_SELECTED);
							m_IList.SetItemState(nItem-1,LVIS_SELECTED,LVIS_SELECTED);
						}
					}
				}
				break;
			case ILCMND_LOAD:
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
					opf.Flags =OFN_HIDEREADONLY|OFN_ENABLESIZING|OFN_EXPLORER|OFN_FILEMUSTEXIST|OFN_LONGNAMES|OFN_PATHMUSTEXIST|OFN_NOCHANGEDIR|OFN_SHOWHELP;
					#ifdef RUS
						opf.lpstrFilter="Файл списка изображений (*.GIL)\x0*.GIL\x0";
						opf.lpstrTitle="Чтение списка изображений";
					#else
						opf.lpstrFilter="ImageList File (*.GIL)\x0*.GIL\x0";
						opf.lpstrTitle="Load ImageList File";
					#endif
					opf.lpstrDefExt="GIL";

					opf.lpstrInitialDir=m_csLastDirLoad;

					if (GetOpenFileName(&opf))
					{
						m_csLastDirLoad=opf.lpstrFile;
						m_csLastDirLoad=m_csLastDirLoad.Left(::GetFileName((LPCSTR)m_csLastDirLoad)-(LPCSTR)m_csLastDirLoad-1);

						if (m_CurImageList->LoadList(opf.lpstrFile))
						{
							m_CurImageList->ILName=ExtractField(::GetFileName(opf.lpstrFile),0,".");
							FillIListList();
							OnSelchangeComboimagelists();
						}
					}
					delete[] opf.lpstrFile;
				}
				break;
			case ILCMND_SAVE:
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
					opf.Flags =OFN_CREATEPROMPT|OFN_NOREADONLYRETURN|OFN_OVERWRITEPROMPT|OFN_DONTADDTORECENT|OFN_HIDEREADONLY|OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_PATHMUSTEXIST|OFN_NOCHANGEDIR|OFN_SHOWHELP;
					#ifdef RUS
						opf.lpstrFilter="Файл списка изображений (*.GIL)\x0*.GIL\x0";
						opf.lpstrTitle="Запись списка изображений";
					#else
						opf.lpstrFilter="ImageList File (*.GIL)\x0*.GIL\x0";
						opf.lpstrTitle="Save ImageList File";
					#endif
					opf.lpstrDefExt="GIL";

					opf.lpstrInitialDir=m_csLastDirLoad;

					if (GetSaveFileName(&opf))
					{
						m_csLastDirSave=opf.lpstrFile;
						m_csLastDirSave=m_csLastDirSave.Left(::GetFileName((LPCSTR)m_csLastDirSave)-(LPCSTR)m_csLastDirSave-1);
						m_CurImageList->WriteList(opf.lpstrFile);
					}

					delete[] opf.lpstrFile;
				}
				break;
			case ILCMND_DELETE:
				#ifdef RUS
					if (MessageBox("Удалить выбранные элементы?","Редактор списка изображений",MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2)==IDYES)
				#else
					if (MessageBox("Delete selected items?","ImageList Editor",MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2)==IDYES)
				#endif
				{
					POSITION pos = m_IList.GetFirstSelectedItemPosition();
					int nDeleted=0;
					while(pos)
					{
						int nItem = m_IList.GetNextSelectedItem(pos);
						if (nItem>=0)
							m_CurImageList->m_IL.Remove(nItem-nDeleted++);
					}
					pos = m_IList.GetFirstSelectedItemPosition();
					while(pos)
					{
						int nItem = m_IList.GetNextSelectedItem(pos);
						if (nItem>=0)
							m_IList.DeleteItem(nItem);
					}
					ResetILList();
				}
				break;
			case ILCMND_LIST:
				m_IList.SendMessage(LVM_SETVIEW,LV_VIEW_LIST,0);
				m_IList.ModifyStyle(LVS_ICON|LVS_REPORT|LVS_SMALLICON|LVS_LIST,LVS_SMALLICON|LVS_LIST);
				break;
			case ILCMND_SICON:
				m_IList.ModifyStyle(LVS_ICON|LVS_REPORT|LVS_SMALLICON|LVS_LIST,LVS_SMALLICON);
				m_IList.SendMessage(LVM_SETVIEW,LV_VIEW_SMALLICON,0);
				break;
			case ILCMND_LICON:
				m_IList.ModifyStyle(LVS_ICON|LVS_REPORT|LVS_SMALLICON|LVS_LIST,LVS_ICON);
				m_IList.SendMessage(LVM_SETVIEW,LV_VIEW_ICON,0);
				break;
			case ILCMND_ADDIMAGE:
				if (m_CurImageList)
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
					opf.lpstrFile = new char [25000];
					*opf.lpstrFile=0;
					opf.nMaxFile =24900;
					opf.Flags =OFN_ALLOWMULTISELECT|OFN_DONTADDTORECENT|OFN_DONTADDTORECENT|OFN_HIDEREADONLY|OFN_ENABLESIZING|OFN_EXPLORER|OFN_FILEMUSTEXIST|OFN_LONGNAMES|OFN_PATHMUSTEXIST|OFN_NOCHANGEDIR|OFN_SHOWHELP;
					#ifdef RUS
						opf.lpstrFilter="Файл значков (*.ICO)\x0*.ICO\x0Графические файлы (*.BMP)\x0*.BMP\x0JPEG files (*.JPG)\x0*.JPG\x0GIF files (*.GIF)\x0*.GIF\x0Все форматы (*.*)\x0*.*\x0";
						opf.lpstrTitle="Добавление изображения в список";
					#else
						opf.lpstrFilter="Icons (*.ICO)\x0*.ICO\x0Pictures (*.BMP)\x0*.BMP\x0JPEG files (*.JPG)\x0*.JPG\x0GIF files (*.GIF)\x0*.GIF\x0 All (*.*)\x0*.*\x0";
						opf.lpstrTitle="Add in ImageList";
					#endif
					opf.lpstrDefExt="GIL";

					opf.lpstrInitialDir=m_csLastDirAdd;

					if (GetOpenFileName(&opf))
					{
						if (opf.lpstrFile && *(opf.lpstrFile))
						{
							BOOL bDoMaskDlg=TRUE;
							m_csLastDirAdd=opf.lpstrFile;
							CDlgImageMask dlg(m_CurImageList,opf.lpstrFile);

							char *pos=opf.lpstrFile;
							while(*(pos++));
							if (!*pos)
							{
								m_csLastDirAdd=m_csLastDirAdd.Left(::GetFileName((LPCSTR)m_csLastDirAdd)-(LPCSTR)m_csLastDirAdd-1);
								pos=opf.lpstrFile+m_csLastDirAdd.GetLength()+1;
							}
							do
							{
								CString fname=m_csLastDirAdd;
								if (fname!="") fname+="\\"; 
								fname+=pos;

								if (strstr(pos,".ico") || strstr(pos,".ICO"))
								{
									m_CurImageList->AddFromFile(fname,0,0);
								}
								else
								{
									if (bDoMaskDlg)
									{
										bDoMaskDlg=FALSE;
										if (dlg.DoModal()==IDCANCEL) break;
									}
									
									m_CurImageList->AddFromFile(fname,0,RGB(dlg.m_EdR,dlg.m_EdG,dlg.m_EdB));
									ResetILList();
								}

								while(*(pos++));
							}while(*pos);
						}
						OnSelchangeComboimagelists();
					}
					delete[] opf.lpstrFile;
				}
				break;
			}
		}
		catch(...){
			GPC.m_ErrReport.GPWriteErrorLog("CDlgImageList", "OnCommand","");
		}
	}
	return Commandret?CDialog::OnCommand(wParam, lParam):FALSE;
}

void CDlgImageList::ReSetImageList()
{
	if (m_CurImageList)
	{
		m_IList.SetImageList(&m_CurImageList->m_IL,TVSIL_NORMAL);
		m_IList.SetImageList(&m_CurImageList->m_IL,LVSIL_SMALL);
	}
}

