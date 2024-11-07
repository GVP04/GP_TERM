// GPWindow.cpp: implementation of the GPWindow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GP_term.h"
#include "GPUnit.h"
#include "GPWindow.h"
#include "GP_TermView.h"
#include "GP_DlgSetting.h"
#include "ODContextItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const UINT GPWindow::uNMethods=74;
const char *GPWindow::cArrMethods[]={
/*00*/		"AddLayer","DeleteLayer","DeleteAllLayers","SetLayerStyle","Invalidate",
/*05*/		"RedrawWnd","SetBkgColor","GetBkgColor","SetFrgColor","GetFrgColor",
/*10*/		"SetChrStyle","GetChrStyle","ModifyChrStyle","GetWindowSize","GetMethods",
/*15*/		"GetWindowRect","DrawCharRect","DrawCharLine","FillCharRect","CharShadow",
/*20*/		"SetExPerfixPosition","GetNearestChars","CharOutW","CharOutAW","InsertChar",
/*25*/		"DelChar","LoadScrRgn","GetScrScrollState","SetScrScrollState","LineOut",
/*30*/		"GetCursorState","SetCursorState","SetChrSpace","GetChrSpace","SetChrColorIndex",
/*35*/		"SetBkgColorIndex","GetChrColorIndex","GetBkgColorIndex","SetReverseVideo","GetReverseVideo",
/*40*/		"ClearEndOfWindow","ClearEndOfLine","CursorMoveCR","CursorMoveLF","SetCursorPosition",
/*45*/		"GetCursorPosition","CursorMoveUp","CursorMoveDown","CursorMoveRight","CursorMoveLeft",
/*50*/		"ScrollDown","ScrollUp","ScrollLeft","ScrollRight","GetWindowContent",
/*55*/		"SetWindowContent","RedrawRect","DelLine","InsertLine","WndSetState",
/*60*/		"WndForward","WndBackward","SelectWindow","ClearWindow","GetBlinkPoints",
/*65*/		"RepaintRect","WndGetState","ModifyBkgColor","ModifyFrgColor","ModifyTermCmdMask",
/*70*/		"ClearToBeginOfLine","CharOutGRUC","SetInsertMode","GetInsertMode","",
/*85*/		"","","","","",
/*90*/		"","","","","",
/*95*/		"","","","","",
	};

const char *GPWindow::cArrMethodsParams[]={
/*00*/		"LayerName,ODCName[,LayerBefore[,Style=VISIBLE|BKG]]","LayerName[,bRemoveODC=1]","[Style]"," LayerName,Style","[X,Y,CX,CY]",
/*05*/		"[X,Y,CX,CY]","color[;X,Y,CX,CY]","","color[;X,Y,CX,CY]","",
/*10*/		"Style[,X,Y,CX,CY]","","StyleToDelete[,[StyleToAdd][,X,Y,CX,CY]]","","[Type]",
/*15*/		"","X,Y,Width,Height[,CharOrType]","X1,Y1,X2,Y2[,CharOrType]","X,Y,Width,Height,CharCode","X,Y,Width,Height,ScaleFrg[,ScaleBkg]",
/*20*/		"[X,Y]","[X,Y]","[X],[Y],CharCode1[,CharCode2[,CharCode3[,...]]]","[X],[Y],CharCode1[,CharCode2[,CharCode3[,...]]]","[X],[Y][,nTimes[,CharCode]]",
/*25*/		"[X],[Y][,nTimes]","SaveID,X,Y","","State","[X][,Y];CharLine",
/*30*/		"","State","CharCode","","Index",
/*35*/		"Index","","","dwFlags","",
/*40*/		"","","[nTimes]","[nTimes]","[X],[Y]",
/*45*/		"","[nTimes]","[nTimes]","[nTimes]","[nTimes]",
/*50*/		"[nTimes]","[nTimes]","[nTimes]","[nTimes]","Type[,X,Y,CX,CY]",
/*55*/		"Type[,X,Y,CX,CY];[Frg];[Bkg];[Styles];[Chars]","[X,Y,CX,CY]","[nLine][,nTimes]","[nLine][,nTimes]","State",
/*60*/		"","","","","",
/*65*/		"[X,Y[,CX,CY]]","","[R],[G],[B],[A]","[R],[G],[B],[A]","[MaskToDelete][,MaskToAdd]",
/*70*/		"","UCode","","","",
/*85*/		"","","","","",
/*90*/		"","","","","",
/*95*/		"","","","","",
	};


GPWindow::GPWindow(GPScreen *iScrParent,UINT iWndId, Size &iWindowSize,Rect &iWindowViewRect, UINT iGPWndState, UINT iChrStyle, DWORD dwOldCommandMask_IN)
{
	m_dwFlags=0;
	dwOldCommandMask=dwOldCommandMask_IN;
	ReverseColorFlag=FALSE;
	ChrColor= GPC.DefFrgColor; // цвет символов
	BkgColor= GPC.DefBkgColor;  // свет фона
	ChrColorInd= GPC.DefFrgColorInd; // цвет символов
	BkgColorInd= GPC.DefBkgColorInd;  // свет фона
	BkgMode=OPAQUE;

	ZeroMemory(ArrLayers,sizeof(PODCLAYERINFO)*MAX_LAYERS);
	if (iWndId && iScrParent)
	{
		m_CompositingQuality=	iScrParent->aGPWindow[0]->m_CompositingQuality;
		m_InterpolationMode=	iScrParent->aGPWindow[0]->m_InterpolationMode;
		m_PixelOffsetMode=		iScrParent->aGPWindow[0]->m_PixelOffsetMode;
		m_SmoothingMode=		iScrParent->aGPWindow[0]->m_SmoothingMode;
		m_TextContrast=			iScrParent->aGPWindow[0]->m_TextContrast;
		m_TextRenderingHint=	iScrParent->aGPWindow[0]->m_TextRenderingHint;
		m_Language=				iScrParent->aGPWindow[0]->m_Language;
		m_SubLanguage=			iScrParent->aGPWindow[0]->m_SubLanguage;
		m_CurCodePage=			iScrParent->aGPWindow[0]->m_CurCodePage;
	}
	else
	{
		m_CompositingQuality=GPC.m_CompositingQuality;
		m_InterpolationMode= GPC.m_InterpolationMode;
		m_PixelOffsetMode=	 GPC.m_PixelOffsetMode;
		m_SmoothingMode=	 GPC.m_SmoothingMode;
		m_TextContrast=		 GPC.m_TextContrast;
		m_TextRenderingHint= GPC.m_TextRenderingHint;
		m_Language=			 GPC.m_Language;
		m_SubLanguage=		 GPC.m_SubLanguage;
		m_CurCodePage=		 CP_ACP;
	}

	ScrParent=iScrParent;
	m_NGPUNITmax=500;
// Создание текстового окна где:
// GPWindow::GPWindow(UINT iWndId, Size iWindowSize,Rect iWindowViewRect, UINT iGPWndState, UINT iChrStyle)
// iWndId         - идентификатор
// iWindowSize     - размеры окна
// iWindowViewRect - размеры видимой области окна
// iGPWndState    - Состояние
// iChrStyle      - стиль символов
	m_CDlgDialogEditor=NULL;
	m_NextMBOutChar=0;
	m_LastPrefix=0;
	m_ProtectedModeFlag=0;
	m_ProtectedFieldModeFlag=0;
	m_PrefixPosition=0;
	m_PrefixPositionEx=0;
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwCreateWnd++;
	WndId=iWndId;
	CursorVisible=TRUE;
	ChrSpace=' ';  // пробельный символ
	WindowSize=iWindowSize; // размеры окна
	GPWndState=iGPWndState; // Состояние активно/неактивно
	GPWndViewOfset.X=0;
	ScrollWnd=TRUE;
	WaitScroll=FALSE;
	GPWndViewOfset.Y=0;
	if (WindowSize.Width<=0) WindowSize.Width=80;
	if (WindowSize.Height<=0) WindowSize.Height=25;
	if (WindowSize.Width>16384) WindowSize.Width=80;
	if (WindowSize.Height>16384) WindowSize.Height=25;
	WindowViewRect=iWindowViewRect; // размеры видимой области и позиция в экране
	if (WindowViewRect.Width>WindowSize.Width || WindowViewRect.Width==0) WindowViewRect.Width=WindowSize.Width; 
	if (WindowViewRect.Height>WindowSize.Height || WindowViewRect.Height==0) WindowViewRect.Height=WindowSize.Height; 
	
	cursor.Y=cursor.X=0;	// позиция курсора
	ChrStyle=iChrStyle;	// стиль символов


	nall=WindowSize.Width*WindowSize.Height;
	

	m_NGPUNITmax=NINITIALUNITS;
	WndUnit= new GPUnit * [NINITIALUNITS];
	ZeroMemory(WndUnit,sizeof(GPUnit *)*NINITIALUNITS);

	WndUnit[0]	=new GPUnit(0,0,"",WndUnit,&GPC.m_ScrToolTip,GPC.m_hViewWnd,GPC.m_View->m_AUSI);
	WndChrRGB	=new UINT [nall];
	WndChar		=new unsigned short [nall];
	WndBkgRGB	=new UINT [nall];
	WndChrStyle	=new UINT [nall];
	WndTabStops =new char [WindowSize.Width];
	ZeroMemory(WndTabStops,WindowSize.Width);
	SetTABStopPos(5);
	
	ClearWnd();
}

GPWindow::~GPWindow()
{
	try
	{
		if (m_CDlgDialogEditor!=NULL)
		{
			m_CDlgDialogEditor->DestroyWindow();
			delete m_CDlgDialogEditor;
		}
	}catch(...)
	{
			GPC.m_ErrReport.GPWriteErrorLog("GPWindow", "~GPWindow 87","");
	}
	m_CDlgDialogEditor=NULL;

	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwDeleteWnd++;
	if (WndChrRGB	!=NULL) delete[] WndChrRGB;
	WndChrRGB=NULL;
	if (WndChar		!=NULL) delete[] WndChar;
	WndChar=NULL;
	if (WndBkgRGB	!=NULL) delete[] WndBkgRGB;
	WndBkgRGB=NULL;
	if (WndChrStyle	!=NULL) delete[] WndChrStyle;
	WndChrStyle=NULL;
	if (WndTabStops	!=NULL) delete[] WndTabStops;
	WndTabStops=NULL;
	int i;
	if (WndUnit)
	{
		if (*WndUnit)
		for(i=1;(UINT)i<(*WndUnit)->m_NGPUNIT;i++) 
			if (WndUnit[i]) 
			try
			{delete WndUnit[i];WndUnit[i]=NULL;}
			catch(...)
			{
				GPC.m_ErrReport.GPWriteErrorLog("GPWindow", "~GPWindow 104","");
				WndUnit[i]=NULL;
			}

		if (*WndUnit) {delete *WndUnit;*WndUnit=NULL;}
		delete[] WndUnit;
	}
	DeleteLayers();
}

PODCLAYERINFO GPWindow::GetLayer(const char *iName)
{
	PODCLAYERINFO ret=NULL;
	DWORD dwNum=GetLayerNum(iName);
	if (dwNum<MAX_LAYERS) ret=ArrLayers[dwNum];
	return ret;
}

DWORD GPWindow::GetLayerNum(const char *iName)
{
	DWORD ret=-1;
	int i;
	if (iName && *iName)
		for(i=0;i<MAX_LAYERS && ret>MAX_LAYERS;i++) 
			if (ArrLayers[i] && ArrLayers[i]->csName==iName) ret=i;
	return ret;
}
void GPWindow::AddLayer(const char *iName, const char *iODCName, DWORD dwStyle, const char *iNameBefore)
{
	DeleteLayer(iName,0);
	DWORD dwNewId=GetLayerNum(iNameBefore);
	if (dwNewId<MAX_LAYERS) 
	{
		DWORD tmpId=MAX_LAYERS;
		while(--tmpId>dwNewId) ArrLayers[tmpId]=ArrLayers[tmpId-1];
		if (++tmpId==MAX_LAYERS) delete ArrLayers[--tmpId];

	}
	else
	{
		dwNewId=MAX_LAYERS;
		while(--dwNewId<MAX_LAYERS && !ArrLayers[dwNewId]);
		dwNewId++;
		if (dwNewId==MAX_LAYERS) delete ArrLayers[--dwNewId];
	}

	ArrLayers[dwNewId]=new ODCLAYERINFO;
	ArrLayers[dwNewId]->dwStyle=dwStyle;
	ArrLayers[dwNewId]->csName=iName;
	ArrLayers[dwNewId]->csContextName=iODCName;

	ArrLayers[dwNewId]->pContext=GPC.m_View->m_ODContextsArray->GetContext(ArrLayers[dwNewId]->csContextName);
	if (ArrLayers[dwNewId]->pContext->m_ContextName!=ArrLayers[dwNewId]->csContextName)
		ArrLayers[dwNewId]->pContext=NULL;

}

void GPWindow::DeleteLayer(const char *iName, DWORD dwType)
{
	DWORD dwId=GetLayerNum(iName);
	if (dwId<MAX_LAYERS)
	{
		delete ArrLayers[dwId];
		while(++dwId<MAX_LAYERS)
			ArrLayers[dwId-1]=ArrLayers[dwId];
		ArrLayers[dwId-1]=NULL;
	}
}

void GPWindow::DeleteLayers(DWORD dwStyle)
{
	int i;
	for(i=0;i<MAX_LAYERS;i++) 
	{
		if (ArrLayers[i] && (dwStyle==0 ||  (ArrLayers[i]->dwStyle&dwStyle)==dwStyle))
		{
			if (GPC.m_View && GPC.m_View->m_ODContextsArray && (ArrLayers[i]->dwStyle&ODCL_SHAREODC)!=ODCL_SHAREODC)
				GPC.m_View->m_ODContextsArray->DeleteContext(ArrLayers[i]->csContextName);
			delete ArrLayers[i];
		}
	}
	ZeroMemory(ArrLayers,sizeof(PODCLAYERINFO)*MAX_LAYERS);
}


DWORD GPWindow::CompileLayerStyle(const char *ccStile)
{
	DWORD dwLStyle=ODCL_VISIBLE|ODCL_BKG;
	if (ccStile && *ccStile)
	{
		CString csTmp=ccStile;
		dwLStyle=0;
		csTmp.MakeUpper();
		csTmp.Replace(" ","");
		csTmp+="|";
		if (csTmp.Find("VISIBLE|")>=0) dwLStyle|=ODCL_VISIBLE;
		if (csTmp.Find("FRG")>=0) dwLStyle|=ODCL_FRG;
		else
		if (csTmp.Find("BKG")>=0) dwLStyle|=ODCL_BKG;
		if (csTmp.Find("SHAREODC")>=0) dwLStyle|=ODCL_SHAREODC;
	}
	return dwLStyle;
}


