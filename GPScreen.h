// GPScreen.h: interface for the GPScreen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPSCREEN_H__CAC53B22_CBDD_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GPSCREEN_H__CAC53B22_CBDD_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define GPMAX_SAVESCR 255
#define GPMAX_NWINDOW 255
#define GPMAX_NSAVEDREGION 257

#include "GPFont.h"	// Added by ClassView
#include "GPWindow.h"


enum GP_SCROPMASK
{
 GP_SCRMASK_UNDERLINE   =		0x00000001,				
 GP_SCRMASK_STRIKE      =		0x00000002,
 GP_SCRMASK_ITALIC      =		0x00000004,
 GP_SCRMASK_BOLD		=	 	0x00000008,
 GP_SCRMASK_SELECTION	=	 	0x00000010,
 GP_SCRMASK_FIXED		=	 	0x00000020,
 GP_SCRMASK_OPAQUE      =		0x00000040,	
 GP_SCRMASK_CODE        =   	0x00000080,
 GP_SCRMASK_BLINK		=		0x00000100,				
 GP_SCRMASK_LIGHT		=	 	0x00000200,
 GP_SCRMASK_SHADOW		=	 	0x00000400,
 GP_SCRMASK_CLRFRG      =	 	0x00000800,
 GP_SCRMASK_CLRBKG      =	 	0x00001000,
 GP_SCRMASK_REVERSE     =	 	0x00002000,

 GP_SCRMASK_CLR		    =	 	GP_SCRMASK_CLRBKG|GP_SCRMASK_CLRFRG,
 GP_SCRMASK_STYLESNEW   =	 	GP_SCRMASK_SHADOW|GP_SCRMASK_OPAQUE|GP_SCRMASK_SELECTION|GP_SCRMASK_ITALIC|GP_SCRMASK_STRIKE,
 GP_SCRMASK_STYLESOLD   =	 	GP_SCRMASK_REVERSE|GP_SCRMASK_BLINK|GP_SCRMASK_FIXED|GP_SCRMASK_BOLD|GP_SCRMASK_UNDERLINE,
 GP_SCRMASK_STYLES	    =	 	GP_SCRMASK_STYLESOLD|GP_SCRMASK_STYLESNEW,
 GP_SCRMASK_ALL         =	 	GP_SCRMASK_STYLES|GP_SCRMASK_CLR,

};



class GPScreen  
{
	friend class CGP_TermView;
	friend class GPWindow;
	friend class CODContextItem;
	friend UINT RefreshThreadFn(LPVOID pParam);
public:

	enum SizingModeEnum
	{
	SSM_SAFE		=0x0,
	SSM_LEFT		=0x1,	
	SSM_RIGHT		=0x2,	
	SSM_TOP			=0x4,	
	SSM_BOTTOM		=0x8,	
	SSM_SIZE_X		=SSM_LEFT|SSM_RIGHT,	
	SSM_SIZE_Y		=SSM_TOP|SSM_BOTTOM,	
	SSM_SIZE_XY		=SSM_LEFT|SSM_RIGHT|SSM_TOP|SSM_BOTTOM,
	};

	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];

	DWORD dwOldCommandMask;
	const static char *cArrCommandMask[];
	const static DWORD uArrCommandMask[];
	const static DWORD uArrCommandMaskM[];

	UINT DoMethod(const char *iStr, char *oStr);
	void DeleteAllObjects();
	void SetExPerfixPosition();
	DWORD GetNearestChars(PNEAREST9X9 iNC);
	DWORD RestoreScr(int nSaved);
	void CharOut(const unsigned short *iBuff, DWORD iLength);
	void CharOutAW(const char *iBuff, DWORD iLength);
	void SetSelection(Rect &re);
	void ResetSelection();
	void ScrToBuffer(unsigned short  *buff, Rect & boundRect);
	void DelLine(int pos);
	void InsertLine(int pos);
	void InsertChar(Point &pos);
	void DelChar(Point &pos);
	void DelLine(UINT nTimes);
	void InsertLine(UINT nTimes);
	void InsertChar(UINT nTimes);
	void DelChar(UINT nTimes);
	BOOL SetInsertMode(BOOL bOnOff);
	BOOL GetInsertMode();

	void RecolorScr(UINT iFrg, UINT iBkg);
	GPWindow * GPActiveWindow();
	GPWindow * GPGetWindowById(UINT iNum);
	GPWindow * GPGetWindowByNum(UINT iNum);
	UINT GPCreateWindow(Size &iGPWndSize, Rect &iGPWndViewRect, UINT IdWnd = 0);
	void WndSetState(UINT iWndId,UINT iWndState);
	void WndBackward(UINT iWndId);
	void WndForward(UINT iWndId);
	void WndBackwardOne(UINT iWndId);
	void WndForwardOne(UINT iWndId);
	char SelectWindow(UINT iWndId);
	void DeleteWindow(UINT iWndId);
	UINT GetWindowNum(UINT iWndId);
	void TextBox(Rect re,int type);
	void TextVerLine(int x, int y, int typ, int len);
	void TextHorLine(int x, int y, int typ, int len);
	BOOL GetCursorState();
	void ShadowOld(Rect &re,int type);
	BOOL GetScrScrollState();
	void SetScrScrollState(BOOL state);
	Point GetCursorPosition();
	void GetCursorPosition(Point &cur);
	void CharLine(Point &pos1, Point &pos2,unsigned short Ch);
	void RecolorString(int posX,int posY,int LineLength);
	BOOL LoadScrRgn(const char *name, Point &topleft);
	void SetCursorState(BOOL state);
	unsigned short SetChrSpace(UINT newSpace);
	unsigned short  GetChrSpace();
	UINT SetChrStyle(UINT newStyle, DWORD dwMask);
	UINT GetChrStyle();
	UINT SetChrColor(UINT newcolor, DWORD dwMask);
	UINT SetBkgColor(UINT newcolor, DWORD dwMask);
	UINT SetChrColorIndex(UINT newcolorIndex, DWORD dwMask);
	UINT SetBkgColorIndex(UINT newcolorIndex, DWORD dwMask);
	UINT GetChrColorIndex();
	UINT GetBkgColorIndex();
	UINT GetChrColor();
	UINT GetBkgColor();
	BOOL SetReverseVideo(BOOL bReverse, DWORD dwMask);
	BOOL GetReverseVideo();
	void ClearScreen();
	void ClearScreenBorder(Graphics & grbmp);
	void InvalidateScreenBorder();
	void ClearEndOfScreen();
	void ClearEndOfLine();
	void ClearToBeginOfLine();
	void CursorMoveCR();
	void CursorMoveLF();
	void CharOutAW(int x, int y, char ch);
	void CharOutAW(char ch);
	void CharOutGRUC(unsigned short ch);
	void CharOut(int x, int y, unsigned short ch);
	void CharOut(unsigned short ch);
	void LineOut(int x, int y, unsigned short *line, DWORD lineLen);
	void LineOut(unsigned short *line, DWORD lineLen);
	void SetCursorPosition(int x, int y);
	void SetCursorPosition(Point &newPoint);
	void CursorMoveUp();
	void CursorMoveDown();
	void CursorMoveRight();
	void CursorMoveLeft();
	void ScrollDown(UINT ntime);
	void ScrollUp(UINT ntime);
	void ScrollDown();
	void ScrollUp();
	void ScrollLeft(UINT ntime)	;
	void ScrollRight(UINT ntime);
	void ScrollLeft();
	void ScrollRight();
	void GetBlinkPoints(char *mscr);			
	void DeleteSaveScrRgn(int NumberRgn);
	void CopySaveScrRgn(int NumberRgn,Point &pnt_to);
	void UpdateSaveScrRgn(int NumberRgn);
	int SaveScrRgn(Rect &SaveRgn,int NumberRgn = -1);
	Size GetScreenSize();
	void EnableScrSaving(BOOL st);
	void ScrPrint(CDC *sdc, CPrintInfo* pInfo);
	DWORD ScrPrint(const char *iStrParams);
	void SaveScr(UINT n);
	void SetViewSize(int cx, int cy);
	void CalcSafeBorder(int *cx, int *cy, REAL *CurBLeft, REAL *CurBRight, REAL *CurBTop, REAL *CurBBottom);
	void CalcSafeBorder(int *cx, int *cy);
	GPScreen(UINT iScrId, Size &iScrSize, UINT iScrState, UINT iChrStyle);
	virtual ~GPScreen();
	BOOL IsScrSaveEnable();
	BOOL IsScrViewEnable();
	void SaveCursorPosition();
	void RestoreCursorPosition();
	const Point GetCharPosByWndPos(Point & iPos);
	UINT ScrId;
	BOOL GetNeedRedraw();
	BOOL GetNeedRepaint();
	void SetNeedRedraw(BOOL bNeed = TRUE);
	void SetNeedRepaint(BOOL bNeed = TRUE);
	void RepaintScr();
	void RepaintRect(Rect &re);
	void RedrawScr();
	void RedrawRect(Rect &re);
	void RedrawPoint(DWORD pos);
	void RepaintPoint(DWORD pos);
	void RedrawScreen();
	void CreateScreenBitmap(BOOL bClear = FALSE);
	void CreateScreenPrintBitmap(INT Width, INT Height);
	DWORD GetInvPoint(DWORD pos);
	CBitmapPlus *ScreenToBitmap(INT Width, INT Height, PixelFormat oPixelFormat, DWORD dwFlags);
	CBitmapPlus *ScreenToPrintBitmap(INT Width, INT Height, PixelFormat oPixelFormat, DWORD dwFlags);
	void SetScrollRange(UINT uStart, UINT uEnd);
	void ScrollRange(UINT nTimes, UINT uDirection);
	void DoTab(DWORD dwFlags);
	void SetTABStopPos(DWORD dwFlags);
	void SetTABStopPos(UINT posX, DWORD dwFlags);

	static DWORD TranslateScrCmdMask(const char *iStr);
	static char *TranslateScrCmdMask(char *iStr, DWORD dwMask);

	REAL LeftBorderSafe;
	REAL TopBorderSafe;
	REAL RightBorderSafe;
	REAL BottomBorderSafe;

	REAL LeftBorderC;
	REAL RightBorderC;
	REAL TopBorderC;
	REAL BottomBorderC;
	static REAL ScrLeftBorder;
	static REAL ScrRightBorder;
	static REAL ScrTopBorder;
	static REAL ScrBottomBorder;

	REAL LeftPageMargin;
	REAL RightPageMargin;
	REAL TopPageMargin;
	REAL BottomPageMargin;
	static REAL ScrLeftPageMargin;
	static REAL ScrRightPageMargin;
	static REAL ScrTopPageMargin;
	static REAL ScrBottomPageMargin;

	REAL FontDeltaX;
	static REAL ScrFontDeltaX;
	REAL FontDeltaY;
	static REAL ScrFontDeltaY;

	REAL FontOfsetX;
	static REAL ScrFontOfsetX;
	REAL FontOfsetY;
	static REAL ScrFontOfsetY;

	REAL ScaleHeightToWidth;
	static REAL ScrScaleHeightToWidth;

	DWORD PrintBorders;
	static DWORD ScrPrintBorders;

	DWORD PrintInvert;
	static DWORD ScrPrintInvert;

	DWORD SizeScaleFlags;
	static DWORD ScrSizeScaleFlags;

	DWORD ScaleFlags;
	static DWORD ScrScaleFlags;

	DWORD ScrConvFlags;
	static DWORD dwGRConvFlags[];

protected:
	GPWindow **aGPWindow;	
	GPWindow **aGPWindowRgnSaved;
	GPScreen **aSavedScr;	
	UINT ScrState;
	Size ScreenSize;
	SizeF CharPlaceSize;
	SizeF CharPlacePrintSize;
	Rect ScreenViewRect;
	DWORD *InvPoints;
	Bitmap *ScreenBitmap;
	Bitmap *ScreenPrintBitmap;

private:
	UINT uScrollLineStart;
	UINT uScrollLineEnd;
	UINT ActiveWindow;
	UINT nall;
	UINT * WndNumbers;
	UINT ChrStyle;
	DWORD dwNeedRedraw;
};

#endif // !defined(AFX_GPSCREEN_H__CAC53B22_CBDD_11D2_B27D_00600840D054__INCLUDED_)
