// GPCRecordset.cpp : implementation file
//

#include "stdafx.h"
#include "GP_term.h"
#include "GPCRecordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPCRecordset

IMPLEMENT_DYNAMIC(GPCRecordset, CRecordset)

GPCRecordset::GPCRecordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(GPCRecordset)
	//}}AFX_FIELD_INIT
	m_nParams = 1;
	m_strCourseIDParam = "";

	m_DosAnsiFlag=TRUE;
	UpdFieldsArr=TRUE;
	int i;
	for(i=0;i<256;i++)
		a_CStringFieldOut[i].GetBufferSetLength (10000);

}

GPCRecordset::~GPCRecordset()
{
	if (IsOpen()>0) Close();
	int i;
	for(i=0;i<256;i++)
		a_CStringFieldOut[i].ReleaseBuffer(-1);
}

/////////////////////////////////////////////////////////////////////////////
// GPCDAORecordset diagnostics

#ifdef _DEBUG
void GPCRecordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void GPCRecordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

int GPCRecordset::DoMethod(const char *iMethod, char *oStr)
{
	char *met=new char [(int)strlen(iMethod)+50];
	strcpy(met,iMethod);
	const char *pos=strchr(iMethod,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc=0;
	int retint=-123456; 

	char *fn[67]={
		"Get_nFields","Get_nParams","Get_strFilter","Get_strSort","Set_strFilter",
		"Set_strSort","Open","Close","CanAppend","CanBookmark",
		"CanRestart","CanScroll","CanTransact","CanUpdate","GetODBCFieldCount",
		"GetRecordCount","GetStatus","GetTableName","GetSQL","IsOpen",
		"IsBOF","IsEOF","IsDeleted","AddNew","CancelUpdate",
		"Delete","Edit","Update","GetBookmark","Move",
		"MoveFirst","MoveLast","MoveNext","MovePrev","SetAbsolutePosition",
		"SetBookmark","Cancel","FlushResultSet","GetIFV","GetIFieldInfo",
		"GetRowsetSize","GetRowsFetched","GetRowStatus","IsFieldDirty","IsFieldNull",
		"IsFieldNullable","RefreshRowset","Requery","SetFieldDirty","SetFieldNull",
		"SetLockingMode","SetParamNull","SetRowsetCursorPosition","GetNFV","GetNFieldInfo",
		"GetFieldsInfo","ReadRow","ReadRowMoveNext","ReadRows","SetIFV",
		"SetNFV","WriteRow","WriteRows","AppendRow","AppendRows",
		"DeleteRows","SetCodeConvert",
	};

	if (*met>='0' && *met<='9') nfunc=atoi(met);
	else
		for(nfunc=0;nfunc<67 && _stricmp(met,fn[nfunc])!=0;nfunc++); 

try
{
	switch(nfunc)
	{
	case 66: /*SetCodeConvert*/ m_DosAnsiFlag=atoi(pos);	break;		
	case 0: /*Get_nFields*/		retint=m_nFields;	break;
	case 1: /*Get_nParams*/		retint=m_nParams;	break;
	case 2: /*Get_strFilter*/	if (oStr!=NULL) strcpy(oStr,m_strFilter);		break;
	case 3: /*Get_strSort*/		if (oStr!=NULL) strcpy(oStr,m_strSort);			break;
	case 4: /*Set_strFilter*/	m_strFilter=pos;		break;
	case 5: /*Set_strSort*/		m_strSort=pos;			break;
	case 6: /*Open*/
		{
			UINT rstype[4]={CRecordset::dynaset,CRecordset::snapshot,CRecordset::dynamic,CRecordset::forwardOnly,};
			char * crstype[4]={"DYNASET","SNAPSHOT","DYNAMIC","FORWARDONLY",};
			DWORD rsOptions[11]={CRecordset::none,CRecordset::appendOnly,CRecordset::readOnly,CRecordset::optimizeBulkAdd,CRecordset::useMultiRowFetch,CRecordset::skipDeletedRecords,CRecordset::useBookmarks,CRecordset::noDirtyFieldCheck,CRecordset::executeDirect,CRecordset::useExtendedFetch,CRecordset::userAllocMultiRowBuffers,};
			char * crsOptions[11]={"NONE","APPENDONLY","READONLY","OPTIMIZEBULK","MULTIROWFETCH","SKIPDELETED","USEBOOKMARKS","NODIRTYFIELD","EXECUTEDIRECT","EXTENDEDFETCH","ALLOCMULTIROW",};
//			char * [4]={"dynaset","snapshot","dynamic","forwardOnly",};
//			char * [11]={"none","appendOnly","readOnly","optimizeBulk","MultiRowFetch","skipDeleted","useBookmarks","noDirtyField","executeDirect","ExtendedFetch","AllocMultiRow","};
			int i;
			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
			char *posSQL=strchr(pos333,';');
			if (posSQL!=NULL)  *(posSQL++)=0;
			_strupr(pos333);
			UINT rst=AFX_DB_USE_DEFAULT_TYPE;
			for(i=0;i<4;i++)
				if (strstr(pos333,crstype[i])!=NULL)
					{	rst=rstype[i];	break;	}

			DWORD opt=0;
			for(i=0;i<11;i++)
				if (strstr(pos333,crsOptions[i])!=NULL)	opt|=rsOptions[i];	

			m_DosAnsiFlag=strstr(pos333,"NOANSIDOS")==NULL;

			m_nFields=255;
			{
				unsigned int ii;
				for(ii=0;ii<m_nFields;ii++)
					a_CStringFieldOut[ii]="";
			}
			UpdFieldsArr=TRUE;
			retint=Open(rst,posSQL,opt);
			m_nFields=GetODBCFieldCount( );
			delete[] pos333;
		}
		break;
	case 7: /*Close*/  
		if (IsOpen())		Close();
		UpdFieldsArr=TRUE;	
		break;
	case 8: /*CanAppend*/	if (IsOpen()) retint=CanAppend();		break;
	case 9: /*CanBookmark*/	if (IsOpen()) retint=CanBookmark();	break;
	case 10: /*CanRestart*/	if (IsOpen()) retint=CanRestart();	break;
	case 11: /*CanScroll*/	if (IsOpen()) retint=CanScroll();		break;
	case 12: /*CanTransact*/if (IsOpen()) retint=CanTransact();	break;
	case 13: /*CanUpdate*/	if (IsOpen()) retint=CanUpdate();		break;
	case 14: /*GetODBCFieldCount*/	if (IsOpen()) retint=GetODBCFieldCount();		break;
	case 15: /*GetRecordCount*/	if (oStr!=NULL && IsOpen()) sprintf(oStr,"%ld",GetRecordCount());		break;
	case 16: /*GetStatus*/
		if (oStr!=NULL) 
		{
			CRecordsetStatus rStatus={0};
			GetStatus(rStatus);
			sprintf(oStr,"%ld\x7F%d",rStatus.m_lCurrentRecord,rStatus.m_bRecordCountFinal);
		}
		break;
	case 17: /*GetTableName*/	if (oStr!=NULL) strcpy(oStr,GetTableName());	break;
	case 18: /*GetSQL*/			if (oStr!=NULL) strcpy(oStr,GetSQL());			break;
	case 19: /*IsOpen*/			retint=IsOpen();	break;
	case 20: /*IsBOF*/			if (IsOpen()) retint=IsBOF();		break;
	case 21: /*IsEOF*/			if (IsOpen()) retint=IsEOF();		break;
	case 22: /*IsDeleted*/		if (IsOpen()) retint=IsDeleted();	break;
	case 23: /*AddNew*/
		if (IsOpen() && CanUpdate()) {retint=1;AddNew();}
		break;
	case 24: /*CancelUpdate*/	if (IsOpen()) {retint=1;CancelUpdate();}	break;
	case 25: /*Delete*/
		if (IsOpen() && CanUpdate()) 
		{
			retint=1;
			Delete();
			MoveNext();
		}
		break;
	case 26: /*Edit*/
		if (IsOpen() && CanUpdate())  {retint=1;Edit();}
		break;
	case 27: /*Update*/
		if (IsOpen() && CanUpdate()) retint=Update();
		break;
	case 28: /*GetBookmark*/
		if (IsOpen()) 
		{
			int nBM=atoi(pos);
			if (nBM>=0 && nBM<10000)
			a_CDBVariantBM[nBM].Clear();
			GetBookmark(a_CDBVariantBM[nBM]);
			retint=nBM;
		}
		break;
	case 29: /*Move*/
		if (IsOpen()) 
		{
			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
			WORD wFetchType=SQL_FETCH_RELATIVE;
			long nRows=atoi(pos333);
			_strupr(pos333);
			WORD wFt[7]={SQL_FETCH_RELATIVE,SQL_FETCH_NEXT,SQL_FETCH_PRIOR,SQL_FETCH_FIRST,SQL_FETCH_LAST,SQL_FETCH_ABSOLUTE,SQL_FETCH_BOOKMARK,};
			char *cFt[7]={"RELATIVE","NEXT","PRIOR","FIRST","LAST","ABSOLUTE","BOOKMARK",};
			int i;
			for(i=0;i<7;i++)
				if (strstr(pos333,cFt[i])!=NULL)
					{wFetchType=wFt[i];break;}

			if (wFetchType==SQL_FETCH_BOOKMARK)
				nRows=a_CDBVariantBM[nRows].m_lVal;

			Move(nRows,wFetchType);
			retint=nRows;
			delete[] pos333;
		}
		break;
	case 30: /*MoveFirst*/
		if (IsOpen()) {retint=1;MoveFirst();}
		break;
	case 31: /*MoveLast*/
		if (IsOpen()) {retint=1;MoveLast();}
		break;
	case 32: /*MoveNext*/
		if (IsOpen()) {retint=1;MoveNext();}
		break;
	case 33: /*MovePrev*/
		if (IsOpen()) {retint=1;MovePrev();}
		break;
	case 34: /*SetAbsolutePosition*/
		if (IsOpen()) 
		{
			retint=0;
			long ap=atoi(pos);
			if (ap>0)
				{SetAbsolutePosition(ap);retint=ap;}
		}
		break;
	case 35: /*SetBookmark*/
		if (IsOpen()) 
		{
			retint=1;
			long ap=atoi(pos);
			if (ap>=0 && ap<256)
				{SetBookmark(a_CDBVariantBM[ap]);retint=a_CDBVariantBM[ap].m_lVal;}
		}
		break;
	case 36: /*Cancel*/		
		if (IsOpen())  {retint=1;Cancel();}	
		UpdFieldsArr=TRUE;
		break;
	case 37: /*FlushResultSet*/
		if (IsOpen()) retint=FlushResultSet();
		break;
	case 38: /*GetIFV   == GetFieldValue by index*/
	case 53: /*GetNFV   == GetFieldValue by name*/
		if (oStr!=NULL && IsOpen()) 
		{
			CString tmp="";
			if (nfunc==38)
			{
				unsigned int ap=atoi(pos);
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
	case 39: /*GetIFieldInfo == GetODBCFieldInfo by index*/
	case 54: /*GetNFieldInfo == GetODBCFieldInfo by name*/
		if (oStr!=NULL && IsOpen()) 
		{
			CODBCFieldInfo inf;
			inf.m_nNullability=0;
			inf.m_nPrecision=0;
			inf.m_nScale=0;
			inf.m_nSQLType=0;
			inf.m_strName="";

			if (nfunc==38)
			{
				short ap=atoi(pos);
				if (ap>=0)	GetODBCFieldInfo(ap,inf);
			}
			else
				if (*pos!=0) GetODBCFieldInfo(pos,inf);
			GetFIString(inf,oStr);
		}
		break;
	case 40: /*GetRowsetSize*/	if (IsOpen()) retint=GetRowsetSize();		break;
	case 41: /*GetRowsFetched*/	if (IsOpen()) retint=GetRowsFetched();	break;
	case 42: /*GetRowStatus*/
		if (oStr!=NULL && IsOpen()) 
		{
			WORD wRow=atoi(pos);
			char *cret[8]={"SUCCESS","UPDATED","DELETED","ADDED","ERROR","NOROW","SUCCESS_WITH_INFO","UNKNOWN",};
			WORD res=7;
			if (wRow>0 && wRow<m_nFields)
			{
				res=GetRowStatus(wRow);
				if (res<0 || res>7) res=7;
			}
			strcpy(oStr,cret[res]);
		}
		break;
	case 43: /*IsFieldDirty*/
		if (oStr!=NULL && IsOpen()) 
		{
			unsigned int nfi=atoi(pos);
			if (nfi>=0 && nfi<m_nFields)
				retint=IsFieldDirty(&a_CStringFieldOut[nfi]);
		}
		break;
	case 44: /*IsFieldNull*/
		if (oStr!=NULL && IsOpen()) 
		{
			unsigned int nfi=atoi(pos);
			if (nfi>=0 && nfi<m_nFields)
				retint=IsFieldNull(&a_CStringFieldOut[nfi]);
		}
		break;
	case 45: /*IsFieldNullable*/
		if (oStr!=NULL && IsOpen()) 
		{
			unsigned int nfi=atoi(pos);
			if (nfi>=0 && nfi<m_nFields)
				retint=IsFieldNullable(&a_CStringFieldOut[nfi]);
		}
		break;
	case 52: /*SetRowsetCursorPosition*/
	case 46: /*RefreshRowset*/
		if (IsOpen()) 
		{
			WORD wRow=atoi(pos);
			if (wRow>0)
			{
				WORD wLockType=SQL_LOCK_NO_CHANGE;
				if (strstr(pos,"UNLOCK")!=NULL) wLockType=SQL_LOCK_UNLOCK;
				else
				if (strstr(pos,"EXCLUSIVE")!=NULL) wLockType=SQL_LOCK_EXCLUSIVE;

				if (nfunc==46)	RefreshRowset( wRow, wLockType );
				else			SetRowsetCursorPosition( wRow, wLockType );
			}
		}
		break;
	case 47: /*Requery*/
		UpdFieldsArr=TRUE;
		if (IsOpen()) retint=Requery();
		break;
	case 48: /*SetFieldDirty*/
		if (IsOpen() && CanUpdate()) 
		{
			unsigned int nfi=0;
			int state=0;
			m_LastScanf=sscanf(pos,"%d,%d",&nfi,&state);
			if (nfi>=0 && nfi<m_nFields) 
				SetFieldDirty(&a_CStringFieldOut[nfi],state);
		}
		break;
	case 49: /*SetFieldNull*/
		if (IsOpen() && CanUpdate()) 
		{
			unsigned int nfi=atoi(pos);
			if (nfi>=0 && nfi<m_nFields)
				SetFieldNull(&a_CStringFieldOut[nfi]);
		}
		break;
	case 50: /*SetLockingMode*/		
		{
			if ((atoi(pos)&0x1)==0)	SetLockingMode(optimistic);	
			else					SetLockingMode(pessimistic);	
		}break;
	case 51: /*SetParamNull*/
		if (IsOpen()) 
		{
			int nIndex=0, bNull = 1;
			m_LastScanf=sscanf(pos,"%d,%d",&nIndex,&bNull);
			SetParamNull( nIndex, bNull);
		}
		break;
	case 55: /*GetFieldsInfo*/
		if (IsOpen() && oStr!=NULL) 
		{

			unsigned int nIndex;
			char *pos1=oStr;
			for(nIndex=0;nIndex<m_nFields;nIndex++)
			{
				GetFIString(a_CODBCFieldInfo[nIndex],pos1);
				pos1+=(int)strlen(pos1);
				if (nIndex<m_nFields-1)	strcat(pos1++,"\x7F");
				
			}
		}
		break;
	case 56: /*ReadRow*/
		if (IsOpen() && oStr!=NULL) 
		{
			unsigned int nIndex;
			char *pos1=oStr;
			*pos1=0;
			CString tmp;
			for(nIndex=0;nIndex<m_nFields;nIndex++)
			{
				tmp=a_CStringFieldOut[nIndex];
				tmp.Replace(10,3);
				tmp.Replace(13,3);
				tmp.Replace(7,3);
				tmp.Replace(1,3);
				strcat(pos1,tmp);
				pos1+=(int)strlen(pos1);
				if (nIndex<m_nFields-1)	strcat(pos1++,"\x7F");
			}
		}
		break;
	case 57: /*ReadRowMoveNext*/
		if (IsOpen() && oStr!=NULL) 
		{
			unsigned int nIndex;
			char *pos1=oStr;
			*pos1=0;
			CString tmp;
			for(nIndex=0;nIndex<m_nFields;nIndex++)
			{
				tmp=a_CStringFieldOut[nIndex];
				tmp.Replace(10,3);
				tmp.Replace(13,3);
				tmp.Replace(7,3);
				tmp.Replace(1,3);
				strcat(pos1,tmp);
				pos1+=(int)strlen(pos1);
				if (nIndex<m_nFields-1)	strcat(pos1++,"\x7F");
			}
			DoMethod("MoveNext",NULL);
		}
		break;
	case 58: /*ReadRows*/
		if (IsOpen() && oStr!=NULL) 
		{
			unsigned int nIndex;
			char *pos1=oStr;
			int i,nRow=atoi(pos);
			*pos1=0;
			CString tmp;
			for(i=0;i<nRow && !IsEOF();i++)
			{
				for(nIndex=0;nIndex<m_nFields;nIndex++)
				{
					tmp=a_CStringFieldOut[nIndex];
					tmp.Replace(10,3);
					tmp.Replace(13,3);
					tmp.Replace(7,3);
					tmp.Replace(1,3);
					strcat(pos1,tmp);
					pos1+=(int)strlen(pos1);
					if (nIndex<m_nFields-1)	strcat(pos1++,"\x07");
				}
				if (i<nRow-1) strcat(pos1++,"\x7F");
				try			{MoveNext();}
				catch(...)	
				{
					GPC.m_ErrReport.GPWriteErrorLog("GPCRecordset", "DoMethod 471",iMethod);
					if (IsEOF())break;
				}
			}		
		}
		break;
	case 59: /*SetIFV   == SetFieldValue by index*/
		if (IsOpen() && CanUpdate()) 
		{
			unsigned int nIndex=atoi(pos);
			const char *postext=strchr(pos,',');
			if (postext++==NULL) postext="";
			if (nIndex>=0 && nIndex<m_nFields)
				a_CStringFieldOut[nIndex]=postext;
		}
		break;
	case 60: /*SetNFV   == SetFieldValue by name*/
		if (IsOpen() && CanUpdate()) 
		{
			char *postmpcc=new char [(int)strlen(pos)+10];
			strcpy(postmpcc,pos);
			char *postext=strchr(postmpcc,',');
			if (postext==NULL) postext="";
			else *(postext++)=0;

			int nIndex=GetFieldIndexByName(postmpcc);
			if (nIndex>=0 && (unsigned int)nIndex<m_nFields)
				a_CStringFieldOut[nIndex]=postext;
			delete[] postmpcc;
		}
		break;
	case 61: /*WriteRow*/
	case 63: /*AppendRow*/
		if (IsOpen() && CanUpdate()) 
		{
			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
			if (nfunc==61) Edit();
			else AddNew();
			char *postext=pos333,*postmp;
			unsigned int nIndex=0;
			while(postext!=NULL && nIndex<m_nFields)
			{
				postmp=strchr(postext,2);
				if (postmp==NULL) postmp=strchr(postext,GPC.DelimiterIn1);
				if (postmp!=NULL) *(postmp++)=0;
				a_CStringFieldOut[nIndex]=postext;
				postext=postmp;
				nIndex++;
			}
			Update();
			if (nfunc==61) MoveNext();
			delete[] pos333;
		}
		else if (oStr!=NULL) sprintf(oStr,ErrObjSub,met);
		break;
	case 62: /*WriteRows*/
	case 64: /*AppendRows*/
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

				if (nfunc==62) Edit();
				else AddNew();

				char *postext=posrec,*postmp;
				unsigned int nIndex=0;
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
				if (nfunc==62) MoveNext();
				posrec=posrectmp;
			}
			delete[] pos333;
		}
		else if (oStr!=NULL) sprintf(oStr,ErrObjSub,met);
		break;
	case 65: /*DeleteRows*/
		if (IsOpen() && CanUpdate()) 
		{
			int nRows=atoi(pos);
			while((nRows--)>0)
			{
				retint=1;
				Delete();
				MoveNext();
			}
		}
		break;

	default:
		GPC.m_ErrReport.GPWriteWarnLog2("GPCRecordset", "Unknown Method",iMethod);
		if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;
		break;
	}
}
catch(...)
{if (oStr!=NULL) sprintf(oStr,"-1\x7F%s",met);}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
		GPC.m_ErrReport.GPWriteErrorLog("GPCRecordset", "DoMethod",iMethod);
	delete[] met;
	return nfunc;
}


void GPCRecordset::GetFIString(CODBCFieldInfo &finfo, char *oStrInfo)
{
	SWORD swtype[19]={SQL_CHAR,SQL_DECIMAL,SQL_SMALLINT,SQL_REAL,SQL_INTEGER,SQL_FLOAT,SQL_DOUBLE,SQL_NUMERIC,SQL_VARCHAR,SQL_LONGVARCHAR,SQL_BIT,SQL_TINYINT,SQL_BIGINT,SQL_BINARY,SQL_VARBINARY,SQL_LONGVARBINARY,SQL_DATE,SQL_TIME,SQL_TIMESTAMP,};
	char *ctype[19]={"CHAR","DECIMAL","SMALLINT","REAL","INTEGER","FLOAT","DOUBLE","NUMERIC","VARCHAR","LONGVARCHAR","BIT","TINYINT","BIGINT","BINARY","VARBINARY","LONGVARBINARY","DATE","TIME","TIMESTAMP",};

	int ntype;

	for(ntype=0;ntype<19 && finfo.m_nSQLType!=swtype[ntype];ntype++);
	if (ntype>=19) ntype=0;

	sprintf(oStrInfo,"%s\x07%s\x07%d\x07%d\x07%d",(LPCSTR)finfo.m_strName,ctype[ntype],finfo.m_nPrecision,finfo.m_nScale,finfo.m_nNullability);
}

void GPCRecordset::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::inoutParam);
	RFX_Text(pFX, "CourseIDParam", m_strCourseIDParam);

	try
	{
		if (a_CStringFieldOut!=NULL && m_nFields>0)
		{
			UpdateFieldsArr();
			unsigned int i;
			pFX->SetFieldType(CFieldExchange::outputColumn);
			for(i=0;i<m_nFields;i++)
			{
				RFX_Text(pFX,a_CODBCFieldInfo[i].m_strName,a_CStringFieldOut[i],9990);
			}
		}
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPCRecordset", "DoFieldExchange","");
	}

}

