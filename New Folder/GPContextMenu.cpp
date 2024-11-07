// GPContextMenu.cpp: implementation of the CGPContextMenu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPContextMenu.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


const UINT CGPContextMenu::uNMethods=15;
const char *CGPContextMenu::cArrMethods[]={
		"DeleteMenu",	"RenameMenu",	"TrackMenu",	"CreatePopupMenu",	"InsertMenuItem",
		"InsertSeparator",	"SetOutputString",	"SetDescription",	"Load",	"LoadMenu",
		"AppendFromFile",	"Save",	"SaveMenu",	"Execute",	"DeleteAllItems",
		"",	"",	"",	"",	"",
		"",	"",	"",	"",	"",
	};
const char *CGPContextMenu::cArrMethodsParams[]={
		"MenuName[,position]",	"Name1,Name2",	"MenuName[,[px],[py][,flags]]",	"ParentName,[InsertBefore],PopupMenuName,PopupMenuText",	"ParentName,[InsertBefore],MenuName,MenuText;MenuOutput",
		"ParentName,[InsertBefore][,SeparatorName]",	"MenuName,[position],OutputString",	"MenuName,[position],Description",	"FileName[,InitDir]",	"MenuName,FileName[,InitDir]",
		"MenuName,FileName[,InitDir]",	"FileName[,InitDir]",	"MenuName,FileName[,InitDir]",	"MenuName",	"",
		"",	"",	"",	"",	"",
		"",	"",	"",	"",	"",
	};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGPContextMenu::CGPContextMenu(GPMenu *pGPMenu)
{
	m_pGPMenu=pGPMenu;
	m_nArr=0;
	m_nMaxArr=200;
	m_ArrayIdMenuInfo=new DWORD[m_nMaxArr];

	UINT i;
	for(i=0;i<m_nMaxArr;i++)
		m_ArrayIdMenuInfo[i]=-1;

	m_Menu=::CreatePopupMenu();
}

CGPContextMenu::~CGPContextMenu()
{
	if (m_ArrayIdMenuInfo)
	{
		DeleteAllItems();
		m_nMaxArr=0;
		delete[] m_ArrayIdMenuInfo;
		m_ArrayIdMenuInfo=NULL;
	}

	if (m_Menu) DestroyMenu(m_Menu);
	m_Menu=NULL;
}

CGPContextMenu & CGPContextMenu::operator= (const CGPContextMenu &iCGPContextMenu)
{
	if (this!=&iCGPContextMenu && &iCGPContextMenu)
	{
		DeleteAllItems();
		if (m_Menu==NULL)
			m_Menu=::CreatePopupMenu();
		if (m_ArrayIdMenuInfo==NULL)
		{
			if (m_nMaxArr==0) m_nMaxArr=200;
			m_ArrayIdMenuInfo=new DWORD[m_nMaxArr];
			UINT i;
			for(i=0;i<m_nMaxArr;i++)
				m_ArrayIdMenuInfo[i]=-1;
		}
		m_nArr=0;

		if (iCGPContextMenu.m_nArr)
			AddFromOther(&iCGPContextMenu,iCGPContextMenu.m_Menu,m_Menu);
	}
	return *this;
}

UINT CGPContextMenu::AddFromOther(const CGPContextMenu *iArr, HMENU iHMENU, HMENU destHMENU)
{
	if (iArr && iHMENU)
	{
		if (m_Menu==NULL) m_Menu=::CreatePopupMenu();
		if (m_ArrayIdMenuInfo==NULL)
		{
			if (m_nMaxArr==0) m_nMaxArr=200;
			m_ArrayIdMenuInfo=new DWORD[m_nMaxArr];
			UINT i;
			for(i=0;i<m_nMaxArr;i++) m_ArrayIdMenuInfo[i]=-1;
			m_nArr=0;
		}

		MENUITEMINFO mi={0};
		mi.cbSize=sizeofMENUITEMINFO;

		UINT i;
		for(i=0;i<iArr->m_nArr;i++)
		{
			PGPMENUINFO pMUSrc=NULL;
			if (iArr->m_ArrayIdMenuInfo && iArr->m_ArrayIdMenuInfo[i]!=-1 && (pMUSrc=&(iArr->m_pGPMenu->MENUINFOArray[iArr->m_ArrayIdMenuInfo[i]]))->hMenu==iHMENU)
			{
				DWORD item=AddItem();
				if (destHMENU==NULL) destHMENU=::CreatePopupMenu();
				if (pMUSrc->csContext=="") pMUSrc->csContext="CustomMenu";
				m_ArrayIdMenuInfo[item]=m_pGPMenu->RegisterMenuItem(*pMUSrc);
				PGPMENUINFO pMUDst=&(m_pGPMenu->MENUINFOArray[item]);
				pMUDst->hMenu=destHMENU;
				if (pMUDst->csContext=="") pMUDst->csContext="CustomMenu";
				mi.dwTypeData=(char *)(LPCSTR)pMUDst->csText;
				mi.cch=(int)pMUDst->csText.GetLength();
				mi.hSubMenu=NULL;


				if (pMUSrc->hSubMenu)
				{//SUBMENU
					pMUDst->hSubMenu=::CreatePopupMenu();
					#ifdef W_95
						mi.fMask=MIIM_SUBMENU|MIIM_TYPE|MIIM_DATA;
						mi.fType=MFT_STRING;
					#else
						#ifdef W_NT
							mi.fMask=MIIM_SUBMENU|MIIM_TYPE|MIIM_DATA;
							mi.fType=MFT_STRING;
						#else
							mi.fMask=MIIM_SUBMENU|MIIM_STRING|MIIM_DATA;
						#endif
					#endif
					mi.dwItemData=item;
					mi.hSubMenu=pMUDst->hSubMenu;





//						mi.dwItemData=RegisterMenuItem(((DWORD)ihPopup)|0x80000000,(UINT)mii.wID, GPC.csODCTerminalMenuName, menuText2, dwFlags);
					::InsertMenuItem(pMUDst->hMenu,-1,TRUE,&mi);

//	
//						UINT j;
//						for(j=0;j<iArr->m_nArr;j++)
//							if (iArr->m_Arr[j]->hMenu==iArr->m_Arr[i]->hSubMenu)
					AddFromOther(iArr, pMUSrc->hSubMenu, pMUDst->hSubMenu);
				}
				else
				if (pMUSrc->dwCmd==0)
				{//SEPARATOR
					mi.dwTypeData=NULL;
					#ifdef W_95
						mi.fMask=MIIM_TYPE|MIIM_DATA;
					#else
						#ifdef W_NT
							mi.fMask=MIIM_TYPE|MIIM_DATA;
						#else
							mi.fMask=MIIM_FTYPE|MIIM_DATA;
						#endif
					#endif
					mi.fType=MFT_SEPARATOR;
					mi.dwItemData=item;
					mi.wID=0;
					::InsertMenuItem(pMUDst->hMenu,-1,TRUE,&mi);
				}
				else
				{//MENUITEM
					#ifdef W_95
						mi.fMask=MIIM_TYPE|MIIM_ID|MIIM_DATA;
						mi.fType=MFT_STRING;
					#else
						#ifdef W_NT
							mi.fMask=MIIM_TYPE|MIIM_ID|MIIM_DATA;
							mi.fType=MFT_STRING;
						#else
							mi.fMask=MIIM_STRING|MIIM_ID|MIIM_DATA;
						#endif
					#endif
					mi.dwItemData=item;
					mi.wID=pMUDst->dwCmd;
					::InsertMenuItem(pMUDst->hMenu,-1,TRUE,&mi);
				}
			}
		}
	}
	return m_nArr;
}

