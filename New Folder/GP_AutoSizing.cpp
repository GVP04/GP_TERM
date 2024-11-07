// GP_AutoSizing.cpp: implementation of the GP_AutoSizing class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GP_AutoSizing.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GP_AutoSizing::GP_AutoSizing()
{
	m_Pause=0;
	nItem=0;
	nBuff=10;
	aSizingItem=new SIZINGITEM * [nBuff];
	int i;
	for(i=0;i<nBuff;i++)
		aSizingItem[i]=NULL;

	InitSizing();
}

GP_AutoSizing::~GP_AutoSizing()
{
	if (aSizingItem!=NULL)
	{
		DeleteAll();
		delete aSizingItem;
	}
	aSizingItem=NULL;
}

void GP_AutoSizing::ResizeOne(CRect CompareRect, CRect CompareRectW, int Item, CPoint SmeLocal, CPoint SmeLocalW)
{
	if (m_Pause==0)
	{
		CRect *EtalonRect=&aSizingItem[Item]->EtalonRect;
		CRect *EtalonRectW=&aSizingItem[Item]->EtalonRectW;
		CRect *InitialRect=&aSizingItem[Item]->InitialRect;
		CRect *InitialRectW=&aSizingItem[Item]->InitialRectW;
		CRect QurentRect;
		CRect QurentRectW;

		if (aSizingItem[Item]!=NULL && aSizingItem[Item]->ItemHWND!=NULL)
		{
			::GetWindowRect(aSizingItem[Item]->ItemHWND,&QurentRect);
			QurentRectW=QurentRect;
			QurentRect.OffsetRect(-SmeLocal);
			QurentRectW.OffsetRect(-SmeLocalW);

			if (!CompareRect.IsRectEmpty())
			{
				if (!EtalonRect->IsRectEmpty())
				{
					switch(aSizingItem[Item]->StyleTop&0xFFFF)
					{
					case 'N':	QurentRect.top=InitialRect->top;	break;
					case 'P':
						QurentRect.top=CompareRect.top+((InitialRect->top-EtalonRect->top)*(CompareRect.Height()+1))/(EtalonRect->Height()+1)*((aSizingItem[Item]->StyleTop&0x10000)!=0?-1:1);
						break;
					case 'S':
						QurentRect.top=(CompareRect.top-EtalonRect->top)*((aSizingItem[Item]->StyleTop&0x10000)!=0?-1:1)+InitialRect->top;
						break;
					case 'E':
						QurentRect.top=(CompareRect.bottom-EtalonRect->bottom)*((aSizingItem[Item]->StyleTop&0x10000)!=0?-1:1)+InitialRect->top;
						break;
					case 'M':
						QurentRect.top=((CompareRect.bottom+CompareRect.top)-(EtalonRect->bottom+EtalonRect->top))/2*((aSizingItem[Item]->StyleTop&0x10000)!=0?-1:1)+InitialRect->top;
						break;
					case 'I':   break;
					case 'p':
						QurentRect.top=CompareRectW.top+((InitialRectW->top-EtalonRectW->top)*(CompareRectW.Height()+1))/(EtalonRectW->Height()+1)*((aSizingItem[Item]->StyleTop&0x10000)!=0?-1:1);
						break;
					case 'n':	QurentRect.top=InitialRect->top;	break;
					case 's':
						QurentRect.top=(CompareRectW.top-EtalonRectW->top)*((aSizingItem[Item]->StyleTop&0x10000)!=0?-1:1)+InitialRectW->top;
						break;
					case 'e':
						QurentRect.top=(CompareRectW.bottom-EtalonRectW->bottom)*((aSizingItem[Item]->StyleTop&0x10000)!=0?-1:1)+InitialRectW->top;
						break;
					case 'm':
						QurentRect.top=((CompareRectW.bottom+CompareRectW.top)-(EtalonRectW->bottom+EtalonRectW->top))/2*((aSizingItem[Item]->StyleTop&0x10000)!=0?-1:1)+InitialRectW->top;
						break;
					case 'i':  QurentRect.top=QurentRectW.top; break;
					default:
						if (aSizingItem[Item]->StyleTop>='1' && aSizingItem[Item]->StyleTop<='9')
							QurentRect.top=(((CompareRect.bottom+CompareRect.top)-(EtalonRect->bottom+EtalonRect->top))*1000)/((aSizingItem[Item]->StyleTop-'1')*1000)*((aSizingItem[Item]->StyleTop&0x10000)!=0?-1:1)+InitialRect->top;
						break;
					}

					switch(aSizingItem[Item]->StyleLeft&0xFFFF)
					{
					case 'N':	QurentRect.left=InitialRect->left;	break;
					case 'P':
						QurentRect.left=CompareRect.left+((InitialRect->left-EtalonRect->left)*(CompareRect.Width()+1))/(EtalonRect->Width()+1)*((aSizingItem[Item]->StyleLeft&0x10000)!=0?-1:1);
						break;
					case 'S':
						QurentRect.left=(CompareRect.left-EtalonRect->left)*((aSizingItem[Item]->StyleLeft&0x10000)!=0?-1:1)+InitialRect->left;
						break;
					case 'E':
						QurentRect.left=(CompareRect.right-EtalonRect->right)*((aSizingItem[Item]->StyleLeft&0x10000)!=0?-1:1)+InitialRect->left;
						break;
					case 'M':
						QurentRect.left=((CompareRect.left+CompareRect.right)-(EtalonRect->left+EtalonRect->right))/2*((aSizingItem[Item]->StyleLeft&0x10000)!=0?-1:1)+InitialRect->left;
						break;
					case 'I':   break;
					case 'n':	QurentRect.left=InitialRect->left;	break;
					case 'p':
						QurentRect.left=CompareRectW.left+((InitialRectW->left-EtalonRectW->left)*(CompareRectW.Width()+1))/(EtalonRectW->Width()+1)*((aSizingItem[Item]->StyleLeft&0x10000)!=0?-1:1);
						break;
					case 's':
						QurentRect.left=(CompareRectW.left-EtalonRectW->left)*((aSizingItem[Item]->StyleLeft&0x10000)!=0?-1:1)+InitialRectW->left;
						break;
					case 'e':
						QurentRect.left=(CompareRectW.right-EtalonRectW->right)*((aSizingItem[Item]->StyleLeft&0x10000)!=0?-1:1)+InitialRectW->left;
						break;
					case 'm':
						QurentRect.left=((CompareRectW.left+CompareRectW.right)-(EtalonRectW->left+EtalonRectW->right))/2*((aSizingItem[Item]->StyleLeft&0x10000)!=0?-1:1)+InitialRectW->left;
						break;
					case 'i': QurentRect.left=QurentRectW.left;  break;
					default:
						if (aSizingItem[Item]->StyleTop>='1' && aSizingItem[Item]->StyleTop<='9')
							QurentRect.left=(((CompareRect.left+CompareRect.right)-(EtalonRect->left+EtalonRect->right))*1000)/((aSizingItem[Item]->StyleTop-'1')*1000)*((aSizingItem[Item]->StyleLeft&0x10000)!=0?-1:1)+InitialRect->left;
						break;
					}

					switch(aSizingItem[Item]->StyleBottom&0xFFFF)
					{
					case 'N':	QurentRect.bottom=InitialRect->bottom;	break;
					case 'P':
						QurentRect.bottom=CompareRect.bottom+((InitialRect->bottom-EtalonRect->bottom)*(CompareRect.Height()+1))/(EtalonRect->Height()+1)*((aSizingItem[Item]->StyleBottom&0x10000)!=0?-1:1);
						break;
					case 'S':
						QurentRect.bottom=(CompareRect.top-EtalonRect->top)*((aSizingItem[Item]->StyleBottom&0x10000)!=0?-1:1)+InitialRect->bottom;
						break;
					case 'E':
						QurentRect.bottom=(CompareRect.bottom-EtalonRect->bottom)*((aSizingItem[Item]->StyleBottom&0x10000)!=0?-1:1)+InitialRect->bottom;
						break;
					case 'M':
						QurentRect.bottom=((CompareRect.bottom+CompareRect.top)-(EtalonRect->bottom+EtalonRect->top))/2*((aSizingItem[Item]->StyleBottom&0x10000)!=0?-1:1)+InitialRect->bottom;
						break;
					case 'I':   break;
					case 'n':	QurentRect.bottom=InitialRect->bottom;	break;
					case 'p':
						QurentRect.bottom=CompareRectW.bottom+((InitialRectW->bottom-EtalonRectW->bottom)*(CompareRectW.Height()+1))/(EtalonRectW->Height()+1)*((aSizingItem[Item]->StyleBottom&0x10000)!=0?-1:1);
						break;
					case 's':
						QurentRect.bottom=(CompareRectW.top-EtalonRectW->top)*((aSizingItem[Item]->StyleBottom&0x10000)!=0?-1:1)+InitialRectW->bottom;
						break;
					case 'e':
						QurentRect.bottom=(CompareRectW.bottom-EtalonRectW->bottom)*((aSizingItem[Item]->StyleBottom&0x10000)!=0?-1:1)+InitialRectW->bottom;
						break;
					case 'm':
						QurentRect.bottom=((CompareRectW.bottom+CompareRectW.top)-(EtalonRectW->bottom+EtalonRectW->top))/2*((aSizingItem[Item]->StyleBottom&0x10000)!=0?-1:1)+InitialRectW->bottom;
						break;
					case 'i':  QurentRect.bottom=QurentRectW.bottom; break;
					default:
						if (aSizingItem[Item]->StyleTop>='1' && aSizingItem[Item]->StyleTop<='9')
							QurentRect.bottom=(((CompareRect.bottom+CompareRect.top)-(EtalonRect->bottom+EtalonRect->top))*1000)/((aSizingItem[Item]->StyleTop-'1')*1000)*((aSizingItem[Item]->StyleBottom&0x10000)!=0?-1:1)+InitialRect->bottom;
						break;
					}

					switch(aSizingItem[Item]->StyleRight&0xFFFF)
					{
					case 'N':	QurentRect.right=InitialRect->right;	break;
					case 'P':
						QurentRect.right=CompareRect.right+((InitialRect->right-EtalonRect->right)*(CompareRect.Width()+1))/(EtalonRect->Width()+1)*((aSizingItem[Item]->StyleRight&0x10000)!=0?-1:1);
						break;
					case 'S':
						QurentRect.right=(CompareRect.left-EtalonRect->left)*((aSizingItem[Item]->StyleRight&0x10000)!=0?-1:1)+InitialRect->right;
						break;
					case 'E':
						QurentRect.right=(CompareRect.right-EtalonRect->right)*((aSizingItem[Item]->StyleRight&0x10000)!=0?-1:1)+InitialRect->right;
						break;
					case 'M':
						QurentRect.right=((CompareRect.left+CompareRect.right)-(EtalonRect->left+EtalonRect->right))/2*((aSizingItem[Item]->StyleRight&0x10000)!=0?-1:1)+InitialRect->right;
						break;
					case 'I':   break;
					case 'n':	QurentRect.right=InitialRect->right;	break;
					case 'p':
						QurentRect.right=CompareRectW.right+((InitialRectW->right-EtalonRectW->right)*(CompareRectW.Width()+1))/(EtalonRectW->Width()+1)*((aSizingItem[Item]->StyleRight&0x10000)!=0?-1:1);
						break;
					case 's':
						QurentRect.right=(CompareRectW.left-EtalonRectW->left)*((aSizingItem[Item]->StyleRight&0x10000)!=0?-1:1)+InitialRectW->right;
						break;
					case 'e':
						QurentRect.right=(CompareRectW.right-EtalonRectW->right)*((aSizingItem[Item]->StyleRight&0x10000)!=0?-1:1)+InitialRectW->right;
						break;
					case 'm':
						QurentRect.right=((CompareRectW.left+CompareRectW.right)-(EtalonRectW->left+EtalonRectW->right))/2*((aSizingItem[Item]->StyleRight&0x10000)!=0?-1:1)+InitialRectW->right;
						break;
					case 'i':  QurentRect.right=QurentRectW.right; break;
					default:
						if (aSizingItem[Item]->StyleTop>='1' && aSizingItem[Item]->StyleTop<='9')
							QurentRect.right=(((CompareRect.left+CompareRect.right)-(EtalonRect->left+EtalonRect->right))*1000)/((aSizingItem[Item]->StyleTop-'1')*1000)*((aSizingItem[Item]->StyleRight&0x10000)!=0?-1:1)+InitialRect->right;
						break;
					}

				}
			}
			CheckAndUpdate(*aSizingItem[Item], QurentRect);
		}
	}

}

