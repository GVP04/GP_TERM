// GP_TermDoc.h : interface of the CGP_TermDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GP_TERMDOC_H__1509E7B2_DD4C_11D3_970D_0080AD863699__INCLUDED_)
#define AFX_GP_TERMDOC_H__1509E7B2_DD4C_11D3_970D_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GPScreen.h"
#include "GPObjDialog.h"
#include "GPFrameWnd.h"
#include "GPDlgViewMPVar.h"
#include "GPDlgDebug.h"

#define MAX_SCREEN  128
#define MAX_OBJDLG  128

#define N_GPDIRCHANGEINFO  2000
#define N_GPCOPYINFO  100


UINT CommunicateFn(LPVOID pParam);
UINT CommunicateFn2(LPVOID pParam);


class CGP_TermSrvrItem;
class CGPToolTipCtrl;

class CGP_TermDoc : public COleServerDoc
{
friend class CGP_TermView;
friend class CGPTInterface;
friend class GPDlgViewMPVar;
friend class CDlgViewFSMethods;
friend class CODContextArray;
friend UINT CommunicateFn(LPVOID pParam);
friend UINT CommunicateFnIO(LPVOID pParam);
friend UINT CommunicateFn2(LPVOID pParam);

protected: // create from serialization only
	CGP_TermDoc();
	DECLARE_DYNCREATE(CGP_TermDoc)

// Attributes
public:
	CGP_TermSrvrItem* GetEmbeddedItem()
		{ return (CGP_TermSrvrItem*)COleServerDoc::GetEmbeddedItem(); }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGP_TermDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnUpdateDocument();
	virtual void OnDocWindowActivate(BOOL bActivate);
	protected:
	virtual COleServerItem* OnGetEmbeddedItem();
	virtual BOOL SaveModified();
	virtual COleIPFrameWnd* CreateInPlaceFrame(CWnd* pParentWnd);
	//}}AFX_VIRTUAL

// Implementation
public:
	GPMenu * GetDialogGPMenu(DWORD dwDlgId);
	const CString GetUnitsInfo();
	const CString GetUnitsInfo(UINT iDlgID);

	const static char *cArrFSMethods[];
	const static char *cArrFSMethodsParams[];

