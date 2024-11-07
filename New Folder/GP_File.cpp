// GP_File.cpp: implementation of the GP_File class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GP_File.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GP_File::GP_File()
{
	ConvON=0;
	LastPos=0;
	prtflg=0;
	pgs='4';
}

GP_File::~GP_File()
{
	if ((ConvON&512)!=0)
	{
		try
		{
		Write("\r\n\\par ",7);
		if (prtflg!=0)	Write("\\sect ",6);
		Write("}}",2);
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","1");
		}
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_FILES.dwClose++;
}

BOOL GP_File::GPOpenFile(char *Init, char *result)
{
	UINT aModeUINT[8]={CFile::modeCreate,CFile::modeNoTruncate,CFile::modeRead,CFile::modeReadWrite,CFile::modeWrite,CFile::modeNoInherit,CFile::typeText,CFile::typeBinary,};
	char *aModeName[8]={"MODECREATE|","MODENOTRUNCATE|","MODEREAD|","MODEREADWRITE|","MODEWRITE|","MODENOINHERIT|","TYPETEXT|","TYPEBINARY|",};
	UINT aShareUINT[5]={CFile::shareDenyNone,CFile::shareDenyRead,CFile::shareDenyWrite,CFile::shareExclusive,};
	char *aShareName[5]={"SHAREDENYNONE|","SHAREDENYREAD|","SHAREDENYWRITE|","SHAREEXCLUSIVE|",};

	UINT Mode=0;
	char *Name="";
	char *tmpInit=new char [(int)strlen(Init)+25];
	strcpy(tmpInit,Init);

	char *pos=tmpInit;
	BOOL Mess=FALSE;

	int i;
	for(i=0;i<5;i++)
	{
		char *pos2=NULL,str[250];*str=0;
		BOOL flg=FALSE;
		int j;

		if (pos!=NULL)
		{
			pos2=strchr(pos+1,',');
			if (pos2!=NULL) *(pos2++)=0;
			strcpy(str,pos);
		}
		switch(i)
		{
		case 0: //mode
			strcat(str,"|");
			_strupr(str);
			if (pos!=NULL)
				for(j=0;j<8;j++)
					if (strstr(str,aModeName[j])!=NULL) {Mode|=aModeUINT[j];flg=TRUE;}

			if (pos==NULL || flg==FALSE) Mode|=CFile::modeRead;
			break;
		case 1: //Share
			strcat(str,"|");
			_strupr(str);
			if (pos!=NULL)
				for(j=0;j<4;j++)
					if (strstr(str,aShareName[j])!=NULL) {Mode|=aShareUINT[j];flg=TRUE;}

			if (pos==NULL || flg==FALSE) Mode|=CFile::shareDenyNone;
			break;
		case 2:
			if (pos!=NULL) ConvON=atoi(str);
			break;
		case 3:
			if (pos!=NULL) Mess=atoi(str);
			break;
		case 4:
			if (pos!=NULL) Name=pos;
			break;
		}
		if (pos2!=NULL) pos=pos2;
	}


	CFileException pError;
	if (!Open(Name,Mode,&pError))
	{
		char Err[1000];
		sprintf(Err,"%d",pError.m_cause);
		*result=0;
		if (Mess==TRUE) AfxMessageBox(Err);
		GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","2");
	}
	else
		if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_FILES.dwOpen++;

	if ((ConvON&512)!=0)
	{
		char *tmpstr=
"{\\rtf1\\ansi \\deff4\\deflang1033{\\fonttbl{\\f4\\froman\\fcharset204\\fprq2 Times New Roman Cyr;}{\\f5\\fswiss\\fcharset204\\fprq2 Arial Cyr;}{\\f11\\fmodern\\fcharset204\\fprq1 Courier New Cyr;}{\\f32\\fmodern\\fcharset0\\fprq1 Courier New;} \r\n{\\f39\\fmodern\\fcharset2\\fprq1 MS LineDraw;}}{\\colortbl;\\red0\\green0\\blue0;\\red0\\green0\\blue255;\\red0\\green255\\blue255;\\red0\\green255\\blue0;\\red255\\green0\\blue255;\\red255\\green0\\blue0;\\red255\\green255\\blue0;\\red255\\green255\\blue255;\\red0\\green0\\blue128; \r\n\\red0\\green128\\blue128;\\red0\\green128\\blue0;\\red128\\green0\\blue128;\\red128\\green0\\blue0;\\red128\\green128\\blue0;\\red128\\green128\\blue128;\\red192\\green192\\blue192;}{\\stylesheet{\\widctlpar \\f4\\fs20\\lang1049 \\snext0 Normal;}{\\*\\cs10 \\additive \r\nDefault Paragraph Font;}}{\\info{\\author \\'cf\\'f0\\'ff\\'ec\\'ee\\'e2  (87-94)}{\\operator \\'cf\\'f0\\'ff\\'ec\\'ee\\'e2  (87-94)}{\\creatim\\yr1998\\mo5\\dy7\\hr17\\min30}{\\revtim\\yr1998\\mo5\\dy7\\hr17\\min31}{\\version1}{\\edmins1}{\\nofpages1}{\\nofwords5}{\\nofchars30} \r\n{\\*\\company MINFIN}{\\vern57443}}\\paperw11906\\paperh16838 \\widowctrl\\ftnbj\\aenddoc\\makebackup\\formshade \\fet0\\sectd \\linex0\\headery709\\footery709\\colsx709\\endnhere {\\*\\pnseclvl1\\pnucrm\\pnstart1\\pnindent720\\pnhang{\\pntxta .}}{\\*\\pnseclvl2 \r\n\\pnucltr\\pnstart1\\pnindent720\\pnhang{\\pntxta .}}{\\*\\pnseclvl3\\pndec\\pnstart1\\pnindent720\\pnhang{\\pntxta .}}{\\*\\pnseclvl4\\pnlcltr\\pnstart1\\pnindent720\\pnhang{\\pntxta )}}{\\*\\pnseclvl5\\pndec\\pnstart1\\pnindent720\\pnhang{\\pntxtb (}{\\pntxta )}}{\\*\\pnseclvl6 \r\n\\pnlcltr\\pnstart1\\pnindent720\\pnhang{\\pntxtb (}{\\pntxta )}}{\\*\\pnseclvl7\\pnlcrm\\pnstart1\\pnindent720\\pnhang{\\pntxtb (}{\\pntxta )}}{\\*\\pnseclvl8\\pnlcltr\\pnstart1\\pnindent720\\pnhang{\\pntxtb (}{\\pntxta )}}{\\*\\pnseclvl9\\pnlcrm\\pnstart1\\pnindent720\\pnhang \r\n{\\pntxtb (}{\\pntxta )}}\\pard\\plain \\widctlpar \\f4\\fs20\\lang1049 {\\f11\\fs24\\lang1033 \r\n";
		prtflg=0;
		pgs='4';
		try
		{
		Write(tmpstr,(int)strlen(tmpstr));
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","3");
		}
	}

	delete[] tmpInit;
	LastPos=0;
	return FALSE;
}

int GP_File::GPGetChar(char *str, UINT nChar)
{
	*str=0;
	GPGetPosition(&LastPos);
	unsigned char tmp[10];
	char *pos=str;
	if (nChar==0) nChar=1;
	UINT i;
	try
	{
	for(i=0;i<nChar;i++)
		if (Read(tmp,1)!=0)
		{
			pos+=sprintf(pos,"%3.3d",tmp[0]);
			if (GPC.DlgStatistics) GPC.DlgStatistics->SAddFReadCount(1);
		}
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","5");
	}

	if (i!=nChar) strcat(pos,"EOF");

	return i;
}

int GP_File::GPPutChar(int iCh)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SAddFWriteCount(1);
	char str[10];*str=(char)iCh;
	try
	{
		GPGetPosition(&LastPos);
		Write(str,1);
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","6");
	}

	return 0;
}

