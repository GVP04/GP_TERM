// ListMaker.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"

#include "errno.h"
#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "string.h"
#include "unistd.h"
/*
cc ListMaker.c -o ListMaker -lc
chmod 777 ListMaker
*/
/*cc ListMaker.c -o ListMaker| pg*/
/*chmod 777 ListMaker*/
	long SaveList(char *nmlist, char *nmFile);
	long DoMethod(char *iStr, char **oStr);
	unsigned long NotBeginContextLists(char *DestName, char *SrcName1, char *SrcName2);
	unsigned long BeginContextLists(char *DestName, char *SrcName1, char *SrcName2);
	unsigned long NotEndContextLists(char *DestName, char *SrcName1, char *SrcName2);
	unsigned long EndContextLists(char *DestName, char *SrcName1, char *SrcName2);
	unsigned long NotContextLists(char *DestName, char *SrcName1, char *SrcName2);
	unsigned long NotMaskLists(char *DestName, char *SrcName1, char *SrcName2);
	unsigned long MaskLists(char *DestName, char *SrcName1, char *SrcName2);
	unsigned long ContextLists(char *DestName, char *SrcName1, char *SrcName2);
	unsigned long XORLists(char *DestName, char *SrcName1, char *SrcName2);
	unsigned long ANDLists(char *DestName, char *SrcName1, char *SrcName2);
	unsigned long NOTLists(char *DestName, char *SrcName1, char *SrcName2);
	unsigned long ORLists(char *DestName, char *SrcName1, char *SrcName2);
	unsigned long SquiseListC(char *iName);
	unsigned long DuplicateList(char *iName, char *SourceName);
	unsigned long UniqueListC(char *iName);
	void SortListC(char *iName);
	unsigned long AddListC(char *destList,char *srcList);
	unsigned long AppendListC(char *iName, char * iList);
	unsigned long GetListItemCountC(char *iName);
	unsigned long GetListStateC(char *iName);
	unsigned long GetListLengthC(char *iName);
	char * GetListItemC(char *iName, unsigned long iNItem);
	char GetListDelimiterC(char *iName);
	char SetListDelimiterC(char *iName,char newDelimiter);
	unsigned long GetCount();
	unsigned long SetListC(char *iName, char *iList,char delimiter);
	unsigned long LoadList(char *iName);
	unsigned long CreateList(char * iName);
	unsigned long DeleteListC(char *iName);
	unsigned long DeleteList(unsigned long iIndex);
	unsigned long SquiseList(unsigned long iIndex);
	unsigned long UniqueList(unsigned long iIndex);
	void Sort(unsigned long iIndex, long left, long right);
	void SortList(unsigned long iIndex);
	unsigned long AddList(unsigned long idestIndex, unsigned long isrcIndex);
	unsigned long GetListState(unsigned long iIndex);
	unsigned long AppendList(unsigned long iIndex, char * iList);
	char * GetListItem(unsigned long iIndex, unsigned long iNItem);
	unsigned long GetListLength(unsigned long iIndex);
	unsigned long GetListItemCount(unsigned long iIndex);
	char GetListDelimiter(unsigned long iIndex);
	char SetListDelimiter(unsigned long iIndex,char newDelimiter);
	unsigned long SetList(unsigned long iIndex, char *iList,char delimiter);
	unsigned long GetListIndex(char *LName);
	char ** cListArray;
	char *** ListPointers;
	char * cDelmiterArray;
	unsigned long * unListsState;
	unsigned long * unListsElements;
	unsigned long * unListsLength;
	char  **ListsName;
	unsigned long nLists;
	unsigned long nMaxLists;
	char IdPort[100];
	char ListsPath[256];
	long m_Echo=0;


