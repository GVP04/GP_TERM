// GPMenu.cpp: implementation of the GPMenu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPMenu.h"
#include "GPImageList.h"
#include "GPContextMenu.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

DWORD GPMenu::m_dwODCMENUID;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPMenu::GPMenu(HWND mowner,UINT iType)
{
	UINT i;
	GPTypeMenu=iType;
	MenuOwner=mowner;
	m_ArrMenuState=new UINT [MENU_ID_COUNT];
	for(i=0;i<MENU_ID_COUNT;i++) 
		m_ArrMenuState[i]=MF_ENABLED;

	for(i=0;i<MENU_POPUP_COUNT;i++)
		m_ArrPopupMenu[i]=NULL;

	InitTermMenuList();
}

GPMenu::~GPMenu()
{
	if (m_ArrMenuState!=NULL) delete[] m_ArrMenuState;
	int ii;
	for(ii=MENU_POPUP_START;ii<MENU_POPUP_COUNT;ii++) 	
	{
		if (m_ArrPopupMenu[ii])
		{
			if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwDeletePopupMenu++;
			delete m_ArrPopupMenu[ii];
		}
		m_ArrPopupMenu[ii]=NULL;
	}

	if (GPTypeMenu==0)
	{
		UINT ui;
		for(ui=0;ui<MENU_POPUP_COUNT;ui++)
			if (m_ArrPopupMenu[ui]) 
			{
				delete m_ArrPopupMenu[ui];
				m_ArrPopupMenu[ui]=NULL;
			}
	}

	if (m_ArrPopupMenu[0]) delete m_ArrPopupMenu[0];
	m_ArrPopupMenu[0]=NULL;
}

UINT GPMenu::GPSetMenuFlags(UINT iId, char *iFlags)
{
	UINT ret=0;
	if (iId>=MENU_ID_START && iId<=MENU_ID_END) 
	{
		m_ArrMenuState[iId-MENU_ID_START]=0;
		GPEditMenuFlags(iId,iFlags);
		ret=m_ArrMenuState[iId-MENU_ID_START];
	}

	return ret;
}

UINT GPMenu::GPEditMenuFlags(UINT iId, char *iFlags)
{
	UINT ret=0;
	if (iId>=MENU_ID_START && iId<=MENU_ID_END)
		ret=m_ArrMenuState[iId-MENU_ID_START]=GPMenu::TranslateMenuFlags(m_ArrMenuState[iId-MENU_ID_START],iFlags);

	return ret;
}

DWORD GPMenu::TranslateMenuFlags(DWORD dwCurFlag, const char *ccFlags)
{
	UINT ret=dwCurFlag;
	char *str;
	if (ccFlags!=NULL)
	{
		str=new char [(int)strlen(ccFlags)+10];
		strcpy(str,ccFlags);
	}
	else
	{
		str=new char [100];
		*str=0;
	}

	char *tmppos=strchr(str+1,';');
	if (tmppos!=NULL) *tmppos=0;

	ret|=atoi(str);
	if (strchr(str,'B')!=NULL) {	ret|=MFT_MENUBARBREAK;	ret&=(0xFFFFFFFF^(MFT_MENUBREAK));		}
	if (strchr(str,'M')!=NULL) {	ret|=MFT_MENUBREAK;	ret&=(0xFFFFFFFF^(MFT_MENUBARBREAK));		}	
	if (strchr(str,'E')!=NULL) {	ret|=MF_ENABLED;	ret&=(0xFFFFFFFF^(MFS_GRAYED));				}
	if (strchr(str,'D')!=NULL) {	ret|=MF_DISABLED;	ret&=(0xFFFFFFFF^(MF_ENABLED));				}
	if (strchr(str,'G')!=NULL) {	ret|=MFS_GRAYED;	ret&=(0xFFFFFFFF^(MF_ENABLED));				}
	if (strchr(str,'R')!=NULL) {	ret|=MFT_RADIOCHECK;	ret&=(0xFFFFFFFF^(MFS_CHECKED));		}
	if (strchr(str,'C')!=NULL) {	ret|=MFS_CHECKED;	ret&=(0xFFFFFFFF^(MFT_RADIOCHECK));			}
	if (strchr(str,'U')!=NULL) {	ret&=(0xFFFFFFFF^(MFS_CHECKED|MFT_RADIOCHECK));					}
	if (strchr(str,'O')!=NULL) {	ret|=MFT_OWNERDRAW;	ret&=(0xFFFFFFFF^(MF_BITMAP|MFT_STRING));	}
	if (strchr(str,'T')!=NULL) {	ret|=MFT_STRING;	ret&=(0xFFFFFFFF^(MF_BITMAP|MFT_OWNERDRAW));	}
	if (strchr(str,'P')!=NULL) {	ret|=MFT_BITMAP;	ret&=(0xFFFFFFFF^(MFT_STRING|MFT_OWNERDRAW));	}
	if (strchr(str,'d')!=NULL) {	ret|=MFS_DEFAULT;}
	if (strchr(str,'o')!=NULL) {	ret&=(0xFFFFFFFF^(MFS_DEFAULT));	}
	if (strchr(str,'S')!=NULL) {	ret|=MFT_SEPARATOR;	}
	if (strchr(str,'s')!=NULL) {	ret&=(0xFFFFFFFF^(MFT_SEPARATOR));	}
	if (strchr(str,'H')!=NULL) {	ret|=MFS_HILITE;	}
	if (strchr(str,'h')!=NULL) {	ret&=(0xFFFFFFFF^(MFS_HILITE));	}
	if (strchr(str,'Q')!=NULL) {	ret|=MF_HELP;	}
	if (strchr(str,'q')!=NULL) {	ret&=(0xFFFFFFFF^(MF_HELP));	}
	if (strchr(str,'X')!=NULL) {	ret|=MFT_RIGHTORDER;	}
	if (strchr(str,'x')!=NULL) {	ret&=(0xFFFFFFFF^(MFT_RIGHTORDER));	}
	if (strchr(str,'Y')!=NULL) {	ret|=MFT_RIGHTJUSTIFY;	}
	if (strchr(str,'y')!=NULL) {	ret&=(0xFFFFFFFF^(MFT_RIGHTJUSTIFY));	}
	if (strchr(str,'Z')!=NULL) {	ret|=MF_SYSMENU;	}
	if (strchr(str,'z')!=NULL) {	ret&=(0xFFFFFFFF^(MF_SYSMENU));	}
	if (!(ret&(MF_BITMAP|MFT_STRING|MFT_OWNERDRAW))) ret|=MFT_STRING;

	delete[] str;
	return ret;
}


