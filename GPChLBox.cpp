// GPChLBox.cpp : implementation file
//

#include "stdafx.h"
#include "GP_term.h"
#include "GPChLBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPChLBox
const UINT GPChLBox::uNMethods=81;
const char *GPChLBox::cArrMethods[]={
/*00*/		"InitStorage","GetCount","GetHorizontalExtent","SetHorizontalExtent","GetTopIndex",
/*05*/		"SetTopIndex","GetItemData","GetItemDataPtr","SetItemData","SetItemDataPtr",
/*10*/		"GetItemRect","ItemFromPoint","SetItemHeight","GetItemHeight","GetSel",
/*15*/		"GetText","GetTextLen","SetColumnWidth","SetTabStops","GetLocale",
/*20*/		"SetLocale","GetCurSel","SetCurSel","SetSel","GetCaretIndex",
/*25*/		"SetCaretIndex","GetSelCount","GetSelItems","SelItemRange","SetAnchorIndex",
/*30*/		"GetAnchorIndex","AddString","DeleteString","InsertString","ResetContent",
/*35*/		"Dir","FindString","FindStringExact","SelectString","GetItemTextEx",
/*40*/		"GetItemText","CompareItem","DeleteItem","VKeyToItem","CharToItem",
/*45*/		"SetCheckStyle","GetCheckStyle","SetCheck","GetCheck","Enable",
/*50*/		"IsEnabled","GetChecked","GetSelectedItem","UpdateGroup","GetStyle",
/*55*/		"AddStrings","GetContents","SelectAll","DeSelectAll","SelectionDelete",
/*60*/		"SelectionInvert","SelectionDoMethod","SetSelection","SelectionCheck","FillFromSpr",
/*65*/		"ReplaceFromSpr","FillFromList","AddFromSpr","AddFromList","DeleteItemEx",
/*70*/		"AddFile","GetListBoxInfo",	"AddItem",	"SetItemText",	"SetCurSelByItemData",
/*75*/		"SetAutoFocus","SetItemDataEx","GetItemDataEx",	"AddItemEx",	"SetItemTextEx",
/*80*/		"SetCurSelByItemDataEx","","",		"",
		"","","", "", "", 
	};
const char *GPChLBox::cArrMethodsParams[]={
/*00*/		"lines, nbytes","","","cxExtent","",
/*05*/		"nIndex","nIndex","nIndex","nIndex, iData","nIndex, iPtr",
/*10*/		"nIndex","poX, poY","nIndex, cyItemHeight","nIndex","nIndex",
/*15*/		"nIndex","nIndex","cxWidth","iTab1,iTab2,...,iTabN","",
/*20*/		"iLocale","","nSelect","nIndex, bSelect","",
/*25*/		"nIndex, bScroll","","nItems, bTextOut","bSelect, nFirstItem, nLastItem","nIndex",
/*30*/		"","Text","nIndex","nIndex, Text","",
/*35*/		"WRHSDAIE, Dir","nIndexAfter, Text","nIndexAfter, Text","nIndexAfter, Text","ItemData",
/*40*/		"ItemDataEx","Not Present","ItemData","Not Present","Not Present",
/*45*/		"CheckStyle","","nIndex, nCheck","nIndex","nIndex, bEnabled",
/*50*/		"nIndex","","","","",
/*55*/		"Str1^Str2^...^StrN","","","","",
/*60*/		"","Method Params","Sel1,Sel2,...,SelN","iCheck","SprName,Separator,nField1,nField2...",
/*65*/		"SprName,IdentField,Separator,nField1,nField2...","ListName","SprName,Separator,nField1,nField2...","ItemDataEx",
/*70*/		"FileNAme","",	"[iBefore],ItemData;ItemText","[iItem],iItemData;Text","ItemData",
/*75*/		"bAuto","ItemId,ItemDataEx","ItemId",	"[iBefore],ItemDataEx;ItemText","[iItem],iItemDataEx;Text",
/*80*/		"ItemDataEx","","","",
		"","","", "", "", 
	};


GPChLBox::GPChLBox(UINT iUnitId)
{
	ItemDataArray=NULL;
	m_bAutoFocus=TRUE;
	m_LCDOflag=0;
	referGPU=NULL;
	UnitId=iUnitId;
	m_LastHighLight=-1;
}

GPChLBox::~GPChLBox()
{
	if (ItemDataArray) delete ItemDataArray;
	ItemDataArray=NULL;
}


BEGIN_MESSAGE_MAP(GPChLBox, CCheckListBox)
	//{{AFX_MSG_MAP(GPChLBox)
	ON_CONTROL_REFLECT(LBN_SELCHANGE, OnSelchange)
	ON_CONTROL_REFLECT(LBN_ERRSPACE, OnErrspace)
	ON_CONTROL_REFLECT(LBN_SELCANCEL, OnSelcancel)
	ON_WM_PARENTNOTIFY()
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CLOSE()
	ON_WM_SIZING()
	ON_WM_NCHITTEST()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_MOUSEACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPChLBox message handlers

