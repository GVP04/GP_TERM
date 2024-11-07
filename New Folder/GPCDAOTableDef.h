// GPCDAOTableDef.h: interface for the GPCDAOTableDef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPCDAOTABLEDEF_H__91EB9C8B_6F93_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_GPCDAOTABLEDEF_H__91EB9C8B_6F93_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4995)

class GPCDAOTableDef : public CDaoTableDef  
{
friend class CGP_TermDoc;
public:
	void GPClose();
	BOOL GPIsOpen();
	GPCDAOTableDef(CDaoDatabase* pDatabase);
	virtual ~GPCDAOTableDef();

	BOOL GPOpen(const char *iStr);
	BOOL GPCreate(const char *iStr);
	int DoMethod(const char *iMethod, char *oStr);

};

#endif // !defined(AFX_GPCDAOTABLEDEF_H__91EB9C8B_6F93_11D4_970E_0080AD863699__INCLUDED_)