UINT GPMenu::GPTranslateMenuInfo(char *iFlags, MENUINFO *mi)
{
	char *posEx=NULL;
	if (iFlags!=NULL) posEx=strchr(iFlags,';');

	if (posEx!=NULL) posEx++;
	else posEx="";
	UINT ret=0;
	mi->cbSize=sizeof(*mi);
	mi->fMask=MIM_MENUDATA;
	mi->dwMenuData=(DWORD)this;
	if (*posEx!=0) 
	{
		int i;
		char *pos;
		char *type[5]={"HELP=","SIZE=","BRUSH=","STYLE=","SUBMENU=",};
		for(i=0;i<5;i++)
			if ((pos=strstr(posEx,type[i])))
			{
				pos=strchr(pos,'=');
				pos++;
				switch(i)
				{
				case 0: 
					mi->dwContextHelpID=atol(pos);
					mi->fMask|=MIM_HELPID;
					ret++;
					break;
				case 1:
					mi->cyMax=atoi(pos);
					mi->fMask|=MIM_MAXHEIGHT;
					ret++;
					break;
				case 2: 
					{
						LOGBRUSH lb={0};
						GPSetBrushProperty(&lb,pos);
						if (mi->hbrBack!=NULL) DeleteObject(mi->hbrBack);

						if ((lb.lbColor&0xFF000000)==0xFF000000)
						{
							GPImageList *SMainIl;
							int ImgLId=lb.lbColor&0xFF;
							int nImg=(lb.lbColor&0xFF0000)/0x10000;
							if ((SMainIl=&(GPC.a_GPImageList[ImgLId]))!=NULL)
							{
								HICON tmpico;
								tmpico=SMainIl->m_IL.ExtractIcon(nImg);
								Bitmap m_bitmap(tmpico);
								HBITMAP hbm;
								m_bitmap.GetHBITMAP(GetSysColor(COLOR_MENU),&hbm);
								mi->hbrBack=CreatePatternBrush(hbm);
								if (hbm) DeleteObject(hbm);
								DestroyIcon(tmpico);
							}
						}
						else	mi->hbrBack=CreateBrushIndirect( &lb );

						mi->fMask|=MIM_BACKGROUND;
						ret++;
					}
					break;
				case 3: 
					{
						mi->dwStyle=0;
						mi->fMask|=MIM_STYLE;
						char *cstl[6]={"AUTODISMISS","CHECKORBMP","DRAGDROP","MODELESS","NOCHECK","NOTIFYBYPOS",};
						UINT  ustl[6]={MNS_AUTODISMISS,MNS_CHECKORBMP,MNS_DRAGDROP,MNS_MODELESS,MNS_NOCHECK,MNS_NOTIFYBYPOS,};
						int j;
						for(j=0;j<6;j++)
							if (strstr(pos,cstl[j])!=NULL) mi->dwStyle|=ustl[j];
						ret++;
					}
					break;
				case 4:
					if (atoi(pos)>0) mi->fMask|=MIM_APPLYTOSUBMENUS;
					ret++;
					break;
				}
			}
	}

	return ret;
}

UINT GPMenu::GPTranslateMenuItemInfo(char *iFlags, MENUITEMINFO *mi)
{

	char *posEx=NULL;
	if (iFlags!=NULL) posEx=strchr(iFlags,';');

	if (posEx!=NULL) posEx++;
	else posEx="";
	UINT ret=0;
	mi->cbSize=sizeofMENUITEMINFO;
	if (*posEx!=0) 
	{
		int i;
		char *pos;
		char *type[]={"BMPCH=","BMPUCH=","BMPMENU=","BMPSTR=","",};
		for(i=0;*type[i];i++)
			if ((pos=strstr(posEx,type[i])))
			{
				pos=strchr(pos,'=');
				pos++;
				HBITMAP hbm=NULL;
				char *str=new char[(int)strlen(pos)+16];
				strcpy(str,"MISCS");
				int nImage=0;
				m_LastScanf=sscanf(pos,"%d,%s",&nImage,str);
				char *tmp=strchr(str,';');
				if (tmp!=NULL) *tmp=0;

				GPImageList *SMainI;
				int ImgLId=0;
				if ((ImgLId=GPC.GetImageListId(str))>=0 && (SMainI=&(GPC.a_GPImageList[ImgLId])) && SMainI->m_IL.m_hImageList)
				{
					hbm=SMainI->CreateBitmap(nImage,::GetSysColor(COLOR_MENU));
					switch(i)
					{
					case 0: //BMPCH
						mi->fMask|=MIIM_CHECKMARKS;
						mi->hbmpChecked=hbm;
						ret++;
						break;
					case 1://BMPUCH
						mi->fMask|=MIIM_CHECKMARKS;
						mi->hbmpUnchecked=hbm;
						ret++;
						break;
					case 2: //BMPMENU
						{
							#ifdef W_95
								mi->fMask|=MIIM_TYPE;
							//	mi->fType|=MFT_STRING;
								mi->fType|=MFT_BITMAP;
								mi->fType&=(0xFFFFFFFF^MFT_STRING);
							#else
								#ifdef W_NT
									mi->fMask|=MIIM_TYPE;
								//	mi->fType|=MFT_STRING;
									mi->fType|=MFT_BITMAP;
									mi->fType&=(0xFFFFFFFF^MFT_STRING);
								#else
									mi->fMask|=MIIM_BITMAP;
								//	mi->fType|=MIIM_BITMAP/*|MIIM_STRING*/;
								#endif
							#endif
							char *bmpn[10]={"_MBAR_CLOSE","_MBAR_CLOSE_D","_MBAR_MINIMIZE","_MBAR_MINIMIZE_D","_MBAR_RESTORE","_POPUP_CLOSE","_POPUP_MAXIMIZE","_POPUP_MINIMIZE","_POPUP_RESTORE","_SYSTEM",};
							HBITMAP  bmph[10]={HBMMENU_MBAR_CLOSE,HBMMENU_MBAR_CLOSE_D,HBMMENU_MBAR_MINIMIZE,HBMMENU_MBAR_MINIMIZE_D,HBMMENU_MBAR_RESTORE,HBMMENU_POPUP_CLOSE,HBMMENU_POPUP_MAXIMIZE,HBMMENU_POPUP_MINIMIZE,HBMMENU_POPUP_RESTORE,HBMMENU_SYSTEM,};
							int j;
							
							#ifdef W_95
								for(j=0;j<10;j++)
									if (strstr(pos,bmpn[j])!=NULL)
									{ mi->dwTypeData=(char *)bmph[j]; break;}
								if (j>=10) mi->dwTypeData=(char *)hbm;
							#else
								#ifdef W_NT
									for(j=0;j<10;j++)
										if (strstr(pos,bmpn[j])!=NULL)
										{ mi->dwTypeData=(char *)bmph[j]; break;}
									if (j>=10) mi->dwTypeData=(char *)hbm;
								#else
									for(j=0;j<10;j++)
										if (strstr(pos,bmpn[j])!=NULL)
										{ mi->hbmpItem=bmph[j]; break;}
									if (j>=10) mi->hbmpItem=hbm;
								#endif
							#endif
						}
						ret++;
						break;
					case 3://BMPSTR
						#ifdef W_95
							mi->fMask|=MIIM_TYPE;
//							mi->fType|=MFT_STRING;
							mi->fType|=MFT_BITMAP;
							mi->fType&=(0xFFFFFFFF^MFT_STRING);
							mi->dwTypeData=(char *)hbm;
						#else
							#ifdef W_NT
								mi->fMask|=MIIM_TYPE;
	//							mi->fType|=MFT_STRING;
								mi->fType|=MFT_BITMAP;
								mi->fType&=(0xFFFFFFFF^MFT_STRING);
								mi->dwTypeData=(char *)hbm;
							#else
								mi->fMask|=MIIM_FTYPE|MIIM_STRING;
						//		mi->fType|=MIIM_BITMAP/*|MIIM_STRING*/;
								mi->hbmpItem=hbm;
							#endif
						#endif
						ret++;
						break;
					}
					//DestroyIcon(tmpico);
				}
				else
					GPC.m_ErrReport.GPWriteWarnLog2("Can't translate MENU info",iFlags ,"Imagelist not exist");
				delete []str;
			}
	}

	return ret;
}

