// StringFormatPlus.cpp: implementation of the CStringFormatPlus class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "StringFormatPlus.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//const char *CStringFormatPlus::ccA[]={"","","","","","","",};
//const xxxx CStringFormatPlus::iA[]={,,,,,,,0,};

const char *CStringFormatPlus::ccAStringFormatFlags[]={
	"DIRECTIONRIGHTTOLEFT","DIRECTIONVERTICAL","NOFITBLACKBOX","DISPLAYFORMATCONTROL","NOFONTFALLBACK",
	"MEASURETRAILINGSPACES","NOWRAP","LINELIMIT","NOCLIP","",
	};
const DWORD CStringFormatPlus::iAStringFormatFlags[]={
	StringFormatFlagsDirectionRightToLeft,StringFormatFlagsDirectionVertical,StringFormatFlagsNoFitBlackBox,StringFormatFlagsDisplayFormatControl,StringFormatFlagsNoFontFallback,
	StringFormatFlagsMeasureTrailingSpaces,StringFormatFlagsNoWrap,StringFormatFlagsLineLimit,StringFormatFlagsNoClip,0,
	};

const char *CStringFormatPlus::ccAStringAlignment[]={"Near","Center","Far","",};
const Gdiplus::StringAlignment CStringFormatPlus::iAStringAlignment[]={StringAlignmentNear,StringAlignmentCenter,StringAlignmentFar,StringAlignmentNear,};

const char *CStringFormatPlus::ccAStringDigitSubstitute[]={"User","None","National","Traditional","",};
const Gdiplus::StringDigitSubstitute CStringFormatPlus::iAStringDigitSubstitute[]={StringDigitSubstituteUser,StringDigitSubstituteNone,StringDigitSubstituteNational,StringDigitSubstituteTraditional,StringDigitSubstituteUser,};

const char *CStringFormatPlus::ccAHotkeyPrefix[]={"None","Show","Hide","",};
const Gdiplus::HotkeyPrefix CStringFormatPlus::iAHotkeyPrefix[]={HotkeyPrefixNone,HotkeyPrefixShow,HotkeyPrefixHide,HotkeyPrefixNone,};

const char *CStringFormatPlus::ccAStringTrimming[]={
	"None","Character","Word","EllipsisCharacter","EllipsisWord","EllipsisPath","",};
const Gdiplus::StringTrimming CStringFormatPlus::iAStringTrimming[]={
	StringTrimmingNone,StringTrimmingCharacter,StringTrimmingWord,StringTrimmingEllipsisCharacter,StringTrimmingEllipsisWord,StringTrimmingEllipsisPath,StringTrimmingNone,};


const UINT CStringFormatPlus::uNMethods=19;
const char *CStringFormatPlus::cArrMethods[]={
/*00*/		"GetAlignment","GetDigitSubstitutionLanguage","GetDigitSubstitutionMethod","GetFormatFlags","GetLastStatus",
/*05*/		"GetLineAlignment","GetMeasurableCharacterRangeCount","GetTabStopCount","GetTrimming","GetHotkeyPrefix",
/*10*/		"GetTabStops","SetAlignment","SetDigitSubstitution","SetFormatFlags","SetHotkeyPrefix",
/*15*/		"SetLineAlignment","SetMeasurableCharacterRanges","SetTabStops","SetTrimming","",
/*20*/		"","","","","",
/*25*/		"","","","","",
	};
const char *CStringFormatPlus::cArrMethodsParams[]={
/*00*/		"","","","","",
/*05*/		"","","","","",
/*10*/		"","StringAlignment","language,substitute","FormatFlags","HotkeyPrefix",
/*15*/		"StringAlignment","First1,Length1[;First2,Length2[....]]","firstTabOffset,TabStop1[,TabStop1","StringTrimming","",
/*20*/		"","","","","",
/*25*/		"","","","","",
	};

 
CStringFormatPlus::CStringFormatPlus(CODContext *ip_Context, INT formatFlags, LANGID language)
{
	p_Context=ip_Context;
	m_StringFormat=new StringFormat(formatFlags, language);
}

CStringFormatPlus::CStringFormatPlus(CODContext *ip_Context, StringFormat *pStringFormat)
{
	p_Context=ip_Context;
	m_StringFormat=NULL;
	SetStringFormat(pStringFormat);
}

