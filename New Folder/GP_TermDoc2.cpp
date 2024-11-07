#include "stdafx.h"
#include "GP_Term.h"

#include "GP_TermDoc.h"
#include "CntrItem.h"
#include "SrvrItem.h"
#include "GP_TermView.h"
#include "WinEFS.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CGP_TermDoc
DWORD calcCRC16_Type(UINT CRCType, DWORD PrevSumm, BYTE *tmparr, UINT len);
DWORD StringFromToEWExFlag(const char *iOption, DWORD & convOption);
DWORD StringFromToSHTDN_REASON(const char *iOption, DWORD & convOption);

const char *CGP_TermDoc::cArrFSMethods[]={
/*00*/	"CreateHardLink","GetCompressedFileSize","GetDiskFreeSpace","GetDiskFreeSpaceEx","GetLogicalDrives",
/*05*/	"GetLogicalDriveStrings","GetVolumeInformation","SetVolumeLabel","DecryptFile","DuplicateEncryptionInfoFile",
/*10*/	"EncryptFile","EncryptionDisable","EncryptionEnable","FileEncryptionStatus","DeleteVolumeMountPoint",
/*15*/	"FindFirstVolume","FindFirstVolumeMountPoint","FindNextVolume","FindNextVolumeMountPoint","FindVolumeClose",
/*20*/	"FindVolumeMountPointClose","GetVolumeNameForVolumeMountPoint","GetVolumePathName","GetVolumePathNamesForVolumeName","SetVolumeMountPoint",
/*25*/	"AreFileApisANSI","GetTempPath","GetLongPathName","GetTempFileName","GetShortPathName",
/*30*/	"CreateDirectory","SearchPath","SetCurrentDirectory","SetFileApisToANSI","SetFileApisToOEM",
/*35*/	"GetCurrentDirectory","GetBinaryType","DeleteFile","ReplaceFile","RemoveDirectory",
/*40*/	"CreateDirectoryEx","MoveFile","CopyFile","MoveFileEx","GetFileAttributes",
/*45*/	"GetFileAttributesEx","SetFileAttributes","GetDriveType","DefineDosDevice","QueryDosDevice",
/*50*/	"FindFirstFile","FindNextFile","FindClose","FindFirstFileEx","CopyFileEx",
/*55*/	"CancelCopyMove","MoveFileWithProgress","FindFirstChangeNotification","FindCloseChangeNotification","GetArrCRC16",
/*60*/	"ExpandEnvironmentStrings","InitiateSystemShutdown","AbortSystemShutdown","ExitWindows","ExitWindowsEx",
/*65*/	"InitiateSystemShutdownEx","LockWorkStation","FindFiles","FindFilesR","FindImages",
/*70*/	"FindImagesR","GetFileStat","GetMethods",/*"DeviceIoControl"*/"","",
/*75*/	"","","","","",
/*80*/	"","","","","",
/*85*/	"","","","","",
/*90*/	"","","","","",
	};


const char *CGP_TermDoc::cArrFSMethodsParams[]={
/*00*/	"FileName,ExistingFileName","FileName","RootPathName","Disk","",
/*05*/	"","RootPathName","RootPathName,newVolumeName","FileName","SrcFileName,DstFileName,Attributes",
/*10*/	"FileName","DirPath","DirPath","DirPath","VolumeMountPoint",
/*15*/	"nFindId","nFindId,RootPathName","nFindId","nFindId","nFindId",
/*20*/	"nFindId","VolumeMountPoint","FileName","VolumeName","VolumeMountPoint,VolumeName",
/*25*/	"","","ShortPath","PathName,PrefixString,Unique","LongPath",
/*30*/	"Directory","Path,FileName,Extension","CurrentDirectory","","",
/*35*/	"","FileName","FileName","ReplacedFileName,ReplacementFileName,BackupFileName,ReplaceFlags","DirPath",
/*40*/	"TemplateDirectory,NewDirectory","ExistingFileName,NewFileName","ExistingFileName,NewFileName,bFailIfExists","ExistingFileName,NewFileName,Flags","FileName",
/*45*/	"FileName","FileName,Attributes","RootPathName","DeviceName,TargetPath,Flags","DeviceName",
/*50*/	"nFindId,FileNameMask","nFindId","nFindId","nFindId,FileName,InfoLevelId,SearchOp,AdditionalFlags","ExistingFileName,NewFileName,SubRoutine,csCopyFlags,Skip",
/*55*/	"CopyProcId","ExistingFileName,NewFileName,SubRoutine,csMoveFlags,Skip","ExistingPath,bSubTree,FileChangeFlags,Subroutine","Id","CRCType,PrevSumm,DataType,DataArr",
/*60*/	"String","CompName,TimeoutSec,bForceAppsClosed,bRestart;Message","CompName","","Flags,Reason",
/*65*/	"MachineName,Timeout,ForceAppsClosed,RebootAfterShutdown,Reason;lpMessage","","[Attributes],[dtType C A W],[dtStart YYYYMMDDHHmmSS],[dtEnd YYYYMMDDHHmmSS],[nBytesRead];FileName","[Attributes],[dtType C A W],[dtStart YYYYMMDDHHmmSS],[dtEnd YYYYMMDDHHmmSS],[nBytesRead];FileName","[Attributes],[dtType C A W],[dtStart YYYYMMDDHHmmSS],[dtEnd YYYYMMDDHHmmSS],[ILName],[nImage];FileName",
/*70*/	"[Attributes],[dtType C A W],[dtStart YYYYMMDDHHmmSS],[dtEnd],[ILName],[nImage];FileName","FileName","",/*"DevName,IOCtrlCode[;Data]"*/"","",
/*75*/	"","","","","",
/*80*/	"","","","","",
/*85*/	"","","","","",
/*90*/	"","","","","",
	};


DWORD CALLBACK GPCopyProgressRoutine(
  LARGE_INTEGER TotalFileSize,          // file size
  LARGE_INTEGER TotalBytesTransferred,  // bytes transferred
  LARGE_INTEGER StreamSize,             // bytes in stream
  LARGE_INTEGER StreamBytesTransferred, // bytes transferred for stream
  DWORD dwStreamNumber,                 // current stream
  DWORD dwCallbackReason,               // callback reason
  HANDLE hSourceFile,                   // handle to source file
  HANDLE hDestinationFile,              // handle to destination file
  LPVOID lpData                         // from CopyFileEx
)
{
	EnterCriticalSection(&GPC.m_View->m_CSRemap);
	EnterCriticalSection(&GPC.m_Document->m_CSCOPYEditor);
	char *ms=new char [5000];
	char tmps[100];
	*tmps=0;

	GPCOPYINFO * ci=(GPCOPYINFO *)lpData;

	sprintf(ms,"%c%c%d%c%s%c%s%c%s%c%I64d%c%I64d%c%I64d%c%I64d%c%d%c%d%c%d%c%d\r",
		250,
		250,
		54,0xFE,
		ci?(LPCSTR)ci->EventType:"COPYEVENT",0xFE,
		ci?(LPCSTR)ci->SubRoutine:"",0xFE,
		ci?_itoa(ci->IdCopy,tmps,50):"",0xFE,
		TotalFileSize.QuadPart,0xFE,
		TotalBytesTransferred.QuadPart,0xFE,
		StreamSize.QuadPart,0xFE,
		StreamBytesTransferred.QuadPart,0xFE,
		dwStreamNumber,0xFE,
		dwCallbackReason,0xFE,
		(DWORD)hSourceFile,0xFE,
		(DWORD)hDestinationFile
		);

	if (ci && ci->m_EventsEditor && *(ci->m_EventsEditor) && ::IsWindow(*(ci->m_EventsEditor)) && (ci->dwSkip==0 || (ci->dwCurEnter%ci->dwSkip)==0 || TotalFileSize.QuadPart==TotalBytesTransferred.QuadPart))
	{
		char *CallbackStr=new char [5000];
		strcpy(CallbackStr,ms);
		::PostMessage(*(ci->m_EventsEditor),GPM_SETANDDELETESTRING,(WPARAM)CallbackStr,(LPARAM)CallbackStr);
		::PostMessage(*(ci->m_EventsEditor),GPM_SETANDDELETESTRING,0,(LPARAM)"\r\n");
	}

	if (ci) ci->dwCurEnter++;

	m_Comm.GPSendSafeBlock(AnsiToDos(ms,0),(int)strlen(ms));

	delete[] ms;
	LeaveCriticalSection(&GPC.m_Document->m_CSCOPYEditor);
	LeaveCriticalSection(&GPC.m_View->m_CSRemap);

	return ci?ci->ReturnFlag:PROGRESS_CONTINUE;
}

UINT FnCopyEx(LPVOID pParam)
{
	#ifdef W_95
		return 	0;
	#else
		GPCOPYINFO * ci=(GPCOPYINFO *)pParam;
		UINT ret=(UINT)-1;
		if (ci && ci->IdCopy<N_GPCOPYINFO)
		{
			CopyFileEx(
				ci->SrcName, 
				ci->DstName, 
				GPCopyProgressRoutine,
				pParam, 
				&(ci->bCancel),
				ci->dwCopyFlags
				);
			ret=ci->IdCopy;
			if (GPC.m_Document->m_arrGPCOPYINFO[ret])
			{
				EnterCriticalSection(&GPC.m_Document->m_CSCOPYEditor);
					delete GPC.m_Document->m_arrGPCOPYINFO[ret];
					GPC.m_Document->m_arrGPCOPYINFO[ret]=NULL;
				LeaveCriticalSection(&GPC.m_Document->m_CSCOPYEditor);
			}
		}
		return 	ret;
	#endif
}

