// GPScript.cpp: implementation of the CGPScript class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPScript.h"
#include "GP_TermDoc.h"
#include "GP_TermView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const char *CGPScript::ccSKeywords[]=
{
	"REM","SENDLINE","SENDCHAR","SENDFILE","SENDVAR",
	"LINESCRIPT","EXECSUB","EXECFN","GOSUB","GOTO",
	"LABEL","RETURN","STOP","EXECSUB@","EXECFN@",
	"INCLUDE","VERSION","DESCRIPTION","LINESCRIPT@","",
	"","","","","",
};

CGPScript::GPScriptItemType CGPScript::lineTypes[]=
{
	GPScriptItemTypeRem,GPScriptItemTypeSendLine,GPScriptItemTypeSendChar,GPScriptItemTypeSendFile,GPScriptItemTypeSendVar,
	GPScriptItemTypeLineScript,GPScriptItemTypeExecSub,GPScriptItemTypeExecFn,GPScriptItemTypeGosub,GPScriptItemTypeGoto,
	GPScriptItemTypeLabel,GPScriptItemTypeReturn,GPScriptItemTypeStop,GPScriptItemTypeExecSubVar,GPScriptItemTypeExecFnVar,
	GPScriptItemTypeInclude,GPScriptItemTypeVersion,GPScriptItemTypeDescription,GPScriptItemTypeScriptVar,

	GPScriptItemTypeUnknown,GPScriptItemTypeUnknown,
};


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGPScript::CGPScript()
{
	Reset();
}

CGPScript::~CGPScript()
{
	Reset();
}

void CGPScript::Reset()
{
	csStack="-10";
	dwCurLine=0;
	csVersion="";
	csDescription="";
	ra_ScriptArray.ResetArray();
}

DWORD CGPScript::LoadScript(const char *ccFileName, GPScriptLoadOption dwLoadFlags)
{
	DWORD ret=0;
	if ((dwLoadFlags&GPScriptLoadOptionAppend)!=GPScriptLoadOptionAppend) Reset();
	FILE *src=NULL;
	if (csLoadPath!="") 
	{
		CString csFileName=csLoadPath+"\\"+ccFileName;
		csFileName.Remove(10);
		csFileName.Remove(13);
		src=fopen(csFileName,"rt");
//		"C:\MyProjects\FlashGui\CUR_QM\CompleteDelete_FG_OpenQM.BTSF"
	} 
	if (!src) src=fopen(ccFileName,"rt");

	if (src)
	{
		GPSCRIPTITEM tmpItem;
		char *buf=new char [55000];
		while(fgets(buf,50000,src) && ra_ScriptArray.GetCount()<30000)
		{
			char *tmppos=buf;
			while(*tmppos && *tmppos!=10 && *tmppos!=13) tmppos++;
			*tmppos=0;
			tmppos=buf;
			while(*tmppos==' ' || *tmppos=='\t') tmppos++;
			char *tmpcmd=tmppos;
			while(*tmppos && *tmppos!=' ' && *tmppos!='\t') tmppos++;
			if (*tmppos) *(tmppos++)=0;
			while(*tmppos==' ' || *tmppos=='\t') tmppos++;

			_strupr(tmpcmd);
			if (*tmpcmd)
			{
				GPScriptItemType curLineType=GetTextType(tmpcmd);
				if (curLineType!=GPScriptItemTypeUnknown)
				{
					BOOL bAddItem=TRUE;
					tmpItem.eItemType=curLineType;
					tmpItem.dwItemData=0;
					tmpItem.csItemText=ExtractField(ExtractField(tmppos,1,"\r"),1,"\n");
					tmpItem.csItemText.Replace("$ScriptFolder$",csLoadPath);

					switch(tmpItem.eItemType)
					 {
					case GPScriptItemTypeSendChar:
						{
							int pos=tmpItem.csItemText.FindOneOf("xX");
							if (pos>=0) sscanf(tmpItem.csItemText,"%X",&pos);
							else	pos=atoi(tmpItem.csItemText);
							tmpItem.dwItemData=pos;
						}
						break;
					case GPScriptItemTypeSendFile:
					case GPScriptItemTypeGosub:
					case GPScriptItemTypeGoto:
					case GPScriptItemTypeLabel:
					case GPScriptItemTypeSendVar:
					case GPScriptItemTypeExecSubVar:
					case GPScriptItemTypeExecFnVar:
						tmpItem.csItemText=tmpItem.csItemText.Trim();
						break;
					case GPScriptItemTypeScriptVar:
					case GPScriptItemTypeSendLine:
					case GPScriptItemTypeLineScript:
					case GPScriptItemTypeExecSub:
					case GPScriptItemTypeExecFn:
					case GPScriptItemTypeReturn:
					case GPScriptItemTypeStop:
						break;
					case GPScriptItemTypeInclude:
						bAddItem=FALSE;
						LoadScript(tmppos,(GPScriptLoadOption)(dwLoadFlags|GPScriptLoadOptionAppend));
						break;
					case GPScriptItemTypeVersion:
						bAddItem=FALSE;
						csVersion=tmppos;
						break;
					case GPScriptItemTypeDescription:
						bAddItem=FALSE;
						csDescription=tmppos;
						break;
					case GPScriptItemTypeRem:
						bAddItem=FALSE;
						break;
					default:
						bAddItem=FALSE;
						break;
					}
					if (bAddItem)
					{
						ra_ScriptArray[ra_ScriptArray.GetCount()]=tmpItem;
					}
				}
			}
		}
		fclose(src);
		delete [] buf;
	}

	return ra_ScriptArray.GetCount();
}

