// GP_DlgSetting.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GP_DlgSetting.h"
#include "GPObjDialog.h"
#include "GPFrameWnd.h"
#include "DlgMethods.h"
#include "DlgInitComObject.h"
#include "GPToolTipCtrl.h"

#include "GPUnit.h"
#include "GP_comm.h"
#include "GPChLBox.h"
#include "GPDrLBox.h"
#include "GPStatic.h"
#include "GPAniStatic.h"
#include "GPEdit.h"
#include "GPButton.h"
#include "GPAniButton.h"
#include "GPBButton.h"
#include "GPListBox.h"
#include "GPComboBox.h"
#include "GPComboBoxEx.h"
#include "GPScrollBar.h"
#include "GPProgress.h"
#include "GPAnimate.h"
#include "GPListCtr.h"
#include "GPDateTimeCtrl.h"
#include "GPMonthCalCtrl.h"
#include "GPSpinButton.h"
#include "GPTabCtrl.h"
#include "GPTree.h"
#include "GPSlider.h"
#include "GPHeader.h"
#include "GPToolBarCtrl.h"
#include "GPStatusBarCtrl.h"
#include "GPToolBar.h"
#include "GPStatusBar.h"
#include "GPDialogBar.h"
#include "GPReBarCtrl.h"
#include "GPReBar.h"
#include "GPDrawWnd.h"
#include "GP_RTF.h"
#include "GP_TermView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDialogEditor dialog

CDlgDialogEditor::CDlgDialogEditor(GPObjDialog* iGPOd, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDialogEditor::IDD, pParent)
{
	m_UpdateFlags=0x0001;
	xWindowProc=yWindowProc=0;
	CurUnit=NULL;
	NoUpdateTxt=TRUE;
	m_UpdSize=m_PosFlag=m_SizeFlag=FALSE;
	GPOd=iGPOd;
	GPOf=NULL;
	GPOw=NULL;
	RefGPU=iGPOd->GPU;
}

CDlgDialogEditor::CDlgDialogEditor(GPFrameWnd* iGPOd, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDialogEditor::IDD, pParent)
{
	xWindowProc=yWindowProc=0;
	CurUnit=NULL;
	NoUpdateTxt=TRUE;
	m_UpdSize=m_PosFlag=m_SizeFlag=FALSE;
	GPOw=NULL;
	GPOd=NULL;
	GPOf=iGPOd;
	RefGPU=iGPOd->GPU;
}

CDlgDialogEditor::CDlgDialogEditor(GPWindow* iGPOw, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDialogEditor::IDD, pParent)
{
	m_UpdateFlags=0x0001;
	xWindowProc=yWindowProc=0;
	CurUnit=NULL;
	NoUpdateTxt=TRUE;
	m_UpdSize=m_PosFlag=m_SizeFlag=FALSE;
	GPOw=iGPOw;
	GPOd=NULL;
	GPOf=NULL;
	RefGPU=iGPOw->WndUnit;
}


CDlgDialogEditor::~CDlgDialogEditor()
{
	m_UpdateFlags=0x0;
	if (m_hWnd) DestroyWindow();
}

void CDlgDialogEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDialogEditor)
	DDX_Control(pDX, IDC_CHECKWINDOWLESS, m_ChkWINDOWLESS);
	DDX_Control(pDX, IDC_BUTTONMESSAGETOCLIP, m_BtMessToClip);
	DDX_Control(pDX, IDC_BTNFRGDLG, m_btFRGDlg);
	DDX_Control(pDX, IDC_BTNBRUSHDLG, m_btBrushDlg);
	DDX_Control(pDX, IDC_BTNBKGDLG, m_btBKGDlg);
	DDX_Control(pDX, IDC_EDITFRG, m_edFRG);
	DDX_Control(pDX, IDC_EDITBRUSH, m_edBrush);
	DDX_Control(pDX, IDC_EDITBKG, m_edBKG);
	DDX_Control(pDX, IDC_CBBRUSHTYPE, m_cbBrushType);
	DDX_Control(pDX, IDC_CBBRUSHSTYLE, m_cbBrushStyle);
	DDX_Control(pDX, IDC_BTNFRG, m_btFRG);
	DDX_Control(pDX, IDC_BTNBRUSH, m_btBRUSH);
	DDX_Control(pDX, IDC_BTNBKG, m_btBKG);
	DDX_Control(pDX, IDC_BTNCLALLTEXT, m_btClearAllTextEv);
	DDX_Control(pDX, IDC_BTNCLALLEV, m_BtClAllEvents);
	DDX_Control(pDX, IDC_LISTEVENTS, m_ListEvents);
	DDX_Control(pDX, IDC_EDITEVENTSOUTPUT, m_EditEventsOutput);
	DDX_Control(pDX, IDC_STATICPROPERTY, m_StaticProperty);
	DDX_Control(pDX, IDC_EDITPROPERTY, m_EditProperty);
	DDX_Control(pDX, IDC_BTNDOPROPERTY, m_BtDoProperty);
	DDX_Control(pDX, IDC_EDITPARAMS, m_EditParams);
	DDX_Control(pDX, IDC_EDITRESULT, m_EditResult);
	DDX_Control(pDX, IDC_EDITPARAMSHELP, m_EditParamsHelp);
	DDX_Control(pDX, IDC_BUTTONEXECUTE, m_BtExecute);
	DDX_Control(pDX, IDC_COMBOMETHODS, m_ComboMethods);
	DDX_Control(pDX, IDC_CHECKSELECT, m_CheckAutoSel);
	DDX_Control(pDX, IDC_CHECKTOPMOST, m_ChecOnTop);
	DDX_Control(pDX, IDC_EDITWSE, m_EditWSE);
	DDX_Control(pDX, IDC_EDITWS, m_EditWS);
	DDX_Control(pDX, IDC_EDITOSE, m_EditOSE);
	DDX_Control(pDX, IDC_EDITOS, m_EditOS);
	DDX_Control(pDX, IDC_EDITGROUP, m_EditGroup);
	DDX_Control(pDX, IDC_STATICOWNER, m_StaticOwner);
	DDX_Control(pDX, IDC_STATICGROUP, m_StaticGroup);
	DDX_Control(pDX, IDC_COMBOOWNER, m_ComboOwner);
	DDX_Control(pDX, IDC_LISTUNITTYPE, m_ListUnitType);
	DDX_Control(pDX, IDC_STATICTOOLTIP, m_StaticToolTip);
	DDX_Control(pDX, IDC_EDITTOOLTIP, m_EditToolTip);
	DDX_Control(pDX, IDC_BUTTONCREATOCLIP, m_BtCreatToClip);
	DDX_Control(pDX, IDC_EDITTEXT, m_EditText);
	DDX_Control(pDX, IDC_STATICTEXT, m_StaticText);
	DDX_Control(pDX, IDC_STATICSIZING, m_StaticSizing);
	DDX_Control(pDX, IDC_EDITSIZING, m_EditSizing);
	DDX_Control(pDX, IDC_COMBOSIZING, m_ComboSizing);
	DDX_Control(pDX, IDC_STATICOBJSIZE, m_SOS);
	DDX_Control(pDX, IDC_STATIC4, m_Stat4);
	DDX_Control(pDX, IDC_STATIC3, m_Stat3);
	DDX_Control(pDX, IDC_STATIC2, m_Stat2);
	DDX_Control(pDX, IDC_STATIC1, m_Stat1);
	DDX_Control(pDX, IDC_STATICSIZE, m_StaticSize);
	DDX_Control(pDX, IDC_BUTTONDELETE, m_btdelete);
	DDX_Control(pDX, IDC_EDIT6, m_ed6);
	DDX_Control(pDX, IDC_EDIT5, m_ed5);
	DDX_Control(pDX, IDC_EDIT2, m_ed2);
	DDX_Control(pDX, IDC_EDIT1, m_ed1);
	DDX_Control(pDX, IDC_TAB1, m_Tabs);
	DDX_Control(pDX, IDC_LISTUSESTL2, m_ListUnitStl);
	DDX_Control(pDX, IDC_LISTUSESTL, m_WSList);
	DDX_Control(pDX, IDC_SPIN6, m_sw);
	DDX_Control(pDX, IDC_SPIN5, m_sh);
	DDX_Control(pDX, IDC_SPIN2, m_st);
	DDX_Control(pDX, IDC_SPIN1, m_sl);
	DDX_Control(pDX, IDC_LISTUNIT, m_LUnit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDialogEditor, CDialog)
	//{{AFX_MSG_MAP(CDlgDialogEditor)
	ON_LBN_SELCHANGE(IDC_LISTUNIT, OnSelchangeListunit)
	ON_LBN_DBLCLK(IDC_LISTUNIT, OnDblclkListunit)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeEdit6)
	ON_BN_CLICKED(IDC_BUTTONDELETE, OnButtondelte)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_LBN_DBLCLK(IDC_LISTUSESTL, OnDblclkListusestl)
	ON_LBN_DBLCLK(IDC_LISTUSESTL2, OnDblclkListusestl2)
	ON_BN_CLICKED(IDC_BUTTONUPDATE, OnButtonupdate)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_CBN_SELCHANGE(IDC_COMBOSIZING, OnSelchangeCombosizing)
	ON_EN_CHANGE(IDC_EDITSIZING, OnChangeEditsizing)
	ON_EN_CHANGE(IDC_EDITTEXT, OnChangeEdittext)
	ON_BN_CLICKED(IDC_BUTTONCREATOCLIP, OnButtoncreatoclip)
	ON_EN_CHANGE(IDC_EDITTOOLTIP, OnChangeEdittooltip)
	ON_LBN_DBLCLK(IDC_LISTUNITTYPE, OnDblclkListunittype)
	ON_LBN_KILLFOCUS(IDC_LISTUNITTYPE, OnKillfocusListunittype)
	ON_BN_CLICKED(IDC_BUTTONBUFFALL, OnButtonbuffall)
	ON_CBN_SELCHANGE(IDC_COMBOOWNER, OnSelchangeComboowner)
	ON_EN_KILLFOCUS(IDC_EDITGROUP, OnKillfocusEditgroup)
	ON_BN_CLICKED(IDC_CHECKTOPMOST, OnChecktopmost)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECKSELECT, OnCheckselect)
	ON_CBN_SELCHANGE(IDC_COMBOMETHODS, OnSelchangeCombomethods)
	ON_BN_CLICKED(IDC_BUTTONEXECUTE, OnButtonexecute)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTNDOPROPERTY, OnBtndoproperty)
	ON_LBN_DBLCLK(IDC_LISTEVENTS, OnDblclkListevents)
	ON_BN_CLICKED(IDC_BTNCLALLEV, OnBtnclallev)
	ON_BN_CLICKED(IDC_BTNCLALLTEXT, OnBtnclalltext)
	ON_BN_CLICKED(IDC_BTNFRGDLG, OnBtnfrgdlg)
	ON_BN_CLICKED(IDC_BTNFRG, OnBtnfrg)
	ON_BN_CLICKED(IDC_BTNBRUSH, OnBtnbrush)
	ON_BN_CLICKED(IDC_BTNBRUSHDLG, OnBtnbrushdlg)
	ON_BN_CLICKED(IDC_BTNBKG, OnBtnbkg)
	ON_BN_CLICKED(IDC_BTNBKGDLG, OnBtnbkgdlg)
	ON_BN_CLICKED(IDC_BUTTONMESSAGETOCLIP, OnButtonmessagetoclip)
	ON_BN_CLICKED(IDC_CHECKWINDOWLESS, OnCheckwindowless)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDialogEditor message handlers

BOOL CDlgDialogEditor::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetTimer(2,2000,0);
	m_Tabs.ModifyStyle(0,TCS_BUTTONS);
	if (RefGPU==NULL) OnClose();

	FillObjList(1);
	uStlComO=uStlO=uStlOE=uStlW=uStlWE=0;

	m_ListUnitType.ResetContent();
	int i;
	for(i=0;i<*GPUnit::aTypeUnit[i];i++)
		if ((int)strlen(GPUnit::aTypeUnit[i])>=3)
			m_ListUnitType.SetItemData(m_ListUnitType.AddString(GPUnit::aTypeUnit[i]),GPUnit::auTypeUnit[i]);

	m_st.SetRange(-5000,+5000);
	m_sl.SetRange(-5000,+5000);
	m_sw.SetRange(-5000,+5000);
	m_sh.SetRange(-5000,+5000);
	if (m_LUnit.SetCurSel(0)!=LB_ERR) OnSelchangeListunit();
	m_Tabs.InsertItem(0,"Obj");
	m_Tabs.InsertItem(1,"WS_");
	m_Tabs.InsertItem(2,"OBJS_");
	m_Tabs.InsertItem(3,"Prop");
	m_Tabs.InsertItem(4,"Size");
	m_Tabs.InsertItem(5,"Meth");
	m_Tabs.InsertItem(6,"Events");
	m_Tabs.SetCurSel(0);
	UpdateTabs();
	m_WSList.SetCheckStyle(BS_CHECKBOX);
	m_ListUnitStl.SetCheckStyle(BS_CHECKBOX);
	m_ListEvents.SetCheckStyle(BS_CHECKBOX);

	m_ComboMethods.SetDroppedWidth(370);

	return TRUE;
}

