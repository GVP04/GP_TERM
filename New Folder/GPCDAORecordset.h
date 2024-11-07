#if !defined(AFX_GPCDAORECORDSET_H__E67FF1C4_412F_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_GPCDAORECORDSET_H__E67FF1C4_412F_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPCDAORecordset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GPCDAORecordset DAO recordset

#pragma warning(disable : 4995)

class GPCDAORecordset : public CDaoRecordset
{
friend class CGP_TermDoc;
public:
	BOOL m_DosAnsiFlag;
	static const UINT nArrFieldAttr;
	static const long siArrFieldAttr[6];
	static const char *cArrFieldAttrName[6];
	static const UINT nArrOpenTbType;
	static const int iArrOpenTbType[6];
	static const char *cArrOpenTbTypeName[6];
	static const UINT nArrFieldType;
	static const short siArrFieldType[13];
	static const char *cArrFieldTypeName[13];
	static const UINT nArrEditMode;
	static const short siArrEditMode[7];
	static const char *siArrEditModeName[7];

	static const char * ReTranslateEditMode(int iType);
	static int TranslateEditMode(const char * iStr);
	static const char * ReTranslateRSType(int iType);
	static int TranslateRSType(const char * iStr);

	static short TranslateFieldType(const char * iStr);
	static const char * ReTranslateFieldType(short iType);
	static long TranslateFieldAttr(const char * iStr);
	static const CString ReTranslateFieldAttr(long iType);

	static void GetFIString(CDaoFieldInfo &finfo, char *oStrInfo);
	static void GetIIString(CDaoIndexInfo &iinfo, char *oStrInfo);

	GPCDAORecordset(CDaoDatabase* pDatabase);
	DECLARE_DYNAMIC(GPCDAORecordset)

// Field/Param Data
	//{{AFX_FIELD(GPCDAORecordset, CDaoRecordset)
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPCDAORecordset)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	virtual void Close();
	//}}AFX_VIRTUAL

public:
// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	BOOL GPOpen(const char *iStr);
	BOOL GPIsOpen();
	int GetFieldIndexByName(const char *name);
	void UpdateFieldsArr();

	int DoMethod(const char *iMethod, char *oStr);
	virtual ~GPCDAORecordset();
	COleVariant a_COleVariantBM[256]; 
	CDaoFieldInfo a_CDAOFieldInfo[256]; 
	CString a_CStringFieldIn[256]; 
	CString a_CStringFieldOut[256]; 

	CString m_strCourseIDParam;

protected:
	BOOL UpdFieldsArr;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPCDAORECORDSET_H__E67FF1C4_412F_11D4_970E_0080AD863699__INCLUDED_)
