// GPEdit.cpp : implementation file
//

#include "stdafx.h"
#include "GP_term.h"
#include "GPEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GPEdit
const char *GPEdit::cNoeditChars=" .,/\\*-+-¹;:|{}_()[]@!#$%^&*~`?'\"";
const UINT GPEdit::uNMethods=68;
const char *GPEdit::cArrMethods[]={
/*00*/		"CanUndo","GetLineCount","GetModify","SetModify","GetRect",
/*05*/		"GetSel","SetMargins","GetMargins","SetLimitText","GetLimitText",
/*10*/		"PosFromChar","CharFromPos","GetLine","GetPasswordChar","GetFirstVisibleLine",
/*15*/		"EmptyUndoBuffer","FmtLines","LimitText","LineFromChar","LineIndex",
/*20*/		"LineLength","LineScroll","ReplaceSel","SetPasswordChar","SetRect",
/*25*/		"SetRectNP","SetSel","SetTabStops","SetReadOnly","Undo",
/*30*/		"Clear","Copy","Cut","Paste","ClearText",
/*35*/		"SetFloat","SetChar","SetMask","UpdateGroup","AddLine",
/*40*/		"GetAllText","GetInsertMode","SetInsertMode","ScrollUp","ScrollDown",
/*45*/		"ScrollPGUP","ScrollPGDOWN","ScrollCaret","GetThumb","SetVP",
/*50*/		"SetAutoWidth","EnableContextMenu","IsEnableContextMenu","GetMaskSpec","GetCharSpec",
/*55*/		"GetFloat","ClearMaskText","SetImeStatus","GetImeStatus","SetCueBanner",
/*60*/		"GetCueBanner","ShowBalloonTip","HideBalloonTip","SetAutoFocus","SetOnchangeFlag",
/*65*/		"SetAddOnly","GetTextLength","SetDefSelMode","","",
/*70*/		"","","","","",
	};

const char *GPEdit::cArrMethodsParams[]={
/*00*/		"","","","bModify","",
/*05*/		"","left,right","","nMax","",
/*10*/		"nChar","poX,poY","nIndex","","",
/*15*/		"","bAddEOL","nChars","nIndex","nLine",
/*20*/		"nLine","nLines,nChars","Text","PssChar","left,top,right,bottom",
/*25*/		"left,top,right,bottom","nStartChar,nEndChar,bNoScroll","TStop1,TStop2,...,TStopN","bReadOnly","",
/*30*/		"","","","","",
/*35*/		"nAfterPoint","MaskCharString","Not Present","","Text",
/*40*/		"","","bInsertMode","","",
/*45*/		"","","","","iPos",
/*50*/		"min,max,delta","bEnable","","","",
/*55*/		"","","ImeStatus","","BannerText",
/*60*/		"","nIcon,TitleText^TipText","","bAuto","bAlwaysOnchange",
/*65*/		"bAddOnly","","SelectionMode 0 1 2 ","","",
/*70*/		"","","","","",
	};

GPEdit::GPEdit(UINT iUnitId)
{
	m_dwTextMode=0;
	m_AddOnlyFlag=0;
	m_AlwaysOnchange=1;
	m_DOflags=0;
	AutoWidthMin=0;AutoWidthMax=0;AutoWidthDelta=0;
	m_EnableContextMenu=1;
	MaskFlag=0xFFFF;
	m_uCurVP=0;
	CharSpec=NULL;
	MaskSpec=NULL;
	FloatPoint=-1;
	referGPU=NULL;
	UnitId=iUnitId;
	m_bAutoFocus=TRUE;
	m_LastChangedCRC=0;
}

GPEdit::~GPEdit()
{
	if (CharSpec!=NULL) delete[] CharSpec;
	if (MaskSpec!=NULL) delete[] MaskSpec;
}


BEGIN_MESSAGE_MAP(GPEdit, CEdit)
	//{{AFX_MSG_MAP(GPEdit)
	ON_CONTROL_REFLECT(EN_HSCROLL, OnHscroll)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_CONTROL_REFLECT(EN_ERRSPACE, OnErrspace)
	ON_CONTROL_REFLECT(EN_MAXTEXT, OnMaxtext)
	ON_CONTROL_REFLECT(EN_SETFOCUS, OnNotifySetfocus)
	ON_CONTROL_REFLECT(EN_UPDATE, OnUpdate)
	ON_CONTROL_REFLECT(EN_ALIGN_LTR_EC, OnALIGN_LTR_EC)
	ON_CONTROL_REFLECT(EN_ALIGN_RTL_EC, OnALIGN_RTL_EC)
	ON_CONTROL_REFLECT(EN_VSCROLL, OnVscroll)
	ON_WM_PARENTNOTIFY_REFLECT()
	ON_WM_CLOSE()
	ON_WM_SIZING()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_NCHITTEST()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_CONTROL_REFLECT(EN_KILLFOCUS, OnNotifyKillfocus)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPEdit message handlers
