// SrvrItem.h : interface of the CGP_TermSrvrItem class
//

#if !defined(AFX_SRVRITEM_H__1509E7B7_DD4C_11D3_970D_0080AD863699__INCLUDED_)
#define AFX_SRVRITEM_H__1509E7B7_DD4C_11D3_970D_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGP_TermSrvrItem : public CDocObjectServerItem
{
	DECLARE_DYNAMIC(CGP_TermSrvrItem)

// Constructors
public:
	CGP_TermSrvrItem(CGP_TermDoc* pContainerDoc);

// Attributes
	CGP_TermDoc* GetDocument() const
		{ return (CGP_TermDoc*)CDocObjectServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGP_TermSrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CGP_TermSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRVRITEM_H__1509E7B7_DD4C_11D3_970D_0080AD863699__INCLUDED_)
