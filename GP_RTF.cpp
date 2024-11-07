// GP_RTF.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GP_RTF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#ifndef BOM_DEFPARADIR
	#define BOM_DEFPARADIR			0x0001	// Default paragraph direction (implies alignment) (obsolete) 
	#define BOM_PLAINTEXT			0x0002	// Use plain text layout (obsolete) 
	#define BOE_RTLDIR				0x0001	// Default paragraph direction (implies alignment) (obsolete) 
	#define BOE_PLAINTEXT			0x0002	// Use plain text layout (obsolete) 
#endif // _RICHEDIT_VER == 0x0100 



/////////////////////////////////////////////////////////////////////////////
// GP_RTF
const UINT GP_RTF::uNMethods=115;
const char *GP_RTF::cArrMethods[]={
/*00*/	"CanUndo","GetLineCount","GetModify","SetModify","GetRect",
/*05*/	"GetSel","GetSelText","GetSelectionType","LimitText","GetLimitText",
/*10*/	"GetCharPos","HideSelection","GetLine","GetTextLength","GetFirstVisibleLine",
/*15*/	"EmptyUndoBuffer","CanPaste","PasteSpecial","LineFromChar","LineIndex",
/*20*/	"LineLength","LineScroll","ReplaceSel","SetBackgroundColor","SetRect",
/*25*/	"RequestResize","SetSel","SetOptions","SetReadOnly","Undo",
/*30*/	"Clear","Copy","Cut","Paste","ClearText",
/*35*/	"AddOptions","AndOptions","XorOptions","UpdateGroup","Load",
/*40*/	"LoadSel","Save","SaveSel","SDCF","SSCF",
/*45*/	"SWCF","GDCF","GSCF","SPF","GPF",
/*50*/	"FindText","PrintAsText","Print","OpenDefEditorAsText","OpenDefEditor",
/*55*/	"SetLineObject","SetColumnObject","SetLinePrefix","SetColumnPrefix","SetCharObject",
/*60*/	"SetCharPrefix","SetUndoLimit","SetZoom","StopGroupTyping","GetAllAsText",
/*65*/	"PrintSelAsText","PrintSel","OpenSelDefEditorAsText","OpenSelDefEditor","AutoURLDetect",
/*70*/	"CanRedo","FindWordBreak","GetAutoURLDetect","GetBiDiOptions","SetBiDiOptions",
/*75*/	"GetEditStyle","SetEditStyle","GetLangOptions","SetLangOptions","GetRedoName",
/*80*/	"GetScrollPos","GetTextMode","SetTextMode","GetTipogrphyOptions","SetTipogrphyOptions",
/*85*/	"GetUndoName","GetZoom","Reconversion","Redo","RequestResize",
/*90*/	"SetFontSize","SetScrollPos","SetTabSeq","GetTabSeq","SetIndent",
/*95*/	"GetIndent","PosFromChar","CharFromPos","ScrollCaret","DisplayBand",
/*100*/	"GetEventMask","SetEventMask","GetTextRange","ShowVScrollBar","ShowHScrollBar",
/*105*/	"OutLine","TrimEndSpace","SetVP","SetAutoWidth","SetImeStatus",
/*110*/	"GetImeStatus","SetCueBanner","GetCueBanner","ShowBalloonTip","HideBalloonTip",
/*115*/	"","","","","",
/*120*/	"","","","","",
	};

const char *GP_RTF::cArrMethodsParams[]={
/*00*/	"","","","ModifyFlag","",
/*05*/	"","","","TextLen","",
/*10*/	"Pos","bHide, bPerm","nLine","","",
/*15*/	"","Not Present","Not Present","nIndex","nLine",
/*20*/	"nLine","nLines, nChars","Text","R, G, B","left,top,right,bottom",
/*25*/	"","nStartChar, nEndChar","Options","bReadOnly","",
/*30*/	"","","","","",
/*35*/	"Options","Options","Options","","FileName, Type",
/*40*/	"FileName, Type","FileName, Type","FileName, Type","C=R,G,B;E=ABCDEFHILMNOPRSUW;H=yHeight;O=yOffset;N=szFaceName;P=bPitchAndFamily;K=bCharSet;W=wWeight;S=sSpacing;B=R,G,B;U=1SDUNW;F=wKerning","C=R,G,B;E=ABCDEFHILMNOPRSUW;H=yHeight;O=yOffset;N=szFaceName;P=bPitchAndFamily;K=bCharSet;W=wWeight;S=sSpacing;B=R,G,B;U=1SDUNW;F=wKerning",
/*45*/	"C=R,G,B;E=ABCDEFHILMNOPRSUW;H=yHeight;O=yOffset;N=szFaceName;P=bPitchAndFamily;K=bCharSet;W=wWeight;S=sSpacing;B=R,G,B;U=1SDUNW;F=wKerning","Not Present","Not Present","NU=wNumbering;EF=DKNLWBRSTEC;SI=dxStartIndent;RI=dxRightIndent;OF=dxOffset;AL=wAlignment;TS=tb1,tb2,...,tbN;SB=dySpaceBefore;SA=dySpaceAfter;LS=dyLineSpacing;ST=sStyle;LR=bLineSpacingRule;OL=bOutlineLevel;SW=wShadingWeight;SS=wShadingStyle;NB=wNumberingStart;NS=wNumberingStyle;NT=wNumberingTab;BS=wBorderSpace;BW=wBorderWidth;BO=wBorders","Not Present",
/*50*/	"cpMin,cpMax,Type;Text","","","","",
/*55*/	"ObjectId","ObjectId","Text","Text","ObjectId",
/*60*/	"Text","nLimit","numerator,denominator","","",
/*65*/	"","","","","bAuto",
/*70*/	"","StartIndex,OPTIONS{CLASSIFY ISDELIMITER LEFT LEFTBREAK MOVEWORDLEFT MOVEWORDRIGHT RIGHT RIGHTBREAK}","","","Mask,Effects",
/*75*/	"","Style","","Options","",
/*80*/	"","","Mode","","Options",
/*85*/	"","","","","",
/*90*/	"","x,y","String","","bIndent",
/*95*/	"","Index","x,y","","left,top,right,bottom",
/*100*/	"","MASK_LIST","cMin,cMax","bShow","bShow",
/*105*/	"lparam,Option","","iPos","min,max,delta","ImeStatus",
/*110*/	"","BannerText","","nIcon,TitleText^TipText","",
/*115*/	"","","","","",
/*120*/	"","","","","",
	};

GP_RTF::GP_RTF(UINT iUnitId)
{
	m_DOflags=0;
	AutoWidthMin=0;AutoWidthMax=0;AutoWidthDelta=0;
	m_uCurVP=0;
	m_bTrackMousePos=FALSE;
	EnableAutomation();
	referGPU=NULL;
	UnitId=iUnitId;
	CharObjId=lastSelPos=LineObjId=ColumnObjId=-1;
	m_TabReplaser="    ";
	m_Indent=1;
}

GP_RTF::~GP_RTF()
{
}

BEGIN_MESSAGE_MAP(GP_RTF, CRichEditCtrl)
	//{{AFX_MSG_MAP(GP_RTF)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_CONTROL_REFLECT(EN_ERRSPACE, OnErrspace)
	ON_CONTROL_REFLECT(EN_HSCROLL, OnHscroll)
	ON_CONTROL_REFLECT(EN_MAXTEXT, OnMaxtext)
	ON_CONTROL_REFLECT(EN_SETFOCUS, OnNotifySetfocus)
	ON_CONTROL_REFLECT(EN_UPDATE, OnUpdate)
	ON_CONTROL_REFLECT(EN_ALIGN_LTR_EC, OnALIGN_LTR_EC)
	ON_CONTROL_REFLECT(EN_ALIGN_RTL_EC, OnALIGN_RTL_EC)
	ON_CONTROL_REFLECT(EN_VSCROLL, OnVscroll)
	ON_CONTROL_REFLECT(EN_MSGFILTER, OnMSGFILTER)
	ON_CONTROL_REFLECT(EN_REQUESTRESIZE, OnREQUESTRESIZE)
	ON_CONTROL_REFLECT(EN_SELCHANGE, OnSELCHANGE)
	ON_CONTROL_REFLECT(EN_DROPFILES, OnDROPFILES)
	ON_CONTROL_REFLECT(EN_PROTECTED, OnPROTECTED)
	ON_CONTROL_REFLECT(EN_CORRECTTEXT, OnCORRECTTEXT)
	ON_CONTROL_REFLECT(EN_STOPNOUNDO, OnSTOPNOUNDO)
	ON_CONTROL_REFLECT(EN_IMECHANGE, OnIMECHANGE)
	ON_CONTROL_REFLECT(EN_SAVECLIPBOARD, OnSAVECLIPBOARD)
	ON_CONTROL_REFLECT(EN_OLEOPFAILED, OnOLEOPFAILED)
	ON_CONTROL_REFLECT(EN_OBJECTPOSITIONS, OnOBJECTPOSITIONS)
	ON_CONTROL_REFLECT(EN_DRAGDROPDONE, OnDRAGDROPDONE)
	ON_CONTROL_REFLECT(EN_PARAGRAPHEXPANDED, OnPARAGRAPHEXPANDED)
	ON_CONTROL_REFLECT(EN_ALIGNLTR, OnALIGNLTR)
	ON_CONTROL_REFLECT(EN_ALIGNRTL, OnALIGNRTL)
	ON_CONTROL_REFLECT(EN_LINK, OnLINK)
	ON_WM_PARENTNOTIFY_REFLECT()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CHAR()
	ON_WM_SIZING()
	ON_WM_NCHITTEST()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_CONTROL_REFLECT(EN_KILLFOCUS, OnNotifyKillfocus)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// GP_RTF message handlers

void GP_RTF::OnChange()
{
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnChange","");
		char *str = new char [10000];
		int nC=0;
		if ((nC=GetLine(0,str,9990))<1) *str=0;
		else str[nC]=0;
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnChangeEx",str);
		delete[] str;
		if (referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
			DoMethod("UpdateGroup",NULL);
	}
	OnChangeVP();
}

void GP_RTF::OnErrspace()
{
	if (referGPU!=NULL)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnErrspace","");
}

void GP_RTF::OnHscroll()
{
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnHscroll","");
		if (referGPU[UnitId&0xFFFF]->m_SizerArray)	Invalidate();
	}
	OnChangeVP();
}

void GP_RTF::OnNotifyKillfocus()
{
	if (referGPU!=NULL)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNotifyKillfocus","");
}