struct AFX_CHECK_DATA
{
public:
	int m_nCheck;
	BOOL m_bEnabled;
	DWORD m_dwUserData;

	AFX_CHECK_DATA()
	{
		m_nCheck = 0;
		m_bEnabled = TRUE;
		m_dwUserData = 0;
	};
};

void CDlgDialogEditor::OnSelchangeListunit()
{
	int id=m_LUnit.GetCurSel( );

	NoUpdateTxt=TRUE;

	//ClearItemsData(&m_WSList);
	//ClearItemsData(&m_ListUnitStl);

	m_WSList.ResetContent();
	m_ListUnitStl.ResetContent();
	m_ComboMethods.ResetContent();
	m_BtExecute.EnableWindow(FALSE);
	m_EditParamsHelp.SetWindowText("");

	m_ListEvents.ResetContent();


	CurUnit=NULL;

	if (id!=LB_ERR && RefGPU!=NULL && RefGPU[id]!=NULL)
	{
		CRect re;
		CurUnit=RefGPU[id];
		CurUnit->GPGetWndRect(&re);
		m_ChkWINDOWLESS.ModifyStyle(0,WS_DISABLED);
		m_ChkWINDOWLESS.SetCheck(CurUnit->m_WindowLessFlag);

		if (id!=0 && CurUnit->UnitHWND!=NULL)
		{
			CPoint ppp(0,0);
			if (CurUnit->UnitHWND)
			{
				HWND parent=::GetParent(CurUnit->UnitHWND);
				if (parent)	::ClientToScreen(parent,&ppp);
			}
			re.OffsetRect(-ppp);
		}

		m_UpdSize=FALSE;
		m_st.SetPos(re.top);
		m_sl.SetPos(re.left);
		m_sw.SetPos(re.Width());
		m_sh.SetPos(re.Height());
		m_UpdSize=TRUE;
		OnChangeEdit1();

		m_BtExecute.EnableWindow(TRUE);
		if (GPOf)
			CDlgMethods::FillMethodCombo(CurUnit->UnitType,&m_ComboMethods,CurUnit,GPUnit::UST_FRAME);
		else
		if (GPOw)
			CDlgMethods::FillMethodCombo(CurUnit->UnitType,&m_ComboMethods,CurUnit,GPUnit::UST_SCREEN);
		else
			CDlgMethods::FillMethodCombo(CurUnit->UnitType,&m_ComboMethods,CurUnit,GPUnit::UST_DLG);

		if (CurUnit->GPMSG!=NULL)
		{
			if (CurUnit->UnitType==GPUnit::UT_CONTROL)
			{
				CString tmps;
				CString tmps2;
				AX_NAMES anm;
				anm.cbSize=sizeof(AX_NAMES);
				anm.NamesArr=tmps.AllocSysString();
				anm.DescriptionsArr=tmps.AllocSysString();
				::SendMessage(CurUnit->UnitHWND,GPM_AX_GETEVENTS,0,(LPARAM)(&anm));
				tmps=anm.NamesArr;
				tmps2=anm.DescriptionsArr;
				CString tmpEv;
				int i=0;
				while((tmpEv=ExtractField(tmps,i+1,"\x1"))!="")
				{
					int tmpNitem=m_ListEvents.AddString(tmpEv);
					m_ListEvents.SetCheck(tmpNitem,atoi(ExtractField(tmps2,++i,"\x1")));
				}
				::SysFreeString(anm.DescriptionsArr);
				::SysFreeString(anm.NamesArr);
			}
			char *tmpc=new char [(int)strlen(CurUnit->GPMSG->E_List)+100];
			strcpy(tmpc,CurUnit->GPMSG->E_List);
			char *postmp=tmpc;
			while(*postmp!=0)
			{
				char *pos2=postmp;
				while(*pos2!=0 && *pos2!=',') pos2++;
				if (*pos2!=0) *(pos2++)=0;
				int nItem=m_ListEvents.AddString(postmp);
				if (nItem!=LB_ERR && CurUnit->GPMSG->FindInActive(postmp)!=NULL)
					m_ListEvents.SetCheck(nItem,1);
				postmp=pos2;
			}

			int i;
			for(i=0;i<N_WND_MESSAGE;i++)
			{
				int nItem=m_ListEvents.AddString(alpmes[i]);
				if (nItem!=LB_ERR && CurUnit->GPMSG->FindInActive(alpmes[i])!=NULL)
					m_ListEvents.SetCheck(nItem,1);
			}
			delete[] tmpc;
		}
		CurUnit->GPMSG->m_OutputEdit=&m_EditEventsOutput;
	}
	else
	{
		m_ChkWINDOWLESS.ModifyStyle(WS_DISABLED,0);
		CurUnit=NULL;
		m_st.SetPos(0);
		m_sl.SetPos(0);
		m_sw.SetPos(0);
		m_sh.SetPos(0);
	}

	UpdateChecks(1);
//	UpdateCheckEvents();
	UpdateTabs();
	NoUpdateTxt=FALSE;
	Invalidate();
}


void CDlgDialogEditor::OnChangeEdit1()
{

	if (m_UpdSize==TRUE && m_LUnit.m_hWnd!=NULL &&  CurUnit!=NULL && m_sl.m_hWnd!=NULL)
	{
		char str[250];
		sprintf(str,"RECT=%d,%d,%d,%d",m_sl.GetPos( ),m_st.GetPos( ),m_sl.GetPos( )+m_sw.GetPos( ),m_st.GetPos( )+m_sh.GetPos( ));

		if (NoUpdateTxt==FALSE)	CurUnit->GPSetProperty(str);

		CRect reStaticSize,MainRect;

		if (m_LUnit.GetCurSel( )==0) MainRect=CRect(0,0,800,600);
		else RefGPU[0]->GPGetWndRect(&MainRect);

		m_StaticSize.GetWindowRect(&reStaticSize);
		ScreenToClient(&reStaticSize);

		if (MainRect.IsRectEmpty()==FALSE)
		{
			double mx=(double)reStaticSize.Width()/(double)MainRect.Width();
			double my=(double)reStaticSize.Height()/(double)MainRect.Height();
			CRect rrr=CRect(
				(int)(m_sl.GetPos( )*mx)+reStaticSize.left,
				(int)(m_st.GetPos( )*my)+reStaticSize.top,
				(int)((m_sl.GetPos( )+m_sw.GetPos( ))*mx)+reStaticSize.left,
				(int)((m_st.GetPos( )+m_sh.GetPos( ))*my)+reStaticSize.top);
			m_SOS.MoveWindow(rrr);
		}
	}
}

void CDlgDialogEditor::OnChangeEdit2() {OnChangeEdit1(); }
void CDlgDialogEditor::OnChangeEdit5() {OnChangeEdit1(); }
void CDlgDialogEditor::OnChangeEdit6() {OnChangeEdit1(); }


void CDlgDialogEditor::OnButtondelte()
{
 	int id=m_LUnit.GetCurSel( );

	if (id!=LB_ERR && id!=0 && RefGPU[id]!=NULL)
	{
		if (RefGPU[id]->UnitHWND && RefGPU[id]->m_WindowLessFlag==0)
		{
			if (::IsWindow(RefGPU[id]->UnitHWND))
			{
				::SetWindowLong(RefGPU[id]->UnitHWND,GWL_STYLE,::GetWindowLong(RefGPU[id]->UnitHWND,GWL_STYLE)|WS_DISABLED);
				::DestroyWindow(RefGPU[id]->UnitHWND);
			}

			if (GPOd)	GPOd->DeleteUnit(id, FALSE);
			else
			if (GPOf)	GPOf->DeleteUnit(id, FALSE);
			else
			if (GPOw)	GPOw->DeleteUnit(id, FALSE);

			UINT tmpId;
			CString tmps;
			for(tmpId=1;tmpId<(*RefGPU)->m_NGPUNIT;tmpId++)
			{
				if (!RefGPU[tmpId])
				{
					m_LUnit.GetText(tmpId,tmps);
					if (tmps!= "NULL")
					{
						m_LUnit.DeleteString(tmpId);
						m_LUnit.InsertString(tmpId,"NULL");
					}
				}
			}

		}
		else if (RefGPU[id]->UnitHWND) ((CWnd *)RefGPU[id]->UnitPtr)->Detach();

		CurUnit=NULL;
		m_LUnit.DeleteString(id);
		m_LUnit.InsertString(id,"NULL");

		::SendMessage(RefGPU[0]->UnitHWND,WM_APP+1,0,0);
	}

}


void CDlgDialogEditor::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	UpdateTabs();
	*pResult = 0;
}

