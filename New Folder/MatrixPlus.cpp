// MatrixPlus.cpp: implementation of the CMatrixPlus class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gp_term.h"
#include "MatrixPlus.h"
#include "GP_TermView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//const char *CMatrixPlus::ccA[]={"","","","",};
//const xxxx CMatrixPlus::iA[]={,,,,};

const char *CMatrixPlus::ccAMatrixOrder[]={
	"Prepend","Append",
	"MatrixOrderPrepend","MatrixOrderAppend",
	"",};
const MatrixOrder CMatrixPlus::iAMatrixOrder[]={
	MatrixOrderPrepend,MatrixOrderAppend,
	MatrixOrderPrepend,MatrixOrderAppend,
	MatrixOrderPrepend};

const UINT CMatrixPlus::uNMethods=18;
const char *CMatrixPlus::cArrMethods[]={
/*00*/		"Equals","GetElements","GetLastStatus","Invert","IsIdentity",
/*05*/		"IsInvertible","Multiply","OffsetX","OffsetY","Reset",
/*10*/		"Rotate","RotateAt","Scale","SetElements","Shear",
/*15*/		"TransformPoints","TransformVectors","Translate","","",
/*20*/		"","","","","",
/*25*/		"","","","","",
/*30*/		"","","","","",
/*35*/		"","","","","",
	};
const char *CMatrixPlus::cArrMethodsParams[]={
/*00*/		"Context,nMatrix","","","","",
/*05*/		"","Context,nMatrix,MatrixOrder","","","",
/*10*/		"angle,MatrixOrder","angle,MatrixOrder,POINT","scaleX,scaleY,MatrixOrder","m11,m12,m21,m22,dx,dy","shearX,shearY,MatrixOrder",
/*15*/		"Context,nPoint,Count","Context,nPoint,Count","offsetX,offsetY,MatrixOrder","","",
/*20*/		"","","","","",
/*25*/		"","","","","",
/*30*/		"","","","","",
/*35*/		"","","","","",
	};


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMatrixPlus::~CMatrixPlus()
{
	if (m_Matrix) delete m_Matrix;
	m_Matrix=NULL;
}

CMatrixPlus::CMatrixPlus(CODContext *ip_Context, const RectF &rect, const PointF *dstplg)
{
	p_Context=ip_Context;
	m_Matrix=new Matrix(rect, dstplg);
	m_dwType=0;
}
CMatrixPlus::CMatrixPlus(CODContext *ip_Context, REAL m11, REAL m12, REAL m21, REAL m22, REAL dx, REAL dy)
{
	p_Context=ip_Context;
	m_Matrix=new Matrix(m11, m12, m21, m22, dx, dy);
	m_dwType=1;
}

CMatrixPlus::CMatrixPlus(CODContext *ip_Context, const char *ccMatrixDescription)
{
	p_Context=ip_Context;
	if (ccMatrixDescription && *ccMatrixDescription)
	{
		REAL mReal[6]={1,0,0,1,0,0};
		const char *pStr=ccMatrixDescription;
		int nParams=1;
		while(*pStr) if (*(pStr++)==',') nParams++;
		switch(nParams)
		{
		case 1://nMatrix
			{
				UINT nMat=atoi(ccMatrixDescription);
				if (nMat<p_Context->m_nMatrixArray && p_Context->m_MatrixArr[nMat] && p_Context->m_MatrixArr[nMat]->m_Matrix)
					p_Context->m_MatrixArr[nMat]->m_Matrix->GetElements(mReal);
			}
			break;
		case 2://Context,nMatrix
			{
				CString ContName=ExtractField(ccMatrixDescription,1,",");
				CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
				UINT nMat=atoi(ExtractField(ccMatrixDescription,2,","));
				if (nMat < ocontext->m_nMatrixArray && ocontext->m_MatrixArr[nMat] && ocontext->m_MatrixArr[nMat]->m_Matrix)
					ocontext->m_MatrixArr[nMat]->m_Matrix->GetElements(mReal);
			}
		case 6://m11, &m12, &m21, &m22, &dx, &dy
			sscanf(ccMatrixDescription,"%g,%g,%g,%g,%g,%g",mReal, mReal+1, mReal+2, mReal+3, mReal+4, mReal+5);
			break;
		default:
			break;
		}
		m_Matrix=new Matrix(mReal[0], mReal[1], mReal[2], mReal[3], mReal[4], mReal[5]);
	}
	else m_Matrix=new Matrix;

	m_dwType=1;
}

