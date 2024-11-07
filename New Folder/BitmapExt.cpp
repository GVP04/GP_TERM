#include "stdafx.h"
#include "BitmapExt.h"


CBitmapExt::~CBitmapExt(void)
{
}

CBitmapExt * CBitmapExt::CreateFromIL(const char *ccStr)
{
			int nIcon=0,nImage=0;
			char name[200];*name=0;
			m_LastScanf=sscanf(pos,"%d,%d,%s",&nIcon,&nImage,name);
			m_BitmapArrString[nIcon]=pos;

			if (*name==0) strcpy(name,"MISCS");

			GPImageList *SMainIl;
			int ImgLId;
			if ((ImgLId=GPC.GetImageListId(name))>=0 && (SMainIl=&(GPC.a_GPImageList[ImgLId])))
				m_BitmapArr[nIcon]=(HICON)	SMainIl->m_IL.ExtractIcon(nImage);

	
	CreationString;
}

CBitmapExt(IDirectDrawSurface7 * pIDDSurf7) :Bitmap(pIDDSurf7)
{
}

CBitmapExt(INT width,INT height,Grpaphics *pTarget) :Bitmap(width, height, pTarget)
{
}

CBitmapExt(BITMAPINFO *pgdiBitmapInfo, VOID *pgdiBitmapData) :Bitmap(pgdiBitmapInfo, pgdiBitmapData)
{
}

CBitmapExt(INT width, INT height, PixelFormat format) :Bitmap(width, height, format)
{
}

CBitmapExt(HBITMAP hbm, HPALETTE hpal) :Bitmap(hbm, hpal)
{
}

CBitmapExt(INT width, INT height, INT stride, PixelFormat format, BYTE *pscan0) :Bitmap(width, height, stride, format, pscan0)
{
}

CBitmapExt(WCHAR *pfilename, BOOL useIcm) :Bitmap(pfilename, useIcm)
{
}

CBitmapExt(HINSTANCE hInstance, WCHAR *pbitmapName) :Bitmap(hInstance, pbitmapName)
{
}

CBitmapExt(HICON hicon) :Bitmap(hicon)
{
}

CBitmapExt(IStream *pstream, BOOL useIcm) :Bitmap(pstream, useIcm)
{
}