DWORD CGPContextMenu::AddItem()
{
	DWORD ret=-1;
	if (m_ArrayIdMenuInfo)
	{
		while(m_nArr>=m_nMaxArr)
		{
			DWORD *tmp=new DWORD[m_nMaxArr+100];
			UINT i;
			for(i=0;i<m_nMaxArr;i++) tmp[i]=m_ArrayIdMenuInfo[i];

			m_nMaxArr+=100;
			for(;i<m_nMaxArr;i++)	tmp[i]=-1;

			delete[] m_ArrayIdMenuInfo;
			m_ArrayIdMenuInfo=tmp;
		}
		ret=m_nArr++;
	}
	return ret;
}

PGPMENUINFO CGPContextMenu::ClearItem(PGPMENUINFO iItem)
{
	if (iItem)
	{
		iItem->csDescription="";
		iItem->csName="";
		iItem->csText="";
		iItem->csOut="";
		iItem->dwCmd=0;
		iItem->dwData=0;
		iItem->dwPtr=0;
		iItem->hMenu=NULL;
		iItem->hSubMenu=NULL;
		iItem->dwFlags=1;
		iItem->dwPopupId=0;
		iItem->csContext="CustomMenu";
		iItem->csImageList="";
		iItem->dwImage=0;
	}

	return iItem;
}

UINT CGPContextMenu::DeleteItem(PGPMENUINFO iItem)
{
	if (iItem)
	{
		UINT i;
		if (iItem->hSubMenu)
		{
			for(i=0;i<m_nArr;i++)
			{
				if (m_ArrayIdMenuInfo[i]!=-1 && (m_pGPMenu->MENUINFOArray[m_ArrayIdMenuInfo[i]]).hMenu==iItem->hSubMenu)
				{
					DeleteItem(&(m_pGPMenu->MENUINFOArray[m_ArrayIdMenuInfo[i--]]));
				}
			}
			if (iItem->hMenu)
			{
				int nItems=::GetMenuItemCount(iItem->hMenu);
				int j;
				for(j=0;j<nItems && ::GetSubMenu(iItem->hMenu,j)!=iItem->hSubMenu;j++);

				if (j<nItems)
				{
					::RemoveMenu(iItem->hMenu,j,MF_BYPOSITION);
				}
			}
			::DestroyMenu(iItem->hSubMenu);
			iItem->hSubMenu=NULL;
		}

		for(i=0;i<m_nArr;i++)
		{
			if (&(m_pGPMenu->MENUINFOArray[m_ArrayIdMenuInfo[i]])==iItem)
			{
				DeleteItem((UINT)i--);
			}
		}
	}

	return m_nArr;
}

UINT CGPContextMenu::DeleteItem(UINT iItem)
{
	if (iItem<m_nArr)
	{
		PGPMENUINFO pgpiItem=&(m_pGPMenu->MENUINFOArray[m_ArrayIdMenuInfo[iItem]]);
		if (pgpiItem->hMenu)
		{

			int pos=FindPositionByData(pgpiItem->hMenu,m_ArrayIdMenuInfo[iItem]);
			if (pos>=0) ::DeleteMenu(pgpiItem->hMenu,pos,MF_BYPOSITION);
		}
		m_pGPMenu->UnRegisterMenuItem(m_ArrayIdMenuInfo[iItem]);
		m_nArr--;
		UINT i;
		for(i=iItem;i<m_nArr;i++)
			m_ArrayIdMenuInfo[i]=m_ArrayIdMenuInfo[i+1];

		m_ArrayIdMenuInfo[i]=-1;
	}
	return m_nArr;
}


DWORD CGPContextMenu::Load(const char *iName)
{
	if (m_Menu)
	{
		FILE *fl=fopen(iName==NULL || *iName==0?GPC.contmenuFileName:iName,"rt");
		if (fl)
		{
			DeleteAllItems();

			LoadMenu(fl,m_Menu);

			fclose(fl);
		}
	}
	return m_nArr;
}

BOOL CGPContextMenu::Save(const char *iName)
{
	BOOL ret=FALSE;
	FILE *fl=fopen(iName && *iName?iName:GPC.contmenuFileName,"wt");
	if (fl)
	{
		ret=TRUE;
		SaveMenu(fl,m_Menu,0);
		fclose(fl);
	}

	return ret;
}

