// GPInputPool.cpp: implementation of the CGPInputPool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GPInputPool.h"
#include "GP_Term.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGPInputPool::CGPInputPool()
{
	BookMarkFlag=0;
	n_Transfered=0;
	InitializeCriticalSection(&m_CS_GPInputPool);
	InputPoolsArr=NULL;
	n_InputPools=0;
	Init(65520);
}

CGPInputPool::~CGPInputPool()
{
	EnterCriticalSection(&m_CS_GPInputPool);
	try
	{
		DeletePools();
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGPInputPool", "~CGPInputPool","");
	}
	LeaveCriticalSection(&m_CS_GPInputPool);
	DeleteCriticalSection(&m_CS_GPInputPool);
}

void CGPInputPool::AddPool()
{
//	TRACE("%d %d %d %d\n",n_InputPools,n_CurPoolBM,n_CurPoolWrite,n_CurPoolRead);
	if (InputPoolsArr==NULL)
	{
		ResetPools();
		InputPoolsArr=new BYTE * [n_InputPools+1];
		InputPoolsArr[n_InputPools]=new BYTE [n_PoolSize];
	}
	else
	{
		BYTE **InputPoolsArrTMP=new BYTE * [n_InputPools+1];
		if (n_CurPoolWrite>=n_CurPoolBM)
		{
			UINT i;
			for(i=0;i<n_InputPools;i++)
				InputPoolsArrTMP[i]=InputPoolsArr[i];
			InputPoolsArrTMP[i]=new BYTE [n_PoolSize];
		}
		else
		{
			UINT i;
			for(i=0;i<n_CurPoolBM;i++)
				InputPoolsArrTMP[i]=InputPoolsArr[i];

			InputPoolsArrTMP[i]=new BYTE [n_PoolSize];

			UINT j;
			for(j=i++;j<n_InputPools;j++,i++)
				InputPoolsArrTMP[i]=InputPoolsArr[j];

			n_CurPoolBM++;
			n_CurPoolRead++;
		}
		delete[] InputPoolsArr;
		InputPoolsArr=InputPoolsArrTMP;
	}
	n_InputPools++;
}

void CGPInputPool::Init(UINT iPoolSize)
{
	EnterCriticalSection(&m_CS_GPInputPool);
	try
	{
		DeletePools();
		if (iPoolSize>0x4000000 || iPoolSize<1024) iPoolSize=65520;
		n_PoolSize=iPoolSize;
		AddPool();
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGPInputPool", "Init","");
	}
	LeaveCriticalSection(&m_CS_GPInputPool);
}

void CGPInputPool::ResetPools()
{
	n_CurPoolWrite=0;
	n_CurPosWrite=0;
	n_CurPoolRead=0;
	n_CurPosRead=0;
	n_CurPoolBM=0;
	n_CurPosBM=0;
	n_Transfered=0;
}

void CGPInputPool::DeletePools()
{
	if (InputPoolsArr)
	{
		UINT i;
		for(i=0;i<n_InputPools;i++)
			if (InputPoolsArr[i]) 
			{
				delete InputPoolsArr[i];
				InputPoolsArr[i]=NULL;
			}
		delete[] InputPoolsArr;
		InputPoolsArr=NULL;
		n_InputPools=0;
	}
	ResetPools();
}

