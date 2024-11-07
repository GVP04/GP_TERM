// ListMaker.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"

#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "string.h"
#include "unistd.h"
/*
cc ListMaker.c -o ListMaker -lc
chmod 777 ListMaker

cc ListMaker.cpp -o ListMaker 
chmod 777 ListMaker

g++ ListMaker.cpp -o ListMaker -funsigned-char
chmod 777 ListMaker

*/
/*cc ListMaker.c -o ListMaker| pg*/
/*chmod 777 ListMaker*/
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


int main(int argc, char* argv[])
{
	long i;
	nMaxLists=200;
	nLists=0;
	cListArray=new char * [nMaxLists+5];
	ListsName= new char * [nMaxLists+5];
	ListPointers=new char ** [ nMaxLists+5];
	unListsElements=new long  [ nMaxLists+5];
	unListsLength=new long  [ nMaxLists+5];
	unListsState=new long  [ nMaxLists+5];
	cDelmiterArray=new char  [ nMaxLists+5];
	strcpy(ListsPath,"ListMaker");

	for (i=0;i<nMaxLists;i++)
	{
		cListArray[i]=NULL;
		ListsName[i]=NULL;
		ListPointers[i]=NULL;
		unListsState[i]=0;
		unListsElements[i]=0;
		unListsLength[i]=0;
		cDelmiterArray[i]='^';
	}

	if (argc>1 && argv[1]!=0 && *argv[1]!=0)
	{
		char comname[1000];
		FILE *src;
		strncpy(IdPort,argv[1],250);
		if (argc>2 && argv[2]!=0 && *argv[2]!=0) 
			strcpy(ListsPath,argv[2]);
		sprintf(comname,"%s/%scommand",ListsPath,IdPort);

		src=fopen(comname,"rt");
		if (src!=NULL)
		{
			long fLen;
			char *buff,*pos;
			fseek(src,0,SEEK_END);
			fLen=ftell(src);
			rewind(src);
			buff=new char [fLen+10];
			buff[fLen]=0;
			if (buff!=NULL)
			{
				fread(buff,1,fLen, src);
				pos=buff;
				while(*pos!=0)
				{
					char *pos2=pos;
					while(*pos2!=0 && *pos2!=10 && *pos2!=13) pos2++;
					if (*pos2!=0)
					{
						*(pos2++)=0;
						while(*pos2==10 || *pos2==13) pos2++;
					}
					DoMethod(pos,NULL);
					pos=pos2;
				}
				delete[] buff;
			}
			fclose(src);
		}
	}

	if (cListArray!=NULL)
	{
		for(i=0;i<nLists;i++)
			if (cListArray[i]!=NULL)
			{
				delete cListArray[i];
				cListArray[i]=NULL;
			}
		delete cListArray;
		cListArray=NULL;
	}
	if (ListsName!=NULL)
	{
		for(i=0;i<nLists;i++)
			if (ListsName[i]!=NULL) 
			{
				delete ListsName[i];
				ListsName[i]=NULL;
			}
		delete ListsName;
		ListsName=NULL;
	}

	if (ListPointers!=NULL)
	{
		for(i=0;i<nLists;i++)
			if (ListPointers[i]!=NULL) 
			{
				delete ListPointers[i];
				ListPointers[i]=NULL;
			}
		delete ListPointers;
		ListPointers=NULL;
	}
	if (unListsElements!=NULL)	delete unListsElements;
	unListsElements=NULL;
	if (unListsLength!=NULL)	delete unListsLength;
	unListsLength=NULL;
	if (cDelmiterArray!=NULL)	delete cDelmiterArray;
	cDelmiterArray=NULL;
	if (unListsState!=NULL)		delete unListsState;
	unListsState=NULL;




	return 0;
}


long DeleteListC(const char *iName)
{
//	printf("begin DeleteListC\n");
	long retind=GetListIndex(iName);
//	printf("cont DeleteListC %d\n",retind);
	long ret=DeleteList(retind);
//	printf("end DeleteListC %d %d\n",retind,ret);
	return ret;
}