UINT GPEdit::DoMethod(const char *iStr, char *oStr)
{
	char met[150];
	strncpy(met,iStr,145);
	met[145]=0;
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc=0;
	int retint=-123456;

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

	switch(nfunc)
	{
	case 0: /*CanUndo*/		if (oStr!=NULL)	retint=CanUndo();		break;
	case 1: /*GetLineCount*/if (oStr!=NULL)	retint=GetLineCount();	break;
	case 2: /*GetModify*/	if (oStr!=NULL)	retint=GetModify();		break;
	case 3: /*SetModify*/	SetModify(atoipos);						break;
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
			UINT tmpUINT=GetSel();
			sprintf(oStr,"%d\x7F%d",LOWORD(tmpUINT),HIWORD(tmpUINT));
		}
		break;
	case 6: /*SetMargins*/
		{
			UINT left=0,right=1;
			m_LastScanf=sscanf(pos,"%d,%d",&left,&right);
			SetMargins(left,right);
		}
		break;
	case 7: /*GetMargins*/
		if (oStr!=NULL)
		{
			UINT tmpUINT=GetMargins();
			sprintf(oStr,"%d\x7F%d",tmpUINT%0xFFFF,tmpUINT/0xFFFF);
		}
		break;
	case 8: /*SetLimitText*/ SetLimitText(atoipos);					break;
	case 9: /*GetLimitText*/ if (oStr!=NULL) retint=GetLimitText()	;break;
	case 10: /*PosFromChar*/
		if (oStr!=NULL)
		{
			CPoint po;
			po=PosFromChar(atoipos);
			sprintf(oStr,"%d\x7F%d",po.x,po.y);
		}
		break;
	case 11: /*CharFromPos*/
		if (oStr!=NULL)
		{
			CPoint po;po.x=0;po.y=0;
			m_LastScanf=sscanf(pos,"%d,%d",&po.x,&po.y);
			DWORD ch=CharFromPos(po);
			sprintf(oStr,"%d\x7F%d",LOWORD(ch),HIWORD(ch));
		}
		break;
	case 12: /*GetLine*/
		if (oStr!=NULL)
		{
			UINT tmpUINT=GetLine(atoipos,oStr,TMP_STR_OUT_LEN);
			oStr[tmpUINT]=0;
			char *str=oStr;
			do
				if (*str==10 || *str==13) *str=0;
			while(*(str++));
		}
		break;
	case 13: /*GetPasswordChar*/
		if (oStr!=NULL)	sprintf(oStr,"%c",(GetPasswordChar()==NULL)?' ':GetPasswordChar());
		break;
	case 14: /*GetFirstVisibleLine*/	if (oStr!=NULL)	retint=GetFirstVisibleLine();	break;
	case 15: /*EmptyUndoBuffer*/		EmptyUndoBuffer();			break;
	case 16: /*FmtLines*/				retint=FmtLines(atoipos);	break;
	case 17: /*LimitText*/				LimitText(atoipos);			break;
	case 18: /*LineFromChar*/			if (oStr!=NULL)	retint=LineFromChar(atoipos);	break;
	case 19: /*LineIndex*/				if (oStr!=NULL)	retint=LineIndex(atoipos);		break;
	case 20: /*LineLength*/				if (oStr!=NULL)	retint=LineLength(atoipos);		break;
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
			char *pos3=pos333,*pos4;
			do
			{
				pos3=strstr(pos3,"\\PARA");
				if (pos3!=NULL)
				{
					*(pos3++)=chDelim;
					strcpy(pos3,pos3+4);
				}
			}
			while(pos3!=NULL);

			pos3=pos333;

			if (*pos3!=0)
			{
				while(*pos3!=0)
				{
					pos4=pos3;
					while(*pos4!=0 && *pos4!=chDelim) pos4++;

					if (*pos4==0)
					{
						ReplaceSel(pos3,TRUE);break;
					}
					if (*pos4==chDelim) *(pos4++)=0;

					ReplaceSel(pos3,TRUE);
					ReplaceSel("\x0D\x0A",TRUE);
					pos3=pos4;
				}
			}
			else	ReplaceSel(pos333,TRUE);
			if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
				DoMethod("UpdateGroup",NULL);
			delete[] pos333;
			//SetDefSel();
		}
		break;
	case 23: /*SetPasswordChar*/ SetPasswordChar(*pos);	break;
	case 24: /*SetRect*/
	case 25: /*SetRectNP*/
		{
			CRect re; re.SetRect(11,11,22,22);
			m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&re.left,&re.top,&re.right,&re.bottom);
			if (nfunc==24) SetRect(re); else	SetRectNP(re);
		}
		break;
	case 26: /*SetSel*/
		{
			int left=0,right=1,repl=0;
			m_LastScanf=sscanf(pos,"%d,%d,%d",&left,&right,&repl);
			SetSel(left,right,repl);
			break;
		}
	case 27: /*SetTabStops*/
			if (strchr(pos,',')==NULL) SetTabStops(atoipos);
			else
				{
					const char *pos2,*pos3=pos;
					int ts[100];UINT nts=0;
					while((pos3=strchr(pos2=pos3,','))!=NULL && nts<99) ts[nts++]=atoi(++pos2);
					retint=SetTabStops(nts,ts);
				}
		break;
	case 28: /*SetReadOnly*/ retint=SetReadOnly(atoipos);			break;
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
			SetSel(0,-1,FALSE );
			Clear();
			if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->m_UpdateGroupFlag)
				DoMethod("UpdateGroup",NULL);
		}
		break;
	case 35: /*SetFloat*/
		FloatPoint=atoipos;
		if (CharSpec==NULL) CharSpec=new char [256];
		if (FloatPoint>0)
			strcpy(CharSpec,"-.,0123456789");
		else
		if (FloatPoint==0) strcpy(CharSpec,"-0123456789");
		else	{	delete[] CharSpec;CharSpec=NULL;	}

		break;
	case 36: /*SetChar*/
		if (*pos)
		{
			if (CharSpec==NULL) CharSpec=new char [(int)strlen(pos)+256];
			strcpy(CharSpec,pos);
		}
		else
		{
			if (CharSpec) delete[] CharSpec;
			CharSpec=NULL;
		}
		break;
	case 37: /*SetMask*/
		if (*pos)
		{
			if (MaskSpec==NULL) MaskSpec=new char [(int)strlen(pos)+256];
			strcpy(MaskSpec,pos);
			ClearMaskText();
		}
		else
		{
			if (MaskSpec) delete[] MaskSpec;
			MaskSpec=NULL;
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
	case 39: /*AddLine*/
		{
			int chDelim=1;
			if ((referGPU[UnitId&0xFFFF]->UnitCommonStyles&UCS_CRVM)==UCS_CRVM) chDelim=2;
			if ((referGPU[UnitId&0xFFFF]->UnitCommonStyles&UCS_CRSVM)==UCS_CRSVM) chDelim=3;
			int nStart=0,nEnd=0,EndTmp=0,StartTmp=0;
			GetSel(nStart,nEnd);
			SetSel(nEnd,-1);
			GetSel(StartTmp,EndTmp);
			SetSel(EndTmp,EndTmp);
			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
			char *pos3=pos333,*pos4;
			do
			{
				pos3=strstr(pos3,"\\PARA");
				if (pos3!=NULL)
				{
					*(pos3++)=chDelim;
					strcpy(pos3,pos3+4);
				}
			}
			while(pos3!=NULL);

			pos3=pos333;

			if (*pos3!=0)
			{
				while(*pos3!=0)
				{
					pos4=pos3;
					while(*pos4!=0 && *pos4!=chDelim) pos4++;

					if (*pos4==0)
					{
						ReplaceSel(pos3,TRUE);break;
					}
					if (*pos4==chDelim) *(pos4++)=0;

					ReplaceSel(pos3,TRUE);
					ReplaceSel("\x0D\x0A",TRUE);
					pos3=pos4;
				}
			}
			else	ReplaceSel(pos333,TRUE);
			SetSel(nStart,nEnd);
			delete[] pos333;
		}
		break;
	case 40: /*GetAllText*/
		if (oStr!=NULL)
		{
			int nnn=::GetWindowTextLength(m_hWnd);
			if (nnn>TMP_STR_OUT_LEN-10) nnn=TMP_STR_OUT_LEN-10;
			if (nnn) nnn=::GetWindowText(m_hWnd,oStr,nnn+2);
			oStr[nnn]=0;
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
				else *(str2++)=*str;
				str++;
			}
			*str2=0;
		}
		break;
	case 41: /*GetInsertMode*/	retint=GPC.m_bInsertMode;						break;
	case 42: /*SetInsertMode*/	GPC.m_bInsertMode=atoipos;						break;
	case 43: /*ScrollUp*/		retint=SendMessage(EM_SCROLL,SB_LINEUP,0);		break;
	case 44: /*ScrollDown*/		retint=SendMessage(EM_SCROLL,SB_LINEDOWN,0);	break;
	case 45: /*ScrollPGUP*/		retint=SendMessage(EM_SCROLL,SB_PAGEUP,0);		break;
	case 46: /*ScrollPGDOWN*/	retint=SendMessage(EM_SCROLL,SB_PAGEDOWN,0);	break;
	case 47: /*ScrollCaret*/	retint=SendMessage(EM_SCROLLCARET,0,0);			break;
	case 48: /*GetThumb*/		retint=SendMessage(EM_GETTHUMB,0,0);			break;
	case 49: /*SetVP*/
		{
			int nStart=0,nEnd=0;
			GetSel(nStart,nEnd);
			SetSel(atoipos,atoipos);
			SetSel(nStart,nEnd);
		}
		break;
	case 50: /*SetAutoWidth*/
		{
			AutoWidthMin=0;AutoWidthMax=0;AutoWidthDelta=0;
			m_LastScanf=sscanf(pos,"%d,%d,%d",&AutoWidthMin,&AutoWidthMax,&AutoWidthDelta);
			OnChangeVP();
		}
		break;
	case 51: /*EnableContextMenu*/
	case 52: /*IsEnableContextMenu*/
		retint=m_EnableContextMenu;
		if (nfunc==51) m_EnableContextMenu=atoipos;
		break;
	case 53: /*GetMaskSpec*/
		if (oStr!=NULL && MaskSpec) strcpy(oStr,MaskSpec);
		break;
	case 54: /*GetCharSpec*/
		if (oStr!=NULL && CharSpec) strcpy(oStr,CharSpec);
		break;
	case 55: /*GetFloat*/	retint=FloatPoint;	break;
	case 56: /*ClearMaskText*/ ClearMaskText();	break;
	case 57: /*SetImeStatus*/
	case 58: /*GetImeStatus*/
		{
			char *cArrIn[]={"GET","CAN","COMPL",};
			char *cArr[]={"GETCOMPSTRATONCE","CANCELCOMPSTRINFOCUS","COMPLETECOMPSTRKILLFOCUS",};
			UINT uArr[]={EIMES_GETCOMPSTRATONCE,EIMES_CANCELCOMPSTRINFOCUS,EIMES_COMPLETECOMPSTRKILLFOCUS,};
			UINT nArr=3;
			UINT i;
			DWORD ret=0;

			switch(nfunc)
			{
			case 57: /*SetImeStatus*/
				{
					DWORD uNew=0;
					for(i=0;i<nArr;i++)
						if (strstr(pos,cArrIn[i])) uNew|=uArr[i];

					ret=SendMessage(EM_SETIMESTATUS,EMSIS_COMPOSITIONSTRING,(LPARAM)uNew);
				}
				if (oStr==NULL) break;

			case 58: /*GetImeStatus*/
				if (oStr)
				{
					if (nfunc==58)	ret=SendMessage(EM_GETIMESTATUS,EMSIS_COMPOSITIONSTRING,0);
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
	case 59: /*SetCueBanner*/
		{
			CString tmps=pos;
			BSTR tmpbstr=tmps.AllocSysString();
			retint=SendMessage(EM_SETCUEBANNER,0,(LPARAM)((LPCWSTR)tmpbstr));
			::SysFreeString(tmpbstr);
		}
		break;
	case 60: /*GetCueBanner*/
		if (oStr)
		{
			BSTR tmpbstr=NULL;
			retint=SendMessage(EM_GETCUEBANNER,0,(LPARAM)(LPCWSTR)tmpbstr);
			CString tmps(tmpbstr);
			strcpy(oStr,tmps);
			::SysFreeString(tmpbstr);
		}
		break;
	case 61: /*ShowBalloonTip*/
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
	case 62: /*HideBalloonTip*/
		retint=SendMessage(EM_HIDEBALLOONTIP,0,0);
		break;
	case 63: /*SetAutoFocus*/
		retint=m_bAutoFocus;
		m_bAutoFocus=atoipos;
		break;
	case 64: /*SetOnchangeFlag*/
		retint=m_AlwaysOnchange;
		m_AlwaysOnchange=atoipos;
		break;
	case 65: /*SetAddOnly*/
		retint=m_AddOnlyFlag;
		m_AddOnlyFlag=atoipos;
		break;
	case 66: /*GetTextLength*/
		retint=::GetWindowTextLength(m_hWnd);
		break;
	case 67: /*SetDefSelMode*/
		retint=m_dwTextMode;
		m_dwTextMode=atoipos;
		break;

	default:
		if (oStr!=NULL)
				 sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);

	return nfunc;
}


UINT GPEdit::GPSetProperty(const char *iStr)
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
				if (m_hWnd!=NULL)
				{
					char *tmp=new char [(int)strlen(pos)+100];
					sprintf(tmp,"ReplaceSel %s",pos);
					SetSel(0,-1);
					DoMethod(tmp,NULL);
					delete[] tmp;
					SetDefSel();
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
					for(i=0;i<N_EDIT_STYLES;i++)
						if (strstr(pos,aEditStyleName[i])!=NULL)
						{
							InvFlg++;
							switch(propnum)
							{
							case 3: /* STYLE*/
							case 1: /* ADDSTYLE*/	ModifyStyle(0,aEditStyleUINT[i]);break;
							case 2: /* DELSTYLE*/	ModifyStyle(aEditStyleUINT[i],0);break;
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

void GPEdit::OnHscroll()
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnHscroll","");
	OnChangeVP();
	if (referGPU && referGPU[UnitId&0xFFFF]->m_SizerArray)	Invalidate();
}

void GPEdit::OnChange()
{
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		DWORD newCRC=(m_AlwaysOnchange)?m_LastChangedCRC+1:GetCRC16forText();
		if (newCRC!=m_LastChangedCRC)
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
			m_LastChangedCRC=newCRC;
		}
	}
}

void GPEdit::OnErrspace()
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnErrspace","");
}

