// DlgDrawEdit.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgDrawEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDrawEdit dialog


CDlgDrawEdit::CDlgDrawEdit(GPDrawWnd *iDrawUnit, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDrawEdit::IDD, pParent)
{
	DrawUnit=iDrawUnit;
	DlgAutoSize=NULL;
	//{{AFX_DATA_INIT(CDlgDrawEdit)
	//}}AFX_DATA_INIT
}

CDlgDrawEdit::~CDlgDrawEdit()
{
	if (DlgAutoSize) delete DlgAutoSize;
	DlgAutoSize=NULL;
}


void CDlgDrawEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDrawEdit)
	DDX_Control(pDX, IDC_BUTTONRELOAD, m_BtReload);
	DDX_Control(pDX, IDC_EDITREGION, m_EditRegion);
	DDX_Control(pDX, IDC_EDITURECT, m_EditURect);
	DDX_Control(pDX, IDC_EDITUPOINT, m_EditUPoint);
	DDX_Control(pDX, IDC_EDITINT, m_EditInt);
	DDX_Control(pDX, IDC_EDITDOUBLE, m_EditDouble);
	DDX_Control(pDX, IDC_BUTTON1, m_BtRedraw);
	DDX_Control(pDX, IDC_EDITBRUSH, m_EditBrush);
	DDX_Control(pDX, IDC_EDITPEN, m_EditPen);
	DDX_Control(pDX, IDC_EDITFONT, m_EditFont);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	DDX_Control(pDX, IDC_EDITTEXT, m_EditText);
	DDX_Control(pDX, IDC_EDITRECT, m_EditRect);
	DDX_Control(pDX, IDC_EDITPOINT, m_EditPoint);
	DDX_Control(pDX, IDC_EDITITEMS, m_EditItems);
	DDX_Control(pDX, IDC_EDITICON, m_EditIcon);
	DDX_Control(pDX, IDC_EDITCOLOR, m_EditColor);
	DDX_Control(pDX, IDC_BTCOLOR, m_btColor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDrawEdit, CDialog)
	//{{AFX_MSG_MAP(CDlgDrawEdit)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab)
	ON_BN_CLICKED(IDC_BTCOLOR, OnBtcolor)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonRedraw)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTONRELOAD, OnButtonreload)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDrawEdit message handlers
