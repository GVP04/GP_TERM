// GPImageList.cpp: implementation of the GPImageList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GP_Term.h"
#include "GPImageList.h"
#include "GP_TermDoc.h"
#include "DlgImageList.h"
#include <io.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const UINT GPImageList::uNMethods=31;
const char *GPImageList::cArrMethods[]={
/*00*/	"Create","Load","Delete","GetCount","SetBkColor",
/*05*/	"GetBkColor","GetImageInfo","SetImageCount","Add","AddFromFile",
/*10*/	"AddFromILFile","Remove","Replace","ReplaceFromFile","ReplaceFromILF",
/*15*/	"SetOverlay","Copy","Swap","SwapEx","CopyEx",
/*20*/	"SetDragCursor","Write","BeginDrag","DragEnter","EndDrag",
/*25*/	"DragLeave","DragMove","DragShowNolock","GetIconSize","SetIconSize",
/*30*/	"ShowEditDialog","","","","",
/*35*/	"","","","","",
/*40*/	"","","","","",
/*45*/	"","","","","",
/*50*/	"","","","","",
	};

const char *GPImageList::cArrMethodsParams[]={
/*00*/	"CX,CY,nIitial,Style","Name","","","R, G, B",
/*05*/	"","nImage","ImageCount","nImage,SName","FName[,Flags[,R,G,B]]",
/*10*/	"nImage,FName","nImage","nImage,SnImage,SName","nImage,FName","nImage,SnImage,FName",
/*15*/	"nImage,nOverlay","nSImage,nDImage","nSImage,nDImage","nSImage,nDImage,DName","nSImage,nDImage,DName",
/*20*/	"PX,PY,nImage","","PX,PY,nImage","IdDlg,IdObj,PX,PY","",
/*25*/	"IdDlg,IdObj,Name","PX,PY","","","PX,PY",
/*30*/	"[HWND]","","","","",
/*35*/	"","","","","",
/*40*/	"","","","","",
/*45*/	"","","","","",
/*50*/	"","","","","",
	};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPImageList::GPImageList()
{
	m_Bitmap=NULL;

}

GPImageList::~GPImageList()
{
	if (m_Bitmap) delete m_Bitmap;
	m_Bitmap=NULL;
}

CBitmapPlus *GPImageList::GetBitmap()
{
	if (!m_Bitmap) LoadBitmapPlus();
	if (!m_Bitmap) CreateBitmapPlus();
	if (!m_Bitmap) LoadBitmapPlus();
	return m_Bitmap;
}

CBitmapPlus *GPImageList::LoadBitmapPlus()
{
	if (ILFileName=="") ILFileName=ILName;
	CString csFD=ILFileName;
	csFD.MakeUpper();
	int i;
	i=csFD.Find(".GIL");
	if (i>0) csFD=ILFileName.Mid(0,i);
	else csFD=ILFileName;
	if (csFD.Find(".TIFF")<0) csFD+=".TIFF";
	BSTR bs=csFD.AllocSysString();

	if (m_Bitmap) delete m_Bitmap;
	m_Bitmap=new CBitmapPlus(NULL,bs,FALSE);
	if (m_Bitmap && (!m_Bitmap->m_Bitmap || m_Bitmap->m_Bitmap->GetLastStatus())) 
	{
		delete m_Bitmap;
		m_Bitmap=NULL;
	}

	::SysFreeString(bs);

	return m_Bitmap;
}

CBitmapPlus *GPImageList::CreateBitmapPlus()
{
	if (m_Bitmap) delete m_Bitmap;
	m_Bitmap=NULL;
	int i;
	CString csFD=ILFileName;
	csFD.MakeUpper();
	i=csFD.Find(".GIL");
	if (i>0) csFD=ILFileName.Mid(0,i);
	else csFD=ILFileName;
	csFD+=".TIFF";
	BSTR bs=csFD.AllocSysString();

//	GUID dimension = FrameDimensionPage;

	CLSID encoderClsid;
	CBitmapPlus::GetEncoderClsid(L"image/tiff", &encoderClsid);
	for(i=0;m_IL.m_hImageList && i<m_IL.GetImageCount();i++)
	{
		HICON tmpico;
		tmpico=m_IL.ExtractIcon(i);
		if (i==0)
		{
			m_Bitmap=new CBitmapPlus(NULL,tmpico);
			m_Bitmap->encoderParameters->Parameter[0].Guid = EncoderSaveFlag;
			m_Bitmap->encoderParameters->Parameter[0].Type = EncoderParameterValueTypeLong;
			m_Bitmap->parameterValue = EncoderValueMultiFrame;
			m_Bitmap->m_Bitmap->Save(bs, &encoderClsid, m_Bitmap->encoderParameters);
		}
		else
		if (m_Bitmap && m_Bitmap->m_Bitmap)
		{
			Bitmap mbmt(tmpico);
			m_Bitmap->parameterValue = EncoderValueFrameDimensionPage;
			m_Bitmap->m_Bitmap->SaveAdd(&mbmt,m_Bitmap->encoderParameters);
		}
		::DestroyIcon(tmpico);
	}
	if (m_Bitmap && m_Bitmap->m_Bitmap)
	{
		m_Bitmap->parameterValue = EncoderValueFlush;
		m_Bitmap->m_Bitmap->SaveAdd(m_Bitmap->encoderParameters);
	}
	if (m_Bitmap) delete m_Bitmap;
	m_Bitmap=NULL;
	::SysFreeString(bs);
	return m_Bitmap;
}

