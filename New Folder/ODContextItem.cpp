// ODContext.cpp: implementation of the CODContextItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPUnit.h"
#include "ODContextItem.h"
#include "GP_TermDoc.h"
#include "GP_TermView.h"
#include "DlgViewSystemMethods.h"
#include <math.h>
#include <float.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


const char **CODContextItem::ccAFlagNames[]={
	CODContextItem::ccADriverStringOptions, 				CBitmapPlus::ccAUnit,		
	CGraphicsPathPlus::ccAFillMode,							CODContextItem::ccAFlushIntention,	
	CMatrixPlus::ccAMatrixOrder,							CODContextItem::ccACombineMode,
	CODContextItem::ccACompositingMode,						CODContextItem::ccACompositingQuality,
	CODContextItem::ccAInterpolationMode,					CODContextItem::ccAPixelOffsetMode,
	CODContextItem::ccASmoothingMode,						CODContextItem::ccATextRenderingHint,
	CODContextItem::ccACoordinateSpace,						CDlgViewSystemMethods::chMetricsNames,
	CDlgViewSystemMethods::chColorNames,					CODContextItem::ccACompareOperation,
	CODContextItem::ccAOperators,							CODContextItem::ccAMathFunction,
	CODContext::ccANamedColors,								CBrushPlus::ccAWrapMode,
	NULL,NULL,
};

const char *CODContextItem::ccAFlagTypes[]={
	"DriverStringOptions",									"Unit",
	"FillMode",												"FlushIntention",
	"MatrixOrder",											"CombineMode",
	"CompositingMode",										"CompositingQuality",
	"InterpolationMode",									"PixelOffsetMode",
	"SmoothingMode",										"TextRenderingHint",
	"CoordinateSpace",										"SystemMetrics",
	"SytemColors",											"CompareOperation",
	"Operators",											"MathFunction",
	"NamedColors",											"BrushWrapMode",
	"",							"",
};

const DCParamType CODContextItem::iAFlag[]={
	DCPTF_DRIVERSTRINGOPTIONS,								DCPTF_UNIT,
	DCPTF_FILLMODE,											DCPTF_FLUSHINTENTION,
	DCPTF_MATRIXORDER,										DCPTF_COMBINEMODE,
	DCPTF_COMPOSITINGMODE,									DCPTF_COMPOSITINGQUALITY,
	DCPTF_INTERPOLATIONMODE,								DCPTF_PIXELOFFSETMODE,
	DCPTF_SMOOTHINGMODE,									DCPTF_TEXTRENDERINGHINT,
	DCPTF_COORDINATESPACE,									DCPTF_SYTEMMETRICS,
	DCPTF_SYTEMCOLORS,										DCPTF_COMPAREOPERATIONS,
	DCPTF_OPERATORS,										DCPTF_MATH,
	DCPTF_NAMEDCOLORS,										DCPTF_BRUSHWRAPMODE,
	DCPT_NONE,
	DCPT_NONE,
};

const DWORD CODContextItem::iAFlagStyles[]={
	1,													0,
	0,													0,
	0,													0,
	0,													0,
	0,													0,
	0,													0,
	0,													0,
	0,													0,
	0,													0,
	0,													0,
	0,													0,
	0,
};

const DWORD *CODContextItem::iAFlagValues[]={
	(DWORD *)CODContextItem::iADriverStringOptions,			(DWORD *)CBitmapPlus::iAUnit,
	(DWORD *)CGraphicsPathPlus::iAFillMode,					(DWORD *)CODContextItem::ccAFlushIntention,
	(DWORD *)CMatrixPlus::iAMatrixOrder,					(DWORD *)CODContextItem::iACombineMode,
	(DWORD *)CODContextItem::iACompositingMode,				(DWORD *)CODContextItem::iACompositingQuality,
	(DWORD *)CODContextItem::iAInterpolationMode,			(DWORD *)CODContextItem::iAPixelOffsetMode,
	(DWORD *)CODContextItem::iASmoothingMode,				(DWORD *)CODContextItem::iATextRenderingHint,
	(DWORD *)CODContextItem::iACoordinateSpace,				(DWORD *)CDlgViewSystemMethods::uMetricsNames,
	(DWORD *)CDlgViewSystemMethods::uColorNames,			(DWORD *)CODContextItem::iACompareOperation,
	(DWORD *)CODContextItem::iAOperators,					(DWORD *)CODContextItem::iAMathFunction,
	(DWORD *)CODContext::iANamedColors,						(DWORD *)CBrushPlus::iAWrapMode,
	NULL,
	NULL,
};

/////////////////////////////////////////
/////////////////////////////////////////
/*
const char *CODContextItem::ccA[]={
	"","","","","",
};

const xxxxx CODContextItem::iA[]={
	,,,,
	(xxxxx)0,
};
*/

const char *CODContextItem::ccAMathFunction[]={
	"NONE","ABS","ACOS","ASIN","ATAN","ATAN2","BESSEL_j0","BESSEL_j1","BESSEL_jn","BESSEL_y0",
	"BESSEL_y1","BESSEL_yn","CABS","CEIL","CHGSIGN","CLEAR87","CLEARFP","CONTROL87","CONTROLFP","COPYSIGN",
	"COS","COSH","DIVQUOT","EXP","FABS","FINITE","FLOOR","FMOD","FPCLASS","FPRESET",
	"FREXPMANT","HYPOT","ISNAN","LABS","LDEXP","LDIVQUOT","LOG","LOG10","LOGB","LROTL",
	"LROTR","MAX","MIN","MODFFLOAT","NEXTAFTER","POW","RAND","ROTL","ROTR","SCALB",
	"SIN","SINH","SQRT","SRAND","STATUS87","STATUSFP","STRTOD","TAN","TANH",
	"DIVREM","FREXPEXP","LDIVREM","MODFINT","",
	"","","","","",
};

const DCMathFunction CODContextItem::iAMathFunction[]={
	DCMF_NONE,DCMF_ABS,DCMF_ACOS,DCMF_ASIN,DCMF_ATAN,DCMF_ATAN2,DCMF_BESSEL_j0,DCMF_BESSEL_j1,DCMF_BESSEL_jn,DCMF_BESSEL_y0,
	DCMF_BESSEL_y1,DCMF_BESSEL_yn,DCMF_CABS,DCMF_CEIL,DCMF_CHGSIGN,DCMF_CLEAR87,DCMF_CLEARFP,DCMF_CONTROL87,DCMF_CONTROLFP,DCMF_COPYSIGN,
	DCMF_COS,DCMF_COSH,DCMF_DIVQUOT,DCMF_EXP,DCMF_FABS,DCMF_FINITE,DCMF_FLOOR,DCMF_FMOD,DCMF_FPCLASS,DCMF_FPRESET,
	DCMF_FREXPMANT,DCMF_HYPOT,DCMF_ISNAN,DCMF_LABS,DCMF_LDEXP,DCMF_LDIVQUOT,DCMF_LOG,DCMF_LOG10,DCMF_LOGB,DCMF_LROTL,
	DCMF_LROTR,DCMF_MAX,DCMF_MIN,DCMF_MODFFLOAT,DCMF_NEXTAFTER,DCMF_POW,DCMF_RAND,DCMF_ROTL,DCMF_ROTR,DCMF_SCALB,
	DCMF_SIN,DCMF_SINH,DCMF_SQRT,DCMF_SRAND,DCMF_STATUS87,DCMF_STATUSFP,DCMF_STRTOD,DCMF_TAN,DCMF_TANH,
	DCMF_DIVREM,DCMF_FREXPEXP,DCMF_LDIVREM,DCMF_MODFINT,
	
	DCMF_NONE,
};


const char *CODContextItem::ccAOperators[]={
	"+","PLUS","-","MINUS","*","MUL",
	"/","DIV","|","OR","^","XOR",
	"&","AND",">>","RIGHT","<<","LEFT",
	"%","MOD","-/2","CENTER",
	"","","","",
};

const DCOperators CODContextItem::iAOperators[]={
	DCAO_PLUS,DCAO_PLUS,DCAO_MINUS,DCAO_MINUS,DCAO_MUL,DCAO_MUL,
	DCAO_DIV,DCAO_DIV,DCAO_OR,DCAO_OR,DCAO_XOR,DCAO_XOR,
	DCAO_AND,DCAO_AND,DCAO_TORIGHT,DCAO_TORIGHT,DCAO_TOLEFT,DCAO_TOLEFT,
	DCAO_MODULO,DCAO_MODULO,DCAO_CENTER,DCAO_CENTER,
	DCAO_PLUS,
};


const char *CODContextItem::ccACompareOperation[]={
	">","GT","<","LT","=","<>","NE","!=",
	">=","<=","GE","LE","!&","NOTAND","&","AND",

	"",
};

const DCCompareOperation CODContextItem::iACompareOperation[]={
	DCCO_GREATER,DCCO_GREATER,DCCO_LESS,DCCO_LESS,DCCO_EQUAL,DCCO_NOTEQUAL,DCCO_NOTEQUAL,DCCO_NOTEQUAL,
	DCCO_GREATEREQUAL,DCCO_LESSEQUAL,DCCO_GREATEREQUAL,DCCO_LESSEQUAL,DCCO_NOTAND,DCCO_NOTAND,DCCO_AND,DCCO_AND,
	DCCO_EQUAL,
};

const char *CODContextItem::ccACoordinateSpace[]={
	"World","Page","Device",
	"CoordinateSpaceWorld","CoordinateSpacePage","CoordinateSpaceDevice",
	"",
};

const CoordinateSpace CODContextItem::iACoordinateSpace[]={
	CoordinateSpaceWorld,CoordinateSpacePage,CoordinateSpaceDevice,
	CoordinateSpaceWorld,CoordinateSpacePage,CoordinateSpaceDevice,
	CoordinateSpaceWorld,
};



const char *CODContextItem::ccATextRenderingHint[]={
	"SystemDefault","SingleBitPerPixelGridFit","SingleBitPerPixel",
	"AntiAliasGridFit","AntiAlias","ClearTypeGridFit",
	"TextRenderingHintSystemDefault","TextRenderingHintSingleBitPerPixelGridFit","TextRenderingHintSingleBitPerPixel",
	"TextRenderingHintAntiAliasGridFit","TextRenderingHintAntiAlias","TextRenderingHintClearTypeGridFit",
	"",
};

const TextRenderingHint CODContextItem::iATextRenderingHint[]={
	TextRenderingHintSystemDefault,TextRenderingHintSingleBitPerPixelGridFit,TextRenderingHintSingleBitPerPixel,
	TextRenderingHintAntiAliasGridFit,TextRenderingHintAntiAlias,TextRenderingHintClearTypeGridFit,
	TextRenderingHintSystemDefault,TextRenderingHintSingleBitPerPixelGridFit,TextRenderingHintSingleBitPerPixel,
	TextRenderingHintAntiAliasGridFit,TextRenderingHintAntiAlias,TextRenderingHintClearTypeGridFit,
	TextRenderingHintSystemDefault,
};

const char *CODContextItem::ccASmoothingMode[]={
	"Invalid","Default","HighSpeed","HighQuality",
	"None","AntiAlias","AntiAlias8x4","AntiAlias8x8",
	"SmoothingModeInvalid","SmoothingModeDefault","SmoothingModeHighSpeed","SmoothingModeHighQuality",
	"SmoothingModeNone","SmoothingModeAntiAlias","SmoothingModeAntiAlias8x4","SmoothingModeAntiAlias8x8",
	"",""
	"",
};

const SmoothingMode CODContextItem::iASmoothingMode[]={
	SmoothingModeInvalid,SmoothingModeDefault,SmoothingModeHighSpeed,SmoothingModeHighQuality,
	SmoothingModeNone,SmoothingModeAntiAlias,SmoothingModeAntiAlias8x4,SmoothingModeAntiAlias8x8,
	SmoothingModeInvalid,SmoothingModeDefault,SmoothingModeHighSpeed,SmoothingModeHighQuality,
	SmoothingModeNone,SmoothingModeAntiAlias,SmoothingModeAntiAlias8x4,SmoothingModeAntiAlias8x8,
	SmoothingModeDefault,
	(SmoothingMode)0,
};


const char *CODContextItem::ccAPixelOffsetMode[]={
	"Invalid","Default","HighSpeed",
	"HighQuality","None","Half",
	"PixelOffsetModeInvalid","PixelOffsetModeDefault","PixelOffsetModeHighSpeed",
	"PixelOffsetModeHighQuality","PixelOffsetModeNone","PixelOffsetModeHalf",
	"",
};

const PixelOffsetMode CODContextItem::iAPixelOffsetMode[]={
	PixelOffsetModeInvalid,PixelOffsetModeDefault,PixelOffsetModeHighSpeed,
	PixelOffsetModeHighQuality,PixelOffsetModeNone,PixelOffsetModeHalf,
	PixelOffsetModeInvalid,PixelOffsetModeDefault,PixelOffsetModeHighSpeed,
	PixelOffsetModeHighQuality,PixelOffsetModeNone,PixelOffsetModeHalf,
	PixelOffsetModeDefault,
};

const char *CODContextItem::ccAInterpolationMode[]={
	"Invalid","Default","LowQuality","HighQuality",
	"Bilinear","Bicubic","NearestNeighbor",
	"HighQualityBilinear","HighQualityBicubic",
	"InterpolationModeInvalid","InterpolationModeDefault","InterpolationModeLowQuality","InterpolationModeHighQuality",
	"InterpolationModeBilinear","InterpolationModeBicubic","InterpolationModeNearestNeighbor",
	"InterpolationModeHighQualityBilinear","InterpolationModeHighQualityBicubic",
	"",
};

const InterpolationMode CODContextItem::iAInterpolationMode[]={
	InterpolationModeInvalid,InterpolationModeDefault,InterpolationModeLowQuality,InterpolationModeHighQuality,
	InterpolationModeBilinear,InterpolationModeBicubic,InterpolationModeNearestNeighbor,
	InterpolationModeHighQualityBilinear,InterpolationModeHighQualityBicubic,
	InterpolationModeInvalid,InterpolationModeDefault,InterpolationModeLowQuality,InterpolationModeHighQuality,
	InterpolationModeBilinear,InterpolationModeBicubic,InterpolationModeNearestNeighbor,
	InterpolationModeHighQualityBilinear,InterpolationModeHighQualityBicubic,
	InterpolationModeDefault,
	(InterpolationMode)0,
};
    

    


const char *CODContextItem::ccACompositingMode[]={
	"Over","Copy",
	"CompositingModeSourceOver","CompositingModeSourceCopy",
	"",
};

const CompositingMode CODContextItem::iACompositingMode[]={
	CompositingModeSourceOver,CompositingModeSourceCopy,
	CompositingModeSourceOver,CompositingModeSourceCopy,
	CompositingModeSourceOver,
};

const char *CODContextItem::ccACompositingQuality[]={
	"Invalid","Default","HighSpeed",
	"HighQuality","GammaCorrected","AssumeLinear",
	"CompositingQualityInvalid","CompositingQualityDefault","CompositingQualityHighSpeed",
	"CompositingQualityHighQuality","CompositingQualityGammaCorrected","CompositingQualityAssumeLinear",
	"",
};

const CompositingQuality CODContextItem::iACompositingQuality[]={
	CompositingQualityInvalid,CompositingQualityDefault,CompositingQualityHighSpeed,
	CompositingQualityHighQuality,CompositingQualityGammaCorrected,CompositingQualityAssumeLinear,
	CompositingQualityInvalid,CompositingQualityDefault,CompositingQualityHighSpeed,
	CompositingQualityHighQuality,CompositingQualityGammaCorrected,CompositingQualityAssumeLinear,
	CompositingQualityDefault,
};

const char *CODContextItem::ccACombineMode[]={
	"Replace","Intersect","Union","Xor","Exclude","Complement",
	"CombineModeReplace","CombineModeIntersect","CombineModeUnion","CombineModeXor","CombineModeExclude","CombineModeComplement",
	"","",
};

const CombineMode CODContextItem::iACombineMode[]={
	CombineModeReplace,CombineModeIntersect,CombineModeUnion,CombineModeXor,CombineModeExclude,CombineModeComplement,
	CombineModeReplace,CombineModeIntersect,CombineModeUnion,CombineModeXor,CombineModeExclude,CombineModeComplement,
	CombineModeReplace,
	(CombineMode)0,
};

const char *CODContextItem::ccADriverStringOptions[]={
	"CmapLookup","Vertical","RealizedAdvance","LimitSubpixel",
	"DriverStringOptionsCmapLookup","DriverStringOptionsVertical","DriverStringOptionsRealizedAdvance","DriverStringOptionsLimitSubpixel",
	"","",
};

const DriverStringOptions CODContextItem::iADriverStringOptions[]={
	DriverStringOptionsCmapLookup,DriverStringOptionsVertical,DriverStringOptionsRealizedAdvance,DriverStringOptionsLimitSubpixel,
	DriverStringOptionsCmapLookup,DriverStringOptionsVertical,DriverStringOptionsRealizedAdvance,DriverStringOptionsLimitSubpixel,
	(DriverStringOptions)0,
};

const char *CODContextItem::ccAFlushIntention[]={
	"Flush","Sync",
	"FlushIntentionFlush","FlushIntentionSync",
	"",
};

const FlushIntention CODContextItem::iAFlushIntention[]={
	FlushIntentionFlush,FlushIntentionSync,
	FlushIntentionFlush,FlushIntentionSync,
	FlushIntentionFlush,
	(FlushIntention)0,
};



////////////////////////////////////////
////////////////////////////////////////
const UINT CODContextItem::uNMethods=0;
const char *CODContextItem::cArrMethods[]={
/*00*/	"","","","","",
/*05*/	"","","","","",
	};


const char *CODContextItem::cArrMethodsParams[]={
/*00*/	"","","","","",
/*05*/	"","","","","",
	};




const UINT CODContextItem::uNUnitType=149;
const char *CODContextItem::cArrUnitType[]={
/*000*/		"NONE",					"BEGINCONTAINER",			"CLEAR",				"DRAWARC",				"DRAWBEZIER",
/*005*/		"DRAWBEZIERS",			"DRAWCLOSEDCURVE",			"DRAWCLOSEDCURVET",		"DRAWCURVE",			"DRAWCURVET",
/*010*/		"DRAWDRIVERSTRING",		"DRAWELLIPSE",				"DRAWIMAGE",			"DRAWIMAGE2",			"DRAWIMAGE3",
/*015*/		"DRAWIMAGE4",			"DRAWIMAGE5",				"DRAWIMAGE6",			"DRAWLINE",				"DRAWLINES",
/*020*/		"DRAWPATH",				"DRAWPIE",					"DRAWPOLYGON",			"DRAWRECTANGLE",		"DRAWRECTANGLES",
/*025*/		"DRAWSTRING",			"DRAWSTRING2",				"DRAWSTRING3",			"ENDCONTAINER",			"EXCLUDECLIPRECT",	
/*030*/		"EXCLUDECLIPREGION",	"FILLCLOSEDCURVE",			"FILLCLOSEDCURVE2",		"FILLELLIPSE",			"FILLPATH",
/*035*/		"FILLPIE",				"FILLPOLYGON",				"FILLPOLYGON2",			"FILLRECTANGLE",		"FILLRECTANGLES",
/*040*/		"FILLREGION",			"FLUSH",					"GETCLIP",				"GETCLIPBOUNDS",		"GETCOMPOSITINGMODE",
/*045*/		"GETCOMPOSITINGQUALITY","GETDPIX",					"GETDPIY",				"GETINTERPOLATIONMODE",	"GETLASTSTATUS",		
/*050*/		"GETNEARESTCOLOR",		"GETPAGESCALE",				"GETPAGEUNIT",			"GETPIXELOFFSETMODE",	"GETRENDERINGORIGIN",	
/*055*/		"GETSMOOTHINGMODE",		"GETTEXTCONTRAST",			"GETTEXTRENDERINGHINT",	"GETTRANSFORM",			"GETVISIBLECLIPBOUNDS",
/*060*/		"INTERSECTCLIPRECT",	"INTERSECTCLIPREGION",		"ISCLIPEMPTY",			"ISPOINTVISIBLE",		"ISRECTVISIBLE",
/*065*/		"ISVISIBLECLIPEMPTY",	"MULTIPLYTRANSFORM",		"RESETCLIP",			"RESETTRANSFORM",		"RESTORE",	
/*070*/		"ROTATETRANSFORM",		"SAVE",						"SCALETRANSFORM",		"SETCLIPBYRECT",		"SETCLIPBYREGION",
/*075*/		"SETCLIPBYPATH",		"SETCOMPOSITINGMODE",		"SETCOMPOSITINGQUALITY","SETINTERPOLATIONMODE",	"SETPAGESCALE",
/*080*/		"SETPAGEUNIT",			"SETPIXELOFFSETMODE",		"SETRENDERINGORIGIN",	"SETSMOOTHINGMODE",		"SETTEXTCONTRAST",
/*085*/		"SETTEXTRENDERINGHINT",	"SETTRANSFORM",				"TRANSFORMPOINTS",		"TRANSLATECLIP",		"TRANSLATETRANSFORM",	
/*090*/		"MEASUREDRIVERSTRING",	"MEASURESTRING",			"MEASURESTRING2",		"MEASURESTRING3",		"MEASURESTRING4",
/*095*/		"MEASURESTRING5",		"GETSYSTEMMETRICS",			"GETSYSTEMCOLORS",		"LABEL",				"GOTO",
/*100*/		"GOSUB",				"RETURN",					"IF",					"IFGOTO",				"IFGOSUB",
/*105*/		"ELSE",					"ENDIF",					"SET",					"ARITHMETIC",			"MATH",
/*110*/		"RECTCONTAINS",			"RECTEQUALS",				"RECTGETBOTTOM",		"RECTGETRIGHT",			"RECTGETLOCATION",	
/*115*/		"RECTGETSIZE",			"RECTINFLATE",				"RECTINTERSECT",		"RECTISEMPTYAREA",		"RECTOFFSET",
/*120*/		"RECTUNION",			"CLRGETALPHA",				"CLRSETALPHA",			"CLRGETRED",			"CLRSETRED",	
/*125*/		"CLRGETGREEN",			"CLRSETGREEN",				"CLRGETBLUE",			"CLRSETBLUE",			"GETWINDOWRECT",
/*130*/		"GETCLIENTRECT",		"SCRTOCL",					"CLTOSCR",				"MOVEWINDOW",			"STRMID",
/*135*/		"STRLEFT",				"STRRIGHT",					"STRFORMAT",			"OBJSUB",				"OBJFN",						
/*140*/		"CONTEXTSUB",			"CONTEXTFN",				"SYSTEMSUB",			"SYSTEMFN",				"GETFIELD",
/*145*/		"SETFIELD",				"SETMATRIXELEMENT",			"GETMATRIXELEMENT",		"TRANSFORMBRUSH",		"",
/*150*/		"",	"",	"",	"",	"",
/*155*/		"",	"",	"",	"",	"",
/*160*/		"",	"",	"",	"",	"",
/*165*/		"",	"",	"",	"",	"",
/*170*/		"",	"",	"",	"",	"",
/*175*/		"",	"",	"",	"",	"",
/*180*/		"",	"",	"",	"",	"",
/*185*/		"",	"",	"",	"",	"",
/*190*/		"",	"",	"",	"",	"",
/*195*/		"",	"",	"",	"",	"",
	};
	

const DCUnitType CODContextItem::uArrUnitType[]={
/*000*/		DCUT_NONE,					DCUT_BEGINCONTAINER,			DCUT_CLEAR,					DCUT_DRAWARC,				DCUT_DRAWBEZIER,
/*005*/		DCUT_DRAWBEZIERS,			DCUT_DRAWCLOSEDCURVE,			DCUT_DRAWCLOSEDCURVET,		DCUT_DRAWCURVE,				DCUT_DRAWCURVET,
/*010*/		DCUT_DRAWDRIVERSTRING,		DCUT_DRAWELLIPSE,				DCUT_DRAWIMAGE,				DCUT_DRAWIMAGE2,			DCUT_DRAWIMAGE3,
/*015*/		DCUT_DRAWIMAGE4,			DCUT_DRAWIMAGE5,				DCUT_DRAWIMAGE6,			DCUT_DRAWLINE,				DCUT_DRAWLINES,
/*020*/		DCUT_DRAWPATH,				DCUT_DRAWPIE,					DCUT_DRAWPOLYGON,			DCUT_DRAWRECTANGLE,			DCUT_DRAWRECTANGLES,
/*025*/		DCUT_DRAWSTRING,			DCUT_DRAWSTRING2,				DCUT_DRAWSTRING3,			DCUT_ENDCONTAINER,			DCUT_EXCLUDECLIPRECT,	
/*030*/		DCUT_EXCLUDECLIPREGION,		DCUT_FILLCLOSEDCURVE,			DCUT_FILLCLOSEDCURVE2,		DCUT_FILLELLIPSE,			DCUT_FILLPATH,
/*035*/		DCUT_FILLPIE,				DCUT_FILLPOLYGON,				DCUT_FILLPOLYGON2,			DCUT_FILLRECTANGLE,			DCUT_FILLRECTANGLES,
/*040*/		DCUT_FILLREGION,			DCUT_FLUSH,						DCUT_GETCLIP,				DCUT_GETCLIPBOUNDS,			DCUT_GETCOMPOSITINGMODE,
/*045*/		DCUT_GETCOMPOSITINGQUALITY,	DCUT_GETDPIX,					DCUT_GETDPIY,				DCUT_GETINTERPOLATIONMODE,	DCUT_GETLASTSTATUS,		
/*050*/		DCUT_GETNEARESTCOLOR,		DCUT_GETPAGESCALE,				DCUT_GETPAGEUNIT,			DCUT_GETPIXELOFFSETMODE,	DCUT_GETRENDERINGORIGIN,
/*055*/		DCUT_GETSMOOTHINGMODE,		DCUT_GETTEXTCONTRAST,			DCUT_GETTEXTRENDERINGHINT,	DCUT_GETTRANSFORM,			DCUT_GETVISIBLECLIPBOUNDS,
/*060*/		DCUT_INTERSECTCLIPRECT,		DCUT_INTERSECTCLIPREGION,		DCUT_ISCLIPEMPTY,			DCUT_ISPOINTVISIBLE,		DCUT_ISRECTVISIBLE,
/*065*/		DCUT_ISVISIBLECLIPEMPTY,	DCUT_MULTIPLYTRANSFORM,			DCUT_RESETCLIP,				DCUT_RESETTRANSFORM,		DCUT_RESTORE,	
/*070*/		DCUT_ROTATETRANSFORM,		DCUT_SAVE,						DCUT_SCALETRANSFORM,		DCUT_SETCLIPBYRECT,			DCUT_SETCLIPBYREGION,
/*075*/		DCUT_SETCLIPBYPATH,			DCUT_SETCOMPOSITINGMODE,		DCUT_SETCOMPOSITINGQUALITY,	DCUT_SETINTERPOLATIONMODE,	DCUT_SETPAGESCALE,
/*080*/		DCUT_SETPAGEUNIT,			DCUT_SETPIXELOFFSETMODE,		DCUT_SETRENDERINGORIGIN,	DCUT_SETSMOOTHINGMODE,		DCUT_SETTEXTCONTRAST,
/*085*/		DCUT_SETTEXTRENDERINGHINT,	DCUT_SETTRANSFORM,				DCUT_TRANSFORMPOINTS,		DCUT_TRANSLATECLIP,			DCUT_TRANSLATETRANSFORM,
/*090*/		DCUT_MEASUREDRIVERSTRING,	DCUT_MEASURESTRING,				DCUT_MEASURESTRING2,		DCUT_MEASURESTRING3,		DCUT_MEASURESTRING4,
/*095*/		DCUT_MEASURESTRING5,		DCUT_GETSYSTEMMETRICS,			DCUT_GETSYSTEMCOLORS,		DCUT_LABEL,					DCUT_GOTO,
/*100*/		DCUT_GOSUB,					DCUT_RETURN,					DCUT_IF,					DCUT_IFGOTO,				DCUT_IFGOSUB,
/*105*/		DCUT_ELSE,					DCUT_ENDIF,						DCUT_SET,					DCUT_ARITHMETIC,			DCUT_MATH,
/*110*/		DCUT_RECTCONTAINS,			DCUT_RECTEQUALS,				DCUT_RECTGETBOTTOM,			DCUT_RECTGETRIGHT,			DCUT_RECTGETLOCATION,	
/*115*/		DCUT_RECTGETSIZE,			DCUT_RECTINFLATE,				DCUT_RECTINTERSECT,			DCUT_RECTISEMPTYAREA,		DCUT_RECTOFFSET,
/*120*/		DCUT_RECTUNION,				DCUT_CLRGETALPHA,				DCUT_CLRSETALPHA,			DCUT_CLRGETRED,				DCUT_CLRSETRED,	
/*125*/		DCUT_CLRGETGREEN,			DCUT_CLRSETGREEN,				DCUT_CLRGETBLUE,			DCUT_CLRSETBLUE,			DCUT_GETWINDOWRECT,
/*130*/		DCUT_GETCLIENTRECT,			DCUT_SCRTOCL,					DCUT_CLTOSCR,				DCUT_MOVEWINDOW,			DCUT_STRMID,
/*135*/		DCUT_STRLEFT,				DCUT_STRRIGHT,					DCUT_STRFORMAT,				DCUT_OBJSUB,				DCUT_OBJFN,
/*140*/		DCUT_CONTEXTSUB,			DCUT_CONTEXTFN,					DCUT_SYSTEMSUB,				DCUT_SYSTEMFN,				DCUT_GETFIELD,
/*145*/		DCUT_SETFIELD,				DCUT_SETMATRIXELEMENT,			DCUT_GETMATRIXELEMENT,		DCUT_TRANSFORMBRUSH,	DCUT_NONE,
/*150*/		DCUT_NONE,	DCUT_NONE,	DCUT_NONE,	DCUT_NONE,	DCUT_NONE,
/*155*/		DCUT_NONE,	DCUT_NONE,	DCUT_NONE,	DCUT_NONE,	DCUT_NONE,
/*160*/		DCUT_NONE,	DCUT_NONE,	DCUT_NONE,	DCUT_NONE,	DCUT_NONE,
/*165*/		DCUT_NONE,	DCUT_NONE,	DCUT_NONE,	DCUT_NONE,	DCUT_NONE,
/*170*/		DCUT_NONE,	DCUT_NONE,	DCUT_NONE,	DCUT_NONE,	DCUT_NONE,
/*175*/		DCUT_NONE,	DCUT_NONE,	DCUT_NONE,	DCUT_NONE,	DCUT_NONE,
/*180*/		DCUT_NONE,	DCUT_NONE,	DCUT_NONE,	DCUT_NONE,	DCUT_NONE,
/*185*/		DCUT_NONE,	DCUT_NONE,	DCUT_NONE,	DCUT_NONE,	DCUT_NONE,
/*190*/		DCUT_NONE,	DCUT_NONE,	DCUT_NONE,	DCUT_NONE,	DCUT_NONE,
/*195*/		DCUT_NONE,	DCUT_NONE,	DCUT_NONE,	DCUT_NONE,	DCUT_NONE,

	};

#define DU_NSTACK		50

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CODContextItem::CODContextItem(CODContext *ipContext)
{
	pContext=ipContext;
	m_Type=DCUT_NONE;
	m_Action=DCUA_NONE;
	m_NParams=0;
//	m_InitString="";
	m_Parameters=NULL;
	::ZeroMemory(&m_Result,sizeof(DCIRESULT));
	m_Result.dwParamType=DCPT_NONE;
}

CODContextItem::~CODContextItem()
{
	ResetItem();
}

void CODContextItem::ResetItem()
{
	CODContextItem::ResetParameters(&m_Parameters,&m_NParams);
	m_Type=DCUT_NONE;
	m_Action=DCUA_NONE;
	ResetResult();
}

DWORD CODContextItem::CompileVarSubtypeNames(const char *ccName)
{
	const char *cvartypes[]={
		"CPLACEY",		"CPLACEX",		"SCRHEIGHT",		"SCRWIDTH",		"SCRCY",
		"SCRCX",		"SCRSCALEYX",	"SCRCLIENTRECT",	"SCRWNDRECT",	"MOUSEPOINTW",
		"MOUSEPOINTS",	"MOUSEPOINTC",	"",	"",	"",
		"",	"",	"",	"",	"",
	};
	const DWORD dwvartypes[]={
		DCPTF_ST_CPLACEY,		DCPTF_ST_CPLACEX,		DCPTF_ST_SCRHEIGHT,		DCPTF_ST_SCRWIDTH,		DCPTF_ST_SCRCY,
		DCPTF_ST_SCRCX,			DCPTF_ST_SCRSCALEYX,	DCPTF_ST_SCRCLIENTRECT,	DCPTF_ST_SCRWNDRECT,	DCPTF_ST_MOUSEPOINTW,
		DCPTF_ST_MOUSEPOINTS,	DCPTF_ST_MOUSEPOINTC,	DCPTF_SUBTYPEUSUAL,		DCPTF_SUBTYPEUSUAL,		DCPTF_SUBTYPEUSUAL,
		DCPTF_SUBTYPEUSUAL,		DCPTF_SUBTYPEUSUAL,		DCPTF_SUBTYPEUSUAL,		DCPTF_SUBTYPEUSUAL,		DCPTF_SUBTYPEUSUAL,
	};

	char tmps[150];
	strncpy(tmps,ccName,145);
	tmps[50]=0;
	char *posbr=strchr(tmps,')');
	if (posbr) *posbr=0;
	else
	{
		posbr=strchr(tmps,'(');
		if (posbr) *posbr=0;
	}
	
	int nvt;
	for(nvt=0;*cvartypes[nvt] && _stricmp(tmps,cvartypes[nvt])!=0;nvt++);

	return dwvartypes[nvt];
}

CODContextItem *CODContextItem::SetItem(CODContext *ipContect, const char * iStr)
{
	DCUnitType ItemType=DCUT_NONE;
	const char * pStr=FindField(iStr,2,",");
	if (iStr && *iStr)
	{
		char tmpC[100];
		strncpy(tmpC,iStr,99);
		tmpC[99]=0;
		char *pos=strchr(tmpC,',');
		if (pos) *pos=0;
		UINT i;
		_strupr(tmpC);
		for(i=0;*CODContextItem::cArrUnitType[i] && strcmp(CODContextItem::cArrUnitType[i],tmpC)!=0;i++);
		ItemType=CODContextItem::uArrUnitType[i];
	}
	return SetItem(ipContect, ItemType, pStr);
}