UINT FnMoveEx(LPVOID pParam)
{
	#ifdef W_95
		return 	0;
	#else
		GPCOPYINFO * ci=(GPCOPYINFO *)pParam;
		UINT ret=(UINT)-1;
		if (ci && ci->IdCopy<N_GPCOPYINFO)
		{
			CopyFileEx(
				ci->SrcName, 
				ci->DstName, 
				GPCopyProgressRoutine,
				pParam, 
				&(ci->bCancel),
				ci->dwCopyFlags
				);
			ret=ci->IdCopy;
			if (GPC.m_Document->m_arrGPCOPYINFO[ret])
			{
				EnterCriticalSection(&GPC.m_Document->m_CSCOPYEditor);
					delete GPC.m_Document->m_arrGPCOPYINFO[ret];
					GPC.m_Document->m_arrGPCOPYINFO[ret]=NULL;
				LeaveCriticalSection(&GPC.m_Document->m_CSCOPYEditor);
			}
		}
		return 	ret;
	#endif
}

UINT FnChangeDir(LPVOID pParam)
{
	int id=-1;
	GPDIRCHANGEINFO * ci=(GPDIRCHANGEINFO *)pParam;
	UINT ret=(UINT)-1;
	if (ci && ci->IdCopy<N_GPDIRCHANGEINFO)
	{
		id=ci->IdCopy;
		if (ci->Handle)
		{
			HANDLE Handle=ci->Handle;
			CString subName=ci->SubRoutine;
			char tmps[250];
			char *evType="";
			BOOL cont=TRUE;
			HWND *m_EventsEditor=ci->m_EventsEditor;
			CString csFilter=GPIOFile::FileNotifChangeToString(ci->m_EventsFilter);
	
			do
			{
				DWORD dwWaitStatus=WaitForSingleObject(Handle,INFINITE);

				switch(dwWaitStatus)
				{
				case WAIT_ABANDONED:
					cont=FALSE;
					evType="WAIT_ABANDONED";
					break;
				case WAIT_OBJECT_0:
					evType="WAIT_OK";
					cont=FindNextChangeNotification(Handle);
					break;
				case WAIT_TIMEOUT:
					evType="WAIT_TIMEOUT";
					cont=FALSE;
					break;
				case WAIT_FAILED:
					evType="WAIT_FAILED";
					cont=FALSE;
					break;
				default:
					evType="WAIT_UNKNOWN";
					cont=FALSE;
					break;
				}

				EnterCriticalSection(&GPC.m_Document->m_CSCOPYEditor);
				EnterCriticalSection(&GPC.m_View->m_CSRemap);

					if (!GPC.m_Document->m_arrGPDIRCHANGEINFO[id]) cont=FALSE;
					if (GPC.m_Document->m_arrGPDIRCHANGEINFO[id] && !GPC.m_Document->m_arrGPDIRCHANGEINFO[id]->bCancel)
					{
						sprintf(tmps,"%c%c%d%c%s%c%s%c%d%c%s%c%s%c%s\r",
							250,
							250,
							54,0xFE,
							"DIRCHANGEEVENT",0xFE,
							(LPCSTR)subName,0xFE,
							id,0xFE,
							evType,0xFE,
							cont?"":"CANCEL",0xFE,
							(LPCSTR)csFilter
							);

						m_Comm.GPSendSafeBlock(tmps,(int)strlen(tmps));

						if (m_EventsEditor && *m_EventsEditor && ::IsWindow(*m_EventsEditor))
						{
							char *CallbackStr=new char [5000];
							strcpy(CallbackStr,tmps);
								::PostMessage(*m_EventsEditor,GPM_SETANDDELETESTRING,(WPARAM)CallbackStr,(LPARAM)CallbackStr);
								::PostMessage(*m_EventsEditor,GPM_SETANDDELETESTRING,0,(LPARAM)"\r\n");
						}
					}
				LeaveCriticalSection(&GPC.m_View->m_CSRemap);
				LeaveCriticalSection(&GPC.m_Document->m_CSCOPYEditor);

			}
			while(cont && GPC.m_Document->m_arrGPDIRCHANGEINFO[id] && !GPC.m_Document->m_arrGPDIRCHANGEINFO[id]->bCancel && GPC.m_Document->m_arrGPDIRCHANGEINFO[id]->Handle);


		}

		ret=ci->IdCopy;
		if (GPC.m_Document->m_arrGPDIRCHANGEINFO[id])
		{
			EnterCriticalSection(&GPC.m_Document->m_CSCOPYEditor);
				delete GPC.m_Document->m_arrGPDIRCHANGEINFO[ret];
				GPC.m_Document->m_arrGPDIRCHANGEINFO[ret]=NULL;
			LeaveCriticalSection(&GPC.m_Document->m_CSCOPYEditor);
		}
	}
	return 	ret;
}