void CDlgDialogEditor::UpdateTabs()
{

	NoUpdateTxt=TRUE;

	m_btFRGDlg.ModifyStyle(WS_VISIBLE, 0);
	m_btBKGDlg.ModifyStyle(WS_VISIBLE, 0);
	m_btBrushDlg.ModifyStyle(WS_VISIBLE, 0);
	m_edFRG.ModifyStyle(WS_VISIBLE, 0);
	m_edBrush.ModifyStyle(WS_VISIBLE, 0);
	m_edBKG.ModifyStyle(WS_VISIBLE, 0);
	m_ChkWINDOWLESS.ModifyStyle(WS_VISIBLE, 0);
	m_cbBrushType.ModifyStyle(WS_VISIBLE, 0);
	m_cbBrushStyle.ModifyStyle(WS_VISIBLE, 0);
	m_btFRG.ModifyStyle(WS_VISIBLE, 0);
	m_btBRUSH.ModifyStyle(WS_VISIBLE, 0);
	m_btBKG.ModifyStyle(WS_VISIBLE, 0);
	m_btClearAllTextEv.ModifyStyle(WS_VISIBLE, 0);
	m_BtClAllEvents.ModifyStyle(WS_VISIBLE, 0);
	m_EditEventsOutput.ModifyStyle(WS_VISIBLE, 0);
	m_ListEvents.ModifyStyle(WS_VISIBLE, 0);
	m_ComboMethods.ModifyStyle(WS_VISIBLE, 0);
	m_BtExecute.ModifyStyle(WS_VISIBLE, 0);
	m_EditResult.ModifyStyle(WS_VISIBLE, 0);
	m_EditParamsHelp.ModifyStyle(WS_VISIBLE, 0);
	m_EditParams.ModifyStyle(WS_VISIBLE, 0);
	m_btdelete.ModifyStyle(WS_VISIBLE, 0);
	m_ed6.ModifyStyle(WS_VISIBLE, 0);
	m_ed5.ModifyStyle(WS_VISIBLE, 0);
	m_ed2.ModifyStyle(WS_VISIBLE, 0);
	m_ed1.ModifyStyle(WS_VISIBLE, 0);
	m_ListUnitStl.ModifyStyle(WS_VISIBLE, 0);
	m_WSList.ModifyStyle(WS_VISIBLE, 0);
	m_sw.ModifyStyle(WS_VISIBLE, 0);
	m_sh.ModifyStyle(WS_VISIBLE, 0);
	m_st.ModifyStyle(WS_VISIBLE, 0);
	m_sl.ModifyStyle(WS_VISIBLE, 0);
	m_LUnit.ModifyStyle(WS_VISIBLE, 0);
	m_Stat1.ModifyStyle(WS_VISIBLE, 0);
	m_Stat2.ModifyStyle(WS_VISIBLE, 0);
	m_Stat3.ModifyStyle(WS_VISIBLE, 0);
	m_Stat4.ModifyStyle(WS_VISIBLE, 0);
	m_StaticSize.ModifyStyle(WS_VISIBLE, 0);
	m_SOS.ModifyStyle(WS_VISIBLE, 0);
	m_StaticSizing.ModifyStyle(WS_VISIBLE, 0);
	m_EditSizing.ModifyStyle(WS_VISIBLE, 0);
	m_ComboSizing.ModifyStyle(WS_VISIBLE, 0);
	m_EditText.ModifyStyle(WS_VISIBLE, 0);
	m_StaticText.ModifyStyle(WS_VISIBLE, 0);
	m_BtCreatToClip.ModifyStyle(WS_VISIBLE, 0);
	m_StaticToolTip.ModifyStyle(WS_VISIBLE, 0);
	m_EditToolTip.ModifyStyle(WS_VISIBLE, 0);
	m_ListUnitType.ModifyStyle(WS_VISIBLE, 0);
	m_StaticOwner.ModifyStyle(WS_VISIBLE, 0);
	m_StaticGroup.ModifyStyle(WS_VISIBLE, 0);
	m_ComboOwner.ModifyStyle(WS_VISIBLE, 0);
	m_EditGroup.ModifyStyle(WS_VISIBLE, 0);
	m_EditWS.ModifyStyle(WS_VISIBLE, 0);
	m_EditWSE.ModifyStyle(WS_VISIBLE, 0);
	m_EditOS.ModifyStyle(WS_VISIBLE, 0);
	m_EditOSE.ModifyStyle(WS_VISIBLE, 0);
	m_StaticProperty.ModifyStyle(WS_VISIBLE, 0);
	m_EditProperty.ModifyStyle(WS_VISIBLE, 0);
	m_BtDoProperty.ModifyStyle(WS_VISIBLE, 0);
	m_BtMessToClip.ModifyStyle(WS_VISIBLE, 0);

	m_btdelete.EnableWindow(FALSE);

 	int id=m_LUnit.GetCurSel( );

	CurUnit=NULL;

	if (id!=LB_ERR && RefGPU!=NULL) CurUnit=RefGPU[id];

	switch(m_Tabs.GetCurSel())
	{
	case 0:
		if (CurUnit!=NULL)
		{
			if (id>0)
			{
				m_ChkWINDOWLESS.ModifyStyle(0,WS_VISIBLE);
				m_StaticOwner.ModifyStyle(0,WS_VISIBLE);
				m_StaticGroup.ModifyStyle(0,WS_VISIBLE);
				m_ComboOwner.ModifyStyle(0,WS_VISIBLE);
				m_EditGroup.ModifyStyle(0,WS_VISIBLE);
				m_btdelete.EnableWindow(TRUE);

				m_ComboOwner.ResetContent();
				int cstr;
				int i;
				for(i=0;(UINT)i<(*RefGPU)->m_NGPUNIT;i++)
				{
					char *pos="NULL";
					char str[2000];
					if (RefGPU[i]!=NULL && i!=id)
					{
						RefGPU[i]->DoWindowMethod("GetWindowTextEx",str+100);
						sprintf(str,"%s %d %s %s",GPUnit::aTypeUnit[RefGPU[i]->UnitType],i,(LPCSTR)RefGPU[i]->m_ObjName,str+100);
						pos=str;
						cstr=m_ComboOwner.AddString(pos);
						if ((UINT)i==CurUnit->ParentNum) m_ComboOwner.SetCurSel(cstr);
					}
				}
				cstr=m_ComboOwner.AddString("DeskTop; -1");
				if (CurUnit->ParentNum>(*RefGPU)->m_NGPUNIT) m_ComboOwner.SetCurSel(cstr);
				m_EditGroup.SetWindowText("");
				if (CurUnit->GroupNum!=NULL) m_EditGroup.SetWindowText(CurUnit->GroupNum);
			}
			m_BtCreatToClip.EnableWindow(TRUE);
		}

		m_btdelete.ModifyStyle(0,WS_VISIBLE);
		m_LUnit.ModifyStyle(0,WS_VISIBLE);
		m_BtCreatToClip.ModifyStyle(0,WS_VISIBLE);
		m_ChkWINDOWLESS.ModifyStyle(0,WS_VISIBLE);
		break;
	case 1:
		m_WSList.ModifyStyle(0,WS_VISIBLE);
		m_EditWS.ModifyStyle(0,WS_VISIBLE);
		m_EditWSE.ModifyStyle(0,WS_VISIBLE);
		m_EditOS.ModifyStyle(0,WS_VISIBLE);
		m_EditOSE.ModifyStyle(0,WS_VISIBLE);
		break;
	case 2:
		m_ListUnitStl.ModifyStyle(0,WS_VISIBLE);
		m_EditWS.ModifyStyle(0,WS_VISIBLE);
		m_EditWSE.ModifyStyle(0,WS_VISIBLE);
		m_EditOS.ModifyStyle(0,WS_VISIBLE);
		m_EditOSE.ModifyStyle(0,WS_VISIBLE);
		break;
	case 3:
		m_StaticProperty.ModifyStyle(0,WS_VISIBLE);
		m_EditProperty.ModifyStyle(0,WS_VISIBLE);
		m_BtDoProperty.ModifyStyle(0,WS_VISIBLE);
		m_EditText.ModifyStyle(0,WS_VISIBLE);
		m_StaticText.ModifyStyle(0,WS_VISIBLE);
		m_StaticToolTip.ModifyStyle(0,WS_VISIBLE);
		m_EditToolTip.ModifyStyle(0,WS_VISIBLE);

		m_edFRG.ModifyStyle(0,WS_VISIBLE);
		m_edBrush.ModifyStyle(0,WS_VISIBLE);
		m_edBKG.ModifyStyle(0,WS_VISIBLE);
		m_cbBrushType.ModifyStyle(0,WS_VISIBLE);
		m_cbBrushStyle.ModifyStyle(0,WS_VISIBLE);
		m_btFRG.ModifyStyle(0,WS_VISIBLE);
		m_btBRUSH.ModifyStyle(0,WS_VISIBLE);
		m_btBKG.ModifyStyle(0,WS_VISIBLE);
		m_btFRGDlg.ModifyStyle(0,WS_VISIBLE);
		m_btBKGDlg.ModifyStyle(0,WS_VISIBLE);
		m_btBrushDlg.ModifyStyle(0,WS_VISIBLE);

		if (CurUnit!=NULL)
		{
			char *str=new char [CurUnit->UnitHWND?::GetWindowTextLength(CurUnit->UnitHWND)+1000:1000];
			*str=0;
			CurUnit->DoWindowMethod("GetWindowText",str);
			m_EditText.SetWindowText(str);
			if (*CurUnit->m_ToolTip!=NULL && (*CurUnit->m_ToolTip)->m_hWnd!=NULL)
			{
				char *tstr="";
				if (CurUnit->ToolTipText!=NULL) tstr=CurUnit->ToolTipText;
				m_EditToolTip.SetWindowText(tstr);
			}
			delete[] str;
		}

		break;
	case 4:
		m_ComboSizing.ResetContent();
		m_EditSizing.LimitText(8);

		if (CurUnit!=NULL)
		{
			int cso=CurUnit->GetResizeingOwner();
			int i;
			for(i=0;(UINT)i<(*RefGPU)->m_NGPUNIT;i++)
			{
				char *pos="NULL";
				char str[2000];
				if (RefGPU[i]!=NULL)
				{
					RefGPU[i]->DoWindowMethod("GetWindowTextEx",str+100);
					sprintf(str,"%s %d %s",GPUnit::aTypeUnit[RefGPU[i]->UnitType],i,str+100);
					pos=str;
					int cstr=m_ComboSizing.AddString(pos);
					if (i==cso)
						m_ComboSizing.SetCurSel(cstr);
				}
			}
			m_EditSizing.SetWindowText(CurUnit->GetSizingStyle());
		}
		m_ed6.ModifyStyle(0,WS_VISIBLE);
		m_ed5.ModifyStyle(0,WS_VISIBLE);
		m_ed2.ModifyStyle(0,WS_VISIBLE);
		m_ed1.ModifyStyle(0,WS_VISIBLE);
		m_sw.ModifyStyle(0,WS_VISIBLE);
		m_sh.ModifyStyle(0,WS_VISIBLE);
		m_st.ModifyStyle(0,WS_VISIBLE);
		m_sl.ModifyStyle(0,WS_VISIBLE);
		m_Stat1.ModifyStyle(0,WS_VISIBLE);
		m_Stat2.ModifyStyle(0,WS_VISIBLE);
		m_Stat3.ModifyStyle(0,WS_VISIBLE);
		m_Stat4.ModifyStyle(0,WS_VISIBLE);
		m_StaticSize.ModifyStyle(0,WS_VISIBLE);
		m_SOS.ModifyStyle(0,WS_VISIBLE);
		m_StaticSizing.ModifyStyle(0,WS_VISIBLE);
		m_EditSizing.ModifyStyle(0,WS_VISIBLE);
		m_ComboSizing.ModifyStyle(0,WS_VISIBLE);
		break;
	case 5:
		m_ComboMethods.ModifyStyle(0,WS_VISIBLE);
		m_BtExecute.ModifyStyle(0,WS_VISIBLE);
		m_EditResult.ModifyStyle(0,WS_VISIBLE);
		m_EditParamsHelp.ModifyStyle(0,WS_VISIBLE);
		m_EditParams.ModifyStyle(0,WS_VISIBLE);
		break;
	case 6:
		m_btClearAllTextEv.ModifyStyle(0,WS_VISIBLE);
		m_BtClAllEvents.ModifyStyle(0,WS_VISIBLE);
		m_EditEventsOutput.ModifyStyle(0,WS_VISIBLE);
		m_ListEvents.ModifyStyle(0,WS_VISIBLE);
		m_BtMessToClip.ModifyStyle(0,WS_VISIBLE);
		break;
	}

	Invalidate();

	NoUpdateTxt=FALSE;

}

void CDlgDialogEditor::OnDblclkListusestl()
{
	int id=m_WSList.GetCurSel( );

	if (id!=LB_ERR && CurUnit!=NULL)
	{
		char str[350];
		m_WSList.GetText(id,str+100);
		int ch=m_WSList.GetCheck(id );

		sprintf(str,"%sSTYLE=%s|;",ch==0?"ADD":"DEL",str+100 );
		m_WSList.SetCheck(id,ch==0?TRUE:FALSE);

		if (strstr(str,"WS_CHILD")==NULL)
			CurUnit->GPSetProperty(str);

		UpdateChecks(0);
	}
}

void CDlgDialogEditor::OnDblclkListusestl2()
{
	int id=m_ListUnitStl.GetCurSel( );
	if (id!=LB_ERR && CurUnit!=NULL)
	{
		char str[350];
		m_ListUnitStl.GetText(id,str+100);
		int ch=m_ListUnitStl.GetCheck(id );
		sprintf(str,"%sSTYLE=%s|;",ch==0?"ADD":"DEL",str+100 );
		m_ListUnitStl.SetCheck(id,ch==0?TRUE:FALSE);

		if (NoUpdateTxt==FALSE)	CurUnit->GPSetProperty(str);
		UpdateChecks(0);
	}
}

