// GP_TermDoc.cpp : implementation of the CGP_TermDoc class
//

#include "stdafx.h"
#include "GP_Term.h"

#include "GP_TermDoc.h"
#include "CntrItem.h"
#include "GPToolTipCtrl.h"
#include "SrvrItem.h"
#include "GP_TermView.h"
#include "GP_DlgSetting.h"
#include <math.h>
#include "DlgViewSystemMethods.h"
#include "GPContextMenu.h"
#include "COMServer.h"
#include "DllServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CCOMServer m_COMServer;
extern DllServer m_DllServer;

char *BLOCK_STR="_APPEND_END_OF_STRING";
/////////////////////////////////////////////////////////////////////////////
// CGP_TermDoc

#define AMMT_GUIOBJECT			0x0000
#define AMMT_FILESYSTEM			0x0001
#define AMMT_SYSTEM				0x0002
#define AMMT_IMAGELIST			0x0003
#define AMMT_SPR				0x0004
#define AMMT_SEPVIEW			0x0005
#define AMMT_COM				0x0006
#define AMMT_DLL				0x0007
#define AMMT_DAODATABASE		0x0008
#define AMMT_DAOQUERYDEF		0x0009
#define AMMT_DAORECORDSET		0x0010
#define AMMT_DAOTABLEDEF		0x0011
#define AMMT_DAOWORKSPACE		0x0012
#define AMMT_DATABASE			0x0013
#define AMMT_RECORDSET			0x0014
#define AMMT_CONTEXTMENU		0x0015
#define AMMT_CURSOR				0x0016
#define AMMT_DLGFINDREPLACE		0x0017
#define AMMT_IOFILE				0x0018
#define AMMT_EXCEL				0x0019
#define AMMT_EXCELAPPLICATION	0x0020
#define AMMT_EXCELWORKSHEET		0x0021
#define AMMT_EXCELWORKBOOK		0x0022
#define AMMT_EXCELRANGE			0x0023
#define AMMT_REGION				0x0024
#define AMMT_LISTMAKER			0x0025



char m_D3OlePrefix[]={0xFA,0xFA,0x39,0xFE,0xFE,0x00,};

IMPLEMENT_DYNCREATE(CGP_TermDoc, COleServerDoc)

BEGIN_MESSAGE_MAP(CGP_TermDoc, COleServerDoc)
	//{{AFX_MSG_MAP(CGP_TermDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(IDM_DLGPICKDATA, OnDlgpickdata)
	ON_UPDATE_COMMAND_UI(IDM_DLGPICKDATA, OnUpdateDlgpickdata)
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
//	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, COleServerDoc::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, COleServerDoc::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, COleServerDoc::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, COleServerDoc::OnEditConvert)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, COleServerDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, COleServerDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, COleServerDoc::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

BEGIN_OLECMD_MAP(CGP_TermDoc, COleServerDoc)
	ON_OLECMD_PAGESETUP()
	ON_OLECMD_PRINT()
END_OLECMD_MAP()