UINT GPChLBox::DoMethod(const char *iStr, char *oStr)
{
	char met[150];
	UINT tmpUINT=0;
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
	int AtoiPos=atoi(pos);
	int retint=-123456;

	switch(nfunc)
	{
	case 0: /*InitStorage*/
		{ UINT lines,nbytes;m_LastScanf=sscanf(pos,"%d,%d",&lines,&nbytes);
			if (lines<100) lines=200;
			if (nbytes<10000) nbytes=10000;
			retint=InitStorage(lines,nbytes);
		}
		break;
	case 1: /*GetCount*/	retint=GetCount();	break;
	case 2: /*GetHorizontalExtent*/	retint=GetHorizontalExtent();	break;
	case 3: /*SetHorizontalExtent*/	SetHorizontalExtent(AtoiPos);	break;
	case 4: /*GetTopIndex*/			retint=GetTopIndex();	break;
	case 5: /*SetTopIndex*/			retint=SetTopIndex(AtoiPos);	break;
	case 6: /*GetItemData*/		if (oStr!=NULL)	sprintf(oStr,"%u",GetItemData(AtoiPos));	break;
	case 7: /*GetItemDataPtr*/	if (oStr!=NULL)	sprintf(oStr,"%p",GetItemDataPtr(AtoiPos));	break;
	case 8: /*SetItemData*/
		{
			int id; m_LastScanf=sscanf(pos,"%d,%u",&id,&tmpUINT);
			retint=SetItemData(id,tmpUINT);
		}
		break;
	case 9: /*SetItemDataPtr*/
		{
			void *ptr;int id;m_LastScanf=sscanf(pos,"%d,%p",&id,&ptr);
			retint=SetItemDataPtr(id,ptr);
		}
		break;
	case 10: /*GetItemRect*/
		if (oStr!=NULL)
		{
			CRect re;GetItemRect(AtoiPos,&re);
			sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
		}
		break;
	case 11: /*ItemFromPoint*/
		if (oStr!=NULL)
		{
			CPoint po;po.x=0;po.y=0; BOOL out=0;
			m_LastScanf=sscanf(pos,"%d,%d",&po.x,&po.y);
			tmpUINT=ItemFromPoint(po,out);
			sprintf(oStr,"%d\x7F%d",tmpUINT,out);
		}
		break;
	case 12: /*SetItemHeight*/
		{
			int id; m_LastScanf=sscanf(pos,"%d,%u",&id,&tmpUINT);
			retint=SetItemHeight(id,tmpUINT);
		}
		break;
	case 13: /*GetItemHeight*/	retint=GetItemHeight(AtoiPos);	break;
	case 14: /*GetSel*/			retint=GetSel(AtoiPos);	break;
	case 15: /*GetText*/
		if (oStr!=NULL)
		{
			int retint1;
			retint1=GetText(AtoiPos,oStr);	
			if (retint1==LB_ERR) retint1=0;
			oStr[retint1]=0;
		}
		break;
	case 16: /*GetTextLen*/		retint=GetTextLen(AtoiPos);	break;
	case 17: /*SetColumnWidth*/ SetColumnWidth(AtoiPos);	break;
	case 18: /*SetTabStops*/
		if (strchr(pos,',')==NULL) SetTabStops(AtoiPos);
		else
			{
				const char *pos2,*pos3=pos;
				int ts[100];UINT nts=0;
				while((pos3=strchr(pos2=pos3,','))!=NULL && nts<99) ts[nts++]=atoi(++pos2);
				SetTabStops(nts,ts);
			}
		break;
	case 19: /*GetLocale*/	if (oStr!=NULL)	sprintf(oStr,"%u",GetLocale());	break;
	case 20: /*SetLocale*/
		{
			tmpUINT=SetLocale(AtoiPos);
			if (oStr!=NULL)	sprintf(oStr,"%u",tmpUINT);
		}
		break;
	case 21: /*GetCurSel*/	retint=GetCurSel();	break;
	case 22: /*SetCurSel*/	retint=SetCurSel(AtoiPos);	break;
	case 23: /*SetSel*/
		{
			BOOL flg;
			m_LastScanf=sscanf(pos,"%d,%d",&tmpUINT,&flg);
			if (strchr(pos,',')==NULL) flg=TRUE;
			retint=SetSel(tmpUINT,flg);
		}
		break;
	case 24: /*GetCaretIndex*/ retint=GetCaretIndex();	break;
	case 25: /*SetCaretIndex*/
		{
			BOOL flg;
			m_LastScanf=sscanf(pos,"%d,%d",&tmpUINT,&flg);
			if (strchr(pos,',')==NULL) flg=TRUE;
			retint=SetCaretIndex(tmpUINT,flg);
		}
		break;
	case 26: /*GetSelCount*/ retint=GetSelCount();	break;
	case 27: /*GetSelItems*/
		if (oStr!=NULL)
		{
			int nItem=0,*it;
			int flg=0;
			m_LastScanf=sscanf(pos,"%d,%d",&nItem,&flg);
			if (nItem>0)
			{
				it=new int [nItem+5];
				int j,nreal=GetSelItems(nItem,it);
				char brk[5]={127,0,};
				char brk2[5]={7,0,};
				char *posout=oStr;
				*posout=0;
				if (nreal>0 && nreal<=nItem && nreal!=LB_ERR)
					for(j=0;j<nreal;j++)
					{
						if (*oStr!=0)
						{
							strcat(posout,brk);
							posout+=(int)strlen(posout);
						}
						posout+=sprintf(posout,"%d",it[j]);
						if (flg!=0)
						{
							int retint1;
							strcat(posout,brk2);
							posout+=(int)strlen(posout);
							retint1=GetText(it[j],posout);	
							if (retint1==LB_ERR) retint1=0;
							posout[retint1]=0;
							posout+=(int)strlen(posout);
						}
					}
				delete[] it;
			}
		}
		break;
	case 28: /*SelItemRange*/
		{
			int start=0,end=0;BOOL flg=TRUE;
			m_LastScanf=sscanf(pos,"%d,%d,%d",&flg,&start,&end);
			if (start>=0 && start<=end)
				retint=SelItemRange(flg,start,end);
		}
		break;
	case 29: /*SetAnchorIndex*/ SetAnchorIndex(AtoiPos);	break;
	case 30: /*GetAnchorIndex*/	retint=GetAnchorIndex();	break;
	case 31: /*AddString*/		retint=AddString(pos);		break;
	case 32: /*DeleteString*/
		if (ItemDataArray)
		{
			DWORD itemData=GetItemData(AtoiPos);
			ItemDataArray->RemoveItem(itemData);
		}
		retint=DeleteString(AtoiPos);
		break;
	case 33: /*InsertString*/
	case 36: /*FindString*/
	case 37: /*FindStringExact*/
	case 38: /*SelectString*/
		{
			const char *pos2=strchr(pos,',');int ind=AtoiPos;
			if (pos2!=NULL)
			{
				if (nfunc==33)	retint=InsertString(ind,++pos2);
				else
					if (nfunc==36)	retint=FindString(ind,++pos2);
					else
						if (nfunc==37)	retint=FindStringExact(ind,++pos2);
						else
							if (nfunc==38)	retint=SelectString(ind,++pos2);
			}
			else	if (oStr!=NULL)	sprintf(oStr,"ERROR");
		}
		break;
	case 34: /*ResetContent*/
		if (ItemDataArray) 
		{
			delete ItemDataArray;
			ItemDataArray=NULL;
		}
		ResetContent();
		break;
	case 35: /*Dir*/
		{
			const char *attr="WRHSDAIE",*pos2=pos,*pos3;
			UINT UAttr=0,flg[8]={0x0000,0x0001,0x0002,0x0004,0x0010,0x0020,0x4000,0x8000,};
			while(*pos2!=0 && *pos2!=',')
				if ((pos3=strchr(attr,*(pos2++)))!=NULL) UAttr|=flg[pos3-attr];
			if (*pos2!=0) pos2++;
			retint=Dir(UAttr,pos2);
		}
		break;
	case 41: /*CompareItem*/
	case 43: /*VKeyToItem*/
	case 44: /*CharToItem*/ if (oStr!=NULL)	sprintf(oStr,"not released in this version");break;
	case 42: /*DeleteItem ItemData*/
		{
			retint=CB_ERR;
			int nItems=GetCount();
			*oStr=0;
			int i;
			for(i=0;i<nItems && AtoiPos!=(int)GetItemData(i);i++);
			if (i!=nItems) 
			{
				if (ItemDataArray) ItemDataArray->RemoveItem(AtoiPos);
				DeleteString(i);
			}
		}
		break;
	case 45: /*SetCheckStyle*/
		{
			char *lpstl[23]={"_AUTO3STATE|","_CHECKBOX|","_DEFPUSHBUTTON|","_GROUPBOX|","_LEFTTEXT|","_OWNERDRAW|","_PUSHBUTTON|","_RADIOBUTTON|","_3STATE|","_TEXT|","_ICON|","_BITMAP|","_LEFT|","_RIGHT|","_CENTER|","_TOP|","_BOTTOM|","_VCENTER|","_PUSHLIKE|","_MULTILINE|","_NOTIFY|","_FLAT|","_RIGHTBUTTON|",};
			UINT  uistl[23]={BS_AUTO3STATE, BS_CHECKBOX, BS_DEFPUSHBUTTON, BS_GROUPBOX, BS_LEFTTEXT, BS_OWNERDRAW, BS_PUSHBUTTON, BS_RADIOBUTTON, BS_3STATE, BS_TEXT, BS_ICON, BS_BITMAP, BS_LEFT, BS_RIGHT, BS_CENTER, BS_TOP, BS_BOTTOM, BS_VCENTER, BS_PUSHLIKE, BS_MULTILINE, BS_NOTIFY, BS_FLAT, BS_RIGHTBUTTON,};
			UINT tmpstl=0;
			int i;
			for(i=0;i<23;i++)
				if (strstr(pos,lpstl[i])!=NULL) tmpstl|=uistl[i];

			SetCheckStyle(tmpstl);
		}
	case 46: /*GetCheckStyle*/
		if (oStr!=NULL)
		{
			tmpUINT=GetCheckStyle();
			*oStr=0;
			char brk[5]={127,0,};
			char *lpstl[25]={"_AUTOCHECKBOX|","_AUTORADIOBUTTON|","_AUTO3STATE|","_CHECKBOX|","_DEFPUSHBUTTON|","_GROUPBOX|","_LEFTTEXT|","_OWNERDRAW|","_PUSHBUTTON|","_RADIOBUTTON|","_3STATE|","_TEXT|","_ICON|","_BITMAP|","_LEFT|","_RIGHT|","_CENTER|","_TOP|","_BOTTOM|","_VCENTER|","_PUSHLIKE|","_MULTILINE|","_NOTIFY|","_FLAT|","_RIGHTBUTTON|",};
			UINT  uistl[25]={BS_AUTOCHECKBOX,BS_AUTORADIOBUTTON,BS_AUTO3STATE,BS_CHECKBOX,BS_DEFPUSHBUTTON,BS_GROUPBOX,BS_LEFTTEXT,BS_OWNERDRAW,BS_PUSHBUTTON,BS_RADIOBUTTON,BS_3STATE,BS_TEXT,BS_ICON,BS_BITMAP,BS_LEFT,BS_RIGHT,BS_CENTER,BS_TOP,BS_BOTTOM,BS_VCENTER,BS_PUSHLIKE,BS_MULTILINE,BS_NOTIFY,BS_FLAT,BS_RIGHTBUTTON,};
			int i;
			for(i=0;i<25;i++)
				if ((tmpUINT&uistl[i])==uistl[i])
				{
					if (*oStr!=0) strcat(oStr,brk);
					strcat(oStr,lpstl[i]);
				}
		}
		break;
	case 47: /*SetCheck*/
		{
			int ind,check;
			m_LastScanf=sscanf(pos,"%d,%d",&ind,&check);
			SetCheck(ind,check);
		}
		break;
	case 48: /*GetCheck*/	retint=GetCheck(AtoiPos);		break;
	case 49: /*Enable*/
		{
			int ind,enab;
			m_LastScanf=sscanf(pos,"%d,%d",&ind,&enab);
			Enable(ind,enab);
		}
		break;
	case 50: /*IsEnabled*/	retint=IsEnabled(AtoiPos);		break;
	case 51: /*GetChecked*/
		if (oStr)
		{
			int i,nItem=GetCount( );
			char brk[5]={127,0,};
			char *posout=oStr;
			*posout=0;
			if (nItem!=LB_ERR)
				for(i=0;i<nItem;i++)
					if (GetCheck(i)==TRUE)
					{
						if (*oStr)
						{
							strcat(posout,brk);
							posout+=(int)strlen(posout);
						}
						posout+=sprintf(posout,"%d%c",i,7);

						int retint1;
						retint1=GetText(i,posout);	
						if (retint1==LB_ERR) retint1=0;
						posout[retint1]=0;
						posout+=retint1;
					}
		}
		break;
	case 52: /*GetSelectedItem*/	if (oStr!=NULL)	GetSelectedItem(oStr);break;
	case 53: /*UpdateGroup*/
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
		{
			retint=GetCurSel();
			int nItem=GetCount();
			if (retint==LB_ERR && nItem!=LB_ERR)
			{
				int *it;
				it=new int [nItem+5];
				int j,nreal=GetSelItems(nItem,it);
				if (nreal==0) referGPU[UnitId&0xFFFF]->UpdateGroup(-123456,GetStyle());
				else
				for(j=0;j<nreal;j++)
					referGPU[UnitId&0xFFFF]->UpdateGroup(it[j]+(j!=0)*0x1000,GetStyle());

				delete[] it;
			}
			else
				referGPU[UnitId&0xFFFF]->UpdateGroup(retint,GetStyle());
		}
		break;
	case 54: /*GetStyle*/
		if (oStr!=NULL)
			GetObjStlStr(oStr, GetStyle(), N_LISTBOX_STYLES,  aListBoxStyleName, aListBoxStyleUINT, aListBoxStyleMask);
		break;
	case 55: /*AddStrings*/
		{
			char *postmpcc=new char [(int)strlen(pos)+10];
			strcpy(postmpcc,pos);
			char *pos1=postmpcc;
			char *pos2;
			retint=0;
			do
			{
				if ((pos2=strchr(pos1,GPC.DelimiterIn1))!=NULL) *pos2=0;
				if (AddString(pos1)!=LB_ERR) retint++;
				pos1=pos2+1;
			}while(pos2!=NULL);
			delete[] postmpcc;
		}
		break;
	case 56: /*GetContents*/
		if (oStr!=NULL)
		{
			int nItem=GetCount(),len=0;
			char *postxt=oStr;
			if (nItem>0)
			{
				int i;
				for(i=0;i<nItem;i++)
				{
					postxt[len=GetText(i,postxt)]=0;
					postxt[len]=0;
					if (i<nItem-1) strcat(postxt,"\x7F");
					postxt+=(int)strlen(postxt);
				}
			}
		}
		break;

	case 57: /*SelectAll*/
	case 58: /*DeSelectAll*/
		{
			int nItem=GetCount();
			if (nItem!=LB_ERR)
				SelItemRange(nfunc==57, 0, --nItem);
		}
		break;
	case 59: /*SelectionDelete*/
	case 60: /*SelectionInvert*/
	case 61: /*SelectionDoMethod*/
	case 62: /*SetSelection*/
	case 63: /*SelectionCheck*/
		{
			int nItemAll=GetCount();
			int i;
			if (nItemAll!=LB_ERR && nItemAll>0)
			{
				int *it=new int [nItemAll+5];
				int nSel=GetSelItems(nItemAll,it);
				if (nSel!=LB_ERR && nSel>0)
				{
					switch(nfunc)
					{
					case 59: /*SelectionDelete*/
						qsort(it, nSel,sizeof(int),CompareIntDES);
						for(i=0;i<nSel;i++)
						{
							if (ItemDataArray)
							{
								DWORD itemData=GetItemData(it[i]);
								ItemDataArray->RemoveItem(itemData);
							}
							DeleteString(it[i]);
						}
						break;
					case 60: /*SelectionInvert*/
						{
							int curItem=0;
							qsort(it, nSel,sizeof(int),CompareIntASC);
							for(i=0;i<nSel;i++)
							{
								while(curItem<it[i])
									SetSel(curItem++,TRUE);

								SetSel(curItem++,FALSE);
							}
						}
						break;
					case 61: /*SelectionDoMethod*/
						{
							char *postmpcc=new char [(int)strlen(pos)+10];
							strcpy(postmpcc,pos);
							qsort(it, nSel,sizeof(int),CompareIntDES);
							char *posstr=oStr;
							char *selmet=new char [(int)strlen(postmpcc)+100];
							char *pos2=strchr(postmpcc,' ');
							if (!pos2) pos2="";
							else 
							{
								*(pos2++)=0;
								while(*pos2==' ') pos2++;
							}

							for(i=0;i<nSel;i++)
							{
								sprintf(selmet,"%s %d,%s",postmpcc,it[i],pos2);
								DoMethod(selmet,posstr);
								if (posstr!=NULL)
								{
									if (i<nSel-1) strcat(posstr,"\x06");
									posstr+=(int)strlen(posstr);
								}
							}
							delete[] selmet;
							delete[] postmpcc;
						}
						break;
					case 62: /*SetSelection*/
						{
							SelItemRange(FALSE, 0, nItemAll-1);
							int nItem;
							while(*pos!=0)
							{
								nItem=atoi(pos);
								if ((nItem=atoi(pos))<nItemAll && nItem>=0)
									SetSel(nItem,TRUE);

								while(*pos>='0' && *pos<='9') pos++;

								if (*pos=='-')
								{
									int nItem2=atoi(++pos);
									while(++nItem<nItemAll && nItem<=nItem2 && nItem>=0)
										SetSel(nItem,TRUE);

									while(*pos>='0' && *pos<='9') pos++;
								}
								if (*pos==',') pos++;
							}
						}
						break;
					case 63: /*SelectionCheck*/
						{
							int chk=atoi(pos);
							for(i=0;i<nSel;i++)
								SetCheck(it[i],chk);
						}
						break;
					}
				}
			}
		}
		break;
	case 64: /*FillFromSpr*/  //"SprName,Separator,nField1,nField2..."
	case 67: /*AddFromSpr*/  //"SprName,Separator,nField1,nField2..."
		{
			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
			char *tmp=pos333,*tmp2;
			tmp2=strchr(tmp,',');
			if (tmp2!=NULL) *(tmp2++)=0;
			else tmp2="";
			CGPSpr *spr=GPC.m_SprArray.GetSpr(tmp);
			if (spr!=NULL) retint=spr->FillObject(m_hWnd,GPSPRFILL_LISTBOX,tmp2,nfunc==64?0:1);
			delete[] pos333;
		}
		break;
	case 65: /*ReplaceFromSpr*/ //"SprName,IdentField,Separator,nField1,nField2..."
		{
			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
			char *tmp=pos333,*tmp2;
			tmp2=strchr(tmp,',');
			if (tmp2!=NULL) *(tmp2++)=0;
			else tmp2="";
			CGPSpr *spr=GPC.m_SprArray.GetSpr(tmp);
			if (spr!=NULL) retint=spr->ReplaceObject(m_hWnd,GPSPRFILL_LISTBOX,tmp2);
			delete[] pos333;
		}
		break;
	case 66: /*FillFromList*/ //"ListName"
	case 68: /*AddFromList*/ //"ListName"
		retint=GPC.m_ListMaker.FillObject(pos,m_hWnd,GPSPRFILL_LISTBOX,nfunc==66?0:1);
	case 70: /*AddFile*/
		retint=SendMessage(LB_ADDFILE,0,(LPARAM)pos);
		break;
	case 71: /*GetListBoxInfo*/
		retint=SendMessage(LB_GETLISTBOXINFO,0,0);
		break;
	case 72: /*AddItem iBefore,ItemData;ItemText*/
		{
			const char *postext=strchr(pos,';');
			if (!(postext++)) postext="";
			DWORD ItemData=0;
			int nItem=-1;
			int itm=LB_ERR;
			if (*pos==',')
			{
				ItemData=atoi(pos+1);
				itm=AddString(postext);
			}
			else
			{
				m_LastScanf=sscanf(pos,"%d,%d",&nItem,&ItemData);
				itm=InsertString(nItem,postext);
			}
			if (itm!=LB_ERR) SetItemData(itm,ItemData);
		}
		break;
	case 73: /*SetItemText iItem,iItemData;Text*/
		{
			const char *postext=strchr(pos,';');
			if (!(postext++)) postext="";
			int nItem=-1;
			DWORD ItemData=0;
			int itm=LB_ERR;
			if (*pos==',')
			{
				ItemData=atoi(pos+1);
				int nItems=GetCount();
				int i;
				for(i=0;i<nItems && itm==LB_ERR;i++)
					if (GetItemData(i)==ItemData)
					{
						DeleteString(i);
						itm=InsertString(i,postext);
					}
			}
			else
			{
				m_LastScanf=sscanf(pos,"%d,%d",&nItem,&ItemData);
				DeleteString(nItem);
				itm=InsertString(nItem,postext);
			}
			if (itm!=LB_ERR) SetItemData(itm,ItemData);
		}
		break;
	case 74: /*SetCurSelByItemData iItemData*/
		{
			retint=LB_ERR;
			int nItems=GetCount();
			DWORD cmpData=atoi(pos);
			int i;
			for(i=0;i<nItems && cmpData!=GetItemData(i);i++);
		
			if (i!=nItems) SetCurSel(retint=i);
		}
		break;
	case 75: /*SetAutoFocus*/
		retint=m_bAutoFocus;
		m_bAutoFocus=atoi(pos);
		break;
	case 76: /*SetItemDataEx*/
		{
			if (!ItemDataArray) ItemDataArray = new GP_RarefiedArr<CString>(5,"");
			DWORD arrId=GetItemData(AtoiPos);
			if (arrId==CB_ERR || !arrId)
			{
				arrId=ItemDataArray->GetMaxId()+1;
				SetItemData(AtoiPos,arrId);
			}
			const char *pos2=strchr(pos,',');
			if (!pos2++) pos2="";
			(*ItemDataArray)[arrId]=pos2;
			retint=arrId;
		}
		break;
	case 77: /*GetItemDataEx*/
		if (oStr!=NULL)
		{
			DWORD arrId=GetItemData(AtoiPos);
			if (!ItemDataArray || arrId==CB_ERR || !arrId) sprintf(oStr,"%u",arrId);
			else
			{
				strcpy(oStr,(*ItemDataArray)[arrId]);
			}
		}
		break;

	case 78: /*AddItemEx [iBefore],ItemDataEx;ItemText*/
		{
			if (!ItemDataArray) ItemDataArray = new GP_RarefiedArr<CString>(5,"");
			char *tmppos=new char [(int)strlen(pos)+10];
			strcpy(tmppos,pos);
			char *postext=strchr(tmppos,';');
			if (postext) *(postext++)=0;
			else postext="";

			char *posdata=strchr(tmppos,',');
			if (posdata) *(posdata++)=0;
			else posdata="";

			DWORD ItemData=0;
			int nItem=-1;
			int itm=CB_ERR;
			if (*pos==',')
				itm=AddString(postext);
			else
				itm=InsertString(nItem,postext);

			if (itm!=CB_ERR)
				SetItemData(itm,ItemDataArray->AddItem(posdata));
			delete[] tmppos;
		}
		break;

	case 79: /*SetItemTextEx [iItem],iItemDataEx;Text*/
		if (ItemDataArray)
		{
			char *tmppos=new char [(int)strlen(pos)+10];
			strcpy(tmppos,pos);
			char *postext=strchr(tmppos,';');
			if (postext) *(postext++)=0;
			else postext="";

			char *posdata=strchr(tmppos,',');
			if (posdata) *(posdata++)=0;
			else posdata="";
			DWORD tmpItemData=ItemDataArray->GetIdByVal(posdata);

			int itm=CB_ERR;
			if (*pos==',')
			{
				int nItems=GetCount();
				int i;
				for(i=0;i<nItems && itm==CB_ERR;i++)
					if (GetItemData(i)==tmpItemData)
					{
						DeleteString(i);
						itm=InsertString(i,postext);
					}
			}
			else
			{
				DeleteString(AtoiPos);
				itm=InsertString(AtoiPos,postext);
			}
			if (itm!=CB_ERR)
			{
				if (tmpItemData>ItemDataArray->GetCount())
					tmpItemData=ItemDataArray->AddItem(posdata);
				SetItemData(itm,tmpItemData);
			}
			delete[] tmppos;
		}
		break;

	case 80: /*SetCurSelByItemDataEx ItemDataEx*/
		if (ItemDataArray)
		{
			retint=CB_ERR;
			int nItems=GetCount();
			DWORD cmpData=ItemDataArray->GetIdByVal(pos);
			int i;
			for(i=0;i<nItems && cmpData!=GetItemData(i);i++);
		
			if (i!=nItems) SetCurSel(retint=i);
		}
		break;

	case 39: /*GetItemTextEx ItemDataEx*/
	case 40: /*GetItemText ItemData*/
		if (oStr)
		{
			int retint1;
			retint1=CB_ERR;
			int nItems=GetCount();
			*oStr=0;
			DWORD cmpData=(ItemDataArray && nfunc==79)?ItemDataArray->GetIdByVal(pos):AtoiPos;
			int i;
			for(i=0;i<nItems && cmpData!=GetItemData(i);i++);
			if (i!=nItems)
			{
				retint1=GetText(i,oStr);
				if (retint1==LB_ERR) retint1=0;
				oStr[retint1]=0;
			}
		}
		break;
	case 69: /*DeleteItemEx ItemDataEx*/
		{
			retint=CB_ERR;
			int nItems=GetCount();
			*oStr=0;
			DWORD cmpData=(ItemDataArray)?ItemDataArray->GetIdByVal(pos):AtoiPos;
			int i;
			for(i=0;i<nItems && cmpData!=GetItemData(i);i++);
			if (i!=nItems) 
			{
				if (ItemDataArray) ItemDataArray->RemoveItem(cmpData);
				DeleteString(i);
			}
		}
		break;

	default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456)	sprintf(oStr,"%d",retint);

	return nfunc;
}


