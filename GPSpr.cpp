// GPSpr.cpp: implementation of the CGPSpr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "GPSpr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


const UINT CGPSpr::uNMethods=47;
const char *CGPSpr::cArrMethods[]={
		"InsertEmpty",		"AddEmpty",			"InsertItem",		"InsertItems",		"AddItem",
		"AddItems",			"DeleteItem",		"SetItem",			"SetSubItem",		"SetFilter",
		"SetFilterItem",	"SetSortPrior",		"SetSortPriorItem",	"SortItems",		"PriorSortItems",
		"SortItemsDesc",	"PriorSortItemsDesc","SortItemsAsNum",	"PriorSortItemsAsNum","SortItemsDescAsNum",
		"PriorSortItemsDescAsNum","MoveFirst",	"FindNextItem",		"FindNextItemExact","FindItem",
		"FindItemExact",	"GetSprInfo",		"GetSpr",			"GetItem",			"GetFilter",
		"GetSort",			"SetFilterItemOR",	"SetFilterItemXOR",	"GetValues",		"GetValuesEx",
		"GetNextItem",		"GetCurPos",		"GetSumm",			"GetMinValue",		"GetMaxValue",
		"GetMidValue",		"GetMinMaxValue",	"GetCountValues",	"FindNextItemF",		"FindNextItemExactF",
		"FindItemF",		"FindItemExactF","","","",
		"","","", "", "", 
		"","",
	};
const char *CGPSpr::cArrMethodsParams[]={
		"iBefore,iCount","iCount","iBefore,TextF1]TextF2]...","iBefore,Text1F1]Text1F2]...^Text2F1]Text2F2]...","TextF1^TextF2^...",
		"Text1F1]Text1F2]...^Text2F1]Text2F2]...","nItem","nItem,Text1F1]Text1F2]...","nItem,nSubItem,TextF","Oper1,Text1F1'LOGOP'Text1F2'LOGOP'...",
		"nItem,Oper1,Text1F1'LOGOP'Text1F2'LOGOP'...","Text1F1^Text1F2^...","nItem,Text1F1^Text1F2^...","nField1,nField2,...","nField1,nField2,...",
		"nField1,nField2,...","nField1,nField2,...","nField1,nField2,...","nField1,nField2,...","nField1,nField2,...",
		"nField1,nField2,...","","FindInField,FindValue","FindInField,FindValue","FindInField,FindValue",
		"FindInField,FindValue","","bFull","ItemId","",
		"","nItem,Oper1,Text1F1'LOGOP'Text1F2'LOGOP'...","nItem,Oper1,Text1F1'LOGOP'Text1F2'LOGOP'...","nField","nField1^nField2^...",
		"",					"",					"nField1,nField2... ;DelimChar;format","nField1,nField2... ;DelimChar;format","nField1,nField2... ;DelimChar;format",
		"nField1,nField2... ;DelimChar;format","nField1,nField2... ;DelimChar;format","nField1,nField2... ;DelimChar;format","FindInField,FindValue","FindInField,FindValue",
		"FindInField,FindValue","FindInField,FindValue","","","",
		"","","", "", "", 
		"","",
	};


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGPSpr::CGPSpr()
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwCreateSpr++;
	SprName="";
	nSpr=0;
	nmaxSpr=0;
	nFields=1;
	CSprArr=NULL;
	RetCString="";
	SortPriorArray=NULL;
	uPosition=0;
}

CGPSpr::~CGPSpr()
{
	if (GPC.DlgStatistics) GPC.DlgStatistics->m_STAT_TERMINAL.dwDeleteSpr++;
	Destroy();
}