UINT GPWindow::DoMethod(const char *iStr, char *oStr)
{
	int nfunc=0;
	char met[150];
	strncpy(met,iStr,145);
	met[145]=0;
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int retint=-123456; 
	int atoipos=atoi(pos);
	const char *pos2=pos;
	while(*pos2!=0 && *pos2!=',' && *pos2!='=') pos2++;
	if (*pos2!=0) pos2++;

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
	case  0: //AddLayer LayerName,ODCName[,LayerBefore[,Style=VISIBLE|BKG]]
		{
			DWORD dwLStyle=CompileLayerStyle(ExtractField(pos,4,","));
			AddLayer(ExtractField(pos,1,","),ExtractField(pos,2,","),dwLStyle,ExtractField(pos,3,","));
			if ((dwLStyle&ODCL_VISIBLE)==ODCL_VISIBLE) RedrawWnd();
		}
		break; 
	case  1: //DeleteLayer LayerName[,bRemoveODC=1]
		{
			const char *ccType=FindField(pos,2,",");
			DeleteLayer(ExtractField(pos,1,","),(ccType && *ccType)?atoi(ccType):1);
		}
		break; 
	case  2: //DeleteAllLayers [Style]
		{
			DWORD dwStyle=(pos && *pos)?CompileLayerStyle(pos):0;
			DeleteLayers(dwStyle);
			RedrawWnd();
		}
		break; 
	case  3: //SetLayerStyle LayerName,Style
		{
			DWORD dwStyle=CompileLayerStyle(ExtractField(pos,2,","));
			PODCLAYERINFO layer=GetLayer(ExtractField(pos,1,","));
			if (layer) 
			{
				DWORD dwOldStyle=layer->dwStyle;
				layer->dwStyle=dwStyle;
				if (((dwStyle^dwOldStyle)&ODCL_VISIBLE)==ODCL_VISIBLE) RedrawWnd();
			}
		}
		break; 
	case  4: //Invalidate [X,Y,CX,CY]
		if (*pos)
		{
			Rect re;
			sscanf(pos,"%d,%d,%d,%d",&re.X,&re.Y,&re.Width,&re.Height);
			RepaintRect(re);
		}
		else RepaintWnd();
		break; 
	case  5: //RedrawWnd [X,Y,CX,CY]
		if (*pos)
		{
			Rect re;
			sscanf(pos,"%d,%d,%d,%d",&re.X,&re.Y,&re.Width,&re.Height);
			RedrawRect(re);
		}
		else RedrawWnd();
		break; 
	case  6: // SetBkgColor color[;X,Y,CX,CY]
		{
			const char *posRect=FindField(pos,2,";");
			ARGB newColor=CODContextItem::TranlateColor(ExtractField(pos,1,";"));
			if (newColor==0x10101) newColor=GPC.DefBkgColor;
			if (posRect && *posRect)
			{
				Rect re(0,0,WindowSize.Width,WindowSize.Height);
				sscanf(posRect,"%d,%d,%d,%d",&re.X,&re.Y,&re.Width,&re.Height);
				SetBkgColor(newColor, re);
			}
			else
				SetBkgColor(newColor,0);
		}
		break; 
	case  7: // GetBkgColor
		if (oStr) 
		{
			Color clr(GetBkgColor());
			sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",clr.GetRed(),clr.GetGreen(),clr.GetBlue(),clr.GetAlpha());
		}
		break; 
	case  8: // SetFrgColor color[;X,Y,CX,CY]
		{
			const char *posRect=FindField(pos,2,";");
			ARGB newColor=CODContextItem::TranlateColor(ExtractField(pos,1,";"));
			if (newColor==0x10101) newColor=GPC.DefFrgColor;
			if (posRect && *posRect)
			{
				Rect re(0,0,WindowSize.Width,WindowSize.Height);
				sscanf(posRect,"%d,%d,%d,%d",&re.X,&re.Y,&re.Width,&re.Height);
				SetChrColor(newColor, re);
			}
			else
				SetChrColor(newColor,0);
		}
		break; 
	case  9: // GetFrgColor
		if (oStr) 
		{
			Color clr(GetChrColor());
			sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",clr.GetRed(),clr.GetGreen(),clr.GetBlue(),clr.GetAlpha());
		}
		break; 
	case  10: // SetChrStyle Style[,X,Y,CX,CY]
		{
			const char *posRect=FindField(pos,2,",");
			if (posRect && *posRect)
			{
				Rect re(0,0,WindowSize.Width,WindowSize.Height);
				sscanf(posRect,"%d,%d,%d,%d",&re.X,&re.Y,&re.Width,&re.Height);
				SetStyle(0xFFFFFFFF, GPFont::TranslateCharStyle(ExtractField(pos,1,",")), re);
			}
			else
				SetChrStyle(GPFont::TranslateCharStyle(ExtractField(pos,1,",")),0);
		}
		break; 
	case  11: // GetChrStyle
		if (oStr)
			strcpy(oStr,GPFont::TranslateCharStyle(GetChrStyle()));
		break; 
	case  12: // ModifyChrStyle StyleToDelete[,[StyleToAdd][,X,Y,CX,CY]]
		{
			const char *posRect=FindField(pos,3,",");
			if (posRect && *posRect)
			{
				Rect re(0,0,WindowSize.Width,WindowSize.Height);
				sscanf(posRect,"%d,%d,%d,%d",&re.X,&re.Y,&re.Width,&re.Height);
				SetStyle(
					GPFont::TranslateCharStyle(ExtractField(pos,1,",")),
					GPFont::TranslateCharStyle(ExtractField(pos,2,",")),
					re);
			}
			else
			{
				DWORD newStlToDelete=GPFont::TranslateCharStyle(ExtractField(pos,1,","));
				DWORD newStlToAdd=GPFont::TranslateCharStyle(ExtractField(pos,2,","));
				SetChrStyle((GetChrStyle()&(0xFFFFFFFF^newStlToDelete))|newStlToAdd,0);
			}
		}
		break; 
	case  13: // GetWindowSize
		if (oStr) sprintf(oStr,"%d\x7F%d",WindowSize.Width,WindowSize.Height);
		break; 
	case  14: // GetMethods [Type]
		if (oStr)
		{
			int i;
			char *posout=oStr;
			for(i=0;*GPWindow::cArrMethods[i];i++)
			{
				if (i) *(posout++)=0x7F;
				if (atoipos)
					posout+=sprintf(posout,"%s\x7%s",GPWindow::cArrMethods[i],GPWindow::cArrMethodsParams[i]);
				else
					posout+=sprintf(posout,"%s",GPWindow::cArrMethods[i]);
			}
		}
		break; 
	case  15: // GetWindowRect
		if (oStr) sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",WindowViewRect.X,WindowViewRect.Y,WindowViewRect.Width,WindowViewRect.Height);
		break; 
	case  16: // DrawCharRect X,Y,Width,Height[,CharOrType]
	case  17: // DrawCharLine X1,Y1,X2,Y2[,CharOrType]
	case  18: // FillCharRect X,Y,Width,Height,CharCode
	case  19: // CharShadow X,Y,Width,Height,ScaleFrg[,ScaleBkg]
		{
			Rect re(0,0,1,1);
			sscanf(pos,"%d,%d,%d,%d",&re.X,&re.Y,&re.Width,&re.Height);
			if (re.X<0) re.X=0;
			if (re.Y<0) re.Y=0;
			if (re.X+re.Width>WindowSize.Width) re.Width=WindowSize.Width-re.X;
			if (re.Y+re.Height>WindowSize.Height) re.Height=WindowSize.Height-re.Y;
			const char *tmp5=FindField(pos,5,",");
			int CharOrScale=atoi(tmp5);
			if (*tmp5=='0' && (tmp5[1]&0x1F)==('X'&0x1F))
			{
				sscanf(tmp5+2,"%X",&CharOrScale);
			}
			else
			{
				CharOrScale=(CharOrScale/100000)*0x10000+CharOrScale%100000;
			}

			switch(nfunc)
			{
			case  16: // DrawCharRect X,Y,Width,Height[,CharOrType]
				TextBox(re,CharOrScale);
				break;
			case  17: // DrawCharLine X1,Y1,X2,Y2[,CharOrType]
				if (re.Width<re.X)	re.Width=re.X-re.Width+1;
				else				re.Width=re.Width-re.X+1;
				if (re.Height<re.X)	re.Height=re.X-re.Height+1;
				else				re.Height=re.Height-re.X+1;
				TextBox(re,CharOrScale);
				break;
			case  18: // FillCharRect X,Y,Width,Height,CharCode
				{
					unsigned short tmpChr=ChrSpace;
					ChrSpace=CharOrScale;
					ClearRect(re);
					ChrSpace=tmpChr;
				}
				break;
			case  19: // CharShadow X,Y,Width,Height,ScaleFrg[,ScaleBkg]
				{
					const char *tmp6=FindField(tmp5,2,",");
					int ScaleFrg=CharOrScale;
					if (*tmp6) ScaleFrg=atoi(tmp6);
					ScaleColor(re, ScaleFrg, CharOrScale);
				}
				break;
			}
		}
		break; 
	case  20: // SetExPerfixPosition [X,Y]
		if (*pos) 
		{
			Point po=cursor;
			CString tmpCS;
			tmpCS=ExtractField(pos,1,",");
			if (tmpCS!="") po.X=atoi(tmpCS);
			tmpCS=ExtractField(pos,2,",");
			if (tmpCS!="") po.Y=atoi(tmpCS);
			m_PrefixPositionEx=po.X+po.Y*WindowSize.Width;
		}
		else SetExPerfixPosition();
		break; 
	case  21: // GetNearestChars [X,Y]
		if (oStr)
		{
			Point po=cursor;
			CString tmpCS;
			tmpCS=ExtractField(pos,1,",");
			if (tmpCS!="") po.X=atoi(tmpCS);
			tmpCS=ExtractField(pos,2,",");
			if (tmpCS!="") po.Y=atoi(tmpCS);
			NEAREST9X9 ne;
			ne.X=po.X;
			ne.Y=po.Y;
			GetNearestChars(&ne);
			sprintf(oStr,"%d\x7%d\x7%d\x7F%d\x7%d\x7%d\x7F%d\x7%d\x7%d",
				ne.topleft,ne.top,ne.topright,
				ne.left,ne.center,ne.right,
				ne.bottomleft,ne.bottom,ne.bottomright);
		}
		break; 
	case  22: // CharOutW [X],[Y],CharCode1[,CharCode2[,CharCode3[,...]]]
		{
			Point po=cursor;
			CString tmpCS;
			tmpCS=ExtractField(pos,1,",");
			if (tmpCS!="") po.X=atoi(tmpCS);
			tmpCS=ExtractField(pos,2,",");
			if (tmpCS!="") po.Y=atoi(tmpCS);

			const char *poschar=FindField(pos,3,",");
			UINT tmpposition=po.X+po.Y*WindowSize.Width;
			if (*poschar=='0' && (poschar[1]=='x' || poschar[1]=='X'))
			{
				poschar+=2;
				while(*poschar && tmpposition<nall)
				{
					unsigned short ch0=0;
					int i;
					for(i=0;i<4;i++)
						if (*poschar)
						{
							unsigned short chx=*(poschar++);
							if (chx>='A' && chx<='F') chx-=('A'+10);
							else
							if (chx>='a' && chx<='f') chx-=('a'+10);
							else
							if (chx>='0' && chx<='9') chx-='0';
							else chx=0;

							ch0=ch0*0x10+chx;
						}
					CharOut(tmpposition++,ch0);
					if (*poschar) poschar++;
				}
			}
			else
			while(*poschar && tmpposition<nall)
			{
				unsigned short ch=atoi(poschar);
				CharOut(tmpposition++,ch);
				while(*poschar && *poschar!=',') poschar++;
				if (*poschar) poschar++;
			}
		}
		break; 
	case  23: // CharOutAW [X],[Y],CharCode1[,CharCode2[,CharCode3[,...]]]
		{
			Point po=cursor;
			CString tmpCS;
			tmpCS=ExtractField(pos,1,",");
			if (tmpCS!="") po.X=atoi(tmpCS);
			tmpCS=ExtractField(pos,2,",");
			if (tmpCS!="") po.Y=atoi(tmpCS);

			const char *poschar=FindField(pos,3,",");
			UINT tmpposition=po.X+po.Y*WindowSize.Width;
			if (*poschar=='0' && (poschar[1]=='x' || poschar[1]=='X'))
			{
				poschar+=2;
				while(*poschar && tmpposition<nall)
				{
					char ch0=0;
					int i;
					for(i=0;i<4;i++)
						if (*poschar)
						{
							char chx=*(poschar++);
							if (chx>='A' && chx<='F') chx-=('A'+10);
							else
							if (chx>='a' && chx<='f') chx-=('a'+10);
							else
							if (chx>='0' && chx<='9') chx-='0';
							else chx=0;

							ch0=ch0*0x10+chx;
						}
					CharOutAW(tmpposition++,ch0);
					if (*poschar) poschar++;
				}
			}
			else
			while(*poschar && tmpposition<nall)
			{
				char ch=atoi(poschar);
				CharOutAW(tmpposition++,ch);
				while(*poschar && *poschar!=',') poschar++;
				if (*poschar) poschar++;
			}
		}
		break; 
	case  24: // InsertChar [X],[Y][,nTimes[,CharCode]]
		{
			Point po=cursor;
			UINT nTimes=1;
			CString tmpCS;
			tmpCS=ExtractField(pos,1,",");
			if (tmpCS!="") po.X=atoi(tmpCS);
			tmpCS=ExtractField(pos,2,",");
			if (tmpCS!="") po.Y=atoi(tmpCS);
			tmpCS=ExtractField(pos,3,",");
			if (tmpCS!="") nTimes=atoi(tmpCS);
			if (nTimes>=nall) nTimes=nall;
			if (nTimes>0)
			{
				const char *poscode=FindField(pos,4,",");
				unsigned short ch=ChrSpace;
				if (*poscode)
				{
					if (*poscode=='0' && (poscode[1]=='x' || poscode[1]=='X'))
						sscanf(poscode+2,"%X",&ch);
					else ch=atoi(poscode);
				}
				while(nTimes-->0)
				{
					InsertChar(po);
					CharOut(po,ch);
				}
			}
		}
		break; 
	case  25: // DelChar [X],[Y][,nTimes]
		{
			Point po=cursor;
			UINT nTimes=1;
			CString tmpCS;
			tmpCS=ExtractField(pos,1,",");
			if (tmpCS!="") po.X=atoi(tmpCS);
			tmpCS=ExtractField(pos,2,",");
			if (tmpCS!="") po.Y=atoi(tmpCS);
			tmpCS=ExtractField(pos,3,",");
			if (tmpCS!="") nTimes=atoi(tmpCS);
			if (nTimes>=nall) nTimes=nall;
			while(nTimes-->0)
				DelChar(po);
		}
		break; 
	case  26: // LoadScrRgn SaveID,X,Y
		{
			Point po(0,0);
			sscanf(FindField(pos,2,","),"%d,%d",&po.X,&po.Y);
			LoadScrRgn(ExtractField(pos,1,","),po);
		}
		break; 
	case  27: // GetScrScrollState 
		retint=WaitScroll;
		break; 
	case  28: // SetScrScrollState State
		retint=WaitScroll;
		WaitScroll=atoipos;
		break; 
	case  29: // LineOut [X][,Y];CharLine
		{
			Point po=cursor;
			CString tmpCS;
			tmpCS=ExtractField(pos,1,",");
			if (tmpCS!="") po.X=atoi(tmpCS);
			tmpCS=ExtractField(pos,2,",");
			if (tmpCS!="") po.Y=atoi(tmpCS);
			SetCursorPosition(po);

			const char *poschar=FindField(pos,2,";");
			while(*poschar)
				CharOut(*(poschar++));
		}
		break; 
	case  30: // GetCursorState
		retint=CursorVisible;
		break; 
	case  31: // SetCursorState State
		retint=CursorVisible;
		CursorVisible=atoipos;
		break; 
	case  32: // SetChrSpace CharCode
		if (*pos)
		{
			if (*pos=='0' && (pos[1]=='x' || pos[1]=='X'))
				sscanf(pos+2,"%X",&ChrSpace);
			else ChrSpace=atoi(pos);

		}
		else ChrSpace=' ';
		break; 
	case  33: // GetChrSpace 
		retint=ChrSpace;
		break; 
	case  34: // SetChrColorIndex Index
		retint=SetChrColorIndex(atoipos,0);
		break; 
	case  35: // SetBkgColorIndex Index
		retint=SetBkgColorIndex(atoipos,0);
		break; 
	case  36: // GetChrColorIndex
		retint=GetChrColorIndex();
		break; 
	case  37: // GetBkgColorIndex 
		retint=GetBkgColorIndex();
		break; 
	case  38: // SetReverseVideo dwFlags
		retint=SetReverseVideo(atoipos,0);
		break; 
	case  39: // GetReverseVideo 
		retint=GetReverseVideo();
		break; 
	case  40: // ClearEndOfWindow
		ClearEndOfWnd();
		break; 
	case  41: // ClearEndOfLine
		ClearEndOfLine();
		break; 
	case  42: // CursorMoveCR [nTimes]
		if (atoipos<=0) atoipos=1;
		if (atoipos>1000) atoipos=WindowSize.Height;
		while(atoipos-->0)
		{
			int nTimes=atoipos;
			CursorMoveCR();
		}
		break; 
	case  43: // CursorMoveLF [nTimes]
		if (atoipos<=0) atoipos=1;
		if (atoipos>1000) atoipos=WindowSize.Height;
		while(atoipos-->0)
		{
			int nTimes=atoipos;
			CursorMoveLF();
		}
		break; 
	case  44: // SetCursorPosition [X],[Y]
		{
			Point po=cursor;
			CString tmpCS;
			tmpCS=ExtractField(pos,1,",");
			if (tmpCS!="") po.X=atoi(tmpCS);
			tmpCS=ExtractField(pos,2,",");
			if (tmpCS!="") po.Y=atoi(tmpCS);
			SetCursorPosition(po);
		}
		break; 
	case  45: // GetCursorPosition
		if (oStr) sprintf(oStr,"%d\x7F%d",cursor.X,cursor.Y);
		break; 
	case  46: // CursorMoveUp [nTimes]
		if (atoipos<=0) atoipos=1;
		if (atoipos>1000) atoipos=WindowSize.Height;
		while(atoipos-->0)
		{
			int nTimes=atoipos;
			CursorMoveUp();
		}
		break; 
	case  47: // CursorMoveDown [nTimes]
		if (atoipos<=0) atoipos=1;
		if (atoipos>1000) atoipos=WindowSize.Height;
		while(atoipos-->0)
		{
			int nTimes=atoipos;
			CursorMoveDown();
		}
		break; 
	case  48: // CursorMoveRight [nTimes]
		if (atoipos<=0) atoipos=1;
		if (atoipos>1000) atoipos=WindowSize.Height;
		while(atoipos-->0)
		{
			int nTimes=atoipos;
			CursorMoveRight();
		}
		break; 
	case  49: // CursorMoveLeft [nTimes]
		if (atoipos<=0) atoipos=1;
		if (atoipos>1000) atoipos=WindowSize.Height;
		while(atoipos-->0)
		{
			int nTimes=atoipos;
			CursorMoveLeft();
		}
		break; 
	case  50: // ScrollDown [nTimes]
		if (atoipos<=0) atoipos=1;
		if (atoipos>1000) atoipos=WindowSize.Height;
		while(atoipos-->0)
		{
			int nTimes=atoipos;
			ScrollDown();
		}
		break; 
	case  51: // ScrollUp [nTimes]
		if (atoipos<=0) atoipos=1;
		if (atoipos>1000) atoipos=WindowSize.Height;
		while(atoipos-->0)
		{
			int nTimes=atoipos;
			ScrollUp();
		}
		break; 
	case  52: // ScrollLeft [nTimes]
		if (atoipos<=0) atoipos=1;
		if (atoipos>1000) atoipos=WindowSize.Height;
		while(atoipos-->0)
		{
			int nTimes=atoipos;
			ScrollLeft();
		}
		break; 
	case  53: // ScrollRight [nTimes]
		if (atoipos<=0) atoipos=1;
		if (atoipos>1000) atoipos=WindowSize.Height;
		while(atoipos-->0)
		{
			int nTimes=atoipos;
			ScrollRight();
		}
		break; 
	case  54: // GetWindowContent Type[,X,Y,CX,CY]
	case  55: // SetWindowContent Type[,X,Y,CX,CY];[Frg];[Bkg];[Style];[Chars]
		{
			CString csPart1=ExtractField(pos,1,";");
			CString csType=ExtractField(csPart1,1,",");
			Rect re(0,0,WindowSize.Width,WindowSize.Height);

			CString tmpCS;
			tmpCS=ExtractField(csPart1,2,",");
			if (tmpCS!="") re.X=atoi(tmpCS);
			tmpCS=ExtractField(csPart1,3,",");
			if (tmpCS!="") re.Y=atoi(tmpCS);
			tmpCS=ExtractField(csPart1,4,",");
			if (tmpCS!="") re.Width=atoi(tmpCS);
			tmpCS=ExtractField(csPart1,5,",");
			if (tmpCS!="") re.Height=atoi(tmpCS);
			re.Intersect(Rect(0,0,WindowSize.Width,WindowSize.Height));
			
			if (re.IsEmptyArea()) retint=0;
			else 
			{
				DWORD dwnAll=re.Width*re.Height;
				ARGB *Frg=NULL,*Bkg=NULL;
				DWORD *dwStyles=NULL;
				unsigned short *usChars=NULL;
				csPart1.MakeUpper();
				//FOREGROUND
				if (csPart1.Find('F')>=0) { Frg=new ARGB[dwnAll+re.Width]; ZeroMemory(Frg,sizeof(ARGB)*dwnAll);}
				//BACKGROUND
				if (csPart1.Find('B')>=0) { Bkg=new ARGB[dwnAll+re.Width]; ZeroMemory(Bkg,sizeof(ARGB)*dwnAll);}
				//STYLES
				if (csPart1.Find('T')>=0) { dwStyles=new DWORD[dwnAll+re.Width]; ZeroMemory(dwStyles,sizeof(DWORD)*dwnAll);}
				//CHARS
				if (csPart1.Find('H')>=0) { usChars=new unsigned short[dwnAll+re.Width]; ZeroMemory(usChars,sizeof(unsigned short)*dwnAll);}
				DWORD dwRet=0;

				if (nfunc==54 && oStr)
				{
					dwRet=GetWindowContent(re, Frg, Bkg, dwStyles, usChars);
					if ((dwRet&0xFFFF) && (dwRet&0xFFFF0000))
					{
						char *posout=oStr;
						DWORD i;
						posout+=sprintf(posout,"%d\x7F%d\x7%d\x7F",dwnAll,re.Width,re.Height);
						if (Frg)
							for(i=0;i<dwnAll;i++)
							{
								if (i) {*(posout++)=0x7;*posout=0;}
								posout+=sprintf(posout,"%X",Frg[i]);
							}
						*(posout++)=0x7F;*posout=0;
						if (Bkg)
							for(i=0;i<dwnAll;i++)
							{
								if (i) {*(posout++)=0x7;*posout=0;}
								posout+=sprintf(posout,"%X",Bkg[i]);
							}
						*(posout++)=0x7F;*posout=0;
						if (dwStyles)
							for(i=0;i<dwnAll;i++)
							{
								if (i) {*(posout++)=0x7;*posout=0;}
								posout+=sprintf(posout,"%X",dwStyles[i]);
							}
						*(posout++)=0x7F;*posout=0;
						if (usChars)
							for(i=0;i<dwnAll;i++)
							{
								if (i) {*(posout++)=0x7;*posout=0;}
								posout+=sprintf(posout,"%X",usChars[i]);
							}
					}
				}
				if (nfunc==55) //SetWindowContent Type[,X,Y,CX,CY];[Frg];[Bkg];[Style];[Chars]
				{
					if (Frg)
					{
						const char *ccpos=FindField(pos,2,";");
						DWORD tmpCount=0;
						while(tmpCount<dwnAll && *ccpos && *ccpos!=';')
						{
							sscanf(ccpos,"%X",Frg+(tmpCount++));
							while(*ccpos && *ccpos!=',' && *ccpos!=';') ccpos++;
							if (*ccpos==',') ccpos++;
						}
					}
					if (Bkg)
					{
						const char *ccpos=FindField(pos,3,";");
						DWORD tmpCount=0;
						while(tmpCount<dwnAll && *ccpos && *ccpos!=';')
						{
							sscanf(ccpos,"%X",Bkg+(tmpCount++));
							while(*ccpos && *ccpos!=',' && *ccpos!=';') ccpos++;
							if (*ccpos==',') ccpos++;
						}
					}
					if (dwStyles)
					{
						const char *ccpos=FindField(pos,4,";");
						DWORD tmpCount=0;
						while(tmpCount<dwnAll && *ccpos && *ccpos!=';')
						{
							sscanf(ccpos,"%X",dwStyles+(tmpCount++));
							while(*ccpos && *ccpos!=',' && *ccpos!=';') ccpos++;
							if (*ccpos==',') ccpos++;
						}
					}
					if (usChars)
					{
						const char *ccpos=FindField(pos,5,";");
						DWORD tmpCount=0;
						while(tmpCount<dwnAll && *ccpos && *ccpos!=';')
						{
							sscanf(ccpos,"%X",usChars+(tmpCount++));
							while(*ccpos && *ccpos!=',' && *ccpos!=';') ccpos++;
							if (*ccpos==',') ccpos++;
						}
					}
					dwRet=SetWindowContent(re, Frg, Bkg, dwStyles, usChars);
				}
				if (Frg) delete []Frg;
				if (Bkg) delete []Bkg;
				if (dwStyles) delete []dwStyles;
				if (usChars) delete []usChars;
			}
		}
		break; 
	case  56: // RedrawRect [X,Y,CX,CY]
		{
			Rect re(0,0,WindowSize.Width,WindowSize.Height);
			CString tmpCS;
			tmpCS=ExtractField(pos,1,",");
			if (tmpCS!="") re.X=atoi(tmpCS);
			tmpCS=ExtractField(pos,2,",");
			if (tmpCS!="") re.Y=atoi(tmpCS);
			tmpCS=ExtractField(pos,3,",");
			if (tmpCS!="") re.Width=atoi(tmpCS);
			tmpCS=ExtractField(pos,4,",");
			if (tmpCS!="") re.Height=atoi(tmpCS);
			RedrawRect(re);
		}
		break; 
	case  57: // DelLine [nLine][,nTimes]
		{
			int posScr=*pos?atoi(pos):cursor.Y;
			int nTimes=atoi(FindField(pos,2,","));
			if (nTimes>WindowSize.Height) nTimes=WindowSize.Height-1;
			while(nTimes-->0)
				DelLine(posScr);
		}
		break; 
	case  58: // InsertLine [nLine][,nTimes]
		{
			int posScr=*pos?atoi(pos):cursor.Y;
			int nTimes=atoi(FindField(pos,2,","));
			if (nTimes>WindowSize.Height) nTimes=WindowSize.Height-1;
			while(nTimes-->0)
				InsertLine(posScr);
		}
		break; 
	case  59: // WndSetState State
		{
			DWORD dwState=atoipos;
			if (*pos=='0' && (pos[1]=='X' || pos[1]=='x)'))
				sscanf(pos+2,"%X",&dwState);
			SetViewState(dwState);
		}
		break; 
	case  60: // WndForward
		ScrParent->WndForwardOne(WndId);
		break; 
	case  61: // WndBackward
		ScrParent->WndBackward(WndId);
		break; 
	case  62: // SelectWindow
		ScrParent->SelectWindow(WndId);
		break; 
	case  63: // ClearWindow
		ClearWnd();
		break; 
	case  64: // GetBlinkPoints
		if (oStr)
		{
			DWORD i=nall;
			char *posout=oStr;
			while(i)
				*(posout++)=((WndChrStyle[i--]&GP_FNT_BLINK)==GP_FNT_BLINK)?'1':'0';
			*posout=0;
		}
		break; 
	case  65: // RepaintRect [X,Y[,CX,CY]]
		{
			Rect re(0,0,WindowSize.Width,WindowSize.Height);
			CString tmpCS;
			tmpCS=ExtractField(pos,1,",");
			if (tmpCS!="") re.X=atoi(tmpCS);
			tmpCS=ExtractField(pos,2,",");
			if (tmpCS!="") re.Y=atoi(tmpCS);
			tmpCS=ExtractField(pos,3,",");
			if (tmpCS!="") re.Width=atoi(tmpCS);
			tmpCS=ExtractField(pos,4,",");
			if (tmpCS!="") re.Height=atoi(tmpCS);
			RepaintRect(re);
		}
		break; 
	case  66: // WndGetState 
		if (oStr) sprintf(oStr,"%X",GPWndState);
		break; 
	case  67: // ModifyBkgColor [R],[G],[B],[A]
	case  68: // ModifyFrgColor [R],[G],[B],[A]
		{
			ARGB tmpc=(nfunc==68)?GetChrColor():GetBkgColor();
			Color tmpcolor;
			if ((tmpc&0xFF000000)) tmpcolor.SetValue(tmpc); else tmpcolor.SetFromCOLORREF(tmpc);
			BYTE cl[]={tmpcolor.GetRed(),tmpcolor.GetGreen(),tmpcolor.GetBlue(),tmpcolor.GetAlpha()};

			const char *posColor;
			int i;
			for(i=0;i<4;i++)
			{
				posColor=FindField(pos,i+1,",");
				if (posColor && *posColor && *posColor!=' ' && *posColor!=',')
					cl[i]=atoi(posColor);
			}

			tmpc=MAKEARGB(cl[3],cl[0],cl[1],cl[2]);
			if (nfunc==68) SetChrColor(tmpc,0); else SetBkgColor(tmpc,0);
		}
		break; 
	case 69: // ModifyTermCmdMask [MaskToDelete][,MaskToAdd]
		{
			if (oStr) GPScreen::TranslateScrCmdMask(oStr, dwOldCommandMask);
			dwOldCommandMask&=(0xFFFFFFFF^GPScreen::TranslateScrCmdMask(ExtractField(pos,1,",")));
			dwOldCommandMask|=GPScreen::TranslateScrCmdMask(ExtractField(pos,2,","));
		}
		break; 
	case 70: // ClearToBeginOfLine
		ClearToBeginOfLine();
		break; 

	case 71: // CharOutGRUC UCode
		{
			int CharCode=atoi(pos);
			if (*pos=='0' && (pos[1]&0x1F)==('X'&0x1F))
				sscanf(pos+2,"%X",&CharCode);
			CharOutGRUC(CharCode);
		}
		break; 
	case  72: // SetInsertMode
		retint=SetInsertMode(atoipos);
		break; 
	case  73: // GetInsertMode bOnOff
		retint=GetInsertMode();
		break; 

	default:
		if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);
		nfunc=0xFFFFFFFFL;
		break;
	}
	if (oStr && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);

	return nfunc;
}