void GP_RTF::OnMaxtext()
	{if (referGPU!=NULL)
	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnMaxtext","");}

void GP_RTF::OnNotifySetfocus()
{
	if (referGPU!=NULL)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNotifySetfocus","");
}

void GP_RTF::OnUpdate()
{
	if (referGPU!=NULL)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnUpdate","");
}

void GP_RTF::OnVscroll()
{
	if (referGPU!=NULL)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnVscroll","");
	if (referGPU && referGPU[UnitId&0xFFFF]->m_SizerArray)	Invalidate();
	OnChangeVP();
}

void GP_RTF::OnMSGFILTER()
{
	if (referGPU!=NULL)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnMsgfilter","");
}

void GP_RTF::OnREQUESTRESIZE()
{
	if (referGPU!=NULL)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnRequestresize","");
}

void GP_RTF::OnSELCHANGE()
{
	if (referGPU!=NULL)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSelchange","");
	OnChangeVP();
}

void GP_RTF::OnDROPFILES()
{
	if (referGPU!=NULL)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDropfiles","");
}

void GP_RTF::OnPROTECTED()
{
	if (referGPU!=NULL)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnProtected","");
}

void GP_RTF::OnCORRECTTEXT()
{
	if (referGPU!=NULL)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnCorrecttext","");
}

void GP_RTF::OnSTOPNOUNDO()
{
	if (referGPU!=NULL)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnStopnoundo","");
}

void GP_RTF::OnIMECHANGE()
{
	if (referGPU!=NULL)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnImechange","");
}

void GP_RTF::OnSAVECLIPBOARD()
{
	if (referGPU!=NULL)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSaveclipboard","");
}

void GP_RTF::OnOLEOPFAILED()
{
	if (referGPU!=NULL)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnOleopfailed","");
}

void GP_RTF::OnOBJECTPOSITIONS()
{
	if (referGPU!=NULL)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnObjectpositions","");
}

void GP_RTF::OnDRAGDROPDONE()
{
	if (referGPU!=NULL)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDragdropdone","");
}

void GP_RTF::OnPARAGRAPHEXPANDED()
{
	if (referGPU!=NULL)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnParagraphexpanded","");
}

void GP_RTF::OnALIGNLTR()
{
	if (referGPU!=NULL)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnAlignltr","");
}

void GP_RTF::OnALIGNRTL()
{
	if (referGPU!=NULL)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnAlignrtl","");
}

void GP_RTF::OnLINK()
{
	if (referGPU!=NULL)
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnLink","");
}

void GP_RTF::ParentNotify(UINT message, LPARAM lParam)
{
	char txt[100];
	if (message==WM_CREATE || message==WM_DESTROY)
		sprintf(txt,"%d\x7F%d\x7F%X",message/0x10000,(message&0xFFFF),lParam/0x10000);
	else
		sprintf(txt,"%d\x7F%d\x7F%d\x7F%d",message/0x10000,(message&0xFFFF),lParam/0x10000,(lParam&0xFFFF));
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"ParentNotify",txt);
}

LRESULT GP_RTF::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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

	if (message==WM_KEYFIRST || message==WM_KEYLAST)
		OnChangeVP();

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
	else lpr=CRichEditCtrl::WindowProc(message, wParam, lParam);

	return lpr;
}

BOOL GP_RTF::PreTranslateMessage(MSG* pMsg)
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
		}
	}
	return CRichEditCtrl::PreTranslateMessage(pMsg);
}


static DWORD CALLBACK MyStreamOutCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
   CFile* pFile =(CFile*) dwCookie;
   pFile->Write(pbBuff, cb);
   *pcb = cb;
   return 0;
}// The example code.

static DWORD CALLBACK MyStreamInCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
   CFile* pFile =(CFile*) dwCookie;
   *pcb = pFile->Read(pbBuff, cb);
   return 0;
}