BOOL GPImageList::LoadList(const char *iFName)
{
	BOOL ret=FALSE;
	if (iFName && *iFName)
	{
		try
		{
			ILFileName=iFName;
			CString FName=ILFileName;
			FName.MakeUpper();
			if (FName.Find(".GIL",0)<0)	ILFileName="IMAGELISTS\\"+FName+".GIL";
			CFile   myFile;
			myFile.Open(ILFileName,CFile::modeRead|CFile::shareDenyNone,NULL);
			if (myFile.m_hFile!=CFile::hFileNull)
			{
				{
					CArchive ar(&myFile, CArchive::load);
					m_IL.DeleteImageList();
					if (m_IL.Read(&ar)>0)
					{
						ILName=iFName;
						ret=TRUE;
						FName=ILFileName.Mid(0,ILFileName.Find(".GIL",0))+".TIFF";
						if (_access(FName,0)<0) CreateBitmapPlus();
					}
				}
				myFile.Close();
			}
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("GPImageList", "LoadList",iFName);
			ret=FALSE;
		}
		if (!ret)
		{
			try
			{
				ILFileName=iFName;
				CString FName=ILFileName;
				FName.MakeUpper();
				int i;
				if ((i=FName.Find(".GIL",0))>0)
				{
					ILFileName=iFName;
					ILFileName=ILFileName.Mid(0,i)+".TIFF";
					FName=ILFileName;
					FName.MakeUpper();
				}

				if (FName.Find(".TIFF",0)<0)	ILFileName="IMAGELISTS\\"+FName+".TIFF";
				ret=LoadFromTIFF(ILFileName);
				if (ret) ILName=iFName;
			}
			catch(...)
			{
				GPC.m_ErrReport.GPWriteErrorLog("GPImageList", "LoadList TIFF",iFName);
				ret=FALSE;
			}

		}
	}
	return ret;
}
BOOL GPImageList::LoadFromTIFF(const char *FName)
{
	BOOL ret=FALSE;
	LoadBitmapPlus();
	if (m_Bitmap)
	{
		//	GUID dimension = FrameDimensionPage;
		CLSID encoderClsid;
		CBitmapPlus::GetEncoderClsid(L"image/tiff", &encoderClsid);
		UINT i,nFrames=m_Bitmap->m_Bitmap->GetFrameCount(&FrameDimensionPage);
		UINT CX=m_Bitmap->m_Bitmap->GetHeight();
		UINT CY=m_Bitmap->m_Bitmap->GetWidth();

		try	{m_IL.DeleteImageList();}	catch(...)	{GPC.m_ErrReport.GPWriteErrorLog("GPImageList", "CreateIL 220",FName);}
		try	{m_IL.Create(CX,CY,ILC_COLOR32|ILC_MASK,0,0);}	catch(...){	GPC.m_ErrReport.GPWriteErrorLog("GPImageList", "CreateIL 222",FName);}

		if (m_IL.m_hImageList)
		{
			for(i=0;i<nFrames;i++)
			{
				m_Bitmap->m_Bitmap->SelectActiveFrame(&FrameDimensionPage,i);
				HICON hIcon=NULL;
				m_Bitmap->m_Bitmap->GetHICON(&hIcon);
				m_IL.Add(hIcon);
				::DestroyIcon(hIcon);
			}
			ret=m_IL.GetImageCount()>0;
		}
	}

	return m_Bitmap!=NULL;
}


