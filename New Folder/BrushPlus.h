// BrushPlus.h: interface for the CBrushPlus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BrushPlus_H__60A8D5E2_A0FB_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_BrushPlus_H__60A8D5E2_A0FB_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CODContext;

class CBrushPlus
{
public:
	virtual UINT DoMethod(const char *iStr, char *oStr);
    CBrushPlus(CODContext *ip_Context, IN const char *iStr);
    CBrushPlus(CODContext *ip_Context, IN const Color& color);
    CBrushPlus(CODContext *ip_Context, IN Image* image, IN WrapMode wrapMode = WrapModeTile);
    CBrushPlus(CODContext *ip_Context, IN Image* image, IN WrapMode wrapMode, IN const RectF &dstRect);
    CBrushPlus(CODContext *ip_Context, IN Image *image, IN const RectF &dstRect, IN const ImageAttributes *imageAttributes = NULL);
    CBrushPlus(CODContext *ip_Context, IN Image *image, IN const Rect &dstRect, IN const ImageAttributes *imageAttributes = NULL);
    CBrushPlus(CODContext *ip_Context, IN Image* image, IN WrapMode wrapMode, const IN Rect &dstRect);
    CBrushPlus(CODContext *ip_Context, IN Image* image, IN WrapMode wrapMode, IN REAL dstX, IN REAL dstY, IN REAL dstWidth, IN REAL dstHeight);
    CBrushPlus(CODContext *ip_Context, IN Image* image, IN WrapMode wrapMode, IN INT dstX, IN INT dstY, IN INT dstWidth, IN INT dstHeight);
    CBrushPlus(CODContext *ip_Context, IN const PointF& point1, IN const PointF& point2, IN const Color& color1, IN const Color& color2);
    CBrushPlus(CODContext *ip_Context, IN const Point& point1, IN const Point& point2, IN const Color& color1, IN const Color& color2);
    CBrushPlus(CODContext *ip_Context, IN const RectF& rect, IN const Color& color1, IN const Color& color2, IN LinearGradientMode mode);
    CBrushPlus(CODContext *ip_Context, IN const Rect& rect, IN const Color& color1, IN const Color& color2, IN LinearGradientMode mode);
    CBrushPlus(CODContext *ip_Context, IN const RectF& rect, IN const Color& color1, IN const Color& color2, IN REAL angle, IN BOOL isAngleScalable = FALSE);
    CBrushPlus(CODContext *ip_Context, IN const Rect& rect, IN const Color& color1, IN const Color& color2, IN REAL angle, IN BOOL isAngleScalable = FALSE);
    CBrushPlus(CODContext *ip_Context, IN HatchStyle hatchStyle, IN const Color& foreColor, IN const Color& backColor = Color());
    CBrushPlus(CODContext *ip_Context, IN const PointF* points, IN INT count, IN WrapMode wrapMode = WrapModeClamp);
    CBrushPlus(CODContext *ip_Context, IN const Point* points, IN INT count, IN WrapMode wrapMode = WrapModeClamp);
    CBrushPlus(CODContext *ip_Context, IN const GraphicsPath* path);
    CBrushPlus(CODContext *ip_Context, IN const CBrushPlus *iBrush);

	const Brush *SetBrush(Brush *pBrush);

	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];

	const static char *ccABrushType[];
	const static BrushType iABrushType[];
	const static char *ccAWrapMode[];
	const static WrapMode iAWrapMode[];
	const static char *ccAHatchStyle[];
	const static HatchStyle iAHatchStyle[];
	const static char *ccALinearGradientMode[];
	const static LinearGradientMode iALinearGradientMode[];

	CODContext *p_Context;
	virtual ~CBrushPlus();
	CString CreationString;
	Brush *m_Brush;
};

#endif // !defined(AFX_BrushPlus_H__60A8D5E2_A0FB_11D4_970E_0080AD863699__INCLUDED_)
