// GPCDatabase.h: interface for the GPCDatabase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPCDATABASE_H__7EBF802B_3985_11D4_A239_DCF4C16A2217__INCLUDED_)
#define AFX_GPCDATABASE_H__7EBF802B_3985_11D4_A239_DCF4C16A2217__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GPCRecordset.h"
#define N_MAX_RECODSET	128

class GPCDatabase : public CDatabase  
{
friend class CGP_TermDoc;
public:
	void DoRSMethod(const char *iStr, BOOL Ret);
	int CloseGPRS(const char *iStr);
	int OpenGPRS(const char *iStr);
	GPCRecordset *GPRS[N_MAX_RECODSET];
	int DoMethod(const char *iMethod, char *oStr);
	GPCDatabase();
	virtual ~GPCDatabase();

};

#endif // !defined(AFX_GPCDATABASE_H__7EBF802B_3985_11D4_A239_DCF4C16A2217__INCLUDED_)
