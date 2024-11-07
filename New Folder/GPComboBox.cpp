// GPComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "GP_term.h"
#include "GPComboBox.h"
#include "GP_TermDoc.h"
#include "GPEdit.h"
#include "GPListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPComboBox
const UINT GPComboBox::uNMethods=79;
const char *GPComboBox::cArrMethods[]={
/*00*/		"InitStorage",		"GetCount",		"GetCurSel",	"SetCurSel",	"GetEditSel",
/*05*/		"SetEditSel",		"SetItemData",	"SetItemDataPtr","GetItemData",	"GetItemDataPtr",
/*10*/		"GetTopIndex",		"SetTopIndex",	"GetHorizontalExtent","SetHorizontalExtent","SetDroppedWidth",
/*15*/		"GetDroppedWidth",	"Clear",		"Copy",			"Cut",			"Paste",
/*20*/		"LimitText",		"SetItemHeight","GetItemHeight","GetLBText",	"GetLBTextLen",
/*25*/		"ShowDropDown",		"GetDroppedControlRect","GetDroppedState","SetExtendedUI","GetExtendedUI",
/*30*/		"GetLocale",		"SetLocale",	"AddString",	"DeleteString",	"InsertString",
/*35*/		"ResetContent",		"Dir",			"FindString",	"FindStringExact","SelectString",
/*40*/		"GetItemTextEx",			"DeleteItemEx",	"CompareItem",	"DeleteItem",	"AddStrings",
/*45*/		"UpdateGroup",		"GetEditText",	"AddStringIfNone","FillFromSpr","ReplaceFromSpr",
/*50*/		"FillFromList",		"AddFromSpr",	"AddFromList",	"GetContents",	"SelectionDelete",
/*55*/		"SetMinDroppedWidth","SetMinDroppedHeight","GetMinVisible","SetMinVisible","SetMaxDroppedHeight",
/*60*/		"GetMinDroppedWidth","GetMinDroppedHeight","GetMaxDroppedHeight","GetComboBoxInfo","SetEditProperty",
/*65*/		"DoEditMethod",		"SetListProperty","DoListMethod","GetCurSelEx",	"SetAutoFocus",
/*70*/		"AddItem",			"SetItemText",	"SetCurSelByItemData","SetItemDataEx","GetItemDataEx",
/*75*/		"AddItemEx",		"SetItemTextEx","SetCurSelByItemDataEx","GetItemText","",
/*80*/		"",
		"","","", "", "", 
	};

const char *GPComboBox::cArrMethodsParams[]={
/*00*/		"lines, nbytes",	"",				"",				"nSelect",		"",
/*05*/		"nStartChar, nEndChar","nIndex, iData","nIndex, iPtr","nIndex",		"nIndex",
/*10*/		"",					"nIndex",		"",				"nExtent",		"nWidth",
/*15*/		"",					"",				"",				"",				"",
/*20*/		"nMaxChars",		"nIndex, cyItemHeight","nIndex","nIndex",		"nIndex",
/*25*/		"bShowIt",			"",				"",				"bExtended",	"",
/*30*/		"",					"nNewLocale",	"Text",			"nIndex",		"nIndex,Text",
/*35*/		"",					"RWHSDAIE,DirName","nIndex,Text","nIndex,Text",	"nIndex,Text",
/*40*/		"ItemDataEx",		"ItemDataEx",	"Not Present",	"ItemData",	"Str1^Str2,...,StrN",
/*45*/		"",					"",				"Text",			"SprName,Separator,nField1,nField2...","SprName,IdentField,Separator,nField1,nField2...",
/*50*/		"ListName",			"SprName,Separator,nField1,nField2...","ListName","","",
/*55*/		"MinWidth",			"MinHeight",	"",				"nMinVisible",	"MaxHeight",
/*60*/		"",					"",				"",				"",				"",
/*65*/		"",					"",				"",				"",				"bAuto",
/*70*/		"[iBefore],ItemData;ItemText","[iItem],iItemData;Text","ItemData","ItemId,ItemDataEx","ItemId",
/*75*/		"[iBefore],ItemDataEx;ItemText","[iItem],iItemDataEx;Text","ItemDataEx","ItemData","",
/*80*/		"",
		"","","", "", "", 
	};


GPComboBox::GPComboBox(UINT iUnitId)
{
	ItemDataArray=NULL;
	m_LCDOflag=0;
	referGPU=NULL;
	UnitId=iUnitId;
	m_MinListWidth=0;
	m_uMinDroppedHeight=0;
	m_uMaxDroppedHeight=0;
	m_bAutoFocus=TRUE;
}

GPComboBox::~GPComboBox()
{
	if (ItemDataArray) delete ItemDataArray;
	ItemDataArray=NULL;
}


