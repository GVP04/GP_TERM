// FontPlus.cpp: implementation of the CFontPlus class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "FontPlus.h"
#include "GP_TermView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//const char *CFontPlus::ccA[]={"","","","","","","",};
//const DWORD CFontPlus::iA[]={,,,,,,,0,};

const char *CFontPlus::ccAFontStyle[]={"Regular","Bold","Italic","BoldItalic","Underline","Strikeout","",};
const DWORD CFontPlus::iAFontStyle[]={FontStyleRegular,FontStyleBold,FontStyleItalic,FontStyleBoldItalic,FontStyleUnderline,FontStyleStrikeout,FontStyleRegular,0,};



const UINT CFontPlus::uNMethods=12;
const char *CFontPlus::cArrMethods[]={
/*00*/		"GetCellAscent","GetCellDescent","GetEmHeight","GetLineSpacing","IsStyleAvailable",
/*05*/		"GetFamilyName","GetHeight","GetLastStatus","GetSize","GetStyle",
/*10*/		"GetUnit","IsAvailable","","","",
/*15*/		"","","","","",
	};
const char *CFontPlus::cArrMethodsParams[]={
/*00*/		"FontStyle","FontStyle","FontStyle","FontStyle","FontStyle",
/*05*/		"","DPI","","","",
/*10*/		"","","","","",
/*15*/		"","","","","",
	};

CFontPlus::CFontPlus(const char *ccIstr)
{
	CString CSFontFamily,CSTmp;
	REAL rSize=0;
	DWORD fStyle=FontStyleRegular;
	//SIZE=xxx;NAME=xxx;STYLE=xxxx;

	int i=0;
	if (ccIstr)
		while((CSTmp=ExtractField(ccIstr,++i,";"))!="")
		{
			CString CSTmp1=ExtractField(CSTmp,1,"=");
			CString CSTmp2=ExtractField(CSTmp,2,"=");
			CSTmp1.MakeUpper();
			if (CSTmp2!="")
				if (CSTmp1=="SIZE")
					rSize=(REAL)atof(CSTmp2);
				else
				if (CSTmp1=="NAME")
					CSFontFamily=CSTmp2;
				else
				if (CSTmp1=="STYLE")
				{
					int j;
					CSTmp2.MakeUpper();
					for(j=0;*CFontPlus::ccAFontStyle[j];j++)
					{
						CSTmp1=CFontPlus::ccAFontStyle[j];
						CSTmp1.MakeUpper();
						if (CSTmp2.Find(CSTmp1)>=0) fStyle|=CFontPlus::iAFontStyle[j];
					}
				}
		}


	FontFamily *emHeightFontFamily=NULL;
	const FontFamily *FFPtr=FontFamily::GenericSansSerif();
	if (CSFontFamily!="")
	{
		WCHAR tmpWText2[200];
		MultiByteToWideChar(CP_ACP, 0,CSFontFamily, -1, tmpWText2, 100);
		emHeightFontFamily=new FontFamily(tmpWText2);
		if (emHeightFontFamily->GetLastStatus())
		{
			CSTmp=CSFontFamily;
			CSTmp.MakeUpper();

			if (CSTmp.Find("SANS")>=0 && CSTmp.Find("SERIF")>=0) FFPtr=FontFamily::GenericSansSerif();
			else
			if (CSTmp.Find("SERIF")>=0) FFPtr=FontFamily::GenericSerif();
			else
			if (CSTmp.Find("MONOS")>=0) FFPtr=FontFamily::GenericMonospace();
		}
		else FFPtr=emHeightFontFamily;
	}

	if (rSize<5) rSize=((REAL)(::GetSystemMetrics(SM_CYMENU)))/2-2;
	if (rSize<5) rSize=8;


	m_Font=new Font(FFPtr, rSize,(FontStyle)fStyle);
	if (emHeightFontFamily) delete emHeightFontFamily;
}

CFontPlus::CFontPlus(HDC hdc, const char *ccIstr)
{
	HDC tmpHDC=NULL;
	if (!hdc)
	{
		tmpHDC=::GetDC(GPC.m_hViewWnd);
		hdc=tmpHDC;
	}
	if (ccIstr && *ccIstr)
	{
		LOGFONT lf={0};
		TranslLOGFONT(lf,ccIstr);
		m_Font=new Font(hdc,&lf);
	}
	else 
		m_Font=new Font(hdc);

	if (tmpHDC) ::ReleaseDC(GPC.m_hViewWnd,tmpHDC);
}