long DeleteList(long iIndex)
{
	if (iIndex>=0 && iIndex<nLists)
	{
		long i;
		if (cListArray!=NULL && cListArray[iIndex]!=NULL)
		{
			delete cListArray[iIndex];
			cListArray[iIndex]=NULL;
		}
		if (ListsName!=NULL && ListsName[iIndex]!=NULL) 
		{
			delete ListsName[iIndex];
			ListsName[iIndex]=NULL;
		}

		if (ListPointers!=NULL && ListPointers[iIndex]!=NULL) 
		{
			delete ListPointers[iIndex];
			ListPointers[iIndex]=NULL;
		}
		nLists--;
		for(i=iIndex; i<nLists;i++)
		{
			cListArray[i]=cListArray[i+1];
			ListsName[i]=ListsName[i+1];
			ListPointers[i]=ListPointers[i+1];
			unListsElements[i]=unListsElements[i+1];
			unListsState[i]=unListsState[i+1];
			unListsLength[i]=unListsLength[i+1];
			cDelmiterArray[i]=cDelmiterArray[i+1];
		}
		cListArray[i]=NULL;
		ListsName[i]=NULL;
		ListPointers[i]=NULL;
		unListsState[i]=0;
		unListsElements[i]=0;
		unListsLength[i]=0;
		cDelmiterArray[i]='^';
	}

	return nLists;
}

long GetListIndex(const char *LName)
{
	long ret=0xFFFFFFFF;
	if (ListsName!=NULL)
		for(ret=0;ret<nLists;ret++)
			if (ListsName[ret]!=NULL &&  strcmp(ListsName[ret],LName)==0) break; 
	return ret==nLists?0xFFFFFFFF:ret;
}

long CreateList(const char *iName)
{
	//////////////
//	printf("CreateList %d %d\n",nLists,nMaxLists);
	if (nLists>=nMaxLists)
	{
		nMaxLists+=50;
		{
			char ** cListArrayT=new char * [nMaxLists+5];
			char ** ListsNameT= new char * [nMaxLists+5];
			char *** ListPointersT=new char ** [ nMaxLists+5];
			long * unListsElementsT=new long  [ nMaxLists+5];
			long * unListsLengthT=new long  [ nMaxLists+5];
			long * unListsStateT=new long  [ nMaxLists+5];
			char * cDelmiterArrayT=new char  [ nMaxLists+5];
			long i;

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
				cDelmiterArrayT[i]='^';
			}

			delete cListArray;
			delete ListsName;
			delete ListPointers;
			delete unListsState;
			delete unListsElements;
			delete unListsLength;
			delete cDelmiterArray;

			cListArray=cListArrayT;
			ListsName=ListsNameT;
			ListPointers=ListPointersT;
			unListsState=unListsStateT;
			unListsElements=unListsElementsT;
			unListsLength=unListsLengthT;
			cDelmiterArray=cDelmiterArrayT;
		}
	}
	
//	printf("DeleteListC %s\n",iName);
	DeleteListC(iName);

	ListsName[nLists]=new char  [50];
	strcpy(ListsName[nLists],iName);
	cListArray[nLists]=NULL;
	ListPointers[nLists]=NULL;
	unListsState[nLists]=0;
	unListsElements[nLists]=0;
	unListsLength[nLists]=0;
	cDelmiterArray[nLists]='^';

//	printf("End Creat %d\n",nLists);
	return nLists++;
}

long SetListC(const char *iName, const char *iList,char delimiter)
{
	CreateList(iName);
	return SetList(GetListIndex(iName),iList,delimiter);
}

long SetList(long iIndex, const char *iList,char delimiter)
{
	long ret=0xFFFFFFFF;
	if (iIndex<nLists)
	{
		long nElem=0;
		const char *pos;
		if (cListArray[iIndex]!=NULL) delete cListArray[iIndex];
		cListArray[iIndex]=NULL;
		if (ListPointers[iIndex]!=NULL) delete ListPointers[iIndex];
		ListPointers[iIndex]=NULL;
		unListsState[iIndex]=0;
		unListsElements[iIndex]=0;
		unListsLength[iIndex]=0;
		cDelmiterArray[iIndex]=delimiter;

		pos=iList;
		while(*pos!=0)
		{
			if (*pos==delimiter) nElem++;
			pos++;
		}
		unListsLength[iIndex]=pos-iList;

		if (unListsLength[iIndex])
		{
			char *posDest;
			nElem++;
			ret=unListsElements[iIndex]=nElem;
			cListArray[iIndex]=new char  [unListsLength[iIndex]+5];
			ListPointers[iIndex]=new char * [nElem+5];

			posDest=cListArray[iIndex];
			*ListPointers[iIndex]=posDest;
			pos=iList;
			nElem=0;
			while((*posDest=*pos)!=0)
			{
				if (*posDest==delimiter) 
				{
					*posDest=0;
					ListPointers[iIndex][++nElem]=posDest+1;
				}
				posDest++;
				pos++;
			}
		}
	}

	return ret;
}

