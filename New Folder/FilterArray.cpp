// FilterArray.cpp: implementation of the CFilterArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "FilterArray.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC( CFilterArray , CObject )

CFilterArray::CFilterArray()
{
	m_uMaxFilter=10;
	m_Array =new SPRFILTERITEM * [m_uMaxFilter];
	UINT i;
	for(i=0; i<m_uMaxFilter;i++)
		m_Array[i]=NULL;
	m_uNFilter=0;
}

CFilterArray::~CFilterArray()
{
	if (m_Array)
	{
		UINT i;
		for(i=0; i<m_uMaxFilter;i++)
			if (m_Array[i]) 
			{
				delete m_Array[i];
				m_Array[i]=NULL;
			}
		delete[] m_Array;
		m_Array=NULL;
	}
	m_uNFilter=0;
}

const SPRFILTERITEM * CFilterArray::GetFilter(const char *FilterName)
{
	const SPRFILTERITEM * tmp=NULL;
	UINT i;
	if (m_Array)
		for(i=0; i<m_uNFilter;i++)
			if (m_Array[i] && strcmp(m_Array[i]->csName,FilterName)==0)
			{
				tmp=m_Array[i];
				break;
			}
	return tmp;
}

UINT CFilterArray::DeleteFilter(const char *FilterName)
{
	UINT i;
	if (m_Array)
		for(i=0; i<m_uNFilter;i++)
			if (m_Array[i] && strcmp(m_Array[i]->csName,FilterName)==0)
			{
				delete m_Array[i];
				UINT j;
				for(j=i+1;j<m_uNFilter;j++)
					m_Array[j-1]=m_Array[j];
				m_uNFilter--;
				m_Array[m_uNFilter]=NULL;
				i--;
			}
	return m_uNFilter;
}

UINT CFilterArray::DeleteFilter(UINT FieldNum)
{
	UINT i;
	if (m_Array && m_uNFilter)
		for(i=m_uNFilter-1; i>=0 && i<m_uNFilter;i--)
			if (m_Array[i] && m_Array[i]->nField==FieldNum)
			{
				delete m_Array[i];
				UINT j;
				for(j=i+1;j<m_uNFilter;j++)
					m_Array[j-1]=m_Array[j];
				m_uNFilter--;
				m_Array[m_uNFilter]=NULL;
			}
	return m_uNFilter;
}


UINT CFilterArray::GetCount()
{
	return m_uNFilter;
}
const char * CFilterArray::GetFilterName(UINT uNFilter)
{
	const char *ret="";
	if (m_Array && uNFilter<m_uNFilter && m_Array[uNFilter])
		ret=m_Array[uNFilter]->csName;
	return ret;
}

UINT CFilterArray::GetFilterId(const char *iFilterName)
{
	UINT ret =(UINT)-1;
	if (m_Array)
	{
		UINT i;
		for(i=0; i<m_uNFilter;i++)
			if (m_Array[i] && strcmp(m_Array[i]->csName,iFilterName)==0)
			{
				ret=i;
				break;
			}
	}
	return ret;
}

void CFilterArray::DeleteAll()
{
	if (m_Array)
	{
		UINT i;
		for(i=0; i<m_uMaxFilter;i++)
			if (m_Array[i]) 
			{
				delete m_Array[i];
				m_Array[i]=NULL;
			}
	}
	m_uNFilter=0;
}

