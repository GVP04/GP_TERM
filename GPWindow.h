// GPWindow.h: interface for the GPWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPWINDOW_H__CAC53B21_CBDD_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GPWINDOW_H__CAC53B21_CBDD_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GPUnit.h"

#define MAXLEN_WNDNAME  20
#define MAX_LAYERS		0x20

enum GP_WNDSTYLE
{
	GP_WND_SAVE     =    0x0001,
	GP_WND_VIEW		=    0x0002,
};

enum GP_WNDFLAGMASK
{
	GP_WND_FM_INSERT		=	0x0001,
};

class GPScreen;

typedef struct _NEAREST9X9
{
	INT X;
	INT Y;
	unsigned short left;
	unsigned short right;
	unsigned short top;
	unsigned short bottom;
	unsigned short bottomleft;
	unsigned short topleft;
	unsigned short bottomright;
	unsigned short topright;
	unsigned short center;
} NEAREST9X9, *PNEAREST9X9;



typedef struct _ODCLAYERINFO
{
	CString csName;
	DWORD dwStyle;
	CString csContextName;
	CODContext *pContext;
} ODCLAYERINFO, *PODCLAYERINFO;



class CDlgDialogEditor;
  
class GPWindow  
{
	friend class CGP_TermDoc;
	friend class CGP_TermView;
	friend class CDlgTermSet;
	friend class CDlgFontSet;
	friend class CDlgDialogEditor;
	friend class CODContextArray;
public:
	DWORD GetWindowContent(Rect &iRect, ARGB *Frg, ARGB *Bkg, DWORD *dwStyles, unsigned short *usChars);
	DWORD SetWindowContent(Rect &iRect, ARGB *Frg, ARGB *Bkg, DWORD *dwStyles, unsigned short *usChars);


	const static enum ODCLayerStyles
	{
		ODCL_VISIBLE	= 0x1,
		ODCL_FRG		= 0x2,
		ODCL_BKG		= 0x4,
		ODCL_SHAREODC	= 0x8
	};

	void AddLayer(const char *iName, const char *iODCName, DWORD dwStyle, const char *iNameBefore);
	void DeleteLayer(const char *iName, DWORD dwType);
	void DeleteLayers(DWORD dwStyle = 0);
	DWORD GetLayerNum(const char *iName);
	static DWORD CompileLayerStyle(const char *ccStile);
	PODCLAYERINFO GetLayer(const char *iName);
	void DeleteAllObjects();
	CDlgDialogEditor *m_CDlgDialogEditor;
	unsigned short m_NextMBOutChar;
	DWORD SetStyleToChars(DWORD dwStlToDelete, DWORD dwStlToAdd, unsigned short usChar);
	void SetExPerfixPosition();
	DWORD m_PrefixPosition;
	DWORD m_PrefixPositionEx;
	DWORD GetNearestChars(PNEAREST9X9 iNC);
	DWORD GetNearestChars(PNEAREST9X9 iNC, Point &iPosition);
	unsigned short GetCurChar();
	unsigned short GetCurChar(Point &pos);
	void CharOut(const unsigned short *iBuff, DWORD iLength);
	void RunEditor();
	void CharOutAW(const char *iBuff, DWORD iLength);
	void SetSelection(Rect & re,Size & ScrSize);
	void ResetSelection(BOOL bRedraw = TRUE);
	void WndToBuffer(char *buff,Rect &iRe, Size &ScrSize);
	void WndToBuffer(unsigned short *buff,Rect &iRe, Size &ScrSize);
	void SetStyle(DWORD dwStlDelete, DWORD dwStlAdd, Rect &iRe);
	void SetBkgColor(ARGB argbNew, Rect &iRe);
	void SetChrColor(ARGB argbNew, Rect &iRe);
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
	void DoMethod(UINT UnitNum, const char *iStr, char *oStr);
	void RecolorWnd(UINT iFrg, UINT iBkg);
	void GPInvertWnd();
	void ClearRect(Rect &iRect);
	GPUnit * GetUnitByNum(UINT iUnitNum);
	GPUnit * GetUnitById(UINT iUnitId);
	void SetViewState(UINT iState);
	UINT GetObjectNum(UINT iObjId);
	void DeleteUnit(UINT iObjId, BOOL bReport);
	UINT CreateUnit(UINT iType,UINT iId, const char *iProp, HWND pParentWnd);
	void TextBox(Rect &re,int type);
	void TextVerLine(int x, int y, int typ, int len);
	void TextHorLine(int x, int y, int typ, int len);
	void ShadowOld(Rect &re,int type);
	void CharLine(Point &pos1, Point &pos2,unsigned short Ch);
	void RecolorString(int posX, int posY, int LineLength);
	BOOL LoadScrRgn(const char *name, Point &topleft);
	void CharOut(Point &pos, unsigned short ch);
	void CharOut(UINT pos, unsigned short ch);
	void CharOutAW(Point &pos, char ch);
	void CharOutGR(UINT pos, char ch);
	void CharOutAW(UINT pos, char ch);
	void CharOut(UINT pos1, UINT pos2);
	void SetCursorPosition(int x, int y);
	void SetCursorPosition(Point &newPoint);
	void CursorMoveCR();
	void CursorMoveLF();
	void CursorMoveUp();
	void CursorMoveDown();
	void CursorMoveRight();
	void CursorMoveLeft();
	void ScrollDown(UINT ntime);
	void ScrollUp(UINT ntime);
	void ScrollDown();
	void ScrollUp();
	void ScrollLeft(UINT ntime);
	void ScrollRight(UINT ntime);
	void ScrollLeft();
	void ScrollRight();
	void RedrawWndPos(Point &pos);
	void RedrawWndPos(UINT pos);
	void RedrawRect(Rect &refrect);
	void RedrawWnd();
	void RepaintWndPos(Point &pos);
	void RepaintWndPos(UINT pos);
	void RepaintRect(Rect &refrect);
	void RepaintWnd();
	DWORD GetInvPoint(UINT pos);