UINT CGPSpr::DoMethod(const char *iStr, char **oStr)
{
	char met[150];
	strncpy(met,iStr,145);
	met[145]=0;
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int nfunc=0;
	int retint=-123456; 
	int atoipos=atoi(pos);

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
	case 0: /*InsertEmpty*/	
		{
			int iBefore=0,iCount=1;
			m_LastScanf=sscanf(pos,"%d,%d",&iBefore,&iCount);
			retint=InsertEmpty(iBefore,iCount);
		}
		break;
	case 1: /*AddEmpty*/	retint=InsertEmpty(nSpr,atoipos);		break;
	case 2: /*InsertItem*/
		{
			int iBefore=atoipos;
			retint=InsertEmpty(iBefore,1);
			while(*pos!=0 && *pos!=',') pos++;
			if (*pos!=0) pos++;
			retint=SetItem(iBefore,pos);
		}
		break;
	case 3: /*InsertItems*/
		{
			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
			int iBefore=atoipos,iCount=1;
			char *pos1=pos333;
			while(*pos1!=0 && *pos1!=',') pos1++;
			if (*pos1!=0) pos1++;

			char *tmp=pos1;

			do if (*tmp==GPC.DelimiterIn1) iCount++;
			while(*tmp++!=0);
			retint=InsertEmpty(iBefore,iCount);
			tmp=pos1;
			while(tmp!=NULL && *tmp!=0)
			{
				char *tmp2=strchr(tmp,GPC.DelimiterIn1);
				if (tmp2!=NULL) *(tmp2++)=0;
				ReplaceChar(tmp,GPC.DelimiterIn2,GPC.DelimiterIn1);
				retint=SetItem(iBefore++,tmp);
				tmp=tmp2;
			}
			retint=nSpr;
			delete[] pos333;
		}
		break;
	case 4: /*AddItem*/
		retint=SetItem(InsertEmpty(nSpr,1)-1,pos);
		break;
	case 5: /*AddItems*/
		{
			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
			char *pos1=pos333;
			int iBefore=nSpr,iCount=1;
			char *tmp=pos1;
			do if (*tmp==GPC.DelimiterIn1) iCount++;
			while(*tmp++!=0);
			retint=InsertEmpty(iBefore,iCount);
			tmp=pos1;
			while(tmp!=NULL && *tmp!=0)
			{
				char *tmp2=strchr(tmp,GPC.DelimiterIn1);
				if (tmp2!=NULL) *(tmp2++)=0;
				ReplaceChar(tmp,GPC.DelimiterIn2,GPC.DelimiterIn1);
				retint=SetItem(iBefore++,tmp);
				tmp=tmp2;
			}
			retint=nSpr;
			delete[] pos333;
		}
		break;
	case 6: /*DeleteItem*/
		{
			const char *tmp=pos;
			int nDelta=0;
			if (atoipos<0)
			{
				if (CSprArr!=NULL)
				{
					UINT i;
					for(i=0;i<nSpr;i++)
						if (CSprArr[i]!=NULL)
						{
							delete[]  CSprArr[i];
							CSprArr[i]=NULL;
						}
				}
				nSpr=0;
				nmaxSpr=0;
			}
			else
				while(tmp!=NULL && *tmp!=0)
				{
					int nItem=atoi(tmp);
					DeleteItem(nItem-nDelta++);
					while(*tmp!=0 && *tmp!=',' && *tmp!=';' && *tmp!=GPC.DelimiterIn1) tmp++;
					if (*tmp!=0) tmp++;
				}
			retint=nSpr;
		}
		break;
	case 7: /*SetItem*/
		while(*pos!=0 && *pos!=',') pos++;
		if (*pos!=0) pos++;
		retint=SetItem(atoipos,pos);
		break;
	case 8: /*SetSubItem*/
		{
			int nItem=0,nSubItem=0;
			m_LastScanf=sscanf(pos,"%d,%d",&nItem,&nSubItem);
			while(*pos!=0 && *pos!=',') pos++;
			if (*pos!=0) pos++;
			while(*pos!=0 && *pos!=',') pos++;
			if (*pos!=0) pos++;
			retint=SetSubItem(nItem,nSubItem,pos);
		}
		break;
	case 9: /*SetFilter*/	
		SetFilter(pos);
		MoveFirst();
		break;
	case 10: /*SetFilterItem*/
	case 31: /*SetFilterItemOR*/
	case 32: /*SetFilterItemXOR*/
		while(*pos!=0 && *pos!=',') pos++;
		if (*pos!=0) pos++;
		m_FilterArray.SetFilter(atoipos,pos,nfunc==10?0:nfunc==31?1:2);
///		SetFilterItem(atoipos,pos);
		MoveFirst();
		break;
	case 11: /*SetSortPrior*/
		SetSortPrior(pos);
		MoveFirst();
		break;
	case 12: /*SetSortPriorItem*/
		while(*pos!=0 && *pos!=',') pos++;
		if (*pos!=0) pos++;
		SetSortPriorItem(atoipos,pos);
		MoveFirst();
		break;
	case 13: /*SortItems*/
	case 14: /*PriorSortItems*/
	case 15: /*SortItemsDesc*/
	case 16: /*PriorSortItemsDesc*/
	case 17: /*SortItemsAsNum*/
	case 18: /*PriorSortItemsAsNum*/
	case 19: /*SortItemsDescAsNum*/
	case 20: /*PriorSortItemsDescAsNum*/
		{
			UINT *Flds=new UINT [nFields+5];
			UINT i;
			for(i=0;i<nFields+5;i++) Flds[i]=0;
			const char *pos2=pos;
			i=0;
			while(*pos2!=0 && i<nFields)
			{
				Flds[i+1]=Flds[i]=atoi(pos2);
				while(*pos2!=0 && *pos2!=',' && *pos2!='.' && *pos2!=';' && *pos2!=GPC.DelimiterIn1) pos2++;
				if (*pos2!=0)  pos2++;
				i++;
			}

			switch(nfunc)
			{
			case 13: /*SortItems*/			SortSpr(CSprArr,Flds,0,nSpr-1,GPS_ASCENDING);				break;
			case 14: /*PriorSortItems*/		SortSpr(CSprArr,Flds,0,nSpr-1,GPS_ASCENDING|GPS_USEPRIOR);	break;
			case 15: /*SortItemsDesc*/		SortSpr(CSprArr,Flds,0,nSpr-1,GPS_DESCENDING);				break;
			case 16: /*PriorSortItemsDesc*/	SortSpr(CSprArr,Flds,0,nSpr-1,GPS_DESCENDING|GPS_USEPRIOR);	break;
			case 17: /*SortItemsAsNum*/				SortSprAsNum(CSprArr,Flds,0,nSpr-1,GPS_ASCENDING);				break;
			case 18: /*PriorSortItemsAsNum*/		SortSprAsNum(CSprArr,Flds,0,nSpr-1,GPS_ASCENDING|GPS_USEPRIOR);	break;
			case 19: /*SortItemsDescAsNum*/			SortSprAsNum(CSprArr,Flds,0,nSpr-1,GPS_DESCENDING);				break;
			case 20: /*PriorSortItemsDescAsNum*/	SortSprAsNum(CSprArr,Flds,0,nSpr-1,GPS_DESCENDING|GPS_USEPRIOR);break;
			}
			delete[] Flds;
			MoveFirst();
		}
		break;
	case 21: /*MoveFirst*/		MoveFirst(); break;
	case 22: /*FindNextItem*/   //"FindInField,FindValue",	 
	case 23: /*FindNextItemExact*/	
	case 24: /*FindItem*/	
	case 25: /*FindItemExact*/	
	case 43: /*FindNextItemF*/   //"FindInField,FindValue",	 
	case 44: /*FindNextItemExactF*/	
	case 45: /*FindItemF*/	
	case 46: /*FindItemExactF*/	
		{
			while(*pos!=0 && *pos!=',') pos++;
			if (*pos!=0) pos++;
			const CString * tmpitem=NULL;
			switch(nfunc)
			{
			case 22: /*FindNextItem*/		tmpitem=FindNextItem		(atoipos,pos);	break;
			case 23: /*FindNextItemExact*/	tmpitem=FindNextItemExact	(atoipos,pos);	break;
			case 24: /*FindItem*/			tmpitem=FindItem			(atoipos,pos);	break;
			case 25: /*FindItemExact*/		tmpitem=FindItemExact		(atoipos,pos);	break;
			case 43: /*FindNextItemF*/		tmpitem=FindNextItemF		(atoipos,pos);	break;
			case 44: /*FindNextItemExactF*/	tmpitem=FindNextItemExactF	(atoipos,pos);	break;
			case 45: /*FindItemF*/			tmpitem=FindItemF			(atoipos,pos);	break;
			case 46: /*FindItemExactF*/		tmpitem=FindItemExactF		(atoipos,pos);	break;
			}

			if (oStr!=NULL)
			{
				if (tmpitem==NULL) 
				{
					*oStr=new char [100];
					strcpy(*oStr,"-1");
				}
				else
				{
					UINT i;
					UINT len=0;
					for(i=0;i<nFields;i++)
						len+=tmpitem[i].GetLength();

					*oStr=new char [len+nFields+100];
					**oStr=0;
					char *posout=*oStr;
					posout+=sprintf(posout,"%d",uPosition-1);
					for(i=0;i<nFields;i++)
						posout+=sprintf(posout,"\x7F%s",(LPCSTR)tmpitem[i]);
				}
			}
		}
		break;
	case 26: /*GetSprInfo*/	
		if (oStr!=NULL)
		{
			VARIANT SprInfo;
			VariantInit(&SprInfo);
			GetSprInfo(&SprInfo,0);
			CString str;
			ArrayToStringEx(&SprInfo,str,"\x7Fq1w2e3r4\x7");
			*oStr=new char [str.GetLength()+100];
			strcpy(*oStr,str);
		}
		break;
	case 27: /*GetSpr*/	
		if (oStr!=NULL && nFields>0)
		{
			long maxlen=10000;
			long curlen=0;
			char *tmp=new char [maxlen+10];
			*tmp=0;
			UINT i;
			for(i=0;i<nSpr;i++)
			{
				if (atoipos!=0 || IsItemInFilter(i))
				{
					UINT j;
					for(j=0;j<nFields;j++)
					{
						long len=CSprArr[i][j].GetLength();
						while(len+curlen>=maxlen)
						{
							maxlen+=maxlen/4;
							char *tt=new char [maxlen+10];
							char *posd=tt;
							char *poss=tmp;
							while(((*posd++)=(*poss++))!=0);
							delete[] tmp;
							tmp=tt;
						}
						strcat(tmp+curlen,CSprArr[i][j]);
						curlen+=len;
						tmp[curlen++]=0x07;
						tmp[curlen]=0x0;
					}
					if (curlen>0) tmp[curlen-1]=0x7F;
					tmp[curlen]=0x0;
				}
			}
			if (curlen!=0) tmp[curlen-1]=0;
			*oStr=tmp;
		}
		break;
	case 28: /*GetItem*/	
		if (oStr!=NULL && (UINT)atoipos<nSpr && CSprArr[atoipos]!=NULL)
		{
			long curlen=0;
			UINT j;
			for(j=0;j<nFields;j++) curlen+=CSprArr[atoipos][j].GetLength();
			*oStr=new char [curlen+nFields+100];
			**oStr=0;

			for(j=0;j<nFields;j++)
			{
				if (j>0) strcat(*oStr,"\x7F");
				strcat(*oStr,CSprArr[atoipos][j]);
			}
		}
		break;
	case 29: /*GetFilter*/	
		if (oStr!=NULL)
		{
			CString strtmp;
			strtmp="";
			UINT k=0;
			for(k=0;k<nFields;k++)
				if (k==0)	strtmp=GetFilter(k);
				else		strtmp+="\x7F"+GetFilter(k);

			*oStr=new char [strtmp.GetLength()+100];
			strcpy(*oStr,strtmp);
		}
		break;

	case 30: /*GetSort*/
		if (oStr!=NULL)
		{
			CString strtmp;
			strtmp="";
			UINT k=0;

			strtmp="";
			for(k=0;k<nFields;k++)
				if (k==0)	strtmp=GetSort(k);
				else		strtmp+="\x7F"+GetSort(k);

			*oStr=new char [strtmp.GetLength()+100];
			strcpy(*oStr,strtmp);
		}
		break;
	case 33: /*GetValues nField*/
		if (oStr!=NULL && CSprArr && (UINT)atoipos<nFields)
		{
			CListMaker m_LM;
			m_LM.CreateList("__tmpSprList__");
			UINT m_CurPosTmp=0;

			while(m_CurPosTmp<nSpr)
			{
				if (IsItemInFilter(m_CurPosTmp))
				{
					if (CSprArr[m_CurPosTmp])
					m_LM.AppendList("__tmpSprList__",CSprArr[m_CurPosTmp][atoipos]);
				}
				m_CurPosTmp++;
			}
			m_LM.SortList("__tmpSprList__");
			m_LM.UniqueList("__tmpSprList__");
			m_LM.GetList("__tmpSprList__",oStr);
		}
		break;
	case 34: /*GetValuesEx nField*/
		if (oStr!=NULL && CSprArr && (UINT)atoipos<nFields)
		{
			UINT ncField=0;
			UINT i=0;
			UINT *auFieldsNum=new UINT [nFields+500];
			UINT *auFieldsLen=new UINT [nFields+500];
			char **auFieldsPos=new char * [nFields+500];
			char **acFieldsVal=new char * [nFields+500];
			const char *pos2=pos;

			do
			{
				auFieldsNum[ncField]=(atoi(pos2)%nFields);
				auFieldsLen[ncField]=9950;
				*(auFieldsPos[ncField]=acFieldsVal[ncField]=new char [10000])=0;
				ncField++;

				while(*pos2!=0 && *pos2!=GPC.DelimiterIn1 && *pos2!=',') pos2++;
				if (*pos2) pos2++;
			}
			while(*pos2!=0 && ncField<500);

			UINT m_CurPosTmp=0;
			while(m_CurPosTmp<nSpr)
			{
				if (IsItemInFilter(m_CurPosTmp) && CSprArr[m_CurPosTmp])
				{
					UINT curLen;
					for(i=0;i<ncField;i++)
					{
						if (auFieldsPos[i]!=acFieldsVal[i])
						{
							*(auFieldsPos[i]++)=GPC.DelimiterIn1;
							*auFieldsPos[i]=0;
						}
						curLen=CSprArr[m_CurPosTmp][auFieldsNum[i]].GetLength()+auFieldsPos[i]-acFieldsVal[i];
						if (curLen>auFieldsLen[i])
						{
							char *tmp=new char [curLen*2+2];
							strcpy(tmp,acFieldsVal[i]);
							auFieldsPos[i]=auFieldsPos[i]-acFieldsVal[i]+tmp;
							delete acFieldsVal[i];
							acFieldsVal[i]=tmp;
							auFieldsLen[i]=curLen*2;
						}
						strcpy(auFieldsPos[i],CSprArr[m_CurPosTmp][auFieldsNum[i]]);
						auFieldsPos[i]=acFieldsVal[i]+curLen;
					}
				}
				m_CurPosTmp++;
			}

			UINT lenAll=0;
			for(i=0;i<ncField;i++)
				lenAll+=auFieldsPos[i]-acFieldsVal[i]+1;

			*oStr=new char [lenAll+ncField];
			char *tmppos=*oStr;

			for(i=0;i<ncField;i++)
			{
				CListMaker m_LM;
				char *tmpOstr=NULL;
				m_LM.CreateList("__tmpSprList__");
				m_LM.SetList("__tmpSprList__",acFieldsVal[i],GPC.DelimiterIn1);
				m_LM.SortList("__tmpSprList__");
				m_LM.UniqueList("__tmpSprList__");
				m_LM.GetList("__tmpSprList__",&tmpOstr);
				if (tmpOstr)
				{
					char *tmppos7=tmpOstr;
					while(*tmppos7)
					{
						if (*tmppos7==127) *tmppos7=7;
						tmppos7++;
					}

					strcpy(tmppos,tmpOstr);
					tmppos+=(int)strlen(tmpOstr);
					if (i<ncField-1)
					{
						*(tmppos++)=127;
						*tmppos=0;
					}
					delete[] tmpOstr;
				}
			}



			for(i=0;i<ncField;i++)
			{
				if (acFieldsVal[i]) delete acFieldsVal[i];
				acFieldsVal[i]=NULL;
			}

			delete[] auFieldsNum;
			delete[] auFieldsLen;
			delete[] auFieldsPos;
			delete[] acFieldsVal;

		}
		break;
	case 35: /*GetNextItem*/
		if (oStr!=NULL)
		{
			for(;uPosition<nSpr;uPosition++)
				if (CSprArr[uPosition]!=NULL && IsItemInFilter(uPosition))
				{
					char tmps[100];
					sprintf(tmps,"GetItem %d",uPosition);
					DoMethod(tmps,oStr);
					uPosition++;
					break;
				}

			if (*oStr==NULL)
			{
				*oStr=new char [100];
				**oStr=0;
			}
		}
		break;
	case 36: /*GetCurPos*/
		retint=uPosition>nSpr?-1:uPosition;
		break;
	case 37: /*GetSumm*/
	case 38: /*GetMinValue*/
	case 39: /*GetMaxValue*/
	case 40: /*GetMidValue*/
	case 41: /*GetMinMaxValue*/
	case 42: /*GetCountValues*/
		if (oStr!=NULL)
		{
			char *pos333=new char [(int)strlen(pos)+2];
			strcpy(pos333,pos);
			double **adSumm;
			double **adSumm2;
			long **alCount;
			UINT *alNValues;
			UINT *alNFields;
			UINT nSumm=0;
			char *pos2=pos333;
			char delimChar;
			char *outFormat="%g";
			if (*pos333 && *pos333!=';') nSumm=1;

			while(*pos2 && *pos2!=';')
				if (*(pos2++)==',') nSumm++;
			if (nSumm==0) nSumm=nFields;

			alCount=new long * [nSumm];
			adSumm=new double * [nSumm];
			adSumm2=new double * [nSumm];
			alNFields=new UINT [nSumm];
			alNValues=new UINT [nSumm];

			pos2=strchr(pos333,';');
			if (pos2++==NULL) pos2=" ";
			delimChar=*pos2;

			pos2=strchr(pos2,';');
			if (pos2++ && *pos2 && strchr(pos2,'%')) outFormat=pos2;

			pos2=pos333;
			UINT i;
			for(i=0;i<nSumm;i++)
			{
				if (nSumm!=nFields)
				{
					alNFields[i]=atoi(pos2);
					while(*pos2 && *(pos2++)!=',');
				}
				else alNFields[i]=i;
				if (alNFields[i]>nFields) alNFields[i]=0;
				adSumm[i]=new double[1];
				switch(nfunc)
				{
				case 37: /*GetSumm*/
				case 40: /*GetMidValue*/
				case 42: /*GetCountValues*/
					*adSumm[i]=0.;
					break;
				case 38: /*GetMinValue*/
					*adSumm[i]=9.9999e300;
					break;
				case 39: /*GetMaxValue*/
					*adSumm[i]=-9.9999e300;
					break;
				case 41: /*GetMinMaxValue*/
					adSumm2[i]=new double[1];
					*adSumm[i]=9.9999e300;
					*adSumm2[i]=-9.9999e300;
					break;
				}

				alCount[i]=new long[1];
				*alCount[i]=0;
				alNValues[i]=1;
			}

			uPosition=0;
			char *tmps=new char[200];
			char *stoptmps=tmps+90;

			for(;uPosition<nSpr;uPosition++)
				if (CSprArr[uPosition]!=NULL && IsItemInFilter(uPosition))
				{
					for(i=0;i<nSumm;i++)
					{
						const char *ps=CSprArr[uPosition][alNFields[i]];
						const char *ps2=ps;
						UINT curSubField=0;
						while(*ps2)
						{
							{
								char *pd=tmps;
								while((*pd=*ps2) && *(ps2++)!=delimChar && pd!=stoptmps)
								{
									if (*pd==',') *pd='.';
									pd++;
								}
								*pd=0;
							}

							if (curSubField>=alNValues[i])
								switch(nfunc)
								{
									case 41: /*GetMinMaxValue*/
										{
											double *tmpd=new double [curSubField+1];
											UINT j;
											for(j=0;j<alNValues[i];j++)
												tmpd[j]=adSumm2[i][j];
											delete adSumm2[i];
											adSumm2[i]=tmpd;
											for(;j<alNValues[i];j++)
												adSumm2[i][j]=9.9999e300;
										}
									case 37: /*GetSumm*/
									case 40: /*GetMidValue*/
									case 42: /*GetCountValues*/
									case 38: /*GetMinValue*/
									case 39: /*GetMaxValue*/
										{
											double *tmpd=new double [curSubField+1];
											long *tmpl=new long [curSubField+1];
											UINT j;
											for(j=0;j<alNValues[i];j++)
											{
												tmpl[j]=alCount[i][j];
												tmpd[j]=adSumm[i][j];
											}
											delete alCount[i];
											delete adSumm[i];
											adSumm[i]=tmpd;
											alCount[i]=tmpl;
											alNValues[i]=curSubField+1;
											for(;j<alNValues[i];j++)
												switch(nfunc)
												{
												case 37: /*GetSumm*/
												case 40: /*GetMidValue*/
												case 42: /*GetCountValues*/
													{
														adSumm[i][j]=0.;
														alCount[i][j]=0;
													}
													break;
												case 38: /*GetMinValue*/
													{
														adSumm[i][j]=9.9999e300;
														alCount[i][j]=0;
													}
													break;
												case 39: /*GetMaxValue*/
												case 41: /*GetMinMaxValue*/
													{
														adSumm[i][j]=-9.9999e300;
														alCount[i][j]=0;
													}
													break;
												}
										}
										break;
								}

							switch(nfunc)
							{
							case 42: /*GetCountValues*/
								break;
							case 37: /*GetSumm*/
							case 40: /*GetMidValue*/
								adSumm[i][curSubField]+=atof(tmps);
								break;
							case 38: /*GetMinValue*/
								{
									double cmp=atof(tmps);
									if (adSumm[i][curSubField]>cmp) adSumm[i][curSubField]=cmp;
								}
								break;
							case 39: /*GetMaxValue*/
								{
									double cmp=atof(tmps);
									if (adSumm[i][curSubField]<cmp) adSumm[i][curSubField]=cmp;
								}
								break;
							case 41: /*GetMinMaxValue*/
								{
									double cmp=atof(tmps);
									if (adSumm[i][curSubField]<cmp) adSumm[i][curSubField]=cmp;
									if (adSumm2[i][curSubField]>cmp) adSumm2[i][curSubField]=cmp;
								}
								break;
							}
							alCount[i][curSubField++]++;
							ps=ps2;
						}
					}
				}

			UINT nAll=0;
			for(i=0;i<nSumm;i++) nAll+=alNValues[i];
			*oStr=new char [nAll*30];
			**oStr=0;
			pos2=*oStr;

			switch(nfunc)
			{
			case 37: /*GetSumm*/
			case 38: /*GetMinValue*/
			case 39: /*GetMaxValue*/
				for(i=0;i<nSumm;i++)
				{
					if (i) {*(pos2++)=127;*pos2=0;}

					UINT j;
					for(j=0;j<alNValues[i];j++)
					{
						if (j) {*(pos2++)=1;*pos2=0;}
						pos2+=sprintf(pos2,outFormat,adSumm[i][j]);
					}
				}
				break;
			case 40: /*GetMidValue*/
				for(i=0;i<nSumm;i++)
				{
					if (i) {*(pos2++)=127;*pos2=0;}

					UINT j;
					for(j=0;j<alNValues[i];j++)
					{
						if (j) {*(pos2++)=1;*pos2=0;}
						pos2+=sprintf(pos2,outFormat,alCount[i][j]!=0?adSumm[i][j]/alCount[i][j]:0.0);
					}
				}
				break;
			case 41: /*GetMinMaxValue*/
				for(i=0;i<nSumm;i++)
				{
					if (i) {*(pos2++)=1;*pos2=0;}

					UINT j;
					for(j=0;j<alNValues[i];j++)
					{
						if (j) {*(pos2++)=2;*pos2=0;}
						pos2+=sprintf(pos2,outFormat,adSumm2[i][j]);
					}
				}

				*(pos2++)=127;
				*pos2=0;

				for(i=0;i<nSumm;i++)
				{
					if (i) {*(pos2++)=1;*pos2=0;}

					UINT j;
					for(j=0;j<alNValues[i];j++)
					{
						if (j) {*(pos2++)=2;*pos2=0;}
						pos2+=sprintf(pos2,outFormat,adSumm[i][j]);
					}
				}
				break;
			case 42: /*GetCountValues*/
				for(i=0;i<nSumm;i++)
				{
					if (i) {*(pos2++)=127;*pos2=0;}

					UINT j;
					for(j=0;j<alNValues[i];j++)
					{
						if (j) {*(pos2++)=1;*pos2=0;}
						pos2+=sprintf(pos2,outFormat,alCount[i][j]);
					}
				}
				break;
			}


			for(i=0;i<nSumm;i++)
			{
				delete adSumm[i];
				adSumm[i]=NULL;
				delete alCount[i];
				alCount[i]=NULL;
			}

			if (nfunc==41)
				for(i=0;i<nSumm;i++)
				{
					delete adSumm2[i];
					adSumm2[i]=NULL;
				}

			uPosition=0;
			delete[] tmps;
			delete[] adSumm;
			delete[] adSumm2;
			delete[] alCount;
			delete[] alNFields;
			delete[] alNValues;
			delete[] pos333;
		}
		break;

	default:
		GPC.m_ErrReport.GPWriteWarnLog2("GPSpr", "Unknown Method",iStr);
		if (oStr!=NULL)
		{
			*oStr=new char [1000];
			sprintf(*oStr,ErrObjSub,met); nfunc=0xFFFFFFFFL; 
		}
		break;
	}
	if (oStr!=NULL && *oStr==0 && retint!=-123456)
	{
		*oStr=new char [1000];
		sprintf(*oStr,"%d",retint);
	}
	return nfunc;
}

