// ODContextArray.cpp: implementation of the CODContextArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "ODContextArray.h"
#include "GPUnit.h"
#include <stdio.h>
#include <direct.h>
#include <io.h>
#include "GP_TermDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#include "GPImageList.h"


CODContextArray::CODContextArray()
{
	pTerminalMenuContext=NULL;
	pTerminalUserMenuContext=NULL;
	m_uNContext=0;
	m_CurrentContextNum=0;
	m_uMaxContext=50;
	m_Array =new CODContext * [m_uMaxContext];
	ZeroMemory(m_Array,sizeof(CODContext *)*m_uMaxContext);

//	pTerminalMenuContext=	LoadContext(GPC.csODCTerminalMenuName, "");
//	LoadContext("Default", "");
//	LoadContext("DefaultMenu", "");

}

CODContextArray::~CODContextArray()
{
	if (m_Array)
	{
		UINT i;
		for(i=0; i<m_uMaxContext;i++)
			if (m_Array[i]) 
			{
				delete m_Array[i];
				m_Array[i]=NULL;
			}
		delete[] m_Array;
		m_Array=NULL;
	}
	m_uNContext=0;
}


CODContext * CODContextArray::AddEmpty()
{
	UINT newID=FindItemByName("");
	if (newID>m_uNContext)
	{
		UINT i;
		while((m_uNContext>=m_uMaxContext-1 && m_uMaxContext<0x1000) || m_uMaxContext==0)
		{
			CODContext ** tmp2=new CODContext * [m_uNContext+10];
			for(i=0; i<m_uMaxContext;i++)
				tmp2[i]=m_Array[i];
			m_uMaxContext=m_uNContext+10;
			delete[] m_Array;
			for(; i<m_uMaxContext;i++)
				tmp2[i]=NULL;
			m_Array=tmp2;
		}
		for(newID=0; newID<m_uMaxContext;newID++)
			if (m_Array[newID]==NULL)
			{
				m_Array[newID]=new CODContext;
				ResetItem(m_Array[newID]);
				m_uNContext++;
				break;
			}
	}
	return m_Array[newID];
}

CODContext *CODContextArray::CreateContext(const char *ContextName)
{
	UINT Id=FindItemByName(ContextName);
	CODContext *it=NULL;
	if (Id>m_uNContext) it=AddEmpty();
	else it=m_Array[Id];

	ResetItem(it);
	it->m_ContextName=ContextName;

	return it;
}

CODContext *CODContextArray::CreateContext(CODContext & iValue)
{
	UINT Id=FindItemByName(iValue.m_ContextName);
	CODContext *it=NULL;
	if (Id>m_uNContext) it=AddEmpty();
	else it=m_Array[Id];

	ResetItem(it);

	it->m_ContextName		=iValue.m_ContextName;

	return it;
}

UINT CODContextArray::DeleteContext(const char *ContextName)
{
	UINT Id=FindItemByName(ContextName);
	if (Id<m_uNContext && Id>0)
	{
		delete m_Array[Id];
		UINT j;
		for(j=Id+1;j<m_uNContext;j++)
			m_Array[j-1]=m_Array[j];
		m_uNContext--;
		m_Array[m_uNContext]=NULL;
	}
	return GetCount();
}

UINT CODContextArray::GetCount()
{
	return m_uNContext;
}

UINT CODContextArray::FindItemByContext(CODContext *iContext)
{
	UINT ret = -1;
	UINT i;
	if (m_Array)
		for(i=0; i<m_uNContext && ret==-1;i++)
			if (m_Array[i]==iContext)	ret=i;
	return ret;
}

UINT CODContextArray::FindItemByName(const char *iName)
{
	UINT ret = -1;
	UINT i;
	if (m_Array!=NULL)
		for(i=0; i<m_uNContext && ret==-1;i++)
			if (m_Array[i] && m_Array[i]->m_ContextName==iName)	ret=i;
	return ret;
}

void CODContextArray::ResetItem(CODContext *iItem)
{
	if (iItem) iItem->ResetContext();
}

const CString CODContextArray::EnumContextrs(UINT iIndex)
{
	CString ret="";
	UINT i=0;
	if (m_Array && m_uNContext)
		for(i=0;i<m_uNContext;i++)
			if (m_Array[i])
			{
				if (i>0) ret+="\x7F"+m_Array[i]->m_ContextName;
				else	 ret=m_Array[i]->m_ContextName;
			}
	return ret;
}

