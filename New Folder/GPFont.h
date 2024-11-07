// GPFont.h: interface for the GPFont class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPFONT_H__2D485AA1_D149_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GPFONT_H__2D485AA1_D149_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum GP_FNT
{
 GP_FNT_REGULAR     =		FontStyleRegular,		
 GP_FNT_UNDERLINE   =		FontStyleUnderline,				
 GP_FNT_STRIKE      =		FontStyleStrikeout,		
 GP_FNT_ITALIC      =		FontStyleItalic,		
 GP_FNT_BOLD		=	 	FontStyleBold,
 GP_FNT_STYLEMASK	=	 	0x0000000F,
 GP_FNT_MAXCNT		=		0x00000010,
 GP_FNT_SELECTION	=	 	0x00010000,
 GP_FNT_FIXED		=	 	0x00020000,
 GP_FNT_OPAQUE      =		0x00040000,		    // прозрачный
 GP_FNT_CODE        =   	0x00080000,			// 0 OEM 1 RUSSIAN, 
 GP_FNT_BLINK		=		0x00100000,				
 GP_FNT_LIGHT		=	 	0x00200000,
 GP_FNT_SHADOW1		=	 	0x01000000,
 GP_FNT_SHADOW2		=	 	0x02000000,
 GP_FNT_SHADOW3		=	 	0x03000000,
 GP_FNT_SHADOW4		=	 	0x04000000,
 GP_FNT_SHADOW5		=	 	0x05000000,
 GP_FNT_SHADOW6		=	 	0x06000000,
 GP_FNT_SHADOW7		=	 	0x07000000,
 GP_FNT_SHADOW8		=	 	0x08000000,
 GP_FNT_SHADOWMASK	=	 	0x0F000000,
 GP_FNT_SHADOWMP    =	 	0x01000000,
};

class GPScreen;


class GPFont  
{
public:
	const Font * InitFontTable(const char * iFamilyName, GPScreen *pScr);
	const Font * InitFontTable(WCHAR * iFamilyName, GPScreen *pScr);
	void DeleteFontTable();
	const Font * GetFont(DWORD dwType);
	static DWORD TranslateCharStyle(const char *iStr);
	static CString TranslateCharStyle(DWORD dwiStyle);
	const static char *cArrStyles[];
	const static char *cArrStyles2[];
	const static GP_FNT uArrStyles[];

	REAL maxWidth;
	REAL maxHeight;
	REAL DeltaWidthUC;
	REAL DeltaHeightUC;
	GPFont();
	virtual ~GPFont();
	WCHAR familyName[250];
private:
	Font **fnt;
};

#endif // !defined(AFX_GPFONT_H__2D485AA1_D149_11D2_B27D_00600840D054__INCLUDED_)
