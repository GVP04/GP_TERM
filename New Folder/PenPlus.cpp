// PenPlus.cpp: implementation of the CPenPlus class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "PenPlus.h"
#include "GP_TermView.h"
#include "ODContextItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const char *CPenPlus::ccALineCap[]={"Flat","Square","Round","Triangle","NoAnchor","SquareAnchor","RoundAnchor","DiamondAnchor","ArrowAnchor","Custom","",};
const DWORD CPenPlus::iALineCap[]={LineCapFlat,LineCapSquare,LineCapRound,LineCapTriangle,LineCapNoAnchor,LineCapSquareAnchor,LineCapRoundAnchor,LineCapDiamondAnchor,LineCapArrowAnchor,LineCapCustom,0,};
const char *CPenPlus::ccADashStyle[]={"Solid","Dash","Dot","DashDot","DashDotDot","Custom","",};
const DWORD CPenPlus::iADashStyle[]={DashStyleSolid,DashStyleDash,DashStyleDot,DashStyleDashDot,DashStyleDashDotDot,DashStyleCustom,0,};
const char *CPenPlus::ccADashCap[]={"Flat","Round","Triangle","",};
const DWORD CPenPlus::iADashCap[]={DashCapFlat,DashCapRound,DashCapTriangle,0,};
const char *CPenPlus::ccALineJoin[]={"Miter","Bevel","Round","MiterClipped","",};
const DWORD CPenPlus::iALineJoin[]={LineJoinMiter,LineJoinBevel,LineJoinRound,LineJoinMiterClipped,0,};


const UINT CPenPlus::uNMethods=41;
const char *CPenPlus::cArrMethods[]={
/*00*/		"GetAlignment","GetBrush","GetColor","GetCompoundArray","GetCompoundArrayCount",
/*05*/		"GetCustomEndCap","GetCustomStartCap","GetDashCap","GetDashOffset","GetDashPattern",
/*10*/		"GetDashPatternCount","GetDashStyle","GetEndCap","GetLastStatus","GetLineJoin",
/*15*/		"GetMiterLimit","GetPenType","GetStartCap","GetTransform","GetWidth",
/*20*/		"MultiplyTransform","ResetTransform","RotateTransform","ScaleTransform","SetAlignment",
/*25*/		"SetBrush","SetColor","SetCompoundArray","SetCustomEndCap","SetCustomStartCap",
/*30*/		"SetDashCap","SetDashOffset","SetDashPattern","SetDashStyle","SetEndCap",
/*35*/		"SetLineCap","SetLineJoin","SetMiterLimit","SetStartCap","SetTransform",
/*40*/		"SetWidth","","","","",
/*45*/		"","","","","",
/*50*/		"","","","","",
/*55*/		"","","","","",
	};
const char *CPenPlus::cArrMethodsParams[]={
/*00*/		"","","","","",
/*05*/		"","","","","",
/*10*/		"","","","","",
/*15*/		"","","","","",
/*20*/		"Order,m11,m12,m21,m22,dx,dy","","MatrixOrder,angle","sx,sy,MatrixOrder","penAlignment",
/*25*/		"ContextName,BruhNumber","R,G,B,A","X1.1,X1.2[;X2.1,X2.2[;X3.1,X3.2]....]","","",
/*30*/		"DashCap","DashOffset","X1[,X2[,X3[...]]]","DashStyle","EndCap",
/*35*/		"startCap,endCap,dashCap","LineJoin","MiterLimit","StartCap","m11,m12,m21,m22,dx,dy",
/*40*/		"Width","","","","",
/*45*/		"","","","","",
/*50*/		"","","","","",
/*55*/		"","","","","",
	};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPenPlus::~CPenPlus()
{
	if (m_Pen) delete m_Pen;
	m_Pen=NULL;
	if (m_DefBrush) delete m_DefBrush;
	m_DefBrush=NULL;
}

CPenPlus::CPenPlus(CODContext *ip_Context, const Color &color, REAL width)
{
	p_Context=ip_Context;
	m_Pen=new Pen(color,width);
	m_DefBrush=NULL;
	m_dwType=0;
}
CPenPlus::CPenPlus(CODContext *ip_Context, const Brush *brush, REAL width)
{
	p_Context=ip_Context;
	m_Pen=new Pen(brush,width);
	m_DefBrush=NULL;
	m_dwType=1;
}


