// GPWndSizer.cpp: implementation of the CGPWndSizer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPWndSizer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const UINT CGPWndSizer::uNTypes=18;
const char *CGPWndSizer::cArrTypes[18]={
	"GPSS_TOP",		"GPSS_BOTTOM",	"GPSS_LEFT",	"GPSS_RIGHT",	"GPSS_TLEFT",
	"GPSS_TRIGHT",	"GPSS_BLEFT",	"GPSS_BRIGHT",	"GPSS_CENTER",	"GPSS_VERTICAL",
	"GPSS_HORISONTAL","GPSS_INVERT","GPSS_BRUSH",	"GPSS_INSIDE","GPSS_ROUND",
	"GPSS_SQUARE",	"GPSS_ICON",	"GPSS_MOVE",
	};

const UINT CGPWndSizer::uArrTypes[18]={
	GPSS_TOP,		GPSS_BOTTOM,	GPSS_LEFT,		GPSS_RIGHT,		GPSS_TLEFT,
	GPSS_TRIGHT,	GPSS_BLEFT,		GPSS_BRIGHT,	GPSS_CENTER,	GPSS_VERTICAL,
	GPSS_HORISONTAL,GPSS_INVERT,	GPSS_BRUSH,		GPSS_INSIDE,	GPSS_ROUND,
	GPSS_SQUARE,	GPSS_ICON,		GPSS_MOVE,
	};


BEGIN_MESSAGE_MAP(CGPWndSizer, CWnd)
	//{{AFX_MSG_MAP(CGPWndSizer)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CGPWndSizer::CGPWndSizer(HWND iParentHWND, UINT iId)
{
	m_clrBkgndSizer =-1;
	m_brBkgndSizer= NULL;
	m_Width=3;
	m_deltaStart=0;
	m_deltaEnd=0;
	m_Type=0;
	MinParentSize=2;
	MaxParentSize=0x1000;
	ParentHWND=iParentHWND;
	m_ID=iId;
	m_Drag=0;
	m_HICON=NULL;
	CreateEx(0,NULL,"",WS_CHILD,CRect(0,0,15,15),CWnd::FromHandle(ParentHWND),m_ID);
	Invalidate();
}

CGPWndSizer::~CGPWndSizer()
{
	if (m_HICON)
		DestroyIcon(m_HICON);
	m_HICON=NULL;

	if (m_brBkgndSizer!=NULL) delete m_brBkgndSizer;
}


const CString CGPWndSizer::GetName()
{
	return m_Name;
}

CString CGPWndSizer::SetName(CString & iNewName)
{
	CString ret=m_Name;
	m_Name=iNewName;
	return ret;
}

UINT CGPWndSizer::SetSizer(const char * iSetStr)
{
	UINT ret=0;
	char *tmp=new char [(int)strlen(iSetStr)+10];
	strcpy(tmp,iSetStr);
	_strupr(tmp);
	//"Type,Size,MinParentSize,MaxParentSize"
	char *pos=strchr(tmp,',');
	if (pos)
	{
		ret++;
		m_LastScanf=sscanf(++pos,"%d,%d,%d",&m_Width,&MinParentSize,&MaxParentSize);
		if (m_Width<1) m_Width=3;
		if (MinParentSize<1) MinParentSize=3;
		if (MaxParentSize<3) MaxParentSize=0x1000;
	}

	UINT i;
	for(i=0;i<uNTypes;i++)
		if (strstr(tmp,cArrTypes[i]))
			m_Type|=uArrTypes[i];

	UINT stl=0;
	for(i=0;i<N_WND_STYLES;i++)
		if (strstr(tmp,aWndStyleName[i]))
			stl|=aWndStyleUINT[i];

	if (stl)
		ModifyStyle(GetStyle()&(0xFFFFFFFF^WS_CHILD),stl|WS_CHILD);
	RECT re;
	GetWindowRect(&re);
	GetClientRect(&re);
	stl=0;
	for(i=0;i<N_WND_EX_STYLES;i++)
		if (strstr(tmp,aWndExStyleName[i]))
			m_Type=aWndExStyleUINT[i];

	if (stl) ModifyStyleEx(GetExStyle(),stl);

	UpdateSizer();
	delete[] tmp;
	return ret;
}

