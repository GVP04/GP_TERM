// GPCDAOWorkspace.cpp: implementation of the GPCDAOWorkspace class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPCDAOWorkspace.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const UINT GPCDAOWorkspace::nArrLocale=21;
const char *GPCDAOWorkspace::LocName[]={
		"GENERAL","ARABIC","CYRILLIC","CZECH","DUTCH",
		"GREEK","HEBREW","HUNGARIAN","ICELANDIC","NORDIC",
		"NORWDAN","POLISH","SPANISH","SWEDFIN","TURKISH",
		"JAPANESE","CHINESESIMPLIFIED","CHINESETRADITIONAL","KOREAN","THAI",
		"SLOVENIAN","",
	};
LPCTSTR GPCDAOWorkspace::uLocale[]={
		dbLangGeneral,dbLangArabic,dbLangCyrillic,dbLangCzech,dbLangDutch,
		dbLangGreek,dbLangHebrew,dbLangHungarian,dbLangIcelandic,dbLangNordic,
		dbLangNorwDan,dbLangPolish,dbLangSpanish,dbLangSwedFin,dbLangTurkish,
		dbLangJapanese,dbLangChineseSimplified,dbLangChineseTraditional,dbLangKorean,dbLangThai,
		dbLangSlovenian,dbLangGeneral,
	};


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPCDAOWorkspace::GPCDAOWorkspace()
{
	int i,j;
	for(i=0;i<N_DAOWORKSPACE_ARR;i++)
	{
		for(j=0;j<N_DAODATABASE_COUNT;j++) gpdb[i*N_DAODATABASE_COUNT+j]=NULL;
		gpws[i]=NULL;
	}
}

GPCDAOWorkspace::~GPCDAOWorkspace()
{
	int i;
	for(i=0;i<N_DAOWORKSPACE_ARR;i++)
		CloseGPWS(i);
}


int GPCDAOWorkspace::OpenGPWS(const char *iStr)
{
	int ret=-1;
	char *oStr=new char [(int)strlen(iStr)+50];
	strcpy(oStr,iStr);
	char *pos2=strchr(oStr,';');
	if (pos2!=NULL) *(pos2++)=0;
	else pos2="";
	char *pos3=strchr(pos2,';');
	if (pos3!=NULL) *(pos3++)=0;
	else pos3="";

	int i;
	for(i=0;i<N_DAOWORKSPACE_ARR;i++)
		if (gpws[i]!=NULL && gpws[i]->IsOpen() && gpws[i]->GetName()==oStr) break;

	if (i<N_DAOWORKSPACE_ARR)
	{
		int j;
		for(j=0;j<N_DAODATABASE_COUNT;j++)
			if (gpdb[i*N_DAODATABASE_COUNT+j]!=NULL)
			{
				if (gpdb[i*N_DAODATABASE_COUNT+j]->GPIsOpen())
					gpdb[i*N_DAODATABASE_COUNT+j]->GPClose();

				delete gpdb[i*N_DAODATABASE_COUNT+j];
				gpdb[i]=NULL;
			}

		gpws[i]->Close();
		delete gpws[i];
		gpws[i]=NULL;
	}

	for(i=0;i<N_DAOWORKSPACE_ARR;i++)
		if (gpws[i]==NULL) 
		{
			gpws[i]=new CDaoWorkspace;
			gpws[i]->Create(oStr,pos2,pos3);
			try{gpws[i]->Append( );}catch(...)
			{
				GPC.m_ErrReport.GPWriteErrorLog("GPCDAOWorkspace", "OpenGPWS",iStr);
			}
			break;
		}

	if (i>=N_DAOWORKSPACE_ARR) i=-1;
	sprintf(oStr,"%d\r",i);
	m_Comm.GPSendBlock(oStr,(int)strlen(oStr));
	return ret;
}

