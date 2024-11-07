// DlgMethods.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgMethods.h"
#include "GPUnit.h"
#include "GPFrameWnd.h"

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
#include "GPSlider.h"
#include "GPHeader.h"
#include "GPTree.h"
#include "GP_RTF.h"
#include "GPDlgBar.h"
#include "GPFrameBar.h"
#include "GPStatusBarCtrl.h"
#include "GPStatusBar.h"
#include "GPToolBarCtrl.h"
#include "GPToolBar.h"
#include "GPDialogBar.h"
#include "GPReBarCtrl.h"
#include "GPReBar.h"
#include "GPObjDialog.h"
#include "GPDrawWnd.h"
#include "gpmsflexgrid.h"
#include "GPWebBrowser2.h"
#include "GPScintilla.h"
#include "GPToolTipCtrl.h"
#include "GP_Control.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMethods dialog


CDlgMethods::CDlgMethods(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMethods::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMethods)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgMethods::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMethods)
	DDX_Control(pDX, IDC_CHECK1, m_CheckParam);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	DDX_Control(pDX, IDC_COMBO2, m_ComboMethod);
	DDX_Control(pDX, IDC_COMBO1, m_ComboType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMethods, CDialog)
	//{{AFX_MSG_MAP(CDlgMethods)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnChangeType)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnChangeMethod)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK1, OnCheckParam)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonBuff)
	ON_BN_CLICKED(IDC_BUTTON2, OnButtonInsert)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMethods message handlers

BOOL CDlgMethods::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_CheckParam.SetCheck(1);

	UINT i;
	for(i=0;*GPUnit::aTypeUnit[i];i++)
		{
			int nItem=m_ComboType.AddString(GPUnit::aTypeUnit[i]);
			m_ComboType.SetItemData(nItem,GPUnit::auTypeUnit[i]);
		}
	return TRUE;
}
void CDlgMethods::OnChangeType()
{
	int nItem=m_ComboType.GetCurSel();
	int nUnitType=m_ComboType.GetItemData(nItem);
	FillMethodCombo(nUnitType,&m_ComboMethod,NULL,GPUnit::UST_ALLMAIN);
}

