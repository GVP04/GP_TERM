// GPTree.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GP_TermDoc.h"
#include "GPTree.h"
#include "DlgViewSystemMethods.h"
#include "GPContextMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPTree

const UINT GPTree::nTVIS=7;
const char *GPTree::TVISName[7]={"_BOLD|","_CUT|","_DROPHILITED|","_EXPANDED|","_EXPANDEDONCE|","_EXPANDPARTIAL|","_SELECTED|",};
const UINT GPTree::TVISUINT[7]={TVIS_BOLD,TVIS_CUT,TVIS_DROPHILITED,TVIS_EXPANDED,TVIS_EXPANDEDONCE,TVIS_EXPANDPARTIAL,TVIS_SELECTED,};
const UINT GPTree::maskTVIS=TVIS_BOLD|TVIS_CUT|TVIS_DROPHILITED|TVIS_EXPANDED|TVIS_EXPANDEDONCE|TVIS_EXPANDPARTIAL|TVIS_SELECTED;
const UINT GPTree::nTVISEx=2;
const char *GPTree::TVISNameEx[2]={"_EX_FLAT|","_EX_DISABLED|",};
const UINT GPTree::TVISUINTEx[2]={TVIS_EX_FLAT,TVIS_EX_DISABLED};
const UINT GPTree::maskTVISEx=TVIS_EX_FLAT|TVIS_EX_DISABLED;

const UINT GPTree::nTVGN=12;
const UINT GPTree::TVGNUINT[12]={TVGN_CARET,TVGN_CHILD,TVGN_DROPHILITE ,TVGN_FIRSTVISIBLE,TVGN_NEXT,TVGN_NEXTVISIBLE,TVGN_PARENT,TVGN_PREVIOUS,TVGN_PREVIOUSVISIBLE,TVGN_ROOT,TVGN_LASTVISIBLE,TVSI_NOSINGLEEXPAND,};
const char *GPTree::TVGNName[12]={"_CARET|","_CHILD|","_DROPHILITE|","_FIRSTVISIBLE|","_NEXT|","_NEXTVISIBLE|","_PARENT|","_PREVIOUS|","_PREVIOUSVISIBLE|","_ROOT|","_LASTVISIBLE|","_NOSINGLEEXPAND|",};

const UINT GPTree::nTVIF=9;
const UINT GPTree::TVIFUINT[9]={TVIF_HANDLE,TVIF_IMAGE,TVIF_PARAM ,TVIF_SELECTEDIMAGE,TVIF_STATE,TVIF_TEXT,TVIF_CHILDREN,TVIF_INTEGRAL,TVIF_PARENT,};
const char *GPTree::TVIFName[9]={"_HANDLE|","_IMAGE|","_PARAM|","_SELECTEDIMAGE|","_STATE|","_TEXT|","_CHILDREN|","_INTEGRAL|","_PARENT|"};
const UINT GPTree::maskTVIF=TVIF_HANDLE|TVIF_IMAGE|TVIF_PARAM |TVIF_SELECTEDIMAGE|TVIF_STATE|TVIF_TEXT|TVIF_CHILDREN|TVIF_INTEGRAL;

const UINT GPTree::nTVE=5;
const char *GPTree::TVEName[5]={"_COLLAPSE","_COLLAPSERESET","_EXPAND","_TOGGLE","_EXPANDPARTIAL",};
const UINT GPTree::TVEUINT[5]={TVE_COLLAPSE,TVE_COLLAPSERESET,TVE_EXPAND,TVE_TOGGLE,TVE_EXPANDPARTIAL,};

const UINT GPTree::uNMethods=100;
const char *GPTree::cArrMethods[]={
/*00*/	"GetCount","GetIndent","SetIndent","GetImageList","SetImageList",
/*05*/	"GetNextItem","ItemHasChildren","GetChildItem","GetNextSiblingItem","GetPrevSiblingItem",
/*10*/	"GetParentItem","GetFirstVisibleItem","GetNextVisibleItem","GetPrevVisibleItem","GetSelectedItem",
/*15*/	"GetDropHilightItem","GetRootItem","GetItem","SetItem","GetItemState",
/*20*/	"SetItemState","GetItemImage","SetItemImage","GetItemText","SetItemText",
/*25*/	"GetItemData","SetItemData","GetItemRect","GetEditControl","GetVisibleCount",
/*30*/	"GetToolTips","SetToolTips","GetBkColor","SetBkColor","GetItemHeight",
/*35*/	"SetItemHeight","GetTextColor","SetTextColor","SetInsertMark","GetCheck",
/*40*/	"SetCheck","GetInsertMarkColor","SetInsertMarkColor","InsertItem","DeleteItem",
/*45*/	"DeleteAllItems","Expand","Select","SelectItem","SelectDropTarget",
/*50*/	"SelectSetFirstVisible","EditLabel","HitTest","CreateDragImage","SortChildren",
/*55*/	"EnsureVisible","SortChildrenCB","UpdateGroup","GetTreeStyle","GetChecked",
/*60*/	"GetParents", "DeleteAllChild","SetDragROOT","CopyChildren","EndEditLabel",
/*65*/	"GetISearchString","SetUnicodeFormat","GetUnicodeFormat","SetScrollTime","GetScrollTime",
/*70*/	"SetLineColor","GetLineColor","MapAccIdToHTREEITEM","MapHTREEITEMToAccId","MoveTree",
/*75*/	"ClearDropHilight","ClearSelection","AutoClearDropHilight","CopyTree","GetChildList",
/*80*/	"NormalizeTree","RestoreId","ChangeId","SaveId","GetIdArray",
/*85*/	"GetIdArraySave","SetIdArray","SetIdArraySave","GetContents","GetTreeStructure",
/*90*/	"GetChildListEx","GetContentsEx","IsChildOf","DependsSet","DependsDelete",
/*95*/	"DependsDeleteStyle","DependsAddStyle","SpecialFill","GetTreeExtendedStyle","SetTreeExtendedStyle",
/*100*/	"","","","","",
/*105*/	"","","","","",
	};

//#define TreeView_GetNextSelected(hwnd, hitem)   TreeView_GetNextItem(hwnd, hitem,  TVGN_NEXTSELECTED)


const char *GPTree::cArrMethodsParams[]={
/*00*/	"","","nIndent","type","ImageListName,type",
/*05*/	"IdItem,_CARET|_CHILD|_DROPHILITE|_FIRSTVISIBLE|_NEXT|_NEXTVISIBLE|_PARENT|_PREVIOUS|_PREVIOUSVISIBLE|_ROOT|","IdItem","IdItem","IdItem","IdItem",
/*10*/	"IdItem","","IdItem","IdItem","",
/*15*/	"","","IdItem","IdItem,lParam,iImage,iSelectedImage,iIntegral,state,mask;Text","IdItem",
/*20*/	"IdItem,State[,StateMask]","IdItem","IdItem,nImage,nSelectedImage","IdItem","IdItem,Text",
/*25*/	"IdItem","IdItem,iItemData","IdItem,bTextOnly","Not Present","",
/*30*/	"Not Present","Not Present","","r,g,b","",
/*35*/	"iItemHeight","","r,g,b","IdItem,fAfter","IdItem",
/*40*/	"IdItem,iCheck","","r,g,b","IdItem,IdParent,IdInsertAfter,lParam,nImage,nSelectedImage,iIntegral,cChildren,State;Text","IdItem",
/*45*/	"","IdItem,_COLLAPSE_COLLAPSERESET_EXPAND_TOGGLE,bAll","IdItem,_CARET_DROPHILITE_FIRSTVISIBLE","IdItem","IdItem",
/*50*/	"IdItem","IdItem","ptx,pty","Not Present","IdItem[,bRecurse]",
/*55*/	"IdItem","IdItem","","","",
/*60*/	"[IdItem]", "[IdItem]","bValue","IdItemDst,IdItemSrc,DeltaId","bSave",
/*65*/	"","bFormat","","ScrollTimeMS","",
/*70*/	"r,g,b","","AccId","ITEMId","IdItemDst,IdItemSrc",
/*75*/	"","","bOnOff","From,To,IdDelta","[IdItem[,nLevel[,bFull]]]",
/*80*/	"IdStart,iDelta[,bCreateUndo]","[Id]","Id,newId","[Id]","",
/*85*/	"","Id1,Id2,....","Id1,Id2,....","","[IdItem]",
/*90*/	"IdItem,nLevels,Attributes","Attributes","IdChild,IdParent","type,{Value[|Value2...],IdDlg,IdObj,OnStyleAdd,OnStyleDel,OffStyleAdd,OffStyleDel[^]}","type,Value[|Value2...],IdDlg,IdObj",
/*95*/	"type,{Value[|Value2...],IdDlg,IdObj,OnStyleAdd,OnStyleDel,OffStyleAdd,OffStyleDel[^]}","type,{Value[|Value2...],IdDlg,IdObj,OnStyleAdd,OnStyleDel,OffStyleAdd,OffStyleDel[^]}","[type]","","ExStyle",
/*100*/	"","","","","",
/*105*/	"","","","","",
	};


GPTree::GPTree(UINT iUnitId)
{
	m_HelperMode=0;
	GPPA_Image = NULL;
	GPPA_SelImage = NULL;
	GPPA_lValue = NULL;
	GPPA_IdItem = NULL;
	GPPA_IdParent = NULL;

	m_ClearDropHilight=TRUE;
	HTREEITEM InitV=NULL;
	ItemIdArray.SetInitValue(InitV);
	m_bDragROOT=TRUE;
	m_hDragItem = NULL;
	m_bDragging = FALSE;

	referGPU=NULL;
	UnitId=iUnitId;
	oldState=0;
}

GPTree::~GPTree()
{
	if (GPPA_Image)		delete[] GPPA_Image;
	GPPA_Image=NULL;

	if (GPPA_IdParent)	delete[] GPPA_IdParent;
	GPPA_IdParent=NULL;

	if (GPPA_SelImage)	delete[] GPPA_SelImage;
	GPPA_SelImage=NULL;

	if (GPPA_lValue)	delete[] GPPA_lValue;
	GPPA_lValue=NULL;

	if (GPPA_IdItem)	delete[] GPPA_IdItem;
	GPPA_IdItem=NULL;
}


BEGIN_MESSAGE_MAP(GPTree, CTreeCtrl)
	//{{AFX_MSG_MAP(GPTree)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(NM_KILLFOCUS, OnKillfocus)
	ON_NOTIFY_REFLECT(NM_OUTOFMEMORY, OnOutofmemory)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(NM_RDBLCLK, OnRdblclk)
	ON_NOTIFY_REFLECT(NM_RETURN, OnReturn)
	ON_NOTIFY_REFLECT(NM_SETFOCUS, OnSetfocus)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
	ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, OnBeginlabeledit)
	ON_NOTIFY_REFLECT(TVN_BEGINRDRAG, OnBeginrdrag)
	ON_NOTIFY_REFLECT(TVN_DELETEITEM, OnDeleteitem)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
	ON_NOTIFY_REFLECT(TVN_GETDISPINFO, OnGetdispinfo)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemexpanded)
	ON_NOTIFY_REFLECT(TVN_KEYDOWN, OnKeydown)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_NOTIFY_REFLECT(TVN_SELCHANGING, OnSelchanging)
	ON_NOTIFY_REFLECT(TVN_SETDISPINFO, OnSetdispinfo)
	ON_NOTIFY_REFLECT(TVN_SINGLEEXPAND, OnSingleExpand)
	ON_NOTIFY_REFLECT(TVN_GETINFOTIP, OnGetInfotip)
	ON_WM_PARENTNOTIFY_REFLECT()
	ON_WM_CLOSE()
	ON_WM_SIZING()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_NCHITTEST()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPTree message handlers

