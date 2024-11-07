#include "stdafx.h"
#include "GP_term.h"
#include "ProcMonitor.h"
#include "psapi.h"

CProcMonitor::CProcMonitor(CRITICAL_SECTION *i_pCSRemap)
{
	m_pCSRemap=i_pCSRemap;
}

CProcMonitor::~CProcMonitor(void)
{
	SetState(-1,-1,-1,0);
	m_Array.ResetArray();
}

PGPPROCMONITOR CProcMonitor::GetMonitorStruct(DWORD dwProcID, DWORD dwDlgId, DWORD dwScrId)
{
	PGPPROCMONITOR ret=0;
	DWORD i=m_Array.SelectFirst();
	while(i!=0xFFFFFFFF && !ret)
	{
		PGPPROCMONITOR pMonitortmp=m_Array.GetSelected();
		if (pMonitortmp
				&& (dwProcID==0xFFFFFFFF || dwProcID==pMonitortmp->dwProcID)
				&& (dwDlgId==0xFFFFFFFF || dwDlgId==pMonitortmp->dwProcID)
				&& (dwScrId==0xFFFFFFFF || dwScrId==pMonitortmp->dwProcID))
			ret=pMonitortmp;
		else
			i=m_Array.SelectNext();
	}

	return ret;
}

DWORD CProcMonitor::SetState(DWORD dwProcID, DWORD dwDlgId, DWORD dwScrId, DWORD dwState)
{
	DWORD i=m_Array.SelectFirst();

	while(m_Array.GetCount() && i!=0xFFFFFFFF)
	{

		PGPPROCMONITOR pMonitortmp=m_Array.GetSelected();
		if (pMonitortmp
			&& (dwProcID==0xFFFFFFFF || dwProcID==pMonitortmp->dwProcID)
			&& (dwDlgId==0xFFFFFFFF || dwDlgId==pMonitortmp->dwProcID)
			&& (dwScrId==0xFFFFFFFF || dwScrId==pMonitortmp->dwProcID))
		{
			if (pMonitortmp)
			{
				pMonitortmp->dwState=dwState; 
				if ((dwState&0x1)==0) SetEvent(pMonitortmp->m_hEvent);
			}
			if ((dwState&0x1)==0) m_Array.RemoveSelected();
			else i=m_Array.SelectNext();
		}
		else i=m_Array.SelectNext();
	}
	return m_Array.GetCount();
}

DWORD CProcMonitor::ModifyMonitor(GPPROCMONITOR &mMonitor)
{
	DWORD i=m_Array.SelectFirst();

	while(m_Array.GetCount() && i!=0xFFFFFFFF)
	{
		PGPPROCMONITOR pMonitortmp=m_Array.GetSelected();
		if (pMonitortmp
			&& (mMonitor.dwProcID==0xFFFFFFFF || mMonitor.dwProcID==pMonitortmp->dwProcID)
			&& (mMonitor.dwDlgId==0xFFFFFFFF || mMonitor.dwDlgId==pMonitortmp->dwProcID)
			&& (mMonitor.dwScrId==0xFFFFFFFF || mMonitor.dwScrId==pMonitortmp->dwProcID))
		{
			if (pMonitortmp)
			{
				if (mMonitor.dwElapse!=0xFFFFFFFF) pMonitortmp->dwElapse=mMonitor.dwElapse; 
				if (*mMonitor.subName) strcpy(pMonitortmp->subName,mMonitor.subName); 
			}
		}
		i=m_Array.SelectNext();
	}
	return m_Array.GetCount();
}

