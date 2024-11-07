// ErrReport.h: interface for the CErrReport class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ERRREPORT_H__28E83852_50E6_416C_9D03_EDEC90EF9EB6__INCLUDED_)
#define AFX_ERRREPORT_H__28E83852_50E6_416C_9D03_EDEC90EF9EB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GPSpr.h"


#define EL_INDICERROR1		0x00000002
#define EL_INDICERROR2		0x00000004
#define EL_INDICWARNING1	0x00000008
#define EL_INDICWARNING2	0x00000010

#define EL_WRITEERROR1		0x00020000
#define EL_WRITEERROR2		0x00040000
#define EL_WRITEWARNING1	0x00080000
#define EL_WRITEWARNING2	0x00100000


#define EL_INDICWARNINGMASK		EL_INDICWARNING1|EL_INDICWARNING2
#define EL_INDICERRORMASK		EL_INDICERROR1|EL_INDICERROR2
#define EL_INDICMASK		EL_INDICWARNINGMASK|EL_INDICERRORMASK

#define EL_WRITEWARNINGMASK		EL_WRITEWARNING1|EL_WRITEWARNING2
#define EL_WRITEERRORMASK		EL_WRITEERROR1|EL_WRITEERROR2
#define EL_WRITEMASK		EL_WRITEWARNINGMASK|EL_WRITEERRORMASK


class CErrReport  
{
public:
	const char * m_FileName;
	void Init();
	DWORD dwErrorFlag;
	DWORD dwErrorMask;
	void ResetErrorFlag();
	DWORD SetIcon(HWND ihWnd, DWORD dwFlags);
	CErrReport();
	virtual ~CErrReport();
	void GPWriteErrorLog(const char *ccId, const char *iInfo, const char *iInfo2);
	void GPWriteErrorLog2(const char *ccId, const char *iInfo, const char *iInfo2);
	void GPWriteWarnLog(const char *ccId, const char *iInfo, const char *iInfo2);
	void GPWriteWarnLog2(const char *ccId, const char *iInfo, const char *iInfo2);
	HICON hiNormal;
	HICON hiWarn;
private:
	CGPSpr *m_SprErr;
	CGPSpr *m_SprErr2;
	CGPSpr *m_SprWarn;
	CGPSpr *m_SprWarn2;
};

#endif // !defined(AFX_ERRREPORT_H__28E83852_50E6_416C_9D03_EDEC90EF9EB6__INCLUDED_)
