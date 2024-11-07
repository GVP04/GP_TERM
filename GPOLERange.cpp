// GPOLERange.cpp: implementation of the GPOLERange class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GP_Term.h"
#include "GPOLERange.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPOLERange::GPOLERange()
{
	int i=0;

	while (i<N_EXCELOLERANGE_ARR)
	{
		gpRanges[i]=NULL;
		gpIdAppRanges[i]=-1;
		gpIdWorkbookRanges[i]=-1;
		gpIdWorksheetRanges[i]=-1;
		i++;
	}
}

GPOLERange::~GPOLERange()
{
	int i=0;

	while (i<N_EXCELOLERANGE_ARR)
	{
		if	(gpRanges[i]!=NULL)
		{
			delete gpRanges[i];
			gpRanges[i]=NULL;
		}
		i++;
	}
}

int GPOLERange::CreateGPExcelRange(LPDISPATCH pDisp,const char *iStr,char* oStr)
{
	int ret=-2;
	int IdApp,IdWorkbook,IdWorksheet;
	const char* pos;
	char bff[256];
	int i=0;
	pos=iStr;
	while((*pos!=',') && (*pos!=0))
	{
		bff[i]=*pos;
		i++;
		pos++;
	}
	if (*pos!=',')
		return ret;
	bff[i]=0;
	IdApp=atoi(bff); //get IdApp
	pos++;
	i=0;
	while((*pos!=',') && (*pos!=0))
	{
		bff[i]=*pos;
		i++;
		pos++;
	}
	if (*pos!=',')
		return ret;
	bff[i]=0;
	IdWorkbook=atoi(bff); //get Workbook
	pos++;
	i=0;
	while((*pos!=',') && (*pos!=0))
	{
		bff[i]=*pos;
		i++;
		pos++;
	}
	if (*pos!=',')
		return ret;
	bff[i]=0;
	IdWorksheet=atoi(bff); //get Worksheet

	i=0;
	while ((i<N_EXCELOLERANGE_ARR) && (gpRanges[i]!=NULL))
		i++;
	if (i<N_EXCELOLERANGE_ARR)
	{
		gpRanges[i]=new GPExcelOLERange(pDisp);
		gpIdAppRanges[i]=IdApp;
		gpIdWorkbookRanges[i]=IdWorkbook;
		gpIdWorksheetRanges[i]=IdWorksheet;
		if (oStr!=NULL)
			sprintf(oStr,"%d",i);
	}

	return ret;
}

int GPOLERange::CloseGPExcelRange(const char *iStr)
{
	int ret=-2;
	int IdExcelRange=-1;
	char buff[256];
	const char* pos=iStr;
	int i=0;

	while ((i<255) && (*pos!=',') && (*pos!='\0'))
	{
		buff[i]=*pos;
		i++;
		pos++;
	}
	buff[i]='\0';
	IdExcelRange=atoi(buff);
	if ((IdExcelRange>=0) && (IdExcelRange<N_EXCELOLERANGE_ARR))
	{
		if (gpRanges[IdExcelRange]!=NULL)
		{
			delete gpRanges[IdExcelRange];
			gpRanges[IdExcelRange]=NULL;
			ret=IdExcelRange;
		}
	}

	return ret;
}

int GPOLERange::DeleteRangesForApp(int IdApp)
{
	int ret=1;
	int iApp=0;

	while (iApp<N_EXCELOLERANGE_ARR)
	{
		if (gpIdAppRanges[iApp]==IdApp)
		{
			if (gpRanges[iApp]!=NULL)
			{
				delete gpRanges[iApp];
				gpRanges[iApp]=NULL;
				gpIdAppRanges[iApp]=-1;
				gpIdWorkbookRanges[iApp]=-1;
				gpIdWorksheetRanges[iApp]=-1;
			}
		}
		iApp++;
	}
	return ret;
}

