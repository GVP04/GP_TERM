// GPCDAORecordset.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPCDAORecordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const UINT GPCDAORecordset::nArrFieldAttr=5;
const long GPCDAORecordset::siArrFieldAttr[]={
			dbFixedField,dbVariableField,dbAutoIncrField,dbUpdatableField,dbDescending,dbFixedField,
			};
const char *GPCDAORecordset::cArrFieldAttrName[]={
			"FIXEDFIELD","VARIABLEFIELD","AUTOINCRFIELD","UPDATABLEFIELD","DESCENDING","",
			};

const UINT GPCDAORecordset::nArrOpenTbType=5;
const int GPCDAORecordset::iArrOpenTbType[]={
			dbOpenTable,dbOpenDynaset,dbOpenSnapshot,dbOpenForwardOnly,dbOpenDynamic,dbOpenTable,
			};
const char *GPCDAORecordset::cArrOpenTbTypeName[]={
			"OPENTABLE","OPENDYNASET","OPENSNAPSHOT","OPENFORWARDONLY","OPENDYNAMIC","OPENTABLE",
			};

const UINT	GPCDAORecordset::nArrFieldType=12;
const short GPCDAORecordset::siArrFieldType[]={
			dbBoolean,dbByte,dbInteger,dbLong,dbCurrency,
			dbSingle,dbDouble,dbDate,dbText,dbLongBinary,
			dbMemo,dbGUID,dbInteger,
			};
const char *GPCDAORecordset::cArrFieldTypeName[]={
			"BOOLEAN","BYTE","INTEGER","LONG","CURRENCY",
			"SINGLE","DOUBLE","DATE","TEXT","LONGBINARY",
			"MEMO","GUID","",
			};

const UINT GPCDAORecordset::nArrEditMode=6;
const short GPCDAORecordset::siArrEditMode[]={
			dbEditNone,dbEditInProgress,dbEditAdd,dbEditChanged,dbEditDeleted,
			dbEditNew,dbEditNone,
			};
const char *GPCDAORecordset::siArrEditModeName[]={
			"EditNone","EditInProgress","EditAdd","EditChanged","EditDeleted",
			"EditNew","EditNone",
			};


/////////////////////////////////////////////////////////////////////////////
// GPCDAORecordset

IMPLEMENT_DYNAMIC(GPCDAORecordset, CDaoRecordset)

GPCDAORecordset::GPCDAORecordset(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(GPCDAORecordset)
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;

	m_DosAnsiFlag=TRUE;
	m_nParams = 1;
	m_strCourseIDParam = "";
	UpdFieldsArr=TRUE;
}


CString GPCDAORecordset::GetDefaultDBName()
{
	return _T("");
}

CString GPCDAORecordset::GetDefaultSQL()
{
	return _T("");
}

/////////////////////////////////////////////////////////////////////////////
// GPCDAORecordset diagnostics

#ifdef _DEBUG
void GPCDAORecordset::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void GPCDAORecordset::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG


GPCDAORecordset::~GPCDAORecordset()
{
	if (IsOpen()>0) Close();
}

short GPCDAORecordset::TranslateFieldType(const char * iStr)
{
	int j;
	for(j=0;j<nArrFieldType && _stricmp(iStr,cArrFieldTypeName[j])==NULL;j++);

	return siArrFieldType[j];

}

const char * GPCDAORecordset::ReTranslateFieldType(short iType)
{
	int i;
	for(i=0;i<nArrFieldType && iType!=siArrFieldType[i];i++);
	return cArrFieldTypeName[i];
}

long GPCDAORecordset::TranslateFieldAttr(const char * iStr)
{
	long ret=0;
	UINT i;
	for(i=0;i<nArrFieldAttr;i++)
		if (strstr(iStr,cArrFieldAttrName[i])!=NULL) 
			ret|=siArrFieldAttr[i];

	return ret;
}