void CGPInputPool::FreeExtra()
{
	EnterCriticalSection(&m_CS_GPInputPool);
	try
	{
		FreeExtraNCS();
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGPInputPool", "FreeExtra","");
	}
	LeaveCriticalSection(&m_CS_GPInputPool);
}
void CGPInputPool::FreeExtraNCS()
{
	if (InputPoolsArr)
	{
		if (n_CurPoolWrite>=n_CurPoolBM)
		{
			UINT i;
			for(i=n_CurPoolWrite+1;i<n_InputPools;i++)
				if (InputPoolsArr[i])
				{
					delete InputPoolsArr[i];
					InputPoolsArr[i]=NULL;
				}
			n_InputPools=n_CurPoolWrite+1;

			if (n_CurPoolBM>0)
			{
				BYTE **InputPoolsArrTMP=new BYTE * [n_InputPools-n_CurPoolBM];
				for(i=0;i<n_InputPools;i++)
					if (i<n_CurPoolBM)
					{
						if (InputPoolsArr[i])	delete InputPoolsArr[i];
						InputPoolsArr[i]=NULL;
					}
					else
						InputPoolsArrTMP[i-n_CurPoolBM]=InputPoolsArr[i];

				delete[] InputPoolsArr;
				InputPoolsArr=InputPoolsArrTMP;
				n_InputPools-=n_CurPoolBM;
				n_CurPoolWrite-=n_CurPoolBM;
				n_CurPoolRead-=n_CurPoolBM;
				n_CurPoolBM=0;
			}
		}
		else
			if (n_CurPoolWrite<n_CurPoolBM-1)
			{
				UINT i,j;
				for(i=n_CurPoolWrite+1;i<n_CurPoolBM;i++)
					if (InputPoolsArr[i])
					{
						delete InputPoolsArr[i];
						InputPoolsArr[i]=NULL;
					}

				for(j=n_CurPoolWrite+1,i=n_CurPoolBM;i<n_InputPools;i++,j++)
					InputPoolsArr[j]=InputPoolsArr[i];

				n_InputPools-=(n_CurPoolBM-n_CurPoolWrite-1);
				if (n_CurPoolRead>n_CurPoolWrite) n_CurPoolRead-=n_CurPoolBM-n_CurPoolWrite-1;
				n_CurPoolBM=n_CurPoolWrite+1;
			}
	}
}

UINT CGPInputPool::GetReadLength()
{
	UINT ret=0;
	EnterCriticalSection(&m_CS_GPInputPool);
	try
	{
		ret=GetReadLengthNCS();
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CGPInputPool", "GetReadLength","");
	}
	LeaveCriticalSection(&m_CS_GPInputPool);
	return ret;
}

UINT CGPInputPool::GetReadLengthNCS()
{
	UINT ret=0;
	ret=n_CurPosWrite-n_CurPosRead;
	if (n_CurPoolWrite>n_CurPoolRead)
		ret+=(n_CurPoolWrite-n_CurPoolRead)*n_PoolSize;
	else
		if (n_CurPoolWrite<n_CurPoolRead)
			ret+=(n_CurPoolWrite+n_InputPools-n_CurPoolRead)*n_PoolSize;

	return ret;
}

UINT CGPInputPool::GetPoolsFreeSpace()
{
	UINT ret=n_CurPosBM-n_CurPosWrite;
	if (n_CurPoolBM>n_CurPoolWrite)
		ret+=(n_CurPoolBM-n_CurPoolWrite)*n_PoolSize;
	else
		if (n_CurPoolBM<n_CurPoolWrite)
			ret+=(n_CurPoolBM+n_InputPools-n_CurPoolWrite)*n_PoolSize;
	return ret;
}

UINT CGPInputPool::FillFromHandle(HANDLE iHandle, OVERLAPPED *ov, UINT nMax, UINT nMaxConst)
{
	UINT ret=0;
	if (iHandle)
	{
		EnterCriticalSection(&m_CS_GPInputPool);
		try
		{
			if (InputPoolsArr==NULL) AddPool();

			while(nMax)
			{
				UINT curnRead=n_PoolSize-n_CurPosWrite;
				if (curnRead>nMax) curnRead=nMax;
				DWORD realRead=0;

				if (ReadFile(iHandle,LPVOID(InputPoolsArr[n_CurPoolWrite]+n_CurPosWrite),curnRead,&realRead,ov))
				{
					nMax-=realRead;
					n_CurPosWrite+=realRead;
					n_Transfered+=realRead;
					if (n_CurPosWrite>=n_PoolSize) 
					{
						if (n_CurPoolWrite<n_CurPoolBM)
						{
							if (n_CurPoolWrite==n_CurPoolBM-1) AddPool();
							n_CurPoolWrite++;
						}
						else
						{
							if (n_CurPoolWrite==n_InputPools-1)
							{
								if (n_CurPoolBM==0) 
								{
									AddPool();
									n_CurPoolWrite++;
								}
								else n_CurPoolWrite=0;
							}
							else n_CurPoolWrite++;
						}
						n_CurPosWrite-=n_PoolSize;
					}
				}
				else 
					nMax=0;
				ret+=realRead;
			}
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("CGPInputPool", "FillFromHandle","");
		}
		LeaveCriticalSection(&m_CS_GPInputPool);
	}
	return ret;
}


