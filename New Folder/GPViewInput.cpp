// GPViewInput.cpp: implementation of the GPViewInput class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPViewInput.h"
#include "GP_TermView.h"
#include "scintilla\Scintilla.h"
#include "DlgViewInput.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPViewInput::GPViewInput(UINT iUnitId)
	: GPScintilla(iUnitId)
{
	m_FileNameLK="SVILockKeys.txt";
	LoadLockKeys();
	m_dwKeyExecute=(VK_RETURN*0x10000)|MOD_CONTROL;
	m_dwKeyBreak=0x420000|MOD_ALT;
	m_dwKeySoftBreak=0x580000|MOD_CONTROL;
	m_SkipVK=0;
	LoadAppendKeyWords();
}

GPViewInput::~GPViewInput()
{

}

BEGIN_MESSAGE_MAP(GPViewInput, GPScintilla)
	//{{AFX_MSG_MAP(GPViewInput)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int GPViewInput::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (GPScintilla::OnCreate(lpCreateStruct) == -1)
		return -1;

	ScMethod(SCI_SETEOLMODE,1,0);

	return 0;
}

LRESULT GPViewInput::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	LRESULT lr=NULL;
	UINT RetSwitch=0;
	if (message==WM_KEYUP || message==WM_KEYDOWN || message==WM_CHAR) 
	{
		UINT CurVk=(wParam&0xFFFF)*0x10000;
		CurVk|=(GetAsyncKeyState(MOD_SHIFT)&0xFF00)!=0 || (GetAsyncKeyState(VK_RSHIFT)&0xFF00)!=0 || (GetAsyncKeyState(VK_LSHIFT)&0xFF00)!=0?MOD_SHIFT:0;
		CurVk|=(GetAsyncKeyState(VK_CONTROL)&0xFF00)!=0 || (GetAsyncKeyState(VK_RCONTROL)&0xFF00)!=0 || (GetAsyncKeyState(VK_LCONTROL)&0xFF00)!=0?MOD_CONTROL:0;
		CurVk|=(GetAsyncKeyState(MOD_ALT)&0xFF00)!=0 || (GetAsyncKeyState(VK_RMENU)&0xFF00)!=0 || (GetAsyncKeyState(VK_LMENU)&0xFF00)!=0?MOD_ALT:0;


		if (message==WM_KEYUP)
			switch(CurVk)
			{
			case VK_F2*0x10000:
				RetSwitch=4;
				::SendMessage(::GetParent(m_hWnd),WM_COMMAND,SCCMND_MARKERNEXT,NULL);
				break;
			case (VK_F2*0x10000)|MOD_CONTROL:
				RetSwitch=4;
				::SendMessage(::GetParent(m_hWnd),WM_COMMAND,SCCMND_MARKERADD,NULL);
				break;
			case (VK_F2*0x10000)|MOD_SHIFT:
				RetSwitch=4;
				::SendMessage(::GetParent(m_hWnd),WM_COMMAND,SCCMND_MARKERPREV,NULL);
				break;
			case (VK_F2*0x10000)|(MOD_SHIFT|MOD_CONTROL):
				RetSwitch=4;
				::SendMessage(::GetParent(m_hWnd),WM_COMMAND,SCCMND_MARKERTYPENEXT,NULL);
				break;
			default:
				break;
			}

		if (RetSwitch==0)
		{
			if (CurVk==m_dwKeyExecute)
			{
				RetSwitch=1;
				if (message==WM_KEYUP)	::SendMessage(::GetParent(m_hWnd),WM_COMMAND,SCCMND_EXECUTE,(LPARAM)m_hWnd);
				else					m_SkipVK=10;
			}
			else
			if (CurVk==m_dwKeySoftBreak)
			{
				RetSwitch=2;
				if (message!=WM_KEYUP)	m_SkipVK=10;
				else					::SendMessage(::GetParent(m_hWnd),WM_COMMAND,SCCMND_SOFTBREAK,(LPARAM)m_hWnd);
			}
			else
			if (CurVk==m_dwKeyBreak)
			{
				RetSwitch=3;
				::SendMessage(::GetParent(m_hWnd),WM_COMMAND,SCCMND_BREAK,(LPARAM)m_hWnd);
			}
			else
			if (m_SkipVK && message==WM_CHAR)
			{
				RetSwitch=3;
			}
			else m_SkipVK=0;
		}
	}

	if (RetSwitch==0)
		lr=GPScintilla::WindowProc(message, wParam, lParam);

	return lr;
}

