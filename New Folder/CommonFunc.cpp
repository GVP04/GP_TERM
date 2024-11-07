// GP_term.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "GP_term.h"
#include "GPColorDlg.h"
#include <direct.h>
#include <math.h>

///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////

struct AFX_CHECK_DATA
{
public:
	int m_nCheck;
	BOOL m_bEnabled;
	DWORD m_dwUserData;

	AFX_CHECK_DATA()
	{
		m_nCheck = 0;
		m_bEnabled = TRUE;
		m_dwUserData = 0;
	};
};


int GetInputCodePage() {
	HKL inputLocale = ::GetKeyboardLayout(0);
	LANGID inputLang = LOWORD(inputLocale);
	char sCodePage[10];
	int res = ::GetLocaleInfo(MAKELCID(inputLang, SORT_DEFAULT),
	  LOCALE_IDEFAULTANSICODEPAGE, sCodePage, sizeof(sCodePage));
	if (!res)
		return 0;
	return atoi(sCodePage);
}

void ClearItemsData(CCheckListBox *lb)
{
	int nItem=lb->GetCount();
	if (nItem!=LB_ERR)
	{
		int i;
		for(i=0;i<nItem;i++)
		{
			AFX_CHECK_DATA* pState = (AFX_CHECK_DATA*)lb->GetItemData(i);
			if (pState)
				delete[] pState;
			lb->SetItemData(i,NULL);
		}
	}

}

const char *GetFileName(const char *fname)
{
	const char *pos=fname+(int)strlen(fname);
	while(pos!=fname && *pos!='\\') pos--;
	if (*pos=='\\') pos++;
 return pos;
}


char * AnsiToDos(char *str, int flag)
{
	char *pos=str;
	if ((pos--))
		while(*(++pos)!=0)
			if (GPC.m_USEMBCONV && (GPC.MBConv3PCSrw(pos, pos) || GPC.chWideAnsiDos[*pos]))
			{
				if (GPC.chWideAnsiDos[*pos])
				{
					*pos=GPC.chWideAnsiDos[*pos];
					if (GPC.m_USEMBCONV2 && *(++pos) && GPC.chWideAnsiDos2[*pos])
						*pos=GPC.chWideAnsiDos2[*pos];
					else if (!*pos) pos--;
				}
				else pos++;
			}
			else
			if (*pos==7) *pos=253;
				else
				if (*pos==127) *pos=254;
					else
					if (*pos>0 && *pos<6 && flag!=0)
					{
						if (*pos==1) *pos=253;
							else
							if (*pos==2) *pos=252;
								else
								if (*pos==3) *pos=251;
									else
									if (*pos==4) *pos=250;
										else
										if (*pos==5) *pos=249;
					}
					else
						if (flag>1 && *pos==13) *pos=254;
						else
							if (flag>1 && *pos==10) *pos=254;
							else
								*pos=GPC.chAnsiDos[*pos];

	return str;
}

char * AnsiToDosMB(char *str, int flag)
{
	char *pos=str;
	if ((pos--))
		while(*(++pos))
			if (GPC.m_USEMBCONV && (GPC.MBConv3PCSrw(pos, pos) || GPC.chWideAnsiDos[*pos]))
			{
				if (GPC.chWideAnsiDos[*pos])
				{
					*pos=GPC.chWideAnsiDos[*pos];
					if (GPC.m_USEMBCONV2 && *(++pos) && GPC.chWideAnsiDos2[*pos])
						*pos=GPC.chWideAnsiDos2[*pos];
					else if (!*pos) pos--;
				}
				else pos++;
			}
			else
				if (*pos==7) *pos=253;
					else
					if (*pos==127) *pos=254;
						else
						if (*pos>0 && *pos<6 && flag!=0)
						{
							if (*pos==1) *pos=253;
								else
								if (*pos==2) *pos=252;
									else
									if (*pos==3) *pos=251;
										else
										if (*pos==4) *pos=250;
											else
											if (*pos==5) *pos=249;
						}
						else
							if (flag>1 && *pos==13) *pos=254;
							else
								if (flag>1 && *pos==10) *pos=254;
								else
									*pos=GPC.chAnsiDos[*pos];

	return str;
}

void AnsiToDos(const char *tmp, CString &str, int flag)
{
	str=tmp;
	int len=str.GetLength();
	int i;
	char tmppos[20];
	for(i=0;i<len;i++)
	{
		*tmppos=0;
		if (GPC.m_USEMBCONV && (GPC.MBConv3PCSrw(tmp+i, tmppos) || GPC.chWideAnsiDos[tmp[i]]))
		{
			if (*tmppos)
			{
				str.SetAt(i,tmppos[0]);
				str.SetAt(i+1,tmppos[1]);
			}
			else
			{
				tmppos[0]=tmp[i];
				tmppos[1]=tmp[i+1];
			}

			if (GPC.chWideAnsiDos[tmppos[0]])
			{
				str.SetAt(i,GPC.chWideAnsiDos[tmppos[0]]);
				if (GPC.m_USEMBCONV2 && GPC.chWideAnsiDos2[tmppos[1]])
					tmppos[1]=GPC.chWideAnsiDos2[tmppos[1]];
				if (++i<len) str.SetAt(i,tmppos[1]);
			}
			else 
				i++;
		}
		else
		if (tmp[i]==7) str.SetAt(i,253);
		else
			if (tmp[i]==127) str.SetAt(i,254);
			else
				if (tmp[i]>0 && tmp[i]<6 && flag!=0)
				{
					if (tmp[i]==1) str.SetAt(i,253);
					else
						if (tmp[i]==2) str.SetAt(i,252);
						else
							if (tmp[i]==3) str.SetAt(i,251);
							else
								if (tmp[i]==4) str.SetAt(i,250);
								else
									if (tmp[i]==5) str.SetAt(i,249);
				}
				else
					if (flag>1 && tmp[i]==13) str.SetAt(i,254);
					else
						if (flag>1 && tmp[i]==10) str.SetAt(i,254);
						else
							if (GPC.chAnsiDos[tmp[i]]!=tmp[i]) str.SetAt(i,GPC.chAnsiDos[tmp[i]]);
	}
}

void AnsiToDosMB(const char *tmp, CString &str, int flag)
{
	str=tmp;
	int len=str.GetLength();
	int i;
	char tmppos[20];
	for(i=0;i<len;i++)
	{
		*tmppos=0;
		if (GPC.m_USEMBCONV && (GPC.MBConv3PCSrw(tmp+i, tmppos) || GPC.chWideAnsiDos[tmp[i]]))
		{
			if (*tmppos)
			{
				str.SetAt(i,tmppos[0]);
				str.SetAt(i+1,tmppos[1]);
			}
			else
			{
				tmppos[0]=tmp[i];
				tmppos[1]=tmp[i+1];
			}

			if (GPC.chWideAnsiDos[tmppos[0]])
			{
				str.SetAt(i,GPC.chWideAnsiDos[tmppos[0]]);
				if (GPC.m_USEMBCONV2 && GPC.chWideAnsiDos2[tmppos[1]])
					tmppos[1]=GPC.chWideAnsiDos2[tmppos[1]];
				if (++i<len) str.SetAt(i,tmppos[1]);
			}
			else 
				i++;
		}
		else
		if (tmp[i]==7) str.SetAt(i,253);
		else
			if (tmp[i]==127) str.SetAt(i,254);
			else
				if (tmp[i]>0 && tmp[i]<6 && flag!=0)
				{
					if (tmp[i]==1) str.SetAt(i,253);
					else
						if (tmp[i]==2) str.SetAt(i,252);
						else
							if (tmp[i]==3) str.SetAt(i,251);
							else
								if (tmp[i]==4) str.SetAt(i,250);
								else
									if (tmp[i]==5) str.SetAt(i,249);
				}
				else
					if (flag>1 && tmp[i]==13) str.SetAt(i,254);
					else
						if (flag>1 && tmp[i]==10) str.SetAt(i,254);
						else
							if (GPC.chAnsiDos[tmp[i]]!=tmp[i]) str.SetAt(i,GPC.chAnsiDos[tmp[i]]);
	}
}

BYTE * AnsiToDos(BYTE *Arr, int flag, UINT Len)
{
	BYTE *ret=Arr;
	if (Arr && Len)
		while(Len--)
		{
			int tmpret=0;
			if (Len && GPC.m_USEMBCONV && ((tmpret=GPC.MBConv3PCSrw((const char *)Arr, (char *)Arr)) || GPC.chWideAnsiDos[*Arr]))
			{
				if (GPC.chWideAnsiDos[*Arr])
				{
					*Arr=GPC.chWideAnsiDos[*Arr];
					if (GPC.m_USEMBCONV2 && GPC.chWideAnsiDos2[*(++Arr)])
					{
						Len--;
						*Arr=GPC.chWideAnsiDos2[*Arr];
					}
					else if (tmpret) {Len--;Arr++;}
				}
				else Arr++;
			}
			else
			if (*Arr==7) *Arr=253;
				else
				if (*Arr==127) *Arr=254;
					else
					if (*Arr>0 && *Arr<6 && flag!=0)
					{
						if (*Arr==1) *Arr=253;
							else
							if (*Arr==2) *Arr=252;
								else
								if (*Arr==3) *Arr=251;
									else
									if (*Arr==4) *Arr=250;
										else
										if (*Arr==5) *Arr=249;
					}
					else
					if (flag>1 && *Arr==13) *Arr=254;
						else
						if (flag>1 && *Arr==10) *Arr=254;
							else
								if (GPC.chAnsiDos[*Arr]!=*Arr) *Arr=GPC.chAnsiDos[*Arr];
			Arr++;
		}

	return ret;
}


char * DosToAnsi(char *str)
{
	char *pos=str;
	if (pos)
		while(*pos!=0)
		{
			char c=*pos;
			if (GPC.m_USEMBCONV && GPC.chWideDosAnsi[c])
			{
				char *tmppos=pos;
				*pos=GPC.chWideDosAnsi[c];
				if (GPC.m_USEMBCONV2 && *(++pos) && GPC.chWideDosAnsi2[*pos])
					*pos=GPC.chWideDosAnsi2[*pos];
				else if (!*(pos)) pos--;

				if (GPC.MBConv3SrwPC(tmppos, tmppos) && tmppos==pos) pos++;
			}
			else
			if (c==GPC.DelimiterSrc1) *pos=GPC.DelimiterIn1;
			else
			if (c==GPC.DelimiterSrc2) *pos=GPC.DelimiterIn2;
			else
			if (c==GPC.DelimiterSrc3) *pos=GPC.DelimiterIn3;
			else
			if (c==GPC.DelimiterSrc4) *pos=GPC.DelimiterIn4;
			else
			if (c==GPC.DelimiterSrc5) 
				*pos=GPC.DelimiterIn5;
			else
			if (c==GPC.DelimiterSrc6) *pos=GPC.DelimiterIn6;
			else	*pos=GPC.chDosAnsi[*pos];
			pos++;
		}
	return str;
}

void DosToAnsi(const char *tmp, CString &str)
{
	str=tmp;
	int len=str.GetLength();
	int i;
	for(i=0;i<len;i++)
	{
		char c=tmp[i];
		if (GPC.m_USEMBCONV && GPC.chWideDosAnsi[c])
		{
				char tmppos[4];
				tmppos[0]=GPC.chWideDosAnsi[c];
				tmppos[1]=tmp[i+1];

				if (GPC.m_USEMBCONV2 && GPC.chWideDosAnsi2[tmppos[1]])
				{
					tmppos[1]=GPC.chWideDosAnsi2[tmppos[1]];
					GPC.MBConv3SrwPC(tmppos, tmppos);
					str.SetAt(i,tmppos[0]);
					if (++i<len) str.SetAt(i,tmppos[1]);
				}
				else
				{
					if (GPC.MBConv3SrwPC(tmppos, tmppos))
					{
						str.SetAt(i,tmppos[0]);
						if (++i<len) str.SetAt(i,tmppos[1]);
					}
					else
						str.SetAt(i,tmppos[0]);
				}
		}
		else
		if (c==GPC.DelimiterSrc1) str.SetAt(i,GPC.DelimiterIn1);
		else
		if (c==GPC.DelimiterSrc2) str.SetAt(i,GPC.DelimiterIn2);
		else
		if (c==GPC.DelimiterSrc3) str.SetAt(i,GPC.DelimiterIn3);
		else
		if (c==GPC.DelimiterSrc4) str.SetAt(i,GPC.DelimiterIn4);
		else
		if (c==GPC.DelimiterSrc5) str.SetAt(i,GPC.DelimiterIn5);
		else
		if (c==GPC.DelimiterSrc6) str.SetAt(i,GPC.DelimiterIn6);
		else
		if (GPC.chDosAnsi[tmp[i]]!=tmp[i]) str.SetAt(i,GPC.chDosAnsi[tmp[i]]);
	}
}

char * DosToAnsiMB(char *str)
{
	char *pos=str;
	if (pos)
		while(*pos)
		{
			char c=*pos;
			if (GPC.m_USEMBCONV && GPC.chWideDosAnsi[c%256])
			{
				char *tmppos=pos;
				*pos=GPC.chWideDosAnsi[c];
				if (GPC.m_USEMBCONV2 && *(++pos) && GPC.chWideDosAnsi2[*pos])
					*pos=GPC.chWideDosAnsi2[*pos];
				else if (!*(pos)) pos--;

				if (GPC.MBConv3SrwPC(tmppos, tmppos) && tmppos==pos) pos++;
			}
			else
			if (c==GPC.DelimiterSrc1) *pos=GPC.DelimiterIn1;
			else
			if (c==GPC.DelimiterSrc2) *pos=GPC.DelimiterIn2;
			else
			if (c==GPC.DelimiterSrc3) *pos=GPC.DelimiterIn3;
			else
			if (c==GPC.DelimiterSrc4) *pos=GPC.DelimiterIn4;
			else
			if (c==GPC.DelimiterSrc5) 
				*pos=GPC.DelimiterIn5;
			else
			if (c==GPC.DelimiterSrc6) *pos=GPC.DelimiterIn6;
			else	*pos=GPC.chDosAnsi[*pos];
			pos++;
		}
	return str;
}

void DosToAnsiMB(const char *tmp, CString &str)
{
	str=tmp;
	int len=str.GetLength();
	int i;
	for(i=0;i<len;i++)
	{
		char c=tmp[i];
		if (GPC.m_USEMBCONV && GPC.chWideDosAnsi[c])
		{
				char tmppos[4];
				tmppos[0]=GPC.chWideDosAnsi[c];
				tmppos[1]=tmp[i+1];

				if (GPC.m_USEMBCONV2 && GPC.chWideDosAnsi2[tmppos[1]])
				{
					tmppos[1]=GPC.chWideDosAnsi2[tmppos[1]];
					GPC.MBConv3SrwPC(tmppos, tmppos);
					str.SetAt(i,tmppos[0]);
					if (++i<len) str.SetAt(i,tmppos[1]);
				}
				else
				{
					if (GPC.MBConv3SrwPC(tmppos, tmppos))
					{
						str.SetAt(i,tmppos[0]);
						if (++i<len) str.SetAt(i,tmppos[1]);
					}
					else
						str.SetAt(i,tmppos[0]);
				}
		}
		else
		if (c==GPC.DelimiterSrc1) str.SetAt(i,GPC.DelimiterIn1);
		else
		if (c==GPC.DelimiterSrc2) str.SetAt(i,GPC.DelimiterIn2);
		else
		if (c==GPC.DelimiterSrc3) str.SetAt(i,GPC.DelimiterIn3);
		else
		if (c==GPC.DelimiterSrc4) str.SetAt(i,GPC.DelimiterIn4);
		else
		if (c==GPC.DelimiterSrc5) str.SetAt(i,GPC.DelimiterIn5);
		else
		if (c==GPC.DelimiterSrc6) str.SetAt(i,GPC.DelimiterIn6);
		else
		if (GPC.chDosAnsi[tmp[i]]!=tmp[i]) str.SetAt(i,GPC.chDosAnsi[tmp[i]]);
	}
}

BYTE * DosToAnsi(BYTE *Arr, UINT Len)
{
	BYTE *ret=Arr;

	if (Arr && Len)
		while(Len--)
		{
			char c=*Arr;
			if (Len && GPC.m_USEMBCONV && GPC.chWideDosAnsi[c])
			{
				BYTE *tmppos=Arr;
				*Arr=GPC.chWideDosAnsi[c];
				if (GPC.m_USEMBCONV2)
				{
					Arr[1]=GPC.chWideDosAnsi2[Arr[1]];
					GPC.MBConv3SrwPC((const char *)Arr, (char *)Arr);
					Len--;
					Arr++;
				}
				else
				{
					if (GPC.MBConv3SrwPC((const char *)Arr, (char *)Arr))
					{
						Len--;
						Arr++;
					}
				}
			}
			else
			if (c==GPC.DelimiterSrc1) *Arr=GPC.DelimiterIn1;
			else
			if (c==GPC.DelimiterSrc2) *Arr=GPC.DelimiterIn2;
			else
			if (c==GPC.DelimiterSrc3) *Arr=GPC.DelimiterIn3;
			else
			if (c==GPC.DelimiterSrc4) *Arr=GPC.DelimiterIn4;
			else
			if (c==GPC.DelimiterSrc5) *Arr=GPC.DelimiterIn5;
			else
			if (c==GPC.DelimiterSrc6) *Arr=GPC.DelimiterIn6;
			else *Arr=GPC.chDosAnsi[*Arr];
			Arr++;
		}
	return ret;
}


UINT ShadowColor(UINT & incolor)
{
	incolor/=2;
	incolor&=RGB(127,127,127);
	incolor^=RGB(7,7,7);
	return incolor;
}

void OptimColor(CDC *dc, UINT & iFRG, UINT & iBKG)
{
    UINT newRGBf;
    UINT newRGBb;
	iBKG=newRGBb=dc->GetNearestColor(iBKG);
	iFRG=newRGBf=dc->GetNearestColor(iFRG);

	while(1)
	{
		Sleep(10);
		if (dc->GetNearestColor(newRGBb)!=iBKG) newRGBb=iBKG=dc->GetNearestColor(newRGBb);
		if (dc->GetNearestColor(newRGBf)!=iFRG) newRGBf=iFRG=dc->GetNearestColor(newRGBf);
		UINT SSb=(newRGBb%256+(newRGBb/256)%256+(newRGBb/65536)%256)/3;
		UINT SSf=(newRGBf%256+(newRGBf/256)%256+(newRGBf/65536)%256)/3;
		if (SSb<SSf)
		{
			UINT tmp=SSb;	SSb=SSf;	SSf=tmp;
			tmp	=newRGBb;	newRGBb=newRGBf;	newRGBf	=tmp;
		}

		if (SSb-SSf>100 && dc->GetNearestColor(newRGBb)!=dc->GetNearestColor(newRGBf)) break;
		SSb+=15;
		SSf-=15;
		if (SSb>255) SSb=255;
		if (SSf>255) SSf=0;
		newRGBb=SSb+SSb*256+SSb*65536;
		newRGBf=SSf+SSf*256+SSf*65536;
	}

	iBKG=dc->GetNearestColor(newRGBb);
	iFRG=dc->GetNearestColor(newRGBf);
}


