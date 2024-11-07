// BrushPlus.cpp: implementation of the CBrushPlus class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "BrushPlus.h"
#include "GP_TermView.h"
#include "ODContextItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//const char *CBrushPlus::ccABrushType[]={"","","","","","","",};
//const DWORD CBrushPlus::iABrushType[]={,,,,,,,0,};


const char *CBrushPlus::ccALinearGradientMode[]={
	"Horizontal","Vertical","ForwardDiagonal","BackwardDiagonal",
	"",};
const LinearGradientMode CBrushPlus::iALinearGradientMode[]={
	LinearGradientModeHorizontal,LinearGradientModeVertical,LinearGradientModeForwardDiagonal,LinearGradientModeBackwardDiagonal,
	LinearGradientModeHorizontal,};


const char *CBrushPlus::ccABrushType[]={"SolidColor","HatchFill","TextureFill","PathGradient","LinearGradient","",};
const BrushType CBrushPlus::iABrushType[]={BrushTypeSolidColor,BrushTypeHatchFill,BrushTypeTextureFill,BrushTypePathGradient,BrushTypeLinearGradient,
		BrushTypeSolidColor,};

const char *CBrushPlus::ccAWrapMode[]={"Tile","TileFlipX","TileFlipY","TileFlipXY","Clamp","",};
const WrapMode CBrushPlus::iAWrapMode[]={WrapModeTile,WrapModeTileFlipX,WrapModeTileFlipY,WrapModeTileFlipXY,WrapModeClamp,
		WrapModeTile,};


const HatchStyle CBrushPlus::iAHatchStyle[]={
			HatchStyleHorizontal,            HatchStyleVertical,              HatchStyleForwardDiagonal,       
			HatchStyleBackwardDiagonal,      HatchStyleCross,                 HatchStyleDiagonalCross,         
			HatchStyle05Percent,             HatchStyle10Percent,             HatchStyle20Percent,             
			HatchStyle25Percent,             HatchStyle30Percent,             HatchStyle40Percent,             
			HatchStyle50Percent,             HatchStyle60Percent,             HatchStyle70Percent,             
			HatchStyle75Percent,             HatchStyle80Percent,             HatchStyle90Percent,             
			HatchStyleLightDownwardDiagonal, HatchStyleLightUpwardDiagonal,   HatchStyleDarkDownwardDiagonal,  
			HatchStyleDarkUpwardDiagonal,    HatchStyleWideDownwardDiagonal,  HatchStyleWideUpwardDiagonal,    
			HatchStyleLightVertical,         HatchStyleLightHorizontal,       HatchStyleNarrowVertical,        
			HatchStyleNarrowHorizontal,      HatchStyleDarkVertical,          HatchStyleDarkHorizontal,        
			HatchStyleDashedDownwardDiagonal,HatchStyleDashedUpwardDiagonal,  HatchStyleDashedHorizontal,      
			HatchStyleDashedVertical,        HatchStyleSmallConfetti,         HatchStyleLargeConfetti,         
			HatchStyleZigZag,                HatchStyleWave,                  HatchStyleDiagonalBrick,         
			HatchStyleHorizontalBrick,       HatchStyleWeave,                 HatchStylePlaid,                 
			HatchStyleDivot,                 HatchStyleDottedGrid,            HatchStyleDottedDiamond,         
			HatchStyleShingle,               HatchStyleTrellis,               HatchStyleSphere,                
			HatchStyleSmallGrid,             HatchStyleSmallCheckerBoard,     HatchStyleLargeCheckerBoard,     
			HatchStyleOutlinedDiamond,       HatchStyleSolidDiamond,          HatchStyleHorizontal,
			HatchStyleHorizontal,};

const char *CBrushPlus::ccAHatchStyle[]={
			"Horizontal",            "Vertical",              "ForwardDiagonal",       
			"BackwardDiagonal",      "Cross",                 "DiagonalCross",         
			"05Percent",             "10Percent",             "20Percent",             
			"25Percent",             "30Percent",             "40Percent",             
			"50Percent",             "60Percent",             "70Percent",             
			"75Percent",             "80Percent",             "90Percent",             
			"LightDownwardDiagonal", "LightUpwardDiagonal",   "DarkDownwardDiagonal",  
			"DarkUpwardDiagonal",    "WideDownwardDiagonal",  "WideUpwardDiagonal",    
			"LightVertical",         "LightHorizontal",       "NarrowVertical",        
			"NarrowHorizontal",      "DarkVertical",          "DarkHorizontal",        
			"DashedDownwardDiagonal","DashedUpwardDiagonal",  "DashedHorizontal",      
			"DashedVertical",        "SmallConfetti",         "LargeConfetti",         
			"ZigZag",                "Wave",                  "DiagonalBrick",         
			"HorizontalBrick",       "Weave",                 "Plaid",                 
			"Divot",                 "DottedGrid",            "DottedDiamond",         
			"Shingle",               "Trellis",               "Sphere",                
			"SmallGrid",             "SmallCheckerBoard",     "LargeCheckerBoard",     
			"OutlinedDiamond",       "SolidDiamond",          "","","",
			};



const UINT CBrushPlus::uNMethods=42;
const char *CBrushPlus::cArrMethods[]={
/*00*/		"GetType","GetLastStatus","GetBackgroundColor","GetForegroundColor","GetHatchStyle",
/*05*/		"GetBlend","GetBlendCount","GetGammaCorrection","GetInterpolationColorCount","GetInterpolationColors",
/*10*/		"GetLinearColors","GetRectangle","GetRectangleF","GetTransform","GetWrapMode",
/*15*/		"MultiplyTransform","ResetTransform","RotateTransform","ScaleTransform","SetBlend",
/*20*/		"SetBlendBellShape","SetBlendTriangularShape","SetGammaCorrection","SetInterpolationColors","SetLinearColors",
/*25*/		"SetTransform","SetWrapMode","TranslateTransform","GetCenterColor","GetCenterPoint",
/*30*/		"GetCenterPointF","GetFocusScales","GetPointCount","GetSurroundColorCount","GetSurroundColors",
/*35*/		"SetCenterPointF","SetCenterPoint","SetFocusScales","SetGraphicsPath","SetSurroundColors",
/*40*/		"GetColor","SetColor","","","",
/*45*/		"","","","","",
	};
const char *CBrushPlus::cArrMethodsParams[]={
/*00*/		"","","","","",
/*05*/		"","","","","",
/*10*/		"","","","","",
/*15*/		"Order,m11,m12,m21,m22,dx,dy","","Order,angle","Order,sx,sy","blendFactors,blendPositions[;blendFactors,blendPositions]...",
/*20*/		"sx,sy","sx,sy","bCorrection","blendPosition,R,G,B,A[[;blendPosition,R,G,B,A]....]","R1,G1,B1,A1,R2,G2,B2,A2",
/*25*/		"m11,m12,m21,m22,dx,dy","WrapMode","Order,dx,dy","","",
/*30*/		"","not implemented","","","",
/*35*/		"X,Y","X,Y","xScale,yScale","ContextName,nGraphPath","R,G,B,A[[;R,G,B,A]....]",
/*40*/		"","R,G,B,A","","","",
/*45*/		"","","","","",
	};


