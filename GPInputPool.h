// GPInputPool.h: interface for the CGPInputPool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPINPUTPOOL_H__27675C80_ED7E_4C65_AAC4_3285F681890E__INCLUDED_)
#define AFX_GPINPUTPOOL_H__27675C80_ED7E_4C65_AAC4_3285F681890E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define IP_NONE		0x0000
#define IP_MOVE		0x0001
#define IP_FREEEXTRA		0x0002

class CGPInputPool : public CObject  
{
public:
	UINT GetTransferedLen();
	UINT MoveBookMark(UINT delta);
	DWORD GetCRC16(int start, int Length, ULONG PrevSumm, UINT crc16type);
	UINT SetBookMarkFlag(UINT newValue);
	UINT GetBookMarkFlag();
	UINT GetString(char **iStr);
	UINT GetByte(BYTE *oByte, UINT Flags=IP_MOVE);
	UINT GetData(BYTE **oArr, UINT nByte=0, UINT Flags=IP_MOVE);
	UINT FillFromArray(const BYTE *iArr, UINT iArrayLen);
	UINT FillFromHandle(HANDLE iHandle, OVERLAPPED *ov, UINT nMax=65000, UINT nMaxConst=0);
	UINT GetReadLength();
	void Init(UINT iPoolSize);
	CGPInputPool();
	virtual ~CGPInputPool();
	void FreeExtra();
private:
	UINT n_Transfered;
	UINT BookMarkFlag;
	void FreeExtraNCS();
	UINT GetReadLengthNCS();
	UINT GetPoolsFreeSpace();
	void DeletePools();
	void ResetPools();
	void AddPool();
	BYTE ** InputPoolsArr;
	UINT n_InputPools;
	UINT n_CurPoolWrite;
	UINT n_CurPosWrite;
	UINT n_CurPoolRead;
	UINT n_CurPosRead;
	UINT n_CurPoolBM;
	UINT n_CurPosBM;
	UINT n_PoolSize;
	CRITICAL_SECTION m_CS_GPInputPool;
};

#endif // !defined(AFX_GPINPUTPOOL_H__27675C80_ED7E_4C65_AAC4_3285F681890E__INCLUDED_)