const CString GPCDAORecordset::ReTranslateFieldAttr(long iType)
{
	CString ret;
	UINT i;
	for(i=0;i<nArrFieldAttr;i++)
		if ((iType&siArrFieldAttr[i])==siArrFieldAttr[i])
		{
			if (ret.GetLength()>0) ret+="\x7";
			ret+=cArrFieldAttrName[i];
		}
	return ret;
}



void GPCDAORecordset::GetFIString(CDaoFieldInfo &finfo, char *oStrInfo)
{
	sprintf(oStrInfo,"%s\x7F%s\x7F%s\x7F%s\x7F%s\x7F%d\x7F%s\x7F%d\x7F%d\x7F%d\x7F%s\x7F%s\x7F%s\x7F%s",
		(LPCTSTR)finfo.m_strName,
		(LPCTSTR)finfo.m_strForeignName,
		(LPCTSTR)finfo.m_strSourceField,
		(LPCTSTR)finfo.m_strSourceTable,
		(LPCTSTR)ReTranslateFieldType(finfo.m_nType),
		finfo.m_lSize,
		(LPCTSTR)ReTranslateFieldAttr(finfo.m_lAttributes),
		finfo.m_nOrdinalPosition,
		finfo.m_bRequired,
		finfo.m_bAllowZeroLength,
		(LPCTSTR)GPCDAODatabase::ReTranslateCollation(finfo.m_lCollatingOrder),
		(LPCTSTR)finfo.m_strValidationRule,
		(LPCTSTR)finfo.m_strValidationText,
		(LPCTSTR)finfo.m_strDefaultValue
		);
}

void GPCDAORecordset::GetIIString(CDaoIndexInfo &iinfo, char *oStrInfo)
{
	char *outpos=oStrInfo;
	outpos+=sprintf(outpos,"%s\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d",
		(LPCTSTR)iinfo.m_strName,
		iinfo.m_bPrimary,
		iinfo.m_bUnique,
		iinfo.m_bClustered,
		iinfo.m_bIgnoreNulls,
		iinfo.m_bRequired,
		iinfo.m_bForeign,
		iinfo.m_lDistinctCount,
		iinfo.m_nFields
		);

	int i;
	for(i=0;i<iinfo.m_nFields;i++)
		outpos+=sprintf(outpos,"\x7F%s\x07%d",(LPCTSTR)iinfo.m_pFieldInfos[i].m_strName,iinfo.m_pFieldInfos[i].m_bDescending);
}


void GPCDAORecordset::DoFieldExchange(CDaoFieldExchange* pFX)
{
	try
	{
		//{{AFX_FIELD_MAP(GPCDAORecordset)
		pFX->SetFieldType(CDaoFieldExchange::param);
		DFX_Text(pFX, "CourseIDParam", m_strCourseIDParam);
		//}}AFX_FIELD_MAP

		if (a_CStringFieldOut!=NULL && m_nFields>0)
		{
			UpdateFieldsArr();
			int i;
			pFX->SetFieldType(CDaoFieldExchange::outputColumn);
			for(i=0;i<m_nFields;i++)
			{
				DFX_Text(pFX,a_CDAOFieldInfo[i].m_strName,a_CStringFieldOut[i],9990);
			}
		}
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPCDAORecordset", "DoFieldExchange","");
	}

}

void GPCDAORecordset::UpdateFieldsArr()
{
	if (UpdFieldsArr==TRUE && IsOpen())
	{
		int i=0;
		BOOL Brk=FALSE;
		try
		{
			if ((i=GetFieldCount())>0)
			{
				m_nFields=i;
				for(i=0;i<m_nFields;i++)
				{
					try
					{
						GetFieldInfo(i,a_CDAOFieldInfo[i]);
					}
					catch(...)
					{
						GPC.m_ErrReport.GPWriteErrorLog("GPCDAORecordset", "UpdateFieldsArr 232","");
						if (i>0) m_nFields=i; 
						Brk=TRUE;
					}

					if (Brk==TRUE) break;

				}
				if (i>0) UpdFieldsArr=FALSE;
			}
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("GPCDAORecordset", "UpdateFieldsArr 245","");
		}
	}
}