UINT CGPInputPool::FillFromArray(const BYTE *iArr, UINT iArrayLen)
{
	UINT ret=iArrayLen;
	n_Transfered+=iArrayLen;
	if (iArr && iArrayLen)
	{
		EnterCriticalSection(&m_CS_GPInputPool);
		try
		{
			if (InputPoolsArr==NULL) AddPool();

			while(iArrayLen)
			{
				UINT curnRead=n_PoolSize-n_CurPosWrite;
				if (curnRead>iArrayLen) curnRead=iArrayLen;
				UINT realRead=iArrayLen;
				if (realRead>curnRead) realRead=curnRead;
				if (realRead)
				{
					iArrayLen-=realRead;
					BYTE *dest=InputPoolsArr[n_CurPoolWrite]+n_CurPosWrite;
					n_CurPosWrite+=realRead;
					ret+=realRead;
					while(realRead--)
						*(dest++)=*(iArr++);

					if (n_CurPosWrite>=n_PoolSize) 
					{
						if (n_CurPoolWrite<n_CurPoolBM)
						{
							if (n_CurPoolWrite==n_CurPoolBM-1) AddPool();
							n_CurPoolWrite++;
						}
						else
						{
							if (n_CurPoolWrite==n_InputPools-1)
							{
								if (n_CurPoolBM==0) 
								{
									AddPool();
									n_CurPoolWrite++;
								}
								else n_CurPoolWrite=0;
							}
							else n_CurPoolWrite++;
						}
						n_CurPosWrite-=n_PoolSize;
					}
				}
				else 
					iArrayLen=0;
			}
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("CGPInputPool", "FillFromArray","");
		}
		LeaveCriticalSection(&m_CS_GPInputPool);
	}
	return ret-iArrayLen;
}

UINT CGPInputPool::GetByte(BYTE *oByte, UINT Flags)
{
	UINT ret=0;
	if (oByte)
	{
		EnterCriticalSection(&m_CS_GPInputPool);
		try
		{
			UINT nRealBytes=GetReadLengthNCS();
			UINT tmpn_CurPosRead=n_CurPosRead;
			UINT tmpn_CurPoolRead=n_CurPoolRead;
			UINT nByte=1;

			if (nByte>nRealBytes) nByte=nRealBytes;
			if (nByte)
			{
				BYTE *DEST=oByte;
				while(ret<nByte)
				{
					BYTE *SRC=InputPoolsArr[tmpn_CurPoolRead]+tmpn_CurPosRead;
					if (n_CurPoolWrite==tmpn_CurPoolRead)
					{
						if (nByte-ret>=n_CurPosWrite-tmpn_CurPosRead)
						{
							while(tmpn_CurPosRead++<n_CurPosWrite)	*(DEST++)=*(SRC++);
							ret=nByte;
						}
						else
						{
							tmpn_CurPosRead+=(nByte-ret);
							while(ret++!=nByte)	*(DEST++)=*(SRC++);
						}
					}
					else
					{
						if (nByte-ret>=n_PoolSize-tmpn_CurPosRead)
						{
							while(tmpn_CurPosRead++<n_PoolSize)	*(DEST++)=*(SRC++);
							ret=nByte;
						}
						else
						{
							tmpn_CurPosRead+=(nByte-ret);
							while(ret++!=nByte)	*(DEST++)=*(SRC++);
						}

						tmpn_CurPoolRead++;
						if (tmpn_CurPoolRead==n_InputPools) tmpn_CurPoolRead=0;
					}
				}
				if ((Flags&IP_MOVE)==IP_MOVE) 
				{
					n_CurPosRead=tmpn_CurPosRead;
					if (BookMarkFlag==0) n_CurPosBM=n_CurPosRead;
					n_CurPoolRead=tmpn_CurPoolRead;
					if (BookMarkFlag==0) n_CurPoolBM=tmpn_CurPoolRead;
				}
				if ((Flags&IP_FREEEXTRA)==IP_FREEEXTRA) FreeExtra();
			}
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("CGPInputPool", "GetByte","");
		}
		LeaveCriticalSection(&m_CS_GPInputPool);
	}
	return ret;
}

