// ListMaker.h: interface for the CListMaker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTMAKER_H__67AB5043_3AE5_4F11_9CE1_CBA8C337274A__INCLUDED_)
#define AFX_LISTMAKER_H__67AB5043_3AE5_4F11_9CE1_CBA8C337274A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CListMaker  
{
public:
	long FillObject(const char *iName, HWND ihWnd, UINT ObjType, long FillType);
	long GetList(const char *iName, char **oList);
	long GetList(const char *iName, char **oList, char delim);
#ifndef WLISTMAKER
	long GetList(const char *iName, BSTR FAR* OutListString);
	long GetListAsArray(const char *iName, VARIANT *iList);
	long SetListAsArray(const char *iName, VARIANT *iList);
	long GetListInfo(const char *iName, VARIANT FAR* ListInfo);
	long GetListsInfo(VARIANT FAR* ListInfo);
#endif
	UINT LoadList(const char *ListName, const char *FileName);
	int SaveList(const char *nmlist, const char *nmFile);
	UINT NotBeginContextLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	UINT BeginContextLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	UINT NotEndContextLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	UINT EndContextLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	UINT NotContextLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	UINT NotMaskLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	UINT MaskLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	UINT ContextLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	int DoMethod(const char * iStr, char **oStr);
	UINT XORLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	UINT ANDLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	UINT NOTLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	UINT ORLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	UINT SquiseList(const char *iName);
	UINT DuplicateList(const char *iName, const char *SourceName);
	UINT UniqueList(const char *iName);
	void SortList(const char *iName);
	void SortListDesc(const char *iName);
	UINT AddList(const char *destList,const char *srcList);
	UINT AppendList(const char *iName, const char * iList);
	UINT GetListItemCount(const char *iName);
	UINT GetListState(const char *iName);
	UINT GetListLength(const char *iName);
	const char * GetListItem(const char *iName, UINT iNItem);
	char GetListDelimiter(const char *iName);
	char SetListDelimiter(const char *iName,char newDelimiter);
	UINT GetCount();
	UINT SetList(const char *iName, const char *iList,char delimiter);
	UINT CreateList(const char * iName);
	UINT DeleteList(const char *iName);
	CListMaker();
	virtual ~CListMaker();

private:
	long FillObject(UINT iIndex, HWND ihWnd, UINT ObjType, long FillType);
	long GetList(UINT iIndex, char **oList);
	long GetList(UINT iIndex, char **oList, char delim);
#ifndef WLISTMAKER
	long GetList(UINT iIndex, BSTR FAR* OutListString);
	long SetListAsArray(UINT iIndex, VARIANT *iList);
	long GetListAsArray(UINT iIndex, VARIANT *iList);
	long GetListInfo(UINT iIndex, VARIANT FAR* ListInfo);
#endif
	UINT DeleteList(UINT iIndex);
	UINT SquiseList(UINT iIndex);
	UINT UniqueList(UINT iIndex);
	void Sort(UINT iIndex, UINT left, UINT right);
	void SortDesc(UINT iIndex, UINT left, UINT right);
	void SortList(UINT iIndex);
	void SortListDesc(UINT iIndex);
	UINT AddList(UINT idestIndex, UINT isrcIndex);
	UINT GetListState(UINT iIndex);
	UINT AppendList(UINT iIndex, const char * iList);
	const char * GetListItem(UINT iIndex, UINT iNItem);
	UINT GetListLength(UINT iIndex);
	UINT GetListItemCount(UINT iIndex);
	char GetListDelimiter(UINT iIndex);
	char SetListDelimiter(UINT iIndex,char newDelimiter);
	UINT SetList(UINT iIndex, const char *iList,char delimiter);
	UINT GetListIndex(const char *LName);
	char ** cListArray;
	char *** ListPointers;
	char * cDelmiterArray;
	UINT * unListsState;
	UINT * unListsElements;
	UINT * unListsLength;
	char ** ListsName;
	UINT nLists;
	UINT nMaxLists;
};

#endif // !defined(AFX_LISTMAKER_H__67AB5043_3AE5_4F11_9CE1_CBA8C337274A__INCLUDED_)
