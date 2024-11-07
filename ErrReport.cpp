// ErrReport.cpp: implementation of the CErrReport class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "ErrReport.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CErrReport::CErrReport()
{
	m_FileName="MAINERR.LOG";
	dwErrorFlag=0;
	dwErrorMask=(EL_INDICMASK|EL_WRITEMASK)^(EL_INDICWARNING2|EL_INDICWARNING1|EL_WRITEWARNING2|EL_WRITEWARNING1);

	m_SprErr=NULL;
	m_SprErr2=NULL;
	m_SprWarn=NULL;
	m_SprWarn2=NULL;

	m_SprErr	=GPC.m_SprArray.CreateSpr("m_SprErr");
	m_SprErr2	=GPC.m_SprArray.CreateSpr("m_SprErr2");
	m_SprWarn	=GPC.m_SprArray.CreateSpr("m_SprWarn");
	m_SprWarn2	=GPC.m_SprArray.CreateSpr("m_SprWarn2");

	m_SprErr	->Create("m_SprErr",5);
	m_SprErr2	->Create("m_SprErr2",5);
	m_SprWarn	->Create("m_SprWarn",5);
	m_SprWarn2	->Create("m_SprWarn2",5);

	hiNormal=NULL;
	hiWarn=NULL;
}

CErrReport::~CErrReport()
{
	if (hiNormal) DestroyIcon(hiNormal);
	if (hiWarn) DestroyIcon(hiWarn);
}

DWORD CErrReport::SetIcon(HWND ihWnd, DWORD dwFlags)
{
	SYSTEMTIME mst={0};
	GetSystemTime(&mst);
	HICON hIconOld;
	static int lastsecond;
	if (hiWarn && hiNormal && mst.wSecond!=lastsecond)
	{
		lastsecond=mst.wSecond;
		hIconOld=CWnd::FromHandle(ihWnd)->SetIcon((dwErrorFlag&dwErrorMask) && (mst.wSecond&0x1)?hiWarn:hiNormal,FALSE);
		if (hIconOld!=hiWarn && hIconOld!=hiNormal) DestroyIcon(hIconOld);
	}
	return 0;
}

void CErrReport::GPWriteErrorLog(const char *ccId, const char *iInfo, const char *iInfo2)
{
	COleDateTime tm=COleDateTime::GetCurrentTime();
	CString tmp1=tm.Format("%#c");
	if ((dwErrorMask&EL_INDICERROR1))
	{
		dwErrorFlag|=EL_INDICERROR1;
		if (m_SprErr->GetCount()>2500)
			while(m_SprErr->GetCount()>2000)
				m_SprErr->DeleteItem(0);

		UINT itm=m_SprErr->InsertEmpty(-1,1)-1;
		m_SprErr->SetItem(itm,tmp1);
		m_SprErr->SetSubItem(itm,1,ccId);
		m_SprErr->SetSubItem(itm,2,iInfo);
		m_SprErr->SetSubItem(itm,3,iInfo2);
		m_SprErr->SetSubItem(itm,4,"ERROR1");
	}

	if ((dwErrorMask&EL_WRITEERROR1))
	{
		FILE *fl=fopen(m_FileName,"at");
		if (fl)
		{
			fputs(tmp1,fl);
			fputs("\t0\t",fl);
			fputs(ccId,fl);
			fputc('\t',fl);
			fputs(iInfo,fl);
			fputc('\t',fl);
			fputs(iInfo2,fl);
			fputs("\n",fl);
			fclose(fl);
		}
	}
}