UINT CGPContextMenu::SaveMenu(FILE *fl, HMENU mnu, int iLevel)
{
	UINT ret=0;
	if (fl && m_ArrayIdMenuInfo)
	{
		CString prefix="";
		int j=0;
		for(j=0;j<iLevel;j++)
			prefix+="    ";

		UINT i;
		PGPMENUINFO pgpiItem;

		for(i=0;i<m_nArr;i++)
			if (m_ArrayIdMenuInfo[i]!=-1 && (pgpiItem=&(m_pGPMenu->MENUINFOArray[m_ArrayIdMenuInfo[i]]))->hMenu==mnu)
			{
				ret++;
				fprintf(fl,"%s\t",(LPCSTR)prefix);
				if (pgpiItem->hSubMenu)
				{
					fprintf(fl,"SUBMENU\t%s\t%d\t%d\t%s\t%s\t%s\t%s\t%s\n",
						(LPCSTR)pgpiItem->csName,
						pgpiItem->dwCmd,
						pgpiItem->dwImage,
						(LPCSTR)pgpiItem->csImageList,
						(LPCSTR)pgpiItem->csText,
						(LPCSTR)pgpiItem->csDescription,
						(LPCSTR)pgpiItem->csOut,
						(LPCSTR)pgpiItem->csContext
						);
					SaveMenu(fl,pgpiItem->hSubMenu, iLevel+1);
				}
				else
				if (pgpiItem->dwCmd==0)
				{
					fprintf(fl,"SEPARATOR\n");
				}
				else
				{

					fprintf(fl,"MENUITEM\t%s\t%d\t%s\t%s\t%s\t%s\t%s\n",
						(LPCSTR)pgpiItem->csName,
						pgpiItem->dwImage,
						(LPCSTR)pgpiItem->csImageList,
						(LPCSTR)pgpiItem->csText,
						(LPCSTR)pgpiItem->csDescription,
						(LPCSTR)pgpiItem->csOut,
						(LPCSTR)pgpiItem->csContext
						);
				}
			}

		fprintf(fl,"%s\tEND\n",(LPCSTR)prefix);
	}

	return ret;
}

void CGPContextMenu::DeleteAllItems()
{
	while(m_nArr)
		if (m_ArrayIdMenuInfo)
			DeleteItem(&(m_pGPMenu->MENUINFOArray[m_ArrayIdMenuInfo[0]]));
		else
			DeleteItem((UINT)0);

	if (m_Menu)
	{
		int nItems=::GetMenuItemCount(m_Menu);
		while(nItems-->0)
			::DeleteMenu(m_Menu,0,MF_BYPOSITION);
	}
}

UINT CGPContextMenu::LoadMenu(FILE *iFile, HMENU mnu)
{
	if (mnu && iFile)
	{
		char *buff=new char [1024];
		CString tmps;
		int curMenuPos=0;
		while(tmps!="END" && fgets(buff,1000,iFile))
		{
			char *pos1=buff;
			while(*pos1 && *pos1!='\n' && *pos1!='\r') pos1++;
			*pos1=0;

			tmps=ExtractField(buff,2,"\t");
			tmps.MakeUpper();
			tmps.Replace(" ","");
			BOOL bDoODC=FALSE;
			if (tmps=="SUBMENU")
			{
				GPMENUINFO MUDst;
				ClearItem(&MUDst);
				HMENU newMenu=::CreatePopupMenu();
				MUDst.hSubMenu=newMenu;
				MUDst.hMenu=mnu;
				MUDst.csName=ExtractField(buff,3,"\t");
				MUDst.dwCmd=atoi(ExtractField(buff,4,"\t"));
				MUDst.dwImage=atoi(ExtractField(buff,5,"\t"));
				MUDst.csImageList=ExtractField(buff,6,"\t");
				MUDst.csText=ExtractField(buff,7,"\t");
				MUDst.csDescription=ExtractField(buff,8,"\t");
				MUDst.csOut=ExtractField(buff,9,"\t");
				MUDst.csContext=ExtractField(buff,10,"\t");
				if (MUDst.csContext=="") MUDst.csContext="CustomMenu";

				MENUITEMINFO mi={0};
				mi.cbSize=sizeofMENUITEMINFO;
				#ifdef W_95
					mi.fMask=MIIM_SUBMENU|MIIM_TYPE|MIIM_DATA;
				#else
					#ifdef W_NT
						mi.fMask=MIIM_SUBMENU|MIIM_TYPE|MIIM_DATA;
					#else
						mi.fMask=MIIM_SUBMENU|MIIM_STRING|MIIM_DATA;
					#endif
				#endif

				mi.dwTypeData=(char *)(LPCSTR)MUDst.csText;
				mi.cch=MUDst.csText.GetLength();
				mi.hSubMenu=newMenu;

				DWORD item=AddItem();
				mi.dwItemData=m_ArrayIdMenuInfo[item]=m_pGPMenu->RegisterMenuItem(MUDst);

				bDoODC=::InsertMenuItem(mnu,-1,TRUE,&mi);
				LoadMenu(iFile,newMenu);
			}
			else
			if (tmps=="MENUITEM")
			{
				GPMENUINFO MUDst;
				ClearItem(&MUDst);
				MUDst.hMenu=mnu;
				MUDst.dwCmd=GetFreeCommand();
				MUDst.csName=ExtractField(buff,3,"\t");
				MUDst.dwImage=atoi(ExtractField(buff,4,"\t"));
				MUDst.csImageList=ExtractField(buff,5,"\t");
				MUDst.csText=ExtractField(buff,6,"\t");
				MUDst.csDescription=ExtractField(buff,7,"\t");
				MUDst.csOut=ExtractField(buff,8,"\t");
				MUDst.csContext=ExtractField(buff,9,"\t");
				if (MUDst.csContext=="") MUDst.csContext="CustomMenu";

				MENUITEMINFO mi={0};
				mi.cbSize=sizeofMENUITEMINFO;
				#ifdef W_95
					mi.fMask=MIIM_STRING|MIIM_TYPE|MIIM_ID|MIIM_DATA;
				#else
					#ifdef W_NT
						mi.fMask=MIIM_STRING|MIIM_TYPE|MIIM_ID|MIIM_DATA;
					#else
						mi.fMask=MIIM_STRING|MIIM_ID|MIIM_DATA;
					#endif
				#endif

				mi.dwTypeData=(char *)(LPCSTR)MUDst.csText;
				mi.cch=MUDst.csText.GetLength();
				mi.wID=MUDst.dwCmd;

				DWORD item=AddItem();
				mi.dwItemData=m_ArrayIdMenuInfo[item]=m_pGPMenu->RegisterMenuItem(MUDst);

				bDoODC=::InsertMenuItem(mnu,-1,TRUE,&mi);
			}
			else
			if (tmps=="SEPARATOR")
			{
				GPMENUINFO MUDst;
				ClearItem(&MUDst);
				MUDst.hMenu=mnu;
				MUDst.csText=tmps;
				MUDst.csDescription=tmps;
				MUDst.csName=tmps;
				MUDst.dwCmd=0;
				if (MUDst.csContext=="") MUDst.csContext="CustomMenu";

				MENUITEMINFO mi={0};
				mi.cbSize=sizeofMENUITEMINFO;
				#ifdef W_95
					mi.fMask=MIIM_TYPE|MIIM_DATA;
				#else
					#ifdef W_NT
						mi.fMask=MIIM_TYPE|MIIM_DATA;
					#else
						mi.fMask=MIIM_FTYPE|MIIM_DATA;
					#endif
				#endif

				mi.fType=MFT_SEPARATOR;
			//	mi.fType|=MFT_OWNERDRAW;
				mi.dwTypeData=(char *)(LPCSTR)MUDst.csText;
				mi.cch=MUDst.csText.GetLength();
				mi.wID=MUDst.dwCmd;

				DWORD item=AddItem();
				mi.dwItemData=m_ArrayIdMenuInfo[item]=m_pGPMenu->RegisterMenuItem(MUDst);
				bDoODC=::InsertMenuItem(mnu,-1,TRUE,&mi);
			}
			if (bDoODC)
			{
				MENUITEMINFO mii={0};
				mii.cbSize=sizeofMENUITEMINFO;
				mii.fMask=MIIM_FTYPE;
				::GetMenuItemInfo(mnu,curMenuPos,TRUE,&mii);
				mii.fType|=MFT_OWNERDRAW;
				::SetMenuItemInfo(mnu,curMenuPos,TRUE,&mii);
				curMenuPos++;
			}
		}
		delete[] buff;
	}

	return m_nArr;
}

