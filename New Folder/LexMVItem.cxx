// Scintilla source code edit control
/** @file LexSepView.cxx
 ** Lexer for MultiValue Item
 **/

#include "stdafx.h"

#include "scintilla\Platform.h"

#include "scintilla\PropSet.h"
#include "scintilla\Accessor.h"
#include "scintilla\StyleContext.h"
#include "scintilla\KeyWords.h"
#include "scintilla\Scintilla.h"
#include "scintilla\SciLexer.h"

//#define SCE_MVITEM_ATT1 0
//#define SCE_MVITEM_ATT2 1
//#define SCE_MVITEM_ATT1VAL1 2
//#define SCE_MVITEM_ATT2VAL1 3
//#define SCE_MVITEM_ATT1VAL2 4
//#define SCE_MVITEM_ATT2VAL2 5
//#define SCE_MVITEM_ATT1VAL1SV1 6
//#define SCE_MVITEM_ATT2VAL1SV1 7
//#define SCE_MVITEM_ATT1VAL2SV1 8
//#define SCE_MVITEM_ATT2VAL2SV1 9
//#define SCE_MVITEM_ATT1VAL1SV2 10
//#define SCE_MVITEM_ATT2VAL1SV2 11
//#define SCE_MVITEM_ATT1VAL2SV2 12
//#define SCE_MVITEM_ATT2VAL2SV2 13


//1/2 |v1/2 |v-flg |sv1/2 |sv-flg

/*
00000 SCE_MVITEM_ATT1
00001 SCE_MVITEM_ATT2
00010 SCE_MVITEM_DEFAULT
00011 SCE_MVITEM_DEFAULT
00100 SCE_MVITEM_ATT1VAL1
00101 SCE_MVITEM_ATT2VAL1
00110 SCE_MVITEM_ATT1VAL2
00111 SCE_MVITEM_ATT2VAL2
01000 SCE_MVITEM_DEFAULT
01001 SCE_MVITEM_DEFAULT
01010 SCE_MVITEM_DEFAULT
01011 SCE_MVITEM_DEFAULT
01100 SCE_MVITEM_DEFAULT
01101 SCE_MVITEM_DEFAULT
01110 SCE_MVITEM_DEFAULT
01111 SCE_MVITEM_DEFAULT
10000 SCE_MVITEM_DEFAULT
10001 SCE_MVITEM_DEFAULT
10010 SCE_MVITEM_DEFAULT
10011 SCE_MVITEM_DEFAULT
10100 SCE_MVITEM_ATT1VAL1SV1
10101 SCE_MVITEM_ATT2VAL1SV1
10110 SCE_MVITEM_ATT1VAL2SV1
10111 SCE_MVITEM_ATT2VAL2SV1
11000 SCE_MVITEM_DEFAULT
11001 SCE_MVITEM_DEFAULT
11010 SCE_MVITEM_DEFAULT
11011 SCE_MVITEM_DEFAULT
11100 SCE_MVITEM_ATT1VAL1SV2
11101 SCE_MVITEM_ATT2VAL1SV2
11110 SCE_MVITEM_ATT1VAL2SV2
11111 SCE_MVITEM_ATT2VAL2SV2
*/