int GP_File::GPGetStr(char **str, UINT nstr)
{
	char blk[15];
	UINT len=0,sme=0,j=0;
	try
	{
		GPGetPosition(&LastPos);
		__int64 pos=0;
		GPGetPosition(&pos);
		while(Read(blk,1)==1 && (!(ConvON&1024) || *blk!=26))
		{
			sme=0;
			if (*blk==10 || *blk==13 || *blk==0)
			{
				blk[1]=100;blk[2]=100;
				int nr=Read(blk+1,2);
				if ((blk[0]==10 && blk[1]==13 && blk[2]==0)
					|| (blk[0]==13 && blk[1]==10 && blk[2]==0)
					|| (blk[0]==10 && blk[1]==10 && blk[2]==13)
					|| (blk[0]==13 && blk[1]==13 && blk[2]==10)
					) sme=3;
				else
				if ((blk[0]==10 && blk[1]==13)
					||(blk[0]==13 && blk[1]==10)
					|| (blk[0]==10 && blk[1]==0)
					|| (blk[0]==13 && blk[1]==0)) {sme=2;if (nr==2) GPSeek(-1,FILE_CURRENT);}
				else
				 {sme=1;if (nr!=0) GPSeek(-2,FILE_CURRENT);}
				if (++j==nstr) break;
				len+=sme;
			}
			else	len++;
		}

		GPSeek(pos,FILE_BEGIN);
		*str=new char [len+nstr+100];
		if (len==0 && sme==0) strcpy(*str,"<(EOF)>");
		else
		{
			if (GPC.DlgStatistics) GPC.DlgStatistics->SAddFReadCount(len);
			Read(*str,len);
			(*str)[len]=0;
			if ((ConvON&1)==1) AnsiToDos(*str,0);
			UINT i;
			for(i=0;i<len;i++)
				if ((*str)[i]==255) (*str)[i]='@';
				else
				if ((*str)[i]==127) (*str)[i]=254;

			(*str)[len]=0;

			if ((ConvON&1024))
			{
				char *psrc=*str;
				char *pdst=*str;
				while(*psrc!=26 && (*(pdst++)=*(psrc++)));
				*pdst=0;
			}


			for(i=0,j=0;i<len;i++,j++)
				if (
					((*str)[i]==10 && (*str)[i+1]==13 && (*str)[i+2]==0)
					|| ((*str)[i]==13 && (*str)[i+1]==10 && (*str)[i+2]==0)
					|| ((*str)[i]==10 && (*str)[i+1]==10 && (*str)[i+2]==13)
					|| ((*str)[i]==13 && (*str)[i+1]==13 && (*str)[i+2]==10)
					)
				{(*str)[j]=254;i+=2;}
				else
				if (((*str)[i]==10 && (*str)[i+1]==13)
					||((*str)[i]==13 && (*str)[i+1]==10)
					|| ((*str)[i]==10 && (*str)[i+1]==0)
					|| ((*str)[i]==13 && (*str)[i+1]==0)) {(*str)[j]=254;i++;}
				else
				if ((*str)[i]==10 || (*str)[i]==13 || (*str)[i]==0) (*str)[j]=254;
				else (*str)[j]=(*str)[i];

			(*str)[j]=0;
			if (j!=0 && (*str)[j-1]==254) (*str)[j-1]=0;

			if (sme!=0) Read(blk,sme);
		}
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","7");
	}

	return len;
}