BOOL GPMenu::OnCommandUserMenu(UINT idDlg, UINT nID)
{
	GPC.GPMSG->GPSendMenuMessage(GPTypeMenu,idDlg,nID);
	return TRUE;
}

BOOL GPMenu::DoUpdateUserMenu(UINT nID, CCmdUI *pCmdUI)
{
	BOOL ret=TRUE;

	if (pCmdUI->m_pSubMenu != NULL)  
	{
		int i;
		for(i=1;i<MENU_POPUP_COUNT && (!m_ArrPopupMenu[i] || m_ArrPopupMenu[i]->m_hMenu!=pCmdUI->m_pMenu->m_hMenu);i++);
		if (i!=MENU_POPUP_COUNT)
		{
			pCmdUI->m_pMenu->EnableMenuItem(pCmdUI->m_nIndex,
				MF_BYPOSITION | (m_ArrPopupMenu[i]->m_PopupMenuState==MF_ENABLED ? MF_ENABLED : MFS_GRAYED));
		}
		else ret=FALSE;
	}    
	else 
	{
		pCmdUI->Enable(!(m_ArrMenuState[nID]&MF_GRAYED));
		if ((m_ArrMenuState[nID]&MFT_RADIOCHECK)==0)	pCmdUI->SetCheck((m_ArrMenuState[nID]&MFS_CHECKED)!=0);
		if ((m_ArrMenuState[nID]&MFS_CHECKED)==0)		pCmdUI->SetRadio((m_ArrMenuState[nID]&MFT_RADIOCHECK)!=0);

		if (pCmdUI->m_pMenu && pCmdUI->m_pMenu->m_hMenu)
		{
			MENUITEMINFO mii={0};
			mii.cbSize=sizeofMENUITEMINFO;
			mii.fMask=MIIM_STATE;
			::GetMenuItemInfo(pCmdUI->m_pMenu->m_hMenu,pCmdUI->m_nIndex,TRUE,&mii);
			if (mii.fState!=m_ArrMenuState[nID])
			{
				mii.fState=m_ArrMenuState[nID];
				::SetMenuItemInfo(pCmdUI->m_pMenu->m_hMenu,pCmdUI->m_nIndex,TRUE,&mii);
				::EnableMenuItem(pCmdUI->m_pMenu->m_hMenu,pCmdUI->m_nIndex,MF_BYPOSITION|m_ArrMenuState[nID]);
				if (pCmdUI->m_pOther) ::DrawMenuBar(pCmdUI->m_pOther->m_hWnd);
			}
		}
	}

	return ret;
}


void GPMenu::Fill_mArrMenu(BOOL DelAll = FALSE)
{
	if (!m_ArrPopupMenu[0])  
	{
		m_ArrPopupMenu[0]=new CMenuCustom;
		m_ArrPopupMenu[0]->m_dwViewType=0;
	}
	if (GPTypeMenu==0) m_ArrPopupMenu[0]->m_hMenu=::GetMenu(AfxGetMainWnd()->m_hWnd);
	else m_ArrPopupMenu[0]->m_hMenu=::GetMenu(MenuOwner);

	int pos;
	if (GPTypeMenu==0) 
	{
		int cnt=0;
		for(pos=::GetMenuItemCount(m_ArrPopupMenu[0]->m_hMenu)-1;pos>=0;pos--)
		{
			HMENU tmphm=::GetSubMenu(m_ArrPopupMenu[0]->m_hMenu,pos);
			BOOL isTMenu=IsTerminalMenu(tmphm);
			if (isTMenu) 
			{
				if (!m_ArrPopupMenu[++cnt]) m_ArrPopupMenu[cnt]= new CMenuCustom;
				m_ArrPopupMenu[cnt]->m_hMenu=tmphm;
				m_ArrPopupMenu[cnt]->m_dwMenuStyle=TranslateMenuFlags(MF_BYPOSITION|MF_POPUP|MFT_STRING, "E");
			}
			else
				if (DelAll && m_ArrPopupMenu[0] && m_ArrPopupMenu[0]->m_hMenu)
						::DeleteMenu(m_ArrPopupMenu[0]->m_hMenu,pos, MF_BYPOSITION);
		}
	}

	if (DelAll)
	{
		ReleaseHBMP();
		int i;
		for(i=MENU_POPUP_START;i<MENU_POPUP_COUNT;i++) 	
		{
			if (m_ArrPopupMenu[i]!=NULL)
			{
				if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwDeletePopupMenu++;
				delete m_ArrPopupMenu[i];
			}
			m_ArrPopupMenu[i]=NULL;
		}
//		GPDrawMenuBar();
	}
}