int GPOLERange::DeleteRangesForWorkbook(int IdApp, const char *iStr)
{
	int ret=0;
	int IdWorkbook=-1;
	int iApp=0;
	int i=0;
	char buff[256];
	const char* pos=iStr;

	//read IdWorkbook
	while ((i<255) && (*pos!=',') && (*pos!='\0'))
	{
		buff[i]=*pos;
		pos++;
		i++;
	}
	buff[i]='\0';
	IdWorkbook=atoi(buff);
	if ((IdWorkbook>=0) && (IdWorkbook<N_EXCELWORKBOOK_ARR))
	{
		while (iApp<N_EXCELOLERANGE_ARR)
		{
			if (gpRanges[iApp]!=NULL)
			{
				if (gpIdAppRanges[iApp]==IdApp)
				{
					if (gpIdWorkbookRanges[iApp]==IdWorkbook)
					{
						delete gpRanges[iApp];
						gpRanges[iApp]=NULL;
						gpIdAppRanges[iApp]=-1;
						gpIdWorkbookRanges[iApp]=-1;
						gpIdWorksheetRanges[iApp]=-1;
						ret=1;
					}
				}
			}
			iApp++;
		}
	}
	else
		ret=-1;

	return ret;
}

int GPOLERange::DeleteRangesForWorksheet(int IdApp, const char *iStr)
{
	int ret=0;
	int IdWorkbook=-1;
	int IdWorksheet;
	int iApp=0;
	int i=0;
	char buff[256];
	const char* pos=iStr;

	//read IdWorkbook
	while ((i<255) && (*pos!=',') && (*pos!='\0'))
	{
		buff[i]=*pos;
		pos++;
		i++;
	}
	buff[i]='\0';
	IdWorkbook=atoi(buff);
	pos++;
	//read IdWorksheet
	while ((i<255) && (*pos!=',') && (*pos!='\0'))
	{
		buff[i]=*pos;
		pos++;
		i++;
	}
	buff[i]='\0';
	IdWorksheet=atoi(buff);
	if ((IdWorkbook>=0) && (IdWorkbook<N_EXCELWORKBOOK_ARR))
		if ((IdWorksheet>=0) && (IdWorksheet<N_EXCELWORKSHEET_ARR))
		{
			while (iApp<N_EXCELOLERANGE_ARR)
			{
				if (gpRanges[iApp]!=NULL)
				{
					if (gpIdAppRanges[iApp]==IdApp)
					{
						if (gpIdWorkbookRanges[iApp]==IdWorkbook)
							if (gpIdWorksheetRanges[iApp]==IdWorksheet)
							{
								delete gpRanges[iApp];
								gpRanges[iApp]=NULL;
								gpIdAppRanges[iApp]=-1;
								gpIdWorkbookRanges[iApp]=-1;
								gpIdWorksheetRanges[iApp]=-1;
								ret=1;
							}
					}
				}
				iApp++;
			}
		}
		else
			ret=-2;
	else
		ret=-1;

	return ret;
}

int GPOLERange::DoERMethod(int IdER, const char *iMethod, char *oStr,BOOL flgRet) // Excel Range Method
{
	int ret=-1;

	if ((IdER>=0) && (IdER<N_EXCELOLERANGE_ARR)) 
		if (gpRanges[IdER]!=NULL)
			ret=gpRanges[IdER]->DoMethod(iMethod,oStr,flgRet);
	return ret;
}