UINT GPChLBox::GPSetProperty(char *iStr)
{
	char *iValue=new char [(int)strlen(iStr)+5];
	strcpy(iValue,iStr);
	UINT ret=1,i;
	char *pos=strchr(iValue,'=');

	if (pos!=NULL && m_hWnd)
	{
		char *prop[]={ "ADDSTYLE", "DELSTYLE","STYLE",};
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
					// ListBOX specif
					for(i=0;i<N_LISTBOX_STYLES;i++)
						if (strstr(pos,aListBoxStyleName[i])!=NULL)
							switch(propnum)
							{
							case 2: /* STYLE*/
							case 0: /* ADDSTYLE*/	ModifyStyle(0,aListBoxStyleUINT[i]);break;
							case 1: /* DELSTYLE*/	ModifyStyle(aListBoxStyleUINT[i],0);break;
							}
					Invalidate();
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

void GPChLBox::OnSelchange()
{
	CString str;
	CString str2;
	int id= GetCurSel();
	if (id>=0) GetText( id, str2);
	str.Format("%d\x7F",GetCurSel());
	str+=str2;
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSelchange",str);
		if (referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
			DoMethod("UpdateGroup",NULL);
	}
}

void GPChLBox::OnErrspace()
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnErrspace","");
}

void GPChLBox::OnSelcancel()
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
	{
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSelcancel","");
			if (referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
			DoMethod("UpdateGroup",NULL);
	}
}

void GPChLBox::OnParentNotify(UINT message, LPARAM lParam)
{
	char txt[100];
	if (message==WM_CREATE || message==WM_DESTROY)
		sprintf(txt,"%d\x7F%d\x7F%X",message/0x10000,(message&0xFFFF),lParam/0x10000);
	else
		sprintf(txt,"%d\x7F%d\x7F%d\x7F%d",message/0x10000,(message&0xFFFF),lParam/0x10000,(lParam&0xFFFF));

	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"ParentNotify",txt);

	CCheckListBox::OnParentNotify(message, lParam);
}