void CDlgDialogEditor::UpdateChecks(int Type)
{
	if (CurUnit!=NULL && CurUnit->UnitHWND!=NULL)
	{
		UINT Stl=0,ExStl=0;
		uStlComO=uStlO=uStlOE=uStlW=uStlWE=0;
		Stl=	::GetWindowLong(CurUnit->UnitHWND,GWL_STYLE);
		ExStl=	::GetWindowLong(CurUnit->UnitHWND,GWL_EXSTYLE);

		uStlW=SetObjStlCheck(&m_WSList, Stl, N_WND_STYLES,  aWndStyleName, aWndStyleUINT, aWndStyleMask,Type);
		uStlWE=SetObjStlCheck(&m_WSList, ExStl, N_WND_EX_STYLES,  aWndExStyleName, aWndExStyleUINT, aWndExStyleMask,Type);

		switch(CurUnit->UnitType)
		{
		case GPUnit::UT_MAINDLGSCR: /*DIALOG*/
			uStlW|=SetObjStlCheck(&m_ListUnitStl, Stl,  N_DLG_STYLES,  aDlgStyleName, aDlgStyleUINT, aDlgStyleMask,Type);
			break;
		case GPUnit::UT_DRAW:
			break;
		case GPUnit::UT_DATETIMECTRL: /*GPDateTimeCtrl*/
			{
				uStlW|=SetObjStlCheck(&m_ListUnitStl, Stl, N_DATETIME_STYLES,  aDateTimeStyleName, aDateTimeStyleUINT, aDateTimeStyleMask,Type);

				Stl=((GPDateTimeCtrl*)CurUnit->UnitPtr)->MCStyle;
				uStlO=SetObjStlCheck(&m_ListUnitStl, Stl, N_MONTHCAL_STYLES,  aMonthCalStyleName, aMonthCalStyleUINT, aMonthCalStyleMask,Type);
			}
			break;
		case GPUnit::UT_MONTHCAL: /*GPMonthCal*/
			uStlW|=SetObjStlCheck(&m_ListUnitStl, Stl, N_MONTHCAL_STYLES,  aMonthCalStyleName, aMonthCalStyleUINT, aMonthCalStyleMask,Type);
			break;
		case GPUnit::UT_DLGBAR:
		case GPUnit::UT_FRAMEBAR:
			uStlW|=SetObjStlCheck(&m_ListUnitStl, Stl, N_DLG_STYLES,  aDlgStyleName, aDlgStyleUINT, aDlgStyleMask,Type);
			break;
		case GPUnit::UT_RTF:
			uStlW|=SetObjStlCheck(&m_ListUnitStl, Stl, N_RTF_STYLES,  aRTFStyleName, aRTFStyleUINT, aRTFStyleMask,Type);
			Stl=((GP_RTF*)CurUnit->UnitPtr)->GetExStyle( );
			uStlOE=SetObjStlCheck(&m_ListUnitStl, Stl, N_RTF_EX_STYLES,  aRTFExStyleName, aRTFExStyleUINT, aRTFExStyleMask,Type);
			uStlComO=SetObjStlCheck(&m_ListUnitStl, CurUnit->UnitCommonStyles, N_UNITCOMMON_STYLES , aUnitCommonStyleName , aUnitCommonStyleUINT, aUnitCommonStyleMask,Type);
			break;
		case GPUnit::UT_EDITOR:
			break;
		case GPUnit::UT_TREECTRL:
			uStlW|=SetObjStlCheck(&m_ListUnitStl, Stl, N_TREECTRL_STYLES,  aTreeCtrlStyleName, aTreeCtrlStyleUINT, aTreeCtrlStyleMask,Type);
			Stl=((GPTree*)CurUnit->UnitPtr)->GetExtendedStyle( );
			uStlOE=SetObjStlCheck(&m_ListUnitStl, Stl, N_TREECTRL_EX_STYLES,  aTreeCtrlExStyleName, aTreeCtrlExStyleUINT, aTreeCtrlExStyleMask,Type);
			break;
		case GPUnit::UT_HEADER:
			uStlW|=SetObjStlCheck(&m_ListUnitStl, Stl, N_HEADER_STYLES,  aHeaderStyleName, aHeaderStyleUINT, aHeaderStyleMask,Type);
			uStlO=SetObjStlCheck(&m_ListUnitStl, Stl, N_COMCTRL_STYLES,  aComCtrlStyleName, aComCtrlStyleUINT, aComCtrlStyleMask,Type);
			break;
		case GPUnit::UT_REBARCTRL:
			uStlW|=SetObjStlCheck(&m_ListUnitStl, Stl, N_REBARCTRL_STYLES,  aReBarCtrlStyleName, aReBarCtrlStyleUINT, aReBarCtrlStyleMask,Type);
			uStlO=SetObjStlCheck(&m_ListUnitStl, Stl, N_COMCTRL_STYLES,  aComCtrlStyleName, aComCtrlStyleUINT, aComCtrlStyleMask,Type);
			break;
		case GPUnit::UT_REBAR:
			uStlO|=SetObjStlCheck(&m_ListUnitStl, Stl, N_REBARCTRL_STYLES,  aReBarCtrlStyleName, aReBarCtrlStyleUINT, aReBarCtrlStyleMask,Type);
			Stl=((GPReBar*)CurUnit->UnitPtr)->GetBarStyle( );
			uStlOE=SetObjStlCheck(&m_ListUnitStl,Stl, N_CTRLBAR_STYLES,  aCtrlBarStyleName, aCtrlBarStyleUINT, aCtrlBarStyleMask,Type);
			break;
		case GPUnit::UT_STATUSBARCTRL:
			uStlW|=SetObjStlCheck(&m_ListUnitStl, Stl, N_STATUSBARCTRL_STYLES,  aStatusBarCtrlStyleName, aStatusBarCtrlStyleUINT, aStatusBarCtrlStyleMask,Type);
			uStlO=SetObjStlCheck(&m_ListUnitStl, Stl, N_COMCTRL_STYLES,  aComCtrlStyleName, aComCtrlStyleUINT, aComCtrlStyleMask,Type);
			break;
		case GPUnit::UT_STATUSBAR:
			uStlO|=SetObjStlCheck(&m_ListUnitStl, Stl, N_STATUSBAR_STYLES,  aStatusBarStyleName, aStatusBarStyleUINT, aStatusBarStyleMask,Type);
			Stl=((GPStatusBar*)CurUnit->UnitPtr)->GetBarStyle( );
			uStlOE=SetObjStlCheck(&m_ListUnitStl,Stl, N_CTRLBAR_STYLES,  aCtrlBarStyleName, aCtrlBarStyleUINT, aCtrlBarStyleMask,Type);
			break;
		case GPUnit::UT_DIALOGBAR:
			Stl=((GPDialogBar*)CurUnit->UnitPtr)->GetBarStyle( );
			uStlOE=SetObjStlCheck(&m_ListUnitStl,Stl, N_CTRLBAR_STYLES,  aCtrlBarStyleName, aCtrlBarStyleUINT, aCtrlBarStyleMask,Type);
			break;
		case GPUnit::UT_TOOLBARCTRL:
			uStlO=SetObjStlCheck(&m_ListUnitStl, Stl|((GPToolBarCtrl*)CurUnit->UnitPtr)->GetStyle( ), N_TOOLBARCTRL_STYLES, aToolBarCtrlStyleName, aToolBarCtrlStyleUINT, aToolBarCtrlStyleMask,Type);
			uStlW|=SetObjStlCheck(&m_ListUnitStl, Stl, N_COMCTRL_STYLES,  aComCtrlStyleName, aComCtrlStyleUINT, aComCtrlStyleMask,Type);
			Stl=((GPToolBarCtrl*)CurUnit->UnitPtr)->GetExtendedStyle( );
			uStlOE=SetObjStlCheck(&m_ListUnitStl, Stl, N_TOOLBARCTRL_EX_STYLES,  aToolBarCtrlExStyleName, aToolBarCtrlExStyleUINT, aToolBarCtrlExStyleMask,Type);
			break;
		case GPUnit::UT_TOOLBAR:
			uStlO=SetObjStlCheck(&m_ListUnitStl,((GPToolBar*)CurUnit->UnitPtr)->GetToolBarCtrl().GetStyle( ), N_TOOLBARCTRL_STYLES, aToolBarCtrlStyleName, aToolBarCtrlStyleUINT, aToolBarCtrlStyleMask,Type);
			Stl=((GPToolBar*)CurUnit->UnitPtr)->GetToolBarCtrl().GetExtendedStyle( );
			uStlOE=SetObjStlCheck(&m_ListUnitStl, Stl, N_TOOLBARCTRL_EX_STYLES,  aToolBarCtrlExStyleName, aToolBarCtrlExStyleUINT, aToolBarCtrlExStyleMask,Type);
			Stl=((GPToolBar*)CurUnit->UnitPtr)->GetBarStyle( );
			uStlOE=SetObjStlCheck(&m_ListUnitStl,Stl, N_CTRLBAR_STYLES,  aCtrlBarStyleName, aCtrlBarStyleUINT, aCtrlBarStyleMask,Type);
			break;
		case GPUnit::UT_SLIDER:
			uStlO=SetObjStlCheck(&m_ListUnitStl, Stl, N_SLIDER_STYLES,  aSliderStyleName, aSliderStyleUINT, aSliderStyleMask,Type);
			break;
		case GPUnit::UT_TABCTRL:
			uStlW|=SetObjStlCheck(&m_ListUnitStl, Stl, N_TAB_STYLES,  aTabStyleName, aTabStyleUINT, aTabStyleMask,Type);
			Stl=((GPTabCtrl*)CurUnit->UnitPtr)->GetExtendedStyle( );
			uStlOE=SetObjStlCheck(&m_ListUnitStl, Stl, N_TAB_EX_STYLES,  aTabExStyleName, aTabExStyleUINT, aTabExStyleMask,Type);
			break;
		case GPUnit::UT_SPINBUTTON:
			uStlW|=SetObjStlCheck(&m_ListUnitStl, Stl, N_SPIN_STYLES,  aSpinStyleName, aSpinStyleUINT, aSpinStyleMask,Type);
			break;
		case GPUnit::UT_BBUTTON:
			uStlO=SetObjStlCheck(&m_ListUnitStl, Stl|((GPBButton*)CurUnit->UnitPtr)->GetButtonStyle( ), N_BUTTON_STYLES, aButtonStyleName, aButtonStyleUINT, aButtonStyleMask,Type);
			break;
		case GPUnit::UT_BUTTON:
			uStlO=SetObjStlCheck(&m_ListUnitStl, Stl|((GPButton*)CurUnit->UnitPtr)->GetButtonStyle( ), N_BUTTON_STYLES, aButtonStyleName, aButtonStyleUINT, aButtonStyleMask,Type);
			break;
		case GPUnit::UT_ANIBUTTON:
			uStlO=SetObjStlCheck(&m_ListUnitStl, Stl|((GPAniButton*)CurUnit->UnitPtr)->GetButtonStyle( ), N_BUTTON_STYLES, aButtonStyleName, aButtonStyleUINT, aButtonStyleMask,Type);
			break;
		case GPUnit::UT_STATIC:
			uStlW|=SetObjStlCheck(&m_ListUnitStl, Stl, N_STATIC_STYLES,  aStaticStyleName, aStaticStyleUINT, aStaticStyleMask,Type);
			break;
		case GPUnit::UT_ANISTATIC:
			uStlW|=SetObjStlCheck(&m_ListUnitStl, Stl, N_STATIC_STYLES,  aStaticStyleName, aStaticStyleUINT, aStaticStyleMask,Type);
			break;
		case GPUnit::UT_EDIT:
			uStlW|=SetObjStlCheck(&m_ListUnitStl, Stl, N_EDIT_STYLES,  aEditStyleName, aEditStyleUINT, aEditStyleMask,Type);
			uStlComO=SetObjStlCheck(&m_ListUnitStl, CurUnit->UnitCommonStyles, N_UNITCOMMON_STYLES , aUnitCommonStyleName , aUnitCommonStyleUINT, aUnitCommonStyleMask,Type);
			break;
		case GPUnit::UT_COMBOBOX:
			uStlW|=SetObjStlCheck(&m_ListUnitStl, Stl, N_COMBOBOX_STYLES,  aComboBoxStyleName, aComboBoxStyleUINT, aComboBoxStyleMask,Type);
			break;
		case GPUnit::UT_COMBOBOXEX:
			uStlW|=SetObjStlCheck(&m_ListUnitStl, Stl, N_COMBOBOXEX_STYLES,  aComboBoxExStyleName, aComboBoxExStyleUINT, aComboBoxExStyleMask,Type);
			Stl=((GPComboBoxEx*)CurUnit->UnitPtr)->GetExtendedStyle( );
			uStlOE=SetObjStlCheck(&m_ListUnitStl, Stl, N_COMBOBOXEX_EX_STYLES,  aComboBoxExExStyleName, aComboBoxExExStyleUINT, aComboBoxExExStyleMask,Type);
			break;
		case GPUnit::UT_SCROLLBAR:
			uStlW|=SetObjStlCheck(&m_ListUnitStl, Stl, N_SCROLL_STYLES,  aScrollStyleName, aScrollStyleUINT, aScrollStyleMask,Type);
			break;
		case GPUnit::UT_PROGRESS:
			uStlW|=SetObjStlCheck(&m_ListUnitStl, Stl, N_PROGRESS_STYLES,  aProgressStyleName, aProgressStyleUINT, aProgressStyleMask,Type);
			break;
		case GPUnit::UT_ANIMAT:
			uStlW|=SetObjStlCheck(&m_ListUnitStl, Stl, N_ANIMATION_STYLES,  aAnimationStyleName, aAnimationStyleUINT, aAnimationStyleMask,Type);
			break;
		case GPUnit::UT_LISTBOX:
		case GPUnit::UT_CHECKLISTBOX:
		case GPUnit::UT_DRAGLISTBOX:
			uStlW|=SetObjStlCheck(&m_ListUnitStl, Stl, N_LISTBOX_STYLES,  aListBoxStyleName, aListBoxStyleUINT, aListBoxStyleMask,Type);
			break;
		case GPUnit::UT_LISTCTRL:
			uStlW|=SetObjStlCheck(&m_ListUnitStl, Stl, N_LISTCTRL_STYLES,  aListCtrlStyleName, aListCtrlStyleUINT, aListCtrlStyleMask,Type);
			Stl=((GPListCtr*)CurUnit->UnitPtr)->GetExtendedStyle( );
			uStlOE=SetObjStlCheck(&m_ListUnitStl, Stl, N_LISTCTRL_EX_STYLES,  aListCtrlExStyleName, aListCtrlExStyleUINT, aListCtrlExStyleMask,Type);
			break;
		case GPUnit::UT_FLEXGRID:
			break;
		case GPUnit::UT_WEBBROWSER:
			break;
		default:
			break;
		}
	}

	char strtmp[100];
	sprintf(strtmp,"&W%X",uStlW);
	m_EditWS.SetWindowText(strtmp);
	sprintf(strtmp,"&E%X",uStlWE);
	m_EditWSE.SetWindowText(strtmp);
	sprintf(strtmp,"&U%X",uStlO);
	m_EditOS.SetWindowText(strtmp);
	sprintf(strtmp,"&X%X",uStlOE);
	m_EditOSE.SetWindowText(strtmp);

}