CPenPlus::CPenPlus(CODContext *ip_Context, IN const char *iStr, REAL width)
{
	p_Context=ip_Context;
	m_DefBrush=NULL;
	m_Pen=NULL;
	m_dwType=0;

	if (*iStr!='B' && *iStr!='b')
	{
		m_Pen=new Pen(Color(CODContext::GetColorFromString(p_Context, iStr)),width);
	}
	else
	{
		//CLR(...)
		PDCIPARAMETER mparam=NULL;
		DCParamType pta[]={DCPT_VARTYPE,DCPT_NONE};
		UINT tmpNParams=0;
		CODContextItem::TranslateParams(iStr,pta,p_Context,&(mparam),&tmpNParams);
		if (mparam)
		{
			if ((mparam[0].dwParamType&DCPT_TYPEMASK)==DCPT_BRUSH)
			{
				if (p_Context) CODContextItem::PrepareParameter(p_Context,&(mparam[0]));
				if (mparam[0].m_pBrush && mparam[0].m_pBrush->m_Brush) m_Pen=new Pen(mparam[0].m_pBrush->m_Brush,width);
			}

			CODContextItem::ResetParameters(&mparam,&tmpNParams);
			delete []mparam;
		}
	}

	if (!m_Pen)	m_Pen=new Pen(Color(255,0,0,0),width);
}

UINT CPenPlus::DoMethod(const char *iStr, char *oStr)
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
	case  0: //GetAlignment
		retint=m_Pen->GetAlignment();
		break; 
//	case  1: //GetBrush
//		break; 
	case  2: //GetColor
		if (oStr)
		{
			Color clr;
			m_Pen->GetColor(&clr);
			sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",clr.GetR(),clr.GetG(),clr.GetB(),clr.GetA());
		}
		break; 
	case  3: //GetCompoundArray
		if (oStr)
		{
			UINT nArr=m_Pen->GetCompoundArrayCount();
			UINT i;
			REAL *ca=new REAL[nArr+10];
			m_Pen->GetCompoundArray(ca,nArr);
			char *posout=oStr;
			for(i=0;i<nArr;i++)
			{
				if (posout!=oStr) (*posout++)=0x7F;
				*posout=0;
				posout+=sprintf(posout,"%g",ca[i]);
			}

			delete []ca;
		}
		break; 
	case  4: //GetCompoundArrayCount
		retint=m_Pen->GetCompoundArrayCount();
		break; 