void FileTexToBin(char *names, char *named)
{
	FILE *tms,*tmd;
	if ((tms=fopen(names,"rb")))
	{
		if ((tmd=fopen(named,"wb")))
		{
			int c,oldt=0;
			while((c=fgetc(tms))!=EOF)
				switch(c)
				{
				case 241: oldt=-32; continue;
				case 242: oldt=0;  continue;
				case 243: oldt=32; continue;
				default: fputc(c-oldt,tmd); break;
				}
			fclose(tmd);
		}
		fclose(tms);
	}

}

void FileBinToText(char *names, char *named)
{
	FILE *tms,*tmd;
	if ((tms=fopen(names,"rb")))
	{
		if ((tmd=fopen(named,"wb")))
		{
			int c,oldt=0;
			while((c=fgetc(tms))!=EOF)
			{
				if (c<32)
				{
					if (oldt<=0)  fputc(243,tmd);
					oldt=32;
				}
				else
				if ((c>125 && c<=127) ||  (c>240 && c<=255))
				{
					if (oldt>=0)  fputc(241,tmd);
					oldt=-32;
				}
				else
				if (oldt!=0)
				{
					fputc(242,tmd);
					oldt=0;
				}

				fputc(c+oldt,tmd);

			}
			fclose(tmd);
		}
		fclose(tms);
	}

}


char * ReplaceSpec(char *pos)
{
	const char *hexchars="0123456789ABCDEFabcdef";
	const DWORD hexValues[]={0,1,2,3,4,5,6,7,8,9,0xA,0xB,0xC,0xD,0xE,0xF,0xa,0xb,0xc,0xd,0xe,0xf,};
	char *pos1=pos;
	char *pos2=pos;
	while (*pos2!=0)
		if (*pos2!='\\') *(pos1++)=*(pos2++);
		else
		{
			switch(pos2[1])
			{
			case '\\':	*(pos1++)=*pos2;	break;
			case 'n':	*(pos1++)='\n';		break;
			case 't':	*(pos1++)='\t';		break;
			case 'r':	*(pos1++)='\r';		break;
			case 'x':
				{
					pos2++;
					DWORD dwValue=0;
					const char *postmp=strchr(hexchars,pos2[1]);
					if (postmp)
					{
						pos2++;
						dwValue=hexValues[postmp-hexchars];
						postmp=strchr(hexchars,pos2[1]);
						if ((postmp=strchr(hexchars,pos2[1])))
						{
							pos2++;
							dwValue=dwValue*0x10+hexValues[postmp-hexchars];
						}
					}
					*(pos1++)=(char)dwValue;
				}
				break;
			default: break;
			}
			pos2++;
			if (*pos2!=0) pos2++;
		}

	*pos1=*pos2;
	return pos;
}

char * ReplaceChar(char *Str, char cOld, char cNew)
{
	char *pos=Str;
	if (pos)
		while(*pos!=0)
			if (*(pos++)==cOld)
			{
				*(--pos)=cNew;
				pos++;
			}

	return Str;
}

char * ReplaceChar(char *Str, char cOld, char cNew, char cStop)
{
	char *pos=Str;
	if (pos)
		while(*pos!=0 && *pos!=cStop)
			if (*(pos++)==cOld)
			{
				*(--pos)=cNew;
				pos++;
			}

	return Str;
}

BOOL TranslLOGFONT2(LOGFONT & lftmp, const char *pos)
{
	strcpy(lftmp.lfFaceName, GPC.m_GUISet.UseDefault?"MS Sans Serif":GPC.m_GUISet.FontName);
	lftmp.lfWeight=GPC.m_GUISet.UseDefault?400:GPC.m_GUISet.Weight;
	lftmp.lfItalic=GPC.m_GUISet.UseDefault?0:GPC.m_GUISet.Italic;
	#ifdef RUS
		lftmp.lfCharSet  =GPC.m_GUISet.UseDefault?RUSSIAN_CHARSET:GPC.m_GUISet.CharSet;
	#else
		lftmp.lfCharSet  =GPC.m_GUISet.UseDefault?DEFAULT_CHARSET:GPC.m_GUISet.CharSet;
	#endif
	return TranslLOGFONT(lftmp,pos);
}


BOOL TranslLOGFONT(LOGFONT & lftmp, const char *pos)
{
	int i;
	char *lfpos;
	char *lfprop[14]={"HEIGHT ","WIDTH ","ESCAPEMENT ","ORIENTATION ","WEIGHT ","ITALIC ","UNDERLINE ","STRIKE ","CHARSET ","OUTPREC ","CLIPPREC ","QUALITY ","PITCH ","NAME ",};
	char *tmpbuff=new char [(int)strlen(pos)+100];
	strcpy(tmpbuff,pos);
	_strupr(tmpbuff);
	char *tmppos=strstr(tmpbuff,"FONT=");
	if (!tmppos) tmppos=strstr(tmpbuff,"FONT2=");
	if (tmppos) strcpy(tmpbuff,tmppos);
	tmppos=strchr(tmpbuff,';');
	if (tmppos) *tmppos=0;

	for(i=0;i<14;i++)
		if ((lfpos=strstr(tmpbuff,lfprop[i])))
		{
			char *possp=strchr(lfpos,' ');
			int ilfval;
			if (possp)
			{
				while(*possp==' ') possp++;

				switch(i)
				{
				case 0: /*lfHeight*/		m_LastScanf=sscanf(possp,"%d",&ilfval);				lftmp.lfHeight=ilfval;		break;
				case 1: /*lfWidth*/			m_LastScanf=sscanf(possp,"%d",&ilfval);				lftmp.lfWidth=ilfval;		break;
				case 2: /*lfEscapement*/	m_LastScanf=sscanf(possp,"%d",&ilfval);ilfval%=3600;lftmp.lfEscapement=ilfval;	break;
				case 3: /*lfOrientation*/	m_LastScanf=sscanf(possp,"%d",&ilfval);ilfval%=3600;lftmp.lfOrientation=ilfval;break;
				case 4: /*lfWeight*/		m_LastScanf=sscanf(possp,"%d",&ilfval);ilfval%=1000;lftmp.lfWeight=ilfval;		break;
				case 5: /*lfItalic*/		m_LastScanf=sscanf(possp,"%d",&ilfval);ilfval%=256;	lftmp.lfItalic=(char)ilfval;	break;
				case 6: /*lfUnderline*/		m_LastScanf=sscanf(possp,"%d",&ilfval);ilfval%=256;	lftmp.lfUnderline=(char)ilfval;	break;
				case 7: /*lfStrikeOut*/		m_LastScanf=sscanf(possp,"%d",&ilfval);ilfval%=256;	lftmp.lfStrikeOut=(char)ilfval;	break;
				case 8: /*lfCharSet*/
					{
						for(i=0;i<18 && strncmp(possp,clfCharSet[i],(int)strlen(clfCharSet[i]))!=0;i++);
						if (i<18) lftmp.lfCharSet=(unsigned char)ulfCharSet[i];
						break;
					}
				case 9: /*lfOutPrecision*/
					{
						for(i=0;i<9 && strncmp(possp,clfOutPrecision[i],(int)strlen(clfOutPrecision[i]))!=0;i++);
						if (i<9) lftmp.lfOutPrecision=(unsigned char)ulfOutPrecision[i];
						break;
					}
				case 10:/*lfClipPrecision*/
					{
						char *tmpend=strchr(possp,',');
						if (tmpend) *tmpend=0;
						lftmp.lfClipPrecision=0;
						for(i=0;i<7;i++)
							if (strncmp(possp,clfClipPrecision[i],(int)strlen(clfClipPrecision[i]))==0)
								lftmp.lfClipPrecision|=ulfClipPrecision[i];

						if (tmpend) *tmpend=',';
						break;
					}
				case 11:/*lfQuality*/
					{
						for(i=0;i<6 && strncmp(possp,clfQuality[i],(int)strlen(clfQuality[i]))!=0;i++);
						if (i<6) lftmp.lfQuality=(unsigned char)ulfQuality[i];
						break;
					}
				case 12:/*lfPitchAndFamily*/
					{
						for(i=0;i<18 && strncmp(possp,clfPitchAndFamily[i],(int)strlen(clfPitchAndFamily[i]))!=0;i++);
						if (i<18) lftmp.lfPitchAndFamily=(unsigned char)ulfPitchAndFamily[i];
						break;
					}
				case 13:/*lfFaceName*/
					{
						char *tmpend;
						strncpy(lftmp.lfFaceName,possp-tmpbuff+pos,32);
						lftmp.lfFaceName[31]=0;
						if ((tmpend=strchr(lftmp.lfFaceName,','))) *tmpend=0;
						break;
					}
				}

			}
		}
	delete[] tmpbuff;
	return TRUE;
}


BOOL TranslLOGFONTtoString(char *pos, LOGFONT & lftmp)
{
	char *lfprop[14]={"HEIGHT ","WIDTH ","ESCAPEMENT ","ORIENTATION ","WEIGHT ","ITALIC ","UNDERLINE ","STRIKE ","CHARSET ","OUTPREC ","CLIPPREC ","QUALITY ","PITCH ","NAME ",};

	if (pos)
	{
		int ilfCharSet,ilfOutPrecision,ilfClipPrecision,ilfQuality,ilfPitchAndFamily;
		for(ilfCharSet=0;ilfCharSet<17 && lftmp.lfCharSet!=ulfCharSet[ilfCharSet];ilfCharSet++);
		for(ilfOutPrecision=0;ilfOutPrecision<8 && lftmp.lfOutPrecision!=ulfOutPrecision[ilfOutPrecision];ilfOutPrecision++);
		for(ilfClipPrecision=0;ilfClipPrecision<6 && lftmp.lfClipPrecision!=ulfClipPrecision[ilfClipPrecision];ilfClipPrecision++);
		for(ilfQuality=0;ilfQuality<2 && lftmp.lfQuality!=ulfQuality[ilfQuality];ilfQuality++);
		for(ilfPitchAndFamily=0;ilfPitchAndFamily<17 && lftmp.lfPitchAndFamily!=ulfPitchAndFamily[ilfPitchAndFamily];ilfPitchAndFamily++);

		sprintf(pos,"lfHeight\x7%d\x7FlfWidth\x7%d\x7FlfEscapement\x7%d\x7FlfOrientation\x7%d\x7FlfWeight\x7%d\x7FlfItalic\x7%d\x7FlfUnderline\x7%d\x7FlfStrikeOut\x7%d\x7FlfCharSet\x7%s\x7FlfOutPrecision\x7%s\x7FlfClipPrecision\x7%s\x7FlfQuality\x7%s\x7FlfPitchAndFamily\x7%s\x7FlfFaceName\x7%s",
			lftmp.lfHeight,
			lftmp.lfWidth,
			lftmp.lfEscapement,
			lftmp.lfOrientation,
			lftmp.lfWeight,
			lftmp.lfItalic,
			lftmp.lfUnderline,
			lftmp.lfStrikeOut,
			clfCharSet[ilfCharSet],
			clfOutPrecision[ilfOutPrecision],
			clfClipPrecision[ilfClipPrecision],
			clfQuality[ilfQuality],
			clfPitchAndFamily[ilfPitchAndFamily],
			lftmp.lfFaceName);
	}
	return TRUE;
}



BOOL TranslTextAlignment(UINT & tmpAlign, char *pos)
{
	strcat(pos,"|");
	tmpAlign=0;

	char *calign[19]={"_BKGFILL|","_RECTCLIP|","_RECTFILL|","_LEFT|","_RIGHT|","_CENTER|","_TOP|","_BOTTOM|","_VCENTER|","_BASELINE|","_UPDATECP|","_END_ELLIPSIS|","_PATH_ELLIPSIS|","_EXPANDTABS|","_EXTERNALLEADING|","_PATH_ELLIPSIS|","_SINGLELINE|","_TABSTOP|","_WORDBREAK|",};
	UINT ualign[19]= {GP_BKGFILL ,GP_RECTCLIP ,GP_RECTFILL ,GP_LEFT ,GP_RIGHT ,GP_CENTER ,GP_TOP ,GP_BOTTOM ,GP_VCENTER ,GP_BASELINE ,GP_UPDATECP ,GP_END_ELLIPSIS ,GP_PATH_ELLIPSIS ,GP_EXPANDTABS ,GP_EXTERNALLEADING ,GP_PATH_ELLIPSIS ,GP_SINGLELINE ,GP_TABSTOP ,GP_WORDBREAK ,};

	int i;
	for(i=0;i<19;i++)
		if (strstr(pos,calign[i])) tmpAlign|=ualign[i];

	return TRUE;
}


void GPSetBrushProperty(LOGBRUSH *lb, const char *iStr)
{
	if (lb)
	{
		int r=0,g=-1,b=0;
		char *pos=new char [(int)strlen(iStr)+100];
		strcpy(pos,iStr);
		strcat(pos,"|");
		m_LastScanf=sscanf(pos,"%d,%d,%d|",&r,&g,&b);
		char *lpha[6]={"_BDIAGONAL|","_CROSS|","_DIAGCROSS|","_FDIAGONAL|","_HORIZONTAL|","_VERTICAL|",};
		UINT  uiha[6]={HS_BDIAGONAL,HS_CROSS,HS_DIAGCROSS,HS_FDIAGONAL,HS_HORIZONTAL,HS_VERTICAL,};
		char *lpstl[9]={"_DIBPATTERN|","_DIBPATTERN8X8|","_DIBPATTERNPT|","_HATCHED|","_HOLLOW|","_NULL|","_PATTERN|","_PATTERN8X8|","_SOLID|",};
		UINT  uistl[9]={BS_DIBPATTERN,BS_DIBPATTERN8X8,BS_DIBPATTERNPT,BS_HATCHED,BS_HOLLOW,BS_NULL,BS_PATTERN,BS_PATTERN8X8,BS_SOLID};

		lb->lbColor=RGB(r,g,b);
		lb->lbHatch=0;lb->lbStyle=BS_SOLID;
		int i;
		for(i=0;i<6;i++)
			if (strstr(pos,lpha[i]))	lb->lbHatch|=uiha[i];

		for(i=0;i<9;i++)
			if (strstr(pos,lpstl[i]))
			{
				if (lb->lbStyle==BS_SOLID) lb->lbStyle=0;
				lb->lbStyle|=uistl[i];
			}

		if (g<0)
		{
			g=0;
			char *pp=strchr(pos,',');
			char *tmp=strchr(pos,'|');
			if (tmp) *tmp=0;
			if (pp==NULL ||	(b=GPC.GetImageListId(++pp))<0) lb->lbColor=0;
			else lb->lbColor=0xFF000000+0x10000*r+0x100*g+b;
		}

		delete[] pos;
	}
}

void GPGetBrushString(LOGBRUSH *lb, char *iStr)
{
	if (lb)
	{
		char *lpha[6]={"_BDIAGONAL|","_CROSS|","_DIAGCROSS|","_FDIAGONAL|","_HORIZONTAL|","_VERTICAL|",};
		UINT  uiha[6]={HS_BDIAGONAL,HS_CROSS,HS_DIAGCROSS,HS_FDIAGONAL,HS_HORIZONTAL,HS_VERTICAL,};
		char *lpstl[9]={"_DIBPATTERN|","_DIBPATTERN8X8|","_DIBPATTERNPT|","_HATCHED|","_HOLLOW|","_NULL|","_PATTERN|","_PATTERN8X8|","_SOLID|",};
		UINT  uistl[9]={BS_DIBPATTERN,BS_DIBPATTERN8X8,BS_DIBPATTERNPT,BS_HATCHED,BS_HOLLOW,BS_NULL,BS_PATTERN,BS_PATTERN8X8,BS_SOLID};

		sprintf(iStr,"%d\x07%d\x07%d\x7F",
			GetRValue(lb->lbColor),GetGValue(lb->lbColor),GetBValue(lb->lbColor));

		int i;
		for(i=0;i<6;i++)
			if ((lb->lbHatch&uiha[i])==uiha[i])
				strcat(iStr,lpha[i]);

		strcat(iStr,"\x7F");

		for(i=0;i<9;i++)
			if ((lb->lbStyle&uistl[i])==uistl[i])
				strcat(iStr,lpstl[i]);

	}
}

void GPSetBrush(HWND iHWND, CBrush **bru, LOGBRUSH *lb, UINT BkgColor)
{
	if (*bru) delete *bru;
	*bru= new CBrush;
	try
	{
		if ((lb->lbColor&0xFF000000)==0xFF000000)
		{
			GPImageList *SMainIl;
			int ImgLId=lb->lbColor&0xFF;
			int nImg=(lb->lbColor&0xFF0000)/0x10000;
			if ((SMainIl=&(GPC.a_GPImageList[ImgLId])))
			{
				HBITMAP hbm=SMainIl->CreateBitmap(iHWND,nImg,BkgColor);
				(*bru)->CreatePatternBrush(CBitmap::FromHandle(hbm));
				if (hbm) DeleteObject(hbm);
			}
		}
		else
			(*bru)->CreateBrushIndirect( lb );
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("common", "943","GPSetBrush");
		delete *bru;*bru=NULL;
	}
}

void GPSetBrush(HWND iHWND, CBrushExt **bru, LOGBRUSH *lb, UINT BkgColor, const char *iStr)
{
	if (*bru) delete *bru;
	*bru= new CBrushExt;
	if ((lb->lbColor&0xFF000000)==0xFF000000)
	{
		GPImageList *SMainIl;
		int ImgLId=lb->lbColor&0xFF;
		int nImg=(lb->lbColor&0xFF0000)/0x10000;
		if ((SMainIl=&(GPC.a_GPImageList[ImgLId])))
		{
			HBITMAP hbm=SMainIl->CreateBitmap(iHWND,nImg,BkgColor);
			(*bru)->CreatePatternBrush(CBitmap::FromHandle(hbm));
			if (hbm) DeleteObject(hbm);
		}

	}
	else	(*bru)->CreateBrushIndirect( lb );

	(*bru)->CreationString=iStr;
}

