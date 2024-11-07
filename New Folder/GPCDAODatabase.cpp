// GPCDAODatabase.cpp: implementation of the GPCDAODatabase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPCDAODatabase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const UINT		GPCDAODatabase::nArrCollation=25;
const char *	GPCDAODatabase::cArrCollationName[]={
					"SORTNEUTRAL","SORTARABIC","SORTCYRILLIC","SORTCZECH","SORTDUTCH",
					"SORTGENERAL","SORTGREEK","SORTHEBREW","SORTHUNGARIAN","SORTICELANDIC",
					"SORTNORWDAN","SORTPDXINTL","SORTPDXNOR","SORTPDXSWE","SORTPOLISH",
					"SORTSPANISH","SORTSWEDFIN","SORTTURKISH","SORTJAPANESE","SORTCHINESESIMPLIFIED",
					"SORTCHINESETRADITIONAL","SORTKOREAN","SORTTHAI","SORTSLOVENIAN","SORTUNDEFINED",
					"",
					};

const long		GPCDAODatabase::lArrCollation[]={
					dbSortNeutral,dbSortArabic,dbSortCyrillic,dbSortCzech,dbSortDutch,
					dbSortGeneral,dbSortGreek,dbSortHebrew,dbSortHungarian,dbSortIcelandic,
					dbSortNorwdan,dbSortPDXIntl,dbSortPDXNor,dbSortPDXSwe,dbSortPolish,
					dbSortSpanish,dbSortSwedFin,dbSortTurkish,dbSortJapanese,dbSortChineseSimplified,
					dbSortChineseTraditional,dbSortKorean,dbSortThai,dbSortSlovenian,dbSortUndefined,
					0,
					};

const UINT		GPCDAODatabase::nArrQDefType=13;
const char *	GPCDAODatabase::cArrQDefTypeName[]={
					"QSELECT","QPROCEDURE","QACTION","QCROSSTAB","QDELETE",
					"QUPDATE","QAPPEND","QMAKETABLE","QDDL","QSQLPASSTHROUGH",
					"QSETOPERATION","QSPTBULK","QCOMPOUND","",
					};
const int		GPCDAODatabase::iArrQDefType[]={
					dbQSelect,dbQProcedure,dbQAction,dbQCrosstab,dbQDelete,
					dbQUpdate,dbQAppend,dbQMakeTable,dbQDDL,dbQSQLPassThrough,
					dbQSetOperation,dbQSPTBulk,dbQCompound,0,
					};

const UINT		GPCDAODatabase::nArrRelAtt=7;
const char *	GPCDAODatabase::cArrRelAttName[]={
					"UNIQUE","DONTENFORCE","INHERITED","LEFT","RIGHT",
					"UPDATECASCADE","DELETECASCADE",
					};
const long		GPCDAODatabase::lArrRelAtt[]={
					dbRelationUnique,dbRelationDontEnforce,dbRelationInherited,dbRelationLeft,dbRelationRight,
					dbRelationUpdateCascade,dbRelationDeleteCascade,
					};

const UINT		GPCDAODatabase::nArrExecuteOpt=12;
const char *	GPCDAODatabase::cArrExecuteOptName[]={
					"DENYWRITE","DENYREAD","READONLY","APPENDONLY","INCONSISTENT",
					"CONSISTENT","SQLPASSTHROUGH","FAILONERROR","FORWARDONLY","SEECHANGES",
					"RUNASYNC","EXECDIRECT",
					};
const int		GPCDAODatabase::iArrExecuteOpt[]={
					dbDenyWrite,dbDenyRead,dbReadOnly,dbAppendOnly,dbInconsistent,
					dbConsistent,dbSQLPassThrough,dbFailOnError,dbForwardOnly,dbSeeChanges,
					dbRunAsync,dbExecDirect,
					};

const UINT		GPCDAODatabase::nArrTDefAtt=6;
const char *	GPCDAODatabase::cArrTDefAttName[]={
					"ATTACHEXCLUSIVE","ATTACHSAVEPWD","SYSTEMOBJECT","ATTACHEDTABLE","ATTACHEDODBC",
					"HIDDENOBJECT",
					};