CODContextItem *CODContextItem::SetItem(CODContext *ipContect, DCUnitType iItemType, const char * iStr)
{
	CODContextItem *ret=new CODContextItem(ipContect);
	ret->m_Type=iItemType;
	if (!iStr) iStr="";
	const char *pos2=iStr;
	int tmpcnt=0;

	switch(iItemType)
	{
	case DCUT_BEGINCONTAINER://DestInteger[,dstrect,srcrect,unit]
		if (*pos2)
		{
			DCParamType pta[]={DCPT_DESTINTEGER,DCPT_RECT,DCPT_RECT,(DCParamType)(DCPT_FLAG|DCPTF_UNIT),DCPT_NONE};
			CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		else CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		break;
	case DCUT_ENDCONTAINER://conteinerId
		if (*pos2)
		{
			DCParamType pta[]={DCPT_INTEGER,DCPT_NONE};
			CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		else CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		break;
	case DCUT_CLEAR://Color
		{
			DCParamType pta[]={DCPT_COLOR,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("CLR(NUM(0),NUM(0),NUM(0),NUM(0)",NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_DRAWARC://Pen,Rect,startAngle,sweepAngle
	case DCUT_DRAWPIE://Pen,Rect,startAngle,sweepAngle
		{
			DCParamType pta[]={DCPT_PEN,DCPT_RECT,DCPT_REAL,DCPT_REAL,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("PEN(0),RECT(IDX(0)),REAL(0),REAL(0)",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_DRAWBEZIER://Pen,Point1,Point2,Point3,Point4
		{
			DCParamType pta[]={DCPT_PEN,DCPT_POINT,DCPT_POINT,DCPT_POINT,DCPT_POINT,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("PEN(0),POINT(IDX(0)),POINT(IDX(1)),POINT(IDX(2)),POINT(IDX(3))",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_DRAWBEZIERS://Pen,ARRAYxxx
	case DCUT_DRAWCLOSEDCURVE://Pen,ARRAYxxx
	case DCUT_DRAWCURVE://Pen,ARRAYxxx
	case DCUT_DRAWLINES://Pen,ARRAYxxx
	case DCUT_DRAWPOLYGON://Pen,ARRAYxxx
		{
			DCParamType pta[]={DCPT_PEN,DCPT_ARRAY,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_DRAWRECTANGLES://Pen,ARRAYxxx
		{
			DCParamType pta[]={DCPT_PEN,DCPT_ARRAY,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_FILLRECTANGLES://Brush,ARRAYxxx
		{
			DCParamType pta[]={DCPT_BRUSH,DCPT_ARRAY,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_DRAWCLOSEDCURVET://Pen,ARRAYxxx,tension
	case DCUT_DRAWCURVET://Pen,ARRAYxxx,tension
		{
			DCParamType pta[]={DCPT_PEN,DCPT_ARRAY,DCPT_REAL,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_DRAWDRIVERSTRING://Font,Brush,Matrix,Point,flags,text
		{
			DCParamType pta[]={DCPT_FONT,DCPT_BRUSH,DCPT_MATRIX,DCPT_POINT,(DCParamType)(DCPTF_DRIVERSTRINGOPTIONS|DCPT_FLAG),DCPT_STRING,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_DRAWELLIPSE://Pen,Rect
	case DCUT_DRAWRECTANGLE://Pen,Rect
		{
			DCParamType pta[]={DCPT_PEN,DCPT_RECT,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("PEN(0),RECT(IDX(0))",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_DRAWIMAGE://Image,Point
		{
			DCParamType pta[]={DCPT_IMAGE,DCPT_POINT,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("BITMAP(0),POINT(IDX(0))",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_DRAWIMAGE2://Image,Point1,Point2,Point3
		{
			DCParamType pta[]={DCPT_IMAGE,DCPT_POINT,DCPT_POINT,DCPT_POINT,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("BITMAP(0),POINT(IDX(0)),POINT(IDX(1)),POINT(IDX(2))",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_DRAWIMAGE3://Image,Rect
		{
			DCParamType pta[]={DCPT_IMAGE,DCPT_RECT,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("BITMAP(0),RECT(IDX(0))",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_DRAWIMAGE4://Image,Point,Rect,UnitType
		{
			DCParamType pta[]={DCPT_IMAGE,DCPT_POINT,DCPT_RECT,(DCParamType)(DCPTF_UNIT|DCPT_FLAG),DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("BITMAP(0),POINT(IDX(0)),RECT(IDX(0)),0",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_DRAWIMAGE5://Image,Point1,Point2,Point3,Rect,UnitType
		{
			DCParamType pta[]={DCPT_IMAGE,DCPT_POINT,DCPT_POINT,DCPT_POINT,DCPT_RECT,(DCParamType)(DCPTF_UNIT|DCPT_FLAG),DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("BITMAP(0),POINT(IDX(0)),POINT(IDX(1)),POINT(IDX(2)),RECT(IDX(0)),0",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_DRAWIMAGE6://Image,Rect,Rect,UnitType
		{
			DCParamType pta[]={DCPT_IMAGE,DCPT_RECT,DCPT_RECT,(DCParamType)(DCPTF_UNIT|DCPT_FLAG),DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("BITMAP(0),POINT(RECT(0)),RECT(IDX(0)),0",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_DRAWLINE://Pen,Point1,Point2
		{
			DCParamType pta[]={DCPT_PEN,DCPT_POINT,DCPT_POINT,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("PEN(0),POINT(IDX(0)),POINT(IDX(1))",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_DRAWPATH://Pen,Path
		{
			DCParamType pta[]={DCPT_PEN,DCPT_PATH,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_DRAWSTRING://Font,Brush,Point,text
		{
			DCParamType pta[]={DCPT_FONT,DCPT_BRUSH,DCPT_POINT,DCPT_STRING,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_DRAWSTRING2://Font,Brush,Point,Format,text
		{
			DCParamType pta[]={DCPT_FONT,DCPT_BRUSH,DCPT_POINT,DCPT_SFORMAT,DCPT_STRING,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_DRAWSTRING3://Font,Brush,Rect,Format,text
		{
			DCParamType pta[]={DCPT_FONT,DCPT_BRUSH,DCPT_RECT,DCPT_SFORMAT,DCPT_STRING,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_EXCLUDECLIPRECT://Rect
	case DCUT_INTERSECTCLIPRECT://Rect
		{
			DCParamType pta[]={DCPT_RECT,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("RECT(IDX(0))",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_EXCLUDECLIPREGION://Region
	case DCUT_INTERSECTCLIPREGION://Region
		{
			DCParamType pta[]={DCPT_REGION,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("REGION(IDX(0))",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_FILLCLOSEDCURVE://Brush,ARRAYxxx
		{
			DCParamType pta[]={DCPT_BRUSH,DCPT_ARRAY,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_FILLCLOSEDCURVE2://Brush,ARRAYxxx,FillMode,tension
		{
			DCParamType pta[]={DCPT_BRUSH,DCPT_ARRAY,(DCParamType)(DCPTF_FILLMODE|DCPT_FLAG),DCPT_REAL,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_FILLELLIPSE://Brush,Rect
	case DCUT_FILLRECTANGLE://Brush,Rect
		{
			DCParamType pta[]={DCPT_BRUSH,DCPT_RECT,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("BRUSH(0),RECT(IDX(0))",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_FILLPATH://Brush,Path
		{
			DCParamType pta[]={DCPT_BRUSH,DCPT_PATH,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("BRUSH(0),PATH(IDX(0))",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_FILLPIE://Brush,Rect,startAngle,sweepAngle
		{
			DCParamType pta[]={DCPT_BRUSH,DCPT_RECT,DCPT_REAL,DCPT_REAL,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("BRUSH(0),RECT(IDX(0)),REAL(0),REAL(0)",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_FILLPOLYGON://Brush,ARRAYxxx
		{
			DCParamType pta[]={DCPT_BRUSH,DCPT_ARRAY,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_FILLPOLYGON2://Brush,ARRAYxxx,FillMode
		{
			DCParamType pta[]={DCPT_BRUSH,DCPT_ARRAY,(DCParamType)(DCPTF_FILLMODE|DCPT_FLAG),DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_FILLREGION://Brush,Region
		{
			DCParamType pta[]={DCPT_BRUSH,DCPT_REGION,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("BRUSH(0),REGION(IDX(0))",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_FLUSH://FlushIntention
		{
			DCParamType pta[]={(DCParamType)(DCPTF_FLUSHINTENTION|DCPT_FLAG),DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_GETCLIP://DestRegion
		{
			DCParamType pta[]={DCPT_REGION,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("REGION(IDX(0))",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_GETCLIPBOUNDS://DestRect
	case DCUT_GETVISIBLECLIPBOUNDS://DestRect
		{
			DCParamType pta[]={DCPT_DESTRECT,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("RECT(IDX(0))",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break; 
	case DCUT_GETCOMPOSITINGMODE://DestInteger
	case DCUT_GETCOMPOSITINGQUALITY://DestInteger
	case DCUT_GETINTERPOLATIONMODE://DestInteger
	case DCUT_GETLASTSTATUS://DestInteger
	case DCUT_GETPAGEUNIT://DestInteger
	case DCUT_GETPIXELOFFSETMODE://DestInteger
	case DCUT_GETSMOOTHINGMODE://DestInteger
	case DCUT_GETTEXTCONTRAST://DestInteger
	case DCUT_GETTEXTRENDERINGHINT://DestInteger
	case DCUT_ISCLIPEMPTY://DestInteger
	case DCUT_ISVISIBLECLIPEMPTY://DestInteger
	case DCUT_SAVE://DestInteger
		{
			DCParamType pta[]={DCPT_DESTINTEGER,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("INT(IDX(0))",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break; 
	case DCUT_SETTEXTCONTRAST://Contrast
		{
			DCParamType pta[]={DCPT_INTEGER,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("INT(IDX(0))",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break; 
	case DCUT_GETDPIX://DestReal
	case DCUT_GETDPIY://DestReal
	case DCUT_GETPAGESCALE://DestReal
		{
			DCParamType pta[]={DCPT_DESTREAL,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("REAL(IDX(0))",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break; 
	case DCUT_GETNEARESTCOLOR://Color
		{
			DCParamType pta[]={DCPT_DESTCOLOR,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("CLR(IDX(0))",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_GETRENDERINGORIGIN://DestIntegerX,DestIntegerY
		{
			DCParamType pta[]={DCPT_DESTINTEGER,DCPT_DESTINTEGER,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("INT(IDX(0)),INT(IDX(1))",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_GETTRANSFORM://DestMatrix
		{
			DCParamType pta[]={DCPT_DESTMATRIX,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("DESTMATRIX(IDX(0))",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_ISPOINTVISIBLE://DestInteger,Point
		{
			DCParamType pta[]={DCPT_DESTINTEGER,DCPT_POINT,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("INT(IDX(0)),POINT(IDX(1))",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_ISRECTVISIBLE://DestInteger,Rect
		{
			DCParamType pta[]={DCPT_DESTINTEGER,DCPT_RECT,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("INT(IDX(0)),RECT(IDX(1))",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_MULTIPLYTRANSFORM://Matrix,MatrixOrder
		{
			DCParamType pta[]={DCPT_DESTMATRIX,(DCParamType)(DCPTF_MATRIXORDER|DCPT_FLAG),DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("MATRIX(IDX(0)),0",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_RESETCLIP://
	case DCUT_RESETTRANSFORM://
		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		break;
	case DCUT_RESTORE://unit
		if (*pos2)
		{
			DCParamType pta[]={DCPT_INTEGER,DCPT_NONE};
			CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_ROTATETRANSFORM://Angle,MatrixOrder
		{
			DCParamType pta[]={DCPT_REAL,(DCParamType)(DCPTF_MATRIXORDER|DCPT_FLAG),DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("REAL(0),0",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_SCALETRANSFORM://sx,sy,MatrixOrder
		{
			DCParamType pta[]={DCPT_REAL,DCPT_REAL,(DCParamType)(DCPTF_MATRIXORDER|DCPT_FLAG),DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("REAL(0),0",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_SETCLIPBYRECT://Rect,CombineMode
		{
			DCParamType pta[]={DCPT_RECT,(DCParamType)(DCPTF_COMBINEMODE|DCPT_FLAG),DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("RECT(IDX(0)),0",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_SETCLIPBYREGION://Region,CombineMode
		{
			DCParamType pta[]={DCPT_REGION,(DCParamType)(DCPTF_COMBINEMODE|DCPT_FLAG),DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("REGION(IDX(0)),0",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_SETCLIPBYPATH://Path,CombineMode
		{
			DCParamType pta[]={DCPT_PATH,(DCParamType)(DCPTF_COMBINEMODE|DCPT_FLAG),DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("PATH(IDX(0)),0",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_SETCOMPOSITINGMODE://CompositingMode
		{
			DCParamType pta[]={(DCParamType)(DCPTF_COMPOSITINGMODE|DCPT_FLAG),DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("0",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_SETCOMPOSITINGQUALITY://CompositingQuality
		{
			DCParamType pta[]={(DCParamType)(DCPTF_COMPOSITINGQUALITY|DCPT_FLAG),DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("0",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_SETINTERPOLATIONMODE://InterpolationMode
		{
			DCParamType pta[]={(DCParamType)(DCPTF_INTERPOLATIONMODE|DCPT_FLAG),DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("0",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_SETPAGESCALE://Scale
		{
			DCParamType pta[]={DCPT_REAL,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("REAL(0)",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_SETPAGEUNIT://UnitType
		{
			DCParamType pta[]={(DCParamType)(DCPTF_UNIT|DCPT_FLAG),DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("0",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_SETPIXELOFFSETMODE://PixelOffsetMode
		{
			DCParamType pta[]={(DCParamType)(DCPTF_PIXELOFFSETMODE|DCPT_FLAG),DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("0",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_SETRENDERINGORIGIN://intX,intY
		if (*pos2)
		{
			DCParamType pta[]={DCPT_INTEGER,DCPT_INTEGER,DCPT_NONE};
			CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_SETSMOOTHINGMODE://SmoothingMode
		{
			DCParamType pta[]={(DCParamType)(DCPTF_SMOOTHINGMODE|DCPT_FLAG),DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("0",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_SETTEXTRENDERINGHINT://TextRenderingHint
		{
			DCParamType pta[]={(DCParamType)(DCPTF_TEXTRENDERINGHINT|DCPT_FLAG),DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("0",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_SETTRANSFORM://Matrix
		{
			DCParamType pta[]={DCPT_MATRIX,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("MATRIX(IDX(0))",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_TRANSFORMPOINTS://destSpace,srcSpace,ARRAYxxx
		{
			DCParamType pta[]={(DCParamType)(DCPTF_COORDINATESPACE|DCPT_FLAG),(DCParamType)(DCPTF_COORDINATESPACE|DCPT_FLAG),DCPT_ARRAY,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_TRANSLATECLIP://dX,dY
		{
			DCParamType pta[]={DCPT_REAL,DCPT_REAL,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("REAL(0),REAL(0)",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_TRANSLATETRANSFORM://dx,dy,MatrixOrder
		{
			DCParamType pta[]={DCPT_REAL,DCPT_REAL,(DCParamType)(DCPTF_MATRIXORDER|DCPT_FLAG),DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams("REAL(0),REAL(0),0",pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_MEASUREDRIVERSTRING://Font,Matrix,Point,flags,boundingBox,text
		{
			DCParamType pta[]={DCPT_FONT,DCPT_MATRIX,DCPT_POINT,(DCParamType)(DCPTF_DRIVERSTRINGOPTIONS|DCPT_FLAG),
				DCPT_DESTRECT,DCPT_STRING,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_MEASURESTRING://Font,SrcRect,DstRect,text
		{
			DCParamType pta[]={DCPT_FONT,DCPT_RECT,DCPT_DESTRECT,DCPT_STRING,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_MEASURESTRING2://Font,Point,DstRect,text
		{
			DCParamType pta[]={DCPT_FONT,DCPT_POINT,DCPT_DESTRECT,DCPT_STRING,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_MEASURESTRING3://Font,SrcRect,DstRect,StringFormat,text
		{
			DCParamType pta[]={DCPT_FONT,DCPT_RECT,DCPT_DESTRECT,DCPT_SFORMAT,DCPT_STRING,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_MEASURESTRING4://Font,Point,DstRect,StringFormat,text
		{
			DCParamType pta[]={DCPT_FONT,DCPT_POINT,DCPT_DESTRECT,DCPT_SFORMAT,DCPT_STRING,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_MEASURESTRING5://Font,SrcRect,DstRect,StringFormat,codepointsFitted,linesFilled,text
		{
			DCParamType pta[]={DCPT_FONT,DCPT_RECT,DCPT_DESTRECT,DCPT_SFORMAT,DCPT_DESTINTEGER,DCPT_DESTINTEGER,DCPT_STRING,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_GETSYSTEMMETRICS://DestInt,MetricType
		{
			DCParamType pta[]={DCPT_DESTVARTYPE,(DCParamType)(DCPTF_SYTEMMETRICS|DCPT_FLAG),DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_GETSYSTEMCOLORS://DestColor,ColorType
		{
			DCParamType pta[]={DCPT_DESTVARTYPE,(DCParamType)(DCPTF_SYTEMCOLORS|DCPT_FLAG),DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_LABEL://LAbelName
	case DCUT_GOTO://LAbelName
	case DCUT_GOSUB://LAbelName
		{
			DCParamType pta[]={DCPT_STRING,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_IF://LeftOp,Operation,RightOp[,LogOp,LeftOp,Operation,RightOp[,LogOp,LeftOp,Operation,RightOp[,LogOp,LeftOp,Operation,RightOp]]]
		{
			DCParamType pta[]={
				DCPT_VARTYPE,(DCParamType)(DCPTF_COMPAREOPERATIONS|DCPT_FLAG),DCPT_VARTYPE,
				(DCParamType)(DCPTF_OPERATORS|DCPT_FLAG),
				DCPT_VARTYPE,(DCParamType)(DCPTF_COMPAREOPERATIONS|DCPT_FLAG),DCPT_VARTYPE,
				(DCParamType)(DCPTF_OPERATORS|DCPT_FLAG),
				DCPT_VARTYPE,(DCParamType)(DCPTF_COMPAREOPERATIONS|DCPT_FLAG),DCPT_VARTYPE,
				(DCParamType)(DCPTF_OPERATORS|DCPT_FLAG),
				DCPT_VARTYPE,(DCParamType)(DCPTF_COMPAREOPERATIONS|DCPT_FLAG),DCPT_VARTYPE,
				DCPT_NONE};
			if (*pos2)
			{
				UINT i;
				CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
				for(i=0;i<ret->m_NParams && ret->m_Parameters[i].dwParamType!=DCPT_NONE;i++);
				ret->m_NParams=i;
			}
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;

	case DCUT_IFGOTO://LeftOp,Operation,RightOp,Label
	case DCUT_IFGOSUB://LeftOp,Operation,RightOp,Label
		{
			DCParamType pta[]={DCPT_VARTYPE,(DCParamType)(DCPTF_COMPAREOPERATIONS|DCPT_FLAG),DCPT_VARTYPE,DCPT_STRING,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_SET://LeftOp,RightOp
		{
			DCParamType pta[]={DCPT_DESTVARTYPE,DCPT_VARTYPE,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_ARITHMETIC://LeftOp,RightArg1,Operator,RightArg2
		{
			DCParamType pta[]={DCPT_DESTVARTYPE,DCPT_VARTYPE,(DCParamType)(DCPTF_OPERATORS|DCPT_FLAG),DCPT_VARTYPE,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_MATH://LeftOp,MathFunction,Operand1[,Operand2[,Operand3[,Operand4]]]
		{
			DCParamType pta[]={DCPT_DESTVARTYPE,(DCParamType)(DCPTF_MATH|DCPT_FLAG),DCPT_VARTYPE,DCPT_VARTYPE,DCPT_VARTYPE,DCPT_VARTYPE,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_RECTCONTAINS:	//DestInt,Rect,Rect|Point
		{
			DCParamType pta[]={DCPT_DESTINTEGER,DCPT_RECT,DCPT_VARTYPE,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_RECTEQUALS:	//DestInt,Rect,Rect
		{
			DCParamType pta[]={DCPT_DESTINTEGER,DCPT_RECT,DCPT_RECT,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_RECTGETBOTTOM:	//DestReal,Rect
	case DCUT_RECTGETRIGHT:	//DestReal,Rect
		{
			DCParamType pta[]={DCPT_DESTREAL,DCPT_RECT,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_RECTGETLOCATION:	//DestPoint,Rect
	case DCUT_RECTGETSIZE:	//DestPoint,Rect
		{
			DCParamType pta[]={DCPT_DESTPOINT,DCPT_RECT,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_RECTINFLATE:	//Rect,Point
	case DCUT_RECTOFFSET:	//Rect,Point
		{
			DCParamType pta[]={DCPT_DESTRECT,DCPT_POINT,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_RECTINTERSECT:	//DestRect,Rect
	case DCUT_RECTUNION:	//DestRect,Rect
		{
			DCParamType pta[]={DCPT_DESTRECT,DCPT_RECT,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_RECTISEMPTYAREA:	//DestInt,Rect
		{
			DCParamType pta[]={DCPT_DESTINTEGER,DCPT_RECT,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_CLRGETALPHA:	//DestInt,Color
	case DCUT_CLRGETRED:	//DestInt,Color
	case DCUT_CLRGETGREEN:	//DestInt,Color
	case DCUT_CLRGETBLUE:	//DestInt,Color
		{
			DCParamType pta[]={DCPT_DESTINTEGER,DCPT_COLOR,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_CLRSETALPHA:	//DestColor,Int
	case DCUT_CLRSETRED:	//DestColor,Int
	case DCUT_CLRSETGREEN:	//DestColor,Int
	case DCUT_CLRSETBLUE:	//DestColor,Int
		{
			DCParamType pta[]={DCPT_DESTCOLOR,DCPT_INTEGER,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_GETWINDOWRECT:	//DestRect,GUIObject
	case DCUT_GETCLIENTRECT:	//DestRect,GUIObject
		{
			DCParamType pta[]={DCPT_DESTRECT,DCPT_GUIOBJECT,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_SCRTOCL:	//DestRect|DestPoint,Rect|Point,GUIObject
	case DCUT_CLTOSCR:	//DestRect|DestPoint,Rect|Point,GUIObject
		{
			DCParamType pta[]={DCPT_DESTVARTYPE,DCPT_RECT,DCPT_GUIOBJECT,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_MOVEWINDOW: //GUIObject,Rect
		{
			DCParamType pta[]={DCPT_GUIOBJECT,DCPT_RECT,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_STRMID: //DestString,String,IntStart,IntLen
		{
			DCParamType pta[]={DCPT_DESTSTRING,DCPT_STRING,DCPT_INTEGER,DCPT_INTEGER,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_STRLEFT: //DestString,String,IntLen
	case DCUT_STRRIGHT: //DestString,String,IntLen
		{
			DCParamType pta[]={DCPT_DESTSTRING,DCPT_STRING,DCPT_INTEGER,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_STRFORMAT: //DestString,StrFormat,Variable
		{
			DCParamType pta[]={DCPT_DESTSTRING,DCPT_STRING,DCPT_VARTYPE,DCPT_VARTYPE,DCPT_VARTYPE,DCPT_VARTYPE,DCPT_VARTYPE,DCPT_VARTYPE,DCPT_VARTYPE,DCPT_VARTYPE,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_OBJSUB:	//GUIObject,Method
		{
			DCParamType pta[]={DCPT_GUIOBJECT,DCPT_STRING,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_OBJFN:	//DestString,GUIObject,Method
		{
			DCParamType pta[]={DCPT_DESTSTRING,DCPT_GUIOBJECT,DCPT_STRING,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;

	case DCUT_CONTEXTSUB:	//ContextName,Method
		{
			DCParamType pta[]={DCPT_STRING,DCPT_STRING,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_CONTEXTFN:	//DestString,ContextName,Method
		{
			DCParamType pta[]={DCPT_DESTSTRING,DCPT_STRING,DCPT_STRING,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_SYSTEMSUB:	//Method
		{
			DCParamType pta[]={DCPT_STRING,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_SYSTEMFN:	//DestString,Method
		{
			DCParamType pta[]={DCPT_DESTSTRING,DCPT_STRING,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_GETFIELD:	//DestString,SrcString,nField,Delimiter
		{
			DCParamType pta[]={DCPT_DESTSTRING,DCPT_STRING,DCPT_INTEGER,DCPT_VARTYPE,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_SETFIELD:	//DestString,Value,nField,Delimiter
		{
			DCParamType pta[]={DCPT_DESTSTRING,DCPT_VARTYPE,DCPT_INTEGER,DCPT_VARTYPE,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_SETMATRIXELEMENT:	//DestMatrix,nElement,Value
		{
			DCParamType pta[]={DCPT_DESTMATRIX,DCPT_INTEGER,DCPT_VARTYPE,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_GETMATRIXELEMENT:	//DestValue,nMatrix,nElement
		{
			DCParamType pta[]={DCPT_DESTVARTYPE,DCPT_MATRIX,DCPT_INTEGER,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;
	case DCUT_TRANSFORMBRUSH:	//Brush,nMatrix
		{
			DCParamType pta[]={DCPT_BRUSH,DCPT_MATRIX,DCPT_NONE};
			if (*pos2)	CODContextItem::TranslateParams(pos2,pta,ipContect,&ret->m_Parameters,&ret->m_NParams);
			else		CODContextItem::TranslateParams(NULL,NULL,ipContect,&ret->m_Parameters,&ret->m_NParams);
		}
		break;





	case DCUT_ELSE:
	case DCUT_ENDIF:
	case DCUT_RETURN:
	case DCUT_NONE:
	default:
		break;
	}
	return ret;
}

DCUnitAction CODContextItem::DoAction(Graphics *pGraphics)
{
	if (m_NParams>0) PrepareParameters();
	m_Action=DCUA_NONE;

	if (pGraphics)
		switch(m_Type)
		{
		case DCUT_BEGINCONTAINER://DestInteger[,dstrect,srcrect,unit]
			if (m_NParams==4 && m_Parameters)
				m_Result.m_dword=*(m_Parameters[0].m_pDestDword)=(DWORD)pGraphics->BeginContainer(
					*(m_Parameters[1].m_pRectF),
					*(m_Parameters[2].m_pRectF),
					(Gdiplus::Unit)m_Parameters[3].m_dword);
			else
			if (m_NParams==1 && m_Parameters)
				m_Result.m_dword=*(m_Parameters[0].m_pDestDword)=(DWORD)pGraphics->BeginContainer();
			else	m_Result.m_dword=(DWORD)pGraphics->BeginContainer();
			break;
		case DCUT_ENDCONTAINER://ConteinerId
			if (m_NParams==1 && m_Parameters)
				m_Result.m_dword=(DWORD)pGraphics->EndContainer((Gdiplus::GraphicsContainer)m_Parameters[0].m_dword);
			break;
		case DCUT_CLEAR://Color
			m_Result.m_dword=(DWORD)pGraphics->Clear(*(m_Parameters[0].m_pColor));
			break;
		case DCUT_DRAWARC:////Pen,Rect,startAngle,sweepAngle
			if (m_NParams==4 && m_Parameters && m_Parameters[0].m_pPen)
				m_Result.m_dword=(DWORD)pGraphics->DrawArc(
					m_Parameters[0].m_pPen->m_Pen,
					*(m_Parameters[1].m_pRectF),
					m_Parameters[2].m_real,
					m_Parameters[3].m_real);
			break;
		case DCUT_DRAWPIE:////Pen,Rect,startAngle,sweepAngle
			if (m_NParams==4 && m_Parameters && m_Parameters[0].m_pPen)
				m_Result.m_dword=(DWORD)pGraphics->DrawPie(
					m_Parameters[0].m_pPen->m_Pen,
					*(m_Parameters[1].m_pRectF),
					m_Parameters[2].m_real,
					m_Parameters[3].m_real);
			break;
		case DCUT_DRAWBEZIER://Pen,Point1,Point2,Point3,Point4
			if (m_NParams==5 && m_Parameters && m_Parameters[0].m_pPen)
				m_Result.m_dword=(DWORD)pGraphics->DrawBezier(
					m_Parameters[0].m_pPen->m_Pen,
					*(m_Parameters[1].m_pPointF),
					*(m_Parameters[2].m_pPointF),
					*(m_Parameters[3].m_pPointF),
					*(m_Parameters[4].m_pPointF));
			break;
		case DCUT_DRAWBEZIERS://Pen,ARRAYxxx
		case DCUT_DRAWCLOSEDCURVE://Pen,ARRAYxxx
		case DCUT_DRAWCLOSEDCURVET://Pen,ARRAYxxx,tension
		case DCUT_DRAWCURVE://Pen,ARRAYxxx
		case DCUT_DRAWCURVET://Pen,ARRAYxxx,tension
		case DCUT_DRAWLINES://Pen,ARRAYxxx
		case DCUT_DRAWPOLYGON://Pen,ARRAYxxx
		case DCUT_FILLCLOSEDCURVE://Brush,ARRAYxxx
		case DCUT_FILLCLOSEDCURVE2://Brush,ARRAYxxx,tension,FillMode
		case DCUT_FILLPOLYGON://Brush,ARRAYxxx
		case DCUT_FILLPOLYGON2://Brush,ARRAYxxx,FillMode
			if (m_NParams>=2 && m_Parameters && m_Parameters[0].m_pPen && m_Parameters[1].m_dwArray)
			{
				PointF *tmpPA=NULL;
				PointF *tmpA=NULL;
				switch(m_Parameters[1].dwParamType)
				{
				case DCPT_ARRAY|DCPT_POINT:
					tmpPA=m_Parameters[1].m_pPointF;		break;
				case DCPT_ARRAYIDX:
				case DCPT_ARRAYREF:
					{
						tmpPA=tmpA=new PointF [m_Parameters[1].dwNElements];
						UINT i;
						for(i=0;i<m_Parameters[1].dwNElements;i++)
						{
							UINT ref=m_Parameters[1].m_dwArray[i];
							if ((m_Parameters[1].dwParamType&DCPT_ARRAYREF)==DCPT_ARRAYREF && ref<pContext->m_nIntArray)
								ref=pContext->m_IntArr[ref];
							if (ref<pContext->m_nPointArray) tmpA[i]=pContext->m_PointArr[ref];
						}
					}
					break;
				}
				switch(m_Type)
				{
				case DCUT_DRAWBEZIERS://Pen,ARRAYxxx
					m_Result.m_dword=(DWORD)pGraphics->DrawBeziers(
						m_Parameters[0].m_pPen->m_Pen,
						tmpPA,
						m_Parameters[1].dwNElements);
					break;
				case DCUT_DRAWCLOSEDCURVE://Pen,ARRAYxxx
					m_Result.m_dword=(DWORD)pGraphics->DrawClosedCurve(
						m_Parameters[0].m_pPen->m_Pen,
						tmpPA,
						m_Parameters[1].dwNElements);
					break;
				case DCUT_DRAWCLOSEDCURVET://Pen,ARRAYxxx,tension
					m_Result.m_dword=(DWORD)pGraphics->DrawClosedCurve(
						m_Parameters[0].m_pPen->m_Pen,
						tmpPA,
						m_Parameters[1].dwNElements,
						m_Parameters[2].m_real);
					break;
				case DCUT_DRAWCURVE://Pen,ARRAYxxx
					m_Result.m_dword=(DWORD)pGraphics->DrawCurve(
						m_Parameters[0].m_pPen->m_Pen,
						tmpPA,
						m_Parameters[1].dwNElements);
					break;
				case DCUT_DRAWCURVET://Pen,ARRAYxxx,tension
					m_Result.m_dword=(DWORD)pGraphics->DrawCurve(
						m_Parameters[0].m_pPen->m_Pen,
						tmpPA,
						m_Parameters[1].dwNElements,
						m_Parameters[2].m_real);
					break;
				case DCUT_DRAWLINES://Pen,ARRAYxxx
					m_Result.m_dword=(DWORD)pGraphics->DrawLines(
						m_Parameters[0].m_pPen->m_Pen,
						tmpPA,
						m_Parameters[1].dwNElements);
					break;
				case DCUT_DRAWPOLYGON://Pen,ARRAYxxx
					m_Result.m_dword=(DWORD)pGraphics->DrawPolygon(
						m_Parameters[0].m_pPen->m_Pen,
						tmpPA,
						m_Parameters[1].dwNElements);
					break;
				case DCUT_FILLCLOSEDCURVE://Brush,ARRAYxxx
					m_Result.m_dword=(DWORD)pGraphics->FillClosedCurve(
						m_Parameters[0].m_pBrush->m_Brush,
						tmpPA,
						m_Parameters[1].dwNElements);
					break;
				case DCUT_FILLCLOSEDCURVE2://Brush,ARRAYxxx,FillMode,tension
					m_Result.m_dword=(DWORD)pGraphics->FillClosedCurve(
						m_Parameters[0].m_pBrush->m_Brush,
						tmpPA,
						m_Parameters[1].dwNElements,
						(Gdiplus::FillMode)m_Parameters[2].m_dword,
						m_Parameters[3].m_real);
					break;
				case DCUT_FILLPOLYGON://Brush,ARRAYxxx
					m_Result.m_dword=(DWORD)pGraphics->FillPolygon(
						m_Parameters[0].m_pBrush->m_Brush,
						tmpPA,
						m_Parameters[1].dwNElements);
					break;
				case DCUT_FILLPOLYGON2://Brush,ARRAYxxx,FillMode
					m_Result.m_dword=(DWORD)pGraphics->FillPolygon(
						m_Parameters[0].m_pBrush->m_Brush,
						tmpPA,
						m_Parameters[1].dwNElements,
						(Gdiplus::FillMode)m_Parameters[2].m_dword);
					break;
				}
				if (tmpA) delete []tmpA;
			}
			break;
		case DCUT_DRAWRECTANGLES://Pen,ARRAYxxx
		case DCUT_FILLRECTANGLES://Brush,ARRAYxxx
			if (m_NParams>=2 && m_Parameters && m_Parameters[0].m_pPen && m_Parameters[1].m_dwArray)
			{
				RectF *tmpPA=NULL;
				RectF *tmpA=NULL;
				switch(m_Parameters[1].dwParamType)
				{
				case DCPT_ARRAY|DCPT_RECT:
					tmpPA=m_Parameters[1].m_pRectF;		break;
				case DCPT_ARRAYIDX:
				case DCPT_ARRAYREF:
					{
						tmpPA=tmpA=new RectF [m_Parameters[1].dwNElements];
						UINT i;
						for(i=0;i<m_Parameters[1].dwNElements;i++)
						{
							UINT ref=m_Parameters[1].m_dwArray[i];
							if ((m_Parameters[1].dwParamType&DCPT_ARRAYREF)==DCPT_ARRAYREF && ref<pContext->m_nIntArray)
								ref=pContext->m_IntArr[ref];
							if (ref<pContext->m_nRectArray) tmpA[i]=pContext->m_RectArr[ref];
						}
					}
					break;
				}
				switch(m_Type)
				{
				case DCUT_DRAWRECTANGLES://Pen,ARRAYxxx
					m_Result.m_dword=(DWORD)pGraphics->DrawRectangles(
						m_Parameters[0].m_pPen->m_Pen,
						tmpPA,
						m_Parameters[1].dwNElements);
					break;
				case DCUT_FILLRECTANGLES://Brush,ARRAYxxx
					m_Result.m_dword=(DWORD)pGraphics->FillRectangles(
						m_Parameters[0].m_pBrush->m_Brush,
						tmpPA,
						m_Parameters[1].dwNElements);
					break;
				}
				if (tmpA) delete []tmpA;
			}
			break;
		case DCUT_DRAWDRIVERSTRING://Font,Brush,Matrix,Point,flags,text
			if (m_NParams==6 && m_Parameters && m_Parameters[0].m_pFont && m_Parameters[1].m_pBrush && m_Parameters[2].m_pMatrix)
			{
				UINT tLen=m_Parameters[5].m_pCString->GetLength();

				UINT16 *tmpWText2=new UINT16 [tLen*2+10];
				MultiByteToWideChar(CP_ACP, 0,*m_Parameters[5].m_pCString , -1, (LPWSTR)tmpWText2, tLen*2);

				m_Result.m_dword=(DWORD)pGraphics->DrawDriverString(
					tmpWText2,
					tLen,
					m_Parameters[0].m_pFont->m_Font,
					m_Parameters[1].m_pBrush->m_Brush,
					m_Parameters[3].m_pPointF,
					m_Parameters[4].m_dword,
					m_Parameters[2].m_pMatrix->m_Matrix);
				delete []tmpWText2;
			}
			break;
		case DCUT_DRAWELLIPSE://Pen,Rect
			if (m_NParams==2 && m_Parameters && m_Parameters[0].m_pPen)
				m_Result.m_dword=(DWORD)pGraphics->DrawEllipse(
					m_Parameters[0].m_pPen->m_Pen,
					*(m_Parameters[1].m_pRectF));
			break;
		case DCUT_DRAWRECTANGLE://Pen,Rect
			if (m_NParams==2 && m_Parameters && m_Parameters[0].m_pPen)
				m_Result.m_dword=(DWORD)pGraphics->DrawRectangle(
					m_Parameters[0].m_pPen->m_Pen,
					*(m_Parameters[1].m_pRectF));
			break;
		case DCUT_DRAWIMAGE://Image,Point
			if (m_NParams==2 && m_Parameters && m_Parameters[0].m_pBitmap)
				m_Result.m_dword=(DWORD)pGraphics->DrawImage(
					m_Parameters[0].m_pBitmap->m_Bitmap,
					*(m_Parameters[1].m_pPointF));
			break;
		case DCUT_DRAWIMAGE2://Image,Point1,Point2,Point3
			if (m_NParams==4 && m_Parameters && m_Parameters[0].m_pBitmap && m_Parameters[1].m_pPointF && m_Parameters[2].m_pPointF && m_Parameters[3].m_pPointF)
			{
				PointF mpp[3];
				mpp[0]=*(m_Parameters[1].m_pPointF);
				mpp[1]=*(m_Parameters[2].m_pPointF);
				mpp[2]=*(m_Parameters[3].m_pPointF);
				m_Result.m_dword=(DWORD)pGraphics->DrawImage(
					m_Parameters[0].m_pBitmap->m_Bitmap,
					mpp,3);
			}
			break;
		case DCUT_DRAWIMAGE3://Image,Rect
			if (m_NParams==2 && m_Parameters && m_Parameters[0].m_pBitmap)
				m_Result.m_dword=(DWORD)pGraphics->DrawImage(
					m_Parameters[0].m_pBitmap->m_Bitmap,
					*(m_Parameters[1].m_pRectF));
			break;
		case DCUT_DRAWIMAGE4://Image,Point,Rect,UnitType
			if (m_NParams==4 && m_Parameters && m_Parameters[0].m_pBitmap)
				m_Result.m_dword=(DWORD)pGraphics->DrawImage(
					m_Parameters[0].m_pBitmap->m_Bitmap,
					m_Parameters[1].m_pPointF->X,
					m_Parameters[1].m_pPointF->Y,
					m_Parameters[2].m_pRectF->X,
					m_Parameters[2].m_pRectF->Y,
					m_Parameters[2].m_pRectF->Width,
					m_Parameters[2].m_pRectF->Height,
					(Gdiplus::Unit)m_Parameters[3].m_dword);
			break;
		case DCUT_DRAWIMAGE5://Image,Point1,Point2,Point3,Rect,UnitType
			if (m_NParams==6 && m_Parameters && m_Parameters[0].m_pBitmap)
			{
				PointF mpp[3];
				mpp[0]=*(m_Parameters[1].m_pPointF);
				mpp[1]=*(m_Parameters[2].m_pPointF);
				mpp[2]=*(m_Parameters[3].m_pPointF);
				m_Result.m_dword=(DWORD)pGraphics->DrawImage(
					m_Parameters[0].m_pBitmap->m_Bitmap,
					mpp,3,
					m_Parameters[4].m_pRectF->X,
					m_Parameters[4].m_pRectF->Y,
					m_Parameters[4].m_pRectF->Width,
					m_Parameters[4].m_pRectF->Height,
					(Gdiplus::Unit)m_Parameters[5].m_dword);
			}
			break;
		case DCUT_DRAWIMAGE6://Image,Rect,Rect,UnitType
			if (m_NParams==4 && m_Parameters && m_Parameters[0].m_pBitmap)
				m_Result.m_dword=(DWORD)pGraphics->DrawImage(
					m_Parameters[0].m_pBitmap->m_Bitmap,
					*(m_Parameters[1].m_pRectF),
					m_Parameters[2].m_pRectF->X,
					m_Parameters[2].m_pRectF->Y,
					m_Parameters[2].m_pRectF->Width,
					m_Parameters[2].m_pRectF->Height,
					(Gdiplus::Unit)m_Parameters[3].m_dword);
			break;
		case DCUT_DRAWLINE://Pen,Point1,Point2
			if (m_NParams==3 && m_Parameters && m_Parameters[0].m_pPen)
				m_Result.m_dword=(DWORD)pGraphics->DrawLine(
					m_Parameters[0].m_pPen->m_Pen,
					*(m_Parameters[1].m_pPointF),
					*(m_Parameters[2].m_pPointF));
			break;
		case DCUT_DRAWPATH:////Pen,Path
			if (m_NParams==2 && m_Parameters && m_Parameters[0].m_pPen && m_Parameters[1].m_pPath)
				m_Result.m_dword=(DWORD)pGraphics->DrawPath(
					m_Parameters[0].m_pPen->m_Pen,
					m_Parameters[1].m_pPath->m_GraphicsPath);
			break;
		case DCUT_DRAWSTRING://Font,Brush,Point,text
			if (m_NParams==4 && m_Parameters && m_Parameters[0].m_pFont && m_Parameters[1].m_pBrush)
			{
				UINT tLen=m_Parameters[3].m_pCString->GetLength();

				WCHAR *tmpWText2=new WCHAR [tLen*2+10];
				MultiByteToWideChar(CP_ACP, 0,*m_Parameters[3].m_pCString , -1, tmpWText2, tLen*2);
				
				m_Result.m_dword=(DWORD)pGraphics->DrawString(
					tmpWText2,
					tLen,
					m_Parameters[0].m_pFont->m_Font,
					*(m_Parameters[2].m_pPointF),
					m_Parameters[1].m_pBrush->m_Brush);
				delete []tmpWText2;
			}
			break;
		case DCUT_DRAWSTRING2://Font,Brush,Point,Format,text
			if (m_NParams==5 && m_Parameters && m_Parameters[0].m_pFont && m_Parameters[1].m_pBrush)
			{
				UINT tLen=m_Parameters[4].m_pCString->GetLength();

				WCHAR *tmpWText2=new WCHAR [tLen*2+10];
				MultiByteToWideChar(CP_ACP, 0,*m_Parameters[4].m_pCString , -1, tmpWText2, tLen*2);

				m_Result.m_dword=(DWORD)pGraphics->DrawString(
					tmpWText2,
					tLen,
					m_Parameters[0].m_pFont->m_Font,
					*(m_Parameters[2].m_pPointF),
					m_Parameters[3].m_pStrFormat->m_StringFormat,
					m_Parameters[1].m_pBrush->m_Brush);
				delete []tmpWText2;
			}
			break;
		case DCUT_DRAWSTRING3://Font,Brush,Rect,Format,text
			if (m_NParams==5 && m_Parameters && m_Parameters[0].m_pFont && m_Parameters[1].m_pBrush)
			{
				UINT tLen=m_Parameters[4].m_pCString->GetLength();

				WCHAR *tmpWText2=new WCHAR [tLen*2+10];
				MultiByteToWideChar(CP_ACP, 0,*m_Parameters[4].m_pCString , -1, tmpWText2, tLen*2);

				if (m_Parameters[3].m_pStrFormat && m_Parameters[3].m_pStrFormat->m_StringFormat)
				{
					m_Result.m_dword=(DWORD)pGraphics->DrawString(
						tmpWText2,
						tLen,
						m_Parameters[0].m_pFont->m_Font,
						*(m_Parameters[2].m_pRectF),
						m_Parameters[3].m_pStrFormat->m_StringFormat,
						m_Parameters[1].m_pBrush->m_Brush);
				}
				else
				{
					PointF pof(m_Parameters[2].m_pRectF->X,m_Parameters[2].m_pRectF->Y);
					UINT tLen=m_Parameters[4].m_pCString->GetLength();
					m_Result.m_dword=(DWORD)pGraphics->DrawString(
						tmpWText2,
						tLen,
						m_Parameters[0].m_pFont->m_Font,
						pof,
						m_Parameters[1].m_pBrush->m_Brush);
				}
				delete []tmpWText2;
			}
			break;
		case DCUT_EXCLUDECLIPRECT:////Rect
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pRectF)
				m_Result.m_dword=(DWORD)pGraphics->ExcludeClip(
					*(m_Parameters[0].m_pRectF));
			break;
		case DCUT_EXCLUDECLIPREGION:////Region
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pRegion)
				m_Result.m_dword=(DWORD)pGraphics->ExcludeClip(
					m_Parameters[0].m_pRegion->m_Rgn);
			break;
		case DCUT_INTERSECTCLIPRECT:////Rect
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pRectF)
				m_Result.m_dword=(DWORD)pGraphics->IntersectClip(
					*(m_Parameters[0].m_pRectF));
			break;
		case DCUT_INTERSECTCLIPREGION:////Region
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pRegion)
				m_Result.m_dword=(DWORD)pGraphics->IntersectClip(
					m_Parameters[0].m_pRegion->m_Rgn);
			break;
		case DCUT_FILLELLIPSE:////Brush,Rect
			if (m_NParams==2 && m_Parameters && m_Parameters[0].m_pBrush)
				m_Result.m_dword=(DWORD)pGraphics->FillEllipse(
					m_Parameters[0].m_pBrush->m_Brush,
					*(m_Parameters[1].m_pRectF));
			break;
		case DCUT_FILLRECTANGLE:////Brush,Rect
			if (m_NParams==2 && m_Parameters && m_Parameters[0].m_pBrush)
				m_Result.m_dword=(DWORD)pGraphics->FillRectangle(
					m_Parameters[0].m_pBrush->m_Brush,
					*(m_Parameters[1].m_pRectF));
			break;
		case DCUT_FILLPATH:////Brush,Path
			if (m_NParams==2 && m_Parameters && m_Parameters[0].m_pBrush && m_Parameters[1].m_pPath)
				m_Result.m_dword=(DWORD)pGraphics->FillPath(
					m_Parameters[0].m_pBrush->m_Brush,
					m_Parameters[1].m_pPath->m_GraphicsPath);
			break;
		case DCUT_FILLPIE:////Brush,Rect,startAngle,sweepAngle
			if (m_NParams==4 && m_Parameters && m_Parameters[0].m_pBrush)
				m_Result.m_dword=(DWORD)pGraphics->FillPie(
					m_Parameters[0].m_pBrush->m_Brush,
					*(m_Parameters[1].m_pRectF),
					m_Parameters[2].m_real,
					m_Parameters[3].m_real);
			break;
		case DCUT_FILLREGION:////Brush,Region
			if (m_NParams==2 && m_Parameters && m_Parameters[0].m_pBrush && m_Parameters[1].m_pRegion)
				m_Result.m_dword=(DWORD)pGraphics->FillRegion(
					m_Parameters[0].m_pBrush->m_Brush,
					m_Parameters[1].m_pRegion->m_Rgn);
			break;
		case DCUT_FLUSH://FlushIntention
			if (m_Parameters)
				m_Result.m_dword=0;
				pGraphics->Flush((FlushIntention)(m_Parameters[0].m_dword));
			break;
		case DCUT_GETCLIP://DestRegion
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pRegion)
				m_Result.m_dword=(DWORD)pGraphics->GetClip(m_Parameters[0].m_pRegion->m_Rgn);
			break;
		case DCUT_GETCLIPBOUNDS://DestRect
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pDestRectF)
				m_Result.m_dword=(DWORD)pGraphics->GetClipBounds(m_Parameters[0].m_pDestRectF);
			break;
		case DCUT_GETCOMPOSITINGMODE://DestInteger
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pDestDword)
				m_Result.m_dword=*(m_Parameters[0].m_pDestDword)=(DWORD)pGraphics->GetCompositingMode();
			else	m_Result.m_dword=(DWORD)pGraphics->GetCompositingMode();
			break;
		case DCUT_GETCOMPOSITINGQUALITY://DestInteger
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pDestDword)
				m_Result.m_dword=*(m_Parameters[0].m_pDestDword)=(DWORD)pGraphics->GetCompositingQuality();
			else	m_Result.m_dword=(DWORD)pGraphics->GetCompositingQuality();
			break;
		case DCUT_GETDPIX://DestReal
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pDestDword)
				m_Result.m_real=*(m_Parameters[0].m_pDestReal)=pGraphics->GetDpiX();
			break;
		case DCUT_GETDPIY://DestReal
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pDestDword)
				m_Result.m_real=*(m_Parameters[0].m_pDestReal)=pGraphics->GetDpiY();
			break;
		case DCUT_GETINTERPOLATIONMODE://DestInteger
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pDestDword)
				m_Result.m_dword=*(m_Parameters[0].m_pDestDword)=(DWORD)pGraphics->GetInterpolationMode();
			else	m_Result.m_dword=(DWORD)pGraphics->GetInterpolationMode();
			break;
		case DCUT_GETLASTSTATUS://DestInteger
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pDestDword)
				m_Result.m_dword=*(m_Parameters[0].m_pDestDword)=(DWORD)pGraphics->GetLastStatus();
			else	m_Result.m_dword=(DWORD)pGraphics->GetLastStatus();
			break;
		case DCUT_GETNEARESTCOLOR://Color
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pDestColor)
				m_Result.m_dword=(DWORD)pGraphics->GetNearestColor(m_Parameters[0].m_pDestColor);
			break;
		case DCUT_GETPAGESCALE://DestReal
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pDestDword)
				m_Result.m_real=*(m_Parameters[0].m_pDestReal)=pGraphics->GetPageScale();
			break;
		case DCUT_GETPAGEUNIT://DestInteger
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pDestDword)
				m_Result.m_dword=*(m_Parameters[0].m_pDestDword)=(DWORD)pGraphics->GetPageUnit();
			else	m_Result.m_dword=(DWORD)pGraphics->GetPageUnit();
			break;
		case DCUT_GETPIXELOFFSETMODE://DestInteger
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pDestDword)
				m_Result.m_dword=*(m_Parameters[0].m_pDestDword)=(DWORD)pGraphics->GetPixelOffsetMode();
			else	m_Result.m_dword=(DWORD)pGraphics->GetPixelOffsetMode();
			break;
		case DCUT_GETRENDERINGORIGIN://DestIntegerX,DestIntegerY
			if (m_NParams==2 && m_Parameters && m_Parameters[0].m_pDestDword && m_Parameters && m_Parameters[1].m_pDestDword)
				m_Result.m_dword=(DWORD)pGraphics->GetRenderingOrigin(m_Parameters[0].m_pDestInt,m_Parameters[1].m_pDestInt);
			break;
		case DCUT_GETSMOOTHINGMODE://DestInteger
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pDestDword)
				m_Result.m_dword=*(m_Parameters[0].m_pDestDword)=(DWORD)pGraphics->GetSmoothingMode();
			else	m_Result.m_dword=(DWORD)pGraphics->GetSmoothingMode();
			break;
		case DCUT_GETTEXTCONTRAST://DestInteger
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pDestDword)
				m_Result.m_dword=*(m_Parameters[0].m_pDestDword)=(DWORD)pGraphics->GetTextContrast();
			else	m_Result.m_dword=(DWORD)pGraphics->GetTextContrast();
			break;
		case DCUT_GETTEXTRENDERINGHINT://DestInteger
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pDestDword)
				m_Result.m_dword=*(m_Parameters[0].m_pDestDword)=(DWORD)pGraphics->GetTextRenderingHint();
			else	m_Result.m_dword=(DWORD)pGraphics->GetTextRenderingHint();
			break;
		case DCUT_GETTRANSFORM://DestMatrix
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pDestMatrix)
				m_Result.m_dword=(DWORD)pGraphics->GetTransform(m_Parameters[0].m_pDestMatrix->m_Matrix);
			break;
		case DCUT_GETVISIBLECLIPBOUNDS://DestRect
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pDestRectF)
				m_Result.m_dword=(DWORD)pGraphics->GetVisibleClipBounds(m_Parameters[0].m_pDestRectF);
			break;
		case DCUT_ISCLIPEMPTY://DestInteger
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pDestDword)
				m_Result.m_dword=*(m_Parameters[0].m_pDestDword)=(DWORD)pGraphics->IsClipEmpty();
			else	m_Result.m_dword=(DWORD)pGraphics->IsClipEmpty();
			break;
		case DCUT_ISPOINTVISIBLE://DestInteger,Point
			if (m_NParams==2 && m_Parameters && m_Parameters[0].m_pDestDword)
				m_Result.m_dword=*(m_Parameters[0].m_pDestDword)=(DWORD)pGraphics->IsVisible(*(m_Parameters[1].m_pPointF));
			break;
		case DCUT_ISRECTVISIBLE://DestInteger,Rect
			if (m_NParams==2 && m_Parameters && m_Parameters[0].m_pDestDword)
				m_Result.m_dword=*(m_Parameters[0].m_pDestDword)=(DWORD)pGraphics->IsVisible(*(m_Parameters[1].m_pRectF));
			break;
		case DCUT_ISVISIBLECLIPEMPTY://DestInteger
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pDestDword)
				m_Result.m_dword=*(m_Parameters[0].m_pDestDword)=(DWORD)pGraphics->IsVisibleClipEmpty();
			else	m_Result.m_dword=(DWORD)pGraphics->IsVisibleClipEmpty();
			break;
		case DCUT_MULTIPLYTRANSFORM://Matrix,MatrixOrder
			if (m_NParams==2 && m_Parameters && m_Parameters[0].m_pDestMatrix)
				m_Result.m_dword=(DWORD)pGraphics->MultiplyTransform(
				m_Parameters[0].m_pDestMatrix->m_Matrix,
				(MatrixOrder)m_Parameters[1].m_dword);
			break;
		case DCUT_RESETCLIP://
			m_Result.m_dword=(DWORD)pGraphics->ResetClip();
			break;
		case DCUT_RESETTRANSFORM://
			m_Result.m_dword=(DWORD)pGraphics->ResetTransform();
			break;
		case DCUT_RESTORE://Integer
			if (m_NParams==1 && m_Parameters)
				m_Result.m_dword=(DWORD)pGraphics->Restore(m_Parameters[0].m_dword);
			break;
		case DCUT_ROTATETRANSFORM://Angle,MatrixOrder
			if (m_NParams==2 && m_Parameters)
				m_Result.m_dword=(DWORD)pGraphics->RotateTransform(
				m_Parameters[0].m_real,
				(MatrixOrder)m_Parameters[1].m_dword);
			break;
		case DCUT_SAVE://DestInteger
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pDestDword)
				m_Result.m_dword=*(m_Parameters[0].m_pDestDword)=(DWORD)pGraphics->Save();
			else	m_Result.m_dword=(DWORD)pGraphics->Save();
			break;
		case DCUT_SCALETRANSFORM://sx,sy,MatrixOrder
			if (m_NParams==3 && m_Parameters)
				m_Result.m_dword=(DWORD)pGraphics->ScaleTransform(
				m_Parameters[0].m_real,
				m_Parameters[1].m_real,
				(MatrixOrder)m_Parameters[2].m_dword);
			break;
		case DCUT_SETCLIPBYRECT://Rect,CombineMode
			if (m_NParams==2 && m_Parameters) 
				m_Result.m_dword=(DWORD)pGraphics->SetClip(
				*(m_Parameters[0].m_pRectF),
				(CombineMode)m_Parameters[1].m_dword);
			break;
		case DCUT_SETCLIPBYREGION://Region,CombineMode
			if (m_NParams==2 && m_Parameters && m_Parameters[0].m_pRegion)
				m_Result.m_dword=(DWORD)pGraphics->SetClip(
				m_Parameters[0].m_pRegion->m_Rgn,
				(CombineMode)m_Parameters[1].m_dword);
			break;
		case DCUT_SETCLIPBYPATH://Path,CombineMode
			if (m_NParams==2 && m_Parameters && m_Parameters[0].m_pPath)
				m_Result.m_dword=(DWORD)pGraphics->SetClip(
				m_Parameters[0].m_pPath->m_GraphicsPath,
				(CombineMode)m_Parameters[1].m_dword);
			break;
		case DCUT_SETCOMPOSITINGMODE://CompositingMode
			if (m_NParams==1 && m_Parameters)
				m_Result.m_dword=(DWORD)pGraphics->SetCompositingMode((CompositingMode)m_Parameters[0].m_dword);
			break;
		case DCUT_SETCOMPOSITINGQUALITY://CompositingQuality
			if (m_NParams==1 && m_Parameters)
				m_Result.m_dword=(DWORD)pGraphics->SetCompositingQuality((CompositingQuality)m_Parameters[0].m_dword);
			break;
		case DCUT_SETINTERPOLATIONMODE://InterpolationMode
			if (m_NParams==1 && m_Parameters)
				m_Result.m_dword=(DWORD)pGraphics->SetInterpolationMode((InterpolationMode)m_Parameters[0].m_dword);
			break;
		case DCUT_SETPAGESCALE://Scale
			if (m_NParams==1 && m_Parameters)
				m_Result.m_dword=(DWORD)pGraphics->SetPageScale(m_Parameters[0].m_real);
			break;
		case DCUT_SETPAGEUNIT://UnitType
			if (m_NParams==1 && m_Parameters)
				m_Result.m_dword=(DWORD)pGraphics->SetPageUnit((Gdiplus::Unit)m_Parameters[0].m_dword);
			break;
		case DCUT_SETPIXELOFFSETMODE://PixelOffsetMode
			if (m_NParams==1 && m_Parameters)
				m_Result.m_dword=(DWORD)pGraphics->SetPixelOffsetMode((Gdiplus::PixelOffsetMode)m_Parameters[0].m_dword);
			break;
		case DCUT_SETRENDERINGORIGIN://intX,intY
			if (m_NParams==2 && m_Parameters)
				m_Result.m_dword=(DWORD)pGraphics->SetRenderingOrigin(m_Parameters[0].m_int,m_Parameters[1].m_int);
			break;
		case DCUT_SETSMOOTHINGMODE://SmoothingMode
			if (m_NParams==1 && m_Parameters)
				m_Result.m_dword=(DWORD)pGraphics->SetSmoothingMode((Gdiplus::SmoothingMode)m_Parameters[0].m_dword);
			break;
		case DCUT_SETTEXTCONTRAST://TextContrast
			if (m_NParams==1 && m_Parameters)
				m_Result.m_dword=(DWORD)pGraphics->SetTextContrast(m_Parameters[0].m_dword);
			break;
		case DCUT_SETTEXTRENDERINGHINT://TextRenderingHint
			if (m_NParams==1 && m_Parameters)
				m_Result.m_dword=(DWORD)pGraphics->SetTextRenderingHint((Gdiplus::TextRenderingHint)m_Parameters[0].m_dword);
			break;
		case DCUT_SETTRANSFORM://Matrix
			if (m_NParams==1 && m_Parameters && m_Parameters[0].m_pMatrix)
				m_Result.m_dword=(DWORD)pGraphics->SetTransform(m_Parameters[0].m_pDestMatrix->m_Matrix);
			break;
		case DCUT_TRANSFORMPOINTS://destSpace,srcSpace,ARRAYxxx
			if (m_NParams==3 && m_Parameters && m_Parameters[2].m_dwArray)
			{
				PointF *tmpPA=NULL;
				PointF *tmpA=NULL;
				switch(m_Parameters[2].dwParamType)
				{
				case DCPT_ARRAY|DCPT_POINT:
					tmpPA=m_Parameters[2].m_pPointF;		break;
				case DCPT_ARRAYIDX:
				case DCPT_ARRAYREF:
					{
						tmpPA=tmpA=new PointF [m_Parameters[2].dwNElements];
						UINT i;
						for(i=0;i<m_Parameters[2].dwNElements;i++)
						{
							UINT ref=m_Parameters[2].m_dwArray[i];
							if ((m_Parameters[2].dwParamType&DCPT_ARRAYREF)==DCPT_ARRAYREF && ref<pContext->m_nIntArray)
								ref=pContext->m_IntArr[ref];
							if (ref<pContext->m_nPointArray) tmpA[i]=pContext->m_PointArr[ref];
						}
					}
					break;
				}

				if (tmpPA && m_Parameters[2].dwNElements>0)
				{
					switch(m_Type)
					{
					case DCUT_TRANSFORMPOINTS://destSpace,srcSpace,ARRAYxxx
						m_Result.m_dword=(DWORD)pGraphics->TransformPoints(
							(Gdiplus::CoordinateSpace)m_Parameters[0].m_dword,
							(Gdiplus::CoordinateSpace)m_Parameters[1].m_dword,
							tmpPA,
							m_Parameters[2].dwNElements);
						break;
					}

					switch(m_Parameters[2].dwParamType)
					{
					case DCPT_ARRAY|DCPT_POINT:
						break;
					case DCPT_ARRAYIDX:
					case DCPT_ARRAYREF:
						{
							UINT i;
							for(i=0;i<m_Parameters[2].dwNElements;i++)
							{
								UINT ref=m_Parameters[2].m_dwArray[i];
								if ((m_Parameters[2].dwParamType&DCPT_ARRAYREF)==DCPT_ARRAYREF && ref<pContext->m_nIntArray)
									ref=pContext->m_IntArr[ref];
								if (ref<pContext->m_nPointArray)
									pContext->m_PointArr[ref]=tmpA[i];
							}
						}
						break;
					}
				}
				if (tmpA) delete []tmpA;
			}
			break;
		case DCUT_TRANSLATECLIP://dX,dY
			if (m_NParams==2 && m_Parameters)
				m_Result.m_dword=(DWORD)pGraphics->TranslateClip(m_Parameters[0].m_real,m_Parameters[1].m_real);
			break;
		case DCUT_TRANSLATETRANSFORM://dx,dy,MatrixOrder
			if (m_NParams==3 && m_Parameters)
				m_Result.m_dword=(DWORD)pGraphics->TranslateTransform(
				m_Parameters[0].m_real,
				m_Parameters[1].m_real,
				(MatrixOrder)m_Parameters[2].m_dword);
			break;
		case DCUT_MEASUREDRIVERSTRING://Font,Matrix,Point,flags,boundingBox,text
			if (m_NParams==6 && m_Parameters && m_Parameters[0].m_pFont && m_Parameters[1].m_pMatrix && m_Parameters[4].m_pDestRectF && m_Parameters[5].m_pCString)
			{
				UINT tLen=m_Parameters[5].m_pCString->GetLength();

				UINT16 *tmpWText2=new UINT16 [tLen*2+10];
				MultiByteToWideChar(CP_ACP, 0,*m_Parameters[5].m_pCString , -1, (LPWSTR)tmpWText2, tLen*2);

				m_Result.m_dword=(DWORD)pGraphics->MeasureDriverString(
					tmpWText2,
					tLen,
					m_Parameters[0].m_pFont->m_Font,
					m_Parameters[2].m_pPointF,
					m_Parameters[3].m_dword,
					m_Parameters[1].m_pMatrix->m_Matrix,
					m_Parameters[4].m_pDestRectF);
				delete []tmpWText2;
			}
			break;
		case DCUT_MEASURESTRING://Font,SrcRect,DstRect,text
			if (m_NParams==4 && m_Parameters && m_Parameters[0].m_pFont && m_Parameters[2].m_pDestRectF && m_Parameters[3].m_pCString)
			{
				UINT tLen=m_Parameters[3].m_pCString->GetLength();

				WCHAR *tmpWText2=new WCHAR [tLen*2+10];
				MultiByteToWideChar(CP_ACP, 0,*m_Parameters[3].m_pCString , -1, tmpWText2, tLen*2);

				m_Result.m_dword=(DWORD)pGraphics->MeasureString(
					tmpWText2,
					tLen,
					m_Parameters[0].m_pFont->m_Font,
					*m_Parameters[1].m_pRectF,
					m_Parameters[2].m_pDestRectF);
				delete []tmpWText2;
			}
			break;
		case DCUT_MEASURESTRING2://Font,Point,DstRect,text
			if (m_NParams==4 && m_Parameters && m_Parameters[0].m_pFont && m_Parameters[2].m_pDestRectF && m_Parameters[3].m_pCString)
			{
				UINT tLen=m_Parameters[3].m_pCString->GetLength();

				WCHAR *tmpWText2=new WCHAR [tLen*2+10];
				MultiByteToWideChar(CP_ACP, 0,*m_Parameters[3].m_pCString , -1, tmpWText2, tLen*2);

				m_Result.m_dword=(DWORD)pGraphics->MeasureString(
					tmpWText2,
					tLen,
					m_Parameters[0].m_pFont->m_Font,
					*m_Parameters[1].m_pPointF,
					m_Parameters[2].m_pDestRectF);
				delete []tmpWText2;
			}
			break;
		case DCUT_MEASURESTRING3://Font,SrcRect,DstRect,StringFormat,text
			if (m_NParams==5 && m_Parameters && m_Parameters[0].m_pFont && m_Parameters[3].m_pStrFormat && m_Parameters[2].m_pDestRectF && m_Parameters[4].m_pCString)
			{
				UINT tLen=m_Parameters[4].m_pCString->GetLength();

				WCHAR *tmpWText2=new WCHAR [tLen*2+10];
				MultiByteToWideChar(CP_ACP, 0,*m_Parameters[4].m_pCString , -1, tmpWText2, tLen*2);

				m_Result.m_dword=(DWORD)pGraphics->MeasureString(
					tmpWText2,
					tLen,
					m_Parameters[0].m_pFont->m_Font,
					*m_Parameters[1].m_pRectF,
					m_Parameters[3].m_pStrFormat->m_StringFormat,
					m_Parameters[2].m_pDestRectF);
				delete []tmpWText2;
			}
			break;
		case DCUT_MEASURESTRING4://Font,Point,DstRect,StringFormat,text
			if (m_NParams==5 && m_Parameters && m_Parameters[0].m_pFont && m_Parameters[3].m_pStrFormat && m_Parameters[2].m_pDestRectF && m_Parameters[4].m_pCString)
			{
				UINT tLen=m_Parameters[4].m_pCString->GetLength();

				WCHAR *tmpWText2=new WCHAR [tLen*2+10];
				MultiByteToWideChar(CP_ACP, 0,*m_Parameters[4].m_pCString , -1, tmpWText2, tLen*2);

				m_Result.m_dword=(DWORD)pGraphics->MeasureString(
					tmpWText2,
					tLen,
					m_Parameters[0].m_pFont->m_Font,
					*m_Parameters[1].m_pPointF,
					m_Parameters[3].m_pStrFormat->m_StringFormat,
					m_Parameters[2].m_pDestRectF);
				delete []tmpWText2;
			}
			break;
		case DCUT_MEASURESTRING5://Font,SrcRect,DstRect,StringFormat,codepointsFitted,linesFilled,text
			if (m_NParams==7 && m_Parameters && m_Parameters[0].m_pFont && m_Parameters[3].m_pStrFormat
				&& m_Parameters[2].m_pDestRectF && m_Parameters[6].m_pCString && m_Parameters[4].m_pDestInt
				&& m_Parameters[5].m_pDestInt)
			{
				UINT tLen=m_Parameters[6].m_pCString->GetLength();

				WCHAR *tmpWText2=new WCHAR [tLen*2+10];
				MultiByteToWideChar(CP_ACP, 0,*m_Parameters[6].m_pCString , -1, tmpWText2, tLen*2);

				m_Result.m_dword=(DWORD)pGraphics->MeasureString(
					tmpWText2,
					tLen,
					m_Parameters[0].m_pFont->m_Font,
					*m_Parameters[1].m_pRectF,
					m_Parameters[3].m_pStrFormat->m_StringFormat,
					m_Parameters[2].m_pDestRectF,
					m_Parameters[4].m_pDestInt,
					m_Parameters[5].m_pDestInt);
				delete []tmpWText2;
			}
			break;
		case DCUT_GETSYSTEMMETRICS://DestInt,MetricType
			if (m_NParams==2 && m_Parameters && m_Parameters[0].m_pDestDword)
				m_Result.m_dword=*(m_Parameters[0].m_pDestDword)=(DWORD)::GetSystemMetrics(m_Parameters[1].m_dword);
			break;
		case DCUT_GETSYSTEMCOLORS://DestColor,ColorType
			if (m_NParams==2 && m_Parameters)
			{
				Color c;
				c.SetFromCOLORREF(::GetSysColor(m_Parameters[1].m_dword));
				switch(m_Parameters[0].dwParamType&DCPT_TYPEMASK)
				{
				case DCPT_DESTCOLOR:
					if (m_Parameters[0].m_pDestColor)	*m_Parameters[0].m_pDestColor=c;
					break;
				case DCPT_DESTINTEGER:
					if (m_Parameters[0].m_pDestInt)		*m_Parameters[0].m_pDestInt=c.GetValue();
					break;
				}
			}
			break;
		case DCUT_GOTO://LAbelName
			m_Action=DCUA_GOTO;
			break;
		case DCUT_GOSUB://LAbelName
			m_Action=DCUA_GOSUB;
			break;
		case DCUT_RETURN:
			m_Action=DCUA_RETURN;
			break;
		case DCUT_IF://LeftOp,Operation,RightOp[,LogOp,LeftOp,Operation,RightOp[,LogOp,LeftOp,Operation,RightOp[,LogOp,LeftOp,Operation,RightOp]]]
		case DCUT_IFGOTO://LeftOp,Operation,RightOp,Label
		case DCUT_IFGOSUB://LeftOp,Operation,RightOp,Label
			{
				BOOL retVal=FALSE;
				BOOL results[]={FALSE,FALSE,FALSE,FALSE,FALSE,};
				if ((m_NParams==3 || m_NParams==4 || m_NParams==7 || m_NParams==11 || m_NParams==15) && m_Parameters)
				{
					int nTimes=(m_NParams+1)/4;
					int curIter;
					for(curIter=0;curIter<nTimes;curIter++)
					{
						int IdxDelta=curIter*4;
						DCParamType mType=(DCParamType)(m_Parameters[IdxDelta].dwParamType&DCPT_TYPEMASK);
						REAL rLeft=0;
						REAL rRight=0;
						INT iLeft=0;
						INT iRight=0;
						BOOL bDoCompare=TRUE;

						switch(mType)
						{
						case DCPT_RECTX:
						case DCPT_RECTY:
						case DCPT_RECTH:
						case DCPT_RECTW:
						case DCPT_POINTX:
						case DCPT_POINTY:
						case DCPT_REAL:
							iLeft=(INT)(rLeft=m_Parameters[IdxDelta].m_real);
							mType=DCPT_REAL;
							break;
						case DCPT_FLAG:
						case DCPT_INTEGER:
							rLeft=(REAL)(iLeft=m_Parameters[IdxDelta].m_int);
							mType=DCPT_INTEGER;
							break;
						case DCPT_COLOR:
							rLeft=(REAL)(iLeft=m_Parameters[IdxDelta].m_pColor->GetValue());
							mType=DCPT_INTEGER;
							break;
						case DCPT_RECT:
							if ((m_Parameters[2+IdxDelta].dwParamType&DCPT_TYPEMASK)!=DCPT_RECT || !m_Parameters[2+IdxDelta].m_pRectF) bDoCompare=FALSE;
							break;
						case DCPT_POINT:
							if ((m_Parameters[2+IdxDelta].dwParamType&DCPT_TYPEMASK)!=DCPT_POINT || !m_Parameters[2+IdxDelta].m_pPointF) bDoCompare=FALSE;
							break;
						case DCPT_STRING:
							if ((m_Parameters[2+IdxDelta].dwParamType&DCPT_TYPEMASK)!=DCPT_STRING || !m_Parameters[2+IdxDelta].m_pCString) bDoCompare=FALSE;
							break;
						case DCPT_MATRIX:
							if ((m_Parameters[2+IdxDelta].dwParamType&DCPT_TYPEMASK)!=DCPT_MATRIX || !m_Parameters[2+IdxDelta].m_pMatrix) bDoCompare=FALSE;
							break;
						default: 
							bDoCompare=FALSE;
							break;
						}
						if (bDoCompare)
							switch(m_Parameters[2+IdxDelta].dwParamType&DCPT_TYPEMASK)
							{
							case DCPT_RECTX:
							case DCPT_RECTY:
							case DCPT_RECTH:
							case DCPT_RECTW:
							case DCPT_POINTX:
							case DCPT_POINTY:
							case DCPT_REAL:
								rRight=m_Parameters[2+IdxDelta].m_real;
								mType=DCPT_REAL;
								break;
							case DCPT_FLAG:
							case DCPT_INTEGER:
								rRight=(REAL)(iRight=m_Parameters[2+IdxDelta].m_int);
								break;
							case DCPT_COLOR:
								iRight=m_Parameters[2+IdxDelta].m_pColor->GetValue();
								mType=DCPT_INTEGER;
								break;
							case DCPT_RECT:
								if ((m_Parameters[IdxDelta].dwParamType&DCPT_TYPEMASK)!=DCPT_RECT || !m_Parameters[IdxDelta].m_pRectF) bDoCompare=FALSE;
								break;
							case DCPT_POINT:
								if ((m_Parameters[IdxDelta].dwParamType&DCPT_TYPEMASK)!=DCPT_POINT || !m_Parameters[IdxDelta].m_pPointF) bDoCompare=FALSE;
								break;
							case DCPT_STRING:
								if ((m_Parameters[IdxDelta].dwParamType&DCPT_TYPEMASK)!=DCPT_STRING || !m_Parameters[IdxDelta].m_pCString) bDoCompare=FALSE;
								break;
							case DCPT_MATRIX:
								if ((m_Parameters[IdxDelta].dwParamType&DCPT_TYPEMASK)!=DCPT_MATRIX || !m_Parameters[IdxDelta].m_pMatrix) bDoCompare=FALSE;
								break;
							default: 
								bDoCompare=FALSE;
								break;
							}

						if (bDoCompare)
							switch(mType)
							{
							case DCPT_INTEGER:
								switch(m_Parameters[1+IdxDelta].m_dword)
								{
								case DCCO_EQUAL:		retVal=(iLeft==iRight);		break;
								case DCCO_LESS:			retVal=(iLeft<iRight);		break;
								case DCCO_GREATER:		retVal=(iLeft>iRight);		break;
								case DCCO_LESSEQUAL:	retVal=(iLeft<=iRight);		break;
								case DCCO_GREATEREQUAL:	retVal=(iLeft>=iRight);		break;
								case DCCO_NOTEQUAL:		retVal=(iLeft!=iRight);		break;
								case DCCO_NOTAND:		retVal=((iLeft&iRight)==0);	break;
								case DCCO_AND:			retVal=((iLeft&iRight)!=0);	break;
								}
								break;
							case DCPT_REAL:
								switch(m_Parameters[1+IdxDelta].m_dword)
								{
								case DCCO_EQUAL:		retVal=(rLeft==rRight);		break;
								case DCCO_LESS:			retVal=(rLeft<rRight);		break;
								case DCCO_GREATER:		retVal=(rLeft>rRight);		break;
								case DCCO_LESSEQUAL:	retVal=(rLeft<=rRight);		break;
								case DCCO_GREATEREQUAL:	retVal=(rLeft>=rRight);		break;
								case DCCO_NOTEQUAL:		retVal=(rLeft!=rRight);		break;
								case DCCO_NOTAND:		retVal=((iLeft&iRight)==0);	break;
								case DCCO_AND:			retVal=((iLeft&iRight)!=0);	break;
								}
								break;
							case DCPT_RECT:
								switch(m_Parameters[1+IdxDelta].m_dword)
								{
								case DCCO_EQUAL:		retVal=m_Parameters[IdxDelta].m_pRectF->Equals(*m_Parameters[2+IdxDelta].m_pRectF);		break;
								case DCCO_LESS:			retVal=m_Parameters[2+IdxDelta].m_pRectF->Contains(*m_Parameters[IdxDelta].m_pRectF);		break;
								case DCCO_GREATER:		retVal=m_Parameters[IdxDelta].m_pRectF->Contains(*m_Parameters[2+IdxDelta].m_pRectF);		break;
								case DCCO_LESSEQUAL:	
									retVal=m_Parameters[IdxDelta].m_pRectF->Equals(*m_Parameters[2+IdxDelta].m_pRectF);
									if (!retVal) retVal=m_Parameters[2+IdxDelta].m_pRectF->Contains(*m_Parameters[IdxDelta].m_pRectF);
									break;
								case DCCO_GREATEREQUAL:	retVal=(rLeft>=rRight);		break;
									retVal=m_Parameters[IdxDelta].m_pRectF->Equals(*m_Parameters[2+IdxDelta].m_pRectF);
									if (!retVal) retVal=m_Parameters[IdxDelta].m_pRectF->Contains(*m_Parameters[2+IdxDelta].m_pRectF);
								case DCCO_NOTEQUAL:		retVal=!m_Parameters[IdxDelta].m_pRectF->Equals(*m_Parameters[2+IdxDelta].m_pRectF);	break;
								}
								break;
							case DCPT_POINT:
								switch(m_Parameters[1+IdxDelta].m_dword)
								{
								case DCCO_EQUAL:		retVal=m_Parameters[IdxDelta].m_pPointF->Equals(*m_Parameters[2+IdxDelta].m_pPointF);		break;
								case DCCO_NOTEQUAL:		retVal=!m_Parameters[IdxDelta].m_pPointF->Equals(*m_Parameters[2+IdxDelta].m_pPointF);		break;
								case DCCO_LESS:			
								case DCCO_GREATER:		
								case DCCO_LESSEQUAL:	
								case DCCO_GREATEREQUAL:	
									break;
								}
								break;
							case DCPT_STRING:
								switch(m_Parameters[1+IdxDelta].m_dword)
								{
								case DCCO_EQUAL:		retVal=(*m_Parameters[IdxDelta].m_pCString==*m_Parameters[2+IdxDelta].m_pCString);		break;
								case DCCO_LESS:			retVal=(*m_Parameters[IdxDelta].m_pCString<*m_Parameters[2+IdxDelta].m_pCString);		break;
								case DCCO_GREATER:		retVal=(*m_Parameters[IdxDelta].m_pCString>*m_Parameters[2+IdxDelta].m_pCString);		break;
								case DCCO_LESSEQUAL:	retVal=(*m_Parameters[IdxDelta].m_pCString<=*m_Parameters[2+IdxDelta].m_pCString);		break;
								case DCCO_GREATEREQUAL:	retVal=(*m_Parameters[IdxDelta].m_pCString>=*m_Parameters[2+IdxDelta].m_pCString);		break;
								case DCCO_NOTEQUAL:		retVal=(*m_Parameters[IdxDelta].m_pCString!=*m_Parameters[2+IdxDelta].m_pCString);		break;
								}
								break;
							case DCPT_MATRIX:
								switch(m_Parameters[1+IdxDelta].m_dword)
								{
								case DCCO_EQUAL:		retVal=m_Parameters[IdxDelta].m_pMatrix->m_Matrix->Equals(m_Parameters[2+IdxDelta].m_pMatrix->m_Matrix);		break;
								case DCCO_NOTEQUAL:		retVal=!m_Parameters[IdxDelta].m_pMatrix->m_Matrix->Equals(m_Parameters[2+IdxDelta].m_pMatrix->m_Matrix);		break;
								case DCCO_LESS:			
								case DCCO_GREATER:		
								case DCCO_LESSEQUAL:	
								case DCCO_GREATEREQUAL:	
									break;
								}
								break;
							default: 
								break;
							}
						results[curIter]=retVal;
					}
					retVal=results[0];
					for(curIter=1;curIter<nTimes;curIter++)
					{
						switch(m_Parameters[curIter*4-1].m_dword)
						{
						case DCAO_OR:	retVal=(retVal || results[curIter]);	break;
						case DCAO_XOR:	retVal=(retVal ^ results[curIter]);	break;
						case DCAO_AND:	retVal=(retVal && results[curIter]);	break;
						default:		retVal=FALSE;	break;
						}
					}
				}

				switch(m_Type)
				{
				case DCUT_IF://LeftOp,Operation,RightOp
					if (!retVal) m_Action=DCUA_GOTOELSE;
					break;
				case DCUT_IFGOTO://LeftOp,Operation,RightOp,Label
					if (retVal) m_Action=DCUA_GOTO;
					break;
				case DCUT_IFGOSUB://LeftOp,Operation,RightOp,Label
					if (retVal) m_Action=DCUA_GOSUB;
					break;
				}
			}
			break;
		case DCUT_ELSE:
			m_Action=DCUA_GOTOENDIF;
			break;
		case DCUT_SET://LeftOp,RightOp
			if (m_NParams==2 && m_Parameters && m_Parameters[0].m_pDestDword)
			{
				DCParamType mType=DCPT_INTEGER;
				REAL rsrc=0;
				INT isrc=0;

				switch(m_Parameters[1].dwParamType&DCPT_TYPEMASK)
				{
				case DCPT_RECTX:
				case DCPT_RECTY:
				case DCPT_RECTH:
				case DCPT_RECTW:
				case DCPT_POINTX:
				case DCPT_POINTY:
				case DCPT_REAL:
					switch(m_Parameters[0].dwParamType&DCPT_TYPEMASK)
					{
					case DCPT_DESTRECTX:
					case DCPT_DESTRECTY:
					case DCPT_DESTRECTH:
					case DCPT_DESTRECTW:
					case DCPT_DESTPOINTX:
					case DCPT_DESTPOINTY:
					case DCPT_DESTREAL:
						*(m_Parameters[0].m_pDestReal)=m_Parameters[1].m_real;
						break;
					case DCPT_DESTRECT:
						m_Parameters[0].m_pDestRectF->X=m_Parameters[0].m_pDestRectF->Y
							=m_Parameters[0].m_pDestRectF->Height=m_Parameters[0].m_pDestRectF->Width=m_Parameters[1].m_real;
						break;
					case DCPT_DESTPOINT:
						m_Parameters[0].m_pDestPointF->X=m_Parameters[0].m_pDestPointF->Y=m_Parameters[1].m_real;
						break;
					case DCPT_DESTCOLOR:
						m_Parameters[0].m_pDestColor->SetValue((ARGB)m_Parameters[1].m_real);
						break;
					case DCPT_DESTMATRIX:
						m_Parameters[0].m_pDestMatrix->m_Matrix->SetElements(
							m_Parameters[1].m_real,m_Parameters[1].m_real,m_Parameters[1].m_real,
							m_Parameters[1].m_real,m_Parameters[1].m_real,m_Parameters[1].m_real
							);
						break;
					case DCPT_DESTINTEGER:
						*(m_Parameters[0].m_pDestInt)=(INT)m_Parameters[1].m_real;
						break;
					case DCPT_DESTSTRING:
						m_Parameters[0].m_pDestCString->Format("%g",m_Parameters[1].m_real);
						break;
					}
					break;
				case DCPT_COLOR:
					switch(m_Parameters[0].dwParamType&DCPT_TYPEMASK)
					{
					case DCPT_DESTRECTX:
					case DCPT_DESTRECTY:
					case DCPT_DESTRECTH:
					case DCPT_DESTRECTW:
					case DCPT_DESTPOINTX:
					case DCPT_DESTPOINTY:
					case DCPT_DESTREAL:
						*(m_Parameters[0].m_pDestReal)=(REAL)m_Parameters[1].m_pColor->GetValue();
						break;
					case DCPT_DESTRECT:
						m_Parameters[0].m_pDestRectF->X=m_Parameters[1].m_pColor->GetA();
						m_Parameters[0].m_pDestRectF->Y=m_Parameters[1].m_pColor->GetR();
						m_Parameters[0].m_pDestRectF->Width=m_Parameters[1].m_pColor->GetG();
						m_Parameters[0].m_pDestRectF->Height=m_Parameters[1].m_pColor->GetB();
						break;
					case DCPT_DESTPOINT:
						m_Parameters[0].m_pDestPointF->X=m_Parameters[0].m_pDestPointF->Y=(REAL)m_Parameters[1].m_pColor->GetValue();
						break;
					case DCPT_DESTCOLOR:
						*(m_Parameters[0].m_pDestColor)=*m_Parameters[1].m_pColor;
						break;
					case DCPT_DESTMATRIX:
						m_Parameters[0].m_pDestMatrix->m_Matrix->SetElements(
							m_Parameters[1].m_pColor->GetA(),m_Parameters[1].m_pColor->GetR(),m_Parameters[1].m_pColor->GetG(),
							m_Parameters[1].m_pColor->GetB(),0,0
							);
						break;
					case DCPT_DESTINTEGER:
						*(m_Parameters[0].m_pDestInt)=(INT)m_Parameters[1].m_pColor->GetValue();
						break;
					case DCPT_DESTSTRING:
						m_Parameters[0].m_pDestCString->Format("%d,%d,%d,%d",
							m_Parameters[1].m_pColor->GetRed(),
							m_Parameters[1].m_pColor->GetGreen(),
							m_Parameters[1].m_pColor->GetBlue(),
							m_Parameters[1].m_pColor->GetAlpha()
							);
						break;
					}
					break;
				case DCPT_RECT:
					switch(m_Parameters[0].dwParamType&DCPT_TYPEMASK)
					{
					case DCPT_DESTRECTX:
					case DCPT_DESTRECTY:
					case DCPT_DESTRECTH:
					case DCPT_DESTRECTW:
					case DCPT_DESTPOINTX:
					case DCPT_DESTPOINTY:
					case DCPT_DESTREAL:
						*(m_Parameters[0].m_pDestReal)=m_Parameters[1].m_pRectF->X;
						break;
					case DCPT_DESTRECT:
						*(m_Parameters[0].m_pDestRectF)=*m_Parameters[1].m_pRectF;
						break;
					case DCPT_DESTPOINT:
						m_Parameters[0].m_pDestPointF->X=m_Parameters[1].m_pRectF->X;
						m_Parameters[0].m_pDestPointF->Y=m_Parameters[1].m_pRectF->Y;
						break;
					case DCPT_DESTCOLOR:
						m_Parameters[0].m_pDestColor->SetValue(Color::MakeARGB(
							(BYTE)m_Parameters[1].m_pRectF->X,	(BYTE)m_Parameters[1].m_pRectF->Y,
							(BYTE)m_Parameters[1].m_pRectF->Width,	(BYTE)m_Parameters[1].m_pRectF->Height));
						break;
					case DCPT_DESTMATRIX:
						m_Parameters[0].m_pDestMatrix->m_Matrix->SetElements(
							m_Parameters[1].m_pRectF->X,m_Parameters[1].m_pRectF->Y,m_Parameters[1].m_pRectF->Width,
							m_Parameters[1].m_pRectF->Height,0,0
							);
						break;
					case DCPT_DESTINTEGER:
						*(m_Parameters[0].m_pDestInt)=((INT)m_Parameters[1].m_pRectF->X)+0x10000*((INT)m_Parameters[1].m_pRectF->Y);
						break;
					case DCPT_DESTSTRING:
						m_Parameters[0].m_pDestCString->Format("%g,%g,%g,%g",
							m_Parameters[1].m_pRectF->X,
							m_Parameters[1].m_pRectF->Y,
							m_Parameters[1].m_pRectF->Width,
							m_Parameters[1].m_pRectF->Height
							);
						break;
					case DCPT_DESTREGION:
						m_Parameters[0].m_pDestRegion->m_Rgn->MakeEmpty();
						m_Parameters[0].m_pDestRegion->m_Rgn->Union(*(m_Parameters[1].m_pRectF));
						break;
					}
					break;
				case DCPT_POINT:
					switch(m_Parameters[0].dwParamType&DCPT_TYPEMASK)
					{
					case DCPT_DESTRECTX:
					case DCPT_DESTRECTY:
					case DCPT_DESTRECTH:
					case DCPT_DESTRECTW:
					case DCPT_DESTPOINTX:
					case DCPT_DESTPOINTY:
					case DCPT_DESTREAL:
						*(m_Parameters[0].m_pDestReal)=m_Parameters[1].m_pPointF->X;
						break;
					case DCPT_DESTRECT:
						m_Parameters[0].m_pDestRectF->X=m_Parameters[1].m_pPointF->X;
						m_Parameters[0].m_pDestRectF->Y=m_Parameters[1].m_pPointF->Y;
						break;
					case DCPT_DESTPOINT:
						*m_Parameters[0].m_pDestPointF=*m_Parameters[1].m_pPointF;
						break;
					case DCPT_DESTCOLOR:
						m_Parameters[0].m_pDestColor->SetValue(Color::MakeARGB((BYTE)m_Parameters[1].m_pPointF->X,(BYTE)m_Parameters[1].m_pPointF->Y,0,0));
						break;
					case DCPT_DESTMATRIX:
						m_Parameters[0].m_pDestMatrix->m_Matrix->Shear(m_Parameters[1].m_pPointF->X,m_Parameters[1].m_pPointF->Y);
						break;
					case DCPT_DESTINTEGER:
						*(m_Parameters[0].m_pDestInt)=((INT)m_Parameters[1].m_pPointF->X)+0x10000*((INT)m_Parameters[1].m_pPointF->Y);
						break;
					case DCPT_DESTSTRING:
						m_Parameters[0].m_pDestCString->Format("%g,%g",
							m_Parameters[1].m_pPointF->X,
							m_Parameters[1].m_pPointF->Y
							);
						break;
					}
					break;
				case DCPT_STRING:
					switch(m_Parameters[0].dwParamType&DCPT_TYPEMASK)
					{
					case DCPT_DESTRECTX:
					case DCPT_DESTRECTY:
					case DCPT_DESTRECTH:
					case DCPT_DESTRECTW:
					case DCPT_DESTPOINTX:
					case DCPT_DESTPOINTY:
					case DCPT_DESTREAL:
						*(m_Parameters[0].m_pDestReal)=(REAL)atof(*m_Parameters[1].m_pCString);
						break;
					case DCPT_DESTRECT:
						sscanf(*m_Parameters[1].m_pCString,"%g,%g,%g,%g",
							&m_Parameters[0].m_pDestRectF->X,
							&m_Parameters[0].m_pDestRectF->Y,
							&m_Parameters[0].m_pDestRectF->Width,
							&m_Parameters[0].m_pDestRectF->Height
							);
						break;
					case DCPT_DESTPOINT:
						sscanf(*m_Parameters[1].m_pCString,"%g,%g",
							&m_Parameters[0].m_pDestPointF->X,
							&m_Parameters[0].m_pDestPointF->Y
							);
						break;
					case DCPT_DESTCOLOR:
						{
							m_Parameters[0].m_pDestColor->SetValue(CODContext::GetColorFromString(pContext, *m_Parameters[1].m_pCString));
						}
						break;
					case DCPT_DESTMATRIX:
						{
							REAL rea[10]={0,0,0,0,0,0,0,0,0,};
							sscanf(*m_Parameters[1].m_pCString,"%g,%g,%g,%g,%g,%g",rea,rea+1,rea+2,rea+3,rea+4,rea+5);
							m_Parameters[0].m_pDestMatrix->m_Matrix->SetElements(rea[0],rea[1],rea[2],rea[3],rea[4],rea[5]);
						}
						break;
					case DCPT_DESTINTEGER:
						*(m_Parameters[0].m_pDestInt)=(INT)atoi(*m_Parameters[1].m_pCString);
						break;
					case DCPT_DESTSTRING:
						*m_Parameters[0].m_pDestCString=*m_Parameters[1].m_pCString;
						break;
					}
					break;
				case DCPT_MATRIX:
					if (m_Parameters[1].m_pMatrix && m_Parameters[1].m_pMatrix->m_Matrix)
					switch(m_Parameters[0].dwParamType&DCPT_TYPEMASK)
					{
					case DCPT_DESTRECTX:
					case DCPT_DESTRECTY:
					case DCPT_DESTRECTH:
					case DCPT_DESTRECTW:
					case DCPT_DESTPOINTX:
					case DCPT_DESTPOINTY:
					case DCPT_DESTREAL:
						 *(m_Parameters[0].m_pDestReal)=(REAL)m_Parameters[1].m_pMatrix->m_Matrix->IsInvertible();
						break;
					case DCPT_DESTRECT:
						{
							REAL rea[10]={0,0,0,0,0,0,0,0,0,};
							m_Parameters[1].m_pMatrix->m_Matrix->GetElements(rea);
							m_Parameters[0].m_pDestRectF->X=rea[0];
							m_Parameters[0].m_pDestRectF->Y=rea[1];
							m_Parameters[0].m_pDestRectF->Width=rea[2];
							m_Parameters[0].m_pDestRectF->Height=rea[3];
						}
						break;
					case DCPT_DESTPOINT:
						{
							REAL rea[10]={0,0,0,0,0,0,0,0,0,};
							m_Parameters[1].m_pMatrix->m_Matrix->GetElements(rea);
							m_Parameters[0].m_pDestPointF->X=rea[0];
							m_Parameters[0].m_pDestPointF->Y=rea[1];
						}
						break;
					case DCPT_DESTCOLOR:
						{
							REAL rea[10]={0,0,0,0,0,0,0,0,0,};
							m_Parameters[1].m_pMatrix->m_Matrix->GetElements(rea);
							m_Parameters[0].m_pDestColor->SetValue(Color::MakeARGB((BYTE)rea[0],(BYTE)rea[1],(BYTE)rea[2],(BYTE)rea[3]));
						}
						break;
					case DCPT_DESTMATRIX:
						{
							REAL rea[10]={0,0,0,0,0,0,0,0,0,};
							m_Parameters[1].m_pMatrix->m_Matrix->GetElements(rea);
							m_Parameters[0].m_pDestMatrix->m_Matrix->SetElements(rea[0],rea[1],rea[2],rea[3],rea[4],rea[5]);
						}
						break;
					case DCPT_DESTINTEGER:
						*(m_Parameters[0].m_pDestInt)=(INT)m_Parameters[1].m_pMatrix->m_Matrix->GetLastStatus();
						break;
					case DCPT_DESTSTRING:
						{
							REAL rea[10]={0};
							m_Parameters[1].m_pMatrix->m_Matrix->GetElements(rea);
							m_Parameters[0].m_pDestCString->Format("%g,%g,%g,%g,%g,%g",rea[0],rea[1],rea[2],rea[3],rea[4],rea[5]);
						}
						break;
					}
					break;
				case DCPT_REGION:
					if (m_Parameters[1].m_pMatrix && m_Parameters[1].m_pMatrix->m_Matrix)
					switch(m_Parameters[0].dwParamType&DCPT_TYPEMASK)
					{
					case DCPT_DESTRECT:
						m_Parameters[1].m_pRegion->m_Rgn->GetBounds(m_Parameters[0].m_pDestRectF,pGraphics);
						break;
					}
					break;
				case DCPT_INTEGER:
				case DCPT_FLAG:
					switch(m_Parameters[0].dwParamType&DCPT_TYPEMASK)
					{
					case DCPT_DESTRECTX:
					case DCPT_DESTRECTY:
					case DCPT_DESTRECTH:
					case DCPT_DESTRECTW:
					case DCPT_DESTPOINTX:
					case DCPT_DESTPOINTY:
					case DCPT_DESTREAL:
						*(m_Parameters[0].m_pDestReal)=(REAL)m_Parameters[1].m_dword;
						break;
					case DCPT_DESTRECT:
						m_Parameters[0].m_pDestRectF->X=
						m_Parameters[0].m_pDestRectF->Y=
						m_Parameters[0].m_pDestRectF->Width=
						m_Parameters[0].m_pDestRectF->Height=(REAL)m_Parameters[1].m_dword;
						break;
					case DCPT_DESTPOINT:
						m_Parameters[0].m_pDestPointF->X=m_Parameters[0].m_pDestPointF->Y=(REAL)m_Parameters[1].m_dword;
						break;
					case DCPT_DESTCOLOR:
						m_Parameters[0].m_pDestColor->SetValue((ARGB)m_Parameters[1].m_dword);
						break;
					case DCPT_DESTMATRIX:
						m_Parameters[0].m_pDestMatrix->m_Matrix->SetElements(
							(REAL)m_Parameters[1].m_dword,
							(REAL)m_Parameters[1].m_dword,
							(REAL)m_Parameters[1].m_dword,
							(REAL)m_Parameters[1].m_dword,
							(REAL)m_Parameters[1].m_dword,
							(REAL)m_Parameters[1].m_dword
							);

						break;
					case DCPT_DESTINTEGER:
						*m_Parameters[0].m_pDestInt=m_Parameters[1].m_dword;
						break;
					case DCPT_DESTSTRING:
						m_Parameters[0].m_pDestCString->Format("%d",m_Parameters[1].m_dword);
						break;
					}
					break;
				}
			}
			break;
		case DCUT_ARITHMETIC://LeftOp,RightArg1,Operator,RightArg2
			if (m_NParams==4 && m_Parameters)
			{
				REAL r1=0;
				REAL r2=0;
				INT i1=0;
				INT i2=0;
				switch(m_Parameters[1].dwParamType&DCPT_TYPEMASK)
				{
				case DCPT_RECTX:
				case DCPT_RECTY:
				case DCPT_RECTH:
				case DCPT_RECTW:
				case DCPT_POINTX:
				case DCPT_POINTY:
				case DCPT_REAL:
					i1=(INT)(r1=m_Parameters[1].m_real);
					break;
				case DCPT_COLOR:
					r1=(REAL)(i1=m_Parameters[1].m_pColor->GetValue());
					break;
				case DCPT_RECT:
					r1=(REAL)(i1=(INT)m_Parameters[1].m_pRectF->X+0x10000*(INT)m_Parameters[1].m_pRectF->Y);
					break;
				case DCPT_POINT:
					r1=(REAL)(i1=(INT)m_Parameters[1].m_pPointF->X+0x10000*(INT)m_Parameters[1].m_pPointF->Y);
					break;
				case DCPT_STRING:
					i1=atoi(*m_Parameters[1].m_pCString);
					r1=(REAL)atof(*m_Parameters[1].m_pCString);
					break;
				case DCPT_MATRIX:
					break;
				case DCPT_INTEGER:
				case DCPT_FLAG:
					r1=(REAL)(i1=m_Parameters[1].m_int);
					break;
				}

				switch(m_Parameters[3].dwParamType&DCPT_TYPEMASK)
				{
				case DCPT_RECTX:
				case DCPT_RECTY:
				case DCPT_RECTH:
				case DCPT_RECTW:
				case DCPT_POINTX:
				case DCPT_POINTY:
				case DCPT_REAL:
					i2=(INT)(r2=m_Parameters[3].m_real);
					break;
				case DCPT_COLOR:
					r2=(REAL)(i2=m_Parameters[3].m_pColor->GetValue());
					break;
				case DCPT_RECT:
					r2=(REAL)(i2=(INT)m_Parameters[3].m_pRectF->X+0x10000*(INT)m_Parameters[3].m_pRectF->Y);
					break;
				case DCPT_POINT:
					r2=(REAL)(i2=(INT)m_Parameters[3].m_pPointF->X+0x10000*(INT)m_Parameters[3].m_pPointF->Y);
					break;
				case DCPT_STRING:
					i2=atoi(*m_Parameters[3].m_pCString);
					r2=(REAL)atof(*m_Parameters[3].m_pCString);
					break;
				case DCPT_MATRIX:
					break;
				case DCPT_INTEGER:
				case DCPT_FLAG:
					r2=(REAL)(i2=m_Parameters[3].m_int);
					break;
				}


				switch(m_Parameters[0].dwParamType&DCPT_TYPEMASK)
				{
					case DCPT_DESTRECTX:
					case DCPT_DESTRECTY:
					case DCPT_DESTRECTH:
					case DCPT_DESTRECTW:
					case DCPT_DESTPOINTX:
					case DCPT_DESTPOINTY:
					case DCPT_DESTREAL:
						switch(m_Parameters[2].m_dword)
						{
						case DCAO_PLUS:		*m_Parameters[0].m_pDestReal=r1+r2;	break;
						case DCAO_MINUS:	*m_Parameters[0].m_pDestReal=r1-r2;	break;
						case DCAO_MUL: 		*m_Parameters[0].m_pDestReal=r1*r2;	break;
						case DCAO_DIV:
							if (r2!=0)		*m_Parameters[0].m_pDestReal=r1/r2;	break;
						case DCAO_OR: 		*m_Parameters[0].m_pDestReal=(REAL)(i1|i2);	break;
						case DCAO_XOR: 		*m_Parameters[0].m_pDestReal=(REAL)(i1^i2);	break;
						case DCAO_AND: 		*m_Parameters[0].m_pDestReal=(REAL)(i1&i2);	break;
						case DCAO_TORIGHT: 	*m_Parameters[0].m_pDestReal=(REAL)(i1>>i2);	break;
						case DCAO_TOLEFT: 	*m_Parameters[0].m_pDestReal=(REAL)(i1<<i2);	break;
						case DCAO_MODULO: 	*m_Parameters[0].m_pDestReal=(REAL)(i1%i2);	break;
						case DCAO_CENTER: 	*m_Parameters[0].m_pDestReal=(r1-r2)/2;	break;
						}
						break;
					case DCPT_DESTSTRING:
						{
							if ((m_Parameters[1].dwParamType&DCPT_TYPEMASK)==DCPT_STRING || (m_Parameters[3].dwParamType&DCPT_TYPEMASK)==DCPT_STRING)
							{
								CString tmpParam;
								if ((m_Parameters[1].dwParamType&DCPT_TYPEMASK)==DCPT_STRING && (m_Parameters[3].dwParamType&DCPT_TYPEMASK)==DCPT_STRING)
								{
									switch(m_Parameters[2].m_dword)
									{
									case DCAO_PLUS:
										*m_Parameters[0].m_pDestCString=*m_Parameters[1].m_pCString+*m_Parameters[3].m_pCString;
										break;
									case DCAO_MINUS:
										tmpParam=*m_Parameters[1].m_pCString;
										tmpParam.Replace(*m_Parameters[3].m_pCString,"");
										*m_Parameters[0].m_pDestCString=tmpParam;
										break;
									case DCAO_DIV:
										{
											tmpParam=*m_Parameters[1].m_pCString;
											int len=m_Parameters[3].m_pCString->GetLength();
											while(--len>=0)
												tmpParam.Replace(m_Parameters[3].m_pCString->Mid(len,1),"");
											*m_Parameters[0].m_pDestCString=tmpParam;
										}
										break;
									case DCAO_OR: 		
										{
											tmpParam=*m_Parameters[1].m_pCString;
											int len=m_Parameters[3].m_pCString->GetLength();
											while(--len>=0)
												tmpParam.Replace(m_Parameters[3].m_pCString->Mid(len,1),"");
											tmpParam+=*m_Parameters[3].m_pCString;
											*m_Parameters[0].m_pDestCString=tmpParam;
										}
										break;
									}
								}
								else
								if ((m_Parameters[1].dwParamType&DCPT_TYPEMASK)==DCPT_STRING)
								{
									CString tmpCS;
									CString tmpCSFirst=*m_Parameters[1].m_pCString;
									switch(m_Parameters[2].m_dword)
									{
									case DCAO_PLUS:
										switch(m_Parameters[3].dwParamType&DCPT_TYPEMASK)
										{
										case DCPT_RECTX:
										case DCPT_RECTY:
										case DCPT_RECTH:
										case DCPT_RECTW:
										case DCPT_POINTX:
										case DCPT_POINTY:
										case DCPT_REAL:
											tmpCS.Format("%g",r2);
											*m_Parameters[0].m_pDestCString=tmpCSFirst+tmpCS;
											break;
										case DCPT_COLOR:
											tmpCS.Format("%d",i2);
											*m_Parameters[0].m_pDestCString=tmpCSFirst+tmpCS;
											break;
										case DCPT_RECT:
											tmpCS.Format("%g,%g,%g,%g",
												m_Parameters[3].m_pRectF->X,m_Parameters[3].m_pRectF->Y,
												m_Parameters[3].m_pRectF->Width,m_Parameters[3].m_pRectF->Height);
											*m_Parameters[0].m_pDestCString=tmpCSFirst+tmpCS;
											break;
										case DCPT_POINT:
											tmpCS.Format("%g,%g",
												m_Parameters[3].m_pPointF->X,m_Parameters[3].m_pPointF->Y);
											*m_Parameters[0].m_pDestCString=tmpCSFirst+tmpCS;
											break;
										case DCPT_MATRIX:
											{
												REAL rea[10]={0,0,0,0,0,0,0,0,0,};
												m_Parameters[3].m_pMatrix->m_Matrix->GetElements(rea);
												tmpCS.Format("%g,%g,%g,%g,%g,%g",rea[0],rea[1],rea[2],rea[3],rea[4],rea[5]);
												*m_Parameters[0].m_pDestCString=tmpCSFirst+tmpCS;
											}
											break;
										case DCPT_INTEGER:
										case DCPT_FLAG:
											tmpCS.Format("%d",i2);
											*m_Parameters[0].m_pDestCString=tmpCSFirst+tmpCS;
											break;
										}
										break;
									case DCAO_MUL:
										{
											while(i2-->0)	tmpCS+=tmpCSFirst;
											*m_Parameters[0].m_pDestCString=tmpCS;
										}
										break;
									}
								}
							}
							else
							{
								INT desti=0;
								if (((m_Parameters[1].dwParamType&DCPT_TYPEMASK)>DCPT_MINREAL &&  (m_Parameters[1].dwParamType&DCPT_TYPEMASK)<DCPT_MAXREAL)||
									((m_Parameters[3].dwParamType&DCPT_TYPEMASK)>DCPT_MINREAL &&  (m_Parameters[3].dwParamType&DCPT_TYPEMASK)<DCPT_MAXREAL))
								{
									REAL dest=0;
									switch(m_Parameters[2].m_dword)
									{
									case DCAO_PLUS:		dest=r1+r2;	break;
									case DCAO_MINUS:	dest=r1-r2;	break;
									case DCAO_MUL: 		dest=r1*r2;	break;
									case DCAO_DIV:
										if (r2!=0)		dest=r1/r2;	break;
									case DCAO_OR: 		dest=(REAL)(i1|i2);	break;
									case DCAO_XOR: 		dest=(REAL)(i1^i2);	break;
									case DCAO_AND: 		dest=(REAL)(i1&i2);	break;
									case DCAO_TORIGHT: 	dest=(REAL)(i1>>i2);	break;
									case DCAO_TOLEFT: 	dest=(REAL)(i1<<i2);	break;
									case DCAO_MODULO: 	dest=(REAL)(i1%i2);	break;
									case DCAO_CENTER: 	dest=(r1-r2)/2;	break;
									}
									m_Parameters[0].m_pDestCString->Format("%g",dest);
								}
								else
								{
									INT dest=0;
									switch(m_Parameters[2].m_dword)
									{
									case DCAO_PLUS:		dest=i1+i2;	break;
									case DCAO_MINUS:	dest=i1-i2;	break;
									case DCAO_MUL: 		dest=i1*i2;	break;
									case DCAO_DIV:		
										if (i2!=0)		dest=i1/i2;	break;
									case DCAO_OR: 		dest=i1|i2;	break;
									case DCAO_XOR: 		dest=i1^i2;	break;
									case DCAO_AND: 		dest=i1&i2;	break;
									case DCAO_TORIGHT: 	dest=i1>>i2;	break;
									case DCAO_TOLEFT: 	dest=i1<<i2;	break;
									case DCAO_MODULO: 	dest=i1%i2;	break;
									case DCAO_CENTER: 	dest=(i1-i2)/2;	break;
									}
									m_Parameters[0].m_pDestCString->Format("%d",dest);
								}
							}
						}
						break;
					case DCPT_DESTRECT:
						switch(m_Parameters[1].dwParamType&DCPT_TYPEMASK)
						{
						case DCPT_RECT:
							*m_Parameters[0].m_pDestRectF=*m_Parameters[1].m_pRectF;
							switch(m_Parameters[3].dwParamType&DCPT_TYPEMASK)
							{
							case DCPT_RECT:
								switch(m_Parameters[2].m_dword)
								{
								case DCAO_PLUS:
									m_Parameters[0].m_pDestRectF->X+=m_Parameters[3].m_pRectF->X;
									m_Parameters[0].m_pDestRectF->Y+=m_Parameters[3].m_pRectF->Y;
									m_Parameters[0].m_pDestRectF->Width+=m_Parameters[3].m_pRectF->Width;
									m_Parameters[0].m_pDestRectF->Height+=m_Parameters[3].m_pRectF->Height;
									break;
								case DCAO_MINUS: 
									m_Parameters[0].m_pDestRectF->X-=m_Parameters[3].m_pRectF->X;
									m_Parameters[0].m_pDestRectF->Y-=m_Parameters[3].m_pRectF->Y;
									m_Parameters[0].m_pDestRectF->Width-=m_Parameters[3].m_pRectF->Width;
									m_Parameters[0].m_pDestRectF->Height-=m_Parameters[3].m_pRectF->Height;
									break;
								case DCAO_OR:
								case DCAO_XOR:
									{
										REAL right = max(m_Parameters[1].m_pRectF->GetRight(), m_Parameters[3].m_pRectF->GetRight());
										REAL bottom = max(m_Parameters[1].m_pRectF->GetBottom(), m_Parameters[3].m_pRectF->GetBottom());
										REAL left = min(m_Parameters[1].m_pRectF->GetLeft(), m_Parameters[3].m_pRectF->GetLeft());
										REAL top = min(m_Parameters[1].m_pRectF->GetTop(), m_Parameters[3].m_pRectF->GetTop());

										m_Parameters[0].m_pDestRectF->X = left;
										m_Parameters[0].m_pDestRectF->Y = top;
										m_Parameters[0].m_pDestRectF->Width = right - left;
										m_Parameters[0].m_pDestRectF->Height = bottom - top;
									}
									break;
								case DCAO_AND:
								case DCAO_MUL:
								case DCAO_DIV:
									{
										REAL right = min(m_Parameters[1].m_pRectF->GetRight(), m_Parameters[3].m_pRectF->GetRight());
										REAL bottom = min(m_Parameters[1].m_pRectF->GetBottom(), m_Parameters[3].m_pRectF->GetBottom());
										REAL left = max(m_Parameters[1].m_pRectF->GetLeft(), m_Parameters[3].m_pRectF->GetLeft());
										REAL top = max(m_Parameters[1].m_pRectF->GetTop(), m_Parameters[3].m_pRectF->GetTop());

										m_Parameters[0].m_pDestRectF->X = left;
										m_Parameters[0].m_pDestRectF->Y = top;
										m_Parameters[0].m_pDestRectF->Width = right - left;
										m_Parameters[0].m_pDestRectF->Height = bottom - top;
									}
									break;
								case DCAO_CENTER: 
									m_Parameters[0].m_pDestRectF->X=m_Parameters[1].m_pRectF->X+((m_Parameters[1].m_pRectF->Width-m_Parameters[3].m_pRectF->Width)/2);
									m_Parameters[0].m_pDestRectF->Y=m_Parameters[1].m_pRectF->Y+((m_Parameters[1].m_pRectF->Height-m_Parameters[3].m_pRectF->Height)/2);
									m_Parameters[0].m_pDestRectF->Width=m_Parameters[3].m_pRectF->Width;
									m_Parameters[0].m_pDestRectF->Height=m_Parameters[3].m_pRectF->Height;
									break;
								}
								break;
							case DCPT_POINT:
								switch(m_Parameters[2].m_dword)
								{
								case DCAO_PLUS: 
									m_Parameters[0].m_pDestRectF->X+=m_Parameters[3].m_pPointF->X;
									m_Parameters[0].m_pDestRectF->Y+=m_Parameters[3].m_pPointF->Y;
									break;
								case DCAO_MINUS: 
									m_Parameters[0].m_pDestRectF->X-=m_Parameters[3].m_pPointF->X;
									m_Parameters[0].m_pDestRectF->Y-=m_Parameters[3].m_pPointF->Y;
									break;
								case DCAO_MUL: 
									m_Parameters[0].m_pDestRectF->Inflate(*m_Parameters[3].m_pPointF);
									break;
								case DCAO_DIV: 
									m_Parameters[0].m_pDestRectF->Offset(*m_Parameters[3].m_pPointF);
									break;
								case DCAO_CENTER:
									m_Parameters[0].m_pDestRectF->X=m_Parameters[3].m_pPointF->X-m_Parameters[1].m_pRectF->Width/2;
									m_Parameters[0].m_pDestRectF->Y=m_Parameters[3].m_pPointF->Y-m_Parameters[1].m_pRectF->Height/2;
									m_Parameters[0].m_pDestRectF->Width=m_Parameters[1].m_pRectF->Width;
									m_Parameters[0].m_pDestRectF->Height=m_Parameters[1].m_pRectF->Height;
									break;
								case DCAO_OR: 
								case DCAO_XOR: 
								case DCAO_AND:
								case DCAO_TORIGHT: 
								case DCAO_TOLEFT: 
								case DCAO_MODULO: 
									break;
								}
								break;
							default:
								switch(m_Parameters[2].m_dword)
								{
								case DCAO_PLUS: 
									m_Parameters[0].m_pDestRectF->Width+=r2;
									m_Parameters[0].m_pDestRectF->Height+=r2;
									break;
								case DCAO_MINUS: 
									m_Parameters[0].m_pDestRectF->Width-=r2;
									m_Parameters[0].m_pDestRectF->Height-=r2;
									break;
								case DCAO_MUL: 
									m_Parameters[0].m_pDestRectF->Inflate(r2,r2);
									 break;
								case DCAO_DIV: 
									m_Parameters[0].m_pDestRectF->Offset(r2,r2);
									 break;
								case DCAO_OR: 
								case DCAO_XOR: 
								case DCAO_AND:
								case DCAO_TORIGHT: 
								case DCAO_TOLEFT: 
								case DCAO_MODULO: 
									break;
								}
								break;
							}
							break;
						default:
							switch(m_Parameters[2].m_dword)
							{
							case DCAO_PLUS: 
								m_Parameters[0].m_pDestRectF->Width+=r1;
								m_Parameters[0].m_pDestRectF->Height+=r2;
								break;
							case DCAO_MINUS: 
								m_Parameters[0].m_pDestRectF->Width-=r1;
								m_Parameters[0].m_pDestRectF->Height-=r2;
								break;
							case DCAO_MUL: 
								m_Parameters[0].m_pDestRectF->Inflate(r1,r2);
								 break;
							case DCAO_DIV: 
								m_Parameters[0].m_pDestRectF->Offset(r1,r2);
								 break;
							case DCAO_OR: 
							case DCAO_XOR: 
							case DCAO_AND:
							case DCAO_TORIGHT: 
							case DCAO_TOLEFT: 
							case DCAO_MODULO: 
								break;
							case DCAO_CENTER:
								m_Parameters[0].m_pDestRectF->X=(r1-r2)/2;	
								break;
							}
						}
						break;
					case DCPT_DESTPOINT:
						switch(m_Parameters[1].dwParamType&DCPT_TYPEMASK)
						{
						case DCPT_RECT:
							m_Parameters[0].m_pDestPointF->X=m_Parameters[1].m_pRectF->X;
							m_Parameters[0].m_pDestPointF->Y=m_Parameters[1].m_pRectF->Y;
							switch(m_Parameters[3].dwParamType&DCPT_TYPEMASK)
							{
							case DCPT_RECT:
								switch(m_Parameters[2].m_dword)
								{
								case DCAO_PLUS:
									m_Parameters[0].m_pDestPointF->X+=m_Parameters[3].m_pRectF->X;
									m_Parameters[0].m_pDestPointF->Y+=m_Parameters[3].m_pRectF->Y;
									break;
								case DCAO_MINUS: 
									m_Parameters[0].m_pDestPointF->X-=m_Parameters[3].m_pRectF->X;
									m_Parameters[0].m_pDestPointF->Y-=m_Parameters[3].m_pRectF->Y;
									break;
								case DCAO_CENTER: 
									m_Parameters[0].m_pDestPointF->X=m_Parameters[1].m_pRectF->X+((m_Parameters[1].m_pRectF->Width-m_Parameters[3].m_pRectF->Width)/2);
									m_Parameters[0].m_pDestPointF->Y=m_Parameters[1].m_pRectF->Y+((m_Parameters[1].m_pRectF->Height-m_Parameters[3].m_pRectF->Height)/2);
									break;
								}
								break;
							case DCPT_POINT:
								switch(m_Parameters[2].m_dword)
								{
								case DCAO_PLUS: 
									m_Parameters[0].m_pDestPointF->X+=m_Parameters[3].m_pPointF->X;
									m_Parameters[0].m_pDestPointF->Y+=m_Parameters[3].m_pPointF->Y;
									break;
								case DCAO_MINUS: 
									m_Parameters[0].m_pDestPointF->X-=m_Parameters[3].m_pPointF->X;
									m_Parameters[0].m_pDestPointF->Y-=m_Parameters[3].m_pPointF->Y;
									break;
								case DCAO_CENTER:
									m_Parameters[0].m_pDestPointF->X=m_Parameters[3].m_pPointF->X+m_Parameters[1].m_pRectF->Width/2;
									m_Parameters[0].m_pDestPointF->Y=m_Parameters[3].m_pPointF->Y+m_Parameters[1].m_pRectF->Height/2;
									break;
								case DCAO_OR: 
								case DCAO_XOR: 
								case DCAO_AND:
								case DCAO_TORIGHT: 
								case DCAO_TOLEFT: 
								case DCAO_MODULO: 
									break;
								}
								break;
							default:
								switch(m_Parameters[2].m_dword)
								{
								case DCAO_PLUS: 
									m_Parameters[0].m_pDestPointF->X+=r2;
									m_Parameters[0].m_pDestPointF->Y+=r2;
									break;
								case DCAO_MINUS: 
									m_Parameters[0].m_pDestPointF->X-=r2;
									m_Parameters[0].m_pDestPointF->Y-=r2;
									break;
								case DCAO_CENTER:
									m_Parameters[0].m_pDestPointF->X=r2+m_Parameters[1].m_pPointF->X+m_Parameters[1].m_pRectF->Width/2;
									m_Parameters[0].m_pDestPointF->Y=r2+m_Parameters[1].m_pPointF->Y+m_Parameters[1].m_pRectF->Height/2;
									break;
								case DCAO_DIV: 
								case DCAO_MUL: 
								case DCAO_OR: 
								case DCAO_XOR: 
								case DCAO_AND:
								case DCAO_TORIGHT: 
								case DCAO_TOLEFT: 
								case DCAO_MODULO: 
									break;
								}
								break;
							}
							break;
						case DCPT_POINT:
							*m_Parameters[0].m_pDestPointF=*m_Parameters[1].m_pPointF;
							switch(m_Parameters[3].dwParamType&DCPT_TYPEMASK)
							{
							case DCPT_RECT:
								switch(m_Parameters[2].m_dword)
								{
								case DCAO_PLUS: 
									m_Parameters[0].m_pDestPointF->X+=m_Parameters[3].m_pRectF->X;
									m_Parameters[0].m_pDestPointF->Y+=m_Parameters[3].m_pRectF->Y;
									break;
								case DCAO_MINUS: 
									m_Parameters[0].m_pDestPointF->X-=m_Parameters[3].m_pRectF->X;
									m_Parameters[0].m_pDestPointF->Y-=m_Parameters[3].m_pRectF->Y;
									break;
								case DCAO_CENTER:
									m_Parameters[0].m_pDestPointF->X-=m_Parameters[3].m_pRectF->X/2;	
									m_Parameters[0].m_pDestPointF->Y-=m_Parameters[3].m_pRectF->Y/2;	
									break;
								}
								break;
							case DCPT_POINT:
								switch(m_Parameters[2].m_dword)
								{
								case DCAO_PLUS: 
									m_Parameters[0].m_pDestPointF->X+=m_Parameters[3].m_pPointF->X;
									m_Parameters[0].m_pDestPointF->Y+=m_Parameters[3].m_pPointF->Y;
									break;
								case DCAO_MINUS: 
									m_Parameters[0].m_pDestPointF->X-=m_Parameters[3].m_pPointF->X;
									m_Parameters[0].m_pDestPointF->Y-=m_Parameters[3].m_pPointF->Y;
									break;
								case DCAO_CENTER:
									m_Parameters[0].m_pDestPointF->X=(m_Parameters[3].m_pPointF->X-m_Parameters[1].m_pPointF->X)/2;	
									m_Parameters[0].m_pDestPointF->Y=(m_Parameters[3].m_pPointF->Y-m_Parameters[1].m_pPointF->Y)/2;	
									break;
								}
								break;
							default:
								switch(m_Parameters[2].m_dword)
								{
								case DCAO_PLUS: 
									m_Parameters[0].m_pDestPointF->X+=r2;
									m_Parameters[0].m_pDestPointF->Y+=r2;
									break;
								case DCAO_MINUS: 
									m_Parameters[0].m_pDestRectF->X-=r2;
									m_Parameters[0].m_pDestRectF->Y-=r2;
									break;
								}
								break;
							}
							break;
						default:
							switch(m_Parameters[2].m_dword)
							{
							case DCAO_PLUS:
								m_Parameters[0].m_pDestPointF->X+=r1;
								m_Parameters[0].m_pDestPointF->Y+=r2;
								break;
							case DCAO_MINUS:
								m_Parameters[0].m_pDestPointF->X-=r1;
								m_Parameters[0].m_pDestPointF->Y-=r2;
								break;
							case DCAO_MUL:
								m_Parameters[0].m_pDestPointF->X*=r1;
								m_Parameters[0].m_pDestPointF->Y*=r2;
								break;
							case DCAO_DIV:
								if (r1!=0) m_Parameters[0].m_pDestPointF->X/=r1;
								if (r2!=0) m_Parameters[0].m_pDestPointF->Y/=r2;
								break;
							}
						}
						break;
					case DCPT_DESTCOLOR:
						{
							switch(m_Parameters[2].m_dword)
							{
							case DCAO_PLUS:
								m_Parameters[0].m_pDestColor->SetValue((ARGB)(i1+i2));
								break;
							case DCAO_MINUS: 
								m_Parameters[0].m_pDestColor->SetValue((ARGB)(i1-i2));
								break;
							case DCAO_MUL:
								m_Parameters[0].m_pDestColor->SetValue((ARGB)(i1*i2));
								break;
							case DCAO_DIV:
								if (i2!=0) m_Parameters[0].m_pDestColor->SetValue((ARGB)(i1/i2));
								break;
							case DCAO_OR: 
								m_Parameters[0].m_pDestColor->SetValue((ARGB)(i1|i2));
								break;
							case DCAO_XOR:
								m_Parameters[0].m_pDestColor->SetValue((ARGB)(i1^i2));
								break;
							case DCAO_AND:
								m_Parameters[0].m_pDestColor->SetValue((ARGB)(i1&i2));
								break;
							case DCAO_TORIGHT:
								m_Parameters[0].m_pDestColor->SetValue((ARGB)(i1>>i2));
								break;
							case DCAO_TOLEFT: 
								m_Parameters[0].m_pDestColor->SetValue((ARGB)(i1<<i2));
								break;
							case DCAO_MODULO: 
								m_Parameters[0].m_pDestColor->SetValue((ARGB)(i1%i2));
								break;
							}
						}
						break;
					case DCPT_DESTMATRIX:
						{
							switch(m_Parameters[2].m_dword)
							{
							case DCAO_PLUS: break;
							case DCAO_MINUS: break;
							case DCAO_MUL: break;
							case DCAO_DIV: break;
							case DCAO_OR: break;
							case DCAO_XOR: break;
							case DCAO_AND: break;
							case DCAO_TORIGHT: break;
							case DCAO_TOLEFT: break;
							case DCAO_MODULO: break;
							}
						}
						break;
					case DCPT_DESTINTEGER:
						{
							switch(m_Parameters[2].m_dword)
							{
							case DCAO_PLUS:		*m_Parameters[0].m_pDestInt=i1+i2;	break;
							case DCAO_MINUS:	*m_Parameters[0].m_pDestInt=i1-i2;	break;
							case DCAO_MUL: 		*m_Parameters[0].m_pDestInt=i1*i2;	break;
							case DCAO_DIV:
								if (i2!=0)		*m_Parameters[0].m_pDestInt=i1/i2;	break;
							case DCAO_OR: 		*m_Parameters[0].m_pDestInt=i1|i2;	break;
							case DCAO_XOR: 		*m_Parameters[0].m_pDestInt=i1^i2;	break;
							case DCAO_AND: 		*m_Parameters[0].m_pDestInt=i1&i2;	break;
							case DCAO_TORIGHT: 	*m_Parameters[0].m_pDestInt=i1>>i2;	break;
							case DCAO_TOLEFT: 	*m_Parameters[0].m_pDestInt=i1<<i2;	break;
							case DCAO_MODULO: 	*m_Parameters[0].m_pDestInt=i1%i2;	break;
							case DCAO_CENTER:	*m_Parameters[0].m_pDestInt=(i1+i2)/2;	break;
							}
						}
						break;
				default: 
					break;
				}
			}
			break;
		case DCUT_MATH://LeftOp,MathFunction,Operand1[,Operand2[,Operand3[,Operand4]]]
			{
				REAL r1=0,r2=0;
				INT i1=0,i2=0;
				if (m_NParams>2)
					switch(m_Parameters[2].dwParamType&DCPT_TYPEMASK)
					{
					case DCPT_RECTX:
					case DCPT_RECTY:
					case DCPT_RECTH:
					case DCPT_RECTW:
					case DCPT_POINTX:
					case DCPT_POINTY:
					case DCPT_REAL:
						i1=(INT)(r1=m_Parameters[2].m_real);
						break;
					case DCPT_COLOR:
						r1=(REAL)(i1=m_Parameters[2].m_pColor->GetValue());
						break;
					case DCPT_STRING:
						i1=atoi(*m_Parameters[2].m_pCString);
						r1=(REAL)atof(*m_Parameters[2].m_pCString);
						break;
					case DCPT_INTEGER:
					case DCPT_FLAG:
						r1=(REAL)(i1=m_Parameters[2].m_int);
						break;
					}
				if (m_NParams>3)
					switch(m_Parameters[3].dwParamType&DCPT_TYPEMASK)
					{
					case DCPT_RECTX:
					case DCPT_RECTY:
					case DCPT_RECTH:
					case DCPT_RECTW:
					case DCPT_POINTX:
					case DCPT_POINTY:
					case DCPT_REAL:
						i2=(INT)(r2=m_Parameters[3].m_real);
						break;
					case DCPT_COLOR:
						r2=(REAL)(i2=m_Parameters[3].m_pColor->GetValue());
						break;
					case DCPT_STRING:
						i2=atoi(*m_Parameters[3].m_pCString);
						r2=(REAL)atof(*m_Parameters[3].m_pCString);
						break;
					case DCPT_INTEGER:
					case DCPT_FLAG:
						r2=(REAL)(i2=m_Parameters[3].m_int);
						break;
					}
				DCParamType outType=DCPT_NONE;
				switch(m_Parameters[0].dwParamType&DCPT_TYPEMASK)
				{
				case DCPT_DESTREAL:
				case DCPT_DESTRECTX:
				case DCPT_DESTRECTY:
				case DCPT_DESTRECTW:
				case DCPT_DESTRECTH:
				case DCPT_DESTPOINTX:
				case DCPT_DESTPOINTY:
					if (m_Parameters[0].m_pDestReal) outType=DCPT_DESTREAL;
					break;
				case DCPT_DESTINTEGER:
				case DCPT_DESTCOLOR:
					if (m_Parameters[0].m_pDestInt) outType=DCPT_DESTINTEGER;
					break;
				case DCPT_DESTSTRING:
					if (m_Parameters[0].m_pDestCString) outType=DCPT_DESTSTRING;
					break;
				case DCPT_DESTRECT:
					if (m_Parameters[0].m_pDestRectF) outType=DCPT_DESTRECT;
					break;
				case DCPT_DESTPOINT:
					if (m_Parameters[0].m_pDestPointF) outType=DCPT_DESTPOINT;
					break;
				}

				switch(m_Parameters[1].m_dword)
				{
				case DCMF_NONE://
					break;
				case DCMF_ABS://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=abs(i1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)abs(r1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%d",abs(i1));
					else
					if (outType==DCPT_DESTPOINT && (m_Parameters[2].dwParamType&DCPT_TYPEMASK)==DCPT_POINT)
					{
						m_Parameters[0].m_pDestPointF->X=(REAL)abs(m_Parameters[2].m_pPointF->X);
						m_Parameters[0].m_pDestPointF->Y=(REAL)abs(m_Parameters[2].m_pPointF->Y);
					}
					else
					if (outType==DCPT_DESTPOINT && (m_Parameters[2].dwParamType&DCPT_TYPEMASK)==DCPT_RECT)
					{
						m_Parameters[0].m_pDestPointF->X=(REAL)abs(m_Parameters[2].m_pRectF->X);
						m_Parameters[0].m_pDestPointF->Y=(REAL)abs(m_Parameters[2].m_pRectF->Y);
					}
					else
					if (outType==DCPT_DESTRECT && (m_Parameters[2].dwParamType&DCPT_TYPEMASK)==DCPT_RECT)
					{
						m_Parameters[0].m_pDestRectF->X=(REAL)abs(m_Parameters[2].m_pRectF->X);
						m_Parameters[0].m_pDestRectF->Y=(REAL)abs(m_Parameters[2].m_pRectF->Y);
						m_Parameters[0].m_pDestRectF->Width=(REAL)abs(m_Parameters[2].m_pRectF->Width);
						m_Parameters[0].m_pDestRectF->Height=(REAL)abs(m_Parameters[2].m_pRectF->Height);
					}
					break;
				case DCMF_ACOS://
					if (r1>=-1 && r1<=1)
					{
						if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)acos(r1);
						else
						if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)acos(r1);
						else
						if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",acos(r1));
					}
					break;
				case DCMF_ASIN://
					if (r1>=-1 && r1<=1)
					{
						if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)asin(r1);
						else
						if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)asin(r1);
						else
						if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",asin(r1));
					}
					break;
				case DCMF_ATAN://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)atan(r1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)atan(r1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",atan(r1));
					break;
				case DCMF_ATAN2://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)atan2(r1,r2);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)atan2(r1,r2);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",atan2(r1,r2));
					break;
				case DCMF_BESSEL_j0://	
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_j0(r1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_j0(r1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",_j0(r1));
					break;
				case DCMF_BESSEL_j1://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_j1(r1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_j1(r1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",_j1(r1));
					break;
				case DCMF_BESSEL_jn://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_jn(i1,r2);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_jn(i1,r2);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",_jn(i1,r2));
					break;
				case DCMF_BESSEL_y0://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_y0(r1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_y0(r1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",_y0(r1));
					break;
				case DCMF_BESSEL_y1://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_y1(r1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_y1(r1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",_y1(r1));
					break;
				case DCMF_BESSEL_yn://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_yn(i1,r2);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_yn(i1,r2);
					break;
				case DCMF_CABS://
					{
					   struct _complex number = {r1,r2};
						if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_cabs(number);
						else
						if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_cabs(number);
						else
						if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",_cabs(number));
					}
					break;
				case DCMF_CEIL://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)ceil(r1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)ceil(r1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",ceil(r1));
					else
					if (outType==DCPT_DESTPOINT && (m_Parameters[2].dwParamType&DCPT_TYPEMASK)==DCPT_POINT)
					{
						m_Parameters[0].m_pDestPointF->X=(REAL)ceil(m_Parameters[2].m_pPointF->X);
						m_Parameters[0].m_pDestPointF->Y=(REAL)ceil(m_Parameters[2].m_pPointF->Y);
					}
					else
					if (outType==DCPT_DESTPOINT && (m_Parameters[2].dwParamType&DCPT_TYPEMASK)==DCPT_RECT)
					{
						m_Parameters[0].m_pDestPointF->X=(REAL)ceil(m_Parameters[2].m_pRectF->X);
						m_Parameters[0].m_pDestPointF->Y=(REAL)ceil(m_Parameters[2].m_pRectF->Y);
					}
					else
					if (outType==DCPT_DESTRECT && (m_Parameters[2].dwParamType&DCPT_TYPEMASK)==DCPT_RECT)
					{
						m_Parameters[0].m_pDestRectF->X=(REAL)ceil(m_Parameters[2].m_pRectF->X);
						m_Parameters[0].m_pDestRectF->Y=(REAL)ceil(m_Parameters[2].m_pRectF->Y);
						m_Parameters[0].m_pDestRectF->Width=(REAL)ceil(m_Parameters[2].m_pRectF->Width);
						m_Parameters[0].m_pDestRectF->Height=(REAL)ceil(m_Parameters[2].m_pRectF->Height);
					}
					break;
				case DCMF_CHGSIGN://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_chgsign(r1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_chgsign(r1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",_chgsign(r1));
					break;
				case DCMF_CLEAR87://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_clear87();
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_clear87();
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%d",_clear87());
					break;
				case DCMF_CLEARFP://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_clearfp();
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_clearfp();
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%d",_clearfp());
					break;
				case DCMF_CONTROL87://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_control87(i1,i2);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_control87(i1,i2);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%d",_control87(i1,i2));
					break;
				case DCMF_CONTROLFP://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_controlfp(i1,i2);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_controlfp(i1,i2);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%d",_controlfp(i1,i2));
					break;
				case DCMF_COPYSIGN://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_copysign(r1,r2);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_copysign(r1,r2);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",_copysign(r1,r2));
					break;
				case DCMF_COS://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)cos(r1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)cos(r1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",cos(r1));
					break;
				case DCMF_COSH://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)cosh(r1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)cosh(r1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",cosh(r1));
					break;
				case DCMF_DIVQUOT://
					{
						div_t retdiv;
						retdiv=div(i1,i2);
						if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)retdiv.quot;
						else
						if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)retdiv.quot;
						else
						if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%d",retdiv.quot);
					}
					break;
				case DCMF_DIVREM://
					{
						div_t retdiv;
						retdiv=div(i1,i2);
						if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)retdiv.rem;
						else
						if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)retdiv.rem;
						else
						if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%d",retdiv.rem);
					}
					break;
				case DCMF_EXP://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)exp(r1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)exp(r1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",exp(r1));
					break;
				case DCMF_FABS://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)fabs(r1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)fabs(r1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",fabs(r1));
					break;
				case DCMF_FINITE://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_finite(r1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_finite(r1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%d",_finite(r1));
					else
					if (outType==DCPT_DESTPOINT && (m_Parameters[2].dwParamType&DCPT_TYPEMASK)==DCPT_POINT)
					{
						m_Parameters[0].m_pDestPointF->X=(REAL)_finite(m_Parameters[2].m_pPointF->X);
						m_Parameters[0].m_pDestPointF->Y=(REAL)_finite(m_Parameters[2].m_pPointF->Y);
					}
					else
					if (outType==DCPT_DESTPOINT && (m_Parameters[2].dwParamType&DCPT_TYPEMASK)==DCPT_RECT)
					{
						m_Parameters[0].m_pDestPointF->X=(REAL)_finite(m_Parameters[2].m_pRectF->X);
						m_Parameters[0].m_pDestPointF->Y=(REAL)_finite(m_Parameters[2].m_pRectF->Y);
					}
					else
					if (outType==DCPT_DESTRECT && (m_Parameters[2].dwParamType&DCPT_TYPEMASK)==DCPT_RECT)
					{
						m_Parameters[0].m_pDestRectF->X=(REAL)_finite(m_Parameters[2].m_pRectF->X);
						m_Parameters[0].m_pDestRectF->Y=(REAL)_finite(m_Parameters[2].m_pRectF->Y);
						m_Parameters[0].m_pDestRectF->Width=(REAL)_finite(m_Parameters[2].m_pRectF->Width);
						m_Parameters[0].m_pDestRectF->Height=(REAL)_finite(m_Parameters[2].m_pRectF->Height);
					}
					break;
				case DCMF_FLOOR://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)floor(r1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)floor(r1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",floor(r1));
					else
					if (outType==DCPT_DESTPOINT && (m_Parameters[2].dwParamType&DCPT_TYPEMASK)==DCPT_POINT)
					{
						m_Parameters[0].m_pDestPointF->X=(REAL)floor(m_Parameters[2].m_pPointF->X);
						m_Parameters[0].m_pDestPointF->Y=(REAL)floor(m_Parameters[2].m_pPointF->Y);
					}
					else
					if (outType==DCPT_DESTPOINT && (m_Parameters[2].dwParamType&DCPT_TYPEMASK)==DCPT_RECT)
					{
						m_Parameters[0].m_pDestPointF->X=(REAL)floor(m_Parameters[2].m_pRectF->X);
						m_Parameters[0].m_pDestPointF->Y=(REAL)floor(m_Parameters[2].m_pRectF->Y);
					}
					else
					if (outType==DCPT_DESTRECT && (m_Parameters[2].dwParamType&DCPT_TYPEMASK)==DCPT_RECT)
					{
						m_Parameters[0].m_pDestRectF->X=(REAL)floor(m_Parameters[2].m_pRectF->X);
						m_Parameters[0].m_pDestRectF->Y=(REAL)floor(m_Parameters[2].m_pRectF->Y);
						m_Parameters[0].m_pDestRectF->Width=(REAL)floor(m_Parameters[2].m_pRectF->Width);
						m_Parameters[0].m_pDestRectF->Height=(REAL)floor(m_Parameters[2].m_pRectF->Height);
					}
					break;
				case DCMF_FMOD://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)fmod(r1,r2);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)fmod(r1,r2);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",fmod(r1,r2));
					break;
				case DCMF_FPCLASS://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_fpclass(r1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_fpclass(r1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%d",_fpclass(r1));
					break;
				case DCMF_FPRESET://
					_fpreset();
					break;
				case DCMF_FREXPMANT://
					{
						int tmpres=0;
						if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)frexp(r1,&tmpres);
						else
						if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)frexp(r1,&tmpres);
						else
						if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",frexp(r1,&tmpres));
					}
					break;
				case DCMF_FREXPEXP://
					{
						int tmpres=0;
						frexp(r1,&tmpres);
						if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)tmpres;
						else
						if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)tmpres;
						else
						if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%d",tmpres);
					}
					break;
				case DCMF_HYPOT://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_hypot(r1,r2);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_hypot(r1,r2);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",_hypot(r1,r2));
					break;
				case DCMF_ISNAN://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_isnan(r1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_isnan(r1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%d",_isnan(r1));
					break;
				case DCMF_LABS://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)labs(i1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)labs(i1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%ld",labs(i1));
					else
					if (outType==DCPT_DESTPOINT && (m_Parameters[2].dwParamType&DCPT_TYPEMASK)==DCPT_POINT)
					{
						m_Parameters[0].m_pDestPointF->X=(REAL)labs((long)m_Parameters[2].m_pPointF->X);
						m_Parameters[0].m_pDestPointF->Y=(REAL)labs((long)m_Parameters[2].m_pPointF->Y);
					}
					else
					if (outType==DCPT_DESTPOINT && (m_Parameters[2].dwParamType&DCPT_TYPEMASK)==DCPT_RECT)
					{
						m_Parameters[0].m_pDestPointF->X=(REAL)labs((long)m_Parameters[2].m_pRectF->X);
						m_Parameters[0].m_pDestPointF->Y=(REAL)labs((long)m_Parameters[2].m_pRectF->Y);
					}
					else
					if (outType==DCPT_DESTRECT && (m_Parameters[2].dwParamType&DCPT_TYPEMASK)==DCPT_RECT)
					{
						m_Parameters[0].m_pDestRectF->X=(REAL)labs((long)m_Parameters[2].m_pRectF->X);
						m_Parameters[0].m_pDestRectF->Y=(REAL)labs((long)m_Parameters[2].m_pRectF->Y);
						m_Parameters[0].m_pDestRectF->Width=(REAL)labs((long)m_Parameters[2].m_pRectF->Width);
						m_Parameters[0].m_pDestRectF->Height=(REAL)labs((long)m_Parameters[2].m_pRectF->Height);
					}
					break;
				case DCMF_LDEXP://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)ldexp(r1,i2);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)ldexp(r1,i2);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",ldexp(r1,i2));
					break;
				case DCMF_LDIVQUOT://
					{
						ldiv_t retdiv=ldiv(i1,i2);
						if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)retdiv.quot;
						else
						if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)retdiv.quot;
						else
						if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%ld",retdiv.quot);
					}
					break;
				case DCMF_LDIVREM://
					{
						ldiv_t retdiv=ldiv(i1,i2);
						if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)retdiv.rem;
						else
						if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)retdiv.rem;
						else
						if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%ld",retdiv.rem);
					}
					break;
				case DCMF_LOG://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)log(r1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)log(r1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",log(r1));
					break;
				case DCMF_LOG10://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)log10(r1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)log10(r1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",log10(r1));
					break;
				case DCMF_LOGB://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_logb(r1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_logb(r1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",_logb(r1));
					break;
				case DCMF_LROTL://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_lrotl(i1,i2);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_lrotl(i1,i2);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%d",_lrotl(i1,i2));
					break;
				case DCMF_LROTR://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_lrotr(i1,i2);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_lrotr(i1,i2);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%d",_lrotr(i1,i2));
					break;
				case DCMF_MAX://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)((i1>i2)?i1:i2);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)((r1>r2)?r1:r2);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",((r1>r2)?r1:r2));
					break;
				case DCMF_MIN://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)((i1<i2)?i1:i2);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)((r1<r2)?r1:r2);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",((r1<r2)?r1:r2));
					break;
				case DCMF_MODFFLOAT://
					{
						REAL tmpres=0;
						if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)modf(r1,&tmpres);
						else
						if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)modf(r1,&tmpres);
						else
						if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",modf(r1,&tmpres));
					}
				case DCMF_MODFINT://
					{
						REAL tmpres=0;
						modf(r1,&tmpres);	
						if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)tmpres;
						else
						if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)tmpres;
						else
						if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",tmpres);
					}
					break;
				case DCMF_NEXTAFTER://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_nextafter(r1,r2);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_nextafter(r1,r2);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",_nextafter(r1,r2));
					break;
				case DCMF_POW://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)pow(r1,r2);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)pow(r1,r2);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",pow(r1,r2));
					break;
				case DCMF_RAND://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)rand();
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)rand();
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%d",rand());
					break;
				case DCMF_ROTL://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_rotl(i1,i2);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_rotl(i1,i2);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%d",_rotl(i1,i2));
					break;
				case DCMF_ROTR://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_rotr(i1,i2);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_rotr(i1,i2);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%d",_rotr(i1,i2));
					break;
				case DCMF_SCALB://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_scalb(r1,i2);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_scalb(r1,i2);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",_scalb(r1,i2));
					break;
				case DCMF_SIN://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)sin(r1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)sin(r1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",sin(r1));
					break;
				case DCMF_SINH://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)sinh(r1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)sinh(r1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",sinh(r1));
					break;
				case DCMF_SQRT://
					if (r1>=0)
					{
						if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)sqrt(r1);
						else
						if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)sqrt(r1);
						else
						if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",sqrt(r1));
					}
					break;
				case DCMF_SRAND://
					srand(i1);
					break;
				case DCMF_STATUS87://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_status87();
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_status87();
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%d",_status87());
					break;
				case DCMF_STATUSFP://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)_statusfp();
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)_statusfp();
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%d",_statusfp());
					break;
				case DCMF_STRTOD://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=i1;
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=r1;
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",r1);
					break;
				case DCMF_TAN://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)tan(r1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)tan(r1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",tan(r1));
					break;
				case DCMF_TANH://
					if (outType==DCPT_DESTINTEGER)	*m_Parameters[0].m_pDestInt=(INT)tanh(r1);
					else
					if (outType==DCPT_DESTREAL)	*m_Parameters[0].m_pDestReal=(REAL)tanh(r1);
					else
					if (outType==DCPT_DESTSTRING)	m_Parameters[0].m_pDestCString->Format("%g",tanh(r1));
					break;
				}
			}
			break;
		case DCUT_RECTCONTAINS:	//DestInt,Rect,Rect|Point
			if (m_NParams==3 && m_Parameters)
			{
				switch(m_Parameters[2].dwParamType&DCPT_TYPEMASK)
				{
				case DCPT_RECT:
					*m_Parameters[0].m_pDestInt=m_Parameters[1].m_pRectF->Contains(*m_Parameters[2].m_pRectF);
					break;
				case DCPT_POINT:
					*m_Parameters[0].m_pDestInt=m_Parameters[1].m_pRectF->Contains(*m_Parameters[2].m_pPointF);
					break;
				}
			}
			break;
		case DCUT_RECTEQUALS:	//DestInt,Rect,Rect
			if (m_NParams==3 && m_Parameters)
				*m_Parameters[0].m_pDestInt=m_Parameters[1].m_pRectF->Equals(*m_Parameters[2].m_pRectF);
			break;
		case DCUT_RECTGETBOTTOM:	//DestReal,Rect
			if (m_NParams==2 && m_Parameters)
				*m_Parameters[0].m_pDestReal=m_Parameters[1].m_pRectF->GetBottom();
			break;
		case DCUT_RECTGETRIGHT:	//DestReal,Rect
			if (m_NParams==2 && m_Parameters)
				*m_Parameters[0].m_pDestReal=m_Parameters[1].m_pRectF->GetRight();
			break;
		case DCUT_RECTGETLOCATION:	//DestPoint,Rect
			if (m_NParams==2 && m_Parameters)
				m_Parameters[1].m_pRectF->GetLocation(m_Parameters[0].m_pDestPointF);
			break;
		case DCUT_RECTGETSIZE:	//DestPoint,Rect
			if (m_NParams==2 && m_Parameters)
				m_Parameters[1].m_pRectF->GetLocation(m_Parameters[0].m_pDestPointF);
			break;
		case DCUT_RECTINFLATE:	//Rect,Point
			if (m_NParams==2 && m_Parameters)
				m_Parameters[0].m_pRectF->Inflate(*m_Parameters[1].m_pPointF);
			break;
		case DCUT_RECTINTERSECT:	//Rect,Rect
			if (m_NParams==2 && m_Parameters)
				m_Parameters[0].m_pRectF->IntersectsWith(*m_Parameters[1].m_pRectF);
			break;
		case DCUT_RECTISEMPTYAREA:	//DestInt,Rect
			if (m_NParams==2 && m_Parameters)
				*m_Parameters[0].m_pDestInt=m_Parameters[1].m_pRectF->IsEmptyArea();
			break;
		case DCUT_RECTOFFSET:	//Rect,Point
			if (m_NParams==2 && m_Parameters)
				m_Parameters[0].m_pRectF->Offset(*m_Parameters[1].m_pPointF);
			break;
		case DCUT_RECTUNION:	//Rect,Rect
			if (m_NParams==2 && m_Parameters)
			{
				REAL right = max(m_Parameters[0].m_pRectF->GetRight(), m_Parameters[1].m_pRectF->GetRight());
				REAL bottom = max(m_Parameters[0].m_pRectF->GetBottom(), m_Parameters[1].m_pRectF->GetBottom());
				REAL left = min(m_Parameters[0].m_pRectF->GetLeft(), m_Parameters[1].m_pRectF->GetLeft());
				REAL top = min(m_Parameters[0].m_pRectF->GetTop(), m_Parameters[1].m_pRectF->GetTop());

				m_Parameters[0].m_pDestRectF->X = left;
				m_Parameters[0].m_pDestRectF->Y = top;
				m_Parameters[0].m_pDestRectF->Width = right - left;
				m_Parameters[0].m_pDestRectF->Height = bottom - top;
			}
			break;
		case DCUT_CLRGETALPHA:	//DestInt,Color
			if (m_NParams==2 && m_Parameters)	*m_Parameters[0].m_pDestInt=m_Parameters[1].m_pColor->GetAlpha();
			break;
		case DCUT_CLRGETRED:	//DestInt,Color
			if (m_NParams==2 && m_Parameters)	*m_Parameters[0].m_pDestInt=m_Parameters[1].m_pColor->GetRed();
			break;
		case DCUT_CLRGETGREEN:	//DestInt,Color
			if (m_NParams==2 && m_Parameters)	*m_Parameters[0].m_pDestInt=m_Parameters[1].m_pColor->GetGreen();
			break;
		case DCUT_CLRGETBLUE:	//DestInt,Color
			if (m_NParams==2 && m_Parameters)	*m_Parameters[0].m_pDestInt=m_Parameters[1].m_pColor->GetBlue();
			break;
		case DCUT_CLRSETALPHA:	//DestColor,Int
			if (m_NParams==2 && m_Parameters)	
				m_Parameters[0].m_pDestColor->SetValue(Color::MakeARGB(
				m_Parameters[1].m_int,
				m_Parameters[0].m_pColor->GetR(),
				m_Parameters[0].m_pColor->GetG(),
				m_Parameters[0].m_pColor->GetB()));
			break;
		case DCUT_CLRSETRED:	//DestColor,Int
			if (m_NParams==2 && m_Parameters)	
				m_Parameters[0].m_pDestColor->SetValue(Color::MakeARGB(
				m_Parameters[0].m_pColor->GetA(),
				m_Parameters[1].m_int,
				m_Parameters[0].m_pColor->GetG(),
				m_Parameters[0].m_pColor->GetB()));
			break;
		case DCUT_CLRSETGREEN:	//DestColor,Int
			if (m_NParams==2 && m_Parameters)	
				m_Parameters[0].m_pDestColor->SetValue(Color::MakeARGB(
				m_Parameters[0].m_pColor->GetA(),
				m_Parameters[0].m_pColor->GetR(),
				m_Parameters[1].m_int,
				m_Parameters[0].m_pColor->GetB()));
			break;
		case DCUT_CLRSETBLUE:	//DestColor,Int
			if (m_NParams==2 && m_Parameters)	
				m_Parameters[0].m_pDestColor->SetValue(Color::MakeARGB(
				m_Parameters[0].m_pColor->GetA(),
				m_Parameters[0].m_pColor->GetR(),
				m_Parameters[0].m_pColor->GetG(),
				m_Parameters[1].m_int));
			break;
		case DCUT_GETWINDOWRECT:	//DestRect,GUIObject
			if (m_NParams==2 && m_Parameters && m_Parameters[0].m_pDestRectF)
			{
				HWND tmpHWND=(pContext->m_CurDialogGPU && m_Parameters[1].m_Reference<(*pContext->m_CurDialogGPU)->m_NGPUNIT && pContext->m_CurDialogGPU[m_Parameters[1].m_Reference])?pContext->m_CurDialogGPU[m_Parameters[1].m_Reference]->UnitHWND:NULL;
				if (!tmpHWND) tmpHWND=::GetDesktopWindow();
				if (tmpHWND)
				{
					RECT re={0};
					::GetWindowRect(tmpHWND,&re);
					m_Parameters[0].m_pDestRectF->X=(REAL)re.left;
					m_Parameters[0].m_pDestRectF->Y=(REAL)re.top;
					m_Parameters[0].m_pDestRectF->Width=(REAL)(re.right-re.left);
					m_Parameters[0].m_pDestRectF->Height=(REAL)(re.bottom-re.top);
				}
			}
			break;
		case DCUT_GETCLIENTRECT:	//DestRect,GUIObject
			if (m_NParams==2 && m_Parameters && m_Parameters[0].m_pDestRectF)
			{
				HWND tmpHWND=(pContext->m_CurDialogGPU && m_Parameters[1].m_Reference<(*pContext->m_CurDialogGPU)->m_NGPUNIT && pContext->m_CurDialogGPU[m_Parameters[1].m_Reference])?pContext->m_CurDialogGPU[m_Parameters[1].m_Reference]->UnitHWND:NULL;
				if (!tmpHWND)
					if (pContext && pContext->m_CurHWND && m_Parameters[1].dwParamType==DCPT_NONE) tmpHWND=pContext->m_CurHWND;
						else tmpHWND=::GetDesktopWindow();
				if (tmpHWND)
				{
					RECT re={0};
					::GetClientRect(tmpHWND,&re);
					m_Parameters[0].m_pDestRectF->X=(REAL)re.left;
					m_Parameters[0].m_pDestRectF->Y=(REAL)re.top;
					m_Parameters[0].m_pDestRectF->Width=(REAL)(re.right-re.left);
					m_Parameters[0].m_pDestRectF->Height=(REAL)(re.bottom-re.top);
				}
			}
			break;
		case DCUT_SCRTOCL:	//DestRect,Rect|Point,GUIObject
		case DCUT_CLTOSCR:	//DestRect,Rect,GUIObject
			if (m_NParams==3 && m_Parameters && m_Parameters[0].m_pDestRectF)
			{
				HWND tmpHWND=(pContext->m_CurDialogGPU 
						&& m_Parameters[2].m_Reference<(*pContext->m_CurDialogGPU)->m_NGPUNIT && pContext->m_CurDialogGPU[m_Parameters[2].m_Reference])
						? pContext->m_CurDialogGPU[m_Parameters[2].m_Reference]->UnitHWND:NULL;
				if (!tmpHWND) tmpHWND=::GetDesktopWindow();
				if (tmpHWND)
				{
					POINT po={0};
					if ((m_Parameters[1].dwParamType&DCPT_TYPEMASK)==DCPT_POINT) 
					{
						po.x=(LONG)(m_Parameters[1].m_pPointF->X);
						po.y=(LONG)(m_Parameters[1].m_pPointF->Y);
					}
					else
					if ((m_Parameters[1].dwParamType&DCPT_TYPEMASK)==DCPT_RECT) 
					{
						po.x=(LONG)(m_Parameters[1].m_pRectF->X);
						po.y=(LONG)(m_Parameters[1].m_pRectF->Y);
					}

					if (m_Type==DCUT_CLTOSCR)
						::ClientToScreen(tmpHWND,&po);
						else
						if (m_Type==DCUT_SCRTOCL)
							::ScreenToClient(tmpHWND,&po);
					if ((m_Parameters[0].dwParamType&DCPT_TYPEMASK)==DCPT_DESTPOINT)
					{
						m_Parameters[0].m_pDestPointF->X=(REAL)po.x;
						m_Parameters[0].m_pDestPointF->Y=(REAL)po.y;
					}
					else
					if ((m_Parameters[0].dwParamType&DCPT_TYPEMASK)==DCPT_DESTRECT)
					{
						m_Parameters[0].m_pDestRectF->X=(REAL)po.x;
						m_Parameters[0].m_pDestRectF->Y=(REAL)po.y;
					}
				}
			}
			break;
		case DCUT_MOVEWINDOW: //GUIObject,Rect
			if (m_NParams==2 && m_Parameters && m_Parameters[0].m_pDestRectF)
			{
				HWND tmpHWND=(pContext->m_CurDialogGPU 
						&& m_Parameters[0].m_Reference<(*pContext->m_CurDialogGPU)->m_NGPUNIT && pContext->m_CurDialogGPU[m_Parameters[0].m_Reference])
						? pContext->m_CurDialogGPU[m_Parameters[0].m_Reference]->UnitHWND:NULL;
				if (tmpHWND)
				{
					RectF *pre=m_Parameters[1].m_pRectF;
					::MoveWindow(tmpHWND,(INT)pre->X,(INT)pre->Y,(INT)pre->Width,(INT)pre->Height,1);
				}
			}
			break;
		case DCUT_STRMID: //DestString,String,IntStart,IntLen
			if (m_NParams>=3 && m_Parameters && m_Parameters[0].m_pDestCString)
			{
				if (m_Parameters[0].m_pDestCString!=m_Parameters[1].m_pCString)
					*m_Parameters[0].m_pDestCString=*m_Parameters[1].m_pCString;
				if (m_NParams==3)
					m_Parameters[0].m_pDestCString->Mid(m_Parameters[2].m_int);
				else
					m_Parameters[0].m_pDestCString->Mid(m_Parameters[2].m_int,m_Parameters[3].m_int);
			}
			break;
		case DCUT_STRLEFT: //DestString,String,IntLen
			if (m_NParams==3 && m_Parameters && m_Parameters[0].m_pDestCString)
			{
				if (m_Parameters[0].m_pDestCString!=m_Parameters[1].m_pCString)
					*m_Parameters[0].m_pDestCString=*m_Parameters[1].m_pCString;
				m_Parameters[0].m_pDestCString->Left(m_Parameters[2].m_int);
			}
			break;
		case DCUT_STRRIGHT: //DestString,String,IntLen
			if (m_NParams==3 && m_Parameters && m_Parameters[0].m_pDestCString)
			{
				if (m_Parameters[0].m_pDestCString!=m_Parameters[1].m_pCString)
					*m_Parameters[0].m_pDestCString=*m_Parameters[1].m_pCString;
				m_Parameters[0].m_pDestCString->Right(m_Parameters[2].m_int);
			}
			break;
		case DCUT_STRFORMAT: //DestString,StrFormat,Variables
			if (m_NParams>=3 && m_Parameters && m_Parameters[0].m_pDestCString && m_Parameters[1].m_pCString)
			{
				*(m_Parameters[0].m_pDestCString)="";
				int curParam=2;
				char *tmpFormat=new char [35000];
				char *tmpOut=tmpFormat+m_Parameters[1].m_pCString->GetLength()+1000;
				char *resOut=tmpOut;
				char *tmppos=tmpFormat;
				*resOut=0;
				strcpy(tmpFormat,*(m_Parameters[1].m_pCString));
				while(*tmppos)
				{
					while(*tmppos && *tmppos!='%') *(tmpOut++)=*(tmppos++);
					*tmpOut=0;
					if (*tmppos=='%' && tmppos[1]=='%')
					{
						*(tmpOut++)=*(tmppos++);
						tmppos++;
						*tmpOut=0;
					}
					else
					if (*tmppos)
					{
						char *tmptmppos=tmppos+1;
						while(*tmptmppos && *tmptmppos!='%') tmptmppos++;
						char nextChar=*tmptmppos;
						*tmptmppos=0;
						switch(m_Parameters[curParam].dwParamType&DCPT_TYPEMASK)
						{
						case DCPT_RECTX:
						case DCPT_RECTY:
						case DCPT_RECTH:
						case DCPT_RECTW:
						case DCPT_POINTX:
						case DCPT_POINTY:
						case DCPT_REAL:
							tmpOut+=sprintf(tmpOut,tmppos,m_Parameters[curParam].m_real);
							break;
						case DCPT_COLOR:
							tmpOut+=sprintf(tmpOut,tmppos,m_Parameters[curParam].m_pColor->GetValue());
							break;
						case DCPT_STRING:
							tmpOut+=sprintf(tmpOut,tmppos,(LPCSTR)(*m_Parameters[curParam].m_pCString));
							break;
						case DCPT_INTEGER:
							tmpOut+=sprintf(tmpOut,tmppos,m_Parameters[curParam].m_int);
							break;
						case DCPT_FLAG:
							tmpOut+=sprintf(tmpOut,tmppos,m_Parameters[curParam].m_dword);
							break;
						default:
							while((*tmpOut=*(tmppos++))) tmpOut++;
							curParam--;
							break;
						}
						curParam++;
						*tmptmppos=nextChar;
						tmppos=tmptmppos;
					}
				}
				*(m_Parameters[0].m_pDestCString)=resOut;
				delete [] tmpFormat;
			}
			break;
		case DCUT_OBJSUB:	//GUIObject,Method
			if (m_NParams==2 && m_Parameters && pContext->m_CurDialogGPU 
				&& m_Parameters[0].m_Reference<(*pContext->m_CurDialogGPU)->m_NGPUNIT && pContext->m_CurDialogGPU[m_Parameters[0].m_Reference]
				)
			{
				pContext->m_CurDialogGPU[m_Parameters[0].m_Reference]->DoMethod(*m_Parameters[1].m_pCString,NULL);
			}
			break;
		case DCUT_OBJFN:	//DestString,GUIObject,Method
			if (m_NParams==3 && m_Parameters && m_Parameters[0].m_pDestCString && pContext->m_CurDialogGPU 
				&& m_Parameters[1].m_Reference<(*pContext->m_CurDialogGPU)->m_NGPUNIT && pContext->m_CurDialogGPU[m_Parameters[1].m_Reference]
				)
			{
				char *tmps=new char [50000];
				*tmps=0;
				pContext->m_CurDialogGPU[m_Parameters[1].m_Reference]->DoMethod(*m_Parameters[2].m_pCString,tmps);
				*m_Parameters[0].m_pDestCString=tmps;
				delete [] tmps;
			}
			break;
		case DCUT_CONTEXTSUB:	//ContextName,Method
			if (m_NParams==2 && m_Parameters && pContext)
			{
				CODContext *pc=pContext;
				if (*m_Parameters[0].m_pCString!="")
					pc=GPC.m_View->m_ODContextsArray->GetContext(*m_Parameters[0].m_pCString);
				
				if (pc && m_Parameters[1].m_pCString)
					pc->DoMethod(*m_Parameters[1].m_pCString,NULL);
			}
			break;
		case DCUT_CONTEXTFN:	//DestString,ContextName,Method
			if (m_NParams==3 && m_Parameters && pContext)
			{
				char *tmps=new char [50000];
				*tmps=0;
				CODContext *pc=pContext;
				if (*m_Parameters[1].m_pCString!="")
					pc=GPC.m_View->m_ODContextsArray->GetContext(*m_Parameters[1].m_pCString);
				
				if (pc && m_Parameters[1].m_pCString)
					pc->DoMethod(*m_Parameters[2].m_pCString,tmps);
				*m_Parameters[0].m_pDestCString=tmps;
				delete [] tmps;
			}
			break;
		case DCUT_SYSTEMSUB:	//Method
			if (m_NParams==1 && m_Parameters)
			{
				CDlgViewSystemMethods::DoMethod(*m_Parameters[0].m_pCString,NULL);
			}
			break;
		case DCUT_SYSTEMFN:	//DestString,Method
			if (m_NParams==2 && m_Parameters)
			{
				char *tmps=new char [50000];
				*tmps=0;
				CDlgViewSystemMethods::DoMethod(*m_Parameters[1].m_pCString,tmps);
				*m_Parameters[0].m_pDestCString=tmps;
				delete [] tmps;
			}
			break;
		case DCUT_GETFIELD:	//DestString,String,nField,Delimiter
			if (m_NParams==4 && m_Parameters && m_Parameters[0].m_pDestCString && m_Parameters[1].m_pCString && m_Parameters[2].m_int>0)
			{
				CString tmpCS;
				if ((m_Parameters[3].dwParamType&DCPT_TYPEMASK)==DCPT_STRING) tmpCS=*m_Parameters[3].m_pCString;
				else
				{
					tmpCS=" ";
					tmpCS.SetAt(0,(char)((m_Parameters[3].m_dword)%0xFF));
				}
				*m_Parameters[0].m_pDestCString=ExtractField(*m_Parameters[1].m_pCString,m_Parameters[2].m_int,tmpCS);
			}
			break;
		case DCUT_SETFIELD:	//DestString,Value,nField,Delimiter
			if (m_NParams==4 && m_Parameters && m_Parameters[0].m_pDestCString)
			{
				CString tmpCS;
				CString tmpDestCS;
				if ((m_Parameters[3].dwParamType&DCPT_TYPEMASK)==DCPT_STRING) tmpCS=*m_Parameters[3].m_pCString;
				else
				{
					tmpCS=" ";
					tmpCS.SetAt(0,(char)((m_Parameters[3].m_dword)%0xFF));
				}

				switch(m_Parameters[1].dwParamType&DCPT_TYPEMASK)
				{
				case DCPT_RECTX:
				case DCPT_RECTY:
				case DCPT_RECTH:
				case DCPT_RECTW:
				case DCPT_POINTX:
				case DCPT_POINTY:
				case DCPT_REAL:
					tmpDestCS.Format("%g",m_Parameters[1].m_real);
					break;
				case DCPT_COLOR:
						tmpDestCS.Format("%d,%d,%d,%d",
							m_Parameters[1].m_pColor->GetRed(),	m_Parameters[1].m_pColor->GetGreen(),
							m_Parameters[1].m_pColor->GetBlue(),m_Parameters[1].m_pColor->GetAlpha());
					break;
				case DCPT_RECT:
						tmpDestCS.Format("%g,%g,%g,%g",
							m_Parameters[1].m_pRectF->X,		m_Parameters[1].m_pRectF->Y,
							m_Parameters[1].m_pRectF->Width,	m_Parameters[1].m_pRectF->Height);
					break;
				case DCPT_POINT:
						tmpDestCS.Format("%g,%g",m_Parameters[1].m_pPointF->X,m_Parameters[1].m_pPointF->Y);
					break;
				case DCPT_STRING:
						tmpDestCS=*m_Parameters[1].m_pCString;
					break;
				case DCPT_MATRIX:
						{
							REAL rea[10]={0};
							m_Parameters[1].m_pMatrix->m_Matrix->GetElements(rea);
							tmpDestCS.Format("%g,%g,%g,%g,%g,%g",rea[0],rea[1],rea[2],rea[3],rea[4],rea[5]);
						}
					break;
				case DCPT_INTEGER:
				case DCPT_FLAG:
						tmpDestCS.Format("%d",m_Parameters[1].m_dword);
					break;
				}
				SetMVField(*m_Parameters[0].m_pDestCString,	tmpDestCS, m_Parameters[2].m_int, -1, 0, tmpCS);
			}
			break;
		case DCUT_SETMATRIXELEMENT:	//DestMatrix,nElement,Value
			if (m_NParams==3 && m_Parameters && m_Parameters[0].m_pDestMatrix && m_Parameters[0].m_pDestMatrix->m_Matrix)
			{
				if (m_Parameters[1].m_int>=0 && m_Parameters[1].m_int<=5)
				{
					REAL m[10];
					m_Parameters[0].m_pDestMatrix->m_Matrix->GetElements(m);
					switch(m_Parameters[2].dwParamType&DCPT_TYPEMASK)
					{
					case DCPT_RECTX:
					case DCPT_RECTY:
					case DCPT_RECTH:
					case DCPT_RECTW:
					case DCPT_POINTX:
					case DCPT_POINTY:
					case DCPT_REAL:
						m[m_Parameters[1].m_int]=m_Parameters[2].m_real;
						break;
					case DCPT_COLOR:
						m[m_Parameters[1].m_int]=(REAL)m_Parameters[2].m_pColor->GetValue();
						break;
					case DCPT_STRING:
						m[m_Parameters[1].m_int]=(REAL)atof(*m_Parameters[2].m_pCString);
						break;
					case DCPT_MATRIX:
						{
							REAL m2[10];
							m_Parameters[2].m_pMatrix->m_Matrix->GetElements(m2);
							m[m_Parameters[1].m_int]=m2[m_Parameters[1].m_int];
						}
						break;
					case DCPT_INTEGER:
					case DCPT_FLAG:
						m[m_Parameters[1].m_int]=(REAL)m_Parameters[2].m_int;
						break;
					}
					m_Parameters[0].m_pDestMatrix->m_Matrix->SetElements(m[0],m[1],m[2],m[3],m[4],m[5]);
				}
			}
			break;
		case DCUT_GETMATRIXELEMENT:	//DestValue,nMatrix,nElement
			if (m_NParams==3 && m_Parameters && m_Parameters[0].m_pDestReal && m_Parameters[1].m_pMatrix->m_Matrix)
			{
				if (m_Parameters[2].m_int>=0 && m_Parameters[2].m_int<=5)
				{
					REAL m[10];
					m_Parameters[1].m_pMatrix->m_Matrix->GetElements(m);
					switch(m_Parameters[0].dwParamType&DCPT_TYPEMASK)
					{
					case DCPT_DESTRECTX:
					case DCPT_DESTRECTY:
					case DCPT_DESTRECTH:
					case DCPT_DESTRECTW:
					case DCPT_DESTPOINTX:
					case DCPT_DESTPOINTY:
					case DCPT_DESTREAL:
						*(m_Parameters[0].m_pDestReal)=m[m_Parameters[2].m_int];
						break;
					case DCPT_DESTMATRIX:
						{
							REAL m2[10];
							m_Parameters[0].m_pDestMatrix->m_Matrix->GetElements(m2);
							m2[m_Parameters[2].m_int]=m[m_Parameters[2].m_int];
							m_Parameters[0].m_pDestMatrix->m_Matrix->SetElements(m2[0],m2[1],m2[2],m2[3],m2[4],m2[5]);
						}
						break;
					case DCPT_DESTINTEGER:
						*(m_Parameters[0].m_pDestInt)=(INT)m[m_Parameters[2].m_int];
						break;
					case DCPT_DESTSTRING:
						m_Parameters[0].m_pDestCString->Format("%g",m[m_Parameters[2].m_int]);
						break;
					}
				}
			}
			break;
		case DCUT_TRANSFORMBRUSH:	//Brush,nMatrix
			if (m_NParams==2 && m_Parameters && m_Parameters[0].m_pBrush && m_Parameters[0].m_pBrush->m_Brush && m_Parameters[1].m_pMatrix && m_Parameters[1].m_pMatrix->m_Matrix)
				switch(m_Parameters[0].m_pBrush->m_Brush->GetType())
				{
				case BrushTypeLinearGradient:
					((LinearGradientBrush *)m_Parameters[0].m_pBrush->m_Brush)->SetTransform(m_Parameters[1].m_pMatrix->m_Matrix);
					break;
				case BrushTypePathGradient:
					((PathGradientBrush *)m_Parameters[0].m_pBrush->m_Brush)->SetTransform(m_Parameters[1].m_pMatrix->m_Matrix);
					break;
				case BrushTypeTextureFill:
					((TextureBrush *)m_Parameters[0].m_pBrush->m_Brush)->SetTransform(m_Parameters[1].m_pMatrix->m_Matrix);
					break;
				}
			break;

		case DCUT_ENDIF:
		case DCUT_LABEL://LabelName
		case DCUT_NONE:
		default:
			m_Action=DCUA_NONE;
			break;
		}
	else
		switch(m_Type)
		{
		case DCUT_NONE:
		default:
			break;
		}

	SetResult();

	return m_Action;
}

void CODContextItem::ResetResult()
{
	CODContextItem::ResetParameter((PDCIPARAMETER)&m_Result);
	m_Result.dwDestination=DCPT_NONE;
}

void CODContextItem::ResetParameters(PDCIPARAMETER *pParam, UINT *ioNParams)
{
	if (pParam && *pParam && ioNParams)
	{
		UINT i;
		for(i=0;i<*ioNParams;i++)
			CODContextItem::ResetParameter((*pParam)+i);
		delete []*pParam;
	}
	*ioNParams=0;
	*pParam=NULL;
}

void CODContextItem::ResetParameter(PDCIPARAMETER pParam)
{
	if (pParam)
	{
		switch(pParam->dwParamType&(0xFFFFFFFF^DCPTF_SUBTYPEMASK))
		{
		case DCPT_DESTRECT:
		case DCPT_REFERENCE|DCPT_DESTRECT:
		case DCPT_REFERENCE2|DCPT_DESTRECT:
			pParam->m_pDestRectF=NULL;
			break;
		case DCPT_DESTCOLOR:
		case DCPT_REFERENCE|DCPT_DESTCOLOR:
		case DCPT_REFERENCE2|DCPT_DESTCOLOR:
			pParam->m_pDestColor=NULL;
			break;
		case DCPT_RECT:
		case DCPT_REFERENCE|DCPT_RECT:
		case DCPT_REFERENCE2|DCPT_RECT:
			if (pParam->m_pRectF) delete pParam->m_pRectF;
			pParam->m_pRectF=NULL;
			break;
		case DCPT_POINT:
		case DCPT_REFERENCE|DCPT_POINT:
		case DCPT_REFERENCE2|DCPT_POINT:
			if (pParam->m_pPointF) delete pParam->m_pPointF;
			pParam->m_pPointF=NULL;
			break;
		case DCPT_STRING:
		case DCPT_REFERENCE|DCPT_STRING:
		case DCPT_REFERENCE2|DCPT_STRING:
			if (pParam->m_pCString) delete pParam->m_pCString;
			pParam->m_pCString=NULL;
			break;
		case DCPT_COLOR:
		case DCPT_REFERENCE|DCPT_COLOR:
		case DCPT_REFERENCE2|DCPT_COLOR:
			if (pParam->m_pColor) delete pParam->m_pColor;
			pParam->m_pColor=NULL;
			break;
		case DCPT_PEN:
		case DCPT_REFERENCE|DCPT_PEN:
		case DCPT_REFERENCE2|DCPT_PEN:
			pParam->m_pPen=NULL;
			break;
		case DCPT_GUIOBJECT:
		case DCPT_REFERENCE|DCPT_GUIOBJECT:
		case DCPT_REFERENCE2|DCPT_GUIOBJECT:
			pParam->m_pGPUnit=NULL;
			break;
		case DCPT_IMAGE:
		case DCPT_REFERENCE|DCPT_IMAGE:
		case DCPT_REFERENCE2|DCPT_IMAGE:
			pParam->m_pBitmap=NULL;
			break;
		case DCPT_IMAGELIST:
			if (pParam->pAddParams)
			{
				CODContextItem::ResetParameter(pParam->pAddParams+1);
				CODContextItem::ResetParameter(pParam->pAddParams);
				delete []pParam->pAddParams;
				pParam->pAddParams=NULL;
			}
			pParam->m_pBitmap=NULL;
			break;
		case DCPT_PATH:
		case DCPT_REFERENCE|DCPT_PATH:
		case DCPT_REFERENCE2|DCPT_PATH:
			pParam->m_pPath=NULL;
			break;
		case DCPT_REGION:
		case DCPT_REFERENCE|DCPT_REGION:
		case DCPT_REFERENCE2|DCPT_REGION:
			pParam->m_pRegion=NULL;
			break;
		case DCPT_FONT:
		case DCPT_REFERENCE|DCPT_FONT:
		case DCPT_REFERENCE2|DCPT_FONT:
			pParam->m_pFont=NULL;
			break;
		case DCPT_BRUSH:
		case DCPT_REFERENCE|DCPT_BRUSH:
		case DCPT_REFERENCE2|DCPT_BRUSH:
			pParam->m_pBrush=NULL;
			break;
		case DCPT_SFORMAT:
		case DCPT_REFERENCE|DCPT_SFORMAT:
		case DCPT_REFERENCE2|DCPT_SFORMAT:
			pParam->m_pStrFormat=NULL;
			break;
		case DCPT_MATRIX:
			if (pParam->m_pMatrix) delete pParam->m_pMatrix;
		case DCPT_REFERENCE|DCPT_MATRIX:
		case DCPT_REFERENCE2|DCPT_MATRIX:
			pParam->m_pMatrix=NULL;
			break;
		case DCPT_DESTMATRIX:
		case DCPT_REFERENCE|DCPT_DESTMATRIX:
		case DCPT_REFERENCE2|DCPT_DESTMATRIX:
			pParam->m_pDestMatrix=NULL;
			break;
		case DCPT_DESTSTRING:
		case DCPT_REFERENCE|DCPT_DESTSTRING:
		case DCPT_REFERENCE2|DCPT_DESTSTRING:
			pParam->m_pDestCString=NULL;
			break;
		case DCPT_DESTREGION:
		case DCPT_REFERENCE|DCPT_DESTREGION:
		case DCPT_REFERENCE2|DCPT_DESTREGION:
			pParam->m_pDestRegion=NULL;
			break;
		case DCPT_ARRAYIDX:
		case DCPT_ARRAYREF:
			if (pParam->m_dwArray) delete []pParam->m_dwArray;
			pParam->m_dwArray=NULL;
			break;
		case DCPT_ARRAY|DCPT_POINT:
			if (pParam->m_pPointF) delete []pParam->m_pPointF;
			pParam->m_pPointF=NULL;
			break;
		case DCPT_ARRAY|DCPT_STRING:
			if (pParam->m_pCString) delete []pParam->m_pCString;
			pParam->m_pCString=NULL;
			break;
		case DCPT_ARRAY|DCPT_RECT:
			if (pParam->m_pRectF) delete []pParam->m_pRectF;
			pParam->m_pRectF=NULL;
			break;



		case DCPT_REAL:
		case DCPT_REFERENCE|DCPT_REAL:
		case DCPT_REFERENCE2|DCPT_REAL:
		case DCPT_INTEGER:
		case DCPT_REFERENCE|DCPT_INTEGER:
		case DCPT_REFERENCE2|DCPT_INTEGER:
		default: 
			break;
		}

		::ZeroMemory(pParam,sizeof(DCIPARAMETER));
		pParam->dwParamType=DCPT_NONE;
	}
}

void CODContextItem::PrepareParameters()
{
	UINT i;
	if (m_Parameters)
		for(i=0;i<m_NParams;i++) PrepareParameter(pContext, m_Parameters+i);
}

void CODContextItem::PrepareParameter(CODContext *ipContext, PDCIPARAMETER pParam)
{
	if (pParam && ipContext)
	{
		if ((pParam->dwParamType&DCPTF_SUBTYPEMASK))
		{
			switch(pParam->dwParamType&DCPTF_SUBTYPEMASK)
			{
			case DCPTF_ST_CPLACEY:
				pParam->m_real=GPC.m_Document->GetMainScreen()->CharPlaceSize.Height;
				break;
			case DCPTF_ST_CPLACEX:
				pParam->m_real=GPC.m_Document->GetMainScreen()->CharPlaceSize.Width;
				break;
			case DCPTF_ST_SCRHEIGHT:
				{
					RECT re;
					::GetClientRect(GPC.m_hViewWnd,&re);
					pParam->m_int=re.bottom;
				}
				break;
			case DCPTF_ST_SCRWIDTH:
				{
					RECT re;
					::GetClientRect(GPC.m_hViewWnd,&re);
					pParam->m_int=re.right;
				}
				break;
			case DCPTF_ST_SCRCY:
				pParam->m_int=GPC.m_Document->GetMainScreen()->ScreenSize.Height;
				break;
			case DCPTF_ST_SCRCX:
				pParam->m_int=GPC.m_Document->GetMainScreen()->ScreenSize.Width;
				break;
			case DCPTF_ST_SCRSCALEYX:
				{
					GPScreen *s=GPC.m_Document->GetMainScreen();
					pParam->m_real=s->CharPlaceSize.Height/s->CharPlaceSize.Width;
				}
				break;
			case DCPTF_ST_SCRCLIENTRECT:
				{
					RECT re;
					::GetClientRect(GPC.m_hViewWnd,&re);
					if (pParam->dwParamType==(DCPT_RECT|DCPTF_ST_SCRCLIENTRECT))
					{
						pParam->m_pRectF->X=(REAL)re.left;
						pParam->m_pRectF->Y=(REAL)re.top;
						pParam->m_pRectF->Width=(REAL)(re.right-re.left+1);
						pParam->m_pRectF->Height=(REAL)(re.bottom-re.top+1);
					}
				}
				break;
			case DCPTF_ST_SCRWNDRECT:
				{
					RECT re;
					::GetWindowRect(GPC.m_hViewWnd,&re);
					if (pParam->dwParamType==(DCPT_RECT|DCPTF_ST_SCRWNDRECT))
					{
						pParam->m_pRectF->X=(REAL)re.left;
						pParam->m_pRectF->Y=(REAL)re.top;
						pParam->m_pRectF->Width=(REAL)(re.right-re.left+1);
						pParam->m_pRectF->Height=(REAL)(re.bottom-re.top+1);
					}
				}
				break;

			case DCPTF_ST_MOUSEPOINTW:
				{
					POINT po;
					::GetCursorPos(&po);
					if (pParam->dwParamType==(DCPT_POINT|DCPTF_ST_MOUSEPOINTW))
					{
						pParam->m_pPointF->X=(REAL)po.x;
						pParam->m_pPointF->Y=(REAL)po.y;
					}
				}
				break;

			case DCPTF_ST_MOUSEPOINTS:
				{
					POINT po;
					::GetCursorPos(&po);
					::ScreenToClient(GPC.m_hViewWnd,&po);
					if (pParam->dwParamType==(DCPT_POINT|DCPTF_ST_MOUSEPOINTS))
					{
						pParam->m_pPointF->X=(REAL)po.x;
						pParam->m_pPointF->Y=(REAL)po.y;
					}
				}
				break;
			case DCPTF_ST_MOUSEPOINTC:
				{
					POINT po;
					::GetCursorPos(&po);
					if (pParam->dwParamType==(DCPT_POINT|DCPTF_ST_MOUSEPOINTC))
					{
						GPScreen *s=GPC.m_Document->GetMainScreen();
						Point po2;
						po2.X=po.x;
						po2.Y=po.y;
						s->GetCharPosByWndPos(po2);
						pParam->m_pPointF->X=(REAL)po2.X;
						pParam->m_pPointF->Y=(REAL)po2.Y;
					}
				}
				break;
			}
		}
		else
		switch(pParam->dwParamType)
		{
		case DCPT_DESTRECT:
		case DCPT_REFERENCE|DCPT_DESTRECT:
			pParam->m_pDestRectF=NULL;
			if (pParam->m_Reference<ipContext->m_nRectArray)
				pParam->m_pDestRectF=ipContext->m_RectArr+pParam->m_Reference;
			else
			{
				CString tmpCS;
				tmpCS.Format("SetRect %d,0,0,0,0",pParam->m_Reference);
				ipContext->DoMethod(tmpCS,NULL); 
				if (pParam->m_Reference<ipContext->m_nRectArray)
					pParam->m_pDestRectF=ipContext->m_RectArr+pParam->m_Reference;
			}
			break;
		case DCPT_REFERENCE2|DCPT_DESTRECT:
			pParam->m_pDestRectF=NULL;
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nRectArray)
					pParam->m_pDestRectF=ipContext->m_RectArr+nRef;
				else
				{
					CString tmpCS;
					tmpCS.Format("SetRect %d,0,0,0,0",nRef);
					ipContext->DoMethod(tmpCS,NULL); 
					if (nRef<ipContext->m_nRectArray)
						pParam->m_pDestRectF=ipContext->m_RectArr+nRef;
				}
			}
			break;
		case DCPT_REFERENCE|DCPT_DESTRECTX:
			if (pParam->m_Reference<ipContext->m_nRectArray)
				pParam->m_pDestReal=&(ipContext->m_RectArr[pParam->m_Reference].X);
			else
			{
				CString tmpCS;
				tmpCS.Format("SetRect %d,0,0,0,0",pParam->m_Reference);
				ipContext->DoMethod(tmpCS,NULL); 
				if (pParam->m_Reference<ipContext->m_nRectArray)
					pParam->m_pDestReal=&(ipContext->m_RectArr[pParam->m_Reference].X);
			}
			break;
		case DCPT_REFERENCE2|DCPT_DESTRECTX:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nRectArray)
					pParam->m_pDestReal=&(ipContext->m_RectArr[nRef].X);
				else
				{
					CString tmpCS;
					tmpCS.Format("SetRect %d,0,0,0,0",nRef);
					ipContext->DoMethod(tmpCS,NULL); 
					if (nRef<ipContext->m_nRectArray)
						pParam->m_pDestReal=&(ipContext->m_RectArr[nRef].X);
				}
			}
			break;
		case DCPT_REFERENCE|DCPT_DESTRECTY:
			if (pParam->m_Reference<ipContext->m_nRectArray)
				pParam->m_pDestReal=&(ipContext->m_RectArr[pParam->m_Reference].Y);
			else
			{
				CString tmpCS;
				tmpCS.Format("SetRect %d,0,0,0,0",pParam->m_Reference);
				ipContext->DoMethod(tmpCS,NULL); 
				if (pParam->m_Reference<ipContext->m_nRectArray)
					pParam->m_pDestReal=&(ipContext->m_RectArr[pParam->m_Reference].Y);
			}
			break;
		case DCPT_REFERENCE2|DCPT_DESTRECTY:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nRectArray)
					pParam->m_pDestReal=&(ipContext->m_RectArr[nRef].Y);
				else
				{
					CString tmpCS;
					tmpCS.Format("SetRect %d,0,0,0,0",nRef);
					ipContext->DoMethod(tmpCS,NULL); 
					if (nRef<ipContext->m_nRectArray)
						pParam->m_pDestReal=&(ipContext->m_RectArr[nRef].Y);
				}
			}
			break;
		case DCPT_REFERENCE|DCPT_DESTRECTW:
			if (pParam->m_Reference<ipContext->m_nRectArray)
				pParam->m_pDestReal=&(ipContext->m_RectArr[pParam->m_Reference].Width);
			else
			{
				CString tmpCS;
				tmpCS.Format("SetRect %d,0,0,0,0",pParam->m_Reference);
				ipContext->DoMethod(tmpCS,NULL); 
				if (pParam->m_Reference<ipContext->m_nRectArray)
					pParam->m_pDestReal=&(ipContext->m_RectArr[pParam->m_Reference].Width);
			}
			break;
		case DCPT_REFERENCE2|DCPT_DESTRECTW:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nRectArray)
					pParam->m_pDestReal=&(ipContext->m_RectArr[nRef].Width);
				else
				{
					CString tmpCS;
					tmpCS.Format("SetRect %d,0,0,0,0",nRef);
					ipContext->DoMethod(tmpCS,NULL); 
					if (nRef<ipContext->m_nRectArray)
						pParam->m_pDestReal=&(ipContext->m_RectArr[nRef].Width);
				}
			}
			break;
		case DCPT_REFERENCE|DCPT_DESTRECTH:
			if (pParam->m_Reference<ipContext->m_nRectArray)
				pParam->m_pDestReal=&(ipContext->m_RectArr[pParam->m_Reference].Height);
			else
			{
				CString tmpCS;
				tmpCS.Format("SetRect %d,0,0,0,0",pParam->m_Reference);
				ipContext->DoMethod(tmpCS,NULL); 
				if (pParam->m_Reference<ipContext->m_nRectArray)
					pParam->m_pDestReal=&(ipContext->m_RectArr[pParam->m_Reference].Height);
			}
			break;
		case DCPT_REFERENCE2|DCPT_DESTRECTH:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nRectArray)
					pParam->m_pDestReal=&(ipContext->m_RectArr[nRef].Height);
				else
				{
					CString tmpCS;
					tmpCS.Format("SetRect %d,0,0,0,0",nRef);
					ipContext->DoMethod(tmpCS,NULL); 
					if (nRef<ipContext->m_nRectArray)
						pParam->m_pDestReal=&(ipContext->m_RectArr[nRef].Height);
				}
			}
			break;
		case DCPT_REFERENCE|DCPT_RECT:
			if (pParam->m_pRectF && pParam->m_Reference<ipContext->m_nRectArray)
				*(pParam->m_pRectF)=ipContext->m_RectArr[pParam->m_Reference];
			break;
		case DCPT_REFERENCE2|DCPT_RECT:
			if (pParam->m_pRectF && pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nRectArray)
					*(pParam->m_pRectF)=ipContext->m_RectArr[nRef];
			}
			break;
		case DCPT_REFERENCE|DCPT_RECTX:
			if (pParam->m_Reference<ipContext->m_nRectArray)
				pParam->m_real=ipContext->m_RectArr[pParam->m_Reference].X;
			break;
		case DCPT_REFERENCE2|DCPT_RECTX:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nRectArray)
					pParam->m_real=ipContext->m_RectArr[nRef].X;
			}
			break;
		case DCPT_REFERENCE|DCPT_RECTY:
			if (pParam->m_Reference<ipContext->m_nRectArray)
				pParam->m_real=ipContext->m_RectArr[pParam->m_Reference].Y;
			break;
		case DCPT_REFERENCE2|DCPT_RECTY:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nRectArray)
					pParam->m_real=ipContext->m_RectArr[nRef].Y;
			}
			break;
		case DCPT_REFERENCE|DCPT_RECTH:
			if (pParam->m_Reference<ipContext->m_nRectArray)
				pParam->m_real=ipContext->m_RectArr[pParam->m_Reference].Height;
			break;
		case DCPT_REFERENCE2|DCPT_RECTH:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nRectArray)
					pParam->m_real=ipContext->m_RectArr[nRef].Height;
			}
			break;
		case DCPT_REFERENCE|DCPT_RECTW:
			if (pParam->m_Reference<ipContext->m_nRectArray)
				pParam->m_real=ipContext->m_RectArr[pParam->m_Reference].Width;
			break;
		case DCPT_REFERENCE2|DCPT_RECTW:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nRectArray)
					pParam->m_real=ipContext->m_RectArr[nRef].Width;
			}
			break;
		case DCPT_REFERENCE|DCPT_POINT:
			if (pParam->m_pPointF && pParam->m_Reference<ipContext->m_nPointArray)
				*(pParam->m_pPointF)=ipContext->m_PointArr[pParam->m_Reference];
			break;
		case DCPT_REFERENCE2|DCPT_POINT:
			if (pParam->m_pPointF && pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nPointArray)
					*(pParam->m_pPointF)=ipContext->m_PointArr[nRef];
			}
			break;
		case DCPT_REFERENCE|DCPT_DESTPOINT:
			pParam->m_pDestPointF=NULL;
			if (pParam->m_Reference<ipContext->m_nPointArray)
				pParam->m_pDestPointF=ipContext->m_PointArr+pParam->m_Reference;
			else
			{
				CString tmpCS;
				tmpCS.Format("SetPoint %d,0,0",pParam->m_Reference);
				ipContext->DoMethod(tmpCS,NULL); 
				if (pParam->m_Reference<ipContext->m_nPointArray)
					pParam->m_pDestPointF=ipContext->m_PointArr+pParam->m_Reference;
			}
			break;
		case DCPT_REFERENCE2|DCPT_DESTPOINT:
			pParam->m_pDestPointF=NULL;
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nPointArray)
					pParam->m_pDestPointF=ipContext->m_PointArr+nRef;
				else
				{
					CString tmpCS;
					tmpCS.Format("SetPoint %d,0,0",nRef);
					ipContext->DoMethod(tmpCS,NULL); 
					if (nRef<ipContext->m_nPointArray)
						pParam->m_pDestPointF=ipContext->m_PointArr+nRef;
				}
			}
			break;
		case DCPT_REFERENCE|DCPT_DESTPOINTX:
			if (pParam->m_Reference<ipContext->m_nPointArray)
				pParam->m_pDestReal=&(ipContext->m_PointArr[pParam->m_Reference].X);
			else
			{
				CString tmpCS;
				tmpCS.Format("SetPoint %d,0,0",pParam->m_Reference);
				ipContext->DoMethod(tmpCS,NULL); 
				if (pParam->m_Reference<ipContext->m_nPointArray)
					pParam->m_pDestReal=&(ipContext->m_PointArr[pParam->m_Reference].X);
			}
			break;
		case DCPT_REFERENCE2|DCPT_DESTPOINTX:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nPointArray)
					pParam->m_pDestReal=&(ipContext->m_PointArr[nRef].X);
				else
				{
					CString tmpCS;
					tmpCS.Format("SetPoint %d,0,0",nRef);
					ipContext->DoMethod(tmpCS,NULL); 
					if (nRef<ipContext->m_nPointArray)
						pParam->m_pDestReal=&(ipContext->m_PointArr[nRef].X);
				}
			}
			break;
		case DCPT_REFERENCE|DCPT_DESTPOINTY:
			if (pParam->m_Reference<ipContext->m_nPointArray)
				pParam->m_pDestReal=&(ipContext->m_PointArr[pParam->m_Reference].Y);
			else
			{
				CString tmpCS;
				tmpCS.Format("SetPoint %d,0,0",pParam->m_Reference);
				ipContext->DoMethod(tmpCS,NULL); 
				if (pParam->m_Reference<ipContext->m_nPointArray)
					pParam->m_pDestReal=&(ipContext->m_PointArr[pParam->m_Reference].Y);
			}
			break;
		case DCPT_REFERENCE2|DCPT_DESTPOINTY:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nPointArray)
					pParam->m_pDestReal=&(ipContext->m_PointArr[nRef].Y);
				else
				{
					CString tmpCS;
					tmpCS.Format("SetPoint %d,0,0",nRef);
					ipContext->DoMethod(tmpCS,NULL); 
					if (nRef<ipContext->m_nPointArray)
						pParam->m_pDestReal=&(ipContext->m_PointArr[nRef].Y);
				}
			}
			break;
		case DCPT_REFERENCE|DCPT_POINTX:
			if (pParam->m_Reference<ipContext->m_nPointArray)
				pParam->m_real=ipContext->m_PointArr[pParam->m_Reference].X;
			break;
		case DCPT_REFERENCE2|DCPT_POINTX:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nPointArray)
					pParam->m_real=ipContext->m_PointArr[nRef].X;
			}
			break;
		case DCPT_REFERENCE|DCPT_POINTY:
			if (pParam->m_Reference<ipContext->m_nPointArray)
				pParam->m_real=ipContext->m_PointArr[pParam->m_Reference].Y;
			break;
		case DCPT_REFERENCE2|DCPT_POINTY:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nPointArray)
					pParam->m_real=ipContext->m_PointArr[nRef].Y;
			}
			break;
		case DCPT_REFERENCE|DCPT_STRING:
			if (pParam->m_pCString && pParam->m_Reference<ipContext->m_nStringArray)
				*(pParam->m_pCString)=ipContext->m_StringArr[pParam->m_Reference];
			break;
		case DCPT_REFERENCE2|DCPT_STRING:
			if (pParam->m_pCString && pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nStringArray)
					*(pParam->m_pCString)=ipContext->m_StringArr[nRef];
			}
			break;
		case DCPT_REFERENCE|DCPT_INTEGER:
			if (pParam->m_Reference<ipContext->m_nIntArray)
				pParam->m_dword=ipContext->m_IntArr[pParam->m_Reference];
			break;
		case DCPT_REFERENCE2|DCPT_INTEGER:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nIntArray)
					pParam->m_dword=ipContext->m_IntArr[nRef];
			}
			break;
		case DCPT_DESTINTEGER:
		case DCPT_REFERENCE|DCPT_DESTINTEGER:
			if (pParam->m_Reference<ipContext->m_nIntArray)
				pParam->m_pDestInt=ipContext->m_IntArr+pParam->m_Reference;
			else
			{
				CString tmpCS;
				tmpCS.Format("SetInt %d,0",pParam->m_Reference);
				ipContext->DoMethod(tmpCS,NULL); 
				if (pParam->m_Reference<ipContext->m_nIntArray)
					pParam->m_pDestInt=ipContext->m_IntArr+pParam->m_Reference;
			}
			break;
		case DCPT_REFERENCE2|DCPT_DESTINTEGER:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nIntArray)
					pParam->m_pDestInt=ipContext->m_IntArr+nRef;
				else
				{
					CString tmpCS;
					tmpCS.Format("SetInt %d,0",nRef);
					ipContext->DoMethod(tmpCS,NULL); 
					if (nRef<ipContext->m_nIntArray)
						pParam->m_pDestInt=ipContext->m_IntArr+nRef;
				}
			}
			break;
		case DCPT_REFERENCE|DCPT_REAL:
			if (pParam->m_Reference<ipContext->m_nREALArray)
				pParam->m_real=(REAL)ipContext->m_REALArr[pParam->m_Reference];
			break;
		case DCPT_REFERENCE2|DCPT_REAL:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nREALArray)
					pParam->m_real=(REAL)ipContext->m_REALArr[nRef];
			}
			break;
		case DCPT_DESTREAL:
		case DCPT_REFERENCE|DCPT_DESTREAL:
			if (pParam->m_Reference<ipContext->m_nREALArray)
				pParam->m_pDestReal=ipContext->m_REALArr+pParam->m_Reference;
			else
			{
				CString tmpCS;
				tmpCS.Format("SetREAL %d,0",pParam->m_Reference);
				ipContext->DoMethod(tmpCS,NULL); 
				if (pParam->m_Reference<ipContext->m_nREALArray)
					pParam->m_pDestReal=ipContext->m_REALArr+pParam->m_Reference;
			}
			break;
		case DCPT_REFERENCE2|DCPT_DESTREAL:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nREALArray)
					pParam->m_pDestReal=ipContext->m_REALArr+nRef;
				else
				{
					CString tmpCS;
					tmpCS.Format("SetREAL %d,0",nRef);
					ipContext->DoMethod(tmpCS,NULL); 
					if (nRef<ipContext->m_nREALArray)
						pParam->m_pDestReal=ipContext->m_REALArr+nRef;
				}
			}
			break;
		case DCPT_REFERENCE|DCPT_COLOR:
			if (pParam->m_pColor && pParam->m_Reference<ipContext->m_nRGBArray)
				*pParam->m_pColor=ipContext->m_RGBArr[pParam->m_Reference];
			break;
		case DCPT_REFERENCE2|DCPT_COLOR:
			if (pParam->m_pColor && pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nRGBArray)
					*pParam->m_pColor=ipContext->m_RGBArr[nRef];
			}
			break;
		case DCPT_DESTCOLOR:
		case DCPT_REFERENCE|DCPT_DESTCOLOR:
			pParam->m_pDestColor=NULL;
			if (pParam->m_Reference<ipContext->m_nRGBArray)
				pParam->m_pDestColor=ipContext->m_RGBArr+pParam->m_Reference;
			else
			{
				CString tmpCS;
				tmpCS.Format("SetColor %d,0,0,0,255",pParam->m_Reference);
				ipContext->DoMethod(tmpCS,NULL); 
				if (pParam->m_Reference<ipContext->m_nRGBArray)
					pParam->m_pDestColor=ipContext->m_RGBArr+pParam->m_Reference;
			}
			break;
		case DCPT_REFERENCE2|DCPT_DESTCOLOR:
			pParam->m_pDestColor=NULL;
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nRGBArray)
					pParam->m_pDestColor=ipContext->m_RGBArr+nRef;
				else
				{
					CString tmpCS;
					tmpCS.Format("SetColor %d,0,0,0,255",nRef);
					ipContext->DoMethod(tmpCS,NULL); 
					if (nRef<ipContext->m_nRGBArray)
						pParam->m_pDestColor=ipContext->m_RGBArr+nRef;
				}
			}
			break;
		case DCPT_PEN:
		case DCPT_REFERENCE|DCPT_PEN:
			if (pParam->m_Reference<ipContext->m_nPenArray)
				pParam->m_pPen=ipContext->m_PenArr[pParam->m_Reference];
			break;
		case DCPT_REFERENCE2|DCPT_PEN:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nPenArray)
					pParam->m_pPen=ipContext->m_PenArr[nRef];
			}
			break;
		case DCPT_IMAGE:
		case DCPT_REFERENCE|DCPT_IMAGE:
			if (pParam->m_Reference<ipContext->m_nBitmapArray)
				pParam->m_pBitmap=ipContext->m_BitmapArr[pParam->m_Reference];
			break;
		case DCPT_REFERENCE2|DCPT_IMAGE:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nBitmapArray)
					pParam->m_pBitmap=ipContext->m_BitmapArr[nRef];
			}
			break;
		case DCPT_IMAGELIST:
			if (pParam->pAddParams && ipContext->m_ILBitmap)
			{
				pParam->m_pBitmap=NULL;
				PrepareParameter(ipContext, pParam->pAddParams);
				PrepareParameter(ipContext, pParam->pAddParams+1);
				if (*pParam->pAddParams[0].m_pCString!="")
				{
					UINT i;
					for(i=0;i<ipContext->m_nILBitmap && (!ipContext->m_ILBitmap[i] || ipContext->m_ILBitmap[i]->CreationString!=*(pParam->pAddParams[0].m_pCString));i++)
						i=i;
					if (i>=ipContext->m_nILBitmap) 
					{
						CString tmpCS="LoadImageList "+*pParam->pAddParams[0].m_pCString+","+*pParam->pAddParams[0].m_pCString;
						ipContext->DoMethod(tmpCS,NULL);
						for(i=0;i<ipContext->m_nILBitmap && (!ipContext->m_ILBitmap[i] || ipContext->m_ILBitmap[i]->CreationString!=*(pParam->pAddParams[0].m_pCString));i++);
					}
					if (i<ipContext->m_nILBitmap) 
					{
						GUID   pageGuid = FrameDimensionPage;
						pParam->m_pBitmap=ipContext->m_ILBitmap[i];
						pParam->m_pBitmap->m_Bitmap->SelectActiveFrame(&pageGuid,pParam->pAddParams[1].m_int);
					}
				}
			}
			break;
		case DCPT_GUIOBJECT:
		case DCPT_REFERENCE|DCPT_GUIOBJECT:
			if (pParam->m_Reference<(*ipContext->m_CurDialogGPU)->m_NGPUNIT)
				pParam->m_pGPUnit=ipContext->m_CurDialogGPU[pParam->m_Reference];
			break;
		case DCPT_REFERENCE2|DCPT_GUIOBJECT:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<(*ipContext->m_CurDialogGPU)->m_NGPUNIT)
					pParam->m_pGPUnit=ipContext->m_CurDialogGPU[nRef];
			}
			break;
		case DCPT_PATH:
		case DCPT_REFERENCE|DCPT_PATH:
			if (pParam->m_Reference<ipContext->m_nGraphPathArray)
				pParam->m_pPath=ipContext->m_GraphPathArr[pParam->m_Reference];
			break;
		case DCPT_REFERENCE2|DCPT_PATH:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nGraphPathArray)
					pParam->m_pPath=ipContext->m_GraphPathArr[nRef];
			}
			break;
		case DCPT_FONT:
		case DCPT_REFERENCE|DCPT_FONT:
		case DCPT_REFERENCE2|DCPT_FONT:
			{
				UINT nRef=-1;
				pParam->m_pFont=NULL;
				if (pParam->dwParamType==(DCPT_REFERENCE2|DCPT_FONT))
				{
					if (pParam->m_Reference<ipContext->m_nIntArray)
						nRef=ipContext->m_IntArr[pParam->m_Reference];
				}
				else nRef=pParam->m_Reference;
				if (nRef<ipContext->m_nFontArray)
				{
					pParam->m_pFont=ipContext->m_FontArr[nRef];
					if (pParam->m_pFont && pParam->m_pFont->m_Font==NULL)
					{
						LOGFONT lf={0};
						CWnd *w=AfxGetMainWnd();
						CFont *f=GPC.m_View->GetFont();
						if (f) 
							f->GetLogFont(&lf);
						FontFamily *emHeightFontFamily;
						if (*lf.lfFaceName==0)
							emHeightFontFamily=new FontFamily(L"arial");
						else
						{
							WCHAR tmpWText2[200];
							MultiByteToWideChar(CP_ACP, 0, lf.lfFaceName, -1, tmpWText2, 100);
							emHeightFontFamily=new FontFamily(tmpWText2);
						}
						if (lf.lfHeight==0) lf.lfHeight=11;
						if (lf.lfHeight<0) lf.lfHeight=-lf.lfHeight;
						ipContext->m_FontArr[nRef]->m_Font=new Font(emHeightFontFamily, (REAL)lf.lfHeight);
					}
				}
			}
			break;
		case DCPT_BRUSH:
		case DCPT_REFERENCE|DCPT_BRUSH:
			if (pParam->m_Reference<ipContext->m_nBrushArray)
				pParam->m_pBrush=ipContext->m_BrushArr[pParam->m_Reference];
			break;
		case DCPT_REFERENCE2|DCPT_BRUSH:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nBrushArray)
					pParam->m_pBrush=ipContext->m_BrushArr[nRef];
			}
			break;
		case DCPT_SFORMAT:
		case DCPT_REFERENCE|DCPT_SFORMAT:
			if (pParam->m_Reference<ipContext->m_nStringFormatArray)
				pParam->m_pStrFormat=ipContext->m_StringFormatArr[pParam->m_Reference];
			break;
		case DCPT_REFERENCE2|DCPT_SFORMAT:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nStringFormatArray)
					pParam->m_pStrFormat=ipContext->m_StringFormatArr[nRef];
			}
			break;
		case DCPT_MATRIX:
			break;
		case DCPT_REFERENCE|DCPT_MATRIX:
			if (pParam->m_Reference<ipContext->m_nMatrixArray)
				pParam->m_pMatrix=ipContext->m_MatrixArr[pParam->m_Reference];
			break;
		case DCPT_REFERENCE2|DCPT_MATRIX:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nMatrixArray)
					pParam->m_pMatrix=ipContext->m_MatrixArr[nRef];
			}
			break;
		case DCPT_DESTMATRIX:
		case DCPT_REFERENCE|DCPT_DESTMATRIX:
			if (pParam->m_Reference<ipContext->m_nMatrixArray)
				pParam->m_pDestMatrix=ipContext->m_MatrixArr[pParam->m_Reference];
			if (!pParam->m_pDestMatrix) 
			{
				CString tmpCS;
				tmpCS.Format("SetMatrix %d,0,0,0,0,0,0",pParam->m_Reference);
				ipContext->DoMethod(tmpCS,NULL); 
				if (pParam->m_Reference<ipContext->m_nMatrixArray)
					pParam->m_pDestMatrix=ipContext->m_MatrixArr[pParam->m_Reference];
			}
			break;
		case DCPT_REFERENCE2|DCPT_DESTMATRIX:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nMatrixArray)
					pParam->m_pDestMatrix=ipContext->m_MatrixArr[nRef];
				if (!pParam->m_pDestMatrix) 
				{
					CString tmpCS;
					tmpCS.Format("SetMatrix %d,0,0,0,0,0,0",nRef);
					ipContext->DoMethod(tmpCS,NULL); 
					if (nRef<ipContext->m_nMatrixArray)
						pParam->m_pDestMatrix=ipContext->m_MatrixArr[nRef];
				}
			}
			break;
		case DCPT_REGION:
		case DCPT_REFERENCE|DCPT_REGION:
			if (pParam->m_Reference<ipContext->m_nRgnArray)
				pParam->m_pRegion=ipContext->m_RgnArr[pParam->m_Reference];
			break;
		case DCPT_REFERENCE2|DCPT_REGION:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nRgnArray)
					pParam->m_pRegion=ipContext->m_RgnArr[nRef];
			}
			break;
		case DCPT_DESTREGION:
		case DCPT_REFERENCE|DCPT_DESTREGION:
			if (pParam->m_Reference<ipContext->m_nRgnArray)
				pParam->m_pDestRegion=ipContext->m_RgnArr[pParam->m_Reference];
			if (!pParam->m_pDestRegion) 
			{
				CString tmpCS;
				tmpCS.Format("SetRegion %d",pParam->m_Reference);
				ipContext->DoMethod(tmpCS,NULL); 
				if (pParam->m_Reference<ipContext->m_nRgnArray)
					pParam->m_pDestRegion=ipContext->m_RgnArr[pParam->m_Reference];
			}
			break;
		case DCPT_REFERENCE2|DCPT_DESTREGION:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nRgnArray)
					pParam->m_pDestRegion=ipContext->m_RgnArr[nRef];
				if (!pParam->m_pDestRegion) 
				{
					CString tmpCS;
					tmpCS.Format("SetRegion %d",nRef);
					ipContext->DoMethod(tmpCS,NULL); 
					if (nRef<ipContext->m_nRgnArray)
						pParam->m_pDestRegion=ipContext->m_RgnArr[nRef];
				}
			}
			break;
		case DCPT_DESTSTRING:
		case DCPT_REFERENCE|DCPT_DESTSTRING:
			if (pParam->m_Reference<ipContext->m_nStringArray)
				pParam->m_pDestCString=ipContext->m_StringArr+pParam->m_Reference;
			else
			{
				CString tmpCS;
				tmpCS.Format("SetString %d,",pParam->m_Reference);
				ipContext->DoMethod(tmpCS,NULL); 
				if (pParam->m_Reference<ipContext->m_nStringArray)
					pParam->m_pDestCString=ipContext->m_StringArr+pParam->m_Reference;
			}
			break;
		case DCPT_REFERENCE2|DCPT_DESTSTRING:
			if (pParam->m_Reference<ipContext->m_nIntArray)
			{
				UINT nRef=ipContext->m_IntArr[pParam->m_Reference];
				if (nRef<ipContext->m_nStringArray)
					pParam->m_pDestCString=ipContext->m_StringArr+nRef;
				else
				{
					CString tmpCS;
					tmpCS.Format("SetString %d,",nRef);
					ipContext->DoMethod(tmpCS,NULL); 
					if (nRef<ipContext->m_nStringArray)
						pParam->m_pDestCString=ipContext->m_StringArr+nRef;
				}
			}
			break;


		case DCPT_REAL:
		case DCPT_INTEGER:
		case DCPT_RECT:
		case DCPT_POINT:
		case DCPT_STRING:
		case DCPT_ARRAY|DCPT_RECT:
		case DCPT_ARRAY|DCPT_POINT:
		case DCPT_ARRAY|DCPT_STRING:
		case DCPT_ARRAYIDX:
		case DCPT_ARRAYREF:
			break;
		default: 
			//::ZeroMemory(pParam,sizeof(DCIPARAMETER));
			//pParam->dwParamType=DCPT_NONE;
			break;
		}

	}
}

int CODContextItem::TranslateParams(const char *ccStr, const DCParamType *pta, CODContext *ipContext, PDCIPARAMETER *iParameters, UINT *ioNParams)
{
	int ret=0;
	CODContextItem::ResetParameters(iParameters,ioNParams);
	if (ccStr && *ccStr && pta && *pta!=DCPT_NONE)
	{
		char *copyStr=new char [strlen(ccStr)+10];
		strcpy(copyStr,ccStr);
		char *mStr=copyStr;
		

		for(ret=0;pta[ret]!=DCPT_NONE;ret++);
		*iParameters= new DCIPARAMETER [ret];
		::ZeroMemory(*iParameters,ret*sizeof(DCIPARAMETER));
		for(ret=0;pta[ret]!=DCPT_NONE;ret++)
		if (!*mStr) (*iParameters)[ret].dwParamType=DCPT_NONE;
		else
		{
			char *mNextStr=mStr;
			char *mCurStr=mStr;
			int tmpCnt=0;
			while(*mNextStr && (tmpCnt!=0 || *mNextStr!=','))
			{
				if (*mNextStr=='\\') mNextStr++;
				else
				{
					if (*mNextStr=='(') tmpCnt++;
					if (*mNextStr==')') tmpCnt--;
				}
				*(mCurStr++)=*mNextStr;
				if (*mNextStr) mNextStr++;
			}
			if (*mNextStr) *(mNextStr++)=0;
			if (*mCurStr) *mCurStr=0;

			const char *posBrace=strchr(mStr,'(');
			if (posBrace) posBrace++;
			const char *posBrace2=NULL;
			if (posBrace) posBrace2=strchr(posBrace,'(') ;
			if (posBrace2) posBrace2++;
			DCParamType tmpType=(DCParamType)(pta[ret]&DCPT_TYPEMASK);
			if ((pta[ret]&DCPT_TYPEMASK)==DCPT_VARTYPE)
			{
				if (strncmp("INT(",mStr,4)==0) tmpType=DCPT_INTEGER;
				else
				if (strncmp("FLAG(",mStr,5)==0) tmpType=DCPT_FLAG;
				else
				if (strncmp("REAL(",mStr,5)==0) tmpType=DCPT_REAL;
				else
				if (strncmp("STRING(",mStr,7)==0) tmpType=DCPT_STRING;
				else
				if (strncmp("CLR(",mStr,4)==0) tmpType=DCPT_COLOR;
				else
				if (strncmp("CLRN(",mStr,5)==0) tmpType=DCPT_COLOR;
				else
				if (strncmp("CLRS(",mStr,5)==0) tmpType=DCPT_COLOR;
				else
				if (strncmp("RECT(",mStr,5)==0) tmpType=DCPT_RECT;
				else
				if (strncmp("RECTX(",mStr,6)==0) tmpType=DCPT_RECTX;
				else
				if (strncmp("RECTY(",mStr,6)==0) tmpType=DCPT_RECTY;
				else
				if (strncmp("RECTH(",mStr,6)==0) tmpType=DCPT_RECTH;
				else
				if (strncmp("RECTW(",mStr,6)==0) tmpType=DCPT_RECTW;
				else
				if (strncmp("POINT(",mStr,6)==0) tmpType=DCPT_POINT;
				else
				if (strncmp("POINTX(",mStr,7)==0) tmpType=DCPT_POINTX;
				else
				if (strncmp("POINTY(",mStr,7)==0) tmpType=DCPT_POINTY;
				else
				if (strncmp("PEN(",mStr,4)==0) tmpType=DCPT_PEN;
				else
				if (strncmp("BITMAP(",mStr,7)==0) tmpType=DCPT_IMAGE;
				else
				if (strncmp("ILIST(",mStr,6)==0) tmpType=DCPT_IMAGELIST;
				else
				if (strncmp("GUIOBJ(",mStr,7)==0) tmpType=DCPT_GUIOBJECT;
				else
				if (strncmp("PATH(",mStr,5)==0) tmpType=DCPT_PATH;
				else
				if (strncmp("REGION(",mStr,7)==0) tmpType=DCPT_REGION;
				else
				if (strncmp("MATRIX(",mStr,7)==0) tmpType=DCPT_MATRIX;
				else
				if (strncmp("FONT(",mStr,5)==0) tmpType=DCPT_FONT;
				else
				if (strncmp("BRUSH(",mStr,6)==0) tmpType=DCPT_BRUSH;
				else
				if (strncmp("SFORMAT(",mStr,8)==0) tmpType=DCPT_SFORMAT;
				else
				if (strncmp("ARRAYIDX(",mStr,9)==0) tmpType=DCPT_ARRAY;
				else
				if (strncmp("ARRAYREF(",mStr,9)==0) tmpType=DCPT_ARRAY;
				else
				if (strncmp("ARRAYPTS(",mStr,9)==0) tmpType=DCPT_ARRAY;
				else
				if (strncmp("ARRAYRECT(",mStr,10)==0) tmpType=DCPT_ARRAY;
				else tmpType=DCPT_INTEGER;
			}
			if ((pta[ret]&DCPT_TYPEMASK)==DCPT_DESTVARTYPE)
			{
				if (strncmp("INT(",mStr,4)==0) tmpType=DCPT_DESTINTEGER;
				else
				if (strncmp("REAL(",mStr,5)==0) tmpType=DCPT_DESTREAL;
				else
				if (strncmp("STRING(",mStr,7)==0) tmpType=DCPT_DESTSTRING;
				else
				if (strncmp("RECT(",mStr,5)==0) tmpType=DCPT_DESTRECT;
				else
				if (strncmp("RECTX(",mStr,6)==0) tmpType=DCPT_DESTRECTX;
				else
				if (strncmp("RECTY(",mStr,6)==0) tmpType=DCPT_DESTRECTY;
				else
				if (strncmp("RECTH(",mStr,6)==0) tmpType=DCPT_DESTRECTH;
				else
				if (strncmp("RECTW(",mStr,6)==0) tmpType=DCPT_DESTRECTW;
				else
				if (strncmp("POINT(",mStr,6)==0) tmpType=DCPT_DESTPOINT;
				else
				if (strncmp("POINTX(",mStr,7)==0) tmpType=DCPT_DESTPOINTX;
				else
				if (strncmp("POINTY(",mStr,7)==0) tmpType=DCPT_DESTPOINTY;
				else
				if (strncmp("CLR(",mStr,4)==0) tmpType=DCPT_DESTCOLOR;
				else
				if (strncmp("REGION(",mStr,7)==0) tmpType=DCPT_DESTREGION;
				else
				if (strncmp("MATRIX(",mStr,7)==0) tmpType=DCPT_DESTMATRIX;
				else tmpType=DCPT_NONE;
			}
			if (pta[ret]==DCPT_ARRAY)
			{
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_NONE;
				if (strncmp("ARRAYIDX(",mStr,9)==0 && posBrace)
				{
					(*iParameters)[ret].dwParamType=DCPT_ARRAYIDX;
					const char *pB=posBrace;
					UINT nArr=1;
					while(*pB) if (*(pB++)==';') nArr++;
					(*iParameters)[ret].m_dwArray=new DWORD [nArr+1];
					(*iParameters)[ret].dwNElements=nArr;
					pB=posBrace;
					nArr=0;
					while(*pB) 
					{
						(*iParameters)[ret].m_dwArray[nArr++]=atoi(pB);
						while(*pB && *(pB++)!=';');
					}
				}
				else
				if (strncmp("ARRAYREF(",mStr,9)==0 && posBrace)
				{
					(*iParameters)[ret].dwParamType=DCPT_ARRAYREF;
					const char *pB=posBrace;
					UINT nArr=1;
					while(*pB) if (*(pB++)==';') nArr++;
					(*iParameters)[ret].m_dwArray=new DWORD [nArr+1];
					(*iParameters)[ret].dwNElements=nArr;
					pB=posBrace;
					nArr=0;
					while(*pB) 
					{
						(*iParameters)[ret].m_dwArray[nArr++]=atoi(pB);
						while(*pB && *(pB++)!=';');
					}
				}
				else
				if (strncmp("ARRAYPTS(",mStr,9)==0 && posBrace)
				{
					(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_ARRAY|DCPT_POINT);
					const char *pB=posBrace;
					UINT nArr=1;
					while(*pB) if (*(pB++)==';') nArr++;
					(*iParameters)[ret].m_pPointF=new PointF [nArr+1];
					(*iParameters)[ret].dwNElements=nArr;
					pB=posBrace;
					nArr=0;
					while(*pB) 
					{
						REAL X=0,Y=0;
						sscanf(pB,"%g,%g",&X,&Y);
						(*iParameters)[ret].m_pPointF[nArr].X=X;
						(*iParameters)[ret].m_pPointF[nArr++].Y=Y;
						while(*pB && *(pB++)!=';');
					}
				}
				else
				if (strncmp("ARRAYRECT(",mStr,10)==0 && posBrace)
				{
					(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_ARRAY|DCPT_RECT);
					const char *pB=posBrace;
					UINT nArr=1;
					while(*pB) if (*(pB++)==';') nArr++;
					(*iParameters)[ret].m_pRectF=new RectF [nArr+1];
					(*iParameters)[ret].dwNElements=nArr;
					pB=posBrace;
					nArr=0;
					while(*pB) 
					{
						REAL X=0,Y=0,CX=0,CY=0;
						sscanf(pB,"%g,%g,%g,%g",&X,&Y,&CX,&CY);
						(*iParameters)[ret].m_pRectF[nArr].X=X;
						(*iParameters)[ret].m_pRectF[nArr].Y=Y;
						(*iParameters)[ret].m_pRectF[nArr].Width=CX;
						(*iParameters)[ret].m_pRectF[nArr++].Height=CY;
						while(*pB && *(pB++)!=';');
					}
				}
			}
			else
			switch(tmpType)
			{
			case DCPT_RECT:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_RECT;
				(*iParameters)[ret].dwNElements=1;
				(*iParameters)[ret].m_pRectF=new RectF(0,0,0,0);
				if (strncmp("RECT(",mStr,5)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_RECT|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_RECT|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("VAR(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_RECT|CompileVarSubtypeNames(posBrace2));
					}
					else
					{
						REAL X=0,Y=0,CX=0,CY=0;
						sscanf(posBrace,"%g,%g,%g,%g",&X,&Y,&CX,&CY);
						(*iParameters)[ret].m_pRectF->X=X;
						(*iParameters)[ret].m_pRectF->Y=Y;
						(*iParameters)[ret].m_pRectF->Width=CX;
						(*iParameters)[ret].m_pRectF->Height=CY;
					}
				}
				break;
			case DCPT_RECTX:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_NONE;
				if (strncmp("RECTX(",mStr,6)==0 && posBrace)
				{
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_RECTX|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_RECTX|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_RECTX|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				break;
			case DCPT_RECTY:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_NONE;
				if (strncmp("RECTY(",mStr,6)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_RECTY|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_RECTY|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_RECTY|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				break;
			case DCPT_RECTH:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_NONE;
				if (strncmp("RECTH(",mStr,6)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_RECTH|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_RECTH|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_RECTH|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				break;
			case DCPT_RECTW:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_NONE;
				if (strncmp("RECTW(",mStr,6)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_RECTW|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_RECTW|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_RECTW|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				break;
			case DCPT_DESTRECT:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTRECT|DCPT_REFERENCE);
				(*iParameters)[ret].dwNElements=0;
				if (strncmp("RECT(",mStr,5)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTRECT|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTRECT|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTRECT|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				else
				{
					(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTRECT|DCPT_REFERENCE);
					(*iParameters)[ret].m_Reference=0;
				}
				break;
			case DCPT_DESTRECTX:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_NONE;
				if (strncmp("RECTX(",mStr,6)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTRECTX|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTRECTX|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTRECTX|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				break;
			case DCPT_DESTRECTY:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_NONE;
				if (strncmp("RECTY(",mStr,6)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTRECTY|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTRECTY|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTRECTY|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				break;
			case DCPT_DESTRECTH:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_NONE;
				if (strncmp("RECTH(",mStr,6)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTRECTH|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTRECTH|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTRECTH|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				break;
			case DCPT_DESTRECTW:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_NONE;
				if (strncmp("RECTW(",mStr,6)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTRECTW|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTRECTW|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTRECTW|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				break;
			case DCPT_POINT:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_POINT;
				(*iParameters)[ret].dwNElements=1;
				(*iParameters)[ret].m_pPointF=new PointF(0,0);
				if (strncmp("POINT(",mStr,6)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_POINT|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_POINT|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("VAR(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_POINT|CompileVarSubtypeNames(posBrace2));
					}
					else
					{
						REAL X=0,Y=0;
						sscanf(posBrace,"%g,%g",&X,&Y);
						(*iParameters)[ret].m_pPointF->X=X;
						(*iParameters)[ret].m_pPointF->Y=Y;
					}
				}
				break;
			case DCPT_POINTX:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_NONE;
				if (strncmp("POINTX(",mStr,7)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_POINTX|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_POINTX|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_POINTX|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				break;
			case DCPT_POINTY:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_NONE;
				if (strncmp("POINTY(",mStr,7)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_POINTY|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_POINTY|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_POINTY|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				break;
			case DCPT_DESTPOINT:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTPOINT|DCPT_REFERENCE);
				if (strncmp("POINT(",mStr,6)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTPOINT|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTPOINT|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTPOINT|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				break;
			case DCPT_DESTPOINTY:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_NONE;
				if (strncmp("POINTY(",mStr,7)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTPOINTY|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTPOINTY|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTPOINTY|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				break;
			case DCPT_DESTPOINTX:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_NONE;
				if (strncmp("POINTX(",mStr,7)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTPOINTX|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTPOINTX|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTPOINTX|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				break;
			case DCPT_STRING:
				(*iParameters)[ret].dwParamType=DCPT_STRING;
				(*iParameters)[ret].dwNElements=1;
				(*iParameters)[ret].m_pCString=new CString;
				if (strncmp("STRING(",mStr,7)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_STRING|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_STRING|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						*(*iParameters)[ret].m_pCString=posBrace;
						if (*posBrace) *(*iParameters)[ret].m_pCString=(*iParameters)[ret].m_pCString->Mid(0,(*iParameters)[ret].m_pCString->GetLength()-1);
					}
				}
				break;	
			case DCPT_COLOR:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_COLOR;
				(*iParameters)[ret].dwNElements=1;
				(*iParameters)[ret].m_pColor=new Color(255,0,0,0);
				if (strncmp("CLR(",mStr,4)==0 && posBrace && (*posBrace!='C' || posBrace[5]!='_'))
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_COLOR|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_COLOR|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("HEX(",posBrace,4)==0 && posBrace2)
					{
						ARGB argb=0;
						sscanf(posBrace2,"%X",&argb);
						(*iParameters)[ret].m_pColor->SetValue(argb);
					}
					else
					if (*posBrace>64 && *posBrace<=127)
					{
						int nc=0;
						char tmpcmp[100];
						strncpy(tmpcmp,posBrace,90);
						char *tmpcmpbr=tmpcmp;
						while(*tmpcmpbr>64 && *tmpcmpbr<=127) tmpcmpbr++;
						*tmpcmpbr=0;
						for(nc=0;*CODContext::ccANamedColors[nc] && _stricmp(CODContext::ccANamedColors[nc],tmpcmp)!=0;nc++);
						(*iParameters)[ret].m_pColor->SetValue(CODContext::iANamedColors[nc]);
					}
					else
					{
						INT R=0,G=0,B=0,A=255;
						sscanf(posBrace,"%d,%d,%d,%d",&R,&G,&B,&A);
						(*iParameters)[ret].m_pColor->SetValue(Color::MakeARGB(A,R,G,B));
					}
				}
				else
				if (strncmp("CLRN(",mStr,5)==0 && posBrace)
				{
					if (strncmp("COLOR_",mStr,6)==0) posBrace=mStr;
					(*iParameters)[ret].dwParamType=(DCParamType)DCPT_COLOR;
					int nc=0;
					char tmpss[100];
					strncpy(tmpss,posBrace,90);
					char *tmpp=strchr(tmpss,')');
					if (tmpp) *tmpp=0;
					for(nc=0;*CODContext::ccANamedColors[nc] && _stricmp(CODContext::ccANamedColors[nc],tmpss)!=0;nc++);
					(*iParameters)[ret].m_pColor->SetValue(CODContext::iANamedColors[nc]);
				}
				else
				if ((strncmp("CLRS(",mStr,5)==0 && posBrace) || (posBrace && *posBrace=='C' && posBrace[5]=='_') || strncmp("COLOR_",mStr,6)==0)
				{
					if (strncmp("COLOR_",mStr,6)==0) posBrace=mStr;
					(*iParameters)[ret].dwParamType=(DCParamType)DCPT_COLOR;
					if (strncmp("HEX(",posBrace,4)==0 && posBrace2)
					{
						DWORD argb=0;
						sscanf(posBrace2,"%X",&argb);
						(*iParameters)[ret].m_pColor->SetFromCOLORREF(::GetSysColor(argb));
					}
					else
					if (strncmp("INT(",posBrace,4)==0 && posBrace2)
					{
						ARGB argb=0;
						sscanf(posBrace2,"%d",&argb);
						(*iParameters)[ret].m_pColor->SetFromCOLORREF(::GetSysColor(argb));
					}
					else
					{
						char tmpss[100];
						strncpy(tmpss,posBrace,90);
						char *tmpp=strchr(tmpss,')');
						if (tmpp) *tmpp=0;
						int nc=0;
						for(nc=0;*CDlgViewSystemMethods::chColorNames[nc] && _stricmp(CDlgViewSystemMethods::chColorNames[nc],tmpss)!=0;nc++);
						(*iParameters)[ret].m_pColor->SetFromCOLORREF(::GetSysColor(CDlgViewSystemMethods::uColorNames[nc]));
					}
				}
				else
				{
					if (*mStr>64 && *mStr<=127)
					{
						int nc=0;
						for(nc=0;*CODContext::ccANamedColors[nc] && _stricmp(CODContext::ccANamedColors[nc],mStr)!=0;nc++);
						(*iParameters)[ret].m_pColor->SetValue(CODContext::iANamedColors[nc]);
					}
					else
					if (*mStr=='0' && (mStr[1]=='x' || mStr[1]=='X'))
					{
						DWORD c=0;
						m_LastScanf=sscanf(mStr+2,"%X",&c);
						(*iParameters)[ret].m_pColor->SetValue(c);
					}
					else (*iParameters)[ret].m_pColor->SetValue(atoi(mStr));
				}
				break;
			case DCPT_DESTCOLOR:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTCOLOR|DCPT_REFERENCE);
				(*iParameters)[ret].dwNElements=1;
				if (strncmp("CLR(",mStr,4)==0 && posBrace)
				{
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTCOLOR|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTCOLOR|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTCOLOR|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				else
				{
					(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTCOLOR|DCPT_REFERENCE);
					(*iParameters)[ret].m_Reference=atoi(mStr);
				}
				break;
			case DCPT_PEN:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_PEN;
				(*iParameters)[ret].dwNElements=1;
				(*iParameters)[ret].m_pPen=NULL;
				if (strncmp("PEN(",mStr,4)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_PEN|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_PEN|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_PEN|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				else
				{
					(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_PEN|DCPT_REFERENCE);
					(*iParameters)[ret].m_Reference=atoi(mStr);
				}
				break;
			case DCPT_GUIOBJECT:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_GUIOBJECT|DCPT_REFERENCE);
				(*iParameters)[ret].dwNElements=0;
				(*iParameters)[ret].m_pGPUnit=NULL;

				if (strncmp("GUIOBJ(",mStr,7)==0 && posBrace && posBrace2)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_GUIOBJECT|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
						if ((*iParameters)[ret].m_Reference>=30000) (*iParameters)[ret].m_Reference=-1;
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_GUIOBJECT|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
				}
				else
				{
					if (!posBrace) posBrace=mStr;
					(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_GUIOBJECT|DCPT_REFERENCE);
					(*iParameters)[ret].m_Reference=atoi(posBrace);
					if ((*iParameters)[ret].m_Reference==0 && *posBrace!='0' && ipContext->m_CurDialogGPU)
					{
						UINT i;
						for(i=0;i<(*ipContext->m_CurDialogGPU)->m_NGPUNIT;i++)
							if (ipContext->m_CurDialogGPU[i] && _stricmp(posBrace,ipContext->m_CurDialogGPU[i]->m_ObjName)==0)
							{
								(*iParameters)[ret].m_Reference=i;
								i=(*ipContext->m_CurDialogGPU)->m_NGPUNIT;
							}
					}
				}
				break;
			case DCPT_IMAGELIST:
			case DCPT_IMAGE:
				{
					CString CSsrc=mStr;
					_strupr(mStr);
					if (strncmp("ILIST(",mStr,6)==0 && posBrace)
					{
						(*iParameters)[ret].dwParamType=DCPT_IMAGELIST;
						(*iParameters)[ret].dwNElements=-1;
						(*iParameters)[ret].m_pBitmap=NULL;
						(*iParameters)[ret].pAddParams=NULL;//new DCIPARAMETER [3];
						//::ZeroMemory((*iParameters)[ret].pAddParams,3*sizeof(DCIPARAMETER));
						DCParamType pta[]={DCPT_STRING,DCPT_INTEGER,DCPT_NONE};
						UINT tmpNParams=0;
						CODContextItem::TranslateParams(posBrace,pta,ipContext,&((*iParameters)[ret].pAddParams),&tmpNParams);
					}
					else
					{
						(*iParameters)[ret].dwParamType=DCPT_IMAGE;
						(*iParameters)[ret].dwNElements=1;
						(*iParameters)[ret].m_pBitmap=NULL;
						if (strncmp("BITMAP(",mStr,7)==0 && posBrace)
						{
							if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
							{
								(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_IMAGE|DCPT_REFERENCE);
								(*iParameters)[ret].m_Reference=atoi(posBrace2);
							}
							else
							if (strncmp("REF(",posBrace,4)==0 && posBrace2)
							{
								(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_IMAGE|DCPT_REFERENCE2);
								(*iParameters)[ret].m_Reference=atoi(posBrace2);
							}
							else
							{
								(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_IMAGE|DCPT_REFERENCE);
								(*iParameters)[ret].m_Reference=atoi(posBrace);
							}
						}
						else
						{
							(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_IMAGE|DCPT_REFERENCE);
							(*iParameters)[ret].m_Reference=atoi(mStr);
						}
					}
				}
				break;
			case DCPT_PATH:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_PATH;
				(*iParameters)[ret].dwNElements=1;
				(*iParameters)[ret].m_pPath=NULL;
				if (strncmp("PATH(",mStr,5)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_PATH|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_PATH|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_PATH|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				else
				{
					(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_PATH|DCPT_REFERENCE);
					(*iParameters)[ret].m_Reference=atoi(mStr);
				}
				break;
			case DCPT_REGION:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_REGION;
				(*iParameters)[ret].dwNElements=1;
				(*iParameters)[ret].m_pRegion=NULL;
				if (strncmp("REGION(",mStr,7)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_REGION|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_REGION|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_REGION|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				else
				{
					(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_REGION|DCPT_REFERENCE);
					(*iParameters)[ret].m_Reference=atoi(mStr);
				}
				break;
			case DCPT_DESTREGION:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTREGION|DCPT_REFERENCE);
				(*iParameters)[ret].dwNElements=0;
				(*iParameters)[ret].m_pDestRegion=NULL;
				if (strncmp("REGION(",mStr,7)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTREGION|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTREGION|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTREGION|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				else
				{
					(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTREGION|DCPT_REFERENCE);
					(*iParameters)[ret].m_Reference=atoi(mStr);
				}
				break;
			case DCPT_MATRIX:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_MATRIX|DCPT_REFERENCE);
				(*iParameters)[ret].dwNElements=0;
				(*iParameters)[ret].m_pMatrix=NULL;
				if (strncmp("MATRIX(",mStr,7)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_MATRIX|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_MATRIX|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strchr(posBrace,','))
					{
						(*iParameters)[ret].m_pMatrix=new CMatrixPlus(ipContext,posBrace);
						(*iParameters)[ret].dwParamType=DCPT_MATRIX;
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_MATRIX|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				else
				{
					(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_MATRIX|DCPT_REFERENCE);
					(*iParameters)[ret].m_Reference=atoi(mStr);
				}
				break;
			case DCPT_DESTMATRIX:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTMATRIX|DCPT_REFERENCE);
				(*iParameters)[ret].dwNElements=0;
				(*iParameters)[ret].m_pDestMatrix=NULL;
				if (strncmp("MATRIX(",mStr,7)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTMATRIX|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTMATRIX|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTMATRIX|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				else
				{
					(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTMATRIX|DCPT_REFERENCE);
					(*iParameters)[ret].m_Reference=atoi(mStr);
				}
				break;
			case DCPT_DESTSTRING:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTSTRING|DCPT_REFERENCE);
				(*iParameters)[ret].dwNElements=0;
				(*iParameters)[ret].m_pDestCString=NULL;
				if (strncmp("STRING(",mStr,7)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTSTRING|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTSTRING|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTSTRING|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				else
				{
					(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTSTRING|DCPT_REFERENCE);
					(*iParameters)[ret].m_Reference=atoi(mStr);
				}
				break;
			case DCPT_FONT:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_FONT;
				(*iParameters)[ret].dwNElements=1;
				(*iParameters)[ret].m_pFont=NULL;
				if (strncmp("FONT(",mStr,5)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_FONT|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_FONT|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_FONT|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				else
				{
					(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_FONT|DCPT_REFERENCE);
					(*iParameters)[ret].m_Reference=atoi(mStr);
				}
				break;
			case DCPT_BRUSH:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_BRUSH;
				(*iParameters)[ret].dwNElements=1;
				(*iParameters)[ret].m_pBrush=NULL;
				if (strncmp("BRUSH(",mStr,6)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_BRUSH|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_BRUSH|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_BRUSH|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				else
				{
					(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_BRUSH|DCPT_REFERENCE);
					(*iParameters)[ret].m_Reference=atoi(mStr);
				}
				break;
			case DCPT_SFORMAT:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_SFORMAT;
				(*iParameters)[ret].dwNElements=1;
				(*iParameters)[ret].m_pBrush=NULL;
				if (strncmp("SFORMAT(",mStr,8)==0 && posBrace)
				{
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_SFORMAT|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_SFORMAT|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_SFORMAT|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace);
					}
				}
				else
				{
					(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_SFORMAT|DCPT_REFERENCE);
					(*iParameters)[ret].m_Reference=atoi(mStr);
				}
				break;
			case DCPT_INTEGER:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_INTEGER;
				if (strncmp("INT(",mStr,4)==0 && posBrace)
				{
					(*iParameters)[ret].m_dword=atoi(posBrace);
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_INTEGER|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_INTEGER|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("VAR(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].m_dword=atoi(posBrace2);
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_INTEGER|CompileVarSubtypeNames(posBrace2));
					}
					else
					if (strncmp("HEX(",posBrace,4)==0 && posBrace2)
					{
						sscanf(posBrace2,"%X",&(*iParameters)[ret].m_dword);
					}
				}
				else
				if (strncmp("HEX(",mStr,4)==0 && posBrace)
				{
					sscanf(posBrace,"%X",&(*iParameters)[ret].m_dword);
				}
				else
				if (posBrace)	(*iParameters)[ret].m_dword=atoi(posBrace);
				else			(*iParameters)[ret].m_dword=atoi(mStr);
				break;
			case DCPT_DESTINTEGER:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTINTEGER|DCPT_REFERENCE);
				if (strncmp("INT(",mStr,4)==0 && posBrace)
				{
					(*iParameters)[ret].m_dword=atoi(posBrace);
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTINTEGER|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTINTEGER|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
				}
				else
				if (posBrace)	(*iParameters)[ret].m_Reference=atoi(posBrace);
				else			(*iParameters)[ret].m_Reference=atoi(mStr);
				break;
			case DCPT_FLAG:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_INTEGER;
				posBrace=mStr;
				if (strncmp("FLAG(",mStr,5)==0) posBrace=mStr+5;
				if (posBrace)
				{
					(*iParameters)[ret].m_dword=atoi(posBrace);
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_INTEGER|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_INTEGER|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("VAR(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].m_dword=atoi(posBrace2);
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_INTEGER|CompileVarSubtypeNames(posBrace2));
					}
					else
					{
						if ((*iParameters)[ret].m_dword==0 && *posBrace!='0')
						{
							UINT i;
							DCParamType cmpParam=(DCParamType)(DCPTF_MASK&pta[ret]);
							for(i=0;CODContextItem::iAFlag[i]!=cmpParam && CODContextItem::ccAFlagNames[i];i++);
							if (CODContextItem::ccAFlagNames[i])
							{
								CString tmpCS;
								const char **pNames=CODContextItem::ccAFlagNames[i];
								const DWORD *pDwords=CODContextItem::iAFlagValues[i];
								UINT j,k;
								if (CODContextItem::iAFlagStyles[i]==0) //single 
								{
									tmpCS=ExtractField(posBrace,1,")");
									for(j=0;*pNames[j] && _stricmp(tmpCS,pNames[j])!=0;j++);
									(*iParameters)[ret].m_dword=pDwords[j];
								}
								else
								if (CODContextItem::iAFlagStyles[i]==1) //multy
								{
									for(k=1;(tmpCS=ExtractField(posBrace,k,"|"))!="";k++)
									{
										for(j=0;*pNames[j] && _stricmp(tmpCS,pNames[j])!=0;j++);
										if (*pNames[j]) (*iParameters)[ret].m_dword|=pDwords[j];
									}
								}
							}
							else
							{
								CString tmpCS;
								tmpCS=ExtractField(posBrace,1,")");
								BOOL bDone=FALSE;
								for(i=0;CODContextItem::iAFlag[i]!=cmpParam && CODContextItem::ccAFlagNames[i] && !bDone;i++)
								{
									UINT j;
									for(j=0;*(CODContextItem::ccAFlagNames[i][j]) && _stricmp(CODContextItem::ccAFlagNames[i][j],tmpCS)!=0;j++)
										j=j;
									if (*(CODContextItem::ccAFlagNames[i][j]))
									{
										bDone=TRUE;
										(*iParameters)[ret].m_dword=CODContextItem::iAFlagValues[i][j];
									}
								}
							}
						}
					}
				}
				else
				if (posBrace)	(*iParameters)[ret].m_dword=atoi(posBrace);
				else			(*iParameters)[ret].m_dword=atoi(mStr);
				break;
			case DCPT_REAL:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=DCPT_REAL;
				if (strncmp("REAL(",mStr,5)==0 && posBrace)
				{
					(*iParameters)[ret].m_real=(REAL)atof(posBrace);
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_REAL|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_REAL|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("VAR(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].m_real=(REAL)atof(posBrace2);
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_REAL|CompileVarSubtypeNames(posBrace2));
					}
					else
					if (posBrace2)	(*iParameters)[ret].m_real=(REAL)atof(posBrace2);
					else			(*iParameters)[ret].m_real=(REAL)atof(posBrace);
				}
				else
				if (posBrace)	(*iParameters)[ret].m_real=(REAL)atof(posBrace);
				else			(*iParameters)[ret].m_real=(REAL)atof(mStr);
				break;
			case DCPT_DESTREAL:
				_strupr(mStr);
				(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTREAL|DCPT_REFERENCE);
				if (strncmp("REAL(",mStr,5)==0 && posBrace)
				{
					(*iParameters)[ret].m_real=(REAL)atof(posBrace);
					if (strncmp("IDX(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTREAL|DCPT_REFERENCE);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
					else
					if (strncmp("REF(",posBrace,4)==0 && posBrace2)
					{
						(*iParameters)[ret].dwParamType=(DCParamType)(DCPT_DESTREAL|DCPT_REFERENCE2);
						(*iParameters)[ret].m_Reference=atoi(posBrace2);
					}
				}
				else
				if (posBrace)	(*iParameters)[ret].m_Reference=atoi(posBrace);
				else			(*iParameters)[ret].m_Reference=atoi(mStr);
				break;
			default:
				(*iParameters)[ret].dwParamType=DCPT_NONE;
				break;
			}
			mStr=mNextStr;
		}
		delete []copyStr;
	}
	
	return *ioNParams=ret;
}

void CODContextItem::SetResult()
{
}

UINT CODContextItem::DoMethod(const char *iStr, char *oStr)
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
	while(*pos2 && *pos2!=',' && *pos2!='=') pos2++;
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
	case 0: //
	case 1: //

	default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
	}

	if (oStr && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);

	return nfunc;
}

ARGB CODContextItem::TranlateColor(const char *iStr)
{
	ARGB ret=0xFF000000;
	if (iStr)
	{
		const char *posBrace=strchr(iStr,'(');
		if (posBrace) posBrace++;
		const char *posBrace2=NULL;
		if (posBrace) posBrace2=strchr(posBrace,'(') ;
		if (posBrace2) posBrace2++;

		if (strncmp("HEX(",iStr,4)==0)
			sscanf(iStr+4,"%X",&ret);
		else
		if (*iStr=='0' && (iStr[1]=='x' || iStr[1]=='X'))
			sscanf(iStr+2,"%X",&ret);
		else
		if (*iStr>64 && *iStr<=127)
		{
			if ((iStr[0]=='D' || iStr[0]=='d') && (iStr[1]=='E' || iStr[1]=='e') && (iStr[2]=='F' || iStr[2]=='f'))
			{
				ret=0x10101;
			}
			else
			if ((iStr[0]=='R' || iStr[0]=='r') && (iStr[1]=='E' || iStr[1]=='e') && (iStr[2]=='S' || iStr[2]=='s'))
			{
				ret=0x10102;
			}
			else
			if (strncmp("COLOR_",iStr,6)==0)
			{
				int nc;
				for(nc=0;*CDlgViewSystemMethods::chColorNames[nc] && _stricmp(CDlgViewSystemMethods::chColorNames[nc],iStr)!=0;nc++);
				if (*CDlgViewSystemMethods::chColorNames[nc]) 
				{
					COLORREF clrr=::GetSysColor(CDlgViewSystemMethods::uColorNames[nc]);
					ret=MAKEARGB(0xFF,GetRValue(clrr),GetGValue(clrr),GetBValue(clrr));
				}
			}
			else
			if (strncmp("CLRS(",iStr,5)==0)
			{
				COLORREF clrr=::GetSysColor(atoi(iStr+5));
				ret=MAKEARGB(0xFF,GetRValue(clrr),GetGValue(clrr),GetBValue(clrr));
			}
			else
			{
				int nc=0;
				for(nc=0;*CODContext::ccANamedColors[nc] && _stricmp(CODContext::ccANamedColors[nc],iStr)!=0;nc++);
				if (*CODContext::ccANamedColors[nc]) ret=CODContext::iANamedColors[nc];
			}
		}
		else
		{
			INT R=0,G=0,B=0,A=255;
			sscanf(iStr,"%d,%d,%d,%d",&R,&G,&B,&A);
			ret=MAKEARGB(A,R,G,B);
		}
	}
	return ret;
}


