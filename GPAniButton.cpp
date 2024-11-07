// GPAniButton.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPAniButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ANIBUTTON_TIMER_ID   102
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const UINT GPAniButton::uNMethods=13;
const char *GPAniButton::cArrMethods[]={
		"SetBitmap","SetIcon","SetImageList","SetDisableImageList","SetHotImageList",
		"Play","SetDefDuration","SetDuration","SetDisableDuration","SetHotDuration",
		"SetSequence","SetDisableSequence","SetHotSequence","","",
		"","","", "", "", 
	};
const char *GPAniButton::cArrMethodsParams[]={
		"Not Present","Not Present","ImageListName","ImageListName","ImageListName",
		"iDirection, iDisDirection, iHotDirection","uDefDuration","uDur1,uDur2,...,uDurN","uDur1,uDur2,...,uDurN","uDur1,uDur2,...,uDurN",
		"nSeq1,nSeq2,...,nSeqN","nSeq1,nSeq2,...,nSeqN","nSeq1,nSeq2,...,nSeqN","","",
		"","","", "", "", 
	};





GPAniButton::GPAniButton(UINT iUnitId):GPButton(iUnitId)
{
	iDirection=1;
	iDisDirection=1;
	iHotDirection=1;
	uCurPos=0;
	uCurDisPos=0;
	uCurHotPos=0;
	uArrDuration=NULL;
	uArrDisDuration=NULL;
	uArrHotDuration=NULL;
	uArrSeq=NULL;
	uArrDisSeq=NULL;
	uArrHotSeq=NULL;
	uNFrame=0;
	uDisNFrame=0;
	uHotNFrame=0;
	uDefDuration=250;
	uNSeq=0;
	uDisNSeq=0;
	uHotNSeq=0;
	uNDuration=0;
	uDisNDuration=0;
	uHotNDuration=0;
	tmpHICON=NULL;
}

GPAniButton::~GPAniButton()
{
	if (tmpHICON!=NULL) DestroyIcon(tmpHICON);
	if (uArrDuration!=NULL) delete[] uArrDuration;
	if (uArrDisDuration!=NULL) delete[] uArrDisDuration;
	if (uArrHotDuration!=NULL) delete[] uArrHotDuration;
	if (uArrSeq!=NULL) delete[] uArrSeq;
	if (uArrDisSeq!=NULL) delete[] uArrDisSeq;
	if (uArrHotSeq!=NULL) delete[] uArrHotSeq;
	uArrDuration=NULL;
	uArrDisDuration=NULL;
	uArrHotDuration=NULL;
	uArrSeq=NULL;
	uArrDisSeq=NULL;
	uArrHotSeq=NULL;
}

BEGIN_MESSAGE_MAP(GPAniButton, GPButton)
	//{{AFX_MSG_MAP(GPAniButton)
	ON_WM_TIMER()
	ON_WM_NCHITTEST()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void GPAniButton::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==ANIBUTTON_TIMER_ID)
	{
		KillTimer(ANIBUTTON_TIMER_ID);
		UINT nFr=0;
		UINT nDur=uDefDuration;

		if (IsWindowEnabled() || uDisNFrame==0)
		{
			if ((GetState()&0x0007)!=0 || uNFrame==0) /*Press | Hot*/
			{
				if (uArrHotSeq!=NULL)
				{
					if (uCurHotPos>=uHotNSeq) uCurHotPos=0;
					nFr=uArrHotSeq[uCurHotPos];
					if (nFr>=uHotNFrame) nFr=0;
				}
				else	if ((nFr=uCurHotPos)>=uHotNFrame) uCurHotPos=nFr=0;

				if (uArrHotDuration!=NULL && uCurHotPos<uHotNDuration) nDur=uArrHotDuration[uCurHotPos];

				if (uHotNFrame>0)
					DestroyIcon(SetIcon(tmpHICON=(HICON)	HotIL.m_IL.ExtractIcon(nFr)));
				uCurHotPos+=iHotDirection;

				if (iHotDirection<0 && uCurHotPos>0xFFFFFF)
				{
					if (uHotNSeq>0)	uCurHotPos+=uHotNSeq;
					else			uCurHotPos+=uHotNFrame;
				}
			}
			else /*Not Press & Not Hot*/
			{
				if (uArrSeq!=NULL)
				{
					if (uCurPos>=uNSeq) uCurPos=0;
					nFr=uArrSeq[uCurPos];
					if (nFr>=uNFrame) nFr=0;
				}
				else	if ((nFr=uCurPos)>=uNFrame) uCurPos=nFr=0;

				if (uArrDuration!=NULL && uCurPos<uNDuration) nDur=uArrDuration[uCurPos];

				if (uNFrame>0)
					DestroyIcon(SetIcon(tmpHICON=(HICON)NormalIL.m_IL.ExtractIcon(nFr)));

				uCurPos+=iDirection;
				if (iDirection<0 && uCurPos>0xFFFFFF)
				{
					if (uNSeq>0)	uCurPos+=uNSeq;
					else			uCurPos+=uNFrame;
				}
			}
		}
		else /*Disabled*/
		{
			if (uArrDisSeq!=NULL)
			{
				if (uCurDisPos>=uDisNSeq) uCurDisPos=0;
				nFr=uArrDisSeq[uCurDisPos];
				if (nFr>=uDisNFrame) nFr=0;
			}
			else	if ((nFr=uCurDisPos)>=uDisNFrame) uCurDisPos=nFr=0;

			if (uArrDisDuration!=NULL && uCurDisPos<uDisNDuration) nDur=uArrDisDuration[uCurDisPos];

			if (uDisNFrame>0)
				DestroyIcon(SetIcon(tmpHICON=(HICON)DisableIL.m_IL.ExtractIcon(nFr)));
			uCurDisPos+=iDisDirection;
			if (iDisDirection<0 && uCurDisPos>0xFFFFFF)
				uCurDisPos=uCurDisPos+uDisNSeq;

			if (iHotDirection<0 && uCurHotPos>0xFFFFFF)
			{
				if (uDisNSeq>0)	uCurDisPos+=uDisNSeq;
				else			uCurDisPos+=uDisNFrame;
			}
		}

		SetTimer(ANIBUTTON_TIMER_ID,nDur,0);
	}
	else GPButton::OnTimer(nIDEvent);
}