int GPChLBox::CharToItem(UINT nChar, UINT nIndex)
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"CharToItem","");
	return 0;
}

CRect GPChLBox::OnGetCheckPosition( CRect rectItem, CRect rectCheckBox )
{
	m_rectCheckBox=rectCheckBox;
	return rectCheckBox;
}

int GPChLBox::VKeyToItem(UINT nKey, UINT nIndex)
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"VKeyToItem","");
	return -1;
}

HBRUSH GPChLBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CCheckListBox::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}

char * GPChLBox::GetSelectedItem(char *iStr)
{
	int Sel=GetCurSel();
	char tmp[200];
	int nn=GetText(Sel,iStr);
	if (nn==LB_ERR) nn=0;
	iStr[nn]=0;
	CRect re;
	GetItemRect(Sel,&re);
	sprintf(tmp,"\x7F%d\x7F%ld\x7F%ld\x7F%d\x07%d\x07%d\x07%d",Sel,GetLocale(),GetItemData(Sel),re.left,re.top,re.right,re.bottom);
	strcat(iStr,tmp);
	return iStr;
}

LRESULT GPChLBox::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (referGPU && referGPU[UnitId&0xFFFF] && message!=WM_MEASUREITEM && message!=WM_DRAWITEM)
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
		UINT ret;
		if (message==GPM_CLIENTKILLFOCUS || message==GPM_CLIENTSETFOCUS)
		{
			PGPUNITINFO ui=(PGPUNITINFO)lParam;
			if (ui)
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent
					(m_hWnd, UnitId,message==GPM_CLIENTSETFOCUS?"OnCSetFocus":"OnCKillFocus",GPUnit::UnitInfoToString2(ui,"\x7F"));
		}
		if ((ret=referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjMessage(m_hWnd, UnitId, message, wParam, lParam))>0) return ret;
		if (message==WM_KEYDOWN && referGPU!=NULL && referGPU[UnitId&0xFFFF]->UnitHotkey && this->m_hWnd!=NULL && IsWindowEnabled()==TRUE && IsWindowVisible()==TRUE)
				if ((ret=referGPU[UnitId&0xFFFF]->UnitHotkey->SendHotkeyMessage(message, wParam,lParam))>0) return ret;
		if (message==GPM_PROCHOTKEY)
		{
			if(referGPU[UnitId&0xFFFF]->UnitHotkey && (ret=referGPU[UnitId&0xFFFF]->UnitHotkey->SendHotkeyMessage(WM_KEYDOWN, wParam,lParam))>0) return ret;
			GetParent()->SendMessage(message, wParam,lParam);
		}
		else
		if  (message==WM_KEYDOWN)
			GetParent()->SendMessage(GPM_PROCHOTKEY, wParam,lParam);
	}

	if (message==WM_KILLFOCUS)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnKillfocus","");
	else
		if (message==WM_SETFOCUS)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSetfocus","");
	else
	if (message==WM_SIZEPARENT && referGPU!=NULL)
	{
		UINT SizStyle=referGPU[UnitId&0xFFFF]->SizStyle;
		if ((SizStyle&0xFFFF0000)!=0)
		{
			AFX_SIZEPARENTPARAMS* lpLayout =(AFX_SIZEPARENTPARAMS*)lParam;

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
		if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDragLeave","");
		HighlightDropTarget(NULL,CPoint(-111,-111));
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
	if (message==WM_SETFOCUS && m_bAutoFocus && ::GetFocus()==m_hWnd && wParam==(WPARAM)m_hWnd)  
		lpr=FALSE;
	else
	if (message==WM_SETCURSOR && GPC.m_bWaitCursor) lpr=FALSE;
	else lpr=CCheckListBox::WindowProc(message, wParam, lParam);

	return lpr;
}

void GPChLBox::OnLButtonDown(UINT nFlags, CPoint point)
{
	CCheckListBox::OnLButtonDown(nFlags, point);
}

void GPChLBox::OnLButtonUp(UINT nFlags, CPoint point)
{
	CCheckListBox::OnLButtonUp(nFlags, point);
}



BOOL GPChLBox::PreTranslateMessage(MSG* pMsg)
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
				if ((ret=referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjMessage(m_hWnd, UnitId, pMsg->message, pMsg->wParam, pMsg->lParam))>0) return ret;
				if (pMsg->message==WM_KEYDOWN && referGPU!=NULL && referGPU[UnitId&0xFFFF]->UnitHotkey && this->m_hWnd!=NULL && IsWindowEnabled()==TRUE && IsWindowVisible()==TRUE)
						if ((ret=referGPU[UnitId&0xFFFF]->UnitHotkey->SendHotkeyMessage(pMsg->message, pMsg->wParam,pMsg->lParam))>0) return ret;
			}

			if (pMsg->message==WM_LBUTTONDOWN)
			{
				int nIt;
				CPoint pt(pMsg->lParam);
				BOOL ins=FALSE;
				nIt=ItemFromPoint(pt,ins);
				if (nIt!=LB_ERR && !ins)
				{
					CRect re;
					GetItemRect(nIt, &re);
					if (re.top<=pt.y && re.bottom>=pt.y && m_rectCheckBox.left<=pt.x && m_rectCheckBox.right>=pt.x )//MAKEPOINTS(pMsg->lParam).y<=re.bottom)
					{
						char *buff=new char [10000];
						int nl=GetText(nIt,buff+100);
						if (nl==LB_ERR) nl=0;
						else buff[nl+100]=0;
						buff[nl+100]=0;
						sprintf(buff,"%d\x7F%s\x7F%d",nIt,buff+100,1-GetCheck(nIt));
						referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnCheck",buff);
						delete[] buff;
					}
				}
			}
			else
			if (pMsg->message==WM_LBUTTONDBLCLK)
			{
				char *buff=new char [10000];
				GetSelectedItem(buff);
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDblclk",buff);
				delete[] buff;
			}
		}
	}
	return CCheckListBox::PreTranslateMessage(pMsg);
}