UINT GP_RTF::DoMethod(const char *iStr, char *oStr)
{
	UINT uSelType[5] ={SEL_EMPTY,SEL_TEXT,SEL_OBJECT,SEL_MULTICHAR,SEL_MULTIOBJECT,};
	char *cSelType[5]={"SEL_EMPTY","SEL_TEXT","SEL_OBJECT","SEL_MULTICHAR","SEL_MULTIOBJECT",};

	char met[150];
	UINT tmpUINT=0;
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

	switch(nfunc)
	{
	case 0: /*CanUndo*/		retint=CanUndo();		break;
	case 1: /*GetLineCount*/retint=GetLineCount();	break;
	case 2: /*GetModify*/	retint=GetModify();		break;
	case 3: /*SetModify*/	SetModify(atoipos);		break;
	case 4: /*GetRect*/
		if (oStr!=NULL)
		{
			CRect re;
			GetRect(&re);
			sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",re.left,re.top,re.right,re.bottom);
		}
		break;
	case 5: /*GetSel*/
		if (oStr!=NULL)
		{
			CHARRANGE cr={0};
			SendMessage(EM_EXGETSEL,0,(LPARAM)&cr);
			sprintf(oStr,"%d\x7F%d",cr.cpMin,cr.cpMax);
		}
		break;
	case 6: /*GetSelText*/
		if (oStr!=NULL)
		{
			TEXTRANGE tr={0};
			GetSel(tr.chrg.cpMin,tr.chrg.cpMax);
			tr.lpstrText= oStr;
			if (tr.chrg.cpMax-tr.chrg.cpMin>TMP_STR_OUT_LEN)
				tr.chrg.cpMax=tr.chrg.cpMin+TMP_STR_OUT_LEN;
			SendMessage(EM_GETTEXTRANGE,0,(LPARAM)&tr);

			int delim=127;
			if ((referGPU[UnitId&0xFFFF]->UnitCommonStyles&UCS_CRVM)==UCS_CRVM) delim=7;
			if ((referGPU[UnitId&0xFFFF]->UnitCommonStyles&UCS_CRSVM)==UCS_CRSVM) delim=3;
			char *str=oStr;
			char *str2=oStr;
			while(*(str)!=0)
			{
				if ((*str==10 && str[1]==13) || (*str==13 && str[1]==10)) {str++;*(str2++)=delim;}
				else
				if (*str==13 || *str==10) *(str2++)=delim;
				else
				if (*str==2 || *str==3) *(str2++)=(*str)-1;
				else *(str2++)=*str;
				str++;
			}
			*str2=0;
		}
		break;
	case 7: /*GetSelectionType*/
		if (oStr!=NULL)
		{
			tmpUINT=GetSelectionType();
			int i;
			for(i=0;i<5;i++)
				if ((tmpUINT&uSelType[i])==uSelType[i])
				{
					strcat(oStr,cSelType[i]);
					strcat(oStr,"|");
				}
		}
		break;
	case 8: /*LimitText*/		SendMessage(EM_EXLIMITTEXT,0, atoipos); 	break;
	case 9: /*GetLimitText*/	retint=GetLimitText();	break;
	case 10: /*GetCharPos*/
		if (oStr!=NULL)
		{
			CPoint po;
			po=GetCharPos(atoipos);
			sprintf(oStr,"%d\x7F%d",po.x,po.y);
		}
		break;
	case 11: /*HideSelection*/
		{
			UINT bHide=0,bPerm =0;
			m_LastScanf=sscanf(pos,"%d,%d",&bHide,&bPerm);
			HideSelection(bHide,bPerm);
		}
		break;
	case 12: /*GetLine*/
		if (oStr!=NULL)
		{
			tmpUINT=GetLine(atoipos,oStr,TMP_STR_OUT_LEN);
			oStr[tmpUINT]=0;
			char *str=oStr;str--;
			while(*(++str)!=0)
				if (*str==10) *str=0;
				else
				if (*str==13) *str=127;
				else
				if (*str==2)	*(str)=1;
				else
				if (*str==3)	*(str)=2;
		}
		break;
	case 13: /*GetTextLength*/			retint=GetTextLength();			break;
	case 14: /*GetFirstVisibleLine*/	retint=GetFirstVisibleLine();	break;
	case 15: /*EmptyUndoBuffer*/		EmptyUndoBuffer();				break;
	case 16: /*CanPaste*/				retint=CanPaste(atoipos);		break;

	case 18: /*LineFromChar*/			retint=SendMessage(EM_EXLINEFROMCHAR,0,atoipos);	break;
	case 19: /*LineIndex*/				retint=LineIndex(atoipos);	break;
	case 20: /*LineLength*/				retint=LineLength(atoipos);	break;
	case 21: /*LineScroll*/
		{
			UINT updn=0,rightleft=0;
			m_LastScanf=sscanf(pos,"%d,%d",&updn,&rightleft);
			LineScroll(updn,rightleft);
		}
		break;
	case 22: /*ReplaceSel*/
		{
			int chDelim=1;
			if ((referGPU[UnitId&0xFFFF]->UnitCommonStyles&UCS_CRVM)==UCS_CRVM) chDelim=2;
			if ((referGPU[UnitId&0xFFFF]->UnitCommonStyles&UCS_CRSVM)==UCS_CRSVM) chDelim=3;
			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
			char *pos3=pos333;
			do
			{
				pos3=strstr(pos3,"\\PARA");
				if (pos3!=NULL)
				{
					*(pos3++)=13;
					*(pos3++)=10;
					strcpy(pos3,pos3+3);
				}
			}
			while(pos3!=NULL);

			pos3=pos333;
			while(*pos3!=0)
			{
				if (*pos3==chDelim) *pos3=10;
				pos3++;
			}
			ReplaceSel(pos333,TRUE);
			delete[] pos333;
		}
		if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
			DoMethod("UpdateGroup",NULL);
		break;
	case 23: /*SetBackgroundColor*/
		{
			int R=-1,G=-1,B=-1;
			m_LastScanf=sscanf(pos,"%d,%d,%d",&R,&G,&B);
			if (R<0) SetBackgroundColor(TRUE,0);
			else SetBackgroundColor(FALSE,RGB(R,G,B));
		}
		break;
	case 24: /*SetRect*/
		{
			CRect re; re.SetRect(0,0,150,22);
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&re.left,&re.top,&re.right,&re.bottom);
			SetRect(re);
		}
		break;
	case 25: /*RequestResize*/	RequestResize();	break;
	case 26: /*SetSel*/
		{
			CHARRANGE cr={0};
			cr.cpMax=1;
			m_LastScanf=sscanf(pos,"%d,%d",&cr.cpMin,&cr.cpMax);
			SendMessage(EM_EXSETSEL,0,(LPARAM)&cr);
			break;
		}
	case 35: /*AddOptions*/
	case 36: /*AndOptions*/
	case 37: /*XorOptions*/
	case 27: /*SetOptions*/
		{
			UINT opt=0,type=ECOOP_SET;
			int i;
			for(i=0;i<N_RTF_OPTIONS;i++)
				if (strstr(pos,aRTFOptionName[i])!=NULL) opt|=aRTFOptionUINT[i];
			switch(nfunc)
			{
				case 35: /*AddOptions*/	type=ECOOP_OR;break;
				case 36: /*AndOptions*/	type=ECOOP_AND;break;
				case 37: /*XorOptions*/	type=ECOOP_XOR;break;
				case 27: /*SetOptions*/	type=ECOOP_SET;break;
			}
			SetOptions((WORD)type,opt);
		}
		break;
	case 28: /*SetReadOnly*/ SetReadOnly(atoipos);						break;
	case 29: /*Undo*/
		retint=Undo();
		if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
			DoMethod("UpdateGroup",NULL);
		break;
	case 30: /*Clear*/
		Clear();
		if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
			DoMethod("UpdateGroup",NULL);
		break;
	case 31: /*Copy*/
		Copy();
		if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
			DoMethod("UpdateGroup",NULL);
		break;
	case 32: /*Cut*/
		Cut();
		if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
			DoMethod("UpdateGroup",NULL);
		break;
	case 33: /*Paste*/
		Paste();
		if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
			DoMethod("UpdateGroup",NULL);
		break;
	case 34: /*ClearText*/
		{
			SetSel(0,-1);
			Clear();
			if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
				DoMethod("UpdateGroup",NULL);
		}
		break;
	case 38: /*UpdateGroup*/
		if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
		{
			char str[50];
			GetWindowText(str,45);str[45]=0;
			referGPU[UnitId&0xFFFF]->UpdateGroup(atoi(str),GetStyle());
		}
		break;
	case 39: /*Load*/
	case 40: /*LoadSel*/
		{
			char name[350];
			strncpy(name,pos,300);name[300]=0;
			UINT type=SF_RTF;
			char *pos2=strchr(name,',');
			if (pos2!=NULL)
			{
				*(pos2++)=0;
				if (_stricmp(pos2,"TEXT")==0) type=SF_TEXT;
			}

			try
			{
				CFile cFile;
				cFile.Open(name,CFile::modeRead|CFile::shareDenyNone,NULL);
				if (cFile.m_hFile!=CFile::hFileNull)
				{
					EDITSTREAM es;
					es.dwCookie =(DWORD) &cFile;
					es.pfnCallback = MyStreamInCallback;
					StreamIn(type|(nfunc==40?SFF_SELECTION:0), es);
					cFile.Close();
				}
			}
			catch(...)
			{
				GPC.m_ErrReport.GPWriteErrorLog("GP_RTF", "DoMethod 751",iStr);
			}
		}
		break;
	case 41: /*Save*/
	case 42: /*SaveSel*/
		{
			char *ctype[4]={"TEXT","RTF","RTFNOOBJS","TEXTIZED",};
			UINT  utype[4]={SF_TEXT,SF_RTF,SF_RTFNOOBJS,SF_TEXTIZED,};
			char name[350];
			strncpy(name,pos,300);name[300]=0;
			UINT type=SF_RTF;
			char *pos2=strchr(name,',');
			if (pos2!=NULL)
			{
				*(pos2++)=0;
				int i;
				for(i=0;i<4;i++)
					if (_stricmp(pos2,ctype[i])==0)
						type=utype[i];
			}

			try
			{
				CFile cFile;
				cFile.Open(name,CFile::modeCreate|CFile::modeWrite,NULL);
				if (cFile.m_hFile!=CFile::hFileNull)
				{
					EDITSTREAM es;
					es.dwCookie =(DWORD) &cFile;
					es.pfnCallback = MyStreamOutCallback;
					StreamOut(type|(nfunc==42?SFF_SELECTION:0), es);
					cFile.Close();
				}
			}
			catch(...)
			{
				GPC.m_ErrReport.GPWriteErrorLog("GP_RTF", "788 DoMethod",iStr);
			}
		}
		break;

	case 43: /*SDCF*/
	case 44: /*SSCF*/
	case 45: /*SWCF*/
		{
			char *postmpcc=new char [(int)strlen(pos)+10];
			strcpy(postmpcc,pos);
			char *cf[12]={"C=","E=","H=","O=","N=","P=","K=","W=","S=","B=","U=","F=",};
			CHARFORMAT2 chf;
			chf.cbSize = sizeof(chf);
			chf.dwMask =0;
			chf.dwEffects=0;

			int R=0,G=0,B=0,j;
			char *pos2;

			int i;
			for(i=0;i<12;i++)
				if ((pos2=strstr(postmpcc,cf[i]))!=NULL)
				{
					pos2+=2;
					switch(i)
					{
					case 0: /*"C=crTextColor",,*/
						m_LastScanf=sscanf(pos2,"%d,%d,%d",&R,&G,&B);
						chf.crTextColor=RGB(R,G,B);
						chf.dwMask|=CFM_COLOR;
						break;
					case 1: /*"E=dwEffects"*/
						{
							char *cmask="ABCDEFGHILMNOPRSUW",*pos3;
								UINT umask[18]={
								CFM_COLOR,CFM_BOLD,CFM_SMALLCAPS,CFM_DISABLED ,CFM_EMBOSS,
								CFM_SUPERSCRIPT,CFM_ALLCAPS,CFM_HIDDEN,CFM_ITALIC,CFM_LINK,CFM_IMPRINT,
								CFM_SUBSCRIPT,CFM_OUTLINE,CFM_PROTECTED,CFM_REVISED,
								CFM_STRIKEOUT,CFM_UNDERLINE,CFM_SHADOW,};
								UINT ueff[18]={
								CFE_AUTOCOLOR,CFE_BOLD,CFE_SMALLCAPS,CFE_DISABLED,CFE_EMBOSS,
								CFE_SUPERSCRIPT,CFE_ALLCAPS,CFE_HIDDEN,CFE_ITALIC,CFE_LINK,CFE_IMPRINT,
								CFE_SUBSCRIPT,CFE_OUTLINE,CFE_PROTECTED,CFE_REVISED,
								CFE_STRIKEOUT,CFE_UNDERLINE,CFE_SHADOW,};

							while(*pos2!=0 &&(pos3=strchr(cmask,*pos2))!=NULL)
							{
								pos2++;
								chf.dwEffects|=ueff[pos3-cmask];
								chf.dwMask|=umask[pos3-cmask];
							}
						}
						break;
					case 2: /*"H=yHeight"*/
						chf.yHeight=atoi(pos2);
						chf.dwMask|=CFM_SIZE;
						break;
					case 3: /*"O=yOffset"*/
						chf.yOffset=atoi(pos2);
						chf.dwMask|=CFM_OFFSET;
						break;
					case 4: /*"N=szFaceName"*/
						{
							strncpy(chf.szFaceName,pos2,32);
							chf.szFaceName[31]=0;
							char *pos3=strchr(chf.szFaceName,';');
							if (pos3!=NULL) *pos3=0;
							chf.dwMask|=CFM_FACE;
						}
						break;
					case 5: /*"P=bPitchAndFamily"*/
						for(j=0;j<18;j++)
							if (strncmp(pos2,clfPitchAndFamily[j],(int)strlen(clfPitchAndFamily[j]))==0)
							{
								chf.bPitchAndFamily=(unsigned char)ulfPitchAndFamily[j];
								chf.dwMask|=CFM_FACE;
								break;
							}
						break;
					case 6: /*"K=bCharSet "*/
						for(j=0;j<18;j++)
							if (strncmp(pos2,clfCharSet[j],(int)strlen(clfCharSet[j]))==0)
							{
								chf.bCharSet=(unsigned char)ulfCharSet[j];
								chf.dwMask|=CFM_CHARSET;
								break;
							}
						break;
					case 7: /*"W=wWeight"*/
						chf.wWeight=(WORD)atoi(pos2);
						chf.dwMask|=CFM_WEIGHT;
						break;
					case 8: /*"S=sSpacing"*/
						chf.sSpacing=(WORD)atoi(pos2);
						chf.dwMask|=CFM_SPACING;
						break;
					case 9: /*"B=crBackColor"*/
						m_LastScanf=sscanf(pos2,"%d,%d,%d",&R,&G,&B);
						chf.crBackColor=RGB(R,G,B);
						chf.dwMask|=CFM_BACKCOLOR;
						break;
					case 10: /*"U=bUnderlineType "*/
						{
							char *cmask="1SDUNWHITAO2-",*pos3;
								UINT umask[]={
								CFU_CF1UNDERLINE,CFU_UNDERLINE,CFU_UNDERLINEDOTTED,
								CFU_UNDERLINEDOUBLE ,CFU_UNDERLINENONE,CFU_UNDERLINEWORD,
								CFU_UNDERLINEHAIRLINE,CFU_INVERT,CFU_UNDERLINETHICK,CFU_UNDERLINEWAVE,
								CFU_UNDERLINEDASHDOT,CFU_UNDERLINEDASHDOTDOT,CFU_UNDERLINEDASH,
								};

							while(*pos2!=0 &&(pos3=strchr(cmask,*pos2))!=NULL)
							{
								chf.dwMask|=CFM_UNDERLINETYPE;
								chf.bUnderlineType |=umask[pos3-cmask];
								pos2++;
							}
						}
						break;
					case 11: /*"F=wKerning"*/
						chf.wKerning=(WORD)atoi(pos2);
						chf.dwMask|=CFM_KERNING;
						break;
					}
				}
			switch(nfunc)
			{
			case 43: /*SDCF*/	SetDefaultCharFormat(chf);		break;
			case 44: /*SSCF*/	SetSelectionCharFormat(chf);	break;
			case 45: /*SWCF*/	SetWordCharFormat(chf);			break;
			}

			delete[] postmpcc;
		}
		break;

	case 48: /*SPF*/
		{
			char *cf[21]={"NU=","EF=","SI=","RI=","OF=","AL=","TS=","SB=","SA=","LS=","ST=","LR=","OL=","SW=","SS=","NB=","NS=","NT=","BS=","BW=","BO=",};
			PARAFORMAT2 prf;
			prf.cbSize = sizeof(prf);
			prf.dwMask =0;
			prf.wEffects=0;
			const char *pos2;

			int i;
			for(i=0;i<21;i++)
				if ((pos2=strstr(pos,cf[i]))!=NULL)
				{
					pos2+=3;
					switch(i)
					{
					case 0:  /*NU=wNumbering*/
						prf.wNumbering=(WORD)atoi(pos2);
						prf.dwMask|=PFM_NUMBERING;
						break;
					case 1:  /*EF=wEffects*/
						{
							char *cmask="DKNLWBRST",*pos3;
								UINT umask[9]={
								PFM_DONOTHYPHEN,PFM_KEEP,PFM_KEEPNEXT,PFM_NOLINENUMBER,
								PFM_NOWIDOWCONTROL,PFM_PAGEBREAKBEFORE,PFM_RTLPARA,PFM_SIDEBYSIDE,
								PFM_TEXTWRAPPINGBREAK};
								UINT ueff[9]={
								PFE_DONOTHYPHEN,PFE_KEEP,PFE_KEEPNEXT,PFE_NOLINENUMBER,
								PFE_NOWIDOWCONTROL,PFE_PAGEBREAKBEFORE,PFE_RTLPARA,PFE_SIDEBYSIDE,
								PFE_TEXTWRAPPINGBREAK};

							while(*pos2!=0 &&(pos3=strchr(cmask,*pos2))!=NULL)
							{
								prf.wEffects|=ueff[pos3-cmask];
								prf.dwMask|=umask[pos3-cmask];
								pos2++;
							}
						}
						break;
					case 2:  /*SI=dxStartIndent*/
						prf.dxStartIndent=atoi(pos2);
						prf.dwMask|=PFM_STARTINDENT;
						break;
					case 3:  /*RI=dxRightIndent*/
						prf.dxRightIndent=atoi(pos2);
						prf.dwMask|=PFM_RIGHTINDENT ;
						break;
					case 4:  /*OF=dxOffset*/
						prf.dxOffset=atoi(pos2);
						prf.dwMask|=PFM_OFFSET;
						break;
					case 5:  /*AL=wAlignment*/
						prf.wAlignment=(WORD)atoi(pos2);
						prf.dwMask|=PFM_ALIGNMENT;
						break;
					case 6:  /*TS=rgxTabs*//*TC=cTabCount*/
						{
							LONG tbp[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
							m_LastScanf=sscanf(pos2,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",tbp,tbp+1,tbp+2,tbp+3,tbp+4,tbp+5,tbp+6,tbp+7,tbp+8,tbp+9,tbp+10,tbp+11,tbp+12,tbp+13,tbp+14);
							prf.cTabCount=0;
							while(prf.cTabCount<MAX_TAB_STOPS && tbp[prf.cTabCount]>0)
							{
								prf.rgxTabs[prf.cTabCount]=tbp[prf.cTabCount];
								prf.cTabCount++;
								prf.dwMask|=PFM_TABSTOPS;
							}
						}
						break;
					case 7:  /*SB=dySpaceBefore*/
						prf.dySpaceBefore=atoi(pos2);
						prf.dwMask|=PFM_SPACEBEFORE;
						break;
					case 8:  /*SA=dySpaceAfter*/
						prf.dySpaceAfter=atoi(pos2);
						prf.dwMask|=PFM_SPACEAFTER;
						break;
					case 9:  /*LS=dyLineSpacing*/
						prf.dySpaceAfter=atoi(pos2);
						prf.dwMask|=PFM_LINESPACING;
						break;
					case 10: /*ST=sStyle*/
						prf.sStyle=atoi(pos2);
						prf.dwMask|=PFM_STYLE;
						break;
					case 11: /*LR=bLineSpacingRule*/
						prf.bLineSpacingRule=atoi(pos2);
						prf.dwMask|=PFM_SPACEAFTER;
						break;
					case 12: /*OL=bOutlineLevel*/
//						prf.bOutlineLevel=atoi(pos2);
//						prf.dwMask|=0 ;
						break;
					case 13: /*SW=wShadingWeight*/
						prf.wShadingWeight=atoi(pos2);
						prf.dwMask|=PFM_SHADING ;
						break;
					case 14: /*SS=wShadingStyle*/
						prf.wShadingStyle =atoi(pos2);
						prf.dwMask|=PFM_SHADING;
						break;
					case 15: /*NB=wNumberingStart*/
						prf.wNumberingStart=atoi(pos2);
						prf.dwMask|=PFM_NUMBERINGSTART ;
						break;
					case 16: /*NS=wNumberingStyle*/
						prf.wNumberingStyle =atoi(pos2);
						prf.dwMask|=PFM_NUMBERINGSTYLE;
						break;
					case 17: /*NT=wNumberingTab*/
						prf.wNumberingTab=atoi(pos2);
						prf.dwMask|=PFM_NUMBERINGTAB;
						break;
					case 18: /*BS=wBorderSpace*/
						prf.wBorderSpace=atoi(pos2);
						prf.dwMask|=PFM_BORDER;
						break;
					case 19: /*BW=wBorderWidth*/
						prf.wBorderWidth=atoi(pos2);
						prf.dwMask|=PFM_BORDER;
						break;
					case 20: /*BO=wBorders*/
						prf.wBorders=atoi(pos2);
						prf.dwMask|=PFM_BORDER;
						break;

					}
				}
			SetParaFormat(prf);
		}
		break;

	case 50: /*FindText*/
		if (oStr!=NULL)
		{
			char *postmpcc=new char [(int)strlen(pos)+10];
			strcpy(postmpcc,pos);
			FINDTEXTEX ft={0};
			UINT flg=0;
			ft.chrg.cpMin=0;
			ft.chrg.cpMax=-1;
			m_LastScanf=sscanf(postmpcc,"%d,%d",&ft.chrg.cpMin,&ft.chrg.cpMax);
			ft.lpstrText=strchr(postmpcc,';');
			if (ft.lpstrText++!=NULL && *ft.lpstrText!=0)
			{
				if (strstr(postmpcc,"MATCHCASE")!=NULL) flg|=FR_MATCHCASE;
				if (strstr(postmpcc,"WHOLEWORD")!=NULL) flg|=FR_WHOLEWORD;
				FindText(flg,&ft);
			}
			sprintf(oStr,"%d\x7F%d",ft.chrgText.cpMin,ft.chrgText.cpMax);
			delete[] postmpcc;
		}
		break;
	case 51: /*PrintAsText*/
	case 52: /*Print*/
	case 53: /*OpenDefEditorAsText*/
	case 54: /*OpenDefEditor*/
	case 65: /*PrintSelAsText*/
	case 66: /*PrintSel*/
	case 67: /*OpenSelDefEditorAsText*/
	case 68: /*OpenSelDefEditor*/
		{
			SHELLEXECUTEINFO ShExecInfo;
			ShExecInfo.nShow = SW_HIDE ;
			ShExecInfo.lpVerb= "print";
			ShExecInfo.lpFile="tmp.txt";

			switch(nfunc)
			{
			case 51: /*PrintAsText*/
				DoMethod("Save tmp.txt,TEXT",NULL);
				break;
			case 52: /*Print*/
				DoMethod("Save tmp.rtf,",NULL);
				ShExecInfo.lpFile="tmp.rtf";
				break;
			case 53: /*OpenDefEditorAsText*/
				DoMethod("Save tmp.txt,TEXT",NULL);
				ShExecInfo.nShow = SW_MAXIMIZE;
				ShExecInfo.lpVerb= "open";
				break;
			case 54: /*OpenDefEditor*/
				DoMethod("Save tmp.rtf,",NULL);
				ShExecInfo.nShow = SW_MAXIMIZE;
				ShExecInfo.lpVerb= "open";
				ShExecInfo.lpFile="tmp.rtf";
				break;
			case 65: /*PrintSelAsText*/
				DoMethod("SaveSel tmp.txt,TEXT",NULL);
				break;
			case 66: /*PrintSel*/
				DoMethod("SaveSel tmp.rtf,",NULL);
				ShExecInfo.lpFile="tmp.rtf";
				break;
			case 67: /*OpenSelDefEditorAsText*/
				DoMethod("SaveSel tmp.txt,TEXT",NULL);
				ShExecInfo.nShow = SW_MAXIMIZE;
				ShExecInfo.lpVerb= "open";
				break;
			case 68: /*OpenSelDefEditor*/
				DoMethod("SaveSel tmp.rtf,",NULL);
				ShExecInfo.nShow = SW_MAXIMIZE;
				ShExecInfo.lpVerb= "open";
				ShExecInfo.lpFile="tmp.rtf";
				break;
			}

			ShExecInfo.cbSize = sizeof(ShExecInfo);
			ShExecInfo.fMask = SEE_MASK_FLAG_NO_UI;
			ShExecInfo.hwnd = m_hWnd;
			ShExecInfo.lpParameters = NULL;
			ShExecInfo.lpDirectory = NULL;
			ShExecInfo.hInstApp = NULL;
			ShellExecuteEx(&ShExecInfo);
		}
		break;
	case 55: /*SetLineObject*/		LineObjId=atoipos;		break;
	case 56: /*SetColumnObject*/	ColumnObjId=atoipos;	break;
	case 57: /*SetLinePrefix*/		LinePrefix=pos;			break;
	case 58: /*SetColumnPrefix*/	ColumnPrefix=pos;		break;
	case 59: /*SetCharObject*/		CharObjId=atoipos;		break;
	case 60: /*SetCharPrefix*/		CharPrefix=pos;			break;
	case 61: /*SetUndoLimit*/		SendMessage( EM_SETUNDOLIMIT,atoipos,0);	break;
	case 62: /*SetZoom*/
		{
			int chisl=0,znam=0;
			m_LastScanf=sscanf(pos,"%d,%d",&chisl,&znam);
			if (chisl/znam<1/64 || chisl/znam>64) chisl=znam=0;
//			SendMessage(EM_SETZOOM,chisl,znam);
		}
		break;
	case 64: /*GetAllAsText*/
		{
			long nStartChar, nEndChar;
			GetSel(nStartChar,nEndChar );
			SetSel(0,-1);
			DoMethod("GetSelText",oStr);
			SetSel(nStartChar,nEndChar);
		}
		break;
	case 69: /*AutoURLDetect*/		SendMessage(EM_AUTOURLDETECT,atoipos,0);	break;
	case 70: /*CanRedo*/			retint=SendMessage(EM_CANREDO,0,0);			break;
	case 71: /*FindWordBreak*/
		{
			const char *nm[]={"CLASSIFY","ISDELIMITER","LEFT","LEFTBREAK","MOVEWORDLEFT","MOVEWORDRIGHT","RIGHT","RIGHTBREAK",};
			const UINT  ui[]={WB_CLASSIFY,WB_ISDELIMITER,WB_LEFT,WB_LEFTBREAK,WB_MOVEWORDLEFT,WB_MOVEWORDRIGHT,WB_RIGHT,WB_RIGHTBREAK,};
			const char *pss=strchr(pos,',');
			if (pss++==NULL) pss="";
			UINT stl=WB_RIGHT;
			UINT i;
			for(i=0;i<8;i++)
				if (_stricmp(nm[i],pss)==0)	{stl=ui[i];	break;}
			retint=SendMessage(EM_FINDWORDBREAK,stl,atoipos);
		}
		break;
	case 72: /*GetAutoURLDetect*/	retint=SendMessage(EM_GETAUTOURLDETECT,0,0);break;
	case 73: /*GetBiDiOptions*/
	case 74: /*SetBiDiOptions*/
		{
			const char *nmmask[]={"DEFPARADIR","PLAINTEXT","NEUTRALOVERRIDE","CONTEXTREADING","CONTEXTALIGNMENT",};
			const char *nmEff[]={"RTLDIR","PLAINTEXT","NEUTRALOVERRIDE","CONTEXTREADING","CONTEXTALIGNMENT",};
			const UINT  uimask[]={BOM_CONTEXTREADING,BOM_NEUTRALOVERRIDE,BOM_PLAINTEXT,BOM_DEFPARADIR,BOM_CONTEXTALIGNMENT,};
			const UINT  uiEff[]={BOE_RTLDIR,BOE_PLAINTEXT,BOE_NEUTRALOVERRIDE,BOE_CONTEXTREADING,BOE_CONTEXTALIGNMENT,};

			char *postmpcc=new char [(int)strlen(pos)+10];
			strcpy(postmpcc,pos);
			BIDIOPTIONS bidio={0};
			bidio.cbSize=sizeof(bidio);

			if (nfunc==74)
			{/*SetBiDiOptions*/
				char *pss=strchr(postmpcc,',');
				if (pss==NULL) pss="";
				else *(pss++)=0;

				UINT i;
				for(i=0;i<5;i++)
				{
					if (strstr(pos,nmmask[i])!=NULL)	bidio.wMask|=uimask[i];
					if (strstr(pos,nmEff[i])!=NULL)	bidio.wEffects|=uiEff[i];
				}
				SendMessage(EM_SETBIDIOPTIONS,0,(LPARAM)&bidio);
			}
			else
				if (oStr!=NULL)
				{
					SendMessage(EM_GETBIDIOPTIONS,0,(LPARAM)&bidio);
					UINT i;
					for(i=0;i<5;i++)
						if ((bidio.wEffects&uiEff[i])==uiEff[i]) {strcat(oStr,nmEff[i]);strcat(oStr,"|");}
				}
			delete[] postmpcc;
		}
		break;
	case 75: /*GetEditStyle*/
	case 76: /*SetEditStyle*/
		{
			const char *nmopt[]=
			{
				"EMULATESYSEDIT","BEEPONMAXTEXT","EXTENDBACKCOLOR","MAPCPS","EMULATE10",
				"USECRLF","USEAIMM","NOIME","ALLOWBEEPS","UPPERCASE",
				"LOWERCASE","NOINPUTSEQUENCECHK","BIDI","SCROLLONKILLFOCUS","XLTCRCRLFTOCR",
				"DRAFTMODE","USECTF","HIDEGRIDLINES","USEATFONT","CUSTOMLOOK",
				"LBSCROLLNOTIFY","CTFALLOWEMBED","CTFALLOWSMARTTAG","CTFALLOWPROOFING",
			};
			const UINT  uiopt[]=
			{
				SES_EMULATESYSEDIT,SES_BEEPONMAXTEXT,SES_EXTENDBACKCOLOR,SES_MAPCPS,SES_EMULATE10,
				SES_USECRLF,SES_USEAIMM,SES_NOIME,SES_ALLOWBEEPS,SES_UPPERCASE,
				SES_LOWERCASE,SES_NOINPUTSEQUENCECHK,SES_BIDI,SES_SCROLLONKILLFOCUS,SES_XLTCRCRLFTOCR,
				SES_DRAFTMODE,SES_USECTF,SES_HIDEGRIDLINES,SES_USEATFONT,SES_CUSTOMLOOK,
				SES_LBSCROLLNOTIFY,SES_CTFALLOWEMBED,SES_CTFALLOWSMARTTAG,SES_CTFALLOWPROOFING,
			};

			if (nfunc==76)
			{/*SetEditStyle*/
				UINT stl=0;

				UINT i;
				for(i=0;i<24;i++)
					if (strstr(pos,nmopt[i])!=NULL)	stl|=uiopt[i];

				SendMessage(EM_SETEDITSTYLE,stl,stl);
			}
			else/*GetEditStyle*/
				if (oStr!=NULL)
				{
					retint=SendMessage(EM_GETEDITSTYLE,0,0);
					UINT i;
					for(i=0;i<24;i++)
						if ((retint&uiopt[i])==uiopt[i]) {strcat(oStr,nmopt[i]);strcat(oStr,"|");}
				}
		}
		break;
	case 77: /*GetLangOptions*/
	case 78: /*SetLangOptions*/
		{
			const char *nmopt[]={"AUTOFONT","AUTOFONTSIZEADJUST","AUTOKEYBOARD","DUALFONT","IMEALWAYSSENDNOTIFY","IMECANCELCOMPLETE","UIFONTS",};
			const UINT  uiopt[]={IMF_AUTOFONT,IMF_AUTOFONTSIZEADJUST,IMF_AUTOKEYBOARD,IMF_DUALFONT,IMF_IMEALWAYSSENDNOTIFY,IMF_IMECANCELCOMPLETE,IMF_UIFONTS,};

			if (nfunc==78)
			{/*SetLangOptions*/
				UINT stl=0;

				UINT i;
				for(i=0;i<7;i++)
					if (strstr(pos,nmopt[i])!=NULL)	stl|=uiopt[i];

				SendMessage(EM_SETLANGOPTIONS,stl,stl);
			}
			else/*GetLangOptions*/
				if (oStr!=NULL)
				{
					retint=SendMessage(EM_GETLANGOPTIONS,0,0);
					UINT i;
					for(i=0;i<7;i++)
						if ((retint&uiopt[i])==uiopt[i]) {strcat(oStr,nmopt[i]);strcat(oStr,"|");}
				}
		}
		break;
	case 79: /*GetRedoName*/
	case 85: /*GetUndoName*/
		if (oStr!=NULL)
		{
			const char *nmopt[]={"UNKNOWN","TYPING","DELETE","DRAGDROP","CUT","PASTE","",};
			retint=SendMessage(nfunc==79?EM_GETREDONAME:EM_GETUNDONAME,0,0);
			strcpy(oStr,nmopt[retint]);
		}
		break;
	case 80: /*GetScrollPos*/
		if (oStr!=NULL)
		{
			POINT po;
			SendMessage(EM_GETSCROLLPOS,0,(LPARAM)&po);
			sprintf(oStr,"%d\x7F%d",po.x,po.y);
		}
		break;
	case 81: /*GetTextMode*/
	case 82: /*SetTextMode*/
		{
			const char *nmopt[]={"PLAINTEXT","RICHTEXT","SINGLELEVELUNDO","MULTILEVELUNDO","SINGLECODEPAGE","MULTICODEPAGE",};
			const UINT  uiopt[]={TM_PLAINTEXT,TM_RICHTEXT,TM_SINGLELEVELUNDO,TM_MULTILEVELUNDO,TM_SINGLECODEPAGE,TM_MULTICODEPAGE,};

			if (nfunc==82)
			{/*SetTextMode*/
				UINT stl=0;

				UINT i;
				for(i=0;i<6;i++)
					if (strstr(pos,nmopt[i])!=NULL)	stl|=uiopt[i];

				retint=SendMessage(EM_SETTEXTMODE,stl,0);
			}
			else/*GetTextMode*/
				if (oStr)
				{
					retint=SendMessage(EM_GETTEXTMODE,0,0);
					UINT i;
					for(i=0;i<6;i++)
						if ((retint&uiopt[i])==uiopt[i]) {strcat(oStr,nmopt[i]);strcat(oStr,"|");}
				}
		}
		break;
	case 83: /*GetTipogrphyOptions*/
		retint=SendMessage(EM_GETTYPOGRAPHYOPTIONS,0,0);
		break;
	case 84: /*SetTipogrphyOptions*/
		retint=SendMessage(EM_SETTYPOGRAPHYOPTIONS,atoipos,0);
		break;
	case 86: /*GetZoom*/
		{
			long den=0,num=0;
			retint=SendMessage(EM_GETZOOM,(UINT)&den,(UINT)&num);
			sprintf(oStr,"%d\x7F%d",den,num);
		}
		break;
	case 87: /*Reconversion*/
		retint=SendMessage(EM_RECONVERSION,atoipos,0);
		break;
	case 88: /*Redo*/			retint=SendMessage(EM_REDO,0,0);	break;
	case 89: /*RequestResize*/	SendMessage(EM_REQUESTRESIZE,0,0);	break;
	case 90: /*SetFontSize*/
		SendMessage(EM_SETFONTSIZE,atoipos,0);	break;
		break;
	case 91: /*SetScrollPos*/
		{
			POINT po;
			m_LastScanf=sscanf(pos,"%d,%d",&po.x,&po.y);
			SendMessage(EM_SETSCROLLPOS,0,(LPARAM)&po);
		}
		break;
	case 92: /*SetTabSeq*/		m_TabReplaser=pos;		break;
	case 93: /*GetTabSeq*/
		if (oStr!=NULL)
			strcpy(oStr,m_TabReplaser);
		break;
	case 94: /*SetIndent*/		m_Indent=atoipos;		break;
	case 95: /*GetIndent*/		retint=m_Indent;		break;
	case 96: /*PosFromChar*/
		if (oStr!=NULL)
		{
			POINTL mPOINTL={0};
			SendMessage(EM_POSFROMCHAR, (WPARAM) &mPOINTL, (LPARAM) atoipos);
			sprintf(oStr,"%d\x7%d",mPOINTL.x,mPOINTL.y);
		}
		break;

	case 97: /*CharFromPos*/
		if (oStr!=NULL)
		{
			POINTL pol={0};
			m_LastScanf=sscanf(pos,"%d,%d",&pol.x,&pol.y);
			long nchar = SendMessage(EM_CHARFROMPOS,0,(LPARAM)&pol);
			long nline = SendMessage(EM_LINEFROMCHAR,nchar,0);
			long ncharINline = SendMessage(EM_LINEINDEX,nline,0);
			sprintf(oStr,"%d\x7F%d\x7F%d",nchar,nline,ncharINline);
		}
		break;
	case 98: /*ScrollCaret*/
			retint = SendMessage(EM_SCROLLCARET,0,0);
		break;
	case 99: /*DisplayBand*/
		{
			RECT re={0};
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&re.left,&re.top,&re.right,&re.bottom);
			retint = SendMessage(EM_DISPLAYBAND,0,(LPARAM)&re);
		}
		break;
	case 100: /*SetEventMask*/
	case 101: /*GetEventMask*/
		{
			const static char *cEventMask[]={
				"_CHANGE|","_UPDATE|","_SCROLL|","_SCROLLEVENTS|","_DRAGDROPDONE|",
				"_PARAGRAPHEXPANDED|","_PAGECHANGE|","_KEYEVENTS|","_MOUSEEVENTS|","_REQUESTRESIZE|",
				"_SELCHANGE|","_DROPFILES|","_PROTECTED|","_CORRECTTEXT|","_IMECHANGE|",
				"_LANGCHANGE|","_OBJECTPOSITIONS|","_LINK|","_LOWFIRTF|",
				};
			const static UINT uEventMask[]={
				ENM_CHANGE,ENM_UPDATE,ENM_SCROLL,ENM_SCROLLEVENTS,ENM_DRAGDROPDONE,
				ENM_PARAGRAPHEXPANDED,ENM_PAGECHANGE,ENM_KEYEVENTS,ENM_MOUSEEVENTS,ENM_REQUESTRESIZE,
				ENM_SELCHANGE,ENM_DROPFILES,ENM_PROTECTED,ENM_CORRECTTEXT,ENM_IMECHANGE,
				ENM_LANGCHANGE,ENM_OBJECTPOSITIONS,ENM_LINK,ENM_LOWFIRTF,
				};

			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
			_strupr(pos333);
			UINT uEvntMask=0;
			if (nfunc==101)/*GetEventMask*/
				uEvntMask=SendMessage(EM_GETEVENTMASK,0,0);

			if (nfunc==100)/*SetEventMask*/
			{
				UINT i;
				for(i=0;i<19;i++)
					if (strstr(pos333,cEventMask[i])) uEvntMask|=uEventMask[i];
				uEvntMask = SendMessage(EM_SETEVENTMASK,0,(LPARAM)uEvntMask);
			}

			if (oStr)/*GetEventMask SetEventMask*/
			{
				UINT i;
				for(i=0;i<19;i++)
					if ((uEventMask[i]&uEvntMask)==uEventMask[i])
						strcat(oStr,cEventMask[i]);
			}
			delete[] pos333;
		}
		break;
	case 102: /*GetTextRange cMin,cMax*/
		if (oStr)
		{
			TEXTRANGE tr={0};
			m_LastScanf=sscanf(pos,"%d,%d",&tr.chrg.cpMin,&tr.chrg.cpMax);
			tr.lpstrText= oStr;
			if (tr.chrg.cpMax-tr.chrg.cpMin>TMP_STR_OUT_LEN)
				tr.chrg.cpMax=tr.chrg.cpMin+TMP_STR_OUT_LEN;
			SendMessage(EM_GETTEXTRANGE,0,(LPARAM)&tr);
		}
		break;
	case 103: /*ShowVScrollBar bShow*/
	case 104: /*ShowHScrollBar bShow*/
			SendMessage(EM_SHOWSCROLLBAR,nfunc==103?SB_VERT:SB_HORZ,(LPARAM)atoipos);
		break;
	case 105: /*OutLine lparam,Option*/
		{
			const static char *cOptions[]={
				"_EXIT","_ENTER","_PROMOTE","_PROMOTE","_MOVESELECTION","_GETVIEWMODE",
				"_EXPAND",
				};
			const static UINT uOptionsWp[]={
				EMO_EXIT,EMO_ENTER,EMO_PROMOTE,EMO_MOVESELECTION,EMO_GETVIEWMODE,
				EMO_EXPAND,0,
				};

			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);

			_strupr(pos333);

			UINT i;
			for(i=0;i<6 && strstr(pos333,cOptions[i])==NULL;i++);
			retint = SendMessage(EM_OUTLINE,uOptionsWp[i],(LPARAM)atoipos);
			delete[] pos333;
		}
		break;

	case 106: /*TrimEndSpace*/
		{
			long nStartChar, nEndChar;
			long nStartChar2, nEndChar2;
			GetSel(nStartChar,nEndChar );
			SetSel(0,-1);
			GetSel(nStartChar2,nEndChar2);
			CString csStr=GetSelText();
			int tmplen=csStr.GetLength();
			char *str=new char [tmplen+100];
			if (tmplen>=0)
			{
				strcpy(str,csStr);
				char *poss=str;
				char *posd=str;
				char *postmp=NULL;

				while(*posd!=0)
				{
					if (*poss==' ' || *poss==9)
					{
						if (postmp==NULL) postmp=posd;
					}
					else
						if ((*poss==10 || *poss==13 || *poss==0) && postmp)
						{
							if (poss<str+nStartChar)
							{
								nStartChar-=(posd-postmp);
								nEndChar-=(posd-postmp);
							}
							else
							if (poss<str+nStartChar)
								nEndChar-=(posd-postmp);

							posd=postmp;
						}
						else
							postmp=NULL;

					*(posd++)=*(poss++);
				}
				ReplaceSel(str,TRUE);
			}
			SetSel(nStartChar,nEndChar);
			delete[] str;
		}
		break;
	case 107: /*SetVP*/
		{
			long nStart=0,nEnd=0;
			GetSel(nStart,nEnd);
			SetSel(0,0);
			SetSel(nStart,nEnd);
		}
		break;
	case 108: /*SetAutoWidth*/
		{
			AutoWidthMin=0;AutoWidthMax=0;AutoWidthDelta=0;
			m_LastScanf=sscanf(pos,"%d,%d,%d",&AutoWidthMin,&AutoWidthMax,&AutoWidthDelta);
			OnChangeVP();
		}
		break;
	case 109: /*SetImeStatus*/
	case 110: /*GetImeStatus*/
		{
			char *cArrIn[]={"GET","CAN","COMPL",};
			char *cArr[]={"GETCOMPSTRATONCE","CANCELCOMPSTRINFOCUS","COMPLETECOMPSTRKILLFOCUS",};
			UINT uArr[]={EIMES_GETCOMPSTRATONCE,EIMES_CANCELCOMPSTRINFOCUS,EIMES_COMPLETECOMPSTRKILLFOCUS,};
			UINT nArr=3;
			UINT i;
			DWORD ret=0;

			switch(nfunc)
			{
			case 109: /*SetImeStatus*/
				{
					DWORD uNew=0;
					for(i=0;i<nArr;i++)
						if (strstr(pos,cArrIn[i])) uNew|=uArr[i];

					ret=SendMessage(EM_SETIMESTATUS,EMSIS_COMPOSITIONSTRING,(LPARAM)uNew);
				}
				if (oStr==NULL) break;

			case 110: /*GetImeStatus*/
				if (oStr)
				{
					if (nfunc==110)	ret=SendMessage(EM_GETIMESTATUS,EMSIS_COMPOSITIONSTRING,0);
					for(i=0;i<nArr;i++)
						if ((ret&uArr[i])==uArr[i])
						{
							if (*oStr) strcat(oStr,"|");
							strcat(oStr,cArr[i]);
						}
				}
				break;
			}
		}
		break;
	case 111: /*SetCueBanner*/
		{
			CString tmps=pos;
			BSTR tmpbstr=tmps.AllocSysString();
			retint=SendMessage(EM_SETCUEBANNER,0,(LPARAM)(LPCWSTR)tmpbstr);
			::SysFreeString(tmpbstr);
		}
		break;
	case 112: /*GetCueBanner*/
		if (oStr)
		{
			BSTR tmpbstr=NULL;
			retint=SendMessage(EM_GETCUEBANNER,0,(LPARAM)(LPCWSTR)tmpbstr);
			CString tmps(tmpbstr);
			strcpy(oStr,tmps);
			::SysFreeString(tmpbstr);
		}
		break;
	case 113: /*ShowBalloonTip*/
		{
			const char *pos2=strchr(pos,',');
			retint=0;
			if (pos2)
			{
				UINT uArr[]={TTI_NONE,TTI_INFO,TTI_WARNING,TTI_ERROR,};
				EDITBALLOONTIP ebt={0};
				ebt.cbStruct=sizeof(ebt);

				ebt.ttiIcon=uArr[atoipos%4];
				BSTR pszTitle;
				BSTR pszText;
				CString tmp=ExtractField(pos2,1,GPC.csDelimiterIn1);
				ebt.pszTitle=pszTitle=tmp.AllocSysString();
				tmp=ExtractField(pos2,2,GPC.csDelimiterIn1);
				ebt.pszText=pszText=tmp.AllocSysString();
				retint=SendMessage(EM_SHOWBALLOONTIP,0,(LPARAM)&ebt);
				::SysFreeString(pszText);
				::SysFreeString(pszTitle);
			}
		}
		break;
	case 114: /*HideBalloonTip*/
		retint=SendMessage(EM_HIDEBALLOONTIP,0,0);
		break;
	case 115: /*StopGroupTyping*/
		retint=SendMessage(EM_STOPGROUPTYPING,0,0);
		break;

	case 46: /*GDCF*/
	case 47: /*GSCF*/
	case 49: /*GPF*/
	case 17: /*PasteSpecial*/
	default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);