UINT GPTree::DoMethod(const char *iStr, char *oStr)
{
	char met[150];

	strncpy(met,iStr,145);
	met[145]=0;
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc=0;

	HTREEITEM tmpHTree=NULL;

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
	try
	{
		switch(nfunc)
		{
		case  0: /*GetCount*/	retint=GetCount( );	break;
		case  1: /*GetIndent*/	retint=GetIndent( );	break;
		case  2: /*SetIndent*/	SetIndent(AtoiPos);	break;
		case  5: /*GetNextItem*/ // fromat IdCurItem, чтоискать
			{
				UINT nCode =TVGN_NEXT;
				const char *postmp=strchr(pos,',');
				if (postmp++!=NULL)
				{
					int i;
					for(i=0;i<GPTree::nTVGN;i++)
						if (strcmp(postmp,GPTree::TVGNName[i])==0) {nCode=GPTree::TVGNUINT[i];break;}
				}

				if ((tmpHTree=ItemIdArray[AtoiPos])!=NULL)
					retint=ItemIdArray.GetIdByVal(GetNextItem(tmpHTree,nCode));
			}
			break;
		case  6: /*ItemHasChildren*/
			if ((tmpHTree=ItemIdArray[AtoiPos])!=NULL) 	retint=ItemHasChildren(tmpHTree);
			break;
		case  7: /*GetChildItem*/
			if ((tmpHTree=ItemIdArray[AtoiPos])!=NULL) 	retint=ItemIdArray.GetIdByVal(GetChildItem(tmpHTree));
			break;
		case  8: /*GetNextSiblingItem*/
			if ((tmpHTree=ItemIdArray[AtoiPos])!=NULL) 	retint=ItemIdArray.GetIdByVal(GetNextSiblingItem(tmpHTree));
			break;
		case  9: /*GetPrevSiblingItem*/
			if ((tmpHTree=ItemIdArray[AtoiPos])!=NULL) 	retint=ItemIdArray.GetIdByVal(GetPrevSiblingItem(tmpHTree));
			break;
		case 10: /*GetParentItem*/
			if ((tmpHTree=ItemIdArray[AtoiPos])!=NULL) 	retint=ItemIdArray.GetIdByVal(GetParentItem(tmpHTree));
			break;
		case 11: /*GetFirstVisibleItem*/
			retint=ItemIdArray.GetIdByVal(GetFirstVisibleItem());
			break;
		case 12: /*GetNextVisibleItem*/
			if ((tmpHTree=ItemIdArray[AtoiPos])!=NULL) 	retint=ItemIdArray.GetIdByVal(GetNextVisibleItem(tmpHTree));
			break;
		case 13: /*GetPrevVisibleItem*/
			if ((tmpHTree=ItemIdArray[AtoiPos])!=NULL) 	retint=ItemIdArray.GetIdByVal(GetPrevVisibleItem(tmpHTree));
			break;
		case 14: /*GetSelectedItem*/
			if ((tmpHTree=GetSelectedItem())!=NULL) ItemString(tmpHTree,oStr);
			break;
		case 15: /*GetDropHilightItem*/	retint=ItemIdArray.GetIdByVal(GetDropHilightItem());	break;
		case 16: /*GetRootItem*/		retint=ItemIdArray.GetIdByVal(GetRootItem());			break;
		case 17: /*GetItem*/			ItemString(ItemIdArray[AtoiPos],oStr);					break;
		case 18: /*SetItem*/
			{
				char *postmpcc=new char [(int)strlen(pos)+10];
				strcpy(postmpcc,pos);

				TVITEMEX curItem={0};

				int IdItem=0;
				m_LastScanf=sscanf(postmpcc,"%d,%ld,%d,%d,%d",&IdItem,&curItem.lParam,&curItem.iImage,&curItem.iSelectedImage,&curItem.iIntegral);

				curItem.pszText=strchr(postmpcc,';');
				if (curItem.pszText++==NULL) curItem.pszText="";

				curItem.state=curItem.mask=0;
				curItem.stateMask=GPTree::maskTVIS;

				curItem.state=StringToState(postmpcc);

				int i;
				for(i=0;i<GPTree::nTVIF;i++)
					if (strstr(postmpcc,GPTree::TVIFName[i])!=NULL) curItem.mask|=GPTree::TVIFUINT[i];

				curItem.hItem= ItemIdArray[IdItem];
				SendMessage(TVM_SETITEM,0,(LPARAM)&curItem);
				delete[] postmpcc;
			}
			break;
		case 19: /*GetItemState*/
			if (oStr!=NULL &&(tmpHTree=ItemIdArray[AtoiPos])!=NULL)
			{
				UINT state=GetItemState(tmpHTree,GPTree::maskTVIS);
				int i;
				for(i=0;i<GPTree::nTVIS;i++)
					if ((state&GPTree::TVISUINT[i])==GPTree::TVISUINT[i]) strcat(oStr,GPTree::TVISName[i]);
			}
			break;
		case 20: /*SetItemState*/
			if ((tmpHTree=ItemIdArray[AtoiPos])!=NULL)
			{
				UINT nState=0;
				UINT nStateMask=0;
				CString stateM=ExtractField(pos,3,",");
				if (stateM=="") nStateMask=GPTree::maskTVIS;
				else nStateMask=StringToState(stateM);

				stateM=ExtractField(pos,2,",");
				nState=StringToState(stateM);
				retint=SetItemState(tmpHTree,nState,nStateMask);
			}
			break;
		case 23: /*GetItemText*/
			if (oStr!=NULL &&(tmpHTree=ItemIdArray[AtoiPos])!=NULL) strcpy(oStr,GetItemText(tmpHTree));
			break;
		case 24: /*SetItemText*/
			if ((tmpHTree=ItemIdArray[AtoiPos]))
			{
				const char *posstr=strchr(pos,',');
				if (posstr++!=NULL)	retint=SetItemText(tmpHTree,posstr);
			}
			break;
		case 25: /*GetItemData*/
			if ((tmpHTree=ItemIdArray[AtoiPos])) retint=GetItemData(tmpHTree);
			else 
			{
				tmpHTree=GetSelectedItem();
				if (tmpHTree) retint=GetItemData(tmpHTree);
			}
			break;
		case 26: /*SetItemData*/
			{
				int IdItem=-1,ItemData=0;
				m_LastScanf=sscanf(pos,"%d,%d",&IdItem,&ItemData);
				if ((tmpHTree=ItemIdArray[IdItem])!=NULL) retint=SetItemData(tmpHTree,ItemData);
			}
			break;
		case 27: /*GetItemRect*/
			if (oStr!=NULL)
			{
				int IdItem=-1,bTextOnly=0;
				CRect re;
				m_LastScanf=sscanf(pos,"%d,%d",&IdItem,&bTextOnly);
				if ((tmpHTree=ItemIdArray[IdItem])!=NULL && GetItemRect(tmpHTree,&re,bTextOnly)!=FALSE)
					sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
			}
			break;
		case 29: /*GetVisibleCount*/ retint=GetVisibleCount( );	break;
		case 32: /*GetBkColor*/
		case 36: /*GetTextColor*/
		case 41: /*GetInsertMarkColor*/
		case 71: /*GetLineColor*/
			if (oStr!=NULL)
			{
				UINT cref=0;
				switch(nfunc)
				{
				case 32: /*GetBkColor*/				cref=GetBkColor();			break;
				case 36: /*GetTextColor*/			cref=GetTextColor();		break;
				case 41: /*GetInsertMarkColor*/		cref=GetInsertMarkColor();	break;
				case 71: /*GetLineColor*/
					cref=SendMessage(TVM_GETLINECOLOR,0,0);
					break;
				}
				sprintf(oStr,"%d\x07%d\x07%d",GetRValue(cref),GetGValue(cref),GetBValue(cref));
			}
			break;
		case 33: /*SetBkColor*/
		case 37: /*SetTextColor*/
		case 42: /*SetInsertMarkColor*/
		case 70: /*SetLineColor*/
			{
				COLORREF clr=CLR_DEFAULT;
				COLORREF clrret=CLR_DEFAULT;
				if (*pos)
				{
					UINT r=0,g=0,b=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d",&r,&g,&b);
					clr=RGB(r,g,b);
				}

				switch(nfunc)
				{
				case 33: /*SetBkColor*/			clrret=SetBkColor(clr);			break;
				case 37: /*SetTextColor*/		clrret=SetTextColor(clr);		break;
				case 42: /*SetInsertMarkColor*/	clrret=SetInsertMarkColor(clr);	break;
				case 70: /*SetLineColor*/
					clrret=SendMessage(TVM_SETLINECOLOR,0,(LPARAM)clr);
					break;
				}
				if (oStr!=NULL)	sprintf(oStr,"%d\x07%d\x07%d",GetRValue(clrret),GetGValue(clrret),GetBValue(clrret));
			}
			break;
		case 34: /*GetItemHeight*/	retint=GetItemHeight();	break;
		case 35: /*SetItemHeight*/	retint=SetItemHeight(AtoiPos);	break;
		case 38: /*SetInsertMark*/
			{
				int IdItem=-1,fAfter=0;
				m_LastScanf=sscanf(pos,"%d,%d",&IdItem,&fAfter);
				if ((tmpHTree=ItemIdArray[IdItem])!=NULL)
					retint=SetInsertMark(tmpHTree, fAfter);
			}
			break;
		case 39: /*GetCheck*/
			if ((tmpHTree=ItemIdArray[AtoiPos]) || (tmpHTree=GetSelectedItem())) 	retint=GetCheck(tmpHTree);
			break;
		case 40: /*SetCheck*/
			{
				int IdItem=-1,fCheck=0;
				m_LastScanf=sscanf(pos,"%d,%d",&IdItem,&fCheck);
				if ((tmpHTree=ItemIdArray[IdItem])!=NULL)	retint=SetCheck(tmpHTree, fCheck);
			}
			break;
		case 43: /*InsertItem*/
			// format													(TVISName)
			// IdItem,IdParent,IdInsertAfter,lParam,nImage,nSelectedImage,iIntegral,cChildren,nState;lpszItem
			{
				char *postmpcc=new char [(int)strlen(pos)+10];
				strcpy(postmpcc,pos);

				TVINSERTSTRUCT newItem={0};

				newItem.itemex.hItem=NULL;
				newItem.itemex.mask=GPTree::maskTVIF;
				newItem.itemex.mask^=TVIF_STATE|TVIF_HANDLE;
				newItem.itemex.stateMask=GPTree::maskTVIS;
				newItem.itemex.cchTextMax=5000;

				if ((newItem.itemex.state=StringToState(postmpcc))!=0 || (newItem.itemex.state=StringToState(ExtractField(postmpcc,9,",")))!=0)
					newItem.itemex.mask|=TVIF_STATE;

				oldState=newItem.itemex.state;

				int IdItem=AtoiPos;
				CString fld;
				fld=ExtractField(postmpcc,2,",");

				if (fld.Find("ROOT")>=0) newItem.hParent=TVI_ROOT;
				else					newItem.hParent=ItemIdArray[atoi(fld)];

				fld=ExtractField(postmpcc,3,",");
				if (fld.Find("FIRST")>=0) newItem.hInsertAfter=TVI_FIRST;
				else
				if (fld.Find("LAST")>=0) newItem.hInsertAfter=TVI_LAST;
				else
				if (fld.Find("ROOT")>=0) newItem.hInsertAfter=TVI_ROOT;
				else
				if (fld.Find("SORT")>=0) newItem.hInsertAfter=TVI_SORT;
				else					newItem.hInsertAfter=ItemIdArray[atoi(fld)];

				fld=ExtractField(postmpcc,4,",");
				if (fld=="")	newItem.itemex.mask^=TVIF_PARAM;
					else		newItem.itemex.lParam=atoi(fld);

				fld=ExtractField(postmpcc,5,",");
				if (fld=="")	newItem.itemex.mask^=TVIF_IMAGE;
					else		newItem.itemex.iImage=atoi(fld);

				fld=ExtractField(postmpcc,6,",");
				if (fld=="")	newItem.itemex.mask^=TVIF_SELECTEDIMAGE;
					else		newItem.itemex.iSelectedImage=atoi(fld);

				fld=ExtractField(postmpcc,7,",");
				if (fld=="")	newItem.itemex.mask^=TVIF_INTEGRAL;
					else		newItem.itemex.iIntegral=atoi(fld);

				fld=ExtractField(postmpcc,8,",");
				if (fld=="")	newItem.itemex.mask^=TVIF_CHILDREN;
					else		newItem.itemex.cChildren=atoi(fld);




				newItem.itemex.pszText=strchr(postmpcc,';');
				if (newItem.itemex.pszText++==NULL) newItem.itemex.pszText="";

				if (IdItem!=-1)
				{
					HTREEITEM newHI=(HTREEITEM)SendMessage(TVM_INSERTITEM,0,(LPARAM)&newItem);
					if (newHI)
					{
						retint=(int)newHI;
						ItemIdArray[IdItem]=newHI;
					}
				}
				delete[] postmpcc;
			}
			break;
		case 44: /*DeleteItem*/
			if (*pos && (tmpHTree=ItemIdArray[AtoiPos]))
			{
				retint=DeleteItem(tmpHTree);
			}
			break;
		case 45: /*DeleteAllItems*/
			{
				ItemIdArray.ResetArray();
				DWORD stl=GetStyle();
				if ((stl&WS_VISIBLE)) ModifyStyle(WS_VISIBLE,0);
				retint=DeleteAllItems();
				if ((stl&WS_VISIBLE))
				{
					ModifyStyle(0,WS_VISIBLE);
					Invalidate();
				}
			}
			break;
		case 46: /*Expand*/
			{
				UINT nItems=ItemIdArray.GetCount();
				if (nItems && (strstr(pos,"root") || strstr(pos,"ROOT") || (tmpHTree=ItemIdArray[AtoiPos]) || (tmpHTree=GetSelectedItem())))
				{
					if (tmpHTree==NULL) tmpHTree=TVI_ROOT;
					UINT i;
					char posstr[500];
					strcpy(posstr,ExtractField(pos,2,","));

					for(i=0;i<GPTree::nTVE && strcmp(posstr,GPTree::TVEName[i])!=0;i++);

					DWORD ExpFlag=(*posstr==0 || i==4) ? TVE_EXPAND:GPTree::TVEUINT[i];

					if (atoi(ExtractField(pos,3,",")))
					{
						HTREEITEM *Arr=new HTREEITEM [nItems+5];
						if (Arr)
						{
							UINT nArr=GetChildList(tmpHTree,Arr,1000,NULL);
							for(i=0;i<nArr;i++)
								if (Arr[i] && ItemHasChildren(Arr[i]))
									Expand(Arr[i],ExpFlag);
							delete[] Arr;
						}
					}

					retint=Expand(tmpHTree,ExpFlag);
					Invalidate();
				}
			}
			break;
		case 47: /*Select*/
			if ((tmpHTree=ItemIdArray[AtoiPos]) || (tmpHTree=GetSelectedItem()))
			{
				int i=-1;
				const char *posstr=strchr(pos,',');
				char *nCodeName[3]={"_CARET","_DROPHILITE","_FIRSTVISIBLE",};
				UINT nCodeUINT[3]={TVGN_CARET,TVGN_DROPHILITE,TVGN_FIRSTVISIBLE,};

				if (posstr!=NULL)
					for(posstr++,i=0;i<3 && strcmp(posstr,nCodeName[i])!=0;i++);

					retint=Select(tmpHTree,(posstr==NULL || i==3) ? TVE_EXPAND:i<0?0:nCodeUINT[i]);
			}
			break;
		case 48: /*SelectItem*/
			if ((tmpHTree=ItemIdArray[AtoiPos])) 	retint=SelectItem(tmpHTree);
			break;
		case 49: /*SelectDropTarget*/
			if ((tmpHTree=ItemIdArray[AtoiPos]) || (tmpHTree=GetSelectedItem())) 	retint=SelectDropTarget(tmpHTree);
			break;
		case 50: /*SelectSetFirstVisible*/
			if ((tmpHTree=ItemIdArray[AtoiPos]) || (tmpHTree=GetSelectedItem())) 	retint=SelectSetFirstVisible(tmpHTree);
			break;
		case 51: /*EditLabel*/
			if ((tmpHTree=ItemIdArray[AtoiPos]) || (tmpHTree=GetSelectedItem())) 	retint=(int)EditLabel(tmpHTree);
			break;
		case 52: /*HitTest*/
			if (oStr!=NULL)
			{
				TVHITTESTINFO HTestInfo={0};
				HTestInfo.hItem=tmpHTree;
				m_LastScanf=sscanf(pos,"%d,%d",&HTestInfo.pt.x,&HTestInfo.pt.y);

				int i;
				char *nCodeName[12]={"_ABOVE|","_BELOW|","_NOWHERE|","_ONITEM|","_ONITEMBUTTON|","_ONITEMICON|","_ONITEMINDENT|","_ONITEMLABEL|","_ONITEMRIGHT|","_ONITEMSTATEICON|","_TOLEFT|","_TORIGHT|",};
				UINT nCodeUINT[12]={TVHT_ABOVE,TVHT_BELOW,TVHT_NOWHERE,TVHT_ONITEM,TVHT_ONITEMBUTTON,TVHT_ONITEMICON,TVHT_ONITEMINDENT,TVHT_ONITEMLABEL,TVHT_ONITEMRIGHT,TVHT_ONITEMSTATEICON,TVHT_TOLEFT,TVHT_TORIGHT,};

				char str[250];*str=0;

				tmpHTree=HitTest(&HTestInfo);

				for(i=0;i<12;i++)
					if ((HTestInfo.flags&=nCodeUINT[i])==nCodeUINT[i]) strcat(str,nCodeName[i]);

				i=-1;
				if (tmpHTree!=NULL) i=ItemIdArray.GetIdByVal(tmpHTree);
				sprintf(oStr,"%d%c%s",i,0x7F,str);
			}
			break;
		case 54: /*SortChildren*/
			if ((tmpHTree=ItemIdArray[AtoiPos]) || (tmpHTree=GetSelectedItem())) 
			{
				DWORD fRecurse=0;
				const char *pos2=strchr(pos,',');
				if (pos2) fRecurse=atoi(++pos2);
				retint=::SendMessage(m_hWnd,TVM_SORTCHILDREN,fRecurse,(LPARAM)tmpHTree);
			}
			break;
		case 55: /*EnsureVisible*/
			if ((tmpHTree=ItemIdArray[AtoiPos]) || (tmpHTree=GetSelectedItem())) 	retint=EnsureVisible(tmpHTree);
			break;
		case 56: /*SortChildrenCB*/
			{
				TVSORTCB Tvs={0};
				if (*pos==0 || *pos<'0' || *pos>'9')
					Tvs.hParent=GetSelectedItem();
				else
					Tvs.hParent=ItemIdArray[AtoiPos];

				if (Tvs.hParent)
					retint=SortChildrenCB(&Tvs);
			}
			break;
		case 57: /*UpdateGroup*/
			if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
			{
				int cs=-123456;
				if ((tmpHTree=GetSelectedItem())!=NULL) cs=ItemIdArray.GetIdByVal(tmpHTree);

				if (tmpHTree && (GPPA_IdParent || GPPA_Image || GPPA_SelImage || GPPA_lValue || GPPA_IdItem))
				{
					TVITEM tmpItem={0};
					tmpItem.hItem=tmpHTree;
					tmpItem.mask=TVIF_HANDLE|TVIF_IMAGE|TVIF_PARAM|TVIF_SELECTEDIMAGE;
					if (GetItem(&tmpItem))
					{
						if (GPPA_Image)
							GPPA_Image->SetOnStyles(tmpItem.iImage);

						if (GPPA_SelImage)
							GPPA_SelImage->SetOnStyles(tmpItem.iSelectedImage);

						if (GPPA_lValue)
							GPPA_lValue->SetOnStyles(tmpItem.lParam);

						if (GPPA_IdItem)
							GPPA_IdItem->SetOnStyles(cs);

						if (GPPA_IdParent)
							GPPA_IdParent->SetOnStyles(ItemIdArray.GetIdByVal(GetParentItem(tmpHTree)));
					}
				}
				else
				{
						if (GPPA_Image)
							GPPA_Image->SetOffStyles(-1);

						if (GPPA_SelImage)
							GPPA_Image->SetOffStyles(-1);

						if (GPPA_lValue)
							GPPA_Image->SetOffStyles(-1);

						if (GPPA_IdItem)
							GPPA_Image->SetOffStyles(-1);

						if (GPPA_IdParent)
							GPPA_Image->SetOffStyles(-1);
				}

				referGPU[UnitId&0xFFFF]->UpdateGroup(cs,GetStyle());
			}
			break;
		case 58: /*GetTreeStyle*/
			if (oStr!=NULL)
				GetObjStlStr(oStr, GetStyle(), N_TREECTRL_STYLES,  aTreeCtrlStyleName, aTreeCtrlStyleUINT, aTreeCtrlStyleMask);
			break;
		case 59: /*GetChecked*/
			if (oStr!=NULL)
			{
				int nn=0;
				if (ItemIdArray.SelectFirst()!=0xFFFFFFFFL)
					do
						if ((tmpHTree=ItemIdArray[ItemIdArray.GetSelectedId()])!=NULL &&	GetCheck(tmpHTree))
							nn+=sprintf(oStr+nn,"%d\x7F",ItemIdArray.GetSelectedId());
					while(ItemIdArray.SelectNext()!=0xFFFFFFFFL);
				if (nn!=0) oStr[--nn]=0;
			}
			break;
		case 60: /*GetParents*/
			if (oStr!=NULL)
			{
				char *posout=oStr;
				CString TextStr;

				if (*pos==0 || *pos<'0' || *pos>'9')
					tmpHTree=GetSelectedItem();
				else
					tmpHTree=ItemIdArray[AtoiPos];

				if (tmpHTree!=NULL)
				{
					do
					{
						if (posout==oStr) posout+=sprintf(posout,"%d",ItemIdArray.GetIdByVal(tmpHTree));
						else 
						{
							posout+=sprintf(posout,"\x7%d",ItemIdArray.GetIdByVal(tmpHTree));
							TextStr+="\x7";
						}
						TextStr+=GetItemText(tmpHTree);
					}
					while((tmpHTree=GetParentItem(tmpHTree))!=NULL);
				}
				sprintf(posout,"\x7F%s",(const char *)TextStr);
			}
			break;
		case 61: /*DeleteAllChild*/
			{
				if (*pos)	tmpHTree=ItemIdArray[AtoiPos];
				else		tmpHTree=GetSelectedItem();
				if (tmpHTree!=NULL)
				{
					HTREEITEM tmpHTree2;
					while((tmpHTree2=GetChildItem(tmpHTree)))
						DeleteItem(tmpHTree2);
				}
			}
			break;
		case 3: /*GetImageList*/
			if (oStr!=NULL)
			{
				UINT type=0;
				if (_stricmp(pos,"NORMAL")==0)  type=TVSIL_NORMAL;
				else type=TVSIL_STATE;
				CImageList* tmp=GetImageList(type);
				int id=GPC.FindImageList(tmp);
				if (id>=0) strcpy(oStr,GPC.a_GPImageList[id].ILName);
			}
			break;
		case 4: /*SetImageList*/
			{
				const char *pos2=strchr(pos,',');
				UINT type=LVSIL_NORMAL;
				if (pos2!=NULL)
				{
					if (_stricmp(++pos2,"NORMAL")==0) type=TVSIL_NORMAL;
					else  type=TVSIL_STATE;
				}
				int num;
				if ((num=GPC.GetImageListId(ExtractField(pos,1,",")))>=0)
				{
					SetImageList(&(GPC.a_GPImageList[num].m_IL),type );
				}
			}
			break;

		case 21: /*GetItemImage*/
			if (oStr!=NULL)
			{
				int nImage=0,nSelectedImage=0;
				if ((tmpHTree=ItemIdArray[AtoiPos]) || (tmpHTree=GetSelectedItem()))
				{
					retint=GetItemImage(tmpHTree,nImage,nSelectedImage);
					sprintf(oStr,"%d\x7F%d\x7F%d",retint,nImage,nSelectedImage);
				}
			}
		case 22: /*SetItemImage*/
			{
				int nImage=0,nSelectedImage=0;
				HTREEITEM itm=TVI_ROOT;
				if (*pos==0 || *pos<'0' || *pos>'9')
					itm=GetSelectedItem();
				else
					itm=ItemIdArray[AtoiPos];

				if (itm)
				{
					const char *pos2=strchr(pos,',');
					if (pos2++==NULL) pos2="";
					m_LastScanf=sscanf(pos2,"%d,%d",&nImage,&nSelectedImage);
					retint=SetItemImage(itm,nImage,nSelectedImage);
				}
			}
			break;
		case 62: /*SetDragROOT*/
			retint=m_bDragROOT;
			m_bDragROOT=atoi(pos);
			break;
		case 63: /*CopyChildren*/
			{
				int itemDst=0,itemSrc=0,nDelt=200000;
				m_LastScanf=sscanf(pos,"%d,%d,%d",&itemDst,&itemSrc,&nDelt);
				CopyChildren(ItemIdArray[itemDst],ItemIdArray[itemSrc],nDelt);
			}
			break;
		case 64: /*EndEditLabel*/
			SendMessage(TVM_ENDEDITLABELNOW,(WPARAM)AtoiPos,0);
			break;
		case 65: /*GetISearchString*/
			if (oStr) SendMessage(TVM_GETISEARCHSTRING,0,(LPARAM)oStr);
			break;
		case 66: /*SetUnicodeFormat*/
			retint=SendMessage(TVM_SETUNICODEFORMAT,AtoiPos,0);
			break;
		case 67: /*GetUnicodeFormat*/
			retint=SendMessage(TVM_GETUNICODEFORMAT,0,0);
			break;
		case 68: /*SetScrollTime*/
			retint=SendMessage(TVM_SETSCROLLTIME,AtoiPos,0);
			break;
		case 69: /*GetScrollTime*/
			retint=SendMessage(TVM_GETSCROLLTIME,0,0);
			break;
		case 72: /*MapAccIdToHTREEITEM*/
			retint=ItemIdArray.GetIdByVal(
				(HTREEITEM)SendMessage(TVM_MAPACCIDTOHTREEITEM,(WPARAM)AtoiPos,0)
				);
			break;
		case 73: /*MapHTREEITEMToAccId*/
			retint=-1;
			if (ItemIdArray[AtoiPos]!=NULL)
				retint=SendMessage(TVM_MAPHTREEITEMTOACCID,(WPARAM)ItemIdArray[AtoiPos],0);
			break;
		case 74: /*MoveTree hDst,hSrc*/
			{
				int iSrc=0;
				int iDst=0;
				m_LastScanf=sscanf(pos,"%d,%d",&iDst,&iSrc);
				HTREEITEM hSrc=ItemIdArray[iSrc];
				HTREEITEM hDst=ItemIdArray[iDst];
				if (hDst==NULL || strstr(pos,"ROOT")) hDst=TVI_ROOT;

				if (hSrc!=hDst && hSrc && hDst)
					MoveTree(hDst,hSrc);
			}
			break;
		case 75: /*ClearDropHilight*/
			SelectDropTarget(NULL);
			/*
			{
				HTREEITEM hi=GetDropHilightItem();
				if (hi)
					SetItemState(hi,0,TVIS_DROPHILITED);
			}*/
			break;
		case 76: /*ClearSelection*/
			{
				HTREEITEM hi=GetSelectedItem();
				if (hi)
					SetItemState(hi,0,TVIS_SELECTED);
			}
			break;
		case 77: /*AutoClearDropHilight*/
			retint=m_ClearDropHilight;
			m_ClearDropHilight=AtoiPos;
			break;
		case 78: /*CopyTree hDst,hSrc,iDelta*/
			{
				int iSrc=0;
				int iDst=0;
				int iDelta=0;
				m_LastScanf=sscanf(pos,"%d,%d,%d",&iDst,&iSrc,&iDelta);
				HTREEITEM hSrc=ItemIdArray[iSrc];
				HTREEITEM hDst=ItemIdArray[iDst];
				if (hDst==NULL || strstr(pos,"ROOT")) hDst=TVI_ROOT;
				if (hSrc!=hDst && hSrc && hDst)
					CopyTree(hDst,hSrc,iDelta);
			}
			break;
		case 79: /*GetChildList*/
			if (oStr)
			{
				HTREEITEM gcl=NULL;
				if (*pos>='0' && *pos<='9') gcl=ItemIdArray[AtoiPos];
				else
				if (*pos==0 || strstr(pos,"ROOT") || strstr(pos,"root")) gcl=TVI_ROOT;
				else
				if (strstr(pos,"HILI") || strstr(pos,"hili")) gcl=GetDropHilightItem();
				else
				if (strstr(pos,"sel") || strstr(pos,"SEL")) gcl=GetSelectedItem();

				if (gcl)
				{
					UINT nLevels=atoi(ExtractField(pos,2,","));
					if (nLevels==0) nLevels=10000;
					UINT nArr=GetChildList(gcl,NULL,1000,gcl);
					if (nArr)
					{
						HTREEITEM *mArr=new HTREEITEM [nArr+5];
						GetChildList(gcl,mArr,1000,gcl);
						CString tmps=ExtractField(pos,2,",");
						char *outs=oStr;
						if (tmps=="")
						{
							UINT i;
							for(i=0;i<nArr;i++)
								if (i)
									outs+=sprintf(outs,"\x7F%d",ItemIdArray.GetIdByVal(mArr[i]));
								else
									outs+=sprintf(outs,"\x7F%d",ItemIdArray.GetIdByVal(mArr[i]));
						}
						else
						{
							UINT i;
							for(i=0;i<nArr;i++)
							{
								if (i) {*(outs++)=0x7f; *(outs)=0;}
								ItemString(mArr[i],outs,7);
								if (*outs)
									while(*(++outs));
							}
						}
						delete[] mArr;
					}
				}
			}
			break;
		case 80: /*NormalizeTree*/
			ItemIdArray.Normalize(AtoiPos,atoi(ExtractField(pos,2,",")),atoi(ExtractField(pos,3,",")));
			break;
		case 81: /*RestoreId*/
			if (*pos)	ItemIdArray.RestoreId(AtoiPos,atoi(ExtractField(pos,2,",")));
			else		ItemIdArray.RestoreArrayId();
			break;
		case 82: /*ChangeId*/
			ItemIdArray.ChangeId(AtoiPos,atoi(ExtractField(pos,2,",")));
			break;
		case 83: /*SaveId*/
			if (*pos)	ItemIdArray.SaveId(AtoiPos);
			else		ItemIdArray.SaveArrayId();
			break;
		case 84: /*GetIdArray*/
			if (oStr)
			{
				UINT *IdA=NULL;
				UINT nItems=ItemIdArray.GetIdArray(&IdA);
				char *posout=oStr;
				if (nItems)
				{
					posout+=sprintf(posout,"%d",*IdA);
					UINT i;
					for(i=1;i<nItems;i++)
						posout+=sprintf(posout,"\x7F%d",IdA[i]);
				}
			}
			break;
		case 85: /*GetIdArraySave*/
			if (oStr)
			{
				UINT *IdA=NULL;
				UINT nItems=ItemIdArray.GetIdArraySave(&IdA);
				char *posout=oStr;
				if (nItems)
				{
					posout+=sprintf(posout,"%d",*IdA);
					UINT i;
					for(i=1;i<nItems;i++)
						posout+=sprintf(posout,"\x7F%d",IdA[i]);
				}
			}
			break;
		case 86: /*SetIdArray*/
		case 87: /*SetIdArraySave*/
			if (*pos)
			{
				const char *pos2=pos;
				UINT nItems=ItemIdArray.GetCount();
				UINT i=0;
				if (nItems)
				{
					UINT *Arr=new UINT [nItems];
					while(i<nItems && *pos2)
					{
						Arr[i]=atoi(pos2);
						while(*pos2 && *pos2<='9' && *pos2>='0') pos2++;
						while(*pos2 && (*pos2>'9' || *pos2<'0')) pos2++;
					}
					if (nfunc==86)
						ItemIdArray.SetIdArray(Arr);
					else
						ItemIdArray.SetIdArraySave(Arr);
					delete[] Arr;
				}
			}
			break;
		case 88: /*GetContents*/
			if (oStr)
			{
				UINT *mArr;
				UINT nItem=ItemIdArray.GetIdArray(&mArr);
				if (nItem)
				{
					char *outs=oStr;
					UINT i;
					for(i=0;i<nItem;i++)
					{
						if (i) {*(outs++)=0x7f; *(outs)=0;}
						ItemString(ItemIdArray[mArr[i]],outs,7);
						if (*outs)
							while(*(++outs));
					}
					delete[] mArr;
				}
			}
			break;
		case 89: /*GetTreeStructure*/
			if (oStr)
			{
				HTREEITEM gcl=NULL;
				if (*pos>='0' && *pos<='9') gcl=ItemIdArray[AtoiPos];
				else
				if (*pos==0 || strstr(pos,"ROOT") || strstr(pos,"root")) gcl=TVI_ROOT;
				else
				if (strstr(pos,"HILI") || strstr(pos,"hili")) gcl=GetDropHilightItem();
				else
				if (strstr(pos,"sel") || strstr(pos,"SEL")) gcl=GetSelectedItem();

				if (gcl)
				{
					UINT nArr=GetChildList(gcl,NULL,1000,gcl);
					if (nArr)
					{
						HTREEITEM *mArr=new HTREEITEM [nArr+5];
						GetChildList(gcl,mArr,1000,gcl);
						char *outs=oStr;
						HTREEITEM hParentOld=NULL;
						UINT idParentOld=-1;
						UINT i;
						for(i=0;i<nArr;i++)
						{
							HTREEITEM hParent=GetParentItem(mArr[i]);
							if (hParent!=hParentOld) idParentOld=ItemIdArray.GetIdByVal(hParent);
							hParentOld=hParent;
							outs+=sprintf(outs,"%s%d\x07%d",i?"\x7F":"",ItemIdArray.GetIdByVal(mArr[i]),idParentOld);
						}
						delete[] mArr;
					}
				}
			}
			break;
		case 90: /*GetChildListEx  IdItem,nLevels,Attributes*/
			if (oStr)
			{
				HTREEITEM gcl=NULL;
				if (*pos>='0' && *pos<='9') gcl=ItemIdArray[AtoiPos];

				if (gcl==NULL)
					if (*pos==0 || strstr(pos,"ROOT") || strstr(pos,"root")) gcl=TVI_ROOT;
					else
					if (strstr(pos,"HILI") || strstr(pos,"hili")) gcl=GetDropHilightItem();
					else
					if (strstr(pos,"sel") || strstr(pos,"SEL")) gcl=GetSelectedItem();

				if (gcl)
				{
					UINT nLevels=atoi(ExtractField(pos,2,","));
					if (nLevels==0) nLevels=10000;
					DWORD AttrArray[]={TVIF_HANDLE,0,0,0,0,0,0,0,0,0,0,};
					{
						CString tmps=ExtractField(pos,3,",");
						if (tmps!="")
						{
							CString Attr;
							int i;
							for(i=1;i<10 && (Attr=ExtractField(tmps,i,"|"))!="";i++)
							{
								AttrArray[i-1]=TVIF_HANDLE;
								int j;
								for(j=0;j<GPTree::nTVIF && strstr(GPTree::TVIFName[j],Attr)==NULL;j++);

								if (j<GPTree::nTVIF)
									AttrArray[i-1]=GPTree::TVIFUINT[j];
							}
						}

					}

					UINT nArr=GetChildList(gcl,NULL,1000,gcl);
					if (nArr)
					{
						HTREEITEM *mArr=new HTREEITEM [nArr+5];
						GetChildList(gcl,mArr,1000,gcl);
						CString tmps=ExtractField(pos,2,",");
						char *outs=oStr;
						UINT i;
						for(i=0;i<nArr;i++)
						{
							if (i) {*(outs++)=0x7f; *(outs)=0;}
							ItemString(mArr[i],outs,7,AttrArray);
							if (*outs)
								while(*(++outs));
						}
						delete[] mArr;
					}
				}
			}
			break;
		case 91: /*GetContentsEx  IdItem,nLevels,Attributes*/
			if (oStr)
			{
				DWORD AttrArray[]={TVIF_HANDLE,0,0,0,0,0,0,0,0,0,0,};
				{
					CString Attr;
					int i;
					for(i=1;i<10 && (Attr=ExtractField(pos,i,"|"))!="";i++)
					{
						AttrArray[i-1]=TVIF_HANDLE;
						int j;
						for(j=0;j<GPTree::nTVIF && strstr(GPTree::TVIFName[j],Attr)==NULL;j++);

						if (j<GPTree::nTVIF)
							AttrArray[i-1]=GPTree::TVIFUINT[j];
					}
				}
				UINT *mArr;
				UINT nItem=ItemIdArray.GetIdArray(&mArr);
				if (nItem)
				{
					char *outs=oStr;
					UINT i;
					for(i=0;i<nItem;i++)
					{
						if (i) {*(outs++)=0x7f; *(outs)=0;}
						ItemString(ItemIdArray[mArr[i]],outs,7,AttrArray);
						if (*outs)
							while(*(++outs));
					}
					delete[] mArr;
				}

			}
			break;
		case 92: /*IsChildOf*/
			{
				retint=0;
				HTREEITEM ch=ItemIdArray[AtoiPos],pa=ItemIdArray[atoi(ExtractField(pos,2,","))];
				if (ch && pa)
					retint=IsChildOf(ch,pa);
			}
			break;
		case 93: /*DependsSet type,{Value1|Value2|..,IdDlg,IdObj1|IdObj2|..,OnStyleAdd,OnStyleDel,OffStyleAdd,OffStyleDel[^]}*/
		case 94: /*DependsDelete type,Value,Id,IdObj*/
		case 95: /*DependsDeleteStyle type,{Value1|Value2|..,IdDlg,IdObj1|IdObj2|..,OnStyleAdd,OnStyleDel,OffStyleAdd,OffStyleDel[^]}*/
		case 96: /*DependsAddStyle type,{Value1|Value2|..,IdDlg,IdObj1|IdObj2|..,OnStyleAdd,OnStyleDel,OffStyleAdd,OffStyleDel[^]}*/
			{
				//type IMAGE SELIMAGE PARAM IDITEM IDPARENT
				CGPWndPropertyArray **ptrArr=NULL;
				CString tmps=ExtractField(pos,1,",");
				if (tmps=="IMAGE") ptrArr=&GPPA_Image;
				else
				if (tmps=="SELIMAGE") ptrArr=&GPPA_SelImage;
				else
				if (tmps=="PARAM") ptrArr=&GPPA_lValue;
				else
				if (tmps=="IDITEM") ptrArr=&GPPA_IdItem;
				else
				if (tmps=="IDPARENT") ptrArr=&GPPA_IdParent;
				else ptrArr=NULL;

				const char *pos2=strchr(pos,',');
				CString Valuesfield;
				CString Valuefield;
				CString IdObjfield;
				CString IdObjfield1;
				CString sStylesOnAdd;
				CString sStylesOnDel;
				CString sStylesOffAdd;
				CString sStylesOffDel;

				switch(nfunc)
				{
				case 93:/*DependsSet*/
					if (ptrArr && pos2 && *ptrArr==NULL)
						*ptrArr= new CGPWndPropertyArray;
				case 95:/*DependsDeleteStyle*/
				case 96:/*DependsAddStyle*/
					if (ptrArr && *ptrArr && pos2)
					{
						do
						{
							pos2++;
							Valuesfield=ExtractField(pos2,1,",");
							if (nfunc!=93 && Valuesfield=="")
								(**ptrArr).GetIdsList(Valuesfield,"|");

							UINT IdDlg=GPC.FindDlg(ExtractField(pos2,2,","));
							if (IdDlg<MAX_OBJDLG && Valuesfield!="")
							{
								IdObjfield1=ExtractField(pos2,3,",");
								GPUNITINFO gpui;
								GPPAITEM GPPAI={0};
								UINT nObj=0;
								sStylesOnAdd=ExtractField(pos2,4,",")+"|";
								sStylesOnDel=ExtractField(pos2,5,",")+"|";
								sStylesOffAdd=ExtractField(pos2,6,",")+"|";
								sStylesOffDel=ExtractField(pos2,7,",")+"|";



								while((IdObjfield=ExtractField(IdObjfield1,++nObj,"|"))!="" || nObj==1)
								{
									gpui.hWnd=(HWND)GPPAI_ALLWINDOWS;
									if (IdObjfield=="" || (GPC.FindObject(IdDlg,IdObjfield,gpui) && gpui.hWnd))
									{
										UINT nValue=0;
										while((Valuefield=ExtractField(Valuesfield,++nValue,"|"))!="")
										{
											GPUnit *gu=GPC.GetDlgObject(IdDlg,gpui.IdObj);
											if (gu)
											{
												GPPAI.OnAddStyle=gu->StringToStyle(sStylesOnAdd);
												GPPAI.OnDelStyle=gu->StringToStyle(sStylesOnDel);
												GPPAI.OffAddStyle=gu->StringToStyle(sStylesOffAdd);
												GPPAI.OffDelStyle=gu->StringToStyle(sStylesOffDel);
												GPPAI.OnAddStyleEx=gu->StringToStyleEx(sStylesOnAdd);
												GPPAI.OnDelStyleEx=gu->StringToStyleEx(sStylesOnDel);
												GPPAI.OffAddStyleEx=gu->StringToStyleEx(sStylesOffAdd);
												GPPAI.OffDelStyleEx=gu->StringToStyleEx(sStylesOffDel);
												switch(nfunc)
												{
												case 93:/*DependsSet*/
													(**ptrArr)[atoi(Valuefield)].AddWnd(gpui.hWnd,GPPAI);
													break;
												case 95:/*DependsDeleteStyle*/
													(**ptrArr)[atoi(Valuefield)].WndDelStyles(gpui.hWnd,GPPAI);
													break;
												case 96:/*DependsAddStyle*/
													(**ptrArr)[atoi(Valuefield)].WndAddStyles(gpui.hWnd,GPPAI);
													break;
												}

											}
										}
									}
								}
							}
							pos2=strchr(pos2,GPC.DelimiterIn1);
						}
						while(pos2);
					}
					break;
				case 94: /*DependsDelete type,Value,Id,IdObj*/
					{
						if (ptrArr && *ptrArr && pos2)
						{
							do
							{
								pos2++;
								Valuesfield=ExtractField(pos2,1,",");
								if (Valuesfield=="")
									(**ptrArr).GetIdsList(Valuesfield,"|");
								UINT IdDlg=GPC.FindDlg(ExtractField(pos2,2,","));
								if (IdDlg<MAX_OBJDLG && Valuesfield!="")
								{
									IdObjfield1=ExtractField(pos2,3,",");
									GPUNITINFO gpui;
									UINT nObj=0;

									while((IdObjfield=ExtractField(IdObjfield1,++nObj,"|"))!="" || nObj==1)
									{
										gpui.hWnd=(HWND)GPPAI_ALLWINDOWS;
										if (IdObjfield=="" || (GPC.FindObject(IdDlg,IdObjfield,gpui) && gpui.hWnd))
										{
											UINT nValue=0;
											while((Valuefield=ExtractField(Valuesfield,++nValue,"|"))!="")
												(**ptrArr)[atoi(Valuefield)].DeleteWnd(gpui.hWnd);
										}
									}
								}
								else
								{
								}
								pos2=strchr(pos2,GPC.DelimiterIn1);
							}
							while(pos2);
						}
					}
					break;
				}
			}
			break;

		case 97: /*SpecialFill [type]*/
			{
				DeleteAllItems();
				char *tmps=new char [150000];
				int nImage=0,nSelectedImage=0;
				HTREEITEM hParent=TVI_ROOT;
				HTREEITEM hParent2=NULL;


				hParent=InsertItem("Objects",nImage,nSelectedImage,TVI_ROOT,TVI_LAST);
				ItemIdArray[10000000]=hParent;

				UINT i1;
				for(i1=1;*GPUnit::aTypeUnit[i1];i1++)
					ItemIdArray[10100000+GPUnit::auTypeUnit[i1]]=InsertItem(GPUnit::aTypeUnit[i1],nImage,nSelectedImage,hParent,TVI_LAST);

				::SendMessage(m_hWnd,TVM_SORTCHILDREN,0,(LPARAM)hParent);

				hParent=InsertItem("Methods",nImage,nSelectedImage,TVI_ROOT,TVI_LAST);
				ItemIdArray[10200000]=hParent;
				{
					for(i1=1;*GPUnit::aTypeUnit[i1];i1++)
					{
						char tmpcomm[100];
						sprintf(tmpcomm,"GetGUIObjectMethods %s",GPUnit::aTypeUnit[i1]);
						CDlgViewSystemMethods::DoMethod(tmpcomm,tmps);
						if (*tmps)
						{
							hParent2=InsertItem(GPUnit::aTypeUnit[i1],nImage,nSelectedImage,hParent,TVI_LAST);
							ItemIdArray[10200000+GPUnit::auTypeUnit[i1]*1000]=hParent2;
							char *pos333=tmps;
							int tmpitem=0;
							while (*pos333)
							{
								char *pos2=pos333;
								while(*pos2 && *pos2!=0x2) pos2++;
								if (*pos2)
								{
									switch(AtoiPos)
									{
									case 1:		if (pos2[1]>=' ') *(pos2++)=' '; else *(pos2++)=0;	break;
									case 0:
									default:	*(pos2++)=0;	break;
									}
									while(*pos2 && *pos2!=0x1) pos2++;
									if (*pos2) *(pos2++)=0;
								}
								tmpitem++;
								InsertItem(pos333,nImage,nSelectedImage,hParent2,TVI_LAST);
								ItemIdArray[10200000+GPUnit::auTypeUnit[i1]*1000+tmpitem]=hParent2;
								pos333=pos2;
							}
							::SendMessage(m_hWnd,TVM_SORTCHILDREN,0,(LPARAM)hParent2);
						}
					}
					hParent2=InsertItem("WINDOWS",nImage,nSelectedImage,hParent,TVI_LAST);
					ItemIdArray[10299000]=hParent2;
					switch(AtoiPos)
					{
					case 1:
						{
							char *tmpstr = new char [2000];
							for(i1=0;*GPUnit::cArrMethods[i1];i1++)
							{
								strcpy(tmpstr,GPUnit::cArrMethods[i1]);
								if (*GPUnit::cArrMethodsParams[i1])
								{
									strcat(tmpstr," ");
									strcat(tmpstr,GPUnit::cArrMethodsParams[i1]);
								}
								ItemIdArray[10299001+i1]=InsertItem(tmpstr,nImage,nSelectedImage,hParent2,TVI_LAST);
							}
							delete[] tmpstr;
						}
						break;
					case 0:
					default:
						for(i1=0;*GPUnit::cArrMethods[i1];i1++)
							ItemIdArray[10299001+i1]=InsertItem(GPUnit::cArrMethods[i1],nImage,nSelectedImage,hParent2,TVI_LAST);
						break;
					}

					::SendMessage(m_hWnd,TVM_SORTCHILDREN,0,(LPARAM)hParent2);
					::SendMessage(m_hWnd,TVM_SORTCHILDREN,0,(LPARAM)hParent);
				}

				hParent=InsertItem("Events",nImage,nSelectedImage,TVI_ROOT,TVI_LAST);
				ItemIdArray[10300000]=hParent;
				{
					for(i1=1;*GPUnit::aTypeUnit[i1];i1++)
						if (aUnitMessage[i1] && *aUnitMessage[i1])
						{
							hParent2=InsertItem(GPUnit::aTypeUnit[i1],nImage,nSelectedImage,hParent,TVI_LAST);
							ItemIdArray[10300000+GPUnit::auTypeUnit[i1]*1000]=hParent2;
							strcpy(tmps,aUnitMessage[i1]);
							if (*tmps) strcat(tmps,aUnitCommonMessages);
							char *pos333=tmps;
							int tmpitem=0;
							while (*pos333)
							{
								char *pos2=pos333;
								while(*pos2 && *pos2!=',') pos2++;
								if (*pos2)	*(pos2++)=0;
								while(*pos2 && *pos2==',') pos2++;
								tmpitem++;
								InsertItem(pos333,nImage,nSelectedImage,hParent2,TVI_LAST);
								ItemIdArray[10300000+GPUnit::auTypeUnit[i1]*1000+tmpitem]=hParent2;
								pos333=pos2;
							}
							::SendMessage(m_hWnd,TVM_SORTCHILDREN,0,(LPARAM)hParent2);
						}
					hParent2=InsertItem("WINDOWS",nImage,nSelectedImage,hParent,TVI_LAST);
					ItemIdArray[10399000]=hParent2;

					for(i1=0;i1<N_WND_MESSAGE;i1++)
						ItemIdArray[10399001+i1]=InsertItem(alpmes[i1],nImage,nSelectedImage,hParent2,TVI_LAST);

					::SendMessage(m_hWnd,TVM_SORTCHILDREN,0,(LPARAM)hParent2);
					::SendMessage(m_hWnd,TVM_SORTCHILDREN,0,(LPARAM)hParent);
				}


				hParent=InsertItem("Styles",nImage,nSelectedImage,TVI_ROOT,TVI_LAST);
				ItemIdArray[10400000]=hParent;
				{
					for(i1=1;*GPUnit::aTypeUnit[i1];i1++)
					{
						char tmpcomm[100];
						sprintf(tmpcomm,"GetGUIObjectStyles %s",GPUnit::aTypeUnit[i1]);
						CDlgViewSystemMethods::DoMethod(tmpcomm,tmps);
						if (*tmps)
						{
							hParent2=InsertItem(GPUnit::aTypeUnit[i1],nImage,nSelectedImage,hParent,TVI_LAST);
							ItemIdArray[10400000+GPUnit::auTypeUnit[i1]*1000]=hParent2;
							char *pos22=tmps;
							int tmpitem=0;
							while (*pos22)
							{
								char *pos2=pos22;
								while(*pos2 && *pos2!=0x2) pos2++;
								if (*pos2)
								{
									*(pos2++)=0;
									while(*pos2 && *(pos2++)!=0x1);
								}
								tmpitem++;
								InsertItem(pos22,nImage,nSelectedImage,hParent2,TVI_LAST);
								ItemIdArray[10400000+GPUnit::auTypeUnit[i1]*1000+tmpitem]=hParent2;
								pos22=pos2;
							}

							sprintf(tmpcomm,"GetGUIObjectExStyles %s",GPUnit::aTypeUnit[i1]);
							CDlgViewSystemMethods::DoMethod(tmpcomm,tmps);
							if (*tmps)
							{
								char *pos333=tmps;
								while (*pos333)
								{
									char *pos2=pos333;
									while(*pos2 && *pos2!=0x2) pos2++;
									if (*pos2)
									{
										*(pos2++)=0;
										while(*pos2 && *(pos2++)!=0x1);
									}
									tmpitem++;
									InsertItem(pos333,nImage,nSelectedImage,hParent2,TVI_LAST);
									ItemIdArray[10400000+GPUnit::auTypeUnit[i1]*1000+tmpitem]=hParent2;
									pos333=pos2;
								}
								::SendMessage(m_hWnd,TVM_SORTCHILDREN,0,(LPARAM)hParent2);
							}
						}

					}
					hParent2=InsertItem("WINDOWS",nImage,nSelectedImage,hParent,TVI_LAST);
					ItemIdArray[10499000]=hParent2;
					for(i1=0;i1<N_WND_STYLES;i1++)
						ItemIdArray[10499001+i1]=InsertItem(aWndStyleName[i1],nImage,nSelectedImage,hParent2,TVI_LAST);
					for(i1=0;i1<N_WND_EX_STYLES;i1++)
						ItemIdArray[10499001+N_WND_STYLES+i1]=InsertItem(aWndExStyleName[i1],nImage,nSelectedImage,hParent2,TVI_LAST);

					::SendMessage(m_hWnd,TVM_SORTCHILDREN,0,(LPARAM)hParent2);
					::SendMessage(m_hWnd,TVM_SORTCHILDREN,0,(LPARAM)hParent);
				}

				hParent=InsertItem("System Methods",nImage,nSelectedImage,TVI_ROOT,TVI_LAST);
				ItemIdArray[10500000]=hParent;
				for(i1=0;*CDlgViewSystemMethods::cArrMethods[i1];i1++)
					ItemIdArray[10500001+i1]=InsertItem(CDlgViewSystemMethods::cArrMethods[i1],nImage,nSelectedImage,hParent,TVI_LAST);
				::SendMessage(m_hWnd,TVM_SORTCHILDREN,0,(LPARAM)hParent);

				hParent=InsertItem("Image List Methods",nImage,nSelectedImage,TVI_ROOT,TVI_LAST);
				ItemIdArray[10600000]=hParent;
				for(i1=0;i1<GPImageList::uNMethods;i1++)
					ItemIdArray[10600001+i1]=InsertItem(GPImageList::cArrMethods[i1],nImage,nSelectedImage,hParent,TVI_LAST);
				::SendMessage(m_hWnd,TVM_SORTCHILDREN,0,(LPARAM)hParent);

				hParent=InsertItem("File System Methods",nImage,nSelectedImage,TVI_ROOT,TVI_LAST);
				ItemIdArray[10700000]=hParent;
				for(i1=0;*CGP_TermDoc::cArrFSMethods[i1];i1++)
					ItemIdArray[10700001+i1]=InsertItem(CGP_TermDoc::cArrFSMethods[i1],nImage,nSelectedImage,hParent,TVI_LAST);
				::SendMessage(m_hWnd,TVM_SORTCHILDREN,0,(LPARAM)hParent);

				hParent=InsertItem("IOFiles",nImage,nSelectedImage,TVI_ROOT,TVI_LAST);
				ItemIdArray[10800000]=hParent;
				for(i1=0;i1<GPIOFile::uNMethods;i1++)
					ItemIdArray[10800001+i1]=InsertItem(GPIOFile::cArrMethods[i1],nImage,nSelectedImage,hParent,TVI_LAST);
				::SendMessage(m_hWnd,TVM_SORTCHILDREN,0,(LPARAM)hParent);

				hParent=InsertItem("Registry Methods",nImage,nSelectedImage,TVI_ROOT,TVI_LAST);
				ItemIdArray[10900000]=hParent;
				for(i1=0;i1<GPCurrent::uNRegistryMethods;i1++)
					ItemIdArray[10900001+i1]=InsertItem(GPCurrent::cArrRegistryMethods[i1],nImage,nSelectedImage,hParent,TVI_LAST);
				::SendMessage(m_hWnd,TVM_SORTCHILDREN,0,(LPARAM)hParent);

				hParent=InsertItem("User Menu",nImage,nSelectedImage,TVI_ROOT,TVI_LAST);
				ItemIdArray[11000000]=hParent;
				for(i1=0;i1<CGPContextMenu::uNMethods;i1++)
					ItemIdArray[11000001+i1]=InsertItem(CGPContextMenu::cArrMethods[i1],nImage,nSelectedImage,hParent,TVI_LAST);
				::SendMessage(m_hWnd,TVM_SORTCHILDREN,0,(LPARAM)hParent);

				hParent=InsertItem("Free Tables",nImage,nSelectedImage,TVI_ROOT,TVI_LAST);
				ItemIdArray[11100000]=hParent;
				for(i1=0;i1<CGPSpr::uNMethods;i1++)
					ItemIdArray[11100001+i1]=InsertItem(CGPSpr::cArrMethods[i1],nImage,nSelectedImage,hParent,TVI_LAST);
				::SendMessage(m_hWnd,TVM_SORTCHILDREN,0,(LPARAM)hParent);

				delete[] tmps;
			}
			break;

		case 98: /*GetTreeExtendedStyle*/
			if (oStr!=NULL)
				GetObjStlStr(oStr, GetExtendedStyle(), N_LISTCTRL_EX_STYLES,  aListCtrlExStyleName, aListCtrlExStyleUINT, aListCtrlExStyleMask);
			break;
		case 99: /*SetTreeExtendedStyle ExStyle*/
			{
				UINT stl=0;
				int i;
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				_strupr(pos333);
				for(i=0;i<N_LISTCTRL_EX_STYLES;i++)
					if (strstr(pos333,aListCtrlExStyleName[i])!=NULL) stl|=aListCtrlExStyleUINT[i];

				stl=SetExtendedStyle(stl);
				delete[] pos333;
			}
			break;




		case 28: /*GetEditControl*/ // не реализовано
		case 30: /*GetToolTips*/ // не реализовано
		case 31: /*SetToolTips*/ // не реализовано
		case 53: /*CreateDragImage*/ // не реализовано
		default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
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
		GPC.m_ErrReport.GPWriteErrorLog("GPTree", "DoMethod",iStr);
		delete[] str;
	}
		if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);

	return nfunc;
}