void CDlgDialogEditor::GetObjStyleStr(UINT id, char *StrStl)
{

	if (id!=LB_ERR && RefGPU[id]!=NULL)
	{
		if (RefGPU[id]->UnitHWND!=NULL)
		{
			UINT Stl=0,ExStl=0;
			uStlComO=uStlO=uStlOE=uStlW=uStlWE=0;
			Stl=	CWnd::FromHandle(RefGPU[id]->UnitHWND)->GetStyle();
			ExStl=	CWnd::FromHandle(RefGPU[id]->UnitHWND)->GetExStyle();
			*StrStl=0;

			uStlW=	GetObjStlStr(StrStl, Stl, N_WND_STYLES,  aWndStyleName, aWndStyleUINT, aWndStyleMask);

			char *posStrStl=StrStl+(int)strlen(StrStl);
			uStlWE=	GetObjStlStr(posStrStl, ExStl, N_WND_EX_STYLES,  aWndExStyleName, aWndExStyleUINT, aWndExStyleMask);

			posStrStl+=(int)strlen(posStrStl);

			switch(RefGPU[id]->UnitType)
			{
			case GPUnit::UT_MAINDLGSCR:
					uStlW|=GetObjStlStr(posStrStl, Stl, N_DLG_STYLES,  aDlgStyleName, aDlgStyleUINT, aDlgStyleMask);
				break;
			case GPUnit::UT_DATETIMECTRL:
				{
					uStlW|=GetObjStlStr(posStrStl, Stl, N_DATETIME_STYLES,  aDateTimeStyleName, aDateTimeStyleUINT, aDateTimeStyleMask);
					Stl=((GPDateTimeCtrl*)CurUnit->UnitPtr)->MCStyle;
					posStrStl+=(int)strlen(posStrStl);
					uStlO=GetObjStlStr(posStrStl, Stl, N_MONTHCAL_STYLES,  aMonthCalStyleName, aMonthCalStyleUINT, aMonthCalStyleMask);
				}
				break;
			case GPUnit::UT_MONTHCAL:
				uStlW|=GetObjStlStr(posStrStl, Stl, N_MONTHCAL_STYLES,  aMonthCalStyleName, aMonthCalStyleUINT, aMonthCalStyleMask);
				break;
			case GPUnit::UT_DRAW:
				break;
			case GPUnit::UT_DLGBAR:
			case GPUnit::UT_FRAMEBAR:
					uStlW|=GetObjStlStr(posStrStl, Stl, N_DLG_STYLES,  aDlgStyleName, aDlgStyleUINT, aDlgStyleMask);
				break;
			case GPUnit::UT_RTF:
				uStlW|=GetObjStlStr(posStrStl, Stl, N_RTF_STYLES,  aRTFStyleName, aRTFStyleUINT, aRTFStyleMask);
				Stl=((GP_RTF*)RefGPU[id]->UnitPtr)->GetExStyle( );
				posStrStl+=(int)strlen(posStrStl);
				uStlOE=GetObjStlStr(posStrStl, Stl, N_RTF_EX_STYLES,  aRTFExStyleName, aRTFExStyleUINT, aRTFExStyleMask);
				posStrStl+=(int)strlen(posStrStl);
				uStlComO=GetObjStlStr(posStrStl, CurUnit->UnitCommonStyles, N_UNITCOMMON_STYLES,  aUnitCommonStyleName, aUnitCommonStyleUINT, aUnitCommonStyleMask);
				break;
			case GPUnit::UT_EDITOR:
				break;
			case GPUnit::UT_TREECTRL:
				uStlW|=GetObjStlStr(posStrStl, Stl, N_TREECTRL_STYLES,  aTreeCtrlStyleName, aTreeCtrlStyleUINT, aTreeCtrlStyleMask);
				Stl=((GPTree*)RefGPU[id]->UnitPtr)->GetExtendedStyle( );
				posStrStl+=(int)strlen(posStrStl);
				uStlOE=GetObjStlStr(posStrStl, Stl, N_TREECTRL_EX_STYLES,  aTreeCtrlExStyleName, aTreeCtrlExStyleUINT, aTreeCtrlExStyleMask);
				break;
			case GPUnit::UT_HEADER:
				uStlW|=GetObjStlStr(posStrStl, Stl, N_HEADER_STYLES,  aHeaderStyleName, aHeaderStyleUINT, aHeaderStyleMask);
				posStrStl+=(int)strlen(posStrStl);
				uStlW|=GetObjStlStr(posStrStl, Stl, N_COMCTRL_STYLES,  aComCtrlStyleName, aComCtrlStyleUINT, aComCtrlStyleMask);
				break;
			case GPUnit::UT_REBARCTRL:
				uStlW|=GetObjStlStr(posStrStl, Stl, N_REBARCTRL_STYLES,  aReBarCtrlStyleName, aReBarCtrlStyleUINT, aReBarCtrlStyleMask);
				posStrStl+=(int)strlen(posStrStl);
				uStlW|=GetObjStlStr(posStrStl, Stl, N_COMCTRL_STYLES,  aComCtrlStyleName, aComCtrlStyleUINT, aComCtrlStyleMask);
				break;
			case GPUnit::UT_REBAR:
				uStlW|=GetObjStlStr(posStrStl, Stl, N_REBARCTRL_STYLES,  aReBarCtrlStyleName, aReBarCtrlStyleUINT, aReBarCtrlStyleMask);
				posStrStl+=(int)strlen(posStrStl);
				Stl=((GPReBar*)CurUnit->UnitPtr)->GetBarStyle( );
				uStlOE=GetObjStlStr(posStrStl,Stl, N_CTRLBAR_STYLES,  aCtrlBarStyleName, aCtrlBarStyleUINT, aCtrlBarStyleMask);
				break;
			case GPUnit::UT_STATUSBARCTRL:
				uStlW|=GetObjStlStr(posStrStl, Stl, N_STATUSBARCTRL_STYLES,  aStatusBarCtrlStyleName, aStatusBarCtrlStyleUINT, aStatusBarCtrlStyleMask);
				posStrStl+=(int)strlen(posStrStl);
				uStlW|=GetObjStlStr(posStrStl, Stl, N_COMCTRL_STYLES,  aComCtrlStyleName, aComCtrlStyleUINT, aComCtrlStyleMask);
				break;
			case GPUnit::UT_STATUSBAR:
				uStlW|=GetObjStlStr(posStrStl, Stl, N_STATUSBAR_STYLES,  aStatusBarStyleName, aStatusBarStyleUINT, aStatusBarStyleMask);
				posStrStl+=(int)strlen(posStrStl);
				Stl=((GPStatusBar*)CurUnit->UnitPtr)->GetBarStyle( );
				uStlOE=GetObjStlStr(posStrStl,Stl, N_CTRLBAR_STYLES,  aCtrlBarStyleName, aCtrlBarStyleUINT, aCtrlBarStyleMask);
				break;
			case GPUnit::UT_DIALOGBAR:
				posStrStl+=(int)strlen(posStrStl);
				Stl=((GPDialogBar*)CurUnit->UnitPtr)->GetBarStyle( );
				uStlOE=GetObjStlStr(posStrStl,Stl, N_CTRLBAR_STYLES,  aCtrlBarStyleName, aCtrlBarStyleUINT, aCtrlBarStyleMask);
				break;
			case GPUnit::UT_TOOLBARCTRL:
				uStlO=GetObjStlStr(posStrStl, Stl|((GPToolBarCtrl*)RefGPU[id]->UnitPtr)->GetStyle(), N_TOOLBARCTRL_STYLES, aToolBarCtrlStyleName, aToolBarCtrlStyleUINT, aToolBarCtrlStyleMask);
				posStrStl+=(int)strlen(posStrStl);
				uStlW|=GetObjStlStr(posStrStl, Stl, N_COMCTRL_STYLES,  aComCtrlStyleName, aComCtrlStyleUINT, aComCtrlStyleMask);
				Stl=((GPToolBarCtrl*)RefGPU[id]->UnitPtr)->GetExtendedStyle( );
				posStrStl+=(int)strlen(posStrStl);
				uStlOE=GetObjStlStr(posStrStl, Stl, N_TOOLBARCTRL_EX_STYLES,  aToolBarCtrlExStyleName, aToolBarCtrlExStyleUINT, aToolBarCtrlExStyleMask);
				break;
			case GPUnit::UT_TOOLBAR:
				uStlO=GetObjStlStr(posStrStl,((GPToolBar*)RefGPU[id]->UnitPtr)->GetToolBarCtrl().GetStyle(), N_TOOLBARCTRL_STYLES, aToolBarCtrlStyleName, aToolBarCtrlStyleUINT, aToolBarCtrlStyleMask);
				posStrStl+=(int)strlen(posStrStl);
				Stl=((GPToolBar*)RefGPU[id]->UnitPtr)->GetToolBarCtrl().GetExtendedStyle( );
				uStlOE=GetObjStlStr(posStrStl, Stl, N_TOOLBARCTRL_EX_STYLES,  aToolBarCtrlExStyleName, aToolBarCtrlExStyleUINT, aToolBarCtrlExStyleMask);
				posStrStl+=(int)strlen(posStrStl);
				Stl=((GPToolBar*)CurUnit->UnitPtr)->GetBarStyle( );
				uStlOE=GetObjStlStr(posStrStl,Stl, N_CTRLBAR_STYLES,  aCtrlBarStyleName, aCtrlBarStyleUINT, aCtrlBarStyleMask);
				break;
			case GPUnit::UT_SLIDER:
				uStlO=GetObjStlStr(posStrStl, Stl, N_SLIDER_STYLES,  aSliderStyleName, aSliderStyleUINT, aSliderStyleMask);
				break;
			case GPUnit::UT_TABCTRL:
				uStlW|=GetObjStlStr(posStrStl, Stl, N_TAB_STYLES,  aTabStyleName, aTabStyleUINT, aTabStyleMask);
				Stl=((GPTabCtrl*)RefGPU[id]->UnitPtr)->GetExtendedStyle( );
				posStrStl+=(int)strlen(posStrStl);
				uStlO=GetObjStlStr(posStrStl, Stl, N_TAB_EX_STYLES,  aTabExStyleName, aTabExStyleUINT, aTabExStyleMask);
				break;
			case GPUnit::UT_SPINBUTTON:
				uStlW|=GetObjStlStr(posStrStl, Stl, N_SPIN_STYLES,  aSpinStyleName, aSpinStyleUINT, aSpinStyleMask);
				break;
			case GPUnit::UT_BBUTTON:
				uStlO=GetObjStlStr(posStrStl, Stl|((GPBButton*)RefGPU[id]->UnitPtr)->GetButtonStyle( ), N_BUTTON_STYLES, aButtonStyleName, aButtonStyleUINT, aButtonStyleMask);
				break;
			case GPUnit::UT_BUTTON:
				uStlO=GetObjStlStr(posStrStl, Stl|((GPButton*)RefGPU[id]->UnitPtr)->GetButtonStyle( ), N_BUTTON_STYLES, aButtonStyleName, aButtonStyleUINT, aButtonStyleMask);
				break;
			case GPUnit::UT_ANIBUTTON:
				uStlO=GetObjStlStr(posStrStl, Stl|((GPAniButton*)RefGPU[id]->UnitPtr)->GetButtonStyle( ), N_BUTTON_STYLES, aButtonStyleName, aButtonStyleUINT, aButtonStyleMask);
				break;
			case GPUnit::UT_STATIC:
				uStlW|=GetObjStlStr(posStrStl, Stl, N_STATIC_STYLES,  aStaticStyleName, aStaticStyleUINT, aStaticStyleMask);
				break;
			case GPUnit::UT_ANISTATIC:
				uStlW|=GetObjStlStr(posStrStl, Stl, N_STATIC_STYLES,  aStaticStyleName, aStaticStyleUINT, aStaticStyleMask);
				break;
			case GPUnit::UT_EDIT:
				uStlW|=GetObjStlStr(posStrStl, Stl, N_EDIT_STYLES,  aEditStyleName, aEditStyleUINT, aEditStyleMask);
				posStrStl+=(int)strlen(posStrStl);
				uStlComO=GetObjStlStr(posStrStl, CurUnit->UnitCommonStyles, N_UNITCOMMON_STYLES,  aUnitCommonStyleName, aUnitCommonStyleUINT, aUnitCommonStyleMask);
				break;
			case GPUnit::UT_COMBOBOX:
				uStlW|=GetObjStlStr(posStrStl, Stl, N_COMBOBOX_STYLES,  aComboBoxStyleName, aComboBoxStyleUINT, aComboBoxStyleMask);
				break;
			case GPUnit::UT_COMBOBOXEX:
				uStlW|=GetObjStlStr(posStrStl, Stl, N_COMBOBOXEX_STYLES,  aComboBoxExStyleName, aComboBoxExStyleUINT, aComboBoxExStyleMask);
				Stl=((GPComboBoxEx*)RefGPU[id]->UnitPtr)->GetExtendedStyle( );
				posStrStl+=(int)strlen(posStrStl);
				uStlOE=GetObjStlStr(posStrStl, Stl, N_COMBOBOXEX_EX_STYLES,aComboBoxExExStyleName, aComboBoxExExStyleUINT, aComboBoxExExStyleMask);
				break;
			case GPUnit::UT_SCROLLBAR:
				uStlW|=GetObjStlStr(posStrStl, Stl, N_SCROLL_STYLES,  aScrollStyleName, aScrollStyleUINT, aScrollStyleMask);
				break;
			case GPUnit::UT_PROGRESS:
				uStlW|=GetObjStlStr(posStrStl, Stl, N_PROGRESS_STYLES,  aProgressStyleName, aProgressStyleUINT, aProgressStyleMask);
				break;
			case GPUnit::UT_ANIMAT:
				uStlW|=GetObjStlStr(posStrStl, Stl, N_ANIMATION_STYLES,  aAnimationStyleName, aAnimationStyleUINT, aAnimationStyleMask);
				break;
			case GPUnit::UT_LISTBOX:
			case GPUnit::UT_CHECKLISTBOX:
			case GPUnit::UT_DRAGLISTBOX:
				uStlW|=GetObjStlStr(posStrStl, Stl, N_LISTBOX_STYLES,  aListBoxStyleName, aListBoxStyleUINT, aListBoxStyleMask);
				break;
			case GPUnit::UT_LISTCTRL:
				uStlW|=GetObjStlStr(posStrStl, Stl, N_LISTCTRL_STYLES,  aListCtrlStyleName, aListCtrlStyleUINT, aListCtrlStyleMask);
				Stl=((GPListCtr*)RefGPU[id]->UnitPtr)->GetExtendedStyle( );
				posStrStl+=(int)strlen(posStrStl);
				uStlOE=GetObjStlStr(posStrStl, Stl, N_LISTCTRL_EX_STYLES,  aListCtrlExStyleName, aListCtrlExStyleUINT, aListCtrlExStyleMask);
				break;
			case GPUnit::UT_FLEXGRID:
				break;
			case GPUnit::UT_WEBBROWSER:
				break;
			default:
				break;
			}
		}
		else if (RefGPU[id]->m_WindowLessFlag) strcpy(StrStl,"WS_WINDOWLESS");
	}
	char strtmp[100];
	sprintf(strtmp,"&W%X",uStlW);
	m_EditWS.SetWindowText(strtmp);
	sprintf(strtmp,"&E%X",uStlWE);
	m_EditWSE.SetWindowText(strtmp);
	sprintf(strtmp,"&U%X",uStlO);
	m_EditOS.SetWindowText(strtmp);
	sprintf(strtmp,"&X%X",uStlOE);
	m_EditOSE.SetWindowText(strtmp);

}