const long		GPCDAODatabase::lArrTDefAtt[]={
					dbAttachExclusive,dbAttachSavePWD,dbSystemObject,dbAttachedTable,dbAttachedODBC,
					dbHiddenObject,
					};




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPCDAODatabase::GPCDAODatabase(CDaoWorkspace* pdb) : CDaoDatabase(pdb)
{
	int i;
	for(i=0;i<N_DAORECORDSET_COUNT;i++)
		a_GPDAORecodset[i]=NULL;

	for( i=0;i<N_DAOQUERYDEF_COUNT;i++)
		a_GPDAOQueryDef[i]=NULL;

	for( i=0;i<N_DAOTABLEDEF_COUNT;i++)
		a_GPDAOTableDef[i]=NULL;
}

GPCDAODatabase::~GPCDAODatabase()
{
	GPClose();
}

int GPCDAODatabase::DoMethod(const char *iMethod, char *oStr)
{
	char *met=new char [(int)strlen(iMethod)+50];
	strcpy(met,iMethod);
	const char *pos=strchr(iMethod,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc;
	char *fn[21]={
		"CanTransact","CanUpdate","GetConnect","GetName","GetQueryTimeout",
		"GetRecordsAffected","GetVersion","IsOpen","SetQueryTimeout","CreateRelation",
		"DeleteQueryDef","DeleteRelation","DeleteTableDef","Execute","GetQueryDefCount",
		"GetQueryDefInfo","GetRelationCount","GetRelationInfo","GetTableDefCount","GetTableDefInfo",
		"GetTableDefAllInfo",
	};

	if (*met>='0' && *met<='9') nfunc=atoi(met);
	else
		for(nfunc=0;nfunc<21 && _stricmp(met,fn[nfunc])!=0;nfunc++); 

	int retint=-123456; 
	int atoipos=atoi(pos);

	try
	{
		switch(nfunc)
		{
		case 0:	/*CanTransact*/		retint=CanTransact();	break;
		case 1:	/*CanUpdate*/		retint=CanUpdate();		break;
		case 2:	/*GetConnect*/		if (oStr!=NULL) strcpy(oStr,GetConnect());	break;
		case 3:	/*GetName*/			if (oStr!=NULL) strcpy(oStr,GetName());		break;
		case 4:	/*GetQueryTimeout*/	retint=GetQueryTimeout();	break;
		case 5:	/*GetRecordsAffected*/	retint=GetRecordsAffected();	break;
		case 6:	/*GetVersion*/		if (oStr!=NULL) strcpy(oStr,GetVersion());	break;
		case 7:	/*IsOpen*/			retint=IsOpen();	break;
		case 8:	/*SetQueryTimeout*/	SetQueryTimeout(atoipos);	break;
		case 9:	/*CreateRelation*/
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				_strupr(pos333);
				CDaoRelationInfo relinfo;
				CDaoRelationFieldInfo finfo[100];
				relinfo.m_nFields=0;
				relinfo.m_pFieldInfos=finfo;
				relinfo.m_lAttributes=0;

				char *cParam[5]={"NAME=","TABLE=","TABLE2=","ATTR=","FIELD=",};
				int i;
				for(i=0;i<5;i++)
				{
					char *posPar=strstr(pos333,cParam[i]);
					if (posPar!=NULL)
					{
						posPar+=(int)strlen(cParam[i]);
						char *posend=strchr(posPar,';');
						if (posend!=NULL) *posend=0;
						switch(i)
						{
						case 0:/*"NAME="*/		relinfo.m_strName=posPar;			break;
						case 1:/*"TABLE="*/		relinfo.m_strTable=posPar;			break;
						case 2:/*"TABLE2="*/	relinfo.m_strForeignTable=posPar;	break;
						case 3:/*"ATTR="*/		relinfo.m_lAttributes=TranslateRelAttr(posPar);	break;
						case 4:/*"FIELD="*/
							{
								do
								{
									char *tmp2=strchr(posPar,',');
									if (tmp2!=NULL) *tmp2=0;
									finfo[relinfo.m_nFields].m_strName=posPar;
									if (tmp2!=NULL)
									{
										*(tmp2++)=',';
										finfo[relinfo.m_nFields].m_strForeignName=tmp2+1;
									}
									relinfo.m_nFields++;
				
									if (posend!=NULL)
									{
										*posend=';';
										posPar=strstr(posend,cParam[i]);
										if (posPar==NULL) break;
										posPar+=(int)strlen(cParam[i]);
										posend=strchr(posPar,';');
									}
									else posPar=NULL;
								}
								while(posPar!=NULL && relinfo.m_nFields<99);
							}
							break;
						}
						if (posend!=NULL) *posend=';';
					}
				}
				CreateRelation(relinfo);
				delete[] pos333;
			}
			break;
		case 10:	/*DeleteQueryDef*/	DeleteQueryDef(pos);	break;
		case 11:	/*DeleteRelation*/	DeleteRelation(pos);	break;
		case 12:	/*DeleteTableDef*/	DeleteTableDef(pos);	break;
		case 13:	/*Execute*/
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				_strupr(pos333);
				char *posSQL=strchr(pos333,';');
				if (posSQL!=NULL)
				{
					*(posSQL++)=0;
					Execute(posSQL,TranslateExecuteOptions(pos333));
				}
				delete[] pos333;
			}
			break;
		case 14:	/*GetQueryDefCount*/	retint=GetQueryDefCount();	break;
		case 15:	/*GetQueryDefInfo*/
			if (oStr!=NULL)
			{
				CDaoQueryDefInfo QDI;
				GetQueryDefInfo(pos,QDI,AFX_DAO_ALL_INFO);
				char *outpos=oStr;
				outpos+=sprintf(outpos,"%s\x7F%s\x7F%s\x7F%s\x7F%d\x7F%d\x7F%d\x7F",
				(LPCTSTR)QDI.m_strName,
				(LPCTSTR)QDI.m_strSQL,
				(LPCTSTR)QDI.m_strConnect,
				(LPCTSTR)ReTranslateQDefType(QDI.m_nType),
				QDI.m_bUpdatable,
				QDI.m_bReturnsRecords,
				QDI.m_nODBCTimeout);


				outpos+=sprintf(outpos,"%d\x7%d\x7%d\x7%d\x7%d\x7%d\x7F",
						QDI.m_dateCreated.GetYear(),
						QDI.m_dateCreated.GetMonth(),
						QDI.m_dateCreated.GetDay(),
						QDI.m_dateCreated.GetHour(),
						QDI.m_dateCreated.GetMinute(),
						QDI.m_dateCreated.GetSecond());

				outpos+=sprintf(outpos,"%d\x7%d\x7%d\x7%d\x7%d\x7%d",
						QDI.m_dateLastUpdated.GetYear(),
						QDI.m_dateLastUpdated.GetMonth(),
						QDI.m_dateLastUpdated.GetDay(),
						QDI.m_dateLastUpdated.GetHour(),
						QDI.m_dateLastUpdated.GetMinute(),
						QDI.m_dateLastUpdated.GetSecond());

			}
			break;
		case 16:	/*GetRelationCount*/	retint=GetRelationCount();	break;
		case 17:	/*GetRelationInfo*/
			if (oStr!=NULL)
			{
				CDaoRelationInfo relinfo;
				GetRelationInfo(pos,relinfo,AFX_DAO_SECONDARY_INFO|AFX_DAO_PRIMARY_INFO);
				char *outpos=oStr;
				outpos+=sprintf(outpos,"%s\x7F%s\x7F%s\x7F%s\x7F%d\x7F",
					(LPCTSTR)relinfo.m_strName,
					(LPCTSTR)relinfo.m_strTable,
					(LPCTSTR)relinfo.m_strForeignTable,
					(LPCTSTR)ReTranslateRelAttr(relinfo.m_lAttributes),
					relinfo.m_nFields);

				int i;
				for(i=0;i<relinfo.m_nFields;i++)
				{
					if (i>0) *(outpos++)=0x7F;
					outpos+=sprintf(outpos,"%s\x7%s",(LPCSTR)relinfo.m_pFieldInfos[i].m_strName,(LPCSTR)relinfo.m_pFieldInfos[i].m_strForeignName);
				}
			}
			break;
		case 18:	/*GetTableDefCount*/	retint=GetTableDefCount();	break;
		case 19:	/*GetTableDefInfo*/
			{
				CDaoTableDefInfo tabledefinfo;
				GetTableDefInfo(pos, tabledefinfo, AFX_DAO_PRIMARY_INFO|AFX_DAO_SECONDARY_INFO);

				char *outpos=oStr;
				outpos+=sprintf(outpos,"%s\x7F%s\x7F%s\x7F%s\x7F%d\x7F",
				(LPCTSTR)tabledefinfo.m_strName,
				(LPCTSTR)tabledefinfo.m_strSrcTableName,
				(LPCTSTR)tabledefinfo.m_strConnect,
				(LPCTSTR)ReTranslateTDefAttr(tabledefinfo.m_lAttributes),
				tabledefinfo.m_bUpdatable);

				outpos+=sprintf(outpos,"%d\x7%d\x7%d\x7%d\x7%d\x7%d\x7F",
						tabledefinfo.m_dateCreated.GetYear(),
						tabledefinfo.m_dateCreated.GetMonth(),
						tabledefinfo.m_dateCreated.GetDay(),
						tabledefinfo.m_dateCreated.GetHour(),
						tabledefinfo.m_dateCreated.GetMinute(),
						tabledefinfo.m_dateCreated.GetSecond());

				outpos+=sprintf(outpos,"%d\x7%d\x7%d\x7%d\x7%d\x7%d",
						tabledefinfo.m_dateLastUpdated.GetYear(),
						tabledefinfo.m_dateLastUpdated.GetMonth(),
						tabledefinfo.m_dateLastUpdated.GetDay(),
						tabledefinfo.m_dateLastUpdated.GetHour(),
						tabledefinfo.m_dateLastUpdated.GetMinute(),
						tabledefinfo.m_dateLastUpdated.GetSecond());
			}
			break;
		case 20:	/*GetTableDefAllInfo*/
			{
				CDaoTableDefInfo tabledefinfo;
				GetTableDefInfo(pos, tabledefinfo, AFX_DAO_ALL_INFO);

				char *outpos=oStr;
				outpos+=sprintf(outpos,"%s\x7F%s\x7F%s\x7F%s\x7F%s\x7F%s\x7F%d\x7F%d\x7F",
				(LPCTSTR)tabledefinfo.m_strName,
				(LPCTSTR)tabledefinfo.m_strSrcTableName,
				(LPCTSTR)tabledefinfo.m_strConnect,
				(LPCTSTR)tabledefinfo.m_strValidationRule,
				(LPCTSTR)tabledefinfo.m_strValidationText,
				(LPCTSTR)ReTranslateTDefAttr(tabledefinfo.m_lAttributes),
				tabledefinfo.m_bUpdatable,
				tabledefinfo.m_lRecordCount);

				outpos+=sprintf(outpos,"%d\x7%d\x7%d\x7%d\x7%d\x7%d\x7F",
						tabledefinfo.m_dateCreated.GetYear(),
						tabledefinfo.m_dateCreated.GetMonth(),
						tabledefinfo.m_dateCreated.GetDay(),
						tabledefinfo.m_dateCreated.GetHour(),
						tabledefinfo.m_dateCreated.GetMinute(),
						tabledefinfo.m_dateCreated.GetSecond());

				outpos+=sprintf(outpos,"%d\x7%d\x7%d\x7%d\x7%d\x7%d",
						tabledefinfo.m_dateLastUpdated.GetYear(),
						tabledefinfo.m_dateLastUpdated.GetMonth(),
						tabledefinfo.m_dateLastUpdated.GetDay(),
						tabledefinfo.m_dateLastUpdated.GetHour(),
						tabledefinfo.m_dateLastUpdated.GetMinute(),
						tabledefinfo.m_dateLastUpdated.GetSecond());
			}
			break;
		default:
			GPC.m_ErrReport.GPWriteWarnLog2("GPCDAODatabase", "Unknown Method",iMethod);
			if (oStr!=NULL)		 sprintf(oStr,ErrObjSub,met);
			nfunc=0xFFFFFFFFL;
			break;
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
		GPC.m_ErrReport.GPWriteErrorLog("GPCDAODatabase", "DoMethod",iMethod);
		delete[] str;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
	delete[] met;
	return nfunc;
};

void GPCDAODatabase::GPClose()
{
	int i;
	for(i=0;i<N_DAORECORDSET_COUNT;i++)
		if (a_GPDAORecodset[i]!=NULL)
		{
			try
			{
				if (a_GPDAORecodset[i]->GPIsOpen()) a_GPDAORecodset[i]->Close();
			}catch(...)
			{
				GPC.m_ErrReport.GPWriteErrorLog("GPCDAODatabase", "GPClose 376","");
			}
			delete a_GPDAORecodset[i];
			a_GPDAORecodset[i]=NULL;
		}

	for(i=0;i<N_DAOQUERYDEF_COUNT;i++)
		if (a_GPDAOQueryDef[i]!=NULL)
		{
			try
			{
				if (a_GPDAOQueryDef[i]->GPIsOpen()) a_GPDAOQueryDef[i]->GPClose();
			}catch(...)
			{
				GPC.m_ErrReport.GPWriteErrorLog("GPCDAODatabase", "GPClose 390","");
			}
			delete a_GPDAOQueryDef[i];
			a_GPDAOQueryDef[i]=NULL;
		}

	for(i=0;i<N_DAOTABLEDEF_COUNT;i++)
		if (a_GPDAOTableDef[i]!=NULL)
		{
			try
			{
				if (a_GPDAOTableDef[i]->GPIsOpen()) a_GPDAOTableDef[i]->GPClose();
			}catch(...)
			{
				GPC.m_ErrReport.GPWriteErrorLog("GPCDAODatabase", "GPClose 404","");
			}
			delete a_GPDAOTableDef[i];
			a_GPDAOTableDef[i]=NULL;
		}
		
	try
	{
		if (IsOpen()) Close();
	}catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPCDAODatabase", "GPClose 415","");
	}
}

