// NGProperties.cpp : implementation file
//

#include "stdafx.h"
#include "NGLogViewApp.h"
#include "NGLogViewAppView.h"
#include "NGPropertySheet.h"

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
	GetActivePage ()->UpdateData (TRUE);

	PROPINFO props;
	props.bEnableEmptyString = m_FilterPage.m_bEnableEmptyString;
	wcscpy(props.wszExcludeList, m_FilterPage.m_wszExcludeList);
	wcscpy(props.wszIncludeList, m_FilterPage.m_wszIncludeList);

	GetParent ()->SendMessage (WM_USER_APPLY, 0, (LPARAM) &props);

	m_FilterPage.SetModified (FALSE);
}