BOOL CDlgDrawEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	DlgAutoSize=new GP_AutoSizing;
	DlgAutoSize->AddSetMain(this->m_hWnd);
	CRect MinimumRecr;
	GetWindowRect(&MinimumRecr);
	DlgAutoSize->SetMinSize(this->m_hWnd,MinimumRecr.Width(),MinimumRecr.Height());
	DlgAutoSize->AddWnd(m_EditFont.m_hWnd,this->m_hWnd,"NNEE");
	DlgAutoSize->AddWnd(m_EditText.m_hWnd,this->m_hWnd,"NNEE");
	DlgAutoSize->AddWnd(m_EditRect.m_hWnd,this->m_hWnd,"NMEE");
	DlgAutoSize->AddWnd(m_EditPoint.m_hWnd,this->m_hWnd,"NNEM");
	DlgAutoSize->AddWnd(m_EditUPoint.m_hWnd,this->m_hWnd,"NNEM");
	DlgAutoSize->AddWnd(m_EditURect.m_hWnd,this->m_hWnd,"NMEE");
	DlgAutoSize->AddWnd(m_EditItems.m_hWnd,this->m_hWnd,"NNEE");
	DlgAutoSize->AddWnd(m_EditIcon.m_hWnd,this->m_hWnd,"NNEE");
	DlgAutoSize->AddWnd(m_EditColor.m_hWnd,this->m_hWnd,"NNEE");
	DlgAutoSize->AddWnd(m_EditPen.m_hWnd,this->m_hWnd,"NNEE");
	DlgAutoSize->AddWnd(m_EditBrush.m_hWnd,this->m_hWnd,"NNEE");
	DlgAutoSize->AddWnd(m_btColor.m_hWnd,this->m_hWnd,"ENEN");
	DlgAutoSize->AddWnd(m_BtReload.m_hWnd,this->m_hWnd,"EEEE");
	DlgAutoSize->AddWnd(m_BtRedraw.m_hWnd,this->m_hWnd,"EEEE");
	DlgAutoSize->AddWnd(m_Tab.m_hWnd,this->m_hWnd,"NNNE");
	DlgAutoSize->AddWnd(m_EditInt.m_hWnd,this->m_hWnd,"NNEM");
	DlgAutoSize->AddWnd(m_EditDouble.m_hWnd,this->m_hWnd,"NMEE");
	DlgAutoSize->AddWnd(m_EditRegion.m_hWnd,this->m_hWnd,"NNEE");

	SendMessage(EM_LIMITTEXT, 0x7FFF,0);

	m_EditFont.SendMessage(EM_LIMITTEXT, 0x7FFF,0);
	m_EditText.SendMessage(EM_LIMITTEXT, 0x7FFF,0);
	m_EditRect.SendMessage(EM_LIMITTEXT, 0x7FFF,0);
	m_EditURect.SendMessage(EM_LIMITTEXT, 0x7FFF,0);
	m_EditPoint.SendMessage(EM_LIMITTEXT, 0x7FFF,0);
	m_EditUPoint.SendMessage(EM_LIMITTEXT, 0x7FFF,0);
	m_EditInt.SendMessage(EM_LIMITTEXT, 0x7FFF,0);
	m_EditDouble.SendMessage(EM_LIMITTEXT, 0x7FFF,0);
	m_EditItems.SendMessage(EM_LIMITTEXT, 0x7FFF,0);
	m_EditIcon.SendMessage(EM_LIMITTEXT, 0x7FFF,0);
	m_EditColor.SendMessage(EM_LIMITTEXT, 0x7FFF,0);
	m_EditPen.SendMessage(EM_LIMITTEXT, 0x7FFF,0);
	m_EditBrush.SendMessage(EM_LIMITTEXT, 0x7FFF,0);
	m_btColor.SendMessage(EM_LIMITTEXT, 0x7FFF,0);
	m_EditRegion.SendMessage(EM_LIMITTEXT, 0x7FFF,0);
	m_EditItems.SendMessage(EM_LIMITTEXT, 0x7FFF,0);
	m_EditRegion.SendMessage(EM_LIMITTEXT, 0x7FFF,0);

	m_Tab.InsertItem(0,"ITEMS");
	m_Tab.InsertItem(1,"POINT/RECT");
	m_Tab.InsertItem(2,"UPOINT/URECT");
	m_Tab.InsertItem(3,"PEN");
	m_Tab.InsertItem(4,"BRUSH");
	m_Tab.InsertItem(5,"COLOR");
	m_Tab.InsertItem(6,"FONT");
	m_Tab.InsertItem(7,"TEXT");
	m_Tab.InsertItem(8,"INT/DOUBLE");
	m_Tab.InsertItem(9,"ICON");
	m_Tab.InsertItem(10,"REGION");
	m_Tab.SetCurSel(0);
	UpdateTabs();

	ReloadEdit();
	return TRUE;
}

void CDlgDrawEdit::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if (DlgAutoSize && nType!=SIZE_MINIMIZED)
		DlgAutoSize->UpdateSize();
}

void CDlgDrawEdit::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult)
{
	UpdateTabs();
	*pResult = 0;
}