void GPWriteErrorLog(const char *iInfo, const char *iInfo2)
{
	FILE *fl=fopen("MAINERR.LOG","at");
	if (fl)
	{
		COleDateTime tm=COleDateTime::GetCurrentTime();
		CString tmp1=tm.Format("%#c ");
		fputs(tmp1,fl);
		fputs(iInfo,fl);
		fputs(iInfo2,fl);
		fputs("\n",fl);
		fclose(fl);
	}
}

void GP_AutoSizing::UpdateSize()
{
	if (m_Pause==0 && nItem)
	{
		int i;
		char *done=new char [nItem+20];
		try
		{
			if (MainSizingItem.ItemHWND && !::IsIconic(MainSizingItem.ItemHWND))
			{
				{
					CRect re;
					::GetWindowRect(MainSizingItem.ItemHWND,&re);
					if ((::GetWindowLong(MainSizingItem.ItemHWND,GWL_STYLE)&WS_CHILD)==WS_CHILD)
					{
						ScreenToClient(::GetParent(MainSizingItem.ItemHWND),(LPPOINT)((LPRECT)&re));
						ScreenToClient(::GetParent(MainSizingItem.ItemHWND),((LPPOINT)((LPRECT)&re))+1);
					}
					CheckAndUpdate(MainSizingItem, re);
				}


				for(i=0;i<nItem;i++) done[i]=0;

				if (MainSizingItem.ItemHWND!=NULL)
				{
					CRect CmpRect;
					CRect CmpRectW;
					CPoint Sme(0,0);
					CPoint SmeW(0,0);
					::GetClientRect(MainSizingItem.ItemHWND,&CmpRect);
					::GetWindowRect(MainSizingItem.ItemHWND,&CmpRectW);
					SmeW=CmpRectW.TopLeft();
					::ScreenToClient(MainSizingItem.ItemHWND,((LPPOINT)((LPRECT)CmpRectW)));
					::ScreenToClient(MainSizingItem.ItemHWND,((LPPOINT)((LPRECT)CmpRectW))+1);
					::ClientToScreen(MainSizingItem.ItemHWND,&Sme);

					for(i=0;i<nItem;i++)
						if (aSizingItem[i]!=NULL && aSizingItem[i]->MainHWND==MainSizingItem.ItemHWND)
						{
							done[i]=1;
							HWND tmpparent=::GetParent(aSizingItem[i]->ItemHWND);
							if (tmpparent==MainSizingItem.ItemHWND)
								ResizeOne(CmpRect,CmpRectW,i,Sme,SmeW);
							else
							{
								CPoint Sme2(0,0);
								CPoint Sme2W(0,0);
								CRect CmpRectW2;
								::ClientToScreen(tmpparent,&Sme2);
								::GetWindowRect(MainSizingItem.ItemHWND,&CmpRectW2);
								Sme2W=CmpRectW2.TopLeft();
								ResizeOne(CmpRect,CmpRectW,i,Sme2,Sme2W);
							}

						}

					int flg=-1,oldflg;
					do
					{
						oldflg=flg;
						flg=0;
						for(i=0;i<nItem;i++)
							if (aSizingItem[i]!=NULL && done[i]==0)
							{
								flg++;
								if (aSizingItem[i]->ItemHWND==aSizingItem[i]->MainHWND)
								{
									CRect QurentRect;
									::GetWindowRect(aSizingItem[i]->ItemHWND,&QurentRect);
									HWND tmpparent=::GetParent(aSizingItem[i]->ItemHWND);
									::ScreenToClient(tmpparent,(LPPOINT)((LPRECT)&QurentRect));
									::ScreenToClient(tmpparent,((LPPOINT)((LPRECT)&QurentRect))+1);
									CheckAndUpdate(*aSizingItem[i], QurentRect);
									done[i]=1;
								}
								else
								{
									int j;
									for(j=0;j<nItem;j++)
										if (aSizingItem[j]!=NULL && aSizingItem[i]->MainHWND==aSizingItem[j]->ItemHWND && done[j]!=0)
										{
											done[i]=1;
											if (aSizingItem[i]->MainHWND!=NULL)
											{
												::GetClientRect(aSizingItem[i]->MainHWND,&CmpRect);
												::GetWindowRect(aSizingItem[i]->MainHWND,&CmpRectW);
												::ScreenToClient(aSizingItem[i]->MainHWND,((LPPOINT)((LPRECT)CmpRectW)));
												::ScreenToClient(aSizingItem[i]->MainHWND,((LPPOINT)((LPRECT)CmpRectW))+1);

												if (::GetParent(aSizingItem[i]->ItemHWND)==MainSizingItem.ItemHWND)
												{
													::ClientToScreen(aSizingItem[i]->MainHWND,(LPPOINT)((LPRECT)&CmpRect));
													::ClientToScreen(aSizingItem[i]->MainHWND,((LPPOINT)((LPRECT)&CmpRect))+1);
													::ClientToScreen(aSizingItem[i]->MainHWND,(LPPOINT)((LPRECT)&CmpRectW));
													::ClientToScreen(aSizingItem[i]->MainHWND,((LPPOINT)((LPRECT)&CmpRectW))+1);
													CPoint ppp(0,0);
													CPoint ppp2(0,0);
													::ClientToScreen(MainSizingItem.ItemHWND,&ppp);
													CmpRect.OffsetRect(-ppp);
													CRect tmpRect;
													::GetWindowRect(MainSizingItem.ItemHWND,&tmpRect);
													ppp2=tmpRect.TopLeft();
													CmpRectW.OffsetRect(-ppp2);
													ResizeOne(CmpRect,CmpRectW,i,ppp,ppp2);
												}
												else
												{
													if (::GetParent(aSizingItem[i]->ItemHWND)!=aSizingItem[i]->MainHWND)
													{
														CPoint ppp(0,0);
														CPoint pppW(0,0);
														CRect tmpr;
														::GetWindowRect(::GetParent(aSizingItem[i]->ItemHWND),&tmpr);
														pppW=tmpr.TopLeft();
														::ScreenToClient(::GetParent(aSizingItem[i]->MainHWND),&pppW);
														::ClientToScreen(::GetParent(aSizingItem[i]->ItemHWND),&pppW);

														::ClientToScreen(::GetParent(aSizingItem[i]->ItemHWND),&ppp);
														::ScreenToClient(::GetParent(aSizingItem[i]->MainHWND),&ppp);
														::ClientToScreen(::GetParent(aSizingItem[i]->ItemHWND),&ppp);
														ResizeOne(CmpRect,CmpRectW,i,-ppp,-pppW);
													}
													else ResizeOne(CmpRect,CmpRectW,i,-Sme,-SmeW);
												}
											}
											break;
										}
								}
							}
					}while(flg!=oldflg);
				}
			}
		}
		catch(...){GPWriteErrorLog("ERROR GP_AutoSizing.cpp(297):", "");;}


		if (MainSizingItem.ItemHWND!=NULL)
		{
			RECT InvRect;
			::GetClientRect(MainSizingItem.ItemHWND,&InvRect);
			::InvalidateRect(MainSizingItem.ItemHWND,&InvRect,TRUE);
		}
		
		delete[] done;
	}
}

