// Scintilla source code edit control
/** @file LexPB.cxx
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

 
#define PB_MAYBE_COMMENT		0x0001
#define PB_MAYBE_NUMBER			0x0002
#define PB_MAYBE_KEYWORD		0x0004
#define PB_MAYBE_STRING			0x0008
#define PB_MAYBE_PREPROCESSOR	0x0010
#define PB_MAYBE_OPERATOR		0x0020
#define PB_MAYBE_IDENTIFIER		0x0040
#define PB_MAYBE_NEXTCOMMAND	0x0080
#define PB_MAYBE_SUBROUTINE		0x0100
#define PB_MAYBE_ANY			0x00FF

//MayBeFlag=PB_MAYBE_ANY^PB_MAYBE_COMMENT^PB_MAYBE_NUMBER^PB_MAYBE_KEYWORD^PB_MAYBE_STRING^PB_MAYBE_PREPROCESSOR^PB_MAYBE_OPERATOR^PB_MAYBE_IDENTIFIER^PB_MAYBE_NEXTCOMMAND^PB_MAYBE_SUBROUTINE;
//MayBeFlag=PB_MAYBE_COMMENT|PB_MAYBE_NUMBER|PB_MAYBE_KEYWORD|PB_MAYBE_STRING|PB_MAYBE_PREPROCESSOR|PB_MAYBE_OPERATOR|PB_MAYBE_IDENTIFIER|PB_MAYBE_NEXTCOMMAND|PB_MAYBE_SUBROUTINE;
/*
#define SCE_PB_DEFAULT 0
#define SCE_PB_COMMENT 1
#define SCE_PB_NUMBER 2
#define SCE_PB_KEYWORD 3
#define SCE_PB_STRING 4
#define SCE_PB_PREPROCESSOR 5
#define SCE_PB_OPERATOR 6
#define SCE_PB_IDENTIFIER 7
#define SCE_PB_DATE 8
#define SCE_PB_ERROR 9
#define SCE_PB_SUBROUTINE 10
*/

static bool IsPBComment(Accessor &styler, int pos, int len) {
	return len>0 && (styler[pos]=='!' || styler[pos]=='*' || ((styler[pos]=='r' || styler[pos]=='R') && (styler[pos+1]=='e' || styler[pos+1]=='E') && (styler[pos+2]=='m' || styler[pos+2]=='M') && (styler[pos+3]==' ' || styler[pos+3]=='\t')));
}


static void ColourisePBDoc(unsigned int startPos, int length, int initStyle,
                           WordList *keywordlists[], Accessor &styler, bool pbScriptSyntax)
 {

	WordList &keywordspb = *keywordlists[0];
	WordList &keywordsgp = *keywordlists[1];
	WordList &keywordsfs = *keywordlists[2];
	WordList &keywordsf3 = *keywordlists[3];
	WordList &keywordsf4 = *keywordlists[4];
	WordList &keywordsf5 = *keywordlists[5];

	styler.StartAt(startPos);

	char BracesArr[200];
	UINT BracesArrMayBeFlag[200];
	int posBraces=0;
	UINT presentInLists=0;
	BracesArrMayBeFlag[posBraces]=0;

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
			posBraces=0;
			BracesArrMayBeFlag[posBraces]=PB_MAYBE_ANY^PB_MAYBE_OPERATOR^PB_MAYBE_STRING;
			prevState=SCE_PB_DEFAULT;
			sc.SetState(SCE_PB_DEFAULT);
			presentInLists=0;
		}
