// GPColorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GP_term.h"
#include "GPColorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGPDlgColor127 dialog

const char *CGPDlgColor127::aColorName[8]={"BLACK","RED","BROWN","MAGENTA","GREEN","CYAN","BLUE","WHITE",};
const char *CGPDlgColor127::aIntensityName[2]={"FULL","HALF",};
const char *CGPDlgColor127::aForeBackName[2]={"FOREGROUND","BACKGROUND",};

CGPDlgColor127::CGPDlgColor127(CWnd* pParent /*=NULL*/)
	: CDialog(CGPDlgColor127::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGPDlgColor127)
	//}}AFX_DATA_INIT
	cur_cF=0;
	cur_cB=0;
	CString inn;
#ifdef BRIZ
	OldFileName="BRIZ.RGB";
#else
	OldFileName="GP_TERM.RGB";
#endif

	inn=AfxGetApp()->GetProfileString(GPC.cs_RegTermViewSetName, "RGB_cRf","1315858 255 65535 16711935 65280 16776960 16711680 16777215 0 150 46003 10027158 39168 10066176 10027008 12170936");
	m_LastScanf=sscanf(inn,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",cF,cF+1,cF+2,cF+3,cF+4,cF+5,cF+6,cF+7,cF+8,cF+9,cF+10,cF+11,cF+12,cF+13,cF+14,cF+15);
	inn=AfxGetApp()->GetProfileString(GPC.cs_RegTermViewSetName, "RGB_cRb","0 242 61680 16122100 60928 14336256 15400960 15129549");
	m_LastScanf=sscanf(inn,"%d %d %d %d %d %d %d %d",cB,cB+1,cB+2,cB+3,cB+4,cB+5,cB+6,cB+7);

}


