// GPExcel.cpp: implementation of the GPExcel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GP_term.h"
#include "GPExcel.h"

#include <comdef.h>
#include <direct.h>



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*struct StartOle {
    StartOle() { CoInitialize(NULL); }
    ~StartOle() { CoUninitialize(); }
} _inst_StartOle;*/

//////////////////void dump_com_error(_com_error &e)
//////////////////{
//////////////////	char str[2000];
//////////////////
//////////////////    _bstr_t bstrSource(e.Source());
//////////////////    _bstr_t bstrDescription(e.Description());
//////////////////
 //////////////////   sprintf(str,"Возникла ошибка при создании объекта!\n\a\tКод ошибки = %08lx\n\a\tЗначение кода = %s\n\a\tИсточник = %s\n\a\tОписание = %s\n",
//////////////////		e.Error(),e.ErrorMessage(), (LPCTSTR) bstrSource, (LPCTSTR) bstrDescription);
//////////////////	GPC.m_hViewWnd->MessageBox(str,"Интегрированная база данных МинФина России",MB_OK |MB_ICONEXCLAMATION );
//////////////////}


GPExcel::GPExcel()
{
	pExcel.m_lpDispatch=NULL;

	HRESULT hr;
	CLSID clsid;
	LPUNKNOWN pUnk=NULL;
	LPDISPATCH pDisp=NULL;
	hr=::CoInitialize(NULL); //инициализация библиотеки COM
	if (FAILED(hr))
		return ;
	hr=::CLSIDFromProgID(L"Excel.Application",&clsid); 
	if (SUCCEEDED(hr))
	{
		try
		{
			hr=::GetActiveObject(clsid,NULL,&pUnk); 
			if (SUCCEEDED(hr))  //приложение EXCEL уже существует
			{
				hr=pUnk->QueryInterface(IID_IDispatch,(void**)&pDisp);
				if (SUCCEEDED(hr))
				{
					pExcel.AttachDispatch(pDisp);
					static BYTE parms[]=VTS_BOOL;
					pExcel.InvokeHelper(0x22e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,TRUE);
				}
				hr=pUnk->Release(); 
			}
			else	// загрузить EXCEL
			{
				hr=::CoCreateInstance(clsid,NULL,CLSCTX_LOCAL_SERVER,IID_IUnknown,(void**)&pUnk);
				if (SUCCEEDED(hr))
				{
					hr=pUnk->QueryInterface(IID_IDispatch,(void**)&pDisp);
					if (SUCCEEDED(hr))
					{
						pExcel.AttachDispatch(pDisp);  
						static BYTE parms[]=VTS_BOOL;
						pExcel.InvokeHelper(0x22e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,TRUE);
					}
					hr=pUnk->Release(); 
				}
			}
		}
		catch(...) 
		{   
			GPC.m_ErrReport.GPWriteErrorLog("GPExcel", "GPExcel","");
		}
	}
	if (pExcel.m_lpDispatch!=NULL)
		IsDelete=TRUE;
}

GPExcel::~GPExcel()
{
//////////////////	if (IsDelete==TRUE && pXL!=NULL) delete[] pXL;
//	HRESULT hr;
	if (pExcel.m_lpDispatch!=NULL)
		pExcel.ReleaseDispatch(); 
	::CoUninitialize(); 
}







