// WndPrint.cpp: implementation of the WndPrint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "WndPrint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WndPrint::WndPrint(HWND hWnd)
{
	m_hWnd=hWnd;
}

WndPrint::~WndPrint()
{

}


   // Return a HDC for the default printer.
HDC WndPrint::GetPrinterDC(void)
{
	PRINTDLG pdlg;

	memset( &pdlg, 0, sizeof( pdlg ) );
	pdlg.lStructSize = sizeof( pdlg );
	pdlg.Flags = PD_RETURNDEFAULT | PD_RETURNDC;
	PrintDlg( &pdlg );
	return pdlg.hDC;
}

   // Create a copy of the current system palette.
HPALETTE WndPrint::GetSystemPalette()
{
	HDC hDC;
	HPALETTE hPal;
	HANDLE hLogPal;
	LPLOGPALETTE lpLogPal;

	// Get a DC for the desktop.
	hDC = GetDC(NULL);

	// Check to see if you are a running in a palette-based video mode.
	if (!(GetDeviceCaps(hDC, RASTERCAPS) & RC_PALETTE)) {
	   ReleaseDC(NULL, hDC);
	   return NULL;
	}

	// Allocate memory for the palette.
	hLogPal = GlobalAlloc(GPTR, sizeof(LOGPALETTE) + 256*sizeof(PALETTEENTRY));
	if (!hLogPal)  return NULL;

	// Initialize.
	lpLogPal=(LPLOGPALETTE)hLogPal;
	lpLogPal->palVersion = 0x300;
	lpLogPal->palNumEntries = 256;

	// Copy the current system palette into the logical palette.
	GetSystemPaletteEntries(hDC, 0, 256,
	   (LPPALETTEENTRY)(lpLogPal->palPalEntry));

	// Create the palette.
	hPal = CreatePalette(lpLogPal);

	// Clean up.
	GlobalFree(lpLogPal);
	ReleaseDC(NULL, hDC);

	return hPal;
}

   // Create a 24-bit-per-pixel surface.
HBITMAP WndPrint::Create24BPPDIBSection(HDC hDC, int iWidth, int iHeight)
{
	BITMAPINFO bmi;
	HBITMAP hbm;
	LPBYTE pBits;

	// Initialize to 0s.
	ZeroMemory(&bmi, sizeof(bmi));

	// Initialize the header.
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = iWidth;
	bmi.bmiHeader.biHeight = iHeight;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biCompression = BI_RGB;

	// Create the surface.
	hbm = CreateDIBSection(hDC, &bmi, DIB_RGB_COLORS, (void **)&pBits, NULL, 0);

	return(hbm);
}


