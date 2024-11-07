// CntrItem.h : interface of the CGP_TermCntrItem class
//

#if !defined(AFX_CNTRITEM_H__1509E7BB_DD4C_11D3_970D_0080AD863699__INCLUDED_)
#define AFX_CNTRITEM_H__1509E7BB_DD4C_11D3_970D_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGP_TermDoc;
class CGP_TermView;

class CGP_TermCntrItem : public COleDocObjectItem
{
	DECLARE_SERIAL(CGP_TermCntrItem)

// Constructors
public:
	CGP_TermCntrItem(CGP_TermDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CGP_TermDoc* GetDocument()
		{ return (CGP_TermDoc*)COleDocObjectItem::GetDocument(); }
	CGP_TermView* GetActiveView()
		{ return (CGP_TermView*)COleDocObjectItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGP_TermCntrItem)
	public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();
	protected:
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	virtual BOOL CanActivate();
	//}}AFX_VIRTUAL

// Implementation
public:
	~CGP_TermCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__1509E7BB_DD4C_11D3_970D_0080AD863699__INCLUDED_)
