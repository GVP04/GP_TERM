// ListMaker.cpp: implementation of the CListMaker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#ifndef WLISTMAKER
	#include "GP_Term.h"
	#include "ListMaker.h"
#else
	#include ".\ListMaker.h"
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListMaker::CListMaker()
{
	nMaxLists=50;
	nLists=0;
	cListArray=new char * [nMaxLists+10];
	ListsName= new char * [nMaxLists+10];
	ListPointers=new char ** [nMaxLists+10];
	unListsElements=new UINT [nMaxLists+10];
	unListsLength=new UINT [nMaxLists+10];
	unListsState=new UINT [nMaxLists+10];
	cDelmiterArray=new char [nMaxLists+10];


	UINT i;
	for(i=0;i<nMaxLists;i++)
	{
		cListArray[i]=NULL;
		ListsName[i]=NULL;
		ListPointers[i]=NULL;
		unListsState[i]=0;
		unListsElements[i]=0;
		unListsLength[i]=0;
		cDelmiterArray[i]=GPC.DelimiterIn1;
	}
}

CListMaker::~CListMaker()
{
	UINT i;
	if (cListArray!=NULL)
	{
		for(i=0;i<nLists;i++)
			if (cListArray[i]!=NULL)
			{
				delete[] cListArray[i];
				cListArray[i]=NULL;
			}
		delete[] cListArray;
		cListArray=NULL;
	}
	if (ListsName!=NULL)
	{
		for(i=0;i<nLists;i++)
			if (ListsName[i]!=NULL) 
			{
				delete[] ListsName[i];
				ListsName[i]=NULL;
			}
		delete[] ListsName;
		ListsName=NULL;
	}

	if (ListPointers!=NULL)
	{
		for(i=0;i<nLists;i++)
			if (ListPointers[i]!=NULL) 
			{
				delete[] ListPointers[i];
				ListPointers[i]=NULL;
			}
		delete[] ListPointers;
		ListPointers=NULL;
	}
	if (unListsElements!=NULL)	delete[] unListsElements;
	unListsElements=NULL;
	if (unListsLength!=NULL)	delete[] unListsLength;
	unListsLength=NULL;
	if (cDelmiterArray!=NULL)	delete[] cDelmiterArray;
	cDelmiterArray=NULL;
	if (unListsState!=NULL)		delete[] unListsState;
	unListsState=NULL;
}
UINT CListMaker::DeleteList(const char *iName)
	{return DeleteList(GetListIndex(iName));}

UINT CListMaker::DeleteList(UINT iIndex)
{
	if (iIndex<nLists)
	{
		if (cListArray && cListArray[iIndex])
		{
			delete[] cListArray[iIndex];
			cListArray[iIndex]=NULL;
		}
		if (ListsName && ListsName[iIndex]) 
		{
			delete[] ListsName[iIndex];
			ListsName[iIndex]=NULL;
		}

		if (ListPointers && ListPointers[iIndex]) 
		{
			delete[] ListPointers[iIndex];
			ListPointers[iIndex]=NULL;
		}
		nLists--;
		UINT i;
		for(i=iIndex; i<nLists;i++)
		{
			if (cListArray)		cListArray[i]=cListArray[i+1];
			if (ListsName)		ListsName[i]=ListsName[i+1];
			if (ListPointers)	ListPointers[i]=ListPointers[i+1];
			unListsElements[i]=unListsElements[i+1];
			unListsState[i]=unListsState[i+1];
			unListsLength[i]=unListsLength[i+1];
			cDelmiterArray[i]=cDelmiterArray[i+1];
		}
		if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwDeleteList++;
		if (cListArray)		cListArray[i]=NULL;
		if (ListsName)		ListsName[i]=NULL;
		if (ListPointers)	ListPointers[i]=NULL;
		unListsState[i]=0;
		unListsElements[i]=0;
		unListsLength[i]=0;
		cDelmiterArray[i]=GPC.DelimiterIn1;
	}

	return nLists;
}

UINT CListMaker::GetListIndex(const char *LName)
{
	UINT ret=-1;
	if (ListsName!=NULL)
		for(ret=0;ret<nLists;ret++)
			if (ListsName[ret]!=NULL &&  strcmp(ListsName[ret],LName)==0) break; 
	return ret==nLists?-1:ret;
}

UINT CListMaker::CreateList(const char *iName)
{
	BOOL CreateOk=TRUE;
	while(CreateOk && (nLists>=nMaxLists-1 || nMaxLists==0))
	{
		nMaxLists+=50;
		char ** cListArrayT=new char * [nMaxLists];
		char ** ListsNameT= new char * [nMaxLists];
		char *** ListPointersT=new char ** [nMaxLists];
		UINT *unListsElementsT=new UINT [nMaxLists];
		UINT *unListsStateT=new UINT [nMaxLists];
		UINT *unListsLengthT=new UINT [nMaxLists];
		char * cDelmiterArrayT=new char [nMaxLists];

		try
		{
			UINT i;
			for(i=0;i<nLists;i++)
			{
				cListArrayT[i]=cListArray[i];
				ListsNameT[i]=ListsName[i];
				ListPointersT[i]=ListPointers[i];
				unListsStateT[i]=unListsState[i];
				unListsElementsT[i]=unListsElements[i];
				unListsLengthT[i]=unListsLength[i];
				cDelmiterArrayT[i]=cDelmiterArray[i];
			}
			for(;i<nMaxLists;i++)
			{
				cListArrayT[i]=NULL;
				ListsNameT[i]=NULL;
				ListPointersT[i]=NULL;
				unListsState[i]=0;
				unListsElementsT[i]=0;
				unListsLengthT[i]=0;
				cDelmiterArrayT[i]=GPC.DelimiterIn1;
			}
		}
		catch(...)
		{CreateOk=FALSE;}

		if (CreateOk)
		{
			delete[] cListArray;
			delete[] ListsName;
			delete[] ListPointers;
			delete[] unListsState;
			delete[] unListsElements;
			delete[] unListsLength;
			delete[] cDelmiterArray;
			cListArray=cListArrayT;
			ListsName=ListsNameT;
			ListPointers=ListPointersT;
			unListsState=unListsStateT;
			unListsElements=unListsElementsT;
			unListsLength=unListsLengthT;
			cDelmiterArray=cDelmiterArrayT;
		}
		else
		{
			delete[] cListArrayT;
			delete[] ListsNameT;
			delete[] ListPointersT;
			delete[] unListsStateT;
			delete[] unListsElementsT;
			delete[] unListsLengthT;
			delete[] cDelmiterArrayT;
		}

	}

	if (CreateOk)
	{
		DeleteList(iName);
		if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwCreateList++;

		ListsName[nLists]=new char[50];
		strcpy(ListsName[nLists],iName);
		cListArray[nLists]=new char [5];
		*cListArray[nLists]=0;
		ListPointers[nLists]=new char * [2];
		*ListPointers[nLists]=cListArray[nLists];
		unListsState[nLists]=0;
		unListsElements[nLists]=0;
		unListsLength[nLists]=0;
		cDelmiterArray[nLists]=GPC.DelimiterIn1;
	}

	return CreateOk?nLists++:-1;
}

UINT CListMaker::SetList(const char *iName, const char *iList,char delimiter)
{
	CreateList(iName);
	return SetList(GetListIndex(iName),iList,delimiter);
}

UINT CListMaker::SetList(UINT iIndex, const char *iList,char delimiter)
{
	UINT ret=-1;
	if (iIndex<nLists)
	{
		if (cListArray[iIndex]!=NULL) delete[] cListArray[iIndex];
		cListArray[iIndex]=NULL;
		if (ListPointers[iIndex]!=NULL) delete[] ListPointers[iIndex];
		ListPointers[iIndex]=NULL;
		unListsState[iIndex]=0;
		unListsElements[iIndex]=0;
		unListsLength[iIndex]=0;
		cDelmiterArray[iIndex]=delimiter;
		UINT nElem=0;

		const char *pos=iList;
		while(*pos!=0)
		{
			if (*pos==delimiter) nElem++;
			pos++;
		}
		unListsLength[iIndex]=pos-iList;
		if (unListsLength[iIndex])
		{
			nElem++;
			ret=unListsElements[iIndex]=nElem;
			cListArray[iIndex]=new char [unListsLength[iIndex]+5];
			ListPointers[iIndex]=new char * [nElem+5];

			char *posDest=cListArray[iIndex];
			*ListPointers[iIndex]=posDest;
			pos=iList;
			nElem=0;

			while((*posDest=*pos)!=0)
			{
				if (*posDest==delimiter) 
				{
					nElem++;
					ListPointers[iIndex][nElem]=posDest+1;
					*posDest=0;
				}
				posDest++;
				pos++;
			}
		}
	}

	return ret;
}

UINT CListMaker::GetCount()	
	{return nLists;}

UINT CListMaker::GetListItemCount(const char *iName)
	{return GetListItemCount(GetListIndex(iName));}

char CListMaker::GetListDelimiter(const char *iName)
	{return GetListDelimiter(GetListIndex(iName));}

char CListMaker::SetListDelimiter(const char *iName,char newDelimiter)
	{return SetListDelimiter(GetListIndex(iName),newDelimiter);}

UINT CListMaker::GetListItemCount(UINT iIndex)
	{return (iIndex<nLists)?unListsElements[iIndex]:-1;}

UINT CListMaker::GetListState(const char *iName)
	{return GetListState(GetListIndex(iName));}

UINT CListMaker::GetListState(UINT iIndex)
	{return (iIndex<nLists)?unListsState[iIndex]:-1;}