CODContext *CODContextArray::GetContext(const char * ContextName)
{
	CODContext *ret=NULL;
	if (*ContextName>='0' && *ContextName<='9')
	{
		UINT tmpID=atoi(ContextName);
		UINT UnitNum=(tmpID&0xFFFF);
		UINT ScrDlgNum=(tmpID/0x10000)&0xFFF;
		GPUnit **tmpGPU=NULL;
		if ((tmpID&IS_DLG_UNIT)==IS_DLG_UNIT)
		{
			if (ScrDlgNum<MAX_OBJDLG)
			{
				if (GPC.m_Document->a_GPObjDialog[ScrDlgNum])tmpGPU=GPC.m_Document->a_GPObjDialog[ScrDlgNum]->GPU;
				else
				if (GPC.m_Document->a_GPObjFrame[ScrDlgNum])tmpGPU=GPC.m_Document->a_GPObjFrame[ScrDlgNum]->GPU;
			}
		}
		else
		{
			if (ScrDlgNum<MAX_SCREEN && GPC.m_Document->aGPScreen[ScrDlgNum])
				tmpGPU=GPC.m_Document->aGPScreen[ScrDlgNum]->GPGetWindowById(0)->WndUnit;
			//	MAX_SCREEN;
			//	GPMAX_NWINDOW;
		}
		if (tmpGPU && UnitNum<tmpGPU[0]->m_NGPUNIT && tmpGPU[UnitNum]) ret=tmpGPU[UnitNum]->m_ODC;
	}

	if (!ret)
	{
		ret=*m_Array;
		UINT tmpNum=FindItemByName(ContextName);

		if (tmpNum<m_uNContext && m_Array && m_Array[tmpNum])
			ret=m_Array[tmpNum];
	}
	return ret;
}

void CODContextArray::PaintByDRAWITEMSTRUCT(GPUnit *gpuRes, WPARAM wParam, LPDRAWITEMSTRUCT lPDiStruct, GPMenu *pMenu)
{
	if (lPDiStruct && gpuRes && gpuRes->GPU)
	{
		DWORD dwUnitId=(lPDiStruct->CtlID)?lPDiStruct->CtlID%0xFFFF-50000:0;
		if (gpuRes && gpuRes->GPU && dwUnitId<(*gpuRes->GPU)->m_NGPUNIT && gpuRes->GPU[dwUnitId])
		{
			LPARAM lParam=NULL;
			CODContext *mdc=*m_Array;

			switch (lPDiStruct->CtlType)
			{
			case ODT_MENU:
				if (pMenu)
				{
					lParam=(LPARAM)(&pMenu->MENUINFOArray[lPDiStruct->itemData]);
					mdc=GetContext(((PGPMENUINFO)(lParam))->csContext);
				}
				if (mdc && mdc==*m_Array && m_Array[1] && m_Array[0]->m_ContextName=="Default") mdc=m_Array[1];
				break;
			default:
				mdc=NULL;
				if (gpuRes->GPU[dwUnitId]->m_DrawContextName=="" && gpuRes->GPU[dwUnitId]->m_ODC)
					mdc=gpuRes->GPU[dwUnitId]->m_ODC;

				if (!mdc) mdc=GetContext(gpuRes->GPU[dwUnitId]->m_DrawContextName);
				break;
			}
			if (mdc)
			{
				/*				
				if (mdc==*m_Array || mdc==m_Array[1])
				{
					CString tmps;
					tmps.Format("Default context used for object Id=%d IdDlgScr=%d Requred context %s",dwUnitId,dwUnitId/0x10000,(LPCSTR)gpuRes->GPU[dwUnitId]->m_DrawContextName);
					if (gpuRes->GPU[dwUnitId]->m_DrawContextName!="")
					{
						tmps.Format("Default context used for object Id=%d IdDlgScr=%d Requred context %s",dwUnitId,dwUnitId/0x10000,(LPCSTR)gpuRes->GPU[dwUnitId]->m_DrawContextName);
						GPC.m_ErrReport.GPWriteErrorLog2("GUI", "OwnerDraw",tmps);
					}
					else
					{
						tmps.Format("Default context used for object Id=%d IdDlgScr=%d",dwUnitId,dwUnitId/0x10000,(LPCSTR)gpuRes->GPU[dwUnitId]->m_DrawContextName);
						GPC.m_ErrReport.GPWriteWarnLog2("GUI", "OwnerDraw",tmps);
					}
				}
				*/
				mdc->m_CurHWND=gpuRes->GPU[dwUnitId]->UnitHWND;
				mdc->m_MeasureFlag=0;
				mdc->PaintByDRAWITEMSTRUCT(gpuRes->GPU[dwUnitId],wParam,lPDiStruct,pMenu,lParam);
			}
		}

	}
}