void CDlgDialogEditor::FillObjList(UINT Type)
{
	if (m_LUnit.m_hWnd!=NULL)
	{
		int possel=m_LUnit.GetCurSel( );
		char str[10000];

		UINT nMaxUnit=(*RefGPU)->m_NGPUNIT;
		if (GPOd)	nMaxUnit=GPOd->m_NGPUNITmax;
		else
		if (GPOf)	nMaxUnit=GPOf->m_NGPUNITmax;
		else
		if (GPOw)	nMaxUnit=GPOw->m_NGPUNITmax;

		int i;
		for(i=0;(UINT)i<nMaxUnit;i++)
		{
			char *pos="NULL";
			if (RefGPU && RefGPU[i])
			{
				int mStrLen=m_LUnit.GetText(i,str);
				if (mStrLen>5000 || mStrLen<0) mStrLen=0;
				str[mStrLen]=0;
				if (strcmp(str,"NULL")==0 || (i==0 && !GPOw))
				{
					RefGPU[i]->DoWindowMethod("SizerAdd C,WS_VISIBLE|GPSS_CENTER|GPSS_INVERT|WS_CLIPSIBLINGS|,6,8,2000",NULL);
					RefGPU[i]->DoWindowMethod("SizerAdd L,WS_VISIBLE|GPSS_LEFT,4,8,2000",NULL);
					RefGPU[i]->DoWindowMethod("SizerAdd R,WS_VISIBLE|GPSS_RIGHT,4,8,2000",NULL);
					RefGPU[i]->DoWindowMethod("SizerAdd T,WS_VISIBLE|GPSS_TOP,4,8,2000",NULL);
					RefGPU[i]->DoWindowMethod("SizerAdd B,WS_VISIBLE|GPSS_BOTTOM,4,8,2000",NULL);
				}
				RefGPU[i]->DoWindowMethod("GetWindowTextEx",str+100);
				sprintf(str,"%s %d %s %s",GPUnit::aTypeUnit[RefGPU[i]->UnitType],i,(LPCSTR)RefGPU[i]->GetObjectName(),str+100);
				pos=str;
			}

			if (Type>0)	m_LUnit.AddString(pos);
			else
			{
				m_LUnit.DeleteString(i);
				m_LUnit.InsertString(i,pos);
				if (i==possel) m_LUnit.SetCurSel(i);
			}
		}
	}
}


void CDlgDialogEditor::OnButtonupdate()
{
	int nItem=m_ComboMethods.GetCurSel();
	OnSelchangeListunit();
	FillObjList(0);
	m_ComboMethods.SetCurSel(nItem);
}


void CDlgDialogEditor::OnRButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnRButtonDown(nFlags, point);
 	if (m_Tabs.GetCurSel()==4)
	{
		CRect re;
		m_StaticSize.GetWindowRect(&re);
		CRect re2;
		GetClientRect(&re2);
		ClientToScreen(&re2);
		re.OffsetRect(-re2.TopLeft());
		if (re.PtInRect(point)==TRUE && CurUnit!=NULL)
		{
			m_SizeFlag=TRUE;
			CurUnit->NoUpdateParent=TRUE;
		}
	}
}

void CDlgDialogEditor::OnRButtonUp(UINT nFlags, CPoint point)
{
	CDialog::OnRButtonUp(nFlags, point);
	m_SizeFlag=FALSE;
	if (CurUnit!=NULL)	CurUnit->NoUpdateParent=FALSE;
}

void CDlgDialogEditor::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDown(nFlags, point);
 	if (m_Tabs.GetCurSel()==4)
	{
		CRect re;
		m_StaticSize.GetWindowRect(&re);
		CRect re2;
		GetClientRect(&re2);
		ClientToScreen(&re2);
		re.OffsetRect(-re2.TopLeft());
		if (re.PtInRect(point)==TRUE && CurUnit!=NULL)
		{
			m_PosFlag=TRUE;
			CurUnit->NoUpdateParent=TRUE;
		}
	}
}

void CDlgDialogEditor::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonUp(nFlags, point);
	m_PosFlag=FALSE;
	if (CurUnit!=NULL)	CurUnit->NoUpdateParent=FALSE;
}

void CDlgDialogEditor::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialog::OnMouseMove(nFlags, point);

	if (m_SizeFlag==TRUE || m_PosFlag==TRUE)
	{
		CRect reStaticSize,MainRect;

		if (m_LUnit.GetCurSel( )==0) MainRect=CRect(0,0,800,600);
		else RefGPU[0]->GPGetWndRect(&MainRect);


		m_StaticSize.GetWindowRect(&reStaticSize);
		ScreenToClient(&reStaticSize);

		if (m_PosFlag==TRUE)
		{
			m_sl.SetPos(((point.x-reStaticSize.left)*MainRect.Width())/reStaticSize.Width());
			m_st.SetPos(((point.y-reStaticSize.top)*MainRect.Height())/reStaticSize.Height());
		}
		else
		{
			m_sw.SetPos(((point.x-reStaticSize.left)*MainRect.Width())/reStaticSize.Width()-m_sl.GetPos());
			m_sh.SetPos(((point.y-reStaticSize.top)*MainRect.Height())/reStaticSize.Height()-m_st.GetPos());
		}
	}
}


void CDlgDialogEditor::OnSelchangeCombosizing()
{

	char str[500];
	m_ComboSizing.GetWindowText(str,50);
	char *pp=strchr(str,';');
	if (pp!=NULL)
	{
		str[m_EditSizing.GetLine(0,str+100,390)+100]=0;
		sprintf(str,"SIZING=%d,%s;",atoi(pp+2),str+100);
		if (NoUpdateTxt==FALSE)	CurUnit->GPSetProperty(str);
	}
}

void CDlgDialogEditor::OnChangeEditsizing()
{
	if (CurUnit!=NULL)
	{
		char str[500];
		str[m_EditSizing.GetLine(0,str+100,390)+100]=0;
		sprintf(str,"SIZING=%d,%s;",m_ComboSizing.GetCurSel(),str+100);
		if (NoUpdateTxt==FALSE)	CurUnit->GPSetProperty(str);
	}

}

void CDlgDialogEditor::OnChangeEdittext()
{
	if (CurUnit!=NULL)
	{
		char str[500];
		str[m_EditText.GetLine(0,str+100,390)+100]=0;
		sprintf(str,"TEXT=%s",str+100);
		if (NoUpdateTxt==FALSE)	CurUnit->GPSetProperty(str);
	}
}


BOOL CDlgDialogEditor::GetCreationString(UINT Id, char *str)
{
	BOOL ret=FALSE;
	if (Id<(*RefGPU)->m_NGPUNIT && RefGPU[Id] && (RefGPU[Id]->UnitHWND || RefGPU[Id]->m_WindowLessFlag))
	{

		char Stl[1000];*Stl=0;
		char StrText[500];*StrText=0;
		CRect re;
		CRect re2;

		if (RefGPU[Id]->m_WindowLessFlag==0)
		{
			CWnd::FromHandle(RefGPU[Id]->UnitHWND)->GetWindowRect(&re);
			if (Id!=0)
			{
				::GetClientRect(::GetParent(RefGPU[Id]->UnitHWND),&re2);
				::ClientToScreen(::GetParent(RefGPU[Id]->UnitHWND),(POINT *)(&re2));
				::ClientToScreen(::GetParent(RefGPU[Id]->UnitHWND),((POINT *)(&re2))+1);
				re.OffsetRect(-re2.TopLeft());
			}


			switch(RefGPU[Id]->UnitType)
			{
			case GPUnit::UT_BUTTON:
			case GPUnit::UT_BBUTTON:
				RefGPU[Id]->DoWindowMethod("GetWindowText",StrText);
				break;
			default:
				RefGPU[Id]->DoWindowMethod("GetWindowTextEx",StrText);
				break;
			}

			switch(RefGPU[Id]->UnitType)
			{
			case GPUnit::UT_DATETIMECTRL:
			case GPUnit::UT_MONTHCAL:
			case GPUnit::UT_TREECTRL:
			case GPUnit::UT_HEADER:
			case GPUnit::UT_SLIDER:
			case GPUnit::UT_TABCTRL:
			case GPUnit::UT_SPINBUTTON:
			case GPUnit::UT_LISTBOX:
			case GPUnit::UT_COMBOBOX:
			case GPUnit::UT_COMBOBOXEX:
			case GPUnit::UT_SCROLLBAR:
			case GPUnit::UT_PROGRESS:
			case GPUnit::UT_ANIMAT:
			case GPUnit::UT_CHECKLISTBOX:
			case GPUnit::UT_DRAGLISTBOX:
			case GPUnit::UT_LISTCTRL:
			case GPUnit::UT_STATUSBARCTRL:
			case GPUnit::UT_TOOLBARCTRL:
			case GPUnit::UT_STATUSBAR:
			case GPUnit::UT_TOOLBAR:
			case GPUnit::UT_DIALOGBAR:
			case GPUnit::UT_REBARCTRL:
			case GPUnit::UT_DRAW:
			case GPUnit::UT_REBAR:
			case GPUnit::UT_FLEXGRID:
			case GPUnit::UT_WEBBROWSER:
				*StrText=0;break;
			}
		}

		GetObjStyleStr(Id,Stl);

		if (Id==0)	sprintf(str,"  IdDlg=%s; IdParentDlg=%d\r\n CALL GP.CreateDlg(IdDlg,IdParentDlg,\"",(LPCSTR)RefGPU[0]->GetObjectName(),0);
		else
			sprintf(str,"    CALL GP.DlgCreateObj(IdDlg,\"%s\",\"%s\",\"",(LPCSTR)RefGPU[Id]->GetObjectName(),GPUnit::aTypeUnit[RefGPU[Id]->UnitType]);

		if (*StrText!=0)						sprintf(str+(int)strlen(str),"TEXT=%s;",StrText);
		if (RefGPU[Id]->ToolTipText!=NULL)	sprintf(str+(int)strlen(str),"TOOLTIP=%s;",RefGPU[Id]->ToolTipText);

		sprintf(str+(int)strlen(str),"STYLE=%s;",Stl);

		if (RefGPU[Id]->m_WindowLessFlag==0)
			sprintf(str+(int)strlen(str),"RECT=%d,%d,%d,%d;",re.left,re.top,re.right,
				((RefGPU[Id]->UnitType==GPUnit::UT_COMBOBOX || RefGPU[Id]->UnitType==GPUnit::UT_COMBOBOXEX) && re.Height()<25)?re.top+250:re.bottom);

		if (RefGPU[Id]->m_WindowLessFlag==0 && Id!=0)
		{
			if (RefGPU[Id]->ParentNum!=0) sprintf(str+(int)strlen(str),"PARENT=%d;",RefGPU[Id]->ParentNum);
			if (RefGPU[Id]->GroupNum!=NULL && (int)strlen(RefGPU[Id]->GroupNum)!=0) sprintf(str+(int)strlen(str),"GROUP=%s;",RefGPU[Id]->GroupNum);
			if (strcmp("NNNN",RefGPU[Id]->GetSizingStyle())!=0)
			{
				CString resowner;
				UINT ownerID=0;
				resowner.Format("%d",ownerID=RefGPU[Id]->GetResizeingOwner());
				if (RefGPU[ownerID]) resowner=RefGPU[ownerID]->GetObjectName();
				sprintf(str+(int)strlen(str),"SIZING=%s,%s;",(LPCSTR)resowner,RefGPU[Id]->GetSizingStyle());
			}
		}


		if (Id==0)	strcat(str,"\",TmpRes)");
		else		strcat(str,"\")");
		ret=TRUE;
	}

return ret;
}