char CListMaker::GetListDelimiter(UINT iIndex)
	{return (iIndex<nLists)?cDelmiterArray[iIndex]:0;}

char CListMaker::SetListDelimiter(UINT iIndex,char newDelimiter)
	{return (iIndex<nLists)?cDelmiterArray[iIndex]=newDelimiter:0;}

const char * CListMaker::GetListItem(const char *iName, UINT iNItem)
	{return GetListItem(GetListIndex(iName),iNItem);}

const char * CListMaker::GetListItem(UINT iIndex, UINT iNItem)
	{return (iIndex<nLists && ListPointers[iIndex]!=NULL && iNItem<unListsElements[iIndex])?ListPointers[iIndex][iNItem]:NULL;}

UINT CListMaker::GetListLength(const char *iName)
	{return GetListLength(GetListIndex(iName));}

UINT CListMaker::GetListLength(UINT iIndex)
	{return (iIndex<nLists)?unListsLength[iIndex]:-1;}


UINT CListMaker::AppendList(const char *iName, const char * iList)
{
	UINT iInd= GetListIndex(iName);
	if (iInd>=nLists) CreateList(iName);
	return AppendList(GetListIndex(iName),iList);
}

UINT CListMaker::AppendList(UINT iIndex, const char * iList)
{
	UINT ret=-1;
	if (iIndex<nLists)
	{
		UINT nElem=0;
		char delimiter=cDelmiterArray[iIndex];
		const char *pos=iList;
		while(*pos!=0)
		{
			if (*pos==delimiter) nElem++;
			pos++;
		}

		UINT appLen=pos-iList;
		if (appLen>0)
		{
			nElem++;
			UINT newLen=unListsLength[iIndex]+pos-iList;
			UINT newElem=unListsElements[iIndex]+nElem;
			UINT oldElem=unListsElements[iIndex];

			char ** tmpListPointers= new char * [newElem+5];
			char *  tmpListArray= new char [newLen+5+newElem];
			char *postmpD=tmpListArray+unListsLength[iIndex]+oldElem;
			char *postmpS=cListArray[iIndex]+unListsLength[iIndex]+oldElem;
			*postmpD=0;
			if (postmpS==NULL) postmpD--;
			else
				do 
				{
					if (postmpS) *postmpD=*(postmpS--);
				}
				while(postmpD--!=tmpListArray);

			char ** tmppos=ListPointers[iIndex];
			int delta=cListArray[iIndex]-tmpListArray;
			if (cListArray[iIndex]!=NULL)
			{
				UINT i;
				for(i=0;i<oldElem;i++)
					tmpListPointers[i]=tmppos[i]-delta;
			}
			char *posDest=tmpListArray+unListsLength[iIndex]+oldElem;
			char **tmpPoints=tmpListPointers+oldElem;
			*tmpPoints=posDest;
			pos=iList;
			nElem=0;
			while((*posDest=*pos)!=0)
			{
				if (*posDest==delimiter) 
				{
					nElem++;
					tmpPoints[nElem]=posDest+1;
					*posDest=0;
				}
				posDest++;
				pos++;
			}

			unListsElements[iIndex]	=newElem;
			unListsState[iIndex]	=0;
			unListsLength[iIndex]	=newLen;
			if (ListPointers[iIndex]!=NULL)	delete[] ListPointers[iIndex];
			if (cListArray[iIndex]!=NULL) delete[] cListArray[iIndex];
			cListArray[iIndex]=tmpListArray;
			ListPointers[iIndex]=tmpListPointers;
		}
	}

	return ret;

}


UINT CListMaker::AddList(const char *destList, const char *srcList)
{
	UINT iInd= GetListIndex(destList);
	if (iInd>=nLists) CreateList(destList);
	return AddList(GetListIndex(destList),GetListIndex(srcList));
}

UINT CListMaker::AddList(UINT idestIndex, UINT isrcIndex)
{
	UINT ret=0;
	if (idestIndex<nLists)
	{
		if (isrcIndex<nLists)
		{
			UINT newLen=unListsLength[idestIndex]+unListsLength[isrcIndex]+1;
			UINT newElem=unListsElements[idestIndex]+unListsElements[isrcIndex];

			char ** tmpListPointers= new char * [newElem+5];
			char *  tmpListArray= new char [newLen+5];

			char *postmpD=tmpListArray;
			char *postmpS=cListArray[idestIndex];
			UINT lentmp=unListsLength[idestIndex];

			do
				*(postmpD++)=*(postmpS++);
			while(lentmp-->0);

			char ** tmppos=ListPointers[idestIndex];
			int delta=cListArray[idestIndex]-tmpListArray;
			UINT tmpnElem=unListsElements[idestIndex];
			UINT i;
			for(i=0;i<tmpnElem;i++)
				tmpListPointers[i]=tmppos[i]-delta;

			tmppos=ListPointers[isrcIndex];
			delta=cListArray[isrcIndex]-postmpD;

			postmpS=cListArray[isrcIndex];
			lentmp=unListsLength[isrcIndex];
			do
				*(postmpD++)=*(postmpS++);
			while(lentmp-->0);

			char ** tmpListPointers2=tmpListPointers+i;
			tmpnElem=unListsElements[isrcIndex];
			for(i=0;i<tmpnElem;i++)
				tmpListPointers2[i]=tmppos[i]-delta;

			unListsElements[idestIndex]	=newElem;
			unListsState[idestIndex]	=0;
			unListsLength[idestIndex]	=newLen;
			delete[] ListPointers[idestIndex];
			delete[] cListArray[idestIndex];
			cListArray[idestIndex]=tmpListArray;
			ListPointers[idestIndex]=tmpListPointers;

		}
		ret=unListsElements[idestIndex];
	}

	return ret;
}


void CListMaker::SortList(const char *iName)
	{SortList(GetListIndex(iName));}

void CListMaker::SortListDesc(const char *iName)
	{SortListDesc(GetListIndex(iName));}

void CListMaker::SortList(UINT iIndex)
{
	if (iIndex<nLists && cListArray[iIndex]!=NULL && ListPointers[iIndex]!=NULL && unListsElements[iIndex]>0 && (unListsState[iIndex]&0x1)==0)
	{
		Sort(iIndex,0,unListsElements[iIndex]-1);
		unListsState[iIndex]|=0x1;
	}
}

void CListMaker::SortListDesc(UINT iIndex)
{
	if (iIndex<nLists && cListArray[iIndex]!=NULL && ListPointers[iIndex]!=NULL && unListsElements[iIndex]>0 && (unListsState[iIndex]&0x1)==0)
	{
		SortDesc(iIndex,0,unListsElements[iIndex]-1);
		unListsState[iIndex]|=0x1;
	}
}

void CListMaker::Sort(UINT iIndex, UINT left, UINT right)
{
	long i,j;
	char *x,*y;

	if (iIndex<nLists && cListArray[iIndex]!=NULL && ListPointers[iIndex]!=NULL)
	{
		char ** item=ListPointers[iIndex];
		i=left;
		j=right;
		x=item[(left+right)/2];

		do
		{
			while(i<(long)right)
			{
				char *pos1=item[i];
				char *pos2=x;
				while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
				if (*pos1>=*pos2) break;
				i++;
			}

			while(j>(long)left)
			{
				char *pos1=item[j];
				char *pos2=x;
				while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
				if (*pos1<=*pos2) break;
				j--;
			}

			if (i<=j)
			{
				y=item[i];			item[i]=item[j];			item[j]=y;
				i++;				j--;
			}
		}while(i<=j);
		if((long)left<j) Sort(iIndex,left,j);
		if (i<(long)right) Sort(iIndex,i,right);
	}
}

void CListMaker::SortDesc(UINT iIndex, UINT left, UINT right)
{
	long i,j;
	char *x,*y;

	if (iIndex<nLists && cListArray[iIndex]!=NULL && ListPointers[iIndex]!=NULL)
	{
		char ** item=ListPointers[iIndex];
		i=left;
		j=right;
		x=item[(left+right)/2];

		do
		{
			while(i<(long)right)
			{
				char *pos1=item[i];
				char *pos2=x;
				while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
				if (*pos1<=*pos2) break;
				i++;
			}

			while(j>(long)left)
			{
				char *pos1=item[j];
				char *pos2=x;
				while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
				if (*pos1>=*pos2) break;
				j--;
			}

			if (i<=j)
			{
				y=item[i];			item[i]=item[j];			item[j]=y;
				i++;				j--;
			}
		}while(i<=j);
		if((long)left<j) SortDesc(iIndex,left,j);
		if (i<(long)right) SortDesc(iIndex,i,right);
	}
}

UINT CListMaker::UniqueList(const char *iName)
{
	return UniqueList(GetListIndex(iName));
}

UINT CListMaker::UniqueList(UINT iIndex)
{
	UINT ret=0;
	if (iIndex<nLists && (unListsState[iIndex]&0x2)==0)
	{
		if ((unListsState[iIndex]&0x1)==0) SortList(iIndex);
		UINT nItem=unListsElements[iIndex];
		char ** tmppos=ListPointers[iIndex];
		UINT npos=0;
		UINT i;
		for(i=1;i<nItem;i++)
		{
			char *pos1=tmppos[npos];
			char *pos2=tmppos[i];
			while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
			if (*pos1!=*pos2) npos++;
			tmppos[npos]=tmppos[i];
		}
		unListsElements[iIndex]=++npos;
		unListsState[iIndex]|=0x2;
	}
	return ret;
}

