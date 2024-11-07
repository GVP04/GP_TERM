// DlgEditorColor.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "DlgEditorColor.h"
#include "GPScintilla.h"
#include "GPFontList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEditorColor dialog

#define RGBPALLETESIZE	576

CDlgEditorColor::CDlgEditorColor(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEditorColor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEditorColor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_ColorArr=NULL;
	m_Scintilla=NULL;
	m_nColors=0;


	BYTE m_BIT[1024];
	BYTE m_BIT2[1024];
	UINT k;
	for(k=0;k<1024;k++)
	{
		m_BIT[k]=0;
		m_BIT2[k]=0;
	}

	hiEtalon=::CreateIcon(AfxGetInstanceHandle(),16,16,1,24,m_BIT,m_BIT2);

	iiEtalon.hbmMask=iiEtalon.hbmColor=NULL;
	if (hiEtalon)
		::GetIconInfo(hiEtalon,&iiEtalon);
	iiEtalon.fIcon=TRUE;
	iiEtalon.xHotspot=iiEtalon.yHotspot=4;

	hiRGB=NULL;
	arrRGB=NULL;
	m_bUpdateClr=FALSE;
	m_CurListSel=-1;
}

CDlgEditorColor::~CDlgEditorColor()
{
	if (m_ColorArr) delete[]  m_ColorArr;
	m_nColors=0;
	m_ILMixed.DeleteImageList();
	if (hiEtalon)
		DestroyIcon(hiEtalon);
	hiEtalon=NULL;
	if (iiEtalon.hbmMask)
		::DeleteObject(iiEtalon.hbmMask);
	iiEtalon.hbmMask=NULL;
	if (iiEtalon.hbmColor)
		::DeleteObject(iiEtalon.hbmColor);
	iiEtalon.hbmColor=NULL;
	if (arrRGB) delete[] arrRGB;
	arrRGB=NULL;
	if (hiRGB) DestroyIcon(hiRGB);
	hiRGB=NULL;
}

void CDlgEditorColor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEditorColor)
	DDX_Control(pDX, IDC_STATICRGB, m_StaticRGB);
	DDX_Control(pDX, IDC_SLIDERFRG, m_SliderFrg);
	DDX_Control(pDX, IDC_SLIDERBKG, m_SliderBkg);
	DDX_Control(pDX, IDC_LIST2, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEditorColor, CDialog)
	//{{AFX_MSG_MAP(CDlgEditorColor)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonFont)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnDblclkListStyles)
	ON_WM_SIZE()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERBKG, OnCustomdrawSliderbkg)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERFRG, OnCustomdrawSliderfrg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, OnItemchangedListColors)
	ON_CBN_SELCHANGE(IDC_COMBOFONT, OnSelchangeCombofont)
	ON_BN_CLICKED(IDC_CHECKBOLD, OnCheckbold)
	ON_BN_CLICKED(IDC_CHECKITALIC, OnCheckitalic)
	ON_BN_CLICKED(IDC_CHECKUNDERLINE, OnCheckunderline)
	ON_EN_CHANGE(IDC_EDITCHARSET, OnChangeEditcharset)
	ON_EN_CHANGE(IDC_EDITFONTSIZE, OnChangeEditfontsize)
	ON_BN_CLICKED(IDC_CHECKVISIBLE, OnCheckvisible)
	ON_CBN_SELCHANGE(IDC_COMBOCASE, OnSelchangeCombocase)
	ON_BN_CLICKED(IDC_CHECKHOTSPOT, OnCheckhotspot)
	ON_BN_CLICKED(IDC_CHECKEOLFILLED, OnCheckeolfilled)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEditorColor message handlers

BEGIN_EVENTSINK_MAP(CDlgEditorColor, CDialog)
    //{{AFX_EVENTSINK_MAP(CDlgEditorColor)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


