#if !defined(AFX_GPCONTAINER_H__F939F15B_CD8C_4CCB_947E_69AC12D7512B__INCLUDED_)
#define AFX_GPCONTAINER_H__F939F15B_CD8C_4CCB_947E_69AC12D7512B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPContainer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGPContainer window

class CGPContainer : public CWnd
{
// Construction
public:
	CGPContainer();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGPContainer)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGPContainer();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGPContainer)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPCONTAINER_H__F939F15B_CD8C_4CCB_947E_69AC12D7512B__INCLUDED_)