CMatrixPlus::CMatrixPlus(CODContext *ip_Context, Matrix *ClonedMatrix)
{
	p_Context=ip_Context;
	m_Matrix=ClonedMatrix;
	m_dwType=1;
}
UINT CMatrixPlus::DoMethod(const char *iStr, char *oStr)
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
	case  0: //Equals Context,nMatrix
		if (oStr)
		{
			retint=0;
			CString ContName=ExtractField(pos,1,",");
			CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
			UINT nMat=atoi(ExtractField(pos,2,","));
			if (nMat < ocontext->m_nMatrixArray && ocontext->m_MatrixArr[nMat] && ocontext->m_MatrixArr[nMat]->m_Matrix)
				retint=m_Matrix->Equals(ocontext->m_MatrixArr[nMat]->m_Matrix);
		}
		break; 
	case  1: //GetElements
		if (oStr)
		{
			REAL mReal[6]={0,0,0,0,0,0};
			m_Matrix->GetElements(mReal);
			sprintf(oStr,"%g\x7F%g\x7F%g\x7F%g\x7F%g\x7F%g",mReal[0], mReal[1], mReal[2], mReal[3], mReal[4], mReal[5]);
		}
		break; 
	case  2: //GetLastStatus
		retint=m_Matrix->GetLastStatus();
		break; 
	case  3: //Invert
		retint=m_Matrix->Invert();
		break; 
	case  4: //IsIdentity
		retint=m_Matrix->IsIdentity();
		break; 
	case  5: //IsInvertible
		retint=m_Matrix->IsInvertible();
		break; 
	case  6: //Multiply Context,nMatrix,MatrixOrder
		{
			retint=0;
			CString tmpSC=ExtractField(pos,3,",");
			MatrixOrder mo=(MatrixOrder)atoi(tmpSC);
			if (mo==MatrixOrderPrepend && tmpSC[0]!='0')
			{
				int i;
				for(i=0;*CMatrixPlus::ccAMatrixOrder[i] && _stricmp(CMatrixPlus::ccAMatrixOrder[i],tmpSC)!=0;i++);
				mo=CMatrixPlus::iAMatrixOrder[i];
			}
			CString ContName=ExtractField(pos,1,",");
			CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
			UINT nMat=atoi(ExtractField(pos,2,","));
			if (nMat < ocontext->m_nMatrixArray && ocontext->m_MatrixArr[nMat] && ocontext->m_MatrixArr[nMat]->m_Matrix)
				retint=m_Matrix->Multiply(ocontext->m_MatrixArr[nMat]->m_Matrix,mo);
		}
		break; 
	case  7: //OffsetX
		if (oStr) sprintf(oStr,"%g",m_Matrix->OffsetX());
		break; 
	case  8: //OffsetY
		if (oStr) sprintf(oStr,"%g",m_Matrix->OffsetY());
		break; 
	case  9: //Reset
		retint=m_Matrix->Reset();
		break; 
	case 10: //Rotate angle,MatrixOrder
		{
			REAL angle=(REAL)atof(pos);
			const char *pos2=FindField(pos,2,",");
			MatrixOrder mo=MatrixOrderPrepend;
			if (pos2 && *pos2 && (mo=(MatrixOrder)atoi(pos2))==MatrixOrderPrepend && *pos2!='0')
			{
				int i;
				for(i=0;*CMatrixPlus::ccAMatrixOrder[i] && _stricmp(CMatrixPlus::ccAMatrixOrder[i],pos2)!=0;i++);
				mo=CMatrixPlus::iAMatrixOrder[i];
			}
			retint=0;
			retint=m_Matrix->Rotate(angle,mo);
		}
		break; 
	case 11: //RotateAt angle,MatrixOrder,POINT
		{
			REAL angle=(REAL)atof(pos);
			const char *pos2=FindField(pos,2,",");
			MatrixOrder mo=MatrixOrderPrepend;
			if (pos2 && *pos2 && (mo=(MatrixOrder)atoi(pos2))==MatrixOrderPrepend && *pos2!='0')
			{
				int i;
				for(i=0;*CMatrixPlus::ccAMatrixOrder[i] && _stricmp(CMatrixPlus::ccAMatrixOrder[i],pos2)!=0;i++);
				mo=CMatrixPlus::iAMatrixOrder[i];
			}
			CString ContName=ExtractField(pos,3,",");
			CString CSPoint=ExtractField(pos,4,",");
			PointF po;
			if (CSPoint=="")
			{
				UINT nPoint=atoi(ContName);
				if (nPoint < p_Context->m_nPointArray) po=p_Context->m_PointArr[nPoint];
			}
			else
			if (ContName[0]>='0' && ContName[0]<='9')
			{
				po.X=(REAL)atof(ContName);
				po.Y=(REAL)atof(CSPoint);
			}
			else
			{
				UINT nPoint=atoi(CSPoint);
				CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
				if (nPoint < ocontext->m_nPointArray)
					po=ocontext->m_PointArr[nPoint];
			}
			retint=m_Matrix->RotateAt(angle,po,mo);
		}
		break; 
	case 12: //Scale scaleX,scaleY,MatrixOrder
	case 14: //Shear shearX,shearY,MatrixOrder
	case 17: //Translate offsetX,offsetY,MatrixOrder
		{
			REAL scaleX=1,scaleY=1;
			sscanf(pos,"%g,%g",&scaleX,&scaleY);
			const char *pos2=FindField(pos,3,",");
			MatrixOrder mo=MatrixOrderPrepend;
			if (pos2 && *pos2 && (mo=(MatrixOrder)atoi(pos2))==MatrixOrderPrepend && *pos2!='0')
			{
				int i;
				for(i=0;*CMatrixPlus::ccAMatrixOrder[i] && _stricmp(CMatrixPlus::ccAMatrixOrder[i],pos2)!=0;i++);
				mo=CMatrixPlus::iAMatrixOrder[i];
			}
			switch(nfunc)
			{
			case 12: //Scale scaleX,scaleY,MatrixOrder
				retint=m_Matrix->Scale(scaleX,scaleY,mo);
				break; 
			case 14: //Shear shearX,shearY,MatrixOrder
				retint=m_Matrix->Shear(scaleX,scaleY,mo);
				break; 
			case 17: //Translate offsetX,offsetY,MatrixOrder
				retint=m_Matrix->Translate(scaleX,scaleY,mo);
				break; 
			}
		}
		break; 
	case 13: //SetElements m11,m12,m21,m22,dx,dy
		{
			REAL rea[6]={0,0,0,0,0,0,};
			sscanf(pos,"%g,%g,%g,%g,%g,%g",rea,rea+1,rea+2,rea+3,rea+4,rea+5);
			retint=m_Matrix->SetElements(rea[0],rea[1],rea[2],rea[3],rea[4],rea[5]);
		}
		break; 
	case 15: //TransformPoints Context,nPoint,Count
	case 16: //TransformVectors Context,nPoint,Count
		{
			UINT nCount=atoi(ExtractField(pos,3,","));
			retint=0;
			if (nCount>0)
			{
				CString ContName=ExtractField(pos,1,",");
				UINT nPoint=atoi(ExtractField(pos,2,","));
				CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
				if (nPoint < ocontext->m_nPointArray)
				{
					if (nPoint+nCount>=ocontext->m_nPointArray) nCount=ocontext->m_nPointArray-nPoint;
					if (nfunc==15)	retint=m_Matrix->TransformPoints(ocontext->m_PointArr+nPoint,nCount);
					else			retint=m_Matrix->TransformVectors(ocontext->m_PointArr+nPoint,nCount);
				}
			}
		}
		break; 

	default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
	}
	if (oStr && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);

	return nfunc;
}


const Matrix *CMatrixPlus::SetMatrix(Matrix *pMatrix)
{
	if (pMatrix)
	{
		if (m_Matrix) delete m_Matrix;
		m_Matrix=pMatrix;
	}
	return m_Matrix;
}