UINT CListMaker::DuplicateList(const char *iName, const char *SourceName)
{
	UINT ret=-1;
	UINT indexs=GetListIndex(SourceName);
	if (indexs<nLists && strcmp(iName,SourceName)!=0)
	{
		SquiseList(indexs);
		CreateList(iName);
		UINT indexd=GetListIndex(iName);
		if (indexd<nLists)
		{
			unListsState[indexd]=unListsState[indexs];
			unListsElements[indexd]=unListsElements[indexs];
			unListsLength[indexd]=unListsLength[indexs];
			cDelmiterArray[indexd]=cDelmiterArray[indexs];

			cListArray[indexd]=new char [unListsLength[indexd]+5];
			ListPointers[indexd]=new char * [unListsElements[indexd]+5];

			char *postmpD=cListArray[indexd];
			char *postmpS=cListArray[indexs];
			UINT lentmp=unListsLength[indexs];

			do
				*(postmpD++)=*(postmpS++);
			while(lentmp-->0);

			char ** tmppos=ListPointers[indexs];
			char ** tmpposd=ListPointers[indexd];
			int delta=cListArray[indexs]-cListArray[indexd];
			UINT tmpnElem=unListsElements[indexd];
			UINT i;
			for(i=0;i<tmpnElem;i++)
				tmpposd[i]=tmppos[i]-delta;

			ret=indexd;
		}
	}
	return ret;
}


UINT CListMaker::SquiseList(const char *iName)
	{return SquiseList(GetListIndex(iName));}

UINT CListMaker::SquiseList(UINT iIndex)
{
	UINT ret=-1;
	if (iIndex<nLists && cListArray[iIndex]!=NULL)
	{
		UINT nElem=unListsElements[iIndex];
		UINT i;
		char **tmppos=ListPointers[iIndex];
		UINT newLen=0;
		for(i=0;i<nElem;i++)
		{
			char *pos2=tmppos[i];
			while(*pos2++!=0);
			newLen+=(pos2-tmppos[i]);
		}
		char *tmpList=new char [newLen+5];
		char **tmpPointer= new char * [nElem+5];
		char *posDest=tmpList;
		for(i=0;i<nElem;i++)
		{
			char *pos2=tmppos[i];
			tmpPointer[i]=posDest;
			while((*(posDest++)=*(pos2++))!=0);
		}

		unListsElements[iIndex]	=nElem;
		unListsState[iIndex]	&=(0xFFFFFFFF^0x2);
		unListsLength[iIndex]	=newLen;
		delete[] ListPointers[iIndex];
		delete[] cListArray[iIndex];
		cListArray[iIndex]=tmpList;
		ListPointers[iIndex]=tmpPointer;
		ret=nElem;
	}
	return ret;
}

UINT CListMaker::ORLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	UINT ret=-1;
	UINT index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		SortList(index1);
		UniqueList(index1);
		UINT index2=GetListIndex(SrcName2);
		if (index2<nLists)
		{
			SortList(index2);
			UniqueList(index2);
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			UINT newNElem=0;
			UINT nElem1=unListsElements[index1];
			UINT nElem2=unListsElements[index2];
			UINT newLen=0;
			UINT c1=0,c2=0;
			while(c1<nElem1)
			{
				while(c2<nElem2)
				{
					char *pos1=tmppos1[c1];
					char *pos2=tmppos2[c2];
					while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
					if (*pos1<*pos2) break;
					if (*pos1>*pos2)
					{
						while(*(pos2++)!=0);
						newLen+=(pos2-tmppos2[c2]);
						newNElem++;
					}
					c2++;
				}
				if (c2>=nElem2) break;
				{
					char *pos1=tmppos1[c1];
					char *pos2=tmppos2[c2];
					while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
					if (*pos1>*pos2) continue;
					if (*pos1<=*pos2)
					{
						while(*(pos1++)!=0);
						newLen+=(pos1-tmppos1[c1]);
						newNElem++;
					}
					c1++;
				}
			}
			while(c2<nElem2)
			{
				char *pos2=tmppos2[c2];
				while(*(pos2++)!=0);
				newLen+=(pos2-tmppos2[c2]);
				newNElem++;
				c2++;
			}
			while(c1<nElem1)
			{
				char *pos1=tmppos1[c1];
				while(*(pos1++)!=0);
				newLen+=(pos1-tmppos1[c1]);
				newNElem++;
				c1++;
			}

			CreateList("ortmplist");
			UINT newindex=GetListIndex("ortmplist");
			if (newindex<nLists)
			{
				ret=unListsElements[newindex]	=newNElem;
				unListsState[newindex]=0x3;
				unListsLength[newindex]	=newLen;
				cListArray[newindex]=new char [newLen+5];
				ListPointers[newindex]=new char * [newNElem+5];;
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					UINT NElem=0;
					c1=0,c2=0;
					while(c1<nElem1)
					{
						while(c2<nElem2)
						{
							char *pos1=tmppos1[c1];
							char *pos2=tmppos2[c2];
							while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
							if (*pos1<*pos2) break;
							if (*pos1>*pos2)
							{
								tmpposDest[NElem++]=posDest;
								pos2=tmppos2[c2];
								while((*(posDest++)=*(pos2++))!=0);
							}
							c2++;
						}
						if (c2>=nElem2) break;
						{
							char *pos1=tmppos1[c1];
							char *pos2=tmppos2[c2];
							while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
							if (*pos1>*pos2) continue;
							if (*pos1<=*pos2)
							{
								tmpposDest[NElem++]=posDest;
								pos1=tmppos1[c1];
								while((*(posDest++)=*(pos1++))!=0);
							}
							c1++;
						}
					}

					while(c2<nElem2)
					{
						char *pos2=tmppos2[c2];
						tmpposDest[NElem++]=posDest;
						while((*(posDest++)=*(pos2++))!=0);
						c2++;
					}
					while(c1<nElem1)
					{
						char *pos1=tmppos1[c1];
						tmpposDest[NElem++]=posDest;
						while((*(posDest++)=*(pos1++))!=0);
						c1++;
					}
				}

				{
					DeleteList(DestName);
					UINT tmpid=GetListIndex("ortmplist");
					strcpy(ListsName[tmpid],DestName);
				}
			}
		}
	}

	return ret;
}

UINT CListMaker::XORLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	UINT ret=-1;
	UINT index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		UINT index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			UINT newindex;
			UINT newNElem=0;
			UINT nElem1=unListsElements[index1];
			UINT nElem2=unListsElements[index2];
			UINT newLen=0;
			UINT c1=0,c2=0;

			SortList(index2);
			UniqueList(index2);
			while(c1<nElem1)
			{
				int flgUNI=0;
				while(c2<nElem2)
				{
					char *pos1=tmppos1[c1];
					char *pos2=tmppos2[c2];
					while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
					if (*pos1<*pos2) break;
					if (*pos1==*pos2) flgUNI=1;
					if (*pos1>*pos2)
					{
						while(*(pos2++)!=0);
						newLen+=(pos2-tmppos2[c2]);
						newNElem++;
					}
					c2++;
				}
				if (c2>=nElem2) break;
				{
					char *pos1=tmppos1[c1];
					char *pos2=tmppos2[c2];
					while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
					if (*pos1<*pos2)
					{
						if (flgUNI==0)
						{
							while(*(pos1++)!=0);
							newLen+=(pos1-tmppos1[c1]);
							newNElem++;
						}
					}
					c1++;
				}
			}
			while(c2<nElem2)
			{
				char *pos2=tmppos2[c2];
				while(*(pos2++)!=0);
				newLen+=(pos2-tmppos2[c2]);
				newNElem++;
				c2++;
			}
			while(c1<nElem1)
			{
				char *pos1=tmppos1[c1];
				while(*(pos1++)!=0);
				newLen+=(pos1-tmppos1[c1]);
				newNElem++;
				c1++;
			}

			CreateList("ortmplist");
			newindex=GetListIndex("ortmplist");
			if (newindex<nLists)
			{
				ret=unListsElements[newindex]	=newNElem;
				unListsState[newindex]=0x3;
				unListsLength[newindex]	=newLen;
				cListArray[newindex]=new char [newLen+5];
				ListPointers[newindex]=new char * [newNElem+5];
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					UINT NElem=0;

					c1=0,c2=0;
					while(c1<nElem1)
					{
						int flgUNI=0;
						while(c2<nElem2)
						{
							char *pos1=tmppos1[c1];
							char *pos2=tmppos2[c2];
							while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
							if (*pos1<*pos2) break;
							if (*pos1==*pos2) flgUNI=1;
							if (*pos1>*pos2)
							{
								tmpposDest[NElem++]=posDest;
								pos2=tmppos2[c2];
								while((*(posDest++)=*(pos2++))!=0);
							}
							c2++;
						}
						if (c2>=nElem2) break;
						{
							char *pos1=tmppos1[c1];
							char *pos2=tmppos2[c2];
							while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}

							if (*pos1<*pos2)
							{
								if (flgUNI==0)
								{
									tmpposDest[NElem++]=posDest;
									pos1=tmppos1[c1];
									while((*(posDest++)=*(pos1++))!=0);
								}
							}
							c1++;
						}
					}

					while(c2<nElem2)
					{
						char *pos2=tmppos2[c2];
						tmpposDest[NElem++]=posDest;
						while((*(posDest++)=*(pos2++))!=0);
						c2++;
					}
					while(c1<nElem1)
					{
						char *pos1=tmppos1[c1];
						tmpposDest[NElem++]=posDest;
						while((*(posDest++)=*(pos1++))!=0);
						c1++;
					}
				}
				{
					DeleteList(DestName);
					UINT tmpid=GetListIndex("ortmplist");
					strcpy(ListsName[tmpid],DestName);
				}
			}
		}
	}

	return ret;
}