void GP_AutoSizing::Reset()
{
	InitSizing();
}

UINT GP_AutoSizing::GetItemCount()
{
	return nItem;
}

BOOL GP_AutoSizing::AddWnd(HWND ihWnd, HWND hWndMain, const char *iString)
{
	BOOL ret=FALSE;

	if (ihWnd!=NULL && hWndMain!=NULL)
	{
		DeleteWndEx(ihWnd,hWndMain);

		while(nItem>=nBuff)
		{
			SIZINGITEM **aSizingItemTMP=new SIZINGITEM * [nBuff+32];
			if (aSizingItemTMP!=NULL)
			{
				nBuff+=32;
				int i;
				for(i=0;i<nItem;i++)
					aSizingItemTMP[i]=aSizingItem[i];

				for(;i<nBuff;i++)
					aSizingItemTMP[i]=NULL;

				delete[] aSizingItem;
				aSizingItem=aSizingItemTMP;
			}
		}

		int CurItem=nItem++;
		ret=TRUE;
		if (aSizingItem[CurItem]==NULL) aSizingItem[CurItem]=new SIZINGITEM;
		aSizingItem[CurItem]->ItemHWND=ihWnd;
		aSizingItem[CurItem]->MainHWND=hWndMain;
		{
			UINT StlSign=0;
			if (*iString=='-')  {StlSign=0x10000;iString++;} else StlSign=0;
			aSizingItem[CurItem]->StyleTop=(*(iString++))|StlSign;
			if (*iString=='-')  {StlSign=0x10000;iString++;} else StlSign=0;
			aSizingItem[CurItem]->StyleLeft=(*(iString++))|StlSign;
			if (*iString=='-')  {StlSign=0x10000;iString++;} else StlSign=0;
			aSizingItem[CurItem]->StyleBottom=(*(iString++))|StlSign;
			if (*iString=='-')  {StlSign=0x10000;iString++;} else StlSign=0;
			aSizingItem[CurItem]->StyleRight=(*(iString++))|StlSign;
		}

		if (hWndMain==MainSizingItem.ItemHWND)
		{
			::GetClientRect(hWndMain,&aSizingItem[CurItem]->EtalonRect);
			::GetWindowRect(hWndMain,&aSizingItem[CurItem]->EtalonRectW);
			::ScreenToClient(hWndMain,(POINT *)((LPRECT)aSizingItem[CurItem]->EtalonRectW));
			::ScreenToClient(hWndMain,((POINT *)((LPRECT)aSizingItem[CurItem]->EtalonRectW))+1);
			CPoint Sme(0,0);
			CRect tmpRect;

			if (::GetParent(ihWnd)!=MainSizingItem.ItemHWND)
			{
				::ClientToScreen(::GetParent(ihWnd),&Sme);
				::GetWindowRect(::GetParent(ihWnd),&tmpRect);
			}
			else
			{
				::ClientToScreen(hWndMain,&Sme);
				::GetWindowRect(hWndMain,&tmpRect);
			}

			::GetWindowRect(ihWnd,&aSizingItem[CurItem]->InitialRect);
			aSizingItem[CurItem]->InitialRectW=aSizingItem[CurItem]->InitialRect;
			aSizingItem[CurItem]->InitialRect.OffsetRect(-Sme);
			aSizingItem[CurItem]->InitialRectW.OffsetRect(-tmpRect.TopLeft());
		}
		else
		{
			CPoint Sme(0,0);
			if (::GetParent(ihWnd)!=MainSizingItem.ItemHWND)
			{
				::GetClientRect(hWndMain,&aSizingItem[CurItem]->EtalonRect);
				::GetWindowRect(hWndMain,&aSizingItem[CurItem]->EtalonRectW);
				::ScreenToClient(hWndMain,(LPPOINT)((LPRECT)aSizingItem[CurItem]->EtalonRectW));
				::ScreenToClient(hWndMain,((LPPOINT)((LPRECT)aSizingItem[CurItem]->EtalonRectW))+1);
				if (::GetParent(ihWnd)==hWndMain)
				{
					CPoint ppp(0,0);
					::GetWindowRect(ihWnd,&aSizingItem[CurItem]->InitialRect);
					aSizingItem[CurItem]->InitialRectW=aSizingItem[CurItem]->InitialRect;
					CRect tmpRect;
					::GetWindowRect(hWndMain,&tmpRect);
					aSizingItem[CurItem]->InitialRectW.OffsetRect(-tmpRect.TopLeft());
					::ClientToScreen(hWndMain,&ppp);
					aSizingItem[CurItem]->InitialRect.OffsetRect(-ppp);
				}
				else
				{
					HWND tmpHWND=::GetParent(hWndMain);
					::ClientToScreen(tmpHWND,(LPPOINT)((LPRECT)&aSizingItem[CurItem]->EtalonRect));
					::ClientToScreen(tmpHWND,((LPPOINT)((LPRECT)&aSizingItem[CurItem]->EtalonRect))+1);
					::ClientToScreen(tmpHWND,(LPPOINT)((LPRECT)&aSizingItem[CurItem]->EtalonRectW));
					::ClientToScreen(tmpHWND,((LPPOINT)((LPRECT)&aSizingItem[CurItem]->EtalonRectW))+1);
					::ClientToScreen(tmpHWND,&Sme);
					aSizingItem[CurItem]->EtalonRect.OffsetRect(-Sme);
					CRect tmpRect;
					::GetWindowRect(tmpHWND,&tmpRect);
					aSizingItem[CurItem]->EtalonRectW.OffsetRect(-tmpRect.TopLeft());
					::GetWindowRect(ihWnd,&aSizingItem[CurItem]->InitialRect);
					::ScreenToClient(::GetParent(ihWnd),(LPPOINT)((LPRECT)&aSizingItem[CurItem]->InitialRect));
					::ScreenToClient(::GetParent(ihWnd),((LPPOINT)((LPRECT)&aSizingItem[CurItem]->InitialRect))+1);
					aSizingItem[CurItem]->InitialRectW=aSizingItem[CurItem]->InitialRect;
				}
			}
			else
			{
				::GetClientRect(hWndMain,&aSizingItem[CurItem]->EtalonRect);
				::GetWindowRect(hWndMain,&aSizingItem[CurItem]->EtalonRectW);
				::ClientToScreen(hWndMain,(LPPOINT)((LPRECT)&aSizingItem[CurItem]->EtalonRect));
				::ClientToScreen(hWndMain,((LPPOINT)((LPRECT)&aSizingItem[CurItem]->EtalonRect))+1);
				::ClientToScreen(MainSizingItem.ItemHWND,&Sme);
				CRect tmpRect;
				::GetWindowRect(MainSizingItem.ItemHWND,&tmpRect);

				aSizingItem[CurItem]->EtalonRect.OffsetRect(-Sme);
				aSizingItem[CurItem]->EtalonRectW.OffsetRect(-tmpRect.TopLeft());
				::GetWindowRect(ihWnd,&aSizingItem[CurItem]->InitialRect);
				aSizingItem[CurItem]->InitialRectW=aSizingItem[CurItem]->InitialRect;
				aSizingItem[CurItem]->InitialRect.OffsetRect(-Sme);
				aSizingItem[CurItem]->InitialRectW.OffsetRect(-tmpRect.TopLeft());
			}
		}

		aSizingItem[CurItem]->MaxRect=aSizingItem[CurItem]->MinRect=CRect(-11111,-11111,-11111,-11111);
		aSizingItem[CurItem]->MaxSize=aSizingItem[CurItem]->MinSize=CSize(-11111,-11111);
	}
	return ret;
}

