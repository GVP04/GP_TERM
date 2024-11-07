// GPHeader.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPHeader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPHeader
const UINT GPHeader::uNMethods=37;
const char *GPHeader::cArrMethods[]={
		"GetItemCount","GetItem","SetItem","GetImageList","SetImageList",
		"SetItemLPARAM","GetOrderArray","SetOrderArray","OrderToIndex","InsertItem",
		"DeleteItem","Layout","CreateDragImage","SetHotDivider","UpdateGroup",
		"GetFilter","SetFilter","GetFilters","SetFilters","ClearFilter",
		"ClearAllFilters","EditFilter","GetBitmapMargin","GetItemRect","GetItemsRect",
		"HitTest","SetBitmapMargin","SetFilterTimeout","DeleteAllColumns","SetUnicodeFormat",
		"GetUnicodeFormat","SetItemText","SetItemOrder","SetItemImage","SetItemFormat",
		"SetItemWidth","SetItemHeight","",
		"","","", "", "", 
	};

const char *GPHeader::cArrMethodsParams[]={
		"","nItem","position,cxy,HEIGHT,iOrder,iImage,lParam,fmt,MASK;pszText","","ImageListName",
		"Id,LPARAM","","item1,item2, ... itemN","nItem","position,cxy,HEIGHT,iOrder,iImage,lParam,fmt,MASK;pszText",
		"nItem","left,top,right,bottom","Not Present","nItem,poX,poY","",
		"nItem","nItem,Value","","Value1^Value2^...","nItem",
		"","nItem, bDiscard","","nItem","",
		"posx,posy","nWidth","nTimeout","","bUseUnicode",
		"","Id,Text","Id,Order","Id,iImage","Id,Format",
		"Id,Width","Id,Height","",
		"","","", "", "", 
	};

GPHeader::GPHeader(UINT iUnitId)
{
	referGPU=NULL;
	UnitId=iUnitId;
}

GPHeader::~GPHeader()
{
}


BEGIN_MESSAGE_MAP(GPHeader, CHeaderCtrl)
	//{{AFX_MSG_MAP(GPHeader)
	ON_NOTIFY_REFLECT(HDN_TRACK, OnTrack)
	ON_NOTIFY_REFLECT(HDN_ITEMCLICK, OnItemclick)
	ON_NOTIFY_REFLECT(HDN_ITEMDBLCLICK, OnItemdblclick)
	ON_NOTIFY_REFLECT(HDN_BEGINTRACK, OnBegintrack)
	ON_NOTIFY_REFLECT(HDN_ENDTRACK, OnEndtrack)
	ON_NOTIFY_REFLECT(HDN_DIVIDERDBLCLICK, OnDividerdblclick)
	ON_NOTIFY_REFLECT(HDN_ENDDRAG, OnEnddrag)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(HDN_ITEMCHANGED, OnItemchanged)
	ON_NOTIFY_REFLECT(HDN_ITEMCHANGING, OnItemchanging)
	ON_NOTIFY_REFLECT(HDN_BEGINDRAG, OnBegindrag)
	ON_NOTIFY_REFLECT(HDN_GETDISPINFO, OnGetdispinfo)
	ON_NOTIFY_REFLECT(HDN_FILTERCHANGE, OnFILTERCHANGE)
	ON_NOTIFY_REFLECT(HDN_FILTERBTNCLICK, OnFILTERBTNCLICK)
	ON_WM_CLOSE()
	ON_WM_SIZING()
	ON_WM_NCHITTEST()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPHeader message handlers