CFontPlus::CFontPlus(const FontFamily *family, REAL emSize, INT style, Unit unit) 
{
	m_Font=new Font(family, emSize, style, unit);
}

CFontPlus::CFontPlus(HDC hdc, const LOGFONTA *logfont)
{
	m_Font=new Font(hdc, logfont);
}

CFontPlus::CFontPlus(HDC hdc) 
{
	m_Font=new Font(hdc);
}

CFontPlus::~CFontPlus()
{
	if (m_Font) delete m_Font;
	m_Font=NULL;
}


UINT CFontPlus::DoMethod(const char *iStr, char *oStr)
{
	int nfunc=0;
	char met[150];
	strncpy(met,iStr,145);
	met[145]=0;
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int retint=-123456; 
	int i;
	int atoipos=atoi(pos);
	const char *pos2=pos;
	while(*pos2!=0 && *pos2!=',' && *pos2!='=') pos2++;
	if (*pos2!=0) pos2++;

	if (*met>='0' && *met<='9') nfunc=atoi(met);
	else
	{
		static const char *sccArrMethods[sizeof(cArrMethods)/sizeof(char *)];
		static DWORD scdMethodsId[sizeof(cArrMethods)/sizeof(char *)];
		if (!*sccArrMethods)
		{
			DWORD i;
			for(i=0;i<uNMethods;i++)
			{
				sccArrMethods[i]=cArrMethods[i];
				scdMethodsId[i]=i;
			}
			qsCharILineAndDWORD(sccArrMethods, scdMethodsId, 0, uNMethods-1);
			scdMethodsId[i]=i;
		}
		nfunc=scdMethodsId[FindInSortArrayIC(met, sccArrMethods, uNMethods)];
	}

	switch(nfunc)
	{
	case  0: //GetCellAscent FontStyle
	case  1: //GetCellDescent FontStyle
	case  2: //GetEmHeight FontStyle
	case  3: //GetLineSpacing FontStyle
	case  4: //IsStyleAvailable FontStyle
		{
			FontFamily fontFamily;
			m_Font->GetFamily(&fontFamily);
			DWORD dwStyle=atoipos;
			if (*pos!='0' && dwStyle==0)
			{
				for(i=0;*ccAFontStyle[i] && _stricmp(ccAFontStyle[i],pos)!=0;i++);
				dwStyle=iAFontStyle[i];
			}
			switch(nfunc)
			{
			case  0:
				retint=fontFamily.GetCellAscent(dwStyle);
				break;
			case  1: 
				retint=fontFamily.GetCellDescent(dwStyle);
				break;
			case  2: 
				retint=fontFamily.GetEmHeight(dwStyle);
				break;
			case  3:
				retint=fontFamily.GetLineSpacing(dwStyle);
				break;
			case  4:
				retint=fontFamily.IsStyleAvailable(dwStyle);
			}
		}
		break; 
	case 5: //GetFamilyName
		if (oStr)
		{
			FontFamily fontFamily;
			m_Font->GetFamily(&fontFamily);
			WCHAR  familyName[LF_FACESIZE];
			fontFamily.GetFamilyName(familyName);
			CString tmpcs(familyName);
			strcpy(oStr,tmpcs);
		}
		break; 
	case  6: // GetHeight DPI
		if (oStr) sprintf(oStr,"%g",m_Font->GetHeight((REAL)atof(pos)));
		break; 
	case  7: // GetLastStatus 
		retint=m_Font->GetLastStatus();
		break; 
	case  8: // GetSize
		if (oStr) sprintf(oStr,"%g",m_Font->GetSize());
		break; 
	case  9: // GetStyle 
		retint=m_Font->GetStyle();
		break; 
	case  10: // GetUnit 
		retint=m_Font->GetUnit();
		break; 
	case  11: // IsAvailable
		retint=m_Font->IsAvailable();
		break; 
	default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
	}
	if (oStr && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);

	return nfunc;
}