CBrushPlus::CBrushPlus(CODContext *ip_Context, IN const CBrushPlus *iBrush)
{
	p_Context=ip_Context;
	if (iBrush)
		m_Brush=iBrush->m_Brush->Clone();
	else
		m_Brush=new SolidBrush(Color(255,0,0,0));
}

CBrushPlus::CBrushPlus(CODContext *ip_Context, IN const char *iStr)
{
	// type,
	if (iStr) CreationString=iStr;
	int i;
	p_Context=ip_Context;
	CString csTmp=ExtractField(iStr,1,",");
	DWORD dwType=atoi(iStr);
	if (dwType==0 && *iStr!='0')
	{
		for(i=0;*ccABrushType[i] && _stricmp(ccABrushType[i],csTmp)!=0;i++);
		dwType=iABrushType[i];
	}
	iStr=strchr(iStr,',');
	if (iStr++==NULL) iStr="";
	csTmp=ExtractField(iStr,1,",");
	m_Brush=NULL;
	if (*iStr)
	{
		switch(dwType)
		{
		case BrushTypeHatchFill:
			{
				DWORD dwHatchStyle=atoi(iStr);
				if (*iStr!='0' || csTmp.GetLength()>4)
				{
					for(i=0;*ccAHatchStyle[i] && _stricmp(ccAHatchStyle[i],csTmp)!=0;i++);
					dwHatchStyle=iAHatchStyle[i];
				}
				iStr=strchr(iStr,',');
				if (iStr++==NULL) iStr="";
				if (*iStr>='0' && *iStr<='9')
				{
					int R1=0,G1=0,B1=0,A1=255,R2=0,G2=0,B2=0,A2=255;
					sscanf(iStr,"%d,%d,%d,%d,%d,%d,%d,%d,",&R1,&G1,&B1,&A1,&R2,&G2,&B2,&A2);
					m_Brush=new HatchBrush((Gdiplus::HatchStyle)dwHatchStyle,  Color(A1,R1,G1,B1), Color(A2,R2,G2,B2));
				}
				else
				{//CLR(...),CLR(...)
					PDCIPARAMETER mparam=NULL;
					DCParamType pta[]={DCPT_COLOR,DCPT_COLOR,DCPT_NONE};
					UINT tmpNParams=0;
					CODContextItem::TranslateParams(iStr,pta,p_Context,&(mparam),&tmpNParams);
					if (mparam)
					{
						if ((mparam[0].dwParamType&DCPT_TYPEMASK)==DCPT_COLOR && (mparam[1].dwParamType&DCPT_TYPEMASK)==DCPT_COLOR)
						{
							if (p_Context) 
							{
								CODContextItem::PrepareParameter(p_Context,&(mparam[0]));
								CODContextItem::PrepareParameter(p_Context,&(mparam[1]));
							}
							m_Brush=new HatchBrush((Gdiplus::HatchStyle)dwHatchStyle,*(mparam[0].m_pColor), *(mparam[1].m_pColor));
						}
						CODContextItem::ResetParameters(&mparam,&tmpNParams);
						delete []mparam;
					}
				}
			}
			break;
		case BrushTypeTextureFill:
			{  // ImageContext,ImageNum,WrapMode,dstX,dstY,dstWidth,dstHeight
				const char *iStr2=FindField(iStr,3,",");
				if (!iStr2) iStr2="";
				if (strstr(iStr,"ILIST(") || strstr(iStr,"BITMAP("))
				{
					PDCIPARAMETER mparam=NULL;
					DCParamType pta[]={DCPT_IMAGE,(DCParamType)(DCPT_FLAG|DCPTF_BRUSHWRAPMODE),DCPT_RECT,DCPT_NONE};
					UINT tmpNParams=0;
					CODContextItem::TranslateParams(iStr,pta,p_Context,&(mparam),&tmpNParams);
					if (mparam)
					{
						if (p_Context && ((mparam[0].dwParamType&DCPT_TYPEMASK)==DCPT_IMAGE || (mparam[0].dwParamType&DCPT_TYPEMASK)==DCPT_IMAGELIST))
						{
							CODContextItem::PrepareParameter(p_Context,&(mparam[0]));
							CODContextItem::PrepareParameter(p_Context,&(mparam[1]));
							CODContextItem::PrepareParameter(p_Context,&(mparam[2]));
							if (mparam[0].m_pBitmap->m_Bitmap)
							{
								UINT ImgH=mparam[0].m_pBitmap->m_Bitmap->GetHeight(), ImgW=mparam[0].m_pBitmap->m_Bitmap->GetWidth();
								if (mparam[2].m_pRectF->X<0) mparam[2].m_pRectF->X=0;
								if (mparam[2].m_pRectF->Y<0) mparam[2].m_pRectF->Y=0;
								if (mparam[2].m_pRectF->X>=mparam[2].m_pRectF->Width) mparam[2].m_pRectF->X=0;
								if (mparam[2].m_pRectF->Y>=mparam[2].m_pRectF->Height) mparam[2].m_pRectF->Y=0;
								if (ImgW<mparam[2].m_pRectF->Width+mparam[2].m_pRectF->X) mparam[2].m_pRectF->Width=ImgW-mparam[2].m_pRectF->X;
								if (ImgH<mparam[2].m_pRectF->Height+mparam[2].m_pRectF->Y) mparam[2].m_pRectF->Height=ImgH-mparam[2].m_pRectF->Y;
								m_Brush=new TextureBrush(mparam[0].m_pBitmap->m_Bitmap,(Gdiplus::WrapMode)(mparam[1].m_dword),*(mparam[2].m_pRectF));
							}
						}
						CODContextItem::ResetParameters(&mparam,&tmpNParams);
						delete []mparam;
					}
				}
				else
				{
					Image *ptmpImage=NULL;
					{
						CODContext *ocontext=(csTmp=="" && p_Context)?p_Context:GPC.m_View->m_ODContextsArray->GetContext(csTmp);
						UINT nImage=atoi(ExtractField(iStr,2,","));
						if (nImage < ocontext->m_nBitmapArray && ocontext->m_BitmapArr[nImage])
							ptmpImage=ocontext->m_BitmapArr[nImage]->m_Bitmap;
					}
					if (!ptmpImage)
					{
						ptmpImage=new Image(L"");
						m_Brush=new TextureBrush(ptmpImage, WrapModeTile);
						delete ptmpImage;
					}
					else
					{
						DWORD dwWrapMode=atoi(iStr2);
						if (dwWrapMode==0 && *iStr2!='0')
						{
							CString tmpWM=ExtractField(iStr2,1,",");
							for(i=0;*ccAWrapMode[i] && _stricmp(ccAWrapMode[i],tmpWM)!=0;i++);
							dwWrapMode=iAWrapMode[i];
						}
						iStr2=strchr(iStr2,',');
						if (!iStr2++)	m_Brush=new TextureBrush(ptmpImage, (Gdiplus::WrapMode)dwWrapMode);
						else
						if (*iStr2>='0' && *iStr2<='9')
						{
							REAL dstX=0, dstY=0, dstWidth=0, dstHeight=0;
							UINT ImgH=ptmpImage->GetHeight(), ImgW=ptmpImage->GetWidth();
							sscanf(iStr2,"%g,%g,%g,%g",&dstX,&dstY,&dstWidth,&dstHeight);
							if (dstX<0) dstX=0;
							if (dstY<0) dstY=0;
							if (dstX>=dstWidth) dstX=0;
							if (dstY>=dstHeight) dstY=0;
							if (ImgW<dstWidth+dstX) dstWidth=ImgW-dstX;
							if (ImgH<dstHeight+dstY) dstHeight=ImgH-dstY;

							m_Brush=new TextureBrush(ptmpImage, (Gdiplus::WrapMode)dwWrapMode,dstX,dstY,dstWidth,dstHeight);
						}
						else
						{
							//rect(...)
							PDCIPARAMETER mparam=NULL;
							DCParamType pta[]={DCPT_RECT,DCPT_NONE};
							UINT tmpNParams=0;
							CODContextItem::TranslateParams(iStr,pta,p_Context,&(mparam),&tmpNParams);
							if (mparam)
							{
								if ((mparam[0].dwParamType&DCPT_TYPEMASK)==DCPT_RECT)
								{
									if (p_Context) 
									{
										CODContextItem::PrepareParameter(p_Context,&(mparam[0]));
									}
									m_Brush=new TextureBrush(ptmpImage, (Gdiplus::WrapMode)dwWrapMode,*(mparam[0].m_pRectF));
								}
								CODContextItem::ResetParameters(&mparam,&tmpNParams);
								delete []mparam;
							}
						}
					}
				}
			}
			break;
		case BrushTypePathGradient:
			{
				if (ExtractField(iStr,3,",") == "")
				{
					CODContext *ocontext=(*iStr==0 && p_Context)?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ExtractField(iStr,1,","));
					UINT nPath=atoi(ExtractField(iStr,2,","));
					if (nPath < ocontext->m_nGraphPathArray && ocontext->m_GraphPathArr[nPath])
						m_Brush=new PathGradientBrush(ocontext->m_GraphPathArr[nPath]->m_GraphicsPath);
					else
						m_Brush=new SolidBrush(Color(255,0,0,0));
				}
				else
				if (strstr(iStr,"PATH("))
				{ // PATH()
					PDCIPARAMETER mparam=NULL;
					DCParamType pta[]={DCPT_PATH,DCPT_NONE};
					UINT tmpNParams=0;
					CODContextItem::TranslateParams(iStr,pta,p_Context,&(mparam),&tmpNParams);
					if (mparam)
					{
						if (p_Context && (mparam[0].dwParamType&DCPT_TYPEMASK)==DCPT_FLAG && (mparam[1].dwParamType&DCPT_TYPEMASK)==DCPT_PATH)
						{
							CODContextItem::PrepareParameter(p_Context,&(mparam[0]));
							CODContextItem::PrepareParameter(p_Context,&(mparam[1]));
							m_Brush=new PathGradientBrush(mparam[1].m_pPath->m_GraphicsPath);
						}
						CODContextItem::ResetParameters(&mparam,&tmpNParams);
						delete []mparam;
					}

				}
				if (strstr(iStr,"FLAG("))
				{ // FLAG(wrapMode),ARRAYPTS()
					PDCIPARAMETER mparam=NULL;
					DCParamType pta[]={(DCParamType)(DCPT_FLAG|DCPTF_BRUSHWRAPMODE),DCPT_ARRAY,DCPT_NONE};
					UINT tmpNParams=0;
					CODContextItem::TranslateParams(iStr,pta,p_Context,&(mparam),&tmpNParams);
					if (p_Context && mparam && (mparam[0].dwParamType&DCPT_TYPEMASK)==DCPT_INTEGER)
					{
						CODContextItem::PrepareParameter(p_Context,&(mparam[0]));
						CODContextItem::PrepareParameter(p_Context,&(mparam[1]));
						m_Brush=new PathGradientBrush(mparam[1].m_pPointF,mparam[1].dwNElements,(Gdiplus::WrapMode)mparam[0].m_dword);
						CODContextItem::ResetParameters(&mparam,&tmpNParams);
					}
					if (mparam) delete []mparam;
				}
				else
				{	// wrapMode,pointsX1,pointsY1;pointsX2,pointsY2;....
					DWORD dwWrapMode=atoi(iStr);
					if (dwType==0 && *iStr!='0')
					{
						for(i=0;*ccAWrapMode[i] && _stricmp(ccAWrapMode[i],csTmp)!=0;i++);
						dwWrapMode=iAWrapMode[i];
					}
					int nArr=1;
					iStr=strchr(iStr,',');
					if (iStr++==NULL) iStr="";
					const char *pos2=iStr;
					while(*pos2) if (*(pos2++)==',') nArr++;
					nArr/=2;
					if (nArr>1)
					{
						PointF *arr1=new PointF [nArr+10];
						pos2=iStr;
						PointF *arrPos1=arr1;
					
						while(*pos2)
						{
							arrPos1->X=(REAL)atof(pos2);
							while(*pos2 && *pos2!=',') pos2++;
							if (*pos2) pos2++;
							arrPos1->Y=(REAL)atof(pos2);
							while(*pos2 && *pos2!=',' && *pos2!=';') pos2++;
							if (*pos2) pos2++;
							arrPos1++;
						}
						m_Brush= new PathGradientBrush(arr1,nArr,(Gdiplus::WrapMode)dwWrapMode);
						delete [] arr1;
					}
				}
			}
			break;
		case BrushTypeLinearGradient: 
			{
				const char *pos3=FindFieldEx(iStr,5,",");
				const char *pos4=strchr(pos3?pos3:"",',');
				LinearGradientMode lgm;
				if (pos3 && !pos4)
				{
					lgm=(Gdiplus::LinearGradientMode)atoi(pos3);
					if (*pos3 && *pos3!='0' && lgm==LinearGradientModeHorizontal)
					{
						int i;
						for(i=0;*ccALinearGradientMode[i] && _stricmp(pos3,ccALinearGradientMode[i])!=0;i++);
						lgm=iALinearGradientMode[i];
					}
				}

				if (*iStr=='P' || *iStr=='p')
				{
					// POINT1,POINT2,COLOR1,COLOR2[,mode|[angle,isAngleScalable]]
					PDCIPARAMETER mparam=NULL;
					DCParamType pta[]={DCPT_POINT,DCPT_POINT,DCPT_COLOR,DCPT_COLOR,DCPT_NONE};
					UINT tmpNParams=0;
					CODContextItem::TranslateParams(iStr,pta,p_Context,&(mparam),&tmpNParams);
					if (mparam)
					{
						if ((mparam[0].dwParamType&DCPT_TYPEMASK)==DCPT_POINT && (mparam[1].dwParamType&DCPT_TYPEMASK)==DCPT_POINT 
						 && (mparam[2].dwParamType&DCPT_TYPEMASK)==DCPT_COLOR && (mparam[3].dwParamType&DCPT_TYPEMASK)==DCPT_COLOR)
						{
							if (p_Context) 
							{
								CODContextItem::PrepareParameter(p_Context,&(mparam[0]));
								CODContextItem::PrepareParameter(p_Context,&(mparam[1]));
								CODContextItem::PrepareParameter(p_Context,&(mparam[2]));
								CODContextItem::PrepareParameter(p_Context,&(mparam[3]));
							}
							if (!pos3)
							{
								m_Brush=new LinearGradientBrush( *(mparam[0].m_pPointF), *(mparam[1].m_pPointF), *(mparam[2].m_pColor), *(mparam[3].m_pColor));
							}
							else	
							{
								RectF re(mparam[0].m_pPointF->X,mparam[0].m_pPointF->Y,mparam[1].m_pPointF->X-mparam[0].m_pPointF->X,mparam[1].m_pPointF->Y-mparam[0].m_pPointF->Y);

								if (pos4)	m_Brush=new LinearGradientBrush(re, *(mparam[2].m_pColor), *(mparam[3].m_pColor), (REAL) atof(pos3), atoi(pos4));
								else		m_Brush=new LinearGradientBrush(re, *(mparam[2].m_pColor), *(mparam[3].m_pColor), lgm);
							}
						}
						CODContextItem::ResetParameters(&mparam,&tmpNParams);
						delete []mparam;
					}
				}
				else
				{
					// X1,Y1,X2,Y2,R1,G1,B1,A1,R2,G2,B2,A2[,mode|[angle,isAngleScalable]]
					REAL X1=0,Y1=0,X2=0,Y2=0;
					int R1=0,G1=0,B1=0,A1=255,R2=0,G2=0,B2=0,A2=255;
					sscanf(iStr,"%g,%g,%g,%g,%d,%d,%d,%d,%d,%d,%d,%d,",&X1,&Y1,&X2,&Y2,&R1,&G1,&B1,&A1,&R2,&G2,&B2,&A2);
					if (!pos3)	m_Brush=new LinearGradientBrush(PointF(X1,Y1), PointF(X2,Y2), Color(A1,R1,G1,B1), Color(A2,R2,G2,B2));
					else		
						if (pos4)	m_Brush=new LinearGradientBrush(RectF(X1,Y1,X2-X1,Y2-Y1), Color(A1,R1,G1,B1), Color(A2,R2,G2,B2), (REAL) atof(pos3), atoi(pos4));
						else		m_Brush=new LinearGradientBrush(RectF(X1,Y1,X2-X1,Y2-Y1), Color(A1,R1,G1,B1), Color(A2,R2,G2,B2), lgm);
				}
			}
			break;
		case BrushTypeSolidColor:
		default:
			m_Brush=new SolidBrush(Color(CODContext::GetColorFromString(p_Context,iStr)));
			break;
		}	

	}
	if (!m_Brush)	m_Brush=new SolidBrush(Color(255,0,0,0));

}