BOOL CDlgDialogEditor::GetMessagesString(UINT Id, char *str)
{
	BOOL bret=FALSE;
	if (Id>=0 && RefGPU && Id<(*RefGPU)->m_NGPUNIT  && RefGPU[Id] && (RefGPU[Id]->UnitHWND || RefGPU[Id]->m_WindowLessFlag) && RefGPU[Id]->GPMSG)
	{
		bret=TRUE;
		char Stl[1000];*Stl=0;
		CString ret="";

		const char *tmps=RefGPU[Id]->GPMSG->GetActiveMessages();
		if (tmps && *tmps)
		{
			CString tmpMesEt;
			CString tmpMesCur;
			int nmm;
			for(nmm=0; nmm<2;nmm++)
			{
				int nMessCur=1;
				const char *MessEtalon=nmm?aUnitCommonMessages:aUnitMessage[RefGPU[Id]->UnitType];
				while((tmpMesCur=ExtractField(tmps,nMessCur,","))!="")
				{
					int nMessEt=1;
					tmpMesCur.MakeUpper();
					while((tmpMesEt=ExtractField(MessEtalon,nMessEt,","))!="")
					{
						tmpMesEt.MakeUpper();
						if (tmpMesEt==tmpMesCur)
						{
							tmpMesEt=ExtractField(MessEtalon,nMessEt,",");
							if (Id)
								ret+="        CALL GP.DlgObjAddMessage(IdDlg,\""+RefGPU[Id]->GetObjectName()+"\",\""+tmpMesEt+"\",\"XXX.Remap\")\r\n";
								else
								ret+="        CALL GP.AddDlgMessage(IdDlg,\""+tmpMesEt+"\",\"XXX.Remap\")\r\n";
							nMessEt=0xFFFF;
						}
						nMessEt++;
					}
					nMessCur++;
				}
			}
		}
		strcpy(str,ret);
	}
	return bret;
}

void CDlgDialogEditor::OnButtoncreatoclip()
{
	int id=m_LUnit.GetCurSel( );
	if (id!=LB_ERR && RefGPU[id]!=NULL)
	{
		char str[1500];*str=0;
		GetCreationString(id,str);
		StringToClip(str);
	}
}

void CDlgDialogEditor::OnChangeEdittooltip()
{
	if (CurUnit!=NULL)
	{
		char str[500];
		str[m_EditToolTip.GetLine(0,str+100,390)+100]=0;
		sprintf(str,"TOOLTIP=%s",str+100);
		if (NoUpdateTxt==FALSE)	CurUnit->GPSetProperty(str);
	}
}

// Ввод нового объекта
void CDlgDialogEditor::OnDblclkListunit()
{
	int id=m_LUnit.GetCurSel( );
	if (id!=LB_ERR && id!=0 && RefGPU[id]==NULL)
	{
		m_BtCreatToClip.ModifyStyle(WS_VISIBLE,0);
		m_btdelete.ModifyStyle(WS_VISIBLE,0);
		m_LUnit.ModifyStyle(WS_VISIBLE,0);
		m_ListUnitType.ModifyStyle(0,WS_VISIBLE);
		m_ListUnitType.SetFocus();
		Invalidate();
	}
}

void CDlgDialogEditor::OnDblclkListunittype()
{
	int typ=m_ListUnitType.GetItemData(m_ListUnitType.GetCurSel( ));
	int UnitNum=m_LUnit.GetCurSel( );
	char *initstr[]={
/*0*/				"RECT=1,1,50,50;STYLE=WS_VISIBLE",
/*CONTROL*/			"RECT=1,1,150,100;STYLE=WS_VISIBLE|WS_CHILD",
/*DRAW*/			"RECT=1,1,50,50;STYLE=WS_VISIBLE",
/*ANISTATIC*/		"RECT=1,1,150,17;STYLE=WS_VISIBLE",
/*ANIBUTTON*/		"RECT=1,1,50,50;STYLE=WS_VISIBLE",
/*FRAMEBAR*/		"RECT=1,1,50,50;STYLE=WS_VISIBLE|WS_CAPTION|WS_BORDER;",
/*DATETIMECTRL*/	"RECT=1,1,50,50;STYLE=WS_VISIBLE",
/*DLGBAR*/			"RECT=1,1,150,150;STYLE=WS_VISIBLE|WS_CHILD|WS_OVERLAPPEDWINDOW|",
/*RTF*/				"RECT=1,1,250,350;STYLE=WS_VISIBLE|WS_VSCROLL|WS_HSCROLL|_AUTOVSCROLL|_AUTOHSCROLL|_WANTRETURN|_MULTILINE",
/*TREECTRL*/		"RECT=1,1,200,250;STYLE=WS_VISIBLE",
/*HEADER*/			"RECT=1,1,50,50;STYLE=WS_VISIBLE",
/*SLIDER*/			"RECT=1,1,50,50;STYLE=WS_VISIBLE",
/*TABCTRL*/			"RECT=1,1,200,250;STYLE=WS_VISIBLE",
/*SPINBUTTON*/		"RECT=1,1,50,50;STYLE=WS_VISIBLE",
/*BBUTTON*/			"RECT=1,1,50,50;STYLE=WS_VISIBLE",
/*STATIC*/			"RECT=1,1,150,17;STYLE=WS_VISIBLE",
/*EDIT*/			"RECT=1,1,150,15;STYLE=WS_VISIBLE",
/*BUTTON*/			"RECT=1,1,100,25;STYLE=WS_VISIBLE",
/*LISTBOX*/			"RECT=1,1,200,250;STYLE=WS_VISIBLE|WS_VSCROLL",
/*COMBOBOX*/		"RECT=1,1,150,450;STYLE=WS_VISIBLE|_DROPDOWNLIST|WS_VSCROLL",
/*SCROLLBAR*/		"RECT=1,1,50,20;STYLE=WS_VISIBLE",
/*PROGRESS*/		"RECT=1,1,150,20;STYLE=WS_VISIBLE",
/*ANIMAT*/			"RECT=1,1,50,50;STYLE=WS_VISIBLE|WS_CHILD",
/*CHECKLISTBOX*/	"RECT=1,1,200,250;STYLE=WS_VISIBLE|WS_VSCROLL",
/*DRAGLISTBOX*/		"RECT=1,1,200,250;STYLE=WS_VISIBLE|WS_VSCROLL",
/*LISTCTRL*/		"RECT=1,1,200,250;STYLE=WS_VISIBLE",
/*STATUSBARCTRL*/	"RECT=1,1,200,250;STYLE=WS_VISIBLE",
/*TOOLBARCTRL*/		"RECT=1,1,200,250;STYLE=WS_VISIBLE|_BUTTON|_AUTOSIZE|_WRAPABLE|CCS_TOP|",
/*STATUSBAR*/		"RECT=0,0,0,0;STYLE=WS_VISIBLE|CBRS_ALIGN_BOTTOM|",
/*TOOLBAR*/			"RECT=0,0,0,0;STYLE=WS_VISIBLE|CBRS_ALIGN_TOP|CBRS_GRIPPER|_AUTOSIZE|_WRAPABLE|_EX_DRAWDDARROWS|",
/*DIALOGBAR*/		"RECT=0,0,110,26;STYLE=CBRS_ALIGN_ANY|WS_VISIBLE",
/*REBARCTRL*/		"RECT=0,0,110,26;STYLE=CCS_TOP|WS_VISIBLE",
/*REBAR*/			"RECT=0,0,110,26;STYLE=CBRS_ALIGN_TOP|CBRS_GRIPPER|WS_VISIBLE",
/*FLEXGRID*/		"RECT=0,0,200,250;STYLE=WS_VISIBLE|WS_CHILD",
/*MONTHCAL*/		"RECT=1,1,190,154;STYLE=WS_VISIBLE",
/*WEBBROWSER*/		"RECT=1,1,200,250;STYLE=WS_VISIBLE|WS_VSCROLL|WS_HSCROLL|WS_EX_CLIENTEDGE|",
/*COMBOBOXEX*/		"RECT=1,1,150,450;STYLE=WS_VISIBLE|_DROPDOWNLIST|WS_VSCROLL",
/*EDITOR*/			"RECT=1,1,350,450;STYLE=WS_VISIBLE|WS_VSCROLL|WS_HSCROLL|",
	};

	BOOL cont=TRUE;
	CString tmpinit=initstr[typ];

	UINT wl_flag=0;
	if (m_ChkWINDOWLESS.GetCheck())
	{
		wl_flag=1;
		tmpinit+=";ADDSTYLE=WS_WINDOWLESS;";
	}

	OnKillfocusListunittype();

	if (cont!=FALSE)
	{
		char *str= new char [10000];
		FILE *tmp=fopen("Create.ini","rt");
		if (tmp!=NULL)
		{
			CString csCmpStr="CREATION STRING FOR ";
			csCmpStr+=GPUnit::aTypeUnit[typ];
			int cmplen=csCmpStr.GetLength();
			csCmpStr.MakeUpper();

			while(fgets(str,990,tmp)!=NULL)
			{
				str[cmplen]=0;
				_strupr(str);
				if (csCmpStr==str)
				{
					tmpinit=str+(cmplen+1);
					tmpinit.Replace("\r","");
					tmpinit.Replace("\n","");
					if (wl_flag)
						tmpinit+=";ADDSTYLE=WS_WINDOWLESS;";
					break;
				}
			}
			rewind(tmp);
		}

		if (typ==GPUnit::UT_CONTROL && tmpinit.Find("CLSID=")<0)
		{
			CDlgInitComObject dlg;
			if (dlg.DoModal()==IDOK)
				tmpinit+=" ;CLSID="+dlg.m_EditCLSID+";";
			else cont=FALSE;
		}

		if (cont)
		{
			if (GPOd)	GPOd->CreateUnit(typ,UnitNum,tmpinit,GPOd->m_hWnd);
			else
			if (GPOf)	GPOf->CreateUnit(typ,UnitNum,tmpinit,GPOf->m_hWnd);
			else
			if (GPOw)	GPOw->CreateUnit(typ,UnitNum,tmpinit,GPC.m_hViewWnd);

			if (tmp!=NULL)
			{
				int tmpLen=strlen(GPUnit::aTypeUnit[typ]);
				while(fgets(str,990,tmp)!=NULL)
				{
					if (wl_flag && *str=='_') strcpy(str,str+1);
					if ((atoi(str)==0 && typ==0 && *str=='0') || (atoi(str)==typ && typ) || strncmp(GPUnit::aTypeUnit[typ],str,tmpLen)==00)
					{
						char *pos=strchr(str,',');
						if (pos++!=NULL)
						{

							char *pos2=pos;
							do	if (*pos2=='\r' || *pos2=='\n') *pos2=0;
							while(*(pos2++)!=0);

							pos2=strchr(pos,',');

							if (pos2++!=NULL)
							{
								switch(*pos)
								{
								case 'M':
									{
										char *cpos=pos2;
										while((cpos=strstr(cpos,"\\x1")))
										{
											strcpy(cpos,cpos+2);
											*cpos=1;
										}
										cpos=pos2;
										while((cpos=strstr(cpos,"\\x2")))
										{
											strcpy(cpos,cpos+2);
											*cpos=2;
										}
										cpos=pos2;
										while((cpos=strstr(cpos,"\\x3")))
										{
											strcpy(cpos,cpos+2);
											*cpos=3;
										}

										RefGPU[UnitNum]->DoMethod(pos2,NULL);
									}
									break;
								case 'P':	RefGPU[UnitNum]->RemappingProperty(pos2);	break;
								}
							}
						}

					}
				}
				fclose(tmp);
				OnButtonupdate();
			}
		}
		if (tmp!=NULL) fclose(tmp);
		delete[] str;
	}
	FillObjList(0);
}

void CDlgDialogEditor::OnKillfocusListunittype()
{
	m_LUnit.ModifyStyle(0,WS_VISIBLE);
	OnButtonupdate();
	m_LUnit.Invalidate();
	m_LUnit.SetFocus();
}

void CDlgDialogEditor::UpdateEditDlg()
{
	RefGPU[0]->GPUpdateUnit();
}


void CDlgDialogEditor::OnButtonbuffall()
{
	CString str="*** Beginning of objects section. Created by GP_TERM (don't edit this line)\r\n***\r\n";
	char *str1=new char [10000];
	if (str1)
	{
		int i;
		for(i=0;(UINT)i<(*RefGPU)->m_NGPUNIT;i++)
		{
			if (RefGPU[i])
			{
				*str1=0;
				if (GetCreationString(i,str1)==TRUE)	{	str+=str1;str+="\r\n";}
				if (GetMessagesString(i,str1)==TRUE)	{	str+=str1;str+="\r\n";}
			}
		}
		delete[] str1;
	}
	str+="***\r\n*** End of objects section. Created by GP_TERM (don't edit this line)\r\n";
	StringToClip(str);
}