BOOL GPMenu::GPCreatePopupMenu(UINT IdMenu, UINT IdPopup, UINT PosItem, char *iText, char *iFlag)
{
	BOOL ret=FALSE;

	if (m_ArrPopupMenu[IdMenu])
	{
		if (m_ArrPopupMenu[IdPopup])
		{
			if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwDeletePopupMenu++;
			delete m_ArrPopupMenu[IdPopup];
		}
		m_ArrPopupMenu[IdPopup]=new CMenuCustom;
		if (m_ArrPopupMenu[IdPopup])
		{
			if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwCreatePopupMenu++;
			m_ArrPopupMenu[IdPopup]->m_hMenu=::CreatePopupMenu();
			char *str;
			if (iFlag)
			{
				str=new char [(int)strlen(iFlag)+10];
				strcpy(str,iFlag);
			}
			else
			{
				str=new char [100];
				*str=0;
			}
			m_ArrPopupMenu[IdPopup]->csDefContextName=ExtractField(ExtractField(str,2,";DEFCONTEXT="),1,";");
			m_ArrPopupMenu[IdPopup]->m_dwMenuStyle=TranslateMenuFlags(MF_BYPOSITION|MF_POPUP|MFT_STRING, str);
			const char *tmpMenuText;

			ret=::InsertMenu(
				m_ArrPopupMenu[IdMenu]->m_hMenu,
				PosItem,
				m_ArrPopupMenu[IdPopup]->m_dwMenuStyle,
				(UINT)m_ArrPopupMenu[IdPopup]->m_hMenu,
				tmpMenuText=(iText!=NULL?DosToAnsi(iText):"Popup menu")
				);

			#ifdef W_95
			#else
				#ifdef W_NT
				#else
					MENUINFO MI={0};
					if (GPTranslateMenuInfo(iFlag, &MI)>0)
						SetMenuInfo(m_ArrPopupMenu[IdPopup]->m_hMenu,&MI);
				#endif
			#endif


			MENUITEMINFO MII={0};
			MII.cbSize=sizeofMENUITEMINFO;
			MII.fMask=MIIM_DATA;
			MII.dwItemData=RegisterMenuItem(
				IdPopup,
				(UINT)m_ArrPopupMenu[IdPopup]->m_hMenu,
				m_ArrPopupMenu[IdPopup]->csDefContextName,
				tmpMenuText,
				m_ArrPopupMenu[IdMenu]->m_dwViewType,
				m_ArrPopupMenu[IdMenu]->m_hMenu
				);
			GPTranslateMenuItemInfo(iFlag, &MII);
			SetMenuItemInfo(m_ArrPopupMenu[IdMenu]->m_hMenu,PosItem,TRUE,&MII);
			delete[] str;
		}
	}
	return ret;
}


BOOL GPMenu::GPAppendMenu(UINT IdPopup, UINT IdItem, char *posflg, char *postxt)
{
	BOOL ret=FALSE;

	if (m_ArrPopupMenu[IdPopup]!=NULL)	
	{
		const char *tmpMenuText=postxt?DosToAnsi(postxt):"Menu item";
		if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwCreateMenu++;
		ret= ::AppendMenu(m_ArrPopupMenu[IdPopup]->m_hMenu,GPSetMenuFlags(IdItem+MENU_ID_START,posflg==NULL?"":posflg)|MFT_STRING,IdItem+MENU_ID_START,tmpMenuText);

		MENUITEMINFO MII={0};
		MII.fMask=MIIM_DATA;
		MII.cbSize=sizeofMENUITEMINFO;

		CString csTmpContext=ExtractField(ExtractField(posflg==NULL?"":posflg,2,";CONTEXT="),1,";");
		if (csTmpContext=="") csTmpContext=m_ArrPopupMenu[IdPopup]->csDefContextName;

		MII.dwItemData=RegisterMenuItem(IdPopup,IdItem,csTmpContext,tmpMenuText,m_ArrPopupMenu[IdPopup]->m_dwViewType,m_ArrPopupMenu[IdPopup]->m_hMenu);
		GPTranslateMenuItemInfo(posflg, &MII);
		SetMenuItemInfo(m_ArrPopupMenu[IdPopup]->m_hMenu,IdItem+MENU_ID_START,FALSE,&MII);
	}
	return ret;
}