UINT GPHeader::DoMethod(const char *iStr, char *oStr)
{
	char met[150];
	strncpy(met,iStr,145);
	met[145]=0;
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc=0;

	char *aFormatName[14]={"_CENTER","_LEFT","_RIGHT","_RTLREADING","_BITMAP_ON_RIGHT","_IMAGE","_TEXT","_SORTUP","_SORTDOWN","_JUSTIFYMASK","_CHECKBOX","_CHECKED","_FIXEDWIDTH","_SPLITBUTTON",};
	UINT aFormatUINT[14]={HDF_CENTER,HDF_LEFT,HDF_RIGHT,HDF_RTLREADING,HDF_BITMAP_ON_RIGHT,HDF_IMAGE,HDF_STRING,HDF_SORTUP,HDF_SORTDOWN,HDF_JUSTIFYMASK,HDF_CHECKBOX,HDF_CHECKED,HDF_FIXEDWIDTH,HDF_SPLITBUTTON,};

	char *aMaskName[10]={"_FORMAT","_HEIGHT","_IMAGE","_TEXT","_WIDTH","_BITMAP","_DI_SETITEM","_ORDER","_FILTER","_LPARAM",};
	UINT aMaskUINT[10]={HDI_FORMAT,HDI_HEIGHT,HDI_IMAGE,HDI_TEXT,HDI_WIDTH,HDI_BITMAP,HDI_DI_SETITEM,HDI_ORDER,HDI_FILTER,HDI_LPARAM,};

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

	int atoipos=atoi(pos);
	int retint=-123456;

	switch(nfunc)
	{
	case  0: /*GetItemCount*/	if (oStr!=NULL)	sprintf(oStr,"%d",GetItemCount());	break;
	case  1: /*GetItem*/
		if (oStr!=NULL)
		{
			char *txt=new char [5000];
			HDITEM hdi={0};
			hdi.pszText=txt;
			int HEIGHT=hdi.cxy;
			hdi.cchTextMax=2500;
			hdi.mask=HDI_BITMAP|HDI_FILTER|HDI_FORMAT|HDI_IMAGE|HDI_LPARAM|HDI_ORDER|HDI_TEXT|HDI_WIDTH;
			hdi.type=HDFT_ISSTRING;
			HD_TEXTFILTER mFlt={0};
			mFlt.pszText=txt+3000;
			*mFlt.pszText=0;
			mFlt.cchTextMax=1900;
			hdi.pvFilter=&mFlt;

			if (GetItem(atoi(pos),&hdi)!=FALSE)
			{
				char str[200];*str=0;
				int i;
				for(i=0;i<14;i++)
					if ((hdi.fmt&aFormatUINT[i])==aFormatUINT[i]) strcat(str,aFormatName[i]);

				sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d\x7F%ld\x7F%ld\x7F%s\x7F%s\x7F%s",
					hdi.cxy,HEIGHT,hdi.iOrder,hdi.iImage,(DWORD)hdi.hbm,hdi.lParam,str,hdi.pszText,mFlt.pszText);
			}
			delete[] txt;
		}
		break;
	case  2: /*SetItem*/
	case  9: /*InsertItem*/
		// format position,cxy,HEIGHT,iOrder,iImage,lParam,fmt,MASK;pszText
		{
			char *postmpcc=new char [(int)strlen(pos)+10];
			strcpy(postmpcc,pos);
			int height=0;
			int position=0;
			UINT tmpMask=0;
			HDITEM hdi={0};
			m_LastScanf=sscanf(postmpcc,"%d,%d,%d,%d,%d,%d",&position,&hdi.cxy,&height,&hdi.iOrder,&hdi.iImage,&hdi.lParam);
			hdi.mask=hdi.fmt=0;

			int i;
			for(i=0;i<14;i++)
				if (strstr(postmpcc,aFormatName[i])!=NULL) hdi.fmt|=aFormatUINT[i];

			for(i=0;i<10;i++)
				if (strstr(postmpcc,aMaskName[i])!=NULL)
				{
					if (i!=1) hdi.mask|=aMaskUINT[i];
					else tmpMask=HDI_HEIGHT;
				}

			char *pss=strchr(postmpcc,';');
			if (pss++==NULL) pss="";
			hdi.pszText=pss;

			if (nfunc==2) SetItem(position,&hdi);
			else position=InsertItem(position,&hdi);

			if (tmpMask!=0)
			{
				hdi.mask=tmpMask;
				SetItem(position,&hdi);
			}
			if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
				DoMethod("UpdateGroup",NULL);
			delete[] postmpcc;
		}
		break;
	case 5: /*SetItemLPARAM*/
		{
			HDITEM hdi={0};
			const char *pss=strchr(pos,',');
			if (pss++==NULL) pss="";

			hdi.mask=HDI_LPARAM;
			hdi.lParam=atoi(pss);
			retint=SetItem(atoipos,&hdi);
		}
		break;
	case  6: /*GetOrderArray*/
		if (oStr!=NULL)
		{
			*oStr=0;
			int nItems=GetItemCount();
			int *piArray=new int [nItems+1];
			int i;
			for(i=0;i<nItems;i++) piArray[i]=-1;
			GetOrderArray(piArray,nItems);
			char tmp[50];

			for(i=0;i<nItems && piArray[i]!=-1;i++)
			{
				sprintf(tmp,"%d%c",piArray[i],piArray[i+1]!=-1?7:0);
				strcat(oStr,tmp);
			}
			delete[] piArray;
		}
		break;
	case  7: /*SetOrderArray*/
		//format  item1,item2, ... itemN
		{
			UINT ret;
			int i,*piArray=new int [5000];

			const char *pos2=pos,*pos3;
			for(i=1;i<4999 && (pos3=strchr(pos2,','))!=NULL;i++,pos2=pos3++) piArray[i]=atoi(pos2);
			piArray[i++]=atoi(pos);

			ret=SetOrderArray(i,piArray);
			if (oStr!=NULL)	sprintf(oStr,"%d",ret);
			delete[] piArray;
		}
		break;
	case  8: /*OrderToIndex */	if (oStr!=NULL) sprintf(oStr,"%d",OrderToIndex(atoi(pos)));	break;
	case 10: /*DeleteItem*/
		{
			int ret=DeleteItem(atoi(pos));
			if (oStr!=NULL)	sprintf(oStr,"%d",ret);
			if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
				DoMethod("UpdateGroup",NULL);
		}
		break;
	case 11: /*Layout*/ // format left,top,right,bottom
		if (oStr!=NULL)
		{
			HDLAYOUT lo={0};
			CRect re;
			WINDOWPOS wp={0};
			lo.prc=&re;
			lo.pwpos=&wp;
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&re.left,&re.top,&re.right,&re.bottom);
			Layout(&lo);
			char strst[250];*strst=0;
			int i;
			for(i=0;i<N_WINDOWPOS_STYLES;i++)
				if ((wp.flags&aWindowPosStyleUINT[i])==aWindowPosStyleUINT[i]) strcat(strst,aWindowPosStyleName[i]);

			sprintf(oStr,"%X%c%X%c%d%c%d%c%d%c%d%c%ld%c%s",(DWORD)wp.hwnd,7,(DWORD)wp.hwndInsertAfter,
						7,wp.x,7,wp.y,7,wp.cx,7,wp.cy,7,wp.flags,7,strst);
		}
		break;
	case 13: /*SetHotDivider*/ // format   nitem    или  posx, posy
		{
			int ret;
			if (strchr(pos,',')==NULL) ret=SetHotDivider(atoi(pos));
			else
			{
				CPoint po;
				m_LastScanf=sscanf(pos,"%d,%d",&po.x,&po.y);
				ret=SetHotDivider(po);
			}
			if (oStr!=NULL) sprintf(oStr,"%d",ret);
		}
		break;
	case 14: /*UpdateGroup*/
		if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
			referGPU[UnitId&0xFFFF]->UpdateGroup(-123456,GetStyle());
		break;
	case  3: /*GetImageList*/
		if (oStr!=NULL)
		{
			CImageList* tmp=GetImageList();
			int id=GPC.FindImageList(tmp);
			if (id>=0) strcpy(oStr,GPC.a_GPImageList[id].ILName);
		}
		break;
	case  4: /*SetImageList*/
		{
			int num=GPC.GetImageListId(pos);
			if (num>=0)	SetImageList(&(GPC.a_GPImageList[num].m_IL));
		}
		break;

	case 15: /*GetFilter*/
		if (oStr)
		{
			if ((GetStyle()&HDS_FILTERBAR)!=HDS_FILTERBAR) ModifyStyle(0,HDS_FILTERBAR,1);
			HD_TEXTFILTER hdtf={0};
			hdtf.pszText=oStr;
			hdtf.cchTextMax=1990;
			*hdtf.pszText=0;
			HDITEM hdi={0};
			hdi.type=HDFT_ISSTRING;
			hdi.pvFilter=&hdtf;
			hdi.mask=HDI_FILTER;
			GetItem(atoi(pos),&hdi);
		}
		break;
	case 16: /*SetFilter*/
		{
			char *postmpcc=new char [(int)strlen(pos)+10];
			strcpy(postmpcc,pos);
			if ((GetStyle()&HDS_FILTERBAR)!=HDS_FILTERBAR) ModifyStyle(0,HDS_FILTERBAR,1);
			HD_TEXTFILTER hdtf={0};
			char *pos2=strchr(postmpcc,',');
			if (pos2++==NULL) pos2="";
			hdtf.pszText=pos2;
			hdtf.cchTextMax=1990;
			HDITEM hdi={0};
			hdi.type=HDFT_ISSTRING;
			hdi.pvFilter=&hdtf;
			hdi.mask=HDI_FILTER;
			SetItem(atoi(postmpcc),&hdi);
			delete[] postmpcc;
		}
		break;
	case 17: /*GetFilters*/
		if (oStr)
		{
			if ((GetStyle()&HDS_FILTERBAR)!=HDS_FILTERBAR) ModifyStyle(0,HDS_FILTERBAR,1);
			HD_TEXTFILTER hdtf={0};
			hdtf.cchTextMax=1990;
			HDITEM hdi={0};
			hdi.type=HDFT_ISSTRING;
			hdi.mask=HDI_FILTER;
			hdi.pvFilter=&hdtf;
			char *pos2=oStr;

			int nItems=GetItemCount();
			int i;
			for(i=0;i<nItems;)
			{
				hdtf.pszText=pos2;
				*hdtf.pszText=0;
				GetItem(i,&hdi);
				if (++i<nItems) strcat(pos2,"\x7F");
				pos2+=(int)strlen(pos2);
			}
		}
		break;
	case 18: /*SetFilters*/
		{
			if ((GetStyle()&HDS_FILTERBAR)!=HDS_FILTERBAR) ModifyStyle(0,HDS_FILTERBAR,1);
			HD_TEXTFILTER hdtf={0};
			hdtf.cchTextMax=1990;
			HDITEM hdi={0};
			hdi.type=HDFT_ISSTRING;
			hdi.pvFilter=&hdtf;
			hdi.mask=HDI_FILTER;
			int nItem=0;
			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
			char *pos1=pos333;
			while(pos1 && *pos1)
			{
				hdtf.pszText=pos1;
				char *pos2=strchr(pos1,GPC.DelimiterIn1);
				if (pos2) *(pos2++)=0;
				SetItem(nItem++,&hdi);
				pos1=pos2;
			}
			delete[] pos333;
		}
		break;
	case 19: /*ClearFilter*/
		SendMessage(HDM_CLEARFILTER,(WPARAM)m_hWnd,atoi(pos));
		break;
	case 20: /*ClearAllFilters*/
		{
			int nItems=GetItemCount();
			int i;
			for(i=0;i<nItems;i++)
				SendMessage(HDM_CLEARFILTER,(WPARAM)m_hWnd,i);
		}
		break;
	case 21: /*EditFilter*/
		{
			int nItem=0,Disca=0;
			m_LastScanf=sscanf(pos,"%d,%d",&nItem,&Disca);
			SendMessage(HDM_EDITFILTER,nItem,MAKELPARAM(Disca, 0));
		}
		break;
	case 22: /*GetBitmapMargin*/
		if (oStr) sprintf(oStr,"%d",SendMessage(HDM_GETBITMAPMARGIN,0,0));
		break;
	case 23: /*GetItemRect*/
		if (oStr)
		{
			RECT re={0};
			SendMessage(HDM_GETITEMRECT,atoi(pos),(LPARAM)&re);
			sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.top,re.left,re.bottom,re.right);
		}
		break;

	case 24: /*GetItemsRect*/
		if (oStr)
		{
			RECT re={0};
			int nItems=GetItemCount();
			char *pos2=oStr;
			int i;
			for(i=0;i<nItems;i++)
			{
				SendMessage(HDM_GETITEMRECT,i,(LPARAM)&re);
				if (i>0)  *(pos2++)=0x7F;
				pos2+=sprintf(pos2,"%d\x7%d\x7%d\x7%d",re.top,re.left,re.bottom,re.right);
			}
		}
		break;
	case 25: /*HitTest*/
		if (oStr)
		{
			HD_HITTESTINFO hti={0};
			m_LastScanf=sscanf(pos,"%d,%d",&hti.pt.x,&hti.pt.y);
			const char * nm[]={
				"ABOVE","BELOW","NOWHERE","ONDIVIDER","ONDIVOPEN",
				"ONHEADER","ONFILTER","ONFILTERBUTTON","TOLEFT","TORIGHT","NOWHERE",
			};
			const UINT repl[]={
				HHT_ABOVE,HHT_BELOW,HHT_NOWHERE,HHT_ONDIVIDER,HHT_ONDIVOPEN,
				HHT_ONHEADER,HHT_ONFILTER,HHT_ONFILTERBUTTON,HHT_TOLEFT,HHT_TORIGHT,
			};

			SendMessage(HDM_HITTEST,0,(LPARAM)&hti);

			UINT i;
			for(i=0;i<10 && hti.flags!=repl[i];i++);

			sprintf(oStr,"%d\x7F%s",hti.iItem,nm[i]);
		}
		break;
	case 26: /*SetBitmapMargin*/
		SendMessage(HDM_SETBITMAPMARGIN,atoi(pos),0);
		break;
	case 27: /*SetFilterTimeout*/
		SendMessage(HDM_SETFILTERCHANGETIMEOUT,0,atoi(pos));
		break;

	case 28: /*DeleteAllColumns*/
		{
			int nItem=GetItemCount();
			while(nItem>0)
				DeleteItem(--nItem);
		}
		break;
	case 29: /*SetUnicodeFormat*/
		SendMessage(HDM_SETUNICODEFORMAT,atoi(pos),0);
		break;
	case 30: /*GetUnicodeFormat*/
		if (oStr)
			sprintf(oStr,"%d",SendMessage(HDM_GETUNICODEFORMAT,0,0));
		break;

	case 31: /*SetItemText*/
		{

			char *postmpcc=new char [(int)strlen(pos)+10];
			strcpy(postmpcc,pos);
			HDITEM hdi={0};
			char *pss=strchr(postmpcc,',');
			if (pss++==NULL) pss="";

			hdi.mask=HDI_TEXT;
			hdi.pszText=pss;

			retint=SetItem(atoipos,&hdi);
			delete[] postmpcc;
		}
		break;
	case 32: /*SetItemOrder*/
		{
			HDITEM hdi={0};
			const char *pss=strchr(pos,',');
			if (pss++==NULL) pss="";
			hdi.mask=HDI_ORDER;
			hdi.iOrder=atoi(pss);
			retint=SetItem(atoipos,&hdi);
		}
		break;
	case 33: /*SetItemImage*/
		{
			HDITEM hdi={0};
			const char *pss=strchr(pos,',');
			if (pss++==NULL) pss="";

			hdi.mask=HDI_IMAGE;
			hdi.iImage=atoi(pss);
			retint=SetItem(atoipos,&hdi);
		}
		break;
	case 34: /*SetItemFormat*/
		{
			HDITEM hdi={0};
			const char *pss=strchr(pos,',');
			if (pss++==NULL) pss="";
			int i;
			for(i=0;i<14;i++)
				if (strstr(pss,aFormatName[i])!=NULL) hdi.fmt|=aFormatUINT[i];

			hdi.mask=HDI_FORMAT;
			if (hdi.fmt==0)	hdi.fmt=atoi(pss);
			retint=SetItem(atoipos,&hdi);
		}
		break;


	case 35: /*SetItemWidth*/
		{
			HDITEM hdi={0};
			const char *pss=strchr(pos,',');
			if (pss++==NULL) pss="";

			hdi.mask=HDI_WIDTH;
			hdi.cxy=atoi(pss);
			retint=SetItem(atoipos,&hdi);
		}
		break;
	case 36: /*SetItemHeight*/
		{
			HDITEM hdi={0};
			const char *pss=strchr(pos,',');
			if (pss++==NULL) pss="";

			hdi.mask=HDI_HEIGHT;
			hdi.cxy=atoi(pss);
			retint=SetItem(atoipos,&hdi);
		}
		break;



	case 12: /*CreateDragImage*/
	default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);

	return nfunc;
}

