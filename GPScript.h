// GPScript.h: interface for the CGPScript class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPSCRIPT_H__60A8D5E3_A0FB_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_GPSCRIPT_H__60A8D5E3_A0FB_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




class CGPScript : public CFont  
{
public:
	enum GPScriptLoadOption
	{
		GPScriptLoadOptionDefault	= 0x0,	
		GPScriptLoadOptionAppend	= 0x1
	};
	enum GPScriptItemType
	{
		GPScriptItemTypeRem			= 0x0000,	
		GPScriptItemTypeUnknown		= 0x2000,	
		GPScriptItemTypeSendLine	= 0x1001,	
		GPScriptItemTypeSendChar	= 0x1002,
		GPScriptItemTypeSendFile	= 0x1003,
		GPScriptItemTypeSendVar		= 0x1004,
		GPScriptItemTypeLineScript	= 0x0005,
		GPScriptItemTypeExecSub		= 0x0006,	
		GPScriptItemTypeExecFn		= 0x1007,
		GPScriptItemTypeGosub		= 0x0008,
		GPScriptItemTypeGoto		= 0x0009,
		GPScriptItemTypeLabel		= 0x0010,
		GPScriptItemTypeReturn		= 0x0011,
		GPScriptItemTypeStop		= 0x0012,
		GPScriptItemTypeExecSubVar	= 0x0014,	
		GPScriptItemTypeExecFnVar	= 0x1015,
		GPScriptItemTypeInclude		= 0x0016,
		GPScriptItemTypeVersion		= 0x2017,
		GPScriptItemTypeDescription	= 0x2018,
		GPScriptItemTypeScriptVar	= 0x0019,

		GPScriptItemTypeMaskSend	= 0x1000,
		GPScriptItemTypeMaskNOP		= 0x2000,
	};


	typedef struct _GPSCRIPTITEM
	{
		DWORD dwItemData;
		GPScriptItemType eItemType;
		CString csItemText;
	} GPSCRIPTITEM, *PGPSCRIPTITEM;


	CGPScript();
	GP_RarefiedArr<GPSCRIPTITEM> ra_ScriptArray;
	DWORD LoadScript(const char *ccFileName, GPScriptLoadOption dwLoadFlags);
	DWORD FindLabel(const char *ccText);

	CString GetNextLine();
	CString csStack;
	void Reset();
	DWORD dwCurLine;
	CString csVersion;
	CString csLoadPath;
	CString csDescription;
	static CString GetFileVersion(const char *ccFileName);
	static CString GetFileDescription(const char *ccFileName);
	static const char *ccSKeywords[];
	static GPScriptItemType lineTypes[];
	static GPScriptItemType GetTextType(const char *ccText);
	virtual ~CGPScript();
};

#endif // !defined(AFX_GPSCRIPT_H__60A8D5E3_A0FB_11D4_970E_0080AD863699__INCLUDED_)