UINT CListMaker::ANDLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	UINT ret=-1;
	UINT index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		UINT index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			UINT newNElem=0;
			UINT nElem1=unListsElements[index1];
			UINT nElem2=unListsElements[index2];
			UINT newLen=0;
			UINT c1=0,c2=0;
			UINT newindex;
			SortList(index2);
			UniqueList(index2);

			while(c1<nElem1)
			{
				int flgUNI=0;
				while(c2<nElem2)
				{
					char *pos1=tmppos1[c1];
					char *pos2=tmppos2[c2];
					while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
					if (*pos1<*pos2) break;
					if (*pos1==*pos2) {flgUNI=1;break;};
					c2++;
				}
				if (c2>=nElem2) break;
				{
					char *pos1=tmppos1[c1];
					char *pos2=tmppos2[c2];
					while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
					if (*pos1>*pos2) continue;
					if (*pos1==*pos2 && flgUNI==1)
					{
						while(*(pos1++)!=0);
						newLen+=(pos1-tmppos1[c1]);
						newNElem++;
					}
					c1++;
				}
			}

			CreateList("ortmplist");
			newindex=GetListIndex("ortmplist");
			if (newindex<nLists)
			{
				cListArray[newindex]=new char [newLen+5];
				ListPointers[newindex]=new char * [newNElem+5];;
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					UINT NElem=0;
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					ret=unListsElements[newindex]	=newNElem;
					unListsState[newindex]=0x3;
					unListsLength[newindex]	=newLen;
		
					c1=0,c2=0;
					while(c1<nElem1)
					{
						int flgUNI=0;
						while(c2<nElem2)
						{
							char *pos1=tmppos1[c1];
							char *pos2=tmppos2[c2];
							while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
							if (*pos1<*pos2) break;
							if (*pos1==*pos2) {flgUNI=1;break;};
							c2++;
						}
						if (c2>=nElem2) break;
						{
							char *pos1=tmppos1[c1];
							char *pos2=tmppos2[c2];
							while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
							if (*pos1>*pos2) continue;
							if (*pos1==*pos2 && flgUNI==1)
							{
								tmpposDest[NElem++]=posDest;
								pos1=tmppos1[c1];
								while((*(posDest++)=*(pos1++))!=0);
							}
							c1++;
						}
					}
				}

				{
					DeleteList(DestName);
					UINT tmpid=GetListIndex("ortmplist");
					strcpy(ListsName[tmpid],DestName);
				}
			}
		}
	}

	return ret;
}

UINT CListMaker::NOTLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	UINT ret=-1;
	UINT index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		UINT index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			UINT newNElem=0;
			UINT nElem1=unListsElements[index1];
			UINT nElem2=unListsElements[index2];
			UINT newLen=0;
			UINT c1=0,c2=0;
			UINT newindex;

			SortList(index2);
			UniqueList(index2);
			while(c1<nElem1)
			{
				while(c2<nElem2)
				{
					char *pos1=tmppos1[c1];
					char *pos2=tmppos2[c2];
					while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
					if (*pos1<=*pos2) break;
					c2++;
				}
				if (c2>=nElem2) break;
				{
					char *pos1=tmppos1[c1];
					char *pos2=tmppos2[c2];
					while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
					if (*pos1<*pos2)
					{
						while(*(pos1++)!=0);
						newLen+=(pos1-tmppos1[c1]);
						newNElem++;
					}
					else if (*pos1>*pos2) continue;
					c1++;
				}
			}
			while(c1<nElem1)
			{
				char *pos1=tmppos1[c1];
				while(*(pos1++)!=0);
				newLen+=(pos1-tmppos1[c1]);
				newNElem++;
				c1++;
			}

			CreateList("ortmplist");
			newindex=GetListIndex("ortmplist");
			if (newindex<nLists)
			{
				ret=unListsElements[newindex]	=newNElem;
				unListsState[newindex]=0x3;
				unListsLength[newindex]	=newLen;
				cListArray[newindex]=new char [newLen+5];
				ListPointers[newindex]=new char * [newNElem+5];;
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					UINT NElem=0;
					c1=0,c2=0;
					while(c1<nElem1)
					{
						while(c2<nElem2)
						{
							char *pos1=tmppos1[c1];
							char *pos2=tmppos2[c2];
							while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
							if (*pos1<=*pos2) break;
							c2++;
						}
						if (c2>=nElem2) break;
						{
							char *pos1=tmppos1[c1];
							char *pos2=tmppos2[c2];
							while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}

							if (*pos1<*pos2)
							{
								tmpposDest[NElem++]=posDest;
								pos1=tmppos1[c1];
								while((*(posDest++)=*(pos1++))!=0);
							}
							else if (*pos1>*pos2) continue;
							c1++;
						}
					}

					while(c1<nElem1)
					{
						char *pos1=tmppos1[c1];
						tmpposDest[NElem++]=posDest;
						while((*(posDest++)=*(pos1++))!=0);
						c1++;
					}
				}

				{
					DeleteList(DestName);
					UINT tmpid=GetListIndex("ortmplist");
					strcpy(ListsName[tmpid],DestName);
				}
			}
		}
	}

	return ret;
}


UINT CListMaker::ContextLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	UINT ret=-1;
	UINT index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		UINT index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			UINT newNElem=0;
			UINT nElem1=unListsElements[index1];
			UINT nElem2=unListsElements[index2];
			UINT newLen=0;
			UINT c1=0,c2=0;
			UINT newindex;

			SortList(index2);
			UniqueList(index2);
			while(c1<nElem1)
			{
				int flgUNI=0;
				c2=0;
				while(c2<nElem2)
				{
					char *pos1=tmppos1[c1];
					if (*tmppos2[c2]!=0)
					{
						while(*pos1!=0)
						{
							char *pos2=tmppos2[c2];
							char *reppos=pos1;
							while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
							if (*pos2==0) {flgUNI=1;break;}
							if (*pos1==0) break;
							pos1=++reppos;
						}

						if (flgUNI!=0) 
						{	
							while(*(pos1++)!=0);
							newLen+=(pos1-tmppos1[c1]);
							newNElem++;
							break;
						}
					}
					c2++;
				}
				c1++;
			}

			CreateList("ortmplist");
			newindex=GetListIndex("ortmplist");
			if (newindex<nLists)
			{
				ret=unListsElements[newindex]	=newNElem;
				unListsState[newindex]=0x3;
				unListsLength[newindex]	=newLen;
				cListArray[newindex]=new char [newLen+5];
				ListPointers[newindex]=new char * [newNElem+5];
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					UINT NElem=0;
					c1=0,c2=0;
					while(c1<nElem1)
					{
						int flgUNI=0;
						c2=0;
						while(c2<nElem2)
						{
							char *pos1=tmppos1[c1];
							if (*tmppos2[c2]!=0) 
							{
								while(*pos1!=0)
								{
									char *pos2=tmppos2[c2];
									char *reppos=pos1;
									while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
									if (*pos2==0) {flgUNI=1;break;}
									if (*pos1==0) break;
									pos1=++reppos;
								}

								if (flgUNI!=0) 
								{	
									tmpposDest[NElem++]=posDest;
									pos1=tmppos1[c1];
									while((*(posDest++)=*(pos1++))!=0);
									break;
								}
							}
							c2++;
						}
						c1++;
					}
				}

				{
					DeleteList(DestName);
					UINT tmpid=GetListIndex("ortmplist");
					strcpy(ListsName[tmpid],DestName);
				}
			}
		}
	}

	return ret;
}

UINT CListMaker::BeginContextLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	UINT ret=-1;
	UINT index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		UINT index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			UINT newNElem=0;
			UINT nElem1=unListsElements[index1];
			UINT nElem2=unListsElements[index2];
			UINT newLen=0;
			UINT c1=0,c2=0;
			UINT newindex;

			SortList(index2);
			UniqueList(index2);
			while(c1<nElem1)
			{
				int flgUNI=0;
				char *pos1=tmppos1[c1];
				c2=0;
				while(c2<nElem2)
				{
					char *pos2=tmppos2[c2];
					pos1=tmppos1[c1];
					if (*pos2!=0)
					{
						while(*pos1==*pos2 && *pos2!=0) {pos1++;pos2++;}
						if (*pos2==0) {flgUNI=1;break;}
					}
					c2++;
				}
				if (flgUNI!=0) 
				{	
					while(*(pos1++)!=0);
					newLen+=(pos1-tmppos1[c1]);
					newNElem++;
				}
				c1++;
			}

			CreateList("ortmplist");
			newindex=GetListIndex("ortmplist");
			if (newindex<nLists)
			{
				ret=unListsElements[newindex]	=newNElem;
				unListsState[newindex]=0x3;
				unListsLength[newindex]	=newLen;
				cListArray[newindex]=new char [newLen+5];
				ListPointers[newindex]=new char * [newNElem+5];
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					UINT NElem=0;
					c1=0,c2=0;
					while(c1<nElem1)
					{
						int flgUNI=0;
						c2=0;
						while(c2<nElem2)
						{
							char *pos1=tmppos1[c1];
							char *pos2=tmppos2[c2];
							if (*pos2!=0)
							{
								while(*pos1==*pos2 && *pos2!=0) {pos1++;pos2++;}
								if (*pos2==0) {flgUNI=1;break;}
							}
							c2++;
						}
						if (flgUNI!=0) 
						{	
							char *pos1=tmppos1[c1];
							tmpposDest[NElem++]=posDest;
							while((*(posDest++)=*(pos1++))!=0);
						}
						c1++;
					}
				}

				{
					DeleteList(DestName);
					UINT tmpid=GetListIndex("ortmplist");
					strcpy(ListsName[tmpid],DestName);
				}
			}
		}
	}

	return ret;
}