BOOL GPWindow::SetInsertMode(BOOL bOnOff)
{
	BOOL ret=(m_dwFlags&GP_WND_FM_INSERT)!=0;
	if (bOnOff) m_dwFlags|=GP_WND_FM_INSERT;
	else		m_dwFlags&=(0xFFFFFFFF^GP_WND_FM_INSERT);
	return ret;
}

BOOL GPWindow::GetInsertMode()
{
	return (m_dwFlags&GP_WND_FM_INSERT)!=0;
}

void GPWindow::ClearWnd()
{
	UINT i;
	DeleteAllObjects();

	if ((m_ProtectedModeFlag&GP_FNT_FIXED)==GP_FNT_FIXED)
	{
		for(i=0;i<nall;i++)
			if ((WndChrStyle[i]&GP_FNT_FIXED)!=GP_FNT_FIXED)
				WndChar[i]=ChrSpace;
		RedrawWnd();
	}
	else
	{
		DWORD mask=(0xFFFFFFFF^GP_FNT_FIXED);
		for(i=0;i<nall;i++) 
		{
			WndChrStyle[i]&=mask;
			CharOut(i,ChrSpace);
			//CharOut(i,(unsigned short)219);
			//WndChrRGB[i]=0xFF000000|(i*1001);
		}
	}
}

void GPWindow::WndToBuffer(char *buff,Rect &iRe, Size &ScrSize)
{
	*buff=0;
	try
	{
		Rect re=iRe;
		if (re.Width<0){re.X+=re.Width;re.Width=-re.Width;}
		if (re.Height<0){re.Y+=re.Height;re.Height=-re.Height;}
		re.Intersect(Rect(0,0,WindowSize.Width,WindowSize.Height));
		if (re.Width && re.Height)
		{
			int tmpreIntHeight=re.Height;
			int y;
			for(y=0;y<=re.Height;y++)
			{
				int wndpos=(y+re.Y)*WindowSize.Width+re.X;
				int x;
				for(x=0;x<re.Width;x++)
					*(buff++)=WndChar[wndpos+x]&0xFF;
			}
		}
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPWindow", "WndToBuffer","");
	}
}

void GPWindow::WndToBuffer(unsigned short *buff,Rect &iRe, Size &ScrSize)
{
	try
	{
		Rect re=iRe;
		if (re.Width<=0){re.X+=re.Width-1;re.Width=-re.Width+2;}
		if (re.Height<=0){re.Y+=re.Height-1;re.Height=-re.Height+2;}
		re.Intersect(Rect(0,0,WindowSize.Width,WindowSize.Height));
		if (re.Width && re.Height)
		{
			int tmpreIntHeight=re.Height;
			int y;
			for(y=0;y<re.Height;y++)
			{
				int wndpos=(y+re.Y)*WindowSize.Width+re.X;
				int x;
				for(x=0;x<re.Width;x++)
					*(buff++)=WndChar[wndpos+x];
			}
		}
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPWindow", "WndToBuffer2","");
	}
	*buff=0;
}

void GPWindow::WndPaint(Graphics &gr)
{
	int nCont,y,x;
	gr.SetCompositingQuality(m_CompositingQuality);
	gr.SetInterpolationMode(m_InterpolationMode);
	gr.SetPixelOffsetMode(m_PixelOffsetMode);
	gr.SetSmoothingMode(m_SmoothingMode);
	gr.SetTextContrast(m_TextContrast);
	gr.SetTextRenderingHint(m_TextRenderingHint);

	Rect re=WindowViewRect;
	re.Intersect(Rect(0,0,ScrParent->ScreenSize.Width,ScrParent->ScreenSize.Height));

	int minX=re.Width+1;
	int minY=re.Height+1;
	int maxX=0;
	int maxY=0;
	UINT WindowPosX=GPWndViewOfset.X;
	UINT WindowPosY=WindowViewRect.Y;
	UINT WindowPos=WindowPosX+WindowPosY*WindowSize.Width;
	UINT screenPosX=re.X;
	UINT screenPosY=re.Y;
	UINT screenPos=screenPosX+screenPosY*ScrParent->ScreenSize.Width;
	int deltaWindow=WindowSize.Width-re.Width;
	int deltaScreen=ScrParent->ScreenSize.Width-re.Width;

	for(y=0;y<re.Height;y++,WindowPos+=deltaWindow,screenPos+=deltaScreen)
		for(x=0;x<re.Width;x++,WindowPos++,screenPos++)
		if ((ScrParent->InvPoints[screenPos]&0x1))
		{
			if (y>maxY) maxY=y;
			if (x>maxX) maxX=x;
			if (y<minY) minY=y;
			if (x<minX) minX=x;
		}

	WindowPos=WindowPosX+WindowPosY*WindowSize.Width;
	screenPos=screenPosX+screenPosY*ScrParent->ScreenSize.Width;
	for(y=0;y<re.Height;y++,WindowPos+=deltaWindow,screenPos+=deltaScreen)
		for(x=0;x<re.Width;x++,WindowPos++,screenPos++)
		if (y<=maxY && x<=maxX && y>=minY && x>=minX) 
			ScrParent->InvPoints[screenPos]|=3;
		
//	RectF wndClipRect;
//	wndClipRect.X=((REAL)re.X*FontTable.maxWidth);
//	wndClipRect.Width=((REAL)re.Width*FontTable.maxWidth);
//	wndClipRect.Y=((REAL)re.Y*FontTable.maxHeight);
//	wndClipRect.Height=((REAL)re.Height*FontTable.maxHeight);

//	Region clReg(wndClipRect);

	gr.SetClip(RectF(
		-ScrParent->LeftBorderSafe*(REAL)100,
		-ScrParent->TopBorderSafe*(REAL)100,
		((REAL)ScrParent->ScreenSize.Width+ScrParent->LeftBorderSafe+ScrParent->RightBorderSafe)*(REAL)100,
		((REAL)ScrParent->ScreenSize.Height+ScrParent->TopBorderSafe+ScrParent->BottomBorderSafe)*(REAL)100
		),
		CombineModeReplace);

	gr.SetClip(RectF(
		(REAL)0,
		(REAL)0,
		(REAL)(ScrParent->ScreenSize.Width*100),
		(REAL)(ScrParent->ScreenSize.Height*100)
		),
		CombineModeExclude);


	RectF rChPos(
					(REAL)((re.X+minX)*100),
			    	(REAL)((re.Y+minY)*100),
				 	(REAL)(100*(maxX-minX+1)),
					(REAL)(100*(maxY-minY+1))
				);
////	gr.ScaleTransform(100/FontTable.maxWidth,100/FontTable.maxHeight);
//	gr.SetClip(RectF(),CombineModeReplace);
	gr.SetClip(rChPos,CombineModeUnion);
////	gr.ScaleTransform(FontTable.maxWidth/100,FontTable.maxHeight/100);


	for(nCont=0;nCont<MAX_LAYERS;nCont++)
		if (ArrLayers[nCont])
		{
			if (!ArrLayers[nCont]->pContext)
			{
				ArrLayers[nCont]->pContext=GPC.m_View->m_ODContextsArray->GetContext(ArrLayers[nCont]->csContextName);
				if (ArrLayers[nCont]->pContext->m_ContextName!=ArrLayers[nCont]->csContextName)
					ArrLayers[nCont]->pContext=NULL;
			}
			if (ArrLayers[nCont]->pContext && (ArrLayers[nCont]->dwStyle&ODCL_VISIBLE)==ODCL_VISIBLE && (ArrLayers[nCont]->dwStyle&ODCL_BKG)==ODCL_BKG)
			{
				RectF ClientRe(-10000,-10000,10000,10000);
				ArrLayers[nCont]->pContext->PaintToGraphics(gr,ClientRe,NULL);
			}
		}

	gr.ScaleTransform(100/FontTable.maxWidth,100/FontTable.maxHeight);


	if (re.Width && re.Height)
	{
		WindowPosX=GPWndViewOfset.X;
		WindowPosY=WindowViewRect.Y;
		WindowPos=WindowPosX+WindowPosY*WindowSize.Width;

		screenPosX=re.X;
		screenPosY=re.Y;
		screenPos=screenPosX+screenPosY*ScrParent->ScreenSize.Width;

		deltaWindow=WindowSize.Width-re.Width;
		deltaScreen=ScrParent->ScreenSize.Width-re.Width;

		SolidBrush frgBrush(Color(255,0,0,0));
		SolidBrush bkgBrush(Color(255,0,0,0));
		SolidBrush frgShadowBrush(Color(255,0,0,0));
		BOOL bNeedChangeShadow=TRUE;
		Color frgColor(0);
		Color frgShadowColor(0);
		Color bkgColor(0);
		ARGB frgColorCmp=0x02123456;
		ARGB bkgColorCmp=0x02123456;

		StringFormat sFormat(0,MAKELANGID(m_Language,m_SubLanguage));
		sFormat.SetLineAlignment(StringAlignmentCenter);
		sFormat.SetAlignment(StringAlignmentCenter);

		for(y=0;y<re.Height;y++,WindowPos+=deltaWindow,screenPos+=deltaScreen)
			for(x=0;x<re.Width;x++,WindowPos++,screenPos++)
			if ((ScrParent->InvPoints[screenPos]&0x1))
			{
				ScrParent->InvPoints[screenPos]=(ScrParent->InvPoints[screenPos]&(0xFFFFFFFF^0x1))|0x2;
				
				BOOL bNeedChangeBkgColor=FALSE;
				if (bkgColorCmp!=WndBkgRGB[WindowPos])
				{
					bNeedChangeBkgColor=TRUE;
					bkgColorCmp=WndBkgRGB[WindowPos];
					if ((WndBkgRGB[WindowPos]&0xFF000000))
								bkgColor.SetValue(WndBkgRGB[WindowPos]);
					else		bkgColor.SetFromCOLORREF(WndBkgRGB[WindowPos]);
				}

				if ((WndChrStyle[WindowPos]&GP_FNT_SELECTION)==GP_FNT_SELECTION)
				{
					bNeedChangeShadow=TRUE;
					bNeedChangeBkgColor=TRUE;
					bkgColor.SetValue(bkgColorCmp=(bkgColor.GetValue()^0xFFFFFF));
					bkgBrush.SetColor(bkgColor);
				}
				if (bNeedChangeBkgColor) bkgBrush.SetColor(bkgColor);

				RectF rChPos(
						(((REAL)(re.X+x))*FontTable.maxWidth),
						(((REAL)(re.Y+y))*FontTable.maxHeight),
						FontTable.maxWidth,
						FontTable.maxHeight
					);

				if (!*(WndChar+WindowPos+1)) rChPos.Width*=2;
				if (!(WndChrStyle[WindowPos]&GP_FNT_OPAQUE))
				{
					if (*(WndChar+WindowPos) || !x)
						gr.FillRectangle(&bkgBrush,rChPos);
				}

				BOOL bNeedChangeFrgColor=FALSE;
				if (frgColorCmp!=WndChrRGB[WindowPos])
				{
					bNeedChangeFrgColor=TRUE;
					frgColorCmp=WndChrRGB[WindowPos];
					if ((frgColorCmp&0xFF000000))
							frgColor.SetValue(frgColorCmp);
					else	frgColor.SetFromCOLORREF(frgColorCmp);
				}

				if ((WndChrStyle[WindowPos]&GP_FNT_SELECTION)==GP_FNT_SELECTION)
				{
					bNeedChangeFrgColor=TRUE;
					frgColor.SetValue(frgColorCmp=(frgColor.GetValue()^0xFFFFFF));
				}

				if ((WndChrStyle[WindowPos]&GP_FNT_BLINK)!=0)
				{
					bNeedChangeFrgColor=TRUE;
					frgColor.SetValue(frgColorCmp=((frgColor.GetValue()&0xFFFFFF)|GPC.BlinkValue));
				}

				if (bNeedChangeFrgColor)
				{
					bNeedChangeShadow=TRUE;
					frgBrush.SetColor(frgColor);
				}

				if (*(WndChar+WindowPos))
				{
					WCHAR tmpWText2[10]={0,0,};
					if (((*(WndChar+WindowPos))&0xFF00)) 
					{
						rChPos.Y-=rChPos.Height/2;
						rChPos.Y+=FontTable.DeltaHeightUC;
						rChPos.Height*=2;
						*tmpWText2=*(WndChar+WindowPos);
					}
					else
					{
						rChPos.Y-=rChPos.Height/2;
						rChPos.Y+=FontTable.DeltaHeightUC*2/3;
						rChPos.Height*=2;
						char tmpChar=WndChar[WindowPos]&0xFF;
						if ((WndChrStyle[WindowPos]&GP_FNT_CODE))
							MultiByteToWideChar(CP_OEMCP, 0,&tmpChar , 1, tmpWText2, 2);
						else
							MultiByteToWideChar(m_CurCodePage, 0,&tmpChar , 1, tmpWText2, 2);
					}
					rChPos.X+=ScrParent->FontOfsetX;
					rChPos.Y+=ScrParent->FontOfsetY;

					DWORD dwShadowType=(WndChrStyle[WindowPos]&GP_FNT_SHADOWMASK);
					if (dwShadowType)
					{
						RectF ShadowrChPos(rChPos);
						if (bNeedChangeShadow)
						{
							ARGB frgNew=frgColor.GetValue();
							switch(dwShadowType)
							{
							case  GP_FNT_SHADOW1:
							case  GP_FNT_SHADOW2:
								frgShadowColor.SetValue((frgColor.GetValue()&0xFFFFFF)|0xCC000000);
								break;
							case  GP_FNT_SHADOW3:
							case  GP_FNT_SHADOW4:
								frgShadowColor.SetValue((frgColor.GetValue()&0xFFFFFF)|0x99000000);
								break;
							case  GP_FNT_SHADOW5:
							case  GP_FNT_SHADOW6:
								frgShadowColor.SetValue((frgColor.GetValue()&0xFFFFFF)|0x66000000);
								break;
							case  GP_FNT_SHADOW7:
							case  GP_FNT_SHADOW8:
								frgShadowColor.SetValue((frgColor.GetValue()&0xFFFFFF)|0x33000000);
								break;
							}
							frgShadowBrush.SetColor(frgShadowColor);
						}
						switch(dwShadowType)
						{
						case  GP_FNT_SHADOW1:
						case  GP_FNT_SHADOW3:
						case  GP_FNT_SHADOW5:
						case  GP_FNT_SHADOW7:
							ShadowrChPos.X+=3;
							ShadowrChPos.Y+=3;
							rChPos.X-=3;
							rChPos.Y-=3;
							break;
						case  GP_FNT_SHADOW2:
						case  GP_FNT_SHADOW4:
						case  GP_FNT_SHADOW6:
						case  GP_FNT_SHADOW8:
							ShadowrChPos.X+=5;
							ShadowrChPos.Y+=5;
							rChPos.X-=5;
							rChPos.Y-=5;
							break;
						}

						gr.DrawString(tmpWText2, 1, FontTable.GetFont(WndChrStyle[WindowPos]), 
								ShadowrChPos, &sFormat,
								&frgShadowBrush);
					}

					gr.DrawString(tmpWText2, 1, FontTable.GetFont(WndChrStyle[WindowPos]), 
							rChPos, &sFormat,
							&frgBrush);
				}

			}

	gr.ScaleTransform(FontTable.maxWidth/100,FontTable.maxHeight/100);
	for(nCont=0;nCont<MAX_LAYERS;nCont++)
		if (ArrLayers[nCont])
		{
			if (!ArrLayers[nCont]->pContext)
			{
				ArrLayers[nCont]->pContext=GPC.m_View->m_ODContextsArray->GetContext(ArrLayers[nCont]->csContextName);
				if (ArrLayers[nCont]->pContext->m_ContextName!=ArrLayers[nCont]->csContextName)
					ArrLayers[nCont]->pContext=NULL;
			}
			if (ArrLayers[nCont]->pContext && (ArrLayers[nCont]->dwStyle&ODCL_VISIBLE)==ODCL_VISIBLE && (ArrLayers[nCont]->dwStyle&ODCL_FRG)==ODCL_FRG)
			{
				RectF RectClip;
				gr.GetClipBounds(&RectClip);
				ArrLayers[nCont]->pContext->PaintToGraphics(gr,RectClip,NULL);
			}
		}
	}
	gr.ResetClip();
}