void GPEdit::OnMaxtext()
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnMaxtext","");
}

void GPEdit::OnNotifySetfocus()
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNotifySetfocus","");
}

void GPEdit::OnALIGN_LTR_EC()
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnALIGN_LTR_EC","");
}

void GPEdit::OnALIGN_RTL_EC()
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnALIGN_RTL_EC","");
}

void GPEdit::OnUpdate()
{
	int man=0;
	int deltaPos=0;
	DWORD stl=GetStyle();

	if (MaskSpec!=NULL && (stl&ES_READONLY)!=ES_READONLY)
	{
		int nStartChar, nEndChar;
		GetSel(nStartChar, nEndChar);

	}
	else
	if (CharSpec!=NULL && (stl&ES_READONLY)!=ES_READONLY)
	{
		int nline;
		char **astr=new char * [(nline=GetLineCount( ))+1];
		int nStartChar, nEndChar;
		GetSel(nStartChar, nEndChar);

		int i;
		for(i=0;i<nline;i++)
		{
			int nc;
			astr[i]=new char [LineLength(i)+100];
			*astr[i]=0;
			nc=GetLine(i,astr[i],LineLength(i)+100);
			if (nc>0) *(astr[i]+nc)=0;
		}

		for(i=0;i<nline;i++)
		{
			char *cmps=new char [(int)strlen(astr[i])+100];
			strcpy(cmps,astr[i]);

//			if ((int)strlen(astr[i])>0)
			{
				if (FloatPoint>0)
				{
					char *pss=astr[i];
					int n0=0;
					while(*pss && ((*pss>='0' && *pss<='9') || *pss=='-' || *pss=='+'))
					{
						if (*pss>='0' && *pss<='9') n0++;
						pss++;
					}
					if (n0==0) n0++;
					int si=1;
					pss=astr[i];
					while((pss=strchr(pss,'-'))!=NULL) {*(pss++)=' ';si=si-2*si;}
					pss=astr[i];
					while((pss=strchr(pss,'+'))!=NULL) {*(pss++)=' ';si=1;}
					pss=astr[i];
					while((pss=strchr(pss,','))!=NULL) *(pss++)='.';

					if ((pss=strchr(astr[i],'.'))!=NULL)
						while((pss=strchr(++pss,'.'))!=NULL) *pss=' ';

					pss=astr[i];
					while(*pss!=0)
						if (*pss=='.' || (*pss>='0' &&  *pss<='9')) pss++;
							else
							{
								if (pss-astr[i]<nStartChar) nStartChar--;
								if (pss-astr[i]<nEndChar) nEndChar--;
								strcpy(pss,pss+1);
							}

					char fmt[25];
					sprintf(fmt,"%s%c0%d.%df",si<0?"-":"",'%',n0+FloatPoint+1,FloatPoint);
					sprintf(astr[i],fmt,atof(astr[i]));
					char *replPos=astr[i];
					while(*replPos)
					{
						if (*replPos==',') *replPos='.';
						replPos++;
					}
					if (strcmp(cmps,astr[i])!=0)
					{
						if ((*cmps=='.' || *cmps=='-') && atof(astr[i])==0)
						{
							if (*cmps=='-') {nStartChar++;nEndChar++;}
							else strcpy(astr[i],astr[i]+1);
						}
						else
							if (*cmps=='-') {nStartChar++;nEndChar++;}
					}
					else
					if (nStartChar==1 && *cmps=='-' && atof(astr[i]+nStartChar+1)==0 && *(astr[i]+nStartChar+1)!='.')
					{
							strcpy(astr[i]+2,astr[i]+3);
							nStartChar++;nEndChar++;
					}
				}
				else
				if (FloatPoint==0)
				{
					char *pss=astr[i];
					int n0=0;
					while(*pss && ((*pss>='0' && *pss<='9') || *pss=='-' || *pss=='+'))
					{
						if (*pss>='0' && *pss<='9') n0++;
						pss++;
					}

					if (n0==0) n0++;

					pss=astr[i];
					int si=1;
					while((pss=strchr(pss,'-'))!=NULL) {*(pss++)=' ';si=si-2*si;}
					pss=astr[i];
					while((pss=strchr(pss,'+'))!=NULL) {*(pss++)=' ';si=1;}
					pss=astr[i];
					while(*pss!=0)
						if (*pss>='0' &&  *pss<='9') pss++;
							else
							{
								if (pss-astr[i]<nStartChar) nStartChar--;
								if (pss-astr[i]<nEndChar) nEndChar--;
								strcpy(pss,pss+1);
							}

					if (atof(astr[i])!=0 || n0>1)
					{
						char fmt[25];
						sprintf(fmt,"%c0%d.25g",'%',n0);
						sprintf(astr[i],fmt,atof(astr[i])*si);
						char *replPos=astr[i];
						while(*replPos)
						{
							if (*replPos==',') *replPos='.';
							replPos++;
						}
					}
					else
						strcpy(astr[i],si<0?"-0":"0");
				}
				else
				{
					char *pss=astr[i];
					UINT flg=0;
					if (strstr(CharSpec,"SIGN1")!=NULL) flg|=0x0001;
					if (strstr(CharSpec,"SIGN2")!=NULL) flg|=0x0002;
					if (strstr(CharSpec,"SIGN3")!=NULL) flg|=0x0004;
					if (strstr(CharSpec,"SIGN4")!=NULL) flg|=0x0008;
					if (strstr(CharSpec,"DIGIT")!=NULL) flg|=0x0010;
					if (strstr(CharSpec,"LCENG")!=NULL) flg|=0x0020;
					if (strstr(CharSpec,"UCENG")!=NULL) flg|=0x0040;
					if (strstr(CharSpec,"LCRUS")!=NULL) flg|=0x0080;
					if (strstr(CharSpec,"UCRUS")!=NULL) flg|=0x0100;

					while(*pss!=0 && CharSpec!=NULL)
					{
						if (flg!=0)
						{
							if (   ((flg&0x0001)!=0 && *pss>='!' && *pss<='/')
								|| ((flg&0x0002)!=0 && *pss>=':' && *pss<='@')
								|| ((flg&0x0004)!=0 && *pss>='[' && *pss<='`')
								|| ((flg&0x0008)!=0 && *pss>='{' && *pss<='~')
								|| ((flg&0x0010)!=0 && *pss>='0' && *pss<='9')
								|| ((flg&0x0020)!=0 && *pss>='a' && *pss<='z')
								|| ((flg&0x0040)!=0 && *pss>='A' && *pss<='Z')
								|| ((flg&0x0080)!=0 && *pss>='À' && *pss<='ß')
								|| ((flg&0x0100)!=0 && *pss>='à' && *pss<='ÿ')
								) {pss++;continue;}
						}
						else
						{
							if (strchr(CharSpec,*pss)!=NULL) {pss++;continue;}
						}

						if (pss-astr[i]<nStartChar) nStartChar--;
						if (pss-astr[i]<nEndChar) nEndChar--;
						strcpy(pss,pss+1);
					}
				}
			}
			if (strcmp(cmps,astr[i])!=0) man++;
			if (deltaPos==0 && i==0 && (*cmps=='-' || *astr[i]=='-') && *cmps!=*astr[i])
			{
				if (*cmps=='-')	deltaPos=-1;
				else			deltaPos=1;
			}
			delete[] cmps;
		}

		int len=0;
		for(i=0;i<nline;i++)	len+=(int)strlen(astr[i])+1;

		char *str=new char [len+nline*2+200];
		*str=0;

		for(i=0;i<nline;i++)
		{
			strcat(str,astr[i]);
			if (i!=nline-1) strcat(str,"\r\n");
			delete[] astr[i];
		}

		if (man!=0)
		{
			static int flg;
			if (flg!=1)
			{
				flg=1;
				SetSel(0,-1);
				ReplaceSel(str);
				if (deltaPos>0)
				{
					nStartChar+=deltaPos;
					nEndChar+=deltaPos;
				}
				SetSel(nStartChar,nEndChar);
				flg=0;
			}
		}

		delete[] astr;
		delete[] str;
	}
	if (man==0 && referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnUpdate","");
}

void GPEdit::OnVscroll()
{
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnVscroll","");
	OnChangeVP();
	if (referGPU && referGPU[UnitId&0xFFFF]->m_SizerArray)	Invalidate();
}


void GPEdit::ParentNotify(UINT message, LPARAM lParam)
{
	char txt[100];
	if (message==WM_CREATE || message==WM_DESTROY)
		sprintf(txt,"%d\x7F%d\x7F%X",message/0x10000,(message&0xFFFF),lParam/0x10000);
	else
		sprintf(txt,"%d\x7F%d\x7F%d\x7F%d",message/0x10000,(message&0xFFFF),lParam/0x10000,(lParam&0xFFFF));
	if (referGPU!=NULL)
			referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"ParentNotify",txt);
}