void CGPWndSizer::UpdateSizer()
{
	RECT re;
	CWnd *mParent=GetParent();
	if (mParent)
	{
		GetParent()->GetClientRect(&re);


		if ((m_Type&GPSS_TOP)==GPSS_TOP) re.bottom=m_Width;
		else
		if ((m_Type&GPSS_BOTTOM)==GPSS_BOTTOM) re.top=re.bottom-m_Width;

		if ((m_Type&GPSS_LEFT)==GPSS_LEFT) re.right=m_Width;
		else
		if ((m_Type&GPSS_RIGHT)==GPSS_RIGHT) re.left=re.right-m_Width;

		if ((m_Type&GPSS_POSITIONMASK)==GPSS_TOP || (m_Type&GPSS_POSITIONMASK)==GPSS_BOTTOM) {re.left+=m_Width;re.right-=m_Width;}
		else
		if ((m_Type&GPSS_POSITIONMASK)==GPSS_LEFT || (m_Type&GPSS_POSITIONMASK)==GPSS_RIGHT) {re.top+=m_Width;re.bottom-=m_Width;}

		if ((m_Type&(GPSS_ROUND|GPSS_SQUARE|GPSS_ICON))||(m_Type&GPSS_POSITIONMASK)==GPSS_CENTER)
		{
			if ((m_Type&GPSS_POSITIONMASK)==GPSS_TOP || (m_Type&GPSS_POSITIONMASK)==GPSS_BOTTOM || (m_Type&GPSS_POSITIONMASK)==GPSS_CENTER) 
			{
				re.left=re.right/2;
				re.right=re.left+m_Width;
			}
			if ((m_Type&GPSS_POSITIONMASK)==GPSS_LEFT || (m_Type&GPSS_POSITIONMASK)==GPSS_RIGHT || (m_Type&GPSS_POSITIONMASK)==GPSS_CENTER) 
			{
				re.top=re.bottom/2;
				re.bottom=re.top+m_Width;
			}
			if ((m_Type&GPSS_POSITIONMASK)==GPSS_CENTER)
			{
				re.top-=((m_Width+1)/2);
				re.left-=((m_Width+1)/2);
			}
		}

		int delta;
		if ((delta=re.bottom-re.top)<m_Width)
		{
			re.top-=(delta+m_Width)/2;
			re.bottom+=(delta+m_Width)/2;
		}
		if ((delta=re.right-re.left)<m_Width)
		{
			re.left-=(delta+m_Width)/2;
			re.right+=(delta+m_Width)/2;
		}

		MoveWindow(&re);
	}
}


void CGPWndSizer::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonUp(nFlags, point);
	if (m_Drag)
	{
		ReleaseCapture();
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		m_Drag=0;
	}
}

void CGPWndSizer::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonDown(nFlags, point);
	m_StartPoint=point;
	m_Drag=1;
	LPCTSTR pss=IDC_ARROW;
	switch((m_Type&GPSS_POSITIONMASK))
	{
	case GPSS_TOP:			
	case GPSS_BOTTOM:	pss=IDC_SIZENS;		break;
	case GPSS_LEFT:			
	case GPSS_RIGHT:	pss=IDC_SIZEWE;		break;
	case GPSS_TLEFT:		
	case GPSS_BRIGHT:	pss=IDC_SIZENWSE;	break;
	case GPSS_TRIGHT:	
	case GPSS_BLEFT:	pss=IDC_SIZENESW;	break;
	case GPSS_CENTER:	pss=IDC_SIZEALL;	break;
	default:			pss=IDC_ARROW;		break;
	}

	SetCursor(AfxGetApp()->LoadStandardCursor(pss));
	SetCapture();
}