UINT GPRecalcWndRect(CRect *QurentRect, CRect *EtalonRect,CRect *InitialRect, CRect *CompareRect,char *SizingStyle)
{
	UINT ret=0;
	int tmp=0;

	if (CompareRect->IsRectEmpty()==FALSE)
	{
		if (EtalonRect->IsRectEmpty()==TRUE) *EtalonRect=*CompareRect;
		else
		{
			switch(SizingStyle[0])
			{
			case 'P':
				tmp=CompareRect->left+((InitialRect->left-EtalonRect->left)*(CompareRect->Width()+1))/(EtalonRect->Width()+1);
				if (QurentRect->left!=tmp) {ret++;QurentRect->left=tmp;}
				break;
			case 'S':
				tmp=CompareRect->left-EtalonRect->left+InitialRect->left;
				if (QurentRect->left!=tmp) {ret++;QurentRect->left=tmp;}
				break;
			case 'E':
				tmp=CompareRect->right-EtalonRect->right+InitialRect->left;
				if (QurentRect->left!=tmp) {ret++;QurentRect->left=tmp;}
				break;
//			case 'N':
			default:
				QurentRect->left=InitialRect->left;
				break;
			}

			switch(SizingStyle[1])
			{
			case 'P':
				tmp=CompareRect->top+((InitialRect->top-EtalonRect->top)*(CompareRect->Height()+1))/(EtalonRect->Height()+1);
				if (QurentRect->top!=tmp) {ret++;QurentRect->top=tmp;}
				break;
			case 'S':
				tmp=CompareRect->top-EtalonRect->top+InitialRect->top;
				if (QurentRect->top!=tmp) {ret++;QurentRect->top=tmp;}
				break;
			case 'E':
				tmp=CompareRect->bottom-EtalonRect->bottom+InitialRect->top;
				if (QurentRect->top!=tmp) {ret++;QurentRect->top=tmp;}
				break;
//			case 'N':
			default:
				QurentRect->top=InitialRect->top;
				break;
			}

			switch(SizingStyle[2])
			{
			case 'P':
				tmp=CompareRect->right+((InitialRect->right-EtalonRect->right)*(CompareRect->Width()+1))/(EtalonRect->Width()+1);
				if (QurentRect->right!=tmp) {ret++;QurentRect->right=tmp;}
				break;
			case 'S':
				tmp=CompareRect->left-EtalonRect->left+InitialRect->right;
				if (QurentRect->right!=tmp) {ret++;QurentRect->right=tmp;}
				break;
			case 'E':
				tmp=CompareRect->right-EtalonRect->right+InitialRect->right;
				if (QurentRect->right!=tmp) {ret++;QurentRect->right=tmp;}
				break;
//			case 'N':
			default:
				QurentRect->right=InitialRect->right;
				break;
			}

			switch(SizingStyle[3])
			{
			case 'P':
				tmp=CompareRect->bottom+((InitialRect->bottom-EtalonRect->bottom)*(CompareRect->Height()+1))/(EtalonRect->Height()+1);
				if (QurentRect->bottom!=tmp) {ret++;QurentRect->bottom=tmp;}
				break;
			case 'S':
				tmp=CompareRect->top-EtalonRect->top+InitialRect->bottom;
				if (QurentRect->bottom!=tmp) {ret++;QurentRect->bottom=tmp;}
				break;
			case 'E':
				tmp=CompareRect->bottom-EtalonRect->bottom+InitialRect->bottom;
				if (QurentRect->bottom!=tmp) {ret++;QurentRect->bottom=tmp;}
				break;
//			case 'N':
			default:
				QurentRect->bottom=InitialRect->bottom;
				break;
			}
		}
	}
	return ret;
}


UINT SetObjStlCheck(CCheckListBox *m_ListUnitStl, UINT Stl, int nn,const char **lpstl,const UINT *uistl,const UINT *uimask,UINT add )
{
	UINT ret=0;
	if (m_ListUnitStl && m_ListUnitStl->m_hWnd)
	{
		int posD=0;
		if (add==0)
		{
			char str[200];
			strncpy(str,lpstl[0],200);
			str[199]=0;
			{char *pos1=strchr(str,'|');if (pos1) *pos1=0;}
			posD=m_ListUnitStl->FindStringExact(0,str);
		}

		int i;
		for(i=0;i<nn;i++)
		{
			int pos;
			if (add>0)
			{
				char str[200];
				strncpy(str,lpstl[i],200);
				str[199]=0;
				{char *pos1=strchr(str,'|');if (pos1) *pos1=0;}
				pos=m_ListUnitStl->AddString(str);
			}
			else pos=i;
			BOOL rr=FALSE;

			if (uistl[i]==0) {if ((Stl&uimask[i])==uimask[i]) rr=TRUE;}
				else
			if ((Stl&uimask[i])==uistl[i]) rr=TRUE;
			m_ListUnitStl->SetCheck(pos+posD,rr);
			if (rr==TRUE) ret|=uistl[i];
		}
	}
	return ret;
}


UINT GetObjStlStr(char *m_StlStr, UINT Stl, int nn,const char **lpstl,const UINT *uistl,const UINT *uimask)
{
	UINT ret=0;
	if (m_StlStr)
	{
		*m_StlStr=0;
		if (nn==N_WND_STYLES && strncmp(lpstl[0],"WS_B",4)==0 && aWndStyleUINT[N_WND_STYLES-1]==WS_CHILD)
		{
			if ((Stl&WS_CHILD)==WS_CHILD)
			{
				if ((Stl&WS_POPUPWINDOW)==WS_POPUPWINDOW ) Stl^=WS_POPUPWINDOW;
				if ((Stl&WS_POPUP)==WS_POPUP ) Stl^=WS_POPUP;
			}
			if ((WS_OVERLAPPEDWINDOW&Stl)==WS_OVERLAPPEDWINDOW)	{strcat(m_StlStr,"WS_OVERLAPPEDWINDOW|");Stl^=WS_OVERLAPPEDWINDOW;}
			if ((WS_POPUPWINDOW&Stl)==WS_POPUPWINDOW)	{strcat(m_StlStr,"WS_POPUPWINDOW|");Stl^=WS_POPUPWINDOW;}
			if ((WS_CAPTION&Stl)==WS_CAPTION)	{strcat(m_StlStr,"WS_CAPTION|");Stl^=WS_CAPTION;}
			if ((Stl&WS_CHILD)==WS_CHILD)
			{
				if ((WS_GROUP&Stl)==WS_GROUP)		{strcat(m_StlStr,"WS_GROUP|");Stl^=WS_GROUP;}
				if ((WS_TABSTOP&Stl)==WS_TABSTOP)	{strcat(m_StlStr,"WS_TABSTOP|");Stl^=WS_TABSTOP;}
				if ((WS_THICKFRAME&Stl)==WS_THICKFRAME)	{strcat(m_StlStr,"WS_THICKFRAME|");Stl^=WS_THICKFRAME;}
				if ((WS_MINIMIZE&Stl)==WS_MINIMIZE)	{strcat(m_StlStr,"WS_MINIMIZE|");Stl^=WS_MINIMIZE;}
				Stl^=WS_CHILD;
			}
			else
			{
				if ((WS_MINIMIZEBOX&Stl)==WS_MINIMIZEBOX)	{strcat(m_StlStr,"WS_MINIMIZEBOX|");Stl^=WS_MINIMIZEBOX;}
				if ((WS_MAXIMIZEBOX&Stl)==WS_MAXIMIZEBOX)	{strcat(m_StlStr,"WS_MAXIMIZEBOX|");Stl^=WS_MAXIMIZEBOX;}
				if ((WS_SIZEBOX&Stl)==WS_SIZEBOX)			{strcat(m_StlStr,"WS_SIZEBOX|");Stl^=WS_SIZEBOX;}
				if ((WS_ICONIC&Stl)==WS_ICONIC)				{strcat(m_StlStr,"WS_ICONIC|");Stl^=WS_ICONIC;}
			}
		}

		if (nn==N_WND_EX_STYLES && strncmp(lpstl[0],"WS_E",4)==0)
		{
			if ((WS_EX_PALETTEWINDOW&Stl)==WS_EX_PALETTEWINDOW)	{strcat(m_StlStr,"WS_EX_PALETTEWINDOW|");Stl^=WS_EX_PALETTEWINDOW;}
			if ((WS_EX_OVERLAPPEDWINDOW&Stl)==WS_EX_OVERLAPPEDWINDOW)	{strcat(m_StlStr,"WS_EX_OVERLAPPEDWINDOW|");Stl^=WS_EX_OVERLAPPEDWINDOW;}
		}

		int i;
		for(i=0;i<nn;i++)
			if (uistl[i]!=0 && (Stl&uimask[i])==uistl[i])
			{
				strcat(m_StlStr,lpstl[i]);
				ret|=uistl[i];
			}
	}
	return ret;
}

int StringToClip(const char *str)
{
	int ret=0;
	if (AfxGetMainWnd()->OpenClipboard())
	{
		EmptyClipboard();

		HANDLE fff=::GetClipboardData(CF_LOCALE);
		if (fff)
		{
			UINT *ptr = static_cast<UINT *>(::GlobalLock(fff));

			*ptr=GetInputCodePage();
			::GlobalUnlock(fff);
			::SetClipboardData(CF_LOCALE , fff);
		}
		else
		{
			HGLOBAL hand1 = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT,
				64);
			if (hand1) {
			UINT *ptr = static_cast<UINT *>(::GlobalLock(hand1));

			*ptr=GetInputCodePage();
			::GlobalUnlock(hand1);
			::SetClipboardData(CF_LOCALE , hand1);
				
			}
		}

		HGLOBAL hglbCopy;
		hglbCopy = GlobalAlloc(GMEM_DDESHARE, (ret=((int)strlen(str) + 5)) * sizeof(TCHAR));
	    if (hglbCopy != NULL)
		{
			LPTSTR  lptstrCopy;
			lptstrCopy = (LPTSTR) GlobalLock(hglbCopy);
			memcpy(lptstrCopy,	str,  ((int)strlen(str) + 4) * sizeof(TCHAR));
		    GlobalUnlock(hglbCopy);
			SetClipboardData(CF_TEXT,hglbCopy);
       }
		CloseClipboard();
	}
	return ret;
}

void GPRecalcOffsetRect(CWnd *Current, CWnd *Owner, CRect *Re)
{
	if (Re)
	{
		Re->SetRectEmpty();
		if (Owner)
		{
			Current->GetWindowRect(Re);
			if (Owner)
			{
				CRect re2;
				Owner->GetClientRect(&re2);
				Owner->ClientToScreen(&re2);
				Re->OffsetRect(-re2.TopLeft());
			}
		}
	}
}

#include <comdef.h>

long ConvVariantToString( const VARIANT FAR& inArray, CString &Line, const char *DelimeterStr)
{
	Line="";
	const VARIANT *ipArray=&inArray;

	if (V_VT(ipArray)==(VT_VARIANT|VT_BYREF))	ipArray=inArray.pvarVal;


	if ((V_VT(ipArray)&VT_ARRAY) == VT_ARRAY)
	{
		if (ConvertToString(ipArray,Line, DelimeterStr)<=0) Line="";
	}
	else
		if (V_VT(ipArray) == (VT_VARIANT|VT_BYREF) && (V_VT(ipArray->pvarVal)&VT_ARRAY) == VT_ARRAY)
		{
			if (ConvertToString(ipArray->pvarVal,Line, DelimeterStr)<=0) Line="";
		}
		else
		if ((V_VT(ipArray)&VT_BYREF)==VT_BYREF)
		{
			switch(V_VT(ipArray)&0xFF)
			{
			case VT_BSTR:	Line=*ipArray->pbstrVal; break;
			case VT_I2:
			case VT_I4:
			case VT_R4:
			case VT_R8:
			case VT_CY:
			case VT_DATE:
			case VT_ERROR:
			case VT_BOOL:
			case VT_UI1:
				{
					_variant_t var2(*ipArray);
					var2.ChangeType(VT_BSTR);
					Line=(LPCWSTR)var2.bstrVal;
				}
				break;
			case VT_EMPTY: Line=""; break;
			default: 	AfxThrowOleDispatchException(1007,IDS_GPOLEEXEPTION1007);
				break;
			}
		}
		else
		{
			switch(V_VT(ipArray)&0xFF)
			{
			case VT_BSTR:	Line=V_BSTR(ipArray); break;
			case VT_I2:
			case VT_I4:
			case VT_R4:
			case VT_R8:
			case VT_CY:
			case VT_DATE:
			case VT_ERROR:
			case VT_BOOL:
			case VT_UI1:
				{
					_variant_t var2(*ipArray);
					var2.ChangeType(VT_BSTR);
					Line=(LPCWSTR)var2.bstrVal;
				}
				break;
			case VT_EMPTY: Line=""; break;
			default: 	AfxThrowOleDispatchException(1007,IDS_GPOLEEXEPTION1007);
				break;
			}
		}
	return Line.GetLength();
}


long ConvertToString(const VARIANT FAR* vArray,CString &oStr, CString DelimeterStr)
{
	oStr="";

	SAFEARRAY FAR* psa = NULL;

	USES_CONVERSION;

	HRESULT hr;

	if ((V_VT(vArray)&VT_ARRAY) != VT_ARRAY )	AfxThrowOleDispatchException(1001,IDS_GPOLEEXEPTION1001);
	else
	{
		psa = V_ARRAY(vArray);
		// Check dimensions of the array.
		if (SafeArrayGetDim(psa) != 1)				AfxThrowOleDispatchException(1002,IDS_GPOLEEXEPTION1002);
		else
		{
			unsigned short ConvOn=(unsigned short)((V_VT(vArray) != (VT_ARRAY | VT_BSTR))?(V_VT(vArray)&0xFF):VT_BSTR);
			LONG lLBound, lUBound;


			hr = SafeArrayGetLBound(psa, 1, &lLBound);
			if (FAILED(hr))		AfxThrowOleDispatchException(1003,IDS_GPOLEEXEPTION1003);
			else
			{
				hr = SafeArrayGetUBound(psa, 1, &lUBound);
				if (FAILED(hr))		AfxThrowOleDispatchException(1004,IDS_GPOLEEXEPTION1004);
				else
				{
					long int ix;
					int nItem=lUBound-lLBound;
					CString str1(""), str2(""),	 str3(""), str4("");

					if (ConvOn==VT_BSTR)
					{
						BSTR HUGEP *pbstr;
						hr = SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						if (FAILED(hr))     AfxThrowOleDispatchException(1003,IDS_GPOLEEXEPTION1003);
						int i ;
						for(i = 0; i <= nItem; i++)
						{
							str1+=(LPCWSTR)pbstr[i];
							if (i< nItem) str1+=DelimeterStr;
							if ((i%10)==0)
							{
								str2+=str1; str1="";
								if ((i%80)==0)
								{
									str3+=str2; str2="";
									if ((i%400)==0)	{str4+=str3; str3="";}
								}
							}
						}
						SafeArrayUnaccessData(psa);
					}
					else
					if (ConvOn==VT_VARIANT)
					{
						VARIANT HUGEP *pbvar;
						hr = SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbvar);
						if (FAILED(hr))     AfxThrowOleDispatchException(1003,IDS_GPOLEEXEPTION1003);
						int i ;
						for(i = 0; i <= nItem; i++)
						{
							if ((V_VT(pbvar+i)&VT_ARRAY)==VT_ARRAY)
							{
								CString tmpDelim(DelimeterStr);
								if (tmpDelim[0]==127) tmpDelim.SetAt(0,1);
								else
								if (tmpDelim[0]>=1 && tmpDelim[0]<=5) tmpDelim.SetAt(0,(char)(tmpDelim[0]+1));
								CString tmpS;
								ConvertToString(pbvar+i,tmpS,tmpDelim);
								str1+=tmpS;
							}
							else
							if (pbvar[i].bstrVal)
							{
								COleVariant vtmp(pbvar[i]);
								vtmp.ChangeType(VT_BSTR);
								str1+=(LPCWSTR)vtmp.bstrVal;
							}

							if (i< nItem) str1+=DelimeterStr;
							if ((i%10)==0)
							{
								str2+=str1; str1="";
								if ((i%80)==0)
								{
									str3+=str2; str2="";
									if ((i%400)==0)	{str4+=str3; str3="";}
								}
							}
						}
						SafeArrayUnaccessData(psa);
					}
					else
					{
						VARIANT v;
						VariantInit(&v);
						VARIANT HUGEP *pbvar;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbvar);

						int i ;
						for(i = 0; i <= nItem; i++)
						{
							v.vt=(unsigned short)(V_VT(vArray)&0xFF);
							ix=i+lLBound;
//							SafeArrayPtrOfIndex( psa, &ix, (void **)(&v.lVal));
							SafeArrayGetElement( psa, &ix, &v.lVal);
							VariantChangeType(&v,&v,0,VT_BSTR);
							str1+=(LPCWSTR)v.bstrVal;
							if (i< nItem) str1+=DelimeterStr;
							VariantClear(&v);

							if ((i%10)==0)
							{
								str2+=str1; str1="";
								if ((i%80)==0)
								{
									str3+=str2; str2="";
									if ((i%400)==0)	{str4+=str3; str3="";}
								}
							}
						}
						SafeArrayUnaccessData(psa);
					}

					oStr=str4+str3+str2+str1;
					return oStr.GetLength();
				}

			}
		}
	}

	return -1;
}

long ConvertToArray(const CString &iStr, VARIANT FAR* vArray, CString DelimeterStr, DWORD dwArrayType)
{
	long ix=-1;

	SAFEARRAY FAR* psa = NULL;

	USES_CONVERSION;
	SAFEARRAYBOUND tmpSAB={0};

//	HRESULT hr;
	long nElements;
	int i=0,DelimLen=DelimeterStr.GetLength();

	for(nElements=1; (i=iStr.Find(DelimeterStr,i))>=0; i+=DelimLen,nElements++);

	tmpSAB.cElements=nElements;

	if ((V_VT(vArray)&VT_ARRAY) == VT_ARRAY )
	{
		psa = V_ARRAY(vArray);
		SafeArrayGetLBound(psa,1,&tmpSAB.lLbound);
		SafeArrayDestroy(psa);
	}

	VariantInit(vArray);

	try
	{
		COleSafeArray SAtmp;
		SAtmp.Create(dwArrayType?VT_VARIANT:VT_BSTR, 1,&tmpSAB.cElements);
		VariantCopy(vArray,SAtmp);
//		SAtmp.Destroy();
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("common", "1475","ConvertToArray");
	}

	psa = V_ARRAY(vArray);
	// Check dimensions of the array.
	if (SafeArrayGetDim(psa) != 1)			AfxThrowOleDispatchException(1002,IDS_GPOLEEXEPTION1002);
	else
	{
		int nFirst=0,nLast;
		CString CStmp;
		COleVariant tmpOV("");
		BSTR HUGEP *pbstr;
		VARIANT HUGEP *pVar;
		HRESULT hr;
		if (dwArrayType)
			hr = SafeArrayAccessData(psa, (void HUGEP* FAR*)&pVar);
		else
			hr = SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);

		if (FAILED(hr))		AfxThrowOleDispatchException(1001,IDS_GPOLEEXEPTION1001);

		for(ix=0; ix<nElements; ix++)
		{
			nLast=iStr.Find(DelimeterStr,nFirst);
			if (nLast<0)
			{
				nLast=iStr.GetLength()-nFirst;
				CStmp=nLast>0?iStr.Right(iStr.GetLength()-nFirst):"";
			}
			else
			if (nLast==nFirst)	CStmp="";
			else				CStmp=iStr.Mid(nFirst,nLast-nFirst);

			if (dwArrayType)
			{
				VariantInit(&pVar[ix]);
				pVar[ix].vt=VT_BSTR;
				pVar[ix].bstrVal=CStmp.AllocSysString();
			}
			else
			{
				CStmp.SetSysString(&pbstr[ix]);
			}
			nFirst=nLast+DelimLen;
		}
		SafeArrayUnaccessData(psa);
	}

	return ix;
}

