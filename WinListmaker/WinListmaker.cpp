// WinListmaker.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "..\ListMaker.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	CListMaker m_LM;
	char ListsPath[250];
	strcpy(ListsPath,"ListMaker");
	char *argv[10];
	char *tmparg=new char [(int)strlen(lpCmdLine)+10];
	strcpy(tmparg,lpCmdLine);
	int argc=1;
	*argv=tmparg;
	char *posarg=tmparg;
	while(*posarg)
	{
		while(*posarg && *posarg!=' ') posarg++;
		if (*posarg)
		{
			*posarg=0;
			while(*posarg && *posarg==' ') posarg++;
		}
		if (*posarg) argv[argc++]=posarg;
	}


	if (argc>1 && argv[1]!=0 && *argv[1]!=0)
	{
		char comname[1000];
		char IdPort[500];
		FILE *src;
		strncpy(IdPort,argv[1],250);IdPort[250]=0;
		if (argc>2 && argv[2]!=0 && *argv[2]!=0) 
			strcpy(ListsPath,argv[2]);
		sprintf(comname,"%s/%scommand",ListsPath,IdPort);

		src=fopen(comname,"rt");
		if (src!=NULL)
		{
			long fLen;
			char *buff,*pos;
			fseek(src,0,SEEK_END);
			fLen=ftell(src);
			rewind(src);
			buff=new char [fLen+10];
			buff[fLen]=0;
			if (buff!=NULL)
			{
				fread(buff,1,fLen, src);
				pos=buff;
				while(*pos!=0)
				{
					char *pos2=pos;
					while(*pos2!=0 && *pos2!=10 && *pos2!=13) pos2++;
					if (*pos2!=0)
					{
						*(pos2++)=0;
						while(*pos2==10 || *pos2==13) pos2++;
					}
					m_LM.DoMethod(pos,NULL);
					pos=pos2;
				}
				delete[] buff;
			}
			fclose(src);
		}
	}
	return 0;
}


