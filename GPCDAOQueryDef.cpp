// GPCDAOQueryDef.cpp: implementation of the GPCDAOQueryDef class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPCDAOQueryDef.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPCDAOQueryDef::GPCDAOQueryDef(CDaoDatabase* pDatabase )
	:CDaoQueryDef(pDatabase)
{

}

GPCDAOQueryDef::~GPCDAOQueryDef()
{

}

BOOL GPCDAOQueryDef::GPIsOpen()
{
	return IsOpen();
}

void GPCDAOQueryDef::GPClose()
{
	Close();
}


BOOL GPCDAOQueryDef::GPOpen(const char *iStr)
{
	BOOL ret=FALSE;
	try
	{try
	{
		Open(*iStr==0?NULL:iStr);
	}
	catch(CDaoException e)
	{
		e.ReportError();
	}
	}
	catch(CMemoryException e)
	{
		e.ReportError();
	}

	return ret;
}

BOOL GPCDAOQueryDef::GPCreate(const char *iStr)
{
	char *str=new char [(int)strlen(iStr)+20];
	BOOL ret=FALSE;
	try
	{try
	{
		char *lpszName=str;
		char *lpszSQL;

		lpszSQL=strchr(lpszName,';');
		if (lpszSQL!=NULL) *(lpszSQL++)=0;
		else lpszSQL="";

		
		if (*lpszName==0) lpszName=NULL;
		if (*lpszSQL==0) lpszSQL=NULL;

		Create(lpszName, lpszSQL);
		ret=TRUE;
	}
	catch(CDaoException e)
	{
		e.ReportError();
	}
	}
	catch(CMemoryException e)
	{
		e.ReportError();
	}

	delete[] str;
	return ret;
}