long StringToArrayEx(LPCTSTR iString, VARIANT FAR* oArray, const char *strdelim)
{
	char *strd=new char [(int)strlen(strdelim)+5000];
	strcpy(strd,strdelim);
	char *pos=strstr(strd,"q1w2e3r4");
	if (pos) {*pos=0;pos+=8;}	else pos="";

	if (*strd!=0)
	{
		COleSafeArray tmp;
		DWORD nElement=1;
		long lUBound;
		long i=0,DelimLen=(int)strlen(strd);
		const char *STRpos=iString;

		while((STRpos=strstr(STRpos,strd)))
			{	STRpos+=DelimLen;	nElement++;	}

		tmp.Create(VT_VARIANT,1,&nElement);

		tmp.GetUBound(1,&lUBound);
		STRpos=iString;
		const char *STRpos2;
		VARIANT *v;

		COleVariant tmpOV("");
		for(tmp.GetLBound(1,&i); i<=lUBound;i++)
		{
			STRpos2=strstr(STRpos,strd);
			char *tmpSTR;
			if (STRpos2)
			{
				tmpSTR=new char [STRpos2-STRpos+5];
				strncpy(tmpSTR,STRpos,STRpos2-STRpos);
				tmpSTR[STRpos2-STRpos]=0;
			}
			else
			{
				tmpSTR=new char [(int)strlen(STRpos)+500];
				strcpy(tmpSTR,STRpos);
			}

			tmp.PtrOfIndex(&i,(void **)&v);

			char *postmp=strstr(pos,"q1w2e3r4");
			if (postmp) *postmp=0;

			if (strstr(tmpSTR,pos) && *pos!=0)
			{
				if (postmp) *postmp='q';
				StringToArrayEx(tmpSTR,v,pos);
			}
			else
			{
				if (postmp)
				{
					*postmp='q';

					int nLevels=0;
					while(postmp)
					{
						nLevels++;
						postmp+=8;
						char *postmp2=strstr(postmp,"q1w2e3r4");
						if (postmp2)	*postmp2=0;
						if (strstr(tmpSTR,postmp))
						{

							while (nLevels--)
							{
								COleSafeArray tmp2;
								DWORD nElement2=1;
								tmp2.Create(VT_VARIANT,1,&nElement2);
								VariantInit(v);
								VariantCopy(v,tmp2);
								SAFEARRAY FAR* psatmp = NULL;
								psatmp = V_ARRAY(v);
								LONG ix=0;
								SafeArrayPtrOfIndex( psatmp, &ix,(void **) &v);
							}

							if (postmp2)	*postmp2='q';
							StringToArrayEx(tmpSTR,v,postmp);
							break;
						}

						if (postmp2)	*postmp2='q';
						postmp=postmp2;
					}
					if (postmp==NULL || v->vt==VT_EMPTY)
						{tmpOV=tmpSTR;VariantInit(v);	VariantCopy(v,tmpOV);	}
				}
				else
				{
					tmpOV=tmpSTR;
					VariantCopy(v,tmpOV);
				}
			}
			delete[] tmpSTR;
			if (STRpos2==NULL) break;
			STRpos=STRpos2+DelimLen;
		}

		VariantInit(oArray);
		VariantCopy(oArray,tmp);
	}
	delete[] strd;
	return 0;
}

long CountOccurence(const CString & iString, const CString & OccurString)
{
	long ret=0,pos=0;

	while((pos=iString.Find(OccurString,pos))>=0)
		{pos++;	ret++;}

	return ret;
}

long GetIndexSubString(const CString & iString, const CString & SubString, long Occurence)
{
	long count=1,pos=0;

	while((pos=iString.Find(SubString,pos))>=0 && count<Occurence)
		{pos++;	count++;}

	return pos;
}


long ArrayToStringEx(const VARIANT FAR* vArray,CString &oStr,const char *DelimetersArray)
{
	long retLen=-1;
	oStr="";
	SAFEARRAY FAR* psa = NULL;
	USES_CONVERSION;
	HRESULT hr;

	char *posdel=new char [(int)strlen(DelimetersArray)+500];
	strcpy(posdel,DelimetersArray);
	char *posdel2=strstr(posdel,"q1w2e3r4");
	if (posdel2) *posdel2=0;

	if ((V_VT(vArray)&VT_ARRAY) != VT_ARRAY )	AfxThrowOleDispatchException(1001,IDS_GPOLEEXEPTION1001);
	else
	{
		psa = V_ARRAY(vArray);
		// Check dimensions of the array.
		if (SafeArrayGetDim(psa) != 1)				AfxThrowOleDispatchException(1002,IDS_GPOLEEXEPTION1002);
		else
		{
			unsigned short ConvOn=(unsigned short)(V_VT(vArray)&0xFF);
			LONG lLBound, lUBound;
			hr = SafeArrayGetLBound(psa, 1, &lLBound);
			if (FAILED(hr))		AfxThrowOleDispatchException(1003,IDS_GPOLEEXEPTION1003);
			else
			{
				hr = SafeArrayGetUBound(psa, 1, &lUBound);
				if (FAILED(hr))		AfxThrowOleDispatchException(1004,IDS_GPOLEEXEPTION1004);
				else
				{
					long int ix;
					int nItem=lUBound-lLBound;
					CString str1("");
					CString str2("");
					CString str3("");
					CString str4("");

					if (ConvOn==VT_BSTR)
					{
						BSTR HUGEP *pbstr;
						hr = SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						if (FAILED(hr))     AfxThrowOleDispatchException(1003,IDS_GPOLEEXEPTION1003);
						int i ;
						for(i = 0; i <= nItem; i++)
						{
							str1+=(LPCWSTR)pbstr[i];
							if (i< nItem) str1+=posdel;
							if ((i%10)==0)
							{
								str2+=str1; str1="";
								if ((i%80)==0)
								{
									str3+=str2; str2="";
									if ((i%400)==0)	{str4+=str3; str3="";}
								}
							}
						}
						SafeArrayUnaccessData(psa);
					}
					else
					if (ConvOn==VT_VARIANT)
					{
						char *posdel2next=posdel;
						if (posdel2next==NULL) posdel2next="";
						else posdel2next+=9;
						VARIANT HUGEP *pVar;
						hr = SafeArrayAccessData(psa, (void HUGEP* FAR*)&pVar);
						if (FAILED(hr))     AfxThrowOleDispatchException(1003,IDS_GPOLEEXEPTION1003);
						CString CStmp;

						int i ;
						for(i = 0; i <= nItem; i++)
						{
							if ((V_VT(&pVar[i])&VT_ARRAY)==VT_ARRAY)
								 ArrayToStringEx(&pVar[i],CStmp,posdel2next);
							else ConvVariantToString(pVar[i],CStmp,posdel2next);

							str1+=CStmp;

							if (i< nItem) str1+=posdel;
							if ((i%10)==0)
							{
								str2+=str1; str1="";
								if ((i%80)==0)
								{
									str3+=str2; str2="";
									if ((i%400)==0)	{str4+=str3; str3="";}
								}
							}
						}
						SafeArrayUnaccessData(psa);
					}
					else
					{
						VARIANT v;
						VariantInit(&v);
						VARIANT HUGEP *pbvar;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbvar);
						int i ;
						for(i = 0; i <= nItem; i++)
						{
							v.vt=(unsigned short)(V_VT(vArray)&0xFF);
							ix=i+lLBound;
							SafeArrayPtrOfIndex( psa, &ix,(void **) &v.lVal);
							VariantChangeType(&v,&v,0,VT_BSTR);
							str1+=(LPCWSTR)v.bstrVal;
							if (i< nItem) str1+=posdel;
							VariantClear(&v);

							if ((i%10)==0)
							{
								str2+=str1; str1="";
								if ((i%80)==0)
								{
									str3+=str2; str2="";
									if ((i%400)==0)	{str4+=str3; str3="";}
								}
							}
						}
						SafeArrayUnaccessData(psa);
					}
					oStr=str4+str3+str2+str1;
					retLen=oStr.GetLength();
				}
			}
		}
	}

	delete[] posdel;
	return retLen;
}


void qsCharLine(const char **Item, int left, int right)
{
	register int i,j;
	const char *x,*y;

	i=left;
	j=right;
	x=Item[(left+right)/2];

	do
	{
		while(strcmp(Item[i],x)<0 && i<right) i++;
		while(strcmp(x,Item[j])<0 && j>left) j--;

		if (i<=j)
		{
			y=Item[i];		Item[i]=Item[j];		Item[j]=y;
			i++;			j--;
		}
	}while(i<=j);
	if(left<j) qsCharLine(Item,left,j);
	if (i<right) qsCharLine(Item,i,right);
}


void qsCharILine(const char **Item, int left, int right)
{
	register int i,j;
	const char *x,*y;

	i=left;
	j=right;
	x=Item[(left+right)/2];

	do
	{
		while(_stricmp(Item[i],x)<0 && i<right) i++;
		while(_stricmp(x,Item[j])<0 && j>left) j--;


		if (i<=j)
		{
			y=Item[i];		Item[i]=Item[j];		Item[j]=y;
			i++;			j--;
		}
	}while(i<=j);
	if(left<j) qsCharILine(Item,left,j);
	if (i<right) qsCharILine(Item,i,right);
}

void qsCharLineAndDWORD(const char **Item, DWORD *dwItem, int left, int right)
{
	register int i,j;
	const char *x,*y;
	DWORD dwTmp;

	i=left;
	j=right;
	x=Item[(left+right)/2];

	do
	{
		while(strcmp(Item[i],x)<0 && i<right) i++;
		while(strcmp(x,Item[j])<0 && j>left) j--;

		if (i<=j)
		{
			y=Item[i];			Item[i]=Item[j];		Item[j]=y;
			dwTmp=dwItem[i];	dwItem[i]=dwItem[j];	dwItem[j]=dwTmp;
			i++;			j--;
		}
	}while(i<=j);
	if(left<j) qsCharLineAndDWORD(Item,dwItem, left,j);
	if (i<right) qsCharLineAndDWORD(Item,dwItem, i,right);
}

void qsCharILineAndDWORD(const char **Item, DWORD *dwItem, int left, int right)
{
	register int i,j;
	const char *x,*y;
	DWORD dwTmp;

	i=left;
	j=right;
	x=Item[(left+right)/2];

	do
	{
		while(_stricmp(Item[i],x)<0 && i<right) i++;
		while(_stricmp(x,Item[j])<0 && j>left) j--;

		if (i<=j)
		{
			y=Item[i];			Item[i]=Item[j];		Item[j]=y;
			dwTmp=dwItem[i];	dwItem[i]=dwItem[j];	dwItem[j]=dwTmp;
			i++;			j--;
		}
	}while(i<=j);
	if(left<j) qsCharILineAndDWORD(Item,dwItem,left,j);
	if (i<right) qsCharILineAndDWORD(Item,dwItem,i,right);
}


void qsBSTRLine(BSTR *Item, int left, int right)
{
	USES_CONVERSION;
	register int i,j;
	BSTR x,y;

	i=left;
	j=right;
	x=Item[(left+right)/2];

	do
	{
		while(wcscmp(Item[i],x)<0 && i<right) i++;
		while(wcscmp(x,Item[j])<0 && j>left) j--;

		if (i<=j)
		{
			y=Item[i];		Item[i]=Item[j];		Item[j]=y;
			i++;			j--;
		}
	}while(i<=j);
	if(left<j) qsBSTRLine(Item,left,j);
	if (i<right) qsBSTRLine(Item,i,right);
}

void qsBSTRILine(BSTR *Item, int left, int right)
{
	USES_CONVERSION;
	register int i,j;
	BSTR x,y;

	i=left;
	j=right;
	x=Item[(left+right)/2];

	do
	{
		while(_wcsicmp(Item[i],x)<0 && i<right) i++;
		while(_wcsicmp(x,Item[j])<0 && j>left) j--;


		if (i<=j)
		{
			y=Item[i];		Item[i]=Item[j];		Item[j]=y;
			i++;			j--;
		}
	}while(i<=j);
	if(left<j) qsBSTRILine(Item,left,j);
	if (i<right) qsBSTRILine(Item,i,right);
}

void qsVARIANT(VARIANT *Item, int left, int right)
{
	USES_CONVERSION;
	register int i,j;
	VARIANT x,y;
	VariantInit(&x);
	VariantInit(&y);

	i=left;
	j=right;

	if (V_VT(Item)==VT_BSTR)
	{
		VariantCopy(&x,Item+(left+right)/2);
		do
		{
			while(wcscmp(Item[i].bstrVal,x.bstrVal)<0 && i<right)
				i++;
			while(wcscmp(x.bstrVal,Item[j].bstrVal)<0 && j>left)
				j--;

			if (i<=j)
			{
				VariantCopy(&y,Item+i);	VariantCopy(Item+i,Item+j);	VariantCopy(Item+j,&y);
				i++;				j--;
			}
		}while(i<=j);
		VariantClear(&x);
		VariantClear(&y);
	}
	else
	{
		x=Item[(left+right)/2];
		do
		{
			while(Item[i].dblVal<x.dblVal && i<right) i++;
			while(x.dblVal<Item[j].dblVal && j>left) j--;

			if (i<=j)
			{
				y=Item[i];			Item[i]=Item[j];			Item[j]=y;
				i++;				j--;
			}
		}while(i<=j);
	}

	if(left<j) qsVARIANT(Item,left,j);
	if (i<right) qsVARIANT(Item,i,right);
}

void qsVARIANTI(VARIANT *Item, int left, int right)
{
	USES_CONVERSION;
	register int i,j;
	VARIANT x,y;

	i=left;
	j=right;
	x=Item[(left+right)/2];

	if (V_VT(Item)==VT_BSTR)
	{
		do
		{
			while(_wcsicmp(Item[i].bstrVal,x.bstrVal)<0 && i<right) i++;
			while(_wcsicmp(x.bstrVal,Item[j].bstrVal)<0 && j>left) j--;

			if (i<=j)
			{
				y=Item[i];			Item[i]=Item[j];			Item[j]=y;
				i++;				j--;
			}
		}while(i<=j);
	}
	else
	{
		do
		{
			while(Item[i].dblVal<x.dblVal && i<right) i++;
			while(x.dblVal<Item[j].dblVal && j>left) j--;

			if (i<=j)
			{
				y=Item[i];			Item[i]=Item[j];			Item[j]=y;
				i++;				j--;
			}
		}while(i<=j);
	}

	if(left<j) qsVARIANTI(Item,left,j);
	if (i<right) qsVARIANTI(Item,i,right);
}

int CompareIntASC(const void *arg1, const void *arg2)
	{return *(int *)arg1-*(int *)arg2;}
int CompareIntDES(const void *arg1, const void *arg2)	{return *(int *)arg2-*(int *)arg1;}


BOOL LoadPalette(const char *FileName,UINT *cF, UINT *cB)
{
	BOOL ret = FALSE;
	FILE *tmp=fopen(FileName,"rt");
	if (tmp)
	{
		char str[550];
		char *pos;
		while(fgets(str,500,tmp))
			if ((pos=strchr(str,'=')))
			{
				_strupr(str);
				int col=0;

				for(col=0;col<8 && strstr(str,CGPDlgColor127::aColorName[col])==NULL;col++);
				if (col<8)
				{
					UINT clr[3]={0,0,0,};
					int j=0;
					while(*pos!=0 && j<3)
					{
						while(*pos!=0 && (*pos<'0' || *pos>'9')) pos++;
						if (*pos!=0) clr[j++]=atoi(pos);
						while(*pos!=0 && *pos>='0' && *pos<='9') pos++;
					}

					if (strstr(str,CGPDlgColor127::aForeBackName[1]))
						cB[col]=RGB(clr[0],clr[1],clr[2]);
					else
					{
						j=0;
						if (strstr(str,CGPDlgColor127::aIntensityName[1])) j=8;
						cF[col+j]=RGB(clr[0],clr[1],clr[2]);
					}
				}
				ret = TRUE;
			}
		fclose(tmp);
	}
	return ret;
}

BOOL GPDeleteDir(const char * iDir)
{
	CFileFind ff;
	BOOL ret;
	CString sDir=iDir;
	sDir+="\\*.*";

	ret=ff.FindFile(sDir,0);

	while(ret)
	{
		ret=ff.FindNextFile();
		if (!ff.IsDots())
		{
			if (ff.IsDirectory())	GPDeleteDir(ff.GetFilePath());
			else					DeleteFile(ff.GetFilePath());
		}
	}
	ff.Close();

	_rmdir(iDir);
	return ret;
}


BOOL GPCopyDir(const char * sDir, const char * dDir)
{
	CFileFind ff;
	BOOL ret=FALSE;
	CString tmpsDir=sDir;
	tmpsDir+="\\*.*";

	if (_mkdir(dDir)==0)
	{
		ret=ff.FindFile(tmpsDir,0);
		while(ret)
		{
			ret=ff.FindNextFile();
			tmpsDir=dDir;
			tmpsDir+="\\"+ff.GetFileName();

			if (!ff.IsDots())
			{
				if (ff.IsDirectory())	GPCopyDir(ff.GetFilePath(),tmpsDir);
				else					CopyFile(ff.GetFilePath(),tmpsDir,FALSE);
			}
		}
		ff.Close();
	}

	return ret;
}

long ConvertStringToString(CString &iStr,CString &oStr)//my function
{
	long res=-1;
	int counter=iStr.GetLength();
	char* tmp=new char[counter+1];
	BOOL flgapostr1=FALSE;
	BOOL flgapostr2=FALSE;
	int i=0;

	while (i<counter)
	{
		if ((!flgapostr1) && (!flgapostr2))
		{
			if (iStr[i]!=',')
				tmp[i]=iStr[i];
			else
				tmp[i]=1;
		}
		else
			tmp[i]=iStr[i];


		if (iStr[i]=='\'')
		{
			if (!flgapostr2)
				flgapostr1=!flgapostr1;
		}
		if (iStr[i]=='\"')
		{
			if (!flgapostr1)
				flgapostr2=!flgapostr2;
		}
		i++;
	}
	tmp[i]='\0';
	oStr=tmp;

	return res;
}