BOOL CGPSpr::Create(const char *iName, UINT inField)
{
	Destroy();
	if (inField>1000 || inField==0) inField=1;
	nFields=inField;
	SprName=iName;
	SortPriorArray=new CString [inField];

	return TRUE;
}

UINT CGPSpr::GetNItem()	{	return nSpr; }
UINT CGPSpr::GetNField()	{	return nFields; }
const char * CGPSpr::GetName(){	return SprName;}

void CGPSpr::Destroy()
{
	if (SortPriorArray!=NULL) delete[]  SortPriorArray;
	SortPriorArray=NULL;

	if (CSprArr!=NULL)
	{
		UINT i;
		for(i=0;i<nSpr;i++)
			if (CSprArr[i]!=NULL)
			{
				delete[]  CSprArr[i];
				CSprArr[i]=NULL;
			}
		delete[] CSprArr;
		CSprArr=NULL;
	}
	nSpr=0;
	nmaxSpr=0;
}

UINT CGPSpr::InsertEmpty(UINT inBefore, UINT iCount)
{
	UINT newCount=nSpr;
	UINT i;
	if (inBefore>0x1000000) inBefore=nSpr;

	if (inBefore+iCount>=nmaxSpr || nSpr+iCount>=nmaxSpr) newCount=nmaxSpr+iCount+50;

	if (newCount>nmaxSpr)
	{

		CString **tmpIS=new CString * [newCount];
		i=0;

		if (CSprArr!=NULL) 
			for(i=0; i<nmaxSpr;i++)
				tmpIS[i]=CSprArr[i];

		nmaxSpr=newCount;

		for(;i<nmaxSpr;i++)
			tmpIS[i]=NULL;

		if (CSprArr!=NULL) delete[] CSprArr;
		CSprArr=tmpIS;
	}

	if (inBefore<nSpr)
		for(i=nSpr-1;i>=inBefore && i<nSpr;i--)
			CSprArr[i+iCount]=CSprArr[i];

	for(i=inBefore;i<inBefore+iCount;i++)
		CSprArr[i]=new CString [nFields];


	if (nSpr<inBefore) nSpr=inBefore;
	nSpr+=iCount;

	return nSpr;
}

UINT CGPSpr::SetItem(UINT nItem, const char *iStr)
{
	UINT ret=0xFFFFFFFF;
	if (nItem<nSpr && CSprArr!=NULL)
	{
		if (CSprArr[nItem]==NULL)	CSprArr[nItem]=new CString [nFields];

		char *tmp=new char [(int)strlen(iStr)+10];
		char *pos=strcpy(tmp,iStr);
		UINT nFl=0;
		do
		{
			char *pos2=pos;
			pos=strchr(pos,GPC.DelimiterIn1);
			if (pos!=NULL) *(pos++)=0;
			CSprArr[nItem][nFl]=pos2;
		}
		while(pos!=NULL && ++nFl<nFields);

		delete[] tmp;
		ret=nItem;
	}
	return ret;
}

UINT CGPSpr::SetSubItem(UINT nItem, UINT nSubItem, const char *iStr)
{
	UINT ret=0xFFFFFFFF;
	if (nItem<nSpr && CSprArr!=NULL && nSubItem<nFields)
	{
		if (CSprArr[nItem]==NULL) CSprArr[nItem]=new CString [nFields];

		CSprArr[nItem][nSubItem]=iStr;
		ret=nItem;
	}
	return ret;
}

UINT CGPSpr::DeleteItem(UINT nItem)
{
	if (nItem<nSpr && CSprArr!=NULL)
	{
		if (CSprArr[nItem]!=NULL) delete[]  CSprArr[nItem];
		UINT i;
		for(i=nItem+1;i<nSpr;i++)
			CSprArr[i-1]=CSprArr[i];
		nSpr--;
		CSprArr[nSpr]=NULL;
	}
	return nSpr;
}

CString * CGPSpr::GetSubItem(UINT nItem,UINT nSubItem)
{
	CString * ret=&RetCString;
	if (nItem<nSpr && CSprArr!=NULL && CSprArr[nItem]!=NULL && nSubItem<nFields && CSprArr[nItem][nSubItem]!="")
		ret=CSprArr[nItem]+nSubItem;
	return ret;
}

CString * CGPSpr::GetItem(UINT nItem)
{
	CString * ret=&RetCString;
	if (nItem<nSpr && CSprArr!=NULL && CSprArr[nItem]!=NULL)
		ret=CSprArr[nItem];
	return ret;
}

void CGPSpr::SetFilter(const char *iStr)
{
	m_FilterArray.DeleteAll();
	if (iStr!=NULL)
	{
			char *tmp=new char [(int)strlen(iStr)+10];
			strcpy(tmp,iStr);
			char *pos=tmp;
			UINT i;
			for(i=0;*pos!=0 && i<nFields;i++)
			{
				char *tmppos=strchr(pos,GPC.DelimiterIn1);
				if (tmppos!=NULL) *(tmppos++)=0;
				else tmppos="";
				m_FilterArray.SetFilter(i,pos);
				pos=tmppos;
			}
			delete[] tmp;
	}
}

void CGPSpr::SetFilterItem(UINT nItem, const char *iStr)
{
	m_FilterArray.SetFilter(nItem,iStr);
}

void CGPSpr::SetSortPrior(const char *iStr)
{
	if (iStr!=NULL && nFields>0)
	{
		if (SortPriorArray!=NULL) delete[]  SortPriorArray;
		SortPriorArray=NULL;
		if (nFields>0) SortPriorArray=new CString [nFields];
		if (SortPriorArray!=NULL)
		{
			char *tmp=new char [(int)strlen(iStr)+10];
			strcpy(tmp,iStr);
			char *pos=tmp;
			UINT i;
			for(i=0;*pos!=0 && i<nFields;i++)
			{
				char *tmppos=strchr(pos,GPC.DelimiterIn1);
				if (tmppos!=NULL) *(tmppos++)=0;
				else tmppos="";
				SetSortPriorItem(i,pos);
				pos=tmppos;
			}
			delete[] tmp;
		}
	}
}

void CGPSpr::SetSortPriorItem(UINT nItem, const char *iStr)
{
	if (SortPriorArray==NULL && nFields>0)
		SortPriorArray=new CString [nFields];
	if (SortPriorArray!=NULL && nItem<nFields)
		SortPriorArray[nItem]=iStr;
}



