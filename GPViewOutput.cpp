// GPViewOutput.cpp: implementation of the GPViewOutput class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPViewOutput.h"
#include "DlgViewOutput.h"
#include "Scintilla\Scintilla.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPViewOutput::GPViewOutput(UINT iUnitId)
	: GPScintilla(iUnitId)
{
	m_FileNameLK="SVOLockKeys.txt";
	LoadLockKeys();
	m_DuplicateInputFlag=0;
	m_HWNDDuplicateInput=NULL;
}

GPViewOutput::~GPViewOutput()
{

}

BEGIN_MESSAGE_MAP(GPViewOutput, GPScintilla)
	//{{AFX_MSG_MAP(GPViewOutput)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int GPViewOutput::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (GPScintilla::OnCreate(lpCreateStruct) == -1)
		return -1;

	ScMethod(SCI_SETEOLMODE,1,0);

	return 0;
}



UINT GPViewOutput::GetTextLength()
{
	return ScMethod(SCI_GETLENGTH,0,0);
}

UINT GPViewOutput::SetTextLengthFromEnd(UINT uNewLen)
{
	UINT curLen=GetTextLength();
	if (curLen>uNewLen)
	{
		int rOnly=ScMethod(SCI_GETREADONLY,0,0);
		if (rOnly) ScMethod(SCI_SETREADONLY,0,0);

		int cPos=ScMethod(SCI_GETCURRENTPOS,0,0);
		int aPos=ScMethod(SCI_GETANCHOR,0,0);
		int delta=curLen-uNewLen;

		ScMethod(SCI_SETANCHOR,0,0);
		ScMethod(SCI_SETCURRENTPOS,delta,0);

		ScMethod(SCI_REPLACESEL,0,(int)"");
		if (rOnly) ScMethod(SCI_SETREADONLY,1,0);

		if (cPos>delta && aPos>delta)
		{
			ScMethod(SCI_SETANCHOR,aPos-delta,0);
			ScMethod(SCI_SETCURRENTPOS,cPos-delta,0);
		}
	}
	return GetTextLength();
}

UINT GPViewOutput::SetTextLengthFromStart(UINT uNewLen)
{
	UINT curLen=GetTextLength();
	if (curLen>uNewLen)
	{
		int rOnly=ScMethod(SCI_GETREADONLY,0,0);
		if (rOnly) ScMethod(SCI_SETREADONLY,0,0);
		UINT cPos=ScMethod(SCI_GETCURRENTPOS,0,0);
		UINT aPos=ScMethod(SCI_GETANCHOR,0,0);

		ScMethod(SCI_SETANCHOR,curLen,0);
		ScMethod(SCI_SETCURRENTPOS,uNewLen,0);

		ScMethod(SCI_REPLACESEL,0,(int)"");
		if (rOnly) ScMethod(SCI_SETREADONLY,1,0);

		if (cPos<uNewLen && aPos<uNewLen)
		{
			ScMethod(SCI_SETANCHOR,aPos,0);
			ScMethod(SCI_SETCURRENTPOS,cPos,0);
		}
	}
	return GetTextLength();
}

LRESULT GPViewOutput::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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
				if (message==WM_KEYUP)
					::SendMessage(::GetParent(m_hWnd),WM_COMMAND,SCCMND_MARKERNEXT,NULL);
				break;
			case (VK_F2*0x10000)|MOD_CONTROL:
				RetSwitch=4;
				if (message==WM_KEYUP)
					::SendMessage(::GetParent(m_hWnd),WM_COMMAND,SCCMND_MARKERADD,NULL);
				break;
			case (VK_F2*0x10000)|MOD_SHIFT:
				RetSwitch=4;
				if (message==WM_KEYUP)
					::SendMessage(::GetParent(m_hWnd),WM_COMMAND,SCCMND_MARKERPREV,NULL);
				break;
			case (VK_F2*0x10000)|(MOD_SHIFT|MOD_CONTROL):
				RetSwitch=4;
				if (message==WM_KEYUP)
					::SendMessage(::GetParent(m_hWnd),WM_COMMAND,SCCMND_MARKERTYPENEXT,NULL);
				break;
			default:
				break;
			}

		if (m_HWNDDuplicateInput && m_DuplicateInputFlag)
		{
			DWORD tmpkey=CurVk/0x10000;
			if ((CurVk&MOD_CONTROL)!=MOD_CONTROL
				&& (CurVk&MOD_ALT)!=MOD_ALT
				&& tmpkey!=VK_UP
				&& tmpkey!=VK_DOWN
				&& tmpkey!=VK_LEFT
				&& tmpkey!=VK_RIGHT
				&& tmpkey!=VK_NEXT
				&& tmpkey!=VK_PRIOR
				&& tmpkey!=VK_INSERT
				&& tmpkey!=VK_DELETE
				&& tmpkey!=VK_HOME
				&& tmpkey!=VK_END
				&& tmpkey!=VK_CLEAR
				&& tmpkey!=VK_LWIN
				&& tmpkey!=VK_RWIN
				&& tmpkey!=VK_LMENU
				&& tmpkey!=VK_RMENU
				&& tmpkey!=VK_MENU
				&& tmpkey!=VK_SCROLL
				&& tmpkey!=VK_SELECT
				&& tmpkey!=VK_ZOOM
				&& tmpkey!=VK_SHIFT
				&& tmpkey!=VK_RSHIFT
				&& tmpkey!=VK_LSHIFT
				&& tmpkey!=VK_CONTROL
				&& tmpkey!=VK_RCONTROL
				&& tmpkey!=VK_LCONTROL
				&& tmpkey!=0
				)
			::SendMessage(m_HWNDDuplicateInput,message,wParam,lParam);
		}
	}

	if (RetSwitch==0)
		lr=GPScintilla::WindowProc(message, wParam, lParam);
	else
		lr=TRUE;

	return lr;
}

BOOL GPViewOutput::PreTranslateMessage(MSG* pMsg)
{
	return GPScintilla::PreTranslateMessage(pMsg);
}
