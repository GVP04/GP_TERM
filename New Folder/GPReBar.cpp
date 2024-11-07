// GPReBar.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPReBar.h"
#include "GPReBarCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// GPReBar
const UINT GPReBar::uNMethods=34;
const char *GPReBar::cArrMethods[]={
		"UpdateGroup","GetBandCount","GetBandInfo","GetBarHeight","GetBarInfo",
		"GetBkColor","GetDropTarget","GetRect","GetRowCount","GetRowHeight",
		"GetTextColor","GetToolTips","IDToIndex","SetBandInfo","SetBarInfo",
		"SetBkColor","SetTextColor","SetToolTips","GetImageList","SetImageList",
		"GetBandBorders","GetPalette","SetPalette","BeginDrag","DeleteBand",
		"DragMove","EndDrag","HitTest","InsertBand","MaximizeBand",
		"MinimizeBand","ShowBand","SizeToRect","MoveBand","",
		"","","","",
		"","","", "", "", 
	};
const char *GPReBar::cArrMethodsParams[]={
		"","","uBand","","",
		"","Not Present","uBand","","uRow",
		"","Not Present","uBandID","uBand,BACKGROUND=...;CHILD=...;CHILDSIZE=...;COLORS=...;HEADERSIZE=...;IDEALSIZE=...;ID=...;IMAGE=...;LPARAM=...;SIZE=...;STYLE=...;TEXT=...;","ImageListName",
		"r,g,b","r,g,b","Not Present","","ImageListName",
		"uBand","","palVersion,peRed1]peGreen1]peBlue1^peRed2]peGreen2]peBlue2^.....","uBand","uBand",
		"","","ptx,pty","uBand,BACKGROUND=...;CHILD=...;CHILDSIZE=...;COLORS=...;HEADERSIZE=...;IDEALSIZE=...;ID=...;IMAGE=...;LPARAM=...;SIZE=...;STYLE=...;TEXT=...;","uBand",
		"uBand","uBand,bShow","Left,Top,Right,Bottom","uFrom,uTo","",
		"","","","",
		"","","", "", "", 
	};


GPReBar::GPReBar(UINT iUnitId)
{
	referGPU=NULL;
	UnitId=iUnitId;
}

GPReBar::~GPReBar()
{
}


BEGIN_MESSAGE_MAP(GPReBar, CReBar)
	//{{AFX_MSG_MAP(GPReBar)
	ON_WM_PARENTNOTIFY()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_WM_NCHITTEST()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPReBar message handlers