BOOL GP_AutoSizing::AddSetMain(HWND ihWndMain)
{
	MainSizingItem.ItemHWND=MainSizingItem.MainHWND=ihWndMain;
	MainSizingItem.EtalonRect.SetRectEmpty();
	MainSizingItem.EtalonRectW.SetRectEmpty();
	if (ihWndMain)
	{
		::GetWindowRect(ihWndMain,&MainSizingItem.EtalonRect);
		MainSizingItem.InitialRectW=MainSizingItem.EtalonRectW=MainSizingItem.InitialRect=MainSizingItem.EtalonRect;
		MainSizingItem.MaxRect=MainSizingItem.MinRect=CRect(-11111,-11111,-11111,-11111);
		MainSizingItem.MaxSize=MainSizingItem.MinSize=CSize(-11111,-11111);

	}
	return MainSizingItem.EtalonRect.IsRectEmpty();
}

UINT GP_AutoSizing::DeleteWnd(HWND ihWnd)
{
	int i;
	try
	{
		if (nItem>0)
			for(i=0; i<nItem; i++)
				if (aSizingItem[i]!=NULL && aSizingItem[i]->ItemHWND==ihWnd)
				{
					nItem--;
					delete aSizingItem[i];
					int j;
					for(j=i; j<nItem; j++)
						aSizingItem[j]=aSizingItem[j+1];

					aSizingItem[j]=NULL;
					i--;
				}
	}
	catch(...){GPWriteErrorLog("ERROR GP_AutoSizing.cpp(453):", "");;}

	return nItem;
}

