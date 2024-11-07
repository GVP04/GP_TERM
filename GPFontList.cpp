// GPFontList.cpp: implementation of the CGPFontList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPFontList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL( CGPFontList, CObject, 0 )

int CALLBACK GPEnumFontFamExProcGetList(
  ENUMLOGFONTEX *lpelfe,    // logical-font data
  NEWTEXTMETRICEX *lpntme,  // physical-font data
  DWORD FontType,           // type of font
  LPARAM lParam             // application-defined data
)
{
	if (lParam)
	{
		
		while(((CGPFontList *)lParam)->m_nFonts>=((CGPFontList *)lParam)->m_nMaxFonts)
		{
			((CGPFontList *)lParam)->m_nMaxFonts+=((CGPFontList *)lParam)->m_nMaxFonts/2;
			GPFONTINFO **tmparr=new  GPFONTINFO * [((CGPFontList *)lParam)->m_nMaxFonts];
			UINT i;
			for(i=0;i<((CGPFontList *)lParam)->m_nFonts;i++)
				tmparr[i]=((CGPFontList *)lParam)->m_ArrGPFONTINFO[i];
			delete ((CGPFontList *)lParam)->m_ArrGPFONTINFO;
			((CGPFontList *)lParam)->m_ArrGPFONTINFO=tmparr;
		}

		GPFONTINFO *item=((CGPFontList *)lParam)->m_ArrGPFONTINFO[(((CGPFontList *)lParam)->m_nFonts)++]=new GPFONTINFO;
		item->FontType=FontType;
		item->tmex=*lpntme;
		item->elf=*lpelfe;
	}
	return 1;
}


CGPFontList::CGPFontList()
{
	m_nFonts=0;
	m_nMaxFonts=500;
	m_ArrGPFONTINFO=NULL;
	memset(&Logfont,0,sizeof(Logfont));
	Logfont.lfCharSet=DEFAULT_CHARSET;
	Init();
}

CGPFontList::CGPFontList(LOGFONT & ilf)
{
	m_nFonts=0;
	m_nMaxFonts=500;
	m_ArrGPFONTINFO=NULL;
	ResetList(ilf);
}

CGPFontList::~CGPFontList()
{
	DestroyList();
}

void CGPFontList::Serialize( CArchive& archive )
{

}

void CGPFontList::Init()
{
	DestroyList();
	m_nMaxFonts=500;
	m_ArrGPFONTINFO=new GPFONTINFO * [m_nMaxFonts];
	HDC hDC = GetDC( NULL );

	EnumFontFamiliesEx(hDC,&Logfont,(FONTENUMPROC)GPEnumFontFamExProcGetList,(LPARAM)this,0);

	ReleaseDC( NULL, hDC );
}

void CGPFontList::DestroyList()
{
	if (m_ArrGPFONTINFO)
	{
		UINT i;
		for(i=0;i<m_nFonts;i++)
			if (m_ArrGPFONTINFO[i])
			{
				delete m_ArrGPFONTINFO[i];
				m_ArrGPFONTINFO[i]=NULL;
			}
		delete[] m_ArrGPFONTINFO;
		m_ArrGPFONTINFO=NULL;
	}
}

void CGPFontList::FillListBox(HWND iHWND, UINT uFlag = GPFL_CLEAR|GPFL_NOSCRIPT)
{
	if (iHWND)
	{

		if ((uFlag&GPFL_CLEAR)==GPFL_CLEAR)
			::SendMessage(iHWND,LB_RESETCONTENT,0,0);

		if ((uFlag&GPFL_NOSCRIPT)==GPFL_NOSCRIPT)
		{
			CString LastFam="";
			UINT i;
			for(i=0;i<m_nFonts;i++)
				if (LastFam!=m_ArrGPFONTINFO[i]->elf.elfFullName)
				{
					LastFam=m_ArrGPFONTINFO[i]->elf.elfFullName;
					::SendMessage(iHWND,LB_ADDSTRING,0,(LPARAM)((LPCSTR)LastFam));
				}
		}
		else
		if (Logfont.lfCharSet==DEFAULT_CHARSET)
		{
			UINT i;
			for(i=0;i<m_nFonts;i++)
			{
				CString tmp=m_ArrGPFONTINFO[i]->elf.elfFullName;
				tmp+=" ";
				tmp+=(TCHAR *)m_ArrGPFONTINFO[i]->elf.elfScript;
				::SendMessage(iHWND,LB_ADDSTRING,0,(LPARAM)((LPCSTR)tmp));
			}
		}
		else
		{
			UINT i;
			for(i=0;i<m_nFonts;i++)
				::SendMessage(iHWND,LB_ADDSTRING,0,(LPARAM)(m_ArrGPFONTINFO[i]->elf.elfFullName));
		}
	}
}

void CGPFontList::FillComboBox(HWND iHWND, UINT uFlag = GPFL_CLEAR|GPFL_NOSCRIPT, UINT cmpPitchFam)
{
	if (iHWND)
	{
		if ((uFlag&GPFL_CLEAR)==GPFL_CLEAR)
			::SendMessage(iHWND,CB_RESETCONTENT,0,0);

		if ((uFlag&GPFL_NOSCRIPT)==GPFL_NOSCRIPT)
		{
			CString LastFam="";
			UINT i;
			for(i=0;i<m_nFonts;i++)
				if (cmpPitchFam==0 || (cmpPitchFam&m_ArrGPFONTINFO[i]->elf.elfLogFont.lfPitchAndFamily)==cmpPitchFam)
					if (LastFam!=m_ArrGPFONTINFO[i]->elf.elfFullName)
					{
						LastFam=m_ArrGPFONTINFO[i]->elf.elfFullName;
						::SendMessage(iHWND,CB_ADDSTRING,0,(LPARAM)((LPCSTR)LastFam));
					}
		}
		else
		if (Logfont.lfCharSet==DEFAULT_CHARSET)
		{
			UINT i;
			for(i=0;i<m_nFonts;i++)
			{
				CString tmp=m_ArrGPFONTINFO[i]->elf.elfFullName;
				tmp+=" ";
				tmp+=(TCHAR *)m_ArrGPFONTINFO[i]->elf.elfScript;
				::SendMessage(iHWND,CB_ADDSTRING,0,(LPARAM)((LPCSTR)tmp));
			}
		}
		else
		{
			UINT i;
			for(i=0;i<m_nFonts;i++)
				::SendMessage(iHWND,CB_ADDSTRING,0,(LPARAM)(m_ArrGPFONTINFO[i]->elf.elfFullName));
		}
	}
}

void CGPFontList::FillListCtrl(HWND iHWND, UINT uFlag = GPFL_CLEAR|GPFL_NOSCRIPT, int nNameColumn, int ScriptColumn, int SizeColumn)
{

}

UINT CGPFontList::ResetList(LOGFONT & ilf)
{
	Logfont=ilf;
	Init();
	return m_nFonts;
}

const GPFONTINFO *CGPFontList::GetElement(UINT nElement)
{
	GPFONTINFO *ret=NULL;
	if (nElement<m_nFonts && m_ArrGPFONTINFO)
		ret=m_ArrGPFONTINFO[nElement];

	return ret;
}