UINT CFilterArray::SetFilter(UINT nItem, const char *iStrFilter, UINT LogType)
{
	DeleteFilter(nItem);
	char *tmpstr=new char [(int)strlen(iStrFilter)+50];
	sprintf(tmpstr,"'%s'%s",LogType==0?"AND":LogType==1?"OR":"XOR",iStrFilter);
	char *pos=tmpstr;
	while(pos && *pos)
	{
		char *pos2=pos;
		UINT oper=0;
		while(*pos2)
			if (*(pos2++)=='\'')
			{
				if (strncmp(pos2,"OR'",3)==0) {oper=1;pos2+=3;break;}
				if (strncmp(pos2,"AND'",4)==0) {oper=2;pos2+=4;break;}
				if (strncmp(pos2,"XOR'",4)==0) {oper=3;pos2+=4;break;}
			}

		char *pos3=pos2;

		while(*pos2)
			if (*(pos2++)=='\'')
			{
				if (strncmp(pos2,"OR'",3)==0 ||
					strncmp(pos2,"AND'",4)==0 ||
					strncmp(pos2,"XOR'",4)==0) {pos2--;break;}
			}

		if (*pos2) *pos2=0;
		else pos2=NULL;

		if (oper)
		{
			PSPRFILTERITEM lpFilterItem=CreateFilter(nItem);
			if (lpFilterItem)
			{
				lpFilterItem->uLogOperation=oper;
				lpFilterItem->uCompare=0;
				lpFilterItem->csFilter="";
				char tmp[10];
				strncpy(tmp,pos3,8);tmp[8]=0;
				_strupr(tmp);
				char *postmp=strchr(tmp,',');
				if (postmp) *postmp=0;
				else postmp="";
				
				postmp=strchr(pos3,',');
				if (postmp) postmp++;
				else postmp="";

				if (strchr(tmp,'>')) lpFilterItem->uCompare|=0x0001;
				if (strchr(tmp,'<')) lpFilterItem->uCompare|=0x0002;
				if (strchr(tmp,'#')) lpFilterItem->uCompare|=0x0003;
				if (lpFilterItem->uCompare!=0x0003 && strchr(tmp,'=')) lpFilterItem->uCompare|=0x0004;
				if (lpFilterItem->uCompare==0)
				{
					if (strchr(tmp,'G')) lpFilterItem->uCompare|=0x0001;
					if (strchr(tmp,'L')) lpFilterItem->uCompare|=0x0002;
					if (strchr(tmp,'N')) lpFilterItem->uCompare|=0x0003;
					if (strchr(tmp,'E')) lpFilterItem->uCompare|=0x0004;
					if (strchr(tmp,'I')) lpFilterItem->uCompare=0x0018;
					if (lpFilterItem->uCompare==0 && strchr(tmp,'M')) lpFilterItem->uCompare=0x0019;
					else
					if (lpFilterItem->uCompare!=0 && strchr(tmp,'M')) lpFilterItem->uCompare=0x001A;

					if (lpFilterItem->uCompare==0 && strchr(tmp,'C')) lpFilterItem->uCompare=0x0029;
					else
					if (lpFilterItem->uCompare!=0 && strchr(tmp,'C')) lpFilterItem->uCompare=0x002A;

					lpFilterItem->uCompare|=0x0010;
				}
				lpFilterItem->csFilter=postmp;
				if ((lpFilterItem->uCompare&0x0020)!=0) 
					lpFilterItem->csFilter.MakeUpper();
			}
		}
		if (pos2) *pos2='\'';
		pos=pos2;
	}

	delete[] tmpstr;
	return m_uNFilter;
}


SPRFILTERITEM * CFilterArray::CreateFilter(UINT nItem)
{
	SPRFILTERITEM * tmp=NULL;

	while((m_uNFilter>=m_uMaxFilter-1 && m_uMaxFilter<0x1000) || m_uMaxFilter==0)
	{
		SPRFILTERITEM ** tmp2=new SPRFILTERITEM * [m_uNFilter+10];
		UINT i;
		for(i=0; i<m_uMaxFilter;i++)
			tmp2[i]=m_Array[i];
		m_uMaxFilter=m_uNFilter+10;
		delete[] m_Array;
		for(; i<m_uMaxFilter;i++)
			tmp2[i]=NULL;
		m_Array=tmp2;
	}

	if (m_uNFilter<m_uMaxFilter)
	{
		tmp=m_Array[m_uNFilter++]=new SPRFILTERITEM;
		if (tmp) tmp->nField=nItem;
	}

	return tmp;
}

