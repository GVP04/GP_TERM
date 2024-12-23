// GraphicsPathPlus.cpp: implementation of the CGraphicsPathPlus class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GP_TermView.h"
#include "GraphicsPathPlus.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//const char *CGraphicsPathPlus::ccA[]={"","","","","","","",};
//const DWORD CGraphicsPathPlus::iA[]={,,,,,,,0,};

const char *CGraphicsPathPlus::ccAFillMode[]={
	"Alternate","Winding",
	"FillModeAlternate","FillModeWinding",
	"","",};
const DWORD CGraphicsPathPlus::iAFillMode[]={
	FillModeAlternate,FillModeWinding,
	FillModeAlternate,FillModeWinding,
	FillModeAlternate,0,};

const char *CGraphicsPathPlus::ccAWarpMode[]={
	"Perspective","Bilinear",
	"WarpModePerspective","WarpModeBilinear",
	"","",};
const DWORD CGraphicsPathPlus::iAWarpMode[]={
	WarpModePerspective,WarpModeBilinear,
	WarpModePerspective,WarpModeBilinear,
	WarpModePerspective,0,};

const char *CGraphicsPathPlus::ccAPointType[]={
	"TypeStart","TypeLine","TypeBezier","TypePathTypeMask","TypeDashMode",
	"TypePathMarker","TypeCloseSubpath",
	"PathPointTypeStart","PathPointTypeLine","PathPointTypeBezier","PathPointTypePathTypeMask","PathPointTypeDashMode",
	"PathPointTypePathMarker","PathPointTypeCloseSubpath",
	"","",
};
const DWORD CGraphicsPathPlus::iAPointType[]={
	PathPointTypeStart,PathPointTypeLine,PathPointTypeBezier,PathPointTypePathTypeMask,PathPointTypeDashMode,
	PathPointTypePathMarker,PathPointTypeCloseSubpath,
	PathPointTypeStart,PathPointTypeLine,PathPointTypeBezier,PathPointTypePathTypeMask,PathPointTypeDashMode,
	PathPointTypePathMarker,PathPointTypeCloseSubpath,
	PathPointTypeStart,0,
};

const UINT CGraphicsPathPlus::uNMethods=53;
const char *CGraphicsPathPlus::cArrMethods[]={
/*00*/		"AddArc","AddArcR","AddBezier","AddBezierP","AddBeziers",
/*05*/		"AddClosedCurve","AddClosedCurveEx","AddCurve","AddCurveEx","AddLines",
/*10*/		"AddBeziersP","AddClosedCurveP","AddClosedCurvePEx","AddCurveP","AddCurvePEx",
/*15*/		"AddLinesP","AddEllipse","AddEllipseR","AddLine","AddLineP",
/*20*/		"AddPath","AddPie","AddPieR","AddPolygon","AddPolygonP",
/*25*/		"AddRectangle","AddRectangleR","AddRectangles","AddRectanglesP","AddStringP",
/*30*/		"AddStringR","ClearMarkers","CloseAllFigures","CloseFigure","Flatten",
/*35*/		"GetBounds","GetFillMode","GetLastPoint","GetLastStatus","GetPointCount",
/*40*/		"GetPathData","GetPathPoints","GetPathTypes","Outline","Reset",
/*45*/		"Reverse","SetFillMode","SetMarker","StartFigure","Transform",
/*50*/		"Warp","WarpR","Widen","","",
/*55*/		"","","","","",
/*60*/		"","","","","",
/*65*/		"","","","","",
	};
