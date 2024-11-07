// TermCap.cpp: implementation of the CTermCap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "TermCap.h"
#include "GP_Hotkey.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const char *CTermCap::TCFileName="TERMCAP.TXT";


const UINT CTermCap::uNEscTypes=8;
const char *CTermCap::cArrEscTypes[]={
		"TCET_BYTE","TCET_DIGIT","TCET_MOD256MINUSSP","TCET_MOD256","TCET_MOD90MINUSSP","TCET_MOD256MINUS1","TCET_MOD256MINUS31","TCET_HEXDIGIT","",
		};
const char *CTermCap::cArrEscTypesDescr[]={
#ifdef RUS
		"single byte","digit","multi byte - 32","multi byte","multi byte - 32 (mod90)","multi byte - 1 (mod256)","multi byte - 31 (mod256)","Hex digit","",
#else
		"single byte","digit","multi byte - 32","multi byte","multi byte - 32 (mod90)","multi byte - 1 (mod256)","multi byte - 31 (mod256)","Hex digit","",
#endif
		};
const DWORD CTermCap::uEscTypes[]={
		TCET_BYTE,	TCET_DIGIT,	TCET_MOD256MINUSSP,	TCET_MOD256,	TCET_MOD90MINUSSP, TCET_MOD256MINUS1, TCET_MOD256MINUS31,	TCET_HEXDIGIT, TCET_BYTE,	
		};

const UINT CTermCap::uNEscSubTypes=12;
const char *CTermCap::cArrEscSubTypes[]={
		"TCEST_IDWND","TCEST_IDSCR","TCEST_OBJTYPE","TCEST_Y","TCEST_Y2",
		"TCEST_X","TCEST_X2","TCEST_LENGTH","TCEST_COLOR","TCEST_COLOR_R",
		"TCEST_COLOR_G","TCEST_COLOR_B",
		};
const char *CTermCap::cArrEscSubTypesDescr[]={
#ifdef RUS
		"ID Window","ID Screen","ID Object","Coordinate Y","Coordinate Y2",
		"Coordinate X","Coordinate X2","Length","COLOR (256)","COLOR R",
		"COLOR G","COLOR B",
#else
		"ID Window","ID Screen","ID Object","Coordinate Y","Coordinate Y2",
		"Coordinate X","Coordinate X2","Length","COLOR (256)","COLOR R",
		"COLOR G","COLOR B",
#endif
		};
const DWORD CTermCap::uEscSubTypes[]={
		TCEST_IDWND,	TCEST_IDSCR,	TCEST_OBJTYPE,	TCEST_Y,	TCEST_Y2,
		TCEST_X,	TCEST_X2,	TCEST_LENGTH,	TCEST_COLOR,	TCEST_COLOR_R,
		TCEST_COLOR_G,	TCEST_COLOR_B,	
		};


const UINT CTermCap::uNKbdActions=7;
const char *CTermCap::cArrKbdActions[]={
		"NONE","UP","DOWN","LEFT","RIGHT",
		"DELETE","BACKSPACE",
		};
const char *CTermCap::cArrKbdActionsDescr[]={
		"NONE","UP","DOWN","LEFT","RIGHT",
		"DELETE","BACKSPACE",
		};
const DWORD CTermCap::uKbdActions[]={
		TCKA_NONE,TCKA_UP,TCKA_DOWN,TCKA_LEFT,TCKA_RIGHT,
		TCKA_DELETE,TCKA_BACKSPACE,
		};


CTermCap::CTermCap()
{
	dwVattrArrayMax=100;
	pdwVattrArray=new DWORD [dwVattrArrayMax*20];
	dwVattrArrayCount=0;
	ZeroMemory(pdwVattrArray, sizeof(DWORD)*dwVattrArrayMax*20);

	m_EscPoolLength=0;
	m_dwFindPos=0;
	FoundEsc=NULL;
	ClearVars();
	ClearEscPool();
	m_ArrTerminal=NULL;
	m_ArrEsc=NULL;
	m_ArrKbd=NULL;
	m_uMaxEscArr=0;
	m_uArrEscCount=0;
	ResetEscArray();
	m_uMaxKbdArr=0;
	m_uArrKbdCount=0;
	ResetKbdArray();
	m_uMaxTerminalArr=0;
	m_uArrTerminalCount=0;
	ResetTerminalArray();
	CurrentTerminal=NULL;
}

CTermCap::~CTermCap()
{
	DeleteEscArray();
	DeleteKbdArray();
	DeleteTerminalArray();
	dwVattrArrayMax=0;
	dwVattrArrayCount=0;
	if (pdwVattrArray) delete[] pdwVattrArray;
	pdwVattrArray=NULL;
}

