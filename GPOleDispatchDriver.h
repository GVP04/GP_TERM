// GPOleDispatchDriver.h: interface for the CGPOleDispatchDriver class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPOLEDISPATCHDRIVER_H__FB0DBA61_DBED_11D4_AB17_004854899618__INCLUDED_)
#define AFX_GPOLEDISPATCHDRIVER_H__FB0DBA61_DBED_11D4_AB17_004854899618__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGPOleDispatchDriver class

class CGPOleDispatchDriver : public COleDispatchDriver  
{
public:
	CGPOleDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CGPOleDispatchDriver(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	virtual ~CGPOleDispatchDriver();

};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPOLEDISPATCHDRIVER_H__FB0DBA61_DBED_11D4_AB17_004854899618__INCLUDED_)