BEGIN_DISPATCH_MAP(CGP_TermDoc, COleServerDoc)
	//{{AFX_DISPATCH_MAP(CGP_TermDoc)
	DISP_PROPERTY_NOTIFY(CGP_TermDoc, "WaitTimeTCL", m_waitTimeTCL, OnWaitTimeTCLChanged, VT_I4)
	DISP_PROPERTY_NOTIFY(CGP_TermDoc, "WaitTimeSUB", m_waitTimeSUB, OnWaitTimeSUBChanged, VT_I4)
	DISP_PROPERTY_NOTIFY(CGP_TermDoc, "WaitTimeFRead", m_waitTimeFRead, OnWaitTimeFReadChanged, VT_I4)
	DISP_PROPERTY_NOTIFY(CGP_TermDoc, "WaitTimeSystem", m_waitTimeSystem, OnWaitTimeSystemChanged, VT_I4)
	DISP_PROPERTY_NOTIFY(CGP_TermDoc, "WaitTimeMM", m_waitTimeMM, OnWaitTimeMMChanged, VT_I4)
	DISP_PROPERTY_NOTIFY(CGP_TermDoc, "WaitTimeInput", m_waitTimeInput, OnWaitTimeInputChanged, VT_I4)
	DISP_PROPERTY_NOTIFY(CGP_TermDoc, "WaitTimeFWrite", m_waitTimeFWrite, OnWaitTimeFWriteChanged, VT_I4)
	DISP_PROPERTY_NOTIFY(CGP_TermDoc, "WaitTimeFOther", m_waitTimeFOther, OnWaitTimeFOtherChanged, VT_I4)
	DISP_PROPERTY_NOTIFY(CGP_TermDoc, "WaitCountTCL", m_waitCountTCL, OnWaitCountTCLChanged, VT_I4)
	DISP_PROPERTY_NOTIFY(CGP_TermDoc, "WaitCountSystem", m_waitCountSystem, OnWaitCountSystemChanged, VT_I4)
	DISP_PROPERTY_NOTIFY(CGP_TermDoc, "WaitCountSUB", m_waitCountSUB, OnWaitCountSUBChanged, VT_I4)
	DISP_PROPERTY_NOTIFY(CGP_TermDoc, "WaitCountMM", m_waitCountMM, OnWaitCountMMChanged, VT_I4)
	DISP_PROPERTY_NOTIFY(CGP_TermDoc, "WaitCountInput", m_waitCountInput, OnWaitCountInputChanged, VT_I4)
	DISP_PROPERTY_NOTIFY(CGP_TermDoc, "WaitCountFWrite", m_waitCountFWrite, OnWaitCountFWriteChanged, VT_I4)
	DISP_PROPERTY_NOTIFY(CGP_TermDoc, "WaitCountFRead", m_waitCountFRead, OnWaitCountFReadChanged, VT_I4)
	DISP_PROPERTY_NOTIFY(CGP_TermDoc, "WaitCountFOther", m_waitCountFOther, OnWaitCountFOtherChanged, VT_I4)
	DISP_PROPERTY_EX(CGP_TermDoc, "HWND", GetHWND, SetNotSupported, VT_HANDLE)
	DISP_PROPERTY_EX(CGP_TermDoc, "HWNDview", GetHWNDview, SetNotSupported, VT_HANDLE)
	DISP_PROPERTY_EX(CGP_TermDoc, "DelimArray1", GetDelimArray1, SetNotSupported, VT_VARIANT)
	DISP_PROPERTY_EX(CGP_TermDoc, "DelimArray2", GetDelimArray2, SetNotSupported, VT_VARIANT)
	DISP_PROPERTY_EX(CGP_TermDoc, "DelimArray3", GetDelimArray3, SetNotSupported, VT_VARIANT)
	DISP_PROPERTY_EX(CGP_TermDoc, "DelimArray4", GetDelimArray4, SetNotSupported, VT_VARIANT)
	DISP_PROPERTY_EX(CGP_TermDoc, "InputEnable", GetInputEnable, SetInputEnable, VT_I4)
	DISP_FUNCTION(CGP_TermDoc, "SendLine", GPOLESendLine, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "Close", GPOLEClose, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CGP_TermDoc, "Connect", GPOLEConnect, VT_I4, VTS_NONE)
	DISP_FUNCTION(CGP_TermDoc, "IsConnected", GPOLEIsConnected, VT_I4, VTS_NONE)
	DISP_FUNCTION(CGP_TermDoc, "ExecTCL", GPOLEExecTCL, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "GetTCLResult", GPOLEGetTCLResult, VT_I4, VTS_PVARIANT VTS_I4)
	DISP_FUNCTION(CGP_TermDoc, "ResetTCLWait", GPOLEResetTCLWait, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CGP_TermDoc, "ResetSUBWait", GPOLEResetSUBWait, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CGP_TermDoc, "ExecTCLCap", GPOLEExecTCLCap, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "SendChar", GPOLESendChar, VT_I4, VTS_I2)
	DISP_FUNCTION(CGP_TermDoc, "SetECHO", GPOLESetECHO, VT_EMPTY, VTS_I2)
	DISP_FUNCTION(CGP_TermDoc, "GetInput", GPOLEGetInput, VT_I4, VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "SetOutputVisibility", GPOLESetOutputVisibility, VT_EMPTY, VTS_I2)
	DISP_FUNCTION(CGP_TermDoc, "GetSubResult", GPOLEGetSubResult, VT_I4, VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ExecSUB", GPOLEExecSUB, VT_EMPTY, VTS_BSTR VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "TermShow", GPOLETermShow, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(CGP_TermDoc, "OpenPICKFile", GPOLEOpenPICKFile, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ClosePICKFile", GPOLEClosePICKFile, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(CGP_TermDoc, "ReadFromPICK", GPOLEReadFromPICK, VT_I4, VTS_I4 VTS_BSTR VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "WriteToPICK", GPOLEWriteToPICK, VT_I4, VTS_I4 VTS_BSTR VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "GetActiveList", GPOLEGetActiveList, VT_I4, VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "GetList", GPOLEGetList, VT_I4, VTS_BSTR VTS_BSTR VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "SaveList", GPOLESaveList, VT_I4, VTS_BSTR VTS_BSTR VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ReadFromPICKEx", GPOLEReadFromPICKEx, VT_I4, VTS_I4 VTS_VARIANT VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "DeleteFromPICKFile", GPOLEDeleteFromPICKFile, VT_I4, VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "StringToArray", GPOLEStringToArray, VT_I4, VTS_BSTR VTS_PVARIANT VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "CountOccur", GPOLECountOccur, VT_I4, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "IndexSubString", GPOLEIndexSubString, VT_I4, VTS_BSTR VTS_BSTR VTS_I4)
	DISP_FUNCTION(CGP_TermDoc, "ItemExist", GPOLEItemExist, VT_I4, VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "GetListEx", GPOLEGetListEx, VT_EMPTY, VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "EndMessageMap", GPOLEEndMessageMap, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CGP_TermDoc, "IsMessageMapOn", GPOLEIsMessageMapOn, VT_I4, VTS_NONE)
	DISP_FUNCTION(CGP_TermDoc, "WriteVToPICK", GPOLEWriteVToPICK, VT_I4, VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "WriteVToPICKEx", GPOLEWriteVToPICKEx, VT_I4, VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ArrayToString", GPOLEArrayToString, VT_I4, VTS_VARIANT VTS_PBSTR VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "WriteToPICKEx", GPOLEWriteToPICKEx, VT_I4, VTS_I4 VTS_VARIANT VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ReadVFromPICK", GPOLEReadVFromPICK, VT_I4, VTS_I4 VTS_BSTR VTS_I4 VTS_PBSTR)
	DISP_FUNCTION(CGP_TermDoc, "ReadVFromPICKEx", GPOLEReadVFromPICKEx, VT_I4, VTS_I4 VTS_VARIANT VTS_I4 VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "WriteUToPICK", GPOLEWriteUToPICK, VT_I4, VTS_I4 VTS_BSTR VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "WriteUToPICKEx", GPOLEWriteUToPICKEx, VT_I4, VTS_I4 VTS_VARIANT VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "WriteVUToPICK", GPOLEWriteVUToPICK, VT_I4, VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "WriteVUToPICKEx", GPOLEWriteVUToPICKEx, VT_I4, VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ReadUFromPICK", GPOLEReadUFromPICK, VT_I4, VTS_I4 VTS_BSTR VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ReadUFromPICKEx", GPOLEReadUFromPICKEx, VT_I4, VTS_I4 VTS_VARIANT VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ReadVUFromPICK", GPOLEReadVUFromPICK, VT_I4, VTS_I4 VTS_BSTR VTS_I4 VTS_PBSTR)
	DISP_FUNCTION(CGP_TermDoc, "ReadVUFromPICKEx", GPOLEReadVUFromPICKEx, VT_I4, VTS_I4 VTS_VARIANT VTS_I4 VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "GetTimeFromPICK", GPOLEGetTimeFromPICK, VT_DATE, VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "GetDateFromPICK", GPOLEGetDateFromPICK, VT_DATE, VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "SetTimeToPICK", GPOLESetTimeToPICK, VT_I4, VTS_DATE)
	DISP_FUNCTION(CGP_TermDoc, "SetDateToPICK", GPOLESetDateToPICK, VT_I4, VTS_DATE)
	DISP_FUNCTION(CGP_TermDoc, "ReadKFromPICKEx", GPOLEReadKFromPICKEx, VT_I4, VTS_I4 VTS_VARIANT VTS_PVARIANT VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ReadKUFromPICKEx", GPOLEReadKUFromPICKEx, VT_I4, VTS_I4 VTS_VARIANT VTS_PVARIANT VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ReadKVUFromPICKEx", GPOLEReadKVUFromPICKEx, VT_I4, VTS_I4 VTS_VARIANT VTS_I4 VTS_PVARIANT VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ReadKVFromPICKEx", GPOLEReadKVFromPICKEx, VT_I4, VTS_I4 VTS_VARIANT VTS_I4 VTS_PVARIANT VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ResetActiveList", GPOLEResetActiveList, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CGP_TermDoc, "ConvertToSubArray", GPOLEConvertToSubArray, VT_I4, VTS_PVARIANT VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "DoSystem", GPOLEDoSystem, VT_EMPTY, VTS_PVARIANT VTS_I4)
	DISP_FUNCTION(CGP_TermDoc, "ConvertToSubArrayEx", GPOLEConvertToSubArrayEx, VT_I4, VTS_PVARIANT VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "StringToArrayEx", GPOLEStringToArrayEx, VT_I4, VTS_BSTR VTS_PVARIANT VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ExecSubEx", GPOleExecSubEx, VT_EMPTY,VTS_BSTR VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ArrayToStringEx", GPOLEArrayToStringEx, VT_I4, VTS_VARIANT VTS_PBSTR VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ExecTCLEx", GPOLEExecTCLEx, VT_EMPTY, VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ExecTCLCapEx", GPOLEExecTCLCapEx, VT_EMPTY, VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "SetWindowStyle", GPOLESetWindowStyle, VT_EMPTY, VTS_HANDLE VTS_VARIANT VTS_VARIANT VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "SetWindowStyleEx", GPOLESetWindowStyleEx, VT_EMPTY, VTS_HANDLE VTS_VARIANT VTS_VARIANT VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ReleaseLockedItems", GPOLEReleaseLockedItems, VT_EMPTY, VTS_I4 VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ReleaseLockedFile", GPOLEReleaseLockedFile, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(CGP_TermDoc, "ReleaseLocks", GPOLEReleaseLocks, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CGP_TermDoc, "DumpStart", GPOLEDumpStart, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CGP_TermDoc, "DumpStop", GPOLEDumpStop, VT_I4, VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "IConv", GPOLEIConv, VT_EMPTY, VTS_BSTR VTS_BSTR VTS_PBSTR)
	DISP_FUNCTION(CGP_TermDoc, "OConv", GPOLEOConv, VT_EMPTY, VTS_BSTR VTS_BSTR VTS_PBSTR)
	DISP_FUNCTION(CGP_TermDoc, "ArrayDelElement", GPOLEArrayDelElement, VT_I4, VTS_VARIANT VTS_I4)
	DISP_FUNCTION(CGP_TermDoc, "ArrayInsElement", GPOLEArrayInsElement, VT_I4, VTS_VARIANT VTS_I4)
	DISP_FUNCTION(CGP_TermDoc, "SelectOpenPickFile", GPOLESelectOpenPickFile, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "SelectPickFile", GPOLESelectPickFile, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ReadPickFile", GPOLEReadPickFile, VT_I4, VTS_BSTR VTS_PVARIANT VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "SortArray", GPOLESortArray, VT_EMPTY, VTS_PVARIANT VTS_I4)
	DISP_FUNCTION(CGP_TermDoc, "SortArray2", GPOLESortArray2, VT_EMPTY, VTS_PVARIANT VTS_PVARIANT VTS_I4)
	DISP_FUNCTION(CGP_TermDoc, "ArrayFindExactly", GPOLEArrayFindExactly, VT_I4, VTS_VARIANT VTS_VARIANT VTS_I4)
	DISP_FUNCTION(CGP_TermDoc, "ArrayFind", GPOLEArrayFind, VT_I4, VTS_VARIANT VTS_VARIANT VTS_I4)
	DISP_FUNCTION(CGP_TermDoc, "SSelectOpenPickFile", GPOLESSelectOpenPickFile, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "SSelectPickFile", GPOLESSelectPickFile, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ReadItem", GPOLEReadItem, VT_I4, VTS_BSTR VTS_BSTR VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "RegisterInROT", RegisterInROT, VT_I4, VTS_PBSTR)
	DISP_FUNCTION(CGP_TermDoc, "RevokeFromROT", RevokeFromROT, VT_I4, VTS_NONE)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerAddList", ListMakerAddList, VT_I4, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerAppendList", ListMakerAppendList, VT_I4, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerSquiseList", ListMakerSquiseList, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerDuplicateList", ListMakerDuplicateList, VT_I4, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerUniqueList", ListMakerUniqueList, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerSortList", ListMakerSortList, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerLoadList", ListMakerLoadList, VT_I4, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerLoadPickList", ListMakerLoadPickList, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerSavePickList", ListMakerSavePickList, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerNBeginCont", ListMakerNBeginCont, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerBeginCont", ListMakerBeginCont, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerNEndCont", ListMakerNEndCont, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerEndCont", ListMakerEndCont, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerNContList", ListMakerNContList, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerContList", ListMakerContList, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerNMaskList", ListMakerNMaskList, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerMaskList", ListMakerMaskList, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerXORList", ListMakerXORList, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerORList", ListMakerORList, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerANDList", ListMakerANDList, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerNOTList", ListMakerNOTList, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerGetListInfo", ListMakerGetListInfo, VT_I4, VTS_BSTR VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerGetListsInfo", ListMakerGetListsInfo, VT_I4, VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerSaveList", ListMakerSaveList, VT_I4, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerDeleteList", ListMakerDeleteList, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerCreateList", ListMakerCreateList, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerSetListAsArray", ListMakerSetListAsArray, VT_I4, VTS_BSTR VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerGetListAsArray", ListMakerGetListAsArray, VT_I4, VTS_BSTR VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerGetList", ListMakerGetList, VT_I4, VTS_BSTR VTS_PBSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerSetList", ListMakerSetList, VT_I4, VTS_BSTR VTS_BSTR VTS_I2)
	DISP_FUNCTION(CGP_TermDoc, "SprGetInfo", OLESprGetInfo, VT_I4, VTS_BSTR VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "SprGetInfos", OLESprGetInfos, VT_I4, VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "SprCreate", OLESprCreate, VT_I4, VTS_BSTR VTS_I2)
	DISP_FUNCTION(CGP_TermDoc, "SprDelete", OLESprDelete, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "SprDoSub", OLESprDoSub, VT_I4, VTS_BSTR VTS_BSTR VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "SprDoFn", OLESprDoFn, VT_I4, VTS_BSTR VTS_BSTR VTS_VARIANT VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "SprFillObject", OLESprFillObject, VT_I4, VTS_BSTR VTS_HANDLE VTS_I4 VTS_BSTR VTS_I4)
	DISP_FUNCTION(CGP_TermDoc, "SprReplaceObject", OLESprReplaceObject, VT_I4, VTS_BSTR VTS_HANDLE VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerFillObject", ListMakerFillObject, VT_I4, VTS_BSTR VTS_HANDLE VTS_I4 VTS_I4)
	DISP_FUNCTION(CGP_TermDoc, "SprFillByDisp", OLESprFillByDisp, VT_I4, VTS_BSTR VTS_DISPATCH VTS_BSTR VTS_I4)
	DISP_FUNCTION(CGP_TermDoc, "SprFillByArray", OLESprFillByArray, VT_I4, VTS_BSTR VTS_VARIANT VTS_I4 VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "SprReplaceObjectEx", OLESprReplaceObjectEx, VT_I4, VTS_HANDLE VTS_I4 VTS_I4 VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "SprReplaceByDisp", OLESprReplaceByDisp, VT_I4, VTS_DISPATCH VTS_I4 VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "SprGetItem", OLESprGetItem, VT_I4, VTS_BSTR VTS_I4 VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "SprInsertItem", OLESprInsertItem, VT_I4, VTS_BSTR VTS_I4 VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "GetMPVars", OLEGetMPVars, VT_I4, VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "Pause", OLEPause, VT_I4, VTS_I4)
	DISP_FUNCTION(CGP_TermDoc, "GetCRC16", OLEGetCRC16, VT_I4, VTS_VARIANT VTS_I4)
	DISP_FUNCTION(CGP_TermDoc, "SprGetValues", OLESprGetValues, VT_I4, VTS_BSTR VTS_I4 VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "SetNextDlgParent", OLESetNextDlgParent, VT_EMPTY, VTS_HANDLE)
	DISP_FUNCTION(CGP_TermDoc, "SprLoadFromPick", OLESprLoadFromPick, VT_I4, VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "SprSetItem", OLESprSetItem, VT_I4, VTS_BSTR VTS_I4 VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "NamedDataSet", OLENamedDataSet, VT_I4, VTS_BSTR VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "NamedDataGet", OLENamedDataGet, VT_I4, VTS_BSTR VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "NamedDataDelete", OLENamedDataDelete, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "NamedDataReset", OLENamedDataReset, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CGP_TermDoc, "SprGetValuesEx", OLESprGetValuesEx, VT_I4, VTS_BSTR VTS_VARIANT VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "DeletePickItem", GPOLEDeletePickItem, VT_EMPTY, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ReadVCFromPICKEx", GPOLEReadVCFromPICKEx, VT_I4, VTS_I4 VTS_VARIANT VTS_VARIANT VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ReadVCUFromPICKEx", GPOLEReadVCUFromPICKEx, VT_I4, VTS_I4 VTS_VARIANT VTS_VARIANT VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ReadKVCFromPICKEx", GPOLEReadKVCFromPICKEx, VT_I4, VTS_I4 VTS_VARIANT VTS_VARIANT VTS_PVARIANT VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ReadKVCUFromPICKEx", GPOLEReadKVCUFromPICKEx, VT_I4, VTS_I4 VTS_VARIANT VTS_VARIANT VTS_PVARIANT VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ReadKADFromPICKEx", GPOLEReadKADFromPICKEx, VT_I4, VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_PVARIANT VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ReadKADUFromPICKEx", GPOLEReadKADUFromPICKEx, VT_I4, VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_PVARIANT VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ExecListTab", GPOLEExecListTab, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "GetListTabResult", GPOLEGetListTabResult, VT_I4, VTS_PVARIANT VTS_BSTR VTS_I4)
	DISP_FUNCTION(CGP_TermDoc, "SprFindItem", OLESprFindItem, VT_I4, VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "SprFindNextItem", OLESprFindNextItem, VT_I4, VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_PVARIANT)
	DISP_PROPERTY_NOTIFY(CGP_TermDoc, "VariantArrayType", m_VariantArrayType, OnVariantArrayTypeChanged, VT_I4)
	DISP_FUNCTION(CGP_TermDoc, "ConvertToSubArrayNet", GPOLEConvertToSubArrayNet, VT_I4, VTS_VARIANT VTS_PVARIANT VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ExecSUBNet", GPOLEExecSUBNet, VT_EMPTY, VTS_BSTR VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "SaveListNet", GPOLESaveListNet, VT_I4, VTS_BSTR VTS_BSTR VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ListMakerSetListAsArrayNet", ListMakerSetListAsArrayNet, VT_I4, VTS_BSTR VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "ConnectEx", GPOConnectCmd, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ParseCommandLine", GPOParseCommandLine, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "ConvertToSubArrayExNet", GPOLEConvertToSubArrayExNet, VT_I4, VTS_VARIANT VTS_PVARIANT VTS_VARIANT)
	DISP_FUNCTION(CGP_TermDoc, "SortArrayNet", GPOLESortArrayNet, VT_EMPTY, VTS_VARIANT VTS_PVARIANT VTS_I4)
	DISP_FUNCTION(CGP_TermDoc, "SortArray2Net", GPOLESortArray2Net, VT_EMPTY, VTS_VARIANT VTS_PVARIANT VTS_VARIANT VTS_PVARIANT VTS_I4)
	DISP_FUNCTION(CGP_TermDoc, "IsScriptOn", GPOIsScriptOn, VT_I4, VTS_NONE)
	DISP_FUNCTION(CGP_TermDoc, "ExecuteScript", GPOExecuteScript, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CGP_TermDoc, "AbortScript", GPOAbortScript, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CGP_TermDoc, "SMMCmd", GPOLESMMCmd, VT_I4, VTS_BSTR VTS_I4 VTS_PVARIANT)
	DISP_FUNCTION(CGP_TermDoc, "GetInputString", GPOLEGetInputString, VT_I4, VTS_PBSTR VTS_I4)
	DISP_FUNCTION(CGP_TermDoc, "GetInputBytes", GPOLEGetInputBytes, VT_I4, VTS_PVARIANT VTS_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IGP_Term to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the
//  dispinterface in the .ODL file.

// {1509E7A8-DD4C-11D3-970D-0080AD863699}
static const IID IID_IGP_Term =
{ 0x1509e7a8, 0xdd4c, 0x11d3, { 0x97, 0xd, 0x0, 0x80, 0xad, 0x86, 0x36, 0x99 } };

BEGIN_INTERFACE_MAP(CGP_TermDoc, COleServerDoc)
	INTERFACE_PART(CGP_TermDoc, IID_IGP_Term, Dispatch)
END_INTERFACE_MAP() 

/////////////////////////////////////////////////////////////////////////////
// CGP_TermDoc construction/destruction

CGP_TermDoc::CGP_TermDoc()
{
	GPCOPYHWND=NULL;
	DlgMPVars=NULL;
	DlgDebug=NULL;
	ReadColor127();
	m_VariantArrayType=0;

	int IdReg=0;
	while (IdReg<MAX_REGISTERROT)
	{
		m_dwReg[IdReg]=0xFFFFFFFF;
		m_dwRegStr[IdReg]="";
		IdReg++;
	}

	// Use OLE compound files
	EnableCompoundFile();
//////////////////////
	EnableConnections();

/////////////////////
	CurPortNum=0;
	m_LockPICKItem=0;
	GPC.m_Document=this;
	ShowLicDlg=TRUE;
	m_ActiveScr=0;


	m_CDlgDialogEditor=NULL;

	MainScreen=0;
	ScrPrn=NULL;
//	m_visibleInExecTCL=FALSE;
	aGPScreen=new GPScreen * [MAX_SCREEN+1];
	ZeroMemory(aGPScreen,sizeof(GPScreen *)*(MAX_SCREEN+1));
	ZeroMemory(m_arrGPCOPYINFO,sizeof(GPCOPYINFO *)*N_GPCOPYINFO);
	ZeroMemory(m_arrGPDIRCHANGEINFO,sizeof(GPDIRCHANGEINFO *)*N_GPDIRCHANGEINFO);

	int i;
	for(i=0;i<MAX_OBJDLG;i++)
	{
		a_GPObjFrame[i]=NULL;
		a_GPObjDialog[i]=NULL;
		a_GPObjType[i]=0;
//		a_GPObjDialogHn[i]=CreateMutex(NULL,FALSE,NULL);
		a_GPObjDialogHG[i]=	GlobalAlloc(GMEM_ZEROINIT, 256);
	}


	EnableAutomation();
/////	EnableTypeLib();
	AfxOleLockApp();

	a_GPObjDialogDesktop=new GPObjDialog(0,"");
	a_GPObjDialogDesktop->AttachHWND(GetDesktopWindow());
	InitializeCriticalSection(&m_CSCOPYEditor);
}

CGP_TermDoc::~CGP_TermDoc()
{
	if (DlgMPVars!=NULL)
	{
		if (DlgMPVars->m_hWnd!=NULL)
			DlgMPVars->DestroyWindow();
		delete[] DlgMPVars;
		DlgMPVars=NULL;
	}
	if (DlgDebug!=NULL)
	{
		if (DlgDebug->m_hWnd!=NULL)
			DlgDebug->DestroyWindow();
		delete[] DlgDebug;
		DlgDebug=NULL;
	}

	int i;
	for(i=0;i<MAX_SCREEN;i++)
		if (aGPScreen[i]!=NULL) delete aGPScreen[i];

	for(i=0;i<MAX_OBJDLG;i++)
	{
		if (a_GPObjDialog[i]!=NULL)
		{
			if (a_GPObjDialog[i]->m_hWnd) a_GPObjDialog[i]->DestroyWindow();
			delete a_GPObjDialog[i];
		}
		if (a_GPObjFrame[i]!=NULL)
		{
			if (a_GPObjFrame[i]->m_hWnd) a_GPObjFrame[i]->DestroyWindow();
			delete a_GPObjFrame[i];
		}

		a_GPObjDialog[i]=NULL;
		a_GPObjFrame[i]=NULL;
		a_GPObjType[i]=0;
//		if (a_GPObjDialogHn[i]!=NULL) CloseHandle(a_GPObjDialogHn[i]);
		if (a_GPObjDialogHG[i]) GlobalFree(a_GPObjDialogHG[i]);
	}

	if (a_GPObjDialogDesktop)
	{
		if (a_GPObjDialogDesktop->DlgGPMenu!=NULL)
			a_GPObjDialogDesktop->DlgGPMenu->ReleaseHBMP();
		if (a_GPObjDialogDesktop->m_hWnd!=NULL)
			a_GPObjDialogDesktop->Detach();

		delete a_GPObjDialogDesktop;
		a_GPObjDialogDesktop=NULL;
	}

	if (ScrPrn!=NULL) delete ScrPrn;

	if (aGPScreen!=NULL) delete[] aGPScreen;

	for(i=0;i<N_GPCOPYINFO;i++)
		if (m_arrGPCOPYINFO[i])
		{
			delete m_arrGPCOPYINFO[i];
			m_arrGPCOPYINFO[i]=NULL;
		}

	for(i=0;i<N_GPDIRCHANGEINFO;i++)
		if (m_arrGPDIRCHANGEINFO[i])
		{
			delete m_arrGPDIRCHANGEINFO[i];
			m_arrGPDIRCHANGEINFO[i]=NULL;
		}

	try
	{
		if (m_CDlgDialogEditor!=NULL) delete m_CDlgDialogEditor;
	}catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GP_TermDoc", "~","GP_TermDoc");
	}
	m_CDlgDialogEditor=NULL;

	AfxOleUnlockApp();

	RevokeGPTermRegisterFromROT();
	DeleteCriticalSection(&m_CSCOPYEditor);
}

BOOL CGP_TermDoc::OnNewDocument()
{

	if (aGPScreen[0]==NULL)
	if (!COleServerDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	char str[500];
#ifdef RUS
	#ifdef BRIZ
		GPC.termCaptionInit="Графический PICK терминал 'BRIZ'";
		GPC.MsgBoxCaptionInit="Графический PICK терминал 'BRIZ'";
		GPC.ErrBoxCaptionInit="Графический PICK терминал 'BRIZ'";
	#else
		GPC.termCaptionInit="Интегрированная база данных Минфина России";
		GPC.MsgBoxCaptionInit="Интегрированная база данных Минфина России";
		GPC.ErrBoxCaptionInit="Интегрированная база данных Минфина России";
	#endif
#else
		GPC.termCaptionInit="Graphic terminal 'BRIZ'";
		GPC.MsgBoxCaptionInit="Graphic terminal 'BRIZ'";
		GPC.ErrBoxCaptionInit="Graphic terminal 'BRIZ'";
#endif

	GPC.termCaption=AfxGetApp()->GetProfileString(GPC.cs_RegTermViewSetName, "TERMTITLE",(LPCSTR)GPC.termCaptionInit);
	GPC.termCaptionInit=GPC.termCaption;
	GPC.MsgBoxCaption=AfxGetApp()->GetProfileString(GPC.cs_RegTermViewSetName, "MSGBOXTITLE",(LPCSTR)GPC.MsgBoxCaptionInit);
	GPC.MsgBoxCaptionInit=GPC.MsgBoxCaption;
	GPC.ErrBoxCaption=AfxGetApp()->GetProfileString(GPC.cs_RegTermViewSetName, "ERRBOXTITLE",(LPCSTR)GPC.ErrBoxCaptionInit);
	GPC.ErrBoxCaptionInit=GPC.ErrBoxCaption;

	const char *delimStr=" - ";
	if (GPC.termCaption=="" || *m_Comm.GetComment()==0)
		delimStr="";

	sprintf(str,"%s%s%s",(LPCSTR)m_Comm.GetComment(),delimStr,(LPCSTR)GPC.termCaption);

	SetTitle(str);
	InitIfNone();
	GPC.LoadOLESettings();
	m_waitTimeTCL=GPC.m_OLESETTINGS.m_WTCL;
	m_waitTimeSUB=GPC.m_OLESETTINGS.m_WSUB;
	m_waitTimeFRead=GPC.m_OLESETTINGS.m_WFRead;
	m_waitTimeSystem=GPC.m_OLESETTINGS.m_WSystem;
	m_waitTimeMM=GPC.m_OLESETTINGS.m_WMM;
	m_waitTimeInput=GPC.m_OLESETTINGS.m_WInput;
	m_waitTimeFWrite=GPC.m_OLESETTINGS.m_WFWrite;
	m_waitTimeFOther=GPC.m_OLESETTINGS.m_WFOther;
	m_waitCountTCL=GPC.m_OLESETTINGS.m_CTCL;
	m_waitCountSystem=GPC.m_OLESETTINGS.m_CSystem;
	m_waitCountSUB=GPC.m_OLESETTINGS.m_CSUB;
	m_waitCountMM=GPC.m_OLESETTINGS.m_CMM;
	m_waitCountInput=GPC.m_OLESETTINGS.m_CInput;
	m_waitCountFWrite=GPC.m_OLESETTINGS.m_CFWrite;
	m_waitCountFRead=GPC.m_OLESETTINGS.m_CFRead;
	m_waitCountFOther=GPC.m_OLESETTINGS.m_CFOther;


		//test
//#ifdef BRIZ
		RegisterGPTermInROT("BRIZ");
//#else
		RegisterGPTermInROT("GP_Term");
//#endif
	//end test
		GPC.m_TermRegName.Format("GPT_%X",GPC.m_View->m_hWnd);
		RegisterGPTermInROT(GPC.m_TermRegName);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGP_TermDoc Active Document server implementation

CDocObjectServer *CGP_TermDoc::GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite)
{
	return new CDocObjectServer(this, pDocSite);
}



/////////////////////////////////////////////////////////////////////////////
// CGP_TermDoc serialization

void CGP_TermDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class COleServerDoc enables serialization
	//  of the container document's COleClientItem objects.
	COleServerDoc::Serialize(ar);
}


COleServerItem* CGP_TermDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

	CGP_TermSrvrItem* pItem = new CGP_TermSrvrItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}


/////////////////////////////////////////////////////////////////////////////
// CGP_TermDoc diagnostics

#ifdef _DEBUG
void CGP_TermDoc::AssertValid() const
{
	COleServerDoc::AssertValid();
}

void CGP_TermDoc::Dump(CDumpContext& dc) const
{
	COleServerDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGP_TermDoc commands


int CGP_TermDoc::ResizeActiveScr(Size & newsize)
{
	EnterCriticalSection(&GPC.m_View->m_CSRefresh);
	try
	{
		if (aGPScreen[m_ActiveScr]!=NULL)
		{
			GPScreen *tmp=new GPScreen(aGPScreen[m_ActiveScr]->ScrId,newsize,
				(aGPScreen[m_ActiveScr]->IsScrSaveEnable()? GP_WND_SAVE:0)|
				(aGPScreen[m_ActiveScr]->IsScrViewEnable()? GP_WND_VIEW:0),0);
			tmp->SetCursorState(aGPScreen[m_ActiveScr]->GetCursorState());
			delete aGPScreen[m_ActiveScr];
			aGPScreen[m_ActiveScr]=tmp;
		}
		else
		{
			aGPScreen[m_ActiveScr]=new GPScreen(m_ActiveScr,newsize, GP_WND_SAVE|GP_WND_VIEW,0);
			aGPScreen[m_ActiveScr]->SetCursorState(1);
		}
		if (aGPScreen[m_ActiveScr])
		{
			RECT re;
			::GetClientRect(GPC.m_hViewWnd,&re);
			aGPScreen[m_ActiveScr]->SetViewSize(re.right-re.left+1,re.bottom-re.top+1);
		}
	}catch(...)
	{;}
	LeaveCriticalSection(&GPC.m_View->m_CSRefresh);
	::PostMessage(GPC.m_hViewWnd,GPM_MFUPDATESIZE,0,0);

	return aGPScreen[m_ActiveScr]?1:0;
}


UINT CGP_TermDoc::GetScreenNum(UINT iScrId)
{
	int i;
	for(i=0;i<MAX_SCREEN;i++) if (aGPScreen[i]!=NULL && aGPScreen[i]->ScrId==iScrId) break;
	return (i==MAX_SCREEN) ? 0:i;
}


void CGP_TermDoc::DeleteScreen(UINT iScrId)
{
	UINT num=GetScreenNum(iScrId);
	if (num!=0 || iScrId==0)
	{
		delete aGPScreen[num]; aGPScreen[num]=NULL;
		if (m_ActiveScr==num) m_ActiveScr=0;
		if (MainScreen==num) MainScreen=0;
	}
}

char CGP_TermDoc::SelectScreen(UINT iScrId)
{
	char ret='0';
	UINT num=GetScreenNum(iScrId);
	if (num!=0 || iScrId==0) 
	{
		m_ActiveScr=num;
		ret='1';
	}
	return ret;
}

char CGP_TermDoc::SetMainScreen(UINT iScrId)
{
	char ret='0';
	UINT num=GetScreenNum(iScrId);
	if (num!=0 || iScrId==0)
	{
		MainScreen=num;
		ret='1';
	}
	return ret;
}

UINT CGP_TermDoc::CreateScreen(Size & iScrSize, UINT ScrId/*=0*/)
{
	int i;
	if (ScrId==0)
	{
		for(i=1;i<MAX_SCREEN && aGPScreen[i]!=NULL;i++);
	}
	else i=ScrId;

	if (i<MAX_SCREEN)
	{
		aGPScreen[i]=new GPScreen(i,iScrSize,GP_WND_SAVE,0);
	} else i=0;

	return i;
}

GPUnit * CGP_TermDoc::GetScrUnit(UINT iScrId,UINT iUnitId)
{
	if (aGPScreen[GetScreenNum(iScrId)]!=NULL)
		return aGPScreen[GetScreenNum(iScrId)]->GPGetWindowById(0)->GetUnitById(iUnitId);
	else return NULL;
}

GPUnit * CGP_TermDoc::GetDlgUnit(UINT iDlgId,UINT iUnitId)
{
	if (iDlgId<MAX_OBJDLG)
	{
		if (a_GPObjType[iDlgId]==0)
		{
			if (a_GPObjDialog[iDlgId]!=NULL) return a_GPObjDialog[iDlgId]->GetUnitById(iUnitId);
		}
		else
		{
			if (a_GPObjFrame[iDlgId]!=NULL) return a_GPObjFrame[iDlgId]->GetUnitById(iUnitId);
		}
	}

	return NULL;
}

void CGP_TermDoc::DeleteScrUnit(UINT iScrDlgId, UINT iUnitId, BOOL bReport)
{
	if (iScrDlgId<MAX_SCREEN)
	{
		UINT sn=GetScreenNum(iScrDlgId);
		UINT wn=aGPScreen[sn]->GetWindowNum(0);
//		UINT un=aGPScreen[sn]->GPGetWindowByNum(wn)->GetObjectNum(iUnitId);
		aGPScreen[sn]->GPGetWindowByNum(wn)->DeleteUnit(iUnitId, bReport);
	}
}

void CGP_TermDoc::DeleteDlgUnit(UINT iScrDlgId,UINT iUnitId, BOOL bReport)
{
	if (iScrDlgId<MAX_OBJDLG && (a_GPObjDialog[iScrDlgId] || a_GPObjFrame[iScrDlgId]))
	{
		if (a_GPObjType[iScrDlgId]==0)
		{
			if (a_GPObjDialog[iScrDlgId]) a_GPObjDialog[iScrDlgId]->DeleteUnit(iUnitId, bReport);
		}
		else
		{
			if (a_GPObjFrame[iScrDlgId]) a_GPObjFrame[iScrDlgId]->DeleteUnit(iUnitId, bReport);
		}
	}
	else
		if (bReport)
		{
			CString tpms;
			tpms.Format("dialog %d  object %d",iScrDlgId, iUnitId);
			GPC.m_ErrReport.GPWriteWarnLog("Try to delete nonexistent object",tpms ,"");
		}
}

UINT CGP_TermDoc::CreateUnit(char *iProp, HWND pParentWnd)
{
	UINT iScrDlg,iId;
	char str[50];strncpy(str,iProp,49);str[49]=0;
	char *pos=strchr(str,';');
	CString tpms;
	if (pos) *pos=0;
	pos=str;
	for(iId=0;iId<3 && (pos=strchr(pos,','))!=NULL;iId++) pos++;
	if (pos!=NULL) strcpy(str,pos);

	char Ch;
	pos=strchr(iProp,';');
	if (pos++==NULL) pos="";

	m_LastScanf=sscanf(iProp,"%c,%d,%d",&Ch,&iScrDlg,&iId);

	int iUt;
	for(iUt=0;*GPUnit::aTypeUnit[iUt] && _stricmp(str,GPUnit::aTypeUnit[iUt])!=0;iUt++);

	if (*GPUnit::aTypeUnit[iUt])
	{
		if (Ch=='S')
		{
			if (iScrDlg<MAX_SCREEN && GetScreenById(iScrDlg))
				return  GetScreenById(iScrDlg)->GPGetWindowById(0)->CreateUnit(GPUnit::auTypeUnit[iUt],iId,pos,pParentWnd);
		}
		else
		if (Ch=='D')
		{
			if (iScrDlg>=0 && iScrDlg<MAX_OBJDLG)
			{
				if (a_GPObjType[iScrDlg]==0)
				{
					if (a_GPObjDialog[iScrDlg]) return a_GPObjDialog[iScrDlg]->CreateUnit(GPUnit::auTypeUnit[iUt],iId,pos,a_GPObjDialog[iScrDlg]->m_hWnd);
				}
				else
				{
					if (a_GPObjFrame[iScrDlg]) return a_GPObjFrame[iScrDlg]->CreateUnit(GPUnit::auTypeUnit[iUt],iId,pos,a_GPObjFrame[iScrDlg]->m_hWnd);
				}
			}
		}
	}
	else
	{
		tpms.Format("Scr/dlg %d  object %d",iScrDlg,iId);
		GPC.m_ErrReport.GPWriteErrorLog2("Can't create object Unknown type",tpms ,iProp);
	}

	tpms.Format("Scr/dlg %d  object %d",iScrDlg,iId);
	GPC.m_ErrReport.GPWriteErrorLog2("Can't create object",tpms ,iProp);

	return 0;
}

GPScreen * CGP_TermDoc::GetScreenByNum(UINT iNumScr)
{
	if (iNumScr>=MAX_SCREEN) iNumScr=0;
	return aGPScreen[iNumScr];
}

GPScreen * CGP_TermDoc::GetScreenById(UINT iIdScr)
{
	return GetScreenByNum(GetScreenNum(iIdScr));
}

UINT CGP_TermDoc::DoAnyMethodScript(const char *iStr,DWORD iDefObj, CString &oResult)
{
	UINT ret=0;
	CString curMethodStr;
	char delim2[]={0x2,0x0,};
	int nMeth=1;
	int i;

	const char *pos=iStr;
	while(*pos) 
		if (*(pos++)==2) nMeth++;

	for(i=0;i<nMeth;i++)
		if ((curMethodStr=ExtractField(iStr,i+1,delim2))!="")
			ret+=GPC.m_Document->DoAnyMethod(curMethodStr,iDefObj,oResult);

	return ret;
}

UINT CGP_TermDoc::DoAnyMethod(const char *iStr,DWORD iDefObj, CString &oResult)
{
	UINT ret=0;
	ARGPOSITIONS m_Positions;

	char *tmps=new char [(int)strlen(iStr)+10];
	strcpy(tmps,iStr);

	char *Dest=tmps,*ScrDlg=tmps,*ObjIdName="",*Method="",*Params="";
	ExtractScriptPart(Dest, &m_Positions);

	ScrDlg=Dest+m_Positions.End;
	if (m_Positions.ArgType!=GP_ARGTYPE_NONE && *ScrDlg) ScrDlg++;
	if (*ScrDlg) *(ScrDlg++)=0;
	ObjIdName=ScrDlg;

	while(*ObjIdName && *ObjIdName!=',' && *ObjIdName!='<' && *ObjIdName!='[') ObjIdName++;
	if (*ObjIdName=='<')
	{
		while(*ObjIdName && *ObjIdName!='>') ObjIdName++;
		while(*ObjIdName && *ObjIdName!=',') ObjIdName++;
	}
	else
	if (*ObjIdName=='[')
	{
		while(*ObjIdName && *ObjIdName!=']') ObjIdName++;
		while(*ObjIdName && *ObjIdName!=',') ObjIdName++;
	}

	if (*ObjIdName) *(ObjIdName++)=0;
	Method=ObjIdName;

	while(*Method && *Method!=',' && *Method!='<' && *Method!='[') Method++;
	if (*Method=='<')
	{
		while(*Method && *Method!='>') Method++;
		while(*Method && *Method!=',') Method++;
	}
	else
	if (*Method=='[')
	{
		while(*Method && *Method!=']') Method++;
		while(*Method && *Method!=',') Method++;
	}
	if (*Method) *(Method++)=0;
	Params=Method;

	while(*Params && *Params!=' ') Params++;

	UINT tmpDlgId=((iDefObj/0x10000)&0xFF);
	UINT tmpObjId=iDefObj&0xFFFF;
	BOOL ScrFlag=!(iDefObj&IS_DLG_UNIT);

	if (*Method)
	{
		DWORD dwMethodType=AMMT_GUIOBJECT;
		if (*ScrDlg) 
		{
			CString csScrDlg=ScrDlg;
			if (strncmp(ScrDlg,"@&",2)==0)
			{
				if (ScrDlg[2]=='_')
				{
					char *cmpName=ScrDlg+3;
					const char * accDAMTypeName[]=
					{
						"FS","SYS","IL","SPR","SV",
						"COM","DLL","DAODATABASE","DAOQUERYDEF","DAORECORDSET",
						"DAOTABLEDEF","DAOWORKSPACE","DATABASE","RECORDSET","CONTEXTMENU",
						"CURSOR","DLGFR","IOFILE","EXCEL","EXCELAPP",
						"EXCELWORKSHEET","EXCELWORKBOOK","EXCELRANGE","REGION","LISTMAKER",
						"","",
					};
					const DWORD adwDAMTypeName[]=
					{
						AMMT_FILESYSTEM,AMMT_SYSTEM,AMMT_IMAGELIST,AMMT_SPR,AMMT_SEPVIEW,
						AMMT_COM,AMMT_DLL,AMMT_DAODATABASE,AMMT_DAOQUERYDEF,AMMT_DAORECORDSET,
						AMMT_DAOTABLEDEF,AMMT_DAOWORKSPACE,AMMT_DATABASE,AMMT_RECORDSET,AMMT_CONTEXTMENU,
						AMMT_CURSOR,AMMT_DLGFINDREPLACE,AMMT_IOFILE,AMMT_EXCEL,AMMT_EXCELAPPLICATION,
						AMMT_EXCELWORKSHEET,AMMT_EXCELWORKBOOK,AMMT_EXCELRANGE,AMMT_REGION,AMMT_LISTMAKER,

						AMMT_GUIOBJECT,AMMT_GUIOBJECT,
					};
					int ii;
					for(ii=0;*accDAMTypeName[ii] && dwMethodType==AMMT_GUIOBJECT;ii++)
						if (!_stricmp(cmpName,accDAMTypeName[ii]))
						{
							dwMethodType=adwDAMTypeName[ii];
							tmpObjId=0;
						}
				}
				else
				{
					CString *varSpr= (CString *)GPC.SprVariables.FindItemExact(0,ScrDlg);
					if (varSpr)
						csScrDlg=varSpr[1];
					else
						csScrDlg="-1";
				}

				if  (csScrDlg[0]=='S' && csScrDlg[1]>='0' && csScrDlg[1]<='9') 
				{
					ScrFlag=TRUE;
					csScrDlg=csScrDlg.Mid(1,100);
				}

				if ((csScrDlg[0]>='0' && csScrDlg[0]<='9') || csScrDlg[0]>='-') tmpDlgId=atoi(csScrDlg);
				else
				{
					for(tmpDlgId=0;tmpDlgId<MAX_OBJDLG;tmpDlgId++)
						if (a_GPObjType[tmpDlgId]==0)
						{
							if (a_GPObjDialog[tmpDlgId] && a_GPObjDialog[tmpDlgId]->GPU 
								&& *(a_GPObjDialog[tmpDlgId]->GPU) 
								&& (*(a_GPObjDialog[tmpDlgId]->GPU))->m_ObjName==csScrDlg)	break;
						}
						else
							if (a_GPObjFrame[tmpDlgId]!=NULL && a_GPObjFrame[tmpDlgId]->GPU
								&& *(a_GPObjFrame[tmpDlgId]->GPU)
								&& (*(a_GPObjFrame[tmpDlgId]->GPU))->m_ObjName==csScrDlg)	break;
				}
			}
		}

		DWORD dwCurDefObj=tmpDlgId*0x10000+tmpObjId;
		if (ScrFlag) dwCurDefObj|=IS_DLG_UNIT;

		if (tmpDlgId<MAX_OBJDLG)
		{
			GPWindow *w=NULL;
			if (*ObjIdName && dwMethodType==AMMT_GUIOBJECT) 
			{
				CString csObjIdName=ObjIdName;
				if (strncmp(ObjIdName,"@&",2)==0)
				{
					CString *varSpr= (CString *)GPC.SprVariables.FindItemExact(0,ObjIdName);
					if (varSpr)
						csObjIdName=varSpr[1];
					else
						csObjIdName="-1";
				}

				tmpObjId=-1;
				if (csObjIdName[0]>='0' && csObjIdName[0]<='9')
					tmpObjId=atoi(csObjIdName);

				if (ScrFlag)
				{
					if (tmpDlgId<MAX_SCREEN)
					{
						w=aGPScreen[GetScreenNum(tmpDlgId)]->GPActiveWindow();
						for(tmpObjId=0;tmpObjId<w->WndUnit[0]->m_NGPUNIT;tmpObjId++)
							if (w->WndUnit[tmpObjId] && w->WndUnit[tmpObjId]->m_ObjName==csObjIdName) 	break;
						if (tmpObjId>=w->WndUnit[0]->m_NGPUNIT) tmpObjId=-1;
					}
				}
				else
				{
					GPUnit **rGPU=NULL;
					if (a_GPObjType[tmpDlgId]==0)
					{
						if (a_GPObjDialog[tmpDlgId]) rGPU=a_GPObjDialog[tmpDlgId]->GPU;
					}
					else
						if (a_GPObjFrame[tmpDlgId]) rGPU=a_GPObjFrame[tmpDlgId]->GPU;

					if (rGPU)
					{
						for(tmpObjId=0;tmpObjId<(*rGPU)->m_NGPUNIT;tmpObjId++)
							if (rGPU[tmpObjId] && rGPU[tmpObjId]->m_ObjName==csObjIdName) 	break;
						if (tmpObjId>=(*rGPU)->m_NGPUNIT) tmpObjId=-1;
					}
				}
			}

			static int swdStopCntr;
			if (tmpObjId!=-1 && swdStopCntr<32)
			{
				swdStopCntr++;
				try
				{
					char *tmpResult=new char [1000000];
					*tmpResult=0;
					CString csMethod=Method;
					int posDelta=0;
					DWORD noExecute=0;
					if (strncmp(Method,"@&",2)==0) noExecute=1;
					int nnnEmergencyBreak=0;
					while(posDelta>=0 && nnnEmergencyBreak++<2000)
					{
						posDelta=-1;
						const char *tmppcsMethod=(LPCSTR)csMethod;
						const char *cChartmp=tmppcsMethod;
						while((cChartmp=strstr(cChartmp,"@&"))) posDelta=(cChartmp++)-tmppcsMethod;
						if (posDelta>=0)
						{
							int posDeltatmp=ExtractScriptPart(((LPCSTR)csMethod)+posDelta, &m_Positions);
							if ((m_Positions.ArgType&GP_ARGTYPE_TYPEMASK)==GP_ARGTYPE_VARIABLE)
							{
								CString varName=csMethod.Mid(m_Positions.StartName+posDelta,m_Positions.EndName-m_Positions.StartName+1);
								char acVarnamec[10];
								strncpy(acVarnamec,varName,9);
								acVarnamec[9]=0;
								if (acVarnamec[2]=='M' && strcmp(acVarnamec,"@&M")==0 )
								{
									char tmpc[100];
									sprintf(tmpc,"%g",CalcMathString(csMethod.Mid(m_Positions.StartBrace+posDelta,m_Positions.EndBrace-m_Positions.StartBrace)));

									csMethod=
										csMethod.Left(m_Positions.StartName+posDelta)
										+tmpc
										+csMethod.Mid(m_Positions.EndBrace+1+posDelta,csMethod.GetLength());
								}
								else
								if (acVarnamec[2]=='T' && strcmp(acVarnamec,"@&T")==0 )
								{
									csMethod=
										csMethod.Left(m_Positions.StartName+posDelta)
										+csMethod.Mid(m_Positions.StartBrace+posDelta+1,m_Positions.EndBrace-m_Positions.StartBrace-1)
										+csMethod.Mid(m_Positions.EndBrace+1+posDelta,csMethod.GetLength());
								}
								else
								if (acVarnamec[2]=='S' && strcmp(acVarnamec,"@&S")==0 )
								{
									static int iCnt;
									if (iCnt<32)
									{
										iCnt++;
										try
										{
											CString *varSpr= (CString *)GPC.SprVariables.FindItemExact(0,csMethod.Mid(m_Positions.StartBrace+posDelta+1,m_Positions.EndBrace-m_Positions.StartBrace-1));
											if (varSpr) 
											{
												DoAnyMethodScript(varSpr[1],dwCurDefObj,oResult);
											}
											else
											{
												CString tpms="Script no found. Script name = "+csMethod.Mid(m_Positions.StartBrace+posDelta+1,m_Positions.EndBrace-m_Positions.StartBrace-1);
												GPC.m_ErrReport.GPWriteWarnLog("Script Error",csMethod ,"");

											}
											csMethod=
												csMethod.Left(m_Positions.StartName+posDelta)
												+csMethod.Mid(m_Positions.EndBrace+1+posDelta,csMethod.GetLength());
										}catch(...)
										{
											CString tpms="Script= "+csMethod;
											GPC.m_ErrReport.GPWriteWarnLog("Script Error",csMethod ,"");
										}
										iCnt--;
									}
									else
										{
											CString tpms="Script Stack Error. Script= "+csMethod;
											GPC.m_ErrReport.GPWriteWarnLog("Script Error",csMethod ,"");
										}
								}
								else
								{
									CString *varSpr= (CString *)GPC.SprVariables.FindItemExact(0,varName);
									CString varVal="";
									if (varSpr) varVal=varSpr[1];
									if ((m_Positions.ArgType&GP_ARGTYPE_DYNARRAY)==GP_ARGTYPE_DYNARRAY)
									{
										INDEXARR oIdxResult={-7,-7,-7,-7,};
										TranslateIndexes(csMethod.Mid(m_Positions.StartDAIndex+posDelta),&oIdxResult);
										if (oIdxResult.Index1!=-7)	varVal=ExtractField(varVal,oIdxResult.Index1,"\x7F");
										if (oIdxResult.Index2!=-7)	varVal=ExtractField(varVal,oIdxResult.Index2,"\x07");
										if (oIdxResult.Index3!=-7)	varVal=ExtractField(varVal,oIdxResult.Index3,"\x03");
									}
									if ((m_Positions.ArgType&GP_ARGTYPE_EXTRACT)==GP_ARGTYPE_EXTRACT)
									{
										INDEXARR oIdxResult={-7,-7,-7,-7,};
										TranslateIndexes(csMethod.Mid(m_Positions.StartSubstring+posDelta),&oIdxResult);
										if (oIdxResult.Index1!=-7 && oIdxResult.Index2!=-7)
											varVal=varVal.Mid(oIdxResult.Index1,oIdxResult.Index2);
										if (oIdxResult.Index3!=-7)	varVal=ExtractField(varVal,oIdxResult.Index3,"\x03");
									}
									csMethod=csMethod.Left(m_Positions.StartName+posDelta)+varVal+csMethod.Mid(m_Positions.End+posDelta+1);
								}
							}
							else posDelta+=posDeltatmp;
						}

					}

					char *realMethod=new char [csMethod.GetLength()+100];
					strcpy(realMethod,csMethod);

					if (noExecute)
					{
						strcpy(tmpResult,realMethod);
					}
					else
					{
						switch(dwMethodType)
						{
						case AMMT_GUIOBJECT:
							if (ScrFlag)
							{
								if (w) w->WndUnit[tmpObjId]->DoMethod(realMethod,tmpResult);
							}
							else
							{
								if (tmpDlgId==-1)
								{
									if (a_GPObjDialogDesktop) a_GPObjDialogDesktop->DoMethod(tmpObjId,realMethod,tmpResult);
								}
								else
								if (a_GPObjType[tmpDlgId]==0)
								{
									if (a_GPObjDialog[tmpDlgId]) a_GPObjDialog[tmpDlgId]->DoMethod(tmpObjId,realMethod,tmpResult);
								}
								else
								{
									if (a_GPObjFrame[tmpDlgId]) a_GPObjFrame[tmpDlgId]->DoMethod(tmpObjId,realMethod,tmpResult);
								}
							}
							break;
						case AMMT_FILESYSTEM:
							{
								char *tmpoStr=NULL;
								DoFileSystemMethod(realMethod,&tmpoStr);
								if (tmpoStr)
								{
									tmpResult=tmpoStr;
									delete [] tmpoStr;
								}
								else tmpResult="";
							}
							break; 
						case AMMT_SYSTEM:
							{
								char *tmpoStr=new char [TMP_STR_OUT_LEN+10];
								*tmpoStr=0;
								CDlgViewSystemMethods::DoMethod(realMethod,tmpoStr);
								tmpResult=tmpoStr;
								delete [] tmpoStr;
							}
							break; 
						case AMMT_IMAGELIST:
							if (*ObjIdName)
							{
								GPImageList *MainIl=NULL;
								int ImgLId=GPC.GetImageListId(ObjIdName);
								if (ImgLId>=0) MainIl=&(GPC.a_GPImageList[ImgLId]);
								if (MainIl==NULL)
								{
									ImgLId=GPC.GetImageListId("");
									MainIl=&(GPC.a_GPImageList[ImgLId]);
									if (MainIl!=NULL) MainIl->LoadList(ObjIdName);
								}
								if (MainIl)
								{
									char *tmpoStr=new char [TMP_STR_OUT_LEN+10];
									*tmpoStr=0;
									MainIl->DoMethod(realMethod,tmpoStr);
									tmpResult=tmpoStr;
									delete [] tmpoStr;
								}
							}
							break; 
						case AMMT_SPR:
							if (*ObjIdName)
							{
								CGPSpr *pSpr=GPC.m_SprArray.GetSpr(ObjIdName);
								if (pSpr)
								{
									char *tmpoStr=NULL;
									pSpr->DoMethod(realMethod,&tmpoStr);
									if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwNMethodsSubSpr++;
									if (tmpoStr)
									{
										tmpResult=tmpoStr;
										delete [] tmpoStr;
									}
									else tmpResult="";
								}
							}
							break; 
						case AMMT_SEPVIEW:
							{
								char *tmpoStr=NULL;
								GPC.m_View->m_DlgSeparateView.DoMethod(realMethod,&tmpoStr);
								if (tmpoStr)
								{
									tmpResult=tmpoStr;
									delete [] tmpoStr;
								}
								else tmpResult="";
							}
							break; 
						case AMMT_COM:
							if (*ObjIdName)
							{
								int COMId=m_COMServer.GetIdByName(ObjIdName);
								char *tmpoStr=NULL;
								if (COMId>=0)
								{
									const char *posParam=FindField(realMethod,2," ");
									if (!posParam) posParam="";
									m_COMServer.DoMethod(COMId,ExtractField(realMethod,1," "),posParam,&tmpoStr,TRUE);
									if (tmpoStr)
									{
										tmpResult=tmpoStr;
										delete [] tmpoStr;
									}
								}
							}
							break; 
						case AMMT_DLL:
							if (*ObjIdName)
							{
								int DllId=m_DllServer.GetIdByName(ObjIdName);
								if (DllId>=0)
								{
									char *tmpoStr=NULL;
									const char *posParam=FindField(realMethod,2," ");
									if (!posParam) posParam="";
									m_DllServer.DoMethod(DllId,ExtractField(realMethod,1," "),posParam,&tmpoStr,TRUE);
									if (tmpoStr)
									{
										tmpResult=tmpoStr;
										delete [] tmpoStr;
									}
								}
							}
							break; 
						case AMMT_DAOWORKSPACE:
						case AMMT_DAODATABASE:
						case AMMT_DAOQUERYDEF:
						case AMMT_DAORECORDSET:
						case AMMT_DAOTABLEDEF:
							if (*ObjIdName)
							{
								int IdWS=-1, IdDB=-1;
								m_LastScanf=sscanf(ObjIdName,"%d.%d",&IdWS,&IdDB);
								if (IdWS>=0 && IdWS<=N_DAOWORKSPACE_ARR && GPC.GPDAO_WS.gpws[IdWS] && GPC.GPDAO_WS.gpws[IdWS]->IsOpen())
								{
									char *tmpoStr=new char [TMP_STR_OUT_LEN+10];
									*tmpoStr=0;
									int DBNum=IdWS*N_DAODATABASE_COUNT+IdDB;
									switch(dwMethodType)
									{
									case AMMT_DAOWORKSPACE:
										GPC.GPDAO_WS.DoMethod(IdWS,realMethod,tmpoStr);
										break;
									case AMMT_DAODATABASE:
										if (IdDB>=0 && IdDB<=N_DAOWORKSPACE_ARR && GPC.GPDAO_WS.gpdb[DBNum])
											GPC.GPDAO_WS.gpdb[DBNum]->DoMethod(realMethod,tmpoStr);
										break; 
									case AMMT_DAOQUERYDEF:
										if (IdDB>=0 && IdDB<=N_DAOWORKSPACE_ARR && GPC.GPDAO_WS.gpdb[DBNum] && GPC.GPDAO_WS.gpdb[DBNum]->IsOpen())
											GPC.GPDAO_WS.gpdb[DBNum]->DoQDMethod(realMethod,tmpoStr);
										break; 
									case AMMT_DAORECORDSET:
										if (IdDB>=0 && IdDB<=N_DAOWORKSPACE_ARR && GPC.GPDAO_WS.gpdb[DBNum] && GPC.GPDAO_WS.gpdb[DBNum]->IsOpen())
											GPC.GPDAO_WS.gpdb[DBNum]->DoRSMethod(realMethod,tmpoStr);
										break; 
									case AMMT_DAOTABLEDEF:
										if (IdDB>=0 && IdDB<=N_DAOWORKSPACE_ARR && GPC.GPDAO_WS.gpdb[DBNum] && GPC.GPDAO_WS.gpdb[DBNum]->IsOpen())
											GPC.GPDAO_WS.gpdb[DBNum]->DoTDMethod(realMethod,tmpoStr);
										break; 
									}
									tmpResult=tmpoStr;
									delete [] tmpoStr;
								}
							}
							break; 
						case AMMT_DATABASE:
							if (*ObjIdName)
							{
								char *tmpoStr=new char [TMP_STR_OUT_LEN+10];
								*tmpoStr=0;
								int DBId=atoi(ObjIdName); 
								if (*realMethod && DBId>=0 && DBId<N_DATABASE_ARR && GPC.GPODBC_DB.gpdb[DBId]!=NULL)
									GPC.GPODBC_DB.gpdb[DBId]->DoMethod(realMethod,tmpoStr);
								tmpResult=tmpoStr;
								delete [] tmpoStr;
							}
							break; 
						case AMMT_RECORDSET:
							if (*ObjIdName)
							{
								int DBId=-1,RSId=-1; 
								m_LastScanf=sscanf(ObjIdName,"%d.%d",&DBId,&RSId);
								if (DBId>=0 && DBId<N_DATABASE_ARR && GPC.GPODBC_DB.gpdb[DBId]
									&& RSId>=0 && RSId<N_MAX_RECODSET && GPC.GPODBC_DB.gpdb[DBId]->GPRS[RSId]
									)
								{
									char *tmpoStr=new char [TMP_STR_OUT_LEN+10];
									*tmpoStr=0;
									GPC.GPODBC_DB.gpdb[DBId]->GPRS[RSId]->DoMethod(
										(GPC.GPODBC_DB.gpdb[DBId]->GPRS[RSId]->m_DosAnsiFlag)?realMethod:AnsiToDos(realMethod,0),tmpoStr);
									tmpResult=tmpoStr;
									delete [] tmpoStr;
								}
							}
							break; 
						case AMMT_CONTEXTMENU:
							{
								char *tmpoStr=new char [TMP_STR_OUT_LEN+10];
								*tmpoStr=0;
								GPC.m_pContextMenu->DoMethod(realMethod,tmpoStr);
								tmpResult=tmpoStr;
								delete [] tmpoStr;
							}
							break; 
						case AMMT_REGION:
							if (*ObjIdName)
							{
								GPRegion *tmpreg=GPC.RegionArr.GetRgn(ObjIdName);
								if (tmpreg)
								{
									char *tmpoStr=new char [TMP_STR_OUT_LEN+10];
									*tmpoStr=0;
									tmpreg->DoMethod(realMethod,tmpoStr,(void *)&GPC.RegionArr);
									tmpResult=tmpoStr;
									delete [] tmpoStr;
								}
							}
							break; 
						case AMMT_CURSOR:
							if (*ObjIdName)
							{
								GPCursor *tmpreg=GPC.CursorArr.GetCursor(ObjIdName);
								if (tmpreg)
								{
									char *tmpoStr=new char [TMP_STR_OUT_LEN+10];
									*tmpoStr=0;
									tmpreg->DoMethod(realMethod,tmpoStr,(void *)&GPC.CursorArr);
									tmpResult=tmpoStr;
									delete [] tmpoStr;
								}
							}
							break; 
						case AMMT_DLGFINDREPLACE:
							{
								char *tmpoStr=new char [TMP_STR_OUT_LEN+10];
								*tmpoStr=0;
								GPC.m_View->GPFRD->DoMethod(realMethod,tmpoStr);
								tmpResult=tmpoStr;
								delete [] tmpoStr;
							}
							break; 
						case AMMT_LISTMAKER:
							{
								char *tmpoStr=NULL;
								GPC.m_ListMaker.DoMethod(realMethod,&tmpoStr);
								if (tmpoStr)
								{
									tmpResult=tmpoStr;
									delete [] tmpoStr;
								}
							}
							break; 
						case AMMT_IOFILE:
							if (*ObjIdName)
							{
								GPIOFile *pIOFile=GPC.m_IOFileArray.GetIOFile(ObjIdName);
								if (pIOFile!=NULL)
								{
									char *tmpoStr=NULL;
									pIOFile->DoMethod(realMethod,&tmpoStr);
									if (tmpoStr)
									{
										tmpResult=tmpoStr;
										delete [] tmpoStr;
									}
								}
							}
							break; 
						case AMMT_EXCEL:
							{
								char *tmpoStr=new char [TMP_STR_OUT_LEN+10];
								*tmpoStr=0;
								GPC.GPXL.DoMethod(realMethod,tmpoStr,TRUE);
								tmpResult=tmpoStr;
								delete [] tmpoStr;
							}
							break; 
						case AMMT_EXCELAPPLICATION:
							if (*ObjIdName)
							{
								char *tmpoStr=new char [TMP_STR_OUT_LEN+10];
								*tmpoStr=0;
								GPC.GPXL.DoEAMethod(atoi(ObjIdName),realMethod,tmpoStr,TRUE);
								tmpResult=tmpoStr;
								delete [] tmpoStr;
							}
							break; 
						case AMMT_EXCELWORKBOOK:
							if (*ObjIdName)
							{
								int IdApp=-1, IdWorkbook=-1;
								m_LastScanf=sscanf(ObjIdName,"%d.%d",&IdApp,&IdWorkbook);

								char *tmpoStr=new char [TMP_STR_OUT_LEN+10];
								*tmpoStr=0;
								if (IdApp>=0 && (IdApp<N_EXCELAPPLICATION_ARR) && GPC.GPXL.gpApp[IdApp]
									&& IdWorkbook>=0 && IdWorkbook<N_EXCELWORKBOOK_ARR 
									&& GPC.GPXL.gpApp[IdApp]->gpWorkbooks[IdWorkbook]
									)
									GPC.GPXL.gpApp[IdApp]->gpWorkbooks[IdWorkbook]->DoMethod(realMethod,tmpoStr,TRUE);
								tmpResult=tmpoStr;
								delete [] tmpoStr;
							}
							break; 
						case AMMT_EXCELWORKSHEET:
							if (*ObjIdName)
							{
								int IdApp=-1, IdWorkbook=-1, IdWorksheet=-1;
								m_LastScanf=sscanf(ObjIdName,"%d.%d.%d",&IdApp,&IdWorkbook,&IdWorksheet);

								char *tmpoStr=new char [TMP_STR_OUT_LEN+10];
								*tmpoStr=0;
								if (IdApp>=0 && (IdApp<N_EXCELAPPLICATION_ARR) && GPC.GPXL.gpApp[IdApp]
									&& IdWorkbook>=0 && IdWorkbook<N_EXCELWORKBOOK_ARR 
									&& GPC.GPXL.gpApp[IdApp]->gpWorkbooks[IdWorkbook]
									&& IdWorkbook>=0 && IdWorkbook<N_EXCELWORKBOOK_ARR
									&& GPC.GPXL.gpApp[IdApp]->gpWorkbooks[IdWorkbook]->gpWorksheets[IdWorksheet]
									)
									GPC.GPXL.gpApp[IdApp]->gpWorkbooks[IdWorkbook]->gpWorksheets[IdWorksheet]->DoMethod(realMethod,tmpoStr,TRUE);
								tmpResult=tmpoStr;
								delete [] tmpoStr;
							}
							break; 
						case AMMT_EXCELRANGE:
							if (*ObjIdName)
							{
								char *tmpoStr=new char [TMP_STR_OUT_LEN+10];
								*tmpoStr=0;
								GPC.GPXL.DoERMethod(atoi(ObjIdName),realMethod,tmpoStr,TRUE);
								tmpResult=tmpoStr;
								delete [] tmpoStr;
							}
							break; 
						}
					}
					if (Dest && *Dest)
					{
						ExtractScriptPart(Dest, &m_Positions);
						char *delims[]={"\x7F","\x7",};
						INDEXARR oIdxResult={-7,-7,-7,-7,};
						int iSubStrPos=-1;
						int iSubStrLen=-1;
						if ((m_Positions.ArgType&GP_ARGTYPE_EXTRACT)==GP_ARGTYPE_EXTRACT)
						{
							iSubStrLen=100000;
							m_LastScanf=sscanf(Dest+m_Positions.StartSubstring+1,"%d,%d",&iSubStrPos,&iSubStrLen);
						}

						if ((m_Positions.ArgType&GP_ARGTYPE_TYPEMASK)==GP_ARGTYPE_VARIABLE)
						{
							CString varName=Dest+m_Positions.StartName;
							varName=varName.Left(m_Positions.EndName-m_Positions.StartName+1);

							CString *varSpr= (CString *)GPC.SprVariables.FindItemExact(0,varName);
							if (!varSpr)
							{
								GPC.SprVariables.InsertEmpty(0,1);
								GPC.SprVariables.SetItem(0,varName);
								GPC.SprVariables.SetSubItem(0,1,"");
								varSpr=GPC.SprVariables.GetItem(0);
							}
							if (varSpr)
							{
								if ((m_Positions.ArgType&GP_ARGTYPE_DYNARRAY)==GP_ARGTYPE_DYNARRAY)
								{
									TranslateIndexes(Dest+m_Positions.StartDAIndex,&oIdxResult);
									if (oIdxResult.Index2!=-7)
									{
										ReplaceChar(tmpResult, 0x3, 0x5);
										ReplaceChar(tmpResult, 0x7, 0x4);
										ReplaceChar(tmpResult, 0x7F, 0x3);
										SetSubField(varSpr[1], tmpResult, oIdxResult.Index1, oIdxResult.Index2, iSubStrPos, iSubStrLen, delims[0], delims[1]);
									}
									else
									if (oIdxResult.Index1!=-7)
									{
										ReplaceChar(tmpResult, 0x3, 0x4);
										ReplaceChar(tmpResult, 0x7, 0x3);
										ReplaceChar(tmpResult, 0x7F, 0x7);

										SetMVField(varSpr[1], tmpResult, oIdxResult.Index1, iSubStrPos, iSubStrLen, delims[0]);
									}
								}
								else varSpr[1]=tmpResult;
							}
						}
						else
						if ((m_Positions.ArgType&GP_ARGTYPE_DYNARRAY)==GP_ARGTYPE_DYNARRAY || (m_Positions.ArgType&GP_ARGTYPE_DECNUMBER)==GP_ARGTYPE_DECNUMBER)
						{
							oIdxResult.Index1=atoi(Dest);
							if ((m_Positions.ArgType&GP_ARGTYPE_DYNARRAY)==GP_ARGTYPE_DYNARRAY)
							{
								TranslateIndexes(Dest,&oIdxResult);
							}
							if (oIdxResult.Index2!=-7)
							{
								ReplaceChar(tmpResult, 0x3, 0x5);
								ReplaceChar(tmpResult, 0x7, 0x4);
								ReplaceChar(tmpResult, 0x7F, 0x3);
								SetSubField(oResult, tmpResult, oIdxResult.Index1, oIdxResult.Index2, iSubStrPos, iSubStrLen, delims[0], delims[1]);
							}
							else
							if (oIdxResult.Index1!=-7)
							{
								ReplaceChar(tmpResult, 0x3, 0x4);
								ReplaceChar(tmpResult, 0x7, 0x3);
								ReplaceChar(tmpResult, 0x7F, 0x7);
								SetMVField(oResult, tmpResult, oIdxResult.Index1, iSubStrPos, iSubStrLen, delims[0]);
							}

						}
					}
					delete[] realMethod;
					delete[] tmpResult;
				}catch(...)
				{
					CString tpms="Script= ";
					tpms+=iStr;
					GPC.m_ErrReport.GPWriteWarnLog("Script Error",iStr ,"");
				}
				swdStopCntr--;
			}
			else
			GPC.m_ErrReport.GPWriteWarnLog2("Objects", "Unknown Method",iStr);
		}
		else
		GPC.m_ErrReport.GPWriteWarnLog2("Objects", "Unknown Method",iStr);

		delete[] tmps;
	}
	else
	GPC.m_ErrReport.GPWriteWarnLog2("Objects", "Unknown Method",iStr);
	return ret;
}

UINT CGP_TermDoc::DoObjectMethod(const char *iStr, char *oStr, BOOL iSend)
{
	const char *pos=strchr(iStr,';');
	if (!oStr) iSend=FALSE;

	if (pos!=NULL)
	{
		pos++;
		UINT iScrDlgId,iObjId;
		char Ch='S';
		m_LastScanf=sscanf(iStr,"%c,%d,%d",&Ch,&iScrDlgId,&iObjId);

		if (Ch=='S')
		{
			if (iScrDlgId<MAX_SCREEN)
			{
				UINT sn=GetScreenNum(iScrDlgId);
				UINT wn=aGPScreen[sn]->GetWindowNum(0);
				aGPScreen[sn]->GPGetWindowByNum(wn)->DoMethod(iObjId,pos,oStr);
			}
			else
			GPC.m_ErrReport.GPWriteWarnLog2("Objects", "Unknown Method",iStr);
		}
		else
		if (iScrDlgId<MAX_OBJDLG)
		{
			if (a_GPObjType[iScrDlgId]==0)
			{
				if (a_GPObjDialog[iScrDlgId]!=NULL) a_GPObjDialog[iScrDlgId]->DoMethod(iObjId,pos,oStr);
				else
				GPC.m_ErrReport.GPWriteWarnLog2("Objects", "Unknown Method",iStr);
			}
			else
			{
				if (a_GPObjFrame[iScrDlgId]!=NULL) a_GPObjFrame[iScrDlgId]->DoMethod(iObjId,pos,oStr);
				else
				GPC.m_ErrReport.GPWriteWarnLog2("Objects", "Unknown Method",iStr);
			}
		}
		else
			if (iScrDlgId==-1)
			{
				if (a_GPObjDialogDesktop) a_GPObjDialogDesktop->DoMethod(iObjId,pos,oStr);
				else
				GPC.m_ErrReport.GPWriteWarnLog2("Objects", "Unknown Method",iStr);
			}
			else
			GPC.m_ErrReport.GPWriteWarnLog2("Objects", "Unknown Method",iStr);
	}
	else
	{
#ifdef RUS
		if (oStr) sprintf(oStr,"Ошибка задания метода №№%s",iStr);
#else
		if (oStr) sprintf(oStr,"Error execution of method №№%s",iStr);
#endif
		GPC.m_ErrReport.GPWriteWarnLog2("Objects", "Unknown Method",iStr);
	}
	if (oStr)
	{
		char *postmp=GPC.StrTmpOut;
		char *postmp2=postmp;
		while(*postmp!=0)
		{
			if (*postmp=='\r')
			{
				if (*(++postmp)=='\n') postmp++;
 				*(postmp2++)=127;
			}
			else
			if (*postmp=='\n')
			{
				if (*(++postmp)=='\r') postmp++;
				*(postmp2++)=127;
			}
			else *(postmp2++)=*(postmp++);
		}

		*postmp2=0;
		if (iSend==TRUE)
		{
				*(postmp2++)='\r';
				*postmp2=0;
			GPC.WaitFor_m_MuteProc();
				m_Comm.GPSendSafeBlock(AnsiToDos(GPC.StrTmpOut,1),(int)strlen(GPC.StrTmpOut));
			GPC.Release_m_MuteProc();
		}
	}

	return 0;
}



UINT CGP_TermDoc::DoObjectMethod(const char *iStr, BOOL iSend)
{
	UINT ret=0;
	if (iSend)
	{
		char *oStr=GPC.StrTmpOut; *oStr=0;
		ret=DoObjectMethod(iStr, oStr, iSend);
	}
	else ret=DoObjectMethod(iStr, NULL, iSend);

	return ret;
}

UINT CGP_TermDoc::DoObjectMethodEx(const char *iStr, BOOL iSend)
{
	char *postmpcc=new char [(int)strlen(iStr)+10];
	strcpy(postmpcc,iStr);

	char *pos=strchr(postmpcc+3,',');
	CString coStr="";
	if (pos++!=NULL)
	{

		char *oStr=NULL;
		BOOL IsDlg=(*iStr=='D' || *iStr=='d');
		UINT iScrDlgId,iObjId;
		char Ch='S';
		m_LastScanf=sscanf(iStr,"%c,%d,%d",&Ch,&iScrDlgId,&iObjId);

		while(pos!=NULL)
		{
			if (iSend==TRUE) {oStr=GPC.StrTmpOut;	*GPC.StrTmpOut=0;}
			else oStr=NULL;

			iObjId=atoi(pos);
			char *pos2=strchr(pos,11);
			if (pos2!=NULL) *(pos2++)=0;

			if ((pos=strchr(pos,';'))!=NULL) pos++;
			else pos="";

			if (*pos && *pos!=11)
			{
				if (IsDlg)
				{
					if (iScrDlgId<MAX_OBJDLG)
					{
						if (a_GPObjType[iScrDlgId]==0)
						{
							if (a_GPObjDialog[iScrDlgId]!=NULL) a_GPObjDialog[iScrDlgId]->DoMethod(iObjId,pos,oStr);
						}
						else
						{
							if (a_GPObjFrame[iScrDlgId]!=NULL) a_GPObjFrame[iScrDlgId]->DoMethod(iObjId,pos,oStr);
						}
					}
					else
						if (iScrDlgId==-1)
						{
							if (a_GPObjDialogDesktop) a_GPObjDialogDesktop->DoMethod(iObjId,pos,oStr);
						}
				}
				else
				{
					if (iScrDlgId<MAX_SCREEN)
					{
						UINT sn=GetScreenNum(iScrDlgId);
						UINT wn=aGPScreen[sn]->GetWindowNum(0);
						aGPScreen[sn]->GPGetWindowByNum(wn)->DoMethod(iObjId,pos,oStr);
					}
				}
			}
			if (iSend==TRUE)
			{
				char *postmp=GPC.StrTmpOut;
				char *postmp2=postmp;
				while(*postmp!=0)
				{
					if (*postmp=='\r' || *postmp=='\n')
					{
						if (*(++postmp)=='\r' || *postmp=='\n') postmp++;
						*(postmp2++)=254;
					}
					else *(postmp2++)=*(postmp++);

				}
				*(postmp2++)=11;
				*postmp2=0;
				coStr+=GPC.StrTmpOut;
			}

			pos=pos2;
		}
	}
#ifdef RUS
	else coStr.Format("Ошибка задания метода №№%s",iStr);
#else
	else coStr.Format("Error execution of method №№%s",iStr);
#endif

	if (iSend==TRUE)
	{
		GPC.WaitFor_m_MuteProc();
		AnsiToDos(coStr,coStr,1);
		m_Comm.GPSendSafeBlock(coStr,coStr.GetLength());
		m_Comm.GPSendBlock("\r",1);
		GPC.Release_m_MuteProc();
	}
	delete[] postmpcc;
	return 0;
}


Size CGP_TermDoc::GetActiveScrSize()
{
	return aGPScreen[m_ActiveScr]->GetScreenSize();
}

Size CGP_TermDoc::GetMainScrSize()
{
	return aGPScreen[MainScreen]->GetScreenSize();
}
GPScreen *CGP_TermDoc::GetActiveScreen()
{
	return aGPScreen[m_ActiveScr];
}

GPScreen *CGP_TermDoc::GetMainScreen()
{
	return aGPScreen[MainScreen];
}

void CGP_TermDoc::GPSetScrUnitProperty(UINT IdScr, UINT IdUnit, char *PropetyLine)
{
	if (IdScr<MAX_SCREEN)
	{
		UINT sn=GetScreenNum(IdScr);
		UINT wn=aGPScreen[sn]->GetWindowNum(0);
		GPUnit *un=aGPScreen[sn]->GPGetWindowByNum(wn)->GetUnitByNum(IdUnit);
		if (un!=NULL) un->RemappingProperty(PropetyLine);
	}

}

void CGP_TermDoc::GPSetDlgUnitProperty(UINT IdDlg, UINT IdUnit, char *PropetyLine)
{
	if (IdDlg<MAX_OBJDLG)
	{
		GPUnit *un=NULL;
		if (a_GPObjType[IdDlg]==0)
		{
			if (a_GPObjDialog[IdDlg]!=NULL) un=a_GPObjDialog[IdDlg]->GetUnitById(IdUnit);
		}
		else
		{
			if (a_GPObjFrame[IdDlg]!=NULL) un=a_GPObjFrame[IdDlg]->GetUnitById(IdUnit);
		}
		if (un!=NULL) un->RemappingProperty(PropetyLine);
	}

}

void CGP_TermDoc::InitIfNone()
{
	if (aGPScreen[0]==NULL)
	{
		m_ActiveScr=0;
		CWinApp *app=AfxGetApp();

		GPScreen::ScrSizeScaleFlags=app->GetProfileInt(GPC.cs_RegTermViewSetName,   "ScrSizeScaleFlags",(DWORD)GPScreen::SSM_SIZE_XY);

		GPScreen::ScrLeftBorder=(REAL)atof(app->GetProfileString(GPC.cs_RegTermViewSetName,   "ScrLeftBorder","0.3"));
		GPScreen::ScrRightBorder=(REAL)atof(app->GetProfileString(GPC.cs_RegTermViewSetName,  "ScrRightBorder","0.3"));
		GPScreen::ScrTopBorder=(REAL)atof(app->GetProfileString(GPC.cs_RegTermViewSetName,    "ScrTopBorder","0.1"));
		GPScreen::ScrBottomBorder=(REAL)atof(app->GetProfileString(GPC.cs_RegTermViewSetName, "ScrBottomBorder","0.1"));

		GPScreen::ScrLeftPageMargin=(REAL)atof(app->GetProfileString(GPC.cs_RegTermViewSetName,   "ScrLeftPageMargin","0"));
		GPScreen::ScrRightPageMargin=(REAL)atof(app->GetProfileString(GPC.cs_RegTermViewSetName,  "ScrRightPageMargin","0"));
		GPScreen::ScrTopPageMargin=(REAL)atof(app->GetProfileString(GPC.cs_RegTermViewSetName,    "ScrTopPageMargin","0"));
		GPScreen::ScrBottomPageMargin=(REAL)atof(app->GetProfileString(GPC.cs_RegTermViewSetName, "ScrBottomPageMargin","0"));

		GPScreen::ScrFontDeltaX=(REAL)atof(app->GetProfileString(GPC.cs_RegTermViewSetName, "ScrFontDeltaX","0"));
		GPScreen::ScrFontDeltaY=(REAL)atof(app->GetProfileString(GPC.cs_RegTermViewSetName, "ScrFontDeltaY","0"));
		GPScreen::ScrFontOfsetX=(REAL)atof(app->GetProfileString(GPC.cs_RegTermViewSetName, "ScrFontOfsetX","0"));
		GPScreen::ScrFontOfsetY=(REAL)atof(app->GetProfileString(GPC.cs_RegTermViewSetName, "ScrFontOfsetY","0"));

		GPScreen::ScrScaleHeightToWidth=(REAL)atof(app->GetProfileString(GPC.cs_RegTermViewSetName, "ScrScaleHeightToWidth","1.6"));

		GPScreen::ScrPrintBorders=app->GetProfileInt(GPC.cs_RegTermViewSetName, "ScrPrintBorders",1);

		GPScreen::ScrScaleFlags=app->GetProfileInt(GPC.cs_RegTermViewSetName, "ScrScaleFlags",0);

		GPScreen::ScrPrintInvert=app->GetProfileInt(GPC.cs_RegTermViewSetName, "ScrPrintInvert",0);

		aGPScreen[0]=new GPScreen(0,Size(AfxGetApp()->GetProfileInt(m_Comm.GPSectionName, "INITCOLUMNS",80),AfxGetApp()->GetProfileInt(m_Comm.GPSectionName, "INITROWS",25)), GP_WND_SAVE|GP_WND_VIEW,0);
		aGPScreen[0]->SetCursorState(1);
	}
	::PostMessage(GPC.m_hViewWnd,GPM_MFUPDATESIZE,0,0);
}

long CGP_TermDoc::GPOLESendLine(LPCTSTR iStr)
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'SendLine'","");
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	GPC.WaitFor_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	CString dStr(iStr);
	AnsiToDosMB((LPCTSTR)dStr,dStr,0);

	long ret=m_Comm.GPSendLine(dStr);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}


void CGP_TermDoc::GPOLEClose()
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	GPC.Flags|=GP_CUR_EXITFLAG;
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'Close' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'Close' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'Close'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'Close'","");

	GPC.m_ErrReport.GPWriteWarnLog("COM", "Try close terminal","");
	AfxGetApp()->GetMainWnd()->ShowWindow(SW_RESTORE);
	AfxGetApp()->GetMainWnd()->PostMessage(WM_CLOSE);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

void CGP_TermDoc::GPOLETermShow(long ShowType)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
//#define SW_HIDE             0
//#define SW_SHOWNORMAL       1
//#define SW_NORMAL           1
//#define SW_SHOWMINIMIZED    2
//#define SW_SHOWMAXIMIZED    3
//#define SW_MAXIMIZE         3
//#define SW_SHOWNOACTIVATE   4
//#define SW_SHOW             5
//#define SW_MINIMIZE         6
//#define SW_SHOWMINNOACTIVE  7
//#define SW_SHOWNA           8
//#define SW_RESTORE          9
//#define SW_SHOWDEFAULT      10
//#define SW_FORCEMINIMIZE    11
//#define SW_MAX              11

	AfxGetMainWnd()->ShowWindow(ShowType);

	switch(ShowType)
	{
	case SW_SHOWNORMAL:
	case SW_SHOWMAXIMIZED:
	case SW_SHOW:
	case SW_RESTORE:
	case SW_SHOWDEFAULT:
	case SW_MAX:
		if (GPC.m_hViewWnd!=NULL)
			CWnd::FromHandle(GPC.m_hViewWnd)->SetFocus();
		break;
	case SW_HIDE:
	case SW_SHOWMINIMIZED:
	case SW_SHOWNOACTIVATE:
	case SW_MINIMIZE:
	case SW_SHOWMINNOACTIVE:
	case SW_SHOWNA:
		break;
	default:
		GPC.m_ErrReport.GPWriteWarnLog2("COM", "TermShow","Unknown type");
		break;
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}


long CGP_TermDoc::GPOLEConnect()
{
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
	{
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'Connect' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'Connect' when executing SUB","");
	}

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();

	if (m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Connect","Already connected. Use IsConnected.");

	POSITION pos = GetFirstViewPosition();
	if (pos != NULL)
	{
      CView* pView = GetNextView(pos);
	  pView->OnInitialUpdate();
	}


	InitIfNone();
	SetModifiedFlag(FALSE);
	if (GPC.m_View)	GPC.m_View->SafeInit();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();

	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Connect","Can't connect");

	return TRUE;
}

long CGP_TermDoc::GPOLEIsConnected()
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	long ret=m_Comm.IsConnected();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

void CGP_TermDoc::GPOLEExecTCL(LPCTSTR TCLLine)
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ExecTCL'","");

	CString dStr(TCLLine);
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ExecTCL' when executing TCL",dStr);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ExecTCL' when executing SUB",dStr);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ExecTCL'",dStr);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ExecTCL'",dStr);


	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartTCL();
	GPC.m_View->m_TCLvisible=TRUE;
	GPC.ClearOUTTCL();
	GPC.ClearOUTSUB();
	m_waitCountTCL=GPC.m_OLESETTINGS.m_CTCL;

	GPC.m_WaitTCL=TRUE;
	GPC.m_WaitEndTCL=TRUE;

	GPC.WaitFor_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(m_D3OlePrefix,5);
	m_Comm.GPSendBlock("TCL\xFE",4);

	AnsiToDosMB((LPCTSTR)dStr,dStr,0);
	m_Comm.GPSendBlock((LPCTSTR)dStr,dStr.GetLength());
	m_Comm.GPSendBlock("\r",1);
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

long CGP_TermDoc::GPOLEGetTCLResult(VARIANT FAR* ResArray, long GetFlag)
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'GetTCLResult'","");

	if (GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'GetTCLResult' when executing SUB","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'GetTCLResult'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=-10;
	if (--m_waitCountTCL<=0) ret=-1;

	GPC.m_View->DoRemappingInput();

	if (GPC.m_WaitTCL==TRUE) {ret=-9;Sleep(m_waitTimeTCL);}
	else
	{
		if (GPC.m_WaitEndTCL==TRUE)
		{
			ret=-8;
			if (GetFlag!=0)
			{
				if (GPC.GetOUTTCLLen()==0) Sleep(m_waitTimeTCL);
				GPC.DosToAnsiOUTTCL();
				CString delim("\r");
				ConvertToArray(GPC.GetOUTTCL(),ResArray,delim,m_VariantArrayType);
				GPC.ClearOUTTCL();
			}
		}
		else
		{
			GPC.DosToAnsiOUTTCL();
			CString delim("\r");
			ret=ConvertToArray(GPC.GetOUTTCL(),ResArray,delim,m_VariantArrayType);
			GPC.ClearOUTTCL();
			if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndTCL();
		}
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

void CGP_TermDoc::GPOLEExecTCLCap(LPCTSTR TCLLine)
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ExecTCLCap'","");

	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ExecTCLCap' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ExecTCLCap' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ExecTCLCap'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ExecTCLCap'","");


	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartTCL();
	GPC.m_View->m_TCLvisible=FALSE;
	GPC.ClearOUTTCL();
	GPC.ClearOUTSUB();
	m_waitCountTCL=GPC.m_OLESETTINGS.m_CTCL;
	GPC.m_WaitTCL=TRUE;
	GPC.m_WaitEndTCL=TRUE;
	GPC.WaitFor_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(m_D3OlePrefix,5);
	m_Comm.GPSendBlock("TCLCAP\xFE",7);

	CString dStr(TCLLine);
	AnsiToDosMB((LPCTSTR)dStr,dStr,0);
	m_Comm.GPSendLine((LPCTSTR)dStr);
	m_Comm.GPSendBlock("\r",1);
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

void CGP_TermDoc::GPOLEResetTCLWait()
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ResetTCLWait'","");

	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteWarnLog2("COM", "Call 'ResetTCLWait' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteWarnLog2("COM", "Call 'ResetTCLWait' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ResetTCLWait'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ResetTCLWait'","");


	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	m_waitCountTCL=GPC.m_OLESETTINGS.m_CTCL;
	GPC.m_WaitTCL=FALSE;
	GPC.m_WaitEndTCL=FALSE;
	GPC.TCLinProgress=FALSE;
	GPC.ClearOUTTCL();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

void CGP_TermDoc::GPOLEResetSUBWait()
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ResetSUBWait'","");

	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ResetSUBWait' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ResetSUBWait' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ResetSUBWait'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ResetSUBWait'","");

	
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	m_waitCountSUB=GPC.m_OLESETTINGS.m_CSUB;
	GPC.m_WaitTCL=FALSE;
	GPC.m_WaitEndTCL=FALSE;
	GPC.TCLinProgress=FALSE;
	GPC.ClearOUTTCL();
	GPC.ClearOUTSUB();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

long CGP_TermDoc::GPOLESendChar(short iChar)
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'SendChar'","");
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	GPC.WaitFor_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	long ret=m_Comm.GPSendChar((char)iChar);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

void CGP_TermDoc::GPOLESetECHO(short EchoState)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	GPC.m_WaitTCL=FALSE;
	GPC.TCLinProgress=TRUE;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

long CGP_TermDoc::GPOLEGetInput(VARIANT FAR* ResArray)
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'GetInput'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=-10;
	GPC.m_View->DoRemappingInput();


	if (!GPC.TCLinProgress)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Try call 'GetInput' when input disabled","");

	if (GPC.m_WaitTCL==TRUE) {ret=-9;Sleep(m_waitTimeInput);}
	else
	{
		if (GPC.GetOUTTCLLen()==0) {ret=-8;Sleep(m_waitTimeInput);}
		GPC.DosToAnsiOUTTCL();
		CString delim("\r");
		ret=ConvertToArray(GPC.GetOUTTCL(),ResArray,delim,m_VariantArrayType);
		if (GPC.TCLOutputString.GetLength()==0) ret=0;
		GPC.TCLOutputString="";
	}

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	
	return ret;
}

long CGP_TermDoc::GPOLEGetInputString(BSTR FAR* oString, long GetFlag)
{
	long ret=-10;
	if (!m_Comm.IsConnected())		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'GetInputString'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	GPC.m_View->DoRemappingInput();


	if (!GPC.TCLinProgress)			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Try call 'GetInputString' when input disabled","");

	if (GPC.m_WaitTCL==TRUE) {ret=-9;Sleep(m_waitTimeInput);}
	else
	{
		GPC.TCLOutputString+=GPC.TCLOutputString2;
		GPC.TCLOutputString2="";
		ret= GPC.TCLOutputString.GetLength();
		if (ret>0)
		{
			if ((GetFlag&0x300)==0x100) DosToAnsiMB((LPCTSTR)GPC.TCLOutputString,GPC.TCLOutputString);
			GPC.TCLOutputString.SetSysString(oString);
			GPC.TCLOutputString="";
		}
		else  {Sleep(m_waitTimeInput);}
	}

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();

	return ret;
}


long CGP_TermDoc::GPOLEGetInputBytes(VARIANT FAR* ResArray, long GetFlag)
{
	long ret=-10;
	if (!m_Comm.IsConnected())		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'GetInputBytes'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	GPC.m_View->DoRemappingInput();


	if (!GPC.TCLinProgress)			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Try call 'GetInputBytes' when input disabled","");

	if (GPC.m_WaitTCL==TRUE) {ret=-9;Sleep(m_waitTimeInput);}
	else
	{
		GPC.TCLOutputString+=GPC.TCLOutputString2;
		GPC.TCLOutputString2="";
		ret= GPC.TCLOutputString.GetLength();
		if (ret>0)
		{
			if ((GetFlag&0x300)==0x100) DosToAnsiMB((LPCTSTR)GPC.TCLOutputString,GPC.TCLOutputString);
			
			///////////////ConvertToArray(GPC.GetOUTSUB(),RetArray,delim,m_VariantArrayType);
			
			long ix=-1;
			SAFEARRAY FAR* psa = NULL;

			USES_CONVERSION;
			SAFEARRAYBOUND tmpSAB={0};
			tmpSAB.cElements=ret+32;

			int i=0;

			if ((V_VT(ResArray)&VT_ARRAY) == VT_ARRAY )
			{
				psa = V_ARRAY(ResArray);
				SafeArrayGetLBound(psa,1,&tmpSAB.lLbound);
				SafeArrayDestroy(psa);
			}
			VariantInit(ResArray);

			try
			{
				COleSafeArray SAtmp;
				SAtmp.Create(VT_I1, 1,&tmpSAB.cElements+32);
				VariantCopy(ResArray,SAtmp);
		//		SAtmp.Destroy();
			}
			catch(...)
			{
				GPC.m_ErrReport.GPWriteErrorLog("Doc", "2296","GPOLEGetInputBytes");
			}

			psa = V_ARRAY(ResArray);
			// Check dimensions of the array.
			if (SafeArrayGetDim(psa) != 1)			AfxThrowOleDispatchException(1002,IDS_GPOLEEXEPTION1002);
			else
			{
				BYTE HUGEP *pBYTE;
				HRESULT hr;
				hr = SafeArrayAccessData(psa, (void HUGEP* FAR*)&pBYTE);
				if (FAILED(hr))		AfxThrowOleDispatchException(1001,IDS_GPOLEEXEPTION1001);
				
				strcpy_s((char *)pBYTE,ret+30,GPC.TCLOutputString);
				SafeArrayUnaccessData(psa);
			}
			GPC.TCLOutputString="";
		}
		else  {Sleep(m_waitTimeInput);}
	}

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();

	return ret;
}

void CGP_TermDoc::GPOLESetOutputVisibility(short VisType)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	GPC.m_View->m_TCLvisible=VisType;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

long CGP_TermDoc::GPOLEGetSubResult(VARIANT FAR* RetArray)
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'GetSubResult'","");

	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'GetSubResult' when executing TCL","");

	//if (GPC.GetOUTTCLLen())
	//	GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'GetSubResult'","");


	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=-10;
	GPC.m_View->DoRemappingInput();

	if (--m_waitCountSUB<=0)
	{
		ret=-1;
	}

	if (GPC.m_WaitSUB==TRUE) {ret=-9;Sleep(m_waitTimeSUB);}
	else
	if (GPC.m_WaitEndSUB==TRUE) {ret=-8;Sleep(m_waitTimeSUB);}
	else
	{
		if (GPC.GetOUTSUBLen()==0) {ret=-8;Sleep(m_waitTimeSUB);}
		GPC.DosToAnsiOUTSUB();
		CString delim("\x7F");
		ret=ConvertToArray(GPC.GetOUTSUB(),RetArray,delim,m_VariantArrayType);
		GPC.ClearOUTSUB();
//		GPC.ClearOUTTCL();
		if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndSUB();
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

void CGP_TermDoc::GPOLEExecSUBNet(LPCTSTR SubName, const VARIANT FAR& ParamArray)
{
	GPOLEExecSUB(SubName, (VARIANT FAR*)&ParamArray);
}

void CGP_TermDoc::GPOLEExecSUB(LPCTSTR SubName, VARIANT FAR* ParamArray)
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ExecSUB'","");

	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ExecSUB' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ExecSUB' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ExecSUB'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ExecSUB'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartSUB();
	CString oStr;
	CString DelimeterStr("\x7F");
	m_waitCountSUB=GPC.m_OLESETTINGS.m_CSUB;

	if (ConvertToString(ParamArray,oStr, DelimeterStr)>=0)
	{
		char *str=new char [100+strlen(SubName)];
		sprintf(str,"%sSUB%c%s",m_D3OlePrefix,0xFE,SubName);
	GPC.WaitFor_m_MuteProc();
		if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
		m_Comm.GPSendBlock(str,(int)strlen(str));
		m_Comm.GPSendBlock("\r",1);

		GPC.ClearOUTSUB();
		GPC.ClearOUTTCL();
		GPC.m_WaitSUB=TRUE;
		GPC.m_WaitEndSUB=TRUE;

		AnsiToDosMB((LPCTSTR)oStr,oStr,1);
		m_Comm.GPSendLine((LPCTSTR)oStr);
		m_Comm.GPSendBlock("\r",1);
	GPC.Release_m_MuteProc();
		delete []str;
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}


long CGP_TermDoc::GPOLEOpenPICKFile(LPCTSTR FileName)
{
	CString oStr(FileName);
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'OpenPICKFile'",oStr);

	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'OpenPICKFile' when executing TCL",oStr);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'OpenPICKFile' when executing SUB",oStr);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'OpenPICKFile'",oStr);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'OpenPICKFile'",oStr);

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	AnsiToDosMB((LPCTSTR)oStr,oStr,0);

	char str[150];
	sprintf(str,"%sPOFILE%c%s",m_D3OlePrefix,0xFE,(LPCTSTR)oStr);
	GPC.WaitFor_m_MuteProc();
	LastResult=-123456;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);

	int i;
	for(i=0;i<m_waitCountFOther;i++)
	{
		if (GPC.m_View->DoAdditionalMessageLoop()<0)
		{
			GPC.Release_m_MuteProc();
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "'OpenPICKFile' aborted","");
			return  -13;
		}
		GPC.m_View->DoRemappingInput();
		if (LastResult==-123456) Sleep(m_waitTimeFOther);
		else break;
	}
	if (i>=m_waitCountFOther)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'OpenPICKFile'",oStr);

	if (LastResult<=0)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Cant open file by 'OpenPICKFile', You have opened too many files",oStr);

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	GPC.Release_m_MuteProc();

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();

	return LastResult;
}

void CGP_TermDoc::GPOLEClosePICKFile(long FileHandler)
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ClosePICKFile'","");

	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ClosePICKFile' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ClosePICKFile' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ClosePICKFile'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ClosePICKFile'","");

	if (FileHandler<=0)
	{
		char tmps[10];
		sprintf(tmps,"%d",FileHandler);
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Bad file handler in 'ClosePICKFile'",tmps);
	}


	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	char str[150];
	sprintf(str,"%sPCFILE%c%d",m_D3OlePrefix,0xFE,FileHandler);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

long CGP_TermDoc::GPOLEReadFromPICK(long FileHandler, LPCTSTR Key, VARIANT FAR* RetArray)
{
	CString oStr(Key);
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ReadFromPICK'",Key);

	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReadFromPICK' when executing TCL",Key);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReadFromPICK' when executing SUB",Key);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ReadFromPICK'",Key);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ReadFromPICK'",Key);

	if (FileHandler<=0)
	{
		char tmps[10];
		sprintf(tmps,"%d",FileHandler);
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Bad file handler in 'ReadFromPICK'",tmps);
	}


	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNTimesServerRead++;

	AnsiToDosMB((LPCTSTR)oStr,oStr,0);
	long ret=-1;
	char str[150];
	sprintf(str,"%sPR%sFILE%c%d%c%s",m_D3OlePrefix,(m_LockPICKItem==0)?"":"U",0xFE,FileHandler,0xFE,(LPCTSTR)oStr);
	GPC.WaitFor_m_MuteProc();
	LastResult=-123456;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);

	int i;
	for(i=0;i<m_waitCountFRead;i++)
	{
		if (GPC.m_View->DoAdditionalMessageLoop()<0) 
		{
			GPC.Release_m_MuteProc();
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "'ReadFromPICK' aborted","");
			return  -13;
		}
		GPC.m_View->DoRemappingInput();
		if (LastResult==-123456) Sleep(m_waitTimeFRead);
		else break;
	}

	if (i>=m_waitCountFRead)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'ReadFromPICK'",Key);


	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();

	if (LastResult!=-123456)
	{
		DosToAnsi(GPC.m_View->InputBuffer2);
		CString delim("\x7F");
		char *pos=strchr(GPC.m_View->InputBuffer2,'#');
		if ((pos++)==NULL) pos="";
		ret=ConvertToArray(CString(pos),RetArray,delim,m_VariantArrayType);
		long tmp=atoi(GPC.m_View->InputBuffer2);
		if (tmp<0) ret=tmp;
		else 
			if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNItemsServerRead+=ret;
	}

	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();

	return ret;
}

long CGP_TermDoc::GPOLEReadUFromPICK(long FileHandler, LPCTSTR Key, VARIANT FAR* RetArray)
{
	m_LockPICKItem=1;
	long ret=GPOLEReadFromPICK(FileHandler, Key, RetArray);
	m_LockPICKItem=0;
	return ret;
}

long CGP_TermDoc::GPOLEReadFromPICKEx(long FileHandler, const VARIANT FAR& nItem, VARIANT FAR* RetArray)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNTimesServerRead++;
	CString Keys("");
	long ret=-1;
	int num=0;

	ConvVariantToString(nItem, Keys, "\x7F");

	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ReadFromPICKEx'",Keys.Mid(0,100));

	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReadFromPICKEx' when executing TCL",Keys.Mid(0,100));
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReadFromPICKEx' when executing SUB",Keys.Mid(0,100));

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ReadFromPICKEx'",Keys.Mid(0,100));

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ReadFromPICKEx'",Keys.Mid(0,100));

	if (FileHandler<=0)
	{
		char tmps[10];
		sprintf(tmps,"%d",FileHandler);
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Bad file handler in 'ReadFromPICKEx'",tmps);
	}

	if ((V_VT(&nItem)&VT_ARRAY)!=VT_ARRAY &&
			(V_VT(&nItem) != (VT_VARIANT|VT_BYREF) || (V_VT(nItem.pvarVal)&VT_ARRAY) != VT_ARRAY))
		if ((V_VT(&nItem)&0xFF)==VT_I2 || (V_VT(&nItem)&0xFF)==VT_I4) num=2;
			else num=1;

	if (Keys.GetLength()>0)
	{
		AnsiToDosMB((LPCTSTR)Keys,Keys,0);
		char str[150];
		sprintf(str,"%sPR%sFILEEX%c%d%c%d",m_D3OlePrefix,(m_LockPICKItem==0)?"":"U",0xFE,FileHandler,0xFE,num);

	GPC.WaitFor_m_MuteProc();
		LastResult=-123456;
		if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
		m_Comm.GPSendBlock(str,(int)strlen(str));
		m_Comm.GPSendBlock("\r",1);
		if ((Keys.GetLength()%30000)==0 && Keys.GetLength()!=0)	Keys+=BLOCK_STR;
		m_Comm.GPSendBlock((LPCTSTR)Keys,Keys.GetLength());
		m_Comm.GPSendBlock("\r",1);

		int i;
		for(i=0;i<m_waitCountFRead;i++)
		{
			if (GPC.m_View->DoAdditionalMessageLoop()<0)
			{
				GPC.Release_m_MuteProc();
				GPC.m_ErrReport.GPWriteErrorLog2("COM", "'ReadFromPICKEx' aborted","");
				return  -13;
			}
			GPC.m_View->DoRemappingInput();
			if (LastResult==-123456) Sleep(m_waitTimeFRead);
			else break;
		}
		if (i>=m_waitCountFRead)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'ReadFromPICKEx'",Keys.Mid(0,100));
		
		if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();

		if (LastResult!=-123456)
		{
			DosToAnsi(GPC.m_View->InputBuffer2);
			CString delim("\x7F");
			char *pos=strchr(GPC.m_View->InputBuffer2,'#');
			if ((pos++)==NULL) pos="";
			ret=ConvertToArray(CString(pos),RetArray,delim,m_VariantArrayType);
			long tmp=atoi(GPC.m_View->InputBuffer2);
			if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNItemsServerRead+=ret;
//			if (tmp<0)
				ret=tmp;
		}
		GPC.Release_m_MuteProc();
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::GPOLEReadUFromPICKEx(long FileHandler, const VARIANT FAR& nItem, VARIANT FAR* RetArray)
{
	m_LockPICKItem=1;
	long ret=GPOLEReadFromPICKEx(FileHandler, nItem, RetArray);
	m_LockPICKItem=0;
	return ret;
}

long CGP_TermDoc::GPOLEReadKFromPICKEx(long FileHandler, const VARIANT FAR& nItem, VARIANT FAR* RetArray, VARIANT FAR* RetKeyArray)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNTimesServerRead++;
	CString Keys("");
	long ret=-1;
	int num=0;

	ConvVariantToString(nItem, Keys, "\x7F");
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ReadKFromPICKEx'",Keys.Mid(0,100));

	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReadKFromPICKEx' when executing TCL",Keys.Mid(0,100));
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReadKFromPICKEx' when executing SUB",Keys.Mid(0,100));

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ReadKFromPICKEx'",Keys.Mid(0,100));

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ReadKFromPICKEx'",Keys.Mid(0,100));

	if (FileHandler<=0)
	{
		char tmps[10];
		sprintf(tmps,"%d",FileHandler);
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Bad file handler in 'ReadKFromPICKEx'",tmps);
	}

	if ((V_VT(&nItem)&VT_ARRAY)!=VT_ARRAY &&
			(V_VT(&nItem) != (VT_VARIANT|VT_BYREF) || (V_VT(nItem.pvarVal)&VT_ARRAY) != VT_ARRAY))
		if ((V_VT(&nItem)&0xFF)==VT_I2 || (V_VT(&nItem)&0xFF)==VT_I4) num=2;
			else num=1;

	if (Keys.GetLength()>0)
	{
		AnsiToDosMB((LPCTSTR)Keys,Keys,0);
		char str[150];
		sprintf(str,"%sPRK%sFILEEX%c%d%c%d",m_D3OlePrefix,(m_LockPICKItem==0)?"":"U",0xFE,FileHandler,0xFE,num);

	GPC.WaitFor_m_MuteProc();
		LastResult=-123456;
		if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
		m_Comm.GPSendBlock(str,(int)strlen(str));
		m_Comm.GPSendBlock("\r",1);
		if ((Keys.GetLength()%30000)==0 && Keys.GetLength()!=0)	Keys+=BLOCK_STR;

		m_Comm.GPSendBlock((LPCTSTR)Keys,Keys.GetLength());
		m_Comm.GPSendBlock("\r",1);

		int i;
		for(i=0;i<m_waitCountFRead;i++)
		{
			if (GPC.m_View->DoAdditionalMessageLoop()<0)
			{
				GPC.Release_m_MuteProc();
				GPC.m_ErrReport.GPWriteErrorLog2("COM", "'ReadKFromPICKEx' aborted","");
				return  -13;
			}
			GPC.m_View->DoRemappingInput();
			if (LastResult==-123456) Sleep(m_waitTimeFRead);
			else break;
		}
		if (i>=m_waitCountFRead)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'ReadKFromPICKEx'","");

		if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();

		if (LastResult!=-123456)
		{
			DosToAnsi(GPC.m_View->InputBuffer2);
			CString delim("\x7F");
			char *pos=strchr(GPC.m_View->InputBuffer2,'#');
			char *poskey=NULL;
			if (pos!=NULL)
			{
				pos++;
				poskey=strchr(pos,0x05);
				if (poskey!=NULL) *(poskey++)=0;
				ret=ConvertToArray(CString(pos),RetArray,delim,m_VariantArrayType);
				if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNItemsServerRead+=ret;
				if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNItemsServerRead+=ret;
				ConvertToArray(CString(poskey),RetKeyArray,delim,m_VariantArrayType);
			}
			else ret=-4;

			long tmp=atoi(GPC.m_View->InputBuffer2);
//			if (tmp<0)
				ret=tmp;
		}
	GPC.Release_m_MuteProc();
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::GPOLEReadKUFromPICKEx(long FileHandler, const VARIANT FAR& nItem, VARIANT FAR* RetArray, VARIANT FAR* RetKeyArray)
{
	m_LockPICKItem=1;
	long ret=GPOLEReadKFromPICKEx( FileHandler, nItem, RetArray, RetKeyArray);
	m_LockPICKItem=0;
	return ret;
}

long CGP_TermDoc::GPOLEReadVFromPICK(long FileHandler, LPCTSTR Key, long nAttribute, BSTR FAR* Attribute)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNTimesServerRead++;
	CString oStr(Key);

	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ReadVFromPICK'",oStr);

	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReadVFromPICK' when executing TCL",oStr);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReadVFromPICK' when executing SUB",oStr);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ReadVFromPICK'",oStr);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ReadVFromPICK'",oStr);

	if (FileHandler<=0)
	{
		char tmps[10];
		sprintf(tmps,"%d",FileHandler);
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Bad file handler in 'ReadVFromPICK'",tmps);
	}

	AnsiToDosMB((LPCTSTR)oStr,oStr,0);
	long ret=-1;
	char str[150];
	sprintf(str,"%sPR%sFILEV%c%d%c%s%c%ld",m_D3OlePrefix,(m_LockPICKItem==0)?"":"U",0xFE,FileHandler,0xFE,(LPCTSTR)oStr,0xFE,nAttribute);
	GPC.WaitFor_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);

	LastResult=-123456;
	int i;
	for(i=0;i<m_waitCountFRead;i++)
	{
		if (GPC.m_View->DoAdditionalMessageLoop()<0) 
			{
				GPC.Release_m_MuteProc();
				GPC.m_ErrReport.GPWriteErrorLog2("COM", "'ReadVFromPICK' aborted","");
				return  -13;
			}
		GPC.m_View->DoRemappingInput();
		if (LastResult==-123456) Sleep(m_waitTimeFRead);
		else break;
	}
	if (i>=m_waitCountFRead)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'ReadVFromPICK'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	if (LastResult!=-123456)
	{
		DosToAnsi(GPC.m_View->InputBuffer2);
		char *pos=strchr(GPC.m_View->InputBuffer2,'#');
		if ((pos++)==NULL) pos="";
		CString delim(pos);
		delim.SetSysString(Attribute);
		ret=delim.GetLength();
		long tmp=atoi(GPC.m_View->InputBuffer2);
		if (tmp<0) ret=tmp;
		else 
			if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNItemsServerRead++;
	}
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::GPOLEReadVUFromPICK(long FileHandler, LPCTSTR Key, long nAttribute, BSTR FAR* Attribute)
{
	m_LockPICKItem=1;
	long ret=GPOLEReadVFromPICK(FileHandler, Key, nAttribute, Attribute);
	m_LockPICKItem=0;
	return ret;
}

long CGP_TermDoc::GPOLEReadVFromPICKEx(long FileHandler, const VARIANT FAR& nItem, long nAttribute, VARIANT FAR* RetArray)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNTimesServerRead++;
	CString Keys("");
	long ret=-1;
	int num=0;

	ConvVariantToString(nItem, Keys, "\x7F");
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ReadVFromPICKEx'",Keys.Mid(0,100));
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReadVFromPICKEx' when executing TCL",Keys.Mid(0,100));
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReadVFromPICKEx' when executing SUB",Keys.Mid(0,100));

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ReadVFromPICKEx'",Keys.Mid(0,100));

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ReadVFromPICKEx'",Keys.Mid(0,100));

	if (FileHandler<=0)
	{
		char tmps[10];
		sprintf(tmps,"%d",FileHandler);
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Bad file handler in 'ReadVFromPICKEx'",tmps);
	}

	if ((V_VT(&nItem)&VT_ARRAY)!=VT_ARRAY &&
			(V_VT(&nItem) != (VT_VARIANT|VT_BYREF) || (V_VT(nItem.pvarVal)&VT_ARRAY) != VT_ARRAY))
		if ((V_VT(&nItem)&0xFF)==VT_I2 || (V_VT(&nItem)&0xFF)==VT_I4) num=2;
			else num=1;

	if (Keys!="")
	{
		AnsiToDosMB((LPCTSTR)Keys,Keys,0);
		char str[150];
		sprintf(str,"%sPR%sFILEVEX%c%d%c%d%c%ld",m_D3OlePrefix,(m_LockPICKItem==0)?"":"U",0xFE,FileHandler,0xFE,num,0xFE,nAttribute);

	GPC.WaitFor_m_MuteProc();
		if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
		m_Comm.GPSendBlock(str,(int)strlen(str));
		m_Comm.GPSendBlock("\r",1);
		LastResult=-123456;
		if ((Keys.GetLength()%30000)==0 && Keys.GetLength()!=0)	Keys+=BLOCK_STR;
		m_Comm.GPSendBlock((LPCTSTR)Keys,Keys.GetLength());
		m_Comm.GPSendBlock("\r",1);

		int i;
		for(i=0;i<m_waitCountFRead;i++)
		{
			if (GPC.m_View->DoAdditionalMessageLoop()<0) 
			{
				GPC.Release_m_MuteProc();
				GPC.m_ErrReport.GPWriteErrorLog2("COM", "'ReadVFromPICKEx' aborted","");
				return  -13;
			}
			GPC.m_View->DoRemappingInput();
			if (LastResult==-123456) Sleep(m_waitTimeFRead);
			else break;
		}
		if (i>=m_waitCountFRead)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'ReadVFromPICKEx'","");

		if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();

		if (LastResult!=-123456)
		{
			DosToAnsi(GPC.m_View->InputBuffer2);
			CString delim("\x7F");
			char *pos=strchr(GPC.m_View->InputBuffer2,'#');
			if ((pos++)==NULL) pos="";
			ret=ConvertToArray(CString(pos),RetArray,delim,m_VariantArrayType);
			if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNItemsServerRead+=ret;
			long tmp=atoi(GPC.m_View->InputBuffer2);
//			if (tmp<0)
				ret=tmp;
		}
	GPC.Release_m_MuteProc();
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::GPOLEReadVUFromPICKEx(long FileHandler, const VARIANT FAR& nItem, long nAttribute, VARIANT FAR* RetArray)
{
	m_LockPICKItem=1;
	long ret=GPOLEReadVFromPICKEx(FileHandler, nItem, nAttribute, RetArray);
	m_LockPICKItem=0;
	return ret;
}

long CGP_TermDoc::GPOLEReadKVFromPICKEx(long FileHandler, const VARIANT FAR& nItem, long nAttribute, VARIANT FAR* RetArray, VARIANT FAR* RetKeyArray)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNTimesServerRead++;
	CString Keys("");
	long ret=-1;
	int num=0;

	ConvVariantToString(nItem, Keys, "\x7F");
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'KVFromPICKEx'",Keys.Mid(0,100));
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'KVFromPICKEx' when executing TCL",Keys.Mid(0,100));
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'KVFromPICKEx' when executing SUB",Keys.Mid(0,100));

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'KVFromPICKEx'",Keys.Mid(0,100));

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'KVFromPICKEx'",Keys.Mid(0,100));

	if ((V_VT(&nItem)&VT_ARRAY)!=VT_ARRAY &&
			(V_VT(&nItem) != (VT_VARIANT|VT_BYREF) || (V_VT(nItem.pvarVal)&VT_ARRAY) != VT_ARRAY))
		if ((V_VT(&nItem)&0xFF)==VT_I2 || (V_VT(&nItem)&0xFF)==VT_I4) num=2;
			else num=1;

	if (FileHandler<=0)
	{
		char tmps[10];
		sprintf(tmps,"%d",FileHandler);
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Bad file handler in 'KVFromPICKEx'",tmps);
	}

	if (Keys.GetLength()>0)
	{
		AnsiToDosMB((LPCTSTR)Keys,Keys,0);
		char str[150];
		sprintf(str,"%sPRK%sFILEVEX%c%d%c%d%c%ld",m_D3OlePrefix,(m_LockPICKItem==0)?"":"U",0xFE,FileHandler,0xFE,num,0xFE,nAttribute);

	GPC.WaitFor_m_MuteProc();
		LastResult=-123456;
		if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
		m_Comm.GPSendBlock(str,(int)strlen(str));
		m_Comm.GPSendBlock("\r",1);
		if ((Keys.GetLength()%30000)==0 && Keys.GetLength()!=0)	Keys+=BLOCK_STR;
		m_Comm.GPSendBlock((LPCTSTR)Keys,Keys.GetLength());
		m_Comm.GPSendBlock("\r",1);

		int i;
		for(i=0;i<m_waitCountFRead;i++)
		{
			if (GPC.m_View->DoAdditionalMessageLoop()<0) 
			{
				GPC.Release_m_MuteProc();
				GPC.m_ErrReport.GPWriteErrorLog2("COM", "'KVFromPICKEx' aborted","");
				return  -13;
			}
			GPC.m_View->DoRemappingInput();
			if (LastResult==-123456) Sleep(m_waitTimeFRead);
			else break;
		}
		if (i>=m_waitCountFRead)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'KVFromPICKEx'","");
		
		if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();

		if (LastResult!=-123456)
		{
			DosToAnsi(GPC.m_View->InputBuffer2);
			CString delim("\x7F");
			char *pos=strchr(GPC.m_View->InputBuffer2,'#');
			char *poskey=NULL;
			if (pos!=NULL)
			{
				pos++;
				poskey=strchr(pos,0x05);
				if (poskey!=NULL) *(poskey++)=0;
				ret=ConvertToArray(CString(pos),RetArray,delim,m_VariantArrayType);
				if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNItemsServerRead+=ret;
				ConvertToArray(CString(poskey),RetKeyArray,delim,m_VariantArrayType);
			}
			else ret=-4;

			long tmp=atoi(GPC.m_View->InputBuffer2);
//			if (tmp<0)
				ret=tmp;
		}
	GPC.Release_m_MuteProc();
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::GPOLEReadKVUFromPICKEx(long FileHandler, const VARIANT FAR& nItem, long nAttribute, VARIANT FAR* RetArray, VARIANT FAR* RetKeyArray)
{
	m_LockPICKItem=1;
	long ret=GPOLEReadKVFromPICKEx(FileHandler, nItem, nAttribute, RetArray, RetKeyArray);
	m_LockPICKItem=0;
	return ret;
}

long CGP_TermDoc::GPOLEWriteToPICK(long FileHandler, LPCTSTR Key, const VARIANT FAR&RecArray)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNTimesServerWrite++;
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNItemsServerWrite++;
	CString oStr(Key);
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'WriteToPICK'",oStr);
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'WriteToPICK' when executing TCL",oStr);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'WriteToPICK' when executing SUB",oStr);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'WriteToPICK'",oStr);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'WriteToPICK'",oStr);

	if (FileHandler<=0)
	{
		char tmps[10];
		sprintf(tmps,"%d",FileHandler);
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Bad file handler in 'WriteToPICK'",tmps);
	}

	AnsiToDosMB((LPCTSTR)oStr,oStr,0);
	long ret=-1;
	char str[150];
	sprintf(str,"%sPW%sFILE%c%d%c%s",m_D3OlePrefix,(m_LockPICKItem==0)?"":"U",0xFE,FileHandler,0xFE,(LPCTSTR)oStr);
	GPC.WaitFor_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);

	LastResult=-123456;
	ConvVariantToString(RecArray, oStr, "\x7F");
	AnsiToDosMB((LPCTSTR)oStr,oStr,1);
	if ((oStr.GetLength()%30000)==0 && oStr.GetLength()!=0)	oStr+=BLOCK_STR;
	m_Comm.GPSendBlock((LPCTSTR)oStr,oStr.GetLength());
	m_Comm.GPSendBlock("\r",1);

	if (m_waitCountFWrite*m_waitTimeFWrite<20000)
	{
		m_waitCountFWrite=400;
		m_waitTimeFWrite=50;
	}
	int i;
	for(i=0;i<m_waitCountFWrite;i++)
	{
		if (GPC.m_View->DoAdditionalMessageLoop()<0) 
		{
			GPC.Release_m_MuteProc();
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "'WriteToPICK' aborted","");
			return  -13;
		}
		GPC.m_View->DoRemappingInput();
		if (LastResult==-123456) Sleep(m_waitTimeFWrite);
		else
		{
			ret=atoi(GPC.m_View->InputBuffer2);
			break;
		}
	}
	if (i>=m_waitCountFWrite)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'WriteToPICK'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	GPC.Release_m_MuteProc();

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();

	return ret;
}