const CString ExtractField(const char * iStr, int FieldNum, const char * delim)
{
	CString ret="";
	const char *pos;
	int lendelim=(int)strlen(delim);

	while((pos=strstr(iStr,delim)) && --FieldNum>0)
		iStr=pos+lendelim;

	if (pos)
	{
		char *tmp=new char [pos-iStr+5];
		strncpy(tmp,iStr,pos-iStr);
		tmp[pos-iStr]=0;
		ret=tmp;
		delete[] tmp;
	}
	else
		if (FieldNum==1) ret=iStr;

	return ret;
}

const CString SetMVField(CString & iStr, const char *iNewValue, int FieldNum, int iCharPos, int iStrSubLen, const char * delim)
{
	if (delim && *delim && iNewValue)
	{
		int DelimLen=(int)strlen(delim);
		char *tmps="";
		if (iCharPos>1) 
		{
			tmps=new char [iCharPos+1];
			FillMemory(tmps,iCharPos,' ');
			tmps[iCharPos-1]=0;
		}
		if (FieldNum<=0)
		{
			if (FieldNum==-2 || iStr.GetLength()) iStr+=delim;

			if (FieldNum!=0)
			{
				if (*tmps) iStr+=tmps;
				iStr+=iNewValue;
			}
			else 
			{
				if (*tmps) 
				{
					iStr=tmps;
					iStr+=iNewValue;
				}
				else
					iStr=iNewValue;
			}
		}
		else
		{
			int delimlen=(int)strlen(delim);
			int iFielStartPos=0;
			CString csCurField=ExtractField(iStr,FieldNum,delim);
			{
				const char *tmpposInit=iStr;
				const char *tmppos=iStr;
				int nRealFields=1;
				while((tmppos=strstr(tmppos,delim)) && nRealFields<FieldNum)
				{
					tmppos+=delimlen;
					iFielStartPos=tmppos-tmpposInit;
					nRealFields++;
				}

				nRealFields=FieldNum-nRealFields;
				if (nRealFields>0)
				{
					while(nRealFields-->0) iStr+=delim;
					iFielStartPos=iStr.GetLength();
				}
			}
			const char *ccCurField=FindField(iStr,FieldNum,delim);
			const char *ccNextField=FindField(iStr,FieldNum+1,delim);
			if (iCharPos>0)
			{
				CString csBegin;
				if (iCharPos==1) 
				{
					csBegin=tmps;
					if (csCurField.GetLength()>iStrSubLen)
						csCurField=iNewValue+csCurField.Mid(iStrSubLen,csCurField.GetLength());
					else
						csCurField=iNewValue;
				}
				else 
				{
					csBegin=csCurField.Mid(0,iCharPos-1)+tmps; 
					if (csCurField.GetLength()>=iCharPos-1+iStrSubLen)
						csCurField=csBegin.Mid(0,iCharPos-1)+iNewValue+csCurField.Mid(iCharPos-1+iStrSubLen,csCurField.GetLength());
					else
						csCurField=csBegin.Mid(0,iCharPos-1)+iNewValue;
				}
			}
			else csCurField=iNewValue;

			if (iFielStartPos<=0)
				iStr=csCurField+(*ccNextField?ccNextField-delimlen:"");
			else
			{
				CString newres=iStr.Mid(0,iFielStartPos)+csCurField+(*ccNextField?ccNextField-delimlen:"");
				iStr=newres;
			}
		}
		if (tmps && *tmps) delete []tmps;
	}
	return iStr;
}

const CString SetSubField(CString & iStr, const char *iNewValue, int FieldNum,int FieldNum2, int iCharPos, int iStrSubLen, const char * delim, const char * delim2)
{
	CString tmpAttribute=FieldNum<=0?"":ExtractField(iStr,FieldNum,delim);
	SetMVField(tmpAttribute,iNewValue,FieldNum2, iCharPos, iStrSubLen, delim2);
	SetMVField(iStr,tmpAttribute,FieldNum, -1, -1, delim);
	return iStr;
}

DWORD ExtractScriptPart(const char *iValue, PARGPOSITIONS pPositions)
{
	DWORD ret=-1;
	const char *tmppos=iValue;
	if (pPositions) 
	{
		ZeroMemory(pPositions, sizeof(ARGPOSITIONS));
		if (iValue)
		{
			while(*tmppos)
			{
				if (*tmppos!=' ' && *tmppos!=0x8)
				{
					int cntr1=0;
					switch(*tmppos)
					{
					case ',': // next arg
						pPositions->ArgType=GP_ARGTYPE_NONE;
						pPositions->Start=tmppos-iValue;
						pPositions->End=tmppos-iValue;
						break;
					case ';': // next command
						break;
					case '@'://var
						if (tmppos[1]!='&' || !tmppos[2] || tmppos[2]=='<' || tmppos[2]=='[' || tmppos[2]=='"') continue;
						pPositions->ArgType=GP_ARGTYPE_VARIABLE;
						pPositions->Start=tmppos-iValue;
						pPositions->StartName=tmppos-iValue;
						tmppos++;
						tmppos++;
						while((*tmppos>='a' && *tmppos<='z') || (*tmppos>='A' && *tmppos<='z') || (*tmppos>='0' && *tmppos<='9') || *tmppos>='_' ) tmppos++;
						tmppos--;
						pPositions->EndName=tmppos-iValue;

						if ((tmppos[1]=='(' || tmppos[1]=='<' || tmppos[1]=='[' || tmppos[1]=='"'))
						{
							tmppos++;
							continue;
						}
						break;
					case '"':
						while(*(++tmppos) && *(tmppos)!='"');
						if (!*(tmppos)) tmppos--;
						pPositions->ArgType=GP_ARGTYPE_TEXT;
						pPositions->Start=tmppos-iValue;
						pPositions->End=tmppos-iValue;
						break;
					case '\'':
						while(*(++tmppos) && *(tmppos)!='\'');
						if (!*(tmppos)) tmppos--;
						pPositions->ArgType=GP_ARGTYPE_TEXT;
						pPositions->Start=tmppos-iValue;
						pPositions->End=tmppos-iValue;
						break;
					case '\\':
						break;
					case '(':
						pPositions->ArgType|=GP_ARGTYPE_BRACE;
						pPositions->StartBrace=tmppos-iValue;
						while(cntr1>=0 && *(++tmppos))
							if (*tmppos=='(') cntr1++;
							else
							if (*tmppos==')') cntr1--;

						pPositions->EndBrace=tmppos-iValue;
						if (*tmppos && (tmppos[1]=='<' || tmppos[1]=='[' || tmppos[1]=='"'))
						{
							tmppos++;
							continue;
						}
						break;
					case '<':
						pPositions->ArgType|=GP_ARGTYPE_DYNARRAY;
						pPositions->StartDAIndex=tmppos-iValue;
						while(cntr1>=0 && *(++tmppos))
							if (*tmppos=='<') cntr1++;
							else
							if (*tmppos=='>') cntr1--;

						pPositions->EndDAIndex=tmppos-iValue;
						if (*tmppos && (tmppos[1]=='[' || tmppos[1]=='"'))
						{
							tmppos++;
							continue;
						}
						break;
					case '[':
						pPositions->ArgType|=GP_ARGTYPE_EXTRACT;
						pPositions->StartSubstring=tmppos-iValue;
						while(cntr1>=0 && *(++tmppos))
							if (*tmppos=='[') cntr1++;
							else
							if (*tmppos==']') cntr1--;

						pPositions->EndSubstring=tmppos-iValue;
						if (*tmppos && tmppos[1]=='"')
						{
							tmppos++;
							continue;
						}
						break;
					case '-':
						pPositions->ArgType=GP_ARGTYPE_ARITHMMINUS;
						pPositions->Start=tmppos-iValue;
						if (tmppos[1]=='+') 
						{
							tmppos++;
							pPositions->ArgType=GP_ARGTYPE_MINUMINUS;
						}
						pPositions->End=tmppos-iValue;
						break;
					case '+':
						pPositions->ArgType=GP_ARGTYPE_ARITHMPLUS;
						pPositions->Start=tmppos-iValue;
						if (tmppos[1]=='+') 
						{
							tmppos++;
							pPositions->ArgType=GP_ARGTYPE_PLUSPLUS;
						}
						pPositions->End=tmppos-iValue;
						break;
					case '*':
						pPositions->ArgType=GP_ARGTYPE_ARITHMMUL;
						pPositions->Start=tmppos-iValue;
						pPositions->End=tmppos-iValue;
						break;
					case '/':
						pPositions->ArgType=GP_ARGTYPE_ARITHMDIV;
						pPositions->Start=tmppos-iValue;
						pPositions->End=tmppos-iValue;
						break;
					default:
						if (*tmppos>='0' && *tmppos<='9')
						{
							pPositions->ArgType=GP_ARGTYPE_DECNUMBER;
							pPositions->Start=tmppos-iValue;
							if (*tmppos=='0') pPositions->ArgType=GP_ARGTYPE_OCTNUMBER;
							if (tmppos[1]=='x' || tmppos[1]=='X') 
							{
								pPositions->ArgType=GP_ARGTYPE_HEXNUMBER;
								tmppos+=2;
								while((*tmppos>='0' && *tmppos<='9') || (*tmppos>='a' && *tmppos<='f') || (*tmppos>='A' && *tmppos<='F')) tmppos++;
							}
							else
								while(*tmppos>='0' && *tmppos<='9') tmppos++;
							pPositions->End=tmppos-iValue-1;
							if (*tmppos=='[') continue;
						}
						else
						{
							tmppos++;
							continue;
						}
						break;
					}
					break;
				}
				else tmppos++;
			}
		}
		if (pPositions->End<pPositions->EndName)		pPositions->End=pPositions->EndName;
		if (pPositions->End<pPositions->EndDAIndex)		pPositions->End=pPositions->EndDAIndex;
		if (pPositions->End<pPositions->EndSubstring)	pPositions->End=pPositions->EndSubstring;
		if (pPositions->End<pPositions->EndFormat)		pPositions->End=pPositions->EndFormat;
		if (pPositions->End<pPositions->EndBrace)		pPositions->End=pPositions->EndBrace;
		if (pPositions->ArgType==GP_ARGTYPE_NONE)		pPositions->End=tmppos-iValue;
	}

	return tmppos-iValue+1;
}

PINDEXARR TranslateIndexes(const char *iNewValue, PINDEXARR oResult)
{
	if (oResult)
	{
		oResult->Index1=oResult->Index2=oResult->Index3=oResult->Index4=-7;
		if (iNewValue && *iNewValue)
		{
			// need ExtractScriptPart
			while(*iNewValue<'0' || *iNewValue>'9') iNewValue++;
			if (*iNewValue>='0' && *iNewValue<='9') oResult->Index1=atoi(iNewValue);
			while(*iNewValue && !strchr(",>]})",*iNewValue)) iNewValue++;
			if (*iNewValue==',')
			{
				iNewValue++;
				if (*iNewValue>='0' && *iNewValue<='9') oResult->Index2=atoi(iNewValue);
				while(*iNewValue && !strchr(",>]})",*iNewValue)) iNewValue++;
				if (*iNewValue==',') 
				{
					iNewValue++;
					if (*iNewValue>='0' && *iNewValue<='9') oResult->Index3=atoi(iNewValue);
					while(*iNewValue && !strchr(",>]})",*iNewValue)) iNewValue++;
					if (*iNewValue==',') 
					{
						iNewValue++;
						if (*iNewValue>='0' && *iNewValue<='9') oResult->Index4=atoi(iNewValue);
					}
				}
			}
		}
	}

	return oResult;
}

const char *FindField(const char * iStr, int FieldNum, const char * delim)
{
	const char *pos;
	int lendelim=(int)strlen(delim);
	int i;
	for(i=1;i<FieldNum;i++)
	{
		if ((pos=strstr(iStr,delim))==NULL)
			iStr="";
		else iStr=pos+lendelim;
	}

	return iStr;
}

const char *FindFieldEx(const char * iStr, int FieldNum, const char * delim)
{
	const char *pos;
	int lendelim=(int)strlen(delim);
	int i;
	for(i=1;i<FieldNum;i++)
	{
		pos=iStr;
		int nLevel=0;
		while(*pos && (nLevel || (!nLevel && strncmp(pos,delim,lendelim))))
		{
			if (*pos=='(') nLevel++;
			else
			if (*pos==')' && nLevel>0) nLevel--;
			pos++;
		}
		if (!*pos)	iStr="";
		else		iStr=pos+lendelim;
	}

	return iStr;
}


void qsRectYByNum(CRect *RectArr,UINT *NUMs, int left, int right)
{
	register int i,j;
	UINT x,y;

	i=left;
	j=right;
	x=NUMs[(left+right)/2];

	do
	{
		while((RectArr[NUMs[i]].top<RectArr[x].top || (RectArr[NUMs[i]].top==RectArr[x].top && RectArr[NUMs[i]].left<RectArr[x].left)) && i<right) i++;
		while((RectArr[x].top<RectArr[NUMs[j]].top || (RectArr[x].top==RectArr[NUMs[j]].top && RectArr[x].left<RectArr[NUMs[j]].left)) && j>left) j--;

		if (i<=j)
		{
			y=NUMs[i];		NUMs[i]=NUMs[j];		NUMs[j]=y;
			i++;			j--;
		}
	}while(i<=j);
	if(left<j) qsRectYByNum(RectArr,NUMs,left,j);
	if (i<right) qsRectYByNum(RectArr,NUMs,i,right);
}

void qsRectXByNum(CRect *RectArr,UINT *NUMs, int left, int right)
{
	register int i,j;
	UINT x,y;

	i=left;
	j=right;
	x=NUMs[(left+right)/2];

	do
	{
		while((RectArr[NUMs[i]].left<RectArr[x].left || (RectArr[NUMs[i]].left==RectArr[x].left && RectArr[NUMs[i]].top<RectArr[x].top)) && i<right) i++;
		while((RectArr[x].left<RectArr[NUMs[j]].left || (RectArr[x].left==RectArr[NUMs[j]].left && RectArr[x].top<RectArr[NUMs[j]].top)) && j>left) j--;

		if (i<=j)
		{
			y=NUMs[i];		NUMs[i]=NUMs[j];		NUMs[j]=y;
			i++;			j--;
		}
	}while(i<=j);
	if(left<j) qsRectXByNum(RectArr,NUMs,left,j);
	if (i<right) qsRectXByNum(RectArr,NUMs,i,right);
}

UINT StringToArray(CString &iStr, VARIANT FAR* vArray, CString &DelimeterStr,VARTYPE arrType, UINT type=0)
{
	SAFEARRAY FAR* psa = NULL;

	USES_CONVERSION;
	SAFEARRAYBOUND tmpSAB={0};

//	HRESULT hr;
	long nElements;
	int i=0,ix,DelimLen=DelimeterStr.GetLength();

	for(nElements=1; (i=iStr.Find(DelimeterStr,i))>=0; i+=DelimLen,nElements++);

	tmpSAB.cElements=nElements;

	if ((V_VT(vArray)&VT_ARRAY) == VT_ARRAY )
	{
		psa = V_ARRAY(vArray);
		SafeArrayGetLBound(psa,1,&tmpSAB.lLbound);
		SafeArrayDestroy(psa);
	}

	VariantInit(vArray);

	try
	{
		COleSafeArray SAtmp;
		SAtmp.Create(arrType, 1,&tmpSAB.cElements);
		VariantCopy(vArray,SAtmp);
//		SAtmp.Destroy();
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("common", "StringToArray","2545");
	}

	psa = V_ARRAY(vArray);
	// Check dimensions of the array.
	if (SafeArrayGetDim(psa) != 1)			AfxThrowOleDispatchException(1002,IDS_GPOLEEXEPTION1002);
	else
	{
		int nFirst=0,nLast;
		HRESULT hr;

		switch(arrType)
		{
		case VT_BSTR:
			{
				CString CStmp;
				BSTR HUGEP *pbstr;
				hr = SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
				if (FAILED(hr))		AfxThrowOleDispatchException(1001,IDS_GPOLEEXEPTION1001);

				for(ix=0; ix<nElements; ix++)
				{
					nLast=iStr.Find(DelimeterStr,nFirst);
					if (nLast<0)
					{
						nLast=iStr.GetLength()-nFirst;
						CStmp=nLast>0?iStr.Right(iStr.GetLength()-nFirst):"";
					}
					else
					if (nLast==nFirst)	CStmp="";
					else				CStmp=iStr.Mid(nFirst,nLast-nFirst);

					CStmp.SetSysString(&pbstr[ix]);
					nFirst=nLast+DelimLen;
				}
				SafeArrayUnaccessData(psa);
			}
			break;
		case VT_I1:
		case VT_UI1:
			{
				CHAR HUGEP *pbarr;
				hr = SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbarr);
				if (FAILED(hr))		AfxThrowOleDispatchException(1001,IDS_GPOLEEXEPTION1001);
				const char *pos=iStr;
				const char *delim=DelimeterStr;

				switch(type)
				{
				case 0: /* decimal*/
					for(ix=0; ix<nElements; ix++)
						if (pos)
						{
							pbarr[ix]=(char)atoi(pos);
							if (DelimLen)
							{
								pos=strstr(pos,delim);
								if (pos) pos+=DelimLen;
							}
							else pos++;
						}
					break;
				case 1: /* hex*/
					for(ix=0; ix<nElements; ix++)
						if (pos)
						{
							int c=*pos-'0';
							if (*pos<='9')	c=(*pos-'0')*0x10;
							else			c=(*pos-'A'+0x8)*0x10;
							if (*(++pos)<='9')	c=*pos-'0';
							else				c=*pos-'A'+0x8;

							pbarr[ix]=(char)c;
							if (DelimLen)
							{
								pos=strstr(pos,delim);
								if (pos) pos+=DelimLen;
							}
							else pos++;
						}
					break;
				case 2: /* char*/
					for(ix=0; ix<nElements; ix++)
						if (pos)
						{
							pbarr[ix]=*pos;
							if (DelimLen)
							{
								pos=strstr(pos,delim);
								if (pos) pos+=DelimLen;
							}
							else pos++;
						}
					break;
				}
				SafeArrayUnaccessData(psa);
			}
			break;
		}
	}
	return nElements;
}