int GP_File::GPPutStr(char *str)
{
	try
	{
		GPGetPosition(&LastPos);
		if ((ConvON&1024))
		{
			char *psrc=str;
			char *pdst=str;
			while((*(pdst)=*(psrc++))) 
				if (*pdst!=26) pdst++;
		}


		if ((ConvON&512))
		{
	//		DosToAnsi(str);
			char *oStr=NULL;
			ConvertToPrintd(str,&oStr,prtflg,pgs);
			int len=(int)strlen(oStr);
			try
			{
				Write(oStr,len);
				if (GPC.DlgStatistics) GPC.DlgStatistics->SAddFWriteCount(len);
			}
			catch(...)
			{
				GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","9");
			}
			if (oStr!=NULL) delete[] oStr;
		}
		else
		{
			int len=(int)strlen(str);
			if ((ConvON&1)==1) DosToAnsi(str);
			Write(str,len);
			if (GPC.DlgStatistics) GPC.DlgStatistics->SAddFWriteCount(len);
		}
		if (GPC.DlgStatistics) GPC.DlgStatistics->SAddFWriteCount(2);
		Write("\r\n",2);
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","8");
	}
	return 0;
}

UINT GP_File::GPReadBlock(char *blk, int len)
{
	UINT i=0,j=0,n=0;
	try
	{
		GPGetPosition(&LastPos);
		n=Read(blk+len,len);
		if (GPC.DlgStatistics) GPC.DlgStatistics->SAddFReadCount(n);
		for(i=0,j=len;j<n+len;i++,j++)
		{
			if ((ConvON&1024) && blk[j]==26)
			{
				i--;
				j=n+len;
			}
			else
			if ((ConvON&4)==4)
			{
				if ((blk[i]=(char)(blk[j]/16+'0'))>'9') blk[i]+=7;
				if ((blk[++i]=(char)((blk[j]%16)+'0'))>'9') blk[i]+=7;
			}
			else
			if ((ConvON&2)==2 && (blk[j]==10 || blk[j]==13 || blk[j]==0))
			{
				if ((blk[j]==10 && blk[j+1]==13 && blk[j+2]==0)
					|| (blk[j]==13 && blk[j+1]==10 && blk[j+2]==0)) {blk[i]=127;j+=2;}
				else
				if ((blk[j]==10 && blk[j+1]==13)
					||(blk[j]==13 && blk[j+1]==10)
					|| (blk[j]==10 && blk[j+1]==0)
					|| (blk[j]==13 && blk[j+1]==0)) {blk[i]=127;j++;}
				else blk[i]=127;
			}
			else
			switch(blk[j])
			{
				case 0:	case 1:	case 2:	case 3:	case 4:	case 5:	case 6:
							blk[i++]='\\';	blk[i]=(char)('0'+blk[j]); break;
				case 7:		blk[i++]='\\';	blk[i]='a';		break;
				case 8:		blk[i++]='\\';	blk[i]='b';		break;
				case 9:		if ((ConvON&16)==16) {blk[i++]='\\';	blk[i]='t';}
							else
								if ((ConvON&256)==256) {blk[i++]=' ';blk[i++]=' ';blk[i++]=' ';blk[i]=' ';}
								else
									blk[i]=blk[j];
							break;
				case 10:	blk[i++]='\\';	blk[i]='n';		break;
				case 11:	blk[i++]='\\';	blk[i]='v';		break;
				case 12:	if ((ConvON&32)==32) {blk[i++]='\\';	blk[i]='f';}
							else blk[i]=blk[j];
							break;
				case 13:	blk[i++]='\\';	blk[i]='r';		break;
				case 27:	if ((ConvON&64)==64) {blk[i++]='\\';	blk[i]='e';}
							else blk[i]=blk[j];
							break;
				case '\\':	if ((ConvON&128)==128) {blk[i++]='\\';	blk[i]='\\';}
							else blk[i]=blk[j];
							break;
				case 127:	if ((ConvON&8)==8) {blk[i++]='\\';	blk[i]='q';}
							else blk[i]=blk[j];
							break;
				case 250:	if ((ConvON&8)==8) {blk[i++]='\\';	blk[i]='g';}
							else blk[i]=blk[j];
							break;
				case 251:	if ((ConvON&8)==8) {blk[i++]='\\';	blk[i]='h';}
							else blk[i]=blk[j];
							break;
				case 252:	if ((ConvON&8)==8) {blk[i++]='\\';	blk[i]='i';}
							else blk[i]=blk[j];
							break;
				case 253:	if ((ConvON&8)==8) {blk[i++]='\\';	blk[i]='j';}
							else blk[i]=blk[j];
							break;
				case 254:	if ((ConvON&8)==8) {blk[i++]='\\';	blk[i]='k';}
							else blk[i]=blk[j];
							break;
				case 255:	if ((ConvON&1)!=1) {blk[i++]='\\';	blk[i]='l';}
							else blk[i]=blk[j];
							break;
				default: blk[i]=blk[j];break;
			}
		}

		blk[i]=0;
		if ((ConvON&1)==1) AnsiToDos(blk,0);
		else
			for(i=0;blk[i]!=0;i++)
				if (blk[i]==127) blk[i]=254;
				else
					if (blk[i]==255) blk[i]=254;
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","10");
	}
	return i*0x10000+n;
}

