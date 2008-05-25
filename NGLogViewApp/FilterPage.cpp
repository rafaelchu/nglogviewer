// FilterPage.cpp : implementation file
//

#include "stdafx.h"
#include "NGLogViewApp.h"
#include "FilterPage.h"


// CFilterPage dialog

IMPLEMENT_DYNAMIC(CFilterPage, CPropertyPage)

CFilterPage::CFilterPage()
	: CPropertyPage(CFilterPage::IDD)
{
	m_strExcludeList = _T("");
	m_strIncludeList = _T("");
}

CFilterPage::~CFilterPage()
{
}

void CFilterPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_EXCLUDE, m_strExcludeList);
	DDX_Text(pDX, IDC_EDIT_INCLUDE, m_strIncludeList);

}


BEGIN_MESSAGE_MAP(CFilterPage, CPropertyPage)
END_MESSAGE_MAP()


// CFilterPage message handlers