BOOL GPComboBox::SetreferGPU(GPUnit **iGPU)
{
	return (referGPU=iGPU)!=NULL;
}

BEGIN_MESSAGE_MAP(GPComboBox, CComboBox)
	//{{AFX_MSG_MAP(GPComboBox)
	ON_WM_PARENTNOTIFY_REFLECT()
	ON_WM_CLOSE()
	ON_WM_SIZING()
	ON_WM_NCHITTEST()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPComboBox message handlers

UINT GPComboBox::DoMethod(const char *iStr, char *oStr)
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
	case 2: /*GetCurSel*/
		if (oStr!=NULL)
		{
			int ret=GetCurSel();
			if (ret!=CB_ERR)
			{
				int len=sprintf(oStr,"%d\x7F",ret);
				int l=GetLBText(ret,oStr+len);
				if (l!=LB_ERR) *(oStr+len+l)=0;
			}
		}
		break;
	case 68: /*GetCurSelEx*/
		if (oStr!=NULL)
		{
			int ret=GetCurSel();
			if (ret!=CB_ERR)
			{
				int len=sprintf(oStr,"%d\x7F",ret);
				int l=GetLBText(ret,oStr+len);
				if (l!=LB_ERR) *(oStr+len+l)=0;
			}
			else
			{
				CString tmps;
				GetWindowText(tmps);
				sprintf(oStr,"-1\x7F%s",(LPCSTR)tmps);
			}
		}
		break;
	case 3: /*SetCurSel*/	retint=SetCurSel(AtoiPos); break;
	case 4: /*GetEditSel*/
		if (oStr!=NULL)
		{
			tmpUINT=GetEditSel();
			sprintf(oStr,"%d\x7F%d",tmpUINT%0xFFFF,tmpUINT/0xFFFF);
		}
		break;
	case 5: /*SetEditSel*/
		{
			UINT left=0,right=1;
			m_LastScanf=sscanf(pos,"%d,%d",&left,&right);
			retint=SetEditSel(left,right);
		}
		break;
	case 6: /*SetItemData*/
		{
			int id; m_LastScanf=sscanf(pos,"%d,%u",&id,&tmpUINT);
			retint=SetItemData(id,tmpUINT);
		}
		break;
	case 7: /*SetItemDataPtr*/
		{
			void *ptr;int id;m_LastScanf=sscanf(pos,"%d,%p",&id,&ptr);
			retint=SetItemDataPtr(id,ptr);
		}
		break;
	case 8: /*GetItemData*/		if (oStr!=NULL)	sprintf(oStr,"%u",GetItemData(AtoiPos));	break;
	case 9: /*GetItemDataPtr*/	if (oStr!=NULL)	sprintf(oStr,"%p",GetItemDataPtr(AtoiPos));	break;
	case 10: /*GetTopIndex*/	retint=GetTopIndex();	break;
	case 11: /*SetTopIndex*/	retint=SetTopIndex(AtoiPos);	break;
	case 12: /*GetHorizontalExtent*/	retint=GetHorizontalExtent();	break;
	case 13: /*SetHorizontalExtent*/	SetHorizontalExtent(AtoiPos);	break;
	case 14: /*SetDroppedWidth*/		retint=SetDroppedWidth(AtoiPos);	break;
	case 15: /*GetDroppedWidth*/		retint=GetDroppedWidth();	break;
	case 16: /*Clear*/			Clear();	break;
	case 17: /*Copy*/			Copy();	break;
	case 18: /*Cut*/			Cut();	break;
	case 19: /*Paste*/			Paste();	break;
	case 20: /*LimitText*/		retint=LimitText(AtoiPos);break;
	case 21: /*SetItemHeight*/
		{
			int id; m_LastScanf=sscanf(pos,"%d,%u",&id,&tmpUINT);
			retint=SetItemHeight(id,tmpUINT);
		}
		break;
	case 22: /*GetItemHeight*/	retint=GetItemHeight(AtoiPos);	break;
	case 23: /*GetLBText*/
		if (oStr!=NULL)
		{
			int l=GetLBText(AtoiPos,oStr);
			if (l!=CB_ERR) *(oStr+l)=0;
		}
		break;
	case 24: /*GetLBTextLen*/	retint=GetLBTextLen(AtoiPos);	break;
	case 25: /*ShowDropDown*/
		SetFocus();
		SendMessage(CB_SHOWDROPDOWN,AtoiPos,0);
		break;
	case 26: /*GetDroppedControlRect*/
		if (oStr!=NULL)
		{
			CRect re;
			GetDroppedControlRect(&re);
			sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
		}
		break;
	case 27: /*GetDroppedState*/	retint=GetDroppedState();	break;
	case 28: /*SetExtendedUI*/		retint=SetExtendedUI(AtoiPos);	break;
	case 29: /*GetExtendedUI*/		retint=GetExtendedUI();	break;
	case 30: /*GetLocale*/			if (oStr!=NULL)	sprintf(oStr,"%u",GetLocale());	break;
	case 31: /*SetLocale*/
		{
			tmpUINT=SetLocale(AtoiPos);
			if (oStr!=NULL)	sprintf(oStr,"%u",tmpUINT);
		}
		break;
	case 32: /*AddString*/		retint=AddString(pos);	break;
	case 33: /*DeleteString*/
		if (ItemDataArray)
		{
			DWORD itemData=GetItemData(AtoiPos);
			ItemDataArray->RemoveItem(itemData);
		}
		retint=DeleteString(AtoiPos);

		break;
	case 34: /*InsertString*/
	case 37: /*FindString*/
	case 38: /*FindStringExact*/
	case 39: /*SelectString*/
		{
			const char *pos2=strchr(pos,',');int ind=AtoiPos;
			if (pos2!=NULL)
			{
				if (nfunc==34)	retint=InsertString(ind,++pos2);
				else
					if (nfunc==37)	retint=FindString(ind,++pos2);
					else
						if (nfunc==38)	retint=FindStringExact(ind,++pos2);
						else
							if (nfunc==39)	retint=SelectString(ind,++pos2);
			}
			else	if (oStr!=NULL)	sprintf(oStr,"ERROR");
		}
		break;
	case 35: /*ResetContent*/
		ResetContent();
		if (ItemDataArray) 
		{
			delete ItemDataArray;
			ItemDataArray=NULL;
		}
		break;
	case 36: /*Dir*/
		{
			const char *attr="RWHSDAIE",*pos2=pos,*pos3;
			UINT UAttr=0,flg[8]={DDL_READWRITE,DDL_READONLY,DDL_HIDDEN,DDL_SYSTEM,DDL_DIRECTORY,DDL_ARCHIVE,DDL_DRIVES,DDL_EXCLUSIVE,};
			while(*pos2!=0 && *pos2!=',')
				if ((pos3=strchr(attr,*(pos2++)))!=NULL) UAttr|=flg[pos3-attr];
			if (*pos2!=0) pos2++;
			retint=Dir(UAttr,pos2);
		}
		break;
	case 42: /*CompareItem*/
		if (oStr!=NULL)	sprintf(oStr,"not released in this version");break;
	case 43: /*DeleteItem ItemData*/
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
	case 44: /*AddStrings*/
		{
			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
			char *pos2,*pos1=pos333;
			retint=0;
			do
			{
				if ((pos2=strchr(pos1,GPC.DelimiterIn1))!=NULL) *pos2=0;
				if (AddString(pos1)!=CB_ERR) retint++;
				pos1=pos2+1;
			}while(pos2!=NULL);
			delete[] pos333;
		}
		break;
	case 45: /*UpdateGroup*/
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
		{
			retint=GetCurSel();
			if (retint==CB_ERR ) retint=-123456;
			referGPU[UnitId&0xFFFF]->UpdateGroup(retint,GetStyle());
		}
		break;
	case 46: /*GetEditText*/
		if (oStr!=NULL)
		{
			int nnn=::GetWindowTextLength(m_hWnd);
			if (nnn) nnn=::GetWindowText(m_hWnd,oStr,nnn+2);
			oStr[nnn]=0;
		}
		break;
	case 47: /*AddStringIfNone*/
		if (*pos==0)
		{
			CString str;
			GetWindowText(str);
			if (FindStringExact(0,str)==CB_ERR )	retint=AddString(str);
		}
		else
			if (FindStringExact(0,pos)==CB_ERR )	retint=AddString(pos);
		break;
	case 48: /*FillFromSpr*/  //"SprName,Separator,nField1,nField2..."
	case 51: /*AddFromSpr*/  //"SprName,Separator,nField1,nField2..."
		{
			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
			char *tmp=pos333,*tmp2;
			tmp2=strchr(tmp,',');
			if (tmp2!=NULL) *(tmp2++)=0;
			else tmp2="";
			CGPSpr *spr=GPC.m_SprArray.GetSpr(tmp);
			if (spr!=NULL) retint=spr->FillObject(m_hWnd,GPSPRFILL_COMBOBOX,tmp2,nfunc==48?0:1);
			delete[] pos333;
		}
		break;
	case 49: /*ReplaceFromSpr*/ //"SprName,IdentField,Separator,nField1,nField2..."
		{
			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
			char *tmp=pos333,*tmp2;
			tmp2=strchr(tmp,',');
			if (tmp2!=NULL) *(tmp2++)=0;
			else tmp2="";
			CGPSpr *spr=GPC.m_SprArray.GetSpr(tmp);
			if (spr!=NULL) retint=spr->ReplaceObject(m_hWnd,GPSPRFILL_COMBOBOX,tmp2);
			delete[] pos333;
		}
		break;
	case 50: /*FillFromList*/ //"ListName"
	case 52: /*AddFromList*/ //"ListName"
		retint=GPC.m_ListMaker.FillObject(pos,m_hWnd,GPSPRFILL_COMBOBOX,nfunc==50?0:1);
		break;
	case 53: /*GetContents*/
		if (oStr!=NULL)
		{
			int nItem=GetCount(),len=0;
			char *postxt=oStr;
			if (nItem>0)
			{
				int i;
				for(i=0;i<nItem;i++)
				{
					len=GetLBText(i,postxt);
					if (len!=CB_ERR) postxt[len]=0;
					if (i<nItem-1) strcat(postxt,"\x7F");
					postxt+=(int)strlen(postxt);
				}
			}
		}
		break;
	case 54: /*SelectionDelete*/
		if ((retint=GetCurSel())!=CB_ERR)
		{
			if (ItemDataArray)
			{
				DWORD itemData=GetItemData(retint);
				ItemDataArray->RemoveItem(itemData);
			}
			retint=DeleteString(retint);
		}
		break;
	case 55: /*SetMinDroppedWidth*/		m_MinListWidth=AtoiPos;			break;
	case 56: /*SetMinDroppedHeight*/	m_uMinDroppedHeight=AtoiPos;	break;
	case 57: /*GetMinVisible*/			retint=SendMessage(CB_GETMINVISIBLE,0,0);		break;
	case 58: /*SetMinVisible*/			retint=SendMessage(CB_SETMINVISIBLE,AtoiPos,0);	break;
	case 59: /*SetMaxDroppedHeight*/	m_uMaxDroppedHeight=AtoiPos;	break;
	case 60: /*GetMinDroppedWidth*/		retint=m_MinListWidth;		break;
	case 61: /*GetMinDroppedHeight*/	retint=m_uMinDroppedHeight;	break;
	case 62: /*GetMaxDroppedHeight*/	retint=m_uMaxDroppedHeight;	break;
	case 63: /*GetComboBoxInfo*/
		if (oStr)
		{
			COMBOBOXINFO cbi={0};
			cbi.cbSize=sizeof(cbi);
			SendMessage(CB_GETCOMBOBOXINFO,0,(LPARAM)&cbi);
			sprintf(oStr,"%s\x7F%d\x07%d\x07%d\x07%d\x7F%d\x07%d\x07%d\x07%d\x7F%d\x7F%d\x7F%d",
				cbi.stateButton==0?"NOTPRESSED":cbi.stateButton==0?"INVISIBLE":cbi.stateButton==0?"PRESSED":"UNKNOWN",
				cbi.rcItem.top,
				cbi.rcItem.left,
				cbi.rcItem.bottom,
				cbi.rcItem.right,
				cbi.rcButton.top,
				cbi.rcButton.left,
				cbi.rcButton.bottom,
				cbi.rcButton.right,
				(DWORD)cbi.hwndCombo,
				(DWORD)cbi.hwndItem,
				(DWORD)cbi.hwndList
				);
		}
		break;
	case 64: /*SetEditProperty*/
	case 65: /*DoEditMethod*/
	case 66: /*SetListProperty*/
	case 67: /*DoListMethod*/
		{
			COMBOBOXINFO cbi={0};
			cbi.cbSize=sizeof(cbi);
			SendMessage(CB_GETCOMBOBOXINFO,0,(LPARAM)&cbi);

			switch(nfunc)
			{
			case 64: /*SetEditProperty*/
			case 65: /*DoEditMethod*/
				if (cbi.hwndItem && *pos)
				{
					GPEdit mGPAU(UnitId);
					mGPAU.SetreferGPU(referGPU);
					mGPAU.Attach(cbi.hwndItem);
					if (nfunc==64)	mGPAU.GPSetProperty(pos);
					else			mGPAU.DoMethod(pos,oStr);
					mGPAU.Detach();
				}
				break;
			case 66: /*SetListProperty*/
			case 67: /*DoListMethod*/
				if (cbi.hwndList && *pos)
				{
					GPListBox mGPAU(UnitId);
					mGPAU.SetreferGPU(referGPU);
					mGPAU.Attach(cbi.hwndList);
					if (nfunc==66)	mGPAU.GPSetProperty(pos);
					else			mGPAU.DoMethod(pos,oStr);
					mGPAU.Detach();
				}
				break;
			}
			Invalidate();
		}
		break;
	case 69: /*SetAutoFocus*/
		retint=m_bAutoFocus;
		m_bAutoFocus=atoi(pos);
		break;
	case 70: /*AddItem iBefore,ItemData;ItemText*/
		{
			const char *postext=strchr(pos,';');
			if (!(postext++)) postext="";
			DWORD ItemData=0;
			int nItem=-1;
			int itm=CB_ERR;
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
			if (itm!=CB_ERR) SetItemData(itm,ItemData);
		}
		break;
	case 71: /*SetItemText iItem,iItemData;Text*/
		{
			const char *postext=strchr(pos,';');
			if (!(postext++)) postext="";
			int nItem=-1;
			DWORD ItemData=0;
			int itm=CB_ERR;
			if (*pos==',')
			{
				ItemData=atoi(pos+1);
				int nItems=GetCount();
				int i;
				for(i=0;i<nItems && itm==CB_ERR;i++)
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
			if (itm!=CB_ERR) SetItemData(itm,ItemData);
		}
		break;
	case 72: /*SetCurSelByItemData iItemData*/
		{
			retint=CB_ERR;
			int nItems=GetCount();
			DWORD cmpData=atoi(pos);
			int i;
			for(i=0;i<nItems && cmpData!=GetItemData(i);i++);
		
			if (i!=nItems) SetCurSel(retint=i);
		}
		break;
	case 73: /*SetItemDataEx*/
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
	case 74: /*GetItemDataEx*/
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

	case 75: /*AddItemEx [iBefore],ItemDataEx;ItemText*/
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

	case 76: /*SetItemTextEx [iItem],iItemDataEx;Text*/
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

	case 77: /*SetCurSelByItemDataEx ItemDataEx*/
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

	case 78: /*GetItemText ItemData*/
	case 40: /*GetItemTextEx ItemDataEx*/
		if (oStr)
		{
			retint=CB_ERR;
			int nItems=GetCount();
			*oStr=0;
			DWORD cmpData=(ItemDataArray && nfunc==79)?ItemDataArray->GetIdByVal(pos):AtoiPos;
			int i;
			for(i=0;i<nItems && cmpData!=GetItemData(i);i++);
			if (i!=nItems) GetLBText(i,oStr);
		}
		break;
	case 41: /*DeleteItemEx ItemDataEx*/
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

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);

	return nfunc;
}