UINT GPReBar::DoMethod(const char *iStr, char *oStr)
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
	}

	int retint=-123456;
	int atoipos=atoi(pos);

	try
	{
		switch(nfunc)
		{
		case 0: /*UpdateGroup*/
			if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
				referGPU[UnitId&0xFFFF]->UpdateGroup(-123456,GetStyle());
			break;
		case 1: /*GetBandCount*/	retint=GetReBarCtrl().GetBandCount();		break;
		case 2: /*GetBandInfo*/
			if (oStr!=NULL)
			{
				UINT i;
				REBARBANDINFO rbi={0};
				char txt[500];
				rbi.cbSize =sizeof(rbi);
				rbi.fMask=0xFFFF;
				rbi.lpText=txt;
				rbi.cch=450;
				GetReBarCtrl().GetBandInfo(atoipos,&rbi);

				int nObjChild=-1;
				if (referGPU!=NULL)
				{
					for(i=1;i<(*referGPU)->m_NGPUNIT;i++)
						if (referGPU[i]!=NULL && referGPU[i]->UnitHWND==rbi.hwndChild)
							{nObjChild=i;break;}
				}
				char cStl[500];*cStl=0;
				for(i=0;i<GPReBarCtrl::uNBandStyle;i++)
					if ((rbi.fStyle&GPReBarCtrl::uBandStyle[i])==GPReBarCtrl::uBandStyle[i])
					{
						if (*cStl!=0) strcat(cStl,"|");
						strcat(cStl,GPReBarCtrl::aBandStyle[i]);
					}

				sprintf(oStr,"%s\x7F%d\x7%d\x7%d\x7F%d\x7%d\x7%d\x7F%s\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d",
					cStl,
					GetRValue(rbi.clrFore),GetGValue(rbi.clrFore),GetBValue(rbi.clrFore),
					GetRValue(rbi.clrBack),GetGValue(rbi.clrBack),GetBValue(rbi.clrBack),
					rbi.lpText,
					rbi.iImage,
					nObjChild,
					rbi.cxMinChild,
					rbi.cyMinChild,
					rbi.cx,
					rbi.wID,
					rbi.cyChild,
					rbi.cyMaxChild,
					rbi.cyIntegral,
					rbi.cxIdeal,
					(int)rbi.lParam,
					rbi.cxHeader);
			}
			break;
		case 3: /*GetBarHeight*/	retint=GetReBarCtrl().GetBarHeight();		break;
		case 4: /*GetBarInfo*/
			if (oStr!=NULL)
			{
				REBARINFO rbi={0};
				rbi.cbSize=sizeof(rbi);
				rbi.fMask=RBIM_IMAGELIST;
				GetReBarCtrl().GetBarInfo(&rbi);
				if (rbi.himl)
				{
					int id=GPC.FindImageList(CImageList::FromHandle(rbi.himl));
					if (id>=0) strcpy(oStr,GPC.a_GPImageList[id].ILName);
				}
			}
			break;
		case 5: /*GetBkColor*/
			if (oStr!=NULL)
			{
				UINT cref=GetReBarCtrl().GetBkColor();
				sprintf(oStr,"%d\x07%d\x07%d",GetRValue(cref),GetGValue(cref),GetBValue(cref));
			}
			break;
		case 7: /*GetRect*/
			if (oStr!=NULL)
			{
				CRect re;
				if (GetReBarCtrl().GetRect(atoipos,&re))
					sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
			}
			break;
		case 8: /*GetRowCount*/		retint=GetReBarCtrl().GetRowCount();			break;
		case 9: /*GetRowHeight*/	retint=GetReBarCtrl().GetRowHeight(atoipos);	break;
		case 10: /*GetTextColor*/
			if (oStr!=NULL)
			{
				UINT cref=GetReBarCtrl().GetTextColor();
				sprintf(oStr,"%d\x07%d\x07%d",GetRValue(cref),GetGValue(cref),GetBValue(cref));
			}
			break;
		case 12: /*IDToIndex*/		retint=GetReBarCtrl().IDToIndex(atoipos);		break;
		case 13: /*SetBandInfo*/
		case 28: /*InsertBand*/
			{
				UINT i;
				REBARBANDINFO rbi={0};
				rbi.cbSize =sizeof(rbi);

				char *tmppos=new char [(int)strlen(pos)+10];
				strcpy(tmppos,pos);
				char *cpos[50/*GPReBarCtrl::uNBandMask*/],*pos2;

				for(i=0;i<GPReBarCtrl::uNBandMask;i++)
				{
					char tmp[25];
					sprintf(tmp,"%s=",GPReBarCtrl::aBandMask[i]);
					cpos[i]=strstr(tmppos,tmp);
					if (cpos[i]!=NULL) cpos[i]+=(int)strlen(GPReBarCtrl::aBandMask[i])+1;
				}

				HICON tmpHICON=NULL;

				for(i=0;i<GPReBarCtrl::uNBandMask;i++)
					if (cpos[i]!=NULL)
					{
						if ((pos2=strchr(cpos[i],';'))!=NULL) *pos2=0;
						if (i!=11) _strupr(cpos[i]);

						switch(i)
						{
						case 0:/*BACKGROUND*/
							{
								int num;
								char *postmp=strchr(cpos[i],',');
								rbi.fMask|=GPReBarCtrl::uBandMask[i];
								rbi.hbmBack=NULL;
								if (postmp && (num=GPC.GetImageListId(++postmp))>=0)
								{
									rbi.hbmBack=GPC.a_GPImageList[num].CreateBitmap(atoi(cpos[i]),GetReBarCtrl().GetBkColor());
								}
							}
							break;
						case 1:/*CHILD*/
							if (referGPU!=NULL)
							{
								UINT nUnit=atoi(cpos[i]);
								if (nUnit<(*referGPU)->m_NGPUNIT && referGPU[nUnit] && referGPU[nUnit]->UnitHWND)
								{
									rbi.hwndChild=referGPU[nUnit]->UnitHWND;
									rbi.fMask|=GPReBarCtrl::uBandMask[i];
								}
							}
							break;
						case 2:/*CHILDSIZE*/
							m_LastScanf=sscanf(cpos[i],"%d,%d,%d,%d,%d",&rbi.cxMinChild,&rbi.cyMinChild,&rbi.cyChild,&rbi.cyMaxChild,&rbi.cyIntegral);
							rbi.fMask|=GPReBarCtrl::uBandMask[i];
							break;
						case 3:/*COLORS*/
							{
								int fR=255,fG=255,fB=255,bR=0,bG=0,bB=0;
								m_LastScanf=sscanf(cpos[i],"%d,%d,%d,%d,%d,%d",&fR,&fG,&fB,&bR,&bG,&bB);
								rbi.clrFore=RGB(fR,fG,fB);
								rbi.clrBack=RGB(bR,bG,bB);
								rbi.fMask|=GPReBarCtrl::uBandMask[i];
							}
							break;
						case 4:/*HEADERSIZE*/
							rbi.cxHeader=atoi(cpos[i]);
							rbi.fMask|=GPReBarCtrl::uBandMask[i];
							break;
						case 5:/*IDEALSIZE*/
							rbi.cxIdeal=atoi(cpos[i]);
							rbi.fMask|=GPReBarCtrl::uBandMask[i];
							break;
						case 6:/*ID*/
							rbi.wID=atoi(cpos[i]);
							rbi.fMask|=GPReBarCtrl::uBandMask[i];
							break;
						case 7:/*IMAGE*/
							rbi.iImage=atoi(cpos[i]);
							rbi.fMask|=GPReBarCtrl::uBandMask[i];
							break;
						case 8:/*LPARAM*/
							rbi.lParam=atoi(cpos[i]);
							rbi.fMask|=GPReBarCtrl::uBandMask[i];
							break;
						case 9:/*SIZE*/
							rbi.cx=atoi(cpos[i]);
							rbi.fMask|=GPReBarCtrl::uBandMask[i];
							break;
						case 10:/*STYLE*/
							{
								UINT j;
								for(j=0;j<GPReBarCtrl::uNBandStyle;j++)
									if (strstr(cpos[i],GPReBarCtrl::aBandStyle[j])!=NULL)
										rbi.fStyle|=GPReBarCtrl::uBandStyle[j];

								rbi.fMask|=GPReBarCtrl::uBandMask[i];
							}
							break;
						case 11:/*TEXT*/
							rbi.lpText=cpos[i];
							rbi.cch=(int)strlen(cpos[i])+1;
							break;
						}
					}
				if (nfunc==13)		retint=GetReBarCtrl().SetBandInfo(atoipos,&rbi);
				else				retint=GetReBarCtrl().InsertBand(atoipos,&rbi);

				if (tmpHICON!=NULL) DestroyIcon(tmpHICON);
				delete[] tmppos;
			}
			break;
		case 14: /*SetBarInfo*/
			{
				REBARINFO rbi={0};
				rbi.cbSize=sizeof(rbi);
				rbi.fMask=RBIM_IMAGELIST;
				int num;
				if ((num=GPC.GetImageListId(pos))>=0)
				{
					rbi.himl=GPC.a_GPImageList[num].m_IL.m_hImageList;
					GetReBarCtrl().SetBarInfo(&rbi);
				}
			}
			break;
		case 15: /*SetBkColor*/
		case 16: /*SetTextColor*/
			{
				UINT r=0,g=0,b=0,cref=0;
				m_LastScanf=sscanf(pos,"%d,%d,%d",&r,&g,&b);
				cref=((nfunc==15)?GetReBarCtrl().SetBkColor(RGB(r,g,b)):GetReBarCtrl().SetTextColor(RGB(r,g,b)));
				if (oStr!=NULL)
					sprintf(oStr,"%d\x07%d\x07%d",GetRValue(cref),GetGValue(cref),GetBValue(cref));
			}
			break;
		case 18: /*GetImageList*/
			if (oStr!=NULL)
			{
					int id=GPC.FindImageList(GetReBarCtrl().GetImageList());
					if (id>=0) strcpy(oStr,GPC.a_GPImageList[id].ILName);
			}
			break;
		case 19: /*SetImageList*/
			{
				int num;
				if ((num=GPC.GetImageListId(pos))>=0)
				{
					retint=GetReBarCtrl().SetImageList(&(GPC.a_GPImageList[num].m_IL));
				}
				else retint=GetReBarCtrl().SetImageList(NULL);
			}
			break;
		case 20: /*GetBandBorders*/
			if (oStr!=NULL)
			{
				CRect re(0,0,0,0);
				GetReBarCtrl().GetBandBorders(atoipos,&re);
				sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
			}
			break;
		case 21: /*GetPalette*/
			if (oStr!=NULL)
			{
				CPalette* tmpPal=GetReBarCtrl().GetPalette( );
				if (tmpPal!=NULL)
				{
					int nEntrie=tmpPal->GetEntryCount();
					char *outpos=oStr;
					PALETTEENTRY PalEn;
					PalEn.peFlags=0;
					int i;
					for(i=0;i<nEntrie;i++)
						if (tmpPal->GetPaletteEntries(i,1,&PalEn)==1)
						{
							if (i>0)  *(outpos++)=0x7F;
							outpos+=sprintf(outpos,"%d\x7%d\x7%d",PalEn.peRed,PalEn.peGreen,PalEn.peBlue);
						}
				}
			}
			break;
		case 22: /*SetPalette*/
			{
				CPalette pal;
				const char *pos2=pos;
				LOGPALETTE *pPal;
				int nEntry=0;
				while(*pos2!=0)
				{
					while(*pos2!=0 && *pos2!=GPC.DelimiterIn1) pos2++;
					nEntry++;
				}

				pos2=strchr(pos,',');
				if (nEntry>0 && pos2!=NULL)
				{

					pPal = (PLOGPALETTE)LocalAlloc(LMEM_FIXED, sizeof(LOGPALETTE) +	nEntry * sizeof(PALETTEENTRY));
					pPal->palVersion = atoi(pos);
					pPal->palNumEntries = nEntry;
					nEntry=0;
    
					while(*pos2!=0)
					{
						pos2++;
						m_LastScanf=sscanf(pos2,"%d]%d]%d",&(pPal->palPalEntry[nEntry].peRed),&(pPal->palPalEntry[nEntry].peGreen),&(pPal->palPalEntry[nEntry].peBlue));
						while(*pos2!=0 && *pos2!=GPC.DelimiterIn1) pos2++;
						nEntry++;
					}
					pal.CreatePalette(pPal);
					GetReBarCtrl().SetPalette(pal);
					LocalFree(pPal);
				}
			}
			break;
		case 23: /*BeginDrag*/		GetReBarCtrl().BeginDrag(atoipos);				break;
		case 24: /*DeleteBand*/		retint=GetReBarCtrl().DeleteBand(atoipos);		break;
		case 25: /*DragMove*/ 		GetReBarCtrl().DragMove();						break;
		case 26: /*EndDrag*/  		GetReBarCtrl().EndDrag();						break;
		case 27: /*HitTest*/
			if (oStr!=NULL)
			{
				RBHITTESTINFO rbhti={0};
				m_LastScanf=sscanf(pos,"%d,%d",&rbhti.pt.x,&rbhti.pt.y);
				GetReBarCtrl().HitTest(&rbhti);
				sprintf(oStr,"%d\x7F",rbhti.iBand);
				if (rbhti.flags==RBHT_CAPTION)	strcat(oStr,"CAPTION");
				else
				if (rbhti.flags==5/*RBHT_CHEVRON*/)	strcat(oStr,"CHEVRON");
				else
				if (rbhti.flags==RBHT_CLIENT)	strcat(oStr,"CLIENT");
				else
				if (rbhti.flags==RBHT_GRABBER)	strcat(oStr,"GRABBER");
				else
				if (rbhti.flags==RBHT_NOWHERE)	strcat(oStr,"NOWHERE");
				else							strcat(oStr,"OTHER");
			}
			break;
		case 29: /*MaximizeBand*/ 	GetReBarCtrl().MaximizeBand(atoipos);			break;
		case 30: /*MinimizeBand*/ 	GetReBarCtrl().MinimizeBand(atoipos);			break;
		case 31: /*ShowBand*/
			{
				UINT uBand=0, fShow=1;
				m_LastScanf=sscanf(pos,"%d,%d",&uBand, &fShow);
				retint=GetReBarCtrl().ShowBand( uBand, fShow );
			}
			break;
		case 32: /*SizeToRect*/
			{
				CRect rect(0,0,0,0);
				m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&rect.left,&rect.top,&rect.right,&rect.bottom);
				retint=GetReBarCtrl().SizeToRect(rect);
			}
			break;
		case 33: /*MoveBand*/
			{
				UINT uFrom=0, uTo=1;
				m_LastScanf=sscanf(pos,"%d,%d",&uFrom, &uTo);
				retint=GetReBarCtrl().MoveBand( uFrom, uTo );
			}
			break;

		case 6: /*GetDropTarget*/
			break;
		case 11: /*GetToolTips*/
			break;
		case 17: /*SetToolTips*/
			break;
		default:  nfunc=GPUnit::DoControlBarMethod(this,iStr,oStr); break;
		}
	}catch(...)
	{
		char *str=new char [200+(int)strlen(pos)];
		#ifdef RUS
			sprintf(str,"Ошибка выполнения метода %s %s",met,pos);
			MessageBox(str,"Ошибка метода");
		#else
			sprintf(str,"Error execution of method %s %s",met,pos);
			MessageBox(str,"Error execution");
		#endif
		if (oStr!=NULL) strcpy(oStr,str);
		nfunc=0xFFFFFFFFL;
		GPC.m_ErrReport.GPWriteErrorLog("GPReBar", "DoMethod",iStr);
		delete[] str;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
	return nfunc;
}