int GP_File::GPWriteBlock(const char *blk)
{
	UINT n=(int)strlen(blk);
	try
	{
		GPGetPosition(&LastPos);
		if ((ConvON&512)!=0)
		{
			char *oStr=NULL;
	//		DosToAnsi(blk);
			ConvertToPrintd(blk,&oStr,prtflg, pgs);
			int len=(int)strlen(oStr);
			if (GPC.DlgStatistics) GPC.DlgStatistics->SAddFWriteCount(len);
			Write(oStr,len);
			if (oStr!=NULL) delete[] oStr;
		}
		else
		{
			UINT i,j;

			if ((ConvON&4)==4)
			{
				char *blk333=new char [(int)strlen(blk)+2];
				strcpy(blk333,blk);
				int cc;
				try
				{
					for(i=0,j=0;i<n;i++,j++)
					{
						cc=blk333[i];
						if (cc>='0' && cc<='9') blk333[j]=(char)((cc-'0')*16);
						else
						if (cc>='A' && cc<='F') blk333[j]=(char)((cc-'A'+10)*16);
						else			{blk333[j]=(char)cc; continue;}

						cc=blk333[++i];
						if (cc>='0' && cc<='9') blk333[j]=(char)(blk333[j]+(char)(cc-'0'));
						else
						if (cc>='A' && cc<='F') blk333[j]=(char)(blk333[j]+(char)(cc-'A'+10));
					}
					Write(blk333,j);
					if (GPC.DlgStatistics) GPC.DlgStatistics->SAddFWriteCount(j);
				}
				catch(...)
				{
					GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","14");
				}
				delete[] blk333;
			}
			else
			{
				char *blk333=new char [(int)strlen(blk)+2];
				strcpy(blk333,blk);
				if ((ConvON&1)==1) DosToAnsi(blk333);
				/*
				IF INDEX(ModeShare,"ANSIDOS|",1) THEN FileVar<5>+=1
				IF INDEX(ModeShare,"CRAM|",1) THEN FileVar<5>+=2
				IF INDEX(ModeShare,"DECHEX|",1) THEN FileVar<5>+=4
				IF INDEX(ModeShare,"AMVM|",1) THEN FileVar<5>+=8
				IF INDEX(ModeShare,"TAB|",1) THEN FileVar<5>+=16
				IF INDEX(ModeShare,"FF|",1) THEN FileVar<5>+=32
				IF INDEX(ModeShare,"ESC|",1) THEN FileVar<5>+=64
				IF INDEX(ModeShare,"BSLASH|",1) THEN FileVar<5>+=128
				IF INDEX(ModeShare,"TAB4|",1) THEN FileVar<5>+=256
				IF INDEX(ModeShare,"RF|",1) THEN FileVar<5>+=512
				IF INDEX(ModeShare,"SKIPEOF|",1) THEN FileVar<5>+=1024
				IF INDEX(ModeShare,"Message|",1) THEN FileVar<6>=1
				*/
				try
				{
					char tmp[20];
					for(i=0;i<n;i++)
					{
						if (!(ConvON&1024) || blk333[i]!=26)
						{
							if ((ConvON&2)==2 && blk333[i]==127)
							{
								Write("\x0D\x0A",2);
								if (GPC.DlgStatistics) GPC.DlgStatistics->SAddFWriteCount(2);
							}
							else
							if ((ConvON&128)==128 && blk333[i]=='\\')
							{
								switch(blk333[++i])
								{
								case '0':	case '1':	case '2':	case '3':	case '4':	case '5':	case '6':
											*tmp=(char)(blk333[i]-'0'); break;
								case 'a':	*tmp=7;		break;
								case 'b':	*tmp=8;		break;
								case 't':	*tmp=9;		break;
								case 'n':	*tmp=10;		break;
								case 'v':	*tmp=11;		break;
								case 'f':	*tmp=12;		break;
								case 'r':	*tmp=13;		break;
								case 'e':	*tmp=27;		break;
								case '\\':	*tmp='\\';	break;
								case 'q':	*tmp=127;		break;
								case 'g':	*tmp=250;		break;
								case 'h':	*tmp=251;		break;
								case 'i':	*tmp=252;		break;
								case 'j':	*tmp=253;		break;
								case 'k':	*tmp=254;		break;
								case 'l':	*tmp=255;		break;
								default: Write(blk333+i-1,2);continue;
								}
								Write(tmp,1);
								if (GPC.DlgStatistics) GPC.DlgStatistics->SAddFWriteCount(1);
							}
							else
							{
								if (!(ConvON&1024) || blk333[i]!=26)
								{
									Write(blk333+i,1);
									if (GPC.DlgStatistics) GPC.DlgStatistics->SAddFWriteCount(1);
								}
							}
						}
					}
				}
				catch(...)
				{
					GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","12");
				}
				delete[] blk333;
			}
		}
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","11");
	}
	return n;
}