BOOL GPMenu::GPInsertMenu(UINT IdPopup, UINT PosItem, UINT IdItem, char *posflg, char *postxt)
{
	BOOL ret=FALSE;
	if (m_ArrPopupMenu[IdPopup]!=NULL)
	{
		const char *tmpMenuText=postxt?DosToAnsi(postxt):"Menu item";
		DWORD dwFlags=TranslateMenuFlags(MF_BYPOSITION|MFT_STRING, posflg==NULL?"":posflg);
		m_ArrMenuState[IdItem%MENU_ID_COUNT]=dwFlags;
		ret=::InsertMenu(
			m_ArrPopupMenu[IdPopup]->m_hMenu,
			PosItem,
			dwFlags,
			IdItem+MENU_ID_START,
			tmpMenuText
			);
		if (ret && GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwCreateMenu++;
		MENUITEMINFO MII={0};
		MII.fMask=MIIM_DATA;
		MII.cbSize=sizeofMENUITEMINFO;

		CString csTmpContext=ExtractField(ExtractField(posflg==NULL?"":posflg,2,";CONTEXT="),1,";");
		if (csTmpContext=="") csTmpContext=m_ArrPopupMenu[IdPopup]->csDefContextName;

		MII.dwItemData=RegisterMenuItem(IdPopup,IdItem,csTmpContext,tmpMenuText,m_ArrPopupMenu[IdPopup]->m_dwViewType,m_ArrPopupMenu[IdPopup]->m_hMenu);
		GPTranslateMenuItemInfo(posflg, &MII);
		::SetMenuItemInfo(m_ArrPopupMenu[IdPopup]->m_hMenu,PosItem,TRUE,&MII);
	}
	return ret;
}

BOOL GPMenu::GPModifyByCom(UINT IdItem, char *posflg, char *postxt)
{
	BOOL ret=::ModifyMenu(m_ArrPopupMenu[0]->m_hMenu,IdItem+MENU_ID_START,
		GPSetMenuFlags(IdItem+MENU_ID_START,posflg==NULL?"":posflg)|MF_BYCOMMAND,IdItem+MENU_ID_START,postxt!=NULL?DosToAnsi(postxt):"Menu item");

	MENUITEMINFO MII={0};
	MII.cbSize=sizeofMENUITEMINFO;
	MII.fMask=MIIM_DATA;
	::GetMenuItemInfo(m_ArrPopupMenu[0]->m_hMenu,IdItem+MENU_ID_START,FALSE,&MII);
	CString csTmpContext=ExtractField(ExtractField(posflg==NULL?"":posflg,2,";CONTEXT="),1,";");
	MII.fMask=0;
	if (csTmpContext!="") 
	{
		MENUINFOArray[MII.dwItemData].csContext=csTmpContext;
		if (postxt && *postxt) MENUINFOArray[MII.dwItemData].csText=postxt;
	}

	#ifdef W_95
		if ((postxt==NULL  || *postxt==0) && GPTranslateMenuItemInfo(posflg, &MII)>0)
	#else
		#ifdef W_NT
			if ((postxt==NULL  || *postxt==0) && GPTranslateMenuItemInfo(posflg, &MII)>0)
		#else
			if (GPTranslateMenuItemInfo(posflg, &MII)>0)
		#endif
	#endif
				::SetMenuItemInfo(m_ArrPopupMenu[0]->m_hMenu,IdItem+MENU_ID_START,FALSE,&MII);

	return ret;
}

BOOL GPMenu::GPModifyByPos(UINT IdPopup, UINT PosItem, char *posflg, char *postxt)
{
	BOOL ret=FALSE;
	if (m_ArrPopupMenu[IdPopup]!=NULL)
	{
		UINT IdItem;
		IdItem=::GetMenuItemID(m_ArrPopupMenu[IdPopup]->m_hMenu,PosItem);
		ret=::ModifyMenu(m_ArrPopupMenu[IdPopup]->m_hMenu,PosItem,GPSetMenuFlags(IdItem,posflg==NULL?"":posflg)|MF_BYPOSITION,IdItem,postxt!=NULL?DosToAnsi(postxt):"Menu item");
		MENUITEMINFO MII={0};
		MII.cbSize=sizeofMENUITEMINFO;
		MII.fMask=MIIM_DATA;
		::GetMenuItemInfo(m_ArrPopupMenu[0]->m_hMenu,PosItem,TRUE,&MII);
		CString csTmpContext=ExtractField(ExtractField(posflg==NULL?"":posflg,2,";CONTEXT="),1,";");
		MII.fMask=0;
		if (csTmpContext!="")  MENUINFOArray[MII.dwItemData].csContext=csTmpContext;
		if (postxt && *postxt) MENUINFOArray[MII.dwItemData].csText=postxt;

		#ifdef W_95
			if ((postxt==NULL  || *postxt==0) && GPTranslateMenuItemInfo(posflg, &MII)>0)
		#else
			#ifdef W_NT
				if ((postxt==NULL  || *postxt==0) && GPTranslateMenuItemInfo(posflg, &MII)>0)
			#else
				if (GPTranslateMenuItemInfo(posflg, &MII)>0)
			#endif
		#endif
					::SetMenuItemInfo(m_ArrPopupMenu[IdPopup]->m_hMenu,PosItem,TRUE,&MII);
	}
	return ret;
}

BOOL GPMenu::GPRemoveByPos(UINT IdPopup, UINT PosItem)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwDeleteMenu++;
	BOOL ret=FALSE;
	if (m_ArrPopupMenu[IdPopup]!=NULL)	
	{
		MENUITEMINFO MII={0};
		MII.cbSize=sizeofMENUITEMINFO;
		MII.fMask=MIIM_DATA;
		::GetMenuItemInfo(m_ArrPopupMenu[0]->m_hMenu,PosItem,TRUE,&MII);
		UnRegisterMenuItem(MII.dwItemData);
		ret=::DeleteMenu(m_ArrPopupMenu[IdPopup]->m_hMenu,PosItem,MF_BYPOSITION); 
	}
	return ret;
}

BOOL GPMenu::GPEnableByPos(UINT IdPopup, UINT PosItem, char *posflg)
{
	BOOL ret=FALSE;
		if (m_ArrPopupMenu[IdPopup]!=NULL)	
		{
			ret=GPEditMenuFlags(::GetMenuItemID(m_ArrPopupMenu[IdPopup]->m_hMenu,PosItem),posflg==NULL?"":posflg);
			::EnableMenuItem(m_ArrPopupMenu[IdPopup]->m_hMenu,PosItem,MF_BYPOSITION|(strchr(posflg,'G')==NULL?MF_ENABLED:MFS_GRAYED));
			MENUITEMINFO MII={0};
			MII.cbSize=sizeofMENUITEMINFO;
			MII.fMask=MIIM_DATA;
			::GetMenuItemInfo(m_ArrPopupMenu[IdPopup]->m_hMenu,PosItem,TRUE,&MII);
			CString csTmpContext=ExtractField(ExtractField(posflg==NULL?"":posflg,2,";CONTEXT="),1,";");
			MII.fMask=0;
			if (csTmpContext!="")  MENUINFOArray[MII.dwItemData].csContext=csTmpContext;

			if (GPTranslateMenuItemInfo(posflg, &MII)>0)
				SetMenuItemInfo(m_ArrPopupMenu[IdPopup]->m_hMenu,PosItem,TRUE,&MII);
		}
	return ret;
}