UINT GPReBar::GPSetProperty(char *iStr)
{
	char *iValue=new char [(int)strlen(iStr)+5];
	strcpy(iValue,iStr);
	UINT ret=1,i;
	char *pos=strchr(iValue,'=');

	if (pos!=NULL && m_hWnd)
	{
		char *prop[]={ "ADDSTYLE", "DELSTYLE","STYLE",  };
		int propnum;
		*(pos++)=0;
		for(propnum=0;propnum<3 && strcmp(prop[propnum],iValue)!=0;propnum++);
		if (propnum>=3) ret=2;
		else
		{
			ret=3;
			switch(propnum)
			{
			case 0: // ADDSTYLE
			case 1: // DELSTYLE
			case 2: // STYLE
				if (m_hWnd!=NULL)
				{
					ret=2;
					int InvFlg=0;
					int tbctrlchange=0;

					char *postmp=strstr(pos,"&U");

					if (postmp!=NULL)
					{
						UINT tmpstl=0;
						m_LastScanf=sscanf(postmp,"&U%X",&tmpstl);
						InvFlg++;
						tbctrlchange=1;
						switch(propnum)
						{
						case 2: /* STYLE*/
						case 0: /* ADDSTYLE*/	GetReBarCtrl().ModifyStyle(0,tmpstl);	break;
						case 1: /* DELSTYLE*/	GetReBarCtrl().ModifyStyle(tmpstl,0);	break;
						}
						if (InvFlg!=0) Invalidate();
					}
					else
					{
						strcat(pos,"|");
						UINT Stl=0;
						switch(propnum)
						{
						case 0: /* ADDSTYLE*/	Stl=GetReBarCtrl().GetStyle();
						case 2: /* STYLE*/
							for(i=0;i<N_REBARCTRL_STYLES;i++)
								if (strstr(pos,aReBarCtrlStyleName[i])!=NULL)
								{
									InvFlg++;
									Stl|=aReBarCtrlStyleUINT[i];
									tbctrlchange=1;
								}
							GetReBarCtrl().ModifyStyle(0,Stl);
							break;
						case 1: /* DELSTYLE*/
							for(i=0;i<N_REBARCTRL_STYLES;i++)
								if (strstr(pos,aReBarCtrlStyleName[i])!=NULL)
								{
									InvFlg++;
									Stl|=aReBarCtrlStyleUINT[i];
									tbctrlchange=1;
								}
							GetReBarCtrl().ModifyStyle(Stl,0);
							break;
						}

						Stl=0;
						switch(propnum)
						{
						case 0: /* ADDSTYLE*/	Stl=GetBarStyle();
						case 2: /* STYLE*/
							for(i=0;i<N_CTRLBAR_STYLES;i++)
								if (strstr(pos,aCtrlBarStyleName[i])!=NULL)
								{
									InvFlg++;
									Stl|=aCtrlBarStyleUINT[i];
								}
							SetBarStyle(Stl);
							break;
						case 1: /* DELSTYLE*/
							for(i=0;i<N_CTRLBAR_STYLES;i++)
								if (strstr(pos,aCtrlBarStyleName[i])!=NULL)
								{
									InvFlg++;
									Stl|=aCtrlBarStyleUINT[i];
								}
							SetBarStyle(GetBarStyle()&(Stl^0xFFFFFFFF));
							break;
						}
					}

					for(i=0;i<N_COMCTRL_STYLES;i++)
						if (strstr(pos,aComCtrlStyleName[i])!=NULL)
						{
							InvFlg++;
							switch(propnum)
							{
							case 2: /* STYLE*/
							case 0: /* ADDSTYLE*/	ModifyStyle(0,aComCtrlStyleUINT[i]);break;
							case 1: /* DELSTYLE*/	ModifyStyle(aComCtrlStyleUINT[i],0);break;
							}
						}

					GetParent()->PostMessage(WM_SIZE,SIZE_RESTORED,0x00000);

					if (InvFlg!=0)
					{
						GetParent()->PostMessage(WM_APP+1);
						Invalidate();
					}
				}
				break;
			default: /* end */
				ret=2;
				break;
			}

		}
		*(--pos)='=';
	}

	delete[] iValue;
	return ret;
}