BOOL GPCDAODatabase::GPIsOpen()
{
	return IsOpen();
}

BOOL GPCDAODatabase::GPOpen(const char *iStr)
{
	try
	{
		if (IsOpen()) GPClose();
	}catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPCDAODatabase", "GPOpen 431",iStr);
	}

	BOOL ret=FALSE;
	BOOL Share=FALSE,ReadOnly=FALSE;
	char *str=new char [(int)strlen(iStr)+20];
	*str=0;
	m_LastScanf=sscanf(iStr,"%d;%d;%s",&Share,&ReadOnly,str);
	char *posConnect=strchr(str,';');
	if (posConnect!=NULL) *(posConnect++)=0;
	else posConnect="";

	try
	{
		Open(str,Share,ReadOnly,posConnect);
		ret=TRUE;
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPCDAODatabase", "GPOpen 450",iStr);
	}

	delete[] str;
	return ret;
}

BOOL GPCDAODatabase::GPCreate(const char *iStr)
{
//0 027 0 231 0 043 GP.DAODatabaseCreate(/*WSVar,DBVar,*/szName,Options,szLocale)
	try
	{
		if (IsOpen()) GPClose();
	}catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPCDAODatabase", "GPCreate 465",iStr);
	}
	BOOL ret=FALSE;
	char *str=new char [(int)strlen(iStr)+20];
	strcpy(str,iStr);

	char *posOptions=strchr(str,';');
	if (posOptions!=NULL) *(posOptions++)=0;
	else posOptions="";

	char *posLocale=strchr(posOptions,';');
	if (posLocale!=NULL) *(posLocale++)=0;
	else posLocale="";

	try
	{
		Create(str,GPCDAOWorkspace::TranslateLocale(posLocale),GPCDAOWorkspace::TranslateOptions(posOptions));
		ret=TRUE;
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPCDAODatabase", "GPCreate 486",iStr);
	}

	delete[] str;
	return ret;
}

