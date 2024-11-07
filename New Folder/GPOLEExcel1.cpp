// GPOLEExcel1.cpp: implementation of the GPOLEExcel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GP_Term.h"
#include "GPOLEExcel1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPOLEExcel::GPOLEExcel()
{
	int i=0;
	while (i<N_EXCELAPPLICATION_ARR)
	{
		gpApp[i]=NULL;
		i++;
	}

	i=0;
	while (i<N_EXCELRANGE_ARR)
	{
		gpRange[i]=NULL;
		i++;
	}
}

GPOLEExcel::~GPOLEExcel()
{
	int i=0;
try
{
	while (i<N_EXCELAPPLICATION_ARR) //уничтожение объектов Excel Application
	{
		if(gpApp[i]!=NULL)
		{
			//gpApp[i]->Quit(); //excel will not die !!!
			delete gpApp[i];
			gpApp[i]=NULL;
		}
		i++;
	}

	i=0;
	while (i<N_EXCELRANGE_ARR) // удаление объектов Excel Range
	{
		if (gpRange[i]!=NULL)
		{
			delete gpRange[i];
			gpRange[i]=NULL;
		}
		i++;
	}
}
catch (...)
{
}
}

int GPOLEExcel::DoMethod(const char *iMethod, char *oStr,BOOL flgRet) // методы для всех приложений Excel Application
{
	char met[150];
	strncpy(met,iMethod,145);
	met[145]=0;
	const char *pos=strchr(iMethod,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc;
	char *fn[209]={"GetCreator","GetActivePrinter","SetActivePrinter","Calculate",
		"GetDDEAppReturnCode","ExecuteExcel4Macro","Run","SendKeys",
		"ActivateMicrosoftApp","AddCustomList","GetAlertBeforeOverwriting","SetAlertBeforeOverwriting",
		"GetAltStartupPath","SetAltStartupPath","GetAskToUpdateLinks","SetAskToUpdateLinks",
		"GetEnableAnimations","SetEnableAnimations","GetBuild","GetCalculateBeforeSave",
		"SetCalculateBeforeSave","GetCalculation","SetCalculation","GetCanPlaySounds",
		"GetCanRecordSounds","GetCaption","SetCaption","GetCellDragAndDrop",
		"SetCellDragAndDrop","CentimetersToPoints","CheckSpelling","GetClipboardFormats",
		"GetDisplayClipboardWindow","SetDisplayClipboardWindow","GetCommandUnderlines","SetCommandUnderlines",
		"GetConstrainNumeric","SetConstrainNumeric","GetCopyObjectsWithCells","SetCopyObjectsWithCells",
		"GetCursor","SetCursor","GetCustomListCount","GetCutCopyMode",
		"SetCutCopyMode","GetDataEntryMode","SetDataEntryMode","Get_Default",
		"GetDefaultFilePath","SetDefaultFilePath","DeleteChartAutoFormat","DeleteCustomList",
		"GetDisplayAlerts","SetDisplayAlerts","GetDisplayFormulaBar","SetDisplayFormulaBar",
		"GetDisplayFullScreen","SetDisplayFullScreen","GetDisplayNoteIndicator","SetDisplayNoteIndicator",
		"GetDisplayCommentIndicator","SetDisplayCommentIndicator","GetDisplayExcel4Menus","SetDisplayExcel4Menus",
		"GetDisplayRecentFiles","SetDisplayRecentFiles","GetDisplayScrollBars","SetDisplayScrollBars",
		"GetDisplayStatusBar","SetDisplayStatusBar","DoubleClick","GetEditDirectlyInCell",
		"SetEditDirectlyInCell","GetEnableAutoComplete","SetEnableAutoComplete","GetEnableCancelKey",
		"SetEnableCancelKey","GetEnableSound","SetEnableSound","FindFile",
		"GetFixedDecimal","SetFixedDecimal","GetFixedDecimalPlaces","SetFixedDecimalPlaces",
		"GetCustomListNum","GetOpenFilename","GetSaveAsFilename","Goto",
		"GetHeight","SetHeight","Help","GetIgnoreRemoteRequests",
		"SetIgnoreRemoteRequests","InchesToPoints","InputBox","GetInteractive",
		"SetInteractive","GetIteration","SetIteration","GetLeft",
		"SetLeft","GetLibraryPath","MacroOptions","MailLogoff",
		"MailLogon","GetMailSession","GetMailSystem","GetMathCoprocessorAvailable",	
		"GetMaxChange","SetMaxChange","GetMaxIterations","SetMaxIterations",
		"GetMemoryFree","GetMemoryTotal","GetMemoryUsed","GetMouseAvailable",
		"GetMoveAfterReturn","SetMoveAfterReturn","GetMoveAfterReturnDirection","SetMoveAfterReturnDirection",
		"GetName","GetNetworkTemplatesPath","GetODBCTimeout","SetODBCTimeout",
		"OnKey","OnRepeat","OnTime","OnUndo",
		"GetOnWindow","SetOnWindow","GetOperatingSystem","GetOrganizationName",
		"GetPath","GetPathSeparator","GetPivotTableSelection","SetPivotTableSelection",
		"GetPromptForSummaryInfo","SetPromptForSummaryInfo","Quit","GetRecordRelative",
		"GetReferenceStyle","SetReferenceStyle","RegisterXLL","Repeat",	
		"GetRollZoom","SetRollZoom","SaveWorkspace","GetScreenUpdating",
		"SetScreenUpdating","SetDefaultChart","GetSheetsInNewWorkbook","SetSheetsInNewWorkbook",
		"GetShowChartTipNames","SetShowChartTipNames","GetShowChartTipValues","SetShowChartTipValues",
		"GetStandardFont","SetStandardFont","GetStandardFontSize","SetStandardFontSize",
		"GetStartupPath","GetStatusBar","SetStatusBar","GetTemplatesPath",
		"GetShowToolTips","SetShowToolTips","GetTop","SetTop",
		"GetDefaultSaveFormat","SetDefaultSaveFormat","GetTransitionMenuKey","SetTransitionMenuKey",
		"GetTransitionMenuKeyAction","SetTransitionMenuKeyAction","GetTransitionNavigKeys","SetTransitionNavigKeys",
		"Undo","GetUsableHeight","GetUsableWidth","GetUserControl",
		"SetUserControl","GetUserName_","SetUserName","GetValue",
		"GetVersion","GetVisible","SetVisible","Volatile",
		"Wait","GetWidth","SetWidth","GetWindowsForPens",
		"GetWindowState","SetWindowState","GetUILanguage","SetUILanguage",
		"GetDefaultSheetDirection","SetDefaultSheetDirection","GetCursorMovement","SetCursorMovement",
		"GetControlCharacters","SetControlCharacters","GetEnableEvents","SetEnableEvents",
		"GetCountApplication","GetCountRange","RemoveAllExcelControl","RemoveExcelControl"};

	if (*met>='0' && *met<='9') nfunc=atoi(met);
	else
		for(nfunc=0;nfunc<209 && _stricmp(met,fn[nfunc])!=0;nfunc++); 

	int retint=-123456; 
	int atoipos=atoi(pos);
	int IdApp=0; //цикл должен быть по всем приложениям

	try
	{
		if ((nfunc>=0) && (nfunc<204))	
		{
			if (flgRet)
			{
				CString str;
				while (IdApp<N_EXCELAPPLICATION_ARR)
				{
					if(gpApp[IdApp]!=NULL)
					{
						gpApp[IdApp]->DoMethod(iMethod,oStr,flgRet);
						if (0!=strcmp(str,""))
							str+=",";
						str+=oStr;
					}
					IdApp++;
				}
				oStr=new char[(int)strlen(str)+1];
				strcpy(oStr,str);
			}
			else
			{
				while (IdApp<N_EXCELAPPLICATION_ARR)
				{
					if(gpApp[IdApp]!=NULL)
						gpApp[IdApp]->DoMethod(iMethod,oStr,flgRet);
					IdApp++;
				}
			}
		}
		else
		{
			switch(nfunc)
			{
				case 204: /*GetCountApplication*/
					{
						int counter=0;
						while (IdApp<N_EXCELAPPLICATION_ARR)
						{
							if (gpApp[IdApp]!=NULL)
								counter++;
							IdApp++;
						}
						if (flgRet)
							sprintf(oStr,"%d",counter);
					}
					break;
				case 205: /*GetCountRange*/
					{
						int counter=0;
						int IdRange=0;
						while (IdRange<N_EXCELRANGE_ARR)
						{
							if (gpRange[IdRange]!=NULL)
								counter++;
							IdRange++;
						}
						if (flgRet)
							sprintf(oStr,"%d",counter);
					}
					break;
				case 206: /*RemoveAllExcelControl*/
					{
						IdApp=0;
						while (IdApp<N_EXCELAPPLICATION_ARR)
						{
							if(gpApp[IdApp]!=NULL)
							{
								delete gpApp[IdApp];
								gpApp[IdApp]=NULL;
							}
							IdApp++;
						}
						int IdRange=0;
						while (IdRange<N_EXCELRANGE_ARR)
						{
							if(gpRange[IdRange]!=NULL)
							{
								delete gpRange[IdRange];
								gpRange[IdRange]=NULL;
							}
							IdRange++;
						}
					}
					break;
				case 207: /*RemoveExcelControl*/
					{
						IdApp=atoipos;
						if ((IdApp>=0) && (IdApp<N_EXCELAPPLICATION_ARR))
							if(gpApp[IdApp]!=NULL)
							{
								delete gpApp[IdApp];
								gpApp[IdApp]=NULL;
								int IdRange=0;
								while (IdRange<N_EXCELRANGE_ARR)
								{
									if (gpRange[IdRange]!=NULL)
										gpRange[IdRange]->DeleteRangesForApp(IdApp);
									IdRange++;
								}
							}

					}
					break;
				default:
					if (flgRet)		 sprintf(oStr,ErrObjSub,met);
					nfunc=0xFFFFFFFFL;
					break;
			}
		}

	}catch(...)
	{
		GPC.m_ErrReport.GPWriteWarnLog2("GPOLEExcel", "Unknown Method",iMethod);
		char *str=new char [200+(int)strlen(pos)];
		#ifdef RUS
			sprintf(str,"Ошибка выполнения метода %s %s",met,pos);
		#else
			sprintf(str,"Error execution of method %s %s",met,pos);
		#endif
		AfxMessageBox(str,MB_OK|MB_ICONEXCLAMATION);
		if (oStr!=NULL) strcpy(oStr,str);
		nfunc=0xFFFFFFFFL;
		GPC.m_ErrReport.GPWriteErrorLog("GPOLEExcel", "DoMethod",iMethod);
		delete[] str;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
//	delete[] met;
	return nfunc;
}

int GPOLEExcel::DoEAMethod(int IdApp,const char *iMethod, char *oStr,BOOL flgRet) //для определенного приложения Excel Application
{
	int ret=-2;
	if ((IdApp>=0) && (IdApp<N_EXCELAPPLICATION_ARR))
		if (gpApp[IdApp]!=NULL)
			ret=gpApp[IdApp]->DoMethod(iMethod,oStr,flgRet); 
	return ret;
}

int GPOLEExcel::DoWbMethod(int IdApp, const char *iMethod, char *oStr,BOOL flgRet) // метод для книги 
{
	int IdWorkbook;
	int ret=-1;
	char bff[256];
	int i=0;
	char *met=new char [(int)strlen(iMethod)+50];
	strcpy(met,iMethod);
	char *pos=met;
	while ((*pos!=0)&&(*pos!=',') && (i<255))	
	{
		bff[i]=*pos;
		i++;
		pos++;
	}
	if (*pos!=',')
		return ret;
	else
		pos++;
	bff[i]=0;
	IdWorkbook=atoi(bff);

	if ((IdApp>=0) && (IdApp<N_EXCELAPPLICATION_ARR)) 
		if (gpApp[IdApp]!=NULL)
			ret=gpApp[IdApp]->DoWbMethod(IdWorkbook,pos,oStr,flgRet);
	return ret;
}

int GPOLEExcel::DoWsMethod(int IdApp, const char *iMethod, char *oStr,BOOL flgRet) // метод для листа
{
	int IdWorkbook;
	int ret=-1;
	char bff[256];
	int i=0;
	char *met=new char [(int)strlen(iMethod)+50];
	strcpy(met,iMethod);
	char *pos=met;
	while ((*pos!=0)&&(*pos!=',') && (i<255))	
	{
		bff[i]=*pos;
		i++;
		pos++;
	}
	if (*pos!=',')
		return ret;
	else
		pos++;
	bff[i]=0;
	IdWorkbook=atoi(bff);

	if ((IdApp>=0) && (IdApp<N_EXCELAPPLICATION_ARR))
		if (gpApp[IdApp]!=NULL)
			ret=gpApp[IdApp]->DoWsMethod(IdWorkbook,pos,oStr,flgRet);
	return ret;
}

int GPOLEExcel::DoERMethod(int IdRange, const char *iMethod, char *oStr,BOOL flgRet) // метод для Excel Range 
{
	int IdER; //идентификатор для Excel Range 
	int ret=-1;
	char bff[300];
	int i=0;
	char *met=new char [(int)strlen(iMethod)+50];
	strcpy(met,iMethod);
	char *pos=met;
	while ((*pos!=0)&&(*pos!=',') && (i<255))	
	{
		bff[i]=*pos;
		i++;
		pos++;
	}
	if (*pos!=',')
		return ret;
	else
		pos++;
	bff[i]=0;
	IdER=atoi(bff);

	if ((IdRange>=0) && (IdRange<N_EXCELRANGE_ARR))
		if(gpRange[IdRange]!=NULL)
			ret=gpRange[IdRange]->DoERMethod(IdER,pos,oStr,flgRet);
	return ret;
}

int GPOLEExcel::DoRMethod(int IdRange, const char *iMethod, char *oStr,BOOL flgRet) // метод для Range 
{
	int ret=-1;

	if ((IdRange>=0) && (IdRange<N_EXCELRANGE_ARR))
		if(gpRange[IdRange]!=NULL)
			ret=gpRange[IdRange]->DoMethod(iMethod,oStr,flgRet);
	return ret;
}


int GPOLEExcel::CreateGPExcelApp(const char *iStr,char *oStr) // создание нового приложения Excel Application
{
	int IdApp=0;
	int intflg;
	CLSID clsid;
	HRESULT hr;


	hr=::CLSIDFromProgID(L"Excel.Application",&clsid); 
	if (FAILED(hr))
	{
		AfxMessageBox("Excel not found !");
		return -1;
	}

	m_LastScanf=sscanf( iStr, "%d", &intflg);
	while (gpApp[IdApp]!=NULL && IdApp<N_EXCELAPPLICATION_ARR)
		IdApp++;
	if (IdApp>=N_EXCELAPPLICATION_ARR)
	{
		AfxMessageBox("Have no room for Excel !");
		return -2;
	}
	
	try
	{
		gpApp[IdApp]=new GPExcelOLEApplication();
		gpApp[IdApp]->MyIdApp=IdApp; 
	}
	catch(CMemoryException e)
	{
	}
	hr=gpApp[IdApp]->CreateDispatch(clsid); 
	if (FAILED(hr))
	{
		delete gpApp[IdApp];
		gpApp[IdApp]=NULL;
		AfxMessageBox("Can't start Excel !");
		return -3;
	}
	gpApp[IdApp]->SetVisible(intflg); 
	if (oStr!=NULL)
	{
		sprintf(oStr,"%d",IdApp);
	}
	return IdApp;
}

int GPOLEExcel::GetGPExcelApp(const char *iStr,char* oStr) // подключение к уже существующему приложению Excel Application
{
	int IdApp=0;
	BOOL b;
	CLSID clsid;
	HRESULT hr;
	LPDISPATCH pDisp;
	LPUNKNOWN pUnk;


	hr=::CLSIDFromProgID(L"Excel.Application",&clsid); 
	if (FAILED(hr))
	{
		AfxMessageBox("Excel not found !");
		return -1;
	}

	m_LastScanf=sscanf( iStr, "%c", &b);
	while (gpApp[IdApp++]!=NULL && IdApp<N_EXCELAPPLICATION_ARR);
	if (IdApp>=N_EXCELAPPLICATION_ARR)
	{
		AfxMessageBox("Have no room for Excel !");
		return -2;
	}
	gpApp[IdApp]=new GPExcelOLEApplication();
	gpApp[IdApp]->MyIdApp=IdApp; 
	hr=::GetActiveObject(clsid,NULL,&pUnk); 
	if (FAILED(hr))
	{
		delete gpApp[IdApp];
		gpApp[IdApp]=NULL;
		AfxMessageBox("Can't get Excel !");
		return -3;
	}
	hr=pUnk->QueryInterface(IID_IDispatch,(void**)&pDisp);
	ASSERT(pDisp);
	gpApp[IdApp]->AttachDispatch(pDisp); 
	gpApp[IdApp]->SetVisible(b);
	if(oStr!=NULL)
		sprintf(oStr,"%d",IdApp);
	return 0;
}

int GPOLEExcel::OpenGPExcelWorkbook(const char *iStr,char *oStr) // открытие книги
{
	int IdApp=-1;
	char bff[256];
	const char* pstr=iStr;
	int i=0;
	while ((*pstr!='\0') && (*pstr!=','))
	{
		pstr++;
		bff[i]=iStr[i];
		i++;
	}
	bff[i]='\0';
	pstr++;
	m_LastScanf=sscanf(bff,"%d",&IdApp);	
	int ret=-1;

	if (IdApp>=0 && IdApp<=N_EXCELAPPLICATION_ARR)
		if(gpApp[IdApp]!=NULL)
		{
			ret=gpApp[IdApp]->OpenGPExcelWorkbook(pstr,oStr);
		}
	char retStr[100];
	sprintf(retStr,"%d\x7F%d",IdApp,ret);
//	SendRet(retStr);
	return ret;
}
int GPOLEExcel::CreateGPExcelWorkbook(const char *iStr,char *oStr) // создание новой книги
{
	int IdApp=-1;
	char bff[256];
	const char* pstr=iStr;
	int i=0;
	while ((*pstr!='\0') && (*pstr!=','))
	{
		pstr++;
		bff[i]=iStr[i];
		i++;
	}
	bff[i]='\0';
	pstr++;
	m_LastScanf=sscanf(bff,"%d",&IdApp);	
	int ret=-1;

	if (IdApp>=0 && IdApp<=N_EXCELAPPLICATION_ARR)
		if(gpApp[IdApp]!=NULL)
		{
			ret=gpApp[IdApp]->CreateGPExcelWorkbook(pstr,oStr);
		}
	char retStr[100];
	sprintf(retStr,"%d\x7F%d",IdApp,ret);
//	SendRet(retStr);
	return ret;
}

int GPOLEExcel::CloseGPExcelWorkbook(const char *iStr) // закрытие книги
{
	int IdApp=-1;
	char bff[256];
	const char* pstr=iStr;
	int i=0;
	while ((*pstr!='\0') && (*pstr!=','))
	{
		pstr++;
		bff[i]=iStr[i];
		i++;
	}
	bff[i]='\0';
	pstr++;
	m_LastScanf=sscanf(bff,"%d",&IdApp);	
	int ret=-1;

	if (IdApp>=0 && IdApp<=N_EXCELAPPLICATION_ARR)
		if(gpApp[IdApp]!=NULL)
		{
			ret=gpApp[IdApp]->CloseGPExcelWorkbook(pstr);
		}

	if (ret>=0)
	{
		// закрытие всех Ranges для данной книги
		i=0;
		while (i<N_EXCELRANGE_ARR)
		{
			if (gpRange[i]!=NULL)
			{
				gpRange[i]->DeleteRangesForWorkbook(IdApp,pstr); 
			}
			i++;
		}
	}

	char retStr[100];
	sprintf(retStr,"%d\x7F%d",IdApp,ret);
//	SendRet(retStr);
	return ret;
}

int GPOLEExcel::CreateGPExcelWorksheet(const char *iStr,char *oStr) // создание нового листа
{
	int IdApp=-1;
	char bff[256];
	const char* pstr=iStr;
	int i=0;
	while ((*pstr!='\0') && (*pstr!=','))
	{
		pstr++;
		bff[i]=iStr[i];
		i++;
	}
	bff[i]='\0';
	pstr++;
	m_LastScanf=sscanf(bff,"%d",&IdApp);	
	int ret=-1;

	if (IdApp>=0 && IdApp<=N_EXCELAPPLICATION_ARR)
		if(gpApp[IdApp]!=NULL)
		{
			ret=gpApp[IdApp]->CreateGPExcelWorksheet(pstr,oStr);
		}
	char retStr[100];
	sprintf(retStr,"%d\x7F%d",IdApp,ret);
//	SendRet(retStr);
	return ret;
}

int GPOLEExcel::CloseGPExcelWorksheet(const char *iStr) // закрытие листа
{
	int IdApp=-1;
	char bff[256];
	const char* pstr=iStr;
	int i=0;
	while ((*pstr!='\0') && (*pstr!=','))
	{
		pstr++;
		bff[i]=iStr[i];
		i++;
	}
	bff[i]='\0';
	pstr++;
	m_LastScanf=sscanf(bff,"%d",&IdApp);	
	int ret=-1;

	if (IdApp>=0 && IdApp<=N_EXCELAPPLICATION_ARR)
		if(gpApp[IdApp]!=NULL)
		{
			ret=gpApp[IdApp]->CloseGPExcelWorksheet(pstr);
		}

	if (ret>=0)
	{
		// удаление всех Ranges для заданного листа
		i=0;
		while (i<N_EXCELRANGE_ARR)
		{
			if (gpRange[i]!=NULL)
			{
				gpRange[i]->DeleteRangesForWorksheet(IdApp,pstr); 
			}
			i++;
		}
	}	
	
	char retStr[100];
	sprintf(retStr,"%d\x7F%d",IdApp,ret);
//	SendRet(retStr);
	return ret;
}

int GPOLEExcel::CreateGPExcelRange(const char *iStr,char *oStr) // создание нового Excel Range
{
	int ret=-1;
	int IdApp=-1;
	int IdRange=-1;
	int i=0;
	char buff[256];
	const char* pos=iStr;
	const char* posIdApp;
	LPDISPATCH pDisp=NULL;


	// получение IdRange
	while ((*pos!=',') && (*pos!=0))
	{
		buff[i]=*pos;
		pos++;
		i++;
	}
	buff[i]='\0';
	if (*pos==0)
		return ret;
	IdRange=atoi(buff);
	pos++;
	posIdApp=pos;
	// получение IdApp
	i=0;
	while ((*pos!=',') && (*pos!=0))
	{
		buff[i]=*pos;
		pos++;
		i++;
	}
	buff[i]='\0';
	if (*pos==0)
		return ret;
	IdApp=atoi(buff);
	pos++;
	// GetDispatchOfRange
	if ((IdApp>=0) && (IdApp<N_EXCELAPPLICATION_ARR))
	{
		if (gpApp[IdApp]!=NULL)
			pDisp=gpApp[IdApp]->CreateGPExcelRange(pos);
		if (pDisp==NULL)
			return ret;
	}
	//создание Range
	if ((IdRange<N_EXCELRANGE_ARR) && (IdRange>=0))
	{
		if (gpRange[IdRange]!=NULL)
			ret=gpRange[IdRange]->CreateGPExcelRange(pDisp,posIdApp,oStr);
	}
	return ret;
}

int GPOLEExcel::CloseGPExcelRange(const char *iStr) // удаление Excel Range
{
	int ret=-1;
	const char* pos=iStr;
	char buff[300];
	int i=0;
	int IdRange;

	while ((*pos!=',') && (*pos!='\0') && i<255)
	{
		buff[i]=*pos;
		i++;
		pos++;
	}
	buff[i]=0;

	if (*pos!=',')	return ret;

	pos++;
	IdRange=atoi(buff);
	if ((IdRange>=0) && (IdRange<N_EXCELRANGE_ARR))
	{
		if (gpRange[IdRange]!=NULL)
		{
			ret=gpRange[IdRange]->CloseGPExcelRange(pos);
		}
	}
	return ret;
}

int GPOLEExcel::CreateGPOLERange(const char *iStr,char *oStr) // создание нового Range
{
	int ret=-1;
	int i=0;

	while ((i<N_EXCELRANGE_ARR) && (gpRange[i]!=NULL))
		i++;
	if (i<N_EXCELRANGE_ARR)
	{
		gpRange[i]=new GPOLERange();
		ret=i;
	}
	if ((oStr!=NULL) && (ret>=0))
	{
		sprintf(oStr,"%d",i);
	}
	return ret;
}

int GPOLEExcel::CloseGPOLERange(const char *iStr) // удаление Range
{
	int ret=-1;
	const char* pos=iStr;
	char buff[300];
	int i=0;
	int IdRange;

	while ((*pos!=',') && (*pos!='\0') && i<255)
	{
		buff[i]=*pos;
		i++;
		pos++;
	}

	if (*pos!=',')
		return ret;
	buff[i]=0;
	pos++;
	IdRange=atoi(buff);
	if ((IdRange>=0) && (IdRange<N_EXCELRANGE_ARR))
	{
		if (gpRange[IdRange]!=NULL)
		{
			delete gpRange[IdRange];
			gpRange[IdRange]=NULL;
			ret=IdRange;
		}
	}
	return ret;
}

int GPOLEExcel::CloseGPExcelApp(const char *iStr) // закрытие Excel Application
{
	int ret=-1;
	int i=0;
	int IdApp=-1;
	char buff[256];
	const char* pos=iStr;

	while ((*pos!='\0') && (*pos!=',') && (i<255))
	{
		buff[i]=*pos;
		i++;
		pos++;
	}
	buff[i]='\0';
	IdApp=atoi(buff);

	if ((IdApp>=0) && (IdApp<N_EXCELAPPLICATION_ARR))
		if(gpApp[IdApp]!=NULL)
		{
			gpApp[IdApp]->Quit();
			delete gpApp[IdApp];
			gpApp[IdApp]=NULL;
		}

	// удаление всех Ranges для данного приложения
	i=0;
	while (i<N_EXCELRANGE_ARR)
	{
		if (gpRange[i]!=NULL)
		{
			gpRange[i]->DeleteRangesForApp(IdApp); 
		}
		i++;
	}

	return ret;
}