void GPReBar::OnParentNotify(UINT message, LPARAM lParam)
{
//TRACE("OnParentNotify %X,%d\n",message,lParam);

	char txt[100];
	if (message==WM_CREATE || message==WM_DESTROY)
		sprintf(txt,"%d\x7F%d\x7F%X",message/0x10000,(message&0xFFFF),lParam/0x10000);
	else
		sprintf(txt,"%d\x7F%d\x7F%d\x7F%d",message/0x10000,(message&0xFFFF),lParam/0x10000,(lParam&0xFFFF));
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"ParentNotify",txt);

	CReBar::OnParentNotify(message, lParam);
}



HBRUSH GPReBar::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = NULL;
	if (referGPU && referGPU[UnitId&0xFFFF]->m_brBkgnd) 
	{
		hbr = (HBRUSH) *(referGPU[UnitId&0xFFFF]->m_brBkgnd);
	    RECT rc;
		::GetWindowRect(pWnd->m_hWnd, &rc);
		::MapWindowPoints(NULL, m_hWnd, (POINT *)&rc, 2);
		::SetBrushOrgEx(pDC->m_hDC, -rc.left, -rc.top, NULL);
	}

	if (pWnd && pDC && pWnd->m_hWnd && pDC->m_hDC)
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CReBar::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}