UINT GPHeader::GPSetProperty(const char *iStr)
{
	char *iValue=new char [(int)strlen(iStr)+5];
	strcpy(iValue,iStr);
	UINT ret=1,i;
	char *pos=strchr(iValue,'=');

	if (pos!=NULL && m_hWnd)
	{
		char *prop[]={"ADDSTYLE", "DELSTYLE","STYLE",};
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
					strcat(pos,"|");
					int InvFlg=0;
					// HEADER specif
					for(i=0;i<N_HEADER_STYLES;i++)
						if (strstr(pos,aHeaderStyleName[i])!=NULL)
						{
							InvFlg++;
							switch(propnum)
							{
							case 2: /* STYLE*/
							case 0: /* ADDSTYLE*/	ModifyStyle(0,aHeaderStyleUINT[i]);break;
							case 1: /* DELSTYLE*/	ModifyStyle(aHeaderStyleUINT[i],0);break;
							}
						}

					char *postmp=strstr(pos,"&U");
					if (postmp!=NULL)
					{
						UINT tmpstl=0;
						m_LastScanf=sscanf(postmp,"&U%X",&tmpstl);
						InvFlg++;
						switch(propnum)
						{
						case 2: /* STYLE*/
						case 0: /* ADDSTYLE*/	ModifyStyle(0,tmpstl);	break;
						case 1: /* DELSTYLE*/	ModifyStyle(tmpstl,0);break;
						}
					}
					else
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
					if (InvFlg!=0) Invalidate();
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

void GPHeader::OnTrack(NMHDR* pNMHDR, LRESULT* pResult)
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	char str[200];
	sprintf(str,"%X\x7F%ld\x7F%ld",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code);
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnTrack",str);
	*pResult = 0;
}

void GPHeader::OnItemclick(NMHDR* pNMHDR, LRESULT* pResult)
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	char str[200];
	sprintf(str,"%X\x7F%ld\x7F%ld",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code);
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnItemclick",str);
	*pResult = 0;
	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
		DoMethod("UpdateGroup",NULL);
}

