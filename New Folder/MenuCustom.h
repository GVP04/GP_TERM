#if !defined(AFX_MENUCUSTOM_H__1F427AB6_1CDF_477F_9C30_BCCE742FDD47__INCLUDED_)
#define AFX_MENUCUSTOM_H__1F427AB6_1CDF_477F_9C30_BCCE742FDD47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MenuCustom.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMenuCustom window
class CMenuCustom
{
// Construction
public:
	CMenuCustom();

// Attributes
public:
	HMENU m_hMenu;
	HMENU m_PopupMenuINIT;
	UINT m_PopupMenuState;
	DWORD m_dwViewType;
	DWORD m_dwMenuStyle;
	CString csMenuName;
	CString csDefContextName;
// Operations
public:

// Implementation
public:
	virtual ~CMenuCustom();

	// Generated message map functions
protected:

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MENUCUSTOM_H__1F427AB6_1CDF_477F_9C30_BCCE742FDD47__INCLUDED_)
