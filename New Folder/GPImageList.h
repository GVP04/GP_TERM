// GPImageList.h: interface for the GPImageList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPIMAGELIST_H__2C1E23E6_2A75_11D4_970D_0080AD863699__INCLUDED_)
#define AFX_GPIMAGELIST_H__2C1E23E6_2A75_11D4_970D_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBitmapPlus;

class GPImageList
{
public:
	HBITMAP CreateMaskBitmap(HDC hdc, HBITMAP hBitmap, COLORREF cTransparentColor);
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
	HBITMAP GPImageList::CreateBitmap(HWND iHWND, DWORD dwImageId, COLORREF clrBkg = CLR_NONE);
	HBITMAP GPImageList::CreateBitmap(DWORD dwImageId, COLORREF clrBkg = CLR_NONE);
	int DoMethod(const char *iStr, char *oStr);
	BOOL ReplaceFromILF(int nImage, const char *ifName,int nSImage);
	BOOL ReplaceFromFile(const char *iflanme, int nImg);
	BOOL AddFromFile(const char *iflanme, DWORD fuLoad, COLORREF clr);
	void DeleteList();
	static UINT CompileFlags(const char *iFlg);
	BOOL CreateIL(const char *iiName,int CX,int CY,int InitN,UINT iStyle);
	BOOL WriteList(const char *iFName);
	CImageList  m_IL;
	BOOL LoadList(const char *FName);
	BOOL LoadFromTIFF(const char *FName);
	CString ILName;
	CString ILFileName;
	GPImageList();
	CBitmapPlus *GetBitmap();
	CBitmapPlus *LoadBitmapPlus();
	CBitmapPlus *CreateBitmapPlus();

	GPImageList & operator= (const GPImageList &iGPIL)
	{
		if (this!=&iGPIL)
		{
			m_IL.DeleteImageList();
			if (iGPIL.m_IL.m_hImageList)
				m_IL.Create(CImageList::FromHandle(iGPIL.m_IL.m_hImageList));
			ILName=iGPIL.ILName;
		}
		return *this;
	}
	virtual ~GPImageList();
private:
	CBitmapPlus *m_Bitmap;
};

#endif // !defined(AFX_GPIMAGELIST_H__2C1E23E6_2A75_11D4_970D_0080AD863699__INCLUDED_)