CStringFormatPlus::CStringFormatPlus(CODContext *ip_Context, const char *iStr)
{
	p_Context=ip_Context;
	if (iStr && *iStr)
	{
		if (_stricmp(iStr,"Default")==0) m_StringFormat= new StringFormat(StringFormat::GenericDefault());
		else
		if (_stricmp(iStr,"Typographic")==0) m_StringFormat= new StringFormat(StringFormat::GenericTypographic());
		else
		{
			DWORD dwFormatFlags=atoi(iStr);
			LANGID lngid=0;
			CString tmpCS;
			if (*iStr!='0' &&  dwFormatFlags==0)
			{
				tmpCS=ExtractField(iStr,1,",");
				tmpCS.MakeUpper();
				int i;
				for(i=0; *ccAStringFormatFlags[i];i++) 
					if (tmpCS.Find(ccAStringFormatFlags[i])>=0) dwFormatFlags|=iAStringFormatFlags[i];
			}

			tmpCS=ExtractField(iStr,2,",");
			if (tmpCS!="")  lngid=atoi(tmpCS);
			
			m_StringFormat=new StringFormat(dwFormatFlags,lngid);
		}
	}
	if (!m_StringFormat) m_StringFormat=new StringFormat(0,0);
}

CStringFormatPlus::~CStringFormatPlus()
{
	if (m_StringFormat) delete m_StringFormat;
	m_StringFormat=NULL;
}