BOOL GP_AutoSizing::SetMinPos(HWND ihWnd, long MinTop, long MinLeft, long MinBottom, long MinRight)
{
	BOOL ret=FALSE;
	int i;
	for(i=0; i<nItem; i++)
		if (aSizingItem[i]!=NULL && aSizingItem[i]->ItemHWND==ihWnd)
		{
			aSizingItem[i]->MinRect.bottom=MinTop;
			aSizingItem[i]->MinRect.bottom=MinLeft;
			aSizingItem[i]->MinRect.bottom=MinBottom;
			aSizingItem[i]->MinRect.bottom=MinRight;
			ret=TRUE;
		}

	if (ihWnd==MainSizingItem.ItemHWND)
	{
		MainSizingItem.MinRect.bottom=MinTop;
		MainSizingItem.MinRect.bottom=MinLeft;
		MainSizingItem.MinRect.bottom=MinBottom;
		MainSizingItem.MinRect.bottom=MinRight;
		ret=TRUE;
	}



	return ret;
}

BOOL GP_AutoSizing::SetMaxPos(HWND ihWnd, long MaxTop, long MaxLeft, long MaxBottom, long MaxRight)
{
	BOOL ret=FALSE;
	int i;
	for(i=0; i<nItem; i++)
		if (aSizingItem[i]!=NULL && aSizingItem[i]->ItemHWND==ihWnd)
		{
			aSizingItem[i]->MaxRect.bottom=MaxTop;
			aSizingItem[i]->MaxRect.bottom=MaxLeft;
			aSizingItem[i]->MaxRect.bottom=MaxBottom;
			aSizingItem[i]->MaxRect.bottom=MaxRight;
			ret=TRUE;
		}

	if (ihWnd==MainSizingItem.ItemHWND)
	{
		MainSizingItem.MaxRect.bottom=MaxTop;
		MainSizingItem.MaxRect.bottom=MaxLeft;
		MainSizingItem.MaxRect.bottom=MaxBottom;
		MainSizingItem.MaxRect.bottom=MaxRight;
		ret=TRUE;
	}

	return ret;
}

BOOL GP_AutoSizing::SetMaxSize(HWND ihWnd, long iMaxWidth, long iMaxHeight)
{
	BOOL ret=FALSE;
	int i;
	for(i=0; i<nItem; i++)
		if (aSizingItem[i]!=NULL && aSizingItem[i]->ItemHWND==ihWnd)
		{
			aSizingItem[i]->MaxSize.cx=iMaxWidth;
			aSizingItem[i]->MaxSize.cy=iMaxHeight;
			ret=TRUE;
		}

	if (ihWnd==MainSizingItem.ItemHWND)
	{
		MainSizingItem.MaxSize.cx=iMaxWidth;
		MainSizingItem.MaxSize.cy=iMaxHeight;
		ret=TRUE;
	}
	return ret;
}

BOOL GP_AutoSizing::SetMinSize(HWND ihWnd, long iMinWidth, long iMinHeight)
{
	BOOL ret=FALSE;
	int i;
	for(i=0; i<nItem; i++)
		if (aSizingItem[i]!=NULL && aSizingItem[i]->ItemHWND==ihWnd)
		{
			aSizingItem[i]->MinSize.cx=iMinWidth;
			aSizingItem[i]->MinSize.cy=iMinHeight;
			ret=TRUE;
		}

	if (ihWnd==MainSizingItem.ItemHWND)
	{
		MainSizingItem.MinSize.cx=iMinWidth;
		MainSizingItem.MinSize.cy=iMinHeight;
		ret=TRUE;
	}

	return ret;
}


BOOL GP_AutoSizing::InitSizing()
{
	nItem=0;
	int i;
	for(i=0;i<nBuff;i++)
	{
		if (aSizingItem[i]!=NULL) delete aSizingItem[i];
			aSizingItem[i]=NULL;
	}

	MainSizingItem.ItemHWND=MainSizingItem.MainHWND=NULL;
	return TRUE;
}

BOOL GP_AutoSizing::CheckAndUpdate(SIZINGITEM Item, CRect &QurentRect)
{
	int CV=-10000;
	BOOL ret=FALSE;

	if (Item.MinSize.cx	>CV && QurentRect.Width()<Item.MinSize.cx)	{ret=TRUE; QurentRect.right=QurentRect.left+Item.MinSize.cx;}
	else
	if (Item.MaxSize.cx>CV && QurentRect.Width()>Item.MaxSize.cx)	{ret=TRUE; QurentRect.right=QurentRect.left+Item.MaxSize.cx;}

	if (Item.MinSize.cy	>CV && QurentRect.Height()	<Item.MinSize.cy)	{ret=TRUE; QurentRect.bottom=QurentRect.top+Item.MinSize.cy;}
	else
	if (Item.MaxSize.cy>CV && QurentRect.Height()	>Item.MaxSize.cy)	{ret=TRUE; QurentRect.bottom=QurentRect.top+Item.MaxSize.cy;}

	if (Item.MinRect.bottom>CV && QurentRect.bottom>Item.MinRect.bottom)	{ret=TRUE; QurentRect.bottom=Item.MinRect.bottom;}
	else
	if (Item.MaxRect.bottom>CV && QurentRect.bottom<Item.MaxRect.bottom)	{ret=TRUE; QurentRect.bottom=Item.MaxRect.bottom;}

	if (Item.MinRect.top>CV && QurentRect.top>Item.MinRect.top)	{ret=TRUE; QurentRect.top=Item.MinRect.top;}
	else
	if (Item.MaxRect.top>CV && QurentRect.top<Item.MaxRect.top)	{ret=TRUE; QurentRect.top=Item.MaxRect.top;}

	if (Item.MinRect.left>CV && QurentRect.left	>Item.MinRect.left)	{ret=TRUE; QurentRect.left=Item.MinRect.left;}
	else
	if (Item.MaxRect.left>CV && QurentRect.left	<Item.MaxRect.left)	{ret=TRUE; QurentRect.left=Item.MaxRect.left;}

	if (Item.MinRect.right>CV && QurentRect.right>Item.MinRect.right)	{ret=TRUE; QurentRect.right=Item.MinRect.right;}
	else
	if (Item.MaxRect.right>CV && QurentRect.right<Item.MaxRect.right)	{ret=TRUE; QurentRect.right=Item.MaxRect.right;}

//	if (ret!=FALSE)
	{
//			QurentRect.OffsetRect(SmeLocal);
		try
		{
			if (ret ||	Item.ItemHWND!=MainSizingItem.ItemHWND)
				::MoveWindow(Item.ItemHWND,QurentRect.left,QurentRect.top,QurentRect.right-QurentRect.left,QurentRect.bottom-QurentRect.top,TRUE);
			//ReinitSize(Item.ItemHWND,Item.MainHWND);
		}
		catch(...)
		{GPWriteErrorLog("ERROR GP_AutoSizing.cpp(602):", "");;}
//		::InvalidateRect(Item.ItemHWND,QurentRect,TRUE);
	}


	return TRUE;
}