CBrushPlus::CBrushPlus(CODContext *ip_Context, IN const Color& color)
{
	m_Brush=new SolidBrush(color);
	p_Context=ip_Context;
}

CBrushPlus::CBrushPlus(CODContext *ip_Context, IN Image* image, IN WrapMode wrapMode)
{
	m_Brush=new TextureBrush(image, wrapMode);
	p_Context=ip_Context;
}
CBrushPlus::CBrushPlus(CODContext *ip_Context, IN Image* image, IN WrapMode wrapMode, IN const RectF &dstRect)
{
	p_Context=ip_Context;
	m_Brush=new TextureBrush(image, wrapMode, dstRect);
}

CBrushPlus::CBrushPlus(CODContext *ip_Context, IN Image *image, IN const RectF &dstRect, IN const ImageAttributes *imageAttributes)
{
	p_Context=ip_Context;
	m_Brush=new TextureBrush(image, dstRect, imageAttributes);
}

CBrushPlus::CBrushPlus(CODContext *ip_Context, IN Image *image, IN const Rect &dstRect, IN const ImageAttributes *imageAttributes)
{
	p_Context=ip_Context;
	m_Brush=new TextureBrush(image, dstRect, imageAttributes);
}

CBrushPlus::CBrushPlus(CODContext *ip_Context, IN Image* image, IN WrapMode wrapMode, const IN Rect &dstRect)
{
	p_Context=ip_Context;
	m_Brush=new TextureBrush(image, wrapMode, dstRect);
}