DWORD CGPContextMenu::GetFreeCommand()
{
	DWORD ret=0;
	int *tmp=new int [m_nMaxArr+10];
	::ZeroMemory(tmp,m_nMaxArr*sizeof(int));

	if (m_pGPMenu->MENUINFOArray.SelectFirst()!=-1)
		do
		{
			DWORD dwCmd=m_pGPMenu->MENUINFOArray.GetSelected().dwCmd;
			if (dwCmd>=GPCM_ID_START && dwCmd<GPCM_ID_END+m_nMaxArr)
				tmp[dwCmd-GPCM_ID_START]=1;
		}while(m_pGPMenu->MENUINFOArray.SelectNext()!=-1);

	for(ret=0;ret<m_nArr && tmp[ret];ret++);

	delete[] tmp;

	return ret+GPCM_ID_START;
}

DWORD CGPContextMenu::GetFreeSubMenuId()
{
	DWORD ret=0;
	int *tmp=new int [m_nMaxArr+10];
	::ZeroMemory(tmp,m_nMaxArr*sizeof(int));

	if (m_pGPMenu->MENUINFOArray.SelectFirst()!=-1)
		do
		{
			PGPMENUINFO pGPM=&(m_pGPMenu->MENUINFOArray.GetSelected());
			if (pGPM->dwCmd>=m_nMaxArr+10 && pGPM->hSubMenu)
				tmp[pGPM->dwCmd]=1;
		}while(m_pGPMenu->MENUINFOArray.SelectNext()!=-1);

	for(ret=1;ret<m_nArr && tmp[ret];ret++);

	delete[] tmp;
	return ret;
}

BOOL CGPContextMenu::FillTree(HWND TreeHWND, BOOL bCopy)
{
	BOOL ret=FALSE;
	if (TreeHWND)
	{
		::SendMessage(TreeHWND,TVM_DELETEITEM,0,(LPARAM)TVI_ROOT);
		ret=FillTree(TreeHWND,TVI_ROOT,m_Menu,bCopy);
	}

	return ret;
}

UINT CGPContextMenu::FillTree(HWND TreeHWND, HTREEITEM iTreeItem, HMENU mnu, BOOL bCopy)
{
	UINT ret=0;
	if (TreeHWND && m_ArrayIdMenuInfo && iTreeItem)
	{
		TVINSERTSTRUCT tvis={0};
		tvis.hParent=iTreeItem;
		tvis.hInsertAfter=TVI_LAST;
		tvis.item.mask=TVIF_PARAM|TVIF_TEXT;
		PGPMENUINFO pGPMI;

		UINT i;
		for(i=0;i<m_nArr;i++)
			if ((pGPMI=&(m_pGPMenu->MENUINFOArray[m_ArrayIdMenuInfo[i]])) && pGPMI->hMenu==mnu)
			{
				if (pGPMI->csContext=="") pGPMI->csContext="CustomMenu";

				if (bCopy)
				{
					tvis.item.lParam=(DWORD)new GPMENUINFO;
					CGPContextMenu::ClearItem((PGPMENUINFO)tvis.item.lParam);
					*((PGPMENUINFO)tvis.item.lParam)=*pGPMI;

				}
				else tvis.item.lParam=(DWORD)pGPMI;

				tvis.item.pszText=(char *)((LPCSTR)(pGPMI->csText));
				tvis.item.cchTextMax=1000;

				if (pGPMI->dwCmd==0) tvis.item.pszText="-------SEPARATOR-------";

				if ((pGPMI->dwPtr=::SendMessage(TreeHWND,TVM_INSERTITEM,0,(LPARAM)(&tvis))))
				{
					ret++;
					if (pGPMI->hSubMenu) FillTree(TreeHWND,(HTREEITEM)pGPMI->dwPtr,pGPMI->hSubMenu,bCopy);
				}
			}
	}
	return ret;
}

PGPMENUINFO CGPContextMenu::FindItemByData(DWORD dwData)
{
	PGPMENUINFO ret=NULL;
	if (m_pGPMenu)
	{
		if (m_pGPMenu->MENUINFOArray.SelectFirst()!=-1)
			do
			{
				PGPMENUINFO pGPM=&(m_pGPMenu->MENUINFOArray.GetSelected());
				if (pGPM->dwData==dwData) ret=pGPM;
			}while(!ret && m_pGPMenu->MENUINFOArray.SelectNext()!=-1);
	}
	return ret;
}

PGPMENUINFO CGPContextMenu::FindItemByName(const char *iName)
{
	PGPMENUINFO ret=NULL;
	if (m_pGPMenu)
	{
		if (m_pGPMenu->MENUINFOArray.SelectFirst()!=-1)
			do
			{
				PGPMENUINFO pGPM=&(m_pGPMenu->MENUINFOArray.GetSelected());
				if (pGPM->csName==iName) ret=pGPM;
			}while(!ret && m_pGPMenu->MENUINFOArray.SelectNext()!=-1);
	}
	return ret;
}

