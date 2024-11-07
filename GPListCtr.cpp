// GPListCtr.cpp : implementation file
//

#include "stdafx.h"
#include "GP_term.h"
#include "GPListCtr.h"
#include "GP_TermView.h"
#include "GPHeader.h"
#include "GP_TermDoc.h"
#include "GPToolTipCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPListCtr
const UINT GPListCtr::uNMethods=196;
const char *GPListCtr::cArrMethods[]={
/*00*/	"GetBkColor","SetBkColor","GetItemCount","GetItem","SetItem",
/*05*/	"GetCallbackMask","SetCallbackMask","GetNextItem","GetFirstSelectedItemPosition","GetNextSelectedItem",
/*10*/	"GetItemBoundsRect","GetItemIconRect","GetItemLabelRect","SetItemPosition","GetItemPosition",
/*15*/	"GetStringWidth","GetEditControl","GetColumn","SetColumn","GetColumnWidth",
/*20*/	"SetColumnWidth","GetCheck","SetCheck","GetViewRect","GetTextColor",
/*25*/	"SetTextColor","GetTextBkColor","SetTextBkColor","GetTopIndex","GetCountPerPage",
/*30*/	"GetOrigin","GetItemState","SetItemState","GetItemText","SetItemText",
/*35*/	"SetItemCount","SetItemData","GetItemData","GetSelectedCount","SetColumnOrderArray",
/*40*/	"GetColumnOrderArray","SetIconSpacing","GetHeaderCtrl","GetHotCursor","SetHotCursor",
/*45*/	"GetSubItemRect","GetHotItem","SetHotItem","GetSelectionMark","SetSelectionMark",
/*50*/	"GetExtendedStyle","SetExtendedStyle","SubItemHitTest","GetWorkAreas","GetNumberOfWorkAreas",
/*55*/	"SetItemCountEx","SetWorkAreas","ApproximateViewRect","GetBkImage","SetBkImage",
/*60*/	"GetHoverTime","SetHoverTime","InsertItemEx","DeleteItem","DeleteAllItems",
/*65*/	"FindItem","SortItems","HitTest","EnsureVisible","Scroll",
/*70*/	"RedrawItems","Update","Arrange","EditLabel","InsertColumn",
/*75*/	"DeleteColumn","CreateDragImage","InsertItem","SetFilter","GetChecked",
/*80*/	"GetSelected","UpdateGroup","SetEditorPerColumn","SetEditorPerLine","SetEditorForItem",
/*85*/	"SetEditorForSubItem","SetEditOnOff","SetEditor","SetEditItem","GetEditItem",
/*90*/	"GetEditResult","SetAutoUpdate","SetDefEditor","GetDefEditor","GetListContents",
/*95*/	"ClearRegion","SaveListContents","SortItemsAsNum","SortItemsAsDate","GetImageList",
/*100*/	"SetImageList","FindEx","SaveListContentsH","SHImageList","SHItem",
/*105*/	"FindNoCaseEx","SelectAll","DeSelectAll","SelectionDelete","SelectionCheck",
/*110*/	"SelectionInvert","SelectionSetItem","SelectionSetItemText","SelectionSetItemState","SelectionDoMethod",
/*115*/	"SetSelection","SetEditPosParam","FillFromSpr","AddFromSpr","ReplaceFromSpr",
/*120*/	"DeleteAllColumns","SetHFilter","SetHFilters","SetAutoHFilter","GetAutoHFilter",
/*125*/	"DeleteHFilters","ClearHFilter","EditHFilter","GetHFilter","SetHeaderProperty",
/*130*/	"DoHeaderMethod","SetSortMark","SetItemTextReflect","GetEditStatus","InsertItems",
/*135*/	"NextCell","GetColumnCount","CancelEditLabel","EnableGroupView","GetGroupInfo",
/*140*/	"GetGroupMetrics","GetInsertMark","GetInsertMarkColor","GetInsertMarkRect","GetISearchString",
/*145*/	"GetItemSpacing","GetOutlineColor","GetSelectedColumn","GetTileInfo","GetTileViewInfo",
/*150*/	"GetUnicodeFormat","GetView","HasGroup","SetInsertMark","SetInsertMarkColor",
/*155*/	"SetOutlineColor","SetSelectedColumn","InsertGroup","InsertMarkHitTest","IsGroupViewEnabled",
/*160*/	"MapIdToIndex","MapIndexToId","MoveGroup","MoveItemToGroup","RemoveAllGroups",
/*165*/	"RemoveGroup","SetGroupInfo","SetGroupBorderClr","SetGroupBorderSize","SetGroupTextClr",
/*170*/	"SetInfoTip","SetItemPosition32","SetTileInfo","SetTileViewInfo","SetUnicodeFormat",
/*175*/	"SetView","SortGroupsAsNum","SortGroupsAsDate","SortGroups","InserItemInGroup",
/*180*/	"GetItemTextEx","SetCaseSensitive","GetCaseSensitive","SetAutoSort","GetAutoSort",
/*185*/	"SetCacheSize","SetCacheTimeout","GetCacheSize","GetCacheTimeout","SetPrereadCount",
/*190*/	"GetPrereadCount","SetBulkCount","GetBulkCount","ResetVirtualList","SetDefItemImage",
/*195*/	"GetDefItemImage","","","","",
/*200*/	"","","","","",

/*
SortItemsEx
GetToolTips
SetTileWidth
SetToolTips
*/
/*
#define LVM_SORTITEMSEX          (LVM_FIRST + 81)
#define LVM_GETTOOLTIPS       (LVM_FIRST + 78)
#define LVM_SETTILEWIDTH         (LVM_FIRST + 141)
#define LVM_SETTOOLTIPS       (LVM_FIRST + 74)
*/



	};
const char *GPListCtr::cArrMethodsParams[]={
/*00*/	"","r,g,b","","iItem,iSubItem,mask","iItem,iSubItem,cchTextMax,iImage,lParam,iIndent,iGroupId,cColumns,IdCol1,IdCol2...IdColN,mask,stateMask,state;Text",
/*05*/	"","mask","nItem,Flags","","",
/*10*/	"nItem","nItem","nItem","nItem,ptX,ptY","nItem",
/*15*/	"Text","","nColumn","nColumn,mask,fmt,cx,cchTextMax,iSubItem,iImage,iOrder,Text","-1 OR nColumn",
/*20*/	"Col1^Col2.... OR nColumn,Width","nItem","nItem,iCheck","","",
/*25*/	"r,g,b","","r,g,b","","",
/*30*/	"","nItem,Mask","nItem,State","nItem,nSubItem1,nSubItem2,....","nItem,nSubItem;Text^Text^Text^....",
/*35*/	"ItemCount","nItem,ItemData","nItem","","ColumnN,ColumnN2,....",
/*40*/	"","cx,cy","","","Not Present",
/*45*/	"iItem,iSubItem,nArea","","nItem","","nItem",
/*50*/	"","ExtendedStyles","ptX,ptY","nWorkAreas","",
/*55*/	"ItemCount,cflg","nWorkAreas,left^top^right^bottom,left^top^right^bottom,....","szcx,szcy,iCount","","Name;tile,ofX,ofY,ulFlags;",
/*60*/	"","HoverTime","iItem,iSubItem,cchTextMax,iImage,lParam,iIndent,iGroupId,cColumns,IdCol1,IdCol2...IdColN,mask,stateMask,state;Text","nItem","",
/*65*/	"nStart,lParam,ptX,ptY,vkDirection,uflags,Text","nColumn,vkDirection","ptX,ptY,cflg","nItem,bPartialOK","cx,cy",
/*70*/	"nFirst,nLast","nItem","cStyle","nItem","nColumn,mask,fmt,cx,cchTextMax,iSubItem,iImage,iOrder,,Text",
/*75*/	"nColumn","Not Present","iItem[,nImage][:Editor];Text","nColumn,Text","nColumns",
/*80*/	"nColumns","","nObj1^nObj1^nObj1^...","nObj1[nObj[nObj^nObj1[nObj[nObj^nObj1[nObj[nObj^..","nItem,nObj1[nObj1[nObj1[...",
/*85*/	"iItem,iSubItem,nObj","onoff,verhor,skip,forback,lcbreak,delnext","nObj1[nObj[nObj^nObj1[nObj[nObj^nObj1[nObj[nObj^..","iItem,iSubItem","",
/*90*/	"","bAutoUpdate","nObj","","Left,Top,Right,Bottom",
/*95*/	"Left,Top,Right,Bottom;repltext","DELIMETER,nFile,Left,Top,Right,Bottom;ColN,ColNN,....","nColumn,vkDirection","nColumn,vkDirection","ImageListType",
/*100*/	"ImageListName,Type","STR=;COL=;RET=;TEXT=;TEXT<;TEXT>;TEXT2=;TEXT2<;TEXT2>;NUM=;NUM<;NUM>;DATE=;DATE<;DATE>;ACTION=","DELIMETER,nFile,Left,Top,Right,Bottom;ColN,ColNN,....","ImageListName","position,cxy,height,iImage,fmt,mask;Text",
/*105*/	"STR=;COL=;RET=;TEXT=;TEXT<;TEXT>;TEXT2=;TEXT2<;TEXT2>;NUM=;NUM<;NUM>;DATE=;DATE<;DATE>;ACTION=","","","","nCheck",
/*110*/	"","cchTextMax,iImage,lParam,iIndent,iGroupId,cColumns,IdCol1,IdCol2...IdColN,mask,stateMask,state;Text","Text^Text^Text^....","State","Method Params",
/*115*/	"nItem1,NItem2,.. nItem-nItemN,...","SubItem1^SubItem2^SubItem3^...","SprName,nField1^nField2^... ,nCol1^nCol2^...","SprName,nField1^nField2^... ,nCol1^nCol2^...","StartItem,EndItem,SprName1,nCodeCol1,nReplCol1,nFindField1,nTextField1,Prefix1^SprName2,nCodeCol2,nReplCol2,nFindField2,nTextField2,Prefix1...",
/*120*/	"","nCol[,FilterText]","[FilterText1^FilterText2^...]","AutoHFilterOnOff","",
/*125*/	"","nItem","nItem","nColumn OR -1","Property",
/*130*/	"Method string","nColumn,iDirection","nItem,nSubItem;Text^Text^Text^....","","nItem,Text01]Text02]..]text0N^Text11]text12]...",
/*135*/	"KeyDown","","","bEnable","iGroup",
/*140*/	"iGroup","bAFTER","","","",
/*145*/	"","","","iItem","",
/*150*/	"","","idGroup","iItem,bAFTER","R,G,B",
/*155*/	"R,G,B","iCol","iItem,iGroup,state,TEXT","pox,poy,iItem,flag","",
/*160*/	"Id","Index","iGroupId,ToIndex","idItemFrom,idGroupTo","",
/*165*/	"iGroupId","iGroupId,state,uAlign,TEXT","IdGroup,RLeft,GLeft,BLeft,RTop,GTop,BTop,RRight,GRight,BRight,RBottom,GBottom,BBottom","IdGroup,Left,Top,Right,Bottom","IdGroup,RHeader,GHeader,BHeader,RFooter,GFooter,BFooter",
/*170*/	"iItem,iSubItem,Flags,TEXT","iItem,X,Y","iItem,cColumns,Index1,Index2,....","sizex,sizey,cLines,MrgnLeft,MrgnTop,MrgnRight,MrgnBottom,Flag","bFormat",
/*175*/	"bViewType","nColumn,vkDirection","nColumn,vkDirection","nColumn,vkDirection","iItem,IdGroup,Editor;Text",
/*180*/	"Item1,Item2,...ItemN","LVCS_SORT|LVCS_FILTER","","[0/1]","",
/*185*/	"nItems","Delay_ms","","","nPrereadCount",
/*190*/	"","nBulkCount","","","ImageNum",
/*195*/	"","","","","",
/*200*/	"","","","","",
	};

const UINT GPListCtr::uNGRAlign=6;
const char *GPListCtr::cArrGRAlign[6]={
	"F_CENTER","F_LEFT","F_RIGHT","H_CENTER","H_LEFT",
	"H_RIGHT",
	};
const UINT GPListCtr::uArrGRAlign[6]={
	LVGA_FOOTER_CENTER,LVGA_FOOTER_LEFT,LVGA_FOOTER_RIGHT,LVGA_HEADER_CENTER,LVGA_HEADER_LEFT,
	LVGA_HEADER_RIGHT,
	};

const UINT GPListCtr::uNLView=5;
const char *GPListCtr::cArrLView[5]={
	"LV_DETAILS","LV_ICON","LV_LIST","LV_SMALLICON","LV_TILE",
	};
const UINT GPListCtr::uArrLView[5]={
	LV_VIEW_DETAILS,LV_VIEW_ICON,LV_VIEW_LIST,LV_VIEW_SMALLICON,LV_VIEW_TILE,
	};

const UINT GPListCtr::uNIState=6;
const char *GPListCtr::cArrIState[6]={
	"LVIS_ACTIVATING","LVIS_CUT","LVIS_DROPHILITED","LVIS_FOCUSED","LVIS_SELECTED",
		"LVIS_GLOW",
	};
const UINT GPListCtr::uArrIState[6]={
		LVIS_ACTIVATING,LVIS_CUT,LVIS_DROPHILITED,LVIS_FOCUSED,LVIS_SELECTED,
		LVIS_GLOW,
	};

const UINT GPListCtr::uNIMask=9;
const char *GPListCtr::cArrIMask[9]={
		"LVIF_TEXT","LVIF_IMAGE","LVIF_INDENT","LVIF_NORECOMPUTE","LVIF_PARAM",
		"LVIF_STATE","LVIF_DI_SETITEM","LVIF_GROUPID","LVIF_COLUMNS",
	};
const UINT GPListCtr::uArrIMask[9]={
		LVIF_TEXT,LVIF_IMAGE,LVIF_INDENT,LVIF_NORECOMPUTE,LVIF_PARAM,
		LVIF_STATE,LVIF_DI_SETITEM,LVIF_GROUPID,LVIF_COLUMNS,
	};

const UINT GPListCtr::uNGrMask=6;
const char *GPListCtr::cArrGrMask[6]={
		"LVGF_ALIGN","LVGF_FOOTER","LVGF_GROUPID","LVGF_HEADER","LVGF_NONE",
		"LVGF_STATE",
	};
const UINT GPListCtr::uArrGrMask[6]={
		LVGF_ALIGN,LVGF_FOOTER,LVGF_GROUPID,LVGF_HEADER,LVGF_NONE,
		LVGF_STATE,
	};

const UINT GPListCtr::uNGrState=3;
const char *GPListCtr::cArrGrState[3]={
		"LVGS_COLLAPSED","LVGS_HIDDEN","LVGS_NORMAL",
	};
const UINT GPListCtr::uArrGrState[3]={
		LVGS_COLLAPSED,LVGS_HIDDEN,LVGS_NORMAL,
	};


char * stristr(const char *s1,const char *s2);

int CALLBACK GPListCtr::mCompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	GPTextArray *ar1=(GPTextArray *) lParam1;
	GPTextArray *ar2=(GPTextArray *) lParam2;
	int ret = 0;
	GPListCtr *ctrl=(GPListCtr *)lParamSort;
	if (ar1!=NULL && ar2!=NULL)
	{
		char *s1=(char *)ar1->GetItem(ctrl->SortColumnNumber);
		char *s2=(char *)ar2->GetItem(ctrl->SortColumnNumber);
		if (s1!=NULL && s2!=NULL)
		{
			if ((ctrl->m_CSFlag&0x1))
				ret=strcmp(s1,s2);
			else
				ret=_stricmp(s1,s2);

			if (ctrl->nFilterArrayCount>=0 && ctrl->FilterArray!=NULL)
			{
				char *fltitem,*sf1,*sf2,*res1,*res2;
				int ncoll;
				for(ncoll=0; ncoll<=ctrl->nFilterArrayCount;ncoll++)
					if ((fltitem=(char *)ctrl->FilterArray->GetItem(ncoll))!=NULL && *fltitem!=0)
					{
						sf1=(char *)ar1->GetItem(ncoll);
						sf2=(char *)ar2->GetItem(ncoll);
						if (sf1!=NULL && sf2!=NULL)
						{
							if ((ctrl->m_CSFlag&0x2))
							{
								res1=strstr(sf1,fltitem);
								res2=strstr(sf2,fltitem);
							}
							else
							{
								res1=stristr(sf1,fltitem);
								res2=stristr(sf2,fltitem);
							}

							if (res1!=NULL && res2==NULL)
							{
								ret=-1;
								if (ctrl->DESCENDSort) ret=1;
								break;
							}
							else
								if (res1==NULL && res2!=NULL) 
								{
									ret=1;
									if (ctrl->DESCENDSort) ret=-1;
									break;
								}
						}
					}
			}
		}
		else
		if (s1==NULL && s2!=NULL) ret=-1;
		else
		if (s1!=NULL && s2==NULL) ret=1;
	}
	else
	if (ar1==NULL && ar2!=NULL) ret=-1;
	else
	if (ar1!=NULL && ar2==NULL) ret=1;

	if (ctrl->DESCENDSort==TRUE) ret=-ret;

return ret;
}

int CALLBACK GPListCtr::mCompareFuncNum(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	GPTextArray *ar1=(GPTextArray *) lParam1;
	GPTextArray *ar2=(GPTextArray *) lParam2;
	int ret = 0;
	double d1,d2;
	GPListCtr *ctrl=(GPListCtr *)lParamSort;
	if (ar1!=NULL && ar2!=NULL)
	{
		char *s1=(char *)ar1->GetItem(ctrl->SortColumnNumber);
		char *s2=(char *)ar2->GetItem(ctrl->SortColumnNumber);
		if (s1!=NULL && s2!=NULL)
		{
			ret=_stricmp(s1,s2);
			if ((d1=atof(s1))>(d2=atof(s2))) ret=1;
			else if (d1<d2) ret=-1;
			if (ctrl->nFilterArrayCount>=0 && ctrl->FilterArray!=NULL)
			{
				char *fltitem,*sf1,*sf2,*res1,*res2;
				int ncoll;
				for(ncoll=0; ncoll<=ctrl->nFilterArrayCount;ncoll++)
					if ((fltitem=(char *)ctrl->FilterArray->GetItem(ncoll))!=NULL && *fltitem!=0)
					{
						sf1=(char *)ar1->GetItem(ncoll);
						sf2=(char *)ar2->GetItem(ncoll);

						if (sf1!=NULL && sf2!=NULL)
						{
							res1=strstr(sf1,fltitem);
							res2=strstr(sf2,fltitem);
							if (res1!=NULL && res2==NULL)
							{
								ret=-1;
								if (ctrl->DESCENDSort) ret=1;
								break;
							}
							else
								if (res1==NULL && res2!=NULL) 
								{
									ret=1;
									if (ctrl->DESCENDSort) ret=-1;
									break;
								}
						}
					}
			}
		}
		else
		if (s1==NULL && s2!=NULL) ret=-1;
		else
		if (s1!=NULL && s2==NULL) ret=1;
	}
	else
	if (ar1==NULL && ar2!=NULL) ret=-1;
	else
	if (ar1!=NULL && ar2==NULL) ret=1;

	if (ctrl->DESCENDSort==TRUE) ret=-ret;

return ret;
}

int CALLBACK GPListCtr::mCompareFuncDate(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	GPTextArray *ar1=(GPTextArray *) lParam1;
	GPTextArray *ar2=(GPTextArray *) lParam2;
	int ret = 0;
	GPListCtr *ctrl=(GPListCtr *)lParamSort;
	if (ar1!=NULL && ar2!=NULL)
	{
		char *s1=(char *)ar1->GetItem(ctrl->SortColumnNumber);
		char *s2=(char *)ar2->GetItem(ctrl->SortColumnNumber);
		if (s1!=NULL && s2!=NULL)
		{
			BOOL bpt1=FALSE,bpt2=FALSE;
			bpt1=ctrl->Cmpd1.ParseDateTime(s1);
			bpt2=ctrl->Cmpd2.ParseDateTime(s2);
			if (bpt1==FALSE && bpt2==FALSE) ret=_stricmp(s1,s2);
			else
			if (bpt1==FALSE) ret=1;
			else
			if (bpt2==FALSE) ret=-1;
			else
			{
				if (ctrl->Cmpd1>ctrl->Cmpd2) ret=1;
				else if (ctrl->Cmpd1<ctrl->Cmpd2) ret=-1;
			}
			if (ctrl->nFilterArrayCount>=0 && ctrl->FilterArray!=NULL)
			{
				char *fltitem,*sf1,*sf2,*res1,*res2;
				int ncoll;
				for(ncoll=0; ncoll<=ctrl->nFilterArrayCount;ncoll++)
					if ((fltitem=(char *)ctrl->FilterArray->GetItem(ncoll))!=NULL && *fltitem!=0)
					{
						sf1=(char *)ar1->GetItem(ncoll);
						sf2=(char *)ar2->GetItem(ncoll);
						if (sf1!=NULL && sf2!=NULL)
						{
							res1=strstr(sf1,fltitem);
							res2=strstr(sf2,fltitem);
							if (res1!=NULL && res2==NULL)
							{
								ret=-1;
								if (ctrl->DESCENDSort) ret=1;
								break;
							}
							else
								if (res1==NULL && res2!=NULL) 
								{
									ret=1;
									if (ctrl->DESCENDSort) ret=-1;
									break;
								}
						}
					}
			}
		}
		else
		if (s1==NULL && s2!=NULL) ret=-1;
		else
		if (s1!=NULL && s2==NULL) ret=1;
	}
	else
	if (ar1==NULL && ar2!=NULL) ret=-1;
	else
	if (ar1!=NULL && ar2==NULL) ret=1;

	if (ctrl->DESCENDSort==TRUE) ret=-ret;

return ret;
}

GPListCtr::GPListCtr(UINT iUnitId)
{
	m_DefItemImage=-1;
	m_dwVLDelay=200;
	m_VirtualData=NULL;
	m_LCDOflag=0;
	m_DOSubItem=0;
	m_CSFlag=0;
	m_AutoSortFlag=0;
	m_AutoHFilter=0;
	m_LastSort=0;
	limit_of_images=30;
	m_bDragging=FALSE;
	m_iDragItem=-1;
	m_LastDropTarget=-1;
	lastMask=lastFormat=lastState=lastStateMask=lastFlag=0;
	DefEditor=0;
	m_StaticCursor=NULL;
	m_EditInProgr=0;
	AutoUpdate=FALSE;
	MayBeChangeEdit=FALSE;
	hti.iItem=hti.iSubItem=-1;
	lasthti.iItem=lasthti.iSubItem=-2;
	UpdateHtiPosition();
	LastEditorID=0;
	EditorID=0;
	referGPU=NULL;
	UnitId=iUnitId;
	selposition = NULL;
	FilterArray = new GPTextArray;
	LastEditResult="";
	iArrPosExOut=new int [1000];
	int i;
	for(i=0;i<1000;i++)
		iArrPosExOut[i]=-1;
}

GPListCtr::~GPListCtr()
{
	if (FilterArray!=NULL) delete FilterArray;
	FilterArray=NULL;
	if (m_VirtualData!=NULL) delete m_VirtualData;
	m_VirtualData=NULL;
	delete m_StaticCursor;
	delete[] iArrPosExOut;
}

BEGIN_MESSAGE_MAP(GPListCtr, CListCtrl)
	//{{AFX_MSG_MAP(GPListCtr)
	ON_NOTIFY_REFLECT(NM_KILLFOCUS, OnKillfocus)
	ON_NOTIFY_REFLECT(NM_OUTOFMEMORY, OnOutofmemory)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(NM_RDBLCLK, OnRdblclk)
	ON_NOTIFY_REFLECT(NM_RETURN, OnReturn)
	ON_NOTIFY_REFLECT(NM_SETFOCUS, OnSetfocus)
	ON_NOTIFY_REFLECT(LVN_BEGINDRAG, OnBegindrag)
	ON_NOTIFY_REFLECT(LVN_BEGINLABELEDIT, OnBeginlabeledit)
	ON_NOTIFY_REFLECT(LVN_BEGINRDRAG, OnBeginrdrag)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_NOTIFY_REFLECT(LVN_DELETEALLITEMS, OnDeleteallitems)
	ON_NOTIFY_REFLECT(LVN_DELETEITEM, OnDeleteitem)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetdispinfo)
	ON_NOTIFY_REFLECT(LVN_INSERTITEM, OnInsertitem)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGING, OnItemchanging)
	ON_NOTIFY_REFLECT(LVN_KEYDOWN, OnKeydown)
	ON_NOTIFY_REFLECT(LVN_SETDISPINFO, OnSetdispinfo)
	ON_NOTIFY_REFLECT(LVN_ODFINDITEM, OnOdfinditem)
	ON_NOTIFY_REFLECT(LVN_ODSTATECHANGED, OnOdstatechanged)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(LVN_ODCACHEHINT, OnOdcachehint)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_WM_LBUTTONDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_CREATE()
	ON_WM_RBUTTONDOWN()
	ON_WM_CLOSE()
	ON_WM_SIZING()
	ON_WM_TIMER()
	ON_WM_NCHITTEST()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_NOTIFY_REFLECT(LVN_BEGINSCROLL, OnBeginScroll)
	ON_NOTIFY_REFLECT(LVN_ENDSCROLL, OnEndScroll)
	ON_NOTIFY_REFLECT(LVN_GETINFOTIP, OnGetInfotip)
	ON_NOTIFY_REFLECT(LVN_HOTTRACK, OnHotTrack)
	ON_NOTIFY_REFLECT(LVN_ITEMACTIVATE, OnItemActivate)
	ON_NOTIFY_REFLECT(LVN_MARQUEEBEGIN, OnMarqueeBegin)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPListCtr message handlers


