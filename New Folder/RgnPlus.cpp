// RgnPlus.cpp: implementation of the CRgnPlus class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "RgnPlus.h"
#include "GP_TermView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//const char *CRgnPlus::ccA[]={"","","","","","","",};
//const DWORD CRgnPlus::iA[]={,,,,,,,0,};

const UINT CRgnPlus::uNMethods=30;
const char *CRgnPlus::cArrMethods[]={
/*00*/		"ComplementPath","ComplementRegion","ComplementRectN","ExcludePath","ExcludeRegion",
/*05*/		"ExcludeRectN","IntersectPath","IntersectRegion","IntersectRectN","UnionPath",
/*10*/		"UnionRegion","UnionRectN","XorPath","XorRegion","XorRectN",
/*15*/		"ComplementRect","ExcludeRect","IntersectRect","UnionRect","XorRect",
/*20*/		"GetData","GetDataSize","GetLastStatus","MakeEmpty","MakeInfinite",
/*25*/		"Transform","GetRegionScansCount","GetRegionScans","Translate","TranslateP",
/*30*/		"","","","","",
/*35*/		"","","","","",
	};
const char *CRgnPlus::cArrMethodsParams[]={
/*00*/		"ContextName,ObjetNum","ContextName,ObjetNum","ContextName,ObjetNum","ContextName,ObjetNum","ContextName,ObjetNum",
/*05*/		"ContextName,ObjetNum","ContextName,ObjetNum","ContextName,ObjetNum","ContextName,ObjetNum","ContextName,ObjetNum",
/*10*/		"ContextName,ObjetNum","ContextName,ObjetNum","ContextName,ObjetNum","ContextName,ObjetNum","ContextName,ObjetNum",
/*15*/		"X,Y,CY,CY","X,Y,CY,CY","X,Y,CY,CY","X,Y,CY,CY","X,Y,CY,CY",
/*20*/		"","","","","",
/*25*/		"m11,m12,m21,m22,dx,dy","m11,m12,m21,m22,dx,dy","m11,m12,m21,m22,dx,dy","sx,sy","ContextName,ObjetNum",
/*30*/		"","","","","",
/*35*/		"","","","","",
	};


CRgnPlus::CRgnPlus(CODContext *ip_Context)
{
	m_Rgn=new Region();
	p_Context=ip_Context;
}

CRgnPlus::CRgnPlus(CODContext *ip_Context, const char *iStr)
{
	if (iStr && *iStr)
	{
		RectF Re(0,0,0,0);
		sscanf(iStr,"%g,%g,%g,%g",&Re.X,&Re.Y,&Re.Width,&Re.Height);
		m_Rgn= new Region(Re);
	}
	else
		m_Rgn=new Region();
	p_Context=ip_Context;
}

CRgnPlus::CRgnPlus(CODContext *ip_Context, const Rect &rect)
{
	m_Rgn=new Region(rect);
	p_Context=ip_Context;
}
CRgnPlus::CRgnPlus(CODContext *ip_Context, const BYTE *regionData,INT size)
{
	m_Rgn=new Region(regionData, size);
	p_Context=ip_Context;
}
CRgnPlus::CRgnPlus(CODContext *ip_Context, const GraphicsPath *path)
{
	m_Rgn=new Region(path);
	p_Context=ip_Context;
}
CRgnPlus::CRgnPlus(CODContext *ip_Context, HRGN hRgn)
{
	m_Rgn=new Region(hRgn);
	p_Context=ip_Context;
}
CRgnPlus::CRgnPlus(CODContext *ip_Context, const RectF &rect)
{
	m_Rgn=new Region(rect);
	p_Context=ip_Context;
}

CRgnPlus::CRgnPlus(CODContext *ip_Context, IN const CRgnPlus *iRegion)
{
	if (iRegion)
		m_Rgn=iRegion->m_Rgn->Clone();
	else
		m_Rgn=new Region();
	p_Context=ip_Context;
}

CRgnPlus::~CRgnPlus()
{
	p_Context=NULL;
}


