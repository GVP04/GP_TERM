// GPFont.cpp: implementation of the GPFont class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GP_term.h"
#include "GP_TermView.h"
//#include "GPFont.h"
#include <io.h>
#include <direct.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define MAX_FONT_COUNT 5000

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const char *GPFont::cArrStyles2[]={
	"REG","UN","ST","IT","BO",
	"SE","F","BL","LIG","CO",
	"TRA","D1","D2","D3","D4",
	"D5","D6","D7","D8",
	"",
};

const char *GPFont::cArrStyles[]={
	"REGULAR","UNDERLINE","STRIKEOUT","ITALIC","BOLD",
	"SELECTED","FIXED","BLINKED","LIGHT","CODES",
	"TRANSPARENT","SHADOWED1","SHADOWED2","SHADOWED3","SHADOWED4",
	"SHADOWED5","SHADOWED6","SHADOWED7","SHADOWED8",
	"",
};

const GP_FNT GPFont::uArrStyles[]={
	GP_FNT_REGULAR,GP_FNT_UNDERLINE,GP_FNT_STRIKE,GP_FNT_ITALIC,GP_FNT_BOLD,
	GP_FNT_SELECTION,GP_FNT_FIXED,GP_FNT_BLINK,GP_FNT_LIGHT,GP_FNT_CODE,
	GP_FNT_OPAQUE,GP_FNT_SHADOW1,GP_FNT_SHADOW2,GP_FNT_SHADOW3,GP_FNT_SHADOW4,
	GP_FNT_SHADOW5,GP_FNT_SHADOW6,GP_FNT_SHADOW7,GP_FNT_SHADOW8,
	GP_FNT_REGULAR,
};

DWORD GPFont::TranslateCharStyle(const char *iStr)
{
	DWORD ret=0;
	CString tmpCS=iStr;
	tmpCS.MakeUpper();

	int i;
	ret=atoi(iStr);
	const char *tmpp=strstr(iStr,"0x");
	if (!tmpp) tmpp=strstr(iStr,"0X");
	if (tmpp) sscanf(tmpp+2,"%X",&ret);
	
	for(i=0;*GPFont::cArrStyles2[i];i++)
		if (tmpCS.Find(GPFont::cArrStyles2[i],0)>=0) ret|=GPFont::uArrStyles[i];
	return ret;
}

CString GPFont::TranslateCharStyle(DWORD dwiStyle)
{
	CString ret;
	int i;
	for(i=1;*GPFont::cArrStyles2[i];i++)
		if (!(GPFont::uArrStyles[i]&GP_FNT_SHADOWMASK) && (dwiStyle&GPFont::uArrStyles[i])==GPFont::uArrStyles[i])
		{
			if (ret!="") ret+="|";
			ret+=GPFont::cArrStyles[i];
		}
	if ((dwiStyle&GP_FNT_SHADOWMASK))
	{
		if (ret!="") ret+="|";
		for(i=1;*GPFont::cArrStyles2[i];i++)
			if ((GPFont::uArrStyles[i]&GP_FNT_SHADOWMASK) && (dwiStyle&GP_FNT_SHADOWMASK)==GPFont::uArrStyles[i])
			{
				if (ret!="") ret+="|";
				ret+=GPFont::cArrStyles[i];
			}
	}
	return ret;
}


GPFont::GPFont()
{
	fnt=new Font * [GP_FNT_MAXCNT];
	ZeroMemory(fnt,sizeof(Font *)*GP_FNT_MAXCNT);
	wcscpy(familyName,L"Courier");

	DeltaWidthUC=0;
	DeltaHeightUC=0;
	maxWidth=0;
	maxHeight=0;
	REAL MaxX=10000;
	REAL MinX=(REAL)0.01;

}

GPFont::~GPFont()
{
	DeleteFontTable();
	if (fnt) delete fnt;
	fnt=NULL;
}

