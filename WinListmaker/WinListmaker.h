// WinListmaker.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

	int SaveList(const char *nmlist, const char *nmFile);
	int DoMethod(char *iStr, char **oStr);
	long NotBeginContextLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	long BeginContextLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	long NotEndContextLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	long EndContextLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	long NotContextLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	long NotMaskLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	long MaskLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	long ContextLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	long XORLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	long ANDLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	long NOTLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	long ORLists(const char *DestName, const char *SrcName1, const char *SrcName2);
	long SquiseListC(const char *iName);
	long DuplicateList(const char *iName, const char *SourceName);
	long UniqueListC(const char *iName);
	void SortListC(const char *iName);
	long AddListC(const char *destList,const char *srcList);
	long AppendListC(const char *iName, const char * iList);
	long GetListItemCountC(const char *iName);
	long GetListStateC(const char *iName);
	long GetListLengthC(const char *iName);
	const char * GetListItemC(const char *iName, long iNItem);
	char GetListDelimiterC(const char *iName);
	char SetListDelimiterC(const char *iName,char newDelimiter);
	long GetCount();
	long SetListC(const char *iName, const char *iList,char delimiter);
	long LoadList(const char *iName);
	long CreateList(const char * iName);
	long DeleteListC(const char *iName);
	long DeleteList(long iIndex);
	long SquiseList(long iIndex);
	long UniqueList(long iIndex);
	void Sort(long iIndex, long left, long right);
	void SortList(long iIndex);
	long AddList(long idestIndex, long isrcIndex);
	long GetListState(long iIndex);
	long AppendList(long iIndex, const char * iList);
	const char * GetListItem(long iIndex, long iNItem);
	long GetListLength(long iIndex);
	long GetListItemCount(long iIndex);
	char GetListDelimiter(long iIndex);
	char SetListDelimiter(long iIndex,char newDelimiter);
	long SetList(long iIndex, const char *iList,char delimiter);
	long GetListIndex(const char *LName);


	char ** cListArray;
	char *** ListPointers;
	char * cDelmiterArray;
	long * unListsState;
	long * unListsElements;
	long * unListsLength;
	char  **ListsName;
	long nLists;
	long nMaxLists;
	char IdPort[100];
	char ListsPath[256];
	int m_Echo=0;

