// GPCDAOWorkspace.h: interface for the GPCDAOWorkspace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPCDAOWORKSPACE_H__E67FF1C5_412F_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_GPCDAOWORKSPACE_H__E67FF1C5_412F_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GPCDAODatabase.h"

#define N_DAOWORKSPACE_ARR		10
#define N_DAODATABASE_COUNT		64
#define N_DAODATABASE_ARR		640

#pragma warning(disable : 4995)

class GPCDAOWorkspace
{
friend class CGP_TermDoc;
public:
	int CreateGPTDef(const char *iStr);
	int CreateGPQDef(const char *iStr);
	int OpenGPTDef(const char *iStr);
	int OpenGPQDef(const char *iStr);
	BOOL CloseGPTDef(const char *iStr);
	BOOL CloseGPQDef(const char *iStr);

	static const UINT nArrLocale;
	static const char * ReTranslateLocale(LPCTSTR iType);
	static int TranslateOptions(const char * iStr);
	static const char * TranslateLocale(const char * iStr);
	GPCDAOWorkspace();
	virtual ~GPCDAOWorkspace();
	int OpenGPWS(const char *iStr);
	int OpenGPDB(const char *iStr);
	int CreateGPDB(const char *iStr);
	int OpenGPRS(const char *iStr);
	BOOL CloseGPWS(int IdWS);
	BOOL CloseGPDB(const char *iStr);
	BOOL CloseGPRS(const char *iStr);
	void DoStaticWSMethod(const char *iMethod, BOOL Ret);
	void DoWSMethod(const char *iMethod, BOOL Ret);
	void DoDBMethod(const char *iMethod, BOOL Ret);
	void DoRSMethod(const char *iMethod, BOOL Ret);
	void DoQDMethod(const char *iMethod, BOOL Ret);
	void DoTDMethod(const char *iMethod, BOOL Ret);
	int DoMethod(int IdWS, const char *iMethod, char *oStr);
	void SendRet(char *oStr, int type);
	static const char *LocName[22];
	static LPCTSTR uLocale[22];

private:
	GPCDAODatabase *gpdb[N_DAODATABASE_ARR];
	CDaoWorkspace *gpws[N_DAOWORKSPACE_ARR];
};

#endif // !defined(AFX_GPCDAOWORKSPACE_H__E67FF1C5_412F_11D4_970E_0080AD863699__INCLUDED_)