UINT CListMaker::NotBeginContextLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	UINT ret=-1;
	UINT index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		UINT index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			UINT newNElem=0;
			UINT nElem1=unListsElements[index1];
			UINT nElem2=unListsElements[index2];
			UINT newLen=0;
			UINT c1=0,c2=0;
			UINT newindex;

			SortList(index2);
			UniqueList(index2);
			while(c1<nElem1)
			{
				char *pos1=tmppos1[c1];
				int flgUNI=0;
				c2=0;
				while(c2<nElem2)
				{
					char *pos2=tmppos2[c2];
					pos1=tmppos1[c1];
					if (*pos2==0) break;
					while(*pos1==*pos2 && *pos2!=0) {pos1++;pos2++;}
					if (*pos2==0) {flgUNI=1;break;}
					c2++;
				}
				if (flgUNI==0) 
				{	
					while(*(pos1++)!=0);
					newLen+=(pos1-tmppos1[c1]);
					newNElem++;
				}
				c1++;
			}

			CreateList("ortmplist");
			newindex=GetListIndex("ortmplist");
			if (newindex<nLists)
			{
				ret=unListsElements[newindex]	=newNElem;
				unListsState[newindex]=0x3;
				unListsLength[newindex]	=newLen;
				cListArray[newindex]=new char [newLen+5];
				ListPointers[newindex]=new char * [newNElem+5];
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					UINT NElem=0;
					c1=0,c2=0;
					while(c1<nElem1)
					{
						int flgUNI=0;
						c2=0;
						while(c2<nElem2)
						{
							char *pos1=tmppos1[c1];
							char *pos2=tmppos2[c2];
							if (*pos2==0) break;
							while(*pos1==*pos2 && *pos2!=0) {pos1++;pos2++;}
							if (*pos2==0) {flgUNI=1;break;}
							c2++;
						}
						if (flgUNI==0) 
						{	
							char *pos1=tmppos1[c1];
							tmpposDest[NElem++]=posDest;
							while((*(posDest++)=*(pos1++))!=0);
						}
						c1++;
					}
				}

				{
					DeleteList(DestName);
					UINT tmpid=GetListIndex("ortmplist");
					strcpy(ListsName[tmpid],DestName);
				}
			}
		}
	}

	return ret;
}

UINT CListMaker::EndContextLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	UINT ret=-1;
	UINT index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		UINT index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			UINT newNElem=0;
			UINT nElem1=unListsElements[index1];
			UINT nElem2=unListsElements[index2];
			UINT newLen=0;
			UINT c1=0,c2=0;
			UINT newindex;

			SortList(index2);
			UniqueList(index2);
			while(c1<nElem1)
			{
				int flgUNI=0;
				char *pos1=tmppos1[c1];
				c2=0;
				while(c2<nElem2)
				{
					char *pos2=tmppos2[c2];
					pos1=tmppos1[c1];
					if (*pos2!=0) 
					{
						while(*pos1!=0) pos1++;
						while(*pos2!=0) {pos1--;pos2++;}
						if (pos1>=tmppos1[c1]) 
						{
							pos2=tmppos2[c2];
							while(*pos1==*pos2 && *pos2!=0) {pos1++;pos2++;}
							if (*pos2==0) {flgUNI=1;break;}
						}
					}
					c2++;
				}
				if (flgUNI!=0) 
				{	
					while(*(pos1++)!=0);
					newLen+=(pos1-tmppos1[c1]);
					newNElem++;
				}
				c1++;
			}

			CreateList("ortmplist");
			newindex=GetListIndex("ortmplist");
			if (newindex<nLists)
			{
				ret=unListsElements[newindex]	=newNElem;
				unListsState[newindex]=0x3;
				unListsLength[newindex]	=newLen;
				cListArray[newindex]=new char [newLen+5];
				ListPointers[newindex]=new char * [newNElem+5];
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					UINT NElem=0;
					c1=0,c2=0;
					while(c1<nElem1)
					{
						int flgUNI=0;
						c2=0;
						while(c2<nElem2)
						{
							char *pos1=tmppos1[c1];
							char *pos2=tmppos2[c2];
							if (*pos2!=0)
							{
								while(*pos1!=0) pos1++;
								while(*pos2!=0) {pos1--;pos2++;}
								if (pos1>=tmppos1[c1])
								{
									pos2=tmppos2[c2];
									while(*pos1==*pos2 && *pos2!=0) {pos1++;pos2++;}
									if (*pos2==0) {flgUNI=1;break;}
								}
							}
							c2++;
						}
						if (flgUNI!=0) 
						{	
							char *pos1=tmppos1[c1];
							tmpposDest[NElem++]=posDest;
							while((*(posDest++)=*(pos1++))!=0);
						}
						c1++;
					}
				}

				{
					DeleteList(DestName);
					UINT tmpid=GetListIndex("ortmplist");
					strcpy(ListsName[tmpid],DestName);
				}
			}
		}
	}

	return ret;
}

UINT CListMaker::NotEndContextLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	UINT ret=-1;
	UINT index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		UINT index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			UINT newNElem=0;
			UINT nElem1=unListsElements[index1];
			UINT nElem2=unListsElements[index2];
			UINT newLen=0;
			UINT c1=0,c2=0;
			UINT newindex;

			SortList(index2);
			UniqueList(index2);
			while(c1<nElem1)
			{
				int flgUNI=0;
				char *pos1=tmppos1[c1];
				c2=0;
				while(c2<nElem2)
				{
					char *pos2=tmppos2[c2];
					pos1=tmppos1[c1];
					if (*pos2!=0)
					{
						while(*(pos1++)!=0);
						while(*(pos2++)!=0) pos1--;
						if (pos1>=tmppos1[c1])
						{
							pos2=tmppos2[c2];
							while(*pos1==*pos2 && *pos2!=0) {pos1++;pos2++;}
							if (*pos2==0) {flgUNI=1;break;}
						}
					}
					c2++;
				}
				if (flgUNI==0) 
				{	
					while(*(pos1++)!=0);
					newLen+=(pos1-tmppos1[c1]);
					newNElem++;
				}
				c1++;
			}

			CreateList("ortmplist");
			newindex=GetListIndex("ortmplist");
			if (newindex<nLists)
			{
				ret=unListsElements[newindex]	=newNElem;
				unListsState[newindex]=0x3;
				unListsLength[newindex]	=newLen;
				cListArray[newindex]=new char [newLen+5];
				ListPointers[newindex]=new char * [newNElem+5];
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					UINT NElem=0;
					c1=0,c2=0;
					while(c1<nElem1)
					{
						int flgUNI=0;
						c2=0;
						while(c2<nElem2)
						{
							char *pos1=tmppos1[c1];
							char *pos2=tmppos2[c2];
							if (*pos2!=0)
							{
								while(*(pos1++)!=0);
								while(*(pos2++)!=0) pos1--;
								if (pos1>=tmppos1[c1])
								{
									pos2=tmppos2[c2];
									while(*pos1==*pos2 && *pos2!=0) {pos1++;pos2++;}
									if (*pos2==0) {flgUNI=1;break;}
								}
							}
							c2++;
						}
						if (flgUNI==0) 
						{	
							char *pos1=tmppos1[c1];
							tmpposDest[NElem++]=posDest;
							while((*(posDest++)=*(pos1++))!=0);
						}
						c1++;
					}
				}

				{
					DeleteList(DestName);
					UINT tmpid=GetListIndex("ortmplist");
					strcpy(ListsName[tmpid],DestName);
				}
			}
		}
	}

	return ret;
}

UINT CListMaker::NotContextLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	UINT ret=-1;
	UINT index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		UINT index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			UINT newNElem=0;
			UINT nElem1=unListsElements[index1];
			UINT nElem2=unListsElements[index2];
			UINT newLen=0;
			UINT c1=0,c2=0;
			UINT newindex;

			SortList(index2);
			UniqueList(index2);
			while(c1<nElem1)
			{
				char *pos1=tmppos1[c1];
				int flgUNI=0;
				c2=0;
				while(c2<nElem2)
				{
					pos1=tmppos1[c1];
					if (*tmppos2[c2]==0) break;
					while(*pos1!=0)
					{
						char *pos2=tmppos2[c2];
						char *reppos=pos1;
						while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
						if (*pos2==0) {flgUNI=1;break;}
						if (*pos1==0) break;
						pos1=++reppos;
					}

					if (flgUNI!=0) break;
					c2++;
				}
				if (flgUNI==0) 
				{	
					while(*(pos1++)!=0);
					newLen+=(pos1-tmppos1[c1]);
					newNElem++;
				}
				c1++;
			}

			CreateList("ortmplist");
			newindex=GetListIndex("ortmplist");
			if (newindex<nLists)
			{
				ret=unListsElements[newindex]	=newNElem;
				unListsState[newindex]=0x3;
				unListsLength[newindex]	=newLen;
				cListArray[newindex]=new char [newLen+5];
				ListPointers[newindex]=new char * [newNElem+5];
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					UINT NElem=0;
					c1=0,c2=0;
					while(c1<nElem1)
					{
						int flgUNI=0;
						c2=0;
						while(c2<nElem2)
						{
							char *pos1=tmppos1[c1];
							if (*tmppos2[c2]==0) break;
							while(*pos1!=0)
							{
								char *pos2=tmppos2[c2];
								char *reppos=pos1;
								while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
								if (*pos2==0) {flgUNI=1;break;}
								if (*pos1==0) break;
								pos1=++reppos;
							}

							if (flgUNI!=0) break;
							c2++;
						}
						if (flgUNI==0)
						{	
							char *pos1=tmppos1[c1];
							tmpposDest[NElem++]=posDest;
							while((*(posDest++)=*(pos1++))!=0);
						}
						c1++;
					}
				}

				{
					DeleteList(DestName);
					UINT tmpid=GetListIndex("ortmplist");
					strcpy(ListsName[tmpid],DestName);
				}
			}
		}
	}

	return ret;
}