void GPWindow::WndPrint(Graphics &gr)
{
	int nCont;

	gr.SetCompositingQuality(m_CompositingQuality);
	gr.SetInterpolationMode(m_InterpolationMode);
	gr.SetPixelOffsetMode(m_PixelOffsetMode);
	gr.SetSmoothingMode(m_SmoothingMode);
	gr.SetTextContrast(m_TextContrast);
	gr.SetTextRenderingHint(m_TextRenderingHint);

	for(nCont=0;nCont<MAX_LAYERS;nCont++)
		if (ArrLayers[nCont])
		{
			if (!ArrLayers[nCont]->pContext)
			{
				ArrLayers[nCont]->pContext=GPC.m_View->m_ODContextsArray->GetContext(ArrLayers[nCont]->csContextName);
				if (ArrLayers[nCont]->pContext->m_ContextName!=ArrLayers[nCont]->csContextName)
					ArrLayers[nCont]->pContext=NULL;
			}
			if (ArrLayers[nCont]->pContext && (ArrLayers[nCont]->dwStyle&ODCL_VISIBLE)==ODCL_VISIBLE && (ArrLayers[nCont]->dwStyle&ODCL_BKG)==ODCL_BKG)
			{
				RectF ClientRe(-10000,-10000,10000,10000);
				ArrLayers[nCont]->pContext->PaintToGraphics(gr,ClientRe,NULL);
			}
		}

	gr.ScaleTransform(100/PrintFontTable.maxWidth,100/PrintFontTable.maxHeight);

	Rect re=WindowViewRect;
	re.Intersect(Rect(0,0,ScrParent->ScreenSize.Width,ScrParent->ScreenSize.Height));

	if (re.Width && re.Height)
	{
		UINT WindowPosX=GPWndViewOfset.X;
		UINT WindowPosY=WindowViewRect.Y;
		UINT WindowPos=WindowPosX+WindowPosY*WindowSize.Width;

		UINT screenPosX=re.X;
		UINT screenPosY=re.Y;
		UINT screenPos=screenPosX+screenPosY*ScrParent->ScreenSize.Width;

		int deltaWindow=WindowSize.Width-re.Width;
		int deltaScreen=ScrParent->ScreenSize.Width-re.Width;

		SolidBrush frgBrush(Color(255,0,0,0));
		SolidBrush bkgBrush(Color(255,0,0,0));
		Color frgColor(0);
		Color bkgColor(0);

		StringFormat sFormat(0,MAKELANGID(m_Language,m_SubLanguage));
		sFormat.SetLineAlignment(StringAlignmentCenter);
		sFormat.SetAlignment(StringAlignmentCenter);

		int y,x;
		for(y=0;y<re.Height;y++,WindowPos+=deltaWindow,screenPos+=deltaScreen)
			for(x=0;x<re.Width;x++,WindowPos++,screenPos++)
//			if ((ScrParent->InvPoints[screenPos]&0x1))
			{
//				ScrParent->InvPoints[screenPos]=(ScrParent->InvPoints[screenPos]&(0xFFFFFFFF^0x1))|0x2;

				if ((WndBkgRGB[WindowPos]&0xFF000000))
							bkgColor.SetValue(WndBkgRGB[WindowPos]);
				else		bkgColor.SetFromCOLORREF(WndBkgRGB[WindowPos]);

				if ((WndChrStyle[WindowPos]&GP_FNT_SELECTION)==GP_FNT_SELECTION)
					bkgColor.SetValue(bkgColor.GetValue()^0xFFFFFF);

				bkgBrush.SetColor(bkgColor);
				RectF rChPos(
						((re.X+x)*PrintFontTable.maxWidth),
						((re.Y+y)*PrintFontTable.maxHeight),
						PrintFontTable.maxWidth,
						PrintFontTable.maxHeight
					);

				if (!(WndChrStyle[WindowPos]&GP_FNT_OPAQUE))
				{
					if (!*(WndChar+WindowPos+1)) rChPos.Width*=2;
					if (*(WndChar+WindowPos) || !x)
						gr.FillRectangle(&bkgBrush,rChPos);
				}

				if ((WndChrRGB[WindowPos]&0xFF000000))
						frgColor.SetValue(WndChrRGB[WindowPos]);
				else	frgColor.SetFromCOLORREF(WndChrRGB[WindowPos]);

				if ((WndChrStyle[WindowPos]&GP_FNT_SELECTION)==GP_FNT_SELECTION)
				{
					frgColor.SetValue(frgColor.GetValue()^0xFFFFFF);
				}

				if ((WndChrStyle[WindowPos]&GP_FNT_BLINK)!=0)
					frgColor.SetValue((frgColor.GetValue()&0xFFFFFF)|GPC.BlinkValue);

				frgBrush.SetColor(frgColor);

				if (*(WndChar+WindowPos))
				{
					WCHAR tmpWText2[10]={0,0,};
					if (((*(WndChar+WindowPos))&0xFF00)) 
					{
						rChPos.Y-=rChPos.Height/2;
						rChPos.Y+=PrintFontTable.DeltaHeightUC*2/3;
						rChPos.Height*=2;
						*tmpWText2=*(WndChar+WindowPos);
					}
					else
					{
						rChPos.Y-=rChPos.Height/2;
						rChPos.Y+=PrintFontTable.DeltaHeightUC*2/3;
						rChPos.Height*=2;
						char tmpChar=WndChar[WindowPos]&0xFF;
						if ((WndChrStyle[WindowPos]&GP_FNT_CODE))
							MultiByteToWideChar(CP_OEMCP, 0,&tmpChar , 1, tmpWText2, 2);
						else
							MultiByteToWideChar(m_CurCodePage, 0,&tmpChar , 1, tmpWText2, 2);
					}

					rChPos.X+=ScrParent->FontOfsetX;
					rChPos.Y+=ScrParent->FontOfsetY;
					gr.DrawString(tmpWText2, 1, PrintFontTable.GetFont(WndChrStyle[WindowPos]), 
							rChPos, &sFormat,
							&frgBrush);
				}

			}

	gr.ScaleTransform(PrintFontTable.maxWidth/100,PrintFontTable.maxHeight/100);
	for(nCont=0;nCont<MAX_LAYERS;nCont++)
		if (ArrLayers[nCont])
		{
			if (!ArrLayers[nCont]->pContext)
			{
				ArrLayers[nCont]->pContext=GPC.m_View->m_ODContextsArray->GetContext(ArrLayers[nCont]->csContextName);
				if (ArrLayers[nCont]->pContext->m_ContextName!=ArrLayers[nCont]->csContextName)
					ArrLayers[nCont]->pContext=NULL;
			}
			if (ArrLayers[nCont]->pContext && (ArrLayers[nCont]->dwStyle&ODCL_VISIBLE)==ODCL_VISIBLE && (ArrLayers[nCont]->dwStyle&ODCL_FRG)==ODCL_FRG)
			{
				RectF RectClip;
				gr.GetClipBounds(&RectClip);
				ArrLayers[nCont]->pContext->PaintToGraphics(gr,RectClip,NULL);
			}
		}
	}
}

BOOL GPWindow::IsWndSaveEnable() 
{ 	
	return (GPWndState&GP_WND_SAVE)!=0;
}

BOOL GPWindow::IsWndViewEnable() 
{
	return (GPWndState&GP_WND_VIEW)!=0;
}

void GPWindow::GPCopyRgn(GPWindow * SourseWnd, Rect &sourseRect, Point &destRect)
{
	if (WindowSize.Width > destRect.X && WindowSize.Height > destRect.Y )
	{
		int nx=WindowSize.Width-destRect.X;
		int ny=WindowSize.Height-destRect.Y;

		if (nx>sourseRect.Width)	nx=sourseRect.Width;
		if (ny>sourseRect.Height)	ny=sourseRect.Height;

		int delta_s=SourseWnd->GetWndSize().Width;
		int delta_d=GetWndSize().Width;
		int x,y;
		int nallsorse=SourseWnd->GetWndSize().Width*SourseWnd->GetWndSize().Height;
		for(x=0;x<nx;x++)
			for(y=0;y<ny;y++)
			{
				int pos_s=(sourseRect.Y+y)*delta_s+sourseRect.X+x;
				int pos_d=(destRect.Y+y)*delta_d+destRect.X+x;
				if (pos_d<(int)nall && pos_s<nallsorse)
				{
					if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwChOutput++;
					WndChrRGB  [pos_d]	= SourseWnd->WndChrRGB   [pos_s];
					WndChar    [pos_d]	= SourseWnd->WndChar     [pos_s];
					WndBkgRGB  [pos_d]	= SourseWnd->WndBkgRGB   [pos_s];
					WndChrStyle[pos_d]	= SourseWnd->WndChrStyle [pos_s];
				}
			}
	}
	else
	{
		CString tmps;
		tmps.Format("x=%d , y=%d",destRect.X,destRect.Y);
		GPC.m_ErrReport.GPWriteErrorLog2("Green screen","GPCopyRgn wrong parameters",tmps);
	}

}

void GPWindow::IntersectRect(Rect & rect) 
{
	rect.Intersect(WindowViewRect); 
}

Size GPWindow::GetWndSize()		
{	
	return WindowSize;
}

Rect GPWindow::GetWndRect()		
{	
	return Rect(Point(0,0),WindowSize);
}

Rect GPWindow::GetWndViewRect()
{	
	return WindowViewRect;
}

void GPWindow::GetWndViewRect(Rect &iRect)
{
	iRect=WindowViewRect;
}

Point GPWindow::GetCursorPosition() 
{	
	return cursor;
}

void GPWindow::GetCursorPosition(Point &iPoint) 
{	
	iPoint=cursor;
}

void GPWindow::GetBlinkPoints(char *mscr, int scrWidth)
{
	int wpos,spos,y,x,delta;
	delta=scrWidth-WindowViewRect.Width;
	spos=scrWidth*WindowViewRect.Y+WindowViewRect.X;

	for(wpos=0,y=0;y<WindowSize.Height;y++,spos+=delta)
		for(x=0;x<WindowSize.Width;x++,wpos++,spos++)
			if (mscr[spos]==0)
			{
				mscr[spos]=1;
				if ((WndChrStyle[wpos]&GP_FNT_BLINK)==GP_FNT_BLINK) mscr[spos]=2;
			}
}

BOOL GPWindow::SetReverseVideo(BOOL bReverse, DWORD dwMask)
{
	if (((dwMask&dwOldCommandMask)&GP_SCRMASK_REVERSE)!=GP_SCRMASK_REVERSE)
	{
		if (ReverseColorFlag!=bReverse)
		{
			ReverseColorFlag=bReverse;
			UINT bkgInd=GetBkgColorIndex();
			UINT frgInd=GetChrColorIndex();
			DWORD bkg=GetBkgColor();
			DWORD frg=GetChrColor();
			SetBkgColorIndex(frgInd, dwMask);
			SetChrColorIndex(bkgInd, dwMask);
			SetBkgColor(frg, dwMask);
			SetChrColor(bkg, dwMask);
		}
	}
	return ReverseColorFlag;
}

BOOL GPWindow::GetReverseVideo()
{
	return ReverseColorFlag;
}


UINT GPWindow::SetBkgColor(UINT newcolor, DWORD dwMask)
{
	UINT old=BkgColor;
	if (((dwMask&dwOldCommandMask)&GP_SCRMASK_CLRBKG)!=GP_SCRMASK_CLRBKG)
	{
		int i;
		for(i=0;i<16 && newcolor!=cBEtalon[i];i++);
		if (i<16) SetBkgColorIndex(i, dwMask);
		else BkgColor=newcolor;
	}
	return old;
}

UINT GPWindow::SetBkgColorIndex(UINT newcolorIndex, DWORD dwMask)
{
	UINT old=BkgColorInd;
	if (((dwMask&dwOldCommandMask)&GP_SCRMASK_CLRBKG)!=GP_SCRMASK_CLRBKG)
	{
		BkgColorInd=newcolorIndex&0xF;
		BkgColor=cBEtalon[BkgColorInd];
	}
	return old;
}

UINT GPWindow::GetBkgColor() 
{
	return BkgColor; 
}

UINT GPWindow::GetBkgColorIndex() 
{
	return BkgColorInd; 
}

UINT GPWindow::SetChrColor(UINT newcolor, DWORD dwMask)
{
	UINT old=ChrColor;
	if (((dwMask&dwOldCommandMask)&GP_SCRMASK_CLRFRG)!=GP_SCRMASK_CLRFRG)
	{
		int i;
		for(i=0;i<16 && newcolor!=cFEtalon[i];i++);
		if (i<16) SetChrColorIndex(i, dwMask);
		else ChrColor=newcolor;
	}
	return old;
}

UINT GPWindow::SetChrColorIndex(UINT newcolorIndex, DWORD dwMask)
{
	UINT old=ChrColorInd;
	if (((dwMask&dwOldCommandMask)&GP_SCRMASK_CLRFRG)!=GP_SCRMASK_CLRFRG)
	{
		ChrColorInd=newcolorIndex&0xF;
		ChrColor=cFEtalon[ChrColorInd];
	}
	return old;
}

UINT GPWindow::GetChrColor() 
{ 
	return ChrColor;
}

UINT GPWindow::GetChrColorIndex() 
{ 
	return ChrColorInd;
}

UINT GPWindow::SetChrStyle(UINT newStyle, DWORD dwMask)
{
	UINT old=ChrStyle;
	 DWORD cmpStyle=(ChrStyle^newStyle);

	if (((dwMask&dwOldCommandMask)&GP_SCRMASK_UNDERLINE)!=GP_SCRMASK_UNDERLINE && (cmpStyle&GP_FNT_UNDERLINE)==GP_FNT_UNDERLINE)
		ChrStyle^=(cmpStyle&GP_FNT_UNDERLINE);
	if (((dwMask&dwOldCommandMask)&GP_SCRMASK_STRIKE)!=GP_SCRMASK_STRIKE && (cmpStyle&GP_FNT_STRIKE)==GP_FNT_STRIKE)
		ChrStyle^=(cmpStyle&GP_FNT_STRIKE);
	if (((dwMask&dwOldCommandMask)&GP_SCRMASK_ITALIC)!=GP_SCRMASK_ITALIC && (cmpStyle&GP_FNT_ITALIC)==GP_FNT_ITALIC)
		ChrStyle^=(cmpStyle&GP_FNT_ITALIC);
	if (((dwMask&dwOldCommandMask)&GP_SCRMASK_BOLD)!=GP_SCRMASK_BOLD && (cmpStyle&GP_FNT_BOLD)==GP_FNT_BOLD)
		ChrStyle^=(cmpStyle&GP_FNT_BOLD);
	if (((dwMask&dwOldCommandMask)&GP_SCRMASK_SELECTION)!=GP_SCRMASK_SELECTION && (cmpStyle&GP_FNT_SELECTION)==GP_FNT_SELECTION)
		ChrStyle^=(cmpStyle&GP_FNT_SELECTION);
	if (((dwMask&dwOldCommandMask)&GP_SCRMASK_OPAQUE)!=GP_SCRMASK_OPAQUE && (cmpStyle&GP_FNT_OPAQUE)==GP_FNT_OPAQUE)
		ChrStyle^=(cmpStyle&GP_FNT_OPAQUE);
	if (((dwMask&dwOldCommandMask)&GP_SCRMASK_CODE)!=GP_SCRMASK_CODE && (cmpStyle&GP_FNT_CODE)==GP_FNT_CODE)
		ChrStyle^=(cmpStyle&GP_FNT_CODE);
	if (((dwMask&dwOldCommandMask)&GP_SCRMASK_BLINK)!=GP_SCRMASK_BLINK && (cmpStyle&GP_FNT_BLINK)==GP_FNT_BLINK)
		ChrStyle^=(cmpStyle&GP_FNT_BLINK);
	if (((dwMask&dwOldCommandMask)&GP_SCRMASK_LIGHT)!=GP_SCRMASK_LIGHT && (cmpStyle&GP_FNT_LIGHT)==GP_FNT_LIGHT)
		ChrStyle^=(cmpStyle&GP_FNT_LIGHT);
	if (((dwMask&dwOldCommandMask)&GP_SCRMASK_SHADOW)!=GP_SCRMASK_SHADOW && (cmpStyle&GP_FNT_SHADOWMASK))
		ChrStyle^=(cmpStyle&GP_FNT_SHADOWMASK);

	if ((m_ProtectedFieldModeFlag&GP_FNT_FIXED)==GP_FNT_FIXED)	ChrStyle|=GP_FNT_FIXED;
	return old;
}

UINT GPWindow::GetChrStyle() 
{
	return ChrStyle;
}

unsigned short GPWindow::SetChrSpace(unsigned short newSpace)
{
	unsigned short old=ChrSpace;
	ChrSpace=newSpace;
	return old;
}

unsigned short GPWindow::GetChrSpace() 
{ 
	return ChrSpace;
}

void GPWindow::CharOut(int x, int y, unsigned short ch)
{
	SetCursorPosition(x,y);
	CharOut(ch);
}

void GPWindow::CharOutAW(int x, int y, char ch)
{
	SetCursorPosition(x,y);
	CharOutAW(ch);
}

void GPWindow::LineOut(int x, int y, unsigned short *line, DWORD LineLen)
{
	if (LineLen)
	{
		CharOut(x,y,*line);
		LineOut(++line,--LineLen);
	}
}

void GPWindow::LineOut(unsigned short *line, DWORD LineLen)
{
	while(LineLen--) CharOut(*(line++));
}

void GPWindow::CharOut(unsigned short ch)
{

	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwChOutput++;
	switch(ch) 
	{
	case 0:	
		break;
	case 7:	
		if (GPC.m_View->m_uLockBeep==0 && PlaySound("ding.wav", NULL, SND_ASYNC)==FALSE)
			MessageBeep( 0xFFFFFFFF);   
		break;
	case 8:
		CursorMoveLeft();
		CharOut(ChrSpace);
		CursorMoveLeft();
		break;
	case 9:	
		DoTab(0);
		break;
	case 13:
		CursorMoveCR();
		break;
	case 10:
		CursorMoveLF();
		break;
	default:	
		if (WaitScroll)
		{
			WaitScroll=FALSE;
			ScrollUp();
		}
		
		CharOut(cursor,ch);
		CursorMoveRight();
		break;
	}
}

