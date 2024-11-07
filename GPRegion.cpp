// GPRegion.cpp: implementation of the GPRegion class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPRegion.h"
#include "GPRegionArr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


const UINT GPRegion::uNMethods=17;
const char *GPRegion::cArrMethods[]={
		"SetName","CreateCombineRgn","CreateEllipticRgn","CreateEllipticRgnIndirect","CreatePolygonRgn",
		"CreatePolyPolygonRgn","CreateRectRgn","CreateRectRgnIndirect","CreateRoundRectRgn","ExtCreateRegion",
		"SetRectRgn","EqualRgn","GetRgnBox","OffsetRgn","PtInRegion",
		"RectInRegion","CombineRegion","","","",
		"","",
		"","","", "", "", 
	};
const char *GPRegion::cArrMethodsParams[]={
		"Name","RgnName1,RgnName2,CombineMode","Left,Top,Right,Bottom","Left,Top,Right,Bottom","Mode,X1,Y1^X2,Y2^...",
		"Mode,arrXY1;arrXY2;....;arrXY<n>","Left,Top,Right,Bottom","Left,Top,Right,Bottom","Left,Top,Right,Bottom, WidthEllipse,HeightEllipse","SrcRgnName,eM11,eM12,eM21,eM22,eDx,eDy",
		"Left,Top,Right,Bottom","RgnName","","XOffset,YOffset","X,Y",
		"Left,Top,Right,Bottom","RgnName,CombineMode","","","",
		"","",
		"","","", "", "", 
	};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPRegion::GPRegion(const char *iName)
{
	Name=iName;m_rgn=NULL;
}

GPRegion::~GPRegion()
{
	if (m_rgn!=NULL)
		DeleteObject(m_rgn);
	m_rgn=NULL;
}

const CString GPRegion::SetName(const char *iName)
{
	CString tmp=Name;
	Name=iName;

	return tmp;
}

const CString GPRegion::GetName()
{
	return Name;
}


HRGN GPRegion::CreateCombineRgn(HRGN hrgnSrc1, HRGN hrgnSrc2, int fnCombineMode)
{
	if (m_rgn==NULL) m_rgn=::CreateRectRgn(0,0,1,1);
	::CombineRgn(m_rgn,hrgnSrc1,hrgnSrc2,fnCombineMode);
	return m_rgn;
}

HRGN GPRegion::CreateEllipticRgn(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect)
{
	if (m_rgn!=NULL) DeleteObject(m_rgn);
	m_rgn=::CreateEllipticRgn(nLeftRect, nTopRect, nRightRect, nBottomRect);
	return m_rgn;
}

HRGN GPRegion::CreateEllipticRgnIndirect(CONST RECT *lprc)
{
	if (m_rgn!=NULL) DeleteObject(m_rgn);
	m_rgn=::CreateEllipticRgnIndirect(lprc);
	return m_rgn;
}

HRGN GPRegion::CreatePolygonRgn(CONST POINT *lppt, int cPoints, int fnPolyFillMode)
{
	if (m_rgn!=NULL) DeleteObject(m_rgn);
	m_rgn=::CreatePolygonRgn(lppt, cPoints, fnPolyFillMode);
	return m_rgn;
}

HRGN GPRegion::CreatePolyPolygonRgn(CONST POINT *lppt, CONST INT *lpPolyCounts, int nCount, int fnPolyFillMode)
{
	if (m_rgn!=NULL) DeleteObject(m_rgn);
	m_rgn=::CreatePolyPolygonRgn(lppt, lpPolyCounts, nCount, fnPolyFillMode);
	return m_rgn;
}

HRGN GPRegion::CreateRectRgn(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect)
{
	if (m_rgn!=NULL) DeleteObject(m_rgn);
	m_rgn=::CreateRectRgn(nLeftRect, nTopRect, nRightRect, nBottomRect);
	return m_rgn;
}

HRGN GPRegion::CreateRectRgnIndirect(CONST RECT *lprc)
{
	if (m_rgn!=NULL) DeleteObject(m_rgn);
	m_rgn=::CreateRectRgnIndirect(lprc);
	return m_rgn;
}