UINT CStringFormatPlus::DoMethod(const char *iStr, char *oStr)
{
	int nfunc=0;
	char met[150];
	strncpy(met,iStr,145);
	met[145]=0;
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int retint=-123456; 
	int atoipos=atoi(pos);
	const char *pos2=pos;
	while(*pos2!=0 && *pos2!=',' && *pos2!='=') pos2++;
	if (*pos2!=0) pos2++;

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

	switch(nfunc)
	{
	case  0: //GetAlignment
		retint=m_StringFormat->GetAlignment();
		break;
	case  1: //GetDigitSubstitutionLanguage
		retint=m_StringFormat->GetDigitSubstitutionLanguage();
		break;
	case  2: //GetDigitSubstitutionMethod
		retint=m_StringFormat->GetDigitSubstitutionMethod();
		break;
	case  3: //GetFormatFlags
		retint=m_StringFormat->GetFormatFlags();
		break;
	case  4: //GetLastStatus
		retint=m_StringFormat->GetLastStatus();
		break;
	case  5: //GetLineAlignment
		retint=m_StringFormat->GetLineAlignment();
		break;
	case  6: //GetMeasurableCharacterRangeCount
		retint=m_StringFormat->GetMeasurableCharacterRangeCount();
		break;
	case  7: //GetTabStopCount
		retint=m_StringFormat->GetTabStopCount();
		break;
	case  8: //GetTrimming
		retint=m_StringFormat->GetTrimming();
		break;
	case  9: //GetHotkeyPrefix
		retint=m_StringFormat->GetHotkeyPrefix();
		break;
	case 10: //GetTabStops
		if (oStr)
		{
			INT nTabStops=m_StringFormat->GetTabStopCount();
			REAL *tabStops=new REAL [nTabStops+10];
			REAL firstTabOffset=0;
			m_StringFormat->GetTabStops(nTabStops,&firstTabOffset, tabStops);
			INT i;
			char *outpos=oStr;
			outpos+=sprintf(outpos,"%g",firstTabOffset);
			for(i=0;i<nTabStops;i++)
				outpos+=sprintf(outpos,"\x7F%g",tabStops[i]);
			delete []tabStops;
		}
		break;
	case 11: //SetAlignment StringAlignment
	case 15: //SetLineAlignment StringAlignment
		{
			retint=m_StringFormat->GetAlignment();
			StringAlignment stringAlignment=StringAlignmentNear;
			if (*pos && *pos>='0' && *pos<='9') stringAlignment=(Gdiplus::StringAlignment)atoi(pos);
			else
			{
				int i;
				for(i=0;*ccAStringAlignment[i] && _stricmp(pos,ccAStringAlignment[i])!=0;i++);
				stringAlignment=iAStringAlignment[i];
			}
			if (nfunc==11)	m_StringFormat->SetAlignment(stringAlignment);
				else		m_StringFormat->SetLineAlignment(stringAlignment);
		}
		break;
	case 12: //SetDigitSubstitution language,substitute
		{
			retint=m_StringFormat->GetDigitSubstitutionLanguage();
			LANGID language=atoipos;
			StringDigitSubstitute substitute=StringDigitSubstituteUser;
			CString tmpCS=ExtractField(pos,2,",");
			if (tmpCS!="")
			{
				if (tmpCS[0]>='0' && tmpCS[0]<='9') substitute=(Gdiplus::StringDigitSubstitute)atoi(tmpCS);
				else
				{
					int i;
					for(i=0;*ccAStringDigitSubstitute[i] && _stricmp(tmpCS,ccAStringDigitSubstitute[i])!=0;i++);
					substitute=iAStringDigitSubstitute[i];
				}
			}
			m_StringFormat->SetDigitSubstitution(language,substitute);
		}
		break;
	case 13: //SetFormatFlags FormatFlags
		{
			DWORD stringFormatFlags=0;
			CString tmpCS=pos;
			if (tmpCS[0]>='0' && tmpCS[0]<='9') stringFormatFlags=(Gdiplus::StringFormatFlags)atoi(tmpCS);
			else
			if (tmpCS!="")
			{
				tmpCS.MakeUpper();
				int i;
				for(i=0; *ccAStringFormatFlags[i];i++) 
					if (tmpCS.Find(ccAStringFormatFlags[i])>=0) stringFormatFlags|=iAStringFormatFlags[i];
			}
			m_StringFormat->SetFormatFlags((Gdiplus::StringFormatFlags)stringFormatFlags);
		}
		break;
	case 14: //SetHotkeyPrefix HotkeyPrefix
		{
			retint=m_StringFormat->GetHotkeyPrefix();
			HotkeyPrefix hotkeyPrefix=HotkeyPrefixNone;
			if (*pos && *pos>='0' && *pos<='9') hotkeyPrefix=(Gdiplus::HotkeyPrefix)atoi(pos);
			else
			{
				int i;
				for(i=0;*ccAHotkeyPrefix[i] && _stricmp(pos,ccAHotkeyPrefix[i])!=0;i++);
				hotkeyPrefix=iAHotkeyPrefix[i];
			}
			m_StringFormat->SetHotkeyPrefix(hotkeyPrefix);
		}
		break;
	case 16: //SetMeasurableCharacterRanges First1,Length1[;First2,Length2[....]]
		{
			INT cnt=1;
			retint=m_StringFormat->GetMeasurableCharacterRangeCount();
			const char *pos3=pos;
			while(*pos) if (*(pos++)==';') cnt++;
			CharacterRange *pCharacterRange=new CharacterRange[cnt+10];
			pos3=pos;
			cnt=0;
			while(*pos3)
			{
				sscanf(pos3,"%g,%g",&pCharacterRange[cnt].First,&pCharacterRange[cnt].Length);
				cnt++;
				while(*pos3 && *(pos3++)!=';');
			}
			if (cnt) m_StringFormat->SetMeasurableCharacterRanges(cnt,pCharacterRange);
			delete []pCharacterRange;
		}
		break;
	case 17: //SetTabStops firstTabOffset,TabStop1[,TabStop1
		{
			INT cnt=0;
			REAL firstTabOffset=(REAL)atof(pos);
			retint=m_StringFormat->GetTabStopCount();
			const char *pos3=pos;
			while(*pos) if (*(pos++)==',') cnt++;
			REAL *pTabStop=new REAL[cnt+10];
			pos3=strchr(pos,',');
			if (pos3++==NULL) pos3="";
			cnt=0;
			while(*pos3)
			{
				sscanf(pos3,"%g",pTabStop+cnt);
				cnt++;
				while(*pos3 && *(pos3++)!=',');
			}
			if (cnt) m_StringFormat->SetTabStops(firstTabOffset,cnt,pTabStop);
			delete []pTabStop;
		}
		break;
	case 18: //SetTrimming StringTrimming
		 
		{
			retint=m_StringFormat->GetTrimming();
			StringTrimming stringTrimming=StringTrimmingNone;
			if (*pos && *pos>='0' && *pos<='9') stringTrimming=(Gdiplus::StringTrimming)atoi(pos);
			else
			{
				int i;
				for(i=0;*ccAStringTrimming[i] && _stricmp(pos,ccAStringTrimming[i])!=0;i++);
				stringTrimming=iAStringTrimming[i];
			}
			m_StringFormat->SetTrimming(stringTrimming);
		}
		break;

	default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
	}
	if (oStr && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);

	return nfunc;
}


const StringFormat *CStringFormatPlus::SetStringFormat(StringFormat *pStringFormat)
{
	if (pStringFormat)
	{
		if (m_StringFormat) delete m_StringFormat;
		m_StringFormat=pStringFormat;
	}
	return m_StringFormat;
}