long CGP_TermDoc::GPOLEWriteUToPICK(long FileHandler, LPCTSTR Key, const VARIANT FAR& RecArray)
{
	m_LockPICKItem=1;
	long ret=GPOLEWriteToPICK( FileHandler, Key, RecArray);
	m_LockPICKItem=0;
	return ret;
}

long CGP_TermDoc::GPOLEWriteToPICKEx(long FileHandler, const VARIANT FAR& KeyArray, const VARIANT FAR& ItemArray)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNTimesServerWrite++;
	long ret=-1;

	CString LinesKey,LinesItem;

	ConvVariantToString(KeyArray, LinesKey, "\x7F");
	ConvVariantToString(ItemArray, LinesItem, "\x7F");
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'WriteToPICKEx'",LinesKey.Mid(0,100));
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'WriteToPICKEx' when executing TCL",LinesKey.Mid(0,100));
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'WriteToPICKEx' when executing SUB",LinesKey.Mid(0,100));

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'WriteToPICKEx'",LinesKey.Mid(0,100));

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'WriteToPICKEx'",LinesKey.Mid(0,100));

	if (FileHandler<=0)
	{
		char tmps[10];
		sprintf(tmps,"%d",FileHandler);
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Bad file handler in 'WriteToPICKEx'",tmps);
	}

	ret=LinesKey.GetLength();
	ret=LinesItem.GetLength();
	if (LinesKey!="" && LinesItem!="")
	{
		ret=1;
		AnsiToDosMB((LPCTSTR)LinesKey,LinesKey,0);
		AnsiToDosMB((LPCTSTR)LinesItem,LinesItem,0);

		char str[50];
		sprintf(str,"%sPW%sFILEEX%c%d",m_D3OlePrefix,(m_LockPICKItem==0)?"":"U",0xFE,FileHandler);
	GPC.WaitFor_m_MuteProc();
		LastResult=-123456;
		if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
		m_Comm.GPSendBlock(str,(int)strlen(str));
		m_Comm.GPSendBlock("\r",1);
		if ((LinesKey.GetLength()%30000)==0 && LinesKey.GetLength()!=0)	LinesKey+=BLOCK_STR;
		m_Comm.GPSendBlock((LPCTSTR)LinesKey,LinesKey.GetLength());
		m_Comm.GPSendBlock("\r",1);

		if ((LinesItem.GetLength()%30000)==0 && LinesItem.GetLength()!=0)	LinesItem+=BLOCK_STR;
		m_Comm.GPSendBlock((LPCTSTR)LinesItem,LinesItem.GetLength());
		m_Comm.GPSendBlock("\r",1);

	if (m_waitCountFWrite*m_waitTimeFWrite<20000)
	{
		m_waitCountFWrite=400;
		m_waitTimeFWrite=50;
	}

	int i;
	for(i=0;i<m_waitCountFWrite;i++)
	{
		if (GPC.m_View->DoAdditionalMessageLoop()<0)
		{
			GPC.Release_m_MuteProc();
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "'WriteToPICKEx' aborted","");
			return  -13;
		}
		GPC.m_View->DoRemappingInput();
		if (LastResult==-123456) Sleep(m_waitTimeFWrite);
		else
		{
			ret=atoi(GPC.m_View->InputBuffer2);
			if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNItemsServerWrite+=ret;
			break;
		}
	}
	if (i>=m_waitCountFWrite)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'WriteToPICKEx'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();


	GPC.Release_m_MuteProc();
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();

	return ret;
}