BOOL GPImageList::WriteList(const char *iFName)
{
	if (iFName && *iFName) ILFileName=iFName;
	CString FName=ILFileName;
	FName.MakeUpper();
	BOOL ret=FALSE;
	try
	{
		if (FName.Find(".GIL",0)<0)	ILFileName="IMAGELISTS\\"+FName+".GIL";

		CFile myFile;
		myFile.Open(ILFileName,CFile::modeCreate | CFile::modeWrite,NULL);
		if (myFile.m_hFile!=CFile::hFileNull)
		{
			{
				CArchive ar(&myFile, CArchive::store);
				m_IL.SetImageCount(m_IL.GetImageCount());
				m_IL.Write(&ar);
			}
			ret=TRUE;
			myFile.Close();
		}
	}
	catch(...)
	{
#ifdef RUS
		CString err="Ошибка загрузки списка изображений - IMAGELISTS\\"+FName+".GIL";
#else
		CString err="Error loading IMAGELISTS\\"+FName+".GIL";
#endif
		GPC.m_ErrReport.GPWriteErrorLog("GPImageList", "WriteList",err);
		AfxMessageBox(err);
		ret=FALSE;
	}

	return ret;
}

BOOL GPImageList::CreateIL(const char *iName, int CX, int CY, int InitN, UINT iStyle)
{
	BOOL ret=FALSE;
	try
	{m_IL.DeleteImageList();}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPImageList", "CreateIL 139",iName);
	}

	try
	{
		if(m_IL.Create(CX,CY,iStyle,InitN,0)>0)
		{
			ret=TRUE;
			ILName=iName;
		}
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPImageList", "CreateIL 152",iName);
	}

	return ret;
}

UINT GPImageList::CompileFlags(const char *iFlg)
{
	char *cfl[]={"_COLOR","_COLOR4","_COLOR8","_COLOR16","_COLOR24","_COLOR32","_COLORDDB","_MASK","_MIRROR","_PERITEMMIRROR",};
	UINT  ufl[]={ILC_COLOR,ILC_COLOR4,ILC_COLOR8,ILC_COLOR16,ILC_COLOR24,ILC_COLOR32,ILC_COLORDDB,ILC_MASK,ILC_MIRROR,ILC_PERITEMMIRROR,};
	UINT retFlg=0;

	int i;
	for(i=0; i<10;i++) 
		if (strstr(iFlg,cfl[i])!=NULL) retFlg|=ufl[i];

	return retFlg;
}

void GPImageList::DeleteList()
{
	try
	{m_IL.DeleteImageList();}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPImageList", "DeleteList",ILName);
	}

	ILName="";
}

BOOL GPImageList::AddFromFile(const char *iflanme, DWORD fuLoad, COLORREF clr = RGB(255,255,255))
{
	CString flanme=iflanme;
	BOOL ret=FALSE;
	if (m_IL.m_hImageList)
	{
		try
		{
			int cx=16,cy=16;
			::ImageList_GetIconSize(m_IL.m_hImageList,&cx,&cy);

			if (flanme.Find(".ico",0)>0 || flanme.Find(".ICO",0)>0)
			{
				HANDLE bicHANDLE;
				if (fuLoad==0) fuLoad=LR_LOADMAP3DCOLORS;
				fuLoad|=LR_LOADFROMFILE;
				bicHANDLE= LoadImage( NULL, flanme, IMAGE_ICON, cx, cy,fuLoad);
				if (bicHANDLE)
				{
					m_IL.Add( (HICON) bicHANDLE );
					DestroyIcon((HICON)bicHANDLE);
				}
			}
			else
			if (flanme.Find(".cur",0)>0 || flanme.Find(".CUR",0)>0)
			{
				HANDLE bicHANDLE;
				CBitmap bm;
				if (fuLoad==0) fuLoad=LR_LOADMAP3DCOLORS;
				fuLoad|=LR_LOADFROMFILE;
				bicHANDLE= LoadImage( NULL, flanme,  IMAGE_CURSOR, cx, cy, fuLoad);

				if (bicHANDLE)
				{
					bm.Attach((HCURSOR)bicHANDLE);
					m_IL.Add( &bm,clr);
					bm.Detach( );
					DestroyCursor((HCURSOR)bicHANDLE);
				}
			}
			else
			{
				BSTR m_fName=flanme.AllocSysString();
				Bitmap img(m_fName,0);
				SysFreeString(m_fName);
				HBITMAP hbmp=NULL;

				HWND hwndDesktop=GetDesktopWindow();
				HDC hdcDesktop = GetDC(hwndDesktop); 
				HDC hdcMem = CreateCompatibleDC(hdcDesktop); 
				HBITMAP hbmOld; 
				hbmp = ::CreateCompatibleBitmap(hdcDesktop, cx, cy); 
				hbmOld = (HBITMAP)::SelectObject(hdcMem, hbmp); 
				{
					Color cccc(GetRValue(clr),GetGValue(clr),GetBValue(clr));
					Graphics graphics(hdcMem);
					graphics.Clear(cccc);
					graphics.DrawImage(&img, 0, 0,cx, cy);
				}
				::SelectObject(hdcMem, hbmOld); 
				::DeleteDC(hdcMem); 

				if (hbmp)
				{
					HBITMAP hbMask=CreateMaskBitmap(hdcDesktop,hbmp,clr);
					//ImageList_Add(m_IL.m_hImageList,hbmp,clr);
					ImageList_Add(m_IL.m_hImageList,hbmp,hbMask);

					if (hbMask) ::DeleteObject((HBITMAP)hbMask);
					::DeleteObject((HBITMAP)hbmp);
					ret=TRUE;
				}
				::ReleaseDC(hwndDesktop, hdcDesktop); 
			}
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("GPImageList", "AddFromFile",iflanme);
		}
	}

	return ret;
}