/*
WM_CONTEXTMENU			0x007B
WM_UNICHAR				0x0109
WM_PRINTCLIENT			0x0318
EM_FORMATRANGE			(WM_USER + 57)
EM_GETCHARFORMAT		(WM_USER + 58)
EM_GETOLEINTERFACE		(WM_USER + 60)
EM_GETPARAFORMAT		(WM_USER + 61)
EM_PASTESPECIAL			(WM_USER + 64)
EM_SETBKGNDCOLOR		(WM_USER + 67)
EM_SETCHARFORMAT		(WM_USER + 68)
EM_SETPARAFORMAT		(WM_USER + 71)
EM_SETTARGETDEVICE		(WM_USER + 72)
EM_STREAMIN				(WM_USER + 73)
EM_STREAMOUT			(WM_USER + 74)
EM_SETPALETTE			(WM_USER + 93)
EM_GETTEXTEX			(WM_USER + 94)
EM_GETTEXTLENGTHEX		(WM_USER + 95)
EM_SETTEXTEX			(WM_USER + 97)
EM_GETVIEWKIND			(WM_USER + 226)
EM_SETVIEWKIND			(WM_USER + 227)
EM_GETPAGE				(WM_USER + 228)
EM_SETPAGE				(WM_USER + 229)
EM_GETHYPHENATEINFO		(WM_USER + 230)
EM_SETHYPHENATEINFO		(WM_USER + 231)
EM_GETPAGEROTATE		(WM_USER + 235)
EM_SETPAGEROTATE		(WM_USER + 236)
EM_GETCTFMODEBIAS		(WM_USER + 237)
EM_SETCTFMODEBIAS		(WM_USER + 238)
EM_GETCTFOPENSTATUS		(WM_USER + 240)
EM_SETCTFOPENSTATUS		(WM_USER + 241)
EM_GETIMECOMPTEXT		(WM_USER + 242)
EM_ISIME				(WM_USER + 243)
EM_GETIMEPROPERTY		(WM_USER + 244)




// EM_SETPAGEROTATE wparam values
#define EPR_0					0		// Text flows left to right and top to bottom
#define EPR_270					1		// Text flows top to bottom and right to left
#define EPR_180					2		// Text flows right to left and bottom to top
#define	EPR_90					3		// Text flows bottom to top and left to right

// EM_SETCTFMODEBIAS wparam values
#define CTFMODEBIAS_DEFAULT					0x0000
#define CTFMODEBIAS_FILENAME				0x0001
#define CTFMODEBIAS_NAME					0x0002
#define CTFMODEBIAS_READING					0x0003
#define CTFMODEBIAS_DATETIME				0x0004
#define CTFMODEBIAS_CONVERSATION			0x0005
#define CTFMODEBIAS_NUMERIC					0x0006
#define CTFMODEBIAS_HIRAGANA				0x0007
#define CTFMODEBIAS_KATAKANA				0x0008
#define CTFMODEBIAS_HANGUL					0x0009
#define CTFMODEBIAS_HALFWIDTHKATAKANA		0x000A
#define CTFMODEBIAS_FULLWIDTHALPHANUMERIC	0x000B
#define CTFMODEBIAS_HALFWIDTHALPHANUMERIC	0x000C

// EM_SETIMEMODEBIAS lparam values
#define IMF_SMODE_PLAURALCLAUSE	0x0001
#define IMF_SMODE_NONE			0x0002

// EM_GETIMECOMPTEXT wparam structure
typedef struct _imecomptext {
	LONG	cb;			// count of bytes in the output buffer.
	DWORD	flags;		// value specifying the composition string type.
						//	Currently only support ICT_RESULTREADSTR
} IMECOMPTEXT;
#define ICT_RESULTREADSTR		1

// Outline mode wparam values
#define EMO_EXIT                0       // Enter normal mode,  lparam ignored
#define EMO_ENTER               1       // Enter outline mode, lparam ignored
#define EMO_PROMOTE             2       // LOWORD(lparam) == 0 ==>
                                        //  promote  to body-text
                                        // LOWORD(lparam) != 0 ==>
                                        //  promote/demote current selection
                                        //  by indicated number of levels
#define EMO_EXPAND              3       // HIWORD(lparam) = EMO_EXPANDSELECTION
                                        //  -> expands selection to level
                                        //  indicated in LOWORD(lparam)
                                        //  LOWORD(lparam) = -1/+1 corresponds
                                        //  to collapse/expand button presses
                                        //  in winword (other values are
                                        //  equivalent to having pressed these
                                        //  buttons more than once)
                                        //  HIWORD(lparam) = EMO_EXPANDDOCUMENT
                                        //  -> expands whole document to
                                        //  indicated level
#define EMO_MOVESELECTION       4       // LOWORD(lparam) != 0 -> move current
                                        //  selection up/down by indicated amount
#define EMO_GETVIEWMODE			5		// Returns VM_NORMAL or VM_OUTLINE

// EMO_EXPAND options
#define EMO_EXPANDSELECTION     0
#define EMO_EXPANDDOCUMENT      1

#define VM_NORMAL				4		// Agrees with RTF \viewkindN
#define VM_OUTLINE				2
#define VM_PAGE					9		// Screen page view (not print layout)







*/



	return nfunc;
}