BOOL GPCDAOWorkspace::CloseGPWS(int IdWS)
{
	BOOL ret=FALSE;

	if (IdWS>=0 && IdWS<=N_DAOWORKSPACE_ARR && gpws[IdWS]!=NULL)
	{
		int j;
		for(j=0;j<N_DAODATABASE_COUNT;j++)
		{
			int IdDB=IdWS*N_DAODATABASE_COUNT+j;
			if (gpdb[IdDB]!=NULL)
			{
				if (gpdb[IdDB]->GPIsOpen()) gpdb[IdDB]->GPClose();
				delete gpdb[IdDB];
				gpdb[IdDB]=NULL;
			}
		}

		if (gpws[IdWS]->IsOpen()) gpws[IdWS]->Close();
		delete gpws[IdWS];
		gpws[IdWS]=NULL;
		ret=TRUE;
	}
	return ret;		
}

int GPCDAOWorkspace::OpenGPDB(const char *iStr)
{
	int IdWS=-1,IdDB;
	m_LastScanf=sscanf(iStr,"%d",&IdWS);
	int ret=-1;

	if (IdWS>=0 && IdWS<=N_DAOWORKSPACE_ARR && gpws[IdWS]!=NULL && gpws[IdWS]->IsOpen())
	{
		int DBNum=IdWS*N_DAODATABASE_COUNT;
		for(IdDB=0;IdDB<N_DAODATABASE_COUNT && gpdb[IdDB+DBNum]!=NULL;IdDB++);
		if (IdDB<N_DAODATABASE_COUNT)
		{
			gpdb[IdDB+DBNum]=new GPCDAODatabase(gpws[IdWS]);
			const char *posdb=strchr(iStr,';');
			if (posdb++==NULL) posdb="";
			if (gpdb[IdDB+DBNum]->GPOpen(posdb)==TRUE)	ret=IdDB;
			else
			{
				delete gpdb[IdDB+DBNum];
				gpdb[IdDB+DBNum]=NULL;
			}
		}
	}
	char retStr[100];
	sprintf(retStr,"%d\x7F%d",IdWS,ret);
	SendRet(retStr,0);
	return ret;

}

int GPCDAOWorkspace::CreateGPDB(const char *iStr)
{
	int IdWS=-1,IdDB;
	m_LastScanf=sscanf(iStr,"%d",&IdWS);
	int ret=-1;

	if (IdWS>=0 && IdWS<=N_DAOWORKSPACE_ARR && gpws[IdWS]!=NULL && gpws[IdWS]->IsOpen())
	{
		int DBNum=IdWS*N_DAODATABASE_COUNT;
		for(IdDB=0;IdDB<N_DAODATABASE_COUNT && gpdb[IdDB+DBNum]!=NULL;IdDB++);
		if (IdDB<N_DAODATABASE_COUNT)
		{
			gpdb[IdDB+DBNum]=new GPCDAODatabase(gpws[IdWS]);
			const char *posdb=strchr(iStr,';');
			if (posdb++==NULL) posdb="";
			if (gpdb[IdDB+DBNum]->GPCreate(posdb)==TRUE)	ret=IdDB;
			else
			{
				delete gpdb[IdDB+DBNum];
				gpdb[IdDB+DBNum]=NULL;
			}
		}
	}
	char retStr[100];
	sprintf(retStr,"%d\x7F%d",IdWS,ret);
	SendRet(retStr,0);
	return ret;

}

BOOL GPCDAOWorkspace::CloseGPDB(const char *iStr)
{
	BOOL ret=FALSE;
	int IdWS=-1,IdDB=-1;
	m_LastScanf=sscanf(iStr,"%d;%d",&IdWS,&IdDB);
	int DBNum=IdWS*N_DAODATABASE_COUNT+IdDB;
	if (IdWS>=0 && IdWS<=N_DAOWORKSPACE_ARR && gpws[IdWS]!=NULL && gpws[IdWS]->IsOpen()
		&& IdDB>=0 && IdDB<=N_DAODATABASE_COUNT && gpdb[DBNum]!=NULL)
	{
		if (gpdb[DBNum]->GPIsOpen()) gpdb[DBNum]->GPClose();
		delete gpdb[DBNum];
		gpdb[DBNum]=NULL;
		ret=TRUE;
	}

	return TRUE;
}