UINT GPTree::GPSetProperty(char *iStr)
{
	char *iValue=new char [(int)strlen(iStr)+5];
	strcpy(iValue,iStr);
	UINT ret=1,i;
	char *pos=strchr(iValue,'=');

	if (pos!=NULL && m_hWnd)
	{
		char *prop[]={"ADDSTYLE", "DELSTYLE","STYLE", };
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
					// GPTabCtrl specif
					for(i=0;i<N_TREECTRL_STYLES;i++)
						if (strstr(pos,aTreeCtrlStyleName[i])!=NULL)
						{
							InvFlg++;
							switch(propnum)
							{
							case 2: /* STYLE*/
							case 0: /* ADDSTYLE*/	ModifyStyle(0,aTreeCtrlStyleUINT[i]);break;
							case 1: /* DELSTYLE*/	ModifyStyle(aTreeCtrlStyleUINT[i],0);break;
							}
						}

					UINT es=GetExtendedStyle();
					if (propnum==2) es=0;
					char *postmp=strstr(pos,"&X");
					if (postmp!=NULL)
					{
						UINT tmpstl=0;
						m_LastScanf=sscanf(postmp,"&X%X",&tmpstl);
						InvFlg++;
						switch(propnum)
						{
						case 2: /* STYLE*/
						case 0: /* ADDSTYLE*/	es|=tmpstl;	break;
						case 1: /* DELSTYLE*/	es=((es|tmpstl)^tmpstl);break;
						}
					}
					else
					for(i=0;i<N_TREECTRL_EX_STYLES;i++)
						if (strstr(pos,aTreeCtrlExStyleName[i])!=NULL)
						{
							InvFlg++;
							switch(propnum)
							{
							case 2: /* STYLE*/
							case 0: /* ADDSTYLE*/	es|=aTreeCtrlExStyleUINT[i];	break;
							case 1: /* DELSTYLE*/	es=((es|aTreeCtrlExStyleUINT[i])^aTreeCtrlExStyleUINT[i]);break;
							}
						}

					SetExtendedStyle(es);

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

LRESULT GPTree::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDragLeave","");
		if (m_ClearDropHilight)
		{
			SelectDropTarget(NULL);
			//Invalidate();
		}
		break;
	case GPM_DRAGMOUSEMOVE:
		OnMouseDragMove((PGPDRAGDROPSTRUCT)wParam,(LPPOINT)lParam);
		break;
	case GPM_DRAGMOUSEHOVER:
		OnDragMouseHover();
		break;
	case GPM_DROPITEMS:
		OnDragLButtonUp((PGPDRAGDROPSTRUCT)wParam,(LPPOINT)lParam);
		if (m_ClearDropHilight)
		{
			SelectDropTarget(NULL);
			//Invalidate();
		}
		break;
	}

	LRESULT lpr;
	if (message==WM_SETCURSOR && GPC.m_bWaitCursor) lpr=FALSE;
	else lpr=CTreeCtrl::WindowProc(message, wParam, lParam);

	return lpr;
}