LRESULT GPReBar::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		referGPU[UnitId&0xFFFF]->m_CurMessage.message=message;
		referGPU[UnitId&0xFFFF]->m_CurMessage.wParam=wParam;
		referGPU[UnitId&0xFFFF]->m_CurMessage.lParam=lParam;
		if (referGPU[UnitId&0xFFFF]->DefWindowProc(message, wParam, lParam)) return 0;
	}

	if (message==GPM_SETAUTOSIZE)
		GetParent()->PostMessage(GPM_SETAUTOSIZE,wParam);

	if (message==GPN_UPDATESIZE) GetParent()->SendMessage(GPN_UPDATESIZE);

	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)
	{
		if (message==GPM_CLIENTKILLFOCUS || message==GPM_CLIENTSETFOCUS)
		{
			PGPUNITINFO ui=(PGPUNITINFO)lParam;
			if (ui)
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent
					(m_hWnd, UnitId,message==GPM_CLIENTSETFOCUS?"OnCSetFocus":"OnCKillFocus",GPUnit::UnitInfoToString2(ui,"\x7F"));
		}
		UINT ret;
		if((ret=referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjMessage(m_hWnd, UnitId, message, wParam, lParam))>0) return ret;
		if (message==WM_KEYDOWN && referGPU!=NULL && referGPU[UnitId&0xFFFF]->UnitHotkey && this->m_hWnd!=NULL && IsWindowEnabled()==TRUE && IsWindowVisible()==TRUE)
				if((ret=referGPU[UnitId&0xFFFF]->UnitHotkey->SendHotkeyMessage(message, wParam,lParam))>0) return ret;
		if (message==GPM_PROCHOTKEY)
		{
			if(referGPU[UnitId&0xFFFF]->UnitHotkey && (ret=referGPU[UnitId&0xFFFF]->UnitHotkey->SendHotkeyMessage(WM_KEYDOWN, wParam,lParam))>0) return ret;
			GetParent()->SendMessage(message, wParam,lParam);
		}
		else
		if  (message==WM_KEYDOWN)
			GetParent()->SendMessage(GPM_PROCHOTKEY, wParam,lParam);
	}

	if (message==WM_IDLEUPDATECMDUI) return TRUE;

	switch(message)
	{
	case GPM_DRAGMOUSELEAVE:
		if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDragLeave","");
		break;
	case GPM_DRAGMOUSEMOVE:
		OnMouseDragMove((PGPDRAGDROPSTRUCT)wParam,(LPPOINT)lParam);
		break;
	case GPM_DRAGMOUSEHOVER:
		OnDragMouseHover();
		break;
	case GPM_DROPITEMS:
		OnDragLButtonUp((PGPDRAGDROPSTRUCT)wParam,(LPPOINT)lParam);
		break;
	}

	LRESULT lpr;
	if (message==WM_SETCURSOR && GPC.m_bWaitCursor) lpr=FALSE;
	else lpr=CReBar::WindowProc(message, wParam, lParam);

	return lpr;
}