BOOL GPMenu::GPEnableByCom(UINT IdItem, char *posflg)
{
	BOOL ret=::EnableMenuItem(m_ArrPopupMenu[0]->m_hMenu,IdItem+MENU_ID_START,
		GPEditMenuFlags(IdItem+MENU_ID_START,posflg==NULL?"":posflg)|MF_BYCOMMAND);
	MENUITEMINFO MII={0};
	MII.cbSize=sizeofMENUITEMINFO;
	MII.fMask=MIIM_DATA;
	::GetMenuItemInfo(m_ArrPopupMenu[0]->m_hMenu,IdItem+MENU_ID_START,FALSE,&MII);
	CString csTmpContext=ExtractField(ExtractField(posflg==NULL?"":posflg,2,";CONTEXT="),1,";");
	MII.fMask=0;
	if (csTmpContext!="")  MENUINFOArray[MII.dwItemData].csContext=csTmpContext;


	if (GPTranslateMenuItemInfo(posflg, &MII)>0)
		SetMenuItemInfo(m_ArrPopupMenu[0]->m_hMenu,IdItem+MENU_ID_START,FALSE,&MII);

	return ret;
}

BOOL GPMenu::GPCheckByPos(UINT IdPopup, UINT PosItem, char *posflg)
{
	BOOL ret=FALSE;
		if (m_ArrPopupMenu[IdPopup]!=NULL)
		{
			::CheckMenuItem(m_ArrPopupMenu[IdPopup]->m_hMenu,PosItem,MF_BYPOSITION|(strchr(posflg,'U')==NULL?MFS_CHECKED:MF_UNCHECKED));
			ret=GPEditMenuFlags(::GetMenuItemID(m_ArrPopupMenu[IdPopup]->m_hMenu,PosItem),posflg==NULL?"":posflg);
			MENUITEMINFO MII={0};
			MII.cbSize=sizeofMENUITEMINFO;
			MII.fMask=MIIM_DATA;
			::GetMenuItemInfo(m_ArrPopupMenu[IdPopup]->m_hMenu,PosItem,TRUE,&MII);
			CString csTmpContext=ExtractField(ExtractField(posflg==NULL?"":posflg,2,";CONTEXT="),1,";");
			MII.fMask=0;
			if (csTmpContext!="")  MENUINFOArray[MII.dwItemData].csContext=csTmpContext;

			if (GPTranslateMenuItemInfo(posflg, &MII)>0)
				SetMenuItemInfo(m_ArrPopupMenu[IdPopup]->m_hMenu,PosItem,TRUE,&MII);
		}
	return ret;
}

BOOL GPMenu::GPCheckByCom(UINT IdItem, char *posflg)
{
	::CheckMenuItem(m_ArrPopupMenu[0]->m_hMenu,IdItem+MENU_ID_START,MF_BYCOMMAND|(strchr(posflg,'U')==NULL?MFS_CHECKED:MF_UNCHECKED));
	MENUITEMINFO MII={0};
	MII.cbSize=sizeofMENUITEMINFO;
	MII.fMask=MIIM_DATA;
	::GetMenuItemInfo(m_ArrPopupMenu[0]->m_hMenu,IdItem+MENU_ID_START,FALSE,&MII);
	CString csTmpContext=ExtractField(ExtractField(posflg==NULL?"":posflg,2,";CONTEXT="),1,";");
	MII.fMask=0;
	if (csTmpContext!="")  MENUINFOArray[MII.dwItemData].csContext=csTmpContext;
	if (GPTranslateMenuItemInfo(posflg, &MII)>0)
		SetMenuItemInfo(m_ArrPopupMenu[0]->m_hMenu,IdItem+MENU_ID_START,FALSE,&MII);

	return GPEditMenuFlags(IdItem+MENU_ID_START,posflg==NULL?"":posflg);
}

BOOL GPMenu::GPCheckRadio(UINT IdPopup, UINT PosItem, UINT PosItemStart,  UINT PosItemEnd)
{
	BOOL ret=FALSE;
	if (m_ArrPopupMenu[IdPopup])	
	{
		UINT i,id;
		for(i=PosItemStart;i<PosItemEnd;i++)
			if ((id=::GetMenuItemID(m_ArrPopupMenu[IdPopup]->m_hMenu,i))>0)
				GPEditMenuFlags(id,i==PosItem ? "R":"U");

		ret=::CheckMenuRadioItem(m_ArrPopupMenu[IdPopup]->m_hMenu,PosItemStart,PosItemEnd,PosItem,MF_BYPOSITION);	
	}
	return ret;
}

BOOL GPMenu::GPAppendSeparator(UINT IdPopup)
{
	BOOL ret=FALSE;
	if (m_ArrPopupMenu[IdPopup])
	{
		if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwCreateMenu++;
		ret=::AppendMenu(m_ArrPopupMenu[IdPopup]->m_hMenu,MFT_SEPARATOR,0,NULL);
	}
	return ret;
}

