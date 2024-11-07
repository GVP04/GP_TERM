#if !defined(AFX_GPANIBUTTON_H__BF399DC1_62D4_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_GPANIBUTTON_H__BF399DC1_62D4_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPAniButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GPAniButton window
// GPAniButton.h: interface for the GPAniButton class.
//
//////////////////////////////////////////////////////////////////////


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GPButton.h"

class GPAniButton : public GPButton  
{
	friend class GPUnit;

// Construction
public:
	GPAniButton(UINT iUnitId);
// Attributes
public:
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPAniButton)
	public:
	virtual UINT DoMethod(const char *iStr, char *oStr);
	//}}AFX_VIRTUAL

// Implementation
public:
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
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
	UINT *uArrDuration;
	UINT *uArrDisDuration;
	UINT *uArrHotDuration;
	UINT *uArrSeq;
	UINT *uArrDisSeq;
	UINT *uArrHotSeq;
	virtual ~GPAniButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(GPAniButton)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
private:
	HICON tmpHICON;
};

#endif // !defined(AFX_GPANIBUTTON_H__BF399DC1_62D4_11D4_970E_0080AD863699__INCLUDED_)
