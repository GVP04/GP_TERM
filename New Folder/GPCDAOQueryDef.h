// GPCDAOQueryDef.h: interface for the GPCDAOQueryDef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPCDAOQUERYDEF_H__91EB9C8D_6F93_11D4_970E_0080AD863699__INCLUDED_)
#define AFX_GPCDAOQUERYDEF_H__91EB9C8D_6F93_11D4_970E_0080AD863699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4995)

class GPCDAOQueryDef : public CDaoQueryDef  
{
friend class CGP_TermDoc;
public:
	void GPClose();
	BOOL GPIsOpen();
	GPCDAOQueryDef(CDaoDatabase* pDatabase);
	virtual ~GPCDAOQueryDef();
	static void GetPIString(CDaoParameterInfo &pinfo, char *oStrInfo);
	BOOL GPOpen(const char *iStr);
	BOOL GPCreate(const char *iStr);
	int DoMethod(const char *iMethod, char *oStr);

};

#endif // !defined(AFX_GPCDAOQUERYDEF_H__91EB9C8D_6F93_11D4_970E_0080AD863699__INCLUDED_)