BOOL WndPrint::PrintWindowToDC(int Dlg,int Paper,int Orient)
{
	HBITMAP hbm;
	HDC     hdcPrinter;
	HDC     hdcMemory;
	HDC     hdcWindow;
	int     iWidth;
	int     iHeight;
	DOCINFO di;
	RECT    rc;
	DIBSECTION ds;
	HPALETTE   hPal;

	// Do you have a valid window?
	if (!IsWindow(m_hWnd))   return FALSE;

	// Get a HDC for the default printer.
	CPrintDialog *printDlg =
		new CPrintDialog(FALSE, PD_ALLPAGES | PD_RETURNDC|(Dlg==1?0:PD_RETURNDEFAULT), NULL);
	// Initialize some of the fields in PRINTDLG structure.
	printDlg->m_pd.nMinPage = printDlg->m_pd.nMaxPage = 1;
	printDlg->m_pd.nFromPage = printDlg->m_pd.nToPage = 1;
	printDlg->DoModal();
	DEVMODE* dm=printDlg->GetDevMode( );
	BOOL ResetFlg=FALSE;

	if (Orient==0 && dm->dmOrientation!=DMORIENT_PORTRAIT)
	{
		dm->dmOrientation=DMORIENT_PORTRAIT;
		ResetFlg=TRUE;
	}
	if (Orient==1 && dm->dmOrientation!=DMORIENT_LANDSCAPE)
	{
		dm->dmOrientation=DMORIENT_LANDSCAPE;
		ResetFlg=TRUE;
	}

	if (dm->dmPaperSize!=Paper && Paper!=-12345)
	{
		dm->dmPaperSize=(short)Paper;
		ResetFlg=TRUE;
	}

	hdcPrinter = printDlg->GetPrinterDC();
	if (!hdcPrinter) {delete  printDlg;return FALSE;}

	SetForegroundWindow(m_hWnd);
	// Get the HDC for the entire window.
	hdcWindow  = GetWindowDC(m_hWnd);
	if (ResetFlg==TRUE) ResetDC(hdcWindow,dm);


	// Get the rectangle bounding the window.
	GetWindowRect(m_hWnd, &rc);

	// Adjust coordinates to client area.
	OffsetRect(&rc, -rc.left, -rc.top);

	// Get the resolution of the printer device.
	iWidth  = GetDeviceCaps(hdcPrinter, HORZRES);
	iHeight = GetDeviceCaps(hdcPrinter, VERTRES);

	// Create the intermediate drawing surface at window resolution.
	hbm = Create24BPPDIBSection(hdcWindow, rc.right, rc.bottom);
	if (!hbm) 
	{
		DeleteDC(hdcPrinter);
		ReleaseDC(m_hWnd, hdcWindow);
		return FALSE;
	}

	// Prepare the surface for drawing.
	hdcMemory = CreateCompatibleDC(hdcWindow);
	SelectObject(hdcMemory, hbm);

	// Get the current system palette.
	hPal = GetSystemPalette();

	// If a palette was returned.
	if (hPal)
	{
		// Apply the palette to the source DC.
		SelectPalette(hdcWindow, hPal, FALSE);
		RealizePalette(hdcWindow);

		// Apply the palette to the destination DC.
		SelectPalette(hdcMemory, hPal, FALSE);
		RealizePalette(hdcMemory);
	}

	// Copy the window contents to the memory surface.
	BitBlt(hdcMemory, 0, 0, rc.right, rc.bottom,  hdcWindow, 0, 0, SRCCOPY);

	// Prepare the DOCINFO.
	ZeroMemory(&di, sizeof(di));
	di.cbSize = sizeof(di);
	di.lpszDocName = "Window Contents";

	// Initialize the print job.
	if (StartDoc(hdcPrinter, &di) > 0)
	{
	   // Prepare to send a page.
	   if (StartPage(hdcPrinter) > 0)
	   {
		   // Retrieve the information describing the surface.
			SetMapMode(hdcPrinter,MM_ISOTROPIC);
			SIZE sz;
			SetWindowExtEx(hdcPrinter,rc.right+30,rc.bottom+30,&sz);
			SetViewportExtEx(hdcPrinter,iWidth, iHeight,&sz) ;
			POINT pt;
			SetViewportOrgEx(hdcPrinter,200,200,&pt) ;


			GetObject(hbm, sizeof(ds), &ds);
			// Print the contents of the surface.
			StretchDIBits(hdcPrinter,
			   0, 0, rc.right, rc.bottom,
			   0, 0, rc.right, rc.bottom,
			   ds.dsBm.bmBits,
			   (LPBITMAPINFO)&ds.dsBmih,
			   DIB_RGB_COLORS,
			   SRCCOPY);

		   // Let the driver know the page is done.
		   EndPage(hdcPrinter);
	   }
	   // Let the driver know the document is done.
	   EndDoc(hdcPrinter);
	}

	// Clean up the objects you created.
	DeleteDC(hdcPrinter);
	DeleteDC(hdcMemory);
	ReleaseDC(m_hWnd, hdcWindow);
	DeleteObject(hbm);
	if (hPal)	DeleteObject(hPal);

	return TRUE;
}