void CDlgDrawEdit::UpdateTabs()
{
	m_btColor.ModifyStyle(0,WS_VISIBLE);

	m_EditFont.		ModifyStyle(WS_VISIBLE, 0);
	m_EditText.		ModifyStyle(WS_VISIBLE, 0);
	m_EditRect.		ModifyStyle(WS_VISIBLE, 0);
	m_EditURect.	ModifyStyle(WS_VISIBLE, 0);
	m_EditPoint.	ModifyStyle(WS_VISIBLE, 0);
	m_EditUPoint.	ModifyStyle(WS_VISIBLE, 0);
	m_EditInt.		ModifyStyle(WS_VISIBLE, 0);
	m_EditDouble.	ModifyStyle(WS_VISIBLE, 0);
	m_EditItems.	ModifyStyle(WS_VISIBLE, 0);
	m_EditIcon.		ModifyStyle(WS_VISIBLE, 0);
	m_EditColor.	ModifyStyle(WS_VISIBLE, 0);
	m_EditPen.		ModifyStyle(WS_VISIBLE, 0);
	m_EditBrush.	ModifyStyle(WS_VISIBLE, 0);
	m_EditRegion.	ModifyStyle(WS_VISIBLE, 0);

	switch(m_Tab.GetCurSel())
	{
	case 0://ITEMS
		m_EditItems.ModifyStyle(0,WS_VISIBLE);
		break;
	case 1://POINT/RECT
		m_EditPoint.ModifyStyle(0,WS_VISIBLE);
		m_EditRect.ModifyStyle(0,WS_VISIBLE);
		m_btColor.ModifyStyle(WS_VISIBLE,0);
		break;
	case 2://UPOINT/URECT
		m_EditUPoint.ModifyStyle(0,WS_VISIBLE);
		m_EditURect.ModifyStyle(0,WS_VISIBLE);
		m_btColor.ModifyStyle(WS_VISIBLE,0);
		break;
	case 3://PEN
		m_EditPen.ModifyStyle(0,WS_VISIBLE);
		break;
	case 4://BRUSH
		m_EditBrush.ModifyStyle(0,WS_VISIBLE);
		break;
	case 5://COLOR
		m_EditColor.ModifyStyle(0,WS_VISIBLE);
		break;
	case 6://FONT
		m_EditFont.ModifyStyle(0,WS_VISIBLE);
		m_btColor.ModifyStyle(WS_VISIBLE,0);
		break;
	case 7://TEXT
		m_EditText.ModifyStyle(0,WS_VISIBLE);
		break;
	case 8://INT/DOUBLE
		m_EditInt.ModifyStyle(0,WS_VISIBLE);
		m_EditDouble.ModifyStyle(0,WS_VISIBLE);
		m_btColor.ModifyStyle(WS_VISIBLE,0);
		break;
	case 9://ICON
		m_EditIcon.ModifyStyle(0,WS_VISIBLE);
	case 10://REGION
		m_EditRegion.ModifyStyle(0,WS_VISIBLE);
		break;
	}
	Invalidate();
}

void CDlgDrawEdit::OnBtcolor()
{
	int R=0,G=0,B=0;
	int StartChar=0;
	int EndChar=0;
	int CurLine=-1;
	char *buff=new char [10000];
	UINT nItem=0x1000000;

	switch(m_Tab.GetCurSel())
	{
	case 0://ITEMS
		break;
	case 3://PEN
		break;
	case 4://BRUSH
		break;
	case 5://COLOR
		m_EditColor.GetSel(StartChar,EndChar);
		CurLine=m_EditColor.LineFromChar(StartChar);
		m_EditColor.GetLine(CurLine,buff,9990);
		m_LastScanf=sscanf(buff,"%d,%d,%d,%d",&nItem,&R,&G,&B);
		StartChar=m_EditColor.LineIndex(CurLine);
		EndChar=m_EditColor.LineIndex(CurLine+1);
		break;
	case 6://FONT
		break;
	case 7://TEXT
		break;
	}


	CColorDialog dlg (RGB(R,G,B),CC_FULLOPEN|CC_ANYCOLOR, this);
	if (dlg.DoModal()==IDOK && CurLine>=0 && nItem<0x100000)
	{
		CString tmp;

		COLORREF clr=dlg.GetColor();
		switch(m_Tab.GetCurSel())
		{
		case 0://ITEMS
		case 3://PEN
		case 7://TEXT
			tmp.Format("%d,%d,%d\r\n",GetRValue(clr),GetGValue(clr),GetBValue(clr));
			StringToClip(tmp);
			break;
		case 4://BRUSH
			break;
		case 5://COLOR
			m_EditColor.SetSel(StartChar,EndChar);
			tmp.Format("%3.3d,%d,%d,%d\r\n",nItem,GetRValue(clr),GetGValue(clr),GetBValue(clr));
			m_EditColor.ReplaceSel(tmp);
			OnButtonRedraw();
			break;
		}

	}

	delete[] buff;
}