UINT CRgnPlus::DoMethod(const char *iStr, char *oStr)
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
	case  0: //ComplementPath
	case  1: //ComplementRegion
	case  2: //ComplementRectN
	case  3: //ExcludePath
	case  4: //ExcludeRegion
	case  5: //ExcludeRectN
	case  6: //IntersectPath
	case  7: //IntersectRegion
	case  8: //IntersectRectN
	case  9: //UnionPath
	case 10: //UnionRegion
	case 11: //UnionRectN
	case 12: //XorPath
	case 13: //XorRegion
	case 14: //XorRectN
		{
			CString ContName=ExtractField(pos,1,",");
			CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
			UINT nObject=atoi(ExtractField(pos,2,","));
			if (ocontext)
				switch(nfunc)
				{
				case 0: //ComplementPath
					if (nObject < ocontext->m_nGraphPathArray && ocontext->m_GraphPathArr[nObject])
						m_Rgn->Complement(ocontext->m_GraphPathArr[nObject]->m_GraphicsPath);
					break;
				case 1: //ComplementRegion
					if (nObject < ocontext->m_nRgnArray && ocontext->m_RgnArr[nObject])
						m_Rgn->Complement(ocontext->m_RgnArr[nObject]->m_Rgn);
					break;
				case 3: //ExcludePath
					if (nObject < ocontext->m_nGraphPathArray && ocontext->m_GraphPathArr[nObject])
						m_Rgn->Exclude(ocontext->m_GraphPathArr[nObject]->m_GraphicsPath);
					break;
				case 4: //ExcludeRegion
					if (nObject < ocontext->m_nRgnArray && ocontext->m_RgnArr[nObject])
						m_Rgn->Exclude(ocontext->m_RgnArr[nObject]->m_Rgn);
					break;
				case  6: //IntersectPath
					if (nObject < ocontext->m_nGraphPathArray && ocontext->m_GraphPathArr[nObject])
						m_Rgn->Intersect(ocontext->m_GraphPathArr[nObject]->m_GraphicsPath);
					break;
				case  7: //IntersectRegion
					if (nObject < ocontext->m_nRgnArray && ocontext->m_RgnArr[nObject])
						m_Rgn->Intersect(ocontext->m_RgnArr[nObject]->m_Rgn);
					break;
				case  9: //UnionPath
					if (nObject < ocontext->m_nGraphPathArray && ocontext->m_GraphPathArr[nObject])
						m_Rgn->Union(ocontext->m_GraphPathArr[nObject]->m_GraphicsPath);
					break;
				case  10: //UnionRegion
					if (nObject < ocontext->m_nRgnArray && ocontext->m_RgnArr[nObject])
						m_Rgn->Union(ocontext->m_RgnArr[nObject]->m_Rgn);
					break;
				case  12: //XorPath
					if (nObject < ocontext->m_nGraphPathArray && ocontext->m_GraphPathArr[nObject])
						m_Rgn->Xor(ocontext->m_GraphPathArr[nObject]->m_GraphicsPath);
					break;
				case  13: //XorRegion
					if (nObject < ocontext->m_nRgnArray && ocontext->m_RgnArr[nObject])
						m_Rgn->Xor(ocontext->m_RgnArr[nObject]->m_Rgn);
					break;
				case 2: //ComplementRectN
				case 5: //ExcludeRectN
				case 8: //IntersectRectN
				case 11: //UnionRectN
				case 14: //XorRectN
					{
						int inRect=(int)nObject;
						if (inRect<0 && (UINT)(-inRect-1)*4<ocontext->m_nREALArray)
						{
							RectF Re(0,0,0,0);
							Re.X=ocontext->m_REALArr[-inRect-1];
							Re.Y=ocontext->m_REALArr[-inRect];
							Re.Width=ocontext->m_REALArr[-inRect+1];
							Re.Height=ocontext->m_REALArr[-inRect+2];
							if (nfunc==2)	m_Rgn->Complement(Re);
							else		
							if (nfunc==5)	m_Rgn->Exclude(Re);
							else		
							if (nfunc==8)	m_Rgn->Intersect(Re);
							else		
							if (nfunc==11)	m_Rgn->Union(Re);
							else		
							if (nfunc==14)	m_Rgn->Xor(Re);
						}
						else
						if (nObject < ocontext->m_nRectArray)
						{
							if (nfunc==2)	m_Rgn->Complement(ocontext->m_RectArr[nObject]);
							else	
							if (nfunc==5)	m_Rgn->Exclude(ocontext->m_RectArr[nObject]);
							else	
							if (nfunc==8)	m_Rgn->Intersect(ocontext->m_RectArr[nObject]);
							else	
							if (nfunc==11)	m_Rgn->Union(ocontext->m_RectArr[nObject]);
							else	
							if (nfunc==14)	m_Rgn->Xor(ocontext->m_RectArr[nObject]);
						}
					}
					break;
				}
		}
		break; 
	case 15: //ComplementRect
	case 16: //ExcludeRect
	case 17: //IntersectRect
	case 18: //UnionRect
	case 19: //XorRect
		{
			REAL X1=0,Y1=0,X2=0,Y2=0;
			sscanf(pos,"%g,%g,%g,%g",&X1,&Y1,&X2,&Y2);
			switch(nfunc)
			{
			case 15: //ComplementRect
				m_Rgn->Complement(RectF(X1,Y1,X2,Y2));
				break;
			case 16: //ExcludeRect
				m_Rgn->Exclude(RectF(X1,Y1,X2,Y2));
				break;
			case 17: //IntersectRect
				m_Rgn->Intersect(RectF(X1,Y1,X2,Y2));
				break;
			case 18: //UnionRect
				m_Rgn->Union(RectF(X1,Y1,X2,Y2));
				break;
			case 19: //XorRect
				m_Rgn->Xor(RectF(X1,Y1,X2,Y2));
				break;
			}
		}
		break; 
	case  20: //GetData
		if (oStr)
		{
			UINT dataSize=m_Rgn->GetDataSize();
			BYTE *m_Buff=new BYTE[dataSize+100];
			UINT SizeFilled=0;
			m_Rgn->GetData(m_Buff,dataSize,&SizeFilled);
			char *posout=oStr;
			BYTE *m_Buff2=m_Buff;
			while(SizeFilled>0)
			{
				DWORD dw=(*(m_Buff2++))&0xFF;
				DWORD dw2=dw/0x10;
				dw&=0xF;
				if (dw2>9)	*(posout++)=(char)('A'-10+dw2);
				else		*(posout++)=(char)('0'+dw2);
				if (dw>9)	*(posout++)=(char)('A'-10+dw);
				else		*(posout++)=(char)('0'+dw);
			}
			delete []m_Buff;
		}
		break; 
	case 21: //GetDataSize
		retint=m_Rgn->GetDataSize();
		break; 
	case 22: //GetLastStatus
		retint=m_Rgn->GetLastStatus();
		break; 
	case 23: //MakeEmpty
		retint=m_Rgn->MakeEmpty();
		break; 
	case 24: //MakeInfinite
		retint=m_Rgn->MakeInfinite();
		break; 
	case 25: //Transform
	case 26: //GetRegionScansCount
	case 27: //GetRegionScans
		{
			Matrix ma;
			DWORD dwOrder=0;
			REAL rea[10]={0};
			sscanf(pos,"%g,%g,%g,%g,%g,%g",rea,rea+1,rea+2,rea+3,rea+4,rea+5);
			ma.SetElements(rea[0],rea[1],rea[2],rea[3],rea[4],rea[5]);
			if (nfunc==25)		
				retint=m_Rgn->Transform(&ma);
			else
			if (nfunc==26)		
				retint=m_Rgn->GetRegionScansCount(&ma);
			else
			if (nfunc==26)	
			{
				if (oStr)
				{
					INT nrect=m_Rgn->GetRegionScansCount(&ma);
					RectF *mrectf = new RectF[nrect+10];
					m_Rgn->GetRegionScans(&ma,mrectf,&nrect);
					char *posout=oStr;
					for(i=0;i<nrect;i++)
					{
						if (posout!=oStr) {*(posout++)=0x7F;*posout=0;}
						posout+=sprintf(posout,"%g\x7%g\x7%g\x7%g",mrectf[i].X,mrectf[i].Y,mrectf[i].Width,mrectf[i].Height);
					}
					delete []mrectf;
				}
			}
		}
		break; 
	case 28: //Translate
		{
			REAL sx=0;
			REAL sy=0;
			sscanf(pos,"%g,%g",&sx,&sy);
			retint=m_Rgn->Translate(sx,sy);
		}
		break; 
	case 29: //TranslateP
		{
			CString ContName=ExtractField(pos,1,",");
			CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
			UINT nObject=atoi(ExtractField(pos,2,","));
			if (ocontext && nObject<ocontext->m_nPointArray)
				retint=m_Rgn->Translate(ocontext->m_PointArr[nObject].X,ocontext->m_PointArr[nObject].Y);
		}
		break; 


/*
	case  0: //
Region::IsVisible(PointF&,Graphics*) The IsVisible method determines whether a point is inside this region. 
Region::IsVisible(RectF&,Graphics*) The IsVisible method determines whether a rectangle intersects this region. 
Region::IsVisible(Rect&,Graphics*) The IsVisible method determines whether a rectangle intersects this region. 
Region::IsVisible(INT,INT,Graphics*) The IsVisible method determines whether a point is inside this region. 
Region::IsVisible(REAL,REAL,Graphics*) The IsVisible method determines whether a point is inside this region. 
Region::IsVisible(INT,INT,INT,INT,Graphics*) The IsVisible method determines whether a rectangle intersects this region. 
Region::IsVisible(Point&,Graphics*) The IsVisible method determines whether a point is inside this region. 
Region::IsVisible(REAL,REAL,REAL,REAL,Graphics*) The IsVisible method determines whether a rectangle intersects this region. 
		break; 
*/
	default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
	}
	if (oStr && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);

	return nfunc;
}