UINT CGPInputPool::GetData(BYTE **oArr, UINT nByte, UINT Flags)
// nByte=0, Flags=IP_MOVE
{
	UINT ret=0;
	if (oArr)
	{
		EnterCriticalSection(&m_CS_GPInputPool);
		try
		{
			UINT nRealBytes=GetReadLengthNCS();
			UINT tmpn_CurPosRead=n_CurPosRead;
			UINT tmpn_CurPoolRead=n_CurPoolRead;

			if (nByte>nRealBytes || nByte==0) nByte=nRealBytes;
			if (nByte)
			{
				if (*oArr==NULL) *oArr=new BYTE [nByte+10];
				BYTE *DEST=*oArr;
				while(ret<nByte)
				{
					*DEST=0;
					BYTE *SRC=InputPoolsArr[tmpn_CurPoolRead]+tmpn_CurPosRead;
					if (n_CurPoolWrite==tmpn_CurPoolRead)
					{
						if (nByte-ret>=n_CurPosWrite-tmpn_CurPosRead)
						{
							ret+=n_CurPosWrite-tmpn_CurPosRead;
							while(tmpn_CurPosRead<n_CurPosWrite)
							{
								tmpn_CurPosRead++;
								*(DEST++)=*(SRC++);
							}
						}
						else
						{
							tmpn_CurPosRead+=(nByte-ret);
							while(ret!=nByte)
							{
								ret++;
								*(DEST++)=*(SRC++);
							}
						}
					}
					else
					{
						if (nByte-ret>=n_PoolSize-tmpn_CurPosRead)
						{
							ret+=n_PoolSize-tmpn_CurPosRead;
							while(tmpn_CurPosRead<n_PoolSize)
							{
								tmpn_CurPosRead++;
								*(DEST++)=*(SRC++);
							}
						}
						else
						{
							tmpn_CurPosRead+=(nByte-ret);
							while(ret!=nByte)
							{
								ret++;
								*(DEST++)=*(SRC++);
							}
						}

						if (tmpn_CurPosRead>=n_PoolSize)
						{
							tmpn_CurPoolRead++;
							tmpn_CurPosRead=0;
						}
						if (tmpn_CurPoolRead==n_InputPools) tmpn_CurPoolRead=0;
					}
				}
				if ((Flags&IP_MOVE)==IP_MOVE) 
				{
					n_CurPosRead=tmpn_CurPosRead;
					if (BookMarkFlag==0) n_CurPosBM=n_CurPosRead;
					n_CurPoolRead=tmpn_CurPoolRead;
					if (BookMarkFlag==0) n_CurPoolBM=tmpn_CurPoolRead;
				}
				if ((Flags&IP_FREEEXTRA)==IP_FREEEXTRA)
					FreeExtra();
				*DEST=0;
			}
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("CGPInputPool", "GetData","");
		}

		UINT freeSpace=n_CurPosBM-n_CurPosWrite;
		if (n_CurPoolBM>n_CurPoolWrite)
			freeSpace+=(n_CurPoolBM-n_CurPoolWrite)*n_PoolSize;
		else
			if (n_CurPoolBM<=n_CurPoolWrite)
				freeSpace+=(n_CurPoolBM+n_InputPools-n_CurPoolWrite)*n_PoolSize;
		if (freeSpace>n_PoolSize*10) FreeExtraNCS();

		LeaveCriticalSection(&m_CS_GPInputPool);
	}
	return ret;
}