void CGPWndSizer::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd::OnMouseMove(nFlags, point);
	LPCTSTR pss=IDC_ARROW;
	switch((m_Type&GPSS_POSITIONMASK))
	{
	case GPSS_TOP:			
	case GPSS_BOTTOM:	pss=IDC_SIZENS;		break;
	case GPSS_LEFT:			
	case GPSS_RIGHT:	pss=IDC_SIZEWE;		break;
	case GPSS_TLEFT:		
	case GPSS_BRIGHT:	pss=IDC_SIZENWSE;	break;
	case GPSS_TRIGHT:	
	case GPSS_BLEFT:	pss=IDC_SIZENESW;	break;
	case GPSS_CENTER:	pss=IDC_SIZEALL;	break;
	default:			pss=IDC_ARROW;		break;
	}

	SetCursor(AfxGetApp()->LoadStandardCursor(pss));

	if (m_Drag)
	{
		ParentHWND=::GetParent(m_hWnd);
		
		if (ParentHWND)
		{
			CRect pare;
			::GetWindowRect(ParentHWND,&pare);

			if ((::GetWindowLong(ParentHWND,GWL_STYLE)&WS_POPUP)!=WS_POPUP)
			{
				HWND parentparent=::GetParent(ParentHWND);
//				if (parentparent && (::GetWindowLong(parentparent,GWL_STYLE)&WS_POPUP)!=WS_POPUP)
					if (parentparent) 
						CWnd::FromHandle(parentparent)->ScreenToClient(&pare);
			}

			int dx=(point.x-m_StartPoint.x);
			int dy=-(point.y-m_StartPoint.y);

			if ((m_Type&GPSS_TOP)==GPSS_TOP)
			{
				pare.top-=dy;
				if ((m_Type&GPSS_MOVE))
				{
					if (pare.Height()<MinParentSize) pare.bottom=pare.top+MinParentSize;
					if (pare.Height()>MaxParentSize) pare.bottom=pare.top+MaxParentSize;
				}
				else
				{
					if (pare.Height()<MinParentSize) pare.top=pare.bottom-MinParentSize;
					if (pare.Height()>MaxParentSize) pare.top=pare.bottom-MaxParentSize;
				}
			}
			else
			if ((m_Type&GPSS_BOTTOM)==GPSS_BOTTOM)
			{
				pare.bottom-=dy;
				if ((m_Type&GPSS_MOVE))
				{
					if (pare.Height()<MinParentSize) pare.top=pare.bottom-MinParentSize;
					if (pare.Height()>MaxParentSize) pare.top=pare.bottom-MaxParentSize;
				}
				else
				{
					if (pare.Height()<MinParentSize) pare.bottom=pare.top+MinParentSize;
					if (pare.Height()>MaxParentSize) pare.bottom=pare.top+MinParentSize;
				}
			}

			if ((m_Type&GPSS_LEFT)==GPSS_LEFT)
			{
				pare.left+=dx;
				if ((m_Type&GPSS_MOVE))
				{
					if (pare.Width()<MinParentSize) pare.right=pare.left+MinParentSize;
					if (pare.Width()>MaxParentSize) pare.right=pare.left+MaxParentSize;
				}
				else
				{
					if (pare.Width()<MinParentSize) pare.left=pare.right-MinParentSize;
					if (pare.Width()>MaxParentSize) pare.left=pare.right-MaxParentSize;
				}
			}
			else
			if ((m_Type&GPSS_RIGHT)==GPSS_RIGHT)
			{
				pare.right+=dx;
				if ((m_Type&GPSS_MOVE))
				{
					if (pare.Width()<MinParentSize) pare.left=pare.right-MinParentSize;
					if (pare.Width()>MaxParentSize) pare.left=pare.right-MaxParentSize;
				}
				else
				{
					if (pare.Width()<MinParentSize) pare.right=pare.left+MinParentSize;
					if (pare.Width()>MaxParentSize) pare.right=pare.left+MaxParentSize;
				}
			}

			if ((m_Type&GPSS_POSITIONMASK)==GPSS_CENTER)
			{
				pare.top-=dy;
				pare.bottom-=dy;
				pare.left+=dx;
				pare.right+=dx;
			}

//			m_Type|=GPSS_INSIDE;
			if ((m_Type&GPSS_INSIDE)==GPSS_INSIDE && (::GetWindowLong(ParentHWND,GWL_STYLE)&WS_POPUP)!=WS_POPUP)
			{

				HWND parentparent=::GetParent(ParentHWND);
				RECT papare={0};
				::GetClientRect(parentparent,&papare);

				if (pare.right>papare.right)	{pare.left-=(pare.right-papare.right);pare.right=papare.right;}
				if (pare.bottom>papare.bottom)	{pare.top-=(pare.bottom-papare.bottom);pare.bottom=papare.bottom;}

				if (pare.left<0) {pare.right-=pare.left;pare.left=0;}
				if (pare.top<0) {pare.bottom-=pare.top;pare.top=0;}
			}

			if (lastRect!=pare)
			{
				lastRect=pare;
				GetParent()->MoveWindow(&pare);

				if (GPC.m_UpdateSizeNow==0)
				{
					GPC.m_UpdateSizeNow=1;
					::PostMessage(ParentHWND,GPM_SETAUTOSIZE,(WPARAM)ParentHWND,0);
				}
			}
		}
	}
}

