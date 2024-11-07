// GP_QSort.h: interface for the GP_QSort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GP_QSORT_H__1D876523_16F8_11D4_970D_0080AD863699__INCLUDED_)
#define AFX_GP_QSORT_H__1D876523_16F8_11D4_970D_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


template <class GP_QSort> void GP_quick(GP_QSort *Item, int Count)
{
    qs(Item,0,Count-1);
}
template <class GP_QSort> void qs(GP_QSort *Item, int left, int right)
{
	register int i,j;
	GP_QSort x,y;

	i=left;
	j=right;
	x=Item[(left+right)/2];

	do
	{
		while(Item[i]<x && i<right) i++;
		while(x<Item[j] && j>left) j--;

		if (i<=j)
		{
			y=Item[i];			Item[i]=Item[j];			Item[j]=y;
			i++;				j--;
		}
	}while(i<=j);
	if(left<j) qs(Item,left,j);
	if (i<right) qs(Item,i,right);
}


template <class GP_QSort2, class GP_QSortSlave> void GP_quick2(GP_QSort2 *Item, GP_QSortSlave *ItemSlave, int Count)
{
    qs2(Item,ItemSlave,0,Count-1);
}
template <class GP_QSort2, class GP_QSortSlave> void qs2(GP_QSort2 *Item, GP_QSortSlave *ItemSlave, int left, int right)
{
	register int i,j;
	GP_QSort2 x,y;
	GP_QSortSlave tmp;

	i=left;
	j=right;
	x=Item[(left+right)/2];

	do
	{
		while(Item[i]<x && i<right) i++;
		while(x<Item[j] && j>left) j--;

		if (i<=j)
		{
			y=Item[i];			Item[i]=Item[j];			Item[j]=y;
			tmp=ItemSlave[i];	ItemSlave[i]=ItemSlave[j];	ItemSlave[j]=tmp;
			i++;				j--;
		}
	}while(i<=j);
	if(left<j) qs2(Item,ItemSlave,left,j);
	if (i<right) qs2(Item,ItemSlave,i,right);
}



template <class GP_QSort2_4_1, class GP_QSort2_4_2, class GP_QSort2_4_3, class GP_QSort2_4_4 > void GP_quick2_4(GP_QSort2_4_1 *Item1, GP_QSort2_4_2 *Item2, GP_QSort2_4_3 *Item3, GP_QSort2_4_4 *Item4, int Count)
{
    qs2_4(Item1,Item2,Item3,Item4,0,Count-1);
}
template <class GP_QSort2_4_1, class GP_QSort2_4_2, class GP_QSort2_4_3, class GP_QSort2_4_4 > void qs2_4(GP_QSort2_4_1 *Item1, GP_QSort2_4_2 *Item2, GP_QSort2_4_3 *Item3, GP_QSort2_4_4 *Item4, int left, int right)
{


	register int i,j;
	GP_QSort2_4_1 x1,y1;
	GP_QSort2_4_2 x2,y2;
	GP_QSort2_4_3 y3;
	GP_QSort2_4_4 y4;

	i=left;
	j=right;
	x1=Item1[(left+right)/2];
	x2=Item2[(left+right)/2];

	do
	{
		while((Item1[i]<x1 || (Item1[i]==x1 && Item2[i]<x2)) && i<right) i++;
		while((x1<Item1[j] || (x1==Item1[j] && x2<Item2[j])) && j>left) j--;

		if (i<=j)
		{
			y1=Item1[i];			Item1[i]=Item1[j];			Item1[j]=y1;
			y2=Item2[i];			Item2[i]=Item2[j];			Item2[j]=y2;
			y3=Item3[i];			Item3[i]=Item3[j];			Item3[j]=y3;
			y4=Item4[i];			Item4[i]=Item4[j];			Item4[j]=y4;
			i++;				j--;
		}
	}while(i<=j);

	if(left<j) qs2_4(Item1,Item2,Item3,Item4,left,j);
	if (i<right) qs2_4(Item1,Item2,Item3,Item4,i,right);
}


template <class GP_QSortSlave> void GP_quick2CL(char **Item, GP_QSortSlave *ItemSlave, int Count)
{
    qs2CL(Item,ItemSlave,0,Count-1);
}