static void ColouriseMVItemDoc(unsigned int startPos, int length, int initStyle,
                           WordList *keywordlists[], Accessor &styler, bool MVItemScriptSyntax)
 {
	int arrstl[]={
		SCE_MVITEM_ATT1,		SCE_MVITEM_ATT2,		SCE_MVITEM_DEFAULT,		SCE_MVITEM_DEFAULT,
		SCE_MVITEM_ATT1VAL1,	SCE_MVITEM_ATT2VAL1,	SCE_MVITEM_ATT1VAL2,	SCE_MVITEM_ATT2VAL2,
		SCE_MVITEM_DEFAULT,		SCE_MVITEM_DEFAULT,		SCE_MVITEM_DEFAULT,		SCE_MVITEM_DEFAULT,
		SCE_MVITEM_DEFAULT,		SCE_MVITEM_DEFAULT,		SCE_MVITEM_DEFAULT,		SCE_MVITEM_DEFAULT,
		SCE_MVITEM_DEFAULT,		SCE_MVITEM_DEFAULT,		SCE_MVITEM_DEFAULT,		SCE_MVITEM_DEFAULT,
		SCE_MVITEM_ATT1VAL1SV1,	SCE_MVITEM_ATT2VAL1SV1,	SCE_MVITEM_ATT1VAL2SV1,	SCE_MVITEM_ATT2VAL2SV1,
		SCE_MVITEM_DEFAULT,		SCE_MVITEM_DEFAULT,		SCE_MVITEM_DEFAULT,		SCE_MVITEM_DEFAULT,
		SCE_MVITEM_ATT1VAL1SV2,	SCE_MVITEM_ATT2VAL1SV2,	SCE_MVITEM_ATT1VAL2SV2,	SCE_MVITEM_ATT2VAL2SV2,
		};
	int curLine;
	curLine=styler.GetLine(startPos);
	styler.StartAt(startPos);

	StyleContext sc(startPos, length, initStyle, styler);

	char strBeginChar=0;
	UINT prevState=0;
	int forvState=-1;
	int iValueFlg=0,iSubValueFlg=0;
	int iValuePos=0,iSubValuePos=0;
	

	for(; sc.More(); sc.Forward())
	{
		if (sc.atLineStart)
		{
			curLine=styler.GetLine(sc.currentPos);
			iValueFlg=0;
			iSubValueFlg=0;
		}

		sc.SetState(arrstl[iValueFlg+iSubValueFlg+(curLine%2)]);

		switch(sc.ch)
		{
		case 2:
			iValueFlg|=0x4;
			iValueFlg^=0x2;
			iSubValueFlg=0;
			sc.ChangeState(arrstl[iValueFlg+iSubValueFlg+(curLine%2)]);
			iSubValuePos=iValuePos=sc.currentPos+1;
			break;
		case 3:
			iValueFlg|=0x4;
			iSubValueFlg|=0x10;
			iSubValueFlg^=0x8;
			sc.ChangeState(arrstl[iValueFlg+iSubValueFlg+(curLine%2)]);
			iSubValuePos=sc.currentPos+1;
			break;
		case 10:
		case 13:
			iValueFlg=0;
			iSubValueFlg=0;
			sc.SetState(SCE_MVITEM_DEFAULT);
			break;
		default:
			break;
		}
	}
	sc.Complete();
}

static void FoldMVItemDoc(unsigned int startPos, int length, int,
						   WordList *[], Accessor &styler) {
	int endPos = startPos + length;
}

static void ColouriseMVItemNetDoc(unsigned int startPos, int length, int initStyle,
                           WordList *keywordlists[], Accessor &styler) {
	ColouriseMVItemDoc(startPos, length, initStyle, keywordlists, styler, false);
}

static const char * const MVItemWordListDesc[] = {
	"Keywords",
	0
};

LexerModule lmMVItem(SCLEX_MVITEM, ColouriseMVItemNetDoc, "MVItem", FoldMVItemDoc, MVItemWordListDesc);

//==========================================================

static void ColouriseMVTextDoc(unsigned int startPos, int length, int initStyle,
                           WordList *keywordlists[], Accessor &styler, bool MVTextScriptSyntax)
 {
	int curLine;
	curLine=styler.GetLine(startPos);
	styler.StartAt(startPos);

	StyleContext sc(startPos, length, initStyle, styler);

	char strBeginChar=0;
	UINT prevState=0;
	int forvState=-1;
	int iValueFlg=0,iSubValueFlg=0;
	int iValuePos=0,iSubValuePos=0;
	

	for(; sc.More(); sc.Forward())
	{
		if (sc.atLineStart)
		{
			curLine=styler.GetLine(sc.currentPos);
			iValueFlg=0;
			iSubValueFlg=0;
		}

		//sc.SetState(arrstl[iValueFlg+iSubValueFlg+(curLine%2)]);

		switch(sc.ch)
		{
		case 2:
			iValueFlg|=0x4;
			iValueFlg^=0x2;
			iSubValueFlg=0;
			//sc.ChangeState(arrstl[iValueFlg+iSubValueFlg+(curLine%2)]);
			iSubValuePos=iValuePos=sc.currentPos+1;
			break;
		case 3:
			iValueFlg|=0x4;
			iSubValueFlg|=0x10;
			iSubValueFlg^=0x8;
			//sc.ChangeState(arrstl[iValueFlg+iSubValueFlg+(curLine%2)]);
			iSubValuePos=sc.currentPos+1;
			break;
		case 10:
		case 13:
			iValueFlg=0;
			iSubValueFlg=0;
			//sc.SetState(SCE_MVITEM_DEFAULT);
			break;
		default:
			break;
		}
	}
	sc.Complete();
}

static void FoldMVTextDoc(unsigned int startPos, int length, int,
						   WordList *[], Accessor &styler) {
	int endPos = startPos + length;
}

static void ColouriseMVTextNetDoc(unsigned int startPos, int length, int initStyle,
                           WordList *keywordlists[], Accessor &styler) {
	ColouriseMVTextDoc(startPos, length, initStyle, keywordlists, styler, false);
}

static const char * const MVTextWordListDesc[] = {
	"Keywords",
	0
};

LexerModule lmMVText(SCLEX_MVTEXT, ColouriseMVTextNetDoc, "MVText", FoldMVTextDoc, MVTextWordListDesc);