//	case  5: //GetCustomEndCap
//		break; 
//	case  6: //GetCustomStartCap
//		break; 
	case  7: //GetDashCap
		retint=m_Pen->GetDashCap();
		break; 
	case  8: //GetDashOffset
		if (oStr) sprintf(oStr,"%g",m_Pen->GetDashOffset());
		break; 
	case  9: //GetDashPattern
		if (oStr)
		{
			UINT nArr=m_Pen->GetDashPatternCount();
			UINT i;
			REAL *ca=new REAL[nArr+10];
			m_Pen->GetDashPattern(ca,nArr);
			char *posout=oStr;
			for(i=0;i<nArr;i++)
			{
				if (posout!=oStr) (*posout++)=0x7F;
				*posout=0;
				posout+=sprintf(posout,"%g",ca[i]);
			}

			delete []ca;
		}
		break; 
	case 10: //GetDashPatternCount
		retint=m_Pen->GetDashPatternCount();
		break; 
	case 11: //GetDashStyle
		retint=m_Pen->GetDashStyle();
		break; 
	case 12: //GetEndCap
		retint=m_Pen->GetEndCap();
		break; 
	case 13: //GetLastStatus
		retint=m_Pen->GetLastStatus();
		break; 
	case 14: //GetLineJoin
		retint=m_Pen->GetLineJoin();
		break; 
	case 15: //GetMiterLimit
		if (oStr) sprintf(oStr,"%g",m_Pen->GetMiterLimit());
		break; 
	case 16: //GetPenType
		retint=m_Pen->GetPenType();
		break; 
	case 17: //GetStartCap
		retint=m_Pen->GetStartCap();
		break; 
	case 18: //GetTransform
		if (oStr)
		{
			Matrix ma;
			m_Pen->GetTransform(&ma);
			REAL rea[10]={0};
			ma.GetElements(rea);
			sprintf(oStr,"%g\x7F%g\x7F%g\x7F%g\x7F%g\x7F%g",rea[0],rea[1],rea[2],rea[3],rea[4],rea[5]);
		}
		break; 
	case 19: //GetWidth
		if (oStr) sprintf(oStr,"%g",m_Pen->GetWidth());
		break; 
	case 20: //MultiplyTransform
		{
			Matrix ma;
			DWORD dwOrder=0;
			REAL rea[10]={0};
			sscanf(pos,"%d,%g,%g,%g,%g,%g,%g",&dwOrder,rea,rea+1,rea+2,rea+3,rea+4,rea+5);
			ma.SetElements(rea[0],rea[1],rea[2],rea[3],rea[4],rea[5]);
			m_Pen->MultiplyTransform(&ma,(Gdiplus::MatrixOrder)dwOrder);
			if (oStr) DoMethod("GetTransform",oStr);
		}
		break; 
	case 21: //ResetTransform
		retint=m_Pen->ResetTransform();
		break; 
	case 22: //RotateTransform
		{
			DWORD dwOrder=0;
			REAL rea=0;
			sscanf(pos,"%d,%g",&dwOrder,&rea);
			m_Pen->RotateTransform(rea,(Gdiplus::MatrixOrder)dwOrder);
			if (oStr) DoMethod("GetTransform",oStr);
		}
		break; 
	case 23: //ScaleTransform
		{
			REAL sx=0;
			REAL sy=0;
			DWORD dwOrder=0;
			sscanf(pos,"%d,%g,%g",&dwOrder,&sx,&sy);
			m_Pen->ScaleTransform(sx,sy,(Gdiplus::MatrixOrder)dwOrder);
			if (oStr) DoMethod("GetTransform",oStr);
		}
		break; 
	case 24: //SetAlignment
		retint=m_Pen->SetAlignment((Gdiplus::PenAlignment)atoipos);
		break; 
	case 25: //SetBrush
		{
			CODContext *ocontext=(*pos==0 && p_Context)?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ExtractField(pos,1,","));
			UINT nBrush=atoi(ExtractField(pos,2,","));
			if (m_DefBrush) delete m_DefBrush;
			m_DefBrush=NULL;
			if (nBrush > ocontext->m_nBrushArray || ocontext->m_BrushArr[nBrush]==NULL)
				m_DefBrush=new SolidBrush(Color(255,0,0,0));
			else
				m_DefBrush=ocontext->m_BrushArr[nBrush]->m_Brush->Clone();
			m_Pen->SetBrush(m_DefBrush);
		}
		break; 
	case 26: //SetColor
		{
			if (oStr) DoMethod("GetColor",oStr);
			m_Pen->SetColor(Color(CODContext::GetColorFromString(p_Context, iStr)));
		}
		break; 
	case 27: //SetCompoundArray
		{
			if (oStr) DoMethod("GetCompoundArray",oStr);
			int nArr=1;
			const char *pos2=pos;
			while(*pos2) if (*(pos2++)==',') nArr++;
			REAL *arr=new REAL [nArr+10];
			pos2=pos;
			REAL *arrPos=arr;
			REAL lastVal=0;
			
			while(*pos2)
			{
				*arrPos=(REAL)atof(pos2);
				if (*arrPos<0 || *arrPos>1) *arrPos=lastVal;
				lastVal=*(arrPos++);
				while(*pos2 && *pos2!=',' && *pos2!=';') pos2++;
				if (*pos2) pos2++;
			}
			*arrPos=lastVal;
			nArr&=(0xFFFF^0x0001);
			if (!nArr) nArr=2;
			m_Pen->SetCompoundArray(arr,nArr);
			delete [] arr;
		}
		break; 