UINT GPComboBox::GPSetProperty(const char *iStr)
{
	char *iValue=new char [(int)strlen(iStr)+5];
	strcpy(iValue,iStr);
	UINT ret=1,i;
	char *pos=strchr(iValue,'=');

	if (pos!=NULL && m_hWnd)
	{
		char *prop[]={ "TEXT", "ADDSTYLE", "DELSTYLE","STYLE",};
		int propnum;
		*(pos++)=0;
		for(propnum=0;propnum<4 && strcmp(prop[propnum],iValue)!=0;propnum++);
		if (propnum>=4) ret=2;
		else
		{
			ret=3;
			switch(propnum)
			{
			case 0: // TEXT
				{
//					if ((GetStyle()&CBS_DROPDOWNLIST)==CBS_DROPDOWNLIST)
//					{
//						int nitem=FindStringExact(0,pos);
//						if (nitem==CB_ERR ) nitem=FindStringExact(0,"");
//						if (nitem!=CB_ERR ) SetCurSel(nitem);
//					}
//					else
//					{
						int nitem=FindStringExact(0,pos);
						if (nitem==CB_ERR ) nitem=FindStringExact(0,"");
						if (nitem!=CB_ERR ) SetCurSel(nitem);
						else	SetWindowText(pos);
//					}
				}
					break;
			case 1: // ADDSTYLE
			case 2: // DELSTYLE
			case 3: // STYLE
				if (m_hWnd!=NULL)
				{
					ret=2;
					strcat(pos,"|");
					int InvFlg=0;
					// ComboBOX specif
					for(i=0;i<N_COMBOBOX_STYLES;i++)
						if (strstr(pos,aComboBoxStyleName[i])!=NULL)
						{
							InvFlg++;
							switch(propnum)
							{
							case 3: /* STYLE*/
							case 1: /* ADDSTYLE*/	ModifyStyle(0,aComboBoxStyleUINT[i]);break;
							case 2: /* DELSTYLE*/	ModifyStyle(aComboBoxStyleUINT[i],0);break;
							}
						}
					if (InvFlg!=0) Invalidate();
					break;
				}
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

void GPComboBox::ParentNotify(UINT message, LPARAM lParam)
{
	char txt[100];
	if (message==WM_CREATE || message==WM_DESTROY)
		sprintf(txt,"%d\x7F%d\x7F%X",message/0x10000,(message&0xFFFF),lParam/0x10000);
	else
		sprintf(txt,"%d\x7F%d\x7F%d\x7F%d",message/0x10000,(message&0xFFFF),lParam/0x10000,(lParam&0xFFFF));
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"ParentNotify",txt);

}

LRESULT GPComboBox::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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
		if (message==WM_KEYDOWN && referGPU!=NULL && referGPU[UnitId&0xFFFF]->UnitHotkey && m_hWnd!=NULL && IsWindowEnabled()==TRUE && IsWindowVisible()==TRUE)
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
			CRect reDrop;
			GetDroppedControlRect(&reDrop);
			GetWindowRect(&re);
			reDrop.bottom+=re.Height();

			switch((SizStyle&0xFFFF0000)/0x10000)
			{
			case GPUA_TOP:
				MoveWindow(lpLayout->rect.left,lpLayout->rect.top,lpLayout->rect.right-lpLayout->rect.left,reDrop.Height());
				lpLayout->rect.top+=re.Height();
				break;
			case GPUA_BOTTOM:
				MoveWindow(lpLayout->rect.left,lpLayout->rect.bottom-re.Height(),lpLayout->rect.right-lpLayout->rect.left,reDrop.Height());
				lpLayout->rect.bottom-=re.Height();
				break;
			case GPUA_LEFT:
				MoveWindow(lpLayout->rect.left,lpLayout->rect.top,re.Width(),reDrop.Height());
				lpLayout->rect.left+=re.Width();
				break;
			case GPUA_RIGHT:
				MoveWindow(lpLayout->rect.right-re.Width(),lpLayout->rect.top,re.Width(),reDrop.Height());
				lpLayout->rect.right-=re.Width();
				break;
			}
		}
	}

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
	if (message==WM_SETFOCUS && m_bAutoFocus && ::GetFocus()==m_hWnd && wParam==(WPARAM)m_hWnd)  
		lpr=FALSE;
	else
	if (message==WM_SETCURSOR && GPC.m_bWaitCursor) lpr=FALSE;
	else lpr=CComboBox::WindowProc(message, wParam, lParam);

	return lpr;
}