// Возвращает строку описывающую элемент дерева
BOOL GPTree::ItemString(HTREEITEM iIt, char *oStr, char iDelimeter)
{
	int IdParent=-1,IdItem=0xFFFFFFFFL;

	if (oStr!=NULL && iIt!=NULL)
	{
		TVITEMEX curItem={0};
		char state[150];*state=0;
		char str[1500];*str=0;
		IdItem=ItemIdArray.GetIdByVal(iIt);

		curItem.mask=GPTree::maskTVIF;
		curItem.stateMask=GPTree::maskTVIS;
		curItem.cchTextMax=1490;
		curItem.pszText=str;
		curItem.hItem= iIt;

		SendMessage(TVM_GETITEM,0,(LPARAM)&curItem);

		iIt=GetParentItem(iIt);

		if (iIt!=0) IdParent=ItemIdArray.GetIdByVal(iIt);

		int i;
		for(i=0;i<GPTree::nTVIS;i++)
			if ((curItem.state&GPTree::TVISUINT[i])==GPTree::TVISUINT[i]) 		strcat(state,GPTree::TVISName[i]);

		sprintf(oStr,"%d%c%d%c%ld%c%d%c%d%c%d%c%s%c%s%c%d",
			IdItem,	iDelimeter,
			IdParent,iDelimeter,
			curItem.lParam,	iDelimeter,
			curItem.iImage,	iDelimeter,
			curItem.iSelectedImage,	iDelimeter,
			curItem.cChildren,	iDelimeter,
			state,	iDelimeter,
			curItem.pszText,iDelimeter,
			curItem.iIntegral
			);

	}
	return IdItem!=0xFFFFFFFFL;
}