UINT GPAniButton::DoMethod(const char *iStr, char *oStr)
{
	char met[150];
	strncpy(met,iStr,145);
	met[145]=0;
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc=0;

	if (*met>='0' && *met<='9') nfunc=atoi(met);
	else
	{
		static const char *sccArrMethods[sizeof(cArrMethods)/sizeof(char *)];
		static DWORD scdMethodsId[sizeof(cArrMethods)/sizeof(char *)];
		if (!*sccArrMethods)
		{
			DWORD i;
			for(i=0;i<uNMethods;i++)
			{
				sccArrMethods[i]=cArrMethods[i];
				scdMethodsId[i]=i;
			}
			qsCharILineAndDWORD(sccArrMethods, scdMethodsId, 0, uNMethods-1);
			scdMethodsId[i]=i;
		}
		nfunc=scdMethodsId[FindInSortArrayIC(met, sccArrMethods, uNMethods)];
		if (nfunc<uNMethods) nfunc+=100;
	}


	switch(nfunc)
	{
	case 100:	/*SetBitmap заглушка для BUTTON*/		break;
	case 101:	/*SetIcon заглушка для BUTTON*/			break;
	case 102:	/*SetImageList*/
		{
			int nIm=GPC.GetImageListId(pos);
			uDisNFrame=0;
			if (nIm>=0)	NormalIL=GPC.a_GPImageList[nIm];
			else		nIm=-1+NormalIL.LoadList(pos);
			if (nIm>=0)	uNFrame=NormalIL.m_IL.GetImageCount();
			uCurPos=0;
		}
		break;
	case 103:	/*SetDisableImageList*/
		{
			int nIm=GPC.GetImageListId(pos);
			uDisNFrame=0;
			if (nIm>=0)	DisableIL=GPC.a_GPImageList[nIm];
			else		nIm=-1+DisableIL.LoadList(pos);
			if (nIm>=0)	uDisNFrame=DisableIL.m_IL.GetImageCount();
			uCurDisPos=0;
		}
		break;
	case 104:	/*SetHotImageList*/
		{
			int nIm=GPC.GetImageListId(pos);
			uHotNFrame=0;
			if (nIm>=0)	HotIL=GPC.a_GPImageList[nIm];
			else		nIm=-1+HotIL.LoadList(pos);
			if (nIm>=0)	uHotNFrame=HotIL.m_IL.GetImageCount();
			uCurHotPos=0;
		}
		break;
	case 105:	/*Play*/
		{
			iDirection=iDisDirection=iHotDirection=1;
			m_LastScanf=sscanf(pos,"%d,%d,%d",&iDirection,&iDisDirection,&iHotDirection);
			KillTimer(ANIBUTTON_TIMER_ID);
			ModifyStyle(BS_BITMAP,BS_ICON);
			if (iDirection!=0)	SetTimer(ANIBUTTON_TIMER_ID,5,0);
		}
		break;
	case 106:	/*SetDefDuration*/	if ((uDefDuration=atoi(pos))<40) uDefDuration=40;	break;
	case 107:	/*SetDuration*/
		{
			const char *pos2=pos;
			uNDuration=0;
			if (uArrDuration!=NULL) delete[] uArrDuration;
			uArrDuration=new UINT [(int)strlen(pos)+2];
			while(pos2!=NULL)
			{
				uArrDuration[uNDuration]=atoi(pos2);
				if (uArrDuration[uNDuration]<40) uArrDuration[uNDuration]=40;
				if (uArrDuration[uNDuration]>30000) uArrDuration[uNDuration]=1000;
				uNDuration++;
				pos2=strchr(pos2,',');
				if (pos2!=NULL) pos2++;
			}
		}
		break;
	case 108:	/*SetDisableDuration*/
		{
			const char *pos2=pos;
			uDisNDuration=0;
			if (uArrDisDuration!=NULL) delete[] uArrDisDuration;
			uArrDisDuration=new UINT [(int)strlen(pos)+2];
			while(pos2!=NULL)
			{
				uArrDisDuration[uDisNDuration]=atoi(pos2);
				if (uArrDisDuration[uDisNDuration]<40) uArrDisDuration[uDisNDuration]=40;
				if (uArrDisDuration[uDisNDuration]>30000) uArrDisDuration[uDisNDuration]=1000;
				uDisNDuration++;
				pos2=strchr(pos2,',');
				if (pos2!=NULL) pos2++;
			}
		}
		break;
	case 109:	/*SetHotDuration*/
		{
			const char *pos2=pos;
			uHotNDuration=0;
			if (uArrHotDuration!=NULL) delete[] uArrHotDuration;
			uArrHotDuration=new UINT [(int)strlen(pos)+2];
			while(pos2!=NULL)
			{
				uArrHotDuration[uHotNDuration]=atoi(pos2);
				if (uArrHotDuration[uHotNDuration]<40) uArrHotDuration[uHotNDuration]=40;
				if (uArrHotDuration[uHotNDuration]<30000) uArrHotDuration[uHotNDuration]=1000;
				uHotNDuration++;
				pos2=strchr(pos2,',');
				if (pos2!=NULL) pos2++;
			}
		}
		break;
	case 110:/*SetSequence*/
		{
			const char *pos2=pos;
			uNSeq=0;
			if (uArrSeq!=NULL) delete[] uArrSeq;
			uArrSeq=new UINT [(int)strlen(pos)+2];
			while(pos2!=NULL)
			{
				uArrSeq[uNSeq]=atoi(pos2);
				if (uArrSeq[uNSeq]>uNFrame) uArrSeq[uNSeq]=0;
				uNSeq++;
				pos2=strchr(pos2,',');
				if (pos2!=NULL) pos2++;
			}
		}
		break;
	case 111:/*SetDisableSequence*/
		{
			const char *pos2=pos;
			uDisNSeq=0;
			if (uArrDisSeq!=NULL) delete[] uArrDisSeq;
			uArrDisSeq=new UINT [(int)strlen(pos)+2];
			while(pos2!=NULL)
			{
				uArrDisSeq[uDisNSeq]=atoi(pos2);
				if (uArrDisSeq[uDisNSeq]>uDisNFrame) uArrDisSeq[uDisNSeq]=0;
				uDisNSeq++;
				pos2=strchr(pos2,',');
				if (pos2!=NULL) pos2++;
			}
		}
		break;
	case 112:/*SetHotSequence*/
		{
			const char *pos2=pos;
			uHotNSeq=0;
			if (uArrHotSeq!=NULL) delete[] uArrHotSeq;
			uArrHotSeq=new UINT [(int)strlen(pos)+2];
			while(pos2!=NULL)
			{
				uArrHotSeq[uHotNSeq]=atoi(pos2);
				if (uArrHotSeq[uHotNSeq]>uHotNFrame) uArrHotSeq[uHotNSeq]=0;
				uHotNSeq++;
				pos2=strchr(pos2,',');
				if (pos2!=NULL) pos2++;
			}
		}
		break;
	default: nfunc=GPButton::DoMethod(iStr,oStr);break;
	}
	return nfunc;
}


HBRUSH GPAniButton::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = GPButton::OnCtlColor(pDC, pWnd, nCtlColor);
	
	return hbr;
}