char * GetHexStr(char *oStr, BYTE *Arr, UINT Len)
{
	char mask[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',};
	char *ret=oStr;
	if (oStr && Arr && Len)
	{
		while(Len--)
		{
			*(oStr++)=mask[(*Arr)/16];
			*(oStr++)=mask[(*(Arr++))&0x0F];
		}
		*oStr=0;
	}

	return ret;
}

char * GetOctStr(char *oStr, BYTE *Arr, UINT Len)
{
	char mask[16]={'0','1','2','3','4','5','6','7',};
	char *ret=oStr;
	if (oStr && Arr && Len)
	{
		while(Len--)
		{
			*(oStr++)=mask[(*Arr)/64];
			*(oStr++)=mask[((*Arr)/8)&0x07];
			*(oStr++)=mask[(*(Arr++))&0x07];
		}
		*oStr=0;
	}

	return ret;
}

char * GetDecStr(char *oStr, BYTE *Arr, UINT Len)
{
	char *ret=oStr;
	if (oStr && Arr && Len)
	{
		while(Len--)
		{
			int c=*(Arr++);
			*(oStr++)=(char)('0'+c/100);
			*(oStr++)=(char)('0'+((c/10)%10));
			*(oStr++)=(char)('0'+(c%10));
		}
		*oStr=0;
	}
	return ret;
}

char * GetDblStr(char *oStr, char *oStr2, BYTE *Arr, UINT Len)
{
	char *ret=oStr;
	int c;
	if (oStr && oStr2 && Arr && Len)
	{
		while(Len--)
		{
			if ((c=*(Arr++))>0xFB || c==0x7F)
			{
				*(oStr++)=(char)(c-0x20);
				*(oStr2++)='1';
			}
			else
				if (c<0x20)
				{
					*(oStr++)=(char)(c+0x20);
					*(oStr2++)='2';
				}
				else
					{
						*(oStr++)=(char)c;
						*(oStr2++)='0';
					}
		}
		*oStr=0;
		*oStr2=0;
	}
	return ret;
}

BYTE * GetDblArr(BYTE *Arr, const char *oStr, const char *oStr2)
{
	BYTE *ret=Arr;
	if (Arr && oStr--)
	{
		if (oStr2--)
			while(*(++oStr) && *(++oStr2))
			{
				if (*oStr2=='0')
					*(Arr++)=*oStr;
					else
				if (*oStr2=='1')
					*(Arr++)=(BYTE)(*oStr+0x20);
					else
				if (*oStr2=='2')
					*(Arr++)=(BYTE)(*oStr-0x20);
			}
		else
			while(*(Arr++)=*(++oStr));

	}
	return ret;
}

BYTE * GetDecArr(BYTE *Arr, const char *oStr)
{
	BYTE *ret=Arr;
	if (Arr && oStr)
		while(*(oStr))
		{
			*Arr=(BYTE)((*(oStr++)-'0')*100);
			if (*oStr) *Arr=(BYTE)(*Arr+(*(oStr++)-'0')*10);
			if (*oStr) *Arr=(BYTE)(*Arr+*(oStr++)-'0');
			Arr++;
		}
	return ret;
}

BYTE * GetOctArr(BYTE *Arr, const char *oStr)
{
	BYTE *ret=Arr;
	if (Arr && oStr)
		while(*(oStr))
		{
			*Arr=(BYTE)((*(oStr++)-'0')*64);
			if (*oStr) *Arr=(BYTE)(*Arr+(*(oStr++)-'0')*8);
			if (*oStr) *Arr=(BYTE)(*Arr+*(oStr++)-'0');
			Arr++;
		}
	return ret;
}

BYTE * GetHexArr(BYTE *Arr, const char *oStr)
{
	BYTE *ret=Arr;
	BYTE tmp1;
	BYTE tmp2;
	if (Arr && oStr)
		while(*(oStr) && oStr[1])
		{
			if ((tmp1=*(oStr++))>'9')
			{
				if ((tmp2=*(oStr++))>'9')
					*(Arr++)=(BYTE)((tmp1-'A'+10)*0x10+tmp2-'A'+10);
				else
					*(Arr++)=(BYTE)((tmp1-'A'+10)*0x10+tmp2-'0');
			}
			else
				if ((tmp2=*(oStr++))>'9')
					*(Arr++)=(BYTE)((tmp1-'0')*0x10+tmp2-'A'+10);
				else
					*(Arr++)=(BYTE)((tmp1-'0')*0x10+tmp2-'0');
		}
	return ret;
}

BYTE * convHexToByteArr(const char *iDataSrc, BYTE *ArrDataDst)
{
	BYTE *dest=ArrDataDst;
	const char *src=iDataSrc;
	int cc;

	while(*src)
	{
		cc=*(src++);
		if (cc>='0' && cc<='9') *dest=(char)((cc-'0')*16);
		else
		if (cc>='A' && cc<='F') *dest=(char)((cc-'A'+10)*16);
		else
		if (cc>='a' && cc<='f') *dest=(char)((cc-'a'+10)*16);
		else			{*dest=(char)cc; continue;}

		if (*src)
		{
			cc=*(src++);
			if (cc>='0' && cc<='9') *dest=(char)(*dest+(char)(cc-'0'));
			else
			if (cc>='A' && cc<='F') *dest=(char)(*dest+(char)(cc-'A'+10));
			else
			if (cc>='a' && cc<='f') *dest=(char)(*dest+(char)(cc-'a'+10));
			src++;
		}
	}
	return ArrDataDst;
}

DWORD StringFromToWindowStyles(const char *iWindowStyles, DWORD & convWindowStyles)
{
	if (*iWindowStyles)
	{
		char *tmps=new char [(int)strlen(iWindowStyles)+100];
		strcpy(tmps,iWindowStyles);
		_strupr(tmps);
		convWindowStyles=atoi(tmps);
		UINT i;
		for(i=0;i<N_WND_STYLES;i++)
			if (strstr(tmps,aWndStyleName[i]))
				convWindowStyles|=aWndStyleUINT[i];
		delete[] tmps;
	}
	else
	{
		UINT convSD=convWindowStyles;
		UINT i;
		for(i=0;i<N_WND_STYLES;i++)
			if ((convSD&aWndStyleUINT[i])==aWndStyleUINT[i])
			{
				strcat((char *)iWindowStyles,aWndStyleName[i]);
				convSD^=aWndStyleUINT[i];
			}
			if (convSD) sprintf((char *)iWindowStyles+(int)strlen(iWindowStyles),"%s%d",*iWindowStyles?"|":"",convSD);
	}

	return convWindowStyles;
}

DWORD StringFromToWindowStylesEx(const char *iWindowStylesEx, DWORD & convWindowStylesEx)
{
	if (*iWindowStylesEx)
	{
		char *tmps=new char [(int)strlen(iWindowStylesEx)+100];
		strcpy(tmps,iWindowStylesEx);
		_strupr(tmps);
		convWindowStylesEx=atoi(tmps);
		UINT i;
		for(i=0;i<N_WND_EX_STYLES;i++)
			if (strstr(tmps,aWndExStyleName[i]))
				convWindowStylesEx|=aWndExStyleUINT[i];
		delete[] tmps;
	}
	else
	{
		UINT convSD=convWindowStylesEx;
		UINT i;
		for(i=0;i<N_WND_EX_STYLES;i++)
			if ((convSD&aWndExStyleUINT[i])==aWndExStyleUINT[i])
			{
				strcat((char *)iWindowStylesEx,aWndExStyleName[i]);
				convSD^=aWndExStyleUINT[i];
			}
			if (convSD) sprintf((char *)iWindowStylesEx+(int)strlen(iWindowStylesEx),"%s%d",*iWindowStylesEx?"|":"",convSD);
	}

	return convWindowStylesEx;
}

char *fgetsEx(char * iStr, int nchar, FILE *fl)
{
	char *ret=NULL;
	if (fl && iStr)
	{
		ret=fgets(iStr,nchar,fl);
		if (ret)
		{
			char *pos=iStr;
			while(*pos)
				if (*pos==13 || *pos==10) *pos=0;
				else pos++;
		}
	}

	return ret;
}

char * RemoveCharFromString(char *iStr, char iChar)
{
	if (iStr && *iStr)
	{
		char *iStr2=iStr;
		char *postmp=iStr2--;

		while(*(++iStr2))
			if (*iStr2!=iChar) *(postmp++)=*iStr2;

		*(postmp)=0;
	}
	return iStr;
}


HRESULT ModifyPrivilege(LPCTSTR szPrivilege,BOOL fEnable)
{
    HRESULT hr = S_OK;
    TOKEN_PRIVILEGES NewState;
    LUID             luid;
    HANDLE hToken    = NULL;

    // Open the process token for this process.
    if (!OpenProcessToken(GetCurrentProcess(),
                          TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
                          &hToken ))
    {
        printf("Failed OpenProcessToken\n");
        return ERROR_FUNCTION_FAILED;
    }

    // Get the local unique id for the privilege.
    if ( !LookupPrivilegeValue( NULL,
                                szPrivilege,
                                &luid ))
    {
        CloseHandle( hToken );
        printf("Failed LookupPrivilegeValue\n");
        return ERROR_FUNCTION_FAILED;
    }

    // Assign values to the TOKEN_PRIVILEGE structure.
    NewState.PrivilegeCount = 1;
    NewState.Privileges[0].Luid = luid;
    NewState.Privileges[0].Attributes = 
              (fEnable ? SE_PRIVILEGE_ENABLED : 0);

    // Adjust the token privilege.
    if (!AdjustTokenPrivileges(hToken,
                               FALSE,
                               &NewState,
                               sizeof(NewState),
                               NULL,
                               NULL))
    {
        printf("Failed AdjustTokenPrivileges\n");
        hr = ERROR_FUNCTION_FAILED;
    }

    CloseHandle(hToken);

    return hr;
}

DWORD ExportRegistryKey(const char *ccRegKeyName, const char *ccFileName)
{
	ModifyPrivilege(SE_BACKUP_NAME, TRUE);
	ModifyPrivilege(SE_RESTORE_NAME , TRUE);

	DWORD ret=0;
	HKEY tmpKew=NULL;
	ret=::RegOpenKeyEx(HKEY_CURRENT_USER,ccRegKeyName,0,KEY_ALL_ACCESS,&tmpKew);
	//FormatMessage(  FORMAT_MESSAGE_FROM_SYSTEM, (const void *)FORMAT_MESSAGE_FROM_HMODULE, dwDisp, 0, ccc, 2000, NULL);
	if (tmpKew)
	{
		DeleteFile(ccFileName);
		ret=RegSaveKey(tmpKew,ccFileName,NULL);
		RegCloseKey(tmpKew);
	}
	return ret;
}

DWORD ImportRegistryKey(const char *ccRegKeyName, const char *ccFileName)
{
	DWORD ret=0;
	HKEY tmpKew=NULL;

	ModifyPrivilege(SE_BACKUP_NAME, TRUE);
	ModifyPrivilege(SE_RESTORE_NAME , TRUE);

	RegCreateKeyEx(HKEY_CURRENT_USER,ccRegKeyName,0,NULL,REG_OPTION_BACKUP_RESTORE,KEY_ALL_ACCESS,NULL,&tmpKew,&ret);
	if (tmpKew)
	{
		ret=::RegRestoreKey(tmpKew,ccFileName,REG_FORCE_RESTORE);
		RegCloseKey(tmpKew);
	}
	return ret;
}

char *DelimitersDown(char *iStr)
{
	char *posout=iStr;
	while(*posout) 
	{
		if (*posout==127) *posout=1;
		else
		if (*posout==1) *posout=2;
		else
		if (*posout==2) *posout=3;
		else
		if (*posout==3) *posout=4;
		else
		if (*posout==4) *posout=5;
		else
		if (*posout==5) *posout=6;
		else
		if (*posout==7) *posout=2;
		posout++;
	}
	return posout;
}

int DEVMODEToString(PDEVMODE ipDM, char *oStr)
{
	int j;
	char *inits=oStr;
	oStr+=sprintf(oStr,"%s\x7F%X\x7F%d\x7F%d\x7F%d\x7F%8.8X\x7",ipDM->dmDeviceName,ipDM->dmSpecVersion,ipDM->dmDriverVersion,ipDM->dmSize,ipDM->dmDriverExtra,ipDM->dmFields);

	DWORD adwFieldsAtt[]={
		DM_ORIENTATION,DM_PAPERSIZE,DM_PAPERLENGTH,DM_PAPERWIDTH,DM_SCALE,
		DM_POSITION,DM_NUP,DM_DISPLAYORIENTATION,DM_COPIES,DM_DEFAULTSOURCE,
		DM_PRINTQUALITY,DM_COLOR,DM_DUPLEX,DM_YRESOLUTION,DM_TTOPTION,
		DM_COLLATE,DM_FORMNAME,DM_LOGPIXELS,DM_BITSPERPEL,DM_PELSWIDTH,
		DM_PELSHEIGHT,DM_DISPLAYFLAGS,DM_DISPLAYFREQUENCY,DM_ICMMETHOD,DM_ICMINTENT,
		DM_MEDIATYPE,DM_DITHERTYPE,DM_PANNINGWIDTH,DM_PANNINGHEIGHT,DM_DISPLAYFIXEDOUTPUT,
	};	
	char *acFieldsAtt[]={
		"DM_ORIENTATION","DM_PAPERSIZE","DM_PAPERLENGTH","DM_PAPERWIDTH","DM_SCALE",
		"DM_POSITION","DM_NUP","DM_DISPLAYORIENTATION","DM_COPIES","DM_DEFAULTSOURCE",
		"DM_PRINTQUALITY","DM_COLOR","DM_DUPLEX","DM_YRESOLUTION","DM_TTOPTION",
		"DM_COLLATE","DM_FORMNAME","DM_LOGPIXELS","DM_BITSPERPEL","DM_PELSWIDTH",
		"DM_PELSHEIGHT","DM_DISPLAYFLAGS","DM_DISPLAYFREQUENCY","DM_ICMMETHOD","DM_ICMINTENT",
		"DM_MEDIATYPE","DM_DITHERTYPE","DM_PANNINGWIDTH","DM_PANNINGHEIGHT","DM_DISPLAYFIXEDOUTPUT",
	};	

	for(*oStr=0,j=0;j<30;j++)
		if ((ipDM->dmFields&adwFieldsAtt[j])==adwFieldsAtt[j])
		{
			if (*oStr) strcat(oStr++,"|");
			strcat(oStr,acFieldsAtt[j]);
		}
	while(*oStr) oStr++;


	short adwPaperSizeAtt[]={
		DMPAPER_LETTER,DMPAPER_LETTERSMALL,DMPAPER_TABLOID,DMPAPER_LEDGER,DMPAPER_LEGAL,
		DMPAPER_STATEMENT,DMPAPER_EXECUTIVE,DMPAPER_A3,DMPAPER_A4,DMPAPER_A4SMALL,
		DMPAPER_A5,DMPAPER_B4,DMPAPER_B5,DMPAPER_FOLIO,DMPAPER_QUARTO,
		DMPAPER_10X14,DMPAPER_11X17,DMPAPER_NOTE,DMPAPER_ENV_9,DMPAPER_ENV_10,
		DMPAPER_ENV_11,DMPAPER_ENV_12,DMPAPER_ENV_14,DMPAPER_CSHEET,DMPAPER_DSHEET,
		DMPAPER_ESHEET,DMPAPER_ENV_DL,DMPAPER_ENV_C5,DMPAPER_ENV_C3,DMPAPER_ENV_C4,
		DMPAPER_ENV_C6,DMPAPER_ENV_C65,DMPAPER_ENV_B4,DMPAPER_ENV_B5,DMPAPER_ENV_B6,
		DMPAPER_ENV_ITALY,DMPAPER_ENV_MONARCH,DMPAPER_ENV_PERSONAL,DMPAPER_FANFOLD_US,DMPAPER_FANFOLD_STD_GERMAN,
		DMPAPER_FANFOLD_LGL_GERMAN,DMPAPER_ISO_B4,DMPAPER_JAPANESE_POSTCARD,DMPAPER_9X11,DMPAPER_10X11,
		DMPAPER_15X11,DMPAPER_ENV_INVITE,DMPAPER_RESERVED_48,DMPAPER_RESERVED_49,DMPAPER_LETTER_EXTRA,
		DMPAPER_LEGAL_EXTRA,DMPAPER_TABLOID_EXTRA,DMPAPER_A4_EXTRA,DMPAPER_LETTER_TRANSVERSE,DMPAPER_A4_TRANSVERSE,
		DMPAPER_LETTER_EXTRA_TRANSVERSE,DMPAPER_A_PLUS,DMPAPER_B_PLUS,DMPAPER_LETTER_PLUS,DMPAPER_A4_PLUS,
		DMPAPER_A5_TRANSVERSE,DMPAPER_B5_TRANSVERSE,DMPAPER_A3_EXTRA,DMPAPER_A5_EXTRA,DMPAPER_B5_EXTRA,
		DMPAPER_A2,DMPAPER_A3_TRANSVERSE,DMPAPER_A3_EXTRA_TRANSVERSE,DMPAPER_DBL_JAPANESE_POSTCARD,DMPAPER_A6,
		DMPAPER_JENV_KAKU2,DMPAPER_JENV_KAKU3,DMPAPER_JENV_CHOU3,DMPAPER_JENV_CHOU4,DMPAPER_LETTER_ROTATED,
		DMPAPER_A3_ROTATED,DMPAPER_A4_ROTATED,DMPAPER_A5_ROTATED,DMPAPER_B4_JIS_ROTATED,DMPAPER_B5_JIS_ROTATED,
		DMPAPER_JAPANESE_POSTCARD_ROTATED,DMPAPER_DBL_JAPANESE_POSTCARD_ROTATED,DMPAPER_A6_ROTATED,DMPAPER_JENV_KAKU2_ROTATED,DMPAPER_JENV_KAKU3_ROTATED,
		DMPAPER_JENV_CHOU3_ROTATED,DMPAPER_JENV_CHOU4_ROTATED,DMPAPER_B6_JIS,DMPAPER_B6_JIS_ROTATED,DMPAPER_12X11,
		DMPAPER_JENV_YOU4,DMPAPER_JENV_YOU4_ROTATED,DMPAPER_P16K,DMPAPER_P32K,DMPAPER_P32KBIG,
		DMPAPER_PENV_1,DMPAPER_PENV_2,DMPAPER_PENV_3,DMPAPER_PENV_4,DMPAPER_PENV_5,
		DMPAPER_PENV_6,DMPAPER_PENV_7,DMPAPER_PENV_8,DMPAPER_PENV_9,DMPAPER_PENV_10,
		DMPAPER_P16K_ROTATED,DMPAPER_P32K_ROTATED,DMPAPER_P32KBIG_ROTATED,DMPAPER_PENV_1_ROTATED,DMPAPER_PENV_2_ROTATED,
		DMPAPER_PENV_3_ROTATED,DMPAPER_PENV_4_ROTATED,DMPAPER_PENV_5_ROTATED,DMPAPER_PENV_6_ROTATED,DMPAPER_PENV_7_ROTATED,
		DMPAPER_PENV_8_ROTATED,DMPAPER_PENV_9_ROTATED,DMPAPER_PENV_10_ROTATED,DMPAPER_USER,
	};	
	char *acPaperSizeAtt[]={
		"LETTER","LETTERSMALL","TABLOID","LEDGER","LEGAL",
		"STATEMENT","EXECUTIVE","A3","A4","A4SMALL",
		"A5","B4","B5","FOLIO","QUARTO",
		"10X14","11X17","NOTE","ENV_9","ENV_10",
		"ENV_11","ENV_12","ENV_14","CSHEET","DSHEET",
		"ESHEET","ENV_DL","ENV_C5","ENV_C3","ENV_C4",
		"ENV_C6","ENV_C65","ENV_B4","ENV_B5","ENV_B6",
		"ENV_ITALY","ENV_MONARCH","ENV_PERSONAL","FANFOLD_US","FANFOLD_STD_GERMAN",
		"FANFOLD_LGL_GERMAN","ISO_B4","JAPANESE_POSTCARD","9X11","10X11",
		"15X11","ENV_INVITE","RESERVED_48","RESERVED_49","LETTER_EXTRA",
		"LEGAL_EXTRA","TABLOID_EXTRA","A4_EXTRA","LETTER_TRANSVERSE","A4_TRANSVERSE",
		"LETTER_EXTRA_TRANSVERSE","A_PLUS","B_PLUS","LETTER_PLUS","A4_PLUS",
		"A5_TRANSVERSE","B5_TRANSVERSE","A3_EXTRA","A5_EXTRA","B5_EXTRA",
		"A2","A3_TRANSVERSE","A3_EXTRA_TRANSVERSE","DBL_JAPANESE_POSTCARD","A6",
		"JENV_KAKU2","JENV_KAKU3","JENV_CHOU3","JENV_CHOU4","LETTER_ROTATED",
		"A3_ROTATED","A4_ROTATED","A5_ROTATED","B4_JIS_ROTATED","B5_JIS_ROTATED",
		"JAPANESE_POSTCARD_ROTATED","DBL_JAPANESE_POSTCARD_ROTATED","A6_ROTATED","JENV_KAKU2_ROTATED","JENV_KAKU3_ROTATED",
		"JENV_CHOU3_ROTATED","JENV_CHOU4_ROTATED","B6_JIS","B6_JIS_ROTATED","12X11",
		"JENV_YOU4","JENV_YOU4_ROTATED","P16K","P32K","P32KBIG",
		"PENV_1","PENV_2","PENV_3","PENV_4","PENV_5",
		"PENV_6","PENV_7","PENV_8","PENV_9","PENV_10",
		"P16K_ROTATED","P32K_ROTATED","P32KBIG_ROTATED","PENV_1_ROTATED","PENV_2_ROTATED",
		"PENV_3_ROTATED","PENV_4_ROTATED","PENV_5_ROTATED","PENV_6_ROTATED","PENV_7_ROTATED",
		"PENV_8_ROTATED","PENV_9_ROTATED","PENV_10_ROTATED","USER",
	};	

	short adwOrientationAtt[]={DMORIENT_PORTRAIT,DMORIENT_LANDSCAPE,};	
	char *acOrientationAtt[]={"PORTRAIT","LANDSCAPE","UNKNOWN"};	

	for(j=0;j<2 && ipDM->dmOrientation!=adwOrientationAtt[j];j++);

	oStr+=sprintf(oStr,"\x7F%8.8X\x7%s\x7F%8.8X\x7",ipDM->dmOrientation,acOrientationAtt[j],ipDM->dmPaperSize);
	
	for(*oStr=0,j=0;j<119 && !*oStr;j++)
		if (ipDM->dmPaperSize==adwPaperSizeAtt[j])
			strcpy(oStr,acPaperSizeAtt[j]);
	while(*oStr) oStr++;

	oStr+=sprintf(oStr,"\x7F%d\x7F%d\x7F%d\x7F%d",ipDM->dmPaperLength,ipDM->dmPaperWidth,ipDM->dmScale,ipDM->dmCopies);
	char *acDefaultSourceAtt[]={"","ONLYONE","LOWER","MIDDLE","MANUAL","ENVELOPE","ENVMANUAL","AUTO","TRACTOR","SMALLFMT","LARGEFMT","LARGECAPACITY","UNKNOWN","UNKNOWN","CASSETTE","FORMSOURCE",};	
	oStr+=sprintf(oStr,"\x7F%8.8X\x7%s",ipDM->dmDefaultSource,(ipDM->dmDefaultSource>0 && ipDM->dmDefaultSource<16)?acDefaultSourceAtt[ipDM->dmDefaultSource]:(ipDM->dmDefaultSource==256)?"USER":"UNKNOWN");

	if (ipDM->dmPrintQuality<0 && ipDM->dmPrintQuality>-5)
	{
		char *acPrintQuality[]={"","DRAFT","LOW","MEDIUM","HIGH",};	
		oStr+=sprintf(oStr,"\x7F%s",acPrintQuality[-ipDM->dmPrintQuality]);
	}
	else	oStr+=sprintf(oStr,"\x7F%d",ipDM->dmPrintQuality);

	if (ipDM->dmColor==1 || ipDM->dmColor==2)		oStr+=sprintf(oStr,"\x7F%s",(ipDM->dmColor==1)?"MONOCHROME":"COLOR");
	else											oStr+=sprintf(oStr,"\x7F%d",ipDM->dmColor);

	if (ipDM->dmDuplex>0 && ipDM->dmDuplex<4)
	{
		char *acDuplex[]={"","SIMPLEX","VERTICAL","HORIZONTAL",};	
		oStr+=sprintf(oStr,"\x7F%s",acDuplex[ipDM->dmDuplex]);
	}
	else	oStr+=sprintf(oStr,"\x7F%d",ipDM->dmDuplex);

	oStr+=sprintf(oStr,"\x7F%d",ipDM->dmYResolution);

	if (ipDM->dmTTOption>0 && ipDM->dmTTOption<5)
	{
		char *acTTOption[]={"","BITMAP","DOWNLOAD","SUBDEV","DOWNLOAD_OUTLINE",};	
		oStr+=sprintf(oStr,"\x7F%s",acTTOption[ipDM->dmTTOption]);
	}
	else	oStr+=sprintf(oStr,"\x7F%d",ipDM->dmTTOption);
	
	oStr+=sprintf(oStr,"\x7F%d\x7F%s\x7F%d\x7F%d\x7F%d\x7F%d\x7F%X\x7F%X",
		ipDM->dmCollate,ipDM->dmFormName,ipDM->dmLogPixels,ipDM->dmBitsPerPel,
		ipDM->dmPelsWidth,ipDM->dmPelsHeight,ipDM->dmDisplayFlags,ipDM->dmDisplayFrequency
		);

	if ((ipDM->dmICMMethod>0 && ipDM->dmICMMethod<5) || ipDM->dmICMMethod==DMICMMETHOD_USER)
	{
		char *acICMMethod[]={"USER","NONE","SYSTEM","DRIVER","DEVICE",};	
		oStr+=sprintf(oStr,"\x7F%s",acICMMethod[ipDM->dmICMMethod==DMICMMETHOD_USER?0:ipDM->dmICMMethod]);
	}
	else	oStr+=sprintf(oStr,"\x7F%d",ipDM->dmICMMethod);

	if ((ipDM->dmICMIntent>0 && ipDM->dmICMIntent<5) || ipDM->dmICMIntent==DMICM_USER)
	{
		char *acICMIntent[]={"USER","SATURATE","CONTRAST","COLORIMETRIC","ABS_COLORIMETRIC",};	
		oStr+=sprintf(oStr,"\x7F%s",acICMIntent[ipDM->dmICMIntent==DMICM_USER?0:ipDM->dmICMIntent]);
	}
	else	oStr+=sprintf(oStr,"\x7F%d",ipDM->dmICMIntent);

	if ((ipDM->dmMediaType>0 && ipDM->dmMediaType<4) || ipDM->dmMediaType==DMMEDIA_USER)
	{
		char *acICMMediaType[]={"USER","STANDARD","TRANSPARENCY","GLOSSY",};	
		oStr+=sprintf(oStr,"\x7F%s",acICMMediaType[ipDM->dmMediaType==DMMEDIA_USER?0:ipDM->dmMediaType]);
	}
	else	oStr+=sprintf(oStr,"\x7F%d",ipDM->dmMediaType);

	if ((ipDM->dmDitherType>0 && ipDM->dmDitherType<11) || ipDM->dmDitherType==DMDITHER_USER)
	{
		char *acDitherType[]={"USER","NONE","COARSE","FINE","LINEART","ERRORDIFFUSION",
			"RESERVED6","RESERVED7","RESERVED8","RESERVED9","GRAYSCALE",};	
		oStr+=sprintf(oStr,"\x7F%s",acDitherType[ipDM->dmDitherType==DMDITHER_USER?0:ipDM->dmDitherType]);
	}
	else	oStr+=sprintf(oStr,"\x7F%d",ipDM->dmDitherType);

	oStr+=sprintf(oStr,"\x7F%d\x7F%d\x7F%d\x7F%d",
		ipDM->dmReserved1,ipDM->dmReserved2,ipDM->dmPanningWidth,ipDM->dmPanningHeight
		);

	return (int)strlen(oStr);
}

DWORD FindInSortArray(const char *ccFindWhat, const char **ccArray, DWORD dwItems)
{
	DWORD ret=dwItems;

	switch(dwItems)
	{
	case 1: if (strcmp(*ccArray,ccFindWhat)==0) ret=0;
	case 0: break;
	default:
		{
			int low=0,high=dwItems-1,mid;
			while(low<=high)
			{
				mid=(low+high)/2;
				if (strcmp(ccFindWhat,ccArray[mid])<0) high=mid-1;
				else 
					if (strcmp(ccFindWhat,ccArray[mid])>0) low=mid+1;
					else {ret=mid;break;}
			}
		}
	}
	return ret;
}

DWORD FindInSortArrayIC(const char *ccFindWhat, const char **ccArray, DWORD dwItems)
{
	DWORD ret=dwItems;

	switch(dwItems)
	{
	case 1: if (_stricmp(*ccArray,ccFindWhat)==0) ret=0;
	case 0: break;
	default:
		{
			int low=0,high=dwItems==0?0:dwItems-1,mid;
			while(low<=high)
			{
				mid=(low+high)/2;
				if (_stricmp(ccFindWhat,ccArray[mid])<0) high=mid-1;
				else 
					if (_stricmp(ccFindWhat,ccArray[mid])>0) low=mid+1;
					else {ret=mid;break;}
			}
		}
	}
	return ret;
}

char *DwordToStringValue(char cDelim, DWORD dwValue, char *cStr, DWORD *dwArray, const char **ccArray)
{
	int j;
	if (cDelim) *(cStr++)=cDelim;
	*cStr=0;
	for(j=0;*ccArray[j] && dwValue!=dwArray[j];j++);

	if (*ccArray[j])
	{
		strcat(cStr,ccArray[j]);
		while(*cStr) cStr++;
	}
	else if (dwValue) cStr+=sprintf(cStr,"%d",dwValue);


	return cStr;
}

char *DwordToStringMask(char cDelim, DWORD dwValue, char *cStr, DWORD *dwArray, const char **ccArray)
{
	int j;
	if (cDelim) *(cStr++)=cDelim;
	*cStr=0;

	for(j=0;*ccArray[j];j++)
		if ((dwValue&dwArray[j])==dwArray[j])
		{
			dwValue^=dwArray[j];
			if (*cStr) strcat(cStr,"|");
			strcat(cStr,ccArray[j]);
		}


	if (dwValue) 
	{
		if (*cStr) strcat(cStr,"|");
		while(*cStr) cStr++;
		cStr+=sprintf(cStr,"%d",dwValue);
	}

	while(*cStr) cStr++;
	return cStr;
}

DWORD StringToDword(const char *cStr, const char **ccArray, DWORD *dwArray)
{
	int i;
	const char *tmps;
	const char *tmps2;
	DWORD ret=0;

	while(*cStr)
	{
		if ((*cStr>='0' && *cStr<='9') || (*cStr=='&' && cStr[1]=='H'))
		{
			DWORD tmpdw=atoi(cStr);
			if ((*cStr=='0' && (cStr[1]=='x' || cStr[1]=='X')) || *cStr=='&')
				m_LastScanf=sscanf(cStr+2,"%x",&tmpdw);
			ret|=tmpdw;
		}

		for(i=0;*ccArray[i];i++)
		{
			tmps=cStr;
			tmps2=ccArray[i];
			while(*tmps==*tmps2 && ((*tmps>='A' && *tmps<='Z') || (*tmps>='a' && *tmps<='z') || *tmps=='_'))
				{tmps++;tmps2++;}
			if (!*tmps2) ret|=dwArray[i];
		}

		while((*cStr>='A' && *cStr<='Z') || (*cStr>='a' && *cStr<='z') || *cStr=='_') cStr++;
		if (*cStr) cStr++;
	}
	return ret;
}

char *FindFile(const char *ccFileName, char **oStr, DWORD dwAttributes, DWORD dwDateType, CTime &MinTime, CTime &MaxTime, int nMaxBytes)
{
	//,,,,500;c:\AP\*.txt
	if (!dwAttributes) dwAttributes=0xFFFF;

	CFileFind ff;
	BOOL bFind=ff.FindFile(ccFileName,0);
	UINT ret=0;
	CTime LATime,CRTime,LWTime;
	if (bFind)
	{
		int curArrLen=0;
		int maxArrLen=10000;
		char *tmps=new char [5000];
		*oStr=new char [maxArrLen];
		**oStr=*tmps=0;
		char *cReadBytes=NULL;
		try
		{
			if (nMaxBytes>0) cReadBytes=new char [nMaxBytes*3+32];
			do
			{
				char *outpos=tmps;
				ret=ff.FindNextFile();
				DWORD dwMask=0;
				if (cReadBytes) *cReadBytes=0;

				if (ff.IsReadOnly())	dwMask|=0x00000001; else dwMask|=0x00000002;
				if (ff.IsDirectory())	dwMask|=0x00000004; else dwMask|=0x00000008;
				if (ff.IsCompressed())	dwMask|=0x00000010; else dwMask|=0x00000020;
				if (ff.IsSystem())		dwMask|=0x00000040; else dwMask|=0x00000080;
				if (ff.IsHidden())		dwMask|=0x00000100; else dwMask|=0x00000200;
				if (ff.IsTemporary())	dwMask|=0x00000400; else dwMask|=0x00000800;
				if (ff.IsNormal())		dwMask|=0x00001000; else dwMask|=0x00002000;
				if (ff.IsArchived())	dwMask|=0x00004000; else dwMask|=0x00008000;

				dwMask=(dwAttributes&dwMask);
				if ((((dwMask/2)|dwMask)&0x5555)==0x5555)
				{
					ff.GetCreationTime(CRTime);
					ff.GetLastWriteTime(LWTime);
					ff.GetLastAccessTime(LATime);
					if ((!(dwDateType&1) || (CRTime>=MinTime && CRTime<=MaxTime)) &&
					   (!(dwDateType&2) || (LWTime>=MinTime && LWTime<=MaxTime)) &&
					   (!(dwDateType&4) || (LATime>=MinTime && LATime<=MaxTime)))
					{
						if (**oStr)  *(outpos++)=0x7F;
						outpos+=sprintf(outpos,"%s\x7%s\x7%I64d\x7%I64d\x7%2.2d\x7%2.2d\x7%2.2d\x7%2.2d\x7%2.2d\x7%4.4d\x7%I64d\x7%2.2d\x7%2.2d\x7%2.2d\x7%2.2d\x7%2.2d\x7%4.4d\x7%I64d\x7%2.2d\x7%2.2d\x7%2.2d\x7%2.2d\x7%2.2d\x7%4.4d\x7%d\x7%d\x7%d\x7%d\x7%d\x7%d\x7%d\x7%d\x7",
								(LPCSTR)ff.GetRoot(),
								(LPCSTR)ff.GetFileName(),
								ff.GetLength() ,
								CRTime.GetTime(), CRTime.GetSecond(), CRTime.GetMinute(), CRTime.GetHour(), CRTime.GetDay(), CRTime.GetMonth(),CRTime.GetYear(),
								LWTime.GetTime(), LWTime.GetSecond(), LWTime.GetMinute(), LWTime.GetHour(), LWTime.GetDay(), LWTime.GetMonth(),LWTime.GetYear(),
								LATime.GetTime(), LATime.GetSecond(), LATime.GetMinute(), LATime.GetHour(), LATime.GetDay(), LATime.GetMonth(),LATime.GetYear(),
								ff.IsReadOnly() , ff.IsDirectory ( ), ff.IsCompressed( ), ff.IsSystem( ),   ff.IsHidden( ),  ff.IsTemporary( ),ff.IsNormal( ),ff.IsArchived( ));

						curArrLen+=outpos-tmps;
						if (cReadBytes && !ff.IsDirectory())
						{
							int nBytesToRead=nMaxBytes;
							FILE *tmpFile=fopen(ff.GetFilePath(),"rt");
							if (tmpFile)
							{
								char *tmppos=cReadBytes;
								char *tmppostoRead=cReadBytes+nMaxBytes*2;
								while(nBytesToRead>0 && fgets(tmppostoRead,nBytesToRead+1,tmpFile))
								{
									if (tmppos!=cReadBytes)		{*(tmppos)++=3;tmppos++;nBytesToRead--;}
									char *tmppos2=tmppostoRead;
									while((*tmppos=*tmppos2))
									{
										if (*tmppos>0 && *tmppos<4) *tmppos+=3;
										else
										if (*tmppos==7) *tmppos=3;
										else
										if (*tmppos==GPC.BreakChar) *tmppos=6;
										else
										if (*tmppos==0x7F) *tmppos=11;
										tmppos++;tmppos2++;
										nBytesToRead--;
									}
								}
								fclose(tmpFile);
								curArrLen+=(tmppos-cReadBytes)+1;
							}
						}

						if (curArrLen+100>maxArrLen)
						{
							maxArrLen+=(maxArrLen/4);
							char *tmparr=new char [maxArrLen];
							strcpy(tmparr,*oStr);
							delete [] *oStr;
							*oStr=tmparr;
						}
						strcat(*oStr,tmps);
						if (cReadBytes && *cReadBytes) strcat(*oStr,cReadBytes);
					}
				}
			}while(ret);
		}
		catch(...){;}
		if (cReadBytes) delete [] cReadBytes;
		cReadBytes=NULL;
		delete [] tmps;
		tmps=NULL;
		ff.Close();
	}

	return *oStr;
}


char *FindFileRecursive(const char *ccFileName, char **oStr, DWORD dwAttributes, DWORD dwDateType, CTime &MinTime, CTime &MaxTime, int nMaxBytes)
{
	if (!dwAttributes) dwAttributes=0xFFFF;
	char *cPath=new char [(int)strlen(ccFileName)+1100];
	strcpy(cPath,ccFileName);
	char *postmp=cPath;
	char *posFName=cPath;

	while(*postmp)
	{
		if (*postmp=='/') *postmp='\\';
		postmp++;
	}

	postmp=cPath;
	while(*postmp) if (*(postmp++)=='\\') posFName=postmp;

	strcpy(cPath+1000,posFName);
	if (posFName!=cPath) posFName--;
	*(posFName++)='\\';
	*(posFName++)='*';
	*posFName=0;
	posFName=cPath+1000;

	FindFile(ccFileName,oStr, dwAttributes, dwDateType, MinTime, MaxTime, nMaxBytes);
	if (!*oStr)
	{
		*oStr=new char [100];
		**oStr=0;
	}

	CFileFind ff;
	BOOL bFind=ff.FindFile(cPath,0);
	UINT ret=0;
	if (bFind)
	{
		int curArrLen=(int)strlen(*oStr);
		do
		{
			ret=ff.FindNextFile();
			if (ff.IsDirectory() && ff.GetFileName()!="." && ff.GetFileName()!="..")	
			{
				char *tmpoStr=NULL;
				CString tmpP=ff.GetFilePath()+"\\";
				tmpP+=posFName;
				FindFileRecursive(tmpP,&tmpoStr, dwAttributes, dwDateType, MinTime, MaxTime, nMaxBytes);
				if (tmpoStr)
				{
					if (*tmpoStr)
					{
						if (curArrLen) strcpy(*oStr+curArrLen++,"\x7F");
						int iLenTmp=(int)strlen(tmpoStr);
						char *tmpArr=new char [curArrLen+iLenTmp+10];
						strcpy(tmpArr,*oStr);
						strcpy(tmpArr+curArrLen,tmpoStr);
						curArrLen+=iLenTmp;
						delete [] *oStr;
						*oStr=tmpArr;
					}
					delete [] tmpoStr;
				}
			}
		}while(ret);
		ff.Close();
	}
	delete [] cPath;

	return *oStr;
}

char *FindImages(const char *ccFileName, char **oStr, DWORD dwAttributes, DWORD dwDateType, CTime &MinTime, CTime &MaxTime, const char *ccILName, int inImage)
{
	if (!dwAttributes) dwAttributes=(0xFFFF^0x0004);
	if ((dwAttributes&0x0004)) dwAttributes^=0x0004;

	CFileFind ff;
	BOOL bFind=ff.FindFile(ccFileName,0);
	UINT ret=0;
	CTime LATime,CRTime,LWTime;
	if (bFind)
	{
		int curArrLen=0;
		int maxArrLen=10000;
		char *tmps=new char [20000];
		*oStr=new char [maxArrLen];
		try
		{
			**oStr=0;
			do
			{
				char *outpos=tmps;
				ret=ff.FindNextFile();
				DWORD dwMask=0;

				if (ff.IsReadOnly())	dwMask|=0x00000001; else dwMask|=0x00000002;
				if (ff.IsDirectory())	dwMask|=0x00000004; else dwMask|=0x00000008;
				if (ff.IsCompressed())	dwMask|=0x00000010; else dwMask|=0x00000020;
				if (ff.IsSystem())		dwMask|=0x00000040; else dwMask|=0x00000080;
				if (ff.IsHidden())		dwMask|=0x00000100; else dwMask|=0x00000200;
				if (ff.IsTemporary())	dwMask|=0x00000400; else dwMask|=0x00000800;
				if (ff.IsNormal())		dwMask|=0x00001000; else dwMask|=0x00002000;
				if (ff.IsArchived())	dwMask|=0x00004000; else dwMask|=0x00008000;

				dwMask=(dwAttributes&dwMask);
				if ((((dwMask/2)|dwMask)&0x5555)==0x5555)
				{
					ff.GetCreationTime(CRTime);
					ff.GetLastWriteTime(LWTime);
					ff.GetLastAccessTime(LATime);
					if ((!(dwDateType&1) || (CRTime>=MinTime && CRTime<=MaxTime)) &&
					   (!(dwDateType&2) || (LWTime>=MinTime && LWTime<=MaxTime)) &&
					   (!(dwDateType&4) || (LATime>=MinTime && LATime<=MaxTime)))
					{
						if (**oStr)  *(outpos++)=0x7F;
						char *cImgOutPos=outpos+sprintf(outpos,"%s\x7%s\x7%I64d\x7%I64d\x7%2.2d\x7%2.2d\x7%2.2d\x7%2.2d\x7%2.2d\x7%4.4d\x7%I64d\x7%2.2d\x7%2.2d\x7%2.2d\x7%2.2d\x7%2.2d\x7%4.4d\x7%I64d\x7%2.2d\x7%2.2d\x7%2.2d\x7%2.2d\x7%2.2d\x7%4.4d\x7%d\x7%d\x7%d\x7%d\x7%d\x7%d\x7%d\x7%d\x7",
								(LPCSTR)ff.GetRoot(),
								(LPCSTR)ff.GetFileName(),
								ff.GetLength() ,
								CRTime.GetTime(), CRTime.GetSecond(), CRTime.GetMinute(), CRTime.GetHour(), CRTime.GetDay(), CRTime.GetMonth(),CRTime.GetYear(),
								LWTime.GetTime(), LWTime.GetSecond(), LWTime.GetMinute(), LWTime.GetHour(), LWTime.GetDay(), LWTime.GetMonth(),LWTime.GetYear(),
								LATime.GetTime(), LATime.GetSecond(), LATime.GetMinute(), LATime.GetHour(), LATime.GetDay(), LATime.GetMonth(),LATime.GetYear(),
								ff.IsReadOnly() , ff.IsDirectory ( ), ff.IsCompressed( ), ff.IsSystem( ),   ff.IsHidden( ),  ff.IsTemporary( ),ff.IsNormal( ),ff.IsArchived( ));

						BSTR mbstr=ff.GetFilePath().AllocSysString();
						Bitmap *m_Bitmap= new Bitmap(mbstr);
						try
						{
							if (m_Bitmap)
							{
								/*
								UINT totalBufferSize=0;
								UINT numProperties=0;
								m_img->GetPropertySize(&totalBufferSize,&numProperties);
								BYTE *probBuffer = new BYTE [totalBufferSize+1000];
								PropertyItem *allItems=(PropertyItem *)probBuffer;
								m_img->GetAllPropertyItems(totalBufferSize,numProperties,allItems);
								delete [] probBuffer;
								*/
								int ImgLId=(ccILName && *ccILName)?GPC.GetImageListId(ccILName):-1;
								GPImageList *MainIl=NULL;
								if (ImgLId>=0) MainIl=&(GPC.a_GPImageList[ImgLId]);

								SizeF cSF;
								GUID guid;
								WCHAR strGuid[50];
								m_Bitmap->GetRawFormat(&guid);
								StringFromGUID2(guid, strGuid, 39);
								CString csTmpTmp(strGuid);
								m_Bitmap->GetPhysicalDimension(&cSF);
								cImgOutPos+=sprintf(cImgOutPos,"%d\x7%X\x7%d\x7%d\x7%g\x7%g\x7%d\x7%g\x7%g\x7%d\x7%s\x7",
										m_Bitmap->GetLastStatus(),
										m_Bitmap->GetFlags(),
										m_Bitmap->GetWidth(),
										m_Bitmap->GetHeight(),
										m_Bitmap->GetHorizontalResolution(),
										m_Bitmap->GetVerticalResolution(),
										m_Bitmap->GetPixelFormat(),
										cSF.Width,
										cSF.Height,
										m_Bitmap->GetType(),
										(LPCSTR)csTmpTmp
										);


								DWORD nDim=m_Bitmap->GetFrameDimensionsCount();
								GUID *gaGuid=new GUID [nDim+1];
								m_Bitmap->GetFrameDimensionsList(gaGuid,nDim);
								DWORD dwi;
								for(dwi=0;dwi<nDim;dwi++)
								{
									StringFromGUID2(gaGuid[dwi], strGuid, 39);
									csTmpTmp=strGuid;
									if (dwi) *(cImgOutPos++)=3;
									DWORD nFrames=m_Bitmap->GetFrameCount(gaGuid+dwi);
									cImgOutPos+=sprintf(cImgOutPos,"%s\x4%d",(LPCSTR)csTmpTmp,nFrames);
									if (MainIl)
									{
										DWORD nfm;
										DWORD strtFrm=0;
										DWORD endFrm=nFrames-1;
										int nImage=inImage;
										if (nImage>0 && (DWORD)nImage>nFrames) nImage=nFrames-1;
										if (nImage>=0) endFrm=strtFrm=nImage;
										for(nfm=strtFrm;nfm<=endFrm;nfm++)
										{
											HICON hicon=NULL;
											m_Bitmap->SelectActiveFrame(gaGuid+dwi,nfm);
											m_Bitmap->GetHICON(&hicon);
											if (hicon && MainIl->m_IL.m_hImageList)
											{
												MainIl->m_IL.Add(hicon);
												DestroyIcon(hicon);
											}
										}
									}

								}
							}
						}
						catch(...){;}
						if (m_Bitmap) delete m_Bitmap;
						::SysFreeString(mbstr);

						curArrLen+=(int)strlen(tmps);
						if (curArrLen+100>maxArrLen)
						{
							maxArrLen+=(maxArrLen/4);
							char *tmparr=new char [maxArrLen];
							strcpy(tmparr,*oStr);
							delete [] *oStr;
							*oStr=tmparr;
						}
						strcat(*oStr,tmps);
					}
				}
			}while(ret);
		}
		catch(...){;}
		delete [] tmps;
		ff.Close();
	}

	return *oStr;
}

char *FindImagesRecursive(const char *ccFileName, char **oStr, DWORD dwAttributes, DWORD dwDateType, CTime &MinTime, CTime &MaxTime, const char *ccILName, int nImage)
{
	if (!dwAttributes) dwAttributes=0xFFFF;
	char *cPath=new char [(int)strlen(ccFileName)+1100];
	strcpy(cPath,ccFileName);
	char *postmp=cPath;
	char *posFName=cPath;
	while(*postmp)
	{
		if (*postmp=='/') *postmp='\\';
		postmp++;
	}
	postmp=cPath;

	while(*postmp) if (*(postmp++)=='\\') posFName=postmp;

	strcpy(cPath+1000,posFName);
	if (posFName!=cPath) posFName--;
	*(posFName++)='\\';
	*(posFName++)='*';
	*posFName=0;
	posFName=cPath+1000;

	FindImages(ccFileName,oStr, dwAttributes, dwDateType, MinTime, MaxTime, ccILName, nImage);
	if (!*oStr)
	{
		*oStr=new char [100];
		**oStr=0;
	}

	CFileFind ff;
	BOOL bFind=ff.FindFile(cPath,0);
	UINT ret=0;
	if (bFind)
	{
		int curArrLen=(int)strlen(*oStr);
		do
		{
			ret=ff.FindNextFile();
			if (ff.IsDirectory() && ff.GetFileName()!="." && ff.GetFileName()!="..")	
			{
				char *tmpoStr=NULL;
				CString tmpP=ff.GetFilePath()+"\\";
				tmpP+=posFName;
				FindImagesRecursive(tmpP,&tmpoStr, dwAttributes, dwDateType, MinTime, MaxTime, ccILName, nImage);
				if (tmpoStr)
				{
					if (*tmpoStr)
					{
						if (curArrLen) strcpy(*oStr+curArrLen++,"\x7F");
						int iLenTmp=(int)strlen(tmpoStr);
						char *tmpArr=new char [curArrLen+iLenTmp+10];
						strcpy(tmpArr,*oStr);
						strcpy(tmpArr+curArrLen,tmpoStr);
						curArrLen+=iLenTmp;
						delete [] *oStr;
						*oStr=tmpArr;
					}
					delete [] tmpoStr;
				}
			}
		}while(ret);
		ff.Close();
	}
	delete [] cPath;

	return *oStr;
}

MAT_ARGS &CalcArithmeticString(const char *iString, MAT_ARGS &pMA)
{
	pMA.AsInt[0]=0;
	pMA.AsDouble[0]=0;
	pMA.dwCount=0;

	if (*iString)
	{
		const char *pos=iString;
		while(*pos)
		{
			MAT_ARGS arg={0};
			arg.dwOperation[0]='+';
			while(*pos && *pos!=',')
			{
				const char *pos2=pos;
				BOOL bHEX=FALSE;
				BOOL bDbl=FALSE;
				while(*pos2 && ((*pos2>='0' && *pos2<='9') || (*pos2>='A' && *pos2<='F') || (*pos2>='a' && *pos2<='f') || (bDbl=(*pos2=='.')) || (bHEX=(*pos2=='x')) || (bHEX=(*pos2=='X')) )) pos2++;
				if (bHEX)
				{
					m_LastScanf=sscanf((*pos=='0')?pos+2:pos+1,"%x",arg.AsInt+arg.dwCount);
					arg.AsDouble[arg.dwCount]=arg.AsInt[arg.dwCount];
				}
				else
				if (bDbl)
				{
					arg.AsDouble[arg.dwCount]=atof(pos);
					arg.AsInt[arg.dwCount]=(int)arg.AsDouble[arg.dwCount];
				}
				else
				{
					arg.AsDouble[arg.dwCount]=atof(pos);
					arg.AsInt[arg.dwCount]=atoi(pos);
				}
				arg.dwOperation[++arg.dwCount]=*pos2;
				pos=pos2;
				if (*pos) pos++;
			}

			DWORD i;
			DWORD dwCurOperand=0;
			for(i=1;i<arg.dwCount;i++)
				switch(arg.dwOperation[i])
				{
				case '&':
					arg.AsInt[dwCurOperand]&=arg.AsInt[i];
					arg.AsDouble[dwCurOperand]=arg.AsInt[dwCurOperand];
					arg.dwOperation[i]=0;
					break;
				case '|':
					arg.AsInt[dwCurOperand]|=arg.AsInt[i];
					arg.AsDouble[dwCurOperand]=arg.AsInt[dwCurOperand];
					arg.dwOperation[i]=0;
					break;
				case '^':
					arg.AsInt[dwCurOperand]^=arg.AsInt[i];
					arg.AsDouble[dwCurOperand]=arg.AsInt[dwCurOperand];
					arg.dwOperation[i]=0;
					break;
				case '!':
					arg.AsInt[dwCurOperand]=!arg.AsInt[i];
					arg.AsDouble[dwCurOperand]=arg.AsInt[dwCurOperand];
					arg.dwOperation[i]=0;
					break;
				case 0:
					break;
				default:
					dwCurOperand=i;
					break;
				}

			dwCurOperand=0;
			for(i=1;i<arg.dwCount;i++)
				switch(arg.dwOperation[i])
				{
				case '*':
					arg.AsDouble[dwCurOperand]*=arg.AsDouble[i];
					arg.AsInt[dwCurOperand]=(int)arg.AsDouble[dwCurOperand];
					arg.dwOperation[i]=0;
					break;
				case '/':
					if (arg.AsDouble[i]>0.00000000001 || arg.AsDouble[i]<-0.00000000001)
						arg.AsDouble[dwCurOperand]/=arg.AsDouble[i];
					else 
						arg.AsDouble[dwCurOperand]=0;
					arg.AsInt[dwCurOperand]=(int)arg.AsDouble[dwCurOperand];
					arg.dwOperation[i]=0;
					break;
				case 0:
					break;
				default:
					dwCurOperand=i;
					break;
				}


			pMA.AsInt[pMA.dwCount]=arg.AsInt[0];
			pMA.AsDouble[pMA.dwCount]=arg.AsDouble[0];

			for(i=1;i<arg.dwCount;i++)
				switch(arg.dwOperation[i])
				{
				case '+':
					pMA.AsInt[pMA.dwCount]+=arg.AsInt[i];
					pMA.AsDouble[pMA.dwCount]+=arg.AsDouble[i];
					break;
				case '-':
					pMA.AsInt[pMA.dwCount]-=arg.AsInt[i];
					pMA.AsDouble[pMA.dwCount]-=arg.AsDouble[i];
					break;
				case 0:
					break;
				default:
					break;
				}


			pMA.dwCount++;
			if (*pos)
			{
				pMA.AsInt[0]=0;
				pMA.AsDouble[0]=0;
				pMA.dwCount=0;
				pos++;
			}
		}

	}
	else pMA.dwCount=1;

	
	return pMA;
}


double CalcMathString(const char *iString)
{
	MAT_ARGS m_MA;
	double m_dblResult=0;
	if (*iString)
	{
		char *tmpRet=new char [(int)strlen(iString)*4+1000];
		strcpy(tmpRet,iString);
		char *pos=tmpRet;
		char *pos2=pos;
		char *pos3;
		while((*pos2=*pos))
		{
			if (*pos2!=' ') pos2++;
			pos++;
		}

		BOOL bBrace;
		do
		{
			bBrace=FALSE;
			pos2=tmpRet;
			pos3="(";

			while(*pos2 && *pos3=='(')
				if (*pos2=='(')
				{
					bBrace=TRUE;
					pos3=pos2+1;
					while(*pos3 && *pos3!='(' && *pos3!=')') pos3++;
					if (*pos3=='(') pos2=pos3;
					else
					{
						if (!*pos3) pos3[1]=0;
						*(pos3++)=0;
					}
				}
				else pos2++;


			char *pos0=pos2!=tmpRet?pos2-1:pos2;
			if (*pos2=='(')
			{
				*pos2=0;
				*pos3=0;
				CalcArithmeticString(pos2+1,m_MA);
				const char *pos00;
				if (*pos0)
				{
					while(!(pos00=strchr("/*-+()[]{}&!^|,.<>\\\"'#$~%:;?=",*pos0)) && pos0!=tmpRet) pos0--;
					if (pos00) pos0++;
				}


				if (*pos0)
				{
					if (_stricmp("sin",pos0)==0) m_dblResult=sin(m_MA.AsDouble[0]);
					else
					if (_stricmp("abs",pos0)==0) m_dblResult=abs(m_MA.AsInt[0]);
				}
				else m_dblResult=m_MA.AsDouble[0];

				if (!*pos3)
				{
					if (pos0==tmpRet) bBrace=FALSE;
					sprintf(pos0,"%g",m_dblResult);
				}
				else
				{
					char tmpres[100];
					int newlen=pos3-pos0+1-sprintf(tmpres,"%g",m_dblResult);
					if (newlen>=0)
					{
						char *tmppos3=pos3+(int)strlen(pos3)+10;
						strcpy(tmppos3,pos3);
						strcpy(pos0,tmpres);
						strcat(pos0,tmppos3);
					}
					else
					{
						strcpy(pos0,tmpres);
						strcat(pos0,pos3);
					}
				}
			}
			else 
			{
				CalcArithmeticString(tmpRet,m_MA);
				bBrace=FALSE;
				sprintf(pos2,"%g",m_dblResult=m_MA.AsDouble[0]);
			}
		}
		while(bBrace);


		delete [] tmpRet;
	}
	return m_dblResult;
}