void CGPSpr::SortSpr(CString **Item, UINT *Flds, int left, int right, UINT Options)
{
	if (Flds==NULL || right<=0) return;
	register int i,j;
	CString * x,*y;

	i=left;
	j=right;
	x=Item[(left+right)/2];
	BOOL asc=(Options&GPS_SORTORDERMASK)==GPS_ASCENDING;

	if ((Options&GPS_USEPRIORMASK)!=0)
	{
		if (SortPriorArray==NULL) SortSpr(Item,Flds,left, right,Options^GPS_USEPRIOR);
		else
		{
			do
			{
				BOOL brk=TRUE;
				BOOL fltr1,fltr2;
				UINT nf=0;
				for(fltr2=TRUE,nf=0;nf<nFields && fltr2;nf++)
					if (SortPriorArray[nf]!="" && x[nf].Find(SortPriorArray[nf])<0) fltr2=0;

				if (asc)
					while(Item[i]!=NULL && i<right && brk)
					{
						for(nf=0;Flds[nf]<nFields && (nf==0 || Flds[nf]!=Flds[nf-1]) && brk;nf++)
							if (Item[i][Flds[nf]]>x[Flds[nf]]) brk=FALSE;
							else
							if (Item[i][Flds[nf]]<x[Flds[nf]]) break;

						for(fltr1=TRUE,nf=0;nf<nFields && fltr1;nf++)
							if (SortPriorArray[Flds[nf]]!="" && Item[i][Flds[nf]].Find(SortPriorArray[Flds[nf]])<0) fltr1=FALSE;

						if (fltr2 && !fltr1) brk=FALSE;
						else 
							if (!fltr2 && fltr1) brk=TRUE;
						if (brk) i++;
					}
				else
					while(Item[i]!=NULL && i<right && brk)
					{
						for(nf=0;Flds[nf]<nFields && (nf==0 || Flds[nf]!=Flds[nf-1]) && brk;nf++)
							if (Item[i][Flds[nf]]<x[Flds[nf]]) brk=FALSE;
							else
							if (Item[i][Flds[nf]]>x[Flds[nf]]) break;

						for(fltr1=TRUE,nf=0;nf<nFields && fltr1;nf++)
							if (SortPriorArray[nf]!="" && Item[i][nf].Find(SortPriorArray[nf])<0) fltr1=FALSE;
						if (!fltr2 && fltr1) brk=FALSE;
						else 
							if (fltr2 && !fltr1) brk=TRUE;
						if (brk) i++;
					}

				brk=TRUE;
				if (asc)
					while(Item[j]!=NULL && j>left && brk)
					{
						for(nf=0;Flds[nf]<nFields && (nf==0 || Flds[nf]!=Flds[nf-1]) && brk;nf++)
							if (Item[j][Flds[nf]]<x[Flds[nf]]) brk=FALSE;
							else
							if (Item[j][Flds[nf]]>x[Flds[nf]]) break;

						for(fltr1=TRUE,nf=0;nf<nFields && fltr1;nf++)
							if (SortPriorArray[nf]!="" && Item[j][nf].Find(SortPriorArray[nf])<0) fltr1=FALSE;
						if (!fltr2 && fltr1) brk=FALSE;
						else 
							if (fltr2 && !fltr1) brk=TRUE;
						if (brk) j--; 
					}
				else
					while(Item[j]!=NULL && j>left && brk)
					{
						for(nf=0;Flds[nf]<nFields && (nf==0 || Flds[nf]!=Flds[nf-1]) && brk;nf++)
							if (Item[j][Flds[nf]]>x[Flds[nf]]) brk=FALSE;
							else
							if (Item[j][Flds[nf]]<x[Flds[nf]]) break;

						for(fltr1=TRUE,nf=0;nf<nFields && fltr1;nf++)
							if (SortPriorArray[nf]!="" && Item[j][nf].Find(SortPriorArray[nf])<0) fltr1=FALSE;
						if (fltr2 && !fltr1) brk=FALSE;
						else 
							if (!fltr2 && fltr1) brk=TRUE;
						if (brk) j--; 
					}

				if (i<=j)
				{
					y=Item[i];			Item[i]=Item[j];			Item[j]=y;
					i++;				j--;
				}
			}while(i<=j);

			if(left<j) SortSpr(Item,Flds,left,j,Options);
			if (i<right) SortSpr(Item,Flds,i,right,Options);
		}
	}
	else
	{
		do
		{
			BOOL brk=TRUE;
			int nf=0;
			if (asc)
				while(Item[i]!=NULL && i<right && brk && Item[i][Flds[0]]<=x[Flds[0]])
				{
					if (Item[i][Flds[0]]==x[Flds[0]])
					{
						brk=TRUE;
						for(nf=1;Flds[nf]<nFields && brk && (brk=(Flds[nf]!=Flds[nf-1]));nf++)
						{
							if (Item[i][Flds[nf]]>x[Flds[nf]]) brk=FALSE;
							else 
							if (Item[i][Flds[nf]]<x[Flds[nf]]) break;
						}
						if (brk) i++;
					}
					else i++;
				}
			else
				while(Item[i]!=NULL && i<right && brk && Item[i][Flds[0]]>=x[Flds[0]])
				{
					if (Item[i][Flds[0]]==x[Flds[0]])
					{
						brk=TRUE;
						for(nf=1;Flds[nf]<nFields && brk && (brk=(Flds[nf]!=Flds[nf-1]));nf++)
						{
							if (Item[i][Flds[nf]]<x[Flds[nf]]) brk=FALSE;
							else 
							if (Item[i][Flds[nf]]>x[Flds[nf]]) break;
						}
						if (brk) i++;
					}
					else i++;
				}

			brk=TRUE;
			if (asc)
				while(Item[j]!=NULL && j>left && brk && Item[j][Flds[0]]>=x[Flds[0]])
				{
					if (Item[j][Flds[0]]==x[Flds[0]])
					{
						for(nf=1;Flds[nf]<nFields && brk && (brk=(Flds[nf]!=Flds[nf-1]));nf++)
						{
							if (Item[j][Flds[nf]]<x[Flds[nf]]) brk=FALSE;
							else 
							if (Item[j][Flds[nf]]>x[Flds[nf]]) break;
						}
						if (brk) j--; 
					}
					else j--; 
				}
			else
				while(Item[j]!=NULL && j>left && brk && Item[j][Flds[0]]<=x[Flds[0]])
				{
					if (Item[j][Flds[0]]==x[Flds[0]])
					{
						for(nf=1;Flds[nf]<nFields && brk && (brk=(Flds[nf]!=Flds[nf-1]));nf++)
						{
							if (Item[j][Flds[nf]]>x[Flds[nf]]) brk=FALSE;
							else 
							if (Item[j][Flds[nf]]<x[Flds[nf]]) break;
						}
						if (brk) j--; 
					}
					else j--; 
				}

			if (i<=j)
			{
				y=Item[i];			Item[i]=Item[j];			Item[j]=y;
				i++;				j--;
			}
		}while(i<=j);

		if(left<j) SortSpr(Item,Flds,left,j,Options);
		if (i<right) SortSpr(Item,Flds,i,right,Options);
	}
}


void CGPSpr::SortSprAsNum(CString **Item, UINT *Flds, int left, int right, UINT Options)
{
	if (Flds==NULL) return;
	register int i,j;
	CString * x,*y;

	i=left;
	j=right;
	x=Item[(left+right)/2];
	BOOL asc=(Options&GPS_SORTORDERMASK)==GPS_ASCENDING;

	if ((Options&GPS_USEPRIORMASK)!=0)
	{
		if (SortPriorArray==NULL) SortSpr(Item,Flds,left, right,Options^GPS_USEPRIOR);
		else
		{
			do
			{
				BOOL brk=TRUE;
				BOOL fltr1,fltr2;
				UINT nf=0;
				for(fltr2=TRUE,nf=0;nf<nFields && fltr2;nf++)
					if (SortPriorArray[nf]!="" && atof(x[nf])<atof(SortPriorArray[nf])) fltr2=0;

				if (asc)
					while(Item[i]!=NULL && i<right && brk)
					{
						for(nf=0;Flds[nf]<nFields && (nf==0 || Flds[nf]!=Flds[nf-1]) && brk;nf++)
							{if (atof(Item[i][Flds[nf]])>=atof(x[Flds[nf]])) brk=FALSE;}
						for(fltr1=TRUE,nf=0;nf<nFields && fltr1;nf++)
							if (SortPriorArray[nf]!="" && atof(Item[i][nf])<atof(SortPriorArray[nf])) fltr1=FALSE;
						if (fltr2 && !fltr1) brk=FALSE;
						else 
							if (!fltr2 && fltr1) brk=TRUE;
						if (brk) i++;
					}
				else
					while(Item[i]!=NULL && i<right && brk)
					{
						for(nf=0;Flds[nf]<nFields && (nf==0 || Flds[nf]!=Flds[nf-1]) && brk;nf++)
							{if (atof(Item[i][Flds[nf]])<=atof(x[Flds[nf]])) brk=FALSE;}
						for(fltr1=TRUE,nf=0;nf<nFields && fltr1;nf++)
							if (SortPriorArray[nf]!="" && atof(Item[i][nf])<atof(SortPriorArray[nf])) fltr1=FALSE;
						if (!fltr2 && fltr1) brk=FALSE;
						else 
							if (fltr2 && !fltr1) brk=TRUE;
						if (brk) i++;
					}

				brk=TRUE;
				if (asc)
					while(Item[j]!=NULL && j>left && brk)
					{
						for(nf=0;Flds[nf]<nFields && (nf==0 || Flds[nf]!=Flds[nf-1]) && brk;nf++)
							{if (atof(Item[j][Flds[nf]])<=atof(x[Flds[nf]])) brk=FALSE;}
						for(fltr1=TRUE,nf=0;nf<nFields && fltr1;nf++)
							if (SortPriorArray[nf]!="" && atof(Item[j][nf])<atof(SortPriorArray[nf])) fltr1=FALSE;
						if (!fltr2 && fltr1) brk=FALSE;
						else 
							if (fltr2 && !fltr1) brk=TRUE;
						if (brk) j--; 
					}
				else
					while(Item[j]!=NULL && j>left && brk)
					{
						for(nf=0;Flds[nf]<nFields && (nf==0 || Flds[nf]!=Flds[nf-1]) && brk;nf++)
							{if (atof(Item[j][Flds[nf]])>=atof(x[Flds[nf]])) brk=FALSE;}
						for(fltr1=TRUE,nf=0;nf<nFields && fltr1;nf++)
							if (SortPriorArray[nf]!="" && atof(Item[j][nf])<atof(SortPriorArray[nf])) fltr1=FALSE;
						if (fltr2 && !fltr1) brk=FALSE;
						else 
							if (!fltr2 && fltr1) brk=TRUE;
						if (brk) j--; 
					}

				if (i<=j)
				{
					y=Item[i];			Item[i]=Item[j];			Item[j]=y;
					i++;				j--;
				}
			}while(i<=j);

			if(left<j) SortSprAsNum(Item,Flds,left,j,Options);
			if (i<right) SortSprAsNum(Item,Flds,i,right,Options);
		}
	}
	else
	{
		do
		{
			BOOL brk=TRUE;
			int nf=0;
			if (asc)
				while(Item[i]!=NULL && i<right && brk)
				{
					for(nf=0;Flds[nf]<nFields && (nf==0 || Flds[nf]!=Flds[nf-1]) && brk;nf++)
						{if (atof(Item[i][Flds[nf]])>=atof(x[Flds[nf]])) brk=FALSE;}
					if (brk) i++;
				}
			else
				while(Item[i]!=NULL && i<right && brk)
				{
					for(nf=0;Flds[nf]<nFields && (nf==0 || Flds[nf]!=Flds[nf-1]) && brk;nf++)
						{if (atof(Item[i][Flds[nf]])<=atof(x[Flds[nf]])) brk=FALSE;}
					if (brk) i++;
				}

			brk=TRUE;
			if (asc)
				while(Item[j]!=NULL && j>left && brk)
				{
					for(nf=0;Flds[nf]<nFields && (nf==0 || Flds[nf]!=Flds[nf-1]) && brk;nf++)
						{if (atof(Item[j][Flds[nf]])<=atof(x[Flds[nf]])) brk=FALSE;}
					if (brk) j--; 
				}
			else
				while(Item[j]!=NULL && j>left && brk)
				{
					for(nf=0;Flds[nf]<nFields && (nf==0 || Flds[nf]!=Flds[nf-1]) && brk;nf++)
						{if (atof(Item[j][Flds[nf]])>=atof(x[Flds[nf]])) brk=FALSE;}
					if (brk) j--; 
				}

			if (i<=j)
			{
				y=Item[i];			Item[i]=Item[j];			Item[j]=y;
				i++;				j--;
			}
		}while(i<=j);

		if(left<j) SortSprAsNum(Item,Flds,left,j,Options);
		if (i<right) SortSprAsNum(Item,Flds,i,right,Options);
	}
}

void CGPSpr::MoveFirst()
{
	uPosition=0;
}

CString * CGPSpr::GetNextItem()
{
	CString * ret=NULL;

	while(uPosition<nSpr && !IsItemInFilter(uPosition))
		uPosition++;

	if (uPosition<nSpr) 
		ret=GetItem(uPosition++);

	return ret;
}

BOOL CGPSpr::IsItemInFilter(UINT nItem)
{
	BOOL ret=TRUE;
	if (CSprArr!=NULL && CSprArr[nItem]!=NULL)
		ret= m_FilterArray.IsItemInFilter(CSprArr[nItem],nFields);
	return ret;
}