//    dfdfgd          Str<1>=0:@vm:1:@vm:2:@vm:3:@vm:4:@vm:5:@vm:6:@vm:7:@vm:8:@vm:9:@vm:10:@vm:11:@vm:12:@vm:13:@vm:14:@vm:15:@vm:16:@vm:17:@vm:18
//	hfghgf          if DlgData(Ch<4>,8)<12>="" THEN DlgData(Ch<4>,8)<12>="0":@vm:"0"
//    gdfgdf          Str<21>="/d3 ":@vm:5

		BOOL phase2=TRUE;
		switch(sc.state)
		{
		case SCE_PB_OPERATOR:
			if (strchr("*/#=><:+-,",sc.ch))
			{
				phase2=FALSE;
				if (sc.ch=='-')
				{
					if (strchr("><:( []=\t#",sc.chPrev)==NULL || strchr(" ><,.#!=:;()[]-+*/\n\r\t",sc.chNext))
						sc.ChangeState(SCE_PB_ERROR);
					else
						forvState=SCE_PB_DEFAULT;
				}
				else
				if (strchr("><:+-",sc.chPrev)==NULL && sc.ch!='=') 
					sc.ChangeState(SCE_PB_ERROR);
				else
					forvState=SCE_PB_DEFAULT;
			}
			else
			{
				sc.SetState(SCE_PB_DEFAULT);
				BracesArrMayBeFlag[posBraces]=PB_MAYBE_NUMBER|PB_MAYBE_KEYWORD|PB_MAYBE_STRING|PB_MAYBE_IDENTIFIER;
			}

			break;
		case SCE_PB_NUMBER:
			if ((sc.ch<'0' || sc.ch>'9') && sc.ch!='.') 
			{
				sc.SetState(SCE_PB_DEFAULT);
				BracesArrMayBeFlag[posBraces]=PB_MAYBE_OPERATOR|PB_MAYBE_NEXTCOMMAND;
				if (strchr(":",sc.ch) && (BracesArrMayBeFlag[posBraces]&PB_MAYBE_OPERATOR))
					sc.SetState(SCE_PB_OPERATOR);
				else
					if (sc.ch==',')
					{
						phase2=FALSE;
						BracesArrMayBeFlag[posBraces]=PB_MAYBE_NUMBER|PB_MAYBE_STRING|PB_MAYBE_OPERATOR|PB_MAYBE_IDENTIFIER;
					}
			}
			else
			{
				if (sc.ch=='.')
				{
					char s[100];
					presentInLists=0;
					sc.GetCurrentLowered(s, sizeof(s));
					if (strchr(s,'.'))
					{
						sc.ChangeState(SCE_PB_ERROR);
						if (!sc.atLineEnd)
							forvState=SCE_PB_DEFAULT;
					}
					else phase2=FALSE;
				}
				else	phase2=FALSE;
			}
			break;
		case SCE_PB_IDENTIFIER:
			if (	sc.atLineEnd || sc.LengthCurrent()==length-1
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

				if (keywordspb.InList(s))
					presentInLists=0x1;
				else 
				if (keywordsgp.InList(s))
					presentInLists=0x2;
				else 
				if (keywordsfs.InList(s))
					presentInLists=0x4;
				else 
				if (keywordsf3.InList(s))
					presentInLists=0x8;
				else 
				if (keywordsf4.InList(s))
					presentInLists=0x10;
				else 
				if (keywordsf5.InList(s))
					presentInLists=0x20;


				if ((BracesArrMayBeFlag[posBraces]&PB_MAYBE_SUBROUTINE))
				{
					if (presentInLists)
					{
						sc.ChangeState(SCE_PB_ERROR);
						BracesArrMayBeFlag[posBraces]=PB_MAYBE_ANY;
						sc.SetState(SCE_PB_DEFAULT);
					}
					else
					if (sc.ch=='(')
					{
						sc.ChangeState(SCE_PB_SUBROUTINE);
						BracesArrMayBeFlag[posBraces]=PB_MAYBE_NUMBER|PB_MAYBE_KEYWORD|PB_MAYBE_STRING|PB_MAYBE_IDENTIFIER;
						sc.SetState(SCE_PB_DEFAULT);
					}
					else
					if (strchr(" \t\n\r;",sc.ch))
					{
						sc.ChangeState(SCE_PB_SUBROUTINE);
						BracesArrMayBeFlag[posBraces]=PB_MAYBE_NEXTCOMMAND;
						sc.SetState(SCE_PB_DEFAULT);
					}
					else
					if (sc.atLineEnd)
						BracesArrMayBeFlag[posBraces]=0;
					else
					{
						sc.ChangeState(SCE_PB_ERROR);
						BracesArrMayBeFlag[posBraces]=PB_MAYBE_ANY;
						sc.SetState(SCE_PB_DEFAULT);
					}
				}
				else
					if (presentInLists)
					{
						sc.ChangeState(SCE_PB_KEYWORD);
						if (sc.LengthCurrent()==length-1 || sc.atLineEnd || sc.ch=='(' || sc.ch==' ' || sc.ch=='\t' || sc.ch=='\r' || sc.ch=='\n')
						{
							if (strcmp(s,"rem")==0 && sc.ch!='(') sc.SetState(SCE_PB_COMMENT);
							else
							{
								BracesArrMayBeFlag[posBraces]=PB_MAYBE_NUMBER|PB_MAYBE_KEYWORD|PB_MAYBE_STRING|PB_MAYBE_OPERATOR|PB_MAYBE_IDENTIFIER|PB_MAYBE_NEXTCOMMAND;
								if (strcmp(s,"call")==0 && sc.ch==' ') BracesArrMayBeFlag[posBraces]|=PB_MAYBE_SUBROUTINE;
								if (strcmp(s,"then")==0 || strcmp(s,"else")==0 || strcmp(s,"locked")==0) BracesArrMayBeFlag[posBraces]&=(0xFFFF^PB_MAYBE_NUMBER^PB_MAYBE_STRING);
								if (!sc.atLineEnd) sc.SetState(SCE_PB_DEFAULT);
								if (strchr(":",sc.ch) && (BracesArrMayBeFlag[posBraces]&PB_MAYBE_OPERATOR))
									sc.SetState(SCE_PB_OPERATOR);
							}
						}
						else
						{
							sc.ChangeState(SCE_PB_ERROR);
							BracesArrMayBeFlag[posBraces]=PB_MAYBE_ANY;
							sc.SetState(SCE_PB_DEFAULT);
						}
					}
					else
					{
						if (sc.ch=='>')
						{
							if (posBraces && BracesArr[posBraces-1]=='<')
								sc.SetState(SCE_PB_DEFAULT);
							else 
								if ((BracesArrMayBeFlag[posBraces]&PB_MAYBE_OPERATOR))
									sc.SetState(SCE_PB_OPERATOR);
								else
									sc.SetState(SCE_PB_ERROR);
						}
						else
						if (strchr(")}]",sc.ch))
						{
							sc.SetState(SCE_PB_DEFAULT);
							BracesArrMayBeFlag[posBraces]=PB_MAYBE_STRING|PB_MAYBE_OPERATOR|PB_MAYBE_NEXTCOMMAND;
							if (strchr("; ",sc.chNext))
								BracesArrMayBeFlag[posBraces]|=PB_MAYBE_KEYWORD|PB_MAYBE_NUMBER|PB_MAYBE_IDENTIFIER;
						}
						else
						if (strchr(":=-+/*#",sc.ch))
						{
							sc.SetState(SCE_PB_OPERATOR);
							BracesArrMayBeFlag[posBraces]=PB_MAYBE_KEYWORD|PB_MAYBE_NUMBER|PB_MAYBE_STRING|PB_MAYBE_OPERATOR|PB_MAYBE_NEXTCOMMAND|PB_MAYBE_IDENTIFIER;
							phase2=FALSE;
						}
						else
						if (sc.ch==',')
						{
							BracesArrMayBeFlag[posBraces]=PB_MAYBE_KEYWORD|PB_MAYBE_NUMBER|PB_MAYBE_STRING|PB_MAYBE_OPERATOR|PB_MAYBE_NEXTCOMMAND|PB_MAYBE_IDENTIFIER;
							sc.SetState(SCE_PB_DEFAULT);
							phase2=FALSE;
						}
						else
						{
							BracesArrMayBeFlag[posBraces]=PB_MAYBE_NUMBER|PB_MAYBE_KEYWORD|PB_MAYBE_STRING|PB_MAYBE_OPERATOR|PB_MAYBE_NEXTCOMMAND;
							if (!sc.atLineEnd) sc.SetState(SCE_PB_DEFAULT);
						}
					}
			}
			else
			{
				phase2=FALSE;
			}
			break;
		case SCE_PB_DEFAULT:
			if (sc.ch=='<' && !sc.atLineStart && sc.chPrev!=')' && sc.chPrev!=' ' && sc.chPrev!='\t' && prevState==SCE_PB_IDENTIFIER)
			{
				if (strchr(",.:>}])!*/;?\\",sc.chNext))
					sc.SetState(SCE_PB_ERROR);
				else
				{
					BracesArr[posBraces++]=sc.ch;
					BracesArrMayBeFlag[posBraces]=PB_MAYBE_NUMBER|PB_MAYBE_KEYWORD|PB_MAYBE_IDENTIFIER;
				}
				phase2=FALSE;
			}
			else
			if (sc.ch=='>' && posBraces!=0 && BracesArr[posBraces-1]=='<')
			{
				if (strchr("<.,([=-+*#/;:^!",sc.chPrev))
				{
					sc.SetState(SCE_PB_ERROR);
					phase2=FALSE;
				}
				else
				{
					posBraces--;
					phase2=FALSE;
					BracesArrMayBeFlag[posBraces]|=PB_MAYBE_STRING|PB_MAYBE_NEXTCOMMAND|PB_MAYBE_OPERATOR;
					if (sc.chNext==' ' || sc.chNext=='\t')
						BracesArrMayBeFlag[posBraces]|=PB_MAYBE_KEYWORD;
				}
			}
			else
			if ((sc.ch=='*' || sc.ch=='!') && (BracesArrMayBeFlag[posBraces]&PB_MAYBE_COMMENT))
			{
				sc.SetState(SCE_PB_COMMENT);
				phase2=FALSE;
			}
			else
			if (strchr("><=:+-*/#",sc.ch))
			{
				if (BracesArrMayBeFlag[posBraces]&PB_MAYBE_OPERATOR)
				{
					sc.SetState(SCE_PB_OPERATOR);
					phase2=FALSE;
				}
				else 
					sc.SetState(SCE_PB_ERROR);
			}
			break;

		}

		if (phase2)
			switch(sc.state)
			{
			case SCE_PB_COMMENT:
				if (sc.atLineEnd) sc.SetState(SCE_PB_DEFAULT);
				break;
			case SCE_PB_STRING:
				if (sc.ch==strBeginChar)
				{
					forvState=SCE_PB_DEFAULT;
					BracesArrMayBeFlag[posBraces]=PB_MAYBE_KEYWORD|PB_MAYBE_OPERATOR|PB_MAYBE_NEXTCOMMAND;
				}
				else
					if (sc.atLineEnd) 
						sc.ChangeState(SCE_PB_ERROR);
							
				break;
			case SCE_PB_DEFAULT:
				switch(sc.ch)
				{
				case '!':
				case '*':
					if ((BracesArrMayBeFlag[posBraces]&PB_MAYBE_COMMENT)) 
						sc.SetState(SCE_PB_COMMENT);
					else
						if ((BracesArrMayBeFlag[posBraces]&PB_MAYBE_OPERATOR)) sc.SetState(SCE_PB_OPERATOR);
						else sc.SetState(SCE_PB_ERROR);
					break;
				case '\'':
				case '"':
					if ((BracesArrMayBeFlag[posBraces]&PB_MAYBE_STRING))
					{
						sc.SetState(SCE_PB_STRING);
						strBeginChar=sc.ch;
					}
					else
						sc.SetState(SCE_PB_ERROR);
					break;
				case '\r':
				case '\n':
					if (posBraces)
						sc.ChangeState(SCE_PB_ERROR);
					break;
				case ' ':
				case '\t':
					break;
				case ';':
					if ((BracesArrMayBeFlag[posBraces]&PB_MAYBE_NEXTCOMMAND))
					{
						BracesArrMayBeFlag[posBraces]=PB_MAYBE_COMMENT|PB_MAYBE_KEYWORD|PB_MAYBE_IDENTIFIER|PB_MAYBE_NEXTCOMMAND;
						if (posBraces) BracesArrMayBeFlag[posBraces]|=PB_MAYBE_STRING;
						else	prevState=SCE_PB_DEFAULT;

					}
					else
					{
 						if (!posBraces)	sc.SetState(SCE_PB_ERROR);
						if (!sc.atLineEnd) forvState=SCE_PB_DEFAULT;
					}
					break;
				default:
					presentInLists=0;

					if (sc.ch=='<' && !sc.atLineStart && sc.chPrev!=' ' && sc.chPrev!='\t' && prevState==SCE_PB_IDENTIFIER)
					{
						if (strchr(",.:>}])!*/;?\\",sc.chNext))
						{
							sc.SetState(SCE_PB_ERROR);
						}
						else
						{
							BracesArr[posBraces++]=sc.ch;
							BracesArrMayBeFlag[posBraces]=PB_MAYBE_NUMBER|PB_MAYBE_KEYWORD|PB_MAYBE_IDENTIFIER|PB_MAYBE_OPERATOR|PB_MAYBE_STRING;
						}
					}
					else
					if (sc.ch=='>' && posBraces!=0 && BracesArr[posBraces-1]=='<')
					{
						if (strchr("<.,([=-+*#/;:^!",sc.chPrev))
						{
							sc.SetState(SCE_PB_ERROR);
						}
						else
						{
							posBraces--;
							BracesArrMayBeFlag[posBraces]|=PB_MAYBE_STRING|PB_MAYBE_NEXTCOMMAND|PB_MAYBE_OPERATOR;
							if ((sc.chNext==' ' || sc.chNext=='\t') && posBraces==0)
								BracesArrMayBeFlag[posBraces]|=PB_MAYBE_KEYWORD;
							if (strchr("=,:; \t\n\r\"'-+#*/{([<>])}",sc.chNext)==NULL && posBraces)
								forvState=SCE_PB_ERROR;
						}
					}
					else
					if ((sc.ch=='<' || sc.ch=='>') && (BracesArrMayBeFlag[posBraces]&PB_MAYBE_OPERATOR))
					{
						BracesArrMayBeFlag[posBraces]=SCE_PB_OPERATOR;
						BracesArrMayBeFlag[posBraces]=PB_MAYBE_STRING|PB_MAYBE_NUMBER|PB_MAYBE_KEYWORD|PB_MAYBE_IDENTIFIER|PB_MAYBE_OPERATOR;
					}
					else
					if (sc.ch=='{' || sc.ch=='[' || sc.ch=='(')
					{
						if (strchr(",.:>}])!*/;?\\",sc.chNext))
						{
							sc.SetState(SCE_PB_ERROR);
						}
						else
						{
							if (((prevState|sc.state)&(SCE_PB_IDENTIFIER|SCE_PB_OPERATOR|SCE_PB_KEYWORD|SCE_PB_SUBROUTINE)))
							{
								BracesArr[posBraces++]=sc.ch;
								BracesArrMayBeFlag[posBraces]=PB_MAYBE_NUMBER|PB_MAYBE_KEYWORD|PB_MAYBE_IDENTIFIER|PB_MAYBE_STRING;
							}
							else
							{
								sc.SetState(SCE_PB_ERROR);
								if (!sc.atLineEnd) forvState=SCE_PB_DEFAULT;
							}
						}
					}
					else
					if (sc.ch=='}' || sc.ch==']' || sc.ch==')')
					{
						if (posBraces && ((sc.ch-BracesArr[--posBraces])&0x7F)<4)
						{
							BracesArrMayBeFlag[posBraces]|=PB_MAYBE_STRING|PB_MAYBE_NEXTCOMMAND|PB_MAYBE_OPERATOR;
							if (sc.chNext==' ' || sc.chNext=='\t')
								BracesArrMayBeFlag[posBraces]|=PB_MAYBE_KEYWORD;
						}
						else
						{
							sc.SetState(SCE_PB_ERROR);
							if (!sc.atLineEnd) forvState=SCE_PB_DEFAULT;
						}
					}
					else
					if (sc.ch>='0' && sc.ch<='9')
					{
						if ((BracesArrMayBeFlag[posBraces]&PB_MAYBE_NUMBER)) 
							sc.SetState(SCE_PB_NUMBER);
						else
						{
							sc.SetState(SCE_PB_ERROR);
						}
					}
					else
					if (strchr("?|.",sc.ch) || (sc.ch<' ' && sc.ch!=10 && sc.ch!=13))
					{
						sc.SetState(SCE_PB_ERROR);
					}
					else
					{
						if (strchr(",:",sc.ch)==NULL)
						{
							sc.SetState(SCE_PB_IDENTIFIER);
							BracesArrMayBeFlag[posBraces]|=PB_MAYBE_STRING|PB_MAYBE_OPERATOR;
						}
						else
						{
							BracesArrMayBeFlag[posBraces]|=PB_MAYBE_NUMBER|PB_MAYBE_KEYWORD|PB_MAYBE_STRING|PB_MAYBE_OPERATOR|PB_MAYBE_IDENTIFIER;
							BracesArrMayBeFlag[posBraces]&=(0xFFFF^PB_MAYBE_COMMENT|PB_MAYBE_NEXTCOMMAND|PB_MAYBE_SUBROUTINE);
						}
					}
					break;
				}
				break;
			}

		if (sc.state!=SCE_PB_DEFAULT && sc.state!=SCE_PB_ERROR) prevState=sc.state;
	}

	sc.Complete();
}

