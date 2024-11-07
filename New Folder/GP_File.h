// GP_File.h: interface for the GP_File class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GP_FILE_H__FF2597E2_B9B8_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GP_FILE_H__FF2597E2_B9B8_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class GP_File : public CFile  
{
public:
	int prtflg, pgs;
	static void ConvertToPrintd(const char *iStr, char **oStr, int & pr, int & pg);
	__int64 GPFindPlace(char *str);
	int GPGetBlocksInfo(char *str, int Len);
	int GPPosRollBack();
	UINT ConvON;
	int GPUnLockRange(int param1, int param2);
	int GPLockRange(int param1, int param2);
	int GPGetStatus(char *str);
	BOOL GPGetPosition(__int64 * position);
	BOOL GPGetLength(__int64 * position);
	int GPSetLength(__int64 param1);
	int GPFlush();
	__int64 GPSeekToEnd();
	int GPSeekToBegin();
	BOOL GPSeek(__int64 param1, DWORD param2);
	int GPWriteBlock(const char *blk);
	UINT GPReadBlock(char *blk,int len);
	int GPPutStr(char *str);
	int GPGetStr(char **str, UINT nstr);
	int GPPutChar(int iCh);
	int GPGetChar(char *str, UINT nChar);
	BOOL GPOpenFile(char *Init,char *result);
	GP_File();
	virtual ~GP_File();
	__int64 LastPos;

};

#endif // !defined(AFX_GP_FILE_H__FF2597E2_B9B8_11D2_B27D_00600840D054__INCLUDED_)