CString * CGPSpr::FindItemExact(UINT inField, const char *iValue)
{	return FindItemExact(inField, CString(iValue));}

CString * CGPSpr::FindItem(UINT inField, const char *iValue)
{	return FindItem(inField, CString(iValue));}

CString * CGPSpr::FindItemExact(UINT inField, const CString &iValue)
{
	CString * ret=NULL;
	if (inField<nFields && CSprArr!=NULL)
	{
		UINT i;
		for(i=0;i<nSpr;i++)
			if (CSprArr[i]!=NULL && CSprArr[i][inField]==iValue) 
			{
				uPosition=i+1;
				ret=CSprArr[i];
				break;
			}
	}
	return ret;
}

CString * CGPSpr::FindItem(UINT inField, const CString &iValue)
{
	CString * ret=NULL;
	if (inField<nFields && CSprArr!=NULL)
	{
		UINT i;
		for(i=0;i<nSpr;i++)
			if (CSprArr[i]!=NULL && CSprArr[i][inField].Find(iValue)>=0) 
			{
				uPosition=i+1;
				ret=CSprArr[i];
				break;
			}
	}
	return ret;
}



CString * CGPSpr::FindItemExactF(UINT inField, const char *iValue)
{	return FindItemExactF(inField, CString(iValue));}

CString * CGPSpr::FindItemF(UINT inField, const char *iValue)
{	return FindItemF(inField, CString(iValue));}

CString * CGPSpr::FindItemExactF(UINT inField, const CString &iValue)
{
	CString * ret=NULL;
	if (inField<nFields && CSprArr!=NULL)
	{
		UINT i;
		for(i=0;i<nSpr;i++)
			if (CSprArr[i]!=NULL && CSprArr[i][inField]==iValue && IsItemInFilter(i)) 
			{
				uPosition=i+1;
				ret=CSprArr[i];
				break;
			}
	}
	return ret;
}

CString * CGPSpr::FindItemF(UINT inField, const CString &iValue)
{
	CString * ret=NULL;
	if (inField<nFields && CSprArr!=NULL)
	{
		UINT i;
		for(i=0;i<nSpr;i++)
			if (CSprArr[i]!=NULL && CSprArr[i][inField].Find(iValue)>=0 && IsItemInFilter(i)) 
			{
				uPosition=i+1;
				ret=CSprArr[i];
				break;
			}
	}
	return ret;
}


CString * CGPSpr::FindNextItemExact(UINT inField, const char *iValue)
{	return FindNextItemExact( inField, CString(iValue));}

CString * CGPSpr::FindNextItem(UINT inField, const char *iValue)
{	return FindNextItem( inField, CString(iValue));}

CString * CGPSpr::FindNextItemExact(UINT inField, const CString &iValue)
{
	CString * ret=NULL;
	if (uPosition<nSpr && inField<nFields && CSprArr!=NULL)
		for(;uPosition<nSpr;uPosition++)
			if (CSprArr[uPosition]!=NULL && CSprArr[uPosition][inField]==iValue) 
			{
				ret=CSprArr[uPosition++];
				break;
			}
	return ret;
}

CString * CGPSpr::FindNextItem(UINT inField, const CString &iValue)
{
	CString * ret=NULL;
	if (uPosition<nSpr && inField<nFields && CSprArr!=NULL)
		for(;uPosition<nSpr;uPosition++)
			if (CSprArr[uPosition]!=NULL && CSprArr[uPosition][inField].Find(iValue)>=0) 
			{
				ret=CSprArr[uPosition++];
				break;
			}
	return ret;
}

CString * CGPSpr::FindNextItemExactF(UINT inField, const char *iValue)
{	return FindNextItemExactF( inField, CString(iValue));}

CString * CGPSpr::FindNextItemF(UINT inField, const char *iValue)
{	return FindNextItemF( inField, CString(iValue));}

CString * CGPSpr::FindNextItemExactF(UINT inField, const CString &iValue)
{
	CString * ret=NULL;
	if (uPosition<nSpr && inField<nFields && CSprArr!=NULL)
		for(;uPosition<nSpr;uPosition++)
			if (CSprArr[uPosition]!=NULL && CSprArr[uPosition][inField]==iValue && IsItemInFilter(uPosition)) 
			{
				ret=CSprArr[uPosition++];
				break;
			}
	return ret;
}

CString * CGPSpr::FindNextItemF(UINT inField, const CString &iValue)
{
	CString * ret=NULL;
	if (uPosition<nSpr && inField<nFields && CSprArr!=NULL)
		for(;uPosition<nSpr;uPosition++)
			if (CSprArr[uPosition]!=NULL && CSprArr[uPosition][inField].Find(iValue)>=0 && IsItemInFilter(uPosition)) 
			{
				ret=CSprArr[uPosition++];
				break;
			}
	return ret;
}


UINT CGPSpr::GetCount()
{
	return nSpr;
}


long CGPSpr::GetSprInfo(VARIANT *SprInfo, DWORD dwArrType)
{
	SAFEARRAY FAR* psa = NULL;
	long ret=0;
	USES_CONVERSION;
	SAFEARRAYBOUND tmpSAB={0};

	long nElements=7;

	tmpSAB.cElements=nElements;
//AfxMessageBox("?????",MB_OK|MB_SYSTEMMODAL|MB_ICONEXCLAMATION);

	if ((V_VT(SprInfo)&VT_ARRAY) == VT_ARRAY )
	{
		psa = V_ARRAY(SprInfo); 
		SafeArrayGetLBound(psa,1,&tmpSAB.lLbound);
		SafeArrayDestroy(psa);
	}
//AfxMessageBox("0000",MB_OK|MB_SYSTEMMODAL|MB_ICONEXCLAMATION);

	VariantInit(SprInfo);

	try
	{
		COleSafeArray SAtmp;
		SAtmp.Create(VT_VARIANT, 1,&tmpSAB.cElements);
		VariantCopy(SprInfo,SAtmp);
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("SPR", "GetSprInfo","");
	}
//AfxMessageBox("11111",MB_OK|MB_SYSTEMMODAL|MB_ICONEXCLAMATION);
	psa = V_ARRAY(SprInfo);   
	// Check dimensions of the array.
	if (SafeArrayGetDim(psa) == 1)	
	{
		VARIANT HUGEP *pbstr;
		HRESULT hr;
		hr = SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
		if (!FAILED(hr))
		{
			long ind=0;
//AfxMessageBox("2222",MB_OK|MB_SYSTEMMODAL|MB_ICONEXCLAMATION);
			SafeArrayPutElement(psa,&ind,(void *)((LPVARIANT)COleVariant(SprName)));
//AfxMessageBox("3333",MB_OK|MB_SYSTEMMODAL|MB_ICONEXCLAMATION);
			ind++;
//AfxMessageBox("4444",MB_OK|MB_SYSTEMMODAL|MB_ICONEXCLAMATION);
			SafeArrayPutElement(psa,&ind,(void *)((LPVARIANT)COleVariant((long)nSpr,VT_I4 )));
//AfxMessageBox("5555",MB_OK|MB_SYSTEMMODAL|MB_ICONEXCLAMATION);
			ind++;
//AfxMessageBox("6666",MB_OK|MB_SYSTEMMODAL|MB_ICONEXCLAMATION);
			SafeArrayPutElement(psa,&ind,(void *)((LPVARIANT)COleVariant((long)nFields,VT_I4)));
			ind++;
//AfxMessageBox("7777",MB_OK|MB_SYSTEMMODAL|MB_ICONEXCLAMATION);
			SafeArrayPutElement(psa,&ind,(void *)((LPVARIANT)COleVariant((long)uPosition, VT_I4)));

//AfxMessageBox("8888",MB_OK|MB_SYSTEMMODAL|MB_ICONEXCLAMATION);
			VARIANT FilterInfo;
			VariantInit(&FilterInfo);
			CString strtmp;
			UINT k=0;

//AfxMessageBox("9999",MB_OK|MB_SYSTEMMODAL|MB_ICONEXCLAMATION);
			strtmp="";
			for(k=0;k<nFields;k++)
				if (k==0)	strtmp=GetFilter(k);
				else		strtmp+="\x01"+GetFilter(k);

//AfxMessageBox("aaaaaa",MB_OK|MB_SYSTEMMODAL|MB_ICONEXCLAMATION);
			ConvertToArray(strtmp,&FilterInfo,"\x01",dwArrType);
			ind++;
//AfxMessageBox("bbbb",MB_OK|MB_SYSTEMMODAL|MB_ICONEXCLAMATION);
			SafeArrayPutElement(psa,&ind,(void *)&FilterInfo);

//AfxMessageBox("ccccc",MB_OK|MB_SYSTEMMODAL|MB_ICONEXCLAMATION);
			for(k=0;k<nFields;k++)
				if (k==0)	strtmp=GetFilter(k);
				else		strtmp+="\x01"+GetFilter(k);

//AfxMessageBox("ddddd",MB_OK|MB_SYSTEMMODAL|MB_ICONEXCLAMATION);
			ConvertToArray(strtmp,&FilterInfo,"\x01",dwArrType);
			ind++;
//AfxMessageBox("eeee",MB_OK|MB_SYSTEMMODAL|MB_ICONEXCLAMATION);
			SafeArrayPutElement(psa,&ind,(void *)&FilterInfo);

//AfxMessageBox("fffff",MB_OK|MB_SYSTEMMODAL|MB_ICONEXCLAMATION);
			for(k=0;k<nFields;k++)
				if (k==0)	strtmp=GetSort(k);
				else		strtmp+="\x01"+GetSort(k);

//AfxMessageBox("gggg",MB_OK|MB_SYSTEMMODAL|MB_ICONEXCLAMATION);
			ConvertToArray(strtmp,&FilterInfo,"\x01",dwArrType);
			ind++;
//AfxMessageBox("hhhhh",MB_OK|MB_SYSTEMMODAL|MB_ICONEXCLAMATION);
			SafeArrayPutElement(psa,&ind,(void *)&FilterInfo);

//AfxMessageBox("iiiii",MB_OK|MB_SYSTEMMODAL|MB_ICONEXCLAMATION);
			SafeArrayUnaccessData(psa);
			ret=1;
		}
	}
//AfxMessageBox("jjjjj",MB_OK|MB_SYSTEMMODAL|MB_ICONEXCLAMATION);

	return ret;
}

