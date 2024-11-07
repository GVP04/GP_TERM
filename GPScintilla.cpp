// GPScintilla.cpp : implementation file
//

#include "stdafx.h"
#include "gp_term.h"
#include "GPScintilla.h"
#include "Scintilla\Scintilla.h"
#include "Scintilla\SciLexer.h"
#include "GP_TermDoc.h"
#include "DlgEditorColor.h"
#include "GP_TermView.h"
#include "DlgGPScintillaFind.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgGPScintillaFind * GPScintilla::m_FindDlg=NULL;
CEditorPrintSettings GPScintilla::EditorPrintSettings;

/////////////////////////////////////////////////////////////////////////////
// GPScintilla
const UINT GPScintilla::uNMethods=440;
const char *GPScintilla::cArrMethods[]={
/*00*/		"SetViewEOL","GetViewEOL","SetZoom","GetZoom","AddText",
/*05*/		"AppendText","KeybAction","AssignCmdKey","ClearAllCmdKeys","ClearCmdKey",
/*10*/		"Cut","Copy","Paste","Clear","CanPaste",
/*15*/		"CopyRange","CopyText","ClearAll","SetOvertype","GetOvertype",
/*20*/		"GetText","GetTextLength","GetLength","SetText","SetSavePoint",
/*25*/		"GetModify","GetLine","ReplaceSel","SetReadonly","GetReadonly",
/*30*/		"GetTextRange","InsertText","ClearDocumentStyle","GetCharAt","GetStyleAt",
/*35*/		"SetStyleBits","GetStyleBits","SearchAnchor","SearchNext","SearchPrev",
/*40*/		"SearchNextScroll","SearchPrevScroll","FindText","SetTargetStart","GetTargetStart",
/*45*/		"SetTargetEnd","GetTargetEnd","SetTarget","GetTarget","TargetFromSelection",
/*50*/		"ReplaceTarget","ReplaceTargetRe","SetSearchFlags","GetSearchFlags","SearchInTarget",
/*55*/		"SetStatus","GetStatus","Undo","CanUndo","EmptyUndoBuffer",
/*60*/		"Redo","CanRedo","SetUndoCollection","GetUndoCollection","BeginUndoAction",
/*65*/		"EndUndoAction","GetLineCount","GetFirstVisibleLine","LinesOnScreen","SetSel",
/*70*/		"GotoPos","GotoLine","SetCurrentPos","GetCurrentPos","SetAnchor",
/*75*/		"GetAnchor","SetSelectionStart","SetSelectionEnd","GetSelectionStart","GetSelectionEnd",
/*80*/		"SelectAll","LineFromPosition","PositionFromLine","GetLineEndPosition","GetLineLength",
/*85*/		"GetSelText","GetCurLine","GetCurLineEx","SelectionIsRectangle","MoveCaretInsideView",
/*90*/		"WordEndPosition","WordStartPosition","PositionBefore","PositionAfter","TextWidth",
/*95*/		"TextHeight","GetColumn","PositionFromPoint","PositionFromPointClose","PointXFromPosition",
/*100*/		"PointYFromPosition","HideSelection","ChooseCaretX","LineScroll","ScrollCaret",
/*105*/		"SetXCaretPolicy","SetYCaretPolicy","SetVisiblePolicy","SetHScrollBar","GetHScrollBar",
/*110*/		"SetVScrollBar","GetVScrollBar","GetXOffset","SetXOffset","SetScrollWidth",
/*115*/		"GetScrollWidth","SetEndAtLastLine","GetEndAtLastLine","SetViewWS","GetViewWS",
/*120*/		"SetWhiteSpaceFore","SetWhiteSpaceBack","SetEditCursor","GetEditCursor","SetMouseDownCaptures",
/*125*/		"GetMouseDownCaptures","ConvertEOLs","SetEOLMode","GetEOLMode","SetSelFore",
/*130*/		"SetSelBack","SetCaretFore","GetCaretFore","SetCaretLineVisible","GetCaretLineVisible",
/*135*/		"SetCaretLineBack","GetCaretLineBack","SetCaretPeriod","GetCaretPeriod","SetCaretWidth",
/*140*/		"GetCaretWidth","SetHotspotActiveFore","SetHotspotActiveBack","SetHotspotActiveUnderline","SetControlCharSymbol",
/*145*/		"GetControlCharSymbol","SetMarginTypeN","GetMarginTypeN","SetMarginWidthN","GetMarginWidthN",
/*150*/		"SetMarginMaskN","GetMarginMaskN","SetMarginSensitiveN","GetMarginSensitiveN","SetMarginLeft",
/*155*/		"GetMarginLeft","SetMarginRight","GetMarginRight","SetFoldMarginColor","SetFoldMarginHiColor",
/*160*/		"SetBufferedDraw","GetBufferedDraw","SetTwoPhaseDraw","GetTwoPhaseDraw","SetCodePage",
/*165*/		"GetCodePage","SetWordChars","SCI_GrabFocus","SCI_SetFocus","SCI_GetFocus",
/*170*/		"BraceHighlight","BraceBadLight","BraceMatch","SetTabWidth","GetTabWidth",
/*175*/		"SetUseTabs","GetUseTabs","SetIndent","GetIndent","SetTabIndents",
/*180*/		"GetTabIndents","SetBackspaceUnindents","GetBackspaceUnindents","SetLineIndentation","GetLineIndentation",
/*185*/		"GetLineIndentPosition","SetIndentationGuides","GetIndentationGuides","SetHighlightGuide","GetHighlightGuide",
/*190*/		"MarkerDefine","MarkerDefinePixmap","MarkerSetFore","MarkerSetBack","MarkerAdd",
/*195*/		"MarkerDelete","MarkerDeleteAll","MarkerGet","MarkerNext","MarkerPrevious",
/*200*/		"MarkerLineFromHandle","MarkerDeleteHandle","IndicSetStyle","IndicGetStyle","IndicSetFore",
/*205*/		"IndicGetFore","AutocShow","AutocCancel","AutocActive","AutocPosStart",
/*210*/		"AutocComplete","AutocStops","AutocSetSeparator","AutocGetSeparator","AutocSelect",
/*215*/		"AutocSetCancelAtStart","AutocGetCancelAtStart","AutocSetFillUps","AutocSetChooseSingle","AutocGetChooseSingle",
/*220*/		"AutocSetIgnoreCase","AutocGetIgnoreCase","AutocSetAutoHide","AutocGetAutoHide","AutocSetDropRestOfWord",
/*225*/		"AutocGetDropRestOfWord","AutocSetTypeSeparator","AutocGetTypeSeparator","ClearRegisteredImages","RegisterImage",
/*230*/		"UserListShow","CallTipShow","CallTipCancel","CallTipActive","CallTipPosStart",
/*235*/		"CallTipSetHlt","CallTipSetBack","CallTipSetFore","CallTipSetForehlt","UsePopup",
/*240*/		"StartRecord","StopRecord","ColorsDialogLex","SetPrintMagnification","GetPrintMagnification",
/*245*/		"SetPrintColorMode","GetPrintColorMode","SetPrintWrapMode","GetPrintWrapMode","VisibleFromDocline",
/*250*/		"DoclineFromVisible","ShowLines","HideLines","GetLineVisible","SetFoldLevel",
/*255*/		"GetFoldLevel","SetFoldFlags","GetLastChild","GetFoldParent","SetFoldExpanded",
/*260*/		"GetFoldExpanded","ToggleFold","EnsureVisible","EnsureVisibleEnforcePolicy","SetWrapMode",
/*265*/		"GetWrapMode","SetLayoutCache","GetLayoutCache","LinesSplit","LinesJoin",
/*270*/		"ZoomIn","ZoomOut","SetEdgeMode","GetEdgeMode","SetEdgeColumn",
/*275*/		"GetEdgeColumn","SetEdgeColor","GetEdgeColor","SetLexer","GetLexer",
/*280*/		"SetLexerLanguage","LoadLexerLibrary","Colorise","SetProperty","SetKeywords",
/*285*/		"GetEndStyled","StartStyling","SetStyLing","SetStylingEx","SetLineState",
/*290*/		"GetLineState","GetMaxLineState","StyleResetDefault","StyleClearAll","StyleSetFont",
/*295*/		"StyleSetSize","StyleSetBold","StyleSetItalic","StyleSetUnderline","StyleSetFore",
/*300*/		"StyleSetBack","StyleSetEOLFilled","StyleSetCharacterSet","StyleSetCase","StyleSetVisible",
/*305*/		"StyleSetChangeable","StyleSetHotspot","SetMouseDwellTime","GetMouseDwellTime","SetUsePalette",
/*310*/		"GetUsePalette","Initialize","SetAStyle","ColorsDialog","StyleGetFore",
/*315*/		"StyleGetBack","StyleGetInfo","StyleGetFont","StyleGetSize","StyleGetBold",
/*320*/		"StyleGetItalic","StyleGetUnderline","StyleGetVisible","StyleGetEOLFilled","StyleGetCase",
/*325*/		"StyleGetCharacterSet","StyleGetHOTSPOT","SetAStyleEx","GetWhiteSpaceFore","GetWhiteSpaceBack",
/*330*/		"GetUseWhiteSpaceFore","GetUseWhiteSpaceBack","SetUseWhiteSpaceFore","SetUseWhiteSpaceBack","Sort",
/*335*/		"LoadText","SaveText","LoadKeywords","SaveKeywords","LoadColors",
/*340*/		"SetDirectInput","GetDirectInput","GetMarkerBack","GetMarkerFore","GetMarkerDefine",
/*345*/		"SetLineObject","SetColumnObject","SetLinePrefix","SetColumnPrefix","SetCharObject",
/*350*/		"SetCharPrefix","GetCurrentMarker","SetCurrentMarker","EnableContextMenu","IsEnableContextMenu",
/*355*/		"ShowFindDialog","LockHotKeys","Print","SetHeaderFormat","SetFooterFormat",
/*360*/		"GetHeaderFormat","GetFooterFormat","SetHeaderStyle","SetFooterStyle","GetHeaderStyle",
/*365*/		"GetFooterStyle","SetHeaderUse","SetFooterUse","GetHeaderUse","GetFooterUse",
/*370*/		"PageSetup","TrimEndSpace","GetLexers","SetWhitespaceChars","SetCharsDefault",
/*375*/		"Allocate","SetWrapVisualFlags","GetWrapVisualFlags","SetWrapVisualFlagsLocation","GetWrapVisualFlagsLocation",
/*380*/		"SetWrapStartIndent","GetWrapStartIndent","SetSelectionMode","GetSelectionMode","GetLineSelStartPosition",
/*385*/		"GetLineSelEndPosition","SetHotspotSingleLine","AutocGetCurrent","InitFolding","SetAutoIndent",
/*390*/		"GetAutoIndent","GetSelectionMetrics","FindTextEx","GetFindReplaceString","ReplaceAll",
/*395*/		"SetAutocList","AutocShowSpr","AutocShowListMaker","AutocShowWords","AutocSetMaxWidth",
/*400*/		"AutocGetMaxWidth","AutocSetMaxHeight","AutocGetMaxHeight","GetCaretSticky","SetCaretSticky",
/*405*/		"ToggleCaretSticky","FindColumn","SetLengthForEncode","EncodedFromUTF8","TargetAsUTF8",
/*410*/		"MarkerGetList","GetFoldExpandedList","SetFoldExpandedList","MarkerSetList","ReplaceWord",
/*415*/		"SelectWord","PointsFromPosition","GetMetricsByPos","GetMetricsByLine","SetLineStyle",
/*420*/		"SetStyleForText","GetStylePositions","GotoNextStyle","SetStyleByPos","SetFindString",
/*425*/		"SetReplaceString","ReplaceNext","ReplaceNextScroll","ReplacePrev","ReplacePrevScroll",
/*430*/		"SetFindStringCB","SetReplaceStringCB","SetAutoFocus","SetLine","InsertLine",
/*435*/		"DeleteLine","SetScrollTick","GetScrollTick","SetAutoScrollDelay","GetAutoScrollDelay",
/*440*/		"","","", "", "", 
/*445*/		"","","", "", "", 
/*450*/		"","","", "", "", 
	};

const char *GPScintilla::cArrMethodsParams[]={
/*00*/		"bEOL","","ZoomLevel","","Text",
/*05*/		"Text","Action[,nTimes]","Command,Key|Mod","","Key|Mod",
/*10*/		"","","","","",
/*15*/		"start,end","text","","bOvertype","",
/*20*/		"[TextLen]","","","Text","",
/*25*/		"","nLine","text","bReadonly","",
/*30*/		"Start,End","pos,Text","","position","position",
/*35*/		"StyleBits","","","flags,Text","flags,Text",
/*40*/		"flags,Text","flags,Text","start,end,searchFlags,text","position","",
/*45*/		"position","","start,end","","",
/*50*/		"Text","Text","SearchFlags","","Text",
/*55*/		"Status","","[nTimes]","","",
/*60*/		"[nTimes]","","bSetUndoCollection","","",
/*65*/		"","","","","Start,End",
/*70*/		"position","Line","CurrentPos","","Anchor",
/*75*/		"","SelectionStart","SelectionEnd","","",
/*80*/		"","Position","Line","Line","Line",
/*85*/		"","","","","",
/*90*/		"position,onlyWordCharacters","position,onlyWordCharacters","position","position","styleNumber,text",
/*95*/		"line","pos","x,y","x,y","pos",
/*100*/		"pos","bHide","","column,line","",
/*105*/		"caretSlop,caretPolicy","caretSlop,caretPolicy","caretSlop,caretPolicy","visible","",
/*110*/		"visible","","","xOffset","pixelWidth",
/*115*/		"","endAtLastLine","","wsMode","",
/*120*/		"useWSForeColor,r,g,b","useWSForeColor,r,g,b","curType","","captures",
/*125*/		"","eolMode","eolMode","","useSelectionForeColor,r,g,b",
/*130*/		"useSelectionForeColor,r,g,b","r,g,b","","show","",
/*135*/		"r,g,b","","milliseconds","","pixels",
/*140*/		"","useColor,r,g,b","useColor,r,g,b","","symbol",
/*145*/		"","Margin,MarginType","Margin","Margin,MarginWidth","Margin,",
/*150*/		"Margin,Mask","Margin,","Margin,sensitive","Margin,","pixels",
/*155*/		"","pixels","","useSetting,r,g,b","useSetting,r,g,b",
/*160*/		"bBuffered","","twoPhase","","CodePage",
/*165*/		"","WordChars","","focus","",
/*170*/		"pos1,pos2","pos1","position,maxReStyle","widthInChars","",
/*175*/		"useTabs","","widthInChars","","tabIndents",
/*180*/		"","bsUnIndents","","line,indentation","line",
/*185*/		"line","view","","column","",
/*190*/		"markerNumber,markerSymbols","markerNumber,xpm","markerNumber,r,g,b","markerNumber,r,g,b","line,markerNumber[,bToggle]",
/*195*/		"line,markerNumber[,bToggle]","markerNumber","line","lineStart,markerMask,bShow","lineStart,markerMask,bShow",
/*200*/		"handle","handle","indicatorNumber,indicatorStyle","indicatorNumber","indicatorNumber,r,g,b",
/*205*/		"indicatorNumber","lenEntered,list","","","",
/*210*/		"","chars","separator","","select",
/*215*/		"cancel","","chars","chooseSingle","",
/*220*/		"ignoreCase","","autoHide","","dropRestOfWord",
/*225*/		"","separatorCharacter","","","type,xpmData",
/*230*/		"lenEntered,list","posStart,definition","","","",
/*235*/		"highlightStart,highlightEnd","r,g,b","r,g,b","r,g,b","bEnablePopup",
/*240*/		"","","[FileName]","magnification","",
/*245*/		"mode","","","","docLine",
/*250*/		"displayLine","lineStart,lineEnd","lineStart,lineEnd","line","line,level",
/*255*/		"line","flags","line,level","line","line,expanded",
/*260*/		"line","line","line","line","wrapMode",
/*265*/		"","cacheMode","","","",
/*270*/		"","","mode","","column",
/*275*/		"","r,g,b","","lexer","",
/*280*/		"name","path","start,end","key,value","keyWordSet,keyWordList",
/*285*/		"","position,mask","length,style","length,style1^style2^...","line,value",
/*290*/		"line","","","","styleNumber,fontName",
/*295*/		"styleNumber,sizeInPoints","styleNumber,bold","styleNumber,italic","styleNumber,underline","styleNumber,r,g,b",
/*300*/		"styleNumber,r,g,b","styleNumber,eolFilled","styleNumber,charSet","styleNumber, caseMode","styleNumber, visible",
/*305*/		"styleNumber,changeable","styleNumber,hotspot","MouseDwellTime","","UsePalette",
/*310*/		"","[fontsize[,fontname]]","style,Rfore,Gfore,Bfore[,Rback,Gback,Bback[,size[,face]]]","bUpdate,S=style1,[SD=description,][F=Font,][FS=Size,][B=Bold,][I=Italic,][U=Underline,][V=Visible,][E=EOLFilled,][C=Case,][CS=CharacterSet,][H=HOTSPOT,][FR=Rfore,][FG=Gfore,][FB=Bfore,][BR=Rback,][BG=Gback,][BB=Bback,];style2....","Style",
/*315*/		"Style","Style","Style","Style","Style",
/*320*/		"Style","Style","Style","Style","Style",
/*325*/		"Style","Style","S=style1,[SD=description,][F=Font,][FS=Size,][B=Bold,][I=Italic,][U=Underline,][V=Visible,][E=EOLFilled,][C=Case,][CS=CharacterSet,][H=HOTSPOT,][FR=Rfore,][FG=Gfore,][FB=Bfore,][BR=Rback,][BG=Gback,][BB=Bback,];style2....","","",
/*330*/		"","","bUse","bUse","Options",
/*335*/		"Flags,FileName","Flags,FileName","LexerName","LexerName","LexerName,FileName",
/*340*/		"bTnable","","MarkerType","MarkerType","MarkerType",
/*345*/		"ObjectId","ObjectId","Text","Text","ObjectId",
/*350*/		"Text","","NewMarkerNum","bEnable","",
/*355*/		"bShow","bLock","bDialog|DIALOG|SELECTION|FORMAT|NOHEADER|NOFOOTER","HeaderFormat","FooterFormat",
/*360*/		"","","HeaderStyle","FooterStyle","",
/*365*/		"","bUse","bUse","bUse","bUse",
/*370*/		"","","","WSChars","",
/*375*/		"nBytes","wrapVisualFlags","","wrapVisualFlagsLocation","",
/*380*/		"indent","","Mode","","line",
/*385*/		"line","bsingleLine","","","m_AutoIndentFlag",
/*390*/		"","","searchFlags,text","","SearchFlags,SearchTextCHAR(1)ReplaceText",
/*395*/		"List","lenEntered,field,SprName","lenEntered,ListName","lenEntered[,MinLength=3]","characterCount",
/*400*/		"","rowCount","","","bUseCaretStickyBehaviour",
/*405*/		"","Line,Column","bytes","text","",
/*410*/		"","","bState[,Line1][,Line2][....]","MarkerId,Line1[,Line2][....]","[Position[-1]][,NewText]",
/*415*/		"[Position]","[Position]","[Position]","[Line]","Line,Style[,mask]",
/*420*/		"nStyle,SearchFlags;Text","nStyle","nStyle[,bDirection=1]","nStyle,nStyleMask,Pos1,Len1[^Pos2,Len2^...]","[Text]",
/*425*/		"[Text]","flags,SearchText","flags,SearchText","flags,SearchText","flags,SearchText",
/*430*/		"","","bAutoFocus","LineNumber,Text","LineNumber,Text",
/*435*/		"LineNumber","msScrollTick","","msAutoScrollDelay","",
/*440*/		"","","", "", "", 
/*445*/		"","","", "", "", 
/*450*/		"","","", "", "", 
	};

const char *GPScintilla::cArrKeybMethods[]={
		"LINEDOWN","LINEDOWNEXTEND","LINEUP","LINEUPEXTEND","PARADOWN",
		"PARADOWNEXTEND","PARAUP","PARAUPEXTEND","CHARLEFT","CHARLEFTEXTEND",
		"CHARRIGHT","CHARRIGHTEXTEND","WORDLEFT","WORDLEFTEXTEND","WORDRIGHT",
		"WORDRIGHTEXTEND","HOME","HOMEEXTEND","HOMEWRAP","HOMEWRAPEXTEND",
		"LINEEND","LINEENDEXTEND","LINEENDWRAP","LINEENDWRAPEXTEND","DOCUMENTSTART",
		"DOCUMENTSTARTEXTEND","DOCUMENTEND","DOCUMENTENDEXTEND","PAGEUP","PAGEUPEXTEND",
		"PAGEDOWN","PAGEDOWNEXTEND","EDITTOGGLEOVERTYPE","CANCEL","DELETEBACK",
		"DELETEBACKNOTLINE","TAB","BACKTAB","NEWLINE","FORMFEED",
		"VCHOME","VCHOMEEXTEND","DELWORDLEFT","DELWORDRIGHT","DELLINELEFT",
		"DELLINERIGHT","LINESCROLLDOWN","LINESCROLLUP","LINECUT","LINECOPY",
		"LINEDELETE","LINETRANSPOSE","LINEDUPLICATE","LOWERCASE","UPPERCASE",
		"WORDPARTLEFT","WORDPARTLEFTEXTEND","WORDPARTRIGHT","WORDPARTRIGHTEXTEND","HOMEDISPLAY",
		"HOMEDISPLAYEXTEND","LINEENDDISPLAY","LINEENDDISPLAYEXTEND","VCHOMEWRAP","VCHOMEWRAPEXTEND",
		"LINEDOWNRECTEXTEND","LINEUPRECTEXTEND","CHARLEFTRECTEXTEND","CHARRIGHTRECTEXTEND","WORDLEFTEND",
		"WORDLEFTENDEXTEND","WORDRIGHTEND","HOMERECTEXTEND","WORDRIGHTENDEXTEND","LINEENDRECTEXTEND",
		"STUTTEREDPAGEUP","STUTTEREDPAGEUPEXTEND","STUTTEREDPAGEDOWN","STUTTEREDPAGEDOWNEXTEND","PAGEUPRECTEXTEND",
		"PAGEDOWNRECTEXTEND","VCHOMERECTEXTEND",
		
		"LINEDOWNRECTEXTEND", "LINEUPRECTEXTEND", "CHARLEFTRECTEXTEND", "CHARRIGHTRECTEXTEND", "WORDLEFTEND", 
		"WORDLEFTENDEXTEND", "WORDRIGHTEND", "HOMERECTEXTEND", "WORDRIGHTENDEXTEND", "LINEENDRECTEXTEND", 
		"STUTTEREDPAGEUP", "STUTTEREDPAGEUPEXTEND", "STUTTEREDPAGEDOWN", "STUTTEREDPAGEDOWNEXTEND", "PAGEUPRECTEXTEND", 
		"PAGEDOWNRECTEXTEND", "VCHOMERECTEXTEND", 
		
		
		"","",
		
		};
const UINT  GPScintilla::uArrKeybMethods[]={
		SCI_LINEDOWN,SCI_LINEDOWNEXTEND,SCI_LINEUP,SCI_LINEUPEXTEND,SCI_PARADOWN,
		SCI_PARADOWNEXTEND,SCI_PARAUP,SCI_PARAUPEXTEND,SCI_CHARLEFT,SCI_CHARLEFTEXTEND,
		SCI_CHARRIGHT,SCI_CHARRIGHTEXTEND,SCI_WORDLEFT,SCI_WORDLEFTEXTEND,SCI_WORDRIGHT,
		SCI_WORDRIGHTEXTEND,SCI_HOME,SCI_HOMEEXTEND,SCI_HOMEWRAP,SCI_HOMEWRAPEXTEND,
		SCI_LINEEND,SCI_LINEENDEXTEND,SCI_LINEENDWRAP,SCI_LINEENDWRAPEXTEND,SCI_DOCUMENTSTART,
		SCI_DOCUMENTSTARTEXTEND,SCI_DOCUMENTEND,SCI_DOCUMENTENDEXTEND,SCI_PAGEUP,SCI_PAGEUPEXTEND,
		SCI_PAGEDOWN,SCI_PAGEDOWNEXTEND,SCI_EDITTOGGLEOVERTYPE,SCI_CANCEL,SCI_DELETEBACK,
		SCI_DELETEBACKNOTLINE,SCI_TAB,SCI_BACKTAB,SCI_NEWLINE,SCI_FORMFEED,
		SCI_VCHOME,SCI_VCHOMEEXTEND,SCI_DELWORDLEFT,SCI_DELWORDRIGHT,SCI_DELLINELEFT,
		SCI_DELLINERIGHT,SCI_LINESCROLLDOWN,SCI_LINESCROLLUP,SCI_LINECUT,SCI_LINECOPY,
		SCI_LINEDELETE,SCI_LINETRANSPOSE,SCI_LINEDUPLICATE,SCI_LOWERCASE,SCI_UPPERCASE,
		SCI_WORDPARTLEFT,SCI_WORDPARTLEFTEXTEND,SCI_WORDPARTRIGHT,SCI_WORDPARTRIGHTEXTEND,SCI_HOMEDISPLAY,
		SCI_HOMEDISPLAYEXTEND,SCI_LINEENDDISPLAY,SCI_LINEENDDISPLAYEXTEND,SCI_VCHOMEWRAP,SCI_VCHOMEWRAPEXTEND,
		SCI_LINEDOWNRECTEXTEND,SCI_LINEUPRECTEXTEND,SCI_CHARLEFTRECTEXTEND,SCI_CHARRIGHTRECTEXTEND,SCI_WORDLEFTEND,
		SCI_WORDLEFTENDEXTEND,SCI_WORDRIGHTEND,SCI_HOMERECTEXTEND,SCI_WORDRIGHTENDEXTEND,SCI_LINEENDRECTEXTEND,
		SCI_STUTTEREDPAGEUP,SCI_STUTTEREDPAGEUPEXTEND,SCI_STUTTEREDPAGEDOWN,SCI_STUTTEREDPAGEDOWNEXTEND,SCI_PAGEUPRECTEXTEND,
		SCI_PAGEDOWNRECTEXTEND,SCI_VCHOMERECTEXTEND,
		
		SCI_LINEDOWNRECTEXTEND, SCI_LINEUPRECTEXTEND, SCI_CHARLEFTRECTEXTEND, SCI_CHARRIGHTRECTEXTEND, SCI_WORDLEFTEND,
		SCI_WORDLEFTENDEXTEND, SCI_WORDRIGHTEND, SCI_HOMERECTEXTEND, SCI_WORDRIGHTENDEXTEND, SCI_LINEENDRECTEXTEND,
		SCI_STUTTEREDPAGEUP, SCI_STUTTEREDPAGEUPEXTEND, SCI_STUTTEREDPAGEDOWN, SCI_STUTTEREDPAGEDOWNEXTEND, SCI_PAGEUPRECTEXTEND,
		SCI_PAGEDOWNRECTEXTEND, SCI_VCHOMERECTEXTEND,
	
		0,0,
		};

const char *GPScintilla::SepViewKeyWordsDef=
"list select sort who lu maxusers fof delete sselect gl sl set-device"
"";

const char *GPScintilla::pbKeyWords=
"and begin capturing call case char close common convert crt "
"data dcount delete dim else end execute exit field for from gosub goto "
"if iconv in include index input locate locked loop mat matbuild matparse matread matreadu mod next "
"oconv open or out print prompt read readnext readu readv readvu rem repeat return "
"select step stop sub subroutine system then to until while write writeu writev writevu xor";

const char *GPScintilla::gpKeyWords=
	"";

const char *GPScintilla::fsKeyWords=
	"";


const UINT GPScintilla::uN0Methods=33;
const char *GPScintilla::cArr0Methods[33]={
		"SCI_NULL","CLEARALLCMDKEYS","CUT","COPY","PASTE",
		"CLEAR","CLEARALL","SETSAVEPOINT","CLEARDOCUMENTSTYLE","SEARCHANCHOR",
		"TARGETFROMSELECTION","UNDO","EMPTYUNDOBUFFER","REDO","BEGINUNDOACTION",
		"ENDUNDOACTION","CHOOSECARETX","MOVECARETINSIDEVIEW","SELECTALL","SCROLLCARET",
		"GRABFOCUS","AUTOCCANCEL","AUTOCACTIVE","AUTOCPOSSTART","AUTOCCOMPLETE",
		"CLEARREGISTEREDIMAGES","CALLTIPCANCEL","STARTRECORD","STOPRECORD","ZOOMIN",
		"ZOOMOUT","STYLERESETDEFAULT","STYLECLEARALL",
		};
const UINT  GPScintilla::uArr0Methods[33]={
		SCI_NULL,SCI_CLEARALLCMDKEYS,SCI_CUT,SCI_COPY,SCI_PASTE,
		SCI_CLEAR,SCI_CLEARALL,SCI_SETSAVEPOINT,SCI_CLEARDOCUMENTSTYLE, SCI_SEARCHANCHOR,
		SCI_TARGETFROMSELECTION,SCI_UNDO,SCI_EMPTYUNDOBUFFER,SCI_REDO,SCI_BEGINUNDOACTION,
		SCI_ENDUNDOACTION,SCI_CHOOSECARETX,SCI_MOVECARETINSIDEVIEW,SCI_SELECTALL,SCI_SCROLLCARET,
		SCI_GRABFOCUS,SCI_AUTOCCANCEL,SCI_AUTOCACTIVE,SCI_AUTOCPOSSTART,SCI_AUTOCCOMPLETE,
		SCI_CLEARREGISTEREDIMAGES,SCI_CALLTIPCANCEL,SCI_STARTRECORD,SCI_STOPRECORD,SCI_ZOOMIN,
		SCI_ZOOMOUT,SCI_STYLERESETDEFAULT,SCI_STYLECLEARALL,
		};

const UINT GPScintilla::uNKeybDef=20;
const char *GPScintilla::cArrKeybDef[20]={
		"SCK_ADD","SCK_BACK","SCK_DELETE","SCK_DIVIDE","SCK_DOWN",
		"SCK_END","SCK_ESCAPE","SCK_HOME","SCK_INSERT","SCK_LEFT",
		"SCK_NEXT","SCK_PRIOR","SCK_RETURN","SCK_RIGHT","SCK_SUBTRACT",
		"SCK_TAB","SCK_UP","SCMOD_ALT","SCMOD_CTRL","SCMOD_SHIFT",
		};
const UINT  GPScintilla::uArrKeybDef[20]={
		SCK_ADD,SCK_BACK,SCK_DELETE,SCK_DIVIDE,SCK_DOWN,
		SCK_END,SCK_ESCAPE,SCK_HOME,SCK_INSERT,SCK_LEFT,
		SCK_NEXT,SCK_PRIOR,SCK_RETURN,SCK_RIGHT,SCK_SUBTRACT,
		SCK_TAB,SCK_UP,SCMOD_ALT,SCMOD_CTRL,SCMOD_SHIFT,
		};

const UINT GPScintilla::uNSearchFlags=6;
const char *GPScintilla::cArrSearchFlags[]={
		"MATCHCASE","POSIX","REGEXP","WHOLEWORD","WORDSTART","SELECTION",
		};
const UINT  GPScintilla::uArrSearchFlags[]={
		SCFIND_MATCHCASE,SCFIND_POSIX,SCFIND_REGEXP,SCFIND_WHOLEWORD,SCFIND_WORDSTART,SCFIND_SELECTION,
		};

const UINT GPScintilla::uNcaretPolicy=4;
const char *GPScintilla::cArrcaretPolicy[4]={
		"EVEN","JUMPS","SLOP","STRICT",
		};
const UINT  GPScintilla::uArrcaretPolicy[4]={
		CARET_EVEN,CARET_JUMPS,CARET_SLOP,CARET_STRICT,
		};

const UINT GPScintilla::uNWSpaceStyle=3;
const char *GPScintilla::cArrWSpaceStyle[3]={
		"INVISIBLE","VISIBLEAFTERINDENT","VISIBLEALWAYS",
		};
const UINT  GPScintilla::uArrWSpaceStyle[3]={
		SCWS_INVISIBLE,SCWS_VISIBLEAFTERINDENT,SCWS_VISIBLEALWAYS,
		};

const UINT GPScintilla::uNCursorType=2;
const char *GPScintilla::cArrCursorType[2]={
		"CURSORNORMAL","CURSORWAIT",
		};
const int  GPScintilla::uArrCursorType[2]={
		SC_CURSORNORMAL,SC_CURSORWAIT,
		};

const UINT GPScintilla::uNEOLMode=3;
const char *GPScintilla::cArrEOLMode[3]={
		"EOL_CR","EOL_CRLF","EOL_LF",
		};

const UINT  GPScintilla::uArrEOLMode[3]={
		SC_EOL_CR,SC_EOL_CRLF,SC_EOL_LF,
		};

const UINT GPScintilla::uNMarginType=3;
const char *GPScintilla::cArrMarginType[3]={
		"MARGIN_NUMBER","MARGIN_SYMBOL","3",
		};
const UINT  GPScintilla::uArrMarginType[3]={
		SC_MARGIN_NUMBER,SC_MARGIN_SYMBOL,3,
		};

const UINT GPScintilla::uNMarginMask=1;
const char *GPScintilla::cArrMarginMask[3]={
		"MASK_FOLDERS","","",
		};
const UINT  GPScintilla::uArrMarginMask[3]={
		SC_MASK_FOLDERS,0,0,
		};
		
const UINT GPScintilla::uNCodePage=2;
const char *GPScintilla::cArrCodePage[3]={
		"CP_DBCS","CP_UTF8","",
		};
const UINT  GPScintilla::uArrCodePage[3]={
		SC_CP_DBCS,SC_CP_UTF8,0,
		};

const UINT GPScintilla::uNMark=27;
const char *GPScintilla::cArrMark[27]={
		"CIRCLE","ROUNDRECT","ARROW","SMALLRECT","SHORTARROW",
		"EMPTY","ARROWDOWN","MINUS","PLUS","VLINE",
		"LCORNER","TCORNER","BOXPLUS","BOXPLUSCONNECTED","BOXMINUS",
		"BOXMINUSCONNECTED","LCORNERCURVE","TCORNERCURVE","CIRCLEPLUS","CIRCLEPLUSCONNECTED",
		"CIRCLEMINUS","CIRCLEMINUSCONNECTED","BACKGROUND","DOTDOTDOT","ARROWS",
		"PIXMAP","CHARACTER",
		};
const UINT  GPScintilla::uArrMark[27]={
		SC_MARK_CIRCLE,SC_MARK_ROUNDRECT,SC_MARK_ARROW,SC_MARK_SMALLRECT,SC_MARK_SHORTARROW,
		SC_MARK_EMPTY,SC_MARK_ARROWDOWN,SC_MARK_MINUS,SC_MARK_PLUS,SC_MARK_VLINE,
		SC_MARK_LCORNER,SC_MARK_TCORNER,SC_MARK_BOXPLUS,SC_MARK_BOXPLUSCONNECTED,SC_MARK_BOXMINUS,
		SC_MARK_BOXMINUSCONNECTED,SC_MARK_LCORNERCURVE,SC_MARK_TCORNERCURVE,SC_MARK_CIRCLEPLUS,SC_MARK_CIRCLEPLUSCONNECTED,
		SC_MARK_CIRCLEMINUS,SC_MARK_CIRCLEMINUSCONNECTED,SC_MARK_BACKGROUND,SC_MARK_DOTDOTDOT,SC_MARK_ARROWS,
		SC_MARK_PIXMAP,SC_MARK_CHARACTER,
		};

const UINT GPScintilla::uNMarkNum=7;
const char *GPScintilla::cArrMarkNum[7]={
		"FOLDER","FOLDEREND","FOLDERMIDTAIL","FOLDEROPEN","FOLDEROPENMID",
		"FOLDERSUB","FOLDERTAIL",
		};
const UINT  GPScintilla::uArrMarkNum[7]={
		SC_MARKNUM_FOLDER,SC_MARKNUM_FOLDEREND,SC_MARKNUM_FOLDERMIDTAIL,SC_MARKNUM_FOLDEROPEN,SC_MARKNUM_FOLDEROPENMID,
		SC_MARKNUM_FOLDERSUB,SC_MARKNUM_FOLDERTAIL,
		};

const UINT GPScintilla::uNIndicator=8;
const char *GPScintilla::cArrIndicator[8]={
		"DIAGONAL","MAX","PLAIN","SQUIGGLE","STRIKE",
		"TT","HIDDEN","BOX",
		};
const UINT  GPScintilla::uArrIndicator[8]={
		INDIC_DIAGONAL,INDIC_MAX,INDIC_PLAIN,INDIC_SQUIGGLE,INDIC_STRIKE,
		INDIC_TT,INDIC_HIDDEN,INDIC_BOX,
		};

const UINT GPScintilla::uNPrintMode=5;
const char *GPScintilla::cArrPrintMode[5]={
		"BLACKONWHITE","COLORONWHITE","COLORONWHITEDEFAULTBG","INVERTLIGHT","NORMAL",
		};
const UINT  GPScintilla::uArrPrintMode[5]={
		SC_PRINT_BLACKONWHITE,SC_PRINT_COLOURONWHITE,SC_PRINT_COLOURONWHITEDEFAULTBG,SC_PRINT_INVERTLIGHT,SC_PRINT_NORMAL,
		};

const UINT GPScintilla::uNWrapMode=3;
const char *GPScintilla::cArrWrapMode[3]={
		"WRAP_NONE","WRAP_WORD","WRAP_CHAR ",
		};
const UINT  GPScintilla::uArrWrapMode[3]={
		SC_WRAP_NONE,SC_WRAP_WORD,SC_WRAP_CHAR,
		};

const UINT GPScintilla::uNFoldFlag=6;
const char *GPScintilla::cArrFoldFlag[6]={
		"BOX","LEVELNUMBERS","LINEAFTER_CONTRACTED",
		"LINEAFTER_EXPANDED","LINEBEFORE_CONTRACTED","LINEBEFORE_EXPANDED",
		};
const UINT  GPScintilla::uArrFoldFlag[6]={
		SC_FOLDFLAG_BOX,SC_FOLDFLAG_LEVELNUMBERS,SC_FOLDFLAG_LINEAFTER_CONTRACTED,
		SC_FOLDFLAG_LINEAFTER_EXPANDED,SC_FOLDFLAG_LINEBEFORE_CONTRACTED,SC_FOLDFLAG_LINEBEFORE_EXPANDED,
		};

const UINT GPScintilla::uNCacheMode=4;
const char *GPScintilla::cArrCacheMode[4]={
		"CARET","DOCUMENT","NONE","PAGE",
		};
const UINT  GPScintilla::uArrCacheMode[4]={
		SC_CACHE_CARET,SC_CACHE_DOCUMENT,SC_CACHE_NONE,SC_CACHE_PAGE,
		};

const UINT GPScintilla::uNEdgeMode=3;
const char *GPScintilla::cArrEdgeMode[3]={
		"BACKGROUND","LINE","NONE",
		};
const UINT  GPScintilla::uArrEdgeMode[3]={
		EDGE_BACKGROUND,EDGE_LINE,EDGE_NONE,
		};

const char *GPScintilla::cArrLexer[]={
		"CONTAINER","NULL","PYTHON","CPP","HTML",
		"XML","PERL","SQL","VB","PROPERTIES",
		"ERRORLIST","MAKEFILE","BATCH","XCODE","LATEX",
		"LUA","DIFF","CONF","PASCAL","AVE",
		"ADA","LISP","RUBY","EIFFEL","EIFFELKW",
		"TCL","NNCRONTAB","BULLANT","VBSCRIPT","ASP",
		"PHP","BAAN","MATLAB","SCRIPTOL","ASM",
		"CPPNOCASE","FORTRAN","F77","CSS","POV",
		"LOUT","ESCRIPT","AUTOMATIC","PB","SEPVIEW",
		"C","RC","IDL","JAVA","JAVASCRIPT",
		"PLSQL","PS","NSIS","MMIXAL","CLW",
		"CLWNOCASE","LOT","YAML","TEX","METAPOST",
		"POWERBASIC","FORTH","ERLANG","OCTAVE","MSSQL",
		"VERILOG","KIX","GUI4CLI","SPECMAN","AU3",
		"APDL","BASH","MVITEM","ASN1","VHDL",
		"CAML","BLITZBASIC","PUREBASIC","HASKELL","PHPSCRIPT",
		"MVTEXT",
		
		"TADS3", "REBOL", "SMALLTALK", "FLAGSHIP", "CSOUND", 
		"FREEBASIC", "INNOSETUP", "OPAL", "SPICE", "D", 
		"CMAKE", "GAP", "PLM", "PROGRESS", "ABAQUS", 
		"ASYMPTOTE", "R", "MAGIK", "POWERSHELL", "MYSQL", 
		"PO", 
		
		"","","","",
		};
const UINT  GPScintilla::uArrLexer[]={
		SCLEX_CONTAINER,SCLEX_NULL,SCLEX_PYTHON,SCLEX_CPP,SCLEX_HTML,
		SCLEX_XML,SCLEX_PERL,SCLEX_SQL,SCLEX_VB,SCLEX_PROPERTIES,
		SCLEX_ERRORLIST,SCLEX_MAKEFILE,SCLEX_BATCH,SCLEX_XCODE,SCLEX_LATEX,
		SCLEX_LUA,SCLEX_DIFF,SCLEX_CONF,SCLEX_PASCAL,SCLEX_AVE,
		SCLEX_ADA,SCLEX_LISP,SCLEX_RUBY,SCLEX_EIFFEL,SCLEX_EIFFELKW,
		SCLEX_TCL,SCLEX_NNCRONTAB,SCLEX_BULLANT,SCLEX_VBSCRIPT,SCLEX_ASP,
		SCLEX_PHP,SCLEX_BAAN,SCLEX_MATLAB,SCLEX_SCRIPTOL,SCLEX_ASM,
		SCLEX_CPPNOCASE,SCLEX_FORTRAN,SCLEX_F77,SCLEX_CSS,SCLEX_POV,
		SCLEX_LOUT,SCLEX_ESCRIPT,SCLEX_AUTOMATIC,SCLEX_PB,SCLEX_SEPVIEW,
		SCLEX_C,SCLEX_RC,SCLEX_IDL,SCLEX_JAVA,SCLEX_JAVASCRIPT,
		SCLEX_PLSQL,SCLEX_PS,SCLEX_NSIS,SCLEX_MMIXAL,SCLEX_CLW,
		SCLEX_CLWNOCASE,SCLEX_LOT,SCLEX_YAML,SCLEX_TEX,SCLEX_METAPOST,
		SCLEX_POWERBASIC,SCLEX_FORTH,SCLEX_ERLANG,SCLEX_OCTAVE,SCLEX_MSSQL,
		SCLEX_VERILOG,SCLEX_KIX,SCLEX_GUI4CLI,SCLEX_SPECMAN,SCLEX_AU3,
		SCLEX_APDL,SCLEX_BASH,SCLEX_MVITEM,SCLEX_ASN1,SCLEX_VHDL,
		SCLEX_CAML,SCLEX_BLITZBASIC,SCLEX_PUREBASIC,SCLEX_HASKELL,SCLEX_PHPSCRIPT,
		SCLEX_MVTEXT,
		
		SCLEX_TADS3, SCLEX_REBOL, SCLEX_SMALLTALK, SCLEX_FLAGSHIP, SCLEX_CSOUND,
		SCLEX_FREEBASIC, SCLEX_INNOSETUP, SCLEX_OPAL, SCLEX_SPICE, SCLEX_D,
		SCLEX_CMAKE, SCLEX_GAP, SCLEX_PLM, SCLEX_PROGRESS, SCLEX_ABAQUS, 
		SCLEX_ASYMPTOTE, SCLEX_R, SCLEX_MAGIK, SCLEX_POWERSHELL, SCLEX_MYSQL,
		SCLEX_PO,
		
		SCLEX_NULL,	SCLEX_NULL,	SCLEX_NULL,
		};
		
		



		

const UINT GPScintilla::uNStyleType=8;
const char *GPScintilla::cArrStyleType[8]={
		"BRACEBAD","BRACELIGHT","CONTROLCHAR","DEFAULT","INDENTGUIDE",
		"LASTPREDEFINED","LINENUMBER","MAX",
		};
const UINT  GPScintilla::uArrStyleType[8]={
		STYLE_BRACEBAD,STYLE_BRACELIGHT,STYLE_CONTROLCHAR,STYLE_DEFAULT,STYLE_INDENTGUIDE,
		STYLE_LASTPREDEFINED,STYLE_LINENUMBER,STYLE_MAX,
		};


const UINT GPScintilla::uNCharSet=19;
const char *GPScintilla::cArrCharSet[19]={
		"ANSI","ARABIC","BALTIC","CHINESEBIG5","DEFAULT",
		"EASTEUROPE","GB2312","GREEK","HANGUL","HEBREW",
		"JOHAB","MAC","OEM","RUSSIAN","SHIFTJIS",
		"SYMBOL","THAI","TURKISH","VIETNAMESE",
		};
const UINT  GPScintilla::uArrCharSet[19]={
		SC_CHARSET_ANSI,SC_CHARSET_ARABIC,SC_CHARSET_BALTIC,SC_CHARSET_CHINESEBIG5,SC_CHARSET_DEFAULT,
		SC_CHARSET_EASTEUROPE,SC_CHARSET_GB2312,SC_CHARSET_GREEK,SC_CHARSET_HANGUL,SC_CHARSET_HEBREW,
		SC_CHARSET_JOHAB,SC_CHARSET_MAC,SC_CHARSET_OEM,SC_CHARSET_RUSSIAN,SC_CHARSET_SHIFTJIS,
		SC_CHARSET_SYMBOL,SC_CHARSET_THAI,SC_CHARSET_TURKISH,SC_CHARSET_VIETNAMESE,
		};

const UINT GPScintilla::uNCaseType=3;
const char *GPScintilla::cArrCaseType[3]={
		"LOWER","MIXED","UPPER",
		};
const UINT  GPScintilla::uArrCaseType[3]={
		SC_CASE_LOWER,SC_CASE_MIXED,SC_CASE_UPPER,
		};

const UINT GPScintilla::uNVisiblePolicy=2;
const char *GPScintilla::cArrVisiblePolicy[2]={
		"SLOP","STRICT",
		};
const UINT  GPScintilla::uArrVisiblePolicy[2]={
		VISIBLE_SLOP,VISIBLE_STRICT,
		};

const UINT GPScintilla::uNFoldLevel=7;
const char *GPScintilla::cArrFoldLevel[7]={
		"FOLDLEVELBASE","FOLDLEVELBOXFOOTERFLAG","FOLDLEVELBOXHEADERFLAG","FOLDLEVELCONTRACTED","FOLDLEVELHEADERFLAG",
		"FOLDLEVELUNINDENT","FOLDLEVELWHITEFLAG",
		};
const UINT  GPScintilla::uArrFoldLevel[7]={
		SC_FOLDLEVELBASE,SC_FOLDLEVELBOXFOOTERFLAG,SC_FOLDLEVELBOXHEADERFLAG,SC_FOLDLEVELCONTRACTED,SC_FOLDLEVELHEADERFLAG,
		SC_FOLDLEVELUNINDENT,SC_FOLDLEVELWHITEFLAG,
		};

const UINT GPScintilla::uNMarkerMask=32;
const char *GPScintilla::cArrMarkerMask[32]={
		"MARKERMASK_0","MARKERMASK_1","MARKERMASK_2","MARKERMASK_3","MARKERMASK_4",
		"MARKERMASK_5","MARKERMASK_6","MARKERMASK_7","MARKERMASK_8","MARKERMASK_9",
		"MARKERMASK_10","MARKERMASK_11","MARKERMASK_12","MARKERMASK_13","MARKERMASK_14",
		"MARKERMASK_15","MARKERMASK_16","MARKERMASK_17","MARKERMASK_18","MARKERMASK_19",
		"MARKERMASK_20","MARKERMASK_21","MARKERMASK_22","MARKERMASK_23","MARKERMASK_24",
		"MARKERMASK_25","MARKERMASK_26","MARKERMASK_27","MARKERMASK_28","MARKERMASK_29",
		"MARKERMASK_30","MARKERMASK_31",
		};
const UINT  GPScintilla::uArrMarkerMask[32]={
		0x00000001,0x00000002,0x00000004,0x00000008,0x00000010,
		0x00000020,0x00000040,0x00000080,0x00000100,0x00000200,
		0x00000400,0x00000800,0x00001000,0x00002000,0x00004000,
		0x00008000,0x00010000,0x00020000,0x00040000,0x00080000,
		0x00100000,0x00200000,0x00400000,0x00800000,0x01000000,
		0x02000000,0x04000000,0x08000000,0x10000000,0x20000000,
		0x40000000,0x80000000,
		};
	
const char *GPScintilla::cArrStyles[]={
			"SCLEX_CONTAINER",	"SCLEX_NULL",	"SCLEX_PYTHON",	"SCLEX_CPP",	"SCLEX_HTML",
			"SCLEX_XML",		"SCLEX_PERL",	"SCLEX_SQL",	"SCLEX_VB",	"SCLEX_PROPERTIES",
			"SCLEX_ERRORLIST",	"SCLEX_MAKEFILE",	"SCLEX_BATCH",	"SCLEX_XCODE",	"SCLEX_LATEX",
			"SCLEX_LUA",		"SCLEX_DIFF",	"SCLEX_CONF",	"SCLEX_PASCAL",	"SCLEX_AVE",
			"SCLEX_ADA",		"SCLEX_LISP",	"SCLEX_RUBY",	"SCLEX_EIFFEL",	"SCLEX_EIFFELKW",
			"SCLEX_TCL",		"SCLEX_NNCRONTAB",	"SCLEX_BULLANT",	"SCLEX_VBSCRIPT",	"SCLEX_ASP",
			"SCLEX_PHP",		"SCLEX_BAAN",	"SCLEX_MATLAB",	"SCLEX_SCRIPTOL",	"SCLEX_ASM",
			"SCLEX_CPPNOCASE",	"SCLEX_FORTRAN",	"SCLEX_F77",	"SCLEX_CSS",	"SCLEX_POV",
			"SCLEX_LOUT",		"SCLEX_ESCRIPT",	"SCLEX_PS",	"SCLEX_NSIS",	"SCLEX_MMIXAL",
			"SCLEX_CLW",		"SCLEX_CLWNOCASE",	"SCLEX_LOT",	"SCLEX_YAML",	"SCLEX_TEX",
			"SCLEX_METAPOST",	"SCLEX_POWERBASIC",	"SCLEX_FORTH",	"SCLEX_ERLANG",	"SCLEX_OCTAVE",
			"SCLEX_MSSQL",		"SCLEX_VERILOG",	"SCLEX_KIX",	"SCLEX_GUI4CLI",	"SCLEX_SPECMAN",
			"SCLEX_AU3",		"SCLEX_APDL",	"SCLEX_BASH",	"SCLEX_ASN1",	"SCLEX_VHDL",
			"SCLEX_CAML",		"SCLEX_BLITZBASIC",	"SCLEX_PUREBASIC",	"SCLEX_HASKELL",	"SCLEX_PHPSCRIPT",
			"SCLEX_MVITEM",		"SCLEX_PB",	"SCLEX_SEPVIEW",	"SCLEX_C",	"SCLEX_RC",
			"SCLEX_IDL",		"SCLEX_JAVA",	"SCLEX_JAVASCRIPT",	"P_DEFAULT",	"P_COMMENTLINE",
			"P_NUMBER",			"P_STRING",	"P_CHARACTER",	"P_WORD",	"P_TRIPLE",
			"P_TRIPLEDOUBLE",	"P_CLASSNAME",	"P_DEFNAME",	"P_OPERATOR",	"P_IDENTIFIER",
			"P_COMMENTBLOCK",	"P_STRINGEOL",	"C_DEFAULT",	"C_COMMENT",	"C_COMMENTLINE",
			"C_COMMENTDOC",		"C_NUMBER",	"C_WORD",	"C_STRING",	"C_CHARACTER",
			"C_UUID",			"C_PREPROCESSOR",	"C_OPERATOR",	"C_IDENTIFIER",	"C_STRINGEOL",
			"C_VERBATIM",		"C_REGEX",	"C_COMMENTLINEDOC",	"C_WORD2",	"C_COMMENTDOCKEYWORD",
			"C_COMMENTDOCKEYWORDERROR",	"C_GLOBALCLASS",	"H_DEFAULT",	"H_TAG",	"H_TAGUNKNOWN",
			"H_ATTRIBUTE",		"H_ATTRIBUTEUNKNOWN",	"H_NUMBER",	"H_DOUBLESTRING",	"H_SINGLESTRING",
			"H_OTHER",			"H_COMMENT",	"H_ENTITY",	"H_TAGEND",	"H_XMLSTART",
			"H_XMLEND",			"H_SCRIPT",	"H_ASP",	"H_ASPAT",	"H_CDATA",
			"H_QUESTION",		"H_VALUE",	"H_XCCOMMENT",	"H_SGML_DEFAULT",	"H_SGML_COMMAND",
			"H_SGML_1ST_PARAM",	"H_SGML_DOUBLESTRING",	"H_SGML_SIMPLESTRING",	"H_SGML_ERROR",	"H_SGML_SPECIAL",
			"H_SGML_ENTITY",	"H_SGML_COMMENT",	"H_SGML_1ST_PARAM_COMMENT",	"H_SGML_BLOCK_DEFAULT",	"HJ_START",
			"HJ_DEFAULT",		"HJ_COMMENT",	"HJ_COMMENTLINE",	"HJ_COMMENTDOC",	"HJ_NUMBER",
			"HJ_WORD",			"HJ_KEYWORD",	"HJ_DOUBLESTRING",	"HJ_SINGLESTRING",	"HJ_SYMBOLS",
			"HJ_STRINGEOL",		"HJ_REGEX",	"HJA_START",	"HJA_DEFAULT",	"HJA_COMMENT",
			"HJA_COMMENTLINE",	"HJA_COMMENTDOC",	"HJA_NUMBER",	"HJA_WORD",	"HJA_KEYWORD",
			"HJA_DOUBLESTRING",	"HJA_SINGLESTRING",	"HJA_SYMBOLS",	"HJA_STRINGEOL",	"HJA_REGEX",
			"HB_START",			"HB_DEFAULT",	"HB_COMMENTLINE",	"HB_NUMBER",	"HB_WORD",
			"HB_STRING",		"HB_IDENTIFIER",	"HB_STRINGEOL",	"HBA_START",	"HBA_DEFAULT",
			"HBA_COMMENTLINE",	"HBA_NUMBER",	"HBA_WORD",	"HBA_STRING",	"HBA_IDENTIFIER",
			"HBA_STRINGEOL",	"HP_START",	"HP_DEFAULT",	"HP_COMMENTLINE",	"HP_NUMBER",
			"HP_STRING",		"HP_CHARACTER",	"HP_WORD",	"HP_TRIPLE",	"HP_TRIPLEDOUBLE",
			"HP_CLASSNAME",		"HP_DEFNAME",	"HP_OPERATOR",	"HP_IDENTIFIER",	"HPA_START",
			"HPA_DEFAULT",		"HPA_COMMENTLINE",	"HPA_NUMBER",	"HPA_STRING",	"HPA_CHARACTER",
			"HPA_WORD",			"HPA_TRIPLE",	"HPA_TRIPLEDOUBLE",	"HPA_CLASSNAME",	"HPA_DEFNAME",
			"HPA_OPERATOR",		"HPA_IDENTIFIER",	"HPHP_COMPLEX_VARIABLE",	"HPHP_DEFAULT",	"HPHP_HSTRING",
			"HPHP_SIMPLESTRING",	"HPHP_WORD",	"HPHP_NUMBER",	"HPHP_VARIABLE",	"HPHP_COMMENT",
			"HPHP_COMMENTLINE",	"HPHP_HSTRING_VARIABLE",	"HPHP_OPERATOR",	"PL_DEFAULT",	"PL_ERROR",
			"PL_COMMENTLINE",	"PL_POD",	"PL_NUMBER",	"PL_WORD",	"PL_STRING",
			"PL_CHARACTER",		"PL_PUNCTUATION",	"PL_PREPROCESSOR",	"PL_OPERATOR",	"PL_IDENTIFIER",
			"PL_SCALAR",		"PL_ARRAY",	"PL_HASH",	"PL_SYMBOLTABLE",	"PL_REGEX",
			"PL_REGSUBST",		"PL_LONGQUOTE",	"PL_BACKTICKS",	"PL_DATASECTION",	"PL_HERE_DELIM",
			"PL_HERE_Q",		"PL_HERE_QQ",	"PL_HERE_QX",	"PL_STRING_Q",	"PL_STRING_QQ",
			"PL_STRING_QX",		"PL_STRING_QR",	"PL_STRING_QW",	"B_DEFAULT",	"B_COMMENT",
			"B_NUMBER",			"B_KEYWORD",	"B_STRING",	"B_PREPROCESSOR",	"B_OPERATOR",
			"B_IDENTIFIER",		"B_DATE",	"B_STRINGEOL",	"B_KEYWORD2",	"B_KEYWORD3",
			"B_KEYWORD4",		"B_CONSTANT",	"B_ASM",	"B_LABEL",	"B_ERROR",
			"B_HEXNUMBER",		"B_BINNUMBER",	"SV_DEFAULT",	"SV_NUMBER",	"SV_KEYWORD",
			"SV_STRING",		"SV_ERROR",	"SV_OPERATOR",	"SV_IDENTIFIER",	"SV_DATE",
			"SV_KEYWORD2",		"SV_KEYWORD3",	"SV_KEYWORD4",	"SV_KEYWORD5",	"SV_KEYWORD6",
			"MVITEM_DEFAULT",	"MVITEM_ATT1",	"MVITEM_ATT2",	"MVITEM_ATT1VAL1",	"MVITEM_ATT2VAL1",
			"MVITEM_ATT1VAL2",	"MVITEM_ATT2VAL2",	"MVITEM_ATT1VAL1SV1",	"MVITEM_ATT2VAL1SV1",	"MVITEM_ATT1VAL2SV1",
			"MVITEM_ATT2VAL2SV1",	"MVITEM_ATT1VAL1SV2",	"MVITEM_ATT2VAL1SV2",	"MVITEM_ATT1VAL2SV2",	"MVITEM_ATT2VAL2SV2",
			"PROPS_DEFAULT",	"PROPS_COMMENT",	"PROPS_SECTION",	"PROPS_ASSIGNMENT",	"PROPS_DEFVAL",
			"L_DEFAULT",		"L_COMMAND",	"L_TAG",	"L_MATH",	"L_COMMENT",
			"LUA_DEFAULT",		"LUA_COMMENT",	"LUA_COMMENTLINE",	"LUA_COMMENTDOC",	"LUA_NUMBER",
			"LUA_WORD",			"LUA_STRING",	"LUA_CHARACTER",	"LUA_LITERALSTRING",	"LUA_PREPROCESSOR",
			"LUA_OPERATOR",		"LUA_IDENTIFIER",	"LUA_STRINGEOL",	"LUA_WORD2",	"LUA_WORD3",
			"LUA_WORD4",		"LUA_WORD5",	"LUA_WORD6",	"LUA_WORD7",	"LUA_WORD8",
			"ERR_DEFAULT",		"ERR_PYTHON",	"ERR_GCC",	"ERR_MS",	"ERR_CMD",
			"ERR_BORLAND",		"ERR_PERL",	"ERR_NET",	"ERR_LUA",	"ERR_CTAG",
			"ERR_DIFF_CHANGED",	"ERR_DIFF_ADDITION",	"ERR_DIFF_DELETION",	"ERR_DIFF_MESSAGE",	"ERR_PHP",
			"ERR_ELF",			"ERR_IFC",	"ERR_IFORT",	"ERR_ABSF",	"ERR_TIDY",
			"ERR_JAVA_STACK",	"BAT_DEFAULT",	"BAT_COMMENT",	"BAT_WORD",	"BAT_LABEL",
			"BAT_HIDE",			"BAT_COMMAND",	"BAT_IDENTIFIER",	"BAT_OPERATOR",	"MAKE_DEFAULT",
			"MAKE_COMMENT",		"MAKE_PREPROCESSOR",	"MAKE_IDENTIFIER",	"MAKE_OPERATOR",	"MAKE_TARGET",
			"MAKE_IDEOL",		"DIFF_DEFAULT",	"DIFF_COMMENT",	"DIFF_COMMAND",	"DIFF_HEADER",
			"DIFF_POSITION",	"DIFF_DELETED",	"DIFF_ADDED",	"CONF_DEFAULT",	"CONF_COMMENT",
			"CONF_NUMBER",		"CONF_IDENTIFIER",	"CONF_EXTENSION",	"CONF_PARAMETER",	"CONF_STRING",
			"CONF_OPERATOR",	"CONF_IP",	"CONF_DIRECTIVE",	"AVE_DEFAULT",	"AVE_COMMENT",
			"AVE_NUMBER",		"AVE_WORD",	"AVE_STRING",	"AVE_ENUM",	"AVE_STRINGEOL",
			"AVE_IDENTIFIER",	"AVE_OPERATOR",	"AVE_WORD1",	"AVE_WORD2",	"AVE_WORD3",
			"AVE_WORD4",		"AVE_WORD5",	"AVE_WORD6",	"ADA_DEFAULT",	"ADA_WORD",
			"ADA_IDENTIFIER",	"ADA_NUMBER",	"ADA_DELIMITER",	"ADA_CHARACTER",	"ADA_CHARACTEREOL",
			"ADA_STRING",		"ADA_STRINGEOL",	"ADA_LABEL",	"ADA_COMMENTLINE",	"ADA_ILLEGAL",
			"BAAN_DEFAULT",		"BAAN_COMMENT",	"BAAN_COMMENTDOC",	"BAAN_NUMBER",	"BAAN_WORD",
			"BAAN_STRING",		"BAAN_PREPROCESSOR",	"BAAN_OPERATOR",	"BAAN_IDENTIFIER",	"BAAN_STRINGEOL",
			"BAAN_WORD2",		"LISP_DEFAULT",	"LISP_COMMENT",	"LISP_NUMBER",	"LISP_KEYWORD",
			"LISP_STRING",		"LISP_STRINGEOL",	"LISP_IDENTIFIER",	"LISP_OPERATOR",	"EIFFEL_DEFAULT",
			"EIFFEL_COMMENTLINE",	"EIFFEL_NUMBER",	"EIFFEL_WORD",	"EIFFEL_STRING",	"EIFFEL_CHARACTER",
			"EIFFEL_OPERATOR",	"EIFFEL_IDENTIFIER",	"EIFFEL_STRINGEOL",	"NNCRONTAB_DEFAULT",	"NNCRONTAB_COMMENT",
			"NNCRONTAB_TASK",	"NNCRONTAB_SECTION",	"NNCRONTAB_KEYWORD",	"NNCRONTAB_MODIFIER",	"NNCRONTAB_ASTERISK",
			"NNCRONTAB_NUMBER",	"NNCRONTAB_STRING",	"NNCRONTAB_ENVIRONMENT",	"NNCRONTAB_IDENTIFIER",	"FORTH_DEFAULT",
			"FORTH_COMMENT",	"FORTH_COMMENT_ML",	"FORTH_IDENTIFIER",	"FORTH_CONTROL",	"FORTH_KEYWORD",
			"FORTH_DEFWORD",	"FORTH_PREWORD1",	"FORTH_PREWORD2",	"FORTH_NUMBER",	"FORTH_STRING",
			"FORTH_LOCALE",	"MATLAB_DEFAULT",	"MATLAB_COMMENT",	"MATLAB_COMMAND",	"MATLAB_NUMBER",
			"MATLAB_KEYWORD",	"MATLAB_STRING",	"MATLAB_OPERATOR",	"MATLAB_IDENTIFIER",	"MATLAB_DOUBLEQUOTESTRING",
			"SCRIPTOL_DEFAULT",	"SCRIPTOL_WHITE",	"SCRIPTOL_COMMENTLINE",	
			"SCRIPTOL_PERSISTENT",	"SCRIPTOL_CSTYLE",	"SCRIPTOL_COMMENTBLOCK",	"SCRIPTOL_NUMBER",
			"SCRIPTOL_STRING",	"SCRIPTOL_CHARACTER",	"SCRIPTOL_STRINGEOL",	"SCRIPTOL_KEYWORD",
			"SCRIPTOL_OPERATOR",	"SCRIPTOL_IDENTIFIER",	"SCRIPTOL_TRIPLE",	
			"SCRIPTOL_CLASSNAME",	"SCRIPTOL_PREPROCESSOR",	
			"ASM_DEFAULT",	"ASM_COMMENT",	"ASM_NUMBER",
			"ASM_STRING",	"ASM_OPERATOR",	"ASM_IDENTIFIER",	"ASM_CPUINSTRUCTION",	"ASM_MATHINSTRUCTION",
			"ASM_REGISTER",	"ASM_DIRECTIVE",	"ASM_DIRECTIVEOPERAND",	"ASM_COMMENTBLOCK",	"ASM_CHARACTER",
			"ASM_STRINGEOL",	"ASM_EXTINSTRUCTION",	"F_DEFAULT",	"F_COMMENT",	"F_NUMBER",
			"F_STRING1",	"F_STRING2",	"F_STRINGEOL",	"F_OPERATOR",	"F_IDENTIFIER",
			"F_WORD",	"F_WORD2",	"F_WORD3",	"F_PREPROCESSOR",	"F_OPERATOR2",
			"F_LABEL",	"F_CONTINUATION",	"CSS_DEFAULT",	"CSS_TAG",	"CSS_CLASS",
			"CSS_PSEUDOCLASS",	"CSS_UNKNOWN_PSEUDOCLASS",	"CSS_OPERATOR",	"CSS_IDENTIFIER",	"CSS_UNKNOWN_IDENTIFIER",
			"CSS_VALUE",	"CSS_COMMENT",	"CSS_ID",	"CSS_IMPORTANT",	"CSS_DIRECTIVE",
			"CSS_DOUBLESTRING",	"CSS_SINGLESTRING",	"CSS_IDENTIFIER2",	"CSS_ATTRIBUTE",	"POV_DEFAULT",
			"POV_COMMENT",	"POV_COMMENTLINE",	"POV_NUMBER",	"POV_OPERATOR",
			"POV_IDENTIFIER",	"POV_STRING",	"POV_STRINGEOL",	"POV_DIRECTIVE",
			"POV_BADDIRECTIVE",	"POV_WORD2",	"POV_WORD3",	"POV_WORD4",
			"POV_WORD5",	"POV_WORD6",	"POV_WORD7",	"POV_WORD8",	"LOUT_DEFAULT",
			"LOUT_COMMENT",	"LOUT_NUMBER",	"LOUT_WORD",	"LOUT_WORD2",	"LOUT_WORD3",
			"LOUT_WORD4",	"LOUT_STRING",	"LOUT_OPERATOR",	"LOUT_IDENTIFIER",	"LOUT_STRINGEOL",
			"ESCRIPT_DEFAULT",	"ESCRIPT_COMMENT",	"ESCRIPT_COMMENTLINE",	"ESCRIPT_COMMENTDOC",	"ESCRIPT_NUMBER",
			"ESCRIPT_WORD",	"ESCRIPT_STRING",	"ESCRIPT_OPERATOR",	"ESCRIPT_IDENTIFIER",	"ESCRIPT_BRACE",
			"ESCRIPT_WORD2",	"ESCRIPT_WORD3",	"PS_DEFAULT",	"PS_COMMENT",	"PS_DSC_COMMENT",
			"PS_DSC_VALUE",	"PS_NUMBER",	"PS_NAME",	"PS_KEYWORD",	"PS_LITERAL",
			"PS_IMMEVAL",	"PS_PAREN_ARRAY",	"PS_PAREN_DICT",	"PS_PAREN_PROC",	"PS_TEXT",
			"PS_HEXSTRING",	"PS_BASE85STRING",	"PS_BADSTRINGCHAR",	"NSIS_DEFAULT",	"NSIS_COMMENT",
			"NSIS_STRINGDQ",	"NSIS_STRINGLQ",	"NSIS_STRINGRQ",	"NSIS_FUNCTION",	"NSIS_VARIABLE",
			"NSIS_LABEL",	"NSIS_USERDEFINED",	"NSIS_SECTIONDEF",	"NSIS_SUBSECTIONDEF",	"NSIS_IFDEFINEDEF",
			"NSIS_MACRODEF",	"NSIS_STRINGVAR",	"NSIS_NUMBER",	"NSIS_SECTIONGROUP",	"NSIS_PAGEEX",
			"NSIS_FUNCTIONDEF",	"NSIS_COMMENTBOX",	"MMIXAL_LEADWS",	"MMIXAL_COMMENT",	"MMIXAL_LABEL",
			"MMIXAL_OPCODE",	"MMIXAL_OPCODE_PRE",	"MMIXAL_OPCODE_VALID",	"MMIXAL_OPCODE_UNKNOWN",	"MMIXAL_OPCODE_POST",
			"MMIXAL_OPERANDS",	"MMIXAL_NUMBER",	"MMIXAL_REF",	"MMIXAL_CHAR",	"MMIXAL_STRING",
			"MMIXAL_REGISTER",	"MMIXAL_HEX",	"MMIXAL_OPERATOR",	"MMIXAL_SYMBOL",	"MMIXAL_INCLUDE",
			"CLW_DEFAULT",	"CLW_LABEL",	"CLW_COMMENT",	"CLW_STRING",	"CLW_USER_IDENTIFIER",
			"CLW_INTEGER_CONSTANT",	"CLW_REAL_CONSTANT",	"CLW_PICTURE_STRING",	"CLW_KEYWORD",	"CLW_COMPILER_DIRECTIVE",
			"CLW_RUNTIME_EXPRESSIONS",	"CLW_BUILTIN_PROCEDURES_FUNCTION",	"CLW_STRUCTURE_DATA_TYPE",	"CLW_ATTRIBUTE",	"CLW_STANDARD_EQUATE",
			"CLW_ERROR",	"CLW_DEPRECATED",	"LOT_DEFAULT",	"LOT_HEADER",	"LOT_BREAK",
			"LOT_SET",	"LOT_PASS",	"LOT_FAIL",	"LOT_ABORT",	"YAML_DEFAULT",
			"YAML_COMMENT",	"YAML_IDENTIFIER",	"YAML_KEYWORD",	"YAML_NUMBER",	"YAML_REFERENCE",
			"YAML_DOCUMENT",	"YAML_TEXT",	"YAML_ERROR",	"TEX_DEFAULT",	"TEX_SPECIAL",
			"TEX_GROUP",	"TEX_SYMBOL",	"TEX_COMMAND",	"TEX_TEXT",	"METAPOST_DEFAULT",
			"METAPOST_SPECIAL",	"METAPOST_GROUP",	"METAPOST_SYMBOL",	"METAPOST_COMMAND",	"METAPOST_TEXT",
			"METAPOST_EXTRA",	"ERLANG_DEFAULT",	"ERLANG_COMMENT",	"ERLANG_VARIABLE",	"ERLANG_NUMBER",
			"ERLANG_KEYWORD",	"ERLANG_STRING",	"ERLANG_OPERATOR",	"ERLANG_ATOM",	"ERLANG_FUNCTION_NAME",
			"ERLANG_CHARACTER",	"ERLANG_MACRO",	"ERLANG_RECORD",	"ERLANG_SEPARATOR",	"ERLANG_NODE_NAME",
			"ERLANG_UNKNOWN",	"MSSQL_DEFAULT",	"MSSQL_COMMENT",	"MSSQL_LINE_COMMENT",	"MSSQL_NUMBER",
			"MSSQL_STRING",	"MSSQL_OPERATOR",	"MSSQL_IDENTIFIER",	"MSSQL_VARIABLE",	"MSSQL_COLUMN_NAME",
			"MSSQL_STATEMENT",	"MSSQL_DATATYPE",	"MSSQL_SYSTABLE",	"MSSQL_GLOBAL_VARIABLE",	"MSSQL_FUNCTION",
			"MSSQL_STORED_PROCEDURE",	"MSSQL_DEFAULT_PREF_DATATYPE",	"MSSQL_COLUMN_NAME_2",	"V_DEFAULT",	"V_COMMENT",
			"V_COMMENTLINE",	"V_COMMENTLINEBANG",	"V_NUMBER",	"V_WORD",	"V_STRING",
			"V_WORD2",	"V_WORD3",	"V_PREPROCESSOR",	"V_OPERATOR",	"V_IDENTIFIER",
			"V_STRINGEOL",	"V_USER",	"KIX_DEFAULT",	"KIX_COMMENT",	"KIX_STRING1",
			"KIX_STRING2",	"KIX_NUMBER",	"KIX_VAR",	"KIX_MACRO",	"KIX_KEYWORD",
			"KIX_FUNCTIONS",	"KIX_OPERATOR",	"KIX_IDENTIFIER",	"GC_DEFAULT",	"GC_COMMENTLINE",
			"GC_COMMENTBLOCK",	"GC_GLOBAL",	"GC_EVENT",	"GC_ATTRIBUTE",	"GC_CONTROL",
			"GC_COMMAND",	"GC_STRING",	"GC_OPERATOR",	"SN_DEFAULT",	"SN_CODE",
			"SN_COMMENTLINE",	"SN_COMMENTLINEBANG",	"SN_NUMBER",	"SN_WORD",	"SN_STRING",
			"SN_WORD2",	"SN_WORD3",	"SN_PREPROCESSOR",	"SN_OPERATOR",	"SN_IDENTIFIER",
			"SN_STRINGEOL",	"SN_REGEXTAG",	"SN_SIGNAL",	"SN_USER",	"AU3_DEFAULT",
			"AU3_COMMENT",	"AU3_COMMENTBLOCK",	"AU3_NUMBER",	"AU3_FUNCTION",	"AU3_KEYWORD",
			"AU3_MACRO",	"AU3_STRING",	"AU3_OPERATOR",	"AU3_VARIABLE",	"AU3_SENT",
			"AU3_PREPROCESSOR",	"AU3_SPECIAL",	"AU3_EXPAND",	"APDL_DEFAULT",	"APDL_COMMENT",
			"APDL_COMMENTBLOCK",	"APDL_NUMBER",	"APDL_STRING",	"APDL_OPERATOR",	"APDL_WORD",
			"APDL_PROCESSOR",	"APDL_COMMAND",	"APDL_SLASHCOMMAND",	"APDL_STARCOMMAND",	"APDL_ARGUMENT",
			"APDL_FUNCTION",	"SH_DEFAULT",	"SH_ERROR",	"SH_COMMENTLINE",	"SH_NUMBER",
			"SH_WORD",	"SH_STRING",	"SH_CHARACTER",	"SH_OPERATOR",	"SH_IDENTIFIER",
			"SH_SCALAR",	"SH_PARAM",	"SH_BACKTICKS",	"SH_HERE_DELIM",	"SH_HERE_Q",
			"ASN1_DEFAULT",	"ASN1_COMMENT",	"ASN1_IDENTIFIER",	"ASN1_STRING",	"ASN1_OID",
			"ASN1_SCALAR",	"ASN1_KEYWORD",	"ASN1_ATTRIBUTE",	"ASN1_DESCRIPTOR",	"ASN1_TYPE",
			"ASN1_OPERATOR",	"CAML_DEFAULT",	"CAML_IDENTIFIER",	"CAML_TAGNAME",	"CAML_KEYWORD",
			"CAML_KEYWORD2",	"CAML_LINENUM",	"CAML_OPERATOR",	"CAML_NUMBER",	"CAML_CHAR",
			"CAML_STRING",	"CAML_COMMENT",	"CAML_COMMENT1",	"CAML_COMMENT2",	"CAML_COMMENT3",
			"VHDL_DEFAULT",	"VHDL_COMMENT",	"VHDL_COMMENTLINEBANG",	"VHDL_NUMBER",	"VHDL_STRING",
			"VHDL_OPERATOR",	"VHDL_IDENTIFIER",	"VHDL_STRINGEOL",	"VHDL_KEYWORD",	"VHDL_STDOPERATOR",
			"VHDL_ATTRIBUTE",	"VHDL_STDFUNCTION",	"VHDL_STDPACKAGE",	"VHDL_STDTYPE",	"VHDL_USERWORD",
			"HA_DEFAULT",	"HA_IDENTIFIER",	"HA_KEYWORD",	"HA_NUMBER",	"HA_STRING",
			"HA_CHARACTER",	"HA_CLASS",	"HA_MODULE",	"HA_CAPITAL",	"HA_DATA",
			"HA_IMPORT",	"HA_OPERATOR",	"HA_INSTANCE",	"HA_COMMENTLINE",	"HA_COMMENTBLOCK",
			"HA_COMMENTBLOCK2",	"HA_COMMENTBLOCK3",	"PB_DEFAULT",	"PB_COMMENT",	"PB_NUMBER",
			"PB_KEYWORD",	"PB_STRING",	"PB_PREPROCESSOR",	"PB_OPERATOR",	"PB_IDENTIFIER",
			"PB_DATE",	"PB_ERROR",	"PB_SUBROUTINE",	"SCLEX_MVTEXT",	"MVTEXT_STYLE1",	
			"MVTEXT_STYLE2",	"MVTEXT_STYLE3",	"MVTEXT_STYLE4",	"MVTEXT_STYLE5",	"MVTEXT_STYLE6",
			"MVTEXT_STYLE7",	"MVTEXT_STYLE8", "MVTEXT_DEFAULT",

			"SCLEX_TADS3", "SCLEX_REBOL", "SCLEX_SMALLTALK", "SCLEX_FLAGSHIP", "SCLEX_CSOUND", 
			"SCLEX_FREEBASIC", "SCLEX_INNOSETUP", "SCLEX_OPAL", "SCLEX_SPICE", "SCLEX_D", 
			"SCLEX_CMAKE", "SCLEX_GAP", "SCLEX_PLM", "SCLEX_PROGRESS", "SCLEX_ABAQUS", 
			"SCLEX_ASYMPTOTE", "SCLEX_R", "SCLEX_MAGIK", "SCLEX_POWERSHELL", "SCLEX_MYSQL", 
			"SCLEX_PO", 


			"","","","","",
		};

const UINT  GPScintilla::uArrStyles[]={
			SCLEX_CONTAINER,	SCLEX_NULL,	SCLEX_PYTHON,	SCLEX_CPP,	SCLEX_HTML,
			SCLEX_XML,		SCLEX_PERL,	SCLEX_SQL,	SCLEX_VB,	SCLEX_PROPERTIES,
			SCLEX_ERRORLIST,	SCLEX_MAKEFILE,	SCLEX_BATCH,	SCLEX_XCODE,	SCLEX_LATEX,
			SCLEX_LUA,		SCLEX_DIFF,	SCLEX_CONF,	SCLEX_PASCAL,	SCLEX_AVE,
			SCLEX_ADA,		SCLEX_LISP,	SCLEX_RUBY,	SCLEX_EIFFEL,	SCLEX_EIFFELKW,
			SCLEX_TCL,		SCLEX_NNCRONTAB,	SCLEX_BULLANT,	SCLEX_VBSCRIPT,	SCLEX_ASP,
			SCLEX_PHP,		SCLEX_BAAN,	SCLEX_MATLAB,	SCLEX_SCRIPTOL,	SCLEX_ASM,
			SCLEX_CPPNOCASE,	SCLEX_FORTRAN,	SCLEX_F77,	SCLEX_CSS,	SCLEX_POV,
			SCLEX_LOUT	,	SCLEX_ESCRIPT,	SCLEX_PS,	SCLEX_NSIS,	SCLEX_MMIXAL,
			SCLEX_CLW,		SCLEX_CLWNOCASE,	SCLEX_LOT,	SCLEX_YAML,	SCLEX_TEX,
			SCLEX_METAPOST,	SCLEX_POWERBASIC,	SCLEX_FORTH,	SCLEX_ERLANG,	SCLEX_OCTAVE,
			SCLEX_MSSQL,	SCLEX_VERILOG,	SCLEX_KIX,	SCLEX_GUI4CLI,	SCLEX_SPECMAN,
			SCLEX_AU3,		SCLEX_APDL,	SCLEX_BASH,	SCLEX_ASN1,	SCLEX_VHDL,
			SCLEX_CAML,		SCLEX_BLITZBASIC,	SCLEX_PUREBASIC,	SCLEX_HASKELL,	SCLEX_PHPSCRIPT,
			SCLEX_MVITEM,	SCLEX_PB,	SCLEX_SEPVIEW,	SCLEX_C,	SCLEX_RC,
			SCLEX_IDL,		SCLEX_JAVA,	SCLEX_JAVASCRIPT,	SCE_P_DEFAULT,	SCE_P_COMMENTLINE,
			SCE_P_NUMBER,	SCE_P_STRING,	SCE_P_CHARACTER,	SCE_P_WORD,	SCE_P_TRIPLE,
			SCE_P_TRIPLEDOUBLE,	SCE_P_CLASSNAME,	SCE_P_DEFNAME,	SCE_P_OPERATOR,	SCE_P_IDENTIFIER,
			SCE_P_COMMENTBLOCK,	SCE_P_STRINGEOL,	SCE_C_DEFAULT,	SCE_C_COMMENT,	SCE_C_COMMENTLINE,
			SCE_C_COMMENTDOC,	SCE_C_NUMBER,	SCE_C_WORD,	SCE_C_STRING,	SCE_C_CHARACTER,
			SCE_C_UUID,		SCE_C_PREPROCESSOR,	SCE_C_OPERATOR,	SCE_C_IDENTIFIER,	SCE_C_STRINGEOL,
			SCE_C_VERBATIM,	SCE_C_REGEX,	SCE_C_COMMENTLINEDOC,	SCE_C_WORD2,	SCE_C_COMMENTDOCKEYWORD,
			SCE_C_COMMENTDOCKEYWORDERROR,	SCE_C_GLOBALCLASS,	SCE_H_DEFAULT,	SCE_H_TAG,	SCE_H_TAGUNKNOWN,
			SCE_H_ATTRIBUTE,	SCE_H_ATTRIBUTEUNKNOWN,	SCE_H_NUMBER,	SCE_H_DOUBLESTRING,	SCE_H_SINGLESTRING,
			SCE_H_OTHER,	SCE_H_COMMENT,	SCE_H_ENTITY,	SCE_H_TAGEND,	SCE_H_XMLSTART,
			SCE_H_XMLEND,	SCE_H_SCRIPT,	SCE_H_ASP,	SCE_H_ASPAT,	SCE_H_CDATA,
			SCE_H_QUESTION,	SCE_H_VALUE,	SCE_H_XCCOMMENT,	SCE_H_SGML_DEFAULT,	SCE_H_SGML_COMMAND,
			SCE_H_SGML_1ST_PARAM,	SCE_H_SGML_DOUBLESTRING,	SCE_H_SGML_SIMPLESTRING,	SCE_H_SGML_ERROR,	SCE_H_SGML_SPECIAL,
			SCE_H_SGML_ENTITY,	SCE_H_SGML_COMMENT,	SCE_H_SGML_1ST_PARAM_COMMENT,	SCE_H_SGML_BLOCK_DEFAULT,	SCE_HJ_START,
			SCE_HJ_DEFAULT,	SCE_HJ_COMMENT,	SCE_HJ_COMMENTLINE,	SCE_HJ_COMMENTDOC,	SCE_HJ_NUMBER,
			SCE_HJ_WORD,	SCE_HJ_KEYWORD,	SCE_HJ_DOUBLESTRING,	SCE_HJ_SINGLESTRING,	SCE_HJ_SYMBOLS,
			SCE_HJ_STRINGEOL,	SCE_HJ_REGEX,	SCE_HJA_START,	SCE_HJA_DEFAULT,	SCE_HJA_COMMENT,
			SCE_HJA_COMMENTLINE,	SCE_HJA_COMMENTDOC,	SCE_HJA_NUMBER,	SCE_HJA_WORD,	SCE_HJA_KEYWORD,
			SCE_HJA_DOUBLESTRING,	SCE_HJA_SINGLESTRING,	SCE_HJA_SYMBOLS,	SCE_HJA_STRINGEOL,	SCE_HJA_REGEX,
			SCE_HB_START,	SCE_HB_DEFAULT,	SCE_HB_COMMENTLINE,	SCE_HB_NUMBER,	SCE_HB_WORD,
			SCE_HB_STRING,	SCE_HB_IDENTIFIER,	SCE_HB_STRINGEOL,	SCE_HBA_START,	SCE_HBA_DEFAULT,
			SCE_HBA_COMMENTLINE,	SCE_HBA_NUMBER,	SCE_HBA_WORD,	SCE_HBA_STRING,	SCE_HBA_IDENTIFIER,
			SCE_HBA_STRINGEOL,	SCE_HP_START,	SCE_HP_DEFAULT,	SCE_HP_COMMENTLINE,	SCE_HP_NUMBER,
			SCE_HP_STRING,	SCE_HP_CHARACTER,	SCE_HP_WORD,	SCE_HP_TRIPLE,	SCE_HP_TRIPLEDOUBLE,
			SCE_HP_CLASSNAME,	SCE_HP_DEFNAME,	SCE_HP_OPERATOR,	SCE_HP_IDENTIFIER,	SCE_HPA_START,
			SCE_HPA_DEFAULT,	SCE_HPA_COMMENTLINE,	SCE_HPA_NUMBER,	SCE_HPA_STRING,	SCE_HPA_CHARACTER,
			SCE_HPA_WORD,	SCE_HPA_TRIPLE,	SCE_HPA_TRIPLEDOUBLE,	SCE_HPA_CLASSNAME,	SCE_HPA_DEFNAME,
			SCE_HPA_OPERATOR,	SCE_HPA_IDENTIFIER,	SCE_HPHP_COMPLEX_VARIABLE,	SCE_HPHP_DEFAULT,	SCE_HPHP_HSTRING,
			SCE_HPHP_SIMPLESTRING,	SCE_HPHP_WORD,	SCE_HPHP_NUMBER,	SCE_HPHP_VARIABLE,	SCE_HPHP_COMMENT,
			SCE_HPHP_COMMENTLINE,	SCE_HPHP_HSTRING_VARIABLE,	SCE_HPHP_OPERATOR,	SCE_PL_DEFAULT,	SCE_PL_ERROR,
			SCE_PL_COMMENTLINE,	SCE_PL_POD,	SCE_PL_NUMBER,	SCE_PL_WORD,	SCE_PL_STRING,
			SCE_PL_CHARACTER,	SCE_PL_PUNCTUATION,	SCE_PL_PREPROCESSOR,	SCE_PL_OPERATOR,	SCE_PL_IDENTIFIER,
			SCE_PL_SCALAR,	SCE_PL_ARRAY,	SCE_PL_HASH,	SCE_PL_SYMBOLTABLE,	SCE_PL_REGEX,
			SCE_PL_REGSUBST,	SCE_PL_LONGQUOTE,	SCE_PL_BACKTICKS,	SCE_PL_DATASECTION,	SCE_PL_HERE_DELIM,
			SCE_PL_HERE_Q,	SCE_PL_HERE_QQ,	SCE_PL_HERE_QX,	SCE_PL_STRING_Q,	SCE_PL_STRING_QQ,
			SCE_PL_STRING_QX,	SCE_PL_STRING_QR,	SCE_PL_STRING_QW,	SCE_B_DEFAULT,	SCE_B_COMMENT,
			SCE_B_NUMBER,	SCE_B_KEYWORD,	SCE_B_STRING,	SCE_B_PREPROCESSOR,	SCE_B_OPERATOR,
			SCE_B_IDENTIFIER,	SCE_B_DATE,	SCE_B_STRINGEOL,	SCE_B_KEYWORD2,	SCE_B_KEYWORD3,
			SCE_B_KEYWORD4,	SCE_B_CONSTANT,	SCE_B_ASM,	SCE_B_LABEL,	SCE_B_ERROR,
			SCE_B_HEXNUMBER,	SCE_B_BINNUMBER,	SCE_SV_DEFAULT,	SCE_SV_NUMBER,	SCE_SV_KEYWORD,
			SCE_SV_STRING,	SCE_SV_ERROR,	SCE_SV_OPERATOR,	SCE_SV_IDENTIFIER,	SCE_SV_DATE,
			SCE_SV_KEYWORD2,	SCE_SV_KEYWORD3,	SCE_SV_KEYWORD4,	SCE_SV_KEYWORD5,	SCE_SV_KEYWORD6,
			SCE_MVITEM_DEFAULT,	SCE_MVITEM_ATT1,	SCE_MVITEM_ATT2,	SCE_MVITEM_ATT1VAL1,	SCE_MVITEM_ATT2VAL1,
			SCE_MVITEM_ATT1VAL2,	SCE_MVITEM_ATT2VAL2,	SCE_MVITEM_ATT1VAL1SV1,	SCE_MVITEM_ATT2VAL1SV1,	SCE_MVITEM_ATT1VAL2SV1,
			SCE_MVITEM_ATT2VAL2SV1,	SCE_MVITEM_ATT1VAL1SV2,	SCE_MVITEM_ATT2VAL1SV2,	SCE_MVITEM_ATT1VAL2SV2,	SCE_MVITEM_ATT2VAL2SV2,
			SCE_PROPS_DEFAULT,	SCE_PROPS_COMMENT,	SCE_PROPS_SECTION,	SCE_PROPS_ASSIGNMENT,	SCE_PROPS_DEFVAL,
			SCE_L_DEFAULT,	SCE_L_COMMAND,	SCE_L_TAG,	SCE_L_MATH,	SCE_L_COMMENT,
			SCE_LUA_DEFAULT,	SCE_LUA_COMMENT,	SCE_LUA_COMMENTLINE,	SCE_LUA_COMMENTDOC,	SCE_LUA_NUMBER,
			SCE_LUA_WORD,	SCE_LUA_STRING,	SCE_LUA_CHARACTER,	SCE_LUA_LITERALSTRING,	SCE_LUA_PREPROCESSOR,
			SCE_LUA_OPERATOR,	SCE_LUA_IDENTIFIER,	SCE_LUA_STRINGEOL,	SCE_LUA_WORD2,	SCE_LUA_WORD3,
			SCE_LUA_WORD4,	SCE_LUA_WORD5,	SCE_LUA_WORD6,	SCE_LUA_WORD7,	SCE_LUA_WORD8,
			SCE_ERR_DEFAULT,	SCE_ERR_PYTHON,	SCE_ERR_GCC,	SCE_ERR_MS,	SCE_ERR_CMD,
			SCE_ERR_BORLAND,	SCE_ERR_PERL,	SCE_ERR_NET,	SCE_ERR_LUA,	SCE_ERR_CTAG,
			SCE_ERR_DIFF_CHANGED,	SCE_ERR_DIFF_ADDITION,	SCE_ERR_DIFF_DELETION,	SCE_ERR_DIFF_MESSAGE,	SCE_ERR_PHP,
			SCE_ERR_ELF,	SCE_ERR_IFC,	SCE_ERR_IFORT,	SCE_ERR_ABSF,	SCE_ERR_TIDY,
			SCE_ERR_JAVA_STACK,	SCE_BAT_DEFAULT,	SCE_BAT_COMMENT,	SCE_BAT_WORD,	SCE_BAT_LABEL,
			SCE_BAT_HIDE,	SCE_BAT_COMMAND,	SCE_BAT_IDENTIFIER,	SCE_BAT_OPERATOR,	SCE_MAKE_DEFAULT,
			SCE_MAKE_COMMENT,	SCE_MAKE_PREPROCESSOR,	SCE_MAKE_IDENTIFIER,	SCE_MAKE_OPERATOR,	SCE_MAKE_TARGET,
			SCE_MAKE_IDEOL,	SCE_DIFF_DEFAULT,	SCE_DIFF_COMMENT,	SCE_DIFF_COMMAND,	SCE_DIFF_HEADER,
			SCE_DIFF_POSITION,	SCE_DIFF_DELETED,	SCE_DIFF_ADDED,	SCE_CONF_DEFAULT,	SCE_CONF_COMMENT,
			SCE_CONF_NUMBER,	SCE_CONF_IDENTIFIER,	SCE_CONF_EXTENSION,	SCE_CONF_PARAMETER,	SCE_CONF_STRING,
			SCE_CONF_OPERATOR,	SCE_CONF_IP,	SCE_CONF_DIRECTIVE,	SCE_AVE_DEFAULT,	SCE_AVE_COMMENT,
			SCE_AVE_NUMBER,	SCE_AVE_WORD,	SCE_AVE_STRING,	SCE_AVE_ENUM,	SCE_AVE_STRINGEOL,
			SCE_AVE_IDENTIFIER,	SCE_AVE_OPERATOR,	SCE_AVE_WORD1,	SCE_AVE_WORD2,	SCE_AVE_WORD3,
			SCE_AVE_WORD4,	SCE_AVE_WORD5,	SCE_AVE_WORD6,	SCE_ADA_DEFAULT,	SCE_ADA_WORD,
			SCE_ADA_IDENTIFIER,	SCE_ADA_NUMBER,	SCE_ADA_DELIMITER,	SCE_ADA_CHARACTER,	SCE_ADA_CHARACTEREOL,
			SCE_ADA_STRING,	SCE_ADA_STRINGEOL,	SCE_ADA_LABEL,	SCE_ADA_COMMENTLINE,	SCE_ADA_ILLEGAL,
			SCE_BAAN_DEFAULT,	SCE_BAAN_COMMENT,	SCE_BAAN_COMMENTDOC,	SCE_BAAN_NUMBER,	SCE_BAAN_WORD,
			SCE_BAAN_STRING,	SCE_BAAN_PREPROCESSOR,	SCE_BAAN_OPERATOR,	SCE_BAAN_IDENTIFIER,	SCE_BAAN_STRINGEOL,
			SCE_BAAN_WORD2,	SCE_LISP_DEFAULT,	SCE_LISP_COMMENT,	SCE_LISP_NUMBER,	SCE_LISP_KEYWORD,
			SCE_LISP_STRING,	SCE_LISP_STRINGEOL,	SCE_LISP_IDENTIFIER,	SCE_LISP_OPERATOR,	SCE_EIFFEL_DEFAULT,
			SCE_EIFFEL_COMMENTLINE,	SCE_EIFFEL_NUMBER,	SCE_EIFFEL_WORD,	SCE_EIFFEL_STRING,	SCE_EIFFEL_CHARACTER,
			SCE_EIFFEL_OPERATOR,	SCE_EIFFEL_IDENTIFIER,	SCE_EIFFEL_STRINGEOL,	SCE_NNCRONTAB_DEFAULT,	SCE_NNCRONTAB_COMMENT,
			SCE_NNCRONTAB_TASK,	SCE_NNCRONTAB_SECTION,	SCE_NNCRONTAB_KEYWORD,	SCE_NNCRONTAB_MODIFIER,	SCE_NNCRONTAB_ASTERISK,
			SCE_NNCRONTAB_NUMBER,	SCE_NNCRONTAB_STRING,	SCE_NNCRONTAB_ENVIRONMENT,	SCE_NNCRONTAB_IDENTIFIER,	SCE_FORTH_DEFAULT,
			SCE_FORTH_COMMENT,	SCE_FORTH_COMMENT_ML,	SCE_FORTH_IDENTIFIER,	SCE_FORTH_CONTROL,	SCE_FORTH_KEYWORD,
			SCE_FORTH_DEFWORD,	SCE_FORTH_PREWORD1,	SCE_FORTH_PREWORD2,	SCE_FORTH_NUMBER,	SCE_FORTH_STRING,
			SCE_FORTH_LOCALE,	SCE_MATLAB_DEFAULT,	SCE_MATLAB_COMMENT,	SCE_MATLAB_COMMAND,	SCE_MATLAB_NUMBER,
			SCE_MATLAB_KEYWORD,	SCE_MATLAB_STRING,	SCE_MATLAB_OPERATOR,	SCE_MATLAB_IDENTIFIER,	SCE_MATLAB_DOUBLEQUOTESTRING,
			SCE_SCRIPTOL_DEFAULT,	SCE_SCRIPTOL_WHITE,	SCE_SCRIPTOL_COMMENTLINE,	
			SCE_SCRIPTOL_PERSISTENT,	SCE_SCRIPTOL_CSTYLE,	SCE_SCRIPTOL_COMMENTBLOCK,	SCE_SCRIPTOL_NUMBER,
			SCE_SCRIPTOL_STRING,	SCE_SCRIPTOL_CHARACTER,	SCE_SCRIPTOL_STRINGEOL,	SCE_SCRIPTOL_KEYWORD,
			SCE_SCRIPTOL_OPERATOR,	SCE_SCRIPTOL_IDENTIFIER,	SCE_SCRIPTOL_TRIPLE,
			SCE_SCRIPTOL_CLASSNAME,	SCE_SCRIPTOL_PREPROCESSOR,	
			SCE_ASM_DEFAULT,	SCE_ASM_COMMENT,	SCE_ASM_NUMBER,
			SCE_ASM_STRING,	SCE_ASM_OPERATOR,	SCE_ASM_IDENTIFIER,	SCE_ASM_CPUINSTRUCTION,	SCE_ASM_MATHINSTRUCTION,
			SCE_ASM_REGISTER,	SCE_ASM_DIRECTIVE,	SCE_ASM_DIRECTIVEOPERAND,	SCE_ASM_COMMENTBLOCK,	SCE_ASM_CHARACTER,
			SCE_ASM_STRINGEOL,	SCE_ASM_EXTINSTRUCTION,	SCE_F_DEFAULT,	SCE_F_COMMENT,	SCE_F_NUMBER,
			SCE_F_STRING1,	SCE_F_STRING2,	SCE_F_STRINGEOL,	SCE_F_OPERATOR,	SCE_F_IDENTIFIER,
			SCE_F_WORD,		SCE_F_WORD2,	SCE_F_WORD3,	SCE_F_PREPROCESSOR,	SCE_F_OPERATOR2,
			SCE_F_LABEL,	SCE_F_CONTINUATION,	SCE_CSS_DEFAULT,	SCE_CSS_TAG,	SCE_CSS_CLASS,
			SCE_CSS_PSEUDOCLASS,	SCE_CSS_UNKNOWN_PSEUDOCLASS,	SCE_CSS_OPERATOR,	SCE_CSS_IDENTIFIER,	SCE_CSS_UNKNOWN_IDENTIFIER,
			SCE_CSS_VALUE,	SCE_CSS_COMMENT,	SCE_CSS_ID,	SCE_CSS_IMPORTANT,	SCE_CSS_DIRECTIVE,
			SCE_CSS_DOUBLESTRING,	SCE_CSS_SINGLESTRING,	SCE_CSS_IDENTIFIER2,	SCE_CSS_ATTRIBUTE,	SCE_POV_DEFAULT,
			SCE_POV_COMMENT,	SCE_POV_COMMENTLINE,	SCE_POV_NUMBER,	SCE_POV_OPERATOR,
			SCE_POV_IDENTIFIER,	SCE_POV_STRING,	SCE_POV_STRINGEOL,	SCE_POV_DIRECTIVE,
			SCE_POV_BADDIRECTIVE,	SCE_POV_WORD2,	SCE_POV_WORD3,	SCE_POV_WORD4,
			SCE_POV_WORD5,	SCE_POV_WORD6,	SCE_POV_WORD7,	SCE_POV_WORD8,	SCE_LOUT_DEFAULT,
			SCE_LOUT_COMMENT,	SCE_LOUT_NUMBER,	SCE_LOUT_WORD,	SCE_LOUT_WORD2,	SCE_LOUT_WORD3,
			SCE_LOUT_WORD4,	SCE_LOUT_STRING,	SCE_LOUT_OPERATOR,	SCE_LOUT_IDENTIFIER,	SCE_LOUT_STRINGEOL,
			SCE_ESCRIPT_DEFAULT,	SCE_ESCRIPT_COMMENT,	SCE_ESCRIPT_COMMENTLINE,	SCE_ESCRIPT_COMMENTDOC,	SCE_ESCRIPT_NUMBER,
			SCE_ESCRIPT_WORD,	SCE_ESCRIPT_STRING,	SCE_ESCRIPT_OPERATOR,	SCE_ESCRIPT_IDENTIFIER,	SCE_ESCRIPT_BRACE,
			SCE_ESCRIPT_WORD2,	SCE_ESCRIPT_WORD3,	SCE_PS_DEFAULT,	SCE_PS_COMMENT,	SCE_PS_DSC_COMMENT,
			SCE_PS_DSC_VALUE,	SCE_PS_NUMBER,	SCE_PS_NAME,	SCE_PS_KEYWORD,	SCE_PS_LITERAL,
			SCE_PS_IMMEVAL,	SCE_PS_PAREN_ARRAY,	SCE_PS_PAREN_DICT,	SCE_PS_PAREN_PROC,	SCE_PS_TEXT,
			SCE_PS_HEXSTRING,	SCE_PS_BASE85STRING,	SCE_PS_BADSTRINGCHAR,	SCE_NSIS_DEFAULT,	SCE_NSIS_COMMENT,
			SCE_NSIS_STRINGDQ,	SCE_NSIS_STRINGLQ,	SCE_NSIS_STRINGRQ,	SCE_NSIS_FUNCTION,	SCE_NSIS_VARIABLE,
			SCE_NSIS_LABEL,	SCE_NSIS_USERDEFINED,	SCE_NSIS_SECTIONDEF,	SCE_NSIS_SUBSECTIONDEF,	SCE_NSIS_IFDEFINEDEF,
			SCE_NSIS_MACRODEF,	SCE_NSIS_STRINGVAR,	SCE_NSIS_NUMBER,	SCE_NSIS_SECTIONGROUP,	SCE_NSIS_PAGEEX,
			SCE_NSIS_FUNCTIONDEF,	SCE_NSIS_COMMENTBOX,	SCE_MMIXAL_LEADWS,	SCE_MMIXAL_COMMENT,	SCE_MMIXAL_LABEL,
			SCE_MMIXAL_OPCODE,	SCE_MMIXAL_OPCODE_PRE,	SCE_MMIXAL_OPCODE_VALID,	SCE_MMIXAL_OPCODE_UNKNOWN,	SCE_MMIXAL_OPCODE_POST,
			SCE_MMIXAL_OPERANDS,	SCE_MMIXAL_NUMBER,	SCE_MMIXAL_REF,	SCE_MMIXAL_CHAR,	SCE_MMIXAL_STRING,
			SCE_MMIXAL_REGISTER,	SCE_MMIXAL_HEX,	SCE_MMIXAL_OPERATOR,	SCE_MMIXAL_SYMBOL,	SCE_MMIXAL_INCLUDE,
			SCE_CLW_DEFAULT,	SCE_CLW_LABEL,	SCE_CLW_COMMENT,	SCE_CLW_STRING,	SCE_CLW_USER_IDENTIFIER,
			SCE_CLW_INTEGER_CONSTANT,	SCE_CLW_REAL_CONSTANT,	SCE_CLW_PICTURE_STRING,	SCE_CLW_KEYWORD,	SCE_CLW_COMPILER_DIRECTIVE,
			SCE_CLW_RUNTIME_EXPRESSIONS,	SCE_CLW_BUILTIN_PROCEDURES_FUNCTION,	SCE_CLW_STRUCTURE_DATA_TYPE,	SCE_CLW_ATTRIBUTE,	SCE_CLW_STANDARD_EQUATE,
			SCE_CLW_ERROR,	SCE_CLW_DEPRECATED,	SCE_LOT_DEFAULT,	SCE_LOT_HEADER,	SCE_LOT_BREAK,
			SCE_LOT_SET,	SCE_LOT_PASS,	SCE_LOT_FAIL,	SCE_LOT_ABORT,	SCE_YAML_DEFAULT,
			SCE_YAML_COMMENT,	SCE_YAML_IDENTIFIER,	SCE_YAML_KEYWORD,	SCE_YAML_NUMBER,	SCE_YAML_REFERENCE,
			SCE_YAML_DOCUMENT,	SCE_YAML_TEXT,	SCE_YAML_ERROR,	SCE_TEX_DEFAULT,	SCE_TEX_SPECIAL,
			SCE_TEX_GROUP,	SCE_TEX_SYMBOL,	SCE_TEX_COMMAND,	SCE_TEX_TEXT,	SCE_METAPOST_DEFAULT,
			SCE_METAPOST_SPECIAL,	SCE_METAPOST_GROUP,	SCE_METAPOST_SYMBOL,	SCE_METAPOST_COMMAND,	SCE_METAPOST_TEXT,
			SCE_METAPOST_EXTRA,	SCE_ERLANG_DEFAULT,	SCE_ERLANG_COMMENT,	SCE_ERLANG_VARIABLE,	SCE_ERLANG_NUMBER,
			SCE_ERLANG_KEYWORD,	SCE_ERLANG_STRING,	SCE_ERLANG_OPERATOR,	SCE_ERLANG_ATOM,	SCE_ERLANG_FUNCTION_NAME,
			SCE_ERLANG_CHARACTER,	SCE_ERLANG_MACRO,	SCE_ERLANG_RECORD,	SCE_ERLANG_SEPARATOR,	SCE_ERLANG_NODE_NAME,
			SCE_ERLANG_UNKNOWN,	SCE_MSSQL_DEFAULT,	SCE_MSSQL_COMMENT,	SCE_MSSQL_LINE_COMMENT,	SCE_MSSQL_NUMBER,
			SCE_MSSQL_STRING,	SCE_MSSQL_OPERATOR,	SCE_MSSQL_IDENTIFIER,	SCE_MSSQL_VARIABLE,	SCE_MSSQL_COLUMN_NAME,
			SCE_MSSQL_STATEMENT,	SCE_MSSQL_DATATYPE,	SCE_MSSQL_SYSTABLE,	SCE_MSSQL_GLOBAL_VARIABLE,	SCE_MSSQL_FUNCTION,
			SCE_MSSQL_STORED_PROCEDURE,	SCE_MSSQL_DEFAULT_PREF_DATATYPE,	SCE_MSSQL_COLUMN_NAME_2,	SCE_V_DEFAULT,	SCE_V_COMMENT,
			SCE_V_COMMENTLINE,	SCE_V_COMMENTLINEBANG,	SCE_V_NUMBER,	SCE_V_WORD,	SCE_V_STRING,
			SCE_V_WORD2,	SCE_V_WORD3,	SCE_V_PREPROCESSOR,	SCE_V_OPERATOR,	SCE_V_IDENTIFIER,
			SCE_V_STRINGEOL,	SCE_V_USER,	SCE_KIX_DEFAULT,	SCE_KIX_COMMENT,	SCE_KIX_STRING1,
			SCE_KIX_STRING2,	SCE_KIX_NUMBER,	SCE_KIX_VAR,	SCE_KIX_MACRO,	SCE_KIX_KEYWORD,
			SCE_KIX_FUNCTIONS,	SCE_KIX_OPERATOR,	SCE_KIX_IDENTIFIER,	SCE_GC_DEFAULT,	SCE_GC_COMMENTLINE,
			SCE_GC_COMMENTBLOCK,	SCE_GC_GLOBAL,	SCE_GC_EVENT,	SCE_GC_ATTRIBUTE,	SCE_GC_CONTROL,
			SCE_GC_COMMAND,	SCE_GC_STRING,	SCE_GC_OPERATOR,	SCE_SN_DEFAULT,	SCE_SN_CODE,
			SCE_SN_COMMENTLINE,	SCE_SN_COMMENTLINEBANG,	SCE_SN_NUMBER,	SCE_SN_WORD,	SCE_SN_STRING,
			SCE_SN_WORD2,	SCE_SN_WORD3,	SCE_SN_PREPROCESSOR,	SCE_SN_OPERATOR,	SCE_SN_IDENTIFIER,
			SCE_SN_STRINGEOL,	SCE_SN_REGEXTAG,	SCE_SN_SIGNAL,	SCE_SN_USER,	SCE_AU3_DEFAULT,
			SCE_AU3_COMMENT,	SCE_AU3_COMMENTBLOCK,	SCE_AU3_NUMBER,	SCE_AU3_FUNCTION,	SCE_AU3_KEYWORD,
			SCE_AU3_MACRO,	SCE_AU3_STRING,	SCE_AU3_OPERATOR,	SCE_AU3_VARIABLE,	SCE_AU3_SENT,
			SCE_AU3_PREPROCESSOR,	SCE_AU3_SPECIAL,	SCE_AU3_EXPAND,	SCE_APDL_DEFAULT,	SCE_APDL_COMMENT,
			SCE_APDL_COMMENTBLOCK,	SCE_APDL_NUMBER,	SCE_APDL_STRING,	SCE_APDL_OPERATOR,	SCE_APDL_WORD,
			SCE_APDL_PROCESSOR,	SCE_APDL_COMMAND,	SCE_APDL_SLASHCOMMAND,	SCE_APDL_STARCOMMAND,	SCE_APDL_ARGUMENT,
			SCE_APDL_FUNCTION,	SCE_SH_DEFAULT,	SCE_SH_ERROR,	SCE_SH_COMMENTLINE,	SCE_SH_NUMBER,
			SCE_SH_WORD,	SCE_SH_STRING,	SCE_SH_CHARACTER,	SCE_SH_OPERATOR,	SCE_SH_IDENTIFIER,
			SCE_SH_SCALAR,	SCE_SH_PARAM,	SCE_SH_BACKTICKS,	SCE_SH_HERE_DELIM,	SCE_SH_HERE_Q,
			SCE_ASN1_DEFAULT,	SCE_ASN1_COMMENT,	SCE_ASN1_IDENTIFIER,	SCE_ASN1_STRING,	SCE_ASN1_OID,
			SCE_ASN1_SCALAR,	SCE_ASN1_KEYWORD,	SCE_ASN1_ATTRIBUTE,	SCE_ASN1_DESCRIPTOR,	SCE_ASN1_TYPE,
			SCE_ASN1_OPERATOR,	SCE_CAML_DEFAULT,	SCE_CAML_IDENTIFIER,	SCE_CAML_TAGNAME,	SCE_CAML_KEYWORD,
			SCE_CAML_KEYWORD2,	SCE_CAML_LINENUM,	SCE_CAML_OPERATOR,	SCE_CAML_NUMBER,	SCE_CAML_CHAR,
			SCE_CAML_STRING,	SCE_CAML_COMMENT,	SCE_CAML_COMMENT1,	SCE_CAML_COMMENT2,	SCE_CAML_COMMENT3,
			SCE_VHDL_DEFAULT,	SCE_VHDL_COMMENT,	SCE_VHDL_COMMENTLINEBANG,	SCE_VHDL_NUMBER,	SCE_VHDL_STRING,
			SCE_VHDL_OPERATOR,	SCE_VHDL_IDENTIFIER,	SCE_VHDL_STRINGEOL,	SCE_VHDL_KEYWORD,	SCE_VHDL_STDOPERATOR,
			SCE_VHDL_ATTRIBUTE,	SCE_VHDL_STDFUNCTION,	SCE_VHDL_STDPACKAGE,	SCE_VHDL_STDTYPE,	SCE_VHDL_USERWORD,
			SCE_HA_DEFAULT,	SCE_HA_IDENTIFIER,	SCE_HA_KEYWORD,	SCE_HA_NUMBER,	SCE_HA_STRING,
			SCE_HA_CHARACTER,	SCE_HA_CLASS,	SCE_HA_MODULE,	SCE_HA_CAPITAL,	SCE_HA_DATA,
			SCE_HA_IMPORT,	SCE_HA_OPERATOR,	SCE_HA_INSTANCE,	SCE_HA_COMMENTLINE,	SCE_HA_COMMENTBLOCK,
			SCE_HA_COMMENTBLOCK2,	SCE_HA_COMMENTBLOCK3,	SCE_PB_DEFAULT,	SCE_PB_COMMENT,	SCE_PB_NUMBER,
			SCE_PB_KEYWORD,	SCE_PB_STRING,	SCE_PB_PREPROCESSOR,	SCE_PB_OPERATOR,	SCE_PB_IDENTIFIER,
			SCE_PB_DATE,	SCE_PB_ERROR,	SCE_PB_SUBROUTINE,	SCLEX_MVTEXT,	SCE_MVTEXT_STYLE1,
			SCE_MVTEXT_STYLE2,	SCE_MVTEXT_STYLE3,	SCE_MVTEXT_STYLE4,	SCE_MVTEXT_STYLE5,	SCE_MVTEXT_STYLE6,
			SCE_MVTEXT_STYLE7,	SCE_MVTEXT_STYLE8,	SCE_MVTEXT_DEFAULT,	
			
			SCLEX_TADS3, SCLEX_REBOL, SCLEX_SMALLTALK, SCLEX_FLAGSHIP, SCLEX_CSOUND,
			SCLEX_FREEBASIC, SCLEX_INNOSETUP, SCLEX_OPAL, SCLEX_SPICE, SCLEX_D,
			SCLEX_CMAKE, SCLEX_GAP, SCLEX_PLM, SCLEX_PROGRESS, SCLEX_ABAQUS, 
			SCLEX_ASYMPTOTE, SCLEX_R, SCLEX_MAGIK, SCLEX_POWERSHELL, SCLEX_MYSQL,
			SCLEX_PO,
		
			0,0,0,0,0,
		};

/*
#define INDIC0_MASK 0x20
#define INDIC1_MASK 0x40
#define INDIC2_MASK 0x80
#define INDICS_MASK 0xE0
#define MARKER_MAX 31
#define SC_LASTSTEPINUNDOREDO 0x100
#define SC_MODEVENTMASKALL 0xF77
#define SC_PERFORMED_REDO 0x40
#define SC_PERFORMED_UNDO 0x20
#define SC_PERFORMED_USER 0x10
#define SC_TIME_FOREVER 10000000
#define SCI_ADDREFDOCUMENT 2376
/////////////////////////////////////////////#define SCI_ADDSTYLEDTEXT 2002
#define SCI_CREATEDOCUMENT 2375
/////////////////////////////////////////////////#define SCI_FORMATRANGE 2151
///////////////////////////////////////////////#define SCI_GETDOCPOINTER 2357
////////////////////////////////////////////////#define SCI_GETMODEVENTMASK 2378
///////////////////////////////////////////////#define SCI_GETSTYLEDTEXT 2015
#define SCI_LEXER_START 4000
#define SCI_OPTIONAL_START 3000
#define SCI_RELEASEDOCUMENT 2377
/////////////////////////////////////////////////#define SCI_SETDOCPOINTER 2358
/////////////////////////////////////////////////#define SCI_SETMODEVENTMASK 2359
*/
GPScintilla::GPScintilla(UINT iUnitId)
{
	PseudoConstructor(iUnitId);
	EditorPrintSettings.LoadSettings();
}

GPScintilla::GPScintilla()
{
	PseudoConstructor(-1);
}

void GPScintilla::PseudoConstructor(UINT iUnitId)
{
	m_bAutoFocus=FALSE;
	m_DOflags=0;
	m_PBdelim1=new char [256];
	strcpy(m_PBdelim1,"(){}[]<> .,;:'\"/*-+`~|!#$%^&=");

	m_autocList=NULL;
	m_AutoIndentFlag=0;
	m_ProcHK=1;
	m_bTrackMousePos=FALSE;
	CharObjId=lastSelPos=LineObjId=ColumnObjId=-1;
	m_ArrLockKey=NULL;
	m_LockKeysFlag=0;
	m_FileNameLK="LockKeys.txt";
	m_CurMarkerType=0;
	if (m_FindDlg==NULL || m_FindDlg->m_hWnd==NULL)
	{
		if (m_FindDlg==NULL) m_FindDlg=new CDlgGPScintillaFind;
		if (GPC.m_View)      m_FindDlg->Create(IDD_DLGSCFIND,GPC.m_View);
	}

	if (m_FindDlg && m_FindDlg->m_hWnd) m_FindDlg->AddRef(this);


	SepViewKeyWords=SepViewKeyWordsDef;
	m_DirectInputFlag=0;
	Scincillafn=NULL;
	Scincillaptr=NULL;
	InitFnPtr=TRUE;
	m_AutoSaveFlag=0;

	m_EnableContextMenu=1;
	referGPU=NULL;
	UnitId=iUnitId;
}


GPScintilla::~GPScintilla()
{
	if (m_PBdelim1) delete[] m_PBdelim1;
	m_PBdelim1=NULL;

	if (m_autocList) delete[] m_autocList;
	m_autocList=NULL;

	if (m_ArrLockKey) delete m_ArrLockKey;
	m_ArrLockKey=NULL;

	if (m_FindDlg)
	{
		if (m_FindDlg->DelRef(this)==0)
		{
			m_FindDlg->DestroyWindow();
			delete m_FindDlg;
			m_FindDlg=NULL;
		}
	}
}



BEGIN_MESSAGE_MAP(GPScintilla, CWnd)
	//{{AFX_MSG_MAP(GPScintilla)
	ON_WM_CLOSE()
	ON_WM_SIZING()
	ON_WM_NCHITTEST()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CHAR()
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
	ON_WM_MOUSEACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GPScintilla

/////////////////////////////////////////////////////////////////////////////
// GPScintilla message handlers
UINT GPScintilla::DoMethod(const char *iStr, char *oStr)
{
	char met[150];
	strncpy(met,iStr,145);
	met[145]=0;
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc=0;
	int retint=-123456; 

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

	int atoipos=atoi(pos);
	if (nfunc<250)
	{
		if (nfunc<126)
		{
			if (nfunc<64)
			{
				switch(nfunc)
				{
				case 0: /*SetViewEOL*/
					retint=ScMethod(SCI_SETVIEWEOL,atoipos,0);
					break;
				case 1: /*GetViewEOL*/
					retint=ScMethod(SCI_GETVIEWEOL,0,0);
					break;
				case 2: /*SetZoom*/
					retint=ScMethod(SCI_SETZOOM,atoipos,0);
					break;
				case 3: /*GetZoom*/
					retint=ScMethod(SCI_GETZOOM,0,0);
					break;
				case 4: /*AddText*/
				case 5: /*AppendText*/		
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						Replace1To13(pos333);

						switch(nfunc)
						{
						case 4: /*AddText*/
							retint=ScMethod(SCI_ADDTEXT,(int)strlen(pos333),(int)pos333);
							break;
						case 5: /*AppendText*/		
							retint=ScMethod(SCI_APPENDTEXT,(int)strlen(pos333),(int)pos333);
							break;
						}
						delete[] pos333;
					}
					break;				
				case 6: /*KeybAction*/
					{
						retint=-1;
						CString kb=ExtractField(pos,1,",");
						if (kb!="")
						{
							UINT nRepeat=atoi(ExtractField(pos,2,","));
							if (nRepeat==0 || nRepeat>0x10000) nRepeat=1;
							DWORD met333=atoi(pos);
							UINT i=0;
							kb.MakeUpper();
							for(i=0;*GPScintilla::cArrKeybMethods[i] && met333==0;i++)
								if (strcmp(kb,GPScintilla::cArrKeybMethods[i])==0)
									met333=GPScintilla::uArrKeybMethods[i];

							if (met333)
								for(i=0;i<nRepeat;i++)
									retint=ScMethod(met333,0,0);
						}
					}
					break;				
				case 7: /*AssignCmdKey*/
					retint=-1;
					if (*pos)
					{
						CString cmd=ExtractField(pos,1,",");
						CString key=ExtractField(pos,2,",");
						cmd.MakeUpper();
						key.MakeUpper();
						DWORD dcmd=atoi(cmd),dkey=atoi(key);
						if (dcmd==0)
						{
							UINT i;
							for(i=0;*GPScintilla::cArrKeybMethods[i] && dcmd==0;i++)
								if (GPScintilla::cArrKeybMethods[i]==cmd)
									dcmd=GPScintilla::uArrKeybMethods[i];

							for(i=0;i<GPScintilla::uN0Methods && dcmd==0;i++)
								if (GPScintilla::cArr0Methods[i]==cmd)
									dcmd=GPScintilla::uArr0Methods[i];
						}

						if (dcmd)
						{
							if (dkey==0)
							{
								UINT i;
								for(i=0;i<GPScintilla::uNKeybDef-3;i++)
									if (key.Find(GPScintilla::cArrKeybDef[i])>=0)
										dkey|=GPScintilla::uArrKeybDef[i];

								for(;i<GPScintilla::uNKeybDef;i++)
									if (key.Find(GPScintilla::cArrKeybDef[i])>=0)
										dkey|=(GPScintilla::uArrKeybDef[i]*0x10000);

								for(i=0;i<GP_N_TYPE_HOTKEY;i++)
									if (key.Find(GP_HotKey:: aVKName[i])>=0)
										dkey|=GP_HotKey:: aVKUINT[i];
							}

							if (dkey)
								retint=ScMethod(SCI_ASSIGNCMDKEY,dkey,dcmd);
						}
					}
					break;	
				case 8: /*ClearAllCmdKeys*/
					retint=ScMethod(SCI_CLEARALLCMDKEYS,0,0);
					break;	
				case 9: /*ClearCmdKey*/
					retint=-1;
					if (*pos)
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						_strupr(pos333);
						DWORD dkey=atoi(pos333);
						if (dkey==0)
						{
							UINT i;
							for(i=0;i<GPScintilla::uNKeybDef-3;i++)
								if (strstr(pos333,GPScintilla::cArrKeybDef[i]))
									dkey|=GPScintilla::uArrKeybDef[i];

							for(;i<GPScintilla::uNKeybDef;i++)
								if (strstr(pos333,GPScintilla::cArrKeybDef[i]))
									dkey|=(GPScintilla::uArrKeybDef[i]*0x10000);

							for(i=0;i<GP_N_TYPE_HOTKEY;i++)
								if (strstr(pos333,GP_HotKey:: aVKName[i]))
									dkey|=GP_HotKey:: aVKUINT[i];
						}

						if (dkey)
							retint=ScMethod(SCI_CLEARCMDKEY,dkey,0);
						delete[] pos333;
					}
					break;	
				case 10: /*Cut*/
					retint=ScMethod(SCI_CUT,0,0);
					break;	
				case 11: /*Copy*/
					retint=ScMethod(SCI_COPY,0,0);
					break;	
				case 12: /*Paste*/
					retint=ScMethod(SCI_PASTE,0,0);
					break;	
				case 13: /*Clear*/
					retint=ScMethod(SCI_CLEAR,0,0);
					break;	
				case 14: /*CanPaste*/
					retint=ScMethod(SCI_CANPASTE,0,0);
					break;	
				case 15: /*CopyRange*/
					{
						int start=0,end=0;
						m_LastScanf=sscanf(pos,"%d,%d",&start,&end);
						retint=ScMethod(SCI_COPYRANGE,start,end);
					}
					break;	
				case 16: /*CopyText*/
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						Replace1To13(pos333);
						retint=ScMethod(SCI_COPYTEXT,(int)strlen(pos333),(int)pos333);
						delete[] pos333;
					}
					break;	
				case 17: /*ClearAll*/
					retint=ScMethod(SCI_CLEARALL,0,0);
					break;	
				case 18: /*SetOvertype*/
					retint=ScMethod(SCI_SETOVERTYPE,atoipos,0);
					break;	
				case 19: /*GetOvertype*/
					retint=ScMethod(SCI_GETOVERTYPE,0,0);
					break;	
				case 20: /*GetText*/
					if (oStr)
					{
						if (atoipos<=0)
							atoipos=ScMethod(SCI_GETTEXTLENGTH,0,0);

						if (atoipos<=0) atoipos=1;
						atoipos++;
						if (atoipos>TMP_STR_OUT_LEN-1000) atoipos=TMP_STR_OUT_LEN-1000;
						ScMethod(SCI_GETTEXT,atoipos,(int)oStr);
					}
					break;	
				case 21: /*GetTextLength*/
					retint=ScMethod(SCI_GETTEXTLENGTH,0,0);
					break;	
				case 22: /*GetLength*/
					retint=ScMethod(SCI_GETLENGTH,0,0);
					break;	
				case 23: /*SetText*/
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						Replace1To13(pos333);
						retint=ScMethod(SCI_SETTEXT,(int)strlen(pos333),(int)pos333);
						delete[] pos333;
					}
					break;	
				case 24: /*SetSavePoint*/
					retint=ScMethod(SCI_SETSAVEPOINT,0,0);
					break;	
				case 25: /*GetModify*/
					retint=ScMethod(SCI_GETMODIFY,0,0);
					break;	
				case 26: /*GetLine*/
					if (oStr)
					{
						if (atoipos<0 || *pos==0)	atoipos=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
						int nChars=ScMethod(SCI_GETLINE,atoipos,(int)oStr);
						if (nChars>=0) 
						{
							oStr[nChars]=0;
							while(nChars>0 && (oStr[nChars-1]==13 || oStr[nChars-1]==10))
								oStr[--nChars]=0;
						}
						else *oStr=0;
					}
					break;	
				case 27: /*ReplaceSel*/
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						Replace1To13(pos333);
						retint=ScMethod(SCI_REPLACESEL,0,(int)pos333);
						delete[] pos333;
					}
					break;	
				case 28: /*SetReadonly*/
					retint=ScMethod(SCI_SETREADONLY,atoipos,0);
					break;	
				case 29: /*GetReadonly*/
					retint=ScMethod(SCI_GETREADONLY,0,0);
					break;	
				case 30: /*GetTextRange*/
					if (oStr)
					{
						TextRange tr={0};
						tr.lpstrText=oStr;
						m_LastScanf=sscanf(pos,"%d,%d",&tr.chrg.cpMin,&tr.chrg.cpMax);
						int nChars=ScMethod(SCI_GETTEXTRANGE,0,(int)&tr);
						if (nChars>=0) oStr[nChars]=0;
					}
					break;	
				case 31: /*InsertText*/
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						char *pos1=strchr(pos333,',');
						if (pos1) pos1++;
						else pos1="";
						Replace1To13(pos1);
						retint=ScMethod(SCI_INSERTTEXT,atoipos,(int)pos1);
						delete[] pos333;
					}
					break;				
				case 32: /*ClearDocumentStyle*/
					retint=ScMethod(SCI_CLEARDOCUMENTSTYLE,0,0);
					break;	
				case 33: /*GetCharAt*/
					retint=ScMethod(SCI_GETCHARAT,atoipos,0);
					break;	
				case 34: /*GetStyleAt*/
					retint=ScMethod(SCI_GETSTYLEAT,atoipos,0);
					break;	
				case 35: /*SetStyleBits*/
					retint=ScMethod(SCI_SETSTYLEBITS,atoipos,0);
					break;	
				case 36: /*GetStyleBits*/
					retint=ScMethod(SCI_GETSTYLEBITS,0,0);
					break;	
				case 37: /*SearchAnchor*/
					retint=ScMethod(SCI_SEARCHANCHOR,0,0);
					break;	
				case 38: /*SearchNext*/
				case 39: /*SearchPrev*/
				case 40: /*SearchNextScroll*/
				case 41: /*SearchPrevScroll*/
					{
						DWORD sf=0;
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						char *pos2=strchr(pos333,',');
						if (pos2) *(pos2++)=0;
						else pos2="";
						_strupr(pos333);
						CString src=pos2;
						if (m_FindDlg==NULL || m_FindDlg->m_hWnd==NULL) ShowFindDialog(0);
						if (m_FindDlg)	m_FindDlg->UpdateCombos();

						if (*pos333)
						{
							UINT i;
							for(i=0;i<GPScintilla::uNSearchFlags;i++)
								if (strstr(pos333,GPScintilla::cArrSearchFlags[i]))
									sf|=GPScintilla::uArrSearchFlags[i];
						}
						else
							if (m_FindDlg) sf=m_FindDlg->GetSearchFlags();

						if (src=="" && m_FindDlg) src=m_FindDlg->GetSearchText();

						int selstart=ScMethod(SCI_GETSELECTIONSTART,0,0);
						if (nfunc==40 || nfunc==38)			selstart++;
						else
						{
							selstart--;
							if (selstart<0) selstart=0;
						}

						ScMethod(SCI_SETSELECTIONSTART,selstart,0);
						ScMethod(SCI_SETSELECTIONEND,selstart,0);
						ScMethod(SCI_SEARCHANCHOR,0,0);

						BOOL scrl=FALSE;
						switch(nfunc)
						{
						case 40: /*SearchNextScroll*/
							scrl=TRUE;
						case 38: /*SearchNext*/
							retint=ScMethod(SCI_SEARCHNEXT,sf,(int)((LPCSTR)src));
							break;	
						case 41: /*SearchPrevScroll*/
							scrl=TRUE;
						case 39: /*SearchPrev*/
							retint=ScMethod(SCI_SEARCHPREV,sf,(int)((LPCSTR)src));
							break;	
						}

						if (retint<0)
						{
							if (nfunc==40 || nfunc==38)	selstart=0;
							else
								selstart=ScMethod(SCI_GETTEXTLENGTH,0,0);

							ScMethod(SCI_SETSELECTIONSTART,selstart,0);
							ScMethod(SCI_SETSELECTIONEND,selstart,0);
							ScMethod(SCI_SEARCHANCHOR,0,0);

							switch(nfunc)
							{
							case 40: /*SearchNextScroll*/
							case 38: /*SearchNext*/
								retint=ScMethod(SCI_SEARCHNEXT,sf,(int)((LPCSTR)src));
								break;	
							case 41: /*SearchPrevScroll*/
							case 39: /*SearchPrev*/
								retint=ScMethod(SCI_SEARCHPREV,sf,(int)((LPCSTR)src));
								break;	
							}
						}

						if (retint>=0)
						{
							if (scrl)
							{
								ScMethod(SCI_GOTOPOS,retint,0);
								ScMethod(SCI_ENSUREVISIBLE,ScMethod(SCI_LINEFROMPOSITION,retint,0),0);
							}
							ScMethod(SCI_SETSELECTIONSTART,retint,0);
							ScMethod(SCI_SETSELECTIONEND,retint+src.GetLength(),0);
						}
						delete[] pos333;
					}
					break;	
				case 42: /*FindText*/
					{
						TextToFind ttf={0};
						ttf.chrg.cpMin=0;
						ttf.chrg.cpMax=-1;
						m_LastScanf=sscanf(pos,"%d,%d",&ttf.chrg.cpMin,&ttf.chrg.cpMax);

						DWORD sf=0;
						CString cssf=ExtractField(pos,3,",");
						cssf.MakeUpper();

						UINT i;
						for(i=0;i<GPScintilla::uNSearchFlags;i++)
							if (cssf.Find(GPScintilla::cArrSearchFlags[i])>=0)
								sf|=GPScintilla::uArrSearchFlags[i];

						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						const char *pos2=FindField(pos333,4,",");
						retint=-1;
						if (pos2 && *pos2)
						{
							ttf.lpstrText=(char *)pos2;
							retint=ScMethod(SCI_FINDTEXT,sf,(int)&ttf);
							if (oStr)
								sprintf(oStr,"%d\x7F%d\x7F%d",retint,ttf.chrgText.cpMin,ttf.chrgText.cpMax);
						}
						delete[] pos333;
					}
					break;	
				case 43: /*SetTargetStart*/
					retint=ScMethod(SCI_SETTARGETSTART,atoipos,0);
					break;	
				case 44: /*GetTargetStart*/
					retint=ScMethod(SCI_GETTARGETSTART,0,0);
					break;	
				case 45: /*SetTargetEnd*/
					retint=ScMethod(SCI_SETTARGETEND,atoipos,0);
					break;	
				case 46: /*GetTargetEnd*/
					retint=ScMethod(SCI_GETTARGETEND,0,0);
					break;	
				case 47: /*SetTarget*/
					{
						int start=0,end=-1;
						m_LastScanf=sscanf(pos,"%d,%d",&start,&end);
						retint=ScMethod(SCI_SETTARGETSTART,start,0);
						retint=ScMethod(SCI_SETTARGETEND,end,0);
					}
					break;	
				case 48: /*GetTarget*/
					if (oStr)
						sprintf(oStr,"%d\x7F%d",ScMethod(SCI_GETTARGETSTART,0,0),ScMethod(SCI_GETTARGETEND,0,0));
					break;	
				case 49: /*TargetFromSelection*/
					retint=ScMethod(SCI_TARGETFROMSELECTION,0,0);
					break;	
				case 50: /*ReplaceTarget*/
				case 51: /*ReplaceTargetRe*/
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						Replace1To13(pos333);
						switch(nfunc)
						{
						case 50: /*ReplaceTarget*/
							retint=ScMethod(SCI_REPLACETARGET,-1,(int)pos333);
							break;	
						case 51: /*ReplaceTargetRe*/
							retint=ScMethod(SCI_REPLACETARGETRE,-1,(int)pos333);
							break;	
						}
						delete[] pos333;
					}
					break;	
				case 52: /*SetSearchFlags*/
					{
						DWORD sf=atoipos;
						if (sf==0)
						{
							char *pos333=new char [(int)strlen(pos)+2];
							strcpy(pos333,pos);
							_strupr(pos333);

							UINT i;
							for(i=0;i<GPScintilla::uNSearchFlags;i++)
								if (strstr(pos333,GPScintilla::cArrSearchFlags[i]))
									sf|=GPScintilla::uArrSearchFlags[i];
							delete[] pos333;
						}
						retint=ScMethod(SCI_SETSEARCHFLAGS,sf,0);
					}
					break;	
				case 53: /*GetSearchFlags*/
					if (oStr)
					{
						retint=ScMethod(SCI_GETSEARCHFLAGS,0,0);
						UINT i;
						for(i=0;i<GPScintilla::uNSearchFlags;i++)
							if ((retint&GPScintilla::uArrSearchFlags[i])==GPScintilla::uArrSearchFlags[i])
							{
								if (*oStr) strcat(oStr,"|");
								strcat(oStr,GPScintilla::cArrSearchFlags[i]);
							}
					}
					break;	
				case 54: /*SearchInTarget*/
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						retint=ScMethod(SCI_SEARCHINTARGET,(int)strlen(pos333),(int)Replace1To13(pos333));
						delete[] pos333;
					}
					break;	
				case 55: /*SetStatus*/
					retint=ScMethod(SCI_SETSTATUS,atoipos,0);
					break;	
				case 56: /*GetStatus*/
					retint=ScMethod(SCI_GETSTATUS,0,0);
					break;	
				case 57: /*Undo*/
					if (atoipos<=0 || atoipos>1000) atoipos=1;
					while(atoipos-->0)
						retint=ScMethod(SCI_UNDO,0,0);
					break;	
				case 58: /*CanUndo*/
					retint=ScMethod(SCI_CANUNDO,0,0);
					break;	
				case 59: /*EmptyUndoBuffer*/
					retint=ScMethod(SCI_EMPTYUNDOBUFFER,0,0);
					break;	
				case 60: /*Redo*/
					if (atoipos<=0 || atoipos>1000) atoipos=1;
					while(atoipos-->0)
						retint=ScMethod(SCI_REDO,0,0);
					break;	
				case 61: /*CanRedo*/
					retint=ScMethod(SCI_CANREDO,0,0);
					break;	
				case 62: /*SetUndoCollection*/
					retint=ScMethod(SCI_SETUNDOCOLLECTION,atoipos,0);
					break;	
				case 63: /*GetUndoCollection*/
					retint=ScMethod(SCI_GETUNDOCOLLECTION,0,0); 
					break;	
				}
			}
			else
			{
				switch(nfunc)
				{
				case 64: /*BeginUndoAction*/
					retint=ScMethod(SCI_BEGINUNDOACTION,0,0);
					break;	
				case 65: /*EndUndoAction*/
					retint=ScMethod(SCI_ENDUNDOACTION,0,0);
					break;	
				case 66: /*GetLineCount*/
					retint=ScMethod(SCI_GETLINECOUNT,0,0);
					break;	
				case 67: /*GetFirstVisibleLine*/
					retint=ScMethod(SCI_GETFIRSTVISIBLELINE,0,0);
					break;	
				case 68: /*LinesOnScreen*/
					retint=ScMethod(SCI_LINESONSCREEN,0,0);
					break;	
				case 69: /*SetSel*/
					{
						int start=0,end=-1;
						m_LastScanf=sscanf(pos,"%d,%d",&start,&end);
						retint=ScMethod(SCI_SETSEL,start,end);
					}
					break;	
				case 70: /*GotoPos*/
					retint=ScMethod(SCI_GOTOPOS,atoipos,0);
					break;	
				case 71: /*GotoLine*/
					retint=ScMethod(SCI_GOTOLINE,atoipos,0);
					break;	
				case 72: /*SetCurrentPos*/
					retint=ScMethod(SCI_SETCURRENTPOS,atoipos,0);
					break;	
				case 73: /*GetCurrentPos*/
					retint=ScMethod(SCI_GETCURRENTPOS,0,0);
					break;	
				case 74: /*SetAnchor*/
					retint=ScMethod(SCI_SETANCHOR,atoipos,0);
					break;	
				case 75: /*GetAnchor*/
					retint=ScMethod(SCI_GETANCHOR,0,0);
					break;	
				case 76: /*SetSelectionStart*/
					retint=ScMethod(SCI_SETSELECTIONSTART,atoipos,0);
					break;	
				case 77: /*SetSelectionEnd*/
					retint=ScMethod(SCI_SETSELECTIONEND,atoipos,0);
					break;	
				case 78: /*GetSelectionStart*/
					retint=ScMethod(SCI_GETSELECTIONSTART,0,0);
					break;	
				case 79: /*GetSelectionEnd*/
					retint=ScMethod(SCI_GETSELECTIONEND,0,0);
					break;	
				case 80: /*SelectAll*/
					retint=ScMethod(SCI_SELECTALL,0,0);
					break;	
				case 81: /*LineFromPosition*/
					retint=ScMethod(SCI_LINEFROMPOSITION,atoipos,0);
					break;	
				case 82: /*PositionFromLine*/
					if (atoipos<0 || *pos==0)	atoipos=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
					retint=ScMethod(SCI_POSITIONFROMLINE,atoipos,0);
					break;	
				case 83: /*GetLineEndPosition*/
					if (atoipos<0 || *pos==0)	atoipos=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
					retint=ScMethod(SCI_GETLINEENDPOSITION,atoipos,0);
					break;	
				case 84: /*GetLineLength*/
					if (atoipos<0 || *pos==0)	atoipos=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
					retint=ScMethod(SCI_LINELENGTH,atoipos,0);
					break;	
				case 85: /*GetSelText*/
					if (oStr)
						ScMethod(SCI_GETSELTEXT,0,(int)oStr);
					break;	
				case 86: /*GetCurLine*/
					if (oStr)
						ScMethod(SCI_GETCURLINE,TMP_STR_OUT_LEN,(int)oStr);
					break;	
				case 87: /*GetCurLineEx*/
					if (oStr)
					{
						retint=ScMethod(SCI_GETCURLINE,TMP_STR_OUT_LEN,(int)(oStr+100));
						sprintf(oStr,"%d\x7F%s",retint,oStr+100);
					}
					break;	
				case 88: /*SelectionIsRectangle*/
					retint=ScMethod(SCI_SELECTIONISRECTANGLE,0,0);
					break;	
				case 89: /*MoveCaretInsideView*/
					retint=ScMethod(SCI_MOVECARETINSIDEVIEW,0,0);
					break;	
				case 90: /*WordEndPosition*/
				case 91: /*WordStartPosition*/
					{
						int position=0;
						BOOL onlyWordCharacters=FALSE;
						m_LastScanf=sscanf(pos,"%d,%d",&position,&onlyWordCharacters);
						switch(nfunc)
						{
						case 90: /*WordEndPosition*/
							retint=ScMethod(SCI_WORDENDPOSITION,position,onlyWordCharacters);
							break;	
						case 91: /*WordStartPosition*/
							retint=ScMethod(SCI_WORDSTARTPOSITION,position,onlyWordCharacters);
							break;	
						}
					}
					break;	
				case 92: /*PositionBefore*/
					retint=ScMethod(SCI_POSITIONBEFORE,atoipos,0);
					break;	
				case 93: /*PositionAfter*/
					retint=ScMethod(SCI_POSITIONAFTER,atoipos,0);
					break;	
				case 94: /*TextWidth*/
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						char *pos1=strchr(pos333,',');
						if (pos1) pos1++;
						else pos1="";
						Replace1To13(pos1);
						retint=ScMethod(SCI_TEXTWIDTH,atoipos,(int)pos1);
						delete[] pos333;
					}
					break;	
				case 95: /*TextHeight*/
					retint=ScMethod(SCI_TEXTHEIGHT,atoipos,0);
					break;	
				case 96: /*GetColumn*/
					retint=ScMethod(SCI_GETCOLUMN,atoipos,0);
					break;	
				case 97: /*PositionFromPoint*/
					{
						int x=0,y=0;
						m_LastScanf=sscanf(pos,"%d,%d",&x,&y);
						retint=ScMethod(SCI_POSITIONFROMPOINT,x,y);
					}
					break;	
				case 98: /*PositionFromPointClose*/
					{
						int x=0,y=0;
						m_LastScanf=sscanf(pos,"%d,%d",&x,&y);
						retint=ScMethod(SCI_POSITIONFROMPOINTCLOSE,x,y);
					}
					break;	
				case 99: /*PointXFromPosition*/
					retint=ScMethod(SCI_POINTXFROMPOSITION,0,atoipos);
					break;	
				case 100: /*PointYFromPosition*/
					retint=ScMethod(SCI_POINTYFROMPOSITION,0,atoipos);
					break;	
				case 101: /*HideSelection*/
					retint=ScMethod(SCI_HIDESELECTION,atoipos,0);
					break;	
				case 102: /*ChooseCaretX*/
					retint=ScMethod(SCI_CHOOSECARETX,0,0);
					break;	
				case 103: /*LineScroll*/
					{
						int column=0,line=0;
						m_LastScanf=sscanf(pos,"%d,%d",&column,&line);
						retint=ScMethod(SCI_LINESCROLL,column,line);
					}
					break;	
				case 104: /*ScrollCaret*/
					retint=ScMethod(SCI_SCROLLCARET,0,0);
					break;	
				case 105: /*SetXCaretPolicy*/
				case 106: /*SetYCaretPolicy*/
					{
						int caretPolicy=0;
						int caretSlop=0;
						m_LastScanf=sscanf(pos,"%d,%d",&caretSlop,&caretPolicy);
						if (caretPolicy==0)
						{
							char *pos333=new char [(int)strlen(pos)+2];
							strcpy(pos333,pos);
							_strupr(pos333);

							UINT i;
							for(i=0;i<GPScintilla::uNcaretPolicy;i++)
								if (strstr(pos333,GPScintilla::cArrcaretPolicy[i]))
									caretPolicy|=GPScintilla::uArrcaretPolicy[i];
							delete[] pos333;
						}
						switch(nfunc)
						{
						case 105: /*SetXCaretPolicy*/
							retint=ScMethod(SCI_SETXCARETPOLICY,caretPolicy,caretSlop);
							break;	
						case 106: /*SetYCaretPolicy*/
							retint=ScMethod(SCI_SETYCARETPOLICY,caretPolicy,caretSlop);
							break;	
						}
					}
					break;	
				case 107: /*SetVisiblePolicy*/
					{
						int VisiblePolicy=0;
						int caretSlop=0;
						m_LastScanf=sscanf(pos,"%d,%d",&caretSlop,&VisiblePolicy);
						if (VisiblePolicy==0)
						{
							char *pos333=new char [(int)strlen(pos)+2];
							strcpy(pos333,pos);
							_strupr(pos333);

							UINT i;
							for(i=0;i<GPScintilla::uNVisiblePolicy;i++)
								if (strstr(pos333,GPScintilla::cArrVisiblePolicy[i]))
									VisiblePolicy|=GPScintilla::uArrVisiblePolicy[i];
							delete[] pos333;
						}
						retint=ScMethod(SCI_SETVISIBLEPOLICY,VisiblePolicy,caretSlop);
					}
					break;	
				case 108: /*SetHScrollBar*/
					retint=ScMethod(SCI_SETHSCROLLBAR,atoipos,0);
					break;	
				case 109: /*GetHScrollBar*/
					retint=ScMethod(SCI_GETHSCROLLBAR,0,0);
					break;	
				case 110: /*SetVScrollBar*/
					retint=ScMethod(SCI_SETVSCROLLBAR,atoipos,0);
					break;	
				case 111: /*GetVScrollBar*/
					retint=ScMethod(SCI_GETVSCROLLBAR,0,0);
					break;	
				case 112: /*GetXOffset*/
					retint=ScMethod(SCI_GETXOFFSET,0,0);
					break;	
				case 113: /*SetXOffset*/
					retint=ScMethod(SCI_SETXOFFSET,atoipos,0);
					break;	
				case 114: /*SetScrollWidth*/
					retint=ScMethod(SCI_SETSCROLLWIDTH,atoipos,0);
					break;	
				case 115: /*GetScrollWidth*/
					retint=ScMethod(SCI_GETSCROLLWIDTH,0,0);
					break;	
				case 116: /*SetEndAtLastLine*/
					if (atoipos<0 || *pos==0)	atoipos=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
					retint=ScMethod(SCI_SETENDATLASTLINE,atoipos,0);
					break;	
				case 117: /*GetEndAtLastLine*/
					retint=ScMethod(SCI_GETENDATLASTLINE,0,0);
					break;
				case 118: /*SetViewWS*/
					{
						int wsMode=atoipos;
						if (wsMode==0)
						{
							char *pos333=new char [(int)strlen(pos)+2];
							strcpy(pos333,pos);
							_strupr(pos333);
							UINT i;
							for(i=0;i<GPScintilla::uNWSpaceStyle;i++)
								if (strstr(pos333,GPScintilla::cArrWSpaceStyle[i]))
									wsMode|=GPScintilla::uArrWSpaceStyle[i];
							delete[] pos333;
						}
						retint=ScMethod(SCI_SETVIEWWS,wsMode,0);
					}
					break;	
				case 119: /*GetViewWS*/
					if (oStr)
					{
						retint=ScMethod(SCI_GETVIEWWS,0,0);
						UINT i;
						for(i=0;i<GPScintilla::uNWSpaceStyle;i++)
							if ((retint&GPScintilla::uArrWSpaceStyle[i])==GPScintilla::uArrWSpaceStyle[i])
							{
								if (*oStr) strcat(oStr,"|");
								strcat(oStr,GPScintilla::cArrWSpaceStyle[i]);
							}
					}
					break;	
				case 120: /*SetWhiteSpaceFore*/
					{
						int useColour=0,r=0,g=0,b=0;
						m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&useColour,&r,&g,&b);
						retint=ScMethod(SCI_SETWHITESPACEFORE,useColour,RGB(r,g,b));
					}
				case 121: /*SetWhiteSpaceBack*/
					{
						int useColour=0,r=0,g=0,b=0;
						m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&useColour,&r,&g,&b);
						retint=ScMethod(SCI_SETWHITESPACEBACK,useColour,RGB(r,g,b));
					}
					break;	
				case 122: /*SetEditCursor*/
					{
						int curType=atoipos;
						if (curType==0)
						{
							char *pos333=new char [(int)strlen(pos)+2];
							strcpy(pos333,pos);
							_strupr(pos333);
							UINT i;
							for(i=0;i<GPScintilla::uNCursorType;i++)
								if (strcmp(pos333,GPScintilla::cArrCursorType[i])==0)
								{
									curType=GPScintilla::uArrCursorType[i];
									break;
								}
							delete[] pos333;
						}
						retint=ScMethod(SCI_SETCURSOR,curType,0);
					}
					break;	
				case 123: /*GetEditCursor*/
					if (oStr)
					{
						retint=ScMethod(SCI_GETCURSOR,0,0);
						UINT i;
						for(i=0;i<GPScintilla::uNCursorType && *oStr==0;i++)
							if (retint==GPScintilla::uArrCursorType[i])
								strcpy(oStr,GPScintilla::cArrCursorType[i]);
					}
					break;	
				case 124: /*SetMouseDownCaptures*/
					retint=ScMethod(SCI_SETMOUSEDOWNCAPTURES,atoipos,0);
					break;	
				case 125: /*GetMouseDownCaptures*/
					retint=ScMethod(SCI_GETMOUSEDOWNCAPTURES,0,0);
					break;	
				}
			}
		}
		else
		{
			switch(nfunc)
			{
			case 126: /*ConvertEOLs*/
			case 127: /*SetEOLMode*/
				{
					int EOLMode=atoipos;
					retint=ScMethod(SCI_GETEOLMODE,0,0);
					if (EOLMode==0)
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						_strupr(pos333);
						UINT i;
						for(i=0;i<GPScintilla::uNEOLMode;i++)
							if (strcmp(pos333,GPScintilla::cArrEOLMode[i])==0)
							{
								EOLMode=GPScintilla::uArrEOLMode[i];
								break;
							}
						delete[] pos333;
					}
					switch(nfunc)
					{
					case 126: /*ConvertEOLs*/
						retint=ScMethod(SCI_CONVERTEOLS,EOLMode,0);
						break;
					case 127: /*SetEOLMode*/
						retint=ScMethod(SCI_SETEOLMODE,EOLMode,0);
						break;
					}
				}
				break;	
			case 128: /*GetEOLMode*/
				if (oStr)
				{
					retint=ScMethod(SCI_GETEOLMODE,0,0);
					UINT i;
					for(i=0;i<GPScintilla::uNEOLMode && *oStr==0;i++)
						if (retint==(int)GPScintilla::uArrEOLMode[i])
							strcpy(oStr,GPScintilla::cArrEOLMode[i]);
				}
				break;	
			case 129: /*SetSelFore*/
				{
					int useColour=0,r=0,g=0,b=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&useColour,&r,&g,&b);
					retint=ScMethod(SCI_SETSELFORE,useColour,RGB(r,g,b));
				}
				break;	
			case 130: /*SetSelBack*/
				{
					int useColour=0,r=0,g=0,b=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&useColour,&r,&g,&b);
					retint=ScMethod(SCI_SETSELBACK,useColour,RGB(r,g,b));
				}
				break;	
			case 131: /*SetCaretFore*/
				{
					int r=0,g=0,b=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d",&r,&g,&b);
					retint=ScMethod(SCI_SETCARETFORE,RGB(r,g,b),0);
				}
				break;	
			case 132: /*GetCaretFore*/
				if (oStr)
				{
					retint=ScMethod(SCI_GETCARETFORE,0,0);
					sprintf(oStr,"%d\x7F%d\x7F%d",GetRValue(retint),GetGValue(retint),GetBValue(retint));
				}
				break;	
			case 133: /*SetCaretLineVisible*/
				retint=ScMethod(SCI_SETCARETLINEVISIBLE,atoipos,0);
				break;	
			case 134: /*GetCaretLineVisible*/
				retint=ScMethod(SCI_GETCARETLINEVISIBLE,0,0);
				break;	
			case 135: /*SetCaretLineBack*/
				{
					int r=0,g=0,b=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d",&r,&g,&b);
					retint=ScMethod(SCI_SETCARETLINEBACK,RGB(r,g,b),0);
				}
				break;	
			case 136: /*GetCaretLineBack*/
				if (oStr)
				{
					retint=ScMethod(SCI_GETCARETLINEBACK,0,0);
					sprintf(oStr,"%d\x7F%d\x7F%d",GetRValue(retint),GetGValue(retint),GetBValue(retint));
				}
				break;	
			case 137: /*SetCaretPeriod*/
				retint=ScMethod(SCI_SETCARETPERIOD,atoipos,0);
				break;	
			case 138: /*GetCaretPeriod*/
				retint=ScMethod(SCI_GETCARETPERIOD,0,0);
				break;	
			case 139: /*SetCaretWidth*/
				retint=ScMethod(SCI_SETCARETWIDTH,atoipos,0);
				break;	
			case 140: /*GetCaretWidth*/
				retint=ScMethod(SCI_GETCARETWIDTH,0,0);
				break;	
			case 141: /*SetHotspotActiveFore*/
				{
					int useColour=0,r=0,g=0,b=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&useColour,&r,&g,&b);
					retint=ScMethod(SCI_SETHOTSPOTACTIVEFORE,useColour,RGB(r,g,b));
				}
				break;	
			case 142: /*SetHotspotActiveBack*/
				{
					int useColour=0,r=0,g=0,b=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&useColour,&r,&g,&b);
					retint=ScMethod(SCI_SETHOTSPOTACTIVEBACK,useColour,RGB(r,g,b));
				}
				break;	
			case 143: /*SetHotspotActiveUnderline*/
				retint=ScMethod(SCI_SETHOTSPOTACTIVEUNDERLINE,atoipos,0);
				break;	
			case 144: /*SetControlCharSymbol*/
				retint=ScMethod(SCI_SETCONTROLCHARSYMBOL,atoipos,0);
				break;	
			case 145: /*GetControlCharSymbol*/
				retint=ScMethod(SCI_GETCONTROLCHARSYMBOL,0,0);
				break;	
			case 146: /*SetMarginTypeN*/
				{
					char *pos333=new char [(int)strlen(pos)+2];
					strcpy(pos333,pos);
					char *pos2=strchr(pos333,',');
					if (pos2++==NULL) pos2="";
					int MarginType=atoi(pos2);
					if (MarginType==0)
					{
						_strupr(pos333);
						UINT i;
						for(i=0;i<GPScintilla::uNMarginType;i++)
							if (strcmp(pos2,GPScintilla::cArrMarginType[i])==0)
							{
								MarginType=GPScintilla::uArrMarginType[i];
								break;
							}
					}
					delete[] pos333;
					retint=ScMethod(SCI_SETMARGINTYPEN,atoipos,MarginType);
				}
				break;	
			case 147: /*GetMarginTypeN Margin*/
				if (oStr)
				{
					retint=ScMethod(SCI_GETMARGINTYPEN,atoipos,0);
					UINT i;
					for(i=0;i<GPScintilla::uNMarginType && *oStr==0;i++)
						if (retint==(int)GPScintilla::uArrMarginType[i])
							strcpy(oStr,GPScintilla::cArrMarginType[i]);
				}
				break;	
			case 148: /*SetMarginWidthN*/
				{
					int margin=0;
					int pixelWidth=0;
					m_LastScanf=sscanf(pos,"%d,%d",&margin,&pixelWidth);
					retint=ScMethod(SCI_SETMARGINWIDTHN,margin,pixelWidth);
				}
				break;	
			case 149: /*GetMarginWidthN*/
				retint=ScMethod(SCI_GETMARGINWIDTHN,atoipos,0);
				break;	
			case 150: /*SetMarginMaskN*/
				{
					char *pos333=new char [(int)strlen(pos)+2];
					strcpy(pos333,pos);
					char *pos2=strchr(pos333,',');
					if (pos2++==NULL) pos2="";
					int MarginMask=atoi(pos2);
					if (MarginMask==0)
					{
						_strupr(pos333);
						UINT i;
						for(i=0;i<GPScintilla::uNMarginMask;i++)
							if (strcmp(pos2,GPScintilla::cArrMarginMask[i])==0)
							{
								MarginMask=GPScintilla::uArrMarginMask[i];
								break;
							}
					}
					delete[] pos333;
					retint=ScMethod(SCI_SETMARGINMASKN,atoipos,MarginMask);
				}
				break;	
			case 151: /*GetMarginMaskN*/
				if (oStr)
				{
					retint=ScMethod(SCI_GETMARGINMASKN,atoipos,0);
					UINT i;
					for(i=0;i<GPScintilla::uNMarginMask && *oStr==0;i++)
						if (retint==(int)GPScintilla::uArrMarginMask[i])
							strcpy(oStr,GPScintilla::cArrMarginMask[i]);
				}
				break;	
			case 152: /*SetMarginSensitiveN*/
				{
					int margin=0;
					int sensitive=0;
					m_LastScanf=sscanf(pos,"%d,%d",&margin,&sensitive);
					retint=ScMethod(SCI_SETMARGINSENSITIVEN,margin,sensitive);
				}
				break;	
			case 153: /*GetMarginSensitiveN*/
				retint=ScMethod(SCI_GETMARGINSENSITIVEN,atoipos,0);
				break;	
			case 154: /*SetMarginLeft*/
				retint=ScMethod(SCI_SETMARGINLEFT,0,atoipos);
				break;	
			case 155: /*GetMarginLeft*/
				retint=ScMethod(SCI_GETMARGINLEFT,0,0);
				break;	
			case 156: /*SetMarginRight*/
				retint=ScMethod(SCI_SETMARGINRIGHT,0,atoipos);
				break;	
			case 157: /*GetMarginRight*/
				retint=ScMethod(SCI_GETMARGINRIGHT,0,0);
				break;	

			case 158: /*SetFoldMarginColor*/
				{
					int useColour=0,r=0,g=0,b=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&useColour,&r,&g,&b);
					retint=ScMethod(SCI_SETFOLDMARGINCOLOUR,useColour,RGB(r,g,b));
				}
				break;	
			case 159: /*SetFoldMarginHiColor*/
				{
					int useColour=0,r=0,g=0,b=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&useColour,&r,&g,&b);
					retint=ScMethod(SCI_SETFOLDMARGINHICOLOUR,useColour,RGB(r,g,b));
				}
				break;	
			case 160: /*SetBufferedDraw*/
				retint=ScMethod(SCI_SETBUFFEREDDRAW,atoipos,0);
				break;	
			case 161: /*GetBufferedDraw*/
				retint=ScMethod(SCI_GETBUFFEREDDRAW,0,0);
				break;	
			case 162: /*SetTwoPhaseDraw*/
				retint=ScMethod(SCI_SETTWOPHASEDRAW,atoipos,0);
				break;	
			case 163: /*GetTwoPhaseDraw*/
				retint=ScMethod(SCI_GETTWOPHASEDRAW,0,0);
				break;	
			case 164: /*SetCodePage*/
				{
					int CodePage=atoipos;
					if (CodePage==0)
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						_strupr(pos333);
						UINT i;
						for(i=0;i<GPScintilla::uNCodePage;i++)
							if (strcmp(pos333,GPScintilla::cArrCodePage[i])==0)
							{
								CodePage=GPScintilla::uArrCodePage[i];
								break;
							}
						delete[] pos333;
					}
					retint=ScMethod(SCI_SETCODEPAGE,CodePage,0);
				}
				break;	
			case 165: /*GetCodePage*/
				if (oStr)
				{
					retint=ScMethod(SCI_GETCODEPAGE,0,0);
					UINT i;
					for(i=0;i<GPScintilla::uNCodePage && *oStr==0;i++)
						if (retint==(int)GPScintilla::uArrCodePage[i])
							strcpy(oStr,GPScintilla::cArrCodePage[i]);
				}
				break;	
			case 166: /*SetWordChars*/
				retint=ScMethod(SCI_SETWORDCHARS,0,(int)pos);
				break;	
			case 167: /*SCI_GrabFocus*/
				retint=ScMethod(SCI_GRABFOCUS,0,0);
				break;	
			case 168: /*SCI_SetFocus*/
				retint=ScMethod(SCI_SETFOCUS,atoipos,0);
				break;	
			case 169: /*SCI_GetFocus*/
				retint=ScMethod(SCI_GETFOCUS,0,0);
				break;	
			case 170: /*BraceHighlight*/
				{
					int pos1=0;
					int pos2=0;
					m_LastScanf=sscanf(pos,"%d,%d",&pos1,&pos2);
					retint=ScMethod(SCI_BRACEHIGHLIGHT,pos1,pos2);
				}
				break;	
			case 171: /*BraceBadLight*/
				retint=ScMethod(SCI_BRACEBADLIGHT,atoipos,0);
				break;	
			case 172: /*BraceMatch*/
				{
					int position=0;
					int maxReStyle=0;
					m_LastScanf=sscanf(pos,"%d,%d",&position,&maxReStyle);
					retint=ScMethod(SCI_BRACEMATCH,position,maxReStyle);
				}
				break;	
			case 173: /*SetTabWidth*/
				retint=ScMethod(SCI_SETTABWIDTH,atoipos,0);
				break;	
			case 174: /*GetTabWidth*/
				retint=ScMethod(SCI_GETTABWIDTH,0,0);
				break;	
			case 175: /*SetUseTabs*/
				retint=ScMethod(SCI_SETUSETABS,atoipos,0);
				break;	
			case 176: /*GetUseTabs*/
				retint=ScMethod(SCI_GETUSETABS,0,0);
				break;	
			case 177: /*SetIndent*/
				retint=ScMethod(SCI_SETINDENT,atoipos,0);
				break;	
			case 178: /*GetIndent*/
				retint=ScMethod(SCI_GETINDENT,0,0);
				break;	
			case 179: /*SetTabIndents*/
				retint=ScMethod(SCI_SETTABINDENTS,atoipos,0);
				break;	
			case 180: /*GetTabIndents*/
				retint=ScMethod(SCI_GETTABINDENTS,0,0);
				break;	
			case 181: /*SetBackspaceUnindents(bool bsUnIndents)*/
				retint=ScMethod(SCI_SETBACKSPACEUNINDENTS,atoipos,0);
				break;	
			case 182: /*GetBackspaceUnindents*/
				retint=ScMethod(SCI_GETBACKSPACEUNINDENTS,0,0);
				break;	
			case 183: /*SetLineIndentation*/
				{
					int line=0;
					int indentation=0;
					m_LastScanf=sscanf(pos,"%d,%d",&line,&indentation);
					if (line<0)	line=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
					retint=ScMethod(SCI_SETLINEINDENTATION,line,indentation);
				}
				break;	
			case 184: /*GetLineIndentation*/
				if (atoipos<0 || *pos==0)	atoipos=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
				retint=ScMethod(SCI_GETLINEINDENTATION,atoipos,0);
				break;	
			case 185: /*GetLineIndentPosition*/
				if (atoipos<0 || *pos==0)	atoipos=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
				retint=ScMethod(SCI_GETLINEINDENTPOSITION,atoipos,0);
				break;	
			case 186: /*SetIndentationGuides*/
				retint=ScMethod(SCI_SETINDENTATIONGUIDES,atoipos,0);
				break;	
			case 187: /*GetIndentationGuides*/
				retint=ScMethod(SCI_GETINDENTATIONGUIDES,0,0);
				break;	
			case 188: /*SetHighlightGuide(int column)*/
				retint=ScMethod(SCI_SETHIGHLIGHTGUIDE,atoipos,0);
				break;	
			case 189: /*GetHighlightGuide*/
				retint=ScMethod(SCI_GETHIGHLIGHTGUIDE,0,0);
				break;
			case 190: /*MarkerDefine*/
				{
					char *pos333=new char [(int)strlen(pos)+2];
					strcpy(pos333,pos);
					char *pos2=strchr(pos333,',');
					if (pos2++==NULL) pos2="";
					int markerSymbols=atoi(pos2);
					if (markerSymbols==0)
					{
						_strupr(pos333);
						UINT i;
						for(i=0;i<GPScintilla::uNMark;i++)
							if (strcmp(pos2,GPScintilla::cArrMark[i])==0)
							{
								markerSymbols=GPScintilla::uArrMark[i];
								break;
							}
					}
					delete[] pos333;
					retint=ScMethod(SCI_MARKERDEFINE,atoipos,markerSymbols);
				}
				break;	
			case 191: /*MarkerDefinePixmap markerNumber,xpm*/
				{
					const char *postmp=strchr(pos,',');
					if (postmp++ && *postmp) 
						retint=ScMethod(SCI_MARKERDEFINEPIXMAP,atoipos,(int)postmp);
				}
				break;	
			case 192: /*MarkerSetFore*/
				{
					int useColour=0,r=0,g=0,b=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&useColour,&r,&g,&b);
					retint=ScMethod(SCI_MARKERSETFORE,useColour,RGB(r,g,b));
				}
				break;	
			case 193: /*MarkerSetBack*/
				{
					int useColour=0,r=0,g=0,b=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&useColour,&r,&g,&b);
					retint=ScMethod(SCI_MARKERSETBACK,useColour,RGB(r,g,b));
				}
				break;	
			case 194: /*MarkerAdd*/
			case 195: /*MarkerDelete*/
				{
					int line=0;
					int markerNumber=0;
					int bToggle=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d",&line,&markerNumber,&bToggle);
					if (line<0)	line=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
					if (bToggle) 
						retint=ScMethod(nfunc==194?SCI_MARKERDELETE:SCI_MARKERADD,line,markerNumber);
					else
						retint=ScMethod(nfunc==194?SCI_MARKERADD:SCI_MARKERDELETE,line,markerNumber);
				}
				break;	
			case 196: /*MarkerDeleteAll*/
				retint=ScMethod(SCI_MARKERDELETEALL,atoipos,0);
				break;	
			case 197: /*MarkerGet*/
				if (atoipos<0 || *pos==0)	atoipos=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
				retint=ScMethod(SCI_MARKERGET,atoipos,0);
				break;	
			case 198: /*MarkerNext*/
			case 199: /*MarkerPrevious*/
				{
					int position=ScMethod(SCI_GETCURRENTPOS,0,0);
					int curline=ScMethod(SCI_LINEFROMPOSITION,position,0);
					int nLines=ScMethod(SCI_GETLINECOUNT,0,0);

					int lineStart=-1;
					int markerMask=-1;
					int bShow=1;
					m_LastScanf=sscanf(pos,"%d,%d,%d",&lineStart,&markerMask,&bShow);
					if (lineStart>=0) curline=lineStart;
					if (markerMask<0) markerMask=GPScintilla::uArrMarkerMask[m_CurMarkerType%32];

					if (nfunc==198)/*MarkerNext*/
					{
						curline++;
						if (curline==nLines) curline=0;
						curline=ScMethod(SCI_MARKERNEXT,curline,markerMask);
						if (curline<0)
							curline=ScMethod(SCI_MARKERNEXT,0,markerMask);
					}
					else /*MarkerPrevious*/
					{
						curline--;
						if (curline<0) curline=nLines-1;
						curline=ScMethod(SCI_MARKERPREVIOUS,curline,markerMask);
						if (curline<0)
							curline=ScMethod(SCI_MARKERPREVIOUS,nLines-1,markerMask);
					}
					if (bShow)
					{
						if (curline<0)
							MessageBeep(MB_ICONASTERISK);
						else
							ScMethod(SCI_GOTOLINE,curline,0);
					}
					retint=curline;
				}
				break;
			case 200: /*MarkerLineFromHandle*/
				retint=ScMethod(SCI_MARKERLINEFROMHANDLE,atoipos,0);
				break;	
			case 201: /*MarkerDeleteHandle*/
				retint=ScMethod(SCI_MARKERDELETEHANDLE,atoipos,0);
				break;	
			case 202: /*IndicSetStyle*/
				{
					char *pos333=new char [(int)strlen(pos)+2];
					strcpy(pos333,pos);
					char *pos2=strchr(pos333,',');
					if (pos2++==NULL) pos2="";
					int Indicator=atoi(pos2);
					if (Indicator==0)
					{
						_strupr(pos333);
						UINT i;
						for(i=0;i<GPScintilla::uNIndicator;i++)
							if (strcmp(pos2,GPScintilla::cArrIndicator[i])==0)
							{
								Indicator=GPScintilla::uArrIndicator[i];
								break;
							}
					}
					delete[] pos333;
					retint=ScMethod(SCI_INDICSETSTYLE,atoipos,Indicator);
				}
				break;	
			case 203: /*IndicGetStyle*/
				if (oStr)
				{
					retint=ScMethod(SCI_INDICGETSTYLE,atoipos,0);
					UINT i;
					for(i=0;i<GPScintilla::uNIndicator && *oStr==0;i++)
						if (retint==(int)GPScintilla::uArrIndicator[i])
							strcpy(oStr,GPScintilla::cArrIndicator[i]);
				}
				break;	
			case 204: /*IndicSetFore*/
				{
					int useColour=0,r=0,g=0,b=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d,%d",&useColour,&r,&g,&b);
					retint=ScMethod(SCI_INDICSETFORE,useColour,RGB(r,g,b));
				}
				break;	
			case 205: /*IndicGetFore*/
				retint=ScMethod(SCI_INDICGETFORE,atoipos,0);
				sprintf(oStr,"%d\x7F%d\x7F%d",GetRValue(retint),GetGValue(retint),GetBValue(retint));
				break;	
			case 206: /*AutocShow*/
			case 230: /*UserListShow lenEntered*/
				{
					const char *pos2=strchr(pos,',');

					if (nfunc==206)
						if (pos2++ && *pos2)
						{
							if (m_autocList) delete[] m_autocList;
							m_autocList=new char [(int)strlen(pos)+100];
							strcpy(m_autocList,pos2);
						}
						else pos2=m_autocList;

					atoipos=CheckEnteredLength(atoipos);
					retint=-1;
					
						switch(nfunc)
						{
						case 206:
							if (m_autocList++ && *m_autocList) 
								retint=ScMethod(SCI_AUTOCSHOW,atoipos,(int)m_autocList);
							break;
						case 230:
							if (pos2++ && *pos2)
								retint=ScMethod(SCI_USERLISTSHOW,atoipos,(int)pos2);
							break;
						}
				}
				break;	
			case 207: /*AutocCancel*/
				retint=ScMethod(SCI_AUTOCCANCEL,0,0);
				break;	
			case 208: /*AutocActive*/
				retint=ScMethod(SCI_AUTOCACTIVE,0,0);
				break;	
			case 209: /*AutocPosStart*/
				retint=ScMethod(SCI_AUTOCPOSSTART,0,0);
				break;	
			case 210: /*AutocComplete*/
				retint=ScMethod(SCI_AUTOCCOMPLETE,0,0);
				break;	
			case 211: /*AutocStops*/
				retint=ScMethod(SCI_AUTOCSTOPS,0,(int)pos);
				break;	
			case 212: /*AutocSetSeparator*/
				retint=ScMethod(SCI_AUTOCSETSEPARATOR,atoipos,0);
				break;	
			case 213: /*AutocGetSeparator*/
				retint=ScMethod(SCI_AUTOCGETSEPARATOR,0,0);
				break;	
			case 214: /*AutocSelect*/
				retint=ScMethod(SCI_AUTOCSELECT,0,(int)pos);
				break;	
			case 215: /*AutocSetCancelAtStart*/
				retint=ScMethod(SCI_AUTOCSETCANCELATSTART,atoipos,0);
				break;	
			case 216: /*AutocGetCancelAtStart*/
				retint=ScMethod(SCI_AUTOCGETCANCELATSTART,0,0);
				break;	
			case 217: /*AutocSetFillUps*/
				retint=ScMethod(SCI_AUTOCSETFILLUPS,0,(int)pos);
				break;	
			case 218: /*AutocSetChooseSingle*/
				retint=ScMethod(SCI_AUTOCSETCHOOSESINGLE,atoipos,0);
				break;	
			case 219: /*AutocGetChooseSingle*/
				retint=ScMethod(SCI_AUTOCGETCHOOSESINGLE,0,0);
				break;	
			case 220: /*AutocSetIgnoreCase*/
				retint=ScMethod(SCI_AUTOCSETIGNORECASE,atoipos,0);
				break;	
			case 221: /*AutocGetIgnoreCase*/
				retint=ScMethod(SCI_AUTOCGETIGNORECASE,0,0);
				break;	
			case 222: /*AutocSetAutoHide*/
				retint=ScMethod(SCI_AUTOCSETAUTOHIDE,atoipos,0);
				break;	
			case 223: /*AutocGetAutoHide*/
				retint=ScMethod(SCI_AUTOCGETAUTOHIDE,0,0);
				break;	
			case 224: /*AutocSetDropRestOfWord*/
				retint=ScMethod(SCI_AUTOCSETDROPRESTOFWORD,atoipos,0);
				break;	
			case 225: /*AutocGetDropRestOfWord*/
				retint=ScMethod(SCI_AUTOCGETDROPRESTOFWORD,0,0);
				break;	
			case 226: /*AutocSetTypeSeparator*/
				retint=ScMethod(SCI_AUTOCSETTYPESEPARATOR,atoipos,0);
				break;	
			case 227: /*AutocGetTypeSeparator*/
				retint=ScMethod(SCI_AUTOCGETTYPESEPARATOR,0,0);
				break;	
			case 228: /*ClearRegisteredImages*/
				retint=ScMethod(SCI_CLEARREGISTEREDIMAGES,0,0);
				break;	
			case 229: /*RegisterImage type,xpm*/
				{
					const char *postmp=strchr(pos,',');
					if (postmp++ && *postmp) 
						retint=ScMethod(SCI_REGISTERIMAGE,atoipos,(int)postmp);
				}
				break;	
			case 231: /*CallTipShow*/
				{
					const char *pos2=strchr(pos,',');
					if (pos2++==NULL) pos2="";
					retint=ScMethod(SCI_CALLTIPSHOW,atoipos,(int)pos2);
				}
				break;	
			case 232: /*CallTipCancel*/
				retint=ScMethod(SCI_CALLTIPCANCEL,0,0);
				break;	
			case 233: /*CallTipActive*/
				retint=ScMethod(SCI_CALLTIPACTIVE,0,0);
				break;	
			case 234: /*CallTipPosStart*/
				retint=ScMethod(SCI_CALLTIPPOSSTART,0,0);
				break;	
			case 235: /*CallTipSetHlt*/
				{
					int highlightStart=0,highlightEnd=0;
					m_LastScanf=sscanf(pos,"%d,%d",&highlightStart,&highlightEnd);
					retint=ScMethod(SCI_CALLTIPSETHLT,highlightStart,highlightEnd);
				}
				break;	
			case 236: /*CallTipSetBack*/
			case 237: /*CallTipSetFore*/
			case 238: /*CallTipSetForehlt*/
				{
					int r=0,g=0,b=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d",&r,&g,&b);
					switch(nfunc)
					{
					case 236: /*CallTipSetBack*/
						retint=ScMethod(SCI_CALLTIPSETBACK,RGB(r,g,b),0);
						break;	
					case 237: /*CallTipSetFore*/
						retint=ScMethod(SCI_CALLTIPSETFORE,RGB(r,g,b),0);
						break;	
					case 238: /*CallTipSetForehlt*/
						retint=ScMethod(SCI_CALLTIPSETFOREHLT,RGB(r,g,b),0);
						break;	
					}
				}
				break;	
			case 239: /*UsePopup*/
				retint=ScMethod(SCI_USEPOPUP,atoipos,0);
				break;	
			case 240: /*StartRecord*/
				retint=ScMethod(SCI_STARTRECORD,0,0);
				break;	
			case 241: /*StopRecord*/
				retint=ScMethod(SCI_STOPRECORD,0,0);
				break;
			case 242: /*ColorsDialogLex*/
				{
					retint=IDCANCEL;
					if (m_hWnd)
					{
						CDlgEditorColor dlg;
						dlg.SetEditor(this);
						DWORD m_CurLexer=ScMethod(SCI_GETLEXER,0,0);
						dlg.LoadColors(m_CurLexer,*pos?pos:NULL);

						if ((retint=dlg.DoModal())==IDOK)
						{
							dlg.SaveColors(m_CurLexer,*pos?pos:NULL);
							LoadColors(m_CurLexer,*pos?pos:NULL);
						}
					}
				}
				break;	
			case 243: /*SetPrintMagnification*/
				retint=ScMethod(SCI_SETPRINTMAGNIFICATION,atoipos,0);
				EditorPrintSettings.m_Magnification=atoipos;
				break;	
			case 244: /*GetPrintMagnification*/
				retint=ScMethod(SCI_GETPRINTMAGNIFICATION,0,0);
				break;	
			case 245: /*SetPrintColorMode*/
				{
					int PrintMode=atoipos;
					if (PrintMode==0)
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						_strupr(pos333);
						UINT i;
						for(i=0;i<GPScintilla::uNPrintMode;i++)
							if (strcmp(pos333,GPScintilla::cArrPrintMode[i])==0)
							{
								PrintMode=GPScintilla::uArrPrintMode[i];
								break;
							}
						delete[] pos333;
					}
					retint=ScMethod(SCI_SETPRINTCOLOURMODE,PrintMode,0);
					EditorPrintSettings.m_ColorType=PrintMode;
				}
				break;	
			case 246: /*GetPrintColorMode*/
				if (oStr)
				{
					retint=ScMethod(SCI_GETPRINTCOLOURMODE,0,0);
					UINT i;
					for(i=0;i<GPScintilla::uNPrintMode && *oStr==0;i++)
						if (retint==(int)GPScintilla::uArrPrintMode[i])
							strcpy(oStr,GPScintilla::cArrPrintMode[i]);
				}
				break;	
			case 247: /*SetPrintWrapMode*/
				{
					int WrapMode=atoipos;
					if (WrapMode==0)
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						_strupr(pos333);
						UINT i;
						for(i=0;i<GPScintilla::uNWrapMode;i++)
							if (strcmp(pos333,GPScintilla::cArrWrapMode[i])==0)
							{
								WrapMode=GPScintilla::uArrWrapMode[i];
								break;
							}
						delete[] pos333;
					}
					retint=ScMethod(SCI_SETPRINTWRAPMODE,WrapMode,0);
					EditorPrintSettings.m_UseWordWrap=WrapMode;

				}
				break;	
			case 248: /*GetPrintWrapMode*/
				if (oStr)
				{
					retint=ScMethod(SCI_GETPRINTWRAPMODE,0,0);
					UINT i;
					for(i=0;i<GPScintilla::uNWrapMode && *oStr==0;i++)
						if (retint==(int)GPScintilla::uArrWrapMode[i])
							strcpy(oStr,GPScintilla::cArrWrapMode[i]);
				}
				break;	
			case 249: /*VisibleFromDocline*/
				if (atoipos<0 || *pos==0)	atoipos=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
				retint=ScMethod(SCI_VISIBLEFROMDOCLINE,atoipos,0);
				break;	
			}
		}
	}
	else
	if (nfunc<1000)
	{
		if (nfunc<380)
		{
			switch(nfunc)
			{
			case 250: /*DoclineFromVisible*/
				retint=ScMethod(SCI_DOCLINEFROMVISIBLE,atoipos,0);
				break;	
			case 251: /*ShowLines*/
				{
					int lineStart=0,lineEnd=0;
					m_LastScanf=sscanf(pos,"%d,%d",&lineStart,&lineEnd);
					retint=ScMethod(SCI_SHOWLINES,lineStart,lineEnd);
				}
				break;	
			case 252: /*HideLines*/
				{
					int lineStart=0,lineEnd=0;
					m_LastScanf=sscanf(pos,"%d,%d",&lineStart,&lineEnd);
					if (lineStart<0)	lineStart=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
					if (lineEnd<0)	lineEnd=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
					retint=ScMethod(SCI_HIDELINES,lineStart,lineEnd);
				}
				break;	
			case 253: /*GetLineVisible*/
				if (atoipos<0 || *pos==0)	atoipos=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
				retint=ScMethod(SCI_GETLINEVISIBLE,atoipos,0);
				break;	
			case 254: /*SetFoldLevel*/
				{
					int line=0,level=0;
					m_LastScanf=sscanf(pos,"%d,%d",&line,&level);
					if (line<0)	line=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
					if (level==0)
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						_strupr(pos333);
						UINT i;
						for(i=0;i<GPScintilla::uNFoldLevel;i++)
							if (strcmp(pos333,GPScintilla::cArrFoldLevel[i])==0)
								level|=GPScintilla::uArrFoldLevel[i];
						delete[] pos333;
					}
					retint=ScMethod(SCI_SETFOLDLEVEL,line,level);
				}
				break;	
			case 255: /*GetFoldLevel*/
				{
					if (atoipos<0 || *pos==0)	atoipos=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
					retint=ScMethod(SCI_GETFOLDLEVEL,atoipos,0);
					UINT i;
					for(i=0;i<GPScintilla::uNFoldLevel;i++)
						if ((retint&GPScintilla::uArrFoldLevel[i])==GPScintilla::uArrFoldLevel[i])
						{
							if (*oStr) strcat(oStr,"|");
							strcat(oStr,GPScintilla::cArrFoldLevel[i]);
						}
				}
				break;	
			case 256: /*SetFoldFlags*/
				{
					int FoldFlag=atoipos;
					if (FoldFlag==0)
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						_strupr(pos333);
						UINT i;
						for(i=0;i<GPScintilla::uNFoldFlag;i++)
							if (strcmp(pos333,GPScintilla::cArrFoldFlag[i])==0)
							{
								FoldFlag=GPScintilla::uArrFoldFlag[i];
								break;
							}
						delete[] pos333;
					}
					retint=ScMethod(SCI_SETFOLDFLAGS,FoldFlag,0);
				}
				break;	
			case 257: /*GetLastChild*/
				{
					int line=0,level=0;
					m_LastScanf=sscanf(pos,"%d,%d",&line,&level);
					if (line<0)	line=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
					retint=ScMethod(SCI_GETLASTCHILD,line,level);
				}
				break;	
			case 258: /*GetFoldParent*/
				if (atoipos<0 || *pos==0)	atoipos=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
				retint=ScMethod(SCI_GETFOLDPARENT,atoipos,0);
				break;	
			case 259: /*SetFoldExpanded*/
				{
					int line=0,expanded=0;
					m_LastScanf=sscanf(pos,"%d,%d",&line,&expanded);
					if (line<0)	line=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
					retint=ScMethod(SCI_SETFOLDEXPANDED,line,expanded);
				}
				break;	
			case 260: /*GetFoldExpanded*/
				if (atoipos<0 || *pos==0)	atoipos=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
				retint=ScMethod(SCI_GETFOLDEXPANDED,atoipos,0);
				break;	
			case 261: /*ToggleFold*/
				if (atoipos<0 || *pos==0)	atoipos=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
				retint=ScMethod(SCI_TOGGLEFOLD,atoipos,0);
				break;	
			case 262: /*EnsureVisible*/
				if (atoipos<0 || *pos==0)	atoipos=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
				retint=ScMethod(SCI_ENSUREVISIBLE,atoipos,0);
				break;	
			case 263: /*EnsureVisibleEnforcePolicy*/
				retint=ScMethod(SCI_ENSUREVISIBLEENFORCEPOLICY,atoipos,0);
				break;	
			case 264: /*SetWrapMode*/
				{
					int WrapMode=atoipos;
					if (WrapMode==0)
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						_strupr(pos333);
						UINT i;
						for(i=0;i<GPScintilla::uNWrapMode;i++)
							if (strcmp(pos333,GPScintilla::cArrWrapMode[i])==0)
							{
								WrapMode=GPScintilla::uArrWrapMode[i];
								break;
							}
						delete[] pos333;
					}
					retint=ScMethod(SCI_SETWRAPMODE,WrapMode,0);
				}
				break;	
			case 265: /*GetWrapMode*/
				if (oStr)
				{
					retint=ScMethod(SCI_GETWRAPMODE,0,0);
					UINT i;
					for(i=0;i<GPScintilla::uNWrapMode && *oStr==0;i++)
						if (retint==(int)GPScintilla::uArrWrapMode[i])
							strcpy(oStr,GPScintilla::cArrWrapMode[i]);
				}
				break;	
			case 266: /*SetLayoutCache*/
				{
					int CacheMode=atoipos;
					if (CacheMode==0)
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						_strupr(pos333);
						UINT i;
						for(i=0;i<GPScintilla::uNCacheMode;i++)
							if (strcmp(pos333,GPScintilla::cArrCacheMode[i])==0)
							{
								CacheMode=GPScintilla::uArrCacheMode[i];
								break;
							}
						delete[] pos333;
					}
					retint=ScMethod(SCI_SETLAYOUTCACHE,CacheMode,0);
				}
				break;	
			case 267: /*GetLayoutCache*/
				if (oStr)
				{
					retint=ScMethod(SCI_GETLAYOUTCACHE,0,0);
					UINT i;
					for(i=0;i<GPScintilla::uNCacheMode && *oStr==0;i++)
						if (retint==(int)GPScintilla::uArrCacheMode[i])
							strcpy(oStr,GPScintilla::cArrCacheMode[i]);
				}
				break;	
			case 268: /*LinesSplit*/
				retint=ScMethod(SCI_LINESSPLIT,atoipos,0);
				break;	
			case 269: /*LinesJoin*/
				retint=ScMethod(SCI_LINESJOIN,atoipos,0);
				break;	
			case 270: /*ZoomIn*/
				retint=ScMethod(SCI_ZOOMIN,0,0);
				break;	
			case 271: /*ZoomOut*/
				retint=ScMethod(SCI_ZOOMOUT,0,0);
				break;	
			case 272: /*SetEdgeMode*/
				{
					int EdgeMode=atoipos;
					if (EdgeMode==0)
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						_strupr(pos333);
						UINT i;
						for(i=0;i<GPScintilla::uNEdgeMode;i++)
							if (strcmp(pos333,GPScintilla::cArrEdgeMode[i])==0)
							{
								EdgeMode=GPScintilla::uArrEdgeMode[i];
								break;
							}
						delete[] pos333;
					}
					retint=ScMethod(SCI_SETEDGEMODE,EdgeMode,0);
				}
				break;	
			case 273: /*GetEdgeMode*/
				if (oStr)
				{
					retint=ScMethod(SCI_GETEDGEMODE,0,0);
					UINT i;
					for(i=0;i<GPScintilla::uNEdgeMode && *oStr==0;i++)
						if (retint==(int)GPScintilla::uArrEdgeMode[i])
							strcpy(oStr,GPScintilla::cArrEdgeMode[i]);
				}
				break;	
			case 274: /*SetEdgeColumn*/
				retint=ScMethod(SCI_SETEDGECOLUMN,atoipos,0);
				break;	
			case 275: /*GetEdgeColumn*/
				retint=ScMethod(SCI_GETEDGECOLUMN,0,0);
				break;	
			case 276: /*SetEdgeColor*/
				{
					int r=0,g=0,b=0;
					m_LastScanf=sscanf(pos,"%d,%d,%d",&r,&g,&b);
					retint=ScMethod(SCI_SETEDGECOLOUR,RGB(r,g,b),0);
				}
				break;	
			case 277: /*GetEdgeColor*/
				retint=ScMethod(SCI_GETEDGECOLOUR,0,0);
				sprintf(oStr,"%d\x7F%d\x7F%d",GetRValue(retint),GetGValue(retint),GetBValue(retint));
				break;	
			case 278: /*SetLexer*/
				{
					int Lexer=atoipos;
					if (Lexer==0)
					{
						char *pos333=new char [(int)strlen(pos)+2];
						strcpy(pos333,pos);
						_strupr(pos333);
						UINT i;
						for(i=0;*GPScintilla::cArrLexer[i];i++)
							if (strcmp(pos333,GPScintilla::cArrLexer[i])==0)
							{
								Lexer=GPScintilla::uArrLexer[i];
								if (Lexer==SCLEX_MVITEM || Lexer==SCLEX_MVTEXT) retint=ScMethod(SCI_SETWRAPMODE,SC_WRAP_WORD,0);
								break;
							}
						delete[] pos333;
					}
					retint=ScMethod(SCI_SETLEXER,Lexer,0);
					LoadColors(Lexer,NULL);
					ScMethod(SCI_COLOURISE,0,-1);
				}
				break;	
			case 279: /*GetLexer*/
				if (oStr)
				{
					retint=ScMethod(SCI_GETLEXER,0,0);
					UINT i;
					for(i=0;*GPScintilla::cArrLexer[i] && *oStr==0;i++)
						if (retint==(int)GPScintilla::uArrLexer[i])
							strcpy(oStr,GPScintilla::cArrLexer[i]);
				}
				break;	
			case 280: /*SetLexerLanguage*/
				{
					retint=ScMethod(SCI_GETLEXER,0,0);
					ScMethod(SCI_SETLEXERLANGUAGE,0,(int)pos);
					if (oStr) sprintf(oStr,"%d\x7F%d",retint,ScMethod(SCI_GETLEXER,0,0));
				}
				break;	
			case 281: /*LoadLexerLibrary*/
				retint=ScMethod(SCI_LOADLEXERLIBRARY,0,(int)pos);
				break;	
			case 282: /*Colorise*/
				{
					int start=0,end=0;
					m_LastScanf=sscanf(pos,"%d,%d",&start,&end);
					retint=ScMethod(SCI_COLOURISE,start,end);
				}
				break;	
			case 283: /*SetProperty*/
				{
					char *pos333=new char [(int)strlen(pos)+2];
					strcpy(pos333,pos);
					char *pos2=strchr(pos333,',');
					if (pos2) *(pos2++)=0;
					else pos2="";
					retint=ScMethod(SCI_SETPROPERTY,(int)pos333,(int)pos2);
					delete[] pos333;
				}
				break;	
			case 284: /*SetKeywords*/
				{
					char *pos333=new char [(int)strlen(pos)+2];
					strcpy(pos333,pos);
					char *pos2=strchr(pos333,',');
					if (pos2) *(pos2++)=0;
					else pos2="";
					retint=ScMethod(SCI_SETKEYWORDS,atoipos,(int)pos2);
					delete[] pos333;
				}
				break;	
			case 285: /*GetEndStyled*/
				retint=ScMethod(SCI_GETENDSTYLED,0,0);
				break;	
			case 286: /*StartStyling*/
				{
					int position=0,mask=0;
					m_LastScanf=sscanf(pos,"%d,%d",&position,&mask);
					retint=ScMethod(SCI_STARTSTYLING,position,mask);
				}
				break;	
			case 287: /*SetStyLing*/
				{
					int length=1,style=0;
					m_LastScanf=sscanf(pos,"%d,%d",&length,&style);
					retint=ScMethod(SCI_SETSTYLING,length,style);
				}
				break;	
			case 288: /*SetStylingEx*/
				{
					retint=-1;
					char stl[110];
					const char *pos2=strchr(pos,',');
					if (pos2)
					{
						int i=0;
						while(pos2 && *pos2 && i<100)
						{
							pos2++;stl[i++]=(char)atoi(pos2);
							pos2=strchr(pos2,',');
						}
						for(;i<110;i++) stl[i]=0;
						retint=ScMethod(SCI_SETSTYLINGEX,atoipos,(int)stl);
					}
				}
				break;	
			case 289: /*SetLineState*/
				{
					int line=0,style=0;
					m_LastScanf=sscanf(pos,"%d,%d",&line,&style);
					if (line<0)	line=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
					retint=ScMethod(SCI_SETLINESTATE,line,style);
				}
				break;	
			case 290: /*GetLineState*/
				if (atoipos<0 || *pos==0)	atoipos=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
				retint=ScMethod(SCI_GETLINESTATE,atoipos,0);
				break;	
			case 291: /*GetMaxLineState*/
				retint=ScMethod(SCI_GETMAXLINESTATE,0,0);
				break;	
			case 292: /*StyleResetDefault*/
				retint=ScMethod(SCI_STYLERESETDEFAULT,0,0);
				break;	
			case 293: /*StyleClearAll*/
				retint=ScMethod(SCI_STYLECLEARALL,0,0);
				break;	
			case 294: /*StyleSetFont*/
			case 295: /*StyleSetSize*/
			case 296: /*StyleSetBold*/
			case 297: /*StyleSetItalic*/
			case 298: /*StyleSetUnderline*/
			case 299: /*StyleSetFore*/
			case 300: /*StyleSetBack*/
			case 301: /*StyleSetEOLFilled*/
			case 302: /*StyleSetCharacterSet*/
			case 303: /*StyleSetCase*/
			case 304: /*StyleSetVisible*/
			case 305: /*StyleSetChangeable*/
			case 306: /*StyleSetHotspot*/
			case 314: /*StyleGetFore*/
			case 315: /*StyleGetBack*/
			case 316: /*StyleGetInfo*/
			case 317: /*StyleGetFont*/
			case 318: /*StyleGetSize*/
			case 319: /*StyleGetBold*/
			case 320: /*StyleGetItalic*/
			case 321: /*StyleGetUnderline*/
			case 322: /*StyleGetVisible*/
			case 323: /*StyleGetEOLFilled*/
			case 324: /*StyleGetCase*/
			case 325: /*StyleGetCharacterSet*/
			case 326: /*StyleGetHOTSPOT*/
				{
					int StyleType=atoipos;
					char *pos333=new char [(int)strlen(pos)+2];
					strcpy(pos333,pos);
					char *pos2=strchr(pos333,',');
					if (pos2 && *pos2) *(pos2++)=0;
					else pos2="";
					if (StyleType==0)
					{
						_strupr(pos333);
						UINT i;
						for(i=0;i<GPScintilla::uNStyleType;i++)
							if (strcmp(pos333,GPScintilla::cArrStyleType[i])==0)
							{
								StyleType=GPScintilla::uArrStyleType[i];
								break;
							}
					}
					switch(nfunc)
					{
					case 294: /*StyleSetFont*/
						retint=ScMethod(SCI_STYLESETFONT,StyleType,(int)pos2);
						break;
					case 295: /*StyleSetSize*/
						retint=ScMethod(SCI_STYLESETSIZE,StyleType,atoi(pos2));
						break;
					case 296: /*StyleSetBold*/
						retint=ScMethod(SCI_STYLESETBOLD,StyleType,atoi(pos2));
						break;
					case 297: /*StyleSetItalic*/
						retint=ScMethod(SCI_STYLESETITALIC,StyleType,atoi(pos2));
						break;
					case 298: /*StyleSetUnderline*/
						retint=ScMethod(SCI_STYLESETUNDERLINE,StyleType,atoi(pos2));
						break;
					case 299: /*StyleSetFore*/
						{
							int r=0,g=0,b=0;
							m_LastScanf=sscanf(pos2,"%d,%d,%d",&r,&g,&b);
							retint=ScMethod(SCI_STYLESETFORE,StyleType,RGB(r,g,b));
						}
						break;	
					case 300: /*StyleSetBack*/
						{
							int r=0,g=0,b=0;
							m_LastScanf=sscanf(pos2,"%d,%d,%d",&r,&g,&b);
							retint=ScMethod(SCI_STYLESETBACK,StyleType,RGB(r,g,b));
						}
						break;	
					case 301: /*StyleSetEOLFilled*/
						retint=ScMethod(SCI_STYLESETEOLFILLED,StyleType,atoi(pos2));
						break;
					case 302: /*StyleSetCharacterSet*/
						{
							int CharSet=atoi(pos2);
							if (CharSet==0)
							{
								_strupr(pos2);
								UINT i;
								for(i=0;i<GPScintilla::uNCharSet;i++)
									if (strcmp(pos2,GPScintilla::cArrCharSet[i])==0)
									{
										CharSet=GPScintilla::uArrCharSet[i];
										break;
									}
							}
							retint=ScMethod(SCI_STYLESETCHARACTERSET,StyleType,CharSet);
						}
						break;	
					case 303: /*StyleSetCase*/
						{
							int CaseType=atoi(pos2);
							if (CaseType==0)
							{
								_strupr(pos2);
								UINT i;
								for(i=0;i<GPScintilla::uNCaseType;i++)
									if (strcmp(pos2,GPScintilla::cArrCaseType[i])==0)
									{
										CaseType=GPScintilla::uArrCaseType[i];
										break;
									}
							}
							retint=ScMethod(SCI_STYLESETCASE,StyleType,CaseType);
						}
						break;	
					case 304: /*StyleSetVisible*/
						retint=ScMethod(SCI_STYLESETVISIBLE,StyleType,atoi(pos2));
						break;
					case 305: /*StyleSetChangeable*/
						retint=ScMethod(SCI_STYLESETCHANGEABLE,StyleType,atoi(pos2));
						break;
					case 306: /*StyleSetHotspot*/
						retint=ScMethod(SCI_STYLESETHOTSPOT,StyleType,atoi(pos2));
						break;
					case 314: /*StyleGetFore*/
						retint=ScMethod(SCI_STYLEGETFORE,StyleType,0);
						if (oStr) sprintf(oStr,"%d\x07%d\x07%d",GetRValue(retint),GetGValue(retint),GetBValue(retint));
						break;	
					case 315: /*StyleGetBack*/
						retint=ScMethod(SCI_STYLEGETBACK,StyleType,0);
						if (oStr) sprintf(oStr,"%d\x07%d\x07%d",GetRValue(retint),GetGValue(retint),GetBValue(retint));
						break;	
					case 316: /*StyleGetInfo*/
						if (oStr)
						{
							GPSCSTYLESET gpsc;
							GetStyleInfo(StyleType,gpsc);
							StyleInfoToString(gpsc);
						}
						break;	
					case 317: /*StyleGetFont*/
						retint=ScMethod(SCI_STYLEGETFONT,StyleType,0);
						break;	
					case 318: /*StyleGetSize*/
						retint=ScMethod(SCI_STYLEGETSIZE,StyleType,0);
						break;	
					case 319: /*StyleGetBold*/
						retint=ScMethod(SCI_STYLEGETBOLD,StyleType,0);
						break;	
					case 320: /*StyleGetItalic*/
						retint=ScMethod(SCI_STYLEGETITALIC,StyleType,0);
						break;	
					case 321: /*StyleGetUnderline*/
						retint=ScMethod(SCI_STYLEGETUNDERLINE,StyleType,0);
						break;	
					case 322: /*StyleGetVisible*/
						retint=ScMethod(SCI_STYLEGETVISIBLE,StyleType,0);
						break;	
					case 323: /*StyleGetEOLFilled*/
						retint=ScMethod(SCI_STYLEGETEOLFILLED,StyleType,0);
						break;	
					case 324: /*StyleGetCase*/
						retint=ScMethod(SCI_STYLEGETCASE,StyleType,0);
						break;	
					case 325: /*StyleGetCharacterSet*/
						retint=ScMethod(SCI_STYLEGETCHARACTERSET,StyleType,0);
						break;	
					case 326: /*StyleGetHOTSPOT*/
						retint=ScMethod(SCI_STYLEGETHOTSPOT,StyleType,0);
						break;	
					}
					delete[] pos333;
				}
				break;	
			case 307: /*SetMouseDwellTime*/
				retint=ScMethod(SCI_SETMOUSEDWELLTIME,atoipos,0);
				break;	
			case 308: /*GetMouseDwellTime*/
				retint=ScMethod(SCI_GETMOUSEDWELLTIME,0,0);
				break;	
			case 309: /*SetUsePalette*/
				retint=ScMethod(SCI_SETUSEPALETTE,atoipos,0);
				break;	
			case 310: /*GetUsePalette*/
				retint=ScMethod(SCI_GETUSEPALETTE,0,0);
				break;	
			case 311: /*Initialize*/
				{
					const char *pos2=strchr(pos,',');
					if ((pos2++)==NULL) pos2="Courier New";
					if (atoipos==0) atoipos=10;

					ScMethod(SCI_SETSTYLEBITS, 7,0);

					ScMethod(SCI_SETKEYWORDS, 0,reinterpret_cast<LPARAM>(pbKeyWords));
					ScMethod(SCI_SETKEYWORDS, 1,reinterpret_cast<LPARAM>(gpKeyWords));
					ScMethod(SCI_SETKEYWORDS, 2,reinterpret_cast<LPARAM>(fsKeyWords));

					SetAStyle(STYLE_DEFAULT, 0, 0xFFFFFF, atoipos, pos2);
					ScMethod(SCI_STYLECLEARALL,0,0);	// Copies global style to all others

					SetAStyle(SCE_PB_DEFAULT,		0x000000, 0xFFFFFF, atoipos, pos2);
					SetAStyle(SCE_PB_COMMENT,		0x00ff00, 0xBBEEEE, atoipos, pos2);
					SetAStyle(SCE_PB_NUMBER,		0xffff00, 0xFFFFFF, atoipos, pos2);
					SetAStyle(SCE_PB_KEYWORD,		0xFF0000, 0xFFFFFF, atoipos, pos2);
					SetAStyle(SCE_PB_STRING,		0x00ffff, 0xFFFFFF, atoipos, pos2);
					SetAStyle(SCE_PB_OPERATOR,		0x00ff00, 0xFFFFFF, atoipos, pos2);
					SetAStyle(SCE_PB_IDENTIFIER,	0xff00ff, 0xFFFFFF, atoipos, pos2);
					SetAStyle(SCE_PB_ERROR,			0x0000ff, 0xEEEEEE, atoipos, pos2);
					SetAStyle(SCE_PB_SUBROUTINE,	0x0000ff, 0xFF00FF, atoipos, pos2);
				}
				break;	
			case 312: /*SetAStyle*/
				{
					DWORD style=0;
					int Rfore=0,Gfore=0,Bfore=0,Rback=255,Gback=255,Bback=255,size=-1;
					char *face=NULL;
					char *pos333=new char [(int)strlen(pos)+2];
					strcpy(pos333,pos);
					char *pos2=strchr(pos333,',');
					if (pos2) *(pos2++)=0;
					else pos2="";
					m_LastScanf=sscanf(pos2,"%d,%d,%d,%d,%d,%d,%d",&Rfore,&Gfore,&Bfore,&Rback,&Gback,&Bback,&size);
					SetAStyle(style,RGB(Rfore,Gfore,Bfore),RGB(Rback,Gback,Bback),size,face);
					delete[] pos333;
				}
				break;	
			case 313: /*ColorsDialog */
				{
					//1,S=0;S=1;S=2;S=3;S=4;S=5;S=6;S=7;S=8;S=9;S=10;S=32;S=33;S=34;S=35;S=36;S=37;S=38;S=39;
					const char *pos2=strchr(pos,',');
					if (pos2++==NULL) pos2="";
					if (*pos2)
					{
						const char *tmp=pos2;
						UINT nClr=1;
						while(*tmp)
							if (*(tmp++)==';' && tmp[1]) nClr++;

						UINT nField=0;
						GPSCSTYLESET *cs=new GPSCSTYLESET[nClr+2];
						CString fld;
						while(nField<=nClr && (fld=ExtractField(pos2,nField+1,";"))!="")
						{
							StringToStyleInfo(fld,cs[nField]);
							GetStyleInfo(cs[nField].id,cs[nField]);
							StringToStyleInfo(fld,cs[nField]);
							nField++;
						}
						CDlgEditorColor dlg;
						dlg.SetColors(cs,nField);
						if (atoipos) dlg.SetEditor(this);
						if (dlg.DoModal()==IDOK)
						{
							if (oStr)
							{
								char *posout=oStr;
								dlg.GetColors(cs);
								UINT i;
								for(i=0;i<=nField;i++)
								{
									CString tmps=StyleInfoToString(cs[i]);
									tmps.Replace("\x07","\x02");
									tmps.Replace("\x7F","\x01");
									if (i) posout+=(int)strlen(strcpy(posout,"\x7F"));
									posout+=(int)strlen(strcpy(posout,tmps));
								}
							}
						}
						else
							if (oStr)
								strcpy(oStr,"CANCEL");
						delete[] cs;
					}
				}
				break;	
			case 327: /*SetAStyleEx*/
				{
					GPSCSTYLESET cs;
					CString fld;
					retint=0;
					while((fld=ExtractField(pos,retint+1,";"))!="")
					{
						retint++;
						StringToStyleInfo(fld,cs);
						SetStyleInfo(cs);
					}
				}
				break;	
			case 328: /*GetWhiteSpaceFore*/
				if (oStr)
				{
					retint=ScMethod(SCI_GETWHITESPACEFORE,0,0);
					sprintf(oStr,"%d\x7F%d\x7F%d",GetRValue(retint),GetGValue(retint),GetBValue(retint));
				}
				break;	
			case 329: /*GetWhiteSpaceBack*/
				if (oStr)
				{
					retint=ScMethod(SCI_GETWHITESPACEBACK,0,0);
					sprintf(oStr,"%d\x7F%d\x7F%d",GetRValue(retint),GetGValue(retint),GetBValue(retint));
				}
				break;	
			case 330: /*GetUseWhiteSpaceFore*/
				retint=ScMethod(SCI_GETUSEWHITESPACEFORE,0,0);
				break;	
			case 331: /*GetUseWhiteSpaceBack*/
				retint=ScMethod(SCI_GETUSEWHITESPACEBACK,0,0);
				break;	
			case 332: /*SetUseWhiteSpaceFore*/
				retint=ScMethod(SCI_SETUSEWHITESPACEFORE,atoipos,0);
				break;	
			case 333: /*SetUseWhiteSpaceBack*/
				retint=ScMethod(SCI_SETUSEWHITESPACEBACK,atoipos,0);
				break;	
			case 334: /*Sort*/
				{
					DWORD Options=0;
					CString flg=pos;
					flg.MakeUpper();
					if (flg.Find("W")>=0) Options|=SC_SORT_WORDS;
					if (flg.Find("U")>=0) Options|=SC_SORT_UNIQUE;
					if (flg.Find("DE")>=0) Options|=SC_SORT_DESC;

					SortText(Options);
				}
				break;	
			case 335: /*LoadText Flags,FileName*/
				{
					DWORD uFlag=0;
					CString fName=ExtractField(pos,1,",");
					if (fName=="") fName=" ";
					uFlag=StringFromToReplaceStyle(fName,uFlag);
					fName=FindField(pos,2,",");
					retint=LoadText(fName, uFlag);
				}
				break;	
			case 336: /*SaveText Flags,FileName*/
				{
					DWORD uFlag=0;
					CString fName=ExtractField(pos,1,",");
					if (fName=="") fName=" ";
					uFlag=StringFromToSaveStyle(fName,uFlag);
					fName=FindField(pos,2,",");
					retint=SaveText(fName, uFlag);
				}
				break;	
			case 337: /*LoadKeywords LexerName*/
				retint=LoadKeywords(GPScintilla::GetLexerId(pos));
				break;	
			case 338: /*SaveKeywords LexerName*/
				retint=SaveKeywords(GPScintilla::GetLexerId(pos));
				break;	
			case 339: /*LoadColors LexerName,FileName*/
				retint=LoadColors(GPScintilla::GetLexerId(ExtractField(pos,1,",")),FindField(pos,2,","));
				break;	
			case 340: /*SetDirectInput*/
				retint=m_DirectInputFlag;
				m_DirectInputFlag=atoipos;
				break;	
			case 341: /*GetDirectInput*/
				retint=m_DirectInputFlag;
				break;	
			case 342: /*GetMarkerBack*/
				retint=ScMethod(SCI_MARKERGETBACK,atoipos,0);
				if (oStr) sprintf(oStr,"%d\x07%d\x07%d",GetRValue(retint),GetGValue(retint),GetBValue(retint));
				break;	
			case 343: /*GetMarkerFore*/
				retint=ScMethod(SCI_MARKERGETFORE,atoipos,0);
				if (oStr) sprintf(oStr,"%d\x07%d\x07%d",GetRValue(retint),GetGValue(retint),GetBValue(retint));
				break;	
			case 344: /*GetMarkerDefine*/
				retint=ScMethod(SCI_MARKERGETDEFINE,atoipos,0);
				break;	
			case 345: /*SetLineObject*/		LineObjId=atoipos;		break;
			case 346: /*SetColumnObject*/	ColumnObjId=atoipos;	break;
			case 347: /*SetLinePrefix*/		LinePrefix=pos;			break;
			case 348: /*SetColumnPrefix*/	ColumnPrefix=pos;		break;
			case 349: /*SetCharObject*/		CharObjId=atoipos;		break;
			case 350: /*SetCharPrefix*/		CharPrefix=pos;			break;
			case 351: /*GetCurrentMarker*/
				retint=m_CurMarkerType;
				break;	
			case 352: /*SetCurrentMarker*/
				retint=m_CurMarkerType;
				m_CurMarkerType=atoipos;
				break;	
			case 353: /*EnableContextMenu*/
			case 354: /*IsEnableContextMenu*/
				retint=m_EnableContextMenu;
				if (nfunc==353) m_EnableContextMenu=atoipos;
				break;
			case 355: /*ShowFindDialog*/
				retint=ShowFindDialog(*pos==0?1:atoipos);
				break;	
			case 356: /*LockHotKeys*/
				retint=(m_ProcHK&0x1);
				m_ProcHK&=(0xFFFFFFFE|(atoipos&0x1));
				break;	
			case 357: /*Print*/
				{
					DWORD flags=0;
					char *pos333=new char [(int)strlen(pos)+2];
					strcpy(pos333,ExtractField(pos,1,";"));
					_strupr(pos333);
					if (strstr(pos333,"DIALOG")) flags|=0x01;
					if (strstr(pos333,"SELECTION")) flags|=0x10;
					if (strstr(pos333,"FORMAT")) flags|=0x02;
					if (strstr(pos333,"NOHEADER")) flags|=0x100;
					if (strstr(pos333,"NOFOOTER")) flags|=0x200;
					Print(atoipos|flags,FindField(pos,2,";"));
					delete[] pos333;
				}
				break;	
			case 358: /*SetHeaderFormat*/
				if (oStr) strcpy(oStr,EditorPrintSettings.csheaderFormat);
				EditorPrintSettings.csheaderFormat=pos;
				break;	
			case 359: /*SetFooterFormat*/
				if (oStr) strcpy(oStr,EditorPrintSettings.csfooterFormat);
				EditorPrintSettings.csfooterFormat=pos;
				break;	
			case 360: /*GetHeaderFormat*/
				if (oStr) strcpy(oStr,EditorPrintSettings.csheaderFormat);
				break;	
			case 361: /*GetFooterFormat*/
				if (oStr) strcpy(oStr,EditorPrintSettings.csfooterFormat);
				break;	
			case 362: /*SetHeaderStyle*/
				if (oStr) strcpy(oStr,EditorPrintSettings.GetHeaderStyle());
				EditorPrintSettings.SetHeaderStyle(pos);
				break;	
			case 363: /*SetFooterStyle*/
				if (oStr) strcpy(oStr,EditorPrintSettings.GetFooterStyle());
				EditorPrintSettings.SetFooterStyle(pos);
				break;	
			case 364: /*GetHeaderStyle*/
				if (oStr) strcpy(oStr,EditorPrintSettings.GetHeaderStyle());
				break;	
			case 365: /*GetFooterStyle*/
				if (oStr) strcpy(oStr,EditorPrintSettings.GetFooterStyle());
				break;	
			case 366: /*SetHeaderUse*/
				retint=EditorPrintSettings.m_UseHeader;
				EditorPrintSettings.m_UseHeader=atoipos;
				break;	
			case 367: /*SetFooterUse*/
				retint=EditorPrintSettings.m_UseFooter;
				EditorPrintSettings.m_UseFooter=atoipos;
				break;	
			case 368: /*GetHeaderUse*/
				retint=EditorPrintSettings.m_UseHeader;
				break;	
			case 369: /*GetFooterUse*/
				retint=EditorPrintSettings.m_UseFooter;
				break;	
			case 370: /*PageSetup*/
				retint=EditorPrintSettings.SetupDlg();
				break;	
			case 371: /*TrimEndSpace*/
				{
					long nStartChar, nEndChar;
					long nEndChar2;
					nStartChar=ScMethod(SCI_GETSELECTIONSTART, FALSE, 0);
					nEndChar=ScMethod(SCI_GETSELECTIONEND, FALSE, 0);
					nEndChar2=ScMethod(SCI_GETTEXTLENGTH,0,0);

					if (nEndChar2>=0)
					{
						char *str=new char [nEndChar2*2+100];
						ScMethod(SCI_GETTEXT,nEndChar2+1,(int)str);
						char *poss=str;
						char *posd=str;
						char *postmp=NULL;
						int c=*poss;

						while(c)
						{
							c=*poss;
							if (c==' ' || c==9) 
							{
								if (postmp==NULL) postmp=posd;
							}
							else
							{
								if (postmp && (c==10 || c==13 || c==0)) posd=postmp;
								postmp=NULL;
							}
							*(posd++)=*(poss++);
						}
						ScMethod(SCI_SETTEXT,0,(int)str);
						delete[] str;
					}
				}
				break;	
			case 372: /*GetLexers*/
				if (oStr)
				{
					*oStr=0;
					char *posout=oStr+10;
					*posout=0;
					retint=0;
					DWORD curlex=ScMethod(SCI_GETLEXER,0,0);
					UINT i;
					for(i=0;*GPScintilla::cArrLexer[i];i++)
					{
						strcat(posout,"\x7F");
						posout+=sprintf(posout,"\x7F%s\x07%d",GPScintilla::cArrLexer[i],GPScintilla::uArrLexer[i]);
						if (GPScintilla::uArrLexer[i]==curlex)
							retint=i;
					}
					sprintf(oStr,"%d%s",retint,oStr+10);
				}
				break;	
			case 373: /*SetWhitespaceChars*/
				retint=ScMethod(SCI_SETWHITESPACECHARS,0,(int)pos);
				break;	
			case 374: /*SetCharsDefault*/
				retint=ScMethod(SCI_SETCHARSDEFAULT,0,0);
				break;	
			case 375: /*Allocate*/
				retint=ScMethod(SCI_ALLOCATE,atoipos,0);
				break;	
			case 376: /*SetWrapVisualFlags*/
				if (_stricmp(pos,"NONE")==0) atoipos=SC_WRAPVISUALFLAG_NONE;
					else
					if (_stricmp(pos,"END")==0) atoipos=SC_WRAPVISUALFLAG_END;
						else
						if (_stricmp(pos,"START")==0) atoipos=SC_WRAPVISUALFLAG_START;

				retint=ScMethod(SCI_SETWRAPVISUALFLAGS,atoipos,0);
				break;	
			case 377: /*GetWrapVisualFlags*/
				retint=ScMethod(SCI_GETWRAPVISUALFLAGS,0,0);
				break;	
			case 378: /*SetWrapVisualFlagsLocation*/
				if (_stricmp(pos,"DEFAULT")==0) atoipos=SC_WRAPVISUALFLAGLOC_DEFAULT;
					else
					if (_stricmp(pos,"END")==0) atoipos=SC_WRAPVISUALFLAGLOC_END_BY_TEXT;
						else
						if (_stricmp(pos,"START")==0) atoipos=SC_WRAPVISUALFLAGLOC_START_BY_TEXT;

				retint=ScMethod(SCI_SETWRAPVISUALFLAGSLOCATION,atoipos,0);
				break;	
			case 379: /*GetWrapVisualFlagsLocation*/
				retint=ScMethod(SCI_GETWRAPVISUALFLAGSLOCATION,0,0);
				break;	

			}
		}
		else
		if (nfunc<1000)
		{
			switch(nfunc)
			{
			case 380: /*SetWrapStartIndent*/
				retint=ScMethod(SCI_SETWRAPSTARTINDENT,atoipos,0);
				break;	
			case 381: /*GetWrapStartIndent*/
				retint=ScMethod(SCI_GETWRAPSTARTINDENT,0,0);
				break;	
			case 382: /*SetSelectionMode*/
				if (_stricmp(pos,"STREAM")==0) atoipos=SC_SEL_STREAM;
					else
					if (_stricmp(pos,"RECTANGLE")==0) atoipos=SC_SEL_RECTANGLE;
						else
						if (_stricmp(pos,"LINES")==0) atoipos=SC_SEL_LINES;

				retint=ScMethod(SCI_SETSELECTIONMODE,atoipos,0);
				break;	
			case 383: /*GetSelectionMode*/
				retint=ScMethod(SCI_GETSELECTIONMODE,0,0);
				break;	
			case 384: /*GetLineSelStartPosition*/
				if (atoipos<0 || *pos==0)	atoipos=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
				retint=ScMethod(SCI_GETLINESELSTARTPOSITION,atoipos,0);
				break;	
			case 385: /*GetLineSelEndPosition*/
				if (atoipos<0 || *pos==0)	atoipos=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
				retint=ScMethod(SCI_GETLINESELENDPOSITION,atoipos,0);
				break;	
			case 386: /*SetHotspotSingleLine*/
				retint=ScMethod(SCI_SETHOTSPOTSINGLELINE,atoipos,0);
				break;	
			case 387: /*AutocGetCurrent*/
				retint=ScMethod(SCI_AUTOCGETCURRENT,0,0);
				break;	
			case 388: /*InitFolding*/
				{
					ScMethod(SCI_SETPROPERTY, (WPARAM)"fold", (LPARAM)"1");
					ScMethod(SCI_SETPROPERTY, (WPARAM)"fold.compact", (LPARAM)"0");
					ScMethod(SCI_SETMARGINTYPEN,  MARGIN_SCRIPT_FOLD_INDEX, SC_MASK_FOLDERS);

					ScMethod(SCI_MARKERDEFINE, SC_MARKNUM_FOLDER, SC_MARK_PLUS);
					ScMethod(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPEN, SC_MARK_MINUS);
					ScMethod(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEREND, SC_MARK_EMPTY);
					ScMethod(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_EMPTY);
					ScMethod(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPENMID, SC_MARK_EMPTY);
					ScMethod(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERSUB, SC_MARK_EMPTY);
					ScMethod(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERTAIL, SC_MARK_EMPTY);
					ScMethod(SCI_SETFOLDFLAGS, 16, 0); // 16  	Draw line below if not expanded
					ScMethod(SCI_SETMARGINSENSITIVEN, MARGIN_SCRIPT_FOLD_INDEX, 1);

					ScMethod(SCI_SETMARGINWIDTHN, MARGIN_SCRIPT_FOLD_INDEX, 55);
					ScMethod(SCI_SETMARGINMASKN, MARGIN_SCRIPT_FOLD_INDEX, SC_MASK_FOLDERS);
					ScMethod(SCI_SETMARGINTYPEN,  MARGIN_SCRIPT_FOLD_INDEX, SC_MARGIN_NUMBER);
					ScMethod(SCI_COLOURISE, 0, -1);
				}
				break;
			case 389: /*SetAutoIndent*/
				retint=m_AutoIndentFlag;
				m_AutoIndentFlag=atoipos;
				break;	
			case 390: /*GetAutoIndent*/
				retint=m_AutoIndentFlag;
				break;	
			case 391: /*GetSelectionMetrics*/
				if (oStr)
				{
					int LineCount=ScMethod(SCI_GETLINECOUNT,0,0);
					int curpos=ScMethod(SCI_GETCURRENTPOS,0,0);
					int curanchor=ScMethod(SCI_GETANCHOR,0,0);
					int selstart=ScMethod(SCI_GETSELECTIONSTART,0,0);
					int selsend=ScMethod(SCI_GETSELECTIONEND,0,0);
					sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d",
						LineCount,
						curpos,ScMethod(SCI_LINEFROMPOSITION,curpos,0),
						curanchor,ScMethod(SCI_LINEFROMPOSITION,curanchor,0),
						selstart,ScMethod(SCI_LINEFROMPOSITION,selstart,0),
						selsend,ScMethod(SCI_LINEFROMPOSITION,selsend,0)
						);
				}
				break;	
			case 392: /*FindTextEx searchFlags,text*/
				if (oStr)
				{
					char *posoStr=oStr;
					if (m_FindDlg==NULL || m_FindDlg->m_hWnd==NULL) ShowFindDialog(0);
					TextToFind ttf={0};
					UINT i;
					ttf.chrg.cpMin=0;
					ttf.chrg.cpMax=-1;
					DWORD flg=0;
					CString cssf=ExtractField(pos,1,",");
					cssf.MakeUpper();
					BOOL bCountOnly=FALSE;
					BOOL bCountEnt=FALSE;

					if (cssf.GetLength()==0)
					{
						if (m_FindDlg)
						{ 
							m_FindDlg->UpdateCombos();
							flg=m_FindDlg->GetSearchFlags();
						}
					}
					else
					{
						for(i=0;i<GPScintilla::uNSearchFlags;i++)
							if (cssf.Find(GPScintilla::cArrSearchFlags[i])>=0)
								flg|=GPScintilla::uArrSearchFlags[i];
						if (cssf.Find("COUNTLINES")>=0) bCountOnly=TRUE;
						if (cssf.Find("COUNTENT")>=0) {bCountOnly=TRUE;bCountEnt=TRUE;}
					}
					const char *pos2=FindField(pos,2,",");
					CString src;
					if (pos2==NULL || *pos2==0)
					{
						if (m_FindDlg)
						{
							m_FindDlg->UpdateCombos();
							src=m_FindDlg->GetSearchText();
						}
					}
					else src=pos2;

					if (src!="")
					{
						int ret=-1;
						int start=0;
						ScMethod(SCI_SETSELECTIONSTART,0,0);
						ScMethod(SCI_SETSELECTIONEND,0,0);
						ScMethod(SCI_SEARCHANCHOR,0,0);
						char *tmpLineText=new char [70000];
						int endline=ScMethod(SCI_GETLINECOUNT,0,0);
						*tmpLineText=0;
						UINT nFind=0;

						do
						{
							ret=ScMethod(SCI_SEARCHNEXT,flg,(int)((LPCSTR)src));
							int findline=ret>=0?ScMethod(SCI_LINEFROMPOSITION,ret,0):-1;
							if (findline>=0)
							{
								nFind++;
								if (!bCountOnly) 
								{
									if (posoStr!=oStr) *(posoStr++)=127;
									*tmpLineText=0;
									int tmpLineLen=ScMethod(SCI_GETLINE,findline,(int)tmpLineText);
									if (tmpLineLen>=0)
									{
										tmpLineText[tmpLineLen]=0;
										while(tmpLineLen && (tmpLineText[tmpLineLen-1]==13 || tmpLineText[tmpLineLen-1]==10))
											tmpLineText[--tmpLineLen]=0;
									}
									else *tmpLineText=0;
									posoStr+=sprintf(posoStr,"%d\x7%d\x7%s",findline,ret,tmpLineText);
								}
							}
							if (ret!=-1)
							{
								int ln=findline;
								ln++;
								if (ln>=endline) ret=-1;
								else
								if (bCountEnt)
								{
									ScMethod(SCI_SETSELECTIONSTART,ret+1,0);
									ScMethod(SCI_SEARCHANCHOR,0,0);
								}
								else
								{
									start=ScMethod(SCI_POSITIONFROMLINE,ln,0);
									ScMethod(SCI_SETSELECTIONSTART,start,0);
									ScMethod(SCI_SEARCHANCHOR,0,0);
								}
							}
						}
						while(ret>=0);
						if (bCountOnly) sprintf(oStr,"%d",nFind);
						delete[] tmpLineText;
					}
				}
				break;	
			case 393: /*GetFindReplaceString*/
				if (oStr)
				{
					if (m_FindDlg==NULL || m_FindDlg->m_hWnd==NULL) ShowFindDialog(0);
					if (m_FindDlg)
					{ 
						*oStr=0;
						m_FindDlg->UpdateCombos();
						DWORD flg=m_FindDlg->GetSearchFlags();
						UINT i;
						for(i=0;i<GPScintilla::uNSearchFlags;i++)
							if ((GPScintilla::uArrSearchFlags[i]&flg)==GPScintilla::uArrSearchFlags[i])
								strcat(oStr,GPScintilla::cArrSearchFlags[i]);
						strcat(oStr,"\x7F");
						strcat(oStr,m_FindDlg->GetSearchText());
						strcat(oStr,"\x7F");
						strcat(oStr,m_FindDlg->GetReplaceText());
					}
				}
				break;	
			case 394: /*ReplaceAll SearchFlags,SearchTextCHAR(1)ReplaceText*/
				{
					if (m_FindDlg==NULL || m_FindDlg->m_hWnd==NULL) ShowFindDialog(0);
					if (m_FindDlg)
					{ 
						m_FindDlg->SetCurrentEditor(this);
						CString oldST=m_FindDlg->GetSearchText();
						CString oldRT=m_FindDlg->GetReplaceText();
						DWORD oldFlg=m_FindDlg->GetSearchFlags();

						CString cssf=ExtractField(pos,1,",");
						if (cssf.GetLength()==0)
						{
							if (m_FindDlg)
							{ 
								m_FindDlg->UpdateCombos();
								m_FindDlg->GetSearchFlags();
							}
						}
						else
						{
							DWORD flg=0;
							UINT i;
							for(i=0;i<GPScintilla::uNSearchFlags;i++)
								if (cssf.Find(GPScintilla::cArrSearchFlags[i])>=0)
									flg|=GPScintilla::uArrSearchFlags[i];
							m_FindDlg->SetSearchFlags(flg);
						}
						const char *srcstr=FindField(pos,2,",");
						if (srcstr)
							m_FindDlg->SetFindText(ExtractField(srcstr,1,"\x1"));

						const char *repstr=FindField(pos,2,"\x1");
						m_FindDlg->SetReplaceText(repstr?repstr:"");
						UINT nReplaced=m_FindDlg->DoReplaceAll();
						m_FindDlg->SetFindText(oldST);
						m_FindDlg->SetReplaceText(oldRT);
						m_FindDlg->SetSearchFlags(oldFlg);
						if (oStr) sprintf(oStr,"%d",nReplaced);
					}
				}
				break;	
			case 395: /*SetAutocList List*/
				{
					if (m_autocList) delete[] m_autocList;
					if (*pos)
					{
						m_autocList=new char [(int)strlen(pos)+100];
						strcpy(m_autocList,pos);
					}
				}
				break;
			case 396: /*AutocShowSpr lenEntered,field,SprName*/
				{
					int lenEntered=0,field=0;
					char *pos333=new char [(int)strlen(pos)+2];
					strcpy(pos333,pos);
					m_LastScanf=sscanf(pos333,"%d,%d",&lenEntered,&field);
					char *tmp2=strchr(pos333,',');
					if (tmp2) tmp2=strchr(++tmp2,',');
					retint=0;
					if (tmp2)
					{
						*(tmp2++)=0;
						CGPSpr *spr=GPC.m_SprArray.GetSpr(tmp2);
						if (spr)
						{
							char *sValues=NULL;
							char commstr[100];
							sprintf(commstr,"GetValues %d",field);
							spr->DoMethod(commstr,&sValues);
							if (sValues && *sValues)
							{
								tmp2=sValues;
								while(*tmp2)
								{
									if (*tmp2==0x7F || *tmp2<=32 || *tmp2==GPC.DelimiterIn1) 
									{
										*tmp2=' '; 
										retint++;
									}
									tmp2++;
								}
								if (retint)	
								{
									lenEntered=CheckEnteredLength(lenEntered);
									ScMethod(SCI_AUTOCSHOW,lenEntered,(int)sValues);
								}
								delete[] sValues;
							}
						}
					}
					delete[] pos333;
				}
				break;
			case 397: /*AutocShowListMaker lenEntered,ListName*/
				{
					int lenEntered=atoipos;
					char *pos333=new char [(int)strlen(pos)+2];
					strcpy(pos333,pos);
					char *tmp2=strchr(pos333,',');
					retint=0;
					if (tmp2)
					{
						*(tmp2++)=0;
						if (*tmp2)
						{
							char *sValues=NULL;
							retint=GPC.m_ListMaker.GetList(tmp2, &sValues, ' ');
							if (sValues && *sValues)
							{
								lenEntered=CheckEnteredLength(lenEntered);
								ScMethod(SCI_AUTOCSHOW,lenEntered,(int)sValues);
								delete[] sValues;
							}
							else retint=0;
						}
					}
					delete[] pos333;
				}
				break;
			case 398: /*AutocShowWords lenEntered[,MinLength=3]*/
				{
					char *buff=NULL;
					int MinLength=3;
					m_LastScanf=sscanf(pos,"%d,%d",&atoipos,&MinLength);
					if (*pos==0 || MinLength<0) MinLength=3;
					atoipos=CheckEnteredLength(atoipos);
					retint=GetWordsList(MinLength, &buff);
					if (buff && *buff) ScMethod(SCI_AUTOCSHOW,atoipos,(int)buff);
					if (buff) delete[] buff;
				}
				break;
			case 399: /*AutoCSetMaxWidth characterCount*/
				retint=ScMethod(SCI_AUTOCSETMAXWIDTH,atoipos,0);
				break;
			case 400: /*AutoCGetMaxWidth*/
				retint=ScMethod(SCI_AUTOCGETMAXWIDTH,0,0);
				break;
			case 401: /*AutoCSetMaxHeight rowCount*/
				retint=ScMethod(SCI_AUTOCSETMAXHEIGHT,atoipos,0);
				break;
			case 402: /*AutoCGetMaxHeight*/
				retint=ScMethod(SCI_AUTOCGETMAXHEIGHT,0,0);
				break;
			case 403: /*GetCaretSticky*/
				retint=ScMethod(SCI_GETCARETSTICKY,0,0);
				break;
			case 404: /*SetCaretSticky useCaretStickyBehaviour*/
				retint=ScMethod(SCI_SETCARETSTICKY,atoipos,0);
				break;
			case 405: /*ToggleCaretSticky*/
				retint=ScMethod(SCI_TOGGLECARETSTICKY,0,0);
				break;
			case 406: /*FindColumn Line,Column*/
				{
					int iLine=0,iColumn=0;
					m_LastScanf=sscanf(pos,"%d,%d",&iLine,&iColumn);
					if (iLine<0)	iLine=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);
					retint=ScMethod(SCI_FINDCOLUMN,iLine,iColumn);
				}
				break;
			case 407: /*SetLengthForEncode bytes*/
				retint=ScMethod(SCI_SETLENGTHFORENCODE,atoipos,0);
				break;
			case 408: /*EncodedFromUTF8 text*/
				if (oStr) retint=ScMethod(SCI_ENCODEDFROMUTF8,(int)pos,(int)oStr);
				break;
			case 409: /*TargetAsUTF8*/
				if (oStr) retint=ScMethod(SCI_TARGETASUTF8,0,(int)oStr);
				break;
			case 410: /*MarkerGetList*/
				if (oStr) 
				{
					char *posoStr=oStr;
					DWORD i;
					for(i=1; i<0x100; i+=i)
					{
						if (posoStr!=oStr) *(posoStr++)='\x1';
						int curLine=0;
						while((curLine=ScMethod(SCI_MARKERNEXT,curLine,i))>=0)
							posoStr+=sprintf(posoStr,"%d\x2",curLine++);
					}
					*posoStr=0;
				}
				break;
			case 411: /*GetFoldExpandedList*/
				if (oStr) 
				{
					char *posoStr=oStr;
					int nLines=ScMethod(SCI_GETLINECOUNT,0,0);
					int i;
					for(i=0;i<nLines;i++)
					{
						if (ScMethod(SCI_GETFOLDEXPANDED,i,0)==0)
						{
							if (posoStr!=oStr) *(posoStr++)='\x1';
							posoStr+=sprintf(posoStr,"%d",i);
						}
					}
					*posoStr=0;
				}
				break;
			case 412: /*SetFoldExpandedList*/
				{
					const char *tmppos=pos+(int)strlen(pos);
					const char *posstop=strchr(pos,',');

					if (posstop++)
						while(tmppos!=posstop)
						{
							while(tmppos!=posstop && (*tmppos<'0' || *tmppos>'9')) tmppos--;
							while(tmppos!=posstop && *tmppos>='0' && *tmppos<='9') tmppos--;
							int line=atoi(tmppos!=posstop?tmppos+1:tmppos);
							ScMethod(SCI_SETFOLDEXPANDED,line,1-atoipos);
							ScMethod(SCI_TOGGLEFOLD,line,0);
						}
					else
					{
						int nLines=ScMethod(SCI_GETLINECOUNT,0,0);
						int i;
						for(i=nLines;i>=0;i--)
						{
							ScMethod(SCI_SETFOLDEXPANDED,i,1-atoipos);
							ScMethod(SCI_TOGGLEFOLD,i,0);
						}
					}
				}
				break;
			case 413: /*MarkerSetList*/
				{
					const char *tmppos=pos;
					while(*tmppos)
					{
						while(*tmppos && *tmppos>='0' && *(tmppos++)<='9');
						while(*tmppos && (*tmppos<'0' || *tmppos>'9')) tmppos++;
						if (*tmppos) ScMethod(SCI_MARKERADD,atoi(tmppos),atoipos);
					}
				}
				break;
			case 414: /*ReplaceWord*/
				{
					retint=SelectWord(*pos>='0' && *pos<='9'?atoipos:-1);
					const char *pos2=strchr(pos,',');
					if (pos2++==NULL) pos2="";
					retint=ScMethod(SCI_REPLACESEL,0,(int)pos2);
				}
				break;
			case 415: /*SelectWord*/
				retint=SelectWord(*pos?atoipos:-1);
				break;
			case 416: /*PointsFromPosition*/
				if (oStr)
				{
					if (atoipos<0) atoipos=ScMethod(SCI_GETCURRENTPOS,0,0);
					POINT po={0};
					po.x=ScMethod(SCI_POINTXFROMPOSITION,atoipos,0);
					po.y=ScMethod(SCI_POINTYFROMPOSITION,atoipos,0);
					sprintf(oStr,"%d\x7%d\x7F",po.x,po.y);
					::ClientToScreen(m_hWnd,&po);
					sprintf(oStr+(int)strlen(oStr),"%d\x7%d",po.x,po.y);
				}
				break;
			case 417: /*GetMetricsByPos*/
			case 418: /*GetMetricsByLine*/
				if (oStr)
				{
					DWORD curpos;
					DWORD curline;
					if (nfunc==417)
					{
						curpos=atoipos;
						if (atoipos<0 || *pos==0)
							curpos=ScMethod(SCI_GETCURRENTPOS,0,0);

						curline=ScMethod(SCI_LINEFROMPOSITION,curpos,0);
					}
					else
					{
						curpos=ScMethod(SCI_GETCURRENTPOS,0,0);
						curline=atoipos;
						if (atoipos<0 || *pos==0)
							curline=ScMethod(SCI_LINEFROMPOSITION,curpos,0);
					}


					sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d",
						curpos,
						curline,
						ScMethod(SCI_GETFIRSTVISIBLELINE,0,0),
						ScMethod(SCI_LINESONSCREEN,0,0),
						ScMethod(SCI_GETSELECTIONSTART,0,0),
						ScMethod(SCI_GETSELECTIONEND,0,0),
						ScMethod(SCI_POSITIONFROMLINE,curline,0),
						ScMethod(SCI_GETLINEENDPOSITION,curline,0),
						ScMethod(SCI_LINELENGTH,curline,0),
						ScMethod(SCI_GETCOLUMN,curpos,0),
						ScMethod(SCI_POINTXFROMPOSITION,0,curpos),
						ScMethod(SCI_POINTYFROMPOSITION,0,curpos),
						ScMethod(SCI_GETLINESELSTARTPOSITION,curline,0),
						ScMethod(SCI_GETLINESELENDPOSITION,curline,0),
						ScMethod(SCI_WORDENDPOSITION,curpos,1),
						ScMethod(SCI_WORDSTARTPOSITION,curpos,1),
						ScMethod(SCI_POSITIONBEFORE,curpos,0),
						ScMethod(SCI_POSITIONAFTER,curpos,0),
						ScMethod(SCI_GETCHARAT,curpos,0),
						ScMethod(SCI_GETSTYLEAT,curpos,0)
						);
				}
				break;

			case 419: /*SetLineStyle*/
				{
					int line=-1,style=0,mask=7;
					m_LastScanf=sscanf(pos,"%d,%d,%d",&line,&style,&mask);
					if (line<0) 
						line=ScMethod(SCI_LINEFROMPOSITION,ScMethod(SCI_GETCURRENTPOS,0,0),0);

					int startpos=ScMethod(SCI_POSITIONFROMLINE,line,0);
					int curlinelen=ScMethod(SCI_LINELENGTH,line,0);
					ScMethod(SCI_STARTSTYLING,startpos,mask);
					retint=ScMethod(SCI_SETSTYLING,curlinelen,style);
				}
				break;	

			case 420: /*SetStyleForText nStyle,SearchFlags;Text*/
				{
					UINT i;
					const char *pos2=strchr(pos,';');
					if (pos2) pos2++;
					else pos2="";
					int nStyle=0;
					int nStyleBits=ScMethod(SCI_GETSTYLEBITS,0,0);
					DWORD StyleMask=(nStyleBits==0)?0:(1<<nStyleBits)-1;
					nStyle=atoipos;
					DWORD flg=0;
					CString cssf=ExtractField(ExtractField(pos,1,";"),2,",");
					cssf.MakeUpper();

					for(i=0;i<GPScintilla::uNSearchFlags;i++)
						if (cssf.Find(GPScintilla::cArrSearchFlags[i])>=0)
							flg|=GPScintilla::uArrSearchFlags[i];

					int oldselStart=ScMethod(SCI_GETSELECTIONSTART,0,0);
					int oldselEnd=ScMethod(SCI_GETSELECTIONEND,0,0);
					int start=oldselStart;

					int StylingLen=oldselEnd-oldselStart;
					if (StylingLen<0) StylingLen=-StylingLen;

					if ((flg&SCFIND_SELECTION)!=SCFIND_SELECTION)
					{
						ScMethod(SCI_SETSELECTIONSTART,0,0);
						ScMethod(SCI_SETSELECTIONEND,0,0);
						StylingLen=ScMethod(SCI_GETTEXTLENGTH,0,0);
						start=0;
					}


					if (*pos2)
					{
						TextToFind ttf={0};
						ttf.chrg.cpMin=0;
						ttf.chrg.cpMax=-1;

						CString src=pos2;
						int ret=-1;
						ScMethod(SCI_SEARCHANCHOR,0,0);
						StylingLen=src.GetLength();
						do
						{
							ret=ScMethod(SCI_SEARCHNEXT,flg,(int)((LPCSTR)src));
							if (ret>=0)
							{
								ScMethod(SCI_STARTSTYLING,ret,StyleMask);
								retint=ScMethod(SCI_SETSTYLING,StylingLen,nStyle);
								ScMethod(SCI_SETSELECTIONSTART,ret+StylingLen,0);
								ScMethod(SCI_SEARCHANCHOR,0,0);
							}
						}
						while(ret>=0);
					}
					else
					{
						ScMethod(SCI_STARTSTYLING,start,StyleMask);
						retint=ScMethod(SCI_SETSTYLING,StylingLen,nStyle);
					}
					ScMethod(SCI_SETSELECTIONSTART,oldselStart,0);
					ScMethod(SCI_SETSELECTIONEND,oldselEnd,0);
				}
				break;
				
			case 421: /*GetStylePositions nStyle */
				if (oStr)
				{
					char *posout=oStr;
					int TextLength=ScMethod(SCI_GETTEXTLENGTH,0,0);
					int startStyle;
					int LastStyle=-1;
					int CurStyle=-1;
					int i;
					for(i=0;i<TextLength;i++)
					{
						CurStyle=ScMethod(SCI_GETSTYLEAT,i,0);
						if (CurStyle==atoipos && LastStyle!=atoipos)
						{ // begin
							startStyle=i;
						}
						else
							if (CurStyle!=atoipos && LastStyle==atoipos)
							{// end
								if (posout!=oStr) *(posout++)=0x7F;
								int line=ScMethod(SCI_LINEFROMPOSITION,startStyle,0);
								posout+=sprintf(posout,"%d\x7%d\x7%d\x7%d",startStyle,i-startStyle,line,startStyle-ScMethod(SCI_POSITIONFROMLINE,line,0));

							}
						LastStyle=CurStyle;
					}

					if (CurStyle==atoipos && LastStyle==atoipos)
					{
						if (posout!=oStr) *(posout++)=0x7F;
						int line=ScMethod(SCI_LINEFROMPOSITION,startStyle,0);
						posout+=sprintf(posout,"%d\x7%d\x7%d\x7%d",startStyle,i-startStyle,line,startStyle-ScMethod(SCI_POSITIONFROMLINE,line,0));
					}
				}
				break;
				
			case 422: /*GotoNextStyle nStyle[,bDirection=1]*/
				{
					int curpos=ScMethod(SCI_GETCURRENTPOS,0,0);
					int CurStyle=ScMethod(SCI_GETSTYLEAT,curpos,0);
					int textLen=ScMethod(SCI_GETTEXTLENGTH,0,0);
					
					int SrchStyle=1,Direction=1;
					m_LastScanf=sscanf(pos,"%d,%d",&SrchStyle,&Direction);

					if (Direction==1)
					{
						int i;
						for(i=curpos; i<textLen && ScMethod(SCI_GETSTYLEAT,i,0)==SrchStyle;i++);
						if (i>=textLen)
							for(i=0;ScMethod(SCI_GETSTYLEAT,i,0)==SrchStyle && i<curpos;i++);
						if (i!=curpos || ScMethod(SCI_GETSTYLEAT,i,0)!=SrchStyle)
						{
							if (i>=curpos)
								for(;i<textLen && ScMethod(SCI_GETSTYLEAT,i,0)!=SrchStyle;i++);
							if (i>=textLen)
								for(i=0;ScMethod(SCI_GETSTYLEAT,i,0)!=SrchStyle && i<curpos;i++);
						}
						ScMethod(SCI_GOTOPOS,i,0);
						if (ScMethod(SCI_GETSTYLEAT,i,0)==SrchStyle)
						{
							ScMethod(SCI_SETSELECTIONSTART,i,0);
							for(;i<textLen && ScMethod(SCI_GETSTYLEAT,i,0)==SrchStyle;i++);
							ScMethod(SCI_SETSELECTIONEND,i,0);
						}
					}
					else
					if (textLen>1)
					{
						int i;
						for(i=curpos==0?0:curpos-1; i>=0 && ScMethod(SCI_GETSTYLEAT,i,0)==SrchStyle;i--);
						if (i<0)
							for(i=textLen-1;ScMethod(SCI_GETSTYLEAT,i,0)==SrchStyle && i>curpos;i--);
						if (i!=curpos || ScMethod(SCI_GETSTYLEAT,i,0)!=SrchStyle)
						{
							if (i<=curpos)
								for(; i>=0 && ScMethod(SCI_GETSTYLEAT,i,0)!=SrchStyle;i--);
							if (i<0)
								for(i=textLen-1;ScMethod(SCI_GETSTYLEAT,i,0)!=SrchStyle && i>curpos;i--);
						}
						if (i>0 && ScMethod(SCI_GETSTYLEAT,i-1,0)==SrchStyle)
						{
							int lastpos=i<textLen-1?i+1:i;
							for(; i>=0 && ScMethod(SCI_GETSTYLEAT,i,0)==SrchStyle;i--);
							ScMethod(SCI_GOTOPOS,i<textLen-1?i+1:i,0);
							ScMethod(SCI_SETSELECTIONEND,lastpos,0);
						}
						else
							ScMethod(SCI_GOTOPOS,i<textLen-1?i+1:i,0);
					}
				}
				break;
				
			case 423: /*SetStyleByPos nStyle,nStyleMask,Pos1,Len1[^Pos2,Len2^...]*/
				if (*pos)
				{
					int textLen=ScMethod(SCI_GETTEXTLENGTH,0,0);
					int nStyle=-1,nStyleMask=0;
					m_LastScanf=sscanf(pos,"%d,%d",&nStyle,&nStyleMask);
					if (nStyleMask<=0) nStyleMask=31;
					const char *pos2=strchr(pos,',');
					if (nStyle>=0 && pos2)
					{
						pos2=strchr(++pos2,',');
						while(pos2++)
						{
							int pStart=-1,len=-1;
							m_LastScanf=sscanf(pos2,"%d,%d",&pStart,&len);
							if (pStart>=0 && len>0 && pStart+len<textLen)
							{
								ScMethod(SCI_STARTSTYLING,pStart,nStyleMask);
								retint=ScMethod(SCI_SETSTYLING,len,nStyle);
							}
							pos2=strchr(pos2,GPC.DelimiterIn1);
						}
					}
				}
				break;
				
			case 424: /*SetFindString*/
				if (m_FindDlg==NULL || m_FindDlg->m_hWnd==NULL) ShowFindDialog(0);
				if (m_FindDlg)
				{
					m_FindDlg->UpdateCombos();
					if (oStr) strcpy(oStr,m_FindDlg->GetSearchText());
					if (*pos) m_FindDlg->SetFindText(pos);
					else
					{
						char *tmptxt=NULL;
						if (ScMethod(SCI_GETSELECTIONSTART,0,0)==ScMethod(SCI_GETSELECTIONEND,0,0)) SelectWord(ScMethod(SCI_GETSELECTIONSTART,0,0));
						GetSelText(&tmptxt);
						if (tmptxt && *tmptxt)
						{
							m_FindDlg->SetFindText(tmptxt);
						}
						if (tmptxt) delete[] tmptxt;
					}
				}
				break;

			case 425: /*SetReplaceString*/
				if (m_FindDlg==NULL || m_FindDlg->m_hWnd==NULL) ShowFindDialog(0);
				if (m_FindDlg)
				{
					m_FindDlg->UpdateCombos();
					if (oStr) strcpy(oStr,m_FindDlg->GetReplaceText());
					if (*pos) m_FindDlg->SetReplaceText(pos);
					else
					{
						char *tmptxt=NULL;
						if (ScMethod(SCI_GETSELECTIONSTART,0,0)==ScMethod(SCI_GETSELECTIONEND,0,0)) SelectWord(ScMethod(SCI_GETSELECTIONSTART,0,0));
						GetSelText(&tmptxt);
						if (tmptxt && *tmptxt)
						{
							m_FindDlg->SetReplaceText(tmptxt);
						}
						if (tmptxt) delete[] tmptxt;
					}
				}
				break;
			case 426: /*ReplaceNext*/
			case 427: /*ReplaceNextScroll*/
			case 428: /*ReplacePrev*/
			case 429: /*ReplacePrevScroll*/
				{
					DWORD sf=0;
					char *pos333=new char [(int)strlen(pos)+2];
					strcpy(pos333,pos);
					char *pos2=strchr(pos333,',');
					if (pos2) *(pos2++)=0;
					else pos2="";
					_strupr(pos333);
					CString src=pos2;
					if (m_FindDlg==NULL || m_FindDlg->m_hWnd==NULL) ShowFindDialog(0);
					if (m_FindDlg)	m_FindDlg->UpdateCombos();

					if (*pos333)
					{
						UINT i;
						for(i=0;i<GPScintilla::uNSearchFlags;i++)
							if (strstr(pos333,GPScintilla::cArrSearchFlags[i]))
								sf|=GPScintilla::uArrSearchFlags[i];
					}
					else
						if (m_FindDlg) sf=m_FindDlg->GetSearchFlags();

					if (src=="" && m_FindDlg) src=m_FindDlg->GetSearchText();

					int selstart=ScMethod(SCI_GETSELECTIONSTART,0,0);
					if (nfunc==426 || nfunc==427)			selstart++;
					else
					{
						selstart--;
						if (selstart<0) selstart=0;
					}

					ScMethod(SCI_SETSELECTIONSTART,selstart,0);
					ScMethod(SCI_SETSELECTIONEND,selstart,0);
					ScMethod(SCI_SEARCHANCHOR,0,0);

					BOOL scrl=FALSE;
					switch(nfunc)
					{
					case 427: /*ReplaceNextScroll*/
						scrl=TRUE;
					case 426: /*ReplaceNext*/
						retint=ScMethod(SCI_SEARCHNEXT,sf,(int)((LPCSTR)src));
						break;	
					case 429: /*ReplacePrevScroll*/
						scrl=TRUE;
					case 428: /*ReplacePrev*/
						retint=ScMethod(SCI_SEARCHPREV,sf,(int)((LPCSTR)src));
						break;	
					}

					if (retint<0)
					{
						if (nfunc==426 || nfunc==427)	selstart=0;
						else
							selstart=ScMethod(SCI_GETTEXTLENGTH,0,0);

						ScMethod(SCI_SETSELECTIONSTART,selstart,0);
						ScMethod(SCI_SETSELECTIONEND,selstart,0);
						ScMethod(SCI_SEARCHANCHOR,0,0);

						switch(nfunc)
						{
						case 427: /*ReplaceNextScroll*/
						case 426: /*ReplaceNext*/
							retint=ScMethod(SCI_SEARCHNEXT,sf,(int)((LPCSTR)src));
							break;	
						case 429: /*ReplacePrevScroll*/
						case 428: /*ReplacePrev*/
							retint=ScMethod(SCI_SEARCHPREV,sf,(int)((LPCSTR)src));
							break;	
						}
					}

					if (retint>=0)
					{
						if (scrl)
						{
							ScMethod(SCI_GOTOPOS,retint,0);
							ScMethod(SCI_ENSUREVISIBLE,ScMethod(SCI_LINEFROMPOSITION,retint,0),0);
						}
						ScMethod(SCI_SETSELECTIONSTART,retint,0);
						ScMethod(SCI_SETSELECTIONEND,retint+src.GetLength(),0);
						if (m_FindDlg==NULL || m_FindDlg->m_hWnd==NULL) ShowFindDialog(0);
						if (m_FindDlg) ScMethod(SCI_REPLACESEL,0,(int)((LPCSTR)m_FindDlg->GetReplaceText()));
					}
					delete[] pos333;
				}
				break;	

			case 430: /*SetFindStringCB*/
			case 431: /*SetReplaceStringCB*/
				if (m_FindDlg==NULL || m_FindDlg->m_hWnd==NULL) ShowFindDialog(0);
				if (m_FindDlg)
				{
					m_FindDlg->UpdateCombos();

					HANDLE hClipData; 
					LPSTR  lpClipData;
					char *str=NULL;
					
					if (OpenClipboard()) 
					{
						if (!(hClipData = GetClipboardData(CF_TEXT)))    CloseClipboard();
						else
						{
							if (!(lpClipData = (char *)GlobalLock(hClipData))) CloseClipboard();
							else
							{
								if (nfunc==430)
									m_FindDlg->SetFindText(lpClipData);
								else
									m_FindDlg->SetReplaceText(lpClipData);
								GlobalUnlock(hClipData);
								CloseClipboard();
							}
						}
					}
				}
				break;
			case 432: /*SetAutoFocus*/
				retint=m_bAutoFocus;
				m_bAutoFocus=atoipos;
				break;

			case 433: /*SetLine LineNumber,Text*/
				if (atoipos>=0 && atoipos<ScMethod(SCI_GETLINECOUNT,0,0))
				{
					ScMethod(SCI_SETTARGETSTART,ScMethod(SCI_POSITIONFROMLINE,atoipos,0),0);
					ScMethod(SCI_SETTARGETEND,ScMethod(SCI_POSITIONFROMLINE,atoipos+1,0)-1,0);
					char *pos333=new char [(int)strlen(pos)+2];
					const char *tmppos=strchr(pos,',');
					if (!tmppos++) tmppos="";
					strcpy(pos333,tmppos);
					Replace1To13(pos333);
					retint=ScMethod(SCI_REPLACETARGET,-1,(int)pos333);
					delete[] pos333;
				}
				break;
			case 434: /*InsertLine LineNumber,Text*/
				if (atoipos>=0 && atoipos<ScMethod(SCI_GETLINECOUNT,0,0))
				{
					int linestart;
					ScMethod(SCI_SETTARGETSTART,linestart=ScMethod(SCI_POSITIONFROMLINE,atoipos,0),0);
					ScMethod(SCI_SETTARGETEND,linestart,0);

					char *pos333=new char [(int)strlen(pos)+2];
					const char *tmppos=strchr(pos,',');
					if (!tmppos++) tmppos="";
					strcpy(pos333,tmppos);
					strcat(pos333,"\x01");
					Replace1To13(pos333);
					retint=ScMethod(SCI_REPLACETARGET,-1,(int)pos333);
					delete[] pos333;
				}
				break;
			case 435: /*DeleteLine LineNumber*/
				if (atoipos>=0 && atoipos<ScMethod(SCI_GETLINECOUNT,0,0))
				{
					ScMethod(SCI_SETTARGETSTART,ScMethod(SCI_POSITIONFROMLINE,atoipos,0),0);
					ScMethod(SCI_SETTARGETEND,ScMethod(SCI_POSITIONFROMLINE,atoipos+1,0),0);
					retint=ScMethod(SCI_REPLACETARGET,-1,(int)"");
				}
				break;
			case 436://SetScrollTick
				retint=ScMethod(SCI_GETSCROLLTICK,0,0);
				ScMethod(SCI_SETSCROLLTICK,atoipos,0);
				break;
			case 437://GetScrollTick
				retint=ScMethod(SCI_GETSCROLLTICK,0,0);
				break;
			case 438://SetAutoScrollDelay
				retint=ScMethod(SCI_GETASCROLLDELAY,0,0);
				ScMethod(SCI_SETASCROLLDELAY,atoipos,0);
				break;
			case 439://GetAutoScrollDelay
				retint=ScMethod(SCI_GETASCROLLDELAY,0,0);
				break;


			default: 
				if (oStr!=NULL)
						 sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
			}
		}
	}

	if (oStr!=NULL && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);

	return nfunc;
}


UINT GPScintilla::GPSetProperty(char *iStr)
{
	char *iValue=new char [(int)strlen(iStr)+5];
	strcpy(iValue,iStr);
	UINT ret=1,i;
	char *pos=strchr(iValue,'=');

	if (pos!=NULL && m_hWnd)
	{
		char *prop[]={ "TEXT", "ADDSTYLE", "DELSTYLE","STYLE", };
		int propnum;
		*(pos++)=0;
		for(propnum=0;propnum<4 && strcmp(prop[propnum],iValue)!=0;propnum++); 
		if (propnum>=4) ret=2;
		else
		{
			ret=3;
			switch(propnum)
			{
			case 0: // TEXT
				if ((GetStyle()&ES_MULTILINE)==ES_MULTILINE) SetWindowText(ReplaceSpec(pos));
				 else SetWindowText(pos);
				Invalidate();
				break;
			case 1: // ADDSTYLE
			case 2: // DELSTYLE
			case 3: // STYLE
				if (m_hWnd!=NULL)
				{
					ret=2;
					strcat(pos,"|");
					int InvFlg=0;
					for(i=0;i<N_EDIT_STYLES;i++)	
						if (strstr(pos,aEditStyleName[i])!=NULL)
						{
							InvFlg++; 
							switch(propnum)
							{
							case 3: /* STYLE*/	
							case 1: /* ADDSTYLE*/	ModifyStyle(0,aEditStyleUINT[i]);break;
							case 2: /* DELSTYLE*/	ModifyStyle(aEditStyleUINT[i],0);break;
							}
						}
					if (InvFlg!=0) Invalidate();
				}
				break;
			default: /* end */
				ret=2;
				break;
			}

		}
		*(--pos)='=';
	}

	delete[] iValue;
	return ret;
}

LRESULT GPScintilla::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		referGPU[UnitId&0xFFFF]->m_CurMessage.message=message;
		referGPU[UnitId&0xFFFF]->m_CurMessage.wParam=wParam;
		referGPU[UnitId&0xFFFF]->m_CurMessage.lParam=lParam;
		if (referGPU[UnitId&0xFFFF]->DefWindowProc(message, wParam, lParam)) return 0;
	}

	if (message==WM_KEYUP || message==WM_KEYDOWN || message==WM_CHAR) 
	{
		if (message==WM_KEYDOWN) m_ProcHK&=(0xFFFFFFFF^0x2);
		if (m_DirectInputFlag)
		{
			DWORD key=0;
			BOOL bSend=TRUE;
			if (m_ArrLockKey && m_LockKeysFlag && message!=WM_CHAR)
			{
				key=(((GetAsyncKeyState(VK_CONTROL)&0xFF00)==0)?0:MOD_CONTROL)
					|(((GetAsyncKeyState(VK_SHIFT)&0xFF00)==0)?0:MOD_SHIFT)
					|(((GetAsyncKeyState(VK_RWIN)&0xFF00)==0 && (GetAsyncKeyState(VK_LWIN)&0xFF00)==0)?0:MOD_WIN)
					|(((GetAsyncKeyState(VK_MENU)&0xFF00)==0)?0:MOD_ALT)
					|(wParam*0x10000);

				if (m_ArrLockKey->IsIdInArray(key))
					bSend=FALSE;
				if ((key==0x560002 || key==0x2D0004) && message==WM_KEYUP)
				{
					HANDLE hClipData; 
					LPSTR  lpClipData;
					char *str=NULL;
					
					if (OpenClipboard()) 
					{
						if (!(hClipData = GetClipboardData(CF_TEXT)))    CloseClipboard();
						else
						{
							str=new char [GlobalSize(hClipData)+10];
							*str=0;
							if (!(lpClipData = (char *)GlobalLock(hClipData))) CloseClipboard();
							else
							{
								strcpy(str, lpClipData);
								GlobalUnlock(hClipData);
								CloseClipboard();
								AnsiToDos(str,1);
								m_Comm.GPSendBlock(str,(int)strlen(str));
							}
							delete[] str;
						}
					}
				}
			}
			if (bSend) ::SendMessage(GPC.m_hViewWnd,message, wParam, lParam);
		}
		else
			if ((m_ProcHK&0x3)==0x3) return 0;
	}

	if (message==GPM_SETAUTOSIZE) 
		GetParent()->PostMessage(GPM_SETAUTOSIZE,wParam);

	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG) 
	{
		if (message==GPM_CLIENTKILLFOCUS || message==GPM_CLIENTSETFOCUS)
		{
			PGPUNITINFO ui=(PGPUNITINFO)lParam;
			if (ui)
				referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent
					(m_hWnd, UnitId,message==GPM_CLIENTSETFOCUS?"OnCSetFocus":"OnCKillFocus",GPUnit::UnitInfoToString2(ui,"\x7F"));
		}
		UINT ret;
		if ((ret=referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjMessage(m_hWnd, UnitId, message, wParam, lParam))>0) return ret;
		if (message==WM_KEYDOWN && referGPU!=NULL && referGPU[UnitId&0xFFFF]->UnitHotkey && this->m_hWnd!=NULL && IsWindowEnabled()==TRUE && IsWindowVisible()==TRUE)
				if ((ret=referGPU[UnitId&0xFFFF]->UnitHotkey->SendHotkeyMessage(message, wParam,lParam))>0) 
				{m_ProcHK|=0x2;return ret;}

		if (message==GPM_PROCHOTKEY)
		{
			if(referGPU[UnitId&0xFFFF]->UnitHotkey && (ret=referGPU[UnitId&0xFFFF]->UnitHotkey->SendHotkeyMessage(WM_KEYDOWN, wParam,lParam))>0) return ret;
			GetParent()->SendMessage(message, wParam,lParam);
		}
		else 
		if  (message==WM_KEYDOWN)
			GetParent()->SendMessage(GPM_PROCHOTKEY, wParam,lParam);
	}

	if (message==WM_SIZEPARENT && referGPU!=NULL)
	{
		UINT SizStyle=referGPU[UnitId&0xFFFF]->SizStyle;
		if ((SizStyle&0xFFFF0000)!=0)
		{
			AFX_SIZEPARENTPARAMS* lpLayout = (AFX_SIZEPARENTPARAMS*)lParam;

			CRect re;
			GetWindowRect(&re);
			switch((SizStyle&0xFFFF0000)/0x10000)
			{
			case GPUA_TOP:
				MoveWindow(lpLayout->rect.left,lpLayout->rect.top,lpLayout->rect.right-lpLayout->rect.left,re.Height());
				lpLayout->rect.top+=re.Height();
				break;
			case GPUA_BOTTOM:
				MoveWindow(lpLayout->rect.left,lpLayout->rect.bottom-re.Height(),lpLayout->rect.right-lpLayout->rect.left,re.Height());
				lpLayout->rect.bottom-=re.Height();
				break;
			case GPUA_LEFT:
				MoveWindow(lpLayout->rect.left,lpLayout->rect.top,re.Width(),lpLayout->rect.bottom-lpLayout->rect.top);
				lpLayout->rect.left+=re.Width();
				break;
			case GPUA_RIGHT:
				MoveWindow(lpLayout->rect.right-re.Width(),lpLayout->rect.top,re.Width(),lpLayout->rect.bottom-lpLayout->rect.top);
				lpLayout->rect.right-=re.Width();
				break;
			case GPUA_ENTIRE:
				MoveWindow(&lpLayout->rect);
				lpLayout->rect.left=lpLayout->rect.right;
				lpLayout->rect.top=lpLayout->rect.bottom;
				break;
			}

		}

	}
	
	if (message==GPN_UPDATESIZE) GetParent()->SendMessage(GPN_UPDATESIZE);

	switch(message)
	{
	case GPM_DRAGMOUSELEAVE:
		if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDragLeave","");
		break;
	case GPM_DRAGMOUSEMOVE:	
		OnMouseDragMove((PGPDRAGDROPSTRUCT)wParam,(LPPOINT)lParam);
		break;
	case GPM_DRAGMOUSEHOVER:
		OnDragMouseHover();
		break;
	case GPM_DROPITEMS:
		OnDragLButtonUp((PGPDRAGDROPSTRUCT)wParam,(LPPOINT)lParam);
		break;
	}

	LRESULT lpr;
	if (message==WM_SETFOCUS && m_bAutoFocus && ::GetFocus()==m_hWnd && wParam==(WPARAM)m_hWnd)  
		lpr=FALSE;
	else
	if ((message==WM_SETCURSOR && GPC.m_bWaitCursor) ||(message==WM_CONTEXTMENU && !m_EnableContextMenu)) lpr=FALSE;
	else lpr=CWnd::WindowProc(message, wParam, lParam);

	return lpr;
}

BOOL GPScintilla::PreTranslateMessage(MSG* pMsg) 
{
	if (referGPU && referGPU[UnitId&0xFFFF])
	{
		referGPU[UnitId&0xFFFF]->m_CurPreMessage=pMsg;
		if (!referGPU[UnitId&0xFFFF]->DefPreTranslateMessage(pMsg)) return 0;
		if (referGPU[UnitId&0xFFFF]->GPMSG) 
		{
			UINT ret;
			if (pMsg->message!=WM_KEYDOWN || pMsg->wParam==VK_RETURN || pMsg->wParam==VK_TAB || pMsg->wParam==VK_CANCEL || pMsg->wParam==VK_ESCAPE || pMsg->wParam==VK_HELP)
			{
				if ((ret=referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjMessage(m_hWnd, UnitId, pMsg->message, pMsg->wParam, pMsg->lParam))>0) return ret;
				if (pMsg->message==WM_KEYDOWN && referGPU!=NULL && referGPU[UnitId&0xFFFF]->UnitHotkey && this->m_hWnd!=NULL && IsWindowEnabled()==TRUE && IsWindowVisible()==TRUE)
						if ((ret=referGPU[UnitId&0xFFFF]->UnitHotkey->SendHotkeyMessage(pMsg->message, pMsg->wParam,pMsg->lParam))>0) return ret;
			}

			if (pMsg->message==WM_SYSKEYDOWN && pMsg->wParam==0x56 && referGPU!=NULL && referGPU[UnitId&0xFFFF]->UnitHotkey && this->m_hWnd!=NULL && IsWindowEnabled()==TRUE && IsWindowVisible()==TRUE)
				if ((ret=referGPU[UnitId&0xFFFF]->UnitHotkey->SendHotkeyMessage(pMsg->message, pMsg->wParam,pMsg->lParam))>0) return ret;

		}
	}	
	return CWnd::PreTranslateMessage(pMsg);
}

void GPScintilla::OnClose() 
{
	if (referGPU!=NULL)	referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnClose","");
}

void GPScintilla::OnSizing(UINT fwSide, LPRECT pRect) 
{

	BOOL EnableSz=TRUE;
	UINT SizStyle=referGPU[UnitId&0xFFFF]->SizStyle;
	if ((SizStyle&0xFFFF)!=0)
	{
		CRect re;
		GetWindowRect(&re);
		switch(fwSide)
		{
		case WMSZ_BOTTOM:
			if ((SizStyle&GPUA_BOTTOM)!=GPUA_BOTTOM) EnableSz=FALSE;
			break;
		case WMSZ_BOTTOMLEFT:
			if ((SizStyle&GPUA_BOTTOM)!=GPUA_BOTTOM && (SizStyle&GPUA_LEFT)!=GPUA_LEFT) EnableSz=FALSE;
			break;
		case WMSZ_BOTTOMRIGHT:
			if ((SizStyle&GPUA_BOTTOM)!=GPUA_BOTTOM && (SizStyle&GPUA_RIGHT)!=GPUA_RIGHT) EnableSz=FALSE;
			break;
		case WMSZ_LEFT:
			if ((SizStyle&GPUA_LEFT)!=GPUA_LEFT) EnableSz=FALSE;
			break;
		case WMSZ_RIGHT:
			if ((SizStyle&GPUA_RIGHT)!=GPUA_RIGHT) EnableSz=FALSE;
			break;
		case WMSZ_TOP:
			if ((SizStyle&GPUA_TOP)!=GPUA_TOP) EnableSz=FALSE;
			break;
		case WMSZ_TOPLEFT:
			if ((SizStyle&GPUA_LEFT)!=GPUA_LEFT && (SizStyle&GPUA_TOP)!=GPUA_TOP) EnableSz=FALSE;
			break;
		case WMSZ_TOPRIGHT:
			if ((SizStyle&GPUA_RIGHT)!=GPUA_RIGHT && (SizStyle&GPUA_TOP)!=GPUA_TOP) EnableSz=FALSE;
			break;
		}
		if (EnableSz==FALSE)
		{
			pRect->top=re.top;
			pRect->left=re.left;
			pRect->right=re.right;
			pRect->bottom=re.bottom;
		}
		else
		{
			GetParent()->SendMessage(WM_SIZE);
		}
	}

	if (EnableSz) CWnd::OnSizing(fwSide, pRect);

	GetParent()->SendMessage(GPN_UPDATESIZE);
}

void GPScintilla::OnDragMouseHover() 
{
	if (referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(GPC.m_DragDrop.DragName)<0xFFFFFFFFL)
	{
		// Reset the timer.
		SetTimer(DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nScrollInterval, NULL);

		// Get the current cursor position and window height.
		DWORD dwPos = ::GetMessagePos();
		CPoint point(LOWORD(dwPos), HIWORD(dwPos));
		ScreenToClient(&point);

		CRect rect;
		GetClientRect(rect);
		int cy = rect.Height();


		// Scroll the window if the cursor is near the top or bottom.
		if (point.y >= 0 && point.y <= referGPU[UnitId&0xFFFF]->m_nScrollMargin)
		{
			int iii;
			int iiii=iii;
/*			int nFirstVisibleLine = GetFirstVisibleLine();
			GPC.m_DragDrop.pImageList->DragShowNolock(FALSE);
			SendMessage(WM_VSCROLL, MAKEWPARAM(SB_LINEUP, 0), NULL);
			GPC.m_DragDrop.pImageList->DragShowNolock(TRUE);

			// Kill the timer if the window did not scroll, or redraw the drop target highlight if the window did scroll.
			if (GetFirstVisibleLine() == nFirstVisibleLine)
				::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);
			else 
				HighlightDropTarget(&GPC.m_DragDrop, point);
				*/
		}
		else
			if (point.y >= cy - referGPU[UnitId&0xFFFF]->m_nScrollMargin && point.y <= cy) 
			{
			int iii;
			int iiii=iii;
			/*
				int nFirstVisibleLine = GetFirstVisibleLine();
				GPC.m_DragDrop.pImageList->DragShowNolock(FALSE);
				SendMessage(WM_VSCROLL, MAKEWPARAM(SB_LINEDOWN, 0), NULL);
				GPC.m_DragDrop.pImageList->DragShowNolock(TRUE);

				// Kill the timer if the window did not scroll, or redraw the drop target highlight if the window did scroll.
				if (GetFirstVisibleLine() == nFirstVisibleLine) ::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);
				else 
					HighlightDropTarget(&GPC.m_DragDrop, point);
					*/
			}
			else  ::KillTimer(GPC.m_DragDrop.hWndDrag,DRAG_TIMER_ID);

		CString tmps;
		POINTL pol;
		pol.x=LOWORD(dwPos);
		pol.y=HIWORD(dwPos);
		long nchar = SendMessage(EM_CHARFROMPOS,0,(LPARAM)&pol);
		long nline = SendMessage(EM_LINEFROMCHAR,nchar,0);
		long ncharINline = SendMessage(EM_LINEINDEX,nline,0);
		tmps.Format("%d\x07%d\x07%d",nchar,nline,ncharINline);
		referGPU[UnitId&0xFFFF]->SendDropHoverEvent(tmps,&GPC.m_DragDrop,&point);
	}
}

void GPScintilla::OnMouseDragMove(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point) 
{
	if (pDrDrStruct && pDrDrStruct->pImageList != NULL)
	{
		::ScreenToClient(m_hWnd,point);
		::KillTimer(pDrDrStruct->hWndDrag,DRAG_TIMER_ID);
		// Offset point
		if (referGPU && referGPU[UnitId&0xFFFF])	
			referGPU[UnitId&0xFFFF]->OffsetWndPoint(point);

		// Erase the old drag image and draw a new one.
		if (pDrDrStruct->hWndLast!=m_hWnd)
		{
			pDrDrStruct->pImageList->DragLeave(CWnd::FromHandle(pDrDrStruct->hWndLast));
			pDrDrStruct->hWndLast=m_hWnd;
			pDrDrStruct->pImageList->DragEnter(this, CPoint(*point));
		}
		pDrDrStruct->pImageList->DragMove(CPoint(*point));

		DWORD dwHighlightItem=(DWORD)-1;
		BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
		// Highlight the drop target if the cursor is over an item.
		if (mDrop)
			dwHighlightItem = HighlightDropTarget(pDrDrStruct, CPoint(*point));
		// Modify the cursor to provide visual feedback to the user. Note: It's important to do this AFTER the call to DragMove.
		::SetCursor(dwHighlightItem == -1 ?
			AfxGetApp()->LoadStandardCursor(IDC_NO) :
			(HCURSOR) ::GetClassLong(m_hWnd, GCL_HCURSOR));

		CString tmps;
		POINTL pol;
		pol.x=point->x;
		pol.y=point->y;
		long nchar = SendMessage(EM_CHARFROMPOS,0,(LPARAM)&pol);
		long nline = SendMessage(EM_LINEFROMCHAR,nchar,0);
		long ncharINline = SendMessage(EM_LINEINDEX,nline,0);
		tmps.Format("%d\x07%d\x07%d",nchar,nline,ncharINline);
		referGPU[UnitId&0xFFFF]->SendDropMoveEvent(tmps,pDrDrStruct,point);

		if (mDrop)
			::SetTimer(pDrDrStruct->hWndDrag,DRAG_TIMER_ID, referGPU[UnitId&0xFFFF]->m_nDelayInterval, NULL);
	}
}

void GPScintilla::OnDragLButtonUp(PGPDRAGDROPSTRUCT pDrDrStruct, LPPOINT point) 
{
	BOOL mDrop=referGPU[UnitId&0xFFFF]->m_DropNamesArray && referGPU[UnitId&0xFFFF]->m_DropNamesArray->GetIdByVal(pDrDrStruct->DragName)<0xFFFFFFFFL;
	if (pDrDrStruct && mDrop && referGPU)
	{
		::ScreenToClient(m_hWnd,point);
		CString tmp;
		long nchar = SendMessage(EM_CHARFROMPOS,0,MAKELPARAM(point->x,point->y));
		long nline = SendMessage(EM_LINEFROMCHAR,nchar,0);
		long ncharINline = SendMessage(EM_LINEINDEX,nline,0);
		tmp.Format("%d\x07%d\x07%d",nchar,nline,ncharINline);
		referGPU[UnitId&0xFFFF]->SendDropEvent(tmp,pDrDrStruct,point);
	}
}

DWORD GPScintilla::HighlightDropTarget(PGPDRAGDROPSTRUCT pDrDrStruct, CPoint point)
{
	return 0;
}

LRESULT GPScintilla::OnNcHitTest(CPoint point) 
{
	LRESULT ret=CWnd::OnNcHitTest(point);
	if (referGPU && referGPU[UnitId&0xFFFF])
		ret=referGPU[UnitId&0xFFFF]->GPNCHitTest(point,ret);
	return ret;
}

BOOL GPScintilla::SetreferGPU(GPUnit **iGPU)
{
	return (referGPU=iGPU)!=NULL;
}

void GPScintilla::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd::OnKillFocus(pNewWnd);
	GPUNITINFO ui;
	GPUNITINFO uiold;
	if (referGPU && referGPU[UnitId&0xFFFF])
		referGPU[UnitId&0xFFFF]->GetUnitInfo(ui);
	if (pNewWnd)
	{
		GPC.m_Document->FindObject(pNewWnd->m_hWnd,uiold);
		ui.hWnd2=uiold.hWnd;
		ui.IdDlg2=uiold.IdDlg;
		ui.IdObj2=uiold.IdObj;
	}
	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG) 
	{
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent
			(m_hWnd, UnitId,"OnKillFocus",GPUnit::UnitInfoToString2(&ui,"\x7F"));
	}

	::PostMessage(::GetParent(m_hWnd),GPM_UPDATELVEDITOR,0,0);
	if (referGPU!=NULL)	
	{
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnKillFocusEx","");
	}
	::SendMessage(::GetParent(m_hWnd),GPM_CLIENTKILLFOCUS,(WPARAM)(pNewWnd?pNewWnd->m_hWnd:NULL),(LPARAM)&ui);
}

void GPScintilla::OnSetFocus(CWnd* pOldWnd) 
{
	if (m_FindDlg)	m_FindDlg->SetCurrentEditor(this);

	CWnd::OnSetFocus(pOldWnd);
	GPUNITINFO ui;
	GPUNITINFO uiold;
	if (referGPU && referGPU[UnitId&0xFFFF])
		referGPU[UnitId&0xFFFF]->GetUnitInfo(ui);
	if (pOldWnd)
	{
		GPC.m_Document->FindObject(pOldWnd->m_hWnd,uiold);
		ui.hWnd2=uiold.hWnd;
		ui.IdDlg2=uiold.IdDlg;
		ui.IdObj2=uiold.IdObj;
	}
	if (referGPU && referGPU[UnitId&0xFFFF] && referGPU[UnitId&0xFFFF]->GPMSG) 
		referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent
			(m_hWnd, UnitId,"OnSetFocus",GPUnit::UnitInfoToString2(&ui,"\x7F"));

	::SendMessage(::GetParent(m_hWnd),GPM_CLIENTSETFOCUS,(WPARAM)(pOldWnd?pOldWnd->m_hWnd:NULL),(LPARAM)&ui);
}

void GPScintilla::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	if (m_hWnd)
	{
		if (referGPU!=NULL && referGPU[UnitId&0xFFFF])
			referGPU[UnitId&0xFFFF]->UpdateSizerSize();
	}
}

int GPScintilla::ScMethod(int Message,int wParam,int lParam)
{
	int ret=0;

	if (InitFnPtr && Scincillafn==NULL && Scincillaptr==NULL && m_hWnd)
	{
		Scincillafn = (int (__cdecl *)(void *,int,int,int))SendMessage(SCI_GETDIRECTFUNCTION,0,0);
		Scincillaptr = (void *)SendMessage(SCI_GETDIRECTPOINTER,0,0);
		InitFnPtr=FALSE;
	}


	if (Scincillafn && Scincillaptr)
		ret=Scincillafn(Scincillaptr,Message,wParam,lParam);
	else
		if (m_hWnd)
			ret=SendMessage(Message,wParam,lParam);
	return ret;
}

/*
#define SC_MOD_BEFOREDELETE 0x800
#define SC_MOD_BEFOREINSERT 0x400
#define SC_MOD_CHANGEFOLD 0x8
#define SC_MOD_CHANGEMARKER 0x200
#define SC_MOD_CHANGESTYLE 0x4
#define SC_MOD_DELETETEXT 0x2
#define SC_MOD_INSERTTEXT 0x1
*/
BOOL GPScintilla::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult) 
{
	if (referGPU && referGPU[UnitId&0xFFFF]->GPMSG)	
	{
		switch(message)
		{
		case WM_COMMAND:
			{
				switch(HIWORD(wParam))
				{
				case SCEN_CHANGE:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnENChange","");
					break;
				case SCEN_KILLFOCUS:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnENKillFocus","");
					break;
				case SCEN_SETFOCUS:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnENSetFocus","");
					break;
				default:
//					TRACE("GPScintilla::OnChildNotify WM_COMMAND %d\n",HIWORD(wParam));
					break;
				}
			}
			break;
		case WM_NOTIFY:			
			{
				NMHDR* pNMHDR=(NMHDR *) lParam;
				SCNotification *ppp=(SCNotification *) lParam;
				switch(pNMHDR->code)
				{
					break;
				case SCN_MODIFIED:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnModified","");
					break;
				case SCN_UPDATEUI:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnUpdateUI","");
					break;
				case SCN_CHARADDED:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnCharAdded","");
					break;
				case SCN_STYLENEEDED:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnStyleNeeded","");
					break;
				case SCN_PAINTED:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnPainted","");
					break;
				case SCN_SAVEPOINTLEFT:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSavepointLeft","");
					break;
				case SCN_DOUBLECLICK:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDoubleClick","");
					break;
				case SCN_CALLTIPCLICK:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnCallTipClick","");
					break;
				case SCN_DWELLEND:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDWellEnd","");
					break;
				case SCN_DWELLSTART:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnDWellStart","");
					break;
				case SCN_HOTSPOTCLICK:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnHotspotClick","");
					break;
				case SCN_HOTSPOTDOUBLECLICK:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnHotspotDoubleclick","");
					break;
				case SCN_KEY:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnKey","");
					break;
				case SCN_MACRORECORD:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnMacroRecord","");
					break;
				case SCN_MARGINCLICK:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnMarginClick","");
					if (ppp->margin==MARGIN_SCRIPT_FOLD_INDEX)
						MarginClick(ppp->position,ppp->modifiers);
					break;
				case SCN_MODIFYATTEMPTRO:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnModifyAttemptRO","");
					break;
				case SCN_NEEDSHOWN:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnNeedShown","");
					break;
				case SCN_SAVEPOINTREACHED:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnSavepointReached","");
					break;
				case SCN_URIDROPPED:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnURIDropped","");
					break;
				case SCN_USERLISTSELECTION:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnUserListSelection","");
					break;
				case SCN_ZOOM:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnZoom","");
					break;
				case SCN_AUTOCSELECTION:
					referGPU[UnitId&0xFFFF]->GPMSG->GPSendObjEvent(m_hWnd, UnitId,"OnAutocSelection","");
					break;
				default:
//					TRACE("GPScintilla::OnChildNotify WM_NOTIFY %d\n",pNMHDR->code);
					break;
				}
				break;
			}
		break;
		}
	}
	return CWnd::OnChildNotify(message, wParam, lParam, pLResult);
}

const char * GPScintilla::Replace1To13(char *iStr)
{
	char *pos2=iStr;
	while(*pos2)
	{
		if (*pos2==1) *pos2=13;
		pos2++;
	}
	return iStr;
}

void GPScintilla::SetAStyle(int style, COLORREF fore, COLORREF back, int size, const char *face) 
{
	ScMethod(SCI_STYLESETFORE, style, fore);
	ScMethod(SCI_STYLESETBACK, style, back);
	if (size >= 1)
		ScMethod(SCI_STYLESETSIZE, style, size);
	if (face) 
		ScMethod(SCI_STYLESETFONT, style, reinterpret_cast<LPARAM>(face));
}

BOOL GPScintilla::GetStyleInfo(UINT iStyle, GPSCSTYLESET & GPCS)
{
	BOOL ret=TRUE;
	char fontName[1000];

	if ((iStyle&GPSC_STYLETYPEMASK)==GPSC_STYLETYPESTYLE)
	{
		iStyle&=0xFFFF;
		GPCS.bkg=ScMethod(SCI_STYLEGETBACK,iStyle,0);
		GPCS.frg=ScMethod(SCI_STYLEGETFORE,iStyle,0);
		*fontName=0;
		ScMethod(SCI_STYLEGETFONT,iStyle,(int)fontName);
		GPCS.fontName=fontName;
		GPCS.fontSize	=ScMethod(SCI_STYLEGETSIZE,iStyle,0);
		GPCS.bold		=ScMethod(SCI_STYLEGETBOLD,iStyle,0);
		GPCS.italic		=ScMethod(SCI_STYLEGETITALIC,iStyle,0);
		GPCS.underline	=ScMethod(SCI_STYLEGETUNDERLINE,iStyle,0);
		GPCS.visible	=ScMethod(SCI_STYLEGETVISIBLE,iStyle,0);
		GPCS.EOLFilled	=ScMethod(SCI_STYLEGETEOLFILLED,iStyle,0);
		GPCS.Case		=ScMethod(SCI_STYLEGETCASE,iStyle,0);
		GPCS.CharacterSet	=ScMethod(SCI_STYLEGETCHARACTERSET,iStyle,0);
		GPCS.HOTSPOT	=ScMethod(SCI_STYLEGETHOTSPOT,iStyle,0);
		GPCS.id=iStyle;
	}
	else
	if ((iStyle&GPSC_STYLETYPEMASK)==GPSC_STYLETYPEMARKER)
	{
		GPCS.bkg=ScMethod(SCI_MARKERGETBACK,iStyle,0);
		GPCS.frg=ScMethod(SCI_MARKERGETFORE,iStyle,0);
		GPCS.fontName="";
		GPCS.fontSize	=0;
		GPCS.bold		=0;
		GPCS.italic		=0;
		GPCS.underline	=0;
		GPCS.visible	=0;
		GPCS.EOLFilled	=0;
		GPCS.Case		=0;
		GPCS.CharacterSet	=ScMethod(SCI_MARKERGETDEFINE,iStyle,0);
		GPCS.HOTSPOT	=0;
		GPCS.id=iStyle;
	}
	else
	if ((iStyle&GPSC_STYLETYPEMASK)==GPSC_STYLETYPEINDIC)
	{
	}





	return ret;
}

void GPScintilla::SetStyleInfo(GPSCSTYLESET & GPCS)
{
	if ((GPCS.id&GPSC_STYLETYPEMASK)==GPSC_STYLETYPESTYLE)
	{
		ScMethod(SCI_STYLESETBACK,			GPCS.id,GPCS.bkg);
		ScMethod(SCI_STYLESETFORE,			GPCS.id,GPCS.frg);
		ScMethod(SCI_STYLESETFONT,			GPCS.id,(int)(LPCSTR)GPCS.fontName);
		ScMethod(SCI_STYLESETSIZE,			GPCS.id,GPCS.fontSize);
		ScMethod(SCI_STYLESETBOLD,			GPCS.id,GPCS.bold);
		ScMethod(SCI_STYLESETITALIC,		GPCS.id,GPCS.italic);
		ScMethod(SCI_STYLESETUNDERLINE,		GPCS.id,GPCS.underline);
		ScMethod(SCI_STYLESETVISIBLE,		GPCS.id,GPCS.visible);
		ScMethod(SCI_STYLESETEOLFILLED,		GPCS.id,GPCS.EOLFilled);
		ScMethod(SCI_STYLESETCASE,			GPCS.id,GPCS.Case);
		ScMethod(SCI_STYLESETCHARACTERSET,	GPCS.id,GPCS.CharacterSet);
		ScMethod(SCI_STYLESETHOTSPOT,		GPCS.id,GPCS.HOTSPOT);
	}
	else
	if ((GPCS.id&GPSC_STYLETYPEMASK)==GPSC_STYLETYPEMARKER)
	{
		ScMethod(SCI_MARKERSETBACK,	GPCS.id&0xFFFF,GPCS.bkg);
		ScMethod(SCI_MARKERSETFORE,	GPCS.id&0xFFFF,GPCS.frg);
		ScMethod(SCI_MARKERDEFINE,	GPCS.id&0xFFFF,GPCS.CharacterSet);
	}
	else
	if ((GPCS.id&GPSC_STYLETYPEMASK)==GPSC_STYLETYPEINDIC)
	{
	}
}


const GPSCSTYLESET * GPScintilla::StringToStyleInfo(const char *iStyle, GPSCSTYLESET & GPCS)
{
	const char *ident[18]={
		"F=",	"FS=",	"B=",	"I=",	"U=",
		"V=",	"E=",	"C=",	"CS=",	"H=",
		"FR=",	"FG=",	"FB=",	"BR=",	"BG=",
		"BB=",	"S=",	"SD=",
	};
	const int identlen[18]={2,3,2,2,2,2,2,2,3,2,3,3,3,3,3,3,2,3,};

	CString field;
	CString tmp;
	UINT i;
	for(i=0;i<18 && (field=ExtractField(iStyle,i+1,";"))!="";i++)
	{
		tmp=field;
		tmp.MakeUpper();
		UINT j;
		for(j=0;j<18 && strncmp(tmp,ident[j],identlen[j]);j++);

		if (j<18)
		{
			int atoipos=0;
			field.Delete(0,identlen[j]);
			if (j<17) field.MakeUpper();

			if (field.GetLength()==0) atoipos=0;
			else
			if (field[0]=='0') m_LastScanf=sscanf(field,"%o",&atoipos);
			else
			if (field[0]=='&') m_LastScanf=sscanf(((LPCSTR)field)+1,"%x",&atoipos);
			else
			if (field=="TRUE") atoipos=1;
			else
				atoipos=atoi(field);

			switch(j)
			{
			case 0:		/*F=Font*/			GPCS.fontName=field;	break;
			case 1:		/*FS=Size*/			GPCS.fontSize=atoipos;	break;
			case 2:		/*B=Bold*/			GPCS.bold=atoipos;		break;
			case 3:		/*I=Italic*/		GPCS.italic=atoipos;	break;
			case 4:		/*U=Underline*/		GPCS.underline=atoipos;	break;
			case 5:		/*V=Visible*/		GPCS.visible=atoipos;	break;
			case 6:		/*E=EOLFilled*/		GPCS.EOLFilled=atoipos;	break;
			case 7:		/*C=Case*/			GPCS.Case=atoipos;		break;
			case 8:		/*CS=CharacterSet*/	GPCS.CharacterSet=atoipos;	break;
			case 9:		/*H=HOTSPOT*/		GPCS.HOTSPOT=atoipos;	break;
			case 10:	/*FR=Rfore*/
				GPCS.frg=RGB(atoipos,GetGValue(GPCS.frg),GetBValue(GPCS.frg));
				break;
			case 11:	/*FG=Gfore*/
				GPCS.frg=RGB(GetRValue(GPCS.frg),atoipos,GetBValue(GPCS.frg));
				break;
			case 12:	/*FB=Bfore*/
				GPCS.frg=RGB(GetRValue(GPCS.frg),GetGValue(GPCS.frg),atoipos);
				break;
			case 13:	/*BR=Rback*/
				GPCS.bkg=RGB(atoipos,GetGValue(GPCS.bkg),GetBValue(GPCS.bkg));
				break;
			case 14:	/*BG=Gback*/
				GPCS.bkg=RGB(GetRValue(GPCS.bkg),atoipos,GetBValue(GPCS.bkg));
				break;
			case 15:	/*BB=Bback*/
				GPCS.bkg=RGB(GetRValue(GPCS.bkg),GetGValue(GPCS.bkg),atoipos);
				break;
			case 16:	/*S=style*/
				{
					GPCS.id=atoipos;
					if (GPCS.id==0)
					{
						UINT i333;
						for(i333=0;i333<GPScintilla::uNStyleType;i333++)
							if (field==GPScintilla::cArrStyleType[i333])
							{
								GPCS.id=GPScintilla::uArrStyleType[i333];
								GPCS.styleName=GPScintilla::cArrStyleType[i333];
								break;
							}
					}
					if (GPCS.styleName=="")
						GPCS.styleName.Format("STYLE - %3.3d",GPCS.id);
				}
				break;
			case 17:	/*SD=Description*/
				GPCS.StyleDescription=field;
				break;
			default:
				break;
			}
		}
	}
	GPCS.msize=sizeof(GPSCSTYLESET);

	return &GPCS;
}

const CString GPScintilla::StyleInfoToString(GPSCSTYLESET & GPCS)
{
	CString ret;
	ret.Format("%d\x7F%s\x7F%s\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x7F%d\x07%d\x07%d\x7F%d\x07%d\x07%d\x7F%s",
			GPCS.id,
			(LPCSTR)GPCS.styleName,
			(LPCSTR)GPCS.fontName,
			GPCS.fontSize,
			GPCS.bold,
			GPCS.italic,
			GPCS.underline,
			GPCS.visible,
			GPCS.EOLFilled,
			GPCS.Case,
			GPCS.CharacterSet,
			GPCS.HOTSPOT,
			GetRValue(GPCS.frg),GetGValue(GPCS.frg),GetBValue(GPCS.frg),
			GetRValue(GPCS.bkg),GetGValue(GPCS.bkg),GetBValue(GPCS.bkg),
			(LPCSTR)GPCS.StyleDescription
			);

	return ret;
}

const CString GPScintilla::StyleInfoToStringEx(GPSCSTYLESET & GPCS)
{
	CString ret;

	ret.Format("S=%d;F=%s;FS=%d;B=%d;I=%d;U=%d;V=%d;E=%d;C=%d;CS=%d;H=%d;FR=%d;FG=%d;FB=%d;BR=%d;BG=%d;BB=%d;SD=%s",
			GPCS.id,
			(LPCSTR)GPCS.fontName,
			GPCS.fontSize,
			GPCS.bold,
			GPCS.italic,
			GPCS.underline,
			GPCS.visible,
			GPCS.EOLFilled,
			GPCS.Case,
			GPCS.CharacterSet,
			GPCS.HOTSPOT,
			GetRValue(GPCS.frg),GetGValue(GPCS.frg),GetBValue(GPCS.frg),
			GetRValue(GPCS.bkg),GetGValue(GPCS.bkg),GetBValue(GPCS.bkg),
			(LPCSTR)GPCS.StyleDescription
			);

	return ret;
}

int GPScintilla::AppendChar(char iCh, UINT SelectionFlag=0)
{

	char tmps[5]={0,0,};
	*tmps=iCh;

	AppendBlock((const BYTE *)tmps,1,SelectionFlag);
	return iCh;
}

char * GPScintilla::AppendString(const char *iCh, UINT SelectionFlag=0)
{
	int len=(int)strlen(iCh);
	if (len>0)
		AppendBlock((const BYTE *)iCh,len,SelectionFlag);
	
	AppendBlock((const BYTE *)"\r\n",2,SelectionFlag);

	return (char *)iCh;
}

BYTE * GPScintilla::AppendBlock(const BYTE *iCh, UINT uBlockLen, UINT SelectionFlag)
{
	if (uBlockLen)
	{
		int rOnly=ScMethod(SCI_GETREADONLY,0,0);
		if (rOnly) ScMethod(SCI_SETREADONLY,0,0);
		ScMethod(SCI_APPENDTEXT,uBlockLen,(int)iCh);
		if (rOnly) ScMethod(SCI_SETREADONLY,1,0);

		if (SelectionFlag&0x1)
		{
			int fvl=0;
			int fvl2=ScMethod(SCI_GETFIRSTVISIBLELINE,0,0);
			do
			{
				fvl=fvl2;
				ScMethod(SCI_LINESCROLL,0,1000);
				fvl2=ScMethod(SCI_GETFIRSTVISIBLELINE,0,0);
			}
			while(fvl!=fvl2);
		}

		if (m_DirectInputFlag)
			ScMethod(SCI_GOTOPOS,ScMethod(SCI_GETTEXTLENGTH,0,0),0);

	}
	return (BYTE *)iCh;
}

UINT GPScintilla::StringToStyle(const char *iStyle,const char * delimiter = NULL)
{
	UINT ret=0;
	GPSCSTYLESET GPCS;
	char *tmps=new char [(int)strlen(iStyle)+10];
	strcpy(tmps,iStyle);
	char *pos=tmps;
	int delimLen=0;
	if (delimiter) delimLen=(int)strlen(delimiter);

	while(pos && *pos)
	{
		char *pos2=NULL;
		if (delimLen) pos2=strstr(pos,delimiter);
		if (pos2)
		{
			*(pos2)=0;
			pos2+=delimLen;
		}
		StringToStyleInfo(pos,GPCS);
		SetStyleInfo(GPCS);
		ret++;
		pos=pos2;
	}
	delete[] tmps;
	return ret;
}

void GPScintilla::SetUseWSColors(BOOL bFore, BOOL bBack)
{
	ScMethod(SCI_SETUSEWHITESPACEFORE,bFore,0);
	ScMethod(SCI_SETUSEWHITESPACEBACK,bBack,0);
}

UINT GPScintilla::GetText(char **EditText)
{
	UINT ret=0;
	if (EditText)
	{
		if (*EditText) delete[] *EditText;
		*EditText=NULL;
		ret=ScMethod(SCI_GETTEXTLENGTH,0,0);
		if (ret)
		{
			*EditText= new char [ret+1000];
			ScMethod(SCI_GETTEXT,ret+100,(int)*EditText);
		}
	}
	return ret;
}

UINT GPScintilla::GetSelText(char **EditText)
{
	UINT ret=0;
	if (EditText)
	{
		if (*EditText) delete[] *EditText;
		*EditText=NULL;
		ret=ScMethod(SCI_GETSELECTIONEND,0,0)-ScMethod(SCI_GETSELECTIONSTART,0,0);
		if (ret)
		{
			*EditText= new char [ret+1000];
			ScMethod(SCI_GETSELTEXT,0,(int)*EditText);
		}
	}
	return ret;
}

UINT GPScintilla::GetText(char **EditText,DWORD flags)
{
	UINT ret=0;
	if ((flags&SC_SAVE_SELECTION)==SC_SAVE_SELECTION)
		ret=GetSelText(EditText);
	else
		ret=GetText(EditText);
	return ret;
}

UINT GPScintilla::SetText(const char *iText, UINT uFlag)
{
	int curlen,selstart,selend;
	curlen=ScMethod(SCI_GETTEXTLENGTH,0,0);
	selstart=ScMethod(SCI_GETSELECTIONSTART,0,0);
	selend=ScMethod(SCI_GETSELECTIONEND,0,0);
	if (selstart>selend)
		{int tmp=selstart;selstart=selend;selend=tmp;}

	char *poss=(char *)iText;
	char *posnext=(char *)poss;
	int inslen=0;

	while(*poss)
	{
		int txtl=0;
		int c1=0,c2=0;
		int delta=0;

		while(*posnext && txtl<65000)
		{
			if (*posnext==10 || *posnext==13) txtl=0;
			else txtl++;
			posnext++;
			delta++;
		}
		inslen+=delta;

		if (*posnext)
		{c1=posnext[0];posnext[0]=13;c2=posnext[1];posnext[1]=0;}

		switch((uFlag&SC_REPLACE_POSITIONMASK))
		{
		case SC_REPLACE_ALL:
			ScMethod(SCI_SETTEXT,0,(int)poss);
			break;
		case SC_REPLACE_SELECTION:
			ScMethod(SCI_REPLACESEL,0,(int)poss);
			break;
		case SC_REPLACE_START:
			ScMethod(SCI_INSERTTEXT,0,(int)poss);
			break;
		case SC_REPLACE_END:
			ScMethod(SCI_INSERTTEXT,curlen,(int)poss);
			break;
		case SC_REPLACE_START|SC_REPLACE_SELECTION:
			ScMethod(SCI_INSERTTEXT,selstart,(int)poss);
			break;
		case SC_REPLACE_END|SC_REPLACE_SELECTION:
			ScMethod(SCI_INSERTTEXT,selend,(int)poss);
			break;
		}

		if (c1)
		{
			selend+=delta;
			selstart+=delta;
			curlen+=delta;
			posnext[0]=c1;posnext[1]=c2;
		}
		poss=posnext;
	}

	if ((uFlag&SC_REPLACE_SCROLL)==SC_REPLACE_SCROLL)
	{
		if (m_DirectInputFlag)
			switch((uFlag&SC_REPLACE_POSITIONMASK))
			{
			case SC_REPLACE_ALL:
			case SC_REPLACE_END:
				ScMethod(SCI_GOTOPOS,ScMethod(SCI_GETTEXTLENGTH,0,0),0);
				break;
			case SC_REPLACE_SELECTION:
			case SC_REPLACE_START|SC_REPLACE_SELECTION:
				ScMethod(SCI_GOTOPOS,selstart+inslen,0);
				break;
			case SC_REPLACE_START:
				ScMethod(SCI_GOTOPOS,inslen,0);
				break;
			case SC_REPLACE_END|SC_REPLACE_SELECTION:
				ScMethod(SCI_GOTOPOS,selend+inslen,0);
				break;
			}
		else
			switch((uFlag&SC_REPLACE_POSITIONMASK))
			{
			case SC_REPLACE_ALL:
				ScMethod(SCI_ENSUREVISIBLE,0,0);
				break;
			case SC_REPLACE_SELECTION:
				ScMethod(SCI_ENSUREVISIBLE,selstart,0);
				break;
			case SC_REPLACE_START:
				ScMethod(SCI_ENSUREVISIBLE,0,0);
				break;
			case SC_REPLACE_END:
				ScMethod(SCI_ENSUREVISIBLE,curlen,0);
				break;
			case SC_REPLACE_START|SC_REPLACE_SELECTION:
				ScMethod(SCI_ENSUREVISIBLE,selstart,0);
				break;
			case SC_REPLACE_END|SC_REPLACE_SELECTION:
				ScMethod(SCI_ENSUREVISIBLE,selend,0);
				break;
			}
	}
	return ScMethod(SCI_GETTEXTLENGTH,0,0);
}


BOOL GPScintilla::LoadText(CString &fName, UINT uFlag)
{
	BOOL ret=FALSE;
	if (fName=="" || fName.Find("*")>=0)
	{
		OPENFILENAME opf={0};
		#ifdef W_95
			opf.lStructSize=OPENFILENAME_SIZE_VERSION_400;
		#else
			#ifdef W_NT
				opf.lStructSize=OPENFILENAME_SIZE_VERSION_400;
			#else
				opf.lStructSize=sizeof(OPENFILENAME);
			#endif
		#endif

		opf.hwndOwner=m_hWnd;
		opf.lpstrFile = new char [1000];
		strcpy(opf.lpstrFile,fName);
		opf.nMaxFile =4900;
		opf.Flags =OFN_DONTADDTORECENT|OFN_ENABLESIZING|OFN_EXPLORER|OFN_FILEMUSTEXIST|OFN_LONGNAMES|OFN_NOCHANGEDIR|OFN_PATHMUSTEXIST|OFN_NOCHANGEDIR|OFN_SHOWHELP;

		if (GetOpenFileName(&opf))
			fName=opf.lpstrFile;
		delete[] opf.lpstrFile;
	}

	if (fName!="" && fName.Find("*")<0)
	{
		CFile mFile;
		try
		{
			mFile.Open(fName,CFile::modeRead|CFile::shareDenyNone,NULL);
			if (mFile.m_hFile!=CFile::hFileNull)
			{
				DWORD dwLength = (DWORD) mFile.GetLength();
				if (dwLength)
				{
					char *tmps=new char [dwLength+1000];
					int realLen=mFile.Read((void *)tmps,dwLength+900);
					tmps[realLen]=0;
					int ro=ScMethod(SCI_GETREADONLY,0,0);
					if (ro) ScMethod(SCI_SETREADONLY,0,0);
					SetText(tmps,uFlag);
					if (ro) ScMethod(SCI_SETREADONLY,ro,0);

					delete[] tmps;
				}
				mFile.Close();
			}
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("GPEDITOR", "LoadText",fName);
		}
	}
	return ret;
}

BOOL GPScintilla::SaveText(CString &fName, UINT uFlag)
{
	BOOL ret=FALSE;
	if (fName=="" || fName.Find("*")>=0)
	{
		OPENFILENAME opf={0};
		#ifdef W_95
			opf.lStructSize=OPENFILENAME_SIZE_VERSION_400;
		#else
			#ifdef W_NT
				opf.lStructSize=OPENFILENAME_SIZE_VERSION_400;
			#else
				opf.lStructSize=sizeof(OPENFILENAME);
			#endif
		#endif
		opf.hwndOwner=m_hWnd;
		opf.lpstrFile = new char [1000];
		if (fName!="") 
			strcpy(opf.lpstrFile,fName);
		else
			strcpy(opf.lpstrFile,m_csLastFileName);

		opf.nMaxFile =4900;
		opf.Flags =OFN_DONTADDTORECENT|OFN_ENABLESIZING|OFN_EXPLORER|OFN_LONGNAMES|OFN_NOCHANGEDIR|OFN_PATHMUSTEXIST|OFN_NOCHANGEDIR|OFN_SHOWHELP;

		if (GetSaveFileName(&opf))
		{
			fName=opf.lpstrFile;
			m_csLastFileName=fName;
		}
		delete[] opf.lpstrFile;
	}

	if (fName!="" && fName.Find("*")<0)
	{
		CFile mFile;
		try
		{
			if ((uFlag&SC_SAVE_APPEND)==SC_SAVE_APPEND)
				mFile.Open(fName,CFile::modeWrite|CFile::shareDenyNone,NULL);

			if (mFile.m_hFile==CFile::hFileNull)
				mFile.Open(fName,CFile::modeWrite|CFile::shareDenyNone|CFile::modeCreate,NULL);

			if (mFile.m_hFile!=CFile::hFileNull)
			{
				char *tmps=NULL;
				UINT len=0;
				if ((uFlag&SC_SAVE_SELECTION)==SC_SAVE_SELECTION)
					len=GetSelText(&tmps);
				else
					len=GetText(&tmps);
				if (len && len<0x10000000)
				{
					mFile.Write(tmps,len);
					ret=TRUE;
				}
				mFile.Close();
				if (tmps) delete[] tmps;
				tmps=NULL;
			}
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("GPEDITOR", "SaveText",fName);
		}
	}
	return ret;
}

DWORD GPScintilla::StringFromToReplaceStyle(const char *iReplaceStyle, DWORD & convReplaceStyle)
{
	const char *OptionName[]={
	"REPLACE_ALL","REPLACE_SELECTION","REPLACE_START","REPLACE_END","REPLACE_SCROLL",
	};
	const UINT  uOptionList[]={
	SC_REPLACE_ALL,SC_REPLACE_SELECTION,SC_REPLACE_START,SC_REPLACE_END,SC_REPLACE_SCROLL,
	};

	if (iReplaceStyle)
	{
		if (*iReplaceStyle)
		{
			char *tmps=new char [(int)strlen(iReplaceStyle)+100];
			strcpy(tmps,iReplaceStyle);
			_strupr(tmps);
			convReplaceStyle=atoi(tmps);
			UINT i;
			for(i=0;i<5;i++)
				if (strstr(tmps,OptionName[i]))
					convReplaceStyle|=uOptionList[i];
			delete[] tmps;
		}
		else
		{
			UINT convSD=convReplaceStyle;
			UINT i;
			for(i=0;i<5;i++)
				if (uOptionList[i]==0)
				{
					if ((convSD&SC_REPLACE_SELECTION)!=SC_REPLACE_SELECTION)
					{
						if (*iReplaceStyle) strcat((char *)iReplaceStyle,"|");
						strcat((char *)iReplaceStyle,OptionName[i]);
					}
				}
				else
				if ((convSD&uOptionList[i])==uOptionList[i])
				{
					if (*iReplaceStyle) strcat((char *)iReplaceStyle,"|");
					strcat((char *)iReplaceStyle,OptionName[i]);
					convSD^=uOptionList[i];
				}
				if (convSD) sprintf((char *)iReplaceStyle+(int)strlen(iReplaceStyle),"%s%d",*iReplaceStyle?"|":"",convSD);
		}
	}

	return convReplaceStyle;
}


DWORD GPScintilla::StringFromToSaveStyle(const char *iReplaceStyle, DWORD & convReplaceStyle)
{
	const char *OptionName[]={
	"SAVE_APPEND","SAVE_SELECTION","","","",
	};
	const UINT  uOptionList[]={
	SC_SAVE_APPEND,SC_SAVE_SELECTION,
	};

	if (iReplaceStyle)
	{
		if (*iReplaceStyle)
		{
			char *tmps=new char [(int)strlen(iReplaceStyle)+100];
			strcpy(tmps,iReplaceStyle);
			_strupr(tmps);
			convReplaceStyle=atoi(tmps);
			UINT i;
			for(i=0;i<2;i++)
				if (strstr(tmps,OptionName[i]))
					convReplaceStyle|=uOptionList[i];
			delete[] tmps;
		}
		else
		{
			UINT convSD=convReplaceStyle;
			UINT i;
			for(i=0;i<2;i++)
				if (uOptionList[i]==0)
				{
					if ((convSD&SC_REPLACE_SELECTION)!=SC_REPLACE_SELECTION)
					{
						if (*iReplaceStyle) strcat((char *)iReplaceStyle,"|");
						strcat((char *)iReplaceStyle,OptionName[i]);
					}
				}
				else
				if ((convSD&uOptionList[i])==uOptionList[i])
				{
					if (*iReplaceStyle) strcat((char *)iReplaceStyle,"|");
					strcat((char *)iReplaceStyle,OptionName[i]);
					convSD^=uOptionList[i];
				}
				if (convSD) sprintf((char *)iReplaceStyle+(int)strlen(iReplaceStyle),"%s%d",*iReplaceStyle?"|":"",convSD);
		}
	}

	return convReplaceStyle;
}


BOOL GPScintilla::LoadKeywords(UINT uLexerType)
{
	BOOL ret=FALSE;
	UINT uLexNum=0;
	for(uLexNum=0;*GPScintilla::cArrLexer[uLexNum] && GPScintilla::uArrLexer[uLexNum]!=uLexerType;uLexNum++);
	
	if (*GPScintilla::cArrLexer[uLexNum])
	{
		FILE *src=NULL;
		int i=0,nKeyLists=ScMethod(SCI_GETKEYWORDSCOUNT,0,0);

		for(i=0;i<nKeyLists;i++)
			ScMethod(SCI_SETKEYWORDS, i,0/*reinterpret_cast<LPARAM>(NULL)*/);

		src=fopen("LexKeywords.txt","rb");
		if (src)
		{
			ret=TRUE;
			char *tmps=new char [10000];
			while(fgetsEx(tmps,9990,src))
			{
				if (ExtractField(tmps,1,",")==GPScintilla::cArrLexer[uLexNum])
					ScMethod(SCI_SETKEYWORDS,atoi(ExtractField(tmps,2,",")),(int)FindField(tmps,3,","));
			}
			delete[] tmps;
			fclose(src);
		}
	}

	return ret;
}

BOOL GPScintilla::SaveKeywords(UINT uLexerType)
{
	BOOL ret=FALSE;
	UINT uLexNum=0;
	for(uLexNum=0; *GPScintilla::cArrLexer[uLexNum] && GPScintilla::uArrLexer[uLexNum]!=uLexerType;uLexNum++);
	
	if (*GPScintilla::cArrLexer[uLexNum])
	{
		int nKeyLists=ScMethod(SCI_GETKEYWORDSCOUNT,0,0);
		if (nKeyLists)
		{
			FILE *src=NULL;
			FILE *dst=NULL;
			src=fopen("LexKeywords.txt","rt");
			if (src)
			{
				dst=fopen("LexKeywords.tmp","wt");
				if (dst)
				{
					ret=TRUE;
					char *tmps=new char [10000];
					while(fgetsEx(tmps,9990,src))
					{
						if (ExtractField(tmps,1,",")!=GPScintilla::cArrLexer[uLexNum])
							fprintf(dst,"%s\n",tmps);
					}

					int i,j;
					for(i=0,j=0;i<100 && j<nKeyLists;i++)
					{
						char *keyarr=NULL;
						ScMethod(SCI_GETKEYWORDS,i,(int)&keyarr);
						if (keyarr)
						{
							if (*keyarr)
							{
								fprintf(dst,"%s,%d,%s\n",GPScintilla::cArrLexer[uLexNum],i,keyarr);
								j++;
							}

							delete[] keyarr;
						}
					}
					fclose(dst);
					delete[] tmps;
				}
				fclose(src);
				if (ret)
				{
					CopyFile("LexKeywords.tmp","LexKeywords.txt",FALSE);
				}
				DeleteFile("LexKeywords.tmp");
			}
		}
	}

	return ret;
}

BOOL GPScintilla::LoadColors(DWORD uLexerType, const char * cFileName)
{
	BOOL ret=FALSE;
	int nLexer;
	for(nLexer=0;*GPScintilla::cArrLexer[nLexer] && GPScintilla::uArrLexer[nLexer]!=uLexerType;nLexer++);

	if (*GPScintilla::cArrLexer[nLexer])
	{
		FILE *src=fopen(cFileName && *cFileName?cFileName:"LexerColors.txt","rt");
		if (src)
		{
			GPSCSTYLESET m_Clr={0};
			char *strtmp=new char [10000];

			while(fgetsEx(strtmp,9990,src))
			{
				char *posstl=strchr(strtmp,',');
				if (posstl)
				{
					*(posstl++)=0;
					if (*posstl && _stricmp(strtmp,GPScintilla::cArrLexer[nLexer])==0)
					{
							GPScintilla::StringToStyleInfo(posstl,m_Clr);
							SetStyleInfo(m_Clr);
							ret=TRUE;
					}
				}
			}

			delete[] strtmp;
			fclose(src);
		}
	}
	return ret;
}

void GPScintilla::SortText(DWORD sortFlag)
{
	char *text=NULL;
	GetSelText(&text);
	UINT selType=0;
	if (text) selType=1;
	else GetText(&text);

	if (text)
	{
		CListMaker lm;
		
		if ((sortFlag&SC_SORT_WORDS)==SC_SORT_WORDS)
		{
			char *pos=text;
			char *posres=text;

			while(*pos)
			{
				char *pos2=pos,*pos3=pos;
				while(*pos3 && *pos3!='\r')
					if (*pos3==' ' && (pos3[1]==' ' || pos3[1]=='\r')) pos3++;
					else *(pos2++)=*(pos3++);

				char endchar=*pos3;
				if (endchar) pos3++;
				*pos2=0;

				lm.SetList("tmp",pos,' ');

				if ((sortFlag&SC_SORT_DESC)==SC_SORT_DESC)
					lm.SortListDesc("tmp");
				else
					lm.SortList("tmp");

				if ((sortFlag&SC_SORT_UNIQUE)==SC_SORT_UNIQUE)
					lm.UniqueList("tmp");

				char *restmp=NULL;
				lm.GetList("tmp",&restmp,' ');
				if (restmp)
				{
					strcpy(posres,restmp);
					posres+=(int)strlen(posres);
					if (endchar)
						*(posres++)=endchar;

					delete[] restmp;
				}
				pos=pos3;
			}
			*(posres)=0;
		}
		else
		{
			lm.SetList("tmp",text,'\r');
			delete[] text;
			text=NULL;

			if ((sortFlag&SC_SORT_DESC)==SC_SORT_DESC) 
				lm.SortListDesc("tmp");
			else
				lm.SortList("tmp");

			if ((sortFlag&SC_SORT_UNIQUE)==SC_SORT_UNIQUE)
				lm.UniqueList("tmp");

			lm.GetList("tmp",&text,'\r');
		}

		int ro=ScMethod(SCI_GETREADONLY,0,0);
		if (ro) ScMethod(SCI_SETREADONLY,0,0);
		SetText(text,selType?SC_REPLACE_SELECTION:SC_REPLACE_ALL);
		if (ro) ScMethod(SCI_SETREADONLY,ro,0);
		delete[] text;
	}

}

UINT GPScintilla::GetLexerId(const char *iLexerName)
{
	UINT ret=-1;
	int i=0;
	for(i=0;*GPScintilla::cArrLexer[i] && _stricmp(GPScintilla::cArrLexer[i],iLexerName);i++);

	if (*GPScintilla::cArrLexer[i]) ret=GPScintilla::uArrLexer[i];

	return ret;
}

const char * GPScintilla::GetLexerName(DWORD iLexerID)
{
	const char * ret="";
	int i=0;
	for(i=0;*GPScintilla::cArrLexer[i] && GPScintilla::uArrLexer[i]!=iLexerID;i++);

	if (*GPScintilla::cArrLexer[i]) ret=GPScintilla::cArrLexer[i];

	return ret;
}


#include "DlgFileItemName.h"

BOOL GPScintilla::SaveOnServerSide(const char *FileName, const char *ItemName, DWORD SaveFlags)
{
	BOOL ret=FALSE;
	if (m_Comm.IsConnected())
	{
		CString tmps;
		CString csFileName=FileName;
		CString csItemName=ItemName;
		UINT retdlg=IDOK;
		while(retdlg==IDOK && (csFileName=="" || csFileName.FindOneOf("^[]")>=0 || csItemName=="" || csItemName.FindOneOf("^[]")>=0))
		{
			CDlgFileItemName dlg;
			if (csFileName=="") csFileName=m_csLastSrvFileName;
			if (csItemName=="") csItemName=m_csLastSrvItemName;

			dlg.SetFileName(csFileName);
			dlg.SetItemName(csItemName);

			if ((retdlg=dlg.DoModal())==IDOK)
			{
				csFileName=m_csLastSrvFileName=dlg.GetFileName();
				csItemName=m_csLastSrvItemName=dlg.GetItemName();
			}
		}
		if (retdlg==IDOK)
		{
			EnterCriticalSection(&GPC.m_View->m_CSRemap);
			AnsiToDos(csFileName,csFileName,1);
			AnsiToDos(csItemName,csItemName,1);
			char cStyle[250];
			*cStyle=0;
			GPScintilla::StringFromToSaveStyle(cStyle,SaveFlags);

			m_Comm.GPSendLine("SVSUB\r");
			tmps.Format("%c%c%d%c%s%c%s%c%s%c%s%c%s\r",
				250,
				250,
				59,0xFE,
				"SV",0xFE,
				"SaveInput",0xFE,
				(LPCSTR)csFileName,0xFE,
				(LPCSTR)csItemName,0xFE,
				cStyle
				);
			m_Comm.GPSendLine(tmps);
			LeaveCriticalSection(&GPC.m_View->m_CSRemap);
		}
	}
	return ret;
}

BOOL GPScintilla::LoadFromServerSide(const char *FileName, const char *ItemName, DWORD SaveFlags)
{
	BOOL ret=FALSE;
	if (m_Comm.IsConnected())
	{
		CString tmps;
		char cStyle[250];
		*cStyle=0;
		GPScintilla::StringFromToReplaceStyle(cStyle,SaveFlags);

		CString csFileName=FileName;
		CString csItemName=ItemName;

		UINT retdlg=IDOK;
		while(retdlg==IDOK && (csFileName=="" || csFileName.FindOneOf("^[]")>=0 || csItemName=="" || csItemName.FindOneOf("^[]")>=0))
		{
			CDlgFileItemName dlg;
			if (csFileName=="") csFileName=m_csLastSrvFileName;
			if (csItemName=="") csItemName=m_csLastSrvItemName;

			dlg.SetFileName(csFileName);
			dlg.SetItemName(csItemName);

			if ((retdlg=dlg.DoModal())==IDOK)
			{
				csFileName=m_csLastSrvFileName=dlg.GetFileName();
				csItemName=m_csLastSrvItemName=dlg.GetItemName();
			}
		}
		if (retdlg==IDOK)
		{
			EnterCriticalSection(&GPC.m_View->m_CSRemap);

			AnsiToDos(csFileName,csFileName,1);
			AnsiToDos(csItemName,csItemName,1);

			m_Comm.GPSendLine("SVSUB\r");
			tmps.Format("%c%c%d%c%s%c%s%c%s%c%s%c%s\r",
				250,
				250,
				59,0xFE,
				"SV",0xFE,
				"LoadInput",0xFE,
				(LPCSTR)csFileName,0xFE,
				(LPCSTR)csItemName,0xFE,
				cStyle
				);
			m_Comm.GPSendLine(tmps);

			LeaveCriticalSection(&GPC.m_View->m_CSRemap);
		}
	}
	return ret;
}

HMENU GPScintilla::SCCreatePopupMenu(DWORD iMenuType)
{
	HMENU m_Menu=::CreatePopupMenu();

	if (m_Menu)
		switch(iMenuType)
		{
		case SCCMND_TYPESAVE:
			#ifdef RUS
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SAVESELCLIENT,		"Сохранить выделенное на компьютере");
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SAVECLIENTAS,			"Сохранить как ... на компьютере");
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SAVESELCLIENTAS,		"Сохранить как ... выделенное на компьютере");
				if (m_Comm.IsConnected())	
				{
					::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SAVESERVER,		"Сохранить на сервере");
					::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SAVESELSERVER,	"Сохранить выделенное на сервере");
					::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SAVESERVERAS,		"Сохранить как ... на сервере");
					::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SAVESELSERVERAS,	"Сохранить как ... выделенное на сервере");
				}
			#else
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SAVESELCLIENT,		"Save Selection on Workstation");
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SAVECLIENTAS,			"Save As ... on Workstation");
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SAVESELCLIENTAS,		"Save Selection As ... on Workstation");
				if (m_Comm.IsConnected())	
				{
					::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SAVESERVER,		"Save on Server");
					::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SAVESELSERVER,	"Save Selection on Server");
					::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SAVESERVERAS,		"Save As ... on Server");
					::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SAVESELSERVERAS,	"Save Selection As ... on Server");
				}
			#endif
			break;
		case SCCMND_TYPELOAD:
			#ifdef RUS
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_LOADCLIENTFROM,		"Загрузить из файла на компьютере");
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_LOADINSCLIENT,		"Вставить из текущего файла на компьютере");
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_LOADINSCLIENTFROM,	"Вставить из файла на компьютере");
				if (m_Comm.IsConnected())	
				{
					::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_LOADSERVER,		"Загрузить с сервера");
					::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_LOADSERVERFROM,	"Загрузить из файла на сервере");
					::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_LOADINSSERVER,	"Вставить с сервера");
					::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_LOADINSSERVERFROM,"Вставить из файла на сервере");
				}
			#else
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_LOADCLIENTFROM,		"Load from client file");
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_LOADINSCLIENT,		"Insert form client");
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_LOADINSCLIENTFROM,	"Insert form client file");
				if (m_Comm.IsConnected())	
				{
					::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_LOADSERVER,		"Load from server");
					::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_LOADSERVERFROM,	"Load from server file");
					::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_LOADINSSERVER,	"Insert from server");
					::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_LOADINSSERVERFROM,"Insert from server file");
				}
			#endif
			break;
		case SCCMND_TYPESORT:
			#ifdef RUS
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SORTDESC				,"Сортировать абзацы по убыванию");
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SORTWORDSASC			,"Сортировать слова");
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SORTWORDSDESC			,"Сортировать слова по убыванию");
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SORTUNIQUETASC		,"Сортировать уникальные абзацы");
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SORTUNIQUETDESC		,"Сортировать уникальные абзацы по убыванию");
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SORTUNIQUETWORDSASC	,"Сортировать уникальные слова");
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SORTUNIQUETWORDSDESC	,"Сортировать уникальные слова по убыванию");
			#else
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SORTDESC				,"Sort paragraph (desc)");
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SORTWORDSASC			,"Sort words (asc)");
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SORTWORDSDESC			,"Sort words (desc)");
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SORTUNIQUETASC		,"Sort and unique paragraph (asc)");
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SORTUNIQUETDESC		,"Sort and unique paragraph (desc)");
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SORTUNIQUETWORDSASC	,"Sort and unique words (asc)");
				::AppendMenu(m_Menu,MF_STRING|MF_ENABLED|MF_STRING,SCCMND_SORTUNIQUETWORDSDESC	,"Sort and unique words (desc)");
			#endif
			break;
		default:
			::DestroyMenu(m_Menu);
			m_Menu=NULL;
		}

	return m_Menu;
}

void GPScintilla::OnDestroy() 
{
	if (m_AutoSaveFlag)
		SaveText(m_csDefClFileName,SC_SAVE_ALL|SC_SAVE_REPLACE);

	if (m_FindDlg)
	{
		if (m_FindDlg->DelRef(this)==0 && m_FindDlg->m_hWnd)
		{
			m_FindDlg->DestroyWindow();
			delete m_FindDlg;
			m_FindDlg=NULL;
		}
	}

	Scincillafn=NULL;
	Scincillaptr=NULL;
	InitFnPtr=TRUE;

	CWnd::OnDestroy();
}

DWORD GPScintilla::ShowFindDialog(DWORD dwFlags)
{
	DWORD ret=0;

	if (m_FindDlg==NULL)
		m_FindDlg=new CDlgGPScintillaFind;

	if (m_FindDlg && m_FindDlg->m_hWnd==NULL)
		m_FindDlg->Create(IDD_DLGSCFIND,GPC.m_View);

	if (dwFlags)
	{
		
		if (m_FindDlg && m_FindDlg->m_hWnd)
		{
			m_FindDlg->AddRef(this);
			m_FindDlg->SetCurrentEditor(this);

			int start=ScMethod(SCI_GETSELECTIONSTART,0,0);
			int end=ScMethod(SCI_GETSELECTIONEND,0,0);
			int sellen=end-start;
			if (sellen<0) sellen=-sellen;
			char *seltext=NULL;
			if (sellen<100)
				GetSelText(&seltext);

			if (seltext && *seltext)
			{
				unsigned char *pos=(unsigned char *)seltext;
				while(*pos && *pos!=10 && *pos!=13) pos++;
				*pos=0;
				if (*seltext)
				{
					m_FindDlg->SetFindText((const char *)seltext);
					m_FindDlg->UpdateCombos();
				}
				delete[] seltext;
			}
			ret=m_FindDlg->ShowWindow(SW_SHOW);
			m_FindDlg->SetWindowPos(GetParent(),0,0,0,0,SWP_NOREPOSITION/*|SWP_NOACTIVATE*/|SWP_NOMOVE|SWP_NOSIZE);
			::EnableWindow(m_FindDlg->m_hWnd,TRUE);
			::SetFocus(::GetDlgItem(m_FindDlg->m_hWnd,IDC_COMBOFIND));
		}
	}
	else
	{
		if (m_FindDlg && m_FindDlg->m_hWnd)
		{
			m_FindDlg->ShowWindow(SW_HIDE);
		}
	}

	return ret;
}

void GPScintilla::CloseFindDialog() 
{
	if (m_FindDlg && m_FindDlg->m_hWnd)
		::ShowWindow(m_FindDlg->m_hWnd,SW_HIDE);
}

DWORD GPScintilla::LoadLockKeys()
{
	if (m_ArrLockKey) 
	{
		delete m_ArrLockKey;
		m_ArrLockKey=NULL;
	}

	if (m_FileNameLK!="")
	{
		FILE *fl=fopen(m_FileNameLK,"rt");
		if (fl)
		{
			char str[500];
			while(fgets(str,490,fl))
			{
				DWORD hotkey=0;
				if (*str=='+')
				{
					strcat(str,"|");
					GP_HotKey::StringFromToHotKey(str,hotkey);
					if ((hotkey&0xFFFF0000))
					{
						if (m_ArrLockKey==NULL)	m_ArrLockKey=new GP_RarefiedArr<DWORD>(5,0);
						if (m_ArrLockKey) (*m_ArrLockKey)[hotkey]=hotkey;
					}
				}
			}
			fclose(fl);
		}
	}
	return m_ArrLockKey?m_ArrLockKey->GetCount():0;
}

void GPScintilla::SetLineColPositionText()
{
	long nStartChar,nEndChar;
	nStartChar=ScMethod(SCI_GETSELECTIONSTART,0,0);
	nEndChar=ScMethod(SCI_GETSELECTIONEND,0,0);

	if (nStartChar!=lastSelPos || lastSelPos!=nEndChar)
	{
		lastSelPos=nStartChar;
		char str[1000];
		if (LineObjId>=0 && (UINT)LineObjId<(*referGPU)->m_NGPUNIT && referGPU[LineObjId])
		{
			if (nStartChar==nEndChar)
				sprintf(str,"TEXT=%s%d",(LPCSTR)LinePrefix, SendMessage(EM_LINEFROMCHAR,nStartChar,0)+1);
			else
				sprintf(str,"TEXT=%s%d - %d",(LPCSTR)LinePrefix, SendMessage(EM_LINEFROMCHAR,nStartChar,0)+1, SendMessage(EM_LINEFROMCHAR,nEndChar,0)+1);
			referGPU[LineObjId]->GPSetProperty(str);
		}
		if (ColumnObjId>=0 && (UINT)ColumnObjId<(*referGPU)->m_NGPUNIT && referGPU[ColumnObjId])
		{
			if (nStartChar==nEndChar)
				sprintf(str,"TEXT=%s%d",(LPCSTR)ColumnPrefix,ScMethod(SCI_GETCOLUMN,nStartChar,0)+1);
			else
				sprintf(str,"TEXT=%s%d - %d",(LPCSTR)ColumnPrefix,ScMethod(SCI_GETCOLUMN,nStartChar,0)+1,ScMethod(SCI_GETCOLUMN,nEndChar,0)+1);
			referGPU[ColumnObjId]->GPSetProperty(str);
		}
		if (CharObjId>=0 && (UINT)CharObjId<(*referGPU)->m_NGPUNIT && referGPU[CharObjId])
		{
			sprintf(str,"TEXT=%s%d",(LPCSTR)CharPrefix,SendMessage(SCI_GETCHARAT,nStartChar,0));
			referGPU[CharObjId]->GPSetProperty(str);
		}
	}
}

void GPScintilla::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
	SetLineColPositionText();
}

void GPScintilla::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CWnd::OnRButtonDown(nFlags, point);
	SetLineColPositionText();
	m_bTrackMousePos=TRUE;
}

void GPScintilla::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonDown(nFlags, point);
	SetLineColPositionText();
	m_bTrackMousePos=TRUE;
}

void GPScintilla::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonUp(nFlags, point);
	SetLineColPositionText();
	m_bTrackMousePos=FALSE;
}

void GPScintilla::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CWnd::OnRButtonUp(nFlags, point);
	SetLineColPositionText();
	m_bTrackMousePos=FALSE;
}

void GPScintilla::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd::OnMouseMove(nFlags, point);
	if (m_bTrackMousePos==TRUE)	SetLineColPositionText();
}

void GPScintilla::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CWnd::OnChar(nChar, nRepCnt, nFlags);
	if (nChar==13 && m_AutoIndentFlag)
	{
		int curpos=SendMessage(SCI_GETCURRENTPOS,0,0);
		int curline=SendMessage(SCI_LINEFROMPOSITION,curpos,0);
		int curindent=ScMethod(SCI_GETLINEINDENTATION,curline-1,0);
		if (curindent)
		{
			ScMethod(SCI_SETLINEINDENTATION,curline,curindent);
			int newpos=ScMethod(SCI_GETLINEINDENTPOSITION,curline,0);
			ScMethod(SCI_GOTOPOS,newpos,0);
			ScMethod(SCI_CHOOSECARETX,0,0);
		}
	}
	SetLineColPositionText();
}

void GPScintilla::Print(DWORD showDialog, const char *ccAdditionalData) 
{
	if (!ccAdditionalData) ccAdditionalData="";
	if (showDialog&0x10) EditorPrintSettings.m_UseSelection=1;
	CString csTmpHeader=ExtractField(ccAdditionalData,1,"\x01");
	CString csTmpFooter=ExtractField(ccAdditionalData,2,"\x01");
	CString csTmpHeaderRestore=EditorPrintSettings.csheaderFormat;
	CString csTmpFooterRestore=EditorPrintSettings.csfooterFormat;

	if (csTmpHeader!="") EditorPrintSettings.csheaderFormat=csTmpHeader;
	if (csTmpFooter!="") EditorPrintSettings.csfooterFormat=csTmpFooter;
	EditorPrintSettings.csAdditionalString=ExtractField(ccAdditionalData,3,"\x01");;

	PRINTDLG pdlg = {0};
	pdlg.lStructSize=sizeof(PRINTDLG);
	pdlg.hwndOwner = GPC.m_hViewWnd;
	pdlg.hInstance = AfxGetInstanceHandle();
	pdlg.Flags = PD_USEDEVMODECOPIES | PD_ALLPAGES | PD_RETURNDC;
	pdlg.nFromPage = 1;
	pdlg.nToPage = 1;
	pdlg.nMinPage = 1;
	pdlg.nMaxPage = 0xFFFFU; // We do not know how many pages in the
	// document until the printer is selected and the paper size is known.
	pdlg.nCopies = 1;
	pdlg.hDC = 0;

	// See if a range has been selected
	cScCharacterRange crange;
	int startPos = crange.cpMin = ScMethod(SCI_GETSELECTIONSTART,0,0);
	int endPos = crange.cpMax =  ScMethod(SCI_GETSELECTIONEND,0,0);

	if (startPos == endPos) showDialog&=(0xFFFFFFFF^0x10);

	if (!(showDialog&0x1)) 
	{
		pdlg.Flags |= PD_RETURNDEFAULT;
		if ((showDialog&0x10)==0 || EditorPrintSettings.m_UseSelection==0) startPos = endPos;
	}

	if (startPos == endPos) pdlg.Flags |= PD_NOSELECTION;
	 else 	 pdlg.Flags |= PD_SELECTION;

	if (((showDialog&0x2)==0 || EditorPrintSettings.SetupDlg()!=IDCANCEL) && ((showDialog&0x1)==0 || ::PrintDlg(&pdlg)))
	{
		int lbWidth=ScMethod(SCI_GETMARGINWIDTHN,1,0);
		int lbType=ScMethod(SCI_GETMARGINTYPEN,1,0);


		if (EditorPrintSettings.m_PrintLineNumber)
		{
			ScMethod(SCI_SETMARGINTYPEN,1,1);
			ScMethod(SCI_SETMARGINWIDTHN,1,46);
		}
		else
			ScMethod(SCI_SETMARGINWIDTHN,1,0);


		HDC hdc = pdlg.hDC;

		CRect rectMargins, rectPhysMargins;
		POINT ptPage;
		POINT ptDpi;

		// Get printer resolution
		ptDpi.x = GetDeviceCaps(hdc, LOGPIXELSX);    // dpi in X direction
		ptDpi.y = GetDeviceCaps(hdc, LOGPIXELSY);    // dpi in Y direction

		// Start by getting the physical page size (in device units).
		ptPage.x = GetDeviceCaps(hdc, PHYSICALWIDTH);   // device units
		ptPage.y = GetDeviceCaps(hdc, PHYSICALHEIGHT);  // device units

		// Get the dimensions of the unprintable
		// part of the page (in device units).
		rectPhysMargins.left = GetDeviceCaps(hdc, PHYSICALOFFSETX);
		rectPhysMargins.top = GetDeviceCaps(hdc, PHYSICALOFFSETY);

		// To get the right and lower unprintable area,
		// we take the entire width and height of the paper and
		// subtract everything else.
		rectPhysMargins.right = ptPage.x						// total paper width
								- GetDeviceCaps(hdc, HORZRES) // printable width
								- rectPhysMargins.left;				// left unprintable margin

		rectPhysMargins.bottom = ptPage.y						// total paper height
								 - GetDeviceCaps(hdc, VERTRES)	// printable height
								 - rectPhysMargins.top;				// right unprintable margin

		// At this point, rectPhysMargins contains the widths of the
		// unprintable regions on all four sides of the page in device units.

		// Take in account the page setup given by the user (if one value is not null)
		if (EditorPrintSettings.pagesetupMargin.left != 0 || EditorPrintSettings.pagesetupMargin.right != 0 ||
				EditorPrintSettings.pagesetupMargin.top != 0 || EditorPrintSettings.pagesetupMargin.bottom != 0) {
			CRect rectSetup;

			// Convert the hundredths of millimeters (HiMetric) or
			// thousandths of inches (HiEnglish) margin values
			// from the Page Setup dialog to device units.
			// (There are 2540 hundredths of a mm in an inch.)

			char localeInfo[3];
			GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_IMEASURE, localeInfo, 3);

			if (localeInfo[0] == '0') {	// Metric system. '1' is US System
				rectSetup.left = MulDiv (EditorPrintSettings.pagesetupMargin.left, ptDpi.x, 2540);
				rectSetup.top = MulDiv (EditorPrintSettings.pagesetupMargin.top, ptDpi.y, 2540);
				rectSetup.right	= MulDiv(EditorPrintSettings.pagesetupMargin.right, ptDpi.x, 2540);
				rectSetup.bottom	= MulDiv(EditorPrintSettings.pagesetupMargin.bottom, ptDpi.y, 2540);
			} else {
				rectSetup.left	= MulDiv(EditorPrintSettings.pagesetupMargin.left, ptDpi.x, 1000);
				rectSetup.top	= MulDiv(EditorPrintSettings.pagesetupMargin.top, ptDpi.y, 1000);
				rectSetup.right	= MulDiv(EditorPrintSettings.pagesetupMargin.right, ptDpi.x, 1000);
				rectSetup.bottom	= MulDiv(EditorPrintSettings.pagesetupMargin.bottom, ptDpi.y, 1000);
			}

			// Dont reduce margins below the minimum printable area
			rectMargins.left	= 	rectPhysMargins.left > rectSetup.left?rectPhysMargins.left:rectSetup.left;
			rectMargins.top		=	rectPhysMargins.top >  rectSetup.top?rectPhysMargins.top: rectSetup.top;
			rectMargins.right	=	rectPhysMargins.right > rectSetup.right ?rectPhysMargins.right: rectSetup.right;
			rectMargins.bottom	=	rectPhysMargins.bottom > rectSetup.bottom ?rectPhysMargins.bottom: rectSetup.bottom;
		} else {
			rectMargins.left	= rectPhysMargins.left;
			rectMargins.top	= rectPhysMargins.top;
			rectMargins.right	= rectPhysMargins.right;
			rectMargins.bottom	= rectPhysMargins.bottom;
		}

		// rectMargins now contains the values used to shrink the printable
		// area of the page.

		// Convert device coordinates into logical coordinates
		DPtoLP(hdc, (LPPOINT) &rectMargins, 2);
		DPtoLP(hdc, (LPPOINT)&rectPhysMargins, 2);

		// Convert page size to logical units and we're done!
		DPtoLP(hdc, (LPPOINT) &ptPage, 1);

		TEXTMETRIC tm;
		int headerLineHeight =0;
		int footerLineHeight =0;
		HFONT fontFooter = NULL;
		HFONT fontHeader = NULL;

		if (EditorPrintSettings.m_UseHeader && (showDialog&0x100)==0 && EditorPrintSettings.csheaderFormat.GetLength())
		{
			headerLineHeight = ::MulDiv(EditorPrintSettings.sdHeader.fontSize? EditorPrintSettings.sdHeader.fontSize:9, ptDpi.y, 72);
			fontHeader = ::CreateFont(headerLineHeight,
									0, 0, 0,
									EditorPrintSettings.sdHeader.bold ? FW_BOLD : FW_NORMAL,
									EditorPrintSettings.sdHeader.italic,
									EditorPrintSettings.sdHeader.underline,
									0, 0, 0,
									0, 0, 0,
									EditorPrintSettings.sdHeader.fontName != "" ? EditorPrintSettings.sdHeader.fontName : "Arial");
			::SelectObject(hdc, fontHeader);
			::GetTextMetrics(hdc, &tm);
			headerLineHeight = tm.tmHeight + tm.tmExternalLeading;

		}

		if (EditorPrintSettings.m_UseFooter && (showDialog&0x200)==0 && EditorPrintSettings.csfooterFormat.GetLength())
		{
			footerLineHeight = ::MulDiv( EditorPrintSettings.sdFooter.fontSize ? EditorPrintSettings.sdFooter.fontSize : 9, ptDpi.y, 72);
			fontFooter = ::CreateFont(footerLineHeight,
								0, 0, 0,
								EditorPrintSettings.sdFooter.bold ? FW_BOLD : FW_NORMAL,
								EditorPrintSettings.sdFooter.italic,
								EditorPrintSettings.sdFooter.underline,
								0, 0, 0,
								0, 0, 0,
								EditorPrintSettings.sdFooter.fontName != "" ? EditorPrintSettings.sdFooter.fontName : "Arial");
			::SelectObject(hdc, fontFooter);
			::GetTextMetrics(hdc, &tm);
			footerLineHeight = tm.tmHeight + tm.tmExternalLeading;
		}

		DOCINFO di = {sizeof(DOCINFO), 0, 0, 0, 0};
		di.lpszDocName = "Doc name";
		di.lpszOutput = 0;
		di.lpszDatatype = 0;
		di.fwType = 0;
		if (::StartDoc(hdc, &di) < 0) 
		{
			MessageBox("Can't start printer document.","Editor Print",MB_OK);
			return;
		}

		LONG lengthDoc = ScMethod(SCI_GETLENGTH,0,0);
		LONG lengthDocMax = lengthDoc;
		LONG lengthPrinted = 0;

		// Requested to print selection
		if (pdlg.Flags & PD_SELECTION)
		{
			if (startPos > endPos)
			{
				lengthPrinted = endPos;
				lengthDoc = startPos;
			}
			else 
			{
				lengthPrinted = startPos;
				lengthDoc = endPos;
			}

			if (lengthPrinted < 0)			lengthPrinted = 0;
			if (lengthDoc > lengthDocMax)	lengthDoc = lengthDocMax;
		}

		// We must substract the physical margins from the printable area
		RangeToFormat frPrint;
		frPrint.hdc = hdc;
		frPrint.hdcTarget = hdc;
		frPrint.rc.left = rectMargins.left - rectPhysMargins.left;
		frPrint.rc.top = rectMargins.top - rectPhysMargins.top;
		frPrint.rc.right = ptPage.x - rectMargins.right - rectPhysMargins.left;
		frPrint.rc.bottom = ptPage.y - rectMargins.bottom - rectPhysMargins.top;
		frPrint.rcPage.left = 0;
		frPrint.rcPage.top = 0;
		frPrint.rcPage.right = ptPage.x - rectPhysMargins.left - rectPhysMargins.right - 1;
		frPrint.rcPage.bottom = ptPage.y - rectPhysMargins.top - rectPhysMargins.bottom - 1;
		if (EditorPrintSettings.csheaderFormat.GetLength())
			frPrint.rc.top += headerLineHeight + headerLineHeight / 2;
		if (EditorPrintSettings.csfooterFormat.GetLength())
			frPrint.rc.bottom -= footerLineHeight + footerLineHeight / 2;
		// Print each page
		int pageNum = 1;
		bool printPage;

		while (lengthPrinted < lengthDoc)
		{
			printPage = (!(pdlg.Flags & PD_PAGENUMS) ||
						 (pageNum >= pdlg.nFromPage) && (pageNum <= pdlg.nToPage));
			if (printPage)
			{
				::StartPage(hdc);

				if (EditorPrintSettings.m_UseHeader && (showDialog&0x100)==0 && EditorPrintSettings.csheaderFormat.GetLength())
				{
					CString sHeader=EditorPrintSettings.GetFormatedHeaderString(pageNum);

					::SetTextColor(hdc, EditorPrintSettings.sdHeader.frg);
					::SetBkColor(hdc, EditorPrintSettings.sdHeader.bkg);
					::SelectObject(hdc, fontHeader);
					UINT ta = ::SetTextAlign(hdc, TA_BOTTOM);
					RECT rcw = {frPrint.rc.left, frPrint.rc.top - headerLineHeight - headerLineHeight / 2,
								frPrint.rc.right, frPrint.rc.top - headerLineHeight / 2};
					rcw.bottom = rcw.top + headerLineHeight;
					::ExtTextOut(hdc, frPrint.rc.left + 5, frPrint.rc.top - headerLineHeight / 2,
								 ETO_OPAQUE, &rcw, sHeader,
								 static_cast<int>(sHeader.GetLength()), NULL);
					::SetTextAlign(hdc, ta);
					HPEN pen = ::CreatePen(0, 1, EditorPrintSettings.sdHeader.frg);
					HPEN penOld = static_cast<HPEN>(::SelectObject(hdc, pen));
					::MoveToEx(hdc, frPrint.rc.left, frPrint.rc.top - headerLineHeight / 4, NULL);
					::LineTo(hdc, frPrint.rc.right, frPrint.rc.top - headerLineHeight / 4);
					::SelectObject(hdc, penOld);
					::DeleteObject(pen);
				}
			}

			frPrint.chrg.cpMin = lengthPrinted;
			frPrint.chrg.cpMax = lengthDoc;

			lengthPrinted = ScMethod(SCI_FORMATRANGE,printPage,reinterpret_cast<LPARAM>(&frPrint));

			if (printPage) 
			{
				if (EditorPrintSettings.m_UseFooter && (showDialog&0x200)==0 && EditorPrintSettings.csfooterFormat.GetLength()) 
				{
					CString sFooter=EditorPrintSettings.GetFormatedFooterString(pageNum);
					::SetTextColor(hdc, EditorPrintSettings.sdFooter.frg);
					::SetBkColor(hdc, EditorPrintSettings.sdFooter.bkg);
					::SelectObject(hdc, fontFooter);
					UINT ta = ::SetTextAlign(hdc, TA_TOP);
					RECT rcw = {frPrint.rc.left, frPrint.rc.bottom + footerLineHeight / 2,
								frPrint.rc.right, frPrint.rc.bottom + footerLineHeight + footerLineHeight / 2};
					::ExtTextOut(hdc, frPrint.rc.left + 5, frPrint.rc.bottom + footerLineHeight / 2,
								 ETO_OPAQUE, &rcw, sFooter,
								 static_cast<int>(sFooter.GetLength()), NULL);
					::SetTextAlign(hdc, ta);
					HPEN pen = ::CreatePen(0, 1, EditorPrintSettings.sdFooter.frg);
					HPEN penOld = static_cast<HPEN>(::SelectObject(hdc, pen));
					::SetBkColor(hdc, EditorPrintSettings.sdFooter.frg);
					::MoveToEx(hdc, frPrint.rc.left, frPrint.rc.bottom + footerLineHeight / 4, NULL);
					::LineTo(hdc, frPrint.rc.right, frPrint.rc.bottom + footerLineHeight / 4);
					::SelectObject(hdc, penOld);
					::DeleteObject(pen);
				}

				::EndPage(hdc);
			}
			pageNum++;

			if ((pdlg.Flags & PD_PAGENUMS) && (pageNum > pdlg.nToPage))		break;
		}

		ScMethod(SCI_FORMATRANGE, FALSE, 0);

		::EndDoc(hdc);
		::DeleteDC(hdc);
		if (fontHeader)
			::DeleteObject(fontHeader);
		if (fontFooter) 
			::DeleteObject(fontFooter);

		ScMethod(SCI_SETMARGINTYPEN,1,lbType);
		ScMethod(SCI_SETMARGINWIDTHN,1,lbWidth);

		if (csTmpHeader==EditorPrintSettings.csheaderFormat)
			EditorPrintSettings.csheaderFormat=csTmpHeaderRestore;
		if (csTmpFooter==EditorPrintSettings.csfooterFormat)
			EditorPrintSettings.csfooterFormat=csTmpFooterRestore;
		EditorPrintSettings.SaveSettings();
	}
	else
	{
		EditorPrintSettings.csheaderFormat=csTmpHeaderRestore;
		EditorPrintSettings.csfooterFormat=csTmpFooterRestore;
	}

}

BOOL GPScintilla::MarginClick(int position, int modifiers) 
{
	int lineClick = ScMethod(SCI_LINEFROMPOSITION, position, 0);
	//Platform::DebugPrintf("Margin click %d %d %x\n", position, lineClick,
	//	SendEditor(SCI_GETFOLDLEVEL, lineClick) & SC_FOLDLEVELHEADERFLAG);
	if ((modifiers & SCMOD_SHIFT) && (modifiers & SCMOD_CTRL))	FoldAll();
	else 
	{
		int levelClick = ScMethod(SCI_GETFOLDLEVEL, lineClick, 0);
		if (levelClick & SC_FOLDLEVELHEADERFLAG)
		{
			if (modifiers & SCMOD_SHIFT) 
			{
				// Ensure all children visible
				ScMethod(SCI_SETFOLDEXPANDED, lineClick, 1);
				Expand(lineClick, TRUE, TRUE, 100, levelClick);
			}
			else 
			if (modifiers & SCMOD_CTRL)
			{
				if (ScMethod(SCI_GETFOLDEXPANDED, lineClick,0))
				{
					// Contract this line and all children
					ScMethod(SCI_SETFOLDEXPANDED, lineClick, 0);
					Expand(lineClick, FALSE, TRUE, 0, levelClick);
				}
				else
				{
					// Expand this line and all children
					ScMethod(SCI_SETFOLDEXPANDED, lineClick, 1);
					Expand(lineClick, TRUE, TRUE, 100, levelClick);
				}
			}
			else 
			{
				// Toggle this line
				ScMethod(SCI_TOGGLEFOLD, lineClick,0);
			}
		}
	}
	return TRUE;
}

void GPScintilla::Expand(int &line, BOOL doExpand, BOOL force, int visLevels, int level)
{
	int lineMaxSubord = ScMethod(SCI_GETLASTCHILD, line, level & SC_FOLDLEVELNUMBERMASK);
	line++;
	while (line <= lineMaxSubord)
	{
		if (force)
		{
			if (visLevels > 0)	ScMethod(SCI_SHOWLINES, line, line);
			else				ScMethod(SCI_HIDELINES, line, line);
		}
		else 
			if (doExpand)	ScMethod(SCI_SHOWLINES, line, line);

		int levelLine = level;
		if (levelLine == -1) levelLine = ScMethod(SCI_GETFOLDLEVEL, line, 0);
		if (levelLine & SC_FOLDLEVELHEADERFLAG)
		{
			if (force)
			{
				if (visLevels > 1)	ScMethod(SCI_SETFOLDEXPANDED, line, 1);
				else				ScMethod(SCI_SETFOLDEXPANDED, line, 0);
				Expand(line, doExpand, force, visLevels - 1);
			}
			else
			{
				if (doExpand)
				{
					if (!ScMethod(SCI_GETFOLDEXPANDED, line, 0))
						ScMethod(SCI_SETFOLDEXPANDED, line, 1);
					Expand(line, TRUE, force, visLevels - 1);
				}
				else
					Expand(line, FALSE, force, visLevels - 1);
			}
		}
		else line++;
	}
}

void GPScintilla::FoldAll()
{
	ScMethod(SCI_COLOURISE, 0, -1);
	int maxLine = ScMethod(SCI_GETLINECOUNT, 0, 0);
	BOOL expanding = TRUE;
	int lineSeek ;
	for(lineSeek = 0; lineSeek < maxLine; lineSeek++) 
		if (ScMethod(SCI_GETFOLDLEVEL, lineSeek, 0) & SC_FOLDLEVELHEADERFLAG)
		{
			expanding = !ScMethod(SCI_GETFOLDEXPANDED, lineSeek, 0);
			break;
		}

	int line ;
	for(line = 0; line < maxLine; line++)
	{
		int level = ScMethod(SCI_GETFOLDLEVEL, line, 0);
		if ((level & SC_FOLDLEVELHEADERFLAG) && (SC_FOLDLEVELBASE == (level & SC_FOLDLEVELNUMBERMASK))) 
		{
			if (expanding) 
			{
				ScMethod(SCI_SETFOLDEXPANDED, line, 1);
				Expand(line, TRUE, FALSE, 0, level);
				line--;
			}
			else 
			{
				int lineMaxSubord = ScMethod(SCI_GETLASTCHILD, line, -1);
				ScMethod(SCI_SETFOLDEXPANDED, line, 0);
				if (lineMaxSubord > line)
					ScMethod(SCI_HIDELINES, line + 1, lineMaxSubord);
			}
		}
	}
}


int GPScintilla::GetWordsList(int iMinLen, char **oBuff)
{
	int ret=0;
	int textlen=ScMethod(SCI_GETTEXTLENGTH,0,0);
	if (textlen>1 && oBuff)
	{
		if (*oBuff) delete[] *oBuff;
		*oBuff=new char [textlen+10];
		ret=ScMethod(SCI_GETTEXT,textlen,(int)(*oBuff));
		char *postmp=*oBuff;
		char *postmp2;

		while(*postmp)
		{
 			if ((*postmp<'A' || *postmp>'z' || (*postmp>'Z' && *postmp<'a')) && strchr("_.@&%",*postmp)==NULL) *postmp=' ';
			postmp++;
		}

		if (iMinLen>0) 
		{
			postmp=*oBuff;
			while(*postmp)
			{
				while(*postmp && *postmp==' ') postmp++;
				postmp2=postmp;
				while(*postmp2 && *postmp2!=' ') postmp2++;
				if (postmp2-postmp<iMinLen)
					while(*postmp && postmp2>postmp) *(postmp++)=' ';
				postmp=postmp2;
			}
		}

		postmp=*oBuff;
		while(*postmp)
		{
			while(*postmp && *postmp==' ') postmp++;
			if (*postmp>='0' && *postmp<='9')
				while(*postmp && *postmp!=' ') *(postmp++)=' ';
			else
				while(*postmp && *postmp!=' ') postmp++;
		}

		int nItems=0;
		postmp2=postmp=*oBuff;
		while(*postmp2)
		{
			nItems++;
			while(*postmp2 && *postmp2==' ') postmp2++;
			while((*(postmp++)=*(postmp2)) && *(postmp2++)!=' ');
		}

		while(postmp>*oBuff && *(--postmp)==' ') *postmp=0;

		char *SrcBuff= new char [postmp-*oBuff+100];
		char *SrcBuff2= new char [postmp-*oBuff+100];
		char **PtrBfr = new char * [nItems+100];
		char **PtrBfrPos=PtrBfr;
		long delta=SrcBuff-SrcBuff2;

		strcpy(SrcBuff,*oBuff);
		strcpy(SrcBuff2,*oBuff);
		_strupr(postmp2=SrcBuff2);
		nItems=0;
		while(*postmp2)
		{
			nItems++;
			*(PtrBfrPos++)=postmp2;
			while(*(++postmp2) && *postmp2!=' ');
			if (*postmp2) *(postmp2++)=*(postmp2+delta)=0;
		}
		*(PtrBfrPos)=postmp2;

		qsCharLine((const char **)PtrBfr,0,nItems-1);
		char **PtrBfrPos2=PtrBfr;

		postmp2=*oBuff;
		while(PtrBfrPos2!=PtrBfrPos)
		{
			if (strcmp(*PtrBfrPos2,*(PtrBfrPos2+1)))
			{
				char *src=*PtrBfrPos2+delta;
				while((*(postmp2)=*(src++))) postmp2++;
				*(postmp2++)=' ';
			}
			PtrBfrPos2++;
		}
		if (postmp2!=*oBuff) *(--postmp2)=0;
		
		delete[] PtrBfr;
		delete[] SrcBuff;
		delete[] SrcBuff2;
		ret=nItems;
	}
	return ret;
}

int GPScintilla::CheckEnteredLength(int iLen)
{
	if (iLen<0)
	{
		TextRange tr={0};
		tr.chrg.cpMax=ScMethod(SCI_GETSELECTIONSTART,0,0);
		tr.chrg.cpMin=tr.chrg.cpMax<25?0:tr.chrg.cpMax-25;
		char tmps[200];
		tr.lpstrText=tmps;
		int nChars=ScMethod(SCI_GETTEXTRANGE,0,(int)&tr);
		iLen=0;
		if (nChars>0)
		{
			while(--nChars>=0 && tr.lpstrText[nChars]>32 && strchr(m_PBdelim1,tr.lpstrText[nChars])==NULL) 
				iLen++;
			if (nChars<0) iLen=0;
		}
	}
	return iLen;
}

int GPScintilla::SelectWord(int Position)
{
	if (Position<0) Position=ScMethod(SCI_GETSELECTIONSTART,0,0);

	TextRange tr={0};
	tr.chrg.cpMax=Position+100;
	tr.chrg.cpMin=tr.chrg.cpMax<200?0:tr.chrg.cpMax-200;

	char tmps[500];
	tr.lpstrText=tmps;
	int nCharsAll=ScMethod(SCI_GETTEXTLENGTH,0,0);
	if (tr.chrg.cpMax>nCharsAll) tr.chrg.cpMax=nCharsAll;
	int nChars=ScMethod(SCI_GETTEXTRANGE,0,(int)&tr);
	int i;
	for(i=Position-tr.chrg.cpMin-1;i>=0 && tr.lpstrText[i]>32 && strchr(m_PBdelim1,tr.lpstrText[i])==NULL;i--);
	int ret=tr.chrg.cpMin+i+1;
	ScMethod(SCI_SETSELECTIONSTART,ret,0);
	for(i=Position-tr.chrg.cpMin;i<nChars && tr.lpstrText[i]>32 && strchr(m_PBdelim1,tr.lpstrText[i])==NULL;i++);
	ret=i+tr.chrg.cpMin-ret;
	ScMethod(SCI_SETSELECTIONEND,i+tr.chrg.cpMin,0);
	return ret;
}

HBRUSH GPScintilla::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = NULL;
	if (referGPU && referGPU[UnitId&0xFFFF]->m_brBkgnd) 
	{
		hbr = (HBRUSH) *(referGPU[UnitId&0xFFFF]->m_brBkgnd);
	    RECT rc;
		::GetWindowRect(pWnd->m_hWnd, &rc);
		::MapWindowPoints(NULL, m_hWnd, (POINT *)&rc, 2);
		::SetBrushOrgEx(pDC->m_hDC, -rc.left, -rc.top, NULL);
	}

	if (pWnd && pDC && pWnd->m_hWnd && pDC->m_hDC)
		GPUnit::ChildCtlColor(referGPU, pDC->m_hDC, pWnd->m_hWnd, hbr, CWnd::OnCtlColor(pDC, pWnd, nCtlColor), nCtlColor);

	return hbr;
}

int GPScintilla::AddChar(char iChar, DWORD iFlags)
{
	int ret=0;
	if (iChar)
	{
		DWORD tmpDIFlag=m_DirectInputFlag;
		m_DirectInputFlag=0;

		int TextLen=ScMethod(SCI_GETLENGTH,0,0);
		ScMethod(SCI_SETSEL,TextLen,TextLen);
		char ReplText[]={0,0,};
		*ReplText=iChar;
		int ro=ScMethod(SCI_GETREADONLY,0,0);
		if (ro) ScMethod(SCI_SETREADONLY,0,0);

		if (iChar==GPC.DelimiterIn1 && (iFlags&0x8))
			iChar=10;
		if (iChar==GPC.DelimiterIn2 && (iFlags&0x8))
			iChar=13;

		if ((m_DOflags&0xFF)==13 && (iFlags&0x2))
		{
			if (iChar==10)
			{
				*ReplText=13;
				ScMethod(SCI_REPLACESEL,0,(int)ReplText);
				*ReplText=10;
				ScMethod(SCI_REPLACESEL,0,(int)ReplText);
				TextLen++;
				TextLen++;
			}
			else
			{
				TextLen=ScMethod(SCI_POSITIONFROMLINE,ScMethod(SCI_GETLINECOUNT, 0, 0)-1,0);
				ScMethod(SCI_SETSEL,TextLen,-1);
				ScMethod(SCI_REPLACESEL,0,(int)"");
			}
		}

		if (iChar==13 && (iFlags&0x2))
		{
		}
		else
		if (iChar==10 && (iFlags&0x2))
		{
			if ((m_DOflags&0xFF)!=13)
			{
				*ReplText=13;
				ScMethod(SCI_REPLACESEL,0,(int)ReplText);
				*ReplText=10;
				ScMethod(SCI_REPLACESEL,0,(int)ReplText);
				TextLen++;
				TextLen++;
			}
		}
		else 
		if (iChar==8 && (iFlags&0x4))
		{
			if (TextLen)
			{
				ScMethod(SCI_SETSEL,TextLen-1,TextLen);
				ScMethod(SCI_REPLACESEL,0,(int)"");
			}
		}
		else
		{
			ScMethod(SCI_REPLACESEL,0,(int)ReplText);
			TextLen++;
		}

		if (ro) ScMethod(SCI_SETREADONLY,ro,0);
		m_DirectInputFlag=tmpDIFlag;
		m_DOflags=(m_DOflags&0xFFFFFF00)|iChar;
		ret=TextLen;
	}
	return ret;
}

int GPScintilla::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message) 
{
	int ret=CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
	if (m_bAutoFocus && ::GetFocus()!=m_hWnd)
		::PostMessage(m_hWnd,GPM_SETFOCUSTOWND,(WPARAM)m_hWnd,0);
	return ret;
}