int main(int argc, char* argv[])
{
	unsigned long i;
	nMaxLists=200;
	nLists=0;
	printf("executing main \n");
	cListArray=(char **)malloc(nMaxLists*4);
	//ListsName= (char **)malloc(nMaxLists*4);
	ListsName= (char **)malloc(nMaxLists*sizeof(char *));
	ListPointers=(char ***)malloc( nMaxLists*4);
	unListsElements=(unsigned long *)malloc( nMaxLists*4);
	unListsLength=(unsigned long *)malloc( nMaxLists*4);
	unListsState=(unsigned long *)malloc( nMaxLists*4);
	cDelmiterArray=(char *)malloc( nMaxLists);
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
		strncpy(IdPort,argv[1],250);IdPort[250]=0;
		if (argc>2 && argv[2]!=0 && *argv[2]!=0) 
			strcpy(ListsPath,argv[2]);
		sprintf(comname,"%s/%scommand",ListsPath,IdPort);

		src=fopen(comname,"rt");
		if (src!=NULL)
		{
			unsigned long fLen;
			char *buff,*pos;
			fseek(src,0,SEEK_END);
			fLen=ftell(src);
			rewind(src);
			buff=(char *) malloc(fLen+10);
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
					printf("pos consist: %s\n",pos);
					DoMethod(pos,NULL);
					printf("pos consist: %s\n",pos);
					pos=pos2;
				}


				free(buff);
			}
			fclose(src);
		}
                  else printf("not commanm #%s#\n",comname);
	}

	if (cListArray!=NULL)
	{
		for(i=0;i<nLists;i++)
			if (cListArray[i]!=NULL)
			{
				free(cListArray[i]);
				cListArray[i]=NULL;
			}
		free(cListArray);
		cListArray=NULL;
	}
	if (ListsName!=NULL)
	{
		for(i=0;i<nLists;i++)
			if (ListsName[i]!=NULL) 
			{
				free(ListsName[i]);
				ListsName[i]=NULL;
			}
		free(ListsName);
		ListsName=NULL;
	}

	if (ListPointers!=NULL)
	{
		for(i=0;i<nLists;i++)
			if (ListPointers[i]!=NULL) 
			{
				free(ListPointers[i]);
				ListPointers[i]=NULL;
			}
		free(ListPointers);
		ListPointers=NULL;
	}
	if (unListsElements!=NULL)	free( unListsElements);
	unListsElements=NULL;
	if (unListsLength!=NULL)	free( unListsLength);
	unListsLength=NULL;
	if (cDelmiterArray!=NULL)	free( cDelmiterArray);
	cDelmiterArray=NULL;
	if (unListsState!=NULL)		free( unListsState);
	unListsState=NULL;




	return 0;
}


unsigned long DeleteListC(char *iName)
	{return DeleteList(GetListIndex(iName));}