BOOL GPViewInput::PreTranslateMessage(MSG* pMsg) 
{
	return GPScintilla::PreTranslateMessage(pMsg);
}

void GPViewInput::ExecCurent()
{
	char *txt;
	int len=ScMethod(SCI_GETSELECTIONEND,0,0)-ScMethod(SCI_GETSELECTIONSTART,0,0);
	if (len<1)
	{
		int cp=ScMethod(SCI_GETCURRENTPOS,0,0);	
		int blocklen=32000;
		if (cp>=0)
		{
			int cl=ScMethod(SCI_LINEFROMPOSITION,cp,0);
			if (cl>=0)
				blocklen=ScMethod(SCI_LINELENGTH,cl,0);
		}
		txt=new char [blocklen+100];
		ScMethod(SCI_GETCURLINE,blocklen+10,(int)txt);
		len=(int)strlen(txt);
		if (len) 
		{
			if (txt[len-1]>15)
				ScMethod(SCI_APPENDTEXT,1,(int)"\r");
		}
	}
	else
	{
		txt=new char [len+100];
		ScMethod(SCI_GETSELTEXT,0,(int)txt);
	}
	Execute(txt);
	delete[] txt;
}

void GPViewInput::Execute(const char *execstr)
{
	if (execstr && *execstr)
	{
		char *tmps=new char [(int)strlen(execstr)+20];
		strcpy(tmps,execstr);
		char *pos=tmps;
		while(*pos)
		{
			char *pos2=pos;
			while(*pos2 && *pos2!='\r' && *pos2!='\n') pos2++;

			if (*pos2) *(pos2++)=0;

			if (*pos)
			{
				CString csExec=pos;
				if (SeqArrayAppend.GetCount())
				{
					CString csPrefix=ExtractField(pos,1," ");
					csPrefix.MakeUpper();
					if (csPrefix!="")
					{
						csPrefix+=" ";
						int curIndex=SeqArray.SelectFirst();
						while(curIndex>=0)
						{
							CString cmpSeq=SeqArray[curIndex];
							cmpSeq.MakeUpper();
							if (cmpSeq.Find(csPrefix,0)>=0)
							{
								csExec+=SeqArrayAppend[curIndex];
								curIndex=-1;
							}
							else
								curIndex=SeqArray.SelectNext();
						}
					}
				}
				csExec+="\r";
				AnsiToDos(csExec,csExec,1);
				m_Comm.GPSendBlock(csExec,csExec.GetLength());
			}
			pos=pos2;
		}
		m_csLastExecute=execstr;
		delete[] tmps;
	}
}

void GPViewInput::ExecuteLast()
{
	Execute(m_csLastExecute);
}

UINT GPViewInput::LoadAppendKeyWords()
{
	SeqArray.ResetArray();
	SeqArrayAppend.ResetArray();
	FILE *src=NULL;

	src=fopen("LexKeywords.txt","rb");
	if (src)
	{
		char *tmps=new char [11000];
		CString cmpName="APPENDKEYWORDS";

		while(fgetsEx(tmps,9990,src))
		{
			if (ExtractField(tmps,1,",")==cmpName)
			{
				int nSubKey=atoi(ExtractField(tmps,2,","));
				char *pos2=tmps,*pos3=tmps;
				do
				{
					if (*pos2==' ' && pos3[1]==' ') pos3++;
					else *(pos2++)=*(pos3++);
				}
				while(*pos3);

				SeqArray[nSubKey]=FindField(ExtractField(tmps,1,"_APPKWDELIM_"),3,",");
				SeqArray[nSubKey]+=" ";
				SeqArrayAppend[nSubKey]=ExtractField(tmps,2,"_APPKWDELIM_");
			}
		}
		delete[] tmps;
		fclose(src);
	}

	return SeqArray.GetCount();
}

