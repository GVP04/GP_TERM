// GPOLERange.h: interface for the GPOLERange class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPOLERANGE_H__B0E28B96_DBFE_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_GPOLERANGE_H__B0E28B96_DBFE_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "excel8.h"

#define N_EXCELOLERANGE_ARR 20

class GPOLERange  
{
friend class CGP_TermDoc;
public:
	int DeleteRangesForWorksheet(int IdApp,const char* iStr);
	int DeleteRangesForWorkbook(int IdApp,const char* iStr);
	int DeleteRangesForApp(int IdApp);
	GPOLERange();
	virtual ~GPOLERange();
	int DoMethod(const char* iMethod,char* oStr,BOOL flgRet); //Range Method
	int GPOLERange::DoERMethod(int IdER, const char *iMethod, char *oStr,BOOL flgRet); // Excel Range Method
	int CreateGPExcelRange(LPDISPATCH pDisp,const char *iStr,char* oStr);
	int CloseGPExcelRange(const char *iStr);
private:
	GPExcelOLERange* gpRanges[N_EXCELOLERANGE_ARR];
	int gpIdAppRanges[N_EXCELOLERANGE_ARR];
	int gpIdWorkbookRanges[N_EXCELOLERANGE_ARR];
	int gpIdWorksheetRanges[N_EXCELOLERANGE_ARR];
};

#endif // !defined(AFX_GPOLERANGE_H__B0E28B96_DBFE_11D4_970E_0080AD863699__INCLUDED_)