void GPChLBox::OnClose()
{
	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClose","");
//	CCheckListBox::OnClose();
}

void GPChLBox::OnSizing(UINT fwSide, LPRECT pRect)
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
			if ((SizStyle&GPUA_BOTTOM)!=GPUA_BOTTOM &&(SizStyle&GPUA_LEFT)!=GPUA_LEFT) EnableSz=FALSE;
			break;
		case WMSZ_BOTTOMRIGHT:
			if ((SizStyle&GPUA_BOTTOM)!=GPUA_BOTTOM &&(SizStyle&GPUA_RIGHT)!=GPUA_RIGHT) EnableSz=FALSE;
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
			if ((SizStyle&GPUA_LEFT)!=GPUA_LEFT &&(SizStyle&GPUA_TOP)!=GPUA_TOP) EnableSz=FALSE;
			break;
		case WMSZ_TOPRIGHT:
			if ((SizStyle&GPUA_RIGHT)!=GPUA_RIGHT &&(SizStyle&GPUA_TOP)!=GPUA_TOP) EnableSz=FALSE;
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

	if (EnableSz) CCheckListBox::OnSizing(fwSide, pRect);

	GetParent()->SendMessage(GPN_UPDATESIZE);

}

void GPChLBox::OnDragMouseHover()
{
	if (referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(GPC.m_DragDrop.DragName)<0xFFFFFFFFL)
	{
		// Reset the timer.
		::SetTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nScrollInterval, NULL);

		// Get the current cursor position and window height.
		DWORD dwPos = ::GetMessagePos();
		CPoint point(LOWORD(dwPos), HIWORD(dwPos));
		ScreenToClient(&point);

		CRect rect;
		GetClientRect(rect);
		int cy = rect.Height();

		// Scroll the window if the cursor is near the top or bottom.
		if (point.y >= 0 && point.y <= referGPU[UnitId&0xFFFF]->m_nScrollMargin)
		{
			int iFirstVisible = GetTopIndex();
			GPC.m_DragDrop.pImageList->DragShowNolock(FALSE);
			SendMessage(WM_VSCROLL, MAKEWPARAM(SB_LINEUP, 0), NULL);
			GPC.m_DragDrop.pImageList->DragShowNolock(TRUE);

			// Kill the timer if the window did not scroll, or redraw the drop target highlight if the window did scroll.
			if (GetTopIndex() == iFirstVisible)
				::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);
			else
				HighlightDropTarget(&GPC.m_DragDrop, point);
		}
		else
			if (point.y >= cy - referGPU[UnitId&0xFFFF]->m_nScrollMargin && point.y <= cy)
			{
				int iFirstVisible = GetTopIndex();
				GPC.m_DragDrop.pImageList->DragShowNolock(FALSE);
				SendMessage(WM_VSCROLL, MAKEWPARAM(SB_LINEDOWN, 0), NULL);
				GPC.m_DragDrop.pImageList->DragShowNolock(TRUE);

				// Kill the timer if the window did not scroll, or redraw the drop target highlight if the window did scroll.
				if (GetTopIndex() == iFirstVisible) ::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);
				else
					HighlightDropTarget(&GPC.m_DragDrop, point);
			}
			else  ::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);

		BOOL mb_Out;
		int HiItem=ItemFromPoint(point,mb_Out);
		if (!mb_Out && HiItem!=LB_ERR)
		{
			CString tmps;
			CString tmpstext;
			GetText(HiItem,tmpstext);
			tmps.Format("%d\x07%s",HiItem,(LPCSTR)tmpstext);
			referGPU[UnitId&0xFFFF]->SendDropHoverEvent(tmps,&GPC.m_DragDrop,&point);
		}
	}
}