BOOL GP_File::GPSeek(__int64 param1, DWORD param2)
{
	BOOL ret=FALSE;
	try
	{
		#ifdef W_95
			LARGE_INTEGER li;
			li.QuadPart=param1;
			if (m_hFile) ret=li.LowPart=SetFilePointer((void *)m_hFile,li.LowPart,&(li.HighPart),param2);
		#else
			#ifdef W_NT
				LARGE_INTEGER li;
				li.QuadPart=param1;
				if (m_hFile) ret=li.LowPart=SetFilePointer((void *)m_hFile,li.LowPart,&(li.HighPart),param2);
			#else
				#ifdef W_98
					LARGE_INTEGER li;
					li.QuadPart=param1;
					if (m_hFile) ret=li.LowPart=SetFilePointer((void *)m_hFile,li.LowPart,&(li.HighPart),param2);
				#else
					GPGetPosition(&LastPos);
					LARGE_INTEGER liNewFilePointer={0};
					if (param2!=FILE_BEGIN && param2!=FILE_CURRENT && param2!=FILE_END) param2=FILE_BEGIN;

					ret=(m_hFile)?SetFilePointerEx((void *)m_hFile,*((PLARGE_INTEGER)(&param1)),(PLARGE_INTEGER)&liNewFilePointer,param2):FALSE;
				#endif
			#endif
		#endif
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","15");
	}
	return ret;
}