const CString CFilterArray::GetFilter(UINT iField)
{
	CString ret;
	UINT i;
	for(i=0; i<m_uNFilter;i++)
		if (m_Array[i]->nField==iField)
		{
			const char *pss="";
			if (ret!="")
				switch(m_Array[i]->uLogOperation)
				{
				case 1:/*OR*/	pss="'OR'";		break;
				case 2:/*AND*/	pss="'AND'";	break;	
				case 3:/*XOR*/	pss="'XOR'";	break;	
				default:
					pss="";	break;
				}
			ret+=pss;

			switch(m_Array[i]->uCompare)
			{
			case 0x0000:/*none*/	pss="none";	break;
			case 0x0008:/*none*/	pss="none";	break;	
			case 0x0001:/*>*/		pss=">";	break;	
			case 0x0002:/*<*/		pss="<";	break;
			case 0x0003:/*#*/		pss="#";	break;
			case 0x0004:/*=*/		pss="=";	break;
			case 0x0005:/*>=*/		pss=">=";	break;
			case 0x0006:/*<=*/		pss="<=";	break;
			case 0x0011:/*G*/		pss="G";	break;
			case 0x0012:/*L*/		pss="L";	break;
			case 0x0013:/*N*/		pss="N";	break;
			case 0x0014:/*E*/		pss="E";	break;
			case 0x0015:/*GE*/		pss="GE";	break;
			case 0x0016:/*LE*/		pss="LE";	break;
			case 0x0017:/*GLE*/		pss="GLE";	break;
			case 0x0018:/*I*/		pss="I";	break;
			case 0x0019:/*M*/		pss="M";	break;
			case 0x001A:/*NM*/		pss="NM";	break;
			case 0x0039:/*C*/		pss="C";	break;
			case 0x003A:/*NC*/		pss="NC";	break;
			default:
				pss="none";	break;
			}
			ret+=pss;
			ret+=",";
			ret+=m_Array[i]->csFilter;
		}

	return ret;
}

