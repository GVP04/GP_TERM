// GPCDAODatabase.h: interface for the GPCDAODatabase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPCDAODATABASE_H__E67FF1C6_412F_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_GPCDAODATABASE_H__E67FF1C6_412F_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GPCDAORecordset.h"
#include "GPCDAOTableDef.h"
#include "GPCDAOQueryDef.h"

#define N_DAORECORDSET_COUNT		32
#define N_DAOQUERYDEF_COUNT			32
#define N_DAOTABLEDEF_COUNT			32

#pragma warning(disable : 4995)

class GPCDAODatabase : public CDaoDatabase
{
friend class CGP_TermDoc;
public:
	static const UINT nArrCollation; 
	static const char * cArrCollationName[26];
	static const long   lArrCollation[26];
	static const UINT nArrQDefType;
	static const char *cArrQDefTypeName[14];
	static const int   iArrQDefType[14];
	static const UINT nArrRelAtt;
	static const char *cArrRelAttName[7];
	static const long  lArrRelAtt[7];
	static const UINT nArrExecuteOpt;
	static const char *cArrExecuteOptName[12];
	static const int   iArrExecuteOpt[12];
	static const UINT nArrTDefAtt;
	static const char *cArrTDefAttName[6];
	static const long  lArrTDefAtt[6];


	static long TranslateCollation(const char *iStr);
	static int TranslateQDefType(const char * iStr);
	static long TranslateTDefAttr(const char * iStr);
	static int TranslateExecuteOptions(const char * iStr);
	static long TranslateRelAttr(const char * iStr);
	static const char * ReTranslateCollation(long iType);
	static const char * ReTranslateQDefType(int iType);
	static const CString ReTranslateTDefAttr(long iAttr);
	static const CString ReTranslateRelAttr(long iAttr);


	int OpenGPTDef(const char *iStr);
	int OpenGPQDef(const char *iStr);
	int CreateGPTDef(const char *iStr);
	int CreateGPQDef(const char *iStr);
	GPCDAODatabase(CDaoWorkspace* pCDaoWorkspace);
	virtual ~GPCDAODatabase();
	GPCDAORecordset *a_GPDAORecodset[N_DAORECORDSET_COUNT];
	GPCDAOQueryDef *a_GPDAOQueryDef[N_DAOQUERYDEF_COUNT];
	GPCDAOTableDef *a_GPDAOTableDef[N_DAOTABLEDEF_COUNT];
	void GPClose();
	BOOL GPIsOpen();
	BOOL GPOpen(const char *iStr);
	BOOL GPCreate(const char *iStr);
	int OpenRS(const char *posRS);
	BOOL CloseGPTDef(int IdTDef);
	BOOL CloseGPQDef(int IdQDef);
	BOOL CloseRS(int IdRS);
	int DoMethod(const char *iMethod, char *oStr);
	int DoRSMethod(const char *iMethod, char *oStr);
	int DoQDMethod(const char *iMethod, char *oStr);
	int DoTDMethod(const char *iMethod, char *oStr);
};

#endif // !defined(AFX_GPCDAODATABASE_H__E67FF1C6_412F_11D4_970E_0080AD863699__INCLUDED_)
