// GP_termView.cpp : implementation of the CGP_TermView class
//

#include "stdafx.h"
#include "GP_term.h"

#include "GP_termDoc.h"
#include "CntrItem.h"
#include "GP_termView.h"
#include "ComPortSetings.h"
#include <stdio.h>
#include <io.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CGP_TermView

int CGP_TermView::WriteDos()
{
	FILE *tmp;
	char txt[250];
	char *x=NULL;
	int ret=0;
if (forcounter==0)
{
	strcpy(name_curent,InputBuffer2);
	DosToAnsi(name_curent);
	if ((_access(name_curent,0)==0 && _access(name_curent,2)!=0) || (tmp=fopen(name_curent,"wb"))==NULL ) 
	{
		CString str;
		#ifdef RUS
			str.Format("Ошибка открытия файла\n<%s>\nОбратитесь к администратору",name_curent);
		#else
			str.Format("Error Open File\n<%s>",name_curent);
		#endif
		MessageBox(str,GPC.ErrBoxCaption,MB_OK |MB_ICONEXCLAMATION );
		forcounter=0;job_flag=0; SendChar(48);
	}
	else
	{
		SendChar(49);
		fclose(tmp); 
		forcounter=1;
	}
}
else
if (GPC.ModeSendToDos==R03WRITEDOS) 
{
	switch(forcounter++)
	{
	case 1: if (*InputBuffer2!='Y')  
			{forcounter=0; job_flag=0;break;}
			break;
	case 2: SendPickFlProgressDlg=new SendPickFlProgress(CWnd::FromHandle(GPC.m_hViewWnd)); // началось
			SendPickFlProgressDlg->Create(IDD_DIALOGSENDFILE,CWnd::FromHandle(GPC.m_hViewWnd));
			#ifdef RUS
				if ((int)strlen(name_curent)<43)	sprintf(txt,"Файл - %s",name_curent);
				else						sprintf(txt,"Файл - ...%s",name_curent+(int)strlen(name_curent)-42);
			#else
				if ((int)strlen(name_curent)<43)	sprintf(txt,"File - %s",name_curent);
				else						sprintf(txt,"File - ...%s",name_curent+(int)strlen(name_curent)-42);
			#endif

			if (SendPickFlProgressDlg!=NULL) 
			{
				SendPickFlProgressDlg->SetDlgItemText(IDC_SFDEST,txt);
				SendPickFlProgressDlg->SetDlgItemText(IDC_SFLENGTH,"");
				SendPickFlProgressDlg->SetDlgItemText(IDC_SFSORSE,"");
				SendPickFlProgressDlg->ShowWindow(SW_SHOW);
			}
			log_flag=0;
			if (*InputBuffer2==-3) 
			{
				char strr[1000];
				strcpy(strr,InputBuffer2);
				if (AutoDecodFT) DosToAnsi(strr);
				tmp=fopen(name_curent,"at");
				if (tmp)
				{
					fprintf(tmp,"%s\n",strr);
					fclose(tmp);
				}
#ifdef RUS
				sprintf(txt,"Запись - %s",DosToAnsi(InputBuffer2+1));
#else
				sprintf(txt,"Item - %s",DosToAnsi(InputBuffer2+1));
#endif
				if (SendPickFlProgressDlg!=NULL) 
					SendPickFlProgressDlg->SetDlgItemText(IDC_SFSORSE,txt);
			}
			else	{forcounter++; ret--; job_flag=-53;} // если имя и длина не нужна
			break;
	case 3:  SendChar(89);  break;
	default:
		if (forcounter>=123456)	SendChar(99);
			if (*InputBuffer2==4 || forcounter>=123456)	
			{
				stopchar=123456; 
				if (SendPickFlProgressDlg!=NULL) 
				{
					SendPickFlProgressDlg->GPClose();
					delete SendPickFlProgressDlg;
					SendPickFlProgressDlg=NULL;
				}
				log_flag=0;inputnbyte=0;curent_inputbyte=-1;job_flag=0;forcounter=0;
				SendChar(forcounter>=123456?48:49);
				break;
			}
			if (log_flag==0) 
			{
				if (AutoDecodFT) DosToAnsi(InputBuffer2);
				tmp=fopen(name_curent,"at"); fprintf(tmp,"%s\n",InputBuffer2);fclose(tmp);
				curent_inputbyte+=(int)strlen(InputBuffer2)+1;
				if (SendPickFlProgressDlg!=NULL) 
				{
					if (curent_inputbyte>inputnbyte) SendPickFlProgressDlg->m_progress.SetRange32(0,inputnbyte=curent_inputbyte*4);
					SendPickFlProgressDlg->m_progress.SetPos(curent_inputbyte);
					char len[25];
#ifdef RUS
					sprintf(len,"Передано %d байт",curent_inputbyte);
#else
					sprintf(len,"Send %d b",curent_inputbyte);
#endif
					SendPickFlProgressDlg->SetDlgItemText(IDC_SFLENGTH,len);
				}
			}
			else	 SendChar(89);
			log_flag=1-log_flag;
	}
}
else
{
	x=strchr(InputBuffer2,255);
	if (x!=NULL) *x=0;
	switch(forcounter++)
	{
	case 1: if (*InputBuffer2!='Y')  		{	forcounter=0; job_flag=0;	break;	}
			SendPickFlProgressDlg=new SendPickFlProgress(CWnd::FromHandle(GPC.m_hViewWnd)); // началось
			SendPickFlProgressDlg->Create(IDD_DIALOGSENDFILE,CWnd::FromHandle(GPC.m_hViewWnd));
#ifdef RUS
			if ((int)strlen(name_curent)<43)	sprintf(txt,"Файл - %s",name_curent);
			else						sprintf(txt,"Файл - ...%s",name_curent+(int)strlen(name_curent)-42);
#else
			if ((int)strlen(name_curent)<43)	sprintf(txt,"File - %s",name_curent);
			else						sprintf(txt,"File - ...%s",name_curent+(int)strlen(name_curent)-42);
#endif
			if (SendPickFlProgressDlg!=NULL) SendPickFlProgressDlg->SetDlgItemText(IDC_SFDEST,txt);
			break;
	case 2: if (SendPickFlProgressDlg!=NULL) SendPickFlProgressDlg->SetDlgItemText(IDC_SFLENGTH,"");
			if (curent_inputbyte>1)
			{
				char strr[1000];
				strcpy(strr,InputBuffer2+1);
				if (AutoDecodFT) DosToAnsi(strr);
				tmp=fopen(name_curent,"at"); 
				if (tmp)
				{
					fprintf(tmp,"%s\n",strr);
					fclose(tmp);
				}
			}

#ifdef RUS
			sprintf(txt,"Запись - %s",DosToAnsi(InputBuffer2+2));
#else
			sprintf(txt,"Item - %s",DosToAnsi(InputBuffer2+2));
#endif
			if (SendPickFlProgressDlg!=NULL) 
				SendPickFlProgressDlg->SetDlgItemText(IDC_SFSORSE,txt);
			SendChar(201);	curent_inputbyte=0;
			break;
	case 3:
			inputnbyte=atoi(InputBuffer2+2);
			curent_inputbyte=0;
#ifdef RUS
			sprintf(txt,"Передано %d из %d байт",curent_inputbyte,inputnbyte);
#else
			sprintf(txt,"Send %d from %d b",curent_inputbyte,inputnbyte);
#endif
			if (SendPickFlProgressDlg!=NULL) 
			{
				SendPickFlProgressDlg->SetDlgItemText(IDC_SFLENGTH,txt);
				SendPickFlProgressDlg->m_progress.SetRange32(0,inputnbyte);
				SendPickFlProgressDlg->ShowWindow(SW_SHOW);
			}
			SendChar(202);	forcounter=31;
			break;
	default:
			if (*InputBuffer2==210 || forcounter>=123456) 
			{
				stopchar=123456;
				if (SendPickFlProgressDlg!=NULL) 
				{
					SendPickFlProgressDlg->GPClose();
					delete SendPickFlProgressDlg;
					SendPickFlProgressDlg=NULL;
				}
				log_flag=0;inputnbyte=0;curent_inputbyte=-1;job_flag=0;forcounter=0;
				SendChar(forcounter>=123456?255:210);
				SendChar( forcounter>=123456?48:49);
				tmp=fopen(name_curent,"at");fprintf(tmp,"\n");fclose(tmp);
				break;
			}
			if (*InputBuffer2>200) {tmp=fopen(name_curent,"at");fprintf(tmp,"\n");fclose(tmp);forcounter=2; ret--; job_flag=-53; break;}
			if (((int)strlen(InputBuffer2)+32)!=(UINT)InputBuffer2[1] && InputBuffer2[1]!=190) {SendChar(*InputBuffer2-1);break;}
			SendChar(*InputBuffer2);
			if (InputBuffer2[1]!=190)	curent_inputbyte+=(InputBuffer2[1]-34);
			else						curent_inputbyte+=((int)strlen(InputBuffer2)-2);
			
#ifdef RUS
			sprintf(txt,"Передано %d из %d байт",curent_inputbyte,inputnbyte);
#else
			sprintf(txt,"Send %d from %d b",curent_inputbyte,inputnbyte);
#endif
			if (SendPickFlProgressDlg!=NULL) 
			{
				SendPickFlProgressDlg->SetDlgItemText(IDC_SFLENGTH,txt);
				SendPickFlProgressDlg->m_progress.SetPos(curent_inputbyte);
			}
			x=InputBuffer2+1;
			tmp=fopen(name_curent,"at");
			while(*(++x)!=0)
				if (*x==254) fprintf(tmp,"\n");
				else 
					if (AutoDecodFT) 
					{
						int cc=*x;
						if (GPC.chDosAnsi[cc]!=cc) cc=GPC.chDosAnsi[cc];
						fputc(cc,tmp);
					}
					else fputc(*x,tmp);
			fclose(tmp);
			break;
	}
}


return ret;
}
//##################################
//##################################
//##################################
//##################################
//##################################
//##################################