void GPChLBox::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
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
		pDrDrStruct->pImageList->DragMove(CPoint(*point));

		DWORD dHiItem=0xFFFFFFFF;
		BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
		// Highlight the drop target if the cursor is over an item.
		if (mDrop)
			dHiItem = HighlightDropTarget(pDrDrStruct, CPoint(*point));
		// Modify the cursor to provide visual feedback to the user. Note: It's important to do this AFTER the call to DragMove.
		::SetCursor(dHiItem == 0xFFFFFFFF ?
			AfxGetApp()->LoadStandardCursor(IDC_NO) :
			(HCURSOR) ::GetClassLong(m_hWnd, GCL_HCURSOR));

		BOOL mb_Out;
		int HiItem=ItemFromPoint(*point,mb_Out);
		if (!mb_Out && HiItem!=LB_ERR)
		{
			CString tmps;
			CString tmpstext;
			GetText(HiItem,tmpstext);
			tmps.Format("%d\x07%s",HiItem,(LPCSTR)tmpstext);
			referGPU[UnitId&0xFFFF]->SendDropMoveEvent(tmps,pDrDrStruct,point);
		}
		// Set a timer if the cursor is at the top or bottom of the window, or if it's over a collapsed item.
		if (mDrop)
			::SetTimer(pDrDrStruct->hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nDelayInterval, NULL);
	}
}