UINT CListMaker::MaskLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	UINT ret=-1;
	UINT index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		UINT index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			UINT newNElem=0;
			UINT nElem1=unListsElements[index1];
			UINT nElem2=unListsElements[index2];
			UINT newLen=0;
			UINT c1=0,c2=0;
			UINT newindex;

			SortList(index2);
			UniqueList(index2);
			while(c1<nElem1)
			{
				int flgUNI=0;
				c2=0;
				while(c2<nElem2)
				{
					char *pos1=tmppos1[c1];
					if (*tmppos2[c2]!=0)
					{
						while(*pos1!=0)
						{
							char *pos2=tmppos2[c2];
							char *reppos=pos1;
							if (*pos2=='[')
							{
								pos2++;
								while(*pos1!=0 && *pos1!=*pos2) {pos1++;reppos++;}
								if (*pos1==0) break;
							}

							while((*pos1==*pos2 || *pos2==GPC.DelimiterIn1) && *pos1!=0 && *pos2!=']')
								{pos1++;pos2++;}
							if ((*pos2==0 && *pos1==0) || *pos2==']') {flgUNI=1;break;}
							if (*pos1==0) break;
							if (*pos2!='[') break;

							pos1=++reppos;
						}


						if (flgUNI!=0) 
						{	
							while(*(pos1++)!=0);
							newLen+=(pos1-tmppos1[c1]);
							newNElem++;
							break;
						}
					}
					c2++;
				}
				c1++;
			}

			CreateList("ortmplist");
			newindex=GetListIndex("ortmplist");
			if (newindex<nLists)
			{
				ret=unListsElements[newindex]	=newNElem;
				unListsState[newindex]=0x3;
				unListsLength[newindex]	=newLen;
				cListArray[newindex]=new char [newLen+5];
				ListPointers[newindex]=new char * [newNElem+5];
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					UINT NElem=0;
					c1=0,c2=0;
					while(c1<nElem1)
					{
						int flgUNI=0;
						c2=0;
						while(c2<nElem2)
						{
							char *pos1=tmppos1[c1];
							if (*tmppos2[c2]!=0)
							{
								while(*pos1!=0)
								{
									char *pos2=tmppos2[c2];
									char *reppos=pos1;
									if (*pos2=='[')
									{
										pos2++;
										while(*pos1!=0 && *pos1!=*pos2) {pos1++;reppos++;}
										if (*pos1==0) break;
									}
									while((*pos1==*pos2 || *pos2==GPC.DelimiterIn1) && *pos1!=0 && *pos2!=']') {pos1++;pos2++;}
									if ((*pos2==0 && *pos1==0) || *pos2==']') {flgUNI=1;break;}
									if (*pos1==0) break;
									if (*pos2!='[') break;

									pos1=++reppos;
								}
								if (flgUNI!=0) 
								{	
									tmpposDest[NElem++]=posDest;
									pos1=tmppos1[c1];
									while((*(posDest++)=*(pos1++))!=0);
									break;
								}
							}
							c2++;
						}
						c1++;
					}
				}

				{
					DeleteList(DestName);
					UINT tmpid=GetListIndex("ortmplist");
					strcpy(ListsName[tmpid],DestName);
				}
			}
		}
	}

	return ret;
}

UINT CListMaker::NotMaskLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	UINT ret=-1;
	UINT index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		UINT index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			UINT newNElem=0;
			UINT nElem1=unListsElements[index1];
			UINT nElem2=unListsElements[index2];
			UINT newLen=0;
			UINT c1=0,c2=0;
			UINT newindex;

			SortList(index2);
			UniqueList(index2);
			while(c1<nElem1)
			{
				char *pos1=tmppos1[c1];
				int flgUNI=0;
				c2=0;
				while(c2<nElem2)
				{
					pos1=tmppos1[c1];
					if (*tmppos2[c2]==0) break;
					while(*pos1!=0)
					{
						char *pos2=tmppos2[c2];
						char *reppos=pos1;
						if (*pos2=='[')
						{
							pos2++;
							while(*pos1!=0 && *pos1!=*pos2) {pos1++;reppos++;}
							if (*pos1==0) break;
						}

						while((*pos1==*pos2 || *pos2==GPC.DelimiterIn1) && *pos1!=0 && *pos2!=']')
							{pos1++;pos2++;}
						if ((*pos2==0 && *pos1==0) || *pos2==']') {flgUNI=1;break;}
						if (*pos1==0) break;
						if (*pos2!='[') break;

						pos1=++reppos;
					}



					if (flgUNI!=0) break;
					c2++;
				}
				if (flgUNI==0)
				{	
					while(*(pos1++)!=0);
					newLen+=(pos1-tmppos1[c1]);
					newNElem++;
				}
				c1++;
			}

			CreateList("ortmplist");
			newindex=GetListIndex("ortmplist");
			if (newindex<nLists)
			{
				ret=unListsElements[newindex]	=newNElem;
				unListsState[newindex]=0x3;
				unListsLength[newindex]	=newLen;
				cListArray[newindex]=new char [newLen+5];
				ListPointers[newindex]=new char * [newNElem+5];
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					UINT NElem=0;
					c1=0,c2=0;
					while(c1<nElem1)
					{
						int flgUNI=0;
						c2=0;
						while(c2<nElem2)
						{
							char *pos1=tmppos1[c1];
							if (*tmppos2[c2]==0) break;
							while(*pos1!=0)
							{
								char *pos2=tmppos2[c2];
								char *reppos=pos1;
								if (*pos2=='[')
								{
									pos2++;
									while(*pos1!=0 && *pos1!=*pos2) {pos1++;reppos++;}
									if (*pos1==0) break;
								}
								while((*pos1==*pos2 || *pos2==GPC.DelimiterIn1) && *pos1!=0 && *pos2!=']') {pos1++;pos2++;}
								if ((*pos2==0 && *pos1==0) || *pos2==']') {flgUNI=1;break;}
								if (*pos1==0) break;
								if (*pos2!='[') break;

								pos1=++reppos;
							}
							if (flgUNI!=0) break;
							c2++;
						}
						if (flgUNI==0) 
						{	
							char *pos1=tmppos1[c1];
							tmpposDest[NElem++]=posDest;
							while((*(posDest++)=*(pos1++))!=0);
						}
						c1++;
					}
				}

				{
					DeleteList(DestName);
					UINT tmpid=GetListIndex("ortmplist");
					strcpy(ListsName[tmpid],DestName);
				}
			}
		}
	}

	return ret;
}


UINT CListMaker::LoadList(const char *ListName, const char *FileName = NULL)
{
	UINT ret=-1;
	FILE *src;
	const char *fNm;
	if ((fNm=FileName)==NULL) fNm=ListName;
	src=fopen(fNm,"rb");
	if (src!=NULL)
	{
		UINT iIndex;
		CreateList(ListName);
		iIndex=GetListIndex(ListName);
		if (iIndex<nLists)
		{
			UINT nElem=0;
			char *pos;
			if (cListArray[iIndex]!=NULL) delete[] cListArray[iIndex];
			cListArray[iIndex]=NULL;
			if (ListPointers[iIndex]!=NULL) delete[] ListPointers[iIndex];
			ListPointers[iIndex]=NULL;
			unListsState[iIndex]=0;
			unListsElements[iIndex]=0;
			unListsLength[iIndex]=0;
			cDelmiterArray[iIndex]=10;
			fseek(src,0,SEEK_END);
			unListsLength[iIndex]=ftell(src);
			cListArray[iIndex]=new char [unListsLength[iIndex]+5];
			rewind(src);
			pos=cListArray[iIndex];
			fread( cListArray[iIndex],1,unListsLength[iIndex], src);
 			cListArray[iIndex][unListsLength[iIndex]]=0;
     
			while(*pos!=0)
			{
				if (*pos==10 || *pos==13 || *pos==254) 
				{
					do
						pos++;
					while(*pos!=0 && (*pos==13 || *pos==10 || *pos==254));
					pos--;
					nElem++;
				}
				pos++;
			}

			if (unListsLength[iIndex])
			{
				char *posDest;
				nElem++;
				ret=unListsElements[iIndex]=nElem;
				ListPointers[iIndex]=new char * [nElem+5];

				posDest=cListArray[iIndex];
				*ListPointers[iIndex]=posDest;
				nElem=0;

				while(*posDest!=0)
				{
					if (*posDest==10 || *posDest==13 || *posDest==254) 
					{
						*(posDest++)=0;
						while(*posDest!=0 && (*posDest==13 || *posDest==10 || *posDest==254)) posDest++;
						ListPointers[iIndex][++nElem]=posDest;
						posDest--;
					}
					posDest++;
				}
			}
		}
		fclose(src);
	}

	return ret;
}