	void CharOut(int x, int y, unsigned short ch);
	void CharOut(unsigned short ch);
	void LineOut(int x, int y, unsigned short *line, DWORD LineLen);
	void LineOut(unsigned short *line, DWORD LineLen);
	void CharOutAW(int x, int y, char ch);
	void CharOutAW(char ch);
	void CharOutGR(char ch);
	void CharOutGRUC(unsigned short ch);
	void LineOutAW(int x, int y, char *line, DWORD LineLen);
	void LineOutAW(const char *line, DWORD LineLen);
	unsigned short SetChrSpace(unsigned short newSpace);
	unsigned short GetChrSpace();
	UINT SetChrStyle(UINT newStyle, DWORD dwMask);
	UINT ScaleColor(Rect &iRect, int ScaleFrg, int ScaleBkg);
	UINT GetChrStyle();
	UINT SetChrColor(UINT newcolor, DWORD dwMask);
	UINT SetBkgColor(UINT newcolor, DWORD dwMask);
	UINT SetChrColorIndex(UINT newcolorIndex, DWORD dwMask);
	UINT SetBkgColorIndex(UINT newcolorIndex, DWORD dwMask);
	UINT GetChrColor();
	UINT GetBkgColor();
	UINT GetChrColorIndex();
	UINT GetBkgColorIndex();
	void GetBlinkPoints(char *mscr, int scrWidth);
	Point GetCursorPosition();
	void GetCursorPosition(Point &iPoint);
	Rect GetWndViewRect();
	void GetWndViewRect(Rect &iRect);
	Size GetWndSize();
	Rect GetWndRect();
	void IntersectRect(Rect & rect);
	void GPCopyRgn(GPWindow * SourseWnd, Rect &sourseRect, Point &destRect);
	void WndPaint(Graphics &gr);
	void WndPrint(Graphics &gr);
	void ClearWnd();
	void ClearEndOfWnd();
	void ClearEndOfLine();
	void ClearToBeginOfLine();
	void SaveCursorPosition();
	void RestoreCursorPosition();
	GPWindow(GPScreen *iScrParent, UINT iWndId, Size &iGPWndSize,Rect &iGPWndViewRect, UINT iGPWndState, UINT iChrStyle, DWORD dwOldCommandMask_IN);
	virtual ~GPWindow();
	BOOL IsWndSaveEnable();
	BOOL IsWndViewEnable();
	UINT WndId;
	BOOL ScrollWnd;
	Point GPWndViewOfset;
	BOOL CursorVisible;
	DWORD m_ProtectedModeFlag;
	DWORD m_ProtectedFieldModeFlag;
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];
	UINT DoMethod(const char *iStr, char *oStr);
	BOOL SetReverseVideo(BOOL bReverse, DWORD dwMask);
	BOOL GetReverseVideo();
	void DoTab(DWORD dwFlags);
	void SetTABStopPos(DWORD dwFlags);
	void SetTABStopPos(UINT posX,DWORD dwFlags);

protected:
	PODCLAYERINFO ArrLayers[MAX_LAYERS];
	GPScreen *ScrParent;
	Point cursor;	
	Point cursorSaved;	
	UINT ChrStyle;	
	UINT ChrColor;	
	UINT BkgColor;	
	UINT ChrColorInd;	
	UINT BkgColorInd;	
	UINT BkgMode;	
	BOOL ReverseColorFlag;
	unsigned short ChrSpace;	
	unsigned short * WndChar;	
	UINT * WndChrRGB;
	UINT * WndBkgRGB;
	UINT * WndChrStyle;
	char * WndTabStops;	
	GPUnit ** WndUnit; 

	CompositingQuality	m_CompositingQuality;
	InterpolationMode	m_InterpolationMode;
	PixelOffsetMode		m_PixelOffsetMode;
	SmoothingMode		m_SmoothingMode;
	DWORD				m_TextContrast;
	TextRenderingHint	m_TextRenderingHint;
	DWORD				m_Language;
	DWORD				m_SubLanguage;
	DWORD				m_CurCodePage;
	DWORD				m_dwFlags;

private:
	char m_LastPrefix;
	BOOL WaitScroll;
	UINT nall;
	UINT m_NGPUNITmax;
	UINT GPWndState;
	Size WindowSize; 
	Rect WindowViewRect;
public:
	GPUnit * GetUnitByName(const char *iccName);
	GPUnit * GetUnitByHWND(HWND iHWND);
	DWORD dwOldCommandMask;
};

#endif // !defined(AFX_GPWINDOW_H__CAC53B21_CBDD_11D2_B27D_00600840D054__INCLUDED_)