BOOL GPReBar::PreTranslateMessage(MSG* pMsg)
{
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		if (!referGPU[UnitId&0xFFFF]->DefPreTranslateMessage(pMsg)) return 0;
		referGPU[UnitId&0xFFFF]->m_CurPreMessage=pMsg;
		if (referGPU[UnitId&0xFFFF]->GPMSG)
		{
			UINT ret;
			if (pMsg->message!=WM_KEYDOWN || pMsg->wParam==VK_RETURN || pMsg->wParam==VK_TAB || pMsg->wParam==VK_CANCEL || pMsg->wParam==VK_ESCAPE || pMsg->wParam==VK_HELP)
			{
				if((ret=referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjMessage(m_hWnd, UnitId, pMsg->message, pMsg->wParam, pMsg->lParam))>0) return ret;
				if (pMsg->message==WM_KEYDOWN && referGPU!=NULL && referGPU[UnitId&0xFFFF]->UnitHotkey && this->m_hWnd!=NULL && IsWindowEnabled()==TRUE && IsWindowVisible()==TRUE)
						if((ret=referGPU[UnitId&0xFFFF]->UnitHotkey->SendHotkeyMessage(pMsg->message, pMsg->wParam,pMsg->lParam))>0) return ret;
			}
		}
	}
//TRACE("PRE%X,%d,%d\n",pMsg->message,pMsg->wParam,pMsg->lParam);
	return CReBar::PreTranslateMessage(pMsg);
}

void GPReBar::OnClose()
{

	if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClose","");
//	CReBar::OnClose();
}