PGPMENUINFO CGPContextMenu::FindItemByCommand(DWORD dwCommand)
{
	PGPMENUINFO ret=NULL;
	if (m_pGPMenu)
	{
		if (m_pGPMenu->MENUINFOArray.SelectFirst()!=-1)
			do
			{
				PGPMENUINFO pGPM=&(m_pGPMenu->MENUINFOArray.GetSelected());
				if (pGPM->dwCmd==dwCommand) ret=pGPM;
			}while(!ret && m_pGPMenu->MENUINFOArray.SelectNext()!=-1);
	}
	return ret;
}

PGPMENUINFO CGPContextMenu::FindItemBySubMenuId(DWORD dwSubMenuId)
{
	PGPMENUINFO ret=NULL;
	if (m_pGPMenu)
	{
		if (m_pGPMenu->MENUINFOArray.SelectFirst()!=-1)
			do
			{
				PGPMENUINFO pGPM=&(m_pGPMenu->MENUINFOArray.GetSelected());
				if (pGPM->dwCmd==dwSubMenuId) ret=pGPM;
			}while(!ret && m_pGPMenu->MENUINFOArray.SelectNext()!=-1);
	}
	return ret;
}

PGPMENUINFO CGPContextMenu::FindItemByData(HMENU ihPopupMenu, DWORD dwData)
{
	PGPMENUINFO ret=NULL;
	if (m_pGPMenu && ihPopupMenu && dwData)
	{
		int nItems=::GetMenuItemCount(ihPopupMenu);
		MENUITEMINFO mi={0};
		mi.cbSize=sizeofMENUITEMINFO;
		mi.fMask=MIIM_DATA;
		int i;
		for(i=0;i<nItems && !ret;i++)
		{
			::GetMenuItemInfo(ihPopupMenu,i,TRUE,&mi);
			if (mi.dwItemData==dwData) ret=&(m_pGPMenu->MENUINFOArray[mi.dwItemData]);
		}
	}
	return ret;
}

int CGPContextMenu::FindPositionByData(HMENU ihPopupMenu, DWORD dwData)
{
	int ret=-1;
	if (m_pGPMenu && ihPopupMenu && dwData)
	{
		int nItems=::GetMenuItemCount(ihPopupMenu);
		MENUITEMINFO mi={0};
		mi.cbSize=sizeofMENUITEMINFO;
		mi.fMask=MIIM_DATA;
		int i;
		for(i=0;i<nItems && ret<0;i++)
		{
			::GetMenuItemInfo(ihPopupMenu,i,TRUE,&mi);
			if (mi.dwItemData==dwData) ret=i;
		}
	}
	return ret;
}

DWORD CGPContextMenu::GetMenuItemData(HMENU ihPopupMenu, int position)
{
	DWORD ret=0;

	if (ihPopupMenu)
	{
		MENUITEMINFO mi={0};
		mi.cbSize=sizeofMENUITEMINFO;
		mi.fMask=MIIM_DATA;
		if (::GetMenuItemInfo(ihPopupMenu,position,TRUE,&mi)) ret=mi.dwItemData;
	}
	return ret;
}