int GPOLERange::DoMethod(const char* iMethod,char* oStr,BOOL flgRet) //Range Method
{
	char met[150];
	strncpy(met,iMethod,145);
	met[145]=0;
	const char *pos=strchr(iMethod,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc;
	char *fn[137]={"GetCreator","Activate","GetAddIndent","SetAddIndent","GetAddress",
		"GetAddressLocal","AdvancedFilter","ApplyNames","ApplyOutlineStyles","AutoComplete",
		"AutoFilter","AutoFit","AutoFormat","AutoOutline","BorderAround",
		"Calculate","Clear","ClearContents","ClearFormats","ClearNotes",
		"ClearOutline","GetColumn","GetColumnWidth","SetColumnWidth","Consolidate",
		"Copy","CopyPicture","GetCount","CreateNames","CreatePublisher",
		"Cut","DataSeries","Delete","DialogBox","EditionOptions",
		"FillDown","FillLeft","FillRight","FillUp","GetFormula",
		"SetFormula","GetFormulaArray","SetFormulaArray","GetFormulaLabel","SetFormulaLabel",
		"GetFormulaHidden","SetFormulaHidden","GetFormulaLocal","SetFormulaLocal","GetFormulaR1C1",
		"SetFormulaR1C1","GetFormulaR1C1Local","SetFormulaR1C1Local","FunctionWizard","Group",
		"GetHasArray","GetHasFormula","GetHeight","GetHidden","SetHidden",
		"GetHorizontalAlignment","SetHorizontalAlignment","GetIndentLevel","SetIndentLevel","InsertIndent",
		"Insert","GetItem","SetItem","Justify","GetLeft",
		"GetListHeaderRows","ListNames","GetLocationInTable","GetLocked","SetLocked",
		"Merge","UnMerge","GetMergeCells","SetMergeCells","GetName",
		"SetName","NavigateArrow","NoteText","GetNumberFormat","SetNumberFormat",
		"GetNumberFormatLocal","SetNumberFormatLocal","GetOrientation","SetOrientation","GetOutlineLevel",
		"SetOutlineLevel","GetPageBreak","SetPageBreak","Parse","PasteSpecial",
		"GetPrefixCharacter","PrintOut","PrintPreview","RemoveSubtotal","Replace",
		"GetRow","GetRowHeight","SetRowHeight","Run","Select",
		"Show","ShowDependents","GetShowDetail","SetShowDetail","ShowErrors",
		"ShowPrecedents","GetShrinkToFit","SetShrinkToFit","Sort","SortSpecial",
		"Subtotal","GetSummary","GetText","GetTop",	"Ungroup","GetUseStandardHeight",
		"SetUseStandardHeight","GetUseStandardWidth","SetUseStandardWidth",	"GetValue","SetValue",
		"GetValue2","SetValue2","GetVerticalAlignment",	"SetVerticalAlignment","GetWidth",
		"GetWrapText","SetWrapText","ClearComments","GetReadingOrder","SetReadingOrder",
		"GetCountRange"};


	if (*met>='0' && *met<='9') nfunc=atoi(met);
	else
		for(nfunc=0;nfunc<137 && _stricmp(met,fn[nfunc])!=0;nfunc++); 

	int retint=-123456; 

	try
	{
		int IdRange=0;
		if ((nfunc>=0) && (nfunc<136))	
		{
			if (flgRet)
			{
				CString str;
				while (IdRange<N_EXCELOLERANGE_ARR)
				{
					if(gpRanges[IdRange]!=NULL)
					{
						gpRanges[IdRange]->DoMethod(iMethod,oStr,flgRet);
						if (0!=strcmp(str,""))
							str+=",";
						str+=oStr;
					}
					IdRange++;
				}
				oStr=new char[(int)strlen(str)+1];
				strcpy(oStr,str);
			}
			else
			{
				while (IdRange<N_EXCELOLERANGE_ARR)
				{
					if(gpRanges[IdRange]!=NULL)
						gpRanges[IdRange]->DoMethod(iMethod,oStr,flgRet);
					IdRange++;
				}
			}
		}
		else
		{
			switch(nfunc)
			{
				case 136: /*GetCountRange*/
					{
						int counter=0;
						while (IdRange<N_EXCELOLERANGE_ARR)
						{
							if (gpRanges[IdRange]!=NULL)
								counter++;
							IdRange++;
						}
						if (flgRet)
							sprintf(oStr,"%d",counter);
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
		char *str=new char [200+(int)strlen(pos)];
		#ifdef RUS
			sprintf(str,"Ошибка выполнения метода %s %s",met,pos);
		#else
			sprintf(str,"Error execution of method %s %s",met,pos);
		#endif
		AfxMessageBox(str,MB_OK|MB_ICONEXCLAMATION);
		if (oStr!=NULL) strcpy(oStr,str);
		nfunc=0xFFFFFFFFL;
		GPC.m_ErrReport.GPWriteErrorLog("GPOLERange", "DoMethod",iMethod);
		delete[] str;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
//	delete[] met;
	return nfunc;	

}