BOOL CDlgEditorColor::OnInitDialog()
{
	CDialog::OnInitDialog();

	HWND tmph;
	AUSI.AddSetMain(m_hWnd);
	CRect re;
	GetWindowRect(&re);
	AUSI.SetMinSize(m_hWnd,re.Width(),re.Height()/2);

	DWORD IDS[23]={
		IDOK,			IDCANCEL,		IDC_APPLY,			IDC_LIST2,		IDC_COMBOFONT,
		IDC_STATICRGB,	IDC_SLIDERFRG,	IDC_SLIDERBKG,		IDC_STATICBKG,	IDC_STATICFRG,
		IDC_STATICFONT,	IDC_STATICCS,	IDC_EDITCHARSET,	IDC_STATICSIZE,	IDC_EDITFONTSIZE,
		IDC_CHECKITALIC,IDC_CHECKBOLD,	IDC_CHECKUNDERLINE,	IDC_CHECKVISIBLE,IDC_CHECKEOLFILLED,
		IDC_CHECKHOTSPOT,IDC_STATICCASE,IDC_COMBOCASE,
	};
	const char *stls[23]={
		"EEEE","EEEE","EEEE","NNEE","ENEN",
		"ENEN","ENEN","ENEN","ENEN","ENEN",
		"ENEN","ENEN","ENEN","ENEN","ENEN",
		"ENEN","ENEN","ENEN","ENEN","ENEN",
		"ENEN","ENEN","ENEN",
	};

	UINT j,nItem;

	for(nItem=0;nItem<23;nItem++)
	{
		tmph=NULL;
		GetDlgItem(IDS[nItem],&tmph);
		if (tmph)
		{
			AUSI.AddWnd(tmph,m_hWnd,stls[nItem]);
			if (IDS[nItem]==IDC_COMBOFONT)
			{
				CGPFontList fl;
				fl.FillComboBox(tmph,GPFL_CLEAR|GPFL_NOSCRIPT);
			}
		}
	}

	::SendMessage(::GetDlgItem(m_hWnd,IDC_COMBOCASE),CB_ADDSTRING,0,(LPARAM)"MIXED");
	::SendMessage(::GetDlgItem(m_hWnd,IDC_COMBOCASE),CB_ADDSTRING,0,(LPARAM)"UPPER");
	::SendMessage(::GetDlgItem(m_hWnd,IDC_COMBOCASE),CB_ADDSTRING,0,(LPARAM)"LOWER");

	m_SliderBkg.SetRange(0,RGBPALLETESIZE-1);
	m_SliderFrg.SetRange(0,RGBPALLETESIZE-1);

	m_StaticRGB.ModifyStyle(0,SS_ICON);

	BYTE *m_BIT=new BYTE [RGBPALLETESIZE*16*4+100];
	BYTE *m_BIT2=new BYTE [RGBPALLETESIZE*16*4+100];
	arrRGB=new BYTE [RGBPALLETESIZE*4];

	int i,k;
	for(k=0;k<RGBPALLETESIZE*16*4;k++)
	{
		m_BIT[k]=0;
		m_BIT2[k]=0xFF;
	}

	BYTE *pos=m_BIT;

	for(j=0;j<RGBPALLETESIZE*16*4;j++)
	{
		m_BIT[j]=0;
		m_BIT2[j]=0;//0xFF;
	}

	int Rd[]={69,6, 0,0, 0,0,69,6,69,6, 0,0, 0,9, 127,-4,   0, 4, 128, 4, 255,-4, 127,-4,   0, 4, 128, 4, 255,-4, 127,-4,   0, 4, 128, 4, };
	int Gd[]={ 0,0,69,6, 0,0,69,6, 0,0,69,6, 0,9,   0, 1,  32, 1,  64, 1,  96, 1, 128, 1, 160, 1, 192, 1, 224, 1, 255,-1, 223,-1, 191,-1, };
	int Bd[]={ 0,0, 0,0,69,6, 0,0,69,6,69,6, 0,9,   0, 2,  64, 2, 128, 2, 192, 2, 255,-2, 191,-2, 127,-2,  63,-2,   0, 2,  64, 2, 128, 2, };

	BYTE *posarrRGB=arrRGB;

	for(k=0;k<16;k++)
	{
	int R=0,G=0,B=0;
	for(i=0;i<18;i++)
		{
				R=Rd[i*2];
				G=Gd[i*2];
				B=Bd[i*2];

		for(j=0;j<32;j++)
			{
				*(pos++)=(BYTE)(B);
				*(pos++)=(BYTE)(G);
				*(pos++)=(BYTE)(R);
//				*(pos++)=255;

				if (k==0)
				{
					*(posarrRGB++)=(BYTE)(B);
					*(posarrRGB++)=(BYTE)(G);
					*(posarrRGB++)=(BYTE)(R);
				}

				if ((R+=Rd[i*2+1])>255) R=255;
				if ((G+=Gd[i*2+1])>255) G=255;
				if ((B+=Bd[i*2+1])>255) B=255;
				if (R<0) R=0;
				if (G<0) G=0;
				if (B<0) B=0;

			}
		}
	}

	ICONINFO iiTmpCreate={0};
	HDC mdc=::GetDC(m_hWnd);
	iiTmpCreate.hbmMask=CreateCompatibleBitmap(mdc,RGBPALLETESIZE,16);
	iiTmpCreate.hbmColor=CreateCompatibleBitmap(mdc,RGBPALLETESIZE,16);
	iiTmpCreate.fIcon=TRUE;
	iiTmpCreate.xHotspot=iiTmpCreate.yHotspot=4;

	BITMAPINFO lpbmi={0};
	lpbmi.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	lpbmi.bmiHeader.biWidth=RGBPALLETESIZE;
	lpbmi.bmiHeader.biHeight=16;
	lpbmi.bmiHeader.biPlanes=1;
	lpbmi.bmiHeader.biBitCount=24;
	lpbmi.bmiHeader.biCompression=BI_RGB;
	lpbmi.bmiHeader.biSizeImage=0;
	lpbmi.bmiHeader.biXPelsPerMeter=0;
	lpbmi.bmiHeader.biYPelsPerMeter=0;
	lpbmi.bmiHeader.biClrUsed=0;
	lpbmi.bmiHeader.biClrImportant=0;

	SetDIBits(
	  mdc,
	  iiTmpCreate.hbmMask,	// handle to bitmap
	  0,					// starting scan line
	  RGBPALLETESIZE,		// number of scan lines
	  (VOID *)m_BIT2,		// array of bitmap bits
	  &lpbmi,				// bitmap data
	  DIB_RGB_COLORS		// type of color indexes to use
	);

	SetDIBits(
	  mdc,
	  iiTmpCreate.hbmColor,	// handle to bitmap
	  0,					// starting scan line
	  RGBPALLETESIZE,		// number of scan lines
	  (VOID *)m_BIT,		// array of bitmap bits
	  &lpbmi,				// bitmap data
	  DIB_RGB_COLORS		// type of color indexes to use
	);

	::ReleaseDC(m_hWnd,mdc);

	hiRGB=::CreateIconIndirect(&iiTmpCreate);

	m_StaticRGB.SetIcon(hiRGB);

	if (iiTmpCreate.hbmMask)
		::DeleteObject(iiTmpCreate.hbmMask);
	iiTmpCreate.hbmMask=NULL;
	if (iiTmpCreate.hbmColor)
		::DeleteObject(iiTmpCreate.hbmColor);
	iiTmpCreate.hbmColor=NULL;

	delete[] m_BIT;
	delete[] m_BIT2;


	m_ILMixed.Create(16,16,ILC_COLOR24|ILC_MASK,0,3);

	for(j=0;j<m_nColors;j++)
	{
		m_ILMixed.Add(hiEtalon);
		m_ILMixed.Add(hiEtalon);
		m_ILMixed.Add(hiEtalon);
	}
	m_List.ModifyStyle(0,LVS_SHAREIMAGELISTS|LVS_SHOWSELALWAYS|LVS_SINGLESEL);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP|LVS_EX_SUBITEMIMAGES);
	m_List.InsertColumn(0,"ID",LVCFMT_RIGHT,40);
	m_List.InsertColumn(1,"STYLE NAME",LVCFMT_LEFT,110);
	m_List.InsertColumn(2,"DESCRIPTION",LVCFMT_LEFT,180);
	m_List.InsertColumn(3,"FRG",LVCFMT_LEFT,90);
	m_List.InsertColumn(4,"BKG",LVCFMT_LEFT,90);
	m_List.InsertColumn(5,"FONT NAME",LVCFMT_LEFT,90);
	m_List.InsertColumn(6,"SIZE",LVCFMT_LEFT,44);
	m_List.InsertColumn(7,"UND",LVCFMT_LEFT,38);
	m_List.InsertColumn(8,"BOLD",LVCFMT_LEFT,44);
	m_List.InsertColumn(9,"ITA",LVCFMT_LEFT,34);
	m_List.InsertColumn(10,"VIS",LVCFMT_LEFT,34);
	m_List.InsertColumn(11,"EOL",LVCFMT_LEFT,34);
	m_List.InsertColumn(12,"CASE",LVCFMT_LEFT,58);
	m_List.InsertColumn(13,"CSET",LVCFMT_LEFT,44);
	m_List.InsertColumn(14,"HOTSPOT",LVCFMT_LEFT,68);


	m_List.SetImageList(&m_ILMixed,LVSIL_SMALL);

	tmph=NULL;
	GetDlgItem(IDC_APPLY,&tmph);
	if (tmph) SetWindowLong(tmph,GWL_STYLE,
		m_Scintilla?
		 (0xFFFFFFFF^WS_DISABLED)&GetWindowLong(tmph,GWL_STYLE)
		:WS_DISABLED|GetWindowLong(tmph,GWL_STYLE)
		);

	UpdateColors();

	m_List.SetItemState(0,LVIS_SELECTED,LVIS_SELECTED);

	return TRUE;
}

