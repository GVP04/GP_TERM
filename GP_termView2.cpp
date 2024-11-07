// GP_termView.cpp : implementation of the CGP_TermView class
//

#include "stdafx.h"
#include "GP_term.h"

#include "GP_termDoc.h"
#include "CntrItem.h"
#include "GP_termView.h"
#include "GPExcel.h"
#include "GPContextMenu.h"
#include "DlgViewSystemMethods.h"
#include "DlgLogin.h"
#include "COMServer.h"
#include "DllServer.h"
#include "DlgNotepadSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CCOMServer m_COMServer;
extern DllServer m_DllServer;

/////////////////////////////////////////////////////////////////////////////
// CGP_TermView

// Продолжение исполнения сложных ESC последовательностей
// void CGP_TermView::RemappingInput(int nbyte)

UINT CGP_TermView::RemappingInput(int nbyte)
{
	GPScreen *s=GetDocument()->GetActiveScreen();

	static int iLastChar;

	if (m_dwParseInitStrFlag)
	{
		if (*m_Comm.GetInitStr()!=0 && m_Comm.Get_commType()==GPCT_SOCKET)
		{
			GPC.cs_ScriptLine=m_Comm.GetInitStr()+GPC.cs_ScriptLine;
			GPC.cs_ScriptWaitLine="";
			GPC.cs_ScriptWaitLineCurrent="";
			GPC.dw_ScriptWaitFlag=0;
			DoScriptCommand();
		}
		m_dwParseInitStrFlag=0;
	}
	BOOL working_flag=TRUE;

	int i;
	for(i=0;(i<nbyte || (i==nbyte && job_flag!=-27 && job_flag<-4 && i--)) && working_flag;iLastChar=InputBuffer[i++])
	{
		if (job_flag<-27 && InputBuffer[i]==27) i--;

		if (GPC.dw_ScriptWaitFlag)
		{
			if (GPC.cs_ScriptWaitLine!="")
			{
				char tmadd[]={0,0,};
				*tmadd=InputBuffer[i];
				GPC.cs_ScriptWaitLineCurrent+=tmadd;
				//TRACE("%c",*tmadd);
				int ipos=GPC.cs_ScriptWaitLineCurrent.Find(GPC.cs_ScriptWaitLine,0);
				if (ipos<0)
				{
					ipos=GPC.cs_ScriptWaitLineCurrent.Find(GPC.cs_ScriptWaitLine[0]);
					if (ipos<0) GPC.cs_ScriptWaitLineCurrent="";
					else
					if (ipos==0)
					{
						if (GPC.cs_ScriptWaitLineCurrent.GetLength()>GPC.cs_ScriptWaitLine.GetLength())
							GPC.cs_ScriptWaitLineCurrent=GPC.cs_ScriptWaitLineCurrent.Mid(1,100000);
					}
					else
					{
						GPC.cs_ScriptWaitLineCurrent=GPC.cs_ScriptWaitLineCurrent.Mid(ipos,100000);
					}
				}
				else
				{
				//TRACE("*****%s\n",GPC.cs_ScriptWaitLineCurrent);
				//TRACE("*****%s\n",GPC.cs_ScriptWaitLine);
					GPC.cs_ScriptWaitLineCurrent=GPC.cs_ScriptWaitLineCurrent.Mid(ipos+GPC.cs_ScriptWaitLine.GetLength(),100000);
					GPC.cs_ScriptWaitLine="";
					GPC.dw_ScriptWaitFlag=0;
					DoScriptCommand();
					if (GPC.dw_ScriptWaitFlag==0) GPC.cs_ScriptWaitLineCurrent="";
					TRACE("%s\r",GPC.cs_ScriptLine);
					if (GPC.cs_ScriptLine=="\\r") 
						i=i;

				//TRACE("*****%s\n",GPC.cs_ScriptWaitLineCurrent);
				//TRACE("*****%s\n",GPC.cs_ScriptWaitLine);
				}
			}
			else 
			{
				GPC.dw_ScriptWaitFlag=0;
				GPC.cs_ScriptWaitLineCurrent="";
			}
		}

		if (InputBuffer[i]!=13 && InputBuffer[i]!=0 && InputBuffer[i]!=10) {iSkip_10=0;iSkip_13=0;iSkip_0=0;}

		if (m_Comm.IsDumping())
			m_Comm.PrintDmp(InputBuffer[i],job_flag,GPC_DUMPREM);

		if (iSkip_10!=0)
		{
			if (InputBuffer[i]==10)
			{
				iSkip_10=0;
				continue;
			}
			else
				if (InputBuffer[i]!=13 && InputBuffer[i]!=0) iSkip_10=0;
		}

		if (iSkip_13!=0 || (iLastChar==13 && iSkip_10!=0 && InputBuffer[i]==13))
		{
			if (InputBuffer[i]==13)
			{
				iSkip_13=0;
				continue;
			}
			else
				if (InputBuffer[i]!=10 && InputBuffer[i]!=0) iSkip_13=0;
		}

		if (iSkip_0!=0)
		{
			if (InputBuffer[i]==0)
			{
				if (i+2<nbyte)
				{
					if (InputBuffer[i+1]!=10 || InputBuffer[i+2]!=0) iSkip_0=0;
				}
				else
				if (i+1<nbyte)
				{
					if (InputBuffer[i+1]!=10) iSkip_0=0;
				}
				else
				{
					iSkip_0=0;
				}
				continue;
			}
			else
				if (InputBuffer[i]!=10 && InputBuffer[i]!=13) iSkip_0=0;
		}

		if (job_flag>-31)
		{
			switch(job_flag)
			{
			case 0:
				{
					switch(InputBuffer[i])
					{
					case 8:
						{
							m_TermCap.ClearEscPool();
							m_TermCap.FoundEsc=NULL;
							DoEscSeq(2);
							continue;
						}
					case 27: 
					case 10:
					case 11:
					case 12:
					case 14:
					case 15:
					case 17:
					case 18:
					case 19:
					case 20:
					case 21:
					case 22:
					case 23:
					case 24:
					case 25:
					case 26:
					case 29:
					case 30:
						job_flag=-27;
						break;
					case 16:
					case 28:
						job_flag=-27;
						break;
					default:
						{
							while(i+2<nbyte && InputBuffer[i]==7 && InputBuffer[i+1]==7) i++;

							iLastCommand=0;

							if (InputBuffer[i]==250 && i<nbyte-1 && InputBuffer[i+1]==250 && m_Comm.GetLockEventsEcho()!=0)
							{
								next_job=0;
								job_flag=-4;
								continue;
							}

							BOOL bInsChar=s->GetInsertMode();
							int nSubCount=1;
							static int iGraphFlag;
							char cOutTmp=InputBuffer[i];
							if (cOutTmp==0xE2 && (s->ScrConvFlags&0x1))
							{
								DWORD dwMaskidx[]={
									0x00000001,0x00000002,0x00000004,0x00000008,
									0x00000010,0x00000020,0x00000040,0x00000080,
									0x00000100,0x00000200,0x00000400,0x00000800,
									0x00001000,0x00002000,0x00004000,0x00008000,
									0x00010000,0x00020000,0x00040000,0x00080000,
									0x00100000,0x00200000,0x00400000,0x00800000,
									0x01000000,0x02000000,0x04000000,0x08000000,
									0x10000000,0x20000000,0x40000000,0x80000000,
									};
								unsigned short idx=(InputBuffer[i+2] & 0x3F);
								DWORD idx2=dwMaskidx[(idx&0x1F)];
								if ((nbyte-i<2 || (nbyte-i<3 && (UINT)InputBuffer[i+1]>=0x128)) && iGraphFlag )
								{
									working_flag=FALSE;
									next_job=job_flag=0;
									i--;
									continue;
								}
								else
								if (nbyte-i>2 && (UINT)InputBuffer[i+1]>=128 && (InputBuffer[i+2]&(0xFF^0x3F)) && (GPScreen::dwGRConvFlags[((UINT)InputBuffer[i+1]-128)*2+(idx%1)] & idx2))
								{
									unsigned short gc3=0;
									if ((UINT)InputBuffer[i+1]<192)
										gc3=0x2000+(InputBuffer[i+1]-128)*64+idx;
									else
										gc3=0x1000+(InputBuffer[i+1]-128)*64+idx;

									if (gc3)
									{
										i+=2;
										iGraphFlag=gc3;
										if (m_CaptureFile && (!GPC.TCLinProgress || m_TCLvisible==TRUE || m_HIDEVIEWMODE))
										{
											fputc(InputBuffer[i-2],m_CaptureFile);
											fputc(InputBuffer[i-1],m_CaptureFile);
											fputc(InputBuffer[i]  ,m_CaptureFile);
										}

										if (!GPC.TCLinProgress)
										{

											if (m_CaptureFile==NULL || (m_CaptureFlags&0x1)) 
											{
												if (!AddCharToDirectInput((char)gc3,s))
												{
													if (bInsChar) s->InsertChar((UINT)1);
													s->CharOutGRUC(gc3);
													m_DlgSeparateView.AppendCharToOutput(InputBuffer[i-2],m_OutputCharDelay?1:0);
													m_DlgSeparateView.AppendCharToOutput(InputBuffer[i-1],m_OutputCharDelay?1:0);
													m_DlgSeparateView.AppendCharToOutput(InputBuffer[i]  ,m_OutputCharDelay?1:0);
												}
											}
											m_OutputCharDelay=0;
										}
										else
										{
											if (m_TCLvisible==TRUE || m_HIDEVIEWMODE)
											{
												if (m_CaptureFile==NULL || (m_CaptureFlags&0x1)) 
												{
													if (bInsChar) s->InsertChar((UINT)1);
													s->CharOutGRUC(gc3);
												}
												m_DlgSeparateView.AppendCharToOutput(InputBuffer[i-2],m_OutputCharDelay?1:0);
												m_DlgSeparateView.AppendCharToOutput(InputBuffer[i-1],m_OutputCharDelay?1:0);
												m_DlgSeparateView.AppendCharToOutput(InputBuffer[i]  ,m_OutputCharDelay?1:0);
											}

											char tstr[]={0,0,0,0,};
											tstr[0]=InputBuffer[i-2];
											tstr[1]=InputBuffer[i-1];
											tstr[2]=InputBuffer[i];
											GPC.AddToOUTTCL(tstr);
										}

									}
									else iGraphFlag=0;
								}
								else iGraphFlag=0;
							}
							else iGraphFlag=0;

							if (!iGraphFlag)
							{
								if (GPC.TCLinProgress==FALSE)
								{
									if (m_CaptureFile && cOutTmp) fputc(GPC.chDosAnsi[cOutTmp&0xFF],m_CaptureFile);

									if (m_CaptureFile==NULL || (m_CaptureFlags&0x1)) 
									{
										if (!AddCharToDirectInput(cOutTmp,s))
										{
											if (bInsChar) s->InsertChar((UINT)1);
											s->CharOutAW(cOutTmp);
											m_DlgSeparateView.AppendCharToOutput(GPC.chDosAnsi[cOutTmp&0xFF],m_OutputCharDelay?1:0);
										}
									}
									m_OutputCharDelay=0;
								}
								else
								{
									if (m_TCLvisible==TRUE || m_HIDEVIEWMODE)
									{
										if (m_CaptureFile==NULL || (m_CaptureFlags&0x1)) 
										{
												if (bInsChar) s->InsertChar((UINT)1);
												s->CharOutAW(cOutTmp);
										}
										if (m_CaptureFile) fputc(GPC.chDosAnsi[cOutTmp&0xFF],m_CaptureFile);
										m_DlgSeparateView.AppendCharToOutput(GPC.chDosAnsi[cOutTmp&0xFF],0);
									}
									char tstr[10];
									tstr[0]=cOutTmp;
									tstr[1]=0;
									if (cOutTmp!=10 && cOutTmp!=0) GPC.AddToOUTTCL(tstr);
								}
							}
						}
						continue;
					}
				}

			case -27: // поиск последовательности
				if (InputBuffer[i]/* && InputBuffer[i]!=10 && InputBuffer[i]!=13*/)
				{
					curent_inputbyte=-1;
					forcounter=0;
					switch(m_TermCap.AddByteToEscPool(InputBuffer[i]))
					{
					case -1: // нет вообще
						{
							int nn,nech=m_TermCap.GetEscPoolLen();
							const char *tmpesc=m_TermCap.GetEscPool();
							iLastCommand=0;
					if (*tmpesc!=10) 
						TRACE("Unknown ESC %s  - ",tmpesc);
							for(nn=0;nn<nech;nn++)
							{
					if (*tmpesc!=10) TRACE("%d ",tmpesc[nn]);
								if (GPC.TCLinProgress==FALSE)
								{
									if (m_CaptureFile) fputc(GPC.chDosAnsi[tmpesc[nn]&0xFF],m_CaptureFile);

									if (m_CaptureFile==NULL || (m_CaptureFlags&0x1)) 
									{
										if (!AddCharToDirectInput(tmpesc[nn],s))
										{
											s->CharOutAW(tmpesc[nn]);
											m_DlgSeparateView.AppendCharToOutput(GPC.chDosAnsi[tmpesc[nn]&0xFF],m_OutputCharDelay?1:0);
										}
									}
									m_OutputCharDelay=0;
								}
								else
								{
									if (m_TCLvisible==TRUE || m_HIDEVIEWMODE)
									{
										if (!m_CaptureFile || (m_CaptureFlags&0x1)) s->CharOutAW(tmpesc[nn]);
										if (m_CaptureFile) fputc(GPC.chDosAnsi[tmpesc[nn]&0xFF],m_CaptureFile);
										m_DlgSeparateView.AppendCharToOutput(GPC.chDosAnsi[tmpesc[nn]&0xFF],0);
									}
									char tstr[10];
									tstr[0]=tmpesc[nn];
									tstr[1]=0;
									if (tmpesc[nn]!=10 && tmpesc[nn]!=0) GPC.AddToOUTTCL(tstr);
								}
							}
					if (*tmpesc!=10) TRACE("\n");

						}
						if (GPC.DlgStatistics && InputBuffer[i]!=10 && InputBuffer[i]!=0) GPC.DlgStatistics->m_STAT_SESSION.dwEscUnknSeq++;
						m_TermCap.ClearEscPool();
						if (i<-1) i=-1;
						if (esc_pointer) i-=(esc_pointer-1);
						job_flag=esc_pointer=0;
						break;
					case -2: // пока есть надежда
						break;
					default: // нашлась
						{
							if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_SESSION.dwEscSeq++;
							PTERMCAPESCITEM pEsc=m_TermCap.GetFoundEsc();
							if (pEsc)
							{
								const DWORD *pCmdList=m_TermCap.GetVAttrByCmdId(pEsc->dwCommand);
								if (pCmdList && *pCmdList)
								{
									pCmdList++;
									while(*(++pCmdList))
										DoEscSeq(*pCmdList);
									esc_pointer=0;
								}
								else
								switch(DoEscSeq(pEsc->dwCommand)) /* выполнение */
								{
								case -1:	break;
								case 1:		i--;
								default:	esc_pointer=0;
								}
								iLastCommand=pEsc->dwCommand;
								m_TermCap.ClearEscPool();
								if (LockRemappingFlag>0)
								{
									i++;
									int j;
									for(j=0;j<nbyte-i;j++) InputBuffer[j]=InputBuffer[i+j];
									return nbyte-i;
								}
							}
							else
							{
								s->CharOutAW(m_TermCap.GetEscPool(),m_TermCap.GetEscPoolLen());
								m_TermCap.ClearEscPool();
								iLastCommand=0;
							}
	
						}
						break;
					}
				}
				break;

			case -2:  // load inputnbyte into InputBuffer2
				if (curent_inputbyte==0 && CurLenIB2>DEFNIB2)
				{
					delete[] InputBuffer2;
					CurLenIB2=DEFNIB2;
					InputBuffer2=new char [DEFNIB2+100];
				}

				if (curent_inputbyte>=CurLenIB2)
				{
					char *tmp=new char [CurLenIB2+CurLenIB2/2+100];
					int jjj;
					for(jjj=0;jjj<CurLenIB2;jjj++) tmp[jjj]=InputBuffer2[jjj];
					CurLenIB2=CurLenIB2+CurLenIB2/2;
					delete[] InputBuffer2;
					InputBuffer2=tmp;
				}

				InputBuffer2[curent_inputbyte]=InputBuffer[i];
				if ((++curent_inputbyte)>=inputnbyte)	{i--;job_flag=next_job;}
				break;
			case -3:  // skip inputnbyte
			case -1: // load string into 	InputBuffer2
				if (string_ptr==0 && CurLenIB2>DEFNIB2)
				{
					delete[] InputBuffer2;
					CurLenIB2=DEFNIB2;
					InputBuffer2=new char [DEFNIB2+100];
				}

				if (string_ptr>=CurLenIB2)
				{
					char *tmp=new char [CurLenIB2+CurLenIB2/2+100];
					int jjj;
					for(jjj=0;jjj<CurLenIB2;jjj++) tmp[jjj]=InputBuffer2[jjj];
					CurLenIB2=CurLenIB2+CurLenIB2/2;
					delete[] InputBuffer2;
					InputBuffer2=tmp;
				}

				InputBuffer2[string_ptr]=InputBuffer[i];
				InputBuffer2[string_ptr+1]=0;

				if (InputBuffer[i]==13 || InputBuffer[i]==10 || InputBuffer[i]==0 || InputBuffer[i]==stopchar)
				{
					switch(InputBuffer[i])
					{
					case 0:
						InputBuffer2[string_ptr]=0;
						iSkip_0=1;
						iSkip_10=1;
						iSkip_13=1;
						break;
					case 10:
						InputBuffer2[string_ptr]=0;
						iSkip_13=1;
						iSkip_0=1;
						break;
					case 13:
						InputBuffer2[string_ptr]=0;
						iSkip_10=1;
						iSkip_0=1;
						break;
					}

					string_ptr=0;
					if((job_flag=next_job)<0)
					{
						string_ptr--;
						if (InputBuffer[i]!=13 && InputBuffer[i]!=10 && InputBuffer[i]!=0) string_ptr=0;
			//			if (i<nbyte+1 && InputBuffer[i+1]==0 && InputBuffer[i]==13) i++;
						i--;
					}
				}
				else	string_ptr++;
				break;
			case -4:  // skip line
				if (InputBuffer[i]==13 || InputBuffer[i]==10 || InputBuffer[i]==0 || InputBuffer[i]==stopchar)
				{
					switch(InputBuffer[i])
					{
					case 0:
						iSkip_0=1;
						iSkip_10=1;
						iSkip_13=1;
						break;
					case 10:
						iSkip_13=1;
						iSkip_0=1;
						break;
					case 13:
						iSkip_10=1;
						iSkip_0=1;
						break;
					}
					job_flag=next_job;
				}
				break;
			case -5: // load string into InputBuffer2 till stop char
				if (string_ptr==0 && CurLenIB2>DEFNIB2)
				{
					delete[] InputBuffer2;
					CurLenIB2=DEFNIB2;
					InputBuffer2=new char [DEFNIB2+100];
				}

				if (string_ptr>=CurLenIB2)
				{
					char *tmp=new char [CurLenIB2+CurLenIB2/2+100];
					int jjj;
					for(jjj=0;jjj<CurLenIB2;jjj++) tmp[jjj]=InputBuffer2[jjj];
					CurLenIB2=CurLenIB2+CurLenIB2/2;
					delete[] InputBuffer2;
					InputBuffer2=tmp;
				}

				InputBuffer2[string_ptr]=InputBuffer[i];
				InputBuffer2[string_ptr+1]=0;

				if (InputBuffer[i]==stopchar || string_ptr>10000000)
				{
					if((job_flag=next_job)<0)
						i--;
				}
				else	string_ptr++;
				break;

			default: // Продолжение выполнения сложных команд
				next_job=job_flag=0;
				break;
			}
		}
		else
		if (job_flag>-1000)
		{
			switch(job_flag)
			{
			case -34: // load table Part two
					if (curent_inputbyte==-1)
					{
						strncpy(name_curent,InputBuffer2,200);
						name_curent[200]=0;
						job_flag=-2;
						curent_inputbyte=0;
						inputnbyte=2; 
						break;
					}
					SendChar(LoadScrRgn(name_curent,Point(InputBuffer2[0]-32,InputBuffer2[1]-32))?'1':'0');
					curent_inputbyte=-1;job_flag=0;	break;
			case -35: // DOSFILE EXIST Part two
					SendChar(_access(InputBuffer2,0)+'1');curent_inputbyte=-1;job_flag=0;break;
			case -38: // DOS COMMAND Part two
					if ((int)strlen(InputBuffer2)==0)
					{
						char *posrepl=name_curent;
						while(*posrepl)
						{
							if (*posrepl>0 && *posrepl<32) *posrepl=32;
							posrepl++;
						}
						if (_strnicmp(name_curent,"cd ",3)==0) SendChar(_chdir(name_curent+3)+'1');
						else
						if (_strnicmp(name_curent,"chdir ",6)==0) SendChar(_chdir(name_curent+6)+'1');
						else
						if (_strnicmp(name_curent,"mkdir ",6)==0) SendChar(_mkdir(name_curent+6)+'1');
						else
							if (_strnicmp(name_curent,"spawn_",6)==0)
							{
								char *prg=strchr(name_curent,' ');
								if (prg!=NULL)
								{
									UINT type=_P_NOWAIT;

									if (_strnicmp(name_curent,"spawn_w ",8)==0) 	type=_P_WAIT;
									else
										if (_strnicmp(name_curent,"spawn_n ",8)==0) 	type=_P_NOWAIT;
										else
											if (_strnicmp(name_curent,"spawn_d ",8)==0) 	type=_P_DETACH;

									while(*prg==' ') prg++;
									char *args=strchr(prg,' ');
									if (args!=NULL && *args!=0)
									{
										*(args++)=0;
										while(*args==' ') args++;
									}

									errno=0;
									if (args!=NULL && *args!=0)
										_spawnlp(type,prg,prg,args,NULL);
									else
										_spawnlp(type,prg,prg,NULL);

									SendChar(errno+(errno?'0':'1'));
								}
							}
							else
								SendChar(system(DosToAnsi(name_curent))+'1');
						SendChar(13);
						iSkip_0=0;
						iSkip_10=0;
						iSkip_13=0;
						curent_inputbyte=-1;
						job_flag=0;
					}
					else
					{
						strcat(name_curent,InputBuffer2);strcat(name_curent,"   "); 
						string_ptr=0; 
						job_flag=-1;
						curent_inputbyte=-1;
					}
					break;
			case -39: // DOS COMMAND Part two
				{
					if (_strnicmp(InputBuffer2,"cd ",3)==0) SendChar(_chdir(InputBuffer2+3)+'1');
					else
					if (_strnicmp(InputBuffer2,"chdir ",6)==0) SendChar(_chdir(InputBuffer2+6)+'1');
					else
					if (_strnicmp(InputBuffer2,"mkdir ",6)==0) SendChar(_mkdir(InputBuffer2+6)+'1');
					else					SendChar(-system(DosToAnsi(InputBuffer2))+'1');

					curent_inputbyte=-1;
					job_flag=0;
				}
					break;
			case -41: // MESSAGE TWOMES Part two
					if (forcounter==0) {*name_curent=0;}
					if (forcounter<2)
					{
						char *tmmm=name_curent+(int)strlen(name_curent);
						strncpy(tmmm,InputBuffer2,1024);
						tmmm[1024]=0;
						strcat(name_curent,"\r");
						string_ptr=0; forcounter++;
						iSkip_0=1;
						iSkip_10=1;
						iSkip_13=1;
						job_flag=-1;
						break;
					}
					{
						HWND tmp=::GetFocus();
						SendChar(MessageBox(DosToAnsi(ReplaceSpec(name_curent)),DosToAnsi(InputBuffer2),MB_OKCANCEL|MB_ICONQUESTION)==IDOK?'1':'0');
						if (tmp!=NULL) ::SetFocus(tmp);
					}
					curent_inputbyte=-1; forcounter=0; job_flag=0;
					break;
			case -42: // MESSAGE ASKWIN Part two
					if (forcounter==0) *name_curent=0;
					if (forcounter<10 && *InputBuffer2!=243)
					{
						char *tmmm=name_curent+(int)strlen(name_curent);
						strncpy(tmmm,InputBuffer2,1024);
						tmmm[1024]=0;
						strcat(name_curent,"\r");

						forcounter++;
						job_flag=-1;
						iSkip_0=1;
						iSkip_10=1;
						iSkip_13=1;
						string_ptr=0;
						break;
					}
					{
						HWND tmp=::GetFocus();
						forcounter=MessageBox(DosToAnsi(ReplaceSpec(name_curent)),GPC.MsgBoxCaption,MB_YESNOCANCEL|MB_ICONQUESTION);
						SendChar(forcounter==IDYES? 89 : forcounter==IDNO ? 78 : 68 );
						if (tmp!=NULL) ::SetFocus(tmp);
					}
					curent_inputbyte=-1; forcounter=0; job_flag=0;
					break;
			case -43: // MESSAGE ONEMES Part two
					{
						HWND tmp=::GetFocus();
						SendChar(MessageBox(DosToAnsi(ReplaceSpec(InputBuffer2)),GPC.MsgBoxCaption,MB_OKCANCEL|MB_ICONQUESTION)==IDOK?'1':'0');
						if (tmp!=NULL) ::SetFocus(tmp);
					}
					string_ptr=0;
					curent_inputbyte=-1; forcounter=0; job_flag=0;
					break;
			case -53: /* WRITEDOS */   string_ptr=0; job_flag=-1; i+=WriteDos(); break;
			case -54: /* READDOS  */   string_ptr=0; job_flag=-1; i+=ReadDos(); break;
			case -60: // load menu
					SendChar(49+forcounter);
					if (forcounter<1)
					{	forcounter++; string_ptr=0; job_flag=-1;	}
					else
					{curent_inputbyte=-1; forcounter=0; job_flag=0;	}
					break;
			case -61: /* CONVERT TO TEXT6 */
			case -62: /* CONVERT TO BIN8 */
			case -63: /* DOS COPYFILE */
			case -65: /* DOS RENAME FILE */
					if (*name_curent==0)
					{
						char *pos2=strchr(InputBuffer2,0x1);
						if (pos2)	*(pos2++)=0;
						strcpy(name_curent,InputBuffer2);
						if (pos2)	strcpy(InputBuffer2,pos2);
						string_ptr=0; 
						if (!pos2)
						{
							job_flag=-1;
							break;
						}
					}
					switch(job_flag)
					{
					case -61: /* CONVERT TO TEXT6 */FileBinToText(DosToAnsi(name_curent),DosToAnsi(InputBuffer2));	break;
					case -62: /* CONVERT TO BIN8 */	FileTexToBin(DosToAnsi(name_curent),DosToAnsi(InputBuffer2));		break;
					case -63: /* DOS COPYFILE */	CopyFile(DosToAnsi(name_curent),DosToAnsi(InputBuffer2),FALSE);	break;
					case -65: /* DOS RENAME FILE */	MoveFile(DosToAnsi(name_curent),DosToAnsi(InputBuffer2));			break;
					}
					job_flag=0;
					break;

			case -64: /* DOS DELETE FILE */
				{
					CFileFind ff;
					if (ff.FindFile(DosToAnsi(InputBuffer2),0))
					{
						UINT ret=0;
						CTime LATime,CRTime,LWTime;
						do
						{
							ret=ff.FindNextFile();
							ff.GetLastAccessTime(LATime);
							ff.GetCreationTime(CRTime);
							ff.GetLastWriteTime(LWTime);
							if (!ff.IsDirectory ( ))
							{
								DeleteFile(ff.GetFilePath());
							}
						}	while(ret);
						ff.Close();
					}
					next_job=job_flag=0;
				}
				break;
			case -68: /* PRINT SCR*/
				{
					//m_PrintTransp=IdScr;
					DosToAnsi(InputBuffer2);
					GPScreen *sc=GetDocument()->GetScreenById(atoi(InputBuffer2));
					if (sc) sc->ScrPrint(FindField(InputBuffer2,2,","));
					LockRemappingFlag++;
					job_flag=0;
					break;
				}
			case -69: /*CREATE SCR*/
				{
					Size siz(80,25);
					m_TermCap.m_Vars.IdScr=0;
					m_LastScanf=sscanf(InputBuffer2,"%d,%d,%d",&m_TermCap.m_Vars.IdScr,&siz.Width,&siz.Height);
					GetDocument()->SelectScreen(GetDocument()->CreateScreen(siz,m_TermCap.m_Vars.IdScr));
					job_flag=0;
					s=GetDocument()->GetActiveScreen();
					break;
				}
			case -70: /*CREATE WND*/
				{
					Size cs(80,25);
					Rect re(1,1,10,10);
					m_LastScanf=sscanf(InputBuffer2,"%d,%d,%d,%d,%d,%d,%d,%d",&m_TermCap.m_Vars.IdScr,&m_TermCap.m_Vars.IdWnd,&cs.Width,&cs.Height,&re.X,&re.Y,&re.Width,&re.Height);
					re.Width-=re.X;
					re.Height-=re.Y;
					GPScreen *scr=GetDocument()->GetScreenById(m_TermCap.m_Vars.IdScr);
					if (scr) scr->GPCreateWindow(cs, re, m_TermCap.m_Vars.IdWnd);
					job_flag=0;
					break;
				}
			case -71: /*DELETE SCR*/
				{
					m_TermCap.m_Vars.IdScr=1;
					m_LastScanf=sscanf(InputBuffer2,"%d",&m_TermCap.m_Vars.IdScr);
					GetDocument()->DeleteScreen(m_TermCap.m_Vars.IdScr);
					job_flag=0;
					s=GetDocument()->GetActiveScreen();
					break;
				}
			case -72: /*DELETE WND*/
				{
					m_TermCap.m_Vars.IdScr=1;
					m_LastScanf=sscanf(InputBuffer2,"%d,%d",&m_TermCap.m_Vars.IdScr,&m_TermCap.m_Vars.IdWnd);
					GetDocument()->GetScreenById(m_TermCap.m_Vars.IdScr)->DeleteWindow(m_TermCap.m_Vars.IdWnd);
					job_flag=0;
					break;
				}
			case -74: /*CHANGE DIR*/ 
				{
					if (InputBuffer2[1]==':')
					{
						char cwd[250];
						*cwd=0;
						_getcwd(cwd,200);
						if ((cwd[0]&0x17)!=(InputBuffer2[0]&0x17))
							_chdrive(InputBuffer2[0]&0x17);
					}

					SendChar(_chdir(InputBuffer2)+'1');	
					job_flag=0; 
				}
				break;
			case -75: /*GET FILE PROPERTIES*/
				{
					CFileFind fl;
					char str[2000];*str=0;
					if (*InputBuffer2)
					{
						char *tmpposs=InputBuffer2+(int)strlen(InputBuffer2)-1;
						if (*tmpposs=='\\' || *tmpposs=='/') *tmpposs=0;
					}
					if (fl.FindFile(DosToAnsi(InputBuffer2))!=0)
					{
						fl.FindNextFile();
						CTime LATime,CRTime,LWTime;
						fl.GetLastAccessTime(LATime);
						fl.GetCreationTime(CRTime);
						fl.GetLastWriteTime(LWTime);

						sprintf(str,"%I64d\x7F%I64d\x7F%2.2d\x7F%2.2d\x7F%2.2d\x7F%2.2d\x7F%2.2d\x7F%4.4d\x7F%I64d\x7F%2.2d\x7F%2.2d\x7F%2.2d\x7F%2.2d\x7F%2.2d\x7F%4.4d\x7F%I64d\x7F%2.2d\x7F%2.2d\x7F%2.2d\x7F%2.2d\x7F%2.2d\x7F%4.4d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d",
									fl.GetLength( ) ,
									CRTime.GetTime(), CRTime.GetSecond(), CRTime.GetMinute(), CRTime.GetHour(), CRTime.GetDay(), CRTime.GetMonth(),CRTime.GetYear(),
									LWTime.GetTime(), LWTime.GetSecond(), LWTime.GetMinute(), LWTime.GetHour(), LWTime.GetDay(), LWTime.GetMonth(),LWTime.GetYear(),
									LATime.GetTime(), LATime.GetSecond(), LATime.GetMinute(), LATime.GetHour(), LATime.GetDay(), LATime.GetMonth(),LATime.GetYear(),
									fl.IsReadOnly() , fl.IsDirectory ( ), fl.IsCompressed( ), fl.IsSystem( ),   fl.IsHidden( ),  fl.IsTemporary( ),fl.IsNormal( ),fl.IsArchived( ));
					}
					strcat(str,"\r");
					m_Comm.GPSendBlock(AnsiToDos(str,0),(int)strlen(str),1);
					fl.Close( );
				}
				job_flag=0;
				break;

			case -76:/* GP_TERM OPEN FILE */
			case -77:/* GP_TERM CLOSE FILE */
			case -78:/* GP_TERM FILE GETCHAR*/
			case -79:/* GP_TERM FILE PUTCHAR*/
			case -80:/* GP_TERM FILE GETSTR*/
			case -81:/* GP_TERM FILE PUTSTR*/
			case -82:/* GP_TERM FILE READBLOCK*/
			case -83:/* GP_TERM FILE WRITEBLOCK*/
			case -84:/* GP_TERM FILE SEEK*/
			case -85:/* GP_TERM FILE SEEKTOBEGIN*/
			case -86:/* GP_TERM FILE SEEKTOEND*/
			case -87:/* GP_TERM FILE FLUSH*/
			case -88:/* GP_TERM FILE GETLENGTH*/
			case -89:/* GP_TERM FILE SETLENGTH*/
			case -90:/* GP_TERM FILE GETPOSITION*/
			case -91:/* GP_TERM FILE GETSTATUS*/
			case -92:/* GP_TERM FILE LOCKRANGE*/
			case -93:/* GPTERM FILE UNLOCKRANGE*/
			case -94:/* GPTERM FILE SETCONV*/
			case -95:/* GPTERM FILE POSROLLBACK*/
			case -96:/* GPTERM FILE GPGetBlocksInfo*/
			case -97:/* GPTERM FILE FINDPLACE*/
				{
					char str[1000];
					int nFile=0,param1=0,param2=0;
					m_LastScanf=sscanf(InputBuffer2,"%d,%d,%d",&nFile,&param1,&param2);
					/////////////////////
					if (GPC.AjCheckState>120000) GPC.AjCheckState=0;
					SetKeybLock();	// AJ.CHECK ON
					/////////////////////

					if ((nFile<GP_NFILES && aGP_File[nFile]!=NULL) || job_flag==-76)
					switch(job_flag)
					{
					case -76:/* GP_TERM OPEN FILE */
						{
							int i333;
							for(i333=0;i333<GP_NFILES && aGP_File[i333]!=NULL;i333++);
#ifdef RUS
							if (i333==GP_NFILES) sprintf(str,"-1\x7FФайлов не может быть больше %d\r",GP_NFILES);
#else
							if (i333==GP_NFILES) sprintf(str,"-1\x7F No more then %d files\r",GP_NFILES);
#endif
							else
							{
								aGP_File[i333]=new GP_File;
								sprintf(str,"%d\r",i333);
								aGP_File[i333]->GPOpenFile(DosToAnsi(InputBuffer2),str);
								if (*str==0 || *str=='-')
								{
#ifdef RUS
									sprintf(str,"-1\x7FОШИБКА ОТКРЫТИЯ ФАЙЛА\r");
#else
									sprintf(str,"-1%cERROR OPENING FILE\r",127);
#endif
									delete aGP_File[i333];aGP_File[i333]=NULL;
								}
								AnsiToDos(str,1);
								m_Comm.GPSendLine(str);
							}
						}
						break;
					case -77:/* GP_TERM CLOSE FILE */
						delete aGP_File[nFile];aGP_File[nFile]=NULL;
						break;
					case -78:/* GP_TERM FILE GETCHAR*/
						{
							if (param1>1000000 || param1<1) param1=1;
							char *tmp=new char [param1*4+20];
							aGP_File[nFile]->GPGetChar(tmp,param1);
							strcat(tmp,"\r");
							m_Comm.GPSendLine(tmp);
							delete[] tmp;
						}
						break;
					case -79:/* GP_TERM FILE PUTCHAR*/
						aGP_File[nFile]->GPPutChar(param1);
						break;
					case -80:/* GP_TERM FILE GETSTR*/
						{
							char *tmp=NULL;
							if (param1>10000000 || param1<1) param1=1;
							aGP_File[nFile]->GPGetStr(&tmp,param1);
							if (tmp!=NULL)
							{
								strcat(tmp,"\r");
								m_Comm.GPSendLine(tmp);
								delete[] tmp;
							}
						}
						break;
					case -81:/* GP_TERM FILE PUTSTR*/
						{
							char *tmp=strchr(InputBuffer2,',');
							if (tmp++!=NULL) aGP_File[nFile]->GPPutStr(tmp);
						}
						break;
					case -82:/* GP_TERM FILE READBLOCK*/
						{
							char *tmp=new char [param1*2+4];
							aGP_File[nFile]->GPReadBlock(tmp,param1);
							strcat(tmp,"\r");
							m_Comm.GPSendLine(tmp);
							delete[] tmp;
						}
						break;
					case -83:/* GP_TERM FILE WRITEBLOCK*/
						{
							char *tmp=strchr(InputBuffer2,',');
							if (tmp++!=NULL) aGP_File[nFile]->GPWriteBlock(tmp);
						}
						break;
					case -84:/* GP_TERM FILE SEEK*/
						{
							__int64 param1_64=0;
							m_LastScanf=sscanf(InputBuffer2,"%d,%I64d",&nFile,&param1_64);
							aGP_File[nFile]->GPSeek(param1_64,param2);
						}
						break;
					case -85:/* GP_TERM FILE SEEKTOBEGIN*/
						aGP_File[nFile]->GPSeekToBegin();
						break;
					case -86:/* GP_TERM FILE SEEKTOEND*/
						aGP_File[nFile]->GPSeekToEnd();
						break;
					case -87:/* GP_TERM FILE FLUSH*/
						aGP_File[nFile]->GPFlush();
						break;
					case -88:/* GP_TERM FILE GETLENGTH*/
						{
							__int64 i64tmp=0;
							aGP_File[nFile]->GPGetLength(&i64tmp);
							sprintf(str,"%I64d\r",i64tmp);
							m_Comm.GPSendLine(str);
						}
						break;
					case -89:/* GP_TERM FILE SETLENGTH*/
						{
							__int64 param1_64=0;
							m_LastScanf=sscanf(InputBuffer2,"%d,%I64d",&nFile,&param1_64);
							aGP_File[nFile]->GPSetLength(param1_64);
						}
						break;
					case -90:/* GP_TERM FILE GETPOSITION*/
						{
							__int64 i64tmp=0;
							aGP_File[nFile]->GPGetPosition(&i64tmp);
							sprintf(str,"%I64d\r",i64tmp);
							m_Comm.GPSendLine(str);
						}
						break;
					case -91:/* GP_TERM FILE GETSTATUS*/
						aGP_File[nFile]->GPGetStatus(str);
						m_Comm.GPSendLine(str);
						break;
					case -92:/* GP_TERM FILE LOCKRANGE*/
						aGP_File[nFile]->GPLockRange(param1,param2);
						break;
					case -93:/* GPTERM FILE UNLOCKRANGE*/
						aGP_File[nFile]->GPUnLockRange(param1,param2);
						break;
					case -94:/* GPTERM FILE SETCONV*/
						aGP_File[nFile]->ConvON =param1;
						break;
					case -95:/* GPTERM FILE POSROLLBACK*/
						aGP_File[nFile]->GPPosRollBack();
						break;
					case -96:/* GPTERM FILE GPGetBlocksInfo*/
						{
							if (param1<32) param1=2048;
							char *tmp=new char [(ULONG)((aGP_File[nFile]->GetLength()*50)/param1+500)];
							aGP_File[nFile]->GPGetBlocksInfo(tmp,param1);
							strcat(tmp,"\r");
							m_Comm.GPSendLine(tmp);
							delete[] tmp;
						}
						break;
					case -97:/* GPTERM FILE FINDPLACE*/
						{
							char *tmp=strchr(InputBuffer2,',');
							char ostr[100]={0};
							__int64 ret=-1;
							if (tmp++!=NULL) ret=aGP_File[nFile]->GPFindPlace(tmp);
							if (ret!=0xFFFFFFFF)
								sprintf(str,"%I64d\r",ret);
							strcat(ostr,"\r");
							m_Comm.GPSendLine(ostr);
						}
						break;
					}
					else // ERROR
					switch(job_flag)
					{
					case -78:/* GP_TERM FILE GETCHAR*/
					case -80:/* GP_TERM FILE GETSTR*/
					case -82:/* GP_TERM FILE READBLOCK*/
					case -88:/* GP_TERM FILE GETLENGTH*/
					case -90:/* GP_TERM FILE GETPOSITION*/
					case -91:/* GP_TERM FILE GETSTATUS*/
					case -96:/* GPTERM FILE GPGetBlocksInfo*/
					case -97:/* GPTERM FILE FINDPLACE*/
#ifdef RUS
						sprintf(str,"!!!ОШИБКА ФАЙЛА (не открыт) %d !!!\r",nFile);
#else
						sprintf(str,"!!!FILE ERROR (not open) %d !!!\r",nFile);
#endif
						m_Comm.GPSendLine(str);
						break;
					}
				}
				///////////////////////////////////
				if (GPC.AjCheckState>1) GPC.AjCheckState-=2; else GPC.AjCheckState=123456;
				SetKeybLock(); // AJ.CHECK OFF
				///////////////////////////////////

				job_flag=0;
				break;
			case -98:/* GP_TERM FILE MKDIR*/
				{
					DosToAnsi(InputBuffer2);
					char *pos=InputBuffer2;
					do
					{
						pos=strchr(pos,'\\');
						if (pos!=NULL)
						{
							*pos=0;
							_mkdir(InputBuffer2);
							*(pos++)='\\';
						}
						else
							_mkdir(InputBuffer2);
					}
					while(pos!=NULL && *pos!=0);

					job_flag=0;
					break;
				}
			case -99:/*099 0 027 0 064 0 240 0 071 GP_TERM GP.FileFind*/
				{
					CFileFind ff;
					BOOL bFind=ff.FindFile(DosToAnsi(InputBuffer2),0);
					UINT ret=0;
					char *oStr=new char [100000];
					char *outpos=oStr;
					CTime LATime,CRTime,LWTime;
					*oStr=0;
					if (bFind)
					{
						do
						{
							ret=ff.FindNextFile();
							ff.GetLastAccessTime(LATime);
							ff.GetCreationTime(CRTime);
							ff.GetLastWriteTime(LWTime);
							if (outpos!=oStr)  *(outpos++)=0x7F;
							outpos+=sprintf(outpos,"%s\x7%I64d\x7%I64d\x7%2.2d\x7%2.2d\x7%2.2d\x7%2.2d\x7%2.2d\x7%4.4d\x7%I64d\x7%2.2d\x7%2.2d\x7%2.2d\x7%2.2d\x7%2.2d\x7%4.4d\x7%I64d\x7%2.2d\x7%2.2d\x7%2.2d\x7%2.2d\x7%2.2d\x7%4.4d\x7%d\x7%d\x7%d\x7%d\x7%d\x7%d\x7%d\x7%d",
										(LPCSTR)ff.GetFileName(),
										ff.GetLength() ,
										CRTime.GetTime(), CRTime.GetSecond(), CRTime.GetMinute(), CRTime.GetHour(), CRTime.GetDay(), CRTime.GetMonth(),CRTime.GetYear(),
										LWTime.GetTime(), LWTime.GetSecond(), LWTime.GetMinute(), LWTime.GetHour(), LWTime.GetDay(), LWTime.GetMonth(),LWTime.GetYear(),
										LATime.GetTime(), LATime.GetSecond(), LATime.GetMinute(), LATime.GetHour(), LATime.GetDay(), LATime.GetMonth(),LATime.GetYear(),
										ff.IsReadOnly() , ff.IsDirectory ( ), ff.IsCompressed( ), ff.IsSystem( ),   ff.IsHidden( ),  ff.IsTemporary( ),ff.IsNormal( ),ff.IsArchived( ));
						}	while(ret && (outpos-oStr)<99500);
						ff.Close();
					}
					if (((int)strlen(oStr)%30000)==0 && *oStr!=0)
						strcat(oStr,"_APPEND_END_OF_STRING\r");
					else
						strcat(oStr,"\r");
					m_Comm.GPSendBlock(AnsiToDos(oStr,0),(int)strlen(oStr));
					delete[] oStr;
					next_job=job_flag=0;
					break;
				}


			case -180:/* GP_TERM GP.FileDeleteDir 000180 0 027 0 064 0 240 0 152*/
				{
					GPDeleteDir(DosToAnsi(InputBuffer2));
					next_job=job_flag=0;
					break;
				}
			case -181:/* GP_TERM GP.FileCopyDir 000181 0 027 0 064 0 240 0 153*/
				{
					DosToAnsi(InputBuffer2);
					char *pos=strchr(InputBuffer2,';');
					if (pos!=NULL) *(pos++)=0;
					else pos="";

					GPCopyDir(InputBuffer2,pos);

					next_job=job_flag=0;
					break;
				}

			case -190:/* GP_TERM GP.FileSystemSub 000190 0 027 0 064 0 240 0 162*/
				{
					GetDocument()->DoFileSystemMethod(DosToAnsi(InputBuffer2),NULL);
					next_job=job_flag=0;
					break;
				}
			case -191:/* GP_TERM GP.FileSystemFn 000191 0 027 0 064 0 240 0 163*/
				{
					char *oStr=NULL;
					*GPC.StrTmpOut=0;
					GetDocument()->DoFileSystemMethod(DosToAnsi(InputBuffer2),&oStr);

					if (oStr==NULL) SendStringToPICK(GPC.StrTmpOut);
					else
					{
						SendStringToPICK(oStr);
						delete[] oStr;
					}

					next_job=job_flag=0;
					break;
				}


			case -200:/* GP_TERM GP.ScreenSub 000200 0 027 0 228 0 096*/
			case -201:/* GP_TERM GP.ScreenFn 000201 0 027 0 228 0 097*/
			case -202:/* GP_TERM GP.WindowSub 000202 0 027 0 228 0 098*/
			case -203:/* GP_TERM GP.WindowFn 000203 0 027 0 228 0 099*/
				{
					DosToAnsi(InputBuffer2);
					const char *fnStr=FindField(InputBuffer2,2,";");
					if (fnStr)
					{
						int IdScr=atoi(InputBuffer2);
						int IdWnd=atoi(ExtractField(ExtractField(InputBuffer2,1,";"),2,","));
						GPScreen *tmps=GetDocument()->GetScreenById(IdScr);
						if (tmps)
							switch(job_flag)
							{
							case -200:/* GP_TERM GP.ScreenSub 000200 0 027 0 228 0 096*/
								tmps->DoMethod(fnStr,NULL);
								break;
							case -201:/* GP_TERM GP.ScreenFn 000201 0 027 0 228 0 097*/
								{
									*GPC.StrTmpOut=0;
									tmps->DoMethod(fnStr,GPC.StrTmpOut);
									SendStringToPICK(GPC.StrTmpOut);
								}
								break;
							case -202:/* GP_TERM GP.WindowSub 000202 0 027 0 228 0 098*/
							case -203:/* GP_TERM GP.WindowFn 000203 0 027 0 228 0 099*/
								{
									GPWindow *tmpw=tmps->GPGetWindowById(IdWnd);
									if (tmpw)
										switch(job_flag)
										{
										case -202:/* GP_TERM GP.WindowSub 000202 0 027 0 228 0 098*/
											tmpw->DoMethod(fnStr,NULL);
											break;
										case -203:/* GP_TERM GP.WindowFn 000203 0 027 0 228 0 099*/
											{
												*GPC.StrTmpOut=0;
												tmpw->DoMethod(fnStr,GPC.StrTmpOut);
												SendStringToPICK(GPC.StrTmpOut);
											}
											break;
										}
								}
								break;
							}
					}
				}
				job_flag=next_job=0;
				break;


			default: // Продолжение выполнения сложных команд
					next_job=job_flag=0;
					break;
			}
		}
		else
		if (job_flag>-11000)
		{
			switch(job_flag)
			{
			case -1000: // printon
				if (GPC.EnableSlavePrint)
				{
					FILE *tempr=NULL;
					static int nball,npage,lastbyte;
					if (slave_nbcur==0)
					{
						lastbyte=0;
						nball=slave_nbcur=npage=1;
						#ifdef RUS
							if ((tempr=fopen("prnt.txt","wb"))==NULL) MessageBox("Ошибка печати задания\nОбратитесь к администратору",GPC.ErrBoxCaption,MB_OK |MB_ICONEXCLAMATION );
						#else
							if ((tempr=fopen("prnt.txt","wb"))==NULL) MessageBox("Printing error",GPC.ErrBoxCaption,MB_OK |MB_ICONEXCLAMATION );
						#endif

						if (tempr)	fclose(tempr);
						tempr=NULL;
						SendPickFlProgressDlg=new SendPickFlProgress(CWnd::FromHandle(GPC.m_hViewWnd)); // началось
						SendPickFlProgressDlg->Create(IDD_DIALOGSENDFILE,CWnd::FromHandle(GPC.m_hViewWnd));
						SendPickFlProgressDlg->SetWindowText(GPC.MsgBoxCaption);
						#ifdef RUS
							SendPickFlProgressDlg->SetDlgItemText(IDC_SFDEST,"Печать указанной информации");
						#else
							SendPickFlProgressDlg->SetDlgItemText(IDC_SFDEST,"Printing information");
						#endif
						SendPickFlProgressDlg->ShowWindow(SW_SHOW);
					}

					if((tempr=fopen("prnt.txt","ab"))==NULL)
						#ifdef RUS
							MessageBox("Ошибка печати задания\nОбратитесь к администратору",GPC.ErrBoxCaption,MB_OK |MB_ICONEXCLAMATION );
						#else
							MessageBox("Printing Error",GPC.ErrBoxCaption,MB_OK |MB_ICONEXCLAMATION );
						#endif


					const PTERMCAPESCITEM pON=m_TermCap.GetEscItemById(1000,m_TermCap.GetCurrentTerminal()->dwTermId);
					const PTERMCAPESCITEM pOFF=m_TermCap.GetEscItemById(1001,m_TermCap.GetCurrentTerminal()->dwTermId);

					while(i<nbyte)
					{
						if ((lastbyte==pOFF->seq.ch[pOFF->seq.dwSeqLen-1] && strncmp(InputBuffer+i,(const char *)pON->seq.ch,pON->seq.dwSeqLen))
							|| (!strncmp(InputBuffer+i,(const char *)pOFF->seq.ch,pOFF->seq.dwSeqLen) && i==nbyte-1))
						{
							if (SendPickFlProgressDlg!=NULL)
							{
								SendPickFlProgressDlg->GPClose();
								delete SendPickFlProgressDlg;
								SendPickFlProgressDlg=NULL;
							}
							if (tempr) fclose(tempr);
							tempr=NULL;
							m_PrintTransp=TRANSPRINT;

							if (slave_nbcur>3)
							{
								if (AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "PRINTASTXT",0))
								{
									CString csNotepadDumpSet="";
									CString csNotepadSet="";
									CDlgNotepadSet::GetNotepadSettings(csNotepadSet);
									CDlgNotepadSet::GetNotepadTypeSettings("SlavePrintPageSetup",csNotepadDumpSet);
									if (csNotepadDumpSet=="")			csNotepadDumpSet=csNotepadSet;
									if (csNotepadSet!=csNotepadDumpSet)	CDlgNotepadSet::SetNotepadSettings(csNotepadDumpSet);

									SHELLEXECUTEINFO ShExecInfo={0};
									ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
									ShExecInfo.fMask=0x00000010/*SEE_MASK_ICON*/|SEE_MASK_NOASYNC|SEE_MASK_NOCLOSEPROCESS;
									ShExecInfo.lpParameters = NULL;
									ShExecInfo.lpFile="NOTEPAD.EXE";
									ShExecInfo.hwnd=m_hWnd;
									char tmpcwd[500];
									*tmpcwd=0;
									_getcwd(tmpcwd,490);
									ShExecInfo.lpDirectory=tmpcwd;
									ShExecInfo.lpVerb="open";
									ShExecInfo.nShow=SW_HIDE;
									ShExecInfo.lpParameters=" /p \"prnt.txt\"";
									if (::ShellExecuteEx(&ShExecInfo)==FALSE)
									{
										ShExecInfo.lpParameters=NULL;
										ShExecInfo.lpFile="prnt.txt";
										ShExecInfo.lpVerb="print";
										::ShellExecuteEx(&ShExecInfo);
									}
									if (ShExecInfo.hProcess) 
									{
										DWORD dwExCode=STILL_ACTIVE;
										DWORD cntr=0;
										while(cntr++<1000 && ::GetExitCodeProcess(ShExecInfo.hProcess,&dwExCode) && dwExCode)
											Sleep(10);
									}

									if (csNotepadSet!=csNotepadDumpSet)
										CDlgNotepadSet::SetNotepadSettings(csNotepadSet);
								}
								else
								SendMessage(WM_COMMAND,AfxGetApp()->GetProfileInt(GPC.cs_RegTermViewSetName, "m_PrintDlg",1)==0?ID_FILE_PRINT_DIRECT:ID_FILE_PRINT);
							}

							if (lastbyte==pOFF->seq.ch[pOFF->seq.dwSeqLen-1]) i--;
							curent_inputbyte=-1; inputnbyte=forcounter=0; job_flag=0;
							nball=npage=slave_nbcur=0;
							lastbyte=0;
							break;
						}

						if (strncmp(InputBuffer+i,(const char *)pOFF->seq.ch,pOFF->seq.dwSeqLen) && strncmp(InputBuffer+i,(const char *)pON->seq.ch,pON->seq.dwSeqLen))
						{
							if (InputBuffer[i]!=0 && tempr) fputc(InputBuffer[i],tempr);
							if (SlaveVisible || m_HIDEVIEWMODE)
							{
								s->CharOutAW(InputBuffer[i]);
							}
							if (InputBuffer[i]==12) npage++;
							slave_nbcur++;
							if (slave_nbcur>nball && SendPickFlProgressDlg) SendPickFlProgressDlg->m_progress.SetRange32(0,nball=slave_nbcur*4);
							if ((slave_nbcur%427)==1 && SendPickFlProgressDlg)
							{
								char len[100];
#ifdef RUS
								sprintf(len,"Передано %d байт",slave_nbcur);
								SendPickFlProgressDlg->SetDlgItemText(IDC_SFLENGTH,len);
								SendPickFlProgressDlg->m_progress.SetPos(slave_nbcur);job_flag=-1000;
								sprintf(len,"Подготавливается страница  %d",npage);
								SendPickFlProgressDlg->SetDlgItemText(IDC_SFSORSE,len);
#else
								sprintf(len,"Trasfering %d bytes",slave_nbcur);
								SendPickFlProgressDlg->SetDlgItemText(IDC_SFLENGTH,len);
								SendPickFlProgressDlg->m_progress.SetPos(slave_nbcur);job_flag=-1000;
								sprintf(len,"Prepare page No %d",npage);
								SendPickFlProgressDlg->SetDlgItemText(IDC_SFSORSE,len);
#endif
							}
						}

						lastbyte=InputBuffer[i++];
					}
					if (tempr) fclose(tempr);
					tempr=NULL;
					if (job_flag!=0 && i!=nbyte) i=nbyte-1;
					curent_inputbyte=-1; inputnbyte=forcounter=0;
				}
				break;

			case -1102: /*BlockingSendStr input from host*/
				if ((GPC.m_uCurrInputBlock%50)==49)
				{
					char str[100];
					sprintf(str,"%c%c%c%d\x7F%d\r",250,250,58,48,GPC.m_uCurrInputBlock+1);
					AnsiToDos(str,0);
					m_Comm.GPSendBlock(str,(int)strlen(str));
				}

				{
					UINT ks=0,len=0,nbl;
					UINT cks=0;
					nbl=(InputBuffer2[0]-32)*48+InputBuffer2[1]-32;
					len=InputBuffer2[2]-32;
					ks=InputBuffer2[3]-32;
					BOOL requ=FALSE;

					if (len==(((int)strlen(InputBuffer2)-4)%64))
					{
						unsigned char *pos2=(unsigned char *)(InputBuffer2+3);
						while(*(++pos2)!=0)
							if (*pos2<=250 && *pos2>=32 && *pos2!=94 && *pos2!=91) cks+=*pos2;
						if ((cks%64)!=ks) requ=TRUE;
					}
					else  requ=TRUE;

					if (requ!=TRUE && nbl>0 && nbl<=300) GPC.arrInputBlocks[nbl-1]=InputBuffer2+4;

					if (GPC.arrInputBlocks[GPC.m_uCurrInputBlock]!="GPCIO")
					{
						BOOL flg=TRUE;
						char *bf=new char [nbyte-i+10];
						int j;
						for(j=i;j<nbyte;j++) bf[j-i]=InputBuffer[j];

						while(GPC.arrInputBlocks[GPC.m_uCurrInputBlock]!="GPCIO")
						{
							if (GPC.m_uCurrInputBlock+1==nbl) flg=FALSE;
							sprintf(InputBuffer,"%s\n",(LPCSTR)GPC.arrInputBlocks[GPC.m_uCurrInputBlock]);
							GPC.arrInputBlocks[GPC.m_uCurrInputBlock++]="GPCIO";
							if (GPC.m_uCurrInputBlock>=300) GPC.m_uCurrInputBlock=0;
							int tmpnext_job=next_job;
							int tmpjobflag=job_flag;
							job_flag=0;next_job=0;
							RemappingInput((int)strlen(InputBuffer));
							next_job=tmpnext_job;
							job_flag=tmpjobflag;
						}
						for(j=i;j<nbyte;j++) InputBuffer[j]=bf[j-i];
						delete[] bf;
						if (requ==FALSE && flg==TRUE) requ=TRUE;
					}
					else  requ=TRUE;

					if ( requ==TRUE)
					{
						char str[100];
						sprintf(str,"%c%c%c%d\x7F%d\r",250,250,58,49,GPC.m_uCurrInputBlock+1);
						AnsiToDos(str,0);
						m_Comm.GPSendBlock(str,(int)strlen(str));
					}
				}

				job_flag=0;
				break;
			case -1103: /*запрос пропущенного*/
				job_flag=0;
				break;

			case -1105: /*INPUT OUTPUT INFO FROM HOST 001105 0 027 0 005 0 035*/
				{
					UINT nIn=0,nOut=0;
					m_LastScanf=sscanf(InputBuffer2,"%d,%d",&nIn,&nOut);
					if (nIn!=GPC.m_uCurrInputBlock+1)
					{
						UINT i333;
						if (GPC.m_uCurrInputBlock+1>nIn)
							for(i333=GPC.m_uCurrInputBlock;i333<300;i333++)
								if (GPC.arrInputBlocks[i333]=="GPCIO")
								{
									char str[100];
									sprintf(str,"%c%c%c%d\x7F%d\r",250,250,58,49,i333+1);
									AnsiToDos(str,0);
									m_Comm.GPSendBlock(str,(int)strlen(str));
								}

						for(i333=0;i333<nIn-1;i333++)
							if (GPC.arrInputBlocks[i333]=="GPCIO")
							{
								char str[100];
								sprintf(str,"%c%c%c%d\x7F%d\r",250,250,58,49,i333+1);
								AnsiToDos(str,0);
								m_Comm.GPSendBlock(str,(int)strlen(str));
							}
					}
					if (nOut!=GPC.m_uCurrOutputBlock+1)
					{
						UINT i333;
						if (GPC.m_uCurrOutputBlock+1>nIn)
							for(i333=GPC.m_uCurrOutputBlock;i333<100;i333++)
								if (GPC.arrOutputBlocks[i333]!="GPCIO")
								{
									char *str=new char [GPC.arrOutputBlocks[i333].GetLength()+50];
									sprintf(str,"%c%c%c%d\x7F%d%s\r",250,250,58,50,i333+1,(LPCSTR)GPC.arrOutputBlocks[i333]);
									AnsiToDos(str,0);
									m_Comm.GPSendBlock(str,(int)strlen(str));
									delete[] str;
								}

						for(i333=0;i333<nIn-1;i333++)
							if (GPC.arrOutputBlocks[i333]!="GPCIO")
							{
								char *str=new char [GPC.arrOutputBlocks[i333].GetLength()+50];
								sprintf(str,"%c%c%c%d\x7F%d%s\r",250,250,58,50,i333+1,(LPCSTR)GPC.arrOutputBlocks[i333]);
								AnsiToDos(str,0);
								m_Comm.GPSendBlock(str,(int)strlen(str));
								delete[] str;
							}
					}
					job_flag=0;
				}
				break;
			case -1106: // LISTEN & CONNECT  PORT,WAITTIME,FLAGS
				{
					DWORD iPort=atoi(InputBuffer2)&0xFFFF;
					if (iPort) m_Comm.ListenPort=iPort;
					iPort=atoi(ExtractField(InputBuffer2,2,","));
					if (iPort) m_Comm.ListenTime=iPort;
					const char *fld3=FindField(InputBuffer2,3,",");
					if (fld3 && *fld3)
					{
						CString tmpfld3=fld3;
						tmpfld3.MakeUpper();
						m_Comm.SetTelnetFlag(tmpfld3.Find("TELNET",0)>=0?1:0);
					}
					m_Comm.m_ConnectionFlag=0x1;
					m_Comm.GPConnect();
					job_flag=0;
				}
				break;
			case -2007: // Download Function Keys     ESC:Z:Fn:TEXT:CHAR(13):CHAR(127)> where Fn - A for F1  B for F2 ....
			case -2008: // Download Function Keys  with slashes    ESC:Z:Fn:TEXT:CHAR(13):CHAR(127)> where Fn - A for F1  B for F2 ....
			case -2009: // Download Function Keys     ESC:Z:Fn:TEXT:CHAR(13):CHAR(127)> where Fn - A for F1  B for F2 ....
			case -2010: // Download Function Keys  with slashes    ESC:Z:Fn:TEXT:CHAR(13):CHAR(127)> where Fn - A for F1  B for F2 ....
				if (string_ptr)
				{
					if (*InputBuffer2>='@' && *InputBuffer2<='X')
					{
						DWORD dwVKFn[]={
							VK_F1,VK_F2,VK_F3,VK_F4,VK_F5,VK_F6,VK_F7,VK_F8,VK_F9,VK_F10,
							VK_F11,VK_F12,VK_F13,VK_F14,VK_F15,VK_F16,VK_F17,VK_F18,VK_F19,VK_F20,
							VK_F21,VK_F22,VK_F23,VK_F24,
						};
						char *tmp=new char [string_ptr*2+1000];
						char *postmp=tmp;
						int iPBuff;
						for(iPBuff=1;iPBuff<string_ptr;iPBuff++)
						{
							char chtmp=InputBuffer2[iPBuff];
							if (chtmp==0 || chtmp==10 || chtmp==13)
							{
								if (
									   (chtmp==0  && InputBuffer2[iPBuff+1]==13 && InputBuffer2[iPBuff+2]==10)
									|| (chtmp==0  && InputBuffer2[iPBuff+1]==10 && InputBuffer2[iPBuff+2]==13)
									|| (chtmp==10 && InputBuffer2[iPBuff+1]==13 && InputBuffer2[iPBuff+2]==0)
									|| (chtmp==10 && InputBuffer2[iPBuff+1]== 0 && InputBuffer2[iPBuff+2]==13)
									|| (chtmp==13 && InputBuffer2[iPBuff+1]==10 && InputBuffer2[iPBuff+2]==0)
									|| (chtmp==13 && InputBuffer2[iPBuff+1]== 0 && InputBuffer2[iPBuff+2]==10)
									)
								{
									*(postmp++)=13;
									iPBuff++;
									iPBuff++;
								}
								else
								if (
									   (chtmp==0  && InputBuffer2[iPBuff+1]==10)
									|| (chtmp==0  && InputBuffer2[iPBuff+1]==13)
									|| (chtmp==10 && InputBuffer2[iPBuff+1]== 0)
									|| (chtmp==10 && InputBuffer2[iPBuff+1]==13)
									|| (chtmp==13 && InputBuffer2[iPBuff+1]== 0)
									|| (chtmp==13 && InputBuffer2[iPBuff+1]==10)
									)
								{
									*(postmp++)=13;
									iPBuff++;
								}
								else *(postmp++)=chtmp;
							}
							else if ((job_flag==-2007 || job_flag==-2009) && chtmp=='\\') 
							{
								*(postmp++)=chtmp;
								*(postmp++)=chtmp;
							}
							else *(postmp++)=chtmp;
						}
						*(postmp++)=0;

						TERMCAPKBDITEM kbdItem;
						kbdItem.dwFlags=1;
						kbdItem.dwTermId=m_TermCap.GetCurrentTerminalId();
						kbdItem.dwVirtualKey=dwVKFn[*InputBuffer2-'@']*0x10000;
						kbdItem.Seq=tmp;
						m_TermCap.DeleteKbdItems(kbdItem);
						PTERMCAPKBDITEM pItem=m_TermCap.AddKbdItem();
						if (pItem)
						{
							pItem->dwVirtualKey=kbdItem.dwVirtualKey;
							pItem->dwTermId=kbdItem.dwTermId;
							pItem->dwFlags=kbdItem.dwFlags;
							pItem->Seq=kbdItem.Seq;
						}
						delete[] tmp;
					}
					else
					{
						s->CharOutAW(InputBuffer2,string_ptr);
					}

				}
				stopchar=123456;
				next_job=0;job_flag=0;string_ptr=0;	
				break;

			case -10021: // MESSAGEBOX  Part two
			case -10001: // MESSAGEBOX  Part two
				if (forcounter<1)
				{
					char *pos2=strchr(InputBuffer2,0x1);
					if (pos2)	*(pos2++)=0;
					strncpy(name_curent,InputBuffer2,1024);
					name_curent[1024]=0;
					if (pos2)	strcpy(InputBuffer2,pos2);
					string_ptr=0; 
					if (!pos2)
					{
						forcounter++;
						job_flag=-1;
						break;
					}
				}

				{
					UINT mbTYPE[7]={MB_ABORTRETRYIGNORE,MB_OK,MB_OKCANCEL,MB_RETRYCANCEL,MB_YESNO,MB_YESNOCANCEL,MB_CANCELTRYCONTINUE,};
					UINT mbMODALITY[3]={MB_APPLMODAL,MB_SYSTEMMODAL,MB_TASKMODAL,};
					UINT mbICONS[4]={MB_ICONEXCLAMATION,MB_ICONINFORMATION,MB_ICONQUESTION,MB_ICONSTOP,};
					UINT mbDEFBUT[3]={MB_DEFBUTTON1,MB_DEFBUTTON2,MB_DEFBUTTON3,};
					{
						HWND tmp=::GetFocus();
						UINT res=CWnd::FromHandle(tmp)->MessageBox(DosToAnsi(ReplaceSpec(InputBuffer2)),ReplaceSpec(DosToAnsi(name_curent)),
							mbTYPE[(m_TermCap.m_Vars.Pos_X%10)%10]|mbMODALITY[(m_TermCap.m_Vars.Pos_X/10)%3]|mbICONS[(m_TermCap.m_Vars.Pos_Y%10)%4]|mbDEFBUT[(m_TermCap.m_Vars.Pos_Y/10)%3]);
						if (job_flag==-10001 && (m_TermCap.m_Vars.Pos_X/10)<4)
							switch(res)
							{
							case IDABORT:	SendChar('1'); break;
							case IDCANCEL:	SendChar('2'); break;
							case IDIGNORE:	SendChar('3'); break;
							case IDNO:		SendChar('4'); break;
							case IDOK:		SendChar('5'); break;
							case IDRETRY:	SendChar('6'); break;
							case IDYES:		SendChar('7'); break;
							default:		SendChar('0'); break;
							}
						if (tmp!=NULL) ::SetFocus(tmp);
					}
					curent_inputbyte=-1; forcounter=0; job_flag=0;
				}
				break;
			case -10005: /* Resize active*/
				{
					Size ss(80,25);
					m_LastScanf=sscanf(InputBuffer2,"%d,%d",&ss.Width,&ss.Height);
					SendChar(GetDocument()->ResizeActiveScr(ss)+48);
					s=GetDocument()->GetActiveScreen();
					job_flag=0;
				}
				break;
			case -10008: /*GP_TERM Text HorLine*/
			case -10009: /*GP_TERM Text VerLine*/
				{
					UINT uX=0,uY=0,uLen=1,uTyp=0;
					m_LastScanf=sscanf(InputBuffer2,"%d,%d,%d,%d",&uX,&uY,&uLen,&uTyp);
					if (job_flag==-10008)	s->TextHorLine(uX,uY,uTyp,uLen);
					else 					s->TextVerLine(uX,uY,uTyp,uLen);
					job_flag=0;
				}
				break;
			case -10018: /* SET term Title */
				if (_stricmp(InputBuffer2,"OpenQM")==0)
				{
					m_Comm.DelimiterSrc1=254;
					m_Comm.DelimiterSrc2=253;
					m_Comm.DelimiterSrc3=252;
					m_Comm.DelimiterSrc4=251;
					m_Comm.DelimiterSrc5=250;
					m_Comm.DelimiterSrc6=255;
					m_Comm.DelimiterIn1 =182;
					m_Comm.DelimiterIn2 =181;
					m_Comm.DelimiterIn3 =180;
					m_Comm.DelimiterIn4 =179;
					m_Comm.DelimiterIn5 =178;
					m_Comm.DelimiterIn6 =177;
					m_Comm.SaveDelimiters();

				}
				else
				if (_stricmp(InputBuffer2,"D3")==0)
				{
					m_Comm.DelimiterSrc1='^';
					m_Comm.DelimiterSrc2=']';
					m_Comm.DelimiterSrc3='\\';
					m_Comm.DelimiterSrc4=4;
					m_Comm.DelimiterSrc5=5;
					m_Comm.DelimiterSrc6=6;
					m_Comm.DelimiterIn1 ='^';
					m_Comm.DelimiterIn2 =']';
					m_Comm.DelimiterIn3 ='\\';
					m_Comm.DelimiterIn4 =4;
					m_Comm.DelimiterIn5 =5;
					m_Comm.DelimiterIn6 =6;
					m_Comm.SaveDelimiters();
				}
				else
				if (!*InputBuffer2)
				{
					const char *delimStr=" - ";
					if (GPC.termCaption=="" || *m_Comm.GetComment()==0)
						delimStr="";

					sprintf(InputBuffer2,"%s%s%s",(LPCSTR)m_Comm.GetComment(),delimStr,(LPCSTR)GPC.termCaption);
					GetDocument()->SetTitle(InputBuffer2);
					GPC.termCaption=InputBuffer2;
				}
				else	GetDocument()->SetTitle(DosToAnsi(InputBuffer2));
				job_flag=0;
				break;
			case -10022: //GP.CListMakerSub 010022 0 027 0 222 0 056
				GPC.m_ListMaker.DoMethod(DosToAnsi(InputBuffer2),NULL);
				job_flag=0;
				break;
			case -10023: //GP.CListMakerFn  010023 0 027 0 222 0 057
				{
					char *oStr=NULL;
					GPC.m_ListMaker.DoMethod(DosToAnsi(InputBuffer2),&oStr);
					if (oStr!=NULL)
					{
						UINT len= (int)strlen(AnsiToDos(oStr,0));
						strcpy(oStr+len,"\r");
						m_Comm.GPSendBlock(oStr,len+1);
						delete[] oStr;
					}
					else m_Comm.GPSendBlock("\r",1);
					job_flag=0;
				}
				break;
			case -10025: //GP.SetInsertMode(InsertMode) 010025 0 027 0 222 0 059
				GPC.m_bInsertMode=atoi(InputBuffer2);
				job_flag=0;
				break;
			case -10026: //GP.SetTermTips(Text) GP_TERM Set Tips 010026 0 027 0 222 0 060
				strncpy(GPC.TermTip,DosToAnsi(InputBuffer2),250);
				GPC.TermTip[250]=0;
				job_flag=0;
				break;

			case -10027: //GP.OpenFileDialogEx(Text)
			case -10028: //GP.SaveFileDialogEx(Text)
				{
					char *cstl[25]={"OFN_ALLOWMULTISELECT|","OFN_CREATEPROMPT|","OFN_ENABLEHOOK|","OFN_ENABLESIZING|","OFN_EXPLORER|","OFN_EXTENSIONDIFFERENT|","OFN_FILEMUSTEXIST|","OFN_HIDEREADONLY|","OFN_LONGNAMES|","OFN_NOCHANGEDIR|","OFN_NODEREFERENCELINKS|","OFN_NOLONGNAMES|","OFN_NONETWORKBUTTON|","OFN_NOREADONLYRETURN|","OFN_NOTESTFILECREATE|","OFN_OVERWRITEPROMPT|","OFN_PATHMUSTEXIST|","OFN_READONLY|","OFN_SHAREAWARE|","OFN_SHOWHELP|","OFN_ENABLETEMPLATE|","OFN_ENABLETEMPLATEHANDLE|","OFN_NOVALIDATE|","OFN_DONTADDTORECENT|","OFN_FORCESHOWHIDDEN|",};
					UINT ustl[25]={OFN_ALLOWMULTISELECT,OFN_CREATEPROMPT,OFN_ENABLEHOOK,OFN_ENABLESIZING,OFN_EXPLORER,OFN_EXTENSIONDIFFERENT,OFN_FILEMUSTEXIST,OFN_HIDEREADONLY,OFN_LONGNAMES,OFN_NOCHANGEDIR,OFN_NODEREFERENCELINKS,OFN_NOLONGNAMES,OFN_NONETWORKBUTTON,OFN_NOREADONLYRETURN,OFN_NOTESTFILECREATE,OFN_OVERWRITEPROMPT,OFN_PATHMUSTEXIST,OFN_READONLY,OFN_SHAREAWARE,OFN_SHOWHELP,OFN_ENABLETEMPLATE,OFN_ENABLETEMPLATEHANDLE,OFN_NOVALIDATE,OFN_DONTADDTORECENT,OFN_FORCESHOWHIDDEN,};
					CString str,str2;
					char *pos;
					char *postmpconst;

					DosToAnsi(InputBuffer2);

					OPENFILENAME opf={0};
					#ifdef W_95
						opf.lStructSize=OPENFILENAME_SIZE_VERSION_400;
					#else
						#ifdef W_NT
							opf.lStructSize=OPENFILENAME_SIZE_VERSION_400;
						#else
							opf.lStructSize=sizeof(OPENFILENAME);
						#endif
					#endif
					opf.hwndOwner=GPC.m_hViewWnd;
					opf.lpstrFile = new char [50000];
					*opf.lpstrFile=0;
					opf.nMaxFile =49900;
					int k;
					for(k=0;k<25;k++)
						if (strstr(InputBuffer2,cstl[k])!=NULL) opf.Flags|=ustl[k];

					opf.Flags|=OFN_NOCHANGEDIR;
					opf.lpstrFilter=NULL;
					////// FILTER=Text Files,*.TXT|Excel,*.xls

					if ((pos=strstr(InputBuffer2,"FILTER="))!=NULL)
					{
						pos+=7;
						opf.lpstrFilter=postmpconst=new char [(int)strlen(pos)+10];
						*postmpconst=0;
						pos=strcpy(postmpconst,pos);

						while(*pos!=0 && (*pos!=';' || pos[1]=='*'))
						{
							if (*pos==',' || *pos=='|' ) *pos=0;
							pos++;
						}
						*(pos++)=0;
						*(pos++)=0;
					}

					if ((pos=strstr(InputBuffer2,"FILTERC="))!=NULL)
					{
						pos+=8;
						opf.nMaxCustFilter=1000;
						opf.lpstrCustomFilter=new char [opf.nMaxCustFilter];
						pos=strcpy(opf.lpstrCustomFilter,pos);

						while(*pos!=0 && (*pos!=';' || pos[1]=='*'))
						{
							if (*pos==',' || *pos=='|' ) *pos=0;
							pos++;
						}
						*(pos++)=0;
						*(pos++)=0;
					}


					opf.nFilterIndex=1;
					if ((pos=strstr(InputBuffer2,"FILTERINDEX="))!=NULL)
						opf.nFilterIndex=atoi(pos+12);

					if ((pos=strstr(InputBuffer2,"FILE="))!=NULL)
					{
						pos=strcpy(opf.lpstrFile,pos+5);
						if ((pos=strchr(pos,';'))!=NULL) *pos=0;
					}

					if ((pos=strstr(InputBuffer2,"FILETITLE="))!=NULL)
					{
						pos=lstrcpyn(opf.lpstrFileTitle,pos+10,opf.nMaxFileTitle);
						if ((pos=strchr(pos,';'))!=NULL) *pos=0;
					}

					if ((pos=strstr(InputBuffer2,"INITDIR="))!=NULL)
					{
						pos+=8;
						opf.lpstrInitialDir=postmpconst=new char [(int)strlen(pos)+10];
						pos=strcpy(postmpconst,pos);
						if ((pos=strchr(pos,';'))!=NULL) *pos=0;
					}

					if ((pos=strstr(InputBuffer2,"DLGTITLE="))!=NULL)
					{
						pos+=9;
						opf.lpstrTitle=postmpconst=new char [(int)strlen(pos)+10];
						pos=strcpy(postmpconst,pos);
						if ((pos=strchr(pos,';'))!=NULL) *pos=0;
					}

					if ((pos=strstr(InputBuffer2,"DEFEXT="))!=NULL)
					{
						pos+=7;
						opf.lpstrDefExt=postmpconst=new char [(int)strlen(pos)+10];
						pos=strcpy(postmpconst,pos);
						if ((pos=strchr(pos,';'))!=NULL) *pos=0;
					}

					if ((job_flag==-10028?::GetOpenFileName(&opf): ::GetSaveFileName(&opf))==0)
						str="CANCEL";
					else
					{
						str.Format("OK\x7F%s\x7F",opf.lpstrFileTitle?opf.lpstrFileTitle:"");

						pos=opf.lpstrFile;

						if (pos!=NULL)
						{
							char *pss=pos;
							while(*pos!=0 || ((opf.Flags&OFN_ALLOWMULTISELECT)==OFN_ALLOWMULTISELECT && pos[1]!=0))
							{
								if (pos[1]==0)
								{
									str+=pss;
									if (pos[2]!=0) str+="\x7";
									pss=pos+2;
								}
								pos++;
							}
						}
						str+="\x7F";

						pos=opf.lpstrCustomFilter;
						if (pos!=NULL)
						{
							char *pss=pos;
							while(*pos!=0 && pos[1]!=0)
							{
								if (pos[1]==0)
								{
									str+=pss;
									if (pos[2]!=0) str+="\x7";
									pss=pos+2;
								}
								pos++;
							}
						}

						str2.Format("\x7F%d",opf.nFilterIndex);
						str+=str2;
					}

					if (opf.lpstrFilter!=NULL)			delete[] (char *)	opf.lpstrFilter;
					if (opf.lpstrCustomFilter!=NULL)	delete[]			opf.lpstrCustomFilter;
					if (opf.lpstrInitialDir!=NULL)		delete[] (char *)	opf.lpstrInitialDir;
					if (opf.lpstrTitle!=NULL)			delete[] (char *)	opf.lpstrTitle;
					if (opf.lpstrDefExt!=NULL)			delete[] (char *)	opf.lpstrDefExt;

					str+="\r";
					AnsiToDos(str,str,0);
					m_Comm.GPSendBlock(str,str.GetLength());

					delete[] opf.lpstrFile;

				}
				job_flag=0;
				break;

			case -10029: // GP_TERM Set Info line (Title) stop by ^G or \r of \n or ^@
				if (!*InputBuffer2 || !string_ptr)
				{
					const char *delimStr=" - ";
					if (GPC.termCaption=="" || *m_Comm.GetComment()==0)
						delimStr="";

					sprintf(InputBuffer2,"%s%s%s",(LPCSTR)m_Comm.GetComment(),delimStr,(LPCSTR)GPC.termCaption);
					GetDocument()->SetTitle(InputBuffer2);
					GPC.termCaption=InputBuffer2;
				}
				else
				{
					InputBuffer2[string_ptr]=0;
					GetDocument()->SetTitle(DosToAnsi(InputBuffer2));
				}
				stopchar=123456;
				next_job=0;job_flag=0;string_ptr=0;	
				break;


			default: // Продолжение выполнения сложных команд
					next_job=job_flag=0;
					break;
			}
		}
		else
		if (job_flag>-12000)
		{
			switch(job_flag)
			{
			case -11000: /* CREATE OBJECT */
				GetDocument()->CreateUnit(DosToAnsi(InputBuffer2),GPC.m_hViewWnd);
				job_flag=0;
				break;
			case -11002: /* DELETE OBJECT */
				{
					char Ch='S';
					m_LastScanf=sscanf(InputBuffer2,"%c,%d,%d",&Ch,&m_TermCap.m_Vars.IdScr,&m_TermCap.m_Vars.typeUnit);
					if (Ch=='S')	GetDocument()->DeleteScrUnit(m_TermCap.m_Vars.IdScr,m_TermCap.m_Vars.typeUnit, TRUE);
					else			GetDocument()->DeleteDlgUnit(m_TermCap.m_Vars.IdScr,m_TermCap.m_Vars.typeUnit, TRUE);
				}
				job_flag=0;
				break;
			case -11003: /* PROPERTY OBJECT */
				{
					char Ch='S';
					m_LastScanf=sscanf(InputBuffer2,"%c,%d,%d",&Ch,&m_TermCap.m_Vars.IdScr,&m_TermCap.m_Vars.typeUnit);
					if (Ch=='S')	GetDocument()->GPSetScrUnitProperty(m_TermCap.m_Vars.IdScr,m_TermCap.m_Vars.typeUnit,DosToAnsi(InputBuffer2));
					else			GetDocument()->GPSetDlgUnitProperty(m_TermCap.m_Vars.IdScr,m_TermCap.m_Vars.typeUnit,DosToAnsi(InputBuffer2));
				}
				job_flag=0;
				break;

			case -11006: /* SET DEFAULT LOGFONT */
				job_flag=0;
				break;

			case -11009: /*DoObjSub*/
				GetDocument()->DoObjectMethod(DosToAnsi(InputBuffer2),FALSE);
				if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwNMethodsSubObj++;
				job_flag=0;
				break;
			case -11010: /*DoObjFun*/
				GetDocument()->DoObjectMethod(DosToAnsi(InputBuffer2),TRUE);
				if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwNMethodsFnObj++;
				job_flag=0;
				break;
			case -11011: /*ADD MESSAGE*/
				{
					char Ch='S';
					m_LastScanf=sscanf(InputBuffer2,"%c,%d,%d",&Ch,&m_TermCap.m_Vars.IdScr,&m_TermCap.m_Vars.typeUnit);
					char *pos=strchr(InputBuffer2,';');
					if (pos++!=NULL && m_TermCap.m_Vars.IdScr>=0 && m_TermCap.m_Vars.typeUnit>=0)
					{
						if (m_TermCap.m_Vars.typeUnit>0)
						{
							if (Ch=='S')
							{
								GPUnit *tmp=GetDocument()->GetScrUnit(m_TermCap.m_Vars.IdScr,m_TermCap.m_Vars.typeUnit);
								if (tmp!=NULL) tmp->GPAddMessage(pos);
							}
							else
							{
								GPUnit *tmp=GetDocument()->GetDlgUnit(m_TermCap.m_Vars.IdScr,m_TermCap.m_Vars.typeUnit);
								if (tmp!=NULL) tmp->GPAddMessage(pos);
							}
						}
						else
						{ // ADD ObjScrMessage()
							if (Ch=='S') ;
							else
							if(m_TermCap.m_Vars.IdScr<MAX_OBJDLG)
							{
								if (GetDocument()->a_GPObjType[m_TermCap.m_Vars.IdScr]==0)
								{
									 if (GetDocument()->a_GPObjDialog[m_TermCap.m_Vars.IdScr]!=NULL)
										GetDocument()->a_GPObjDialog[m_TermCap.m_Vars.IdScr]->GPAddMessage(pos);
								}
								else
								{
									 if (GetDocument()->a_GPObjFrame[m_TermCap.m_Vars.IdScr]!=NULL)
										GetDocument()->a_GPObjFrame[m_TermCap.m_Vars.IdScr]->GPAddMessage(pos);
								}
							}
						}
					}
				}
				job_flag=0;
				break;
			case -11012: /*DELETE MESSAGE*/
				{
					char Ch='S';
					m_LastScanf=sscanf(InputBuffer2,"%c,%d,%d",&Ch,&m_TermCap.m_Vars.IdScr,&m_TermCap.m_Vars.typeUnit);
					char *pos=strchr(InputBuffer2,';');
					if (pos++!=NULL && m_TermCap.m_Vars.IdScr>=0 && m_TermCap.m_Vars.typeUnit>=0)
					{
						if (m_TermCap.m_Vars.typeUnit>0)
						{
							if (Ch=='S')
							{
								GPUnit *tmp=GetDocument()->GetScrUnit(m_TermCap.m_Vars.IdScr,m_TermCap.m_Vars.typeUnit);
								if (tmp!=NULL) tmp->GPDeleteMessage(pos);
							}
							else
							{
								GPUnit *tmp=GetDocument()->GetDlgUnit(m_TermCap.m_Vars.IdScr,m_TermCap.m_Vars.typeUnit);
								if (tmp!=NULL) tmp->GPDeleteMessage(pos);
							}
						}
						else
						{ // DELETE delete ObjScrMessage()

							if (Ch=='S') ;
							else
								if(m_TermCap.m_Vars.IdScr<MAX_OBJDLG)
								{

									if (GetDocument()->a_GPObjType[m_TermCap.m_Vars.IdScr]==0)
									{
										 if (GetDocument()->a_GPObjDialog[m_TermCap.m_Vars.IdScr]!=NULL)
											GetDocument()->a_GPObjDialog[m_TermCap.m_Vars.IdScr]->GPDeleteMessage(pos);
									}
									else
									{
										 if (GetDocument()->a_GPObjFrame[m_TermCap.m_Vars.IdScr]!=NULL)
											GetDocument()->a_GPObjFrame[m_TermCap.m_Vars.IdScr]->GPDeleteMessage(pos);
									}
								}
						}
					}
				}
				job_flag=0;
				break;

			case -11013: /*DELETE ALL MESSAGES*/
				{
					char Ch='S';
					m_LastScanf=sscanf(InputBuffer2,"%c,%d,%d",&Ch,&m_TermCap.m_Vars.IdScr,&m_TermCap.m_Vars.typeUnit);
						if (m_TermCap.m_Vars.typeUnit>0)
						{
							if (Ch=='S')
							{
								GPUnit *tmp=GetDocument()->GetScrUnit(m_TermCap.m_Vars.IdScr,m_TermCap.m_Vars.typeUnit);
								if (tmp!=NULL) tmp->GPDeleteAllMessage();
							}
							else
							{
								GPUnit *tmp=GetDocument()->GetDlgUnit(m_TermCap.m_Vars.IdScr,m_TermCap.m_Vars.typeUnit);
								if (tmp!=NULL) tmp->GPDeleteAllMessage();
							}
						}
						else
						{ // DELETE ALL ObjScrMessage()
							if (Ch=='S') ;
							else
								if(m_TermCap.m_Vars.IdScr<MAX_OBJDLG)
								{
									if (GetDocument()->a_GPObjType[m_TermCap.m_Vars.IdScr]==0)
									{
										 if (GetDocument()->a_GPObjDialog[m_TermCap.m_Vars.IdScr]!=NULL)
											GetDocument()->a_GPObjDialog[m_TermCap.m_Vars.IdScr]->GPDeleteAllMessage();
									}
									else
									{
										 if (GetDocument()->a_GPObjFrame[m_TermCap.m_Vars.IdScr]!=NULL)
											GetDocument()->a_GPObjFrame[m_TermCap.m_Vars.IdScr]->GPDeleteAllMessage();
									}
								}
						}
				}
				job_flag=0;
				break;
			case -11014: /*GP_TERM OBJECT SUBROUTINEEX 011014 0 027 0 223 0 047*/
				GetDocument()->DoObjectMethodEx(DosToAnsi(InputBuffer2),FALSE);
				if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwNMethodsSubObj++;
				job_flag=0;
				break;
			case -11015: /*GP_TERM OBJECT FUNCTIONEX 011015 0 027 0 223 0 048*/
				GetDocument()->DoObjectMethodEx(DosToAnsi(InputBuffer2),TRUE);
				if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwNMethodsFnObj++;
				job_flag=0;
				break;
			case -11016: /*GP_TERM OBJECT GP.ScrObjAddMMSG GP.DlgObjAddMMSG 0011016 0 027 0 223 0 049*/
				{
					//CRT CHAR(27):CHAR(223):CHAR(49):"D,":IdDlg-1:",":IdObj:",":IdDlgDest-1:",":IdObjDest:",":OnTimer:",":OffTimer:CHAR(1):Message:CHAR(1):OffMessage:CHAR(1):OnProp:CHAR(1):OffProp:CHAR(1):oOnSub:CHAR(1):oOffSub

					char Ch='S';
					UINT vIdDlg=0,Unit=0,vIdDlgDest=0,UnitDest=0,OnTimer=0,OffTimer=0;
					m_LastScanf=sscanf(InputBuffer2,"%c,%d,%d,%d,%d,%d,%d",&Ch,&vIdDlg,&Unit,&vIdDlgDest,&UnitDest,&OnTimer,&OffTimer);
					DosToAnsi(InputBuffer2);

					char *Message,*OffMessage,*OnProp,*OffProp,*OnSub,*OffSub;
					Message=strchr(InputBuffer2,1);
					if (Message!=NULL) *(Message++)=0;
					else Message="";
					OffMessage=strchr(Message,1);
					if (OffMessage!=NULL) *(OffMessage++)=0;
					else OffMessage="";
					OnProp=strchr(OffMessage,1);
					if (OnProp!=NULL) *(OnProp++)=0;
					else OnProp="";
					OffProp=strchr(OnProp,1);
					if (OffProp!=NULL) *(OffProp++)=0;
					else OffProp="";
					OnSub=strchr(OffProp,1);
					if (OnSub!=NULL) *(OnSub++)=0;
					else OnSub="";
					OffSub=strchr(OnSub,1);
					if (OffSub!=NULL) *(OffSub++)=0;
					else OffSub="";
					char msgon[100],msgoff[100];
					strncpy(msgon,Message,95);
					msgon[95]=0;
					strncpy(msgoff,OffMessage,95);
					msgoff[95]=0;
					char *postmp=strchr(msgon,';');
					if (postmp!=NULL) *postmp=0;
					postmp=strchr(msgoff,';');
					if (postmp!=NULL) *postmp=0;

					if (vIdDlg>=0 && Unit>=0)
					{
						if (Unit>0)
						{
							if (Ch=='S')
							{
								GPUnit *tmp=GetDocument()->GetScrUnit(vIdDlg,Unit);
								GPUnit *tmpd=GetDocument()->GetScrUnit(vIdDlgDest,UnitDest);
								if (tmp!=NULL) tmp->GPMSG->AddMMesager((void *)tmpd,OnProp,OffProp,OnSub,OffSub,Message,OffMessage,msgon,msgoff,OnTimer,OffTimer);
							}
							else
							{
								GPUnit *tmp=GetDocument()->GetDlgUnit(vIdDlg,Unit);
								GPUnit *tmpd=GetDocument()->GetDlgUnit(vIdDlgDest,UnitDest);
								if (tmp!=NULL) tmp->GPMSG->AddMMesager((void *)tmpd,OnProp,OffProp,OnSub,OffSub,Message,OffMessage,msgon,msgoff,OnTimer,OffTimer);
							}
						}
						else
						{ // ADD ObjScrMessage()
							if (Ch=='S') ;
							else
							if(m_TermCap.m_Vars.IdScr<MAX_OBJDLG)
							{
								CGP_TermDoc *mTmpdoc=GetDocument();
								GPUnit *tmpd=NULL;
								GPUnit *tmp=NULL;
								if (mTmpdoc->a_GPObjType[vIdDlg]==0)
								{
									tmp=mTmpdoc->GetScrUnit(0,0);
									tmpd=mTmpdoc->GetScrUnit(vIdDlgDest,UnitDest);
								}
								else
								{
									tmp=mTmpdoc->GetDlgUnit(vIdDlg,0);
									tmpd=mTmpdoc->GetDlgUnit(vIdDlgDest,UnitDest);
								}

								if (tmp && tmp->GPMSG)
									tmp->GPMSG->AddMMesager((void *)tmpd,OnProp,OffProp,OnSub,OffSub,Message,OffMessage,msgon,msgoff,OnTimer,OffTimer);
							}
						}
					}
				}

				job_flag=0;
				break;
			case -11017: /*GP_TERM OBJECT GP.ScrObjDelMMSG GP.DlgObjDelMMSG 0011016 0 027 0 223 0 050*/
				{
					//CRT CHAR(27):CHAR(223):CHAR(50):"D,":IdDlg-1:",":IdObj:",":IdDlgDest-1:",":IdObjDest:CHAR(1):Message:
					char Ch='S';
					UINT vIdDlg=0,Unit=0,vIdDlgDest=0,UnitDest=0;
					m_LastScanf=sscanf(InputBuffer2,"%c,%d,%d,%d,%d",&Ch,&vIdDlg,&Unit,&vIdDlgDest,&UnitDest);
					DosToAnsi(InputBuffer2);

					char *Message;
					Message=strchr(InputBuffer2,1);
					if (Message!=NULL) *(Message++)=0;
					else Message="";

					if (vIdDlg>=0 && Unit>=0)
					{
						if (Unit>0)
						{
							if (Ch=='S')
							{
								GPUnit *tmp=GetDocument()->GetScrUnit(vIdDlg,Unit);
								GPUnit *tmpd=GetDocument()->GetScrUnit(vIdDlgDest,UnitDest);
								if (tmp!=NULL) tmp->GPMSG->DelMMesager((void *)tmpd,Message);
							}
							else
							{
								GPUnit *tmp=GetDocument()->GetDlgUnit(vIdDlg,Unit);
								GPUnit *tmpd=GetDocument()->GetDlgUnit(vIdDlgDest,UnitDest);
								if (tmp!=NULL) tmp->GPMSG->DelMMesager((void *)tmpd,Message);
							}
						}
						else
						{ // DEL ObjScrMessage()
							if (Ch=='S') ;
							else
							if(m_TermCap.m_Vars.IdScr<MAX_OBJDLG)
							{
								if (GetDocument()->a_GPObjType[vIdDlg]==0)
								{
									GPUnit *tmpd=GetDocument()->GetScrUnit(vIdDlgDest,UnitDest);
									GPUnit *tmp=GetDocument()->GetScrUnit(vIdDlg,0);
									if (tmp && tmp->GPMSG)	tmp->GPMSG->DelMMesager((void *)tmpd,Message);
								}
								else
								{
									GPUnit *tmpd=GetDocument()->GetDlgUnit(vIdDlgDest,UnitDest);
									GPUnit *tmp=GetDocument()->GetDlgUnit(vIdDlg,0);
									if (tmp && tmp->GPMSG)	tmp->GPMSG->DelMMesager((void *)tmpd,Message);
								}
							}
						}
					}
				}
				job_flag=0;
				break;
			case -11018: /*GP_TERM OBJECT GP.ScrObjDelMMSG GP.DlgObjDelAllMMSG 0011016 0 027 0 223 0 051*/
				{
					//CRT CHAR(27):CHAR(223):CHAR(51):"D,":IdDlg-1:",":IdObj
					char Ch='S';
					UINT vIdDlg=0,Unit=0;
					m_LastScanf=sscanf(InputBuffer2,"%c,%d,%d",&Ch,&vIdDlg,&Unit);
					if (vIdDlg>=0 && Unit>=0)
					{
						GPUnit *tmp=NULL;
						if (Unit>0)
						{
							if (Ch=='S')
								tmp=GetDocument()->GetScrUnit(vIdDlg,Unit);
							else
								tmp=GetDocument()->GetDlgUnit(vIdDlg,Unit);
						}
						else
						{ // DEL ObjScrMessage()
							if (Ch!='S' && m_TermCap.m_Vars.IdScr<MAX_OBJDLG)
								tmp=GetDocument()->GetDlgUnit(vIdDlg,0);
						}
						if (tmp!=NULL) tmp->GPMSG->DelAllMMesager();
					}
				}
				job_flag=0;
				break;

			default: // Продолжение выполнения сложных команд
					next_job=job_flag=0;
					break;
			}
		}
		else
		if (job_flag>-13000)
		{
			switch(job_flag)
			{
			case -12000: /* Create CommonDialog */
			{
				char *oStr=new char [20000];
				*oStr=0;
				DosToAnsi(InputBuffer2);
				GPCommonDlg(InputBuffer2,oStr);
				AnsiToDos(oStr,1);
				strcat(oStr,"\r");
				m_Comm.GPSendBlock(oStr,(int)strlen(oStr));
				delete[] oStr;
				job_flag=next_job=0;
				break;
			}

			case -12001: /* GP_TERM FindRepl Dialog create 012001 0 027 0 224 0 033*/
				{
					UINT IdDlg=0xFFFFF,IdParent=0xFFFFF;
					m_LastScanf=sscanf(InputBuffer2,"%d,%d",&IdDlg,&IdParent);
					HWND tmp=NULL;

					if (IdParent<MAX_OBJDLG && GetDocument()->a_GPObjDialog[IdParent]!=NULL)
						tmp=GetDocument()->a_GPObjDialog[IdParent]->m_hWnd;

					if (tmp==NULL) tmp=GPC.m_hViewWnd;
					if (GPFRD == NULL)
					{
						GPFRD=new GPDlgFindReplace(atoi(InputBuffer2),CWnd::FromHandle(tmp));
						GPFRD->Create(IDD_DIALOGFINDREPLACE,CWnd::FromHandle(tmp));
					}
					if (IdDlg<MAX_OBJDLG)	GPFRD->IdDlg=IdDlg;
					GPFRD->ShowWindow(SW_SHOW);
				}
				job_flag=next_job=0;
				break;
			case -12002: /* GP_TERM FindRepl Dialog close 012002 0 027 0 224 0 034*/
				if (GPFRD != NULL)
				{
					GPFRD->SetParent(CWnd::FromHandle(GPC.m_hViewWnd));
					GPFRD->ShowWindow(SW_HIDE);
					GPFRD->DoMethod("SetMessages",NULL);
				}
				job_flag=next_job=0;
				break;
			case -12003: /* GP_TERM FindRepl Dialog Fn 012003 0 027 0 224 0 035*/
				*GPC.StrTmpOut=0;
				if (GPFRD != NULL)
					GPFRD->DoMethod(DosToAnsi(InputBuffer2),GPC.StrTmpOut);
				SendStringToPICK(GPC.StrTmpOut);
				job_flag=next_job=0;
				break;
			case -12004: /* GP_TERM FindRepl Dialog Sub 012004 0 027 0 224 0 036*/
				if (GPFRD != NULL)	GPFRD->DoMethod(DosToAnsi(InputBuffer2),NULL);
				job_flag=next_job=0;
				break;

			case -12100: /* Create GPObjDialog */
				{
					UINT IdDlg=atoi(InputBuffer2);
					if (IdDlg>=MAX_OBJDLG) IdDlg=MAX_OBJDLG-1;
					CreateObjDlg(IdDlg,DosToAnsi(InputBuffer2));
					job_flag=0;
				}
				break;

			case -12101: /* Delete GPObjDialog */
				{
					UINT IdDlg=atoi(InputBuffer2);
					if (IdDlg<MAX_OBJDLG) GetDocument()->DeleteObjDlg(IdDlg,TRUE,TRUE);
					job_flag=0;
				}
				break;

			case -12102: /* Create GPObjFrame */
				{
					UINT IdDlg=atoi(InputBuffer2);
					if (IdDlg>=MAX_OBJDLG) IdDlg=MAX_OBJDLG-1;
					CreateObjFrame(IdDlg,DosToAnsi(InputBuffer2));
					job_flag=0;
				}
				break;

			case -12103: /* Delete GPObjFrame */
				{
					UINT IdDlg=atoi(InputBuffer2);
					if (IdDlg<MAX_OBJDLG) GetDocument()->DeleteObjFrame(IdDlg,TRUE,TRUE);
					job_flag=0;
				}
				break;



			case -12201: /* Menu Create Popup */
			case -12202: /* Menu Append */
			case -12203: /* Menu Insert */
			case -12204: /* Menu ModifyByCom */
			case -12205: /* Menu ModifyByPos */
			case -12206: /* Menu RemoveByPos */
			case -12207: /* Menu RemoveByCom */
			case -12208: /* Menu EnableByPos */
			case -12209: /* Menu EnableByCom */
			case -12210: /* Menu CheckByPos */
			case -12211: /* Menu CheckByCom */
			case -12212: /* Menu CheckRadio */
			case -12213: /* Menu AppendSeparator */
			case -12214: /* Menu InsertSeparator */
			case -12215: /* Menu Remove All */
			case -12216: /* Menu Create Track */
			case -12217: /* Menu Track Popup*/
			case -12218: /* Menu Enable Popup */

			case -12221: /* Menu Dialog Create Popup */
			case -12222: /* Menu Dialog Append */
			case -12223: /* Menu Dialog Insert */
			case -12224: /* Menu Dialog ModifyByCom */
			case -12225: /* Menu Dialog ModifyByPos */
			case -12226: /* Menu Dialog RemoveByPos */
			case -12227: /* Menu Dialog RemoveByCom */
			case -12228: /* Menu Dialog EnableByPos */
			case -12229: /* Menu Dialog EnableByCom */
			case -12230: /* Menu Dialog CheckByPos */
			case -12231: /* Menu Dialog CheckByCom */
			case -12232: /* Menu Dialog CheckRadio */
			case -12233: /* Menu Dialog AppendSeparator */
			case -12234: /* Menu Dialog InsertSeparator */
			case -12235: /* Menu Dialog Remove All */
			case -12236: /* Menu Dialog Create Track */
			case -12237: /* Menu Dialog Track Popup*/
			case -12238: /* Menu Dialog Enable Popup */
			try
				{
					UINT IdMenu=1,IdPopup=-1,PosItem=-1,IdItem=-1,PosItemStart=-1,PosItemEnd=-1;
					int IdDlg=-1,CX=0,CY=0;
					char *postxt=NULL,*posflg=NULL;
					posflg=strchr(InputBuffer2,';');
					if (posflg!=NULL)
					{
						char *tmp=posflg;
						while ((tmp=strchr(++tmp,';'))!=NULL)
							postxt=tmp;
						if (postxt!=NULL) *(postxt++)=0;
						else postxt="";
					}
					else posflg="";

					switch(job_flag)
					{
					case -12201: /* Menu Create Popup */
					case -12221: /* Menu Dialog Create Popup */
						m_LastScanf=sscanf(InputBuffer2,"%d,%d,%d,%d",&IdDlg,&IdMenu,&PosItem,&IdPopup);
						IdMenu%=MENU_POPUP_COUNT;
						IdPopup%=MENU_POPUP_COUNT;
						break;
					case -12202: /* Menu Append */
					case -12222: /* Menu Dialog Append */
						m_LastScanf=sscanf(InputBuffer2,"%d,%d,%d",&IdDlg,&IdPopup,&IdItem);
						IdItem%=MENU_ID_COUNT;
						IdPopup%=MENU_POPUP_COUNT;
						break;
					case -12203: /* Menu Insert */
					case -12223: /* Menu Dialog Insert */
						m_LastScanf=sscanf(InputBuffer2,"%d,%d,%d,%d",&IdDlg,&IdPopup,&PosItem,&IdItem);
						IdItem%=MENU_ID_COUNT;
						IdPopup%=MENU_POPUP_COUNT;
						break;
					case -12204: /* Menu ModifyByCom */
					case -12207: /* Menu RemoveByCom */
					case -12209: /* Menu EnableByCom */
					case -12211: /* Menu CheckByCom */
					case -12224: /* Menu Dialog ModifyByCom */
					case -12227: /* Menu Dialog RemoveByCom */
					case -12229: /* Menu Dialog EnableByCom */
					case -12231: /* Menu Dialog CheckByCom */
						m_LastScanf=sscanf(InputBuffer2,"%d,%d",&IdDlg,&IdItem);
						IdItem%=MENU_ID_COUNT;
						break;
					case -12205: /* Menu ModifyByPos */
					case -12206: /* Menu RemoveByPos */
					case -12208: /* Menu EnableByPos */
					case -12210: /* Menu CheckByPos */
					case -12214: /* Menu InsertSeparator */
					case -12225: /* Menu Dialog ModifyByPos */
					case -12226: /* Menu Dialog RemoveByPos */
					case -12228: /* Menu Dialog EnableByPos */
					case -12230: /* Menu Dialog CheckByPos */
					case -12234: /* Menu Dialog InsertSeparator */
					case -12218: /* Menu Enable Popup */
					case -12238: /* Menu Dialog Enable Popup */
						m_LastScanf=sscanf(InputBuffer2,"%d,%d,%d",&IdDlg,&IdPopup,&PosItem);
						IdPopup%=MENU_POPUP_COUNT;
						break;
					case -12212: /* Menu CheckRadio */
					case -12232: /* Menu Dialog CheckRadio */
						m_LastScanf=sscanf(InputBuffer2,"%d,%d,%d,%d,%d",&IdDlg,&IdPopup,&PosItemStart,&PosItem,&PosItemEnd);
						IdPopup%=MENU_POPUP_COUNT;
						break;
					case -12213: /* Menu AppendSeparator */
					case -12233: /* Menu Dialog AppendSeparator */
					case -12216: /* Menu Create Track */
					case -12236: /* Menu Dialog Create Track */
						m_LastScanf=sscanf(InputBuffer2,"%d,%d",&IdDlg,&IdPopup);
						IdPopup%=MENU_POPUP_COUNT;
						break;
					case -12217: /* Menu Track Popup*/
					case -12237: /* Menu Dialog Track Popup*/
						m_LastScanf=sscanf(InputBuffer2,"%d,%d,%d,%d",&IdDlg,&IdPopup,&CX,&CY);
						IdPopup%=MENU_POPUP_COUNT;
						break;
					case -12235: /* Menu Dialog Removeallmenu */
					case -12215: /* Menu Removeallmenu */
						IdDlg=atoi(InputBuffer2);
						break;
					}
					GPMenu *pGPM=NULL;
					if (IdDlg<0) pGPM=m_GPMenu;
					else
					{
						if (IdDlg>=MAX_OBJDLG) IdDlg=MAX_OBJDLG-1;
						if (GetDocument()->a_GPObjType[IdDlg]==0)
						{
							if (GetDocument()->a_GPObjDialog[IdDlg]!=NULL)
								pGPM=GetDocument()->a_GPObjDialog[IdDlg]->CreateDlgMenu();
						}
						else
						{
							if (GetDocument()->a_GPObjFrame[IdDlg]!=NULL)
								pGPM=GetDocument()->a_GPObjFrame[IdDlg]->CreateDlgMenu();
						}
					}

					if (pGPM!=NULL)
					{
						pGPM->Fill_mArrMenu(FALSE);
						switch(job_flag)
						{
						case -12221: /* Menu Dialog Create Popup */
						case -12201: /* Menu Create Popup */
							if (IdPopup<10)
								#ifdef RUS
									MessageBox("Id нового popup menu должен быть в пределах 10 - 1000",GPC.ErrBoxCaption,MB_OK|MB_ICONEXCLAMATION);
								#else
									MessageBox("Id of new popup menu must be in range 10 - 1000",GPC.ErrBoxCaption,MB_OK|MB_ICONEXCLAMATION);
								#endif
							else
							pGPM->GPCreatePopupMenu(IdMenu,IdPopup,PosItem,postxt,posflg);
							break;
						case -12222: /* Menu Dialog Append */
						case -12202: /* Menu Append */
							pGPM->GPAppendMenu(IdPopup, IdItem, posflg, postxt);
							break;
						case -12223: /* Menu Dialog Insert */
						case -12203: /* Menu Insert */
							pGPM->GPInsertMenu(IdPopup, PosItem, IdItem, posflg, postxt);
							break;
						case -12224: /* Menu Dialog ModifyByCom */
						case -12204: /* Menu ModifyByCom */
							pGPM->GPModifyByCom( IdItem, posflg, postxt);
							break;
						case -12225: /* Menu Dialog ModifyByPos */
						case -12205: /* Menu ModifyByPos */
							pGPM->GPModifyByPos(IdPopup, PosItem, posflg, postxt);
							break;
						case -12226: /* Menu Dialog RemoveByPos */
						case -12206: /* Menu RemoveByPos */
							pGPM->GPRemoveByPos(IdPopup, PosItem);
							break;
						case -12227: /* Menu Dialog RemoveByCom */
						case -12207: /* Menu RemoveByCom */
							pGPM->GPRemoveByCom(IdItem);
							break;
						case -12228: /* Menu Dialog EnableByPos */
						case -12208: /* Menu EnableByPos */
							pGPM->GPEnableByPos(IdPopup, PosItem, posflg);
							break;
						case -12229: /* Menu Dialog EnableByCom */
						case -12209: /* Menu EnableByCom */
							pGPM->GPEnableByCom(IdItem, posflg);
							break;
						case -12230: /* Menu Dialog CheckByPos */
						case -12210: /* Menu CheckByPos */
							pGPM->GPCheckByPos(IdPopup, PosItem, posflg);
							break;
						case -12231: /* Menu Dialog CheckByCom */
						case -12211: /* Menu CheckByCom */
							pGPM->GPCheckByCom(IdItem, posflg);
							break;
						case -12232: /* Menu Dialog CheckRadio */
						case -12212: /* Menu CheckRadio */
							pGPM->GPCheckRadio(IdPopup, PosItem, PosItemStart, PosItemEnd);
							break;
						case -12233: /* Menu Dialog AppendSeparator*/
						case -12213: /* Menu AppendSeparator*/
							pGPM->GPAppendSeparator(IdPopup);
							break;
						case -12234: /* Menu Dialog InsertSeparator */
						case -12214: /* Menu InsertSeparator */
							pGPM->GPInsertSeparator(IdPopup, PosItem);
							break;
						case -12235: /* Menu Dialog Removeallmenu */
						case -12215: /* Menu Removeallmenu */
							pGPM->Fill_mArrMenu(TRUE);
							pGPM->GPDrawMenuBar();
							break;
						case -12216: /* Menu Create Track */
						case -12236: /* Menu Dialog Create Track */
							pGPM->GPCreateTrackMenu(IdPopup,posflg);
							break;
						case -12217: /* Menu Track Popup*/
						case -12237: /* Menu Dialog Track Popup*/
							{
								DWORD nflags=0;
								if (*posflg) nflags=CGPContextMenu::StringFromToTPMFlags(posflg,nflags);
								CRect re=CRect(0,0,0,0);
								m_LastScanf=sscanf(postxt,"%d,%d,%d,%d",&re.left,&re.top,&re.right,&re.bottom);

								pGPM->GPTrackPopupMenu(IdPopup,nflags,CX,CY,&re);
							}
							break;
						case -12218: /* Menu Enable Popup */
						case -12238: /* Menu Dialog Enable Popup */
							pGPM->EnablePopup(IdPopup,PosItem);
							break;
						}

						if (IdPopup==0 || IdMenu==0/*&& IdDlg>=0*/)
							pGPM->GPDrawMenuBar();
					}

					next_job=job_flag=0;
				}
				catch(...)
				{
					char tmpss[150];
					sprintf(tmpss,"job_flag=%d",job_flag);
					GPC.m_ErrReport.GPWriteErrorLog("CGP_TermView", "RemappingInput",tmpss);
					GPC.m_ErrReport.GPWriteErrorLog("CGP_TermView", "RemappingInput DATA",InputBuffer2);
				}
				break;

			case -12239: /* User Menu Sub 012239 0 027 0 225 0 071 */
				if (GPC.m_pContextMenu)
					GPC.m_pContextMenu->DoMethod(DosToAnsi(InputBuffer2),NULL);
				job_flag=next_job=0;
				break;
			case -12240: /* User Menu Fn 012240 0 027 0 225 0 072 */
				*GPC.StrTmpOut=0;
				if (GPC.m_pContextMenu)
				{

					char *oStr=GPC.StrTmpOut;
					GPC.m_pContextMenu->DoMethod(DosToAnsi(InputBuffer2),oStr);
				}
				SendStringToPICK(GPC.StrTmpOut);
				job_flag=next_job=0;
				break;

			case -12301: /* AddHotKey IdScrDlg, IdObj, VK_ 012301 0 027 0 226 0 032*/
			case -12302: /* DelHotKey IdScrDlg, IdObj, VK_ 012302 0 027 0 226 0 033*/
			case -12303: /* DelAllHotKey IdScrDlg, IdObj   012303 0 027 0 226 0 034*/
				{
					//"D,IdDlg-1,IdObj,VK_Name"
					char t='D';
					int IdDlg=0,IdObj=0,VkId=0;
					char *VK_Name="";
					m_LastScanf=sscanf(InputBuffer2,"%c,%d,%d,%d",&t,&IdDlg,&IdObj,&VkId);
					if ((VK_Name=strstr(InputBuffer2,"VK_"))==NULL) VK_Name="";
					char *seq;
					if ((seq=strstr(InputBuffer2,"MOD_")) && (seq<VK_Name || *VK_Name==0)) VK_Name=seq;
					CString tmpScript;
					seq=strchr(InputBuffer2,0x2);
					if (seq)
					{
						tmpScript=seq;
						*seq=0;
					}
					seq=strchr(InputBuffer2,'=');
					if (seq)
					{
						tmpScript=seq+tmpScript;
						*seq=0;
					}

					GPUnit *tmpu=NULL;

					if (t=='S' || t=='s')
					{
						tmpu=s->GPGetWindowById(0)->GetUnitById(IdObj>0?IdObj:0);
					}
					else
					{
						if (IdDlg<0 || IdDlg>MAX_OBJDLG) IdDlg=0;

						if (IdObj>0)
						{
							if (GetDocument()->a_GPObjType[IdDlg]==0)
							{
								if (GetDocument()->a_GPObjDialog[IdDlg]!=NULL)
									tmpu=((GPObjDialog *)GetDocument()->a_GPObjDialog[IdDlg])->GetUnitById(IdObj);
							}
							else
							{
								if (GetDocument()->a_GPObjFrame[IdDlg]!=NULL)
									tmpu=GetDocument()->a_GPObjFrame[IdDlg]->GetUnitById(IdObj);
							}
						}
						else
							switch(job_flag)
							{
								case -12301: /* AddHotKey IdScrDlg, IdObj, VK_ 012301 0 027 0 226 0 032*/
									if (*VK_Name!=0)
									{
										if (GetDocument()->a_GPObjType[IdDlg]==0)
										{
											if (GetDocument()->a_GPObjDialog[IdDlg])
												GetDocument()->a_GPObjDialog[IdDlg]->AddHotkey(VK_Name,VkId,tmpScript);
										}
										else
											if (GetDocument()->a_GPObjFrame[IdDlg]!=NULL)
												GetDocument()->a_GPObjFrame[IdDlg]->AddHotkey(VK_Name,VkId,tmpScript);
									}
									break;
								case -12302: /* DelHotKey IdScrDlg, IdObj, VK_ 012302 0 027 0 226 0 033*/
									if (GetDocument()->a_GPObjType[IdDlg]==0)
									{
										if (GetDocument()->a_GPObjDialog[IdDlg]!=NULL)
											GetDocument()->a_GPObjDialog[IdDlg]->DelHotkey(VkId,VK_Name);
									}
									else
										if (GetDocument()->a_GPObjFrame[IdDlg]!=NULL)
											GetDocument()->a_GPObjFrame[IdDlg]->DelHotkey(VkId,VK_Name);
									break;
								case -12303: /* DelAllHotKey IdScrDlg, IdObj   012303 0 027 0 226 0 034*/
									if (GetDocument()->a_GPObjType[IdDlg]==0)
									{
										if (GetDocument()->a_GPObjDialog[IdDlg]!=NULL)
											GetDocument()->a_GPObjDialog[IdDlg]->DelAllHotkey();
									}
									else
										if (GetDocument()->a_GPObjFrame[IdDlg]!=NULL)
											GetDocument()->a_GPObjFrame[IdDlg]->DelAllHotkey();
									break;
							}
					}

					if (tmpu!=NULL)
						switch(job_flag)
						{
							case -12301: /* AddHotKey IdScrDlg, IdObj, VK_ 012301 0 027 0 226 0 032*/
								if (*VK_Name!=0) tmpu->AddHotkey(VK_Name,VkId,tmpScript);
								break;
							case -12302: /* DelHotKey IdScrDlg, IdObj, VK_ 012302 0 027 0 226 0 033*/
								tmpu->DelHotkey(VkId,VK_Name);
								break;
							case -12303: /* DelAllHotKey IdScrDlg, IdObj   012303 0 027 0 226 0 034*/
								tmpu->DelAllHotkey();;
								break;
						}
					next_job=job_flag=0;
				}
				break;
			//GP_TERM OLE Convent (12500-12599)
			case -12501: /* GP_TERM  OLE TCL-Start/End 012501 0 027 0 227 0 032 */

				if (atoi(InputBuffer2)==1)
				{
					GPC.TCLinProgress=TRUE;
					GPC.m_WaitTCL=FALSE;
				}

				if (atoi(InputBuffer2)==0)
				{
					GPC.TCLinProgress=FALSE;
					GPC.m_WaitEndTCL=FALSE;
					if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
				}
				working_flag=FALSE;
				next_job=job_flag=0;
				break;
			case -12502: /* GP_TERM  OLE SUB-Start 012502 0 027 0 227 0 033 */
				GPC.TCLinProgress=TRUE;
				GPC.ClearOUTSUB();
				GPC.ClearOUTTCL();
				GPC.m_WaitSUB=FALSE;
				working_flag=FALSE;
				next_job=job_flag=0;
				break;

			case -12503: /* GP_TERM  OLE SUB-Result 012503 0 027 0 227 0 034 */
				if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
				GPC.AddToOUTSUB(InputBuffer2);
				GPC.TCLinProgress=FALSE;
				GPC.m_WaitEndSUB=FALSE;
				working_flag=FALSE;
				next_job=job_flag=0;
				break;
			case -12504: /* GP_TERM  OLE OPENFILE DELETEITEM WRITEFILE SAVELIST Result 012504 0 027 0 227 0 035 */
				GetDocument()->LastResult=atoi(InputBuffer2);
				working_flag=FALSE;
				next_job=job_flag=0;
				break;
			case -12505: /* GP_TERM  OLE READFILE READFILEEX GETACTIVELIST GETLIST Result 012505 0 027 0 227 0 036 */
				GetDocument()->LastResult=1;
				working_flag=FALSE;
				next_job=job_flag=0;
				break;
			default: // Продолжение выполнения сложных команд
					next_job=job_flag=0;
					break;
			}
		}
		else
		if (job_flag>-14500)
		{
			switch(job_flag)
			{
			case -13002: /* GP_TERM RUN EXELL MACRO   013002 0 027 0 228 0 034*/
				{
					if (m_CaptureFile) fputs(InputBuffer2,m_CaptureFile);
					m_DlgSeparateView.AppendStringToOutput(InputBuffer2);

					next_job=job_flag=0;
					char* pParmExcel=DosToAnsi(InputBuffer2);
					char* pParamExcel2=new char[(int)strlen(pParmExcel)+1];
					strcpy(pParamExcel2,pParmExcel);
//					char *pss=strchr(InputBuffer2,',');
//					if (pss!=NULL)
//					{
//						*pss=0;
//						FILE *tmpf=fopen(InputBuffer2,"rb");
//						if (
//						*pss=',';
//					}
					GPExcel::RunGPExcelMacro(pParamExcel2);
					*GPC.StrTmpOut=0;
					SendStringToPICK(GPC.StrTmpOut);
					break;
				}
			case -13003: /* GP_TERM GPTERM.MessageSound   013003 0 027 0 228 0 035*/
				if (m_uLockBeep==0)
				{
					if (m_CaptureFile) fputs(InputBuffer2,m_CaptureFile);
					m_DlgSeparateView.AppendStringToOutput(InputBuffer2);
					char *cstl[5]={"ASTERISK","EXCLAMATION","HAND","QUESTION","OK",};
					UINT  ustl[5]={MB_ICONASTERISK,MB_ICONEXCLAMATION,MB_ICONHAND,MB_ICONQUESTION,MB_OK,};
					UINT stl=MB_ICONEXCLAMATION;
					int i333;
					for(i333=0;i333<5;i333++)
						if (strcmp(InputBuffer2,cstl[i333])==0) {stl=ustl[i333];break;}
					MessageBeep(stl);
					next_job=job_flag=0;
					break;
				}
				else m_uLockBeep|=0x6;
				break;
			case -13004: /* GP_TERM GPTERM.BeepSound   013004 0 027 0 228 0 036*/
				if (m_uLockBeep==0)
				{
					if (m_CaptureFile) fputs(InputBuffer2,m_CaptureFile);
					m_DlgSeparateView.AppendStringToOutput(InputBuffer2);
					UINT freq=1000,dur=1000;
					m_LastScanf=sscanf(InputBuffer2,"%d,%d",&freq,&dur);
					Beep(freq,dur);
					next_job=job_flag=0;
					break;
				}
				else m_uLockBeep|=0x6;
				break;
			case -13005: /* GP_TERM GPTERM.PlaySound   013005 0 027 0 228 0 037*/
				{
					if (m_CaptureFile) fputs(InputBuffer2,m_CaptureFile);
					m_DlgSeparateView.AppendStringToOutput(InputBuffer2);
					char *nm=strchr(InputBuffer2,',');
					if (nm!=NULL)
						PlaySound(DosToAnsi(++nm), NULL, SND_FILENAME|SND_ASYNC |(atoi(InputBuffer2)==0?0:SND_LOOP));
					next_job=job_flag=0;
					break;
				}
			case -13007: /* GP_TERM GPTERM.ShellExecuteEx   013007 0 027 0 228 0 039*/
				{
					DosToAnsi(InputBuffer2);
					CString tmps="ShellExecuteEx ";
					tmps+=InputBuffer2;
					if (m_CaptureFile) fputs(InputBuffer2,m_CaptureFile);
					m_DlgSeparateView.AppendStringToOutput(InputBuffer2);
					CDlgViewSystemMethods::DoMethod(tmps,NULL);
					next_job=job_flag=0;
					break;
				}
			case -13008: /* GP_TERM GP.GetSysColor   013008 0 027 0 228 0 040*/
			case -13010: /* GP_TERM GP.GetSysColorBrush   013010 0 027 0 228 0 042*/
			case -13017: /* GP_TERM GP.GetSysMetrics   013017 0 027 0 228 0 049*/
				{
					char *oStr=new char [20000];
					*oStr=0;
					CString tmps;
					switch(job_flag)
					{
					case -13008: /* GP_TERM GP.GetSysColor*/
						tmps="GetSysColor ";		break;
						break;
					case -13010: /* GP_TERM GP.GetSysColorBrush*/
						tmps="GetSysColorBrush ";		break;
						break;
					case -13017: /* GP_TERM GP.GetSysMetrics*/
						tmps="GetSystemMetrics ";		break;
					}
					tmps+=InputBuffer2;
					CDlgViewSystemMethods::DoMethod(tmps,oStr);
					strcat(oStr,"\r");
					AnsiToDos(oStr,0);
					m_Comm.GPSendBlock(oStr,(int)strlen(oStr));
					delete[] oStr;
					next_job=job_flag=0;
					break;
				}
			case -13009: /* GP_TERM GP.SetSysColor   013009 0 027 0 228 0 041*/
				{
					CString tmps="SetSysColors ";
					tmps+=InputBuffer2;
					CDlgViewSystemMethods::DoMethod(tmps,NULL);
					next_job=job_flag=0;
					break;
				}
			case -13011: /* GP_TERM GP.GetClipboardText   013011 0 027 0 228 0 043*/
				{
					HANDLE hClipData;                        /* handle to clip data  */
					LPSTR  lpClipData;                           /* pointers to clip data */
					char *str=NULL;
					char *pos;

					if (OpenClipboard())
					{
						if (!(hClipData = GetClipboardData(CF_TEXT)))    CloseClipboard();
						else
						{
							str=new char [GlobalSize(hClipData)+10];
							*str=0;
							if (!(lpClipData = (char *)GlobalLock(hClipData))) CloseClipboard();
							else
							{
								strcpy(str, lpClipData);
								GlobalUnlock(hClipData);
								CloseClipboard();
								AnsiToDos(str,1);
								pos=str;
								while(*pos!=0)
								{
									if ((*pos==10 && pos[1]==13) || (*pos==13 && pos[1]==10))
										*(pos++)=' ';
									if (*pos==10  || *pos==13) *pos=254;
									pos++;
								}
							}
						}
					}

					if (str!=NULL)
					{
						strcat(str,"\r");
						m_Comm.GPSendBlock(str,(int)strlen(str));
						delete[] str;
					}
					else m_Comm.GPSendBlock("\r",1);

				}
				next_job=job_flag=0;
				break;
			case -13012: /* GP_TERM GP.SetClipboardText   013013 0 027 0 228 0 044*/
				StringToClip(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;
				break;
			case -13018: /* GP_TERM GP.LoadKeyboard    013018 0 027 0 228 0 050*/
				if ((int)strlen(InputBuffer2)==0) m_csCurentTermCapFileName=m_csOldTermCapFileName;
				else
				{
					m_csOldTermCapFileName=m_csCurentTermCapFileName;
					m_csCurentTermCapFileName=AnsiToDos(InputBuffer2,0);
				}

				strncpy(GPC.TermCapFileName,m_csCurentTermCapFileName,250);
				GPC.TermCapFileName[250]=0;
				m_TermCap.Load(GPC.TermCapFileName);
				next_job=job_flag=0;
				break;
			case -13019: /* GP_TERM GP.LoadPalette     013019 0 027 0 228 0 051*/
				if ((int)strlen(InputBuffer2)==0) CurentPaletteFile=OldPaletteFile;
				else
				{
					OldPaletteFile=CurentPaletteFile;
					CurentPaletteFile=AnsiToDos(InputBuffer2,0);
				}
				LoadPalette(CurentPaletteFile,cFEtalon,cBEtalon);
				next_job=job_flag=0;
				break;
			case -13021: /* GP_TERM GP.DnsHostToCompName 013021 0 027 0 228 0 053 :DnsHost*/
				{
					char str[512];*str=0;
#ifdef _W2K
					DnsHostnameToComputerName(DosToAnsi(InputBuffer2),str,500);
#else
					strcpy(str,"Old Windows");
#endif
					strcat(str,"\r");
					m_Comm.GPSendBlock(AnsiToDos(str,0),(int)strlen(str));
				}
				next_job=job_flag=0;
				break;
			case -13022: /* GP_TERM GP.GetComputerName 013022 0 027 0 228 0 054 :ComputerNameFormat*/
			case -13023: /* GP_TERM GP.GetComputerObjectName 013023 0 027 0 228 0 055 :ObjectNameFormat*/
			case -13026: /* GP_TERM GP.GetUserName 013026 0 027 0 228 0 058 :uNameType*/
				{
					char str[MAX_COMPUTERNAME_LENGTH + 512];*str=0;
					unsigned long nLen=MAX_COMPUTERNAME_LENGTH + 500;
#ifdef _W2K
					switch(job_flag)
					{
						case -13022: /*GP.GetComputerName*/
							GetComputerNameEx(Type,str,nLen);	break;
						case -13023: /*GP.GetComputerObjectName*/
							GetComputerObjectName (Type,str,nLen);	break;
						case -13026: /*GP.GetUserName*/
							GetUserNameEx (Type,str,nLen);	break;
					}
#else
					switch(job_flag)
					{
						case -13022: /*GP.GetComputerName*/
							GetComputerName(str,&nLen);	break;
						case -13023: /*GP.GetComputerObjectName*/
							strcpy(str,"Old Windows");	break;
						case -13026: /*GP.GetUserName*/
							GetUserName (str,&nLen);	break;
					}
#endif
					strcat(str,"\r");
					m_Comm.GPSendBlock(AnsiToDos(str,0),(int)strlen(str));
				}
				next_job=job_flag=0;
				break;
			case -13028: /* GP_TERM GP.TranslateName 013028 0 027 0 228 0 060 :sNameType:",":dNameType:",":sName*/
				{
					int sType=0,dType=0;
					char name[1000];*name=0;
					m_LastScanf=sscanf(InputBuffer2,"%d,%d,%s",&sType,&dType,name);
					DosToAnsi(name);
#ifdef _W2K
					TranslateName(sType,&dType,name,990);
#else
					strcpy(name,"Old Windows");
#endif
					strcat(name,"\r");
					m_Comm.GPSendBlock(AnsiToDos(name,0),(int)strlen(name));
				}
				next_job=job_flag=0;
				break;
			case -13029: /* GP_TERM GP.RegisterTerminal 013029 0 027 0 228 0 061 :sNameType:*/
				GetDocument()->RegisterGPTermInROT(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;
				break;
			case -13030: /* GP_TERM GP.UnRegisterTerminal 013030 0 027 0 228 0 062 :sNameType:*/
				GetDocument()->UnRegisterGPTermInROT(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;
				break;

			case -13031: /* GP_TERM GP.RegionCreate 013031 0 027 0 228 0 063 :Name*/
				GPC.RegionArr.CreateRgn(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;
				break;
			case -13032: /* GP_TERM GP.RegionDelete 013032 0 027 0 228 0 064 :Name*/
				GPC.RegionArr.GPDeleteRgn(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;
				break;
			case -13034: /* GP_TERM GP.RegionSub 013034 0 027 0 228 0 066 :Name;SubSting*/
			case -13035: /* GP_TERM GP.RegionFn 013035 0 027 0 228 0 067 :Name,SubSting ->ret*/
				{
					char *pos=strchr(DosToAnsi(InputBuffer2),';');
					if (pos!=NULL)
					{
						*(pos++)=0;
						GPRegion *tmpreg=GPC.RegionArr.GetRgn(InputBuffer2);
						*GPC.StrTmpOut=0;
						char *oStr=job_flag==-13034?NULL:GPC.StrTmpOut;
						if (tmpreg)
							tmpreg->DoMethod(pos,oStr,(void *)&GPC.RegionArr);

						if (oStr!=NULL) SendStringToPICK(GPC.StrTmpOut);
						else SendStringToPICK("");
					}
					else SendStringToPICK("");
				}
				next_job=job_flag=0;
				break;
			case -13036: /* GP_TERM GP.RegionFromDlgObj 013036 0 027 0 228 0 068 :Name;IdDlg,IdObj*/
			case -13037: /* GP_TERM GP.RegionFromScrObj 013037 0 027 0 228 0 069 :Name;iIdScr,iIdObj ->ret*/
				{
					char *pos=strchr(DosToAnsi(InputBuffer2),';');
					if (pos!=NULL)
					{
						*(pos++)=0;
						GPRegion *tmpreg=GPC.RegionArr.CreateRgn(InputBuffer2);
						if (tmpreg!=NULL)
						{
							HRGN rg=tmpreg->CreateRectRgn(0,0,5,5);
							UINT IdDlg=0,IdObj=0;
							m_LastScanf=sscanf(pos,"%d,%d",&IdDlg,&IdObj);
							GPUnit *tmpunit=NULL;
							if (IdDlg<MAX_OBJDLG)
							{
								if (job_flag==-13036) //Dlg
								{
									if (GetDocument()->a_GPObjType[IdDlg]==0)
									{
										if (GetDocument()->a_GPObjDialog[IdDlg])
											tmpunit=GetDocument()->a_GPObjDialog[IdDlg]->GetUnit(IdObj);
									}
									else
										if (GetDocument()->a_GPObjFrame[IdDlg])
											tmpunit=GetDocument()->a_GPObjFrame[IdDlg]->GetUnit(IdObj);
								}
								else //Scr
									tmpunit=s->GPGetWindowById(0)->GetUnitById(IdObj);

								if (rg && tmpunit!=NULL && tmpunit->UnitHWND!=NULL)
									::GetWindowRgn(tmpunit->UnitHWND,rg);
							}
						}
					}
				}
				next_job=job_flag=0;
				break;
			case -13041: /* GP_TERM GP.CursorCreate 013031 0 027 0 228 0 073 :Name*/
				GPC.CursorArr.CreateCursor(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;
				break;
			case -13042: /* GP_TERM GP.CursorDelete 013032 0 027 0 228 0 074 :Name*/
				GPC.CursorArr.DeleteCursor(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;
				break;
			case -13044: /* GP_TERM GP.CursorSub 013034 0 027 0 228 0 076 :Name;SubSting*/
			case -13045: /* GP_TERM GP.CursorFn 013035 0 027 0 228 0 077 :Name,SubSting ->ret*/
				{
					char *pos=strchr(DosToAnsi(InputBuffer2),';');
					*GPC.StrTmpOut=0;
					if (pos!=NULL)
					{
						*(pos++)=0;
						GPCursor *tmpreg=GPC.CursorArr.GetCursor(InputBuffer2);
						char *oStr=job_flag==-13044?NULL:GPC.StrTmpOut;
						if (tmpreg)
							tmpreg->DoMethod(pos,oStr,(void *)&GPC.CursorArr);

						if (oStr!=NULL)
							SendStringToPICK(GPC.StrTmpOut);
						else SendStringToPICK("");
					}
					else SendStringToPICK("");
				}
				next_job=job_flag=0;
				break;
			case -13046: /* GP_TERM GP.LockBeep 013046 0 027 0 228 0 078 */
				m_uLockBeep=atoi(InputBuffer2);
				next_job=job_flag=0;
				break;
			case -13047: /* GP_TERM GPTERM.Show(Show) 013047 0 027 0 228 0 079 */
				{
					_strupr(InputBuffer2);
					int i333;
					for(i333=0; i333 < N_WND_SHOW_STYLES && strstr(InputBuffer2,aWndShowStyleName[i333])==NULL; i333++);
					if (i333<N_WND_SHOW_STYLES)
					{
						AfxGetMainWnd()->ShowWindow(aWndShowStyleUINT[i333]);
						if (aWndShowStyleUINT[i333]==SW_SHOW) SetFocus();
					}
				}
				m_uLockBeep=atoi(InputBuffer2);
				next_job=job_flag=0;
				break;
			case -13048:/* GP_TERM GP.SystemSub 013048 0 027 0 228 0 080*/
				CDlgViewSystemMethods::DoMethod(DosToAnsi(InputBuffer2),NULL);
				job_flag=next_job=0;
				break;
			case -13049:/* GP_TERM GP.SystemFn 013049 0 027 0 228 0 081*/
				{
					*GPC.StrTmpOut=0;
					CDlgViewSystemMethods::DoMethod(DosToAnsi(InputBuffer2),GPC.StrTmpOut);
					SendStringToPICK(GPC.StrTmpOut);
				}
				job_flag=next_job=0;
				break;

			case -13060:/* GP_TERM GP.DCCreate 013060 0 027 0 228 0 092*/
			case -13061:/* GP_TERM GP.DCDelete 013061 0 027 0 228 0 093*/
			case -13062:/* GP_TERM GP.DCSub 013062 0 027 0 228 0 094*/
			case -13063:/* GP_TERM GP.DCFn 013063 0 027 0 228 0 095*/
				{
					DosToAnsi(InputBuffer2);
					CString csName=ExtractField(InputBuffer2,1,";");
					CODContext *m_Context=GPC.m_View->m_ODContextsArray->GetContext(csName);
					char *posparam=strchr(InputBuffer2,';');
					if (!posparam++) posparam="";
					switch(job_flag)
					{
					case -13060:/* GP_TERM GP.DCCreate 013060 0 027 0 228 0 092*/
						if (csName!=m_Context->m_ContextName && csName!="Default" && csName!="DefaultMenu")
							GPC.m_View->m_ODContextsArray->CreateContext(csName);
						break;
					case -13061:/* GP_TERM GP.DCDelete 013061 0 027 0 228 0 093*/
						if (csName==m_Context->m_ContextName && csName!="Default" && csName!="DefaultMenu")
							GPC.m_View->m_ODContextsArray->DeleteContext(csName);
						break;
					case -13062:/* GP_TERM GP.DCSub 013062 0 027 0 228 0 094*/
						if (*posparam) m_Context->DoMethod(posparam,NULL);
						break;
					case -13063:/* GP_TERM GP.DCFn 013063 0 027 0 228 0 095*/
						{
							*GPC.StrTmpOut=0;
							if (*posparam) m_Context->DoMethod(posparam,GPC.StrTmpOut);
							SendStringToPICK(GPC.StrTmpOut);
						}
						break;
					}
				}
				job_flag=next_job=0;
				break;



			///
			///  #######################################################################
			/// GP_TERM IMAGELIST COMMANDS (13500-13549)
			///  #######################################################################
			///
			case -13500: // 0 027 0 229 0 032  GP.IListCreate(Name,CX,CY,nIitial,Style)
			case -13501: // 0 027 0 229 0 033  GP.IListLoad(Name)
			case -13502: // 0 027 0 229 0 034  GP.IListDelete(Name)
			case -13503: // 0 027 0 229 0 035  GP.IListGetCount(Name, RetCount)
			case -13504: // 0 027 0 229 0 036  GP.IListSetBkColor(Name, R, G, B)
			case -13505: // 0 027 0 229 0 037  GP.IListGetBkColor(Name, RetRGB)
			case -13506: // 0 027 0 229 0 038  GP.IListGetImageInfo(Name, nImage, ImageInfo)
			case -13507: // 0 027 0 229 0 039  GP.IListSetImageCount(Name,ImageCount)
			case -13508: // 0 027 0 229 0 040  GP.IListAdd(Name,SName, nImage)
			case -13509: // 0 027 0 229 0 041  GP.IListAddFromFile(Name,FName)
			case -13510: // 0 027 0 229 0 042  GP.IListAddFromILFile(Name,FName,nImage)
			case -13511: // 0 027 0 229 0 043  GP.IListRemove(Name,nImage)
			case -13512: // 0 027 0 229 0 044  GP.IListReplace(Name,nImage,SName,SnImage)
			case -13513: // 0 027 0 229 0 045  GP.IListReplaceFromFile(Name,nImage,FName)
			case -13514: // 0 027 0 229 0 046  GP.IListReplaceFromILF(Name,nImage,FName,SnImage)
			case -13515: // 0 027 0 229 0 047  GP.IListSetOverlay(Name,nImage,nOverlay)
			case -13516: // 0 027 0 229 0 048  GP.IListCopy(Name,nSImage,nDImage)
			case -13517: // 0 027 0 229 0 049  GP.IListSwap(Name,nSImage,nDImage)
			case -13518: // 0 027 0 229 0 050  GP.IListSwapEx(SName,nSImage,DName,nDImage)
			case -13519: // 0 027 0 229 0 051  GP.IListCopyEx(SName,nSImage,DName,nDImage)
			case -13520: // 0 027 0 229 0 052  GP.IListSetDragCursor(Name,nImage,PX,PY)
			case -13521: // 0 027 0 229 0 053  GP.IListWrite(Name)
			case -13522: // 0 027 0 229 0 054  GP.IListBeginDrag(Name,nImage,PX,PY)
			case -13523: // 0 027 0 229 0 055  GP.IListDragEnter(IdDlg,IdObj,Name,PX,PY)
			case -13524: // 0 027 0 229 0 056  GP.IListEndDrag(Name)
			case -13525: // 0 027 0 229 0 057  GP.IListDragLeave(IdDlg,IdObj,Name)
			case -13526: // 0 027 0 229 0 058  GP.IListDragMove(Name,PX,PY)
			case -13527: // 0 027 0 229 0 059  GP.IListDragShowNolock(Name)
				{
					char tmp[1000],*Name2=tmp,*Name=tmp;
					*Name=0;
					int nImage1=0,nImage2=0,IdDlg=0,IdObj=0;
					DosToAnsi(InputBuffer2);
					POINT po;
					po.x=po.y=16;
					switch(job_flag)
					{
					case -13501: // 0 027 0 229 0 033  GP.IListLoad(Name)
					case -13502: // 0 027 0 229 0 034  GP.IListDelete(Name)
					case -13521: // 0 027 0 229 0 053  GP.IListWrite(Name)
					case -13524: // 0 027 0 229 0 056  GP.IListEndDrag(Name)
					case -13503: // 0 027 0 229 0 035  GP.IListGetCount(Name, RetCount)
					case -13505: // 0 027 0 229 0 037  GP.IListGetBkColor(Name, RetRGB)
						strcpy(Name,InputBuffer2);
						break;
					case -13500: // 0 027 0 229 0 032  GP.IListCreate(Name,CX,CY,nIitial,Style)
						m_LastScanf=sscanf(InputBuffer2,"%d,%d,%d,%s",&po.x,&po.y,&nImage1,tmp);
						Name=strchr(tmp,';');
						if (Name!=NULL) *(Name++)=0;
						else Name="";
						break;
					case -13504: // 0 027 0 229 0 036  GP.IListSetBkColor(Name, R, G, B)
					case -13520: // 0 027 0 229 0 052  GP.IListSetDragCursor(Name,nImage,PX,PY)
					case -13522: // 0 027 0 229 0 054  GP.IListBeginDrag(Name,nImage,PX,PY)
						m_LastScanf=sscanf(InputBuffer2,"%d,%d,%d;%s",&po.x,&po.y,&nImage1,tmp);
						break;
					case -13506: // 0 027 0 229 0 038  GP.IListGetImageInfo(Name, nImage, ImageInfo)
					case -13507: // 0 027 0 229 0 039  GP.IListSetImageCount(Name,ImageCount)
					case -13511: // 0 027 0 229 0 043  GP.IListRemove(Name,nImage)
					case -13527: // 0 027 0 229 0 059  GP.IListDragShowNolock(Name,fShow)
						m_LastScanf=sscanf(InputBuffer2,"%d;%s",&nImage1,tmp);
						break;
					case -13508: // 0 027 0 229 0 040  GP.IListAdd(Name,SName, nImage)
					case -13510: // 0 027 0 229 0 042  GP.IListAddFromILFile(Name,FName,nImage)
					case -13513: // 0 027 0 229 0 045  GP.IListReplaceFromFile(Name,nImage,FName)
						m_LastScanf=sscanf(InputBuffer2,"%d;%s",&nImage1,tmp);
						Name2=strchr(tmp,';');
						if (Name2!=NULL) *(Name2++)=0;
						else Name2="";
						break;
					case -13509: // 0 027 0 229 0 041  GP.IListAddFromFile(Name,FName)
						strncpy(tmp,InputBuffer2,900);tmp[900]=0;
						Name2=strchr(tmp,';');
						if (Name2!=NULL) *(Name2++)=0;
						else Name2="";
						break;
					case -13512: // 0 027 0 229 0 044  GP.IListReplace(Name,nImage,SName,SnImage)
					case -13514: // 0 027 0 229 0 046  GP.IListReplaceFromILF(Name,nImage,FName,SnImage)
					case -13518: // 0 027 0 229 0 050  GP.IListSwapEx(SName,nSImage,DName,nDImage)
					case -13519: // 0 027 0 229 0 051  GP.IListCopyEx(SName,nSImage,DName,nDImage)
						m_LastScanf=sscanf(InputBuffer2,"%d,%d,%s",&nImage1,&nImage2,tmp);
						Name2=strchr(tmp,';');
						if (Name2!=NULL) *(Name2++)=0;
						else Name2="";
						break;
					case -13515: // 0 027 0 229 0 047  GP.IListSetOverlay(Name,nImage,nOverlay)
					case -13516: // 0 027 0 229 0 048  GP.IListCopy(Name,nSImage,nDImage)
					case -13517: // 0 027 0 229 0 049  GP.IListSwap(Name,nSImage,nDImage)
					case -13525: // 0 027 0 229 0 057  GP.IListDragLeave(IdDlg,IdObj,Name)
						m_LastScanf=sscanf(InputBuffer2,"%d,%d;%s",&nImage1,&nImage2,tmp);
						break;
					case -13523: // 0 027 0 229 0 055  GP.IListDragEnter(IdDlg,IdObj,Name,PX,PY)
						m_LastScanf=sscanf(InputBuffer2,"%d,%d,%d,%d;%s",&IdDlg,&IdObj,&po.x,&po.y,tmp);
						break;
					case -13526: // 0 027 0 229 0 058  GP.IListDragMove(Name,PX,PY)
						m_LastScanf=sscanf(InputBuffer2,"%d,%d;%s",&po.x,&po.y,tmp);
						break;
					}
					if (*Name==0) Name="MISCS";

					GPImageList *MainIl=NULL;

					int ImgLId=GPC.GetImageListId(Name);
					if (ImgLId>=0) MainIl=&(GPC.a_GPImageList[ImgLId]);

					switch(job_flag)
					{
					case -13500: // 0 027 0 229 0 032  GP.IListCreate(Name,CX,CY,nIitial,Style)
						if (MainIl==NULL)
						{
							ImgLId=GPC.GetImageListId("");
							MainIl=&(GPC.a_GPImageList[ImgLId]);
						}

						if (MainIl!=NULL)
							MainIl->CreateIL(CString(Name),po.x,po.y,nImage1,GPImageList::CompileFlags(Name2));
						break;
					case -13501: // 0 027 0 229 0 033  GP.IListLoad(Name)
						if (MainIl==NULL)
						{
							ImgLId=GPC.GetImageListId("");
							MainIl=&(GPC.a_GPImageList[ImgLId]);
						}

						if (MainIl!=NULL)
							MainIl->LoadList(Name);
						break;
					case -13502: // 0 027 0 229 0 034  GP.IListDelete(Name)
						if (MainIl!=NULL) MainIl->DeleteList();
						break;
					case -13503: // 0 027 0 229 0 035  GP.IListGetCount(Name, RetCount)
						nImage1=0;
						if (MainIl!=NULL) nImage1=MainIl->m_IL.GetImageCount();
						sprintf(Name2,"%d\r",nImage1);
						m_Comm.GPSendLine(Name2);
						break;
					case -13504: // 0 027 0 229 0 036  GP.IListSetBkColor(Name, R, G, B)
						if (MainIl!=NULL) nImage1=MainIl->m_IL.SetBkColor(RGB(po.x,po.y,nImage1));
						break;
					case -13505: // 0 027 0 229 0 037  GP.IListGetBkColor(Name, RetRGB)
						{
							UINT mR=0,mG=0,mB=0;
							if (MainIl!=NULL)
							{
								nImage1=MainIl->m_IL.GetBkColor();
								mR=GetRValue(nImage1);
								mG=GetGValue(nImage1);
								mB=GetBValue(nImage1);
							}
							sprintf(Name2,"%d\x7F%d\x7F%d\r",mR,mG,mB);
							AnsiToDos(Name2,0);
							m_Comm.GPSendLine(Name2);
						}
						break;
					case -13506: // 0 027 0 229 0 038  GP.IListGetImageInfo(Name, nImage, ImageInfo)
						{
							IMAGEINFO ImIn={0};
							if (MainIl!=NULL) nImage1=MainIl->m_IL.GetImageInfo(nImage1,&ImIn);
							sprintf(Name2,"%d\x7F%d\x7F%d\x7F%d\x7F%d\x7%d\x7%d\x7%d\r",
								(DWORD)ImIn.hbmImage,(DWORD)ImIn.hbmMask,ImIn.Unused1,ImIn.Unused2,ImIn.rcImage.top,ImIn.rcImage.left,ImIn.rcImage.bottom,ImIn.rcImage.right);
							AnsiToDos(Name2,0);
							m_Comm.GPSendLine(Name2);
						}
						break;
					case -13507: // 0 027 0 229 0 039  GP.IListSetImageCount(Name,ImageCount)
						if (MainIl!=NULL) MainIl->m_IL.SetImageCount(nImage1);
						break;
					case -13508: // 0 027 0 229 0 040  GP.IListAdd(Name,SName, nImage)
						if (MainIl!=NULL)
						{
							GPImageList *SMainIl;
							if ((ImgLId=GPC.GetImageListId(Name2))>=0 && (SMainIl=&(GPC.a_GPImageList[ImgLId]))!=NULL)
								MainIl->m_IL.Add((HICON)(SMainIl->m_IL.ExtractIcon(nImage1)));
						}
						break;
					case -13509: // 0 027 0 229 0 041  GP.IListAddFromFile(Name,FName)
						if (MainIl!=NULL) MainIl->AddFromFile(Name2,0,RGB(255,255,255));
						break;
					case -13510: // 0 027 0 229 0 042  GP.IListAddFromILFile(Name,FName,nImage)
						if (MainIl!=NULL)
						{
							GPImageList SMainIl;
							SMainIl.LoadList(Name2);
							MainIl->m_IL.Add((HICON)(SMainIl.m_IL.ExtractIcon(nImage1)));
						}
						break;
					case -13511: // 0 027 0 229 0 043  GP.IListRemove(Name,nImage)
						if (MainIl!=NULL) MainIl->m_IL.Remove(nImage1);
						break;
					case -13512: // 0 027 0 229 0 044  GP.IListReplace(Name,nImage,SName,SnImage)
						if (MainIl!=NULL)
						{
							GPImageList *SMainIl;
							if ((ImgLId=GPC.GetImageListId(Name2))>=0 && (SMainIl=&(GPC.a_GPImageList[ImgLId]))!=NULL)
								MainIl->m_IL.Replace(nImage1,(HICON)(SMainIl->m_IL.ExtractIcon(nImage2)));
						}
						break;
					case -13513: // 0 027 0 229 0 045  GP.IListReplaceFromFile(Name,nImage,FName)
						if (MainIl!=NULL) MainIl->ReplaceFromFile(Name2,nImage1);
						break;
					case -13514: // 0 027 0 229 0 046  GP.IListReplaceFromILF(Name,nImage,FName,SnImage)
						if (MainIl!=NULL) MainIl->ReplaceFromILF(nImage1,Name2,nImage2);
						break;
					case -13515: // 0 027 0 229 0 047  GP.IListSetOverlay(Name,nImage,nOverlay)
						if (MainIl!=NULL) MainIl->m_IL.SetOverlayImage(nImage1,nImage2);
						break;
					case -13516: // 0 027 0 229 0 048  GP.IListCopy(Name,nSImage,nDImage)
						if (MainIl!=NULL) MainIl->m_IL.Copy(nImage1,nImage2,ILCF_MOVE);
						break;
					case -13517: // 0 027 0 229 0 049  GP.IListSwap(Name,nSImage,nDImage)
						if (MainIl!=NULL) MainIl->m_IL.Copy(nImage1,nImage2,ILCF_SWAP);
						break;
					case -13518: // 0 027 0 229 0 050  GP.IListSwapEx(SName,nSImage,DName,nDImage)
						if (MainIl!=NULL)
						{
							GPImageList *SMainIl;
							if ((ImgLId=GPC.GetImageListId(Name2))>=0 && (SMainIl=&(GPC.a_GPImageList[ImgLId]))!=NULL)
								MainIl->m_IL.Copy(nImage1,&(SMainIl->m_IL),nImage1,ILCF_SWAP);
						}
						break;
					case -13519: // 0 027 0 229 0 051  GP.IListCopyEx(SName,nSImage,DName,nDImage)
						if (MainIl!=NULL)
						{
							GPImageList *SMainIl;
							if ((ImgLId=GPC.GetImageListId(Name2))>=0 && (SMainIl=&(GPC.a_GPImageList[ImgLId]))!=NULL)
								MainIl->m_IL.Copy(nImage1,&(SMainIl->m_IL),nImage1,ILCF_MOVE);
						}
						break;
					case -13520: // 0 027 0 229 0 052  GP.IListSetDragCursor(Name,nImage,PX,PY)
						if (MainIl!=NULL) MainIl->m_IL.SetDragCursorImage(nImage1,po);
						break;
					case -13521: // 0 027 0 229 0 053  GP.IListWrite(Name)
						if (MainIl!=NULL) MainIl->WriteList(Name);
						break;
					case -13522: // 0 027 0 229 0 054  GP.IListBeginDrag(Name,nImage,PX,PY)
						if (MainIl!=NULL) MainIl->m_IL.BeginDrag(nImage1,po);
						break;
					case -13523: // 0 027 0 229 0 055  GP.IListDragEnter(IdDlg,IdObj,Name,PX,PY)
						if (MainIl!=NULL && IdDlg<MAX_OBJDLG)
						{
							GPUnit *tmp333=NULL;
							if (GetDocument()->a_GPObjType[IdDlg]==0)
							{
								if (GetDocument()->a_GPObjDialog[IdDlg]!=NULL)
									tmp333=GetDocument()->a_GPObjDialog[IdDlg]->GetUnit(IdObj);
							}
							else
							{
								if (GetDocument()->a_GPObjFrame[IdDlg]!=NULL)
									tmp333=GetDocument()->a_GPObjFrame[IdDlg]->GetUnit(IdObj);
							}

							if (tmp333!=NULL && tmp333->UnitHWND!=NULL)
								MainIl->m_IL.DragEnter(CWnd::FromHandle(tmp333->UnitHWND),po);
						}
						break;
					case -13524: // 0 027 0 229 0 056  GP.IListEndDrag(Name)
						if (MainIl!=NULL) MainIl->m_IL.EndDrag();
						break;
					case -13525: // 0 027 0 229 0 057  GP.IListDragLeave(IdDlg,IdObj,Name)
						if (MainIl!=NULL && nImage1<MAX_OBJDLG)
						{
							GPUnit *tmp333=NULL;
							if (GetDocument()->a_GPObjType[nImage1]==0)
							{
								if (GetDocument()->a_GPObjDialog[nImage1]!=NULL)
									tmp333=GetDocument()->a_GPObjDialog[nImage1]->GetUnit(nImage2);
							}
							else
							{
								if (GetDocument()->a_GPObjFrame[nImage1]!=NULL)
									tmp333=GetDocument()->a_GPObjFrame[nImage1]->GetUnit(nImage2);
							}

							if (tmp333!=NULL && tmp333->UnitHWND!=NULL)
								MainIl->m_IL.DragLeave(CWnd::FromHandle(tmp333->UnitHWND));
						}
						break;
					case -13526: // 0 027 0 229 0 058  GP.IListDragMove(Name,PX,PY)
						if (MainIl!=NULL) MainIl->m_IL.DragMove(po);
						break;
					case -13527: // 0 027 0 229 0 059  GP.IListDragShowNolock(Name,fShow)
						if (MainIl!=NULL) MainIl->m_IL.DragShowNolock(nImage1);
						break;
					}
				}
				next_job=job_flag=0;
				break;
			case -13528: // 0 027 0 229 0 060  GP.IListSub(Name,SubStr)
			case -13529: // 0 027 0 229 0 061  GP.IListFn(Name,FnStr,Ret)
				{
					char *tmp=strchr(DosToAnsi(InputBuffer2),';');
					if (tmp!=NULL) *(tmp++)=0; else tmp="";
					GPImageList *MainIl=NULL;
					int ImgLId=GPC.GetImageListId(InputBuffer2);
					if (ImgLId>=0) MainIl=&(GPC.a_GPImageList[ImgLId]);

					if (MainIl==NULL)
					{
						ImgLId=GPC.GetImageListId("");
						MainIl=&(GPC.a_GPImageList[ImgLId]);
						if (MainIl!=NULL) MainIl->LoadList(InputBuffer2);
					}

					if (MainIl)
					{
						switch(job_flag)
						{
						case -13528: // 0 027 0 229 0 060  GP.IListSub(Name,SubStr)
							MainIl->DoMethod(tmp,NULL);
							break;
						case -13529: // 0 027 0 229 0 061  GP.IListFn(Name,FnStr,Ret)
							*GPC.StrTmpOut=0;
							{
								char *oStr=GPC.StrTmpOut;
								MainIl->DoMethod(tmp,oStr);
							}
							SendStringToPICK(GPC.StrTmpOut);
							break;
						}
					}
					next_job=job_flag=0;
					break;
				}
			//***  #######################################################################
			//*** GP_TERM ODBCDataBase COMMANDS (13600-13699)
			//***  #######################################################################
			case -13600: //  0 027 0 230 0 032 GP_TERM  SUB GP.ODBCDatabaseOpen(DBOption:";":DBString)
				GPC.GPODBC_DB.OpenGPDB(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;	break;
			case -13601: //  0 027 0 230 0 033 GP_TERM  SUB GP.ODBCDatabaseClose(DBVar)
				GPC.GPODBC_DB.CloseGPDB(atoi(InputBuffer2));
				next_job=job_flag=0;	break;
			case -13602: //  0 027 0 230 0 034 GP_TERM  SUB GP.ODBCDatabaseFn(DBVar:";":FnStr |||,RetStr)
				GPC.GPODBC_DB.DoDBMethod(DosToAnsi(InputBuffer2),TRUE);
				next_job=job_flag=0;	break;
			case -13603: //  0 027 0 230 0 035 GP_TERM  SUB GP.ODBCDatabaseSub(DBVar:";":SubStr)
				GPC.GPODBC_DB.DoDBMethod(DosToAnsi(InputBuffer2),FALSE);
				next_job=job_flag=0;	break;
			case -13650: //  0 027 0 230 0 082 GP_TERM  SUB GP.ODBCRecordsetOpen(DBVar,RSVar,DBString,DBOption)
				GPC.GPODBC_DB.OpenGPRS(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;	break;
			case -13651: //  0 027 0 230 0 083 GP_TERM  SUB GP.ODBCRecordsetClose(RSVar)
				GPC.GPODBC_DB.CloseGPRS(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;	break;
			case -13652: //  0 027 0 230 0 084 GP_TERM  SUB GP.ODBCRecordsetFn(RSVar,FnStr,RetStr)
				GPC.GPODBC_DB.DoRSMethod(DosToAnsi(InputBuffer2),TRUE);
				next_job=job_flag=0;	break;
			case -13653: //  0 027 0 230 0 085 GP_TERM  SUB GP.ODBCRecordsetSub(RSVar,SubStr)
				GPC.GPODBC_DB.DoRSMethod(DosToAnsi(InputBuffer2),FALSE);
				next_job=job_flag=0;	break;


			//***  #######################################################################
			//*** GP_TERM DAODataBase COMMANDS (13700-13799)
			//***  #######################################################################
			case -13700: //  0 027 0 231 0 032 GP.DAOWorkspaceOpen(WSVar,szName,szUserName,szPassword)
				GPC.GPDAO_WS.OpenGPWS(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;	break;
			case -13701: //  0 027 0 231 0 033 GP.DAOWorkspaceClose(WSVar)
				GPC.GPDAO_WS.CloseGPWS(atoi(InputBuffer2));
				next_job=job_flag=0;	break;
			case -13702: //  0 027 0 231 0 034 GP.DAOWorkspaceFn(WSVar,FnStr,RetStr)
				GPC.GPDAO_WS.DoWSMethod(DosToAnsi(InputBuffer2),TRUE);
				next_job=job_flag=0;	break;
			case -13703: //  0 027 0 231 0 035 GP.DAOWorkspaceSub(WSVar,SubStr)
				GPC.GPDAO_WS.DoWSMethod(DosToAnsi(InputBuffer2),FALSE);
				next_job=job_flag=0;	break;

			case -13750: //  0 027 0 231 0 036 GP.DAOEngineSub(SubStr)
				GPC.GPDAO_WS.DoStaticWSMethod(DosToAnsi(InputBuffer2),FALSE);
				next_job=job_flag=0;	break;
			case -13751: //  0 027 0 231 0 037 GP.DAOEngineFn(SubStr,RetStr)
				GPC.GPDAO_WS.DoStaticWSMethod(DosToAnsi(InputBuffer2),TRUE);
				next_job=job_flag=0;	break;

			case -013710: //  0 027 0 231 0 042 GP.DAODatabaseOpen(WSVar,DBVar,szName,bExclusive,bReadOnly,szConnect)
				GPC.GPDAO_WS.OpenGPDB(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;	break;
			case -013711: //  0 027 0 231 0 043 GP.DAODatabaseCreate(WSVar,DBVar,szName,Options,szLocale)
				GPC.GPDAO_WS.CreateGPDB(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;	break;
			case -013712: //  0 027 0 231 0 044 GP.DAODatabaseClose(DBVar)
				GPC.GPDAO_WS.CloseGPDB(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;	break;
			case -13713: //  0 027 0 231 0 045 GP.DAODatabaseFn(DBVar,FnStr,RetStr)
				GPC.GPDAO_WS.DoDBMethod(DosToAnsi(InputBuffer2),TRUE);
				next_job=job_flag=0;	break;
			case -13714: //  0 027 0 231 0 046 GP.DAODatabaseSub(DBVar,SubStr)
				GPC.GPDAO_WS.DoDBMethod(DosToAnsi(InputBuffer2),FALSE);
				next_job=job_flag=0;	break;

			case -13720: //  0 027 0 231 0 052 GP.DAORecordsetOpen(DBVar,RSVar,RSType,RSOption,RSSQL)
				GPC.GPDAO_WS.OpenGPRS(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;	break;
			case -13721: //  0 027 0 231 0 053 GP.DAORecordsetClose(RSVar)
				GPC.GPDAO_WS.CloseGPRS(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;	break;
			case -13722: //  0 027 0 231 0 054 GP.DAORecordsetFn(RSVar,FnStr,RetStr)
				GPC.GPDAO_WS.DoRSMethod(DosToAnsi(InputBuffer2),TRUE);
				next_job=job_flag=0;	break;
			case -13723: //  0 027 0 231 0 055 GP.DAORecordsetSub(RSVar,SubStr)
				GPC.GPDAO_WS.DoRSMethod(DosToAnsi(InputBuffer2),FALSE);
				next_job=job_flag=0;	break;

			case -13730: //  0 027 0 231 0 062 GP.DAOTableDefOpen(DBVar,TDVar,TDName)
				GPC.GPDAO_WS.OpenGPTDef(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;	break;
			case -13731: //  0 027 0 231 0 063 GP.DAOTableDefCreate(DBVar,TDVar,TDName,TDSrcTable,TDAttr,TDConnect)
				GPC.GPDAO_WS.CreateGPTDef(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;	break;
			case -13732: //  0 027 0 231 0 064 GP.DAOTableDefClose(TDVar)
				GPC.GPDAO_WS.CloseGPTDef(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;	break;
			case -13733: //  0 027 0 231 0 065 GP.DAOTableDefFn(TDVar,FnStr,RetStr)
				GPC.GPDAO_WS.DoTDMethod(DosToAnsi(InputBuffer2),TRUE);
				next_job=job_flag=0;	break;
			case -13734: //  0 027 0 231 0 066 GP.DAOTableDefSub(TDVar,SubStr)
				GPC.GPDAO_WS.DoTDMethod(DosToAnsi(InputBuffer2),FALSE);
				next_job=job_flag=0;	break;

			case -13740: //  0 027 0 231 0 072 GP.DAOQueryDefOpen(DBVar,QDVar,TDName)
				GPC.GPDAO_WS.OpenGPQDef(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;	break;
			case -13741: //  0 027 0 231 0 073 GP.DAOQueryDefCreate(DBVar,QDVar,QDName,QDSQL)
				GPC.GPDAO_WS.CreateGPQDef(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;	break;
			case -13742: //  0 027 0 231 0 074 GP.DAOQueryDefClose(QDVar)
				GPC.GPDAO_WS.CloseGPQDef(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;	break;
			case -13743: //  0 027 0 231 0 075 GP.DAOQueryDefFn(QDVar,FnStr,RetStr)
				GPC.GPDAO_WS.DoQDMethod(DosToAnsi(InputBuffer2),TRUE);
				next_job=job_flag=0;	break;
			case -13744: //  0 027 0 231 0 076 GP.DAOQueryDefSub(QDVar,SubStr)
				GPC.GPDAO_WS.DoQDMethod(DosToAnsi(InputBuffer2),FALSE);
				next_job=job_flag=0;	break;


			//***  #######################################################################
			//*** GP_TERM SPR COMMANDS (13900-13919)
			//***  #######################################################################
			case -13900: // 0 027 0 232 0 032 GPTERM.SprCreate(SprName,nFields)
				{
					char *tmp=strchr(DosToAnsi(InputBuffer2),',');
					if (tmp!=NULL) *(tmp++)=0; else tmp="1";
					CGPSpr *pSpr=GPC.m_SprArray.CreateSpr(InputBuffer2);
					if (pSpr!=NULL) pSpr->Create(InputBuffer2,atoi(tmp));
				}
				next_job=job_flag=0;
				break;
			case -13901: // 0 027 0 232 0 033 GPTERM.SprDelete(SprName)
				GPC.m_SprArray.DeleteSpr(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;
				break;
			case -13903: // 0 027 0 232 0 034 GPTERM.SprSub(SprName,SubStr)
				{
					char *tmp=strchr(DosToAnsi(InputBuffer2),',');
					if (tmp!=NULL) *(tmp++)=0; else tmp="";
					CGPSpr *pSpr=GPC.m_SprArray.GetSpr(InputBuffer2);
					if (pSpr!=NULL)
					{
						pSpr->DoMethod(tmp,NULL);
						if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwNMethodsSubSpr++;
					}
				}
				next_job=job_flag=0;
				break;
			case -13904: // 0 027 0 232 0 035 GPTERM.SprFn(SprName,FnStr,RetStr)
				{
					char *tmp=strchr(DosToAnsi(InputBuffer2),',');
					if (tmp!=NULL) *(tmp++)=0; else tmp="";
					CGPSpr *pSpr=GPC.m_SprArray.GetSpr(InputBuffer2);
					*GPC.StrTmpOut=0;

					if (pSpr!=NULL)
					{
						char *oStr=NULL;
						pSpr->DoMethod(tmp,&oStr);
						if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwNMethodsFnSpr++;
						if (oStr==NULL)	
							SendStringToPICK(GPC.StrTmpOut);
						else
						{
							SendStringToPICK(oStr);
							delete[] oStr;
						}
					}
					else SendStringToPICK("");
				}
				next_job=job_flag=0;
				break;

			//***  #######################################################################
			//*** GP_TERM IOFILE COMMANDS (13920-13949)
			//***  #######################################################################
			case -13920: // 0 027 0 232 0 052 GPTERM.IOFILECreate(IOFILEName)
				{
					DosToAnsi(InputBuffer2);
					/*GPIOFile *pIOFile=*/GPC.m_IOFileArray.CreateIOFile(InputBuffer2);
				}
				next_job=job_flag=0;
				break;
			case -13921: // 0 027 0 232 0 053 GPTERM.IOFILEDelete(IOFILEName)
				GPC.m_IOFileArray.DeleteIOFile(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;
				break;
			case -13923: // 0 027 0 232 0 054 GPTERM.IOFILESub(IOFILEName,SubStr)
				{
					char *tmp=strchr(DosToAnsi(InputBuffer2),';');
					if (tmp!=NULL) *(tmp++)=0; else tmp="";
					GPIOFile *pIOFile=GPC.m_IOFileArray.GetIOFile(InputBuffer2);
					if (pIOFile!=NULL)
						pIOFile->DoMethod(tmp,NULL);
				}
				next_job=job_flag=0;
				break;
			case -13924: // 0 027 0 232 0 055 GPTERM.IOFILEFn(IOFILEName,FnStr,RetStr)
				{
					char *tmp=strchr(DosToAnsi(InputBuffer2),';');
					if (tmp!=NULL) *(tmp++)=0; else tmp="";
					GPIOFile *pIOFile=GPC.m_IOFileArray.GetIOFile(InputBuffer2);
					*GPC.StrTmpOut=0;

					if (pIOFile!=NULL)
					{
						char *oStr=NULL;
						pIOFile->DoMethod(tmp,&oStr);
						if (oStr==NULL)
							SendStringToPICK(GPC.StrTmpOut);
						else
						{
							m_Comm.GPSendSafeBlock(oStr,(int)strlen(oStr));
							m_Comm.GPSendBlock("\r",1);
							delete[] oStr;
						}
					}
					else SendStringToPICK("");
				}
				next_job=job_flag=0;
				break;

			//***  #######################################################################
			//*** GP_TERM REGISTRY COMMANDS (13930-13939)
			//***  #######################################################################
			case -13930: // 0 027 0 232 0 062 GPTERM.RegistryHandleCreate(HandleName)
				GPC.m_HandlerArray.CreateHandle(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;
				break;
			case -13931: // 0 027 0 232 0 063 GPTERM.RegistryHandleDelete(HandleName)
				GPC.m_HandlerArray.DeleteHandle(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;
				break;
			case -13933: // 0 027 0 232 0 064 GPTERM.RegistrySub(HandleName,SubStr)
				GPC.DoRegistryMethod(DosToAnsi(InputBuffer2),NULL);
				next_job=job_flag=0;
				break;
			case -13934: // 0 027 0 232 0 065 GPTERM.RegistryFn(HandleName,FnStr,RetStr)
				{
					char *oStr=NULL;
					GPC.DoRegistryMethod(DosToAnsi(InputBuffer2),&oStr);
					if (oStr==NULL)	SendStringToPICK(GPC.StrTmpOut);
					else
					{
						m_Comm.GPSendSafeBlock(AnsiToDos(oStr,1),(int)strlen(oStr));
						m_Comm.GPSendBlock("\r",1);
						delete[] oStr;
					}
				}
				next_job=job_flag=0;
				break;

			//***  #######################################################################
			//*** GP_TERM SEPARATE VIEW COMMANDS (13940-13949)
			//***  #######################################################################
			case -13940: // 0 027 0 232 0 072 SViewSub(Method,Params)
				m_DlgSeparateView.DoMethod(DosToAnsi(InputBuffer2),NULL);
				next_job=job_flag=0;
				break;
			case -13941: // 0 027 0 232 0 073 SViewFn(Method,Params,RetVal)
				{
					char *oStr=NULL;
					m_DlgSeparateView.DoMethod(DosToAnsi(InputBuffer2),&oStr);
					if (oStr==NULL)	SendStringToPICK(GPC.StrTmpOut);
					else
					{
						m_Comm.GPSendSafeBlock(AnsiToDos(oStr,2),(int)strlen(oStr));
						m_Comm.GPSendBlock("\r",1);
						delete[] oStr;
					}
				}
				next_job=job_flag=0;
				break;


			//***  #######################################################################
			//*** GP_TERM EXCEL COMMANDS (14000-14500)
			//***  #######################################################################
			case -14000: // 014000 0 027 0 233 0 032 GP.ExcelApplicationClose
				{
					CString strstr=DosToAnsi(InputBuffer2);
					GPC.GPXL.CloseGPExcelApp(strstr);
					next_job=job_flag=0;
				}
				break;
			case -14001: // 014001 0 027 0 233 0 033 GP.ExcelApplicationCreate
				{
					CString strstr;
					char *oStr=GPC.StrTmpOut;
					*GPC.StrTmpOut=0;
					GPC.GPXL.CreateGPExcelApp(strstr,oStr);
					SendStringToPICK(oStr);
					next_job=job_flag=0;
				}
				break;
			case -14002: // 014002 0 027 0 233 0 034 GP.ExcelApplicationFn(EVar,FnStr,RetStr)
				{
					CString strstr;
					char *oStr=GPC.StrTmpOut;
					*GPC.StrTmpOut=0;
					int IdApp=0;
					char bufff[256];
					char* posf=DosToAnsi(InputBuffer2);
					while((*posf!=',') && (*posf!=0) && (IdApp<255))
					{
						bufff[IdApp]=*posf;
						posf++;
						IdApp++;
					}
					bufff[IdApp]=0;
					IdApp=atoi(bufff);
					if (*posf!=0)
						strstr=(++posf);
					else
						strstr="";
					GPC.GPXL.DoEAMethod(IdApp,strstr,oStr,TRUE);
					SendStringToPICK(oStr);
					if (oStr!=GPC.StrTmpOut)
						delete[] oStr;
					next_job=job_flag=0;
				}
				break;
			case -14003: // 014003 0 027 0 233 0 035 GP.ExcelApplicationSub(EVar,SubStr)
				{
					CString strstr;
					int IdApp=0;
					char bufff[256];
					char* posf=DosToAnsi(InputBuffer2);
					while((*posf!=',') && (*posf!=0) && (IdApp<255))
					{
						bufff[IdApp]=*posf;
						posf++;
						IdApp++;
					}
					bufff[IdApp]=0;
					IdApp=atoi(bufff);
					if (*posf!=0)
						strstr=(++posf);
					else
						strstr="";
					GPC.GPXL.DoEAMethod(IdApp,strstr,NULL,FALSE);
					next_job=job_flag=0;
				}
				break;
			case -14004: // 014004 0 027 0 233 0 036 GP.ExcelGPRangeClose(EVar)
				{
					CString strstr=DosToAnsi(InputBuffer2);
					GPC.GPXL.CloseGPOLERange(strstr);
					next_job=job_flag=0;
				}
				break;
			case -14005: // 014005 0 027 0 233 0 037 GP.ExcelGPRangeCreate(CrStr,RetStr)
				{
					CString strstr=DosToAnsi(InputBuffer2);
					char *oStr=GPC.StrTmpOut;
					*GPC.StrTmpOut=0;
					GPC.GPXL.CreateGPOLERange(strstr,oStr);
					SendStringToPICK(oStr);
					next_job=job_flag=0;
				}
				break;
			case -14006: // 014006 0 027 0 233 0 038 GP.ExcelGPRangeFn(EVar,FnStr,RetStr)
				{
					CString strstr;
					char *oStr=GPC.StrTmpOut;
					*GPC.StrTmpOut=0;
					int IdApp=0;
					char bufff[256];
					char* posf=DosToAnsi(InputBuffer2);
					while((*posf!=',') && (*posf!=0) && (IdApp<255))
					{
						bufff[IdApp]=*posf;
						posf++;
						IdApp++;
					}
					bufff[IdApp]=0;
					IdApp=atoi(bufff);
					if (*posf!=0)
						strstr=(++posf);
					else
						strstr="";
					GPC.GPXL.DoRMethod(IdApp,strstr,oStr,TRUE);
					SendStringToPICK(oStr);
					if (oStr!=GPC.StrTmpOut)
						delete[] oStr;
					next_job=job_flag=0;
				}
				break;
			case -14007: // 014007 0 027 0 233 0 039 GP.ExcelGPRangeSub(EVar,SubStr)
				{
					CString strstr;
					int IdApp=0;
					char bufff[256];
					char* posf=DosToAnsi(InputBuffer2);
					while((*posf!=',') && (*posf!=0) && (IdApp<255))
					{
						bufff[IdApp]=*posf;
						posf++;
						IdApp++;
					}
					bufff[IdApp]=0;
					IdApp=atoi(bufff);
					if (*posf!=0)
						strstr=(++posf);
					else
						strstr="";
					GPC.GPXL.DoRMethod(IdApp,strstr,NULL,FALSE);
					next_job=job_flag=0;
				}
				break;
			case -14008: // 014008 0 027 0 233 0 040 GP.ExcelRangeClose(EVar)
				{
					CString strstr=DosToAnsi(InputBuffer2);
					GPC.GPXL.CloseGPExcelRange(strstr);
					next_job=job_flag=0;
				}
				break;
			case -14009: // 014009 0 027 0 233 0 041 GP.ExcelRangeCreate(CrStr,RetStr)
				{
					CString strstr=DosToAnsi(InputBuffer2);
					char *oStr=GPC.StrTmpOut;
					*GPC.StrTmpOut=0;
					GPC.GPXL.CreateGPExcelRange(strstr,oStr);
					SendStringToPICK(oStr);
					next_job=job_flag=0;
				}
				break;
			case -14010: // 014010 0 027 0 233 0 042 GP.ExcelRangeFn(EVar,FnStr,RetStr)
				{
					CString strstr;
					char *oStr=GPC.StrTmpOut;
					*GPC.StrTmpOut=0;
					int IdApp=0;
					char bufff[256];
					char* posf=DosToAnsi(InputBuffer2);;
					while((*posf!=',') && (*posf!=0) && (IdApp<255))
					{
						bufff[IdApp]=*posf;
						posf++;
						IdApp++;
					}
					bufff[IdApp]=0;
					IdApp=atoi(bufff);
					if (*posf!=0)
						strstr=(++posf);
					else
						strstr="";
					GPC.GPXL.DoERMethod(IdApp,strstr,oStr,TRUE);
					SendStringToPICK(oStr);
					if (oStr!=GPC.StrTmpOut)
						delete[] oStr;
					next_job=job_flag=0;
				}
				break;
			case -14011: // 014011 0 027 0 233 0 043 GP.ExcelRangeSub(EVar,SubStr)
				{
					CString strstr;
					int IdApp=0;
					char bufff[256];
					char* posf=DosToAnsi(InputBuffer2);;
					while((*posf!=',') && (*posf!=0) && (IdApp<255))
					{
						bufff[IdApp]=*posf;
						posf++;
						IdApp++;
					}
					bufff[IdApp]=0;
					IdApp=atoi(bufff);
					if (*posf!=0)
						strstr=(++posf);
					else
						strstr="";
					GPC.GPXL.DoERMethod(IdApp,strstr,NULL,FALSE);
					next_job=job_flag=0;
				}
				break;
			case -14012: // 014012 0 027 0 233 0 044 GP.ExcelWorkbookClose(EVar)
				{
					CString strstr=DosToAnsi(InputBuffer2);
					GPC.GPXL.CloseGPExcelWorkbook(strstr);
					next_job=job_flag=0;
				}
				break;
			case -14013: // 014013 0 027 0 233 0 045 GP.ExcelWorkbookCreate(CrStr,RetStr)
				{
					CString strstr=DosToAnsi(InputBuffer2);
					char *oStr=GPC.StrTmpOut;
					*GPC.StrTmpOut=0;
					GPC.GPXL.CreateGPExcelWorkbook(strstr,oStr);
					SendStringToPICK(oStr);
					next_job=job_flag=0;
				}
				break;
			case -14014: // 014014 0 027 0 233 0 046 GP.ExcelWorkbookFn(EVar,FnStr,RetStr)
				{
					CString strstr;
					char *oStr=GPC.StrTmpOut;
					*GPC.StrTmpOut=0;
					int IdApp=0;
					char bufff[256];
					char* posf=DosToAnsi(InputBuffer2);
					while((*posf!=',') && (*posf!=0) && (IdApp<255))
					{
						bufff[IdApp]=*posf;
						posf++;
						IdApp++;
					}
					bufff[IdApp]=0;
					IdApp=atoi(bufff);
					if (*posf!=0)
						strstr=(++posf);
					else
						strstr="";
					GPC.GPXL.DoWbMethod(IdApp,strstr,oStr,TRUE);
					SendStringToPICK(oStr);
					if (oStr!=GPC.StrTmpOut)
						delete[] oStr;
					next_job=job_flag=0;
				}
				break;
			case -14015: // 014015 0 027 0 233 0 047 GP.ExcelWorkbookSub(EVar,SubStr)
				{
					CString strstr;
					int IdApp=0;
					char bufff[256];
					char* posf=DosToAnsi(InputBuffer2);;
					while((*posf!=',') && (*posf!=0) && (IdApp<255))
					{
						bufff[IdApp]=*posf;
						posf++;
						IdApp++;
					}
					bufff[IdApp]=0;
					IdApp=atoi(bufff);
					if (*posf!=0)
						strstr=(++posf);
					else
						strstr="";
					GPC.GPXL.DoWbMethod(IdApp,strstr,NULL,FALSE);
					next_job=job_flag=0;
				}
				break;
			case -14016: // 014016 0 027 0 233 0 048 GP.ExcelWorksheetClose(EVar)
				{
					CString strstr=DosToAnsi(InputBuffer2);
					GPC.GPXL.CloseGPExcelWorksheet(strstr);
					next_job=job_flag=0;
				}
				break;
			case -14017: // 014017 0 027 0 233 0 049 GP.ExcelWorksheetCreate(CrStr,RetStr)
				{
					CString strstr=DosToAnsi(InputBuffer2);
					char *oStr=GPC.StrTmpOut;
					*GPC.StrTmpOut=0;
					GPC.GPXL.CreateGPExcelWorksheet(strstr,oStr);
					SendStringToPICK(oStr);
					next_job=job_flag=0;
				}
				break;
			case -14018: // 014018 0 027 0 233 0 050 GP.ExcelWorksheetFn(EVar,FnStr,RetStr)
				{
					CString strstr;
					char *oStr=GPC.StrTmpOut;
					*GPC.StrTmpOut=0;
					int IdApp=0;
					char bufff[256];
					char* posf=DosToAnsi(InputBuffer2);
					while((*posf!=',') && (*posf!=0) && (IdApp<255))
					{
						bufff[IdApp]=*posf;
						posf++;
						IdApp++;
					}
					bufff[IdApp]=0;
					IdApp=atoi(bufff);
					if (*posf!=0)
						strstr=(++posf);
					else
						strstr="";
					GPC.GPXL.DoWsMethod(IdApp,strstr,oStr,TRUE);
					SendStringToPICK(oStr);
					if (oStr!=GPC.StrTmpOut)
						delete[] oStr;
					next_job=job_flag=0;
				}
				break;
			case -14019: // 014019 0 027 0 233 0 051 GP.ExcelWorksheetSub(EVar,SubStr)
				{
					CString strstr;
					char *oStr=GPC.StrTmpOut;
					*GPC.StrTmpOut=0;
					int IdApp=0;
					char bufff[256];
					char* posf=DosToAnsi(InputBuffer2);
					while((*posf!=',') && (*posf!=0) && (IdApp<255))
					{
						bufff[IdApp]=*posf;
						posf++;
						IdApp++;
					}
					bufff[IdApp]=0;
					IdApp=atoi(bufff);
					if (*posf!=0)
						strstr=(++posf);
					else
						strstr="";
					GPC.GPXL.DoWsMethod(IdApp,strstr,oStr,FALSE);
					next_job=job_flag=0;
				}
				break;
			case -14020: // 014020 0 027 0 233 0 052 GP.ExcelFn(FnStr,RetStr)
				{
					CString strstr=DosToAnsi(InputBuffer2);
					char *oStr=GPC.StrTmpOut;
					*GPC.StrTmpOut=0;
					GPC.GPXL.DoMethod(strstr,oStr,TRUE);
					SendStringToPICK(oStr);
					if (oStr!=GPC.StrTmpOut)
						delete[] oStr;
					next_job=job_flag=0;
				}
				break;
			case -14021: // 014021 0 027 0 233 0 053 GP.ExcelSub(SubStr)
				{
					CString strstr=DosToAnsi(InputBuffer2);
					GPC.GPXL.DoMethod(strstr,NULL,FALSE);
					next_job=job_flag=0;
				}
				break;
			case -14022: // 014022 0 027 0 233 0 054 GP.ExcelWorkbookOpen(CrStr,RetStr)
				{
					CString strstr=DosToAnsi(InputBuffer2);
					char *oStr=GPC.StrTmpOut;
					*GPC.StrTmpOut=0;
					GPC.GPXL.OpenGPExcelWorkbook(strstr,oStr);
					SendStringToPICK(oStr);
					next_job=job_flag=0;
				}
				break;

			default: // Продолжение выполнения сложных команд
					next_job=job_flag=0;
					break;
			}
		}
		else
		if (job_flag>-17000)
		{
			switch(job_flag)
			{
				//CCOMServer m_COMServer;
			case -15000: /* GP.COMDoSub */
			case -15001: /* GP.COMDoFn */
				{
					DosToAnsi(InputBuffer2);
					int DllId=m_COMServer.GetIdByName(ExtractField(ExtractField(InputBuffer2,1,";"),1,","));
					char *oStr=NULL;
					if (DllId>=0)
					{
						const char *posParam=FindField(InputBuffer2,2,";");
						if (!posParam) posParam="";
						m_COMServer.DoMethod(DllId,ExtractField(ExtractField(InputBuffer2,1,";"),2,","),posParam,&oStr,(job_flag==-15001));
					}

					if (job_flag==-15001)
					{
						if (oStr)
						{
							AnsiToDos(oStr,0);
							m_Comm.GPSendBlock(oStr,(int)strlen(oStr));
							delete []oStr;
						}
						m_Comm.GPSendBlock("\r",1);
					}
				}
				next_job=job_flag=0;
				break;
			case -15002: /* GP.COMLoadDll */
			case -15003: /* GP.COMLoadExe */
				{
					DosToAnsi(InputBuffer2);
					CString csName=ExtractField(InputBuffer2,1,",");
					CString ProgId=ExtractField(InputBuffer2,2,",");
					CString csSubName=ExtractField(InputBuffer2,3,",");
					CString WndId=ExtractField(InputBuffer2,4,",");
					HWND tmpHWND=::GetDesktopWindow();
					if (atoi(WndId)==-2) tmpHWND=GPC.m_hViewWnd;
					else
						if (WndId.Find(":",0)>=0)
						{
							GPUnit *tmp=NULL;
							if (WndId[0]==':')
								tmp=GetDocument()->GetScrUnit(0,atoi(ExtractField(WndId,2,":")));
							else
								tmp=GetDocument()->GetDlgUnit(atoi(WndId),atoi(ExtractField(WndId,2,":")));
							if (tmp) tmpHWND=tmp->UnitHWND;
						}
						else if (WndId!="") tmpHWND=(HWND)atoi(WndId);


					char tmpout[100];
					sprintf(tmpout,"%d\r",(job_flag==-15002)?m_COMServer.LoadDll(ProgId,tmpHWND,csName,csSubName):m_COMServer.LoadExe(ProgId,tmpHWND,csName,csSubName));
					m_Comm.GPSendBlock(tmpout,(int)strlen(tmpout));
				}
				next_job=job_flag=0;
				break;
			case -15004: /* GP.COMUnload */
				if (atoi(InputBuffer2)==-1)	m_COMServer.UnloadAll();
				else 
					if (*InputBuffer2) m_COMServer.Unload(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;
				break;

				//DllServer m_DllServer;
			case -15100: /* GP.DllDoSub */
			case -15101: /* GP.DllDoFn */
				{
					DosToAnsi(InputBuffer2);
					int DllId=m_DllServer.GetIdByName(ExtractField(ExtractField(InputBuffer2,1,";"),1,","));
					char *oStr=NULL;
					if (DllId>=0)
					{
						const char *posParam=FindField(InputBuffer2,2,";");
						if (!posParam) posParam="";
						m_DllServer.DoMethod(DllId,ExtractField(ExtractField(InputBuffer2,1,";"),2,","),posParam,&oStr,(job_flag==-15101));
					}

					if (job_flag==-15101)
					{
						if (oStr)
						{
							AnsiToDos(oStr,0);
							m_Comm.GPSendBlock(oStr,(int)strlen(oStr));
							delete []oStr;
						}
						m_Comm.GPSendBlock("\r",1);
					}
				}
				next_job=job_flag=0;
				break;
			case -15102: /* GP.DllLoad */
				{
					DosToAnsi(InputBuffer2);
					CString csName=ExtractField(InputBuffer2,1,",");
					CString ProgId=ExtractField(InputBuffer2,2,",");
					CString csSubName=ExtractField(InputBuffer2,3,",");
					char tmpout[100];
					sprintf(tmpout,"%d\r",m_DllServer.Load(ProgId,csName,csSubName));
					m_Comm.GPSendBlock(tmpout,(int)strlen(tmpout));
				}
				next_job=job_flag=0;
				break;
			case -15103: /* GP.DllUnload */
				if (atoi(InputBuffer2)==-1)	m_DllServer.UnloadAll();
				else 
					if (*InputBuffer2) m_DllServer.Unload(DosToAnsi(InputBuffer2));
				next_job=job_flag=0;
				break;


			default: // Продолжение выполнения сложных команд
				next_job=job_flag=0;
				break;
			}
		}
	}
	return nbyte-i;


}

int CGP_TermView::DoEscSeq(int CurrEscVariant)
{
// Непосредственное выполнение ESC последовательностей
// int CGP_TermView::DoEscSeq(int CurrEscVariant)
	int	ret=0,i;
	job_flag=0;
if (CurrEscVariant<100)
{
	GPScreen *CurScr=GetDocument()->GetActiveScreen();
	switch(CurrEscVariant)
	{
	case 1: // CUP move cursor to Y X
		m_TermCap.TranslateFoundEsc();
		if (m_TermCap.m_Vars.Pos_X>0) m_TermCap.m_Vars.Pos_X--;
		if (m_TermCap.m_Vars.Pos_Y>0) m_TermCap.m_Vars.Pos_Y--;
		CurScr->SetCursorPosition(m_TermCap.m_Vars.Pos_X,m_TermCap.m_Vars.Pos_Y);
		{
			NEAREST9X9 nearest={0};
			if (GPC.dwMBReposition&0x40000000) GPC.dwMBReposition|=0x80000000;
			CurScr->GetNearestChars(&nearest);
			if (!(nearest.left) && GPC.dwMBReposition)
			{
				//GPC.dwMBReposition|=0x80000000;
			}
		}
		break;
	case 2: /* CUB cursor left */
		{
			m_TermCap.TranslateFoundEsc();
			if (m_TermCap.m_Vars.Pos_X==0) m_TermCap.m_Vars.Pos_X=1;
			Point po=CurScr->GetCursorPosition();
			po.X-=m_TermCap.m_Vars.Pos_X;
			int scrcx=CurScr->GetScreenSize().Width;
			while(po.X<0)
			{
				po.X+=scrcx;
				CurScr->CursorMoveUp();
			}
			CurScr->SetCursorPosition(po.X,CurScr->GetCursorPosition().Y);
			if (m_CaptureFile) fputc(' ',m_CaptureFile);
			m_DlgSeparateView.AppendCharToOutput(9,1);
		}
		break;
	case 3: /* CUU cursor up */
		{
			m_TermCap.TranslateFoundEsc();
			if (m_TermCap.m_Vars.Pos_Y==0) m_TermCap.m_Vars.Pos_Y=1;
			int cnt=m_TermCap.m_Vars.Pos_Y;
			while(cnt-->0)
				CurScr->CursorMoveUp();

			m_DlgSeparateView.AppendStringToOutput("");
			if (m_CaptureFile) fputs("",m_CaptureFile);
		}
		break;
	case 4: /* CUF cursor right */
		{
			m_TermCap.TranslateFoundEsc();
			if (m_TermCap.m_Vars.Pos_X==0) m_TermCap.m_Vars.Pos_X=1;
			Point po=CurScr->GetCursorPosition();
			po.X+=m_TermCap.m_Vars.Pos_X;
			int scrcx=CurScr->GetScreenSize().Width;
			while(po.X>=scrcx)
			{
				po.X-=scrcx;
				CurScr->CursorMoveDown();
			}

			CurScr->SetCursorPosition(po.X,CurScr->GetCursorPosition().Y);
			if (m_CaptureFile) fputc(' ',m_CaptureFile);
			m_DlgSeparateView.AppendCharToOutput(' ',1);
		}
		break;
	case 5: /* CUD cursor down */
		{
			m_TermCap.TranslateFoundEsc();
			if (m_TermCap.m_Vars.Pos_Y==0) m_TermCap.m_Vars.Pos_Y=1;
			int cnt=m_TermCap.m_Vars.Pos_Y;
			while(cnt-->0)
				CurScr->CursorMoveDown();

			m_DlgSeparateView.AppendCharToOutput('\r',1);
			if (m_CaptureFile) fputs("",m_CaptureFile);
		}
		break;
	case 6: /* CHA Cursor Horizntal Absolute */
		m_TermCap.TranslateFoundEsc();
		CurScr->SetCursorPosition(m_TermCap.m_Vars.Pos_X,CurScr->GetCursorPosition().Y);
		break;
	case 7: /* CVA Cursor Vertical Absolute */
		m_TermCap.TranslateFoundEsc();
		CurScr->SetCursorPosition(CurScr->GetCursorPosition().X,m_TermCap.m_Vars.Pos_Y);
		break;
	case 8: // Save cursor position
		CurScr->SaveCursorPosition();
		break;
	case 9: // Restore cursor position
		CurScr->RestoreCursorPosition();
		break;
	case 10: /* clear screen */
		CurScr->ClearScreen();
		CurScr->SetCursorPosition(0,0);
		if (m_CaptureFile) fputs("",m_CaptureFile);
		m_DlgSeparateView.AppendStringToOutput("");
		break;
	case 11: /* clear end of screen */
		if (CurScr->GetCursorPosition().X || CurScr->GetCursorPosition().Y)
			CurScr->ClearEndOfScreen(); 
		else CurScr->ClearScreen();
		break;
	case 12: /* clear end of line */ 	CurScr->ClearEndOfLine();	  break;
	case 14: // ClearToBeginOfLine
		CurScr->ClearToBeginOfLine();
		break;
	case 20: /* save reg  */
		m_TermCap.TranslateFoundEsc();
		CurScr->SaveScrRgn(
			Rect(
				m_TermCap.m_Vars.Pos_X, 
				m_TermCap.m_Vars.Pos_Y,
				m_TermCap.m_Vars.Pos_X2+1-m_TermCap.m_Vars.Pos_X,
				m_TermCap.m_Vars.Pos_Y2+1-m_TermCap.m_Vars.Pos_Y),
			m_TermCap.m_Vars.Length);
		SendChar('1');
		break;
	case 21: /* restore reg */
		m_TermCap.TranslateFoundEsc();
		CurScr->CopySaveScrRgn(m_TermCap.m_Vars.Length,Point(m_TermCap.m_Vars.Pos_X,m_TermCap.m_Vars.Pos_Y));
		SendChar('1');
		break;
	case 22: /* Create Region with C fill */
		m_TermCap.TranslateFoundEsc();
		for(i=m_TermCap.m_Vars.Pos_Y;i<=m_TermCap.m_Vars.Pos_Y2;i++)
			CurScr->CharLine(Point(m_TermCap.m_Vars.Pos_X,i),Point(m_TermCap.m_Vars.Pos_X2+1,i),(char)m_TermCap.m_Vars.ClrRef);
		SendChar('1');
		break;
	case 23: /* lRecolor string from x1 length L */
		m_TermCap.TranslateFoundEsc();
		CurScr->RecolorString(m_TermCap.m_Vars.Pos_X,m_TermCap.m_Vars.Pos_Y,m_TermCap.m_Vars.Length);
		SendChar('1');
		break;
	case 24: /* Remove Cursor */	CurScr->SetCursorState(FALSE);	break;
	case 25: /* Normal Cursor */
	case 26: /* Full Cursor */ 		CurScr->SetCursorState(TRUE); break;
	case 27: /* Box Single border */ 
		m_TermCap.TranslateFoundEsc();
		CurScr->TextBox(
			Rect(
				m_TermCap.m_Vars.Pos_X,
				m_TermCap.m_Vars.Pos_Y,
				m_TermCap.m_Vars.Pos_X2-m_TermCap.m_Vars.Pos_X,
				m_TermCap.m_Vars.Pos_Y2-m_TermCap.m_Vars.Pos_Y),
			0+0x10000);
		SendChar('1');
		break;
	case 28: /* Box Dowble border */
		m_TermCap.TranslateFoundEsc();
		CurScr->TextBox(
			Rect(
				m_TermCap.m_Vars.Pos_X,
				m_TermCap.m_Vars.Pos_Y,
				m_TermCap.m_Vars.Pos_X2-m_TermCap.m_Vars.Pos_X,
				m_TermCap.m_Vars.Pos_Y2-m_TermCap.m_Vars.Pos_Y),
			1+0x10000);
		SendChar('1');
		break;
	case 29: /* HorLine with Ch from X1 to X2 */
		m_TermCap.TranslateFoundEsc();
		CurScr->CharLine(
			Point(m_TermCap.m_Vars.Pos_X,m_TermCap.m_Vars.Pos_Y),
			Point(m_TermCap.m_Vars.Pos_X2+1,m_TermCap.m_Vars.Pos_Y),
			(char)m_TermCap.m_Vars.ClrRef);
		SendChar('1');
		break;
	case 30: /* VerLine with Ch from Y1 to Y2 */
		m_TermCap.TranslateFoundEsc();
		CurScr->CharLine(
			Point(m_TermCap.m_Vars.Pos_X,m_TermCap.m_Vars.Pos_Y),
			Point(m_TermCap.m_Vars.Pos_X,m_TermCap.m_Vars.Pos_Y2+1),
			(char)m_TermCap.m_Vars.ClrRef);
		SendChar('1');
		break;
	case 31: /* Start Old Mouse */	OldMouse=true;  break;
	case 32: /* End Old Mouse */	OldMouse=false; break;
	case 33: /* Response Old Mouse */
		{
			switch(MouseLastFlag)
			{
			case MK_CONTROL|MK_LBUTTON: SendChar(57); break;
			case MK_CONTROL|MK_RBUTTON: SendChar(58); break;
			case MK_CONTROL|MK_MBUTTON: SendChar(59); break;
			case MK_SHIFT|MK_LBUTTON:	SendChar(54); break;
			case MK_SHIFT|MK_RBUTTON:	SendChar(55); break;
			case MK_SHIFT|MK_MBUTTON:	SendChar(56); break;
			case MK_LBUTTON:			SendChar(51); break;
			case MK_RBUTTON:			SendChar(52); break;
			case MK_MBUTTON:			SendChar(53); break;
			default:					SendChar(1); break;
			}
			Point poCh=CurScr->GetCharPosByWndPos(Point(MouseLastPoint.x,MouseLastPoint.y));
			SendChar((char)(poCh.X+' '));
			SendChar((char)(poCh.Y+' '));
		}
		break;

	case 34: /* load table */
	case 35: /* DOS FILE EXIST */  	string_ptr=0; next_job=-CurrEscVariant; job_flag=-1; break;

	case 36: /* return to home dir */ _chdrive(GPC.HomeDrive);_chdir(GPC.app_path); break;
	case 37: /* support color (unrel) */ SendChar('1'); break;

	case 38: /* dos command */
		string_ptr=0;
		*name_curent=0;
		next_job=-CurrEscVariant;
		job_flag=-1;
		break;
	case 39: /* dos command */
		string_ptr=0;
		next_job=-CurrEscVariant;
		job_flag=-1;
		break;
	case 40: /* MOUSE ENABLE REQUEST */  SendChar('1'); break;

	case 41: /* message TWOMES */
	case 42: /* message ASKWIN */
	case 43: /* message ONEMES */		string_ptr=0; next_job=-CurrEscVariant; job_flag=-1; 	break;

	case 44: /* shadow bottom_right */
		m_TermCap.TranslateFoundEsc();
		CurScr->ShadowOld(
			Rect(
			m_TermCap.m_Vars.Pos_X,
			m_TermCap.m_Vars.Pos_Y,
			m_TermCap.m_Vars.Pos_X2+1-m_TermCap.m_Vars.Pos_X,
			m_TermCap.m_Vars.Pos_Y2+1-m_TermCap.m_Vars.Pos_Y),
			0);
		SendChar('1');
		break;
	case 45: /* shadow top_left */
		m_TermCap.TranslateFoundEsc();
		CurScr->ShadowOld(
			Rect(
			m_TermCap.m_Vars.Pos_X,
			m_TermCap.m_Vars.Pos_Y,
			m_TermCap.m_Vars.Pos_X2+1-m_TermCap.m_Vars.Pos_X,
			m_TermCap.m_Vars.Pos_Y2+1-m_TermCap.m_Vars.Pos_Y),
			1);
		SendChar('1');
		break;
	case 46: /* INSERT MODE OFF */	InsMode=false;	break;
	case 47: /* INSERT MODE ON */	InsMode=true;	break;
	case 48: /* MODE AJ.WRITEDOS */	GPC.ModeSendToDos= AJ_WRITEDOS	; break;
	case 49: /* MODE R03WRITEDOS */	GPC.ModeSendToDos= R03WRITEDOS	; break;
	case 50: /* MODE R03READDOS */	GPC.ModeSendToPick=R03READDOS	; break;
	case 51: /* MODE AJ.READDOS */	GPC.ModeSendToPick=AJ_READDOS	; break;
	case 52: /* MODE AJ.READNEW */	GPC.ModeSendToPick=AJ_READNEW	; break;
	case 53: /* WRITEDOS */
		if (GPC.ModeSendToDos==AJ_WRITEDOS) stopchar=255;else stopchar=4;
		string_ptr=0; next_job=-CurrEscVariant;  job_flag=-1; break;
	case 54: /* READDOS */			string_ptr=0; next_job=-CurrEscVariant;  job_flag=-1;	break;
	case 55: /* MAIN ON заглушка */	SendChar('1'); break;
	case 56: /* MAIN OFF заглушка */ break;
	case 57: /* TERM version */
		m_Comm.GPSendLine(m_TermVersion);
		m_Comm.GPSendLine("\r");
		iSkip_0=1;
		iSkip_10=1;
		iSkip_13=1;
		break;
	case 58: /* TERM EXIT  */
//		if (GPC.AdmIsOn==FALSE)
			GPC.Flags|=GP_CUR_EXITFLAG;
		AfxGetApp()->GetMainWnd()->PostMessage(WM_CLOSE);
		if (m_CaptureFile) fputs("",m_CaptureFile);
		m_DlgSeparateView.AppendStringToOutput("");
		break;
	case 59: /* AJ.EDIT.STR */
		SendChar('0');SendChar('\r');
		#ifdef RUS
			MessageBox("AJ.EDIT.STR не реализована.\nОбратитесь к администратору",GPC.ErrBoxCaption,MB_OK |MB_ICONEXCLAMATION );
		#else
			MessageBox("AJ.EDIT.STR UnSupport.",GPC.ErrBoxCaption,MB_OK |MB_ICONEXCLAMATION );
		#endif
		job_flag=0; break;
	case 60: /* LOAD MENU */
	case 61: /* CONVERT TO TEXT6 */
	case 62: /* CONVERT TO BIN8 */
	case 63: /* DOS COPYFILE */
	case 64: /* DOS DELETE FILE */
	case 65: /* DOS RENAME FILE */	*name_curent=0; string_ptr=0; next_job=-CurrEscVariant; job_flag=-1; 	break;
	case 66: /* RESTART TERM */
		{
			if (m_CaptureFile) fputs("",m_CaptureFile);
			m_DlgSeparateView.AppendStringToOutput("");
			_execl("UPD_TERM.EXE","UPD_TERM.EXE",m_Comm.GPSectionName,NULL);
		}
		break;
	case 68: /* PRINT SCR*/
	case 69: /*CREATE SCR*/
	case 70: /*CREATE WND*/
	case 71: /*DELETE SCR*/
	case 72: /*DELETE WND*/
		string_ptr=0; next_job=-CurrEscVariant;  job_flag=-1; break;
	case 73: /*AUTODECODE*/
		m_TermCap.TranslateFoundEsc();
		AutoDecodFT=(m_TermCap.m_Vars.typeUnit==1)?true:false;
		break;
	case 74: /*CHANGE DIR*/
	case 75: /*GET FILE PROPERTIES*/
	case 76:/* GP_TERM OPEN FILE */
	case 77:/* GP_TERM CLOSE FILE */
	case 78:/* GP_TERM FILE GETCHAR*/
	case 79:/* GP_TERM FILE PUTCHAR*/
	case 80:/* GP_TERM FILE GETSTR*/
	case 81:/* GP_TERM FILE PUTSTR*/
	case 82:/* GP_TERM FILE READBLOCK*/
	case 83:/* GP_TERM FILE WRITEBLOCK*/
	case 84:/* GP_TERM FILE SEEK*/
	case 85:/* GP_TERM FILE SEEKTOBEGIN*/
	case 86:/* GP_TERM FILE SEEKTOEND*/
	case 87:/* GP_TERM FILE FLUSH*/
	case 88:/* GP_TERM FILE GETLENGTH*/
	case 89:/* GP_TERM FILE SETLENGTH*/
	case 90:/* GP_TERM FILE GETPOSITION*/
	case 91:/* GP_TERM FILE GETSTATUS*/
	case 92:/* GP_TERM FILE LOCKRANGE*/
	case 93:/* GPTERM FILE UNLOCKRANGE*/
	case 94:/* GPTERM FILE SETCONV*/
	case 95:/* GPTERM FILE POSROLLBACK*/
	case 96:/* GPTERM FILE GPGetBlocksInfo*/
	case 97:/* GPTERM FILE FINDPLACE*/
	case 98:/* GP_TERM FILE MKDIR*/
	case 99:/* GP_TERM FILE GETDIRCONTENTS*/
		string_ptr=0; next_job=-CurrEscVariant;  job_flag=-1; break;

	default: ret=-1; break;
	}
}
else
if (CurrEscVariant<200)
{
	GPScreen *CurScr=GetDocument()->GetActiveScreen();
	switch(CurrEscVariant)
	{
	case 100: /* set BLINK on */		CurScr->SetChrStyle(CurScr->GetChrStyle()|GP_FNT_BLINK,CurScr->dwOldCommandMask);		break;
	case 101: /* set BLINK off */		CurScr->SetChrStyle(CurScr->GetChrStyle()&(0xFFFFFFFF^GP_FNT_BLINK),CurScr->dwOldCommandMask);		break;
	case 102: /* bold on   */			CurScr->SetChrStyle(CurScr->GetChrStyle()|GP_FNT_BOLD,CurScr->dwOldCommandMask);	break;
	case 103: /* bold off */			CurScr->SetChrStyle(CurScr->GetChrStyle()&(0xFFFFFFFF^GP_FNT_BOLD),CurScr->dwOldCommandMask); break;
	case 104: /* underline on */		CurScr->SetChrStyle(CurScr->GetChrStyle()|GP_FNT_UNDERLINE,CurScr->dwOldCommandMask);	break;
	case 105: /* underline off */		CurScr->SetChrStyle(CurScr->GetChrStyle()&(0xFFFFFFFF^GP_FNT_UNDERLINE),CurScr->dwOldCommandMask);		break;
	case 106: /* half intensyty */
		{
			DWORD clrIndex=CurScr->GetChrColorIndex();
			if (!(clrIndex&0x8))
			{
				CurScr->SetChrColorIndex(clrIndex|0x8,CurScr->dwOldCommandMask);
				HalfIntensity=true;
			}
		}
		break;
	case 107: /* full intensyty */
		{
			DWORD clrIndex=CurScr->GetChrColorIndex();
			if ((clrIndex&0x8))
			{
				CurScr->SetChrColorIndex(clrIndex^0x8,CurScr->dwOldCommandMask);
				HalfIntensity=false;
			}
		}
		break;

	case 110:  CurScr->SetBkgColorIndex(7,CurScr->dwOldCommandMask);		break; // BACKGROUND - WHITE
	case 111:  CurScr->SetBkgColorIndex(2,CurScr->dwOldCommandMask);		break; // BACKGROUND - BROWN
	case 112:  CurScr->SetBkgColorIndex(3,CurScr->dwOldCommandMask);		break; // BACKGROUND - MAGENTA
	case 113:  CurScr->SetBkgColorIndex(1,CurScr->dwOldCommandMask);		break; // BACKGROUND - RED
	case 114:  CurScr->SetBkgColorIndex(5,CurScr->dwOldCommandMask);		break; // BACKGROUND - CYAN
	case 115:  CurScr->SetBkgColorIndex(4,CurScr->dwOldCommandMask);		break; // BACKGROUND - GREEN
	case 116:  CurScr->SetBkgColorIndex(6,CurScr->dwOldCommandMask);		break; // BACKGROUND - BLUE
	case 117:  CurScr->SetBkgColorIndex(0,CurScr->dwOldCommandMask);		break; // BACKGROUND - BLACK
	case 118:  CurScr->SetReverseVideo(TRUE,CurScr->dwOldCommandMask);	break; // REVERSE COLOR
	case 119:// HOME
		if (m_CaptureFile) fputs("",m_CaptureFile);
		m_DlgSeparateView.AppendStringToOutput("");
		CurScr->SetCursorPosition(0,0);
		break;  
	case 120:  CurScr->SetChrColorIndex(HalfIntensity?15:7,CurScr->dwOldCommandMask); break; // FOREGROUND - WHITE
	case 121:  CurScr->SetChrColorIndex(HalfIntensity?10:2,CurScr->dwOldCommandMask); break; // FOREGROUND - BROWN
	case 122:  CurScr->SetChrColorIndex(HalfIntensity?11:3,CurScr->dwOldCommandMask); break; // FOREGROUND - MAGENTA
	case 123:  CurScr->SetChrColorIndex(HalfIntensity?9 :1,CurScr->dwOldCommandMask); break; // FOREGROUND - RED
	case 124:  CurScr->SetChrColorIndex(HalfIntensity?13:5,CurScr->dwOldCommandMask); break; // FOREGROUND - CYAN
	case 125:  CurScr->SetChrColorIndex(HalfIntensity?12:4,CurScr->dwOldCommandMask); break; // FOREGROUND - GREEN
	case 126:  CurScr->SetChrColorIndex(HalfIntensity?14:6,CurScr->dwOldCommandMask); break; // FOREGROUND - BLUE
	case 127:  CurScr->SetChrColorIndex(HalfIntensity?8 :0,CurScr->dwOldCommandMask); break; // FOREGROUND - BLACK0
	case 128:  CurScr->SetChrStyle(CurScr->GetChrStyle()|GP_FNT_OPAQUE,CurScr->dwOldCommandMask);	break;	/* Opaque font off */
	case 129:  CurScr->SetChrStyle(CurScr->GetChrStyle()&(0xFFFFFFFF^GP_FNT_OPAQUE),CurScr->dwOldCommandMask);	break;/* Opaque font on */
	case 130:  CurScr->SetChrStyle(CurScr->GetChrStyle()|GP_FNT_ITALIC,CurScr->dwOldCommandMask);	break;/* GP_FNT_ITALIC font on */
	case 131:  CurScr->SetChrStyle(CurScr->GetChrStyle()&(0xFFFFFFFF^GP_FNT_ITALIC),CurScr->dwOldCommandMask);	break;/* GP_FNT_ITALIC font off */
	case 132:  /* cbt BACK TAB */
		CurScr->DoTab(0x0001);
		break;
	case 133:  /* SCROLL SCREEN UP */
		{
			Point px=CurScr->GetCursorPosition();
			CurScr->ScrollUp();
			CurScr->SetCursorPosition(px);
		}
		break;
	case 134:  /* SCROLL SCREEN DOWN */
		{
			Point px=CurScr->GetCursorPosition();
			CurScr->ScrollDown();
			CurScr->SetCursorPosition(px);
		}
		break;
	case 135:  /* DELETE CHAR dch1 */
			CurScr->DelChar(CurScr->GetCursorPosition());		break;
	case 136:  /* DELETE LINE dl1 */
		if (m_CaptureFile) fputs("",m_CaptureFile);
		m_DlgSeparateView.AppendStringToOutput(InputBuffer2);
		CurScr->DelLine(CurScr->GetCursorPosition().Y);
		break;
	case 137:  /* INSERT CHAR ich1 */
		if (m_CaptureFile) fputc(' ',m_CaptureFile);
		CurScr->InsertChar(CurScr->GetCursorPosition());
		m_DlgSeparateView.AppendStringToOutput(InputBuffer2);
		break;
	case 138:  /* INSERT LINE il1 */
		CurScr->InsertLine(CurScr->GetCursorPosition().Y);
		break;
	case 139: // Set BACKGROUND - Default
		CurScr->SetBkgColorIndex(GPC.DefBkgColorInd,CurScr->dwOldCommandMask);
		break; 
	case 140: // Set FOREGROUND - Default
		CurScr->SetChrColorIndex(GPC.DefFrgColorInd,CurScr->dwOldCommandMask);
		break; 
	case 141: // Set BACKGROUND color index
		{
			int clrMap[]={0,1,4,2,6,3,5,7,8,9,12,10,14,11,13,15,};
			m_TermCap.TranslateFoundEsc();
			int clrIndex=m_TermCap.m_Vars.Pos_X;
			CurScr->SetBkgColorIndex(clrMap[clrIndex&0x000F],CurScr->dwOldCommandMask);
		}
		break; 
	case 142: // Set FOREGROUND color index
		{
			int clrMap[]={0,1,4,2,6,3,5,7,8,9,12,10,14,11,13,15,};
			m_TermCap.TranslateFoundEsc();
			int clrIndex=m_TermCap.m_Vars.Pos_X;
			if (HalfIntensity) clrIndex|=0x0008;
			CurScr->SetChrColorIndex(clrMap[clrIndex&0x000F],CurScr->dwOldCommandMask);
		}
		break; 
	case 143: // DELETE # CHARS dch DC
		{
			m_TermCap.TranslateFoundEsc();
			CurScr->DelChar((UINT)m_TermCap.m_Vars.Pos_Y);
		}
		break; 
	case 144: // DELETE # LINES dl DL
		{
			m_TermCap.TranslateFoundEsc();
			CurScr->DelLine((UINT)m_TermCap.m_Vars.Pos_Y);
		}
		break; 
	case 145: // INSERT # CHARS ich IC
		{
			m_TermCap.TranslateFoundEsc();
			CurScr->InsertChar((UINT)m_TermCap.m_Vars.Pos_Y);
		}
		break; 
	case 146: // INSERT # LINES il AL
		{
			m_TermCap.TranslateFoundEsc();
			CurScr->InsertLine((UINT)m_TermCap.m_Vars.Pos_Y);
		}
		break; 
	case 147:  // SCROLL WND REGION UP sf
		{
			m_TermCap.TranslateFoundEsc();
			CurScr->ScrollRange(1,1);
		}
		break;
	case 148:  // SCROLL WND REGION DOWN sr
		{
			m_TermCap.TranslateFoundEsc();
			CurScr->ScrollRange(1,0);
		}
		break;
	case 149:  // SCROLL WND REGION UP nTimes SF 
		{
			m_TermCap.TranslateFoundEsc();
			CurScr->ScrollRange(m_TermCap.m_Vars.Pos_X,1);
		}
		break;
	case 150:  // SCROLL WND REGION DOWN nTimes SR
		{
			m_TermCap.TranslateFoundEsc();
			CurScr->ScrollRange(m_TermCap.m_Vars.Pos_Y,1);
		}
		break;

	case 151:  // SET SCROLL REGION cs
		{
			m_TermCap.TranslateFoundEsc();
			CurScr->SetScrollRange(m_TermCap.m_Vars.Pos_X,m_TermCap.m_Vars.Pos_Y);
		}
		break;
	case 152:  // Reverse video off
		CurScr->SetReverseVideo(FALSE,CurScr->dwOldCommandMask);
		break;
	case 153:  // Set TABSTOP position
		CurScr->SetTABStopPos(0x1);
		break;
	case 154:  // ResSet all TABSTOP positions
		CurScr->SetTABStopPos(0x4);
		break;
	case 155:  // Next TABSTOP positions
		CurScr->DoTab(0);
		break;
	case 156:  // Off something 
		//switch(iLastCommand)
		//{
		//case :
		//	break;
		//}
		break;
	case 157:  // Insert mode Off
		CurScr->SetInsertMode(FALSE);
		break;

	case 158:  // Don't Send Mouse X & Y on button press and release
		dwXMouseMode&=(0xFFFFFFFF^GP_XMOUSE_VT200);
		break;
	case 159:  // Don't Use Hilite Mouse Tracking
		dwXMouseMode&=(0xFFFFFFFF^GP_XMOUSE_VT200_HIGHLIGHT);
		break;
	case 160:  // Send Mouse X & Y on button press and release
		dwXMouseMode|=GP_XMOUSE_VT200;
		break;
	case 161:  // Use Hilite Mouse Tracking
		dwXMouseMode|=GP_XMOUSE_VT200_HIGHLIGHT;
		break;
	case 162:  // Don't Send Mouse X & Y on button press
		dwXMouseMode&=(0xFFFFFFFF^GP_XMOUSE_X10);
		break;
	case 163:  // Send Mouse X & Y on button press
		dwXMouseMode|=GP_XMOUSE_X10;
		break;

	case 164:  // DEC Restore  DEC Private Mode Values
		break;
	case 165:  // DEC Save DEC Private Mode Values
		break;

	case 166:  // Enable alternate charset
		break;
	case 167:  // Insert mode ON (im)
		CurScr->SetInsertMode(TRUE);
		break;

	case 168:  // (te) End program that uses cursor motion
	case 169:  // (ti) Begin program that uses cursor motion
		dwXMouseMode&=(0xFFFFFFFF^GP_XMOUSE_MASK_DEC);
		break;

	case 170:  // Don't Use Hilite Mouse Tracking
		dwXMouseMode&=(0xFFFFFFFF^GP_XMOUSE_BTN_EVENT);
		break;
	case 171:  // Send Mouse X & Y on button press and release
		dwXMouseMode|=GP_XMOUSE_BTN_EVENT;
		break;
	case 172:  // Don't Use Hilite Mouse Tracking
		dwXMouseMode&=(0xFFFFFFFF^GP_XMOUSE_ANY_EVENT);
		break;
	case 173:  // Send Mouse X & Y on button press and release
		dwXMouseMode|=GP_XMOUSE_ANY_EVENT;
		break;


	case 180:/* GP_TERM GP.FileDeleteDir 000180 0 027 0 064 0 240 0 152*/
	case 181:/* GP_TERM GP.FileCopyDir 000180 0 027 0 064 0 240 0 153*/
		string_ptr=0; next_job=-CurrEscVariant;  job_flag=-1; break;


	case 190:/* GP_TERM GP.FileSystemSub 000190 0 027 0 064 0 240 0 162*/
	case 191:/* GP_TERM GP.FileSystemFn 000191 0 027 0 064 0 240 0 163*/
		string_ptr=0; next_job=-CurrEscVariant;  job_flag=-1; break;

	default: ret=-1; break;
	}
}
else
if (CurrEscVariant<1000)
{
	GPScreen *CurScr=GetDocument()->GetActiveScreen();
	switch(CurrEscVariant)
	{

	case 200:/* GP_TERM GP.ScreenSub 000200 0 027 0 228 0 096*/
	case 201:/* GP_TERM GP.ScreenFn 000201 0 027 0 228 0 097*/
	case 202:/* GP_TERM GP.WindowSub 000202 0 027 0 228 0 098*/
	case 203:/* GP_TERM GP.WindowFn 000203 0 027 0 228 0 099*/
		string_ptr=0; job_flag=-1; next_job=-CurrEscVariant; break;

	case 220:  CurScr->SetChrColorIndex(7,CurScr->dwOldCommandMask); break; // FOREGROUND - WHITE full
	case 221:  CurScr->SetChrColorIndex(2,CurScr->dwOldCommandMask); break; // FOREGROUND - BROWN full
	case 222:  CurScr->SetChrColorIndex(3,CurScr->dwOldCommandMask); break; // FOREGROUND - MAGENTA full
	case 223:  CurScr->SetChrColorIndex(1,CurScr->dwOldCommandMask); break; // FOREGROUND - RED full
	case 224:  CurScr->SetChrColorIndex(5,CurScr->dwOldCommandMask); break; // FOREGROUND - CYAN full
	case 225:  CurScr->SetChrColorIndex(4,CurScr->dwOldCommandMask); break; // FOREGROUND - GREEN full
	case 226:  CurScr->SetChrColorIndex(6,CurScr->dwOldCommandMask); break; // FOREGROUND - BLUE full
	case 227:  CurScr->SetChrColorIndex(0,CurScr->dwOldCommandMask); break; // FOREGROUND - BLACK0 full

	case 320:  CurScr->SetChrColorIndex(15,CurScr->dwOldCommandMask); break; // FOREGROUND - WHITE half
	case 321:  CurScr->SetChrColorIndex(10,CurScr->dwOldCommandMask); break; // FOREGROUND - BROWN half
	case 322:  CurScr->SetChrColorIndex(11,CurScr->dwOldCommandMask); break; // FOREGROUND - MAGENTA half
	case 323:  CurScr->SetChrColorIndex(9 ,CurScr->dwOldCommandMask); break; // FOREGROUND - RED half
	case 324:  CurScr->SetChrColorIndex(13,CurScr->dwOldCommandMask); break; // FOREGROUND - CYAN half
	case 325:  CurScr->SetChrColorIndex(12,CurScr->dwOldCommandMask); break; // FOREGROUND - GREEN half
	case 326:  CurScr->SetChrColorIndex(14,CurScr->dwOldCommandMask); break; // FOREGROUND - BLUE half
	case 327:  CurScr->SetChrColorIndex(8 ,CurScr->dwOldCommandMask); break; // FOREGROUND - BLACK0 half

	case 400:/* BLINK terminal REVERSE*/
		AfxGetMainWnd()->FlashWindow(TRUE);
		break;
	case 401:/* BLINK terminal RESTORE*/
		AfxGetMainWnd()->FlashWindow(FALSE);
		break;
	case 402:/* BLINK terminal icon*/
		#ifdef W_95
			AfxGetMainWnd()->FlashWindow(TRUE);
		#else
			#ifdef W_NT
				AfxGetMainWnd()->FlashWindow(TRUE);
			#else
			{
				FLASHWINFO fi={0};
				fi.cbSize=sizeof(fi);
				fi.hwnd=m_hWnd;
				fi.dwFlags=FLASHW_CAPTION|FLASHW_STOP;
				fi.uCount=1;
				fi.dwTimeout=1;
				::FlashWindowEx(&fi);
				::FlashWindowEx(&fi);
			}
			#endif
		#endif
		break;
	case 403:/* BLINK terminal ALL*/
		#ifdef W_95
			AfxGetMainWnd()->FlashWindow(TRUE);
		#else
			#ifdef W_NT
				AfxGetMainWnd()->FlashWindow(TRUE);
			#else
			{
				FLASHWINFO fi={0};
				fi.cbSize=sizeof(fi);
				fi.hwnd=m_hWnd;
				fi.dwFlags=FLASHW_ALL|FLASHW_STOP;
				fi.uCount=1;
				fi.dwTimeout=1;
				::FlashWindowEx(&fi);
				::FlashWindowEx(&fi);
			}
			#endif
		#endif
		break;
	case 404:/* Print screen*/
		{
			GPScreen *sc=GetDocument()->GetActiveScreen();
			if (sc) sc->ScrPrint("");
		}
		break;
	case 405:/* Printer on*/
		break;
	case 406:/* Printer off*/
		break;


	default: ret=-1;	break;
	}
}
else
if (CurrEscVariant<10000)
{
	GPScreen *CurScr=GetDocument()->GetActiveScreen();
	switch(CurrEscVariant)
	{
	case 1000: /* printon */
		if (GPC.EnableSlavePrintCHARVIEW) 
			CurScr->CharOutAW(m_TermCap.GetEscPool(),m_TermCap.GetEscPoolLen());
		if (GPC.EnableSlavePrint)
		{
			next_job=-1000; job_flag=-2;inputnbyte=1;curent_inputbyte=0;
		}
		else
			iSkip_0=iSkip_10=iSkip_13=0;
		break;
	case 1001:	/* printoff */	
			if (GPC.EnableSlavePrintCHARVIEW) 
			{
				CurScr->CharOutAW(m_TermCap.GetEscPool(),m_TermCap.GetEscPoolLen());
			}
		break; 
	case 1002: /* заблокировать клавиатуру */
	case 1004:  if (GPC.AjCheckState>120000) GPC.AjCheckState=0;
		SetKeybLock();
		break; // AJ.CHECK ON

	case 1003: /* разблокировать клавиатуру */
		GPC.AjCheckState=123456;
		iSkip_0=0;
		iSkip_10=0;
		iSkip_13=0;
		SetKeybLock();
		break;
	case 1005:
		if (GPC.AjCheckState>1)
			GPC.AjCheckState-=2;
		else
			GPC.AjCheckState=123456;
		iSkip_0=0;
		iSkip_10=0;
		iSkip_13=0;
		SetKeybLock();
		break; // AJ.CHECK OFF
	case 1100: /*включить BLOCK CONTROL и очистить буффер*/
		{
			GPC.BlockControl=TRUE;
			GPC.m_uCurrInputBlock=0;
			int i333;
			for(i333=0;i333<300;i333++)
				GPC.arrInputBlocks[i333]="GPCIO";
		}
		break;
	case 1101: /*выключить BLOCK CONTROL и очистить буффер*/
		{
			GPC.BlockControl=FALSE;
			GPC.m_uCurrInputBlock=0;
			int i333;
			for(i333=0;i333<300;i333++)
				GPC.arrInputBlocks[i333]="GPCIO";
		}
		break;
	case 1102: /*BlockingSendStr*/
	case 1103: /*запрос пропущенного*/
		string_ptr=0; next_job=-CurrEscVariant; job_flag=-1;	break;
	case 1104: /*Инициализация BLOCK CONTROL*/
		{
			GPC.m_uCurrInputBlock=0;
			int i333;
			for(i333=0;i333<300;i333++)
				GPC.arrInputBlocks[i333]="GPCIO";
		}
		break;
	case 1105: /*INPUT OUTPUT INFO FROM HOST 001105 0 027 0 005 0 035*/
	case 1106: /*LISTEN & CONNECT*/
		string_ptr=0; next_job=-CurrEscVariant; job_flag=-1;	break;
	case 2001: // GRAPH ON
		GPC.dwGraphFlag=1;	next_job=job_flag=0;	break;
	case 2002: // GRAPH OFF
		GPC.dwGraphFlag=0;	next_job=job_flag=0;	break;
	case 2003: // Enables Protect Mode
		CurScr->GPActiveWindow()->m_ProtectedModeFlag|=GP_FNT_FIXED;
	//	CurScr->GPActiveWindow()->SetStyleToChars(GP_FNT_FIXED,0, 0xFFFF);
		next_job=job_flag=0;	break;
	case 2004: // Disables Protect Mode
		CurScr->GPActiveWindow()->m_ProtectedModeFlag&=(0xFFFFFFFF^GP_FNT_FIXED);
	//	CurScr->GPActiveWindow()->SetStyleToChars(GP_FNT_FIXED,0, 0xFFFF);
	next_job=job_flag=0;	break;


	case 2015: // Enables Protect Mode for spaces and half intensity
		DoEscSeq(106);
	case 2005: // Enables protected-field
		CurScr->GPActiveWindow()->m_ProtectedFieldModeFlag|=GP_FNT_FIXED;
		next_job=job_flag=0;
		break;
	case 2016: // Disables protected-field and half intensity
		DoEscSeq(107);
	case 2006: // Disables protected-field
		CurScr->GPActiveWindow()->m_ProtectedFieldModeFlag&=(0xFFFFFFFF^GP_FNT_FIXED);
		next_job=job_flag=0;
		break;
	case 2007: // Download Function Keys ended 127
	case 2008: // Download Function Keys with slashes ended 127
		stopchar=127;
		next_job=-CurrEscVariant;job_flag=-5;string_ptr=0;	break;
	case 2009: // Download Function Keys ended 25
	case 2010: // Download Function Keys with slashes ended 25
		stopchar=25;
		next_job=-CurrEscVariant;job_flag=-5;string_ptr=0;	break;
	case 2011: // Enables Protect Mode for spaces
		CurScr->GPActiveWindow()->m_ProtectedModeFlag|=GP_FNT_FIXED;
		CurScr->GPActiveWindow()->SetStyleToChars(0,GP_FNT_FIXED, 0xFFFF);
		CurScr->GPActiveWindow()->SetStyleToChars(GP_FNT_FIXED,0, ' ');
		next_job=job_flag=0;
		break;


	default: ret=-1; 	break;
	}
}
else
if (CurrEscVariant<12000)
{
	GPScreen *CurScr=GetDocument()->GetActiveScreen();
	switch(CurrEscVariant)
	{
	case 10001: // message box
		m_TermCap.TranslateFoundEsc();
		string_ptr=0;
		next_job=-CurrEscVariant;
		job_flag=-1; 
		break;
	case 10002: // FOREGROUND RGB
		m_TermCap.TranslateFoundEsc();
		CurScr->SetChrColor(RGB(m_TermCap.m_Vars.R,m_TermCap.m_Vars.G,m_TermCap.m_Vars.B),0);
		break;
	case 10003: // BACKGROUND RGB
		m_TermCap.TranslateFoundEsc();
		CurScr->SetBkgColor(RGB(m_TermCap.m_Vars.R,m_TermCap.m_Vars.G,m_TermCap.m_Vars.B),0);
		break;
	case 10004:// SET FONT STYLE
		{
			m_TermCap.TranslateFoundEsc();
			DWORD tmpStyle=((m_TermCap.m_Vars.ClrRef-32)%32);
			DWORD dwNewStyle=0;
			if ((tmpStyle&0x1)==0x1) dwNewStyle|=GP_FNT_UNDERLINE;
			if ((tmpStyle&0x2)==0x2) dwNewStyle|=GP_FNT_STRIKE;
			if ((tmpStyle&0x4)==0x4) dwNewStyle|=GP_FNT_ITALIC;
			if ((tmpStyle&0x8)==0x8) dwNewStyle|=GP_FNT_BLINK;
			if ((tmpStyle&0x10)==0x10) dwNewStyle|=GP_FNT_OPAQUE;
			if ((tmpStyle&0x20)==0x20) dwNewStyle|=GP_FNT_BOLD;
			if ((tmpStyle&0x40)==0x40) dwNewStyle|=GP_FNT_CODE;
			if ((tmpStyle&0x80)==0x80) dwNewStyle|=GP_FNT_LIGHT;
			CurScr->SetChrStyle(dwNewStyle,0);
		}
		break;
	case 10005: /* Resize active*/ string_ptr=0; next_job=-CurrEscVariant; job_flag=-1; 	 break;
	case 10006:
		m_TermCap.TranslateFoundEsc();
		CurScr->TextHorLine(m_TermCap.m_Vars.Pos_X,m_TermCap.m_Vars.Pos_Y,m_TermCap.m_Vars.ClrRef,m_TermCap.m_Vars.Length);
		break;
	case 10007:
		m_TermCap.TranslateFoundEsc();
		CurScr->TextVerLine(m_TermCap.m_Vars.Pos_X,m_TermCap.m_Vars.Pos_Y,m_TermCap.m_Vars.ClrRef,m_TermCap.m_Vars.Length);
		break;
	case 10008: /*GP_TERM Text HorLine*/
	case 10009: /*GP_TERM Text VerLine*/
		string_ptr=0; next_job=-CurrEscVariant; job_flag=-1; 	 break;
	case 10010: /* select screen */
		m_TermCap.TranslateFoundEsc();
		SendChar(GetDocument()->SelectScreen(m_TermCap.m_Vars.IdScr));
		break;
	case 10011: /* select Window */
		m_TermCap.TranslateFoundEsc();
		SendChar(CurScr->SelectWindow(m_TermCap.m_Vars.IdWnd));
		break;
	case 10012: /* SetMainScreen */
		m_TermCap.TranslateFoundEsc();
		GetDocument()->SetMainScreen(m_TermCap.m_Vars.IdScr);
		break;
	case 10013: /* Move Window ForwardOne */
		m_TermCap.TranslateFoundEsc();
		CurScr->WndForwardOne(m_TermCap.m_Vars.IdWnd);
		break;
	case 10014: /* Move Window BackwardOne */
		m_TermCap.TranslateFoundEsc();
		CurScr->WndBackwardOne(m_TermCap.m_Vars.IdWnd);
		break;
	case 10015: /* Move Window Forward */
		m_TermCap.TranslateFoundEsc();
		CurScr->WndForward(m_TermCap.m_Vars.IdWnd);
		break;
	case 10016: /* Move Window Backward */
		m_TermCap.TranslateFoundEsc();
		CurScr->WndBackward(m_TermCap.m_Vars.IdWnd);
		break;
	case 10017: /* Move Window Backward */
		m_TermCap.TranslateFoundEsc();
		CurScr->WndSetState(m_TermCap.m_Vars.IdWnd,m_TermCap.m_Vars.typeUnit);
		break;
	case 10018: /* Set Title */
		string_ptr=0; next_job=-CurrEscVariant; job_flag=-1; 	 break;
	case 10019: /* GP.BUFFERKEY ON  */	 FlagBufferKeb=true; 		KeybBufferSize=0;	break;
	case 10020: /* GP.BUFFERKEY OFF  */	 FlagBufferKeb=false; 		KeybBufferSize=0;	break;
	case 10021:// message box
		m_TermCap.TranslateFoundEsc();
		string_ptr=0; next_job=-CurrEscVariant; job_flag=-1;
		break; 
	case 10022: //GP.CListMakerSub 010022 0 027 0 222 0 056
	case 10023: //GP.CListMakerFn  010023 0 027 0 222 0 057
		string_ptr=0; next_job=-CurrEscVariant; job_flag=-1; 	 break;
	case 10024: //GP.GetInsertMode(InsertMode) 010024 0 027 0 222 0 058
		{
			char str[100];
			sprintf(str,"%d",GPC.m_bInsertMode);
			SendStringToPICK(str);
		}
		break;
	case 10025: //GP.SetInsertMode(InsertMode) 010025 0 027 0 222 0 059
	case 10026: //GP.SetTermTips(Text) GP_TERM Set Tips 010026 0 027 0 222 0 060
	case 10027: //GP.OpenFileDialogEx(Text) 010026 0 027 0 222 0 061
	case 10028: //GP.OpenFileDialogEx(Text) 010026 0 027 0 222 0 062
		string_ptr=0; next_job=-CurrEscVariant; job_flag=-1; 	 break;
	case 10029: // GP_TERM Set Info line (Title) stop by ^G or \r of \n or ^@
		stopchar=7;
		next_job=-CurrEscVariant;job_flag=-5;string_ptr=0;	break;

	// object seq
	case 11000: /* CREATE OBJECT */
	case 11002: /* DELETE OBJECT */
	case 11003: /* PROPERTY OBJECT */ 	string_ptr=0; next_job=-CurrEscVariant; job_flag=-1;	break;


	case 11006: /* SET DEFAULT LOGFONT */ next_job=-CurrEscVariant; job_flag=-2;inputnbyte=13;curent_inputbyte=0; break;

	case 11009: /*DoObjSub*/
	case 11010: /*DoObjFun*/
	case 11011: /*ADD MESSAGE*/
	case 11012: /*DELETE MESSAGE*/
	case 11013: /*DELETE ALL MESSAGES*/
	case 11014: /*GP_TERM OBJECT SUBROUTINEEX 011014 0 027 0 223 0 047*/
	case 11015: /*GP_TERM OBJECT FUNCTIONEX 011015 0 027 0 223 0 048*/
	case 11016: /*GP_TERM OBJECT GP.ScrObjAddMMSG GP.DlgObjAddMMSG 0011016 0 027 0 223 0 049*/
	case 11017: /*GP_TERM OBJECT GP.ScrObjDelMMSG GP.DlgObjDelMMSG 0011016 0 027 0 223 0 050*/
	case 11018: /*GP_TERM OBJECT GP.ScrObjDelMMSG GP.DlgObjDelAllMMSG 0011016 0 027 0 223 0 051*/
		string_ptr=0; next_job=-CurrEscVariant; job_flag=-1;	break;

	default: ret=-1; break;
	}
}
else
if (CurrEscVariant<13000)
{
	GPScreen *CurScr=GetDocument()->GetActiveScreen();
	switch(CurrEscVariant)
	{
	case 12000: /* Create GPCommonDlg */
	case 12001: /* GP_TERM FindRepl Dialog create 012001 0 027 0 224 0 033*/
		string_ptr=0; next_job=-CurrEscVariant; job_flag=-1;break;
	case 12002: /* GP_TERM FindRepl Dialog close 012002 0 027 0 224 0 034*/
		next_job=-12002; job_flag=-12002;break;
	case 12003: /* GP_TERM FindRepl Dialog Fn 012003 0 027 0 224 0 035*/
	case 12004: /* GP_TERM FindRepl Dialog Sub 012004 0 027 0 224 0 036*/
		string_ptr=0; next_job=-CurrEscVariant; job_flag=-1;break;

	case 12005: /* GP_TERM PrintSetup Dialog 012005 0 027 0 224 0 037*/
		AfxGetMainWnd()->PostMessage( WM_COMMAND,ID_FILE_PRINT_SETUP,0);
		break;
	case 12006: /* GP_TERM User Login Dialog 012006 0 027 0 224 0 038 1 088 1 088 1 088 1 088 1 088*/
		{
			CDlgLogin mdlg;
			m_TermCap.TranslateFoundEsc();
			mdlg.m_DlgFlags=m_TermCap.m_Vars.Pos_X;
			mdlg.DoModal();
		}
		break;

	case 12100: /* Create GPObjDialog */
	case 12101: /* Delete GPObjDialog */
	case 12102: /* Create GPObjFrame */
	case 12103: /* Delete GPObjFrame */
		string_ptr=0; next_job=-CurrEscVariant; job_flag=-1;break;


	case 12201: /* Menu Create Popup */
	case 12202: /* Menu Append */
	case 12203: /* Menu Insert */
	case 12204: /* Menu ModifyByCom */
	case 12205: /* Menu ModifyByPos */
	case 12206: /* Menu RemoveByPos */
	case 12207: /* Menu RemoveByCom */
	case 12208: /* Menu EnableByPos */
	case 12209: /* Menu EnableByCom */
	case 12210: /* Menu CheckByPos */
	case 12211: /* Menu CheckByCom */
	case 12212: /* Menu CheckRadio */
	case 12213: /* Menu AppendSeparator */
	case 12214: /* Menu InsertSeparator */
	case 12215: /* Menu RemoveAllMenu */
	case 12216: /* Menu Create Track */
	case 12217: /* Menu Track Popup*/
	case 12218: /* Menu Enable Popup */

	case 12221: /* Menu Dialog Create Popup */
	case 12222: /* Menu Dialog Append */
	case 12223: /* Menu Dialog Insert */
	case 12224: /* Menu Dialog ModifyByCom */
	case 12225: /* Menu Dialog ModifyByPos */
	case 12226: /* Menu Dialog RemoveByPos */
	case 12227: /* Menu Dialog RemoveByCom */
	case 12228: /* Menu Dialog EnableByPos */
	case 12229: /* Menu Dialog EnableByCom */
	case 12230: /* Menu Dialog CheckByPos */
	case 12231: /* Menu Dialog CheckByCom */
	case 12232: /* Menu Dialog CheckRadio */
	case 12233: /* Menu Dialog AppendSeparator */
	case 12234: /* Menu Dialog InsertSeparator */
	case 12235: /* Menu Dialog RemoveAllMenu */
	case 12236: /* Menu Dialog Create Track */
	case 12237: /* Menu Dialog Track Popup*/
	case 12238: /* Menu Dialog Enable Popup */

	case 12239: /* User Menu Sub */
	case 12240: /* User Menu Fn */

	case 12301: /* AddHotKey IdScrDlg, IdObj, VK_ 012301 0 027 0 226 0 032 */
	case 12302: /* DelHotKey IdScrDlg, IdObj, VK_ 012302 0 027 0 226 0 033*/
	case 12303: /* DelAllHotKey IdScrDlg, IdObj   012303 0 027 0 226 0 034*/

		//GP_TERM OLE Convent (12500-12599)
	case 12501: /* GP_TERM  OLE TCL-Start/End 012501 0 027 0 227 0 032 */
	case 12502: /* GP_TERM  OLE SUB-Start 012502 0 027 0 227 0 033 */
	case 12503: /* GP_TERM  OLE SUB-Result 012503 0 027 0 227 0 034 */
	case 12504: /* GP_TERM  OLE OPENFILE DELETEITEM WRITEFILE SAVELIST ... Result  012504 0 027 0 227 0 035 */
	case 12505: /* GP_TERM  OLE READFILE READFILEEX GETACTIVELIST GETLIST ... Result 012505 0 027 0 227 0 036 */

		string_ptr=0; job_flag=-1; next_job=-CurrEscVariant; break;

	default: ret=-1;
	}
}
else
if (CurrEscVariant<13500)
{
	switch(CurrEscVariant)
	{
	case 13000: /* GP_TERM PAUSE EVENTS    032 013000 0 027 0 228 0 032*/
		GPC.StopEventsFlag=1; break;
	case 13001: /* GP_TERM RELEASE EVENTS  032 013001 0 027 0 228 0 033*/
		GPC.StopEventsFlag=0; break;

	case 13002: /* GP_TERM RUN EXELL MACRO   013002 0 027 0 228 0 034*/
		string_ptr=0; job_flag=-1; next_job=-CurrEscVariant; break;
	case 13003: /* GP_TERM GPTERM.MessageSound   013003 0 027 0 228 0 035*/
	case 13004: /* GP_TERM GPTERM.BeepSound   013004 0 027 0 228 0 036*/
	case 13005: /* GP_TERM GPTERM.PlaySound   013005 0 027 0 228 0 037*/
			string_ptr=0; job_flag=-1; next_job=-CurrEscVariant;
		break;
	case 13006: /* GP_TERM GPTERM.StopSound   013006 0 027 0 228 0 038*/
		PlaySound(NULL, NULL, SND_FILENAME);	break;
	case 13007: /* GP_TERM GPTERM.ShellExecuteEx   013007 0 027 0 228 0 039*/
	case 13008: /* GP_TERM GP.GetSysColor   013008 0 027 0 228 0 040*/
	case 13009: /* GP_TERM GP.SetSysColor   013009 0 027 0 228 0 041*/
	case 13010: /* GP_TERM GP.GetSysColorBrush   013010 0 027 0 228 0 042*/
	case 13011: /* GP_TERM GP.GetClipboardText   013011 0 027 0 228 0 043*/
	case 13012: /* GP_TERM GP.SetClipboardText   013012 0 027 0 228 0 044*/
		string_ptr=0; job_flag=-1; next_job=-CurrEscVariant; break;

	case 13013: /* GP_TERM GP.GetWindowsDir   013013 0 027 0 228 0 045*/
	case 13014: /* GP_TERM GP.GetSystemDir   013014 0 027 0 228 0 046*/
	case 13015: /* GP_TERM GP.GetSystemWindowsDir   013015 0 027 0 228 0 047*/
	case 13016: /* GP_TERM GP.GetSystemInfo   013016 0 027 0 228 0 048*/
		{
			char str[1000];*str=0;
			switch(CurrEscVariant)
			{
			case 13013:/* GP_TERM GP.GetWindowsDir*/
				GetWindowsDirectory(str,900);	break;
			case 13014:/* GP_TERM GP.GetSystemDir*/
				GetSystemDirectory(str,900);	break;
			case 13015:/* GP_TERM GP.GetSystemWindowsDir*/
				#ifdef W_95
				#else
					#ifdef W_NT
					#else
						#ifdef W_98
						#else
							GetSystemWindowsDirectory(str,900);
						#endif
					#endif
				#endif
				break;
			case 13016:/* GP_TERM GP.GetSystemInfo*/
				{
					SYSTEM_INFO m_SystemInfo={0};
					GetSystemInfo(&m_SystemInfo);
					char *prar[5]={"INTEL","MIPS","ALPHA","PPC","UNKNOWN",};
					WORD wprar[5]={PROCESSOR_ARCHITECTURE_INTEL,PROCESSOR_ARCHITECTURE_MIPS,PROCESSOR_ARCHITECTURE_ALPHA,PROCESSOR_ARCHITECTURE_PPC,PROCESSOR_ARCHITECTURE_UNKNOWN,};
					int i333;
					for(i333=0;i333<5 && m_SystemInfo.wProcessorArchitecture!=wprar[i333];i333++);
					if (i333>=5) i333=4;

					sprintf(str,"%s\x7F%X\x7F%X\x7F%X\x7F%X\x7F%X\x7F%X\x7F%X\x7F%X",
						prar[i333],
						m_SystemInfo.dwPageSize,
						(DWORD)m_SystemInfo.lpMinimumApplicationAddress,
						(DWORD)m_SystemInfo.lpMaximumApplicationAddress,
						m_SystemInfo.dwActiveProcessorMask,
						m_SystemInfo.dwNumberOfProcessors,
						m_SystemInfo.dwAllocationGranularity,
						m_SystemInfo.wProcessorArchitecture,
						m_SystemInfo.wProcessorRevision);
					break;
				}
				break;
			}
			strcat(str,"\r");
			m_Comm.GPSendBlock(AnsiToDos(str,0),(int)strlen(str));
		}
		 break;
	case 13017: /* GP_TERM GP.GetSysMetrics   013017 0 027 0 228 0 049*/
	case 13018: /* GP_TERM GP.LoadKeyboard    013018 0 027 0 228 0 050*/
	case 13019: /* GP_TERM GP.LoadPalette     013019 0 027 0 228 0 051*/
		string_ptr=0; job_flag=-1; next_job=-CurrEscVariant; break;
	case 13020: /* GP_TERM GP.GetVersionEx(VersionText)     13020 0 027 0 228 0 052*/
		{
			char str[1000];*str=0;
			OSVERSIONINFO osvi;
			osvi.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);

			GetVersionEx(&osvi);
			char *outpos=str;

			outpos+=sprintf(outpos,"%d\x7F%d\x7F%d\x7F",
				osvi.dwMajorVersion,
				osvi.dwMinorVersion,
				osvi.dwBuildNumber
				);

			switch(osvi.dwPlatformId)
			{
			case VER_PLATFORM_WIN32_WINDOWS:
				if (osvi.dwMajorVersion > 4 || osvi.dwMinorVersion ==90)
					outpos+=sprintf(outpos,"WMe\x7F");
				else
				if (osvi.dwMajorVersion > 4 || osvi.dwMinorVersion > 0)
					outpos+=sprintf(outpos,"W98\x7F");
				else
					outpos+=sprintf(outpos,"W95\x7F");
				break;
			case VER_PLATFORM_WIN32_NT:
				if ( osvi.dwMajorVersion < 4 )
					outpos+=sprintf(outpos,"NT3.51\x7F");
				else
				if ( osvi.dwMajorVersion == 4 )
					outpos+=sprintf(outpos,"NT3.51\x7F");
				else
					if (osvi.dwMinorVersion==0)
						outpos+=sprintf(outpos,"W2K\x7F");
					else
						outpos+=sprintf(outpos,"XP\x7F");
				break;
			default:	outpos+=sprintf(outpos,"UNKNOWN\x7F");
			}

			sprintf(outpos,"%s\r",osvi.szCSDVersion);
			m_Comm.GPSendBlock(AnsiToDos(str,0),(int)strlen(str));
		}
		break;
	case 13021: /* GP_TERM GP.DnsHostToCompName 013021 0 027 0 228 0 053 :DnsHost*/
	case 13022: /* GP_TERM GP.GetComputerName 013022 0 027 0 228 0 054 :ComputerNameFormat*/
	case 13023: /* GP_TERM GP.GetComputerObjectName 013023 0 027 0 228 0 055 :ObjectNameFormat*/
		string_ptr=0; job_flag=-1; next_job=-CurrEscVariant; break;
	case 13024: /* GP_TERM GP.GetCurrentHwProfile 013024 0 027 0 228 0 056*/
		{
			char *str=new char [10000];
			*str=0;
#if(_WIN32_WINNT >= 0x0700)
			HW_PROFILE_INFO pi;
			GetCurrentHwProfile(&pi);
			char *nm[5]={"DOCKED","UNDOCKED","USER_SUPPLIED","USER_DOCKEDPLIED","USER_UNDOCKED",};
			UINT  type[5]={DOCKINFO_DOCKED,DOCKINFO_UNDOCKED,DOCKINFO_USER_SUPPLIED,DOCKINFO_USER_DOCKEDPLIED,DOCKINFO_USER_UNDOCKED,};
			char *posout=str;
			int i;
			for(i=0;i<5;i++)
				if ((pi.dwDockInfo&type[i])==type[i])
					posout+=sprintf(posout,"%s|",nm[i]);

			sprintf(pos,"\x7F%s\x7F%s\r",pi.szHwProfileGuid,pi.szHwProfileName);
#else
			strcpy(str,"Old Windows\r");
#endif
			m_Comm.GPSendBlock(AnsiToDos(str,0),(int)strlen(str));
			delete[] str;
		}
		break;
	case 13025: /* GP_TERM GP.GetKeyboardType 013025 0 027 0 228 0 057*/
		{
			int Type=GetKeyboardType(0);
			int SubType=GetKeyboardType(1);
			int nFkey=GetKeyboardType(2);
			char str[1000];
			const char *nmType[]={"unknown","IBM PC/XT or compatible (83-key) keyboard","Olivetti \"ICO\" (102-key) keyboard","IBM PC/AT (84-key) or similar keyboard","IBM enhanced (101- or 102-key) keyboard","Nokia 1050 and similar keyboards","Nokia 9140 and similar keyboards ","Japanese keyboard",};
			const char *nmFkey[]={"unknown","10","12 (sometimes 18)","10","12","10","24","Hardware dependent and specified by the OEM",};
			if (Type<0 || Type>7) Type=0;
			if (nFkey<0 || nFkey>7) nFkey=0;
			sprintf(str,"%s\x7F%d\x7F%s\r",nmType[Type],SubType,nmFkey[nFkey]);
			m_Comm.GPSendBlock(AnsiToDos(str,0),(int)strlen(str));
		}
		break;
	case 13026: /* GP_TERM GP.GetUserName 013026 0 027 0 228 0 058 :uNameType*/
		string_ptr=0; job_flag=-1; next_job=-CurrEscVariant; break;
	case 13027: /* GP_TERM GP.IsProcFeaturePresent 013027 0 027 0 228 0 059*/
		{
			char str[1000];*str=0;

#if(_WIN32_WINNT >= 0x0700)
			char *pos=str;
			const char *nm[8]={
				"FLOATING_POINT_PRECISION_ERRATA|","FLOATING_POINT_EMULATED|","COMPARE_EXCHANGE_DOUBLE|",
				"MMX_INSTRUCTIONS_AVAILABLE|","XMMI_INSTRUCTIONS_AVAILABLE|","3DNOW_INSTRUCTIONS_AVAILABLE|",
				"RDTSC_INSTRUCTION_AVAILABLE|","PAE_ENABLED|",
			};
			UINT types[8]={
				PF_FLOATING_POINT_PRECISION_ERRATA,PF_FLOATING_POINT_EMULATED,PF_COMPARE_EXCHANGE_DOUBLE,
				PF_MMX_INSTRUCTIONS_AVAILABLE,PF_XMMI_INSTRUCTIONS_AVAILABLE,PF_3DNOW_INSTRUCTIONS_AVAILABLE,
				PF_RDTSC_INSTRUCTION_AVAILABLE,PF_PAE_ENABLED,
			};
			int i;
			for(i=0;i<8;i++)
			{
				if (IsProcessorFeaturePresent(types[i]))
					pos+=sprintf(pos,"%s",nm[i]);
			}
#else
			strcpy(str,"Old Windows");
#endif
			strcat(str,"\r");
			m_Comm.GPSendBlock(AnsiToDos(str,0),(int)strlen(str));
		}
		break;
	case 13028: /* GP_TERM GP.TranslateName 013028 0 027 0 228 0 060 :sNameType:",":dNameType:",":sName*/
	case 13029: /* GP_TERM GP.RegisterTerminal 013029 0 027 0 228 0 061 :sNameType:*/
	case 13030: /* GP_TERM GP.UnRegisterTerminal 013029 0 027 0 228 0 061 :sNameType:*/

	case 13031: /* GP_TERM GP.RegionCreate 013031 0 027 0 228 0 063 :Name*/
	case 13032: /* GP_TERM GP.RegionDelete 013032 0 027 0 228 0 064 :Name*/
		string_ptr=0; job_flag=-1; next_job=-CurrEscVariant; break;
	case 13033: /* GP_TERM GP.RegionDeleteAll 013033 0 027 0 228 0 065 */
		GPC.RegionArr.DeleteAll(); break;
	case 13034: /* GP_TERM GP.RegionSub 013034 0 027 0 228 0 066 :Name;SubSting*/
	case 13035: /* GP_TERM GP.RegionFn 013035 0 027 0 228 0 067 :Name,SubSting ->ret*/
	case 13036: /* GP_TERM GP.RegionFromDlgObj 013036 0 027 0 228 0 068 :Name;IdDlg,IdObj*/
	case 13037: /* GP_TERM GP.RegionFromScrObj 013037 0 027 0 228 0 069 :Name,iIdScr,iIdObj ->ret*/
		string_ptr=0; job_flag=-1; next_job=-CurrEscVariant; break;


	case 13041: /* GP_TERM GP.CursorCreate 013031 0 027 0 228 0 073 :Name*/
	case 13042: /* GP_TERM GP.CursorDelete 013032 0 027 0 228 0 074 :Name*/
		string_ptr=0; job_flag=-1; next_job=-CurrEscVariant; break;
	case 13043: /* GP_TERM GP.CursorDeleteAll 013033 0 027 0 228 0 075 */
		GPC.CursorArr.DeleteAll(); break;
	case 13044: /* GP_TERM GP.CursorSub 013034 0 027 0 228 0 076 :Name;SubSting*/
	case 13045: /* GP_TERM GP.CursorFn 013035 0 027 0 228 0 077 :Name,SubSting ->ret*/
	case 13046: /* GP_TERM GP.LockBeep 013046 0 027 0 228 0 078 */
	case 13047: /* GP_TERM GPTERM.Show(Show) 013047 0 027 0 228 0 079 */
	case 13048:/* GP_TERM GP.FileSystemSub 013048 0 027 0 228 0 080*/
	case 13049:/* GP_TERM GP.FileSystemFn 013049 0 027 0 228 0 081*/
		string_ptr=0; job_flag=-1; next_job=-CurrEscVariant; break;

	case 13060:/* GP_TERM GP.DCCreate 013060 0 027 0 228 0 092*/
	case 13061:/* GP_TERM GP.DCDelete 013061 0 027 0 228 0 093*/
	case 13062:/* GP_TERM GP.DCSub 013062 0 027 0 228 0 094*/
	case 13063:/* GP_TERM GP.DCFn 013063 0 027 0 228 0 095*/
		string_ptr=0; job_flag=-1; next_job=-CurrEscVariant; break;

	default: ret=-1; break;
	}
}
else
if (CurrEscVariant<14500)
{
	GPScreen *CurScr=GetDocument()->GetActiveScreen();
	switch(CurrEscVariant)
	{

	///
	///  #######################################################################
	/// GP_TERM IMAGELIST COMMANDS (13500-13549)
	///  #######################################################################
	///
	case 13500: // 0 027 0 229 0 032  GP.IListCreate(Name,CX,CY,nIitial,Style)
	case 13501: // 0 027 0 229 0 033  GP.IListLoad(Name)
	case 13502: // 0 027 0 229 0 034  GP.IListDelete(Name)
	case 13503: // 0 027 0 229 0 035  GP.IListGetCount(Name, RetCount)
	case 13504: // 0 027 0 229 0 036  GP.IListSetBkColor(Name, R, G, B)
	case 13505: // 0 027 0 229 0 037  GP.IListGetBkColor(Name, RetRGB)
	case 13506: // 0 027 0 229 0 038  GP.IListGetImageInfo(Name, nImage, ImageInfo)
	case 13507: // 0 027 0 229 0 039  GP.IListSetImageCount(Name,ImageCount)
	case 13508: // 0 027 0 229 0 040  GP.IListAdd(Name,SName, nImage)
	case 13509: // 0 027 0 229 0 041  GP.IListAddFromFile(Name,FName)
	case 13510: // 0 027 0 229 0 042  GP.IListAddFromILFile(Name,FName,nImage)
	case 13511: // 0 027 0 229 0 043  GP.IListRemove(Name,nImage)
	case 13512: // 0 027 0 229 0 044  GP.IListReplace(Name,nImage,SName,SnImage)
	case 13513: // 0 027 0 229 0 045  GP.IListReplaceFromFile(Name,nImage,FName)
	case 13514: // 0 027 0 229 0 046  GP.IListReplaceFromILF(Name,nImage,FName,SnImage)
	case 13515: // 0 027 0 229 0 047  GP.IListSetOverlay(Name,nImage,nOverlay)
	case 13516: // 0 027 0 229 0 048  GP.IListCopy(Name,nSImage,nDImage)
	case 13517: // 0 027 0 229 0 049  GP.IListSwap(Name,nSImage,nDImage)
	case 13518: // 0 027 0 229 0 050  GP.IListSwapEx(SName,nSImage,DName,nDImage)
	case 13519: // 0 027 0 229 0 051  GP.IListCopyEx(SName,nSImage,DName,nDImage)
	case 13520: // 0 027 0 229 0 052  GP.IListSetDragCursor(Name,nImage,PX,PY)
	case 13521: // 0 027 0 229 0 053  GP.IListWrite(Name)
	case 13522: // 0 027 0 229 0 054  GP.IListBeginDrag(Name,nImage,PX,PY)
	case 13523: // 0 027 0 229 0 055  GP.IListDragEnter(IdDlg,IdObj,Name,PX,PY)
	case 13524: // 0 027 0 229 0 056  GP.IListEndDrag(Name)
	case 13525: // 0 027 0 229 0 057  GP.IListDragLeave(IdDlg,IdObj,Name)
	case 13526: // 0 027 0 229 0 058  GP.IListDragMove(Name,PX,PY)
	case 13527: // 0 027 0 229 0 059  GP.IListDragShowNolock(Name,fShow)
	case 13528: // 0 027 0 229 0 060  GP.IListSub(Name,SubStr)
	case 13529: // 0 027 0 229 0 061  GP.IListFn(Name,FnStr,Ret)
		string_ptr=0; job_flag=-1; next_job=-CurrEscVariant; break;

	//***  #######################################################################
	//*** GP_TERM ODBCDataBase COMMANDS (13600-13699)
	//***  #######################################################################
	case 13600: //  0 027 0 230 0 032 GP_TERM  SUB GP.ODBCDatabaseOpen(DBVar,DBString,DBOption)
	case 13601: //  0 027 0 230 0 033 GP_TERM  SUB GP.ODBCDatabaseClose(DBVar)
	case 13602: //  0 027 0 230 0 034 GP_TERM  SUB GP.ODBCDatabaseFn(DBVar,FnStr,RetStr)
	case 13603: //  0 027 0 230 0 035 GP_TERM  SUB GP.ODBCDatabaseSub(DBVar,SubStr)
	case 13650: //  0 027 0 230 0 082 GP_TERM  SUB GP.ODBCRecordsetOpen(DBVar,RSVar,DBString,DBOption)
	case 13651: //  0 027 0 230 0 083 GP_TERM  SUB GP.ODBCRecordsetClose(RSVar)
	case 13652: //  0 027 0 230 0 084 GP_TERM  SUB GP.ODBCRecordsetFn(RSVar,FnStr,RetStr)
	case 13653: //  0 027 0 230 0 085 GP_TERM  SUB GP.ODBCRecordsetSub(RSVar,SubStr)
		string_ptr=0; job_flag=-1; next_job=-CurrEscVariant; break;

	//***  #######################################################################
	//*** GP_TERM DAODataBase COMMANDS (13700-13799)
	//***  #######################################################################
	case 13700: //  0 027 0 231 0 032 GP.DAOWorkspaceOpen(WSVar,szName,szUserName,szPassword)
	case 13701: //  0 027 0 231 0 033 GP.DAOWorkspaceClose(WSVar)
	case 13702: //  0 027 0 231 0 034 GP.DAOWorkspaceFn(WSVar,FnStr,RetStr)
	case 13703: //  0 027 0 231 0 035 GP.DAOWorkspaceSub(WSVar,SubStr)
	case 13750: //  0 027 0 231 0 036 GP.DAOEngineSub(SubStr)
	case 13751: //  0 027 0 231 0 037 GP.DAOEngineFn(SubStr,RetStr)
	case 13710: //  0 027 0 231 0 042 GP.DAODatabaseOpen(WSVar,DBVar,szName,bExclusive,bReadOnly,szConnect)
	case 13711: //  0 027 0 231 0 043 GP.DAODatabaseCreate(WSVar,DBVar,szName,szLocale,Options)
	case 13712: //  0 027 0 231 0 044 GP.DAODatabaseClose(DBVar)
	case 13713: //  0 027 0 231 0 045 GP.DAODatabaseFn(DBVar,FnStr,RetStr)
	case 13714: //  0 027 0 231 0 046 GP.DAODatabaseSub(DBVar,SubStr)
	case 13720: //  0 027 0 231 0 052 GP.DAORecordsetOpen(DBVar,RSVar,RSType,RSOption,RSSQL)
	case 13721: //  0 027 0 231 0 053 GP.DAORecordsetClose(RSVar)
	case 13722: //  0 027 0 231 0 054 GP.DAORecordsetFn(RSVar,FnStr,RetStr)
	case 13723: //  0 027 0 231 0 055 GP.DAORecordsetSub(RSVar,SubStr)
	case 13730: //  0 027 0 231 0 062 GP.DAOTableDefOpen(DBVar,TDVar,TDName)
	case 13731: //  0 027 0 231 0 063 GP.DAOTableDefCreate(DBVar,TDVar,TDName,TDSrcTable,TDAttr,TDConnect)
	case 13732: //  0 027 0 231 0 064 GP.DAOTableDefClose(TDVar)
	case 13733: //  0 027 0 231 0 065 GP.DAOTableDefFn(TDVar,FnStr,RetStr)
	case 13734: //  0 027 0 231 0 066 GP.DAOTableDefSub(TDVar,SubStr)
	case 13740: //  0 027 0 231 0 072 GP.DAOQueryDefOpen(DBVar,QDVar,TDName)
	case 13741: //  0 027 0 231 0 073 GP.DAOQueryDefCreate(DBVar,QDVar,QDName,QDSQL)
	case 13742: //  0 027 0 231 0 074 GP.DAOQueryDefClose(QDVar)
	case 13743: //  0 027 0 231 0 075 GP.DAOQueryDefFn(QDVar,FnStr,RetStr)
	case 13744: //  0 027 0 231 0 076 GP.DAOQueryDefSub(QDVar,SubStr)
		string_ptr=0; job_flag=-1; next_job=-CurrEscVariant; break;

	//***  #######################################################################
	//*** GP_TERM SPR COMMANDS (13900-13999)
	//***  #######################################################################
	case 13900: // 0 027 0 232 0 032 GPTERM.SprCreate(SprName,nFields)
	case 13901: // 0 027 0 232 0 033 GPTERM.SprDelete(SprName)
	case 13903: // 0 027 0 232 0 034 GPTERM.SprSub(SprName,SubStr)
	case 13904: // 0 027 0 232 0 035 GPTERM.SprFn(SprName,FnStr,RetStr)
		string_ptr=0; job_flag=-1; next_job=-CurrEscVariant; break;
	case 13905: // 0 027 0 232 0 035 GPTERM.SprGetActiveList(RetList)
		{
			CString str;
			GPC.m_SprArray.GetArrayDescr(str);
			str+="\r";
			AnsiToDos(str,str,0);
			m_Comm.GPSendBlock(str,str.GetLength());
		}
		break;

	//***  #######################################################################
	//*** GP_TERM IOFILE COMMANDS (13920-13929)
	//***  #######################################################################
	case 13920: // 0 027 0 232 0 052 GPTERM.IOFILECreate(IOFILEName)
	case 13921: // 0 027 0 232 0 053 GPTERM.IOFILEDelete(IOFILEName)
	case 13923: // 0 027 0 232 0 054 GPTERM.IOFILESub(IOFILEName,SubStr)
	case 13924: // 0 027 0 232 0 055 GPTERM.IOFILEFn(IOFILEName,FnStr,RetStr)
		string_ptr=0; job_flag=-1; next_job=-CurrEscVariant; break;

	//***  #######################################################################
	//*** GP_TERM REGISTRY COMMANDS (13930-13939)
	//***  #######################################################################
	case 13930: // 0 027 0 232 0 062 GPTERM.RegistryHandleCreate(HandleName)
	case 13931: // 0 027 0 232 0 063 GPTERM.RegistryHandleDelete(HandleName)
	case 13933: // 0 027 0 232 0 064 GPTERM.RegistrySub(HandleName,SubStr)
	case 13934: // 0 027 0 232 0 065 GPTERM.RegistryFn(HandleName,FnStr,RetStr)
		string_ptr=0; job_flag=-1; next_job=-CurrEscVariant; break;

	//***  #######################################################################
	//*** GP_TERM SEPARATE VIEW COMMANDS (13940-13949)
	//***  #######################################################################
	case 13940: // 0 027 0 232 0 072 SViewSub(Method,Params)
	case 13941: // 0 027 0 232 0 073 SViewFn(Method,Params,RetVal)
		string_ptr=0; job_flag=-1; next_job=-CurrEscVariant; break;

	//***  #######################################################################
	//*** GP_TERM EXCEL COMMANDS (14000-14500)
	//***  #######################################################################
	case 14000: // 014000 0 027 0 233 0 032 GP.ExcelApplicationClose
	case 14001: // 014001 0 027 0 233 0 033 GP.ExcelApplicationCreate
	case 14002: // 014002 0 027 0 233 0 034 GP.ExcelApplicationFn(EVar,FnStr,RetStr)
	case 14003: // 014003 0 027 0 233 0 035 GP.ExcelApplicationSub(EVar,SubStr)
	case 14004: // 014004 0 027 0 233 0 036 GP.ExcelGPRangeClose(EVar)
	case 14005: // 014005 0 027 0 233 0 037 GP.ExcelGPRangeCreate(CrStr,RetStr)
	case 14006: // 014006 0 027 0 233 0 038 GP.ExcelGPRangeFn(EVar,FnStr,RetStr)
	case 14007: // 014007 0 027 0 233 0 039 GP.ExcelGPRangeSub(EVar,SubStr)
	case 14008: // 014008 0 027 0 233 0 040 GP.ExcelRangeClose(EVar)
	case 14009: // 014009 0 027 0 233 0 041 GP.ExcelRangeCreate(CrStr,RetStr)
	case 14010: // 014010 0 027 0 233 0 042 GP.ExcelRangeFn(EVar,FnStr,RetStr)
	case 14011: // 014011 0 027 0 233 0 043 GP.ExcelRangeSub(EVar,SubStr)
	case 14012: // 014012 0 027 0 233 0 044 GP.ExcelWorkbookClose(EVar)
	case 14013: // 014013 0 027 0 233 0 045 GP.ExcelWorkbookCreate(CrStr,RetStr)
	case 14014: // 014014 0 027 0 233 0 046 GP.ExcelWorkbookFn(EVar,FnStr,RetStr)
	case 14015: // 014015 0 027 0 233 0 047 GP.ExcelWorkbookSub(EVar,SubStr)
	case 14016: // 014016 0 027 0 233 0 048 GP.ExcelWorksheetClose(EVar)
	case 14017: // 014017 0 027 0 233 0 049 GP.ExcelWorksheetCreate(CrStr,RetStr)
	case 14018: // 014018 0 027 0 233 0 050 GP.ExcelWorksheetFn(EVar,FnStr,RetStr)
	case 14019: // 014019 0 027 0 233 0 051 GP.ExcelWorksheetSub(EVar,SubStr)
	case 14020: // 014020 0 027 0 233 0 052 GP.ExcelFn(FnStr,RetStr)
	case 14021: // 014021 0 027 0 233 0 053 GP.ExcelSub(SubStr)
	case 14022: // 014022 0 027 0 233 0 054 GP.ExcelWorkbookOpen(CrStr,RetStr)
	string_ptr=0; job_flag=-1; next_job=-CurrEscVariant; break;


	default: ret=-1;
	}
}
else
if (CurrEscVariant<17000)
	switch(CurrEscVariant)
	{
		//CCOMServer m_COMServer;
	case 15000: /* GP.COMDoSub */
	case 15001: /* GP.COMDoFn */
	case 15002: /* GP.COMLoadDll */
	case 15003: /* GP.COMLoadExe */
	case 15004: /* GP.COMUnload */
		string_ptr=0; job_flag=-1; next_job=-CurrEscVariant; break;
		//DllServer m_DllServer;
	case 15100: /* GP.DllDoSub */
	case 15101: /* GP.DllDoFn */
	case 15102: /* GP.DllLoad */
	case 15103: /* GP.DllUnload */
		string_ptr=0; job_flag=-1; next_job=-CurrEscVariant; break;

	default: ret=-1;
	}
else
if (CurrEscVariant<1000000)
{
	GPScreen *CurScr=GetDocument()->GetActiveScreen();
	switch(CurrEscVariant)
	{
	case 111111: /* all attr off */
		CurScr->SetReverseVideo(FALSE,CurScr->dwOldCommandMask);
		DoEscSeq(101);
		DoEscSeq(103);
		DoEscSeq(105);
		DoEscSeq(129);
		DoEscSeq(131);
		break;
	case 111112: /* all clr off */
		CurScr->SetBkgColorIndex(GPC.DefBkgColorInd,CurScr->dwOldCommandMask);
		CurScr->SetChrColorIndex(GPC.DefFrgColorInd,CurScr->dwOldCommandMask);
		break;
	case 111113: /* all attr & clr off */
		DoEscSeq(111111);
		DoEscSeq(111112);
		break;
	case 111114: /* all attr off & FullIntensity */
		DoEscSeq(111111);
		DoEscSeq(107);
		break;
	case 111115: /* all attr & clr off  & FullIntensity*/
		DoEscSeq(111114);
		DoEscSeq(111112);
		break;
	case 111211: /* multi m */
		{
			unsigned char tmps[128];
			m_TermCap.TranslateFoundEsc();
			m_TermCap.ClearEscPool();
			int param1=m_TermCap.m_Vars.Pos_Y;
			int param2=m_TermCap.m_Vars.Pos_X;
			esc_pointer=sprintf((char *)tmps,"%c[%dm",27,param1);
			
			int tmpescvar=m_TermCap.AddArrayToEscPool(tmps,(int)strlen((char *)tmps));
			if (tmpescvar>=0)
			{
				PTERMCAPESCITEM pEsc=m_TermCap.GetFoundEsc();
				if (pEsc) DoEscSeq(pEsc->dwCommand); 
			}
			m_TermCap.ClearEscPool();
			esc_pointer=sprintf((char *)tmps,"%c[%dm",27,param2);
			tmpescvar=m_TermCap.AddArrayToEscPool(tmps,(int)strlen((char *)tmps));
			if (tmpescvar>=0)
			{
				PTERMCAPESCITEM pEsc=m_TermCap.GetFoundEsc();
				if (pEsc) DoEscSeq(pEsc->dwCommand); 
			}
			m_TermCap.ClearEscPool();
		}
		break;
	case 111212: /* multi m inverse*/
		{
			unsigned char tmps[128];
			m_TermCap.TranslateFoundEsc();
			m_TermCap.ClearEscPool();
			int param1=m_TermCap.m_Vars.Pos_Y;
			int param2=m_TermCap.m_Vars.Pos_X;
			esc_pointer=sprintf((char *)tmps,"%c[%dm",27,param1<2?1-param1:param1);
			
			int tmpescvar=m_TermCap.AddArrayToEscPool(tmps,(int)strlen((char *)tmps));
			if (tmpescvar>=0)
			{
				PTERMCAPESCITEM pEsc=m_TermCap.GetFoundEsc();
				if (pEsc) DoEscSeq(pEsc->dwCommand); 
			}
			m_TermCap.ClearEscPool();
			esc_pointer=sprintf((char *)tmps,"%c[%dm",27,param2<2?1-param2:param2);
			tmpescvar=m_TermCap.AddArrayToEscPool(tmps,(int)strlen((char *)tmps));
			if (tmpescvar>=0)
			{
				PTERMCAPESCITEM pEsc=m_TermCap.GetFoundEsc();
				if (pEsc) DoEscSeq(pEsc->dwCommand); 
			}
			m_TermCap.ClearEscPool();
		}
		break;
	case 111300: /*NOP*/
		break;

	default: ret=-1;
	}
}
	return ret;
}

BOOL CGP_TermView::LoadScrRgn(char *name, Point topleft)
{
// Загрузить из файла прямоугольный регион
// LoadScrRgn(char *name, CPoint topleft)
	return GetDocument()->GetActiveScreen()->LoadScrRgn(name,topleft);
}