DWORD CTermCap::Load(const char *fName)
{
	CurrentTerminal=NULL;
	ResetEscArray();
	ResetKbdArray();
	ResetTerminalArray();
	int *iUsedId=new int [10000];
	int i;
	for(i=0;i<10000;i++)
		iUsedId[i]=0;

	int nFile;
	for(nFile=0;nFile<10;nFile++)
	{
		CString csfName=fName?fName:CTermCap::TCFileName;
		if (nFile)
		{
			char tmps[5]={0,'.',0,};
			*tmps=nFile+'0';
			csfName.Replace(".",tmps);
		}
		FILE *fl=fopen(csfName,"rt");
		if (fl)
		{
			char *buff=new char [5500];
			char *fld[20];
			TERMCAPESCITEM escItem;
			TERMCAPKBDITEM kbdItem;
			TERMCAPTERMINALITEM terminalItem;

			while(fgets(buff,5000,fl))
			{
				char *pos=buff;
				int nFields=0;
				while(*pos && nFields<20)
				{
					fld[nFields++]=pos;
					while(*pos && *pos!='\t' && *pos!='\r' && *pos!='\n') pos++;
					if (*pos) *(pos++)=0;
				}
				for(i=nFields;i<20;i++)
					fld[i]="";

				if (nFields>2)
				{
					switch(atoi(fld[0]))
					{
					case 1: // TERMINAL
						if (*fld[1] && *fld[2] && *fld[3])
						{
							// TERMINAL fld1=1
							// TERMINAL fld2=TERMINAL Id
							// TERMINAL fld3=name
							// TERMINAL fld4=description
							ClearTerminalItem(terminalItem);
							terminalItem.dwTermId=atoi(fld[1]);
							terminalItem.dwFlags=atoi(fld[2]);
							terminalItem.TerminalName=fld[3];
							terminalItem.AlternateNames=fld[4];
							terminalItem.Description=fld[5];
							DeleteTerminalItems(terminalItem);
							PTERMCAPTERMINALITEM pItem=AddTerminalItem();
							if (pItem) *pItem=terminalItem;
						}
						break;
					case 2: // ESC
						if (*fld[1] && *fld[2]  && *fld[3] && *fld[6])
						{
							// ESC fld1=2
							// ESC fld2= TERMINAL Id
							// ESC fld3= PROC Id    (dwCommand)
							// ESC fld4= GROUP
							// ESC fld5= TermcapName
							// ESC fld6= Seq
							// ESC fld7= Description
							ClearEscItem(escItem);
							escItem.dwTermId=atoi(fld[1]);
							escItem.dwFlags=atoi(fld[2]);
							escItem.dwCommand=atoi(fld[3]);

							char *pos22=fld[6];
							int index=0;
							while(pos22 && *pos22 && index<TERMCAP_SEQLENGTH)
							{
								while(*pos22 && (*pos22<'0' || *pos22>'9')) pos22++;
								if (*pos22) escItem.seq.chType[index]=atoi(pos22);
								while(*pos22 && *pos22>='0' && *pos22<='9') pos22++;
								while(*pos22 && (*pos22<'0' || *pos22>'9')) pos22++;
								if (*pos22) escItem.seq.ch[index++]=atoi(pos22);
								while(*pos22 && *pos22>='0' && *pos22<='9') pos22++;
							}

							DeleteEscItems(escItem);

							if (index)
							{
								PTERMCAPESCITEM pItem=AddEscItem();
								if (pItem)
								{
									*pItem=escItem;
									pItem->seq.dwSeqLen=index;
									if (escItem.dwCommand>0 && escItem.dwCommand<10000) iUsedId[escItem.dwCommand]=1;
									pItem->TermcapName=fld[5];
									pItem->GroupName=fld[4];
									pItem->Description=fld[7];
								}
							}
						}
						break;
					case 3: // KEY
						if (*fld[1] && *fld[2] && *fld[3])
						{
							// KBD fld1=3
							// KBD fld2= TERMINAL Id
							// KBD fld3= VIRTUAL KEY
							// KBD fld4= Seq
							// KBD fld5= Description
							// KBD fld6= Action
							ClearKbdItem(kbdItem);
							kbdItem.dwTermId=atoi(fld[1]);
							kbdItem.dwFlags=atoi(fld[2]);
							kbdItem.dwVirtualKey=0;
							GP_HotKey::StringFromToHotKey(fld[3],kbdItem.dwVirtualKey);
							DeleteKbdItems(kbdItem);

							PTERMCAPKBDITEM pItem=AddKbdItem();
							if (pItem)
							{
								pItem->dwVirtualKey=kbdItem.dwVirtualKey;
								pItem->dwTermId=kbdItem.dwTermId;
								pItem->dwFlags=kbdItem.dwFlags;
								pItem->Seq=fld[4];
								pItem->Description=fld[5];
								pItem->csAction=fld[6];
							}
						}
						break;
					}
				}
			}
			// add missing items for old termcaps
			if (!iUsedId[2001])
			{
				PTERMCAPESCITEM pItem=AddEscItem();
				if (pItem)
				{
					pItem->dwCommand=2001;
					pItem->seq.dwSeqLen=1;
					pItem->seq.ch[0]=14;
					pItem->seq.chType[0]=0;
					pItem->TermcapName="GRON";
					pItem->Description="GRAPHIC ON";
					pItem->dwFlags=1;
				}
				pItem=AddEscItem();
				if (pItem)
				{
					pItem->dwCommand=2001;
					pItem->seq.dwSeqLen=4;
					pItem->seq.ch[0]=27;
					pItem->seq.chType[0]=0;
					pItem->seq.ch[1]=')';
					pItem->seq.chType[1]=0;
					pItem->seq.ch[2]='0';
					pItem->seq.chType[2]=0;
					pItem->seq.ch[3]=14;
					pItem->seq.chType[3]=0;
					pItem->TermcapName="GRON";
					pItem->Description="GRAPHIC ON";
					pItem->dwFlags=1;
				}
			}
			if (!iUsedId[2002])
			{
				PTERMCAPESCITEM pItem=AddEscItem();
				if (pItem)
				{
					pItem->dwCommand=2002;
					pItem->seq.dwSeqLen=1;
					pItem->seq.ch[0]=15;
					pItem->seq.chType[0]=0;
					pItem->TermcapName="GROFF";
					pItem->Description="GRAPHIC OFF";
					pItem->dwFlags=1;
				}
			}

			fclose(fl);
			delete[] buff;
		}
		else
			if (nFile==0)
			{
				char cTmp[1500];
				cTmp[GetCurrentDirectory(1400,cTmp)]=0;
				CString csTmp="Can't open termcap file \""+csfName+"\"\n Current folder is \"";
				csTmp+=cTmp;
				csTmp+=+"\"";
				AfxMessageBox(csTmp,MB_OK|MB_APPLMODAL|MB_ICONEXCLAMATION,0);
			}
	}
	if (m_uArrTerminalCount && m_ArrTerminal && *m_ArrTerminal)
			CurrentTerminal=*m_ArrTerminal;

	delete[] iUsedId;
	LoadTermCapVAttr("");
	return m_uArrEscCount;
}

BOOL CTermCap::Save(const char *fName)
{
	BOOL ret=FALSE;

	FILE *fl=fopen(fName?fName:CTermCap::TCFileName,"wt");
	if (fl)
	{
		if (m_ArrKbd)
		{
			DWORD oldNItems=m_uArrKbdCount;
			NormaliseKbd();
			if (oldNItems!=m_uArrKbdCount)
				AfxMessageBox("Some Keyboard items are present in GP_TERM terminal!");
		}
		if (m_ArrEsc)
		{
			DWORD oldNItems=m_uArrEscCount;
			NormaliseEsc();
			if (oldNItems!=m_uArrEscCount)
				AfxMessageBox("Some ESC items are present in GP_TERM terminal!");
		}

		char *buff=new char [5500];
		UINT i;

		if (m_ArrTerminal)
			for(i=0;i<m_uArrTerminalCount;i++)
				if (m_ArrTerminal[i])
					fprintf(fl,"1\t%d\t%d\t%s\t%s\t%s\n",m_ArrTerminal[i]->dwTermId,m_ArrTerminal[i]->dwFlags,(LPCSTR)m_ArrTerminal[i]->TerminalName,(LPCSTR)m_ArrTerminal[i]->AlternateNames,(LPCSTR)m_ArrTerminal[i]->Description);


		if (m_ArrEsc)
		{
			PTERMCAPESCITEM pItem=NULL;

			for(i=0;i<m_uArrEscCount;i++)
				if ((pItem=m_ArrEsc[i]))
				{
					fprintf(fl,"2\t%d\t%d\t%5.5d\t%s\t%s\t",
						pItem->dwTermId,
						pItem->dwFlags,
						pItem->dwCommand,
						(LPCSTR)pItem->GroupName,
						(LPCSTR)pItem->TermcapName);

					UINT j;
					for(j=0;j<pItem->seq.dwSeqLen;j++)
						fprintf(fl," %d %3.3d",pItem->seq.chType[j],pItem->seq.ch[j]);

					fprintf(fl,"\t%s\n",(LPCSTR)pItem->Description);
				}
		}

		if (m_ArrKbd)
			for(i=0;i<m_uArrKbdCount;i++)
				if (m_ArrKbd[i])
				{
					*buff=0;
					GP_HotKey::StringFromToHotKey(buff,m_ArrKbd[i]->dwVirtualKey);

					fprintf(fl,"3\t%d\t%d\t%s\t%s\t%s\t%s\n",
						m_ArrKbd[i]->dwTermId,
						m_ArrKbd[i]->dwFlags,
						buff,
						(LPCSTR)m_ArrKbd[i]->Seq,
						(LPCSTR)m_ArrKbd[i]->Description,
						(LPCSTR)m_ArrKbd[i]->csAction
						);
				}

		delete[] buff;
		fclose(fl);
	}
	SaveTermCapVAttr("");

	return ret;
}