UINT ProcMonitorThreadFn(void* ipGPPROCMONITOR)
{
	GPPROCMONITOR pgpm=*((PGPPROCMONITOR)ipGPPROCMONITOR);
	pgpm.dwState=1;
	static DWORD cntr;
	pgpm.dwCurId=++cntr;

	pgpm.m_hEvent = CreateEvent( NULL, TRUE, FALSE, NULL);

	char *tmps=new char [20000];
	char *tmps2=tmps;
	tmps2+=sprintf(tmps2,"%c%c%c%cPROCMONITOR%c%s%c%d%c",250,250,60,0x7F,0x7F,pgpm.subName,0x7F,pgpm.dwCurId,0x7F);
	AnsiToDos(tmps,0);

	if (pgpm.dwState)
	{
		((CProcMonitor *)pgpm.lParam)->m_Array[pgpm.dwCurId]=&pgpm;
		

		if (!*pgpm.subName) strcpy(pgpm.subName,"GPTERM.UnknownInputSub");
		DWORD dwElapse=0xFFFF0000;
		DWORD dwWaitStatus=WAIT_TIMEOUT;
		while(pgpm.dwState)
		{

			switch(dwWaitStatus)
			{
			case WAIT_TIMEOUT:
				dwElapse+=100;
				if (dwElapse>=pgpm.dwElapse)
				{
					*tmps2=0;
					dwElapse=0;
					CProcMonitor::GetProcessDescription(pgpm.dwProcID, tmps2);
					if (!atoi(tmps2)) pgpm.dwState=0;
					AnsiToDos(tmps2,0);
					if ((pgpm.dwState&0x2)==0)
					{
						m_Comm.GPSendBlock(tmps,strlen(tmps));
						m_Comm.GPSendBlock("\r",1);
					}
				}
				dwWaitStatus=WaitForSingleObject(pgpm.m_hEvent,100);
				break;
			case WAIT_ABANDONED:
			case WAIT_OBJECT_0:
			case WAIT_FAILED:
			default:
				pgpm.dwState=0;
				break;
			}
		}
		((CProcMonitor *)pgpm.lParam)->m_Array.RemoveItem(pgpm.dwCurId);
	}
	else
	{
		GPC.WaitFor_m_MuteProc();
		sprintf(tmps2,"-1%cCan't open process %d\r",pgpm.dwProcID,0x7F);
		AnsiToDos(tmps2,0);
		m_Comm.GPSendBlock(tmps,strlen(tmps));
		GPC.Release_m_MuteProc();
	}

	delete []tmps;
	CloseHandle(pgpm.m_hEvent);

	return 1;
}

PGPPROCMONITOR CProcMonitor::StartMonitor(GPPROCMONITOR &mMonitor)
{
	PGPPROCMONITOR ret=NULL;
	SetState(mMonitor.dwProcID, mMonitor.dwDlgId, mMonitor.dwScrId,0);
	mMonitor.lParam=(LPARAM)this;
	mMonitor.m_hEvent=NULL;
	AfxBeginThread(ProcMonitorThreadFn,(void*)&mMonitor);
	return &mMonitor;
}

