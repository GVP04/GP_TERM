// GPSprArray.cpp: implementation of the CGPSprArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPSprArray.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGPSprArray::CGPSprArray()
{
	m_uMaxSpr=50;
	m_Array =new CGPSpr * [m_uMaxSpr];
	UINT i;
	for(i=0; i<m_uMaxSpr;i++) m_Array[i]=NULL;
	m_uNSpr=0;
}

CGPSprArray::~CGPSprArray()
{
	if (m_Array!=NULL)
	{
		UINT i;
		for(i=0; i<m_uMaxSpr;i++)
			if (m_Array[i]!=NULL) 
			{
				delete m_Array[i];
				m_Array[i]=NULL;
			}
		delete[] m_Array;
		m_Array=NULL;
	}
	m_uNSpr=0;
}

CGPSpr * CGPSprArray::GetSpr(const char *SprName)
{
	CGPSpr * tmp=NULL;
	UINT i;
	if (m_Array!=NULL)
		for(i=0; i<m_uNSpr;i++)
			if (m_Array[i]!=NULL && strcmp(m_Array[i]->GetName(),SprName)==0)
			{
				tmp=m_Array[i];
				break;
			}
	return tmp;
}

CGPSpr * CGPSprArray::CreateSpr(const char *SprName)
{
	CGPSpr * tmp=GetSpr(SprName);
	if (tmp!=NULL) DeleteSpr(SprName);

	while((m_uNSpr>=m_uMaxSpr-1 && m_uMaxSpr<0x1000) || m_uMaxSpr==0)
	{
		CGPSpr ** tmp2=new CGPSpr * [m_uNSpr+10];
		UINT i;
		for(i=0; i<m_uMaxSpr;i++)
			tmp2[i]=m_Array[i];
		m_uMaxSpr=m_uNSpr+10;
		if (m_Array) delete[] m_Array;
		for(; i<m_uMaxSpr;i++)
			tmp2[i]=NULL;
		m_Array=tmp2;
	}

	if (m_uNSpr<m_uMaxSpr)
	{
		tmp=m_Array[m_uNSpr++]=new CGPSpr;
		if (tmp && *SprName) tmp->SprName=SprName;
	}

	return tmp;
}

UINT CGPSprArray::DeleteSpr(const char *SprName)
{
	UINT i;
	if (m_Array!=NULL)
		for(i=0; i<m_uNSpr;i++)
			if (m_Array[i]!=NULL && strcmp(m_Array[i]->GetName(),SprName)==0)
			{
				delete m_Array[i];
				UINT j;
				for(j=i+1;j<m_uNSpr;j++)
					m_Array[j-1]=m_Array[j];
				m_uNSpr--;
				m_Array[m_uNSpr]=NULL;
				break;
			}
	return m_uNSpr;
}

UINT CGPSprArray::GetCount()
{
	return m_uNSpr;
}

const char * CGPSprArray::GetSprName(UINT uNSpr)
{
	const char *ret="";
	if (m_Array!=NULL && uNSpr<m_uNSpr && m_Array[uNSpr]!=NULL)
		ret=m_Array[uNSpr]->GetName();
	return ret;
}

UINT CGPSprArray::GetArrayDescr(CString &str)
{
	UINT ret=0,i;
	str="";
	CString tmp;

	if (m_Array!=NULL)
		for(i=0,ret=0;i<m_uNSpr;i++)
			if (m_Array[i]!=NULL)
			{
				if ((ret++)>0) str+="\0x7F";
				tmp.Format("%s\x07%d\x07%d",m_Array[i]->GetName(),m_Array[i]->GetCount(),m_Array[i]->GetNField());
				str+=tmp;
			}
	return ret;
}

long CGPSprArray::GetSprInfos(VARIANT *ListInfo, DWORD dwArrType)
{
	SAFEARRAY FAR* psa = NULL;
	long ret=0;

	USES_CONVERSION;
	SAFEARRAYBOUND tmpSAB={0};

	UINT nElements=m_uNSpr;
	if (nElements==0) nElements++;

	tmpSAB.cElements=nElements;

	if ((V_VT(ListInfo)&VT_ARRAY) == VT_ARRAY )
	{
		psa = V_ARRAY(ListInfo); 
		SafeArrayGetLBound(psa,1,&tmpSAB.lLbound);
		SafeArrayDestroy(psa);
	}

	VariantInit(ListInfo);

	try
	{
		COleSafeArray SAtmp;
		SAtmp.Create(VT_VARIANT, 1,&tmpSAB.cElements);
		VariantCopy(ListInfo,SAtmp);
	}
	catch(...)
	{
			GPC.m_ErrReport.GPWriteErrorLog("GPSprArray", "GetSprInfos","");
	}

	psa = V_ARRAY(ListInfo);   
	// Check dimensions of the array.
	if (SafeArrayGetDim(psa) == 1)	
	{
		VARIANT HUGEP *pbstr;
		HRESULT hr;
		hr = SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
		if (!FAILED(hr))
		{
			UINT i;
			for(i=0;i<m_uNSpr;i++)
				m_Array[i]->GetSprInfo(pbstr+i,dwArrType);
			SafeArrayUnaccessData(psa);
			ret=nElements;
		}
	}

	return ret;
}

