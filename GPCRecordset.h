#if !defined(AFX_GPCRECORDSET_H__228AD544_3AE6_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_GPCRECORDSET_H__228AD544_3AE6_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPCRecordset.h: interface for the GPCRecordset class.
//
//////////////////////////////////////////////////////////////////////



class GPCRecordset : public CRecordset
{
friend class CGP_TermDoc;
public:
	BOOL m_DosAnsiFlag;
	GPCRecordset(CDatabase* pDatabase);
	DECLARE_DYNAMIC(GPCRecordset)

// Field/Param Data
	//{{AFX_FIELD(GPCRecordset, CRecordset)
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPCRecordset)
	public:
	virtual CString GetDefaultConnect();    // default connection string
	virtual CString GetDefaultSQL();    // default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

public:
// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	int GetFieldIndexByName(const char *name);
	void UpdateFieldsArr();

	static void GetFIString(CODBCFieldInfo &finfo, char *oStrInfo);
	int DoMethod(const char *iMethod, char *oStr);
	CDBVariant a_CDBVariantBM[256]; 
	virtual ~GPCRecordset();
	CODBCFieldInfo a_CODBCFieldInfo[256]; 
	CString a_CStringFieldIn[256]; 
	CString a_CStringFieldOut[256]; 


	CString m_strCourseIDParam;

protected:
	BOOL UpdFieldsArr;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPCRECORDSET_H__228AD544_3AE6_11D4_970E_0080AD863699__INCLUDED_)
