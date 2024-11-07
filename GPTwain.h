#pragma once
#include "TwainCpp.h"

// CGPTwain command target

class CGPTwain : public CObject,public CTwain
{
friend class CDlgViewSystemMethods;
public:
	CGPTwain();
	DECLARE_DYNAMIC( CGPTwain )

	void CopyImage(HANDLE hBitmap,TW_IMAGEINFO& info);


public:
// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	virtual ~CGPTwain();

};


