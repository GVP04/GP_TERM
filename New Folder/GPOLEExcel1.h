// GPOLEExcel1.h: interface for the GPOLEExcel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPOLEEXCEL1_H__FBFBBEC1_D659_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_GPOLEEXCEL1_H__FBFBBEC1_D659_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GPOLERange.h"

#define N_EXCELAPPLICATION_ARR		20
#define N_EXCELRANGE_ARR			20

class GPOLEExcel  
{
friend class CGP_TermDoc;
public:
	int DoRMethod(int IdRange, const char *iMethod, char *oStr,BOOL flgRet); //Range Method
	int DoERMethod(int IdRange, const char *iMethod, char *oStr,BOOL flgRet); // Excel range Method
	int DoWsMethod(int IdApp, const char *iMethod, char *oStr,BOOL flgRet);
	int DoWbMethod(int IdApp,const char* iMethod,char* oStr,BOOL flgRet);
	int CreateGPOLERange(const char *iStr,char *oStr);
	int CloseGPOLERange(const char *iStr);
	int CreateGPExcelRange(const char *iStr,char *oStr);
	int CloseGPExcelRange(const char *iStr);
	int CreateGPExcelWorksheet(const char *iStr,char *oStr);
	int CloseGPExcelWorksheet(const char *iStr);
	int CreateGPExcelWorkbook(const char *iStr,char *oStr);
	int CloseGPExcelWorkbook(const char *iStr);
	int OpenGPExcelWorkbook(const char *iStr,char *oStr);
	int CloseGPExcelApp(const char *iStr);
	GPOLEExcel();
	virtual ~GPOLEExcel();
	int DoMethod(const char *iMethod, char *oStr,BOOL flgRet); // для всех приложений
	int DoEAMethod(int IdApp,const char *iMethod, char *oStr,BOOL flgRet); //для определенного приложения
	int CreateGPExcelApp(const char *iStr,char *oStr);
	int GetGPExcelApp(const char *iStr,char* oStr);
	
private:
	GPExcelOLEApplication* gpApp[N_EXCELAPPLICATION_ARR];
	GPOLERange* gpRange[N_EXCELRANGE_ARR];
};

#endif // !defined(AFX_GPOLEEXCEL1_H__FBFBBEC1_D659_11D4_970E_0080AD863699__INCLUDED_)