// Возвращает строку описывающую элемент дерева
BOOL GPTree::ItemString(HTREEITEM iIt, char *oStr, char iDelimeter, const DWORD *iFields)
{
	int IdParent=-1,IdItem=0xFFFFFFFFL;

	if (iFields==NULL || *iFields==0)
	{
		if (ItemString(iIt, oStr, iDelimeter)) IdItem=0;
	}
	else
	{
		if (oStr!=NULL && iIt!=NULL)
		{
			TVITEMEX curItem={0};
			char state[150];*state=0;
			char str[1500];*str=0;
			IdItem=ItemIdArray.GetIdByVal(iIt);

			curItem.mask=GPTree::maskTVIF;
			curItem.stateMask=GPTree::maskTVIS;
			curItem.cchTextMax=1490;
			curItem.pszText=str;
			curItem.hItem= iIt;

			SendMessage(TVM_GETITEM,0,(LPARAM)&curItem);

			iIt=GetParentItem(iIt);

			if (iIt!=0) IdParent=ItemIdArray.GetIdByVal(iIt);
			int i=0;

			while(*iFields)
			{
				if (i++) {*(oStr++)=iDelimeter;*oStr=0;}
				switch(*iFields)
				{
				case TVIF_HANDLE:			oStr+=sprintf(oStr,"%d",IdItem);break;
				case TVIF_IMAGE:			oStr+=sprintf(oStr,"%d",curItem.iImage);break;
				case TVIF_PARAM:			oStr+=sprintf(oStr,"%d",curItem.lParam);break;
				case TVIF_SELECTEDIMAGE:	oStr+=sprintf(oStr,"%d",curItem.iSelectedImage);break;
				case TVIF_STATE:
					{
						int i333;
						for(i333=0;i333<GPTree::nTVIS;i333++)
							if ((curItem.state&GPTree::TVISUINT[i333])==GPTree::TVISUINT[i333])
							{
								strcpy(oStr,GPTree::TVISName[i333]);
								oStr+=(int)strlen(oStr);
							}
					}
					break;
				case TVIF_TEXT:				oStr+=sprintf(oStr,"%s",curItem.pszText);break;
				case TVIF_CHILDREN:			oStr+=sprintf(oStr,"%d",curItem.cChildren);break;
				case TVIF_INTEGRAL:			oStr+=sprintf(oStr,"%d",curItem.iIntegral);break;
				case TVIF_PARENT:			oStr+=sprintf(oStr,"%d",IdParent);break;
				}
				iFields++;
			}
		}
	}

	return IdItem!=0xFFFFFFFFL;
}