static void FoldPBDoc(unsigned int startPos, int length, int,
						   WordList *[], Accessor &styler) {
	int endPos = startPos + length;
	// Backtrack to previous line in case need to fix its fold status
	int lineCurrent = styler.GetLine(startPos);
	if (startPos > 0) {
		if (lineCurrent > 0) {
			lineCurrent--;
			startPos = styler.LineStart(lineCurrent);
		}
	}
	int spaceFlags = 0;
	int indentCurrent = styler.IndentAmount(lineCurrent, &spaceFlags, IsPBComment);
	char chNext = styler[startPos];
	int i ;
	for(i = startPos; i < endPos; i++) {
		char ch = chNext;
		chNext = styler.SafeGetCharAt(i + 1);

		if ((ch == '\r' && chNext != '\n') || (ch == '\n') || (i == endPos)) {
			int lev = indentCurrent;
			int indentNext = styler.IndentAmount(lineCurrent + 1, &spaceFlags, IsPBComment);
			if (!(indentCurrent & SC_FOLDLEVELWHITEFLAG)) {
				// Only non whitespace lines can be headers
				if ((indentCurrent & SC_FOLDLEVELNUMBERMASK) < (indentNext & SC_FOLDLEVELNUMBERMASK)) {
					lev |= SC_FOLDLEVELHEADERFLAG;
				} else if (indentNext & SC_FOLDLEVELWHITEFLAG) {
					// Line after is blank so check the next - maybe should continue further?
					int spaceFlags2 = 0;
					int indentNext2 = styler.IndentAmount(lineCurrent + 2, &spaceFlags2, IsPBComment);
					if ((indentCurrent & SC_FOLDLEVELNUMBERMASK) < (indentNext2 & SC_FOLDLEVELNUMBERMASK)) {
						lev |= SC_FOLDLEVELHEADERFLAG;
					}
				}
			}
			indentCurrent = indentNext;
			styler.SetLevel(lineCurrent, lev);
			lineCurrent++;
		}
	}
}

static void ColourisePBNetDoc(unsigned int startPos, int length, int initStyle,
                           WordList *keywordlists[], Accessor &styler) {
	ColourisePBDoc(startPos, length, initStyle, keywordlists, styler, false);
}

static const char * const pbWordListDesc[] = {
	"Keywords",
	"Keywords2",
	"Keywords3",
	"Keywords4",
	"Keywords5",
	"Keywords6",
	0
};

LexerModule lmPB(SCLEX_PB, ColourisePBNetDoc, "pb", FoldPBDoc, pbWordListDesc);