CString CGPScript::GetNextLine()
{
	EnterCriticalSection(&(GPC.m_View->m_CSRemap));
	DWORD emergencyVar=0;
	CString ret="";
	BOOL bExit=FALSE;
	DWORD dwnLines=ra_ScriptArray.GetCount();
	while(emergencyVar++<100000 && dwCurLine<dwnLines && !bExit)
	{
		GPSCRIPTITEM tmpItem=ra_ScriptArray[dwCurLine];
		AnsiToDos(tmpItem.csItemText,tmpItem.csItemText,0);
		switch(tmpItem.eItemType)
		{
		case GPScriptItemTypeSendLine:
			m_Comm.GPSendLine(tmpItem.csItemText);
			m_Comm.GPSendChar('\r');
			break;
		case GPScriptItemTypeSendChar:
			m_Comm.GPSendChar((char)tmpItem.dwItemData);
			break;
		case GPScriptItemTypeSendFile:
			{
				CString csFileName=ExtractField(tmpItem.csItemText,2,";");
				if (csLoadPath!="") csFileName=csLoadPath+"\\"+csFileName;
				CString csParams=ExtractField(ExtractField(tmpItem.csItemText,1,";"),1,",");
				csParams.MakeUpper();
				if (csFileName!="")
				{
					const char *ftype=csParams.Find("HEX")>=0?"rb":"rt";
					FILE *tmpf=fopen(csFileName,ftype);
					if (!tmpf) tmpf=fopen(ExtractField(tmpItem.csItemText,2,";"),ftype);
					if (tmpf)
					{
						BOOL bFlagCRAM=(csParams.Find("CRAM")>=0);
						if (csParams=="" || bFlagCRAM)
						{
							char delimstr[]={'\r',0};
							int LineDelim='\r';
							if (bFlagCRAM) *delimstr=LineDelim=0x7F;
							AnsiToDos(delimstr,0);

							int nstr=0;
							char *buf=new char [55000];
							while(fgets(buf,50000,tmpf))
							{
								char *tmppos=buf;
								if (nstr++) m_Comm.GPSendLine(delimstr);
								while(*tmppos && *tmppos!=10)
								{
									if (*tmppos==13)  {nstr++;*tmppos=LineDelim;}
									tmppos++;
								}
								*tmppos=0;
								AnsiToDos(buf,0);
								m_Comm.GPSendLine(buf);
							}
							delete [] buf;
						}
						else
						if (csParams.Find("HEX")>=0)
						{
							int c;
							while((c=fgetc(tmpf))!=EOF)
							{
								m_Comm.GPSendChar(hexchars[(c/0x10)&0xF]);
								m_Comm.GPSendChar(hexchars[c&0xF]);
							}
						}
						fclose(tmpf);
					}
				}
			}
			break;
		case GPScriptItemTypeSendVar:
			{
				CString tmpcs="";
				CString *varSpr= (CString *)GPC.SprVariables.FindItemExact(0,tmpItem.csItemText);
				if (varSpr) tmpcs=varSpr[1];
				AnsiToDos(tmpcs,tmpcs,0);
				m_Comm.GPSendLine(tmpcs);
			}
			break;
		case GPScriptItemTypeLineScript:
			ret=tmpItem.csItemText;
			bExit=TRUE;
			break;
		case GPScriptItemTypeExecSub:
			{
				CString tmpRes;
				GPC.m_Document->DoAnyMethod(tmpItem.csItemText,0, tmpRes);
			}
			break;
		case GPScriptItemTypeExecFn:
			{
				CString tmpRes;
				GPC.m_Document->DoAnyMethod(tmpItem.csItemText,0, tmpRes);
				AnsiToDos(tmpRes,tmpRes,0);
				m_Comm.GPSendLine(tmpRes);
			}
			break;
		case GPScriptItemTypeGosub:
			{
				CString tmpcs;
				tmpcs.Format("%d,",dwCurLine);
				csStack=tmpcs+csStack;
			}
		case GPScriptItemTypeGoto:
			dwCurLine=-10;
			if (tmpItem.csItemText!="") dwCurLine=FindLabel(tmpItem.csItemText);
			break;
		case GPScriptItemTypeReturn:
			if (csStack=="") csStack="-10";
			dwCurLine=atoi(csStack);
			if (dwCurLine==0 && csStack)
			if (dwCurLine<dwnLines)
			{
				CString tmpcs=FindField(csStack,2,",");
				csStack=tmpcs;
				if (csStack=="") csStack="-10";
			}
			break;
		case GPScriptItemTypeStop:
			dwCurLine=-10;
			break;
		case GPScriptItemTypeExecSubVar:
		case GPScriptItemTypeExecFnVar:
		case GPScriptItemTypeScriptVar:
			{
				CString tmpcs="";
				CString *varSpr= (CString *)GPC.SprVariables.FindItemExact(0,tmpItem.csItemText);
				if (varSpr) tmpcs=varSpr[1];
				if (tmpcs!="")
				{
					CString tmpRes;

					switch(tmpItem.eItemType)
					{
					case GPScriptItemTypeExecSubVar:
						GPC.m_Document->DoAnyMethod(tmpcs,0, tmpRes);
						break;
					case GPScriptItemTypeExecFnVar:
						GPC.m_Document->DoAnyMethod(tmpcs,0, tmpRes);
						AnsiToDos(tmpRes,tmpRes,0);
						m_Comm.GPSendLine(tmpRes);
						break;
					case GPScriptItemTypeScriptVar:
						ret=tmpcs;
						bExit=TRUE;
						break;
					}
				}
			}
			break;
		default:
			break;
		}
		dwCurLine++;
	}
	if (dwCurLine>=dwnLines) Reset();

	LeaveCriticalSection(&(GPC.m_View->m_CSRemap));
	return ret;
}


