// GPCDatabase.cpp: implementation of the GPCDatabase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPCDatabase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPCDatabase::GPCDatabase()
{
	int i;
	for(i=0;i<N_MAX_RECODSET;i++)
		GPRS[i]=NULL;
}

GPCDatabase::~GPCDatabase()
{
	int i;
	for(i=0;i<N_MAX_RECODSET;i++)
		if (GPRS[i]!=NULL)
		{
			delete GPRS[i];
			GPRS[i]=NULL;
		}
}

int GPCDatabase::DoMethod(const char *iMethod, char *oStr)
{
	char *met=new char [(int)strlen(iMethod)+50];
	strcpy(met,iMethod);
	const char *pos=strchr(iMethod,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	char *fn[18]={
		"OpenEx","Close","GetConnect","IsOpen","GetDatabaseName",
		"CanUpdate","CanTransact","SetLoginTimeout","SetQueryTimeout","GetBookmarkPersistence",
		"GetCursorCommitBehavior","GetCursorRollbackBehavior","BeginTrans","BindParameters","CommitTrans",
		"Rollback","Cancel","ExecuteSQL",
	};

	int nfunc;
	if (*met>='0' && *met<='9') nfunc=atoi(met);
	else
		for(nfunc=0;nfunc<18 && _stricmp(met,fn[nfunc])!=0;nfunc++); 

try
{
	switch(nfunc)
	{
	case 0: /*OpenEx*/
		{
			char *postmpcc=new char [(int)strlen(pos)+10];
			strcpy(postmpcc,pos);
			DWORD opt[5]={CDatabase::openExclusive,CDatabase::openReadOnly,CDatabase::useCursorLib,CDatabase::noOdbcDialog,CDatabase::forceOdbcDialog,};
			char *copt[5]={"EXCLUSIVE","READONLY","CURSOR","NODIALOG","FORCEDIALOG",};
			char *constr=strchr(postmpcc,';');
			DWORD flg=0;
			if (constr!=NULL) *(constr++)=0;
			int i;
			for(i=0;i<5;i++)
				if (strstr(postmpcc,copt[i])!=NULL) flg|=opt[i];

			BOOL ret=FALSE;
			try
			{
				ret=OpenEx(constr,flg);
			}catch(...)
			{
				GPC.m_ErrReport.GPWriteErrorLog("GPCDatabase", "DoMethod 80",iMethod);
			}

			if (oStr!=NULL) sprintf(oStr,"%d",ret);
			delete[] postmpcc;
		}
		break;
	case 1: /*Close*/			Close(); break;
	case 2: /*GetConnect*/		if (oStr!=NULL) strcpy(oStr,GetConnect());			break;
	case 3: /*IsOpen*/			if (oStr!=NULL) sprintf(oStr,"%d",IsOpen());		break;
	case 4: /*GetDatabaseName*/	if (oStr!=NULL) strcpy(oStr,GetDatabaseName());		break;
	case 5: /*CanUpdate*/		if (oStr!=NULL) sprintf(oStr,"%d",CanUpdate());		break;
	case 6: /*CanTransact*/		if (oStr!=NULL) sprintf(oStr,"%d",CanTransact());	break;
	case 7: /*SetLoginTimeout*/	SetLoginTimeout(atoi(pos));		break;
	case 8: /*SetQueryTimeout*/	SetLoginTimeout(atoi(pos));		break;
	case 9: /*GetBookmarkPersistence*/
		if (oStr!=NULL)
		{
			DWORD ret=GetBookmarkPersistence();
			DWORD retst[7]={SQL_BP_CLOSE,SQL_BP_DELETE,SQL_BP_DROP,SQL_BP_SCROLL,SQL_BP_TRANSACTION,SQL_BP_UPDATE,SQL_BP_OTHER_HSTMT,};
			char  *cret[7]={"_CLOSE|","_DELETE|","_DROP|","_SCROLL|","_TRANSACTION|","_UPDATE|","_OTHER_HSTMT|",};
			int i;
			for(i=0;i<7;i++)
				if ((ret&retst[i])==retst[i])	strcat(oStr,cret[i]);
		}
		break;
	case 10: /*GetCursorCommitBehavior*/
	case 11: /*GetCursorRollbackBehavior*/
		if (oStr!=NULL)
		{
			int ret;
			if (nfunc==10)	ret=GetBookmarkPersistence();
			else			ret=GetCursorRollbackBehavior();
			int retst[3]={SQL_CB_CLOSE,SQL_CB_DELETE,SQL_CB_PRESERVE,};
			char  *cret[3]={"_CLOSE|","_DELETE|","_PRESERVE|",};
			int i;
			for(i=0;i<3;i++)
				if ((ret&retst[i])==retst[i])	strcat(oStr,cret[i]);
		}
		break;
	case 12: /*BeginTrans*/
		{
			BOOL ret=BeginTrans();
			if (oStr!=NULL) sprintf(oStr,"%d",ret);
		}
		break;
	case 14: /*CommitTrans*/
		{
			BOOL ret=CommitTrans();
			if (oStr!=NULL) sprintf(oStr,"%d",ret);
		}
		break;
	case 15: /*Rollback*/
		{
			BOOL ret=Rollback();
			if (oStr!=NULL) sprintf(oStr,"%d",ret);
		}
		break;
	case 16: /*Cancel*/		Cancel();	break;
	case 17: /*ExecuteSQL*/
		{
			BOOL ret=TRUE;
			try
			{	ExecuteSQL(pos);	}
			catch(...)
			{
				GPC.m_ErrReport.GPWriteErrorLog("GPCDatabase", "DoMethod 146",iMethod);
				ret=FALSE;
			}

			if (oStr!=NULL) sprintf(oStr,"%d",ret);
		}
		break;

	case 13: /*BindParameters*/
	default: 
		if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL; 
		GPC.m_ErrReport.GPWriteWarnLog2("GPCDatabase", "Unknown Method",iMethod);
		break;
	}
}catch(CDBException e)
{
	BOOL ret=FALSE;
	AfxMessageBox(e.m_strStateNativeOrigin);
	sprintf(oStr,"%d",ret);
	GPC.m_ErrReport.GPWriteErrorLog("GPCDatabase", "DoMethod",iMethod);
}

	delete[] met;
	return nfunc;
}


int GPCDatabase::OpenGPRS(const char *iStr)
{
	int ret=-1;
	if (strncmp(iStr,"Open ",5)==0)
	{
		int i;
		for(i=0;i<N_MAX_RECODSET;i++)
			if (GPRS[i]==NULL) 
			{
				GPRS[i]=new GPCRecordset(this);
				char *oStr=GPC.StrTmpOut;
				*GPC.StrTmpOut=0;
				GPRS[i]->DoMethod(iStr,oStr);
				if (atoi(oStr)==0) 
				{
					delete GPRS[i];
					GPRS[i]=NULL;
				}
				else ret=i;

				break;
			}
	}
	return ret;
}

int GPCDatabase::CloseGPRS(const char *iStr)
{
	int nRS=atoi(iStr);
	if (nRS>=0 && nRS<N_MAX_RECODSET && GPRS[nRS]!=NULL)
	{
		GPRS[nRS]->DoMethod("Close",NULL);
		delete GPRS[nRS];
		GPRS[nRS]=NULL;
	}
	return nRS;
}

void GPCDatabase::DoRSMethod(const char *iStr, BOOL Ret)
{
	char *postmpcc=new char [(int)strlen(iStr)+10];
	strcpy(postmpcc,iStr);
	char *pos=strchr(postmpcc,';');
	if (Ret) *GPC.StrTmpOut=0;
	int RSId=atoi(postmpcc); 
	if (pos==NULL || RSId<0 || RSId>=N_MAX_RECODSET || GPRS[RSId]==NULL || GPRS[RSId]->DoMethod((GPRS[RSId]->m_DosAnsiFlag)?++pos:AnsiToDos(++pos,0),GPC.StrTmpOut)==0xFFFFFFFFL)
	{
		GPC.m_ErrReport.GPWriteWarnLog2("GPCRecordset", "Unknown Method",iStr);
#ifdef RUS
		if (Ret) sprintf(GPC.StrTmpOut,"Ошибка задания метода №№%s",iStr);
#else
		if (Ret) sprintf(GPC.StrTmpOut,"Error execution of method №№%s",iStr);
#endif
	}
	else 
	{
		if (Ret) 
		{
			char *postmp=GPC.StrTmpOut;
			char *postmp2=postmp;
			if (RSId<N_MAX_RECODSET && GPRS[RSId] && !GPRS[RSId]->m_DosAnsiFlag)
				DosToAnsi(GPC.StrTmpOut);

			while(*postmp!=0)
			{
				if (*postmp=='\r' || *postmp=='\n')
				{
					if (*(++postmp)=='\r' || *postmp=='\n') postmp++;
					*(postmp2++)=127;
				}
				else *(postmp2++)=*(postmp++);
			}
			strcat(GPC.StrTmpOut,"\r");
			m_Comm.GPSendBlock(AnsiToDos(GPC.StrTmpOut,1),(int)strlen(GPC.StrTmpOut));
		}
	}
	delete[] postmpcc;
}
