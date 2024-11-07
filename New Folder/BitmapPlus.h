#pragma once

class CODContext;

class CBitmapPlus
{
public:
	~CBitmapPlus(void);
	CString CreationString;

//	const static char *ccA[];
//	const static xxxx iA[];

	const static char *ccAPixelFormat[];
	const static PixelFormat iAPixelFormat[];

	const static char *ccAPropertyTagType[];
	const static WORD iAPropertyTagType[];

	const static char *ccAUnit[];
	const static Unit iAUnit[];

	const static char *ccAImageFlags[];
	const static ImageFlags iAImageFlags[];

	const static char *ccARotateFlipType[];
	const static RotateFlipType iARotateFlipType[];

	const static char *ccAEncoderParameterValueType[];
	const static EncoderParameterValueType iAEncoderParameterValueType[];

	const static char *ccAPropertyTag[];
	const static PROPID iAPropertyTag[];

	const static char *ccAEncoderParamType[];
	const static GUID iAEncoderParamType[];

	const static char *ccAPaletteFlags[];
	const static PaletteFlags iAPaletteFlags[];

	static const UINT uNMethods;
	static const char *cArrMethods[];
	static const char *cArrMethodsParams[];

	UINT DoMethod(const char *iStr, char *oStr);

	CBitmapPlus(CODContext *ip_Context, IDirectDrawSurface7 * pIDDSurf7);
	CBitmapPlus(CODContext *ip_Context, INT width,INT height, Graphics *pTarget);
	CBitmapPlus(CODContext *ip_Context, BITMAPINFO *pgdiBitmapInfo, VOID *pgdiBitmapData);
	CBitmapPlus(CODContext *ip_Context, INT width, INT height, PixelFormat format);
	CBitmapPlus(CODContext *ip_Context, HBITMAP hbm, HPALETTE hpal);
	CBitmapPlus(CODContext *ip_Context, INT width, INT height, INT stride, PixelFormat format, BYTE *pscan0);
	CBitmapPlus(CODContext *ip_Context, WCHAR *pfilename, BOOL useIcm);
	CBitmapPlus(CODContext *ip_Context, HINSTANCE hInstance, WCHAR *pbitmapName);
	CBitmapPlus(CODContext *ip_Context, HICON hicon);
	CBitmapPlus(CODContext *ip_Context, IStream *pstream, BOOL useIcm);
	CBitmapPlus(CODContext *ip_Context, DWORD dwType, const char *iStr);
	CBitmapPlus(CODContext *ip_Context, Bitmap *p_Bitmap, BOOL bClone);

	static PixelFormat TranslatePixelFormat(const char *iccFormat);
	static UINT GetPropertyDesc(const PropertyItem *pValue, char *oStr, DWORD dwLevel);
	static PROPID TranslatePropertyID(const char *iccID);
	static int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	static int GetEncoderClsid(const char* format, CLSID* pClsid);

	Bitmap *m_Bitmap;
	CODContext *p_Context;
	EncoderParameters *encoderParameters;
	union
	{
		ULONG parameterValue;
		ULONG parameterValueLong;
		BYTE parameterValueByte;
		char *parameterValueASCII;
		short parameterValueShort;
		REAL parameterValueRational;
		ULONG *parameterValueLongRange;
		ULONG parameterValueUndefined;
		REAL *parameterValueRationalRange;
		VOID *parameterValuePointer;
	};
	void Init();
	GUID encoderClsid;


};
