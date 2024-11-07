// GPWndPropertyArrayItem.cpp: implementation of the CGPWndPropertyArrayItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPWndPropertyArrayItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGPWndPropertyArrayItem::CGPWndPropertyArrayItem()
{
	GPPAITEM InitItem={0};
	ArrStyles.SetInitValue(InitItem);
}

CGPWndPropertyArrayItem::~CGPWndPropertyArrayItem()
{

}


void CGPWndPropertyArrayItem::SetOnStyles()
{
	int nSel=ArrStyles.SelectFirst();

	do
		if (nSel!=-1)
		{
			GPPAITEM *tmp=&ArrStyles[nSel];
			DWORD flg=0;

			if (tmp->OnAddStyle!=tmp->OnDelStyle && (tmp->OnAddStyle || tmp->OnDelStyle) && (tmp->OnAddStyle!=tmp->OffAddStyle || tmp->OnDelStyle!=tmp->OffDelStyle))
			{
			::SetWindowLong(
				(HWND)nSel,
				GWL_STYLE,
				(::GetWindowLong((HWND)nSel,GWL_STYLE)|tmp->OnAddStyle)&(0xFFFFFFFF^tmp->OnDelStyle)
				);
				flg++;
			}
			if (tmp->OnAddStyleEx!=tmp->OnDelStyleEx && (tmp->OnAddStyleEx || tmp->OnDelStyleEx) && (tmp->OnAddStyleEx!=tmp->OffAddStyleEx || tmp->OnDelStyleEx!=tmp->OffDelStyleEx))
			{
			::SetWindowLong(
				(HWND)nSel,
				GWL_EXSTYLE,
				(::GetWindowLong((HWND)nSel,GWL_EXSTYLE)|tmp->OnAddStyleEx)&(0xFFFFFFFF^tmp->OnDelStyleEx)
				);
				flg++;
			}
			if (flg)
			{
				RECT re={0};
				POINT po={0};
				::GetWindowRect((HWND)nSel,&re);
				HWND hp=::GetParent((HWND)nSel);
				if (hp)
				{
					::ScreenToClient((HWND)hp,&po);
					re.top+=po.y;
					re.bottom+=po.y;
					re.left+=po.x;
					re.right+=po.x;
					::RedrawWindow(hp,&re,NULL,RDW_ALLCHILDREN|RDW_ERASE|RDW_FRAME|RDW_INTERNALPAINT|RDW_INVALIDATE);
				}
			}
		}
	while((nSel=ArrStyles.SelectNext())!=0xFFFFFFFF);
}

void CGPWndPropertyArrayItem::SetOffStyles()
{
	int nSel=ArrStyles.SelectFirst();

	do
		if (nSel!=-1)
		{
			GPPAITEM *tmp=&ArrStyles[nSel];
			DWORD flg=0;

			if (tmp->OffAddStyle!=tmp->OffDelStyle && (tmp->OffAddStyle || tmp->OffDelStyle) && (tmp->OnAddStyle!=tmp->OffAddStyle || tmp->OnDelStyle!=tmp->OffDelStyle))
			{
				::SetWindowLong(
					(HWND)nSel,
					GWL_STYLE,
					(::GetWindowLong((HWND)nSel,GWL_STYLE)|tmp->OffAddStyle)&(0xFFFFFFFF^tmp->OffDelStyle)
					);
				flg++;
			}
			if (tmp->OffAddStyleEx!=tmp->OffDelStyleEx && (tmp->OffAddStyleEx || tmp->OffDelStyleEx) && (tmp->OnAddStyleEx!=tmp->OffAddStyleEx || tmp->OnDelStyleEx!=tmp->OffDelStyleEx))
			{
			::SetWindowLong(
				(HWND)nSel,
				GWL_EXSTYLE,
				(::GetWindowLong((HWND)nSel,GWL_EXSTYLE)|tmp->OffAddStyleEx)&(0xFFFFFFFF^tmp->OffDelStyleEx)
				);
				flg++;
			}
			if (flg)
			{
				RECT re={0};
				POINT po={0};
				::GetWindowRect((HWND)nSel,&re);
				HWND hp=::GetParent((HWND)nSel);
				::ScreenToClient((HWND)hp,&po);
				re.top+=po.y;
				re.bottom+=po.y;
				re.left+=po.x;
				re.right+=po.x;
				::RedrawWindow(hp,&re,NULL,RDW_ALLCHILDREN|RDW_ERASE|RDW_FRAME|RDW_INTERNALPAINT|RDW_INVALIDATE);
			}
		}
	while((nSel=ArrStyles.SelectNext())!=0xFFFFFFFF);
}


