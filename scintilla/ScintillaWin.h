#ifndef SPI_GETWHEELSCROLLLINES
#define SPI_GETWHEELSCROLLLINES   104
#endif

#ifndef WM_UNICHAR
#define WM_UNICHAR                      0x0109
#endif

#ifndef UNICODE_NOCHAR
#define UNICODE_NOCHAR                  0xFFFF
#endif

#ifdef __MINGW_H
#if __MINGW32_MAJOR_VERSION == 1
#undef WM_IME_STARTCOMPOSITION
#undef WM_IME_ENDCOMPOSITION
#undef WM_IME_COMPOSITION
#undef WM_IME_KEYLAST
#undef WM_IME_SETCONTEXT
#undef WM_IME_NOTIFY
#undef WM_IME_CONTROL
#undef WM_IME_COMPOSITIONFULL
#undef WM_IME_SELECT
#undef WM_IME_CHAR
#undef WM_IME_KEYDOWN
#undef WM_IME_KEYUP
#endif
#endif

#include "ScintillaBase.h"

#ifndef WM_IME_STARTCOMPOSITION
#include <imm.h>
#endif

#ifndef __BORLANDC__
#ifndef __DMC__
#include <zmouse.h>
#endif
#endif
#include <ole2.h>

#ifndef MK_ALT
#define MK_ALT 32
#endif

class ScintillaBase; 	// Forward declaration for COM interface subobjects
class ScintillaWin; 	// Forward declaration for COM interface subobjects

/**
 */
class FormatEnumerator {
public:
	void **vtbl;
	int ref;
	int pos;
	CLIPFORMAT formats[2];
	int formatsLen;
	FormatEnumerator(int pos_, CLIPFORMAT formats_[], int formatsLen_);
};

/**
 */
class DropSource {
public:
	void **vtbl;
	ScintillaWin *sci;
	DropSource();
};

/**
 */
class DataObject {
public:
	void **vtbl;
	ScintillaWin *sci;
	DataObject();
};

/**
 */
class DropTarget {
public:
	void **vtbl;
	ScintillaWin *sci;
	DropTarget();
};

/**
 */
class ScintillaWin :
	public ScintillaBase {

	bool lastKeyDownConsumed;

	bool capturedMouse;

	unsigned int linesPerScroll;	///< Intellimouse support
	int wheelDelta; ///< Wheel delta from roll

	bool hasOKText;

	CLIPFORMAT cfColumnSelect;

	DropSource ds;
	DataObject dob;
	DropTarget dt;

	static HINSTANCE hInstance;

	ScintillaWin(const ScintillaWin &) : ScintillaBase() {}
	virtual ~ScintillaWin();
	ScintillaWin &operator=(const ScintillaWin &) { return *this; }

	virtual void Initialise();
	virtual void Finalise();
	HWND MainHWND();

	static sptr_t DirectFunction(
		    ScintillaWin *sci, UINT iMessage, uptr_t wParam, sptr_t lParam);
	static sptr_t PASCAL SWndProc(
		    HWND hWnd, UINT iMessage, WPARAM wParam, sptr_t lParam);
	static sptr_t PASCAL CTWndProc(
		    HWND hWnd, UINT iMessage, WPARAM wParam, sptr_t lParam);
  
  	enum { invalidTimerID, standardTimerID, idleTimerID };

	virtual void StartDrag();
	sptr_t WndPaint(uptr_t wParam);
	sptr_t HandleComposition(uptr_t wParam, sptr_t lParam);
	virtual sptr_t DefWndProc(unsigned int iMessage, uptr_t wParam, sptr_t lParam);
  	virtual bool SetIdle(bool on);
	virtual void SetTicking(bool on);
	virtual void SetMouseCapture(bool on);
	virtual bool HaveMouseCapture();
	virtual void ScrollText(int linesToMove);
  	virtual void UpdateSystemCaret();
	virtual void SetVerticalScrollPos();
	virtual void SetHorizontalScrollPos();
	virtual bool ModifyScrollBars(int nMax, int nPage);
	virtual void NotifyChange();
	virtual void NotifyFocus(bool focus);
	virtual int GetCtrlID();
	virtual void NotifyParent(SCNotification scn);
	virtual void NotifyDoubleClick(cScPoint pt, bool shift);
	virtual void Copy();
	virtual bool CanPaste();
	virtual void Paste();
	virtual void CreateCallTipWindow(PRectangle rc);
	virtual void AddToPopUp(const char *label, int cmd = 0, bool enabled = true);
	virtual void ClaimSelection();

	// DBCS
	void ImeStartComposition();
	void ImeEndComposition();

	void AddCharBytes(char b0, char b1=0);

  	void GetIntelliMouseParameters();
  	virtual void CopyToClipboard(const SelectionText &selectedText);
  	void ScrollMessage(WPARAM wParam);
  	void HorizontalScrollMessage(WPARAM wParam);
  	void RealizeWindowPalette(bool inBackGround);
  	void FullPaint();
  	void FullPaintDC(HDC dc);
  	bool IsCompatibleDC(HDC dc);
  
  	virtual int SetScrollInfo(int nBar, LPCSCROLLINFO lpsi, BOOL bRedraw);
  	virtual bool GetScrollInfo(int nBar, LPSCROLLINFO lpsi);
  	void ChangeScrollPos(int barType, int pos);

public:
	ScintillaWin(HWND hwnd);
	// Public for benefit of Scintilla_DirectFunction
	virtual sptr_t WndProc(unsigned int iMessage, uptr_t wParam, sptr_t lParam);

	/// Implement IUnknown
	STDMETHODIMP QueryInterface(REFIID riid, PVOID *ppv);
	STDMETHODIMP_(ULONG)AddRef();
	STDMETHODIMP_(ULONG)Release();

	/// Implement IDropTarget
	STDMETHODIMP DragEnter(LPDATAOBJECT pIDataSource, DWORD grfKeyState,
	                       POINTL pt, PDWORD pdwEffect);
	STDMETHODIMP DragOver(DWORD grfKeyState, POINTL pt, PDWORD pdwEffect);
	STDMETHODIMP DragLeave();
	STDMETHODIMP Drop(LPDATAOBJECT pIDataSource, DWORD grfKeyState,
	                  POINTL pt, PDWORD pdwEffect);

	/// Implement important part of IDataObject
	STDMETHODIMP GetData(FORMATETC *pFEIn, STGMEDIUM *pSTM);

	// External Lexers
#ifdef SCI_LEXER
	void SetLexerLanguage(const char *languageName);
	void SetLexer(uptr_t wParam);
#endif

	static bool Register(HINSTANCE hInstance_);
	static bool Unregister();

	friend class DropSource;
	friend class DataObject;
	friend class DropTarget;
	bool DragIsRectangularOK(CLIPFORMAT fmt) {
		return drag.rectangular && (fmt == cfColumnSelect);
	}

  private:
  	// For use in creating a system caret
  	bool HasCaretSizeChanged();
  	BOOL CreateSystemCaret();
  	BOOL DestroySystemCaret();
  	HBITMAP sysCaretBitmap;
  	int sysCaretWidth;
  	int sysCaretHeight;
};