void CGPDlgColor127::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGPDlgColor127)
	DDX_Control(pDX, IDC_RADIO9, m_r9);
	DDX_Control(pDX, IDC_RADIO8, m_r8);
	DDX_Control(pDX, IDC_RADIO7, m_r7);
	DDX_Control(pDX, IDC_RADIO6, m_r6);
	DDX_Control(pDX, IDC_RADIO5, m_r5);
	DDX_Control(pDX, IDC_RADIO4, m_r4);
	DDX_Control(pDX, IDC_RADIO3, m_r3);
	DDX_Control(pDX, IDC_RADIO24, m_r24);
	DDX_Control(pDX, IDC_RADIO23, m_r23);
	DDX_Control(pDX, IDC_RADIO22, m_r22);
	DDX_Control(pDX, IDC_RADIO21, m_r21);
	DDX_Control(pDX, IDC_RADIO20, m_r20);
	DDX_Control(pDX, IDC_RADIO2, m_r2);
	DDX_Control(pDX, IDC_RADIO19, m_r19);
	DDX_Control(pDX, IDC_RADIO18, m_r18);
	DDX_Control(pDX, IDC_RADIO17, m_r17);
	DDX_Control(pDX, IDC_RADIO16, m_r16);
	DDX_Control(pDX, IDC_RADIO15, m_r15);
	DDX_Control(pDX, IDC_RADIO14, m_r14);
	DDX_Control(pDX, IDC_RADIO13, m_r13);
	DDX_Control(pDX, IDC_RADIO12, m_r12);
	DDX_Control(pDX, IDC_RADIO11, m_r11);
	DDX_Control(pDX, IDC_RADIO10, m_r10);
	DDX_Control(pDX, IDC_RADIO1, m_r1);
	DDX_Control(pDX, IDC_SLIDER10, m_BlueSpinFon);
	DDX_Control(pDX, IDC_SLIDER9, m_GreenSpinFon);
	DDX_Control(pDX, IDC_SLIDER8, m_RedSpinFon);
	DDX_Control(pDX, IDC_SLIDER7, m_BlueSpin);
	DDX_Control(pDX, IDC_SLIDER6, m_GreenSpin);
	DDX_Control(pDX, IDC_SLIDER5, m_RedSpin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGPDlgColor127, CDialog)
	//{{AFX_MSG_MAP(CGPDlgColor127)
	ON_WM_PAINT()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER5, OnReleasedcaptureSlider5)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER6, OnReleasedcaptureSlider6)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER7, OnReleasedcaptureSlider7)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER8, OnReleasedcaptureSlider8)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER10, OnReleasedcaptureSlider10)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER9, OnReleasedcaptureSlider9)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO10, OnRadio10)
	ON_BN_CLICKED(IDC_RADIO11, OnRadio11)
	ON_BN_CLICKED(IDC_RADIO12, OnRadio12)
	ON_BN_CLICKED(IDC_RADIO13, OnRadio13)
	ON_BN_CLICKED(IDC_RADIO14, OnRadio14)
	ON_BN_CLICKED(IDC_RADIO15, OnRadio15)
	ON_BN_CLICKED(IDC_RADIO16, OnRadio16)
	ON_BN_CLICKED(IDC_RADIO17, OnRadio17)
	ON_BN_CLICKED(IDC_RADIO18, OnRadio18)
	ON_BN_CLICKED(IDC_RADIO19, OnRadio19)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO20, OnRadio20)
	ON_BN_CLICKED(IDC_RADIO21, OnRadio21)
	ON_BN_CLICKED(IDC_RADIO22, OnRadio22)
	ON_BN_CLICKED(IDC_RADIO23, OnRadio23)
	ON_BN_CLICKED(IDC_RADIO24, OnRadio24)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
	ON_BN_CLICKED(IDC_RADIO8, OnRadio8)
	ON_BN_CLICKED(IDC_RADIO9, OnRadio9)
	ON_BN_CLICKED(IDC_BUTTONINVERT, OnButtoninvert)
	ON_BN_CLICKED(IDC_BUTTONDEFAULT, OnButtondefault)
	ON_BN_CLICKED(IDC_BUTTONLOAD, OnButtonload)
	ON_BN_CLICKED(IDC_BUTTONSAVE, OnButtonsave)
	ON_BN_CLICKED(IDC_BUTTONBKGDLG, OnButtonbkgdlg)
	ON_BN_CLICKED(IDC_BUTTONFRGDLG, OnButtonfrgdlg)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER5, OnCustomdrawSlider5)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER6, OnCustomdrawSlider6)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER7, OnCustomdrawSlider7)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER8, OnCustomdrawSlider8)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER9, OnCustomdrawSlider9)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER10, OnCustomdrawSlider10)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGPDlgColor127 message handlers

BOOL CGPDlgColor127::OnInitDialog() 
{
	CDialog::OnInitDialog();

	mbtF[0 ]=&m_r1 ;
	mbtF[1 ]=&m_r2 ;
	mbtF[2 ]=&m_r3 ;
	mbtF[3 ]=&m_r4 ;
	mbtF[4 ]=&m_r5 ;
	mbtF[5 ]=&m_r6 ;
	mbtF[6 ]=&m_r7 ;
	mbtF[7 ]=&m_r8 ;
	mbtF[8 ]=&m_r9 ;
	mbtF[9 ]=&m_r10;
	mbtF[10]=&m_r11;
	mbtF[11]=&m_r12;
	mbtF[12]=&m_r13;
	mbtF[13]=&m_r14;
	mbtF[14]=&m_r15;
	mbtF[15]=&m_r16;

	mbtB[0]=&m_r17;
	mbtB[1]=&m_r18;
	mbtB[2]=&m_r19;
	mbtB[3]=&m_r20;
	mbtB[4]=&m_r21;
	mbtB[5]=&m_r22;
	mbtB[6]=&m_r23;
	mbtB[7]=&m_r24;


	m_BlueSpin.SetRange	( 0, 255,TRUE);
	m_GreenSpin.SetRange( 0, 255,TRUE);
	m_RedSpin.SetRange	( 0, 255,TRUE);
	m_BlueSpinFon.SetRange	( 0, 255,TRUE);
	m_GreenSpinFon.SetRange	( 0, 255,TRUE);
	m_RedSpinFon.SetRange	( 0, 255,TRUE);
	GPSetCheck();
	return TRUE;
}