CGPWndPropertyArrayItem & CGPWndPropertyArrayItem::operator=(const CGPWndPropertyArrayItem &iGPPAI)
{
	if (&iGPPAI && &iGPPAI!=this)
	{
		ArrStyles.CopyArray(&iGPPAI.ArrStyles);
	}

	return *this;
}

GPPAITEM & CGPWndPropertyArrayItem::operator[](UINT nItem)
{
	return ArrStyles[nItem];
}

UINT CGPWndPropertyArrayItem::AddWnd(HWND iHWND, GPPAITEM & Styles)
{
	return SetWnd(iHWND, Styles);
}

UINT CGPWndPropertyArrayItem::DeleteWnd(HWND iHWND)
{
	ArrStyles.RemoveItem((UINT)iHWND==GPPAI_ALLWINDOWS?GPPAI_ALLWINDOWS:(UINT)iHWND);
	return ArrStyles.GetCount();
}

UINT CGPWndPropertyArrayItem::SetWnd(HWND iHWND, GPPAITEM & Styles)
{
	if ((UINT)iHWND==GPPAI_ALLWINDOWS) ArrStyles.SetArray(Styles);
	else					 	 ArrStyles[(UINT)iHWND]=Styles;
	return ArrStyles.GetCount();
}

UINT WndDelStyles(HWND iHWND, GPPAITEM & Styles);


UINT CGPWndPropertyArrayItem::WndAddStyles(HWND iHWND, GPPAITEM & Styles)
{
	if ((UINT)iHWND==GPPAI_ALLWINDOWS) 
	{
		int sel=ArrStyles.SelectFirst();
		while(sel>=0)
		{
			GPPAITEM *tmp=&ArrStyles[sel];

			tmp->OnAddStyle		|=	Styles.OnAddStyle;
			tmp->OnAddStyleEx	|=	Styles.OnAddStyleEx;
			tmp->OnDelStyle		|=	Styles.OnDelStyle;
			tmp->OnDelStyleEx	|=	Styles.OnDelStyleEx;
			tmp->OffAddStyle	|=	Styles.OffAddStyle;
			tmp->OffAddStyleEx	|=	Styles.OffAddStyleEx;
			tmp->OffDelStyle	|=	Styles.OffDelStyle;
			tmp->OffDelStyleEx	|=	Styles.OffDelStyleEx;
			sel=ArrStyles.SelectNext();
		}
	}
	else
	{
		GPPAITEM *tmp=&ArrStyles[(UINT)iHWND];

		tmp->OnAddStyle		|=	Styles.OnAddStyle;
		tmp->OnAddStyleEx	|=	Styles.OnAddStyleEx;
		tmp->OnDelStyle		|=	Styles.OnDelStyle;
		tmp->OnDelStyleEx	|=	Styles.OnDelStyleEx;
		tmp->OffAddStyle	|=	Styles.OffAddStyle;
		tmp->OffAddStyleEx	|=	Styles.OffAddStyleEx;
		tmp->OffDelStyle	|=	Styles.OffDelStyle;
		tmp->OffDelStyleEx	|=	Styles.OffDelStyleEx;
	}
	return ArrStyles.GetCount();
}