CBrushPlus::CBrushPlus(CODContext *ip_Context, IN Image* image, IN WrapMode wrapMode, IN REAL dstX, IN REAL dstY, IN REAL dstWidth, IN REAL dstHeight)
{
	p_Context=ip_Context;
	m_Brush=new TextureBrush(image, wrapMode, dstX, dstY, dstWidth, dstHeight);
}

CBrushPlus::CBrushPlus(CODContext *ip_Context, IN Image* image, IN WrapMode wrapMode, IN INT dstX, IN INT dstY, IN INT dstWidth, IN INT dstHeight)
{
	p_Context=ip_Context;
	m_Brush=new TextureBrush(image, wrapMode, dstX, dstY, dstWidth, dstHeight);
}

CBrushPlus::CBrushPlus(CODContext *ip_Context, IN const PointF& point1, IN const PointF& point2, IN const Color& color1, IN const Color& color2)
{
	p_Context=ip_Context;
	m_Brush=new LinearGradientBrush(point1, point2, color1, color2);
}

CBrushPlus::CBrushPlus(CODContext *ip_Context, IN const Point& point1, IN const Point& point2, IN const Color& color1, IN const Color& color2)
{
	p_Context=ip_Context;
	m_Brush=new LinearGradientBrush(point1, point2, color1, color2);
}

CBrushPlus::CBrushPlus(CODContext *ip_Context, IN const RectF& rect, IN const Color& color1, IN const Color& color2, IN LinearGradientMode mode)
{
	p_Context=ip_Context;
	m_Brush=new LinearGradientBrush(rect, color1, color2, mode);
}

CBrushPlus::CBrushPlus(CODContext *ip_Context, IN const Rect& rect, IN const Color& color1, IN const Color& color2, IN LinearGradientMode mode)
{
	p_Context=ip_Context;
	m_Brush=new LinearGradientBrush(rect, color1, color2, mode);
}

CBrushPlus::CBrushPlus(CODContext *ip_Context, IN const RectF& rect, IN const Color& color1, IN const Color& color2, IN REAL angle, IN BOOL isAngleScalable)
{
	p_Context=ip_Context;
	m_Brush=new LinearGradientBrush(rect, color1, color2, angle, isAngleScalable);
}

