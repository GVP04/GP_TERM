// GPExcel.h: interface for the GPExcel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPEXCEL_H__E645EC81_B9B8_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GPEXCEL_H__E645EC81_B9B8_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// TO DO: Edit the #import paths
////////////////////#import "mso97.dll" no_namespace rename("DocumentProperties", "DocumentPropertiesXL")   
////////////////////#import "vbeext1.olb" no_namespace   
////////////////////#import "excel8.olb" rename("DialogBox", "DialogBoxXL") rename("RGB", "RBGXL") rename("DocumentProperties", "DocumentPropertiesXL") no_dual_interfaces


//#import "xl5en32.olb" rename_namespace("XLDemo") rename("DialogBox", "DialogBoxXL")

#include <stdio.h>
#include <tchar.h>

#pragma warning (disable:4192)

// If this is placed in the scope of the smart pointers, they must be
// explicitly Release(d) before CoUninitialize() is called.  If any reference
// count is non-zero, a protection fault will occur.
////////////////////using namespace Excel;


class GPExcel  
{
friend class CGP_TermDoc;
public:
	static UINT RunGPExcelMacro(char* pParam);
	BOOL OpenWorkBook(char* name,COleVariant* vararray);
	BOOL IsDelete;
	GPExcel();
	virtual ~GPExcel();
	UINT GPExcelMacro(char *pParam);

private:
	COleDispatchDriver pExcel;
};

#endif // !defined(AFX_GPEXCEL_H__E645EC81_B9B8_11D2_B27D_00600840D054__INCLUDED_)