UINT GP_RTF::GPSetProperty(char *iStr)
{
	char *iValue=new char [(int)strlen(iStr)+5];
	strcpy(iValue,iStr);
	UINT ret=1,i;
	char *pos=strchr(iValue,'=');

	if (pos!=NULL && m_hWnd)
	{
		const static char *prop[]={ "TEXT", "ADDSTYLE", "DELSTYLE","STYLE",};
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
				if (m_hWnd!=NULL)
				{
					char *tmp=new char [(int)strlen(pos)+100];
					sprintf(tmp,"ReplaceSel %s",pos);
					SetSel(0,-1);
					DoMethod(tmp,NULL);
					delete[] tmp;
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
					// GPListCtr specif
					for(i=0;i<N_RTF_STYLES;i++)
						if (strstr(pos,aRTFStyleName[i])!=NULL)
						{
							InvFlg++;
							switch(propnum)
							{
							case 3: /* STYLE*/
							case 1: /* ADDSTYLE*/	ModifyStyle(0,aRTFStyleUINT[i]);break;
							case 2: /* DELSTYLE*/	ModifyStyle(aRTFStyleUINT[i],0);break;
							}
						}

					UINT es=GetExStyle();
					UINT oldstyle=es;
					if (propnum==2) es=0;
					char *postmp=strstr(pos,"&X");
					if (postmp!=NULL)
					{
						UINT tmpstl=0;
						m_LastScanf=sscanf(postmp,"&X%X",&tmpstl);
						InvFlg++;
						switch(propnum)
						{
						case 3: /* STYLE*/
						case 1: /* ADDSTYLE*/	es|=tmpstl;	break;
						case 2: /* DELSTYLE*/	es=((es|tmpstl)^tmpstl);break;
						}
					}
					else
					for(i=0;i<N_RTF_EX_STYLES;i++)
						if (strstr(pos,aRTFExStyleName[i])!=NULL)
						{
							InvFlg++;
							switch(propnum)
							{
							case 3: /* STYLE*/
							case 1: /* ADDSTYLE*/	es|=aRTFExStyleUINT[i];	break;
							case 2: /* DELSTYLE*/	es=((es|aRTFExStyleUINT[i])^aRTFExStyleUINT[i]);break;
							}
						}

					if (oldstyle!=es) ModifyStyleEx(oldstyle&(0xFFFFFFFF^es),es);
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

void GP_RTF::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CRichEditCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
	SetLineColPositionText();
	if ((nChar==VK_DELETE || nChar==VK_BACK) && AutoWidthMin!=0 && AutoWidthMax>AutoWidthMin && AutoWidthDelta>0)
		m_uCurVP=-1;
	OnChangeVP();
}

void GP_RTF::SetLineColPositionText()
{
	long nStartChar,nEndChar;
	GetSel(nStartChar,nEndChar);
	if (nStartChar!=lastSelPos || lastSelPos!=nEndChar)
	{
		lastSelPos=nStartChar;
		char str[100];
		if (LineObjId>=0 && LineObjId<(*referGPU)->m_NGPUNIT && referGPU[LineObjId]!=NULL)
		{
			if (nStartChar==nEndChar)
				sprintf(str,"TEXT=%s%d",(LPCSTR)LinePrefix,LineFromChar(nStartChar)+1);
			else
				sprintf(str,"TEXT=%s%d - %d",(LPCSTR)LinePrefix,LineFromChar(nStartChar)+1,LineFromChar(nEndChar)+1);
			referGPU[LineObjId]->GPSetProperty(str);

		}
		if (ColumnObjId>=0 && ColumnObjId<(*referGPU)->m_NGPUNIT && referGPU[ColumnObjId]!=NULL)
		{
			if (nStartChar==nEndChar)
				sprintf(str,"TEXT=%s%d",(LPCSTR)ColumnPrefix,nStartChar-LineIndex(LineFromChar(nStartChar))+1);
			else
				sprintf(str,"TEXT=%s%d - %d",(LPCSTR)ColumnPrefix,nStartChar-LineIndex(LineFromChar(nStartChar))+1,nEndChar-LineIndex(LineFromChar(nEndChar))+1);
			referGPU[ColumnObjId]->GPSetProperty(str);
		}
		if (CharObjId>=0 && CharObjId<(*referGPU)->m_NGPUNIT && referGPU[CharObjId]!=NULL)
		{
			int nCol=nStartChar-LineIndex(LineFromChar(nStartChar));
			char *tmp=new char [nCol+20];
			GetLine(LineFromChar(nStartChar),tmp,nCol+10);

			sprintf(str,"TEXT=%s%d",(LPCSTR)CharPrefix,tmp[nCol]);
			delete[] tmp;
			referGPU[CharObjId]->GPSetProperty(str);
		}
	}
}

void GP_RTF::OnRButtonDown(UINT nFlags, CPoint point)
{
	CRichEditCtrl::OnRButtonDown(nFlags, point);
	SetLineColPositionText();
	m_bTrackMousePos=TRUE;
	OnChangeVP();
}


void GP_RTF::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRichEditCtrl::OnLButtonDown(nFlags, point);
	SetLineColPositionText();
	m_bTrackMousePos=TRUE;
	OnChangeVP();
}

void GP_RTF::OnRButtonUp(UINT nFlags, CPoint point)
{
	CRichEditCtrl::OnRButtonUp(nFlags, point);
	SetLineColPositionText();
	m_bTrackMousePos=FALSE;
	OnChangeVP();
}

void GP_RTF::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRichEditCtrl::OnLButtonUp(nFlags, point);
	SetLineColPositionText();
	m_bTrackMousePos=FALSE;
	OnChangeVP();
}