UINT GPExcel::GPExcelMacro(char *pParam)
{
	int i,nall;
	char *pos=(char *)pParam;
	char *argv[44];
	COleVariant* vararray=new COleVariant[44];

	for(nall=0;nall<44 && pos!=NULL;nall++)
	{
		argv[nall]=pos;
		if ((pos=strchr(pos,','))!=NULL) 
			*(pos++)=0;
	}

	for(i=nall;i<44;i++) argv[i]=NULL;
	for(i=0;i<44;i++)
	{
		switch(i)
		{
			case 0: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(argv[i]);
							else
								vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
						}
						else
							vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					}
					break;
			case 1: 
					{
						vararray[i]=COleVariant(long(atoi(argv[i])));
					}
					break;
			case 2: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(short(atoi(argv[i])));
							else
								vararray[i]=COleVariant(short(FALSE));
						}
						else
							vararray[i]=COleVariant(short(FALSE));
					}
					break;
			case 3: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(long(atoi(argv[i])));
							else
								vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
						}
						else
							vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					}
					break;
			case 4: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(argv[i]);
							else
								vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
						}
						else
							vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					}
					break;
			case 5: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(argv[i]);
							else
								vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
						}
						else
							vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					}
					break;
			case 6: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(short(atoi(argv[i])));
							else
								vararray[i]=COleVariant(short(FALSE));
						}
						else
							vararray[i]=COleVariant(short(FALSE));
					}
					break;
			case 7: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(long(atoi(argv[i])));
							else
								vararray[i]=COleVariant(long(2));
						}
						else
							vararray[i]=COleVariant(long(2));
					}
					break;
			case 8: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(argv[i]);
							else
								vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
						}
						else
							vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					}
					break;
			case 9: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(short(atoi(argv[i])));
							else
								vararray[i]=COleVariant(short(FALSE));
						}
						else
							vararray[i]=COleVariant(short(FALSE));
					}
					break;
			case 10: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(short(atoi(argv[i])));
							else
								vararray[i]=COleVariant(short(FALSE));
						}
						else
							vararray[i]=COleVariant(short(FALSE));
					}
					break;
			case 11: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(long(atoi(argv[i])));
							else
								vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
						}
						else
							vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					}
					break;
			case 12: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(short(atoi(argv[i])));
							else
								vararray[i]=COleVariant(short(FALSE));
						}
						else
							vararray[i]=COleVariant(short(FALSE));
					}
					break;
			default: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(argv[i]);
							else
								vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
						}
						else
							vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					}
					break;
		}
	}


	if (pExcel.m_lpDispatch!=NULL)
	{
		try 
		{
			if (OpenWorkBook(argv[0],vararray))
			{
				VARIANT result;
				static BYTE parms[] =
				VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT 
				VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
				pExcel.InvokeHelper(0x103, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&vararray[13], &vararray[14], &vararray[15], &vararray[16], &vararray[17], &vararray[18], 
		&vararray[19], &vararray[20], &vararray[21], &vararray[22], &vararray[23], &vararray[24],
		&vararray[25], &vararray[26], &vararray[27], &vararray[28], &vararray[29], &vararray[30],
		&vararray[31], &vararray[32], &vararray[33], &vararray[34], &vararray[35], &vararray[36],
		&vararray[37], &vararray[38], &vararray[39], &vararray[40], &vararray[41], &vararray[42],
		&vararray[43]);
			}
			
		} 
		catch(...) 
		{
			GPC.m_ErrReport.GPWriteErrorLog("GPExcel", "GPExcelMacro",pParam);
		}
	}
	delete[] vararray;
	return 0;
}

BOOL GPExcel::OpenWorkBook(char* name,COleVariant *vararray)
{
	BOOL ret=FALSE;
	COleDispatchDriver pWorkbooks;

	// получение коллекции Workbook
	pWorkbooks.m_lpDispatch=NULL;
	pExcel.InvokeHelper(0x23c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pWorkbooks.m_lpDispatch, NULL);

	LPDISPATCH result=NULL;
	if (pWorkbooks.m_lpDispatch!=NULL)
	{
		static BYTE parms[] =
			VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
		pWorkbooks.InvokeHelper(0x2aa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
			name, &vararray[1], &vararray[2], &vararray[3], &vararray[4], &vararray[5],
			&vararray[6], &vararray[7], &vararray[8], &vararray[9], &vararray[10], &vararray[11], &vararray[12]);
	}

	if (result!=NULL)
		ret=TRUE;

	return ret;
}