CString CGPScript::GetFileVersion(const char *ccFileName)
{
	CString ret;
	FILE *src=fopen(ccFileName,"rt");
	if (src)
	{
		char *buf=new char [55000];
		while(fgets(buf,50000,src))
		{
			char *tmppos=buf;
			while(*tmppos==' ' || *tmppos=='\t') tmppos++;
			char *tmpcmd=tmppos;
			while(*tmppos && *tmppos!=' ' && *tmppos!='\t') tmppos++;
			if (*tmppos) *(tmppos++)=0;
			_strupr(tmpcmd);
			if (GetTextType(tmpcmd)==GPScriptItemTypeVersion) ret=ExtractField(ExtractField(tmppos,1,"\r"),1,"\n");
		}
		fclose(src);
		delete [] buf;
	}
	return ret;
}
CString CGPScript::GetFileDescription(const char *ccFileName)
{
	CString ret;
	FILE *src=fopen(ccFileName,"rt");
	if (src)
	{
		char *buf=new char [55000];
		while(fgets(buf,50000,src))
		{
			char *tmppos=buf;
			while(*tmppos==' ' || *tmppos=='\t') tmppos++;
			char *tmpcmd=tmppos;
			while(*tmppos && *tmppos!=' ' && *tmppos!='\t') tmppos++;
			if (*tmppos) *(tmppos++)=0;
			_strupr(tmpcmd);
			if (GetTextType(tmpcmd)==GPScriptItemTypeDescription) ret=ExtractField(ExtractField(tmppos,1,"\r"),1,"\n");
		}
		fclose(src);
		delete [] buf;
	}
	return ret;
}

CGPScript::GPScriptItemType CGPScript::GetTextType(const char *ccText)
{
	GPScriptItemType ret=GPScriptItemTypeUnknown;
	if (ccText && *ccText)
	{
		int i;
		for(i=0;*ccSKeywords[i] && strcmp(ccSKeywords[i],ccText)!=0;i++);
		ret=lineTypes[i];
	}
	return ret;
}

DWORD CGPScript::FindLabel(const char *ccText)
{
	DWORD ret=-10;
	DWORD i;
	GPSCRIPTITEM tmpItem;
	DWORD dwnLines=ra_ScriptArray.GetCount();
	for(i=0;i<dwnLines && ret==-10;i++)
	{
		tmpItem=ra_ScriptArray[i];
		if (tmpItem.eItemType==GPScriptItemTypeLabel && tmpItem.csItemText==ccText) ret=i;
	}

	return ret;
}