LRESULT GPEdit::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		referGPU[UnitId&0xFFFF]->m_CurMessage.message=message;
		referGPU[UnitId&0xFFFF]->m_CurMessage.wParam=wParam;
		referGPU[UnitId&0xFFFF]->m_CurMessage.lParam=lParam;
		if (referGPU[UnitId&0xFFFF]->DefWindowProc(message, wParam, lParam)) return 0;
	}


	if (m_AddOnlyFlag)
	{
		switch(message)
		{
		case EM_SETSEL:
			if (m_AddOnlyFlag)
			{
				CEdit::WindowProc(message, (UINT)lParam>(UINT)wParam?wParam:lParam, -1);
				return 1;
			}
			break;
		case WM_LBUTTONUP:
			if (m_AddOnlyFlag)
			{
				m_AddOnlyFlag=1;
				CEdit::WindowProc(message, wParam, lParam);
				int selstrt=0,selend=-1;
				GetSel(selstrt,selend);
				if (selstrt>selend) selstrt=selend;
				CEdit::WindowProc(EM_SETSEL,selstrt, -1);
				return 1;
			}
			break;
		}
	}


	if (message==GPM_SETAUTOSIZE)
		GetParent()->PostMessage(GPM_SETAUTOSIZE,wParam);

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
		if (message!=WM_KEYDOWN || !(::GetWindowLong(m_hWnd,GWL_STYLE)&ES_MULTILINE))
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
			case GPUA_ENTIRE:
				MoveWindow(&lpLayout->rect);
				lpLayout->rect.left=lpLayout->rect.right;
				lpLayout->rect.top=lpLayout->rect.bottom;
				break;
			}

		}

	}

	if (message==GPN_UPDATESIZE) GetParent()->SendMessage(GPN_UPDATESIZE);

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
	if ((message==WM_SETCURSOR && GPC.m_bWaitCursor) ||(message==WM_CONTEXTMENU && !m_EnableContextMenu)) lpr=FALSE;
	else lpr=CEdit::WindowProc(message, wParam, lParam);

	return lpr;
}