void CDlgMethods::FillMethodCombo(int iUnitType,CComboBox *MetCombo, GPUnit *iGPU, DWORD dwSubType)
{
	UINT i;
	MetCombo->ResetContent();
	if (iUnitType!=CB_ERR)
	{
		switch(GPUnit::auTypeUnit[iUnitType])
		{
			case GPUnit::UT_MAINDLGSCR:
				for(i=0;i<CGPToolTipCtrl::uNToolTipMethods;i++)
				{
					int tmpNitem=MetCombo->AddString(CGPToolTipCtrl::cArrToolTipMethods[i]);
					MetCombo->SetItemData(tmpNitem,i|0x8FFF0000);
				}
			default:
				for(i=0;i<CGPToolTipCtrl::uNToolTipMethodsAll;i++)
				{
					int tmpNitem=MetCombo->AddString(CGPToolTipCtrl::cArrToolTipMethodsAll[i]);
					MetCombo->SetItemData(tmpNitem,i|0x4FFF0000);
				}
				for(i=0;*GPUnit::cArrMethods[i];i++)
				{
					int tmpNitem=MetCombo->AddString(GPUnit::cArrMethods[i]);
					MetCombo->SetItemData(tmpNitem,i|0xFFFF0000);
				}
				break;
		}

		UINT nMeth=0;
		const char **cMeth=NULL;
		UINT Hwrd=0;
		switch(GPUnit::auTypeUnit[iUnitType])
		{
			case GPUnit::UT_ANIBUTTON:
				cMeth=GPButton::cArrMethods;
				nMeth=GPButton::uNMethods;
				Hwrd=GPUnit::UT_BUTTON;
				break;
			case GPUnit::UT_ANISTATIC:
				cMeth=GPStatic::cArrMethods;
				nMeth=GPStatic::uNMethods;
				Hwrd=GPUnit::UT_STATIC;
				break;
			case GPUnit::UT_STATUSBAR:
				cMeth=GPUnit::cArrControlBarMethod;
				nMeth=GPUnit::uNControlBarMethod;
				Hwrd=GPUnit::UT_STATUSBAR;
				break;
			case GPUnit::UT_REBAR:
				cMeth=GPUnit::cArrControlBarMethod;
				nMeth=GPUnit::uNControlBarMethod;
				Hwrd=GPUnit::UT_REBAR;
				break;
			case GPUnit::UT_TOOLBAR:
				cMeth=GPUnit::cArrControlBarMethod;
				nMeth=GPUnit::uNControlBarMethod;
				Hwrd=GPUnit::UT_TOOLBAR;
				break;
			case GPUnit::UT_DIALOGBAR:
				cMeth=GPUnit::cArrControlBarMethod;
				nMeth=GPUnit::uNControlBarMethod;
				Hwrd=GPUnit::UT_DIALOGBAR;
				break;
		}
		for(i=0;i<nMeth;i++)
		{
			int tmpNitem=MetCombo->AddString(cMeth[i]);
			MetCombo->SetItemData(tmpNitem,i|(Hwrd*0x10000));
		}

		Hwrd=0;

		switch(GPUnit::auTypeUnit[iUnitType])
		{
			case GPUnit::UT_MAINDLGSCR:
				switch(dwSubType)
				{
				case GPUnit::UST_DLG:
					cMeth=GPObjDialog::cArrMethods;
					nMeth=GPObjDialog::uNMethods;
					break;
				case GPUnit::UST_FRAME:
					cMeth=GPFrameWnd::cArrMethods;
					nMeth=GPFrameWnd::uNMethods;
					break;
				case GPUnit::UST_SCREEN:
					break;
				case GPUnit::UST_ALLMAIN:
					cMeth=GPFrameWnd::cArrMethods;
					nMeth=GPFrameWnd::uNMethods;
					for(i=0;i<nMeth;i++)
					{
						int tmpNitem=MetCombo->AddString(cMeth[i]);
						MetCombo->SetItemData(tmpNitem,i);
					}
					cMeth=GPObjDialog::cArrMethods;
					nMeth=GPObjDialog::uNMethods;
					break;
				}
				break;
			case GPUnit::UT_DATETIMECTRL:
				cMeth=GPDateTimeCtrl::cArrMethods;
				nMeth=GPDateTimeCtrl::uNMethods;
				break;
			case GPUnit::UT_MONTHCAL:
				cMeth=GPMonthCalCtrl::cArrMethods;
				nMeth=GPMonthCalCtrl::uNMethods;
				break;
			case GPUnit::UT_DLGBAR:
				cMeth=GPDlgBar::cArrMethods;
				nMeth=GPDlgBar::uNMethods;
				break;
			case GPUnit::UT_FRAMEBAR:
				cMeth=GPFrameBar::cArrMethods;
				nMeth=GPFrameBar::uNMethods;
				break;
			case GPUnit::UT_RTF:
				cMeth=GP_RTF::cArrMethods;
				nMeth=GP_RTF::uNMethods;
				break;
			case GPUnit::UT_EDITOR:
				cMeth=GPScintilla::cArrMethods;
				nMeth=GPScintilla::uNMethods;
				break;
			case GPUnit::UT_TREECTRL:
				cMeth=GPTree::cArrMethods;
				nMeth=GPTree::uNMethods;
				break;
			case GPUnit::UT_HEADER:
				cMeth=GPHeader::cArrMethods;
				nMeth=GPHeader::uNMethods;
				break;
			case GPUnit::UT_SLIDER:
				cMeth=GPSlider::cArrMethods;
				nMeth=GPSlider::uNMethods;
				break;
			case GPUnit::UT_TABCTRL:
				cMeth=GPTabCtrl::cArrMethods;
				nMeth=GPTabCtrl::uNMethods;
				break;
			case GPUnit::UT_SPINBUTTON:
				cMeth=GPSpinButton::cArrMethods;
				nMeth=GPSpinButton::uNMethods;
				break;
			case GPUnit::UT_BUTTON:
				cMeth=GPButton::cArrMethods;
				nMeth=GPButton::uNMethods;
				break;
			case GPUnit::UT_ANIBUTTON:
				cMeth=GPAniButton::cArrMethods;
				nMeth=GPAniButton::uNMethods;
				break;
			case GPUnit::UT_BBUTTON:
				cMeth=GPBButton::cArrMethods;
				nMeth=GPBButton::uNMethods;
				break;
			case GPUnit::UT_STATIC:
				cMeth=GPStatic::cArrMethods;
				nMeth=GPStatic::uNMethods;
				break;
			case GPUnit::UT_ANISTATIC:
				cMeth=GPAniStatic::cArrMethods;
				nMeth=GPAniStatic::uNMethods;
				break;
			case GPUnit::UT_EDIT:
				cMeth=GPEdit::cArrMethods;
				nMeth=GPEdit::uNMethods;
				break;
			case GPUnit::UT_LISTBOX:
				cMeth=GPListBox::cArrMethods;
				nMeth=GPListBox::uNMethods;
				break;
			case GPUnit::UT_COMBOBOX:
				cMeth=GPComboBox::cArrMethods;
				nMeth=GPComboBox::uNMethods;
				break;
			case GPUnit::UT_COMBOBOXEX:
				cMeth=GPComboBoxEx::cArrMethods;
				nMeth=GPComboBoxEx::uNMethods;
				break;
			case GPUnit::UT_SCROLLBAR:
				cMeth=GPScrollBar::cArrMethods;
				nMeth=GPScrollBar::uNMethods;
				break;
			case GPUnit::UT_PROGRESS:
				cMeth=GPProgress::cArrMethods;
				nMeth=GPProgress::uNMethods;
				break;
			case GPUnit::UT_ANIMAT:
				cMeth=GPAnimate::cArrMethods;
				nMeth=GPAnimate::uNMethods;
				break;
			case GPUnit::UT_CHECKLISTBOX:
				cMeth=GPChLBox::cArrMethods;
				nMeth=GPChLBox::uNMethods;
				break;
			case GPUnit::UT_DRAGLISTBOX:
				cMeth=GPDrLBox::cArrMethods;
				nMeth=GPDrLBox::uNMethods;
				break;
			case GPUnit::UT_LISTCTRL:
				cMeth=GPListCtr::cArrMethods;
				nMeth=GPListCtr::uNMethods;
				break;
			case GPUnit::UT_REBARCTRL:
				cMeth=GPReBarCtrl::cArrMethods;
				nMeth=GPReBarCtrl::uNMethods;
				break;
			case GPUnit::UT_REBAR:
				cMeth=GPReBar::cArrMethods;
				nMeth=GPReBar::uNMethods;
				break;
			case GPUnit::UT_STATUSBARCTRL:
				cMeth=GPStatusBarCtrl::cArrMethods;
				nMeth=GPStatusBarCtrl::uNMethods;
				break;
			case GPUnit::UT_TOOLBARCTRL:
				cMeth=GPToolBarCtrl::cArrMethods;
				nMeth=GPToolBarCtrl::uNMethods;
				break;
			case GPUnit::UT_STATUSBAR:
				cMeth=GPStatusBar::cArrMethods;
				nMeth=GPStatusBar::uNMethods;
				break;
			case GPUnit::UT_TOOLBAR:
				cMeth=GPToolBar::cArrMethods;
				nMeth=GPToolBar::uNMethods;
				break;
			case GPUnit::UT_DIALOGBAR:
				cMeth=GPDialogBar::cArrMethods;
				nMeth=GPDialogBar::uNMethods;
				break;
			case GPUnit::UT_DRAW:
				cMeth=GPDrawWnd::cArrMethods;
				nMeth=GPDrawWnd::uNMethods;
				break;
			case GPUnit::UT_FLEXGRID:
				cMeth=GPCMSFlexGrid::cArrMethods;
				nMeth=GPCMSFlexGrid::uNMethods;
				break;
			case GPUnit::UT_WEBBROWSER:
				cMeth=GPWebBrowser2::cArrMethods;
				nMeth=GPWebBrowser2::uNMethods;
				break;
			case GPUnit::UT_CONTROL:
				cMeth=GP_Control::cArrMethods;
				nMeth=GP_Control::uNMethods;
				break;
		}
		for(i=0;i<nMeth;i++)
		{
			int tmpNitem=MetCombo->AddString(cMeth[i]);
			MetCombo->SetItemData(tmpNitem,i);
		}

		if (iGPU && iGPU->UnitHWND)
		{
			CString tmps;
			AX_NAMES anm;
			anm.cbSize=sizeof(AX_NAMES);
			anm.NamesArr=tmps.AllocSysString();
			anm.DescriptionsArr=tmps.AllocSysString();
			switch(GPUnit::auTypeUnit[iUnitType])
			{
			case GPUnit::UT_CONTROL:
				::SendMessage(iGPU->UnitHWND,GPM_AX_GETMETHODS,0,(LPARAM)(&anm));
				break;
			}
			tmps=anm.NamesArr;
			CString tmpMeth;
			i=0;
			while((tmpMeth=ExtractField(tmps,i+1,"\x1"))!="")
			{
				int tmpNitem=MetCombo->AddString(tmpMeth);
				MetCombo->SetItemData(tmpNitem,i++);
			}
			::SysFreeString(anm.DescriptionsArr);
			::SysFreeString(anm.NamesArr);
		}
	}

}