int CGP_TermView::ReadDos()
{
	static FILE *tmp;
	char txt[1500];
	char *x=NULL;
	int ret=0;
	static int nbyte,curbyte,c;

	if (forcounter==0)
	{
		strcpy(name_curent,InputBuffer2);
		DosToAnsi(name_curent);
		if (_access(name_curent,1)!=0 || (tmp=fopen(name_curent,"rt"))==NULL) 
		{
			CString str;
			#ifdef RUS
				str.Format("Ошибка открытия файла\n<%s>\nОбратитесь к администратору",name_curent);
			#else
				str.Format("Error Open File\n<%s>",name_curent);
			#endif
			MessageBox(str,GPC.ErrBoxCaption,MB_OK |MB_ICONEXCLAMATION );
			forcounter=0; job_flag=0;SendChar(48);
		}
		else
		{
			fseek(tmp,0,2);nbyte=ftell(tmp);rewind(tmp);curbyte=0;
			SendChar(49);
			forcounter=1;
		}
	}
	// #######################################################
	// #######################################################
	else if (GPC.ModeSendToPick==R03READDOS) 
	{
		switch(forcounter++)
		{
		case 1: if (*InputBuffer2!='Y')  		{	forcounter=0; job_flag=0;	break;	}
				break;
		case 2: if (*InputBuffer2!='Y')  		{	forcounter=0; job_flag=0;break;	}
				SendPickFlProgressDlg=new SendPickFlProgress(CWnd::FromHandle(GPC.m_hViewWnd)); // началось
				SendPickFlProgressDlg->Create(IDD_DIALOGSENDFILE,CWnd::FromHandle(GPC.m_hViewWnd));
	#ifdef RUS
				if ((int)strlen(name_curent)<43)	sprintf(txt,"Файл - %s",name_curent);
				else						sprintf(txt,"Файл - ...%s",name_curent+(int)strlen(name_curent)-42);
	#else
				if ((int)strlen(name_curent)<43)	sprintf(txt,"File - %s",name_curent);
				else						sprintf(txt,"File - ...%s",name_curent+(int)strlen(name_curent)-42);
	#endif
							
				if (SendPickFlProgressDlg!=NULL) 
				{
					SendPickFlProgressDlg->SetDlgItemText(IDC_SFDEST,txt);
	#ifdef RUS
					sprintf(txt,"Передано %d из %d байт",curbyte,nbyte);
	#else
					sprintf(txt,"Send %d from %d b",curbyte,nbyte);
	#endif
					SendPickFlProgressDlg->SetDlgItemText(IDC_SFLENGTH,txt);
					SendPickFlProgressDlg->m_progress.SetRange32(0,nbyte);
					SendPickFlProgressDlg->ShowWindow(SW_SHOW);
				}
				job_flag=next_job; 
				break;
		case 3: {
					int i=0;
					c=0;
					if (curbyte==0 && fgetc(tmp)!=3)
					{
						rewind(tmp);curbyte++;
						sprintf(txt,"%s",name_curent);
	//					sprintf(txt,"%s",GetFileName(name_curent));
						i=(int)strlen(txt);
					}
					else
					{
						for(i=0;i<215 && (c=fgetc(tmp))!=EOF ;i++,curbyte++)
						{
							if (c==3 || c==10) break;
							if (c==13) i--;	else txt[i]=c; 
						}
						txt[i]=0;
					}

					if (AutoDecodFT) AnsiToDos(txt,0);
					m_Comm.GPSendLine(txt);
					Sleep(100);
					if (c!=10 && c!=0 && c!=EOF) {SendChar(2); i++;}
					SendChar(13);
					iSkip_0=1;
					iSkip_10=1;
					iSkip_13=1;
					sprintf(txt,"%d\r",i);
					m_Comm.GPSendLine(txt);
					Sleep(100);
					//SendChar(13);
					iSkip_0=1;
					iSkip_10=1;
					iSkip_13=1;

					if (SendPickFlProgressDlg!=NULL) 
					{
	#ifdef RUS
						sprintf(txt,"Передано %d из %d байт",curbyte,nbyte);
	#else
						sprintf(txt,"Send %d from %d b",curbyte,nbyte);
	#endif
						SendPickFlProgressDlg->SetDlgItemText(IDC_SFLENGTH,txt);
						SendPickFlProgressDlg->m_progress.SetPos(curbyte);
					}
					forcounter=5;
					job_flag=-2; 
					inputnbyte=3;curent_inputbyte=0;job_flag=-2;
					break;
				}
		case 5:	if (InputBuffer2[1]!=78 && c!=EOF)
				{
					if (c==3)
					{
						SendChar(3);
						Sleep(50);
						SendChar(13);
						Sleep(50);
						iSkip_0=1;
						iSkip_10=1;
						iSkip_13=1;
					}
					forcounter=3;
					ret=-1;job_flag=-54;
					break;
				}
				sprintf(txt,"%c%c%c%c",3,13,4,13);
				Sleep(50);
				m_Comm.GPSendLine(txt);
				iSkip_0=1;
				iSkip_10=1;
				iSkip_13=1;
				Sleep(50);
				stopchar=123456; 
				if (SendPickFlProgressDlg!=NULL)
				{
					SendPickFlProgressDlg->GPClose();
					delete SendPickFlProgressDlg;
					SendPickFlProgressDlg=NULL;
				}
				fclose(tmp);tmp=NULL;
				Sleep(50);		SendChar(49);		Sleep(50);
				inputnbyte=2;curent_inputbyte=0;job_flag=-2;next_job=0;forcounter=0; 
				break;
		}
	}
	// #######################################################
	// #######################################################
	else if (GPC.ModeSendToPick==AJ_READDOS) 
	{
		switch(forcounter++)
		{
		case 1: if (*InputBuffer2!='Y')  		{	forcounter=0; job_flag=0; break;	}
				break;
		case 2: if (*InputBuffer2!='Y')  		{	forcounter=0; job_flag=0;break;	}
				SendPickFlProgressDlg=new SendPickFlProgress(CWnd::FromHandle(GPC.m_hViewWnd)); // началось
				SendPickFlProgressDlg->Create(IDD_DIALOGSENDFILE,CWnd::FromHandle(GPC.m_hViewWnd));
	#ifdef RUS
				if ((int)strlen(name_curent)<43)	sprintf(txt,"Файл - %s",name_curent);
				else						sprintf(txt,"Файл - ...%s",name_curent+(int)strlen(name_curent)-42);
	#else
				if ((int)strlen(name_curent)<43)	sprintf(txt,"File - %s",name_curent);
				else						sprintf(txt,"File - ...%s",name_curent+(int)strlen(name_curent)-42);
	#endif

				if (SendPickFlProgressDlg!=NULL) 
				{
					SendPickFlProgressDlg->SetDlgItemText(IDC_SFDEST,txt);
	#ifdef RUS
					sprintf(txt,"Передано %d из %d байт",curbyte,nbyte);
	#else
					sprintf(txt,"Sending %d of %d bytes",curbyte,nbyte);
	#endif
					SendPickFlProgressDlg->SetDlgItemText(IDC_SFLENGTH,txt);
					SendPickFlProgressDlg->m_progress.SetRange32(0,nbyte);
					SendPickFlProgressDlg->ShowWindow(SW_SHOW);
				}
		case 3: {
					int i;
					c=EOF;
					for(i=2;i<220 && (c=fgetc(tmp))!=EOF && (i==2 || c!=3);i++,curbyte++)
					{
						if (curbyte==0 && c!=3)
						{
							strcpy(txt+3,GetFileName(name_curent));
							i=(int)strlen(txt+3)+3;
							txt[2]=3;
	//						for(txt[i++]=3;name_curent[i-3]!=0;i++) txt[i]=name_curent[i-3];
							txt[i++]=10;
							curbyte++;
							fseek(tmp,-1,SEEK_CUR);
							break;
						}
						else
						switch(c)
						{
						case 13: i--; break;
						default: txt[i]=c; break;
						}
					}

					if (i>2 || (i>1 && c!=EOF))
					{
						static int fl;
						fl=1-fl;
						txt[i]=0;
						txt[0]=fl+40;
						if (i==127-32) {fseek(tmp,-1,SEEK_CUR);i--;curbyte--;}
						txt[1]=i+32;
						
						if (AutoDecodFT) AnsiToDos(txt+2,0);
						x=txt+2;
						while(*x!=0) 
						{
							if (*x==10) *x=254;
							x++;
						}
						*x=255;x[1]=0;
						x=txt;
						while(*x!=0) m_Comm.GPSendChar(*(x++));
	//					m_Comm.GPSendLine(txt);
	Sleep(150);	
						if (SendPickFlProgressDlg!=NULL) 
						{
	#ifdef RUS
							sprintf(txt,"Передано %d из %d байт",curbyte,nbyte);
	#else
							sprintf(txt,"Send %d from %d b",curbyte,nbyte);
	#endif
							SendPickFlProgressDlg->SetDlgItemText(IDC_SFLENGTH,txt);
							SendPickFlProgressDlg->m_progress.SetPos(curbyte);
						}
					}
					else
					{
	Sleep(30);		m_Comm.GPSendChar(208);
	Sleep(10);		m_Comm.GPSendChar(35);
	Sleep(10);		m_Comm.GPSendChar('O');
	Sleep(10);		m_Comm.GPSendChar(255);
	Sleep(30);	
						fclose(tmp);tmp=NULL;
					}
					forcounter=1000;
					inputnbyte=1;curent_inputbyte=0;job_flag=-2;
					break;
				}
		case 1000: 	if (tmp==NULL)	forcounter=1001;
					else			
					{
						if (*InputBuffer2==209) 
							fseek(tmp,0,2);
						forcounter=3;
					}
					ret=-1;job_flag=-54;
					break;
		case 1001: 
					stopchar=123456; 
					if (SendPickFlProgressDlg!=NULL) 
					{
						SendPickFlProgressDlg->GPClose();
						delete SendPickFlProgressDlg;
						SendPickFlProgressDlg=NULL;
					}
					inputnbyte=0;curent_inputbyte=-1;job_flag=0;forcounter=0;
	Sleep(30);	
					SendChar(49);
	Sleep(30);	
					break;
		}

	}
	// #######################################################
	// #######################################################
	else if (GPC.ModeSendToPick==AJ_READNEW) 
	{
		switch(forcounter++)
		{
		case 1: if (*InputBuffer2!='Y')  		{	forcounter=0; job_flag=0; break;	}
				break;
		case 2: if (*InputBuffer2!='Y')  		{	forcounter=0; job_flag=0;break;	}
				SendPickFlProgressDlg=new SendPickFlProgress(CWnd::FromHandle(GPC.m_hViewWnd)); // началось
				SendPickFlProgressDlg->Create(IDD_DIALOGSENDFILE,CWnd::FromHandle(GPC.m_hViewWnd));
	#ifdef RUS
				if ((int)strlen(name_curent)<43)	sprintf(txt,"Файл - %s",name_curent);
				else						sprintf(txt,"Файл - ...%s",name_curent+(int)strlen(name_curent)-42);
	#else
				if ((int)strlen(name_curent)<43)	sprintf(txt,"File - %s",name_curent);
				else						sprintf(txt,"File - ...%s",name_curent+(int)strlen(name_curent)-42);
	#endif

				if (SendPickFlProgressDlg!=NULL) 
				{
					SendPickFlProgressDlg->SetDlgItemText(IDC_SFDEST,txt);
	#ifdef RUS
					sprintf(txt,"Передано %d из %d байт",curbyte,nbyte);
	#else
					sprintf(txt,"Send %d from %d b",curbyte,nbyte);
	#endif
					SendPickFlProgressDlg->SetDlgItemText(IDC_SFLENGTH,txt);
					SendPickFlProgressDlg->m_progress.SetRange32(0,nbyte);
					SendPickFlProgressDlg->ShowWindow(SW_SHOW);
				}
		case 3: {
					int i;
					c=EOF;
					for(i=2;i<220 && (c=fgetc(tmp))!=EOF && (i==2 || c!=3);i++,curbyte++)
					{
						if (curbyte==0 && c!=3)
						{
							strcpy(txt+3,GetFileName(name_curent));
							i=(int)strlen(txt+3)+3;
							txt[2]=3;
	//						for(txt[i++]=3;name_curent[i-3]!=0;i++) txt[i]=name_curent[i-3];
							txt[i++]=13;
							curbyte++;
							fseek(tmp,-1,SEEK_CUR);
							break;
						}
						else
						switch(c)
						{
						case 13: i--; break;
						default: txt[i]=c; break;
						}
					}
					if (i>2 || (i>1 && c!=EOF))
					{
						static int fl;
						fl=1-fl;
						txt[i]=0;
						txt[0]=fl+40;
						x=txt;
						while(*x!=0 && *x!=10 && *x!=13) x++;
						*x=13;x[1]=0;
						txt[1]=32;
						i=(int)strlen(txt);

						if (i==127-32)
						{txt[i-1]=' ';txt[i++]=13;txt[i]=0;}
						txt[1]=i+32;

						if (AutoDecodFT) AnsiToDos(txt+2,0);
						x=txt;
						Sleep(20);	
						while(*x!=0) m_Comm.GPSendChar(*(x++));
	//					m_Comm.GPSendLine(txt);
						Sleep(20);
						if (SendPickFlProgressDlg!=NULL) 
						{
	#ifdef RUS
							sprintf(txt,"Передано %d из %d байт",curbyte,nbyte);
	#else
							sprintf(txt,"Send %d from %d b",curbyte,nbyte);
	#endif
							SendPickFlProgressDlg->SetDlgItemText(IDC_SFLENGTH,txt);
							SendPickFlProgressDlg->m_progress.SetPos(curbyte);
						}
					}
					else
					{
	Sleep(30);		m_Comm.GPSendChar(208);
	Sleep(10);		m_Comm.GPSendChar(35);
	Sleep(10);		m_Comm.GPSendChar('O');
	Sleep(10);		m_Comm.GPSendChar(13);
	Sleep(30);	
						fclose(tmp);tmp=NULL;
					}
					forcounter=1000;
					inputnbyte=1;curent_inputbyte=0;job_flag=-2;
					break;
				}
		case 1000: 	if (tmp==NULL)	forcounter=1001;
					else			
					{
						if (*InputBuffer2==209) fseek(tmp,0,2);
						forcounter=3;
					}
					ret=-1;job_flag=-54;
					break;
		case 1001: 
					stopchar=123456; 
					if (SendPickFlProgressDlg!=NULL) 
					{
						SendPickFlProgressDlg->GPClose();
						delete SendPickFlProgressDlg;
						SendPickFlProgressDlg=NULL;
					}
					inputnbyte=0;curent_inputbyte=-1;job_flag=0;forcounter=0;
	Sleep(50);	
					SendChar(49);
	Sleep(50);	
					break;
		}
	}

return ret;
}