CString CGPContextMenu::ConvertToOutput(const char *iStr, const char *iClip)
{
	CString ret;
	if (iStr)
	{
		CString clip;
		if (iClip) clip=iClip;
		else
		{
			HANDLE hClipData;
			LPSTR  lpClipData;

			if (AfxGetMainWnd()->OpenClipboard())
			{
				if ((hClipData = GetClipboardData(CF_TEXT)) && (lpClipData = (char *)GlobalLock(hClipData)))
				{
					clip=lpClipData;
					GlobalUnlock(hClipData);
				}
				CloseClipboard();
			}
		}

		const char *pos=iStr;
		int maxlen=(int)strlen(iStr)*2+500;
		char *tmpstring=new char [maxlen];
		char *tmps=tmpstring;
		int CurFld=1;
		int CurStr=1;
		char Delimiter[5]={32,0,};
		DWORD flag=0x0001;
		*tmps=0;

		clip.Replace("\r\n","\n");
		clip.Replace("\n\r","\n");
		clip.Replace("\r","\n");

		while(*pos)
		{
			switch(*pos)
			{
			case '\\':
				switch(*(++pos))
				{
				case 'q':
					//query
				case 'w':
					//wait
				case 's':
					//synchro
					*(tmps++)='\\';*(tmps++)=*(pos++);	break;
				case 'a':	*(tmps++)='\a'; pos++;	break;
				case 'b':	*(tmps++)='\b'; pos++;	break;
				case 'f':	*(tmps++)='\f'; pos++;	break;
				case 'n':	*(tmps++)='\n'; pos++;	break;
				case 'r':	*(tmps++)='\r'; pos++;	break;
				case 't':	*(tmps++)='\t'; pos++;	break;
				case 'v':	*(tmps++)='\v'; pos++;	break;
				case 'x': case 'X':
					{
						int c=0,fl=0;
						int i;
						for(i=0;i<2 && fl>=0;i++)
						{
							c*=16;
							if (*(++pos)>='0' && *pos<='9') c+=*pos-'0';
							else
							if (*pos>='A' && *pos<='F') c+=*pos-'A'+10;
							else
							if (*pos>='a' && *pos<='f') c+=*pos-'a'+10;
							else {fl=-1;break;}
							*tmps=c;
						}

						if (fl>=0) pos++;
						if (i>0)
						{
							if (c==0)
							{
								ret+=tmpstring;
								*tmpstring=0;
								tmps=tmpstring;
								ret+=" ";
								ret.SetAt(ret.GetLength()-1,0);
							}
							else tmps++;
						}
					}
					break;
				case 'd': case 'D':
					{
						int c=0,fl=0;
						int i;
						for(i=0;i<3 && fl>=0;i++)
						{
							c*=10;
							if (*(++pos)>='0' && *pos<='9' && c+*pos-'0'<256) c+=*pos-'0';
							else {fl=-1;break;}
							*tmps=c;
						}

						if (fl>=0) pos++;
						if (i>0)
						{
							if (c==0)
							{
								ret+=tmpstring;
								*tmpstring=0;
								tmps=tmpstring;
								ret+=" ";
								ret.SetAt(ret.GetLength()-1,0);
							}
							else tmps++;
						}
					}
					break;
				case 'B':
					{
						int c=0,fl=0;
						int i;
						for(i=0;i<10 && fl>=0;i++)
						{
							c*=2;
							if (*(++pos)>='0' && *pos<='1' && c+*pos-'0'<256) c+=*pos-'0';
							else {fl=-1;break;}
							*tmps=c;
						}

						if (fl>=0) pos++;
						if (i>0)
						{
							if (c==0)
							{
								ret+=tmpstring;
								*tmpstring=0;
								tmps=tmpstring;
								ret+=" ";
								ret.SetAt(ret.GetLength()-1,0);
							}
							else tmps++;
						}
					}
					break;
				case '0': case '1':	case '2': case '3':	case '4':
				case '5': case '6':	case '7': case '8':	case '9':
					{
						int c=0,fl=0;
						int i;
						for(i=0;i<3 && fl>=0;i++)
						{
							c*=8;
							if (*(++pos)>='0' && *pos<='7' && c+*pos-'0'<256) c+=*pos-'0';
							else {fl=-1;break;}
							*tmps=c;
						}

						if (fl>=0) pos++;
						if (i>0)
						{
							if (c==0)
							{
								ret+=tmpstring;
								*tmpstring=0;
								tmps=tmpstring;
								ret+=" ";
								ret.SetAt(ret.GetLength()-1,0);
							}
							else tmps++;
						}
					}
					break;
				case 'e': case 'E':
					*(tmps++)='\33'; pos++;	break;

				case '?': case '"': case '\'': case '\\': case '%':
				default:
					*(tmps++)=*(pos++);break;
				}
				break;

			case '%':
				{
					int tmpInt=0;
					switch(*(++pos))
					{
					case '%':
						*(tmps++)=*(pos++);
						tmpInt=-1;
						break;
					case '0': case '1':	case '2': case '3':	case '4':
					case '5': case '6':	case '7': case '8':	case '9':
						tmpInt=atoi(pos);
						while(*pos && *pos>='0' && *pos<='9') pos++;
						break;
					default:
						break;
					}
					if (tmpInt>=0)
					{
						*tmps=0;
						ret+=tmpstring;
						*tmpstring=0;
						tmps=tmpstring;

						switch(*(pos++))
						{
						case 'c': case 'C': //clipboard text
							ret+=clip;
							break;
						case 'g': case 'G': //clipboard text Line No
							CurStr=tmpInt?tmpInt:1;
							ret+=ExtractField(clip,CurStr,"\n");
							break;
						case 'w': case 'W': //clipboard Word No from cur Line
							CurFld=tmpInt?tmpInt:1;
							ret+=ExtractWord(clip,CurStr,CurFld,Delimiter,flag);
							break;
						case 's': case 'S': //clipboard set Line No
							CurStr=tmpInt?tmpInt:1;
							break;
						case 'a': case 'A': //clipboard set Word No
							CurFld=tmpInt?tmpInt:1;
							break;
						case 'f': case 'F': //set Flag
							flag=tmpInt;
							break;
						case 'n': case 'N': //clipboard text next Line
							ret+=ExtractField(clip,++CurStr,"\n");
							break;
						case 'r': case 'R': //clipboard next Word from cur Line
							ret+=ExtractWord(clip,CurStr,++CurFld,Delimiter,flag);
							break;
						case 'l': case 'L': //clipboard prev Word from cur Line
							if (CurFld>1) CurFld--;
							else CurFld=1;
							ret+=ExtractWord(clip,CurStr,CurFld,Delimiter,flag);
							break;
						case 'p': case 'P': //clipboard text prev Line
							if (CurStr>1) CurStr--;
							else CurStr=1;
							ret+=ExtractField(clip,CurStr,"\n");
							break;
						case 'D': case 'd': //Delimiter for word
							if (*pos) *Delimiter=*(pos++);
							break;
						}
					}
				}
				break;
			default: *(tmps++)=*(pos++); break;
			}
		}
		*tmps=0;
		ret+=tmpstring;
		delete[] tmpstring;
	}

	return ret;
}


CString CGPContextMenu::ExtractWord(const char *iStr, int nLine, int nWord, const char *Delimiter, DWORD flag)
{
	CString ret;
	if (iStr && *iStr && nLine>0 && nWord>0 && Delimiter && *Delimiter)
	{
		CString line=ExtractField(iStr,nLine,"\n");
		if ((flag&0x0001))
		{
			CString tmp=Delimiter;
			tmp+=Delimiter;
			int lastlen=0;
			int curlen=-1;
			do
			{
				lastlen=curlen;
				line.Replace(tmp,Delimiter);
				curlen=line.GetLength();
			}while(lastlen!=curlen);
		}
		ret=ExtractField(line,nWord,Delimiter);
	}
	return ret;
}

UINT CGPContextMenu::GetCount()
{
	return m_nArr;
}