BOOL GPImageList::ReplaceFromFile(const char *iflanme, int nImg)
{
	CString flanme=iflanme;
	BOOL ret=FALSE;
	if (m_IL.m_hImageList)
	{
		try
		{
			int cx=16,cy=16;
			::ImageList_GetIconSize(m_IL.m_hImageList,&cx,&cy);
			
			if (m_IL.GetImageCount()>nImg)
			{

				if (flanme.Find(".ico",0)>0 || flanme.Find(".ICO",0)>0)
				{
					HANDLE bicHANDLE;
					bicHANDLE= LoadImage( NULL, flanme,  IMAGE_ICON, cx, cy, LR_LOADFROMFILE|LR_DEFAULTCOLOR|LR_LOADMAP3DCOLORS|LR_DEFAULTSIZE  );
					m_IL.Replace(nImg, (HICON) bicHANDLE );
					DestroyCursor((HICON)bicHANDLE);
				}
				else
					/*
				if (flanme.Find(".bmp",0)>0 || flanme.Find(".BMP",0)>0)
				{
					HANDLE bicHANDLE;
					CBitmap bm;
					bicHANDLE= LoadImage( NULL, flanme,  IMAGE_BITMAP, cx, cy, LR_LOADFROMFILE  );
					bm.Attach((HBITMAP)bicHANDLE);
					m_IL.Replace(nImg,&bm,NULL);
					bm.Detach( );
					DeleteObject((HBITMAP)bicHANDLE);
				}
				else
				*/
			{
				COLORREF clr=m_IL.GetBkColor();
				BSTR m_fName=flanme.AllocSysString();
				Bitmap img(m_fName,0);
				SysFreeString(m_fName);
				HBITMAP hbmp=NULL;

				HWND hwndDesktop=GetDesktopWindow();
				HDC hdcDesktop = GetDC(hwndDesktop); 
				HDC hdcMem = CreateCompatibleDC(hdcDesktop); 
				HBITMAP hbmOld; 
				hbmp = ::CreateCompatibleBitmap(hdcDesktop, cx, cy); 
				hbmOld = (HBITMAP)::SelectObject(hdcMem, hbmp); 
				{
					Color cccc(GetRValue(clr),GetGValue(clr),GetBValue(clr));
					Graphics graphics(hdcMem);
					graphics.Clear(cccc);
					graphics.DrawImage(&img, 0, 0,cx, cy);
				}
				::SelectObject(hdcMem, hbmOld); 
				::DeleteDC(hdcMem); 

				if (hbmp)
				{
					HBITMAP hbMask=CreateMaskBitmap(hdcDesktop,hbmp,clr);
					//ImageList_Add(m_IL.m_hImageList,hbmp,clr);
					ImageList_Replace(m_IL.m_hImageList,nImg,hbmp,hbMask);

					if (hbMask) ::DeleteObject((HBITMAP)hbMask);
					::DeleteObject((HBITMAP)hbmp);
					ret=TRUE;
				}
				::ReleaseDC(hwndDesktop, hdcDesktop); 
			}


				ret=TRUE;
			}
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("GPImageList", "ReplaceFromFile",iflanme);
		}
	}

	return ret;
}

BOOL GPImageList::ReplaceFromILF(int nImage, const char *fName, int nSImage)
{
	GPImageList tmp;
	BOOL ret=tmp.LoadList(fName);
	if (ret==TRUE && m_IL.Replace(nImage,(HICON)(tmp.m_IL.ExtractIcon(nSImage)))<0) ret=FALSE;
	return ret;
}

