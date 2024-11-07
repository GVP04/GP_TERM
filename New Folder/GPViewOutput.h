// GPViewOutput.h: interface for the GPViewOutput class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPVIEWOUTPUT_H__9477A9B6_1E54_41E9_848B_4EC75215AC3C__INCLUDED_)
#define AFX_GPVIEWOUTPUT_H__9477A9B6_1E54_41E9_848B_4EC75215AC3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GPScintilla.h"

class GPViewOutput : public GPScintilla  
{
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPViewOutput)
	public:
		virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
		virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

public:
	HWND m_HWNDDuplicateInput;
	DWORD m_DuplicateInputFlag;
	UINT SetTextLengthFromEnd(UINT uNewLen);
	UINT SetTextLengthFromStart(UINT uNewLen);
	UINT GetTextLength();
	GPViewOutput(UINT iUnitId);
	virtual ~GPViewOutput();

protected:
	//{{AFX_MSG(GPViewOutput)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	// Generated message map functions
	
	DECLARE_MESSAGE_MAP()

};

#endif // !defined(AFX_GPVIEWOUTPUT_H__9477A9B6_1E54_41E9_848B_4EC75215AC3C__INCLUDED_)
