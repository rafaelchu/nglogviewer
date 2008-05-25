// NGProperties.cpp : implementation file
//

#include "stdafx.h"
#include "NGLogViewApp.h"
#include "NGPropertySheet.h"
#include "../Utility/Debug.h"

// CNGProperties

IMPLEMENT_DYNAMIC(CNGPropertySheet, CPropertySheet)

CNGPropertySheet::CNGPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_FilterPage);
}

CNGPropertySheet::CNGPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_FilterPage);
}

CNGPropertySheet::~CNGPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CNGPropertySheet, CPropertySheet)
END_MESSAGE_MAP()


// CNGProperties message handlers
void CNGPropertySheet::OnApply ()
{
	
	
}