int GPCDAODatabase::OpenRS(const char *posRS)
{
	int IdRS;
	int ret=-1;
	for(IdRS=0;IdRS<N_DAORECORDSET_COUNT && a_GPDAORecodset[IdRS]!=NULL;IdRS++);

	if (IdRS<N_DAORECORDSET_COUNT)
	{
		a_GPDAORecodset[IdRS]=new GPCDAORecordset(this);

		if (a_GPDAORecodset[IdRS]->GPOpen(posRS)==TRUE)	ret=IdRS;
		else
		{
			delete a_GPDAORecodset[IdRS];
			a_GPDAORecodset[IdRS]=NULL;
		}
	}
	return ret;
}

BOOL GPCDAODatabase::CloseRS(int IdRS)
{
	BOOL ret=FALSE;
	if (IdRS>=0 && IdRS<N_DAORECORDSET_COUNT && a_GPDAORecodset[IdRS]!=NULL)
	{
		if (a_GPDAORecodset[IdRS]->GPIsOpen()) a_GPDAORecodset[IdRS]->Close();
		delete a_GPDAORecodset[IdRS];
		a_GPDAORecodset[IdRS]=NULL;
		ret=TRUE;
	}
	return ret;
}

int GPCDAODatabase::DoRSMethod(const char *iMethod, char *oStr)
{
	int ret=0;

	const char *posmet=strchr(iMethod,';');
	if (posmet++==NULL) posmet="";

	int IdRS=atoi(iMethod);
	if (IdRS>=0 && IdRS<N_DAORECORDSET_COUNT && a_GPDAORecodset[IdRS]!=NULL)
	{
		if (a_GPDAORecodset[IdRS]->m_DosAnsiFlag)
		{
			if (a_GPDAORecodset[IdRS]->DoMethod(posmet,oStr)>=0) ret=1;
		}
		else
		{
			AnsiToDos((char *)posmet,0);
			if (a_GPDAORecodset[IdRS]->DoMethod(posmet,oStr)>=0) ret=2;
		}
	}

	return ret;
}