BOOL CDlgEditorColor::SetColors(const GPSCSTYLESET *iArray, UINT nColors)
{
	BOOL ret=FALSE;
	if (m_ColorArr) delete[] m_ColorArr;
	m_ColorArr=NULL;
	m_nColors=0;

	if (iArray && nColors)
	{
		ret=TRUE;
		m_nColors=nColors;
		m_ColorArr=new GPSCSTYLESET [m_nColors];
		UINT i;
		for(i=0;i<m_nColors;i++)
			m_ColorArr[i]=iArray[i];
	}
	if (m_hWnd) UpdateColors();
	return ret;
}

BOOL CDlgEditorColor::SaveColors(DWORD uLexerType, const char * cFileName)
{

	BOOL ret=FALSE;
	UINT uLexNum=0;
	for(uLexNum=0;uLexNum<GPScintilla::uNLexer && GPScintilla::uArrLexer[uLexNum]!=uLexerType;uLexNum++);

	if (uLexNum<GPScintilla::uNLexer && m_ColorArr && m_nColors)
	{
		FILE *src=NULL;
		FILE *dst=NULL;
		src=fopen(cFileName?cFileName:"LexerColors.txt","rt");
		dst=fopen("LexerColors.tmp","wt");
		if (dst)
		{
			char *tmps=new char [10000];
			while(src && fgetsEx(tmps,9990,src))
			{
				if (ExtractField(tmps,1,",")!=GPScintilla::cArrLexer[uLexNum])
					fprintf(dst,"%s\n",tmps);
			}
			CString strout;
			int i;
			for(i=0;i<(int)m_nColors;i++)
			{
				strout=GPScintilla::StyleInfoToStringEx(m_ColorArr[i]);
				if (strout!="")
				{
					ret=TRUE;
					fprintf(dst,"%s,%s\n",GPScintilla::cArrLexer[uLexNum],(LPCSTR)strout);
				}
			}

			fclose(dst);
			delete[] tmps;
		}
		if (src) fclose(src);

		if (ret)
		{
			CopyFile("LexerColors.tmp",cFileName?cFileName:"LexerColors.txt",FALSE);
		}
		DeleteFile("LexerColors.tmp");
	}

	return ret;
}