void WndPrint::TranslateParam(const char *iStr, int &Dlg,int &Paper,int &Orient)
{
	Dlg=0;
	Paper=-12345;
	Orient=-12345;
	m_LastScanf=sscanf(iStr,"%d,%d,%d",&Dlg,&Orient,&Paper);
	if (Paper==-12345)
	{
		char *buff=new char [(int)strlen(iStr)+10];
		strcpy(buff,iStr);
		char *postmp=strchr(buff,',');
		if (postmp!=NULL) 
			postmp=strchr(++postmp,',');

		Paper=9;
		if (postmp++!=NULL) 
		{
			_strupr(postmp);
			int PapInt[118]=
			{
				 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,
				21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
				41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,
				61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,
				81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,
				101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,
			};
			char *PapStr[118]=
			{
				"LETTER","LETTERSMALL","TABLOID","LEDGER","LEGAL",
				"STATEMENT","EXECUTIVE","A3","A4","A4SMALL",
				"A5","B4","B5","FOLIO","QUARTO",
				"10X14","11X17","NOTE","ENV_9","ENV_10",
				"ENV_11","ENV_12","ENV_14","CSHEET","DSHEET",
				"ESHEET","ENV_DL","ENV_C5","ENV_C3","ENV_C4",
				"ENV_C6","ENV_C65","ENV_B4","ENV_B5","ENV_B6",
				"ENV_ITALY","ENV_MONARCH","ENV_PERSONAL","FANFOLD_US","FANFOLD_STD_GERMAN",
				"FANFOLD_LGL_GERMAN","ISO_B4","JAPANESE_POSTCARD","9X11","10X11",
				"15X11","ENV_INVITE","RESERVED_48","RESERVED_49","LETTER_EXTRA",
				"LEGAL_EXTRA","TABLOID_EXTRA","A4_EXTRA","LETTER_TRANSVERSE","A4_TRANSVERSE",
				"LETTER_EXTRA_TRANSVERSE","A_PLUS","B_PLUS","LETTER_PLUS","A4_PLUS",
				"A5_TRANSVERSE","B5_TRANSVERSE","A3_EXTRA","A5_EXTRA","B5_EXTRA",
				"A2","A3_TRANSVERSE","A3_EXTRA_TRANSVERSE","DBL_JAPANESE_POSTCARD","A6",
				"JENV_KAKU2","JENV_KAKU3","JENV_CHOU3","JENV_CHOU4","LETTER_ROTATED",
				"A3_ROTATED","A4_ROTATED","A5_ROTATED","B4_JIS_ROTATED","B5_JIS_ROTATED",
				"JAPANESE_POSTCARD_ROTATED","DBL_JAPANESE_POSTCARD_ROTATED","A6_ROTATED","JENV_KAKU2_ROTATED","JENV_KAKU3_ROTATED",
				"JENV_CHOU3_ROTATED","JENV_CHOU4_ROTATED","B6_JIS","B6_JIS_ROTATED","12X11",
				"JENV_YOU4","JENV_YOU4_ROTATED","P16K","P32K","P32KBIG",
				"PENV_1","PENV_2","PENV_3","PENV_4","PENV_5",
				"PENV_6","PENV_7","PENV_8","PENV_9","PENV_10",
				"P16K_ROTATED","P32K_ROTATED","P32KBIG_ROTATED","PENV_1_ROTATED","PENV_2_ROTATED",
				"PENV_3_ROTATED","PENV_4_ROTATED","PENV_5_ROTATED","PENV_6_ROTATED","PENV_7_ROTATED",
				"PENV_8_ROTATED","PENV_9_ROTATED","PENV_10_ROTATED",
			};

			int i;
			for(i=0;i<118 && strcmp(postmp,PapStr[i])!=0;i++);
				if (i<118) Paper=PapInt[i];
		}
		delete[] buff;
	}
}
