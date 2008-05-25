#pragma once

#include "FilterPage.h"

// CNGPropertySheet 

class CNGPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CNGPropertySheet)

public:
	CNGPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CNGPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CNGPropertySheet();

protected:
	CFilterPage m_FilterPage;
	afx_msg void OnApply ();
	DECLARE_MESSAGE_MAP()
};