int GPCDAORecordset::GetFieldIndexByName(const char *name)
{
	int nField;
	for(nField=0;nField<m_nFields && _stricmp(name,a_CDAOFieldInfo[nField].m_strName)!=0;nField++);
	
	return nField>=m_nFields?-1:nField;
}

BOOL GPCDAORecordset::GPIsOpen()
{
	return IsOpen();
}

void GPCDAORecordset::Close() 
{
	CDaoRecordset::Close();
}


int GPCDAORecordset::TranslateRSType(const char *iStr)
{
	int j;
	for(j=0;j<nArrOpenTbType && _stricmp(iStr,cArrOpenTbTypeName[j])!=0;j++);

	return iArrOpenTbType[j];
}

const char * GPCDAORecordset::ReTranslateRSType(int iType)
{
	int i;
	for(i=0;i<nArrOpenTbType && iType!=iArrOpenTbType[i];i++);
	return cArrOpenTbTypeName[i];
}

int GPCDAORecordset::TranslateEditMode(const char *iStr)
{
	int j;
	for(j=0;j<nArrEditMode && _stricmp(iStr,siArrEditModeName[j])!=0;j++);

	return siArrEditMode[j];
}

const char * GPCDAORecordset::ReTranslateEditMode(int iType)
{
	int i;
	for(i=0;i<nArrEditMode && iType!=siArrEditMode[i];i++);
	return siArrEditModeName[i];
}