BOOL CDlgEditorColor::LoadColors(DWORD uLexerType, const char * cFileName)
{
	BOOL ret=FALSE;
	int nLexer;
	for(nLexer=0;nLexer<(int)GPScintilla::uNLexer && GPScintilla::uArrLexer[nLexer]!=uLexerType;nLexer++);

	if (nLexer<(int)GPScintilla::uNLexer)
	{
		FILE *src=fopen(cFileName?cFileName:"LexerColors.txt","rt");
		if (src)
		{
			if (m_ColorArr) delete[]  m_ColorArr;
			m_ColorArr=new GPSCSTYLESET [150];
			m_nColors=0;
			char *strtmp=new char [10000];

			while(fgetsEx(strtmp,9990,src) && m_nColors<150)
			{
				char *posstl=strchr(strtmp,',');
				if (posstl)
				{
					*(posstl++)=0;
					if (*posstl && _stricmp(strtmp,GPScintilla::cArrLexer[nLexer])==0)
							GPScintilla::StringToStyleInfo(posstl, m_ColorArr[m_nColors++]);
				}
			}

			delete[] strtmp;
			fclose(src);
			if (ret && m_hWnd) UpdateColors();
		}
	}
	return ret;
}


UINT CDlgEditorColor::GetColors(GPSCSTYLESET *iArray)
{
	UINT ret=0;
	if (iArray && m_nColors && m_ColorArr)
	{
		ret++;
		UINT i;
		for(i=0;i<m_nColors;i++)
			iArray[i]=m_ColorArr[i];
	}
	return ret;
}