int GPCDAOWorkspace::OpenGPRS(const char *iStr)
{
	int IdWS=-1,IdDB=-1;
	int ret=-1;
	m_LastScanf=sscanf(iStr,"%d;%d",&IdWS,&IdDB);
	int DBNum=IdWS*N_DAODATABASE_COUNT+IdDB;
	if (IdWS>=0 && IdWS<=N_DAOWORKSPACE_ARR && gpws[IdWS]!=NULL && gpws[IdWS]->IsOpen()
		&& IdDB>=0 && IdDB<=N_DAODATABASE_COUNT && gpdb[DBNum]!=NULL && gpdb[DBNum]->GPIsOpen())
	{
		const char *posRS=strchr(iStr,';');
		if (posRS!=NULL) posRS=strchr(++posRS,';');
		if (posRS++==NULL) posRS="";
		ret=gpdb[DBNum]->OpenRS(posRS);
	}

	char retStr[100];
	sprintf(retStr,"%d\x7F%d\x7F%d",IdWS,IdDB,ret);
	SendRet(retStr,0);
	return ret;
}

BOOL GPCDAOWorkspace::CloseGPRS(const char *iStr)
{
	BOOL ret=FALSE;
	int IdWS=-1,IdDB=-1,IdRS=-1;
	m_LastScanf=sscanf(iStr,"%d;%d;%d",&IdWS,&IdDB,&IdRS);
	int DBNum=IdWS*N_DAODATABASE_COUNT+IdDB;

	if (IdWS>=0 && IdWS<=N_DAOWORKSPACE_ARR && gpws[IdWS]!=NULL && gpws[IdWS]->IsOpen()
		&& IdDB>=0 && IdDB<=N_DAODATABASE_COUNT && gpdb[DBNum]!=NULL && gpdb[DBNum]->GPIsOpen())
	{
		ret=gpdb[DBNum]->CloseRS(IdRS);
	}
	return ret;
}

void GPCDAOWorkspace::DoWSMethod(const char *iMethod, BOOL Ret)
{
	char *oStr=NULL;
	const char *posmet=strchr(iMethod,';');
	if (posmet++==NULL) posmet="";

	if (Ret==TRUE) {oStr=GPC.StrTmpOut;	*GPC.StrTmpOut=0;}

	int IdWS=-1;
	m_LastScanf=sscanf(iMethod,"%d",&IdWS);


	if (IdWS>=0 && IdWS<=N_DAOWORKSPACE_ARR && gpws[IdWS]!=NULL)
	{
		DoMethod(IdWS,posmet,oStr);
	}
	else 
	{
#ifdef RUS
		if (oStr!=NULL) sprintf(oStr,"Ошибка задания метода №№%s",iMethod);
#else
		if (oStr!=NULL) sprintf(oStr,"Error execution of method №№%s",iMethod);
#endif
		GPC.m_ErrReport.GPWriteWarnLog2("GPCDAOWorkspace", "Unknown Method",iMethod);
	}
	if (Ret==TRUE) SendRet(oStr,0);
}


void GPCDAOWorkspace::DoDBMethod(const char *iMethod, BOOL Ret)
{
	char *oStr=NULL;
	const char *posmet=strchr(iMethod,';');
	if (posmet!=NULL) posmet=strchr(++posmet,';');
	if (posmet++==NULL) posmet="";

	if (Ret==TRUE) {oStr=GPC.StrTmpOut;	*GPC.StrTmpOut=0;}

	int IdWS=-1,IdDB=-1;
	m_LastScanf=sscanf(iMethod,"%d;%d",&IdWS,&IdDB);


	int DBNum=IdWS*N_DAODATABASE_COUNT+IdDB;
	if (IdWS>=0 && IdWS<=N_DAOWORKSPACE_ARR && gpws[IdWS]!=NULL && gpws[IdWS]->IsOpen()
		&& IdDB>=0 && IdDB<=N_DAODATABASE_COUNT && gpdb[DBNum]!=NULL)
	{
		gpdb[DBNum]->DoMethod(posmet,oStr);
	}
	else 
	{
#ifdef RUS
		if (oStr!=NULL) sprintf(oStr,"Ошибка задания метода №№%s",iMethod);
#else
		if (oStr!=NULL) sprintf(oStr,"Error execution of method №№%s",iMethod);
#endif
		GPC.m_ErrReport.GPWriteWarnLog2("GPCDAODatabase", "Unknown Method",iMethod);
	}
	if (Ret==TRUE) SendRet(oStr,0);
}

