// GPFontList.h: interface for the CGPFontList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPFONTLIST_H__6FC129D1_F4AA_4EF4_9455_7FCC54CCA0DC__INCLUDED_)
#define AFX_GPFONTLIST_H__6FC129D1_F4AA_4EF4_9455_7FCC54CCA0DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define GPFL_CLEAR		0x01
#define GPFL_NOSCRIPT	0x02


typedef struct _GPFONTINFO
{
	ENUMLOGFONTEX elf;
	NEWTEXTMETRICEX tmex;
	DWORD FontType;
} GPFONTINFO, *PGPFONTINFO;


class CGPFontList : public CObject  
{
	friend int CALLBACK GPEnumFontFamExProcGetList(
					  ENUMLOGFONTEX *lpelfe,    // logical-font data
					  NEWTEXTMETRICEX *lpntme,  // physical-font data
					  DWORD FontType,           // type of font
					  LPARAM lParam             // application-defined data
					);

	DECLARE_SERIAL(CGPFontList)
public:
	UINT ResetList(LOGFONT & ilf);
	void FillListBox(HWND iHWND,  UINT uFlag);
	void FillComboBox(HWND iHWND, UINT uFlag, UINT cmpPitchFam=0);
	void FillListCtrl(HWND iHWND, UINT uFlag, int nNameColumn=-1, int ScriptColumn=-1, int SizeColumn=-1);
	const GPFONTINFO *GetElement(UINT nElement);

	CGPFontList();
	CGPFontList(LOGFONT & ilf);
	virtual ~CGPFontList();
	void Serialize( CArchive& archive );
	UINT GetCount(){return m_nFonts;}
private:
	void DestroyList();
	void Init();
	GPFONTINFO **m_ArrGPFONTINFO;
	UINT m_nFonts;
	UINT m_nMaxFonts;
	LOGFONT Logfont; 
};

#endif // !defined(AFX_GPFONTLIST_H__6FC129D1_F4AA_4EF4_9455_7FCC54CCA0DC__INCLUDED_)