HRGN GPRegion::CreateRoundRectRgn(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nWidthEllipse, int nHeightEllipse)
{
	if (m_rgn!=NULL) DeleteObject(m_rgn);
	m_rgn=::CreateRoundRectRgn(nLeftRect, nTopRect, nRightRect, nBottomRect, nWidthEllipse, nHeightEllipse);
	return m_rgn;
}

HRGN GPRegion::ExtCreateRegion(CONST XFORM *lpXform, DWORD nCount, CONST RGNDATA *lpRgnData)
{
	if (m_rgn!=NULL) DeleteObject(m_rgn);
	m_rgn=::ExtCreateRegion(lpXform, nCount, lpRgnData);
	return m_rgn;
}

HRGN GPRegion::SetRectRgn(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect  )
{
	::SetRectRgn(m_rgn, nLeftRect, nTopRect, nRightRect, nBottomRect);
	return m_rgn;
}

BOOL GPRegion::EqualRgn(HRGN hrgnSrc)
{
	BOOL ret=m_rgn==hrgnSrc;
	if (hrgnSrc && m_rgn) ret=::EqualRgn(m_rgn, hrgnSrc);

	return ret;
}

BOOL GPRegion::FillRgn(HDC hdc, HBRUSH hbr)
{
	return ::FillRgn(hdc, m_rgn, hbr);
}

BOOL GPRegion::FrameRgn(HDC hdc, HBRUSH hbr, int nWidth, int nHeight)
{
	return ::FrameRgn(hdc, m_rgn, hbr, nWidth, nHeight);
}

DWORD GPRegion::GetRegionData(DWORD dwCount, LPRGNDATA lpRgnData)
{
	return ::GetRegionData(m_rgn, dwCount, lpRgnData);
}

int GPRegion::GetRgnBox(LPRECT lprc)
{
	return ::GetRgnBox(m_rgn, lprc);
}

BOOL GPRegion::InvertRgn(HDC hdc)
{
	return ::InvertRgn(hdc, m_rgn);
}

int GPRegion::OffsetRgn(int nXOffset, int nYOffset)
{
	return ::OffsetRgn(m_rgn, nXOffset, nYOffset);
}

BOOL GPRegion::PaintRgn(HDC hdc)
{
	return ::PaintRgn(hdc, m_rgn);
}

BOOL GPRegion::PtInRegion(int X, int Y)
{
	return ::PtInRegion(m_rgn, X, Y);
}

BOOL GPRegion::RectInRegion(CONST RECT *lprc)
{
	return ::RectInRegion(m_rgn, lprc);
}


