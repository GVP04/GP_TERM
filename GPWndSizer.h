// GPWndSizer.h: interface for the CGPWndSizer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPWNDSIZER_H__25DF6D5F_907E_4756_A11F_DA89B95EF68B__INCLUDED_)
#define AFX_GPWNDSIZER_H__25DF6D5F_907E_4756_A11F_DA89B95EF68B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//position
#define GPSS_TOP			0x0001
#define GPSS_BOTTOM			0x0002
#define GPSS_LEFT			0x0004
#define GPSS_RIGHT			0x0008
#define GPSS_TLEFT			GPSS_TOP|GPSS_LEFT
#define GPSS_TRIGHT			GPSS_TOP|GPSS_RIGHT
#define GPSS_BLEFT			GPSS_BOTTOM|GPSS_LEFT
#define GPSS_BRIGHT			GPSS_BOTTOM|GPSS_RIGHT
#define GPSS_CENTER			0x0010
#define GPSS_POSITIONMASK	0x00FF

//orientation
#define GPSS_VERTICAL		0x0100
#define GPSS_HORISONTAL		0x0200
#define GPSS_ORIENTATIONMASK	0x0F00

//fill
#define GPSS_INVISIBLE		0x0000
#define GPSS_INVERT			0x1000
#define GPSS_BRUSH			0x2000
#define GPSS_FILLMASK		0xF000

//form
#define GPSS_ROUND			0x00020000
#define GPSS_SQUARE			0x00040000
#define GPSS_ICON			0x00080000
#define GPSS_FORMMASK		0x000F0000

//move
#define GPSS_MOVE			0x00100000
#define GPSS_INSIDE			0x00200000
#define GPSS_MOVEMASK		0x00F00000

class CGPWndSizer : public CWnd  
{
	friend class GPUnit;
	friend class CDlgDrawEdit;
	friend class CGPWndSizerArr;
public:
	const static UINT uNTypes;
	const static char *cArrTypes[];
	const static UINT uArrTypes[];
	UINT SetSizer(const char * iSetStr);
	const CString GetName();
	CString SetName(CString & iNewName);
	CGPWndSizer(HWND iParentHWND, UINT iId);
	virtual ~CGPWndSizer();
	HWND SetSizerIcon(const char *iStr);
	HWND SetSizerRgn(const char *iStr);
	HWND SetSizerBrush(const char *iStr);

private:
	UINT m_clrBkgndSizer;
	CBrush *m_brBkgndSizer;
	LOGBRUSH lbSizer;
	HICON m_HICON;
	CPoint m_StartPoint;
	UINT m_Drag;
	HWND ParentHWND;
	CString m_Name;
	int MinParentSize;
	int MaxParentSize;
	UINT m_Type;
	UINT m_ID;
	int m_Width;
	int m_deltaStart;
	int m_deltaEnd;
	CRect lastRect;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGPWndSizer)
	//}}AFX_VIRTUAL

// Implementation
public:
	void UpdateSizer();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGPWndSizer)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_GPWNDSIZER_H__25DF6D5F_907E_4756_A11F_DA89B95EF68B__INCLUDED_)
/////////////////////////////////////////////////////////////////////////////
// CGPWndSizer window