void CDlgEditorColor::UpdateColors()
{
	if (m_hWnd)
	{
		m_List.DeleteAllItems();
		if (m_nColors && m_ColorArr)
		{
			UINT i;
			for(i=0;i<m_nColors;i++)
			{
				int nItem=m_List.InsertItem(i,"");
				SetItemInList(nItem,i);
			}
		}
	}
}

void CDlgEditorColor::SetImageInList(UINT nImage, COLORREF clr, COLORREF clrHatch)
{
	if ((UINT)m_ILMixed.GetImageCount()>nImage && iiEtalon.hbmColor && iiEtalon.hbmMask)
	{
		BYTE *b=new BYTE [2500];
		BYTE *b2=b+1250;
		BYTE *pos=b;
		int j;

		for(j=0;j<1024;j++)
		{
			b2[j]=0;
			b[j]=0;
		}

		HICON ic=NULL;

		for(j=0;j<256;j++)
		{
			if (clrHatch!=-1 && ((j%4)==2 || ((j/16)%4)==2))
			{
				*(pos++)=(BYTE)((clrHatch/0x10000)&0xFF);
				*(pos++)=(BYTE)((clrHatch/0x100)&0xFF);
				*(pos++)=(BYTE)((clrHatch)&0xFF);
			}
			else
			{
				*(pos++)=(BYTE)((clr/0x10000)&0xFF);
				*(pos++)=(BYTE)((clr/0x100)&0xFF);
				*(pos++)=(BYTE)((clr)&0xFF);
			}
		}

		HDC mdc=::GetDC(m_hWnd);
		BITMAPINFO lpbmi={0};
		lpbmi.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
		lpbmi.bmiHeader.biWidth=16;
		lpbmi.bmiHeader.biHeight=16;
		lpbmi.bmiHeader.biPlanes=1;
		lpbmi.bmiHeader.biBitCount=24;
		lpbmi.bmiHeader.biCompression=BI_RGB;
		lpbmi.bmiHeader.biSizeImage=0;
		lpbmi.bmiHeader.biXPelsPerMeter=0;
		lpbmi.bmiHeader.biYPelsPerMeter=0;
		lpbmi.bmiHeader.biClrUsed=0;
		lpbmi.bmiHeader.biClrImportant=0;

		SetDIBits(mdc, iiEtalon.hbmColor, 0, 16, (VOID *)b, &lpbmi, DIB_RGB_COLORS);
		SetDIBits(mdc, iiEtalon.hbmMask, 0, 16, (VOID *)b2, &lpbmi, DIB_RGB_COLORS);

		::ReleaseDC(m_hWnd,mdc);

		ic=::CreateIconIndirect(&iiEtalon);
		m_ILMixed.Replace(nImage,ic);
		DestroyIcon(ic);
		delete[] b;
	}
}