BOOL GPCDAORecordset::GPOpen(const char *iStr)
{
	char *str=new char [(int)strlen(iStr)+20];
	BOOL ret=FALSE;
	try
	{try
	{
		char *posOpt=strchr(str,';');
		if (posOpt!=NULL) *(posOpt++)=0;
		else posOpt="";
		char *posSQL=strchr(posOpt,';');
		if (posSQL!=NULL) *(posSQL++)=0;
		
		m_DosAnsiFlag=strstr(iStr,"NOANSIDOS")==NULL;
		Open(TranslateRSType(iStr),posSQL,GPCDAODatabase::TranslateExecuteOptions(posOpt));
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

int GPCDAORecordset::DoMethod(const char *iMethod, char *oStr)
{
	char *met=new char [(int)strlen(iMethod)+50];
	strcpy(met,iMethod);
	const char *pos=strchr(iMethod,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc;
	char *fn[83]={
		"CanAppend","CanBookmark","CanRestart","CanScroll","CanTransact",
		"CanUpdate","CanAll","GetCurrentIndex","GetDateCreated","GetDateLastUpdated",
		"GetEditMode","GetLastModifiedBookmark","GetName","GetParamValue","GetRecordCount",
		"GetSQL","GetType","GetValidationRule","GetValidationText","IsBOF",
		"IsDeleted","IsEOF","IsOpen","IsFieldDirty","IsFieldNull",
		"IsFieldNullable","SetCurrentIndex","SetParamValue","SetParamValueNull","AddNew",
		"CancelUpdate","Delete","Edit","Update","Find",
		"FindFirst","FindLast","FindNext","FindPrev","GetAbsolutePosition",
		"GetBookmark","GetPercentPosition","Move","MoveFirst","MoveLast",
		"MoveNext","MovePrev","Seek","SetAbsolutePosition","SetBookmark",
		"SetPercentPosition","FillCache","GetCacheSize","GetCacheStart","GetFieldCount",
		"GetFieldInfo","GetFieldInfoById","GetIFV","GetNFV","GetIndexCount",
		"GetIndexInfo","GetLockingMode","Requery","SetCacheSize","SetCacheStart",
		"SetFieldDirty","SetFieldNull","SetFV","SetFVNull","SetFVById",
		"SetFVNullById","SetLockingMode","GetFieldsInfo","ReadRow","ReadRowMoveNext",
		"ReadRows","WriteRow","AppendRow","WriteRows","AppendRows",
		"DeleteRows","SetCodeConvert",
		};


	if (*met>='0' && *met<='9') nfunc=atoi(met);
	else
		for(nfunc=0;nfunc<83 && _stricmp(met,fn[nfunc])!=0;nfunc++); 

	int retint=-123456; 
	int atoipos=atoi(pos);

	try
	{
		try
		{
			switch(nfunc)
			{
			case 82: /*SetCodeConvert*/ m_DosAnsiFlag=atoi(pos);	break;		
			case 0:	/*CanAppend*/	if (IsOpen()) retint=CanAppend(); break;
			case 1:	/*CanBookmark*/	if (IsOpen()) retint=CanBookmark(); break;
			case 2:	/*CanRestart*/	if (IsOpen()) retint=CanRestart(); break;
			case 3:	/*CanScroll*/	if (IsOpen()) retint=CanScroll(); break;
			case 4:	/*CanTransact*/	if (IsOpen()) retint=CanTransact(); break;
			case 5:	/*CanUpdate*/	if (IsOpen()) retint=CanUpdate(); break;
			case 6:	/*CanAll*/
				if (IsOpen() && oStr!=NULL) 
					sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d",
							CanAppend(),
							CanBookmark(),
							CanRestart(),
							CanScroll(),
							CanTransact(),
							CanUpdate()
							);
				break;
			case 7:	/*GetCurrentIndex*/	if (IsOpen() && oStr!=NULL) strcpy(oStr,GetCurrentIndex());break;
			case 8:	/*GetDateCreated*/
			case 9:	/*GetDateLastUpdated*/
				if (IsOpen() && oStr!=NULL)
				{
					COleDateTime dt;
					if (nfunc==8)	dt=GetDateCreated();
					else			dt=GetDateLastUpdated();
					sprintf(oStr,"%d\x7%d\x7%d\x7%d\x7%d\x7%d\x7F",
							dt.GetYear(),
							dt.GetMonth(),
							dt.GetDay(),
							dt.GetHour(),
							dt.GetMinute(),
							dt.GetSecond()
							);
				}
				break;
			case 10:/*GetEditMode*/		if (IsOpen() && oStr!=NULL) strcpy(oStr,ReTranslateEditMode(GetEditMode()));	break;
			case 11:/*GetLastModifiedBookmark*/
			case 13:/*GetParamValue*/	
			case 40:/*GetBookmark*/	
				if (IsOpen() && oStr!=NULL)
				{
					COleVariant lbm;
					switch(nfunc)
					{
					case 11:/*GetLastModifiedBookmark*/		lbm=GetLastModifiedBookmark();	break;
					case 13:/*GetParamValue*/				lbm=GetParamValue(atoipos);		break;
					case 40:/*GetBookmark*/					lbm=GetBookmark();				break;
					}
					CString str;
					ConvertToString(lbm,str,"\x7F");
					strcpy(oStr,str);
				}
				break;
			case 12:/*GetName*/		if (oStr!=NULL)						strcpy(oStr,GetName());break;
			case 14:/*GetRecordCount*/	if (IsOpen() && oStr!=NULL)		retint=GetRecordCount(); break;
			case 15:/*GetSQL*/		if (oStr!=NULL)						strcpy(oStr,GetSQL());break;
			case 16:/*GetType*/		if (IsOpen() && oStr!=NULL)			strcpy(oStr,ReTranslateRSType(GetType()));break;
			case 17:/*GetValidationRule*/	if (oStr!=NULL)				strcpy(oStr,GetValidationRule());break;
			case 18:/*GetValidationText*/	if (oStr!=NULL)				strcpy(oStr,GetValidationText());break;
			case 19:/*IsBOF*/		if (IsOpen())	retint=IsBOF();		break;
			case 20:/*IsDeleted*/	if (IsOpen())	retint=IsDeleted(); break;
			case 21:/*IsEOF*/		if (IsOpen())	retint=IsEOF();		break;
			case 22:/*IsOpen*/		retint=IsOpen(); break;
			case 23:/*IsFieldDirty*/
			case 24:/*IsFieldNull*/	
			case 25:/*IsFieldNullable*/	
				if (oStr!=NULL && IsOpen() && atoipos>=0 && atoipos<m_nFields) 
					switch(nfunc)
					{
					case 23:/*IsFieldDirty*/	retint=IsFieldDirty(&a_CStringFieldOut[atoipos]);		break;
					case 24:/*IsFieldNull*/		retint=IsFieldNull(&a_CStringFieldOut[atoipos]);		break;
					case 25:/*IsFieldNullable*/	retint=IsFieldNullable(&a_CStringFieldOut[atoipos]);	break;
					}
				break;
			case 26:/*SetCurrentIndex*/	if (IsOpen())	SetCurrentIndex(pos); break;
			case 27:/*SetParamValue*/
				{
					const char *pospar=strchr(pos,',');
					if (pospar++==NULL) pospar="";
					SetParamValue(atoipos,COleVariant(pospar));
				}
				break;
			case 28:/*SetParamValueNull*/	if (IsOpen()) 	SetParamValueNull(atoipos);		break;
			case 29:/*AddNew*/	if (IsOpen() && CanUpdate()) {retint=1;AddNew();}			break;
			case 30:/*CancelUpdate*/
				if (IsOpen() && CanUpdate()) 
				{
					retint=1;
					CancelUpdate();
				}
				UpdFieldsArr=TRUE;
				break;
			case 31:/*Delete*/	
				if (IsOpen() && CanUpdate()) 
				{
					retint=1;
					Delete();
					MoveNext();
				}
			case 32:/*Edit*/			if (IsOpen() && CanUpdate()) {retint=1;Edit();}		break;
			case 33:/*Update*/			if (IsOpen() && CanUpdate()) {retint=1;Update();}	break;
			case 34:/*Find*/
				if (IsOpen())
				{
					char *pos333=new char [(int)strlen(pos)+2];
					strcpy(pos333,pos);
					char *posFind=strchr(pos333,',');
					if (posFind!=NULL) 
					{
						*(posFind++)=0;
						_strupr(pos333);
						long type=AFX_DAO_NEXT;
						if (strcmp(pos333,"PREV")==0)	type=AFX_DAO_PREV;
							else
							if (strcmp(pos333,"FIRST")==0)	type=AFX_DAO_FIRST;
								else
								if (strcmp(pos333,"LAST")==0)	type=AFX_DAO_LAST;
									//else	/*NEXT*/			type=AFX_DAO_NEXT;
						retint=Find(type,posFind);
					}
					delete[] pos333;
				}
				break;
			case 35:/*FindFirst*/	if (IsOpen())	retint=FindFirst(pos);	break;	
			case 36:/*FindLast*/	if (IsOpen())	retint=FindLast(pos);	break;	
			case 37:/*FindNext*/	if (IsOpen())	retint=FindNext(pos);	break;	
			case 38:/*FindPrev*/	if (IsOpen())	retint=FindPrev(pos);	break;	
			case 39:/*GetAbsolutePosition*/
				if (oStr!=NULL && IsOpen())	
					retint=GetAbsolutePosition();
				break;
			case 41:/*GetPercentPosition*/
				if (oStr!=NULL && IsOpen())
					sprintf(oStr,"%f",GetPercentPosition());
				break;
			case 42:/*Move*/		if (IsOpen()) Move(atoipos); retint=1;break;
			case 43:/*MoveFirst*/	if (IsOpen()) MoveFirst(); retint=1;break;
			case 44:/*MoveLast*/	if (IsOpen()) MoveLast(); retint=1;break;
			case 45:/*MoveNext*/	if (IsOpen()) MoveNext(); retint=1;break;
			case 46:/*MovePrev*/	if (IsOpen()) MovePrev(); retint=1;break;
			case 47:/*Seek*/
				if (IsOpen())
				{
					char *postmpcc=new char [(int)strlen(pos)+10];
					strcpy(postmpcc,pos);
					char *pos2=strchr(postmpcc,',');
					if (pos2!=NULL)
					{
						*(pos2++)=0;
						WORD nKeys=0;
						COleVariant KeyArr[32];
						while(pos2!=NULL && nKeys<31)
						{
							char *pos3=strchr(pos2,GPC.DelimiterIn1);
							if (pos3!=NULL) *(pos3++)=0;
							KeyArr[nKeys++]=pos2;
							pos2=pos3;
						}
						retint=Seek(postmpcc,KeyArr,nKeys);
					}
					delete[] postmpcc;
				}
				break;
			case 48:/*SetAbsolutePosition*/		if (IsOpen()) SetAbsolutePosition(atoipos); break;
			case 49:/*SetBookmark*/			
				if (IsOpen()) 
				{
					retint=1;
					long ap=atoi(pos);
					if (ap>=0 && ap<256)
					{
						SetBookmark(a_COleVariantBM[ap]);
						retint=a_COleVariantBM[ap].lVal;
					}
				}
				break;
			case 50:/*SetPercentPosition*/	if (IsOpen()) SetPercentPosition((float)atof(pos)); break;
			case 51:/*FillCache*/
				if (IsOpen())
				{
					long cs=0,bm=-1,*pcs=NULL;
					m_LastScanf=sscanf(pos,"%ld,%ld",&cs,&bm);
					COleVariant *pbm=NULL;
					if (bm>=0 && bm<256) pbm=&a_COleVariantBM[bm];
					if (cs>0 && cs<50000) pcs=&cs;
					FillCache(pcs,pbm);
				}
				break;
			case 52:/*GetCacheSize*/	if (IsOpen()) retint=GetCacheSize(); break;
			case 53:/*GetCacheStart*/	if (oStr!=NULL && IsOpen())	retint=GetCacheStart().lVal;	break;
			case 54:/*GetFieldCount*/	if (IsOpen()) retint=GetFieldCount(); break;
			case 55:/*GetFieldInfo*/
			case 56:/*GetFieldInfoById*/
				if (oStr!=NULL)
				{
					CDaoFieldInfo finfo;
					if (nfunc==55)	GetFieldInfo(atoipos,finfo,AFX_DAO_ALL_INFO);
					else			GetFieldInfo(pos,finfo,AFX_DAO_ALL_INFO);
					GetFIString(finfo,oStr);
				}
				break;
			case 57: /*GetIFV   == GetFieldValue by index*/
			case 58: /*GetNFV   == GetFieldValue by name*/
				if (oStr!=NULL && IsOpen()) 
				{
					CString tmp="";
					if (nfunc==57)
					{
						int ap=atoi(pos);
						if (ap>=0 && ap<m_nFields)
							tmp=a_CStringFieldOut[ap];
					}
					else
					{
						if (*pos!=0)
						{
							int nf=GetFieldIndexByName(pos);
							if (nf>=0) tmp=a_CStringFieldOut[nf];
						}
					}
					tmp.Replace(10,3);
					tmp.Replace(13,3);
					tmp.Replace(7,3);
					strcpy(oStr,tmp);
				}
				break;

			case 59:/*GetIndexCount*/	retint=GetIndexCount(); break;
			case 60:/*GetIndexInfo*/
			case 61:/*GetIndexInfoById*/	break;
				if (oStr!=NULL)
				{
					CDaoIndexInfo iinfo;
					if (nfunc==60)	GetIndexInfo(atoipos,iinfo,AFX_DAO_ALL_INFO);
					else			GetIndexInfo(pos,iinfo,AFX_DAO_ALL_INFO);
					GetIIString(iinfo,oStr);
				}
				break;
			case 62:/*GetLockingMode*/	if (IsOpen() && CanUpdate()) retint=GetLockingMode();	break;
			case 63:/*Requery*/	
				Requery(); 
				retint=1;
				UpdFieldsArr=TRUE;
				break;
			case 64:/*SetCacheSize*/	SetCacheSize(atoipos); break;
			case 65:/*SetCacheStart*/	
				if (IsOpen()) 
				{
					retint=1;
					long ap=atoi(pos);
					if (ap>=0 && ap<256)
						SetCacheStart(a_COleVariantBM[ap]);
				}
				break;
			case 66:/*SetFieldDirty*/
			case 67:/*SetFieldNull*/
				if (IsOpen() && CanUpdate()) 
				{
					int nfi=0;
					int state=0;
					m_LastScanf=sscanf(pos,"%d,%d",&nfi,&state);
					if (nfi>=0 && nfi<m_nFields) 
					{
						if (nfunc==66)	SetFieldDirty(&a_CStringFieldOut[nfi],state);
						else			SetFieldNull(&a_CStringFieldOut[nfi],state);
					}
				}
				break;
			case 68:/*SetFV*/
				if (IsOpen() && CanUpdate()) 
				{
					char *postmpcc=new char [(int)strlen(pos)+10];
					strcpy(postmpcc,pos);
					char *postext=strchr(postmpcc,',');
					if (postext==NULL) postext="";
					else *(postext++)=0;
					SetFieldValue(postmpcc,postext);
					delete[] postmpcc;
				}
				break;
			case 69:/*SetFVNull*/	if (IsOpen() && CanUpdate()) SetFieldValueNull(pos); break;
			case 70:/*SetFVById*/
				if (IsOpen() && CanUpdate()) 
				{
					const char *postext=strchr(pos,',');
					if (postext++==NULL) postext="";
					SetFieldValue(atoipos,postext);
				}
				break;
			case 71:/*SetFVNullById*/	if (IsOpen() && CanUpdate()) SetFieldValueNull(atoipos); break;
			case 72:/*SetLockingMode*/	SetLockingMode(atoipos&0x1);	break;
			case 73:/*GetFieldsInfo*/
				if (IsOpen() && oStr!=NULL) 
				{
					int nIndex;
					char *pos333=oStr;
					CDaoFieldInfo finfo;

					for(nIndex=0;nIndex<m_nFields;nIndex++)
					{
						if (nIndex>0)	strcat(pos333++,"\x7F");
						GetFieldInfo(nIndex,finfo,AFX_DAO_ALL_INFO);
						GetFIString(finfo,oStr);
					}
				}
				break;
			case 74: /*ReadRow*/
				if (IsOpen() && oStr!=NULL) 
				{
					int nIndex;
					char *pos1=oStr;
					CString tmp;
					for(nIndex=0;nIndex<m_nFields;nIndex++)
					{
						tmp=a_CStringFieldOut[nIndex];
						tmp.Replace(10,3);
						tmp.Replace(13,3);
						tmp.Replace(7,3);
						strcat(pos1,tmp);
						pos1+=(int)strlen(pos1);
						if (nIndex<m_nFields-1)	strcat(pos1++,"\x7F");
					}
				}
				break;
			case 75: /*ReadRowMoveNext*/
				if (IsOpen() && oStr!=NULL) 
				{
					int nIndex;
					char *pos1=oStr;
					CString tmp;
					for(nIndex=0;nIndex<m_nFields;nIndex++)
					{
						tmp=a_CStringFieldOut[nIndex];
						tmp.Replace(10,3);
						tmp.Replace(13,3);
						tmp.Replace(7,3);
						strcat(pos1,tmp);
						pos1+=(int)strlen(pos1);
						if (nIndex<m_nFields-1)	strcat(pos1++,"\x7F");
					}
					DoMethod("MoveNext",NULL);
				}
				break;
			case 76: /*ReadRows*/
				if (IsOpen() && oStr!=NULL) 
				{
					int nIndex;
					char *pos1=oStr;
					int i,nRow=atoi(pos);
					*pos1=0;
					CString tmp;
					for(i=0;i<nRow;i++)
					{
						for(nIndex=0;nIndex<m_nFields && !IsEOF();nIndex++)
						{
							tmp=a_CStringFieldOut[nIndex];
							tmp.Replace(10,3);
							tmp.Replace(13,3);
							tmp.Replace(7,3);
							strcat(pos1,tmp);
							pos1+=(int)strlen(pos1);
							if (nIndex<m_nFields-1)	strcat(pos1++,"\x07");
						}
						if (i<nRow-1) strcat(pos1++,"\x7F");
						try			{MoveNext();}
						catch(...)
						{
							GPC.m_ErrReport.GPWriteErrorLog("GPCDAORecordset", "DoMethod 742",iMethod);
							if (IsEOF())break;
						}
					}		
				}
				break;

			case 77: /*WriteRow*/
			case 78: /*AppendRow*/
				if (IsOpen() && CanUpdate()) 
				{
					char *pos333=new char [(int)strlen(pos)+2];
					strcpy(pos333,pos);
					if (nfunc==77) Edit();
					else AddNew();
					char *postext=pos333,*postmp;
					int nIndex=0;
					while(postext!=NULL && nIndex<m_nFields)
					{
						postmp=strchr(postext,2);
						if (postmp==NULL) postmp=strchr(postext,GPC.DelimiterIn1);
						if (postmp!=NULL) *(postmp++)=0;
						a_CStringFieldOut[nIndex]=postext;
						postext=postmp;
						nIndex++;
					}
					delete[] pos333;
					Update();
					if (nfunc==77) MoveNext();

				}
				else if (oStr!=NULL) sprintf(oStr,ErrObjSub,met);
				break;
			case 79: /*WriteRows*/
			case 80: /*AppendRows*/
				if (IsOpen() && CanUpdate()) 
				{
					char *pos333=new char [(int)strlen(pos)+2];
					strcpy(pos333,pos);
					char *posrec=pos333,*posrectmp;
					while(posrec!=NULL)
					{
						posrectmp=strchr(posrec,1);
						if (posrectmp==NULL) posrectmp=strchr(posrec,GPC.DelimiterIn1);
						if (posrectmp!=NULL) *(posrectmp++)=0;

						if (nfunc==79) Edit();
						else AddNew();

						char *postext=posrec,*postmp;
						int nIndex=0;
						while(postext!=NULL && nIndex<m_nFields)
						{
							postmp=strchr(postext,2);
							if (postmp==NULL) postmp=strchr(postext,GPC.DelimiterIn1);
							if (postmp==NULL) postmp=strchr(postext,GPC.DelimiterIn2);
							if (postmp!=NULL) *(postmp++)=0;
							a_CStringFieldOut[nIndex]=postext;
							postext=postmp;
							nIndex++;
						}
						Update();
						if (nfunc==79) MoveNext();
						posrec=posrectmp;
					}
					delete[] pos333;
				}
				else if (oStr!=NULL) sprintf(oStr,ErrObjSub,met);
				break;
			case 81: /*DeleteRows*/
				if (IsOpen() && CanUpdate()) 
				{
					int nRows=atoipos;
					while((nRows--)>0)
					{
						retint=1;
						Delete();
						MoveNext();
					}
				}
				break;
			default:
				GPC.m_ErrReport.GPWriteWarnLog2("GPCDAORecordset", "Unknown Method",iMethod);
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
		GPC.m_ErrReport.GPWriteErrorLog("GPCDAORecordset", "DoMethod",iMethod);
		delete[] str;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
	delete[] met;
	return nfunc;
}