UINT GPListCtr::DoMethod(const char *iStr, char *oStr)
{
	char met[150];
	strncpy(met,iStr,145);
	met[145]=0;
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc=0;

	int retint=-123456;
	int atoipos=atoi(pos);

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
	try
	{
		switch(nfunc)
		{
		case 0: /*GetBkColor*/
			if (oStr!=NULL)
			{	UINT cref=GetBkColor();
				sprintf(oStr,"%d\x07%d\x07%d",GetRValue(cref),GetGValue(cref),GetBValue(cref));
			}
			break;
		case 1: /*SetBkColor*/
			{
				UINT r=0,g=0,b=0;
				m_LastScanf=sscanf(pos,"%d,%d,%d",&r,&g,&b);
				retint=SetBkColor(RGB(r,g,b));
			}
			break;

		case 179: /*InserItemInGroup*/
		case 77: /*InsertItem*/
			if (!m_VirtualData)
			{
				char *postmpcc=new char [(int)strlen(pos)+10];
				strcpy(postmpcc,pos);
				char *txt=strchr(postmpcc,';');

				char *ed=strchr(postmpcc,':');
				if (ed && txt && ed>txt) ed=NULL;
				if (txt==NULL) txt=""; else *(txt++)=0;
				LVITEM lvi={0};
				lvi.iGroupId=23456;
				m_LastScanf=sscanf(postmpcc,"%d,%d",&lvi.iItem,&lvi.iGroupId);
				lvi.iItem=atoipos;
				lvi.mask=LVIF_TEXT|LVIF_PARAM;
				if (nfunc==179) 
					lvi.mask|=LVIF_GROUPID;
				else
				{
					lvi.iImage=lvi.iGroupId;
					if (lvi.iImage==23456) lvi.iImage=m_DefItemImage;
					lvi.mask|=LVIF_IMAGE;
				}

				GPTextArray *ar=new GPTextArray;
				char *ni=strchr(txt,GPC.DelimiterIn1);

				if (ni!=NULL) *(ni++)=0;
				lvi.iSubItem=0;
				lvi.pszText=txt;
				if (ar!=NULL)
				{
					ar->SetItem(0,lvi.pszText);
					ar->SetItemData(0,DefEditor);
				}
				lvi.lParam=(DWORD) ar;
				lvi.iItem=InsertItem(&lvi);

				int j;
				for(j=1;lvi.iItem>=0 && ni!=NULL;j++)
				{
					lvi.pszText=ni;
					ni=strchr(ni,GPC.DelimiterIn1);
					if (ni!=NULL) *(ni++)=0;
					if (ar!=NULL)
					{
						ar->SetItem(j,lvi.pszText);
						if (ed!=NULL)
						{
							DWORD edi=atoi(ed);
							ar->SetItemData(j,edi);
							ar->SetItemData(j,DefEditor);
							ed=strchr(ed,GPC.DelimiterIn1);
							if (ed!=NULL) ed++;
						}
					}
					SetItemText(lvi.iItem,j,lvi.pszText);
				}

				retint=lvi.iItem;
				delete[] postmpcc;
			}
			break;
		case 2: /*GetItemCount*/	retint=GetItemCount();	break;
		case 3: /*GetItem*/
		case 4: /*SetItem*/
		case 62:/*InsertItemEx*/
			{
				LVITEM lvi={0};

				lvi.mask=StringToIMask(pos);
				if (lvi.mask==0) lvi.mask=lastMask; else lastMask=lvi.mask;

				if (nfunc==3) /*GetItem*/
				{
					lvi.pszText=new char [5000];
					lvi.cchTextMax=4999;
					lvi.cColumns=1000;
					lvi.puColumns=new UINT [1000];
					m_LastScanf=sscanf(pos,"%d,%d",&lvi.iItem,&lvi.iSubItem);

					GetItem(&lvi);


					if (oStr!=NULL)	sprintf(oStr,"%ld\x7F%d\x7F%d\x7F%s\x7F%ld\x7F%d\x7F%d\x7F%ld\x7F%d\x7F%s\x7F%d\x7F%d",
							 lvi.mask, lvi.iItem, lvi.iSubItem,(LPCSTR)IStateToString(lvi.state),
							 lvi.stateMask,lvi.cchTextMax,lvi.iImage,
							 lvi.lParam,lvi.iIndent,lvi.pszText,lvi.iGroupId,lvi.cColumns);
					delete[] lvi.pszText;
					delete[] lvi.puColumns;
				}
				else
				if (nfunc==4 || nfunc==62) /*SetItem*/ /*InsertItemEx*/
				{
					char *postmpcc=new char [(int)strlen(pos)+10];
					strcpy(postmpcc,pos);

					lvi.state=StringToIState(postmpcc);
					if (lvi.state==0) lvi.state=lastState; else lastState=lvi.state;

					lvi.stateMask=StringToIMask(postmpcc);
					if (lvi.stateMask==0) lvi.stateMask=lastStateMask; else lastStateMask=lvi.stateMask;
					lvi.iImage=m_DefItemImage;
					m_LastScanf=sscanf(postmpcc,"%d,%d,%d,%d,%d,%d,%d,%d",
						 &lvi.iItem,&lvi.iSubItem,&lvi.cchTextMax,&lvi.iImage,&lvi.lParam,&lvi.iIndent,&lvi.iGroupId,&lvi.cColumns);
					CString tmpItemData=ExtractField(postmpcc,5,",");
					const char *pos2=FindField(postmpcc,8,",");
					lvi.puColumns=new UINT [lvi.cColumns+10];

					UINT i;
					for(i=0;i<lvi.cColumns;i++)
					{
						if (pos2)
						{
							lvi.puColumns[i]=atoi(pos2);
							pos2=strchr(pos2,',');
							if ((pos2++)==NULL) pos2="0";
						}
						else
						lvi.puColumns[i]=0;
					}


					lvi.pszText=strchr(postmpcc,';');
					if ((lvi.pszText++)==NULL) lvi.pszText="";

					if (nfunc==4) /*SetItemEx*/
					{
						if (!m_VirtualData)
						{
							if ((lvi.mask&LVIF_TEXT)==LVIF_TEXT)
							{
								GPTextArray *ar=(GPTextArray *) GetItemData(lvi.iItem);
								if (ar!=NULL)
								{
									ar->csItemData=tmpItemData;
									ar->SetItem(lvi.iSubItem,lvi.pszText);
									ar->SetItemData(lvi.iSubItem,DefEditor);
								}
							}
							retint=SetItem(&lvi);
						}
						else
						{
							m_VirtualData->SetItemText(lvi.iItem,lvi.iSubItem,lvi.pszText);
							m_VirtualData->SetItemState(lvi.iItem,lvi.iSubItem,lvi.state);
							m_VirtualData->SetItemImage(lvi.iItem,lvi.iSubItem,lvi.iImage);
							RedrawItems(lvi.iItem,lvi.iItem);
							retint=lvi.iItem;
						}
					}
					else /*InsertItemEx*/
					if (!m_VirtualData)
					{
						GPTextArray *ar=new GPTextArray;
						ar->SetItem(0,lvi.pszText);
						ar->SetItemData(0,DefEditor);
						ar->csItemData=tmpItemData;
						lvi.lParam=(DWORD) ar;
						lvi.mask|=(LVIF_TEXT|LVIF_PARAM);
						retint=InsertItem(&lvi);
					}
					delete[] lvi.puColumns;
					delete[] postmpcc;
				}
			}

		case 5: /*GetCallbackMask*/	if (oStr!=NULL)	sprintf(oStr,"%ld",GetCallbackMask());	break;
		case 6: /*SetCallbackMask*/
			{
				UINT mask=0;
				m_LastScanf=sscanf(pos,"%ld",&mask);
				retint=SetCallbackMask(mask);
			}
			break;
		case 7: /*GetNextItem*/
			{
				int nItem=-1,nFlags=0;
				nItem=atoipos;
				const char *pos2=strchr(pos,',');
				if (pos2!=NULL)
				{

					char *cstl[9]={"_ABOVE","_ALL","_BELOW","_TOLEFT","_TORIGHT","_DROPHILITED","_FOCUSED|","_SELECTED","_CUT" };
					UINT  ustl[9]={LVNI_ABOVE,LVNI_ALL,LVNI_BELOW,LVNI_TOLEFT,LVNI_TORIGHT,LVNI_DROPHILITED,LVNI_FOCUSED,LVNI_SELECTED,LVNI_CUT, };
					int i;
					for(i=0;i<9;i++)
						if (strstr(pos2,cstl[i])!=NULL) {nFlags|=ustl[i];lastFlag=nFlags;}

					if (nFlags==0) nFlags=lastFlag;
				}
				retint=GetNextItem(nItem,nFlags );
			}
			break;
		case 8: /*GetFirstSelectedItemPosition*/	retint=(int)(selposition=GetFirstSelectedItemPosition());	break;
		case 9: /*GetNextSelectedItem*/
			if (selposition==NULL) selposition=GetFirstSelectedItemPosition();
			if (oStr!=NULL && selposition!=NULL)
			{
				int nItem=GetNextSelectedItem(selposition);
				int len=sprintf(oStr,"%d\x7F",nItem);
				if (GetItemText(nItem,0,oStr+len,500)<=0) oStr[len]=0;
			}
			break;
		case 10: /*GetItemBoundsRect*/
		case 11: /*GetItemIconRect*/
		case 12: /*GetItemLabelRect*/
			if (oStr!=NULL)
			{
				UINT flg=0;
				if (nfunc==10) flg=LVIR_BOUNDS;
				else
				if (nfunc==11) flg=LVIR_ICON;
				else
				if (nfunc==12) flg=LVIR_LABEL;

				CRect re;
				GetItemRect(atoipos,&re,flg);
				sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
			}
			break;
		case 13: /*SetItemPosition*/
			{
				POINT pt={0};
				UINT nItem=0;
				m_LastScanf=sscanf(pos,"%d,%d,%d",&nItem,&pt.x,&pt.y);
				retint=SetItemPosition( nItem, pt);
			}
			break;
		case 14: /*GetItemPosition*/
			if (oStr!=NULL)
			{
				POINT pt={0};
				UINT ret=GetItemPosition(atoipos,&pt);
				sprintf(oStr,"%d\x7F%d\x7F%d",pt.x,pt.y,ret);
			}
			break;
		case 15: /*GetStringWidth*/	retint=GetStringWidth(pos);	break;
		case 16: /*GetEditControl*/	if (oStr!=NULL)	sprintf(oStr,"%X",(DWORD)GetEditControl() );	break;
		case 74: /*InsertColumn*/
		case 17: /*GetColumn*/
		case 18: /*SetColumn*/
		{
			char *cstl[6]={"LVCF_FMT","LVCF_IMAGE","LVCF_ORDER","LVCF_SUBITEM","LVCF_TEXT","LVCF_WIDTH",};
			UINT  ustl[6]={LVCF_FMT,LVCF_IMAGE,LVCF_ORDER,LVCF_SUBITEM,LVCF_TEXT,LVCF_WIDTH,};

			char *fcstl[8]={"LVCFMT_BITMAP_ON_RIGHT","LVCFMT_CENTER","LVCFMT_COL_HAS_IMAGES","LVCFMT_IMAGE","LVCFMT_RIGHT","LVCFMT_LEFT","_SORTUP","_SORTDOWN",};
			UINT  fustl[8]={LVCFMT_BITMAP_ON_RIGHT,LVCFMT_CENTER,LVCFMT_COL_HAS_IMAGES,LVCFMT_IMAGE,LVCFMT_RIGHT,LVCFMT_LEFT,HDF_SORTUP,HDF_SORTDOWN,};
			char *txt=new char [5000];
			*txt=0;
			LVCOLUMN lvc={0};
			lvc.pszText=txt;
			lvc.cchTextMax=4900;

			if (nfunc==17)
			{
				if (oStr!=NULL)
				{
					lvc.mask=LVCF_FMT|LVCF_IMAGE|LVCF_ORDER|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH;
					UINT ret=GetColumn(atoipos,&lvc);
					char mask[150];*mask=0;

					if (ret)
					{
						int i;
						for(i=0;i<6;i++)
							if ((lvc.mask&ustl[i])==ustl[i]) {strcat(mask,cstl[i]);strcat(mask,"|");}

						char fmt[150];
						for(i=0;i<8;i++)
							if ((lvc.fmt&fustl[i])==fustl[i]) {strcpy(fmt,fcstl[i]);break;}

						sprintf(oStr,"%s\x7F%s\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%s",
								mask,fmt, lvc.cx, lvc.cchTextMax, lvc.iSubItem, lvc.iImage,lvc.iOrder, lvc.pszText);
					}
					else *oStr=0;
				}
			}
			else
			if (nfunc==18 || nfunc==74)//	SetColumn || InsertColumn
			{
				int j;
				const char *pos2=pos,*pos3;
				int i;
				for(i=0;(pos3=strchr(pos2,','))!=NULL && i<8;i++)
				{
					pos2=++pos3;
					switch(i)
					{
					case 0:/*mask*/
							for(j=0;j<6;j++)
								if (strstr(pos2,cstl[j])!=NULL) lvc.mask|=ustl[j];

							if (lvc.mask==0) lvc.mask=lastMask; else lastMask=lvc.mask;
						break;
					case 1:/*fmt*/
							for(j=0;j<8;j++)
								if (strstr(pos2,fcstl[j])!=NULL) {lastFormat=lvc.fmt=fustl[j];break;}
							if (lvc.fmt==0) lvc.fmt=lastFormat; else lastFormat=lvc.fmt;
						break;
					case 2:/*lvc.cx*/			lvc.cx=atoi(pos2);			break;
					case 3:/*lvc.cchTextMax*/	lvc.cchTextMax=atoi(pos2);	break;
					case 4:/*lvc.iSubItem*/		lvc.iSubItem=atoi(pos2);	break;
					case 5:/*lvc.iImage*/		lvc.iImage=atoi(pos2);		break;
					case 6:/*lvc.iOrder*/		lvc.iOrder=atoi(pos2);		break;
					case 7:/*lvc.pszText*/		strcpy(lvc.pszText,pos2);	break;
					}

				}

				if (nfunc==18)		retint=SetColumn(atoipos,&lvc);
				else			
				{
					retint=InsertColumn(atoipos,&lvc);
					if (m_VirtualData) 
						m_VirtualData->InsertColumn(atoipos);
				}
			}
			delete[] txt;
		}
			break;
		case 19: /*GetColumnWidth*/
			if (oStr!=NULL)
				if (atoipos<0)
				{
					int nCol=GetHeaderCtrl()->GetItemCount(),i,curlen=0;
					for(i=0;i<nCol;i++)
						curlen+=sprintf(oStr+curlen,"%d\x07",GetColumnWidth(i));
					if (curlen>0) oStr[curlen-1]=0;
				}
				else
					retint=GetColumnWidth(atoipos);
			break;
		case 20: /*SetColumnWidth*/
			{
				//DWORD dwWFlags[]={LVSCW_AUTOSIZE, LVSCW_AUTOSIZE_USEHEADER,};
				//char *acWFlags[]={"A", "U",};
				if (strchr(pos,GPC.DelimiterIn1))
				{// multi
					int nCol=GetHeaderCtrl()->GetItemCount(),i;
					const char *pos2=pos;
					for(i=0;i<nCol && pos2!=NULL;i++)
					{
						int iWidth=atoi(pos2);
						if (iWidth>0 || *pos2=='0')	SetColumnWidth(i,iWidth);
						else 	SetColumnWidth(i,strchr(pos2,'H')?LVSCW_AUTOSIZE_USEHEADER:LVSCW_AUTOSIZE);
						if ((pos2=strchr(pos2,GPC.DelimiterIn1))) pos2++;
					}
				}
				else
				{
					UINT iWidth;
					const char *pos2=strchr(pos,',');
					if (pos2++==NULL)  pos2="100";
					iWidth=atoi(pos2);
					if (iWidth>0 || *pos2=='0')	SetColumnWidth(atoipos,iWidth);
					else 	SetColumnWidth(atoipos,strchr(pos2,'H')?LVSCW_AUTOSIZE_USEHEADER:LVSCW_AUTOSIZE);

					if (iWidth==-1)
					{
						retint=GetColumnWidth(iWidth);
						retint=SetColumnWidth(iWidth,retint+4);
					}
				}
				Invalidate();
				SetEditRect();
				break;
			}
		case 21: /*GetCheck*/	retint=GetCheck(atoipos);	break;
		case 22: /*SetCheck*/
			{ UINT nItem=0,fCheck=1;
				m_LastScanf=sscanf(pos,"%d,%d",&nItem,&fCheck);
				retint=SetCheck(nItem,fCheck);
			}
			break;
		case 23: /*GetViewRect*/
			if (oStr!=NULL)
			{
				CRect re;GetViewRect(&re);
				sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
			}
			break;
		case 24: /*GetTextColor*/
			if (oStr!=NULL)
			{	UINT cref=GetTextColor();
				sprintf(oStr,"%d\x07%d\x07%d",GetRValue(cref),GetGValue(cref),GetBValue(cref));
			}
			break;
		case 25: /*SetTextColor*/
			{
				UINT r=0,g=0,b=0;
				m_LastScanf=sscanf(pos,"%d,%d,%d",&r,&g,&b);
				retint=SetTextColor(RGB(r,g,b));
			}
			break;
		case 26: /*GetTextBkColor*/
			if (oStr!=NULL)
			{	UINT cref=GetTextBkColor();
				sprintf(oStr,"%d\x07%d\x07%d",GetRValue(cref),GetGValue(cref),GetBValue(cref));
			}
			break;
		case 27: /*SetTextBkColor*/
			{
				UINT r=0,g=0,b=0,ret=0;
				m_LastScanf=sscanf(pos,"%d,%d,%d",&r,&g,&b);
				ret=SetTextBkColor(RGB(r,g,b));
				if (oStr!=NULL)	sprintf(oStr,"%d",ret);
			}
			break;
		case 28: /*GetTopIndex*/	retint=GetTopIndex();	break;
		case 29: /*GetCountPerPage*/	retint=GetCountPerPage();	break;
		case 30: /*GetOrigin*/
			if (oStr!=NULL)
			{
				POINT pt={0};
				GetOrigin(&pt);
				sprintf(oStr,"%d\x7F%d",pt.x,pt.y);
			}
			break;
		case 31: /*GetItemState*/
		case 32: /*SetItemState*/
		{
			UINT nMask=0;
			UINT tmpstate=0;

			if (nfunc==31)
			{
				if (oStr!=NULL)
				{
					nMask=StringToIState(*pos==0?NULL:pos);

					if (nMask==0) nMask=lastMask; else lastMask=nMask;
					tmpstate=GetItemState(atoipos, nMask );

					sprintf(oStr,"%ld\x7F%s",tmpstate,(LPCSTR)IStateToString(tmpstate));
				}
			}
			else
			{
				tmpstate=StringToIState(*pos==0?NULL:pos);
				if (tmpstate==0) tmpstate=lastState; else lastState=tmpstate;
				retint=SetItemState(atoipos,tmpstate,tmpstate);
			}
		}
			break;
		case 33: /*GetItemText*/
			if (oStr)
			{
				char *str=oStr;
				*str=0;
				const char *postmp=pos;
				int len=0;
				int nField=0;
				while((*(postmp=FindField(postmp,2,",")) && len<TMP_STR_OUT_LEN) || nField==0)
				{
					if (postmp==NULL && len==0) postmp="0";
					if (nField) strcpy(str+len++,"\x7F");
					if (GetItemText(atoipos,atoi(postmp),str+len,TMP_STR_OUT_LEN-len)<=0) *(str+len)=0;
					len+=(int)strlen(str+len);
					nField++;
				}
			}
			break;
		case 180: /*GetItemTextEx*/
			if (oStr)
			{
				int nCol=GetHeaderCtrl()->GetItemCount();

				char *str=oStr;
				*str=0;
				const char *postmp=pos;
				int len=0;
				int nField=0;
				while(*postmp && len<TMP_STR_OUT_LEN)
				{
					int i;
					for(i=0;i<nCol;i++)
					{
						if (i==0)
						{
							if (nField)	strcpy(str+len++,"\x7F");
						}
						else		strcpy(str+len++,"\x07");

						if (GetItemText(atoi(postmp),i,str+len,TMP_STR_OUT_LEN-len)<=0) *(str+len)=0;
						len+=(int)strlen(str+len);
						nField++;
					}
					postmp=FindField(postmp,2,",");
				}
			}
			break;
		case 132: /*SetItemTextReflect*/
		case 34: /*SetItemText*/
			{
				char *postmpcc=new char [(int)strlen(pos)+10];
				strcpy(postmpcc,pos);

				char *pos2=strchr(postmpcc,';');
				if (pos2++==NULL) pos2="";
				LVITEM lvi={0};
				m_LastScanf=sscanf(postmpcc,"%d,%d",&lvi.iItem,&lvi.iSubItem);
				lvi.mask=LVIF_PARAM;
				GetItem(&lvi);
				GPTextArray *ar=(GPTextArray *) lvi.lParam;

				for(;lvi.iItem>=0 && pos2!=NULL;lvi.iSubItem++)
				{
					lvi.pszText=pos2;
					pos2=strchr(pos2,GPC.DelimiterIn1);
					if (pos2!=NULL) *(pos2++)=0;
					if (m_VirtualData)
					{
						m_VirtualData->SetItemText(lvi.iItem,lvi.iSubItem,lvi.pszText);
						RedrawItems(lvi.iItem,lvi.iItem);
					}
					else
						SetItemText(lvi.iItem,lvi.iSubItem,lvi.pszText);
					if (ar!=NULL) ar->SetItem(lvi.iSubItem,lvi.pszText);
					if (nfunc==132 && referGPU!=NULL)
					{
						CString str;
						str.Format("%d\x7F%d\x7F%s",lvi.iItem,lvi.iSubItem,lvi.pszText);
						referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnItemTextReflect",str);
					}
				}
				delete[] postmpcc;
			}
			break;
		case 35: /*SetItemCount*/
			SetItemCount(atoipos); 
			break;
		case 36: /*SetItemData*/
			{ 
				GPTextArray *ar=(GPTextArray *) GetItemData(atoipos);
				if (ar)
					ar->csItemData=strchr(pos,',')?strchr(pos,','):"";
			}
			break;
		case 37: /*GetItemData*/
			if (oStr && atoipos>=0 && atoipos<GetItemCount()) 
			{
				GPTextArray *ar=(GPTextArray *) GetItemData(atoipos);
				if (ar) strcpy(oStr,ar->csItemData);
			}
			break;
		case 38: /*GetSelectedCount*/		retint=GetSelectedCount(); break;
		case 39: /*SetColumnOrderArray*/
			{
				int *piArray=new int [512];
				int i;
				for(i=0;i<512;i++) piArray[i]=0;
				const char *pos2=pos;
				if ((pos2=strchr(pos2,',')) || (pos2=strchr(pos2,GPC.DelimiterIn1)))
				{
					if (atoipos<=0) atoipos=GetHeaderCtrl()->GetItemCount();
					for(i=0;i<atoipos && pos2;i++)
					{
						const char *postmp;
						piArray[i]=atoi(++pos2);
						if (!(postmp=strchr(pos2,','))) postmp=strchr(pos2,GPC.DelimiterIn1);
						pos2=postmp;
					}
					retint=SetColumnOrderArray(atoipos,piArray);
					Invalidate();
					SetEditRect();
				}
				delete[] piArray;
			}
			break;
		case 40: /*GetColumnOrderArray*/
			if (oStr!=NULL)
			{
				UINT nCol=1;
				CHeaderCtrl *tmpHead=GetHeaderCtrl();
				if (tmpHead!=NULL)
				{
					try
					{
						nCol=tmpHead->GetItemCount();
					}catch(...)
					{
						GPC.m_ErrReport.GPWriteErrorLog("GPListCtr", "DoMethod 1093",iStr);
						nCol=1;
					}
				}


				int *piArray=new int [nCol+5];
				UINT i;
				for(i=0;i<nCol+3 && nCol<0xFFFF;i++) piArray[i]=-1;
				GetColumnOrderArray(piArray,nCol);
				char tmp[50];

				for(i=0;i<nCol && piArray[i]!=-1;i++)
				{
					sprintf(tmp,"%d%c",piArray[i],piArray[i+1]!=-1?7:0);
					strcat(oStr,tmp);
				}
				delete[] piArray;
			}
			break;
		case 41: /*SetIconSpacing*/
			{
				CSize is(0,0);
				int cx=0,cy=0;
				m_LastScanf=sscanf(pos,"%d,%d",&cx,&cy);
				is=SetIconSpacing(cx,cy);
				if (oStr!=NULL)	sprintf(oStr,"%d\x7F%d",is.cx,is.cy);
			}
			break;
		case 42: /*GetHeaderCtrl*/ if (oStr!=NULL) sprintf(oStr,"%X",(DWORD)GetHeaderCtrl()); break;
		case 43: /*GetHotCursor*/ if (oStr!=NULL) sprintf(oStr,"%X",(DWORD)GetHotCursor()); break;
		case 44: /*SetHotCursor*/
			{	HCURSOR hc=NULL,rhc=NULL;
				DWORD dwtmp=0;
				m_LastScanf=sscanf(pos,"%X",&dwtmp);
				hc=(HCURSOR)dwtmp;
				if (hc!=NULL)	rhc=SetHotCursor(hc);
				if (oStr!=NULL)	sprintf(oStr,"%X",(DWORD)rhc);
			}
			break;
		case 45: /*GetSubItemRect*/
			{
				char *cnArea[3]={"LVIR_BOUNDS","LVIR_ICON","LVIR_LABEL",};
				UINT  unArea[3]={LVIR_BOUNDS,LVIR_ICON,LVIR_LABEL,};
				int nArea=0,iItem=0,iSubItem=0;
				m_LastScanf=sscanf(pos,"%d,%d",&iItem,&iSubItem);
				CRect re(0,0,0,0);

				int i;
				for(i=0;i<3;i++)
					if (strstr(pos,cnArea[i])!=NULL) nArea|=unArea[i];

				GetSubItemRect(iItem,iSubItem,nArea,re);
				if (oStr!=NULL)
					sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);

			}
			break;
		case 46: /*GetHotItem*/				retint=GetHotItem(); break;
		case 47: /*SetHotItem*/				retint=SetHotItem(atoipos); break;
		case 48: /*GetSelectionMark*/		retint=GetSelectionMark(); break;
		case 49: /*SetSelectionMark*/		retint=SetSelectionMark(atoipos); break;
		case 50: /*GetExtendedStyle*/
			if (oStr!=NULL)
				GetObjStlStr(oStr, GetExtendedStyle(), N_LISTCTRL_EX_STYLES,  aListCtrlExStyleName, aListCtrlExStyleUINT, aListCtrlExStyleMask);
			break;
		case 51: /*SetExtendedStyle*/
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
		case 52: /*SubItemHitTest*/
		case 67: /*HitTest*/
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				_strupr(pos333);
				LVHITTESTINFO pInfo;
				m_LastScanf=sscanf(pos333,"%d,%d",&pInfo.pt.x,&pInfo.pt.y);
				char *cflg[8]={"LVHT_ABOVE|","LVHT_BELOW|","LVHT_NOWHERE|","LVHT_ONITEMICON|","LVHT_ONITEMLABEL|","LVHT_ONITEMSTATEICON|","LVHT_TOLEFT|","LVHT_TORIGHT|",};
				UINT  uflg[8]={LVHT_ABOVE,LVHT_BELOW,LVHT_NOWHERE,LVHT_ONITEMICON,LVHT_ONITEMLABEL,LVHT_ONITEMSTATEICON,LVHT_TOLEFT,LVHT_TORIGHT,};
				int i;
				char flags[250];*flags=0;

				if (nfunc==52)	/*SubItemHitTest*/	SubItemHitTest(&pInfo);
				else			/*HitTest*/			HitTest(&pInfo);

				for(i=0;i<8;i++)
					if ((pInfo.flags&uflg[i])==uflg[i]) strcat(flags,cflg[i]);

				if (oStr!=NULL) sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d\x7F%s",pInfo.iItem,pInfo.iSubItem,pInfo.pt.x,pInfo.pt.y,flags);
				delete[] pos333;
			}
			break;
		case 53: /*GetWorkAreas*/
			if (oStr!=NULL)
			{
				int nWorkAreas=atoipos;
				if (nWorkAreas<0 || nWorkAreas>1000) nWorkAreas=990;
				CRect *piArray=new CRect[nWorkAreas+2];
				int i;
				for(i=0;i<nWorkAreas;i++) piArray[i].SetRectEmpty();
				GetWorkAreas(nWorkAreas,piArray);

				char tmp[100];
				for(i=0;i<nWorkAreas;i++)
				{
					sprintf(tmp,"%d\x07%d\x07%d\x07%d\x7F",piArray[i].left,piArray[i].top,piArray[i].right,piArray[i].bottom);
					strcat(oStr,tmp);
				}
				delete[] piArray;
			}
			break;
		case 54: /*GetNumberOfWorkAreas*/ retint=GetNumberOfWorkAreas(); break;
		case 55: /*SetItemCountEx*/
			if (m_VirtualData)
			{
				m_VirtualData->SetMinAvID(0);
				m_VirtualData->SetMaxAvID(atoipos);
				SetItemCountEx(atoipos,(strstr(pos,"SC")?LVSICF_NOSCROLL:0)|(strstr(pos,"IN")?LVSICF_NOINVALIDATEALL:0));
			}
			break;
		case 56: /*SetWorkAreas*/
			{
				int nWorkAreas=atoipos;
				if (nWorkAreas<0 || nWorkAreas>1000) nWorkAreas=990;
				CRect *piArray=new CRect[nWorkAreas+2];
				const char *pos2;
				if ((pos2=strchr(pos,','))!=NULL)
				{
					int i;
					for(i=0;i<nWorkAreas;i++)
						if (pos2!=NULL)
						{
							char frmt[50];
							sprintf(frmt,"%%d%c%%d%c%%d%c%%d",GPC.DelimiterIn1,GPC.DelimiterIn1,GPC.DelimiterIn1);
							m_LastScanf=sscanf(++pos2,frmt,&piArray[i].left,&piArray[i].top,&piArray[i].right,&piArray[i].bottom);
							pos2=strchr(pos2,GPC.DelimiterIn2);

						} else piArray[i].SetRectEmpty();
				}

				SetWorkAreas(nWorkAreas,piArray);
				delete[] piArray;
			}
			break;
		case 57: /*ApproximateViewRect*/
			{
				CSize sz(-1,-1),retsz;
				int iCount;
				m_LastScanf=sscanf(pos,"%d,%d,%d",&sz.cx,&sz.cy,&iCount);

				retsz=ApproximateViewRect(sz,iCount);

				if (oStr!=NULL) sprintf(oStr,"%d\x7F%d",retsz.cx,retsz.cy);
			}
			break;
		case 58: /*GetBkImage*/
		case 59: /*SetBkImage*/
			{
				char *cstl[5]={"_SOURCE_NONE|","_SOURCE_HBITMAP|","_SOURCE_URL|","_STYLE_NORMAL|","_STYLE_TILE|",};
				UINT  ustl[5]={LVBKIF_SOURCE_NONE,LVBKIF_SOURCE_HBITMAP,LVBKIF_SOURCE_URL,LVBKIF_STYLE_NORMAL,LVBKIF_STYLE_TILE,};
				LVBKIMAGE lvbkImage;
				lvbkImage.pszImage =new char [1000];
				int i;

				if (nfunc==58)
				{
					if (oStr!=NULL)
					{
						GetBkImage( &lvbkImage );

						char str[200];*str=0;
						for(i=0;i<5;i++)
							if ((lvbkImage.ulFlags&ustl[i])==ustl[i]) {strcat(str,cstl[i]);strcat(str,"|");}

						sprintf(oStr,"%s\x7F%s\x7F%ld\x7F%ld\x7F%d\x7F%d",str,lvbkImage.pszImage,(DWORD)lvbkImage.hbm,lvbkImage.cchImageMax,lvbkImage.xOffsetPercent,lvbkImage.yOffsetPercent);
					}
				}
				else
				{
					lvbkImage.ulFlags=0;
					char *pos333=new char [(int)strlen(pos)+2];
					strcpy(pos333,pos);
					char *pos2=strchr(pos333,';');
					int tile=1,ofX=0,ofY=0;
					if (pos2!=NULL)
					{
						*(pos2++)=0;
						m_LastScanf=sscanf(pos2,"%d,%d,%d",&tile,&ofX,&ofY);
					}
					SetBkImage(DosToAnsi(pos333),tile,ofX,ofY);
					delete[] pos333;
				}
				delete[] lvbkImage.pszImage;
			}
			break;
		case 60: /*GetHoverTime*/ retint=GetHoverTime(); break;
		case 61: /*SetHoverTime*/ retint=SetHoverTime(atoipos);	break;
		// case 62: см. выше
		case 63: /*DeleteItem*/
			if (!m_VirtualData)
			{
				const char *pCh=NULL;
				if ((pCh=strchr(pos,GPC.DelimiterIn1))!=NULL ||(pCh=strchr(pos,','))!=NULL ||(pCh=strchr(pos,GPC.DelimiterIn2))!=NULL)
				{
					UINT *itarr=new UINT [(int)strlen(pos)/2+10];
					const char *pos2=pos;
					UINT i=0;
					do
					{
						itarr[i++]=atoi(pos2);
						pos2=strchr(pos2,*pCh);
					}
					while(pos2++!=NULL);

					int nItem=GetItemCount();
					qs(itarr,0,i-1);
					do
						if (itarr[--i]<(UINT)nItem)
						{
							if ((m_EditInProgr&0x1)!=0)
							{
								if ((UINT)lasthti.iItem==itarr[i])
								{
									if (LastEditorID>0 && referGPU && LastEditorID<(*referGPU)->m_NGPUNIT && referGPU[LastEditorID]!=NULL && referGPU[LastEditorID]->UnitHWND!=NULL)
										referGPU[LastEditorID]->GPSetProperty("DELSTYLE=WS_VISIBLE");
									lasthti.iItem=-1;
								}
							}
							retint=DeleteItem(itarr[i]);
						}
					while(i>0);
					delete[] itarr;
				}
				else
					if (atoipos>=0 && atoipos<GetItemCount())
					{
						if ((m_EditInProgr&0x1)!=0)
						{
							if (lasthti.iItem==atoipos)
							{
								if (LastEditorID>0 && referGPU && LastEditorID<(*referGPU)->m_NGPUNIT && referGPU[LastEditorID]!=NULL && referGPU[LastEditorID]->UnitHWND!=NULL)
									referGPU[LastEditorID]->GPSetProperty("DELSTYLE=WS_VISIBLE");
								lasthti.iItem=-1;
							}
						}
						retint=DeleteItem(atoipos);
					}
			}
			break;
		case 64: /*DeleteAllItems*/
			if (!m_VirtualData)
			{
				if ((m_EditInProgr&0x1)!=0)
				{
					if (LastEditorID>0 && referGPU && LastEditorID<(*referGPU)->m_NGPUNIT && referGPU[LastEditorID]!=NULL && referGPU[LastEditorID]->UnitHWND!=NULL)
							referGPU[LastEditorID]->GPSetProperty("DELSTYLE=WS_VISIBLE");
						lasthti.iItem=-1;
				}
				BOOL wv=IsWindowVisible();
				if (wv) ModifyStyle(WS_VISIBLE,0);
				EnsureVisible(0,TRUE);
				retint=DeleteAllItems();
				if (wv)
				{
					ModifyStyle(0,WS_VISIBLE);
					Invalidate();
				}
			}
			break;
		case 65: /*FindItem*/
			if (!m_VirtualData)
			{
				LVFINDINFO lfi={0};
				int nStart = -1;
				/*
	VK_LEFT
	VK_RIGHT
	VK_UP
	VK_DOWN
	VK_HOME
	VK_END
	VK_PRIOR
	VK_NEXT
	*/
				char *cflags[5]={"_PARAM|","_PARTIAL|","_STRING|","_WRAP|","_NEARESTXY|",};
				UINT  uflags[5]={LVFI_PARAM,LVFI_PARTIAL,LVFI_STRING,LVFI_WRAP,LVFI_NEARESTXY,};
				m_LastScanf=sscanf(pos,"%d,%ld,%d,%d,%ld",&nStart,&lfi.lParam,&lfi.pt.x,&lfi.pt.y,&lfi.vkDirection);
				const char *pos2=pos,*pos3;
				while((pos3=strchr(pos2,','))!=NULL) pos2=++pos3;
				lfi.psz=pos2;

				int i;
				for(i=0;i<5;i++)
					if (strstr(pos,cflags[i])!=NULL) lfi.flags|=uflags[i];

				retint=FindItem(&lfi, nStart);
			}
			break;
		case 97: /*SortItemsAsNum*/
		case 98: /*SortItemsAsDate*/
		case 66: /*SortItems*/
			if (!m_VirtualData)
			{
				const char *pos2=strchr(pos,',');
				if (pos2) pos2++;

				if (pos2==NULL || *pos2=='3' || *pos2=='0') 
				{
					if (m_LastSort==atoipos) DESCENDSort=DESCENDSort?FALSE:TRUE;
				}
				else
				{
					DESCENDSort=( *pos2=='D' || *pos2=='d' || *pos2=='2')?TRUE:FALSE;
				}

				if (*pos)	SortColumnNumber=atoipos;
				else		atoipos=m_LastSort;

				nFilterArrayCount=FilterArray->GetItemCount();
				if ((m_EditInProgr&0x1)!=0 && hti.iItem!=-1 && hti.iSubItem!=-1)
					SetItemState(hti.iItem,LVIS_SELECTED,LVIS_SELECTED|LVIS_FOCUSED|LVIS_ACTIVATING );

				while(nFilterArrayCount>=0 &&(FilterArray->GetItem(nFilterArrayCount)==NULL || *((char *)FilterArray->GetItem(nFilterArrayCount))==0))
					nFilterArrayCount--;
				if (nfunc==66)	retint=SortItems( mCompareFunc,(DWORD)(CWnd::FromHandle(this->m_hWnd)));
				else
				if (nfunc==97)	retint=SortItems( mCompareFuncNum,(DWORD)(CWnd::FromHandle(this->m_hWnd)));
				else
				if (nfunc==98)	retint=SortItems( mCompareFuncDate,(DWORD)(CWnd::FromHandle(this->m_hWnd)));

				if ((m_EditInProgr&0x1)!=0  && hti.iItem!=-1 && hti.iSubItem!=-1)
				{
					POSITION pos22 = GetFirstSelectedItemPosition();
					if (pos22 != NULL)
					{
						lasthti.iItem= hti.iItem = GetNextSelectedItem(pos22);
						SetItemState(hti.iItem,0,LVIS_SELECTED|LVIS_FOCUSED|LVIS_ACTIVATING );
						SetEditRect();
					}
				}
				if (*pos) m_LastSort=atoipos;
			}
			break;
		// case 67: HitTest  см.выше
		case 68: /*EnsureVisible*/
			{
				int nItem;
				UINT bPartialOK;
				m_LastScanf=sscanf(pos,"%d,%d",&nItem,&bPartialOK);
				retint=EnsureVisible(nItem,bPartialOK );
			}
			break;
		case 69: /*Scroll*/
			{
				CSize size;
				m_LastScanf=sscanf(pos,"%d,%d",&size.cx,&size.cy);
				retint=Scroll(size);
			}
			break;
		case 70: /*RedrawItems*/
			{
				int nFirst,nLast;
				m_LastScanf=sscanf(pos,"%d,%d",&nFirst,&nLast);
				retint=EnsureVisible(nFirst,nLast );
			}
			break;
		case 71: /*Update*/ 	retint=Update(atoipos);	break;
		case 72: /*Arrange*/
			if (!m_VirtualData)
			{
				UINT flg=LVA_DEFAULT;
				if (strstr(pos,"LVA_ALIGNLEFT")!=NULL)	flg=LVA_ALIGNLEFT;
				else
				if (strstr(pos,"LVA_ALIGNTOP")!=NULL)	flg=LVA_ALIGNTOP;
				else
				if (strstr(pos,"LVA_SNAPTOGRID")!=NULL)	flg=LVA_SNAPTOGRID;
				retint=Arrange(flg);
			}
			break;
		case 73: /*EditLabel*/
			{
				void *ret=EditLabel(atoipos);
				if (oStr!=NULL) sprintf(oStr,"%ld",(DWORD)ret);
			}
			break;
		// case 74: InsertColumn  см.выше
		case 75: /*DeleteColumn*/
			{
				if (m_VirtualData) m_VirtualData->DeleteColumn(atoipos);
				UINT ret=DeleteColumn(atoipos);
				if (oStr!=NULL) sprintf(oStr,"%d",ret);
			}
			break;
		case 78: /*SetFilter*/
			if (!m_VirtualData)
			if (FilterArray!=NULL)
			{
				const char *pos2=strchr(pos,',');
				if (pos2!=NULL) pos2++; else pos2="";
				retint=FilterArray->SetItem(atoipos,pos2)!=NULL;
				DoMethod("SortItems",NULL);
			}
			break;
		case 79: /*GetChecked*/
			if (oStr!=NULL)
			{
				int i,nItem=GetItemCount( );
				char brk[3]={127,0,};
				char brk2[3]={7,0,};
				char tmp[1005];
				int flg=0;
				flg=atoipos;
				if (flg>=0 && flg<1000)
				for(i=0;i<nItem;i++)
					if (GetCheck(i)==TRUE)
					{
						if (*oStr!=0) strcat(oStr,brk);
						sprintf(oStr+(int)strlen(oStr),"%d",i);
						if (flg>0)
						{
							int j;
							for(j=0;j<flg;j++)
							{
								strcat(oStr,brk2);
								*tmp=0;
								if (GetItemText(i,j,tmp,1000)<=0 ) *tmp=0;
								strcat(oStr,tmp);
							}
						}
					}
			}
			break;
		case 80: /*GetSelected*/
			if (oStr!=NULL)
			{
				char brk[3]={127,0,};
				char brk2[3]={7,0,};
				char tmp[1005];
				int flg=atoipos;
				POSITION posit = GetFirstSelectedItemPosition();

				if (flg>=0 && flg<1000 && posit != NULL)
					while(posit)
					{
						int nItem = GetNextSelectedItem(posit);
						if (*oStr!=0) strcat(oStr,brk);
						sprintf(oStr+(int)strlen(oStr),"%d",nItem);
						if (flg>0)
						{
							int j;
							for(j=0;j<flg;j++)
							{
								strcat(oStr,brk2);
								*tmp=0;
								if (GetItemText(nItem,j,tmp,1000)==0) *tmp=0;
								strcat(oStr,tmp);
							}
						}
					}
			}
			break;
		case 76: /*CreateDragImage*/  // зарезервировано
					//CImageList* CreateDragImage( int nItem, LPPOINT lpPoint );

		case 81: /*UpdateGroup*/
			if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
			{
				int i=0;
				POSITION posit = GetFirstSelectedItemPosition();

				if (posit == NULL)
					referGPU[UnitId&0xFFFF]->UpdateGroup(-123456,GetStyle());
				else
					while(posit)
						referGPU[UnitId&0xFFFF]->UpdateGroup(GetNextSelectedItem(posit)+(i++!=0)*0x1000,GetStyle());
			}
			break;
		case 82: /*SetEditorPerColumn*/
			{
				int nItem=GetItemCount(),i,j;
				const char *ed=pos,*ed2=NULL;
				int nCol=GetHeaderCtrl()->GetItemCount();
				if (nCol>0)
				{
					UINT *edarr=new UINT [nCol];

					{
						DWORD edUnit=0;
						for(i=0;i<nCol;i++)
						{
							if (ed!=NULL)
							{
								edUnit=atoi(ed);
								ed=strchr(ed,GPC.DelimiterIn1);
								if (ed!=NULL) ed++;
							}
							edarr[i]=edUnit;
						}
					}

					for(i=0;i<nItem;i++)
					{
						GPTextArray *ar=(GPTextArray *) GetItemData(i);
						if (ar!=NULL)
						{
							int nSubItem=ar->GetItemCount();
							for(j=0;j<nSubItem && j<nCol;j++)
								ar->SetItemData(j,edarr[j]);
						}
						ed=ed2;
					}

					delete[] edarr;
				}
			}
			break;
		case 83: /*SetEditorPerLine*/
		case 84: /*SetEditorForItem*/
		case 87: /*SetEditor*/
			{
				int nItem=GetItemCount(),i,j;
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				char *ed=pos333,*ed2=NULL;
				DWORD edUnit=0;
				int start=0;
				if (nfunc==84)
				{
					start=atoipos;
					ed=strchr(pos333,',');
					if (ed!=NULL) ed++;
					if (start<0) start=nItem;
					else if (start<nItem) nItem=start+1;
				}

				for(i=start;i<nItem;i++)
				{
					GPTextArray *ar=(GPTextArray *) GetItemData(i);
					if (ar!=NULL)
					{
						int nSubItem=ar->GetItemCount();
						if (ed!=NULL)
						{
							ed2=strchr(ed,GPC.DelimiterIn1);
							if (ed2!=NULL) *(ed2++)=0;
							for(j=0;j<nSubItem;j++)
							{
								if (ed!=NULL)
								{
									edUnit=atoi(ed);
									ed=strchr(ed,GPC.DelimiterIn2);
									if (ed!=NULL) ed++;
								}
								ar->SetItemData(j,edUnit);
							}
						}
						else
							for(j=0;j<nSubItem;j++)	ar->SetItemData(j,edUnit);
					}
					ed=ed2;
				}
				delete[] pos333;
			}
			break;
		case 85: /*SetEditorForSubItem*/
			{
				int iItem=0;
				UINT iSubItem=0;
				DWORD edUnit=0;
				m_LastScanf=sscanf(pos,"%d,%d,%d",&iItem,&iSubItem,&edUnit);
				GPTextArray *ar=(GPTextArray *) GetItemData(iItem);
				if (ar!=NULL && iSubItem<ar->GetItemCount())
					ar->SetItemData(iSubItem,edUnit);
			}
			break;
		case 86: /*SetEditOnOff*/
			{	//29,M,SetEditOnOff 1,0,1,0,1
				int onoff=0,verhor=0,forback=0,skip=0,lcbreak=0,delnext=0,ManMove=0;
				m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d,%d,%d",&onoff,&verhor,&skip,&forback,&lcbreak,&delnext,&ManMove);
				onoff%=2;verhor%=2;skip%=2;forback%=2;lcbreak%=2;delnext%=2;ManMove%=2;
				retint=m_EditInProgr;
				if (onoff>1)	m_EditInProgr=onoff;
				else			m_EditInProgr=onoff+verhor*0x2+skip*0x4+forback*0x8+lcbreak*0x10+delnext*0x20+ManMove*0x40;
				if (onoff==0)
				{
					lasthti.iItem=-1;lasthti.iSubItem=-1;
					if (LastEditorID>0 && referGPU && LastEditorID<(*referGPU)->m_NGPUNIT && referGPU[LastEditorID] && referGPU[LastEditorID]->UnitHWND!=NULL)
						referGPU[LastEditorID]->GPSetProperty("DELSTYLE=WS_VISIBLE");
					else
						if (LastEditorID==0)
						{
							::SetWindowLong(m_StaticCursor->m_hWnd,GWL_STYLE,::GetWindowLong(m_StaticCursor->m_hWnd,GWL_STYLE)&(0xFFFFFFFF^WS_VISIBLE));
							//m_StaticCursor->ModifyStyle(WS_VISIBLE,0);
							m_StaticCursor->Invalidate();
						}
				}
				Invalidate();
			}
			break;
		case 88: /*SetEditItem*/
			{
				int iItem=0;
				UINT iSubItem=0;
				m_LastScanf=sscanf(pos,"%d,%d",&iItem,&iSubItem);
				if (iItem>=0 && iItem<GetItemCount())
				{
					SetFocus();
					GPTextArray *ar=(GPTextArray *) GetItemData(iItem);
					if (ar!=NULL && iSubItem<ar->GetItemCount())
					{
						hti.iItem=iItem;
						hti.iSubItem=iSubItem;
						UpdateHtiPosition();
						EnsureVisible(hti.iItem,FALSE);
	//					EditorID=ar->GetItemData(hti.iSubItem);

						SetEditRect();
						SetSelByEdit();
						Invalidate();
					}
				}
			}
			break;
		case 89: /*GetEditItem*/
			if (oStr!=NULL)	sprintf(oStr,"%d\x7F%d",hti.iItem,hti.iSubItem);
			break;
		case 90: /*GetEditResult*/
			if (oStr!=NULL)	strcpy(oStr,(LPCSTR)LastEditResult);
			break;
		case 91: /*SetAutoUpdate*/
			retint=AutoUpdate;
			AutoUpdate=atoipos;
			break;
		case 92: /*SetDefEditor*/
			retint=DefEditor;
			DefEditor=atoipos;
			break;
		case 93: /*GetDefEditor*/	retint=DefEditor;		break;
		case 94: /*GetListContents*/
		case 95: /*ClearRegion*/
			if (oStr!=NULL || nfunc==95)
			{
				int i,j,CurLen=0,nItem=GetItemCount();
				int nCol=GetHeaderCtrl()->GetItemCount();
				int Left,Right,Top,Bottom;
				Left=Right=Top=Bottom=-1;
				const char *repltext=strchr(pos,';');
				if (repltext++==NULL) repltext="";

				m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&Left,&Top,&Right,&Bottom);
				if (Left<0) Left=0;
				if (Right<Left || Right>nCol ) Right=nCol;
				if (Top<0) Top=0;
				if (Bottom<Top || Bottom>=nItem ) Bottom=nItem-1;

				for(i=Top;i<=Bottom;i++)
				{
					if (nfunc==94 && i!=Top) oStr[CurLen++]=127;
					for(j=Left;j<=Right;j++)
					{
						if (nfunc==94)
						{
							if (j!=Left) oStr[CurLen++]=7;
							CurLen+=GetItemText(i,j,oStr+CurLen,9990);
							if (oStr[CurLen]!=0)
								oStr[CurLen]=0;
						}
						else	SetItemText(i,j,repltext);
					}
				}
			}
			break;
		case 102: /*SaveListContentsH*/
		case 96: /*SaveListContents*/
			retint=-1;
			if (!m_VirtualData)
			if (*pos!=0)
			{
				char *postmpcc=new char [(int)strlen(pos)+10];
				strcpy(postmpcc,pos);
				int nFile=0;
				int i,j,CurLen=0,nItem=GetItemCount();
				int nCol=GetHeaderCtrl()->GetItemCount();
				int Left,Right,Top,Bottom;
				Left=Right=Top=Bottom=-1;
				char *pos2=strchr(postmpcc+1,',');
				if (pos2!=NULL) *(pos2++)=0; else pos2="";
				m_LastScanf=sscanf(pos2,"%d,%d,%d,%d,%d",&nFile,&Left,&Top,&Right,&Bottom);

				if (nFile>=0 && nFile<GP_NFILES &&GPC.m_View->aGP_File[nFile]!=NULL)
				{
					char *poscol=strchr(pos2,';');
					char *buff=new char [10000];
					int *colarr=NULL,nOutCol=0;

					if (Left<0) Left=0;
					if (Right<Left || Right>nCol ) Right=nCol;
					if (Top<0) Top=0;
					if (Bottom<Top || Bottom>=nItem ) Bottom=nItem-1;

					if (poscol!=NULL)
					{
						nOutCol=CountOccurence(poscol,",");
						if (nOutCol>0 && nOutCol<10000)
						{
							colarr=new int [nOutCol+5];

							for(i=0;i<nOutCol && poscol!=NULL;i++)
							{
								if ((colarr[i]=atoi(++poscol))<0 || colarr[i]>=nCol || colarr[i]<Left || colarr[i]>Right)
									{nOutCol--,i--;}
								poscol=strchr(poscol,';');
							}

							if (nOutCol<=0) {delete[] colarr; colarr=NULL;}
						}
					}
					UINT tmpConvON=GPC.m_View->aGP_File[nFile]->ConvON;
					if ((tmpConvON&1)==1)GPC.m_View->aGP_File[nFile]->ConvON^=1;
					retint=0;

					if (nfunc==102) /*SaveListContentsH*/
					{
						CHeaderCtrl *tmpH=GetHeaderCtrl();
						HDITEM hdi={0};
						hdi.cchTextMax=9990;
						hdi.mask=HDI_TEXT;
						hdi.pszText=buff;

						if (colarr!=NULL)
							for(j=0;j<nOutCol;j++)
							{
								if (j!=nOutCol-1 && j!=0)GPC.m_View->aGP_File[nFile]->GPWriteBlock(postmpcc);
								tmpH->GetItem(colarr[j],&hdi);
								if (*buff!=0)
									GPC.m_View->aGP_File[nFile]->GPWriteBlock(buff);
							}
						else
							for(j=Left;j<Right;j++)
							{
								if (j!=Right && j!=Left)GPC.m_View->aGP_File[nFile]->GPWriteBlock(postmpcc);
								tmpH->GetItem(j,&hdi);
								if (*buff!=0)
									GPC.m_View->aGP_File[nFile]->GPWriteBlock(buff);
							}
						GPC.m_View->aGP_File[nFile]->GPPutStr("");
					}

					for(i=Top;i<=Bottom;i++,retint++)
					{
						if (colarr!=NULL)
							for(j=0;j<nOutCol;j++)
							{
								if (j!=nOutCol-1 && j!=0)GPC.m_View->aGP_File[nFile]->GPWriteBlock(postmpcc);
								CurLen=GetItemText(i,colarr[j],buff,9990);
								if (CurLen>=0)
								{
									buff[CurLen]=0;
									GPC.m_View->aGP_File[nFile]->GPWriteBlock(buff);
								}
							}
						else
							for(j=Left;j<=Right;j++)
							{
								if (j!=Right && j!=Left)GPC.m_View->aGP_File[nFile]->GPWriteBlock(postmpcc);
								CurLen=GetItemText(i,j,buff,9990);
								if (CurLen>=0)
								{
									buff[CurLen]=0;
									GPC.m_View->aGP_File[nFile]->GPWriteBlock(buff);
								}
							}
						GPC.m_View->aGP_File[nFile]->GPPutStr("");
					}

					if ((tmpConvON&1)==1)GPC.m_View->aGP_File[nFile]->ConvON^=1;
					if (colarr!=NULL) delete[] colarr;
					if (buff!=NULL) delete[] buff;
				}
				delete[] postmpcc;
			}
			break;
		case 99: /*GetImageList*/
			if (oStr!=NULL)
			{
				UINT type=0;
				if (_stricmp(pos,"SMALL")==0)  type=LVSIL_SMALL;
					else
					if (_stricmp(pos,"STATE")==0)  type=LVSIL_STATE;
						else type=LVSIL_NORMAL;
				int id=GPC.FindImageList(GetImageList(type));
				if (id>=0) strcpy(oStr,GPC.a_GPImageList[id].ILName);
			}
			break;
		case 100: /*SetImageList*/
			{
				const char *pos2=strchr(pos,',');
				UINT type=LVSIL_NORMAL;
				if (pos2!=NULL)
				{
					if (_stricmp(++pos2,"NORMAL")==0) type=LVSIL_NORMAL;
					else
					if (_stricmp(pos2,"SMALL")==0)  type=LVSIL_SMALL;
					else
					if (_stricmp(pos2,"STATE")==0)  type=LVSIL_STATE;
				}
				int num;
				if ((num=GPC.GetImageListId(ExtractField(pos,1,",")))>=0)
				{
					SetImageList(&(GPC.a_GPImageList[num].m_IL),type );
				}
			}
			break;
		case 101: /*FindEx*/
		case 105: /*FindNoCaseEx*/
			if (!m_VirtualData)
			{
				char *paramc[16]={"STR=","COL=","RET=","TEXT=","TEXT<","TEXT>","TEXT2=","TEXT2<","TEXT2>","NUM=","NUM<","NUM>","DATE=","DATE<","DATE>","ACTION="};
				char *ppc[16]   ={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,};
				int retcol[5]={-1,-1,-1,-1,-1,};
				int strstart=0,strend=GetItemCount()-1,tmp1,tmp2;
				int colstart=0,colend=GetHeaderCtrl()->GetItemCount()-1;
				int nCol=colend,colFlg=0;
				double numE=0,numL=0,numM=0;
				UINT ActState=0;
				BOOL ActFlag=FALSE;
				int i,j;
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				char *tmppos;
				if (nfunc==105) _strupr(pos333);
				BOOL FlagNum=FALSE,FlagDate=FALSE;
				COleDateTime oDTE,oDTL,oDTM,DTtmp;
				if (nfunc==105)	_strupr(pos333);

				for(i=0;i<16;i++)
					if ((ppc[i]=strstr(pos333,paramc[i]))!=NULL)
						ppc[i]+=(int)strlen(paramc[i]);
				for(i=0;i<16;i++)
					if (ppc[i]!=NULL)
					{
						tmppos=strchr(ppc[i],';');
						if (tmppos!=NULL) *tmppos=0;
						switch(i)
						{
						case 0:
							tmp1=strstart;tmp2=strend;
							m_LastScanf=sscanf(ppc[i],"%d,%d",&tmp1,&tmp2);
							if (tmp1>strstart && tmp1<=strend) strstart=tmp1;
							if (tmp2>strstart && tmp2<=strend) strend=tmp1;
							break;
						case 1:
							tmp1=colstart;tmp2=colend;
							m_LastScanf=sscanf(ppc[i],"%d,%d",&colstart,&colend);
							if (tmp1>colstart && tmp1<=colend) colstart=tmp1;
							if (tmp2>colstart && tmp2<=colend) colend=tmp1;
							break;
						case 2: m_LastScanf=sscanf(ppc[i],"%d,%d,%d,%d,%d",retcol,retcol+1,retcol+2,retcol+3,retcol+4);
							for(j=0;j<5;j++)
								if (retcol[j]>=nCol || retcol[j]<0) retcol[j]=-1;
							colFlg=1;
							break;
						case 9:  numE=atof(ppc[i]);FlagNum=TRUE;break;
						case 10: numL=atof(ppc[i]);FlagNum=TRUE;break;
						case 11: numM=atof(ppc[i]);FlagNum=TRUE;break;
						case 12:
							try
							{oDTE.ParseDateTime(ppc[i]);}
							catch(...)
							{
								GPC.m_ErrReport.GPWriteErrorLog("GPListCtr", "DoMethod 1965",iStr);
							}
							FlagDate=TRUE;
							break;
						case 13:
							try
							{oDTL.ParseDateTime(ppc[i]);}
							catch(...)
							{
								GPC.m_ErrReport.GPWriteErrorLog("GPListCtr", "DoMethod 1974",iStr);
							}
							FlagDate=TRUE;
							break;
						case 14:
							try
							{oDTM.ParseDateTime(ppc[i]);}
							catch(...)
							{
								GPC.m_ErrReport.GPWriteErrorLog("GPListCtr", "DoMethod 1983",iStr);
							}
							FlagDate=TRUE;
							break;
						case 15: // ACTION
							{
								ActFlag=TRUE;
								char *cAct[5]={"AC_CHECK","AC_UNCHECK","AC_SELECT","AC_DESELECT","AC_DELETE",};
								UINT  uAct[5]={		0x1	,		0x2	,		0x4	,	0x8			,	0x10	,};
								_strupr(ppc[i]);
								int ii;
								for(ii=0;ii<5;ii++)
									if (strstr(ppc[i],cAct[ii])!=NULL) ActState|=uAct[ii];
							}
							break;
						}
					}

				int CurLen=0;
				BOOL yesno;
				double tmpNum=0;
				char *buff=new char [10000];
				char *posoStr=oStr;

				int str;
				for(str=strstart;str<=strend;str++)
				{
					yesno=TRUE;
					int col;
					for(col=colstart;col<=colend && yesno==TRUE;col++)
					{
						CurLen=GetItemText(str,col,buff,9990);
						buff[CurLen]=0;
						if (nfunc==105)
						{
							_strupr(buff);
						}
						if (FlagNum==TRUE) tmpNum=atof(buff);
						if (FlagDate==TRUE)
							try
							{DTtmp.ParseDateTime(buff);}
							catch(...)
							{
								GPC.m_ErrReport.GPWriteErrorLog("GPListCtr", "DoMethod ",iStr);
							}

							for(i=3;i<15;i++)
							if (ppc[i]!=NULL)
								switch(i)
								{
								case 6:
								case 3: if (strstr(buff,ppc[i])==NULL) yesno=FALSE;		break;
								case 7:
								case 4: if (strcmp(buff,ppc[i])>=0) yesno=FALSE;		break;
								case 8:
								case 5: if (strcmp(buff,ppc[i])<=0) yesno=FALSE;		break;
								case 9:  if (tmpNum!=numE) yesno=FALSE;			break;
								case 10: if (tmpNum>=numL) yesno=FALSE;			break;
								case 11: if (tmpNum<=numM) yesno=FALSE;			break;
								case 12: if (DTtmp!=oDTE) yesno=FALSE;			break;
								case 13: if (DTtmp>=oDTL) yesno=FALSE;			break;
								case 14: if (DTtmp<=oDTM) yesno=FALSE;			break;
								}
					}

					if (yesno==TRUE)
					{
						if (posoStr!=NULL)
						{
							if (posoStr!=oStr) *(posoStr++)=127;
							posoStr+=sprintf(posoStr,"%d\x07",str);
							if (colFlg==0)
								for(j=0;j<=nCol;j++)
								{
									CurLen=GetItemText(str,j,posoStr,9990);
									posoStr[CurLen++]=7;
									posoStr[CurLen]=0;
									posoStr+=CurLen;
								}
							else
								for(j=0;j<5;j++)
								if (retcol[j]>=0)
								{
									CurLen=GetItemText(str,retcol[j],posoStr,9990);
									posoStr[CurLen++]=7;
									posoStr[CurLen]=0;
									posoStr+=CurLen;
								}
						}
						if (ActFlag)
						{
							if (ActState&0x10)
							{
								DeleteItem(str--);
								strend--;
							}
							else
							{
								if (ActState&0x1) SetCheck(str,TRUE);
								if (ActState&0x2) SetCheck(str,FALSE);
								if (ActState&0x4) SetItemState(str,LVIS_SELECTED,LVIS_SELECTED);
								if (ActState&0x8) SetItemState(str,0,LVIS_SELECTED);
								if (ActState&0x20) SetItemState(str,LVIS_CUT,LVIS_CUT);
								if (ActState&0x40) SetItemState(str,0,LVIS_CUT);
							}
						}
					}
				}
				delete[] buff;
				delete[] pos333;
			}
			break;
		case 103: /*SHImageList*/
			{
				CHeaderCtrl *tmpH=GetHeaderCtrl();
				int num=GPC.GetImageListId(pos);
				if (num>=0)	tmpH->SetImageList(&(GPC.a_GPImageList[num].m_IL));
			}
			break;
		case 104: /*SHItem*/
			{
				char *aFormatName[7]={"HDF_CENTER|","HDF_LEFT|","HDF_RIGHT|","HDF_RTLREADING|","HDF_BITMAP_ON_RIGHT|","_IMAGE|","_TEXT|",};
				UINT aFormatUINT[7]={HDF_CENTER,HDF_LEFT,HDF_RIGHT,HDF_RTLREADING,HDF_BITMAP_ON_RIGHT,HDF_IMAGE,HDF_STRING,};
				char *aMaskName[5]={"_FORMAT|","_HEIGHT|","_IMAGE|","_TEXT|","_WIDTH|",};
				UINT aMaskUINT[5]={HDI_FORMAT,HDI_HEIGHT,HDI_IMAGE,HDI_TEXT,HDI_WIDTH,};
				CHeaderCtrl *tmpH=GetHeaderCtrl();
				int height=0;
				int position=0;
				UINT tmpMask=0;
				HDITEM hdi={0};
				m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&position,&hdi.cxy,&height,&hdi.iImage);
				hdi.mask=hdi.fmt=0;
				int i;
				for(i=0;i<7;i++)
					if (strstr(pos,aFormatName[i])!=NULL) hdi.fmt|=aFormatUINT[i];
				for(i=0;i<5;i++)
					if (strstr(pos,aMaskName[i])!=NULL)
					{
						if (i!=1) hdi.mask|=aMaskUINT[i];
						else tmpMask=HDI_HEIGHT;
					}

				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				char *pss=pos333;
				pss=strchr(pss,';');

				if (pss==NULL) pss=""; else pss++;
				hdi.pszText=pss;

				tmpH->SetItem(position,&hdi);
				if (tmpMask!=0)
				{
					hdi.mask=tmpMask;
					tmpH->SetItem(position,&hdi);
				}
				delete[] pos333;
			}
			break;
		case 106: /*SelectAll*/
		case 107: /*DeSelectAll*/
			if (!m_VirtualData)
			{
				int i,nItem=GetItemCount();
				BOOL sev=GPC.StopEventsFlag;
				GPC.StopEventsFlag=TRUE;
				UINT state=LVIS_SELECTED;
				if (nfunc==107) state=0;
				for(i=0;i<nItem;i++)
					SetItemState(i,state,LVIS_SELECTED);

				GPC.StopEventsFlag=sev;
			}
			break;
		case 108: /*SelectionDelete*/
		case 109: /*SelectionCheck*/
		case 111: /*SelectionSetItem*/
		case 112: /*SelectionSetItemText*/
		case 113: /*SelectionSetItemState*/
		case 114: /*SelectionDoMethod*/
			if (!m_VirtualData)
			{
				BOOL sev=GPC.StopEventsFlag;
				GPC.StopEventsFlag=TRUE;
				POSITION posit = GetFirstSelectedItemPosition();
				switch(nfunc)
				{
				case 108:/*SelectionDelete*/
					while(posit)
					{
						DeleteItem(GetNextSelectedItem(posit));
						posit = GetFirstSelectedItemPosition();
					}
					break;
				case 109:/*SelectionCheck*/
					{
						int checktmp=atoi(pos);
						while(posit)
							SetCheck(GetNextSelectedItem(posit),checktmp);
					}
					break;
				case 111: /*SelectionSetItem*/
				case 112: /*SelectionSetItemText*/
				case 113: /*SelectionSetItemState*/
					{
						char *newstate=new char [(int)strlen(pos)+100];
						char *nmMethod[3]={"SetItemEx","SetItemText","SetItemState",};
						while(posit)
						{
							sprintf(newstate,"%s %d,%s",nmMethod[nfunc-111],GetNextSelectedItem(posit),pos);
							DoMethod(newstate,NULL);
						}
						delete[] newstate;
					}
					break;
				case 114: /*SelectionDoMethod*/
					{
						char *postmpcc=new char [(int)strlen(pos)+10];
						strcpy(postmpcc,pos);
						char *posstr=oStr;
						char *selmet=new char [(int)strlen(postmpcc)+100];
						char *pos2=strchr(postmpcc,' ');
						if (!pos2) pos2="";
						else 
						{
							*(pos2++)=0;
							while(*pos2==' ') pos2++;
						}

						while(posit)
						{
							sprintf(selmet,"%s %d,%s",postmpcc,GetNextSelectedItem(posit),pos2);
							DoMethod(selmet,posstr);
							if (posstr!=NULL)
							{
								if (posit) strcat(posstr,"\x06");
								posstr+=(int)strlen(posstr);
							}
						}
						delete[] selmet;
						delete[] postmpcc;
					}
					break;
				}

				GPC.StopEventsFlag=sev;
			}
			break;
		case 110: /*SelectionInvert*/
			if (!m_VirtualData)
			{
				int i,nItem=GetItemCount();
				BOOL sev=GPC.StopEventsFlag;
				GPC.StopEventsFlag=TRUE;
				UINT state;
				for(i=0;i<nItem;i++)
				{
					state=GetItemState(i,LVIS_SELECTED);
					state^=LVIS_SELECTED;
					SetItemState(i,state,LVIS_SELECTED);
				}

				GPC.StopEventsFlag=sev;
			}
			break;
		case 115: /*SetSelection*/
			if (!m_VirtualData)
			{
				int nItemAll=GetItemCount();
				DoMethod("DeSelectAll",NULL);
				int nItem=0;
				while(*pos!=0)
				{
					nItem=atoi(pos);
					if ((nItem=atoi(pos))<nItemAll && nItem>=0)
						SetItemState(nItem,LVIS_SELECTED,LVIS_SELECTED);

					while(*pos>='0' && *pos<='9') pos++;

					if (*pos=='-')
					{
						int nItem2=atoi(++pos);
						while(++nItem<nItemAll && nItem<=nItem2 && nItem>=0)
							SetItemState(nItem,LVIS_SELECTED,LVIS_SELECTED);

						while(*pos>='0' && *pos<='9') pos++;
					}
					if (*pos==',') pos++;
				}
			}
		case 116: /*SetEditPosParam*/
			{
				int i;
				for(i=0;i<1000;i++)	iArrPosExOut[i]=-1;
				const char *pos2=pos;

				for(i=0;i<1000 && *pos2!=0;i++)
				{
					iArrPosExOut[i]=atoi(pos2);
					while(*pos2!=0 && *pos2!=',' && *pos2!=GPC.DelimiterIn1 && *pos2!=';') pos2++;
					if (*pos2!=0) pos2++;
				}
			}
			break;
		case 117: /*FillFromSpr*/
		case 118: /*AddFromSpr*/
			if (!m_VirtualData)
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				char *tmp=pos333,*tmp2;
				tmp2=strchr(tmp,',');
				if (tmp2!=NULL) *(tmp2++)=0;
				else tmp2="";
				CGPSpr *spr=GPC.m_SprArray.GetSpr(tmp);
				if (spr!=NULL) retint=spr->FillObject(m_hWnd,GPSPRFILL_LISTCTRL|GPSPRFILL_USEDATA,tmp2,nfunc==117?0:1);
				delete[] pos333;
			}
			break;
		case 119: /*ReplaceFromSpr*///"StartItem,EndItem,SprName1,nCodeCol1,nReplCol1,nFindField1,nTextField1,Prefix1^SprName2,nCodeCol2,nReplCol2,nFindField2,nTextField2,Prefix1...",
			if (!m_VirtualData)
			{
				long StartItem=0,EndItem=-1;
				m_LastScanf=sscanf(pos,"%ld,%ld",&StartItem,&EndItem);
				const char *tmp=pos;
				while(*tmp!=0 && *tmp!=',') tmp++;
				if (*tmp!=0) tmp++;
				if (*tmp!=0)
					while(*tmp!=0 && *tmp!=',') tmp++;
				if (*tmp!=0) tmp++;

				retint=GPC.m_SprArray.ReplaceOblectEx(m_hWnd,GPSPRFILL_LISTCTRL|GPSPRFILL_USEDATA,StartItem,EndItem,tmp);
			}
			break;
		case 120: /*DeleteAllColumns*/
			{

				CHeaderCtrl *tmp=GetHeaderCtrl();
				if (tmp!=NULL)
				{
					int nItem=tmp->GetItemCount();
					while(nItem>0)
					{
						DeleteColumn(--nItem);
						if (m_VirtualData) m_VirtualData->DeleteColumn(nItem);
					}
				}
			}
			break;
		case 121: /*SetHFilter*/
			{
				CHeaderCtrl *tmp=GetHeaderCtrl();
				if (tmp!=NULL)
				{
					char *postmpcc=new char [(int)strlen(pos)+10];
					strcpy(postmpcc,pos);
					tmp->ModifyStyle(0,HDS_FILTERBAR);

					HDITEM hdi={0};
					HDTEXTFILTER tf={0};

					hdi.mask=HDI_FILTER;
					hdi.type=HDFT_ISSTRING;
					tf.cchTextMax=980;
					char *pos2=strchr(postmpcc,',');
					if (pos2!=NULL) pos2++; else pos2="";
					tf.pszText=pos2;

					hdi.pvFilter=(LPVOID) &tf;
					tmp->SetItem(atoipos,&hdi);
					Update(0);
					Invalidate();
					delete[] postmpcc;
				}
			}
			break;
		case 122: /*SetHFilters*/
			{
				CHeaderCtrl *tmp=GetHeaderCtrl();
				if (tmp!=NULL)
				{
					char *pos333=new char [(int)strlen(pos)+2];
					strcpy(pos333,pos);
					tmp->ModifyStyle(0,HDS_FILTERBAR);
					HDITEM hdi={0};
					HDTEXTFILTER tf={0};
					hdi.mask=HDI_FILTER;
					hdi.type=HDFT_ISSTRING;
					hdi.pvFilter=(LPVOID) &tf;
					tf.cchTextMax=980;

					int nStrt=atoipos;
					int nEnd=atoipos;
					if (nStrt<0)
					{
						nStrt=0;
						nEnd=tmp->GetItemCount();
					}

					int i;
					char *pos1=pos333;
					for(i=nStrt;i<nEnd;i++)
					{
						char *pos2=strchr(pos1,GPC.DelimiterIn1);
						if (pos2==NULL) pos2="";
						else *(pos2++)=0;
						tf.pszText=pos1;
						tmp->SetItem(atoipos,&hdi);
						pos1=pos2;
					}
					Update(0);
					Invalidate();
					delete[] pos333;
				}
			}
			break;
		case 123: /*SetAutoHFilter*/
			{
				CHeaderCtrl *tmp=GetHeaderCtrl();
				if (tmp)
				{
					m_AutoHFilter=atoipos;
					if (m_AutoHFilter)
					{
						tmp->ModifyStyle(0,HDS_FILTERBAR);
						DoMethod("SortItems",NULL);
					}
					else
					{
						tmp->ModifyStyle(HDS_FILTERBAR,0);
						tmp->SendMessage(HDM_CLEARFILTER,(WPARAM)tmp->m_hWnd,-1);
					}
					Update(0);
					Invalidate();
					tmp->Invalidate();
				}
			}
			break;
		case 124: /*GetAutoHFilter*/
			retint=m_AutoHFilter;
			break;
		case 125: /*DeleteHFilters*/
			{
				CHeaderCtrl *tmp=GetHeaderCtrl();
				if (tmp!=NULL)
					tmp->ModifyStyle(HDS_FILTERBAR,0);
				Update(0);
				Invalidate();
				DoMethod("SortItems",NULL);
			}
			break;
		case 126: /*ClearHFilter*/
			{
				CHeaderCtrl *tmp=GetHeaderCtrl();
				if (tmp!=NULL)
				{
					tmp->ModifyStyle(0,HDS_FILTERBAR);
					tmp->SendMessage(HDM_CLEARFILTER,(WPARAM)tmp->m_hWnd,atoipos);
				}
				Update(0);
				Invalidate();
				DoMethod("SortItems",NULL);
			}
			break;
		case 127: /*EditHFilter*/
			{
				CHeaderCtrl *tmp=GetHeaderCtrl();
				if (tmp!=NULL)
				{
					tmp->ModifyStyle(0,HDS_FILTERBAR);
					tmp->SendMessage(HDM_EDITFILTER,(WPARAM)atoipos,0);
				}
			}
			break;
		case 128: /*GetHFilter*/
			if (oStr)
			{
				CHeaderCtrl *tmp=GetHeaderCtrl();
				if (tmp!=NULL)
				{
					int nStrt=atoipos;
					int nEnd=atoipos;
					if (nStrt<0)
					{
						nStrt=0;
						nEnd=tmp->GetItemCount();
					}
					*oStr=0;
					HDITEM hdi={0};
					HDTEXTFILTER tf={0};

					hdi.mask=HDI_FILTER;
					hdi.type=HDFT_ISSTRING;
					tf.pszText=new char [1000];
					tf.cchTextMax=980;
					hdi.pvFilter=(LPVOID) &tf;

					int i;
					for(i=nStrt;i<nEnd;i++)
					{
						if (i>nStrt) strcat(oStr,"\x7F");
						*tf.pszText=0;
						tmp->GetItem(i,&hdi);
						strcat(oStr,tf.pszText);
					}
					delete[] tf.pszText;
				}
			}
			break;
		case 129: /*SetHeaderProperty*/
			{
				CHeaderCtrl *tmp=GetHeaderCtrl();
				if (tmp!=NULL && *pos)
				{
					GPHeader mGPHeader(UnitId);
					mGPHeader.referGPU=referGPU;
					mGPHeader.Attach(tmp->m_hWnd);
					mGPHeader.GPSetProperty(pos);
					mGPHeader.Detach();
				}
				Update(0);
				Invalidate();
			}
			break;
		case 130: /*DoHeaderMethod*/
			{
				CHeaderCtrl *tmp=GetHeaderCtrl();
				if (tmp!=NULL && *pos)
				{
					GPHeader mGPHeader(UnitId);
					mGPHeader.referGPU=referGPU;
					mGPHeader.Attach(tmp->m_hWnd);
					mGPHeader.DoMethod(pos,oStr);
					mGPHeader.Detach();
				}
				Update(0);
				Invalidate();
			}
			break;
		case 131: /*SetSortMark*/
			{
				CHeaderCtrl *tmp=GetHeaderCtrl();
				if (tmp!=NULL)
				{
					int nItem=0,SortState=0;
					m_LastScanf=sscanf(pos,"%d,%d",&nItem,&SortState);
					HDITEM hdi={0};
					hdi.mask=HDI_FORMAT;
					tmp->GetItem(atoipos,&hdi);
					hdi.fmt&=(0xFFFFFFFF^(HDF_SORTUP|HDF_SORTDOWN));
					if (SortState>0) hdi.fmt|=HDF_SORTUP;
					if (SortState<0) hdi.fmt|=HDF_SORTDOWN;
					tmp->SetItem(atoipos,&hdi);
				}
			}
			break;
		case 133: /*GetEditStatus*/	retint=m_EditInProgr;	break;
		case 134: /*InsertItems*/
			if (!m_VirtualData)
			{
				char *pos333=new char [(int)strlen(pos)+2];
				strcpy(pos333,pos);
				char *pos2=pos333;
				while(*pos2 && *(pos2++)!=',');
				int tmpItem=atoipos;
				do
				{
					char *postmp=pos2;
					while(*postmp && *postmp!=GPC.DelimiterIn1) postmp++;

					if (*postmp) *(postmp++)=0;

					int nSubItem=0;
					GPTextArray *ar=NULL;
					do
					{
						char *possub=pos2;
						while(*possub && *possub!=GPC.DelimiterIn2) possub++;
						if (*possub) *(possub++)=0;
						if (nSubItem)
						{
							SetItemText(tmpItem,nSubItem,pos2);
							ar->SetItem(nSubItem,pos2);
							ar->SetItemData(nSubItem++,DefEditor);
						}
						else
						{
							tmpItem=InsertItem(tmpItem,pos2,m_DefItemImage);
							ar=new GPTextArray;
							SetItemData(tmpItem,(DWORD)ar);
							ar->SetItem(0,pos2);
							ar->SetItemData(0,DefEditor);
							nSubItem++;
						}
						pos2=possub;
					}while(*pos2);
					tmpItem++;

					pos2=postmp;
				}
				while(*pos2);
				delete[] pos333;
			}
			break;
		case 135: /*NextCell*/
			{
				UINT i=0;
				char *tmps=new char [(int)strlen(pos)+10];
				strcpy(tmps,pos);
				_strupr(tmps);
				strcat(tmps,"|");
				if (*pos)
					for(i=0;i<GP_HotKey::nTypeHotkey && strstr(tmps,GP_HotKey:: aVKName[i])==NULL;i++);

				if (i<GP_HotKey::nTypeHotkey || *pos==0)
				{
					UINT j;
					for(j=0;j<GP_HotKey::nTypeModifiers && strstr(tmps,GP_HotKey::aVKMODName[j])==NULL;j++);
					DWORD wParam=0;
					if (*pos) wParam=GP_HotKey:: aVKUINT[i];
					if (j<GP_HotKey::nTypeModifiers) wParam|=GP_HotKey::aVKMODUINT[j];
					SendMessage(GPM_NEXTCELL,wParam,0);
				}
			}
			break;
		case 136: /*GetColumnCount*/
			{
				CHeaderCtrl *tmp=GetHeaderCtrl();
				if (tmp)
					retint=tmp->GetItemCount();
			}
			break;
		case 137: /*CancelEditLabel*/
				retint=SendMessage(LVM_CANCELEDITLABEL,0,0);
			break;
		case 138: /*EnableGroupView*/
				retint=SendMessage(LVM_ENABLEGROUPVIEW,(WPARAM)atoipos,0);
			break;
		case 139: /*GetGroupInfo*/
			if (oStr)
			{
				LVGROUP lvg={0};
				lvg.cbSize=sizeof(lvg);
				lvg.cchHeader=5000;
				lvg.pszHeader=(LPWSTR)new unsigned short [lvg.cchHeader];
				*lvg.pszHeader=0;
				lvg.iGroupId=atoipos;
				lvg.mask=StringToGrMask(NULL);
				lvg.stateMask=StringToGrState(NULL);

				if (SendMessage(LVM_GETGROUPINFO,(WPARAM)atoipos,(LPARAM)&lvg)!=-1)
				{
					CString tmps(lvg.pszHeader);

					sprintf(oStr,"%d\x7F%s\x7F%s\x7F%s",
						lvg.iGroupId,
						(LPCSTR)GrStateToString(lvg.state),
						(LPCSTR)GrAlignToString(lvg.uAlign),
						(LPCSTR)tmps
						);
				}
				delete[] lvg.pszHeader;
			}
			break;
		case 140: /*GetGroupMetrics*/
			if (oStr)
			{
				LVGROUPMETRICS lvg={0};
				lvg.cbSize=sizeof(lvg);
				lvg.mask=LVGMF_BORDERCOLOR|LVGMF_BORDERSIZE|LVGMF_TEXTCOLOR;


				SendMessage(LVM_GETGROUPMETRICS,(WPARAM)atoipos,(LPARAM)&lvg);
				sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d\x7F%d\x07%d\x07%d\x7F%d\x07%d\x07%d\x7F%d\x07%d\x07%d\x7F%d\x07%d\x07%d\x7F%d\x07%d\x07%d\x7F%d\x07%d\x07%d",
						lvg.Left,
						lvg.Top,
						lvg.Right,
						lvg.Bottom,
						GetRValue(lvg.crLeft),GetGValue(lvg.crLeft),GetBValue(lvg.crLeft),
						GetRValue(lvg.crTop),GetGValue(lvg.crTop),GetBValue(lvg.crTop),
						GetRValue(lvg.crRight),GetGValue(lvg.crRight),GetBValue(lvg.crRight),
						GetRValue(lvg.crBottom),GetGValue(lvg.crBottom),GetBValue(lvg.crBottom),
						GetRValue(lvg.crHeader),GetGValue(lvg.crHeader),GetBValue(lvg.crHeader),
						GetRValue(lvg.crFooter),GetGValue(lvg.crFooter),GetBValue(lvg.crFooter)
						);
			}
			break;
		case 141: /*GetInsertMark*/
			if (oStr)
			{
				LVINSERTMARK lvg={0};
				lvg.cbSize=sizeof(lvg);
				lvg.dwFlags=(atoipos)?LVIM_AFTER:0;

				SendMessage(LVM_GETINSERTMARKRECT,0,(LPARAM)&lvg);
				retint=lvg.iItem;
			}
			break;
		case 142: /*GetInsertMarkColor*/
			if (oStr)
			{
				COLORREF clr=SendMessage(LVM_GETINSERTMARKCOLOR,0,0);
				sprintf(oStr,"%d\x7F%d\x7F%d",GetRValue(clr),GetGValue(clr),GetBValue(clr));
			}
			break;
		case 143: /*GetInsertMarkRect*/
			if (oStr)
			{
				RECT re={0};
				SendMessage(LVM_GETINSERTMARKCOLOR,0,(LPARAM)&re);
				sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
			}
			break;
		case 144: /*GetISearchString*/
			if (oStr)
			{
				int len=SendMessage(LVM_GETISEARCHSTRING,0,0);
				sprintf(oStr,"%d\x7F",len);
				SendMessage(LVM_GETISEARCHSTRING,0,(LPARAM)(oStr+(int)strlen(oStr)));
			}
			break;
		case 145: /*GetItemSpacing*/
			if (oStr)
			{
				DWORD sm=SendMessage(LVM_GETITEMSPACING,(WPARAM)TRUE,0);
				DWORD lr=SendMessage(LVM_GETITEMSPACING,(WPARAM)FALSE,0);
				sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",LOWORD(sm),HIWORD(sm),LOWORD(lr),HIWORD(lr));
			}
			break;
		case 146: /*GetOutlineColor*/
			if (oStr)
			{
				COLORREF clr=SendMessage(LVM_GETOUTLINECOLOR,0,0);
				sprintf(oStr,"%d\x7F%d\x7F%d",GetRValue(clr),GetGValue(clr),GetBValue(clr));
			}
			break;
		case 147: /*GetSelectedColumn*/
			retint=SendMessage(LVM_GETSELECTEDCOLUMN,0,0);
			break;
		case 148: /*GetTileInfo*/
			if (oStr)
			{
				UINT nCol=GetHeaderCtrl()->GetItemCount();
				LVTILEINFO lvg={0};
				lvg.cbSize=sizeof(lvg);
				lvg.iItem=atoipos;
				lvg.puColumns=new UINT [nCol+10];
				lvg.cColumns =nCol;
				SendMessage(LVM_GETTILEINFO,0,(LPARAM)&lvg);
				CString tmps,tmps2;
				if (lvg.cColumns && lvg.puColumns)
				{
					UINT i;
					for(i=0;i<lvg.cColumns;i++)
					{
						tmps2.Format("%d",lvg.puColumns[i]);
						if (i)	tmps+="\x07";
						tmps+=tmps2;
					}
				}
				if (lvg.puColumns) delete[] lvg.puColumns;
				sprintf(oStr,"%d\x7F%d\x7F%s", lvg.iItem, lvg.cColumns, (LPCSTR)tmps);
			}
			break;
		case 149: /*GetTileViewInfo*/
			if (oStr)
			{
				LVTILEVIEWINFO lvg={0};
				lvg.cbSize=sizeof(lvg);
				lvg.dwMask=LVTVIM_TILESIZE|LVTVIM_COLUMNS|LVTVIM_LABELMARGIN;
				SendMessage(LVM_GETTILEVIEWINFO,0,(LPARAM)&lvg);
				sprintf(oStr,"%s\x7F%d\x07%d\x7F%d\x7F%d\x07%d\x07%d\x07%d",
					(lvg.dwFlags==LVTVIF_FIXEDWIDTH)?"LVTVIF_FIXEDWIDTH":(lvg.dwFlags==LVTVIF_AUTOSIZE)?"LVTVIF_AUTOSIZE":(lvg.dwFlags==LVTVIF_FIXEDHEIGHT)?"LVTVIF_FIXEDHEIGHT":(lvg.dwFlags==LVTVIF_FIXEDSIZE)?"LVTVIF_FIXEDSIZE":"",
					lvg.sizeTile.cx,lvg.sizeTile.cy,
					lvg.cLines,
					lvg.rcLabelMargin.left,lvg.rcLabelMargin.top,lvg.rcLabelMargin.right,lvg.rcLabelMargin.bottom
					);
			}
			break;
		case 150: /*GetUnicodeFormat*/
			retint=SendMessage(LVM_GETUNICODEFORMAT,0,0);
			break;
		case 151: /*GetView*/
			if (oStr)
				strcpy(oStr,LViewToString(SendMessage(LVM_GETVIEW,0,0)));;
			break;
		case 152: /*HasGroup*/
			retint=SendMessage(LVM_HASGROUP,atoipos,0);
			break;
		case 153: /*SetInsertMark*/
			{
				LVINSERTMARK lvg={0};
				lvg.cbSize=sizeof(lvg);
				m_LastScanf=sscanf(pos,"%d,%d",&lvg.iItem,&atoipos);
				lvg.dwFlags=(atoipos)?LVIM_AFTER:0;
				retint=SendMessage(LVM_SETINSERTMARK,0,(LPARAM)&lvg);
			}
			break;
		case 154: /*SetInsertMarkColor*/
			{
				UINT R=0,G=0,B=0;
				m_LastScanf=sscanf(pos,"%d,%d,%d",&R,&G,&B);
				COLORREF clr=RGB(R,G,B);
				clr=SendMessage(LVM_SETINSERTMARKCOLOR,0,(LPARAM)&clr);
				if (oStr)
					sprintf(oStr,"%d\x7F%d\x7F%d",GetRValue(clr),GetGValue(clr),GetBValue(clr));
			}
			break;
		case 155: /*SetOutlineColor*/
			{
				UINT R=0,G=0,B=0;
				m_LastScanf=sscanf(pos,"%d,%d,%d",&R,&G,&B);
				COLORREF clr=RGB(R,G,B);
				clr=SendMessage(LVM_SETOUTLINECOLOR,0,(LPARAM)&clr);
				if (oStr)
					sprintf(oStr,"%d\x7F%d\x7F%d",GetRValue(clr),GetGValue(clr),GetBValue(clr));
			}
			break;
		case 156: /*SetSelectedColumn*/
			SendMessage(LVM_SETSELECTEDCOLUMN,atoipos,0);
			break;
		case 157: /*InsertGroup iItem,iGroup,state,TEXT*/
			if (!m_VirtualData)
			if (oStr)
			{
				LVGROUP lvg={0};
				lvg.cbSize=sizeof(lvg);
				lvg.mask=StringToGrMask(NULL);
				lvg.stateMask=StringToGrState(NULL);
				const char *pos2=strchr(pos,',');
				if (pos2++) lvg.iGroupId=atoi(pos2);
				else pos2="";
				pos2=strchr(pos2,',');
				if (pos2++) lvg.state=StringToGrState(pos2);
				else pos2="";
				pos2=strchr(pos2,',');
				if (pos2++==NULL) pos2="";

				CString tmps=pos2;
				lvg.pszHeader=tmps.AllocSysString();
				lvg.cchHeader=wcslen(lvg.pszHeader);

				retint=SendMessage(LVM_INSERTGROUP,(WPARAM)atoipos,(LPARAM)&lvg);
				::SysFreeString(lvg.pszHeader);
			}
			break;
		case 158: /*InsertMarkHitTest x,y,iGroup,state*/
			if (oStr)
			{

				LVINSERTMARK lvg={0};
				POINT po={0};
				m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&po.x,&po.y,&lvg.iItem,&atoipos);

				lvg.cbSize=sizeof(lvg);
				lvg.dwFlags=(atoipos)?LVIM_AFTER:0;
				retint=SendMessage(LVM_INSERTMARKHITTEST,(WPARAM)&po,(LPARAM)&lvg);
			}
			break;
		case 159: /*IsGroupViewEnabled*/
			retint=SendMessage(LVM_ISGROUPVIEWENABLED,0,0);
			break;
		case 160: /*MapIdToIndex*/
			retint=SendMessage(LVM_MAPIDTOINDEX,(UINT)atoipos,0);
			break;
		case 161: /*MapIndexToId*/
			retint=SendMessage(LVM_MAPINDEXTOID,(UINT)atoipos,0);
			break;
		case 162: /*MoveGroup iGroupId,ToIndex*/
			if (!m_VirtualData)
			{
				int iGroupId=0,ToIndex=0;
				m_LastScanf=sscanf(pos,"%d,%d",&iGroupId,&ToIndex);
				SendMessage(LVM_MOVEGROUP,(WPARAM)iGroupId,(LPARAM)ToIndex);
			}
			break;
		case 163: /*MoveItemToGroup idItemFrom,idGroupTo*/
			{
				int idItemFrom=0,idGroupTo=0;
				m_LastScanf=sscanf(pos,"%d,%d",&idItemFrom,&idGroupTo);
				SendMessage(LVM_MOVEITEMTOGROUP,(WPARAM)idItemFrom,(LPARAM)idGroupTo);
			}
			break;
		case 164: /*RemoveAllGroups*/
			if (!m_VirtualData)
			retint=SendMessage(LVM_REMOVEALLGROUPS,0,0);
			break;
		case 165: /*RemoveGroup*/
			if (!m_VirtualData)
			retint=SendMessage(LVM_REMOVEGROUP,(UINT)atoipos,0);
			break;
		case 166: /*SetGroupInfo iGroupId,state,uAlign,TEXT*/
			if (!m_VirtualData)
			{
				LVGROUP lvg={0};
				lvg.cbSize=sizeof(lvg);

				lvg.mask=StringToGrMask(NULL);
				lvg.stateMask=StringToGrState(NULL);

				CString tmps=FindField(pos,3,",");
				lvg.pszHeader=tmps.AllocSysString();
				lvg.cchHeader=wcslen(lvg.pszHeader);
				lvg.iGroupId=atoipos;
				retint=SendMessage(LVM_SETGROUPINFO,(WPARAM)atoipos,(LPARAM)&lvg);
				::SysFreeString(lvg.pszHeader);
			}
			break;
		case 167: /*SetGroupBorderClr IdGroup,RLeft,GLeft,BLeft,RTop,GTop,BTop,RRight,GRight,BRight,RBottom,GBottom,BBottom*/
			{
				LVGROUPMETRICS lvg={0};
				lvg.cbSize=sizeof(lvg);
				lvg.mask=LVGMF_BORDERCOLOR;

				int Rl=0,Gl=0,Bl=0,Rt=0,Gt=0,Bt=0,Rr=0,Gr=0,Br=0,Rb=0,Gb=0,Bb=0;
				m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",&atoipos,&Rl,&Gl,&Bl,&Rt,&Gt,&Bt,&Rr,&Gr,&Br,&Rb,&Gb,&Bb);

				lvg.crLeft=RGB(Rl,Gl,Bl);
				lvg.crTop=RGB(Rt,Gt,Bt);
				lvg.crRight=RGB(Rr,Gr,Br);
				lvg.crBottom=RGB(Rb,Gb,Bb);

				SendMessage(LVM_SETGROUPMETRICS,(WPARAM)atoipos,(LPARAM)&lvg);
			}
			break;
		case 168: /*SetGroupBorderSize IdGroup,Left,Top,Right,Bottom*/
			{
				LVGROUPMETRICS lvg={0};
				lvg.cbSize=sizeof(lvg);
				lvg.mask=LVGMF_BORDERSIZE;

				m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d",&atoipos,&lvg.Left,&lvg.Top,&lvg.Right,&lvg.Bottom);

				SendMessage(LVM_SETGROUPMETRICS,(WPARAM)atoipos,(LPARAM)&lvg);
			}
			break;
		case 169: /*SetGroupTextClr IdGroup,RHeader,GHeader,BHeader,RFooter,GFooter,BFooter*/
			{
				LVGROUPMETRICS lvg={0};
				lvg.cbSize=sizeof(lvg);
				lvg.mask=LVGMF_TEXTCOLOR;
				int Rl=0,Gl=0,Bl=0,Rt=0,Gt=0,Bt=0;
				m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d,%d,%d",&atoipos,&Rl,&Gl,&Bl,&Rt,&Gt,&Bt);

				lvg.crHeader=RGB(Rl,Gl,Bl);
				lvg.crFooter=RGB(Rt,Gt,Bt);

				SendMessage(LVM_SETGROUPMETRICS,(WPARAM)atoipos,(LPARAM)&lvg);
			}
			break;
		case 170: /*SetInfoTip iItem,iSubItem,Flags,TEXT*/
			{

				LVSETINFOTIP lvg={0};
				lvg.cbSize=sizeof(lvg);

				m_LastScanf=sscanf(pos,"%d,%d,%d",&lvg.iItem,&lvg.iSubItem,&lvg.dwFlags);

				CString tmps=FindField(pos,3,",");
				lvg.pszText=tmps.AllocSysString();
				retint=SendMessage(LVM_SETINFOTIP,0,(LPARAM)&lvg);
				::SysFreeString(lvg.pszText);
			}
			break;
		case 171: /*SetItemPosition32 iItem,X,Y*/
			if (!m_VirtualData)
			{
				int iItem=0;
				POINT po={0};
				m_LastScanf=sscanf(pos,"%d,%d,%d",&iItem,&po.x,&po.y);
				SendMessage(LVM_SETITEMPOSITION32,(WPARAM)iItem,(LPARAM)&po);
			}
			break;
		case 172: /*SetTileInfo iItem,cColumns,Index1,Index2,....*/
			{
				LVTILEINFO lvg={0};
				lvg.cbSize=sizeof(lvg);
				m_LastScanf=sscanf(pos,"%d,%d",&lvg.iItem,&lvg.cColumns);

				if (lvg.cColumns<1000)
				{
					const char *pos2=FindField(pos,2,",");
					lvg.puColumns=new UINT [lvg.cColumns+10];

					UINT i;
					for(i=0;i<lvg.cColumns;i++)
					{
						if (pos2)
						{
							lvg.puColumns[i]=atoi(pos2);
							pos2=strchr(pos2,',');
							if ((pos2++)==NULL) pos2="0";
						}
						else
						lvg.puColumns[i]=0;
					}

					retint=SendMessage(LVM_SETTILEINFO,0,(LPARAM)&lvg);
					delete[] lvg.puColumns;
				}
			}
			break;
		case 173: /*SetTileViewInfo sizex,sizey,cLines,MrgnLeft,MrgnTop,MrgnRight,MrgnBottom,Flag*/
			if (oStr)
			{
				LVTILEVIEWINFO lvg={0};
				lvg.cbSize=sizeof(lvg);
				lvg.dwMask=LVTVIM_TILESIZE|LVTVIM_COLUMNS|LVTVIM_LABELMARGIN;

				m_LastScanf=sscanf(pos,"%d,%d,%d,%d,%d,%d,%d",
					&lvg.sizeTile.cx,&lvg.sizeTile.cy,
					&lvg.cLines,
					&lvg.rcLabelMargin.left,
					&lvg.rcLabelMargin.top,
					&lvg.rcLabelMargin.right,
					&lvg.rcLabelMargin.bottom);
				if (strstr(pos,"LVTVIF_FIXEDWIDTH")) lvg.dwFlags=LVTVIF_FIXEDWIDTH;
				if (strstr(pos,"LVTVIF_AUTOSIZE")) lvg.dwFlags=LVTVIF_AUTOSIZE;
				if (strstr(pos,"LVTVIF_FIXEDHEIGHT")) lvg.dwFlags=LVTVIF_FIXEDHEIGHT;
				if (strstr(pos,"LVTVIF_FIXEDSIZE")) lvg.dwFlags=LVTVIF_FIXEDSIZE;

				retint=SendMessage(LVM_SETTILEVIEWINFO,0,(LPARAM)&lvg);
			}
			break;
		case 174: /*SetUnicodeFormat bFormat*/
			retint=SendMessage(LVM_SETUNICODEFORMAT,(WPARAM)atoipos,0);
			break;
		case 175: /*SetView bViewType*/
			retint=SendMessage(LVM_SETVIEW,(WPARAM)StringToLView(pos),0);
			break;
		case 176: /*SortGroupsAsNum nColumn,vkDirection*/
		case 177: /*SortGroupsAsDate nColumn,vkDirection*/
		case 178: /*SortGroups nColumn,vkDirection*/
			if (!m_VirtualData)
			{
				SortColumnNumber=atoipos;
				DESCENDSort=strstr(pos,"DES")!=NULL?TRUE:FALSE;
				nFilterArrayCount=FilterArray->GetItemCount();
				if ((m_EditInProgr&0x1)!=0 && hti.iItem!=-1 && hti.iSubItem!=-1)
					SetItemState(hti.iItem,LVIS_SELECTED,LVIS_SELECTED|LVIS_FOCUSED|LVIS_ACTIVATING );

				while(nFilterArrayCount>=0 &&(FilterArray->GetItem(nFilterArrayCount)==NULL || *((char *)FilterArray->GetItem(nFilterArrayCount))==0))
					nFilterArrayCount--;

				DWORD tmp;

				if (nfunc==178)	retint=SendMessage(LVM_SORTGROUPS, (WPARAM)&mCompareFunc,(DWORD)(&tmp));
				else
				if (nfunc==176)	retint=SendMessage(LVM_SORTGROUPS, (WPARAM)&mCompareFuncNum,(DWORD)(&tmp));
				else
				if (nfunc==177)	retint=SendMessage(LVM_SORTGROUPS, (WPARAM)&mCompareFuncDate,(DWORD)(&tmp));

				if ((m_EditInProgr&0x1)!=0  && hti.iItem!=-1 && hti.iSubItem!=-1)
				{
					POSITION pos22 = GetFirstSelectedItemPosition();
					if (pos22 != NULL)
					{
						lasthti.iItem= hti.iItem = GetNextSelectedItem(pos22);
						SetItemState(hti.iItem,0,LVIS_SELECTED|LVIS_FOCUSED|LVIS_ACTIVATING );
						SetEditRect();
					}
				}
			}
			break;
		case 181: /*SetCaseSensitive LVCS_SORT|LVCS_FILTER*/
			retint=m_CSFlag;
			m_CSFlag=atoipos;
			if (strstr(pos,"LVCS_SORT")) m_CSFlag|=0x1;
			if (strstr(pos,"LVCS_FILTER")) m_CSFlag|=0x2;
			break;
		case 182: /*GetCaseSensitive*/
			retint=m_CSFlag;
			break;
		case 183: /*SetAutoSort*/
			retint=m_AutoSortFlag;
			if (!m_VirtualData)
			m_AutoSortFlag=atoipos;
			break;
		case 184: /*GetAutoSort*/
			retint=m_AutoSortFlag;
			break;
		case 185: /*SetCacheSize*/
			retint=-1;
			if (m_VirtualData) 
			{
				retint=m_VirtualData->GetItemCount();
				m_VirtualData->SetItemCount(atoipos);
			}
			break;
		case 186: /*SetCacheTimeout*/
			retint=m_dwVLDelay;
			m_dwVLDelay=atoipos;
			break;
		case 187: /*GetCacheSize*/
			retint=-1;
			if (m_VirtualData) retint=m_VirtualData->GetItemCount();
			break;
		case 188: /*GetCacheTimeout*/
			retint=m_dwVLDelay;
			break;
		case 189: /*SetPrereadCount*/
			retint=-1;
			if (m_VirtualData) 
			{
				retint=m_VirtualData->GetPrereadCount();
				m_VirtualData->SetPrereadCount(atoipos);
			}
			break;
		case 190: /*GetPrereadCount*/
			retint=-1;
			if (m_VirtualData) retint=m_VirtualData->GetPrereadCount();
			break;
		case 191: /*SetBulkCount*/
			retint=-1;
			if (m_VirtualData) 
			{
				retint=m_VirtualData->GetBulkCount();
				m_VirtualData->SetBulkCount(atoipos);
			}
			break;
		case 192: /*GetBulkCount*/
			retint=-1;
			if (m_VirtualData) retint=m_VirtualData->GetBulkCount();
			break;
		case 193: /*ResetVirtualList*/
			retint=-1;
			if (m_VirtualData)
			{
				retint=m_VirtualData->ResetData();
				EnsureVisible(0,FALSE);
				Invalidate();
			}
			break;
		case 194: /*SetDefItemImage*/
			retint=m_DefItemImage;
			m_DefItemImage=atoipos;
			if (m_VirtualData) m_VirtualData->SetDefImage(m_DefItemImage);
			break;
		case 195: /*GetDefItemImage*/
			retint=m_DefItemImage;
			break;

		default: if (oStr!=NULL) sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
		}
	}catch(...)
	{
		char *str=new char [200+(int)strlen(pos)];
		#ifdef RUS
			sprintf(str,"ќшибка выполнени€ метода %s %s",met,pos);
			MessageBox(str,"ќшибка метода");
		#else
			sprintf(str,"Error execution of method %s %s",met,pos);
			MessageBox(str,"Error execution");
		#endif
		if (oStr!=NULL) strcpy(oStr,str);
		nfunc=0xFFFFFFFFL;
		GPC.m_ErrReport.GPWriteErrorLog("GPListCtr", "DoMethod",iStr);
		delete[] str;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
	return nfunc;
}

