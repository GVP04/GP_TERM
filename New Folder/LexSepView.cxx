// Scintilla source code edit control
/** @file LexSepView.cxx
 ** Lexer for PICK Basic
 **/

#include "stdafx.h"

#include "scintilla\Platform.h"

#include "scintilla\PropSet.h"
#include "scintilla\Accessor.h"
#include "scintilla\StyleContext.h"
#include "scintilla\KeyWords.h"
#include "scintilla\Scintilla.h"
#include "scintilla\SciLexer.h"

 
static void ColouriseSepViewDoc(unsigned int startPos, int length, int initStyle,
                           WordList *keywordlists[], Accessor &styler, bool SepViewScriptSyntax)
 {

	WordList &keywords = *keywordlists[0];
	WordList &keywords2 = *keywordlists[1];
	WordList &keywords3 = *keywordlists[2];
	WordList &keywords4 = *keywordlists[3];
	WordList &keywords5 = *keywordlists[4];
	WordList &keywords6 = *keywordlists[5];

	styler.StartAt(startPos);
	UINT presentInLists=0;

	StyleContext sc(startPos, length, initStyle, styler);
	char strBeginChar=0;
	UINT prevState=0;
	int forvState=-1;

	for(; sc.More(); sc.Forward())
	{
		if (forvState!=-1) sc.SetState(forvState);
		forvState=-1;
		if (sc.atLineStart)
		{
			prevState=SCE_SV_DEFAULT;
			sc.SetState(SCE_SV_DEFAULT);
			presentInLists=0;
		}

		switch(sc.state)
		{
		case SCE_SV_NUMBER:
			if ((sc.ch<'0' || sc.ch>'9') && sc.ch!='.') 
				sc.SetState(SCE_SV_DEFAULT);
			else
			{
				if (sc.ch=='.')
				{
					char s[100];
					presentInLists=0;
					sc.GetCurrentLowered(s, sizeof(s));
					if (strchr(s,'.'))
					{
						sc.ChangeState(SCE_SV_ERROR);
						if (!sc.atLineEnd)
							forvState=SCE_SV_DEFAULT;
					}
				}
			}
			break;
		case SCE_SV_IDENTIFIER:
			if (sc.atLineEnd || sc.LengthCurrent()==length-1
				|| (sc.ch<'0' && sc.ch!='.')
				|| (sc.ch>'9' && sc.ch<'A') 
				|| (sc.ch>'Z' && sc.ch<'_')
				|| (sc.ch>'_' && sc.ch<'a')
				|| (sc.ch>'z' && sc.ch<'À')
				|| (sc.ch>'ß' && sc.ch<'à')
				)
			{
				char s[100];
				presentInLists=0;
				sc.GetCurrentLowered(s, sizeof(s));
				if (sc.LengthCurrent()==length-1)
				{
					char *ps=s;
					while(*ps) ps++;
					*(ps++)=sc.ch;
					*ps=0;
				}

				if (keywords.InList(s))
					presentInLists=0x1;
				else 
				if (keywords2.InList(s))
					presentInLists=0x2;
				else 
				if (keywords3.InList(s))
					presentInLists=0x4;
				else 
				if (keywords4.InList(s))
					presentInLists=0x8;
				else 
				if (keywords5.InList(s))
					presentInLists=0x10;
				else 
				if (keywords6.InList(s))
					presentInLists=0x20;


				if (presentInLists)
				{
					switch(presentInLists)
					{
					case 1:
						sc.ChangeState(SCE_SV_KEYWORD);
						break;
					case 2:
						sc.ChangeState(SCE_SV_KEYWORD2);
						break;
					case 4:
						sc.ChangeState(SCE_SV_KEYWORD3);
						break;
					case 8:
						sc.ChangeState(SCE_SV_KEYWORD4);
						break;
					case 16:
						sc.ChangeState(SCE_SV_KEYWORD5);
						break;
					case 32:
						sc.ChangeState(SCE_SV_KEYWORD6);
						break;
					}
					if (sc.LengthCurrent()==length-1 || sc.atLineEnd || sc.ch==' ' || sc.ch=='\t' || sc.ch=='\r' || sc.ch=='\n')
					{
						if (!sc.atLineEnd) sc.SetState(SCE_SV_DEFAULT);
					}
					else
					{
						sc.SetState(SCE_SV_DEFAULT);
					}
				}
				else
				{
					if (strchr(")}]>",sc.ch))
						sc.SetState(SCE_SV_DEFAULT);
					else
					if (sc.ch==',')
						sc.SetState(SCE_SV_DEFAULT);
					else
						if (!sc.atLineEnd) sc.SetState(SCE_SV_DEFAULT);
				}
			}
			break;
		case SCE_SV_DEFAULT:
			if (sc.ch>='0' && sc.ch<='9')		sc.SetState(SCE_SV_NUMBER);
			else
				switch(sc.ch)
				{
				case ' ':
					break;
				case '\'':
					break;
				case '"':
						sc.SetState(SCE_SV_STRING);
						strBeginChar=sc.ch;
					break;
				default:
					presentInLists=0;
					sc.SetState(SCE_SV_IDENTIFIER);
					break;
				}	
			break;
		case SCE_SV_STRING:
			if (sc.ch==strBeginChar)
			{
				forvState=SCE_SV_DEFAULT;
			}
			else
				if (sc.atLineEnd)
					sc.ChangeState(SCE_SV_ERROR);
						
			break;

		default:
			presentInLists=0;

			if (sc.ch>='0' && sc.ch<='9')
				sc.SetState(SCE_SV_NUMBER);
			break;
		}

		if (sc.state!=SCE_SV_DEFAULT && sc.state!=SCE_SV_ERROR) prevState=sc.state;
	}

	sc.Complete();
}

static void FoldSepViewDoc(unsigned int startPos, int length, int,
						   WordList *[], Accessor &styler) {
	int endPos = startPos + length;
}

static void ColouriseSepViewNetDoc(unsigned int startPos, int length, int initStyle,
                           WordList *keywordlists[], Accessor &styler) {
	ColouriseSepViewDoc(startPos, length, initStyle, keywordlists, styler, false);
}

static const char * const SepViewWordListDesc[] = {
	"Keywords",
	"Keywords2",
	"Keywords3",
	"Keywords4",
	"Keywords5",
	"Keywords6",
	0
};

LexerModule lmSepView(SCLEX_SEPVIEW, ColouriseSepViewNetDoc, "SepView", FoldSepViewDoc, SepViewWordListDesc);