void CGPDlgColor127::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	UINT i,j;
	UINT oldcolor=dc.GetTextColor();
	UINT oldBkcolor=dc.GetBkColor();

	for(i=0;i<16;i++)
		for(j=0;j<8;j++)
		{
			int x=j*20+72;
			int y=33+i*11+(i/8)*12;
			if (i==cur_cF && j==cur_cB)
			{
				CRect e(x-1,y-1,12,10);
				MapDialogRect(&e);
				dc.FillSolidRect(e.left,e.top,e.right,e.bottom,RGB(0,0,0));
			}
			dc.SetTextColor(cF[i]);
			dc.SetBkColor(cB[j]);
			CRect et(x,y,x+1,y+1);
			MapDialogRect(&et);
			dc.TextOut(et.left,et.top, " @ ",3);
		}

	dc.SetTextColor(oldcolor);
	dc.SetBkColor(oldBkcolor);
}

void CGPDlgColor127::OnOK() 
{
	CString inn; 
	inn.Format("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",cF[0],cF[1],cF[2],cF[3],cF[4],cF[5],cF[6],cF[7],cF[8],cF[9],cF[10],cF[11],cF[12],cF[13],cF[14],cF[15]);
	AfxGetApp()->WriteProfileString(GPC.cs_RegTermViewSetName, "RGB_cRf",inn);
	inn.Format("%d %d %d %d %d %d %d %d",cB[0],cB[1],cB[2],cB[3],cB[4],cB[5],cB[6],cB[7]);
	AfxGetApp()->WriteProfileString(GPC.cs_RegTermViewSetName, "RGB_cRb",inn);
	CDialog::OnOK();
}

void CGPDlgColor127::OnReleasedcaptureSlider5(NMHDR* pNMHDR, LRESULT* pResult) 
{
	cF[cur_cF]&=RGB(0,255,255);
	cF[cur_cF]|=m_RedSpin.GetPos();
	*pResult = 0;
	SetSpinners();
}

void CGPDlgColor127::OnReleasedcaptureSlider6(NMHDR* pNMHDR, LRESULT* pResult) 
{
	cF[cur_cF]&=RGB(255,0,255);
	cF[cur_cF]|=m_GreenSpin.GetPos()*256;
	*pResult = 0;
	SetSpinners();
}

void CGPDlgColor127::OnReleasedcaptureSlider7(NMHDR* pNMHDR, LRESULT* pResult) 
{
	cF[cur_cF]&=RGB(255,255,0);
	cF[cur_cF]|=m_BlueSpin.GetPos()*256*256;
	*pResult = 0;
	SetSpinners();
}

void CGPDlgColor127::OnReleasedcaptureSlider8(NMHDR* pNMHDR, LRESULT* pResult) 
{
	cB[cur_cB]&=RGB(0,255,255);
	cB[cur_cB]|=m_RedSpinFon.GetPos();
	*pResult = 0;
	SetSpinners();
}

void CGPDlgColor127::OnReleasedcaptureSlider9(NMHDR* pNMHDR, LRESULT* pResult) 
{
	cB[cur_cB]&=RGB(255,0,255);
	cB[cur_cB]|=m_GreenSpinFon.GetPos()*256;
	*pResult = 0;
	SetSpinners();
}

void CGPDlgColor127::OnReleasedcaptureSlider10(NMHDR* pNMHDR, LRESULT* pResult) 
{
	cB[cur_cB]&=RGB(255,255,0);
	cB[cur_cB]|=m_BlueSpinFon.GetPos()*256*256;
	*pResult = 0;
	SetSpinners();
}