BOOL GPReBar::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	NMHDR* lpnm=(NMHDR*)lParam;
	switch(lpnm->code)
	{
	case RBN_LAYOUTCHANGED:
	case RBN_HEIGHTCHANGE:
		{
			char str[50];
			CRect re;
			GetWindowRect(&re);
			GetParent()->ScreenToClient(&re);
			sprintf(str,"%d\x7%d\x7%d\x7%d",re.left,re.top,re.right,re.bottom);
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,
				lpnm->code==RBN_LAYOUTCHANGED?"OnLayoutChanged":"OnHeightChange",
				str);
		}
		break;
	case RBN_GETOBJECT:
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnGetObject","");
		break;
	case RBN_AUTOSIZE:
		{
			LPNMRBAUTOSIZE lp=(LPNMRBAUTOSIZE)lParam;
			char str[250];
			sprintf(str,"%d\x7F%d\x7%d\x7%d\x7%d\x7F%d\x7%d\x7%d\x7%d",
				lp->fChanged,
				lp->rcTarget.left,lp->rcTarget.top,lp->rcTarget.right,lp->rcTarget.bottom,
				lp->rcActual.left,lp->rcActual.top,lp->rcActual.right,lp->rcActual.bottom
				);

			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnAutoSize",str);
		}
		break;
	case RBN_BEGINDRAG:
	case RBN_ENDDRAG:
	case RBN_DELETINGBAND:
	case RBN_DELETEDBAND:
		{
			char str[500];
			LPNMREBAR lp=(LPNMREBAR)lParam;
			sprintf(str,"%d\x7F%d\x7F%d\x7F%s",
				lp->uBand,
				((lp->dwMask&RBNM_ID)==RBNM_ID)?lp->wID:0,
				((lp->dwMask&RBNM_LPARAM)==RBNM_LPARAM)?lp->lParam:0,
				((lp->dwMask&RBNM_STYLE)==RBNM_STYLE)?GPReBarCtrl::ReTranslateBandStyle(lp->fStyle):""
			);
			const char *tmp="";
			switch(lpnm->code)
			{
			case RBN_BEGINDRAG:		tmp="OnBeginDrag";			break;
			case RBN_ENDDRAG:		tmp="OnEndDrag";			break;
			case RBN_DELETINGBAND:	tmp="OnDeletingBand";		break;
			case RBN_DELETEDBAND:	tmp="OnDeletedBand";		break;
			}
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,tmp,str);
		}
		break;
	case RBN_CHILDSIZE:
		{
			LPNMREBARCHILDSIZE lp=(LPNMREBARCHILDSIZE)lParam;
			char str[250];
			sprintf(str,"%d\x7F%d\x7F%d\x7%d\x7%d\x7%d\x7F%d\x7%d\x7%d\x7%d",
				lp->uBand,
				lp->wID,
				lp->rcBand.left,lp->rcBand.top,lp->rcBand.right,lp->rcBand.bottom,
				lp->rcChild.left,lp->rcChild.top,lp->rcChild.right,lp->rcChild.bottom
				);

			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnChildSize",str);
		}
		break;
	case RBN_CHEVRONPUSHED:
		{
			LPNMREBARCHEVRON lp=(LPNMREBARCHEVRON)lParam;
			char str[250];
			sprintf(str,"%d\x7F%d\x7F%d\x7%d\x7%d\x7%d",
				lp->uBand,
				lp->wID,
				lp->rc.left,lp->rc.top,lp->rc.right,lp->rc.bottom
				);

			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnChevronPushed",str);
		}
		break;
	case RBN_AUTOBREAK:
		{
			LPNMREBARAUTOBREAK lp=(LPNMREBARAUTOBREAK)lParam;
			char str[500];
			sprintf(str,"%d\x7F%d\x7F%d\x7F%s\x7F%d",
				lp->uBand,
				lp->wID,
				lp->uMsg,
				GPReBarCtrl::ReTranslateBandStyle(lp->fStyleCurrent),
				lp->fAutoBreak
			);
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"AutoBreak",str);
		}
		break;
	case RBN_MINMAX:
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnMinMax","");
		break;
	}

return TRUE;
//	return CReBar::OnNotify(wParam, lParam, pResult);
}

void GPReBar::OnDragMouseHover()
{
	if (referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(GPC.m_DragDrop.DragName)<0xFFFFFFFFL)
	{
		// Reset the timer.
		::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);

		// Get the current cursor position and window height.
		DWORD dwPos = ::GetMessagePos ();
		CPoint point (LOWORD (dwPos), HIWORD (dwPos));
		ScreenToClient (&point);

		RBHITTESTINFO rbh={0};
		rbh.pt.x=point.x;
		rbh.pt.y=point.y;
		int nBand=GetReBarCtrl().HitTest(&rbh);
		CString tmps;
		tmps.Format("%d",nBand);
		referGPU[UnitId&0xFFFF]->SendDropHoverEvent(tmps,&GPC.m_DragDrop,&point);
	}
}