void GP_AutoSizing::SetNewStyle(HWND ihWnd, const char *iString)
{
	int i;
	for(i=0; i<nItem; i++)
		if (aSizingItem[i]!=NULL && aSizingItem[i]->ItemHWND==ihWnd)
		{
			UINT StlSign=0;
			if (*iString=='-')  {StlSign=0x10000;iString++;} else StlSign=0;
			aSizingItem[i]->StyleTop=(*(iString++))|StlSign;
			if (*iString=='-')  {StlSign=0x10000;iString++;} else StlSign=0;
			aSizingItem[i]->StyleLeft=(*(iString++))|StlSign;
			if (*iString=='-')  {StlSign=0x10000;iString++;} else StlSign=0;
			aSizingItem[i]->StyleBottom=(*(iString++))|StlSign;
			if (*iString=='-')  {StlSign=0x10000;iString++;} else StlSign=0;
			aSizingItem[i]->StyleRight=(*(iString++))|StlSign;
		}
}


void GP_AutoSizing::ReinitSize(HWND ihWnd)
{
	int i;
	for(i=0; i<nItem; i++)
		if (aSizingItem[i]!=NULL && aSizingItem[i]->ItemHWND==ihWnd)
			ReinitItemSize(i);
}

void GP_AutoSizing::SetNewSize(HWND ihWnd, CRect newRect)
{
	if (ihWnd!=NULL)
	{
		::MoveWindow(ihWnd,newRect.left,newRect.top,newRect.right-newRect.left,newRect.bottom-newRect.top,TRUE);
		CWnd::FromHandle(ihWnd)->Invalidate();
	}
	ReinitSize(ihWnd);
}

void GP_AutoSizing::SetNewMainSize(CRect &NewRect, UINT Flag)
{

	MainSizingItem.InitialRectW=MainSizingItem.InitialRect=MainSizingItem.EtalonRectW=MainSizingItem.EtalonRect=NewRect;
	MainSizingItem.MaxRect=MainSizingItem.MinRect=CRect(-11111,-11111,-11111,-11111);
	MainSizingItem.MaxSize=MainSizingItem.MinSize=CSize(-11111,-11111);

	::MoveWindow(MainSizingItem.ItemHWND,NewRect.left,NewRect.top,NewRect.right-NewRect.left,NewRect.bottom-NewRect.top,TRUE);
	CWnd::FromHandle(MainSizingItem.ItemHWND)->Invalidate();

	CRect MainWindowRect;
	::GetWindowRect(MainSizingItem.ItemHWND,&MainWindowRect);
	::ScreenToClient(MainSizingItem.ItemHWND,(POINT *)((LPRECT)MainWindowRect));
	::ScreenToClient(MainSizingItem.ItemHWND,((POINT *)((LPRECT)MainWindowRect))+1);

	CRect MainClientRect;
	::GetClientRect(MainSizingItem.ItemHWND,MainClientRect);

	CPoint Sme(0,0);
	::ClientToScreen(MainSizingItem.ItemHWND,&Sme);
	CRect tmpRect;
	::GetWindowRect(MainSizingItem.ItemHWND,&tmpRect);

	int i;
	char *done=new char [nItem];

	for(i=0;i<nItem;i++) done[i]=0;

	if (Flag!=0)
	{
		for(i=0;i<nItem;i++)
			if (aSizingItem[i]!=NULL && aSizingItem[i]->MainHWND==MainSizingItem.ItemHWND)
			{
				aSizingItem[i]->EtalonRect=MainClientRect;
				aSizingItem[i]->EtalonRectW=MainWindowRect;
				::GetWindowRect(aSizingItem[i]->ItemHWND,&aSizingItem[i]->InitialRect);
				aSizingItem[i]->InitialRectW=aSizingItem[i]->InitialRect;
				aSizingItem[i]->InitialRect.OffsetRect(-Sme);
				aSizingItem[i]->InitialRectW.OffsetRect(-tmpRect.TopLeft());
				if (Flag==2)
				{
					aSizingItem[i]->MaxRect=aSizingItem[i]->MinRect=CRect(-11111,-11111,-11111,-11111);
					aSizingItem[i]->MaxSize=aSizingItem[i]->MinSize=CSize(-11111,-11111);
				}
				done[i]=1;
			}

		int flg=-1,oldflg;
		do
		{
			oldflg=flg;
			flg=0;
			for(i=0;i<nItem;i++)
				if (aSizingItem[i]!=NULL && done[i]==0)
				{
					flg++;
					int j;
					for(j=0;j<nItem;j++)
						if (aSizingItem[j]!=NULL && aSizingItem[i]->MainHWND==aSizingItem[j]->ItemHWND && done[j]!=0)
						{
							done[i]=1;
							if (aSizingItem[i]->MainHWND!=NULL)
							{
								::GetClientRect(aSizingItem[i]->MainHWND,&aSizingItem[i]->EtalonRect);
								::GetWindowRect(aSizingItem[i]->MainHWND,&aSizingItem[i]->EtalonRectW);
								::ClientToScreen(aSizingItem[i]->MainHWND,(LPPOINT)((LPRECT)aSizingItem[i]->EtalonRect));
								::ClientToScreen(aSizingItem[i]->MainHWND,(LPPOINT)((LPRECT)aSizingItem[i]->EtalonRect)+1);
								CPoint Sme1(0,0);
								::ClientToScreen(MainSizingItem.ItemHWND,&Sme1);
								CRect tmpRect1;
								::GetWindowRect(MainSizingItem.ItemHWND,&tmpRect1);

								aSizingItem[i]->EtalonRect.OffsetRect(-Sme1);
								aSizingItem[i]->EtalonRectW.OffsetRect(-tmpRect1.TopLeft());
								::GetWindowRect(aSizingItem[i]->ItemHWND,&aSizingItem[i]->InitialRect);
								aSizingItem[i]->InitialRectW=aSizingItem[i]->InitialRect;
								aSizingItem[i]->InitialRect.OffsetRect(-Sme1);
								aSizingItem[i]->InitialRectW.OffsetRect(-tmpRect1.TopLeft());

								if (Flag==2)
								{
									aSizingItem[i]->MaxRect=aSizingItem[i]->MinRect=CRect(-11111,-11111,-11111,-11111);
									aSizingItem[i]->MaxSize=aSizingItem[i]->MinSize=CSize(-11111,-11111);
								}

							}
							break;
						}
				}
		}while(flg!=oldflg);
	}

	delete[] done;
	UpdateSize();

}