void GPHeader::OnItemdblclick(NMHDR* pNMHDR, LRESULT* pResult)
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	char str[200];
	sprintf(str,"%X\x7F%ld\x7F%ld",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code);
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnItemdblclick",str);
	*pResult = 0;
	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
		DoMethod("UpdateGroup",NULL);
}

void GPHeader::OnBegintrack(NMHDR* pNMHDR, LRESULT* pResult)
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	char str[200];
	sprintf(str,"%X\x7F%ld\x7F%ld",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code);
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnBegintrack",str);
	*pResult = 0;
	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
		DoMethod("UpdateGroup",NULL);
}

void GPHeader::OnEndtrack(NMHDR* pNMHDR, LRESULT* pResult)
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	char str[200];
	sprintf(str,"%X\x7F%ld\x7F%ld",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code);
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnEndtrack",str);
	*pResult = 0;
	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
		DoMethod("UpdateGroup",NULL);
}

void GPHeader::OnDividerdblclick(NMHDR* pNMHDR, LRESULT* pResult)
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	char str[200];
	sprintf(str,"%X\x7F%ld\x7F%ld",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code);
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDividerdblclick",str);
	*pResult = 0;
}

void GPHeader::OnEnddrag(NMHDR* pNMHDR, LRESULT* pResult)
{
	HD_NOTIFY * phdn = (HD_NOTIFY *) pNMHDR;
	char str[200];
	sprintf(str,"%X\x7F%ld\x7F%ld",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code);
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnEnddrag",str);
	*pResult = 0;
}