long GetCount()	
	{return nLists;}

long GetListItemCountC(const char *iName)
	{return GetListItemCount(GetListIndex(iName));}

char GetListDelimiterC(const char *iName)
	{return GetListDelimiter(GetListIndex(iName));}

char SetListDelimiterC(const char *iName,char newDelimiter)
	{return SetListDelimiter(GetListIndex(iName),newDelimiter);}

long GetListItemCount(long iIndex)
	{return (iIndex<nLists)?unListsElements[iIndex]:0xFFFFFFFF;}

long GetListStateC(const char *iName)
	{return GetListState(GetListIndex(iName));}

long GetListState(long iIndex)
	{return (iIndex<nLists)?unListsState[iIndex]:0xFFFFFFFF;}

char GetListDelimiter(long iIndex)
	{return (iIndex<nLists)?cDelmiterArray[iIndex]:0;}

char SetListDelimiter(long iIndex,char newDelimiter)
	{return (iIndex<nLists)?cDelmiterArray[iIndex]=newDelimiter:0;}

const char * GetListItemC(const char *iName, long iNItem)
	{return GetListItem(GetListIndex(iName),iNItem);}

const char * GetListItem(long iIndex, long iNItem)
	{return (iIndex<nLists && ListPointers[iIndex]!=NULL && iNItem<unListsElements[iIndex])?ListPointers[iIndex][iNItem]:NULL;}

long GetListLengthC(const char *iName)
	{return GetListLength(GetListIndex(iName));}

long GetListLength(long iIndex)
	{return (iIndex<nLists)?unListsLength[iIndex]:0xFFFFFFFF;}


long AppendListC(const char *iName, const char * iList)
	{return AppendList(GetListIndex(iName),iList);}

long AppendList(long iIndex, const char * iList)
{
	long ret=0xFFFFFFFF;
	if (iIndex<nLists)
	{
		long nElem=0;
		char delimiter=cDelmiterArray[iIndex];
		const char *pos=iList;
		long appLen;
		while(*pos!=0)
		{
			if (*pos==delimiter) nElem++;
			pos++;
		}

		appLen=pos-iList;
		if (appLen>0)
		{
			nElem++;
			{
				long newLen=unListsLength[iIndex]+pos-iList;
				long newElem=unListsElements[iIndex]+nElem;
				long oldElem=unListsElements[iIndex];

				char ** tmpListPointers=new char * [newElem+5];
				char *  tmpListArray=new char  [newLen+5];

				char *postmpD=tmpListArray+unListsLength[iIndex];
				char *postmpS=cListArray[iIndex]+unListsLength[iIndex];
				do *postmpD=*postmpS--;

				while(postmpD--!=tmpListArray);

				{
					char ** tmppos=ListPointers[iIndex];
					int delta=cListArray[iIndex]-tmpListArray;
					long i;
					for(i=0;i<oldElem;i++)
						tmpListPointers[i]=tmppos[i]-delta;

					{
						char *posDest=tmpListArray+unListsLength[iIndex]+1;
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
						delete ListPointers[iIndex];
						delete cListArray[iIndex];
						cListArray[iIndex]=tmpListArray;
						ListPointers[iIndex]=tmpListPointers;
					}
				}
			}
		}
	}

	return ret;

}


long AddListC(const char *destList, const char *srcList)
{
	return AddList(GetListIndex(destList),GetListIndex(srcList));
}

long AddList(long idestIndex, long isrcIndex)
{
	long ret=0;
	if (idestIndex<nLists)
	{
		if (isrcIndex<nLists)
		{
			long newLen=unListsLength[idestIndex]+unListsLength[isrcIndex];
			long newElem=unListsElements[idestIndex]+unListsElements[isrcIndex];

			char ** tmpListPointers= new char * [newElem+5];
			char *  tmpListArray= new char  [newLen+5];

			char *postmpD=tmpListArray;
			char *postmpS=cListArray[idestIndex];
			long lentmp=unListsLength[idestIndex];

			do
				*(postmpD++)=*(postmpS++);
			while(lentmp-->0);
			{
				char ** tmppos=ListPointers[idestIndex];
				int delta=cListArray[idestIndex]-tmpListArray;
				long tmpnElem=unListsElements[idestIndex];
				long i;
				for(i=0;i<tmpnElem;i++)
					tmpListPointers[i]=tmppos[i]-delta;

				tmppos=ListPointers[isrcIndex];
				delta=cListArray[isrcIndex]-postmpD;

				postmpS=cListArray[isrcIndex];
				lentmp=unListsLength[isrcIndex];
				do
					*(postmpD++)=*(postmpS++);
				while(lentmp-->0);

				{
					char ** tmpListPointers2=tmpListPointers+i;
					tmpnElem=unListsElements[isrcIndex];
					for(i=0;i<tmpnElem;i++)
						tmpListPointers2[i]=tmppos[i]-delta;

					unListsElements[idestIndex]	=newElem;
					unListsState[idestIndex]	=0;
					unListsLength[idestIndex]	=newLen;
					delete ListPointers[idestIndex];
					delete cListArray[idestIndex];
					cListArray[idestIndex]=tmpListArray;
					ListPointers[idestIndex]=tmpListPointers;
				}
			}

		}
		ret=unListsElements[idestIndex];
	}

	return ret;
}