template <class GP_QSort2, class GP_QSortSlave> void qs2CL(char **Item, GP_QSortSlave *ItemSlave, int left, int right)
{
	register int i,j;
	char *x,*y;
	GP_QSortSlave tmp;

	i=left;
	j=right;
	x=Item[(left+right)/2];

	do
	{
		while(strcmp(Item[i],x)<0 && i<right) i++;
		while(strcmp(x,Item[j])<0 && j>left) j--;

		if (i<=j)
		{
			y=Item[i];			Item[i]=Item[j];			Item[j]=y;
			tmp=ItemSlave[i];	ItemSlave[i]=ItemSlave[j];	ItemSlave[j]=tmp;
			i++;				j--;
		}
	}while(i<=j);
	if(left<j) qs2CL(Item,ItemSlave,left,j);
	if (i<right) qs2CL(Item,ItemSlave,i,right);
}

template <class GP_QSortSlave> void GP_quick2ICL(char **Item, GP_QSortSlave *ItemSlave, int Count)
{
    qs2ICL(Item,ItemSlave,0,Count-1);
}

template <class GP_QSortSlave> void qs2ICL(char **Item, GP_QSortSlave *ItemSlave, int left, int right)
{
	register int i,j;
	char *x,*y;
	GP_QSortSlave tmp;

	i=left;
	j=right;
	x=Item[(left+right)/2];

	do
	{
		while(_stricmp(Item[i],x)<0 && i<right) i++;
		while(_stricmp(x,Item[j])<0 && j>left) j--;

		if (i<=j)
		{
			y=Item[i];			Item[i]=Item[j];			Item[j]=y;
			tmp=ItemSlave[i];	ItemSlave[i]=ItemSlave[j];	ItemSlave[j]=tmp;
			i++;				j--;
		}
	}while(i<=j);
	if(left<j) qs2ICL(Item,ItemSlave,left,j);
	if (i<right) qs2ICL(Item,ItemSlave,i,right);
}



template <class GP_QSortSlave> void GP_quick2IBSTR(BSTR *Item, GP_QSortSlave *ItemSlave, int Count)
{
    qs2IBSTR(Item,ItemSlave,0,Count-1);
}

template <class GP_QSortSlave> void qs2IBSTR(BSTR *Item, GP_QSortSlave *ItemSlave, int left, int right)
{
	USES_CONVERSION;
	register int i,j;
	BSTR x,y;
	GP_QSortSlave tmp;

	i=left;
	j=right;
	x=Item[(left+right)/2];

	do
	{
		while(_wcsicmp(Item[i],x)<0 && i<right) i++;
		while(_wcsicmp(x,Item[j])<0 && j>left) j--;

		if (i<=j)
		{
			y=Item[i];			Item[i]=Item[j];			Item[j]=y;
			tmp=ItemSlave[i];	ItemSlave[i]=ItemSlave[j];	ItemSlave[j]=tmp;
			i++;				j--;
		}
	}while(i<=j);
	if(left<j) qs2IBSTR(Item,ItemSlave,left,j);
	if (i<right) qs2IBSTR(Item,ItemSlave,i,right);
}



template <class GP_QSortSlave> void GP_quick2BSTR(BSTR *Item, GP_QSortSlave *ItemSlave, int Count)
{
    qs2BSTR(Item,ItemSlave,0,Count-1);
}

template <class GP_QSortSlave> void qs2BSTR(BSTR *Item, GP_QSortSlave *ItemSlave, int left, int right)
{
	USES_CONVERSION;
	register int i,j;
	BSTR x,y;
	GP_QSortSlave tmp;

	i=left;
	j=right;
	x=Item[(left+right)/2];

	do
	{
		while(wcscmp(Item[i],x)<0 && i<right) i++;
		while(wcscmp(x,Item[j])<0 && j>left) j--;

		if (i<=j)
		{
			y=Item[i];			Item[i]=Item[j];			Item[j]=y;
			tmp=ItemSlave[i];	ItemSlave[i]=ItemSlave[j];	ItemSlave[j]=tmp;
			i++;				j--;
		}
	}while(i<=j);
	if(left<j) qs2BSTR(Item,ItemSlave,left,j);
	if (i<right) qs2BSTR(Item,ItemSlave,i,right);
}