long CGP_TermDoc::GPOLEWriteUToPICKEx(long FileHandler, const VARIANT FAR& KeyArray, const VARIANT FAR& ItemArray)
{
	m_LockPICKItem=1;
	long ret=GPOLEWriteToPICKEx( FileHandler, KeyArray, ItemArray);
	m_LockPICKItem=0;
	return ret;
}

long CGP_TermDoc::GPOLEWriteVToPICK(long FileHandler, LPCTSTR Key, long nAtribute, LPCTSTR vString)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNTimesServerWrite++;
	CString oStr(Key);
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'WriteVToPICK'",oStr);
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'WriteVToPICK' when executing TCL",oStr);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'WriteVToPICK' when executing SUB",oStr);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'WriteVToPICK'",oStr);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'WriteVToPICK'",oStr);

	if (FileHandler<=0)
	{
		char tmps[10];
		sprintf(tmps,"%d",FileHandler);
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Bad file handler in 'WriteVToPICK'",tmps);
	}


	AnsiToDosMB((LPCTSTR)oStr,oStr,0);
	long ret=-1;
	char str[150];
	sprintf(str,"%sPW%sFILEV%c%d%c%s%c%ld",m_D3OlePrefix,(m_LockPICKItem==0)?"":"U",0xFE,FileHandler,0xFE,(LPCTSTR)oStr,0xFE,nAtribute);
	GPC.WaitFor_m_MuteProc();

	LastResult=-123456;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);

	oStr=vString;
	AnsiToDosMB((LPCTSTR)oStr,oStr,0);
	if ((oStr.GetLength()%30000)==0 && oStr.GetLength()!=0)	oStr+=BLOCK_STR;
	m_Comm.GPSendBlock((LPCTSTR)oStr,oStr.GetLength());
	m_Comm.GPSendBlock("\r",1);

	if (m_waitCountFWrite*m_waitTimeFWrite<20000)
	{
		m_waitCountFWrite=400;
		m_waitTimeFWrite=50;
	}

	int i;
	for(i=0;i<m_waitCountFWrite;i++)
	{
		if (GPC.m_View->DoAdditionalMessageLoop()<0)
		{
			GPC.Release_m_MuteProc();
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "'WriteVToPICK' aborted","");
			return  -13;
		}
		GPC.m_View->DoRemappingInput();
		if (LastResult==-123456) Sleep(m_waitTimeFWrite);
		else
		{
			ret=atoi(GPC.m_View->InputBuffer2);
			if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNItemsServerWrite+=ret;
			break;
		}
	}
	if (i>=m_waitCountFWrite)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'WriteVToPICK'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	GPC.Release_m_MuteProc();

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();

	return ret;
}

long CGP_TermDoc::GPOLEWriteVUToPICK(long FileHandler, LPCTSTR Key, long nAttribute, LPCTSTR vString)
{
	m_LockPICKItem=1;
	long ret=GPOLEWriteVToPICK( FileHandler, Key, nAttribute, vString);
	m_LockPICKItem=0;
	return ret;
}

long CGP_TermDoc::GPOLEWriteVToPICKEx(long FileHandler, const VARIANT FAR& KeyArray, const VARIANT FAR& nAttrArray, const VARIANT FAR& ValuesArray)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNTimesServerWrite++;
	long ret=-1;

	CString LinesKey,LinesValue,LinesAttr;

	ConvVariantToString(KeyArray, LinesKey, "\x7F");
	ConvVariantToString(ValuesArray, LinesValue, "\x7F");
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'WriteVToPICKEx'",LinesKey.Mid(0,100));
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'WriteVToPICKEx' when executing TCL",LinesKey.Mid(0,100));
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'WriteVToPICKEx' when executing SUB",LinesKey.Mid(0,100));

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'WriteVToPICKEx'",LinesKey.Mid(0,100));

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'WriteVToPICKEx'",LinesKey.Mid(0,100));

	if (FileHandler<=0)
	{
		char tmps[10];
		sprintf(tmps,"%d",FileHandler);
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Bad file handler in 'WriteVToPICKEx'",tmps);
	}

    char delimstr11[]={0xFD,0x00,};
	ConvVariantToString(nAttrArray, LinesAttr, delimstr11);

	if (LinesKey!="" /*&& LinesValue!="" */&& LinesAttr!="")
	{
		ret=1;
		AnsiToDosMB((LPCTSTR)LinesKey,LinesKey,0);
		AnsiToDosMB((LPCTSTR)LinesValue,LinesValue,0);

		char str[50];
		sprintf(str,"%sPW%sFILEVEX%c%ld",m_D3OlePrefix,(m_LockPICKItem==0)?"":"U",0xFE,FileHandler);
		GPC.WaitFor_m_MuteProc();
		LastResult=-123456;
		if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
		m_Comm.GPSendBlock(str,(int)strlen(str));
		m_Comm.GPSendBlock("\r",1);

		if ((LinesKey.GetLength()%30000)==0 && LinesKey.GetLength()!=0)		LinesKey+=BLOCK_STR;
		m_Comm.GPSendBlock((LPCTSTR)LinesKey,LinesKey.GetLength());
		m_Comm.GPSendBlock("\r",1);

		if ((LinesValue.GetLength()%30000)==0 && LinesValue.GetLength()!=0)	LinesValue+=BLOCK_STR;
		m_Comm.GPSendBlock((LPCTSTR)LinesValue,LinesValue.GetLength());
		m_Comm.GPSendBlock("\r",1);

		if ((LinesAttr.GetLength()%30000)==0 && LinesAttr.GetLength()!=0)	LinesAttr+=BLOCK_STR;
		m_Comm.GPSendBlock((LPCTSTR)LinesAttr,LinesAttr.GetLength());
		m_Comm.GPSendBlock("\r",1);

		if (m_waitCountFWrite*m_waitTimeFWrite<20000)
		{
			m_waitCountFWrite=400;
			m_waitTimeFWrite=50;
		}
		int i;
		for(i=0;i<m_waitCountFWrite;i++)
		{
			if (GPC.m_View->DoAdditionalMessageLoop()<0)
			{
				GPC.Release_m_MuteProc();
				GPC.m_ErrReport.GPWriteErrorLog2("COM", "'WriteVToPICKEx' aborted","");
				return  -13;
			}
			GPC.m_View->DoRemappingInput();
			if (LastResult==-123456) Sleep(m_waitTimeFWrite);
			else
			{
				ret=atoi(GPC.m_View->InputBuffer2);
				if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNItemsServerWrite+=ret;
				break;
			}
		}
		if (i>=m_waitCountFWrite)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'WriteVToPICKEx'","");
	
		if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
		GPC.Release_m_MuteProc();
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();

	return ret;
}

long CGP_TermDoc::GPOLEWriteVUToPICKEx(long FileHandler, const VARIANT FAR& KeyArray, const VARIANT FAR& nAttrArray, const VARIANT FAR& ValuesArray)
{
	m_LockPICKItem=1;
	long ret=GPOLEWriteVToPICKEx(FileHandler, KeyArray, nAttrArray, ValuesArray);
	m_LockPICKItem=0;
	return ret;
}

long CGP_TermDoc::GPOLEGetActiveList(VARIANT FAR* ListArray)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNTimesServerRead++;
	long ret=-1;
	GPC.WaitFor_m_MuteProc();
	LastResult=-123456;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'GetActiveList'","");
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'GetActiveList' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'GetActiveList' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'GetActiveList'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'GetActiveList'","");

	m_Comm.GPSendBlock(m_D3OlePrefix,5);
	m_Comm.GPSendBlock("PGALIST\r",8);

	int i;
	for(i=0;i<m_waitCountFRead;i++)
	{
		if (GPC.m_View->DoAdditionalMessageLoop()<0)
		{
			GPC.Release_m_MuteProc();
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "'GetActiveList' aborted","");
			return  -13;
		}
		GPC.m_View->DoRemappingInput();
		if (LastResult==-123456) Sleep(m_waitTimeFRead);
		else break;
	}
	if (i>=m_waitCountFRead)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'GetActiveList'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();

	if (LastResult!=-123456)
	{
		if ((ret=atoi(GPC.m_View->InputBuffer2))>0)
		{
			DosToAnsi(GPC.m_View->InputBuffer2);
			CString delim("\x7F");
			char *pos=strchr(GPC.m_View->InputBuffer2,'#');
			if ((pos++)==NULL) pos="";
			ret=ConvertToArray(CString(pos),ListArray,delim,m_VariantArrayType);
		}
	}
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();

	return ret;
}

long CGP_TermDoc::GPOLEGetList(LPCTSTR FileName, LPCTSTR ListName, VARIANT FAR* RetArray)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNTimesServerRead++;
	long ret=-1;
	CString fStr(FileName);
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'GetList'",FileName);
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'GetList' when executing TCL",FileName);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'GetList' when executing SUB",FileName);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'GetList'",FileName);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'GetList'",FileName);

	AnsiToDosMB((LPCTSTR)fStr,fStr,0);

	CString lStr(ListName);
	AnsiToDosMB((LPCTSTR)lStr,lStr,0);

	char str[250];
	sprintf(str,"%sPGLIST%c%s%c%s",m_D3OlePrefix,0xFE,(LPCTSTR)fStr,0xFE,(LPCTSTR)lStr);
	GPC.WaitFor_m_MuteProc();
	LastResult=-123456;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);

	int i;
	for(i=0;i<m_waitCountFRead;i++)
	{
		if (GPC.m_View->DoAdditionalMessageLoop()<0)
		{
			GPC.Release_m_MuteProc();
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "'GetList' aborted","");
			return  -13;
		}
		GPC.m_View->DoRemappingInput();
		if (LastResult==-123456) Sleep(m_waitTimeFRead);
		else break;
	}
	if (i>=m_waitCountFRead)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'GetList'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();

	if (LastResult!=-123456)
	{
		if ((ret=atoi(GPC.m_View->InputBuffer2))>0)
		{
			DosToAnsi(GPC.m_View->InputBuffer2);
			CString delim("\x7F");
			char *pos=strchr(GPC.m_View->InputBuffer2,'#');
			if ((pos++)==NULL) pos="";
			if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNItemsServerRead++;
			ret=ConvertToArray(CString(pos),RetArray,delim,m_VariantArrayType);
		}
	}
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();

	return ret;
}

long CGP_TermDoc::GPOLESaveListNet(LPCTSTR FileName, LPCTSTR ListName, const VARIANT FAR& ListArray)
{
	return GPOLESaveList(FileName, ListName, (VARIANT FAR*)&ListArray);
}

long CGP_TermDoc::GPOLESaveList(LPCTSTR FileName, LPCTSTR ListName, VARIANT FAR* ListArray)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNTimesServerWrite++;
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNItemsServerWrite++;
	long ret=-1;

	CString fStr(FileName);
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'SaveList'",fStr);
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'SaveList' when executing TCL",fStr);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'SaveList' when executing SUB",fStr);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'SaveList'",fStr);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'SaveList'",fStr);

	AnsiToDosMB((LPCTSTR)fStr,fStr,0);

	CString lStr(ListName);
	AnsiToDosMB((LPCTSTR)lStr,lStr,0);

	char str[250];
	sprintf(str,"%sPSLIST%c%s%c%s",m_D3OlePrefix,0xFE,(LPCTSTR)fStr,0xFE,(LPCTSTR)lStr);
	GPC.WaitFor_m_MuteProc();
	LastResult=-123456;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);

	CString delim("\x7F");
	CString oStr;

	ConvertToString(ListArray,oStr, delim);
	AnsiToDosMB((LPCTSTR)oStr,oStr,1);
	if ((oStr.GetLength()%30000)==0 && oStr.GetLength()!=0)	oStr+=BLOCK_STR;
	m_Comm.GPSendBlock((LPCTSTR)oStr,oStr.GetLength());
	m_Comm.GPSendBlock("\r",1);

	int i;
	for(i=0;i<m_waitCountFWrite;i++)
	{
		if (GPC.m_View->DoAdditionalMessageLoop()<0) 
		{
			GPC.Release_m_MuteProc();
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "'SaveList' aborted","");
			return  -13;
		}
		GPC.m_View->DoRemappingInput();
		if (LastResult==-123456) Sleep(m_waitTimeFWrite);
		else
		{
			ret=atoi(GPC.m_View->InputBuffer2);
			break;
		}
	}
	if (i>=m_waitCountFWrite)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'SaveList'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();

	return ret;
}


long CGP_TermDoc::GPOLEDeleteFromPICKFile(long FileHandler, LPCTSTR Item)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	CString oStr(Item);
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'DeleteFromPICKFile'",Item);
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'DeleteFromPICKFile' when executing TCL",Item);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'DeleteFromPICKFile' when executing SUB",Item);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'DeleteFromPICKFile'",Item);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'DeleteFromPICKFile'",Item);

	if (FileHandler<=0)
	{
		char tmps[10];
		sprintf(tmps,"%d",FileHandler);
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Bad file handler in 'DeleteFromPICKFile'",tmps);
	}

	AnsiToDosMB((LPCTSTR)oStr,oStr,0);
	long ret=-1;

	char str[150];
	sprintf(str,"%sPDFILE%c%d%c%s",m_D3OlePrefix,0xFE,FileHandler,0xFE,(LPCTSTR)oStr);
	GPC.WaitFor_m_MuteProc();
	LastResult=-123456;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);

	int i;
	for(i=0;i<m_waitCountFOther;i++)
	{
		if (GPC.m_View->DoAdditionalMessageLoop()<0)
		{
			GPC.Release_m_MuteProc();
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "'DeleteFromPICKFile' aborted","");
			return  -13;
		}
		GPC.m_View->DoRemappingInput();
		if (LastResult==-123456) Sleep(m_waitTimeFOther);
		else
		{
			ret=atoi(GPC.m_View->InputBuffer2);
			break;
		}
	}
	if (i>=m_waitCountFOther)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'DeleteFromPICKFile'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::GPOLEItemExist(long FileHandler, LPCTSTR ItemKey)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	CString oStr(ItemKey);
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ItemExist'",ItemKey);
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ItemExist' when executing TCL",ItemKey);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ItemExist' when executing SUB",ItemKey);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ItemExist'",ItemKey);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ItemExist'",ItemKey);

	if (FileHandler<=0)
	{
		char tmps[10];
		sprintf(tmps,"%d",FileHandler);
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Bad file handler in 'ItemExist'",tmps);
	}

	AnsiToDosMB((LPCTSTR)oStr,oStr,0);
	long ret=-10;

	char str[150];
	sprintf(str,"%sPIEXIST%c%d%c%s",m_D3OlePrefix,0xFE,FileHandler,0xFE,(LPCTSTR)oStr);
	GPC.WaitFor_m_MuteProc();
	LastResult=-123456;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);

	int i;
	for(i=0;i<m_waitCountFOther;i++)
	{
		if (GPC.m_View->DoAdditionalMessageLoop()<0)
		{
			GPC.Release_m_MuteProc();
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "'ItemExist' aborted","");
			return  -13;
		}
		GPC.m_View->DoRemappingInput();
		if (LastResult==-123456) Sleep(m_waitTimeFOther);
	}
	if (i>=m_waitCountFOther)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'ItemExist'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();

	if (LastResult!=-123456)
	{
		ret=atoi(GPC.m_View->InputBuffer2);
	}
	GPC.Release_m_MuteProc();

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}
long CGP_TermDoc::GPOLEArrayToString(const VARIANT FAR& iArray, BSTR FAR* oString, LPCTSTR DelimiterString)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	CString tmp;
	long ret=ConvVariantToString(iArray, tmp, DelimiterString);
	tmp.SetSysString(oString);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}


long CGP_TermDoc::GPOLEStringToArray(LPCTSTR iString, VARIANT FAR* oArray, LPCTSTR DelimString)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=ConvertToArray(CString(iString),oArray,CString(DelimString),m_VariantArrayType);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}


long CGP_TermDoc::GPOLECountOccur(LPCTSTR iString, LPCTSTR SubString)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=CountOccurence(iString,SubString);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::GPOLEIndexSubString(LPCTSTR iString, LPCTSTR SubString, long Occurence)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GetIndexSubString(iString, SubString, Occurence);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}


void CGP_TermDoc::GPOLEGetListEx(const VARIANT FAR& TCLLines)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNTimesServerRead++;
	CString Lines;
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'GetListEx'",Lines);
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'GetListEx' when executing TCL",Lines);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'GetListEx' when executing SUB",Lines);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'GetListEx'",Lines);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'GetListEx'",Lines);

	ConvVariantToString(TCLLines, Lines, "\x7F");
	if (Lines=="") Lines="WHO";
	AnsiToDosMB((LPCTSTR)Lines,Lines,1);
	GPC.ClearOUTSUB();
	GPC.ClearOUTTCL();
	GPC.m_WaitSUB=TRUE;
	GPC.m_WaitEndSUB=TRUE;
	GPC.WaitFor_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(m_D3OlePrefix,5);
	m_Comm.GPSendBlock("PGLISTEX",8);

	if ((Lines.GetLength()%30000)==0 && Lines.GetLength()!=0)	Lines+=BLOCK_STR;
	m_Comm.GPSendBlock((LPCTSTR)Lines,Lines.GetLength());
	m_Comm.GPSendBlock("\r",1);
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}


void CGP_TermDoc::GPOLEEndMessageMap()
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'EndMessageMap'","");
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'EndMessageMap' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'EndMessageMap' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'EndMessageMap'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'EndMessageMap'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	GPC.WaitFor_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(m_D3OlePrefix,5);
	m_Comm.GPSendBlock("MMOFF\r",6);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

long CGP_TermDoc::GPOIsScriptOn()
{
	return GPC.cs_ScriptLine.GetLength();
}

void CGP_TermDoc::GPOExecuteScript(LPCTSTR iString)
{
	CString tmps=iString;
	GPC.cs_ScriptLine+=tmps;
	GPC.m_View->DoScriptCommand();
}

void CGP_TermDoc::GPOAbortScript()
{
	GPC.m_View->KillTimer(SCRIPTOUT_TIMER_ID);
	GPC.cs_ScriptLine="";
}

long CGP_TermDoc::GPOLEIsMessageMapOn()
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'IsMessageMapOn'","");
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'IsMessageMapOn' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'IsMessageMapOn' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'IsMessageMapOn'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'IsMessageMapOn'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=-1;
	GPC.WaitFor_m_MuteProc();
	LastResult=-123456;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(m_D3OlePrefix,5);
	m_Comm.GPSendBlock("ISMMON\r",7);

	int i;
	for(i=0;i<m_waitCountMM;i++)
	{
		if (GPC.m_View->DoAdditionalMessageLoop()<0)
		{
			GPC.Release_m_MuteProc();
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "'IsMessageMapOn' aborted","");
			return  -13;
		}
		GPC.m_View->DoRemappingInput();
		if (LastResult==-123456) Sleep(m_waitTimeMM);
		else break;
	}
	if (i>=m_waitCountMM)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'IsMessageMapOn'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();

	if (LastResult!=-123456)
	{
		ret=atoi(GPC.m_View->InputBuffer2);
	}
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}


DATE CGP_TermDoc::GPOLEGetTimeFromPICK(const VARIANT FAR& PICKTime)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	double n;
	CString str;
	long tmp=0;
	if ((V_VT(&PICKTime)&VT_ARRAY)==VT_ARRAY || (V_VT(&PICKTime)&0xFF)==VT_BSTR)
	{
		ConvVariantToString(PICKTime, str, "\x7F");
		tmp=atoi(str);
	}
	else
	if (V_VT(&PICKTime)==(VT_VARIANT|VT_BYREF))
	{
		ConvVariantToString(*PICKTime.pvarVal, str, "\x7F");
		tmp=atoi(str);
	}
	else
	if ((V_VT(&PICKTime)&0xFF)==VT_I2 || (V_VT(&PICKTime)&0xFF)==VT_I4)	tmp=PICKTime.iVal;
	else
	if ((V_VT(&PICKTime)&0xFF)==VT_R4)  	tmp= (long)modf(PICKTime.fltVal, &n );
	else
	if ((V_VT(&PICKTime)&0xFF)==VT_R8
		|| (V_VT(&PICKTime)&0xFF)==VT_DATE
		|| (V_VT(&PICKTime)&0xFF)==VT_CY) tmp= (long)modf(PICKTime.dblVal, &n );
	else
		AfxThrowOleDispatchException(1008,IDS_GPOLEEXEPTION1008);

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return (DATE) tmp/3600/24;
}

DATE CGP_TermDoc::GPOLEGetDateFromPICK(const VARIANT FAR& PICKDate)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	double n;
	CString str;
	long tmp=0;
	if ((V_VT(&PICKDate)&VT_ARRAY)==VT_ARRAY || (V_VT(&PICKDate)&0xFF)==VT_BSTR)
	{
		ConvVariantToString(PICKDate, str, "\x7F");
		tmp=atoi(str);
	}
	else
	if (V_VT(&PICKDate)==(VT_VARIANT|VT_BYREF))
	{
		ConvVariantToString(*PICKDate.pvarVal, str, "\x7F");
		tmp=atoi(str);
	}
	else
	if ((V_VT(&PICKDate)&0xFF)==VT_I2)	tmp=PICKDate.iVal;
	else
	if ((V_VT(&PICKDate)&0xFF)==VT_I4)	tmp=PICKDate.lVal;
	else
		if ((V_VT(&PICKDate)&0xFF)==VT_R4)
		{modf(PICKDate.fltVal, &n );tmp= (long)n;}
	else
	if ((V_VT(&PICKDate)&0xFF)==VT_R8
		|| (V_VT(&PICKDate)&0xFF)==VT_DATE
		|| (V_VT(&PICKDate)&0xFF)==VT_CY)
		{modf(PICKDate.dblVal, &n );tmp= (long)n;}
	else
		AfxThrowOleDispatchException(1008,IDS_GPOLEEXEPTION1008);

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return (DATE) tmp+24837;
}

long CGP_TermDoc::GPOLESetTimeToPICK(DATE iOleDateTime)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	double n;
	long ret=(long)(modf(iOleDateTime, &n )*3600*24);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::GPOLESetDateToPICK(DATE iOLEDateTime)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	double n;
	modf( iOLEDateTime, &n );
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return (long)n-24837;
}

void CGP_TermDoc::GPOLEResetActiveList()
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ResetActiveList'","");
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ResetActiveList' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ResetActiveList' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ResetActiveList'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ResetActiveList'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	GPC.WaitFor_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(m_D3OlePrefix,5);
	m_Comm.GPSendBlock("RESETSEL\r",9);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

void CGP_TermDoc::OnCloseDocument()
{
	SetModifiedFlag(FALSE);
	try	{COleServerDoc::OnCloseDocument();}
	catch(...)	
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGP_TermDoc", "OnCloseDocument","");
	}
}


BOOL CGP_TermDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
//	if (!COleServerDoc::OnOpenDocument(lpszPathName))
//		return FALSE;

	SetModifiedFlag(FALSE);
	return TRUE;
}

BOOL CGP_TermDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: Add your specialized code here and/or call the base class

	SetModifiedFlag(FALSE);
	return TRUE;
//	return COleServerDoc::OnSaveDocument(lpszPathName);
}

BOOL CGP_TermDoc::OnUpdateDocument()
{
	// TODO: Add your specialized code here and/or call the base class
	SetModifiedFlag(FALSE);
	return TRUE;
//	return COleServerDoc::OnUpdateDocument();
}

BOOL CGP_TermDoc::SaveModified()
{
	// TODO: Add your specialized code here and/or call the base class
	SetModifiedFlag(FALSE);
	return TRUE;
//	return COleServerDoc::SaveModified();
}

void CGP_TermDoc::GPOLEDoSystem(VARIANT FAR* RetArray, long nSystem)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	char str[100];
	sprintf(str,"%sPDOSYS%c%d",m_D3OlePrefix,0xFE,nSystem);
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'DoSystem'",str);
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'DoSystem' when executing TCL",str);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'DoSystem' when executing SUB",str);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'DoSystem'",str);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'DoSystem'",str);

	GPC.WaitFor_m_MuteProc();
	LastResult=-123456;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);

	int i;
	for(i=0;i<m_waitCountFOther;i++)
	{
		if (GPC.m_View->DoAdditionalMessageLoop()<0) {GPC.Release_m_MuteProc(); return ;}
		GPC.m_View->DoRemappingInput();
		if (LastResult==-123456) Sleep(m_waitTimeFOther);
		else break;
	}
	if (i>=m_waitCountFOther)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'DoSystem'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	if (LastResult!=-123456)
	{
		DosToAnsi(GPC.m_View->InputBuffer2);
		CString delim("\x7F");
		char *pos=strchr(GPC.m_View->InputBuffer2,'#');
		if ((pos++)==NULL) pos="";
		ConvertToArray(CString(pos),RetArray,delim,m_VariantArrayType);
	}
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}


void CGP_TermDoc::OnWaitTimeTCLChanged()
{

	if (m_waitTimeTCL<1 || m_waitTimeTCL>100000) m_waitTimeTCL=GPC.m_OLESETTINGS.m_WTCL;
	if (m_waitTimeTCL<1 || m_waitTimeTCL>100000) m_waitTimeTCL=50;
	GPC.m_OLESETTINGS.m_WTCL=m_waitTimeTCL;
}

void CGP_TermDoc::OnWaitTimeSUBChanged()
{
	if (m_waitTimeSUB<1 || m_waitTimeSUB>100000) m_waitTimeSUB=GPC.m_OLESETTINGS.m_WSUB;
	if (m_waitTimeSUB<1 || m_waitTimeSUB>100000) m_waitTimeSUB=50;
	GPC.m_OLESETTINGS.m_WSUB=m_waitTimeSUB;
}

void CGP_TermDoc::OnWaitTimeFReadChanged()
{
	if (m_waitTimeFRead<1 || m_waitTimeFRead>100000) m_waitTimeFRead=GPC.m_OLESETTINGS.m_WFRead;
	if (m_waitTimeFRead<1 || m_waitTimeFRead>100000) m_waitTimeFRead=50;
	GPC.m_OLESETTINGS.m_WFRead=m_waitTimeFRead;
}

void CGP_TermDoc::OnWaitTimeSystemChanged()
{
	if (m_waitTimeSystem<1 || m_waitTimeSystem>100000) m_waitTimeSystem=GPC.m_OLESETTINGS.m_WSystem;
	if (m_waitTimeSystem<1 || m_waitTimeSystem>100000) m_waitTimeSystem=50;
	GPC.m_OLESETTINGS.m_WSystem=m_waitTimeSystem;
}

void CGP_TermDoc::OnWaitTimeMMChanged()
{
	if (m_waitTimeMM<1 || m_waitTimeMM>100000) m_waitTimeMM=GPC.m_OLESETTINGS.m_WMM;
	if (m_waitTimeMM<1 || m_waitTimeMM>100000) m_waitTimeMM=50;
	GPC.m_OLESETTINGS.m_WMM=m_waitTimeMM;
}

void CGP_TermDoc::OnWaitTimeInputChanged()
{
	if (m_waitTimeInput<1 || m_waitTimeInput>100000) m_waitTimeInput=GPC.m_OLESETTINGS.m_WInput;
	if (m_waitTimeInput<1 || m_waitTimeInput>100000) m_waitTimeInput=60;
	GPC.m_OLESETTINGS.m_WInput=m_waitTimeInput;
}

void CGP_TermDoc::OnWaitTimeFWriteChanged()
{
	if (m_waitTimeFWrite<1 || m_waitTimeFWrite>100000) m_waitTimeFWrite=GPC.m_OLESETTINGS.m_WFWrite;
	if (m_waitTimeFWrite<1 || m_waitTimeFWrite>100000) m_waitTimeFWrite=50;
	GPC.m_OLESETTINGS.m_WFWrite=m_waitTimeFWrite;
}

void CGP_TermDoc::OnWaitTimeFOtherChanged()
{
	if (m_waitTimeFOther<1 || m_waitTimeFOther>100000) m_waitTimeFOther=GPC.m_OLESETTINGS.m_WFOther;
	if (m_waitTimeFOther<1 || m_waitTimeFOther>100000) m_waitTimeFOther=50;
	GPC.m_OLESETTINGS.m_WFOther=m_waitTimeFOther;
}


void CGP_TermDoc::OnWaitCountTCLChanged()
{
	if (m_waitCountTCL<5 || m_waitCountTCL>100000) m_waitCountTCL=GPC.m_OLESETTINGS.m_CTCL;
	if (m_waitCountTCL<5 || m_waitCountTCL>100000) m_waitCountTCL=3000;
	GPC.m_OLESETTINGS.m_CTCL=m_waitCountTCL;
}

void CGP_TermDoc::OnWaitCountSystemChanged()
{
	if (m_waitCountSystem<5 || m_waitCountSystem>100000) m_waitCountSystem=GPC.m_OLESETTINGS.m_CSystem;
	if (m_waitCountSystem<5 || m_waitCountSystem>100000) m_waitCountSystem=60;
	GPC.m_OLESETTINGS.m_CSystem=m_waitCountSystem;
}

void CGP_TermDoc::OnWaitCountSUBChanged()
{
	if (m_waitCountSUB<5 || m_waitCountSUB>100000) m_waitCountSUB=GPC.m_OLESETTINGS.m_CSUB;
	if (m_waitCountSUB<5 || m_waitCountSUB>100000) m_waitCountSUB=3000;
	GPC.m_OLESETTINGS.m_CSUB=m_waitCountSUB;
}

void CGP_TermDoc::OnWaitCountMMChanged()
{
	if (m_waitCountMM<5 || m_waitCountMM>100000) m_waitCountMM=GPC.m_OLESETTINGS.m_CMM;
	if (m_waitCountMM<5 || m_waitCountMM>100000) m_waitCountMM=60;
	GPC.m_OLESETTINGS.m_CMM=m_waitCountMM;
}