BOOL CFilterArray::IsItemInFilter(CString *Item, UINT nItem)
{
	BOOL ret=TRUE;
	BOOL flgFirst=TRUE;


	if (Item)
	{
		UINT i;
		for(i=0; i<m_uNFilter; i++)
			if (m_Array[i] && m_Array[i]->nField<nItem)
			{
				UINT retFlag=0;
				switch(m_Array[i]->uCompare)
				{
				case 0x0000:/*none*/	continue;
				case 0x0008:/*none*/	continue;
				case 0x0001:/*>*/	if (atof(Item[m_Array[i]->nField])<=atof(m_Array[i]->csFilter))	retFlag=0xFFFF;	break;
				case 0x0002:/*<*/	if (atof(Item[m_Array[i]->nField])>=atof(m_Array[i]->csFilter))	retFlag=0xFFFF;	break;
				case 0x0003:/*#*/	if (atof(Item[m_Array[i]->nField])==atof(m_Array[i]->csFilter))	retFlag=0xFFFF;	break;
				case 0x0004:/*=*/	if (atof(Item[m_Array[i]->nField])!=atof(m_Array[i]->csFilter))	retFlag=0xFFFF;	break;
				case 0x0005:/*>=*/	if (atof(Item[m_Array[i]->nField])< atof(m_Array[i]->csFilter))	retFlag=0xFFFF;	break;
				case 0x0006:/*<=*/	if (atof(Item[m_Array[i]->nField])> atof(m_Array[i]->csFilter))	retFlag=0xFFFF;	break;
				case 0x0011:/*G*/	if (Item[m_Array[i]->nField]<=m_Array[i]->csFilter)				retFlag=0xFFFF;	break;
				case 0x0012:/*L*/	if (Item[m_Array[i]->nField]>=m_Array[i]->csFilter)				retFlag=0xFFFF;	break;
				case 0x0013:/*N*/	if (Item[m_Array[i]->nField]==m_Array[i]->csFilter)				retFlag=0xFFFF;	break;
				case 0x0014:/*E*/	if (Item[m_Array[i]->nField]!=m_Array[i]->csFilter)				retFlag=0xFFFF;	break;
				case 0x0015:/*GE*/	if (Item[m_Array[i]->nField]< m_Array[i]->csFilter)				retFlag=0xFFFF;	break;
				case 0x0016:/*LE*/	if (Item[m_Array[i]->nField]> m_Array[i]->csFilter)				retFlag=0xFFFF;	break;
				case 0x0017:/*GLE*/	if ((Item[m_Array[i]->nField].Find(m_Array[i]->csFilter)>=0 && m_Array[i]->csFilter!="") || Item[m_Array[i]->nField]==m_Array[i]->csFilter)	retFlag=0xFFFF;	break;
				case 0x0018:/*I*/	if (Item[m_Array[i]->nField].Find(m_Array[i]->csFilter)< 0 && Item[m_Array[i]->nField]!=m_Array[i]->csFilter)	retFlag=0xFFFF;	break;
				case 0x0019:/*M*/
				case 0x001A:/*NM*/
					{
						UINT flgUNI=0;
						const char *pos1=Item[m_Array[i]->nField];
						while(*pos1!=0)
						{
							const char *pos2=m_Array[i]->csFilter;
							const char *reppos=pos1;
							if (*pos2=='[')
							{
								pos2++;
								while(*pos1!=0 && *pos1!=*pos2) {pos1++;reppos++;}
								if (*pos1==0) break;
							}

							while((*pos1==*pos2 || *pos2==GPC.DelimiterIn1) && *pos1!=0 && *pos2!=GPC.DelimiterIn2)
								{pos1++;pos2++;}

							if ((*pos2==0 && *pos1==0) || *pos2==GPC.DelimiterIn2) {flgUNI=1;break;}
							if (*pos1==0) break;
							if (m_Array[i]->csFilter.GetLength()==0 || m_Array[i]->csFilter[0]!='[') break;

							pos1=++reppos;
						}

						if (flgUNI==0 && m_Array[i]->uCompare==0x0019) retFlag=0xFFFF;
						if (flgUNI!=0 && m_Array[i]->uCompare==0x001A) retFlag=0xFFFF;
					}
					break;
				case 0x0039:/*C*/
				case 0x003A:/*NC*/
					{
						UINT flgUNI=0;
						CString tmps=Item[m_Array[i]->nField];
						tmps.MakeUpper();
						const char *pos1=tmps;
						const char *posFilter=m_Array[i]->csFilter;
						while(*pos1!=0)
						{
							const char *pos2=posFilter;
							const char *reppos=pos1;
							if (*pos2=='[')
							{
								pos2++;
								while(*pos1!=0 && *pos1!=*pos2) {pos1++;reppos++;}
								if (*pos1==0) break;
							}

							while((*pos1==*pos2 || *pos2==GPC.DelimiterIn1) && *pos1!=0 && *pos2!=GPC.DelimiterIn2)
								{pos1++;pos2++;}

							if ((*pos2==0 && *pos1==0) || *pos2==GPC.DelimiterIn2) {flgUNI=1;break;}
							if (*pos1==0) break;
							if (posFilter[0]!='[') break;

							pos1=++reppos;
						}

						if (flgUNI==0 && m_Array[i]->uCompare==0x0039) retFlag=0xFFFF;
						if (flgUNI!=0 && m_Array[i]->uCompare==0x003A) retFlag=0xFFFF;
					}
					break;
				}
				if (retFlag<0xFFFF)
				{// true
					switch(m_Array[i]->uLogOperation)
					{
					case 1: // OR
						ret=TRUE;
						break;
					case 2: // AND
						if (flgFirst) ret=TRUE;
						break;
					case 3: // XOR
						if (flgFirst) ret=TRUE;
						else
							ret= !ret;
						break;
					}
				}
				else
				{// false
					switch(m_Array[i]->uLogOperation)
					{
					case 1: // OR
						if (flgFirst) ret=FALSE;
						break;
					case 2: // AND
						ret=FALSE;
						break;
					case 3: // XOR
						if (flgFirst) ret=FALSE;
						break;
					}
				}
				flgFirst=FALSE;
			}
	}
	return ret;
}