LRESULT GPHeader::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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

	if (message==WM_SIZEPARENT && referGPU!=NULL)
	{
		UINT SizStyle=referGPU[UnitId&0xFFFF]->SizStyle;
		if ((SizStyle&0xFFFF0000)!=0)
		{
			AFX_SIZEPARENTPARAMS* lpLayout = (AFX_SIZEPARENTPARAMS*)lParam;

			CRect re;
			GetWindowRect(&re);
			switch((SizStyle&0xFFFF0000)/0x10000)
			{
			case GPUA_TOP:
				MoveWindow(lpLayout->rect.left,lpLayout->rect.top,lpLayout->rect.right-lpLayout->rect.left,re.Height());
				lpLayout->rect.top+=re.Height();
				break;
			case GPUA_BOTTOM:
				MoveWindow(lpLayout->rect.left,lpLayout->rect.bottom-re.Height(),lpLayout->rect.right-lpLayout->rect.left,re.Height());
				lpLayout->rect.bottom-=re.Height();
				break;
			case GPUA_LEFT:
				MoveWindow(lpLayout->rect.left,lpLayout->rect.top,re.Width(),lpLayout->rect.bottom-lpLayout->rect.top);
				lpLayout->rect.left+=re.Width();
				break;
			case GPUA_RIGHT:
				MoveWindow(lpLayout->rect.right-re.Width(),lpLayout->rect.top,re.Width(),lpLayout->rect.bottom-lpLayout->rect.top);
				lpLayout->rect.right-=re.Width();
				break;
			}
		}
	}

	switch(message)
	{
	case GPM_DRAGMOUSELEAVE:
		if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDragLeave","");
		GPC.m_DragDrop.pImageList->DragShowNolock(FALSE);
		SetHotDivider(-1);
		UpdateWindow();
		GPC.m_DragDrop.pImageList->DragShowNolock(TRUE);
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
	else lpr=CHeaderCtrl::WindowProc(message, wParam, lParam);

	return lpr;
}