void GP_RTF::OnMouseMove(UINT nFlags, CPoint point)
{
	CRichEditCtrl::OnMouseMove(nFlags, point);
	if (m_bTrackMousePos==TRUE)	SetLineColPositionText();
}

void GP_RTF::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar==9)//TAB
	{
		ReplaceSel(m_TabReplaser,TRUE);
	}
	else
	CRichEditCtrl::OnChar(nChar, nRepCnt, nFlags);

	if (nChar==13 && m_Indent!=0)//ENTER
	{
		long Start,end;
		GetSel(Start,end);
		long nextch=Start;
		if (SendMessage(EM_FINDWORDBREAK,WB_ISDELIMITER,Start))
			nextch=SendMessage(EM_FINDWORDBREAK,WB_RIGHT,Start);
		long CurLine=LineFromChar(Start);
		long prevLineIndex=LineIndex(CurLine-1);
		long prevLineCh=prevLineIndex;
		if (SendMessage(EM_FINDWORDBREAK,WB_ISDELIMITER,prevLineIndex))
			prevLineCh=SendMessage(EM_FINDWORDBREAK,WB_RIGHT,prevLineIndex);
		SetSel(Start,nextch);
		long sellen=prevLineCh-prevLineIndex;
		char *str=new char [sellen+100];
		long i;
		for(i=0;i<sellen;i++) str[i]=' ';
		str[i]=0;
		ReplaceSel(str,TRUE);
		delete[] str;
	}

	if (nChar==127)	ReplaceSel("\x7F",TRUE);
	else
	if (nChar==7)	ReplaceSel("\x07",TRUE);
	SetLineColPositionText();
	OnChangeVP();
}

