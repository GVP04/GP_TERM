// GPTextArray.cpp: implementation of the GPTextArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GP_term.h"
#include "GPTextArray.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPTextArray::GPTextArray()
{
	CharArray=NULL;
	ItemData=NULL;
	nItems=0;
}

GPTextArray::GPTextArray(UINT n)
{
	CharArray=NULL;
	ItemData=NULL;
	nItems=0;
	if (n>0)
	{
		nItems=n;
		CharArray=new char * [n];
		if (CharArray==NULL)	nItems=0;
		ItemData=new DWORD [n];
		UINT i;
		for(i=0;i<nItems;i++)
		{
			ItemData[i]=0;
			CharArray[i]=NULL;
		}
	}
}


GPTextArray::~GPTextArray()
{
	ClearAll();
	if (CharArray!=NULL) delete[] CharArray;
	if (ItemData!=NULL) delete[] ItemData;
}

char * GPTextArray::AddItem(char *NewItem)
{
	return InsertItem(nItems,NewItem);
}

char * GPTextArray::InsertItem(UINT ItemNumber, const char *NewItem)
{
	char *ret=NULL;
	if (ItemNumber<1000000)
	{
		UINT newNItems=nItems+1;
		if (newNItems<=ItemNumber) newNItems=ItemNumber+1;

		DWORD *newIData=new DWORD [newNItems];
		if (newIData!=NULL)
		{
			UINT i;
			if (ItemData==NULL)		for(i=0; i<newNItems; i++) newIData[i]=0;
			else
				for(i=0; i<newNItems; i++)
					if (i<nItems && i<ItemNumber) newIData[i]=ItemData[i];
						else if (i<nItems && i>ItemNumber) newIData[i]=ItemData[i-1];
							else if (i>=nItems && i!=ItemNumber) newIData[i]=0;
								else	newIData[i]=0;

			if (ItemData!=NULL)	delete[] ItemData;
			ItemData=newIData;
		}

		char **newArray=new char * [newNItems];
		if (newArray!=NULL)
		{
			UINT i;
			if (CharArray==NULL)
			{
				for(i=0; i<newNItems; i++) newArray[i]=NULL;

				if (NewItem==NULL) newArray[ItemNumber]=NULL;
				else
				{
					newArray[ItemNumber]=new char [(int)strlen(NewItem)+2];
					strcpy(ret=newArray[ItemNumber],NewItem);
				}
			}
			else
				for(i=0; i<newNItems; i++)
					if (i<nItems && i<ItemNumber) newArray[i]=CharArray[i];
						else if (i<nItems && i>ItemNumber) newArray[i]=CharArray[i-1];
							else if (i>=nItems && i!=ItemNumber) newArray[i]=NULL;
								else
								{
									if (NewItem==NULL) newArray[ItemNumber]=NULL;
									else
									{
										newArray[i]=new char [(int)strlen(NewItem)+2];
										strcpy(ret=newArray[i],NewItem);
									}
								}

			nItems=newNItems;
			if (CharArray!=NULL)	delete[] CharArray;
			CharArray=newArray;
		}

	}

	return ret;
}

BOOL GPTextArray::DeleteItem(UINT ItemNumber)
{
	BOOL ret=FALSE;
	if (ItemNumber<nItems)
	{
		UINT i;
		if (CharArray!=NULL)
		{
			if (CharArray[ItemNumber]!=NULL) delete[] CharArray[ItemNumber];
			CharArray[ItemNumber]=NULL;
			for(i=ItemNumber+1; i<nItems; i++) CharArray[i-1]=CharArray[i];
		}

		if (ItemData!=NULL)
			for(i=ItemNumber+1; i<nItems; i++) ItemData[i-1]=ItemData[i];

		nItems--;
	}
	return ret;
}


UINT GPTextArray::GetItemCount()	{ return nItems;}

int GPTextArray::CompareItems(UINT num1, UINT num2, UINT Type)
{
	if (CharArray==NULL) return 0;
	if (num1>=nItems && num2<nItems) return -1;
	if (num2>=nItems && num1<nItems) return 1;
	if (num1>=nItems && num2>=nItems) return num1-num2;

	if (CharArray[num1]==NULL && CharArray[num2]!=NULL) return -1;
	if (CharArray[num2]==NULL && CharArray[num1]!=NULL) return 1;
	if (CharArray[num1]==NULL && CharArray[num2]==NULL) return num1-num2;


	switch(Type)
	{
	case GPTAC_STRING: return strcmp(CharArray[num1],CharArray[num2]);
	case GPTAC_NUMERIC: return atoi(CharArray[num1])-atoi(CharArray[num2]);
	}

	return 0;
}

char * GPTextArray::SetItem(UINT ItemNumber, const char *NewValue)
{

	if (ItemNumber>=nItems || CharArray==NULL) return InsertItem(ItemNumber, NewValue);
	if (CharArray[ItemNumber]!=NULL) delete[] CharArray[ItemNumber];

	if (NewValue==NULL) CharArray[ItemNumber]=NULL;
	else
	{
		CharArray[ItemNumber]=new char [(int)strlen(NewValue)+2];
		strcpy(CharArray[ItemNumber],NewValue);
	}

	return CharArray[ItemNumber];
}


void GPTextArray::ClearAll()
{
	UINT i;
	if (CharArray!=NULL)
		for(i=0;i<nItems;i++) 
			if (CharArray[i]!=NULL) {delete[] CharArray[i];CharArray[i]=NULL;}

	if (ItemData!=NULL)
		for(i=0;i<nItems;i++) ItemData[i]=0;
}

void * GPTextArray::GetItem(UINT num)
{
	if (CharArray!=NULL && num<nItems) return CharArray[num];
	else return NULL;
}

BOOL GPTextArray::SetItemData(UINT nItem, DWORD iData)
{
	BOOL ret=TRUE;
	if (ItemData!=NULL && nItem<nItems) ItemData[nItem]=iData;
	else ret=FALSE;

	return ret;
}

DWORD GPTextArray::GetItemData(UINT nItem)
{
	return (ItemData!=NULL && nItem<nItems)?ItemData[nItem]:0;
}