void GPTree::OnClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL)
	{
		if (m_HelperMode)
		{
			char tmps[500];
			*tmps=0;
			if ((GetAsyncKeyState(VK_MENU)&0xFF00)!=0) strcat(tmps,"MOD_ALT|");
			if ((GetAsyncKeyState(VK_SHIFT)&0xFF00)!=0) strcat(tmps,"MOD_SHIFT|");
			if ((GetAsyncKeyState(VK_CONTROL)&0xFF00)!=0) strcat(tmps,"MOD_CONTROL|");
			if ((GetAsyncKeyState(VK_RWIN)&0xFF00)!=0) strcat(tmps,"VK_RWIN|");
			if ((GetAsyncKeyState(VK_LWIN)&0xFF00)!=0) strcat(tmps,"VK_LWIN|");
			if ((GetAsyncKeyState(VK_RMENU)&0xFF00)!=0) strcat(tmps,"VK_RMENU|");
			if ((GetAsyncKeyState(VK_LMENU)&0xFF00)!=0) strcat(tmps,"VK_LMENU|");

			strcat(tmps,"OnClick\x7F");
			HTREEITEM hti=GetSelectedItem();
			if (hti)
			{
				int iId=ItemIdArray.GetIdByVal(hti);
				sprintf(tmps+(int)strlen(tmps),"%d\x7F%d\x7F%s",iId,ItemHasChildren(hti),(const char *)GetItemText(hti));
			}
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnHelper",tmps);
		}

		HTREEITEM tmpHTree;
		char txt[1150];*txt=0;
		if ((tmpHTree=GetSelectedItem())!=NULL)
		{
			int iId=ItemIdArray.GetIdByVal(tmpHTree);
			sprintf(txt,"%d\x7F%s",iId,(const char *)GetItemText(tmpHTree));
		}

		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClick",txt);
	}
	*pResult = 0;
}

void GPTree::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL)
	{
		if (m_HelperMode)
		{
			char tmps[500];
			*tmps=0;
			if ((GetAsyncKeyState(VK_MENU)&0xFF00)!=0) strcat(tmps,"MOD_ALT|");
			if ((GetAsyncKeyState(VK_SHIFT)&0xFF00)!=0) strcat(tmps,"MOD_SHIFT|");
			if ((GetAsyncKeyState(VK_CONTROL)&0xFF00)!=0) strcat(tmps,"MOD_CONTROL|");
			if ((GetAsyncKeyState(VK_RWIN)&0xFF00)!=0) strcat(tmps,"VK_RWIN|");
			if ((GetAsyncKeyState(VK_LWIN)&0xFF00)!=0) strcat(tmps,"VK_LWIN|");
			if ((GetAsyncKeyState(VK_RMENU)&0xFF00)!=0) strcat(tmps,"VK_RMENU|");
			if ((GetAsyncKeyState(VK_LMENU)&0xFF00)!=0) strcat(tmps,"VK_LMENU|");

			strcat(tmps,"OnDblclk\x7F");
			HTREEITEM hti=GetSelectedItem();
			if (hti)
			{
				int iId=ItemIdArray.GetIdByVal(hti);
				sprintf(tmps+(int)strlen(tmps),"%d\x7F%d\x7F%s",iId,ItemHasChildren(hti),(const char *)GetItemText(hti));
			}
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnHelper",tmps);
		}

		HTREEITEM tmpHTree;
		char txt[1150];*txt=0;
		if ((tmpHTree=GetSelectedItem())!=NULL)
		{
			int iId=ItemIdArray.GetIdByVal(tmpHTree);
			sprintf(txt,"%d\x7F%s",iId,(const char *)GetItemText(tmpHTree));
		}
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDblclk",txt);
	}
	*pResult = 0;
}

void GPTree::OnKillfocus(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNotifyKillfocus","");
	*pResult = 0;
}

void GPTree::OnOutofmemory(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnOutofmemory","");
	*pResult = 0;
}

void GPTree::OnRclick(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL)
	{
		HTREEITEM tmpHTree;
		char txt[150];*txt=0;

		if ((tmpHTree=GetDropHilightItem())!=NULL ||(tmpHTree=GetSelectedItem())!=NULL)
			sprintf(txt,"%d",ItemIdArray.GetIdByVal(tmpHTree));

		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnRclick",txt);
	}
	*pResult = 0;
}

void GPTree::OnRdblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL)
	{
		HTREEITEM tmpHTree;
		char txt[150];*txt=0;

		if ((tmpHTree=GetDropHilightItem())!=NULL ||(tmpHTree=GetSelectedItem())!=NULL)
			sprintf(txt,"%d",ItemIdArray.GetIdByVal(tmpHTree));

		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnRdblclk",txt);
	}
	*pResult = 0;
}

void GPTree::OnReturn(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL)
	{
		HTREEITEM tmpHTree;
		char txt[150];*txt=0;
		if ((tmpHTree=GetSelectedItem())!=NULL)
			sprintf(txt,"%d",ItemIdArray.GetIdByVal(tmpHTree));

		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnReturn",txt);
	}
}

void GPTree::OnSetfocus(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNotifySetfocus","");
	*pResult = 0;
}

void GPTree::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView =(NM_TREEVIEW*)pNMHDR;
	if (referGPU!=NULL)
	{
		char txt[150];
		sprintf(txt,"%d\x7F%d\x7F%d",ItemIdArray.GetIdByVal(pNMTreeView->itemNew.hItem),pNMTreeView->ptDrag.x,pNMTreeView->ptDrag.y);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnBegindrag",txt);
	}

	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	if (m_bDragROOT || GetParentItem(hItem) != NULL)
	{
		SelectItem(hItem);
		GPC.m_DragDrop.pImageList = CreateDragImage(hItem);

		if (GPC.m_DragDrop.pImageList != NULL)
		{
			CRect rect;
			GetItemRect(hItem, rect, TRUE);
			CPoint point(pNMTreeView->ptDrag.x, pNMTreeView->ptDrag.y);
			CPoint hotSpot = point;
			hotSpot.x -= rect.left;
			hotSpot.y -= rect.top;
			CPoint client(0, 0);
			ClientToScreen(&client);
			GetWindowRect(rect);
			point.x += client.x - rect.left;
			point.y += client.y - rect.top;
			GPC.m_DragDrop.DragName=referGPU[UnitId&0xFFFF]?referGPU[UnitId&0xFFFF]->m_DragName:"";
			GPC.m_DragDrop.IdScr=(UnitId&IS_DLG_UNIT)==0?(UnitId/0x10000)&0xFF:0xFFFFFFFF;
			GPC.m_DragDrop.IdDlg=(UnitId&IS_DLG_UNIT)!=0?(UnitId/0x10000)&0xFF:0xFFFFFFFF;
			GPC.m_DragDrop.DlgScrName=referGPU[0]->m_ObjName;
			GPC.m_DragDrop.ObjName=referGPU[UnitId&0xFFFF]->m_ObjName;
			GPC.m_DragDrop.IdObj=UnitId&0xFFFF;
			GPC.m_DragDrop.MessageSting.Format("%d\x7F%s",ItemIdArray.GetIdByVal(hItem),(LPCSTR)GetItemText(hItem));
			GPC.m_DragDrop.hWndDrag=m_hWnd;
			GPC.m_DragDrop.hWndLast=NULL;


			// Capture the mouse and begin dragging.
			SetCapture();
			GPC.m_DragDrop.pImageList->BeginDrag(0, hotSpot);
			GPC.m_DragDrop.pImageList->DragEnter(this, point);
			m_hDragItem = hItem;
			m_bDragging = TRUE;
		}
	}
	*pResult = 0;
}

void GPTree::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult)
{
	TV_DISPINFO* pTVDispInfo =(TV_DISPINFO*)pNMHDR;
	if (referGPU!=NULL)
	{
		CString tmps;
		if (pTVDispInfo)
		{
			tmps.Format("%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%s",
				ItemIdArray.GetIdByVal(pTVDispInfo->item.hItem),
				ItemIdArray.GetIdByVal(GetParentItem(pTVDispInfo->item.hItem)),
				pTVDispInfo->item.iImage,
				pTVDispInfo->item.iSelectedImage,
				pTVDispInfo->item.cChildren,
				(DWORD)pTVDispInfo->item.lParam,
				pTVDispInfo->item.pszText
				);
		}
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnBeginlabeledit",tmps);
	}
	*pResult = 0;
}

void GPTree::OnBeginrdrag(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView =(NM_TREEVIEW*)pNMHDR;
	if (referGPU!=NULL)
	{
		char txt[150];
		sprintf(txt,"%d\x7F%d\x7F%d",ItemIdArray.GetIdByVal(pNMTreeView->itemNew.hItem),pNMTreeView->ptDrag.x,pNMTreeView->ptDrag.y);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnBeginrdrag",txt);
	}
	*pResult = 0;
}

void GPTree::OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView =(NM_TREEVIEW*)pNMHDR;
	if (referGPU!=NULL && ItemIdArray.GetCount())
	{
		char txt[150];
		UINT idI=ItemIdArray.GetIdByVal(pNMTreeView->itemOld.hItem);
		sprintf(txt,"%d",idI);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDeleteitem",txt);
		ItemIdArray.RemoveItem(idI);
	}
	else 
	*pResult = 0;
}