void GPCDAOWorkspace::DoRSMethod(const char *iMethod, BOOL Ret)
{
	char *oStr=NULL;
	const char *posmet=strchr(iMethod,';');
	if (posmet!=NULL) posmet=strchr(++posmet,';');
	if (posmet++==NULL) posmet="";

	if (Ret==TRUE) {oStr=GPC.StrTmpOut;	*GPC.StrTmpOut=0;}

	int IdWS=-1,IdDB=-1;
	m_LastScanf=sscanf(iMethod,"%d;%d",&IdWS,&IdDB);
	int typesend=0;

	int DBNum=IdWS*N_DAODATABASE_COUNT+IdDB;
	if (IdWS>=0 && IdWS<=N_DAOWORKSPACE_ARR && gpws[IdWS]!=NULL && gpws[IdWS]->IsOpen()
		&& IdDB>=0 && IdDB<=N_DAODATABASE_COUNT && gpdb[DBNum]!=NULL && gpdb[DBNum]->GPIsOpen())
	{
		if (gpdb[DBNum]->DoRSMethod(posmet,oStr)==2) typesend=1;
	}
	else 
	{
#ifdef RUS
		if (oStr!=NULL) sprintf(oStr,"Ошибка задания метода №№%s",iMethod);
#else
		if (oStr!=NULL) sprintf(oStr,"Error execution of method №№%s",iMethod);
#endif
		GPC.m_ErrReport.GPWriteWarnLog2("GPCDAORecordset", "Unknown Method",iMethod);
	}
	if (Ret==TRUE) SendRet(oStr,typesend);

}

void GPCDAOWorkspace::DoQDMethod(const char *iMethod, BOOL Ret)
{
	char *oStr=NULL;
	const char *posmet=strchr(iMethod,';');
	if (posmet!=NULL) posmet=strchr(++posmet,';');
	if (posmet++==NULL) posmet="";

	if (Ret==TRUE) {oStr=GPC.StrTmpOut;	*GPC.StrTmpOut=0;}

	int IdWS=-1,IdDB=-1;
	m_LastScanf=sscanf(iMethod,"%d;%d",&IdWS,&IdDB);


	int DBNum=IdWS*N_DAODATABASE_COUNT+IdDB;
	if (IdWS>=0 && IdWS<=N_DAOWORKSPACE_ARR && gpws[IdWS]!=NULL && gpws[IdWS]->IsOpen()
		&& IdDB>=0 && IdDB<=N_DAODATABASE_COUNT && gpdb[DBNum]!=NULL && gpdb[DBNum]->GPIsOpen())
	{
		gpdb[DBNum]->DoQDMethod(posmet,oStr);
	}
	else 
	{
#ifdef RUS
		if (oStr!=NULL) sprintf(oStr,"Ошибка задания метода №№%s",iMethod);
#else
		if (oStr!=NULL) sprintf(oStr,"Error execution of method №№%s",iMethod);
#endif
		GPC.m_ErrReport.GPWriteWarnLog2("GPCDAOQueryDef", "Unknown Method",iMethod);
	}
	if (Ret==TRUE) SendRet(oStr,0);

}