	UINT DoFileSystemMethod(const char *iStr, char ** oStr);
	UINT FindObject(HWND im_hWnd, GPUNITINFO & iUi);
	UINT FindObject(const char *cDlgName, const char *cObjName, GPUNITINFO & iUi);
	UINT FindObject(UINT uIdDlg, const char *cObjName, GPUNITINFO & iUi);
	UINT FindDlg(const char *cDlgName);
	UINT EnableDialogs(BOOL bEnable);
	GPDlgViewMPVar *DlgMPVars;
	GPDlgDebug *DlgDebug;
	long MPGetVariables(char ** StrVar);
	long UnRegisterGPTermInROT(const char* iStr);
	long IsRegisterInROT(IBindCtx* pBind,IRunningObjectTable* prot,BSTR* iStr);
	long RegisterGPTermInROT(const char* iStr);
	long RevokeGPTermRegisterFromROT();
	BOOL ShowLicDlg;
	CString LastLogs;
	CString ItemKey;
	UINT CurPortNum;
	CString StrLkey;
	void DeleteObjDlg(UINT iIdDlg, BOOL Reply, BOOL bReport);
	void DeleteObjFrame(UINT iIdDlg, BOOL Reply, BOOL bReport);
	void RemoveAllDlg();
	void GPOLEOConvIConv(UINT Type, LPCTSTR iString, LPCTSTR iFormat, BSTR FAR* oString);
	long m_LockPICKItem;
	long LastResult;
	void InitIfNone();
	void GPSetDlgUnitProperty(UINT IdDlg, UINT IdUnit, char *PropetyLine);
	void GPSetScrUnitProperty(UINT IdScr, UINT IdUnit, char *PropetyLine);
	UINT DoAnyMethod(const char *iStr,DWORD iDefObj, CString &oResult);
	UINT DoAnyMethodScript(const char *iStr,DWORD iDefObj, CString &oResult);
	UINT DoObjectMethod(const char *iStr, BOOL iSend);
	UINT DoObjectMethod(const char *iStr, char *oStr, BOOL iSend);
	UINT DoObjectMethodEx(const char *iStr, BOOL iSend);
	GPScreen * GetScreenById(UINT iIdScr);
	GPScreen * GetScreenByNum(UINT iNumScr);
	UINT CreateUnit(char *iProp, HWND pParentWnd);
	void DeleteScrUnit(UINT iScrDlgId,UINT iUnitId, BOOL bReport);
	void DeleteDlgUnit(UINT iScrDlgId,UINT iUnitId, BOOL bReport);
	GPUnit * GetScrUnit(UINT iScrId,UINT iUnitId);
	GPUnit * GetDlgUnit(UINT iDlgId,UINT iUnitId);
	UINT CreateScreen(Size  & iScrSize, UINT ScrId = 0);
	char SetMainScreen(UINT iScrId);
	char SelectScreen(UINT iScrId);
	void DeleteScreen(UINT iScrId);
	UINT GetScreenNum(UINT iScrId);
	int ResizeActiveScr(Size & newsize);
	Size GetActiveScrSize();
	Size GetMainScrSize();			
	GPScreen *GetActiveScreen();
	GPScreen *GetMainScreen();
	GPScreen *ScrPrn;
	GPUnit * TerminalUnit;
	virtual ~CGP_TermDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	UINT		a_GPObjType[MAX_OBJDLG];
	GPFrameWnd	*a_GPObjFrame[MAX_OBJDLG];
	GPObjDialog	*a_GPObjDialog[MAX_OBJDLG];
	GPObjDialog	*a_GPObjDialogDesktop;
//	HANDLE		a_GPObjDialogHn[MAX_OBJDLG];
	HGLOBAL		a_GPObjDialogHG[MAX_OBJDLG];
	GPCOPYINFO	*m_arrGPCOPYINFO[N_GPCOPYINFO];
	GPDIRCHANGEINFO	*m_arrGPDIRCHANGEINFO[N_GPDIRCHANGEINFO];

	HWND GPCOPYHWND;
	CRITICAL_SECTION m_CSCOPYEditor;
private:
//	GPCommonDlg *GPCDlg;
	CDlgDialogEditor *m_CDlgDialogEditor;

protected:
	virtual CDocObjectServer* GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite);
	UINT MainScreen;
	UINT m_ActiveScr;
	GPScreen **aGPScreen;