DWORD CProcMonitor::GetProcessDescription(DWORD dwProcID, char *posout)
{
	HANDLE hProc=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, FALSE, dwProcID);
	DWORD dwTypeFlag=0x0001;
	if (!hProc)
	{
		dwTypeFlag^=0x0001;
		hProc=OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcID);
	}
	posout+=sprintf(posout,"%d\x7F",hProc);

	if (hProc) 
	{
		GetProcessDescription(hProc, posout, dwTypeFlag, dwProcID);
		CloseHandle(hProc);
	}
	return (DWORD)hProc;
}
DWORD CProcMonitor::GetProcessDescription(HANDLE hProc, char *posout, DWORD dwTypeFlag, DWORD dwProcID)
{
	DWORD ret=0;
	*posout=0;

	DWORD dwCode=0;
	DWORD dwCode2=0;

	GetExitCodeProcess(hProc,&dwCode);
	ret=dwCode;


#ifdef W_95
#else
	#ifdef W_NT
	#else
		#ifdef W_98
		#else
			#ifdef W_2000
			#else
	dwProcID=GetProcessId(hProc);
			#endif
		#endif
	#endif
#endif


	posout+=sprintf(posout,"%d%c%d%c",dwProcID,0x7F,dwCode,0x7F);

	GetProcessAffinityMask(hProc,&dwCode,&dwCode2);
	posout+=sprintf(posout,"%4.4X\x7F%4.4X\x7F%4.4X\x7F",dwCode,dwCode2,GetPriorityClass(hProc));

	dwCode=0;

#ifdef W_95
#else
	#ifdef W_NT
	#else
		#ifdef W_98
		#else
			#ifdef W_2000
			#else
	GetProcessHandleCount(hProc,&dwCode);
			#endif
		#endif
	#endif
#endif

	posout+=sprintf(posout,"%d\x7F",dwCode);

	IO_COUNTERS ioc={0};
#ifdef W_95
#else
	#ifdef W_NT
	#else
		#ifdef W_98
		#else
	GetProcessIoCounters(hProc,&ioc);
		#endif
	#endif
#endif

	posout+=sprintf(posout,"%I64d\x7F%I64d\x7F%I64d\x7F%I64d\x7F%I64d\x7F%I64d\x7F",
		ioc.ReadOperationCount,ioc.WriteOperationCount,ioc.OtherOperationCount,
		ioc.ReadTransferCount,ioc.WriteTransferCount,ioc.OtherTransferCount);

	BOOL bCode=0;
#ifdef W_95
#else
	#ifdef W_98
	#else
	GetProcessPriorityBoost(hProc,&bCode);
	#endif
#endif
	posout+=sprintf(posout,"%d\x7F%d\x7F%d\x7F",
		bCode,GetGuiResources(hProc,GR_GDIOBJECTS),GetGuiResources(hProc,GR_USEROBJECTS));

#ifdef W_95
		posout+=sprintf(posout,"1901/01/01 00:00:00%c1901/01/01 00:00:00%c1901/01/01 00:00:00%c",0x7F,0x7F,0x7F);
#else
	#ifdef W_98
		posout+=sprintf(posout,"1901/01/01 00:00:00%c1901/01/01 00:00:00%c1901/01/01 00:00:00%c",0x7F,0x7F,0x7F);
	#else
	{
		FILETIME CreationTime, ExitTime, KernelTime, UserTime;
		CreationTime.dwHighDateTime=ExitTime.dwHighDateTime=KernelTime.dwHighDateTime=UserTime.dwHighDateTime=0;
		CreationTime.dwLowDateTime=ExitTime.dwLowDateTime=KernelTime.dwLowDateTime=UserTime.dwLowDateTime=0;
		GetProcessTimes(hProc, &CreationTime, &ExitTime, &KernelTime, &UserTime);

		SYSTEMTIME st={0};
		FileTimeToSystemTime(&CreationTime,&st);
		posout+=sprintf(posout,"%4.4d/%2.2d/%2.2d %2.2d:%2.2d:%2.2d\x7F",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);

		FileTimeToSystemTime(&KernelTime,&st);
		posout+=sprintf(posout,"%d/%2.2d/%2.2d %2.2d:%2.2d:%2.2d\x7F",st.wYear-1601,st.wMonth-1,st.wDay-1,st.wHour,st.wMinute,st.wSecond);

		FileTimeToSystemTime(&UserTime,&st);
		posout+=sprintf(posout,"%d/%2.2d/%2.2d %2.2d:%2.2d:%2.2d\x7F",st.wYear-1601,st.wMonth-1,st.wDay-1,st.wHour,st.wMinute,st.wSecond);
	}
	#endif
#endif
dwCode=dwCode2=0;
#ifdef W_95
#else
	#ifdef W_98
	#else
	GetProcessWorkingSetSize(hProc,&dwCode,&dwCode2);
	#endif
#endif
	posout+=sprintf(posout,"%d\x7F%d\x7F",dwCode,dwCode2);

	bCode=0;
#ifdef W_95
#else
	#ifdef W_NT
	#else
		#ifdef W_98
		#else
			#ifdef W_2000
			#else
	CheckRemoteDebuggerPresent(hProc,&bCode);
			#endif
		#endif
	#endif
#endif
	posout+=sprintf(posout,"%d\x7F",bCode);

	bCode=0;
#ifdef W_95
#else
	#ifdef W_NT
	#else
		#ifdef W_98
		#else
			#ifdef W_2000
			#else
	IsWow64Process(hProc,&bCode);
			#endif
		#endif
	#endif
#endif
	posout+=sprintf(posout,"%d\x7F",bCode);

#ifdef W_95
			posout+=sprintf(posout,"\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F");
#else
	#ifdef W_98
			posout+=sprintf(posout,"\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F");
	#else
		PROCESS_MEMORY_COUNTERS pmc={0};
		pmc.cb=sizeof(PROCESS_MEMORY_COUNTERS);
		if ((dwTypeFlag&0x0001) && GetProcessMemoryInfo(hProc,&pmc,sizeof(PROCESS_MEMORY_COUNTERS)))
			posout+=sprintf(posout,"%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F",
				pmc.PageFaultCount,pmc.PeakWorkingSetSize,pmc.WorkingSetSize,pmc.QuotaPeakPagedPoolUsage,
				pmc.QuotaPagedPoolUsage,pmc.QuotaPeakNonPagedPoolUsage,pmc.QuotaNonPagedPoolUsage,
				pmc.PagefileUsage,pmc.PeakPagefileUsage);
		else
			posout+=sprintf(posout,"\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F");
	#endif
#endif


#ifdef W_95
#else
	#ifdef W_NT
	#else
		#ifdef W_98
		#else
			#ifdef W_2000
			#else
	GetProcessImageFileName(hProc,posout,1024);
			#endif
		#endif
	#endif
#endif

	return ret;
}