void CDlgMethods::GetParamStr(int UnitType, UINT MetData,CString &MetName,CString &MetParam)
{
		MetName="";
		MetParam="";
		int nUmParam=MetData&0xFFFF;
		if ((MetData&0xFFFF0000)==0xFFFF0000)
		{//WinMethod
			MetName=GPUnit::cArrMethods[nUmParam];
			MetParam=GPUnit::cArrMethodsParams[nUmParam];
		}
		else
		if ((MetData&0x8FFF0000)==0x8FFF0000)
		{//WinMethod
			MetName=CGPToolTipCtrl::cArrToolTipMethods[nUmParam];
			MetParam=CGPToolTipCtrl::cArrToolTipMethodsParams[nUmParam];
		}
		else
		if ((MetData&0x4FFF0000)==0x4FFF0000)
		{//WinMethod
			MetName=CGPToolTipCtrl::cArrToolTipMethodsAll[nUmParam];
			MetParam=CGPToolTipCtrl::cArrToolTipMethodsParamsAll[nUmParam];
		}
		else
		{
			if ((MetData&0xFFFF0000)!=0)
			{//BaseClassMethod
				switch(GPUnit::auTypeUnit[MetData/0x10000])
				{
					case GPUnit::UT_BUTTON:
						MetName=GPButton::cArrMethods[nUmParam];
						MetParam=GPButton::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_STATIC:
						MetName=GPStatic::cArrMethods[nUmParam];
						MetParam=GPStatic::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_STATUSBAR:
					case GPUnit::UT_TOOLBAR:
					case GPUnit::UT_DIALOGBAR:
					case GPUnit::UT_REBAR:
						MetName=GPUnit::cArrControlBarMethod[nUmParam];
						MetParam=GPUnit::cArrControlBarMethodParams[nUmParam];
						break;
				}
			}
			else
			{
				switch(GPUnit::auTypeUnit[UnitType])
				{
					case GPUnit::UT_MAINDLGSCR:
						break;
					case GPUnit::UT_DATETIMECTRL:
						MetName=GPDateTimeCtrl::cArrMethods[nUmParam];
						MetParam=GPDateTimeCtrl::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_DLGBAR:
						MetName=GPDlgBar::cArrMethods[nUmParam];
						MetParam=GPDlgBar::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_FRAMEBAR:
						MetName=GPFrameBar::cArrMethods[nUmParam];
						MetParam=GPFrameBar::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_RTF:
						MetName=GP_RTF::cArrMethods[nUmParam];
						MetParam=GP_RTF::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_EDITOR:
						MetName=GPScintilla::cArrMethods[nUmParam];
						MetParam=GPScintilla::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_TREECTRL:
						MetName=GPTree::cArrMethods[nUmParam];
						MetParam=GPTree::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_HEADER:
						MetName=GPHeader::cArrMethods[nUmParam];
						MetParam=GPHeader::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_SLIDER:
						MetName=GPSlider::cArrMethods[nUmParam];
						MetParam=GPSlider::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_TABCTRL:
						MetName=GPTabCtrl::cArrMethods[nUmParam];
						MetParam=GPTabCtrl::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_SPINBUTTON:
						MetName=GPSpinButton::cArrMethods[nUmParam];
						MetParam=GPSpinButton::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_BUTTON:
						MetName=GPButton::cArrMethods[nUmParam];
						MetParam=GPButton::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_ANIBUTTON:
						MetName=GPAniButton::cArrMethods[nUmParam];
						MetParam=GPAniButton::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_BBUTTON:
						MetName=GPBButton::cArrMethods[nUmParam];
						MetParam=GPBButton::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_STATIC:
						MetName=GPStatic::cArrMethods[nUmParam];
						MetParam=GPStatic::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_ANISTATIC:
						MetName=GPAniStatic::cArrMethods[nUmParam];
						MetParam=GPAniStatic::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_EDIT:
						MetName=GPEdit::cArrMethods[nUmParam];
						MetParam=GPEdit::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_LISTBOX:
						MetName=GPListBox::cArrMethods[nUmParam];
						MetParam=GPListBox::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_COMBOBOX:
						MetName=GPComboBox::cArrMethods[nUmParam];
						MetParam=GPComboBox::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_COMBOBOXEX:
						MetName=GPComboBoxEx::cArrMethods[nUmParam];
						MetParam=GPComboBoxEx::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_SCROLLBAR:
						MetName=GPScrollBar::cArrMethods[nUmParam];
						MetParam=GPScrollBar::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_PROGRESS:
						MetName=GPProgress::cArrMethods[nUmParam];
						MetParam=GPProgress::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_ANIMAT:
						MetName=GPAnimate::cArrMethods[nUmParam];
						MetParam=GPAnimate::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_CHECKLISTBOX:
						MetName=GPChLBox::cArrMethods[nUmParam];
						MetParam=GPChLBox::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_DRAGLISTBOX:
						MetName=GPDrLBox::cArrMethods[nUmParam];
						MetParam=GPDrLBox::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_LISTCTRL:
						MetName=GPListCtr::cArrMethods[nUmParam];
						MetParam=GPListCtr::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_REBARCTRL:
						MetName=GPReBarCtrl::cArrMethods[nUmParam];
						MetParam=GPReBarCtrl::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_REBAR:
						MetName=GPReBar::cArrMethods[nUmParam];
						MetParam=GPReBar::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_STATUSBARCTRL:
						MetName=GPStatusBarCtrl::cArrMethods[nUmParam];
						MetParam=GPStatusBarCtrl::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_TOOLBARCTRL:
						MetName=GPToolBarCtrl::cArrMethods[nUmParam];
						MetParam=GPToolBarCtrl::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_STATUSBAR:
						MetName=GPStatusBar::cArrMethods[nUmParam];
						MetParam=GPStatusBar::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_TOOLBAR:
						MetName=GPToolBar::cArrMethods[nUmParam];
						MetParam=GPToolBar::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_DIALOGBAR:
						MetName=GPDialogBar::cArrMethods[nUmParam];
						MetParam=GPDialogBar::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_DRAW:
						MetName=GPDrawWnd::cArrMethods[nUmParam];
						MetParam=GPDrawWnd::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_FLEXGRID:
						MetName=GPCMSFlexGrid::cArrMethods[nUmParam];
						MetParam=GPCMSFlexGrid::cArrMethodsParams[nUmParam];
						break;
					case GPUnit::UT_WEBBROWSER:
						MetName=GPWebBrowser2::cArrMethods[nUmParam];
						MetParam=GPWebBrowser2::cArrMethodsParams[nUmParam];
						break;
				}
			}
		}
}