UINT GPListCtr::GPSetProperty(char *iStr)
{
	char *iValue=new char [(int)strlen(iStr)+5];
	strcpy(iValue,iStr);
	UINT ret=1,i;
	char *pos=strchr(iValue,'=');

	if (pos!=NULL && m_hWnd)
	{
		char *prop[6]={ "ADDSTYLE", "DELSTYLE","STYLE",};
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
					// GPListCtr specif
					for(i=0;i<N_LISTCTRL_STYLES;i++)
						if (strstr(pos,aListCtrlStyleName[i])!=NULL)
						{
							InvFlg++;
							switch(propnum)
							{
							case 2: /* STYLE*/
							case 0: /* ADDSTYLE*/	ModifyStyle(0,aListCtrlStyleUINT[i]);break;
							case 1: /* DELSTYLE*/	ModifyStyle(aListCtrlStyleUINT[i],0);break;
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
					for(i=0;i<N_LISTCTRL_EX_STYLES;i++)
						if (strstr(pos,aListCtrlExStyleName[i])!=NULL)
						{
							InvFlg++;
							switch(propnum)
							{
							case 2: /* STYLE*/
							case 0: /* ADDSTYLE*/	es|=aListCtrlExStyleUINT[i];	break;
							case 1: /* DELSTYLE*/	es=((es|aListCtrlExStyleUINT[i])^aListCtrlExStyleUINT[i]);break;
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

void GPListCtr::OnDestroy()
{
//	DeleteAllItems();
	CListCtrl::OnDestroy();
}

void GPListCtr::OnClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMITEMACTIVATE lpnmitem =(LPNMITEMACTIVATE) pNMHDR;
	LVHITTESTINFO htinfo={0};
	htinfo.pt=lpnmitem->ptAction;
	htinfo.iItem=-1;
	SubItemHitTest(&htinfo);

	selposition  = GetFirstSelectedItemPosition();
	if ((m_EditInProgr&0x1)!=0)
	{
		SetSelByEdit();
		SetEditRect();
	}


	{

		char *str=new char [15000];
		*str=0;
		int len=sprintf(str,"%d\x7F",htinfo.iItem);
		int nSelItem=-1;
		if (selposition  != NULL) nSelItem = GetNextSelectedItem(selposition );

		if (htinfo.iItem>=0)
		{
			if (GetItemText(htinfo.iItem,0,str+5000,4900)<=0) str[5000]=0;
			if (GetItemText(htinfo.iItem,htinfo.iSubItem,str+10000,4900)<=0) str[10000]=0;

		}
		else
		{
			str[5000]=0;
			str[10000]=0;
		}

		if (referGPU!=NULL)
		{
			strcpy(str+len,str+5000);
			POINT poScr=htinfo.pt;
			::ClientToScreen(m_hWnd,&poScr);
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClick",str);
			sprintf(str,"%d\x7F%d\x7F%d\x7F%d\x7%d\x7F%d\x7F%d\x7%d\x7F%s\x7F%s",
				htinfo.iItem,htinfo.iSubItem,nSelItem,htinfo.pt.x,htinfo.pt.y,htinfo.flags,poScr.x,poScr.y,str+5000,str+10000);

			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSubItemClick",str);
		}


		delete[] str;
	}

	*pResult = 0;
}


void GPListCtr::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMITEMACTIVATE lpnmitem =(LPNMITEMACTIVATE) pNMHDR;
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG)
	{
		int nItem=-1;
		selposition  = GetFirstSelectedItemPosition();
		if (referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnDblclk"))
		{
			char *str=new char [10000];
			char *strtxt=str+5000;

			if (selposition  != NULL)
			{
				*str=0;
				nItem = GetNextSelectedItem(selposition );
				if (GetItemText(nItem,0,strtxt,4900)<=0) *strtxt=0;
				sprintf(str,"%d\x7F%s",nItem,strtxt);
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDblclk",str);
			}
			delete[] str;
		}

		if (referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnSubItemDblclk"))
		{
			char *str=new char [15000];
			char *strtxt=str+5000;
			char *strtxt2=str+10000;
			*str=0;

			LVHITTESTINFO htinfo={0};
			htinfo.pt=lpnmitem->ptAction;
			htinfo.iItem=-1;
			SubItemHitTest(&htinfo);
			if (htinfo.iItem>=0 && htinfo.iSubItem>=0)
			{
				if (selposition  != NULL && nItem<0)	nItem = GetNextSelectedItem(selposition );

				if (GetItemText(htinfo.iItem,0,strtxt,4900)<=0) *strtxt=0;
				if (GetItemText(htinfo.iItem,htinfo.iSubItem,strtxt2,4900)<=0) *strtxt2=0;
				
				POINT poScr=htinfo.pt;
				::ClientToScreen(m_hWnd,&poScr);
				sprintf(str,"%d\x7F%d\x7F%d\x7F%d\x7%d\x7F%d\x7F%d\x7%d\x7F%s\x7F%s",
					htinfo.iItem,htinfo.iSubItem,nItem,
					htinfo.pt.x,htinfo.pt.y,htinfo.flags,poScr.x,poScr.y,strtxt,strtxt2);

				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSubItemDblclk",str);
			}

			delete[] str;
		}
	}
	*pResult = 0;
}

void GPListCtr::OnKillfocus(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnKillfocusN"))
	{
		char str[200];
		sprintf(str,"%X\x7F%ld\x7F%ld",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnKillfocusN",str);
	}
	*pResult = 0;
}

void GPListCtr::OnOutofmemory(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnOutofmemory"))
	{
		char str[200];
		sprintf(str,"%X\x7F%ld\x7F%ld",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnOutofmemory",str);
	}
	*pResult = 0;
}

void GPListCtr::OnRclick(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (pNMHDR && referGPU && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnRclick"))
	{
	    LPNMITEMACTIVATE lpnmitem =(LPNMITEMACTIVATE) pNMHDR;
		LVHITTESTINFO htinfo={0};
		htinfo.pt=lpnmitem->ptAction;
		htinfo.iItem=-1;
		SubItemHitTest(&htinfo);

		int nSelItem=-1;
		POSITION tmp_selposition  = GetFirstSelectedItemPosition();
		if (tmp_selposition) nSelItem = GetNextSelectedItem(tmp_selposition );

		char *str=new char [15000];
		*str=0;
		str[5000]=0;
		str[10000]=0;
		CPoint spt(RBhti.pt);
		ClientToScreen(&spt);

		if (htinfo.iItem>=0)
		{
			if (GetItemText(htinfo.iItem,0,str+5000,4900)<=0) str[5000]=0;
			if (GetItemText(htinfo.iItem,htinfo.iSubItem,str+10000,4900)<=0) str[10000]=0;
		}
		sprintf(str,"%X\x7F%ld\x7F%ld\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F\x7F%s\x7F%s",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code,RBhti.iItem,RBhti.iSubItem,RBhti.pt.x,RBhti.pt.y,spt.x,spt.y,nSelItem,str+5000,str+10000);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnRclick",str);
		delete[] str;
	}
	*pResult = 0;
}

void GPListCtr::OnRdblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
//    lpnmitem =(LPNMITEMACTIVATE) lParam;
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnRdblclk"))
	{
	    LPNMITEMACTIVATE lpnmitem =(LPNMITEMACTIVATE) pNMHDR;
		LVHITTESTINFO htinfo={0};
		htinfo.pt=lpnmitem->ptAction;
		htinfo.iItem=-1;
		SubItemHitTest(&htinfo);

		int nSelItem=-1;
		POSITION tmp_selposition  = GetFirstSelectedItemPosition();
		if (tmp_selposition) nSelItem = GetNextSelectedItem(tmp_selposition );

		char *str=new char [15000];
		*str=0;
		str[5000]=0;
		str[10000]=0;
		CPoint spt(RBhti.pt);
		ClientToScreen(&spt);

		if (htinfo.iItem>=0)
		{
			if (GetItemText(htinfo.iItem,0,str+5000,4900)<=0) str[5000]=0;
			if (GetItemText(htinfo.iItem,htinfo.iSubItem,str+10000,4900)<=0) str[10000]=0;
		}
		sprintf(str,"%X\x7F%ld\x7F%ld\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F\x7F%s\x7F%s",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code,RBhti.iItem,RBhti.iSubItem,RBhti.pt.x,RBhti.pt.y,spt.x,spt.y,nSelItem,str+5000,str+10000);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnRdblclk",str);
		delete[] str;
	}
	*pResult = 0;
}

void GPListCtr::OnReturn(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnReturn"))
	{
		selposition  = GetFirstSelectedItemPosition();
		if (selposition  != NULL)
		{
			char *str=new char [5000];
			*str=0;
			int nItem = GetNextSelectedItem(selposition );
			int len=sprintf(str,"%d\x7F",nItem);
			if (GetItemText(nItem,0,str+len,4900)<=0) str[len]=0;
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnReturn",str);
			delete[] str;
		}
	}

	*pResult = 0;
}

void GPListCtr::OnSetfocus(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnSetfocusN"))
	{
		char str[200];
		sprintf(str,"%X\x7F%ld\x7F%ld",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSetfocusN",str);
	}
	*pResult = 0;
}

void GPListCtr::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL)
	{
		NM_LISTVIEW* pNMListView =(NM_LISTVIEW*)pNMHDR;
		char str[1000];
		FillNmListViewStr(pNMListView,str);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnBegindrag",str);

		CPoint point;
		CPoint hotSpot;
		int imagecounter=0;
		CImageList* pImageList_tmp;
		int iItem,iItem_s;
		POSITION pos=this->GetFirstSelectedItemPosition();
		BOOL flgEndByLimit=FALSE;

		GPC.m_DragDrop.DragName=referGPU[UnitId&0xFFFF]?referGPU[UnitId&0xFFFF]->m_DragName:"";
		GPC.m_DragDrop.IdScr=(UnitId&IS_DLG_UNIT)==0?(UnitId/0x10000)&0xFF:0xFFFFFFFF;
		GPC.m_DragDrop.IdDlg=(UnitId&IS_DLG_UNIT)!=0?(UnitId/0x10000)&0xFF:0xFFFFFFFF;
		GPC.m_DragDrop.IdObj=UnitId&0xFFFF;
		GPC.m_DragDrop.DlgScrName=referGPU[0]->m_ObjName;
		GPC.m_DragDrop.ObjName=referGPU[UnitId&0xFFFF]->m_ObjName;
		GPC.m_DragDrop.hWndDrag=m_hWnd;
		GPC.m_DragDrop.hWndLast=NULL;
		GPC.m_DragDrop.MessageSting="";
		CString tmpMStr;
		int nTop=GetTopIndex();

		while (pos && (!flgEndByLimit))
		{
			iItem=this->GetNextSelectedItem(pos);
			if (imagecounter==0)
				iItem_s=iItem;

			tmpMStr.Format("%d\x07%s",iItem,(LPCSTR)GetItemText(iItem,0));

			if (GPC.m_DragDrop.MessageSting=="")
				GPC.m_DragDrop.MessageSting=tmpMStr;
			else GPC.m_DragDrop.MessageSting+="\x7F"+tmpMStr;

			// Create a drag image. If the assertion fails, you probably forgot to assign an image list to the control with SetImageList. Create-
			// DragImage will not work if the control hasn't been assigned an image list!
			POINT initPO;
			pImageList_tmp=NULL;
			EnsureVisible(iItem,TRUE);
			pImageList_tmp = CreateDragImage(iItem,&initPO);
			if (pImageList_tmp != NULL)
			{
				if (imagecounter==0)
				{
				// Compute the coordinates of the Уhot spotФЧthe location of the
				 // cursor relative to the upper left corner of the item rectangle.
					CRect rect;
					GetItemRect (((LPNMLISTVIEW)pNMHDR)->iItem, rect, TRUE);
					DWORD dwPos = ::GetMessagePos();
					point=CPoint(LOWORD(dwPos), HIWORD(dwPos));
			//		ScreenToClient(&point);
					hotSpot = point;
					hotSpot.x -= (rect.left);
					hotSpot.y -= (rect.top);

				 // Convert the client coordinates in УpointФ to coordinates relative
				 // to the upper left corner of the control window.
					CPoint client (0, 0);
					ClientToScreen (&client);
					GetWindowRect (rect);
					point.x += client.x - rect.left;
					point.y += client.y - rect.top;
					ScreenToClient(&hotSpot);
					GPC.m_DragDrop.pImageList=pImageList_tmp;
				}
				else
				{
					flgEndByLimit=TRUE;
					CImageList *pImageList_tmp_x=NULL;
					CRect rct_item;

					if (imagecounter<limit_of_images)
					{
						GetItemRect(0,rct_item,LVIR_BOUNDS);
						pImageList_tmp_x=new CImageList();
						if (pImageList_tmp_x!=NULL)
						{
							if (pImageList_tmp_x->Create(*GPC.m_DragDrop.pImageList,0,*pImageList_tmp,0,0,imagecounter*rct_item.Height())!=0)
							{
								delete GPC.m_DragDrop.pImageList;
								GPC.m_DragDrop.pImageList=pImageList_tmp_x;
								flgEndByLimit=FALSE;
							}
							else
								delete pImageList_tmp_x;
						}
					}
	//				flgEndByLimit=MSCreateImageList(pImageList_tmp,iItem-iItem_s,iItem);
					if (pImageList_tmp) delete pImageList_tmp;
				}
			}
			imagecounter++;
		}

		EnsureVisible(nTop,TRUE);
		EnsureVisible(nTop+GetCountPerPage()-1,TRUE);
		UpdateWindow();

		if ((imagecounter>0) && (GPC.m_DragDrop.pImageList!=NULL))
		{
		   SetCapture ();
		   GPC.m_DragDrop.pImageList->BeginDrag (0, hotSpot);
		   m_bDragging = TRUE;
		}

		*pResult = 0;
	}
}

BOOL GPListCtr::MSCreateImageList(CImageList *pImageList_tmp, int imagecounter, int count)
{
	BOOL flgRet=TRUE;
	CImageList *pImageList_tmp_x=NULL;
	CRect rct_item;

	if (imagecounter<limit_of_images)
	{
		GetItemRect(0,rct_item,LVIR_BOUNDS);
		pImageList_tmp_x=new CImageList();
		if (pImageList_tmp_x!=NULL)
		{
			if (pImageList_tmp_x->Create(*GPC.m_DragDrop.pImageList,0,*pImageList_tmp,0,0,imagecounter*rct_item.Height())!=0)
			{
				delete GPC.m_DragDrop.pImageList;
				GPC.m_DragDrop.pImageList=pImageList_tmp_x;
				flgRet=FALSE;
			}
			else
				delete pImageList_tmp_x;
		}
	}
	return flgRet;
}

void GPListCtr::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnBeginlabeledit"))
	{
		char str[200];
		LVITEM *pItem=&((LV_DISPINFO*)pNMHDR)->item;
		sprintf(str,"%ld\x7F%ld\x7F%ld",pItem->mask,pItem->iItem,pItem->iSubItem);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnBeginlabeledit",str);
	}
	*pResult = 0;
}

void GPListCtr::OnBeginrdrag(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnBeginrdrag"))
	{
		NM_LISTVIEW* pNMListView =(NM_LISTVIEW*)pNMHDR;
		char str[1000];
		FillNmListViewStr(pNMListView,str);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnBeginrdrag",str);
	}
	*pResult = 0;
}

void GPListCtr::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLISTVIEW* pNMListView =(NM_LISTVIEW*)pNMHDR;
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnColumnclick"))
	{
		char str[200];
		sprintf(str,"%d",pNMListView->iSubItem);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnColumnclick",str);
	}
	if (m_AutoSortFlag)
	{
		char str[200];
		sprintf(str,"SortItems %d",pNMListView->iSubItem);
		DoMethod(str,NULL);
	}
	*pResult = 0;
}

#include "ProgressDialog.h"

void GPListCtr::OnDeleteallitems(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView =(NM_LISTVIEW*)pNMHDR;
	char str[1000];
	static HWND m_stHWND;

	int ni=GetItemCount();

	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnDeleteallitems"))
	{
		FillNmListViewStr(pNMListView,str);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDeleteallitems",str);
	}

	GPUnit **tmp=referGPU;
	referGPU=NULL;

	ProgressDialog *dlg=NULL;

	if (ni>1000)
	{
		m_stHWND=::GetFocus();
		dlg=new ProgressDialog;
		dlg->Create(IDD_DIALOGPROGRESS);
		dlg->ShowWindow(SW_SHOW);
		dlg->SetProgressRange(0,ni);
	}
	int i;
	for(i=ni-1;i>=0;i--)
	{
		if (dlg!=NULL &&(i%50)==0) dlg->SetProgressPos(ni-i);
		DeleteItem(i);
	}

	if (dlg!=NULL)
	{
		dlg->DestroyWindow();
		delete dlg;
		if (m_stHWND) ::SetFocus(m_stHWND);
		m_stHWND=NULL;
	}

	referGPU=tmp;
	*pResult = 1;
}

void GPListCtr::OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView =(NM_LISTVIEW*)pNMHDR;

	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnDeleteitem"))
	{
		char str[300];
		sprintf(str,"%d\x7F%d\x7F%X\x7F%ld\x7F%ld\x7F%s",	pNMListView->iItem,	pNMListView->iSubItem,(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code,pNMListView->lParam?(LPCSTR)(((GPTextArray *) pNMListView->lParam)->csItemData):"");
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDeleteitem",str);
	}

	if (pNMListView->lParam != NULL)
		delete(GPTextArray *) pNMListView->lParam;

	*pResult = 0;
}

void GPListCtr::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL)
	{
		CEdit *ed=GetEditControl();
		char tmpstr[1000];
		*tmpstr=0;
		if (ed) ed->GetLine(0,tmpstr,970);
		char str[2000];
		LVITEM *pItem=&((LV_DISPINFO*)pNMHDR)->item;
		sprintf(str,"%ld\x7F%ld\x7F%ld\x7F%s",pItem->mask,pItem->iItem,pItem->iSubItem,tmpstr);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnEndlabeledit",str);
	}
	*pResult = 0;
}

void GPListCtr::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnGetdispinfo"))
	{
		//LV_DISPINFO* pDispInfo =(LV_DISPINFO*)pNMHDR;
		char str[200];
		LVITEM *pItem=&((LV_DISPINFO*)pNMHDR)->item;
		sprintf(str,"%ld\x7F%ld\x7F%ld",pItem->mask,pItem->iItem,pItem->iSubItem);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnGetdispinfo",str);

	}
	if (m_VirtualData)
	{
		KillTimer(VIRTUAL_LIST_TIMER_ID);
		LVITEM *pItem=&((LV_DISPINFO*)pNMHDR)->item;
		if ((pItem->mask&LVIF_IMAGE)==LVIF_IMAGE)
			pItem->iImage=m_VirtualData->GetItemImage(pItem->iItem,pItem->iSubItem);
		if ((pItem->mask&LVIF_STATE)==LVIF_STATE)
			pItem->state=m_VirtualData->GetItemState(pItem->iItem,pItem->iSubItem);
		if ((pItem->mask&LVIF_TEXT)==LVIF_TEXT)
			pItem->pszText=(char *)(m_VirtualData->GetItemText(pItem->iItem,pItem->iSubItem));
		SetTimer(VIRTUAL_LIST_TIMER_ID,m_dwVLDelay,NULL);
	}
	*pResult = 0;
}

void GPListCtr::OnHdrGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnHdrGetdispinfo"))
	{
		LV_DISPINFO* pDispInfo =(LV_DISPINFO*)pNMHDR;
		char str[200];
		sprintf(str,"%X\x7F%ld\x7F%ld",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnHdrGetdispinfo",str);
	}
	*pResult = 0;
}

void GPListCtr::OnInsertitem(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnInsertitem"))
	{
		NM_LISTVIEW* pNMListView =(NM_LISTVIEW*)pNMHDR;
		char str[2000];
		str[100]=0;

		if (GetItemText(pNMListView->iItem,0,str+100,1900)<=0) str[100]=0;

		sprintf(str,"%d\x7F%d\x7F%ld\x7F%ld\x7F%ld\x7F%s",pNMListView->iItem,pNMListView->iSubItem,
			pNMListView->uNewState,pNMListView->uOldState,pNMListView->uChanged,str+100);

		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnInsertitem",str);
	}
	*pResult = 0;
}

void GPListCtr::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL)
	{
		NM_LISTVIEW* pNMListView =(NM_LISTVIEW*)pNMHDR;

//		if (referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnItemActivate"))
//		{
//			char str[2000];
//			str[100]=0;

//			if (GetItemText(pNMListView->iItem,0,str+100,1900)<=0) str[100]=0;

//			sprintf(str,"%d\x7F%d\x7F%ld\x7F%ld\x7F%ld\x7F%s",pNMListView->iItem,pNMListView->iSubItem,
//				pNMListView->uNewState,pNMListView->uOldState,pNMListView->uChanged,str+100);
//			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnItemActivate",str);
//		}

		{
			char str[2000];
			str[100]=0;

			if (GetItemText(pNMListView->iItem,0,str+100,1900)<=0) str[100]=0;

			sprintf(str,"%d\x7F%d\x7F%ld\x7F%ld\x7F%ld\x7F%s",pNMListView->iItem,pNMListView->iSubItem,
				pNMListView->uNewState,pNMListView->uOldState,pNMListView->uChanged,str+100);
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnItemchanged",str);
		}

		if ((pNMListView->uNewState&LVIS_SELECTED)==LVIS_SELECTED)
		{
			if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnSelchange"))
			{
				char str[2000];
				str[100]=0;
				if (GetItemText(pNMListView->iItem,0,str+100,1900)<=0) str[100]=0;

				sprintf(str,"%d\x7F%d\x7F%s",pNMListView->iItem,pNMListView->iSubItem,str+100);
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSelchange",str);
				if (referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
					DoMethod("UpdateGroup",NULL);
			}

		}

		if (((pNMListView->uNewState^pNMListView->uOldState)&0x2000)!=0 && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnCheck"))
		{
			char str[2000];
			str[100]=0;
			if (GetItemText(pNMListView->iItem,0,str+100,1900)<=0) str[100]=0;

			sprintf(str,"%d\x7F%d\x7F%s\x7F%d",pNMListView->iItem,pNMListView->iSubItem,str+100,(pNMListView->uNewState&0x3000)/0x1000);
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnCheck",str);
		}

		if ((m_EditInProgr&0x1)!=0) SetEditRect();
	}

	*pResult = 0;
}

void GPListCtr::OnHdrItemchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnHdrItemchanged"))
	{
		NMHEADER * phdn =(NMHEADER *) pNMHDR;
		char str[200];
		sprintf(str,"%d\x7F%d",phdn->iItem,phdn->iButton);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnHdrItemchanged",str);
		if ((m_EditInProgr&0x1)!=0) PostMessage(GPM_UPDATELVEDITOR,0,0);
		Invalidate();
		SetEditRect();
	}

	*pResult = 0;
}