UINT CGP_TermDoc::DoFileSystemMethod(const char *iStr, char **oStr)
{
	BOOL FRet=FALSE;
	static HANDLE findHANDLE_XP[5];
	static HANDLE findHANDLE_SIMPLE[5];

	try
	{
		if (*iStr) 	
		{
			char met[150];
			strncpy(met,iStr,145);
			met[145]=0;
			const char *pos=strchr(iStr,' ');
			if (pos++) *strchr(met,' ')=0;
			else		pos="";	

			int nfunc=0;
			int retint=-123456; 
			int atoipos=atoi(pos);

			if (*met>='0' && *met<='9') nfunc=atoi(met);
			else
			{
				static const char *sccArrMethods[sizeof(CGP_TermDoc::cArrFSMethods)/sizeof(char *)];
				static DWORD scdMethodsId[sizeof(CGP_TermDoc::cArrFSMethods)/sizeof(char *)];
				static DWORD dwnMethods;

				if (!*sccArrMethods)
				{
					for(dwnMethods=0;*CGP_TermDoc::cArrFSMethods[dwnMethods];dwnMethods++)
					{
						sccArrMethods[dwnMethods]=CGP_TermDoc::cArrFSMethods[dwnMethods];
						scdMethodsId[dwnMethods]=dwnMethods;
					}
					qsCharILineAndDWORD(sccArrMethods, scdMethodsId, 0, dwnMethods-1);
					scdMethodsId[dwnMethods]=dwnMethods;
				}
				nfunc=scdMethodsId[FindInSortArrayIC(met, sccArrMethods, dwnMethods)];
			}


			FRet=TRUE;
			if (oStr!=NULL && *oStr && **oStr ) **oStr=0;
			switch(nfunc)
			{
			case 0: /*CreateHardLink*/
				{
					CString FileName,ExistingFileName;
					FileName=ExtractField(pos,1,",");
					ExistingFileName=ExtractField(pos,2,",");
					retint=-1;
					#ifdef W_95
					#else
						#ifdef W_NT
						#else
							#ifdef W_98
							#else
								if (FileName!="" && ExistingFileName!="")
									retint=CreateHardLink(FileName,ExistingFileName,NULL);
							#endif
						#endif
					#endif
				}
				break;
			case 1: /*GetCompressedFileSize*/
				if (oStr)
				{
					#ifdef W_95
					#else
						#ifdef W_98
						#else
							__int64 i6=0;
							DWORD FileSizeHigh=0,FileSizeLow=0;
							FileSizeLow=GetCompressedFileSize(pos,&FileSizeHigh);
							if (*oStr==NULL) *oStr=new char [100];
							**oStr=0;
							i6=FileSizeHigh;
							i6<<=32;
							i6+=FileSizeLow;
							sprintf(*oStr,"%I64d",i6);
						#endif
					#endif

				}
				break;
			case 2: /*GetDiskFreeSpace*/
				if (oStr)
				{
					if (*oStr==NULL) *oStr=new char [100];
					**oStr=0;
					DWORD SectorsPerCluster=0;
					DWORD BytesPerSector=0;
					DWORD NumberOfFreeClusters=0;
					DWORD TotalNumberOfClusters=0;
					retint=GetDiskFreeSpace(pos,&SectorsPerCluster,&BytesPerSector,&NumberOfFreeClusters,&TotalNumberOfClusters);
					sprintf(*oStr,"%d\x7F%d\x7F%d\x7F%d\x7F%d",retint,SectorsPerCluster,BytesPerSector,NumberOfFreeClusters,TotalNumberOfClusters);
				}
				break;
			case 3: /*GetDiskFreeSpaceEx*/
				if (oStr)
				{
					if (*oStr==NULL) *oStr=new char [500];
					**oStr=0;
					ULARGE_INTEGER FreeBytesAvailable;
					ULARGE_INTEGER TotalNumberOfBytes;
					ULARGE_INTEGER TotalNumberOfFreeBytes;
					FreeBytesAvailable.QuadPart=0;
					TotalNumberOfBytes.QuadPart=0;
					TotalNumberOfFreeBytes.QuadPart=0;
					retint=GetDiskFreeSpaceEx(pos,&FreeBytesAvailable,&TotalNumberOfBytes,&TotalNumberOfFreeBytes);
					sprintf(*oStr,"%d\x7F%I64d\x7F%I64d\x7F%I64d",retint,FreeBytesAvailable.QuadPart,TotalNumberOfBytes.QuadPart,TotalNumberOfFreeBytes.QuadPart);
				}
				break;
			case 4: /*GetLogicalDrives*/
				if (oStr)
				{
					if (*oStr==NULL) *oStr=new char [500];
					**oStr=0;
					DWORD drives=GetLogicalDrives();
					DWORD mask=1;
					char *tmp=*oStr;
					int i;
					for(i=0;i<32;i++,mask*=2)
					{
						if (i) *(tmp++)='\x7F';
						*(tmp++)=(drives&mask)?'1':'0';
					}
					*tmp=0;
				}
				break;
			case 5: /*GetLogicalDriveStrings*/
				if (oStr)
				{
					if (*oStr==NULL) *oStr=new char [50000];
					**oStr=0;
					/*DWORD drives=*/GetLogicalDriveStrings(49000,*oStr);
					char *tmp=*oStr;
					while(*tmp || tmp[1])
						if (*tmp==0) *(tmp++)='\x7F';
						else tmp++;
				}
				break;
			case 6: /*GetVolumeInformation*/
				if (oStr)
				{
					if (*oStr==NULL) *oStr=new char [4000];
					**oStr=0;
					char *VolumeNameBuffer=new char [512];
					*VolumeNameBuffer=0;
					char *FileSystemNameBuffer=new char [512];
					*FileSystemNameBuffer=0;

					DWORD VolumeSerialNumber=0;
					DWORD MaximumComponentLength=0;
					DWORD FileSystemFlags=0;
					retint=GetVolumeInformation(
						pos,
						VolumeNameBuffer,
						500,
						&VolumeSerialNumber,
						&MaximumComponentLength,
						&FileSystemFlags,
						FileSystemNameBuffer,
						500
						);

					DWORD flags[]={
						FS_CASE_IS_PRESERVED,FS_CASE_SENSITIVE,FS_UNICODE_STORED_ON_DISK,FS_PERSISTENT_ACLS,FS_FILE_COMPRESSION,
						FS_VOL_IS_COMPRESSED,FILE_NAMED_STREAMS,FILE_READ_ONLY_VOLUME,FILE_SUPPORTS_ENCRYPTION,FILE_SUPPORTS_OBJECT_IDS,
						FILE_SUPPORTS_REPARSE_POINTS,FILE_SUPPORTS_SPARSE_FILES,FILE_VOLUME_QUOTAS,
						};

					char *names[]={
						"FS_CASE_IS_PRESERVED","FS_CASE_SENSITIVE","FS_UNICODE_STORED_ON_DISK","FS_PERSISTENT_ACLS","FS_FILE_COMPRESSION",
						"FS_VOL_IS_COMPRESSED","FILE_NAMED_STREAMS","FILE_READ_ONLY_VOLUME","FILE_SUPPORTS_ENCRYPTION","FILE_SUPPORTS_OBJECT_IDS",
						"FILE_SUPPORTS_REPARSE_POINTS","FILE_SUPPORTS_SPARSE_FILES","FILE_VOLUME_QUOTAS",
						};

					char *flagsstr=new char [500];
					*flagsstr=0;

					UINT i;
					for(i=0;i<13;i++)
						if ((FileSystemFlags&flags[i])==flags[i])
						{
							if (*flagsstr) strcat(flagsstr,"|");
							strcat(flagsstr,names[i]);
						}


					sprintf(*oStr,"%s\x7F%d\x7F%d\x7F%s\x7F%s",
						VolumeNameBuffer,
						VolumeSerialNumber,
						MaximumComponentLength,
						flagsstr,
						FileSystemNameBuffer
						);

					delete[] flagsstr;
					delete[] VolumeNameBuffer;
					delete[] FileSystemNameBuffer;
				}
				break;
			case 7: /*SetVolumeLabel*/
				retint=SetVolumeLabel(	ExtractField(pos,1,","), ExtractField(pos,2,","));
				break;

			#ifdef W_95
			#else
				#ifdef W_NT
				#else
					#ifdef W_98
					#else
						case 8: /*DecryptFile*/
							if (pos)
							{
								char *tmps=new char [(int)strlen(pos)];
								strcpy(tmps,pos);
								DWORD flag=0;
								char *pos2=strchr(tmps,',');
								if (pos2) 
								{
									*(pos2++)=0;
									flag=atoi(pos2);
								}
								retint=DecryptFile(tmps,flag);
								delete [] tmps;
							}
							break;
						case 10: /*EncryptFile*/
							retint=-1;
							if (*pos) retint=EncryptFile(pos);
							break;
						case 11: /*EncryptionDisable*/
						case 12: /*EncryptionEnable*/
							{
								retint=-1;
								CString tmp=pos;
								BSTR tmpbstr=tmp.AllocSysString();
								if (*pos) retint=EncryptionDisable(tmpbstr,nfunc==11);
								::SysFreeString(tmpbstr);
							}
							break;
							case 13: /*FileEncryptionStatus*/
								if (oStr)
								{
									if (*oStr==NULL) *oStr=new char [2000];
									**oStr=0;
									retint=-1;
									CString tmp=pos;
									DWORD Status=0;
									if (*pos) retint=FileEncryptionStatus(tmp,&Status);
									strcpy(*oStr,GPIOFile::FileEncryptStatusToString(Status));
								}
								break;
							case 14: /*DeleteVolumeMountPoint*/
								retint=-1;
								if (*pos) retint=DeleteVolumeMountPoint(pos);
								break;
							case 15: /*FindFirstVolume*/
								retint=-1;
								if (atoipos>=0 && atoipos<=4)
								{
									if (findHANDLE_XP[atoipos]) FindVolumeClose(findHANDLE_XP[atoipos]);
									findHANDLE_XP[atoipos]=NULL;
									if (oStr)
									{
										if (*oStr==NULL) *oStr=new char [2000];
										**oStr=0;
										findHANDLE_XP[atoipos]=FindFirstVolume(*oStr,1500);
									}
								}
								break;
							case 16: /*FindFirstVolumeMountPoint*/
								{
									CString RootPathName=ExtractField(pos,2,",");
									retint=-1;
									if (RootPathName!="" && atoipos>=0 && atoipos<=4)
									{
										if (findHANDLE_XP[atoipos]) FindVolumeClose(findHANDLE_XP[atoipos]);
										findHANDLE_XP[atoipos]=NULL;
										if (oStr)
										{
											if (*oStr==NULL) *oStr=new char [2000];
											**oStr=0;
											findHANDLE_XP[atoipos]=FindFirstVolumeMountPoint(RootPathName,*oStr,1500);
										}
									}
								}
								break;
							case 17: /*FindNextVolume*/
							case 18: /*FindNextVolumeMountPoint*/
								retint=-1;
								if (atoipos>=0 && atoipos<=4 && findHANDLE_XP[atoipos])
								{
									if (oStr)
									{
										if (*oStr==NULL) *oStr=new char [2000];
										**oStr=0;
										if (nfunc==17)
											retint=FindNextVolume(findHANDLE_XP[atoipos],*oStr,1500);
										else
											retint=FindNextVolumeMountPoint(findHANDLE_XP[atoipos],*oStr,1500);
									}
								}
								break;
							case 19: /*FindVolumeClose*/
								retint=-1;
								if (atoipos>=0 && atoipos<=4)
								{
									retint=FindVolumeClose(findHANDLE_XP[atoipos]);
									findHANDLE_XP[atoipos]=NULL;
								}
								break;
							case 20: /*FindVolumeMountPointClose*/
								retint=-1;
								if (atoipos>=0 && atoipos<=4)
								{
									if (findHANDLE_XP[atoipos])
										retint=FindVolumeMountPointClose(findHANDLE_XP[atoipos]);
									else
										retint=-1;
									findHANDLE_XP[atoipos]=NULL;
								}
								break;
							case 21: /*GetVolumeNameForVolumeMountPoint*/
								retint=-1;
								if (*pos && oStr)
								{
									if (*oStr==NULL) *oStr=new char [2000];
									**oStr=0;
									retint=GetVolumeNameForVolumeMountPoint(pos,*oStr,1500);
								}
								break;
							case 22: /*GetVolumePathName*/
								retint=-1;
								if (*pos && oStr)
								{
									if (*oStr==NULL) *oStr=new char [2000];
									**oStr=0;
									retint=GetVolumePathName(pos,*oStr,1500);
								}
								break;
							case 24: /*SetVolumeMountPoint*/
								retint=-1;
								{
									CString s1,s2;
									s1=ExtractField(pos,1,",");
									s2=ExtractField(pos,2,",");
									if (s1!="" & s2!="")
									{
										retint=SetVolumeMountPoint(s1,s2);
									}
								}
							break;
					#endif
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
							case 9: /*DuplicateEncryptionInfoFile*/
								{
									retint=-1;
									CString SrcFileName,DstFileName,Attributes;
									SrcFileName=ExtractField(pos,1,",");
									DstFileName=ExtractField(pos,1,",");
									Attributes=ExtractField(pos,1,",");
									if (SrcFileName!="" && DstFileName!="")
									{
										DWORD dwCreationDistribution=0;
										DWORD dwAttributes=0;
										SECURITY_ATTRIBUTES SecurityAttributes={0};
										SecurityAttributes.nLength=sizeof(SecurityAttributes);
										SecurityAttributes.bInheritHandle=TRUE;
										dwCreationDistribution=GPIOFile::StringToCreationDisposition(Attributes);
										dwAttributes=GPIOFile::StringToFlagsAndAttributes(Attributes);
										BSTR SrcFileN=SrcFileName.AllocSysString();
										BSTR DstFileN=DstFileName.AllocSysString();
										retint=DuplicateEncryptionInfoFile(SrcFileN,DstFileN,dwCreationDistribution,dwAttributes,&SecurityAttributes);
										::SysFreeString(DstFileN);
										::SysFreeString(SrcFileN);
									}
								}
								break;
							case 23: /*GetVolumePathNamesForVolumeName*/
								retint=-1;
								if (*pos && oStr)
								{
									if (*oStr==NULL) *oStr=new char [50000];
									**oStr=0;
									DWORD len=0;
									retint=GetVolumePathNamesForVolumeName(pos,*oStr,49000,&len);
									char *tmp=*oStr;
									tmp[len]=0;
									while((*tmp || tmp[1]) && len--)
										if (*tmp==0) *(tmp++)='\x7F';
										else tmp++;
								}
								break;
						#endif
					#endif
				#endif
			#endif


			case 25: /*AreFileApisANSI*/
				retint=AreFileApisANSI();
				break;
			case 26: /*GetTempPath*/
				if (oStr)
				{
					if (*oStr==NULL) *oStr=new char [5000];
					GetTempPath(4900,*oStr);
				}
				break;
			#ifdef W_95
			#else
				#ifdef W_NT
				#else
					case 27: /*GetLongPathName*/
						retint=-1;
						if (*pos && oStr)
						{
							if (*oStr==NULL) *oStr=new char [2000];
							**oStr=0;
							retint=GetLongPathName(pos,*oStr,1500);
						}
						break;
				#endif
			#endif


			case 29: /*GetShortPathName*/
				retint=-1;
				if (*pos && oStr)
				{
					if (*oStr==NULL) *oStr=new char [2000];
					**oStr=0;
					retint=GetShortPathName(pos,*oStr,1500);
				}
				break;

			case 28: /*GetTempFileName PathName,PrefixString,Unique*/
				retint=-1;
				if (*pos && oStr)
				{
					CString s1,s2,s3;
					s1=ExtractField(pos,1,",");
					s2=ExtractField(pos,2,",");
					s3=ExtractField(pos,3,",");
					if (*oStr==NULL) *oStr=new char [1000];
					**oStr=0;
					retint=GetTempFileName(s1,s2,atoi(s3),*oStr);
				}
				break;
			case 30: /*CreateDirectory*/
				retint=-1;
				if (*pos)
					retint=CreateDirectory(pos,NULL);
				break;
			case 31: /*SearchPath*/
				retint=-1;
				if (*pos && oStr)
				{
					CString Path,FileName,Extension;
					Path=ExtractField(pos,1,",");
					FileName=ExtractField(pos,2,",");
					Extension=ExtractField(pos,3,",");
					if (*oStr==NULL) *oStr=new char [2000];
					**oStr=0;
					char *endpos=NULL;
					retint=SearchPath(Path==""?NULL:(LPCSTR)Path,(LPCSTR)FileName,Extension==""?NULL:(LPCSTR)Extension,1500,*oStr,&endpos);
				}
				break;
			case 32: /*SetCurrentDirectory*/
				retint=-1;
				if (*pos) 
					retint=SetCurrentDirectory(pos);
				break;
			case 33: /*SetFileApisToANSI*/
				SetFileApisToANSI();
				break;
			case 34: /*SetFileApisToOEM*/
				SetFileApisToOEM();
				break;
			case 35: /*GetCurrentDirectory*/
				if (oStr)
				{
					if (*oStr==NULL) *oStr=new char [1000];
					retint=GetCurrentDirectory(990,*oStr);
				}
				break;
			#ifdef W_95
			#else
				#ifdef W_98
				#else
					case 36: /*GetBinaryType*/
						retint=-1;
						if (oStr && *pos)
						{
							DWORD bType;
							retint=GetBinaryType(pos,&bType);
							if (*oStr==NULL) *oStr=new char [1000];
							strcpy(*oStr,GPIOFile::FBinaryTypeToString(bType));
						}
						break;
				#endif
			#endif

			case 37: /*DeleteFile*/
				retint=-1;
				if (*pos)
					retint=DeleteFile(pos);
				break;

			#ifdef W_95
			#else
				#ifdef W_NT
				#else
					#ifdef W_98
					#else
						case 38: /*ReplaceFile*/
							retint=-1;
							if (*pos)
							{
								CString ReplacedFileName,ReplacementFileName,BackupFileName,ReplaceFlags;

								ReplacedFileName=ExtractField(pos,1,",");
								ReplacementFileName=ExtractField(pos,2,",");
								BackupFileName=ExtractField(pos,3,",");
								ReplaceFlags=ExtractField(pos,4,",");

								DWORD dwReplaceFlags=0;
								DWORD Exclude=0;
								DWORD Reserved=0;
								Exclude=atoi(ExtractField(pos,5,","));
								Reserved=atoi(ExtractField(pos,6,","));
								
								if (ReplaceFlags.FindOneOf("TtWwHhUu")>=0)	dwReplaceFlags|=REPLACEFILE_WRITE_THROUGH;
								if (ReplaceFlags.FindOneOf("NnMmSs")>=0)	dwReplaceFlags|=REPLACEFILE_IGNORE_MERGE_ERRORS;

								retint=ReplaceFile(
									(LPCSTR)ReplacedFileName,
									(LPCSTR)ReplacementFileName,
									(LPCSTR)BackupFileName,
									dwReplaceFlags,
									(LPVOID)Exclude,
									(LPVOID)Reserved
									); 
							}
							break;
					#endif
				#endif
			#endif

			case 39: /*RemoveDirectory*/
				retint=-1;
				if (*pos)
					retint=RemoveDirectory(pos);
				break;
			case 40: /*CreateDirectoryEx*/
				retint=-1;
				if (*pos)
				{
					CString TemplateDirectory,NewDirectory;

					TemplateDirectory=ExtractField(pos,1,",");
					NewDirectory=ExtractField(pos,2,",");
					retint=CreateDirectoryEx(TemplateDirectory,NewDirectory,NULL);
				}
				break;
			case 41: /*MoveFile*/
				retint=-1;
				if (*pos)
				{
					CString ExistingFileName,NewFileName;

					ExistingFileName=ExtractField(pos,1,",");
					NewFileName=ExtractField(pos,2,",");
					retint=MoveFile(ExistingFileName,NewFileName);
				}
				break;
			case 42: /*CopyFile*/
				retint=-1;
				if (*pos)
				{
					CString ExistingFileName,NewFileName;

					ExistingFileName=ExtractField(pos,1,",");
					NewFileName=ExtractField(pos,2,",");
					retint=CopyFile(ExistingFileName,NewFileName,atoi(ExtractField(pos,3,",")));
				}
				break;
			#ifdef W_95
			#else
				#ifdef W_98
				#else
					case 43: /*MoveFileEx*/
						retint=-1;
						if (*pos)
						{
							CString ExistingFileName,NewFileName,Flags;

							ExistingFileName=ExtractField(pos,1,",");
							NewFileName=ExtractField(pos,2,",");
							DWORD dwFlags=GPIOFile::StringToFMoveFlag(ExtractField(pos,3,","));

							retint=MoveFileEx(
								(LPCSTR)ExistingFileName,(LPCSTR)NewFileName,dwFlags); 
						}
						break;
					case 48: /*DefineDosDevice*/
						if (*pos)
						{
							CString DeviceName,TargetPath;

							DeviceName=ExtractField(pos,1,",");
							TargetPath=ExtractField(pos,2,",");
							DWORD dwFlags=GPIOFile::StringToDeviceFlag(ExtractField(pos,3,","));
							retint=DefineDosDevice(dwFlags,DeviceName,TargetPath);
						}
						break;
					case 53: /*FindFirstFileEx*/
						if (atoipos>=0 && atoipos<=4)
						{
							if (findHANDLE_SIMPLE[atoipos]) FindClose(findHANDLE_SIMPLE[atoipos]);

							CString FileName,NewFileName,Flags;

							FileName=ExtractField(pos,2,",");
							
							DWORD dwAdditionalFlags=atoi(ExtractField(pos,5,","));
							WIN32_FIND_DATA FindFileData={0};
							findHANDLE_SIMPLE[atoipos]=FindFirstFileEx(
								FileName,
								(_FINDEX_INFO_LEVELS)atoi(ExtractField(pos,3,",")),
								(LPVOID)&FindFileData,
								(_FINDEX_SEARCH_OPS)atoi(ExtractField(pos,4,",")),
								NULL,
								dwAdditionalFlags
								);
						}
						break;
				#endif
			#endif

			case 44: /*GetFileAttributes*/
				retint=-1;
				if (oStr && *pos)
				{
					DWORD FileAttributes;
					FileAttributes=GetFileAttributes(ExtractField(pos,1,","));
					if (*oStr==NULL) *oStr=new char [1000];
					if (FileAttributes!=0xFFFFFFFF)
						strcpy(*oStr,GPIOFile::FileAttributesToString(FileAttributes));
					else
						strcpy(*oStr,"-1");
				}
				break;
		#ifdef W_95
		#else
			case 45: /*GetFileAttributesEx*/
				retint=-1;
				if (oStr && *pos)
				{
					WIN32_FILE_ATTRIBUTE_DATA fa={0};
					retint=GetFileAttributesEx(pos,GetFileExInfoStandard,(LPVOID)&fa);
					if (*oStr==NULL) *oStr=new char [1000];
					strcpy(*oStr,GPIOFile::FA_DATAToString(fa));
				}
				break;
		#endif
			case 46: /*SetFileAttributes*/
				retint=SetFileAttributes(	ExtractField(pos,1,","), GPIOFile::StringToFlagsAndAttributes(ExtractField(pos,2,",")));
				break;
			case 47: /*GetDriveType*/
				retint=-1;
				if (oStr)
				{
					DWORD DriveType=GetDriveType(*pos?pos:NULL);
					if (*oStr==NULL) *oStr=new char [1000];
					strcpy(*oStr,GPIOFile::DriveTypeToString(DriveType));
				}
				break;
		#ifdef W_95
		#else
			case 49: /*QueryDosDevice*/
				if (oStr)
				{
					if (*oStr==NULL) *oStr=new char [20000];
					if (*oStr)
					{
						**oStr=0;
						DWORD len=QueryDosDevice(pos,*oStr,19000);
						char *tmp=*oStr;
						if (len<19000)
						{
							tmp[len]=0;
							while((*tmp || tmp[1]) && len--)
								if (*tmp==0) *(tmp++)='\x7F';
								else tmp++;
						}
					}
				}
				break;
		#endif
			case 50: /*FindFirstFile*/
				if (oStr && *pos && atoipos>=0 && atoipos<=4)
				{
					if (findHANDLE_SIMPLE[atoipos]) FindClose(findHANDLE_SIMPLE[atoipos]);
					WIN32_FIND_DATA fd={0};
					findHANDLE_SIMPLE[atoipos]=FindFirstFile(pos,&fd);
					if (*oStr==NULL) *oStr=new char [1000];
					**oStr=0;
					sprintf(*oStr,"%d\x7F%s",(DWORD)findHANDLE_SIMPLE[atoipos],(LPCSTR)GPIOFile::FF_DATAToString(fd));
				}
				break;
			case 51: /*FindNextFile*/
				retint=-1;
				if (oStr && atoipos>=0 && atoipos<=4 && findHANDLE_SIMPLE[atoipos])
				{
					{
						if (*oStr==NULL) *oStr=new char [1000];
						**oStr=0;
						WIN32_FIND_DATA fd={0};
						retint=FindNextFile(findHANDLE_SIMPLE[atoipos],&fd);
						sprintf(*oStr,"%d\x7F%s",retint,(LPCSTR)GPIOFile::FF_DATAToString(fd));
					}
				}
				break;
			case 52: /*FindClose*/
				if (atoipos>=0 && atoipos<=4 && findHANDLE_SIMPLE[atoipos])
					retint=FindClose(findHANDLE_SIMPLE[atoipos]);
				break;
	#ifdef W_95
	#else
			case 54: /*CopyFileEx*/
				if (*pos)
				{
					CString ExistingFileName,NewFileName,SubRoutine,csCopyFlags,csSkip;

					DWORD dwCopyFlags=0;
					
					ExistingFileName=ExtractField(pos,1,",");
					NewFileName=ExtractField(pos,2,",");
					SubRoutine=ExtractField(pos,3,",");
					csCopyFlags=ExtractField(pos,4,",");
					csSkip=ExtractField(pos,5,",");
					csCopyFlags.MakeUpper();

					if (csCopyFlags.FindOneOf("WDN")>=0) dwCopyFlags|=COPY_FILE_ALLOW_DECRYPTED_DESTINATION;
					if (csCopyFlags.FindOneOf("X")>=0) dwCopyFlags|=COPY_FILE_FAIL_IF_EXISTS;
					if (csCopyFlags.FindOneOf("B")>=0) dwCopyFlags|=COPY_FILE_RESTARTABLE;

					int i;
					for(i=0;i<N_GPCOPYINFO && m_arrGPCOPYINFO[i];i++);

					if (i!=N_GPCOPYINFO) 
					{
						m_arrGPCOPYINFO[i]= new GPCOPYINFO;

						m_arrGPCOPYINFO[i]->EventType="COPYEVENT";
						m_arrGPCOPYINFO[i]->DstName=NewFileName;
						m_arrGPCOPYINFO[i]->SrcName=ExistingFileName;
						m_arrGPCOPYINFO[i]->SubRoutine=SubRoutine;
						m_arrGPCOPYINFO[i]->bCancel=FALSE;
						m_arrGPCOPYINFO[i]->IdCopy=i;
						m_arrGPCOPYINFO[i]->ReturnFlag=PROGRESS_CONTINUE;
						m_arrGPCOPYINFO[i]->m_EventsEditor=&GPCOPYHWND;
						m_arrGPCOPYINFO[i]->dwCopyFlags=dwCopyFlags;
						m_arrGPCOPYINFO[i]->dwSkip=atoi(csSkip);
						if (m_arrGPCOPYINFO[i]->dwSkip==1) m_arrGPCOPYINFO[i]->dwSkip=2;
						m_arrGPCOPYINFO[i]->dwCurEnter=0;
						AfxBeginThread(FnCopyEx,(LPVOID)m_arrGPCOPYINFO[i]);
						retint=i;
					}
					else retint=-1;
				}
				break;
	#endif
			case 55: /*CancelCopyMove*/
				{
					EnterCriticalSection(&GPC.m_Document->m_CSCOPYEditor);
					int iStart=0,iEnd=N_GPCOPYINFO;
					if (*pos && atoipos>=0 && atoipos<N_GPCOPYINFO && ExtractField(pos,1,",")!="") 
					{
						iStart=atoipos;
						iEnd=atoipos+1;
					}
					CString tmps=ExtractField(pos,2,",");
					tmps.MakeUpper();
					for(atoipos=iStart;atoipos<iEnd;atoipos++)
						if (m_arrGPCOPYINFO[atoipos])
						{
							if (tmps.Find("CONTINUE")) m_arrGPCOPYINFO[atoipos]->ReturnFlag=PROGRESS_CONTINUE;
							if (tmps.Find("CANCEL")) m_arrGPCOPYINFO[atoipos]->ReturnFlag=PROGRESS_CANCEL;
							if (tmps.Find("STOP")) m_arrGPCOPYINFO[atoipos]->ReturnFlag=PROGRESS_STOP;
							if (tmps.Find("QUIET")) m_arrGPCOPYINFO[atoipos]->ReturnFlag=PROGRESS_QUIET;
						}
					LeaveCriticalSection(&GPC.m_Document->m_CSCOPYEditor);
				}
				break;
			case 56: /*MoveFileWithProgress*/
				if (*pos)
				{
					CString ExistingFileName,NewFileName,SubRoutine,csCopyFlags,csSkip;

					DWORD dwCopyFlags=0;
					
					ExistingFileName=ExtractField(pos,1,",");
					NewFileName=ExtractField(pos,2,",");
					SubRoutine=ExtractField(pos,3,",");
					csCopyFlags=ExtractField(pos,4,",");
					csSkip=ExtractField(pos,5,",");
					csCopyFlags.MakeUpper();

					if (csCopyFlags.Find("X"/*"REPLACE_EXISTING"*/)>=0) dwCopyFlags|=MOVEFILE_REPLACE_EXISTING;
					if (csCopyFlags.Find("PY"/*"COPY_ALLOWED"*/)>=0) dwCopyFlags|=MOVEFILE_COPY_ALLOWED;
					if (csCopyFlags.Find("BO"/*"DELAY_UNTIL_REBOOT"*/)>=0) dwCopyFlags|=MOVEFILE_DELAY_UNTIL_REBOOT;
					if (csCopyFlags.Find("WR"/*"WRITE_THROUGH"*/)>=0) dwCopyFlags|=MOVEFILE_WRITE_THROUGH;
					if (csCopyFlags.Find("CR"/*"CREATE_HARDLINK"*/)>=0) dwCopyFlags|=MOVEFILE_CREATE_HARDLINK;
					if (csCopyFlags.Find("FA"/*"FAIL_IF_NOT_TRACKABLE"*/)>=0) dwCopyFlags|=MOVEFILE_FAIL_IF_NOT_TRACKABLE;

					int i;
					for(i=0;i<N_GPCOPYINFO && m_arrGPCOPYINFO[i];i++);

					if (i!=N_GPCOPYINFO) 
					{
						m_arrGPCOPYINFO[i]= new GPCOPYINFO;

						m_arrGPCOPYINFO[i]->EventType="MOVEEVENT";
						m_arrGPCOPYINFO[i]->DstName=NewFileName;
						m_arrGPCOPYINFO[i]->SrcName=ExistingFileName;
						m_arrGPCOPYINFO[i]->SubRoutine=SubRoutine;
						m_arrGPCOPYINFO[i]->bCancel=FALSE;
						m_arrGPCOPYINFO[i]->IdCopy=i;
						m_arrGPCOPYINFO[i]->ReturnFlag=PROGRESS_CONTINUE;
						m_arrGPCOPYINFO[i]->m_EventsEditor=&GPCOPYHWND;
						m_arrGPCOPYINFO[i]->dwCopyFlags=dwCopyFlags;
						m_arrGPCOPYINFO[i]->dwSkip=atoi(csSkip);
						if (m_arrGPCOPYINFO[i]->dwSkip==1) m_arrGPCOPYINFO[i]->dwSkip=2;
						m_arrGPCOPYINFO[i]->dwCurEnter=0;
						AfxBeginThread(FnMoveEx,(LPVOID)m_arrGPCOPYINFO[i]);
						retint=i;
					}
					else retint=-1;
				}
				break;
			case 57: /*FindFirstChangeNotification*/
				retint=-1;
				if (*pos)
				{
					int i;
					for(i=0;i<N_GPDIRCHANGEINFO && m_arrGPDIRCHANGEINFO[i];i++);

					if (i!=N_GPDIRCHANGEINFO) 
					{
						retint=i;
						m_arrGPDIRCHANGEINFO[i]= new GPDIRCHANGEINFO;
						m_arrGPDIRCHANGEINFO[i]->IdCopy=i;
						m_arrGPDIRCHANGEINFO[i]->SrcName=ExtractField(pos,1,",");
						m_arrGPDIRCHANGEINFO[i]->m_EventsEditor=&GPCOPYHWND;
						m_arrGPDIRCHANGEINFO[i]->SubRoutine=ExtractField(pos,4,",");
						m_arrGPDIRCHANGEINFO[i]->bCancel=FALSE;
						m_arrGPDIRCHANGEINFO[i]->dwCurEnter=0;
						m_arrGPDIRCHANGEINFO[i]->dwSkip=0;

						CString NotifyFilter=ExtractField(pos,3,","),csSkip;
						
						m_arrGPDIRCHANGEINFO[i]->m_EventsFilter=GPIOFile::StringToFileNotifChange((NotifyFilter=="")?NULL:(LPCSTR)NotifyFilter);
						m_arrGPDIRCHANGEINFO[i]->Handle=FindFirstChangeNotification(m_arrGPDIRCHANGEINFO[i]->SrcName,atoi(ExtractField(pos,2,",")),m_arrGPDIRCHANGEINFO[i]->m_EventsFilter);
						if (m_arrGPDIRCHANGEINFO[i]->Handle==INVALID_HANDLE_VALUE) m_arrGPDIRCHANGEINFO[i]->Handle=NULL;

						if (m_arrGPDIRCHANGEINFO[i]->Handle==NULL)
						{
							delete m_arrGPDIRCHANGEINFO[i];
							m_arrGPDIRCHANGEINFO[i]=NULL;
							retint=-1;
						}
						else 
							AfxBeginThread(FnChangeDir,(LPVOID)m_arrGPDIRCHANGEINFO[i]);
					}
				}
				break;
			case 58: /*FindCloseChangeNotification*/
				{
					EnterCriticalSection(&GPC.m_Document->m_CSCOPYEditor);
					int iStart=0,iEnd=N_GPDIRCHANGEINFO;
					if (*pos && atoipos>=0 && atoipos<N_GPDIRCHANGEINFO && ExtractField(pos,1,",")!="") 
					{
						iStart=atoipos;
						iEnd=atoipos+1;
					}
					CString tmps=ExtractField(pos,2,",");
					tmps.MakeUpper();
					for(atoipos=iStart;atoipos<iEnd;atoipos++)
						if (m_arrGPDIRCHANGEINFO[atoipos])
						{
							GPDIRCHANGEINFO *tmpchi=m_arrGPDIRCHANGEINFO[atoipos];
							if (m_arrGPDIRCHANGEINFO[atoipos]->Handle && m_arrGPDIRCHANGEINFO[atoipos]->Handle!=INVALID_HANDLE_VALUE)
							{
								PulseEvent(tmpchi->Handle);
								FindCloseChangeNotification(tmpchi->Handle);
							}
							tmpchi->bCancel=TRUE;
						}
					LeaveCriticalSection(&GPC.m_Document->m_CSCOPYEditor);
				}
				break;
			case 59: /*GetArrCRC16*/
				if (oStr)
				{
					char *postmpcc=new char [(int)strlen(pos)+10];
					strcpy(postmpcc,pos);
					int DataType=0,CRCType=0;
					DWORD PrevSumm=0;
					m_LastScanf=sscanf(postmpcc,"%d,%d,%d",&CRCType,&PrevSumm,&DataType);
					BYTE *tmparr=new BYTE [(int)strlen(postmpcc)+5];

					int len=0;
					const char *pos2=FindField(postmpcc,4,",");
					switch(DataType)
					{
					case 16:
						_strupr(postmpcc);
						while(pos2 && *pos2)
						{
							DWORD tmp=0;
							if (*pos2>='0' && *pos2<='9') tmp=*pos2-'0';
							else 
							if (*pos2>='A' && *pos2<='F') tmp=*pos2+10-'A';
							pos2++;
							if (*pos2>='0' && *pos2<='9') tmp=tmp*16+*pos2-'0';
							else 
							if (*pos2>='A' && *pos2<='F') tmp=tmp*16+*pos2+10-'A';

							tmparr[len++]=(unsigned char)tmp;
							if (*pos2 && (*pos2<'0' || *pos2==GPC.DelimiterIn1 || *pos2>'f')) pos2++;
						}
						break;
					case 8:
						while(pos2 && *pos2)
						{
							DWORD tmp=0;
							if (*pos2>='0' && *pos2<='7') tmp=*pos2-'0';
							pos2++;
							if (*pos2>='0' && *pos2<='7') {tmp=tmp*8+*pos2-'0';pos2++;}
							if (*pos2>='0' && *pos2<='7') {tmp=tmp*8+*pos2-'0';pos2++;}

							tmparr[len++]=(unsigned char)tmp;
							if (*pos2 && (*pos2<'0' || *pos2>'7')) pos2++;
						}
						break;
					case 10:
					default:
						while(pos2 && *pos2)
						{
							DWORD tmp=0;
							if (*pos2>='0' && *pos2<='9') tmp=*pos2-'0';
							pos2++;
							if (*pos2>='0' && *pos2<='9') {tmp=tmp*10+*pos2-'0';pos2++;}
							if (*pos2>='0' && *pos2<='9') {tmp=tmp*10+*pos2-'0';pos2++;}

							tmparr[len++]=(unsigned char)tmp;
							if (*pos2 && (*pos2<'0' || *pos2>'9')) pos2++;
						}
						break;
					}


					PrevSumm=calcCRC16_Type(CRCType,PrevSumm,tmparr,len);

					delete[] tmparr;
					*oStr=new char [1000];
					sprintf(*oStr,"%d%c%d%c%d%c%d",(PrevSumm/0x1000000)&0xFF,0xFE,(PrevSumm/0x10000)&0xFF,0xFE,(PrevSumm/0x100)&0xFF,0xFE,PrevSumm&0xFF);
					delete[] postmpcc;
				}
				break;
			case 60: /*ExpandEnvironmentStrings*/
				if (oStr)
				{
					*oStr=new char [10000];
					**oStr=0;
					ExpandEnvironmentStrings(pos,*oStr,9900);
				}
				break;
			#ifdef W_95
			#else
				#ifdef W_98
				#else
					case 61: /*InitiateSystemShutdown CompName,TimeoutSec,bForceAppsClosed,bRestart;Message*/
						{
							char name[500];
							strncpy(name,ExtractField(pos,1,","),490);
							char name2[500];
							strncpy(name2,FindField(pos,2,";"),490);
							char *message=name2;
							if (*message==0) message=NULL;
							retint=::InitiateSystemShutdown(
											name,//CompName
											message,
											atoi(ExtractField(pos,2,",")),//TimeoutSec
											atoi(ExtractField(pos,3,",")),//bForceAppsClosed
											atoi(ExtractField(pos,4,",")) //bRestart
											);
						}
						break;
					case 62: /*AbortSystemShutdown*/
						{
							char name[500];
							strncpy(name,pos,490);
							retint=::AbortSystemShutdown(name);
						}
						break;
				#endif
			#endif


			case 63: /*ExitWindows*/
				retint=::ExitWindows(0,0);
				break;
			case 64: /*ExitWindowsEx*/
				{
					DWORD EWExFlag=0;
					DWORD SHTDN_REASON=0;
					CString csEWExFlag=ExtractField(pos,1,",");
					CString csSHTDN_REASON=ExtractField(pos,2,",");
					if (csEWExFlag!="") StringFromToEWExFlag(csEWExFlag,EWExFlag);
					if (csSHTDN_REASON!="") StringFromToSHTDN_REASON(csSHTDN_REASON,SHTDN_REASON);
					retint=::ExitWindowsEx(EWExFlag,SHTDN_REASON);
				}
				break;

			#ifdef W_95
			#else
				#ifdef W_NT
				#else
					#ifdef W_98
					#else
						case 65: /*InitiateSystemShutdownEx MachineName,Timeout,ForceAppsClosed,RebootAfterShutdown,Reason;lpMessage*/
							{
								DWORD SHTDN_REASON=0;
								CString csSHTDN_REASON=ExtractField(pos,5,",");
								if (csSHTDN_REASON!="") StringFromToSHTDN_REASON(csSHTDN_REASON,SHTDN_REASON);

								char name[500];
								strncpy(name,ExtractField(pos,1,","),490);
								CString name2;
								const char *message=FindField(pos,2,";");
								if (!message) message=NULL;

								retint=::InitiateSystemShutdownEx(
												name,//CompName
												(char *)message,
												atoi(ExtractField(pos,2,",")),//TimeoutSec
												atoi(ExtractField(pos,3,",")),//bForceAppsClosed
												atoi(ExtractField(pos,4,",")),//bRestart
												SHTDN_REASON
												);
							}
							break;
						case 66: /*LockWorkStation*/
							retint=LockWorkStation();
							break;
					#endif
				#endif
			#endif

			case 67: /*FindFiles  [Attributes],[dtType C A W],[dtStart YYYYMMDDHHmmSS],[dtEnd YYYYMMDDHHmmSS],[nBytesRead];FileName*/
			case 68: /*FindFilesR  [Attributes],[dtType C A W],[dtStart YYYYMMDDHHmmSS],[dtEnd YYYYMMDDHHmmSS],[nBytesRead];FileName*/
			case 69: /*FindFiles [Attributes],[dtType C A W],[dtStart YYYYMMDDHHmmSS],[dtEnd YYYYMMDDHHmmSS],[ILName],[nImage];FileName*/
			case 70: /*FindFilesR [Attributes],[dtType C A W],[dtStart YYYYMMDDHHmmSS],[dtEnd YYYYMMDDHHmmSS],[ILName],[nImage];FileName*/
				if (oStr)
				{
					CString csParams=ExtractField(pos,1,";");
					const char *possr=strchr(pos,';');
					if (possr++)
					{
						CString csTmp;
						DWORD params=0xFFFF;
						csTmp=ExtractField(csParams,1,",");
						if (csTmp!="") m_LastScanf=sscanf(csTmp,"%X",&params);
						if (!params) params=0xFFFF;
						SYSTEMTIME tmpst1={0};
						SYSTEMTIME tmpst2={0};
						CTime DtMin(tmpst1),DtMax(tmpst2);
						CString cstmpParam=ExtractField(csParams,2,",");
						DWORD dwDateType=atoi(ExtractField(csParams,2,","));
						if (cstmpParam.Find("C",0)>=0) dwDateType=0x1;
						else
						if (cstmpParam.Find("W",0)>=0) dwDateType=0x2;
						else
						if (cstmpParam.Find("A",0)>=0) dwDateType=0x4;

						if (dwDateType)
						{
							cstmpParam=ExtractField(csParams,3,",");
							if (cstmpParam!="")
							{
								m_LastScanf=sscanf(cstmpParam,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d",&tmpst1.wYear,&tmpst1.wMonth,&tmpst1.wDay,&tmpst1.wHour,&tmpst1.wMinute,&tmpst1.wSecond);
								DtMin=CTime(tmpst1);
							}
							cstmpParam=ExtractField(csParams,4,",");
							if (cstmpParam!="")
							{
								m_LastScanf=sscanf(cstmpParam,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d",&tmpst2.wYear,&tmpst2.wMonth,&tmpst2.wDay,&tmpst2.wHour,&tmpst2.wMinute,&tmpst2.wSecond);
								DtMax=CTime(tmpst2);
							}
						}
						CString param5,param6;
						param5=ExtractField(csParams,5,",");
						param6=ExtractField(csParams,6,",");

						switch(nfunc)
						{
						case 67:
							{
								int nBytes=0;
								if (param5!="") nBytes=atoi(param5);
								FindFile(possr, oStr, params, dwDateType, DtMin, DtMax,nBytes);
							}
							break;
						case 68:
							{
								int nBytes=0;
								if (param5!="") nBytes=atoi(param5);
								FindFileRecursive(possr, oStr, params, dwDateType, DtMin, DtMax,nBytes);
							}
							break;
						case 69:
							{
								int nImage=0;
								if (param6!="") nImage=atoi(param6);
								FindImages(possr, oStr, params, dwDateType, DtMin, DtMax, param5==""?NULL:(LPCSTR)param5, nImage);
							}
							break;
						case 70:
							{
								int nImage=0;
								if (param6!="") nImage=atoi(param6);
								FindImagesRecursive(possr, oStr, params, dwDateType, DtMin, DtMax, param5==""?NULL:(LPCSTR)param5, nImage);
							}
							break;
						}
					}
				}
				break;
			case 71: //GetFileStat FileName
				if (oStr && *pos)
				{
					*oStr=new char [5000];
					**oStr=0;
					FILE *ftmp=fopen(pos,"rb");
					if (ftmp)
					{
						DWORD dwNBytes[256];
						ZeroMemory(dwNBytes,256*sizeof(DWORD));
						DWORD nb=0;
						int c;
						while((c=fgetc(ftmp))!=EOF) 
						{
							nb++;
							dwNBytes[c&0xFF]++;
						}
						fclose(ftmp);
						char *posout=*oStr;
						posout+=sprintf(posout,"%ld\x7F",nb);
						int i;
						for(i=0;i<256;i++)
							if (i)
								posout+=sprintf(posout,"\x7%ld",dwNBytes[i]);
							else
								posout+=sprintf(posout,"%ld",dwNBytes[i]);
					}
				}
				break;
			case 72: //GetMethods
				if (oStr)
				{
					*oStr=new char [5000];
					**oStr=0;
					int i;
					char *posout=*oStr;
					for(i=0;*CGP_TermDoc::cArrFSMethods[i];i++)
					{
						if (i) *(posout++)=0x7F;
						posout+=sprintf(posout,"%s\x7%s",CGP_TermDoc::cArrFSMethods[i],CGP_TermDoc::cArrFSMethodsParams[i]);
					}
				}
				break;
	//		case 73: //DeviceIoControl DevName,IOCtrlCode[;Data]
	//			{
	//			}
	//			break;



			case 12345678:
			default:
				GPC.m_ErrReport.GPWriteWarnLog2("File system", "Unknown Method",iStr);

				if (oStr!=NULL)
				{
					*oStr=new char [1000];
					sprintf(*oStr,ErrObjSub,met);FRet=FALSE;
				}
				break;
			}
			if (oStr && retint!=-123456)
			{
				if ((*oStr && **oStr==0) || *oStr==NULL)
				{
					if (*oStr==NULL) *oStr=new char [1000];
					sprintf(*oStr,"%d",retint);
				}
			}
		}
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGP_TermDoc",  "DoFileSystemMethod",iStr);
		FRet=FALSE;
	}
	return FRet;


}

DWORD StringFromToEWExFlag(const char *iOption, DWORD & convOption)
{
	UINT nOptions=8;
	const char *OptionName[]={
	"EWX_FORCEIFHUNG","EWX_POWEROFF","EWX_FORCE","EWX_REBOOT","EWX_SHUTDOWN","EWX_LOGOFF",
	"EWX_QUICKRESOLVE","EWX_RESTARTAPPS","","",
	};
	const DWORD  uOptionList[]={
	EWX_FORCEIFHUNG,EWX_POWEROFF,EWX_FORCE,EWX_REBOOT,EWX_SHUTDOWN,EWX_LOGOFF,
	EWX_QUICKRESOLVE,EWX_RESTARTAPPS,
	};

	if (*iOption)
	{
		convOption=atoi(iOption);
		UINT i;
		for(i=0;i<nOptions && convOption==NULL;i++)
			if (_stricmp(iOption,OptionName[i])==0)
				convOption=uOptionList[i];
	}
	else
	{
		UINT i;
		for(i=0;i<nOptions && *iOption==0;i++)
			if (convOption==uOptionList[i])
				strcpy((char *)iOption,OptionName[i]);

		if (*iOption==0 && convOption) sprintf((char *)iOption,"%d",convOption);
	}
	return convOption;
}

DWORD StringFromToSHTDN_REASON(const char *iOption, DWORD & convOption)
{
	UINT i;
	UINT nOptions1=4;
	const char *OptionName1[4]={
		"SHTDN_REASON_FLAG_COMMENT_REQUIRED","SHTDN_REASON_FLAG_DIRTY_PROBLEM_ID_REQUIRED","SHTDN_REASON_FLAG_CLEAN_UI","SHTDN_REASON_FLAG_DIRTY_UI",
		};
	const DWORD  uOptionList1[4]={
		SHTDN_REASON_FLAG_COMMENT_REQUIRED,SHTDN_REASON_FLAG_DIRTY_PROBLEM_ID_REQUIRED,SHTDN_REASON_FLAG_CLEAN_UI,SHTDN_REASON_FLAG_DIRTY_UI,
		};

	UINT nOptions2=2;
	const char *OptionName2[2]={
		"SHTDN_REASON_FLAG_USER_DEFINED","SHTDN_REASON_FLAG_PLANNED",
		};
	const DWORD  uOptionList2[2]={
		SHTDN_REASON_FLAG_USER_DEFINED,SHTDN_REASON_FLAG_PLANNED,
		};

	UINT nOptions3=7;
	const char *OptionName3[7]={
		"SHTDN_REASON_MAJOR_HARDWARE","SHTDN_REASON_MAJOR_OPERATINGSYSTEM","SHTDN_REASON_MAJOR_SOFTWARE","SHTDN_REASON_MAJOR_APPLICATION","SHTDN_REASON_MAJOR_SYSTEM",
		"SHTDN_REASON_MAJOR_POWER","SHTDN_REASON_MAJOR_LEGACY_API",
		};
	const DWORD  uOptionList3[7]={
		SHTDN_REASON_MAJOR_HARDWARE,SHTDN_REASON_MAJOR_OPERATINGSYSTEM,SHTDN_REASON_MAJOR_SOFTWARE,SHTDN_REASON_MAJOR_APPLICATION,SHTDN_REASON_MAJOR_SYSTEM,
		SHTDN_REASON_MAJOR_POWER,SHTDN_REASON_MAJOR_LEGACY_API,
		};

	UINT nOptions4=29;
	const char *OptionName4[29]={
		"SHTDN_REASON_MINOR_NONE","SHTDN_REASON_MINOR_MAINTENANCE","SHTDN_REASON_MINOR_INSTALLATION","SHTDN_REASON_MINOR_UPGRADE","SHTDN_REASON_MINOR_RECONFIG",
		"SHTDN_REASON_MINOR_HUNG","SHTDN_REASON_MINOR_UNSTABLE","SHTDN_REASON_MINOR_DISK","SHTDN_REASON_MINOR_PROCESSOR","SHTDN_REASON_MINOR_NETWORKCARD",
		"SHTDN_REASON_MINOR_POWER_SUPPLY","SHTDN_REASON_MINOR_CORDUNPLUGGED","SHTDN_REASON_MINOR_ENVIRONMENT","SHTDN_REASON_MINOR_HARDWARE_DRIVER","SHTDN_REASON_MINOR_OTHERDRIVER",
		"SHTDN_REASON_MINOR_BLUESCREEN","SHTDN_REASON_MINOR_SERVICEPACK","SHTDN_REASON_MINOR_HOTFIX","SHTDN_REASON_MINOR_SECURITYFIX","SHTDN_REASON_MINOR_SECURITY",
		"SHTDN_REASON_MINOR_NETWORK_CONNECTIVITY","SHTDN_REASON_MINOR_WMI","SHTDN_REASON_MINOR_SERVICEPACK_UNINSTALL","SHTDN_REASON_MINOR_HOTFIX_UNINSTALL","SHTDN_REASON_MINOR_SECURITYFIX_UNINSTALL",
		"SHTDN_REASON_MINOR_MMC","SHTDN_REASON_MINOR_TERMSRV","SHTDN_REASON_MINOR_DC_PROMOTION","SHTDN_REASON_MINOR_DC_DEMOTION",
		};
	const DWORD  uOptionList4[29]={
		SHTDN_REASON_MINOR_NONE,SHTDN_REASON_MINOR_MAINTENANCE,SHTDN_REASON_MINOR_INSTALLATION,SHTDN_REASON_MINOR_UPGRADE,SHTDN_REASON_MINOR_RECONFIG,
		SHTDN_REASON_MINOR_HUNG,SHTDN_REASON_MINOR_UNSTABLE,SHTDN_REASON_MINOR_DISK,SHTDN_REASON_MINOR_PROCESSOR,SHTDN_REASON_MINOR_NETWORKCARD,
		SHTDN_REASON_MINOR_POWER_SUPPLY,SHTDN_REASON_MINOR_CORDUNPLUGGED,SHTDN_REASON_MINOR_ENVIRONMENT,SHTDN_REASON_MINOR_HARDWARE_DRIVER,SHTDN_REASON_MINOR_OTHERDRIVER,
		SHTDN_REASON_MINOR_BLUESCREEN,SHTDN_REASON_MINOR_SERVICEPACK,SHTDN_REASON_MINOR_HOTFIX,SHTDN_REASON_MINOR_SECURITYFIX,SHTDN_REASON_MINOR_SECURITY,
		SHTDN_REASON_MINOR_NETWORK_CONNECTIVITY,SHTDN_REASON_MINOR_WMI,SHTDN_REASON_MINOR_SERVICEPACK_UNINSTALL,SHTDN_REASON_MINOR_HOTFIX_UNINSTALL,SHTDN_REASON_MINOR_SECURITYFIX_UNINSTALL,
		SHTDN_REASON_MINOR_MMC,SHTDN_REASON_MINOR_TERMSRV,SHTDN_REASON_MINOR_DC_PROMOTION,SHTDN_REASON_MINOR_DC_DEMOTION,
		};

	if (*iOption)
	{
		DWORD convOption1=0,convOption2=0,convOption3=0,convOption4=0;
		char *tmps=new char [(int)strlen(iOption)+100];
		strcpy(tmps,iOption);
		_strupr(tmps);


		convOption1=atoi(iOption);
		for(i=0;i<nOptions1 && convOption1==NULL;i++)
			if (strstr(tmps,OptionName1[i]))
				convOption1=uOptionList1[i];

		convOption2=atoi(iOption);
		for(i=0;i<nOptions2 && convOption2==NULL;i++)
			if (strstr(tmps,OptionName2[i]))
				convOption2=uOptionList2[i];

		convOption3=atoi(iOption);
		for(i=0;i<nOptions3 && convOption3==NULL;i++)
			if (strstr(tmps,OptionName3[i]))
				convOption3=uOptionList3[i];

		convOption4=atoi(iOption);
		for(i=0;i<nOptions4 && convOption4==NULL;i++)
			if (strstr(tmps,OptionName4[i]))
				convOption4=uOptionList4[i];


		convOption=convOption1|convOption2|convOption3|convOption4;
		delete[] tmps;
	}
	else
	{
		for(i=0;i<nOptions1;i++)
			if ((convOption&0x0F000000)==uOptionList1[i])
			{
				if (*iOption) strcat((char *)iOption,"|");
				strcat((char *)iOption,OptionName1[i]);
			}

		for(i=0;i<nOptions2;i++)
			if ((convOption&0xF0000000)==uOptionList2[i])
			{
				if (*iOption) strcat((char *)iOption,"|");
				strcat((char *)iOption,OptionName2[i]);
			}

		for(i=0;i<nOptions3;i++)
			if ((convOption&0x000F0000)==uOptionList3[i])
			{
				if (*iOption) strcat((char *)iOption,"|");
				strcat((char *)iOption,OptionName3[i]);
			}

		for(i=0;i<nOptions4;i++)
			if ((convOption&0x000000FF)==uOptionList4[i])
			{
				if (*iOption) strcat((char *)iOption,"|");
				strcat((char *)iOption,OptionName4[i]);
			}

		if (*iOption==0) sprintf((char *)iOption,"%d",convOption);
	}

	return convOption;
}

/*
DWORD StringFromToXXXXXXX(const char *iOption, DWORD & convOption)
{
	UINT nOptions=;
	const char *OptionName[]={
	"","","","",
	};
	const DWORD  uOptionList[]={
	,,,,
	};

	if (*iOption)
	{
		convOption=atoi(iOption);
		UINT i;
		for(i=0;i<nOptions && convOption==NULL;i++)
			if (_stricmp(iOption,OptionName[i])==0)
				convOption=uOptionList[i];
	}
	else
	{
	UINT i;
		for(i=0;i<nOptions && *iOption==0;i++)
			if (convOption==uOptionList[i])
				strcpy((char *)iOption,OptionName[i]);

		if (*iOption==0) sprintf((char *)iOption,"%d",convOption);
	}
	return convOption;
}



DWORD StringFromToXXXXXXX(const char *iSamOption, DWORD & convSamOption)
{
	UINT nOptions=;
	const char *OptionName[]={
	"REG_NOTIFY_CHANGE_NAME","REG_NOTIFY_CHANGE_ATTRIBUTES","REG_NOTIFY_CHANGE_LAST_SET","REG_NOTIFY_CHANGE_SECURITY",
	};
	const UINT  uOptionList[]={
	REG_NOTIFY_CHANGE_NAME,REG_NOTIFY_CHANGE_ATTRIBUTES,REG_NOTIFY_CHANGE_LAST_SET,REG_NOTIFY_CHANGE_SECURITY,
	};


	if (*iSamOption)
	{
		char *tmps=new char [(int)strlen(iSamOption)+100];
		strcpy(tmps,iSamOption);
		_strupr(tmps);
		convSamOption=atoi(tmps);
		UINT i;
		for(i=0;i<nOptions;i++)
			if (strstr(tmps,OptionName[i]))
				convSamOption|=uOptionList[i];
		delete[] tmps;
	}
	else
	{
		UINT convSD=convSamOption;
		UINT i;
		for(i=0;i<nOptions;i++)
			if ((convSD&uOptionList[i])==uOptionList[i])
			{
				if (*iSamOption) strcat((char *)iSamOption,"|");
				strcat((char *)iSamOption,OptionName[i]);
				convSD^=uOptionList[i];
			}
			if (convSD) sprintf((char *)iSamOption+(int)strlen(iSamOption),"%s%d",*iSamOption?"|":"",convSD);
	}

	return convSamOption;
}

*/