BOOL GPEdit::PreTranslateMessage(MSG* pMsg)
{
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		referGPU[UnitId&0xFFFF]->m_CurPreMessage=pMsg;
		if (!referGPU[UnitId&0xFFFF]->DefPreTranslateMessage(pMsg)) return 0;
		if (pMsg->message==WM_KEYDOWN)
		{
			if (m_AddOnlyFlag)
			{
				if (pMsg->wParam==VK_END)
				{
					SetSel(-1,-1);
					m_AddOnlyFlag|=0x2;
				}
				else
				if (pMsg->wParam==VK_HOME)
				{
					if (!(GetAsyncKeyState(VK_SHIFT)&0xFF00))
					{
						m_AddOnlyFlag|=0x2;
						::PostMessage(m_hWnd,EM_SETSEL,0,-1);
						::PostMessage(m_hWnd,EM_SETSEL,-1,-1);
					}
					else
					{
						m_AddOnlyFlag&=(0xFFFFFFFF^0x2);
						::PostMessage(m_hWnd,EM_SETSEL,0,-1);
					}
				}
				else
				{
					if (pMsg->wParam>=VK_PRIOR && pMsg->wParam<=VK_DOWN)
					{
						if (!(GetAsyncKeyState(VK_SHIFT)&0xFF00)) return 1;
						if (!(m_AddOnlyFlag&0x2) && pMsg->wParam!=VK_RIGHT) return 1;
					}
					else 
						if  (pMsg->wParam==VK_DELETE || pMsg->wParam==VK_BACK || pMsg->wParam==VK_SPACE || (pMsg->wParam>=0x30 && pMsg->wParam<=0x5A) || (pMsg->wParam>=VK_NUMPAD0 && pMsg->wParam<=VK_DIVIDE))
							m_AddOnlyFlag|=0x2;

				}
			}
			if (pMsg->wParam==0x41 && (GetAsyncKeyState(VK_CONTROL)&0xFF00)) SetSel(0,-1);
		}


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

	return CEdit::PreTranslateMessage(pMsg);
}