UINT CGPWndPropertyArrayItem::WndDelStyles(HWND iHWND, GPPAITEM & Styles)
{
	if ((UINT)iHWND==GPPAI_ALLWINDOWS) 
	{
		int sel=ArrStyles.SelectFirst();
		while(sel>=0)
		{
			GPPAITEM *tmp=&ArrStyles[sel];

			tmp->OnAddStyle		&=	(0xFFFFFFFF^Styles.OnAddStyle);
			tmp->OnAddStyleEx	&=	(0xFFFFFFFF^Styles.OnAddStyleEx);
			tmp->OnDelStyle		&=	(0xFFFFFFFF^Styles.OnDelStyle);
			tmp->OnDelStyleEx	&=	(0xFFFFFFFF^Styles.OnDelStyleEx);
			tmp->OffAddStyle	&=	(0xFFFFFFFF^Styles.OffAddStyle);
			tmp->OffAddStyleEx	&=	(0xFFFFFFFF^Styles.OffAddStyleEx);
			tmp->OffDelStyle	&=	(0xFFFFFFFF^Styles.OffDelStyle);
			tmp->OffDelStyleEx	&=	(0xFFFFFFFF^Styles.OffDelStyleEx);
			sel=ArrStyles.SelectNext();
		}
	}
	else
	{
		GPPAITEM *tmp=&ArrStyles[(UINT)iHWND];

		tmp->OnAddStyle		&=	(0xFFFFFFFF^Styles.OnAddStyle);
		tmp->OnAddStyleEx	&=	(0xFFFFFFFF^Styles.OnAddStyleEx);
		tmp->OnDelStyle		&=	(0xFFFFFFFF^Styles.OnDelStyle);
		tmp->OnDelStyleEx	&=	(0xFFFFFFFF^Styles.OnDelStyleEx);
		tmp->OffAddStyle	&=	(0xFFFFFFFF^Styles.OffAddStyle);
		tmp->OffAddStyleEx	&=	(0xFFFFFFFF^Styles.OffAddStyleEx);
		tmp->OffDelStyle	&=	(0xFFFFFFFF^Styles.OffDelStyle);
		tmp->OffDelStyleEx	&=	(0xFFFFFFFF^Styles.OffDelStyleEx);
	}
	return ArrStyles.GetCount();
}


UINT CGPWndPropertyArrayItem::WndClearStyles(HWND iHWND, GPPAITEM & Styles)
{
	if ((UINT)iHWND==GPPAI_ALLWINDOWS) 
	{
		int sel=ArrStyles.SelectFirst();
		while(sel>=0)
		{
			GPPAITEM *tmp=&ArrStyles[sel];

			if (Styles.OnAddStyle)		tmp->OnAddStyle		=0;
			if (Styles.OnAddStyleEx)	tmp->OnAddStyleEx	=0;
			if (Styles.OnDelStyle)		tmp->OnDelStyle		=0;
			if (Styles.OnDelStyleEx)	tmp->OnDelStyleEx	=0;
			if (Styles.OffAddStyle)		tmp->OffAddStyle	=0;
			if (Styles.OffAddStyleEx)	tmp->OffAddStyleEx	=0;
			if (Styles.OffDelStyle)		tmp->OffDelStyle	=0;
			if (Styles.OffDelStyleEx)	tmp->OffDelStyleEx	=0;
			sel=ArrStyles.SelectNext();
		}

	}
	else
	{
		GPPAITEM *tmp=&ArrStyles[(UINT)iHWND];

		if (Styles.OnAddStyle)		tmp->OnAddStyle		=0;
		if (Styles.OnAddStyleEx)	tmp->OnAddStyleEx	=0;
		if (Styles.OnDelStyle)		tmp->OnDelStyle		=0;
		if (Styles.OnDelStyleEx)	tmp->OnDelStyleEx	=0;
		if (Styles.OffAddStyle)		tmp->OffAddStyle	=0;
		if (Styles.OffAddStyleEx)	tmp->OffAddStyleEx	=0;
		if (Styles.OffDelStyle)		tmp->OffDelStyle	=0;
		if (Styles.OffDelStyleEx)	tmp->OffDelStyleEx	=0;
	}

	return ArrStyles.GetCount();
}

UINT CGPWndPropertyArrayItem::GetCount()
{
	return ArrStyles.GetCount();
}