int GPImageList::DoMethod(const char *iStr, char *oStr)
{
	char met[150];
	strncpy(met,iStr,145);
	met[145]=0;
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc=0;

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
	try
	{
		switch(nfunc)
		{
		case  0: /*Create*/
			{
				int nImage1=0,x=16,y=16;
				m_LastScanf=sscanf(pos,"%d,%d,%d",&x,&y,&nImage1);
				CString Name=ExtractField(pos,4,",");
				retint=CreateIL(Name,x,y,nImage1,GPImageList::CompileFlags(ExtractField(pos,3,",")));
			}
			break;
		case  1: /*Load*/
			retint=LoadList(pos);
			break;
		case  2: /*Delete*/
			DeleteList();
			break;
		case  3: /*GetCount*/
			if (oStr) retint=m_IL.GetImageCount();
			break;
		case  4: /*SetBkColor*/
			{
				int r=0,g=0,b=0;
				m_LastScanf=sscanf(pos,"%d,%d,%d",&r,&g,&b);
				retint=m_IL.SetBkColor(RGB(r,g,b));
			}
			break;
		case  5: /*GetBkColor*/
			if (oStr)
			{
				COLORREF clr=m_IL.GetBkColor();
				sprintf(oStr,"%d\x7F%d\x7F%d\r",GetRValue(clr),GetGValue(clr),GetBValue(clr));
			}
			break;
		case  6: /*GetImageInfo*/
			if (oStr)
			{
				IMAGEINFO ImIn={0};
				retint=m_IL.GetImageInfo(atoipos,&ImIn);
				sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d\x7F%d\x07%d\x7F%d\x7F%d\r",
				(DWORD)ImIn.hbmImage,(DWORD)ImIn.hbmMask,ImIn.Unused1,ImIn.Unused2,
				ImIn.rcImage.top,ImIn.rcImage.left,ImIn.rcImage.bottom,ImIn.rcImage.right);
			}
			break;
		case  7: /*SetImageCount*/
			if (m_IL.m_hImageList)
				retint=m_IL.SetImageCount(atoipos);
			break;
		case  8: /*Add*/
			if (m_IL.m_hImageList)
			{
				retint=0;
				const char *Name=FindField(pos,2,",");
				GPImageList *SMainIl;
				int ImgLId=-1;
				if (*Name && (ImgLId=GPC.GetImageListId(Name))>=0 && (SMainIl=&(GPC.a_GPImageList[ImgLId]))!=NULL)
					retint=m_IL.Add((HICON)(GPC.a_GPImageList[ImgLId].m_IL.ExtractIcon(atoipos)));
			}
			break;
		case  9: /*AddFromFile FName[,Flags[,R,G,B]]*/
			{
				int R=255,G=255,B=255;
				m_LastScanf=sscanf(FindField(pos,3,","),"%d,%d,%d",&R,&G,&B);
				CString flg=ExtractField(pos,2,",");
				DWORD uFl=0;
				flg.MakeUpper();
				if (flg.Find("BS",0)>=0) uFl|=LR_CREATEDIBSECTION;
				if (flg.Find("3D",0)>=0) uFl|=LR_LOADMAP3DCOLORS;
				if (flg.Find("TR",0)>=0) uFl|=LR_LOADTRANSPARENT;
				if (flg.Find("MO",0)>=0) uFl|=LR_MONOCHROME;
				if (flg.Find("V",0)>=0) uFl|=LR_VGACOLOR;

				retint=AddFromFile(ExtractField(pos,1,","),uFl,RGB(R,G,B));
			}
			break;
		case 10: /*AddFromILFile*/
			if (m_IL.m_hImageList)
			{
				CString Name=ExtractField(pos,2,",");
				GPImageList SMainIl;
				SMainIl.LoadList(Name);
				retint=m_IL.Add((HICON)(SMainIl.m_IL.ExtractIcon(atoipos)));
			}
			break;
		case 11: /*Remove*/	
			if (m_IL.m_hImageList)
				retint=m_IL.Remove(atoipos);
			break;
		case 12: /*Replace*/
			if (m_IL.m_hImageList)
			{
				retint=0;
				const char *Name=FindField(pos,3,",");
				int nImage1=0,nImage2=0;
				m_LastScanf=sscanf(pos,"%d,%d",&nImage1,&nImage2);
				if (*Name==0) Name="MISCS";
				int ImgLId=0;
				GPImageList *SMainIl;
				if ((ImgLId=GPC.GetImageListId(Name))>=0 && (SMainIl=&(GPC.a_GPImageList[ImgLId]))!=NULL)
					retint=m_IL.Replace(nImage1,(HICON)(SMainIl->m_IL.ExtractIcon(nImage2)));
			}
			break;
		case 13: /*ReplaceFromFile*/
			{
				CString Name=ExtractField(pos,2,",");
				retint=ReplaceFromFile(Name,atoipos);
			}
			break;
		case 14: /*ReplaceFromILF*/
			{
				int nImage1=0,nImage2=0;
				m_LastScanf=sscanf(pos,"%d,%d",&nImage1,&nImage2);
				CString Name=ExtractField(pos,3,",");
				retint=ReplaceFromILF(nImage1,Name,nImage2);
			}
			break;
		case 15: /*SetOverlay*/
			if (m_IL.m_hImageList)
			{
				int nImage1=0,nImage2=0;
				m_LastScanf=sscanf(pos,"%d,%d",&nImage1,&nImage2);
				retint=m_IL.SetOverlayImage(nImage1,nImage2);
			}
			break;
		case 16: /*Copy*/
			if (m_IL.m_hImageList)
			{
				int nImage1=0,nImage2=0;
				m_LastScanf=sscanf(pos,"%d,%d",&nImage1,&nImage2);
				retint=m_IL.Copy(nImage1,nImage2,ILCF_MOVE);
			}
			break;
		case 17: /*Swap*/
			if (m_IL.m_hImageList)
			{
				int nImage1=0,nImage2=0;
				m_LastScanf=sscanf(pos,"%d,%d",&nImage1,&nImage2);
				retint=m_IL.Copy(nImage1,nImage2,ILCF_SWAP);
			}
			break;
		case 18: /*SwapEx*/
			if (m_IL.m_hImageList)
			{
				retint=0;
				CString Name=ExtractField(pos,3,",");
				int nImage1=0,nImage2=0;
				m_LastScanf=sscanf(pos,"%d,%d",&nImage1,&nImage2);
				GPImageList *SMainIl;
				int ImgLId=-1;
				if ((ImgLId=GPC.GetImageListId(Name))>=0 && (SMainIl=&(GPC.a_GPImageList[ImgLId]))!=NULL)
					retint=m_IL.Copy(nImage1,&(SMainIl->m_IL),nImage1,ILCF_SWAP);
			}
			break;
		case 19: /*CopyEx*/
			if (m_IL.m_hImageList)
			{
				retint=0;
				CString Name=ExtractField(pos,3,",");
				int nImage1=0,nImage2=0;
				m_LastScanf=sscanf(pos,"%d,%d",&nImage1,&nImage2);
						
				GPImageList *SMainIl;
				int ImgLId=-1;
				if ((ImgLId=GPC.GetImageListId(Name))>=0 && (SMainIl=&(GPC.a_GPImageList[ImgLId]))!=NULL)
					retint=m_IL.Copy(nImage1,&(SMainIl->m_IL),nImage1,ILCF_MOVE);
			}
			break;
		case 20: /*SetDragCursor*/
			if (m_IL.m_hImageList)
			{
				int nImage1=0;
				POINT po;
				po.x=po.y=16;
				m_LastScanf=sscanf(pos,"%d,%d,%d",&po.x,&po.y,&nImage1);
						
				retint=m_IL.SetDragCursorImage(nImage1,po);
			}
			break;
		case 21: /*Write*/	retint=WriteList(pos);	break;
		case 22: /*BeginDrag*/
			if (m_IL.m_hImageList)
			{
				int nImage1=0;
				POINT po;
				po.x=po.y=16;
				m_LastScanf=sscanf(pos,"%d,%d,%d",&po.x,&po.y,&nImage1);
				retint=m_IL.BeginDrag(nImage1,po);
			}
			break;
		case 23: /*DragEnter*/
			if (m_IL.m_hImageList)
			{
				retint=0;
				int IdDlg=0,IdObj=0;
				POINT po;
				po.x=po.y=16;
				m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&IdDlg,&IdObj,&po.x,&po.y);

				if (IdDlg<MAX_OBJDLG)
				{
					GPUnit *tmp=NULL;
					if (GPC.m_Document->a_GPObjType[IdDlg]==0)
					{
						if (GPC.m_Document->a_GPObjDialog[IdDlg]!=NULL)
							tmp=GPC.m_Document->a_GPObjDialog[IdDlg]->GetUnit(IdObj);
					}
					else
					{
						if (GPC.m_Document->a_GPObjFrame[IdDlg]!=NULL)
							tmp=GPC.m_Document->a_GPObjFrame[IdDlg]->GetUnit(IdObj);
					}
					
					if (tmp!=NULL && tmp->UnitHWND!=NULL) 
						retint=m_IL.DragEnter(CWnd::FromHandle(tmp->UnitHWND),po);
				}
			}
			break;
		case 24: /*EndDrag*/
			if (m_IL.m_hImageList)	m_IL.EndDrag();
			break;
		case 25: /*DragLeave*/
			if (m_IL.m_hImageList)
			{
				retint=0;
				int IdDlg=0,IdObj=0;
				m_LastScanf=sscanf(pos,"%d,%d",&IdDlg,&IdObj);

				if (IdDlg<MAX_OBJDLG)
				{
					GPUnit *tmp=NULL;
					if (GPC.m_Document->a_GPObjType[IdDlg]==0)
					{
						if (GPC.m_Document->a_GPObjDialog[IdDlg]!=NULL)
							tmp=GPC.m_Document->a_GPObjDialog[IdDlg]->GetUnit(IdObj);
					}
					else
					{
						if (GPC.m_Document->a_GPObjFrame[IdDlg]!=NULL)
							tmp=GPC.m_Document->a_GPObjFrame[IdDlg]->GetUnit(IdObj);
					}

					if (tmp && tmp->UnitHWND) 
						retint=m_IL.DragLeave(CWnd::FromHandle(tmp->UnitHWND));
				}
			}
			break;
		case 26: /*DragMove*/
			if (m_IL.m_hImageList)
			{
				POINT po;
				po.x=po.y=16;
				m_LastScanf=sscanf(pos,"%d,%d",&po.x,&po.y);
				retint=m_IL.DragMove(po);
			}
			break;
		case 27: /*DragShowNolock*/	retint=m_IL.DragShowNolock(atoipos);	break;
		case 28: /*GetIconSize*/
			if (m_IL.m_hImageList && oStr)
			{
				int cx=0,cy=0;
				::ImageList_GetIconSize(m_IL.m_hImageList,&cx,&cy);
				sprintf(oStr,"%d\x7F%d",cx,cy);
			}
			break;
		case 29: /*SetIconSize*/
			if (m_IL.m_hImageList)
			{
				int cx=0,cy=0;
				retint=::ImageList_SetIconSize(m_IL.m_hImageList,cx,cy);
			}
			break;
		case 30: /*ShowEditDialog  [IdDlg or HWND][,FileName]*/
			{
				HWND hWParent;
				if (*pos && ::IsWindow((HWND)atoipos)) hWParent=(HWND)atoipos;
				else hWParent=::GetLastActivePopup(GPC.m_hViewWnd);
				CDlgImageList dlg(CWnd::FromHandle(hWParent));
				dlg.DoModal();
			}
			break;

		default:
			GPC.m_ErrReport.GPWriteWarnLog2("ImageList", "Unknown Method",iStr);
			if (oStr) sprintf(oStr,ErrObjSub,met); nfunc=0xFFFFFFFFL; 
			break;
		}
	}catch(...)
	{
		char *str=new char [(int)strlen(pos)+1000];
		#ifdef RUS
			sprintf(str,"Ошибка выполнения метода %s %s",met,pos);
			::MessageBox(GPC.m_hViewWnd,str,"Ошибка метода",MB_OK|MB_ICONEXCLAMATION);
		#else
			sprintf(str,"Error execution of method %s %s",met,pos);
			::MessageBox(GPC.m_hViewWnd,str,"Error execution",MB_OK|MB_ICONEXCLAMATION);
		#endif
		nfunc=0xFFFFFFFFL;
		GPC.m_ErrReport.GPWriteErrorLog("GPImageList", "DoMethod",iStr);
		if (oStr) strcpy(oStr,str);
		delete[] str;
	}

	if (oStr && *oStr==0)
	{
		if (retint!=-123456)
			sprintf(oStr,"%d",retint);
	}

	return nfunc;
}