BOOL GPComboBox::PreTranslateMessage(MSG* pMsg)
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
				if (pMsg->message==WM_KEYDOWN && referGPU!=NULL && referGPU[UnitId&0xFFFF]->UnitHotkey && m_hWnd!=NULL && IsWindowEnabled()==TRUE && IsWindowVisible()==TRUE)
						if((ret=referGPU[UnitId&0xFFFF]->UnitHotkey->SendHotkeyMessage(pMsg->message, pMsg->wParam,pMsg->lParam))>0) return ret;
			}
		}
	}

	return CComboBox::PreTranslateMessage(pMsg);
}

void GPComboBox::OnClose()
{
	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClose","");
//	CComboBox::OnClose();
}

void GPComboBox::OnSizing(UINT fwSide, LPRECT pRect)
{
	BOOL EnableSz=TRUE;
	if (m_uMinDroppedHeight>0 && (UINT)pRect->bottom-pRect->top<m_uMinDroppedHeight)
		pRect->bottom=pRect->top+m_uMinDroppedHeight;

	if (m_uMaxDroppedHeight>0 && (UINT)pRect->bottom-pRect->top>m_uMaxDroppedHeight)
		pRect->bottom=pRect->top+m_uMinDroppedHeight;

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

	if (EnableSz) CComboBox::OnSizing(fwSide, pRect);

	GetParent()->SendMessage(GPN_UPDATESIZE);

}