long CGPSpr::FillObject(HWND ihWnd, UINT ObjType, const char *Params, long FillType)
{
	long ret=-1;
	char *pos=new char [(int)strlen(Params)+100];
	strcpy(pos,Params);
	if (ihWnd!=NULL)
	{
//		char sss[1000];
//		GetClassName(ihWnd,sss,100);
//"ThunderComboBox""ComboBox"
//"ThunderListBox""ListBox"
		switch(ObjType&0xFFFF)
		{
		case GPSPRFILL_COMBOBOX:
		case GPSPRFILL_COMBOBOXEX:
			{
				COMBOBOXEXITEM cbi={0};
				cbi.mask=CBEIF_TEXT;
				cbi.cchTextMax=5000;
				cbi.pszText=new char [5000];
				cbi.iItem=0;

				if ((FillType&0x1)==0) SendMessage(ihWnd,CB_RESETCONTENT,0,0);
				CString separator;
				char *tmp=pos,*tmp2;
				tmp2=strchr(tmp,',');
				if (tmp2!=NULL) *(tmp2++)=0;
				else tmp2="";
				separator=tmp;
				tmp=tmp2;
				if (nFields>0)
				{
					UINT *fldArr=new UINT [nFields];
					UINT nf;
					for(nf=0;nf<nFields && *tmp!=0;nf++)
					{
						if ((fldArr[nf]=atoi(tmp))>=nFields) fldArr[nf]=0;
						
						while(*tmp!=0 && *tmp!=',' && *tmp!=GPC.DelimiterIn1) tmp++;
						if (*tmp!=0) tmp++;
					}
					if (nf>0)
					{
						CString newItem;
						MoveFirst();
						const CString * item;
						while((item=GetNextItem())!=NULL)
						{
							newItem="";
							UINT i;
							for(i=0;i<nf;i++)
							{
								if (i!=0) newItem+=separator;
								newItem+=item[fldArr[i]];
							}
							if ((ObjType&0xFFFF)==GPSPRFILL_COMBOBOX)
							{
								SendMessage(ihWnd,CB_ADDSTRING,0,(LPARAM)((LPCTSTR)newItem));
							}
							else
							{
								strncpy(cbi.pszText,(LPCSTR)newItem,4990);
								cbi.pszText[4990]=0;
								SendMessage(ihWnd,CBEM_INSERTITEM,0,(LPARAM)&cbi);
								cbi.iItem++;
							}
						}
						ret=SendMessage(ihWnd,CB_GETCOUNT,0,0);
						SendMessage(ihWnd,CB_SETCURSEL,-1,0);
					}
					delete[] fldArr;
					delete[] cbi.pszText;
				}
			}
			break;
		case GPSPRFILL_LISTBOX:
			{
				if ((FillType&0x1)==0) SendMessage(ihWnd,LB_RESETCONTENT,0,0);
				CString separator;
				char *tmp=pos,*tmp2;
				tmp2=strchr(tmp,',');
				if (tmp2!=NULL) *(tmp2++)=0;
				else tmp2="";
				separator=tmp;
				tmp=tmp2;
				if (nFields>0)
				{
					UINT *fldArr=new UINT [nFields];
					UINT nf;
					for(nf=0;nf<nFields && *tmp!=0;nf++)
					{
						if ((fldArr[nf]=atoi(tmp))>=nFields) fldArr[nf]=0;
						
						while(*tmp!=0 && *tmp!=',' && *tmp!=GPC.DelimiterIn1) tmp++;
						if (*tmp!=0) tmp++;
					}
					if (nf>0)
					{
						CString newItem;
						MoveFirst();
						const CString * item;
						while((item=GetNextItem())!=NULL)
						{
							newItem="";
							UINT i;
							for(i=0;i<nf;i++)
							{
								if (i!=0) newItem+=separator;
								newItem+=item[fldArr[i]];
							}
							SendMessage(ihWnd,LB_ADDSTRING,0,(LPARAM)((LPCTSTR)newItem));
						}
						ret=SendMessage(ihWnd,LB_GETCOUNT,0,0);
					}
					delete[] fldArr;
				}
			}
			break;
		case GPSPRFILL_LISTCTRL:
			{
				if ((FillType&0x1)==0) SendMessage(ihWnd,LVM_DELETEALLITEMS,0,0);
				char *FieldsPos=pos,*ColPos;
				ColPos=strchr(FieldsPos,',');
				if (ColPos!=NULL) *(ColPos++)=0;
				else ColPos="";

				UINT nFlds=1;
				UINT nCols=1;

				char *tmppos=FieldsPos;
				while(*tmppos!=0)
					if (*(tmppos++)==GPC.DelimiterIn1) nFlds++;
				tmppos=ColPos;
				while(*tmppos!=0)
					if (*(tmppos++)==GPC.DelimiterIn1) nCols++;

				UINT *fldArr=new UINT [nFlds];
				UINT *colArr=new UINT [nCols];

				tmppos=FieldsPos;
				UINT i=0;
				while(*tmppos!=0)
				{
					fldArr[i++]=atoi(tmppos);
					while(*tmppos!=0 && *tmppos!=GPC.DelimiterIn1) tmppos++;
					if (*tmppos==GPC.DelimiterIn1) tmppos++;
				}
				tmppos=ColPos;
				i=0;
				while(*tmppos!=0)
				{
					colArr[i++]=atoi(tmppos);
					while(*tmppos!=0 && *tmppos!=GPC.DelimiterIn1) tmppos++;
					if (*tmppos==GPC.DelimiterIn1) tmppos++;
				}
				if (nFlds>nFields) nFlds=nFields;
				if (nFlds>nCols) nFlds=nCols;
				if (nFlds<nCols) nCols=nFlds;

				MoveFirst();
				const CString * item;
				LVITEM lvi={0};
				LVITEM lvitext={0};
				lvitext.mask=lvi.mask=LVIF_TEXT;
				lvi.pszText="";

				while((item=GetNextItem())!=NULL)
				{
					GPTextArray *ar=NULL;
					if ((ObjType&GPSPRFILL_USEDATA)==GPSPRFILL_USEDATA)
					{
						ar=new GPTextArray;
						lvi.mask|=LVIF_PARAM;
						ar->SetItem(0,lvi.pszText);
						lvi.lParam=(DWORD) ar;
					}

					lvi.iItem=1000000;
					int nItem=SendMessage(ihWnd,LVM_INSERTITEM,0,(LPARAM)(&lvi));
					if (nItem>=0)
						for(i=0;i<nFlds;i++)
						{
							if (fldArr[i]<nFields)
							{
								lvitext.pszText=(LPTSTR)((LPCTSTR)item[fldArr[i]]);
								lvitext.iItem=nItem;
								lvitext.iSubItem=colArr[i];
								SendMessage(ihWnd,LVM_SETITEMTEXT,nItem,(LPARAM)(&lvitext));
								if (ar!=NULL)
									ar->SetItem(colArr[i],(LPCSTR)item[fldArr[i]]);
							}
						}
				}
				ret=SendMessage(ihWnd,LVM_GETITEMCOUNT,0,0);
				delete[] colArr;
				delete[] fldArr;
			}
			break;
		case GPSPRFILL_COMLISTCTRL:
			{

				LPDISPATCH pDCListItems;
				CWnd::FromHandle(ihWnd)->InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDCListItems, NULL);
				COleDispatchDriver DCListItems;
				DCListItems.AttachDispatch(pDCListItems);

				if ((FillType&0x1)==0)
					DCListItems.InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);

				char *FieldsPos=pos,*ColPos;
				ColPos=strchr(FieldsPos,',');
				if (ColPos!=NULL) *(ColPos++)=0;
				else ColPos="";

				UINT nFlds=1;
				UINT nCols=1;

				char *tmppos=FieldsPos;
				while(*tmppos!=0)
					if (*(tmppos++)==GPC.DelimiterIn1) nFlds++;
				tmppos=ColPos;
				while(*tmppos!=0)
					if (*(tmppos++)==GPC.DelimiterIn1) nCols++;

				UINT *fldArr=new UINT [nFlds];
				UINT *colArr=new UINT [nCols];

				tmppos=FieldsPos;
				UINT i=0;
				while(*tmppos!=0)
				{
					fldArr[i++]=atoi(tmppos);
					while(*tmppos!=0 && *tmppos!=GPC.DelimiterIn1) tmppos++;
					if (*tmppos==GPC.DelimiterIn1) tmppos++;
				}
				tmppos=ColPos;
				i=0;
				while(*tmppos!=0)
				{
					colArr[i++]=atoi(tmppos);
					while(*tmppos!=0 && *tmppos!=GPC.DelimiterIn1) tmppos++;
					if (*tmppos==GPC.DelimiterIn1) tmppos++;
				}
				if (nFlds>nCols) nFlds=nCols;
				if (nFlds<nCols) nCols=nFlds;

				CString newItem;
				MoveFirst();
				const CString * item;
				BOOL bSorted=FALSE;
				CWnd::FromHandle(ihWnd)->InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&bSorted, NULL);
				BYTE parmsSorted[] =	VTS_BOOL;
				CWnd::FromHandle(ihWnd)->InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parmsSorted, FALSE);


				LVITEM lvi={0};
				LVITEM lvitext={0};
				lvitext.mask=lvi.mask=LVIF_TEXT;
				lvi.pszText="";

				BYTE parmsAdd[] =VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
				COleVariant Index((long)0,VT_I4),Key(""), Text(""), Icon(""), SmallIcon("");
				COleDispatchDriver DCItem;
				BYTE parmsSItem[] =	VTS_I2 VTS_BSTR;

				while((item=GetNextItem())!=NULL)
				{
					newItem="";
					LPDISPATCH pDispatchItem;
					DCListItems.InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&pDispatchItem, parmsAdd,
							(VARIANT*)Index, NULL, (VARIANT*)Text, NULL, NULL);
	
					DCItem.AttachDispatch(pDispatchItem);
					
					for(i=0;i<nFlds;i++)
						if (fldArr[i]<nFields)
								DCItem.InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parmsSItem,
									 (short)colArr[i], (LPCTSTR)item[fldArr[i]]);

					DCItem.DetachDispatch();
				}

				CWnd::FromHandle(ihWnd)->InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parmsSorted, bSorted);
				DCListItems.InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&ret, NULL);
				DCListItems.DetachDispatch();
				delete[] colArr;
				delete[] fldArr;
			}
			break;
		}
	}

	delete[] pos;
	return ret;
}

long CGPSpr::ReplaceObject(HWND ihWnd, UINT ObjType, const char *Params)
{
	long ret=-1;
	char *pos=new char [(int)strlen(Params)+100];
	strcpy(pos,Params);
	if (ihWnd!=NULL)
	{
		CString separator;
		char *tmp=pos,*tmp2;
		tmp2=strchr(tmp,',');
		if (tmp2!=NULL) *(tmp2++)=0;
		else tmp2="";
		UINT IdentFld=atoi(tmp2);
		tmp=tmp2;
		tmp2=strchr(tmp,',');
		if (tmp2!=NULL) *(tmp2++)=0;
		else tmp2="";

		separator=tmp;
		tmp=tmp2;
		switch(ObjType&0xFFFF)
		{
		case GPSPRFILL_COMBOBOX:
		case GPSPRFILL_COMBOBOXEX:
			{
				int cnt=SendMessage(ihWnd,CB_GETCOUNT,0,0);
				COMBOBOXEXITEM cbi={0};
				cbi.mask=CBEIF_TEXT;
				cbi.cchTextMax=4990;
				cbi.pszText=new char [5000];
				cbi.iItem=0;

				if (nFields>0 && IdentFld<nFields && cnt>0 && cnt!=CB_ERR)
				{
					UINT *fldArr=new UINT [nFields];
					UINT cursel=SendMessage(ihWnd,CB_GETCURSEL,0,0);
					UINT nf;
					for(nf=0;nf<nFields && *tmp!=0;nf++)
					{
						if ((fldArr[nf]=atoi(tmp))>=nFields) fldArr[nf]=0;
						
						while(*tmp!=0 && *tmp!=',' && *tmp!=GPC.DelimiterIn1) tmp++;
						if (*tmp!=0) tmp++;
					}
					if (nf>0)
					{
						CString *tmpcstr=new CString [cnt];
						int i;
						for(i=0;i<cnt;i++)
						{
							LPTSTR p=tmpcstr[i].GetBufferSetLength( 2*SendMessage(ihWnd,CB_GETLBTEXTLEN,i,0)+10);
							int l=SendMessage(ihWnd,CB_GETLBTEXT,i,(LPARAM)p);
							if (l!=CB_ERR) p[l]=0;
							tmpcstr[i].ReleaseBuffer();
						}

						SendMessage(ihWnd,CB_RESETCONTENT,0,0);
						CString newItem;
						const CString * item;

						for(i=0;i<cnt;i++)
						{
							item=FindItemExact(IdentFld,tmpcstr[i]);
							newItem="";
							if (item==NULL) newItem=tmpcstr[i];
							else
							{
								UINT j;
								for(j=0;j<nf;j++)
								{
									if (j!=0) newItem+=separator;
									newItem+=item[fldArr[j]];
								}
							}

							if ((ObjType&0xFFFF)==GPSPRFILL_COMBOBOX)
							{
								SendMessage(ihWnd,CB_ADDSTRING,0,(LPARAM)((LPCTSTR)newItem));
							}
							else
							{
								strncpy(cbi.pszText,(LPCSTR)newItem,4990);
								cbi.pszText[4990]=0;
								SendMessage(ihWnd,CBEM_INSERTITEM,0,(LPARAM)&cbi);
								cbi.iItem++;
							}
						}
						ret=SendMessage(ihWnd,CB_GETCOUNT,0,0);

						delete[]  tmpcstr;
					}
					delete[] fldArr;
					delete[] cbi.pszText;
					if (cursel!=CB_ERR) SendMessage(ihWnd,CB_SETCURSEL,cursel,0);
				}
			}
			break;
		case GPSPRFILL_LISTBOX:
			{
				int cnt=SendMessage(ihWnd,LB_GETCOUNT,0,0);
				UINT cursel=SendMessage(ihWnd,LB_GETCURSEL,0,0);
				if (nFields>0 && IdentFld<nFields && cnt>0 && cnt!=CB_ERR)
				{
					UINT *fldArr=new UINT [nFields];
					UINT nf;
					for(nf=0;nf<nFields && *tmp!=0;nf++)
					{
						if ((fldArr[nf]=atoi(tmp))>=nFields) fldArr[nf]=0;
						
						while(*tmp!=0 && *tmp!=',' && *tmp!=GPC.DelimiterIn1) tmp++;
						if (*tmp!=0) tmp++;
					}
					if (nf>0)
					{
						CString *tmpcstr=new CString [cnt];
						int i;
						for(i=0;i<cnt;i++)
						{
							LPTSTR p=tmpcstr[i].GetBufferSetLength( 2*SendMessage(ihWnd,LB_GETTEXTLEN,i,0)+10);
							SendMessage(ihWnd,LB_GETTEXT,i,(LPARAM)p);
							tmpcstr[i].ReleaseBuffer();
						}

						cursel=LB_ERR;
						if ((CWnd::FromHandle(ihWnd)->GetStyle()&LBS_MULTIPLESEL)!=LBS_MULTIPLESEL)
							cursel=SendMessage(ihWnd,LB_GETCURSEL,0,0);

						SendMessage(ihWnd,LB_RESETCONTENT,0,0);

						CString newItem;
						const CString * item;

						for(i=0;i<cnt;i++)
						{
							item=FindItemExact(IdentFld,tmpcstr[i]);
							newItem="";
							if (item==NULL) newItem=tmpcstr[i];
							else
							{
								UINT j;
								for(j=0;j<nf;j++)
								{
									if (j!=0) newItem+=separator;
									newItem+=item[fldArr[j]];
								}
							}
							SendMessage(ihWnd,LB_ADDSTRING,0,(LPARAM)((LPCTSTR)newItem));
						}
						ret=SendMessage(ihWnd,LB_GETCOUNT,0,0);
						if (cursel!=LB_ERR) 
							SendMessage(ihWnd,LB_SETCURSEL,cursel,0);
						delete[]  tmpcstr;
					}
					delete[] fldArr;
					if (cursel!=LB_ERR) SendMessage(ihWnd,LB_SETCURSEL,cursel,0);
				}
			}
			break;
		}
	}

	delete[] pos;
	return ret;
}