PTERMCAPESCITEM CTermCap::AddEscItem()
{
	PTERMCAPESCITEM ret=NULL;
	if (m_ArrEsc==NULL) ResetEscArray();

	if (m_ArrEsc && m_uMaxEscArr)
	{
		while(m_uArrEscCount>=m_uMaxEscArr)
		{
			PTERMCAPESCITEM *tmpArr=new PTERMCAPESCITEM [m_uMaxEscArr+64];
			UINT i;
			for(i=0;i<m_uMaxEscArr;i++) tmpArr[i]=m_ArrEsc[i];
			m_uMaxEscArr+=64;
			for(;i<m_uMaxEscArr;i++) tmpArr[i]=NULL;

			delete[] m_ArrEsc;
			m_ArrEsc=tmpArr;
		}
		ret=m_ArrEsc[m_uArrEscCount]=new TERMCAPESCITEM;
		ClearEscItem(*m_ArrEsc[m_uArrEscCount++]);
	}
	return ret;
}

PTERMCAPKBDITEM CTermCap::AddKbdItem()
{
	PTERMCAPKBDITEM ret=NULL;
	if (m_ArrKbd==NULL) ResetKbdArray();

	if (m_ArrKbd && m_uMaxKbdArr)
	{
		while(m_uArrKbdCount>=m_uMaxKbdArr)
		{
			PTERMCAPKBDITEM *tmpArr=new PTERMCAPKBDITEM [m_uMaxKbdArr+64];
			UINT i;
			for(i=0;i<m_uMaxKbdArr;i++) tmpArr[i]=m_ArrKbd[i];
			m_uMaxKbdArr+=64;
			for(;i<m_uMaxKbdArr;i++) tmpArr[i]=NULL;

			delete[] m_ArrKbd;
			m_ArrKbd=tmpArr;
		}
		ret=m_ArrKbd[m_uArrKbdCount]=new TERMCAPKBDITEM;
		ClearKbdItem(*m_ArrKbd[m_uArrKbdCount++]);
	}
	return ret;
}

PTERMCAPTERMINALITEM CTermCap::AddTerminalItem()
{
	PTERMCAPTERMINALITEM ret=NULL;
	if (m_ArrTerminal==NULL) ResetTerminalArray();

	if (m_ArrTerminal && m_uMaxTerminalArr)
	{
		while(m_uArrTerminalCount>=m_uMaxTerminalArr)
		{
			PTERMCAPTERMINALITEM *tmpArr=new PTERMCAPTERMINALITEM [m_uMaxTerminalArr+64];
			UINT i;
			for(i=0;i<m_uMaxTerminalArr;i++) tmpArr[i]=m_ArrTerminal[i];
			m_uMaxTerminalArr+=64;
			for(;i<m_uMaxTerminalArr;i++) tmpArr[i]=NULL;

			delete[] m_ArrTerminal;
			m_ArrTerminal=tmpArr;
		}
		ret=m_ArrTerminal[m_uArrTerminalCount]=new TERMCAPTERMINALITEM;
		ClearTerminalItem(*m_ArrTerminal[m_uArrTerminalCount++]);
	}
	return ret;
}

UINT CTermCap::GetEscCount()
{
	return m_uArrEscCount;
}

UINT CTermCap::GetKbdCount()
{
	return m_uArrKbdCount;
}

UINT CTermCap::GetTerminalCount()
{
	return m_uArrTerminalCount;
}

UINT CTermCap::DeleteEscItem(PTERMCAPESCITEM iItem)
{
	if (m_uArrEscCount && m_ArrEsc)
	{
		if (iItem)
		{
			UINT i;
			for(i=0;i<m_uArrEscCount;i++)
				if (iItem==m_ArrEsc[i])
					DeleteEscItemByNum(i--);
		}
		else
		{
			UINT i;
			for(i=0;i<m_uArrEscCount;i++)
				if (m_ArrEsc[i]==NULL)
				{
					m_uArrEscCount--;
					UINT j;
					for(j=i;j<m_uArrEscCount;j++)
						m_ArrEsc[j]=m_ArrEsc[j+1];
					i--;
				}
		}
	}
	return m_uArrEscCount;
}

UINT CTermCap::DeleteKbdItem(PTERMCAPKBDITEM iItem)
{
	if (m_uArrKbdCount && m_ArrKbd)
	{
		if (iItem)
		{
			UINT i;
			for(i=0;i<m_uArrKbdCount;i++)
				if (iItem==m_ArrKbd[i])
					DeleteKbdItemByNum(i--);
		}
		else
		{
			UINT i;
			for(i=0;i<m_uArrKbdCount;i++)
				if (m_ArrKbd[i]==NULL)
				{
					m_uArrKbdCount--;
					UINT j;
					for(j=i;j<m_uArrKbdCount;j++)
						m_ArrKbd[j]=m_ArrKbd[j+1];
					i--;
				}
		}
	}
	return m_uArrKbdCount;
}

UINT CTermCap::DeleteTerminalItem(PTERMCAPTERMINALITEM iItem)
{
	if (m_uArrTerminalCount && m_ArrTerminal)
	{
		if (iItem)
		{
			UINT i;
			for(i=0;i<m_uArrTerminalCount;i++)
				if (iItem==m_ArrTerminal[i])
					DeleteTerminalItemByNum(i--);
		}
		else
		{
			UINT i;
			for(i=0;i<m_uArrTerminalCount;i++)
				if (m_ArrTerminal[i]==NULL)
				{
					m_uArrTerminalCount--;
					UINT j;
					for(j=i;j<m_uArrTerminalCount;j++)
						m_ArrTerminal[j]=m_ArrTerminal[j+1];
					i--;
				}
		}
	}
	return m_uArrTerminalCount;
}

UINT CTermCap::DeleteTerminalItemByNum(DWORD iItem)
{
	if (m_uArrTerminalCount && m_ArrTerminal && iItem<m_uArrTerminalCount && m_ArrTerminal[iItem])
	{
		delete m_ArrTerminal[iItem];
		m_ArrTerminal[iItem]=NULL;
		m_uArrTerminalCount--;
		UINT i;
		for(i=iItem;i<m_uArrTerminalCount;i++)
			m_ArrTerminal[i]=m_ArrTerminal[i+1];
		m_ArrTerminal[i]=NULL;
	}
	return m_uArrTerminalCount;
}

UINT CTermCap::DeleteKbdItemByNum(DWORD iItem)
{
	if (m_uArrKbdCount && m_ArrKbd && iItem<m_uArrKbdCount && m_ArrKbd[iItem])
	{
		delete m_ArrKbd[iItem];
		m_ArrKbd[iItem]=NULL;
		m_uArrKbdCount--;
		UINT i;
		for(i=iItem;i<m_uArrKbdCount;i++)
			m_ArrKbd[i]=m_ArrKbd[i+1];
		m_ArrKbd[i]=NULL;
	}
	return m_uArrKbdCount;
}

UINT CTermCap::DeleteEscItemByNum(DWORD iItem)
{
	if (m_uArrEscCount && m_ArrEsc && iItem<m_uArrEscCount && m_ArrEsc[iItem])
	{
		delete m_ArrEsc[iItem];
		m_ArrEsc[iItem]=NULL;
		m_uArrEscCount--;
		UINT i;
		for(i=iItem;i<m_uArrEscCount;i++)
			m_ArrEsc[i]=m_ArrEsc[i+1];
		m_ArrEsc[i]=NULL;
	}
	return m_uArrEscCount;
}