UINT GPRegion::DoMethod(const char *iStr, char *oStr, void *GPRArray)
{
	char *strmet=new char [(int)strlen(iStr)+50];
	strcpy(strmet,iStr);

	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(strmet,' ')=0;
	else		pos="";	

	int nfunc=0;
	int retint=-123456; 
	
	if (*strmet>='0' && *strmet<='9') nfunc=atoi(strmet);
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
		nfunc=scdMethodsId[FindInSortArrayIC(strmet, sccArrMethods, uNMethods)];
	}

	switch(nfunc)
	{
	case 0: /*SetName*/	if (*pos!=0) Name=pos; break;
	case 1: /*CreateCombineRgn*/
		if (GPRArray!=NULL)
		{
			HRGN rg1=NULL,rg2=NULL;
			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
			char *postmp=pos333,*pos2;

			if ((postmp=strchr(postmp,','))!=NULL) *(postmp++)=0;
			else postmp="";
			rg1=((GPRegionArr *)GPRArray)->GetRgn(pos333)->GetHRGN();
			pos2=postmp;
			if ((postmp=strchr(postmp,','))!=NULL) *(postmp++)=0;
			else postmp="";
			rg2=((GPRegionArr *)GPRArray)->GetRgn(pos2)->GetHRGN();
			if (rg1 && rg2)	CreateCombineRgn(rg1, rg2,TranslateCombineMode(postmp));
			delete[] pos333;
		}
		break;
	case 2: /*CreateEllipticRgn Left,Top,Right,Bottom*/
	case 3: /*CreateEllipticRgnIndirect Left,Top,Right,Bottom*/
	case 6: /*CreateRectRgn Left,Top,Right,Bottom*/
	case 7: /*CreateRectRgnIndirect Left,Top,Right,Bottom*/
	case 10: /*SetRectRgn Left,Top,Right,Bottom*/
		{
			int Left=0,Top=0,Right=0,Bottom=0;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&Left,&Top,&Right,&Bottom);
			switch(nfunc)
			{
			case 2:		CreateEllipticRgn(Left,Top,Right,Bottom);				break;
			case 3:		CreateEllipticRgnIndirect(CRect(Left,Top,Right,Bottom));break;
			case 6:		CreateRectRgn(Left,Top,Right,Bottom);					break;
			case 7:		CreateRectRgnIndirect(CRect(Left,Top,Right,Bottom));	break;
			case 10:	SetRectRgn(Left,Top,Right,Bottom);						break;
			}
		}
		break;
	case 4: /*CreatePolygonRgn*/
		{
			const char *pos2=strchr(pos,',');
			if (pos2++==NULL) pos2="";
			int nPoints=0;
			do	nPoints++;
			while((pos2=strchr(++pos2,GPC.DelimiterIn1))!=NULL);
			POINT *lpoMain=new POINT [nPoints+5];
			POINT *lpo=lpoMain;
			
			pos2=strchr(pos,',');
			if (pos2++==NULL) pos2="";

			pos2--;
			do	
			{
				lpo->x=lpo->y=0;
				m_LastScanf=sscanf(++pos2,"%d,%d",&lpo->x,&lpo->y);
				lpo++;
			}
			while((pos2=strchr(pos2,GPC.DelimiterIn1))!=NULL);

			CreatePolygonRgn(lpoMain,nPoints,strstr(pos,"AL")!=NULL?ALTERNATE:WINDING);
			delete[] lpoMain;
		}
		break;
	case 5: /*CreatePolyPolygonRgn arrXY1;arrXY2;....;arrXY<n>*/
		{
			char *postmpcc=new char [(int)strlen(pos)+10];
			strcpy(postmpcc,pos);

			char *pos2=strchr(postmpcc,',');
			if (pos2++==NULL) pos2="";
			int nAll=0;
			int nGroup=0;
			do		nAll++;
			while((pos2=strchr(++pos2,';'))!=NULL);
			pos2=postmpcc;

			nGroup=nAll;

			do		nAll++;
			while((pos2=strchr(++pos2,GPC.DelimiterIn1))!=NULL);

			nAll--;
			POINT *lpo=new POINT [nAll];
			INT *lpPolyCounts=new INT [nGroup];
			INT *iCnt=lpPolyCounts;

			char *pos3=strchr(postmpcc,',');
			if (pos3++==NULL) pos3="";
			pos3--;
			
			do	
			{
				pos2=pos3++;
				*iCnt=0;
				char *posNULL=strchr(pos3,';');
				if (posNULL!=NULL) *posNULL=0;
				do	
				{
					lpo->x=lpo->y=0;
					m_LastScanf=sscanf(++pos2,"%d,%d",&lpo->x,&lpo->y);
					*iCnt=*iCnt+1;
					lpo++;
				}
				while((pos2=strchr(pos2,GPC.DelimiterIn1))!=NULL);
				iCnt++;
				if (posNULL!=NULL) *posNULL=';';
			}
			while((pos3=strchr(pos3,';'))!=NULL);

			CreatePolyPolygonRgn(lpo,lpPolyCounts,nGroup,strstr(postmpcc,"AL")!=NULL?ALTERNATE:WINDING);

			delete[] lpo;
			delete[] lpPolyCounts;
			delete[] postmpcc;
		}
		break;
	case 8: /*CreateRoundRectRgn*/
		{
			int Left=0,Top=0,Right=0,Bottom=0,nWidthEllipse=0,nHeightEllipse=0;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d,%d",&Left,&Top,&Right,&Bottom,&nWidthEllipse,&nHeightEllipse);
			CreateRoundRectRgn(Left,Top,Right,Bottom,nWidthEllipse,nHeightEllipse);
		}
		break;
	case 9: /*ExtCreateRegion SrcRgnName,eM11,eM12,eM21,eM22,eDx,eDy*/
		if (GPRArray!=NULL)
		{
			char *postmpcc=new char [(int)strlen(pos)+10];
			strcpy(postmpcc,pos);
			char *pos2;
			if ((pos2=strchr(postmpcc,','))!=NULL) *(pos2++)=0;
			else pos2="";

			HRGN rg1=((GPRegionArr *)GPRArray)->GetRgn(postmpcc)->GetHRGN();

			if (rg1)
			{
				DWORD nb=::GetRegionData(rg1,0,NULL);
				if (nb>0)
				{
					BYTE *bt=new BYTE[nb+500];
					::GetRegionData(rg1,nb,(LPRGNDATA)bt);
					XFORM xf={0}; 
					m_LastScanf=sscanf(pos2,"%f,%f,%f,%f,%f,%f",&xf.eM11,&xf.eM12,&xf.eM21,&xf.eM22,&xf.eDx,&xf.eDy);
					ExtCreateRegion(&xf,nb,(LPRGNDATA)bt);
					delete[] bt;
				}
			}
			delete[] postmpcc;
		}
		break;
	case 11: /*EqualRgn*/
		if (GPRArray!=NULL)
		{
			HRGN rg1=((GPRegionArr *)GPRArray)->GetRgn(pos)->GetHRGN();
			retint=EqualRgn(rg1);
		}
		break;
	case 12: /*GetRgnBox*/
		if (oStr!=NULL)
		{
			RECT re;
			GetRgnBox(&re);
			sprintf(oStr,"%d,%d,%d,%d",re.left,re.top,re.right,re.bottom);
		}
		break;
	case 13: /*OffsetRgn*/
		{
			int X=0,Y=0;
			m_LastScanf=sscanf(pos,"%d,%d",&X,&Y);
			retint=OffsetRgn(X,Y);
		}
		break;
	case 14: /*PtInRegion*/
		{
			int X=0,Y=0;
			m_LastScanf=sscanf(pos,"%d,%d",&X,&Y);
			retint=PtInRegion(X,Y);
		}
		break;
	case 15: /*RectInRegion*/
		{
			int Left=0,Top=0,Right=0,Bottom=0;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&Left,&Top,&Right,&Bottom);
			retint=RectInRegion(CRect(Left,Top,Right,Bottom));
		}
		break;
	case 16: /*CombineRgn*/
		if (GPRArray!=NULL)
		{
			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
			HRGN rg1=NULL;
			char *postmp=pos333;
			if ((postmp=strchr(postmp,','))!=NULL) *(postmp++)=0;
			else postmp="";

			rg1=((GPRegionArr *)GPRArray)->GetRgn(pos333)->GetHRGN();
			if (rg1) CombineRgn(rg1,TranslateCombineMode(postmp));
			delete[] pos333;
		}
		break;


	default:
		GPC.m_ErrReport.GPWriteWarnLog2("GPRegion", "Unknown Method",iStr);
		if (oStr!=NULL) sprintf(oStr,ErrObjSub,strmet);nfunc=0xFFFFFFFFL;
		break;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);

	delete[] strmet;
	return nfunc;
}


long GPRegion::TranslateCombineMode(const char * iStr)
{
	const char *nm[5]={
			"AND","COPY","DIFF","XOR","OR",
		};
	const UINT uin[5]={
			RGN_AND,RGN_COPY,RGN_DIFF,RGN_XOR,RGN_OR,
		};

	long ret=RGN_OR;
	char *buff=new char [(int)strlen(iStr)+10];
	strcpy(buff,iStr);
	_strupr(buff);

	int i;
	for(i=0;i<5;i++)
		if (strstr(buff,nm[i])!=NULL)	{ret=uin[i];break;}

	delete[] buff;
	return ret;
}

HRGN GPRegion::GetHRGN() 
{
	return m_rgn;
}

HRGN GPRegion::CombineRgn(HRGN hrgnSrc1, int fnCombineMode)
{
	if (m_rgn==NULL) m_rgn=::CreateRectRgn(0,0,1,1);
	::CombineRgn(m_rgn,hrgnSrc1,m_rgn,fnCombineMode);
	return m_rgn;
}