void GPListCtr::OnItemchanging(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnItemchanging"))
	{
		NM_LISTVIEW* pNMListView =(NM_LISTVIEW*)pNMHDR;
		char str[1000];
		try
		{
			FillNmListViewStr(pNMListView,str);
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnItemchanging",str);
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("GPListCtr", "OnItemchanging","");
		}
	}
	*pResult = 0;
}

void GPListCtr::OnHdrItemchanging(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnHdrItemchanging"))
	{
		NMHEADER * phdn =(NMHEADER *) pNMHDR;
		char str[200];
		sprintf(str,"%d\x7F%d",phdn->iItem,phdn->iButton);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnHdrItemchanging",str);
	}
	*pResult = 0;
}

void GPListCtr::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG)
	{
		LV_KEYDOWN* pLVKeyDow =(LV_KEYDOWN*)pNMHDR;
		if (referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnKeydown"))
		{
			char str[500];
			sprintf(str,"%X\x7F%ld\x7F%ld\x7F%ld\x7F%ld\x7F%s",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code,pLVKeyDow->wVKey,pLVKeyDow->flags,GP_HotKey::GetKeyName(pLVKeyDow->wVKey<<16));
			if ((GetAsyncKeyState(VK_RWIN)&0xFF00) || (GetAsyncKeyState(VK_LWIN)&0xFF00)) strcat(str,"|MOD_WIN");
			if ((GetAsyncKeyState(MOD_SHIFT)&0xFF00) || (GetAsyncKeyState(VK_LSHIFT)&0xFF00) || (GetAsyncKeyState(VK_RSHIFT)&0xFF00)) strcat(str,"|MOD_SHIFT");
			if ((GetAsyncKeyState(VK_CONTROL)&0xFF00) || (GetAsyncKeyState(VK_RCONTROL)&0xFF00) || (GetAsyncKeyState(VK_LCONTROL)&0xFF00)) strcat(str,"|MOD_CONTROL");
			if ((GetAsyncKeyState(MOD_ALT)&0xFF00) || (GetAsyncKeyState(VK_RMENU)&0xFF00) || (GetAsyncKeyState(VK_LMENU)&0xFF00)) strcat(str,"|MOD_ALT");

			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnKeydown",str);
		}
		if ((pLVKeyDow->wVKey==VK_RIGHT || pLVKeyDow->wVKey==VK_DOWN || pLVKeyDow->wVKey==VK_END || pLVKeyDow->wVKey==VK_NEXT || pLVKeyDow->wVKey==VK_RETURN) && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnKeydownOnEnd"))
		{
			int nItems=GetItemCount();
			if (nItems>0 && (GetItemState(nItems-1,LVIS_SELECTED)&LVIS_SELECTED)==LVIS_SELECTED)
			{
				char str[500];
				sprintf(str,"%X\x7F%ld\x7F%ld\x7F%ld\x7F%ld\x7F%s",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code,pLVKeyDow->wVKey,pLVKeyDow->flags,GP_HotKey::GetKeyName(pLVKeyDow->wVKey<<16));
				if ((GetAsyncKeyState(VK_RWIN)&0xFF00) || (GetAsyncKeyState(VK_LWIN)&0xFF00)) strcat(str,"|MOD_WIN");
				if ((GetAsyncKeyState(MOD_SHIFT)&0xFF00) || (GetAsyncKeyState(VK_LSHIFT)&0xFF00) || (GetAsyncKeyState(VK_RSHIFT)&0xFF00)) strcat(str,"|MOD_SHIFT");
				if ((GetAsyncKeyState(VK_CONTROL)&0xFF00) || (GetAsyncKeyState(VK_RCONTROL)&0xFF00) || (GetAsyncKeyState(VK_LCONTROL)&0xFF00)) strcat(str,"|MOD_CONTROL");
				if ((GetAsyncKeyState(MOD_ALT)&0xFF00) || (GetAsyncKeyState(VK_RMENU)&0xFF00) || (GetAsyncKeyState(VK_LMENU)&0xFF00)) strcat(str,"|MOD_ALT");
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnKeydownOnEnd",str);
			}
		}
		if ((pLVKeyDow->wVKey==VK_LEFT || pLVKeyDow->wVKey==VK_PRIOR || pLVKeyDow->wVKey==VK_HOME || pLVKeyDow->wVKey==VK_UP) && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnKeydownOnBegin"))
		{
			if ((GetItemState(0,LVIS_SELECTED)&LVIS_SELECTED)==LVIS_SELECTED)
			{
				char str[500];
				sprintf(str,"%X\x7F%ld\x7F%ld\x7F%ld\x7F%ld\x7F%s",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code,pLVKeyDow->wVKey,pLVKeyDow->flags,GP_HotKey::GetKeyName(pLVKeyDow->wVKey<<16));
				if ((GetAsyncKeyState(VK_RWIN)&0xFF00) || (GetAsyncKeyState(VK_LWIN)&0xFF00)) strcat(str,"|MOD_WIN");
				if ((GetAsyncKeyState(MOD_SHIFT)&0xFF00) || (GetAsyncKeyState(VK_LSHIFT)&0xFF00) || (GetAsyncKeyState(VK_RSHIFT)&0xFF00)) strcat(str,"|MOD_SHIFT");
				if ((GetAsyncKeyState(VK_CONTROL)&0xFF00) || (GetAsyncKeyState(VK_RCONTROL)&0xFF00) || (GetAsyncKeyState(VK_LCONTROL)&0xFF00)) strcat(str,"|MOD_CONTROL");
				if ((GetAsyncKeyState(MOD_ALT)&0xFF00) || (GetAsyncKeyState(VK_RMENU)&0xFF00) || (GetAsyncKeyState(VK_LMENU)&0xFF00)) strcat(str,"|MOD_ALT");
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnKeydownOnBegin",str);
			}
		}
	}
	*pResult = 0;
}

void GPListCtr::OnSetdispinfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnSetdispinfo"))
	{
		LV_DISPINFO* pDispInfo =(LV_DISPINFO*)pNMHDR;
		char str[200];
		sprintf(str,"%X\x7F%ld\x7F%ld",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSetdispinfo",str);
	}
	*pResult = 0;
}

void GPListCtr::OnOdfinditem(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnOdfinditem"))
	{
		NMLVFINDITEM* pFindInfo =(NMLVFINDITEM*)pNMHDR;
		char str[200];
		sprintf(str,"%X\x7F%ld\x7F%ld",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnOdfinditem",str);
	}
	*pResult = 0;
}

void GPListCtr::OnOdstatechanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnOdstatechanged"))
	{
		NMLVODSTATECHANGE* pStateChanged =(NMLVODSTATECHANGE*)pNMHDR;
		char str[200];
		sprintf(str,"%X\x7F%ld\x7F%ld",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnOdstatechanged",str);
	}
	*pResult = 0;
}

void GPListCtr::OnHdrTrack(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnHdrTrack"))
	{
		NMHEADER * phdn =(NMHEADER *) pNMHDR;
		char str[200];
		sprintf(str,"%d\x7F%d",phdn->iItem,phdn->iButton);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnHdrTrack",str);
	}
	*pResult = 0;
}

void GPListCtr::OnHdrBegindrag(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnHdrBegindrag"))
	{
		NMHEADER * phdn =(NMHEADER *) pNMHDR;
		char str[200];
		sprintf(str,"%d\x7F%d",phdn->iItem,phdn->iButton);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnHdrBegindrag",str);
	}
	*pResult = 0;
}
void GPListCtr::OnHdrItemclick(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnHdrItemclick"))
	{
		NMHEADER * phdn =(NMHEADER *) pNMHDR;
		char str[200];
		sprintf(str,"%d\x7F%d",phdn->iItem,phdn->iButton);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnHdrItemclick",str);
	}
	*pResult = 0;
}

void GPListCtr::OnHdrItemdblclick(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnHdrItemdblclick"))
	{
		NMHEADER * phdn =(NMHEADER *) pNMHDR;
		char str[200];
		sprintf(str,"%d\x7F%d",phdn->iItem,phdn->iButton);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnHdrItemdblclick",str);
		if ((m_EditInProgr&0x1)!=0) PostMessage(GPM_UPDATELVEDITOR,0,0);
	}
	*pResult = 0;
}

void GPListCtr::OnHdrBegintrack(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnHdrBegintrack"))
	{
		NMHEADER * phdn =(NMHEADER *) pNMHDR;
		char str[200];
		sprintf(str,"%d\x7F%d",phdn->iItem,phdn->iButton);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnHdrBegintrack",str);
	}
	*pResult = 0;
}

void GPListCtr::OnHdrEndtrack(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnHdrEndtrack"))
	{
		NMHEADER * phdn =(NMHEADER *) pNMHDR;
		char str[200];
		sprintf(str,"%d\x7F%d",phdn->iItem,phdn->iButton);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnHdrEndtrack",str);
		if ((m_EditInProgr&0x1)!=0) PostMessage(GPM_UPDATELVEDITOR,0,0);
	}
	*pResult = 0;
}

void GPListCtr::OnHdrDividerdblclick(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnDividerdblclick"))
	{
		NMHEADER * phdn =(NMHEADER *) pNMHDR;
		char str[200];
		sprintf(str,"%d\x7F%d",phdn->iItem,phdn->iButton);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDividerdblclick",str);
		SetEditRect();
	}
	*pResult = 0;
}

void GPListCtr::OnHdrFilterChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnHdrFilterChange") || m_AutoHFilter)
	{
		NMHEADER * phdn =(NMHEADER *) pNMHDR;
		HDITEM hdi={0};
		HDTEXTFILTER tf={0};

		hdi.mask=HDI_FILTER;
		hdi.type=HDFT_ISSTRING;
		tf.pszText=new char [1000];
		*tf.pszText=0;
		tf.cchTextMax=980;
		hdi.pvFilter=(LPVOID) &tf;

		GetHeaderCtrl()->GetItem(phdn->iItem,&hdi);

		char *str = new char [1200];
		sprintf(str,"%d\x7F%s",phdn->iItem,tf.pszText);

		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnHdrFilterChange",str);
		if (m_AutoHFilter)
		{
			if (FilterArray)
				FilterArray->SetItem(phdn->iItem,tf.pszText);
			DoMethod("SortItems",NULL);
		}
		delete[] tf.pszText;
		delete[] str;
	}
	*pResult = 0;
}

void GPListCtr::OnHdrFilterBtnClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnHdrFilterBtnClick"))
	{
		LPNMHDFILTERBTNCLICK phdn =(LPNMHDFILTERBTNCLICK) pNMHDR;
		char str[200];
		sprintf(str,"%d\x7F%d\x07%d\x07%d\x07%d",phdn->iItem,phdn->rc.left,phdn->rc.top,phdn->rc.right,phdn->rc.bottom);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnHdrFilterBtnClick",str);
	}
	*pResult = 0;
}

void GPListCtr::OnHdrEnddrag(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL)
	{
		NMHEADER * phdn =(NMHEADER *) pNMHDR;
		char str[200];
		sprintf(str,"%d\x7F%d",phdn->iItem,phdn->iButton);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnHdrEnddrag",str);
		if ((m_EditInProgr&0x1)!=0) PostMessage(GPM_UPDATELVEDITOR,0,0);
		Invalidate();
	}
	*pResult = 0;
}

