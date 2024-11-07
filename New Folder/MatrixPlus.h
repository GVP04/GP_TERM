// MatrixPlus.h: interface for the CMatrixPlus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MatrixPlus_H__60A8D5E1_A0FB_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_MatrixPlus_H__60A8D5E1_A0FB_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CODContext;

class CMatrixPlus
{
public:
	Matrix *m_Matrix;
	DWORD m_dwType;
	virtual UINT DoMethod(const char *iStr, char *oStr);
	const static UINT uNMethods;
	const static char *cArrMethods[];
	const static char *cArrMethodsParams[];

	const static char *ccAMatrixOrder[];
	const static MatrixOrder iAMatrixOrder[];

	CODContext *p_Context;
	virtual ~CMatrixPlus();
	CMatrixPlus(CODContext *ip_Context, const RectF &rect, const PointF *dstplg);
	CMatrixPlus(CODContext *ip_Context, REAL m11, REAL m12, REAL m21, REAL m22, REAL dx, REAL dy);
	CMatrixPlus(CODContext *ip_Context, Matrix *ClonedMatrix);
	CMatrixPlus(CODContext *ip_Context, const char *ccMatrixDescription);
	CString CreationString;
	const Matrix *SetMatrix(Matrix *pMatrix);
};

#endif // !defined(AFX_MatrixPlus_H__60A8D5E1_A0FB_11D4_970E_0080AD863699__INCLUDED_)