void GPCDAOWorkspace::DoTDMethod(const char *iMethod, BOOL Ret)
{
	char *oStr=NULL;
	const char *posmet=strchr(iMethod,';');
	if (posmet!=NULL) posmet=strchr(++posmet,';');
	if (posmet++==NULL) posmet="";

	if (Ret==TRUE) {oStr=GPC.StrTmpOut;	*GPC.StrTmpOut=0;}

	int IdWS=-1,IdDB=-1;
	m_LastScanf=sscanf(iMethod,"%d;%d",&IdWS,&IdDB);


	int DBNum=IdWS*N_DAODATABASE_COUNT+IdDB;
	if (IdWS>=0 && IdWS<=N_DAOWORKSPACE_ARR && gpws[IdWS]!=NULL && gpws[IdWS]->IsOpen()
		&& IdDB>=0 && IdDB<=N_DAODATABASE_COUNT && gpdb[DBNum]!=NULL && gpdb[DBNum]->GPIsOpen())
	{
		gpdb[DBNum]->DoTDMethod(posmet,oStr);
	}
	else 
	{
#ifdef RUS
		if (oStr!=NULL) sprintf(oStr,"Ошибка задания метода №№%s",iMethod);
#else
		if (oStr!=NULL) sprintf(oStr,"Error execution of method №№%s",iMethod);
#endif
		GPC.m_ErrReport.GPWriteWarnLog2("GPCDAOTableDef", "Unknown Method",iMethod);
	}

	if (Ret==TRUE) SendRet(oStr,0);

}

void GPCDAOWorkspace::SendRet(char *oStr, int type)
{
	char tmp[50];
	strcpy(tmp,"!!!ERROR");
	if (oStr==NULL) oStr=tmp;

	char *postmp=oStr;
	char *postmp2=postmp;


	if (!type==0)
		DosToAnsi(oStr);

	while(*postmp!=0)
	{
		if (*postmp=='\r' || *postmp=='\n')
		{
			if (*(++postmp)=='\r' || *postmp=='\n') postmp++;
			*(postmp2++)=127;
		}
		else *(postmp2++)=*(postmp++);
	}

	strcat(oStr,"\r");
	m_Comm.GPSendBlock(AnsiToDos(oStr,1),(int)strlen(oStr));
}