int CListMaker::SaveList(const char *nmlist, const char *nmFile)
{
	FILE *dst;
	dst=fopen(nmFile,"wb");
	if (dst!=NULL)
	{
		UINT iIndex;
		iIndex=GetListIndex(nmlist);
		if (iIndex<nLists && unListsElements[iIndex]>0 && ListPointers[iIndex]!=NULL)
		{
			UINT nItem=unListsElements[iIndex];
			UINT i=0;
			char *ps;
			long len=0;
			SortList(iIndex);
			UniqueList(iIndex);
			if (i<nItem)
			{
				len=0;
				ps=ListPointers[iIndex][i];
				while(*(ps++)!=0) len++;
				fwrite(ListPointers[iIndex][i],1,len,dst);
			}
			for(i=1;i<nItem;i++)
			{
				len=0;
				ps=ListPointers[iIndex][i];
				while(*(ps++)!=0) len++;
				fputc(10,dst);
				fwrite(ListPointers[iIndex][i],1,len,dst);
			}
		}

		fclose(dst);
	}
	return 0;
}	

int CListMaker::DoMethod(const char *iStr, char **oStr)
{
	char met[150];
	int nfunc=0;
	int retint=-123456; 
	int atoipos;
	const UINT uNMethods=27;
	const char *cArrMethods[27]={
			"XORLISTS","ANDLISTS","NOTLISTS","ORLISTS","SQUISELIST",
			"DUPLICATELIST","UNIQUELIST","SORTLIST","ADDLIST","APPENDLIST",
			"SETLISTDELIMITER","SETLIST","LOADLIST","CREATELIST","DELETELIST",
			"SAVELIST","CONTEXTLISTS","MASKLISTS","NOTMASKLISTS","NOTCONTEXTLISTS",
			"BEGINCONTEXTLISTS","NOTBEGINCONTEXTLISTS","ENDCONTEXTLISTS","NOTENDCONTEXTLISTS",
			"GETLISTINFO","GETLISSTINFO","GETLIST",
	};

	strncpy(met,iStr,145);met[145]=0;
	char *tmpppos=met;
	while(*tmpppos!=0 && *tmpppos!=' ')
		*(tmpppos++)&=0xDF;

	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	atoipos=atoi(pos);
	
	for(nfunc=0;nfunc<uNMethods && strcmp(met,cArrMethods[nfunc])!=0;nfunc++); 

	switch(nfunc)
	{
	case 0: /*XORLISTS*/
	case 1: /*ANDLISTS*/
	case 2: /*NOTLISTS*/
	case 3: /*ORLISTS*/
	case 16: /*CONTEXTLISTS*/
	case 17: /*MASKLISTS*/
	case 18: /*NOTMASKLISTS*/
	case 19: /*NOTCONTEXTLISTS*/
	case 20: /*BEGINCONTEXTLISTS*/
	case 21: /*NOTBEGINCONTEXTLISTS*/
	case 22: /*ENDCONTEXTLISTS*/
	case 23: /*NOTENDCONTEXTLISTS*/
		{
			char *postmpcc=new char [(int)strlen(pos)+10];
			strcpy(postmpcc,pos);

			char *nmdest=postmpcc;
			char *nm1,*nm2;
			nm1=strchr(nmdest,',');
			if (nm1!=NULL) *(nm1++)=0;
			else nm1="";
			nm2=strchr(nm1,',');
			if (nm2!=NULL) *(nm2++)=0;
			else nm2="";
			if (*nmdest!=0 && *nm1!=0 && *nm2!=0)
				switch(nfunc)
				{
				case 0: /*XORLISTS*/		retint=XORLists(nmdest,nm1,nm2);		break;
				case 1: /*ANDLISTS*/		retint=ANDLists(nmdest,nm1,nm2);		break;
				case 2: /*NOTLISTS*/		retint=NOTLists(nmdest,nm1,nm2);		break;
				case 3: /*ORLISTS*/			retint= ORLists(nmdest,nm1,nm2);		break;
				case 16: /*CONTEXTLISTS*/	retint= ContextLists(nmdest,nm1,nm2);	break;
				case 17: /*MASKLISTS*/		retint= MaskLists(nmdest,nm1,nm2);		break;
				case 18: /*NOTMASKLISTS*/	retint= NotMaskLists(nmdest,nm1,nm2);	break;
				case 19: /*NOTCONTEXTLISTS*/retint= NotContextLists(nmdest,nm1,nm2);break;
				case 20: /*BEGINCONTEXTLISTS*/retint= BeginContextLists(nmdest,nm1,nm2);break;
				case 21: /*NOTBEGINCONTEXTLISTS*/retint= NotBeginContextLists(nmdest,nm1,nm2);break;
				case 22: /*ENDCONTEXTLISTS*/retint= EndContextLists(nmdest,nm1,nm2);break;
				case 23: /*NOTENDCONTEXTLISTS*/retint= NotEndContextLists(nmdest,nm1,nm2);break;
				}
			delete[] postmpcc;
		}
		break;
	case 4: /*SQUISELIST*/
		retint=SquiseList(pos);
		break;
	case 5: /*DUPLICATELIST*/	
	case 8: /*ADDLIST*/
	case 9: /*APPENDLIST*/
	case 10: /*SETLISTDELIMITER*/
	case 11: /*SETLIST*/
	case 15: /*SAVELIST*/
		{
			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
	
			char *nmdest=pos333,*nm1;
			nm1=strchr(nmdest,',');
			if (nm1!=NULL) *(nm1++)=0;
			else nm1="";
			if (*nmdest!=0 && *nm1!=0) 
				switch(nfunc)
				{
				case 0: /*DUPLICATELIST*/	retint=DuplicateList(nmdest,nm1);	break;
				case 8: /*ADDLIST*/			retint=AddList(nmdest,nm1);		break;
				case 9: /*APPENDLIST*/		retint=AppendList(nmdest,nm1);		break;
				case 10: /*SETLISTDELIMITER*/	retint=SetListDelimiter(nmdest,*nm1);		break;
				case 11: /*SETLIST*/		retint=SetList(nmdest,nm1,GPC.DelimiterIn1);	break;
				case 15: /*SAVELIST*/	
					{
						if (*nm1==0) nm1=nmdest;
						retint=SaveList(nmdest,nm1);
					}
					break;
				}
			delete[] pos333;
		}
		break;
	case 6: /*UNIQUELIST*/		retint=UniqueList(pos);	break;
	case 7: /*SORTLIST*/		SortList(pos);				break;
	case 12: /*LOADLIST*/		retint=LoadList(pos);		break;
	case 13: /*CREATELIST*/		retint=CreateList(pos);		break;
	case 14: /*DELETELIST*/		retint=DeleteList(pos);	break;
	case 24: /*GETLISTINFO*/
		if (oStr!=NULL)
		{
			*oStr=new char [1000];
			retint=-1;
			UINT iIndex=GetListIndex(pos);
			if (iIndex<nLists)
				sprintf(*oStr,"%s\x7F%d\x7F%d\x7F%d",ListsName[iIndex],unListsElements[iIndex],unListsLength[iIndex],unListsState[iIndex]);
		}
		break;
	case 25: /*GETLISSTINFO*/	
		if (oStr!=NULL)
		{
			*oStr=new char [1000+nLists*250];
			retint=-1;
			char *outpos=*oStr;
			UINT i;
			for(i=0;i<nLists;i++)
			{
				if (i!=0)  *(outpos++)=0x7F;
				outpos+=sprintf(outpos,"%s\x07%d\x07%d\x07%d",ListsName[i],unListsElements[i],unListsLength[i],unListsState[i]);
			}
		}
		break;
	case 26: /*GETLIST*/	
		if (oStr!=NULL)
		{
			UINT iIndex=GetListIndex(pos);
			if (iIndex<nLists)
				GetList(iIndex,oStr);
		}
		break;
	default:
		GPC.m_ErrReport.GPWriteWarnLog2("ListMaker", "Unknown Method",iStr);
		if (oStr!=NULL && *oStr==NULL)
		{
			*oStr=new char [100];
			sprintf(*oStr,"Метод отсутствует %s",met);
		}

	}

	if (oStr!=NULL && *oStr==NULL && retint!=-123456)
	{
		*oStr=new char [100];
		sprintf(*oStr,"%d",retint);
	}

	return nfunc;
}

long CListMaker::GetList(const char *iName, char **oList)
{
	return GetList(GetListIndex(iName),oList);
}

long CListMaker::GetList(UINT iIndex, char **oList)
{
	return GetList(iIndex, oList, 0x7F);
}

long CListMaker::GetList(const char *iName, char **oList, char delim)
{
	return GetList(GetListIndex(iName),oList, delim);
}

long CListMaker::GetList(UINT iIndex, char **oList, char delim)
{
	long ret=-1;
	if (oList && iIndex<nLists && cListArray!=NULL && cListArray[iIndex]!=NULL && unListsLength[iIndex]>0)
	{
		SquiseList(iIndex);
		*oList=new char [unListsLength[iIndex]+100];
		UINT nElem=unListsElements[iIndex];
		char *posD=*oList;
		char *posS=cListArray[iIndex];
		UINT n=0;
		while(n<nElem)
		{
			while((*(posD++)=*(posS++))!=0);
			*(--posD)=delim;
			posD++;
			n++;
		}
		*(--posD)=0;
		ret=unListsLength[iIndex];
	}
	return ret;
}

#ifndef WLISTMAKER

long CListMaker::GetListInfo(const char *iName, VARIANT *ListInfo)
{
	return GetListInfo(GetListIndex(iName),ListInfo);
}