int GP_File::GPSeekToBegin()
{
	GPGetPosition(&LastPos);
	SeekToBegin();
	return 0;
}

__int64 GP_File::GPSeekToEnd()
{
	GPGetPosition(&LastPos);
	return SeekToEnd();
}

int GP_File::GPFlush()
{
	try
	{
		Flush();
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","19");
	}
	return 0;
}

BOOL GP_File::GPGetLength(__int64 * position)
{
	BOOL ret=FALSE;
	try
	{
		#ifdef W_95
			LARGE_INTEGER li;
			li.QuadPart=0;
			if (m_hFile) 
			{
				li.LowPart=GetFileSize((void *)m_hFile,(unsigned long *)&(li.HighPart));
				ret=TRUE;
			}
			*position=li.QuadPart;
		#else
			#ifdef W_NT
				LARGE_INTEGER li;
				li.QuadPart=0;
				if (m_hFile)
				{
					li.LowPart=GetFileSize((void *)m_hFile,(unsigned long *)&(li.HighPart));
					*position=li.QuadPart;
					ret=TRUE;
				}
			#else
				#ifdef W_98
					LARGE_INTEGER li;
					li.QuadPart=0;
					if (m_hFile)
					{
						li.LowPart=GetFileSize((void *)m_hFile,(unsigned long *)&(li.HighPart));
						*position=li.QuadPart;
						ret=TRUE;
					}
				#else
					if (m_hFile) ret=GetFileSizeEx((void *)m_hFile,(PLARGE_INTEGER)position);
				#endif
			#endif
		#endif
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","17");
	}
	return ret;
}

int GP_File::GPSetLength(__int64 param1)
{
	try
	{
		if (m_hFile)
		{
			__int64 liCurPosition=0;
			do
			{
				GPGetLength(&liCurPosition);
				if (param1<liCurPosition)
				{
					GPSeek(param1,FILE_CURRENT);
					SetEndOfFile((void *)m_hFile);
				}
				else
				if (param1>liCurPosition)
				{
					GPSeekToEnd();
					Write(this,0x1000);
				}
			}while(param1>liCurPosition);

		}
		GPGetPosition(&LastPos);
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","19");
	}
	return 0;
}

BOOL GP_File::GPGetPosition(__int64 * position)
{
	BOOL ret=FALSE;
	try
	{
		#ifdef W_95
			LARGE_INTEGER li;
			li.QuadPart=0;
			if (m_hFile) 
			{
				li.LowPart=SetFilePointer((void *)m_hFile,li.LowPart,&(li.HighPart),FILE_CURRENT);
				*position=li.QuadPart;
				ret=TRUE;
			}
		#else
			#ifdef W_NT
				LARGE_INTEGER li;
				li.QuadPart=0;
				if (m_hFile) 
				{
					li.LowPart=SetFilePointer((void *)m_hFile,li.LowPart,&(li.HighPart),FILE_CURRENT);
					*position=li.QuadPart;
					ret=TRUE;
				}
			#else
				#ifdef W_98
					LARGE_INTEGER li;
					li.QuadPart=0;
					if (m_hFile) 
					{
						li.LowPart=SetFilePointer((void *)m_hFile,li.LowPart,&(li.HighPart),FILE_CURRENT);
						*position=li.QuadPart;
						ret=TRUE;
					}
				#else
					LARGE_INTEGER liDistanceToMove={0};
					ret=(m_hFile)?SetFilePointerEx((void *)m_hFile,liDistanceToMove,(PLARGE_INTEGER)position,FILE_CURRENT):FALSE;
				#endif
			#endif
		#endif
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","16");
	}
	return ret;
}