UINT CTermCap::DeleteEscItems(TERMCAPESCITEM &iTem)
{
	UINT i;
	for(i=0;i<m_uArrEscCount;i++)
		if (m_ArrEsc[i])
		{
			BOOL del=TRUE;
			if (del && iTem.dwCommand &&  iTem.dwCommand!=m_ArrEsc[i]->dwCommand) del=FALSE;
			if (del && iTem.dwTermId!=-1 &&  iTem.dwTermId!=m_ArrEsc[i]->dwTermId) del=FALSE;
			if (del && iTem.Description!="" &&  iTem.Description!=m_ArrEsc[i]->Description) del=FALSE;
			if (del && iTem.TermcapName!="" &&  iTem.TermcapName!=m_ArrEsc[i]->TermcapName) del=FALSE;
			if (del && iTem.GroupName!="" &&  iTem.GroupName!=m_ArrEsc[i]->GroupName) del=FALSE;
			if (del && iTem.seq.ch[0])
			{
				int j;
				for(j=0;j<TERMCAP_SEQLENGTH && del;j++)
					del=(iTem.seq.ch[j]==m_ArrEsc[i]->seq.ch[j] && iTem.seq.chType[j]==m_ArrEsc[i]->seq.chType[j]);
			}
			if (del) DeleteEscItem(m_ArrEsc[i--]);
		}
	return m_uArrEscCount;
}

UINT CTermCap::DeleteKbdItems(TERMCAPKBDITEM &iTem)
{
	UINT i;
	for(i=0;i<m_uArrKbdCount;i++)
		if (m_ArrKbd[i])
		{
			BOOL del=TRUE;
			if (del && iTem.dwVirtualKey &&  iTem.dwVirtualKey!=m_ArrKbd[i]->dwVirtualKey) del=FALSE;
			if (del && iTem.dwTermId!=m_ArrKbd[i]->dwTermId) del=FALSE;
			if (del) DeleteKbdItem(m_ArrKbd[i--]);
		}
	return m_uArrKbdCount;
}

UINT CTermCap::DeleteTerminalItems(TERMCAPTERMINALITEM &iTem)
{
	UINT i;
	for(i=0;i<m_uArrTerminalCount;i++)
		if (m_ArrTerminal[i])
		{
			BOOL del=TRUE;
			if (del && iTem.dwTermId!=-1 &&  iTem.dwTermId!=m_ArrTerminal[i]->dwTermId) del=FALSE;
			if (del && iTem.Description!="" &&  iTem.Description!=m_ArrTerminal[i]->Description) del=FALSE;
			if (del && iTem.TerminalName!="" &&  iTem.TerminalName!=m_ArrTerminal[i]->TerminalName) del=FALSE;
			if (del && iTem.AlternateNames!="" &&  m_ArrTerminal[i]->AlternateNames.Find(iTem.AlternateNames,0)>=0) del=FALSE;
			if (del) DeleteTerminalItem(m_ArrTerminal[i--]);
		}
	return m_uArrTerminalCount;
}

void CTermCap::DeleteEscArray()
{
	if (m_ArrEsc)
	{
		ResetEscArray();
		m_uMaxEscArr=0;
		delete[] m_ArrEsc;
		m_ArrEsc=NULL;
	}
}

void CTermCap::DeleteKbdArray()
{
	if (m_ArrKbd)
	{
		ResetKbdArray();
		m_uMaxKbdArr=0;
		delete[] m_ArrKbd;
		m_ArrKbd=NULL;
	}
}

void CTermCap::DeleteTerminalArray()
{
	if (m_ArrTerminal)
	{
		ResetTerminalArray();
		m_uMaxTerminalArr=0;
		delete[] m_ArrTerminal;
		m_ArrTerminal=NULL;
	}
}

void CTermCap::ResetEscArray()
{
	if (m_ArrEsc)
	{
		while(m_uArrEscCount--)
		{
			if (m_ArrEsc[m_uArrEscCount]) delete m_ArrEsc[m_uArrEscCount];
			m_ArrEsc[m_uArrEscCount]=NULL;
		}
	}
	else
	{
		if (m_uMaxEscArr<10 || m_uMaxEscArr>10000) m_uMaxEscArr=500;
		m_ArrEsc=new PTERMCAPESCITEM [m_uMaxEscArr];
		UINT i;
		for(i=0;i<m_uMaxEscArr;i++) m_ArrEsc[i]=NULL;
	}
	m_uArrEscCount=0;
}

void CTermCap::ResetKbdArray()
{
	if (m_ArrKbd)
	{
		while(m_uArrKbdCount--)
		{
			if (m_ArrKbd[m_uArrKbdCount]) delete m_ArrKbd[m_uArrKbdCount];
			m_ArrKbd[m_uArrKbdCount]=NULL;
		}
	}
	else
	{
		if (m_uMaxKbdArr<10 || m_uMaxKbdArr>10000) m_uMaxKbdArr=500;
		m_ArrKbd=new PTERMCAPKBDITEM [m_uMaxKbdArr];
		UINT i;
		for(i=0;i<m_uMaxKbdArr;i++) m_ArrKbd[i]=NULL;
	}
	m_uArrKbdCount=0;
}

void CTermCap::ResetTerminalArray()
{
	CurrentTerminal=NULL;

	if (m_ArrTerminal)
	{
		while(m_uArrTerminalCount--)
		{
			if (m_ArrTerminal[m_uArrTerminalCount]) delete m_ArrTerminal[m_uArrTerminalCount];
			m_ArrTerminal[m_uArrTerminalCount]=NULL;
		}
	}
	else
	{
		if (m_uMaxTerminalArr<10 || m_uMaxTerminalArr>10000) m_uMaxTerminalArr=500;
		m_ArrTerminal=new PTERMCAPTERMINALITEM [m_uMaxTerminalArr];
		UINT i;
		for(i=0;i<m_uMaxTerminalArr;i++) m_ArrTerminal[i]=NULL;
	}
	m_uArrTerminalCount=0;
}

void CTermCap::ClearEscItem(TERMCAPESCITEM & iTem)
{
	iTem.Description="";
	iTem.dwCommand=0;
	iTem.dwTermId=0;
	iTem.dwFlags=0;
	iTem.dwSearchFlags=0;
	iTem.GroupName="";
	iTem.TermcapName="";
	ZeroMemory(&(iTem.seq), sizeof(iTem.seq));

}

void CTermCap::ClearKbdItem(TERMCAPKBDITEM & iTem)
{
	iTem.Description="";
	iTem.dwTermId=0;
	iTem.dwFlags=0;
	iTem.dwVirtualKey=0;
	iTem.Seq="";
}

void CTermCap::ClearTerminalItem(TERMCAPTERMINALITEM & iTem)
{
	iTem.Description="";
	iTem.dwTermId=0;
	iTem.dwFlags=0;
	iTem.TerminalName="";
	iTem.AlternateNames="";
}

CTermCap & CTermCap::operator= (const CTermCap &iCTermCap)
{
	if (this!=&iCTermCap && &iCTermCap)
	{
		ResetEscArray();
		ResetKbdArray();
		ResetTerminalArray();

		UINT i=0;

		if (iCTermCap.m_ArrEsc)
			for(i=0;i<iCTermCap.m_uArrEscCount ;i++)
			{
				PTERMCAPESCITEM pItem=iCTermCap.m_ArrEsc[i];
				if (pItem)
				{
					PTERMCAPESCITEM pItemNew=AddEscItem();
					if (pItemNew) *pItemNew=*pItem;
				}
			}

		if (iCTermCap.m_ArrTerminal)
			for(i=0;i<iCTermCap.m_uArrTerminalCount ;i++)
			{
				PTERMCAPTERMINALITEM pItem=iCTermCap.m_ArrTerminal[i];
				if (pItem)
				{
					PTERMCAPTERMINALITEM pItemNew=AddTerminalItem();
					if (pItemNew) *pItemNew=*pItem;
				}
			}

		if (iCTermCap.m_ArrKbd)
			for(i=0;i<iCTermCap.m_uArrKbdCount ;i++)
			{
				PTERMCAPKBDITEM pItem=iCTermCap.m_ArrKbd[i];
				if (pItem)
				{
					PTERMCAPKBDITEM pItemNew=AddKbdItem();
					if (pItemNew) *pItemNew=*pItem;
				}
			}
	}
	return *this;
}