LRESULT GPListCtr::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
//	if (message==WM_MOUSEWHEEL)  return 0;
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		referGPU[UnitId&0xFFFF]->m_CurMessage.message=message;
		referGPU[UnitId&0xFFFF]->m_CurMessage.wParam=wParam;
		referGPU[UnitId&0xFFFF]->m_CurMessage.lParam=lParam;
		if (referGPU[UnitId&0xFFFF]->DefWindowProc(message, wParam, lParam)) return 0;
	}

	if (message==GPM_SETAUTOSIZE)
		GetParent()->PostMessage(GPM_SETAUTOSIZE,wParam);

	if (message==GPM_UPDATELVEDITOR && (m_EditInProgr&0x1)!=0)
	{
		UpdateHtiPosition();
		SetEditRect();
		Invalidate();
	}

	if (message==GPN_UPDATESIZE) GetParent()->SendMessage(GPN_UPDATESIZE);
	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)
	{
		if (message==GPM_CLIENTKILLFOCUS || message==GPM_CLIENTSETFOCUS)
		{
			PGPUNITINFO ui=(PGPUNITINFO)lParam;
			if (ui)
			{
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent
					(m_hWnd, UnitId,message==GPM_CLIENTSETFOCUS?"OnCSetFocus":"OnCKillFocus",GPUnit::UnitInfoToString2(ui,"\x7F"));
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent
					(m_hWnd, UnitId,message==GPM_CLIENTSETFOCUS?"OnCSetFocusEx":"OnCKillFocusEx",GPUnit::UnitInfoToString2Ex(ui,"\x7F"));
			}
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

	if (message==GPM_NEXTCELL &&(m_EditInProgr&0x1)!=0 && htiPosition.iSubItem>=0 && htiPosition.iItem>=0 && referGPU!=NULL)
	{
//		m_EditInProgr=onoff+verhor*2+skip*4+forback*8+lcbreak*16;
		UINT verhor=m_EditInProgr&2,forback=m_EditInProgr&8,lcbreak=m_EditInProgr&16;
		switch(wParam)
		{
		case VK_LEFT:	wParam=0;	verhor=0;		forback=1;	MayBeChangeEdit=TRUE;break;
		case VK_RIGHT:	wParam=0;	verhor=0;		forback=0;	MayBeChangeEdit=TRUE;break;
		case VK_DOWN:	wParam=0;	verhor=1;		forback=0;	MayBeChangeEdit=TRUE;break;
		case VK_UP:		wParam=0;	verhor=1;		forback=1;	MayBeChangeEdit=TRUE;break;
		}


		UINT nCol=1;
		CHeaderCtrl *tmpHead=GetHeaderCtrl();
		if (tmpHead!=NULL)
		{
			try
			{
				nCol=tmpHead->GetItemCount();
			}catch(...){
				char tmps[100];
				sprintf(tmps,"Message %X WPARAM %X LPARAM %X",message, wParam, lParam);
				GPC.m_ErrReport.GPWriteErrorLog("CGPListCtr", "WindowProc 4184",tmps);

				nCol=1;
			}
		}

		UINT nRow=GetItemCount();
		UINT ncurrent=htiPosition.iItem*nCol+htiPosition.iSubItem;
		UINT ncurrent2=ncurrent,nctmp=ncurrent;
		UINT nall=nCol*nRow;
		UINT EdID,n=0;
		GPTextArray *ar;
		LVHITTESTINFO tsthti=hti;

			do
			{
				if (verhor==0) // по горизонтали
				{
					if (forback==0)
					{
						nctmp++;
						if (lcbreak==0 &&(nctmp%nCol)==0 ) break;
						if (nctmp==nall) nctmp=0;
					}
					else
					{
						if (lcbreak==0 &&(nctmp%nCol)==0 ) break;
						if (nctmp==0) nctmp=nall;
						nctmp--;
					}
				}
				else	// по вертикали
				{
					if (forback==0)
					{
						nctmp+=nCol;
						if (lcbreak==0 && nctmp>=nall) break;
						if (nctmp>=nall) nctmp%=nCol;
					}
					else
					{
						if (lcbreak==0 && nctmp<nCol) break;
						if (nctmp<nCol) nctmp+=nall;
						nctmp-=nCol;
					}
				}
				ar=(GPTextArray *) GetItemData(nctmp/nCol);
				if (ar!=NULL &&(nctmp%nCol)<ar->GetItemCount() &&(EdID=ar->GetItemData(nctmp%nCol))>0
					&& referGPU[EdID]!=NULL && referGPU[EdID]->UnitHWND!=NULL)
						{	ncurrent=nctmp;	break;	}
			}
			while(++n<nall);

			if (ncurrent2==ncurrent && nall>0)
			{
				SetSelByEdit(1);
			}


			if (ncurrent2!=ncurrent && (m_EditInProgr&0x1)==0x1)
			{
				htiPosition.iItem=ncurrent/nCol;
				htiPosition.iSubItem=(ncurrent%nCol);

				if (ncurrent/nCol>ncurrent2/nCol)/*DOWN*/
				{
					EnsureVisible(htiPosition.iItem,FALSE);
					SetEditRect();
					RedrawItems( htiPosition.iItem-2, htiPosition.iItem);
				}
				else
				if (ncurrent/nCol<ncurrent2/nCol)/*UP*/
				{
					EnsureVisible(htiPosition.iItem,FALSE);
					SetEditRect();
					RedrawItems( htiPosition.iItem, htiPosition.iItem+1);
				}

				if ((ncurrent%nCol)<(ncurrent2%nCol)) /*LEFT*/
				{
					CRect rei;
					UpdateHti();
					GetSubItemRect(hti.iItem,hti.iSubItem,LVIR_LABEL,rei);
					if (rei.left<0) {Scroll(CSize(rei.left-2,0));Invalidate();}
					SetEditRect();
				}
				else
				if ((ncurrent%nCol)>(ncurrent2%nCol)) /*RIGHT*/
				{
					CRect rei,rec;
					UpdateHti();
					GetSubItemRect(hti.iItem,hti.iSubItem,LVIR_LABEL,rei);
					GetClientRect(&rec);
					if (rei.Width()>rec.Width())	Scroll(CSize(rei.left,0));
					else
					if (rei.right>rec.right)		Scroll(CSize(rei.right-rec.right,0));
					Invalidate();
				}


				CRect rei,rec;
				GetClientRect(&rec);
				UpdateHti();
				GetSubItemRect(hti.iItem,hti.iSubItem,LVIR_LABEL,rei);
				if (rei.left<0) {Scroll(CSize(rei.left-2,0));Invalidate();SetEditRect();}
				else
				if (rei.Width()>rec.Width())	{Scroll(CSize(rei.left,0));Invalidate();SetEditRect();}
				else
				if (rei.right>rec.right)
				{
					Scroll(CSize(rei.right-rec.right,0));
					Invalidate();
					SetEditRect();
				}
				else
				{
					UpdateHti();
					SetEditRect();
					UpdateHtiPosition();
				}
				InvalidateRect(&rei);
				SetFocus();
				if ((wParam&0x1)==0)
				{
					UpdateHti();
					SetSelByEdit();
					UpdateHtiPosition();
				}
			}

			if (hti.iItem>=0 && hti.iSubItem>=0)
			{
				if (hti.iItem!=tsthti.iItem || hti.iSubItem!=tsthti.iSubItem)
				{
					if (hti.iItem!=tsthti.iItem && !(m_EditInProgr&0x2))
					{
						char str[300];
						sprintf(str,"%d\x7F%d\x7F%d\x7F%d",hti.iItem,hti.iSubItem,tsthti.iItem,tsthti.iSubItem);
						referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnChangeLine",str);
					}
					else
					if (hti.iSubItem!=tsthti.iSubItem && (m_EditInProgr&0x2))
					{
						char str[300];
						sprintf(str,"%d\x7F%d\x7F%d\x7F%d",hti.iItem,hti.iSubItem,tsthti.iItem,tsthti.iSubItem);
						referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnChangeColumn",str);
					}
				}
				else
				{
					char str[300];
					sprintf(str,"%d\x7F%d",hti.iItem,hti.iSubItem);
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnEndOfTable",str);
				}
			}
	}


	if (message==GPM_ESCCELL &&(m_EditInProgr&0x1)!=0 && AutoUpdate==TRUE && lasthti.iItem>=0 && lasthti.iSubItem>=0 && EditorID!=0 && referGPU[EditorID]!=NULL && referGPU[EditorID]->UnitHWND!=NULL && hti.iItem!=-1 && hti.iSubItem!=-1)
	{
		CString str="TEXT=";
			str+=GetItemText(hti.iItem,hti.iSubItem);
		referGPU[EditorID]->GPSetProperty((LPCSTR)str);
		SetFocus();
	}

	if (message==WM_KEYDOWN &&(m_EditInProgr&0x1)!=0 && htiPosition.iSubItem>=0 && htiPosition.iItem>=0)
	{
		switch(wParam)
		{
		case 40:	/*DOWN*/
			if (htiPosition.iItem<GetItemCount()-1)
			{
				htiPosition.iItem++;
				EnsureVisible(htiPosition.iItem,FALSE);
				SetEditRect();
				RedrawItems( htiPosition.iItem-2, htiPosition.iItem);
				SetSelByEdit();
			}
			return 0;
		case 38:	/*UP*/
			if (htiPosition.iItem>0)
			{
				htiPosition.iItem--;
				EnsureVisible(htiPosition.iItem,FALSE);
				SetEditRect();
				RedrawItems( htiPosition.iItem, htiPosition.iItem+1);
				SetSelByEdit();
			}
			return 0;
		case 37:	/*LEFT*/
			if (htiPosition.iSubItem>0)
			{
				htiPosition.iSubItem--;
				UpdateHti();
				CRect rei;
				GetSubItemRect(hti.iItem,hti.iSubItem,LVIR_LABEL,rei);
				if (rei.left<0) {Scroll(CSize(rei.left-2,0));/*Invalidate();*/}
				RedrawItems( htiPosition.iItem-1, htiPosition.iItem+1);
				SetEditRect();
				SetSelByEdit();
			}
			return 0;
		case 39:	/*RIGHT*/
			if (htiPosition.iSubItem<GetHeaderCtrl( )->GetItemCount()-1) /*RIGHT*/
			{
				htiPosition.iSubItem++;
				UpdateHti();
				CRect rei,rec;
				GetSubItemRect(hti.iItem,hti.iSubItem,LVIR_LABEL,rei);
				GetClientRect(&rec);
				if (rei.Width()>rec.Width())	Scroll(CSize(rei.left,0));
				else
				if (rei.right>rec.right)		Scroll(CSize(rei.right-rec.right,0));
				RedrawItems( htiPosition.iItem-1, htiPosition.iItem+1);
				SetEditRect();
				SetSelByEdit();
			}
			return 0;
		case 36:	/*HOME*/
			{
				if ((m_EditInProgr&4)!=0)
				{
					int nCol=GetHeaderCtrl()->GetItemCount()-1;
					UINT EdID;
					GPTextArray *ar=(GPTextArray *) GetItemData(htiPosition.iItem);

					for(htiPosition.iSubItem=0;htiPosition.iSubItem<nCol && ar!=NULL;htiPosition.iSubItem++)
					{
						if ((EdID=ar->GetItemData(htiPosition.iSubItem))>0
							&& referGPU[EdID]!=NULL && referGPU[EdID]->UnitHWND!=NULL)	break;
					}
				}
				else
					htiPosition.iSubItem=0;

				CRect rei;
				UpdateHti();
				GetSubItemRect(hti.iItem,hti.iSubItem,LVIR_LABEL,rei);
				if (rei.left<0) Scroll(CSize(rei.left-2,0));
				else			Scroll(CSize(-rei.left,0));
				Invalidate();
				SetEditRect();
				SetSelByEdit();
			}
			return 0;
		case 35:	/*END*/
			{
				htiPosition.iSubItem=GetHeaderCtrl( )->GetItemCount()-1;
				if ((m_EditInProgr&4)!=0)
				{
					UINT EdID;
					GPTextArray *ar=(GPTextArray *) GetItemData(htiPosition.iItem);

					for(;htiPosition.iSubItem>0 && ar!=NULL;htiPosition.iSubItem--)
					{
						if ((EdID=ar->GetItemData(htiPosition.iSubItem))>0
							&& referGPU[EdID]!=NULL && referGPU[EdID]->UnitHWND!=NULL)	break;
					}
				}

				CRect rei,rec;
				UpdateHti();
				GetSubItemRect(hti.iItem,hti.iSubItem,LVIR_LABEL,rei);
				GetClientRect(&rec);
				if (rei.Width()>rec.Width())	Scroll(CSize(rei.left,0));
				else
				if (rei.right>rec.right)		Scroll(CSize(rei.right-rec.right,0));
				Invalidate();
				SetEditRect();
				SetSelByEdit();
			}
			return 0;
		case 34:	/*PGDN*/
			{
				htiPosition.iItem+=GetCountPerPage( )*3/4;
				if (htiPosition.iItem>=GetItemCount() ||(GetKeyState(VK_CONTROL)&0xFF00)!=0) htiPosition.iItem=GetItemCount()-1;
				EnsureVisible(htiPosition.iItem,FALSE);
				Invalidate();
				SetEditRect();
				SetSelByEdit();
			}
			return 0;
		case 33:	/*PGUP*/
			{
				htiPosition.iItem-=GetCountPerPage( )*3/4;
				if (htiPosition.iItem<0 ||(GetKeyState(VK_CONTROL)&0xFF00)!=0) htiPosition.iItem=0;
				EnsureVisible(htiPosition.iItem,FALSE);
				Invalidate();
				SetEditRect();
				SetSelByEdit();
			}
			return 0;
		}
	}

	if ((m_EditInProgr&0x1)!=0 &&(message==WM_KEYDOWN || message==WM_KEYUP || message==WM_CHAR)  && EditorID!=0 && htiPosition.iSubItem>=0 && htiPosition.iItem>=0 && referGPU!=NULL && referGPU[EditorID]!=NULL && referGPU[EditorID]->UnitHWND!=NULL && wParam!=13)
	{
		if (message==WM_KEYDOWN) ::SetFocus(referGPU[EditorID]->UnitHWND);
		if (message==WM_KEYUP || message==WM_CHAR || message==WM_KEYDOWN)
			::SendMessage(referGPU[EditorID]->UnitHWND,message,wParam,lParam);
	}

	switch(message)
	{
	case GPM_DRAGMOUSELEAVE:
		if (referGPU!=NULL)
		{
			if (m_bDragging && GPC.m_DragDrop.pImageList != NULL)
			{
				POINT tmpPo;
				GetCursorPos(&tmpPo);
				OnMouseDragMove(&GPC.m_DragDrop,&tmpPo);
			}
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDragLeave","");
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
		break;
	}

	LRESULT lpr=0;
	if (message==WM_SETCURSOR && GPC.m_bWaitCursor) lpr=FALSE;
	else
	{
		try
		{
			if (message==WM_COMMAND && !::IsWindow((HWND)lParam)) lpr=NULL;
			else			lpr=CListCtrl::WindowProc(message, wParam, lParam);
		}
		catch(...)
		{
			lpr=0;
		}
	}

	if (message==WM_NOTIFY && referGPU!=NULL)
	{
		NMHDR* pNMHDR=(LPNMHDR) lParam;
		if (pNMHDR!=NULL)
		{
			LRESULT lresu;
			switch(pNMHDR->code)
			{
			case HDN_BEGINDRAG:		OnHdrBegindrag(pNMHDR,&lresu);break;
			case HDN_BEGINTRACK:	OnHdrBegintrack(pNMHDR,&lresu);break;
			case HDN_DIVIDERDBLCLICK:OnHdrDividerdblclick(pNMHDR,&lresu);break;
			case HDN_ENDDRAG:		OnHdrEnddrag(pNMHDR,&lresu);break;
			case HDN_ENDTRACK:		OnHdrEndtrack(pNMHDR,&lresu);break;
			case HDN_FILTERBTNCLICK:OnHdrFilterBtnClick(pNMHDR,&lresu);break;
			case HDN_FILTERCHANGE:	OnHdrFilterChange(pNMHDR,&lresu);break;
			case HDN_GETDISPINFO:	OnHdrGetdispinfo(pNMHDR,&lresu);break;
			case HDN_ITEMCHANGED:	OnHdrItemchanged(pNMHDR,&lresu);break;
			case HDN_ITEMCHANGING:	OnHdrItemchanging(pNMHDR,&lresu);break;
			case HDN_ITEMCLICK:		OnHdrItemclick(pNMHDR,&lresu);break;
			case HDN_ITEMDBLCLICK:	OnHdrItemdblclick(pNMHDR,&lresu);break;
			case HDN_TRACK:			OnHdrTrack(pNMHDR,&lresu);break;
			}
		}
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
		SetEditRect();
	}

	return lpr;
}

void GPListCtr::OnOdcachehint(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnOdcachehint"))
	{
		NMLVCACHEHINT* pCacheHint =(NMLVCACHEHINT*)pNMHDR;
		char str[200];
		sprintf(str,"%ld\x7F%ld",pCacheHint->iFrom,pCacheHint->iTo);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnOdcachehint",str);
	}
	*pResult = 0;
}


void GPListCtr::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
	if (referGPU && referGPU[UnitId&0xFFFF]->m_SizerArray)	Invalidate();
	SetEditRect();
	Invalidate(FALSE);
}

void GPListCtr::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
	if (referGPU && referGPU[UnitId&0xFFFF]->m_SizerArray)	Invalidate();
	SetEditRect();
	Invalidate(FALSE);
}