void CGP_TermDoc::OnWaitCountInputChanged()
{
	if (m_waitCountInput<5 || m_waitCountInput>100000) m_waitCountInput=GPC.m_OLESETTINGS.m_CInput;
	if (m_waitCountInput<5 || m_waitCountInput>100000) m_waitCountInput=1000;
	GPC.m_OLESETTINGS.m_CInput=m_waitCountInput;
}

void CGP_TermDoc::OnWaitCountFWriteChanged()
{
	if (m_waitCountFWrite<5 || m_waitCountFWrite>100000) m_waitCountFWrite=GPC.m_OLESETTINGS.m_CFWrite;
	if (m_waitCountFWrite<5 || m_waitCountFWrite>100000) m_waitCountFWrite=3000;
	GPC.m_OLESETTINGS.m_CFWrite=m_waitCountFWrite;
}

void CGP_TermDoc::OnWaitCountFReadChanged()
{
	if (m_waitCountFRead<5 || m_waitCountFRead>100000) m_waitCountFRead=GPC.m_OLESETTINGS.m_CFRead;
	if (m_waitCountFRead<5 || m_waitCountFRead>100000) m_waitCountFRead=1000;
	GPC.m_OLESETTINGS.m_CFRead=m_waitCountFRead;
}

void CGP_TermDoc::OnWaitCountFOtherChanged()
{
	if (m_waitCountFOther<5 || m_waitCountFOther>100000) m_waitCountFOther=GPC.m_OLESETTINGS.m_CFOther;
	if (m_waitCountFOther<5 || m_waitCountFOther>100000) m_waitCountFOther=100;
	GPC.m_OLESETTINGS.m_CFOther=m_waitCountFOther;
}





#include <comdef.h>


long CGP_TermDoc::GPOLEConvertToSubArray(VARIANT FAR* ConvArray, LPCTSTR Delimiter)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	SAFEARRAY FAR* psa = NULL;
	VARIANT *v;
	USES_CONVERSION;
	HRESULT hr;
	hr=NULL;

	if ((V_VT(ConvArray)&VT_ARRAY) != VT_ARRAY )	AfxThrowOleDispatchException(1001,IDS_GPOLEEXEPTION1001);
	else
	{
		psa = V_ARRAY(ConvArray);
		if (SafeArrayGetDim(psa) != 1 )		AfxThrowOleDispatchException(1002,IDS_GPOLEEXEPTION1002);
		else
		try
		{
			COleSafeArray tmp(ConvArray);
			LONG lLBound,lUBound;
			unsigned long nElement;
			LONG ix;

			tmp.GetUBound(1,&lUBound);
			tmp.GetLBound(1,&lLBound);
			nElement=lUBound-lLBound+1;
			{
				SafeArrayDestroy(psa);
				try
				{
					COleSafeArray tmp2;
					tmp2.Create(VT_VARIANT,1,&nElement);
					VariantInit(ConvArray);
					VariantCopy(ConvArray,tmp2);
//					tmp.Destroy();
				}
				catch(...)
				{
					GPC.m_ErrReport.GPWriteErrorLog("CGP_TermDoc", "GPOLEConvertToSubArray 2857","");
				}
				VARIANT HUGEP *pbvar;
				SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbvar);

				psa = V_ARRAY(ConvArray);
				try
				{
					COleSafeArray tmp3;
					tmp3.CreateOneDim(VT_BSTR,2);
					tmp3.Lock();
					for(ix=lLBound; ix<=lUBound; ix++)
					{
						SafeArrayPtrOfIndex(psa,&ix,(void **)&v);
						VariantCopy(v,tmp3);
					}
					tmp3.Unlock();
//				tmp3.Destroy();
				}
				catch(...)
				{
					GPC.m_ErrReport.GPWriteErrorLog("CGP_TermDoc", "GPOLEConvertToSubArray 2878","");
				}
			}

			void *bst;
			switch(V_VT(&tmp)&0xFF)
			{
			case VT_BSTR:
				for(ix=lLBound; ix<=lUBound; ix++)
				{
					tmp.PtrOfIndex(&ix,&bst);
					SafeArrayPtrOfIndex(psa,&ix,(void **)&v);
					try
					{
						CString tmps2;
						tmps2=(*((BSTR*)bst));
						ConvertToArray(tmps2,v,Delimiter,m_VariantArrayType);
					}
					catch(...)
					{
						GPC.m_ErrReport.GPWriteErrorLog("CGP_TermDoc", "GPOLEConvertToSubArray 2893","");
					}
				}
				break;
			case VT_VARIANT:
				for(ix=lLBound; ix<=lUBound; ix++)
				{
					tmp.PtrOfIndex(&ix,&bst);
					SafeArrayPtrOfIndex(psa,&ix,(void **)&v);
					try
					{
						CString tmps2;
						ConvVariantToString(*((VARIANT *)bst),tmps2,"\x6");
						ConvertToArray(tmps2,v,Delimiter,m_VariantArrayType);
					}
					catch(...)
					{
						GPC.m_ErrReport.GPWriteErrorLog("CGP_TermDoc", "GPOLEConvertToSubArray 2920","");
					}
				}
				break;

			}
			SafeArrayUnaccessData(psa);
//			tmp.Destroy();
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("CGP_TermDoc", "GPOLEConvertToSubArray 2900","");
		}
	}

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return 0;
}

long CGP_TermDoc::GPOLEConvertToSubArrayNet(const VARIANT FAR& iConvArray, VARIANT FAR* oConvArray, LPCTSTR Delimiter)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	SAFEARRAY FAR* psa = NULL;
	SAFEARRAY FAR* outpsa = NULL;
	USES_CONVERSION;
	HRESULT hr;
	hr=NULL;

	if ((V_VT(&iConvArray)&VT_ARRAY) != VT_ARRAY )	AfxThrowOleDispatchException(1001,IDS_GPOLEEXEPTION1001);
	else
	{
		psa = V_ARRAY(&iConvArray);
		if (SafeArrayGetDim(psa) != 1 )		AfxThrowOleDispatchException(1002,IDS_GPOLEEXEPTION1002);
		else
		try
		{
			LONG lLBound,lUBound;
			unsigned long nElement;

			SafeArrayGetLBound(psa,1,&lLBound);
			SafeArrayGetUBound(psa,1,&lUBound);
			nElement=lUBound-lLBound+1;

			outpsa=SafeArrayCreateVector(VT_VARIANT,lLBound,nElement);
			VARIANT HUGEP *pbvarOut;
			SafeArrayAccessData(outpsa, (void HUGEP* FAR*)&pbvarOut);
			unsigned short ConvOn=(unsigned short)(V_VT(&iConvArray)&0xFF);
			unsigned long i ;

			if (ConvOn==VT_BSTR)
			{
				BSTR HUGEP *pbstr;

				hr = SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
				if (FAILED(hr))     AfxThrowOleDispatchException(1003,IDS_GPOLEEXEPTION1003);
				for(i = 0; i < nElement; i++)
				{
					CString csTmp(pbstr[i]);
					VariantInit(pbvarOut+i);
					ConvertToArray(csTmp,pbvarOut+i,Delimiter,m_VariantArrayType);
				}
				SafeArrayUnaccessData(psa);
			}
			else
			if (ConvOn==VT_VARIANT)
			{
				VARIANT HUGEP *pVar;
				hr = SafeArrayAccessData(psa, (void HUGEP* FAR*)&pVar);
				if (FAILED(hr))     AfxThrowOleDispatchException(1003,IDS_GPOLEEXEPTION1003);

				CString CStmp;

				for(i = 0; i < nElement; i++)
				{
					if ((V_VT(&pVar[i])&VT_BSTR)==VT_BSTR)
					{
						CString csTmp(pVar[i].bstrVal);
						ConvertToArray(csTmp,pbvarOut+i,Delimiter,m_VariantArrayType);
					}
					else 
						VariantCopy(pbvarOut+i,pVar+i);
				}
				SafeArrayUnaccessData(psa);
			}
			else
				for(i = 0; i < nElement; i++)
					VariantInit(pbvarOut+i);

			SafeArrayUnaccessData(outpsa);
			VariantInit(oConvArray);
			V_VT(oConvArray) = VT_ARRAY|VT_VARIANT;
			V_ARRAY(oConvArray)=outpsa;
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("CGP_TermDoc", "GPOLEConvertToSubArrayNet","");
		}
	}

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return 0;
}
long CGP_TermDoc::GPOLEConvertToSubArrayExNet(const VARIANT FAR&  ConvArrayIn, VARIANT FAR* ConvArrayOut, const VARIANT FAR& DelimiterArray)
{
	VariantCopy(ConvArrayOut,(VARIANT *)(&ConvArrayIn));
	return GPOLEConvertToSubArrayEx(ConvArrayOut, DelimiterArray);
}

long CGP_TermDoc::GPOLEConvertToSubArrayEx(VARIANT FAR* ConvArray, const VARIANT FAR& DelimiterArray)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ix=-1;
	long ret=0;
	SAFEARRAY FAR* psa = NULL;
	USES_CONVERSION;
	HRESULT hr;
	hr=NULL;
	if ((V_VT(ConvArray)&VT_ARRAY) == VT_ARRAY )
	{
		CString strdelim;
		ConvVariantToString(DelimiterArray,strdelim,"q1w2e3r4");
		COleSafeArray tmpSA(ConvArray);
		SAFEARRAYBOUND sab={0};
		long lUBound;
		psa = V_ARRAY(ConvArray);
		SafeArrayDestroy(psa);
		tmpSA.GetLBound(1,&sab.lLbound);
		tmpSA.GetUBound(1,&lUBound);
		sab.cElements=lUBound-sab.lLbound+1;
		{
			COleSafeArray tmp;
			tmp.Create(VT_VARIANT,1,&sab);
			VariantInit(ConvArray);
			VariantCopy(ConvArray,tmp);
		}

		ret=sab.cElements;
		psa = V_ARRAY(ConvArray);
		////////////////
		VARIANT HUGEP *pbvar;
		SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbvar);
		///////////
		void *v;
		VARIANT *pv;
		CString CStmp;

		if (tmpSA.vt==(VT_ARRAY|VT_VARIANT))
			for(ix=sab.lLbound; ix<=lUBound; ix++)
			{
				tmpSA.PtrOfIndex(&ix,(void **)&pv);
				if ((V_VT(pv)&VT_ARRAY) != VT_ARRAY )
				{
					ConvVariantToString(*pv,CStmp,"");
					SafeArrayPtrOfIndex(psa,&ix,(void **)&pv);
					StringToArrayEx(CStmp,pv, strdelim);
				}
				else GPOLEConvertToSubArrayEx(pv, DelimiterArray);
			}
		else
		for(ix=sab.lLbound; ix<=lUBound; ix++)
		{
			tmpSA.PtrOfIndex(&ix,&v);
			SafeArrayPtrOfIndex(psa,&ix,(void **)&pv);
			if (tmpSA.vt==(VT_ARRAY|VT_BSTR))
			{
				StringToArrayEx(CString(*((BSTR*)v)),pv, strdelim);
			}
			else
			{
				switch(tmpSA.vt&0xFF)
				{
				case VT_BSTR:	CStmp=(BSTR)v; break;
				case VT_I2: 	CStmp.Format("%d",*((short *)v));		break;
				case VT_I4:     CStmp.Format("%ld",*((long *)v));		break;
				case VT_R4:     CStmp.Format("%f",*((float *)v));		break;
				case VT_R8:     CStmp.Format("%f",*((double *)v));		break;
				case VT_CY:
					{
						_variant_t var2(*((CY *)v));
						var2.ChangeType(VT_BSTR);
						CStmp=(LPCWSTR)var2.bstrVal;
					}
					break;
				case VT_DATE:
					{
						_variant_t var2(*((DATE *)v));
						var2.ChangeType(VT_BSTR);
						CStmp=(LPCWSTR)var2.bstrVal;
					}
					break;
				case VT_ERROR:
					{
						_variant_t var2(*((SCODE *)v));
						var2.ChangeType(VT_BSTR);
						CStmp=(LPCWSTR)var2.bstrVal;
					}
					break;
				case VT_BOOL:
					{
						_variant_t var2(*((VARIANT_BOOL *)v));
						var2.ChangeType(VT_BSTR);
						CStmp=(LPCWSTR)var2.bstrVal;
					}
					break;
				case VT_UI1:      CStmp.Format("%d",*((unsigned char *)v));		break;
				case VT_EMPTY: CStmp=""; break;
				default: 	AfxThrowOleDispatchException(1007,IDS_GPOLEEXEPTION1007);
					break;
				}
				StringToArrayEx(CStmp,pv, strdelim);
			}

		}
		////////////
		SafeArrayUnaccessData(psa);
		/////////////
	}

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}


long CGP_TermDoc::GPOLEStringToArrayEx(LPCTSTR iString, VARIANT FAR* oArray, const VARIANT FAR& DelimitersArray)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	CString strdelim;
	ConvVariantToString(DelimitersArray,strdelim,"q1w2e3r4");
	StringToArrayEx(iString,oArray, strdelim);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return 0;
}

void CGP_TermDoc::GPOleExecSubEx(LPCTSTR SubName, const VARIANT FAR& ParamArray)
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ExecSubEx'","");
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ExecSubEx' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ExecSubEx' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ExecSubEx'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ExecSubEx'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartSUB();
	SAFEARRAY FAR* psa = NULL;
	USES_CONVERSION;
	HRESULT hr;
	CString oStr;
	int nParam=0;

	const VARIANT *iArray=&ParamArray;
	if (V_VT(iArray)==(VT_VARIANT|VT_BYREF))	iArray=ParamArray.pvarVal;


	if ((V_VT(iArray)&VT_ARRAY) != VT_ARRAY )
	{
		ConvVariantToString(ParamArray,oStr,"\x7F");
		if (oStr.GetLength()>0) nParam=1;
	}
	else
	{
		psa = V_ARRAY(iArray);
		// Check dimensions of the array.
		if (SafeArrayGetDim(psa) != 1)				AfxThrowOleDispatchException(1002,IDS_GPOLEEXEPTION1002);
		else
		{
			LONG lLBound, lUBound;
			hr = SafeArrayGetLBound(psa, 1, &lLBound);
			if (FAILED(hr))		AfxThrowOleDispatchException(1003,IDS_GPOLEEXEPTION1003);
			else
			{
				hr = SafeArrayGetUBound(psa, 1, &lUBound);
				if (FAILED(hr))		AfxThrowOleDispatchException(1004,IDS_GPOLEEXEPTION1004);
				else
				{
					char *strdelim="\x06q1w2e3r4\x7Fq1w2e3r4\x01q1w2e3r4\x02q1w2e3r4\x03q1w2e3r4\x04q1w2e3r4\x05";
					nParam=lUBound-lLBound+1;
					ArrayToStringEx(iArray,oStr,strdelim);
				}
			}
		}
	}

	oStr.Replace("\x0A","");
	oStr.Replace("\x0D","\x7F");
	oStr.Replace("\x06","\x0D");

	m_waitCountSUB=GPC.m_OLESETTINGS.m_CSUB;

	char str[150];
	sprintf(str,"%sSUBEX%c%s%c%d",m_D3OlePrefix,0xFE,SubName,0xFE,nParam);
	GPC.WaitFor_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);
	GPC.m_WaitSUB=TRUE;
	GPC.m_WaitEndSUB=TRUE;
	GPC.ClearOUTSUB();
	GPC.ClearOUTTCL();

	AnsiToDosMB((LPCTSTR)oStr,oStr,1);
	m_Comm.GPSendLine((LPCTSTR)oStr);
	m_Comm.GPSendBlock("\r",1);
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

long CGP_TermDoc::GPOLEArrayToStringEx(const VARIANT FAR& iArray, BSTR FAR* oString, const VARIANT FAR& DelimArray)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	CString strdelim;
	ConvVariantToString(DelimArray,strdelim,"q1w2e3r4");

	CString oStr;
	long ret=ArrayToStringEx(iArray.pvarVal,oStr,strdelim);
	if (ret>=0) oStr.SetSysString(oString);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

void CGP_TermDoc::GPOLEExecTCLEx(const VARIANT FAR& TCLLineArray)
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ExecTCLEx'","");
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ExecTCLEx' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ExecTCLEx' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ExecTCLEx'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ExecTCLEx'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartTCL();
	SAFEARRAY FAR* psa = NULL;
	USES_CONVERSION;
	HRESULT hr;
	CString oStr;
	int nParam=0;

	const VARIANT *iArray=&TCLLineArray;
	if (V_VT(iArray)==(VT_VARIANT|VT_BYREF))	iArray=TCLLineArray.pvarVal;

	if ((V_VT(iArray)&VT_ARRAY) != VT_ARRAY )
	{
		ConvVariantToString(TCLLineArray,oStr,"\x7F");
		if (oStr.GetLength()>0) nParam=1;
	}
	else
	{
		psa = V_ARRAY(iArray);
		// Check dimensions of the array.
		if (SafeArrayGetDim(psa) != 1)				AfxThrowOleDispatchException(1002,IDS_GPOLEEXEPTION1002);
		else
		{
			LONG lLBound, lUBound;
			hr = SafeArrayGetLBound(psa, 1, &lLBound);
			if (FAILED(hr))		AfxThrowOleDispatchException(1003,IDS_GPOLEEXEPTION1003);
			else
			{
				hr = SafeArrayGetUBound(psa, 1, &lUBound);
				if (FAILED(hr))		AfxThrowOleDispatchException(1004,IDS_GPOLEEXEPTION1004);
				else
				{
					char *strdelim="\x0Dq1w2e3r4\x7Fq1w2e3r4\x01q1w2e3r4\x02q1w2e3r4\x03q1w2e3r4\x04q1w2e3r4\x05";
					nParam=lUBound-lLBound+1;
					ArrayToStringEx(iArray,oStr,strdelim);
				}
			}
		}
	}


	GPC.m_View->m_TCLvisible=TRUE;
	GPC.ClearOUTTCL();
	GPC.ClearOUTSUB();
	m_waitCountTCL=GPC.m_OLESETTINGS.m_CTCL;

	char str[50];
	sprintf(str,"%sTCLEX%c%d",m_D3OlePrefix,0xFE,nParam);
	GPC.WaitFor_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);

	GPC.m_WaitTCL=TRUE;
	GPC.m_WaitEndTCL=TRUE;
	AnsiToDosMB((LPCTSTR)oStr,oStr,1);
	m_Comm.GPSendLine((LPCTSTR)oStr);
	m_Comm.GPSendBlock("\r",1);
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

void CGP_TermDoc::GPOLEExecTCLCapEx(const VARIANT FAR& TCLLineArray)
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ExecTCLCapEx'","");
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ExecTCLCapEx' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ExecTCLCapEx' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ExecTCLCapEx'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ExecTCLCapEx'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartTCL();
	SAFEARRAY FAR* psa = NULL;
	USES_CONVERSION;
	HRESULT hr;
	CString oStr;
	int nParam=0;

	const VARIANT *iArray=&TCLLineArray;
	if (V_VT(iArray)==(VT_VARIANT|VT_BYREF))	iArray=TCLLineArray.pvarVal;


	if ((V_VT(iArray)&VT_ARRAY) != VT_ARRAY )
	{
		ConvVariantToString(TCLLineArray,oStr,"\x7F");
		if (oStr.GetLength()>0) nParam=1;
	}
	else
	{
		psa = V_ARRAY(iArray);
		// Check dimensions of the array.
		if (SafeArrayGetDim(psa) != 1)				AfxThrowOleDispatchException(1002,IDS_GPOLEEXEPTION1002);
		else
		{
			LONG lLBound, lUBound;
			hr = SafeArrayGetLBound(psa, 1, &lLBound);
			if (FAILED(hr))		AfxThrowOleDispatchException(1003,IDS_GPOLEEXEPTION1003);
			else
			{
				hr = SafeArrayGetUBound(psa, 1, &lUBound);
				if (FAILED(hr))		AfxThrowOleDispatchException(1004,IDS_GPOLEEXEPTION1004);
				else
				{
					char *strdelim="\x0Dq1w2e3r4\x7Fq1w2e3r4\x01q1w2e3r4\x02q1w2e3r4\x03q1w2e3r4\x04q1w2e3r4\x05";
					nParam=lUBound-lLBound+1;
					ArrayToStringEx(iArray,oStr,strdelim);
				}
			}
		}
	}


	GPC.m_View->m_TCLvisible=FALSE;
	GPC.ClearOUTTCL();
	GPC.ClearOUTSUB();
	m_waitCountTCL=GPC.m_OLESETTINGS.m_CTCL;
	GPC.m_WaitTCL=TRUE;
	GPC.m_WaitEndTCL=TRUE;

	char str[50];
	GPC.WaitFor_m_MuteProc();
	sprintf(str,"%sTCLCAPEX%c%d",m_D3OlePrefix,0xFE,nParam);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);

	AnsiToDosMB((LPCTSTR)oStr,oStr,1);
	m_Comm.GPSendLine((LPCTSTR)oStr);
	m_Comm.GPSendBlock("\r",1);
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

OLE_HANDLE CGP_TermDoc::GetHWND()
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return (OLE_HANDLE)AfxGetMainWnd()->m_hWnd;
}

OLE_HANDLE CGP_TermDoc::GetHWNDview()
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return (OLE_HANDLE)GPC.m_hViewWnd;
}

void CGP_TermDoc::GPOLESetWindowStyle(OLE_HANDLE ihWnd, const VARIANT FAR& RemStyle, const VARIANT FAR& AddStyle, const VARIANT FAR& nFlags)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
const UINT nstlarr[22]={
	N_WND_STYLES,N_DLG_STYLES,N_COMCTRL_STYLES,N_WINDOWPOS_STYLES,N_LISTCTRL_STYLES,N_ANIMATION_STYLES,
	N_PROGRESS_STYLES,N_SCROLL_STYLES,N_COMBOBOX_STYLES,N_LISTBOX_STYLES,N_BUTTON_STYLES,
	N_EDIT_STYLES,N_STATIC_STYLES,N_DATETIME_STYLES,N_MONTHCAL_STYLES,N_SPIN_STYLES,N_TAB_STYLES,
	N_SLIDER_STYLES,N_HEADER_STYLES,N_TREECTRL_STYLES,N_RTF_STYLES,N_COMBOBOXEX_STYLES,};

const char **nmstlarr[22]={
	aWndStyleName,aDlgStyleName,aComCtrlStyleName,aWindowPosStyleName,aListCtrlStyleName,aAnimationStyleName,
	aProgressStyleName,aScrollStyleName,aComboBoxStyleName,aListBoxStyleName,aButtonStyleName,
	aEditStyleName,aStaticStyleName,aDateTimeStyleName,aMonthCalStyleName,aSpinStyleName,aTabStyleName,
	aSliderStyleName,aHeaderStyleName,aTreeCtrlStyleName,aRTFStyleName,aComboBoxExStyleName,};

const UINT *UIstlarr[22]={
	aWndStyleUINT,aDlgStyleUINT,aComCtrlStyleUINT,aWindowPosStyleUINT,aListCtrlStyleUINT,aAnimationStyleUINT,
	aProgressStyleUINT,aScrollStyleUINT,aComboBoxStyleUINT,aListBoxStyleUINT,aButtonStyleUINT,
	aEditStyleUINT,aStaticStyleUINT,aDateTimeStyleUINT,aMonthCalStyleUINT,aSpinStyleUINT,aTabStyleUINT,
	aSliderStyleUINT,aHeaderStyleUINT,aTreeCtrlStyleUINT,aRTFStyleUINT,aComboBoxExStyleUINT,};

char *prefix[22]={
	"","","","","LVS","ACS",
	"PBS","SBS","CBS","LBS","BS",
	"ES","SS","DTS","MCS","UDS","TCS",
	"TBS","HDS","TVS","ES","CBS",};

	UINT StyleAdd=0,StyleDel=0,PosFlg=0;
	CString delim="|";
	UINT i,j;

	if ((V_VT(&RemStyle)&VT_BSTR)==VT_BSTR)
	{
		CString tmpstr,tmp;
		ConvVariantToString(RemStyle,tmpstr,delim);
		for(i=0;i<21;i++)
			for(j=0;j<nstlarr[i];j++)
				if (tmpstr.Find(nmstlarr[i][j])>=0)
				{
					tmp=prefix[i];
					tmp+=nmstlarr[i][j];
					if (tmpstr.Find(tmp)>=0) StyleDel|=UIstlarr[i][j];
				}
	}
	else StyleDel=RemStyle.lVal;

	if ((V_VT(&AddStyle)&VT_BSTR)==VT_BSTR)
	{
		CString tmpstr,tmp;
		ConvVariantToString(AddStyle,tmpstr,delim);
		for(i=0;i<21;i++)
			for(j=0;j<nstlarr[i];j++)
				if (tmpstr.Find(nmstlarr[i][j])>=0)
				{
					tmp=prefix[i];
					tmp+=nmstlarr[i][j];
					if (tmpstr.Find(tmp)>=0) StyleAdd|=UIstlarr[i][j];
				}
	}
	else StyleAdd=AddStyle.lVal;


	if ((V_VT(&nFlags)&VT_BSTR)==VT_BSTR)
	{
		CString tmpstr,tmp;
		ConvVariantToString(nFlags,tmpstr,delim);
		for(j=0;j<nstlarr[3];j++)
			if (tmpstr.Find(nmstlarr[3][j])>=0)
			{
				tmp=prefix[3];
				tmp+=nmstlarr[3][j];
				if (tmpstr.Find(tmp)>=0) PosFlg|=UIstlarr[3][j];
			}
	}
	else PosFlg=nFlags.lVal;

	::SetWindowLong((HWND)ihWnd,GWL_STYLE,(::GetWindowLong((HWND)ihWnd,GWL_STYLE)&(0xFFFFFFFF^StyleDel))|StyleAdd);

//		ModifyStyle(StyleDel,,PosFlg);
	CWnd::FromHandle((HWND)ihWnd)->Invalidate();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

void CGP_TermDoc::GPOLESetWindowStyleEx(OLE_HANDLE ihWnd, const VARIANT FAR& RemStyle, const VARIANT FAR& AddStyle, const VARIANT FAR& nFlags)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	const UINT nstlarr[4]={	N_WND_EX_STYLES,N_TAB_EX_STYLES,N_LISTCTRL_EX_STYLES,N_COMBOBOXEX_EX_STYLES,};
	const char **nmstlarr[4]={aWndExStyleName,aTabExStyleName,aListCtrlExStyleName,aComboBoxExExStyleName,};
	const UINT *UIstlarr[4]={aWndExStyleUINT,aTabExStyleUINT,aListCtrlExStyleUINT,aComboBoxExExStyleUINT,};
	char *prefix[4]={"","TCS","LVS","CBES",};

	UINT StyleAdd=0,StyleDel=0,PosFlg=0;
	CString delim="|";
	UINT i,j;

	if ((V_VT(&RemStyle)&VT_BSTR)==VT_BSTR)
	{
		CString tmpstr,tmp;
		ConvVariantToString(RemStyle,tmpstr,delim);
		for(i=0;i<4;i++)
			for(j=0;j<nstlarr[i];j++)
				if (tmpstr.Find(nmstlarr[i][j])>=0)
				{
					tmp=prefix[i];
					tmp+=nmstlarr[i][j];
					if (tmpstr.Find(tmp)>=0) StyleDel|=UIstlarr[i][j];
				}
	}
	else StyleDel=RemStyle.lVal;

	if ((V_VT(&AddStyle)&VT_BSTR)==VT_BSTR)
	{
		CString tmpstr,tmp;
		ConvVariantToString(AddStyle,tmpstr,delim);
		for(i=0;i<4;i++)
			for(j=0;j<nstlarr[i];j++)
				if (tmpstr.Find(nmstlarr[i][j])>=0)
				{
					tmp=prefix[i];
					tmp+=nmstlarr[i][j];
					if (tmpstr.Find(tmp)>=0) StyleAdd|=UIstlarr[i][j];
				}
	}
	else StyleAdd=AddStyle.lVal;


	if ((V_VT(&nFlags)&VT_BSTR)==VT_BSTR)
	{
		CString tmpstr,tmp;
		ConvVariantToString(nFlags,tmpstr,delim);
		for(j=0;j<nstlarr[3];j++)
			if (tmpstr.Find(nmstlarr[3][j])>=0)
			{
				tmp=prefix[3];
				tmp+=nmstlarr[3][j];
				if (tmpstr.Find(tmp)>=0) PosFlg|=UIstlarr[3][j];
			}
	}
	else PosFlg=nFlags.lVal;

	::SetWindowLong((HWND)ihWnd,GWL_EXSTYLE,(::GetWindowLong((HWND)ihWnd,GWL_EXSTYLE)&(0xFFFFFFFF^StyleDel))|StyleAdd);
//	CWnd::FromHandle((HWND)ihWnd)->ModifyStyleEx(StyleDel,StyleAdd,PosFlg);
	CWnd::FromHandle((HWND)ihWnd)->Invalidate();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}


void CGP_TermDoc::GPOLEReleaseLockedItems(long FileHandler, const VARIANT FAR& Items)
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ReleaseLockedItems'","");
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReleaseLockedItems' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReleaseLockedItems' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ReleaseLockedItems'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ReleaseLockedItems'","");

	if (FileHandler<=0)
	{
		char tmps[10];
		sprintf(tmps,"%d",FileHandler);
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Bad file handler in 'ReleaseLockedItems'",tmps);
	}

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	CString Keys("");
	ConvVariantToString(Items, Keys, "\x7F");

	AnsiToDosMB((LPCTSTR)Keys,Keys,0);
	char str[150];
	sprintf(str,"%sRELEASE%c%d",m_D3OlePrefix,0xFE,FileHandler);

	GPC.WaitFor_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);
	if (Keys.GetLength()>0)
	{
		if ((Keys.GetLength()%30000)==0 && Keys.GetLength()!=0)	Keys+=BLOCK_STR;
		m_Comm.GPSendBlock((LPCTSTR)Keys,Keys.GetLength());
		m_Comm.GPSendBlock("\r",1);
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

void CGP_TermDoc::GPOLEReleaseLockedFile(long FileHandler)
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ReleaseLockedFile'","");
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReleaseLockedFile' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReleaseLockedFile' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ReleaseLockedFile'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ReleaseLockedFile'","");

	if (FileHandler<=0)
	{
		char tmps[10];
		sprintf(tmps,"%d",FileHandler);
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Bad file handler in 'ReleaseLockedFile'",tmps);
	}

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	char str[150];
	sprintf(str,"%sRELEASE%c%d",m_D3OlePrefix,0xFE,FileHandler);
	GPC.WaitFor_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);
	m_Comm.GPSendBlock("\r",1);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

void CGP_TermDoc::GPOLEReleaseLocks()
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ReleaseLocks'","");
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReleaseLocks' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReleaseLocks' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ReleaseLocks'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ReleaseLocks'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	char str[150];
	sprintf(str,"%sRELEASE%c-1",m_D3OlePrefix,0xFE);
	GPC.WaitFor_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);
	m_Comm.GPSendBlock("\r",1);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}


void CGP_TermDoc::GPOLEDumpStart()
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	m_Comm.GPStartDump();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

long CGP_TermDoc::GPOLEDumpStop(VARIANT FAR* RetArray)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	m_Comm.GPStopDump();
	FILE *tmp;
	DWORD nstr=0;
	VariantInit(RetArray);
	if ((tmp=fopen("Dump.log","rt"))!=NULL)
	{
		char str[250];
		CString tmpstr;
		while(fgets(str,240,tmp)!=NULL) nstr++;
		COleSafeArray sa;
		sa.Create(VT_BSTR,1,&nstr);
		sa.Lock();
		rewind(tmp);
		BSTR *bst;
		DWORD i;
		for(i=0;i<nstr;i++)
		{
			fgets(str,240,tmp);
			tmpstr=str;
			sa.PtrOfIndex(((long *)&i),((void **)&bst));
			tmpstr.SetSysString(bst);
		}
		fclose(tmp);
		VariantCopy(RetArray,sa);
		sa.Unlock();
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return nstr;
}

void CGP_TermDoc::GPOLEIConv(LPCTSTR iString, LPCTSTR iFormat, BSTR FAR* oString)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	GPOLEOConvIConv('I', iString, iFormat, oString);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

void CGP_TermDoc::GPOLEOConv(LPCTSTR iString, LPCTSTR iFormat, BSTR FAR* oString)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	GPOLEOConvIConv('O', iString, iFormat, oString);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

void CGP_TermDoc::GPOLEOConvIConv(UINT Type, LPCTSTR iString, LPCTSTR iFormat, BSTR *oString)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	CString CSiFormat(iFormat);
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'OConvIConv'",CSiFormat);
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'OConvIConv' when executing TCL",CSiFormat);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'OConvIConv' when executing SUB",CSiFormat);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'OConvIConv'",CSiFormat);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call ''OConvIConv",CSiFormat);

	AnsiToDosMB((LPCTSTR)CSiFormat,CSiFormat,1);
	char str[1000];
	sprintf(str,"%s%cCONV%c%s",m_D3OlePrefix,Type,0xFE,(LPCTSTR)CSiFormat);

	GPC.WaitFor_m_MuteProc();
	LastResult=-123456;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);
	CSiFormat=iString;
	AnsiToDosMB((LPCTSTR)CSiFormat,CSiFormat,1);
	if ((CSiFormat.GetLength()%30000)==0 && CSiFormat.GetLength()!=0) CSiFormat+=BLOCK_STR;
	m_Comm.GPSendBlock((LPCTSTR)CSiFormat,CSiFormat.GetLength());
	m_Comm.GPSendBlock("\r",1);

	int i;
	for(i=0;i<m_waitCountFOther;i++)
	{
		if (GPC.m_View->DoAdditionalMessageLoop()<0) {GPC.Release_m_MuteProc(); return ;}
		GPC.m_View->DoRemappingInput();
		if (LastResult==-123456) Sleep(m_waitTimeFOther);
		else break;
	}
	if (i>=m_waitCountFOther)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'OConvIConv'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();

	if (LastResult!=-123456)
	{
		DosToAnsi(GPC.m_View->InputBuffer2);
		char *pos=strchr(GPC.m_View->InputBuffer2,'#');
		if ((pos++)==NULL) pos="";
		CString tmp(pos);
		tmp.SetSysString(oString);
	}
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