const Font *GPFont::InitFontTable(const char * iFamilyName, GPScreen *pScr)
{
	WCHAR tmpWC[250];
	MultiByteToWideChar(CP_ACP, 0,iFamilyName, -1, tmpWC, 200);

	return InitFontTable(tmpWC, pScr);
}
const Font *GPFont::InitFontTable(WCHAR * iFamilyName, GPScreen *pScr)
{
	EnterCriticalSection(&GPC.m_View->m_CSRefresh);
	try
	{
	DeleteFontTable();
	wcscpy(familyName,iFamilyName);

	*fnt=new Font(familyName,100,FontStyleRegular,UnitPoint,NULL);
	if (!(*fnt) || (*fnt)->GetLastStatus()!=0)
	{
		if (*fnt) delete *fnt;
		wcscpy(familyName,L"Courier");
		*fnt=new Font(familyName,100,FontStyleRegular,UnitPoint,NULL);
	}
	if (*fnt)
	{
		int nn;
		maxWidth=0;
		maxHeight=0;
		PointF origin(0,0);
		HDC m_HDC=::GetDC(GPC.m_hViewWnd);
		if (m_HDC)
		{
		StringFormat sFormat(0,(LANGID)GPC.m_CONV3SRVPC.dwLang);
	//	sFormat.SetLineAlignment(StringAlignmentCenter);
	//	sFormat.SetAlignment(StringAlignmentCenter);
			Graphics gr(m_HDC);
			RectF boundingBox;
			RectF boundingBox2;
			for(nn=33;nn<256;nn++)
			{
				WCHAR tmpWText2[10]={0,0,};
				char cc[4];
				cc[0]=nn;cc[1]=0;
				MultiByteToWideChar(CP_ACP, 0,cc , 1, tmpWText2, 2);
				tmpWText2[1]=0;
				boundingBox2.Height=boundingBox.Height=boundingBox2.Width=boundingBox.Width=500;
				gr.MeasureString( tmpWText2,1, *fnt, origin, &sFormat, &boundingBox2);
				cc[1]=nn;cc[2]=0;
				MultiByteToWideChar(CP_ACP, 0,cc , 2, tmpWText2, 4);
				tmpWText2[2]=0;
				gr.MeasureString( tmpWText2,2, *fnt, origin, &sFormat, &boundingBox);
				boundingBox.Width-=boundingBox2.Width;
				if (maxWidth<boundingBox.Width)	  maxWidth=boundingBox.Width;
				if (maxHeight<boundingBox.Height) maxHeight=boundingBox.Height;
			}
			if (pScr)
			{
				maxWidth-=pScr->FontDeltaX;
				maxHeight-=pScr->FontDeltaY;
			}
			else
			{
				maxWidth-=GPScreen::ScrFontDeltaX;
				maxHeight-=GPScreen::ScrFontDeltaY;
			}

			FontFamily ff;
			(*fnt)->GetFamily(&ff);
			DeltaHeightUC=100*(REAL)ff.GetCellDescent(FontStyleRegular)/(REAL)ff.GetEmHeight(FontStyleRegular);
			maxHeight-=DeltaHeightUC/2;
		}
		::ReleaseDC(GPC.m_hViewWnd,m_HDC);
	}
	}catch(...)
	{;}
	LeaveCriticalSection(&GPC.m_View->m_CSRefresh);
	return *fnt;
}

const Font * GPFont::GetFont(DWORD dwType)
{
	const Font *ret=*fnt;
	DWORD dwStl=dwType&GP_FNT_STYLEMASK;
	if (fnt[dwStl]) ret=fnt[dwStl];
	else
	{
		fnt[dwStl]=new Font(familyName,100,dwStl,UnitPoint,NULL);
		if (!fnt[dwStl] || fnt[dwStl]->GetLastStatus()!=0) ret=*fnt;
	}
	return ret;
}


void GPFont::DeleteFontTable()
{
	UINT i;
	if (fnt)
		for(i=0; i<GP_FNT_MAXCNT; i++) 
		{
			if (fnt[i]) delete fnt[i];
			fnt[i]=NULL;
		}
}