UINT CGPSprArray::DoMethod(const char *iSprName, const char *iStr, char ** oStr)
{
	UINT ret=-1;
	UINT sprid=GetSprId(iSprName);
	if (sprid<m_uNSpr && m_Array[sprid]!=NULL) ret=m_Array[sprid]->DoMethod(iStr,oStr);
	else
		GPC.m_ErrReport.GPWriteWarnLog2("GPSpr can't find", iSprName, iStr);

	return ret;
}

UINT CGPSprArray::GetSprId(const char *iSprName)
{
	UINT ret = -1;
	if (m_Array!=NULL)
	{
		UINT i;
		for(i=0; i<m_uNSpr;i++)
			if (m_Array[i]!=NULL && strcmp(m_Array[i]->GetName(),iSprName)==0)
			{
				ret=i;
				break;
			}
	}
	return ret;
}

long CGPSprArray::FillObject(const char *SprName, HWND ihWnd, UINT ObjType, const char *Params, long FillType)
{
	UINT ret=-1;
	UINT sprid=GetSprId(SprName);
	if (sprid<m_uNSpr && m_Array[sprid]!=NULL) ret=m_Array[sprid]->FillObject(ihWnd,ObjType,Params, FillType);
	return ret;
}

long CGPSprArray::FillObject(const char *SprName,LPDISPATCH lpDisp, const char *Params, long FillType)
{
	UINT ret=-1;
	UINT sprid=GetSprId(SprName);
	if (sprid<m_uNSpr && m_Array[sprid]!=NULL) ret=m_Array[sprid]->FillObject(lpDisp,Params, FillType);
	return ret;
}

long CGPSprArray::ReplaceObject(const char *SprName, HWND ihWnd, UINT ObjType, const char *Params)
{
	UINT ret=-1;
	UINT sprid=GetSprId(SprName);
	if (sprid<m_uNSpr && m_Array[sprid]!=NULL) ret=m_Array[sprid]->ReplaceObject(ihWnd,ObjType,Params);
	return ret;
}

long CGPSprArray::FillByArray(LPCTSTR SprName, const VARIANT FAR& KeyArray, long nField, VARIANT FAR* RetArray)
{
	UINT ret=-1;
	UINT sprid=GetSprId(SprName);
	if (sprid<m_uNSpr && m_Array[sprid]!=NULL) ret=m_Array[sprid]->FillByArray(KeyArray, nField, RetArray);
	return ret;
}

long CGPSprArray::ReplaceOblectEx(HWND ihWnd, UINT ObjType, long StartItem, long EndItem, const char *Params)
{
	long ret=0;
	if (ihWnd!=NULL && (StartItem<EndItem || EndItem<0))
	{
		int cnt=0;
		switch(ObjType&0xFFFF)
		{
		case GPSPRFILL_COMBOBOX:	cnt=SendMessage(ihWnd,CB_GETCOUNT,0,0);			break;
		case GPSPRFILL_COMBOBOXEX:	cnt=SendMessage(ihWnd,CB_GETCOUNT,0,0);			break;
		case GPSPRFILL_LISTBOX:		cnt=SendMessage(ihWnd,LB_GETCOUNT,0,0);			break;
		case GPSPRFILL_LISTCTRL:	cnt=SendMessage(ihWnd,LVM_GETITEMCOUNT,0,0);	break;
		}
		if (cnt>0 && StartItem<cnt)
		{
			if (EndItem>cnt || EndItem<0) EndItem=cnt-1;
			if (StartItem>cnt) StartItem=cnt-1;
			long nToFill=EndItem-StartItem+1;
			long nFilled=0;
			char *ItemsFlag=new char [nToFill+10];
			long i;
			for(i=0;i<nToFill;i++) ItemsFlag[i]=0;
			char *prm=new char [(int)strlen(Params)+10];
			strcpy(prm,Params);
			char *pos=prm;
			while(pos!=NULL && *pos!=0 && nFilled<nToFill)
			{
				char *pos2=strchr(pos,GPC.DelimiterIn1);
				if (pos2!=NULL) *(pos2++)=0;
				else pos2="";
				char *posParam=strchr(pos,',');
				if (posParam!=NULL) *(posParam++)=0;
				else posParam="";
				UINT sprid=GetSprId(pos);
				if (sprid<m_uNSpr && m_Array[sprid]!=NULL) nFilled+=m_Array[sprid]->ReplaceObjectEx(ihWnd, ObjType, StartItem, EndItem, ItemsFlag, posParam);
				pos=pos2;
			}
			delete[] prm;
			delete[] ItemsFlag;
			ret=nFilled;
		}
	}
	return ret;
}