#include "Tlhelp32.h"

DWORD CProcMonitor::GetProcList(char *oStr, DWORD dwLen, const char *ccMask)
{
	DWORD ret=0;
	HANDLE hProcessSnap;
	HANDLE hProcess;
	PROCESSENTRY32 pe32;
	DWORD dwPriorityClass;
	pe32.dwSize = sizeof( PROCESSENTRY32 );
	*oStr=0;
	dwLen-=1000;

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	if( hProcessSnap != INVALID_HANDLE_VALUE )
	{
		// Retrieve information about the first process
		if(Process32First(hProcessSnap, &pe32))
		{
			char *posout=oStr;
			do
			{
				BOOL bMatched=TRUE;
				if (ccMask && *ccMask)
				{
					CString msk=ccMask;
					CString fName=pe32.szExeFile;
					msk.MakeUpper();
					fName.MakeUpper();
					bMatched=(fName.Find(msk)>=0);
				}
				if (bMatched)
				{
					ret++;
					if (posout!=oStr) {*(posout++)=0x7F;*posout=0;}
					hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pe32.th32ProcessID);
					dwPriorityClass = 0;
					if (hProcess)
					{
						dwPriorityClass = GetPriorityClass(hProcess);
						CloseHandle(hProcess);
					}
					posout+=sprintf(posout, "%s%c%d%c%d%c%d%c%d%c%d",
						pe32.szExeFile, 0x7, pe32.th32ProcessID, 0x7, pe32.cntThreads, 0x7, 
						pe32.th32ParentProcessID, 0x7, pe32.pcPriClassBase, 0x7, dwPriorityClass);
				}
			} while((DWORD)(posout-oStr)<dwLen && Process32Next(hProcessSnap, &pe32));
		}
		CloseHandle(hProcessSnap);
	}
	return ret;
}

DWORD CProcMonitor::GetProcModulesList(DWORD dwPID, char *oStr, DWORD dwLen)
{
	DWORD ret=0;
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;
	me32.dwSize = sizeof(MODULEENTRY32);
	*oStr=0;
	dwLen-=1000;
	// Take a snapshot of all modules in the specified process.
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	if(hModuleSnap != INVALID_HANDLE_VALUE)
	{
		// Retrieve information about the first module,
		if(Module32First(hModuleSnap, &me32))
		{
			char *posout=oStr;
			// Now walk the module list of the process, and display information about each module
			do
			{
				ret++;
				if (posout!=oStr) {*(posout++)=0x7F;*posout=0;}
				posout+=sprintf(posout,"%s%c%s%c%d%c%d%c%d%c%d%c%d",
						me32.szModule,0x7, me32.szExePath,0x7, me32.th32ProcessID,0x7,
						me32.GlblcntUsage,0x7, me32.ProccntUsage,0x7, (DWORD) me32.modBaseAddr,0x7,
						me32.modBaseSize);
			} while((DWORD)(posout-oStr)<dwLen && Module32Next(hModuleSnap, &me32));
		}
		CloseHandle(hModuleSnap);
	}

	return ret;
}