void CGPDlgColor127::SetSpinners(DWORD iFlag)
{
	CString tmp;
#ifdef RUS
	tmp.Format("Красный %d",cF[cur_cF]%256);
		SetDlgItemText(IDC_STATIC_RED ,tmp);
	tmp.Format("Зеленый %d",(cF[cur_cF]/256)%256);
		SetDlgItemText(IDC_STATIC_GREEN,tmp);
	tmp.Format("Синий %d",(cF[cur_cF]/256/256)%256);
		SetDlgItemText(IDC_STATIC_BLUE,tmp);
	tmp.Format("Красный %d", cB[cur_cB]%256);
		SetDlgItemText(IDC_STATIC_RED2,tmp);
	tmp.Format("Зеленый %d",(cB[cur_cB]/256)%256);
		SetDlgItemText(IDC_STATIC_GREEN2,tmp);
	tmp.Format("Синий %d",(cB[cur_cB]/256/256)%256);
		SetDlgItemText(IDC_STATIC_BLUE2,tmp);
#else
	tmp.Format("Red %d",cF[cur_cF]%256);
		SetDlgItemText(IDC_STATIC_RED ,tmp);
	tmp.Format("Green %d",(cF[cur_cF]/256)%256);
		SetDlgItemText(IDC_STATIC_GREEN,tmp);
	tmp.Format("Blue %d",(cF[cur_cF]/256/256)%256);
		SetDlgItemText(IDC_STATIC_BLUE,tmp);
	tmp.Format("Red %d", cB[cur_cB]%256);
		SetDlgItemText(IDC_STATIC_RED2,tmp);
	tmp.Format("Green %d",(cB[cur_cB]/256)%256);
		SetDlgItemText(IDC_STATIC_GREEN2,tmp);
	tmp.Format("Blue %d",(cB[cur_cB]/256/256)%256);
		SetDlgItemText(IDC_STATIC_BLUE2,tmp);
#endif
	if (!iFlag)
	{
		m_RedSpin.		SetPos	( cF[cur_cF]%256);
		m_GreenSpin.	SetPos	((cF[cur_cF]/256)%256);
		m_BlueSpin.		SetPos	((cF[cur_cF]/256/256)%256);
		m_RedSpinFon.	SetPos	( cB[cur_cB]%256);
		m_GreenSpinFon.	SetPos	((cB[cur_cB]/256)%256);
		m_BlueSpinFon.	SetPos	((cB[cur_cB]/256/256)%256);
		InvWorkArea();
	}
	else 
	{
		RECT re={72,43,352,360};
		InvalidateRect(&re, FALSE);
	}
}


void CGPDlgColor127::InvWorkArea()
{
	Invalidate();
}

void CGPDlgColor127::OnRadio1() 
{	cur_cF=0;GPSetCheck();}

void CGPDlgColor127::OnRadio2() 
{	cur_cF=1;GPSetCheck();}

void CGPDlgColor127::OnRadio3() 
{	cur_cF=2;GPSetCheck();}

void CGPDlgColor127::OnRadio4() 
{	cur_cF=3;GPSetCheck();}

void CGPDlgColor127::OnRadio5() 
{	cur_cF=4;GPSetCheck();}

void CGPDlgColor127::OnRadio6() 
{	cur_cF=5;GPSetCheck();}

void CGPDlgColor127::OnRadio7() 
{	cur_cF=6;GPSetCheck();}

void CGPDlgColor127::OnRadio8()
{	cur_cF=7;GPSetCheck();}

void CGPDlgColor127::OnRadio9() 
{	cur_cF=8;GPSetCheck();}

void CGPDlgColor127::OnRadio10() 
{	cur_cF=9;GPSetCheck();}

void CGPDlgColor127::OnRadio11() 
{	cur_cF=10;GPSetCheck();}

void CGPDlgColor127::OnRadio12() 
{	cur_cF=11;GPSetCheck();}

void CGPDlgColor127::OnRadio13() 
{	cur_cF=12;GPSetCheck();}

void CGPDlgColor127::OnRadio14() 
{	cur_cF=13;GPSetCheck();}

void CGPDlgColor127::OnRadio15() 
{	cur_cF=14;GPSetCheck();}