void SortListC(const char *iName)
	{SortList(GetListIndex(iName));}

void SortList(long iIndex)
{
	if (iIndex<nLists && cListArray[iIndex]!=NULL && ListPointers[iIndex]!=NULL && unListsElements[iIndex]>0 && (unListsState[iIndex]&0x1)==0)
	{
		Sort(iIndex,0,unListsElements[iIndex]-1);
		unListsState[iIndex]|=0x1;
	}
}


void Sort(long iIndex, long left, long right)
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
			while(i<right)
			{
				char *pos1=item[i];
				char *pos2=x;
				while(*pos1==*pos2 && *pos1!=0) {pos1++;pos2++;}
				if (*pos1>=*pos2) break;
				i++;
			}

			while(j>left)
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
		if(left<j) Sort(iIndex,left,j);
		if (i<right) Sort(iIndex,i,right);
	}
}

long UniqueListC(const char *iName)
{
	return UniqueList(GetListIndex(iName));
}

long UniqueList(long iIndex)
{
	long ret=0;
	if (iIndex<nLists && (unListsState[iIndex]&0x2)==0)
	{
		if ((unListsState[iIndex]&0x1)==0) SortList(iIndex);
		{
			long nItem=unListsElements[iIndex];
			char ** tmppos=ListPointers[iIndex];
			long npos=0,i;
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
	}
	return ret;
}

long DuplicateList(const char *iName, const char *SourceName)
{
	long ret=0xFFFFFFFF;
	long indexs=GetListIndex(SourceName);
	if (indexs<nLists && strcmp(iName,SourceName)!=0)
	{
		SquiseList(indexs);
		CreateList(iName);
		{
			long indexd=GetListIndex(iName);
			if (indexd<nLists)
			{
				unListsState[indexd]=unListsState[indexs];
				unListsElements[indexd]=unListsElements[indexs];
				unListsLength[indexd]=unListsLength[indexs];
				cDelmiterArray[indexd]=cDelmiterArray[indexs];

				cListArray[indexd]=new char  [unListsLength[indexd]+5];
				ListPointers[indexd]=new char * [unListsElements[indexd]+5];
				{
					char *postmpD=cListArray[indexd];
					char *postmpS=cListArray[indexs];
					long lentmp=unListsLength[indexs];

					do
						*(postmpD++)=*(postmpS++);
					while(lentmp-->0);

					{
						char ** tmppos=ListPointers[indexs];
						char ** tmpposd=ListPointers[indexd];
						int delta=cListArray[indexs]-cListArray[indexd];
						long tmpnElem=unListsElements[indexd];
						long i;

						for(i=0;i<tmpnElem;i++)
							tmpposd[i]=tmppos[i]-delta;

						ret=indexd;
					}
				}
			}
		}
	}
	return ret;
}


long SquiseListC(const char *iName)
	{return SquiseList(GetListIndex(iName));}

long SquiseList(long iIndex)
{
	long ret=0xFFFFFFFF;
	if (iIndex<nLists && cListArray[iIndex]!=NULL)
	{
		long nElem=unListsElements[iIndex];
		long i;
		char **tmppos=ListPointers[iIndex];
		long newLen=0;
		char *tmpList;
		char **tmpPointer;
		char *posDest;

		for(i=0;i<nElem;i++)
		{
			char *pos2=tmppos[i];
			while(*pos2++!=0);
			newLen+=(pos2-tmppos[i]);
		}

		tmpList=new char [newLen+5];
		tmpPointer=new char * [nElem+5];
		posDest=tmpList;

		for(i=0;i<nElem;i++)
		{
			char *pos2=tmppos[i];
			tmpPointer[i]=posDest;
			while((*(posDest++)=*(pos2++))!=0);
		}

		unListsElements[iIndex]	=nElem;
		unListsState[iIndex]	&=(0xFFFFFFFF^0x2);
		unListsLength[iIndex]	=newLen;
		delete ListPointers[iIndex];
		delete cListArray[iIndex];
		cListArray[iIndex]=tmpList;
		ListPointers[iIndex]=tmpPointer;
		ret=nElem;
	}
	return ret;
}

long ORLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	long ret=0xFFFFFFFF;
	long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			long newindex;
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			long newNElem=0;
			long nElem1=unListsElements[index1];
			long nElem2=unListsElements[index2];
			long newLen=0;
			long c1=0,c2=0;
			SortList(index2);
			UniqueList(index2);
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
			newindex=GetListIndex("ortmplist");
			if (newindex<nLists)
			{
				ret=unListsElements[newindex]	=newNElem;
				unListsState[newindex]=0x3;
				unListsLength[newindex]	=newLen;
				cListArray[newindex]=new char [newLen+5];
				ListPointers[newindex]=new char* [newNElem+5];
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					long NElem=0;
		
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
				strcpy(ListsName[newindex],DestName);
				if (strcmp(DestName,SrcName1)==0) DeleteList(index1);
				else if (strcmp(DestName,SrcName2)==0) DeleteList(index2);
			}
		}
	}

	return ret;
}

long XORLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	long ret=0xFFFFFFFF;
	long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			long newindex;
			long newNElem=0;
			long nElem1=unListsElements[index1];
			long nElem2=unListsElements[index2];
			long newLen=0;
			long c1=0,c2=0;

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
				cListArray[newindex]=new char  [newLen+5];
				ListPointers[newindex]=new char * [newNElem+5];
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					long NElem=0;
		
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
				strcpy(ListsName[newindex],DestName);
				if (strcmp(DestName,SrcName1)==0) DeleteList(index1);
				else if (strcmp(DestName,SrcName2)==0) DeleteList(index2);
			}
		}
	}

	return ret;
}

long ANDLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	long ret=0xFFFFFFFF;
	long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			long newNElem=0;
			long nElem1=unListsElements[index1];
			long nElem2=unListsElements[index2];
			long newLen=0;
			long c1=0,c2=0;
			long newindex;
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
				cListArray[newindex]=new char  [newLen+5];
				ListPointers[newindex]=new char * [newNElem+5];
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					long NElem=0;
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
				strcpy(ListsName[newindex],DestName);
				if (strcmp(DestName,SrcName1)==0) DeleteList(index1);
				else if (strcmp(DestName,SrcName2)==0) DeleteList(index2);
			}
		}
	}

	return ret;
}

long NOTLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	long ret=0xFFFFFFFF;
	long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			long newNElem=0;
			long nElem1=unListsElements[index1];
			long nElem2=unListsElements[index2];
			long newLen=0;
			long c1=0,c2=0;
			long newindex;

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
				cListArray[newindex]=new char  [newLen+5];
				ListPointers[newindex]=new char * [newNElem+5];
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					long NElem=0;
					c1=0,c2=0;
					while(c1<nElem1)
					{
						int flgUNI=0;
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

				strcpy(ListsName[newindex],DestName);
				if (strcmp(DestName,SrcName1)==0) DeleteList(index1);
				else if (strcmp(DestName,SrcName2)==0) DeleteList(index2);
			}
		}
	}

	return ret;
}

long ContextLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	long ret=0xFFFFFFFF;
	long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			long newNElem=0;
			long nElem1=unListsElements[index1];
			long nElem2=unListsElements[index2];
			long newLen=0;
			long c1=0,c2=0;
			long newindex;

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
				cListArray[newindex]=new char  [newLen+5];
				ListPointers[newindex]=new char * [newNElem+5];
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					long NElem=0;
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

				strcpy(ListsName[newindex],DestName);
				if (strcmp(DestName,SrcName1)==0) DeleteList(index1);
				else if (strcmp(DestName,SrcName2)==0) DeleteList(index2);
			}
		}
	}

	return ret;
}

long BeginContextLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	long ret=0xFFFFFFFF;
	long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			long newNElem=0;
			long nElem1=unListsElements[index1];
			long nElem2=unListsElements[index2];
			long newLen=0;
			long c1=0,c2=0;
			long newindex;

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
				cListArray[newindex]=new char  [newLen+5];
				ListPointers[newindex]=new char * [newNElem+5];
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					long NElem=0;
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

				strcpy(ListsName[newindex],DestName);
				if (strcmp(DestName,SrcName1)==0) DeleteList(index1);
				else if (strcmp(DestName,SrcName2)==0) DeleteList(index2);
			}
		}
	}

	return ret;
}

long NotBeginContextLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	long ret=0xFFFFFFFF;
	long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			long newNElem=0;
			long nElem1=unListsElements[index1];
			long nElem2=unListsElements[index2];
			long newLen=0;
			long c1=0,c2=0;
			long newindex;

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
				cListArray[newindex]=new char  [newLen+5];
				ListPointers[newindex]=new char * [newNElem+5];
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					long NElem=0;
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

				strcpy(ListsName[newindex],DestName);
				if (strcmp(DestName,SrcName1)==0) DeleteList(index1);
				else if (strcmp(DestName,SrcName2)==0) DeleteList(index2);
			}
		}
	}

	return ret;
}

long EndContextLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	long ret=0xFFFFFFFF;
	long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			long newNElem=0;
			long nElem1=unListsElements[index1];
			long nElem2=unListsElements[index2];
			long newLen=0;
			long c1=0,c2=0;
			long newindex;

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
						while(*pos1!=0)	pos1++;
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
				cListArray[newindex]=new char  [newLen+5];
				ListPointers[newindex]=new char * [newNElem+5];
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					long NElem=0;
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

				strcpy(ListsName[newindex],DestName);
				if (strcmp(DestName,SrcName1)==0) DeleteList(index1);
				else if (strcmp(DestName,SrcName2)==0) DeleteList(index2);
			}
		}
	}

	return ret;
}

long NotEndContextLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	long ret=0xFFFFFFFF;
	long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			long newNElem=0;
			long nElem1=unListsElements[index1];
			long nElem2=unListsElements[index2];
			long newLen=0;
			long c1=0,c2=0;
			long newindex;

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
				cListArray[newindex]=new char  [newLen+5];
				ListPointers[newindex]=new char * [newNElem+5];
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					long NElem=0;
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
						if (flgUNI==0) 
						{	
							char *pos1=tmppos1[c1];
							tmpposDest[NElem++]=posDest;
							while((*(posDest++)=*(pos1++))!=0);
						}
						c1++;
					}
				}

				strcpy(ListsName[newindex],DestName);
				if (strcmp(DestName,SrcName1)==0) DeleteList(index1);
				else if (strcmp(DestName,SrcName2)==0) DeleteList(index2);
			}
		}
	}

	return ret;
}

long NotContextLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	long ret=0xFFFFFFFF;
	long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			long newNElem=0;
			long nElem1=unListsElements[index1];
			long nElem2=unListsElements[index2];
			long newLen=0;
			long c1=0,c2=0;
			long newindex;

			SortList(index2);
			UniqueList(index2);
			while(c1<nElem1)
			{
				char *pos1=tmppos1[c1];
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
				cListArray[newindex]=new char  [newLen+5];
				ListPointers[newindex]=new char * [newNElem+5];
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					long NElem=0;
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

				strcpy(ListsName[newindex],DestName);
				if (strcmp(DestName,SrcName1)==0) DeleteList(index1);
				else if (strcmp(DestName,SrcName2)==0) DeleteList(index2);
			}
		}
	}

	return ret;
}

long MaskLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	long ret=0xFFFFFFFF;
	long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			long newNElem=0;
			long nElem1=unListsElements[index1];
			long nElem2=unListsElements[index2];
			long newLen=0;
			long c1=0,c2=0;
			long newindex;

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
								if (*pos2!='^')
									while(*pos1!=0 && *pos1!=*pos2) pos1++;
								if (*(reppos=pos1)==0) break;
							}
							while((*pos1==*pos2 || *pos2=='^') && *pos1!=0 && *pos2!=']') {pos1++;pos2++;}
							if (*pos2==0 || *pos2==']') {flgUNI=1;break;}
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
				cListArray[newindex]=new char  [newLen+5];
				ListPointers[newindex]=new char * [newNElem+5];
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					long NElem=0;
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
										if (*pos2!='^')
											while(*pos1!=0 && *pos1!=*pos2) pos1++;
										if (*(reppos=pos1)==0) break;
									}
									while((*pos1==*pos2 || *pos2=='^') && *pos1!=0 && *pos2!=']') {pos1++;pos2++;}
									if (*pos2==0 || *pos2==']') {flgUNI=1;break;}
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

				strcpy(ListsName[newindex],DestName);
				if (strcmp(DestName,SrcName1)==0) DeleteList(index1);
				else if (strcmp(DestName,SrcName2)==0) DeleteList(index2);
			}
		}
	}

	return ret;
}