int GPCDAODatabase::DoQDMethod(const char *iMethod, char *oStr)
{
	BOOL ret=FALSE;

	const char *posmet=strchr(iMethod,';');
	if (posmet++==NULL) posmet="";

	int IdQDef=atoi(iMethod);
	if (IdQDef>=0 && IdQDef<N_DAOQUERYDEF_COUNT && a_GPDAOQueryDef[IdQDef]!=NULL
		&& a_GPDAOQueryDef[IdQDef]->DoMethod(posmet,oStr)>=0) ret=TRUE;

	return ret;
}

int GPCDAODatabase::DoTDMethod(const char *iMethod, char *oStr)
{
	BOOL ret=FALSE;

	const char *posmet=strchr(iMethod,';');
	if (posmet++==NULL) posmet="";

	int IdTDef=atoi(iMethod);
	if (IdTDef>=0 && IdTDef<N_DAOTABLEDEF_COUNT && a_GPDAOTableDef[IdTDef]!=NULL
		&& a_GPDAOTableDef[IdTDef]->DoMethod(posmet,oStr)>=0) ret=TRUE;

	return ret;
}

long GPCDAODatabase::TranslateRelAttr(const char *iStr)
{
	long ret=0;

	int i;
	for(i=0;i<nArrRelAtt;i++)
		if (strstr(iStr,cArrRelAttName[i])!=NULL) ret|=lArrRelAtt[i];

	return ret;
}