UINT CGPInputPool::GetString(char **iStr)
{
	UINT retVal=123456789;
	if (iStr)
	{
		char *str=new char [550];
		char *pos;
		int len=0;
		UINT ret=0;
		char **tmpp=&str;
		while((len=GetData((BYTE **)tmpp,512,IP_NONE)) && retVal==123456789)
		{
			pos=str;
			pos[512]=0;
			while(*pos && *pos!=10 && *pos!=13) pos++;

			if (pos-str<len)
			{
				retVal=GetData((BYTE **)iStr,ret+pos-str+1);
				if (retVal) retVal--;
				char *tmps=str+540;
				GetData((BYTE **)&tmps,2,IP_NONE);

				if (*pos==10)
				{
					if (*tmps==0)
						GetData((BYTE **)&tmps,tmps[1]==13?2:1);
					else
					if (*tmps==13)
						GetData((BYTE **)&tmps,tmps[1]==0?2:1);
				}
				else
				if (*pos==13)
				{
					if (*tmps==0)
						GetData((BYTE **)&tmps,tmps[1]==10?2:1);
					else
					if (*tmps==10)
						GetData((BYTE **)&tmps,tmps[1]==0?2:1);
				}
				else
				if (*pos==0)
				{
					if (*tmps==10)
						GetData((BYTE **)&tmps,tmps[1]==13?2:1);
					else
					if (*tmps==13)
						GetData((BYTE **)&tmps,tmps[1]==10?2:1);
				}
			}
			else 
				if (len>=512) ret+=len;
		}
		delete[] str;
	}
	return retVal;
}

UINT CGPInputPool::SetBookMarkFlag(UINT newValue)
{
	UINT ret=BookMarkFlag;
	EnterCriticalSection(&m_CS_GPInputPool);
		BookMarkFlag=newValue;
		if (newValue==0)
		{
			n_CurPoolBM=n_CurPoolRead;
			n_CurPosBM=n_CurPosRead;
			FreeExtra();
		}
	LeaveCriticalSection(&m_CS_GPInputPool);

	return ret;
}

UINT CGPInputPool::GetBookMarkFlag()
{
	return BookMarkFlag;
}

DWORD calcCRC16_Type(UINT CRCType, DWORD PrevSumm, BYTE *tmparr, UINT len);

DWORD CGPInputPool::GetCRC16(int start, int Length, ULONG PrevSumm, UINT crc16type)
{

	EnterCriticalSection(&m_CS_GPInputPool);

		UINT tmpn_CurPosRead=n_CurPosBM;
		UINT tmpn_CurPoolRead=n_CurPoolBM;
		BOOL calc;
		BYTE *tmpArray=new BYTE [Length+2];
		try
		{
			int i;
			for(i=-start;i<Length;i++)
			{
				calc=(i>=0);
				BYTE *SRC=InputPoolsArr[tmpn_CurPoolRead]+tmpn_CurPosRead;
				if (n_CurPoolWrite==tmpn_CurPoolRead)
				{
					if (++tmpn_CurPosRead>=n_CurPosWrite) i=Length;
				}
				else
					if (++tmpn_CurPosRead>=n_PoolSize)
					{
						tmpn_CurPoolRead++;
						if (tmpn_CurPoolRead>=n_InputPools) tmpn_CurPoolRead=0;
						tmpn_CurPosRead=0;
					}



				if (i>=0)	tmpArray[i]=*SRC;
			}
			PrevSumm=calcCRC16_Type(crc16type,PrevSumm,tmpArray, Length);
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("CGPInputPool", "GetCRC16","");
		}
		delete[] tmpArray;
	LeaveCriticalSection(&m_CS_GPInputPool);

	return PrevSumm;
}


UINT CGPInputPool::MoveBookMark(UINT delta)
{
	UINT ret=0;
	if (BookMarkFlag && (n_CurPoolRead!=n_CurPoolBM || n_CurPosRead!=n_CurPosBM))
	{
		EnterCriticalSection(&m_CS_GPInputPool);
		UINT i;
			for(i=0;i<delta;i++)
				if (n_CurPoolBM==n_CurPoolRead)
				{
					if (n_CurPosBM==n_CurPosRead) i=delta;
					else {ret++;n_CurPosBM++;}
				}
				else
					if (++n_CurPosBM>=n_PoolSize)
					{
						ret++;
						n_CurPosBM=0;
						n_CurPoolBM++;
						if (n_CurPoolBM>=n_InputPools) n_CurPoolBM=0;
					}
		LeaveCriticalSection(&m_CS_GPInputPool);
	}

	return ret;
}

UINT CGPInputPool::GetTransferedLen()
{
	return n_Transfered;
}
