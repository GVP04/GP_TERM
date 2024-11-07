// EditorPrintSettings.h: interface for the CEditorPrintSettings class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDITORPRINTSETTINGS_H__9871E5B7_F7D9_45F3_ACC0_24C31CC971A9__INCLUDED_)
#define AFX_EDITORPRINTSETTINGS_H__9871E5B7_F7D9_45F3_ACC0_24C31CC971A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEditorPrintSettings  
{
public:
	CEditorPrintSettings();
	virtual ~CEditorPrintSettings();
	const char * GetFormatedHeaderString(int Page);
	const char * GetFormatedFooterString(int Page);
	const char * GetFormatedString(const char *iFormat, int Page);

public:
	DWORD m_PrintLineNumber;
	DWORD PSetupDlg();
	DWORD m_ColorType;
	void SetHeaderStyle(const char *iStyle);
	void SetFooterStyle(const char *iStyle);
	const char *GetHeaderStyle();
	const char *GetFooterStyle();
	DWORD SetupDlg();
	int m_Magnification;
	CString csheaderFormat;
	CString csfooterFormat;
	CString csAdditionalString;
	CRect pagesetupMargin;
	GPSCSTYLESET sdHeader;
	GPSCSTYLESET sdFooter;
	DWORD m_UseHeader;
	DWORD m_UseFooter;
	DWORD m_UseSelection;
	DWORD m_UseWordWrap;
	void LoadSettings(DWORD iFlag = 0);
	void SaveSettings(DWORD iFlag = 0);

private:
	CString csheaderStyle;
	CString csfooterStyle;
	DWORD m_LoadFlag;
};

#endif // !defined(AFX_EDITORPRINTSETTINGS_H__9871E5B7_F7D9_45F3_ACC0_24C31CC971A9__INCLUDED_)