void CDlgEditorColor::SetItemInList(UINT nItem, UINT nColorArr)
{
	CString tmps;

	SetImageInList(nItem*3,m_ColorArr[nColorArr].bkg,m_ColorArr[nColorArr].frg);
	SetImageInList(nItem*3+1  ,m_ColorArr[nColorArr].frg);
	SetImageInList(nItem*3+2,m_ColorArr[nColorArr].bkg);

	tmps.Format("%3.3d",m_ColorArr[nColorArr].id);
	m_List.SetItem(nItem,0,LVIF_IMAGE|LVIF_TEXT,tmps,-1,0,0,0);
	m_List.SetItem(nItem,1,LVIF_IMAGE|LVIF_TEXT,m_ColorArr[nColorArr].styleName,nColorArr*3,0,0,0);
	m_List.SetItemText(nItem,2,m_ColorArr[nColorArr].StyleDescription);
	tmps.Format("%3.3d,%3.3d,%3.3d",GetRValue(m_ColorArr[nColorArr].frg),GetGValue(m_ColorArr[nColorArr].frg),GetBValue(m_ColorArr[nColorArr].frg));
	m_List.SetItem(nItem,3,LVIF_IMAGE|LVIF_TEXT,tmps,nColorArr*3+1,0,0,0);
	tmps.Format("%3.3d,%3.3d,%3.3d",GetRValue(m_ColorArr[nColorArr].bkg),GetGValue(m_ColorArr[nColorArr].bkg),GetBValue(m_ColorArr[nColorArr].bkg));
	m_List.SetItem(nItem,4,LVIF_IMAGE|LVIF_TEXT,tmps,nColorArr*3+2,0,0,0);
	m_List.SetItemText(nItem,5,m_ColorArr[nColorArr].fontName);
	tmps.Format("%d",m_ColorArr[nColorArr].fontSize);
	m_List.SetItemText(nItem,6,m_ColorArr[nColorArr].fontName==""?"":tmps);

	m_List.SetItemText(nItem,7,m_ColorArr[nColorArr].underline?"1":"0");
	m_List.SetItemText(nItem,8,m_ColorArr[nColorArr].bold?"1":"0");
	m_List.SetItemText(nItem,9,m_ColorArr[nColorArr].italic?"1":"0");
	m_List.SetItemText(nItem,10,m_ColorArr[nColorArr].visible?"1":"0");
	m_List.SetItemText(nItem,11,m_ColorArr[nColorArr].EOLFilled?"1":"0");
	m_List.SetItemText(nItem,12,m_ColorArr[nColorArr].Case==2?"LOWER":m_ColorArr[nColorArr].Case?"UPPER":"MIXED");
	tmps.Format("%d",m_ColorArr[nColorArr].CharacterSet);
	m_List.SetItemText(nItem,13,(LPCSTR)tmps);
	m_List.SetItemText(nItem,14,m_ColorArr[nColorArr].HOTSPOT?"1":"0");



}

void CDlgEditorColor::OnDestroy()
{
	CDialog::OnDestroy();

}

void CDlgEditorColor::OnOK()
{
	CDialog::OnOK();
}

void CDlgEditorColor::OnApply()
{
	if (m_Scintilla && m_Scintilla->m_hWnd && m_nColors && m_ColorArr)
	{
		UINT i;
		for(i=0;i<m_nColors;i++)
			m_Scintilla->SetStyleInfo(m_ColorArr[i]);
	}
}

void CDlgEditorColor::OnButtonFont()
{
}

void CDlgEditorColor::OnDblclkListStyles(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;
}

void CDlgEditorColor::OnCancel()
{
	CDialog::OnCancel();
}

void CDlgEditorColor::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	AUSI.UpdateSize();
}