void GPTree::OnSingleExpand(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView =(NM_TREEVIEW*)pNMHDR;
	if (referGPU!=NULL)
	{
		char txt[150];
		UINT idI=ItemIdArray.GetIdByVal(pNMTreeView->itemOld.hItem);
		UINT idIn=ItemIdArray.GetIdByVal(pNMTreeView->itemNew.hItem);
		sprintf(txt,"%d\x7F%d",idI,idIn);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSingleExpand",txt);
	}
	*pResult = 0;
}

void GPTree::OnGetInfotip(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMTVGETINFOTIP* pNMTreeView =(NMTVGETINFOTIP*)pNMHDR;
	if (referGPU!=NULL)
	{
		char txt[1150];
		UINT idI=ItemIdArray.GetIdByVal(pNMTreeView->hItem);
		sprintf(txt,"%d\x7F%d\x7F%s",idI,pNMTreeView->lParam,pNMTreeView->pszText);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnGetInfotip",txt);
	}
	*pResult = 0;
}

void GPTree::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult)
{
	TV_DISPINFO* pTVDispInfo =(TV_DISPINFO*)pNMHDR;
	if (referGPU!=NULL)
	{
		CString tmps;
		if (pTVDispInfo && pTVDispInfo->item.pszText)
		{
			tmps.Format("%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%s",
				ItemIdArray.GetIdByVal(pTVDispInfo->item.hItem),
				ItemIdArray.GetIdByVal(GetParentItem(pTVDispInfo->item.hItem)),
				pTVDispInfo->item.iImage,
				pTVDispInfo->item.iSelectedImage,
				pTVDispInfo->item.cChildren,
				(DWORD)pTVDispInfo->item.lParam,
				pTVDispInfo->item.pszText
				);
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnEndlabeledit",tmps);
		}
		else
		{
			if (pTVDispInfo)
			{
				tmps.Format("%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F",
					ItemIdArray.GetIdByVal(pTVDispInfo->item.hItem),
					ItemIdArray.GetIdByVal(GetParentItem(pTVDispInfo->item.hItem)),
					0,
					0,
					0,
					0
					);
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnCancellabeledit","");
			}
			else
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnEndlabeledit","");
		}
	}
	*pResult = 0;
}

void GPTree::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	TV_DISPINFO* pTVDispInfo =(TV_DISPINFO*)pNMHDR;
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnGetdispinfo","");
	*pResult = 0;
}

void GPTree::OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView =(NM_TREEVIEW*)pNMHDR;
	if (referGPU!=NULL)
	{
		char style[150];*style=0;
		char action[150];*action=0;
		int i;

		for(i=0;i<GPTree::nTVIS;i++)
			if ((pNMTreeView->itemNew.state&GPTree::TVISUINT[i])==GPTree::TVISUINT[i])
				strcat(style,GPTree::TVISName[i]);

		for(i=0;i<GPTree::nTVE;i++)
			if ((pNMTreeView->action&GPTree::TVEUINT[i])==GPTree::TVEUINT[i])
				strcat(action,GPTree::TVEName[i]);

		char txt[150];
		sprintf(txt,"%d\x7F%s\x7F%s",ItemIdArray.GetIdByVal(pNMTreeView->itemNew.hItem),style,action);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnItemexpanded",txt);
	}
	*pResult = 0;
}

void GPTree::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView =(NM_TREEVIEW*)pNMHDR;
	if (referGPU!=NULL)
	{
		char style[150];*style=0;
		char action[150];*action=0;
		int i;

		for(i=0;i<GPTree::nTVIS;i++)
			if ((pNMTreeView->itemNew.state&GPTree::TVISUINT[i])==GPTree::TVISUINT[i])
				strcat(style,GPTree::TVISName[i]);

		for(i=0;i<GPTree::nTVE;i++)
			if ((pNMTreeView->action&GPTree::TVEUINT[i])==GPTree::TVEUINT[i])
				strcat(action,GPTree::TVEName[i]);

		char txt[150];
		sprintf(txt,"%d\x7F%s\x7F%s",ItemIdArray.GetIdByVal(pNMTreeView->itemNew.hItem),style,action);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnItemexpanding",txt);
	}
	*pResult = 0;
}

void GPTree::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult)
{

	TV_KEYDOWN* pTVKeyDown =(TV_KEYDOWN*)pNMHDR;
	if (referGPU!=NULL)
	{
		const char *action="";
		int i;
		for(i=0;i<GP_N_TYPE_HOTKEY;i++)
			if (GP_HotKey::aVKUINT[i]==pTVKeyDown->wVKey){action=GP_HotKey::aVKName[i];break;}

		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnKeydown",action);
	}
	*pResult = 0;
}

void GPTree::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView =(NM_TREEVIEW*)pNMHDR;
	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)
	{
		if (referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnSelchanged"))
		{
			char txt[150];
			sprintf(txt,"%d\x7F%d\x7F%s",
				ItemIdArray.GetIdByVal(pNMTreeView->itemOld.hItem),
				ItemIdArray.GetIdByVal(pNMTreeView->itemNew.hItem),
				pNMTreeView->action==TVC_BYKEYBOARD?"_BYKEYBOARD":pNMTreeView->action==TVC_BYMOUSE?"_BYMOUSE":"_UNKNOWN"
				);
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSelchanged",txt);
		}
		if (referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnSelchangedEx"))
		{
			char *OldStr=new char [4000];
			char *NewStr=OldStr+1000;
			char *txt=OldStr+2000;
			*OldStr=*txt=*NewStr=0;
			DWORD flds[]={TVIF_HANDLE,TVIF_IMAGE,TVIF_SELECTEDIMAGE,TVIF_PARAM,TVIF_CHILDREN,TVIF_PARENT,TVIF_INTEGRAL,TVIF_TEXT,0,0,};

			ItemString(pNMTreeView->itemOld.hItem,OldStr,0x7,flds);
			ItemString(pNMTreeView->itemNew.hItem,NewStr,0x7,flds);
			sprintf(txt,"%d\x7F%d\x7F%s\x7F%s\x7F%s",
				ItemIdArray.GetIdByVal(pNMTreeView->itemOld.hItem),
				ItemIdArray.GetIdByVal(pNMTreeView->itemNew.hItem),
				pNMTreeView->action==TVC_BYKEYBOARD?"_BYKEYBOARD":pNMTreeView->action==TVC_BYMOUSE?"_BYMOUSE":"_UNKNOWN",
				OldStr,
				NewStr
				);
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSelchangedEx",txt);
			delete[] OldStr;
		}
		if (referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
			DoMethod("UpdateGroup",NULL);
	}

	*pResult = 0;
}

void GPTree::OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView =(NM_TREEVIEW*)pNMHDR;
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG)
	{
		if (referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnSelchanging"))
		{
			char txt[150];
			sprintf(txt,"%d\x7F%d\x7F%s",
				ItemIdArray.GetIdByVal(pNMTreeView->itemOld.hItem),
				ItemIdArray.GetIdByVal(pNMTreeView->itemNew.hItem),
				pNMTreeView->action==TVC_BYKEYBOARD?"_BYKEYBOARD":pNMTreeView->action==TVC_BYMOUSE?"_BYMOUSE":"_UNKNOWN"
				);
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSelchanging",txt);
		}
		if (referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnSelchangingEx"))
		{
			char *OldStr=new char [4000];
			char *NewStr=OldStr+1000;
			char *txt=OldStr+2000;
			*OldStr=*txt=*NewStr=0;
			DWORD flds[]={TVIF_HANDLE,TVIF_IMAGE,TVIF_SELECTEDIMAGE,TVIF_PARAM,TVIF_CHILDREN,TVIF_PARENT,TVIF_INTEGRAL,TVIF_TEXT,0,0,};

			ItemString(pNMTreeView->itemOld.hItem,OldStr,0x7,flds);
			ItemString(pNMTreeView->itemNew.hItem,NewStr,0x7,flds);
			sprintf(txt,"%d\x7F%d\x7F%s\x7F%s\x7F%s",
				ItemIdArray.GetIdByVal(pNMTreeView->itemOld.hItem),
				ItemIdArray.GetIdByVal(pNMTreeView->itemNew.hItem),
				pNMTreeView->action==TVC_BYKEYBOARD?"_BYKEYBOARD":pNMTreeView->action==TVC_BYMOUSE?"_BYMOUSE":"_UNKNOWN",
				OldStr,
				NewStr
				);
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSelchangingEx",txt);
			delete[] OldStr;
		}
	}
	*pResult = 0;
}

void GPTree::OnSetdispinfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	TV_DISPINFO* pTVDispInfo =(TV_DISPINFO*)pNMHDR;
	if (referGPU!=NULL)
	{
		char txt[150];
		sprintf(txt,"%d",ItemIdArray.GetIdByVal(pTVDispInfo->item.hItem));
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSetdispinfo",txt);
	}
	*pResult = 0;
}

void GPTree::ParentNotify(UINT message, LPARAM lParam)
{
	char txt[100];
	if (message==WM_CREATE || message==WM_DESTROY)
	{
		ItemIdArray.ResetArray();
		sprintf(txt,"%d\x7F%d\x7F%X",message/0x10000,(message&0xFFFF),lParam/0x10000);
	}
	else
		sprintf(txt,"%d\x7F%d\x7F%d\x7F%d",message/0x10000,(message&0xFFFF),lParam/0x10000,(lParam&0xFFFF));
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"ParentNotify",txt);
}

BOOL GPTree::PreTranslateMessage(MSG* pMsg)
{
	UINT ret;
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		referGPU[UnitId&0xFFFF]->m_CurPreMessage=pMsg;
		if (!referGPU[UnitId&0xFFFF]->DefPreTranslateMessage(pMsg)) return 0;
		if (referGPU[UnitId&0xFFFF]->GPMSG)
		{
			if (m_HelperMode)
			{
				switch(pMsg->message)
				{
				case WM_KEYDOWN:
					{
						char tmps[500];
						HTREEITEM hti=(HTREEITEM)1;
						*tmps=0;
						if ((GetAsyncKeyState(VK_MENU)&0xFF00)!=0) strcat(tmps,"MOD_ALT|");
						if ((GetAsyncKeyState(VK_SHIFT)&0xFF00)!=0) strcat(tmps,"MOD_SHIFT|");
						if ((GetAsyncKeyState(VK_CONTROL)&0xFF00)!=0) strcat(tmps,"MOD_CONTROL|");
						if ((GetAsyncKeyState(VK_RWIN)&0xFF00)!=0) strcat(tmps,"VK_RWIN|");
						if ((GetAsyncKeyState(VK_LWIN)&0xFF00)!=0) strcat(tmps,"VK_LWIN|");
						if ((GetAsyncKeyState(VK_RMENU)&0xFF00)!=0) strcat(tmps,"VK_RMENU|");
						if ((GetAsyncKeyState(VK_LMENU)&0xFF00)!=0) strcat(tmps,"VK_LMENU|");

						if (pMsg->wParam==VK_RETURN) strcat(tmps,"VK_RETURN|");
							else 
						if (pMsg->wParam==VK_ESCAPE) strcat(tmps,"VK_ESCAPE|");
							else
						if (pMsg->wParam==VK_CANCEL) strcat(tmps,"VK_CANCEL|");
							else
						if (pMsg->wParam==VK_BACK) strcat(tmps,"VK_BACK|");
							else
						if (pMsg->wParam==VK_TAB) strcat(tmps,"VK_TAB|");
							else
						if (pMsg->wParam==VK_CLEAR) strcat(tmps,"VK_CLEAR|");
							else
						if (pMsg->wParam==VK_SPACE) strcat(tmps,"VK_SPACE|");
							else
						if (pMsg->wParam==VK_LEFT) strcat(tmps,"VK_LEFT|");
							else
						if (pMsg->wParam==VK_RIGHT) strcat(tmps,"VK_RIGHT|");
							else hti=0;
						if (hti)
						{
							strcat(tmps,"\x7F");
							hti=GetSelectedItem();
							if (hti)
							{
								int iId=ItemIdArray.GetIdByVal(hti);
								sprintf(tmps+(int)strlen(tmps),"%d\x7F%d\x7F%s",iId,ItemHasChildren(hti),(const char *)GetItemText(hti));
							}
							referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnHelper",tmps);
						}
					}
					break;
				}
			}
		}

		if (pMsg->message!=WM_KEYDOWN || pMsg->wParam==VK_RETURN || pMsg->wParam==VK_TAB || pMsg->wParam==VK_CANCEL || pMsg->wParam==VK_ESCAPE || pMsg->wParam==VK_HELP)
		{
			if ((ret=referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjMessage(m_hWnd, UnitId, pMsg->message, pMsg->wParam, pMsg->lParam))>0) return ret;
			if (pMsg->message==WM_KEYDOWN && referGPU!=NULL && referGPU[UnitId&0xFFFF]->UnitHotkey && this->m_hWnd!=NULL && IsWindowEnabled()==TRUE && IsWindowVisible()==TRUE)
					if ((ret=referGPU[UnitId&0xFFFF]->UnitHotkey->SendHotkeyMessage(pMsg->message, pMsg->wParam,pMsg->lParam))>0) return ret;
		}
	}
	return CTreeCtrl::PreTranslateMessage(pMsg);
}

void GPTree::OnClose()
{
	if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClose","");
//	CTreeCtrl::OnClose();
}

void GPTree::OnSizing(UINT fwSide, LPRECT pRect)
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

	if (EnableSz) CTreeCtrl::OnSizing(fwSide, pRect);

	GetParent()->SendMessage(GPN_UPDATESIZE);

}

void GPTree::OnTimer(UINT nIDEvent)
{
	if (nIDEvent==DRAG_TIMER_ID)
	{
		DWORD dwPos = ::GetMessagePos();
		POINT tmpPo;
		tmpPo.x=LOWORD(dwPos);
		tmpPo.y=HIWORD(dwPos);
		HWND tmpHWND=::WindowFromPoint(tmpPo);
		if (tmpHWND)
			::SendMessage(tmpHWND,GPM_DRAGMOUSEHOVER,(WPARAM)&GPC.m_DragDrop,(LPARAM)&tmpPo);
	}

	CTreeCtrl::OnTimer(nIDEvent);
}