void CDlgDrawEdit::OnButtonRedraw()
{
	int nLine=0,i=0;
	char *buff=new char [20000];
	char *buffout=new char [20000];
	int LineLen=0;

	if (m_EditPen.GetModify())
	{
		for(i=0;(UINT)i<DrawUnit->m_nPenArray;i++)
		{
			if ((UINT)i<DrawUnit->m_nPenArray && DrawUnit->m_PenArr[i])
			{
				DrawUnit->m_PenArr[i]->DeleteObject();
				delete DrawUnit->m_PenArr[i];
				DrawUnit->m_PenArr[i]=NULL;
			}
		}
		nLine=m_EditPen.GetLineCount();
		for(i=0;i<nLine;i++)
		{
			*buff=0;
			LineLen=m_EditPen.GetLine(i,buff,19990);
			buff[LineLen]=0;
			if (strlen(buff)>2)
			{
				int dd=-1,rr;
				m_LastScanf=sscanf(buff,"%d,%d,%d",&rr,&rr,&dd);
				sprintf(buffout,"Set%sPen %s",dd==-1?"B":"",buff);
				DrawUnit->DoMethod(buffout,NULL);
			}
		}
	}

	if (m_EditBrush.GetModify())
	{
		for(i=0;(UINT)i<DrawUnit->m_nBrushArray;i++)
			if (DrawUnit->m_BrushArr[i])
			{
				DrawUnit->m_BrushArr[i]->DeleteObject();
				delete DrawUnit->m_BrushArr[i];
				DrawUnit->m_BrushArr[i]=NULL;
			}

		nLine=m_EditBrush.GetLineCount();
		for(i=0;i<nLine;i++)
		{
			*buff=0;
			LineLen=m_EditBrush.GetLine(i,buff,19900);
			buff[LineLen]=0;
			if (strlen(buff)>4)
			{
				sprintf(buffout,"SetBrush %s",buff);
				DrawUnit->DoMethod(buffout,NULL);
			}
		}
	}

	if (m_EditFont.GetModify())
	{
		for(i=0;(UINT)i<DrawUnit->m_nFontArray;i++)
			if (DrawUnit->m_FontArr[i])
			{
				DrawUnit->m_FontArr[i]->DeleteObject();
				delete DrawUnit->m_FontArr[i];
				DrawUnit->m_FontArr[i]=NULL;
			}

		nLine=m_EditFont.GetLineCount();
		for(i=0;i<nLine;i++)
		{
			*buff=0;
			LineLen=m_EditFont.GetLine(i,buff,19900);
			buff[LineLen]=0;
			if (strlen(buff)>4)
			{
				sprintf(buffout,"SetFont %s",buff);
				DrawUnit->DoMethod(buffout,NULL);
			}
		}
	}

	if (m_EditRegion.GetModify())
	{
		for(i=0;(UINT)i<DrawUnit->m_nRgnArray;i++)
			if (DrawUnit->m_RgnArr[i])
			{
				DrawUnit->m_RgnArr[i]->DeleteObject();
				delete DrawUnit->m_RgnArr[i];
				DrawUnit->m_RgnArr[i]=NULL;
			}

		nLine=m_EditRegion.GetLineCount();
		for(i=0;i<nLine;i++)
		{
			*buff=0;
			LineLen=m_EditRegion.GetLine(i,buff,19900);
			buff[LineLen]=0;
			if (strlen(buff)>4)
			{
				sprintf(buffout,"SetRegion %s",buff);
				DrawUnit->DoMethod(buffout,NULL);
			}
		}
	}

	if (m_EditColor.GetModify())
	{
		for(i=0;(UINT)i<DrawUnit->m_nRGBArray;i++)
			DrawUnit->m_RGBArr[i]=0;

		nLine=m_EditColor.GetLineCount();
		for(i=0;i<nLine;i++)
		{
			*buff=0;
			LineLen=m_EditColor.GetLine(i,buff,19900);
			buff[LineLen]=0;
			if (strlen(buff)>4)
			{
				sprintf(buffout,"SetColor %s",buff);
				DrawUnit->DoMethod(buffout,NULL);
			}
		}
	}

	if (m_EditText.GetModify())
	{
		for(i=0;(UINT)i<DrawUnit->m_nStringArray;i++)
			DrawUnit->m_StringArr[i]="";

		nLine=m_EditText.GetLineCount();
		for(i=0;i<nLine;i++)
		{
			*buff=0;
			LineLen=m_EditText.GetLine(i,buff,19900);
			buff[LineLen]=0;
			if (LineLen>2)
			{
				sprintf(buffout,"SetText %s",buff);
				DrawUnit->DoMethod(buffout,NULL);
			}
		}
	}

	if (m_EditPoint.GetModify())
	{
		for(i=0;(UINT)i<DrawUnit->m_nPointArray;i++)
			DrawUnit->m_PointArr[i].x=DrawUnit->m_PointArr[i].y=0;

		nLine=m_EditPoint.GetLineCount();
		for(i=0;i<nLine;i++)
		{
			*buff=0;
			LineLen=m_EditPoint.GetLine(i,buff,19900);
			buff[LineLen]=0;
			if (LineLen>4)
			{
				sprintf(buffout,"SetPoint %s",buff);
				DrawUnit->DoMethod(buffout,NULL);
			}
		}
	}

	if (m_EditRect.GetModify())
	{
		for(i=0;(UINT)i<DrawUnit->m_nRectArray;i++)
			DrawUnit->m_RectArr[i].SetRect(0,0,0,0);

		nLine=m_EditRect.GetLineCount();
		for(i=0;i<nLine;i++)
		{
			*buff=0;
			LineLen=m_EditRect.GetLine(i,buff,19900);
			buff[LineLen]=0;
			if (strlen(buff)>4)
			{
				sprintf(buffout,"SetRect %s",buff);
				DrawUnit->DoMethod(buffout,NULL);
			}
		}
	}

	if (m_EditInt.GetModify())
	{
		for(i=0;(UINT)i<DrawUnit->m_nIntArray;i++)
			DrawUnit->m_IntArr[i]=0;

		nLine=m_EditInt.GetLineCount();
		for(i=0;i<nLine;i++)
		{
			*buff=0;
			LineLen=m_EditInt.GetLine(i,buff,19900);
			buff[LineLen]=0;
			if (strlen(buff)>2)
			{
				sprintf(buffout,"SetInt %s",buff);
				DrawUnit->DoMethod(buffout,NULL);
			}
		}
	}

	if (m_EditDouble.GetModify())
	{
		for(i=0;(UINT)i<DrawUnit->m_nDoubleArray;i++)
			DrawUnit->m_DoubleArr[i]=0;

		nLine=m_EditDouble.GetLineCount();
		for(i=0;i<nLine;i++)
		{
			*buff=0;
			LineLen=m_EditInt.GetLine(i,buff,19900);
			buff[LineLen]=0;
			if (strlen(buff)>2)
			{
				sprintf(buffout,"SetDouble %s",buff);
				DrawUnit->DoMethod(buffout,NULL);
			}
		}
	}

	if (m_EditUPoint.GetModify())
	{
		nLine=m_EditUPoint.GetLineCount();
		for(i=0;i<nLine;i++)
		{
			*buff=0;
			LineLen=m_EditUPoint.GetLine(i,buff,19900);
			buff[LineLen]=0;
			char *pospoint=strchr(buff,',');
			if (pospoint==NULL) pospoint="";

			if (LineLen>4)
			{
				sprintf(buffout,"SetPoint %d%s",-atoi(buff)-1,pospoint);
				DrawUnit->DoMethod(buffout,NULL);
			}
		}
	}

	if (m_EditURect.GetModify())
	{
		nLine=m_EditURect.GetLineCount();
		for(i=0;i<nLine;i++)
		{
			*buff=0;
			LineLen=m_EditURect.GetLine(i,buff,19900);
			buff[LineLen]=0;
			char *pospoint=strchr(buff,',');
			if (pospoint==NULL) pospoint="";
			if (LineLen>4)
			{
				sprintf(buffout,"SetRect %d%s",-atoi(buff)-1,pospoint);
				DrawUnit->DoMethod(buffout,NULL);
			}
		}
	}


	if (m_EditItems.GetModify())
	{
		strcpy(buffout,"DeleteItems");
		DrawUnit->DoMethod(buffout,NULL);
		nLine=m_EditItems.GetLineCount();
		for(i=0;i<nLine;i++)
		{
			*buff=0;
			*((WORD *)buff)=6000;
			LineLen=m_EditItems.GetLine(i,buff,19900);
			buff[LineLen]=0;
			char *postmp=buff;
			while(*postmp!=0 && ((*postmp>='0' && *postmp<='9') || *postmp==' ')) postmp++;
			if (*postmp!=0) *postmp=',';
			if (*postmp!=0)
			{
				*postmp=',';
				sprintf(buffout,"SetItem %s",buff);
				DrawUnit->DoMethod(buffout,NULL);
			}
		}
	}


	delete[] buffout;
	delete[] buff;
	ReloadEdit();
	DrawUnit->Invalidate();
}