void GPHeader::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	HD_NOTIFY * phdn = (HD_NOTIFY *) pNMHDR;
	char str[200];
	sprintf(str,"%X\x7F%ld\x7F%ld",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code);
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnItemchanged",str);
		if (referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
			DoMethod("UpdateGroup",NULL);
	}

	*pResult = 0;
}

void GPHeader::OnItemchanging(NMHDR* pNMHDR, LRESULT* pResult)
{
	HD_NOTIFY * phdn = (HD_NOTIFY *) pNMHDR;
	char str[200];
	sprintf(str,"%X\x7F%ld\x7F%ld",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code);
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnItemchanging",str);
		if (referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
			DoMethod("UpdateGroup",NULL);
	}

	*pResult = 0;
}

void GPHeader::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult)
{
	HD_NOTIFY * phdn = (HD_NOTIFY *) pNMHDR;
	char str[200];
	sprintf(str,"%X\x7F%ld\x7F%ld",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code);
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnBegindrag",str);

	*pResult = 0;
}

void GPHeader::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
	HD_NOTIFY * phdn = (HD_NOTIFY *) pNMHDR;
	char str[200];
	sprintf(str,"%X\x7F%ld\x7F%ld",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code);
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDblclk",str);

	*pResult = 0;
}

void GPHeader::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	HD_NOTIFY * phdn = (HD_NOTIFY *) pNMHDR;
	char str[200];
	sprintf(str,"%X\x7F%ld\x7F%ld",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code);
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnGetdispinfo",str);

	*pResult = 0;
}