CBrushPlus::CBrushPlus(CODContext *ip_Context, IN const Rect& rect, IN const Color& color1, IN const Color& color2, IN REAL angle, IN BOOL isAngleScalable)
{
	p_Context=ip_Context;
	m_Brush=new LinearGradientBrush(rect, color1, color2, angle, isAngleScalable);
}

CBrushPlus::CBrushPlus(CODContext *ip_Context, IN HatchStyle hatchStyle, IN const Color& foreColor, IN const Color& backColor)
{
	p_Context=ip_Context;
	m_Brush=new HatchBrush(hatchStyle, foreColor, backColor);
}

CBrushPlus::CBrushPlus(CODContext *ip_Context, IN const PointF* points, IN INT count, IN WrapMode wrapMode)
{
	p_Context=ip_Context;
	m_Brush=new PathGradientBrush(points, count, wrapMode);
}

CBrushPlus::CBrushPlus(CODContext *ip_Context, IN const Point* points, IN INT count, IN WrapMode wrapMode)
{
	p_Context=ip_Context;
	m_Brush=new PathGradientBrush(points, count, wrapMode);
}

CBrushPlus::CBrushPlus(CODContext *ip_Context, IN const GraphicsPath* path)
{
	p_Context=ip_Context;
	m_Brush=new PathGradientBrush(path);
}

CBrushPlus::~CBrushPlus()
{
	if (m_Brush) delete m_Brush;
	m_Brush=NULL;
}