DWORD CTermCap::GetCurrentTerminalId()
{
	return CurrentTerminal?CurrentTerminal->dwTermId:(DWORD)-1;
}

PTERMCAPTERMINALITEM CTermCap::GetCurrentTerminal()
{
	return CurrentTerminal;
}

DWORD CTermCap::SetCurrentTerminalId(DWORD dwNewId)
{
	DWORD ret=GetCurrentTerminalId();
	DWORD num=GetTerminalNumById(dwNewId);
	if (num<m_uArrTerminalCount && m_ArrTerminal && m_ArrTerminal[num])
		CurrentTerminal=m_ArrTerminal[num];
	else ret=(DWORD)(-1);
	return ret;
}

DWORD CTermCap::GetTerminalNumById(DWORD dwId)
{
	DWORD ret=(DWORD)(-1);
	UINT i;
	if (m_ArrTerminal)
		for(i=0;i<m_uArrTerminalCount && ret==(DWORD)(-1);i++)
			if (m_ArrTerminal[i] && m_ArrTerminal[i]->dwTermId==dwId)
				ret=i;

	return ret;
}

const char * CTermCap::GetTerminalNameById(DWORD dwId)
{
	const char *ret="";
	UINT i;
	if (m_ArrTerminal)
		for(i=0;i<m_uArrTerminalCount && *ret==0;i++)
			if (m_ArrTerminal[i] && m_ArrTerminal[i]->dwTermId==dwId)
				ret=m_ArrTerminal[i]->TerminalName;

	return *ret==0?"UNKNOWN":ret;
}

UINT CTermCap::GetTerminalIdByName(const char *iName)
{
	UINT ret=(CurrentTerminal)?CurrentTerminal->dwTermId:0;
	if (m_ArrTerminal)
	{
		UINT i;
		for(i=0;i<m_uArrTerminalCount;i++)
			if (m_ArrTerminal[i] && m_ArrTerminal[i]->TerminalName==iName)
			{
				ret=m_ArrTerminal[i]->dwTermId;
				break;
			}
		if (i>=m_uArrTerminalCount)
		{
			for(i=0;i<m_uArrTerminalCount;i++)
				if (m_ArrTerminal[i] && m_ArrTerminal[i]->TerminalName.Find(iName,0)>=0)
				{
					ret=m_ArrTerminal[i]->dwTermId;
					break;
				}
		}
	}
	return ret;
}


BOOL CTermCap::ChangeTerminalId(DWORD iOldId, DWORD iNewId)
{
	BOOL ret=FALSE;
	if (GetTerminalNumById(iOldId)<m_uArrTerminalCount && GetTerminalNumById(iNewId)>=m_uArrTerminalCount)
	{
		UINT i;
		ret=TRUE;
		if (m_ArrTerminal)
			for(i=0;i<m_uArrTerminalCount;i++)
				if (m_ArrTerminal[i] && m_ArrTerminal[i]->dwTermId==iOldId)
					m_ArrTerminal[i]->dwTermId=iNewId;

		if (m_ArrKbd)
			for(i=0;i<m_uArrKbdCount;i++)
				if (m_ArrKbd[i] && m_ArrKbd[i]->dwTermId==iOldId)
					m_ArrKbd[i]->dwTermId=iNewId;

		if (m_ArrEsc)
			for(i=0;i<m_uArrEscCount;i++)
				if (m_ArrEsc[i] && m_ArrEsc[i]->dwTermId==iOldId)
					m_ArrEsc[i]->dwTermId=iNewId;

	}
	return ret;
}

BOOL CTermCap::GetFileName(CString &iInitDir, CString &iFileName, DWORD iFlags, HWND iHWNDPARENT)
{
	BOOL ret=FALSE;
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
	opf.hwndOwner=GPC.m_hViewWnd;
	opf.lpstrFile = new char [500];
	strcpy(opf.lpstrFile,iFileName);
	opf.nMaxFile =490;

	#ifdef RUS
		opf.lpstrFilter="Текстовые файлы (*.txt)\x0*.txt\x0Все файлы\x0*.*\x0";
		opf.lpstrTitle="Выбор файла описания TERMCAP";
	#else
		opf.lpstrFilter="Text Files (*.txt)\x0*.txt\x0 All Files\x0*.*\x0";
		opf.lpstrTitle="Select TERMCAP File";
	#endif
	opf.lpstrDefExt="TXT";
	opf.hwndOwner=iHWNDPARENT;

	if (iInitDir!="")
		opf.lpstrInitialDir=(LPCSTR)iInitDir;

	opf.Flags =OFN_DONTADDTORECENT|OFN_CREATEPROMPT|OFN_ENABLESIZING|OFN_EXPLORER|OFN_NOCHANGEDIR|OFN_SHOWHELP|OFN_LONGNAMES|OFN_PATHMUSTEXIST;

	switch((iFlags&0x0001))
	{
	case 0:
		if ((ret=GetOpenFileName(&opf)))
			iFileName=opf.lpstrFile;
		break;
	case 1:
		opf.Flags|=OFN_NOREADONLYRETURN|OFN_OVERWRITEPROMPT;
		if ((ret=GetSaveFileName(&opf)))
			iFileName=opf.lpstrFile;
		break;
	}
	delete[] opf.lpstrFile;
	return ret;
}

BOOL CTermCap::DeleteTerminal(DWORD dwTermId)
{
	BOOL ret=FALSE;
	if (dwTermId)
	{
		UINT i;
		ret=TRUE;
		if (m_ArrTerminal)
			for(i=0;i<m_uArrTerminalCount;i++)
				if (m_ArrTerminal[i] && m_ArrTerminal[i]->dwTermId==dwTermId)
					DeleteTerminalItemByNum(i--);

		if (m_ArrKbd)
			for(i=0;i<m_uArrKbdCount;i++)
				if (m_ArrKbd[i] && m_ArrKbd[i]->dwTermId==dwTermId)
					DeleteKbdItemByNum(i--);

		if (m_ArrEsc)
			for(i=0;i<m_uArrEscCount;i++)
				if (m_ArrEsc[i] && m_ArrEsc[i]->dwTermId==dwTermId)
					DeleteEscItemByNum(i--);
	}
	return ret;
}

DWORD CTermCap::GetVacTerminalId()
{
	DWORD ret=1;
	UINT i;
	if (m_ArrTerminal)
	{
		char *idflag=new char [m_uArrTerminalCount+50];
		for(i=0;i<m_uArrTerminalCount;i++)
			idflag[i]=0;

		if (m_ArrTerminal)
			for(i=0;i<m_uArrTerminalCount;i++)
				if (m_ArrTerminal[i] && m_ArrTerminal[i]->dwTermId<m_uArrTerminalCount)
					idflag[m_ArrTerminal[i]->dwTermId]=1;

		for(ret=1;ret<m_uArrTerminalCount && idflag[ret];ret++);

		delete[] idflag;
	}
	return ret;
}