BOOL GPHeader::PreTranslateMessage(MSG* pMsg)
{
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		referGPU[UnitId&0xFFFF]->m_CurPreMessage=pMsg;
		if (!referGPU[UnitId&0xFFFF]->DefPreTranslateMessage(pMsg)) return 0;
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

	return CHeaderCtrl::PreTranslateMessage(pMsg);
}

void GPHeader::OnClose()
{
	if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClose","");
//	CHeaderCtrl::OnClose();
}

void GPHeader::OnSizing(UINT fwSide, LPRECT pRect)
{
	BOOL EnableSz=TRUE;
	UINT SizStyle=referGPU[UnitId&0xFFFF]->SizStyle;
	if ((SizStyle&0xFFFF)!=0)
	{
		CRect re;
		GetWindowRect(&re);
		switch(fwSide)
		{
		case WMSZ_BOTTOM:
			if ((SizStyle&GPUA_BOTTOM)!=GPUA_BOTTOM) EnableSz=FALSE;
			break;
		case WMSZ_BOTTOMLEFT:
			if ((SizStyle&GPUA_BOTTOM)!=GPUA_BOTTOM && (SizStyle&GPUA_LEFT)!=GPUA_LEFT) EnableSz=FALSE;
			break;
		case WMSZ_BOTTOMRIGHT:
			if ((SizStyle&GPUA_BOTTOM)!=GPUA_BOTTOM && (SizStyle&GPUA_RIGHT)!=GPUA_RIGHT) EnableSz=FALSE;
			break;
		case WMSZ_LEFT:
			if ((SizStyle&GPUA_LEFT)!=GPUA_LEFT) EnableSz=FALSE;
			break;
		case WMSZ_RIGHT:
			if ((SizStyle&GPUA_RIGHT)!=GPUA_RIGHT) EnableSz=FALSE;
			break;
		case WMSZ_TOP:
			if ((SizStyle&GPUA_TOP)!=GPUA_TOP) EnableSz=FALSE;
			break;
		case WMSZ_TOPLEFT:
			if ((SizStyle&GPUA_LEFT)!=GPUA_LEFT && (SizStyle&GPUA_TOP)!=GPUA_TOP) EnableSz=FALSE;
			break;
		case WMSZ_TOPRIGHT:
			if ((SizStyle&GPUA_RIGHT)!=GPUA_RIGHT && (SizStyle&GPUA_TOP)!=GPUA_TOP) EnableSz=FALSE;
			break;
		}
		if (EnableSz==FALSE)
		{
			pRect->top=re.top;
			pRect->left=re.left;
			pRect->right=re.right;
			pRect->bottom=re.bottom;
		}
		else
		{
			GetParent()->SendMessage(WM_SIZE);
		}
	}

	if (EnableSz) CHeaderCtrl::OnSizing(fwSide, pRect);

	GetParent()->SendMessage(GPN_UPDATESIZE);

}

void GPHeader::OnDragMouseHover()
{
	if (referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(GPC.m_DragDrop.DragName)<0xFFFFFFFFL)
	{
		// Reset the timer.
		::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);

		// Get the current cursor position and window height.
		DWORD dwPos = ::GetMessagePos ();
		CPoint point (LOWORD (dwPos), HIWORD (dwPos));
		ScreenToClient (&point);

		referGPU[UnitId&0xFFFF]->SendDropHoverEvent("",&GPC.m_DragDrop,&point);
	}
}

