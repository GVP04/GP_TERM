// GPViewInput.h: interface for the GPViewInput class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPVIEWINPUT_H__0A5BB7DA_5DFC_453C_83C9_4827D6F4F634__INCLUDED_)
#define AFX_GPVIEWINPUT_H__0A5BB7DA_5DFC_453C_83C9_4827D6F4F634__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GPScintilla.h"

class GPViewInput : public GPScintilla  
{
// Construction
public:
	GPViewInput(UINT iUnitId);
// Attributes
public:
	GP_RarefiedArr<CString> SeqArray;
	GP_RarefiedArr<CString> SeqArrayAppend;
	DWORD m_dwKeyExecute;
	DWORD m_dwKeySoftBreak;
	DWORD m_dwKeyBreak;
	CString m_csSoftBreakSeq;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GPViewInput)
	public:
		virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
		virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	UINT LoadAppendKeyWords();
	void ExecuteLast();
	void Execute(const char * execstr);
	CString m_csLastExecute;
	void ExecCurent();
	virtual ~GPViewInput();

protected:
	//{{AFX_MSG(GPViewInput)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	// Generated message map functions
	
	DECLARE_MESSAGE_MAP()
private:
	UINT m_SkipVK;
};

#endif // !defined(AFX_GPVIEWINPUT_H__0A5BB7DA_5DFC_453C_83C9_4827D6F4F634__INCLUDED_)