void GPChLBox::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && referGPU)
	{
		::ScreenToClient(m_hWnd,point);

		BOOL mb_Out;
		int HiItem=ItemFromPoint(*point,mb_Out);
		CString tmps;
		if (!mb_Out && HiItem!=LB_ERR)
		{
			CString tmpstext;
			GetText(HiItem,tmpstext);
			tmps.Format("%d\x07%s",HiItem,(LPCSTR)tmpstext);
			referGPU[UnitId&0xFFFF]->SendDropHoverEvent(tmps,&GPC.m_DragDrop,point);
		}
		else
			tmps="-1\x7";

		CRect re;
		GPC.m_DragDrop.pImageList->DragShowNolock(FALSE);
		if (m_LastHighLight>=0)
		{
			GetItemRect(m_LastHighLight,&re);
			GetDC()->InvertRect(&re);
			m_LastHighLight=-1;
		}
		GPC.m_DragDrop.pImageList->DragShowNolock(TRUE);

		referGPU[UnitId&0xFFFF]->SendDropEvent(tmps,pDrDrStruct,point);
	}
}

DWORD GPChLBox::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	BOOL mb_Out;
	DWORD res=0xFFFFFFFF;
	int HiItem=ItemFromPoint(point,mb_Out);
	res=HiItem;

	GPC.m_DragDrop.pImageList->DragShowNolock(FALSE);
	CRect re;

	if (HiItem!=m_LastHighLight)
	{
		if (m_LastHighLight>=0)
		{
			GetItemRect(m_LastHighLight,&re);
			GetDC()->InvertRect(&re);
		}
		if (pDrDrStruct && !mb_Out && HiItem!=LB_ERR)
		{
			GetItemRect(HiItem,&re);
			GetDC()->InvertRect(&re);
		}
		else HiItem=LB_ERR;
	}

	if (!mb_Out && HiItem!=LB_ERR)
		res=HiItem;

	GPC.m_DragDrop.pImageList->DragShowNolock(TRUE);
	m_LastHighLight=HiItem;
	return res;
}