const CString GPCDAODatabase::ReTranslateRelAttr(long iAttr)
{
	CString ret;

	int i;
	for(i=0;i<nArrRelAtt;i++)
		if ((iAttr&lArrRelAtt[i])==lArrRelAtt[i])
		{
			if (ret.GetLength()>0) ret+="\x7";
			ret+=cArrRelAttName[i];
		}
	return ret;
}

const CString GPCDAODatabase::ReTranslateTDefAttr(long iAttr)
{
	CString ret;

	int i;
	for(i=0;i<nArrTDefAtt;i++)
		if ((iAttr&lArrTDefAtt[i])==lArrTDefAtt[i])
		{
			if (ret.GetLength()>0) ret+="\x7";
			ret+=cArrTDefAttName[i];
		}
	return ret;
}


int GPCDAODatabase::TranslateExecuteOptions(const char *iStr)
{
	int ret=0;
	int i;
	for(i=0;i<nArrExecuteOpt;i++)
		if (strstr(iStr,cArrExecuteOptName[i])!=NULL) ret|=iArrExecuteOpt[i];
	
	return ret;
}

int GPCDAODatabase::TranslateQDefType(const char *iStr)
{
	UINT i;
	for(i=0;i<nArrQDefType && strcmp(iStr,cArrQDefTypeName[i])!=0;i++);
	return iArrQDefType[i];
}

long GPCDAODatabase::TranslateTDefAttr(const char *iStr)
{
	UINT i;
	for(i=0;i<nArrTDefAtt && strcmp(iStr,cArrTDefAttName[i])!=0;i++);
	return lArrTDefAtt[i];
}

const char * GPCDAODatabase::ReTranslateQDefType(int iType)
{
	UINT i;
	for(i=0;i<nArrQDefType && iType!=iArrQDefType[i];i++);
	return cArrQDefTypeName[i];
}


long GPCDAODatabase::TranslateCollation(const char *iStr)
{
	UINT i;
	for(i=0;i<nArrCollation && _stricmp(iStr,cArrCollationName[i])!=0;i++);
	return lArrCollation[i];
}

