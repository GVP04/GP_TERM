// GPCursor.cpp: implementation of the GPCursor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPCursor.h"
#include "GPCursorArr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


const UINT GPCursor::uNMethods=5;
const char *GPCursor::cArrMethods[]={
		"SetName","CreateFromFile","CreatePredefine","CreateFromImageList","ClipCursor",
		"","","","","",
	};

const char *GPCursor::cArrMethodsParams[]={
		"Name","FileName","OEM_Name, cxDesired, cyDesired","ImageListName, ImageNum, xHotSpot, yHotSpot","Left,Top,Right,Bottom",
		"","","","","",
	};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPCursor::GPCursor(const char *iName)
{
	Name=iName;m_Cursor=NULL;
}

GPCursor::~GPCursor()
{
	if (m_Cursor!=NULL)
		DestroyCursor(m_Cursor);
	m_Cursor=NULL;
}

const CString GPCursor::SetName(const char *iName)
{
	CString tmp=Name;
	Name=iName;

	return tmp;
}

const CString GPCursor::GetName()
{
	return Name;
}

HCURSOR GPCursor::CreateFromFile(LPCTSTR lpFileName)
{
	if (m_Cursor) DestroyCursor(m_Cursor);
	m_Cursor=LoadCursorFromFile(lpFileName);
	return m_Cursor;
}

HCURSOR GPCursor::CreatePredefine(LPCTSTR lpCursorName, int cxDesired, int cyDesired)
{
	UINT     mIDC[16]={OCR_NORMAL,OCR_IBEAM,OCR_WAIT,OCR_CROSS,OCR_UP,OCR_SIZE,OCR_ICON,OCR_SIZENWSE,OCR_SIZENESW,OCR_SIZEWE,OCR_SIZENS,OCR_SIZEALL,OCR_ICOCUR,OCR_NO,OCR_HAND,OCR_APPSTARTING,};
//	UINT mIDC[16]={OCR_NORMAL,32513,32514,32515,32516,32640,32641,32642,32643,32644,32645,32646,32647,32648,32649,32650,};
	char * mIDCnm[16]={"OCR_NORMAL","OCR_IBEAM","OCR_WAIT","OCR_CROSS","OCR_UP","OCR_SIZE","OCR_ICON","OCR_SIZENWSE","OCR_SIZENESW","OCR_SIZEWE","OCR_SIZENS","OCR_SIZEALL","OCR_ICOCUR","OCR_NO","OCR_HAND","OCR_APPSTARTING",};

	UINT i;
	for(i=0;i<16 && _stricmp(lpCursorName,mIDCnm[i])!=0;i++);
	
	UINT nCur;

	if (i>=16) nCur=atoi(lpCursorName);
	else nCur=mIDC[i];

	if (m_Cursor) DestroyCursor(m_Cursor);
	m_Cursor=AfxGetApp()->LoadOEMCursor(nCur);
	return m_Cursor;
}

HCURSOR GPCursor::CreateFromImageList(LPCTSTR lpImagelListName, UINT nImage, int xHotSpot, int yHotSpot)
{
	if (m_Cursor) DestroyCursor(m_Cursor);
	m_Cursor=NULL;

	if (*lpImagelListName==0) lpImagelListName="MISCS";
			
	GPImageList *MainIl=NULL;
	int ImgLId=GPC.GetImageListId(lpImagelListName);
	if (ImgLId>=0) MainIl=&(GPC.a_GPImageList[ImgLId]);
	if (MainIl)
	{
		HICON hi=MainIl->m_IL.ExtractIcon(nImage);
		if (hi)
		{
			ICONINFO iinfo={0};
			GetIconInfo(hi,&iinfo);
			iinfo.xHotspot=xHotSpot;
			iinfo.yHotspot=yHotSpot;
			m_Cursor=CreateIconIndirect(&iinfo);
			DestroyIcon(hi);
			if (iinfo.hbmColor) DeleteObject(iinfo.hbmColor);
			if (iinfo.hbmMask) DeleteObject(iinfo.hbmMask);
		}
	}

	return m_Cursor;
}

BOOL GPCursor::GPClipCursor(CONST RECT *lpRect)
{
	return ::ClipCursor(lpRect);
}


UINT GPCursor::DoMethod(const char *iStr, char *oStr, void *GPRArray)
{
	char *strmet=new char [(int)strlen(iStr)+50];
	strcpy(strmet,iStr);

	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(strmet,' ')=0;
	else		pos="";	

	int nfunc=0;
	int retint=-123456; 
	
	if (*strmet>='0' && *strmet<='9') nfunc=atoi(strmet);
	else for(nfunc=0;nfunc<uNMethods && _stricmp(strmet,cArrMethods[nfunc])!=0;nfunc++); 

	switch(nfunc)
	{
	case 0: /*SetName*/	if (*pos!=0) Name=pos; break;
	case 1: /*CreateFromFile*/
		retint=(int)CreateFromFile(pos);
		break;
	case 2: /*CreatePredefine*/
		{
			int cxDesired=0, cyDesired=0;
			const char *pos2=strchr(pos,',');
			if (pos2) m_LastScanf=sscanf(++pos2,"%d,%d",&cxDesired,&cyDesired);
			retint=(int)CreatePredefine(pos,cxDesired,cyDesired);
		}
		break;
	case 3: /*CreateFromImageList*/
		{
			int nImage=0;
			int xHotSpot=0, yHotSpot=0;
			const char *pos2=strchr(pos,',');
			if (pos2) 
			{
				m_LastScanf=sscanf(pos2,"%d,%d,%d",&nImage,&xHotSpot,&yHotSpot);
				nImage=atoi(pos2);
			}
			retint=(int)CreateFromImageList(ExtractField(pos, 1, ","), nImage, xHotSpot, yHotSpot);
		}
		break;
	case 4: /*ClipCursor*/
		{
			RECT re={0};
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&re.left,&re.top,&re.right,&re.bottom);
			retint=GPClipCursor(&re);
		}
		break;
	default:
		GPC.m_ErrReport.GPWriteWarnLog2("GPCursor", "Unknown Method",iStr);
		if (oStr!=NULL) sprintf(oStr,ErrObjSub,strmet);nfunc=0xFFFFFFFFL;
		break;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);

	delete[] strmet;
	return nfunc;
}

HCURSOR GPCursor::GetHCURSOR() 
{
	return m_Cursor;
}

HCURSOR GPCursor::SetHCURSOR(HCURSOR ihCur)
{
	HCURSOR ret=m_Cursor;
	m_Cursor=ihCur;
	return ret;
}

