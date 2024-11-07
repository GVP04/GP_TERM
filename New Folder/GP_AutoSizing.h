// GP_AutoSizing.h: interface for the GP_AutoSizing class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GP_AUTOSIZING_H__5A1C30A1_F769_11D3_A239_C029BA03009B__INCLUDED_)
#define AFX_GP_AUTOSIZING_H__5A1C30A1_F769_11D3_A239_C029BA03009B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct SIZINGITEM
{
	HWND ItemHWND;
	HWND MainHWND;
	DWORD StyleTop;
	DWORD StyleBottom;
	DWORD StyleLeft;
	DWORD StyleRight;
	CSize MinSize;
	CSize MaxSize;
	CRect InitialRect;
	CRect EtalonRect;
	CRect MaxRect;
	CRect MinRect;
	CRect EtalonRectW;
	CRect InitialRectW;
};


class GP_AutoSizing  
{
public:
	int GetOwnedArray(HWND iOwner, HWND **oArray);
	virtual BOOL CheckMainSize(HWND iHWND, UINT nType, int * cx, int * cy);
	void ReinitSize();
	DWORD GetState();
	void AutoSizingPause();
	void AutoSizingResume();
	const SIZINGITEM * GetMainItem();
	void DeleteAll();
	void ReinitItemSize(int inItem);
	void ReinitSize(HWND ihWnd, HWND iMainHWND);
	void UpdateSize(HWND iHWND);
	void DeleteWndEx(HWND ihWnd, HWND ownerHWND);
	char * GetSizingStyle(HWND iHWND);
	HWND GetResizingOwner(HWND iHWND);
	void SetNewMainSize(CRect &NewRect,UINT Flag);
	void SetNewSize(HWND ihWnd, CRect newRect);
	void ReinitSize(HWND ihWnd);
	void SetNewStyle(HWND ihWnd, const char *iString);
	BOOL InitSizing();
	BOOL SetMinSize(HWND ihWnd, long iMinWidth, long iMinHeight);
	BOOL SetMaxSize(HWND ihWnd, long iMaxWidth, long iMaxHeight);
	BOOL SetMaxPos(HWND ihWnd, long MaxTop, long MaxLeft, long MaxBottom, long MaxRight);
	BOOL SetMinPos(HWND ihWnd, long MinTop, long MinLeft, long MinBottom, long MinRight);
	UINT DeleteWnd(HWND ihWnd);
	BOOL AddSetMain(HWND ihWndMain);
	BOOL AddWnd(HWND ihWnd, HWND hWndMain, const char *iString);
	UINT GetItemCount();
	void Reset();
	void UpdateSize();
	GP_AutoSizing();
	virtual ~GP_AutoSizing();

private:
	DWORD m_Pause;
	BOOL CheckAndUpdate(SIZINGITEM Item, CRect &QurRect);
	void ResizeOne(CRect CompareRect, CRect CompareRectW, int Item, CPoint SmeLocal, CPoint SmeLocalW);
	long nItem;
	long nBuff;
	SIZINGITEM **aSizingItem;
	SIZINGITEM MainSizingItem;
};

#endif // !defined(AFX_GP_AUTOSIZING_H__5A1C30A1_F769_11D3_A239_C029BA03009B__INCLUDED_)