LRESULT CDlgDialogEditor::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	try
	{
		if ((m_UpdateFlags&0x0001))
		{
			if (message==GPN_UPDATESIZE) GetParent()->SendMessage(GPN_UPDATESIZE);
			if (message==WM_WINDOWPOSCHANGED)
			{
				if (xWindowProc==((WINDOWPOS *)lParam)->x && yWindowProc==((WINDOWPOS *)lParam)->y )
				{
					OnButtonupdate() ;
				}
				xWindowProc=((WINDOWPOS *)lParam)->x;
				yWindowProc=((WINDOWPOS *)lParam)->y;
			}
		}
		return CDialog::WindowProc(message, wParam, lParam);
	}
	catch(...)
	{
		char tmps[100];
		sprintf(tmps,"Message %X WPARAM %X LPARAM %X",message, wParam, lParam);
		GPC.m_ErrReport.GPWriteErrorLog("CDlgDialogEditor", "WindowProc",tmps);
	}
	return 0;
}

void CDlgDialogEditor::OnSelchangeComboowner()
{
	char str[100];
	m_ComboOwner.GetWindowText(str,50);
	char *pp=strchr(str,' ');
	if (pp!=NULL)
	{
		sprintf(str,"PARENT=%d",atoi(pp+1));
		if (NoUpdateTxt==FALSE)	CurUnit->GPSetProperty(str);
	}
}


void CDlgDialogEditor::OnKillfocusEditgroup()
{
	int nnn=::GetWindowTextLength(m_EditGroup.m_hWnd);
	char *str= new char [nnn+20];
	strcpy(str,"GROUP=");
	if (nnn) nnn=::GetWindowText(m_EditGroup.m_hWnd,str+6,nnn+2);
	str[nnn+6]=0;
	if ((CurUnit->UnitId&0xFFFF)!=0 && NoUpdateTxt==FALSE)
		CurUnit->GPSetProperty(str);
	delete[] str;
}

void CDlgDialogEditor::OnChecktopmost()
{
	int ch=m_ChecOnTop.GetCheck();
	SetWindowPos(ch==1?&wndTopMost:GetParent(),0,0,0,0,(ch>1?SWP_NOREPOSITION:0)|SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOSIZE);
}

void CDlgDialogEditor::OnTimer(UINT nIDEvent)
{
	if (nIDEvent==1)
	{
		KillTimer(nIDEvent);
		CPoint po;
		GetCursorPos(&po);
		CRect re;
		CRect etRect(0,0,30000,30000);
		GetWindowRect(&re);
		if (RefGPU!=NULL && RefGPU[0]!=NULL && RefGPU[0]->UnitHWND!=NULL && !re.PtInRect(po))
		{
			CWnd::FromHandle(RefGPU[0]->UnitHWND)->GetWindowRect(&re);
			if (re.PtInRect(po))
			{
				int id=0;
				int i;
				for(i=0;(UINT)i<(*RefGPU)->m_NGPUNIT;i++)
					if (RefGPU[i]!=NULL && RefGPU[i]->UnitHWND!=NULL && CWnd::FromHandle(RefGPU[i]->UnitHWND)->IsWindowVisible())
					{
						CWnd::FromHandle(RefGPU[i]->UnitHWND)->GetWindowRect(&re);
						if (re.PtInRect(po))
						{
							if (re.Width()+re.Height()<etRect.Width()+etRect.Height())
							{
								etRect=re;
								id=i;
							}
						}
					}

				int idOld;
				do
				{
					idOld=id;
					for(i=0;(UINT)i<(*RefGPU)->m_NGPUNIT;i++)
						if (i!=id && RefGPU[i]!=NULL && RefGPU[i]->UnitHWND!=NULL && !CWnd::FromHandle(RefGPU[i]->UnitHWND)->IsWindowVisible() && CWnd::FromHandle(RefGPU[i]->UnitHWND)->GetParent()->m_hWnd==RefGPU[id]->UnitHWND)
						{
							CWnd::FromHandle(RefGPU[i]->UnitHWND)->GetWindowRect(&re);
							if (re.PtInRect(po))
							{
								if (re.Width()+re.Height()<etRect.Width()+etRect.Height())
								{
									etRect=re;
									id=i;
								}
							}
						}
				}
				while(id!=idOld);

				if (id!=m_LUnit.GetCurSel( ))
				{
					m_LUnit.SetCurSel(id);
					OnSelchangeListunit();
				}

			}
		}

		OnCheckselect();
	}
	else	ModifyStyle(WS_DISABLED,0);

	CDialog::OnTimer(nIDEvent);
}

void CDlgDialogEditor::OnCheckselect()
{
	KillTimer(1);
	if ((m_CheckAutoSel.GetState()&0x0003)!=0)
	{
		SetTimer(1,1000,0);
	}
}

void CDlgDialogEditor::OnSelchangeCombomethods()
{
	int nItem=m_ComboMethods.GetCurSel();
	if (CurUnit!=NULL && nItem!=CB_ERR)
	{
		UINT MetData=m_ComboMethods.GetItemData(nItem);

		CString MetName,MetParam;
		CDlgMethods::GetParamStr(CurUnit->UnitType,MetData,MetName,MetParam);
		m_EditParamsHelp.SetWindowText(MetParam);
	}

}

void CDlgDialogEditor::OnButtonexecute()
{
	int nItem=m_ComboMethods.GetCurSel();
	if (CurUnit!=NULL && nItem!=CB_ERR)
	{
		CString MetName,MetParam;
		m_ComboMethods.GetLBText(nItem,MetName);
		m_EditParams.GetWindowText(MetParam);
		if (MetParam.GetLength()>0) MetName+=" "+MetParam;
		char *oStr=new char [150000];
		char *MetStr=new char [MetName.GetLength()+100];
		strcpy(MetStr,MetName);
		*oStr=0;

		char *pos=MetStr;
		while((pos=strstr(pos,"\\x1")))
		{
			strcpy(pos,pos+2);
			*pos=1;
		}
		pos=MetStr;
		while((pos=strstr(pos,"\\x2")))
		{
			strcpy(pos,pos+2);
			*pos=2;
		}
		pos=MetStr;
		while((pos=strstr(pos,"\\x3")))
		{
			strcpy(pos,pos+2);
			*pos=3;
		}

		if (CurUnit->UnitType!=GPUnit::UT_MAINDLGSCR)	CurUnit->DoMethod(MetStr,oStr);
		else
		if (GPOd)
		{
			if (GPOd->m_hWnd==::GetDesktopWindow())
				GPOd->DoDlgMethod(MetStr,oStr);
				else
				GPOd->SendMessage(GPM_DODLGMETHOD,(WPARAM)MetStr,(LPARAM)oStr);
		}
		else
		if (GPOw) GPOw->DoMethod(0,MetStr,oStr);
		else
			GetParent()->SendMessage(GPM_DODLGMETHOD,(WPARAM)MetStr,(LPARAM)oStr);


		pos=oStr;
		while(*pos!=0)
		{
			if (*pos==127) *pos=GPC.DelimiterIn1;
			else
			if (*pos==7) *pos=GPC.DelimiterIn2;
			else
			if (*pos==2) *pos=GPC.DelimiterIn3;
			pos++;
		}

		m_EditResult.SetSel(0,-1);
		m_EditResult.ReplaceSel(oStr);
		delete[] oStr;
		delete[] MetStr;
	}

}

void CDlgDialogEditor::OnClose()
{
	ClearItemsData(&m_WSList);
	ClearItemsData(&m_ListUnitStl);
	CDialog::OnClose();
}

void CDlgDialogEditor::OnBtndoproperty()
{
	if (CurUnit!=NULL)
	{
		CString str;
		GetDlgItemText(IDC_EDITPROPERTY,str);
		CurUnit->RemappingProperty(str);
		OnButtonupdate();
	}
}

void CDlgDialogEditor::OnDblclkListevents()
{
	int id=m_ListEvents.GetCurSel( );

	if (id!=LB_ERR && CurUnit!=NULL)
	{
		char str[500];
		m_ListEvents.GetText(id,str);
		if (m_ListEvents.GetCheck(id )==TRUE)
		{
			CurUnit->GPDeleteMessage(str);
			m_ListEvents.SetCheck(id,FALSE);
		}
		else
		{
			CurUnit->GPAddMessage(str);
			m_ListEvents.SetCheck(id,TRUE);
		}
	}
}

void CDlgDialogEditor::UpdateCheckEvents()
{
	int nItem=m_ListEvents.GetCount();
	if (CurUnit->GPMSG!=NULL && nItem!=LB_ERR)
	{
		CString str;
		int i;
		for(i=0;i<nItem;i++)
		{
			m_ListEvents.GetText(i,str);
			m_ListEvents.SetCheck(i,CurUnit->GPMSG->FindInActive(str)!=NULL?1:0);
		}
	}
}

void CDlgDialogEditor::OnBtnclallev()
{
	int nItem=m_ListEvents.GetCount( );
	char str[500];

	if (CurUnit!=NULL)
	{
		int i;
		for(i=0;i<nItem;i++)
		{
			m_ListEvents.GetText(i,str);
			if (m_ListEvents.GetCheck(i)==TRUE)
			{
				CurUnit->GPDeleteMessage(str);
				m_ListEvents.SetCheck(i,FALSE);
			}
		}
	}
}

void CDlgDialogEditor::OnBtnclalltext()
{
	m_EditEventsOutput.SetSel(0,-1);
	m_EditEventsOutput.ReplaceSel("");
}

void CDlgDialogEditor::OnBtnfrgdlg()
{
	char str[55];
	str[m_edFRG.GetLine(0,str,50)]=0;

	int R=0,G=0,B=0;
	m_LastScanf=sscanf(str,"%d,%d,%d",&R,&G,&B);
	CColorDialog dlg (RGB(R,G,B),CC_FULLOPEN|CC_ANYCOLOR, this);
	if (dlg.DoModal()==IDOK)
	{
		COLORREF clr=dlg.GetColor();
		sprintf(str,"%d,%d,%d",GetRValue(clr),GetGValue(clr),GetBValue(clr));
		m_edFRG.SetWindowText(str);
	}

}
void CDlgDialogEditor::OnBtnbrushdlg()
{
	char str[55];
	str[m_edBrush.GetLine(0,str,50)]=0;

	int R=0,G=0,B=0;
	m_LastScanf=sscanf(str,"%d,%d,%d",&R,&G,&B);
	CColorDialog dlg (RGB(R,G,B),CC_FULLOPEN|CC_ANYCOLOR, this);
	if (dlg.DoModal()==IDOK)
	{
		COLORREF clr=dlg.GetColor();
		sprintf(str,"%d,%d,%d",GetRValue(clr),GetGValue(clr),GetBValue(clr));
		m_edBrush.SetWindowText(str);
	}
}
void CDlgDialogEditor::OnBtnbkgdlg()
{
	char str[55];
	str[m_edBKG.GetLine(0,str,50)]=0;

	int R=0,G=0,B=0;
	m_LastScanf=sscanf(str,"%d,%d,%d",&R,&G,&B);
	CColorDialog dlg (RGB(R,G,B),CC_FULLOPEN|CC_ANYCOLOR, this);
	if (dlg.DoModal()==IDOK)
	{
		COLORREF clr=dlg.GetColor();
		sprintf(str,"%d,%d,%d",GetRValue(clr),GetGValue(clr),GetBValue(clr));
		m_edBKG.SetWindowText(str);
	}
}


void CDlgDialogEditor::OnBtnbkg()
{
	if (CurUnit!=NULL)
	{
		char str[55];
		strcpy(str,"BKG=");
		str[m_edBKG.GetLine(0,str+4,50)+4]=0;
		CurUnit->GPSetProperty(str);
	}
}

void CDlgDialogEditor::OnBtnbrush()
{
	if (CurUnit!=NULL)
	{
		char str[255];
		strcpy(str,"BRUSH=");
		str[m_edBrush.GetLine(0,str+6,50)+6]=0;
		strcat(str,",");
		int nItem;
		nItem=m_cbBrushStyle.GetCurSel();
		if (nItem!=CB_ERR)
		{
			int l=m_cbBrushStyle.GetLBText(nItem,str+(int)strlen(str));
			if (l!=CB_ERR)
				str[(int)strlen(str)+l]=0;
		}
		strcat(str,"|");
		nItem=m_cbBrushType.GetCurSel();
		if (nItem!=CB_ERR)
		{
			int l=m_cbBrushType.GetLBText(nItem,str+(int)strlen(str));
			if (l!=CB_ERR)
				str[(int)strlen(str)+l]=0;
		}
		CurUnit->GPSetProperty(str);
	}
}

void CDlgDialogEditor::OnBtnfrg()
{
	if (CurUnit!=NULL)
	{
		char str[55];
		strcpy(str,"FRG=");
		str[m_edFRG.GetLine(0,str+4,50)+4]=0;
		CurUnit->GPSetProperty(str);
	}
}


void CDlgDialogEditor::OnButtonmessagetoclip()
{
	int id=m_LUnit.GetCurSel( );
	if (id!=LB_ERR && RefGPU[id]!=NULL)
	{
		char *str=new char [10000];
		*str=0;
		GetMessagesString(id,str);
		StringToClip(str);
		delete[] str;
	}
}

void CDlgDialogEditor::OnCheckwindowless()
{
}
