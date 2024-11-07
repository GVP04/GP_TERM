#pragma once

class CBitmapExt: public Bitmap
{
public:
	~CBitmapExt(void);
	CString CreationString;
	static CBitmapExt * CreateFromIL(const char *ccStr);

	CBitmapExt(IDirectDrawSurface7 * pIDDSurf7);
	CBitmapExt(INT width,INT height, Graphics *pTarget);
	CBitmapExt(BITMAPINFO *pgdiBitmapInfo, VOID *pgdiBitmapData);
	CBitmapExt(INT width, INT height, PixelFormat format);
	CBitmapExt(HBITMAP hbm, HPALETTE hpal);
	CBitmapExt(INT width, INT height, INT stride, PixelFormat format, BYTE *pscan0);
	CBitmapExt(WCHAR *pfilename, BOOL useIcm);
	CBitmapExt(HINSTANCE hInstance, WCHAR *pbitmapName);
	CBitmapExt(HICON hicon);
	CBitmapExt(IStream *pstream, BOOL useIcm);

};