void GPListCtr::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ((m_EditInProgr&0x1)!=0 && nFlags==MK_LBUTTON)
	{

		hti.pt=point;
		hti.iItem=hti.iSubItem=0;
		SubItemHitTest(&hti);
		UpdateHtiPosition();
		if (hti.flags!=LVHT_ONITEMLABEL && hti.flags!=LVHT_ONITEM )
		{
			hti.iItem=hti.iSubItem=-1;
			UpdateHtiPosition();
		}
		else
		{
			CRect rei,rec;
			GetClientRect(&rec);
			GetSubItemRect(hti.iItem,hti.iSubItem,LVIR_LABEL,rei);
			if (rei.left<0) {Scroll(CSize(rei.left-2,0));Invalidate();SetEditRect();}
			else
			if (rei.Width()>rec.Width())	{Scroll(CSize(rei.left,0));Invalidate();SetEditRect();}
			else
			if (rei.right>rec.right)
			{
				Scroll(CSize(rei.right-rec.right,0));
				Invalidate();
				SetEditRect();
			}
			else SetEditRect();
			InvalidateRect(&rei);
			SetSelByEdit();
		}
	}

	try
	{
		CListCtrl::OnLButtonDown(nFlags, point);
	}
	catch(...)
	{		;}
}

bool GPListCtr::SetEditRect()
{
	UpdateHti();
	if ((m_EditInProgr&0x1)!=0 && hti.iSubItem>=0 && hti.iItem>=0 && referGPU!=NULL)
	{
		UINT EdID=0;
		GPTextArray *ar;
		try
		{
			ar=(GPTextArray *) GetItemData(hti.iItem);
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("GPListCtr", "SetEditRect","");
			ar=NULL;
		}

		if (ar!=NULL && hti.iSubItem<(int)ar->GetItemCount())
			EdID=ar->GetItemData(hti.iSubItem);

		CRect re,re2;
		GetWindowRect(&re2);

		if (EditorID!=0 && referGPU[EditorID]!=NULL && referGPU[EditorID]!=NULL && referGPU[EditorID]->UnitHWND!=NULL)
		{
			::GetWindowRect(referGPU[EditorID]->UnitHWND,&re);
		}

		if (EditorID!=(UnitId&0xFFFF)  && EditorID!=0 && EditorID!=EdID && referGPU[EditorID]!=NULL && referGPU[EditorID]!=NULL && referGPU[EditorID]->UnitHWND!=NULL)
			::SetWindowLong(referGPU[EditorID]->UnitHWND,GWL_STYLE,::GetWindowLong(referGPU[EditorID]->UnitHWND,GWL_STYLE)&(0xFFFFFFFF^WS_VISIBLE));
		else
			if ((EditorID==0 && m_StaticCursor!=NULL && m_StaticCursor->m_hWnd!=NULL)|| EditorID==0 || referGPU[EditorID]==NULL || referGPU[EditorID]==NULL || referGPU[EditorID]->UnitHWND==NULL)
			{
				::SetWindowLong(m_StaticCursor->m_hWnd,GWL_STYLE,::GetWindowLong(m_StaticCursor->m_hWnd,GWL_STYLE)&(0xFFFFFFFF^WS_VISIBLE));
				::GetWindowRect(m_StaticCursor->m_hWnd,&re);
				::InvalidateRect(m_StaticCursor->m_hWnd,&re,TRUE);
			}

		re.top-=3;	re.left-=3;
		re.OffsetRect(-re2.TopLeft());
		InvalidateRect(re);

		if (EdID!=(UnitId&0xFFFF) && EditorID!=EdID && referGPU[EdID]!=NULL && referGPU[EdID]->UnitHWND!=NULL)
		{
			LastEditorID=EditorID;
			EditorID=EdID;
			::SetWindowLong(referGPU[EditorID]->UnitHWND,GWL_STYLE,::GetWindowLong(referGPU[EditorID]->UnitHWND,GWL_STYLE)|WS_VISIBLE);
			::GetWindowRect(referGPU[EditorID]->UnitHWND,&re);

			re.top-=3;	re.left-=3;
			re.OffsetRect(-re2.TopLeft());
			::InvalidateRect(referGPU[EditorID]->UnitHWND,&re,TRUE);
			::InvalidateRect(m_hWnd,&re,TRUE);
		}
		else
		if (referGPU[EdID]==NULL || referGPU[EdID]->UnitHWND==NULL)
		{
			LastEditorID=EditorID;
			EditorID=0;
		}

		GetSubItemRect(hti.iItem,hti.iSubItem,LVIR_LABEL ,re);
		re.top-=3;

		if (EditorID!=0 && EditorID!=(UnitId&0xFFFF))
		{
			CWnd::FromHandle(referGPU[EditorID]->UnitHWND)->MoveWindow(re,FALSE);
			CWnd::FromHandle(referGPU[EditorID]->UnitHWND)->Invalidate();
		}
		else
			if (m_StaticCursor!=NULL && m_StaticCursor->m_hWnd!=NULL)
			{
				m_StaticCursor->ModifyStyle(0,WS_VISIBLE);
				m_StaticCursor->MoveWindow(re,FALSE);
				m_StaticCursor->Invalidate();
			}
		UpdateHtiPosition();
	}
	return TRUE;
}


