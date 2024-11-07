// GPODBC_Database.cpp: implementation of the GPODBC_Database class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPODBC_Database.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPODBC_Database::GPODBC_Database()
{
	int i;
	for(i=0;i<N_DATABASE_ARR;i++)
		gpdb[i]=NULL;
}

GPODBC_Database::~GPODBC_Database()
{
	int i;
	for(i=0;i<N_DATABASE_ARR;i++)
	{
		if (gpdb[i]!=NULL) delete gpdb[i];
		gpdb[i]=NULL;
	}
}

int GPODBC_Database::OpenGPDB(const char *iStr)
{
	int ret=-1;
	if (strncmp(iStr,"OpenEx ",7)==0)
	{
		int i;
		for(i=0;i<N_DATABASE_ARR;i++)
			if (gpdb[i]==NULL) 
			{
				gpdb[i]=new GPCDatabase;
				char *oStr=GPC.StrTmpOut;
				*GPC.StrTmpOut=0;
				gpdb[i]->DoMethod(iStr,oStr);
				if (atoi(oStr)==0) 
				{
					delete gpdb[i];
					gpdb[i]=NULL;
				}
				else ret=i;
			
				break;
			}
	}
	char oStr[50];
	sprintf(oStr,"%d\r",ret);
	m_Comm.GPSendBlock(oStr,(int)strlen(oStr));
	return ret;
}

BOOL GPODBC_Database::CloseGPDB(int iId)
{
	if (iId>=0 && iId<N_DATABASE_ARR && gpdb[iId]!=NULL)
	{
			gpdb[iId]->DoMethod("Close",NULL);
			delete gpdb[iId];
			gpdb[iId]=NULL;
	}

	return TRUE;
}


void GPODBC_Database::DoDBMethod(const char *iStr, BOOL Ret)
{
	char *postmpcc=new char [(int)strlen(iStr)+10];
	strcpy(postmpcc,iStr);
	char *oStr=NULL,*pos=strchr(postmpcc,';');
	if (Ret==TRUE) {oStr=GPC.StrTmpOut;	*GPC.StrTmpOut=0;}
	int DBId=atoi(iStr); 

	if (pos!=NULL && DBId>=0 && DBId<N_DATABASE_ARR && gpdb[DBId]!=NULL)
			gpdb[DBId]->DoMethod(++pos,oStr);
	else 
	{
#ifdef RUS
		if (oStr!=NULL) sprintf(oStr,"Ошибка задания метода №№%s",iStr);
#else
		if (oStr!=NULL) sprintf(oStr,"Error execution of method №№%s",iStr);
#endif
		GPC.m_ErrReport.GPWriteWarnLog2("GPODBC_Database", "Unknown Method",iStr);
	}
	if (Ret==TRUE) 
	{
		char *postmp=GPC.StrTmpOut;
		char *postmp2=postmp;
		while(*postmp!=0)
		{
			if (*postmp=='\r' || *postmp=='\n')
			{
				if (*(++postmp)=='\r' || *postmp=='\n') postmp++;
				*(postmp2++)=254;
			}
			else *(postmp2++)=*(postmp++);
		}

		strcat(GPC.StrTmpOut,"\r");
		m_Comm.GPSendBlock(AnsiToDos(GPC.StrTmpOut,1),(int)strlen(GPC.StrTmpOut));
	}
	delete[] postmpcc;
}


int GPODBC_Database::OpenGPRS(const char *iStr)
{
	int ret=-1;
	int DBId=atoi(iStr); 
	char retStr[100];
	sprintf(retStr,"-1%c-1\r",0xFE);
	const char *pos=strchr(iStr,';');
	if ((pos++)==NULL) pos="Open ";
	if (DBId>=0 && DBId<N_DATABASE_ARR && gpdb[DBId]!=NULL && (ret=gpdb[DBId]->OpenGPRS(pos))>=0)
		sprintf(retStr,"%d%c%d\r",DBId,0xFE,ret);

	m_Comm.GPSendBlock(retStr,(int)strlen(retStr));
	return ret;
}

BOOL GPODBC_Database::CloseGPRS(const char *iStr)
{
	BOOL ret=FALSE;
	int DBId=atoi(iStr); 
	const char *pos=strchr(iStr,GPC.DelimiterIn1);
	if ((pos++)!=NULL && DBId>=0 && DBId<N_DATABASE_ARR && gpdb[DBId]!=NULL)
		ret=gpdb[DBId]->CloseGPRS(pos);

	return ret;
}


void GPODBC_Database::DoRSMethod(const char *iStr, BOOL Ret)
{
	int DBId=atoi(iStr); 
	const char *pos=strchr(iStr,GPC.DelimiterIn1);
	if ((pos++)!=NULL && DBId>=0 && DBId<N_DATABASE_ARR && gpdb[DBId]!=NULL)
		gpdb[DBId]->DoRSMethod(pos,Ret);
	else
	{
		GPC.m_ErrReport.GPWriteWarnLog2("GPODBC_Recordset", "Unknown Method",iStr);
		if (Ret==TRUE)
		{
			m_Comm.GPSendBlock("-1\r",3);
		}
	}
}
