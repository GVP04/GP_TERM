// GP_QScroll.h: interface for the GP_QSort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GP_QSCROLL_H__1D876523_16F8_12D2_970D_0082AD863699__INCLUDED_)
#define AFX_GP_QSCROLL_H__1D876523_16F8_12D2_970D_0082AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


template <class GP_QScroll> void qscroll(GP_QScroll *Item, int nBegin, int nEnd, int nTime, UINT uEvery = 1)
{
	register int i,j;
	GP_QScroll tmp;


	if (nBegin<nEnd)
	{
		nEnd++;
		if (nTime<0) nTime+=nEnd-nBegin;
		if (nTime<0) nTime=nEnd-nBegin-1;

		if (nTime<=((nEnd-nBegin)/2))
		{
			for(i=0;i<nTime;i++)
			{
				tmp=Item[i*uEvery+nBegin];
				for(j=nBegin+(i+nTime)*uEvery;j<nEnd;j+=nTime*uEvery)
					Item[j-nTime*uEvery]=Item[j];
				Item[j-nTime*uEvery]=tmp;
			}
			if (((nEnd-nBegin)%(nTime*uEvery))!=0)
				qscroll(Item,nEnd-nTime*uEvery,nEnd-1,nTime-((nEnd-nBegin)%(nTime*uEvery))%nTime);
		}
		else
		{
			nTime=nEnd-nBegin-nTime;

			for(i=0;i<nTime;)
			{
				i++;
				tmp=Item[nEnd-i*uEvery];
				for(j=nEnd-(i+nTime)*uEvery;j<nEnd && j>=nBegin;j-=nTime*uEvery)
					Item[j+nTime*uEvery]=Item[j];
				Item[j+nTime*uEvery]=tmp;
			}
			if (((nEnd-nBegin)%(nTime*uEvery))!=0)
				qscroll(Item,nBegin,nBegin+nTime*uEvery-1,nTime-((nEnd-nBegin)%(nTime*uEvery))%nTime);

		}
	}
}


#endif // !defined(AFX_GP_QSCROLL_H__1D876523_16F8_12D2_970D_0082AD863699__INCLUDED_)