void GPWindow::CharOutAW(char ch)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwChOutput++;

	if (m_LastPrefix &&  ((ch<=32 && ch>=0) || GPC.dwGraphFlag))
		GPC.dwMBReposition|=0x40000000;

	switch(ch) 
	{
	case 0:
		break;
	case 7:
		if (GPC.m_View->m_uLockBeep==0 && PlaySound("ding.wav", NULL, SND_ASYNC)==FALSE)
			MessageBeep( 0xFFFFFFFF);
		break;
	case 8:
		CursorMoveLeft();
		CharOut(ChrSpace);
		CursorMoveLeft();
		break;
	case 9:	
		DoTab(0);
		break;
	case 13:
		CursorMoveCR();
		break;
	case 10:
		CursorMoveLF();
		break;
	default:
		if (GPC.dwGraphFlag)	CharOutGR(ch);
		else
		if ((GPC.dwMBReposition&0x20000000) && (GPC.dwMBReposition&0x40000000) && (GPC.dwMBReposition&0x80000000) && !(ch<=32 && ch>=0))
		{
			if (WaitScroll)
			{
				WaitScroll=FALSE;
				ScrollUp();
			}
			if (m_PrefixPositionEx<nall)
			{
				char chh[4];
				chh[1]=GPC.chWideDosAnsi[GPC.dwMBReposition&0xFF];
				chh[0]=GPC.chWideDosAnsi2[(GPC.dwMBReposition/0x100)&0xFF];
				GPC.MBConv3SrwPC(chh, chh);
				if (
				MultiByteToWideChar(
				  GPC.m_CurCodePage, // code page
				  MB_PRECOMPOSED,         // character-type options
				  chh, // string to map
				  2,       // number of bytes in string
				  (LPWSTR)(WndChar+m_PrefixPositionEx),  // wide-character buffer
				  1        // size of buffer
				)==0)
				{
					WndChar[m_PrefixPositionEx]=(chh[0]&0xFF);
					//WndChar[cursor.X+cursor.Y*WindowSize.Width]=(chh[1]&0xFF);
					RedrawWndPos(cursor.X+cursor.Y*WindowSize.Width);
					m_NextMBOutChar=(chh[1]&0xFF);
				}

				RedrawWndPos(m_PrefixPositionEx); 

			}
			CursorMoveRight();
			GPC.dwMBReposition=0;
			m_PrefixPositionEx=0xC0000000;
		}
		else
		if (!m_LastPrefix || (ch<=32 && ch>=0))
		{
			if (WaitScroll && !GPC.chWideDosAnsi[ch&0xFF])
			{
				WaitScroll=FALSE;
				ScrollUp();
			}
			if (!m_LastPrefix)
			{
				CharOutAW(cursor,ch);
				if (!m_LastPrefix) 
				{
					if (cursor.X) RedrawWndPos(cursor.X-1+cursor.Y*WindowSize.Width); 
					RedrawWndPos(cursor.X+cursor.Y*WindowSize.Width); 
				}
			}
			else
			{
				CharOut(cursor,ch);
				if (cursor.X) RedrawWndPos(cursor.X-1+cursor.Y*WindowSize.Width); 
				RedrawWndPos(cursor.X+cursor.Y*WindowSize.Width); 
			}
			CursorMoveRight();
		}
		else
		{
			GPC.dwMBReposition|=0x20000000;
			if (m_PrefixPosition<nall) CharOutAW(m_PrefixPosition,ch);
			if (GPC.m_WideOn2Pos) 
			{
				CharOut(cursor,m_NextMBOutChar);
				if ((DWORD)(cursor.X+cursor.Y*WindowSize.Width)!=m_PrefixPosition+1) 
					CharOut((UINT)(m_PrefixPosition+1),(unsigned short)m_NextMBOutChar);
				m_NextMBOutChar=0;
			}
			if (WaitScroll)
			{
				WaitScroll=FALSE;
				ScrollUp();
			}
			if (cursor.X) RedrawWndPos(cursor.X-1+cursor.Y*WindowSize.Width); 
			CursorMoveRight();
		}

		break;
	}
}

void GPWindow::CharOutGR(char ch)
{
	if (GPC.dwGraphDecodeArray[ch]<0xFFFD)
	{
		if (WaitScroll)
		{
			WaitScroll=FALSE;
			ScrollUp();
		}

		CharOutGR(cursor.X+cursor.Y*WindowSize.Width,ch);
		if (!m_LastPrefix) 
		{
			if (cursor.X) RedrawWndPos(cursor.X-1+cursor.Y*WindowSize.Width); 
		}
		CursorMoveRight();
	}
}

void GPWindow::CharOutGRUC(unsigned short ch)
{
	if (WaitScroll)
	{
		WaitScroll=FALSE;
		ScrollUp();
	}

	UINT pos=cursor.X+cursor.Y*WindowSize.Width;
	if ((m_ProtectedModeFlag&GP_FNT_FIXED)==GP_FNT_FIXED)
	{
		while(pos<nall && (WndChrStyle[pos]&GP_FNT_FIXED)==GP_FNT_FIXED) pos++;
		if (pos==nall)
		{
			pos-=WindowSize.Width;
			ScrollUp();
		}
	}
	if (pos<nall)
	{
		WndChrStyle[pos]	=(ChrStyle|GP_FNT_CODE)|(m_ProtectedFieldModeFlag&GP_FNT_FIXED);
		WndChar[pos]		=ch;
		WndChrRGB[pos]		=ChrColor;	// массив цветов символов
		WndBkgRGB[pos]		=BkgColor;	// массив цветов фона
		RedrawWndPos(pos);
	}

	if (!m_LastPrefix) 
	{
		if (cursor.X) RedrawWndPos(cursor.X-1+cursor.Y*WindowSize.Width); 
	}
	CursorMoveRight();
}

DWORD GPWindow::GetInvPoint(UINT pos)
{
	DWORD ret=0;
	if (pos<nall)
	{
		ret=ScrParent->GetInvPoint(
		/*X=*/	(pos%WindowSize.Width)-GPWndViewOfset.X+WindowViewRect.X+
		/*Y=*/	(pos/WindowSize.Width-GPWndViewOfset.Y+WindowViewRect.Y)*ScrParent->ScreenSize.Width);
	}
	return ret;
}


void GPWindow::RedrawWndPos(Point &pos) 
{
	RedrawWndPos(pos.X+pos.Y*WindowSize.Width);
}

void GPWindow::RepaintWndPos(Point &pos) 
{
	RepaintWndPos(pos.X+pos.Y*WindowSize.Width);
}

void GPWindow::RedrawWndPos(UINT pos)
{
	if (pos<nall)
	{
		ScrParent->RedrawPoint(
		/*X=*/	(pos%WindowSize.Width)-GPWndViewOfset.X+WindowViewRect.X+
		/*Y=*/	(pos/WindowSize.Width-GPWndViewOfset.Y+WindowViewRect.Y)*ScrParent->ScreenSize.Width);
	}
}

void GPWindow::RepaintWndPos(UINT pos)
{
	if (pos<nall)
	{
		ScrParent->RepaintPoint(
		/*X=*/	(pos%WindowSize.Width)-GPWndViewOfset.X+WindowViewRect.X+
		/*Y=*/	(pos/WindowSize.Width-GPWndViewOfset.Y+WindowViewRect.Y)*ScrParent->ScreenSize.Width);
	}
}

void GPWindow::RedrawRect(Rect &refrect)
{
	if (IsWndViewEnable()) 
	{
		refrect.Intersect(WindowViewRect);
		refrect.X+=GPWndViewOfset.X;
		refrect.Y+=GPWndViewOfset.Y;
		ScrParent->RedrawRect(refrect);
	}
}

void GPWindow::RepaintRect(Rect &refrect)
{
	if (IsWndViewEnable()) 
	{
		refrect.Intersect(WindowViewRect);
		refrect.X+=GPWndViewOfset.X;
		refrect.Y+=GPWndViewOfset.Y;
		ScrParent->RepaintRect(refrect);
	}
}

void GPWindow::RedrawWnd()
{
	Rect re(0,0,WindowSize.Width,WindowSize.Height);
	RedrawRect(re);
}

void GPWindow::RepaintWnd()
{
	Rect re(0,0,WindowSize.Width,WindowSize.Height);
	RepaintRect(re);
}


void GPWindow::ScrollUp()
{
  if (ScrollWnd)
  {
	UINT pos1,pos2;
	m_PrefixPosition-=WindowSize.Width;
	m_PrefixPositionEx-=WindowSize.Width;

	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwChOutput+=nall;

	for(pos1=0,pos2 = WindowSize.Width;pos2< nall;pos2++,pos1++)
	{
		WndChar[pos1]		=WndChar[pos2];
		WndChrRGB[pos1]		=WndChrRGB[pos2];
		WndBkgRGB[pos1]		=WndBkgRGB[pos2];
		WndChrStyle[pos1]	=WndChrStyle[pos2];
	}

	for(;pos1< nall;pos1++)
		CharOut(pos1,ChrSpace);

	RedrawWnd();
  }
}

void GPWindow::ScrollDown()
{
  if (ScrollWnd)
  {
	int pos1,pos2;
	m_PrefixPosition+=WindowSize.Width;
	m_PrefixPositionEx+=WindowSize.Width;

	for(pos1=nall-1,pos2 = nall-WindowSize.Width-1;pos1>=WindowSize.Width;pos2--,pos1--)
	{
		WndChar[pos1]		=WndChar[pos2];
		WndChrRGB[pos1]		=WndChrRGB[pos2];
		WndBkgRGB[pos1]		=WndBkgRGB[pos2];
		WndChrStyle[pos1]	=WndChrStyle[pos2];
	}

	for(;pos1>=0;pos1--)
		CharOut(pos1,ChrSpace);
	
	RedrawWnd();
  }
}

void GPWindow::ScrollUp(UINT ntime)		
{	
	UINT i;
	for(i=0;i<ntime; i++) ScrollUp();	
}

void GPWindow::ScrollDown(UINT ntime)
{
	UINT i;
	for(i=0;i<ntime; i++) ScrollDown();
}

void GPWindow::ScrollLeft(UINT ntime)
{
	UINT i;
	for(i=0;i<ntime; i++) ScrollLeft();
}

void GPWindow::ScrollRight(UINT ntime)
{
	UINT i;
	for(i=0;i<ntime; i++) ScrollRight();
}

void GPWindow::ScrollLeft()
{
  if (ScrollWnd)
  {
	UINT pos=0;
	int pos1;
	UINT tChrStyle=WndChrStyle[0];		// текущий стиль символа
	UINT tChrColor=WndChrRGB[0];		// текущий цвет символа
	UINT tBkgColor=WndBkgRGB[0];		// текущий цвет фона
	unsigned short tChrSpace=WndChar[0];		// пробельный символ 
	
	if ((m_PrefixPosition%WindowSize.Width)==0)
	{
		m_PrefixPosition=0xC0000000;
	}
	else m_PrefixPosition--;

	if ((m_PrefixPositionEx%WindowSize.Width)==0)
	{
		m_PrefixPositionEx=0xC0000000;
	}
	else m_PrefixPositionEx--;

	for(pos=0;pos<nall;pos++)
	{
		WndChar[pos]		=WndChar[pos+1];
		WndChrRGB[pos]		=WndChrRGB[pos+1];
		WndBkgRGB[pos]		=WndBkgRGB[pos+1];
		WndChrStyle[pos]	=WndChrStyle[pos+1];
	}
	
	for(pos=nall-1,pos1=pos-WindowSize.Width;pos1>=0;pos1-=WindowSize.Width)
	{
		WndChar[pos]		=WndChar[pos1];
		WndChrRGB[pos]		=WndChrRGB[pos1];
		WndBkgRGB[pos]		=WndBkgRGB[pos1];
		WndChrStyle[pos]	=WndChrStyle[pos1];
		pos=pos1;
	}
	
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwChOutput++;
	WndChrStyle[pos]=	tChrStyle;
	WndChrRGB[pos]  =	tChrColor;
	WndBkgRGB[pos]  =	tBkgColor;
	WndChar[pos]	=	tChrSpace;

	RedrawWnd();
  }
}

void GPWindow::ScrollRight()
{
  if (ScrollWnd)
  {

	UINT pos=nall-1;
	UINT tChrStyle=WndChrStyle[pos];	// текущий стиль символа
	UINT tChrColor=WndChrRGB[pos];		// текущий цвет символа
	UINT tBkgColor=WndBkgRGB[pos];		// текущий цвет фона
	unsigned short tChrSpace=WndChar[pos];		// пробельный символ 

	m_PrefixPosition++;
	if ((m_PrefixPosition%WindowSize.Width)==0)
	{
		m_PrefixPosition=0xC0000000;
	}

	m_PrefixPositionEx++;
	if ((m_PrefixPositionEx%WindowSize.Width)==0)
	{
		m_PrefixPositionEx=0xC0000000;
	}
	
	for(;pos>0;pos--)
	{
		WndChar[pos]		=WndChar[pos-1];	// массив символов окна
		WndChrRGB[pos]		=WndChrRGB[pos-1];	// массив цветов символов
		WndBkgRGB[pos]		=WndBkgRGB[pos-1];	// массив цветов фона
		WndChrStyle[pos]	=WndChrStyle[pos-1];// массив характеристик символов
	}
	
	UINT pos1;
	for(pos1=WindowSize.Width;pos1<nall;pos1+=WindowSize.Width)
	{
		WndChar[pos]		=WndChar[pos1];	// массив символов окна
		WndChrRGB[pos]		=WndChrRGB[pos1];	// массив цветов символов
		WndBkgRGB[pos]		=WndBkgRGB[pos1];	// массив цветов фона
		WndChrStyle[pos]	=WndChrStyle[pos1];// массив характеристик символов
		pos=pos1;
	}
	
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwChOutput++;
	WndChrStyle[pos]=	tChrStyle;
	WndChrRGB[pos]  =	tChrColor;
	WndBkgRGB[pos]  =	tBkgColor;
	WndChar[pos]	=	tChrSpace;

	RedrawWnd();
  }
}

void GPWindow::CursorMoveLeft()
{
	WaitScroll=FALSE;
	RepaintWndPos(cursor.X+cursor.Y*WindowSize.Width); 
	if (--cursor.X<0) {	cursor.X=WindowSize.Width-1; CursorMoveUp(); }
}

void GPWindow::CursorMoveRight()
{
	if (WaitScroll) 
	{
		WaitScroll=FALSE;
		ScrollUp();
	}
	else 	
		RepaintWndPos(cursor.X+cursor.Y*WindowSize.Width); 

	if (++cursor.X>=WindowSize.Width) 
	{
		cursor.X=0;	WaitScroll=TRUE; CursorMoveDown();
	}
	else
		RepaintWndPos(cursor.X+cursor.Y*WindowSize.Width); 
}

void GPWindow::CursorMoveCR()
{
	WaitScroll=FALSE;
	RepaintWndPos(cursor.X+cursor.Y*WindowSize.Width); 
	cursor.X=0;
}

void GPWindow::CursorMoveUp()
{
	WaitScroll=FALSE;
	RepaintWndPos(cursor.X+cursor.Y*WindowSize.Width); 
	if (--cursor.Y<0) {	cursor.Y=0;	ScrollDown();	}
}

void GPWindow::CursorMoveDown()
{
	RepaintWndPos(cursor.X+cursor.Y*WindowSize.Width); 
	if (++cursor.Y>=WindowSize.Height) 
	{	
		cursor.Y=WindowSize.Height-1; 
		if (!WaitScroll) ScrollUp();
	}
	else WaitScroll=FALSE;
}

void GPWindow::SetCursorPosition(int x, int y)
{
	if (cursor.X!=x || cursor.Y!=y)
		RepaintWndPos(cursor.X+cursor.Y*WindowSize.Width); 
	WaitScroll=FALSE;
	if (x<WindowSize.Width && x>=0) cursor.X=x;
	else
	{
		CString tmps;
		tmps.Format("x=%d when cx=%d",x,WindowSize.Width);
		GPC.m_ErrReport.GPWriteErrorLog2("Green screen","SetCursorPosition wrong parameters",tmps);
	}

	if (y<WindowSize.Height && y>=0) cursor.Y=y;
	else
	{
		CString tmps;
		tmps.Format("y=%d when cy=%d",y,WindowSize.Height);
		GPC.m_ErrReport.GPWriteErrorLog2("Green screen","SetCursorPosition wrong parameters",tmps);
	}
}

void GPWindow::SetCursorPosition(Point &newPoint) 
{
	if (cursor.X!=newPoint.X || cursor.Y!=newPoint.Y)
		RepaintWndPos(cursor.X+cursor.Y*WindowSize.Width); 

	WaitScroll=FALSE;
	if (newPoint.X<WindowSize.Width && newPoint.X>=0) cursor.X= newPoint.X;
	else
	{
		CString tmps;
		tmps.Format("x=%d when cx=%d",newPoint.X,WindowSize.Width);
		GPC.m_ErrReport.GPWriteErrorLog2("Green screen","SetCursorPosition wrong parameters",tmps);
	}
	if (newPoint.Y<WindowSize.Height && newPoint.Y>=0) cursor.Y= newPoint.Y;
	else
	{
		CString tmps;
		tmps.Format("y=%d when cy=%d",newPoint.Y,WindowSize.Height);
		GPC.m_ErrReport.GPWriteErrorLog2("Green screen","SetCursorPosition wrong parameters",tmps);
	}
}

void GPWindow::CharOut(UINT pos, unsigned short ch)
{
	if ((m_ProtectedModeFlag&GP_FNT_FIXED)==GP_FNT_FIXED)
	{
		while(pos<nall && (WndChrStyle[pos]&GP_FNT_FIXED)==GP_FNT_FIXED) pos++;

		if (pos==nall)
		{
			pos-=WindowSize.Width;
			ScrollUp();
		}
	}

	if (pos<nall)
	{
		if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwChOutput++;

		if(ch>175 && ch<224) 
			WndChrStyle[pos]=(ChrStyle|GP_FNT_CODE)|(m_ProtectedFieldModeFlag&GP_FNT_FIXED);
		else	
		{
			WndChrStyle[pos]	=ChrStyle|(m_ProtectedFieldModeFlag&GP_FNT_FIXED);	// массив характеристик символов
		}
		ch=(ch&0xFF00)|GPC.chDosAnsi[ch&0xFF];

		WndChar[pos]		=ch;	// массив символов окна
		WndChrRGB[pos]		=ChrColor;	// массив цветов символов
		WndBkgRGB[pos]		=BkgColor;	// массив цветов фона
		RedrawWndPos(pos);
	}
}

void GPWindow::CharOutAW(UINT pos, char ch)
{
	if ((m_ProtectedModeFlag&GP_FNT_FIXED)==GP_FNT_FIXED)
	{
		while(pos<nall && (WndChrStyle[pos]&GP_FNT_FIXED)==GP_FNT_FIXED) pos++;
		if (pos==nall)
		{
			pos-=WindowSize.Width;
			ScrollUp();
		}
	}

	if (pos<nall)
	{
		if (GPC.dwGraphFlag)	CharOutGR(ch);
		else
		if (m_LastPrefix)
		{
			if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwChOutput++;
			WndChrStyle[pos]	=ChrStyle|(m_ProtectedFieldModeFlag&GP_FNT_FIXED);
			char chh[4];
			chh[1]=GPC.chWideDosAnsi2[ch];
			chh[0]=m_LastPrefix;
			//mbtowc(WndChar+pos,chh,2);

			GPC.MBConv3SrwPC(chh, chh);
			if (MultiByteToWideChar(
			  GPC.m_CurCodePage, // code page
			  MB_PRECOMPOSED,         // character-type options
			  chh, // string to map
			  2,       // number of bytes in string
			  (LPWSTR)(WndChar+pos),  // wide-character buffer
			  1        // size of buffer
			)==0)
			{
				WndChar[pos]=(chh[0]&0xFF);
				//WndChar[cursor.X+cursor.Y*WindowSize.Width]=(chh[1]&0xFF);
				m_NextMBOutChar=(chh[1]&0xFF);
			}

			WndChrRGB[pos]		=ChrColor;	// массив цветов символов
			WndBkgRGB[pos]		=BkgColor;	// массив цветов фона
			RedrawWndPos(pos);
			m_LastPrefix=0;
		}
		else
		{
			if (GPC.chWideDosAnsi[ch]) 
			{
				m_LastPrefix=GPC.chWideDosAnsi[ch];
				m_PrefixPosition=pos;
				WndChrStyle[pos]	=ChrStyle|(m_ProtectedFieldModeFlag&GP_FNT_FIXED);	// массив характеристик символов
			}
			else
			{

				if(ch>175 && ch<224) 
					WndChrStyle[pos]=((ChrStyle|GP_FNT_CODE)&(0xFFFFFFFF^(GP_FNT_BOLD|GP_FNT_UNDERLINE|GP_FNT_STRIKE|GP_FNT_ITALIC)))|(m_ProtectedFieldModeFlag&GP_FNT_FIXED);
				else	
				{
					WndChrStyle[pos]	=ChrStyle|(m_ProtectedFieldModeFlag&GP_FNT_FIXED);	// массив характеристик символов
				}
				ch=(ch&0xFF00)|GPC.chDosAnsi[ch&0xFF];
				WndChar[pos]		=ch;	// массив символов окна
			}
			WndChrRGB[pos]		=ChrColor;	// массив цветов символов
			WndBkgRGB[pos]		=BkgColor;	// массив цветов фона
			RedrawWndPos(pos);
		}
	}
}