long CGPSprArray::ReplaceOblectEx(LPDISPATCH lpDisp, long StartItem, long EndItem, const char *Params)
{
	long ret=0;
	if (lpDisp!=NULL && (StartItem<EndItem || EndItem<0))
	{
		int cnt=-1;
		long nFix=0;
		CString GUIDListView ("{E0BCE3B3-7EB5-4D6A-A7BB-6062BBE128E7}");
		CString GUIDFlexGrid("{6B93DE84-A00D-47B0-9A78-114E8B0CF652}");
		CString GUIDFlexGrid2("{A9ED5E4E-1791-11D5-AB13-00485481E401}");
		CString GUIDFlexGrid3("{6262D3A0-531B-11CF-91F6-C2863C385E30}");
		CString GUIDFlexGrid4("{5F4DF280-531B-11CF-91F6-C2863C385E30}");
		COleVariant strGU("                                                                                                                     ");
		{
			ITypeInfo *pTInfo;
			lpDisp->GetTypeInfo(0,0,&pTInfo);
			TYPEATTR *hh;
			pTInfo->GetTypeAttr(&hh);
			::StringFromGUID2(hh->guid,strGU.bstrVal,40);
			pTInfo->Release();
		}

		if (GUIDListView==strGU.bstrVal) // ListView
		{
			COleDispatchDriver DCList;
			DCList.AttachDispatch(lpDisp);
			LPDISPATCH pDCListItems;
			DCList.InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDCListItems, NULL);
			COleDispatchDriver DCListItems;
			DCListItems.AttachDispatch(pDCListItems);
			DCListItems.InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&cnt, NULL);
			DCListItems.DetachDispatch();
			DCList.DetachDispatch();
		}
		else
//		if (GUIDFlexGrid==strGU.bstrVal || GUIDFlexGrid2==strGU.bstrVal || GUIDFlexGrid3==strGU.bstrVal || GUIDFlexGrid4==strGU.bstrVal) // FlexGrid
		{
			long nRows=0;
			COleDispatchDriver DCList;
			DCList.AttachDispatch(lpDisp);
			DCList.InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&nFix, NULL);
			DCList.InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&nRows, NULL);
			DCList.DetachDispatch();
			cnt=nRows-nFix;
		}

		if (cnt>0 && StartItem<cnt)
		{
			if (EndItem>cnt+nFix || EndItem<0) EndItem=cnt-1+nFix;
			if (StartItem>cnt) StartItem=cnt-1;
			long nToFill=EndItem-StartItem+1;
			long nFilled=0;
			char *ItemsFlag=new char [nToFill+10];
			long i;
			for(i=0;i<nToFill;i++) ItemsFlag[i]=0;
			char *prm=new char [(int)strlen(Params)+10];
			strcpy(prm,Params);
			char *pos=prm;
			while(pos!=NULL && *pos!=0 && nFilled<nToFill)
			{
				char *pos2=strchr(pos,GPC.DelimiterIn1);
				if (pos2!=NULL) *(pos2++)=0;
				else pos2="";
				char *posParam=strchr(pos,',');
				if (posParam!=NULL) *(posParam++)=0;
				else posParam="";
				UINT sprid=GetSprId(pos);
				if (sprid<m_uNSpr && m_Array[sprid]!=NULL) nFilled+=m_Array[sprid]->ReplaceObjectEx(lpDisp, StartItem, EndItem, ItemsFlag, posParam);
				pos=pos2;
			}
			ret=nFilled;
			delete[] prm;
			delete[] ItemsFlag;
		}
	}
	return ret;
}