void CGPDlgColor127::OnRadio16() 
{	cur_cF=15;GPSetCheck();}

void CGPDlgColor127::OnRadio17() 
{	cur_cB=0;GPSetCheck();}

void CGPDlgColor127::OnRadio18() 
{	cur_cB=1;GPSetCheck();}

void CGPDlgColor127::OnRadio19() 
{	cur_cB=2;GPSetCheck();}

void CGPDlgColor127::OnRadio20() 
{	cur_cB=3;GPSetCheck();}

void CGPDlgColor127::OnRadio21() 
{	cur_cB=4;GPSetCheck();}

void CGPDlgColor127::OnRadio22() 
{	cur_cB=5;GPSetCheck();}

void CGPDlgColor127::OnRadio23() 
{	cur_cB=6;GPSetCheck();}

void CGPDlgColor127::OnRadio24() 
{	cur_cB=7;GPSetCheck();}


void CGPDlgColor127::GPSetCheck()
{
	UINT i;
	for(i=0;i<16;i++) mbtF[i]->SetCheck((i==cur_cF)?1:0); 
	for(i=0;i< 8;i++) mbtB[i]->SetCheck((i==cur_cB)?1:0);
	SetSpinners();
}

void CGPDlgColor127::OnButtoninvert() 
{
	int i;
	for(i=0;i<16;i++)		cF[i]^=0xFFFFFF;
	for(i=0;i<8;i++)		cB[i]^=0xFFFFFF;
	SetSpinners();
}

void CGPDlgColor127::OnButtondefault() 
{
	UINT tmpf[]={4473156,255,65535,16711935,65280,16776960,16711680,16777215,0,150,46003,10027158,39168,10066176,10027008,10066329,};
	UINT tmpb[]={0,242,61680,16122100,60928,15658496,15400960,15789808,};
	int i ;
	for(i = 0 ; i<16; i++)	cF[i]=tmpf[i];
	for(i = 0 ; i<8; i++)	cB[i]=tmpb[i];
	SetSpinners();
}

void CGPDlgColor127::OnButtonload() 
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
	opf.hwndOwner=GPC.m_hViewWnd;
	opf.lpstrFile = new char [5000];
	strcpy(opf.lpstrFile,OldFileName);
	opf.nMaxFile =4900;
	opf.Flags =OFN_DONTADDTORECENT|OFN_HIDEREADONLY|OFN_ENABLESIZING|OFN_EXPLORER|OFN_FILEMUSTEXIST|OFN_LONGNAMES|OFN_NOCHANGEDIR|OFN_PATHMUSTEXIST|OFN_NOCHANGEDIR|OFN_SHOWHELP;
#ifdef RUS
	opf.lpstrFilter="Файл описания цветов(*.RGB)\x0*.RGB\x0";
#else
	opf.lpstrFilter="Color definition file(*.RGB)\x0*.RGB\x0";
#endif
	opf.lpstrDefExt="RGB";

	if (GetOpenFileName(&opf))
	{
		OldFileName=opf.lpstrFile;
		LoadPalette(OldFileName,cF,cB);
	}
	delete[] opf.lpstrFile;

	Invalidate();
}

void CGPDlgColor127::OnButtonsave() 
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
	opf.hwndOwner=GPC.m_hViewWnd;
	opf.lpstrFile = new char [5000];
	strcpy(opf.lpstrFile,OldFileName);
	opf.nMaxFile =4900;
	opf.Flags =OFN_DONTADDTORECENT|OFN_HIDEREADONLY|OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_PATHMUSTEXIST|OFN_NOCHANGEDIR|OFN_SHOWHELP;
#ifdef RUS
	opf.lpstrFilter="Файл описания цветов(*.RGB)\x0*.RGB\x0";
#else
	opf.lpstrFilter="Color definition file(*.RGB)\x0*.RGB\x0";