void GPEdit::OnClose()
{
	if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClose","");
//	CEdit::OnClose();
}

void GPEdit::OnSizing(UINT fwSide, LPRECT pRect)
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

	if (EnableSz) CEdit::OnSizing(fwSide, pRect);

	GetParent()->SendMessage(GPN_UPDATESIZE);
	OnChangeVP();
}

void GPEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	DWORD stl=GetStyle();
	if (GPC.m_bInsertMode && nChar!=VK_DELETE
		&& nChar!=VK_BACK && nChar!=VK_INSERT
		&& nChar!=VK_EXECUTE  && ((nChar>=48 && nChar<=57) || (stl&ES_NUMBER)!=ES_NUMBER)
		&& (stl&ES_READONLY)!=ES_READONLY)
	{
		int nStartChar,nEndChar;
		GetSel(nStartChar,nEndChar);
		char str[210];
		int nl=0;
		GetLine(nl=LineFromChar(nStartChar),str,200);
		if (str[nStartChar-LineIndex(nl)]!='.')
		{
			SetSel(nStartChar,nStartChar+1);
			ReplaceSel("");
			if (nEndChar>nStartChar) nEndChar--;
			SetSel(nStartChar,nEndChar);
		}
	}
	if (MaskSpec==NULL)
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	else
	if (MaskFlag<0xFF)
	{
		char str[300];
		int sel=MaskFlag;
		BOOL bUpdate=FALSE;
		MaskFlag=0xFFFF;
		str[GetLine(0,str,256)]=0;
		switch(MaskSpec[sel])
		{
		case 'D':// day  DD.MM.YYYY.mm.SS.NNN.BBB.HHH.OOO.EEE.eee.AAA.RRR.rrr.CCC.aaa
			bUpdate=
				(MaskSpec[sel+1]=='D' && nChar>='0' && ((nChar=='3' && (str[sel+1]<'2' || str[sel+1]>'9'))||nChar<'3'))
				||
				(MaskSpec[sel-1]=='D' && nChar>='0' && ((str[sel-1]=='3' && (nChar<'2' || nChar>'9'))||(str[sel-1]<'3' && nChar<='9')));
			break;
		case 'M'://month
			bUpdate=
				(MaskSpec[sel+1]=='M' && nChar>='0' && ((nChar=='1' && (str[sel+1]<'3' || str[sel+1]>'9'))||nChar=='0'))
				||
				(MaskSpec[sel-1]=='M' && nChar>='0' && ((str[sel-1]=='1' && (nChar<'3' || nChar>'9'))||(str[sel-1]=='0' && nChar<='9')));
			break;
		case 'Y'://year
		case 'N'://numeric dec
			bUpdate=nChar>='0' && nChar<='9';	break;
		case 'H'://numeric hex
			bUpdate=(nChar>='0' && nChar<='9') || (nChar>='A' && nChar<='F');	break;
		case 'O'://numeric oct
			bUpdate=nChar>='0' && nChar<='7';	break;
		case 'B'://numeric bin
			bUpdate=nChar>='0' && nChar<='1';	break;
		case 'S'://seconds
			bUpdate=
				(MaskSpec[sel+1]=='S' && nChar>='0' && nChar<='5')
				||
				(MaskSpec[sel-1]=='S' && nChar>='0' && nChar<='9');
			break;
		case 'm'://minutes
			bUpdate=
				(MaskSpec[sel+1]=='m' && nChar>='0' && nChar<='5')
				||
				(MaskSpec[sel-1]=='m' && nChar>='0' && nChar<='9');
			break;
		case 'E'://chart I cap
			bUpdate=nChar>='A' && nChar<='Z';	break;
		case 'e'://chart I small
			bUpdate=nChar>='a' && nChar<='z';	break;
		case 'A'://chart I all
			bUpdate=(nChar>='A' && nChar<='Z') || (nChar>='a' && nChar<='z');	break;
		case 'R'://chart II cap
			bUpdate=nChar>='À' && nChar<='ß';	break;
		case 'r'://chart II small
			bUpdate=nChar>='à' && nChar<='ÿ';	break;
		case 'C'://chart II all
			bUpdate=(nChar>='à' && nChar<='ÿ') || (nChar>='À' && nChar<='ß');	break;
		case 'a'://chart II all
			bUpdate=TRUE;		break;
		}

		if (bUpdate)
		{
			str[sel]=nChar;
			SetWindowText(str);
			NextMaskPosition(sel);
		}
		SetSel(sel,sel);
	}
	OnChangeVP();
}

void GPEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (MaskSpec)
	{
		int nStartChar,nEndChar;
		GetSel(nStartChar,nEndChar);
		char *tmpText=new char [1024];
		tmpText[GetLine(0,tmpText,1000)]=0;
		BOOL bUpdate=FALSE;
		switch(nChar)
		{
		case VK_DELETE:
			if ((GetAsyncKeyState(VK_CONTROL)&0xFF00)) ClearMaskText();
			else
			{
				tmpText[nStartChar]='_';
				bUpdate=TRUE;
				if (NextMaskPosition(nStartChar))
					GetParent()->PostMessage(GPM_NEXTCELL,VK_RIGHT,0);
			}
			break;
		case VK_RIGHT:
			if ((GetAsyncKeyState(VK_CONTROL)&0xFF00))
			{
				while(!NextMaskPosition(nStartChar));
				SetSel(nStartChar,nStartChar,FALSE);
			}
			else
			{
				if (NextMaskPosition(nStartChar))
					GetParent()->PostMessage(GPM_NEXTCELL,VK_RIGHT,0);
				SetSel(nStartChar,nStartChar,FALSE);
			}
			break;
		case VK_BACK:
			if ((GetAsyncKeyState(VK_CONTROL)&0xFF00)) ClearMaskText();
			else
			{
				tmpText[nStartChar]='_';
				bUpdate=TRUE;
				if (PrevMaskPosition(nStartChar))
					GetParent()->PostMessage(GPM_NEXTCELL,VK_LEFT,0);
			}
			break;
		case VK_LEFT:
			if ((GetAsyncKeyState(VK_CONTROL)&0xFF00))
			{
				while(!PrevMaskPosition(nStartChar));
				SetSel(nStartChar,nStartChar,FALSE);
			}
			else
			{
				if (PrevMaskPosition(nStartChar))
					GetParent()->PostMessage(GPM_NEXTCELL,VK_LEFT,0);
				SetSel(nStartChar,nStartChar,FALSE);
			}
			break;
		case VK_UP:		GetParent()->PostMessage(GPM_NEXTCELL,VK_UP,0);		break;
		case VK_DOWN:	GetParent()->PostMessage(GPM_NEXTCELL,VK_DOWN,0);	break;
		default:
			if ((GetAsyncKeyState(VK_CONTROL)&0xFF00)==0)
			{
				while(strchr(cNoeditChars,MaskSpec[nStartChar])!=NULL && NextMaskPosition(nStartChar)==0);
				MaskFlag=nStartChar;

				if (NextMaskPosition(nStartChar))
					GetParent()->PostMessage(GPM_NEXTCELL,VK_RIGHT,0);
			}
			break;
		}
		if (bUpdate)
		{
			SetWindowText(tmpText);
			SetSel(nStartChar,nStartChar,FALSE);
		}
		delete[] tmpText;
	}
	else
	if ((GetAsyncKeyState(VK_CONTROL)&0xFF00)==0 &&
		(GetAsyncKeyState(VK_SHIFT)&0xFF00)==0 &&
		(GetAsyncKeyState(VK_RWIN)&0xFF00)==0 &&
		(GetAsyncKeyState(VK_LWIN)&0xFF00)==0 &&
		(nChar==VK_INSERT || nChar==VK_LEFT || nChar==VK_UP || nChar==VK_RIGHT || nChar==VK_DOWN))
	{
		if (nChar==VK_INSERT) GPC.m_bInsertMode=(GPC.m_bInsertMode)?FALSE:TRUE;
		else
		{
			DWORD stl=GetStyle();
			int nStartChar,nEndChar;
			GetSel(nStartChar,nEndChar);

			if ((stl&ES_MULTILINE)==ES_MULTILINE)
			{
				switch(nChar)
				{
				case VK_LEFT:
					if (nStartChar==0)	GetParent()->PostMessage(GPM_NEXTCELL,VK_LEFT,0);
						else			CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
					break;
				case VK_UP:
					if (LineFromChar(nStartChar)==0)	GetParent()->PostMessage(GPM_NEXTCELL,VK_UP,0);
						else							CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
					break;
				case VK_RIGHT:
					{
						LRESULT lr=SendMessage( EM_GETLINECOUNT,0,0)-1;
						LRESULT lrlen=SendMessage( EM_LINELENGTH,nStartChar,0);
						if (lr==LineFromChar(nStartChar) && lrlen==nStartChar)
							GetParent()->PostMessage(GPM_NEXTCELL,VK_RIGHT,0);
							else	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
					}
					break;
				case VK_DOWN:
					{
						LRESULT lr=SendMessage( EM_GETLINECOUNT,0,0)-1;
						if (lr==LineFromChar(nStartChar))
							GetParent()->PostMessage(GPM_NEXTCELL,VK_DOWN,0);
							else	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
					}
					break;
				}
			}
			else
			{
				switch(nChar)
				{
				case VK_UP:		GetParent()->PostMessage(GPM_NEXTCELL,VK_UP,0);		break;
				case VK_DOWN:	GetParent()->PostMessage(GPM_NEXTCELL,VK_DOWN,0);	break;
				case VK_LEFT:
					if (nStartChar==0)
						GetParent()->PostMessage(GPM_NEXTCELL,VK_LEFT,0);
						else	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
					break;
				case VK_RIGHT:
					{
						LRESULT lr=SendMessage( EM_LINELENGTH,nStartChar,0);
						if (lr==nStartChar)
							GetParent()->PostMessage(GPM_NEXTCELL,VK_RIGHT,0);
							else	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
					}
					break;
				}
			}
		}
	}
	else
	if ((nChar==VK_SUBTRACT || nChar==VK_ADD) && FloatPoint>=0)
	{
		nChar=0xBD/*VK_OEM_MINUS*/;
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
	}
	else
	if (nChar==VK_DELETE && FloatPoint>0)
	{
		int nStartChar,nEndChar;
		GetSel(nStartChar,nEndChar);
		char str[210];
		int nl=0;
		GetLine(nl=LineFromChar(nStartChar),str,200);
		if (str[nStartChar-LineIndex(nl)]!='.')
			CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
	}
	else
	if (MaskSpec!=NULL && (nChar==VK_DELETE || nChar==VK_BACK))
	{
		nChar=nChar;
	}
	else
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);

	if ((nChar==VK_DELETE || nChar==VK_BACK) && AutoWidthMin!=0 && AutoWidthMax>AutoWidthMin && AutoWidthDelta>0)
		m_uCurVP=-1;

	OnChangeVP();
}

void GPEdit::OnDragMouseHover()
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
		pol.x=LOWORD(dwPos);
		pol.y=HIWORD(dwPos);
		long nchar = SendMessage(EM_CHARFROMPOS,0,(LPARAM)&pol);
		long nline = SendMessage(EM_LINEFROMCHAR,nchar,0);
		long ncharINline = SendMessage(EM_LINEINDEX,nline,0);
		tmps.Format("%d\x07%d\x07%d",nchar,nline,ncharINline);
		referGPU[UnitId&0xFFFF]->SendDropHoverEvent(tmps,&GPC.m_DragDrop,&point);
	}
}

void GPEdit::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
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

void GPEdit::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point)
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && referGPU)
	{
		::ScreenToClient(m_hWnd,point);
		CString tmp;
		long nchar = SendMessage(EM_CHARFROMPOS,0,MAKELPARAM(point->x,point->y));
		long nline = SendMessage(EM_LINEFROMCHAR,nchar,0);
		long ncharINline = SendMessage(EM_LINEINDEX,nline,0);
		tmp.Format("%d\x07%d\x07%d",nchar,nline,ncharINline);
		referGPU[UnitId&0xFFFF]->SendDropEvent(tmp,pDrDrStruct,point);
	}
}

DWORD GPEdit::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	return 0;
}

