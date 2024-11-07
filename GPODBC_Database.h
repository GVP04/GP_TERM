// GPODBC_Database.h: interface for the GPODBC_Database class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPODBC_DATABASE_H__7EBF8021_3985_11D4_A239_DCF4C16A2217__INCLUDED_)
#define AFX_GPODBC_DATABASE_H__7EBF8021_3985_11D4_A239_DCF4C16A2217__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GPCDatabase.h"
#define N_DATABASE_ARR		128

class GPODBC_Database  
{
friend class CGP_TermDoc;
public:
	void DoRSMethod(const char *iStr, BOOL Ret);
	void DoDBMethod(const char *iStr, BOOL Ret);
	BOOL CloseGPRS(const char *iStr);
	BOOL CloseGPDB(int iId);
	int OpenGPRS(const char *iStr);
	int OpenGPDB(const char *iStr);
	GPODBC_Database();
	virtual ~GPODBC_Database();
	GPCDatabase *gpdb[N_DATABASE_ARR];
	
};

#endif // !defined(AFX_GPODBC_DATABASE_H__7EBF8021_3985_11D4_A239_DCF4C16A2217__INCLUDED_)