void GPTree::OnMouseMove(UINT nFlags, CPoint point)
{
	CTreeCtrl::OnMouseMove(nFlags, point);

	if (m_bDragging && GPC.m_DragDrop.pImageList != NULL)
	{
		POINT tmpPo=point;
		ClientToScreen(&tmpPo);
		HWND tmpHWND=::WindowFromPoint(tmpPo);
		if (GPC.m_DragDrop.hWndLast!=tmpHWND && GPC.m_DragDrop.hWndLast)
			::SendMessage(GPC.m_DragDrop.hWndLast,GPM_DRAGMOUSELEAVE,0,0);
		if (tmpHWND)
			::SendMessage(tmpHWND,GPM_DRAGMOUSEMOVE,(WPARAM)&GPC.m_DragDrop,(LPARAM)&tmpPo);
		GPC.m_DragDrop.hWndLast=tmpHWND;
	}
}

void GPTree::OnLButtonUp(UINT nFlags, CPoint point)
{
	CTreeCtrl::OnLButtonUp(nFlags, point);

	if (m_bDragging && GPC.m_DragDrop.pImageList != NULL)
	{
		// Stop the scroll timer if it's running.
		KillTimer(DRAG_TIMER_ID);

		// Terminate the dragging operation and release the mouse.
		GPC.m_DragDrop.pImageList->DragLeave(CWnd::FromHandle(GPC.m_DragDrop.hWndLast));
		GPC.m_DragDrop.pImageList->EndDrag();
		::ReleaseCapture();
		m_bDragging = FALSE;
		SelectDropTarget(NULL);

		// Delete the image list created by CreateDragImage.
		delete GPC.m_DragDrop.pImageList;
		GPC.m_DragDrop.pImageList = NULL;

		POINT tmpPo=point;
		ClientToScreen(&tmpPo);
		HWND tmpHWND=::WindowFromPoint(tmpPo);
		if (tmpHWND)
				::SendMessage(tmpHWND,GPM_DROPITEMS,(WPARAM)&GPC.m_DragDrop,(LPARAM)&tmpPo);
		m_hDragItem = NULL;
	}
}

void GPTree::OnDragMouseHover()
{
	while(referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(GPC.m_DragDrop.DragName)<0xFFFFFFFFL)
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

		referGPU[UnitId&0xFFFF]->SendDropHoverEvent("",&GPC.m_DragDrop,&point);

		// Scroll the window if the cursor is near the top or bottom.
		if (point.y >= 0 && point.y <= referGPU[UnitId&0xFFFF]->m_nScrollMargin)
		{
			HTREEITEM hFirstVisible = GetFirstVisibleItem();
			GPC.m_DragDrop.pImageList->DragShowNolock(FALSE);
			SendMessage(WM_VSCROLL, MAKEWPARAM(SB_LINEUP, 0), NULL);
			GPC.m_DragDrop.pImageList->DragShowNolock(TRUE);

			// Kill the timer if the window did not scroll, or redraw the drop target highlight if the window did scroll.
			if (GetFirstVisibleItem() == hFirstVisible)
				::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);
			else
			{
				HighlightDropTarget(&GPC.m_DragDrop, point);
				break;
			}
		}
		else
			if (point.y >= cy - referGPU[UnitId&0xFFFF]->m_nScrollMargin && point.y <= cy)
			{
				HTREEITEM hFirstVisible = GetFirstVisibleItem();
				GPC.m_DragDrop.pImageList->DragShowNolock(FALSE);
				SendMessage(WM_VSCROLL, MAKEWPARAM(SB_LINEDOWN, 0), NULL);
				GPC.m_DragDrop.pImageList->DragShowNolock(TRUE);

				// Kill the timer if the window did not scroll, or redraw the drop target highlight if the window did scroll.
				if (GetFirstVisibleItem() == hFirstVisible) ::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);
				else
				{
					HighlightDropTarget(&GPC.m_DragDrop, point);
					break;
				}
			}

		// If the cursor is hovering over a collapsed item, expand the tree.
		UINT nFlags;
		HTREEITEM hItem = HitTest(point, &nFlags);

		if (hItem != NULL && ItemHasChildren(hItem) && !IsItemExpanded(hItem))
		{
			GPC.m_DragDrop.pImageList->DragShowNolock(FALSE);
			Expand(hItem, TVE_EXPAND);
			GPC.m_DragDrop.pImageList->DragShowNolock(TRUE);
			::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);
			break;
		}
		break;
	}
}

void GPTree::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	if (pDrDrStruct && pDrDrStruct->pImageList != NULL)
	{
		::ScreenToClient(m_hWnd,point);
		::KillTimer(pDrDrStruct->hWndDrag,DRAG_TIMER_ID);
		// Offset point
		if (referGPU && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->OffsetWndPoint(point);

		// Erase the old drag image and draw a new one.

		if (pDrDrStruct->hWndLast!=m_hWnd && pDrDrStruct->hWndLast)
		{
			pDrDrStruct->pImageList->DragLeave(CWnd::FromHandle(pDrDrStruct->hWndLast));
			pDrDrStruct->hWndLast=m_hWnd;
			pDrDrStruct->pImageList->DragEnter(this, CPoint(*point));
		}
		pDrDrStruct->pImageList->DragMove(CPoint(*point));

		HTREEITEM hItem=NULL;
		BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
		// Highlight the drop target if the cursor is over an item.
		if (mDrop)
			hItem = HighlightDropTarget(pDrDrStruct, CPoint(*point));
		// Modify the cursor to provide visual feedback to the user. Note: It's important to do this AFTER the call to DragMove.
		SelectDropTarget(hItem);
		if (hItem)
		{
			::SetCursor((HCURSOR) ::GetClassLong(m_hWnd, GCL_HCURSOR));
		}
		else
		{
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_NO));
		}


		referGPU[UnitId&0xFFFF]->SendDropMoveEvent("",pDrDrStruct,point);

		if (mDrop)
			::SetTimer(pDrDrStruct->hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nDelayInterval, NULL);
	}
}

void GPTree::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && referGPU)
	{
		// Get the HTREEITEM of the drop target and exit now if it's NULL.
		::ScreenToClient(m_hWnd,point);
		UINT nFlags;
		HTREEITEM hItem = HitTest(CPoint(*point), &nFlags);
		CString tmp;

		if (hItem != NULL)
			tmp.Format("%d\x7%s",ItemIdArray.GetIdByVal(hItem),(LPCSTR)GetItemText(hItem));
		else
			tmp="-1\x7";
		referGPU[UnitId&0xFFFF]->SendDropEvent(tmp,pDrDrStruct,point);
	}
}

BOOL GPTree::IsChildOf(HTREEITEM hItem1/*child*/, HTREEITEM hItem2/*parent*/)
{
	HTREEITEM hParent = hItem1;
	BOOL ret=FALSE;
	while((hParent = GetParentItem(hParent)) != NULL && !ret)
		ret=(hParent == hItem2);

	return ret;
}

void GPTree::MoveTree(HTREEITEM hDest, HTREEITEM hSrc)
{
	if (IsChildOf(hDest,hSrc)==FALSE)
	{
		CopyTree(hDest, hSrc,1000000000);
		DeleteItem(hSrc);
	}
}

void GPTree::CopyTree(HTREEITEM hDest, HTREEITEM hSrc, int iDelta)
{
	// Get the attributes of item to be copied.
	int nImage, nSelectedImage;
	GetItemImage(hSrc, nImage, nSelectedImage);
	CString string = GetItemText(hSrc);

	// Create an exact copy of the item at the destination.
	HTREEITEM hNewItem = InsertItem(string, nImage, nSelectedImage, hDest);

	if (hNewItem)
	{
		UINT IdS=ItemIdArray.GetIdByVal(hSrc);
		ItemIdArray[IdS+iDelta]=hSrc;
		ItemIdArray[IdS]=hNewItem;

		// If the item has subitems, copy them, too.
		if (ItemHasChildren(hSrc))
			CopyChildren(hNewItem, hSrc,iDelta);
	}
}

void GPTree::CopyChildren(HTREEITEM hDest, HTREEITEM hSrc)
{
	// Get the first subitem.
	HTREEITEM hItem = GetChildItem(hSrc);

	if (hItem != NULL)
	{
		// Create a copy of it at the destination.
		int nImage, nSelectedImage;
		GetItemImage(hItem, nImage, nSelectedImage);
		CString string = GetItemText(hItem);
		DWORD itemData=GetItemData(hItem);
		HTREEITEM hNewItem = InsertItem(string, nImage, nSelectedImage, hDest);
		if (hNewItem)
			SetItemData(hNewItem,itemData);
		// If the subitem has subitems, copy them, too.
		if (ItemHasChildren(hItem))
			CopyChildren(hNewItem, hItem);

		// Do the same for other subitems of hSrc.
		while((hItem = GetNextSiblingItem(hItem)) != NULL)
		{
			GetItemImage(hItem, nImage, nSelectedImage);
			string = GetItemText(hItem);
			itemData=GetItemData(hItem);
			hNewItem = InsertItem(string, nImage, nSelectedImage, hDest);
			if (hNewItem)
				SetItemData(hNewItem,itemData);
			if (ItemHasChildren(hItem))
				CopyChildren(hNewItem, hItem);
		}
	}
}

void GPTree::CopyChildren(HTREEITEM hDest, HTREEITEM hSrc, UINT nDelta)
{
	// Get the first subitem.
	HTREEITEM hItem = GetChildItem(hSrc);

	if (hItem != NULL)
	{
		HTREEITEM hNewItem;
		// Create a copy of it at the destination.
		int nImage, nSelectedImage;
		GetItemImage(hItem, nImage, nSelectedImage);
		CString string = GetItemText(hItem);
		DWORD itemData=GetItemData(hItem);
		UINT srcId=ItemIdArray.GetIdByVal(hItem);
		ItemIdArray[srcId+nDelta]=	hNewItem = InsertItem(string, nImage, nSelectedImage, hDest);
		if (hNewItem)
			SetItemData(hNewItem,itemData);
		// If the subitem has subitems, copy them, too.
		if (ItemHasChildren(hItem))
			CopyChildren(hNewItem, hItem,nDelta);

		// Do the same for other subitems of hSrc.
		while((hItem = GetNextSiblingItem(hItem)) != NULL)
		{
			GetItemImage(hItem, nImage, nSelectedImage);
			string = GetItemText(hItem);
			itemData=GetItemData(hItem);
			srcId=ItemIdArray.GetIdByVal(hItem);
			hNewItem = InsertItem(string, nImage, nSelectedImage, hDest);
			ItemIdArray[srcId+nDelta]=	hItem;
			ItemIdArray[srcId]=	hNewItem;
			if (hNewItem)
				SetItemData(hNewItem,itemData);
			if (ItemHasChildren(hItem))
				CopyChildren(hNewItem, hItem,nDelta);
		}
	}
}

BOOL GPTree::IsItemExpanded(HTREEITEM hItem)
{
	return GetItemState(hItem, TVIS_EXPANDED) & TVIS_EXPANDED;
}

HTREEITEM GPTree::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	// Find out which item(if any) the cursor is over.
	UINT nFlags;
	HTREEITEM hItem = HitTest(point, &nFlags);

	// Highlight the item, or unhighlight all items if the cursor isn't over an item.
	pDrDrStruct->pImageList->DragShowNolock(FALSE);
	SelectDropTarget(hItem);
//	if (hItem) Invalidate();

	pDrDrStruct->pImageList->DragShowNolock(TRUE);

	// Return the handle of the highlighted item.
	return hItem;
}

LRESULT GPTree::OnNcHitTest(CPoint point)
{
	LRESULT ret=CTreeCtrl::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

#include "GP_TermDoc.h"

void GPTree::OnKillFocus(CWnd* pNewWnd)
{
	CTreeCtrl::OnKillFocus(pNewWnd);
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

void GPTree::OnSetFocus(CWnd* pOldWnd)
{
	CTreeCtrl::OnSetFocus(pOldWnd);
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


void GPTree::OnSize(UINT nType, int cx, int cy)
{
	CTreeCtrl::OnSize(nType, cx, cy);

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
	}
}


void GPTree::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CTreeCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
	if (referGPU && referGPU[UnitId&0xFFFF]->m_SizerArray)	Invalidate();
}

void GPTree::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CTreeCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
	if (referGPU && referGPU[UnitId&0xFFFF]->m_SizerArray)	Invalidate();
}


const CString GPTree::StateToString(UINT iState)
{
	CString ret;
	UINT i;
	for(i=0;i<GPTree::nTVIS;i++)
		if ((iState&GPTree::TVISUINT[i])==GPTree::TVISUINT[i])
		{
			if (ret=="") ret=GPTree::TVISName[i];
			else {ret+="|";ret+=GPTree::TVISName[i];}
		}
	return ret;
}

UINT GPTree::StringToState(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<GPTree::nTVIS;i++)
			ret|=GPTree::TVISUINT[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<GPTree::nTVIS;i++)
			if (tmps.Find(GPTree::TVISName[i],0)>=0) ret|=GPTree::TVISUINT[i];
	}

	return ret;
}


UINT GPTree::GetChildList(HTREEITEM hParent, HTREEITEM *hTreeArray, UINT nLevels, HTREEITEM hTreeStop)
{
	UINT nChild=0;
	if (hParent && nLevels)
	{
		HTREEITEM hItem = GetChildItem(hParent);

		if (hItem!=NULL && hItem!=hTreeStop)
		{
			UINT i=0;
			do
			{
				if (hTreeArray) hTreeArray[nChild]=hItem;
				else			nChild+=GetChildList(hItem,NULL,nLevels-1,hTreeStop);

				nChild++;
			}
			while((hItem = GetNextSiblingItem(hItem)) && hItem!=hTreeStop && hItem);

			if (hTreeArray)
			{
				UINT nChildCur=nChild;
				for(i=0;i<nChildCur && hTreeStop!=hTreeArray[i];i++)
					if (ItemHasChildren(hTreeArray[i]))
						nChild+=GetChildList(hTreeArray[i],hTreeArray+nChild,nLevels-1,hTreeStop);
			}
		}
	}
	return nChild;
}


HBRUSH GPTree::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CTreeCtrl::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}

DWORD GPTree::GetExtendedStyle() 
{
	return SendMessage(TVM_GETEXTENDEDSTYLE,0,0);
}

DWORD GPTree::SetExtendedStyle(DWORD dwStyle) 
{
	SendMessage(TVM_SETEXTENDEDSTYLE,0xFFFFFFFF,dwStyle);
	return GetExtendedStyle();
}