void CDlgDrawEdit::ReloadEdit()
{
	CString tmp,tmpout;
	UINT i;
	DWORD cursel;

	cursel=m_EditPoint.GetSel();
	tmpout="";
	for(i=0;i<DrawUnit->m_nPointArray;i++)
	{
		tmp.Format("%3.3d,%d,%d\r\n",i,DrawUnit->m_PointArr[i].x,DrawUnit->m_PointArr[i].y);
		tmpout+=tmp;
	}
	m_EditPoint.SetWindowText(tmpout);
	m_EditPoint.SetModify(0);
	m_EditPoint.SetSel(cursel);

	cursel=m_EditRect.GetSel();
	tmpout="";
	for(i=0;i<DrawUnit->m_nRectArray;i++)
	{
		tmp.Format("%3.3d,%d,%d,%d,%d\r\n",i,DrawUnit->m_RectArr[i].top,DrawUnit->m_RectArr[i].left,DrawUnit->m_RectArr[i].bottom,DrawUnit->m_RectArr[i].right);
		tmpout+=tmp;
	}
	m_EditRect.SetWindowText(tmpout);
	m_EditRect.SetModify(0);
	m_EditRect.SetSel(cursel);

	cursel=m_EditDouble.GetSel();
	tmpout="";
	for(i=0;i<DrawUnit->m_nDoubleArray && i<1000;i++)
	{
		tmp.Format("%3.3d,%lg\r\n",i,DrawUnit->m_DoubleArr[i]);
		tmpout+=tmp;
	}
	m_EditDouble.SetWindowText(tmpout);
	m_EditDouble.SetModify(0);
	m_EditDouble.SetSel(cursel);

	cursel=m_EditUPoint.GetSel();
	tmpout="";
	for(i=0;i<DrawUnit->m_nDoubleArray/2 && i<1000;i++)
	{
		tmp.Format("%3.3d,%d,%d\r\n",i,(int)DrawUnit->m_DoubleArr[i*2],(int)DrawUnit->m_DoubleArr[i*2+1]);
		tmpout+=tmp;
	}
	m_EditUPoint.SetWindowText(tmpout);
	m_EditUPoint.SetModify(0);
	m_EditUPoint.SetSel(cursel);

	cursel=m_EditURect.GetSel();
	tmpout="";
	for(i=0;i<DrawUnit->m_nDoubleArray/4 && i<1000;i++)
	{
		tmp.Format("%3.3d,%d,%d,%d,%d\r\n",i,(int)DrawUnit->m_DoubleArr[i*4],(int)DrawUnit->m_DoubleArr[i*4+1],(int)DrawUnit->m_DoubleArr[i*4+2],(int)DrawUnit->m_DoubleArr[i*4+3]);
		tmpout+=tmp;
	}
	m_EditURect.SetWindowText(tmpout);
	m_EditURect.SetModify(0);
	m_EditURect.SetSel(cursel);

	cursel=m_EditInt.GetSel();
	tmpout="";
	for(i=0;i<DrawUnit->m_nIntArray;i++)
	{
		tmp.Format("%3.3d,%d\r\n",i,DrawUnit->m_IntArr[i]);
		tmpout+=tmp;
	}
	m_EditInt.SetWindowText(tmpout);
	m_EditInt.SetModify(0);
	m_EditInt.SetSel(cursel);

	cursel=m_EditColor.GetSel();
	tmpout="";
	for(i=0;i<DrawUnit->m_nRGBArray;i++)
	{
		tmp.Format("%3.3d,%d,%d,%d\r\n",i,GetRValue(DrawUnit->m_RGBArr[i]),GetGValue(DrawUnit->m_RGBArr[i]),GetBValue(DrawUnit->m_RGBArr[i]));
		tmpout+=tmp;
	}
	m_EditColor.SetWindowText(tmpout);
	m_EditColor.SetModify(0);
	m_EditColor.SetSel(cursel);

	cursel=m_EditText.GetSel();
	tmpout="";
	for(i=0;i<DrawUnit->m_nStringArray;i++)
	{
		tmp.Format("%3.3d,%s\r\n",i,(LPCSTR)DrawUnit->m_StringArr[i]);
		tmpout+=tmp;
	}
	m_EditText.SetWindowText(tmpout);
	m_EditText.SetModify(0);
	m_EditText.SetSel(cursel);

	cursel=m_EditFont.GetSel();
	tmpout="";
	for(i=0;i<DrawUnit->m_nFontArray;i++)
	{
		if (DrawUnit->m_FontArr[i])
			tmp.Format("%3.3d,%s\r\n",i,(LPCSTR)DrawUnit->m_FontArr[i]->CreationString);
		else tmp.Format("%3.3d,\r\n",i);
		tmpout+=tmp;
	}
	m_EditFont.SetWindowText(tmpout);
	m_EditFont.SetModify(0);
	m_EditFont.SetSel(cursel);

	cursel=m_EditRegion.GetSel();
	tmpout="";
	for(i=0;i<DrawUnit->m_nRgnArray;i++)
	{
		if (DrawUnit->m_RgnArr[i])
			tmp.Format("%3.3d,%s\r\n",i,(LPCSTR)DrawUnit->m_RgnArr[i]->CreationString);
		else tmp.Format("%3.3d,\r\n",i);
		tmpout+=tmp;
	}
	m_EditRegion.SetWindowText(tmpout);
	m_EditRegion.SetModify(0);
	m_EditRegion.SetSel(cursel);

	cursel=m_EditPen.GetSel();
	tmpout="";
	for(i=0;i<DrawUnit->m_nPenArray;i++)
	{
		if (DrawUnit->m_PenArr[i])
			tmp.Format("%3.3d,%s\r\n",i,(LPCSTR)DrawUnit->m_PenArr[i]->CreationString);
		else tmp.Format("%3.3d,\r\n",i);
		tmpout+=tmp;
	}
	m_EditPen.SetWindowText(tmpout);
	m_EditPen.SetModify(0);
	m_EditPen.SetSel(cursel);

	cursel=m_EditBrush.GetSel();
	tmpout="";
	for(i=0;i<DrawUnit->m_nBrushArray;i++)
	{
		if (DrawUnit->m_BrushArr[i])
			tmp.Format("%3.3d,%s\r\n",i,(LPCSTR)DrawUnit->m_BrushArr[i]->CreationString);
		else tmp.Format("%3.3d,\r\n",i);
		tmpout+=tmp;
	}
	m_EditBrush.SetWindowText(tmpout);
	m_EditBrush.SetModify(0);
	m_EditBrush.SetSel(cursel);

	cursel=m_EditItems.GetSel();
	tmpout="";
	for(i=0;i<DrawUnit->m_nDraw;i++)
	{
		tmp.Format("%3.3d=%s\r\n",i,(LPCSTR)DrawUnit->m_ArrDrawInitString[i]);
		tmpout+=tmp;
	}
	m_EditItems.SetWindowText(tmpout);
	m_EditItems.SetModify(0);
	m_EditItems.SetSel(cursel);

	cursel=m_EditIcon.GetSel();
	tmpout="";
	for(i=0;i<DrawUnit->m_nIconArray;i++)
	{
		tmp.Format("%3.3d=%s\r\n",i,(LPCSTR)DrawUnit->m_IconArrString[i]);
		tmpout+=tmp;
	}
	m_EditIcon.SetWindowText(tmpout);
	m_EditIcon.SetModify(0);
	m_EditIcon.SetSel(cursel);

}


void CDlgDrawEdit::OnButtonreload()
{
	ReloadEdit();
}
