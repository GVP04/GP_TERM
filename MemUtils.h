// MemUtils.h: interface for the CMemUtils class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMUTILS_H__0A56C78E_CB75_4D1F_8093_42988ABFF785__INCLUDED_)
#define AFX_MEMUTILS_H__0A56C78E_CB75_4D1F_8093_42988ABFF785__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MC_MALLOC(x,y) ((x *)malloc(y * sizeof(x)))
#define MC_FREE(x) (free(x),  x = NULL)
#define MC_DELETE(x) (delete x,  x = NULL)

class CMemUtils  
{
public:
	CMemUtils();
	virtual ~CMemUtils();

	static inline BSTR MEM_AnsiToBSTR(const char *pchData)
	{
	   BSTR bstr = NULL;
	   int nLen = MultiByteToWideChar(CP_ACP, 0, pchData, (int)strlen(pchData), NULL, NULL);

	   bstr = ::SysAllocStringLen(NULL, nLen);
	   if (bstr == NULL) return NULL;
	   MultiByteToWideChar(CP_ACP, 0, pchData, (int)strlen(pchData), bstr, nLen);
	   return bstr;
	}

	static inline LPTSTR MEM_BSTRToAnsi(const BSTR bsData)
	{
		LPTSTR pRet = NULL;
		int nLen = WideCharToMultiByte(CP_ACP, 0, bsData, SysStringLen(bsData), NULL, NULL, NULL, NULL) + 1;
 
		pRet = MC_MALLOC(char,nLen);
		WideCharToMultiByte(CP_ACP, 0, bsData, SysStringLen(bsData), pRet, nLen, NULL, NULL);
		if (nLen>0 && pRet) pRet[nLen - 1] = '\0';
		return pRet;
	}

	static void MEM_AnsiConcatCopy(char *pchData1, char *pchData2)
	{
		char *pchTmp = NULL;
		int nStr1 = (int)strlen(pchData1), nStr2 = (int)strlen(pchData2);
		int nNewLen = nStr1 + nStr2 + 1;

		if (nNewLen > 1)
		{
			pchTmp = MC_MALLOC(char,nNewLen);
			memcpy(pchTmp, (pchData1), nStr1*sizeof(char));
			memcpy(pchTmp+nStr1, pchData2, nStr2*sizeof(char));
			if (nNewLen>0 && pchTmp) pchTmp[nNewLen - 1] = '\0';
			MC_FREE(pchData1);
			pchData1=pchTmp;
		}
	}

	static inline void MEM_BSTRConcatCopy(BSTR bsData1, BSTR bsData2)
	{
		BSTR bstr = NULL;
		int nStr1 = SysStringLen(bsData1), nStr2 = SysStringLen(bsData2);
		int nLenByte1 = WideCharToMultiByte(CP_ACP, 0, bsData1, SysStringLen(bsData1), NULL, NULL, NULL, NULL) + 1;
		int nLenByte2 = WideCharToMultiByte(CP_ACP, 0, bsData2, SysStringLen(bsData2), NULL, NULL, NULL, NULL) + 1;
		int nNewLen = nStr1 + nStr2;

		if (nNewLen > 0)
		{
			bstr = SysAllocStringLen(NULL, nNewLen);
			memcpy(bstr, bsData1, nLenByte1);
			memcpy(bstr+nLenByte1, bsData2, nLenByte2);
			//memcpy(bstr, bsData1, strlen((char *)bsData1));
			//memcpy(bstr+nStr1, bsData2, strlen((char *)bsData2));
			SysFreeString(bsData1);
			bsData1 = bstr;
		}
	}

	static inline void MEM_CopyBstrToVariant(VARIANT *pVarTmp, BSTR bstrTmp) 
	{
		VariantInit(pVarTmp);
		V_BSTR(pVarTmp) = bstrTmp;
		V_VT(pVarTmp) = VT_BSTR;
		return ;
	}

	static inline void MEM_CopyAnsiToVariant(VARIANT *pVarTmp, char* strTmp) 
	{
		VariantInit(pVarTmp);
		V_I1REF(pVarTmp) = strTmp;
		V_VT(pVarTmp) = VT_I1 | VT_BYREF;
		return ;
	}

	static inline void MEM_CopyDispatchToVariant(VARIANT *pVarTmp, IDispatch *pDisp) 
	{
		VariantInit(pVarTmp);
		V_DISPATCH(pVarTmp) = pDisp;
		V_VT(pVarTmp) = VT_DISPATCH;
		return ;
	}
	
	static inline void MEM_CopyPDispatchToVariant(VARIANT *pVarTmp, IDispatch **ppDisp) 
	{
		VariantInit(pVarTmp);
		V_DISPATCHREF(pVarTmp) = ppDisp;
		V_VT(pVarTmp) = VT_BYREF|VT_DISPATCH;
		return ;
	}

	static inline void MEM_CopyLongToVariant(VARIANT *pVarTmp, long lVal) 
	{
		VariantInit(pVarTmp);
		V_I4(pVarTmp) = lVal;
		V_VT(pVarTmp) = VT_I4;
		return ;
	}
};

#endif // !defined(AFX_MEMUTILS_H__0A56C78E_CB75_4D1F_8093_42988ABFF785__INCLUDED_)