template <class GP_RevArr> void GP_Reverse(GP_RevArr *Item, int Count)
{
	register int i,n=Count/2;
	GP_RevArr x;
	Count--;
	for(i=0;i<n;i++)
	{
		x=Item[i];	Item[i]=Item[Count-i];	Item[Count-i]=x;
	}
}





template <class GP_QSortSlave> void GP_quick2VARIANT(VARIANT *Item, GP_QSortSlave *ItemSlave, int Count)
{
    qs2VARIANT(Item,ItemSlave,0,Count-1);
}

template <class GP_QSortSlave> void qs2VARIANT(VARIANT *Item, GP_QSortSlave *ItemSlave, int left, int right)
{
	USES_CONVERSION;
	register int i,j;
	VARIANT x,y;
	GP_QSortSlave tmp;

	i=left;
	j=right;
	x=Item[(left+right)/2];

	if (V_VT(Item)==VT_BSTR)
	{
		do
		{
			while(wcscmp(Item[i].bstrVal,x.bstrVal)<0 && i<right) i++;
			while(wcscmp(x.bstrVal,Item[j].bstrVal)<0 && j>left) j--;

			if (i<=j)
			{
				y=Item[i];			Item[i]=Item[j];			Item[j]=y;
				tmp=ItemSlave[i];	ItemSlave[i]=ItemSlave[j];	ItemSlave[j]=tmp;
				i++;j--;
			}
		}while(i<=j);
	}
	else
	{
		do
		{
			while(Item[i].dblVal<x.dblVal && i<right) i++;
			while(x.dblVal<Item[j].dblVal && j>left) j--;

			if (i<=j)
			{
				y=Item[i];			Item[i]=Item[j];			Item[j]=y;
				tmp=ItemSlave[i];	ItemSlave[i]=ItemSlave[j];	ItemSlave[j]=tmp;
				i++;j--;
			}
		}while(i<=j);
	}

	if(left<j) qs2VARIANT(Item,ItemSlave,left,j);
	if (i<right) qs2VARIANT(Item,ItemSlave,i,right);
}



template <class GP_QSortSlave> void GP_quick2VARIANTI(VARIANT *Item, GP_QSortSlave *ItemSlave, int Count)
{
    qs2VARIANTI(Item,ItemSlave,0,Count-1);
}

template <class GP_QSortSlave> void qs2VARIANTI(VARIANT *Item, GP_QSortSlave *ItemSlave, int left, int right)
{
	USES_CONVERSION;
	register int i,j;
	VARIANT x,y;
	GP_QSortSlave tmp;

	i=left;
	j=right;
	x=Item[(left+right)/2];

	if (V_VT(Item)==VT_BSTR)
	{
		do
		{
			while(_wcsicmp(Item[i].bstrVal,x.bstrVal)<0 && i<right) i++;
			while(_wcsicmp(x.bstrVal,Item[j].bstrVal)<0 && j>left) j--;

			if (i<=j)
			{
				y=Item[i];			Item[i]=Item[j];			Item[j]=y;
				tmp=ItemSlave[i];	ItemSlave[i]=ItemSlave[j];	ItemSlave[j]=tmp;
				i++;j--;
			}
		}while(i<=j);
	}
	else
	{
		do
		{
			while(Item[i].dblVal<x.dblVal && i<right) i++;
			while(x.dblVal<Item[j].dblVal && j>left) j--;

			if (i<=j)
			{
				y=Item[i];			Item[i]=Item[j];			Item[j]=y;
				tmp=ItemSlave[i];	ItemSlave[i]=ItemSlave[j];	ItemSlave[j]=tmp;
				i++;j--;
			}
		}while(i<=j);
	}

	if(left<j) qs2VARIANTI(Item,ItemSlave,left,j);
	if (i<right) qs2VARIANTI(Item,ItemSlave,i,right);
}







#endif // !defined(AFX_GP_QSORT_H__1D876523_16F8_11D4_970D_0080AD863699__INCLUDED_)
