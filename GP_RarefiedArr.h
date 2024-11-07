// GP_RarefiedArr.h: interface for the GP_RarefiedArr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GP_RAREFIEDARR_H__417283C1_B9B8_11D2_B27D_00600840D054__INCLUDED_)
#define AFX_GP_RAREFIEDARR_H__417283C1_B9B8_11D2_B27D_00600840D054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define GPRA_ALLITEMS	0xFFFFFFFE


template <class ArrType> class GP_RarefiedArr  
{
private:
	void DeleteArrays()
	{
		if (SeqArrVal) 
		{
			delete[] SeqArrVal;
			SeqArrVal=NULL;
		}

		if (IdArrSave) 
		{
			delete[] IdArrSave;
			IdArrSave=NULL;
		}

		if (SeqArr!=NULL)
			delete[] SeqArr;
		SeqArr=NULL;
		if (ArrTypeArray!=NULL)
			delete[] ArrTypeArray;
		ArrTypeArray=NULL;
		if (IdArr!=NULL) 
			delete[] IdArr;
		IdArr=NULL;
	}

public:
	int GetIdsList(CString &Outs, const char *Delimeter)
	{
		char tmp[600];
		UINT DelimeterLen=strlen(Delimeter);
		UINT nj=600/(sizeof(UINT)*3+DelimeterLen);
		UINT i;
		*tmp=0;
		for(i=0;i<ItemCount;i++)
		{
			char *pos=tmp;
			UINT j;
			for(j=0;i<ItemCount && j<nj;j++,i++)
			{
				pos+=DelimeterLen;
				pos+=sprintf(pos,"%d",IdArr[SeqArr[i]]);
			}
			if (i==0)	Outs+=(tmp+strlen(Delimeter));
			else		Outs+=tmp;
			
		}
		return ItemCount;
	}
	int GetSelectedId()
	{
		return Selection>ItemCount?0xFFFFFFFFL:IdArr[SeqArr[Selection]];
	}

	int SelectNext() 
	{
		if (Selection<ItemCount) Selection++;
		if (Selection==ItemCount)  Selection=0xFFFFFFFFL;
		return GetSelectedId();
	}

	int SelectFirst() 
	{
		Selection=0;
		if (Selection>ItemCount || ItemCount==0) Selection=0xFFFFFFFFL;
		return GetSelectedId();
	}

	int SelectItem(int iItem)
	{
		Selection=GetIdNum(iItem);
		return GetSelectedId();
	}

	int GetItemCount() 
	{
		return ItemCount;
	}

	int GetArraySize()
	{
		return ArrCount;
	}

	const ArrType GetInitValue()
	{
		return InitValue;
	}

	void SetInitValue(ArrType & iInitValue)
	{
		InitValue=iInitValue;
	}

	void SetArray(ArrType & iInitValue)
	{
		UINT i;
		for(i=0;i<ItemCount;i++)
		 ArrTypeArray[i]=iInitValue;
	}

	UINT GetMaxId()
	{
		return ItemCount>0?IdArr[SeqArr[ItemCount]]:0;
	}

	UINT GetMinId()
	{
		return ItemCount>0?IdArr[SeqArr[0]]:0;
	}

	UINT GetIDsArray(UINT **iIdArray)
	{
		UINT ret=0;
		if (iIdArray && ItemCount) 
		{
			*iIdArray=new UINT [ItemCount];
			UINT *p=*iIdArray;
			UINT *ps=*SeqArr;
			UINT i=ItemCount;

			while(i--)
				*(p++)=IdArr[*(ps++)];
				
			ret=ItemCount;
		}
		return ret;
	}

	BOOL ChangeId(UINT IdOld, UINT IdNew)
	{
		BOOL ret=FALSE;
		if (GetIdNum(IdNew)==0xFFFFFFFFL)
		{
			UINT IdNUM=GetIdNum(IdOld);
			if (IdNUM!=0xFFFFFFFFL)
			{
				IdArr[IdNUM]=IdNew;
				ret=TRUE;
			}
		}

		return ret;
	}

	UINT GetIDsOfSortArray(UINT **iIdArray)
	{
		if (SeqArrVal==NULL) SortArray();

		UINT ret=0;
		if (iIdArray && ItemCount) 
		{
			*iIdArray=new UINT [ItemCount];
			UINT *p=*iIdArray;
			UINT *ps=*SeqArrVal;
			UINT i=ItemCount;

			while(i--)
				*(p++)=IdArr[*(ps++)];
				
			ret=ItemCount;
		}
		return ret;
	}

public:
	void SortArray()
	{
		if (ItemCount)
			qSortArray(0, ItemCount-1);
	}

private:
	void qSortArray(int left, int right)
	{
		register int i,j;
		ArrType x;
		DWORD y;

		i=left;
		j=right;
		x=ArrTypeArray[SeqArr[(left+right)/2]];

		do
		{
			while(ArrTypeArray[SeqArr[i]]<x && i<right) i++;
			while(x<ArrTypeArray[SeqArr[j]] && j>left) j--;

			if (i<=j)
			{
				y=SeqArr[i];
				SeqArr[i]=SeqArr[j];
				SeqArr[j]=y;
				i++;
				j--;
			}
		}while(i<=j);
		if(left<j) qSortArray(left,j);
		if (i<right) qSortArray(i,right);
	}

public:
	void SortArrayById()
	{
		if (ItemCount)
			qSortArrayById(0, ItemCount-1);
	}

private:
	void qSortArrayById(int left, int right)
	{
		register int i,j;
		UINT x,y;

		i=left;
		j=right;
		x=(left+right)/2;

		do
		{
			while(IdArr[SeqArr[i]]<IdArr[SeqArr[x]] && i<right) i++;
			while(IdArr[SeqArr[x]]<IdArr[SeqArr[j]] && j>left) j--;

			if (i<=j)
			{
				y=SeqArr[i];
				SeqArr[i]=SeqArr[j];
				SeqArr[j]=y;
				i++;
				j--;
			}
		}while(i<=j);
		if(left<j) qSortArrayById(left,j);
		if (i<right) qSortArrayById(i,right);
	}

public:
	void RemoveSelected()
	{
		RemoveItem(GetSelectedId());
	}

	void RemoveItem(int iNItem)
	{
		if (SeqArrVal) 
		{
			delete[] SeqArrVal;
			SeqArrVal=NULL;
		}
		if (IdArrSave) 
		{
			delete[] IdArrSave;
			IdArrSave=NULL;
		}

		if (iNItem==GPRA_ALLITEMS)
			InitArray();
		else
		{
			UINT IdNum;
			UINT SeqArrNum;
			if (ItemCount>0 && (IdNum=GetIdNum(iNItem,SeqArrNum))!=0xFFFFFFFFL)
			{
				UINT i;
		
				for(i=SeqArrNum+1;i<ArrCount;i++) 
					SeqArr[i-1]=SeqArr[i];

				for(i=0;i<ItemCount;i++) 
					if (SeqArr[i]>IdNum && SeqArr[i]<ArrCount) SeqArr[i]--;
				
				for(i=IdNum+1;i<ItemCount;i++) 
				{
					IdArr[i-1]=IdArr[i];
					ArrTypeArray[i-1]=ArrTypeArray[i];
				}
				ItemCount--;
				IdArr[ItemCount]=0xFFFFFFFFL;
				ArrTypeArray[ItemCount]=InitValue;
				SeqArr[ItemCount]=IdNum;
			}
		}
	}

	UINT RemoveItemByVal(ArrType iValue)
	{
		RemoveItem(GetIdByVal(iValue));
		return ItemCount;
	}

	UINT Normalize(UINT IdStart, int Delta, BOOL bCreateSave)
	{
		UINT i=0;
		if (ItemCount && Delta)
		{
			if (bCreateSave) SaveArrayId();
			SortArrayById();
			for(i=0;i<ItemCount;i++)
				if (ArrTypeArray[SeqArr[i]]==InitValue)
					RemoveItem(IdArr[SeqArr[i--]]);

			for(i=0;i<ItemCount;i++,IdStart+=Delta)
				IdArr[SeqArr[i]]=IdStart;
			SortArrayById();
		}
		return IdStart;
	}


	UINT AddItem(ArrType iValue)
	{
		if (SeqArrVal) 
		{
			delete[] SeqArrVal;
			SeqArrVal=NULL;
		}
		if (ItemCount)	(*this)[(IdArr[SeqArr[ItemCount-1]]+1)]=iValue;
		else			(*this)[1]=iValue;

		return ItemCount;
	}

	UINT GetIdByVal(ArrType iValue)
	{
		UINT ret=0xFFFFFFFFL;
		if (SeqArrVal) 
		{
			switch(ItemCount)
			{
			case 1: if (iValue==ArrTypeArray[SeqArrVal[0]]) ret=0;
			case 0: break;
			default:
				{
					int low=0,high=ItemCount-1,mid;
					while(low<=high)
					{
						mid=(low+high)/2;
						if (iValue<ArrTypeArray[SeqArrVal[mid]]) high=mid-1;
						else 
							if (iValue>ArrTypeArray[SeqArrVal[mid]]) low=mid+1;
							else {ret=SeqArrVal[mid];break;}
					}
				}
			}
		}
		else
		{
			UINT i;
			for(i=0;i<ItemCount;i++)
				if (ArrTypeArray[i]==iValue) 
				{
					ret=IdArr[i];
					break;
				}
		}
		return ret;
	}

	void SaveArrayId()
	{
		if (IdArrSave) 
		{
			delete[] IdArrSave;
			IdArrSave=NULL;
		}
		if (ItemCount)
		{
			IdArrSave= new UINT [ItemCount];
			UINT i;
			for(i=0;i<ItemCount;i++)
				IdArrSave[i]=IdArr[i];
		}
	}

	void SaveId(UINT iId, BOOL iBySavedId = FALSE)
	{
		if (ItemCount)
		{
			if (IdArrSave==NULL) SaveArrayId();
			else
			{
				UINT IdNum;
				if (iBySavedId)
					IdNum=GetSavedIdNum(iId);
				else
					IdNum=GetIdNum(iId);

				if (IdNum<ItemCount)
					IdArrSave[IdNum]=IdArr[IdNum];
			}
		}
	}

	const UINT GetCount()
	{
		return ItemCount;
	}

	UINT GetIdArray(UINT **oArray)
	{
		UINT ret=0;
		if (oArray && IdArr && ItemCount)
		{
			ret=ItemCount;
			*oArray=new UINT [ItemCount];
			UINT i;
			for(i=0;i<ItemCount;i++)
				(*oArray)[i]=IdArr[SeqArr[i]];
		}
		return ret;
	}

	UINT SetIdArray(UINT *iArray)
	{
		try
		{
			if (iArray)
			{
				UINT i;
				for(i=0;i<ItemCount;i++)
					IdArr[SeqArr[i]]=iArray[i];
			}
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("GP_RarefiedArr", "SetIdArray","");
		}
		return ItemCount;
	}

	UINT GetIdArraySave(UINT **oArray)
	{
		UINT ret=0;
		if (oArray && IdArrSave && ItemCount)
		{
			ret=ItemCount;
			*oArray=new UINT [ItemCount];
			UINT i;
			for(i=0;i<ItemCount;i++)
				(*oArray)[i]=IdArrSave[SeqArr[i]];
		}
		return ret;
	}

	UINT SetIdArraySave(UINT *iArray)
	{
		if (ItemCount)
		{
			try
			{
				if (IdArrSave==NULL) 
					SaveArrayId();

				if (iArray)
				{
					UINT i;
					for(i=0;i<ItemCount;i++)
						IdArrSave[SeqArr[i]]=iArray[i];
				}
			}
			catch(...)
			{
			GPC.m_ErrReport.GPWriteErrorLog("gp_rarefiedarr", "SetIdArraySave","");
			}
		}
		return ItemCount;
	}

	UINT GetSeqArray(UINT **oArray)
	{
		UINT ret=0;
		if (oArray && SeqArr && ItemCount)
		{
			ret=ItemCount;
			*oArray=new UINT [ItemCount];
			UINT i;
			for(i=0;i<ItemCount;i++)
				(*oArray)[i]=SeqArr[i];
		}
		return ret;
	}

	UINT SetSeqArray(UINT *iArray)
	{
		try
		{
			if (iArray)
			{
				UINT i;
				for(i=0;i<ItemCount;i++)
					IdArraySave[i]=iArray[i];
			}
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("gp_rarefiedarr", "SetSeqArray","");
		}
		return ItemCount;
	}


	void RestoreArrayId()
	{
		try
		{
			if (IdArrSave && ItemCount)
			{
				UINT i;
				for(i=0;i<ItemCount;i++)
					IdArr[i]=IdArrSave[i];
			}
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("gp_rarefiedarr", "RestoreArrayId","");
		}
	}

	void RestoreId(UINT iId, BOOL iBySavedId = FALSE)
	{
		if (IdArrSave && ItemCount)
		{
			try
			{
				UINT IdNum;
				if (iBySavedId)
					IdNum=GetSavedIdNum(iId);
				else
					IdNum=GetIdNum(iId);

				if (IdNum<ItemCount)
					IdArr[IdNum]=IdArrSave[IdNum];
			}
			catch(...)
			{
				GPC.m_ErrReport.GPWriteErrorLog("gp_rarefiedarr", "RestoreId","");
			}
		}
	}

	int ResetArray()
	{
		InitArray();
		return 0;
	}

	GP_RarefiedArr(int iSize,ArrType iInitValue)
	{
		ArrCount=iSize;
		InitValue=iInitValue;
		if (ArrCount<=10 || ArrCount>10000)  ArrCount=1000;
		SeqArr	=new UINT [ArrCount];
		IdArr	=new UINT [ArrCount];
		ArrTypeArray	=new ArrType [ArrCount];
		SeqArrVal=NULL;
		IdArrSave=NULL;
		InitArray();
	}

	GP_RarefiedArr()
	{
		ArrCount=5;
		SeqArr	=new UINT [ArrCount];
		IdArr	=new UINT [ArrCount];
		ArrTypeArray	=new ArrType [ArrCount];
		SeqArrVal=NULL;
		IdArrSave=NULL;
		InitArray();
	}


	~GP_RarefiedArr() 
		{
			DeleteArrays();
		}

	ArrType &operator[](int nItem)
	{
		if (nItem==-1) return InitValue;
		UINT Id=GetIdNum(nItem);
		if (Id==0xFFFFFFFFL) Id=ArrNewItem(nItem);
		if (Id==0xFFFFFFFFL) return InitValue;

		if (SeqArrVal) 
		{
			delete[] SeqArrVal;
			SeqArrVal=NULL;
		}

		return ArrTypeArray[Id];
	}

	ArrType & GetSelected()
	{
		if (Selection>ItemCount) return InitValue;
		return ArrTypeArray[Selection];
	}


	void CopyArray(const GP_RarefiedArr *iRA)
	{
		if (this!=iRA && iRA)
		{
			DeleteArrays();
			ArrCount=iRA->ArrCount;
			ItemCount=iRA->ItemCount;
			InitValue=iRA->InitValue;
			SeqArr	=new UINT [ArrCount];
			IdArr	=new UINT [ArrCount];
			ArrTypeArray	=new ArrType [ArrCount];
			SeqArrVal=NULL;
			IdArrSave=NULL;
			UINT i;
			for(i=0;i<ItemCount;i++)
			{
				SeqArr[i]=iRA->SeqArr[i];
				IdArr[i]=iRA->IdArr[i];
				ArrTypeArray[i]=iRA->ArrTypeArray[i];
			}

			for(;i<ArrCount;i++)
			{
				SeqArr[i]=i;
				IdArr[i]=0xFFFFFFFF;
				ArrTypeArray[i]=InitValue;
			}
		}
	}

	BOOL IsIdInArray(UINT iId)
	{
		return GetIdNum(iId)!=0xFFFFFFFFL;
	}

	UINT Find(ArrType iValue)
	{
		return GetIdByVal(iValue);
	}

protected:
	UINT Selection;
	UINT ItemCount;
	UINT ArrCount;
	UINT *SeqArr;
	UINT *SeqArrVal;
	ArrType *ArrTypeArray;
	ArrType InitValue;
	UINT *IdArr;
	UINT *IdArrSave;

	UINT GetIdNum(UINT iId)
	{
		UINT ret=0xFFFFFFFFL;
		switch(ItemCount)
		{
		case 1: if (iId==IdArr[SeqArr[0]]) ret=0;
		case 0: break;
		default:
			{
				int low=0,high=ItemCount-1,mid;
				while(low<=high)
				{
					mid=(low+high)/2;
					if (iId<IdArr[SeqArr[mid]]) high=mid-1;
					else 
						if (iId>IdArr[SeqArr[mid]]) low=mid+1;
						else {ret=SeqArr[mid];break;}
				}
			}
		}
		return ret;
	}

	UINT GetIdNum(UINT iId, UINT & SeqArrNum)
	{
		SeqArrNum=0xFFFFFFFFL;
		UINT ret=0xFFFFFFFFL;
		switch(ItemCount)
		{
		case 1: if (iId==IdArr[SeqArr[SeqArrNum=0]]) ret=0;
		case 0: break;
		default:
			{
				int low=0,high=ItemCount-1,mid;
				while(low<=high)
				{
					mid=(low+high)/2;
					if (iId<IdArr[SeqArr[mid]]) high=mid-1;
					else 
						if (iId>IdArr[SeqArr[mid]]) low=mid+1;
						else {ret=SeqArr[SeqArrNum=mid];break;}
				}
			}
		}
		return ret;
	}

	UINT GetSavedIdNum(UINT iId)
	{
		UINT ret=0xFFFFFFFFL;
		if (IdArrSave)
			switch(ItemCount)
			{
			case 1: if (iId==IdArrSave[SeqArr[0]]) ret=0;
			case 0: break;
			default:
				{
					int low=0,high=ItemCount-1,mid;
					while(low<=high)
					{
						mid=(low+high)/2;
						if (iId<IdArrSave[SeqArr[mid]]) high=mid-1;
						else 
							if (iId>IdArrSave[SeqArr[mid]]) low=mid+1;
							else {ret=SeqArr[mid];break;}
					}
				}
			}
		return ret;
	}

	UINT GetSavedIdNum(UINT iId, UINT & SeqArrNum)
	{
		SeqArrNum=0xFFFFFFFFL;
		UINT ret=0xFFFFFFFFL;
		if (IdArrSave)
			switch(ItemCount)
			{
			case 1: if (iId==IdArrSave[SeqArr[SeqArrNum=0]]) ret=0;
			case 0: break;
			default:
				{
					int low=0,high=ItemCount-1,mid;
					while(low<=high)
					{
						mid=(low+high)/2;
						if (iId<IdArrSave[SeqArr[mid]]) high=mid-1;
						else 
							if (iId>IdArrSave[SeqArr[mid]]) low=mid+1;
							else {ret=SeqArr[SeqArrNum=mid];break;}
					}
				}
			}
		return ret;
	}


	UINT ArrNewItem(UINT nItem)
	{
		if (SeqArrVal) 
		{
			delete[] SeqArrVal;
			SeqArrVal=NULL;
		}

		UINT i=0;
		if (ItemCount>=ArrCount)
		try
		{
			ArrCount=ArrCount+ArrCount/2+3;
			UINT *tmpSeqArr=new UINT [ArrCount];
			UINT *tmpIdArr=new UINT [ArrCount];
			ArrType *tmpArrTypeArray=new ArrType [ArrCount];

			try
			{
				for(i=0;i<ItemCount;i++) 
				{
					tmpSeqArr[i]=SeqArr[i];
					tmpIdArr[i]=IdArr[i];
					tmpArrTypeArray[i]=ArrTypeArray[i];
				}
			}
			catch(...)
			{
				GPC.m_ErrReport.GPWriteErrorLog("GP_RarefiedArr", "773","ArrNewItem");
			}

			try
			{
				for(;i<ArrCount;i++)
				{
					tmpIdArr[i]=0xFFFFFFFFL;
					tmpSeqArr[i]=i-ItemCount;
					tmpArrTypeArray[i]=InitValue;
				}
			}
			catch(...)
			{
				GPC.m_ErrReport.GPWriteErrorLog("GP_RarefiedArr", "787","ArrNewItem");
			}

			if (SeqArr) delete[] SeqArr;
			SeqArr=tmpSeqArr;
			if (IdArr) delete[] IdArr;
			IdArr=tmpIdArr;
			if (ArrTypeArray) delete[] ArrTypeArray;
			ArrTypeArray=tmpArrTypeArray;
		}
		catch(...)
		{
			GPC.m_ErrReport.GPWriteErrorLog("GP_RarefiedArr", "799","ArrNewItem");
		}

		UINT SeqIndex=0;
		
		SeqIndex=GetInsertionNum(nItem);

		IdArr[ItemCount]=nItem;
		for(i=ItemCount;i>SeqIndex;i--)
			SeqArr[i]=SeqArr[i-1];

		SeqArr[SeqIndex]=ItemCount;
		ArrTypeArray[SeqArr[SeqIndex]]=InitValue;

		ItemCount++;

		return ItemCount-1;
	}


protected:

	UINT GetInsertionNum(UINT iId)
	{
		UINT SeqIndex=ItemCount;

		switch(ItemCount)
		{
		case 1: if (iId>=IdArr[0]) {SeqIndex=1;break;};
		case 0: SeqIndex=0;	break;
		default:
			{
				int low=0,high=ItemCount-1,mid;
				mid=high;
				while(low<=high)
				{
					mid=(low+high)/2;
					if (iId<IdArr[SeqArr[mid]]) high=mid-1;
					else 
						if (iId>IdArr[SeqArr[mid]]) low=mid+1;
						else low=high=mid;
				}
				if (low>high) SeqIndex=low;
				else			 SeqIndex=high;
			}
		}
		return SeqIndex;
	}


	virtual void InitArray()
	{
		if (SeqArrVal) 
		{
			delete[] SeqArrVal;
			SeqArrVal=NULL;
		}
		if (IdArrSave) 
		{
			delete[] IdArrSave;
			IdArrSave=NULL;
		}

		UINT i;
		ItemCount=0;
		Selection=0xFFFFFFFFL;

		if (IdArr==NULL) IdArr	=new UINT [ArrCount];
		if (SeqArr==NULL) SeqArr	=new UINT [ArrCount];
		if (ArrTypeArray==NULL) ArrTypeArray	=new ArrType [ArrCount];

		for(i=0;i<ArrCount;i++) 
		{
			IdArr[i]=0xFFFFFFFFL;
			SeqArr[i]=i;
			ArrTypeArray[i]=InitValue;
		}
	}

};

#endif // !defined(AFX_GP_RAREFIEDARR_H__417283C1_B9B8_11D2_B27D_00600840D054__INCLUDED_)