BOOL CODContextArray::MeasureItem(GPUnit *gpuRes, WPARAM wParam, LPMEASUREITEMSTRUCT lPDiStruct, GPMenu *pMenu)
{
	BOOL ret=FALSE;
	if (lPDiStruct && gpuRes && gpuRes->GPU)
	{
		DWORD dwUnitId=(lPDiStruct->CtlID)?lPDiStruct->CtlID%0xFFFF-50000:0;
		if (dwUnitId<(*gpuRes->GPU)->m_NGPUNIT && gpuRes->GPU[dwUnitId])
		{
			LPARAM lParam=NULL;
			CODContext *mdc=*m_Array;

			switch (lPDiStruct->CtlType)
			{
			case ODT_MENU:
				if (pMenu)
				{
					lParam=(LPARAM)(&pMenu->MENUINFOArray[lPDiStruct->itemData]);
					mdc=GetContext(((PGPMENUINFO)(lParam))->csContext);
				}
				if (mdc && mdc==*m_Array && m_Array[1] && m_Array[0]->m_ContextName=="Default") mdc=m_Array[1];
				break;
			default:
				mdc=NULL;
				if (gpuRes->GPU[dwUnitId]->m_DrawContextName=="" && gpuRes->GPU[dwUnitId]->m_ODC)
					mdc=gpuRes->GPU[dwUnitId]->m_ODC;

				if (!mdc) mdc=GetContext(gpuRes->GPU[dwUnitId]->m_DrawContextName);
				break;
			}
/*				
			if (mdc==*m_Array)
			{

				CString tmps;
				tmps.Format("Default context used for object Id=%d IdDlgScr=%d Requred context %s",dwUnitId,dwUnitId/0x10000,(LPCSTR)gpuRes->GPU[dwUnitId]->m_DrawContextName);
				if (gpuRes->GPU[dwUnitId]->m_DrawContextName!="")
				{
					tmps.Format("Default context used for object Id=%d IdDlgScr=%d Requred context %s",dwUnitId,dwUnitId/0x10000,(LPCSTR)gpuRes->GPU[dwUnitId]->m_DrawContextName);
					GPC.m_ErrReport.GPWriteErrorLog2("GUI", "OwnerDraw",tmps);
				}
				else
				{
					tmps.Format("Default context used for object Id=%d IdDlgScr=%d",dwUnitId,dwUnitId/0x10000,(LPCSTR)gpuRes->GPU[dwUnitId]->m_DrawContextName);
					GPC.m_ErrReport.GPWriteWarnLog2("GUI", "OwnerDraw",tmps);
				}
			}
*/
			DRAWITEMSTRUCT tmpStru={0};
			tmpStru.CtlID=lPDiStruct->CtlID;
			tmpStru.CtlType=lPDiStruct->CtlType;
			tmpStru.hDC=::GetDC(NULL);
			tmpStru.hwndItem=gpuRes->UnitHWND;
			if (lPDiStruct->CtlType==ODT_MENU)
				tmpStru.hwndItem=(HWND)(pMenu->MENUINFOArray[lPDiStruct->itemData].hMenu);
			tmpStru.itemAction=0;
			tmpStru.itemData=lPDiStruct->itemData;
			tmpStru.itemID=lPDiStruct->itemID;
			tmpStru.itemState=0;
			tmpStru.rcItem.right=lPDiStruct->itemWidth;
			tmpStru.rcItem.bottom=lPDiStruct->itemHeight;


			if (mdc)
			{
				mdc->m_MeasureFlag=1;
				mdc->m_MeasureStruct=*lPDiStruct;
				//mdc->m_MeasureStruct.itemHeight=mdc->m_MeasureStruct.itemWidth=0;
				mdc->m_CurHWND=gpuRes->GPU[dwUnitId]->UnitHWND;
				mdc->PaintByDRAWITEMSTRUCT(gpuRes->GPU[dwUnitId],wParam,&tmpStru,pMenu,lParam);
				::ReleaseDC(NULL,tmpStru.hDC);
				mdc->m_MeasureFlag=0;
				if (mdc->m_MeasureStruct.itemHeight && mdc->m_MeasureStruct.itemWidth)
				{
					ret=TRUE;
					*lPDiStruct=mdc->m_MeasureStruct;
				}
			}
		}
	}
	return ret;
}