LRESULT GPChLBox::OnNcHitTest(CPoint point)
{
	LRESULT ret=CCheckListBox::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

#include "GP_TermDoc.h"

void GPChLBox::OnKillFocus(CWnd* pNewWnd)
{
	CCheckListBox::OnKillFocus(pNewWnd);
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

void GPChLBox::OnSetFocus(CWnd* pOldWnd)
{
	CCheckListBox::OnSetFocus(pOldWnd);
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

void GPChLBox::OnSize(UINT nType, int cx, int cy)
{
	CCheckListBox::OnSize(nType, cx, cy);

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
	}
}

void GPChLBox::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CCheckListBox::OnHScroll(nSBCode, nPos, pScrollBar);
	if (referGPU && referGPU[UnitId&0xFFFF]->m_SizerArray)	Invalidate();
}

void GPChLBox::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CCheckListBox::OnVScroll(nSBCode, nPos, pScrollBar);
	if (referGPU && referGPU[UnitId&0xFFFF]->m_SizerArray)	Invalidate();
}

int GPChLBox::AddChar(char iChar, DWORD iFlags)
{
	int ret=0;
	if (iChar)
	{
		int nItem=GetCount();
		CString text="";
		if (nItem) 	GetText(--nItem,text);
		else 
		{
			nItem=0;
			AddString("");
		}

		if (m_LCDOflag  && iChar)
		{
			if (text!="") nItem=AddString("");
			text="";
		}

		if (iChar==10 && (iFlags&0x2))
		{
			text="";
		}
		else 
		if (iChar==13 || (iChar==GPC.DelimiterIn1 && (iFlags&0x8)))
		{
			m_LCDOflag=1;
		}
		else 
		if (iChar==8 && (iFlags&0x4))
		{
			int pos=text.GetLength();
			if (pos) text=text.Left(pos-1);
		}
		else 
		if (iChar) text+=iChar;

		DeleteString(nItem);
		AddString(text);
		ret=text.GetLength();
	}
	return ret;
}

int GPChLBox::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message) 
{
	int ret=CCheckListBox::OnMouseActivate(pDesktopWnd, nHitTest, message);
	if (m_bAutoFocus && ::GetFocus()!=m_hWnd)
		::PostMessage(m_hWnd,GPM_SETFOCUSTOWND,(WPARAM)m_hWnd,0);
	return ret;
}