UINT CTermCap::CopyKbd(DWORD SrcTermId, DWORD DstTermId)
{
	if (DstTermId && m_ArrKbd && SrcTermId!=DstTermId)
	{
		UINT i;
		for(i=0;i<m_uArrKbdCount;i++)
			if (m_ArrKbd[i] && m_ArrKbd[i]->dwTermId==SrcTermId)
			{
				PTERMCAPKBDITEM newItem=CTermCap::AddKbdItem();
				if (newItem)
				{
					*newItem=*m_ArrKbd[i];
					newItem->dwTermId=DstTermId;
				}
			}
		NormaliseKbd();
	}
	return m_uArrKbdCount;
}

UINT CTermCap::NormaliseKbd()
{
	UINT i;
	for(i=0;i<m_uArrKbdCount;i++)
		if (m_ArrKbd[i])
			if (m_ArrKbd[i]->dwVirtualKey)
			{
				UINT j;
				for(j=i+1;j<m_uArrKbdCount;j++)
					if (m_ArrKbd[j] && m_ArrKbd[i]->dwVirtualKey==m_ArrKbd[j]->dwVirtualKey)
					{
						if (m_ArrKbd[j]->dwTermId==m_ArrKbd[i]->dwTermId)
							DeleteKbdItemByNum(j--);
						else
							if (m_ArrKbd[j]->Seq==m_ArrKbd[i]->Seq && m_ArrKbd[j]->dwFlags==m_ArrKbd[i]->dwFlags)
								if (m_ArrKbd[i]->dwTermId==0)
									DeleteKbdItemByNum(j--);
								else
								if (m_ArrKbd[j]->dwTermId==0)
								{DeleteKbdItemByNum(i--);break;}
					}
			}
			else DeleteKbdItemByNum(i--);
	return m_uArrKbdCount;
}

UINT CTermCap::NormaliseEsc()
{
	UINT i;
	for(i=0;i<m_uArrEscCount;i++)
		if (m_ArrEsc[i])
		{
			UINT j;
			for(j=i+1;j<m_uArrEscCount;j++)
				if (m_ArrEsc[j] && CompareEscSeq(&m_ArrEsc[i]->seq,&m_ArrEsc[j]->seq)==0)
				{
					if (m_ArrEsc[j]->dwTermId==m_ArrEsc[i]->dwTermId)
						DeleteEscItemByNum(j--);
					else
						if (m_ArrEsc[i]->dwTermId==0)
							DeleteEscItemByNum(j--);
						else
							if (m_ArrEsc[j]->dwTermId==0)
							{
								DeleteEscItemByNum(i--);
								break;
							}
				}
		}
	return m_uArrEscCount;
}

int CTermCap::CompareEscSeq(const PTERMCAPITEMSEQ s1, const PTERMCAPITEMSEQ s2)
{
	int ret=0;
	if (s1 && s2)
	{
		if (s1->dwSeqLen && s2->dwSeqLen)
		{
			DWORD i;
			for(i=0;i<s1->dwSeqLen && i<s2->dwSeqLen && s1->chType[i]==s2->chType[i] && s1->ch[i]==s2->ch[i];i++);
			if (i==s1->dwSeqLen || i==s2->dwSeqLen) 
				ret=s1->dwSeqLen-s2->dwSeqLen;
			else
				if (s1->chType[i]!=s2->chType[i]) 
					ret=s1->chType[i]-s2->chType[i];
				else
					ret=s1->ch[i]-s2->ch[i];
		}
		else
			ret=s1->dwSeqLen-s2->dwSeqLen;
	}
	else ret=s1?1:s2?-1:0;

	return ret;
}

PTERMCAPESCITEM CTermCap::TranslateFoundEsc()
{
	ClearVars();
	if (FoundEsc)
	{
		UINT i;
		_TERMCAPESCVARS varsDelta={0};
		for(i=0;i<FoundEsc->seq.dwSeqLen;i++)
			switch(FoundEsc->seq.chType[i])
			{
			case TCET_DIGIT:
			case TCET_HEXDIGIT:
			case TCET_MOD256MINUSSP:
			case TCET_MOD256MINUS31:
			case TCET_MOD256:
			case TCET_MOD90MINUSSP:
			case TCET_MOD256MINUS1:
				{
					int mul=0;
					int intDelta2=0;
					int tmpVal=EscPool[i];
					switch(FoundEsc->seq.chType[i])
					{
					case TCET_DIGIT:			mul=10;		tmpVal-='0'; 	break;
					case TCET_HEXDIGIT:			mul=16;
						if (tmpVal>='A' && tmpVal<='F' ) tmpVal-=('A'-10); 
						else
						if (tmpVal>='a' && tmpVal<='f' ) tmpVal-=('a'-10); 
						else
						if (tmpVal>='0' && tmpVal<='9' ) tmpVal-='0'; 
						else				tmpVal=0;	
						break;
					case TCET_MOD256MINUSSP:	mul=256;	tmpVal-=' ';	break;
					case TCET_MOD256MINUS31:	mul=256;	tmpVal-=31;	break;
					case TCET_MOD256:			mul=256;	tmpVal-=0;	break;
					case TCET_MOD90MINUSSP:		mul=90;		tmpVal-=' ';	break;
					case TCET_MOD256MINUS1:		mul=10;		tmpVal-='0';	intDelta2=-1;	break;
					}


					switch(FoundEsc->seq.ch[i])
					{
					case TCEST_IDWND:
						m_Vars.IdWnd=m_Vars.IdWnd*mul+tmpVal;
						if (intDelta2!=0) varsDelta.IdWnd=intDelta2;
						break;
					case TCEST_IDSCR:
						m_Vars.IdScr=m_Vars.IdScr*mul+tmpVal;
						if (intDelta2!=0) varsDelta.IdScr=intDelta2;
						break;
					case TCEST_OBJTYPE:
						m_Vars.typeUnit=m_Vars.typeUnit*mul+tmpVal;
						if (intDelta2!=0) varsDelta.typeUnit=intDelta2;
						break;
					case TCEST_Y:
						m_Vars.Pos_Y=m_Vars.Pos_Y*mul+tmpVal;
						if (intDelta2!=0) varsDelta.Pos_Y=intDelta2;
						break;
					case TCEST_X:
						m_Vars.Pos_X=m_Vars.Pos_X*mul+tmpVal;
						if (intDelta2!=0) varsDelta.Pos_X=intDelta2;
						break;
					case TCEST_X2:
						m_Vars.Pos_X2=m_Vars.Pos_X2*mul+tmpVal;
						if (intDelta2!=0) varsDelta.Pos_X2=intDelta2;
						break;
					case TCEST_Y2:
						m_Vars.Pos_Y2=m_Vars.Pos_Y2*mul+tmpVal;
						if (intDelta2!=0) varsDelta.Pos_Y2=intDelta2;
						break;
					case TCEST_COLOR:
						m_Vars.ClrRef=m_Vars.ClrRef*mul+tmpVal;
						if (intDelta2!=0) varsDelta.ClrRef=intDelta2;
						break;
					case TCEST_LENGTH:
						m_Vars.Length=m_Vars.Length*mul+tmpVal;
						if (intDelta2!=0) varsDelta.Length=intDelta2;
						break;
					case TCEST_COLOR_R:
						m_Vars.R=m_Vars.R*mul+tmpVal;
						if (intDelta2!=0) varsDelta.R=intDelta2;
						break;
					case TCEST_COLOR_G:
						m_Vars.G=m_Vars.G*mul+tmpVal;
						if (intDelta2!=0) varsDelta.G=intDelta2;
						break;
					case TCEST_COLOR_B:
						m_Vars.B=m_Vars.B*mul+tmpVal;
						if (intDelta2!=0) varsDelta.B=intDelta2;
						break;
					default:
						m_Vars.Unknown=m_Vars.Unknown*mul+tmpVal;
						break;
					}
				}
				break;
			case TCET_BYTE:
			default:
				break;
			}

		m_Vars.IdWnd+=varsDelta.IdWnd;
		m_Vars.IdScr+=varsDelta.IdScr;
		m_Vars.typeUnit+=varsDelta.typeUnit;
		m_Vars.Length+=varsDelta.Length;
		m_Vars.Pos_Y+=varsDelta.Pos_Y;
		m_Vars.Pos_Y2+=varsDelta.Pos_Y2;
		m_Vars.Pos_X+=varsDelta.Pos_X;
		m_Vars.Pos_X2+=varsDelta.Pos_X2;
		m_Vars.R+=varsDelta.R;
		m_Vars.G+=varsDelta.G;
		m_Vars.B+=varsDelta.B;
		m_Vars.ClrRef+=varsDelta.ClrRef;
		m_Vars.Unknown+=varsDelta.Unknown;


	}
	return FoundEsc;
}