int CGPContextMenu::DoMethod(const char *iStr, char *oStr)
{
	char met[150];
	strncpy(met,iStr,145);
	met[145]=0;
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	UINT nfunc=0;

	int retint=-123456;
	int atoipos=atoi(pos);

	if (*met>='0' && *met<='9') nfunc=atoi(met);
	else	for(nfunc=0;nfunc<uNMethods && _stricmp(met,cArrMethods[nfunc])!=0;nfunc++);
	try
	{
		switch(nfunc)
		{
		case 0: // DeleteMenu
			{
				PGPMENUINFO it=FindItemByName(ExtractField(pos,1,","));
				if (it)
				{
					CString fld2=ExtractField(pos,2,",");
					if (fld2=="") DeleteItem(it);
					else
						if (it->hSubMenu)
						{
							MENUITEMINFO mi={0};
							mi.cbSize=sizeofMENUITEMINFO;
							mi.fMask=MIIM_DATA;
							if (::GetMenuItemInfo(it->hSubMenu,atoi(fld2),TRUE,&mi))
								DeleteItem(&(m_pGPMenu->MENUINFOArray[mi.dwItemData]));
						}
				}
				retint=m_nArr;
			}
			break;
		case 1: // RenameMenu
			{
				PGPMENUINFO it=FindItemByName(ExtractField(pos,1,","));
				retint=1;
				if (it && FindItemByName(ExtractField(pos,1,",")))
					it->csName=ExtractField(pos,2,",");
				else retint=-1;
			}
			break;
		case 2: // TrackMenu PopupMenuName,x,y,flags
			{
				PGPMENUINFO it=FindItemByName(ExtractField(pos,1,","));
				retint=-1;
				if (it && it->hSubMenu)
				{
					POINT po={0};
					po.x=atoi(ExtractField(pos,2,","));
					po.y=atoi(ExtractField(pos,3,","));
					if (po.x==0 && po.y==0)
						::GetCursorPos(&po);
					DWORD flags=0;
					CGPContextMenu::StringFromToTPMFlags(ExtractField(pos,4,","),flags);
					retint=::TrackPopupMenu(it->hSubMenu,flags,po.x,po.y,0,GPC.m_hViewWnd,NULL);
				}
			}
			break;
		case 3: // CreatePopupMenu ParentName,[InsertBefore],PopupMenuName,PopupMenuText
			{
				PGPMENUINFO it=NULL;
				HMENU hInto=NULL;
				CString menuName=ExtractField(pos,3,",");
				if (menuName!="")
				{
					it=FindItemByName(menuName);
					if (it) DeleteItem(it);
				}
				it=NULL;
				if (*pos && *pos!=',') it=FindItemByName(ExtractField(pos,1,","));
				if (it) hInto=it->hSubMenu;
				if (hInto==NULL) hInto=m_Menu;
				if (hInto)
				{
					GPMENUINFO MUDst;
					ClearItem(&MUDst);
					MENUITEMINFO mi={0};
					mi.cbSize=sizeofMENUITEMINFO;

					CString insBefore=ExtractField(pos,2,",");
					UINT uinsBefore=atoi(insBefore);
					if (insBefore=="") uinsBefore=-1;
					else
					if (insBefore!="0" && uinsBefore==0)
						uinsBefore=GetMenuPosition(insBefore);

					MUDst.csName=menuName;
					MUDst.hMenu=hInto;

					switch(nfunc)
					{
					case 3: // CreatePopupMenu
						MUDst.hSubMenu=CreatePopupMenu();
						MUDst.csText=ExtractField(pos,4,",");
						#ifdef W_95
							mi.fMask=MIIM_SUBMENU|MIIM_TYPE|MIIM_DATA;
							mi.fType=MFT_STRING;
						#else
							#ifdef W_NT
								mi.fMask=MIIM_SUBMENU|MIIM_TYPE|MIIM_DATA;
								mi.fType=MFT_STRING;
							#else
								mi.fMask=MIIM_SUBMENU|MIIM_STRING|MIIM_DATA;
							#endif
						#endif
						mi.hSubMenu=MUDst.hSubMenu;
						break;
					case 4: // InsertMenuItem
						MUDst.dwCmd=GetFreeCommand();
						MUDst.csText=ExtractField(ExtractField(pos,1,";"),4,",");
						MUDst.csOut=ExtractField(pos,2,";");
						#ifdef W_95
							mi.fMask=MIIM_TYPE|MIIM_ID|MIIM_DATA;
							mi.fType=MFT_STRING;
						#else
							#ifdef W_NT
								mi.fMask=MIIM_TYPE|MIIM_ID|MIIM_DATA;
								mi.fType=MFT_STRING;
							#else
								mi.fMask=MIIM_STRING|MIIM_ID|MIIM_DATA;
							#endif
						#endif
						mi.wID=MUDst.dwCmd;
						break;
					case 5: // InsertSeparator
						#ifdef W_95
							mi.fMask=MIIM_TYPE|MIIM_DATA;
						#else
							#ifdef W_NT
								mi.fMask=MIIM_TYPE|MIIM_DATA;
							#else
								mi.fMask=MIIM_FTYPE|MIIM_DATA;
							#endif
						#endif
						MUDst.csText=menuName;
						MUDst.csDescription=menuName;
						mi.fType=MFT_SEPARATOR;
						mi.wID=GetFreeCommand();
						break;
					}
					mi.dwTypeData=(char *)(LPCSTR)MUDst.csText;
					mi.cch=MUDst.csText.GetLength();

					DWORD item=AddItem();
					if (MUDst.csContext=="") MUDst.csContext="CustomMenu";
					mi.dwItemData=m_ArrayIdMenuInfo[item]=m_pGPMenu->RegisterMenuItem(MUDst);
					::InsertMenuItem(MUDst.hMenu,uinsBefore,TRUE,&mi);
				}
			}
			break;
		case 6: //SetOutputString MenuName,[position],OutputString
		case 7: //SetDescription MenuName,[position],OutputString
			{
				CString menuName=ExtractField(pos,1,",");
				CString menuPos=ExtractField(pos,2,",");
				PGPMENUINFO it=NULL;
				it=FindItemByName(menuName);
				if (it)
				{
					if (it->hSubMenu)
					{
						if (menuPos=="") it=NULL;
						else
							it=&(m_pGPMenu->MENUINFOArray[GetMenuItemData(it->hSubMenu,atoi(menuPos))]);
					}
					else if (menuPos!="") it=NULL;

					if (it)
						if (nfunc==6)
							it->csOut=ExtractField(pos,3,",");
						else
							it->csDescription=ExtractField(pos,3,",");
				}
			}
			break;
		case 8: //Load FileName[,InitDir]
		case 11: //Save FileName[,InitDir]
			{
				DeleteAllItems();
				const char *pos2=strchr(pos,',');
				CString FileName=ExtractField(pos,1,",");
				CString InitDir=ExtractField(pos,2,",");
				if (pos2 && GetFileName(InitDir,FileName,nfunc==8)==FALSE) FileName="";

				if (FileName!="")
					retint=(nfunc==8)?Load(FileName):Save(FileName);
			}
			break;
		case 9: //LoadMenu MenuName,FileName[,InitDir]
		case 10: //AppendFromFile MenuName,FileName[,InitDir]
		case 12: //SaveMenu MenuName,FileName[,InitDir]
			{
				CString MenuName=ExtractField(pos,1,",");
				CString FileName=ExtractField(pos,2,",");
				CString InitDir=ExtractField(pos,3,",");
				PGPMENUINFO it=FindItemByName(MenuName);
				HMENU mnu=m_Menu;
				if (it) mnu=it->hSubMenu?it->hSubMenu:it->hMenu;

				if (InitDir!="" && GetFileName(InitDir,FileName,nfunc!=12)==FALSE) FileName="";
				FILE *fl=NULL;
				if (FileName!="" && (fl=fopen(FileName,nfunc!=12?"rt":"wt")))
				{
					switch(nfunc)
					{
					case 9: //LoadMenu
						{
							int nItems=::GetMenuItemCount(mnu);
							int j;
							for(j=0;j<nItems;j++)
							{
								PGPMENUINFO tmp=&(m_pGPMenu->MENUINFOArray[GetMenuItemData(mnu,0)]);
								if (tmp) DeleteItem(tmp);
							}
						}
					case 10: //AppendFromFile
						LoadMenu(fl,mnu);
						break;
					case 12: //SaveMenu MenuName,FileName[,InitDir]
						SaveMenu(fl,mnu,1);
						break;
					}
					fclose(fl);
				}
			}
			break;
		case 13: //Execute
			{
				PGPMENUINFO it=FindItemByName(pos);
				if (it)	retint=::SendMessage(GPC.m_hViewWnd,WM_COMMAND,it->dwCmd,NULL);
			}
			break;

		default:
			GPC.m_ErrReport.GPWriteWarnLog2("CGPContextMenu", "Unknown Method",iStr);
			if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;
			break;
		}
	}catch(...)
	{
		char *str=new char [200+(int)strlen(pos)];
		#ifdef RUS
			sprintf(str,"Ошибка выполнения метода %s %s",met,pos);
			AfxGetMainWnd()->MessageBox(str,"Ошибка метода");
		#else
			sprintf(str,"Error execution of method %s %s",met,pos);
			AfxGetMainWnd()->MessageBox(str,"Error execution");
		#endif
		if (oStr!=NULL) strcpy(oStr,str);
		nfunc=0xFFFFFFFFL;
	GPC.m_ErrReport.GPWriteErrorLog("CGPContextMenu", "DoMethod",iStr);
		delete[] str;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);
	return nfunc;
}