BOOL GPMenu::GPInsertSeparator(UINT IdPopup, UINT PosItem)
{
	BOOL ret=FALSE;
	if (m_ArrPopupMenu[IdPopup])	
	{
		ret=::InsertMenu(m_ArrPopupMenu[IdPopup]->m_hMenu,PosItem,MFT_SEPARATOR|MF_BYPOSITION,0,NULL);
		if (ret && GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwCreateMenu++;
	}
	return ret;
}

BOOL GPMenu::GPRemoveByCom(UINT IdItem)
{
	BOOL ret=FALSE;
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwDeleteMenu++;
	HMENU mhm=NULL;
	if (GPTypeMenu==0)
		mhm=::GetMenu(AfxGetMainWnd()->m_hWnd);	
	else
		mhm=::GetMenu(MenuOwner);

	MENUITEMINFO MII={0};
	MII.cbSize=sizeofMENUITEMINFO;
	MII.fMask=MIIM_DATA;

	::GetMenuItemInfo(mhm,IdItem+MENU_ID_START,FALSE,&MII);
	UnRegisterMenuItem(MII.dwItemData);
	::DeleteMenu(mhm,IdItem+MENU_ID_START,MF_BYCOMMAND);
	
	return ret;
}


void GPMenu::GPDrawMenuBar()
{
	::DrawMenuBar(GPTypeMenu==0?AfxGetMainWnd()->m_hWnd:MenuOwner);
}

BOOL GPMenu::GPCreateTrackMenu(UINT IdPopup, char *posfg)
{
	BOOL ret=FALSE;

	if (m_ArrPopupMenu[IdPopup]!=NULL)
	{
		if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwDeletePopupMenu++;
		delete m_ArrPopupMenu[IdPopup];
	}
	m_ArrPopupMenu[IdPopup]=new CMenuCustom;
	if (m_ArrPopupMenu[IdPopup])
	{
		m_ArrPopupMenu[IdPopup]->csDefContextName=ExtractField(ExtractField(posfg?posfg:"",2,";DEFCONTEXT="),1,";");
		m_ArrPopupMenu[IdPopup]->m_dwMenuStyle=TranslateMenuFlags(0, posfg);

		m_ArrPopupMenu[IdPopup]->m_hMenu=::CreatePopupMenu();
		ret=m_ArrPopupMenu[IdPopup]->m_hMenu!=NULL;
		if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwCreatePopupMenu++;
		#ifdef W_95
		#else
			#ifdef W_NT
			#else
				MENUINFO MI={0};
				if (GPTranslateMenuInfo(posfg, &MI)>0)
					::SetMenuInfo(m_ArrPopupMenu[IdPopup]->m_hMenu,&MI);
			#endif
		#endif
	}
	return ret;
}

BOOL GPMenu::GPTrackPopupMenu(UINT IdPopup, UINT nFlags, int CX, int CY, CRect *re)
{
	BOOL ret=FALSE;
	if (this!=NULL)
	if (m_ArrPopupMenu[IdPopup]!=NULL) 
	{
		if (re!=NULL && re->IsRectEmpty()==TRUE) re=NULL;
		ret=::TrackPopupMenu(m_ArrPopupMenu[IdPopup]->m_hMenu,nFlags, CX, CY,0,MenuOwner,re);
	}
	return ret;
}

BOOL GPMenu::EnablePopup(UINT IdPopup, UINT nFlags)
{
	BOOL ret=FALSE;
	if (this && m_ArrPopupMenu[IdPopup]) 
	{
		if (nFlags==0) 
			m_ArrPopupMenu[IdPopup]->m_PopupMenuState=(m_ArrPopupMenu[IdPopup]->m_PopupMenuState|MF_ENABLED)^MF_ENABLED;
		else 
			m_ArrPopupMenu[IdPopup]->m_PopupMenuState=m_ArrPopupMenu[IdPopup]->m_PopupMenuState|MF_ENABLED;
		
		UINT i;
		MENUITEMINFO mii={0};
		mii.cbSize=sizeofMENUITEMINFO;
		mii.fMask=MIIM_STATE;
		for(i=0;i<MENU_POPUP_COUNT ;i++)
			if (m_ArrPopupMenu[i] && m_ArrPopupMenu[i]->m_hMenu && i!=IdPopup)
			{
				int nMenu=::GetMenuItemCount(m_ArrPopupMenu[i]->m_hMenu);
				int j;
				for(j=0;j<nMenu;j++)
					if (::GetSubMenu(m_ArrPopupMenu[i]->m_hMenu,j)==m_ArrPopupMenu[IdPopup]->m_hMenu) 
					{
						::GetMenuItemInfo(m_ArrPopupMenu[i]->m_hMenu,j,MF_BYPOSITION,&mii);
						if ((mii.fState&0x3)!=(nFlags==0?MFS_GRAYED:MF_ENABLED) && ::EnableMenuItem(m_ArrPopupMenu[i]->m_hMenu,j,MF_BYPOSITION|(nFlags==0?MFS_GRAYED:MF_ENABLED)) && i==0)
							GPDrawMenuBar();
						ret=TRUE;
					}
			}
	}
	return ret;
}

void GPMenu::ReleaseHBMP()
{
	if (this)
	{
		int i;
		for(i=MENU_POPUP_START;i<MENU_POPUP_COUNT;i++) 	
		{
			if (m_ArrPopupMenu[i]!=NULL && ::IsMenu(m_ArrPopupMenu[i]->m_hMenu))
			{
				int nMenu=::GetMenuItemCount(m_ArrPopupMenu[i]->m_hMenu);
				MENUITEMINFO mii={0};
				mii.cbSize=sizeofMENUITEMINFO;

				#ifdef W_95
					mii.fMask|=MIIM_TYPE;
				#else
					#ifdef W_NT
						mii.fMask|=MIIM_TYPE;
					#else
						mii.fMask|=MIIM_BITMAP;
					#endif
				#endif
				int j;
				for(j=0;j<nMenu;j++)
					if (::GetSubMenu(m_ArrPopupMenu[i]->m_hMenu,j)==NULL) 
					{
						//int id=m_ArrPopupMenu[i]->GetMenuItemID(j);
						GetMenuItemInfo(m_ArrPopupMenu[i]->m_hMenu,j,TRUE,&mii);
						#ifdef W_95
							if (mii.dwTypeData!=NULL)
							{
								DeleteObject(mii.dwTypeData );
								mii.dwTypeData =NULL;
								SetMenuItemInfo(m_ArrPopupMenu[i]->m_hMenu,j,TRUE,&mii);
							}
						#else
							#ifdef W_NT
								if (mii.dwTypeData!=NULL)
								{
									DeleteObject(mii.dwTypeData );
									mii.dwTypeData =NULL;
									SetMenuItemInfo(m_ArrPopupMenu[i]->m_hMenu,j,TRUE,&mii);
								}
							#else
								if (mii.hbmpItem!=NULL)
								{
									DeleteObject(mii.hbmpItem);
									mii.hbmpItem=NULL;
									SetMenuItemInfo(m_ArrPopupMenu[i]->m_hMenu,j,TRUE,&mii);
								}
							#endif
						#endif
					}
			}
		}
	}
}

UINT GPMenu::FindMenuItem(UINT iIdItem, UINT *oIdPopup, UINT *oPos, CString *oName, UINT nMaxItem)
{
	UINT finPopup=0;
	iIdItem+=MENU_ID_START;

	UINT i;
	for(i=0;i<MENU_POPUP_COUNT && finPopup<nMaxItem;i++)
		if (m_ArrPopupMenu[i]!=NULL && ::IsMenu(m_ArrPopupMenu[i]->m_hMenu))
		{
			UINT nItem=::GetMenuItemCount(m_ArrPopupMenu[i]->m_hMenu);
			if (nItem<0xFFFF)
			{
				UINT j;
				for(j=0;j<nItem;j++)
					if (::GetSubMenu(m_ArrPopupMenu[i]->m_hMenu,j)==NULL && ::GetMenuItemID(m_ArrPopupMenu[i]->m_hMenu,j)==iIdItem)
					{
						oIdPopup[finPopup]=i;
						oPos[finPopup]=j;
						char tmps[1500];
						tmps[::GetMenuString(m_ArrPopupMenu[i]->m_hMenu,j,tmps,1490,MF_BYPOSITION)]=0;
						oName[finPopup]=tmps;
						finPopup++;
					}
			}
		}

	return finPopup;
}

BOOL GPMenu::IsTerminalMenu(HMENU ihMenu)
{
	BOOL ret=FALSE;
	int i;
	for(i=0;ihMenu && i<MENU_POPUP_START && !ret;i++)
		ret=(m_ArrPopupMenu[i] && ihMenu==m_ArrPopupMenu[i]->m_PopupMenuINIT);

	return ret;
}

void GPMenu::InitTermMenuList()
{
	if (GPTypeMenu==0)
	{
		UINT i;
		for(i=1;i<MENU_POPUP_COUNT;i++)
			if (m_ArrPopupMenu[i]) m_ArrPopupMenu[i]->m_PopupMenuINIT=NULL;

		if (m_ArrPopupMenu[0]) delete m_ArrPopupMenu[0];

		m_ArrPopupMenu[0]=new CMenuCustom; 
		m_ArrPopupMenu[0]->m_dwViewType=0;
		m_ArrPopupMenu[0]->m_hMenu= ::GetMenu(AfxGetMainWnd()->m_hWnd);
		m_ArrPopupMenu[0]->m_PopupMenuINIT=m_ArrPopupMenu[0]->m_hMenu;
		UINT nItems=::GetMenuItemCount(m_ArrPopupMenu[0]->m_hMenu);
		for(i=1;i<=nItems;i++)
		{
			if (!m_ArrPopupMenu[i])
			{
				m_ArrPopupMenu[i]=new CMenuCustom;
				m_ArrPopupMenu[i]->m_hMenu=::GetSubMenu(m_ArrPopupMenu[0]->m_hMenu,i-1);
			}
			m_ArrPopupMenu[i]->m_PopupMenuINIT=::GetSubMenu(m_ArrPopupMenu[0]->m_hMenu,i-1);
		}
	}
}

DWORD GPMenu::RegisterMenuItem(DWORD dwPopupId, DWORD dwItemId, const char *ccContext, const char *Text, DWORD dwFlags, HMENU ihMenu)
{
	PGPMENUINFO pmi=&MENUINFOArray[++m_dwODCMENUID];
	CGPContextMenu::ClearItem(pmi);
	pmi->dwPopupId=dwPopupId;
	pmi->csContext=ccContext;
	pmi->csText=Text;
	pmi->hMenu=ihMenu;
	pmi->dwCmd=dwItemId;
	pmi->dwFlags=dwFlags;
	return m_dwODCMENUID;
}

DWORD GPMenu::RegisterMenuItem(GPMENUINFO &iGPMenuInfo)
{
	MENUINFOArray[++m_dwODCMENUID]=iGPMenuInfo;
	return m_dwODCMENUID;
}

DWORD GPMenu::UnRegisterMenuItem(DWORD dwRegItemId)
{
	MENUINFOArray.RemoveItem(dwRegItemId);
	return MENUINFOArray.GetCount();
}


DWORD GPMenu::SetODCForTerminalMenu(CODContext *ipContext, HMENU ihPopup, DWORD dwFlags)
{
	int pos;
	char *menuText=new char[2000];
	char *menuText2=menuText;
	if (ipContext && ipContext->m_ContextName==GPC.csODCTerminalMenuName
		&& ihPopup && (!GPC.m_pContextMenu || GPC.m_pContextMenu->m_Menu!=ihPopup))
		for(pos=::GetMenuItemCount(ihPopup)-1;pos>=0;pos--)
		{
			MENUITEMINFO mii={0};
			mii.cbSize=sizeofMENUITEMINFO;
			*menuText=0;
			mii.dwTypeData=menuText;
			mii.cch=990;

			#ifdef W_95
				mii.fMask=MIIM_FTYPE|MIIM_STRING|MIIM_DATA|MIIM_ID;
			#else
				#ifdef W_NT
					mii.fMask=MIIM_FTYPE|MIIM_STRING|MIIM_DATA|MIIM_ID;
				#else
					mii.fMask=MIIM_FTYPE|MIIM_STRING|MIIM_DATA|MIIM_ID;
				#endif
			#endif

			::GetMenuItemInfo(ihPopup,pos,TRUE,&mii);

			char *tmpPos=menuText;
			char *tmpPosD=menuText2;
			while(*tmpPos)
			{
				if (*tmpPos=='&') tmpPos++;
				*(tmpPosD++)=*tmpPos;
				if (*tmpPos) tmpPos++;
			}
			*tmpPosD=0;
			mii.dwItemData=RegisterMenuItem(((DWORD)ihPopup)|0x80000000,(UINT)mii.wID, GPC.csODCTerminalMenuName, menuText2, dwFlags,ihPopup);
			tmpPos=menuText;
			while(*tmpPos)
			{
				if (*tmpPos<9 && *tmpPos>0) *tmpPos=0;
				tmpPos++;
			}

			#ifdef W_95
				mii.fMask=MIIM_FTYPE|MIIM_STRING|MIIM_DATA;
			#else
				#ifdef W_NT
					mii.fMask=MIIM_FTYPE|MIIM_STRING|MIIM_DATA;
				#else
					mii.fMask=MIIM_FTYPE|MIIM_STRING|MIIM_DATA;
				#endif
			#endif

			mii.fType|=MFT_OWNERDRAW;
			::SetMenuItemInfo(ihPopup,pos,TRUE,&mii);

			HMENU tmphm=::GetSubMenu(ihPopup,pos);
			if (tmphm)
				GPMenu::SetODCForTerminalMenu(ipContext, tmphm, dwFlags|0x00000001);
		}

	delete []menuText;
	return 0;
}