HBITMAP GPImageList::CreateBitmap(DWORD dwImageId, COLORREF clrBkg) 
{ 
	return CreateBitmap( GetDesktopWindow(), dwImageId, clrBkg);
}

HBITMAP GPImageList::CreateBitmap(HWND hwndDesktop, DWORD dwImageId, COLORREF clrBkg) 
{ 
    HDC hdcDesktop = GetDC(hwndDesktop); 
    HDC hdcMem = CreateCompatibleDC(hdcDesktop); 
    HBITMAP hbmOld; 
    HBITMAP hbmRet=NULL; 
	HBRUSH hbrOld=NULL; 

 
    // Create a brush using the menu background color, 
    // and select it into the memory DC. 
	int cx=16,cy=16;
	::ImageList_GetIconSize(m_IL.m_hImageList,&cx,&cy);

    // Create the bitmaps. Select each one into the memory 
    // DC that was created and draw in it. 

    hbmRet = ::CreateCompatibleBitmap(hdcDesktop, cx, cy); 
    hbmOld = (HBITMAP)::SelectObject(hdcMem, hbmRet); 
	if (clrBkg!=CLR_NONE) 
		hbrOld = (HBRUSH)::SelectObject(hdcMem, CreateSolidBrush(clrBkg)); 

	::PatBlt(hdcMem, 0, 0, cx, cy, PATCOPY); 
	POINT pt={0};
	POINT ptOrigin={0};
	SIZE sz={0};
	sz.cx=cx;
	sz.cy=cy;
	m_IL.DrawIndirect(CDC::FromHandle(hdcMem), dwImageId, pt, sz, ptOrigin, ILD_TRANSPARENT,clrBkg,CLR_DEFAULT);

//ILD_NORMAL (0x00000000)Draws the image using the background color for the image list. If the background color is the CLR_NONE value, the image is drawn transparently using the mask. 
//ILD_TRANSPARENT (0x00000001)Draws the image transparently using the mask, regardless of the background color. This value has no effect if the image list does not contain a mask. 
//ILD_BLEND25 (0x00000002)Draws the image, blending 25 percent with the blend color specified by rgbFg. This value has no effect if the image list does not contain a mask. 
//ILD_FOCUS (0x00000002)Same as ILD_BLEND25. 
//ILD_BLEND50 (0x00000004)Draws the image, blending 50 percent with the blend color specified by rgbFg. This value has no effect if the image list does not contain a mask. 
//ILD_SELECTED (0x00000004)Same as ILD_BLEND50. 
//ILD_BLEND (0x00000004)Same as ILD_BLEND50. 
//ILD_MASK (0x00000010)Draws the mask. 
//ILD_IMAGE (0x00000020)If the overlay does not require a mask to be drawn, set this flag. 
//ILD_ROP (0x00000040)Draws the image using the raster operation code specified by the dwRop member. 
//ILD_OVERLAYMASK (0x00000F00)To extract the overlay image from the fStyle member, use the logical AND to combine fStyle with the ILD_OVERLAYMASK value. 
//ILD_PRESERVEALPHA (0x00001000)Preserves the alpha channel in the destination.
//ILD_SCALE (0x00002000)Causes the image to be scaled to cx, cy instead of being clipped.
//ILD_DPISCALE (0x00004000)

	 ::SelectObject(hdcMem, hbmOld); 
	 if (hbrOld) ::DeleteObject(::SelectObject(hdcMem, hbrOld)); 

 
    // Delete the memory DC and release the desktop DC. 
	::DeleteDC(hdcMem); 
	::ReleaseDC(hwndDesktop, hdcDesktop); 
	return hbmRet;
} 