long CGP_TermDoc::GPOLEArrayDelElement(const VARIANT FAR& itmpArray, long DelIndex)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	SAFEARRAY FAR* psa = NULL;

	USES_CONVERSION;
	SAFEARRAYBOUND tmpSAB={0};
	HRESULT hr;

	const VARIANT *iArray=&itmpArray;
	if (V_VT(iArray)==(VT_VARIANT|VT_BYREF))	iArray=itmpArray.pvarVal;

	if ((V_VT(iArray)&VT_ARRAY) != VT_ARRAY )	AfxThrowOleDispatchException(1001,IDS_GPOLEEXEPTION1001);
	else
	{
		psa = V_ARRAY(iArray);
		// Check dimensions of the array.
		if (SafeArrayGetDim(psa) != 1)	AfxThrowOleDispatchException(1002,IDS_GPOLEEXEPTION1002);
		else
		{
			LONG lLBound, lUBound,i;
			hr = SafeArrayGetLBound(psa, 1, &lLBound);
			if (FAILED(hr) || DelIndex<lLBound)	AfxThrowOleDispatchException(1003,IDS_GPOLEEXEPTION1003);
			else
			{
				hr = SafeArrayGetUBound(psa, 1, &lUBound);
				if (FAILED(hr) || DelIndex>lUBound)	AfxThrowOleDispatchException(1004,IDS_GPOLEEXEPTION1004);
				else
				{
					if ((V_VT(iArray)&VT_BYREF) == VT_BYREF)
					{
						void *tmp;
						void HUGEP **pvoid;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pvoid);
						tmp=pvoid[DelIndex-lLBound];
						for(i = DelIndex; i < lUBound; i++)
							pvoid[i-lLBound]=pvoid[i-lLBound+1];

						pvoid[lUBound-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_BSTR) == VT_BSTR)
					{
						BSTR tmp;
						BSTR HUGEP *pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[DelIndex-lLBound];
						for(i = DelIndex; i < lUBound; i++)
							pbstr[i-lLBound]=pbstr[i-lLBound+1];

						pbstr[lUBound-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_UI1) == VT_UI1)
					{
						unsigned char tmp;
						unsigned char HUGEP *pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[DelIndex-lLBound];
						for(i = DelIndex; i < lUBound; i++)
							pbstr[i-lLBound]=pbstr[i-lLBound+1];

						pbstr[lUBound-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_I2) == VT_I2)
					{
						short tmp;
						short HUGEP *pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[DelIndex-lLBound];
						for(i = DelIndex; i < lUBound; i++)
							pbstr[i-lLBound]=pbstr[i-lLBound+1];

						pbstr[lUBound-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_I4) == VT_I4)
					{
						long tmp;
						long HUGEP *pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[DelIndex-lLBound];
						for(i = DelIndex; i < lUBound; i++)
							pbstr[i-lLBound]=pbstr[i-lLBound+1];

						pbstr[lUBound-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_R4) == VT_R4)
					{
						float tmp;
						float HUGEP *pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[DelIndex-lLBound];
						for(i = DelIndex; i < lUBound; i++)
							pbstr[i-lLBound]=pbstr[i-lLBound+1];

						pbstr[lUBound-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_R8) == VT_R8)
					{
						double tmp;
						double HUGEP *pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[DelIndex-lLBound];
						for(i = DelIndex; i < lUBound; i++)
							pbstr[i-lLBound]=pbstr[i-lLBound+1];

						pbstr[lUBound-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_BOOL) == VT_BOOL)
					{
						VARIANT_BOOL tmp;
						VARIANT_BOOL HUGEP *pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[DelIndex-lLBound];
						for(i = DelIndex; i < lUBound; i++)
							pbstr[i-lLBound]=pbstr[i-lLBound+1];

						pbstr[lUBound-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_ERROR) == VT_ERROR)
					{
						SCODE tmp;
						SCODE HUGEP *pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[DelIndex-lLBound];
						for(i = DelIndex; i < lUBound; i++)
							pbstr[i-lLBound]=pbstr[i-lLBound+1];

						pbstr[lUBound-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_CY) == VT_CY)
					{
						CY tmp;
						CY HUGEP *pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[DelIndex-lLBound];
						for(i = DelIndex; i < lUBound; i++)
							pbstr[i-lLBound]=pbstr[i-lLBound+1];

						pbstr[lUBound-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_DATE) == VT_DATE)
					{
						DATE tmp;
						DATE HUGEP *pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[DelIndex-lLBound];
						for(i = DelIndex; i < lUBound; i++)
							pbstr[i-lLBound]=pbstr[i-lLBound+1];

						pbstr[lUBound-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_UNKNOWN) == VT_UNKNOWN)
					{
						IUnknown *tmp;
						IUnknown HUGEP **pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[DelIndex-lLBound];
						for(i = DelIndex; i < lUBound; i++)
							pbstr[i-lLBound]=pbstr[i-lLBound+1];

						pbstr[lUBound-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_DISPATCH) == VT_DISPATCH)
					{
						IDispatch *tmp;
						IDispatch HUGEP **pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[DelIndex-lLBound];
						for(i = DelIndex; i < lUBound; i++)
							pbstr[i-lLBound]=pbstr[i-lLBound+1];

						pbstr[lUBound-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else AfxThrowOleDispatchException(1111,"UNKNOWN ERROR");
					tmpSAB.lLbound=lLBound;
					tmpSAB.cElements=lUBound-lLBound;

					SafeArrayRedim(psa,&tmpSAB);
				}
			}
		}
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return 0;
}

long CGP_TermDoc::GPOLEArrayInsElement(const VARIANT FAR& itmpArray, long InsIndex)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	SAFEARRAY FAR* psa = NULL;

	USES_CONVERSION;
	SAFEARRAYBOUND tmpSAB={0};
	HRESULT hr;

	const VARIANT *iArray=&itmpArray;
	if (V_VT(iArray)==(VT_VARIANT|VT_BYREF))	iArray=itmpArray.pvarVal;

	if ((V_VT(iArray)&VT_ARRAY) != VT_ARRAY )	AfxThrowOleDispatchException(1001,IDS_GPOLEEXEPTION1001);
	else
	{
		psa = V_ARRAY(iArray);
		// Check dimensions of the array.
		if (SafeArrayGetDim(psa) != 1)	AfxThrowOleDispatchException(1002,IDS_GPOLEEXEPTION1002);
		else
		{
			LONG lLBound, lUBound,i;
			hr = SafeArrayGetLBound(psa, 1, &lLBound);
			if (FAILED(hr) || InsIndex<lLBound)	AfxThrowOleDispatchException(1003,IDS_GPOLEEXEPTION1003);
			else
			{
				hr = SafeArrayGetUBound(psa, 1, &lUBound);
				if (FAILED(hr) || InsIndex>lUBound+1)	AfxThrowOleDispatchException(1004,IDS_GPOLEEXEPTION1004);
				else
				{
					tmpSAB.lLbound=lLBound;
					lUBound++;
					tmpSAB.cElements=lUBound-lLBound+1;
					SafeArrayRedim(psa,&tmpSAB);

					if ((V_VT(iArray)&VT_BYREF) == VT_BYREF)
					{
						void *tmp;
						void HUGEP **pvoid;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pvoid);
						tmp=pvoid[lUBound-lLBound+1];
						for(i = lUBound-lLBound+1; i > InsIndex; i--)
							pvoid[i-lLBound]=pvoid[i-lLBound-1];

						pvoid[i-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_BSTR) == VT_BSTR)
					{
						BSTR tmp;
						BSTR HUGEP *pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[lUBound-lLBound+1];
						for(i = lUBound-lLBound+1; i > InsIndex; i--)
							pbstr[i-lLBound]=pbstr[i-lLBound-1];

						pbstr[i-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_UI1) == VT_UI1)
					{
						unsigned char tmp;
						unsigned char HUGEP *pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[lUBound-lLBound+1];
						for(i = lUBound-lLBound+1; i > InsIndex; i--)
							pbstr[i-lLBound]=pbstr[i-lLBound-1];

						pbstr[i-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_I2) == VT_I2)
					{
						short tmp;
						short HUGEP *pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[lUBound-lLBound+1];
						for(i = lUBound-lLBound+1; i > InsIndex; i--)
							pbstr[i-lLBound]=pbstr[i-lLBound-1];

						pbstr[i-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_I4) == VT_I4)
					{
						long tmp;
						long HUGEP *pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[lUBound-lLBound+1];
						for(i = lUBound-lLBound+1; i > InsIndex; i--)
							pbstr[i-lLBound]=pbstr[i-lLBound-1];

						pbstr[i-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_R4) == VT_R4)
					{
						float tmp;
						float HUGEP *pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[lUBound-lLBound+1];
						for(i = lUBound-lLBound+1; i > InsIndex; i--)
							pbstr[i-lLBound]=pbstr[i-lLBound-1];

						pbstr[i-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_R8) == VT_R8)
					{
						double tmp;
						double HUGEP *pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[lUBound-lLBound+1];
						for(i = lUBound-lLBound+1; i > InsIndex; i--)
							pbstr[i-lLBound]=pbstr[i-lLBound-1];

						pbstr[i-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_BOOL) == VT_BOOL)
					{
						VARIANT_BOOL tmp;
						VARIANT_BOOL HUGEP *pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[lUBound-lLBound+1];
						for(i = lUBound-lLBound+1; i > InsIndex; i--)
							pbstr[i-lLBound]=pbstr[i-lLBound-1];

						pbstr[i-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_ERROR) == VT_ERROR)
					{
						SCODE tmp;
						SCODE HUGEP *pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[lUBound-lLBound+1];
						for(i = lUBound-lLBound+1; i > InsIndex; i--)
							pbstr[i-lLBound]=pbstr[i-lLBound-1];

						pbstr[i-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_CY) == VT_CY)
					{
						CY tmp;
						CY HUGEP *pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[lUBound-lLBound+1];
						for(i = lUBound-lLBound+1; i > InsIndex; i--)
							pbstr[i-lLBound]=pbstr[i-lLBound-1];

						pbstr[i-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_DATE) == VT_DATE)
					{
						DATE tmp;
						DATE HUGEP *pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[lUBound-lLBound+1];
						for(i = lUBound-lLBound+1; i > InsIndex; i--)
							pbstr[i-lLBound]=pbstr[i-lLBound-1];

						pbstr[i-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_UNKNOWN) == VT_UNKNOWN)
					{
						IUnknown *tmp;
						IUnknown HUGEP **pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[lUBound-lLBound+1];
						for(i = lUBound-lLBound+1; i > InsIndex; i--)
							pbstr[i-lLBound]=pbstr[i-lLBound-1];

						pbstr[i-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else
					if ((V_VT(iArray)&VT_DISPATCH) == VT_DISPATCH)
					{
						IDispatch *tmp;
						IDispatch HUGEP **pbstr;
						SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						tmp=pbstr[lUBound-lLBound+1];
						for(i = lUBound-lLBound+1; i > InsIndex; i--)
							pbstr[i-lLBound]=pbstr[i-lLBound-1];

						pbstr[i-lLBound]=tmp;
						SafeArrayUnaccessData(psa);
					}
					else AfxThrowOleDispatchException(1111,"UNKNOWN ERROR");
				}
			}
		}
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return 0;
}

VARIANT CGP_TermDoc::GetDelimArray1()
{
	return GPC.DelimArr1;
}

VARIANT CGP_TermDoc::GetDelimArray2()
{
	return GPC.DelimArr2;
}

VARIANT CGP_TermDoc::GetDelimArray3()
{
	return GPC.DelimArr3;
}

VARIANT CGP_TermDoc::GetDelimArray4()
{
	return GPC.DelimArr4;
}

long CGP_TermDoc::GetInputEnable()
{
	return GPC.TCLinProgress;
}

void CGP_TermDoc::SetInputEnable(long nNewValue)
{
	GPC.TCLinProgress=nNewValue;
}

long CGP_TermDoc::GPOLESelectOpenPickFile(LPCTSTR FileName)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	CString oStr(FileName);
	AnsiToDosMB((LPCTSTR)oStr,oStr,0);

	char str[150];
	sprintf(str,"%sPSOFILE%c%s",m_D3OlePrefix,0xFE,(LPCTSTR)oStr);
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'SelectOpenPickFile'",str);
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'SelectOpenPickFile' when executing TCL",str);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'SelectOpenPickFile' when executing SUB",str);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'SelectOpenPickFile'",str);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'SelectOpenPickFile'",str);
	GPC.WaitFor_m_MuteProc();
	LastResult=-123456;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);

	int i;
	for(i=0;i<m_waitCountFOther;i++)
	{
		if (GPC.m_View->DoAdditionalMessageLoop()<0)
		{
			GPC.Release_m_MuteProc();
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "''SelectOpenPickFile aborted","");
			return  -13;
		}
		GPC.m_View->DoRemappingInput();
		if (LastResult==-123456) Sleep(m_waitTimeFOther);
		else break;
	}
	if (i>=m_waitCountFOther)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'SelectOpenPickFile'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	GPC.Release_m_MuteProc();

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return LastResult;
}

long CGP_TermDoc::GPOLESSelectOpenPickFile(LPCTSTR FileName)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	CString oStr(FileName);
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'SSelectOpenPickFile'",oStr);
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'SSelectOpenPickFile' when executing TCL",oStr);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'SSelectOpenPickFile' when executing SUB",oStr);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'SSelectOpenPickFile'",oStr);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'SSelectOpenPickFile'",oStr);

	AnsiToDosMB((LPCTSTR)oStr,oStr,0);

	char str[150];
	sprintf(str,"%sPSSOFILE%c%s",m_D3OlePrefix,0xFE,(LPCTSTR)oStr);
	GPC.WaitFor_m_MuteProc();
	LastResult=-123456;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);

	int i;
	for(i=0;i<m_waitCountFOther;i++)
	{
		if (GPC.m_View->DoAdditionalMessageLoop()<0)
		{
			GPC.Release_m_MuteProc();
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "'SSelectOpenPickFile' aborted","");
			return  -13;
		}
		GPC.m_View->DoRemappingInput();
		if (LastResult==-123456) Sleep(m_waitTimeFOther);
		else break;
	}
	if (i>=m_waitCountFOther)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'SSelectOpenPickFile'","");
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	GPC.Release_m_MuteProc();

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return LastResult;
}

void CGP_TermDoc::GPOLESelectPickFile(LPCTSTR FileName)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	CString oStr(FileName);
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'SelectPickFile'",oStr);
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'SelectPickFile' when executing TCL",oStr);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'SelectPickFile' when executing SUB",oStr);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'SelectPickFile'",oStr);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'SelectPickFile'",oStr);

	AnsiToDosMB((LPCTSTR)oStr,oStr,0);

	char str[150];
	sprintf(str,"%sPSFILE%c%s",m_D3OlePrefix,0xFE,(LPCTSTR)oStr);
	GPC.WaitFor_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

void CGP_TermDoc::GPOLESSelectPickFile(LPCTSTR FileName)
{
	CString oStr(FileName);
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'SSelectPickFile'",FileName);
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'SSelectPickFile' when executing TCL",FileName);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'SSelectPickFile' when executing SUB",FileName);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'SSelectPickFile'",FileName);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'SSelectPickFile'",FileName);

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	AnsiToDosMB((LPCTSTR)oStr,oStr,0);

	char str[150];
	sprintf(str,"%sPSSFILE%c%s",m_D3OlePrefix,0xFE,(LPCTSTR)oStr);
	GPC.WaitFor_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

long CGP_TermDoc::GPOLEReadPickFile(LPCTSTR FileName, VARIANT FAR*  KeyArray, VARIANT FAR* ItemArray)
{
	CString FName(FileName);
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ReadPickFile'",FileName);
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReadPickFile' when executing TCL",FileName);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReadPickFile' when executing SUB",FileName);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ReadPickFile'",FileName);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ReadPickFile'",FileName);

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNTimesServerRead++;
	long ret=-1;
	AnsiToDosMB((LPCTSTR)FName,FName,0);
	char str[150];
	sprintf(str,"%sPRAFILE%c%s",m_D3OlePrefix,0xFE,(LPCTSTR)FName);

	GPC.WaitFor_m_MuteProc();
	LastResult=-123456;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);

	int i;
	for(i=0;i<m_waitCountFRead;i++)
	{
		if (GPC.m_View->DoAdditionalMessageLoop()<0)
		{
			GPC.Release_m_MuteProc();
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "'ReadPickFile' aborted","");
			return  -13;
		}
		GPC.m_View->DoRemappingInput();
		if (LastResult==-123456) Sleep(m_waitTimeFRead);
		else break;
	}
	if (i>=m_waitCountFRead)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'ReadPickFile'","");
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();

	if (LastResult!=-123456)
	{
		DosToAnsi(GPC.m_View->InputBuffer2);
		CString delim("\x7F");
		char *pos=strchr(GPC.m_View->InputBuffer2,'#');
		char *poskey=NULL;
		if (pos!=NULL)
		{
			pos++;
			poskey=strchr(pos,0x05);
			if (poskey!=NULL) *(poskey++)=0;
			ret=ConvertToArray(CString(pos),ItemArray,delim,m_VariantArrayType);
			if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNItemsServerRead+=ret;
			ConvertToArray(CString(poskey),KeyArray,delim,m_VariantArrayType);
		}
		else ret=-4;

		long tmp=atoi(GPC.m_View->InputBuffer2);
		if (tmp<0) ret=tmp;
	}
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

void CGP_TermDoc::GPOLESortArrayNet(const VARIANT FAR& iArrayIn, VARIANT FAR* iArrayOut, long Flags)
{
	VariantCopy(iArrayOut,(VARIANT *)(&iArrayIn));
	GPOLESortArray(iArrayOut, Flags);
}
void CGP_TermDoc::GPOLESortArray(VARIANT FAR* inArray, long Flags)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	SAFEARRAY FAR* psa = NULL;

	USES_CONVERSION;
	HRESULT hr;

	const VARIANT *iArray=inArray;

	if (V_VT(iArray)==(VT_VARIANT|VT_BYREF))	iArray=inArray->pvarVal;

	if ((V_VT(iArray)&VT_ARRAY) != VT_ARRAY )	AfxThrowOleDispatchException(1001,IDS_GPOLEEXEPTION1001);
	else
	{
		psa = V_ARRAY(iArray);
		if (SafeArrayGetDim(psa) != 1)	AfxThrowOleDispatchException(1002,IDS_GPOLEEXEPTION1002);
		else
		{
			LONG lLBound, lUBound;
			SafeArrayGetLBound(psa, 1, &lLBound);
			hr = SafeArrayGetUBound(psa, 1, &lUBound);
			if (FAILED(hr))	AfxThrowOleDispatchException(1003,IDS_GPOLEEXEPTION1003);
			else
			{
				if ((V_VT(iArray)&VT_VARIANT) == VT_VARIANT)
				{
					VARIANT HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					if ((Flags&2)==2) qsVARIANTI(pbstr,0,lUBound);
					else qsVARIANT(pbstr,0,lUBound);
					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_BSTR) == VT_BSTR)
				{
					BSTR HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					if ((Flags&2)==2) qsBSTRILine(pbstr,0,lUBound);
					else qsBSTRLine(pbstr,0,lUBound);
					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_UI1) == VT_UI1)
				{
					unsigned char HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					GP_quick(pbstr,lUBound);
					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_I2) == VT_I2)
				{
					short HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					GP_quick(pbstr,lUBound);
					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_I4) == VT_I4)
				{
					long HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					GP_quick(pbstr,lUBound);
					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_R4) == VT_R4)
				{
					float HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					GP_quick(pbstr,lUBound);
					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_R8) == VT_R8)
				{
					double HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					GP_quick(pbstr,lUBound);
					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_BOOL) == VT_BOOL)
				{
					VARIANT_BOOL HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					GP_quick(pbstr,lUBound);
					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_ERROR) == VT_ERROR)
				{
					SCODE HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					GP_quick(pbstr,lUBound);
					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_CY) == VT_CY)
				{
					LONGLONG HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					GP_quick(pbstr,lUBound);
					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_DATE) == VT_DATE)
				{
					DATE HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					GP_quick(pbstr,lUBound);
					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_UNKNOWN) == VT_UNKNOWN)
				{
					IUnknown HUGEP **pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					GP_quick(pbstr,lUBound);
					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_DISPATCH) == VT_DISPATCH)
				{
					IDispatch HUGEP **pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					GP_quick(pbstr,lUBound);
					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else AfxThrowOleDispatchException(1111,"UNKNOWN ERROR");
			}
		}
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

void CGP_TermDoc::GPOLESortArray2Net(const VARIANT FAR& iArrayMasterIn, VARIANT FAR* iArrayMasterOut, const VARIANT FAR& iArraySlaveIn, VARIANT FAR* iArraySlaveOut, long Flags)
{
	VariantCopy(iArrayMasterOut,(VARIANT *)(&iArrayMasterIn));
	VariantCopy(iArraySlaveOut,(VARIANT *)(&iArraySlaveIn));
	GPOLESortArray2(iArrayMasterOut, iArraySlaveOut, Flags);
}