void CDlgEditorColor::OnCustomdrawSliderbkg(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (m_bUpdateClr && m_CurListSel>=0)
	{
		int posarr=m_SliderBkg.GetPos();
		m_ColorArr[m_CurListSel].bkg=RGB(arrRGB[posarr*3+2],arrRGB[posarr*3+1],arrRGB[posarr*3]);
		SetItemInList(m_CurListSel,m_CurListSel);
	}

	*pResult = 0;
}

void CDlgEditorColor::OnCustomdrawSliderfrg(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (m_bUpdateClr && m_CurListSel>=0)
	{
		int posarr=m_SliderFrg.GetPos();
		m_ColorArr[m_CurListSel].frg=RGB(arrRGB[posarr*3+2],arrRGB[posarr*3+1],arrRGB[posarr*3]);
		SetItemInList(m_CurListSel,m_CurListSel);
	}
	*pResult = 0;
}

void CDlgEditorColor::OnItemchangedListColors(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView =(NM_LISTVIEW*)pNMHDR;
	if ((pNMListView->uNewState&LVIS_SELECTED)==LVIS_SELECTED)
	{
		m_bUpdateClr=FALSE;
		m_CurListSel=pNMListView->iItem;

		m_SliderBkg.SetPos(FindClrInPalette(m_ColorArr[m_CurListSel].bkg));
		m_SliderFrg.SetPos(FindClrInPalette(m_ColorArr[m_CurListSel].frg));

		HWND tmphwnd=::GetDlgItem(m_hWnd,IDC_COMBOFONT);
		if (tmphwnd)
		{
			int nSel=0;
			nSel=::SendMessage(tmphwnd,CB_FINDSTRINGEXACT,0,(LPARAM)((LPCSTR)(m_ColorArr[m_CurListSel].fontName)));
			if (nSel==CB_ERR)
				nSel=::SendMessage(tmphwnd,CB_FINDSTRING,0,(LPARAM)((LPCSTR)(m_ColorArr[m_CurListSel].fontName)));
			if (nSel==CB_ERR)
				nSel=::SendMessage(tmphwnd,CB_FINDSTRING,0,(LPARAM)"Courier");
			if (nSel==CB_ERR)	nSel=0;
			::SendMessage(tmphwnd,CB_SETCURSEL,(WPARAM)nSel,0);
		}

		::CheckDlgButton(m_hWnd,IDC_CHECKBOLD,m_ColorArr[m_CurListSel].bold);
		::CheckDlgButton(m_hWnd,IDC_CHECKITALIC,m_ColorArr[m_CurListSel].italic);
		::CheckDlgButton(m_hWnd,IDC_CHECKUNDERLINE,m_ColorArr[m_CurListSel].underline);
		::CheckDlgButton(m_hWnd,IDC_CHECKVISIBLE,m_ColorArr[m_CurListSel].visible);
		::CheckDlgButton(m_hWnd,IDC_CHECKHOTSPOT,m_ColorArr[m_CurListSel].HOTSPOT);
		::CheckDlgButton(m_hWnd,IDC_CHECKEOLFILLED,m_ColorArr[m_CurListSel].EOLFilled);

		::SendMessage(::GetDlgItem(m_hWnd,IDC_COMBOCASE),CB_SETCURSEL,m_ColorArr[m_CurListSel].Case,0);


		char tmps[100];
		sprintf(tmps,"%d",m_ColorArr[m_CurListSel].CharacterSet);
		::SetDlgItemText(m_hWnd,IDC_EDITCHARSET,(LPCSTR)tmps);
		sprintf(tmps,"%d",m_ColorArr[m_CurListSel].fontSize);
		::SetDlgItemText(m_hWnd,IDC_EDITFONTSIZE,(LPCSTR)tmps);

		m_bUpdateClr=TRUE;
	}

	*pResult = 0;
}