UINT CBrushPlus::DoMethod(const char *iStr, char *oStr)
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

	BrushType m_BrushType=m_Brush->GetType();

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
	case  0: //GetType
		retint=m_BrushType;
		break; 
	case  1: //GetLastStatus 
		retint=m_Brush->GetLastStatus();
		break; 
	case  2: // GetBackgroundColor
		if (oStr && m_BrushType==BrushTypeHatchFill)
		{
			Color clr;
			((HatchBrush *)m_Brush)->GetBackgroundColor(&clr);
			sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",clr.GetR(),clr.GetG(),clr.GetB(),clr.GetA());
		}
		break; 
	case  3: // GetForegroundColor
		if (oStr && m_BrushType==BrushTypeHatchFill)
		{
			Color clr;
			((HatchBrush *)m_Brush)->GetForegroundColor(&clr);
			sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",clr.GetR(),clr.GetG(),clr.GetB(),clr.GetA());
		}
		break; 
	case  4: // GetHatchStyle
		if (m_BrushType==BrushTypeHatchFill) retint=((HatchBrush *)m_Brush)->GetHatchStyle();
		break; 

	case  5: // GetBlend
		if (oStr && (m_BrushType==BrushTypeLinearGradient || m_BrushType==BrushTypePathGradient))
		{
			INT count=(m_BrushType==BrushTypeLinearGradient)?((LinearGradientBrush *)m_Brush)->GetBlendCount():((PathGradientBrush *)m_Brush)->GetBlendCount();
			REAL *blendFactors=new REAL [count+10];
			REAL *blendPositions=new REAL [count+10];
			retint=(m_BrushType==BrushTypeLinearGradient)?((LinearGradientBrush *)m_Brush)->GetBlend(blendFactors,blendPositions,count):((PathGradientBrush *)m_Brush)->GetBlend(blendFactors,blendPositions,count);
			INT i;
			char *posout=oStr;
			for(i=0;i<count;i++)
			{
				if (i) *(posout++)=0x7F;
				*(posout)=0;
				posout+=sprintf(posout,"%g\x7%g",blendFactors[i],blendPositions[i]);
			}
			delete []blendPositions;
			delete []blendFactors;
		}
		break; 
	case  6: // GetBlendCount
		if (m_BrushType==BrushTypeLinearGradient || m_BrushType==BrushTypePathGradient)
		{
			retint=(m_BrushType==BrushTypeLinearGradient)?((LinearGradientBrush *)m_Brush)->GetBlendCount():((PathGradientBrush *)m_Brush)->GetBlendCount();
		}
		break; 
	case  7: // GetGammaCorrection
		if (m_BrushType==BrushTypeLinearGradient || m_BrushType==BrushTypePathGradient)
			retint=(m_BrushType==BrushTypeLinearGradient)?((LinearGradientBrush *)m_Brush)->GetGammaCorrection():((PathGradientBrush *)m_Brush)->GetGammaCorrection();
		break; 
	case  8: // GetInterpolationColorCount
		if (m_BrushType==BrushTypeLinearGradient || m_BrushType==BrushTypePathGradient)
			retint=(m_BrushType==BrushTypeLinearGradient)?((LinearGradientBrush *)m_Brush)->GetInterpolationColorCount():((PathGradientBrush *)m_Brush)->GetInterpolationColorCount();
		break; 
	case  9: // GetInterpolationColors
		if (oStr && (m_BrushType==BrushTypeLinearGradient || m_BrushType==BrushTypePathGradient))
		{
			INT count=(m_BrushType==BrushTypeLinearGradient)?((LinearGradientBrush *)m_Brush)->GetInterpolationColorCount():((PathGradientBrush *)m_Brush)->GetInterpolationColorCount();
			Color *presetColors=new Color [count+10];
			REAL *blendPositions=new REAL [count+10];
			retint=(m_BrushType==BrushTypeLinearGradient)?((LinearGradientBrush *)m_Brush)->GetInterpolationColors(presetColors,blendPositions,count):((PathGradientBrush *)m_Brush)->GetInterpolationColors(presetColors,blendPositions,count);
			INT i;
			char *posout=oStr;
			for(i=0;i<count;i++)
			{
				if (i) *(posout++)=0x7F;
				*(posout)=0;
				posout+=sprintf(posout,"%d\x3%d\x3%d\x3%d\x7%g",presetColors[i].GetR(),presetColors[i].GetG(),presetColors[i].GetB(),presetColors[i].GetA(),blendPositions[i]);
			}
			delete []blendPositions;
			delete []presetColors;
		}
		break; 
	case 10: // GetLinearColors
		if (oStr && m_BrushType==BrushTypeLinearGradient)
		{
			Color clr[2];
			((LinearGradientBrush *)m_Brush)->GetLinearColors(clr);
			sprintf(oStr,"%d\x7%d\x7%d\x7%d\x7F%d\x7%d\x7%d\x7%d",clr[0].GetR(),clr[0].GetG(),clr[0].GetB(),clr[0].GetA(),clr[1].GetR(),clr[1].GetG(),clr[1].GetB(),clr[1].GetA());
		}
		break; 
	case 11: // GetRectangle
		if (oStr && (m_BrushType==BrushTypeLinearGradient || m_BrushType==BrushTypePathGradient))
		{
			Rect re;
			if (m_BrushType==BrushTypeLinearGradient)
				((LinearGradientBrush *)m_Brush)->GetRectangle(&re);
			else
				((PathGradientBrush *)m_Brush)->GetRectangle(&re);
			sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.X,re.Y,re.Width,re.Height);
		}
		break; 
	case 12: // GetRectangleF
		if (oStr && (m_BrushType==BrushTypeLinearGradient || m_BrushType==BrushTypePathGradient))
		{
			RectF re;
			if (m_BrushType==BrushTypeLinearGradient)
				((LinearGradientBrush *)m_Brush)->GetRectangle(&re);
			else
				((PathGradientBrush *)m_Brush)->GetRectangle(&re);
			sprintf(oStr,"%g\x7F%g\x7F%g\x7F%g",re.X,re.Y,re.Width,re.Height);
		}
		break; 
	case 13: // GetTransform
		if (oStr && (m_BrushType==BrushTypeLinearGradient || m_BrushType==BrushTypePathGradient || m_BrushType==BrushTypeTextureFill))
		{
			Matrix ma;
			if (m_BrushType==BrushTypeLinearGradient)
				((LinearGradientBrush *)m_Brush)->GetTransform(&ma);
			else
			if (m_BrushType==BrushTypePathGradient)
				((PathGradientBrush *)m_Brush)->GetTransform(&ma);
			else
			if (m_BrushType==BrushTypeTextureFill)
				((TextureBrush *)m_Brush)->GetTransform(&ma);
			REAL rea[10]={0};
			ma.GetElements(rea);
			sprintf(oStr,"%g\x7F%g\x7F%g\x7F%g\x7F%g\x7F%g",rea[0],rea[1],rea[2],rea[3],rea[4],rea[5]);
		}
		break; 
	case 14: // GetWrapMode
		if (m_BrushType==BrushTypeLinearGradient)
			retint=((LinearGradientBrush *)m_Brush)->GetWrapMode();
		else
		if (m_BrushType==BrushTypePathGradient)
			retint=((PathGradientBrush *)m_Brush)->GetWrapMode();
		else
		if (m_BrushType==BrushTypeTextureFill)
			retint=((TextureBrush *)m_Brush)->GetWrapMode();
		break; 
	case 15: // MultiplyTransform
		if (m_BrushType==BrushTypeLinearGradient || m_BrushType==BrushTypePathGradient || m_BrushType==BrushTypeTextureFill)
		{
			Matrix ma;
			DWORD dwOrder=0;
			REAL rea[10]={0};
			sscanf(pos,"%d,%g,%g,%g,%g,%g,%g",&dwOrder,rea,rea+1,rea+2,rea+3,rea+4,rea+5);
			ma.SetElements(rea[0],rea[1],rea[2],rea[3],rea[4],rea[5]);
			if (m_BrushType==BrushTypeLinearGradient)
				((LinearGradientBrush *)m_Brush)->MultiplyTransform(&ma,(Gdiplus::MatrixOrder)dwOrder);
			else
			if (m_BrushType==BrushTypePathGradient)
				((PathGradientBrush *)m_Brush)->MultiplyTransform(&ma,(Gdiplus::MatrixOrder)dwOrder);
			else
			if (m_BrushType==BrushTypeTextureFill)
				((TextureBrush *)m_Brush)->MultiplyTransform(&ma,(Gdiplus::MatrixOrder)dwOrder);
			if (oStr) DoMethod("GetTransform",oStr);
		}
		break; 
	case 16: // ResetTransform
		if (m_BrushType==BrushTypeLinearGradient)
			retint=((LinearGradientBrush *)m_Brush)->ResetTransform();
		else
		if (m_BrushType==BrushTypePathGradient)
			retint=((PathGradientBrush *)m_Brush)->ResetTransform();
		else
		if (m_BrushType==BrushTypeTextureFill)
			retint=((TextureBrush *)m_Brush)->ResetTransform();
		break; 
	case 17: // RotateTransform
		if (m_BrushType==BrushTypeLinearGradient || m_BrushType==BrushTypePathGradient || m_BrushType==BrushTypeTextureFill)
		{
			DWORD dwOrder=0;
			REAL rea=0;
			sscanf(pos,"%d,%g",&dwOrder,&rea);
			if (m_BrushType==BrushTypeLinearGradient)
				((LinearGradientBrush *)m_Brush)->RotateTransform(rea,(Gdiplus::MatrixOrder)dwOrder);
			else
			if (m_BrushType==BrushTypePathGradient)
				((PathGradientBrush *)m_Brush)->RotateTransform(rea,(Gdiplus::MatrixOrder)dwOrder);
			else
			if (m_BrushType==BrushTypeTextureFill)
				((TextureBrush *)m_Brush)->RotateTransform(rea,(Gdiplus::MatrixOrder)dwOrder);
			if (oStr) DoMethod("GetTransform",oStr);
		}
		break; 
	case 18: // ScaleTransform
		if (m_BrushType==BrushTypeLinearGradient || m_BrushType==BrushTypePathGradient || m_BrushType==BrushTypeTextureFill)
		{
			REAL sx=0;
			REAL sy=0;
			DWORD dwOrder=0;
			sscanf(pos,"%d,%g,%g",&dwOrder,&sx,&sy);
			if (m_BrushType==BrushTypeLinearGradient)
				((LinearGradientBrush *)m_Brush)->ScaleTransform(sx,sy,(Gdiplus::MatrixOrder)dwOrder);
			else
			if (m_BrushType==BrushTypePathGradient)
				((PathGradientBrush *)m_Brush)->ScaleTransform(sx,sy,(Gdiplus::MatrixOrder)dwOrder);
			else
			if (m_BrushType==BrushTypeTextureFill)
				((TextureBrush *)m_Brush)->ScaleTransform(sx,sy,(Gdiplus::MatrixOrder)dwOrder);
			if (oStr) DoMethod("GetTransform",oStr);
		}
		break; 
	case 19: // SetBlend
		if (m_BrushType==BrushTypeLinearGradient || m_BrushType==BrushTypePathGradient)
		{
			if (oStr) DoMethod("GetBlend",oStr);
			int nArr=1;
			const char *pos2=pos;
			while(*pos2) if (*(pos2++)==',') nArr++;
			nArr/=2;
			if (nArr>1)
			{
				REAL *arr1=new REAL [nArr+10];
				REAL *arr2=new REAL [nArr+10];
				pos2=pos;
				REAL *arrPos1=arr1;
				REAL *arrPos2=arr2;
				REAL lastVal1=0;
				REAL lastVal2=0;
				
				while(*pos2)
				{
					*arrPos1=(REAL)atof(pos2);
					if (*arrPos1<0 || *arrPos1>1) *arrPos1=lastVal1;
					lastVal1=*(arrPos1++);
					while(*pos2 && *pos2!=',') pos2++;
					if (*pos2) pos2++;

					*arrPos2=(REAL)atof(pos2);
					if (*arrPos2<0 || *arrPos2>1) *arrPos2=lastVal2;
					lastVal2=*(arrPos2++);
					while(*pos2 && *pos2!=',' && *pos2!=';') pos2++;
					if (*pos2) pos2++;
				}
				*arrPos1=lastVal1;
				*arrPos2=lastVal2;
				arr2[0]=0;
				arr2[nArr-1]=1;
				if (m_BrushType==BrushTypeLinearGradient)
					((LinearGradientBrush *)m_Brush)->SetBlend(arr1,arr2,nArr);
				else
				if (m_BrushType==BrushTypePathGradient)
					((PathGradientBrush *)m_Brush)->SetBlend(arr1,arr2,nArr);
				delete [] arr1;
				delete [] arr2;
			}
		}
		break; 
	case 20: // SetBlendBellShape
		if (m_BrushType==BrushTypeLinearGradient || m_BrushType==BrushTypePathGradient)
		{
			REAL sx=0;
			REAL sy=1;
			sscanf(pos,"%g,%g",&sx,&sy);
			if (m_BrushType==BrushTypeLinearGradient)
				((LinearGradientBrush *)m_Brush)->SetBlendBellShape(sx,sy);
			else
			if (m_BrushType==BrushTypePathGradient)
				((PathGradientBrush *)m_Brush)->SetBlendBellShape(sx,sy);
		}
		break; 
	case 21: // SetBlendTriangularShape
		if (m_BrushType==BrushTypeLinearGradient || m_BrushType==BrushTypePathGradient)
		{
			REAL sx=0;
			REAL sy=1;
			sscanf(pos,"%g,%g",&sx,&sy);
			if (m_BrushType==BrushTypeLinearGradient)
				((LinearGradientBrush *)m_Brush)->SetBlendTriangularShape(sx,sy);
			else
			if (m_BrushType==BrushTypePathGradient)
				((PathGradientBrush *)m_Brush)->SetBlendTriangularShape(sx,sy);
		}
		break; 
	case 22: // SetGammaCorrection
		if (m_BrushType==BrushTypeLinearGradient)
			retint=((LinearGradientBrush *)m_Brush)->SetGammaCorrection(atoipos);
		else
		if (m_BrushType==BrushTypePathGradient)
			retint=((PathGradientBrush *)m_Brush)->SetGammaCorrection(atoipos);
		break; 
	case 23: // SetInterpolationColors
		if (m_BrushType==BrushTypeLinearGradient || m_BrushType==BrushTypePathGradient)
		{
			if (oStr) DoMethod("GetInterpolationColors",oStr);
			int nArr=1;
			const char *pos2=pos;
			while(*pos2) if (*(pos2++)==',') nArr++;
			nArr/=2;
			if (nArr>1)
			{
				Color *arr1=new Color [nArr+10];
				REAL *arr2=new REAL [nArr+10];
				pos2=pos;
				Color *arrPos1=arr1;
				REAL *arrPos2=arr2;
				REAL lastVal2=0;
				
				while(*pos2)
				{
					*arrPos2=(REAL)atof(pos2);
					if (*arrPos2<0 || *arrPos2>1) *arrPos2=lastVal2;
					lastVal2=*(arrPos2++);
					while(*pos2 && *pos2!=',') pos2++;
					if (*pos2) pos2++;
					arrPos1->SetValue(CODContext::GetColorFromString(p_Context, pos2));
					arrPos1++;

					while(*pos2 && *pos2!=';') pos2++;
					if (*pos2) pos2++;
				}

				*arrPos2=lastVal2;
				arr2[0]=0;
				arr2[nArr-1]=1;
				if (m_BrushType==BrushTypeLinearGradient)
					((LinearGradientBrush *)m_Brush)->SetInterpolationColors(arr1,arr2,nArr);
				else
				if (m_BrushType==BrushTypePathGradient)
					((PathGradientBrush *)m_Brush)->SetInterpolationColors(arr1,arr2,nArr);
				delete [] arr1;
				delete [] arr2;
			}
		}
		break; 
	case 24: // SetLinearColors
		if (m_BrushType==BrushTypeLinearGradient)
		{
			int R1=0,G1=0,B1=0,A1=255;
			int R2=0,G2=0,B2=0,A2=255;
			sscanf(pos,"%d,%d,%d,%d,%d,%d,%d,%d",&R1,&G1,&B1,&A1,&R2,&G2,&B2,&A2);
			Color clr1(A1,R1,G1,B1),clr2(A2,R2,G2,B2);
			retint=((LinearGradientBrush *)m_Brush)->SetLinearColors(clr1,clr2);
		}
		break; 
	case 25: // SetTransform
		if (m_BrushType==BrushTypeLinearGradient || m_BrushType==BrushTypePathGradient || m_BrushType==BrushTypeTextureFill)
		{
			if (oStr) DoMethod("GetTransform",oStr);
			Matrix ma;
			DWORD dwOrder=0;
			REAL rea[10]={0};
			sscanf(pos,"%g,%g,%g,%g,%g,%g",rea,rea+1,rea+2,rea+3,rea+4,rea+5);
			ma.SetElements(rea[0],rea[1],rea[2],rea[3],rea[4],rea[5]);
			if (m_BrushType==BrushTypeLinearGradient)
				((LinearGradientBrush *)m_Brush)->SetTransform(&ma);
			else
			if (m_BrushType==BrushTypePathGradient)
				((PathGradientBrush *)m_Brush)->SetTransform(&ma);
			else
			if (m_BrushType==BrushTypeTextureFill)
				((TextureBrush *)m_Brush)->SetTransform(&ma);
		}
		break; 
	case 26: // SetWrapMode
		if (m_BrushType==BrushTypeLinearGradient || m_BrushType==BrushTypePathGradient || m_BrushType==BrushTypeTextureFill)
		{
			if (m_BrushType==BrushTypeLinearGradient)
				retint=((LinearGradientBrush *)m_Brush)->GetWrapMode();
			else
			if (m_BrushType==BrushTypePathGradient)
				retint=((PathGradientBrush *)m_Brush)->GetWrapMode();
			WrapMode CapToset=(WrapMode)atoipos;
			if (*pos!='0' &&  CapToset==0)
			{
				int i;
				for(i=0; *ccAWrapMode[i] && _stricmp(pos,ccAWrapMode[i])!=0;i++);
				CapToset=iAWrapMode[i];
			}
			if (m_BrushType==BrushTypeLinearGradient)
				((LinearGradientBrush *)m_Brush)->SetWrapMode(CapToset);
			else
			if (m_BrushType==BrushTypePathGradient)
				((PathGradientBrush *)m_Brush)->SetWrapMode((Gdiplus::WrapMode)CapToset);
			else
			if (m_BrushType==BrushTypeTextureFill)
				((TextureBrush *)m_Brush)->SetWrapMode((Gdiplus::WrapMode)CapToset);
		}
		break; 
	case 27: // TranslateTransform
		if (m_BrushType==BrushTypeLinearGradient || m_BrushType==BrushTypePathGradient || m_BrushType==BrushTypeTextureFill)
		{
			DWORD dwOrder=0;
			REAL rea1=0;
			REAL rea2=0;
			sscanf(pos,"%d,%g,%g",&dwOrder,&rea1,&rea2);
			if (m_BrushType==BrushTypeLinearGradient)
				((LinearGradientBrush *)m_Brush)->TranslateTransform(rea1,rea2,(Gdiplus::MatrixOrder)dwOrder);
			else
			if (m_BrushType==BrushTypePathGradient)
				((PathGradientBrush *)m_Brush)->TranslateTransform(rea1,rea2,(Gdiplus::MatrixOrder)dwOrder);
			else
			if (m_BrushType==BrushTypeTextureFill)
				((TextureBrush *)m_Brush)->TranslateTransform(rea1,rea2,(Gdiplus::MatrixOrder)dwOrder);
			if (oStr) DoMethod("GetTransform",oStr);
		}
		break; 
	case 28: // GetCenterColor
		if (oStr && m_BrushType==BrushTypePathGradient)
		{
			Color clr;
			retint=((PathGradientBrush *)m_Brush)->GetCenterColor(&clr);
			sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",clr.GetR(),clr.GetG(),clr.GetB(),clr.GetA());
		}
		break; 
	case 29: //GetCenterPoint 
		if (oStr && m_BrushType==BrushTypePathGradient)
		{
			Point po;
			retint=((PathGradientBrush *)m_Brush)->GetCenterPoint(&po);
			sprintf(oStr,"%d\x7F%d",po.X,po.Y);
		}
		break; 
	case 30: //GetCenterPointF 
		if (oStr && m_BrushType==BrushTypePathGradient)
		{
			PointF po;
			retint=((PathGradientBrush *)m_Brush)->GetCenterPoint(&po);
			sprintf(oStr,"%g\x7F%g",po.X,po.Y);
		}
		break; 
	case 31: // GetFocusScales
		if (oStr && m_BrushType==BrushTypePathGradient)
		{
			REAL xScale = 0.0f;
			REAL yScale = 0.0f;
			retint=((PathGradientBrush *)m_Brush)->GetFocusScales(&xScale, &yScale);
			sprintf(oStr,"%g\x7F%g",xScale,yScale);
		}
		break; 
	case 32: // GetPointCount
		if (m_BrushType==BrushTypePathGradient)
			retint=((PathGradientBrush *)m_Brush)->GetPointCount();
		break; 
	case 33: // GetSurroundColorCount
		if (m_BrushType==BrushTypePathGradient)
			retint=((PathGradientBrush *)m_Brush)->GetSurroundColorCount();
		break; 
	case 34: // GetSurroundColors
		if (oStr && m_BrushType==BrushTypePathGradient)
		{
			INT count=((PathGradientBrush *)m_Brush)->GetSurroundColorCount();
			Color *presetColors=new Color [count+10];
			if (((PathGradientBrush *)m_Brush)->GetSurroundColors(presetColors,&count)==0)
			{
				INT i;
				char *posout=oStr;
				for(i=0;i<count;i++)
				{
					if (i) *(posout++)=0x7F;
					*(posout)=0;
					posout+=sprintf(posout,"%d\x7%d\x7%d\x7%d",presetColors[i].GetR(),presetColors[i].GetG(),presetColors[i].GetB(),presetColors[i].GetA());
				}
			}
			delete []presetColors;
		}
		break; 
	case 35: // SetCenterPointF
		if (m_BrushType==BrushTypePathGradient)
		{
			PointF po;
			sscanf(pos,"%g,%g",&po.X,&po.Y);
			retint=((PathGradientBrush *)m_Brush)->SetCenterPoint(po);
		}
		break; 

	case 36: // SetCenterPoint
		if (m_BrushType==BrushTypePathGradient)
		{
			Point po;
			sscanf(pos,"%d,%d",&po.X,&po.Y);
			retint=((PathGradientBrush *)m_Brush)->SetCenterPoint(po);
		}
		break; 

	case 37: // SetFocusScales
		if (m_BrushType==BrushTypePathGradient)
		{
			REAL xScale = 0.0f;
			REAL yScale = 0.0f;
			sscanf(pos,"%g,%g",&xScale,&yScale);
			retint=((PathGradientBrush *)m_Brush)->SetFocusScales(xScale,yScale);
		}
		break; 

	case 38: // SetGraphicsPath
		if (m_BrushType==BrushTypePathGradient)
		{
			CODContext *ocontext=(*pos==0 && p_Context)?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ExtractField(pos,1,","));
			UINT nPath=atoi(ExtractField(pos,2,","));
			if (nPath < ocontext->m_nGraphPathArray && ocontext->m_GraphPathArr[nPath])
				((PathGradientBrush *)m_Brush)->SetGraphicsPath(ocontext->m_GraphPathArr[nPath]->m_GraphicsPath);
		}
		break; 

	case 39: // SetSurroundColors
		if (m_BrushType==BrushTypePathGradient)
		{
			INT nArr=1;
			const char *pos2=pos;
			while(*pos2) if (*(pos2++)==';') nArr++;
			if (nArr>1)
			{
				Color *arr1=new Color [nArr+10];
				pos2=pos;
				Color *arrPos1=arr1;
				while(*pos2)
				{
					arrPos1->SetValue(CODContext::GetColorFromString(p_Context, pos2));
					arrPos1++;
					while(*pos2 && *pos2!=';') pos2++;
					if (*pos2) pos2++;
				}

				if (((PathGradientBrush *)m_Brush)->SetSurroundColors(arr1,&nArr)==0) retint=nArr;
				delete [] arr1;
			}
		}
		break; 
	case 40: // GetColor
		if (m_BrushType==BrushTypeSolidColor)
		{
			Color clr;
			((SolidBrush *)m_Brush)->GetColor(&clr);
			sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",clr.GetR(),clr.GetG(),clr.GetB(),clr.GetA());
		}
		break; 
	case 41: // SetColor
		if (m_BrushType==BrushTypeSolidColor)
		{
			retint=((SolidBrush *)m_Brush)->SetColor(Color(CODContext::GetColorFromString(p_Context, pos)));
		}
		break; 
/*
//	case xxxx: // GetGraphicsPath
//		if (oStr && m_BrushType==BrushTypePathGradient)
//		{
//			retint=((PathGradientBrush *)m_Brush)->GetGraphicsPath();
//		}
//		break; 
	case 28: // 
		if (m_BrushType==BrushTypePathGradient)
		{
			retint=((PathGradientBrush *)m_Brush)->;
		}
		break; 
*/

//TextureBrush::GetImage The GetImage method gets a pointer to the Image object that is defined by this texture brush. 


	default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
	}
	if (oStr && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);

	return nfunc;
}



const Brush *CBrushPlus::SetBrush(Brush *pBrush)
{
	if (pBrush)
	{
		if (m_Brush) delete m_Brush;
		m_Brush=pBrush;
	}
	return m_Brush;
}