LRESULT GPEdit::OnNcHitTest(CPoint point)
{
	LRESULT ret=CEdit::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

void GPEdit::OnChangeVP()
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
								int nStart=0,nEnd=0;
								GetSel(nStart,nEnd);
								SetSel((int)m_uCurVP,(int)m_uCurVP);
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

void GPEdit::OnRButtonDown(UINT nFlags, CPoint point)
{
	CEdit::OnRButtonDown(nFlags, point);
}

void GPEdit::OnRButtonUp(UINT nFlags, CPoint point)
{
	CEdit::OnRButtonUp(nFlags, point);
}

BOOL GPEdit::SetreferGPU(GPUnit **iGPU)
{
	return (referGPU=iGPU)!=NULL;
}

void GPEdit::ClearMaskText()
{
	if (MaskSpec)
	{
		char *tmp=new char [(int)strlen(MaskSpec)+5];
		strcpy(tmp,MaskSpec);
		char *pos=tmp;
		while(*pos)
		{
			if (strchr(cNoeditChars,*pos)==NULL) *pos='_';
			pos++;
		}
		SetWindowText(tmp);
		pos=strchr(tmp,'_');
		if (pos) SetSel(pos-tmp,pos-tmp,FALSE);
		delete[] tmp;
	}
}

long GPEdit::NextMaskPosition(int &iPosition)
{
	long ret=0;
	if (MaskSpec)
	{
		if (iPosition>=(int)(int)strlen(MaskSpec))
		{
			char *pos=MaskSpec;
			while(*pos) pos++;

			while(pos>MaskSpec)
			{
				if (*pos && strchr(cNoeditChars,*pos)==NULL) break;
				pos--;
			}
			iPosition=pos-MaskSpec;
		}
		else
		{
			char *pos=MaskSpec+iPosition;
			char *tmppos=pos;
			while(*(++pos) && strchr(cNoeditChars,*pos));
			if (*pos) iPosition=pos-MaskSpec;
			else
			{
				if (strchr(cNoeditChars,*tmppos)) PrevMaskPosition(iPosition);
				ret=1;
			}
		}
	}
	return ret;
}


long GPEdit::PrevMaskPosition(int &iPosition)
{
	long ret=0;
	if (MaskSpec)
	{
		if (iPosition>=(int)(int)strlen(MaskSpec))
		{
			char *pos=MaskSpec;
			while(*pos) pos++;

			while(pos>MaskSpec)
			{
				if (*pos && strchr(cNoeditChars,*pos)==NULL) break;
				pos--;
			}
			iPosition=pos-MaskSpec;
		}
		else
		{
			char *pos=MaskSpec+iPosition;
			while((--pos)>=MaskSpec && strchr(cNoeditChars,*pos));
			if (pos>=MaskSpec) iPosition=pos-MaskSpec;
			else
			{
				iPosition=0;
				pos=MaskSpec;
				while(*pos && strchr(cNoeditChars,*pos)!=NULL) pos++;
				iPosition=pos-MaskSpec;
				ret=1;
			}
		}
	}
	return ret;
}

#include "GP_TermDoc.h"

void GPEdit::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);
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

	::PostMessage(::GetParent(m_hWnd),GPM_UPDATELVEDITOR,0,0);
	if (referGPU!=NULL)
	{
		char *str = new char [10000];
		int nC=0;
		if ((nC=GetLine(0,str,9990))<1) *str=0;
		else str[nC]=0;
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnKillFocusEx",str);
		delete[] str;
	}
	::SendMessage(::GetParent(m_hWnd),GPM_CLIENTKILLFOCUS,(WPARAM)(pNewWnd?pNewWnd->m_hWnd:NULL),(LPARAM)&ui);
}

void GPEdit::OnSetFocus(CWnd* pOldWnd)
{
	CEdit::OnSetFocus(pOldWnd);
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

void GPEdit::OnNotifyKillfocus()
{
	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG)
	{
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNotifyKillfocus","");
	}
}

void GPEdit::OnSize(UINT nType, int cx, int cy)
{
	CEdit::OnSize(nType, cx, cy);

	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
	}
}

HBRUSH GPEdit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CEdit::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}

int GPEdit::AddChar(char iChar, DWORD iFlags)
{
	int ret=0;
	if (iChar)
	{
		SetSel(0,-1);
		int TextLen=HIWORD(GetSel());
		SetSel(TextLen,TextLen);
		char ReplText[]={0,0,0,};
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
		if (iChar==10 || iChar==13 || iChar==0 || (iChar==GPC.DelimiterIn1 && (iFlags&0x8)))
		{
			if (iChar==13 || (iChar==GPC.DelimiterIn1 && (iFlags&0x8)))
			{
				ReplText[0]=13;
				ReplText[1]=10;
				ReplaceSel(ReplText);
			}
		}
		else
		{
			ReplaceSel(ReplText);
			TextLen++;
		}

		m_DOflags=(m_DOflags&0xFFFFFF00)|iChar;
		ret=TextLen;
	}
	return ret;
}

int GPEdit::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message) 
{
	int ret=CEdit::OnMouseActivate(pDesktopWnd, nHitTest, message);
	if (m_bAutoFocus && ::GetFocus()!=m_hWnd)
		::PostMessage(m_hWnd,GPM_SETFOCUSTOWND,(WPARAM)m_hWnd,0);
	return ret;
}

DWORD GPEdit::GetCRC16forText()
{
	int nnn=::GetWindowTextLength(m_hWnd);
	char *tmpstr=new char [nnn+100];
	if (nnn) nnn=::GetWindowText(m_hWnd,tmpstr,nnn+2);
	DWORD ret=0;
	int i;
	for(i=0;i<nnn;i++)
			calc_CRC16(GPC.tcrc16, &ret,tmpstr[i]);

	delete[] tmpstr;
    return ret;
}

DWORD GPEdit::GetTextLength()
{
	DWORD ret=0;
	int nLines=GetLineCount();
	int i;
	for(i=0;i<nLines;i++)
		ret+=::SendMessage(m_hWnd, EM_LINELENGTH, ::SendMessage(m_hWnd, EM_LINEINDEX, i,0),0);

	ret+=(nLines-1)*2;
	return ret;
}

void GPEdit::SetDefSel()
{
	switch(m_dwTextMode&0xF)
	{
	case 0:
		SetSel(0,0);
		break;
	case 1:
		SetSel(-1,-1);
		break;
	case 2:
		SetSel(0,-1);
		break;
	default:
		break;
	}
}