HBITMAP GPImageList::CreateMaskBitmap(HDC hdc, HBITMAP hBitmap, COLORREF cTransparentColor)
{
   BITMAP     bm;
   HBITMAP    bmAndObject,bmSaveOld, bmObjectOld;
   HDC        hdcObject, hdcTemp;
   POINT      ptSize;

   hdcTemp = CreateCompatibleDC(hdc);
   bmSaveOld=(HBITMAP)::SelectObject(hdcTemp, hBitmap);   // Select the bitmap
   ::GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);
   ptSize.x = bm.bmWidth;            // Get width of bitmap
   ptSize.y = bm.bmHeight;           // Get height of bitmap
   ::DPtoLP(hdcTemp, &ptSize, 1);      // Convert from device
                                     // to logical points
   // Create some DCs to hold temporary data.
   hdcObject = ::CreateCompatibleDC(hdc);

   // GDI functions.
   // Monochrome DC
   bmAndObject = ::CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);


   // Each DC must select a bitmap object to store pixel data.
   bmObjectOld = (HBITMAP)::SelectObject(hdcObject, (HBITMAP)bmAndObject);

   // Set proper mapping mode.
   ::SetMapMode(hdcTemp, GetMapMode(hdc));


   int i,j;
   for(i=0;i<ptSize.x;i++)
   for(j=0;j<ptSize.y;j++)
   {
	   COLORREF cc=::GetPixel(hdcTemp,i,j);
	   ::SetPixel(hdcObject,i,j,(cc&0xFFFFFF)!=(cTransparentColor&0xFFFFFF)?0:0xFFFFFF);
   }

   ::SelectObject(hdcTemp, bmSaveOld);   
   ::SelectObject(hdcObject, bmObjectOld);   

   // Delete the memory DCs.
   ::DeleteDC(hdcObject);
   ::DeleteDC(hdcTemp);

   return bmAndObject;
} 
