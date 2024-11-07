// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "excel8.h"

#include "GP_Term.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// GPExcelOLEApplication properties

/////////////////////////////////////////////////////////////////////////////
// GPExcelOLEApplication operations
GPExcelOLEApplication::~GPExcelOLEApplication()
{
	int i=0;
	while (i<N_EXCELWORKBOOK_ARR)
	{
		if (gpWorkbooks[i]!=NULL)
		{
			delete gpWorkbooks[i];
			gpWorkbooks[i]=NULL;
		}
		i++;
	}
}

LPDISPATCH GPExcelOLEApplication::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long GPExcelOLEApplication::GetCreator()
{
	long result;
	InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetActiveCell()
{
	LPDISPATCH result;
	InvokeHelper(0x131, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetActiveChart()
{
	LPDISPATCH result;
	InvokeHelper(0xb7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString GPExcelOLEApplication::GetActivePrinter()
{
	CString result;
	InvokeHelper(0x132, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetActivePrinter(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x132, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH GPExcelOLEApplication::GetActiveSheet()
{
	LPDISPATCH result;
	InvokeHelper(0x133, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetActiveWindow()
{
	LPDISPATCH result;
	InvokeHelper(0x2f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetActiveWorkbook()
{
	LPDISPATCH result;
	InvokeHelper(0x134, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetAddIns()
{
	LPDISPATCH result;
	InvokeHelper(0x225, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetAssistant()
{
	LPDISPATCH result;
	InvokeHelper(0x59e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::Calculate()
{
	InvokeHelper(0x117, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH GPExcelOLEApplication::GetCells()
{
	LPDISPATCH result;
	InvokeHelper(0xee, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetCharts()
{
	LPDISPATCH result;
	InvokeHelper(0x79, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetColumns()
{
	LPDISPATCH result;
	InvokeHelper(0xf1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetCommandBars()
{
	LPDISPATCH result;
	InvokeHelper(0x59f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long GPExcelOLEApplication::GetDDEAppReturnCode()
{
	long result;
	InvokeHelper(0x14c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::DDEExecute(long Channel, LPCTSTR String)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x14d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Channel, String);
}

long GPExcelOLEApplication::DDEInitiate(LPCTSTR App, LPCTSTR Topic)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x14e, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		App, Topic);
	return result;
}

void GPExcelOLEApplication::DDEPoke(long Channel, const VARIANT& Item, const VARIANT& Data)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x14f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Channel, &Item, &Data);
}

VARIANT GPExcelOLEApplication::DDERequest(long Channel, LPCTSTR Item)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x150, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Channel, Item);
	return result;
}

void GPExcelOLEApplication::DDETerminate(long Channel)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x151, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Channel);
}

VARIANT GPExcelOLEApplication::Evaluate(const VARIANT& Name)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Name);
	return result;
}

VARIANT GPExcelOLEApplication::_Evaluate(const VARIANT& Name)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xfffffffb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Name);
	return result;
}

VARIANT GPExcelOLEApplication::ExecuteExcel4Macro(LPCTSTR String)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x15e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		String);
	return result;
}

LPDISPATCH GPExcelOLEApplication::Intersect(LPDISPATCH Arg1, LPDISPATCH Arg2, const VARIANT& Arg3, const VARIANT& Arg4, const VARIANT& Arg5, const VARIANT& Arg6, const VARIANT& Arg7, const VARIANT& Arg8, const VARIANT& Arg9, const VARIANT& Arg10,
		const VARIANT& Arg11, const VARIANT& Arg12, const VARIANT& Arg13, const VARIANT& Arg14, const VARIANT& Arg15, const VARIANT& Arg16, const VARIANT& Arg17, const VARIANT& Arg18, const VARIANT& Arg19, const VARIANT& Arg20,
		const VARIANT& Arg21, const VARIANT& Arg22, const VARIANT& Arg23, const VARIANT& Arg24, const VARIANT& Arg25, const VARIANT& Arg26, const VARIANT& Arg27, const VARIANT& Arg28, const VARIANT& Arg29, const VARIANT& Arg30)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x2fe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Arg1, Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetNames()
{
	LPDISPATCH result;
	InvokeHelper(0x1ba, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetRange(const VARIANT& Cell1, const VARIANT& Cell2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xc5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&Cell1, &Cell2);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetRows()
{
	LPDISPATCH result;
	InvokeHelper(0x102, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT GPExcelOLEApplication::Run(const VARIANT& Macro, const VARIANT& Arg1, const VARIANT& Arg2, const VARIANT& Arg3, const VARIANT& Arg4, const VARIANT& Arg5, const VARIANT& Arg6, const VARIANT& Arg7, const VARIANT& Arg8, const VARIANT& Arg9,
		const VARIANT& Arg10, const VARIANT& Arg11, const VARIANT& Arg12, const VARIANT& Arg13, const VARIANT& Arg14, const VARIANT& Arg15, const VARIANT& Arg16, const VARIANT& Arg17, const VARIANT& Arg18, const VARIANT& Arg19,
		const VARIANT& Arg20, const VARIANT& Arg21, const VARIANT& Arg22, const VARIANT& Arg23, const VARIANT& Arg24, const VARIANT& Arg25, const VARIANT& Arg26, const VARIANT& Arg27, const VARIANT& Arg28, const VARIANT& Arg29,
		const VARIANT& Arg30)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x103, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Macro, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
	return result;
}

VARIANT GPExcelOLEApplication::_Run2(const VARIANT& Macro, const VARIANT& Arg1, const VARIANT& Arg2, const VARIANT& Arg3, const VARIANT& Arg4, const VARIANT& Arg5, const VARIANT& Arg6, const VARIANT& Arg7, const VARIANT& Arg8, const VARIANT& Arg9,
		const VARIANT& Arg10, const VARIANT& Arg11, const VARIANT& Arg12, const VARIANT& Arg13, const VARIANT& Arg14, const VARIANT& Arg15, const VARIANT& Arg16, const VARIANT& Arg17, const VARIANT& Arg18, const VARIANT& Arg19,
		const VARIANT& Arg20, const VARIANT& Arg21, const VARIANT& Arg22, const VARIANT& Arg23, const VARIANT& Arg24, const VARIANT& Arg25, const VARIANT& Arg26, const VARIANT& Arg27, const VARIANT& Arg28, const VARIANT& Arg29,
		const VARIANT& Arg30)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x326, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Macro, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetSelection()
{
	LPDISPATCH result;
	InvokeHelper(0x93, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SendKeys(const VARIANT& Keys, const VARIANT& Wait)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x17f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Keys, Wait);
}

LPDISPATCH GPExcelOLEApplication::GetSheets()
{
	LPDISPATCH result;
	InvokeHelper(0x1e5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetThisWorkbook()
{
	LPDISPATCH result;
	InvokeHelper(0x30a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEApplication::Union(LPDISPATCH Arg1, LPDISPATCH Arg2, const VARIANT& Arg3, const VARIANT& Arg4, const VARIANT& Arg5, const VARIANT& Arg6, const VARIANT& Arg7, const VARIANT& Arg8, const VARIANT& Arg9, const VARIANT& Arg10, const VARIANT& Arg11,
		const VARIANT& Arg12, const VARIANT& Arg13, const VARIANT& Arg14, const VARIANT& Arg15, const VARIANT& Arg16, const VARIANT& Arg17, const VARIANT& Arg18, const VARIANT& Arg19, const VARIANT& Arg20, const VARIANT& Arg21,
		const VARIANT& Arg22, const VARIANT& Arg23, const VARIANT& Arg24, const VARIANT& Arg25, const VARIANT& Arg26, const VARIANT& Arg27, const VARIANT& Arg28, const VARIANT& Arg29, const VARIANT& Arg30)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x30b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Arg1, Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetWindows()
{
	LPDISPATCH result;
	InvokeHelper(0x1ae, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetWorkbooks()
{
	LPDISPATCH result;
	InvokeHelper(0x23c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetWorksheetFunction()
{
	LPDISPATCH result;
	InvokeHelper(0x5a0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetWorksheets()
{
	LPDISPATCH result;
	InvokeHelper(0x1ee, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetExcel4IntlMacroSheets()
{
	LPDISPATCH result;
	InvokeHelper(0x245, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetExcel4MacroSheets()
{
	LPDISPATCH result;
	InvokeHelper(0x243, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::ActivateMicrosoftApp(long Index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x447, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index);
}

void GPExcelOLEApplication::AddChartAutoFormat(const VARIANT& Chart, LPCTSTR Name, const VARIANT& Description)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR VTS_VARIANT;
	InvokeHelper(0xd8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Chart, Name, &Description);
}

void GPExcelOLEApplication::AddCustomList(const VARIANT& ListArray, const VARIANT& ByRow)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x30c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &ListArray, &ByRow);
}

BOOL GPExcelOLEApplication::GetAlertBeforeOverwriting()
{
	BOOL result;
	InvokeHelper(0x3a2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetAlertBeforeOverwriting(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3a2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString GPExcelOLEApplication::GetAltStartupPath()
{
	CString result;
	InvokeHelper(0x139, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetAltStartupPath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x139, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL GPExcelOLEApplication::GetAskToUpdateLinks()
{
	BOOL result;
	InvokeHelper(0x3e0, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetAskToUpdateLinks(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3e0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL GPExcelOLEApplication::GetEnableAnimations()
{
	BOOL result;
	InvokeHelper(0x49c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetEnableAnimations(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x49c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH GPExcelOLEApplication::GetAutoCorrect()
{
	LPDISPATCH result;
	InvokeHelper(0x479, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long GPExcelOLEApplication::GetBuild()
{
	long result;
	InvokeHelper(0x13a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEApplication::GetCalculateBeforeSave()
{
	BOOL result;
	InvokeHelper(0x13b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetCalculateBeforeSave(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x13b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long GPExcelOLEApplication::GetCalculation()
{
	long result;
	InvokeHelper(0x13c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetCalculation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

VARIANT GPExcelOLEApplication::GetCaller(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x13d, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

BOOL GPExcelOLEApplication::GetCanPlaySounds()
{
	BOOL result;
	InvokeHelper(0x13e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEApplication::GetCanRecordSounds()
{
	BOOL result;
	InvokeHelper(0x13f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString GPExcelOLEApplication::GetCaption()
{
	CString result;
	InvokeHelper(0x8b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetCaption(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL GPExcelOLEApplication::GetCellDragAndDrop()
{
	BOOL result;
	InvokeHelper(0x140, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetCellDragAndDrop(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x140, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

double GPExcelOLEApplication::CentimetersToPoints(double Centimeters)
{
	double result;
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x43e, DISPATCH_METHOD, VT_R8, (void*)&result, parms,
		Centimeters);
	return result;
}

BOOL GPExcelOLEApplication::CheckSpelling(LPCTSTR Word, const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1f9, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Word, &CustomDictionary, &IgnoreUppercase);
	return result;
}

VARIANT GPExcelOLEApplication::GetClipboardFormats(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x141, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

BOOL GPExcelOLEApplication::GetDisplayClipboardWindow()
{
	BOOL result;
	InvokeHelper(0x142, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetDisplayClipboardWindow(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x142, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long GPExcelOLEApplication::GetCommandUnderlines()
{
	long result;
	InvokeHelper(0x143, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetCommandUnderlines(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x143, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL GPExcelOLEApplication::GetConstrainNumeric()
{
	BOOL result;
	InvokeHelper(0x144, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetConstrainNumeric(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x144, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT GPExcelOLEApplication::ConvertFormula(const VARIANT& Formula, long FromReferenceStyle, const VARIANT& ToReferenceStyle, const VARIANT& ToAbsolute, const VARIANT& RelativeTo)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x145, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Formula, FromReferenceStyle, &ToReferenceStyle, &ToAbsolute, &RelativeTo);
	return result;
}

BOOL GPExcelOLEApplication::GetCopyObjectsWithCells()
{
	BOOL result;
	InvokeHelper(0x3df, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetCopyObjectsWithCells(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3df, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long GPExcelOLEApplication::GetCursor()
{
	long result;
	InvokeHelper(0x489, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetCursor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x489, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long GPExcelOLEApplication::GetCustomListCount()
{
	long result;
	InvokeHelper(0x313, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long GPExcelOLEApplication::GetCutCopyMode()
{
	long result;
	InvokeHelper(0x14a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetCutCopyMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x14a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long GPExcelOLEApplication::GetDataEntryMode()
{
	long result;
	InvokeHelper(0x14b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetDataEntryMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x14b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString GPExcelOLEApplication::Get_Default()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString GPExcelOLEApplication::GetDefaultFilePath()
{
	CString result;
	InvokeHelper(0x40e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetDefaultFilePath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x40e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void GPExcelOLEApplication::DeleteChartAutoFormat(LPCTSTR Name)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xd9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name);
}

void GPExcelOLEApplication::DeleteCustomList(long ListNum)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x30f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ListNum);
}

LPDISPATCH GPExcelOLEApplication::GetDialogs()
{
	LPDISPATCH result;
	InvokeHelper(0x2f9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEApplication::GetDisplayAlerts()
{
	BOOL result;
	InvokeHelper(0x157, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetDisplayAlerts(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x157, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL GPExcelOLEApplication::GetDisplayFormulaBar()
{
	BOOL result;
	InvokeHelper(0x158, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetDisplayFormulaBar(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x158, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL GPExcelOLEApplication::GetDisplayFullScreen()
{
	BOOL result;
	InvokeHelper(0x425, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetDisplayFullScreen(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x425, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL GPExcelOLEApplication::GetDisplayNoteIndicator()
{
	BOOL result;
	InvokeHelper(0x159, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetDisplayNoteIndicator(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x159, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long GPExcelOLEApplication::GetDisplayCommentIndicator()
{
	long result;
	InvokeHelper(0x4ac, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetDisplayCommentIndicator(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4ac, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL GPExcelOLEApplication::GetDisplayExcel4Menus()
{
	BOOL result;
	InvokeHelper(0x39f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetDisplayExcel4Menus(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x39f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL GPExcelOLEApplication::GetDisplayRecentFiles()
{
	BOOL result;
	InvokeHelper(0x39e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetDisplayRecentFiles(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x39e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL GPExcelOLEApplication::GetDisplayScrollBars()
{
	BOOL result;
	InvokeHelper(0x15a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetDisplayScrollBars(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x15a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL GPExcelOLEApplication::GetDisplayStatusBar()
{
	BOOL result;
	InvokeHelper(0x15b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetDisplayStatusBar(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x15b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void GPExcelOLEApplication::DoubleClick()
{
	InvokeHelper(0x15d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL GPExcelOLEApplication::GetEditDirectlyInCell()
{
	BOOL result;
	InvokeHelper(0x3a1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetEditDirectlyInCell(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3a1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL GPExcelOLEApplication::GetEnableAutoComplete()
{
	BOOL result;
	InvokeHelper(0x49b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetEnableAutoComplete(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x49b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long GPExcelOLEApplication::GetEnableCancelKey()
{
	long result;
	InvokeHelper(0x448, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetEnableCancelKey(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x448, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL GPExcelOLEApplication::GetEnableSound()
{
	BOOL result;
	InvokeHelper(0x4ad, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetEnableSound(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x4ad, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT GPExcelOLEApplication::GetFileConverters(const VARIANT& Index1, const VARIANT& Index2)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x3a3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		&Index1, &Index2);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetFileSearch()
{
	LPDISPATCH result;
	InvokeHelper(0x4b0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetFileFind()
{
	LPDISPATCH result;
	InvokeHelper(0x4b1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::FindFile()
{
	InvokeHelper(0x42c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL GPExcelOLEApplication::GetFixedDecimal()
{
	BOOL result;
	InvokeHelper(0x15f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetFixedDecimal(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x15f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long GPExcelOLEApplication::GetFixedDecimalPlaces()
{
	long result;
	InvokeHelper(0x160, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetFixedDecimalPlaces(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x160, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

VARIANT GPExcelOLEApplication::GetCustomListContents(long ListNum)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x312, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		ListNum);
	return result;
}

long GPExcelOLEApplication::GetCustomListNum(const VARIANT& ListArray)
{
	long result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x311, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		&ListArray);
	return result;
}

VARIANT GPExcelOLEApplication::GetOpenFilename(const VARIANT& FileFilter, const VARIANT& FilterIndex, const VARIANT& Title, const VARIANT& ButtonText, const VARIANT& MultiSelect)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x433, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&FileFilter, &FilterIndex, &Title, &ButtonText, &MultiSelect);
	return result;
}

VARIANT GPExcelOLEApplication::GetSaveAsFilename(const VARIANT& InitialFilename, const VARIANT& FileFilter, const VARIANT& FilterIndex, const VARIANT& Title, const VARIANT& ButtonText)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x434, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&InitialFilename, &FileFilter, &FilterIndex, &Title, &ButtonText);
	return result;
}

void GPExcelOLEApplication::Goto(const VARIANT& Reference, const VARIANT& Scroll)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1db, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Reference, &Scroll);
}

double GPExcelOLEApplication::GetHeight()
{
	double result;
	InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetHeight(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x7b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void GPExcelOLEApplication::Help(const VARIANT& HelpFile, const VARIANT& HelpContextID)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x162, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &HelpFile, &HelpContextID);
}

BOOL GPExcelOLEApplication::GetIgnoreRemoteRequests()
{
	BOOL result;
	InvokeHelper(0x164, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetIgnoreRemoteRequests(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x164, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

double GPExcelOLEApplication::InchesToPoints(double Inches)
{
	double result;
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x43f, DISPATCH_METHOD, VT_R8, (void*)&result, parms,
		Inches);
	return result;
}

VARIANT GPExcelOLEApplication::InputBox(LPCTSTR Prompt, const VARIANT& Title, const VARIANT& Default, const VARIANT& Left, const VARIANT& Top, const VARIANT& HelpFile, const VARIANT& HelpContextID, const VARIANT& Type)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x165, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Prompt, &Title, &Default, &Left, &Top, &HelpFile, &HelpContextID, &Type);
	return result;
}

BOOL GPExcelOLEApplication::GetInteractive()
{
	BOOL result;
	InvokeHelper(0x169, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetInteractive(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x169, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT GPExcelOLEApplication::GetInternational(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x16a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

BOOL GPExcelOLEApplication::GetIteration()
{
	BOOL result;
	InvokeHelper(0x16b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetIteration(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x16b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

double GPExcelOLEApplication::GetLeft()
{
	double result;
	InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetLeft(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x7f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString GPExcelOLEApplication::GetLibraryPath()
{
	CString result;
	InvokeHelper(0x16e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::MacroOptions(const VARIANT& Macro, const VARIANT& Description, const VARIANT& HasMenu, const VARIANT& MenuText, const VARIANT& HasShortcutKey, const VARIANT& ShortcutKey, const VARIANT& Category, const VARIANT& StatusBar,
		const VARIANT& HelpContextID, const VARIANT& HelpFile)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x46f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Macro, &Description, &HasMenu, &MenuText, &HasShortcutKey, &ShortcutKey, &Category, &StatusBar, &HelpContextID, &HelpFile);
}

void GPExcelOLEApplication::MailLogoff()
{
	InvokeHelper(0x3b1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void GPExcelOLEApplication::MailLogon(const VARIANT& Name, const VARIANT& Password, const VARIANT& DownloadNewMail)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x3af, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Name, &Password, &DownloadNewMail);
}

VARIANT GPExcelOLEApplication::GetMailSession()
{
	VARIANT result;
	InvokeHelper(0x3ae, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

long GPExcelOLEApplication::GetMailSystem()
{
	long result;
	InvokeHelper(0x3cb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEApplication::GetMathCoprocessorAvailable()
{
	BOOL result;
	InvokeHelper(0x16f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

double GPExcelOLEApplication::GetMaxChange()
{
	double result;
	InvokeHelper(0x170, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetMaxChange(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x170, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long GPExcelOLEApplication::GetMaxIterations()
{
	long result;
	InvokeHelper(0x171, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetMaxIterations(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x171, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long GPExcelOLEApplication::GetMemoryFree()
{
	long result;
	InvokeHelper(0x172, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long GPExcelOLEApplication::GetMemoryTotal()
{
	long result;
	InvokeHelper(0x173, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long GPExcelOLEApplication::GetMemoryUsed()
{
	long result;
	InvokeHelper(0x174, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEApplication::GetMouseAvailable()
{
	BOOL result;
	InvokeHelper(0x175, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEApplication::GetMoveAfterReturn()
{
	BOOL result;
	InvokeHelper(0x176, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetMoveAfterReturn(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x176, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long GPExcelOLEApplication::GetMoveAfterReturnDirection()
{
	long result;
	InvokeHelper(0x478, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetMoveAfterReturnDirection(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x478, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH GPExcelOLEApplication::GetRecentFiles()
{
	LPDISPATCH result;
	InvokeHelper(0x4b2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString GPExcelOLEApplication::GetName()
{
	CString result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEApplication::NextLetter()
{
	LPDISPATCH result;
	InvokeHelper(0x3cc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString GPExcelOLEApplication::GetNetworkTemplatesPath()
{
	CString result;
	InvokeHelper(0x184, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetODBCErrors()
{
	LPDISPATCH result;
	InvokeHelper(0x4b3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long GPExcelOLEApplication::GetODBCTimeout()
{
	long result;
	InvokeHelper(0x4b4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetODBCTimeout(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4b4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void GPExcelOLEApplication::OnKey(LPCTSTR Key, const VARIANT& Procedure)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x272, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Key, &Procedure);
}

void GPExcelOLEApplication::OnRepeat(LPCTSTR Text, LPCTSTR Procedure)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x301, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Text, Procedure);
}

void GPExcelOLEApplication::OnTime(const VARIANT& EarliestTime, LPCTSTR Procedure, const VARIANT& LatestTime, const VARIANT& Schedule)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x270, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &EarliestTime, Procedure, &LatestTime, &Schedule);
}

void GPExcelOLEApplication::OnUndo(LPCTSTR Text, LPCTSTR Procedure)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x302, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Text, Procedure);
}

CString GPExcelOLEApplication::GetOnWindow()
{
	CString result;
	InvokeHelper(0x26f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetOnWindow(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x26f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString GPExcelOLEApplication::GetOperatingSystem()
{
	CString result;
	InvokeHelper(0x177, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString GPExcelOLEApplication::GetOrganizationName()
{
	CString result;
	InvokeHelper(0x178, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString GPExcelOLEApplication::GetPath()
{
	CString result;
	InvokeHelper(0x123, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString GPExcelOLEApplication::GetPathSeparator()
{
	CString result;
	InvokeHelper(0x179, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT GPExcelOLEApplication::GetPreviousSelections(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x17a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

BOOL GPExcelOLEApplication::GetPivotTableSelection()
{
	BOOL result;
	InvokeHelper(0x4b5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetPivotTableSelection(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x4b5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL GPExcelOLEApplication::GetPromptForSummaryInfo()
{
	BOOL result;
	InvokeHelper(0x426, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetPromptForSummaryInfo(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x426, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void GPExcelOLEApplication::Quit()
{
	InvokeHelper(0x12e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void GPExcelOLEApplication::RecordMacro(const VARIANT& BasicCode, const VARIANT& XlmCode)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x305, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasicCode, &XlmCode);
}

BOOL GPExcelOLEApplication::GetRecordRelative()
{
	BOOL result;
	InvokeHelper(0x17b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long GPExcelOLEApplication::GetReferenceStyle()
{
	long result;
	InvokeHelper(0x17c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetReferenceStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

VARIANT GPExcelOLEApplication::GetRegisteredFunctions(const VARIANT& Index1, const VARIANT& Index2)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x307, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		&Index1, &Index2);
	return result;
}

BOOL GPExcelOLEApplication::RegisterXLL(LPCTSTR Filename)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Filename);
	return result;
}

void GPExcelOLEApplication::Repeat()
{
	InvokeHelper(0x12d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL GPExcelOLEApplication::GetRollZoom()
{
	BOOL result;
	InvokeHelper(0x4b6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetRollZoom(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x4b6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void GPExcelOLEApplication::SaveWorkspace(const VARIANT& Filename)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xd4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Filename);
}

BOOL GPExcelOLEApplication::GetScreenUpdating()
{
	BOOL result;
	InvokeHelper(0x17e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetScreenUpdating(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x17e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void GPExcelOLEApplication::SetDefaultChart(const VARIANT& FormatName, const VARIANT& Gallery)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xdb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FormatName, &Gallery);
}

long GPExcelOLEApplication::GetSheetsInNewWorkbook()
{
	long result;
	InvokeHelper(0x3e1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetSheetsInNewWorkbook(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3e1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL GPExcelOLEApplication::GetShowChartTipNames()
{
	BOOL result;
	InvokeHelper(0x4b7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetShowChartTipNames(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x4b7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL GPExcelOLEApplication::GetShowChartTipValues()
{
	BOOL result;
	InvokeHelper(0x4b8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetShowChartTipValues(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x4b8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString GPExcelOLEApplication::GetStandardFont()
{
	CString result;
	InvokeHelper(0x39c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetStandardFont(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x39c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double GPExcelOLEApplication::GetStandardFontSize()
{
	double result;
	InvokeHelper(0x39d, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetStandardFontSize(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x39d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString GPExcelOLEApplication::GetStartupPath()
{
	CString result;
	InvokeHelper(0x181, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT GPExcelOLEApplication::GetStatusBar()
{
	VARIANT result;
	InvokeHelper(0x182, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetStatusBar(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x182, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

CString GPExcelOLEApplication::GetTemplatesPath()
{
	CString result;
	InvokeHelper(0x17d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEApplication::GetShowToolTips()
{
	BOOL result;
	InvokeHelper(0x183, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetShowToolTips(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x183, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

double GPExcelOLEApplication::GetTop()
{
	double result;
	InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetTop(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x7e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long GPExcelOLEApplication::GetDefaultSaveFormat()
{
	long result;
	InvokeHelper(0x4b9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetDefaultSaveFormat(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4b9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString GPExcelOLEApplication::GetTransitionMenuKey()
{
	CString result;
	InvokeHelper(0x136, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetTransitionMenuKey(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x136, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long GPExcelOLEApplication::GetTransitionMenuKeyAction()
{
	long result;
	InvokeHelper(0x137, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetTransitionMenuKeyAction(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x137, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL GPExcelOLEApplication::GetTransitionNavigKeys()
{
	BOOL result;
	InvokeHelper(0x138, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetTransitionNavigKeys(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x138, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void GPExcelOLEApplication::Undo()
{
	InvokeHelper(0x12f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

double GPExcelOLEApplication::GetUsableHeight()
{
	double result;
	InvokeHelper(0x185, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

double GPExcelOLEApplication::GetUsableWidth()
{
	double result;
	InvokeHelper(0x186, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEApplication::GetUserControl()
{
	BOOL result;
	InvokeHelper(0x4ba, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetUserControl(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x4ba, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString GPExcelOLEApplication::GetUserName_()
{
	CString result;
	InvokeHelper(0x187, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetUserName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x187, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString GPExcelOLEApplication::GetValue()
{
	CString result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEApplication::GetVbe()
{
	LPDISPATCH result;
	InvokeHelper(0x4bb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString GPExcelOLEApplication::GetVersion()
{
	CString result;
	InvokeHelper(0x188, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEApplication::GetVisible()
{
	BOOL result;
	InvokeHelper(0x22e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x22e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void GPExcelOLEApplication::Volatile(const VARIANT& Volatile)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x314, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Volatile);
}

void GPExcelOLEApplication::Wait(const VARIANT& Time)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x189, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Time);
}

double GPExcelOLEApplication::GetWidth()
{
	double result;
	InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetWidth(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x7a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL GPExcelOLEApplication::GetWindowsForPens()
{
	BOOL result;
	InvokeHelper(0x18b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long GPExcelOLEApplication::GetWindowState()
{
	long result;
	InvokeHelper(0x18c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetWindowState(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x18c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long GPExcelOLEApplication::GetUILanguage()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetUILanguage(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long GPExcelOLEApplication::GetDefaultSheetDirection()
{
	long result;
	InvokeHelper(0xe5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetDefaultSheetDirection(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long GPExcelOLEApplication::GetCursorMovement()
{
	long result;
	InvokeHelper(0xe8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetCursorMovement(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long GPExcelOLEApplication::GetControlCharacters()
{
	long result;
	InvokeHelper(0xe9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetControlCharacters(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL GPExcelOLEApplication::GetEnableEvents()
{
	BOOL result;
	InvokeHelper(0x4bc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEApplication::SetEnableEvents(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x4bc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

// добавленные функции
LPDISPATCH GPExcelOLEApplication::CreateGPExcelRange(const char *iStr) // создание Excel Range
{
	LPDISPATCH pDisp=NULL;
	int IdWorkbook;
	int i=0;
	char buff[256];
	const char* pos=iStr;

	// получение IdWorkbook
	while ((*pos!=',') && (*pos!=0))
	{
		buff[i]=*pos;
		pos++;
		i++;
	}
	buff[i]='\0';
	if (*pos==0)
		return pDisp;
	IdWorkbook=atoi(buff);
	pos++;
	// получение Dispatch'а Range
	if ((IdWorkbook>=0) && (IdWorkbook<N_EXCELWORKBOOK_ARR))
	{
		if (gpWorkbooks[IdWorkbook]!=NULL)
			pDisp=gpWorkbooks[IdWorkbook]->CreateGPExcelRange(pos);
	}

	return pDisp;
}

int GPExcelOLEApplication::OpenGPExcelWorkbook(const char *iStr,char* oStr) // открытие книги
{
	int ret=-2;
	int IdWorkbook=0;
	Workbooks wrk;

	wrk.AttachDispatch(GetWorkbooks());
	while ((IdWorkbook<N_EXCELWORKBOOK_ARR) && (gpWorkbooks[IdWorkbook]!=NULL))
		IdWorkbook++;
	if (IdWorkbook<N_EXCELWORKBOOK_ARR)
	{
		LPDISPATCH pDisp=NULL;
		pDisp=wrk.Add(COleVariant(iStr));
		ASSERT(pDisp);
		gpWorkbooks[IdWorkbook]=new GPExcelOLEWorkbook(pDisp);
		gpWorkbooks[IdWorkbook]->MyIdApp=MyIdApp;
		gpWorkbooks[IdWorkbook]->MyIdWorkbook=IdWorkbook;
		gpWorkbooks[IdWorkbook]->RefreshGPExcelWorksheets();
		ret= IdWorkbook;
		if (oStr!=NULL)
		{
			sprintf(oStr,"%d",IdWorkbook);
		}
	}
	else
	{
		//error
	}
	return ret;
}

int GPExcelOLEApplication::CreateGPExcelWorkbook(const char *iStr,char* oStr) // создание книги
{
	int ret=-2;
	int IdWorkbook=0;
	int numoflists;
	char bff[256];
	const char* pstr=iStr;
	int i=0;
	Workbooks wrk;
	while ((*pstr!='\0') && (*pstr!=','))
	{
		pstr++;
		bff[i]=iStr[i];
		i++;
	}
	bff[i]='\0';
	m_LastScanf=sscanf(bff,"%d",&numoflists);
	if (numoflists<1)
		return ret;

	wrk.AttachDispatch(GetWorkbooks());
	if(wrk.m_lpDispatch==NULL)
		return ret;
	while ((IdWorkbook<N_EXCELWORKBOOK_ARR) && (gpWorkbooks[IdWorkbook]!=NULL))
		IdWorkbook++;
	if (IdWorkbook<N_EXCELWORKBOOK_ARR)
	{
		COleVariant var(long(0));
		LPDISPATCH pDisp=NULL;
		var.lVal=numoflists;
		pDisp=wrk.Add(var);
		if(pDisp==NULL)
			return ret;
		gpWorkbooks[IdWorkbook]=new GPExcelOLEWorkbook(pDisp);
		gpWorkbooks[IdWorkbook]->MyIdApp=MyIdApp;
		gpWorkbooks[IdWorkbook]->MyIdWorkbook=IdWorkbook;
		gpWorkbooks[IdWorkbook]->RefreshGPExcelWorksheets(); // считывание созданных листов в массив листов
		ret= IdWorkbook;
		if (oStr!=NULL)
		{
			sprintf(oStr,"%d",IdWorkbook);
		}
	}
	else
	{
		//error
	}
	return ret;
}

int GPExcelOLEApplication::CloseGPExcelWorkbook(const char *iStr) // закрытие книги
{
	int ret=-2;
	int IdWorkbook=-1;
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
	m_LastScanf=sscanf(bff,"%d",&IdWorkbook);
	if (IdWorkbook<0)
		return ret;

	if (IdWorkbook<N_EXCELWORKBOOK_ARR)
		if(gpWorkbooks[IdWorkbook]!=NULL)
		{

		  COleVariant
                 covTrue((short)TRUE),
                 covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

		  gpWorkbooks[IdWorkbook]->Close(covTrue,covOptional,covOptional);
		  delete gpWorkbooks[IdWorkbook];
		  gpWorkbooks[IdWorkbook]=NULL;
		  ret= IdWorkbook;
		}
	    else
		{
		//error
		}
	else
	{
		//error
	}

	return ret;
}

int GPExcelOLEApplication::CreateGPExcelWorksheet(const char *iStr,char* oStr) // создание листа
{
	int IdWorkbook=0;
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
	m_LastScanf=sscanf(bff,"%d",&IdWorkbook);
	int ret=-1;

	if (IdWorkbook>=0 && IdWorkbook<=N_EXCELWORKBOOK_ARR)
		if(gpWorkbooks[IdWorkbook]!=NULL)
		{
			ret=gpWorkbooks[IdWorkbook]->CreateGPExcelWorksheet(pstr,oStr);
		}

	return ret;
}

int GPExcelOLEApplication::CloseGPExcelWorksheet(const char *iStr) // закрытие листа
{
	int IdWorkbook=0;
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
	m_LastScanf=sscanf(bff,"%d",&IdWorkbook);
	int ret=-1;

	if (IdWorkbook>=0 && IdWorkbook<=N_EXCELWORKBOOK_ARR)
		if (gpWorkbooks[IdWorkbook]!=NULL)
		{
			ret=gpWorkbooks[IdWorkbook]->CloseGPExcelWorksheet(pstr);
		}
	return ret;
}

int GPExcelOLEApplication::DoMethod(const char* iMethod, char* oStr,BOOL flgRet) // методы Excel Application
{
//	char *met=new char [(int)strlen(iMethod)+50];
	char met[200];
	strncpy(met,iMethod,195);met[195]=0;
	const char *pos=strchr(iMethod,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc;
	char *fn[205]={"GetCreator","GetActivePrinter","SetActivePrinter","Calculate",
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
		"GetCountWorkbook"};

	if (*met>='0' && *met<='9') nfunc=atoi(met);
	else
		for(nfunc=0;nfunc<205 && _stricmp(met,fn[nfunc])!=0;nfunc++);

	int retint=-123456;
	int atoipos=atoi(pos);

	try
	{
		switch(nfunc)
		{
		case 0:	/*GetCreator*/
				{
					long val=GetCreator();
					if(flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 1:	/*GetActivePrinter*/
				{
					CString val=GetActivePrinter();
					strcpy(oStr,val);
				}
				break;
		case 2:	/*SetActivePrinter*/
				SetActivePrinter(pos);
				break;
		case 3:	/*Calculate*/
				Calculate();
				break;
		case 4:	/*GetDDEAppReturnCode*/
				{
					long val=GetDDEAppReturnCode();
					if(flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 5:	/*ExecuteExcel4Macro*/
				{
					COleVariant val=ExecuteExcel4Macro(pos);
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 6:	/*Run*/
				{
					CString iStr1=pos,oStr1;
					ConvertStringToString(iStr1,oStr1);
					COleVariant val=RunEx(oStr1);
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 7:	/*SendKeys*/
				SendKeysEx(pos);
				break;
		case 8: /*ActivateMicrosoftApp*/
				ActivateMicrosoftApp(atoipos);
				break;
		case 9:	/*AddCustomList*/
				{ //not working
					COleVariant varbool(short(TRUE));
					COleVariant varlist;
					CString iStr1=pos,oStr1;
					ConvertStringToString(iStr1,oStr1);
					ConvertToArray(oStr1,varlist,"0x1",0);
					AddCustomList(varlist,varbool);
				}
				break;
		case 10:	/*GetAlertBeforeOverwriting*/
				{
					BOOL val=GetAlertBeforeOverwriting();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 11:	/*SetAlertBeforeOverwriting*/
				SetAlertBeforeOverwriting(atoipos);
				break;
		case 12:	/*GetAltStartupPath*/
				{
					CString val=GetAltStartupPath();
					if (flgRet)
					{
						oStr=new char[(int)strlen(val)+1];
						strcpy(oStr,val);
					}
				}
				break;
		case 13:	/*SetAltStartupPath*/
				SetAltStartupPath(oStr);
				break;
		case 14:	/*GetAskToUpdateLinks*/
				{
					BOOL val=GetAskToUpdateLinks();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 15:	/*SetAskToUpdateLinks*/
				SetAskToUpdateLinks(atoipos);
				break;
		case 16:	/*GetEnableAnimations*/
				{
					BOOL val=GetEnableAnimations();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 17:	/*SetEnableAnimations*/
				SetEnableAnimations(atoipos);
				break;
		case 18:	/*GetBuild*/
				{
					long val=GetBuild();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 19:	/*GetCalculateBeforeSave*/
				{
					BOOL val=GetCalculateBeforeSave();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 20:	/*SetCalculateBeforeSave*/
				SetCalculateBeforeSave(atoipos);
				break;
		case 21:	/*GetCalculation*/
				{
					long val=GetCalculation();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 22:	/*SetCalculation*/
				SetCalculation(atoipos);
				break;
		case 23:	/*GetCanPlaySounds*/
				{
					BOOL val=GetCanPlaySounds();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 24:	/*GetCanRecordSounds*/
				{
					BOOL val=GetCanRecordSounds();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 25:	/*GetCaption*/
				{
					CString val=GetCaption();
					if (flgRet)
					{
						oStr=new char[(int)strlen(val)+1];
						strcpy(oStr,val);
					}
				}
				break;
		case 26:	/*SetCaption*/
				SetCaption(pos);
				break;
		case 27:	/*GetCellDragAndDrop*/
				{
					BOOL val=GetCellDragAndDrop();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 28:	/*SetCellDragAndDrop*/
				SetCellDragAndDrop(atoipos);
				break;
		case 29:	/*CentimetersToPoints*/
				{
					double val=CentimetersToPoints(atof(pos));
					if (flgRet)
						sprintf(oStr,"%f",val);
				}
				break;
		case 30:	/*CheckSpelling*/
				{
					BOOL val=CheckSpellingEx(pos);
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 31:	/*GetClipboardFormats*/
				{
					COleVariant val;
					if (*pos!=0)
						val=GetClipboardFormats(COleVariant(pos));
					else
						val=GetClipboardFormats(COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR));
					if (flgRet)
					{
						CString str="";
						switch(val.vt)
						{
							case VT_NULL:	break;
							case VT_ARRAY:	ConvertToString(val,str,",");
											break;
						}
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 32:	/*GetDisplayClipboardWindow*/
				{
					BOOL val=GetDisplayClipboardWindow();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 33:/*SetDisplayClipboardWindow*/
				SetDisplayClipboardWindow(atoipos);
				break;
		case 34:	/*GetCommandUnderlines*/
				{
					long val=GetCommandUnderlines();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 35:/*SetCommandUnderlines*/
				SetCommandUnderlines(atoipos);
				break;
		case 36:	/*GetConstrainNumeric*/
				{
					BOOL val=GetConstrainNumeric();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 37:/*SetConstrainNumeric*/
				SetConstrainNumeric(atoipos);
				break;
		case 38:	/*GetCopyObjectsWithCells*/
				{
					BOOL val=GetCopyObjectsWithCells();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 39:/*SetCopyObjectsWithCells*/
				SetCopyObjectsWithCells(atoipos);
				break;
		case 40:	/*GetCursor*/
				{
					long val=GetCursor();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 41:/*SetCursor*/
				SetCursor(atoipos);
				break;
		case 42:	/*GetCustomListCount*/
				{
					long val=GetCustomListCount();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 43:	/*GetCutCopyMode*/
				{
					long val=GetCutCopyMode();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 44:	/*SetCutCopyMode*/
				SetCutCopyMode(atoipos);
				break;
		case 45:	/*GetDataEntryMode*/
				{
					long val=GetDataEntryMode();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 46:	/*SetDataEntryMode*/
				SetDataEntryMode(atoipos);
				break;
		case 47:	/*Get_Default*/
				{
					CString val=Get_Default();
					if (flgRet)
					{
						oStr=new char[(int)strlen(val)+1];
						strcpy(oStr,val);
					}
				}
				break;
		case 48:	/*GetDefaultFilePath*/
				{
					CString val=GetDefaultFilePath();
					if (flgRet)
					{
						oStr=new char[(int)strlen(val)+1];
						strcpy(oStr,val);
					}
				}
				break;
		case 49:	/*SetDefaultFilePath*/
				SetDefaultFilePath(pos);
				break;
		case 50:	/*DeleteChartAutoFormat*/
				DeleteChartAutoFormat(pos);
				break;
		case 51:	/*DeleteCustomList*/
				DeleteCustomList(atoipos);
				break;
		case 52:	/*GetDisplayAlerts*/
				{
					BOOL val=GetDisplayAlerts();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 53:/*SetDisplayAlerts*/
				SetDisplayAlerts(atoipos);
				break;
		case 54:	/*GetDisplayFormulaBar*/
				{
					BOOL val=GetDisplayFormulaBar();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 55:/*SetDisplayFormulaBar*/
				SetDisplayFormulaBar(atoipos);
				break;
		case 56:	/*GetDisplayFullScreen*/
				{
					BOOL val=GetDisplayFullScreen();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 57:/*SetDisplayFullScreen*/
				SetDisplayFullScreen(atoipos);
				break;
		case 58:	/*GetDisplayNoteIndicator*/
				{
					BOOL val=GetDisplayNoteIndicator();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 59:/*SetDisplayNoteIndicator*/
				SetDisplayNoteIndicator(atoipos);
				break;
		case 60:	/*GetDisplayCommentIndicator*/
				{
					long val=GetDisplayCommentIndicator();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 61:/*SetDisplayCommentIndicator*/
				SetDisplayCommentIndicator(atoipos);
				break;
		case 62:	/*GetDisplayExcel4Menus*/
				{
					BOOL val=GetDisplayExcel4Menus();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 63:/*SetDisplayExcel4Menus*/
				SetDisplayExcel4Menus(atoipos);
				break;
		case 64:	/*GetDisplayRecentFiles*/
				{
					BOOL val=GetDisplayRecentFiles();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 65:/*SetDisplayRecentFiles*/
				SetDisplayRecentFiles(atoipos);
				break;
		case 66:	/*GetDisplayScrollBars*/
				{
					BOOL val=GetDisplayScrollBars();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 67:/*SetDisplayScrollBars*/
				SetDisplayScrollBars(atoipos);
				break;
		case 68:	/*GetDisplayStatusBar*/
				{
					BOOL val=GetDisplayStatusBar();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 69:/*SetDisplayStatusBar*/
				SetDisplayStatusBar(atoipos);
				break;
		case 70:	/*DoubleClick*/
				DoubleClick();
				break;
		case 71:	/*GetEditDirectlyInCell*/
				{
					BOOL val=GetEditDirectlyInCell();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 72:/*SetEditDirectlyInCell*/
				SetEditDirectlyInCell(atoipos);
				break;
		case 73:	/*GetEnableAutoComplete*/
				{
					BOOL val=GetEnableAutoComplete();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 74:/*SetEnableAutoComplete*/
				SetEnableAutoComplete(atoipos);
				break;
		case 75:	/*GetEnableCancelKey*/
				{
					long val=GetEnableCancelKey();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 76:/*SetEnableCancelKey*/
				SetEnableCancelKey(atoipos);
				break;
		case 77:	/*GetEnableSound*/
				{
					BOOL val=GetEnableSound();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 78:/*SetEnableSound*/
				SetEnableSound(atoipos);
				break;
		case 79:	/*FindFile*/
				FindFile();
				break;
		case 80:	/*GetFixedDecimal*/
				{
					BOOL val=GetFixedDecimal();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 81:/*SetFixedDecimal*/
				SetFixedDecimal(atoipos);
				break;
		case 82:	/*GetFixedDecimalPlaces*/
				{
					long val=GetFixedDecimalPlaces();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 83:/*SetFixedDecimalPlaces*/
				SetFixedDecimalPlaces(atoipos);
				break;
		case 84:	/*GetCustomListNum*/
				{
					COleVariant varlist;
					CString iStr1=pos,oStr1;
					ConvertStringToString(iStr1,oStr1);
					ConvertToArray(oStr1,varlist,"0x1",0);
					long val=GetCustomListNum(varlist);
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 85:	/*GetOpenFilename*/
				{
					COleVariant val=GetOpenFilenameEx(pos);
					if (flgRet)
					{
						CString str="";// by default
						if (val.vt==VT_BSTR)
							ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 86:	/*GetSaveAsFilename*/
				{
					COleVariant val=GetSaveAsFilenameEx(pos);
					if (flgRet)
					{
						CString str="";// by default
						if (val.vt==VT_BSTR)
							ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 87:	/*Goto*/
				{
					if (*pos!=0)
					{
						char buff2[256];
						int i=0;
						while ((i<255) && (*pos!=0) && (*pos!=','))
						{
							buff2[i]=*pos;
							i++;
							pos++;
						}
						buff2[i]=0;
						if (*pos!=0)
							pos++;
						Goto(COleVariant(buff2),COleVariant(short(atoipos)));
					}
					else
						Goto(COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR),COleVariant(short(FALSE)));
				}
				break;
		case 88:	/*GetHeight*/
				{
					double val=GetHeight();
					if (flgRet)
						sprintf(oStr,"%f",val);
				}
				break;
		case 89:	/*SetHeight*/
				SetHeight(atof(pos));
				break;
		case 90:	/*Help*/
				{
					COleVariant vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					if (*pos!=0)
					{
						char buff2[256];
						int i=0;
						while ((i<255) && (*pos!=0) && (*pos!=','))
						{
							buff2[i]=*pos;
							i++;
							pos++;
						}
						buff2[i]=0;
						if (*pos!=0)
							pos++;
						if (*pos!=0)
							Help(COleVariant(buff2),COleVariant(long(atoipos)));
						else
							Help(COleVariant(buff2),vOpt);
					}
					else
						Help(vOpt,vOpt);
				}
				break;
		case 91:	/*GetIgnoreRemoteRequests*/
				{
					BOOL val=GetIgnoreRemoteRequests();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 92:/*SetIgnoreRemoteRequests*/
				SetIgnoreRemoteRequests(atoipos);
				break;
		case 93:	/*InchesToPoints*/
				{
					double val=InchesToPoints(atof(pos));
					if (flgRet)
						sprintf(oStr,"%f",val);
				}
				break;
		case 94:	/*InputBox*/
				{
					COleVariant val=InputBoxEx(pos);
					if ((val.vt!=VT_NULL) && (flgRet))
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}

				}
				break;
		case 95:	/*GetInteractive*/
				{
					BOOL val=GetInteractive();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 96:/*SetInteractive*/
				SetInteractive(atoipos);
				break;
		case 97:	/*GetIteration*/
				{
					BOOL val=GetIteration();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 98:/*SetIteration*/
				SetIteration(atoipos);
				break;
		case 99:	/*GetLeft*/
				{
					double val=GetLeft();
					if (flgRet)
						sprintf(oStr,"%f",val);
				}
				break;
		case 100:	/*SetLeft*/
				SetLeft(atof(pos));
				break;
		case 101:	/*GetLibraryPath*/
				{
					CString str=GetLibraryPath();
					if (flgRet)
					{
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 102:	/*MacroOptions*/
				MacroOptionsEx(pos);
				break;
		case 103:	/*MailLogoff*/
				MailLogoff();
				break;
		case 104:	/*MailLogon*/
				MailLogonEx(pos);
				break;
		case 105:	/*GetMailSession*/
				{
					COleVariant val=GetMailSession();
					if ((flgRet) && (val.vt!=VT_NULL))
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 106:	/*GetMailSystem*/
				{
					long val=GetMailSystem();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 107:	/*GetMathCoprocessorAvailable*/
				{
					BOOL val=GetMathCoprocessorAvailable();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 108:	/*GetMaxChange*/
				{
					double val=GetMaxChange();
					if (flgRet)
						sprintf(oStr,"%f",val);
				}
				break;
		case 109:	/*SetMaxChange*/
				SetMaxChange(atof(pos));
				break;
		case 110:	/*GetMaxIterations*/
				{
					long val=GetMaxIterations();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 111:	/*SetMaxIterations*/
				SetMaxIterations(atoipos);
				break;
		case 112:	/*GetMemoryFree*/
				{
					long val=GetMemoryFree();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 113:	/*GetMemoryTotal*/
				{
					long val=GetMemoryTotal();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 114:	/*GetMemoryUsed*/
				{
					long val=GetMemoryUsed();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 115:	/*GetMouseAvailable*/
				{
					BOOL val=GetMouseAvailable();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 116:	/*GetMoveAfterReturn*/
				{
					BOOL val=GetMoveAfterReturn();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 117:	/*SetMoveAfterReturn*/
				SetMoveAfterReturn(atoipos);
				break;
		case 118:	/*GetMoveAfterReturnDirection*/
				{
					long val=GetMoveAfterReturnDirection();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 119:	/*SetMoveAfterReturnDirection*/
				SetMoveAfterReturnDirection(atoipos);
				break;
		case 120:	/*GetName*/
				{
					CString val=GetName();
					if (flgRet)
					{
						oStr=new char[(int)strlen(val)+1];
						strcpy(oStr,val);
					}
				}
				break;
		case 121:	/*GetNetworkTemplatesPath*/
				{
					CString val=GetNetworkTemplatesPath();
					if (flgRet)
					{
						oStr=new char[(int)strlen(val)+1];
						strcpy(oStr,val);
					}
				}
				break;
		case 122:	/*GetODBCTimeout*/
				{
					long val=GetODBCTimeout();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 123:	/*SetODBCTimeout*/
				SetODBCTimeout(atoipos);
				break;
		case 124:	/*OnKey*/
				{
					COleVariant vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					int i=0;
					char buff2[256];

					while ((*pos!=0) && (*pos!=',') && (i<255))
					{
						buff2[i]=*pos;
						i++;
						pos++;
					}
					buff2[i]=0;
					if (*pos!=0)
						pos++;
					if (*pos!=0)
						OnKey(buff2,COleVariant(pos));
					else
						OnKey(buff2,vOpt);
				}
				break;
		case 125:	/*OnRepeat*/
				{
					int i=0;
					char buff2[256];

					while ((*pos!=0) && (*pos!=',') && (i<255))
					{
						buff2[i]=*pos;
						i++;
						pos++;
					}
					buff2[i]=0;
					if (*pos!=0)
						pos++;
					OnRepeat(buff2,pos);
				}
				break;
		case 126:	/*OnTime*/
				OnTimeEx(pos);
				break;
		case 127:	/*OnUndo*/
				{
					int i=0;
					char buff2[256];

					while ((*pos!=0) && (*pos!=',') && (i<255))
					{
						buff2[i]=*pos;
						i++;
						pos++;
					}
					buff2[i]=0;
					if (*pos!=0)
						pos++;
					OnUndo(buff2,pos);
				}
				break;
		case 128:	/*GetOnWindow*/
				{
					CString val=GetOnWindow();
					if (flgRet)
					{
						oStr=new char[(int)strlen(val)+1];
						strcpy(oStr,val);
					}
				}
				break;
		case 129:	/*SetOnWindow*/
				SetOnWindow(pos);
				break;
		case 130:	/*GetOperatingSystem*/
				{
					CString val=GetOperatingSystem();
					if (flgRet)
					{
						oStr=new char[(int)strlen(val)+1];
						strcpy(oStr,val);
					}
				}
				break;
		case 131:	/*GetOrganizationName*/
				{
					CString val=GetOrganizationName();
					if (flgRet)
					{
						oStr=new char[(int)strlen(val)+1];
						strcpy(oStr,val);
					}
				}
				break;
		case 132:	/*GetPath*/
				{
					CString val=GetPath();
					if (flgRet)
					{
						oStr=new char[(int)strlen(val)+1];
						strcpy(oStr,val);
					}
				}
				break;
		case 133:	/*GetPathSeparator*/
				{
					CString val=GetPathSeparator();
					if (flgRet)
					{
						oStr=new char[(int)strlen(val)+1];
						strcpy(oStr,val);
					}
				}
				break;
		case 134:	/*GetPivotTableSelection*/
				{
					BOOL val=GetPivotTableSelection();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 135:	/*SetPivotTableSelection*/
				SetPivotTableSelection(atoipos);
				break;
		case 136:	/*GetPromptForSummaryInfo*/
				{
					BOOL val=GetPromptForSummaryInfo();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 137:	/*SetPromptForSummaryInfo*/
				SetPromptForSummaryInfo(atoipos);
				break;
		case 138:	/*Quit*/
				Quit();
				break;
		case 139:	/*GetRecordRelative*/
				{
					BOOL val=GetRecordRelative();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 140:	/*GetReferenceStyle*/
				{
					long val=GetReferenceStyle();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 141:	/*SetReferenceStyle*/
				SetReferenceStyle(atoipos);
				break;
		case 142:	/*RegisterXLL*/
				{
					BOOL val=RegisterXLL(pos);
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 143:	/*Repeat*/
				Repeat();
				break;
		case 144:	/*GetRollZoom*/
				{
					BOOL val=GetRollZoom();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 145:	/*SetRollZoom*/
				SetRollZoom(atoipos);
				break;
		case 146:	/*SaveWorkspace*/
				SaveWorkspace(COleVariant(pos));
				break;
		case 147:	/*GetScreenUpdating*/
				{
					BOOL val=GetScreenUpdating();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 148:	/*SetScreenUpdating*/
				SetScreenUpdating(atoipos);
				break;
		case 149:	/*SetDefaultChart*/
				SetDefaultChart(COleVariant(pos),COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR));
				break;
		case 150:	/*GetSheetsInNewWorkbook*/
				{
					long val=GetSheetsInNewWorkbook();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 151:	/*SetSheetsInNewWorkbook*/
				SetSheetsInNewWorkbook(atoipos);
				break;
		case 152:	/*GetShowChartTipNames*/
				{
					BOOL val=GetShowChartTipNames();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 153:	/*SetShowChartTipNames*/
				SetShowChartTipNames(atoipos);
				break;
		case 154:	/*GetShowChartTipValues*/
				{
					BOOL val=GetShowChartTipValues();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 155:	/*SetShowChartTipValues*/
				SetShowChartTipValues(atoipos);
				break;
		case 156:	/*GetStandardFont*/
				{
					CString str=GetStandardFont();
					if (flgRet)
					{
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 157:	/*SetStandardFont*/
				SetStandardFont(pos);
				break;
		case 158:	/*GetStandardFontSize*/
				{
					double val=GetStandardFontSize();
					if (flgRet)
						sprintf(oStr,"%f",val);
				}
				break;
		case 159:	/*SetStandardFontSize*/
				SetStandardFontSize(atof(pos));
				break;
		case 160:	/*GetStartupPath*/
				{
					CString str=GetStartupPath();
					if (flgRet)
					{
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 161:	/*GetStatusBar*/
				{
					COleVariant val=GetStatusBar();
					if (flgRet)
					{
						CString str;
						if (val.vt!=VT_NULL)
							ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 162:	/*SetStatusBar*/
				SetStatusBar(COleVariant(pos));
				break;
		case 163:	/*GetTemplatesPath*/
				{
					CString str=GetTemplatesPath();
					if (flgRet)
					{
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 164:	/*GetShowToolTips*/
				{
					BOOL val=GetShowToolTips();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 165:	/*SetShowToolTips*/
				SetShowToolTips(atoipos);
				break;
		case 166:	/*GetTop*/
				{
					double val=GetTop();
					if (flgRet)
						sprintf(oStr,"%f",val);
				}
				break;
		case 167:	/*SetTop*/
				SetTop(atof(pos));
				break;
		case 168:	/*GetDefaultSaveFormat*/
				{
					long val=GetDefaultSaveFormat();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 169:	/*SetDefaultSaveFormat*/
				SetDefaultSaveFormat(atoipos);
				break;
		case 170:	/*GetTransitionMenuKey*/
				{
					CString str=GetTransitionMenuKey();
					if (flgRet)
					{
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 171:	/*SetTransitionMenuKey*/
				SetTransitionMenuKey(pos);
				break;
		case 172:	/*GetTransitionMenuKeyAction*/
				{
					long val=GetTransitionMenuKeyAction();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 173:	/*SetTransitionMenuKeyAction*/
				SetTransitionMenuKeyAction(atoipos);
				break;
		case 174:	/*GetTransitionNavigKeys*/
				{
					BOOL val=GetTransitionNavigKeys();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 175:	/*SetTransitionNavigKeys*/
				SetTransitionNavigKeys(atoipos);
				break;
		case 176:	/*Undo*/
				Undo();
				break;
		case 177:	/*GetUsableHeight*/
				{
					double val=GetUsableHeight();
					if (flgRet)
						sprintf(oStr,"%f",val);
				}
				break;
		case 178:	/*GetUsableWidth*/
				{
					double val=GetUsableWidth();
					if (flgRet)
						sprintf(oStr,"%f",val);
				}
				break;
		case 179:	/*GetUserControl*/
				{
					BOOL val=GetUserControl();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 180:	/*SetUserControl*/
				SetUserControl(atoipos);
				break;
		case 181:	/*GetUserName_*/
				{
					CString str=GetUserName_();
					if (flgRet)
					{
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 182:	/*SetUserName*/
				SetUserName(pos);
				break;
		case 183:	/*GetValue*/
				{
					CString str=GetValue();
					if (flgRet)
					{
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 184:	/*GetVersion*/
				{
					CString str=GetVersion();
					if (flgRet)
					{
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 185:	/*GetVisible*/
				{
					BOOL val=GetVisible();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 186:	/*SetVisible*/
				SetVisible(atoipos);
				break;
		case 187:	/*Volatile*/
				Volatile(COleVariant(short(atoipos)));
				break;
		case 188:	/*Wait*/
				Wait(COleVariant(pos));
				break;
		case 189:	/*GetWidth*/
				{
					double val=GetWidth();
					if (flgRet)
						sprintf(oStr,"%f",val);
				}
				break;
		case 190:	/*SetWidth*/
				SetWidth(atof(pos));
				break;
		case 191:	/*GetWindowsForPens*/
				{
					BOOL val=GetWindowsForPens();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 192:	/*GetWindowState*/
				{
					long val=GetWindowState();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 193:	/*SetWindowState*/
				SetWindowState(atoipos);
				break;
		case 194:	/*GetUILanguage*/
				{
					long val=GetUILanguage();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 195:	/*SetUILanguage*/
				SetUILanguage(atoipos);
				break;
		case 196:	/*GetDefaultSheetDirection*/
				{
					long val=GetDefaultSheetDirection();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 197:	/*SetDefaultSheetDirection*/
				SetDefaultSheetDirection(atoipos);
				break;
		case 198:	/*GetCursorMovement*/
				{
					long val=GetCursorMovement();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 199:	/*SetCursorMovement*/
				SetCursorMovement(atoipos);
				break;
		case 200:	/*GetControlCharacters*/
				{
					long val=GetControlCharacters();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 201:	/*SetControlCharacters*/
				SetControlCharacters(atoipos);
				break;
		case 202:	/*GetEnableEvents*/
				{
					BOOL val=GetEnableEvents();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 203:	/*SetEnableEvents*/
				SetEnableEvents(atoipos);
				break;
		case 204:	/*"GetCountWorkbook"*/
				{
					int counter=0;
					int IdWorkbook=0;
					while(IdWorkbook<N_EXCELWORKBOOK_ARR)
					{
						if (gpWorkbooks[IdWorkbook]!=NULL)
							counter++;
						IdWorkbook++;
					}
				}
				break;
		default:
			GPC.m_ErrReport.GPWriteWarnLog2("GPExcelApplication", "Unknown Method",iMethod);
			if (flgRet)		 sprintf(oStr,ErrObjSub,met);
			nfunc=0xFFFFFFFFL;
			break;
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
		if (flgRet) strcpy(oStr,str);
		nfunc=0xFFFFFFFFL;
		GPC.m_ErrReport.GPWriteErrorLog("GPExcelOLEApplication", "DoMethod",iMethod);
		delete[] str;
	}

	if (flgRet && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
//	delete[] met;
	return nfunc;
}

int GPExcelOLEApplication::DoWbMethod(int IdWorkbook,const char* iMethod,char* oStr,BOOL flgRet)
{
	int ret=-2;

	if ((IdWorkbook>=0) && (IdWorkbook<N_EXCELWORKBOOK_ARR))
		if (gpWorkbooks[IdWorkbook]!=NULL)
			ret=gpWorkbooks[IdWorkbook]->DoMethod(iMethod,oStr,flgRet);

	return ret;
}

int GPExcelOLEApplication::DoWsMethod(int IdWorkbook, const char *iMethod, char *oStr,BOOL flgRet) // Worksheet Method
{
	int ret=-2;
	int IdWorksheet;
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
	IdWorksheet=atoi(bff);
	if ((IdWorkbook>=0) && (IdWorkbook<N_EXCELWORKBOOK_ARR))
		if (gpWorkbooks[IdWorkbook]!=NULL)
			ret=gpWorkbooks[IdWorkbook]->DoWsMethod(IdWorksheet,pos,oStr,flgRet);
	return ret;
}

VARIANT GPExcelOLEApplication::RunEx(const char* iStr) //my run macro
{
	COleVariant vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	COleVariant res;
	COleVariant runarray[31];
	const char* pos=iStr;
	char* buff=new char[(int)strlen(iStr)+1];
	int i=0;
	int j=0;

	if (*pos!=0)
	{
		while(*pos!=0)
		{
			if (*pos==1)
			{
				buff[j]='\0';
				runarray[i]=COleVariant(buff);
				j=0;
				i++;
			}
			else
			{
				buff[j]=*pos;
				j++;
			}
			pos++;
		}
		buff[j]='\0';
		runarray[i]=COleVariant(buff);
		i++;
	}

	while(i<31)
	{
		runarray[i]=vOpt;
		i++;
	}
	res=Run(runarray[0],runarray[1],runarray[2],runarray[3],runarray[4],runarray[5],runarray[6],
		runarray[7],runarray[8],runarray[9],runarray[10],runarray[11],runarray[12],runarray[13],
		runarray[14],runarray[15],runarray[16],runarray[17],runarray[18],runarray[19],runarray[20],
		runarray[21],runarray[22],runarray[23],runarray[24],runarray[25],runarray[26],runarray[27],
		runarray[28],runarray[29],runarray[30]);


	return res;
}

void GPExcelOLEApplication::SendKeysEx(const char* iStr)
{
	const char* pos=iStr;
	char* buff=new char[(int)strlen(iStr)+1];
	COleVariant argvVar[2];
	int nall=0;
	int i=0;


try
{
	// разбор параметров
	buff[0]=0;
	while(nall<2)
	{
		if ((*pos!=0) && (*pos!=','))
			buff[i]=*pos;
		else
		{
			if (buff[0]!=0)
			{
				buff[i]=0;
				switch(nall)
				{
				case 0:argvVar[nall]=COleVariant(buff);
					break;
				case 1:argvVar[nall]=COleVariant(short(atoi(buff)));
					break;
				}
			}
			else
				argvVar[nall]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
			buff[0]=0;
			i=0;
			nall++;
		}
		if (*pos!=0)
		{
			pos++;
			i++;
		}
	}

	SendKeys(argvVar[0],argvVar[1]);
	delete[] buff;
}
catch (CMemoryException e)
{

}
}

BOOL GPExcelOLEApplication::CheckSpellingEx(const char* iStr)
{
	BOOL ret=FALSE;
	const char* pos=iStr;
	char* buff=new char[(int)strlen(iStr)+1];
	COleVariant argvVar[3];
	int nall=0;
	int i=0;


try
{
	// разбор параметров
	buff[0]=0;
	while(nall<3)
	{
		if ((*pos!=0) && (*pos!=','))
			buff[i]=*pos;
		else
		{
			if (buff[0]!=0)
			{
				buff[i]=0;
				switch(nall)
				{
				case 0:argvVar[nall]=COleVariant(buff);
					break;
				case 1:argvVar[nall]=COleVariant(buff);
					break;
				case 2:argvVar[nall]=COleVariant(short(atoi(buff)));
					break;
				}
			}
			else
				argvVar[nall]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
			buff[0]=0;
			i=0;
			nall++;
		}
		if (*pos!=0)
		{
			pos++;
			i++;
		}
	}

	CString str;
	if (argvVar[0].vt!=VT_ERROR)
		str=argvVar[0].bstrVal;
	ret=CheckSpelling(str,argvVar[1],argvVar[2]);
	delete[] buff;
}
catch (CMemoryException e)
{

}
	return ret;
}

VARIANT GPExcelOLEApplication::GetOpenFilenameEx(const char* iStr)
{
	COleVariant ret;
	const char* pos=iStr;
	char* buff=new char[(int)strlen(iStr)+1];
	COleVariant argvVar[5];
	int nall=0;
	int i=0;


try
{
	// разбор параметров
	buff[0]=0;
	while(nall<5)
	{
		if ((*pos!=0) && (*pos!=','))
			buff[i]=*pos;
		else
		{
			if (buff[0]!=0)
			{
				buff[i]=0;
				switch(nall)
				{
				case 0:argvVar[nall]=COleVariant(buff);
					break;
				case 2:argvVar[nall]=COleVariant(buff);
					break;
				case 1:argvVar[nall]=COleVariant(long(atoi(buff)));
					break;
				case 4:argvVar[nall]=COleVariant(short(atoi(buff)));
					break;
				default:
					argvVar[nall]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					break;
				}
			}
			else
				argvVar[nall]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
			buff[0]=0;
			i=0;
			nall++;
		}
		if (*pos!=0)
		{
			pos++;
			i++;
		}
	}

	ret=GetOpenFilename(argvVar[0],argvVar[1],argvVar[2],argvVar[3],argvVar[4]);
	delete[] buff;
}
catch (CMemoryException e)
{

}
	return ret;
}

VARIANT GPExcelOLEApplication::GetSaveAsFilenameEx(const char* iStr)
{
	COleVariant ret;
	const char* pos=iStr;
	char* buff=new char[(int)strlen(iStr)+1];
	COleVariant argvVar[5];
	int nall=0;
	int i=0;


try
{
	// разбор параметров
	buff[0]=0;
	while(nall<5)
	{
		if ((*pos!=0) && (*pos!=','))
			buff[i]=*pos;
		else
		{
			if (buff[0]!=0)
			{
				buff[i]=0;
				switch(nall)
				{
				case 0:argvVar[nall]=COleVariant(buff);
					break;
				case 1:argvVar[nall]=COleVariant(buff);
					break;
				case 3:argvVar[nall]=COleVariant(buff);
					break;
				case 2:argvVar[nall]=COleVariant(long(atoi(buff)));
					break;
				default:
					argvVar[nall]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					break;
				}
			}
			else
				argvVar[nall]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
			buff[0]=0;
			i=0;
			nall++;
		}
		if (*pos!=0)
		{
			pos++;
			i++;
		}
	}

	ret=GetSaveAsFilename(argvVar[0],argvVar[1],argvVar[2],argvVar[3],argvVar[4]);
	delete[] buff;
}
catch (CMemoryException e)
{

}
	return ret;
}

VARIANT GPExcelOLEApplication::InputBoxEx(const char* iStr)
{
	COleVariant ret;
	const char* pos=iStr;
	char* buff=new char[(int)strlen(iStr)+1];
	COleVariant argvVar[8];
	int nall=0;
	int i=0;


try
{
	// разбор параметров
	buff[0]=0;
	while(nall<8)
	{
		if ((*pos!=0) && (*pos!=','))
			buff[i]=*pos;
		else
		{
			if (buff[0]!=0)
			{
				buff[i]=0;
				switch(nall)
				{
				case 0:argvVar[nall]=COleVariant(buff);
					break;
				case 1:argvVar[nall]=COleVariant(buff);
					break;
				case 2:argvVar[nall]=COleVariant(buff);
					break;
				case 3:argvVar[nall]=COleVariant(long(atoi(buff)));
					break;
				case 4:argvVar[nall]=COleVariant(long(atoi(buff)));
					break;
				case 5:argvVar[nall]=COleVariant(buff);
					break;
				case 6:argvVar[nall]=COleVariant(buff);
					break;
				case 7:argvVar[nall]=COleVariant(buff);
					break;
				default:
					argvVar[nall]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					break;
				}
			}
			else
				argvVar[nall]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
			buff[0]=0;
			i=0;
			nall++;
		}
		if (*pos!=0)
		{
			pos++;
			i++;
		}
	}

	CString str;
	if (argvVar[0].vt!=VT_ERROR)
		str=argvVar[0].bstrVal;
	ret=InputBox(str,argvVar[1],argvVar[2],argvVar[3],argvVar[4],
				argvVar[5],argvVar[6],argvVar[7]);
	delete[] buff;
}
catch (CMemoryException e)
{

}
	return ret;
}

int GPExcelOLEApplication::MacroOptionsEx(const char* iStr)
{
	int ret=-2;
	const char* pos=iStr;
	char* buff=new char[(int)strlen(iStr)+1];
	COleVariant argvVar[10];
	int nall=0;
	int i=0;


try
{
	// разбор параметров
	buff[0]=0;
	while(nall<10)
	{
		if ((*pos!=0) && (*pos!=','))
			buff[i]=*pos;
		else
		{
			if (buff[0]!=0)
			{
				buff[i]=0;
				switch(nall)
				{
				case 0:argvVar[nall]=COleVariant(buff);
					break;
				case 1:argvVar[nall]=COleVariant(buff);
					break;
				case 4:argvVar[nall]=COleVariant(short(atoi(buff)));
					break;
				case 5:argvVar[nall]=COleVariant(buff);
					break;
				case 6:argvVar[nall]=COleVariant(long(atoi(buff)));
					break;
				case 7:argvVar[nall]=COleVariant(buff);
					break;
				case 8:argvVar[nall]=COleVariant(long(atoi(buff)));
					break;
				case 9:argvVar[nall]=COleVariant(buff);
					break;
				default:
					argvVar[nall]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					break;
				}
			}
			else
				argvVar[nall]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
			buff[0]=0;
			i=0;
			nall++;
		}
		if (*pos!=0)
		{
			pos++;
			i++;
		}
	}

	MacroOptions(argvVar[0],argvVar[1],argvVar[2],argvVar[3],argvVar[4],
				argvVar[5],argvVar[6],argvVar[7],argvVar[8],argvVar[9]);
	delete[] buff;
}
catch (CMemoryException e)
{

}
	return ret;
}

int GPExcelOLEApplication::MailLogonEx(const char* iStr)
{
	int ret=-2;
	const char* pos=iStr;
	char* buff=new char[(int)strlen(iStr)+1];
	COleVariant argvVar[3];
	int nall=0;
	int i=0;


try
{
	// разбор параметров
	buff[0]=0;
	while(nall<3)
	{
		if ((*pos!=0) && (*pos!=','))
			buff[i]=*pos;
		else
		{
			if (buff[0]!=0)
			{
				buff[i]=0;
				switch(nall)
				{
				case 0:argvVar[nall]=COleVariant(buff);
					break;
				case 1:argvVar[nall]=COleVariant(buff);
					break;
				case 2:argvVar[nall]=COleVariant(short(atoi(buff)));
					break;

				default:
					argvVar[nall]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					break;
				}
			}
			else
				argvVar[nall]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
			buff[0]=0;
			i=0;
			nall++;
		}
		if (*pos!=0)
		{
			pos++;
			i++;
		}
	}

	MailLogon(argvVar[0],argvVar[1],argvVar[2]);
	delete[] buff;
}
catch (CMemoryException e)
{

}
	return ret;
}

int GPExcelOLEApplication::OnTimeEx(const char* iStr)
{
	int ret=-2;
	const char* pos=iStr;
	char* buff=new char[(int)strlen(iStr)+1];
	COleVariant argvVar[4];
	int nall=0;
	int i=0;


try
{
	// разбор параметров
	buff[0]=0;
	while(nall<4)
	{
		if ((*pos!=0) && (*pos!=','))
			buff[i]=*pos;
		else
		{
			if (buff[0]!=0)
			{
				buff[i]=0;
				switch(nall)
				{
				case 0:argvVar[nall]=COleVariant(long(atoi(buff)));
					break;
				case 1:argvVar[nall]=COleVariant(buff);
					break;
				case 2:argvVar[nall]=COleVariant(long(atoi(buff)));
					break;
				case 3:argvVar[nall]=COleVariant(short(atoi(buff)));
					break;
				default:
					argvVar[nall]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					break;
				}
			}
			else
				argvVar[nall]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
			buff[0]=0;
			i=0;
			nall++;
		}
		if (*pos!=0)
		{
			pos++;
			i++;
		}
	}

	CString str;
	if (argvVar[1].vt!=VT_ERROR)
	OnTime(argvVar[0],str,argvVar[2],argvVar[3]);
	delete[] buff;
}
catch (CMemoryException e)
{

}
	return ret;
}


/////////////////////////////////////////////////////////////////////////////
// _Worksheet properties

/////////////////////////////////////////////////////////////////////////////
// _Worksheet operations

LPDISPATCH GPExcelOLEWorksheet::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long GPExcelOLEWorksheet::GetCreator()
{
	long result;
	InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEWorksheet::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorksheet::Activate()
{
	InvokeHelper(0x130, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void GPExcelOLEWorksheet::Copy(const VARIANT& Before, const VARIANT& After)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x227, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Before, &After);
}

void GPExcelOLEWorksheet::Delete()
{
	InvokeHelper(0x75, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString GPExcelOLEWorksheet::GetCodeName()
{
	CString result;
	InvokeHelper(0x55d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString GPExcelOLEWorksheet::Get_CodeName()
{
	CString result;
	InvokeHelper(0x80010000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorksheet::Set_CodeName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x80010000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long GPExcelOLEWorksheet::GetIndex()
{
	long result;
	InvokeHelper(0x1e6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorksheet::Move(const VARIANT& Before, const VARIANT& After)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x27d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Before, &After);
}

CString GPExcelOLEWorksheet::GetName()
{
	CString result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorksheet::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH GPExcelOLEWorksheet::GetNext()
{
	LPDISPATCH result;
	InvokeHelper(0x1f6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEWorksheet::GetPageSetup()
{
	LPDISPATCH result;
	InvokeHelper(0x3e6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEWorksheet::GetPrevious()
{
	LPDISPATCH result;
	InvokeHelper(0x1f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorksheet::PrintOut(const VARIANT& From, const VARIANT& To, const VARIANT& Copies, const VARIANT& Preview, const VARIANT& ActivePrinter, const VARIANT& PrintToFile, const VARIANT& Collate)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x389, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &From, &To, &Copies, &Preview, &ActivePrinter, &PrintToFile, &Collate);
}

void GPExcelOLEWorksheet::PrintPreview(const VARIANT& EnableChanges)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x119, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &EnableChanges);
}

void GPExcelOLEWorksheet::Protect(const VARIANT& Password, const VARIANT& DrawingObjects, const VARIANT& Contents, const VARIANT& Scenarios, const VARIANT& UserInterfaceOnly)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x11a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Password, &DrawingObjects, &Contents, &Scenarios, &UserInterfaceOnly);
}

BOOL GPExcelOLEWorksheet::GetProtectContents()
{
	BOOL result;
	InvokeHelper(0x124, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEWorksheet::GetProtectDrawingObjects()
{
	BOOL result;
	InvokeHelper(0x125, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEWorksheet::GetProtectionMode()
{
	BOOL result;
	InvokeHelper(0x487, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEWorksheet::GetProtectScenarios()
{
	BOOL result;
	InvokeHelper(0x126, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorksheet::SaveAs(LPCTSTR Filename, const VARIANT& FileFormat, const VARIANT& Password, const VARIANT& WriteResPassword, const VARIANT& ReadOnlyRecommended, const VARIANT& CreateBackup, const VARIANT& AddToMru, const VARIANT& TextCodepage,
		const VARIANT& TextVisualLayout)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x11c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Filename, &FileFormat, &Password, &WriteResPassword, &ReadOnlyRecommended, &CreateBackup, &AddToMru, &TextCodepage, &TextVisualLayout);
}

void GPExcelOLEWorksheet::Select(const VARIANT& Replace)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xeb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Replace);
}

void GPExcelOLEWorksheet::Unprotect(const VARIANT& Password)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x11d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Password);
}

long GPExcelOLEWorksheet::GetVisible()
{
	long result;
	InvokeHelper(0x22e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorksheet::SetVisible(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x22e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH GPExcelOLEWorksheet::GetShapes()
{
	LPDISPATCH result;
	InvokeHelper(0x561, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEWorksheet::GetTransitionExpEval()
{
	BOOL result;
	InvokeHelper(0x191, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorksheet::SetTransitionExpEval(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x191, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL GPExcelOLEWorksheet::GetAutoFilterMode()
{
	BOOL result;
	InvokeHelper(0x318, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorksheet::SetAutoFilterMode(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x318, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void GPExcelOLEWorksheet::SetBackgroundPicture(LPCTSTR Filename)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4a4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Filename);
}

void GPExcelOLEWorksheet::Calculate()
{
	InvokeHelper(0x117, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL GPExcelOLEWorksheet::GetEnableCalculation()
{
	BOOL result;
	InvokeHelper(0x590, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorksheet::SetEnableCalculation(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x590, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH GPExcelOLEWorksheet::GetCells()
{
	LPDISPATCH result;
	InvokeHelper(0xee, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEWorksheet::ChartObjects(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x424, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

void GPExcelOLEWorksheet::CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest, const VARIANT& IgnoreInitialAlefHamza, const VARIANT& IgnoreFinalYaa, const VARIANT& SpellScript)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1f9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &CustomDictionary, &IgnoreUppercase, &AlwaysSuggest, &IgnoreInitialAlefHamza, &IgnoreFinalYaa, &SpellScript);
}

LPDISPATCH GPExcelOLEWorksheet::GetCircularReference()
{
	LPDISPATCH result;
	InvokeHelper(0x42d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorksheet::ClearArrows()
{
	InvokeHelper(0x3ca, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH GPExcelOLEWorksheet::GetColumns()
{
	LPDISPATCH result;
	InvokeHelper(0xf1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long GPExcelOLEWorksheet::GetConsolidationFunction()
{
	long result;
	InvokeHelper(0x315, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

VARIANT GPExcelOLEWorksheet::GetConsolidationOptions()
{
	VARIANT result;
	InvokeHelper(0x316, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT GPExcelOLEWorksheet::GetConsolidationSources()
{
	VARIANT result;
	InvokeHelper(0x317, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEWorksheet::GetEnableAutoFilter()
{
	BOOL result;
	InvokeHelper(0x484, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorksheet::SetEnableAutoFilter(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x484, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long GPExcelOLEWorksheet::GetEnableSelection()
{
	long result;
	InvokeHelper(0x591, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorksheet::SetEnableSelection(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x591, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL GPExcelOLEWorksheet::GetEnableOutlining()
{
	BOOL result;
	InvokeHelper(0x485, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorksheet::SetEnableOutlining(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x485, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL GPExcelOLEWorksheet::GetEnablePivotTable()
{
	BOOL result;
	InvokeHelper(0x486, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorksheet::SetEnablePivotTable(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x486, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT GPExcelOLEWorksheet::Evaluate(const VARIANT& Name)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Name);
	return result;
}

VARIANT GPExcelOLEWorksheet::_Evaluate(const VARIANT& Name)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xfffffffb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Name);
	return result;
}

BOOL GPExcelOLEWorksheet::GetFilterMode()
{
	BOOL result;
	InvokeHelper(0x320, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorksheet::ResetAllPageBreaks()
{
	InvokeHelper(0x592, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH GPExcelOLEWorksheet::GetNames()
{
	LPDISPATCH result;
	InvokeHelper(0x1ba, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEWorksheet::OLEObjects(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x31f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

LPDISPATCH GPExcelOLEWorksheet::GetOutline()
{
	LPDISPATCH result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorksheet::Paste(const VARIANT& Destination, const VARIANT& Link)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Destination, &Link);
}

void GPExcelOLEWorksheet::PasteSpecial(const VARIANT& Format, const VARIANT& Link, const VARIANT& DisplayAsIcon, const VARIANT& IconFileName, const VARIANT& IconIndex, const VARIANT& IconLabel)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Format, &Link, &DisplayAsIcon, &IconFileName, &IconIndex, &IconLabel);
}

LPDISPATCH GPExcelOLEWorksheet::PivotTables(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2b2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

LPDISPATCH GPExcelOLEWorksheet::PivotTableWizard(const VARIANT& SourceType, const VARIANT& SourceData, const VARIANT& TableDestination, const VARIANT& TableName, const VARIANT& RowGrand, const VARIANT& ColumnGrand, const VARIANT& SaveData,
		const VARIANT& HasAutoFormat, const VARIANT& AutoPage, const VARIANT& Reserved, const VARIANT& BackgroundQuery, const VARIANT& OptimizeCache, const VARIANT& PageFieldOrder, const VARIANT& PageFieldWrapCount, const VARIANT& ReadData,
		const VARIANT& Connection)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x2ac, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&SourceType, &SourceData, &TableDestination, &TableName, &RowGrand, &ColumnGrand, &SaveData, &HasAutoFormat, &AutoPage, &Reserved, &BackgroundQuery, &OptimizeCache, &PageFieldOrder, &PageFieldWrapCount, &ReadData, &Connection);
	return result;
}

LPDISPATCH GPExcelOLEWorksheet::GetRange(const VARIANT& Cell1, const VARIANT& Cell2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xc5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&Cell1, &Cell2);
	return result;
}

LPDISPATCH GPExcelOLEWorksheet::GetRows()
{
	LPDISPATCH result;
	InvokeHelper(0x102, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEWorksheet::Scenarios(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x38c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

CString GPExcelOLEWorksheet::GetScrollArea()
{
	CString result;
	InvokeHelper(0x599, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorksheet::SetScrollArea(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x599, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void GPExcelOLEWorksheet::ShowAllData()
{
	InvokeHelper(0x31a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void GPExcelOLEWorksheet::ShowDataForm()
{
	InvokeHelper(0x199, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

double GPExcelOLEWorksheet::GetStandardHeight()
{
	double result;
	InvokeHelper(0x197, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

double GPExcelOLEWorksheet::GetStandardWidth()
{
	double result;
	InvokeHelper(0x198, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorksheet::SetStandardWidth(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x198, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL GPExcelOLEWorksheet::GetTransitionFormEntry()
{
	BOOL result;
	InvokeHelper(0x192, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorksheet::SetTransitionFormEntry(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x192, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long GPExcelOLEWorksheet::GetType()
{
	long result;
	InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEWorksheet::GetUsedRange()
{
	LPDISPATCH result;
	InvokeHelper(0x19c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEWorksheet::GetHPageBreaks()
{
	LPDISPATCH result;
	InvokeHelper(0x58a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEWorksheet::GetVPageBreaks()
{
	LPDISPATCH result;
	InvokeHelper(0x58b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEWorksheet::GetQueryTables()
{
	LPDISPATCH result;
	InvokeHelper(0x59a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEWorksheet::GetDisplayPageBreaks()
{
	BOOL result;
	InvokeHelper(0x59b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorksheet::SetDisplayPageBreaks(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x59b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH GPExcelOLEWorksheet::GetComments()
{
	LPDISPATCH result;
	InvokeHelper(0x23f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEWorksheet::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x571, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorksheet::ClearCircles()
{
	InvokeHelper(0x59c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void GPExcelOLEWorksheet::CircleInvalid()
{
	InvokeHelper(0x59d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH GPExcelOLEWorksheet::GetAutoFilter()
{
	LPDISPATCH result;
	InvokeHelper(0x319, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

			// добавленные функции
LPDISPATCH GPExcelOLEWorksheet::CreateGPExcelRange(const char *iStr)
{
	LPDISPATCH pDisp=NULL;
	int i=0;
	char buff[2][256];
	COleVariant varVal[2];
	const char* pos=iStr;

	while ((*pos!=':') && (*pos!=0))
	{
		buff[0][i]=*pos;
		pos++;
		i++;
	}
	buff[0][i]='\0';
	if (*pos==0)
		return pDisp;
	pos++;
	i=0;
	while ((*pos!=':') && (*pos!=0))
	{
		buff[1][i]=*pos;
		pos++;
		i++;
	}
	buff[1][i]='\0';
	i=0;
	while(i<2)
	{
		if (buff[i][0]!=0)
			varVal[i]=COleVariant(buff[i]);
		else
			varVal[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		i++;
	}
	// GetDispatchOfRange
	pDisp=GetRange(varVal[0],varVal[1]);


	return pDisp;
}


int GPExcelOLEWorksheet::DoMethod(const char* iMethod,char* oStr,BOOL flgRet)
{
//	char *met=new char [(int)strlen(iMethod)+50];
	char met[200];
	strncpy(met,iMethod,195);met[195]=0;
	const char *pos=strchr(iMethod,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc;
	char *fn[58]={"GetCreator","Activate","Copy","Delete","GetCodeName","Get_CodeName",
		"Set_CodeName","Move","GetName","SetName","PrintOut",
		"PrintPreview","Protect","GetProtectContents","GetProtectDrawingObjects",
		"GetProtectionMode","GetProtectScenarios","SaveAs","Select","Unprotect","GetVisible",
		"SetVisible","GetTransitionExpEval","SetTransitionExpEval","GetAutoFilterMode",
		"SetAutoFilterMode","SetBackgroundPicture","Calculate","GetEnableCalculation",
		"SetEnableCalculation","ClearArrows","GetConsolidationFunction",
		"GetEnableAutoFilter","SetEnableAutoFilter","GetEnableSelection","SetEnableSelection",
		"GetEnableOutlining","SetEnableOutlining","GetEnablePivotTable",
		"SetEnablePivotTable","GetFilterMode","ResetAllPageBreaks","Paste","PasteSpecial",
		"GetScrollArea","SetScrollArea","ShowAllData","ShowDataForm","GetStandardHeight",
		"GetStandardWidth","SetStandardWidth","GetTransitionFormEntry","SetTransitionFormEntry",
		"GetType","GetDisplayPageBreaks","SetDisplayPageBreaks","ClearCircles","CircleInvalid"
		};

	if (*met>='0' && *met<='9') nfunc=atoi(met);
	else
		for(nfunc=0;nfunc<58 && _stricmp(met,fn[nfunc])!=0;nfunc++);

	int retint=-123456;
	int atoipos=atoi(pos);

	try
	{
		switch(nfunc)
		{
		case 0:	/*GetCreator*/
				{
					long val=GetCreator();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 1:	/*Activate*/
				Activate();
				break;
		case 2:	/*Copy*/
				{
					Copy(COleVariant("A1"),COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR));
					Paste(COleVariant("A3"),COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR));
				}
				break;
		case 3:	/*Delete*/
				Delete();
				break;
		case 4:	/*GetCodeName*/
				{
					CString val=GetCodeName();
					if (flgRet)
					{
						oStr=new char[(int)strlen(val)+1];
						strcpy(oStr,val);
					}
				}
				break;
		case 5:	/*Get_CodeName*/
				{
					CString val=Get_CodeName();
					if (flgRet)
					{
						oStr=new char[(int)strlen(val)+1];
						strcpy(oStr,val);
					}
				}
				break;
		case 6:	/*Set_CodeName*/
				Set_CodeName(pos);
				break;
		case 7:	/*Move*/
				{
					//Move
				}
				break;
		case 8:	/*GetName*/
				{
					CString val=GetName();
					if (flgRet)
					{
						oStr=new char[(int)strlen(val)+1];
						strcpy(oStr,val);
					}
				}
				break;
		case 9:	/*SetName*/
				SetName(pos);
				break;
		case 10:	/*PrintOut*/
				{
					PrintOutEx(pos);
				}
				break;
		case 11:	/*PrintPreview*/
				{
					COleVariant val=pos;
					PrintPreview(val);
				}
				break;
		case 12:	/*Protect*/
				{
					ProtectEx(pos);
				}
				break;
		case 13:	/*GetProtectContents*/
				{
					BOOL val=GetProtectContents();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 14:	/*GetProtectDrawingObjects*/
				{
					BOOL val=GetProtectDrawingObjects();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 15:	/*GetProtectionMode*/
				{
					BOOL val=GetProtectionMode();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 16:	/*GetProtectScenarios*/
				{
					BOOL val=GetProtectScenarios();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 17: /*SaveAs*/
				SaveAsEx(pos);
				break;
		case 18: /*Select*/
				{
					short val=(short)atoipos;
					Select(COleVariant(val));
				}
				break;
		case 19: /*Unprotect*/
				{
					COleVariant val(pos);
					Unprotect(val);
				}
				break;
		case 20:	/*GetVisible*/
				{
					long val=GetVisible();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 21:	/*SetVisible*/
				{
					long val=atoipos;
					SetVisible(val);
				}
				break;
		case 22:	/*GetTransitionExpEval*/
				{
					BOOL val=GetTransitionExpEval();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 23:	/*SetTransitionExpEval*/
				{
					BOOL val=atoipos;
					SetTransitionExpEval(val);
				}
				break;
		case 24:	/*GetAutoFilterMode*/
				{
					BOOL val=GetAutoFilterMode();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 25:	/*SetAutoFilterMode*/
				{
					BOOL val=atoipos;
					SetAutoFilterMode(val);
				}
				break;
		case 26:	/*SetBackgroundPicture*/
				SetBackgroundPicture(pos);
				break;
		case 27:	/*Calculate*/
				Calculate();
				break;
		case 28:	/*GetEnableCalculation*/
				{
					BOOL val=GetEnableCalculation();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 29:	/*SetEnableCalculation*/
				{
					BOOL val=atoipos;
					SetEnableCalculation(val);
				}
				break;
		case 30:	/*ClearArrows*/
				ClearArrows();
				break;
		case 31:	/*GetConsolidationFunction*/
				{
					long val=GetConsolidationFunction();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 32:	/*GetEnableAutoFilter*/
				{
					BOOL val=GetEnableAutoFilter();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 33:	/*SetEnableAutoFilter*/
				{
					BOOL val=atoipos;
					SetEnableAutoFilter(val);
				}
				break;
		case 34:	/*GetEnableSelection*/
				{
					long val=GetEnableAutoFilter();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 35:	/*SetEnableSelection*/
				{
					long val=atoipos;
					SetEnableSelection(val);
				}
				break;
		case 36:	/*GetEnableOutlining*/
				{
					BOOL val=GetEnableOutlining();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 37:	/*SetEnableOutlining*/
				{
					BOOL val=atoipos;
					SetEnableOutlining(val);
				}
				break;
		case 38:	/*GetEnablePivotTable*/
				{
					BOOL val=GetEnablePivotTable();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 39:	/*SetEnablePivotTable*/
				{
					BOOL val=atoipos;
					SetEnablePivotTable(val);
				}
				break;
		case 40:	/*GetFilterMode*/
				{
					BOOL val=GetFilterMode();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 41:	/*ResetAllPageBreaks*/
				ResetAllPageBreaks();
				break;
		case 42:	/*Paste*/
				{
					//Paste();
				}
				break;
		case 43:	/*PasteSpecial*/
				PasteSpecialEx(pos);
				break;
		case 44:	/*GetScrollArea*/
				{
					CString val=GetScrollArea();
					if (flgRet)
					{
						oStr=new char[(int)strlen(val)+1];
						strcpy(oStr,val);
					}
				}
				break;
		case 45:	/*SetScrollArea*/
				SetScrollArea(pos);
				break;
		case 46:	/*ShowAllData*/
				ShowAllData();
				break;
		case 47:	/*ShowDataForm*/
				ShowDataForm();
				break;
		case 48:	/*GetStandardHeight*/
				{
					double val=GetStandardHeight();
					if (flgRet)
						sprintf(oStr,"%f",val);
				}
				break;
		case 49:	/*GetStandardWidth*/
				{
					double val=GetStandardWidth();
					if (flgRet)
						sprintf(oStr,"%f",val);
				}
				break;
		case 50:	/*SetStandardWidth*/
				{
					double val=atof(pos);
					SetStandardWidth(val);
				}
				break;
		case 51:	/*GetTransitionFormEntry*/
				{
					BOOL val=GetTransitionFormEntry();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 52:	/*SetTransitionFormEntry*/
				{
					BOOL val=atoipos;
					SetTransitionFormEntry(val);
				}
				break;
		case 53:	/*GetType*/
				{
					long val=GetType();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 54:	/*GetDisplayPageBreaks*/
				{
					BOOL val=GetDisplayPageBreaks();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 55:	/*SetDisplayPageBreaks*/
				{
					BOOL val=atoipos;
					SetDisplayPageBreaks(val);
				}
				break;
		case 56:	/*ClearCircles*/
				ClearCircles();
				break;
		case 57:	/*CircleInvalid*/
				CircleInvalid();
				break;

		default:
			GPC.m_ErrReport.GPWriteWarnLog2("GPExcelWorkSheet", "Unknown Method",iMethod);
			if (flgRet)		 sprintf(oStr,ErrObjSub,met);
			nfunc=0xFFFFFFFFL;
			break;
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
		if (flgRet) strcpy(oStr,str);
		nfunc=0xFFFFFFFFL;
		GPC.m_ErrReport.GPWriteErrorLog("GPExcelOLEWorksheet", "DoMethod",iMethod);
		delete[] str;
	}

	if (flgRet && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
//	delete[] met;
	return nfunc;

}

int GPExcelOLEWorksheet::PrintOutEx(const char* iStr)
{
	int ret=-3;
	const char* pos=iStr;
	COleVariant vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant varray[8];
	int i=0,iv=0;
	char buff[256];

	while (i<8)
	{
		varray[i]=vOpt;
		i++;
	}

	while ((*pos!=0) && (iv<8))
	{
			i=0;
			while ((i<255) && (*pos!=',') && (*pos!=0))
			{
				buff[i]=*pos;
				pos++;
				i++;
			}
			buff[i]=0;
			if (buff[0]!=0)
				varray[iv]=buff;
			if (*pos!=0)
				pos++;
			iv++;
	}

	PrintOut(varray[0],varray[1],varray[2],varray[3],varray[4],varray[5],varray[6]);

	return ret;
}

int GPExcelOLEWorksheet::ProtectEx(const char* iStr)
{
	int ret=-3;
	const char* pos=iStr;
	COleVariant vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant varray[5];
	int i=0,iv=0;
	char buff[256];

	while (i<5)
	{
		varray[i]=vOpt;
		i++;
	}

	while ((*pos!=0) && (iv<5))
	{
			i=0;
			while ((i<255) && (*pos!=',') && (*pos!=0))
			{
				buff[i]=*pos;
				pos++;
				i++;
			}
			buff[i]=0;
			if (buff[0]!=0)
				varray[iv]=buff;
			if (*pos!=0)
				pos++;
			iv++;
	}

	Protect(varray[0],varray[1],varray[2],varray[3],varray[4]);
	return ret;
}

int GPExcelOLEWorksheet::SaveAsEx(const char* iStr)
{
	int ret=-3;
	const char* pos=iStr;
	COleVariant vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant varray[8];
	int i=0,iv=0;
	char buff[256];
	char filename[256];

	while (i<8)
	{
		varray[i]=vOpt;
		i++;
	}
	i=0;
	while ((i<255) && (*pos!=',') && (*pos!=0))
	{
		filename[i]=*pos;
		i++;
		pos++;
	}

	filename[i]=0;
	if (*pos!=0)
	{
		pos++;
		while ((*pos!=0) && (iv<8))
		{
			i=0;
			while ((i<255) && (*pos!=',') && (*pos!=0))
			{
				buff[i]=*pos;
				pos++;
				i++;
			}
			buff[i]=0;
			if (buff[0]!=NULL)
				varray[iv]=buff;
			if (*pos!=0)
				pos++;
			iv++;
		}
	}

	SaveAs(filename,varray[0],varray[1],varray[2],varray[3],varray[4],varray[5],varray[6],varray[7]);
	return ret;
}

int GPExcelOLEWorksheet::PasteSpecialEx(const char* iStr)
{
	int ret=-3;
	return ret;
}

/////////////////////////////////////////////////////////////////////////////
// _Workbook properties

/////////////////////////////////////////////////////////////////////////////
// _Workbook operations
GPExcelOLEWorkbook::~GPExcelOLEWorkbook()
{
	MyIdApp=-1;
	MyIdWorkbook=-1;
	int i=0;
	while (i<N_EXCELWORKSHEET_ARR)
	{
		if (gpWorksheets[i]!=NULL)
		{
			delete gpWorksheets[i];
			gpWorksheets[i]=NULL;
		}
		i++;
	}
}

GPExcelOLEWorkbook::GPExcelOLEWorkbook()
{
	MyIdApp=-1;
	MyIdWorkbook=-1;
	int i=0;
	while (i<N_EXCELWORKSHEET_ARR)
	{
		gpWorksheets[i]=NULL;
		i++;
	}
}		// Calls COleDispatchDriver default constructor
GPExcelOLEWorkbook::GPExcelOLEWorkbook(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch)
{
	MyIdApp=-1;
	MyIdWorkbook=-1;
	int i=0;
	//init gpWorksheets
	Worksheets wrk2;
	wrk2.AttachDispatch(GetSheets());
	int counter=wrk2.GetCount();
	while (i<counter)
	{
		gpWorksheets[i]=new GPExcelOLEWorksheet();
		i++;
	}
	while (i<N_EXCELWORKSHEET_ARR)
	{
		gpWorksheets[i]=NULL;
		i++;
	}
}

LPDISPATCH GPExcelOLEWorkbook::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long GPExcelOLEWorkbook::GetCreator()
{
	long result;
	InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEWorkbook::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEWorkbook::GetAcceptLabelsInFormulas()
{
	BOOL result;
	InvokeHelper(0x5a1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::SetAcceptLabelsInFormulas(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5a1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void GPExcelOLEWorkbook::Activate()
{
	InvokeHelper(0x130, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH GPExcelOLEWorkbook::GetActiveChart()
{
	LPDISPATCH result;
	InvokeHelper(0xb7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEWorkbook::GetActiveSheet()
{
	LPDISPATCH result;
	InvokeHelper(0x133, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long GPExcelOLEWorkbook::GetAutoUpdateFrequency()
{
	long result;
	InvokeHelper(0x5a2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::SetAutoUpdateFrequency(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5a2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL GPExcelOLEWorkbook::GetAutoUpdateSaveChanges()
{
	BOOL result;
	InvokeHelper(0x5a3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::SetAutoUpdateSaveChanges(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5a3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long GPExcelOLEWorkbook::GetChangeHistoryDuration()
{
	long result;
	InvokeHelper(0x5a4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::SetChangeHistoryDuration(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5a4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH GPExcelOLEWorkbook::GetBuiltinDocumentProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x498, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::ChangeFileAccess(long Mode, const VARIANT& WritePassword, const VARIANT& Notify)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x3dd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Mode, &WritePassword, &Notify);
}

void GPExcelOLEWorkbook::ChangeLink(LPCTSTR Name, LPCTSTR NewName, long Type)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_I4;
	InvokeHelper(0x322, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name, NewName, Type);
}

LPDISPATCH GPExcelOLEWorkbook::GetCharts()
{
	LPDISPATCH result;
	InvokeHelper(0x79, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::Close(const VARIANT& SaveChanges, const VARIANT& Filename, const VARIANT& RouteWorkbook)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x115, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &SaveChanges, &Filename, &RouteWorkbook);
}

CString GPExcelOLEWorkbook::GetCodeName()
{
	CString result;
	InvokeHelper(0x55d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString GPExcelOLEWorkbook::Get_CodeName()
{
	CString result;
	InvokeHelper(0x80010000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::Set_CodeName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x80010000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

VARIANT GPExcelOLEWorkbook::GetColors(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x11e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

void GPExcelOLEWorkbook::SetColors(const VARIANT& Index, const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x11e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &Index, &newValue);
}

LPDISPATCH GPExcelOLEWorkbook::GetCommandBars()
{
	LPDISPATCH result;
	InvokeHelper(0x59f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long GPExcelOLEWorkbook::GetConflictResolution()
{
	long result;
	InvokeHelper(0x497, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::SetConflictResolution(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x497, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH GPExcelOLEWorkbook::GetContainer()
{
	LPDISPATCH result;
	InvokeHelper(0x4a6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEWorkbook::GetCreateBackup()
{
	BOOL result;
	InvokeHelper(0x11f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEWorkbook::GetCustomDocumentProperties()
{
	LPDISPATCH result;
	InvokeHelper(0x499, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEWorkbook::GetDate1904()
{
	BOOL result;
	InvokeHelper(0x193, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::SetDate1904(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x193, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void GPExcelOLEWorkbook::DeleteNumberFormat(LPCTSTR NumberFormat)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x18d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 NumberFormat);
}

long GPExcelOLEWorkbook::GetDisplayDrawingObjects()
{
	long result;
	InvokeHelper(0x194, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::SetDisplayDrawingObjects(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x194, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL GPExcelOLEWorkbook::ExclusiveAccess()
{
	BOOL result;
	InvokeHelper(0x490, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

long GPExcelOLEWorkbook::GetFileFormat()
{
	long result;
	InvokeHelper(0x120, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::ForwardMailer()
{
	InvokeHelper(0x3cd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString GPExcelOLEWorkbook::GetFullName()
{
	CString result;
	InvokeHelper(0x121, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEWorkbook::GetHasPassword()
{
	BOOL result;
	InvokeHelper(0x122, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEWorkbook::GetHasRoutingSlip()
{
	BOOL result;
	InvokeHelper(0x3b6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::SetHasRoutingSlip(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3b6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL GPExcelOLEWorkbook::GetIsAddin()
{
	BOOL result;
	InvokeHelper(0x5a5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::SetIsAddin(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5a5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT GPExcelOLEWorkbook::LinkInfo(LPCTSTR Name, long LinkInfo, const VARIANT& Type, const VARIANT& EditionRef)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x327, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Name, LinkInfo, &Type, &EditionRef);
	return result;
}

VARIANT GPExcelOLEWorkbook::LinkSources(const VARIANT& Type)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x328, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Type);
	return result;
}

LPDISPATCH GPExcelOLEWorkbook::GetMailer()
{
	LPDISPATCH result;
	InvokeHelper(0x3d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::MergeWorkbook(const VARIANT& Filename)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x5a6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Filename);
}

BOOL GPExcelOLEWorkbook::GetMultiUserEditing()
{
	BOOL result;
	InvokeHelper(0x491, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString GPExcelOLEWorkbook::GetName()
{
	CString result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEWorkbook::GetNames()
{
	LPDISPATCH result;
	InvokeHelper(0x1ba, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEWorkbook::NewWindow()
{
	LPDISPATCH result;
	InvokeHelper(0x118, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::OpenLinks(LPCTSTR Name, const VARIANT& ReadOnly, const VARIANT& Type)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x323, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name, &ReadOnly, &Type);
}

CString GPExcelOLEWorkbook::GetPath()
{
	CString result;
	InvokeHelper(0x123, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEWorkbook::GetPersonalViewListSettings()
{
	BOOL result;
	InvokeHelper(0x5a7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::SetPersonalViewListSettings(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5a7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL GPExcelOLEWorkbook::GetPersonalViewPrintSettings()
{
	BOOL result;
	InvokeHelper(0x5a8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::SetPersonalViewPrintSettings(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5a8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH GPExcelOLEWorkbook::PivotCaches()
{
	LPDISPATCH result;
	InvokeHelper(0x5a9, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::Post(const VARIANT& DestName)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x48e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &DestName);
}

BOOL GPExcelOLEWorkbook::GetPrecisionAsDisplayed()
{
	BOOL result;
	InvokeHelper(0x195, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::SetPrecisionAsDisplayed(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x195, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void GPExcelOLEWorkbook::PrintOut(const VARIANT& From, const VARIANT& To, const VARIANT& Copies, const VARIANT& Preview, const VARIANT& ActivePrinter, const VARIANT& PrintToFile, const VARIANT& Collate)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x389, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &From, &To, &Copies, &Preview, &ActivePrinter, &PrintToFile, &Collate);
}

void GPExcelOLEWorkbook::PrintPreview(const VARIANT& EnableChanges)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x119, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &EnableChanges);
}

void GPExcelOLEWorkbook::Protect(const VARIANT& Password, const VARIANT& Structure, const VARIANT& Windows)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x11a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Password, &Structure, &Windows);
}

void GPExcelOLEWorkbook::ProtectSharing(const VARIANT& Filename, const VARIANT& Password, const VARIANT& WriteResPassword, const VARIANT& ReadOnlyRecommended, const VARIANT& CreateBackup, const VARIANT& SharingPassword)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x5aa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Filename, &Password, &WriteResPassword, &ReadOnlyRecommended, &CreateBackup, &SharingPassword);
}

BOOL GPExcelOLEWorkbook::GetProtectStructure()
{
	BOOL result;
	InvokeHelper(0x24c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEWorkbook::GetProtectWindows()
{
	BOOL result;
	InvokeHelper(0x127, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEWorkbook::GetReadOnly()
{
	BOOL result;
	InvokeHelper(0x128, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEWorkbook::GetReadOnlyRecommended()
{
	BOOL result;
	InvokeHelper(0x129, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::RefreshAll()
{
	InvokeHelper(0x5ac, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void GPExcelOLEWorkbook::Reply()
{
	InvokeHelper(0x3d1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void GPExcelOLEWorkbook::ReplyAll()
{
	InvokeHelper(0x3d2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void GPExcelOLEWorkbook::RemoveUser(long Index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5ad, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index);
}

long GPExcelOLEWorkbook::GetRevisionNumber()
{
	long result;
	InvokeHelper(0x494, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::Route()
{
	InvokeHelper(0x3b2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL GPExcelOLEWorkbook::GetRouted()
{
	BOOL result;
	InvokeHelper(0x3b7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEWorkbook::GetRoutingSlip()
{
	LPDISPATCH result;
	InvokeHelper(0x3b5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::RunAutoMacros(long Which)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x27a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Which);
}

void GPExcelOLEWorkbook::Save()
{
	InvokeHelper(0x11b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void GPExcelOLEWorkbook::SaveAs(const VARIANT& Filename, const VARIANT& FileFormat, const VARIANT& Password, const VARIANT& WriteResPassword, const VARIANT& ReadOnlyRecommended, const VARIANT& CreateBackup, long AccessMode, const VARIANT& ConflictResolution,
		const VARIANT& AddToMru, const VARIANT& TextCodepage, const VARIANT& TextVisualLayout)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x11c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Filename, &FileFormat, &Password, &WriteResPassword, &ReadOnlyRecommended, &CreateBackup, AccessMode, &ConflictResolution, &AddToMru, &TextCodepage, &TextVisualLayout);
}

void GPExcelOLEWorkbook::SaveCopyAs(const VARIANT& Filename)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xaf, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Filename);
}

BOOL GPExcelOLEWorkbook::GetSaved()
{
	BOOL result;
	InvokeHelper(0x12a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::SetSaved(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x12a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL GPExcelOLEWorkbook::GetSaveLinkValues()
{
	BOOL result;
	InvokeHelper(0x196, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::SetSaveLinkValues(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x196, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void GPExcelOLEWorkbook::SendMail(const VARIANT& Recipients, const VARIANT& Subject, const VARIANT& ReturnReceipt)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x3b3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Recipients, &Subject, &ReturnReceipt);
}

void GPExcelOLEWorkbook::SendMailer(const VARIANT& FileFormat, long Priority)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_I4;
	InvokeHelper(0x3d4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FileFormat, Priority);
}

void GPExcelOLEWorkbook::SetLinkOnData(LPCTSTR Name, const VARIANT& Procedure)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x329, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name, &Procedure);
}

LPDISPATCH GPExcelOLEWorkbook::GetSheets()
{
	LPDISPATCH result;
	InvokeHelper(0x1e5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEWorkbook::GetShowConflictHistory()
{
	BOOL result;
	InvokeHelper(0x493, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::SetShowConflictHistory(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x493, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH GPExcelOLEWorkbook::GetStyles()
{
	LPDISPATCH result;
	InvokeHelper(0x1ed, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::Unprotect(const VARIANT& Password)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x11d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Password);
}

void GPExcelOLEWorkbook::UnprotectSharing(const VARIANT& SharingPassword)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x5af, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &SharingPassword);
}

void GPExcelOLEWorkbook::UpdateFromFile()
{
	InvokeHelper(0x3e3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void GPExcelOLEWorkbook::UpdateLink(const VARIANT& Name, const VARIANT& Type)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x324, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Name, &Type);
}

BOOL GPExcelOLEWorkbook::GetUpdateRemoteReferences()
{
	BOOL result;
	InvokeHelper(0x19b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::SetUpdateRemoteReferences(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x19b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT GPExcelOLEWorkbook::GetUserStatus()
{
	VARIANT result;
	InvokeHelper(0x495, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEWorkbook::GetCustomViews()
{
	LPDISPATCH result;
	InvokeHelper(0x5b0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEWorkbook::GetWindows()
{
	LPDISPATCH result;
	InvokeHelper(0x1ae, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEWorkbook::GetWorksheets()
{
	LPDISPATCH result;
	InvokeHelper(0x1ee, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEWorkbook::GetWriteReserved()
{
	BOOL result;
	InvokeHelper(0x12b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString GPExcelOLEWorkbook::GetWriteReservedBy()
{
	CString result;
	InvokeHelper(0x12c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEWorkbook::GetExcel4IntlMacroSheets()
{
	LPDISPATCH result;
	InvokeHelper(0x245, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLEWorkbook::GetExcel4MacroSheets()
{
	LPDISPATCH result;
	InvokeHelper(0x243, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL GPExcelOLEWorkbook::GetTemplateRemoveExtData()
{
	BOOL result;
	InvokeHelper(0x5b1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::SetTemplateRemoveExtData(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5b1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void GPExcelOLEWorkbook::HighlightChangesOptions(const VARIANT& When, const VARIANT& Who, const VARIANT& Where)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x5b2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &When, &Who, &Where);
}

BOOL GPExcelOLEWorkbook::GetHighlightChangesOnScreen()
{
	BOOL result;
	InvokeHelper(0x5b5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::SetHighlightChangesOnScreen(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5b5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL GPExcelOLEWorkbook::GetKeepChangeHistory()
{
	BOOL result;
	InvokeHelper(0x5b6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::SetKeepChangeHistory(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5b6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL GPExcelOLEWorkbook::GetListChangesOnNewSheet()
{
	BOOL result;
	InvokeHelper(0x5b7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::SetListChangesOnNewSheet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5b7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void GPExcelOLEWorkbook::PurgeChangeHistoryNow(long Days, const VARIANT& SharingPassword)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x5b8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Days, &SharingPassword);
}

void GPExcelOLEWorkbook::AcceptAllChanges(const VARIANT& When, const VARIANT& Who, const VARIANT& Where)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x5ba, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &When, &Who, &Where);
}

void GPExcelOLEWorkbook::RejectAllChanges(const VARIANT& When, const VARIANT& Who, const VARIANT& Where)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x5bb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &When, &Who, &Where);
}

void GPExcelOLEWorkbook::ResetColors()
{
	InvokeHelper(0x5bc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH GPExcelOLEWorkbook::GetVBProject()
{
	LPDISPATCH result;
	InvokeHelper(0x5bd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPExcelOLEWorkbook::FollowHyperlink(LPCTSTR Address, const VARIANT& SubAddress, const VARIANT& NewWindow, const VARIANT& AddHistory, const VARIANT& ExtraInfo, const VARIANT& Method, const VARIANT& HeaderInfo)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x5be, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Address, &SubAddress, &NewWindow, &AddHistory, &ExtraInfo, &Method, &HeaderInfo);
}

void GPExcelOLEWorkbook::AddToFavorites()
{
	InvokeHelper(0x5c4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL GPExcelOLEWorkbook::GetIsInplace()
{
	BOOL result;
	InvokeHelper(0x6f4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

// добавленные функции
LPDISPATCH GPExcelOLEWorkbook::CreateGPExcelRange(const char *iStr) // создание нового Range
{
	LPDISPATCH pDisp=NULL;
	int IdWorksheet;
	int i=0;
	char buff[256];
	const char* pos=iStr;

	// получение IdWorkbook
	while ((*pos!=',') && (*pos!=0))
	{
		buff[i]=*pos;
		pos++;
		i++;
	}
	buff[i]='\0';
	if (*pos==0)
		return pDisp;
	IdWorksheet=atoi(buff);
	pos++;
	// получение Dispatch Range'а
	if ((IdWorksheet>=0) && (IdWorksheet<N_EXCELWORKBOOK_ARR))
	{
		if (gpWorksheets[IdWorksheet]!=NULL)
			pDisp=gpWorksheets[IdWorksheet]->CreateGPExcelRange(pos);
	}

	return pDisp;
}

int GPExcelOLEWorkbook::CreateGPExcelWorksheet(const char *iStr,char* oStr) //сщздание нового листа
{
	int ret=-2;
	int IdWorksheet=0;
	Worksheets wrk;
	int numoflist;
	char bff[256];
	BOOL flg=TRUE;
	const char* pstr=iStr;
	int i=0;

	while ((*pstr!='\0') && (*pstr!=','))
	{
		pstr++;
		bff[i]=iStr[i];
		i++;
	}
	bff[i]='\0';
	m_LastScanf=sscanf(bff,"%d",&numoflist);
	if (numoflist<1)
		return ret;

	wrk.AttachDispatch(GetWorksheets());
	if (wrk.m_lpDispatch==NULL)
		return ret;
	while ((IdWorksheet<N_EXCELWORKSHEET_ARR) && flg)
	{
		if (gpWorksheets[IdWorksheet]!=NULL)
			flg=FALSE;
		IdWorksheet++;
	}
	if (IdWorksheet<N_EXCELWORKSHEET_ARR)
	{
		COleVariant var(long(0)),
                 covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);			;
		LPDISPATCH pDisp=NULL;
		var.lVal=numoflist;
		pDisp=wrk.Add(covOptional,covOptional,covOptional,var);
		gpWorksheets[IdWorksheet]=new GPExcelOLEWorksheet();
		gpWorksheets[IdWorksheet]->m_lpDispatch=pDisp;
		if (pDisp!=NULL)
		{
			ret=IdWorksheet;
			if (oStr!=NULL)
			{
				sprintf(oStr,"%d",IdWorksheet);
			}
		}
	}
	else
	{
		//error
	}
	return ret;
}

int GPExcelOLEWorkbook::CloseGPExcelWorksheet(const char *iStr)
{
	int ret=-2;
	int IdWorksheet=-1;
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
	m_LastScanf=sscanf(bff,"%d",&IdWorksheet);
	if (IdWorksheet<0)
		return ret;

	if (IdWorksheet<N_EXCELWORKBOOK_ARR)
		if(gpWorksheets[IdWorksheet]!=NULL)
		{
			gpWorksheets[IdWorksheet]->Delete();
			delete gpWorksheets[IdWorksheet];
			gpWorksheets[IdWorksheet]=NULL;
			ret= IdWorksheet;
		}
		else
		{
			// error
		}
	else
	{
		// error
	}
	return ret;
}

int GPExcelOLEWorkbook::RefreshGPExcelWorksheets() //reload worksheets
{
	int ret=-3;
	int i=0;
	int counter;
	LPDISPATCH pDisp;
	Worksheets wrk;

	while (i<N_EXCELWORKSHEET_ARR)
	{
		if(gpWorksheets[i]!=NULL)
			delete gpWorksheets[i];
		gpWorksheets[i]=NULL;
		i++;
	}
	wrk.AttachDispatch(GetWorksheets());
	if (wrk.m_lpDispatch==NULL)
		return ret;
	counter=wrk.GetCount();
	i=0;
	while (i<counter)
	{
		gpWorksheets[i]=new GPExcelOLEWorksheet();
		pDisp=wrk.GetItem(COleVariant(short(i+1)));
		if (pDisp!=NULL)
			gpWorksheets[i]->AttachDispatch(pDisp);
		i++;
	}
	return ret;
}

int GPExcelOLEWorkbook::DoMethod(const char* iMethod,char* oStr,BOOL flgRet)
{
//	char *met=new char [(int)strlen(iMethod)+50];
	char met[200];
	strncpy(met,iMethod,195);met[195]=0;
	const char *pos=strchr(iMethod,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc;
	char *fn[91]={
		"Activate","GetAcceptLabelsInFormulas","SetAcceptLabelsInFormulas","AddToFavorites",
		"GetAutoUpdateFrequency","SetAutoUpdateFrequency","GetAutoUpdateSaveChanges","SetAutoUpdateSaveChanges",
		"ChangeFileAccess","ChangeLink","GetCodeName","GetConflictResolution",
		"SetConflictResolution","GetCreateBackup","GetCreator","GetDate1904",
		"SetDate1904","GetDisplayDrawingObjects","SetDisplayDrawingObjects","ExclusiveAccess",
		"GetFileFormat","GetActiveSheet","GetFullName","GetHasPassword",
		"GetHasRoutingSlip","SetHasRoutingSlip","GetHighlightChangesOnScreen","SetHighlightChangesOnScreen",
		"GetIsAddin","SetIsAddin","GetIsInplace","GetKeepChangeHistory",
		"SetKeepChangeHistory","GetListChangesOnNewSheet","SetListChangesOnNewSheet","MergeWorkbook",
		"GetMultiUserEditing","GetName","GetPath","GetPersonalViewListSettings",
		"SetPersonalViewListSettings","GetPersonalViewPrintSettings","SetPersonalViewPrintSettings","Post",
		"GetPrecisionAsDisplayed","SetPrecisionAsDisplayed","GetReadOnly","GetReadOnlyRecommended",
		"RefreshAll","RemoveUser","Reply","ReplyAll",
		"ResetColors","GetRevisionNumber","Route","GetRouted",
		"RunAutoMacros","Save","SaveAs","SaveCopyAs",
		"GetSaved","SetSaved","GetShowConflictHistory","SetShowConflictHistory",
		"GetTemplateRemoveExtData","SetTemplateRemoveExtData","Unprotect","UnprotectSharing",
		"UpdateFromFile","GetUpdateRemoteReferences","SetUpdateRemoteReferences","GetWriteReserved",
		"GetChangeHistoryDuration","SetChangeHistoryDuration","Close","Get_CodeName",
		"Set_CodeName","GetColors","SetColors","PrintOut",
		"PrintPreview","Protect","ProtectSharing","GetProtectStructure",
		"GetProtectWindows","GetUserStatus","HighlightChangesOptions","PurgeChangeHistoryNow",
		"AcceptAllChanges","RejectAllChanges","GetCountWorksheet"};

	if (*met>='0' && *met<='9') nfunc=atoi(met);
	else
		for(nfunc=0;nfunc<91 && _stricmp(met,fn[nfunc])!=0;nfunc++);

	int retint=-123456;
	int atoipos=atoi(pos);
	try
	{
		switch(nfunc)
		{
		case 0:	/*Activate*/
				Activate();
				break;
		case 1:	/*GetAcceptLabelsInFormulas*/
				{
					BOOL val=GetAcceptLabelsInFormulas();
					if (flgRet)
					{
						sprintf(oStr,"%d",val);
					}
				}
				break;
		case 2:	/*SetAcceptLabelsInFormulas*/
				{
					BOOL val=atoipos;
					SetAcceptLabelsInFormulas(val);
				}
				break;
		case 3:	/*AddToFavorites*/
				AddToFavorites();
				break;
		case 4:	/*GetAutoUpdateFrequency*/
				{
					long val=GetAutoUpdateFrequency();
					if (flgRet)
					{
						sprintf(oStr,"%d",val);
					}
				}
				break;
		case 5:	/*SetAutoUpdateFrequency*/
				{
					long val;
					val=atoipos;
					SetAutoUpdateFrequency(val);
				}
				break;
		case 6:	/*GetAutoUpdateSaveChanges*/
				{
					BOOL val=GetAutoUpdateSaveChanges();
					if (flgRet)
					{
						sprintf(oStr,"%d",val);
					}
				}
				break;
		case 7:	/*SetAutoUpdateSaveChanges*/
				{
					BOOL val;
					val=atoipos;
					SetAutoUpdateSaveChanges(val);
				}
				break;
		case 8:	/*ChangeFileAccess*/
				{
		//			ChangeFileAccess(long Mode, const VARIANT& WritePassword, const VARIANT& Notify);
					const char* pos2=pos;
					char buff2[256]="";
					int i=0;
					while ((*pos2!=',') && (*pos2!=0) && (i<255))
					{
						buff2[i]=*pos2;
						pos2++;
						i++;
					}
					buff2[i]='\0';
					pos2++;
					long Mode=atoi(buff2);
					i=0;
					while ((*pos2!=',') && (*pos2!=0) && (i<255))
					{
						buff2[i]=*pos2;
						pos2++;
						i++;
					}
					buff2[i]='\0';
					pos2++;
					COleVariant WritePassword(buff2);
					i=0;
					while ((*pos2!=',') && (*pos2!=0) && (i<255))
					{
						buff2[i]=*pos2;
						pos2++;
						i++;
					}
					buff2[i]='\0';
					pos2++;
					COleVariant Notify(buff2);
					ChangeFileAccess(Mode,WritePassword,Notify);
				}
				break;
		case 9:	/*ChangeLink*/
				//ChangeLink(LPCTSTR Name, LPCTSTR NewName, long Type);
				{
					const char* pos2=pos;
					char buff2[256]="";
					int i=0;
					while ((*pos2!=',') && (*pos2!=0) && (i<255))
					{
						buff2[i]=*pos2;
						pos2++;
						i++;
					}
					buff2[i]='\0';
					pos2++;
					CString Name=buff2;
					i=0;
					while ((*pos2!=',') && (*pos2!=0) && (i<255))
					{
						buff2[i]=*pos2;
						pos2++;
						i++;
					}
					buff2[i]='\0';
					pos2++;
					CString NewName=buff2;
					i=0;
					while ((*pos2!=',') && (*pos2!=0) && (i<255))
					{
						buff2[i]=*pos2;
						pos2++;
						i++;
					}
					buff2[i]='\0';
					pos2++;
					long Type=atoi(buff2);
					ChangeLink(Name,NewName,Type);
				}
				break;
		case 10:	/*GetCodeName*/
				{
					CString str=GetCodeName();
					if (flgRet)
					{
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 11:	/*GetConflictResolution*/
				{
					long val=GetConflictResolution();
					if (flgRet)
					{
						sprintf(oStr,"%d",val);
					}
				}
				break;
		case 12:	/*SetConflictResolution*/
				{
					long val=atoipos;
					SetConflictResolution(val);
				}
				break;
		case 13:	/*GetCreateBackup*/
				{
					BOOL val=GetCreateBackup();
					if (flgRet)
					{
						sprintf(oStr,"%d",val);
					}
				}
				break;
		case 14:	/*GetCreator*/
				{
					long val=GetCreator();
					if (flgRet)
					{
						sprintf(oStr,"%d",val);
					}
				}
				break;
		case 15: /*GetDate1904*/
				{
					BOOL val=GetDate1904();
					if (flgRet)
					{
						sprintf(oStr,"%d",val);
					}
				}
		case 16: /*SetDate1904*/
				{
					BOOL val=atoipos;
					SetDate1904(val);
				}
				break;
		case 17: /*GetDisplayDrawingObjects*/
				{
					long val=GetDisplayDrawingObjects();
					if (flgRet)
					{
						sprintf(oStr,"%d",val);
					}
				}
				break;
		case 18: /*SetDisplayDrawingObjects*/
				{
					long val=atoipos;
					SetDisplayDrawingObjects(val);
				}
				break;
		case 19: /*ExclusiveAccess*/
				{
					BOOL val=ExclusiveAccess();
					if (flgRet)
					{
						sprintf(oStr,"%d",val);
					}
				}
				break;
		case 20: /*GetFileFormat*/
				{
					long val=GetFileFormat();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 21: /*GetActiveSheet*/
				{
					LPDISPATCH pDisp=GetActiveSheet();
					int i=0;
					int val=-1;
					while ((i<N_EXCELWORKSHEET_ARR) && (val<0))
					{
						if (gpWorksheets[i]!=NULL)
							if (pDisp==gpWorksheets[i]->m_lpDispatch)
								val=i;
						i++;
					}
					pDisp->Release();
					if (flgRet)
						sprintf(oStr,"%d\x7F%d\x7F%d",MyIdApp,MyIdWorkbook,val);
				}
				break;
		case 22: /*GetFullName*/
				{
					CString str=GetFullName();
					if (flgRet)
					{
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 23: /*GetHasPassword*/
				{
					BOOL val=GetHasPassword();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 24: /*GetHasRoutingSlip*/
				{
					BOOL val=GetHasRoutingSlip();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 25: /*SetHasRoutingSlip*/
				{
					BOOL val=atoipos;
					SetHasRoutingSlip(val);
				}
				break;
		case 26: /*GetHighlightChangesOnScreen*/
				{
					BOOL val=GetHighlightChangesOnScreen();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 27: /*SetHighlightChangesOnScreen*/
				{
					BOOL val=atoipos;
					SetHighlightChangesOnScreen(val);
				}
				break;
		case 28: /*GetIsAddin*/
				{
					BOOL val=GetIsAddin();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 29: /*SetIsAddin*/
				{
					BOOL val=atoipos;
					SetIsAddin(val);
				}
				break;
		case 30: /*GetIsInplace*/
				{
					BOOL val=GetIsInplace();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 31: /*GetKeepChangeHistory*/
				{
					BOOL val=GetKeepChangeHistory();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 32: /*SetKeepChangeHistory*/
				{
					BOOL val=atoipos;
					SetKeepChangeHistory(val);
				}
				break;
		case 33: /*GetListChangesOnNewSheet*/
				{
					BOOL val=GetListChangesOnNewSheet();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 34: /*SetListChangesOnNewSheet*/
				{
					BOOL val=atoipos;
					SetListChangesOnNewSheet(val);
				}
				break;
		case 35: /*MergeWorkbook*/
				{
					MergeWorkbook(COleVariant(pos));
				}
				break;
		case 36: /*GetMultiUserEditing*/
				{
					BOOL val=GetMultiUserEditing();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 37: /*GetName*/
				{
					CString str=GetName();
					if (flgRet)
					{
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 38: /*GetPath*/
				{
					CString str=GetPath();
					if (flgRet)
					{
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 39: /*GetPersonalViewListSettings*/
				{
					BOOL val=GetPersonalViewListSettings();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 40: /*SetPersonalViewListSettings*/
				{
					BOOL val=atoipos;
					SetPersonalViewListSettings(val);
				}
				break;
		case 41: /*GetPersonalViewPrintSettings*/
				{
					BOOL val=GetPersonalViewPrintSettings();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 42: /*SetPersonalViewPrintSettings*/
				{
					BOOL val=atoipos;
					SetPersonalViewPrintSettings(val);
				}
				break;
		case 43: /*Post*/
				{
					Post(COleVariant(pos));
				}
				break;
		case 44: /*GetPrecisionAsDisplayed*/
				{
					BOOL val=GetPrecisionAsDisplayed();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 45: /*SetPrecisionAsDisplayed*/
				{
					BOOL val=atoipos;
					SetPrecisionAsDisplayed(val);
				}
				break;
		case 46: /*GetReadOnly*/
				{
					BOOL val=GetReadOnly();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 47: /*GetReadOnlyRecommended*/
				{
					BOOL val=GetReadOnlyRecommended();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 48: /*RefreshAll*/
				RefreshAll();
				break;
		case 49: /*RemoveUser*/
				{
					long val=atoipos;
					RemoveUser(val);
				}
				break;
		case 50: /*Reply*/
				Reply();
				break;
		case 51: /*ReplyAll*/
				ReplyAll();
				break;
		case 52: /*ResetColors*/
				ResetColors();
				break;
		case 53: /*GetRevisionNumber*/
				{
					long val=GetRevisionNumber();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 54: /*Route*/
				Route();
				break;
		case 55: /*GetRouted*/
				{
					BOOL val=GetRouted();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 56: /*RunAutoMacros*/
				 {
					long val=atoipos;
					RunAutoMacros(val);
				 }
				 break;
		case 57: /*Save*/
				Save();
				break;
		case 58:
				SaveAsEx(pos);
				break;
		case 59:
				SaveCopyAs(COleVariant(pos));
				break;
		case 60: /*GetSaved*/
				{
					BOOL val=GetSaved();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 61: /*SetSaved*/
				{
					BOOL val=atoipos;
					SetSaved(val);
				}
				break;
		case 62: /*GetShowConflictHistory*/
				{
					BOOL val=GetShowConflictHistory();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 63: /*SetShowConflictHistory*/
				{
					BOOL val=atoipos;
					SetShowConflictHistory(val);
				}
				break;
		case 64: /*GetTemplateRemoveExtData*/
				{
					BOOL val=GetTemplateRemoveExtData();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 65: /*SetTemplateRemoveExtData*/
				{
					BOOL val=atoipos;
					SetTemplateRemoveExtData(val);
				}
				break;
		case 66: /*Unprotect*/
				Unprotect(COleVariant(pos));
				break;
		case 67: /*UnprotectSharing*/
				UnprotectSharing(COleVariant(pos));
				break;
		case 68: /*UpdateFromFile*/
				UpdateFromFile();
				break;
		case 69: /*GetUpdateRemoteReferences*/
				{
					BOOL val=GetUpdateRemoteReferences();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 70: /*SetUpdateRemoteReferences*/
				{
					BOOL val=atoipos;
					SetUpdateRemoteReferences(val);
				}
				break;
		case 71: /*GetWriteReserved*/
				{
					BOOL val=GetWriteReserved();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 72: /*GetChangeHistoryDuration*/
				{
					long val=GetChangeHistoryDuration();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 73: /*SetChangeHistoryDuration*/
				SetChangeHistoryDuration(atoipos);
				break;
		case 74:	/*Close*/
				//CloseEx(pos); // закрывать книгу лучше из приложения Excel (GPExcelOleApplication::CloseGPExcelWorkbook)
				break;
		case 75:	/*Get_CodeName*/
				{
					CString val=Get_CodeName();
					if (flgRet)
					{
						oStr=new char[(int)strlen(val)+1];
						strcpy(oStr,val);
					}
				}
				break;
		case 76:	/*Set_CodeName*/
				Set_CodeName(pos);
				break;
		case 77:	/*GetColors*/
				{
					COleVariant val=GetColors(COleVariant(long(atoipos)));
					if (flgRet)
					{
						CString val2;
						ConvVariantToString(val,val2,",");
						oStr=new char[(int)strlen(val2)+1];
						strcpy(oStr,val2);
					}
				}
				break;
		case 78:	/*SetColors*/
				{
					COleVariant val[2];
					char buff2[256];
					int i=0;

					while ((i<255) && (*pos!=',') && (*pos!=0))
					{
						buff2[i]=*pos;
						i++;
						pos++;
					}
					buff2[i]=0;
					if (*pos!=0)
					{
						val[0]=COleVariant(long(atoi(buff2)));
						pos++;
					}
					else
						val[0]=COleVariant(long(1));
					if (*pos!=0)
						val[1]=COleVariant(long(pos));
					else
						val[1]=COleVariant(long(0));
					SetColors(val[0],val[1]);
				}
				break;
		case 79:	/*PrintOut*/
				PrintOutEx(pos);
				break;
		case 80:	/*PrintPreview*/
				PrintPreview(COleVariant(long(atoipos)));
				break;
		case 81:	/*Protect*/
				ProtectEx(pos);
				break;
		case 82:	/*ProtectSharing*/
				ProtectSharingEx(pos);
				break;
		case 83:	/*GetProtectStructure*/
				{
					BOOL val=GetProtectStructure();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
		case 84:	/*GetProtectWindows*/
				{
					BOOL val=GetProtectWindows();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 85:	/*GetUserStatus*/
				{
					COleVariant val=GetUserStatus();
					if((flgRet) && (val.vt==VT_ARRAY))
					{
						CString str;
						ConvertToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 86:	/*HighlightChangesOptions*/
				HighlightChangesOptionsEx(pos);
				break;
		case 87:	/*PurgeChangeHistoryNow*/
				PurgeChangeHistoryNowEx(pos);
				break;
		case 88:	/*AcceptAllChanges*/
				{
					COleVariant val=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					AcceptAllChanges(val,val,val);
				}
				break;
		case 89:	/*RejectAllChanges*/
				{
					COleVariant val=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					RejectAllChanges(val,val,val);
				}
				break;
		case 90:	/*GetCountWorksheet*/
				{
					int IdWorksheet=0;
					int counter=0;
					while(IdWorksheet<N_EXCELWORKSHEET_ARR)
					{
						if (gpWorksheets[IdWorksheet]!=NULL)
							counter++;
						IdWorksheet++;
					}
				}
				break;

		default:
			GPC.m_ErrReport.GPWriteWarnLog2("GPExcelWorkbook", "Unknown Method",iMethod);
			if (flgRet)		 sprintf(oStr,ErrObjSub,met);
			nfunc=0xFFFFFFFFL;
			break;
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
		GPC.m_ErrReport.GPWriteErrorLog("GPExcelOLEWorkbook", "DoMethod",iMethod);
		delete[] str;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
	return nfunc;

}

int GPExcelOLEWorkbook::DoWsMethod(int IdWorksheet,const char* iMethod,char* oStr,BOOL flgRet)
{
	int ret=-3;

	if ((IdWorksheet>=0)  && (IdWorksheet<N_EXCELWORKSHEET_ARR))
		if(gpWorksheets[IdWorksheet]!=NULL)
		{
			ret=gpWorksheets[IdWorksheet]->DoMethod(iMethod,oStr,flgRet);
		}

	return ret;
}

int GPExcelOLEWorkbook::SaveAsEx(const char *iStr)
{
	int ret=-1;
	const char* pos=iStr;
	int i=0;
	char buff[256];
	COleVariant varray[10];
	COleVariant varbool(short(FALSE));
	COleVariant vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	long Access=0;

	while (i<10)
	{
		varray[i]=vOpt;
		i++;
	}
	varray[4]=varbool;
	varray[5]=varbool;
	varray[8]=varbool;

	if (*pos!=0)
	{
		i=0;
		while ((i<255) && (*pos!=0) && (*pos!=','))//read filename
		{
			buff[i]=*pos;
			pos++;
			i++;
		}
		buff[i]='\0';
		if (buff[0]!=0)
			varray[0]=buff;
	}
	if (*pos!=0)
	{
		i=0;
		pos++;
		while ((i<255) && (*pos!=0) && (*pos!=','))//read FileFormat
		{
			buff[i]=*pos;
			pos++;
			i++;
		}
		buff[i]='\0';
		if (buff[0]!=0)
			varray[1]=buff;
	}
	if (*pos!=0)
	{
		i=0;
		pos++;
		while ((i<255) && (*pos!=0) && (*pos!=','))//read Password
		{
			buff[i]=*pos;
			pos++;
			i++;
		}
		buff[i]='\0';
		if (buff[0]!=0)
			varray[2]=buff;
	}
	if (*pos!=0)
	{
		i=0;
		pos++;
		while ((i<255) && (*pos!=0) && (*pos!=','))//read WriteResPassword
		{
			buff[i]=*pos;
			pos++;
			i++;
		}
		buff[i]='\0';
		if (buff[0]!=0)
			varray[3]=buff;
	}
	if (*pos!=0)
	{
		i=0;
		pos++;
		while ((i<255) && (*pos!=0) && (*pos!=','))//read ReadOnlyRecommended
		{
			buff[i]=*pos;
			pos++;
			i++;
		}
		buff[i]='\0';
		if (buff[0]!=0)
			varray[4]=buff;
	}
	if (*pos!=0)
	{
		i=0;
		pos++;
		while ((i<255) && (*pos!=0) && (*pos!=','))//read CreateBackup
		{
			buff[i]=*pos;
			pos++;
			i++;
		}
		buff[i]='\0';
		if (buff[0]!=0)
			varray[5]=buff;
	}
	if (*pos!=0)
	{
		i=0;
		pos++;
		while ((i<255) && (*pos!=0) && (*pos!=','))//read ConflictResolution
		{
			buff[i]=*pos;
			pos++;
			i++;
		}
		buff[i]='\0';
		if (buff[0]!=0)
			varray[6]=buff;
	}
	if (*pos!=0)
	{
		i=0;
		pos++;
		while ((i<255) && (*pos!=0) && (*pos!=','))//read AddToMru
		{
			buff[i]=*pos;
			pos++;
			i++;
		}
		buff[i]='\0';
		if (buff[0]!=0)
			varray[7]=buff;
	}
	if (*pos!=0)
	{
		i=0;
		pos++;
		while ((i<255) && (*pos!=0) && (*pos!=','))//read TextCodePage
		{
			buff[i]=*pos;
			pos++;
			i++;
		}
		buff[i]='\0';
		if (buff[0]!=0)
			varray[8]=buff;
	}
	if (*pos!=0)
	{
		i=0;
		pos++;
		while ((i<255) && (*pos!=0) && (*pos!=','))//read TextVisualLayout
		{
			buff[i]=*pos;
			pos++;
			i++;
		}
		buff[i]='\0';
		if (buff[0]!=0)
			varray[9]=buff;
	}


	SaveAs(varray[0],varray[1],varray[2],varray[3],varray[4],varray[5]
		,Access,varray[6],varray[7],varray[8],varray[9]);

	return ret;
}

int GPExcelOLEWorkbook::CloseEx(const char* iStr)
{
	int ret=-2;
	const char* pos=iStr;
	char buff[256];
	CString str;
	int i;
	int iparam=0;
	int paramcounter=3;
	COleVariant val[3];

	CString tmpCString=iStr;
	ConvertStringToString(tmpCString,str);
	pos=str;
	while((iparam<paramcounter) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!='\1') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		if (buff[0]!=0)
			switch (iparam)
				{
					case 1:	val[iparam]=COleVariant(buff);
							break;
					default:	val[iparam]=COleVariant(short(atoi(buff)));
							break;
				}
		else
			val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		iparam++;
	}
	while (iparam<paramcounter)
	{
		val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		iparam++;
	}

	// надо перебрать все листы и выключить их !!!
	Close(val[0],val[1],val[2]);
	return ret;
}

int GPExcelOLEWorkbook::PrintOutEx(const char* iStr)
{
	int ret=-2;
	const char* pos=iStr;
	char buff[256];
	CString str;
	int i;
	int iparam=0;
	int paramcounter=7;
	COleVariant val[7];

	CString tmpCString=iStr;
	ConvertStringToString(tmpCString,str);
	pos=str;
	while((iparam<paramcounter) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!='\1') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		if (buff[0]!=0)
			switch (iparam)
				{
					case 0:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
					case 1:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
					case 2:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
					case 4:	val[iparam]=COleVariant(buff);
							break;
					default:	val[iparam]=COleVariant(short(atoi(buff)));
							break;
				}
		else
			val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		iparam++;
	}
	while (iparam<paramcounter)
	{
		val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		iparam++;
	}

	PrintOut(val[0],val[1],val[2],val[3],val[4],val[5],val[6]);
	return ret;
}

int GPExcelOLEWorkbook::ProtectEx(const char* iStr)
{
	int ret=-2;
	const char* pos=iStr;
	char buff[256];
	CString str;
	int i;
	int iparam=0;
	int paramcounter=3;
	COleVariant val[3];

	CString tmpCString=iStr;
	ConvertStringToString(tmpCString,str);
	pos=str;
	while((iparam<paramcounter) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!='\1') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		if (buff[0]!=0)
			switch (iparam)
				{
					case 0:	val[iparam]=COleVariant(buff);
							break;
					default:	val[iparam]=COleVariant(short(atoi(buff)));
							break;
				}
		else
			val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		iparam++;
	}
	while (iparam<paramcounter)
	{
		val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		iparam++;
	}

	Protect(val[0],val[1],val[2]);
	return ret;
}

int GPExcelOLEWorkbook::ProtectSharingEx(const char* iStr)
{
	int ret=-2;
	const char* pos=iStr;
	char buff[256];
	CString str;
	int i;
	int iparam=0;
	int paramcounter=6;
	COleVariant val[6];

	CString tmpCString=iStr;
	ConvertStringToString(tmpCString,str);
	pos=str;
	while((iparam<paramcounter) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!='\1') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		if (buff[0]!=0)
			switch (iparam)
				{
					case 0:	val[iparam]=COleVariant(buff);
							break;
					case 1:	val[iparam]=COleVariant(buff);
							break;
					case 2:	val[iparam]=COleVariant(buff);
							break;
					case 5:	val[iparam]=COleVariant(buff);
							break;
					default:	val[iparam]=COleVariant(short(atoi(buff)));
							break;
				}
		else
			val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		iparam++;
	}
	while (iparam<paramcounter)
	{
		val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		iparam++;
	}

	ProtectSharing(val[0],val[1],val[2],val[3],val[4],val[5]);
	return ret;
}

int GPExcelOLEWorkbook::HighlightChangesOptionsEx(const char* iStr)
{
	int ret=-2;
	const char* pos=iStr;
	char buff[256];
	CString str;
	int i;
	int iparam=0;
	int paramcounter=3;
	COleVariant val[3];

	CString tmpCString=iStr;
	ConvertStringToString(tmpCString,str);
	pos=str;
	while((iparam<paramcounter) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!='\1') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		if (buff[0]!=0)
			switch (iparam)
				{
					case 0:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
					default:	val[iparam]=COleVariant(buff);
							break;
				}
		else
			val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		iparam++;
	}
	while (iparam<paramcounter)
	{
		val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		iparam++;
	}

	HighlightChangesOptions(val[0],val[1],val[2]);
	return ret;
}

int GPExcelOLEWorkbook::PurgeChangeHistoryNowEx(const char* iStr)
{
	int ret=-2;
	const char* pos=iStr;
	char buff[256];
	*buff=0;
	CString str;
	int i;
	int iparam=0;
	int paramcounter=2;
	COleVariant val[2];

	CString tmpCString=iStr;
	ConvertStringToString(tmpCString,str);
	pos=str;
	while((iparam<paramcounter) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!='\1') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		if (buff[0]!=0)
			switch (iparam)
				{
					case 0:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
					default:	val[iparam]=COleVariant(buff);
							break;
				}
		else
			switch (iparam)
				{
					case 0:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
					default:	val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
							break;
				}
		iparam++;
	}
	while (iparam<paramcounter)
	{
		switch (iparam)
		{
			case 0:	val[iparam]=COleVariant(long(atoi(buff)));
					break;
			default:	val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					break;
		}
		iparam++;
	}

	PurgeChangeHistoryNow(val[0].lVal,val[1]);
	return ret;
}

/////////////////////////////////////////////////////////////////////////////
// Workbooks properties

/////////////////////////////////////////////////////////////////////////////
// Workbooks operations

LPDISPATCH Workbooks::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Workbooks::GetCreator()
{
	long result;
	InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Workbooks::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Workbooks::Add(const VARIANT& Template)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xb5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Template);
	return result;
}

void Workbooks::Close()
{
	InvokeHelper(0x115, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long Workbooks::GetCount()
{
	long result;
	InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Workbooks::GetItem(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xaa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

LPUNKNOWN Workbooks::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

LPDISPATCH Workbooks::Open(LPCTSTR Filename, const VARIANT& UpdateLinks, const VARIANT& ReadOnly, const VARIANT& Format, const VARIANT& Password, const VARIANT& WriteResPassword, const VARIANT& IgnoreReadOnlyRecommended, const VARIANT& Origin,
		const VARIANT& Delimiter, const VARIANT& Editable, const VARIANT& Notify, const VARIANT& Converter, const VARIANT& AddToMru)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x2aa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Filename, &UpdateLinks, &ReadOnly, &Format, &Password, &WriteResPassword, &IgnoreReadOnlyRecommended, &Origin, &Delimiter, &Editable, &Notify, &Converter, &AddToMru);
	return result;
}

void Workbooks::OpenText(LPCTSTR Filename, const VARIANT& Origin, const VARIANT& StartRow, const VARIANT& DataType, long TextQualifier, const VARIANT& ConsecutiveDelimiter, const VARIANT& Tab, const VARIANT& Semicolon, const VARIANT& Comma,
		const VARIANT& Space, const VARIANT& Other, const VARIANT& OtherChar, const VARIANT& FieldInfo, const VARIANT& TextVisualLayout)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x2ab, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Filename, &Origin, &StartRow, &DataType, TextQualifier, &ConsecutiveDelimiter, &Tab, &Semicolon, &Comma, &Space, &Other, &OtherChar, &FieldInfo, &TextVisualLayout);
}

LPDISPATCH Workbooks::Get_Default(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Range properties

/////////////////////////////////////////////////////////////////////////////
// Range operations

LPDISPATCH GPExcelOLERange::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long GPExcelOLERange::GetCreator()
{
	long result;
	InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLERange::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::Activate()
{
	InvokeHelper(0x130, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

VARIANT GPExcelOLERange::GetAddIndent()
{
	VARIANT result;
	InvokeHelper(0x427, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetAddIndent(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x427, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

CString GPExcelOLERange::GetAddress(const VARIANT& RowAbsolute, const VARIANT& ColumnAbsolute, long ReferenceStyle, const VARIANT& External, const VARIANT& RelativeTo)
{
	CString result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_I4 VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xec, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		&RowAbsolute, &ColumnAbsolute, ReferenceStyle, &External, &RelativeTo);
	return result;
}

CString GPExcelOLERange::GetAddressLocal(const VARIANT& RowAbsolute, const VARIANT& ColumnAbsolute, long ReferenceStyle, const VARIANT& External, const VARIANT& RelativeTo)
{
	CString result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_I4 VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1b5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		&RowAbsolute, &ColumnAbsolute, ReferenceStyle, &External, &RelativeTo);
	return result;
}

void GPExcelOLERange::AdvancedFilter(long Action, const VARIANT& CriteriaRange, const VARIANT& CopyToRange, const VARIANT& Unique)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x36c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Action, &CriteriaRange, &CopyToRange, &Unique);
}

void GPExcelOLERange::ApplyNames(const VARIANT& Names, const VARIANT& IgnoreRelativeAbsolute, const VARIANT& UseRowColumnNames, const VARIANT& OmitColumn, const VARIANT& OmitRow, long Order, const VARIANT& AppendLast)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_I4 VTS_VARIANT;
	InvokeHelper(0x1b9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Names, &IgnoreRelativeAbsolute, &UseRowColumnNames, &OmitColumn, &OmitRow, Order, &AppendLast);
}

void GPExcelOLERange::ApplyOutlineStyles()
{
	InvokeHelper(0x1c0, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH GPExcelOLERange::GetAreas()
{
	LPDISPATCH result;
	InvokeHelper(0x238, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString GPExcelOLERange::AutoComplete(LPCTSTR String)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4a1, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		String);
	return result;
}

void GPExcelOLERange::AutoFill(LPDISPATCH Destination, long Type)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x1c1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Destination, Type);
}

void GPExcelOLERange::AutoFilter(const VARIANT& Field, const VARIANT& Criteria1, long Operator, const VARIANT& Criteria2, const VARIANT& VisibleDropDown)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_I4 VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x319, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Field, &Criteria1, Operator, &Criteria2, &VisibleDropDown);
}

void GPExcelOLERange::AutoFit()
{
	InvokeHelper(0xed, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void GPExcelOLERange::AutoFormat(long Format, const VARIANT& Number, const VARIANT& Font, const VARIANT& Alignment, const VARIANT& Border, const VARIANT& Pattern, const VARIANT& Width)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x72, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Format, &Number, &Font, &Alignment, &Border, &Pattern, &Width);
}

void GPExcelOLERange::AutoOutline()
{
	InvokeHelper(0x40c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void GPExcelOLERange::BorderAround(const VARIANT& LineStyle, long Weight, long ColorIndex, const VARIANT& Color)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_I4 VTS_I4 VTS_VARIANT;
	InvokeHelper(0x42b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &LineStyle, Weight, ColorIndex, &Color);
}

LPDISPATCH GPExcelOLERange::GetBorders()
{
	LPDISPATCH result;
	InvokeHelper(0x1b3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::Calculate()
{
	InvokeHelper(0x117, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH GPExcelOLERange::GetCells()
{
	LPDISPATCH result;
	InvokeHelper(0xee, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLERange::GetCharacters(const VARIANT& Start, const VARIANT& Length)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x25b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&Start, &Length);
	return result;
}

void GPExcelOLERange::CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest, const VARIANT& IgnoreInitialAlefHamza, const VARIANT& IgnoreFinalYaa, const VARIANT& SpellScript)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1f9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &CustomDictionary, &IgnoreUppercase, &AlwaysSuggest, &IgnoreInitialAlefHamza, &IgnoreFinalYaa, &SpellScript);
}

void GPExcelOLERange::Clear()
{
	InvokeHelper(0x6f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void GPExcelOLERange::ClearContents()
{
	InvokeHelper(0x71, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void GPExcelOLERange::ClearFormats()
{
	InvokeHelper(0x70, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void GPExcelOLERange::ClearNotes()
{
	InvokeHelper(0xef, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void GPExcelOLERange::ClearOutline()
{
	InvokeHelper(0x40d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long GPExcelOLERange::GetColumn()
{
	long result;
	InvokeHelper(0xf0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLERange::ColumnDifferences(const VARIANT& Comparison)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1fe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Comparison);
	return result;
}

LPDISPATCH GPExcelOLERange::GetColumns()
{
	LPDISPATCH result;
	InvokeHelper(0xf1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT GPExcelOLERange::GetColumnWidth()
{
	VARIANT result;
	InvokeHelper(0xf2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetColumnWidth(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xf2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void GPExcelOLERange::Consolidate(const VARIANT& Sources, const VARIANT& Function, const VARIANT& TopRow, const VARIANT& LeftColumn, const VARIANT& CreateLinks)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1e2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Sources, &Function, &TopRow, &LeftColumn, &CreateLinks);
}

void GPExcelOLERange::Copy(const VARIANT& Destination)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x227, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Destination);
}

long GPExcelOLERange::CopyFromRecordset(LPUNKNOWN Data, const VARIANT& MaxRows, const VARIANT& MaxColumns)
{
	long result;
	static BYTE parms[] =
		VTS_UNKNOWN VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x480, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		Data, &MaxRows, &MaxColumns);
	return result;
}

void GPExcelOLERange::CopyPicture(long Appearance, long Format)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Appearance, Format);
}

long GPExcelOLERange::GetCount()
{
	long result;
	InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::CreateNames(const VARIANT& Top, const VARIANT& Left, const VARIANT& Bottom, const VARIANT& Right)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1c9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Top, &Left, &Bottom, &Right);
}

void GPExcelOLERange::CreatePublisher(const VARIANT& Edition, long Appearance, const VARIANT& ContainsPICT, const VARIANT& ContainsBIFF, const VARIANT& ContainsRTF, const VARIANT& ContainsVALU)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1ca, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Edition, Appearance, &ContainsPICT, &ContainsBIFF, &ContainsRTF, &ContainsVALU);
}

LPDISPATCH GPExcelOLERange::GetCurrentArray()
{
	LPDISPATCH result;
	InvokeHelper(0x1f5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLERange::GetCurrentRegion()
{
	LPDISPATCH result;
	InvokeHelper(0xf3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::Cut(const VARIANT& Destination)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x235, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Destination);
}

void GPExcelOLERange::DataSeries(const VARIANT& Rowcol, long Type, long Date, const VARIANT& Step, const VARIANT& Stop, const VARIANT& Trend)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1d0, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Rowcol, Type, Date, &Step, &Stop, &Trend);
}

VARIANT GPExcelOLERange::Get_Default(const VARIANT& RowIndex, const VARIANT& ColumnIndex)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		&RowIndex, &ColumnIndex);
	return result;
}

void GPExcelOLERange::Set_Default(const VARIANT& RowIndex, const VARIANT& ColumnIndex, const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &RowIndex, &ColumnIndex, &newValue);
}

void GPExcelOLERange::Delete(const VARIANT& Shift)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x75, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Shift);
}

LPDISPATCH GPExcelOLERange::GetDependents()
{
	LPDISPATCH result;
	InvokeHelper(0x21f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT GPExcelOLERange::DialogBox_()
{
	VARIANT result;
	InvokeHelper(0xf5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLERange::GetDirectDependents()
{
	LPDISPATCH result;
	InvokeHelper(0x221, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLERange::GetDirectPrecedents()
{
	LPDISPATCH result;
	InvokeHelper(0x222, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT GPExcelOLERange::EditionOptions(long Type, long Option, const VARIANT& Name, const VARIANT& Reference, long Appearance, long ChartSize, const VARIANT& Format)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT VTS_I4 VTS_I4 VTS_VARIANT;
	InvokeHelper(0x46b, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Type, Option, &Name, &Reference, Appearance, ChartSize, &Format);
	return result;
}

LPDISPATCH GPExcelOLERange::GetEnd(long Direction)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1f4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		Direction);
	return result;
}

LPDISPATCH GPExcelOLERange::GetEntireColumn()
{
	LPDISPATCH result;
	InvokeHelper(0xf6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLERange::GetEntireRow()
{
	LPDISPATCH result;
	InvokeHelper(0xf7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::FillDown()
{
	InvokeHelper(0xf8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void GPExcelOLERange::FillLeft()
{
	InvokeHelper(0xf9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void GPExcelOLERange::FillRight()
{
	InvokeHelper(0xfa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void GPExcelOLERange::FillUp()
{
	InvokeHelper(0xfb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH GPExcelOLERange::Find(const VARIANT& What, const VARIANT& After, const VARIANT& LookIn, const VARIANT& LookAt, const VARIANT& SearchOrder, long SearchDirection, const VARIANT& MatchCase, const VARIANT& MatchByte,
		const VARIANT& MatchControlCharacters, const VARIANT& MatchDiacritics, const VARIANT& MatchKashida, const VARIANT& MatchAlefHamza)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x18e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&What, &After, &LookIn, &LookAt, &SearchOrder, SearchDirection, &MatchCase, &MatchByte, &MatchControlCharacters, &MatchDiacritics, &MatchKashida, &MatchAlefHamza);
	return result;
}

LPDISPATCH GPExcelOLERange::FindNext(const VARIANT& After)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x18f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&After);
	return result;
}

LPDISPATCH GPExcelOLERange::FindPrevious(const VARIANT& After)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x190, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&After);
	return result;
}

LPDISPATCH GPExcelOLERange::GetFont()
{
	LPDISPATCH result;
	InvokeHelper(0x92, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT GPExcelOLERange::GetFormula()
{
	VARIANT result;
	InvokeHelper(0x105, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetFormula(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x105, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPExcelOLERange::GetFormulaArray()
{
	VARIANT result;
	InvokeHelper(0x24a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetFormulaArray(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x24a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long GPExcelOLERange::GetFormulaLabel()
{
	long result;
	InvokeHelper(0x564, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetFormulaLabel(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x564, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

VARIANT GPExcelOLERange::GetFormulaHidden()
{
	VARIANT result;
	InvokeHelper(0x106, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetFormulaHidden(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x106, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPExcelOLERange::GetFormulaLocal()
{
	VARIANT result;
	InvokeHelper(0x107, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetFormulaLocal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x107, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPExcelOLERange::GetFormulaR1C1()
{
	VARIANT result;
	InvokeHelper(0x108, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetFormulaR1C1(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x108, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPExcelOLERange::GetFormulaR1C1Local()
{
	VARIANT result;
	InvokeHelper(0x109, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetFormulaR1C1Local(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x109, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void GPExcelOLERange::FunctionWizard()
{
	InvokeHelper(0x23b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL GPExcelOLERange::GoalSeek(const VARIANT& Goal, LPDISPATCH ChangingCell)
{
	BOOL result;
	static BYTE parms[] =
		VTS_VARIANT VTS_DISPATCH;
	InvokeHelper(0x1d8, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		&Goal, ChangingCell);
	return result;
}

VARIANT GPExcelOLERange::Group(const VARIANT& Start, const VARIANT& End, const VARIANT& By, const VARIANT& Periods)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Start, &End, &By, &Periods);
	return result;
}

VARIANT GPExcelOLERange::GetHasArray()
{
	VARIANT result;
	InvokeHelper(0x10a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT GPExcelOLERange::GetHasFormula()
{
	VARIANT result;
	InvokeHelper(0x10b, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT GPExcelOLERange::GetHeight()
{
	VARIANT result;
	InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT GPExcelOLERange::GetHidden()
{
	VARIANT result;
	InvokeHelper(0x10c, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetHidden(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x10c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPExcelOLERange::GetHorizontalAlignment()
{
	VARIANT result;
	InvokeHelper(0x88, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetHorizontalAlignment(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x88, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPExcelOLERange::GetIndentLevel()
{
	VARIANT result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetIndentLevel(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void GPExcelOLERange::InsertIndent(long InsertAmount)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x565, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 InsertAmount);
}

void GPExcelOLERange::Insert(const VARIANT& Shift)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xfc, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Shift);
}

LPDISPATCH GPExcelOLERange::GetInterior()
{
	LPDISPATCH result;
	InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT GPExcelOLERange::GetItem(const VARIANT& RowIndex, const VARIANT& ColumnIndex)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xaa, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		&RowIndex, &ColumnIndex);
	return result;
}

void GPExcelOLERange::SetItem(const VARIANT& RowIndex, const VARIANT& ColumnIndex, const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xaa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &RowIndex, &ColumnIndex, &newValue);
}

void GPExcelOLERange::Justify()
{
	InvokeHelper(0x1ef, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

VARIANT GPExcelOLERange::GetLeft()
{
	VARIANT result;
	InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

long GPExcelOLERange::GetListHeaderRows()
{
	long result;
	InvokeHelper(0x4a3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::ListNames()
{
	InvokeHelper(0xfd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long GPExcelOLERange::GetLocationInTable()
{
	long result;
	InvokeHelper(0x2b3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

VARIANT GPExcelOLERange::GetLocked()
{
	VARIANT result;
	InvokeHelper(0x10d, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetLocked(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x10d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void GPExcelOLERange::Merge(const VARIANT& Across)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x234, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Across);
}

void GPExcelOLERange::UnMerge()
{
	InvokeHelper(0x568, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH GPExcelOLERange::GetMergeArea()
{
	LPDISPATCH result;
	InvokeHelper(0x569, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT GPExcelOLERange::GetMergeCells()
{
	VARIANT result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetMergeCells(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xd0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPExcelOLERange::GetName()
{
	VARIANT result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetName(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x6e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void GPExcelOLERange::NavigateArrow(const VARIANT& TowardPrecedent, const VARIANT& ArrowNumber, const VARIANT& LinkNumber)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x408, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TowardPrecedent, &ArrowNumber, &LinkNumber);
}

LPUNKNOWN GPExcelOLERange::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLERange::GetNext()
{
	LPDISPATCH result;
	InvokeHelper(0x1f6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString GPExcelOLERange::NoteText(const VARIANT& Text, const VARIANT& Start, const VARIANT& Length)
{
	CString result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x467, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		&Text, &Start, &Length);
	return result;
}

VARIANT GPExcelOLERange::GetNumberFormat()
{
	VARIANT result;
	InvokeHelper(0xc1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetNumberFormat(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xc1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPExcelOLERange::GetNumberFormatLocal()
{
	VARIANT result;
	InvokeHelper(0x449, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetNumberFormatLocal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x449, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

LPDISPATCH GPExcelOLERange::GetOffset(const VARIANT& RowOffset, const VARIANT& ColumnOffset)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xfe, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&RowOffset, &ColumnOffset);
	return result;
}

VARIANT GPExcelOLERange::GetOrientation()
{
	VARIANT result;
	InvokeHelper(0x86, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetOrientation(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x86, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPExcelOLERange::GetOutlineLevel()
{
	VARIANT result;
	InvokeHelper(0x10f, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetOutlineLevel(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x10f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long GPExcelOLERange::GetPageBreak()
{
	long result;
	InvokeHelper(0xff, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetPageBreak(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xff, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void GPExcelOLERange::Parse(const VARIANT& ParseLine, const VARIANT& Destination)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1dd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &ParseLine, &Destination);
}

void GPExcelOLERange::PasteSpecial(long Paste, long Operation, const VARIANT& SkipBlanks, const VARIANT& Transpose)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Paste, Operation, &SkipBlanks, &Transpose);
}

LPDISPATCH GPExcelOLERange::GetPivotField()
{
	LPDISPATCH result;
	InvokeHelper(0x2db, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLERange::GetPivotItem()
{
	LPDISPATCH result;
	InvokeHelper(0x2e4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLERange::GetPivotTable()
{
	LPDISPATCH result;
	InvokeHelper(0x2cc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLERange::GetPrecedents()
{
	LPDISPATCH result;
	InvokeHelper(0x220, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT GPExcelOLERange::GetPrefixCharacter()
{
	VARIANT result;
	InvokeHelper(0x1f8, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLERange::GetPrevious()
{
	LPDISPATCH result;
	InvokeHelper(0x1f7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::PrintOut(const VARIANT& From, const VARIANT& To, const VARIANT& Copies, const VARIANT& Preview, const VARIANT& ActivePrinter, const VARIANT& PrintToFile, const VARIANT& Collate)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x389, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &From, &To, &Copies, &Preview, &ActivePrinter, &PrintToFile, &Collate);
}

void GPExcelOLERange::PrintPreview(const VARIANT& EnableChanges)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x119, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &EnableChanges);
}

LPDISPATCH GPExcelOLERange::GetQueryTable()
{
	LPDISPATCH result;
	InvokeHelper(0x56a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLERange::GetRange(const VARIANT& Cell1, const VARIANT& Cell2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xc5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&Cell1, &Cell2);
	return result;
}

void GPExcelOLERange::RemoveSubtotal()
{
	InvokeHelper(0x373, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL GPExcelOLERange::Replace(const VARIANT& What, const VARIANT& Replacement, const VARIANT& LookAt, const VARIANT& SearchOrder, const VARIANT& MatchCase, const VARIANT& MatchByte, const VARIANT& MatchControlCharacters, const VARIANT& MatchDiacritics,
		const VARIANT& MatchKashida, const VARIANT& MatchAlefHamza)
{
	BOOL result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xe2, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		&What, &Replacement, &LookAt, &SearchOrder, &MatchCase, &MatchByte, &MatchControlCharacters, &MatchDiacritics, &MatchKashida, &MatchAlefHamza);
	return result;
}

LPDISPATCH GPExcelOLERange::GetResize(const VARIANT& RowSize, const VARIANT& ColumnSize)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x100, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&RowSize, &ColumnSize);
	return result;
}

long GPExcelOLERange::GetRow()
{
	long result;
	InvokeHelper(0x101, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLERange::RowDifferences(const VARIANT& Comparison)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1ff, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Comparison);
	return result;
}

VARIANT GPExcelOLERange::GetRowHeight()
{
	VARIANT result;
	InvokeHelper(0x110, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetRowHeight(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x110, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

LPDISPATCH GPExcelOLERange::GetRows()
{
	LPDISPATCH result;
	InvokeHelper(0x102, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT GPExcelOLERange::Run(const VARIANT& Arg1, const VARIANT& Arg2, const VARIANT& Arg3, const VARIANT& Arg4, const VARIANT& Arg5, const VARIANT& Arg6, const VARIANT& Arg7, const VARIANT& Arg8, const VARIANT& Arg9, const VARIANT& Arg10,
		const VARIANT& Arg11, const VARIANT& Arg12, const VARIANT& Arg13, const VARIANT& Arg14, const VARIANT& Arg15, const VARIANT& Arg16, const VARIANT& Arg17, const VARIANT& Arg18, const VARIANT& Arg19, const VARIANT& Arg20,
		const VARIANT& Arg21, const VARIANT& Arg22, const VARIANT& Arg23, const VARIANT& Arg24, const VARIANT& Arg25, const VARIANT& Arg26, const VARIANT& Arg27, const VARIANT& Arg28, const VARIANT& Arg29, const VARIANT& Arg30)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x103, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
	return result;
}

void GPExcelOLERange::Select()
{
	InvokeHelper(0xeb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void GPExcelOLERange::Show()
{
	InvokeHelper(0x1f0, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void GPExcelOLERange::ShowDependents(const VARIANT& Remove)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x36d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Remove);
}

VARIANT GPExcelOLERange::GetShowDetail()
{
	VARIANT result;
	InvokeHelper(0x249, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetShowDetail(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x249, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void GPExcelOLERange::ShowErrors()
{
	InvokeHelper(0x36e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void GPExcelOLERange::ShowPrecedents(const VARIANT& Remove)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x36f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Remove);
}

VARIANT GPExcelOLERange::GetShrinkToFit()
{
	VARIANT result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetShrinkToFit(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xd1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void GPExcelOLERange::Sort(const VARIANT& Key1, long Order1, const VARIANT& Key2, const VARIANT& Type, long Order2, const VARIANT& Key3, long Order3, long Header, const VARIANT& OrderCustom, const VARIANT& MatchCase, long Orientation, long SortMethod,
		const VARIANT& IgnoreControlCharacters, const VARIANT& IgnoreDiacritics, const VARIANT& IgnoreKashida)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_I4 VTS_VARIANT VTS_VARIANT VTS_I4 VTS_VARIANT VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x370, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Key1, Order1, &Key2, &Type, Order2, &Key3, Order3, Header, &OrderCustom, &MatchCase, Orientation, SortMethod, &IgnoreControlCharacters, &IgnoreDiacritics, &IgnoreKashida);
}

void GPExcelOLERange::SortSpecial(long SortMethod, const VARIANT& Key1, long Order1, const VARIANT& Type, const VARIANT& Key2, long Order2, const VARIANT& Key3, long Order3, long Header, const VARIANT& OrderCustom, const VARIANT& MatchCase, long Orientation)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_I4 VTS_VARIANT VTS_VARIANT VTS_I4 VTS_VARIANT VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT VTS_I4;
	InvokeHelper(0x371, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SortMethod, &Key1, Order1, &Type, &Key2, Order2, &Key3, Order3, Header, &OrderCustom, &MatchCase, Orientation);
}

LPDISPATCH GPExcelOLERange::GetSoundNote()
{
	LPDISPATCH result;
	InvokeHelper(0x394, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLERange::SpecialCells(long Type, const VARIANT& Value)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x19a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Type, &Value);
	return result;
}

VARIANT GPExcelOLERange::GetStyle()
{
	VARIANT result;
	InvokeHelper(0x104, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetStyle(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x104, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void GPExcelOLERange::SubscribeTo(LPCTSTR Edition, long Format)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x1e1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Edition, Format);
}

void GPExcelOLERange::Subtotal(long GroupBy, long Function, const VARIANT& TotalList, const VARIANT& Replace, const VARIANT& PageBreaks, long SummaryBelowData)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_I4;
	InvokeHelper(0x372, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 GroupBy, Function, &TotalList, &Replace, &PageBreaks, SummaryBelowData);
}

VARIANT GPExcelOLERange::GetSummary()
{
	VARIANT result;
	InvokeHelper(0x111, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::Table(const VARIANT& RowInput, const VARIANT& ColumnInput)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1f1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &RowInput, &ColumnInput);
}

VARIANT GPExcelOLERange::GetText()
{
	VARIANT result;
	InvokeHelper(0x8a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::TextToColumns(const VARIANT& Destination, long DataType, long TextQualifier, const VARIANT& ConsecutiveDelimiter, const VARIANT& Tab, const VARIANT& Semicolon, const VARIANT& Comma, const VARIANT& Space, const VARIANT& Other,
		const VARIANT& OtherChar, const VARIANT& FieldInfo)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x410, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Destination, DataType, TextQualifier, &ConsecutiveDelimiter, &Tab, &Semicolon, &Comma, &Space, &Other, &OtherChar, &FieldInfo);
}

VARIANT GPExcelOLERange::GetTop()
{
	VARIANT result;
	InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::Ungroup()
{
	InvokeHelper(0xf4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

VARIANT GPExcelOLERange::GetUseStandardHeight()
{
	VARIANT result;
	InvokeHelper(0x112, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetUseStandardHeight(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x112, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPExcelOLERange::GetUseStandardWidth()
{
	VARIANT result;
	InvokeHelper(0x113, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetUseStandardWidth(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x113, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

LPDISPATCH GPExcelOLERange::GetValidation()
{
	LPDISPATCH result;
	InvokeHelper(0x56b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT GPExcelOLERange::GetValue()
{
	VARIANT result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPExcelOLERange::GetValue2()
{
	VARIANT result;
	InvokeHelper(0x56c, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetValue2(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x56c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPExcelOLERange::GetVerticalAlignment()
{
	VARIANT result;
	InvokeHelper(0x89, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetVerticalAlignment(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x89, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT GPExcelOLERange::GetWidth()
{
	VARIANT result;
	InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLERange::GetWorksheet()
{
	LPDISPATCH result;
	InvokeHelper(0x15c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT GPExcelOLERange::GetWrapText()
{
	VARIANT result;
	InvokeHelper(0x114, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetWrapText(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x114, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

LPDISPATCH GPExcelOLERange::AddComment(const VARIANT& Text)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x56d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Text);
	return result;
}

LPDISPATCH GPExcelOLERange::GetComment()
{
	LPDISPATCH result;
	InvokeHelper(0x38e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::ClearComments()
{
	InvokeHelper(0x56e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH GPExcelOLERange::GetPhonetic()
{
	LPDISPATCH result;
	InvokeHelper(0x56f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH GPExcelOLERange::GetFormatConditions()
{
	LPDISPATCH result;
	InvokeHelper(0x570, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long GPExcelOLERange::GetReadingOrder()
{
	long result;
	InvokeHelper(0x3cf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void GPExcelOLERange::SetReadingOrder(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3cf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH GPExcelOLERange::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x571, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

	// добавленные функции
int GPExcelOLERange::DoMethod(const char* iMethod,char* oStr,BOOL flgRet)
{
	char met[200];
	strncpy(met,iMethod,195);met[195]=0;
	const char *pos=strchr(iMethod,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc;
	char *fn[138]={"GetCreator","Activate","GetAddIndent","SetAddIndent","GetAddress",
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
		"Borders","Font"};

	if (*met>='0' && *met<='9') nfunc=atoi(met);
	else
		for(nfunc=0;nfunc<138 && _stricmp(met,fn[nfunc])!=0;nfunc++);

	int retint=-123456;
	int atoipos=atoi(pos);

	try
	{
		switch(nfunc)
		{
		case 0:	/*GetCreator*/
				{
					long val=GetCreator();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 1:	/*Activate*/
				Activate();
				break;
		case 2:	/*GetAddIndent*/
				{
					COleVariant val=GetAddIndent();
					CString str;
					if (flgRet)
					{
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 3:	/*SetAddIndent*/
				{
					BOOL val1=atoipos;
					VARIANT val;
					val.boolVal=(short)val1;
					val.vt=VT_BOOL;
					SetAddIndent(val);
				}
				break;
		case 4:	/*GetAddress*/
				{
					CString val=GetAddressEx(pos);
					if (flgRet)
					{
						oStr=new char[(int)strlen(val)+1];
						strcpy(oStr,val);
					}
				}
				break;
		case 5:	/*GetAddressLocal*/
				{
					CString val=GetAddressLocalEx(pos);
					if (flgRet)
					{
						oStr=new char[(int)strlen(val)+1];
						strcpy(oStr,val);
					}
				}
				break;
		case 6:	/*AdvancedFilter*/
				AdvancedFilterEx(pos);
				break;
		case 7:	/*ApplyNames*/
				ApplyNamesEx(pos);
				break;
		case 8:	/*ApplyOutlineStyles*/
				ApplyOutlineStyles();
				break;
		case 9:	/*AutoComplete*/
				{
					CString val=AutoComplete(pos);
					if (flgRet)
					{
						oStr=new char[(int)strlen(val)+1];
						strcpy(oStr,val);
					}
				}
				break;
		case 10:	/*AutoFilter*/
				AutoFilterEx(pos);
				break;
		case 11:	/*AutoFit*/
				AutoFit();
				break;
		case 12:	/*AutoFormat*/
				AutoFormatEx(pos);
				break;
		case 13:	/*AutoOutline*/
				AutoOutline();
				break;
		case 14:	/*BorderAround*/
				BorderAroundEx(pos);
				break;
		case 15:	/*Calculate*/
				Calculate();
				break;
		case 16:	/*Clear*/
				Clear();
				break;
		case 17:	/*ClearContents*/
				ClearContents();
				break;
		case 18:	/*ClearFormats*/
				ClearFormats();
				break;
		case 19:	/*ClearNotes*/
				ClearNotes();
				break;
		case 20:	/*ClearOutline*/
				ClearOutline();
				break;
		case 21:	/*GetColumn*/
				{
					long val=GetColumn();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 22:	/*GetColumnWidth*/
				{
					COleVariant val=GetColumnWidth();
					if (flgRet)
					{
						CString str;
						if (val.vt!=VT_NULL)
							ConvVariantToString(val,str,",");
						else
							str="0";
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 23:	/*SetColumnWidth*/
				{
					COleVariant val(double(1));
					double val1=atof(pos);
					val=val1;
					SetColumnWidth(val);
				}
				break;
		case 24:	/*Consolidate*/
				ConsolidateEx(pos);
				break;
		case 25:	/*Copy*/
				{
					COleVariant val((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					Copy(val);
				}
				break;
		case 26:	/*CopyPicture*/
				{
					long valAppearance=0;
					long valFormat=0;
					int i1=0;
					char buff1[256];
					if (*pos!=0)
					{
						while ((i1<255) && (*pos!=0) && (*pos!=','))
						{
							buff1[i1]=*pos;
							pos++;
							i1++;
						}
						buff1[i1]=0;
						valAppearance=atoi(buff1);
						if (*pos!=0)
						{
							pos++;
							i1=0;
							while ((i1<255) && (*pos!=0) && (*pos!=','))
							{
								buff1[i1]=*pos;
								pos++;
								i1++;
							}
							buff1[i1]=0;
							valFormat=atoi(buff1);
							CopyPicture(valAppearance,valFormat);
						}
					}
				}
				break;
		case 27:	/*GetCount*/
				{
					long val=GetCount();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 28:	/*CreateNames*/
				CreateNamesEx(pos);
				break;
		case 29:	/*CreatePublisher*/
				CreatePublisherEx(pos);
				break;
		case 30:	/*Cut*/
				{
					COleVariant val((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					Cut(val);
				}
				break;
		case 31:	/*DataSeries*/
				DataSeriesEx(pos);
				break;
		case 32:	/*Delete*/
				{
					COleVariant val(long(0));
					val=long(atoipos);
					Delete(val);
				}
				break;
		case 33:	/*DialogBox*/ //only for macro sheet
				{
					COleVariant	val=DialogBox_();
					CString str;
					ConvVariantToString(val,str,",");
					if (flgRet)
					{
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 34:	/*EditionOptions*/
				EditionOptionsEx(pos);
				break;
		case 35:	/*FillDown*/
				FillDown();
				break;
		case 36:	/*FillLeft*/
				FillLeft();
				break;
		case 37:	/*FillRight*/
				FillRight();
				break;
		case 38:	/*FillUp*/
				FillUp();
				break;
		case 39:	/*GetFormula*/
				{
					COleVariant val=GetFormula();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 40:	/*SetFormula*/
				{
					COleVariant val(pos);
					SetFormula(val);
				}
				break;
		case 41:	/*GetFormulaArray*/
				{
					COleVariant val=GetFormulaArray();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 42:	/*SetFormulaArray*/
				{
					COleVariant val(pos);
					SetFormulaArray(val);
				}
				break;
		case 43:	/*GetFormulaLabel*/
				{
					long val=GetFormulaLabel();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 44:	/*SetFormulaLabel*/
				{
					long val=atoipos;
					SetFormulaLabel(val);
				}
				break;
		case 45:	/*GetFormulaHidden*/
				{
					COleVariant val=GetFormulaHidden();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 46:	/*SetFormulaHidden*/
				{
					COleVariant val(short(0));
					val=short(atoipos);
					SetFormulaHidden(val);
				}
				break;
		case 47:	/*GetFormulaLocal*/
				{
					COleVariant val=GetFormulaLocal();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 48:	/*SetFormulaLocal*/
				{
					COleVariant val(pos);
					SetFormulaLocal(val);
				}
				break;
		case 49:	/*GetFormulaR1C1*/
				{
					COleVariant val=GetFormulaR1C1();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 50:	/*SetFormulaR1C1*/
				{
					COleVariant val(pos);
					SetFormulaR1C1(val);
				}
				break;
		case 51:	/*GetFormulaR1C1Local*/
				{
					COleVariant val=GetFormulaR1C1Local();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 52:	/*SetFormulaR1C1Local*/
				{
					COleVariant val(pos);
					SetFormulaR1C1Local(val);
				}
				break;
		case 53:	/*FunctionWizard*/
				FunctionWizard();
				break;
		case 54:	/*Group*/
				GroupEx(pos);
				break;
		case 55:	/*GetHasArray*/
				{
					COleVariant val=GetHasArray();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 56:	/*GetHasFormula*/
				{
					COleVariant val=GetHasFormula();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 57:	/*GetHeight*/
				{
					COleVariant val=GetHeight();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 58:	/*GetHidden*/
				{
					COleVariant val=GetHidden();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 59:	/*SetHidden*/
				{
					COleVariant val(pos);
					SetHidden(val);
				}
				break;
		case 60:	/*GetHorizontalAlignment*/
				{
					COleVariant val=GetHorizontalAlignment();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 61:	/*SetHorizontalAlignment*/
				{
					COleVariant val(pos);
					SetHorizontalAlignment(val);
				}
				break;
		case 62:	/*GetIndentLevel*/
				{
					COleVariant val=GetIndentLevel();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 63:	/*SetIndentLevel*/
				{
					COleVariant val((long)atoipos);
					SetIndentLevel(val);
				}
				break;
		case 64:	/*InsertIndent*/
				{
					long val=atoipos;
					InsertIndent(val);
				}
				break;
		case 65:	/*Insert*/
				{
					if (*pos!=0)
						Insert(COleVariant(long(atoipos)));
					else
						Insert(COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR));
				}
				break;
		case 66:	/*GetItem*/
				{
					//COleVariant val=GetItem(COleVariant(rowIndex),COleVariant(colIndex)); //return dispatch!!!
					if (flgRet)
					{
					}
				}
				break;
		case 67:	/*SetItem*/
				{
					//SetItem(COleVariant(rowIndex),COleVariant(colIndex),); //set dispatch!!!
				}
				break;
		case 68:	/*InsertIndent*/
				Justify();
				break;
		case 69:	/*GetLeft*/
				{
					COleVariant val=GetLeft();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 70:	/*GetListHeaderRows*/
				{
					long val=GetListHeaderRows();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 71:	/*ListNames*/
				ListNames();
				break;
		case 72:	/*GetLocationInTable*/
				{
					long val=GetLocationInTable();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 73:	/*GetLocked*/
				{
					COleVariant val=GetLocked();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 74:	/*SetLocked*/
				{
					COleVariant val((short)atoipos);
					SetLocked(val);
				}
				break;
		case 75:	/*Merge*/
				{
					COleVariant val((short)atoipos);
					Merge(val);
				}
				break;
		case 76:	/*UnMerge*/
				UnMerge();
				break;
		case 77:	/*GetMergeCells*/
				{
					COleVariant val=GetMergeCells();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 78:	/*SetMergeCells*/
				SetMergeCells(COleVariant(short(atoipos)));
				break;
		case 79:	/*GetName*/
				{
					COleVariant val=GetName();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
		case 80:	/*SetName*/
				SetName(COleVariant(pos));
				break;
		case 81:	/*NavigateArrow*/
				NavigateArrowEx(pos);
				break;
		case 82:	/*NoteText*/
				{
					CString str=NoteTextEx(pos);
					if (flgRet)
					{
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 83:	/*GetNumberFormat*/
				{
					COleVariant val=GetNumberFormat();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 84:	/*SetNumberFormat*/
				SetNumberFormat(COleVariant(pos));
				break;
		case 85:	/*GetNumberFormatLocal*/
				{
					COleVariant val=GetNumberFormatLocal();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 86:	/*SetNumberFormatLocal*/
				SetNumberFormatLocal(COleVariant(pos));
				break;
		case 87:	/*GetOrientation*/
				{
					COleVariant val=GetOrientation();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 88:	/*SetOrientation*/
				SetOrientation(COleVariant(long(atoipos)));
				break;
		case 89:	/*GetOutlineLevel*/
				{
					COleVariant val=GetOutlineLevel();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 90:	/*SetOutlineLevel*/
				SetOutlineLevel(COleVariant(long(atoipos)));
				break;
		case 91:	/*GetPageBreak*/
				{
					long val=GetPageBreak();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 92:	/*SetPageBreak*/
				SetPageBreak((long(atoipos)));
				break;
		case 93:	/*Parse*/
				Parse(COleVariant(pos),COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR));
				break;
		case 94:	/*PasteSpecial*/
				PasteSpecialEx(pos);
				break;
		case 95:	/*GetPrefixCharacter*/
				{
					COleVariant val=GetPrefixCharacter();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 96:	/*PrintOut*/
				PrintOutEx(pos);
				break;
		case 97:	/*PrintPreview*/
				PrintPreview(COleVariant(short(atoipos)));
				break;
		case 98:	/*RemoveSubtotal*/
				RemoveSubtotal();
				break;
		case 99:	/*Replace*/
				{
					BOOL val=ReplaceEx(pos);
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 100:	/*GetRow*/
				{
					long val=GetRow();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 101:	/*GetRowHeight*/
				{
					COleVariant val=GetRowHeight();
					if (flgRet)
					{
						CString str;
						if (val.vt!=VT_NULL)
							ConvVariantToString(val,str,",");
						else
							str="0";
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 102:	/*SetRowHeight*/
				{
					COleVariant val(double(1));
					double val1=atof(pos);
					val=val1;
					SetRowHeight(val);
				}
				break;
		case 103:	/*Run*/
				{
					COleVariant val=RunEx(pos);
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 104:	/*Select*/
				Select();
				break;
		case 105: /*Show*/
				Show();
				break;
		case 106:	/*ShowDependents*/
				{
					COleVariant val((long)atoipos);
					ShowDependents(val);
				}
				break;
		case 107:	/*GetShowDetail*/
				{
					COleVariant val=GetShowDetail();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 108:	/*SetShowDetail*/
				SetShowDetail(COleVariant(short(atoipos)));
				break;
		case 109:	/*ShowErrors*/
				ShowErrors();
				break;
		case 110:	/*ShowPrecedents*/
				ShowPrecedents(COleVariant(short(atoipos)));
				break;
		case 111:	/*GetShrinkToFit*/
				{
					COleVariant val=GetShrinkToFit();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 112:	/*SetShrinkToFit*/
				SetShrinkToFit(COleVariant(short(atoipos)));
				break;
		case 113:	/*Sort*/
				SortEx(pos);
				break;
		case 114:	/*SortSpecial*/
				SortSpecialEx(pos);
				break;
		case 115:	/*Subtotal*/
				SubtotalEx(pos);
				break;
		case 116:	/*GetSummary*/
				{
					COleVariant val=GetSummary();
					if (flgRet)
					{
						CString str;
						ConvVariantToString(val,str,",");
						oStr=new char[(int)strlen(str)+1];
						strcpy(oStr,str);
					}
				}
				break;
		case 117:	/*GetText*/
				{
					COleVariant val=GetText();
					if (flgRet)
					{
						if (val.vt!=VT_NULL)
						{
							CString str;
							ConvVariantToString(val,str,",");
							oStr=new char[(int)strlen(str)+1];
							strcpy(oStr,str);
						}
						else
							oStr[0]=0;
					}
				}
				break;
		case 118:	/*GetTop*/
				{
					COleVariant val=GetTop();
					if (flgRet)
					{
						if (val.vt!=VT_NULL)
						{
							CString str;
							ConvVariantToString(val,str,",");
							oStr=new char[(int)strlen(str)+1];
							strcpy(oStr,str);
						}
						else
							oStr[0]=0;
					}
				}
				break;
		case 119:	/*Ungroup*/
				Ungroup();
				break;
		case 120:	/*GetUseStandardHeight */
				{
					COleVariant val=GetUseStandardHeight();
					if (flgRet)
					{
						if (val.vt!=VT_NULL)
						{
							CString str;
							ConvVariantToString(val,str,",");
							oStr=new char[(int)strlen(str)+1];
							strcpy(oStr,str);
						}
						else
							oStr[0]=0;
					}
				}
				break;
		case 121:	/*SetUseStandardHeight */
				SetUseStandardHeight(COleVariant(short(atoipos)));
				break;
		case 122:	/*GetUseStandardWidth */
				{
					COleVariant val=GetUseStandardWidth();
					if (flgRet)
					{
						if (val.vt!=VT_NULL)
						{
							CString str;
							ConvVariantToString(val,str,",");
							oStr=new char[(int)strlen(str)+1];
							strcpy(oStr,str);
						}
						else
							oStr[0]=0;
					}
				}
				break;
		case 123:	/*SetUseStandardWidth */
				SetUseStandardWidth(COleVariant(short(atoipos)));
				break;
		case 124:	/*GetValue*/
				{
					COleVariant val=GetValue();
					if (flgRet)
					{
						if (val.vt!=VT_NULL)
						{
							CString str;
							ConvVariantToString(val,str,",");
							oStr=new char[(int)strlen(str)+1];
							strcpy(oStr,str);
						}
						else
							oStr[0]=0;
					}
				}
				break;
		case 125:	/*SetValue*/
				SetValue(COleVariant(pos));
				break;
		case 126:	/*GetValue2*/
				{
					COleVariant val=GetValue2();
					if (flgRet)
					{
						if (val.vt!=VT_NULL)
						{
							CString str;
							ConvVariantToString(val,str,",");
							oStr=new char[(int)strlen(str)+1];
							strcpy(oStr,str);
						}
						else
							oStr[0]=0;
					}
				}
				break;
		case 127:	/*SetValue2*/
				SetValue2(COleVariant(pos));
				break;
		case 128:	/*GetVerticalAlignment*/
				{
					COleVariant val=GetVerticalAlignment();
					if (flgRet)
					{
						if (val.vt!=VT_NULL)
						{
							CString str;
							ConvVariantToString(val,str,",");
							oStr=new char[(int)strlen(str)+1];
							strcpy(oStr,str);
						}
						else
							oStr[0]=0;
					}
				}
				break;
		case 129:	/*SetVerticalAlignment*/
				SetVerticalAlignment(COleVariant(long(atoipos)));
				break;
		case 130:	/*GetWidth*/
				{
					COleVariant val=GetWidth();
					if (flgRet)
					{
						if (val.vt!=VT_NULL)
						{
							CString str;
							ConvVariantToString(val,str,",");
							oStr=new char[(int)strlen(str)+1];
							strcpy(oStr,str);
						}
						else
							oStr[0]=0;
					}
				}
				break;
		case 131:	/*GetWrapText*/
				{
					COleVariant val=GetWrapText();
					if (flgRet)
					{
						if (val.vt!=VT_NULL)
						{
							CString str;
							ConvVariantToString(val,str,",");
							oStr=new char[(int)strlen(str)+1];
							strcpy(oStr,str);
						}
						else
							oStr[0]=0;
					}
				}
				break;
		case 132:	/*SetWrapText*/
				SetWrapText(COleVariant(short(atoipos)));
				break;
		case 133:	/*ClearComments*/
				ClearComments();
				break;
		case 134:	/*GetReadingOrder*/
				{
					long val=GetReadingOrder();
					if (flgRet)
						sprintf(oStr,"%d",val);
				}
				break;
		case 135:	/*SetReadingOrder*/
				SetReadingOrder(long(atoipos));
				break;
		case 136:	/*Borders*/
				BordersEx(pos);
				break;
		case 137:	/*Font*/
				FontEx(pos);
				break;
		default:
			GPC.m_ErrReport.GPWriteWarnLog2("GPExcelRange", "Unknown Method",iMethod);
			if (flgRet)		 sprintf(oStr,ErrObjSub,met);
			nfunc=0xFFFFFFFFL;
			break;
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
		GPC.m_ErrReport.GPWriteErrorLog("GPExcelOLERange", "DoMethod",iMethod);
		delete[] str;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
//	delete[] met;
	return nfunc;

}

CString GPExcelOLERange::GetAddressEx(const char* iStr)
{
	CString ret;
	const char* pos=iStr;
	char buff[256];
	int i;
	int iparam=0;
	int paramcounter=5;
	COleVariant val[5];

	while((iparam<paramcounter))
	{
		val[iparam]=COleVariant(short(TRUE));
		iparam++;
	}
	iparam=0;
	while((iparam<paramcounter) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!=',') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		if (buff[0]!=0)
			switch (iparam)
			{
				case 2:	val[iparam]=COleVariant(long(atoi(buff)));
						break;
				default:
						val[iparam]=COleVariant(short(atoi(buff)));
			}
		iparam++;
	}

	val[4]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);// не для объекта range
	ret=GetAddress(val[0],val[1],val[2].intVal,val[3],val[4]);
	return ret;
}

CString GPExcelOLERange::GetAddressLocalEx(const char* iStr)
{
	CString ret;
	const char* pos=iStr;
	char buff[256];
	int i;
	int iparam=0;
	int paramcounter=5;
	COleVariant val[5];

	while((iparam<paramcounter))
	{
		val[iparam]=COleVariant(short(TRUE));
		iparam++;
	}
	iparam=0;
	while((iparam<paramcounter) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!=',') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		if (buff[0]!=0)
			switch (iparam)
			{
				case 2:	val[iparam]=COleVariant(long(atoi(buff)));
						break;
				default:
						val[iparam]=COleVariant(short(atoi(buff)));
			}
		iparam++;
	}

	val[4]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);// not for range object
	ret=GetAddressLocal(val[0],val[1],val[2].intVal,val[3],val[4]);
	return ret;
}

int GPExcelOLERange::AdvancedFilterEx(const char* iStr)
{
	int ret=-2;
	const char* pos=iStr;
	char buff[256];
	int i;
	int iparam=0;
	int paramcounter=4;
	COleVariant val[4];

	while((iparam<paramcounter))
	{
		switch (iparam)
		{
		case 0:	val[iparam]=COleVariant((long)(0));
				break;
		case 1:	val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
				break;
		case 2:	val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
				break;
		default:val[iparam]=COleVariant(short(FALSE));
		}
		iparam++;
	}
	iparam=0;
	while((iparam<paramcounter) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!=',') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		if (buff[0]!=0)
			switch (iparam)
			{
				case 0:	val[iparam]=COleVariant(long(atoi(buff)));
						break;
				case 3:
						val[iparam]=COleVariant(short(atoi(buff)));
						break;
				default:
						break;
			}
		iparam++;
	}

	AdvancedFilter(val[0].intVal,val[1],val[2],val[3]);
	return ret;
}

int GPExcelOLERange::ApplyNamesEx(const char* iStr)
{
	int ret=-2;
	const char* pos=iStr;
	char buff[256];
	int i;
	int iparam=0;
	int paramcounter=7;
	COleVariant val[7];

	while((iparam<paramcounter))
	{
		switch (iparam)
		{
		case 0:	val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
				break;
		case 1:	val[iparam]=COleVariant((long)(5));
				break;
		case 6:	val[iparam]=COleVariant(short(FALSE));
				break;
		default:val[iparam]=COleVariant(short(TRUE));
		}
		iparam++;
	}
	iparam=0;
	while((iparam<paramcounter) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!=',') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		if (buff[0]!=0)
			switch (iparam)
			{
				case 0:
						{
							CString str=buff;
							ConvertToArray(str,val[iparam],",",0);
						}
						break;
				case 5:
						val[iparam]=COleVariant(long(atoi(buff)));
						break;
				default:
						val[iparam]=COleVariant(short(atoi(buff)));
						break;
			}
		iparam++;
	}

	ApplyNames(val[0],val[1],val[2],val[3],val[4],val[5].intVal,val[6]);
	return ret;
}

int GPExcelOLERange::AutoFilterEx(const char* iStr)
{
	int ret=-2;
	return ret;
}

int GPExcelOLERange::AutoFormatEx(const char* iStr)
{
	int ret=-2;
	const char* pos=iStr;
	char buff[256];
	int i;
	int iparam=0;
	int paramcounter=7;
	COleVariant val[7];

	while((iparam<paramcounter))
	{
		switch (iparam)
		{
		case 0:	val[iparam]=COleVariant((long)(0));
				break;
		default:val[iparam]=COleVariant(short(TRUE));
				break;
		}
		iparam++;
	}
	iparam=0;
	while((iparam<paramcounter) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!=',') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		if (buff[0]!=0)
			switch (iparam)
			{
				case 0:	val[iparam].intVal=long(atoi(buff));
						break;
				default:val[iparam].boolVal=short(atoi(buff));
						break;
			}
		iparam++;
	}

	AutoFormat(val[0].intVal,val[1],val[2],val[3],val[4],val[5],val[6]);
	return ret;
}

int GPExcelOLERange::BorderAroundEx(const char* iStr)
{
	int ret=-2;
	const char* pos=iStr;
	char buff[256];
	int i;
	int iparam=0;
	int paramcounter=4;
	COleVariant val[4];

	while((iparam<paramcounter))
	{
		switch (iparam)
		{
		case 0:	val[iparam]=COleVariant(long(RGB(0,0,0)));
				break;
		default:val[iparam]=COleVariant(long(1));
				break;
		}
		iparam++;
	}
	iparam=0;
	while((iparam<paramcounter) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!=',') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		if (buff[0]!=0)
			switch (iparam)
			{
				case 4:	val[iparam].intVal=long(atoi(buff)); //color
						break;
				default:val[iparam].intVal=long(atoi(buff));
						break;
			}
		iparam++;
	}

	BorderAround(val[0],val[1].intVal,val[2].intVal,val[3]);
	return ret;
}

int GPExcelOLERange::ConsolidateEx(const char* iStr)
{
	int ret=-2;
	const char* pos=iStr;
	char buff[256];
	int i;
	int iparam=0;
	int paramcounter=5;
	COleVariant val[5];

	while((iparam<paramcounter))
	{
		switch (iparam)
		{
		case 0:	//val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
				val[iparam]=COleVariant(pos);
				break;
		case 1: val[iparam]=COleVariant(long(1));
				break;
		default:val[iparam]=COleVariant(short(FALSE));
				break;
		}
		iparam++;
	}
	iparam=0;
	while((iparam<paramcounter) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!=',') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		if (buff[0]!=0)
			switch (iparam)
			{
				case 0: val[iparam]=COleVariant(buff);
				case 1:	val[iparam].intVal=long(atoi(buff));
						break;
				default:val[iparam].boolVal=short(atoi(buff));
						break;
			}
		iparam++;
	}

	Consolidate(val[0],val[1],val[2],val[3],val[4]);
	return ret;
}

int GPExcelOLERange::CreateNamesEx(const char* iStr)
{
	int ret=-2;
	const char* pos=iStr;
	char buff[256];
	int i;
	int iparam=0;
	int paramcounter=4;
	COleVariant val[4];

	while((iparam<paramcounter))
	{
		val[iparam]=COleVariant(short(FALSE));
		iparam++;
	}
	iparam=0;
	while((iparam<paramcounter) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!=',') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		if (buff[0]!=0)
			val[iparam].iVal=short(atoi(buff));
		iparam++;
	}

	CreateNames(val[0],val[1],val[2],val[3]);
	return ret;
}

int GPExcelOLERange::CreatePublisherEx(const char* iStr)
{
	int ret=-2;
	return ret;
}

int GPExcelOLERange::DataSeriesEx(const char* iStr)
{
	int ret=-2;
	const char* pos=iStr;
	char buff[256];
	int i;
	int iparam=0;
	int paramcounter=6;
	COleVariant val[6];

	while((iparam<paramcounter) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!=',') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		if (buff[0]!=0)
			switch (iparam)
			{
				case 5:	val[iparam]=COleVariant(short(atoi(buff)));
						break;
				default:val[iparam]=COleVariant(long(atoi(buff)));
						break;
			}
		else
			switch (iparam)
			{
				case 0:	val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
						break;
				case 4:	val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
						break;
				case 5:	val[iparam]=COleVariant(short(FALSE));
						break;
				default:val[iparam]=COleVariant(long(1));
						break;
			}
		iparam++;
	}
	while(iparam<paramcounter)
	{
		switch (iparam)
			{
				case 0:	val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
						break;
				case 4:	val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
						break;
				case 5:	val[iparam]=COleVariant(short(FALSE));
						break;
				default:val[iparam]=COleVariant(long(1));
						break;
			}
		iparam++;
	}

	DataSeries(val[0],val[1].lVal,val[2].lVal,val[3],val[4],val[5]);
	return ret;
}

VARIANT GPExcelOLERange::EditionOptionsEx(const char* iStr)
{
	COleVariant ret;
	return ret;
}

int GPExcelOLERange::GroupEx(const char* iStr)
{
	int ret=-2;
	return ret;
}

int GPExcelOLERange::NavigateArrowEx(const char* iStr)
{
	int ret=-2;
	const char* pos=iStr;
	char buff[256];
	int i;
	int iparam=0;
	int paramcounter=3;
	COleVariant val[3];

	while((iparam<(paramcounter-1)) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!=',') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		switch (iparam)
			{
				case 0:	val[iparam]=COleVariant(short(atoi(buff)));
						break;
				case 1:	val[iparam]=COleVariant(long(atoi(buff)));
						break;
			}
		iparam++;
	}

	val[2]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	NavigateArrow(val[0],val[1],val[2]);
	return ret;
}

CString GPExcelOLERange::NoteTextEx(const char* iStr)
{
	CString ret;
	const char* pos;
	char buff[256];
	int i;
	int iparam=0;
	int paramcounter=3;
	COleVariant val[3];

	CString tmpCString=iStr;
	ConvertStringToString(tmpCString,ret);
	pos=ret;
	while((iparam<paramcounter) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!='\1') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		if (buff[0]!=0)
			switch (iparam)
				{
					case 0:	val[iparam]=COleVariant(buff);
							break;
					default:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
				}
		else
			switch(iparam)
				{
					case 0:	val[iparam]=COleVariant(buff);
							break;
					default:val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
							break;
				}

		iparam++;
	}
	while (iparam<paramcounter)
	{
		val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		iparam++;
	}
	ret=NoteText(val[0],val[1],val[2]);
	return ret;
}

int GPExcelOLERange::PasteSpecialEx(const char* iStr)
{
	int ret=-2;
	const char* pos=iStr;
	char buff[256];
	int i;
	int iparam=0;
	int paramcounter=4;
	COleVariant val[4];

	while((iparam<paramcounter) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!=',') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		if (buff[0]!=0)
			switch (iparam)
				{
					case 2:	val[iparam]=COleVariant(short(atoi(buff)));
							break;
					case 3:	val[iparam]=COleVariant(short(atoi(buff)));
							break;
					default:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
				}
		else
			switch(iparam)
				{
					case 2:	val[iparam]=COleVariant(short(FALSE));
							break;
					case 3:	val[iparam]=COleVariant(short(FALSE));
							break;
					default:	val[iparam]=COleVariant(long(1));
							break;
				}

		iparam++;
	}
	while (iparam<paramcounter)
	{
		switch(iparam)
		{
			case 2:	val[iparam]=COleVariant(short(FALSE));
					break;
			case 3:	val[iparam]=COleVariant(short(FALSE));
					break;
			default:	val[iparam]=COleVariant(long(1));
					break;
		}
		iparam++;
	}
	PasteSpecial(val[0].lVal,val[1].lVal,val[2],val[3]);
	return ret;
}

int GPExcelOLERange::PrintOutEx(const char* iStr)
{
	int ret=-2;
	const char* pos=iStr;
	char buff[256];
	CString str;
	int i;
	int iparam=0;
	int paramcounter=7;
	COleVariant val[7];

	CString tmpCString=iStr;
	ConvertStringToString(tmpCString,str);
	pos=str;
	while((iparam<paramcounter) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!='\1') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		if (buff[0]!=0)
			switch (iparam)
				{
					case 3:	val[iparam]=COleVariant(short(atoi(buff)));
							break;
					case 4:	val[iparam]=COleVariant(buff);
							break;
					case 5:	val[iparam]=COleVariant(short(atoi(buff)));
							break;
					case 6:	val[iparam]=COleVariant(short(atoi(buff)));
							break;
					default:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
				}
		else
			switch(iparam)
				{
					case 3:	val[iparam]=COleVariant(short(FALSE));
							break;
					case 4:	val[iparam]=COleVariant(buff);
							break;
					case 5:	val[iparam]=COleVariant(short(FALSE));
							break;
					case 6:	val[iparam]=COleVariant(buff);
							break;
					default:	val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
							break;
				}

		iparam++;
	}
	while (iparam<paramcounter)
	{
		switch(iparam)
		{
					case 3:	val[iparam]=COleVariant(short(FALSE));
							break;
					case 4:	val[iparam]=COleVariant("");
							break;
					case 5:	val[iparam]=COleVariant(short(FALSE));
							break;
					default:	val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
							break;
		}
		iparam++;
	}
	PrintOut(val[0],val[1],val[2],val[3],val[4],val[5],val[6]);
	return ret;
}

BOOL GPExcelOLERange::ReplaceEx(const char* iStr)
{
	BOOL ret=FALSE;
	const char* pos=iStr;
	char buff[256];
	CString str;
	int i;
	int iparam=0;
	int paramcounter=10;
	COleVariant val[10];

	CString tmpCString=iStr;
	ConvertStringToString(tmpCString,str);
	pos=str;
	while((iparam<paramcounter) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!='\1') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		if (buff[0]!=0)
			switch (iparam)
				{
					case 0:	val[iparam]=COleVariant(buff);
							break;
					case 1:	val[iparam]=COleVariant(buff);
							break;
					case 2:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
					case 3:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
					case 4:	val[iparam]=COleVariant(short(atoi(buff)));
							break;
					case 5:	val[iparam]=COleVariant(short(atoi(buff)));
							break;
					default:	val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
							break;
				}
		else
			switch(iparam)
				{
					case 0:	val[iparam]=COleVariant(buff);
							break;
					case 1:	val[iparam]=COleVariant(buff);
							break;
					case 2:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
					case 3:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
					case 4:	val[iparam]=COleVariant(short(atoi(buff)));
							break;
					case 5:	val[iparam]=COleVariant(short(atoi(buff)));
							break;
					default:	val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
							break;
				}

		iparam++;
	}
	while (iparam<paramcounter)
	{
		switch(iparam)
		{
					case 0:	val[iparam]=COleVariant("");
							break;
					case 1:	val[iparam]=COleVariant("");
							break;
					case 2:	val[iparam]=COleVariant(long(1));
							break;
					case 3:	val[iparam]=COleVariant(long(1));
							break;
					case 4:	val[iparam]=COleVariant(short(TRUE));
							break;
					case 5:	val[iparam]=COleVariant(short(TRUE));
							break;
					default:	val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
							break;
		}
		iparam++;
	}
	ret=Replace(val[0],val[1],val[2],val[3],val[4],val[5],val[6],val[7],val[8],val[9]);
	return ret;
}

VARIANT GPExcelOLERange::RunEx(const char* iStr)
{
	COleVariant ret;
	const char* pos=iStr;
	char buff[256];
	CString str;
	int i;
	int iparam=0;
	int paramcounter=30;
	COleVariant val[30];

	CString tmpCString=iStr;
	ConvertStringToString(tmpCString,str);
	pos=str;
	while((iparam<paramcounter) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!='\1') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		if (buff[0]!=0)
			val[iparam]=COleVariant(buff);
		else
			val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		iparam++;
	}
	while (iparam<paramcounter)
	{
		val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		iparam++;
	}
	ret=Run(val[0],val[1],val[2],val[3],val[4],val[5],val[6],val[7],val[8],val[9],
			val[10],val[11],val[12],val[13],val[14],val[15],val[16],val[17],val[18],val[19],
			val[20],val[21],val[22],val[23],val[24],val[25],val[26],val[27],val[28],val[29]);
	return ret;
}

int GPExcelOLERange::SortEx(const char* iStr)
{
	int ret=-2;
	const char* pos=iStr;
	char buff[256];
	CString str;
	int i;
	int iparam=0;
	int paramcounter=15;
	COleVariant val[15];

	CString tmpCString=iStr;
	ConvertStringToString(tmpCString,str);
	pos=str;
	while((iparam<paramcounter) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!='\1') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		if (buff[0]!=0)
			switch (iparam)
				{
					case 0:	val[iparam]=COleVariant(buff);
							break;
					case 1:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
					case 2:	val[iparam]=COleVariant(buff);
							break;
					case 3:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
					case 4:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
					case 5:	val[iparam]=COleVariant(buff);
							break;
					case 6:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
					case 7:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
					case 8:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
					case 9:	val[iparam]=COleVariant(short(atoi(buff)));
							break;
					case 10:val[iparam]=COleVariant(long(atoi(buff)));
							break;
					case 11:val[iparam]=COleVariant(long(atoi(buff)));
							break;
					default:	val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
							break;
				}
		else
			switch(iparam)
				{
					case 0:	val[iparam]=COleVariant("");
							break;
					case 1:	val[iparam]=COleVariant(long(1));
							break;
					case 10:val[iparam]=COleVariant(long(1));
							break;
					case 11:val[iparam]=COleVariant(long(1));
							break;
					default:	val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
							break;
				}

		iparam++;
	}
	while (iparam<paramcounter)
	{
		switch(iparam)
		{
					case 0:	val[iparam]=COleVariant("");
							break;
					case 1:	val[iparam]=COleVariant(long(1));
							break;
					case 10:val[iparam]=COleVariant(long(1));
							break;
					case 11:val[iparam]=COleVariant(long(1));
							break;
					default:	val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
							break;
		}
		iparam++;
	}
	Sort(val[0],val[1].lVal,val[2],val[3],val[4].lVal,val[5],val[6].lVal,val[7].lVal,
		val[8],val[9],val[10].lVal,val[11].lVal,val[12],val[13],val[14]);

	return ret;
}

int GPExcelOLERange::SortSpecialEx(const char* iStr)
{
	int ret=-2;
	const char* pos=iStr;
	char buff[256];
	CString str;
	int i;
	int iparam=0;
	int paramcounter=12;
	COleVariant val[12];

	CString tmpCString=iStr;

	ConvertStringToString(tmpCString,str);
	pos=str;
	while((iparam<paramcounter) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!='\1') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		if (buff[0]!=0)
			switch (iparam)
				{
					case 0:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
					case 1:	val[iparam]=COleVariant(buff);
							break;
					case 2:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
					case 3:	val[iparam]=COleVariant(buff);
							break;
					case 4:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
					case 5:	val[iparam]=COleVariant(buff);
							break;
					case 6:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
					case 7:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
					case 8:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
					case 9:	val[iparam]=COleVariant(short(atoi(buff)));
							break;
					case 10:val[iparam]=COleVariant(long(atoi(buff)));
							break;
					default:	val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
							break;
				}
		else
			switch(iparam)
				{
					case 0:	val[iparam]=COleVariant(long(1));
							break;
					case 1:	val[iparam]=COleVariant("");
							break;
					case 2:	val[iparam]=COleVariant(long(1));
							break;
					default:	val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
							break;
				}

		iparam++;
	}
	while (iparam<paramcounter)
	{
		switch(iparam)
		{
					case 0:	val[iparam]=COleVariant(long(1));
							break;
					case 1:	val[iparam]=COleVariant("");
							break;
					case 2:	val[iparam]=COleVariant(long(1));
							break;
					case 5:	val[iparam]=COleVariant(long(1));
							break;
					case 7:	val[iparam]=COleVariant(long(1));
							break;
					case 8:	val[iparam]=COleVariant(long(1));
							break;
					case 11:	val[iparam]=COleVariant(long(1));
							break;
					default:	val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
							break;
		}
		iparam++;
	}
	SortSpecial(val[0].lVal,val[1],val[2].lVal,val[3],val[4],val[5].lVal,val[6],val[7].lVal,
		val[8].lVal,val[9],val[10],val[11].lVal);

	return ret;
}

int GPExcelOLERange::SubtotalEx(const char* iStr)
{
	int ret=-2;
	const char* pos=iStr;
	char buff[256];
	CString str;
	int i;
	int iparam=0;
	int paramcounter=6;
	COleVariant val[6];

	CString tmpCString=iStr;
	ConvertStringToString(tmpCString,str);
	pos=str;
	while((iparam<paramcounter) && (*pos!=0))
	{
		i=0;
		while ((i<255) && (*pos!='\1') && (*pos!=0))
		{
			buff[i]=*pos;
			i++;
			pos++;
		}
		buff[i]=0;
		if (*pos!=0)
			pos++;
		if (buff[0]!=0)
			switch (iparam)
				{
					case 2:	{
								CString pstr=buff;
								ConvertToArray(pstr,val[iparam],"0x1",0);
							}
							break;
					case 3:	val[iparam]=COleVariant(short(atoi(buff)));
							break;
					case 4:	val[iparam]=COleVariant(short(atoi(buff)));
							break;
					default:	val[iparam]=COleVariant(long(atoi(buff)));
							break;
				}
		else
			switch(iparam)
				{
					case 0:	val[iparam]=COleVariant(long(1));
							break;
					case 1:	val[iparam]=COleVariant("");
							break;
					case 2:	val[iparam]=COleVariant(long(1));
							break;
					default:	val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
							break;
				}

		iparam++;
	}
	while (iparam<paramcounter)
	{
		switch(iparam)
		{
					case 0:	val[iparam]=COleVariant(long(1));
							break;
					case 1:	val[iparam]=COleVariant("");
							break;
					case 2:	val[iparam]=COleVariant(long(1));
							break;
					case 5:	val[iparam]=COleVariant(long(1));
							break;
					case 7:	val[iparam]=COleVariant(long(1));
							break;
					case 8:	val[iparam]=COleVariant(long(1));
							break;
					case 11:	val[iparam]=COleVariant(long(1));
							break;
					default:	val[iparam]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
							break;
		}
		iparam++;
	}
	Subtotal(val[0].lVal,val[1].lVal,val[2],val[3],val[4],val[5].lVal);

	return ret;
}

int GPExcelOLERange::BordersEx(const char* iStr)
{
	int ret=-3;
	COleDispatchDriver pBordersS;
	COleDispatchDriver pBorderNS;
	int i,nall;
	char *pos=(char *)iStr;
	char *argv[5];
	LPDISPATCH pDisp=NULL;
	static BYTE parms[]=VTS_VARIANT;

	// разбор параметров
	for(nall=0;nall<5 && pos!=NULL;nall++)
	{
		argv[nall]=pos;
		if ((pos=strchr(pos,','))!=NULL)
			*(pos++)=0;
	}
	for(i=nall;i<5;i++) argv[i]=NULL;

	// установка свойств границы
	pDisp=GetBorders();
	ASSERT(pDisp);
	pBordersS.AttachDispatch(pDisp);
	{// получение lpdispatch нужной границы
		long IndexOfBorder=0;
		if (argv[0]!=NULL)
			IndexOfBorder=atoi(argv[0]);
		if ((IndexOfBorder>4) && (IndexOfBorder<13))
		{
			pDisp=NULL;
			static BYTE parms2[]=VTS_I4;
			pBordersS.InvokeHelper(0xaa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDisp, parms2,
				IndexOfBorder);
			ASSERT(pDisp);
			pBorderNS.AttachDispatch(pDisp);
		}
		else
		{
			pBorderNS.AttachDispatch(pDisp);
		}
	}

	for(i=1;i<5;i++)
	{
		if (argv[i]!=NULL)
			if (argv[i][0]!=0)
			{
				COleVariant val=COleVariant(long(atoi(argv[i])));
				switch(i)
				{
					case 1: // color
							{
								pBorderNS.InvokeHelper(0x63, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
												&val);
							}
							break;
					case 2: // colorindex
							{
								pBorderNS.InvokeHelper(0x61, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
									 &val);
							}
							break;
					case 3: // linestyle
							{
								pBorderNS.InvokeHelper(0x77, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
									&val);
							}
							break;
					case 4: // weight
							{
								pBorderNS.InvokeHelper(0x78, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
									 &val);
							}
							break;
				}
			}
	}
	return ret;
}

int GPExcelOLERange::FontEx(const char* iStr)
{
	static BYTE parms[]=VTS_VARIANT;
	COleDispatchDriver FontDisp;
	LPDISPATCH pDisp=NULL;
	int i;
	char *lfpos;
	char *lfprop[14]={"BACKGROUND ","BOLD ","COLOR ","COLORINDEX ","FONTSTYLE ","ITALIC ","NAME ","OUTLINEFONT ","SHADOW ","SIZE ","STRIKETHROUGH ","SUBSCRIPT ","SUPERSCRIPT ","UNDERLINE ",};
	char *tmpbuff=new char [(int)strlen(iStr)+100];
	strcpy(tmpbuff,iStr);
	_strupr(tmpbuff);
	pDisp=GetFont();
	ASSERT(pDisp);
	FontDisp.AttachDispatch(pDisp);
	for(i=0;i<14;i++)
		if ((lfpos=strstr(tmpbuff,lfprop[i]))!=NULL)
		{
			char *possp=strchr(lfpos,' ');
			if (possp!=NULL)
			{
				while(*possp==' ') possp++;
					switch(i)
					{
					case 0: /*BACKGROUND*/
							{
								COleVariant val=COleVariant(long(atoi(possp)));
								FontDisp.InvokeHelper(0xb4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
									&val);
							}
							break;
					case 1: /*BOLD*/
							{
								COleVariant val=COleVariant(short(atoi(possp)));
								FontDisp.InvokeHelper(0x60, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
									 &val);
							}
							break;
					case 2: /*COLOR*/
							{
								COleVariant val=COleVariant(long(atoi(possp)));
								FontDisp.InvokeHelper(0x63, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
									 &val);
							}
							break;
					case 3: /*COLORINDEX*/
							{
								COleVariant val=COleVariant(long(atoi(possp)));
								FontDisp.InvokeHelper(0x61, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
									 &val);
							}
							break;
					case 4: /*FONTSTYLE*/
							{
								COleVariant val=COleVariant(possp);
								FontDisp.InvokeHelper(0xb1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
									 &val);
							}
							break;
					case 5: /*ITALIC*/
							{
								COleVariant val=COleVariant(short(atoi(possp)));
								FontDisp.InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
									 &val);
							}
							break;
					case 6: /*NAME*/
							{
								COleVariant val=COleVariant(possp);
								FontDisp.InvokeHelper(0x6e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
									 &val);
							}
							break;
					case 7: /*OUTLINEFONT*/
							{
								COleVariant val=COleVariant(short(atoi(possp)));
								FontDisp.InvokeHelper(0xdd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
									 &val);
							}
							break;
					case 8: /*SHADOW*/
							{
								COleVariant val=COleVariant(short(atoi(possp)));
								FontDisp.InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
									 &val);
							}
							break;
					case 9: /*SIZE*/
							{
								COleVariant val=COleVariant(long(atoi(possp)));
								FontDisp.InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
									 &val);
							}
							break;
					case 10:/*STRIKETHROUGH*/
							{
								COleVariant val=COleVariant(short(atoi(possp)));
								FontDisp.InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
									 &val);
							}
							break;
					case 11:/*SUBSCRIPT*/
							{
								COleVariant val=COleVariant(short(atoi(possp)));
								FontDisp.InvokeHelper(0xb3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
									 &val);
							}
							break;
					case 12:/*SUPERSCRIPT*/
							{
								COleVariant val=COleVariant(short(atoi(possp)));
								FontDisp.InvokeHelper(0xb2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
									 &val);
							}
							break;
					case 13:/*UNDERLINE*/
							{
								COleVariant val=COleVariant(long(atoi(possp)));
								FontDisp.InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
									 &val);
							}
							break;
					}

				}
		}
	delete[] tmpbuff;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Worksheets properties

/////////////////////////////////////////////////////////////////////////////
// Worksheets operations

LPDISPATCH Worksheets::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Worksheets::GetCreator()
{
	long result;
	InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Worksheets::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Worksheets::Add(const VARIANT& Before, const VARIANT& After, const VARIANT& Count, const VARIANT& Type)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xb5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Before, &After, &Count, &Type);
	return result;
}

void Worksheets::Copy(const VARIANT& Before, const VARIANT& After)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x227, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Before, &After);
}

long Worksheets::GetCount()
{
	long result;
	InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Worksheets::Delete()
{
	InvokeHelper(0x75, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Worksheets::FillAcrossSheets(LPDISPATCH Range, long Type)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x1d5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Range, Type);
}

LPDISPATCH Worksheets::GetItem(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xaa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

void Worksheets::Move(const VARIANT& Before, const VARIANT& After)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x27d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Before, &After);
}

LPUNKNOWN Worksheets::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

void Worksheets::PrintOut(const VARIANT& From, const VARIANT& To, const VARIANT& Copies, const VARIANT& Preview, const VARIANT& ActivePrinter, const VARIANT& PrintToFile, const VARIANT& Collate)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x389, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &From, &To, &Copies, &Preview, &ActivePrinter, &PrintToFile, &Collate);
}

void Worksheets::PrintPreview(const VARIANT& EnableChanges)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x119, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &EnableChanges);
}

void Worksheets::Select(const VARIANT& Replace)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xeb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Replace);
}

LPDISPATCH Worksheets::GetHPageBreaks()
{
	LPDISPATCH result;
	InvokeHelper(0x58a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Worksheets::GetVPageBreaks()
{
	LPDISPATCH result;
	InvokeHelper(0x58b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT Worksheets::GetVisible()
{
	VARIANT result;
	InvokeHelper(0x22e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void Worksheets::SetVisible(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x22e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

LPDISPATCH Worksheets::Get_Default(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}