UINT RunGPExcelMacroThread(LPVOID LPVoidParam)
{
	char *pParam=(char*) LPVoidParam;
	int ret=-1;
	HRESULT hr;
	COleDispatchDriver pWorkbooksS;
	COleDispatchDriver pExcelS;
	int i,nall;
	char *pos=(char *)pParam;
	char *argv[32];
	char* pfilewrkbookbuff;
	CString strfilewrkbookbuff;
	int flg=1;
	COleVariant vararray[32];
	CLSID clsid;
	LPUNKNOWN pUnk=NULL;
	LPDISPATCH pDisp=NULL;

	// разбор параметров
	for(nall=0;nall<32 && pos!=NULL;nall++)
	{
		argv[nall]=pos;
		if ((pos=strchr(pos,','))!=NULL) 
			*(pos++)=0;
	}

	for(i=nall;i<32;i++) argv[i]=NULL;
	for(i=0;i<32;i++)
	{
		if (argv[i]!=NULL)
		{
			if (argv[i][0]!=0)
				vararray[i]=COleVariant(argv[i]);
			else
				vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		}
		else
			vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	}
 
	pExcelS.m_lpDispatch=NULL;
	pWorkbooksS.m_lpDispatch=NULL;

	if (argv[0]==NULL || (int)strlen(argv[0])==0)
	{
		flg=-1;
	}
	else
	{
		pfilewrkbookbuff=strstr(argv[0],":");
		if (((pfilewrkbookbuff==NULL) || (pfilewrkbookbuff==argv[0])) && (argv[0][0]!='.'))
		{
			pfilewrkbookbuff=new char[1024];
			if (!_getcwd(pfilewrkbookbuff,1000)) *pfilewrkbookbuff=0;;
			if (*pfilewrkbookbuff)	strcat(pfilewrkbookbuff,"\\");
			strcat(pfilewrkbookbuff,argv[0]);
			strfilewrkbookbuff=pfilewrkbookbuff;
			delete[] pfilewrkbookbuff;
		}
		else
			strfilewrkbookbuff=argv[0];
		FILE* pFl=fopen(strfilewrkbookbuff,"r");
		if (pFl!=NULL)
		{
			fclose(pFl);
		}
		else
		{
			flg=-1;
		}
	}
	if (flg==-1)
	{
#ifdef RUS
		CString strWarning="Не найден файл EXCEL: ";
#else
		CString strWarning="Can't find EXCEL: ";
#endif
		strWarning+=argv[0];
		AfxMessageBox(strWarning);
	}
	if (flg>=0)
	{
		hr=::CoInitialize(NULL); //инициализация библиотеки COM
		if (FAILED(hr))
		{
		#ifdef RUS
			AfxMessageBox("Невозможно инициализировать библиотеку COM");
		#else
			AfxMessageBox("Can't initialize COM library");
		#endif
			flg=-2;
		}
		else
		{
			hr=::CLSIDFromProgID(L"Excel.Application",&clsid); 
			if (FAILED(hr))
			{
#ifdef RUS
				AfxMessageBox("EXCEL не найден либо не установлен !");
#else
				AfxMessageBox("EXCEL not found !");
#endif
				flg=-3;
			}
			else
			{
				try
				{
					// поиск приложения EXCEL
					hr=::GetActiveObject(clsid,NULL,&pUnk);
					if FAILED(hr)
					{
						// запуск приложения EXCEL
						hr=::CoCreateInstance(clsid,NULL,CLSCTX_LOCAL_SERVER,IID_IUnknown,(void**)&pUnk);
					}
					if (SUCCEEDED(hr))
					{
						hr=pUnk->QueryInterface(IID_IDispatch,(void**)&pDisp);
						if (SUCCEEDED(hr))
						{
							pExcelS.AttachDispatch(pDisp);  
							static BYTE parms[]=VTS_BOOL;
							pExcelS.InvokeHelper(0x22e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,TRUE);
						}
						hr=pUnk->Release(); 
					}
				}
				catch(...) 
				{
					GPC.m_ErrReport.GPWriteErrorLog("GPExcel", "RunGPExcelMacroThread 488","");
#ifdef RUS
					AfxMessageBox("EXCEL не найден либо не установлен !");
#else
					AfxMessageBox("EXCEL not found!");
#endif
					flg=-4;
				}
				if (pExcelS.m_lpDispatch==NULL)
				{
#ifdef RUS
					AfxMessageBox("EXCEL не найден либо не установлен !");
#else
					AfxMessageBox("EXCEL not found!");
#endif
					flg=-4;
				}
				else
				{
					// открытие книги
					try
					{
						LPDISPATCH result=NULL;
						pExcelS.InvokeHelper(0x23c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
						pWorkbooksS.AttachDispatch(result); 
						result=NULL;
						if (pWorkbooksS.m_lpDispatch!=NULL)
						{
							COleVariant vOpt=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
							static BYTE parms[] =
								VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
							pWorkbooksS.InvokeHelper(0x2aa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
								strfilewrkbookbuff, &vOpt, &vOpt, &vOpt, &vOpt, &vOpt,
								&vOpt, &vOpt, &vOpt, &vOpt, &vOpt, &vOpt, &vOpt);
						}
						if (result==NULL)
						{
							AfxMessageBox("Can't open EXCEL workbook!");
							flg=-5;
						}
						else 
							result->Release(); 
					}
					catch(...) 
					{
						GPC.m_ErrReport.GPWriteErrorLog("GPExcel", "RunGPExcelMacroThread 533","");
						AfxMessageBox("Can't open EXCEL workbook!");
						flg=-5;
					}
				}
			}
		}
	}
	if (flg>=0)
	{
		// запуск макроса
		int icounter=0;
		while ((icounter>=0) && (icounter<100))
		{
			try 
			{
				VARIANT resultm;
	/*			static BYTE parms[] =
				VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT
				VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT 
				VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT 
				VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT 
				VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT 
				VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT 
				VTS_VARIANT;*/
				static BYTE parmsm[] =
					VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT 
					VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
					pExcelS.InvokeHelper(0x103, DISPATCH_METHOD, VT_VARIANT, (void*)&resultm, parmsm,
						&vararray[1], &vararray[2], &vararray[3], &vararray[4], &vararray[5], 
						&vararray[6], &vararray[7], &vararray[8], &vararray[9], &vararray[10], 
						&vararray[11], &vararray[12], &vararray[13], &vararray[14], &vararray[15],
						&vararray[16], &vararray[17], &vararray[18], &vararray[19], &vararray[20], 
						&vararray[21], &vararray[22], &vararray[23], &vararray[24],	&vararray[25], 
						&vararray[26], &vararray[27], &vararray[28], &vararray[29], &vararray[30],
						&vararray[31]);
				ret=1;
				icounter=-1;
			} 
			catch(...) 
			{
				GPC.m_ErrReport.GPWriteErrorLog("GPExcel", "RunGPExcelMacroThread","");
				icounter++;
				Sleep(100);
			}
		}
		if (icounter>=100)
#ifdef RUS
			AfxMessageBox("Ошибка запуска макроса EXCEL!");
#else
			AfxMessageBox("Error executing of EXCEL macro!");
#endif
	}	
	if (flg!=-2)
		::CoUninitialize(); 
	delete[]  pParam;
	return ret;
}

UINT GPExcel::RunGPExcelMacro(char *pParam)
{
	AfxBeginThread(RunGPExcelMacroThread,(void*)pParam);
	return 1;
}

UINT RunGPExcelMacroOLD(char *pParam)
{
	int ret=-1;
	HRESULT hr;
	COleDispatchDriver pWorkbooksS;
	COleDispatchDriver pExcelS;
	int i,nall;
	char *pos=(char *)pParam;
	char *argv[44];
	COleVariant vararray[44];
	CLSID clsid;
	LPUNKNOWN pUnk=NULL;
	LPDISPATCH pDisp=NULL;

	// разбор параметров
	for(nall=0;nall<44 && pos!=NULL;nall++)
	{
		argv[nall]=pos;
		if ((pos=strchr(pos,','))!=NULL) 
			*(pos++)=0;
	}

	for(i=nall;i<44;i++) argv[i]=NULL;
	for(i=0;i<44;i++)
	{
		switch(i)
		{
			case 0: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(argv[i]);
							else
								vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
						}
						else
							vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					}
					break;
			case 1: 
					{
						vararray[i]=COleVariant(long(atoi(argv[i])));
					}
					break;
			case 2: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(short(atoi(argv[i])));
							else
								vararray[i]=COleVariant(short(FALSE));
						}
						else
							vararray[i]=COleVariant(short(FALSE));
					}
					break;
			case 3: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(long(atoi(argv[i])));
							else
								vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
						}
						else
							vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					}
					break;
			case 4: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(argv[i]);
							else
								vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
						}
						else
							vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					}
					break;
			case 5: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(argv[i]);
							else
								vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
						}
						else
							vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					}
					break;
			case 6: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(short(atoi(argv[i])));
							else
								vararray[i]=COleVariant(short(FALSE));
						}
						else
							vararray[i]=COleVariant(short(FALSE));
					}
					break;
			case 7: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(long(atoi(argv[i])));
							else
								vararray[i]=COleVariant(long(2));
						}
						else
							vararray[i]=COleVariant(long(2));
					}
					break;
			case 8: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(argv[i]);
							else
								vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
						}
						else
							vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					}
					break;
			case 9: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(short(atoi(argv[i])));
							else
								vararray[i]=COleVariant(short(FALSE));
						}
						else
							vararray[i]=COleVariant(short(FALSE));
					}
					break;
			case 10: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(short(atoi(argv[i])));
							else
								vararray[i]=COleVariant(short(FALSE));
						}
						else
							vararray[i]=COleVariant(short(FALSE));
					}
					break;
			case 11: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(long(atoi(argv[i])));
							else
								vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
						}
						else
							vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					}
					break;
			case 12: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(short(atoi(argv[i])));
							else
								vararray[i]=COleVariant(short(FALSE));
						}
						else
							vararray[i]=COleVariant(short(FALSE));
					}
					break;
			default: 
					{
						if (argv[i]!=NULL)
						{
							if (argv[i][0]!=0)
								vararray[i]=COleVariant(argv[i]);
							else
								vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
						}
						else
							vararray[i]=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
					}
					break;
		}
	}

	// запуск приложения EXCEL 
	pExcelS.m_lpDispatch=NULL;
	pWorkbooksS.m_lpDispatch=NULL; 
	hr=::CoInitialize(NULL); //инициализация библиотеки COM
	if (FAILED(hr))
		return ret;
	hr=::CLSIDFromProgID(L"Excel.Application",&clsid); 
	if (FAILED(hr))
		return ret;
	try
	{
		hr=::CoCreateInstance(clsid,NULL,CLSCTX_LOCAL_SERVER,IID_IUnknown,(void**)&pUnk);
		if (SUCCEEDED(hr))
		{
			hr=pUnk->QueryInterface(IID_IDispatch,(void**)&pDisp);
			if (SUCCEEDED(hr))
			{
				pExcelS.AttachDispatch(pDisp);  
				static BYTE parms[]=VTS_BOOL;
				pExcelS.InvokeHelper(0x22e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,TRUE);
			}
			hr=pUnk->Release(); 
		}
	}
	catch(...) 
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPExcel", "RunGPExcelMacroOLD 828","");
	}
	if (pExcelS.m_lpDispatch==NULL)
		return ret;

	// открытие книги
	try
	{
		LPDISPATCH result=NULL;
		pExcelS.InvokeHelper(0x23c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		pWorkbooksS.AttachDispatch(result); 
		result=NULL;
		if (pWorkbooksS.m_lpDispatch!=NULL)
		{
			static BYTE parms[] =
				VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
			pWorkbooksS.InvokeHelper(0x2aa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
				argv[0], &vararray[1], &vararray[2], &vararray[3], &vararray[4], &vararray[5],
				&vararray[6], &vararray[7], &vararray[8], &vararray[9], &vararray[10], &vararray[11], &vararray[12]);
		}
		if (result==NULL)
			return ret;
	}
	catch(...) 
	{
		GPC.m_ErrReport.GPWriteErrorLog("GPExcel", "RunGPExcelMacroOLD 853","");
	}



	// запуск макроса
	int icounter=0;
	while ((icounter>=0) && (icounter<100))
	{
	 try 
		{
			VARIANT result;
			static BYTE parms[] =
			VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT 
			VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
			pExcelS.InvokeHelper(0x103, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
				&vararray[13], &vararray[14], &vararray[15], &vararray[16], &vararray[17], 
				&vararray[18], &vararray[19], &vararray[20], &vararray[21], &vararray[22], 
				&vararray[23], &vararray[24], &vararray[25], &vararray[26], &vararray[27],
				&vararray[28], &vararray[29], &vararray[30], &vararray[31], &vararray[32], 
				&vararray[33], &vararray[34], &vararray[35], &vararray[36],	&vararray[37], 
				&vararray[38], &vararray[39], &vararray[40], &vararray[41], &vararray[42],
				&vararray[43]);
			ret=1;
			icounter=-1;
		} 
		//catch(_com_error &e) 
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("GPExcel", "RunGPExcelMacroOLD 882","");
			icounter++;
			Sleep(100);
		}
	}
	if (icounter>=100)
#ifdef RUS
		AfxMessageBox("Ошибка запуска макроса !");
#else
		AfxMessageBox("Error executing of EXCEL macro!");
#endif
	

	::CoUninitialize(); 
	return ret;
}