long CListMaker::GetListInfo(UINT iIndex, VARIANT *ListInfo)
{
	SAFEARRAY FAR* psa = NULL;
	long ret=0;
	USES_CONVERSION;
	SAFEARRAYBOUND tmpSAB={0};

	long nElements=4;

	tmpSAB.cElements=nElements;

	if ((V_VT(ListInfo)&VT_ARRAY) == VT_ARRAY )
	{
		psa = V_ARRAY(ListInfo); 
		SafeArrayGetLBound(psa,1,&tmpSAB.lLbound);
		SafeArrayDestroy(psa);
	}

	VariantInit(ListInfo);

	try
	{
		COleSafeArray SAtmp;
		SAtmp.Create(VT_VARIANT, 1,&tmpSAB.cElements);
		VariantCopy(ListInfo,SAtmp);
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("CListMaker", "GetListInfo","");
	}

	psa = V_ARRAY(ListInfo);   
	// Check dimensions of the array.
	if (SafeArrayGetDim(psa) == 1)	
	{
		VARIANT HUGEP *pbstr;
		HRESULT hr;
		hr = SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
		if (!FAILED(hr) && iIndex<nLists)
		{
			long ind=0;
			SafeArrayPutElement(psa,&ind,(void *)((LPVARIANT)COleVariant(ListsName[iIndex])));
			ind++;
			SafeArrayPutElement(psa,&ind,(void *)((LPVARIANT)COleVariant((long)unListsElements[iIndex],VT_I4)));
			ind++;
			SafeArrayPutElement(psa,&ind,(void *)((LPVARIANT)COleVariant((long)unListsLength[iIndex],VT_I4 )));
			ind++;
			SafeArrayPutElement(psa,&ind,(void *)((LPVARIANT)COleVariant((long)unListsState[iIndex], VT_I4)));
			SafeArrayUnaccessData(psa);
			ret=1;
		}
	}

	return ret;
}

long CListMaker::GetListsInfo(VARIANT *ListInfo)
{
	SAFEARRAY FAR* psa = NULL;
	long ret=0;

	USES_CONVERSION;
	SAFEARRAYBOUND tmpSAB={0};

	UINT nElements=nLists;
	if (nElements==0) nElements++;
	tmpSAB.cElements=nElements;

	if ((V_VT(ListInfo)&VT_ARRAY) == VT_ARRAY )
	{
		psa = V_ARRAY(ListInfo); 
		SafeArrayGetLBound(psa,1,&tmpSAB.lLbound);
		SafeArrayDestroy(psa);
	}

	VariantInit(ListInfo);

	try
	{
		COleSafeArray SAtmp;
		SAtmp.Create(VT_VARIANT, 1,&tmpSAB.cElements);
		VariantCopy(ListInfo,SAtmp);
	}
	catch(...)
	{
			GPC.m_ErrReport.GPWriteErrorLog("CListMaker", "GetListsInfo","");
	}

	psa = V_ARRAY(ListInfo);   
	// Check dimensions of the array.
	if (SafeArrayGetDim(psa) == 1)	
	{
		VARIANT HUGEP *pbstr;
		HRESULT hr;
		hr = SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
		if (!FAILED(hr))
		{
			UINT i;
			for(i=0;i<nLists;i++)
				GetListInfo(i,pbstr+i);
			SafeArrayUnaccessData(psa);
			ret=nElements;
		}
	}

	return ret;
}

long CListMaker::SetListAsArray(const char *iName, VARIANT *iList)
{
	CreateList(iName);
	return SetListAsArray(GetListIndex(iName),iList);
}
long CListMaker::SetListAsArray(UINT iIndex, VARIANT *iList)
{
	long ret=-1;
	if (iIndex<nLists)
	{
		CString tmp;
		ret=ArrayToStringEx(iList,tmp,GPC.csDelimiterIn1);
		if (ret>0)
			ret=SetList(iIndex,tmp,GPC.DelimiterIn1);
	}

	return ret;
}

long CListMaker::GetList(const char *iName, BSTR FAR* OutListString)
{
	return GetList(GetListIndex(iName),OutListString);
}

long CListMaker::GetList(UINT iIndex, BSTR FAR* OutListString)
{
	CString oStr;

	if (iIndex<nLists && cListArray!=NULL && cListArray[iIndex]!=NULL && unListsLength[iIndex]>0)
	{
		SquiseList(iIndex);
		UINT nElem=unListsElements[iIndex];
		char *posS=cListArray[iIndex];
		UINT n=0;
		while(n<nElem)
		{
			while(*(posS++)!=0);
			*(--posS)=0x7F;
			posS++;
			n++;
		}

		oStr=cListArray[iIndex];
		n=0;
		posS=cListArray[iIndex];
		while(n<nElem)
		{
			while(*(posS++)!=0x7F);
			*(--posS)=0;
			posS++;
			n++;
		}
	}

	oStr.SetSysString(OutListString);
	return oStr.GetLength();
}

long CListMaker::GetListAsArray(const char *iName, VARIANT *iList)
{
	return GetListAsArray(GetListIndex(iName),iList);
}
long CListMaker::GetListAsArray(UINT iIndex, VARIANT *iList)
{
	long ret=-1;
	if (iIndex<nLists && cListArray!=NULL && cListArray[iIndex]!=NULL && unListsLength[iIndex]>0)
	{
		long ix=-1;

		SAFEARRAY FAR* psa = NULL;
		USES_CONVERSION;
		SAFEARRAYBOUND tmpSAB={0};
		long nElements=unListsElements[iIndex];

		tmpSAB.cElements=nElements;

		if ((V_VT(iList)&VT_ARRAY) == VT_ARRAY )
		{
			psa = V_ARRAY(iList); 
			SafeArrayGetLBound(psa,1,&tmpSAB.lLbound);
			SafeArrayDestroy(psa);
		}

		VariantInit(iList);

		try
		{
			COleSafeArray SAtmp;
			SAtmp.Create(VT_BSTR, 1,&tmpSAB.cElements);
			VariantCopy(iList,SAtmp);
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("CListMaker", "GetListAsArray","");
		}

		psa = V_ARRAY(iList);   
		// Check dimensions of the array.
		if (SafeArrayGetDim(psa) != 1)			AfxThrowOleDispatchException(1002,IDS_GPOLEEXEPTION1002);
		else
		{
			CString CStmp;
			BSTR HUGEP *pbstr;
			HRESULT hr;
			hr = SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
			if (FAILED(hr))		AfxThrowOleDispatchException(1001,IDS_GPOLEEXEPTION1001);

			char **poss=ListPointers[iIndex];
			for(ix=0; ix<nElements; ix++)
			{
				CStmp=*(poss++);
				CStmp.SetSysString(&pbstr[ix]);
			}
			SafeArrayUnaccessData(psa);
		}
	}
	return ret;
}

long CListMaker::FillObject(const char *iName, HWND ihWnd, UINT ObjType, long FillType)
{
	return FillObject(GetListIndex(iName),ihWnd, ObjType, FillType);
}
long CListMaker::FillObject(UINT iIndex, HWND ihWnd, UINT ObjType, long FillType)
{
	long ret=-1;
	if (ihWnd!=NULL && iIndex<nLists && cListArray!=NULL && cListArray[iIndex]!=NULL && unListsLength[iIndex]>0)
	{

		UINT nItem=unListsElements[iIndex];
		char **ptr=ListPointers[iIndex];

		switch(ObjType&0xFFFF)
		{
		case GPSPRFILL_COMBOBOX:
		case GPSPRFILL_COMBOBOXEX:
			{
				COMBOBOXEXITEM cbi={0};
				cbi.mask=CBEIF_TEXT;
				cbi.cchTextMax=5000;
				cbi.iItem=0;
				if ((FillType&0x1)==0) SendMessage(ihWnd,CB_RESETCONTENT,0,0);
				CString newItem;
				{
					UINT i;
					if ((ObjType&0xFFFF)==GPSPRFILL_COMBOBOX)
						for(i=0;i<nItem;i++)
							SendMessage(ihWnd,CB_ADDSTRING,0,(LPARAM)((LPCTSTR)(newItem=ptr[i])));
					else
						for(i=0;i<nItem;i++)
						{
							cbi.pszText=ptr[i];
							SendMessage(ihWnd,CBEM_INSERTITEM,0,(LPARAM)&cbi);
							cbi.iItem++;
						}
				}
				ret=SendMessage(ihWnd,CB_GETCOUNT,0,0);
			}
			break;
		case GPSPRFILL_LISTBOX:
			{
				if ((FillType&0x1)==0) SendMessage(ihWnd,LB_RESETCONTENT,0,0);
				CString newItem;
				{
					UINT i;
					for(i=0;i<nItem;i++)
						SendMessage(ihWnd,LB_ADDSTRING,0,(LPARAM)((LPCTSTR)(newItem=ptr[i])));
				}
				ret=SendMessage(ihWnd,LB_GETCOUNT,0,0);
			}
			break;
		}
	}

	return ret;
}

#endif

/*
void CListMaker::MakeListUC(const char *iName)
	{MakeListUC(GetListIndex(iName));}

void CListMaker::MakeListUC(UINT iIndex)
{
	if (iIndex<nLists && cListArray[iIndex]!=NULL && ListPointers[iIndex]!=NULL && unListsElements[iIndex]>0 && (unListsState[iIndex]&0x1)==0)
	{
		UINT nElem=unListsElements[iIndex];
		char *posS=cListArray[iIndex];
		UINT n=0;
		while(n<nElem)
		{
			while(*(posS++)!=0);
			n++;
		}
	}
}*/
/*
void CListMaker::MakeListLC(const char *iName)
	{MakeListLC(GetListIndex(iName));}

void CListMaker::MakeListLC(UINT iIndex)
{
	if (iIndex<nLists && cListArray[iIndex]!=NULL && ListPointers[iIndex]!=NULL && unListsElements[iIndex]>0 && (unListsState[iIndex]&0x1)==0)
	{
		Sort(iIndex,0,unListsElements[iIndex]-1);
		unListsState[iIndex]|=0x1;
	}
}

*/