int GP_File::GPGetStatus(char *str)
{
	CFileStatus sta;
	try
	{
		GetStatus(sta);

		sprintf(str,"%I64d\x7F%I64d\x7F%2.2d\x7F%2.2d\x7F%2.2d\x7F%2.2d\x7F%2.2d\x7F%4.4d\x7F%I64d\x7F%2.2d\x7F%2.2d\x7F%2.2d\x7F%2.2d\x7F%2.2d\x7F%4.4d\x7F%I64d\x7F%2.2d\x7F%2.2d\x7F%2.2d\x7F%2.2d\x7F%2.2d\x7F%4.4d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d",
				sta.m_size,
	sta.m_ctime.GetTime(), sta.m_ctime.GetSecond(), sta.m_ctime.GetMinute(), sta.m_ctime.GetHour(), sta.m_ctime.GetDay(), sta.m_ctime.GetMonth(),sta.m_ctime.GetYear(),
	sta.m_mtime.GetTime(), sta.m_mtime.GetSecond(), sta.m_mtime.GetMinute(), sta.m_mtime.GetHour(), sta.m_mtime.GetDay(), sta.m_mtime.GetMonth(),sta.m_mtime.GetYear(),
	sta.m_atime.GetTime(), sta.m_atime.GetSecond(), sta.m_atime.GetMinute(), sta.m_atime.GetHour(), sta.m_atime.GetDay(), sta.m_atime.GetMonth(),sta.m_atime.GetYear(),
	 ((sta.m_attribute&0x01)==0x01),
	 ((sta.m_attribute&0x10)==0x10),
	 ((sta.m_attribute&0x08)==0x08),
	 ((sta.m_attribute&0x04)==0x04),
	 ((sta.m_attribute&0x02)==0x02),
	 ((sta.m_attribute&0x20)==0x20)
	 );
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","20");
	}

	return 0;
}

int GP_File::GPLockRange(int param1, int param2)
{
	try
	{
		if (param1<=param2 && param1>=0) LockRange( param1, param2);
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","21");
	}
	return 0;
}

int GP_File::GPUnLockRange(int param1, int param2)
{
	try
	{
		if (param1<=param2 && param1>=0) UnlockRange( param1, param2);
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","22");
	}
	return 0;
}

int GP_File::GPPosRollBack()
{
	int ret=0;
	try
	{
		__int64 tmp=LastPos;
		GPGetPosition(&LastPos);
		ret=GPSeek(tmp,FILE_BEGIN);
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","23");
	}
	return ret;
}

int GP_File::GPGetBlocksInfo(char *str, int Len)
{
	try
	{
		*str=0;
		__int64 tmpLastPos=0;
		GPGetPosition(&tmpLastPos);
		if (Len<32 || Len>262144) Len=2048;
		SeekToBegin();
		int n=(int)(GetLength()/Len+1);
		char *blk=new char [Len*2+10];
		sprintf(str,"%d",n);
		int i;
		for(i=0;i<n;i++)
		{
			UINT ll=0;
			try
			{
				ll=GPReadBlock(blk, Len);
			}
			catch(...)
			{
				GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","25");
			}
			UINT lread= (ll&0xFFFF);
			UINT lblk = (ll/0x10000);
			int summ=0;
			// данный алгоритм из-за убогости битовых операций в PICK  :-(
			// надо насто€щий CRC
			UINT j;
			for(j=0;j<lblk;j++) summ+=((j%32)+1)*(blk[j]+3);

			sprintf(str+(int)strlen(str),"%c%d%c%d%c%d",254,lread,253,lblk,253,summ);
		}

		delete[] blk;

		GPSeek(LastPos=tmpLastPos,FILE_BEGIN);
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","24");
	}

return 0;
}


__int64 GP_File::GPFindPlace(char *str)
{
	char *blk=new char [0x8000];
	UINT ll=0;
	__int64 tmpLastPos=0;
	try
	{
		GPGetPosition(&tmpLastPos);
		int lenstr=(int)strlen(str);
		if (lenstr>0x2000) lenstr=0x2000;

		do
		{
			char *pos;
			ll=GPReadBlock(blk, 0x4000);
			if ((pos=strstr(blk,str))!=NULL)
			{
				if (pos==str) {GPSeek(tmpLastPos,FILE_BEGIN);break;}
				GPSeek(tmpLastPos+=(pos-str-1)/2+1,FILE_BEGIN);
			}
			else
			if (ll!=5000) ll=0;
				else GPSeek(tmpLastPos+=0x3FFF-lenstr,FILE_BEGIN);
		}
		while(ll>0);
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","26");
	}
	delete[] blk;

	return ll==0?-1:tmpLastPos;
}