//	case 28: //SetCustomEndCap
//		break; 
//	case 29: //SetCustomStartCap
//		break; 
	case 30: //SetDashCap
		{
			retint=m_Pen->GetDashCap();
			int CapToset=atoipos;
			if (*pos!='0' &&  CapToset==0)
			{
				int i;
				for(i=0; *ccADashCap[i] && !CapToset;i++) 
					if (_stricmp(pos,ccADashCap[i])==0) CapToset=iADashCap[i];
			}
			m_Pen->SetDashCap((Gdiplus::DashCap)CapToset);
		}
		break; 
	case 31: //SetDashOffset
		if (oStr) sprintf(oStr,"%g",m_Pen->GetDashOffset());
		m_Pen->SetDashOffset((REAL)atof(pos));
		break; 
	case 32: //SetDashPattern
		{
			if (oStr) DoMethod("GetDashPattern",oStr);
			int nArr=1;
			const char *pos2=pos;
			while(*pos2) if (*(pos2++)==',') nArr++;
			REAL *arr=new REAL [nArr+10];
			pos2=pos;
			REAL *arrPos=arr;
			REAL lastVal=0;
			
			while(*pos2)
			{
				*arrPos=(REAL)atof(pos2);
				if (*arrPos<0) *arrPos=lastVal;
				lastVal=*(arrPos++);
				while(*pos2 && *pos2!=',') pos2++;
				if (*pos2) pos2++;
			}
			*arrPos=lastVal;
			m_Pen->SetDashPattern(arr,nArr);
			delete [] arr;
		}
		break; 
	case 33: //SetDashStyle
		{
			retint=m_Pen->GetDashStyle();
			int CapToset=atoipos;
			if (*pos!='0' &&  CapToset==0)
			{
				int i;
				for(i=0; *ccADashStyle[i] && !CapToset;i++) 
					if (_stricmp(pos,ccADashStyle[i])==0) CapToset=iADashStyle[i];
			}
			m_Pen->SetDashStyle((Gdiplus::DashStyle)CapToset);
		}
		break; 
	case 34: //SetEndCap
		{
			retint=m_Pen->GetEndCap();
			int CapToset=atoipos;
			if (*pos!='0' &&  CapToset==0)
			{
				int i;
				for(i=0; *ccALineCap[i] && !CapToset;i++) 
					if (_stricmp(pos,ccALineCap[i])==0) CapToset=iALineCap[i];
			}
			m_Pen->SetEndCap((Gdiplus::LineCap)CapToset);
		}
		break; 
	case 35: //SetLineCap
		{
			int nCap[]={0,0,0,0,};
			int endCap=atoipos;
			int dashCap=atoipos;
			int ni;

			for(ni=0;ni<3;ni++)
			{
				CString tmpcs=ExtractField(pos,ni+1,",");
				nCap[ni]=atoi(tmpcs);
				if (tmpcs[0]!='0' &&  nCap[ni]==0)
				{
					int i;
					if (ni!=2)
					{
						for(i=0; *ccALineCap[i] && !nCap[ni];i++) 
							if (_stricmp(pos,ccALineCap[i])==0) nCap[ni]=iALineCap[i];
					}
					else
					{
						for(i=0; *ccADashCap[i] && !nCap[ni];i++) 
							if (_stricmp(pos,ccADashCap[i])==0) nCap[ni]=iADashCap[i];
					}
				}
			}
			m_Pen->SetLineCap((Gdiplus::LineCap)nCap[0],(Gdiplus::LineCap)nCap[1],(Gdiplus::DashCap)nCap[2]);
		}
		break; 
	case 36: //SetLineJoin
		{
			retint=m_Pen->GetLineJoin();
			int CapToset=atoipos;
			if (*pos!='0' &&  CapToset==0)
			{
				int i;
				for(i=0; *ccALineJoin[i] && !CapToset;i++) 
					if (_stricmp(pos,ccALineJoin[i])==0) CapToset=iALineJoin[i];
			}
			m_Pen->SetLineJoin((Gdiplus::LineJoin)CapToset);
		}
		break; 
	case 37: //SetMiterLimit
		if (oStr) sprintf(oStr,"%g",m_Pen->GetMiterLimit());
		m_Pen->SetMiterLimit((REAL)atof(pos));
		break; 
	case 38: //SetStartCap
		{
			retint=m_Pen->GetStartCap();
			int CapToset=atoipos;
			if (*pos!='0' &&  CapToset==0)
			{
				int i;
				for(i=0; *ccALineCap[i] && !CapToset;i++) 
					if (_stricmp(pos,ccALineCap[i])==0) CapToset=iALineCap[i];
			}
			m_Pen->SetStartCap((Gdiplus::LineCap)CapToset);
		}
		break; 
	case 39: //SetTransform
		{
			if (oStr) DoMethod("GetTransform",oStr);
			Matrix ma;
			DWORD dwOrder=0;
			REAL rea[10]={0};
			sscanf(pos,"%g,%g,%g,%g,%g,%g",rea,rea+1,rea+2,rea+3,rea+4,rea+5);
			ma.SetElements(rea[0],rea[1],rea[2],rea[3],rea[4],rea[5]);
			m_Pen->SetTransform(&ma);
		}
		break; 
	case 40: //SetWidth
		if (oStr) sprintf(oStr,"%g",m_Pen->GetWidth());
		m_Pen->SetWidth((REAL)atof(pos));
		break; 

	default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
	}
	if (oStr && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);

	return nfunc;
}


const Pen *CPenPlus::SetPen(Pen *pPen)
{
	if (pPen)
	{
		if (m_Pen) delete m_Pen;
		if (m_DefBrush) delete m_DefBrush;
		m_DefBrush=NULL;
		m_Pen=pPen;
	}
	return m_Pen;
}