const char *CGraphicsPathPlus::cArrMethodsParams[]={
/*00*/		"x,y,width,height,startAngle,sweepAngle","ContextName,nRect,startAngle,sweepAngle","x1,y1,x2,y2,x3,y3,x4,y4","ContextName,nPoint1,nPoint2,nPoint3,nPoint4","X1,Y1;X2,Y2;X3,Y3;X4,Y4[;....]",
/*05*/		"X1,Y1;X2,Y2;X3,Y3;X4,Y4[;....]","tension,X1,Y1;X2,Y2;X3,Y3;X4,Y4[;....]","X1,Y1;X2,Y2;X3,Y3;X4,Y4[;....]","tension,X1,Y1;X2,Y2;X3,Y3;X4,Y4[;....]","X1,Y1;X2,Y2[;....]",
/*10*/		"ContextName,nPoint1,nPoint2,nPoint3,nPoint4[,....]","ContextName,nPoint1,nPoint2,nPoint3,nPoint4[,....]","ContextName,tension,nPoint1,nPoint2,nPoint3,nPoint4[,....]","ContextName,nPoint1,nPoint2,nPoint3,nPoint4[,....]","ContextName,tension,nPoint1,nPoint2,nPoint3,nPoint4[,....]",
/*15*/		"ContextName,nPoint1,nPoint2[,....]","x,y,width,height","ContextName,nRect","x1,y1,x2,y2","ContextName,nPoint1,nPoint2",
/*20*/		"ContextName,nPath,bConnect","x,y,width,height,startAngle,sweepAngle","ContextName,nRect,startAngle,sweepAngle","X1,Y1;X2,Y2;X3,Y3[;....]","ContextName,nPoint1,nPoint2,nPoint3,nPoint4[,....]",
/*25*/		"x,y,width,height","ContextName,nRect","x1,y1,width11,height1;x2,y2,width12,height2[;....]","ContextName,nRect1,nRect2[,....]","ContextName,nFont,nFormat,nPoint,emSize,style,language;String",
/*30*/		"ContextName,nFont,nFormat,nRect,emSize,style,language;String","","","","[flatness,m11,m12,m21,m22,dx,dy]",
/*35*/		"[ContextName],[nPen],[m11,m12,m21,m22,dx,dy]","","","","",
/*40*/		"","","","[flatness,m11,m12,m21,m22,dx,dy]","",
/*45*/		"","FillMode","","","m11,m12,m21,m22,dx,dy",
/*50*/		"X,Y,CX,CY,[warpMode],[flatness][,m11,m12,m21,m22,dx,dy];X1,Y1;X2,Y2[;....]","ContextName,nRect,[warpMode],[flatness][,m11,m12,m21,m22,dx,dy];X1,Y1;X2,Y2[;....]","ContextName,nPen,[flatness],[m11,m12,m21,m22,dx,dy]","","",
/*55*/		"","","","","",
/*60*/		"","","","","",
/*65*/		"","","","","",
	};

CGraphicsPathPlus::CGraphicsPathPlus(CODContext *ip_Context, const Point *points,  const BYTE *types, INT count,  FillMode fillMode)
{
	p_Context=ip_Context;
	m_GraphicsPath=new GraphicsPath(points, types, count, fillMode);
}

CGraphicsPathPlus::CGraphicsPathPlus(CODContext *ip_Context, FillMode fillMode)
{
	p_Context=ip_Context;
	m_GraphicsPath=new GraphicsPath(fillMode);
}

CGraphicsPathPlus::CGraphicsPathPlus(CODContext *ip_Context, GraphicsPath *pGraphicsPath)
{
	p_Context=ip_Context;
	m_GraphicsPath=NULL;
	SetGraphicsPath(pGraphicsPath);
}

CGraphicsPathPlus::CGraphicsPathPlus(CODContext *ip_Context, const char *iStr)
{
	p_Context=ip_Context;
	if (iStr && *iStr)
	{
		DWORD dwFillMode=atoi(iStr);
		if (*iStr!='0' &&  dwFillMode==0)
		{
			CString tmpCS=ExtractField(iStr,1,";");
			tmpCS=ExtractField(tmpCS,1,",");
			int i;
			for(i=0; *ccAFillMode[i] && !dwFillMode;i++) 
				if (_stricmp(tmpCS,ccAFillMode[i])==0) dwFillMode=iAFillMode[i];
		}
		const char *pos=FindField(iStr,2,";");
		
		if (pos && *pos)
		{
			const char *pos2=pos;
			INT nPoints=1;
			while(pos2 && *pos2) 
				if ((pos2=strchr(pos2,';')))
				{nPoints++;pos2++;}
			PointF *points= new PointF[nPoints+5];
			BYTE *types=new BYTE[nPoints+5];
			INT nCurPoint=0;
			while(*pos)
			{
				CString tmpCS=ExtractField(pos,1,",");
				int i;
				types[nCurPoint]=atoi(pos);
				for(i=0; *ccAPointType[i] && !types[nCurPoint];i++) 
					if (_stricmp(tmpCS,ccAPointType[i])==0) types[nCurPoint]=(BYTE)iAPointType[i];

				while(*pos && *pos!=';' && *pos!=',') pos++;
				if (*pos==',')
				{
					pos++;
					points[nCurPoint].X=points[nCurPoint].Y=0;
					sscanf(pos,"%g,%g",&(points[nCurPoint].X),&(points[nCurPoint].Y));
				}
				nCurPoint++;
				while(*pos && *pos!=';') pos++;
				if (*pos) pos++;
			}
			m_GraphicsPath=new GraphicsPath(points, types, nPoints, (Gdiplus::FillMode)dwFillMode);
			delete []points;
			delete []types;
		}
		else
			m_GraphicsPath=new GraphicsPath((Gdiplus::FillMode)dwFillMode);
	}
	if (!m_GraphicsPath) m_GraphicsPath=new GraphicsPath(FillModeAlternate);
}

