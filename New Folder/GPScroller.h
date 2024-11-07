// GPScroller.h: interface for the CGPScroller class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPSCROLLER_H__57D1B08C_0576_4857_A7B0_666F91AA3D0C__INCLUDED_)
#define AFX_GPSCROLLER_H__57D1B08C_0576_4857_A7B0_666F91AA3D0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGPScroller : public CObject  
{
friend class GPDlgBar;
friend class GPFrameBar;
friend class GPObjDialog;
friend class GPFrameWnd;
public:
	UINT EnsureVisible(HWND iHWND);
	void OnScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void UpdatePosition();
	const CString GetName();
	void SetScroller(int iDeltaX,int iDeltaY, int inPageX, int inPageY, DWORD dwFlags);
	void SetScrollerPos(int iX,int iY);
	CGPScroller(const char *iName, HWND im_hWnd, HWND im_ScrollhWnd, DWORD dwFlags);
	CGPScroller(const char *iName, HWND im_hWnd, HWND im_ScrollhWnd, int iDeltaX,int iDeltaY, int inPageX, int inPageY, DWORD dwFlags);
	virtual ~CGPScroller();
	CPoint CurPoint;
private:
	DWORD dwFlags;
	HWND m_hWnd;
	HWND m_ScrollhWnd;
	int DeltaX;
	int DeltaY;
	int nPageX;
	int nPageY;
	CString Name;
};

#endif // !defined(AFX_GPSCROLLER_H__57D1B08C_0576_4857_A7B0_666F91AA3D0C__INCLUDED_)
