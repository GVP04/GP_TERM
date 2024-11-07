#pragma once
#include "GP_RarefiedArr.h"

typedef struct _GPPROCMONITOR
{
	char subName[100];
	DWORD dwProcID;
	DWORD dwDlgId;
	DWORD dwScrId;
	DWORD dwElapse;
	DWORD dwFields;
	DWORD dwState;
	DWORD dwCurId;
	LPARAM lParam;
	HANDLE m_hEvent;
} GPPROCMONITOR, *PGPPROCMONITOR;


class CProcMonitor
{
friend UINT ProcMonitorThreadFn(void* ipGPPROCMONITOR);

private:
	GP_RarefiedArr<PGPPROCMONITOR> m_Array;
	CRITICAL_SECTION *m_pCSRemap;
public:
	PGPPROCMONITOR GetMonitorStruct(DWORD dwProcID, DWORD dwDlgId, DWORD dwScrId);
	DWORD SetState(DWORD dwProcID, DWORD dwDlgId, DWORD dwScrId, DWORD dwState);
	PGPPROCMONITOR StartMonitor(GPPROCMONITOR &mMonitor);
	DWORD ModifyMonitor(GPPROCMONITOR &mMonitor);
	
	static DWORD GetProcList(char *oStr, DWORD dwLen, const char *ccMask);
	static DWORD GetProcModulesList(DWORD dwPID, char *oStr, DWORD dwLen);
	static DWORD CProcMonitor::GetProcessDescription(HANDLE hProc, char *posout, DWORD dwTypeFlag, DWORD dwProcID);
	static DWORD CProcMonitor::GetProcessDescription(DWORD dwProcID, char *posout);


	CProcMonitor(CRITICAL_SECTION *i_pCSRemap);
	~CProcMonitor(void);
};