void CGP_TermDoc::GPOLESortArray2(VARIANT FAR* iArrayMaster, VARIANT FAR* iArraySlave, long Flags)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	SAFEARRAY FAR* psa = NULL;
	SAFEARRAY FAR* psa2 = NULL;

	USES_CONVERSION;
	HRESULT hr;

	const VARIANT *iArray=iArrayMaster;
	const VARIANT *iArray2=iArraySlave;

	if (V_VT(iArray)==(VT_VARIANT|VT_BYREF))	iArray=iArrayMaster->pvarVal;
	if (V_VT(iArray2)==(VT_VARIANT|VT_BYREF))	iArray2=iArraySlave->pvarVal;

	if ((V_VT(iArray)&VT_ARRAY) != VT_ARRAY || (V_VT(iArray2)&VT_ARRAY) != VT_ARRAY)
		AfxThrowOleDispatchException(1001,IDS_GPOLEEXEPTION1001);
	else
	{
		psa = V_ARRAY(iArray);
		psa2 = V_ARRAY(iArray2);
		if (SafeArrayGetDim(psa) != 1 || SafeArrayGetDim(psa2) != 1)	AfxThrowOleDispatchException(1002,IDS_GPOLEEXEPTION1002);
		else
		{
			LONG lLBound, lUBound;
			SafeArrayGetLBound(psa, 1, &lLBound);
			SafeArrayGetUBound(psa, 1, &lUBound);
			LONG lLBound2, lUBound2;
			SafeArrayGetLBound(psa2, 1, &lLBound2);
			hr = SafeArrayGetUBound(psa2, 1, &lUBound2);
			if (FAILED(hr))	AfxThrowOleDispatchException(1003,IDS_GPOLEEXEPTION1003);
			else
			{
#ifdef RUS
				if (lUBound>lUBound2)	AfxThrowOleDispatchException(1022,"Размерности массивов не совпадают");
#else
				if (lUBound>lUBound2)	AfxThrowOleDispatchException(1022,"Dimension of Arrays is not equ");
#endif
				void HUGEP* FAR ptr2;
				SafeArrayAccessData(psa2,&ptr2);

				if ((V_VT(iArray)&VT_VARIANT) == VT_VARIANT)
				{
					VARIANT HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					switch(V_VT(iArray2)&0xFF)
					{
					case VT_VARIANT:
						if ((Flags&2)==2) qs2VARIANTI(pbstr,(VARIANT HUGEP *)ptr2,0,lUBound);
						else qs2VARIANT(pbstr,(VARIANT HUGEP *)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BSTR:
						if ((Flags&2)==2) qs2VARIANTI(pbstr,(BSTR HUGEP *)ptr2,0,lUBound);
						else qs2VARIANT(pbstr,(BSTR HUGEP *)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((BSTR HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UI1:
						if ((Flags&2)==2) qs2VARIANTI(pbstr,(unsigned char HUGEP *)ptr2,0,lUBound);
						else qs2VARIANT(pbstr,(unsigned char HUGEP *)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((unsigned char HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I2:
						if ((Flags&2)==2) qs2VARIANTI(pbstr,(short HUGEP *)ptr2,0,lUBound);
						else qs2VARIANT(pbstr,(short HUGEP *)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((short HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I4:
						if ((Flags&2)==2) qs2VARIANTI(pbstr,(long HUGEP *)ptr2,0,lUBound);
						else qs2VARIANT(pbstr,(long HUGEP *)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((long HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R4:
						if ((Flags&2)==2) qs2VARIANTI(pbstr,(float HUGEP *)ptr2,0,lUBound);
						else qs2VARIANT(pbstr,(float HUGEP *)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((float HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R8:
						if ((Flags&2)==2) qs2VARIANTI(pbstr,(double HUGEP *)ptr2,0,lUBound);
						else qs2VARIANT(pbstr,(double HUGEP *)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((double HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BOOL:
						if ((Flags&2)==2) qs2VARIANTI(pbstr,(VARIANT_BOOL HUGEP *)ptr2,0,lUBound);
						else qs2VARIANT(pbstr,(VARIANT_BOOL HUGEP *)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT_BOOL HUGEP *)ptr2,lUBound+1);
						break;
					case VT_CY:
						if ((Flags&2)==2) qs2VARIANTI(pbstr,(LONGLONG HUGEP *)ptr2,0,lUBound);
						else qs2VARIANT(pbstr,(LONGLONG HUGEP *)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((LONGLONG HUGEP *)ptr2,lUBound+1);
						break;
					case VT_DATE:
						if ((Flags&2)==2) qs2VARIANTI(pbstr,(DATE HUGEP *)ptr2,0,lUBound);
						else qs2VARIANT(pbstr,(DATE HUGEP *)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((DATE HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UNKNOWN:
						if ((Flags&2)==2) qs2VARIANTI(pbstr,(IUnknown HUGEP **)ptr2,0,lUBound);
						else qs2VARIANT(pbstr,(IUnknown HUGEP **)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((IUnknown HUGEP **)ptr2,lUBound+1);
						break;
					case VT_DISPATCH:
						if ((Flags&2)==2) qs2VARIANTI(pbstr,(IDispatch HUGEP **)ptr2,0,lUBound);
						else qs2VARIANT(pbstr,(IDispatch HUGEP **)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((IDispatch HUGEP **)ptr2,lUBound+1);
						break;
					}

					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_BSTR) == VT_BSTR)
				{
					BSTR HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					switch(V_VT(iArray2)&0xFF)
					{
					case VT_VARIANT:
						if ((Flags&2)==2) qs2IBSTR(pbstr,(VARIANT HUGEP *)ptr2,0,lUBound);
						else qs2BSTR(pbstr,(VARIANT HUGEP *)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BSTR:
						if ((Flags&2)==2) qs2IBSTR(pbstr,(BSTR HUGEP *)ptr2,0,lUBound);
						else qs2BSTR(pbstr,(BSTR HUGEP *)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((BSTR HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UI1:
						if ((Flags&2)==2) qs2IBSTR(pbstr,(unsigned char HUGEP *)ptr2,0,lUBound);
						else qs2BSTR(pbstr,(unsigned char HUGEP *)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((unsigned char HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I2:
						if ((Flags&2)==2) qs2IBSTR(pbstr,(short HUGEP *)ptr2,0,lUBound);
						else qs2BSTR(pbstr,(short HUGEP *)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((short HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I4:
						if ((Flags&2)==2) qs2IBSTR(pbstr,(long HUGEP *)ptr2,0,lUBound);
						else qs2BSTR(pbstr,(long HUGEP *)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((long HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R4:
						if ((Flags&2)==2) qs2IBSTR(pbstr,(float HUGEP *)ptr2,0,lUBound);
						else qs2BSTR(pbstr,(float HUGEP *)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((float HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R8:
						if ((Flags&2)==2) qs2IBSTR(pbstr,(double HUGEP *)ptr2,0,lUBound);
						else qs2BSTR(pbstr,(double HUGEP *)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((double HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BOOL:
						if ((Flags&2)==2) qs2IBSTR(pbstr,(VARIANT_BOOL HUGEP *)ptr2,0,lUBound);
						else qs2BSTR(pbstr,(VARIANT_BOOL HUGEP *)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT_BOOL HUGEP *)ptr2,lUBound+1);
						break;
					case VT_CY:
						if ((Flags&2)==2) qs2IBSTR(pbstr,(LONGLONG HUGEP *)ptr2,0,lUBound);
						else qs2BSTR(pbstr,(LONGLONG HUGEP *)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((LONGLONG HUGEP *)ptr2,lUBound+1);
						break;
					case VT_DATE:
						if ((Flags&2)==2) qs2IBSTR(pbstr,(DATE HUGEP *)ptr2,0,lUBound);
						else qs2BSTR(pbstr,(DATE HUGEP *)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((DATE HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UNKNOWN:
						if ((Flags&2)==2) qs2IBSTR(pbstr,(IUnknown HUGEP **)ptr2,0,lUBound);
						else qs2BSTR(pbstr,(IUnknown HUGEP **)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((IUnknown HUGEP **)ptr2,lUBound+1);
						break;
					case VT_DISPATCH:
						if ((Flags&2)==2) qs2IBSTR(pbstr,(IDispatch HUGEP **)ptr2,0,lUBound);
						else qs2BSTR(pbstr,(IDispatch HUGEP **)ptr2,0,lUBound);
						if ((Flags&1)==1) GP_Reverse((IDispatch HUGEP **)ptr2,lUBound+1);
						break;
					}

					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_UI1) == VT_UI1)
				{
					unsigned char HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					switch(V_VT(iArray2)&0xFF)
					{
					case VT_VARIANT:
						GP_quick2(pbstr,(VARIANT HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BSTR:
						GP_quick2(pbstr,(BSTR HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((BSTR HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UI1:
						GP_quick2(pbstr,(unsigned char HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((unsigned char HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I2:
						GP_quick2(pbstr,(short HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((short HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I4:
						GP_quick2(pbstr,(long HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((long HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R4:
						GP_quick2(pbstr,(float HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((float HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R8:
						GP_quick2(pbstr,(double HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((double HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BOOL:
						GP_quick2(pbstr,(VARIANT_BOOL HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT_BOOL HUGEP *)ptr2,lUBound+1);
						break;
					case VT_CY:
						GP_quick2(pbstr,(LONGLONG HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((LONGLONG HUGEP *)ptr2,lUBound+1);
						break;
					case VT_DATE:
						GP_quick2(pbstr,(DATE HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((DATE HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UNKNOWN:
						GP_quick2(pbstr,(IUnknown HUGEP **)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((IUnknown HUGEP **)ptr2,lUBound+1);
						break;
					case VT_DISPATCH:
						GP_quick2(pbstr,(IDispatch HUGEP **)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((IDispatch HUGEP **)ptr2,lUBound+1);
						break;
					}
					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_I2) == VT_I2)
				{
					short HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					switch(V_VT(iArray2)&0xFF)
					{
					case VT_VARIANT:
						GP_quick2(pbstr,(VARIANT HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BSTR:
						GP_quick2(pbstr,(BSTR HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((BSTR HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UI1:
						GP_quick2(pbstr,(unsigned char HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((unsigned char HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I2:
						GP_quick2(pbstr,(short HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((short HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I4:
						GP_quick2(pbstr,(long HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((long HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R4:
						GP_quick2(pbstr,(float HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((float HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R8:
						GP_quick2(pbstr,(double HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((double HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BOOL:
						GP_quick2(pbstr,(VARIANT_BOOL HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT_BOOL HUGEP *)ptr2,lUBound+1);
						break;
					case VT_CY:
						GP_quick2(pbstr,(LONGLONG HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((LONGLONG HUGEP *)ptr2,lUBound+1);
						break;
					case VT_DATE:
						GP_quick2(pbstr,(DATE HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((DATE HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UNKNOWN:
						GP_quick2(pbstr,(IUnknown HUGEP **)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((IUnknown HUGEP **)ptr2,lUBound+1);
						break;
					case VT_DISPATCH:
						GP_quick2(pbstr,(IDispatch HUGEP **)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((IDispatch HUGEP **)ptr2,lUBound+1);
						break;
					}
					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_I4) == VT_I4)
				{
					long HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					switch(V_VT(iArray2)&0xFF)
					{
					case VT_VARIANT:
						GP_quick2(pbstr,(VARIANT HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BSTR:
						GP_quick2(pbstr,(BSTR HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((BSTR HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UI1:
						GP_quick2(pbstr,(unsigned char HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((unsigned char HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I2:
						GP_quick2(pbstr,(short HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((short HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I4:
						GP_quick2(pbstr,(long HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((long HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R4:
						GP_quick2(pbstr,(float HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((float HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R8:
						GP_quick2(pbstr,(double HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((double HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BOOL:
						GP_quick2(pbstr,(VARIANT_BOOL HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT_BOOL HUGEP *)ptr2,lUBound+1);
						break;
					case VT_CY:
						GP_quick2(pbstr,(LONGLONG HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((LONGLONG HUGEP *)ptr2,lUBound+1);
						break;
					case VT_DATE:
						GP_quick2(pbstr,(DATE HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((DATE HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UNKNOWN:
						GP_quick2(pbstr,(IUnknown HUGEP **)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((IUnknown HUGEP **)ptr2,lUBound+1);
						break;
					case VT_DISPATCH:
						GP_quick2(pbstr,(IDispatch HUGEP **)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((IDispatch HUGEP **)ptr2,lUBound+1);
						break;
					}
					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_R4) == VT_R4)
				{
					float HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					switch(V_VT(iArray2)&0xFF)
					{
					case VT_VARIANT:
						GP_quick2(pbstr,(VARIANT HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BSTR:
						GP_quick2(pbstr,(BSTR HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((BSTR HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UI1:
						GP_quick2(pbstr,(unsigned char HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((unsigned char HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I2:
						GP_quick2(pbstr,(short HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((short HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I4:
						GP_quick2(pbstr,(long HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((long HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R4:
						GP_quick2(pbstr,(float HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((float HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R8:
						GP_quick2(pbstr,(double HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((double HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BOOL:
						GP_quick2(pbstr,(VARIANT_BOOL HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT_BOOL HUGEP *)ptr2,lUBound+1);
						break;
					case VT_CY:
						GP_quick2(pbstr,(LONGLONG HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((LONGLONG HUGEP *)ptr2,lUBound+1);
						break;
					case VT_DATE:
						GP_quick2(pbstr,(DATE HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((DATE HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UNKNOWN:
						GP_quick2(pbstr,(IUnknown HUGEP **)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((IUnknown HUGEP **)ptr2,lUBound+1);
						break;
					case VT_DISPATCH:
						GP_quick2(pbstr,(IDispatch HUGEP **)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((IDispatch HUGEP **)ptr2,lUBound+1);
						break;
					}
					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_R8) == VT_R8)
				{
					double HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					switch(V_VT(iArray2)&0xFF)
					{
					case VT_VARIANT:
						GP_quick2(pbstr,(VARIANT HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BSTR:
						GP_quick2(pbstr,(BSTR HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((BSTR HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UI1:
						GP_quick2(pbstr,(unsigned char HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((unsigned char HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I2:
						GP_quick2(pbstr,(short HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((short HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I4:
						GP_quick2(pbstr,(long HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((long HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R4:
						GP_quick2(pbstr,(float HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((float HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R8:
						GP_quick2(pbstr,(double HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((double HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BOOL:
						GP_quick2(pbstr,(VARIANT_BOOL HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT_BOOL HUGEP *)ptr2,lUBound+1);
						break;
					case VT_CY:
						GP_quick2(pbstr,(LONGLONG HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((LONGLONG HUGEP *)ptr2,lUBound+1);
						break;
					case VT_DATE:
						GP_quick2(pbstr,(DATE HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((DATE HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UNKNOWN:
						GP_quick2(pbstr,(IUnknown HUGEP **)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((IUnknown HUGEP **)ptr2,lUBound+1);
						break;
					case VT_DISPATCH:
						GP_quick2(pbstr,(IDispatch HUGEP **)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((IDispatch HUGEP **)ptr2,lUBound+1);
						break;
					}
					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_BOOL) == VT_BOOL)
				{
					VARIANT_BOOL HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					switch(V_VT(iArray2)&0xFF)
					{
					case VT_VARIANT:
						GP_quick2(pbstr,(VARIANT HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BSTR:
						GP_quick2(pbstr,(BSTR HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((BSTR HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UI1:
						GP_quick2(pbstr,(unsigned char HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((unsigned char HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I2:
						GP_quick2(pbstr,(short HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((short HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I4:
						GP_quick2(pbstr,(long HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((long HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R4:
						GP_quick2(pbstr,(float HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((float HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R8:
						GP_quick2(pbstr,(double HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((double HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BOOL:
						GP_quick2(pbstr,(VARIANT_BOOL HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT_BOOL HUGEP *)ptr2,lUBound+1);
						break;
					case VT_CY:
						GP_quick2(pbstr,(LONGLONG HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((LONGLONG HUGEP *)ptr2,lUBound+1);
						break;
					case VT_DATE:
						GP_quick2(pbstr,(DATE HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((DATE HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UNKNOWN:
						GP_quick2(pbstr,(IUnknown HUGEP **)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((IUnknown HUGEP **)ptr2,lUBound+1);
						break;
					case VT_DISPATCH:
						GP_quick2(pbstr,(IDispatch HUGEP **)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((IDispatch HUGEP **)ptr2,lUBound+1);
						break;
					}
					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_CY) == VT_CY)
				{
					LONGLONG HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					switch(V_VT(iArray2)&0xFF)
					{
					case VT_VARIANT:
						GP_quick2(pbstr,(VARIANT HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BSTR:
						GP_quick2(pbstr,(BSTR HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((BSTR HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UI1:
						GP_quick2(pbstr,(unsigned char HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((unsigned char HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I2:
						GP_quick2(pbstr,(short HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((short HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I4:
						GP_quick2(pbstr,(long HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((long HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R4:
						GP_quick2(pbstr,(float HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((float HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R8:
						GP_quick2(pbstr,(double HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((double HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BOOL:
						GP_quick2(pbstr,(VARIANT_BOOL HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT_BOOL HUGEP *)ptr2,lUBound+1);
						break;
					case VT_CY:
						GP_quick2(pbstr,(LONGLONG HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((LONGLONG HUGEP *)ptr2,lUBound+1);
						break;
					case VT_DATE:
						GP_quick2(pbstr,(DATE HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((DATE HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UNKNOWN:
						GP_quick2(pbstr,(IUnknown HUGEP **)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((IUnknown HUGEP **)ptr2,lUBound+1);
						break;
					case VT_DISPATCH:
						GP_quick2(pbstr,(IDispatch HUGEP **)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((IDispatch HUGEP **)ptr2,lUBound+1);
						break;
					}
					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_DATE) == VT_DATE)
				{
					DATE HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					switch(V_VT(iArray2)&0xFF)
					{
					case VT_VARIANT:
						GP_quick2(pbstr,(VARIANT HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BSTR:
						GP_quick2(pbstr,(BSTR HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((BSTR HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UI1:
						GP_quick2(pbstr,(unsigned char HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((unsigned char HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I2:
						GP_quick2(pbstr,(short HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((short HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I4:
						GP_quick2(pbstr,(long HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((long HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R4:
						GP_quick2(pbstr,(float HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((float HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R8:
						GP_quick2(pbstr,(double HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((double HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BOOL:
						GP_quick2(pbstr,(VARIANT_BOOL HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT_BOOL HUGEP *)ptr2,lUBound+1);
						break;
					case VT_CY:
						GP_quick2(pbstr,(LONGLONG HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((LONGLONG HUGEP *)ptr2,lUBound+1);
						break;
					case VT_DATE:
						GP_quick2(pbstr,(DATE HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((DATE HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UNKNOWN:
						GP_quick2(pbstr,(IUnknown HUGEP **)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((IUnknown HUGEP **)ptr2,lUBound+1);
						break;
					case VT_DISPATCH:
						GP_quick2(pbstr,(IDispatch HUGEP **)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((IDispatch HUGEP **)ptr2,lUBound+1);
						break;
					}
					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_UNKNOWN) == VT_UNKNOWN)
				{
					IUnknown HUGEP **pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					switch(V_VT(iArray2)&0xFF)
					{
					case VT_VARIANT:
						GP_quick2(pbstr,(VARIANT HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BSTR:
						GP_quick2(pbstr,(BSTR HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((BSTR HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UI1:
						GP_quick2(pbstr,(unsigned char HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((unsigned char HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I2:
						GP_quick2(pbstr,(short HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((short HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I4:
						GP_quick2(pbstr,(long HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((long HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R4:
						GP_quick2(pbstr,(float HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((float HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R8:
						GP_quick2(pbstr,(double HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((double HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BOOL:
						GP_quick2(pbstr,(VARIANT_BOOL HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT_BOOL HUGEP *)ptr2,lUBound+1);
						break;
					case VT_CY:
						GP_quick2(pbstr,(LONGLONG HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((LONGLONG HUGEP *)ptr2,lUBound+1);
						break;
					case VT_DATE:
						GP_quick2(pbstr,(DATE HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((DATE HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UNKNOWN:
						GP_quick2(pbstr,(IUnknown HUGEP **)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((IUnknown HUGEP **)ptr2,lUBound+1);
						break;
					case VT_DISPATCH:
						GP_quick2(pbstr,(IDispatch HUGEP **)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((IDispatch HUGEP **)ptr2,lUBound+1);
						break;
					}
					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_DISPATCH) == VT_DISPATCH)
				{
					IDispatch HUGEP **pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					switch(V_VT(iArray2)&0xFF)
					{
					case VT_VARIANT:
						GP_quick2(pbstr,(VARIANT HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BSTR:
						GP_quick2(pbstr,(BSTR HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((BSTR HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UI1:
						GP_quick2(pbstr,(unsigned char HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((unsigned char HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I2:
						GP_quick2(pbstr,(short HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((short HUGEP *)ptr2,lUBound+1);
						break;
					case VT_I4:
						GP_quick2(pbstr,(long HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((long HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R4:
						GP_quick2(pbstr,(float HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((float HUGEP *)ptr2,lUBound+1);
						break;
					case VT_R8:
						GP_quick2(pbstr,(double HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((double HUGEP *)ptr2,lUBound+1);
						break;
					case VT_BOOL:
						GP_quick2(pbstr,(VARIANT_BOOL HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((VARIANT_BOOL HUGEP *)ptr2,lUBound+1);
						break;
					case VT_CY:
						GP_quick2(pbstr,(LONGLONG HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((LONGLONG HUGEP *)ptr2,lUBound+1);
						break;
					case VT_DATE:
						GP_quick2(pbstr,(DATE HUGEP *)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((DATE HUGEP *)ptr2,lUBound+1);
						break;
					case VT_UNKNOWN:
						GP_quick2(pbstr,(IUnknown HUGEP **)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((IUnknown HUGEP **)ptr2,lUBound+1);
						break;
					case VT_DISPATCH:
						GP_quick2(pbstr,(IDispatch HUGEP **)ptr2,lUBound);
						if ((Flags&1)==1) GP_Reverse((IDispatch HUGEP **)ptr2,lUBound+1);
						break;
					}
					if ((Flags&1)==1) GP_Reverse(pbstr,lUBound+1);
					SafeArrayUnaccessData(psa);
				}
				else
				{
					SafeArrayUnaccessData(psa2);
					AfxThrowOleDispatchException(1111,"UNKNOWN ERROR");
				}
				SafeArrayUnaccessData(psa2);
			}
		}
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

long CGP_TermDoc::GPOLEArrayFindExactly(const VARIANT FAR& inArray, const VARIANT FAR& FindWhat, long FindFrom)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	SAFEARRAY FAR* psa = NULL;
	long retInd=-1;
	USES_CONVERSION;
	HRESULT hr;

	const VARIANT *iArray=&inArray;

	if (V_VT(iArray)==(VT_VARIANT|VT_BYREF))	iArray=inArray.pvarVal;

	if ((V_VT(iArray)&VT_ARRAY) != VT_ARRAY )	AfxThrowOleDispatchException(1001,IDS_GPOLEEXEPTION1001);
	else
	{
		psa = V_ARRAY(iArray);
		if (SafeArrayGetDim(psa) != 1)	AfxThrowOleDispatchException(1002,IDS_GPOLEEXEPTION1002);
		else
		{
			LONG lLBound, lUBound;
			SafeArrayGetLBound(psa, 1, &lLBound);
			hr = SafeArrayGetUBound(psa, 1, &lUBound);
			if (FAILED(hr))	AfxThrowOleDispatchException(1003,IDS_GPOLEEXEPTION1003);
#ifdef RUS
			if (FindFrom>lUBound || (FindFrom>=0 && FindFrom<lLBound))	AfxThrowOleDispatchException(1023,"Недопустимая позиция начала поиска");
#else
			if (FindFrom>lUBound || (FindFrom>=0 && FindFrom<lLBound))	AfxThrowOleDispatchException(1023,"Invalid starting position");
#endif
			else
			{
				COleVariant tmpvar(FindWhat);
				tmpvar.ChangeType(VT_BSTR);

				UINT low=FindFrom,high=lUBound,mid;
				if (low<0) low=0;
				CString cstmpstr;
				ConvVariantToString(FindWhat,cstmpstr,"");

				if ((V_VT(iArray)&VT_VARIANT) == VT_VARIANT)
				{
					VARIANT HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					if ((V_VT(pbstr)&VT_BSTR) == VT_BSTR)
					{
						BSTR tmpstr=cstmpstr.AllocSysString();
						while(low<=high)
						{
							mid=(low+high)/2;
							if (_wcsicmp(tmpstr,pbstr[mid].bstrVal)<0) high=mid-1;
							else
								if (_wcsicmp(tmpstr,pbstr[mid].bstrVal)>0) low=mid+1;
								else {retInd=mid;break;}
						}
						SysFreeString(tmpstr);
					}
					else
					if ((V_VT(pbstr)&VT_I2) == VT_I2)
					{
						short iId=atoi(cstmpstr);
						while(low<=high)
						{
							mid=(low+high)/2;
							if (iId<pbstr[mid].iVal) high=mid-1;
							else
								if (iId>pbstr[mid].iVal) low=mid+1;
								else {retInd=mid;break;}
						}
					}
					else
					if ((V_VT(pbstr)&VT_UI1) == VT_UI1)
					{
						unsigned char iId=atoi(cstmpstr);
						while(low<=high)
						{
							mid=(low+high)/2;
							if (iId<pbstr[mid].bVal) high=mid-1;
							else
								if (iId>pbstr[mid].bVal) low=mid+1;
								else {retInd=mid;break;}
						}
					}
					else
					if ((V_VT(pbstr)&VT_I4) == VT_I4 || (V_VT(pbstr)&VT_DATE) == VT_DATE)
					{
						long iId=atoi(cstmpstr);
						while(low<=high)
						{
							mid=(low+high)/2;
							if (iId<pbstr[mid].lVal) high=mid-1;
							else
								if (iId>pbstr[mid].lVal) low=mid+1;
								else {retInd=mid;break;}
						}
					}
					else
					if ((V_VT(pbstr)&VT_R4) == VT_R4)
					{
						float iId=(float)atof(cstmpstr);
						while(low<=high)
						{
							mid=(low+high)/2;
							if (iId<pbstr[mid].fltVal) high=mid-1;
							else
								if (iId>pbstr[mid].fltVal) low=mid+1;
								else {retInd=mid;break;}
						}
					}
					else
					if ((V_VT(pbstr)&VT_R8) == VT_R8 || (V_VT(pbstr)&VT_CY) == VT_CY)
					{
						double iId=atof(cstmpstr);
						while(low<=high)
						{
							mid=(low+high)/2;
							if (iId<pbstr[mid].dblVal) high=mid-1;
							else
								if (iId>pbstr[mid].dblVal) low=mid+1;
								else {retInd=mid;break;}
						}
					}

					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_BSTR) == VT_BSTR)
				{
					BSTR HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					while(low<=high)
					{
						mid=(low+high)/2;
						if (_wcsicmp(tmpvar.bstrVal,pbstr[mid])<0) high=mid-1;
						else
							if (_wcsicmp(tmpvar.bstrVal,pbstr[mid])>0) low=mid+1;
							else {retInd=mid;break;}
					}
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_UI1) == VT_UI1)
				{
					unsigned char HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					unsigned char iId=atoi(cstmpstr);
					while(low<=high)
					{
						mid=(low+high)/2;
						if (iId<pbstr[mid]) high=mid-1;
						else
							if (iId>pbstr[mid]) low=mid+1;
							else {retInd=mid;break;}
					}
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_I2) == VT_I2)
				{
					short HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					short iId=atoi(cstmpstr);
					while(low<=high)
					{
						mid=(low+high)/2;
						if (iId<pbstr[mid]) high=mid-1;
						else
							if (iId>pbstr[mid]) low=mid+1;
							else {retInd=mid;break;}
					}
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_I4) == VT_I4 || (V_VT(iArray)&VT_DATE) == VT_DATE)
				{
					long HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					long iId=atoi(cstmpstr);
					while(low<=high)
					{
						mid=(low+high)/2;
						if (iId<pbstr[mid]) high=mid-1;
						else
							if (iId>pbstr[mid]) low=mid+1;
							else {retInd=mid;break;}
					}
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_R4) == VT_R4)
				{
					float HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					float iId=(float)atof(cstmpstr);
					while(low<=high)
					{
						mid=(low+high)/2;
						if (iId<pbstr[mid]) high=mid-1;
						else
							if (iId>pbstr[mid]) low=mid+1;
							else {retInd=mid;break;}
					}
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_R8) == VT_R8 || (V_VT(iArray)&VT_CY) == VT_CY)
				{
					double HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					double iId=atof(cstmpstr);
					while(low<=high)
					{
						mid=(low+high)/2;
						if (iId<pbstr[mid]) high=mid-1;
						else
							if (iId>pbstr[mid]) low=mid+1;
							else {retInd=mid;break;}
					}
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_BOOL) == VT_BOOL)
				{
					VARIANT_BOOL HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					VARIANT_BOOL iId=atoi(cstmpstr);
					while(low<=high)
					{
						mid=(low+high)/2;
						if (iId<pbstr[mid]) high=mid-1;
						else
							if (iId>pbstr[mid]) low=mid+1;
							else {retInd=mid;break;}
					}
					SafeArrayUnaccessData(psa);
				}
				else AfxThrowOleDispatchException(1111,"UNKNOWN ERROR");
			}
		}
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return retInd;
}

long CGP_TermDoc::GPOLEArrayFind(const VARIANT FAR& inArray, const VARIANT FAR& FindWhat, long FindFrom)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	SAFEARRAY FAR* psa = NULL;
	long retInd=-1;

	USES_CONVERSION;
	HRESULT hr;

	const VARIANT *iArray=&inArray;

	if (V_VT(iArray)==(VT_VARIANT|VT_BYREF))	iArray=inArray.pvarVal;

	if ((V_VT(iArray)&VT_ARRAY) != VT_ARRAY )	AfxThrowOleDispatchException(1001,IDS_GPOLEEXEPTION1001);
	else
	{
		psa = V_ARRAY(iArray);
		if (SafeArrayGetDim(psa) != 1)	AfxThrowOleDispatchException(1002,IDS_GPOLEEXEPTION1002);
		else
		{
			LONG lLBound, lUBound,i;
			SafeArrayGetLBound(psa, 1, &lLBound);
			hr = SafeArrayGetUBound(psa, 1, &lUBound);
			if (FAILED(hr))	AfxThrowOleDispatchException(1003,IDS_GPOLEEXEPTION1003);
#ifdef RUS
			if (FindFrom>lUBound || (FindFrom>=0 && FindFrom<lLBound))	AfxThrowOleDispatchException(1023,"Недопустимая позиция начала поиска");
#else
			if (FindFrom>lUBound || (FindFrom>=0 && FindFrom<lLBound))	AfxThrowOleDispatchException(1023,"Invalid starting position");
#endif
			else
			{
				UINT low=FindFrom;
				if (low<0) low=0;
				CString cstmpstr;
				ConvVariantToString(FindWhat,cstmpstr,"");
				BSTR tmpstr=cstmpstr.AllocSysString();

				if ((V_VT(iArray)&VT_VARIANT) == VT_VARIANT)
				{
					VARIANT HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
					if ((V_VT(pbstr)&VT_BSTR) == VT_BSTR)
					{

						for(i=low;i<=lUBound && wcsstr(tmpstr,pbstr[i].bstrVal)!=NULL;i++);
						if (i<=lUBound) retInd=i;
					}
#ifdef RUS
					else AfxThrowOleDispatchException(1112,"Должен быть массив VARIANT/STRING");
#else
					else AfxThrowOleDispatchException(1112,"Must be array of VARIANT/STRING");
#endif
					SafeArrayUnaccessData(psa);
				}
				else
				if ((V_VT(iArray)&VT_BSTR) == VT_BSTR)
				{
					BSTR HUGEP *pbstr;
					SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
						for(i=low;i<=lUBound && wcsstr(tmpstr,pbstr[i])!=NULL;i++);
						if (i<=lUBound) retInd=i;
					SafeArrayUnaccessData(psa);
				}
#ifdef RUS
				else AfxThrowOleDispatchException(1112,"Должен быть массив VARIANT/STRING");
#else
				else AfxThrowOleDispatchException(1112,"Must be array of VARIANT/STRING");
#endif
				SysFreeString(tmpstr);
			}
		}
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return 0;
}

long CGP_TermDoc::GPOLEReadItem(LPCTSTR FileName, LPCTSTR ItemKey, VARIANT FAR* ItemArray)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNTimesServerRead++;
	long ret=-1;

	CString fStr(FileName);

	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ReadItem'",fStr);
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReadItem' when executing TCL",fStr);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReadItem' when executing SUB",fStr);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ReadItem'",fStr);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ReadItem'",fStr);

	AnsiToDosMB((LPCTSTR)fStr,fStr,0);

	CString lStr(ItemKey);
	AnsiToDosMB((LPCTSTR)lStr,lStr,0);

	char str[250];
	sprintf(str,"%sPGITEM%c%s%c%s",m_D3OlePrefix,0xFE,(LPCTSTR)fStr,0xFE,(LPCTSTR)lStr);
	GPC.WaitFor_m_MuteProc();
	LastResult=-123456;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);

	int i;
	for(i=0;i<m_waitCountFRead;i++)
	{
		if (GPC.m_View->DoAdditionalMessageLoop()<0) 
		{
			GPC.Release_m_MuteProc();
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "'ReadItem' aborted","");
			return  -13;
		}
		GPC.m_View->DoRemappingInput();
		if (LastResult==-123456) Sleep(m_waitTimeFRead);
		else break;
	}
	if (i>=m_waitCountFRead)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'ReadItem'","");
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();

	if (LastResult!=-123456)
	{
		if ((ret=atoi(GPC.m_View->InputBuffer2))>0)
		{
			DosToAnsi(GPC.m_View->InputBuffer2);
			CString delim("\x7F");
			char *pos=strchr(GPC.m_View->InputBuffer2,'#');
			if ((pos++)==NULL) pos="";
			ret=ConvertToArray(CString(pos),ItemArray,delim,m_VariantArrayType);
			if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNItemsServerRead++;
		}
	}
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

void CGP_TermDoc::RemoveAllDlg()
{
	int i;
	for(i=0;i<MAX_OBJDLG;i++)
	{
		DeleteObjDlg(i,FALSE,FALSE);
	}
}

void CGP_TermDoc::DeleteObjFrame(UINT iIdDlg, BOOL Reply, BOOL bReport)
{
	DeleteObjDlg(iIdDlg,Reply,bReport);
}

void CGP_TermDoc::DeleteObjDlg(UINT iIdDlg, BOOL Reply, BOOL bReport)
{
	try
	{
		UINT i;
		BOOL rep=FALSE;
		if (iIdDlg<MAX_OBJDLG)
		{
			if (a_GPObjType[iIdDlg]==0)
			{
				if (a_GPObjDialog[iIdDlg])
				{
					for(i=0;i<MAX_OBJDLG;i++)
						if (i!=iIdDlg)
						{
							if (a_GPObjType[i]==0)
							{
								if (a_GPObjDialog[i])
								{
									if (GetParent(a_GPObjDialog[i]->m_hWnd)==a_GPObjDialog[iIdDlg]->m_hWnd)
									{
										if (bReport)
										{
											CString tpms;
											tpms.Format("Parent %d %s, Child %d %s",iIdDlg,a_GPObjDialog[iIdDlg]->GPU[0]->GetObjectName(),i,a_GPObjDialog[i]->GPU[0]->GetObjectName());
											GPC.m_ErrReport.GPWriteWarnLog("Implicit deleting of child dialog",tpms ,"");
										}
										DeleteObjDlg(i,FALSE,bReport);
									}
								}
							}
							else
							{
								if (a_GPObjFrame[i])
								{
									if (GetParent(a_GPObjFrame[i]->m_hWnd)==a_GPObjDialog[iIdDlg]->m_hWnd)
									{
										if (bReport)
										{
											CString tpms;
											tpms.Format("Parent %d %s, Child %d %s",iIdDlg,a_GPObjDialog[iIdDlg]->GPU[0]->GetObjectName(),i,a_GPObjFrame[i]->GPU[0]->GetObjectName());
											GPC.m_ErrReport.GPWriteWarnLog("Implicit deleting of child frame",tpms ,"");
										}
										DeleteObjFrame(i,FALSE,bReport);
									}
								}
							}
						}

					if (a_GPObjDialog[iIdDlg]->DlgGPMenu) a_GPObjDialog[iIdDlg]->DlgGPMenu->ReleaseHBMP();
					if (a_GPObjDialog[iIdDlg]->m_hWnd!=NULL)
					{
						CWnd *tmp=a_GPObjDialog[iIdDlg]->GetParent();
						if (tmp) tmp->EnableWindow(TRUE);
						a_GPObjDialog[iIdDlg]->DestroyWindow();
					}
					delete a_GPObjDialog[iIdDlg];
//					a_GPObjDialogHn[iIdDlg]=NULL;
					a_GPObjDialog[iIdDlg]=NULL;
				}
				else rep=TRUE;
			}
			else
			{
				if (a_GPObjFrame[iIdDlg])
				{
					for(i=0;i<MAX_OBJDLG;i++)
						if (i!=iIdDlg)
						{
							if (a_GPObjType[i]==0)
							{
								if (a_GPObjDialog[i])
								{
									if (bReport)
									{
										CString tpms;
										tpms.Format("Parent %d %s, Child %d %s",iIdDlg,a_GPObjFrame[iIdDlg]->GPU[0]->GetObjectName(),i,a_GPObjDialog[i]->GPU[0]->GetObjectName());
										GPC.m_ErrReport.GPWriteWarnLog("Implicit deleting of child dialog",tpms ,"");
									}
									DeleteObjDlg(i,FALSE,bReport);
								}
							}
							else
							{
								if (a_GPObjFrame[i])
								{
									if (bReport)
									{
										CString tpms;
										tpms.Format("Parent %d %s, Child %d %s",iIdDlg,a_GPObjFrame[iIdDlg]->GPU[0]->GetObjectName(),i,a_GPObjFrame[i]->GPU[0]->GetObjectName());
										GPC.m_ErrReport.GPWriteWarnLog("Implicit deleting of child frame",tpms ,"");
									}
									DeleteObjFrame(i,FALSE,bReport);
								}
							}
						}
					if (a_GPObjFrame[iIdDlg]->DlgGPMenu) a_GPObjFrame[iIdDlg]->DlgGPMenu->ReleaseHBMP();
					if (a_GPObjFrame[iIdDlg]->m_hWnd!=NULL)
					{
						CWnd *tmp=a_GPObjFrame[iIdDlg]->GetParent();
						if (tmp) tmp->EnableWindow(TRUE);
					}
					delete a_GPObjFrame[iIdDlg];
					a_GPObjFrame[iIdDlg]=NULL;
				}
				else rep=TRUE;
			}
		}
		else rep=TRUE;

		if (bReport && rep)
		{
			CString tpms;
			tpms.Format("%d",iIdDlg);
			GPC.m_ErrReport.GPWriteWarnLog("Try to delete nonexistent dialog",tpms ,"");
		}
	}
	catch(...){;}
	if (Reply==TRUE)
	{
		GPC.WaitFor_m_MuteProc();
		m_Comm.GPSendChar('1');m_Comm.GPSendChar(13);
		GPC.Release_m_MuteProc();
	}
}

void CGP_TermDoc::OnFileOpen()
{
}

void CGP_TermDoc::OnFileNew()
{
//	a_GPObjDialogDesktop->OnRButtonDblClk(MK_CONTROL|MK_SHIFT, CPoint(0,0));
}

COleIPFrameWnd* CGP_TermDoc::CreateInPlaceFrame(CWnd* pParentWnd)
{
	return COleServerDoc::CreateInPlaceFrame(pParentWnd);
}

void CGP_TermDoc::OnDocWindowActivate(BOOL bActivate)
{
	COleServerDoc::OnDocWindowActivate(bActivate);
}

long CGP_TermDoc::RegisterInROT(BSTR* iStr)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	CString str=*iStr;
	long ret=RegisterGPTermInROT(str);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::RegisterGPTermInROT(const char* iStr)
{
	BOOL ret=FALSE;
	IBindCtx* pBindCtx=NULL;
 	IRunningObjectTable* prot=NULL;
	HRESULT hr;
	LPDISPATCH pDisp=NULL;
	LPUNKNOWN pUnk=NULL;
	CString str=iStr;
	BSTR iStrB=str.AllocSysString();

	//получение LPUNKNOWN
	pDisp=GetIDispatch(FALSE);
	ASSERT(pDisp);
	if (pDisp)
	{
		hr=pDisp->QueryInterface(IID_IUnknown,(void**) &pUnk);
		if (SUCCEEDED (hr))
		{
			 hr = CreateBindCtx (0, &pBindCtx);
			 if (SUCCEEDED (hr))
			 {
				// регистрация в ROT
				 IMoniker* pMoniker;
				 hr=CreateItemMoniker(L"",iStrB, &pMoniker);
				 if (SUCCEEDED (hr))
				 {
					// запись в ROT
					hr = pBindCtx->GetRunningObjectTable (&prot);
					if (SUCCEEDED(hr))
					{
						if (IsRegisterInROT(pBindCtx,prot,&iStrB)<=0)
						{
							int IdReg=0;
							while ((IdReg<MAX_REGISTERROT) && (m_dwReg[IdReg]!=0xFFFFFFFF))
								IdReg++;
							if (IdReg<MAX_REGISTERROT)
								if (SUCCEEDED (hr))
								{
									//hr = prot->Register(ROTFLAGS_ALLOWANYCLIENT,pUnk, pMoniker, &m_dwReg[IdReg]);
									hr = prot->Register(ROTFLAGS_REGISTRATIONKEEPSALIVE,pUnk, pMoniker, &m_dwReg[IdReg]);
									if (SUCCEEDED(hr))
									{
										m_dwRegStr[IdReg]=str;
										ret=TRUE;
									}
									pMoniker->Release();
								}
						}
						prot->Release();
					}
					pBindCtx->Release ();
				}
			}
			pUnk->Release();
		 }
	}
	::SysFreeString(iStrB);
	return ret;
}


long CGP_TermDoc::RevokeGPTermRegisterFromROT()
{
	IBindCtx* pBindCtx;
 	IRunningObjectTable* prot;
	HRESULT hr = CreateBindCtx (0, &pBindCtx);
	if (SUCCEEDED(hr))
	{
 		hr = pBindCtx->GetRunningObjectTable (&prot);
		if (SUCCEEDED(hr))
		{
			int IdReg=0;
			while (IdReg!=MAX_REGISTERROT)
			{
				if (m_dwReg[IdReg]!=0xFFFFFFFF)
				{
					hr=prot->Revoke(m_dwReg[IdReg]);
					if (SUCCEEDED(hr))
					{
						m_dwReg[IdReg]=0xFFFFFFFF;
						m_dwRegStr[IdReg]="";
					}
				}
				IdReg++;
			}
			prot->Release();
		}
		pBindCtx->Release();
	}
	return 0;
}

long CGP_TermDoc::RevokeFromROT()
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long val=RevokeGPTermRegisterFromROT();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return val;
}

long CGP_TermDoc::IsRegisterInROT(IBindCtx* pBind,IRunningObjectTable* prot,BSTR* iStr)
{
	long ret=-1;

	LPOLESTR pName;
	IMoniker* pmon;
	IEnumMoniker *pem;
	LPUNKNOWN pUnk;
	HRESULT hr;

    hr = prot->EnumRunning(&pem);
	if (SUCCEEDED(hr))
	{
		pem->Reset();
		ULONG fetched;
		while((pem->Next(1, &pmon, &fetched) == S_OK) && (ret<=0))
		{
			hr=pmon->GetDisplayName(pBind, NULL, &pName);
			if (!wcscmp(*iStr,pName))
			{
				hr=prot->GetObject(pmon,&pUnk);
				if (SUCCEEDED(hr))
				{
					pUnk->Release();
					ret=1;	// уже есть такая строка в ROT
				}
			}
			pmon->Release();
		}
		pem->Release();
	}

	return ret;
}

long CGP_TermDoc::UnRegisterGPTermInROT(const char* iStr)
{
	long ret=-1;
	IBindCtx* pBindCtx;
 	IRunningObjectTable* prot;
	HRESULT hr = CreateBindCtx (0, &pBindCtx);
	CString str=iStr;

	if (SUCCEEDED(hr))
	{
		ret++;
 		hr = pBindCtx->GetRunningObjectTable (&prot);
		if (SUCCEEDED(hr))
		{
			int IdReg=0;
			while (IdReg!=MAX_REGISTERROT)
			{
				if ((m_dwReg[IdReg]!=0xFFFFFFFF) && (0==strcmp(str,m_dwRegStr[IdReg])))
				{
					hr=prot->Revoke(m_dwReg[IdReg]);
					if (SUCCEEDED(hr))
					{
						ret++;
						m_dwReg[IdReg]=0xFFFFFFFF;
						m_dwRegStr[IdReg]="";
					}
				}
				IdReg++;
			}
			prot->Release();
		}
		pBindCtx->Release();
	}
	return ret;
}

long CGP_TermDoc::ListMakerAddList(LPCTSTR DestListName, LPCTSTR SrcListName)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.AddList(CString(DestListName),CString(SrcListName));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerAppendList(LPCTSTR DestListName, LPCTSTR SrcList)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.AppendList(CString(DestListName),CString(SrcList));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerSquiseList(LPCTSTR ListName)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.SquiseList(CString(ListName));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerDuplicateList(LPCTSTR DestListName, LPCTSTR SrcListName)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.DuplicateList(CString(DestListName),CString(SrcListName));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerUniqueList(LPCTSTR ListName)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.UniqueList(CString(ListName));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerSortList(LPCTSTR ListName)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	GPC.m_ListMaker.SortList(CString(ListName));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return 0;
}

long CGP_TermDoc::ListMakerNBeginCont(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.NotBeginContextLists(CString(DestName), CString(SrcName1), CString(SrcName2));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerBeginCont(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.BeginContextLists(CString(DestName), CString(SrcName1),CString( SrcName2));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerNEndCont(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.NotEndContextLists(CString(DestName), CString(SrcName1), CString(SrcName2));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerEndCont(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.EndContextLists(CString(DestName), CString(SrcName1), CString(SrcName2));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerNContList(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.NotContextLists(CString(DestName), CString(SrcName1), CString(SrcName2));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerContList(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.ContextLists(CString(DestName), CString(SrcName1), CString(SrcName2));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerNMaskList(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.NotMaskLists(CString(DestName), CString(SrcName1), CString(SrcName2));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerMaskList(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.MaskLists(CString(DestName), CString(SrcName1), CString(SrcName2));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerXORList(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.XORLists(CString(DestName), CString(SrcName1), CString(SrcName2));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerORList(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.ORLists(CString(DestName), CString(SrcName1), CString(SrcName2));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerANDList(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.ANDLists(CString(DestName), CString(SrcName1), CString(SrcName2));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerNOTList(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.NOTLists(CString(DestName), CString(SrcName1), CString(SrcName2));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerDeleteList(LPCTSTR ListName)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.DeleteList(CString(ListName));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerCreateList(LPCTSTR ListName)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.CreateList(CString(ListName));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerGetListInfo(LPCTSTR ListName, VARIANT FAR* ListInfo)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.GetListInfo(CString(ListName),ListInfo);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerGetListsInfo(VARIANT FAR* ListInfo)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.GetListsInfo(ListInfo);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerLoadList(LPCTSTR ListName, LPCTSTR FileName)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.LoadList(ListName, FileName);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerSaveList(LPCTSTR ListName, LPCTSTR FileName)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.SaveList(CString(ListName), CString(FileName));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerLoadPickList(LPCTSTR ListName, LPCTSTR FileName, LPCTSTR ItemName)
{
	CString fStr(FileName);
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("ListMaker", "Terminal not connected when call 'ListMakerLoadPickList'",FileName);
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ListMakerLoadPickList' when executing TCL",FileName);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ListMakerLoadPickList' when executing SUB",FileName);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ListMakerLoadPickList'",FileName);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ListMakerLoadPickList'",FileName);

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=-1;

	AnsiToDosMB((LPCTSTR)fStr,fStr,0);

	CString lStr(ItemName);
	AnsiToDosMB((LPCTSTR)lStr,lStr,0);

	char str[250];
	sprintf(str,"%sPGLIST%c%s%c%s",m_D3OlePrefix,0xFE,(LPCTSTR)fStr,0xFE,(LPCTSTR)lStr);
	GPC.WaitFor_m_MuteProc();
	LastResult=-123456;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);

	int i;
	for(i=0;i<m_waitCountFRead;i++)
	{
		if (GPC.m_View->DoAdditionalMessageLoop()<0) 
		{
			GPC.Release_m_MuteProc();
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "'ListMakerLoadPickList' aborted","");
			return  -13;
		}
		GPC.m_View->DoRemappingInput();
		if (LastResult==-123456) Sleep(m_waitTimeFRead);
		else break;
	}
	if (i>=m_waitCountFRead)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'ListMakerLoadPickList'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	if (LastResult!=-123456)
	{
		if ((ret=atoi(GPC.m_View->InputBuffer2))>0)
		{
			DosToAnsi(GPC.m_View->InputBuffer2);
			CString delim("\x7F");
			char *pos=strchr(GPC.m_View->InputBuffer2,'#');
			if ((pos++)==NULL) pos="";
			ret=GPC.m_ListMaker.SetList(CString(ListName),pos,GPC.DelimiterIn1);
		}
	}
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerSavePickList(LPCTSTR ListName, LPCTSTR FileName, LPCTSTR ItemName)
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ListMakerSavePickList'","");
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ListMakerSavePickList' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ListMakerSavePickList' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ListMakerSavePickList'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ListMakerSavePickList'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	char *pos=NULL;
	long ret;
	ret=GPC.m_ListMaker.GetList(CString(ListName),&pos);
	if (ret>=0)
	{
		CString fStr(FileName);
		AnsiToDosMB((LPCTSTR)fStr,fStr,0);

		CString lStr(ItemName);
		AnsiToDosMB((LPCTSTR)lStr,lStr,0);

		char str[250];
		sprintf(str,"%sPSLIST%c%s%c%s",m_D3OlePrefix,0xFE,(LPCTSTR)fStr,0xFE,(LPCTSTR)lStr);
		GPC.WaitFor_m_MuteProc();
		LastResult=-123456;
		if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
		m_Comm.GPSendBlock(str,(int)strlen(str));
		m_Comm.GPSendBlock("\r",1);

		AnsiToDosMB(pos,1);
		if ((ret%30000)==0 && ret!=0) strcpy(pos+ret,BLOCK_STR);
		m_Comm.GPSendBlock(pos,(int)strlen(pos));
		m_Comm.GPSendBlock("\r",1);
		if (pos!=NULL) delete[] pos;

		int i;
		for(i=0;i<m_waitCountFWrite;i++)
		{
			if (GPC.m_View->DoAdditionalMessageLoop()<0)
			{
				GPC.Release_m_MuteProc();
				GPC.m_ErrReport.GPWriteErrorLog2("COM", "'ListMakerSavePickList' aborted","");
				return  -13;
			}
			GPC.m_View->DoRemappingInput();
			if (LastResult==-123456) Sleep(m_waitTimeFWrite);
			else
			{
				ret=atoi(GPC.m_View->InputBuffer2);
				break;
			}
		}
		if (i>=m_waitCountFWrite)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'ListMakerSavePickList'","");
		if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
		GPC.Release_m_MuteProc();
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerSetListAsArrayNet(LPCTSTR ListName, const VARIANT FAR& ListArray)
{
	return ListMakerSetListAsArray(ListName, (VARIANT FAR*)&ListArray);
}

long CGP_TermDoc::ListMakerSetListAsArray(LPCTSTR ListName, VARIANT FAR* ListArray)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.SetListAsArray(CString(ListName),ListArray);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerGetListAsArray(LPCTSTR ListName, VARIANT FAR* ListArray)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.GetListAsArray(CString(ListName),ListArray);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerGetList(LPCTSTR ListName, BSTR FAR* OutListString)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.GetList(CString(ListName),OutListString);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerSetList(LPCTSTR ListName, LPCTSTR iList, short delimiter)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.SetList(CString(ListName),CString(iList),(char)delimiter);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}


long CGP_TermDoc::OLESprGetInfo(LPCTSTR SprName, VARIANT FAR* SprInfo)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	CGPSpr *pSpr=GPC.m_SprArray.GetSpr(CString(SprName));
	long ret=-1;
	if (pSpr!=NULL) ret=pSpr->GetSprInfo(SprInfo,m_VariantArrayType);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::OLESprGetInfos(VARIANT FAR* SprInfos)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_SprArray.GetSprInfos(SprInfos,m_VariantArrayType);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::OLESprCreate(LPCTSTR SprName, short nFields)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=0;
	CGPSpr *pSpr=GPC.m_SprArray.CreateSpr(CString(SprName));
	if (pSpr!=NULL) ret=pSpr->Create(CString(SprName),nFields);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::OLESprDelete(LPCTSTR SprName)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_SprArray.DeleteSpr(CString(SprName));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}


long CGP_TermDoc::OLESprDoSub(LPCTSTR SprName, LPCTSTR MethodName,  const VARIANT FAR& Params)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=-1;
	CString tmpstr;
	CString tmpstrmeth(MethodName);
	tmpstrmeth+=" ";
	char wof[3]={0};
	wof[0]=GPC.DelimiterIn1;
	wof[1]=GPC.DelimiterIn2;
	ConvVariantToString(Params,tmpstr,wof);
	tmpstrmeth+=tmpstr;
	ret=GPC.m_SprArray.DoMethod(CString(SprName),tmpstrmeth,NULL);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::OLESprDoFn(LPCTSTR SprName, LPCTSTR MethodName, const VARIANT FAR& Params, VARIANT* Result)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=-1;
	CString tmpstr;
	CString tmpstrmeth(MethodName);
	tmpstrmeth+=" ";
	char wof[3]={0};
	wof[0]=GPC.DelimiterIn1;
	wof[1]=GPC.DelimiterIn2;
	ConvVariantToString(Params,tmpstr,wof);
	char *oStr=NULL;
	tmpstrmeth+=tmpstr;
	ret=GPC.m_SprArray.DoMethod(CString(SprName),tmpstrmeth,&oStr);
	if (oStr!=NULL)
	{
		StringToArrayEx(oStr,Result,"\x7Fq1w2e3r4\x7");
		delete[] oStr;
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::OLESprFillObject(LPCTSTR SprName, OLE_HANDLE hWnd, long ObjType, LPCTSTR FillParam, long FillType)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_SprArray.FillObject(CString(SprName),(HWND)hWnd, ObjType,CString(FillParam), FillType);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::OLESprReplaceObject(LPCTSTR SprName, OLE_HANDLE hWnd, long ObjType, LPCTSTR FillParam)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_SprArray.ReplaceObject(CString(SprName),(HWND)hWnd, ObjType,CString(FillParam));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::ListMakerFillObject(LPCTSTR ListName, OLE_HANDLE hWnd, long ObjType, long FillType)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_ListMaker.FillObject(CString(ListName),(HWND)hWnd, ObjType, FillType);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::OLESprFillByDisp(LPCTSTR SprName, LPDISPATCH ObjDispatch, LPCTSTR FillParams, long FillType)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_SprArray.FillObject(CString(SprName),ObjDispatch, CString(FillParams), FillType);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::OLESprFillByArray(LPCTSTR SprName, const VARIANT FAR& KeyArray, long nField, VARIANT FAR* RetArray)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_SprArray.FillByArray(CString(SprName),KeyArray, nField, RetArray);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::OLESprReplaceObjectEx(OLE_HANDLE ihWnd, long ObjType, long StartItem, long EndItem, LPCTSTR Params)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_SprArray.ReplaceOblectEx((HWND) ihWnd, ObjType, StartItem, EndItem, CString(Params));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::OLESprReplaceByDisp(LPDISPATCH ObjDispatch, long StartItem, long EndItem, LPCTSTR Params)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=GPC.m_SprArray.ReplaceOblectEx(ObjDispatch, StartItem, EndItem,CString(Params));
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::OLESprGetItem(LPCTSTR SprName, long ItemId, VARIANT FAR* SprItem)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=-1;
	CGPSpr *tmpspr= GPC.m_SprArray.GetSpr(CString(SprName));
	if (tmpspr!=NULL)
	{
		char *oStr=NULL;
		CString strmet;
		strmet.Format("GetItem %d",ItemId);
		ret=0;
		tmpspr->DoMethod(strmet,&oStr);

		if (oStr!=NULL)
		{
			StringToArrayEx(oStr,SprItem,"\x7Fq1w2e3r4\x7");
			ret=1;
			delete[] oStr;
		}
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::OLESprInsertItem(LPCTSTR SprName, long ItemId, const VARIANT FAR& SprItem)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=-1;

	CGPSpr *tmpspr= GPC.m_SprArray.GetSpr(CString(SprName));
	if (tmpspr!=NULL)
	{
		CString strmet;
		strmet.Format("InsertItems %d,",ItemId);
		CString strmet2;

		const VARIANT *iArray=&SprItem;
		if (V_VT(iArray)==(VT_VARIANT|VT_BYREF))	iArray=SprItem.pvarVal;


		if ((V_VT(iArray)&VT_ARRAY) != VT_ARRAY )
		{
			ConvVariantToString(SprItem,strmet2,GPC.csDelimiterIn1);
			strmet.Format("InsertItem %d,",ItemId);
		}
		else
		{
			strmet.Format("InsertItems %d,",ItemId);
			char strdelim[200];
			strcpy(strdelim,"^q1w2e3r4]q1w2e3r4\x01q1w2e3r4\x02q1w2e3r4\x03q1w2e3r4\x04q1w2e3r4\x05");
			*strdelim=GPC.DelimiterIn1;
			ArrayToStringEx(iArray,strmet2,strdelim);
		}

		strmet+=strmet2;
		tmpspr->DoMethod(strmet,NULL);
		ret=tmpspr->GetCount();
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::OLESprLoadFromPick(LPCTSTR SprName, LPCTSTR PickFileName, long bReload, LPCTSTR SelectString)
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'SprLoadFromPick'","");
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'SprLoadFromPick' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'SprLoadFromPick' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'SprLoadFromPick'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'SprLoadFromPick'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	int nSel=-1;
	CGPSpr *tmpspr= GPC.m_SprArray.GetSpr(CString(SprName));
	if (tmpspr!=NULL)
	{
		if (*SelectString!=0)
		{
			GPOLEExecTCL(SelectString);
			VARIANT vtmp;
			VariantInit(&vtmp);
			while(GPOLEGetTCLResult(&vtmp,0)<0);
			GPOLEDoSystem(&vtmp,11);
			CString str;
			ConvVariantToString(vtmp,str,"");
			nSel=atoi(str);
			VariantClear(&vtmp);
		}
		else nSel=123456789;

		if (bReload!=0) tmpspr->Destroy();

		if (nSel>0)
		{
			CString FName(PickFileName);
			AnsiToDosMB((LPCTSTR)FName,FName,0);
			char str[150];
			sprintf(str,"%sPRAFILE%c%s",m_D3OlePrefix,0xFE,(LPCTSTR)FName);

			GPC.WaitFor_m_MuteProc();
			LastResult=-123456;
			if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
			m_Comm.GPSendBlock(str,(int)strlen(str));
			m_Comm.GPSendBlock("\r",1);

			int i;
			for(i=0;i<m_waitCountFRead;i++)
			{
				if (GPC.m_View->DoAdditionalMessageLoop()<0)
				{
					GPC.Release_m_MuteProc();
					GPC.m_ErrReport.GPWriteErrorLog2("COM", "'SprLoadFromPick' aborted","");
					return  -13;
				}
				GPC.m_View->DoRemappingInput();
				if (LastResult==-123456) Sleep(m_waitTimeFRead);
				else break;
			}
			if (i>=m_waitCountFRead)
				GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'SprLoadFromPick'","");
			if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();

			{
				DosToAnsi(GPC.m_View->InputBuffer2);
				char *pos=strchr(GPC.m_View->InputBuffer2,'#');
				if (pos!=NULL)
				{
					char *poskey=NULL;
					pos++;
					poskey=strchr(pos,0x05);
					if (poskey!=NULL) *(poskey++)=0;
					else poskey="";
					CString strmet;
					int ItemId=0;
					while(*pos!=0 || *poskey!=0)
					{
						char *pos2=strchr(pos,127);
						char *poskey2=strchr(poskey,127);
						if (pos2!=NULL) *(pos2++)=0;
						else pos2="";
						if (poskey2!=NULL) *(poskey2++)=0;
						else poskey2="";
						strmet.Format("InsertItem %d,%s%c%s",ItemId,pos,GPC.DelimiterIn1,poskey);
						strmet.Replace("\x1",GPC.csDelimiterIn1);
						tmpspr->DoMethod(strmet,NULL);
						pos=pos2;
						poskey=poskey2;
					}
					nSel=tmpspr->GetCount();
				}
				else nSel=-4;
			}
			GPC.Release_m_MuteProc();
		}
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return nSel;
}

long CGP_TermDoc::MPGetVariables(char **StrVar)
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("Terminal", "Terminal not connected when call 'MPGetVariables'","");
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'MPGetVariables' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'MPGetVariables' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'MPGetVariables'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'MPGetVariables'","");

	long ret=-1;
	char str[250];

	sprintf(str,"%sPGETVARS",m_D3OlePrefix);
	GPC.WaitFor_m_MuteProc();
	LastResult=-123456;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);

	int i;
	for(i=0;i<200;i++)
	{
		if (GPC.m_View->DoAdditionalMessageLoop()<0)
		{
			GPC.Release_m_MuteProc();
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "'MPGetVariables' aborted","");
			return  -13;
		}
		GPC.m_View->DoRemappingInput();
		if (LastResult==-123456) Sleep(100);
		else break;
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();

	if (LastResult!=-123456)
	{
		DosToAnsi(GPC.m_View->InputBuffer2);
		*StrVar=new char [(int)strlen(GPC.m_View->InputBuffer2)+100];
		strcpy(*StrVar,GPC.m_View->InputBuffer2);
		ret=(int)strlen(*StrVar);
	}
	GPC.Release_m_MuteProc();

	return ret;
}


long CGP_TermDoc::OLEGetMPVars(VARIANT FAR* MPVarsArr)
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'GetMPVars'","");
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'GetMPVars' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'GetMPVars' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'GetMPVars'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'GetMPVars'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=-1;
	char *str=NULL;

	MPGetVariables(&str);

	if (str!=NULL)
	{
		StringToArrayEx(str,MPVarsArr,"\x6q1w2e3r4\x1q1w2e3r4\x2q1w2e3r4\x3q1w2e3r4\x4q1w2e3r4\x5");
		delete[] str;
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::OLEPause(long DelayMS)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	Sleep(DelayMS);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return DelayMS;
}

WORD wCRC16a[16]={
	0000000,    0140301,    0140601,    0000500,
	0141401,    0001700,    0001200,    0141101,
	0143001,    0003300,    0003600,    0143501,
	0002400,    0142701,    0142201,    0002100,
};
WORD wCRC16b[16]={
	0000000,    0146001,    0154001,    0012000,
	0170001,    0036000,    0024000,    0162001,
	0120001,    0066000,    0074000,    0132001,
	0050000,    0116001,    0104001,    0043000,
};

void calc_CRC16DDK(PVOID pBuffer, ULONG ulSize, PULONG pulSeed)
{
  PBYTE    pb;
  BYTE    bTmp;

  for(pb=(BYTE *)pBuffer; ulSize; ulSize--, pb++)
  {
    bTmp=(BYTE)(((WORD)*pb)^((WORD)*pulSeed));    // Xor CRC with new char
    *pulSeed=((*pulSeed)>>8) ^ wCRC16a[bTmp&0x0F] ^ wCRC16b[bTmp>>4];
  }
}

void calc_CRC16(ULONG *t16, ULONG *crc,BYTE nextbyte)
{
ULONG temp=(*crc)^nextbyte;
temp=(temp>>4)^t16[temp&0x000F];
temp=(temp>>4)^t16[temp&0x000F];
*crc=temp;
}

void calc_table16(ULONG *t16)
{
	ULONG POLY=0xA001;
	for(ULONG val=0;val<=15;val++)
	{
		ULONG result=val;
		for(ULONG i=1;i<=4;i++)
		{
			if ((result&1)==1) result= (result>>1)^POLY;
				else result=(result>> 1);
		}
		t16[val]=result;
	}
}

DWORD calc_CRC16(const BYTE *iArray, DWORD dwArrLen, ULONG PrevCRC, ULONG *table16)
{
	DWORD ret=PrevCRC;
	if (!table16) table16=GPC.tcrc16;
	if (!dwArrLen) dwArrLen=(int)strlen((const char *)iArray);
	while(dwArrLen--)
		calc_CRC16(table16, &ret, *(iArray++));

	return ret;
}

long CGP_TermDoc::OLEGetCRC16(const VARIANT FAR& inpValue, long PrevSumm)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	CString str;
	ConvertToString(&inpValue,str,"");

	UINT ulSize=str.GetLength();
	ULONG ulSeed=PrevSumm;
	const char *pBuffer=str;
	PBYTE    pb;
	for(pb=(BYTE *)pBuffer; ulSize; ulSize--, pb++)
		calc_CRC16(GPC.tcrc16, &ulSeed,*pb);

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ulSeed;
}

long CGP_TermDoc::OLESprGetValues(LPCTSTR SprName, long nField, VARIANT FAR* SprItem)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=-1;

	CGPSpr *tmpspr= GPC.m_SprArray.GetSpr(CString(SprName));
	if (tmpspr!=NULL)
	{
		char strmet[200];
		char *oStr=NULL;
		sprintf(strmet,"GetValues %d",nField);
		ret=0;
		tmpspr->DoMethod(strmet,&oStr);
		if (oStr)
		{
			StringToArrayEx(oStr,SprItem,"\x7Fq1w2e3r4\x7");
			delete[] oStr;
		}
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::OLESprGetValuesEx(LPCTSTR SprName, const VARIANT FAR& FieldsArr, VARIANT FAR* SprItems)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=-1;
	CString strFields;
	ConvVariantToString(FieldsArr,strFields,GPC.csDelimiterIn1);
	CGPSpr *tmpspr= GPC.m_SprArray.GetSpr(CString(SprName));
	if (tmpspr!=NULL && strFields.GetLength()>0)
	{
		CString strmet;
		char *oStr=NULL;
		strmet.Format("GetValuesEx %s",(LPCSTR)strFields);
		ret=0;
		tmpspr->DoMethod(strmet,&oStr);
		if (oStr)
		{
			StringToArrayEx(oStr,SprItems,"\x7Fq1w2e3r4\x7");
			delete[] oStr;
		}
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

void CGP_TermDoc::OnDlgpickdata()
{
	if (DlgMPVars==NULL)
	{
		DlgMPVars =new GPDlgViewMPVar;
		DlgMPVars->Create(IDD_DIALOGVIEWVARS);
	}

	try	{DlgMPVars->ShowWindow(SW_SHOW);}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGP_TermDoc", "OnDlgpickdata 6648","");
		DlgMPVars =new GPDlgViewMPVar;
		DlgMPVars->Create(IDD_DIALOGVIEWVARS);
	}

	try	{DlgMPVars->ShowWindow(SW_SHOW);}catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGP_TermDoc", "OnDlgpickdata 6655","");
	}

	DlgMPVars->SetWindowPos(&CWnd::wndTop,0,0,0,0,SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOSIZE);
}

void CGP_TermDoc::OLESetNextDlgParent(OLE_HANDLE ParentHWND)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	GPC.NextParentFromOLE=(HWND)ParentHWND;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}


long CGP_TermDoc::OLESprSetItem(LPCTSTR SprName, long ItemId, const VARIANT FAR& SprItem)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=-1;
	CGPSpr *tmpspr= GPC.m_SprArray.GetSpr(CString(SprName));
	if (tmpspr!=NULL)
	{
		char *oStr=NULL;
		CString strmet;
		CString strItem;
		ConvVariantToString(SprItem,strItem,GPC.csDelimiterIn1);

		strmet.Format("SetItem %d,%s",ItemId,(LPCTSTR)strItem);
		ret=0;
		tmpspr->DoMethod(strmet,NULL);

		if (oStr!=NULL)
		{
			ret=atoi(oStr);
			ret=1;
			delete[] oStr;
		}
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::OLENamedDataSet(LPCTSTR Name, const VARIANT FAR& Value)
{
	CString lStr(Name);
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'NamedDataSet'",lStr);
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'NamedDataSet' when executing TCL",lStr);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'NamedDataSet' when executing SUB",lStr);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'NamedDataSet'",lStr);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'NamedDataSet'",lStr);

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=0;

	AnsiToDosMB((LPCTSTR)lStr,lStr,0);

	char str[250];
	sprintf(str,"%sSNDATA%c%s",m_D3OlePrefix,0xFE,(LPCTSTR)lStr);
	GPC.WaitFor_m_MuteProc();
	LastResult=-123456;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);

	CString delim("\x7F");
	CString oStr;

	ConvVariantToString(Value, oStr, "\x7F");
	AnsiToDosMB((LPCTSTR)oStr,oStr,1);

	if ((oStr.GetLength()%30000)==0 && oStr.GetLength()!=0)	oStr+=BLOCK_STR;
	m_Comm.GPSendBlock((LPCTSTR)oStr,oStr.GetLength());
	m_Comm.GPSendBlock("\r",1);
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::OLENamedDataGet(LPCTSTR Name, VARIANT FAR* Value)
{
	CString lStr(Name);
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'NamedDataGet'",lStr);
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'NamedDataGet' when executing TCL",lStr);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'NamedDataGet' when executing SUB",lStr);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'NamedDataGet'",lStr);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'NamedDataGet'",lStr);

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=0;

	AnsiToDosMB((LPCTSTR)lStr,lStr,0);

	char str[250];
	sprintf(str,"%sGNDATA%c%s",m_D3OlePrefix,0xFE,(LPCTSTR)lStr);
	GPC.WaitFor_m_MuteProc();
	LastResult=-123456;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);

	int i;
	for(i=0;i<m_waitCountFRead;i++)
	{
		if (GPC.m_View->DoAdditionalMessageLoop()<0)
		{
			GPC.Release_m_MuteProc();
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "'NamedDataGet' aborted","");
			return  -13;
		}
		GPC.m_View->DoRemappingInput();
		if (LastResult==-123456) Sleep(m_waitTimeFRead);
		else break;
	}
	if (i>=m_waitCountFRead)
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'NamedDataGet'","");
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();


	if (LastResult!=-123456)
	{
		DosToAnsi(GPC.m_View->InputBuffer2);
		CString delim("\x7F");
		char *pos=strchr(GPC.m_View->InputBuffer2,'#');
		if ((pos++)==NULL) pos="";
		ret=ConvertToArray(CString(pos),Value,delim,m_VariantArrayType);
		long tmp=atoi(GPC.m_View->InputBuffer2);
//			if (tmp<0)
		ret=tmp;
	}

	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

void CGP_TermDoc::OLENamedDataDelete(LPCTSTR Name)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	CString lStr(Name);
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'NamedDataDelete'",lStr);
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'NamedDataDelete' when executing TCL",lStr);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'NamedDataDelete' when executing SUB",lStr);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'NamedDataDelete'",lStr);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'NamedDataDelete'",lStr);

	AnsiToDosMB((LPCTSTR)lStr,lStr,0);

	char str[250];
	sprintf(str,"%s%s%c%s",m_D3OlePrefix,"DNDATA",0xFE,(LPCTSTR)lStr);
	GPC.WaitFor_m_MuteProc();
	LastResult=-123456;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

void CGP_TermDoc::OLENamedDataReset()
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'NamedDataReset'","");
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'NamedDataReset' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'NamedDataReset' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'NamedDataReset'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'NamedDataReset'","");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	char str[250];
	sprintf(str,"%s%s",m_D3OlePrefix,"RNDATA");
	GPC.WaitFor_m_MuteProc();
	LastResult=-123456;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}

void CGP_TermDoc::OnUpdateDlgpickdata(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GPC.AdmIsOn);
}

void CGP_TermDoc::GPOLEDeletePickItem(LPCTSTR FileName, LPCTSTR ItemKey)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	CString FName(FileName);
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'DeletePickItem'",FName);
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'DeletePickItem' when executing TCL",FName);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'DeletePickItem' when executing SUB",FName);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'DeletePickItem'",FName);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'DeletePickItem'",FName);

	AnsiToDosMB((LPCTSTR)FName,FName,0);
	CString IName(ItemKey);
	AnsiToDosMB((LPCTSTR)IName,IName,0);

	char str[550];
	sprintf(str,"%s%s%c%s%c%s",m_D3OlePrefix,"DPITEN",0xFE,(LPCTSTR)FName,0xFE,(LPCTSTR)IName);
	GPC.WaitFor_m_MuteProc();
	LastResult=-123456;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
	m_Comm.GPSendBlock(str,(int)strlen(str));
	m_Comm.GPSendBlock("\r",1);
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
}


UINT CGP_TermDoc::EnableDialogs(BOOL bEnable)
{
	UINT ret=0;
	int i;
	for(i=0;i<MAX_OBJDLG;i++)
		if (a_GPObjType[i]==0)
		{
			if (a_GPObjDialog[i]!=NULL)
			{
				a_GPObjDialog[i]->EnableWindow(bEnable);
				ret++;
			}
		}
		else
		{
			if (a_GPObjFrame[i]!=NULL)
			{
				a_GPObjFrame[i]->EnableWindow(bEnable);
				ret++;
			}
		}
	return ret;
}

long CGP_TermDoc::GPOLEReadVCUFromPICKEx(long FileHandler, const VARIANT FAR& nItem, const VARIANT FAR& Attributes, VARIANT FAR* RetArray)
{
	m_LockPICKItem=1;
	long ret=GPOLEReadVCFromPICKEx(FileHandler, nItem, Attributes, RetArray);
	m_LockPICKItem=0;
	return ret;
}

long CGP_TermDoc::GPOLEReadVCFromPICKEx(long FileHandler, const VARIANT FAR& nItem, const VARIANT FAR& Attributes, VARIANT FAR* RetArray)
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ReadVCFromPICKEx'","");
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReadVCFromPICKEx' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReadVCFromPICKEx' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ReadVCFromPICKEx'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ReadVCFromPICKEx'","");

	if (FileHandler<=0)
	{
		char tmps[10];
		sprintf(tmps,"%d",FileHandler);
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Bad file handler in 'ReadVCFromPICKEx'",tmps);
	}

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNTimesServerRead++;
	CString Keys("");
	CString Attr("");
	long ret=-1;
	int num=0;

    char delimstr11[]={0xFD,0x00,};
	ConvVariantToString(nItem, Keys, "\x7F");
	ConvVariantToString(Attributes, Attr, delimstr11);

	if ((V_VT(&nItem)&VT_ARRAY)!=VT_ARRAY &&
			(V_VT(&nItem) != (VT_VARIANT|VT_BYREF) || (V_VT(nItem.pvarVal)&VT_ARRAY) != VT_ARRAY))
		if ((V_VT(&nItem)&0xFF)==VT_I2 || (V_VT(&nItem)&0xFF)==VT_I4) num=2;
			else num=1;

	if (Keys!="")
	{
		AnsiToDosMB((LPCTSTR)Keys,Keys,0);
		char str[150];
		sprintf(str,"%sPR%sFILEVCEX%c%d%c%d%c%s",m_D3OlePrefix,(m_LockPICKItem==0)?"":"U",0xFE,FileHandler,0xFE,num,0xFE,(LPCSTR)Attr);

	GPC.WaitFor_m_MuteProc();
		if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
		m_Comm.GPSendBlock(str,(int)strlen(str));
		m_Comm.GPSendBlock("\r",1);
		LastResult=-123456;
		if ((Keys.GetLength()%30000)==0 && Keys.GetLength()!=0)		Keys+=BLOCK_STR;
		m_Comm.GPSendBlock((LPCTSTR)Keys,Keys.GetLength());
		m_Comm.GPSendBlock("\r",1);

		int i;
		for(i=0;i<m_waitCountFRead;i++)
		{
			if (GPC.m_View->DoAdditionalMessageLoop()<0)
			{
				GPC.Release_m_MuteProc();
				GPC.m_ErrReport.GPWriteErrorLog2("COM", "'ReadVCFromPICKEx' aborted","");
				return  -13;
			}
			GPC.m_View->DoRemappingInput();
			if (LastResult==-123456) Sleep(m_waitTimeFRead);
			else break;
		}
		if (i>=m_waitCountFRead)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'ReadVCFromPICKEx'","");
		if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();

		if (LastResult!=-123456)
		{
			DosToAnsi(GPC.m_View->InputBuffer2);
			CString delim("\x7F");
			char *pos=strchr(GPC.m_View->InputBuffer2,'#');
			if ((pos++)==NULL) pos="";
			ret=ConvertToArray(CString(pos),RetArray,delim,m_VariantArrayType);
			if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNItemsServerRead+=ret;
			long tmp=atoi(GPC.m_View->InputBuffer2);
//			if (tmp<0)
				ret=tmp;
		}
	GPC.Release_m_MuteProc();
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::GPOLEReadKVCUFromPICKEx(long FileHandler, const VARIANT FAR& nItem, const VARIANT FAR& Attributes, VARIANT FAR* RetArray, VARIANT FAR* RetKeyArray)
{
	m_LockPICKItem=1;
	long ret=GPOLEReadKVCFromPICKEx(FileHandler, nItem, Attributes, RetArray, RetKeyArray);
	m_LockPICKItem=0;
	return ret;
}

long CGP_TermDoc::GPOLEReadKVCFromPICKEx(long FileHandler, const VARIANT FAR& nItem, const VARIANT FAR& Attributes, VARIANT FAR* RetArray, VARIANT FAR* RetKeyArray)
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ReadKVCFromPICKEx'","");
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReadKVCFromPICKEx' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReadKVCFromPICKEx' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ReadKVCFromPICKEx'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ReadKVCFromPICKEx'","");

	if (FileHandler<=0)
	{
		char tmps[10];
		sprintf(tmps,"%d",FileHandler);
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Bad file handler in 'ReadKVCFromPICKEx'",tmps);
	}

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNTimesServerRead++;
	CString Keys("");
	CString Attr("");
	long ret=-1;
	int num=0;
    char delimstr11[]={0xFD,0x00,};
	ConvVariantToString(nItem, Keys, "\x7F");
	ConvVariantToString(Attributes, Attr, delimstr11);

	if ((V_VT(&nItem)&VT_ARRAY)!=VT_ARRAY &&
			(V_VT(&nItem) != (VT_VARIANT|VT_BYREF) || (V_VT(nItem.pvarVal)&VT_ARRAY) != VT_ARRAY))
		if ((V_VT(&nItem)&0xFF)==VT_I2 || (V_VT(&nItem)&0xFF)==VT_I4) num=2;
			else num=1;

	if (Keys.GetLength()>0)
	{
		AnsiToDosMB((LPCTSTR)Keys,Keys,0);
		char str[150];
		sprintf(str,"%sPRK%sFILEVCEX%c%d%c%d%c%s",m_D3OlePrefix,(m_LockPICKItem==0)?"":"U",0xFE,FileHandler,0xFE,num,0xFE,(LPCSTR)Attr);

	GPC.WaitFor_m_MuteProc();
		LastResult=-123456;
		if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
		m_Comm.GPSendBlock(str,(int)strlen(str));
		m_Comm.GPSendBlock("\r",1);
		if ((Keys.GetLength()%30000)==0 && Keys.GetLength()!=0)	Keys+=BLOCK_STR;
		m_Comm.GPSendBlock((LPCTSTR)Keys,Keys.GetLength());
		m_Comm.GPSendBlock("\r",1);

		int i;
		for(i=0;i<m_waitCountFRead;i++)
		{
			if (GPC.m_View->DoAdditionalMessageLoop()<0)
			{
				GPC.Release_m_MuteProc();
				GPC.m_ErrReport.GPWriteErrorLog2("COM", "'ReadKVCFromPICKEx' aborted","");
				return  -13;
			}
			GPC.m_View->DoRemappingInput();
			if (LastResult==-123456) Sleep(m_waitTimeFRead);
			else break;
		}
		if (i>=m_waitCountFRead)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'ReadKVCFromPICKEx'","");
		if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();

		if (LastResult!=-123456)
		{
			DosToAnsi(GPC.m_View->InputBuffer2);
			CString delim("\x7F");
			char *pos=strchr(GPC.m_View->InputBuffer2,'#');
			char *poskey=NULL;
			if (pos!=NULL)
			{
				pos++;
				poskey=strchr(pos,0x05);
				if (poskey!=NULL) *(poskey++)=0;
				ret=ConvertToArray(CString(pos),RetArray,delim,m_VariantArrayType);
				if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNItemsServerRead+=ret;
				ConvertToArray(CString(poskey),RetKeyArray,delim,m_VariantArrayType);
			}
			else ret=-4;

			long tmp=atoi(GPC.m_View->InputBuffer2);
//			if (tmp<0)
				ret=tmp;
		}
//	else AfxMessageBox("GPOLEReadKVCFromPICKEx");
	GPC.Release_m_MuteProc();
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::GPOLEReadKADUFromPICKEx(LPCTSTR FileName, const VARIANT FAR& nItem, const VARIANT FAR& Attributes, VARIANT FAR* RetArray, VARIANT FAR* RetKeyArray)
{
	m_LockPICKItem=1;
	long ret=GPOLEReadKADFromPICKEx(FileName, nItem, Attributes, RetArray, RetKeyArray);
	m_LockPICKItem=0;
	return ret;
}

long CGP_TermDoc::GPOLEReadKADFromPICKEx(LPCTSTR FileName, const VARIANT FAR& nItem, const VARIANT FAR& Attributes, VARIANT FAR* RetArray, VARIANT FAR* RetKeyArray)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNTimesServerRead++;
	CString Keys("");
	CString Attr("");
	long ret=-1;
	int num=0;

	ConvVariantToString(nItem, Keys, "\x7F");
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ReadKADFromPICKEx'",Keys.Mid(0,100));
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReadKADFromPICKEx' when executing TCL","");
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ReadKADFromPICKEx' when executing SUB","");

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ReadKADFromPICKEx'","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ReadKADFromPICKEx'","");

	ConvVariantToString(Attributes, Attr, "\x7D");

	if ((V_VT(&nItem)&VT_ARRAY)!=VT_ARRAY &&
			(V_VT(&nItem) != (VT_VARIANT|VT_BYREF) || (V_VT(nItem.pvarVal)&VT_ARRAY) != VT_ARRAY))
		if ((V_VT(&nItem)&0xFF)==VT_I2 || (V_VT(&nItem)&0xFF)==VT_I4) num=2;
			else num=1;

	if (Keys.GetLength()>0)
	{
		AnsiToDosMB((LPCTSTR)Keys,Keys,0);
		char str[150];
		sprintf(str,"%sPRK%sFILEDAEX%c%s%c%d%c%s",m_D3OlePrefix,(m_LockPICKItem==0)?"":"U",0xFE,FileName,0xFE,num,0xFE,(LPCSTR)Attr);
		GPC.WaitFor_m_MuteProc();
		LastResult=-123456;
		if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
		m_Comm.GPSendBlock(str,(int)strlen(str));
		m_Comm.GPSendBlock("\r",1);
		if ((Keys.GetLength()%30000)==0 && Keys.GetLength()!=0)	Keys+=BLOCK_STR;
		m_Comm.GPSendBlock((LPCTSTR)Keys,Keys.GetLength());
		m_Comm.GPSendBlock("\r",1);

		int i;
		for(i=0;i<m_waitCountFRead;i++)
		{
			if (GPC.m_View->DoAdditionalMessageLoop()<0)
			{
				GPC.Release_m_MuteProc();
				GPC.m_ErrReport.GPWriteErrorLog2("COM", "'ReadKADFromPICKEx' aborted","");
				return  -13;
			}

			GPC.m_View->DoRemappingInput();
			if (LastResult==-123456) Sleep(m_waitTimeFRead);
			else break;
		}
		if (i>=m_waitCountFRead)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'ReadKADFromPICKEx'","");
		if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();

		if (LastResult!=-123456)
		{
			DosToAnsi(GPC.m_View->InputBuffer2);
			CString delim("\x7F");
			char *pos=strchr(GPC.m_View->InputBuffer2,'#');
			char *poskey=NULL;
			if (pos!=NULL)
			{
				pos++;
				poskey=strchr(pos,0x05);
				if (poskey!=NULL) *(poskey++)=0;
				ret=ConvertToArray(CString(pos),RetArray,delim,m_VariantArrayType);
				if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNItemsServerRead+=ret;
				ConvertToArray(CString(poskey),RetKeyArray,delim,m_VariantArrayType);
			}
			else ret=-4;

			long tmp=atoi(GPC.m_View->InputBuffer2);
//			if (tmp<0)
				ret=tmp;
		}
	GPC.Release_m_MuteProc();
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::GPOLESMMCmd(LPCTSTR SMMCommand, long lFlags, VARIANT FAR* RetArray)
{
	long ret=0;
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	CString tmp;
	tmp.Format("%d\x7F",lFlags);
	tmp+=SMMCommand;

	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'SMMCmd'",tmp);
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'SMMCmd' when executing TCL",tmp);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'SMMCmd' when executing SUB",tmp);

	if (GPC.GetOUTTCLLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'SMMCmd'",tmp);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'SMMCmd'",tmp);

	GPC.WaitFor_m_MuteProc();

	m_Comm.GPSendBlock(m_D3OlePrefix,5);
	m_Comm.GPSendBlock("SMMCMD\xFE",7);

	AnsiToDosMB(tmp,tmp,0);
	m_Comm.GPSendLine((LPCTSTR)tmp);
	m_Comm.GPSendBlock("\r",1);
	if ((lFlags&1))
	{
		ret=-1;
		if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartServer();
		int i;
		LastResult=-123456;
		for(i=0;i<m_waitCountFOther;i++)
		{
			if (GPC.m_View->DoAdditionalMessageLoop()<0)
			{
				GPC.Release_m_MuteProc();
				GPC.m_ErrReport.GPWriteErrorLog2("COM", "'SMMCmd' aborted","");
				return  -13;
			}
			GPC.m_View->DoRemappingInput();
			if (LastResult==-123456) Sleep(m_waitTimeFOther);
			else break;
		}
		if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndServer();
		if (i>=m_waitCountFOther)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "The waiting time has expired 'SMMCmd'","");

		if (LastResult!=-123456)
		{
			ret=atoi(DosToAnsi(GPC.m_View->InputBuffer2));
			CString delim("\x1");
			char *pos=strchr(GPC.m_View->InputBuffer2,'#');
			if ((pos++)==NULL) pos="";
			ConvertToArray(CString(pos),RetArray,delim,m_VariantArrayType);
			if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_OLE.dwNItemsServerRead+=ret;
		}
	}
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::GPOLEExecListTab(LPCTSTR ListTabParam)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartTCL();
	CString tmp="ListTab ";
	tmp+=ListTabParam;
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'ExecListTab'",tmp);
	if (GPC.m_WaitTCL || GPC.m_WaitEndTCL || GPC.m_WaitSUB || GPC.m_WaitEndSUB)
		if (GPC.m_WaitTCL || GPC.m_WaitEndTCL)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ExecListTab' when executing TCL",tmp);
		else
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'ExecListTab' when executing SUB",tmp);

	//if (GPC.GetOUTTCLLen())
		//GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty TCL result when call 'ExecListTab'",tmp);

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'ExecListTab'",tmp);


	GPC.m_View->m_TCLvisible=TRUE;
	GPC.ClearOUTTCL();
	GPC.ClearOUTSUB();
	m_waitCountTCL=GPC.m_OLESETTINGS.m_CTCL;

	GPC.m_WaitTCL=TRUE;
	GPC.m_WaitEndTCL=TRUE;

	GPC.WaitFor_m_MuteProc();
	m_Comm.GPSendBlock(m_D3OlePrefix,5);
	m_Comm.GPSendBlock("TCL\xFE",4);

	AnsiToDosMB((LPCTSTR)tmp,tmp,0);
	m_Comm.GPSendLine((LPCTSTR)tmp);
	m_Comm.GPSendBlock("\r",1);
	GPC.Release_m_MuteProc();
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return 0;
}

long CGP_TermDoc::GPOLEGetListTabResult(VARIANT FAR* RetArray, LPCTSTR DelimStr, long RetType)
{
	if (!m_Comm.IsConnected())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Terminal not connected when call 'GetListTabResult'","");
	if (GPC.m_WaitSUB || GPC.m_WaitEndSUB)
			GPC.m_ErrReport.GPWriteErrorLog2("COM", "Call 'GetListTabResult' when executing SUB","");

	if (GPC.GetOUTSUBLen())
		GPC.m_ErrReport.GPWriteErrorLog2("COM", "Not empty SUB result when call 'GetListTabResult'","");
	
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=-10;
	if (--m_waitCountTCL<=0) ret=-1;

	GPC.m_View->DoRemappingInput();

	if (GPC.m_WaitTCL==TRUE) {ret=-9;Sleep(m_waitTimeTCL);}
	else
	{
		ret=(int)strlen(DelimStr);
		char tmps[5];tmps[1]=0;
		CString delim("\rq1w2e3r4");
		if (ret>0)
		{
			long i;
			for(i=0;i<ret;i++)
			{
				tmps[0]=DelimStr[i];
				delim+=tmps;
				if (i<ret-1) delim+="q1w2e3r4";
			}
		}
		else
		{
			tmps[0]=GPC.chDosAnsi[9];
			delim+=tmps;
			delim+="q1w2e3r4";
			long i;
			for(i=0;i<5;i++)
			{
				tmps[0]=GPC.chDosAnsi[253-i];
				delim+=tmps;
				if (i<4) delim+="q1w2e3r4";
			}
		}

		if (GPC.m_WaitEndTCL==TRUE)
		{
			ret=-8;
			if (RetType!=0)
			{
				if (GPC.GetOUTTCLLen()==0) Sleep(m_waitTimeTCL);
				GPC.DosToAnsiOUTTCL();
				StringToArrayEx(GPC.GetOUTTCL(),RetArray,delim);
				GPC.ClearOUTTCL();
			}
		}
		else
		{
			GPC.DosToAnsiOUTTCL();
			ret=StringToArrayEx(GPC.GetOUTTCL(),RetArray,delim);
			GPC.ClearOUTTCL();
			if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndTCL();
		}
	}
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::OLESprFindItem(LPCTSTR SprName, LPCTSTR FindWhat, long nField, long FindFlag, VARIANT FAR* FindItem)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=-1;
	CGPSpr *tmpspr= GPC.m_SprArray.GetSpr(CString(SprName));
	const CString *tmpret=NULL;
	if (tmpspr!=NULL)
		switch(FindFlag)
		{
		case 0: //FindItem
			tmpret=tmpspr->FindItem(nField,CString(FindWhat)); break;
		case 1: //FindItemF
			tmpret=tmpspr->FindItemF(nField,CString(FindWhat)); break;
		case 2: //FindItemExact
			tmpret=tmpspr->FindItemExact(nField,CString(FindWhat)); break;
		case 3: //FindItemExactF
			tmpret=tmpspr->FindItemExactF(nField,CString(FindWhat)); break;
		}

	if (tmpret)
		ret=StringToArrayEx(*tmpret,FindItem,"\x7Fq1w2e3r4\x7");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

long CGP_TermDoc::OLESprFindNextItem(LPCTSTR SprName, LPCTSTR FindWhat, long nField, long FindFlag, VARIANT FAR* FindItem)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleStartMethod();
	long ret=-1;
	CGPSpr *tmpspr= GPC.m_SprArray.GetSpr(CString(SprName));
	const CString *tmpret=NULL;
	if (tmpspr!=NULL)
		switch(FindFlag)
		{
		case 0: //FindNextItem
			tmpret=tmpspr->FindNextItem(nField,CString(FindWhat)); break;
		case 1: //FindNextItemF
			tmpret=tmpspr->FindNextItemF(nField,CString(FindWhat)); break;
		case 2: //FindNextItemExact
			tmpret=tmpspr->FindNextItemExact(nField,CString(FindWhat)); break;
		case 3: //FindNextItemExactF
			tmpret=tmpspr->FindNextItemExactF(nField,CString(FindWhat)); break;
		}

	if (tmpret)
		ret=StringToArrayEx(*tmpret,FindItem,"\x7Fq1w2e3r4\x7");

	if (GPC.DlgStatistics) GPC.DlgStatistics->SOleEndMethod();
	return ret;
}

UINT CGP_TermDoc::FindObject(HWND im_hWnd, GPUNITINFO &iUi)
{
	UINT ret=0;
	iUi.hWnd=0;
	iUi.hWnd2=0;
	iUi.IdDlg=0;
	iUi.IdDlg2=0;
	iUi.IdObj=0;
	iUi.IdObj2=0;
	iUi.ObjName="";
	iUi.ObjType=0;
	iUi.ObjType2=0;

	UINT nScrDlg,nId;
	GPUnit *gputmp=NULL;


	if(GPC.m_hViewWnd==im_hWnd)
	{
		ret=0x40000;
		if (aGPScreen[0]->GPGetWindowByNum(0)->GetUnitById(0))
				aGPScreen[0]->GPGetWindowByNum(0)->GetUnitById(0)->GetUnitInfo(iUi);
	}

	for(nScrDlg=0;nScrDlg<MAX_OBJDLG && ret==0;nScrDlg++)
	{
		if (a_GPObjDialog[nScrDlg])
		{
			UINT nMax=(*a_GPObjDialog[nScrDlg]->GPU)->m_NGPUNIT;
			for(nId=0;nId<nMax && ret==0;nId++)
			{
				gputmp=a_GPObjDialog[nScrDlg]->GetUnit(nId);
				if (gputmp && gputmp->UnitHWND==im_hWnd)
				{
					gputmp->GetUnitInfo(iUi);
					ret=0x10000+iUi.IdObj;
				}
			}
		}
		else
		if (a_GPObjFrame[nScrDlg]!=NULL)
		{
			UINT nMax=(*a_GPObjFrame[nScrDlg]->GPU)->m_NGPUNIT;
			for(nId=0;nId<nMax && gputmp==NULL;nId++)
			{
				gputmp=a_GPObjFrame[nScrDlg]->GetUnit(nId);
				if (gputmp && gputmp->UnitHWND==im_hWnd)
				{
					gputmp->GetUnitInfo(iUi);
					ret=0x20000+iUi.IdObj;
				}
				else gputmp=NULL;
			}
		}
	}

	for(nScrDlg=0;nScrDlg<MAX_SCREEN && ret==0;nScrDlg++)
	{
		if (GetScreenById(nScrDlg)!=NULL)
		{
			GPWindow *w=GetScreenById(nScrDlg)->GPGetWindowById(0);
			if (w)
			{
				GPUnit *u0=w->GetUnitById(0);
				if (u0)
					for(nId=0;nId<u0->m_NGPUNIT && gputmp==NULL;nId++)
					{
						gputmp=w->GetUnitById(nId);
						if (gputmp && gputmp->UnitHWND==im_hWnd)
						{
							gputmp->GetUnitInfo(iUi);
							ret=0x10000+iUi.IdObj;
						}
						else gputmp=NULL;
					}
			}
		}
	}

	return ret;
}

UINT CGP_TermDoc::FindObject(const char *cDlgName, const char *cObjName, GPUNITINFO &iUi)
{

	UINT ret=0;
	iUi.hWnd=0;
	iUi.hWnd2=0;
	iUi.IdDlg=0;
	iUi.IdDlg2=0;
	iUi.IdObj=0;
	iUi.IdObj2=0;
	iUi.ObjName="";
	iUi.ObjType=0;
	iUi.ObjType2=0;

	UINT nDlg=FindDlg(cDlgName);
	if (nDlg<MAX_OBJDLG)
		ret=FindObject(nDlg, cObjName, iUi);
	return ret;
}


UINT CGP_TermDoc::FindObject(UINT uIdDlg, const char *cObjName, GPUNITINFO &iUi)
{

	UINT ret=0;
	iUi.hWnd=0;
	iUi.hWnd2=0;
	iUi.IdDlg=0;
	iUi.IdDlg2=0;
	iUi.IdObj=0;
	iUi.IdObj2=0;
	iUi.ObjName="";
	iUi.ObjType=0;
	iUi.ObjType2=0;

	UINT nId;

	if (uIdDlg<MAX_OBJDLG &&  cObjName && *cObjName)
	{
		GPUnit *gputmp=NULL;

		if (*cObjName>='0' && *cObjName<='9')
		{
			nId=atoi(cObjName);
			gputmp=a_GPObjDialog[uIdDlg]->GetUnit(nId);
		}
		else
		{
			if (a_GPObjDialog[uIdDlg] && a_GPObjDialog[uIdDlg]->GPU && a_GPObjDialog[uIdDlg]->GPU[0])
			{
				UINT nUnits=a_GPObjDialog[uIdDlg]->GPU[0]->m_NGPUNIT;
				for(nId=0;nId<nUnits && gputmp==NULL;nId++)
				{
					gputmp=a_GPObjDialog[uIdDlg]->GetUnit(nId);
					if (gputmp && gputmp->m_ObjName!=cObjName) gputmp=NULL;
				}
			}
			else
			if (a_GPObjFrame[uIdDlg]!=NULL && a_GPObjFrame[uIdDlg]->GPU && a_GPObjFrame[uIdDlg]->GPU[0])
			{
				UINT nUnits=a_GPObjFrame[uIdDlg]->GPU[0]->m_NGPUNIT;
				for(nId=0;nId<nUnits && gputmp==NULL;nId++)
				{
					gputmp=a_GPObjFrame[uIdDlg]->GetUnit(nId);
					if (gputmp && gputmp->m_ObjName!=cObjName) gputmp=NULL;
				}
			}
		}

		if (gputmp)
		{
			gputmp->GetUnitInfo(iUi);
			ret=1;
		}

	}
	return ret;
}


HWND CGP_TermDoc::GetDlgHWND(DWORD dwDlgId)
{
	HWND ret=NULL;
	if (dwDlgId<MAX_OBJDLG)
		if (a_GPObjDialog[dwDlgId]) ret=a_GPObjDialog[dwDlgId]->GPU[0]->UnitHWND;
		else
		if (a_GPObjFrame[dwDlgId]) ret=a_GPObjFrame[dwDlgId]->GPU[0]->UnitHWND;

	return ret;
}


UINT CGP_TermDoc::FindDlg(const char *cDlgName /*cDlgName[1base]*/)
{
	UINT uIdDlg=-1;

	if (cDlgName && *cDlgName)
	{
		if (*cDlgName>='0' && *cDlgName<='9')
		{
			uIdDlg=atoi(cDlgName)-1;
			if (uIdDlg>=MAX_OBJDLG || (a_GPObjDialog[uIdDlg]==NULL && a_GPObjFrame[uIdDlg]==NULL)) uIdDlg=-1;
		}
		else
		{
			GPUnit *gputmp=NULL;
			for(uIdDlg=0;uIdDlg<MAX_OBJDLG && gputmp==NULL;uIdDlg++)
			{
				if (a_GPObjDialog[uIdDlg]!=NULL)
				{
					gputmp=a_GPObjDialog[uIdDlg]->GetUnit(0);
					if (gputmp && gputmp->m_ObjName!=cDlgName) gputmp=NULL;
				}
				else
				if (a_GPObjFrame[uIdDlg]!=NULL)
				{
					gputmp=a_GPObjFrame[uIdDlg]->GetUnit(0);
					if (gputmp && gputmp->m_ObjName!=cDlgName) gputmp=NULL;
				}
			}
			uIdDlg--;
			if (gputmp==NULL) uIdDlg=-1;
		}
	}
	return uIdDlg;
}

char * stristr(const char *s1,const char *s2)
{
	while(*s1)
	{
		if (((*s1^*s2)&0xDF)==0)
		{
			const char *s11=s1;
			const char *s22=s2;
			while(*s11 && *s22 && ((*s11^*s22)&0xDF)==0) s11++,s22++;
			if (*s22==0) break;
		}
		s1++;
	}

	return (char *) (*s1?s1:NULL);
}

const CString CGP_TermDoc::GetUnitsInfo(UINT iDlgID)
{
	CString ret="";
	GPUnit **gputmp=NULL;
	BOOL bNeedDelim=FALSE;
	if ((a_GPObjDialog[iDlgID] && (gputmp=a_GPObjDialog[iDlgID]->GPU)) || (a_GPObjFrame[iDlgID] && (gputmp=a_GPObjFrame[iDlgID]->GPU)))
	{
		UINT uIdUnit;
		UINT unUnits=gputmp[0]->m_NGPUNIT;
		for(uIdUnit=0;uIdUnit<unUnits;uIdUnit++)
			if (gputmp[uIdUnit])
				if (bNeedDelim) ret+="\x2"+gputmp[uIdUnit]->UnitInfoToString("\x03");
				else
				{
					 ret=gputmp[uIdUnit]->UnitInfoToString("\x03");
					 bNeedDelim=TRUE;
				}
	}
	return ret;
}

const CString CGP_TermDoc::GetUnitsInfo()
{
	CString ret="";
	BOOL bNeedDelim=FALSE;
	UINT uIdDlg;
	for(uIdDlg=0;uIdDlg<MAX_OBJDLG;uIdDlg++)
		if (a_GPObjDialog[uIdDlg] || a_GPObjFrame[uIdDlg])
			if (bNeedDelim) ret+="\x1"+GetUnitsInfo(uIdDlg);
			else
			{
				 ret=GetUnitsInfo(uIdDlg);
				 bNeedDelim=TRUE;
			}

	return ret;
}

void CGP_TermDoc::OnVariantArrayTypeChanged()
{
	if (m_VariantArrayType) m_VariantArrayType=1;
}

long CGP_TermDoc::GPOConnectCmd(LPCTSTR CmdStr)
{
	long ret=0;
	GPOParseCommandLine(CmdStr);
	GPOLEConnect();
	return ret;
}

long CGP_TermDoc::GPOParseCommandLine(LPCTSTR CmdStr)
{
	long ret=0;
	CString tmps(CmdStr);
	GPC.ParseCommandLine(tmps.Find("-COMMNUM",0)<0?-1:0x7FFFFFF,tmps);
	return ret;
}

GPMenu * CGP_TermDoc::GetDialogGPMenu(DWORD dwDlgId)
{
	GPMenu *ret=NULL;

	if (dwDlgId<MAX_OBJDLG)
	{
		if (a_GPObjDialog[dwDlgId]) ret=a_GPObjDialog[dwDlgId]->DlgGPMenu;
		else
		if (a_GPObjFrame[dwDlgId]) ret=a_GPObjFrame[dwDlgId]->DlgGPMenu;
	}
	return ret;

}