// Generated message map functions
protected:
	//{{AFX_MSG(CGP_TermDoc)
	afx_msg void OnFileOpen();
	afx_msg void OnFileNew();
	afx_msg void OnDlgpickdata();
	afx_msg void OnUpdateDlgpickdata(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	DECLARE_OLECMD_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CGP_TermDoc)
	long m_waitTimeTCL;
	afx_msg void OnWaitTimeTCLChanged();
	long m_waitTimeSUB;
	afx_msg void OnWaitTimeSUBChanged();
	long m_waitTimeFRead;
	afx_msg void OnWaitTimeFReadChanged();
	long m_waitTimeSystem;
	afx_msg void OnWaitTimeSystemChanged();
	long m_waitTimeMM;
	afx_msg void OnWaitTimeMMChanged();
	long m_waitTimeInput;
	afx_msg void OnWaitTimeInputChanged();
	long m_waitTimeFWrite;
	afx_msg void OnWaitTimeFWriteChanged();
	long m_waitTimeFOther;
	afx_msg void OnWaitTimeFOtherChanged();
	long m_waitCountTCL;
	afx_msg void OnWaitCountTCLChanged();
	long m_waitCountSystem;
	afx_msg void OnWaitCountSystemChanged();
	long m_waitCountSUB;
	afx_msg void OnWaitCountSUBChanged();
	long m_waitCountMM;
	afx_msg void OnWaitCountMMChanged();
	long m_waitCountInput;
	afx_msg void OnWaitCountInputChanged();
	long m_waitCountFWrite;
	afx_msg void OnWaitCountFWriteChanged();
	long m_waitCountFRead;
	afx_msg void OnWaitCountFReadChanged();
	long m_waitCountFOther;
	afx_msg void OnWaitCountFOtherChanged();
	afx_msg OLE_HANDLE GetHWND();
	afx_msg OLE_HANDLE GetHWNDview();
	afx_msg VARIANT GetDelimArray1();
	afx_msg VARIANT GetDelimArray2();
	afx_msg VARIANT GetDelimArray3();
	afx_msg VARIANT GetDelimArray4();
	afx_msg long GetInputEnable();
	afx_msg void SetInputEnable(long nNewValue);
	afx_msg long GPOLESendLine(LPCTSTR iStr);
	afx_msg void GPOLEClose();
	afx_msg long GPOLEConnect();
	afx_msg long GPOLEIsConnected();
	afx_msg void GPOLEExecTCL(LPCTSTR TCLLine);
	afx_msg long GPOLEGetTCLResult(VARIANT FAR* ResArray, long GetFlag);
	afx_msg void GPOLEResetTCLWait();
	afx_msg void GPOLEResetSUBWait();
	afx_msg void GPOLEExecTCLCap(LPCTSTR TCLLine);
	afx_msg long GPOLESendChar(short iChar);
	afx_msg void GPOLESetECHO(short EchoState);
	afx_msg long GPOLEGetInput(VARIANT FAR* ResArray);
	afx_msg void GPOLESetOutputVisibility(short VisType);
	afx_msg long GPOLEGetSubResult(VARIANT FAR* RetArray);
	afx_msg void GPOLEExecSUB(LPCTSTR SubName, VARIANT FAR* ParamArray);
	afx_msg void GPOLETermShow(long ShowType);
	afx_msg long GPOLEOpenPICKFile(LPCTSTR FileName);
	afx_msg void GPOLEClosePICKFile(long FileHandler);
	afx_msg long GPOLEReadFromPICK(long FileHandler, LPCTSTR Key, VARIANT FAR* RetArray);
	afx_msg long GPOLEWriteToPICK(long FileHandler, LPCTSTR Key, const VARIANT FAR& RecArray);
	afx_msg long GPOLEGetActiveList(VARIANT FAR* ListArray);
	afx_msg long GPOLEGetList(LPCTSTR FileName, LPCTSTR ListName, VARIANT FAR* RetArray);
	afx_msg long GPOLESaveList(LPCTSTR FileName, LPCTSTR ListName, VARIANT FAR* ListArray);
	afx_msg long GPOLEReadFromPICKEx(long FileHandler, const VARIANT FAR& nItem, VARIANT FAR* RetArray);
	afx_msg long GPOLEDeleteFromPICKFile(long FileHandler, LPCTSTR Item);
	afx_msg long GPOLEStringToArray(LPCTSTR iString, VARIANT FAR* oArray, LPCTSTR DelimString);
	afx_msg long GPOLECountOccur(LPCTSTR iString, LPCTSTR SubString);
	afx_msg long GPOLEIndexSubString(LPCTSTR iString, LPCTSTR SubString, long Occurence);
	afx_msg long GPOLEItemExist(long FileHandler, LPCTSTR ItemKey);
	afx_msg void GPOLEGetListEx(const VARIANT FAR& TCLLines);
	afx_msg void GPOLEEndMessageMap();
	afx_msg long GPOLEIsMessageMapOn();
	afx_msg long GPOLEWriteVToPICK(long FileHandler, LPCTSTR Key, long nAtribute, LPCTSTR vString);
	afx_msg long GPOLEWriteVToPICKEx(long FileHandler, const VARIANT FAR& KeyArray, const VARIANT FAR& nAttrArray, const VARIANT FAR& ValuesArray);
	afx_msg long GPOLEArrayToString(const VARIANT FAR& iArray, BSTR FAR* oString, LPCTSTR DelimiterString);
	afx_msg long GPOLEWriteToPICKEx(long FileHandler, const VARIANT FAR& KeyArray, const VARIANT FAR& ItemArray);
	afx_msg long GPOLEReadVFromPICK(long FileHandler, LPCTSTR Key, long nAttribute, BSTR FAR* Attribute);
	afx_msg long GPOLEReadVFromPICKEx(long FileHandler, const VARIANT FAR& nItem, long nAttribute, VARIANT FAR* RetArray);
	afx_msg long GPOLEWriteUToPICK(long FileHandler, LPCTSTR Key, const VARIANT FAR& RecArray);
	afx_msg long GPOLEWriteUToPICKEx(long FileHandler, const VARIANT FAR& KeyArray, const VARIANT FAR& ItemArray);
	afx_msg long GPOLEWriteVUToPICK(long FileHandler, LPCTSTR Key, long nAttribute, LPCTSTR vString);
	afx_msg long GPOLEWriteVUToPICKEx(long FileHandler, const VARIANT FAR& KeyArray, const VARIANT FAR& nAttrArray, const VARIANT FAR& ValuesArray);
	afx_msg long GPOLEReadUFromPICK(long FileHandler, LPCTSTR Key, VARIANT FAR* RetArray);
	afx_msg long GPOLEReadUFromPICKEx(long FileHandler, const VARIANT FAR& nItem, VARIANT FAR* RetArray);
	afx_msg long GPOLEReadVUFromPICK(long FileHandler, LPCTSTR Key, long nAttribute, BSTR FAR* Attribute);
	afx_msg long GPOLEReadVUFromPICKEx(long FileHandler, const VARIANT FAR& nItem, long nAttribute, VARIANT FAR* RetArray);
	afx_msg DATE GPOLEGetTimeFromPICK(const VARIANT FAR& PICKTime);
	afx_msg DATE GPOLEGetDateFromPICK(const VARIANT FAR& PICKDate);
	afx_msg long GPOLESetTimeToPICK(DATE iOleDateTime);
	afx_msg long GPOLESetDateToPICK(DATE iOLEDateTime);
	afx_msg long GPOLEReadKFromPICKEx(long FileHandler, const VARIANT FAR& nItem, VARIANT FAR* RetArray, VARIANT FAR* RetKeyArray);
	afx_msg long GPOLEReadKUFromPICKEx(long FileHandler, const VARIANT FAR& nItem, VARIANT FAR* RetArray, VARIANT FAR* RetKeyArray);
	afx_msg long GPOLEReadKVUFromPICKEx(long FileHandler, const VARIANT FAR& nItem, long nAttribute, VARIANT FAR* RetArray, VARIANT FAR* RetKeyArray);
	afx_msg long GPOLEReadKVFromPICKEx(long FileHandler, const VARIANT FAR& nItem, long nAttribute, VARIANT FAR* RetArray, VARIANT FAR* RetKeyArray);
	afx_msg void GPOLEResetActiveList();
	afx_msg long GPOLEConvertToSubArray(VARIANT FAR* ConvArray, LPCTSTR Delimiter);
	afx_msg void GPOLEDoSystem(VARIANT FAR* RetArray, long nSystem);
	afx_msg long GPOLEConvertToSubArrayEx(VARIANT FAR* ConvArray, const VARIANT FAR& DelimiterArray);
	afx_msg long GPOLEStringToArrayEx(LPCTSTR iString, VARIANT FAR* oArray, const VARIANT FAR& DelimitersArray);
	afx_msg void GPOleExecSubEx(LPCTSTR SubName, const VARIANT FAR& ParamArray);
	afx_msg long GPOLEArrayToStringEx(const VARIANT FAR& iArray, BSTR FAR* oString, const VARIANT FAR& DelimArray);
	afx_msg void GPOLEExecTCLEx(const VARIANT FAR& TCLLineArray);
	afx_msg void GPOLEExecTCLCapEx(const VARIANT FAR& TCLLineArray);
	afx_msg void GPOLESetWindowStyle(OLE_HANDLE ihWnd, const VARIANT FAR& RemStyle, const VARIANT FAR& AddStyle, const VARIANT FAR& nFlags);
	afx_msg void GPOLESetWindowStyleEx(OLE_HANDLE ihWnd, const VARIANT FAR& RemStyle, const VARIANT FAR& AddStyle, const VARIANT FAR& nFlags);
	afx_msg void GPOLEReleaseLockedItems(long FileHandler, const VARIANT FAR& Items);
	afx_msg void GPOLEReleaseLockedFile(long FileHandler);
	afx_msg void GPOLEReleaseLocks();
	afx_msg void GPOLEDumpStart();
	afx_msg long GPOLEDumpStop(VARIANT FAR* RetArray);
	afx_msg void GPOLEIConv(LPCTSTR iString, LPCTSTR iFormat, BSTR FAR* oString);
	afx_msg void GPOLEOConv(LPCTSTR iString, LPCTSTR iFormat, BSTR FAR* oString);
	afx_msg long GPOLEArrayDelElement(const VARIANT FAR& iArray, long DelIndex);
	afx_msg long GPOLEArrayInsElement(const VARIANT FAR& iArray, long InsIndex);
	afx_msg long GPOLESelectOpenPickFile(LPCTSTR FileName);
	afx_msg void GPOLESelectPickFile(LPCTSTR FileName);
	afx_msg long GPOLEReadPickFile(LPCTSTR FileName, VARIANT FAR* KeyArray, VARIANT FAR* ItemArray);
	afx_msg void GPOLESortArray(VARIANT FAR* inArray, long Flags);
	afx_msg void GPOLESortArray2(VARIANT FAR* iArrayMaster, VARIANT FAR* iArraySlave, long Flags);
	afx_msg long GPOLEArrayFindExactly( const VARIANT FAR& inArray, const VARIANT FAR& FindWhat, long FindFrom);
	afx_msg long GPOLEArrayFind(const VARIANT FAR& inArray, const VARIANT FAR& FindWhat, long FindFrom);
	afx_msg long GPOLESSelectOpenPickFile(LPCTSTR FileName);
	afx_msg void GPOLESSelectPickFile(LPCTSTR FileName);
	afx_msg long GPOLEReadItem(LPCTSTR FileName, LPCTSTR ItemKey, VARIANT FAR* ItemArray);
	afx_msg long RegisterInROT(BSTR* iStr);
	afx_msg long RevokeFromROT();
	afx_msg long ListMakerAddList(LPCTSTR DestListName, LPCTSTR SrcListName);
	afx_msg long ListMakerAppendList(LPCTSTR DestListName, LPCTSTR SrcList);
	afx_msg long ListMakerSquiseList(LPCTSTR ListName);
	afx_msg long ListMakerDuplicateList(LPCTSTR DestListName, LPCTSTR SrcListName);
	afx_msg long ListMakerUniqueList(LPCTSTR ListName);
	afx_msg long ListMakerSortList(LPCTSTR ListName);
	afx_msg long ListMakerLoadList(LPCTSTR ListName, LPCTSTR FileName);
	afx_msg long ListMakerLoadPickList(LPCTSTR ListName, LPCTSTR FileName, LPCTSTR ItemName);
	afx_msg long ListMakerSavePickList(LPCTSTR ListName, LPCTSTR FileName, LPCTSTR ItemName);
	afx_msg long ListMakerNBeginCont(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2);
	afx_msg long ListMakerBeginCont(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2);
	afx_msg long ListMakerNEndCont(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2);
	afx_msg long ListMakerEndCont(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2);
	afx_msg long ListMakerNContList(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2);
	afx_msg long ListMakerContList(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2);
	afx_msg long ListMakerNMaskList(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2);
	afx_msg long ListMakerMaskList(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2);
	afx_msg long ListMakerXORList(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2);
	afx_msg long ListMakerORList(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2);
	afx_msg long ListMakerANDList(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2);
	afx_msg long ListMakerNOTList(LPCTSTR DestName, LPCTSTR SrcName1, LPCTSTR SrcName2);
	afx_msg long ListMakerGetListInfo(LPCTSTR ListName, VARIANT FAR* ListInfo);
	afx_msg long ListMakerGetListsInfo(VARIANT FAR* ListInfo);
	afx_msg long ListMakerSaveList(LPCTSTR ListName, LPCTSTR FileName);
	afx_msg long ListMakerDeleteList(LPCTSTR ListName);
	afx_msg long ListMakerCreateList(LPCTSTR ListName);
	afx_msg long ListMakerSetListAsArray(LPCTSTR ListName, VARIANT FAR* ListArray);
	afx_msg long ListMakerGetListAsArray(LPCTSTR ListName, VARIANT FAR* ListArray);
	afx_msg long ListMakerGetList(LPCTSTR ListName, BSTR FAR* OutListString);
	afx_msg long ListMakerSetList(LPCTSTR ListName, LPCTSTR iList, short delimiter);
	afx_msg long OLESprGetInfo(LPCTSTR SprName, VARIANT FAR* SprInfo);
	afx_msg long OLESprGetInfos(VARIANT FAR* SprInfos);
	afx_msg long OLESprCreate(LPCTSTR SprName, short nFields);
	afx_msg long OLESprDelete(LPCTSTR SprName);
	afx_msg long OLESprDoSub(LPCTSTR SprName, LPCTSTR MethodName, const VARIANT FAR& Params);
	afx_msg long OLESprDoFn(LPCTSTR SprName, LPCTSTR MethodName, const VARIANT FAR& Params, VARIANT* Result);
	afx_msg long OLESprFillObject(LPCTSTR SprName, OLE_HANDLE hWnd, long ObjType, LPCTSTR FillParam, long FillType);
	afx_msg long OLESprReplaceObject(LPCTSTR SprName, OLE_HANDLE hWnd, long ObjType, LPCTSTR FillParam);
	afx_msg long ListMakerFillObject(LPCTSTR ListName, OLE_HANDLE hWnd, long ObjType, long FillType);
	afx_msg long OLESprFillByDisp(LPCTSTR SprName, LPDISPATCH ObjDispatch, LPCTSTR FillParams, long FillType);
	afx_msg long OLESprFillByArray(LPCTSTR SprName, const VARIANT FAR& KeyArray, long nField, VARIANT FAR* RetArray);
	afx_msg long OLESprReplaceObjectEx(OLE_HANDLE ihWnd, long ObjType, long StartItem, long EndItem, LPCTSTR Params);
	afx_msg long OLESprReplaceByDisp(LPDISPATCH ObjDispatch, long StartItem, long EndItem, LPCTSTR Params);
	afx_msg long OLESprGetItem(LPCTSTR SprName, long ItemId, VARIANT FAR* SprItem);
	afx_msg long OLESprInsertItem(LPCTSTR SprName, long ItemId, const VARIANT FAR& SprItem);
	afx_msg long OLEGetMPVars(VARIANT FAR* MPVarsArr);
	afx_msg long OLEPause(long DelayMS);
	afx_msg long OLEGetCRC16(const VARIANT FAR& inpValue, long PrevSumm);
	afx_msg long OLESprGetValues(LPCTSTR SprName, long nField, VARIANT FAR* SprItem);
	afx_msg void OLESetNextDlgParent(OLE_HANDLE ParentHWND);
	afx_msg long OLESprLoadFromPick(LPCTSTR SprName, LPCTSTR PickFileName, long bReload, LPCTSTR SelectString);
	afx_msg long OLESprSetItem(LPCTSTR SprName, long ItemId, const VARIANT FAR& SprItem);
	afx_msg long OLENamedDataSet(LPCTSTR Name, const VARIANT FAR& Value);
	afx_msg long OLENamedDataGet(LPCTSTR Name, VARIANT FAR* Value);
	afx_msg void OLENamedDataDelete(LPCTSTR Name);
	afx_msg void OLENamedDataReset();
	afx_msg long OLESprGetValuesEx(LPCTSTR SprName, const VARIANT FAR& FieldsArr, VARIANT FAR* SprItems);
	afx_msg void GPOLEDeletePickItem(LPCTSTR FileName, LPCTSTR ItemKey);
	afx_msg long GPOLEReadVCFromPICKEx(long FileHandler, const VARIANT FAR& nItem, const VARIANT FAR& Attributes, VARIANT FAR* RetArray);
	afx_msg long GPOLEReadVCUFromPICKEx(long FileHandler, const VARIANT FAR& nItem, const VARIANT FAR& Attributes, VARIANT FAR* RetArray);
	afx_msg long GPOLEReadKVCFromPICKEx(long FileHandler, const VARIANT FAR& nItem, const VARIANT FAR& Attributes, VARIANT FAR* RetArray, VARIANT FAR* RetKeyArray);
	afx_msg long GPOLEReadKVCUFromPICKEx(long FileHandler, const VARIANT FAR& nItem, const VARIANT FAR& Attributes, VARIANT FAR* RetArray, VARIANT FAR* RetKeyArray);
	afx_msg long GPOLEReadKADFromPICKEx(LPCTSTR FileName, const VARIANT FAR& nItem, const VARIANT FAR& Attributes, VARIANT FAR* RetArray, VARIANT FAR* RetKeyArray);
	afx_msg long GPOLEReadKADUFromPICKEx(LPCTSTR FileName, const VARIANT FAR& nItem, const VARIANT FAR& Attributes, VARIANT FAR* RetArray, VARIANT FAR* RetKeyArray);
	afx_msg long GPOLEExecListTab(LPCTSTR ListTabParam);
	afx_msg long GPOLESMMCmd(LPCTSTR SMMCommand, long lFlags, VARIANT FAR* RetArray);
	afx_msg long GPOLEGetListTabResult(VARIANT FAR* RetArray, LPCTSTR DelimStr, long RetType);
	afx_msg long OLESprFindItem(LPCTSTR SprName, LPCTSTR FindWhat, long nField, long FindFlag, VARIANT FAR* FindItem);
	afx_msg long OLESprFindNextItem(LPCTSTR SprName, LPCTSTR FindWhat, long nField, long FindFlag, VARIANT FAR* FindItem);
	long m_VariantArrayType;
	afx_msg void OnVariantArrayTypeChanged();
	afx_msg long GPOLEConvertToSubArrayNet(const VARIANT FAR& iConvArray, VARIANT FAR* oConvArray, LPCTSTR Delimiter);
	afx_msg void GPOLEExecSUBNet(LPCTSTR SubName,const VARIANT FAR& ParamArray);
	afx_msg long GPOLESaveListNet(LPCTSTR FileName, LPCTSTR ListName, const VARIANT FAR& ListArray);
	afx_msg long ListMakerSetListAsArrayNet(LPCTSTR ListName, const VARIANT FAR& ListArray);
	afx_msg long GPOConnectCmd(LPCTSTR CmdStr);
	afx_msg long GPOParseCommandLine(LPCTSTR CmdStr);
	afx_msg long GPOLEConvertToSubArrayExNet(const VARIANT FAR& ConvArrayIn, VARIANT FAR* ConvArrayOut, const VARIANT FAR& DelimiterArray);
	afx_msg void GPOLESortArrayNet(const VARIANT FAR& iArrayIn, VARIANT FAR* iArrayOut, long Flags);
	afx_msg void GPOLESortArray2Net(const VARIANT FAR& iArrayMasterIn, VARIANT FAR* iArrayMasterOut, const VARIANT FAR& iArraySlaveIn, VARIANT FAR* iArraySlaveOut, long Flags);
	afx_msg long GPOIsScriptOn();
	afx_msg void GPOExecuteScript(LPCTSTR iString);
	afx_msg void GPOAbortScript();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GP_TERMDOC_H__1509E7B2_DD4C_11D3_970D_0080AD863699__INCLUDED_)