long NotMaskLists(const char *DestName, const char *SrcName1, const char *SrcName2)
{
	long ret=0xFFFFFFFF;
	long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			long newNElem=0;
			long nElem1=unListsElements[index1];
			long nElem2=unListsElements[index2];
			long newLen=0;
			long c1=0,c2=0;
			long newindex;

			SortList(index2);
			UniqueList(index2);
			while(c1<nElem1)
			{
				char *pos1=tmppos1[c1];
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
							if (*pos2!='^')
								while(*pos1!=0 && *pos1!=*pos2) pos1++;
							if (*(reppos=pos1)==0) break;
						}
						while((*pos1==*pos2 || *pos2=='^') && *pos1!=0 && *pos2!=']') {pos1++;pos2++;}
						if (*pos2==0 || *pos2==']') {flgUNI=1;break;}
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
				cListArray[newindex]=new char  [newLen+5];
				ListPointers[newindex]=new char * [newNElem+5];
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					long NElem=0;
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
									if (*pos2!='^')
										while(*pos1!=0 && *pos1!=*pos2) pos1++;
									if (*(reppos=pos1)==0) break;
								}
								while((*pos1==*pos2 || *pos2=='^') && *pos1!=0 && *pos2!=']') {pos1++;pos2++;}
								if (*pos2==0 || *pos2==']') {flgUNI=1;break;}
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

				strcpy(ListsName[newindex],DestName);
				if (strcmp(DestName,SrcName1)==0) DeleteList(index1);
				else if (strcmp(DestName,SrcName2)==0) DeleteList(index2);
			}
		}
	}

	return ret;
}


long LoadList(const char *iName)
{
	long ret=0xFFFFFFFF;
	int chtr=0;
	char nm[250];
	FILE *src=NULL;
	sprintf(nm,"%s/%s%s",ListsPath,IdPort,iName);
	while(src==NULL && ++chtr<3)
	{
		src=fopen(nm,"rb");
		if (src!=NULL)
		{
			long iIndex;
			if (m_Echo!=0) printf("BEGIN LOADLIST #%s#%s# -OK\n",nm,iName);
			CreateList(iName);
			iIndex=GetListIndex(iName);
			if (iIndex<nLists)
			{
				if (m_Echo!=0) printf("CONTINUE LOADLIST #%s#%s# -OK\n",nm,iName);
				long nElem=0;
				char *pos;
				if (cListArray[iIndex]!=NULL) delete cListArray[iIndex];
				cListArray[iIndex]=NULL;
				if (ListPointers[iIndex]!=NULL) delete ListPointers[iIndex];
				ListPointers[iIndex]=NULL;
				unListsState[iIndex]=0;
				unListsElements[iIndex]=0;
				unListsLength[iIndex]=0;
				cDelmiterArray[iIndex]=10;
				fseek(src,0,SEEK_END);
				unListsLength[iIndex]=ftell(src);
				cListArray[iIndex]=new char  [unListsLength[iIndex]+5];
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
				if (m_Echo!=0) printf("END LOADLIST #%s# - %d %d\n",nm,iIndex,nElem);
			}
			else
				if (m_Echo!=0) printf("END LOADLIST #%s# - %d -FAIL\n",nm,iIndex);

			fclose(src);
		}
		else
		{
			sleep(1);
		}
	}

	if (src==NULL)
	{
		long iIndex;
		if (m_Echo!=0) printf("#%s# - FAIL\n",nm);
		CreateList(iName);
			iIndex=GetListIndex(iName);
			if (iIndex<nLists)
			{
				long nElem=0;
				char *pos;
				if (cListArray[iIndex]!=NULL) delete cListArray[iIndex];
				cListArray[iIndex]=NULL;
				if (ListPointers[iIndex]!=NULL) delete ListPointers[iIndex];
				ListPointers[iIndex]=NULL;
				unListsState[iIndex]=0;
				unListsElements[iIndex]=0;
				unListsLength[iIndex]=0;
				cDelmiterArray[iIndex]=10;
				cListArray[iIndex]=new char  [50];
 				cListArray[iIndex][unListsLength[iIndex]]=0;
				ListPointers[iIndex]=new char * [50];
			}
	}

	return ret;
}