HWND GP_AutoSizing::GetResizingOwner(HWND iHWND)
{
	HWND ret=NULL;

	if (iHWND==MainSizingItem.ItemHWND) ret=iHWND;
	else
	{
		int i;
		for(i=0; i<nItem && !ret; i++)
			if (aSizingItem[i]!=NULL && aSizingItem[i]->ItemHWND==iHWND)
				ret=aSizingItem[i]->MainHWND;
	}
	return ret;
}

char * GP_AutoSizing::GetSizingStyle(HWND iHWND)
{
	static char ret[10];
	strcpy(ret,"NNNN");
	int i;
	for(i=0; i<nItem; i++)
		if (aSizingItem[i]!=NULL && aSizingItem[i]->ItemHWND==iHWND)
		{
			char *tmp=ret;
			if ((aSizingItem[i]->StyleLeft&0x10000)!=0) *(tmp++)='-';
			*(tmp++)=(char)(aSizingItem[i]->StyleLeft&0xFFFF);
			if ((aSizingItem[i]->StyleTop&0x10000)!=0) *(tmp++)='-';
			*(tmp++)=(char)(aSizingItem[i]->StyleTop&0xFFFF);
			if ((aSizingItem[i]->StyleRight&0x10000)!=0) *(tmp++)='-';
			*(tmp++)=(char)(aSizingItem[i]->StyleRight&0xFFFF);
			if ((aSizingItem[i]->StyleBottom&0x10000)!=0) *(tmp++)='-';
			*(tmp++)=(char)(aSizingItem[i]->StyleBottom&0xFFFF);
			*(tmp++)=0;
			break;
		}
	return ret;
}

void GP_AutoSizing::DeleteWndEx(HWND ihWnd, HWND ownerHWND)
{
	int i;

	for(i=0; i<nItem; i++)
		if (aSizingItem[i]!=NULL && aSizingItem[i]->ItemHWND==ihWnd && aSizingItem[i]->MainHWND==ownerHWND) break;

	if (i!=nItem)
	{
		nItem--;
		delete aSizingItem[i];
		int j;
		for(j=i; j<nItem; j++)
			aSizingItem[j]=aSizingItem[j+1];

		aSizingItem[j]=NULL;
	}
}

void GP_AutoSizing::UpdateSize(HWND iHWND)
{
	if (m_Pause==0)
	{
		int i;
		for(i=0; i<nItem; i++)
			if (aSizingItem[i]!=NULL && aSizingItem[i]->ItemHWND==iHWND) break;

		if (i<nItem)
		{
			int j;
			for(j=0; j<nItem; j++)
				if (aSizingItem[j]!=NULL && (aSizingItem[j]->MainHWND==iHWND/* || ::GetParent(aSizingItem[j]->ItemHWND)==iHWND*/)) break;

			if (j<nItem) UpdateSize();
		}
	}
}

void GP_AutoSizing::ReinitSize(HWND ihWnd, HWND iMainHWND)
{
	int i;
	for(i=0; i<nItem; i++)
		if (aSizingItem[i]!=NULL && aSizingItem[i]->ItemHWND==ihWnd && aSizingItem[i]->MainHWND==iMainHWND)
			ReinitItemSize(i);
}