void GPReBar::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	if (pDrDrStruct && pDrDrStruct->pImageList != NULL)
	{
		::ScreenToClient(m_hWnd,point);
		::KillTimer(pDrDrStruct->hWndDrag,DRAG_TIMER_ID);
		// Offset point
		if (referGPU && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->OffsetWndPoint(point);

		// Erase the old drag image and draw a new one.
		if (pDrDrStruct->hWndLast!=m_hWnd)
		{
			pDrDrStruct->pImageList->DragLeave(CWnd::FromHandle(pDrDrStruct->hWndLast));
			pDrDrStruct->hWndLast=m_hWnd;
			pDrDrStruct->pImageList->DragEnter(this, CPoint(*point));
		}
		pDrDrStruct->pImageList->DragMove (CPoint(*point));

		DWORD iItem=0xFFFFFFFF;
		BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
		// Highlight the drop target if the cursor is over an item.
		if (mDrop)
			iItem = HighlightDropTarget(pDrDrStruct, CPoint(*point));
		// Modify the cursor to provide visual feedback to the user. Note: It's important to do this AFTER the call to DragMove.
		::SetCursor (iItem == 0xFFFFFFFF ?
			AfxGetApp()->LoadStandardCursor (IDC_NO) :
			AfxGetApp()->LoadStandardCursor (IDC_ARROW));

		RBHITTESTINFO rbh={0};
		rbh.pt.x=point->x;
		rbh.pt.y=point->y;
		int nBand=GetReBarCtrl().HitTest(&rbh);
		CString tmps;
		tmps.Format("%d",nBand);
		referGPU[UnitId&0xFFFF]->SendDropMoveEvent(tmps,pDrDrStruct,point);

		if (mDrop)
				::SetTimer (pDrDrStruct->hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nDelayInterval, NULL);
	}
}

void GPReBar::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && referGPU)
	{
		::ScreenToClient(m_hWnd,point);

		RBHITTESTINFO rbh={0};
		rbh.pt.x=point->x;
		rbh.pt.y=point->y;
		int nBand=GetReBarCtrl().HitTest(&rbh);
		CString tmps;
		tmps.Format("%d",nBand);
		referGPU[UnitId&0xFFFF]->SendDropEvent(tmps,pDrDrStruct,point);
	}
}

DWORD GPReBar::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	RBHITTESTINFO rbh={0};
	rbh.pt.x=point.x;
	rbh.pt.y=point.y;
	int nBand=GetReBarCtrl().HitTest(&rbh);
	return nBand==-1 ? -2:nBand;
}

LRESULT GPReBar::OnNcHitTest(CPoint point)
{
	LRESULT ret=CReBar::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

#include "GP_TermDoc.h"

void GPReBar::OnKillFocus(CWnd* pNewWnd)
{
	CReBar::OnKillFocus(pNewWnd);
	GPUNITINFO ui;
	GPUNITINFO uiold;
	if (referGPU && referGPU[UnitId&0xFFFF])
		referGPU[UnitId&0xFFFF]->GetUnitInfo(ui);
	if (pNewWnd)
	{
		GPC.m_Document->FindObject(pNewWnd->m_hWnd,uiold);
		ui.hWnd2=uiold.hWnd;
		ui.IdDlg2=uiold.IdDlg;
		ui.IdObj2=uiold.IdObj;
	}
	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)
	{
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent
			(m_hWnd, UnitId,"OnKillFocus",GPUnit::UnitInfoToString2(&ui,"\x7F"));
	}
	::SendMessage(::GetParent(m_hWnd),GPM_CLIENTKILLFOCUS,(WPARAM)(pNewWnd?pNewWnd->m_hWnd:NULL),(LPARAM)&ui);
}

void GPReBar::OnSetFocus(CWnd* pOldWnd)
{
	CReBar::OnSetFocus(pOldWnd);
	GPUNITINFO ui;
	GPUNITINFO uiold;
	if (referGPU && referGPU[UnitId&0xFFFF])
		referGPU[UnitId&0xFFFF]->GetUnitInfo(ui);
	if (pOldWnd)
	{
		GPC.m_Document->FindObject(pOldWnd->m_hWnd,uiold);
		ui.hWnd2=uiold.hWnd;
		ui.IdDlg2=uiold.IdDlg;
		ui.IdObj2=uiold.IdObj;
	}
	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent
			(m_hWnd, UnitId,"OnSetFocus",GPUnit::UnitInfoToString2(&ui,"\x7F"));

	::SendMessage(::GetParent(m_hWnd),GPM_CLIENTSETFOCUS,(WPARAM)(pOldWnd?pOldWnd->m_hWnd:NULL),(LPARAM)&ui);
}

void GPReBar::OnSize(UINT nType, int cx, int cy)
{
	CReBar::OnSize(nType, cx, cy);

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
	}
}