int SaveList(const char *nmlist, const char *nmFile)
{
	FILE *dst;
	char fName[500];
	sprintf(fName,"%s/%s%s",ListsPath,IdPort,nmFile);
	///////////////////////////////
//	printf("%s/%s%s",ListsPath,IdPort,nmFile);
	dst=fopen(fName,"wb");
	if (dst!=NULL)
	{
		long iIndex;
		if (m_Echo!=0) printf("#%s# -OK\n",fName);
		iIndex=GetListIndex(nmlist);
		if (iIndex<nLists && unListsElements[iIndex]>0 && ListPointers[iIndex]!=NULL)
		{
			long nItem=unListsElements[iIndex];
			long i=0;
			char *ps;
			long len=0;
			long nWri=0;
			SortList(iIndex);
			UniqueList(iIndex);

			for(i=0;i<nItem;i++)
			{
				len=0;
				ps=ListPointers[iIndex][i];
				while(*(ps++)!=0) len++;
				if (len>0)
				{
				    if (nWri++!=0) fputc(10,dst);
				    fwrite(ListPointers[iIndex][i],1,len,dst);
				}
			}
		}

		fclose(dst);
	}
	else if (m_Echo!=0) printf("#%s# -FAIL\n",fName);

	return 0;
}	

int DoMethod(char *iStr, char **oStr)
{
	char met[50];
	char *pos;
	int nfunc=0;
	int retint=-123456; 
	int atoipos;
	const long uNMethods=25;
	const char *cArrMethods[25]={
			"XORLISTS","ANDLISTS","NOTLISTS","ORLISTS","SQUISELIST",
			"DUPLICATELIST","UNIQUELIST","SORTLIST","ADDLIST","APPENDLIST",
			"SETLISTDELIMITER","SETLIST","LOADLIST","CREATELIST","DELETELIST",
			"SAVELIST","CONTEXTLISTS","MASKLISTS","NOTMASKLISTS","NOTCONTEXTLISTS",
			"BEGINCONTEXTLISTS","NOTBEGINCONTEXTLISTS","ENDCONTEXTLISTS","NOTENDCONTEXTLISTS","ECHO",
	};

	strncpy(met,iStr,45);
	pos=met;
	while(*pos!=0 && *pos!=' ')
		*(pos++)&=0xDF;

	pos=strchr(met,' ');
	if (pos==NULL) pos=iStr+(int)strlen(iStr);
	else	
	{
		*(pos++)=0;
		pos=strchr(iStr,' ');
		pos++;
	}

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
			char *nmdest=pos,*nm1,*nm2;
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
		}
		break;
	case 4: /*SQUISELIST*/
		retint=SquiseListC(pos);
		break;
	case 5: /*DUPLICATELIST*/	
	case 8: /*ADDLIST*/
	case 9: /*APPENDLIST*/
	case 10: /*SETLISTDELIMITER*/
	case 11: /*SETLIST*/
	case 15: /*SAVELIST*/
		{
			char *nmdest=pos,*nm1;
			nm1=strchr(nmdest,',');
			if (nm1!=NULL) *(nm1++)=0;
			else nm1="";
			if (*nmdest!=0 && *nm1!=0) 
				switch(nfunc)
				{
				case 0: /*DUPLICATELIST*/	retint=DuplicateList(nmdest,nm1);	break;
				case 8: /*ADDLIST*/			retint=AddListC(nmdest,nm1);		break;
				case 9: /*APPENDLIST*/		retint=AppendListC(nmdest,nm1);		break;
				case 10: /*SETLISTDELIMITER*/	retint=SetListDelimiterC(nmdest,*nm1);		break;
				case 11: /*SETLIST*/		retint=SetListC(nmdest,nm1,'^');	break;
				case 15: /*SAVELIST*/	
					{
						if (*nm1==0) nm1=nmdest;
						retint=SaveList(nmdest,nm1);
					}
					break;
				}
		}
		break;
	case 6: /*UNIQUELIST*/		retint=UniqueListC(pos);	break;
	case 7: /*SORTLIST*/		SortListC(pos);				break;
	case 12: /*LOADLIST*/		retint=LoadList(pos);		break;
	case 13: /*CREATELIST*/		retint=CreateList(pos);		break;
	case 14: /*DELETELIST*/		retint=DeleteListC(pos);	break;
	case 24: /*ECHO*/			m_Echo=atoi(pos);			break;
	}

	return nfunc;
}