CODContext *CODContextArray::SaveContext(const char * ccContextName, const char * ccFileName)
{
	CODContext *ret=NULL;
	CODContext *pContext=GetContext(ccContextName);
	if (pContext && pContext->m_ContextName!="Default") 
		ret=pContext->SaveContext(ccFileName);

	return ret;
}

CODContext *CODContextArray::LoadContext(const char * ccContextName, const char * ccFileName)
{
	CODContext *ret=NULL;
	if (ccContextName && ccFileName && (*ccContextName || *ccFileName))
	{
		CString csContextName=ccContextName;
		CString csFileName=ccFileName;
		CString csFileTmp;
		int i;
		if (csFileName=="") csFileName=csContextName;
		if (csContextName=="")
		{
			csFileName.MakeUpper();
			i=csFileName.Find(".ODC");
			csFileName=ccFileName;
			if (i<=0) i=csFileName.GetLength();
			csContextName=csFileName.Mid(0,i);
		}
		csFileTmp=csFileName;
		csFileTmp.MakeUpper();
		if (csFileTmp.Find(".ODC")<0) csFileName+=".ODC";

		if ((i=_access(csFileName,0))!=0) csFileName="ODC\\"+csFileName;

		FILE *srcFile=fopen(csFileName,"rt");
		if (srcFile)
		{
			CODContext *pContext=CreateContext(csContextName);
			ret=pContext;
			char *tmps=new char [20000];
			char *tmpsResult=tmps+10000;
			CString tmpCS;
			UINT uCurItem=0;
			while(fgets(tmps,9900,srcFile))
			{
				char *pos=tmps;
				while(*pos)
				{
					if (*pos>0 && *pos<=' ') *pos=' ';
					pos++;
				}
				while(pos!=tmps && *pos>=0 && *pos<=' ')
					*(pos--)=0;

				pos=tmps;
				while(*pos>0 && *pos<=' ') pos++;
				if (*pos && *pos!='*')
				{
					ReplaceSpec(pos);
					tmpCS=ExtractField(pos,1," ");
					while(*pos && *pos!=' ') pos++;
					while(*pos && *pos==' ') pos++;
					if (*pos)
					{
						tmpCS.MakeUpper();
						if (tmpCS=="#DEFINE")
						{
						}
						else
						if (tmpCS=="ITEM")
						{
							pContext->InsertEmptyItem(uCurItem,1);
							pContext->SetItem(uCurItem++,pos);
						}
						else
						if (tmpCS=="METHOD")
						{
							pContext->DoMethod(pos,NULL);
						}
						else
						if (tmpCS=="FUNCTION")
						{
							*tmpsResult=0;
							const char *pos2=pos;
							while(*pos && *(pos++)!='=');
							if (*pos)
							{
								pContext->DoMethod(pos,tmpsResult);
							}
						}
					}
				}
			}
			delete []tmps;
			fclose(srcFile);
		}
	}
	return ret;
}

int CODContextArray::DoContextMethod(const char * ccContextNameMethod, char *oStr)
{
	int ret=-1;
	const char *posMethod=FindField(ccContextNameMethod,2,",");
	if (posMethod && *posMethod) 
		ret=DoContextMethod(ExtractField(ccContextNameMethod,1,","), posMethod, oStr);

	return ret;
}

int CODContextArray::DoContextMethod(const char * ccContextName, const char * ccMethodName, char *oStr)
{
	int ret=-1;
	CODContext *pContext=GetContext(ccContextName);
	if (pContext && (pContext->m_ContextName!="Default" || _stricmp(ccContextName,"Default")==0))
		ret=pContext->DoMethod(ccMethodName,oStr);
	return ret;
}