long CGPSpr::FillObject(LPDISPATCH lpDisp, const char *Params, long FillType)
{
	long ret=-1;
	char *pos=new char [(int)strlen(Params)+100];
	strcpy(pos,Params);
	if (lpDisp!=NULL)
	{
		char *FieldsPos=pos,*ColPos;
		ColPos=strchr(FieldsPos,',');
		if (ColPos!=NULL) *(ColPos++)=0;
		else ColPos="";

		UINT nFlds=1;
		UINT nCols=1;

		char *tmppos=FieldsPos;
		while(*tmppos!=0)
			if (*(tmppos++)==GPC.DelimiterIn1) nFlds++;
		tmppos=ColPos;
		while(*tmppos!=0)
			if (*(tmppos++)==GPC.DelimiterIn1) nCols++;

		UINT *fldArr=new UINT [nFlds];
		UINT *colArr=new UINT [nCols];

		tmppos=FieldsPos;
		UINT i=0;
		while(*tmppos!=0)
		{
			fldArr[i++]=atoi(tmppos);
			while(*tmppos!=0 && *tmppos!=GPC.DelimiterIn1) tmppos++;
			if (*tmppos==GPC.DelimiterIn1) tmppos++;
		}
		tmppos=ColPos;
		i=0;
		while(*tmppos!=0)
		{
			colArr[i++]=atoi(tmppos);
			while(*tmppos!=0 && *tmppos!=GPC.DelimiterIn1) tmppos++;
			if (*tmppos==GPC.DelimiterIn1) tmppos++;
		}
		if (nFlds>nCols) nFlds=nCols;
		if (nFlds<nCols) nCols=nFlds;


		CString GUIDListView ("{E0BCE3B3-7EB5-4D6A-A7BB-6062BBE128E7}");
		CString GUIDFlexGrid ("{6B93DE84-A00D-47B0-9A78-114E8B0CF652}");
		CString GUIDFlexGrid2("{A9ED5E4E-1791-11D5-AB13-00485481E401}");
		COleVariant strGU("{c200e360-38c5-11ce-ae62-08002b2b79ef}   ");
		{
			ITypeInfo *pTInfo;
			lpDisp->GetTypeInfo(0,0,&pTInfo);
			TYPEATTR *hh;
			pTInfo->GetTypeAttr(&hh);
			::StringFromGUID2(hh->guid,strGU.bstrVal,40);
			LPOLESTR lpOl=(LPOLESTR)new USHORT [20000];
			::ProgIDFromCLSID(hh->guid,&lpOl);
			pTInfo->Release();
		}

		if (GUIDListView==strGU.bstrVal) // ListView
		{
			COleDispatchDriver DCList;
			DCList.AttachDispatch(lpDisp);
			LPDISPATCH pDCListItems;
			DCList.InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDCListItems, NULL);

			COleDispatchDriver DCListItems;
			DCListItems.AttachDispatch(pDCListItems);

			if ((FillType&0x1)==0)
				DCListItems.InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);

			CString newItem;
			MoveFirst();
			const CString * item;
			BOOL bSorted=FALSE;
			DCList.InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&bSorted, NULL);
			BYTE parmsSorted[] =	VTS_BOOL;
			DCList.InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parmsSorted, FALSE);

			LVITEM lvi={0};
			LVITEM lvitext={0};
			lvitext.mask=lvi.mask=LVIF_TEXT;
			lvi.pszText="";

			BYTE parmsAdd[] =VTS_PVARIANT;
			BYTE parmsSItem[] =	VTS_I2 VTS_BSTR;
			BYTE parmsText[] =	VTS_BSTR;

			COleDispatchDriver DCItem;

			while((item=GetNextItem())!=NULL)
			{
				newItem="";
				LPDISPATCH pDispatchItem;
				DCListItems.InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&pDispatchItem, NULL);
				DCItem.AttachDispatch(pDispatchItem);
				
				for(i=0;i<nFlds;i++)
					if (fldArr[i]<nFields)
					{
						if (colArr[i]==0)
							DCItem.InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parmsText, (LPCTSTR)item[fldArr[i]]);
						else
							DCItem.InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parmsSItem,
								 (short)(colArr[i]), (LPCTSTR)item[fldArr[i]]);
					}

				DCItem.DetachDispatch();
			}

			DCList.InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parmsSorted, bSorted);
			DCListItems.InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&ret, NULL);
			DCListItems.DetachDispatch();
			DCList.DetachDispatch();
		}
		else
		if (GUIDFlexGrid==strGU.bstrVal || GUIDFlexGrid2==strGU.bstrVal) // FlexGrid
		{
			COleDispatchDriver DCList;
			DCList.AttachDispatch(lpDisp);
			BYTE parmsAdd[] =VTS_BSTR VTS_VARIANT;
			BYTE parmsSetRow[] =	VTS_I4;
			BYTE parmsText[] =  VTS_BSTR;

			if ((FillType&0x1)==0)
			{
				long nFix=0;
				DCList.InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&nFix, NULL);
				DCList.InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parmsSetRow,nFix);
			}

			CString newItem;
			const CString * item;
			COleVariant nLines((long)0,VT_I4);
			DCList.InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_I4, (void*)&nLines.lVal, NULL);

		
			MoveFirst();
			while((item=GetNextItem())!=NULL)
			{
				newItem="";
				DCList.InvokeHelper(0x42, DISPATCH_METHOD, VT_EMPTY, NULL, parmsAdd,(LPCTSTR)newItem, &nLines);

				DCList.InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parmsSetRow, nLines.lVal);

				for(i=0;i<nFlds;i++)
					if (fldArr[i]<nFields)
					{
						DCList.InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parmsSetRow, (long)(colArr[i]));
						DCList.InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parmsText, (LPCTSTR)item[fldArr[i]]);
					}

				nLines.lVal++;
			}

			DCList.InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_I4, (void*)&nLines.lVal, NULL);
			ret=nLines.lVal;
			DCList.DetachDispatch();
		}
			else 
				AfxMessageBox(CString(strGU.bstrVal),0,0); // FlexGrid


		delete[] colArr;
		delete[] fldArr;
	}
	delete[] pos;
	return ret;
}

long CGPSpr::GetItemAsArray(UINT nItem, VARIANT FAR* RetArray)
{
	long ret =-1;
	if (nItem<nSpr)
	{
		SAFEARRAY FAR* psa = NULL;

		USES_CONVERSION;
		SAFEARRAYBOUND tmpSAB={0};
		tmpSAB.cElements=nFields;

		if ((V_VT(RetArray)&VT_ARRAY) == VT_ARRAY )
		{
			psa = V_ARRAY(RetArray); 
			SafeArrayGetLBound(psa,1,&tmpSAB.lLbound);
			SafeArrayDestroy(psa);
		}

		VariantInit(RetArray);

		try
		{
			COleSafeArray SAtmp;
			SAtmp.Create(VT_BSTR, 1,&tmpSAB.cElements);
			VariantCopy(RetArray,SAtmp);
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("SPR", "GetItemAsArray","");
		}

		psa = V_ARRAY(RetArray);   
		if (SafeArrayGetDim(psa) != 1)			AfxThrowOleDispatchException(1002,IDS_GPOLEEXEPTION1002);
		else
		{
			BSTR HUGEP *pbstr;
			HRESULT hr;
			hr = SafeArrayAccessData(psa, (void HUGEP* FAR*)&pbstr);
			if (FAILED(hr))		AfxThrowOleDispatchException(1001,IDS_GPOLEEXEPTION1001);
			UINT ix;
			for(ix=0; ix<nFields; ix++)
			{
				CSprArr[nItem][ix].SetSysString(&pbstr[ix]);
			}
			SafeArrayUnaccessData(psa);
			ret=nFields;
		}
	}
	return ret;
}

long CGPSpr::FillByArray(const VARIANT FAR& KeyArray, long nField, VARIANT FAR* RetArray)
{
	long ret=-1;
	CString KeyString;
	ConvVariantToString(KeyArray,KeyString,"\x7F");
	{
		SAFEARRAY FAR* psa = NULL;

		USES_CONVERSION;
		SAFEARRAYBOUND tmpSAB={0};

		unsigned long nElement=1;
		int nFirst=0,nLast=0;
		while((nLast=KeyString.Find("\x7F",nLast))>=0) 
			{	nElement++;	nLast++;	}


		tmpSAB.cElements=nElement;

		if ((V_VT(RetArray)&VT_ARRAY) == VT_ARRAY )
		{
			psa = V_ARRAY(RetArray); 
			SafeArrayGetLBound(psa,1,&tmpSAB.lLbound);
			SafeArrayDestroy(psa);
		}

		VariantInit(RetArray);

		try
		{
			COleSafeArray SAtmp;
			SAtmp.Create(VT_VARIANT, 1,&tmpSAB.cElements);
			VariantCopy(RetArray,SAtmp);
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("SPR", "FillByArray","");
		}

		psa = V_ARRAY(RetArray);   

		VARIANT *pbVar;
		HRESULT hr;


		CString item;
		long nEl=0;
		nFirst=0;nLast=0;
		ret=0;
		while(nLast>=0) 
		{
			nLast=KeyString.Find("\x7F",nFirst);
			if (nLast<0)
			{
				item=KeyString.GetLength()-nFirst>0?KeyString.Right(KeyString.GetLength()-nFirst):"";
				nLast--;
			}
			else 
			if (nLast==nFirst)	item="";
			else				item=KeyString.Mid(nFirst,nLast-nFirst);

			if (FindItemExact(nField,item)!=NULL)
			{
				ret++;
				hr = SafeArrayPtrOfIndex(psa,&nEl, (void **)&pbVar);
				if (FAILED(hr))		AfxThrowOleDispatchException(1001,IDS_GPOLEEXEPTION1001);
				GetItemAsArray(uPosition-1,pbVar);
			}
			nEl++;
			nFirst=++nLast;
		}
	}

	return ret;
}