void GPWindow::CharOutGR(UINT pos, char ch)
{
	if ((m_ProtectedModeFlag&GP_FNT_FIXED)==GP_FNT_FIXED)
	{
		while(pos<nall && (WndChrStyle[pos]&GP_FNT_FIXED)==GP_FNT_FIXED) pos++;
		if (pos==nall)
		{
			pos-=WindowSize.Width;
			ScrollUp();
		}
	}
	if (pos<nall)
	{
		if (GPC.dwGraphDecodeArray[ch]<0xFFFD)
		{
			WndChrStyle[pos]	=ChrStyle|(m_ProtectedFieldModeFlag&GP_FNT_FIXED);
			WndChar[pos]		=(unsigned short)GPC.dwGraphDecodeArray[ch];
			WndChrRGB[pos]		=ChrColor;	// массив цветов символов
			WndBkgRGB[pos]		=BkgColor;	// массив цветов фона
			RedrawWndPos(pos);
		}
		else
		{
			if (GPC.dwGraphDecodeArray[ch]>0xFFFD) GPC.dwGraphFlag=0;
			if (GPC.dwGraphDecodeArray[ch]==0xFFFE) CharOutAW(pos,ch);
		}
	}
}

void GPWindow::CharOut(UINT pos1,UINT  pos2)
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwChOutput++;
	WndChar[pos1]		=WndChar[pos2];
	WndChrRGB[pos1]		=WndChrRGB[pos2];
	WndBkgRGB[pos1]		=WndBkgRGB[pos2];
	WndChrStyle[pos1]	=WndChrStyle[pos2];
	RedrawWndPos(pos1);
}

void GPWindow::ClearEndOfWnd()
{
	UINT pos=cursor.X+cursor.Y*WindowSize.Width;
	if ((m_ProtectedModeFlag&GP_FNT_FIXED)==GP_FNT_FIXED)
		while(pos<nall)
		{
			if ((WndChrStyle[pos]&GP_FNT_FIXED)!=GP_FNT_FIXED)	CharOut(pos,ChrSpace);
			pos++;
		}
	else
		while(pos<nall) CharOut(pos++,ChrSpace);
}

void GPWindow::ClearEndOfLine()
{
	UINT pos=cursor.X+cursor.Y*WindowSize.Width;
	if ((m_ProtectedModeFlag&GP_FNT_FIXED)==GP_FNT_FIXED)
		while(pos<nall && (WndChrStyle[pos]&GP_FNT_FIXED)!=GP_FNT_FIXED) 
		{
			CharOut(pos++,ChrSpace);
			if ((pos%WindowSize.Width)==0) break;
		}
	else
		while(pos<nall) 
		{
			CharOut(pos++,ChrSpace);
			if ((pos%WindowSize.Width)==0) break;
		}
}

void GPWindow::ClearToBeginOfLine()
{
	UINT pos=cursor.X+cursor.Y*WindowSize.Width;
	int ntimes=cursor.X;
	if ((m_ProtectedModeFlag&GP_FNT_FIXED)==GP_FNT_FIXED)
		while(ntimes-->=0 && pos>=0 && (WndChrStyle[pos]&GP_FNT_FIXED)!=GP_FNT_FIXED) 
			CharOut(pos--,ChrSpace);
	else
		while(ntimes-->=0 && pos>=0) 
			CharOut(pos--,ChrSpace);
}

void GPWindow::CharOut(Point &pos, unsigned short ch) 
{
	CharOut(pos.X+pos.Y*WindowSize.Width,ch);
}

void GPWindow::CharOutAW(Point &pos, char ch) 
{
	CharOutAW(pos.X+pos.Y*WindowSize.Width,ch);
}

BOOL GPWindow::LoadScrRgn(const char *name, Point &topleft) 
{
	// for restore saved Green screen for very old GS apps
	BOOL ret=FALSE;
	char name1[256];
	UINT clr[20];
	sprintf(name1,"%s\\TABLE\\%s.TAB",GPC.app_path,name);
	FILE *tmp=fopen(name1,"rb");
	if (tmp) 
	{
		ret=TRUE;
		fgets(name1,250,tmp);
		BOOL cl;
		cl=!(*name1=='C' || *name1=='c');
		fgets(name1,250,tmp);
		fgets(name1,250,tmp);
		ReplaceChar(name1,0xFD,',');
		m_LastScanf=sscanf(name1,"%d,%d",clr,clr+1);
		int c;

		for(c=0;c<2;c++)
		switch(clr[c])
		{
			case -33: BkgColor=cBEtalon[7];BkgColorInd=7;break;
			case -34: BkgColor=cBEtalon[2];BkgColorInd=2;break;
			case -35: BkgColor=cBEtalon[3];BkgColorInd=3;break;
			case -36: BkgColor=cBEtalon[1];BkgColorInd=1;break;
			case -37: BkgColor=cBEtalon[5];BkgColorInd=5;break;
			case -38: BkgColor=cBEtalon[4];BkgColorInd=4;break;
			case -39: BkgColor=cBEtalon[6];BkgColorInd=6;break;
			case -40: BkgColor=cBEtalon[0];BkgColorInd=0;break;
			case -41: ChrColor=cFEtalon[7];ChrColorInd=7;break;
			case -42: ChrColor=cFEtalon[2];ChrColorInd=2;break;
			case -43: ChrColor=cFEtalon[3];ChrColorInd=3;break;
			case -44: ChrColor=cFEtalon[1];ChrColorInd=1;break;
			case -45: ChrColor=cFEtalon[5];ChrColorInd=5;break;
			case -46: ChrColor=cFEtalon[4];ChrColorInd=4;break;
			case -47: ChrColor=cFEtalon[6];ChrColorInd=6;break;
			case -48: ChrColor=cFEtalon[0];ChrColorInd=0;break;
			case -57: ChrColor=cFEtalon[15];ChrColorInd=15;break;
			case -58: ChrColor=cFEtalon[10];ChrColorInd=10;break;
			case -59: ChrColor=cFEtalon[11];ChrColorInd=11;break;
			case -60: ChrColor=cFEtalon[9 ];ChrColorInd=9 ;break;
			case -61: ChrColor=cFEtalon[13];ChrColorInd=13;break;
			case -62: ChrColor=cFEtalon[12];ChrColorInd=12;break;
			case -63: ChrColor=cFEtalon[14];ChrColorInd=14;break;
			case -64: ChrColor=cFEtalon[8 ];ChrColorInd=8 ;break;
		}

		fgets(name1,250,tmp);
		fgets(name1,250,tmp);
		Rect re;
		ReplaceChar(name1,0xFD,',');
		m_LastScanf=sscanf(name1,"%d,%d,%d,%d",&re.X,&re.Y,&re.Width,&re.Height);
		re.Width++;	re.Height++;
		re.Width-=re.X;	re.Height-=re.Y;
		if (topleft.X!=100) {re.Width-=(re.X-topleft.X);re.X=topleft.X;}
		if (topleft.Y!=100) {re.Height-=(re.Y-topleft.Y);re.Y=topleft.Y;}

		int y=re.Y;
		if (cl) ClearRect(re);


		while(fgets(name1,250,tmp)!=NULL)
		{
			if (y>=0)
			{
				int x=re.X;
				char *pos=name1;
				while(x<0 && *pos!=0) {pos++;x++;}
				while(x<re.GetRight() && *pos!=0 && x<WindowSize.Width) 
				{
					UINT wpos=y*WindowSize.Width+x;
					if (wpos<nall && *pos>=' ')	CharOut(wpos,(unsigned short)(*pos&0xFF));
					x++;pos++;
				}
			}
			y++;
		}
		fclose(tmp);
		
		RedrawRect(re);
	}
	return ret;
}

void GPWindow::RecolorString(int posX, int posY, int LineLength)
{
	UINT pos=posX+posY*WindowSize.Width;
	if (pos<nall)
	{
		CString tmps;
		tmps.Format("x=%d , y=%d",posX,posY);
		GPC.m_ErrReport.GPWriteErrorLog2("Green screen","RecolorString wrong parameters",tmps);
	}

	while(pos<nall && (LineLength--)>0) 
	{
		WndBkgRGB[pos]=BkgColor;
		WndChrRGB[pos]=ChrColor;
		RedrawWndPos(pos++);
	}
}

void GPWindow::CharLine(Point &pos1, Point &pos2,unsigned short Ch)
{
	UINT pos=pos1.X+pos1.Y*WindowSize.Width;
	if (pos1.X!=pos2.X)
		while(pos<nall && (pos%WindowSize.Width)<(UINT)pos2.X) 
		{
			CharOut(pos++,Ch);
		}
	else
		while(pos<(int)nall && (pos/WindowSize.Width)<(UINT)pos2.Y) 
		{
			CharOut(pos,Ch);
			pos+=WindowSize.Width;
		}
}

void GPWindow::ShadowOld(Rect &re,int type)
{
	int pos;
	int n;
	if (type==0) pos=(re.Y+1)*WindowSize.Width+re.GetRight();
		else	 pos=(re.Y-1)*WindowSize.Width+re.GetRight();

	for(n=0;pos<(int)nall && n<re.Height;pos+=WindowSize.Width,n++)
	if (pos>=0 && pos<(int)nall)
	{
		ShadowColor(WndChrRGB[pos]);
		ShadowColor(WndBkgRGB[pos]);
		RedrawWndPos(pos);
	}

	if (type==0) pos=(re.GetBottom())*WindowSize.Width+re.X+1;
		else	 pos=(re.Y-1)*WindowSize.Width+re.X+1;

	for(n=1;pos<(int)nall && n<re.Width;pos++,n++)
	if (pos>=0)
	{
		ShadowColor(WndChrRGB[pos]);
		ShadowColor(WndBkgRGB[pos]);
		RedrawWndPos(pos);
	}
	
}

void GPWindow::TextHorLine(int x, int y, int typ, int len)
{
// Нарисовать горизонтальную текстовую линию по координатам x y длиной len 
// производится объединение с расположенными рядом линиями 
// type 0   single
// type 1   double
// type 2   space
	
	const char chstrt0[]={0xC4,0xDA,0xD6,0xC0,0xC3,0xC3,0xD3,0xC3,0xC7,0xC4,0xC2,0xD2,0xC1,0xC5,0xC5,0xD0,0xC5,0xD7,0x0,};
	const char chstrt1[]={0xCD,0xD5,0xC9,0xD4,0xC6,0xC6,0xC8,0xC6,0xCC,0xCD,0xD1,0xCB,0xCF,0xD8,0xD8,0xCA,0xD8,0xCE,0x0,};
	const char chend0[] ={0xC4,0xBF,0xB7,0xD9,0xB4,0xB4,0xBD,0xB4,0xB6,0xC4,0xC2,0xD2,0xC1,0xC5,0xC5,0xD0,0xC5,0xD7,0x0,};
	const char chend1[] ={0xCD,0xB8,0xBB,0xBE,0xB5,0xB5,0xBC,0xB5,0xB9,0xCD,0xD1,0xCB,0xCF,0xD8,0xD8,0xCA,0xD8,0xCE,0x0,};
	const char *chstrt[]={chstrt0,chstrt1,};
	const char *chend[]={chend0,chend1,};
	char typeup[]   ={0xC3,0xC5,0xB4,0xB3,0xD5,0xD1,0xB8,0xC6,0xD8,0xB5,0xDA,0xC2,0xBF,0xD6,0xD2,0xB7,0xC7,0xD7,0xB6,0xBA,0xC9,0xCB,0xBB,0xCC,0xCE,0xB9,0x0,};
	char typedown[] ={0xC3,0xC5,0xB4,0xB3,0xC0,0xC1,0xD9,0xC6,0xD8,0xB5,0xD4,0xCF,0xBE,0xC7,0xD7,0xB6,0xBA,0xD3,0xD0,0xBD,0xCC,0xCE,0xB9,0xC8,0xCA,0xBC,0x0,};
	char typeleft[] ={0xDA,0xC4,0xC2,0xC3,0xC5,0xC0,0xC1,0xD6,0xD2,0xC7,0xD7,0xD3,0xD0,0xC9,0xCD,0xCB,0xCC,0xCE,0xC8,0xCA,0xD5,0xD1,0xC6,0xD8,0xD4,0xCF,0x0,};
	char typeright[]={0xC4,0xC2,0xBF,0xC5,0xB4,0xC1,0xD9,0xD2,0xB7,0xD7,0xB6,0xD0,0xBD,0xCD,0xCB,0xBB,0xCE,0xB9,0xCA,0xBC,0xD1,0xB8,0xD8,0xB5,0xCF,0xBE,0x0,};
	UINT pos,posend;

	int chl,chr,chu,chd;

	if (y<0) y=0;
	if (x<0) x=0;
	if(y<WindowSize.Height && x<WindowSize.Width) 
	{
		chl=chu=chd=0;
		if (len+x>WindowSize.Width) len=WindowSize.Width-x;
		pos=x+y*WindowSize.Width;
		posend=pos+len;
		if(typ==2)
		{
			while(pos<posend && pos<nall)
				CharOut(pos++,ChrSpace);
		}
		else
		if(typ>2)
		{
			while(pos<posend && pos<nall)
			{CharOut(pos++,(unsigned short)typ);}
		}
		else
		{
			if (x!=0 && (WndChrStyle[pos-1]&GP_FNT_CODE)!=0 && strchr(typeleft,WndChar[pos-1])!=NULL) chl++;
			if (y!=0 && (WndChrStyle[pos-WindowSize.Width]&GP_FNT_CODE)!=0 )      chu=(strchr(typeup,WndChar[pos-WindowSize.Width])-typeup)/13+1;
			if (y!=WindowSize.Height-1 && (WndChrStyle[pos+WindowSize.Width]&GP_FNT_CODE)!=0 ) chd=(strchr(typedown,WndChar[pos+WindowSize.Width])-typedown)/13+1;
			if (chd<0)     chd=0;
			if (chu<0)     chu=0;
			unsigned short tmpus=(unsigned short)(*(chstrt[typ]+chl*9+chu*3+chd));
			tmpus&=0xFF;
			CharOut(pos++,tmpus);
			posend--;
			while(pos<nall && pos<posend)
			{
				chu=chd=0;
				if (y!=0 && (WndChrStyle[pos-WindowSize.Width]&GP_FNT_CODE)!=0) chu=(strchr(typeup,WndChar[pos-WindowSize.Width])-typeup)/13+1;
				if (y!=WindowSize.Height-1&& (WndChrStyle[pos+WindowSize.Width]&GP_FNT_CODE)!=0) chd=(strchr(typedown,WndChar[pos+WindowSize.Width])-typedown)/13+1;
				if (chd<0)     chd=0;
				if (chu<0)     chu=0;
				tmpus=(unsigned short(*(chstrt[typ]+9+chu*3+chd)));
				tmpus&=0xFF;
				CharOut(pos++,tmpus);
			}

			chl=chr=chu=chd=0;
			if (y!=0 && (WndChrStyle[pos-WindowSize.Width]&GP_FNT_CODE)!=0) chu=(strchr(typeup,WndChar[pos-WindowSize.Width])-typeup)/13+1;
			if (y!=WindowSize.Height-1 && (WndChrStyle[pos+WindowSize.Width]&GP_FNT_CODE)!=0) chd=(strchr(typedown,WndChar[pos+WindowSize.Width])-typedown)/13+1;
			if (x!=WindowSize.Width-1 && (WndChrStyle[pos+1]&GP_FNT_CODE)!=0 && strchr(typeright,WndChar[pos+1])!=NULL) chr++;
			if (chd<0) chd=0;
			if (chu<0) chu=0;
			tmpus=(unsigned short(*(chend[typ]+chr*9+chu*3+chd)));
			tmpus&=0xFF;
			CharOut(pos,tmpus);
		}
	}
}

void GPWindow::TextVerLine(int x, int y, int typ, int len)
{
// Нарисовать вертикальную текстовую линию по координатам x y длиной len 
// производится объединение с расположенными рядом линиями 
// type 0   single
// type 1   double
// type 2   space

	const char chstrt0[]={0xB3,0xDA,0xD5,0xBF,0xC2,0xC2,0xB8,0xC2,0xD1,0xB3,0xC3,0xC6,0xB4,0xC5,0xC5,0xB5,0xC5,0xD8,0x0,};
	const char chstrt1[]={0xBA,0xD6,0xC9,0xB7,0xD2,0xD2,0xBB,0xD2,0xCB,0xBA,0xC7,0xCC,0xB6,0xD7,0xD7,0xB9,0xD7,0xCE,0x0,};
	const char chend0[] ={0xB3,0xC0,0xD4,0xD9,0xC1,0xC1,0xBE,0xC1,0xCF,0xB3,0xC3,0xC6,0xB4,0xC5,0xC5,0xB5,0xC5,0xD8,0x0,};
	const char chend1[] ={0xBA,0xD3,0xC8,0xBD,0xD0,0xD0,0xBC,0xD0,0xCA,0xBA,0xC7,0xCC,0xB6,0xD7,0xD7,0xB9,0xD7,0xCE,0x0,};
	const char *chstrt[]={chstrt0,chstrt1,};
	const char *chend[] ={chend0,chend1,};
	char typeup[]   ={0xC3,0xC5,0xB4,0xB3,0xD5,0xD1,0xB8,0xC6,0xD8,0xB5,0xDA,0xC2,0xBF,0xD6,0xD2,0xB7,0xC7,0xD7,0xB6,0xBA,0xC9,0xCB,0xBB,0xCC,0xCE,0xB9,0x0,};
	char typedown[] ={0xC3,0xC5,0xB4,0xB3,0xC0,0xC1,0xD9,0xC6,0xD8,0xB5,0xD4,0xCF,0xBE,0xC7,0xD7,0xB6,0xBA,0xD3,0xD0,0xBD,0xCC,0xCE,0xB9,0xC8,0xCA,0xBC,0x0,};
	char typeleft[] ={0xDA,0xC4,0xC2,0xC3,0xC5,0xC0,0xC1,0xD6,0xD2,0xC7,0xD7,0xD3,0xD0,0xC9,0xCD,0xCB,0xCC,0xCE,0xC8,0xCA,0xD5,0xD1,0xC6,0xD8,0xD4,0xCF,0x0,};
	char typeright[]={0xC4,0xC2,0xBF,0xC5,0xB4,0xC1,0xD9,0xD2,0xB7,0xD7,0xB6,0xD0,0xBD,0xCD,0xCB,0xBB,0xCE,0xB9,0xCA,0xBC,0xD1,0xB8,0xD8,0xB5,0xCF,0xBE,0x0,};

	UINT pos,posend;
	int chl,chr,chu,chd;
	unsigned short tmpus;

	if (y<0) y=0;
	if (x<0) x=0;
	if(y<WindowSize.Height && x<WindowSize.Width) 
	{
		if (len+y>WindowSize.Height) len=WindowSize.Height-y;
		pos=x+y*WindowSize.Width;
		posend=pos+len*WindowSize.Width;
		if(typ==2)
		{
			while(pos<posend && pos<nall)
			{
				CharOut(pos,ChrSpace); 
				pos+=WindowSize.Width;
			}
		}
		else
		if(typ>2)
		{
			while(pos<posend && pos<nall)
			{
				CharOut(pos,(unsigned short)typ);
				pos+=WindowSize.Width;
			}
		}
		else
		{
			chl=chu=chr=0;
			if (y!=0 && (WndChrStyle[pos-WindowSize.Width]&GP_FNT_CODE)!=0 && strchr(typeup,WndChar[pos-WindowSize.Width])!=NULL) chu++;
			if (x!=0 && (WndChrStyle[pos-1]&GP_FNT_CODE)!=0)				chl=(strchr(typeleft,WndChar[pos-1])-typeleft)/13+1;
			if (x!=WindowSize.Width-1 && (WndChrStyle[pos+1]&GP_FNT_CODE)!=0)	chr=(strchr(typeright,WndChar[pos+1])-typeright)/13+1;
			if (chl<0)         chl=0;
			if (chr<0)         chr=0;
			tmpus=(unsigned short(*(chstrt[typ]+chu*9+chl*3+chr)));
			tmpus&=0xFF;
			CharOut(pos,tmpus);
			pos+=WindowSize.Width;

			while(pos<posend-WindowSize.Width && pos<nall-WindowSize.Width)
			{
				chl=chr=0;
				if (x!=0 && (WndChrStyle[pos-1]&GP_FNT_CODE)!=0)				chl=(strchr(typeleft,WndChar[pos-1])-typeleft)/13+1;
				if (x!=WindowSize.Width-1 && (WndChrStyle[pos+1]&GP_FNT_CODE)!=0)	chr=(strchr(typeright,WndChar[pos+1])-typeright)/13+1;
  				if (chl<0)     chl=0;
				if (chr<0)     chr=0;
				tmpus=(unsigned short(*(chstrt[typ]+9+chl*3+chr)));
				tmpus&=0xFF;
				CharOut(pos,tmpus);

				pos+=WindowSize.Width;
			}

			chl=chr=chd=0;
			if (x!=0 && (WndChrStyle[pos-1]&GP_FNT_CODE)!=0)				chl=(strchr(typeleft,WndChar[pos-1])-typeleft)/13+1;
			if (x!=WindowSize.Width-1 && (WndChrStyle[pos+1]&GP_FNT_CODE)!=0)	chr=(strchr(typeright,WndChar[pos+1])-typeright)/13+1;
			if (pos<nall-WindowSize.Width && (WndChrStyle[pos+WindowSize.Width]&GP_FNT_CODE)!=0 && strchr(typedown,WndChar[pos+WindowSize.Width])!=NULL) chd++;
			if (chl<0) chl=0;
			if (chr<0) chr=0;
			tmpus=(unsigned short(*(chend[typ]+chd*9+chl*3+chr)));
			tmpus&=0xFF;
			CharOut(pos,tmpus);
		}
	}
}

