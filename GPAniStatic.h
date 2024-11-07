#if !defined(AFX_GPANISTATIC_H__BF399DC1_62D4_12D4_970E_0080AD863699__INCLUDED_)
#define AFX_GPANISTATIC_H__BF399DC1_62D4_12D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPAniStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GPAniStatic window
// GPAniStatic.h: interface for the GPAniStatic class.
//
//////////////////////////////////////////////////////////////////////


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GPStatic.h"

class GPAniStatic : public GPStatic  
{
	friend class GPUnit;

// Construction
public:
	GPAniStatic(UINT iUnitId);
// Attributes
public:
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPAniStatic)
	public:
	virtual UINT DoMethod(const char *iStr, char *oStr);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
	BOOL m_bMouseOn;
	UINT uDefDuration;
	GPImageList NormalIL;
	GPImageList DisableIL;
	GPImageList HotIL;
	int iDirection;
	int iDisDirection;
	int iHotDirection;
	UINT uNFrame;
	UINT uDisNFrame;
	UINT uHotNFrame;
	UINT uNSeq;
	UINT uDisNSeq;
	UINT uHotNSeq;
	UINT uNDuration;
	UINT uDisNDuration;
	UINT uHotNDuration;
	UINT uCurPos;
	UINT uCurDisPos;
	UINT uCurHotPos;
	UINT uCurXPosPos;
	UINT uCurYPosPos;
	UINT uNXPos;
	UINT uNYPos;
	UINT *uArrDuration;
	UINT *uArrDisDuration;
	UINT *uArrHotDuration;
	UINT *uArrSeq;
	UINT *uArrDisSeq;
	UINT *uArrHotSeq;
	UINT *uArrPosX;
	UINT *uArrPosY;
	virtual ~GPAniStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(GPAniStatic)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	HICON tmpHICON;
};

#endif // !defined(AFX_GPANISTATIC_H__BF399DC1_62D4_12D4_970E_0080AD863699__INCLUDED_)