unsigned long DeleteList(unsigned long iIndex)
{
	if (iIndex<nLists)
	{
		unsigned long i;
		if (cListArray!=NULL && cListArray[iIndex]!=NULL)
		{
			free(cListArray[iIndex]);
			cListArray[iIndex]=NULL;
		}
		if (ListsName!=NULL && ListsName[iIndex]!=NULL) 
		{
			free(ListsName[iIndex]);
			ListsName[iIndex]=NULL;
		}

		if (ListPointers!=NULL && ListPointers[iIndex]!=NULL) 
		{
			free(ListPointers[iIndex]);
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

unsigned long GetListIndex(char *LName)
{
	unsigned long ret=-1;
	if (ListsName!=NULL)
		for(ret=0;ret<nLists;ret++)
			if (ListsName[ret]!=NULL &&  strcmp(ListsName[ret],LName)==0) break; 
	return ret==nLists?-1:ret;
}

unsigned long CreateList(char *iName)
{
printf("Executing CreateList \n");
printf("%s \n",iName);
printf("nLists:%d,nMaxLists:%d \n",nLists,nMaxLists);
	if (nLists>=nMaxLists)
	{
		nMaxLists+=50;
		{
			char ** cListArrayT=(char **)malloc(nMaxLists*4);
			char ** ListsNameT= (char **)malloc(nMaxLists*4);
			char *** ListPointersT=(char ***)malloc( nMaxLists*4);
			unsigned long * unListsElementsT=(unsigned long *)malloc( nMaxLists*4);
			unsigned long * unListsLengthT=(unsigned long *)malloc( nMaxLists*4);
			unsigned long * unListsStateT=(unsigned long *)malloc( nMaxLists*4);
			char * cDelmiterArrayT=(char *)malloc( nMaxLists);
			unsigned long i;

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

			free(cListArray);
			free(ListsName);
			free(ListPointers);
			free(unListsState);
			free(unListsElements);
			free(unListsLength);
			free(cDelmiterArray);

			cListArray=cListArrayT;
			ListsName=ListsNameT;
			ListPointers=ListPointersT;
			unListsState=unListsStateT;
			unListsElements=unListsElementsT;
			unListsLength=unListsLengthT;
			cDelmiterArray=cDelmiterArrayT;
		}
	}
	
printf("Try Execute DeleteListC with:%s\n",iName);
	DeleteListC(iName);
printf("DeleteListC is execute \n");
perror(sys_errlist[errno]);
	//ListsName[nLists]=(char *)malloc(20);
	ListsName[nLists]=(char *)malloc(sizeof(char)*20);
perror(sys_errlist[errno]);
if (errno==ENOMEM)
{
	//printf("ERROR IN MALLOC \n");
	perror("ERRoR in malloc");
}
printf("Execute malloc, nLists:%d\n",nLists);
fflush (stdout);
	strcpy(ListsName[nLists],iName);
printf("Create list:%s\n",ListsName[nLists]);	
	cListArray[nLists]=NULL;
	ListPointers[nLists]=NULL;
	unListsState[nLists]=0;
	unListsElements[nLists]=0;
	unListsLength[nLists]=0;
	cDelmiterArray[nLists]='^';

	return nLists++;
}

unsigned long SetListC(char *iName, char *iList,char delimiter)
{
	CreateList(iName);
	return SetList(GetListIndex(iName),iList,delimiter);
}

unsigned long SetList(unsigned long iIndex, char *iList,char delimiter)
{
	unsigned long ret=-1;
	if (iIndex<nLists)
	{
		unsigned long nElem=0;
		char *pos;
		if (cListArray[iIndex]!=NULL) free(cListArray[iIndex]);
		cListArray[iIndex]=NULL;
		if (ListPointers[iIndex]!=NULL) free(ListPointers[iIndex]);
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
			cListArray[iIndex]=(char *) malloc(unListsLength[iIndex]+5);
			ListPointers[iIndex]=(char **) malloc((nElem+5)*sizeof(char *));

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

unsigned long GetCount()	
	{return nLists;}

unsigned long GetListItemCountC(char *iName)
	{return GetListItemCount(GetListIndex(iName));}

char GetListDelimiterC(char *iName)
	{return GetListDelimiter(GetListIndex(iName));}

char SetListDelimiterC(char *iName,char newDelimiter)
	{return SetListDelimiter(GetListIndex(iName),newDelimiter);}

unsigned long GetListItemCount(unsigned long iIndex)
	{return (iIndex<nLists)?unListsElements[iIndex]:-1;}

unsigned long GetListStateC(char *iName)
	{return GetListState(GetListIndex(iName));}

unsigned long GetListState(unsigned long iIndex)
	{return (iIndex<nLists)?unListsState[iIndex]:-1;}

char GetListDelimiter(unsigned long iIndex)
	{return (iIndex<nLists)?cDelmiterArray[iIndex]:0;}

char SetListDelimiter(unsigned long iIndex,char newDelimiter)
	{return (iIndex<nLists)?cDelmiterArray[iIndex]=newDelimiter:0;}

char * GetListItemC(char *iName, unsigned long iNItem)
	{return GetListItem(GetListIndex(iName),iNItem);}

char * GetListItem(unsigned long iIndex, unsigned long iNItem)
	{return (iIndex<nLists && ListPointers[iIndex]!=NULL && iNItem<unListsElements[iIndex])?ListPointers[iIndex][iNItem]:NULL;}

unsigned long GetListLengthC(char *iName)
	{return GetListLength(GetListIndex(iName));}

unsigned long GetListLength(unsigned long iIndex)
	{return (iIndex<nLists)?unListsLength[iIndex]:-1;}


unsigned long AppendListC(char *iName, char * iList)
	{return AppendList(GetListIndex(iName),iList);}

unsigned long AppendList(unsigned long iIndex, char * iList)
{
	unsigned long ret=-1;
	if (iIndex<nLists)
	{
		unsigned long nElem=0;
		char delimiter=cDelmiterArray[iIndex];
		char *pos=iList;
		unsigned long appLen;
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
				unsigned long newLen=unListsLength[iIndex]+pos-iList;
				unsigned long newElem=unListsElements[iIndex]+nElem;
				unsigned long oldElem=unListsElements[iIndex];

				char ** tmpListPointers=(char **)malloc(4*(newElem+5));
				char *  tmpListArray=(char * )malloc(newLen+5);

				char *postmpD=tmpListArray+unListsLength[iIndex];
				char *postmpS=cListArray[iIndex]+unListsLength[iIndex];
				do *postmpD=*postmpS--;

				while(postmpD--!=tmpListArray);

				{
					char ** tmppos=ListPointers[iIndex];
					long delta=cListArray[iIndex]-tmpListArray;
					unsigned long i;
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
						free(ListPointers[iIndex]);
						free(cListArray[iIndex]);
						cListArray[iIndex]=tmpListArray;
						ListPointers[iIndex]=tmpListPointers;
					}
				}
			}
		}
	}

	return ret;

}


unsigned long AddListC(char *destList, char *srcList)
{
	return AddList(GetListIndex(destList),GetListIndex(srcList));
}

unsigned long AddList(unsigned long idestIndex, unsigned long isrcIndex)
{
	unsigned long ret=0;
	if (idestIndex<nLists)
	{
		if (isrcIndex<nLists)
		{
			unsigned long newLen=unListsLength[idestIndex]+unListsLength[isrcIndex];
			unsigned long newElem=unListsElements[idestIndex]+unListsElements[isrcIndex];

			char ** tmpListPointers= ( char **)malloc(4*( newElem+5));
			char *  tmpListArray= ( char *)malloc(newLen+5);

			char *postmpD=tmpListArray;
			char *postmpS=cListArray[idestIndex];
			unsigned long lentmp=unListsLength[idestIndex];

			do
				*(postmpD++)=*(postmpS++);
			while(lentmp-->0);
			{
				char ** tmppos=ListPointers[idestIndex];
				long delta=cListArray[idestIndex]-tmpListArray;
				unsigned long tmpnElem=unListsElements[idestIndex];
				unsigned long i;
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
					free(ListPointers[idestIndex]);
					free(cListArray[idestIndex]);
					cListArray[idestIndex]=tmpListArray;
					ListPointers[idestIndex]=tmpListPointers;
				}
			}

		}
		ret=unListsElements[idestIndex];
	}

	return ret;
}


void SortListC(char *iName)
	{SortList(GetListIndex(iName));}

void SortList(unsigned long iIndex)
{
	if (iIndex<nLists && cListArray[iIndex]!=NULL && ListPointers[iIndex]!=NULL && unListsElements[iIndex]>0 && (unListsState[iIndex]&0x1)==0)
	{
		Sort(iIndex,0,unListsElements[iIndex]-1);
		unListsState[iIndex]|=0x1;
	}
}


void Sort(unsigned long iIndex, long left, long right)
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

unsigned long UniqueListC(char *iName)
{
	return UniqueList(GetListIndex(iName));
}

unsigned long UniqueList(unsigned long iIndex)
{
	unsigned long ret=0;
	if (iIndex<nLists && (unListsState[iIndex]&0x2)==0)
	{
		if ((unListsState[iIndex]&0x1)==0) SortList(iIndex);
		{
			unsigned long nItem=unListsElements[iIndex];
			char ** tmppos=ListPointers[iIndex];
			unsigned long npos=0,i;
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

unsigned long DuplicateList(char *iName, char *SourceName)
{
	unsigned long ret=-1;
	unsigned long indexs=GetListIndex(SourceName);
	if (indexs<nLists && strcmp(iName,SourceName)!=0)
	{
		SquiseList(indexs);
		CreateList(iName);
		{
			unsigned long indexd=GetListIndex(iName);
			if (indexd<nLists)
			{
				unListsState[indexd]=unListsState[indexs];
				unListsElements[indexd]=unListsElements[indexs];
				unListsLength[indexd]=unListsLength[indexs];
				cDelmiterArray[indexd]=cDelmiterArray[indexs];

				cListArray[indexd]=(char *) malloc(unListsLength[indexd]+5);
				ListPointers[indexd]=(char **) malloc(4*(unListsElements[indexd]+5));
				{
					char *postmpD=cListArray[indexd];
					char *postmpS=cListArray[indexs];
					unsigned long lentmp=unListsLength[indexs];

					do
						*(postmpD++)=*(postmpS++);
					while(lentmp-->0);

					{
						char ** tmppos=ListPointers[indexs];
						char ** tmpposd=ListPointers[indexd];
						long delta=cListArray[indexs]-cListArray[indexd];
						unsigned long tmpnElem=unListsElements[indexd];
						unsigned long i;

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


unsigned long SquiseListC(char *iName)
	{return SquiseList(GetListIndex(iName));}

unsigned long SquiseList(unsigned long iIndex)
{
	unsigned long ret=-1;
	if (iIndex<nLists && cListArray[iIndex]!=NULL)
	{
		unsigned long nElem=unListsElements[iIndex];
		unsigned long i;
		char **tmppos=ListPointers[iIndex];
		unsigned long newLen=0;
		char *tmpList;
		char **tmpPointer;
		char *posDest;

		for(i=0;i<nElem;i++)
		{
			char *pos2=tmppos[i];
			while(*pos2++!=0);
			newLen+=(pos2-tmppos[i]);
		}

		tmpList=(char*)malloc(newLen+5);
		tmpPointer=(char **)malloc(4*(nElem+5));
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
		free(ListPointers[iIndex]);
		free(cListArray[iIndex]);
		cListArray[iIndex]=tmpList;
		ListPointers[iIndex]=tmpPointer;
		ret=nElem;
	}
	return ret;
}

unsigned long ORLists(char *DestName, char *SrcName1, char *SrcName2)
{
	unsigned long ret=-1;
	unsigned long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		unsigned long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			unsigned long newindex;
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			unsigned long newNElem=0;
			unsigned long nElem1=unListsElements[index1];
			unsigned long nElem2=unListsElements[index2];
			unsigned long newLen=0;
			unsigned long c1=0,c2=0;
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
				cListArray[newindex]=(char*)malloc(newLen+5);
				ListPointers[newindex]=(char**)malloc(4*(newNElem+5));
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					unsigned long NElem=0;
		
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

unsigned long XORLists(char *DestName, char *SrcName1, char *SrcName2)
{
	unsigned long ret=-1;
	unsigned long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		unsigned long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			unsigned long newindex;
			unsigned long newNElem=0;
			unsigned long nElem1=unListsElements[index1];
			unsigned long nElem2=unListsElements[index2];
			unsigned long newLen=0;
			unsigned long c1=0,c2=0;

			SortList(index2);
			UniqueList(index2);
			while(c1<nElem1)
			{
				long flgUNI=0;
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
				cListArray[newindex]=(char *) malloc(newLen+5);
				ListPointers[newindex]=(char **)malloc(4*(newNElem+5));
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					unsigned long NElem=0;
		
					c1=0,c2=0;
					while(c1<nElem1)
					{
						long flgUNI=0;
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

unsigned long ANDLists(char *DestName, char *SrcName1, char *SrcName2)
{
	unsigned long ret=-1;
	unsigned long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		unsigned long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			unsigned long newNElem=0;
			unsigned long nElem1=unListsElements[index1];
			unsigned long nElem2=unListsElements[index2];
			unsigned long newLen=0;
			unsigned long c1=0,c2=0;
			unsigned long newindex;
			SortList(index2);
			UniqueList(index2);

			while(c1<nElem1)
			{
				long flgUNI=0;
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
				cListArray[newindex]=(char *) malloc(newLen+5);
				ListPointers[newindex]=(char **) malloc(4*(newNElem+5));
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					unsigned long NElem=0;
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					ret=unListsElements[newindex]	=newNElem;
					unListsState[newindex]=0x3;
					unListsLength[newindex]	=newLen;
		
					c1=0,c2=0;
					while(c1<nElem1)
					{
						long flgUNI=0;
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

unsigned long NOTLists(char *DestName, char *SrcName1, char *SrcName2)
{
	unsigned long ret=-1;
	unsigned long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		unsigned long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			unsigned long newNElem=0;
			unsigned long nElem1=unListsElements[index1];
			unsigned long nElem2=unListsElements[index2];
			unsigned long newLen=0;
			unsigned long c1=0,c2=0;
			unsigned long newindex;

			SortList(index2);
			UniqueList(index2);
			while(c1<nElem1)
			{
				long flgUNI=0;
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
				cListArray[newindex]=(char *) malloc(newLen+5);
				ListPointers[newindex]=(char **) malloc(4*(newNElem+5));
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					unsigned long NElem=0;
					c1=0,c2=0;
					while(c1<nElem1)
					{
						long flgUNI=0;
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

unsigned long ContextLists(char *DestName, char *SrcName1, char *SrcName2)
{
	unsigned long ret=-1;
	unsigned long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		unsigned long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			unsigned long newNElem=0;
			unsigned long nElem1=unListsElements[index1];
			unsigned long nElem2=unListsElements[index2];
			unsigned long newLen=0;
			unsigned long c1=0,c2=0;
			unsigned long newindex;

			SortList(index2);
			UniqueList(index2);
			while(c1<nElem1)
			{
				long flgUNI=0;
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
				cListArray[newindex]=(char *) malloc(newLen+5);
				ListPointers[newindex]=(char **) malloc(4*(newNElem+5));
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					unsigned long NElem=0;
					c1=0,c2=0;
					while(c1<nElem1)
					{
						long flgUNI=0;
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

unsigned long BeginContextLists(char *DestName, char *SrcName1, char *SrcName2)
{
	unsigned long ret=-1;
	unsigned long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		unsigned long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			unsigned long newNElem=0;
			unsigned long nElem1=unListsElements[index1];
			unsigned long nElem2=unListsElements[index2];
			unsigned long newLen=0;
			unsigned long c1=0,c2=0;
			unsigned long newindex;

			SortList(index2);
			UniqueList(index2);
			while(c1<nElem1)
			{
				long flgUNI=0;
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
				cListArray[newindex]=(char *) malloc(newLen+5);
				ListPointers[newindex]=(char **) malloc(4*(newNElem+5));
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					unsigned long NElem=0;
					c1=0,c2=0;
					while(c1<nElem1)
					{
						long flgUNI=0;
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

unsigned long NotBeginContextLists(char *DestName, char *SrcName1, char *SrcName2)
{
	unsigned long ret=-1;
	unsigned long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		unsigned long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			unsigned long newNElem=0;
			unsigned long nElem1=unListsElements[index1];
			unsigned long nElem2=unListsElements[index2];
			unsigned long newLen=0;
			unsigned long c1=0,c2=0;
			unsigned long newindex;

			SortList(index2);
			UniqueList(index2);
			while(c1<nElem1)
			{
				char *pos1=tmppos1[c1];
				long flgUNI=0;
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
				cListArray[newindex]=(char *) malloc(newLen+5);
				ListPointers[newindex]=(char **) malloc(4*(newNElem+5));
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					unsigned long NElem=0;
					c1=0,c2=0;
					while(c1<nElem1)
					{
						long flgUNI=0;
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

unsigned long EndContextLists(char *DestName, char *SrcName1, char *SrcName2)
{
	unsigned long ret=-1;
	unsigned long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		unsigned long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			unsigned long newNElem=0;
			unsigned long nElem1=unListsElements[index1];
			unsigned long nElem2=unListsElements[index2];
			unsigned long newLen=0;
			unsigned long c1=0,c2=0;
			unsigned long newindex;

			SortList(index2);
			UniqueList(index2);
			while(c1<nElem1)
			{
				long flgUNI=0;
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
				cListArray[newindex]=(char *) malloc(newLen+5);
				ListPointers[newindex]=(char **) malloc(4*(newNElem+5));
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					unsigned long NElem=0;
					c1=0,c2=0;
					while(c1<nElem1)
					{
						long flgUNI=0;
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

unsigned long NotEndContextLists(char *DestName, char *SrcName1, char *SrcName2)
{
	unsigned long ret=-1;
	unsigned long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		unsigned long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			unsigned long newNElem=0;
			unsigned long nElem1=unListsElements[index1];
			unsigned long nElem2=unListsElements[index2];
			unsigned long newLen=0;
			unsigned long c1=0,c2=0;
			unsigned long newindex;

			SortList(index2);
			UniqueList(index2);
			while(c1<nElem1)
			{
				long flgUNI=0;
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
				cListArray[newindex]=(char *) malloc(newLen+5);
				ListPointers[newindex]=(char **) malloc(4*(newNElem+5));
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					unsigned long NElem=0;
					c1=0,c2=0;
					while(c1<nElem1)
					{
						long flgUNI=0;
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

unsigned long NotContextLists(char *DestName, char *SrcName1, char *SrcName2)
{
	unsigned long ret=-1;
	unsigned long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		unsigned long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			unsigned long newNElem=0;
			unsigned long nElem1=unListsElements[index1];
			unsigned long nElem2=unListsElements[index2];
			unsigned long newLen=0;
			unsigned long c1=0,c2=0;
			unsigned long newindex;

			SortList(index2);
			UniqueList(index2);
			while(c1<nElem1)
			{
				char *pos1=tmppos1[c1];
				long flgUNI=0;
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
				cListArray[newindex]=(char *) malloc(newLen+5);
				ListPointers[newindex]=(char **) malloc(4*(newNElem+5));
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					unsigned long NElem=0;
					c1=0,c2=0;
					while(c1<nElem1)
					{
						long flgUNI=0;
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

unsigned long MaskLists(char *DestName, char *SrcName1, char *SrcName2)
{
	unsigned long ret=-1;
	unsigned long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		unsigned long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			unsigned long newNElem=0;
			unsigned long nElem1=unListsElements[index1];
			unsigned long nElem2=unListsElements[index2];
			unsigned long newLen=0;
			unsigned long c1=0,c2=0;
			unsigned long newindex;

			SortList(index2);
			UniqueList(index2);
			while(c1<nElem1)
			{
				long flgUNI=0;
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
				cListArray[newindex]=(char *) malloc(newLen+5);
				ListPointers[newindex]=(char **) malloc(4*(newNElem+5));
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					unsigned long NElem=0;
					c1=0,c2=0;
					while(c1<nElem1)
					{
						long flgUNI=0;
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

unsigned long NotMaskLists(char *DestName, char *SrcName1, char *SrcName2)
{
	unsigned long ret=-1;
	unsigned long index1=GetListIndex(SrcName1);
	if (index1<nLists)
	{
		unsigned long index2=GetListIndex(SrcName2);
		SortList(index1);
		UniqueList(index1);
		if (index2<nLists)
		{
			char **tmppos1=ListPointers[index1];
			char **tmppos2=ListPointers[index2];
			unsigned long newNElem=0;
			unsigned long nElem1=unListsElements[index1];
			unsigned long nElem2=unListsElements[index2];
			unsigned long newLen=0;
			unsigned long c1=0,c2=0;
			unsigned long newindex;

			SortList(index2);
			UniqueList(index2);
			while(c1<nElem1)
			{
				char *pos1=tmppos1[c1];
				long flgUNI=0;
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
				cListArray[newindex]=(char *) malloc(newLen+5);
				ListPointers[newindex]=(char **) malloc(4*(newNElem+5));
				cDelmiterArray[newindex]=cDelmiterArray[index1];
				{
					char *posDest=cListArray[newindex];
					char **tmpposDest=ListPointers[newindex];
					unsigned long NElem=0;
					c1=0,c2=0;
					while(c1<nElem1)
					{
						long flgUNI=0;
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


unsigned long LoadList(char *iName)
{
	unsigned long ret=-1;
	long chtr=0;
	unsigned long retCreate;
	char nm[250];
	FILE *src=NULL;


printf("executing LoadList with: %s\n",iName);
	sprintf(nm,"%s/%s%s",ListsPath,IdPort,iName);
	while(src==NULL && (++chtr)<3)
	{
		src=fopen(nm,"rb");
printf("open file: %s \n",nm);
		if (src!=NULL)
		{
			unsigned long iIndex;
			if (m_Echo!=0) printf("#%s# -OK\n",nm);
printf("Trying to create list: \"%s\" \n",iName);
			retCreate=CreateList(iName);
printf("List create: %s \n",iName);
			iIndex=GetListIndex(iName);
printf("Info for lists:%d,%d,%s \n",iIndex,nLists,iName);
			if (iIndex<nLists)
			{
				unsigned long nElem=0;
				unsigned char *pos;
printf("List create \n");
				if (cListArray[iIndex]!=NULL) free(cListArray[iIndex]);
				cListArray[iIndex]=NULL;
				if (ListPointers[iIndex]!=NULL) free(ListPointers[iIndex]);
				ListPointers[iIndex]=NULL;
				unListsState[iIndex]=0;
				unListsElements[iIndex]=0;
				unListsLength[iIndex]=0;
				cDelmiterArray[iIndex]=10;
				fseek(src,0,SEEK_END);
				unListsLength[iIndex]=ftell(src);
				cListArray[iIndex]=(char *) malloc(unListsLength[iIndex]+5);
				rewind(src);
				pos=cListArray[iIndex];
				fread( cListArray[iIndex],1,unListsLength[iIndex], src);
 				cListArray[iIndex][unListsLength[iIndex]]=0;
     
				while((*pos)!=0)
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
					unsigned char *posDest;
					nElem++;
					ret=unListsElements[iIndex]=nElem;
					ListPointers[iIndex]=(char **) malloc((nElem+5)*sizeof(char *));

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
		else
		{
			sleep(1);
		}
	}

	if (src==NULL)
	{
		unsigned long iIndex;
		if (m_Echo!=0) printf("#%s# - FAIL\n",nm);
		CreateList(iName);
			iIndex=GetListIndex(iName);
			if (iIndex<nLists)
			{
				unsigned long nElem=0;
				char *pos;
				if (cListArray[iIndex]!=NULL) free(cListArray[iIndex]);
				cListArray[iIndex]=NULL;
				if (ListPointers[iIndex]!=NULL) free(ListPointers[iIndex]);
				ListPointers[iIndex]=NULL;
				unListsState[iIndex]=0;
				unListsElements[iIndex]=0;
				unListsLength[iIndex]=0;
				cDelmiterArray[iIndex]=10;
				cListArray[iIndex]=(char *) malloc(5);
 				cListArray[iIndex][unListsLength[iIndex]]=0;
				ListPointers[iIndex]=(char **) malloc(5*sizeof(char *));
			}
	}

	return ret;
}

long SaveList(char *nmlist, char *nmFile)
{
	FILE *dst;
	char fName[500];
	printf("executing SaveList \n");
	sprintf(fName,"%s/%s%s",ListsPath,IdPort,nmFile);
	/*dst=fopen(fName,"wb"); */
	dst=fopen(fName,"w+");
	printf("\n",fName,"\n");
	if (dst!=NULL)
	{
		unsigned long iIndex;
		if (m_Echo!=0) printf("#%s# -OK\n",fName);
		iIndex=GetListIndex(nmlist);
		if (iIndex<nLists && unListsElements[iIndex]>0 && ListPointers[iIndex]!=NULL)
		{
			unsigned long nItem=unListsElements[iIndex];
			unsigned long i=0;
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

long DoMethod(char *iStr, char **oStr)
{
	char met[50];
	char *pos;
	long nfunc=0;
	long retint=-123456; 
	long atoipos;
	unsigned long uNMethods=25;
	char *cArrMethods[25]={
			"XORLISTS","ANDLISTS","NOTLISTS","ORLISTS","SQUISELIST",
			"DUPLICATELIST","UNIQUELIST","SORTLIST","ADDLIST","APPENDLIST",
			"SETLISTDELIMITER","SETLIST","LOADLIST","CREATELIST","DELETELIST",
			"SAVELIST","CONTEXTLISTS","MASKLISTS","NOTMASKLISTS","NOTCONTEXTLISTS",
			"BEGINCONTEXTLISTS","NOTBEGINCONTEXTLISTS","ENDCONTEXTLISTS","NOTENDCONTEXTLISTS","ECHO",
	};

	strncpy(met,iStr,45);met[45]=0;
	pos=met;
	while(*pos!=0 && *pos!=' ')
		*(pos++)&=0xDF;

	pos=strchr(met,' ');
	if (pos==NULL) pos=iStr+strlen(iStr);
	else	
	{
		*(pos++)=0;
		pos=strchr(iStr,' ');
		pos++;
	}

	atoipos=atoi(pos);
	
	for(nfunc=0;nfunc<uNMethods && strcmp(met,cArrMethods[nfunc])!=0;nfunc++); 

	printf("%d,%s\n",nfunc,cArrMethods[nfunc]);

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