void CDlgMethods::OnChangeMethod()
{
	m_Edit.SetWindowText("");
	int UnitType=m_ComboType.GetCurSel();
	if (UnitType!=CB_ERR)  UnitType=m_ComboType.GetItemData(UnitType);
	else return;

	int nItem=m_ComboMethod.GetCurSel();
	int ChParam=m_CheckParam.GetState()&0x3;
	CString MetName;
	CString MetParam;

	if (nItem!=CB_ERR)
	{
		CString str;
		UINT iData=m_ComboMethod.GetItemData(nItem);
		GetParamStr(UnitType,iData,MetName,MetParam);

		if ((iData&0xFFFF0000)==0xFFFF0000)
		{//WinMethod
			str.Format("CALL GP.Dlg%sSub(IdDlg%s,'%s",UnitType==0?"":"Object",UnitType==0?"":",IdObj",(LPCTSTR)MetName);
			if (MetParam.GetLength()>0 && ChParam!=0) str+=" "+MetParam;
			str+="')";
		}
		else
		{
			if (MetName.GetLength()>0)
			{
				str="CALL GP.DlgObjectSub(IdDlg,IdObj,'"+MetName;
				if (MetParam.GetLength()>0 && ChParam!=0) str+=" "+MetParam;
				str+="')";
			}

		}
		m_Edit.SetWindowText(str);
	}

}

BOOL CDlgMethods::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if ((wParam!=1 && wParam!=2) || lParam!=0)
		return CDialog::OnCommand(wParam, lParam);

	if (wParam==1 || wParam==2)
		m_pParentWnd->SendMessage(GPN_CLOSEDLGMETHODS,(WPARAM)this);

	return TRUE;
}

void CDlgMethods::OnClose()
{
	m_pParentWnd->SendMessage(GPN_CLOSEDLGMETHODS,(WPARAM)this);
}

void CDlgMethods::OnCheckParam()
{
	OnChangeMethod();
}

void CDlgMethods::OnButtonBuff()
{
	CString str;
	m_Edit.GetWindowText(str);
	StringToClip(str);
}

void CDlgMethods::OnButtonInsert()
{
	CString str;
	m_Edit.GetWindowText(str);
	m_Comm.GPSendBlock(str,str.GetLength());
}