UINT CDlgEditorColor::FindClrInPalette(COLORREF clr)
{
	BYTE R=GetRValue(clr);
	BYTE G=GetGValue(clr);
	BYTE B=GetBValue(clr);
	int i;
	int delta=1000;
	UINT ret=0;
	for(i=0;i<RGBPALLETESIZE && delta;i++)
	{
		int tmpDelta=abs(B-arrRGB[i*3])+abs(G-arrRGB[i*3+1])+abs(R-arrRGB[i*3+2]);
		if (delta>tmpDelta)
		{
			delta=tmpDelta;
			ret=i;
		}
	}
	return ret;
}

UINT CDlgEditorColor::GetColorsCount()
{
	return m_nColors;
}

void CDlgEditorColor::OnSelchangeCombofont()
{
	if (m_bUpdateClr && m_CurListSel>=0)
	{
		GetDlgItemText(IDC_COMBOFONT,m_ColorArr[m_CurListSel].fontName);
		SetItemInList(m_CurListSel,m_CurListSel);
	}
}

void CDlgEditorColor::OnCheckbold()
{
	if (m_bUpdateClr && m_CurListSel>=0)
	{
		m_ColorArr[m_CurListSel].bold=::IsDlgButtonChecked(m_hWnd,IDC_CHECKBOLD);
		SetItemInList(m_CurListSel,m_CurListSel);
	}
}

void CDlgEditorColor::OnCheckitalic()
{
	if (m_bUpdateClr && m_CurListSel>=0)
	{
		m_ColorArr[m_CurListSel].italic=::IsDlgButtonChecked(m_hWnd,IDC_CHECKITALIC);
		SetItemInList(m_CurListSel,m_CurListSel);
	}
}

void CDlgEditorColor::OnCheckunderline()
{
	if (m_bUpdateClr && m_CurListSel>=0)
	{
		m_ColorArr[m_CurListSel].underline=::IsDlgButtonChecked(m_hWnd,IDC_CHECKUNDERLINE);
		SetItemInList(m_CurListSel,m_CurListSel);
	}
}

void CDlgEditorColor::OnCheckvisible()
{
	if (m_bUpdateClr && m_CurListSel>=0)
	{
		m_ColorArr[m_CurListSel].visible=::IsDlgButtonChecked(m_hWnd,IDC_CHECKVISIBLE);
		SetItemInList(m_CurListSel,m_CurListSel);
	}
}

void CDlgEditorColor::OnCheckhotspot()
{
	if (m_bUpdateClr && m_CurListSel>=0)
	{
		m_ColorArr[m_CurListSel].HOTSPOT=::IsDlgButtonChecked(m_hWnd,IDC_CHECKHOTSPOT);
		SetItemInList(m_CurListSel,m_CurListSel);
	}
}

void CDlgEditorColor::OnCheckeolfilled()
{
	if (m_bUpdateClr && m_CurListSel>=0)
	{
		m_ColorArr[m_CurListSel].EOLFilled=::IsDlgButtonChecked(m_hWnd,IDC_CHECKEOLFILLED);
		SetItemInList(m_CurListSel,m_CurListSel);
	}
}


void CDlgEditorColor::OnChangeEditcharset()
{
	if (m_bUpdateClr && m_CurListSel>=0)
	{
		m_ColorArr[m_CurListSel].CharacterSet=GetDlgItemInt(IDC_EDITCHARSET);
		SetItemInList(m_CurListSel,m_CurListSel);
	}

}

void CDlgEditorColor::OnChangeEditfontsize()
{
	if (m_bUpdateClr && m_CurListSel>=0)
	{
		m_ColorArr[m_CurListSel].fontSize=GetDlgItemInt(IDC_EDITFONTSIZE);
		SetItemInList(m_CurListSel,m_CurListSel);
	}
}

void CDlgEditorColor::OnSelchangeCombocase()
{
	if (m_bUpdateClr && m_CurListSel>=0)
	{
		m_ColorArr[m_CurListSel].Case=::SendMessage(::GetDlgItem(m_hWnd,IDC_COMBOCASE),CB_GETCURSEL,0,0);
		SetItemInList(m_CurListSel,m_CurListSel);
	}
}

void CDlgEditorColor::SetEditor(GPScintilla *iEditor)
{
	m_Scintilla=iEditor;
}