PTERMCAPESCITEM CTermCap::GetFoundEsc()
{
	return 	FoundEsc;
}

void CTermCap::ClearVars()
{
	ZeroMemory(&m_Vars, sizeof(TERMCAPESCVARS));
}

const char * CTermCap::GetEscPool()
{
	return EscPool;
}

UINT CTermCap::GetEscPoolLen()
{
	return m_EscPoolLength;
}

void CTermCap::ClearEscPool()
{
	ZeroMemory(&EscPool, sizeof(TERMCAPESCVARS));
	m_EscPoolLength=0;
	m_dwFindPos=0;
}

int CTermCap::AddByteToEscPool(BYTE iByte)
{
	if (m_EscPoolLength<TERMCAP_ESCPOOLLENGTH)
		EscPool[m_EscPoolLength++]=iByte;
	return FindEscSequense();
}

int CTermCap::AddArrayToEscPool(const BYTE *iByte, DWORD iLen)
{
	int ret=-11;
	while(m_EscPoolLength<TERMCAP_ESCPOOLLENGTH && iLen--)
	{
		EscPool[m_EscPoolLength++]=*(iByte++);
		if (ret==-11)
		{
			int tmpret=FindEscSequense();
			if (tmpret==-1 || tmpret>=0) ret=tmpret;
		}
	}
	return ret;
}


int CTermCap::FindEscSequense()
{
	int  ret=-1;
	DWORD m_CommTerminalTypeId=0;
	if (CurrentTerminal)
		m_CommTerminalTypeId=CurrentTerminal->dwTermId;

	if (m_ArrEsc && m_EscPoolLength)
	{
		// -1 нет
		// -2 может быть
		// -3 есть в 0
		// >=0  нашлось
		PTERMCAPESCITEM pEsc;
		UINT i;
		m_dwFindPos=0;
		if (m_EscPoolLength==1)
		{
			FoundEsc=NULL;
			for(i=0;i<m_uArrEscCount && ret<3;i++)
				if ((pEsc=m_ArrEsc[i]))
				{
					if ((pEsc->dwTermId==m_CommTerminalTypeId || pEsc->dwTermId==0) && pEsc->seq.dwSeqLen && (pEsc->dwFlags&1)==1)
						m_ArrEsc[i]->dwSearchFlags=1;
					else
						m_ArrEsc[i]->dwSearchFlags=0;
				}
		}

		int i_ChIndex=m_EscPoolLength-1;
		unsigned char cmpchar=EscPool[i_ChIndex];
		int m_OK;
		for(i=0;i<m_uArrEscCount && ret<0;i++)
		{
			pEsc=m_ArrEsc[i];
			if (pEsc && pEsc->dwSearchFlags)
			{
				m_OK=0;
				switch(pEsc->seq.chType[i_ChIndex])
				{
				case TCET_DIGIT:
				case TCET_MOD256MINUS1:
					if (cmpchar>='0' && cmpchar<='9') m_OK=1;
					break;
				case TCET_HEXDIGIT:
					if (
						(cmpchar>='0' && cmpchar<='9') || 
						(cmpchar>='A' && cmpchar<='F') || 
						(cmpchar>='a' && cmpchar<='f')) 
								m_OK=1;
					break;
				case TCET_MOD90MINUSSP:
				case TCET_MOD256MINUSSP:
				case TCET_MOD256MINUS31:
					if (cmpchar>=' ') m_OK=1;
					break;
				case TCET_MOD256:
					m_OK=1;
					break;
				case TCET_BYTE:
				default:
					if (cmpchar==pEsc->seq.ch[i_ChIndex]) m_OK=1;
					break;
				}

				if (m_OK)
				{
					if (pEsc->dwTermId==m_CommTerminalTypeId)
					{
						if (m_EscPoolLength==pEsc->seq.dwSeqLen) m_dwFindPos=i,ret=0;
							else ret=-2;
					}
					else
						if (m_EscPoolLength==pEsc->seq.dwSeqLen) m_dwFindPos=i,ret=-3;
							else ret=-2;
				}
				else pEsc->dwSearchFlags=0;
			}
		}

		if (ret==-3 || ret==0)
			ret=(FoundEsc=m_ArrEsc[m_dwFindPos])->dwCommand;
	}
	return ret;
}


DWORD CTermCap::FillComboTerminalType(HWND ihWnd, DWORD iSelId)
{
	UINT ret=0;
	if (ihWnd)
	{
		::SendMessage(ihWnd,CB_RESETCONTENT,0,0);

		if (m_ArrTerminal)
		{
			int index=0;
			UINT i;
			for(i=0;i<m_uArrTerminalCount;i++)
				if (m_ArrTerminal[i])
				{
					if (m_ArrTerminal[i]->TerminalName!="")
					{
						index=::SendMessage(ihWnd,CB_ADDSTRING,0,(LPARAM)((LPCSTR)m_ArrTerminal[i]->TerminalName));
						if (index!=CB_ERR)
						{
							ret++;
							::SendMessage(ihWnd,CB_SETITEMDATA,index,m_ArrTerminal[i]->dwTermId);
							if (iSelId!=-1)
							{
								if (iSelId==m_ArrTerminal[i]->dwTermId)
									::SendMessage(ihWnd,CB_SETCURSEL,index,0);
							}
							else
							if (CurrentTerminal && CurrentTerminal->dwTermId==m_ArrTerminal[i]->dwTermId)
								::SendMessage(ihWnd,CB_SETCURSEL,index,0);
						}
					}
				}
		}
	}

	return ret;
}