void GPCDAOWorkspace::DoStaticWSMethod(const char *iMethod, BOOL Ret)
{
	char *oStr=NULL;
	if (Ret==TRUE) {oStr=GPC.StrTmpOut;	*GPC.StrTmpOut=0;}

	char *met=new char [(int)strlen(iMethod)+50];
	strcpy(met,iMethod);
	char *pos=strchr(met,' ');
	if (pos==NULL) pos=(char *)(met+(int)strlen(met));
	else	
	{
		*(pos++)=0;
		pos=strchr(met,' ');
		pos++;
	}
	int nfunc;
	char *fn[10]={
		"GetVersion","GetIniPath","GetLoginTimeout","SetDefaultPassword","SetDefaultUser",
		"SetIniPath","SetLoginTimeout","CompactDatabase","RepairDatabase","Idle",
	};

	if (*met>='0' && *met<='9') nfunc=atoi(met);
	else
		for(nfunc=0;nfunc<10 && _stricmp(met,fn[nfunc])!=0;nfunc++); 

	int retint=-123456; 
	int atoipos=atoi(pos);

	try
	{
		switch(nfunc)
		{
		case 0:	/*GetVersion*/	if (oStr!=NULL) strcpy(oStr,CDaoWorkspace::GetVersion());		break;
		case 1:	/*GetIniPath*/	if (oStr!=NULL) strcpy(oStr,CDaoWorkspace::GetIniPath());		break;
		case 2:	/*GetLoginTimeout*/		retint=CDaoWorkspace::GetLoginTimeout();		break;
		case 3:	/*SetDefaultPassword*/	CDaoWorkspace::SetDefaultPassword(pos);			break;
		case 4:	/*SetDefaultUser*/		CDaoWorkspace::SetDefaultUser(pos);				break;
		case 5:	/*SetIniPath*/			CDaoWorkspace::SetIniPath(pos);					break;
		case 6:	/*SetLoginTimeout*/		CDaoWorkspace::SetLoginTimeout(atoipos);		break;
		case 7:	/*CompactDatabase*/		
			{
				const char *cParam[5]={"SRC=","DST=","LOCALE=","OPTION=","PWD=",};
				const char *cPos[5]={NULL,NULL,NULL,NULL,NULL,};
				int iOpt=0;
				_strupr(pos);
				char pwd[250];

				int i;
				for(i=0;i<5;i++)
					if ((cPos[i]=strstr(pos,cParam[i])))
						cPos[i]+=(int)strlen(cParam[i]);

				for(i=0;i<5;i++)
					if (cPos[i]!=NULL)
					{
						char *postmpcc=new char [(int)strlen(cPos[i])+10];
						strcpy(postmpcc,cPos[i]);
						char *tmppos;
						tmppos=strchr(postmpcc,';');
						if (tmppos!=NULL) *tmppos=0;
						switch(i)
						{
						case 2: /*"LOCALE="*/	cPos[i]=TranslateLocale(postmpcc);		break;
						case 3: /*"OPTION="*/	iOpt=TranslateOptions(postmpcc);		break;
						case 4: //"PWD="
							sprintf(pwd,";PWD=\"%s\"",postmpcc);
							cPos[i]=pwd;
							break;
						}
						delete[] postmpcc;
					}
					else cPos[i]="";

				CDaoWorkspace::CompactDatabase(cPos[0],cPos[1],cPos[2],iOpt,cPos[4]);
			}
			break;
		case 8:	/*RepairDatabase*/		CDaoWorkspace::RepairDatabase(pos);	break;
		case 9:	/*Idle*/
			{
				CDaoWorkspace::Idle(dbFreeLocks);
			}
			break;
		default: 
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
		GPC.m_ErrReport.GPWriteErrorLog("GPCDAOWorkspace", "DoStaticWSMethod",iMethod);
		delete[] str;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
	delete[] met;
	if (Ret==TRUE) SendRet(oStr,0);
}



int GPCDAOWorkspace::DoMethod(int IdWS, const char *iMethod, char *oStr)
{
	char *met=new char [(int)strlen(iMethod)+50];
	strcpy(met,iMethod);
	const char *pos=strchr(iMethod,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc;
	char *fn[12]={
		"GetIsolateODBCTrans","GetName","GetUserName","IsOpen","SetIsolateODBCTrans",
		"BeginTrans","CommitTrans","GetDatabaseCount","GetDatabaseInfo","GetWorkspaceCount",
		"GetWorkspaceInfo","Rollback",
	};

	if (*met>='0' && *met<='9') nfunc=atoi(met);
	else
		for(nfunc=0;nfunc<12 && _stricmp(met,fn[nfunc])!=0;nfunc++); 

	int retint=-123456; 
	int atoipos=atoi(pos);

	try
	{
		switch(nfunc)
		{
		case 0:	/*GetIsolateODBCTrans*/		retint=gpws[IdWS]->GetIsolateODBCTrans();	break;
		case 1:	/*GetName*/					if (oStr!=NULL) strcpy(oStr,gpws[IdWS]->GetName());	break;
		case 2:	/*GetUserName*/				if (oStr!=NULL) strcpy(oStr,gpws[IdWS]->GetUserName());	break;
		case 3:	/*IsOpen*/					retint=gpws[IdWS]->IsOpen();	break;
		case 4:	/*SetIsolateODBCTrans*/		gpws[IdWS]->SetIsolateODBCTrans(atoipos);	break;
		case 5:	/*BeginTrans*/				gpws[IdWS]->BeginTrans();	break;
		case 6:	/*CommitTrans*/				gpws[IdWS]->CommitTrans();	break;
		case 7:	/*GetDatabaseCount*/		retint=gpws[IdWS]->GetDatabaseCount();	break;
		case 8:	/*GetDatabaseInfo*/
			if (oStr!=NULL)
			{
				CDaoDatabaseInfo dbinfo;
				gpws[IdWS]->GetDatabaseInfo(atoipos,dbinfo,AFX_DAO_ALL_INFO);
				sprintf(oStr,"%s\x7F%s\x7F%s\x7F%d\x7F%d\x7F%d\x7F%d",
					(LPCSTR)dbinfo.m_strName,
					(LPCSTR)dbinfo.m_strVersion,
					(LPCSTR)dbinfo.m_strConnect,
					dbinfo.m_nQueryTimeout,
					dbinfo.m_lCollatingOrder,
					dbinfo.m_bUpdatable,
					dbinfo.m_bTransactions);
			}
			break;
		case 9:	/*GetWorkspaceCount*/		retint=gpws[IdWS]->GetWorkspaceCount();	break;
		case 10:	/*GetWorkspaceInfo*/
			if (oStr!=NULL)
			{
				CDaoWorkspaceInfo dbinfo;
				gpws[IdWS]->GetWorkspaceInfo(atoipos,dbinfo,AFX_DAO_ALL_INFO);
				sprintf(oStr,"%s\x7F%s\x7F%d",
					(LPCSTR)dbinfo.m_strName,
					(LPCSTR)dbinfo.m_strUserName,
					dbinfo.m_bIsolateODBCTrans);
			}
			break;
		case 11:	/*Rollback*/		gpws[IdWS]->Rollback();	break;
		default:
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
		GPC.m_ErrReport.GPWriteErrorLog("GPCDAOWorkspace", "DoMethod",iMethod);
		delete[] str;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
	delete[] met;
	return nfunc;
}

const char * GPCDAOWorkspace::TranslateLocale(const char *iStr)
{
	const char *ret;
	static char loc[250];

	int j;
	for(j=0;j<21 && strcmp(iStr,LocName[j])!=0;j++);
	if (j>=15)
	{
		sprintf(loc,";%s",iStr);
		char *tmp=loc;
		while(*tmp!=0) 
			if (*tmp==',') *(tmp++)=';';
			else tmp++;

		ret=loc;
	}
	else ret=uLocale[j];

	return ret;
}

const char * GPCDAOWorkspace::ReTranslateLocale(LPCTSTR iType)
{
	int i;
	for(i=0;i<nArrLocale && _stricmp(iType,uLocale[i])!=0;i++);
	return LocName[i];
}

int GPCDAOWorkspace::TranslateOptions(const char *iStr)
{
	int ret=0;
	char *cOpt[6]={"ENCRYPT","DECRYPT","VERSION10","VERSION11","VERSION20","VERSION30",};
	int iOptArr[6]={dbEncrypt,dbDecrypt,dbVersion10,dbVersion11,dbVersion20,dbVersion30,};
	int j;
	for(j=0;j<6;j++)
		if (strstr(iStr,cOpt[j])!=NULL) ret|=iOptArr[j];

	return ret;
}


BOOL GPCDAOWorkspace::CloseGPQDef(const char *iStr)
{
	BOOL ret=FALSE;
	int IdWS=-1,IdDB=-1,IdQDef=-1;
	m_LastScanf=sscanf(iStr,"%d;%d;%d",&IdWS,&IdDB,&IdQDef);
	int DBNum=IdWS*N_DAODATABASE_COUNT+IdDB;

	if (IdWS>=0 && IdWS<=N_DAOWORKSPACE_ARR && gpws[IdWS]!=NULL && gpws[IdWS]->IsOpen()
		&& IdDB>=0 && IdDB<=N_DAODATABASE_COUNT && gpdb[DBNum]!=NULL && gpdb[DBNum]->GPIsOpen())
	{
		ret=gpdb[DBNum]->CloseGPQDef(IdQDef);
	}
	return ret;
}

BOOL GPCDAOWorkspace::CloseGPTDef(const char *iStr)
{
	BOOL ret=FALSE;
	int IdWS=-1,IdDB=-1,IdTDef=-1;
	m_LastScanf=sscanf(iStr,"%d;%d;%d",&IdWS,&IdDB,&IdTDef);
	int DBNum=IdWS*N_DAODATABASE_COUNT+IdDB;

	if (IdWS>=0 && IdWS<=N_DAOWORKSPACE_ARR && gpws[IdWS]!=NULL && gpws[IdWS]->IsOpen()
		&& IdDB>=0 && IdDB<=N_DAODATABASE_COUNT && gpdb[DBNum]!=NULL && gpdb[DBNum]->GPIsOpen())
	{
		ret=gpdb[DBNum]->CloseGPTDef(IdTDef);
	}
	return ret;
}

int GPCDAOWorkspace::OpenGPQDef(const char *iStr)
{
	int IdWS=-1,IdDB=-1;
	int ret=-1;
	m_LastScanf=sscanf(iStr,"%d;%d",&IdWS,&IdDB);
	int DBNum=IdWS*N_DAODATABASE_COUNT+IdDB;
	if (IdWS>=0 && IdWS<=N_DAOWORKSPACE_ARR && gpws[IdWS]!=NULL && gpws[IdWS]->IsOpen()
		&& IdDB>=0 && IdDB<=N_DAODATABASE_COUNT && gpdb[DBNum]!=NULL && gpdb[DBNum]->GPIsOpen())
	{
		const char *posQDef=strchr(iStr,';');
		if (posQDef!=NULL) posQDef=strchr(++posQDef,';');
		if (posQDef++==NULL) posQDef="";
		ret=gpdb[DBNum]->OpenGPQDef(posQDef);
	}

	char retStr[100];
	sprintf(retStr,"%d\x7F%d\x7F%d",IdWS,IdDB,ret);
	SendRet(retStr,0);
	return ret;
}

int GPCDAOWorkspace::OpenGPTDef(const char *iStr)
{
	int IdWS=-1,IdDB=-1;
	int ret=-1;
	m_LastScanf=sscanf(iStr,"%d;%d",&IdWS,&IdDB);
	int DBNum=IdWS*N_DAODATABASE_COUNT+IdDB;
	if (IdWS>=0 && IdWS<=N_DAOWORKSPACE_ARR && gpws[IdWS]!=NULL && gpws[IdWS]->IsOpen()
		&& IdDB>=0 && IdDB<=N_DAODATABASE_COUNT && gpdb[DBNum]!=NULL && gpdb[DBNum]->GPIsOpen())
	{
		const char *posTDef=strchr(iStr,';');
		if (posTDef!=NULL) posTDef=strchr(++posTDef,';');
		if (posTDef++==NULL) posTDef="";
		ret=gpdb[DBNum]->OpenGPTDef(posTDef);
	}

	char retStr[100];
	sprintf(retStr,"%d\x7F%d\x7F%d",IdWS,IdDB,ret);
	SendRet(retStr,0);
	return ret;

}

int GPCDAOWorkspace::CreateGPQDef(const char *iStr)
{
	int IdWS=-1,IdDB=-1;
	int ret=-1;
	m_LastScanf=sscanf(iStr,"%d;%d",&IdWS,&IdDB);
	int DBNum=IdWS*N_DAODATABASE_COUNT+IdDB;
	if (IdWS>=0 && IdWS<=N_DAOWORKSPACE_ARR && gpws[IdWS]!=NULL && gpws[IdWS]->IsOpen()
		&& IdDB>=0 && IdDB<=N_DAODATABASE_COUNT && gpdb[DBNum]!=NULL && gpdb[DBNum]->GPIsOpen())
	{
		const char *posQDef=strchr(iStr,';');
		if (posQDef!=NULL) posQDef=strchr(++posQDef,';');
		if (posQDef++==NULL) posQDef="";
		ret=gpdb[DBNum]->CreateGPQDef(posQDef);
	}

	char retStr[100];
	sprintf(retStr,"%d\x7F%d\x7F%d",IdWS,IdDB,ret);
	SendRet(retStr,0);
	return ret;
}

int GPCDAOWorkspace::CreateGPTDef(const char *iStr)
{
	int IdWS=-1,IdDB=-1;
	int ret=-1;
	m_LastScanf=sscanf(iStr,"%d;%d",&IdWS,&IdDB);
	int DBNum=IdWS*N_DAODATABASE_COUNT+IdDB;
	if (IdWS>=0 && IdWS<=N_DAOWORKSPACE_ARR && gpws[IdWS]!=NULL && gpws[IdWS]->IsOpen()
		&& IdDB>=0 && IdDB<=N_DAODATABASE_COUNT && gpdb[DBNum]!=NULL && gpdb[DBNum]->GPIsOpen())
	{
		const char *posTDef=strchr(iStr,';');
		if (posTDef!=NULL) posTDef=strchr(++posTDef,';');
		if (posTDef++==NULL) posTDef="";
		ret=gpdb[DBNum]->CreateGPTDef(posTDef);
	}

	char retStr[100];
	sprintf(retStr,"%d\x7F%d\x7F%d",IdWS,IdDB,ret);
	SendRet(retStr,0);
	return ret;

}