void GPWindow::TextBox(Rect &re,int type)
{
// Нарисовать текстовую рамку по размерам re если type > 0xFFFF то 
// объединение с расположенными рядом линиями не производится
// type = 0 - одинарная рамка
// type = 1 - двойная рамка
// type = 2 - пробельная рамка
// type = &0x1001 - double left
// type = &0x1002 - double right
// type = &0x1004 - double top
// type = &0x1008 - double bottom
// type = &0x20000 - custom borders
// type = &0x10000 - connect sidelines 

	if ((type&0x10000)==0)
	{
		int typeLine=type&0x1F;
		if (type&0x20000)
		{
		}
		else 
		{
			typeLine&=0x3;
			if (typeLine==2) typeLine=0x10;
			else
			if (typeLine==1) typeLine=0x0F;
			else typeLine=0;
		}
		char ch[]={//	 T     B	 LT	   RT    LB	   RB        V H V H
			0xC4, 0xC4, 0xB3, 0xB3, 0xDA, 0xBF, 0xC0, 0xD9, //0  1 1 1 1
			0xCD, 0xC4, 0xB3, 0xB3, 0xD5, 0xB8, 0xC0, 0xD9, //1  2 1 1 1
			0xC4, 0xCD, 0xB3, 0xB3, 0xDA, 0xBF, 0xD4, 0xBE, //2  1 1 2 1
			0xCD, 0xCD, 0xB3, 0xB3, 0xD5, 0xB8, 0xD4, 0xBE, //3  2 1 2 1
			0xC4, 0xC4, 0xBA, 0xB3, 0xD6, 0xBF, 0xD3, 0xD9, //4  1 2 1 1
			0xCD, 0xC4, 0xBA, 0xB3, 0xC9, 0xB8, 0xD3, 0xD9, //5  2 2 1 1
			0xC4, 0xCD, 0xBA, 0xB3, 0xD6, 0xBF, 0xC8, 0xBE, //6  1 2 2 1
			0xCD, 0xCD, 0xBA, 0xB3, 0xC9, 0xB8, 0xC8, 0xBE, //7  2 2 2 1
			0xC4, 0xC4, 0xB3, 0xBA, 0xDA, 0xB7, 0xC0, 0xBD, //8  1 1 1 2
			0xCD, 0xC4, 0xB3, 0xBA, 0xD5, 0xBB, 0xC0, 0xBD, //9  2 1 1 2
			0xC4, 0xCD, 0xB3, 0xBA, 0xDA, 0xB7, 0xD4, 0xBC, //A  1 1 2 2
			0xCD, 0xCD, 0xB3, 0xBA, 0xD5, 0xBB, 0xD4, 0xBC, //B  2 1 2 2
			0xC4, 0xC4, 0xBA, 0xBA, 0xD6, 0xB7, 0xD3, 0xBD, //C  1 2 1 2
			0xCD, 0xC4, 0xBA, 0xBA, 0xC9, 0xBB, 0xD3, 0xBD, //D  2 2 1 2
			0xC4, 0xCD, 0xBA, 0xBA, 0xD6, 0xB7, 0xC8, 0xBC, //E  1 2 2 2
			0xCD, 0xCD, 0xBA, 0xBA, 0xC9, 0xBB, 0xC8, 0xBC, //F  2 2 2 2
			0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, //10 
			0x0,};
		//char *ch="ДіЪїАЩНєЙ»Иј       ";
		if (re.Width>2)
		{
			CharLine(Point(re.X,re.Y),	Point(re.GetRight()-1,re.Y), ch[(typeLine)*8]);
			if (re.Height>1)
				CharLine(Point(re.X ,re.GetBottom()-1),Point(re.GetRight()-1,re.GetBottom()-1), ch[(typeLine)*8+1]);
		}
		if (re.Height>2)
		{
			CharLine(Point(re.X,re.Y),	Point(re.X,re.GetBottom()-1), ch[(typeLine)*8+2]);
			if (re.Width>1)
				CharLine(Point(re.GetRight()-1,re.Y),	Point(re.GetRight()-1,re.GetBottom()-1), ch[(typeLine)*8+3]);
		}
		if (re.Height>1 && re.Width>1)
		{
			CharOut(Point(re.X,re.Y),						ch[(typeLine)*8+4]);
			CharOut(Point(re.GetRight()-1,re.Y),				ch[(typeLine)*8+5]);
			CharOut(Point(re.X,re.GetBottom()-1),				ch[(typeLine)*8+6]);	
			CharOut(Point(re.GetRight()-1,re.GetBottom()-1),	ch[(typeLine)*8+7]);
		}
	}
	else
	{
		if ((type&0x20000))
		{
			if (re.Height>1)
			{
				TextVerLine(re.X, re.Y,	(type&0x1)?1:0, re.Height);
				TextVerLine(re.GetRight()-1,re.Y,	(type&0x2)?1:0, re.Height);
			}
			if (re.Width>1)
			{
				TextHorLine(re.X, re.Y,	(type&0x4)?1:0, re.Width);
				TextHorLine(re.X, re.GetBottom()-1, (type&0x8)?1:0, re.Width);
			}
		}
		else
		{
			type&=0xFFFF;
			if (re.Height>1)
			{
				TextVerLine(re.X, re.Y,	type, re.Height);
				TextVerLine(re.GetRight()-1,re.Y,	type, re.Height);
			}
			if (re.Width>1)
			{
				TextHorLine(re.X, re.Y,	type, re.Width);
				TextHorLine(re.X, re.GetBottom()-1, type, re.Width);
			}
		}
	}
}

UINT GPWindow::CreateUnit(UINT iType, UINT iId, const char *iProp, HWND pParentWnd)
{
	UINT ret=0;
	CString tpms;
	tpms.Format("object %d",iId);
	if (iId>=m_NGPUNITmax && iId<0x10000)
	{
		UINT newNMax=iId+5000;
		if (newNMax>0x10000) newNMax=0xFFFF;
		GPUnit **GPUtmp= new GPUnit * [newNMax];
		ZeroMemory(GPUtmp,sizeof(GPUnit *)*newNMax);
		UINT i;
		GPUtmp[0]=WndUnit[0];
		for(i=1;i<WndUnit[0]->m_NGPUNIT;i++)
			if ((GPUtmp[i]=WndUnit[i]))
			{
				GPUtmp[i]->GPU=GPUtmp;
				GPUtmp[i]->SetReferGPU(GPUtmp);
				GPUtmp[i]->GPMSG->SetReferGPU(GPUtmp);
			}

		GPUtmp[0]->GPU=GPUtmp;
		GPUtmp[0]->GPMSG->SetReferGPU(GPUtmp);
		delete []WndUnit;
		WndUnit=GPUtmp;
		m_NGPUNITmax=newNMax;
	}
	if (iId>0 && WndUnit!=NULL && iId<m_NGPUNITmax)
	{
		if (WndUnit[iId]==NULL)
		{
			if (iId>=WndUnit[0]->m_NGPUNIT) WndUnit[0]->m_NGPUNIT=iId+1;
			WndUnit[iId]=new GPUnit(iId,iType,iProp,WndUnit, &(GPC.m_ScrToolTip),GPC.m_hViewWnd,GPC.m_View->m_AUSI);		
			ret=iId;
		}
		else GPC.m_ErrReport.GPWriteErrorLog2("Object already exist",tpms ,iProp);
	}
	else GPC.m_ErrReport.GPWriteErrorLog2("Can't create object",tpms ,iProp);

	return ret;
}

void GPWindow::DeleteUnit(UINT iObjId, BOOL bReport)
{
	UINT iId=GetObjectNum(iObjId);
	BOOL rep=FALSE;
	if (iId>0)
	{
		if (iId<WndUnit[0]->m_NGPUNIT && WndUnit[iId])
		{
			if (WndUnit[iId]==GPUnit::m_ptrUnitValChange) 
			{
				GPUnit::m_ptrUnitValChange=NULL;
//					TRACE("m_ptrUnitValChange=NULL DeleteUnit %s\n",GPU[iId]->UnitInfoToString("\x01") );
			}
			UINT i;
			for(i=1;i<WndUnit[0]->m_NGPUNIT;i++)
				if (WndUnit[i] && i!=iId)
				{
					if (WndUnit[i]->UnitHWND!=NULL && ::GetParent(WndUnit[i]->UnitHWND)==WndUnit[iId]->UnitHWND)
					{
						if (bReport)
						{
							CString tpms=WndUnit[iId]->UnitInfoToString("\x01")+"\x02"+WndUnit[i]->UnitInfoToString("\x01");
							GPC.m_ErrReport.GPWriteWarnLog("Implicit deleting of child object",WndUnit[0]->UnitInfoToString("\x01") ,tpms);
						}
						DeleteUnit(i, bReport);
					}
				}

			if (WndUnit[iId]->UnitHWND && ::IsWindow(WndUnit[iId]->UnitHWND))
			{
				::SetWindowLong(WndUnit[iId]->UnitHWND,GWL_STYLE,::GetWindowLong(WndUnit[iId]->UnitHWND,GWL_STYLE)|WS_DISABLED);
				//::DestroyWindow(WndUnit[num]->UnitHWND);
			}
			delete WndUnit[iId];
			WndUnit[iId]=NULL;
			for(i=iId+1;i<WndUnit[0]->m_NGPUNIT && !WndUnit[i];i++)
			if (i>=WndUnit[0]->m_NGPUNIT)
			{
				WndUnit[0]->m_NGPUNIT=iId;
				for(i=iId;i>0 && !WndUnit[i];i--)
					WndUnit[0]->m_NGPUNIT=i;
			}
		}
		else rep=TRUE;
	}
	else rep=TRUE;

	if (bReport && rep)
	{
		CString tpms;
		tpms.Format("object %d",iObjId);
		GPC.m_ErrReport.GPWriteWarnLog("Try to delete nonexistent object",tpms ,"");
	}
}

UINT GPWindow::GetObjectNum(UINT iObjId)
{
	return (iObjId>=(*WndUnit)->m_NGPUNIT) ? 0:iObjId;
}

void GPWindow::SetViewState(UINT iState)	
{
	GPWndState=iState;
}

GPUnit * GPWindow::GetUnitById(UINT iUnitId)	
{
	return GetUnitByNum(GetObjectNum(iUnitId));
}

GPUnit * GPWindow::GetUnitByNum(UINT iUnitNum)	
{	
	return iUnitNum>=(*WndUnit)->m_NGPUNIT?NULL:WndUnit[iUnitNum];
}

// Функция очистки текстового прямоугольника
void GPWindow::ClearRect(Rect &iRect)
{
	int y;
	int btm=iRect.GetBottom();
	for(y=iRect.Y;y<btm;y++)
		if (y>=0)
		{
			int x;
			int rght=iRect.GetRight();
			for(x=iRect.X;x<rght && x<WindowSize.Width;x++)
			{
				UINT wpos=y*WindowSize.Width+x;
				if (wpos<nall)
				{

					if ((m_ProtectedModeFlag&GP_FNT_FIXED)==GP_FNT_FIXED)
					{
						if ((WndChrStyle[wpos]&GP_FNT_FIXED)!=GP_FNT_FIXED)
						{
							if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwChOutput++;
							WndChar[wpos]		=ChrSpace;
							if(ChrSpace>175 && ChrSpace<224) 
								WndChrStyle[wpos]=(ChrStyle|GP_FNT_CODE);

							WndChrRGB[wpos]		=ChrColor;
							WndBkgRGB[wpos]		=BkgColor;
						}
					}
					else
					{
						if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwChOutput++;
						WndChar[wpos]		=ChrSpace;
						WndChrRGB[wpos]		=ChrColor;
						WndBkgRGB[wpos]		=BkgColor;
						if(ChrSpace>175 && ChrSpace<224) 
							WndChrStyle[wpos]=(ChrStyle|GP_FNT_CODE)|(m_ProtectedFieldModeFlag&GP_FNT_FIXED);
						else
							WndChrStyle[wpos]	=ChrStyle|(m_ProtectedFieldModeFlag&GP_FNT_FIXED);
					}
				}
			}
		}
	RedrawRect(iRect);
}

void GPWindow::GPInvertWnd()
{
	UINT i;
	for(i=0;i<nall;i++) 
	{
		WndChrRGB[i]^=0xFFFFFF;
		WndBkgRGB[i]^=0xFFFFFF;
	}
	RedrawWnd();
}

void GPWindow::RecolorWnd(UINT iFrg, UINT iBkg)
{
	UINT i;
	ChrColor=iFrg;
	BkgColor=iBkg;
	for(i=0;i<nall;i++) 
	{
		WndChrRGB[i]=ChrColor;
		WndBkgRGB[i]=BkgColor;
	}

	RedrawWnd();
}

void GPWindow::DoMethod(UINT UnitId, const char *iStr, char *oStr)
{
	UINT num=GetObjectNum(UnitId);
	if (WndUnit[num] && WndUnit[num]->UnitHWND) 
		WndUnit[num]->DoMethod(iStr, oStr);
}

void GPWindow::CursorMoveLF()
{
	CursorMoveDown();
}

void GPWindow::DelChar(UINT nTimes)
{
	unsigned int poschar=cursor.X+cursor.Y*WindowSize.Width;
	if (nTimes>nall-poschar) nTimes=nall-poschar+1;
	while(nTimes-->0) DelChar(cursor);
}

void GPWindow::InsertChar(UINT nTimes)
{
	unsigned int poschar=cursor.X+cursor.Y*WindowSize.Width;
	if (nTimes>nall-poschar) nTimes=nall-poschar+1;
	while(nTimes-->0) InsertChar(cursor);
}

void GPWindow::InsertLine(UINT nTimes)
{
	if (nTimes>(UINT)(WindowSize.Height-cursor.Y)) nTimes=WindowSize.Height-cursor.Y+1;
	while(nTimes-->0) InsertLine(cursor.Y);
}

void GPWindow::DelLine(UINT nTimes)
{
	if (nTimes>(UINT)(WindowSize.Height-cursor.Y)) nTimes=WindowSize.Height-cursor.Y+1;
	while(nTimes-->0) DelLine(cursor.Y);
}


void GPWindow::DelChar(Point &pos)
{
	unsigned int poschar=pos.X+pos.Y*WindowSize.Width;
	if (poschar<nall)
	{
		if (poschar==m_PrefixPosition)
		{
			m_PrefixPosition=0xC0000000;
		}
		else 
			if (m_PrefixPosition>poschar) m_PrefixPosition++;

		if (poschar==m_PrefixPositionEx)
		{
			m_PrefixPositionEx=0xC0000000;
		}
		else 
			if (m_PrefixPositionEx>poschar) m_PrefixPositionEx++;

		if ((m_ProtectedModeFlag&GP_FNT_FIXED)==GP_FNT_FIXED)
			while(++poschar<nall && (WndChrStyle[poschar]&GP_FNT_FIXED)!=GP_FNT_FIXED)
			{
				WndChar[poschar-1]		=WndChar[poschar];
				WndChrRGB[poschar-1]	=WndChrRGB[poschar];
				WndBkgRGB[poschar-1]	=WndBkgRGB[poschar];
				WndChrStyle[poschar-1]	=WndChrStyle[poschar]|(m_ProtectedFieldModeFlag&GP_FNT_FIXED);
			}
		else
			while(++poschar<nall)
			{
				WndChar[poschar-1]		=WndChar[poschar];
				WndChrRGB[poschar-1]	=WndChrRGB[poschar];
				WndBkgRGB[poschar-1]	=WndBkgRGB[poschar];
				WndChrStyle[poschar-1]	=WndChrStyle[poschar]|(m_ProtectedFieldModeFlag&GP_FNT_FIXED);
			}
		if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwChOutput++;
		WndChar[--poschar]		=ChrSpace;
		WndChrRGB[poschar]		=ChrColor;
		WndBkgRGB[poschar]		=BkgColor;
		WndChrStyle[poschar]	=ChrStyle|(m_ProtectedFieldModeFlag&GP_FNT_FIXED);
		RedrawRect(Rect(pos.X,pos.Y,WindowSize.Width-1,WindowSize.Height-1));
	}
}

void GPWindow::InsertChar(Point &pos)
{
	int poscur=pos.X+pos.Y*WindowSize.Width;
//	int poschar=nall-1;
	int poschar=(pos.Y+1)*WindowSize.Width-1;
	if ((UINT)poscur<nall)
	{
		if (m_PrefixPosition==poscur)
		{
			m_PrefixPosition=0xC0000000;
		}
		else
			if (m_PrefixPosition<=(UINT)poschar && m_PrefixPosition>(UINT)poscur) m_PrefixPosition++;

		if (m_PrefixPositionEx==poscur)
		{
			m_PrefixPositionEx=0xC0000000;
		}
		else
			if (m_PrefixPositionEx<=(UINT)poschar && m_PrefixPositionEx>(UINT)poscur) m_PrefixPositionEx++;

		if ((m_ProtectedModeFlag&GP_FNT_FIXED)==GP_FNT_FIXED)
			while(poschar>0 && --poschar>=poscur && (WndChrStyle[poschar+1]&GP_FNT_FIXED)!=GP_FNT_FIXED)
			{
				WndChar[poschar+1]		=WndChar[poschar];
				WndChrRGB[poschar+1]	=WndChrRGB[poschar];
				WndBkgRGB[poschar+1]	=WndBkgRGB[poschar];
				WndChrStyle[poschar+1]	=WndChrStyle[poschar]|(m_ProtectedFieldModeFlag&GP_FNT_FIXED);
			}
		else
			while(poschar>0 && --poschar>=poscur)
			{
				WndChar[poschar+1]		=WndChar[poschar];
				WndChrRGB[poschar+1]	=WndChrRGB[poschar];
				WndBkgRGB[poschar+1]	=WndBkgRGB[poschar];
				WndChrStyle[poschar+1]	=WndChrStyle[poschar]|(m_ProtectedFieldModeFlag&GP_FNT_FIXED);
			}
		if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwChOutput++;
		WndChar[++poschar]		=ChrSpace;
		WndChrRGB[poschar]		=ChrColor;
		WndBkgRGB[poschar]		=BkgColor;

		WndChrStyle[poschar]	=ChrStyle|(m_ProtectedFieldModeFlag&GP_FNT_FIXED);

		RedrawRect(Rect(pos.X,pos.Y,WindowSize.Width-1,WindowSize.Height-1));
	}
}