void GP_RTF::OnSizing(UINT fwSide, LPRECT pRect)
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

	if (EnableSz) CRichEditCtrl::OnSizing(fwSide, pRect);

	GetParent()->SendMessage(GPN_UPDATESIZE);
	OnChangeVP();
}

void GP_RTF::OnDragMouseHover()
{
	if (referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(GPC.m_DragDrop.DragName)<0xFFFFFFFFL)
	{
		// Reset the timer.
		SetTimer(DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nScrollInterval, NULL);

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
			int nFirstVisibleLine = GetFirstVisibleLine();
			GPC.m_DragDrop.pImageList->DragShowNolock(FALSE);
			SendMessage(WM_VSCROLL, MAKEWPARAM(SB_LINEUP, 0), NULL);
			GPC.m_DragDrop.pImageList->DragShowNolock(TRUE);

			// Kill the timer if the window did not scroll, or redraw the drop target highlight if the window did scroll.
			if (GetFirstVisibleLine() == nFirstVisibleLine)
				::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);
			else
				HighlightDropTarget(&GPC.m_DragDrop, point);
		}
		else
			if (point.y >= cy - referGPU[UnitId&0xFFFF]->m_nScrollMargin && point.y <= cy)
			{
				int nFirstVisibleLine = GetFirstVisibleLine();
				GPC.m_DragDrop.pImageList->DragShowNolock(FALSE);
				SendMessage(WM_VSCROLL, MAKEWPARAM(SB_LINEDOWN, 0), NULL);
				GPC.m_DragDrop.pImageList->DragShowNolock(TRUE);

				// Kill the timer if the window did not scroll, or redraw the drop target highlight if the window did scroll.
				if (GetFirstVisibleLine() == nFirstVisibleLine) ::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);
				else
					HighlightDropTarget(&GPC.m_DragDrop, point);
			}
			else  ::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);

		CString tmps;
		POINTL pol;
		pol.x=point.x;
		pol.y=point.y;
		long nchar = SendMessage(EM_CHARFROMPOS,0,(LPARAM)&pol);
		long nline = SendMessage(EM_LINEFROMCHAR,nchar,0);
		long ncharINline = SendMessage(EM_LINEINDEX,nline,0);
		tmps.Format("%d\x07%d\x07%d",nchar,nline,ncharINline);
		referGPU[UnitId&0xFFFF]->SendDropHoverEvent(tmps,&GPC.m_DragDrop,&point);
	}
}

