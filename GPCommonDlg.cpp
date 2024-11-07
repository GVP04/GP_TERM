// GPCommonDlg.cpp: implementation of the GPCommonDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GP_term.h"
#include "GPCommonFontDlg.h"
#include "GPCommonColorDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define GP_NCOMMDIALOG          7
#define GP_FILE_SAVE_DLG		0
#define GP_FILE_OPEN_DLG		1
#define GP_FONT_DLG				2
#define GP_COLOR_DLG			3
#define GP_FIND_DLG				4
#define GP_FOLDER_OPEN_DLG		5
#define GP_FILE_SAVE_DLG_PREVIEW	6

#include "Vfw.h"

void GPCommonDlg(char *iInitString, char *oStr)
{
	char *cmpiInitString=new char [(int)strlen(iInitString)+5];
	try
	{
	char *CDlgList[GP_NCOMMDIALOG]={"FileSaveDlg","FileOpenDlg","FontDlg","ColorDlg","FindDlg","BrowseFolder","FileSaveDlgPreview",};
	int DlgType=0,i;
	char *postmpconst;
	strcpy(cmpiInitString,iInitString);
	_strupr(cmpiInitString);
	*oStr=0;
	char *pos=strstr(iInitString,"TYPE=");
	if (pos!=NULL)
	{
		if (strstr(cmpiInitString,"TYPE=BROWSEFOLDER")==NULL)
		{
			pos+=5;
			for(DlgType=0;DlgType<GP_NCOMMDIALOG && _strnicmp(CDlgList[DlgType],pos,(int)strlen(CDlgList[DlgType]))!=0;DlgType++);
		}
		else DlgType=GP_FOLDER_OPEN_DLG;
	}

	if (DlgType==GP_NCOMMDIALOG) DlgType=GP_FILE_OPEN_DLG;

	switch(DlgType)
	{
	case GP_FILE_OPEN_DLG:
	case GP_FILE_SAVE_DLG:
	case GP_FILE_SAVE_DLG_PREVIEW:
		{
			char *cstl[25]={"OFN_ALLOWMULTISELECT|","OFN_CREATEPROMPT|","OFN_ENABLEHOOK|","OFN_ENABLESIZING|","OFN_EXPLORER|","OFN_EXTENSIONDIFFERENT|","OFN_FILEMUSTEXIST|","OFN_HIDEREADONLY|","OFN_LONGNAMES|","OFN_NOCHANGEDIR|","OFN_NODEREFERENCELINKS|","OFN_NOLONGNAMES|","OFN_NONETWORKBUTTON|","OFN_NOREADONLYRETURN|","OFN_NOTESTFILECREATE|","OFN_OVERWRITEPROMPT|","OFN_PATHMUSTEXIST|","OFN_READONLY|","OFN_SHAREAWARE|","OFN_SHOWHELP|","OFN_ENABLETEMPLATE|","OFN_ENABLETEMPLATEHANDLE|","OFN_NOVALIDATE|","OFN_DONTADDTORECENT|","OFN_FORCESHOWHIDDEN|",};
			UINT ustl[25]={OFN_ALLOWMULTISELECT,OFN_CREATEPROMPT,OFN_ENABLEHOOK,OFN_ENABLESIZING,OFN_EXPLORER,OFN_EXTENSIONDIFFERENT,OFN_FILEMUSTEXIST,OFN_HIDEREADONLY,OFN_LONGNAMES,OFN_NOCHANGEDIR,OFN_NODEREFERENCELINKS,OFN_NOLONGNAMES,OFN_NONETWORKBUTTON,OFN_NOREADONLYRETURN,OFN_NOTESTFILECREATE,OFN_OVERWRITEPROMPT,OFN_PATHMUSTEXIST,OFN_READONLY,OFN_SHAREAWARE,OFN_SHOWHELP,OFN_ENABLETEMPLATE,OFN_ENABLETEMPLATEHANDLE,OFN_NOVALIDATE,OFN_DONTADDTORECENT,OFN_FORCESHOWHIDDEN,};

			char *cstlEx[1]={"OFN_EX_NOPLACESBAR|",};
			UINT ustlEx[1]={OFN_EX_NOPLACESBAR,};

			OPENFILENAME m_ofn={0};
			#ifdef W_95
				m_ofn.lStructSize=OPENFILENAME_SIZE_VERSION_400;
			#else
				#ifdef W_NT
					m_ofn.lStructSize=OPENFILENAME_SIZE_VERSION_400;
				#else
					m_ofn.lStructSize=sizeof(OPENFILENAME);
				#endif
			#endif
			m_ofn.hwndOwner=::GetForegroundWindow();
			m_ofn.lpstrFile = new char [5000];
			*m_ofn.lpstrFile=0;
			m_ofn.nMaxFile =4900;

			for(i=0;i<25;i++)
				if (strstr(iInitString,cstl[i])!=NULL) m_ofn.Flags|=ustl[i];
			m_ofn.Flags|=OFN_NOCHANGEDIR;

			for(i=0;i<1;i++)
				if (strstr(iInitString,cstlEx[i])!=NULL) m_ofn.FlagsEx|=ustlEx[i];

			////// FILTER=Text Files,*.TXT|Excel,*.xls
			if ((pos=strstr(iInitString,"FILTER="))!=NULL)
			{
				pos+=7;
				m_ofn.lpstrFilter=postmpconst=new char [(int)strlen(pos)+10];
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

			if ((pos=strstr(iInitString,"FILTERC="))!=NULL)
			{
				pos+=8;
				m_ofn.nMaxCustFilter=1000;
				m_ofn.lpstrCustomFilter=new char [m_ofn.nMaxCustFilter];
				pos=strcpy(m_ofn.lpstrCustomFilter,pos);

				while(*pos!=0 && (*pos!=';' || pos[1]=='*'))
				{
					if (*pos==',' || *pos=='|' ) *pos=0;
					pos++;
				}
				*(pos++)=0;
				*(pos++)=0;
			}

			m_ofn.nFilterIndex=1;
			if ((pos=strstr(iInitString,"FILTERINDEX="))!=NULL)
				m_ofn.nFilterIndex=atoi(pos+12);

			if ((pos=strstr(iInitString,"FILE="))!=NULL)
			{
				pos=strcpy(m_ofn.lpstrFile,pos+5);
				if ((pos=strchr(pos,';'))!=NULL) *pos=0;
				if (strstr(m_ofn.lpstrFile,"Open_Dir"))
				{
					DlgType=GP_FOLDER_OPEN_DLG;
//					*m_ofn.lpstrFile=0;
				}
			}

			if ((pos=strstr(iInitString,"FILETITLE="))!=NULL)
			{
				pos=lstrcpyn(m_ofn.lpstrFileTitle,pos+10,m_ofn.nMaxFileTitle);
				if ((pos=strchr(pos,';'))!=NULL) *pos=0;
			}

			if ((pos=strstr(iInitString,"INITDIR="))!=NULL)
			{
				pos+=8;
				m_ofn.lpstrInitialDir=postmpconst=new char [(int)strlen(pos)+10];
				pos=strcpy(postmpconst,pos);
				if ((pos=strchr(pos,';'))!=NULL) *pos=0;
			}

			if ((pos=strstr(iInitString,"DLGTITLE="))!=NULL)
			{
				pos+=9;
				m_ofn.lpstrTitle=postmpconst=new char [(int)strlen(pos)+10];
				pos=strcpy(postmpconst,pos);
				if ((pos=strchr(pos,';'))!=NULL) *pos=0;
			}

			m_ofn.lpstrDefExt=NULL;
			if ((pos=strstr(iInitString,"DEFEXT="))!=NULL)
			{
				pos+=7;
				m_ofn.lpstrDefExt=postmpconst=new char [(int)strlen(pos)+10];
				pos=strcpy(postmpconst,pos);
				if ((pos=strchr(pos,';'))!=NULL) *pos=0;
			}

			BOOL ret=FALSE;
			switch(DlgType)
			{
			case GP_FILE_OPEN_DLG:
				ret=GetOpenFileName(&m_ofn); 
				break;
			case GP_FILE_SAVE_DLG_PREVIEW:
				ret=GetSaveFileNamePreview(&m_ofn);
				break;
			case GP_FOLDER_OPEN_DLG:
			case GP_FILE_SAVE_DLG:
				ret=GetSaveFileName(&m_ofn);
				break;
			}
			


			if (ret==FALSE) strcpy(oStr,"CANCEL");
			else
			{
				sprintf(oStr,"OK\x7F%s\x7F",m_ofn.lpstrFileTitle?m_ofn.lpstrFileTitle:"");

				pos=m_ofn.lpstrFile;
				char *pos2;
				if (DlgType==GP_FOLDER_OPEN_DLG)
				{
					pos2=strstr(pos,"Open_Dir");
					if (pos2!=NULL) *pos2=0;
					pos2=(char *)GetFileName(pos);
					if (pos2) *pos2=0;
				}
				if (pos!=NULL)
				{
					pos2=oStr+(int)strlen(oStr);
					while(*pos!=0 || ((m_ofn.Flags&OFN_ALLOWMULTISELECT)==OFN_ALLOWMULTISELECT && pos[1]!=0))
					{
						if (*pos==0) *(pos2++)=7;
						else *(pos2++)=*pos;
						pos++;
					}
					*pos2=0;
				}
				strcat(oStr,"\x7F");

				pos=m_ofn.lpstrCustomFilter;
				if (pos!=NULL)
				{
					pos2=oStr+(int)strlen(oStr);
					while(*pos!=0 && pos[1]!=0)
					{
						if (*pos==0) *(pos2++)=7;
						else *(pos2++)=*pos;
						pos++;
					}
					*pos2=0;
				}
				sprintf(oStr+(int)strlen(oStr),"\x7F%d",m_ofn.nFilterIndex);
			}

			if (m_ofn.lpstrFilter!=NULL)		delete[] (char *)m_ofn.lpstrFilter;
			if (m_ofn.lpstrCustomFilter!=NULL)	delete[] m_ofn.lpstrCustomFilter;
			if (m_ofn.lpstrInitialDir!=NULL)	delete[] (char *)m_ofn.lpstrInitialDir;
			if (m_ofn.lpstrTitle!=NULL)			delete[] (char *)m_ofn.lpstrTitle;
			if (m_ofn.lpstrDefExt!=NULL)		delete[] (char *)m_ofn.lpstrDefExt;
			if (m_ofn.lpstrFile!=NULL)			delete[] (char *)m_ofn.lpstrFile;

	 
		}
		break;
	case GP_FOLDER_OPEN_DLG:
		{
			BROWSEINFO bi={0};
			bi.hwndOwner=::GetForegroundWindow();

			if ((pos=strstr(iInitString,"DLGTITLE="))!=NULL)
			{
				pos+=9;
				bi.lpszTitle=postmpconst=new char [(int)strlen(pos)+10];
				pos=strcpy(postmpconst,pos);
				if ((pos=strchr(pos,';'))!=NULL) *pos=0;
			}

			TCHAR DisplayName[MAX_PATH];
			ZeroMemory(DisplayName, MAX_PATH);
			bi.pszDisplayName=DisplayName;

			char *cstlBIF[16]={
				"BIF_RETURNONLYFSDIRS","BIF_DONTGOBELOWDOMAIN","BIF_EDITBOX","BIF_RETURNFSANCESTORS","BIF_STATUSTEXT",
				"BIF_BROWSEINCLUDEURLS","BIF_USENEWUI","BIF_NEWDIALOGSTYLE","BIF_VALIDATE",	"BIF_BROWSEFORPRINTER",
				"BIF_BROWSEFORCOMPUTER","BIF_NOTRANSLATETARGETS","BIF_NONEWFOLDERBUTTON","BIF_UAHINT","BIF_SHAREABLE",
				"BIF_BROWSEINCLUDEFILES",
				};
			UINT ustlBIF[16]={
				BIF_RETURNONLYFSDIRS,BIF_DONTGOBELOWDOMAIN,BIF_EDITBOX,BIF_RETURNFSANCESTORS,BIF_STATUSTEXT,
				BIF_BROWSEINCLUDEURLS,BIF_USENEWUI,BIF_NEWDIALOGSTYLE,BIF_VALIDATE,	BIF_BROWSEFORPRINTER,
				BIF_BROWSEFORCOMPUTER,BIF_NOTRANSLATETARGETS,BIF_NONEWFOLDERBUTTON,BIF_UAHINT,BIF_SHAREABLE,
				BIF_BROWSEINCLUDEFILES,
				};

			for(i=0;i<16;i++)
				if (strstr(iInitString,cstlBIF[i])!=NULL) bi.ulFlags|=ustlBIF[i];

			bi.ulFlags&=(0xFFFFFFFF^BIF_RETURNONLYFSDIRS);

			
			LPITEMIDLIST pidl;
			pidl=SHBrowseForFolder(&bi);
			if (pidl) 
			{
				char *pszPath=new char [2000];
				SHGetPathFromIDList(pidl,pszPath);
				sprintf(oStr,"OK\x7F%s\x7F%s\\",bi.pszDisplayName?bi.pszDisplayName:"",pszPath);
				delete[] pszPath;
			}
			else strcpy(oStr,"CANCEL");
			if (bi.lpszTitle) delete[] (char *)bi.lpszTitle;
		}
		break;
	case GP_FONT_DLG:
		{
			UINT Flags=0;
			char *cstl[28]={"CF_APPLY|","CF_ANSIONLY|","CF_BOTH|","CF_TTONLY|","CF_EFFECTS|","CF_ENABLEHOOK|","CF_ENABLETEMPLATE|","CF_ENABLETEMPLATEHANDLE|","CF_FIXEDPITCHONLY|","CF_FORCEFONTEXIST|","CF_INITTOLOGFONTSTRUCT|","CF_LIMITSIZE|","CF_NOOEMFONTS|","CF_NOFACESEL|","CF_NOSCRIPTSEL|","CF_NOSTYLESEL|","CF_NOSIZESEL|","CF_NOSIMULATIONS|","CF_NOVECTORFONTS|","CF_NOVERTFONTS|","CF_PRINTERFONTS|","CF_SCALABLEONLY|","CF_SCREENFONTS|","CF_SCRIPTSONLY|","CF_SELECTSCRIPT|","CF_SHOWHELP|","CF_USESTYLE|","CF_WYSIWYG|",};
			UINT ustl[28]={CF_APPLY,CF_ANSIONLY,CF_BOTH,CF_TTONLY,CF_EFFECTS,CF_ENABLEHOOK,CF_ENABLETEMPLATE,CF_ENABLETEMPLATEHANDLE,CF_FIXEDPITCHONLY,CF_FORCEFONTEXIST,CF_INITTOLOGFONTSTRUCT,CF_LIMITSIZE,CF_NOOEMFONTS,CF_NOFACESEL,CF_NOSCRIPTSEL,CF_NOSTYLESEL,CF_NOSIZESEL,CF_NOSIMULATIONS,CF_NOVECTORFONTS,CF_NOVERTFONTS,CF_PRINTERFONTS,CF_SCALABLEONLY,CF_SCREENFONTS,CF_SCRIPTSONLY,CF_SELECTSCRIPT,CF_SHOWHELP,CF_USESTYLE,CF_WYSIWYG,};
			for(i=0;i<28;i++)
				if (strstr(pos,cstl[i])!=NULL) Flags|=ustl[i];

			static LOGFONT m_LOGFONT;
			GPCommonFontDlg dlg(&m_LOGFONT,Flags);
			dlg.m_cf.iPointSize=10; 
			dlg.m_cf.rgbColors=0;  
			dlg.m_cf.nFontType=0; 

			
			dlg.m_cf.nSizeMin=1;
			if ((pos=strstr(iInitString,"SIZEMIN="))!=NULL)
				dlg.m_cf.nSizeMin=atoi(pos+8);

			dlg.m_cf.nSizeMax=10000;
			if ((pos=strstr(iInitString,"SIZEMAX="))!=NULL)
				dlg.m_cf.nSizeMax=atoi(pos+8);

			if (dlg.DoModal()==IDCANCEL) strcpy(oStr,"CANCEL");
			else
			{
				sprintf(oStr,"OK\x7F%d\x7F%d\x07%d\x07%d\x7F%s\x7F%d\x7F%d\x7F",
					dlg.m_cf.iPointSize,
					GetRValue(dlg.m_cf.rgbColors), 
					GetGValue(dlg.m_cf.rgbColors), 
					GetBValue(dlg.m_cf.rgbColors), 
					dlg.m_cf.lpszStyle, 
					dlg.m_cf.nSizeMin,
					dlg.m_cf.nSizeMax
					);

				UINT ufstl[6]={BOLD_FONTTYPE,ITALIC_FONTTYPE,PRINTER_FONTTYPE,REGULAR_FONTTYPE,SCREEN_FONTTYPE,SIMULATED_FONTTYPE,};
				char *cfstl[6]={"BOLD_FONTTYPE|","ITALIC_FONTTYPE|","PRINTER_FONTTYPE|","REGULAR_FONTTYPE|","SCREEN_FONTTYPE|","SIMULATED_FONTTYPE|",};
				for(i=0;i<6;i++)
					if ((dlg.m_cf.nFontType&ufstl[i])==ufstl[i]) strcat(oStr,cfstl[i]);
				
				strcat(oStr,"\x7F");
				LOGFONT lf={0};
				dlg.GetCurrentFont(&lf);
				TranslLOGFONTtoString(oStr+(int)strlen(oStr),lf);

			}
		}
		break;
	case GP_COLOR_DLG:
		{
			UINT Flags=0;
			char *cstl[9]={"CC_ANYCOLOR|","CC_ENABLEHOOK|","CC_ENABLETEMPLATE|","CC_ENABLETEMPLATEHANDLE|","CC_FULLOPEN|","CC_PREVENTFULLOPEN|","CC_RGBINIT|","CC_SHOWHELP|","CC_SOLIDCOLOR|",};
			UINT ustl[9]={CC_ANYCOLOR,CC_ENABLEHOOK,CC_ENABLETEMPLATE,CC_ENABLETEMPLATEHANDLE,CC_FULLOPEN,CC_PREVENTFULLOPEN,CC_RGBINIT,CC_SHOWHELP,CC_SOLIDCOLOR,};
			for(i=0;i<9;i++)
				if (strstr(pos,cstl[i])!=NULL) Flags|=ustl[i];

			DWORD iRGB=0;

			if ((pos=strstr(iInitString,"INITRGB="))!=NULL)
			{
				int R,G,B;
				m_LastScanf=sscanf(pos+8,"%d,%d,%d",&R,&G,&B);
				iRGB=RGB(R,G,B);
			}

			GPCommonColorDlg dlg(iRGB,Flags);

			dlg.m_cc.rgbResult = 0;

			for(i=0;i<16;i++)
			{
				char tmps[20];
				sprintf(tmps,"CRGB%d=",i);
				if ((pos=strstr(iInitString,tmps))!=NULL)
				{
					int R,G,B;
					m_LastScanf=sscanf(pos+(int)strlen(tmps),"%d,%d,%d",&R,&G,&B);
					dlg.m_cc.lpCustColors[i]=RGB(R,G,B);
				}
			}
			
			if (dlg.DoModal()==IDCANCEL) strcpy(oStr,"CANCEL");
			else
			{
				sprintf(oStr,"OK\x7F%d\x07%d\x07%d\x7F",
					GetRValue(dlg.m_cc.rgbResult), 
					GetGValue(dlg.m_cc.rgbResult), 
					GetBValue(dlg.m_cc.rgbResult)
					);

				if (dlg.m_cc.lpCustColors!=NULL)
					for(i=0;i<16;i++)
					{
						sprintf(oStr+(int)strlen(oStr),"%d\x07%d\x07%d\x7F",
							GetRValue(dlg.m_cc.lpCustColors[i]), 
							GetGValue(dlg.m_cc.lpCustColors[i]), 
							GetBValue(dlg.m_cc.lpCustColors[i])
							);
					}
			}
		}
		break;
	case GP_FIND_DLG:
		{
// см. GPDlgFind.....
		break;
		}
	}
	}
	catch(...)
	{
		char tmps[500];
		sprintf(tmps, "Error create File Open Dlg\n%d", GetLastError());
		
		AfxMessageBox(tmps,MB_OK,0);
		GPC.m_ErrReport.GPWriteErrorLog("GPCommonDlg", "GPCommonDlg",iInitString);
	}
	delete[] cmpiInitString;
}

