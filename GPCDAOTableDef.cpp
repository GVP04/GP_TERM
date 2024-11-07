// GPCDAOTableDef.cpp: implementation of the GPCDAOTableDef class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPCDAOTableDef.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPCDAOTableDef::GPCDAOTableDef(CDaoDatabase* pDatabase )
	:CDaoTableDef(pDatabase)
{

}

GPCDAOTableDef::~GPCDAOTableDef()
{

}

BOOL GPCDAOTableDef::GPIsOpen()
{
	return IsOpen();
}

void GPCDAOTableDef::GPClose()
{
	Close();
}

BOOL GPCDAOTableDef::GPOpen(const char *iStr)
{
	BOOL ret=FALSE;
	try
	{try
	{
		Open(iStr);
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

BOOL GPCDAOTableDef::GPCreate(const char *iStr)
{
	char *str=new char [(int)strlen(iStr)+20];
	BOOL ret=FALSE;
	try
	{try
	{
		char *lpszName=str;
		char *lpAttributes;
		char *lpszSrcTable;
		char *lpszConnect;

		lpszSrcTable=strchr(lpszName,';');
		if (lpszSrcTable!=NULL) *(lpszSrcTable++)=0;
		else lpszSrcTable="";

		lpAttributes=strchr(lpszSrcTable,';');
		if (lpAttributes!=NULL) *(lpAttributes++)=0;
		else lpAttributes="";

		lpszConnect=strchr(lpAttributes,';');
		if (lpszConnect!=NULL) *(lpszConnect++)=0;
		else lpszConnect="";
		
		if (*lpszSrcTable==0) lpszSrcTable=NULL;
		if (*lpszConnect==0) lpszConnect=NULL;

		Create(lpszName, GPCDAODatabase::TranslateTDefAttr(lpAttributes) , lpszSrcTable , lpszConnect);
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

int GPCDAOTableDef::DoMethod(const char *iMethod, char *oStr)
{
	char *met=new char [(int)strlen(iMethod)+50];
	strcpy(met,iMethod);
	const char *pos=strchr(iMethod,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc;
	char *fn[33]={
		"Append","CanUpdate","GetAttributes","GetConnect","GetDateCreated",
		"GetDateLastUpdated","GetFieldCount","GetFieldInfo","GetFieldInfoById","GetFieldsInfo",
		"GetIndexCount","GetIndexInfo","GetIndexInfoById","GetIndexesInfo","GetName",
		"GetRecordCount","GetSourceTableName","GetValidationRule","GetValidationText","IsOpen",
		"SetAttributes","SetConnect","SetName","SetSourceTableName","SetValidationRule",
		"SetValidationText","CreateField","CreateIndex","DeleteField","DeleteFieldById",
		"DeleteIndex","DeleteIndexById","RefreshLink",
		};

	if (*met>='0' && *met<='9') nfunc=atoi(met);
	else
		for(nfunc=0;nfunc<33 && _stricmp(met,fn[nfunc])!=0;nfunc++); 

	int retint=-123456; 
	int atoipos=atoi(pos);

	try
	{
		try
		{
			switch(nfunc)
			{
			case 0:	/*Append*/				Append();	break;
			case 1:	/*CanUpdate*/			if (IsOpen()) retint=CanUpdate();	break;	
			case 2:	/*GetAttributes*/
				if (oStr!=NULL)
					strcpy(oStr,(LPCTSTR)(GPCDAODatabase::ReTranslateTDefAttr(GetAttributes( ))));
				break;
			case 3:	/*GetConnect*/			if (oStr!=NULL) strcpy(oStr,GetConnect());	break;
			case 4:	/*GetDateCreated*/
				if (oStr!=NULL) 
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
			case 5:	/*GetDateLastUpdated*/	
				if (oStr!=NULL) 
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
			case 6:	/*GetFieldCount*/	if (IsOpen()) retint=GetFieldCount();	break;
			case 7:	/*GetFieldInfo*/
			case 8:	/*GetFieldInfoById*/
				if (IsOpen() && oStr!=NULL)
				{
					CDaoFieldInfo finfo;
					if (nfunc==8)	GetFieldInfo(atoipos,finfo,AFX_DAO_ALL_INFO);
					else			GetFieldInfo(pos,finfo,AFX_DAO_ALL_INFO);
					GPCDAORecordset::GetFIString(finfo,oStr);
				}
				break;
			case 9:	/*GetFieldsInfo*/
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
			case 10:/*GetIndexCount*/	if (IsOpen()) retint=GetIndexCount();	break;	
			case 11:/*GetIndexInfo*/	
			case 12:/*GetIndexInfoById*/
				if (IsOpen() && oStr!=NULL)
				{
					CDaoIndexInfo iinfo;
					if (nfunc==12)	GetIndexInfo(atoipos,iinfo,AFX_DAO_ALL_INFO);
					else			GetIndexInfo(pos,iinfo,AFX_DAO_ALL_INFO);
					GPCDAORecordset::GetIIString(iinfo,oStr);
				}
				break;
			case 13:/*GetIndexesInfo*/	
				if (IsOpen() && oStr!=NULL) 
				{
					int nIndex;
					char *pos333=oStr;
					int nIndexes=GetIndexCount();
					CDaoIndexInfo iinfo;
					for(nIndex=0;nIndex<nIndexes;nIndex++)
					{
						if (nIndex>0)	strcat(pos333++,"\x7F");
						GetIndexInfo(nIndex,iinfo,AFX_DAO_ALL_INFO);
						GPCDAORecordset::GetIIString(iinfo,pos333);
						pos333+=(int)strlen(pos333);
					}
				}
				break;
			case 14:/*GetName*/			if (oStr!=NULL) strcpy(oStr,GetName());	break;
			case 15:/*GetRecordCount*/	if (IsOpen()) retint=GetRecordCount();		break;	
			case 16:/*GetSourceTableName*/	if (oStr!=NULL) strcpy(oStr,GetSourceTableName());	break;
			case 17:/*GetValidationRule*/	if (oStr!=NULL) strcpy(oStr,GetValidationRule());	break;
			case 18:/*GetValidationText*/	if (oStr!=NULL) strcpy(oStr,GetValidationText());	break;
			case 19:/*IsOpen*/				retint=IsOpen();			break;
			case 20:/*SetAttributes*/		SetAttributes(GPCDAODatabase::TranslateTDefAttr(pos));	break;
			case 21:/*SetConnect*/			SetConnect(pos);			break;	
			case 22:/*SetName*/				SetName(pos);				break;
			case 23:/*SetSourceTableName*/	SetSourceTableName(pos);	break;
			case 24:/*SetValidationRule*/	SetValidationRule(pos);		break;
			case 25:/*SetValidationText*/	SetValidationText(pos);		break;	
			case 26:/*CreateField*/
				if (IsOpen()) 
				{
					char *cParam[14]={
								"NAME=","TYPE=","SIZE=","ATTR=","OPOS=",
								"REQU=","AZERO=","CORDER=","FORNM=","SFIELD=",
								"STABLE=","VRULE=","VTEXT=","DEFVAL=",
								};

					char *cPos[14]={
								NULL,NULL,NULL,NULL,NULL,
								NULL,NULL,NULL,NULL,NULL,
								NULL,NULL,NULL,NULL,
								};

					char *postmpcc=new char [(int)strlen(pos)+10];
					strcpy(postmpcc,pos);

					CDaoFieldInfo fieldinfo;
					fieldinfo.m_strName="";        // Primary
					fieldinfo.m_nType=0;               // Primary
					fieldinfo.m_lSize=0;                // Primary
					fieldinfo.m_lAttributes=0;          // Primary
					fieldinfo.m_nOrdinalPosition=0;    // Secondary
					fieldinfo.m_bRequired=0;            // Secondary
					fieldinfo.m_bAllowZeroLength=1;     // Secondary
					fieldinfo.m_lCollatingOrder=0;      // Secondary
					fieldinfo.m_strForeignName="";    // Secondary
					fieldinfo.m_strSourceField="";    // Secondary
					fieldinfo.m_strSourceTable="";    // Secondary
					fieldinfo.m_strValidationRule=""; // All
					fieldinfo.m_strValidationText=""; // All
					fieldinfo.m_strDefaultValue="";   // All

					int i;
					for(i=0;i<14;i++)
						if ((cPos[i]=strstr(postmpcc,cParam[i]))!=NULL)
							cPos[i]+=(int)strlen(cParam[i]);

					for(i=0;i<14;i++)
						if (cPos[i]!=NULL)
						{
							char *tmppos;
							tmppos=strchr(cPos[i],';');
							if (tmppos!=NULL) *tmppos=0;
							switch(i)
							{
							case 0:/*"NAME="*/	fieldinfo.m_strName=cPos[i];		break;
							case 1:/*"TYPE="*/	fieldinfo.m_nType=GPCDAORecordset::TranslateFieldType(_strupr(cPos[i]));	break;
							case 2:/*"SIZE="*/	fieldinfo.m_lSize=atoi(cPos[i]);	break;
							case 3:/*"ATTR="*/	fieldinfo.m_lAttributes=GPCDAORecordset::TranslateFieldAttr(_strupr(cPos[i]));	break;
							case 4:/*"OPOS="*/	fieldinfo.m_nOrdinalPosition=atoi(cPos[i]);	break;
							case 5:/*"REQU="*/	fieldinfo.m_bRequired=(atoi(cPos[i])&0x1);	break;
							case 6:/*"AZERO="*/	fieldinfo.m_bAllowZeroLength=(atoi(cPos[i])&0x1);	break;
							case 7:/*"CORDER="*/fieldinfo.m_lCollatingOrder=atoi(cPos[i]);	break;
							case 8:/*"FORNM="*/		fieldinfo.m_strForeignName=cPos[i];		break;
							case 9:/*"SFIELD="*/	fieldinfo.m_strSourceField=cPos[i];		break;
							case 10:/*"STABLE="*/	fieldinfo.m_strSourceTable=cPos[i];		break;
							case 11:/*"VRULE="*/	fieldinfo.m_strValidationRule=cPos[i];	break;
							case 12:/*"VTEXT="*/	fieldinfo.m_strValidationText=cPos[i];	break;
							case 13:/*"DEFVAL="*/	fieldinfo.m_strDefaultValue=cPos[i];	break;
							}
						}
					CreateField(fieldinfo);
					delete[] postmpcc;
				}
				break;
			case 27:/*CreateIndex*/
				if (IsOpen()) 
				{
					char *cParam[9]={
								"NAME=","PRIMARY=","UNIQUE=","CLUSTERED=","IGNULL=",
								"REQU=","FOREIGN=","DISCOUNT=","FIELDS=",
								};

					char *cPos[9]={
								NULL,NULL,NULL,NULL,NULL,
								NULL,NULL,NULL,NULL,
								};

					char *postmpcc=new char [(int)strlen(pos)+10];
					strcpy(postmpcc,pos);

					CDaoIndexFieldInfo FieldInfos[32];

					CDaoIndexInfo indexinfo;
					indexinfo.m_strName="";       
					indexinfo.m_nFields=0;               
					indexinfo.m_pFieldInfos=FieldInfos;      
					indexinfo.m_bPrimary=0;          
					indexinfo.m_bUnique=0;   
					indexinfo.m_bClustered=0;            
					indexinfo.m_bIgnoreNulls=1;    
					indexinfo.m_bRequired=0;      
					indexinfo.m_bForeign=0;   
					indexinfo.m_lDistinctCount=0;    

					int i;
					for(i=0;i<9;i++)
						if ((cPos[i]=strstr(postmpcc,cParam[i]))!=NULL)
							cPos[i]+=(int)strlen(cParam[i]);

					for(i=0;i<9;i++)
						if (cPos[i]!=NULL)
						{
							char *tmppos;
							tmppos=strchr(cPos[i],';');
							if (tmppos!=NULL) *tmppos=0;
							switch(i)
							{
							case 0:/*"NAME="*/		indexinfo.m_strName=cPos[i];				break;
							case 1:/*"PRIMARY="*/	indexinfo.m_bPrimary=(atoi(cPos[i])&0x1);		break;
							case 2:/*"UNIQUE="*/	indexinfo.m_bUnique=(atoi(cPos[i])&0x1);		break;
							case 3:/*"CLUSTERED="*/	indexinfo.m_bClustered=(atoi(cPos[i])&0x1);	break;
							case 4:/*"IGNULL="*/	indexinfo.m_bIgnoreNulls=(atoi(cPos[i])&0x1);	break;
							case 5:/*"REQU="*/		indexinfo.m_bRequired=(atoi(cPos[i])&0x1);	break;
							case 6:/*"FOREIGN="*/	indexinfo.m_bForeign=(atoi(cPos[i])&0x1);		break;
							case 7:/*"DISCOUNT="*/	indexinfo.m_lDistinctCount=atoi(cPos[i]);	break;
							case 8:/*"FIELDS="*/
								{
									char *pos2=cPos[i];
									while(pos2!=NULL && indexinfo.m_nFields<31)
									{
										char *pos3=strchr(pos2,GPC.DelimiterIn1);
										if (pos3!=NULL) *(pos3++)=0;
										char *posDesc=strchr(pos2,',');
										FieldInfos[indexinfo.m_nFields].m_bDescending=0;
										if (posDesc!=NULL)
										{
											*(posDesc++)=0;
											FieldInfos[indexinfo.m_nFields].m_bDescending=(atoi(posDesc)&0x1);
										}
										FieldInfos[indexinfo.m_nFields].m_strName=pos2;
										indexinfo.m_nFields++;
										pos2=pos3;
									}
								}
							}
						}
					CreateIndex(indexinfo);
					delete[] postmpcc;
				}
				break;
			case 28:/*DeleteField*/		if (IsOpen()) DeleteField(pos);		break;
			case 29:/*DeleteFieldById*/	if (IsOpen()) DeleteField(atoipos);	break;
			case 30:/*DeleteIndex*/		if (IsOpen()) DeleteIndex(pos);		break;
			case 31:/*DeleteIndexById*/	if (IsOpen()) DeleteIndex(atoipos);	break;
			case 32:/*RefreshLink*/		if (IsOpen()) RefreshLink();			break;
			default:
				GPC.m_ErrReport.GPWriteWarnLog2("GPCDAOTableDef", "Unknown Method",iMethod);
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
		GPC.m_ErrReport.GPWriteErrorLog("GPCDAOTableDef", "DoMethod",iMethod);
		delete[] str;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
	delete[] met;
	return nfunc;}