void CGPWndSizer::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	RECT re={0};
	GetClientRect(&re);
	CBrush *oldbrush=NULL;

	if (m_clrBkgndSizer!=-1)
		dc.SetBkColor(m_clrBkgndSizer);

	if (m_brBkgndSizer)
		oldbrush=dc.SelectObject(m_brBkgndSizer);


	switch((m_Type&GPSS_FILLMASK))
	{
	case GPSS_INVISIBLE:
		break;
	case GPSS_INVERT:
		dc.InvertRect(&re);
		break;
	case GPSS_BRUSH:	
		if (m_brBkgndSizer) dc.FillRect(&re,m_brBkgndSizer);
		else dc.FillSolidRect(&re,m_clrBkgndSizer);
		break;
	}


	switch((m_Type&GPSS_FORMMASK))
	{
	case GPSS_ROUND:
		dc.Ellipse(&re);
		break;
	case GPSS_SQUARE:
		break;
	case GPSS_ICON:
		if (m_HICON)
			DrawIconEx(dc,(re.right-m_Width)/2,(re.bottom-m_Width)/2,m_HICON,m_Width,m_Width,0,NULL,DI_NORMAL);
		break;
	}


	if (oldbrush) dc.SelectObject(oldbrush);
}

HWND CGPWndSizer::SetSizerIcon(const char *iStr)
{
	 //"Name,ILName,nImage"
	HWND ret=NULL;
	m_Type=(m_Type&(-1^GPSS_FORMMASK))|GPSS_ICON;
	if (m_HICON)
		DestroyIcon(m_HICON);
	m_HICON=NULL;
	CString name=ExtractField(iStr,1,",");

	if (name=="") name="MISCS";

	GPImageList *SMainIl;
	int ImgLId;
	if ((ImgLId=GPC.GetImageListId(name))>=0 && (SMainIl=&(GPC.a_GPImageList[ImgLId]))!=NULL)
	{
		int nImage=atoi(ExtractField(iStr,2,","));
		m_HICON=(HICON)	SMainIl->m_IL.ExtractIcon(nImage);
		if (m_HICON)
		{
			IMAGEINFO ii={0};
			SMainIl->m_IL.GetImageInfo(nImage,&ii);
			if (ii.rcImage.right-ii.rcImage.left>0)
				m_Width=ii.rcImage.right-ii.rcImage.left;

			int cx,cy;
			::ImageList_GetIconSize(SMainIl->m_IL.m_hImageList, &cx, &cy);

			UpdateSizer();
			Invalidate();
		}
	}

	return ret;
}

HWND CGPWndSizer::SetSizerRgn(const char *iStr)
{
	 //"RgnName"
	HWND ret=NULL;

	if (m_hWnd!=NULL)
	{
		int rrr;
		GPRegion *tmpreg=GPC.RegionArr.GetRgn(iStr);
		if (tmpreg!=NULL && tmpreg->GetHRGN()!=NULL)
		{
			HRGN rgtmp=CreateRectRgn(0,0,55,55);
			CombineRgn(rgtmp,tmpreg->GetHRGN(),NULL,RGN_COPY);
			rrr=SetWindowRgn(rgtmp,TRUE);
			ret=m_hWnd;
		}
		else
		{
			CRect re;
			GetWindowRect(&re);
			re.OffsetRect(-re.TopLeft());
			HRGN rg=CreateRectRgnIndirect(re);
			SetWindowRgn(rg,TRUE);
		}
		Invalidate();
	}

	return ret;
}

HWND CGPWndSizer::SetSizerBrush(const char *iStr)
{
	 //"BRUSH_AS_PROPERTY"
	GPSetBrushProperty(&lbSizer,iStr);
	GPSetBrush(m_hWnd,&m_brBkgndSizer,&lbSizer,m_clrBkgndSizer);
	Invalidate();

	return m_hWnd;
}