void GPListCtr::SetSelByEdit(UINT flg)
{
	UpdateHti();
	if ((m_EditInProgr&0x41)==0x1 &&(GetAsyncKeyState(VK_SHIFT)&0xFF00)==0 &&(GetAsyncKeyState(VK_CONTROL)&0xFF00)==0 && hti.iItem!=-1)
		SetItemState(hti.iItem,0,LVIS_SELECTED|LVIS_FOCUSED|LVIS_ACTIVATING );

	if ((m_EditInProgr&0x1)!=0)
	{
		if ((lasthti.iItem!=hti.iItem || lasthti.iSubItem!=hti.iSubItem || flg!=0) && referGPU!=NULL)
		{
			CString str;
			str.Format("%d\x7F%d\x7F%d\x7F%d",lasthti.iItem,lasthti.iSubItem,hti.iItem,hti.iSubItem);
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnEditPos",(LPCSTR)str);
		}

		if ((lasthti.iItem!=hti.iItem || lasthti.iSubItem!=hti.iSubItem || flg!=0) && referGPU!=NULL)
		{
			{
				char *oStr=new char [10000];
				referGPU[LastEditorID]->DoWindowMethod("GetWindowText",oStr);
				LastEditResult=oStr;
				delete[] oStr;
			}
			CString str;
			CString Oldstr;
			if (LastEditorID && AutoUpdate==TRUE && referGPU[LastEditorID]!=NULL && referGPU[LastEditorID]->UnitHWND!=NULL)
				Oldstr=GetItemText(lasthti.iItem,lasthti.iSubItem);
			if (AutoUpdate==TRUE &&((lasthti.iItem>=0 && lasthti.iSubItem>=0  && LastEditorID!=0 && MayBeChangeEdit==TRUE) || flg!=0) && referGPU[LastEditorID]!=NULL && referGPU[LastEditorID]->UnitHWND!=NULL)
	//		&& referGPU[LastEditorID]!=NULL && referGPU[LastEditorID]->UnitHWND!=NULL && LastEditorID!=0 && LastEditorID!=UnitId)
			{
				if (Oldstr!=LastEditResult && LastEditorID)
				{
					GPTextArray *ar=NULL;
					Oldstr=LastEditResult;
					if ((m_EditInProgr&0x41)==0x1) SetItemText(lasthti.iItem,lasthti.iSubItem,(LPCSTR)LastEditResult);
					if (lasthti.iItem>=0 && lasthti.iItem<GetItemCount() && (m_EditInProgr&0x41)==0x1)
					{
						try
						{
							ar=(GPTextArray *) GetItemData(lasthti.iItem);
						}
						catch(...)
						{
							GPC.m_ErrReport.GPWriteErrorLog("GPListCtr", "SetSelByEdit 4790","");
							ar=NULL;
						}
					}

					if (ar!=NULL && (m_EditInProgr&0x41)==0x1)
						ar->SetItem(lasthti.iSubItem,(LPCSTR)LastEditResult);
				}
			}

			MayBeChangeEdit=FALSE;
			str.Format("%d\x7F%d\x7F%d\x7F%d\x7F",lasthti.iItem,lasthti.iSubItem,hti.iItem,hti.iSubItem);
			str+=Oldstr+"\x7F";
			str+=GetItemText(hti.iItem,hti.iSubItem)+"\x7F";
			int i;
			for(i=0;i<1000;i++)
			{
				if (iArrPosExOut[i]>=0)
				{
					try
					{str+=GetItemText(lasthti.iItem,iArrPosExOut[i])+"\x7F";}
					catch(...)
					{
						GPC.m_ErrReport.GPWriteErrorLog("GPListCtr", "SetSelByEdit 4813","");
					}
				}
			}

			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnEditPosEx",(LPCSTR)str);
			if ((m_EditInProgr&0x41)==0x1)
			{
				lasthti=hti;
				LastEditorID=EditorID;
			}
			else hti=lasthti;
		}

		if ((m_EditInProgr&0x41)==0x1 && EditorID!=0 && EditorID!=UnitId && referGPU!=NULL && referGPU[EditorID]!=NULL && hti.iItem!=-1 && hti.iSubItem!=-1)
		{
			referGPU[EditorID]->GPSetProperty("VISIBLE=TRUE");
			CString str("TEXT=");
			str+=GetItemText(hti.iItem, hti.iSubItem );
			referGPU[EditorID]->GPSetProperty((LPCSTR)str);
		}
		UpdateHtiPosition();
	}
}