int GPCDAOQueryDef::DoMethod(const char *iMethod, char *oStr)
{
	char *met=new char [(int)strlen(iMethod)+50];
	strcpy(met,iMethod);
	const char *pos=strchr(iMethod,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc;
	char *fn[30]={
		"Append","CanUpdate","GetConnect","GetDateCreated","GetDateLastUpdated",
		"GetName","GetODBCTimeout","GetRecordsAffected","GetReturnsRecords","GetSQL",
		"GetType","IsOpen","SetConnect","SetName","SetODBCTimeout",
		"SetReturnsRecords","SetSQL","Execute","GetFieldCount","GetFieldInfo",
		"GetFieldInfo","GetFieldsInfo","GetParameterCount","GetParameterInfo","GetParameterInfoById",
		"GetParametersInfo","GetPValue","GetPValueById","SetPValue","SetPValueById",
		};

	if (*met>='0' && *met<='9') nfunc=atoi(met);
	else
		for(nfunc=0;nfunc<30 && _stricmp(met,fn[nfunc])!=0;nfunc++); 

	int retint=-123456; 
	int atoipos=atoi(pos);

	try
	{
		try
		{
			switch(nfunc)
			{
			case 0:	/*Append*/			Append();	break;
			case 1:	/*CanUpdate*/		if (IsOpen()) retint=CanUpdate();	break;
			case 2:	/*GetConnect*/		if (oStr!=NULL) strcpy(oStr,GetConnect());	break;
			case 3:	/*GetDateCreated*/
				if (IsOpen() && oStr!=NULL) 
				{
					COleDateTime dateCreated=GetDateCreated();
					sprintf(oStr,"%d\x7%d\x7%d\x7%d\x7%d\x7%d\x7F",
							dateCreated.GetYear(),
							dateCreated.GetMonth(),
							dateCreated.GetDay(),
							dateCreated.GetHour(),
							dateCreated.GetMinute(),
							dateCreated.GetSecond()
							);
				}
				break;
			case 4:	/*GetDateLastUpdated*/
				if (IsOpen() && oStr!=NULL) 
				{
					COleDateTime dateLastUpdated=GetDateLastUpdated();
					sprintf(oStr,"%d\x7%d\x7%d\x7%d\x7%d\x7%d\x7F",
							dateLastUpdated.GetYear(),
							dateLastUpdated.GetMonth(),
							dateLastUpdated.GetDay(),
							dateLastUpdated.GetHour(),
							dateLastUpdated.GetMinute(),
							dateLastUpdated.GetSecond()
							);
				}
				break;
			case 5:	/*GetName*/				if (oStr!=NULL) strcpy(oStr,GetName());	break;
			case 6:	/*GetODBCTimeout*/		retint=GetODBCTimeout();		break;
			case 7:	/*GetRecordsAffected*/	if (IsOpen()) retint=GetRecordsAffected();	break;
			case 8:	/*GetReturnsRecords*/	retint=GetReturnsRecords();	break;
			case 9:	/*GetSQL*/				if (oStr!=NULL) strcpy(oStr,GetSQL());	break;
			case 10:/*GetType*/	
				if (oStr!=NULL)
					strcpy(oStr,GPCDAODatabase::ReTranslateQDefType(GetType()));
				break;	
			case 11:/*IsOpen*/			retint=IsOpen();	break;
			case 12:/*SetConnect*/		SetConnect(pos);	break;
			case 13:/*SetName*/			SetName(pos);		break;
			case 14:/*SetODBCTimeout*/	SetODBCTimeout((short)atoipos);	break;
			case 15:/*SetReturnsRecords*/	SetReturnsRecords(atoipos&0x1);	break;
			case 16:/*SetSQL*/			SetSQL(pos);		break;
			case 17:/*Execute*/
				{
					char *pos333=new char [(int)strlen(pos)+2];
					strcpy(pos333,pos);
					_strupr(pos333);
					Execute(GPCDAODatabase::TranslateExecuteOptions(pos333));
					retint=1;
					delete[] pos333;
				}
			case 18:/*GetFieldCount*/	retint=GetFieldCount();	break;
			case 19:/*GetFieldInfoById*/
			case 20:/*GetFieldInfo*/
				if (oStr!=NULL)
				{
					CDaoFieldInfo finfo;
					if (nfunc==20)	GetFieldInfo(atoipos,finfo,AFX_DAO_ALL_INFO);
					else			GetFieldInfo(pos,finfo,AFX_DAO_ALL_INFO);
					GPCDAORecordset::GetFIString(finfo,oStr);
				}
				break;
			case 21:/*GetFieldsInfo*/	
				if (IsOpen() && oStr!=NULL) 
				{
					int nIndex;
					char *pos333=oStr;
					int nFields=GetFieldCount();
					CDaoFieldInfo finfo;
					for(nIndex=0;nIndex<nFields;nIndex++)
					{
						if (nIndex>0)	strcat(pos333++,"\x7F");
						GetFieldInfo(nIndex,finfo,AFX_DAO_ALL_INFO);
						GPCDAORecordset::GetFIString(finfo,pos333);
						pos333+=(int)strlen(pos333);
					}
				}
				break;

			case 22:/*GetParameterCount*/	retint=GetParameterCount();	break;	
			case 23:/*GetParameterInfo*/
			case 24:/*GetParameterInfoById*/
				if (oStr!=NULL)
				{
					CDaoParameterInfo pinfo;
					if (nfunc==24)	GetParameterInfo(atoipos,pinfo,AFX_DAO_ALL_INFO);
					else			GetParameterInfo(pos,pinfo,AFX_DAO_ALL_INFO);
					GetPIString(pinfo,oStr);
				}
				break;
			case 25:/*GetParametersInfo*/
				if (IsOpen() && oStr!=NULL) 
				{
					int nIndex;
					char *pos333=oStr;
					int nParam=GetParameterCount();
					CDaoParameterInfo pinfo;
					for(nIndex=0;nIndex<nParam;nIndex++)
					{
						if (nIndex>0)	strcat(pos333++,"\x7F");
						GetParameterInfo(nIndex,pinfo,AFX_DAO_ALL_INFO);
						GetPIString(pinfo,pos333);
						pos333+=(int)strlen(pos333);
					}
				}
				break;
			case 26:/*GetPValue*/	
				if (oStr!=NULL)
				{
					CString str;
					ConvertToString(GetParamValue(pos),str,"\x7F");
					strcpy(oStr,str);
				}
				break;
			case 27:/*GetPValueById*/
				if (oStr!=NULL)
				{
					CString str;
					ConvertToString(GetParamValue(atoipos),str,"\x7F");
					strcpy(oStr,str);
				}
				break;
			case 28:/*SetPValue*/
			case 29:/*SetPValueById*/	
				if (IsOpen()) 
				{
					char *postmpcc=new char [(int)strlen(pos)+10];
					strcpy(postmpcc,pos);
					char *posval=strchr(postmpcc,',');
					if (posval!=NULL) *(posval++)=0;
					if (nfunc==28)	SetParamValue(postmpcc,posval);
					else			SetParamValue(atoipos,posval);
					delete[] postmpcc;
				}
				break;
			default:
				GPC.m_ErrReport.GPWriteWarnLog2("GPCDAOQueryDef", "Unknown Method",iMethod);
				if (oStr!=NULL)		 sprintf(oStr,ErrObjSub,met);
				nfunc=0xFFFFFFFFL;
				break;
			}
		}catch(CDaoException e)
		{
			char *str=new char [200+(int)strlen(pos)];
			#ifdef RUS
				sprintf(str,"Ошибка выполнения метода %s %s\x7F%s\x7F%s",met,pos,(LPCTSTR)e.m_pErrorInfo->m_strDescription,(LPCTSTR)e.m_pErrorInfo->m_strSource);
			#else
				sprintf(str,"Error execution of method %s %s\x7F%s\x7F%s",met,pos,(LPCTSTR)e.m_pErrorInfo->m_strDescription,(LPCTSTR)e.m_pErrorInfo->m_strSource);
			#endif
			e.ReportError();
			if (oStr!=NULL) strcpy(oStr,str);
			nfunc=0xFFFFFFFFL;
			delete[] str;
		}
	}catch(...)
	{
		char *str=new char [200+(int)strlen(pos)];
		#ifdef RUS
			sprintf(str,"Ошибка выполнения метода %s %s",met,pos);
		#else
			sprintf(str,"Error execution of method %s %s",met,pos);
		#endif
		AfxMessageBox(str,MB_OK|MB_ICONEXCLAMATION);
		if (oStr!=NULL) strcpy(oStr,str);
		nfunc=0xFFFFFFFFL;
		GPC.m_ErrReport.GPWriteErrorLog("GPCDAOQueryDef", "DoMethod",iMethod);
		delete[] str;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
	delete[] met;
	return nfunc;
}

void GPCDAOQueryDef::GetPIString(CDaoParameterInfo &pinfo, char *oStrInfo)
{
	CString str;
	ConvertToString(pinfo.m_varValue,str,"\x7F");
	sprintf(oStrInfo,"%s\x7F%s\x7F%s",
		(LPCTSTR)pinfo.m_strName,
		GPCDAORecordset::ReTranslateFieldType(pinfo.m_nType),
		(LPCTSTR)str
		);
}