void GP_File::ConvertToPrintd(const char *iStr, char **oStr, int & pr, int & pg)
{
	int c;
	if (iStr!=NULL)
	{
		*oStr=new char [(int)strlen(iStr)*5+500];
		char *curpos=*oStr;
		*curpos=0;
		try
		{
			while((c=*(iStr++))!=0)
			{
				if (c==GPC.DelimiterIn1)
					curpos+=sprintf(curpos,"\n\\par ");
				else
				switch(c)
				{
				case 127:
				case '\n':	curpos+=sprintf(curpos,"\n\\par ");
				case '\r':  break;
				case '\f':	curpos+=sprintf(curpos,"\n\\page "); break;
				case '\\':  c=*(iStr++);
							if (c!='p' && c!='l' && c!='a') curpos+=sprintf(curpos,"\\");
							else
							if (c=='a')
							{
								int c1=*(iStr++);
								if (c1!='4' && c1!='3') {curpos+=sprintf(curpos,"\\%c",c);c=c1;}
								else
								{
									int c2=*(iStr++);
									if (c2!=' ') {curpos+=sprintf(curpos,"\\%c%c",c,c1);c=c2;}
									else 	{	pg=c1; continue; }
								}


							}
							else
							{
							int c1=*(iStr++);
							if (c1!='r' && c1!='n') {curpos+=sprintf(curpos,"\\%c",c);c=c1;}
							else
								{
								int c2=*(iStr++);
								if (c2!='t' && c2!='d') {curpos+=sprintf(curpos,"\\%c%c",c,c1);c=c2;}
								else
									{
									char *page[12]=
									{
										"\\lndscpsxn\\pghsxn11907\\pgwsxn16840\\margtsxn1000\\margbsxn600\\marglsxn1000\\margrsxn600\\headery600\\footery600\\colsx600\\endnhere ",
												   "\\pgwsxn11907\\pghsxn16840\\marglsxn1000\\margrsxn600\\margtsxn1000\\margbsxn600\\headery600\\footery600\\colsx600\\endnhere ",
										"\\lndscpsxn\\pgwsxn23814\\pghsxn16840\\marglsxn1000\\margrsxn600\\margtsxn1000\\margbsxn600\\headery600\\footery600\\colsx600\\endnhere ",
												   "\\pghsxn23814\\pgwsxn16840\\margtsxn1000\\margbsxn600\\marglsxn1000\\margrsxn600\\headery600\\footery600\\colsx600\\endnhere ",
												   "","","","","","","","",
									};

									int c3=*(iStr++);
									if (c3!=' ') {curpos+=sprintf(curpos,"\\%c%c%c",c,c1,c2);c=c3;}
									if (pr!=0) curpos+=sprintf(curpos,"\\sect ");

									if (c2=='t') curpos+=sprintf(curpos,"\\sectd %s",page[('4'-pg)*2+1]);
										else	 curpos+=sprintf(curpos,"\\sectd %s",page[('4'-pg)*2]);
									pr=1;
									continue;

									}
								}
							}


				default:
							if((c>='А' && c<='Я') || (c>='†' && c<='ѓ')) c+=64;
							else
								if (c>='а' && c<='п') c+=16;
								else
								if ((c>=179 && c<=195)||(c>=197 && c<=204)
									|| (c>=206&&c<=223) || c==196 ||c==205)
								{
									char str[2000];
									int n=0;
								do
								{
									str[n++]=(char)c;
									c=*(iStr++);
								}
								while((c>=179 && c<=195)||(c>=197 && c<=204) || (c>=206&&c<=223) || c==196 ||c==205);
								str[n]=0;
								curpos+=sprintf(curpos,"{\\f39 ");
								int f;
								for(f=0;f<n;f++) curpos+=sprintf(curpos,"\\'%2.2x",str[f]);
								curpos+=sprintf(curpos,"}");

								if (c!=0) iStr--;
								continue;
								}

					if (c<='z') curpos+=sprintf(curpos,"%c",c);
					else		curpos+=sprintf(curpos,"\\'%2.2x",c);
					break;
				}
			}
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("CGP_Term", "GP_File ","27");
		}
		*curpos=0;
	}
}