void GPComboBox::OnDragMouseHover()
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

void GPComboBox::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
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

		DWORD bDropTarget=0xFFFFFFFF;
		BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
		// Highlight the drop target if the cursor is over an item.
		if (mDrop)
			bDropTarget = HighlightDropTarget(pDrDrStruct, CPoint(*point));
		// Modify the cursor to provide visual feedback to the user. Note: It's important to do this AFTER the call to DragMove.
		::SetCursor (bDropTarget==0xFFFFFFFF ?
			AfxGetApp()->LoadStandardCursor (IDC_NO)
			: (HCURSOR) ::GetClassLong (m_hWnd, GCL_HCURSOR));

		referGPU[UnitId&0xFFFF]->SendDropMoveEvent("",pDrDrStruct,point);
		if (mDrop)
			::SetTimer (pDrDrStruct->hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nDelayInterval, NULL);
	}
}

void GPComboBox::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && referGPU)
	{
		::ScreenToClient(m_hWnd,point);
		referGPU[UnitId&0xFFFF]->SendDropEvent("",pDrDrStruct,point);
	}
}

DWORD GPComboBox::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	return 0;
}


LRESULT GPComboBox::OnNcHitTest(CPoint point)
{
	LRESULT ret=CComboBox::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

void GPComboBox::OnKillFocus(CWnd* pNewWnd)
{
	CComboBox::OnKillFocus(pNewWnd);
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

void GPComboBox::OnSetFocus(CWnd* pOldWnd)
{
	CComboBox::OnSetFocus(pOldWnd);
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

void GPComboBox::OnSize(UINT nType, int cx, int cy)
{
	CComboBox::OnSize(nType, cx, cy);

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
	}
}


BOOL GPComboBox::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		switch(message)
		{
		case WM_COMMAND:
			{
				switch(HIWORD(wParam))
				{
				case CBN_EDITCHANGE:
					{
						int nnn=::GetWindowTextLength(m_hWnd);
						char *oStr= new char [nnn+10];
						if (nnn) nnn=::GetWindowText(m_hWnd,oStr,nnn+2);
						oStr[nnn]=0;
						referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnEditchange",oStr);
						delete[] oStr;
					}
					break;
				case CBN_CLOSEUP:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnCloseup","");
					break;
				case CBN_DBLCLK:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDblclk","");
					break;
				case CBN_DROPDOWN:
					if (m_hWnd!=NULL)
					{
						HWND cmpHWND=::GetFocus();
						if (cmpHWND==NULL || ::GetParent(cmpHWND)!= m_hWnd)
							::SetFocus(m_hWnd);
						if (m_MinListWidth)
						{
							int wi=SendMessage(CB_GETDROPPEDWIDTH,0,0);
							if (wi!=CB_ERR && (UINT)wi<m_MinListWidth)
								SendMessage(CB_SETDROPPEDWIDTH ,m_MinListWidth,0);
						}

						if (m_uMinDroppedHeight)
						{
							CRect re;
							GetDroppedControlRect(&re);
							if ((UINT)re.Height()<m_uMinDroppedHeight)
							{
								HWND tmph=::WindowFromPoint(re.TopLeft());
								re.bottom=re.top+m_uMinDroppedHeight;
								GetParent()->ScreenToClient(&re);
								::MoveWindow(tmph,re.left,re.top,re.Width(),re.Height(),TRUE);
							}
						}

						if (m_uMaxDroppedHeight)
						{
							CRect re;
							GetDroppedControlRect(&re);
							if ((UINT)re.Height()>m_uMaxDroppedHeight)
							{
								HWND tmph=::WindowFromPoint(re.TopLeft());
								re.bottom=re.top+m_uMaxDroppedHeight;
								GetParent()->ScreenToClient(&re);
								::MoveWindow(tmph,re.left,re.top,re.Width(),re.Height(),TRUE);
							}
						}

						referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDropdown","");
					}
					break;
				case CBN_EDITUPDATE:
					{
						int nnn=::GetWindowTextLength(m_hWnd);
						char *oStr= new char [nnn+10];
						if (nnn) nnn=::GetWindowText(m_hWnd,oStr,nnn+2);
						oStr[nnn]=0;
						referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnEditupdate",oStr);
						delete[] oStr;
					}
					break;
				case CBN_ERRSPACE:	break;
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnErrspace","");
				case CBN_KILLFOCUS:
					{
						if (referGPU[UnitId&0xFFFF]->m_ptrUnitValChange) referGPU[UnitId&0xFFFF]->m_ptrUnitValChange->SendOnValChangeEvent(0);
						referGPU[UnitId&0xFFFF]->m_ptrUnitValChange=NULL;

						int nnn=::GetWindowTextLength(m_hWnd);
						char *oStr= new char [nnn+10];
						if (nnn) nnn=::GetWindowText(m_hWnd,oStr,nnn+2);
						oStr[nnn]=0;
						referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNotifyKillfocus",oStr);
						delete[] oStr;


						GPUNITINFO ui;
						GPUNITINFO uiold;
						if (referGPU[UnitId&0xFFFF])
							referGPU[UnitId&0xFFFF]->GetUnitInfo(ui);
						HWND pNewWnd=::GetFocus();

						if (pNewWnd)
						{
							GPC.m_Document->FindObject(pNewWnd,uiold);
							ui.hWnd2=uiold.hWnd;
							ui.IdDlg2=uiold.IdDlg;
							ui.IdObj2=uiold.IdObj;
						}
						::SendMessage(::GetParent(m_hWnd),GPM_CLIENTKILLFOCUS,(WPARAM)(pNewWnd?pNewWnd:NULL),(LPARAM)&ui);
					}
					break;
				case CBN_SELCHANGE:
					if (referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnSelchange"))
					{
						CString tmps;
						char str[500];
						*str=0;
						int id=GetCurSel();
						if (id!=CB_ERR)
							GetLBText( id, tmps);
						sprintf(str,"%d\x7F%s",id,(LPCSTR)tmps);
						referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSelchange",str);
						if (referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)	DoMethod("UpdateGroup",NULL);
					}
					break;
				case CBN_SELENDCANCEL:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSelendcancel","");
					if (referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)	DoMethod("UpdateGroup",NULL);
					break;
				case CBN_SELENDOK:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSelendok","");
					if (referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)	DoMethod("UpdateGroup",NULL);
					break;
				case CBN_SETFOCUS:
					{
						if (referGPU[UnitId&0xFFFF]->m_ptrUnitValChange && referGPU[UnitId&0xFFFF]->m_ptrUnitValChange!=referGPU[UnitId&0xFFFF]) referGPU[UnitId&0xFFFF]->m_ptrUnitValChange->SendOnValChangeEvent(0);
						if ((referGPU[UnitId&0xFFFF]->m_dwValChangeFlag&0x1) && m_hWnd && ::IsWindow(m_hWnd)) 
						{
							referGPU[UnitId&0xFFFF]->m_ptrUnitValChange=referGPU[UnitId&0xFFFF];
							referGPU[UnitId&0xFFFF]->SetValChangeCheckPoint();
						}
						else 
							referGPU[UnitId&0xFFFF]->m_ptrUnitValChange=NULL;

						int nnn=::GetWindowTextLength(m_hWnd);
						char *oStr= new char [nnn+10];
						if (nnn) nnn=::GetWindowText(m_hWnd,oStr,nnn+2);
						oStr[nnn]=0;
						referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNotifySetfocus",oStr);
						delete[] oStr;

						GPUNITINFO ui;
						GPUNITINFO uiold;
						if (referGPU[UnitId&0xFFFF])
							referGPU[UnitId&0xFFFF]->GetUnitInfo(ui);
						HWND pNewWnd=::GetFocus();
						if (pNewWnd)
						{
							GPC.m_Document->FindObject(pNewWnd,uiold);
							ui.hWnd2=uiold.hWnd;
							ui.IdDlg2=uiold.IdDlg;
							ui.IdObj2=uiold.IdObj;
						}
						::SendMessage(::GetParent(m_hWnd),GPM_CLIENTSETFOCUS,(WPARAM)(pNewWnd?pNewWnd:NULL),(LPARAM)&ui);
					}
					break;
				default:
//					TRACE("OnChildNotify WM_COMMAND %d\n",HIWORD(wParam));
					break;
				}
			}
			break;
		case WM_NOTIFY:
			{
				NMHDR* pNMHDR=(NMHDR *) lParam;
				switch(pNMHDR->code)
				{
					break;
				case CBEN_INSERTITEM:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnInsertItem","");
					break;
				case CBEN_DELETEITEM:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDeleteItem","");
					break;
				case CBEN_BEGINEDIT:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnBeginEdit","");
					break;
				case CBEN_DRAGBEGIN:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDragBegin","");
					break;
				case CBEN_ENDEDIT:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnEndEdit","");
					break;
				default:
//					TRACE("OnChildNotify WM_NOTIFY %d\n",HIWORD(wParam));
					break;
				}
				break;
			}
		break;
		default:
//		TRACE("OnChildNotify UNKNOWN %4.4X %d\n",message,HIWORD(wParam));
		break;
		}
	}
	return CComboBox::OnChildNotify(message, wParam, lParam, pLResult);
}


HBRUSH GPComboBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CComboBox::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}

int GPComboBox::AddChar(char iChar, DWORD iFlags)
{
	int ret=0;
	if (iChar)
	{
		int nItem=GetCount();
		CString text="";
		if (nItem) 	GetLBText(--nItem,text);
		else 
			nItem=AddString("");

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


int GPComboBox::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message) 
{
	int ret=CComboBox::OnMouseActivate(pDesktopWnd, nHitTest, message);
	if (m_bAutoFocus)
	{
		COMBOBOXINFO cbi={0};
		cbi.cbSize=sizeof(cbi);
		::SendMessage(m_hWnd,CB_GETCOMBOBOXINFO,0,(LPARAM)&cbi);
		HWND hwndFocus=::GetFocus();
		if (hwndFocus!=m_hWnd && hwndFocus!=cbi.hwndItem  && hwndFocus!=cbi.hwndList)
		{
			if (cbi.stateButton!=STATE_SYSTEM_PRESSED)
			::PostMessage(m_hWnd,GPM_SETFOCUSTOWND,(WPARAM)cbi.hwndItem,0);
		}
	}
	return ret;
}