const char * GPCDAODatabase::ReTranslateCollation(long iType)
{
	UINT i;
	for(i=0;i<nArrCollation && iType!=lArrCollation[i];i++);
	return cArrCollationName[i];
}

BOOL GPCDAODatabase::CloseGPQDef(int IdQDef)
{
	BOOL ret=FALSE;
	if (IdQDef>=0 && IdQDef<N_DAOQUERYDEF_COUNT && a_GPDAOQueryDef[IdQDef]!=NULL)
	{
		if (a_GPDAOQueryDef[IdQDef]->GPIsOpen()) a_GPDAOQueryDef[IdQDef]->Close();
		delete a_GPDAOQueryDef[IdQDef];
		a_GPDAOQueryDef[IdQDef]=NULL;
		ret=TRUE;
	}
	return ret;
}

BOOL GPCDAODatabase::CloseGPTDef(int IdTDef)
{
	BOOL ret=FALSE;
	if (IdTDef>=0 && IdTDef<N_DAOTABLEDEF_COUNT && a_GPDAOTableDef[IdTDef]!=NULL)
	{
		if (a_GPDAOTableDef[IdTDef]->GPIsOpen()) a_GPDAOTableDef[IdTDef]->Close();
		delete a_GPDAOTableDef[IdTDef];
		a_GPDAOTableDef[IdTDef]=NULL;
		ret=TRUE;
	}
	return ret;
}

int GPCDAODatabase::OpenGPQDef(const char *iStr)
{
	int IdQDef;
	int ret=-1;
	for(IdQDef=0;IdQDef<N_DAOQUERYDEF_COUNT && a_GPDAOQueryDef[IdQDef]!=NULL;IdQDef++);

	if (IdQDef<N_DAOQUERYDEF_COUNT)
	{
		a_GPDAOQueryDef[IdQDef]=new GPCDAOQueryDef(this);

		if (a_GPDAOQueryDef[IdQDef]->GPOpen(iStr)==TRUE)	ret=IdQDef;
		else
		{
			delete a_GPDAOQueryDef[IdQDef];
			a_GPDAOQueryDef[IdQDef]=NULL;
		}
	}
	return ret;
}

int GPCDAODatabase::OpenGPTDef(const char *iStr)
{
	int IdTDef;
	int ret=-1;
	for(IdTDef=0;IdTDef<N_DAOTABLEDEF_COUNT && a_GPDAOTableDef[IdTDef]!=NULL;IdTDef++);

	if (IdTDef<N_DAOTABLEDEF_COUNT)
	{
		a_GPDAOTableDef[IdTDef]=new GPCDAOTableDef(this);

		if (a_GPDAOTableDef[IdTDef]->GPOpen(iStr)==TRUE)	ret=IdTDef;
		else
		{
			delete a_GPDAOTableDef[IdTDef];
			a_GPDAOTableDef[IdTDef]=NULL;
		}
	}
	return ret;
}

int GPCDAODatabase::CreateGPQDef(const char *iStr)
{
	int IdQDef;
	int ret=-1;
	for(IdQDef=0;IdQDef<N_DAOQUERYDEF_COUNT && a_GPDAOQueryDef[IdQDef]!=NULL;IdQDef++);

	if (IdQDef<N_DAOQUERYDEF_COUNT)
	{
		a_GPDAOQueryDef[IdQDef]=new GPCDAOQueryDef(this);

		if (a_GPDAOQueryDef[IdQDef]->GPCreate(iStr)==TRUE)	ret=IdQDef;
		else
		{
			delete a_GPDAOQueryDef[IdQDef];
			a_GPDAOQueryDef[IdQDef]=NULL;
		}
	}
	return ret;
}

int GPCDAODatabase::CreateGPTDef(const char *iStr)
{
	int IdTDef;
	int ret=-1;
	for(IdTDef=0;IdTDef<N_DAOTABLEDEF_COUNT && a_GPDAOTableDef[IdTDef]!=NULL;IdTDef++);

	if (IdTDef<N_DAOTABLEDEF_COUNT)
	{
		a_GPDAOTableDef[IdTDef]=new GPCDAOTableDef(this);

		if (a_GPDAOTableDef[IdTDef]->GPCreate(iStr)==TRUE)	ret=IdTDef;
		else
		{
			delete a_GPDAOTableDef[IdTDef];
			a_GPDAOTableDef[IdTDef]=NULL;
		}
	}
	return ret;
}