void CErrReport::GPWriteErrorLog2(const char *ccId, const char *iInfo, const char *iInfo2)
{
	COleDateTime tm=COleDateTime::GetCurrentTime();
	CString tmp1=tm.Format("%#c");
	if ((dwErrorMask&EL_INDICERROR2))
	{
		dwErrorFlag|=EL_INDICERROR2;
		if (m_SprErr2->GetCount()>2500)
			while(m_SprErr2->GetCount()>2000)
				m_SprErr2->DeleteItem(0);

		UINT itm=m_SprErr2->InsertEmpty(-1,1)-1;
		m_SprErr2->SetItem(itm,tmp1);
		m_SprErr2->SetSubItem(itm,1,ccId);
		m_SprErr2->SetSubItem(itm,2,iInfo);
		m_SprErr2->SetSubItem(itm,3,iInfo2);
		m_SprErr->SetSubItem(itm,4,"EERROR2");
	}

	if ((dwErrorMask&EL_WRITEERROR2))
	{
		FILE *fl=fopen(m_FileName,"at");
		if (fl)
		{
			fputs(tmp1,fl);
			fputs("\t1\t",fl);
			fputs(ccId,fl);
			fputc('\t',fl);
			fputs(iInfo,fl);
			fputc('\t',fl);
			fputs(iInfo2,fl);
			fputs("\n",fl);
			fclose(fl);
		}
	}
}

void CErrReport::GPWriteWarnLog(const char *ccId, const char *iInfo, const char *iInfo2)
{
	COleDateTime tm=COleDateTime::GetCurrentTime();
	CString tmp1=tm.Format("%#c");
	if ((dwErrorMask&EL_INDICWARNING1))
	{
		dwErrorFlag|=EL_INDICWARNING1;
		if (m_SprWarn->GetCount()>2500)
			while(m_SprWarn->GetCount()>2000)
				m_SprWarn->DeleteItem(0);

		UINT itm=m_SprWarn->InsertEmpty(-1,1)-1;
		m_SprWarn->SetItem(itm,tmp1);
		m_SprWarn->SetSubItem(itm,1,ccId);
		m_SprWarn->SetSubItem(itm,2,iInfo);
		m_SprWarn->SetSubItem(itm,3,iInfo2);
		m_SprErr->SetSubItem(itm,4,"WARNING1");
	}

	if ((dwErrorMask&EL_WRITEWARNING1))
	{
		FILE *fl=fopen(m_FileName,"at");
		if (fl)
		{
			fputs(tmp1,fl);
			fputs("\t2\t",fl);
			fputs(ccId,fl);
			fputc('\t',fl);
			fputs(iInfo,fl);
			fputc('\t',fl);
			fputs(iInfo2,fl);
			fputs("\n",fl);
			fclose(fl);
		}
	}
}

void CErrReport::GPWriteWarnLog2(const char *ccId, const char *iInfo, const char *iInfo2)
{
	COleDateTime tm=COleDateTime::GetCurrentTime();
	CString tmp1=tm.Format("%#c");
	if ((dwErrorMask&EL_INDICWARNING2))
	{
		dwErrorFlag|=EL_INDICWARNING2;
		if (m_SprWarn2->GetCount()>2500)
			while(m_SprWarn2->GetCount()>2000)
				m_SprWarn2->DeleteItem(0);


		UINT itm=m_SprWarn2->InsertEmpty(-1,1)-1;
		m_SprWarn2->SetItem(itm,tmp1);
		m_SprWarn2->SetSubItem(itm,1,ccId);
		m_SprWarn2->SetSubItem(itm,2,iInfo);
		m_SprWarn2->SetSubItem(itm,3,iInfo2);
		m_SprErr->SetSubItem(itm,4,"WARNING2");
	}
	if ((dwErrorMask&EL_WRITEWARNING2))
	{
		FILE *fl=fopen(m_FileName,"at");
		if (fl)
		{
			fputs(tmp1,fl);
			fputs("\t3\t",fl);
			fputs(ccId,fl);
			fputc('\t',fl);
			fputs(iInfo,fl);
			fputc('\t',fl);
			fputs(iInfo2,fl);
			fputs("\n",fl);
			fclose(fl);
		}
	}
}

void CErrReport::ResetErrorFlag()
{
	dwErrorFlag=0;
}

void CErrReport::Init()
{
	hiNormal=(HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_GP_TERTYPE),IMAGE_ICON,16,16,0);
	hiWarn=(HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_GP_TERTYPEWARN),IMAGE_ICON,16,16,0);
	dwErrorMask=(EL_INDICMASK|EL_WRITEMASK)^(EL_INDICWARNING2|EL_INDICWARNING1|EL_WRITEWARNING2|EL_WRITEWARNING1);
}