void GP_RTF::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
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

		DWORD dwHighlightItem=-1;
		BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
		// Highlight the drop target if the cursor is over an item.
		if (mDrop)
			dwHighlightItem = HighlightDropTarget(pDrDrStruct, CPoint(*point));
		// Modify the cursor to provide visual feedback to the user. Note: It's important to do this AFTER the call to DragMove.
		::SetCursor(dwHighlightItem == -1 ?
			AfxGetApp()->LoadStandardCursor(IDC_NO) :
			(HCURSOR) ::GetClassLong(m_hWnd, GCL_HCURSOR));

		CString tmps;
		POINTL pol;
		pol.x=point->x;
		pol.y=point->y;
		long nchar = SendMessage(EM_CHARFROMPOS,0,(LPARAM)&pol);
		long nline = SendMessage(EM_LINEFROMCHAR,nchar,0);
		long ncharINline = SendMessage(EM_LINEINDEX,nline,0);
		tmps.Format("%d\x07%d\x07%d",nchar,nline,ncharINline);
		referGPU[UnitId&0xFFFF]->SendDropMoveEvent(tmps,pDrDrStruct,point);

		if (mDrop)
			::SetTimer(pDrDrStruct->hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nDelayInterval, NULL);
	}
}

void GP_RTF::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && referGPU)
	{
		::ScreenToClient(m_hWnd,point);
		CString tmp;
		POINTL pol;
		pol.x=point->x;
		pol.y=point->y;
		long nchar = SendMessage(EM_CHARFROMPOS,0,(LPARAM)&pol);
		long nline = SendMessage(EM_LINEFROMCHAR,nchar,0);
		long ncharINline = SendMessage(EM_LINEINDEX,nline,0);
		tmp.Format("%d\x07%d\x07%d",nchar,nline,ncharINline);
		referGPU[UnitId&0xFFFF]->SendDropEvent(tmp,pDrDrStruct,point);
	}
}

DWORD GP_RTF::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	return 0;
}

LRESULT GP_RTF::OnNcHitTest(CPoint point)
{
	LRESULT ret=CRichEditCtrl::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

void GP_RTF::OnChangeVP()
{
	UINT curVP=GetFirstVisibleLine();
	if (curVP!=m_uCurVP)
	{
		char str[2000];
		CString tmpstr;
		m_uCurVP=curVP;

		CRect re,reFmt;
		GetWindowRect(&re);
		GetRect(&reFmt);
		GetParent()->ScreenToClient(&re);
		CSize mSize(0,0);
		CDC *mdc=NULL;
		int nchars=GetLine(0,str,1500);
		if (nchars)
			if((mdc=GetDC()))
			{
				if (nchars)
				{
					mSize=mdc->GetTextExtent(str,nchars);
					if (m_uCurVP>0 && m_uCurVP<(UINT)nchars)
					{
						CSize mSize2(0,0);
						mSize2=mdc->GetTextExtent(str+m_uCurVP,nchars-m_uCurVP);
						if (AutoWidthMin!=0 && AutoWidthMax>AutoWidthMin && AutoWidthDelta>0)
							if (mSize2.cx+AutoWidthDelta<(UINT)reFmt.Width())
							{
								m_uCurVP--;
								DoMethod("SetVP 0",NULL);
								long nStart=0,nEnd=0;
								GetSel(nStart,nEnd);
								SetSel(m_uCurVP,m_uCurVP);
								SetSel(nStart,nEnd);
							}
					}
				}
				ReleaseDC(mdc);
			}

		BOOL bSend=TRUE;
		if (AutoWidthMin!=0 && AutoWidthMax>AutoWidthMin && AutoWidthDelta>0)
		{
			if (mSize.cx>reFmt.Width())
			{
				if ((UINT)re.Width()<AutoWidthMax)
				{
					int tmpdelta=mSize.cx-reFmt.Width();
					if ((UINT)tmpdelta<AutoWidthDelta) tmpdelta=AutoWidthDelta;
					re.right+=mSize.cx-reFmt.Width();
					if ((UINT)re.Width()>AutoWidthMax) re.right=re.left+AutoWidthMax;
					bSend=FALSE;
					MoveWindow(&re);
					DoMethod("SetVP 0",NULL);
				}
			}
			else
			{
				if (mSize.cx+AutoWidthDelta<(UINT)reFmt.Width()) re.right-=AutoWidthDelta;
				if ((UINT)re.Width()<AutoWidthMin) re.right=re.left+AutoWidthMin;
				bSend=FALSE;
				MoveWindow(&re);
				DoMethod("SetVP 0",NULL);
			}
		}

		if (bSend)
		{
			tmpstr.Format("%d\x7F%d\x7F%d\x7%d\x7%d\x7%d\x7F%d\x7%d",m_uCurVP,nchars,re.left,re.top,re.right,re.bottom,mSize.cx,mSize.cy);
			if (referGPU && referGPU[UnitId&0xFFFF])
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnChangeVP",tmpstr);
		}
	}
}

#include "GP_TermDoc.h"

void GP_RTF::OnKillFocus(CWnd* pNewWnd)
{
	CRichEditCtrl::OnKillFocus(pNewWnd);
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

void GP_RTF::OnSetFocus(CWnd* pOldWnd)
{
	CRichEditCtrl::OnSetFocus(pOldWnd);
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



void GP_RTF::OnSize(UINT nType, int cx, int cy)
{
	CRichEditCtrl::OnSize(nType, cx, cy);

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
	}
}


void GP_RTF::OnALIGN_LTR_EC()
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnALIGN_LTR_EC","");
}

void GP_RTF::OnALIGN_RTL_EC()
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnALIGN_RTL_EC","");
}
HBRUSH GP_RTF::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CRichEditCtrl::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}

int GP_RTF::AddChar(char iChar, DWORD iFlags)
{
	int ret=0;
	if (iChar)
	{
		return ret;
		int TextLen=GetTextLength();
		SetSel(TextLen,TextLen);
		char ReplText[]={0,0,};
		*ReplText=iChar;

		if (iChar==GPC.DelimiterIn1 && (iFlags&0x8))
			iChar=10;
		if (iChar==GPC.DelimiterIn2 && (iFlags&0x8))
			iChar=13;

		if ((m_DOflags&0xFF)==13 && (iFlags&0x2))
		{
			if (iChar==10)
			{
				*ReplText=13;
				ReplaceSel(ReplText);
				*ReplText=10;
				ReplaceSel(ReplText);
				TextLen++;
				TextLen++;
			}
			else
			{
				int nLine=GetLineCount();
				TextLen=LineIndex(GetLineCount()-1);
				SetSel(TextLen,-1);
				ReplaceSel("");
			}
		}

		if (iChar==13 && (iFlags&0x2))
		{
		}
		else
		if (iChar==10 && (iFlags&0x2))
		{
			if ((m_DOflags&0xFF)!=13)
			{
				*ReplText=13;
				ReplaceSel(ReplText);
				*ReplText=10;
				ReplaceSel(ReplText);
				TextLen++;
				TextLen++;
			}
		}
		else 
		if (iChar==8 && (iFlags&0x4))
		{
			if (TextLen)
			{
				SetSel(TextLen-1,TextLen);
				ReplaceSel("");
			}
		}
		else 
			ReplaceSel(ReplText);

		m_DOflags=(m_DOflags&0xFFFFFF00)|iChar;
		ret=GetTextLength();
	}
	return ret;
}