void GP_AutoSizing::ReinitItemSize(int inItem)
{
	if (inItem>=0 && inItem<nItem && aSizingItem[inItem])
	{
		if (aSizingItem[inItem]->MainHWND==MainSizingItem.ItemHWND)
		{
			CPoint Sme(0,0);
			::GetClientRect(aSizingItem[inItem]->MainHWND,&aSizingItem[inItem]->EtalonRect);
			::GetWindowRect(aSizingItem[inItem]->MainHWND,&aSizingItem[inItem]->EtalonRectW);
			::ScreenToClient(aSizingItem[inItem]->MainHWND,(LPPOINT)((LPRECT)aSizingItem[inItem]->EtalonRectW));
			::ScreenToClient(aSizingItem[inItem]->MainHWND,((LPPOINT)((LPRECT)aSizingItem[inItem]->EtalonRectW))+1);
			CRect tmpRect;

			if (::GetParent(aSizingItem[inItem]->ItemHWND)!=MainSizingItem.ItemHWND)
			{
				::ClientToScreen(::GetParent(aSizingItem[inItem]->ItemHWND),&Sme);
				::GetWindowRect(::GetParent(aSizingItem[inItem]->ItemHWND),&tmpRect);
			}
			else
			{
				::ClientToScreen(aSizingItem[inItem]->MainHWND,&Sme);
				::GetWindowRect(aSizingItem[inItem]->MainHWND,&tmpRect);
			}

			::GetWindowRect(aSizingItem[inItem]->ItemHWND,&aSizingItem[inItem]->InitialRect);
			aSizingItem[inItem]->InitialRectW=aSizingItem[inItem]->InitialRect;
			aSizingItem[inItem]->InitialRect.OffsetRect(-Sme);
			aSizingItem[inItem]->InitialRectW.OffsetRect(-tmpRect.TopLeft());
		}
		else
		{
			CPoint Sme(0,0);
			::GetClientRect(aSizingItem[inItem]->MainHWND,&aSizingItem[inItem]->EtalonRect);
			::GetWindowRect(aSizingItem[inItem]->MainHWND,&aSizingItem[inItem]->EtalonRectW);
			::ScreenToClient(aSizingItem[inItem]->MainHWND,(LPPOINT)((LPRECT)aSizingItem[inItem]->EtalonRectW));
			::ScreenToClient(aSizingItem[inItem]->MainHWND,((LPPOINT)((LPRECT)aSizingItem[inItem]->EtalonRectW))+1);
			HWND tmpHWND;
			CRect tmpRect;
			if (::GetParent(aSizingItem[inItem]->ItemHWND)!=MainSizingItem.ItemHWND)
			{
				tmpHWND=::GetParent(aSizingItem[inItem]->MainHWND);
				::ClientToScreen(tmpHWND,&Sme);
				::GetWindowRect(tmpHWND,&tmpRect);
			}
			else
			{
				tmpHWND=aSizingItem[inItem]->MainHWND;
				::ClientToScreen(MainSizingItem.ItemHWND,&Sme);
				::GetWindowRect(MainSizingItem.ItemHWND,&tmpRect);
			}
			::ClientToScreen(tmpHWND,(LPPOINT)((LPRECT)&aSizingItem[inItem]->EtalonRect));
			::ClientToScreen(tmpHWND,((LPPOINT)((LPRECT)&aSizingItem[inItem]->EtalonRect))+1);
			::ClientToScreen(tmpHWND,(LPPOINT)((LPRECT)&aSizingItem[inItem]->EtalonRectW));
			::ClientToScreen(tmpHWND,((LPPOINT)((LPRECT)&aSizingItem[inItem]->EtalonRectW))+1);
			aSizingItem[inItem]->EtalonRect.OffsetRect(-Sme);
			aSizingItem[inItem]->EtalonRectW.OffsetRect(-tmpRect.TopLeft());


			::GetWindowRect(aSizingItem[inItem]->ItemHWND,&aSizingItem[inItem]->InitialRect);
			aSizingItem[inItem]->InitialRectW=aSizingItem[inItem]->InitialRect;
			aSizingItem[inItem]->InitialRect.OffsetRect(-Sme);
			aSizingItem[inItem]->InitialRectW.OffsetRect(-tmpRect.TopLeft());
		}

		int CV=-10000;
		if (aSizingItem[inItem]->MinSize.cx	>CV && aSizingItem[inItem]->InitialRect.Width()<aSizingItem[inItem]->MinSize.cx)
			aSizingItem[inItem]->MinSize.cx=aSizingItem[inItem]->InitialRect.Width();
		else
		if (aSizingItem[inItem]->MaxSize.cx>CV && aSizingItem[inItem]->InitialRect.Width()>aSizingItem[inItem]->MaxSize.cx)
			aSizingItem[inItem]->MaxSize.cx=aSizingItem[inItem]->InitialRect.Width();

		if (aSizingItem[inItem]->MinSize.cy	>CV && aSizingItem[inItem]->InitialRect.Height()	<aSizingItem[inItem]->MinSize.cy)
			aSizingItem[inItem]->MinSize.cy=aSizingItem[inItem]->InitialRect.Height();
		else
		if (aSizingItem[inItem]->MaxSize.cy>CV && aSizingItem[inItem]->InitialRect.Height()	>aSizingItem[inItem]->MaxSize.cy)
			aSizingItem[inItem]->MaxSize.cy=aSizingItem[inItem]->InitialRect.Height();

		if (aSizingItem[inItem]->MinRect.bottom>CV && aSizingItem[inItem]->InitialRect.bottom>aSizingItem[inItem]->MinRect.bottom)
			aSizingItem[inItem]->MinRect.bottom=aSizingItem[inItem]->InitialRect.bottom;
		else
		if (aSizingItem[inItem]->MaxRect.bottom>CV && aSizingItem[inItem]->InitialRect.bottom<aSizingItem[inItem]->MaxRect.bottom)
			aSizingItem[inItem]->MaxRect.bottom=aSizingItem[inItem]->InitialRect.bottom;

		if (aSizingItem[inItem]->MinRect.top>CV && aSizingItem[inItem]->InitialRect.top>aSizingItem[inItem]->MinRect.top)
			aSizingItem[inItem]->MinRect.top=aSizingItem[inItem]->InitialRect.top;
		else
		if (aSizingItem[inItem]->MaxRect.top>CV && aSizingItem[inItem]->InitialRect.top<aSizingItem[inItem]->MaxRect.top)
			aSizingItem[inItem]->MinRect.top=aSizingItem[inItem]->InitialRect.top;

		if (aSizingItem[inItem]->MinRect.left>CV && aSizingItem[inItem]->InitialRect.left	>aSizingItem[inItem]->MinRect.left)
			aSizingItem[inItem]->MinRect.left=aSizingItem[inItem]->InitialRect.left;
		else
		if (aSizingItem[inItem]->MaxRect.left>CV && aSizingItem[inItem]->InitialRect.left	<aSizingItem[inItem]->MaxRect.left)
			aSizingItem[inItem]->MaxRect.left=aSizingItem[inItem]->InitialRect.left;

		if (aSizingItem[inItem]->MinRect.right>CV && aSizingItem[inItem]->InitialRect.right>aSizingItem[inItem]->MinRect.right)
			aSizingItem[inItem]->MinRect.right=aSizingItem[inItem]->InitialRect.right;
		else
		if (aSizingItem[inItem]->MaxRect.right>CV && aSizingItem[inItem]->InitialRect.right<aSizingItem[inItem]->MaxRect.right)
			aSizingItem[inItem]->MaxRect.right=aSizingItem[inItem]->InitialRect.right;
	}
}

void GP_AutoSizing::DeleteAll()
{
	if (aSizingItem!=NULL)
	{
		int i;
		for(i=0; i<nItem;i++)
		{
			if (aSizingItem[i]!=NULL) delete aSizingItem[i];
			aSizingItem[i]=NULL;
		}
	}
}

const SIZINGITEM * GP_AutoSizing::GetMainItem()
{
	return &MainSizingItem;
}

void GP_AutoSizing::AutoSizingPause()
{
	m_Pause=1;
}

void GP_AutoSizing::AutoSizingResume()
{
	m_Pause=0;
}

DWORD GP_AutoSizing::GetState()
{
	return m_Pause;
}

void GP_AutoSizing::ReinitSize()
{
	int i;
	for(i=0; i<nItem; i++)
		if (aSizingItem[i]) ReinitItemSize(i);
}

BOOL GP_AutoSizing::CheckMainSize(HWND iHWND, UINT nType, int *cx, int *cy)
{
	BOOL ret=TRUE;
	switch(nType)
	{
	case SIZE_MINIMIZED:
		break;
	default:
		if (*cx>0 && *cy>0)
		{
			if (*cx<MainSizingItem.MinSize.cx || *cy<MainSizingItem.MinSize.cy)
				ret=FALSE;
		}
		break;
	}

	return ret;
}

int GP_AutoSizing::GetOwnedArray(HWND iOwner, HWND **oArray)
{
	int ret=0;
	*oArray=NULL;
	if (nItem)
	{
		*oArray=new HWND [nItem+10];
		int i;
		for(i=0;i<nItem;i++)
			(*oArray)[i]=NULL;

		for(i=0;i<nItem;i++)
			if (aSizingItem[i]->MainHWND==iOwner)
				(*oArray)[ret++]=aSizingItem[i]->ItemHWND;

		if (ret==0) 
		{
			delete[] *oArray;
			*oArray=NULL;
		}
	}
	return ret;
}