CGraphicsPathPlus::CGraphicsPathPlus(CODContext *ip_Context, const PointF *points, const BYTE *types, INT count, FillMode fillMode)
{
	p_Context=ip_Context;
	m_GraphicsPath=new GraphicsPath(points, types, count, fillMode);
}


CGraphicsPathPlus::~CGraphicsPathPlus()
{
	if (m_GraphicsPath) delete m_GraphicsPath;
	m_GraphicsPath=NULL;
}


UINT CGraphicsPathPlus::DoMethod(const char *iStr, char *oStr)
{
	int nfunc=0;
	char met[150];
	strncpy(met,iStr,145);
	met[145]=0;
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int retint=-123456; 
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
	case  0: //AddArc x,y,width,height,startAngle,sweepAngle
		{
			REAL x=0,y=0,width=0,height=0,startAngle=0,sweepAngle=0;
			sscanf(pos,"%g,%g,%g,%g,%g,%g",&x,&y,&width,&height,&startAngle,&sweepAngle);
			retint=m_GraphicsPath->AddArc(x,y,width,height,startAngle,sweepAngle);
		}
		break;
	case  1: //AddArcR ContextName,nRect,startAngle,sweepAngle
		if (p_Context)
		{
			CString ContName=ExtractField(pos,1,",");
			CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
			UINT nObject1=atoi(ExtractField(pos,2,","));
			if (ocontext && nObject1 < ocontext->m_nRectArray)
			{
				REAL startAngle=(REAL)atof(ExtractField(pos,4,",")),sweepAngle=(REAL)atof(ExtractField(pos,5,","));
				retint=m_GraphicsPath->AddArc(ocontext->m_RectArr[nObject1],startAngle,sweepAngle);
			}
		}
		break; 
	case  2: //AddBezier x1,y1,x2,y2,x3,y3,x4,y4
		{
			REAL x1=0,y1=0,x2=0,y2=0,x3=0,y3=0,x4=0,y4=0;
			sscanf(pos,"%g,%g,%g,%g,%g,%g,%g,%g",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
			retint=m_GraphicsPath->AddBezier(x1,y1,x2,y2,x3,y3,x4,y4);
		}
		break; 
	case  3: //AddBezierP ContextName,nPoint1,nPoint2,nPoint3,nPoint4
		if (p_Context)
		{
			CString ContName=ExtractField(pos,1,",");
			UINT nObject1=0,nObject2=1,nObject3=2,nObject4=3;
			CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
			const char *pos2=FindField(pos,2,",");
			if (pos) sscanf(pos2,"%d,%d,%d,%d",&nObject1,&nObject2,&nObject3,&nObject4);

			if (ocontext && nObject1 < ocontext->m_nPointArray && nObject2 < ocontext->m_nPointArray && nObject3 < ocontext->m_nPointArray && nObject4 < ocontext->m_nPointArray)
				retint=m_GraphicsPath->AddBezier(ocontext->m_PointArr[nObject1],ocontext->m_PointArr[nObject2],ocontext->m_PointArr[nObject3],ocontext->m_PointArr[nObject4]);
		}
		break; 

	case  4: //AddBeziers X1,Y1;X2,Y2;X3,Y3;X4,Y4[;....]
	case  5: //AddClosedCurve X1,Y1;X2,Y2;X3,Y3;X4,Y4[;....]
	case  6: //AddClosedCurveEx tension,X1,Y1;X2,Y2;X3,Y3;X4,Y4[;....]
	case  7: //AddCurve X1,Y1;X2,Y2;X3,Y3;X4,Y4[;....]
	case  8: //AddCurveEx tension,X1,Y1;X2,Y2;X3,Y3;X4,Y4[;....]
	case  9: //AddLines X1,Y1;X2,Y2[;....]
	case 23: //AddPolygon X1,Y1;X2,Y2;X3,Y3[;....]
		{
			const char *pos2=pos;
			INT nItems=1;
			while(*pos2) if (*(pos2++)==';') nItems++;
			PointF *points=new PointF[nItems+10];
			REAL tension=(REAL) atof(pos);
			if (nfunc==6 || nfunc==8) 
			{
				while(*pos && *pos!=',') pos++;
				if (*pos) pos++;
			}
			nItems=0;
			while(*pos)
			{
				sscanf(pos,"%g,%g",&(points[nItems].X),&(points[nItems].Y));
				nItems++;
				while(*pos && *pos!=';') pos++;
				if (*pos) pos++;
			}
			if (nItems)
				switch(nfunc)
				{
				case  4:	retint=m_GraphicsPath->AddBeziers(points,nItems);				break;
				case  5:	retint=m_GraphicsPath->AddClosedCurve(points,nItems);			break;
				case  6:	retint=m_GraphicsPath->AddClosedCurve(points,nItems,tension);	break;
				case  7:	retint=m_GraphicsPath->AddCurve(points,nItems);					break;
				case  8:	retint=m_GraphicsPath->AddCurve(points,nItems,tension);			break;
				case  9:	retint=m_GraphicsPath->AddLines(points,nItems);					break;
				case 23:	retint=m_GraphicsPath->AddPolygon(points,nItems);				break;
				}
		}
	case 10: //AddBeziersP ContextName,nPoint1,nPoint2,nPoint3,nPoint4[,....]
	case 11: //AddClosedCurveP ContextName,nPoint1,nPoint2,nPoint3,nPoint4[,....]
	case 12: //AddClosedCurvePEx ContextName,tension,nPoint1,nPoint2,nPoint3,nPoint4[,....]
	case 13: //AddCurveP ContextName,nPoint1,nPoint2,nPoint3,nPoint4[,....]
	case 14: //AddCurvePEx ContextName,tension,nPoint1,nPoint2,nPoint3,nPoint4[,....]
	case 15: //AddLinesP ContextName,nPoint1,nPoint2[,....]
	case 24: //AddPolygonP ContextName,nPoint1,nPoint2,nPoint3,nPoint4[,....]
		if (p_Context)
		{
			CString ContName=ExtractField(pos,1,",");
			UINT nObject1=0,nObject2=1,nObject3=2,nObject4=3;
			CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
			const char *pos3=FindField(pos,2,",");
			if (ocontext && pos3) 
			{
				const char *pos2=pos3;
				INT nItems=1;
				while(*pos2) if (*(pos2++)==',') nItems++;
				PointF *points=new PointF[nItems+10];
				nItems=0;
				pos2=pos3;
				REAL tension=(REAL) atof(pos2);
				if (nfunc==12 || nfunc==14) 
				{
					while(*pos2 && *pos2!=',') pos2++;
					if (*pos2) pos2++;
				}
				while(*pos2)
				{
					int nPoint=atoi(pos2);
					if (nPoint>=0)
					{
						if ((UINT)nPoint < ocontext->m_nPointArray) 
							points[nItems++]=ocontext->m_PointArr[nPoint];
					}
					else
					{
						if ((UINT)((-nPoint-1)*2)<ocontext->m_nREALArray)
						{
							points[nItems].X=ocontext->m_REALArr[(-nPoint-1)*2];
							points[nItems].Y=ocontext->m_REALArr[(-nPoint-1)*2+1];
							nItems++;
						}
					}
					while(*pos2 && *pos2!=',') pos2++;
					if (*pos2) pos2++;
				}
				if (nItems) 
					switch(nfunc)
					{
					case 10:	retint=m_GraphicsPath->AddBeziers(points,nItems);				break;
					case 11:	retint=m_GraphicsPath->AddClosedCurve(points,nItems);			break;
					case 12:	retint=m_GraphicsPath->AddClosedCurve(points,nItems,tension);	break;
					case 13:	retint=m_GraphicsPath->AddCurve(points,nItems);					break;
					case 14:	retint=m_GraphicsPath->AddCurve(points,nItems,tension);			break;
					case 15:	retint=m_GraphicsPath->AddLines(points,nItems);					break;
					case 24:	retint=m_GraphicsPath->AddPolygon(points,nItems);				break;
					}
			}
		}
		break; 
	case 16: //AddEllipse x,y,width,height
		{
			REAL x=0,y=0,width=0,height=0;
			sscanf(pos,"%g,%g,%g,%g",&x,&y,&width,&height);
			retint=m_GraphicsPath->AddEllipse(x,y,width,height);
		}
		break;
	case 17: //AddEllipseR ContextName,nRect
		if (p_Context)
		{
			CString ContName=ExtractField(pos,1,",");
			CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
			UINT nObject1=atoi(ExtractField(pos,2,","));
			if (ocontext && nObject1 < ocontext->m_nRectArray)
				retint=m_GraphicsPath->AddEllipse(ocontext->m_RectArr[nObject1]);
		}
		break; 
	case 18: //AddLine x1,y1,x2,y2
		{
			REAL x1=0,y1=0,x2=0,y2=0;
			sscanf(pos,"%g,%g,%g,%g",&x1,&y1,&x2,&y2);
			retint=m_GraphicsPath->AddLine(x1,y1,x2,y2);
		}
		break;
	case 19: //AddLineP ContextName,nPoint1,nPoint2
		if (p_Context)
		{
			CString ContName=ExtractField(pos,1,",");
			CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
			UINT nObject1=atoi(ExtractField(pos,2,","));
			UINT nObject2=atoi(ExtractField(pos,3,","));
			if (ocontext && nObject1 < ocontext->m_nPointArray && nObject2 < ocontext->m_nPointArray)
				retint=m_GraphicsPath->AddLine(ocontext->m_PointArr[nObject1],ocontext->m_PointArr[nObject2]);
		}
		break; 
	case 20: //AddPath ContextName,nPath,bConnect
		if (p_Context)
		{
			CString ContName=ExtractField(pos,1,",");
			CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
			UINT nObject1=atoi(ExtractField(pos,2,","));
			UINT nObject2=atoi(ExtractField(pos,3,","));
			if (ocontext && nObject1 < ocontext->m_nGraphPathArray)
				retint=m_GraphicsPath->AddPath(ocontext->m_GraphPathArr[nObject1]->m_GraphicsPath,nObject2);
		}
		break; 
	case 21: //AddPie x,y,width,height,startAngle,sweepAngle
		{
			REAL x=0,y=0,width=0,height=0,startAngle=0,sweepAngle=0;
			sscanf(pos,"%g,%g,%g,%g,%g,%g",&x,&y,&width,&height,&startAngle,&sweepAngle);
			retint=m_GraphicsPath->AddPie(x,y,width,height,startAngle,sweepAngle);
		}
		break;
	case 22: //AddPieR ContextName,nRect,startAngle,sweepAngle
		if (p_Context)
		{
			CString ContName=ExtractField(pos,1,",");
			CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
			UINT nObject1=atoi(ExtractField(pos,2,","));
			if (ocontext && nObject1 < ocontext->m_nRectArray)
			{
				REAL startAngle=(REAL)atof(ExtractField(pos,4,",")),sweepAngle=(REAL)atof(ExtractField(pos,5,","));
				retint=m_GraphicsPath->AddPie(ocontext->m_RectArr[nObject1],startAngle,sweepAngle);
			}
		}
		break; 
	case 25: //AddRectangle x,y,width,height
		{
			REAL x=0,y=0,width=0,height=0;
			sscanf(pos,"%g,%g,%g,%g",&x,&y,&width,&height);
			retint=m_GraphicsPath->AddRectangle(RectF(x,y,width,height));
		}
		break;
	case 26: //AddRectangleR ContextName,nRect
		if (p_Context)
		{
			CString ContName=ExtractField(pos,1,",");
			CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
			UINT nObject1=atoi(ExtractField(pos,2,","));
			if (ocontext && nObject1 < ocontext->m_nRectArray)
				retint=m_GraphicsPath->AddRectangle(ocontext->m_RectArr[nObject1]);
		}
		break; 
	case 27: //AddRectangles x1,y1,width11,height1;x2,y2,width12,height2[;....]
		{
			const char *pos2=pos;
			INT nItems=1;
			while(*pos2) if (*(pos2++)==';') nItems++;
			RectF *rects=new RectF[nItems+10];
			nItems=0;
			while(*pos)
			{
				sscanf(pos,"%g,%g,%g,%g",&(rects[nItems].X),&(rects[nItems].Y),&(rects[nItems].Width),&(rects[nItems].Height));
				nItems++;
				while(*pos && *pos!=';') pos++;
				if (*pos) pos++;
			}
			if (nItems)
				switch(nfunc)
				{
				case 27:	retint=m_GraphicsPath->AddRectangles(rects,nItems);				break;
				}
		}
	case 28: //AddRectanglesP ContextName,nRect1,nRect2[,....]
		if (p_Context)
		{
			CString ContName=ExtractField(pos,1,",");
			UINT nObject1=0,nObject2=1,nObject3=2,nObject4=3;
			CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
			const char *pos3=FindField(pos,2,",");
			if (ocontext && pos3) 
			{
				const char *pos2=pos3;
				INT nItems=1;
				while(*pos2) if (*(pos2++)==',') nItems++;
				RectF *rects=new RectF[nItems+10];
				nItems=0;
				pos2=pos3;
				while(*pos2)
				{
					int nRects=atoi(pos2);
					if (nRects>=0)
					{
						if ((UINT)nRects < ocontext->m_nRectArray) 
							rects[nItems++]=ocontext->m_RectArr[nRects];
					}
					else
					{
						if ((UINT)((-nRects-1)*2)<ocontext->m_nREALArray)
						{
							rects[nItems].X=ocontext->m_REALArr[(-nRects-1)*2];
							rects[nItems].Y=ocontext->m_REALArr[(-nRects-1)*2+1];
							rects[nItems].Width=ocontext->m_REALArr[(-nRects-1)*2+2];
							rects[nItems].Height=ocontext->m_REALArr[(-nRects-1)*2+3];
							nItems++;
						}
					}
					while(*pos2 && *pos2!=',') pos2++;
					if (*pos2) pos2++;
				}
				if (nItems) 
					switch(nfunc)
					{
					case 28:	retint=m_GraphicsPath->AddRectangles(rects,nItems);				break;
					}
			}
		}
		break; 


	case 29: //AddStringP ContextName,nFont,nFormat,nPoint,emSize,style,language;String
	case 30: //AddStringR ContextName,nFont,nFormat,nRect,emSize,style,language;String
		{
			CString ContName=ExtractField(pos,1,",");
			UINT nObject1=0,nObject2=1,nObject3=2,nObject4=3;
			CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
			const char *pos3=FindField(pos,2,",");
			const char *postext=FindField(pos,2,";");
			if (postext && pos3 && *postext && *pos3)
			{
				UINT  nFont=0,nFormat=0,nRect=0;
				REAL emSize=10;
				sscanf(pos3,"%d,%d,%d,%g",&nFont,&nFormat,&nRect,&emSize);
				CString tmpcs=ExtractField(pos3,5,",");
				CString tmpcsLang=ExtractField(pos3,6,",");
				DWORD dwFontStyle=atoi(tmpcs);
				DWORD dwLangId=tmpcsLang==""?LANG_NEUTRAL:atoi(tmpcsLang);
				if (tmpcs[0]!='0' && dwFontStyle==0)
				{
					int i;
					for(i=0;*CFontPlus::ccAFontStyle[i] && _stricmp(CFontPlus::ccAFontStyle[i],tmpcs)!=0;i++);
					dwFontStyle=CFontPlus::iAFontStyle[i];
				}
				DWORD dwOutLen=strlen(postext)*2+100;
				WCHAR *tmpWText=new WCHAR [dwOutLen];

				MultiByteToWideChar(CP_ACP, 0,postext , -1, tmpWText, dwOutLen);
				FontFamily family;
				if (nFont< ocontext->m_nFontArray && ocontext->m_FontArr[nFont])
				{
					ocontext->m_FontArr[nFont]->m_Font->GetFamily(&family);
					if (emSize<1) emSize=ocontext->m_FontArr[nFont]->m_Font->GetSize();
				}
				if (emSize<1) emSize=10;

				if (nFormat< ocontext->m_nStringFormatArray && ocontext->m_StringFormatArr[nFormat])
				{
					if (nfunc==29)
					{
						if (nRect< ocontext->m_nRectArray)
							retint=m_GraphicsPath->AddString(tmpWText,-1,&family,dwFontStyle,emSize,ocontext->m_PointArr[nRect],ocontext->m_StringFormatArr[nFormat]->m_StringFormat);
					}
					else
					{
						if (nRect< ocontext->m_nPointArray)
							retint=m_GraphicsPath->AddString(tmpWText,-1,&family,dwFontStyle,emSize,ocontext->m_RectArr[nRect],ocontext->m_StringFormatArr[nFormat]->m_StringFormat);
					}
				}
				delete []tmpWText;
			}
		}
		break; 
	case 31: //ClearMarkers
		retint=m_GraphicsPath->ClearMarkers();
		break; 
	case 32: //CloseAllFigures
		retint=m_GraphicsPath->CloseAllFigures();
		break; 
	case 33: //CloseFigure
		retint=m_GraphicsPath->CloseFigure();
		break; 
	case 34: //Flatten [flatness,m11,m12,m21,m22,dx,dy]
	case 43: //Outline [flatness,m11,m12,m21,m22,dx,dy]
		{
			Matrix ma;
			Matrix *pma=&ma;
			REAL dwflatness=FlatnessDefault;
			REAL rea[10]={0};
			sscanf(pos,"%g,%g,%g,%g,%g,%g,%g",&dwflatness,rea,rea+1,rea+2,rea+3,rea+4,rea+5);
			if (*pos==',' || *pos==0) dwflatness=FlatnessDefault;
			if (strchr(pos,',')==NULL) pma=NULL;
			else ma.SetElements(rea[0],rea[1],rea[2],rea[3],rea[4],rea[5]);
			if (nfunc==34)
				retint=m_GraphicsPath->Flatten(pma,dwflatness);
			else
				retint=m_GraphicsPath->Outline(pma,dwflatness);
		}
		break; 
	case 35: //GetBounds [ContextName],[nPen],[m11,m12,m21,m22,dx,dy]
		{
			CString ContName=ExtractField(pos,1,",");
			CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
			UINT nObject1=atoi(ExtractField(pos,2,","));
			const char *pos3=FindField(pos,3,",");
			Rect re(0,0,0,0);
			Pen *pPen=NULL;
			if (ExtractField(pos,2,",")!="" &&  (nObject1< ocontext->m_nPenArray && ocontext->m_PenArr[nObject1]))
				pPen=ocontext->m_PenArr[nObject1]->m_Pen;

			if (pos3 && *pos3)
			{
				Matrix ma;
				REAL rea[10]={0};
				sscanf(pos,"%d,%g,%g,%g,%g,%g",&rea,rea+1,rea+2,rea+3,rea+4,rea+5);
				ma.SetElements(rea[0],rea[1],rea[2],rea[3],rea[4],rea[5]);
				retint=m_GraphicsPath->GetBounds(&re,&ma,pPen);
			}
			else
				retint=m_GraphicsPath->GetBounds(&re,NULL,pPen);
		}
		break; 
	case 36: //GetFillMode
		retint=m_GraphicsPath->GetFillMode();
		break; 
	case 37: //GetLastPoint
		if (oStr)
		{
			PointF po;
			m_GraphicsPath->GetLastPoint(&po);
			sprintf(oStr,"%g\x7F%g",po.X,po.Y);
		}
		break; 
	case 38: //GetLastStatus
		retint=m_GraphicsPath->GetLastStatus();
		break; 
	case 39: //GetPointCount
		retint=m_GraphicsPath->GetPointCount();
		break; 
	case 40: //GetPathData
	case 41: //GetPathPoints
	case 42: //GetPathTypes
		if (oStr)
		{
			PathData pd;
			m_GraphicsPath->GetPathData(&pd);
			INT i;
			char *posout=oStr;
			for(i=0;i<pd.Count;i++)
			{
				if (posout!=oStr) {*(posout++)=0x7F;*posout=0;}
				switch(nfunc)
				{
				case 40:
					posout+=sprintf(posout,"%d\x7%g\x7%g",pd.Types[i],pd.Points[i].X,pd.Points[i].X);
					break;
				case 41:
					posout+=sprintf(posout,"%g\x7%g",pd.Points[i].X,pd.Points[i].X);
					break;
				case 42:
					posout+=sprintf(posout,"%d",pd.Types[i]);
					break;
				}
			}
		}
		break; 
	case 44: //Reset
		retint=m_GraphicsPath->Reset();
		break; 
	case 45: //Reverse
		retint=m_GraphicsPath->Reverse();
		break; 
	case 46: //SetFillMode FillMode 
		{
			DWORD dwFillMode=atoi(pos);
			if (*pos!='0' &&  dwFillMode==0)
			{
				int i;
				for(i=0; *ccAFillMode[i] && !dwFillMode;i++) 
					if (_stricmp(pos,ccAFillMode[i])==0) dwFillMode=iAFillMode[i];
			}
			retint=m_GraphicsPath->SetFillMode((Gdiplus::FillMode)dwFillMode);
		}
		break; 
	case 47: //SetMarker
		retint=m_GraphicsPath->SetMarker();
		break;
	case 48: //StartFigure
		retint=m_GraphicsPath->StartFigure();
		break;
	case 49: //Transform m11,m12,m21,m22,dx,dy
		{
			Matrix ma;
			REAL rea[10]={0};
			sscanf(pos,"%g,%g,%g,%g,%g,%g",rea,rea+1,rea+2,rea+3,rea+4,rea+5);
			ma.SetElements(rea[0],rea[1],rea[2],rea[3],rea[4],rea[5]);
			m_GraphicsPath->Transform(&ma);
		}
		break;

	case 50: //Warp X,Y,CX,CY,[warpMode],[flatness][,m11,m12,m21,m22,dx,dy];X1,Y1;X2,Y2[;....]
	case 51: //WarpR ContextName,nRect,[warpMode],[flatness][,m11,m12,m21,m22,dx,dy];X1,Y1;X2,Y2[;....]
		{
			RectF srcRect(0,0,0,0);
			Matrix matrix;//opt
			Matrix *pmatrix=NULL;//opt
			WarpMode warpMode=WarpModePerspective;//opt
			REAL flatness=FlatnessDefault;//opt
			CString csPart1=ExtractField(pos,1,";");
			int i;
			int fieldelta=3;
			if (nfunc==50)
			{
				sscanf(pos,"%g,%g,%g,%g",&srcRect.X,&srcRect.Y,&srcRect.Width,&srcRect.Height);
			}
			else
			{
				CString ContName=ExtractField(csPart1,1,",");
				CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
				UINT nObject1=atoi(ExtractField(csPart1,2,","));
				if (nObject1< ocontext->m_nRectArray) srcRect=ocontext->m_RectArr[nObject1];
				fieldelta=5;
			}
			CString tmpcs=ExtractField(pos,fieldelta++,",");
			if (tmpcs!="" && tmpcs[0]!='0' && (warpMode=(Gdiplus::WarpMode)atoi(tmpcs))==0)
			{
				for(i=0; *ccAWarpMode[i] && !warpMode;i++) 
					if (_stricmp(pos,ccAWarpMode[i])==0) warpMode=(Gdiplus::WarpMode)iAWarpMode[i];
			}
			tmpcs=ExtractField(pos,fieldelta++,",");
			if (tmpcs!="") flatness=(REAL)atof(tmpcs);
			const char *pos2=FindField(pos,fieldelta,",");
			if (pos2 && *pos2)
			{
				REAL rea[10]={0};
				sscanf(pos2,"%g,%g,%g,%g,%g,%g",rea,rea+1,rea+2,rea+3,rea+4,rea+5);
				matrix.SetElements(rea[0],rea[1],rea[2],rea[3],rea[4],rea[5]);
				pmatrix=&matrix;
			}
			pos2=FindField(pos,2,";");
			if (pos2 && *pos2)
			{
				PointF *destPoints;
				INT PointsCount=1;
				const char *pos3=pos2;
				while(*pos3)
					if (*(pos3++)==';') PointsCount++;
				pos3=pos2;
				destPoints=new PointF[PointsCount+10];
				PointsCount=0;
				while(*pos3)
				{
					sscanf(pos3,"%g,%g",&destPoints[PointsCount].X,&destPoints[PointsCount].Y);
					PointsCount++;
					while(*pos3 && *(pos3++)!=';');
				}
				if (*pos2)
					m_GraphicsPath->Warp(destPoints,PointsCount,srcRect,pmatrix,warpMode,flatness);
				delete []destPoints;
			}
		}
		break; 
	case 52: //Widen ContextName,nPen,[flatness],[m11,m12,m21,m22,dx,dy]
		{
			REAL flatness=FlatnessDefault;
			UINT nPen;
			Matrix matrix;
			Matrix *pmatrix=NULL;
			CString ContName=ExtractField(pos,1,",");
			CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
			nPen=atoi(ExtractField(pos,2,","));
			if (nPen< ocontext->m_nPenArray && ocontext->m_PenArr[nPen])
			{
				const char *pos2=FindField(pos,4,",");
				if (pos2 && *pos2)
				{
					REAL rea[10]={0,0,0,0,0,0,0,0,0,};
					sscanf(pos2,"%g,%g,%g,%g,%g,%g",rea,rea+1,rea+2,rea+3,rea+4,rea+5);
					matrix.SetElements(rea[0],rea[1],rea[2],rea[3],rea[4],rea[5]);
					pmatrix=&matrix;
				}
				CString tmpcs=ExtractField(pos,3,",");
				if (tmpcs!="") flatness=(REAL)atof(tmpcs); 
				m_GraphicsPath->Widen(ocontext->m_PenArr[nPen]->m_Pen,pmatrix,flatness);
			}
		}
		break; 
/*
GraphicsPath::IsOutlineVisible(Point&,Pen*,Graphics*) The IsOutlineVisible method determines whether a specified point touches the outline of this path when the path is drawn by a specified Graphics object and a specified pen. 
GraphicsPath::IsOutlineVisible(REAL,REAL,Pen*,Graphics*) The IsOutlineVisible method determines whether a specified point touches the outline of this path when the path is drawn by a specified Graphics object and a specified pen. 
GraphicsPath::IsOutlineVisible(INT,INT,Pen*,Graphics*) The IsOutlineVisible method determines whether a specified point touches the outline of this path when the path is drawn by a specified Graphics object and a specified pen. 
GraphicsPath::IsOutlineVisible(PointF&,Pen*,Graphics*) The IsOutlineVisible method determines whether a specified point touches the outline of this path when the path is drawn by a specified Graphics object and a specified pen. 
GraphicsPath::IsVisible(REAL,REAL,Graphics*) The IsVisible method determines whether a specified point lies in the area that is filled when this path is filled by a specified Graphics object. 
GraphicsPath::IsVisible(PointF&,Graphics*) The IsVisible method determines whether a specified point lies in the area that is filled when this path is filled by a specified Graphics object. 
GraphicsPath::IsVisible(INT,INT,Graphics*) The IsVisible method determines whether a specified point lies in the area that is filled when this path is filled by a specified Graphics object. 
GraphicsPath::IsVisible(Point&,Graphics*) The IsVisible method determines whether a specified point lies in the area that is filled when this path is filled by a specified Graphics object. 
*/
	default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
	}
	if (oStr && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);

	return nfunc;
}


const GraphicsPath *CGraphicsPathPlus::SetGraphicsPath(GraphicsPath *pGraphicsPath)
{
	if (pGraphicsPath)
	{
		if (m_GraphicsPath) delete m_GraphicsPath;
		m_GraphicsPath=pGraphicsPath;
	}
	return m_GraphicsPath;
}