void GPCRecordset::UpdateFieldsArr()
{
	if (UpdFieldsArr==TRUE && IsOpen())
	{
		unsigned int i=0;
		BOOL Brk=FALSE;
		try
		{
			if ((i=GetODBCFieldCount())>0)
			{
				m_nFields=i;
				for(i=0;i<m_nFields;i++)
				{
					try
					{
						GetODBCFieldInfo(i,a_CODBCFieldInfo[i]);
					}
					catch(...)
					{
						GPC.m_ErrReport.GPWriteErrorLog("GPCRecordset", "UpdateFieldsArr 646","");
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
			GPC.m_ErrReport.GPWriteErrorLog("GPCRecordset", "UpdateFieldsArr 659","");
		}
	}
}


CString GPCRecordset::GetDefaultConnect()
{
	// this minimal connect string will cause ODBC login dialog to be brought up
	return "ODBC;";
}

CString GPCRecordset::GetDefaultSQL()
{
	// there is no default SQL - a direct ODBC call is made instead
	ASSERT(FALSE);
	return "!";
}

int GPCRecordset::GetFieldIndexByName(const char *name)
{
	unsigned int nField;
	for(nField=0;nField<m_nFields && _stricmp(name,a_CODBCFieldInfo[nField].m_strName)!=0;nField++);
	
	return nField>=m_nFields?-1:nField;
}