long CGPSpr::ReplaceObjectEx(HWND ihWnd, UINT ObjType, long StartItem, long EndItem, char *ItemsFlags, const char *Params)
{
	long ret=0;
	if (ihWnd!=NULL && StartItem<EndItem && ItemsFlags!=NULL)
	{
		long cnt=EndItem-StartItem+1;
		if (cnt>0)
		{//nCodeCol,nReplCol,nFindField,nTextField,Prefix1
			int nCodeCol=0,nReplCol=0,nFindField=0,nTextField=0;
			char *Prefix=new char [(int)strlen(Params)+10];
			*Prefix=0;
			m_LastScanf=sscanf(Params,"%ld,%ld,%ld,%ld,%s",&nCodeCol,&nReplCol,&nFindField,&nTextField,Prefix);
			CString str;
			long nFl=0;
			if ((UINT)nFindField<nFields && (UINT)nTextField<nFields)
				switch(ObjType&0xFFFF)
				{
				case GPSPRFILL_COMBOBOX:
				case GPSPRFILL_COMBOBOXEX:
					{
						COMBOBOXEXITEM cbi={0};
						cbi.mask=CBEIF_TEXT;
						cbi.cchTextMax=4990;
						cbi.pszText=new char [5000];
						cbi.iItem=0;
						UINT stl=GetWindowLong(ihWnd,GWL_STYLE);
						BOOL sorted=FALSE;
						if ((stl&CBS_SORT)==CBS_SORT) 
						{
							sorted=TRUE;
							SetWindowLong(ihWnd,GWL_STYLE,stl^CBS_SORT);
						}
						UINT cursel=SendMessage(ihWnd,CB_GETCURSEL,0,0);
						long i;
						for(i=StartItem;i<=EndItem;i++,nFl++)
						{
							if (ItemsFlags[nFl]!=0) continue;

							LPTSTR p=str.GetBufferSetLength(2*SendMessage(ihWnd,CB_GETLBTEXTLEN,i,0)+10);
							int l=SendMessage(ihWnd,CB_GETLBTEXT,i,(LPARAM)p);
							if (l!=CB_ERR) p[l]=0;
							str.ReleaseBuffer();

							const CString *item=FindItemExact(nFindField,str);
							if (item==NULL) continue;

							str=Prefix;
							str+=item[nTextField];
							SendMessage(ihWnd,CB_DELETESTRING,i,0);

							if ((ObjType&0xFFFF)==GPSPRFILL_COMBOBOX)
							{
								SendMessage(ihWnd,CB_INSERTSTRING,i,(LPARAM)((LPCTSTR)str));
							}
							else
							{
								cbi.iItem=i;
								strncpy(cbi.pszText,(LPCSTR)str,4990);
								cbi.pszText[4990]=0;
								SendMessage(ihWnd,CBEM_INSERTITEM,0,(LPARAM)&cbi);
							}
							ret++;
							ItemsFlags[nFl]=1;
						}
						if (cursel!=CB_ERR) SendMessage(ihWnd,CB_SETCURSEL,cursel,0);
						if (sorted) SetWindowLong(ihWnd,GWL_STYLE,stl);
						delete[] cbi.pszText;
					}
					break;
				case GPSPRFILL_LISTBOX:	
					{
						UINT stl=GetWindowLong(ihWnd,GWL_STYLE);
						BOOL sorted=FALSE;
						if ((stl&LBS_SORT)==LBS_SORT) 
						{
							sorted=TRUE;
							SetWindowLong(ihWnd,GWL_STYLE,stl^LBS_SORT);
						}
						int cursel=LB_ERR;
						if ((stl&LBS_MULTIPLESEL)!=LBS_MULTIPLESEL)
							cursel=SendMessage(ihWnd,LB_GETCURSEL,0,0);

						long i;
						for(i=StartItem;i<=EndItem;i++,nFl++)
						{
							if (ItemsFlags[nFl]!=0) continue;

							LPTSTR p=str.GetBufferSetLength(2*SendMessage(ihWnd,LB_GETTEXTLEN,i,0)+10);
							SendMessage(ihWnd,LB_GETTEXT,i,(LPARAM)p);
							str.ReleaseBuffer();

							const CString *item=FindItemExact(nFindField,str);
							if (item==NULL) continue;

							str=Prefix;
							str+=item[nTextField];
							SendMessage(ihWnd,LB_DELETESTRING,i,0);
							SendMessage(ihWnd,LB_INSERTSTRING,i,(LPARAM)((LPCTSTR)str));
							ret++;
							ItemsFlags[nFl]=1;
						}
						if (cursel!=LB_ERR) 
							SendMessage(ihWnd,LB_SETCURSEL,cursel,0);
						if (sorted) SetWindowLong(ihWnd,GWL_STYLE,stl);
					}	
					break;
				case GPSPRFILL_LISTCTRL:
					{
						UINT stl=GetWindowLong(ihWnd,GWL_STYLE);
						BOOL sorted=FALSE;
						if ((stl&LVS_AUTOARRANGE)==LVS_AUTOARRANGE) 
						{
							sorted=TRUE;
							SetWindowLong(ihWnd,GWL_STYLE,stl^LVS_AUTOARRANGE);
						}

						LVITEM lvigettext={0};
						lvigettext.mask=LVIF_TEXT|LVIF_PARAM;
						lvigettext.pszText=str.GetBufferSetLength(2080);
						lvigettext.cchTextMax=2000;
						lvigettext.iSubItem=nCodeCol;

						LVITEM lvisettext={0};
						lvisettext.mask=LVIF_TEXT;
						lvisettext.iSubItem=nReplCol;
						CString NewItem;
						GPTextArray *ar=NULL;

						long i;
						for(i=StartItem;i<=EndItem;i++,nFl++)
						{
							if (ItemsFlags[nFl]!=0) continue;

							lvigettext.iItem=i;
							SendMessage(ihWnd,LVM_GETITEM,0,(LPARAM)(&lvigettext));

							const CString *item=FindItemExact(nFindField,str);
							if (item==NULL) continue;


							NewItem=Prefix;
							NewItem+=item[nTextField];
							lvisettext.pszText=(LPTSTR)((LPCTSTR)NewItem);
							lvisettext.iItem=i;

							if ((ObjType&GPSPRFILL_USEDATA)==GPSPRFILL_USEDATA)
							{
								ar=(GPTextArray *)lvigettext.lParam;
								if (ar!=NULL) ar->SetItem(lvisettext.iSubItem,str);
							}
							SendMessage(ihWnd,LVM_SETITEMTEXT,i,(LPARAM)(&lvisettext));

							ret++;
							ItemsFlags[nFl]=1;
						}

						str.ReleaseBuffer();
						if (sorted) SetWindowLong(ihWnd,GWL_STYLE,stl);
					}	
					break;
				}
			delete[] Prefix;
		}
	}
	return ret;
}


long CGPSpr::ReplaceObjectEx(LPDISPATCH lpDisp, long StartItem, long EndItem, char *ItemsFlags, const char *Params)
{
	long ret=-1;
	try
	{
	char *pos=new char [(int)strlen(Params)+100];
	long cnt=EndItem-StartItem+1;
	strcpy(pos,Params);
	if (lpDisp!=NULL && StartItem<EndItem && ItemsFlags!=NULL && cnt>0)
	{//nCodeCol,nReplCol,nFindField,nTextField,Prefix1
		int nCodeCol=0,nReplCol=0,nFindField=0,nTextField=0;
		const char *Prefix;
		m_LastScanf=sscanf(Params,"%ld,%ld,%ld,%ld",&nCodeCol,&nReplCol,&nFindField,&nTextField);
		Prefix=Params;
		int cntPref=0;
		while(*Prefix!=0 && cntPref<4)
			if (*(Prefix++)==',') cntPref++;
		CString str;
		long nFl=0;
		if ((UINT)nFindField<nFields && (UINT)nTextField<nFields)
		{

			CString GUIDListView("{E0BCE3B3-7EB5-4D6A-A7BB-6062BBE128E7}");
			CString GUIDFlexGrid("{6B93DE84-A00D-47B0-9A78-114E8B0CF652}");
			CString GUIDFlexGrid2("{A9ED5E4E-1791-11D5-AB13-00485481E401}");
			CString GUIDFlexGrid3("{6262D3A0-531B-11CF-91F6-C2863C385E30}");
			CString GUIDFlexGrid4("{5F4DF280-531B-11CF-91F6-C2863C385E30}");
			COleVariant strGU("{c200e360-38c5-11ce-ae62-08002b2b79ef}   ");
			{
				ITypeInfo *pTInfo;
				lpDisp->GetTypeInfo(0,0,&pTInfo);
				TYPEATTR *hh;
				pTInfo->GetTypeAttr(&hh);
				::StringFromGUID2(hh->guid,strGU.bstrVal,40);
				pTInfo->Release();
			}

			if (GUIDListView==strGU.bstrVal) // ListView
			{
				COleDispatchDriver DCList;
				DCList.AttachDispatch(lpDisp);
				LPDISPATCH pDCListItems;
				DCList.InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDCListItems, NULL);

				COleDispatchDriver DCListItems;
				DCListItems.AttachDispatch(pDCListItems);

				BYTE parmsSorted[] =	VTS_BOOL;
				BYTE parmsAdd[] =VTS_PVARIANT;
				BYTE parmsSItem[] =	VTS_I2 VTS_BSTR;
				BYTE parmsText[] =	VTS_BSTR;
				BYTE parmsSubItem[] =  VTS_I2;

				BOOL bSorted=FALSE;
				DCList.InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&bSorted, NULL);
				DCList.InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parmsSorted, FALSE);

				CString NewItem;

				short IndexCodeCol=nCodeCol;
				short IndexTextCol=nReplCol;

				COleDispatchDriver DCItem;
				COleVariant nIndex((long)0,VT_I4);

				long i;
				for(i=StartItem;i<=EndItem;i++,nFl++)
				{
					if (ItemsFlags[nFl]!=0) continue;
					nIndex.lVal=i;

					LPDISPATCH pDispatchItem;
					DCListItems.InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatchItem, parmsAdd,nIndex);
					DCItem.AttachDispatch(pDispatchItem);

					if (IndexCodeCol==0)
						DCItem.InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&NewItem, NULL);
					else
						DCItem.InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&NewItem, parmsSubItem,IndexCodeCol);

					const CString *item=FindItemExact(nFindField,NewItem);
					if (item!=NULL) 
					{
						NewItem=Prefix;
						NewItem+=item[nTextField];
						if (IndexTextCol==0)
							DCItem.InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parmsText,(LPCTSTR)NewItem);
						else
							DCItem.InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parmsSItem,IndexTextCol, (LPCTSTR)NewItem);

						ret++;
						ItemsFlags[nFl]=1;
					}

					DCItem.DetachDispatch();
				}

				DCList.InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parmsSorted, bSorted);
				DCListItems.InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&ret, NULL);
				DCListItems.DetachDispatch();
				DCList.DetachDispatch();
			}
			else
//			if (GUIDFlexGrid==strGU.bstrVal || GUIDFlexGrid2==strGU.bstrVal || GUIDFlexGrid3==strGU.bstrVal || GUIDFlexGrid4==strGU.bstrVal) // FlexGrid
			{
				COleDispatchDriver DCList;
				DCList.AttachDispatch(lpDisp);
				BYTE parmsAdd[] =VTS_BSTR VTS_VARIANT;
				BYTE parmsSetRow[] =	VTS_I4;
				BYTE parmsText[] =  VTS_BSTR;

				CString NewItem;
				long nGridRows;
				DCList.InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4,(void*)&nGridRows, NULL);

				long i;
				for(i=StartItem;i<=EndItem && i<nGridRows;i++,nFl++)
				{
					if (ItemsFlags[nFl]!=0) continue;

					DCList.InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parmsSetRow, i);
					DCList.InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parmsSetRow, nCodeCol);
					DCList.InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&NewItem, NULL);

					const CString *item=FindItemExact(nFindField,NewItem);
					if (item!=NULL) 
					{
						NewItem=Prefix;
						NewItem+=item[nTextField];
						DCList.InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parmsSetRow, nReplCol);
						DCList.InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parmsText, (LPCTSTR)NewItem);

						ret++;
						ItemsFlags[nFl]=1;
					}

				}
				DCList.DetachDispatch();
			}
//			else 
//				AfxMessageBox(CString(strGU.bstrVal),0,0); // FlexGrid

		}
	}
	delete[] pos;
	}
	catch(...)
	{
		GPC.m_ErrReport.GPWriteErrorLog("SPR", "ReplaceObjectEx","");
		ret=-1;
	}
	return ret;
}

const CString CGPSpr::GetFilter(UINT iField)
{
	return m_FilterArray.GetFilter(iField);
}

const CString CGPSpr::GetSort(UINT iField)
{
	CString ret;
	if (iField<nFields && SortPriorArray!=NULL)
		ret=SortPriorArray[iField];
	return ret;
}