void GPWindow::DelLine(int pos)
{
	if (pos>=0 && pos<WindowSize.Height-1)
	{
		UINT poschar=pos*WindowSize.Width;
		if (m_PrefixPosition>=poschar && m_PrefixPosition<poschar+WindowSize.Width)
		{
			m_PrefixPosition=0xC0000000;
		}
		else
		if (m_PrefixPosition>poschar) m_PrefixPosition-=WindowSize.Width;

		if (m_PrefixPositionEx>=poschar && m_PrefixPositionEx<poschar+WindowSize.Width)
		{
			m_PrefixPositionEx=0xC0000000;
		}
		else
		if (m_PrefixPositionEx>poschar) m_PrefixPositionEx-=WindowSize.Width;

		while(poschar<nall-WindowSize.Width)
		{
			WndChar[poschar]	=WndChar[poschar+WindowSize.Width];
			WndChrRGB[poschar]	=WndChrRGB[poschar+WindowSize.Width];
			WndBkgRGB[poschar]	=WndBkgRGB[poschar+WindowSize.Width];
			WndChrStyle[poschar]=WndChrStyle[poschar+WindowSize.Width];
			poschar++;
		}

		while(poschar<nall)
		{
			WndChar[poschar]		=ChrSpace;
			WndChrRGB[poschar]		=ChrColor;
			WndBkgRGB[poschar]		=BkgColor;
			WndChrStyle[poschar++]	=ChrStyle|(m_ProtectedFieldModeFlag&GP_FNT_FIXED);
		}
		RedrawRect(Rect(0,pos,WindowSize.Width-1,WindowSize.Height-1));
	}
	else
	{
		CString tmps;
		tmps.Format("n=%d",pos);
		GPC.m_ErrReport.GPWriteErrorLog2("Green screen","DelLine wrong parameters",tmps);
	}


}

void GPWindow::InsertLine(int pos)
{
	if (pos>=0 && pos<WindowSize.Height)
	{
		int posend=pos*WindowSize.Width;
		int poschar=nall-1;
		if (m_PrefixPosition>=(UINT)posend) m_PrefixPosition+=WindowSize.Width;
		if (m_PrefixPosition>=nall)
		{
			m_PrefixPosition=0xC0000000;
		}

		if (m_PrefixPositionEx>=(UINT)posend) m_PrefixPositionEx+=WindowSize.Width;
		if (m_PrefixPositionEx>=nall)
		{
			m_PrefixPositionEx=0xC0000000;
		}

		while(poschar>=posend+WindowSize.Width)
		{
			WndChar[poschar]	=WndChar[poschar-WindowSize.Width];
			WndChrRGB[poschar]	=WndChrRGB[poschar-WindowSize.Width];
			WndBkgRGB[poschar]	=WndBkgRGB[poschar-WindowSize.Width];
			WndChrStyle[poschar]=WndChrStyle[poschar-WindowSize.Width];
			poschar--;
		}

		while(poschar>=posend)
		{
			WndChar[poschar]		=ChrSpace;
			WndChrRGB[poschar]		=ChrColor;
			WndBkgRGB[poschar]		=BkgColor;
			WndChrStyle[poschar--]	=ChrStyle|(m_ProtectedFieldModeFlag&GP_FNT_FIXED);
		}
		RedrawRect(Rect(0,pos,WindowSize.Width-1,WindowSize.Height-1));
	}
	else
	{
		CString tmps;
		tmps.Format("n=%d",pos);
		GPC.m_ErrReport.GPWriteErrorLog2("Green screen","InsertLine wrong parameters",tmps);
	}
}

void GPWindow::ResetSelection(BOOL bRedraw)
{
	UINT mask=(0xFFFFFFFF^GP_FNT_SELECTION);
	UINT pos;
	for(pos=0;pos<nall;pos++)
	{
		WndChrStyle[pos]&=mask;
		if (bRedraw && !(ScrParent->GetInvPoint(pos)&0x1))
			RedrawWndPos(pos);
	}
}

void GPWindow::SetBkgColor(ARGB argbNew, Rect &iRe)
{
	Rect re=iRe;
	re.Intersect(Rect(0,0,WindowSize.Width,WindowSize.Height));
	if (re.Width && re.Height)
	{
		int tmpreIntHeight=re.Height;
		int y,x;
		int wndpos=re.Y*WindowSize.Width+re.X;
		int delta=WindowSize.Width-re.Width;
		for(y=0;y<re.Height;y++,wndpos+=delta)
			for(x=0;x<re.Width;wndpos++,x++)
				if (WndBkgRGB[wndpos]!=argbNew)
				{
					WndBkgRGB[wndpos]=argbNew;
					RedrawWndPos(wndpos);
				}
	}
}

void GPWindow::SetChrColor(ARGB argbNew, Rect &iRe)
{
	Rect re=iRe;
	re.Intersect(Rect(0,0,WindowSize.Width,WindowSize.Height));
	if (re.Width && re.Height)
	{
		int tmpreIntHeight=re.Height;
		int y,x;
		int wndpos=re.Y*WindowSize.Width+re.X;
		int delta=WindowSize.Width-re.Width;
		for(y=0;y<re.Height;y++,wndpos+=delta)
			for(x=0;x<re.Width;wndpos++,x++)
				if (WndChrRGB[wndpos]!=argbNew)
				{
					WndChrRGB[wndpos]=argbNew;
					RedrawWndPos(wndpos);
				}
	}
}

void GPWindow::SetStyle(DWORD dwStlDelete, DWORD dwStlAdd, Rect &iRe)
{
	Rect re=iRe;
	re.Intersect(Rect(0,0,WindowSize.Width,WindowSize.Height));
	if (re.Width && re.Height)
	{
		int tmpreIntHeight=re.Height;
		int y,x;
		int wndpos=re.Y*WindowSize.Width+re.X;
		int delta=WindowSize.Width-re.Width;
		for(y=0;y<re.Height;y++,wndpos+=delta)
			for(x=0;x<re.Width;wndpos++,x++)
			{
				DWORD dwOldStyle=WndChrStyle[wndpos];
				DWORD dwNewStyle=((dwOldStyle&(0xFFFFFFFF^dwStlDelete))|dwStlAdd);
				if (dwNewStyle!=dwOldStyle)
				{
					WndChrStyle[wndpos]=dwNewStyle;
					RedrawWndPos(wndpos);
				}
			}
	}
}


void GPWindow::SetSelection(Rect &iRe, Size &ScrSize)
{
	Rect re=iRe;
	if (re.Width<0){re.X+=re.Width;re.Width=-re.Width;}
	if (re.Height<0){re.Y+=re.Height;re.Height=-re.Height;}
	re.Intersect(Rect(0,0,ScrSize.Width,ScrSize.Height));
	re.Intersect(WindowViewRect);
	re.X-=GPWndViewOfset.X;
	re.Y-=GPWndViewOfset.Y;
	
	if (re.Width && re.Height)
	{
		//ResetSelection(FALSE);
		int tmpreIntHeight=re.Height;
		int y;
		int x;
		int wndpos;
		for(y=0;y<WindowSize.Height;y++)
		{
			wndpos=y*WindowSize.Width;
			if (y<re.Y || y>=re.Y+re.Height)
			{
				for(x=0;x<WindowSize.Width;x++)
					if ((WndChrStyle[wndpos+x]&GP_FNT_SELECTION))
					{
						WndChrStyle[wndpos+x]&=(0xFFFFFFFF^GP_FNT_SELECTION);
						RedrawWndPos(wndpos+x);
					}
			}
			else
			{
				for(x=0;x<re.X;x++)
					if ((WndChrStyle[wndpos+x]&GP_FNT_SELECTION))
					{
						WndChrStyle[wndpos+x]&=(0xFFFFFFFF^GP_FNT_SELECTION);
						RedrawWndPos(wndpos+x);
					}
				for(x=re.X+re.Width;x<WindowSize.Width;x++)
					if ((WndChrStyle[wndpos+x]&GP_FNT_SELECTION))
					{
						WndChrStyle[wndpos+x]&=(0xFFFFFFFF^GP_FNT_SELECTION);
						RedrawWndPos(wndpos+x);
					}
			}
		}

		for(y=0;y<re.Height;y++)
		{
			int wndpos=(y+re.Y)*WindowSize.Width+re.X;
			for(x=0;x<re.Width;x++)
			{
				WndChrStyle[wndpos+x]|=GP_FNT_SELECTION;
				if (!(ScrParent->GetInvPoint(wndpos+x)&0x1))
					RedrawWndPos(wndpos+x);

			}
		}
	}
	else ResetSelection();
}

void GPWindow::CharOut(const unsigned short *iBuff, DWORD iLength)
{
	if (iBuff && iLength && iLength<0x1000000)
		while(iLength--)
			CharOut(*(iBuff++));
}

void GPWindow::CharOutAW(const char *iBuff, DWORD iLength)
{
	if (iBuff && iLength && iLength<0x1000000)
	{
		while(iLength--)
			CharOutAW(*(iBuff++));
	}
}

unsigned short GPWindow::GetCurChar()
{
	return GetCurChar(cursor);
}

unsigned short GPWindow::GetCurChar(Point &pos)
{
	return WndChar[pos.X+pos.Y*WindowSize.Width];
}

DWORD GPWindow::GetNearestChars(PNEAREST9X9 iNC)
{
	return GetNearestChars(iNC, cursor);
}

DWORD GPWindow::GetNearestChars(PNEAREST9X9 iNC, Point &iPosition)
{
	DWORD ret=0;
	DWORD curpos=iPosition.X+iPosition.Y*WindowSize.Width;
	iNC->X=iPosition.X;
	iNC->Y=iPosition.Y;
	iNC->center=0xFFFF;
	iNC->bottom=0xFFFF;
	iNC->bottomleft=0xFFFF;
	iNC->bottomright=0xFFFF;
	iNC->top=0xFFFF;
	iNC->topleft=0xFFFF;
	iNC->topright=0xFFFF;
	iNC->left=0xFFFF;
	iNC->right=0xFFFF;
	if (curpos-1				<nall)	{ret++; iNC->left		=WndChar[curpos-1				];}
	if (curpos+1				<nall)	{ret++; iNC->right		=WndChar[curpos+1				];}
	if (curpos					<nall)	{ret++; iNC->center		=WndChar[curpos					];}
	if (curpos-1+WindowSize.Width	<nall)	{ret++; iNC->bottomleft	=WndChar[curpos-1+WindowSize.Width	];}
	if (curpos+1+WindowSize.Width	<nall)	{ret++; iNC->bottomright=WndChar[curpos+1+WindowSize.Width	];}
	if (curpos+WindowSize.Width		<nall)	{ret++; iNC->bottom		=WndChar[curpos+WindowSize.Width	];}
	if (curpos-1-WindowSize.Width	<nall)	{ret++; iNC->topleft	=WndChar[curpos-1-WindowSize.Width	];}
	if (curpos+1-WindowSize.Width	<nall)	{ret++; iNC->topright	=WndChar[curpos+1-WindowSize.Width	];}
	if (curpos-WindowSize.Width		<nall)	{ret++; iNC->top		=WndChar[curpos-WindowSize.Width	];}

	return ret;
}

void GPWindow::SetExPerfixPosition()
{
	m_PrefixPositionEx=cursor.X+cursor.Y*WindowSize.Width;
}

DWORD GPWindow::SetStyleToChars(DWORD dwStlToDelete, DWORD dwStlToAdd, unsigned short usChar)
{
	DWORD ret=0;

	UINT i;
	DWORD mask=(0xFFFFFFFF^dwStlToDelete);
	if (dwStlToDelete)
		for(i=0;i<nall;i++)
			if (usChar==0xFFFF || WndChar[i]==usChar)
			{
				ret++;
				WndChrStyle[i]&=mask;
			}


	if (dwStlToAdd)
		for(i=0;i<nall;i++)
			if (usChar==0xFFFF || WndChar[i]==usChar)
			{
				ret++;
				WndChrStyle[i]|=dwStlToAdd;
			}
	return ret;
}

void GPWindow::RunEditor()
{
	if (m_CDlgDialogEditor==NULL)
	{
		m_CDlgDialogEditor =new CDlgDialogEditor(this,GPC.m_View);
		m_CDlgDialogEditor->Create(IDD_DIALOGOBJECTS);
	}

	try
	{
		m_CDlgDialogEditor->ShowWindow(SW_SHOW);
	}catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPWindow", "RunEditor 2074","");
		m_CDlgDialogEditor =new CDlgDialogEditor(this,GPC.m_View);
		m_CDlgDialogEditor->Create(IDD_DIALOGOBJECTS);
	}

	try
	{
		m_CDlgDialogEditor->ShowWindow(SW_SHOW);
	}catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPWindow", "RunEditor 2084","");
	}

	m_CDlgDialogEditor->SetWindowPos(&CWnd::wndTop,0,0,0,0,SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOSIZE);

}

void GPWindow::DeleteAllObjects()
{
	UINT i;
	if (WndUnit)
	{
		for(i=1;i<(*WndUnit)->m_NGPUNIT;i++) 
			if (WndUnit[i]) 
			{
				try
				{	delete WndUnit[i];WndUnit[i]=NULL;	}
				catch(...)
				{
					GPC.m_ErrReport.GPWriteErrorLog("GPWindow", "DeleteAllObjects","");
					WndUnit[i]=NULL;
				}
			}
		(*WndUnit)->m_NGPUNIT=1;
		RepaintWnd();
	}
}

GPUnit * GPWindow::GetUnitByHWND(HWND iHWND)
{
	GPUnit *ret=NULL;
	if (iHWND && WndUnit)
	{
		UINT i;
		for(i=0;i<(*WndUnit)->m_NGPUNIT && !ret;i++)
			if (WndUnit[i] && WndUnit[i]->UnitHWND==iHWND)
				ret=WndUnit[i];
	}

	return ret;
}

UINT GPWindow::ScaleColor(Rect &iRect, int ScaleFrg, int ScaleBkg)
{
	int wndpos=0;
	Rect re=iRect;
	re.Intersect(Rect(0,0,WindowSize.Width,WindowSize.Height));
	if (re.Width && re.Height)
	{
		int tmpreIntHeight=re.Height;
		int y,x;
		wndpos=re.Y*WindowSize.Width+re.X;
		int delta=WindowSize.Width-re.Width;
		for(y=0;y<re.Height;y++,wndpos+=delta)
			for(x=0;x<re.Width;wndpos++,x++)
			{
				ARGB frg=WndChrRGB[wndpos];
				ARGB bkg=WndBkgRGB[wndpos];
				ARGB frgNew=
					(frg&0xFF000000)|
					(((((frg/0x10000)&0xFF)*ScaleFrg/100)&0xFF)*0x10000)|
					(((((frg/0x100)&0xFF)*ScaleFrg/100)&0xFF)*0x100)|
					(((frg&0xFF)*ScaleFrg/100)&0xFF);
				ARGB bkgNew=
					(bkg&0xFF000000)|
					(((((bkg/0x10000)&0xFF)*ScaleBkg/100)&0xFF)*0x10000)|
					(((((bkg/0x100)&0xFF)*ScaleBkg/100)&0xFF)*0x100)|
					(((bkg&0xFF)*ScaleBkg/100)&0xFF);

				if (frg!=frgNew || bkg!=bkgNew)
				{
					WndChrRGB[wndpos]=frgNew;
					WndBkgRGB[wndpos]=bkgNew;
					RedrawWndPos(wndpos);
				}
			}
	}
	return wndpos;
}

DWORD GPWindow::GetWindowContent(Rect &iRect, ARGB *Frg, ARGB *Bkg, DWORD *dwStyles, unsigned short *usChars)
{
	DWORD ret=0;
	Rect re=iRect;
	re.Intersect(Rect(0,0,WindowSize.Width,WindowSize.Height));
	if (re.Width && re.Height)
	{
		int tmpreIntHeight=re.Height;
		int y,x;
		int wndpos=re.Y*WindowSize.Width+re.X;
		int delta=WindowSize.Width-re.Width;
		if (usChars) ret|=0x10000;
		if (Frg) ret|=0x20000;
		if (Bkg) ret|=0x40000;
		if (dwStyles) ret|=0x80000;
		for(y=0;y<re.Height;y++,wndpos+=delta)
			for(x=0;x<re.Width;wndpos++,x++)
			{
				ret++;
				if (usChars) *(usChars++)=WndChar[wndpos];
				if (Frg) *(Frg++)=WndChrRGB[wndpos];
				if (Bkg) *(Bkg++)=WndBkgRGB[wndpos];
				if (dwStyles) *(dwStyles++)=WndChrStyle[wndpos];
			}
	}

	return ret;
}

DWORD GPWindow::SetWindowContent(Rect &iRect, ARGB *Frg, ARGB *Bkg, DWORD *dwStyles, unsigned short *usChars)
{
	DWORD ret=0;
	Rect re=iRect;
	re.Intersect(Rect(0,0,WindowSize.Width,WindowSize.Height));
	if (re.Width && re.Height)
	{
		int tmpreIntHeight=re.Height;
		int y,x;
		int wndpos=re.Y*WindowSize.Width+re.X;
		int delta=WindowSize.Width-re.Width;
		if (usChars) ret|=0x10000;
		if (Frg) ret|=0x20000;
		if (Bkg) ret|=0x40000;
		if (dwStyles) ret|=0x80000;
		for(y=0;y<re.Height;y++,wndpos+=delta)
			for(x=0;x<re.Width;wndpos++,x++)
			{
				ret++;
				if (usChars) WndChar[wndpos]=*(usChars++);
				if (Frg) WndChrRGB[wndpos]=*(Frg++);
				if (Bkg) WndBkgRGB[wndpos]=*(Bkg++);
				if (dwStyles) WndChrStyle[wndpos]=*(dwStyles++);
				RedrawWndPos(wndpos);
			}
	}
	return ret;
}

void GPWindow::SaveCursorPosition()
{
	cursorSaved=cursor;
}

void GPWindow::RestoreCursorPosition()
{
	SetCursorPosition(cursorSaved);
}

void GPWindow::SetTABStopPos(DWORD dwFlags)
{
	SetTABStopPos(cursor.X,dwFlags);
}
void GPWindow::SetTABStopPos(UINT posX,DWORD dwFlags)
{
	if ((dwFlags&0x4))
	{//all
		int i;
		if (!(dwFlags&0x1)) //reset
			for(i=0;i<WindowSize.Width;i++)
				WndTabStops[i]=0;

		for(i=0;i<WindowSize.Width;i++)
			if (!(i%8)) WndTabStops[i]=1;
	}
	else
		if (posX<(UINT)WindowSize.Width)
			WndTabStops[posX]=(char)(dwFlags&0x1);
}

void GPWindow::DoTab(DWORD dwFlags)
{
	if (!(dwFlags&0x0001))
	{ //forward
		do 
		{
			if (!(dwFlags&0x0002)) CharOut(ChrSpace);
			else CursorMoveRight();
		}
		while(!WndTabStops[cursor.X]);
	}
	else
	{//Backward
		do 
		{
			CursorMoveLeft();
			if (!(dwFlags&0x0002))
			{
				CharOut(ChrSpace);
				CursorMoveLeft();
			}
		}
		while(!WndTabStops[cursor.X]);
	}
}