DWORD CGPContextMenu::StringFromToTPMFlags(const char *iTPMFlags, DWORD & convTPMFlags)
{
	UINT nOptions=14;
	const char *OptionName[]={
	"TPM_RECURSE","TPM_RIGHTBUTTON","TPM_CENTERALIGN","TPM_RIGHTALIGN","TPM_VCENTERALIGN",
	"TPM_BOTTOMALIGN","TPM_VERTICAL","TPM_RESERV","TPM_HORPOSANIMATION","TPM_HORNEGANIMATION",
	"TPM_VERPOSANIMATION","TPM_VERNEGANIMATION","TPM_NOANIMATION","TPM_LAYOUTRTL",
	};
	const UINT  uOptionList[]={
	TPM_RECURSE,TPM_RIGHTBUTTON,TPM_CENTERALIGN,TPM_RIGHTALIGN,TPM_VCENTERALIGN,
	TPM_BOTTOMALIGN,TPM_VERTICAL,0x0200L,TPM_HORPOSANIMATION,TPM_HORNEGANIMATION,
	TPM_VERPOSANIMATION,TPM_VERNEGANIMATION,TPM_NOANIMATION,TPM_LAYOUTRTL,
	};

	if (iTPMFlags)
	{
		if (*iTPMFlags)
		{
			char *tmps=new char [(int)strlen(iTPMFlags)+100];
			strcpy(tmps,iTPMFlags);
			_strupr(tmps);
			convTPMFlags=atoi(tmps);
			UINT i;
			for(i=0;i<nOptions;i++)
				if (strstr(tmps,OptionName[i]))
					convTPMFlags|=uOptionList[i];
			delete[] tmps;
		}
		else
		{
			UINT convSD=convTPMFlags;
			UINT i;
			for(i=0;i<nOptions;i++)
				if ((convSD&uOptionList[i])==uOptionList[i])
				{
					if (*iTPMFlags) strcat((char *)iTPMFlags,"|");
					strcat((char *)iTPMFlags,OptionName[i]);
					convSD^=uOptionList[i];
				}
				if (convSD) sprintf((char *)iTPMFlags+(int)strlen(iTPMFlags),"%s%d",*iTPMFlags?"|":"",convSD);
		}
	}
	return convTPMFlags;
}

UINT CGPContextMenu::GetMenuPosition(const char *iName)
{
	int ret=-1;
	PGPMENUINFO it=FindItemByName(iName);
	if (it && it->hMenu)
	{
		int nItems=::GetMenuItemCount(it->hMenu);
		int i;
		for(i=0;i<nItems && ret<0;i++)
			if (::GetMenuItemID(it->hMenu,i)==it->dwCmd) ret=i;
	}

	return (UINT)ret;
}

BOOL CGPContextMenu::GetFileName(CString &iInitDir, CString &iFileName, DWORD iFlags)
{
	BOOL ret=FALSE;
	OPENFILENAME opf={0};
	#ifdef W_95
		opf.lStructSize=OPENFILENAME_SIZE_VERSION_400;
	#else
		#ifdef W_NT
			opf.lStructSize=OPENFILENAME_SIZE_VERSION_400;
		#else
			opf.lStructSize=sizeof(OPENFILENAME);
		#endif
	#endif
	opf.hwndOwner=GPC.m_hViewWnd;
	opf.lpstrFile = new char [500];
	strcpy(opf.lpstrFile,iFileName);
	opf.nMaxFile =490;

	opf.Flags =OFN_DONTADDTORECENT|OFN_CREATEPROMPT|OFN_ENABLESIZING|OFN_EXPLORER|OFN_NOCHANGEDIR|OFN_SHOWHELP|OFN_LONGNAMES|OFN_PATHMUSTEXIST;
	#ifdef RUS
		opf.lpstrFilter="Текстовые файлы (*.txt)\x0*.txt\x0Все файлы\x0*.*\x0";
		opf.lpstrTitle="Выбор файла описания контекстных меню";
	#else
		opf.lpstrFilter="Text Files (*.txt)\x0*.txt\x0 All Files\x0*.*\x0";
		opf.lpstrTitle="Select User Menu File";
	#endif
	opf.lpstrDefExt="TXT";

	if (iInitDir!="")
		opf.lpstrInitialDir=(LPCSTR)iInitDir;


	switch((iFlags&0x0001))
	{
	case 0:
		if ((ret=GetOpenFileName(&opf)))
			iFileName=opf.lpstrFile;
		break;
	case 1:
		if ((ret=GetSaveFileName(&opf)))
			iFileName=opf.lpstrFile;
		break;
	}
	delete[] opf.lpstrFile;
	return ret;
}