void GPListCtr::OnKillFocus(CWnd* pNewWnd)
{
	CListCtrl::OnKillFocus(pNewWnd);
	MayBeChangeEdit=TRUE;
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

int GPListCtr::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if ((lpCreateStruct->style&LVS_OWNERDATA)==LVS_OWNERDATA)
	{
		m_VirtualData= new CTableDataContainer;
	}
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_StaticCursor=new CStatic;
	m_StaticCursor->Create("",SS_BLACKFRAME,CRect(0,0,1,1),this);

	return 0;
}

BOOL GPListCtr::PreTranslateMessage(MSG* pMsg)
{
//	TRACE("%d\n",pMsg->message);
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		referGPU[UnitId&0xFFFF]->m_CurPreMessage=pMsg;
		if (referGPU[UnitId&0xFFFF]->m_ToolTip && *(referGPU[UnitId&0xFFFF]->m_ToolTip))
			(*(referGPU[UnitId&0xFFFF]->m_ToolTip))->RelayEvent(pMsg);

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
		}
	}

	if (pMsg->message==WM_KEYDOWN &&(m_EditInProgr&0x1)!=0 && hti.iItem!=-1 && hti.iSubItem!=-1)
	{
		if (pMsg->wParam==13) PostMessage(GPM_NEXTCELL,0,0);
		else
		if (pMsg->wParam==27) PostMessage(GPM_ESCCELL,0,0);
		else
		if (pMsg->wParam==46 && /*pMsg->lParam==0x09530001 &&*/(m_EditInProgr&32)!=0 && EditorID!=0 && referGPU!=NULL && referGPU[EditorID]!=NULL && pMsg->hwnd==m_hWnd)
		{
			PostMessage(GPM_ESCCELL,0,0);
			PostMessage(GPM_NEXTCELL,0,0);
			PostMessage(GPM_DELCELL,hti.iItem+hti.iSubItem*0x10000,0);
			SetItemText(hti.iItem,hti.iSubItem,"");
			char str[50];
			sprintf(str,"%d\x7F%d",hti.iItem,hti.iSubItem);
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClearSubItem",str);
		}
	}

	if (pMsg->message==GPM_DELCELL)
	{
		SetItemText(pMsg->wParam&0xFFFF,pMsg->wParam/0x10000,"");

	}
	else
	if (pMsg->message==GPM_UPDATELVEDITOR)
	{
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnKillFocus","hhhhhhhhh");
	}
	return CListCtrl::PreTranslateMessage(pMsg);
}

void GPListCtr::OnRButtonDown(UINT nFlags, CPoint point)
{
	RBhti.pt=point;
	RBhti.iItem=hti.iSubItem=0;
	SubItemHitTest(&RBhti);
	if (RBhti.flags!=LVHT_ONITEMLABEL && RBhti.flags!=LVHT_ONITEM ) RBhti.iItem=RBhti.iSubItem=-1;
	else
	{
		if ((m_EditInProgr&0x1)!=0 && nFlags==MK_RBUTTON)
		{
			CRect rei,rec;
			hti=RBhti;
			UpdateHtiPosition();
			GetClientRect(&rec);
			GetSubItemRect(RBhti.iItem,RBhti.iSubItem,LVIR_LABEL,rei);
			if (rei.left<0) {Scroll(CSize(rei.left-2,0));Invalidate();SetEditRect();}
			else
			if (rei.Width()>rec.Width())	{Scroll(CSize(rei.left,0));Invalidate();SetEditRect();}
			else
			if (rei.right>rec.right)
			{
				Scroll(CSize(rei.right-rec.right,0));
				Invalidate();
				SetEditRect();
			}
			else SetEditRect();
			InvalidateRect(&rei);
			SetSelByEdit();
		}
	}
	CListCtrl::OnRButtonDown(nFlags, point);
}

void GPListCtr::OnClose()
{
	if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClose","");
//	CListCtrl::OnClose();
}

void GPListCtr::OnSizing(UINT fwSide, LPRECT pRect)
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

	if (EnableSz) CListCtrl::OnSizing(fwSide, pRect);

	GetParent()->SendMessage(GPN_UPDATESIZE);
}

void GPListCtr::FillNmListViewStr(NM_LISTVIEW *plv, char *str)
{
	str[100]=0;
	int len=GetItemText(plv->iItem,0,str+100,1900);

	if (len<=0) str[100]=0;
	else str[len+100]=0;

	sprintf(str,"%d\x7F%d\x7F%ld\x7F%ld\x7F%ld\x7F%s",
		plv->iItem,plv->iSubItem,plv->uNewState,plv->uOldState,plv->uChanged,str+100);
}

void GPListCtr::OnTimer(UINT nIDEvent)
{
	if (nIDEvent==VIRTUAL_LIST_TIMER_ID)
	{
		KillTimer(VIRTUAL_LIST_TIMER_ID);
		if (m_VirtualData && referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)
		{
			DWORD dwStart=0,dwCount=0;
			m_VirtualData->GetRequest(dwStart,dwCount);
			if (dwCount)
			{
				char str[100];
				sprintf(str,"%d\x7F%d",dwStart,dwCount);
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnVLRequest",str);
			}

		}
	}

	CListCtrl::OnTimer(nIDEvent);
}

void GPListCtr::OnDragMouseHover()
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
		int UpDelta=0;
		if ((GetStyle()&LVS_NOCOLUMNHEADER)!=LVS_NOCOLUMNHEADER)
		{
			CHeaderCtrl *t= GetHeaderCtrl();
			if (t)
			{
				CRect re;
				t->GetWindowRect(&re);
				UpDelta=re.Height();
			}
		}

		if (point.y >= 0 && point.y <= referGPU[UnitId&0xFFFF]->m_nScrollMargin+UpDelta)
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
			else
				::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);

		int nItem=HitTest(point);
		if (nItem>=0)
		{
			CString tmps;
			tmps.Format("%d\x07%s",nItem,(LPCSTR)GetItemText(nItem,0));
			referGPU[UnitId&0xFFFF]->SendDropHoverEvent(tmps,&GPC.m_DragDrop,&point);
		}
	}
}

void GPListCtr::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
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

		DWORD dnItem=0xFFFFFFFF;
		BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
		// Highlight the drop target if the cursor is over an item.
		if (mDrop)
			dnItem = HighlightDropTarget(pDrDrStruct, CPoint(*point));
		// Modify the cursor to provide visual feedback to the user. Note: It's important to do this AFTER the call to DragMove.
		::SetCursor(dnItem==0xFFFFFFFF ?
			AfxGetApp()->LoadStandardCursor(IDC_NO) :
			(HCURSOR) ::GetClassLong(m_hWnd, GCL_HCURSOR));

		int nItem=HitTest(*point);
		if (nItem>=0)
		{
			CString tmps;
			tmps.Format("%d\x07%s",nItem,(LPCSTR)GetItemText(nItem,0));
			referGPU[UnitId&0xFFFF]->SendDropMoveEvent(tmps,pDrDrStruct,point);
		}
		// Set a timer if the cursor is at the top or bottom of the window, or if it's over a collapsed item.
		if (mDrop)
		{
			CRect rect;
			GetClientRect(rect);
			//int cy = rect.Height();
			int UpDelta=0;
			if ((GetStyle()&LVS_NOCOLUMNHEADER)!=LVS_NOCOLUMNHEADER)
			{
				CHeaderCtrl *t= GetHeaderCtrl();
				if (t)
				{
					CRect re;
					t->GetWindowRect(&re);
					UpDelta=re.Height();
				}
			}
			::SetTimer(pDrDrStruct->hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nDelayInterval, NULL);
		}
	}
}

void GPListCtr::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;

	if (m_LastDropTarget>=0)
		SetItemState(m_LastDropTarget,0,LVIS_DROPHILITED);
	m_LastDropTarget=-1;

	if (pDrDrStruct && mDrop && referGPU)
	{
		::ScreenToClient(m_hWnd,point);
		CString tmp;
		int nItem=HitTest(*point);
		if (nItem>=0)
			tmp.Format("%d\x7%s",nItem,(LPCSTR)GetItemText(nItem,0));
		else
			tmp="-1\x7";
		referGPU[UnitId&0xFFFF]->SendDropEvent(tmp,pDrDrStruct,point);
	}
}

DWORD GPListCtr::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	DWORD ret=0xFFFFFFFF;

	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && referGPU)
	{
		pDrDrStruct->pImageList->DragShowNolock(FALSE);

		if (m_LastDropTarget>=0)
			SetItemState(m_LastDropTarget,0,LVIS_DROPHILITED);
		CString tmp;

		int nItem=m_LastDropTarget=HitTest(point);
		if (nItem>=0)
		{
			ret=nItem;
			SetItemState(nItem,LVIS_DROPHILITED,LVIS_DROPHILITED);
		}

		UpdateWindow();
		pDrDrStruct->pImageList->DragShowNolock(TRUE);
	}
	return ret;
}

LRESULT GPListCtr::OnNcHitTest(CPoint point)
{
	LRESULT ret=CListCtrl::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

void GPListCtr::OnMouseMove(UINT nFlags, CPoint point)
{
	CListCtrl::OnMouseMove(nFlags, point);

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

void GPListCtr::OnLButtonUp(UINT nFlags, CPoint point)
{
	CListCtrl::OnLButtonUp(nFlags, point);

	if (m_bDragging && GPC.m_DragDrop.pImageList != NULL)
	{
		// Stop the scroll timer if it's running.
		KillTimer(DRAG_TIMER_ID);

		// Terminate the dragging operation and release the mouse.
		GPC.m_DragDrop.pImageList->DragLeave(CWnd::FromHandle(GPC.m_DragDrop.hWndLast));
		GPC.m_DragDrop.pImageList->EndDrag();
		::ReleaseCapture();
		m_bDragging = FALSE;

		// Delete the image list created by CreateDragImage.
		delete GPC.m_DragDrop.pImageList;
		GPC.m_DragDrop.pImageList = NULL;

		POINT tmpPo=point;
		ClientToScreen(&tmpPo);
		HWND tmpHWND=::WindowFromPoint(tmpPo);
		if (tmpHWND)
			::SendMessage(tmpHWND,GPM_DROPITEMS,(WPARAM)&GPC.m_DragDrop,(LPARAM)&tmpPo);
		m_iDragItem = -1;
	}

	{
		LVHITTESTINFO lv={0};
		lv.pt=point;
		SubItemHitTest(&lv);
		char *cflg[8]={"LVHT_ABOVE|","LVHT_BELOW|","LVHT_NOWHERE|","LVHT_ONITEMICON|","LVHT_ONITEMLABEL|","LVHT_ONITEMSTATEICON|","LVHT_TOLEFT|","LVHT_TORIGHT|",};
		UINT  uflg[8]={LVHT_ABOVE,LVHT_BELOW,LVHT_NOWHERE,LVHT_ONITEMICON,LVHT_ONITEMLABEL,LVHT_ONITEMSTATEICON,LVHT_TOLEFT,LVHT_TORIGHT,};
		int i;
		char flags[250];*flags=0;

		for(i=0;i<8;i++)
			if ((lv.flags&uflg[i])==uflg[i]) strcat(flags,cflg[i]);

		char str[200];
		sprintf(str,"%d\x7F%d\x7F%d\x7F%d\x7F%s",lv.iItem,lv.iSubItem,lv.pt.x,lv.pt.y,flags);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnLUPTest",str);
	}
}

void GPListCtr::OnRButtonUp(UINT nFlags, CPoint point)
{

	CListCtrl::OnRButtonUp(nFlags, point);
	{
		LVHITTESTINFO lv={0};
		lv.pt=point;
		SubItemHitTest(&lv);
		char *cflg[8]={"LVHT_ABOVE|","LVHT_BELOW|","LVHT_NOWHERE|","LVHT_ONITEMICON|","LVHT_ONITEMLABEL|","LVHT_ONITEMSTATEICON|","LVHT_TOLEFT|","LVHT_TORIGHT|",};
		UINT  uflg[8]={LVHT_ABOVE,LVHT_BELOW,LVHT_NOWHERE,LVHT_ONITEMICON,LVHT_ONITEMLABEL,LVHT_ONITEMSTATEICON,LVHT_TOLEFT,LVHT_TORIGHT,};
		int i;
		char flags[250];*flags=0;

		for(i=0;i<8;i++)
			if ((lv.flags&uflg[i])==uflg[i]) strcat(flags,cflg[i]);

		char str[200];
		sprintf(str,"%d\x7F%d\x7F%d\x7F%d\x7F%s",lv.iItem,lv.iSubItem,lv.pt.x,lv.pt.y,flags);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnRUPTest",str);
	}

}

void GPListCtr::OnSetFocus(CWnd* pOldWnd)
{
	CListCtrl::OnSetFocus(pOldWnd);
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


void GPListCtr::ChangeHTI(int deltaVer, int deltaHor)
{


}

void GPListCtr::UpdateHtiPosition()
{
	htiPosition.iItem=-1;
	htiPosition.iSubItem=-1;
	UINT nCol=1;
	CHeaderCtrl *tmpHead=NULL;
	if (m_hWnd)
	{
		try
		{
			tmpHead=GetHeaderCtrl();
			if (tmpHead!=NULL)
			{
				nCol=tmpHead->GetItemCount();
			}
		}catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("GPListCtr", "UpdateHtiPosition","");
			nCol=0;
		}
	}

	if (tmpHead && nCol>0 && hti.iItem>=0)
	{
		int *Order=new int [nCol+5];
		GetColumnOrderArray(Order,nCol);
		htiPosition.iItem=hti.iItem;
		for(htiPosition.iSubItem=0;htiPosition.iSubItem<(int)nCol;htiPosition.iSubItem++)
			if (Order[htiPosition.iSubItem]==hti.iSubItem) break;
		if (htiPosition.iSubItem==(int)nCol) htiPosition.iSubItem=hti.iSubItem;

		if (Order) delete[] Order;
	}
	else htiPosition=hti;
}

void GPListCtr::UpdateHti()
{
	UINT nCol=1;
	CHeaderCtrl *tmpHead=GetHeaderCtrl();
	if (tmpHead!=NULL)
	{
		try
		{
			nCol=tmpHead->GetItemCount();
		}catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("GPListCtr", "UpdateHti","");
			nCol=1;
		}
	}
	if (tmpHead && nCol>0 && htiPosition.iItem>=0)
	{
		int *Order=new int [nCol+5];
		GetColumnOrderArray(Order,nCol);
		hti.iItem=htiPosition.iItem;
		hti.iSubItem=Order[htiPosition.iSubItem];
		if (Order) delete[] Order;
	}
	else hti=htiPosition;
}

void GPListCtr::OnSize(UINT nType, int cx, int cy)
{
	CListCtrl::OnSize(nType, cx, cy);

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
	}
}

void GPListCtr::OnBeginScroll(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL)
	{
		LPNMLVSCROLL pNMListView =(LPNMLVSCROLL)pNMHDR;
		char str[300];
		sprintf(str,"%d\x7F%d",	pNMListView->dx, pNMListView->dy);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnBeginScroll",str);
	}
	*pResult = 0;
}

void GPListCtr::OnEndScroll(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL)
	{
		LPNMLVSCROLL pNMListView =(LPNMLVSCROLL)pNMHDR;
		char str[300];
		sprintf(str,"%d\x7F%d",	pNMListView->dx, pNMListView->dy);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnEndScroll",str);
	}
	*pResult = 0;
}

void GPListCtr::OnGetInfotip(NMHDR* pNMHDR, LRESULT* pResult)
{

	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnGetInfotip"))
	{
		LPNMLVGETINFOTIP pNMListView =(LPNMLVGETINFOTIP)pNMHDR;
		CString str;
		str.Format("%d\x7F%d\x7F%d\x7F%s",pNMListView->dwFlags,pNMListView->iItem,pNMListView->iSubItem,pNMListView->pszText?pNMListView->pszText:"");
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnGetInfotip",str);
	}
	*pResult = 0;
}

void GPListCtr::OnHotTrack(NMHDR* pNMHDR, LRESULT* pResult)
{

	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnHotTrack"))
	{
		NM_LISTVIEW* pNMListView =(NM_LISTVIEW*)pNMHDR;
		char str[300];
		sprintf(str,"%d\x7F%d\x7F%X\x7F%ld\x7F%ld",	pNMListView->iItem,	pNMListView->iSubItem,(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnHotTrack",str);
	}

	*pResult = 0;
}

void GPListCtr::OnItemActivate(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL && referGPU[UnitId&0xFFFF]->GPMSG && referGPU[UnitId&0xFFFF]->GPMSG->FindInActive("OnItemActivate"))
	{
		LPNMITEMACTIVATE pNMListView =(LPNMITEMACTIVATE)pNMHDR;
		CString str;
		str.Format("%d\x7F%d\x7F%d\x7F%d\x7F%s\x7F%s\x7F%s\x7F",
			pNMListView->iItem,
			pNMListView->iSubItem,
			pNMListView->ptAction.x,
			pNMListView->ptAction.y,
			(LPCSTR)IStateToString(pNMListView->uNewState),
			(LPCSTR)IStateToString(pNMListView->uOldState),
			(LPCSTR)IMaskToString(pNMListView->uChanged));

		if (pNMListView->uKeyFlags==LVKF_ALT) str+="LVKF_ALT|";
		if (pNMListView->uKeyFlags==LVKF_CONTROL) str+="LVKF_CONTROL|";
		if (pNMListView->uKeyFlags==LVKF_SHIFT) str+="LVKF_SHIFT|";

		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnItemActivate",str);
	}

	*pResult = 0;
}

void GPListCtr::OnMarqueeBegin(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (referGPU!=NULL)
	{
		char str[200];
		sprintf(str,"%X\x7F%ld\x7F%ld",(DWORD)pNMHDR->hwndFrom,pNMHDR->idFrom,pNMHDR->code);
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnMarqueeBegin",str);
	}

	*pResult = 0;
}


const CString GPListCtr::IStateToString(UINT iState)
{
	CString ret;
	UINT i;
	for(i=0;i<uNIState;i++)
		if ((iState&uArrIState[i])==uArrIState[i])
		{
			if (ret=="") ret=cArrIState[i];
			else {ret+="|";ret+=cArrIState[i];}
		}
	return ret;
}

UINT GPListCtr::StringToIState(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNIState;i++)
			ret|=uArrIState[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNIState;i++)
			if (tmps.Find(cArrIState[i],0)>=0) ret|=uArrIState[i];
	}

	return ret;
}

const CString GPListCtr::IMaskToString(UINT iMask)
{
	CString ret;
	UINT i;
	for(i=0;i<uNIMask;i++)
		if ((iMask&uArrIMask[i])==uArrIMask[i])
		{
			if (ret=="") ret=cArrIMask[i];
			else {ret+="|";ret+=cArrIMask[i];}
		}
	return ret;
}

UINT GPListCtr::StringToIMask(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNIMask;i++)
			ret|=uArrIMask[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNIMask;i++)
			if (tmps.Find(cArrIMask[i],0)>=0) ret|=uArrIMask[i];
	}
	return ret;
}

const CString GPListCtr::GrMaskToString(UINT GrMask)
{
	CString ret;
	UINT i;
	for(i=0;i<uNGrMask;i++)
		if ((GrMask&uArrGrMask[i])==uArrGrMask[i])
		{
			if (ret=="") ret=cArrGrMask[i];
			else {ret+="|";ret+=cArrGrMask[i];}
		}
	return ret;
}

UINT GPListCtr::StringToGrMask(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNGrMask;i++)
			ret|=uArrGrMask[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNGrMask;i++)
			if (tmps.Find(cArrGrMask[i],0)>=0) ret|=uArrGrMask[i];
	}
	return ret;
}

const CString GPListCtr::GrAlignToString(UINT iAlign)
{
	CString ret;
	UINT i;
	for(i=0;i<uNGRAlign;i++)
		if ((iAlign&uArrGRAlign[i])==uArrGRAlign[i])
		{
			if (ret=="") ret=cArrGRAlign[i];
			else {ret+="|";ret+=cArrGRAlign[i];}
		}
	return ret;
}

UINT GPListCtr::StringToGrAlign(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNGRAlign;i++)
			ret|=uArrGRAlign[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNGRAlign;i++)
			if (tmps.Find(cArrGRAlign[i],0)>=0) ret|=uArrGRAlign[i];
	}

	return ret;
}

const CString GPListCtr::LViewToString(UINT iLView)
{
	CString ret;
	UINT i;
	for(i=0;i<uNLView;i++)
		if ((iLView&uArrLView[i])==uArrLView[i])
		{
			if (ret=="") ret=cArrLView[i];
			else {ret+="|";ret+=cArrLView[i];}
		}
	return ret;
}

UINT GPListCtr::StringToLView(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNLView;i++)
			ret|=uArrLView[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNLView;i++)
			if (tmps.Find(cArrLView[i],0)>=0) ret|=uArrLView[i];
	}

	return ret;
}

const CString GPListCtr::GrStateToString(UINT iGrState)
{
	CString ret;
	UINT i;
	for(i=0;i<uNGrState;i++)
		if ((iGrState&uArrGrState[i])==uArrGrState[i])
		{
			if (ret=="") ret=cArrGrState[i];
			else {ret+="|";ret+=cArrGrState[i];}
		}
	return ret;
}

UINT GPListCtr::StringToGrState(const char* iStr)
{
	UINT ret=0;
	if (iStr==NULL)
	{
		UINT i;
		for(i=0;i<uNGrState;i++)
			ret|=uArrGrState[i];
	}
	else
	{
		CString tmps=iStr;
		tmps.MakeUpper();
		tmps+="|";
		tmps.Replace(" ","");

		UINT i;
		for(i=0;i<uNGrState;i++)
			if (tmps.Find(cArrGrState[i],0)>=0) ret|=uArrGrState[i];
	}

	return ret;
}


HBRUSH GPListCtr::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CListCtrl::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}

int GPListCtr::AddChar(char iChar, DWORD iFlags)
{
	int ret=0;
	if (iChar && !m_VirtualData)
	{
		GPTextArray *ar=NULL;
		int nItem=GetItemCount();
		CString text="";
		if (nItem) 
		{
			text=GetItemText(--nItem,m_DOSubItem);
			ar=(GPTextArray *)GetItemData(nItem);
		}
		else 
		{
			nItem=InsertItem(0,"",m_DefItemImage);
			ar=new GPTextArray;
			SetItemData(nItem,(DWORD)ar);
		}

		if (m_LCDOflag && iChar && ar)
		{
			char *tmppos=(char *)ar->GetItem(0);
			if (tmppos==NULL || *tmppos==0) DeleteItem(nItem--);
			m_DOSubItem=0;
			nItem=InsertItem(++nItem,"",m_DefItemImage);
			ar=new GPTextArray;
			SetItemData(nItem,(DWORD)ar);
			text="";
		}
		m_LCDOflag=0;


		if (iChar==10 && (iFlags&0x2))
		{
			text="";
			m_DOSubItem=0;
			DeleteItem(nItem);
			nItem=InsertItem(nItem,"",m_DefItemImage);
			ar=new GPTextArray;
			SetItemData(nItem,(DWORD)ar);
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
			SetItemText(nItem,m_DOSubItem,text);
			if (ar) ar->SetItem(m_DOSubItem,text);
		}
		else 
		if ((iChar==9 && (iFlags&0x40)==0) || (iChar==GPC.DelimiterIn2 && (iFlags&0x10)))
		{
			m_DOSubItem++;
			int nCols=0;
			CHeaderCtrl *tmp=GetHeaderCtrl();
			if (tmp) nCols=tmp->GetItemCount();

			if (m_DOSubItem>=nCols) 
			{
				m_DOSubItem=nCols-1;
				text+=" ";
				SetItemText(nItem,m_DOSubItem,text);
				ar->SetItem(m_DOSubItem,text);
			}
		}
		else 
		if (iChar) 
		{
			text+=iChar;
			SetItemText(nItem,m_DOSubItem,text);
			if (ar) ar->SetItem(m_DOSubItem,text);
		}
		ret=text.GetLength();
	}
	return ret;
}