void GPHeader::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
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

		DWORD hItem=0xFFFFFFFF;
		BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
		// Highlight the drop target if the cursor is over an item.
		if (mDrop)
			hItem = HighlightDropTarget(pDrDrStruct, CPoint(*point));
		// Modify the cursor to provide visual feedback to the user. Note: It's important to do this AFTER the call to DragMove.
		::SetCursor (hItem == 0xFFFFFFFF ?
			AfxGetApp()->LoadStandardCursor (IDC_NO) :
			AfxGetApp()->LoadStandardCursor (IDC_ARROW));

		referGPU[UnitId&0xFFFF]->SendDropMoveEvent("",pDrDrStruct,point);

		if (mDrop)
			::SetTimer (pDrDrStruct->hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nDelayInterval, NULL);
	}
}

void GPHeader::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && referGPU)
	{
		::ScreenToClient(m_hWnd,point);
		HDHITTESTINFO hdh={0};
		hdh.pt.x=point->x;
		hdh.pt.y=point->y;

		int nItem=SendMessage(HDM_HITTEST,0,(LPARAM)&hdh);

		pDrDrStruct->pImageList->DragShowNolock(FALSE);
		SetHotDivider(-1);
		UpdateWindow();
		pDrDrStruct->pImageList->DragShowNolock(TRUE);

		CString tmp;

		if (nItem >=0)
		{
			HDITEM hdi={0};
			hdi.mask=HDI_TEXT;
			hdi.pszText =new char [2000];
			hdi.cchTextMax = 1000;
			GetItem(nItem,&hdi);
			if (hdh.flags==HHT_ONDIVIDER) strcpy(hdi.pszText,"DEVIDER");

			tmp.Format("%d\x7%s",nItem,hdi.pszText);
			delete[] hdi.pszText;
		}
		else
			tmp="-1\x7";

		referGPU[UnitId&0xFFFF]->SendDropEvent(tmp,pDrDrStruct,point);
	}
}

DWORD GPHeader::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	HDHITTESTINFO hdht={0};
	hdht.pt.x=point.x;
	hdht.pt.y=point.y;
	int nItem=SendMessage(HDM_HITTEST,0,(LPARAM)&hdht);

	pDrDrStruct->pImageList->DragShowNolock(FALSE);

	if (hdht.flags==HHT_ONDIVIDER)
		SetHotDivider(nItem=hdht.iItem+1);
	else
		SetHotDivider(-1);

	UpdateWindow();
	pDrDrStruct->pImageList->DragShowNolock(TRUE);

	return nItem;
}

LRESULT GPHeader::OnNcHitTest(CPoint point)
{
	LRESULT ret=CHeaderCtrl::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

void GPHeader::OnFILTERCHANGE(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMHEADER phdn = (LPNMHEADER) pNMHDR;
	char str[400];
	HD_TEXTFILTER hdtf={0};
	hdtf.pszText=str+sprintf(str,"%d\x7F",phdn->iItem);
	hdtf.cchTextMax=370;
	*hdtf.pszText=0;
	HDITEM hdi={0};
	hdi.type=HDFT_ISSTRING;
	hdi.pvFilter=&hdtf;
	hdi.mask=HDI_FILTER;
	GetItem(phdn->iItem,&hdi);

	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnFilterChange",str);

	*pResult = 0;
}

void GPHeader::OnFILTERBTNCLICK(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMHEADER phdn = (LPNMHEADER) pNMHDR;
	char str[400];
	HD_TEXTFILTER hdtf={0};
	hdtf.pszText=str+sprintf(str,"%d\x7F%d\x7F",phdn->iItem,phdn->iButton);
	hdtf.cchTextMax=350;
	*hdtf.pszText=0;
	HDITEM hdi={0};
	hdi.type=HDFT_ISSTRING;
	hdi.pvFilter=&hdtf;
	hdi.mask=HDI_FILTER;
	GetItem(phdn->iItem,&hdi);
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnFilterBtnClick",str);

	*pResult = 0;
}

#include "GP_TermDoc.h"

void GPHeader::OnKillFocus(CWnd* pNewWnd)
{
	CHeaderCtrl::OnKillFocus(pNewWnd);
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

void GPHeader::OnSetFocus(CWnd* pOldWnd)
{
	CHeaderCtrl::OnSetFocus(pOldWnd);
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


void GPHeader::OnSize(UINT nType, int cx, int cy)
{
	CHeaderCtrl::OnSize(nType, cx, cy);

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
	}
}

HBRUSH GPHeader::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CHeaderCtrl::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}