#endif
	opf.lpstrDefExt="RGB";

	if (GetSaveFileName(&opf))
	{
		OldFileName=opf.lpstrFile;
		FILE *tmp=fopen(OldFileName,"wt");
		if (tmp!=NULL)
		{
			int i,j;
			for(j=0;j<2;j++)
				for(i=0;i<8;i++)
					fprintf(tmp,"%s_%s_%s = %d, %d, %d\n",aForeBackName[0],aIntensityName[j],aColorName[i],GetRValue(cF[i]),GetGValue(cF[i]),GetBValue(cF[i]));

			for(i=0;i<8;i++)
				fprintf(tmp,"%s_%s = %d, %d, %d\n",aForeBackName[1],aColorName[i],GetRValue(cB[i]),GetGValue(cB[i]),GetBValue(cB[i]));
			fclose(tmp);
		}
	}
	delete[] opf.lpstrFile;

}

void CGPDlgColor127::OnButtonbkgdlg() 
{
	CColorDialog dlg (cB[cur_cB],CC_FULLOPEN|CC_ANYCOLOR, this);
	if (dlg.DoModal()==IDOK)
	{
		cB[cur_cB]=dlg.GetColor();
		SetSpinners();
	}
}

void CGPDlgColor127::OnButtonfrgdlg() 
{
	CColorDialog dlg (cF[cur_cF],CC_FULLOPEN|CC_ANYCOLOR, this);
	if (dlg.DoModal()==IDOK)
	{
		cF[cur_cF]=dlg.GetColor();
		SetSpinners();
	}
}

void CGPDlgColor127::OnCustomdrawSlider5(NMHDR* pNMHDR, LRESULT* pResult) 
{
	COLORREF curColor=(cF[cur_cF]&RGB(0,255,255))|RGB(m_RedSpin.GetPos(),0,0);
	if (curColor!=cF[cur_cF])
	{
		cF[cur_cF]=curColor;
		SetSpinners(1);
	}
	*pResult = 0;
}

void CGPDlgColor127::OnCustomdrawSlider6(NMHDR* pNMHDR, LRESULT* pResult) 
{
	COLORREF curColor=(cF[cur_cF]&RGB(255,0,255))|RGB(0,m_GreenSpin.GetPos(),0);
	if (curColor!=cF[cur_cF])
	{
		cF[cur_cF]=curColor;
		SetSpinners(1);
	}
	*pResult = 0;
}

void CGPDlgColor127::OnCustomdrawSlider7(NMHDR* pNMHDR, LRESULT* pResult) 
{
	COLORREF curColor=(cF[cur_cF]&RGB(255,255,0))|RGB(0,0,m_BlueSpin.GetPos());
	if (curColor!=cF[cur_cF])
	{
		cF[cur_cF]=curColor;
		SetSpinners(1);
	}
	*pResult = 0;
}

void CGPDlgColor127::OnCustomdrawSlider8(NMHDR* pNMHDR, LRESULT* pResult) 
{
	COLORREF curColor=(cB[cur_cB]&RGB(0,255,255))|RGB(m_RedSpinFon.GetPos(),0,0);
	if (curColor!=cB[cur_cB])
	{
		cB[cur_cB]=curColor;
		SetSpinners(1);
	}
	*pResult = 0;
}

void CGPDlgColor127::OnCustomdrawSlider9(NMHDR* pNMHDR, LRESULT* pResult) 
{
	COLORREF curColor=(cB[cur_cB]&RGB(255,0,255))|RGB(0,m_GreenSpinFon.GetPos(),0);
	if (curColor!=cB[cur_cB])
	{
		cB[cur_cB]=curColor;
		SetSpinners(1);
	}
	*pResult = 0;
}

void CGPDlgColor127::OnCustomdrawSlider10(NMHDR* pNMHDR, LRESULT* pResult) 
{
	COLORREF curColor=(cB[cur_cB]&RGB(255,255,0))|RGB(0,0,m_BlueSpinFon.GetPos());
	if (curColor!=cB[cur_cB])
	{
		cB[cur_cB]=curColor;
		SetSpinners(1);
	}
	*pResult = 0;
}