DWORD CTermCap::SelectTerminal(int x, int y)
{
	UINT i=0;
	DWORD ret=DWORD_MINUS_ONE;
	HMENU m_PopupMenu;
	DWORD curId=DWORD_MINUS_TWO;
	if (CurrentTerminal) curId=CurrentTerminal->dwTermId;

	if (m_ArrTerminal)
		if (m_uArrTerminalCount==1)
			ret=m_ArrTerminal[0]->dwTermId;
		else
		if (m_uArrTerminalCount==2)
		{
			for(i=0;i<m_uArrTerminalCount && ret==DWORD_MINUS_ONE;i++)
				if (m_ArrTerminal[i] && m_ArrTerminal[i]->dwTermId!=curId)
					ret=m_ArrTerminal[i]->dwTermId;
		}
		else
		{
			m_PopupMenu=::CreatePopupMenu();
			if (m_PopupMenu)
			{
				MENUITEMINFO mi={0};
				mi.cbSize=sizeofMENUITEMINFO;
				#ifdef W_95
					mi.fType=MFT_STRING;
					mi.fMask=MIIM_TYPE|MIIM_ID;
				#else
					#ifdef W_NT
						mi.fType=MFT_STRING;
						mi.fMask=MIIM_TYPE|MIIM_ID;
					#else
						mi.fMask=MIIM_STRING|MIIM_ID;
					#endif
				#endif

				for(i=0;i<m_uArrTerminalCount;i++)
					if (m_ArrTerminal[i] && m_ArrTerminal[i]->dwTermId!=curId)
					{
						mi.dwTypeData=(char *)(LPCSTR)m_ArrTerminal[i]->TerminalName;
						mi.cch=(int)strlen((LPCSTR)mi.dwTypeData);
						mi.wID=m_ArrTerminal[i]->dwTermId+0x1000;
						::InsertMenuItem(m_PopupMenu,(DWORD)i,TRUE,&mi);
					}
				ret=::TrackPopupMenu(m_PopupMenu,TPM_RIGHTBUTTON|TPM_BOTTOMALIGN|TPM_LEFTALIGN|TPM_HORNEGANIMATION|TPM_RETURNCMD,x,y,0,GPC.m_hViewWnd,NULL);
				if (ret==0) ret=DWORD_MINUS_ONE;
				else ret-=0x1000;
				::DestroyMenu(m_PopupMenu);
			}
		}
	return ret;
}

const PTERMCAPESCITEM CTermCap::GetEscItemById(DWORD dwID, DWORD dwTermID)
{
	PTERMCAPESCITEM ret=NULL;
	PTERMCAPESCITEM pEsc=NULL;
	PTERMCAPESCITEM pEsc1=NULL;
	UINT i;
	for(i=0;i<m_uArrEscCount && !ret;i++)
		if ((pEsc=m_ArrEsc[i]) && (pEsc->dwTermId==dwTermID || pEsc->dwTermId==0) && pEsc->dwCommand==dwID)
		{
			pEsc1=pEsc;
			if (pEsc->dwTermId==dwTermID) ret=pEsc;
		}
	
	if (!ret) ret=pEsc1;

	return ret;
}

DWORD CTermCap::LoadTermCapVAttr(const char *iName)
{
	if (!dwVattrArrayMax || dwVattrArrayMax>100)
	{
		dwVattrArrayMax=100;
		if (pdwVattrArray) delete[] pdwVattrArray;
		pdwVattrArray=new DWORD [dwVattrArrayMax*20];
	}
	ZeroMemory(pdwVattrArray, sizeof(DWORD)*dwVattrArrayMax*20);
	dwVattrArrayCount=0;
	DWORD cmdList[]={
		100,101,102,103,104,105,106,107,110,111,
		112,113,114,115,116,117,117,118,120,121,
		122,123,124,125,126,127,128,129,130,131,
		2001,2002,111111,
	};


	for(dwVattrArrayCount=0;dwVattrArrayCount<33;dwVattrArrayCount++)
		pdwVattrArray[dwVattrArrayCount*20+2]=pdwVattrArray[dwVattrArrayCount*20]=cmdList[dwVattrArrayCount];


	FILE *tmp=fopen((iName && *iName)?iName:"termcapVA.txt","rt");
	if (tmp)
	{
		dwVattrArrayCount=0;
		char tmps[1000];
		while(fgets(tmps,990,tmp))
		{
			if (dwVattrArrayCount>=dwVattrArrayMax-1)
			{
				DWORD *tmpDword=new DWORD [(dwVattrArrayMax+100)*20];
				ZeroMemory(tmpDword, sizeof(DWORD)*(dwVattrArrayMax+100)*20);
				if (pdwVattrArray)
				{
					CopyMemory(tmpDword,pdwVattrArray,20*dwVattrArrayMax*sizeof(DWORD));
					delete[] pdwVattrArray;
				}
				dwVattrArrayMax+=100;
				pdwVattrArray=tmpDword;
			}
			char *pos=tmps;
			int n=0;
			if (atoi(pos))
			{
				while(pos && *pos && n<20)
				{
					pdwVattrArray[dwVattrArrayCount*20+n++]=atoi(pos);
					while(*pos && *(pos++)!=',');
					while(*pos && (*pos<'0' || *pos>'9')) pos++;
				}
				dwVattrArrayCount++;
			}
		}
		fclose(tmp);
	}

	
	return dwVattrArrayCount;
}

DWORD CTermCap::SaveTermCapVAttr(const char *iName)
{
	DWORD ret=0;
	if (pdwVattrArray)
	{
		FILE *tmp=fopen((iName && *iName)?iName:"termcapVA.txt","wt");
		if (tmp)
		{
			for(ret=0;ret<dwVattrArrayCount;ret++)
			{
				int i;
				for(i=0;i<20 && (i<3 || pdwVattrArray[ret*20+i]);i++)
					fprintf(tmp,"%5.5d,",pdwVattrArray[ret*20+i]);
				fprintf(tmp,"\n");
			}
			fclose(tmp);
		}
	}
	return ret;
}

const DWORD *CTermCap::GetVAttrByCmdId(DWORD cmdID)
{
	static DWORD tmpRet[]={0,0};
	const DWORD *ret=tmpRet;
	if (pdwVattrArray)
	{
		DWORD n=0;
		DWORD *ret0=NULL;
		DWORD *retN=NULL;
		DWORD curTermId=GetCurrentTerminalId();

		for(n=0;n<dwVattrArrayCount;n++)
		{
			DWORD *tmppos=pdwVattrArray+n*20;
			if (*tmppos==cmdID)
			{
				if (tmppos[1]==0) ret0=tmppos;
				if (tmppos[1]==curTermId) retN=tmppos;
			}
		}
		if (retN) ret=retN;
		else
		if (ret0) ret=ret0;
	}
	return ret;
}

DWORD CTermCap::GetVAttrTable(DWORD **pdwArr)
{
	DWORD ret=0;
	if (pdwArr)
	{
		*pdwArr=new DWORD [dwVattrArrayMax*20];
		CopyMemory(*pdwArr,pdwVattrArray,20*dwVattrArrayMax*sizeof(DWORD));
		ret=dwVattrArrayCount;
	}
	return ret;
}

DWORD CTermCap::SetAVArray(DWORD *idwArrai, DWORD dwItemsCount)
{
	if (idwArrai)
	{
		dwVattrArrayCount=dwItemsCount;
		if (pdwVattrArray) delete[] pdwVattrArray;
		dwVattrArrayMax=dwVattrArrayCount+100;
		pdwVattrArray=new DWORD [dwVattrArrayMax*20];
		ZeroMemory(pdwVattrArray, sizeof(DWORD)*dwVattrArrayMax*20);
		CopyMemory(pdwVattrArray,idwArrai,20*dwVattrArrayCount*sizeof(DWORD));
	}

	return dwVattrArrayCount;
}
