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
	m_bEnableEmptyString = false;
}

CFilterPage::~CFilterPage()
{
}

void CFilterPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFilterPage, CPropertyPage)
	ON_EN_CHANGE (IDC_EDIT_EXCLUDE, OnChange)
	ON_EN_CHANGE (IDC_EDIT_INCLUDE, OnChange)
	ON_BN_CLICKED (IDC_CHECK_EMPTY_STRING, OnChange)	
END_MESSAGE_MAP()


// CFilterPage message handlers
void CFilterPage::OnChange()
{
	//CString strExcludeList, strIncludeList;
	CString str1, str2;
	GetDlgItemText(IDC_EDIT_INCLUDE, str1);
	GetDlgItemText(IDC_EDIT_EXCLUDE, str2);
	
	ZeroMemory(m_wszIncludeList, sizeof(wchar_t)*_MAX_PATH);
	ZeroMemory(m_wszExcludeList, sizeof(wchar_t)*_MAX_PATH);

	wsprintf(m_wszIncludeList, TEXT("%s"), str1);
	wsprintf(m_wszExcludeList, TEXT("%s"), str2);
	
	CButton* pCheckBox = (CButton*)GetDlgItem(IDC_CHECK_EMPTY_STRING);
	if (pCheckBox->GetCheck() == BST_CHECKED)
		m_bEnableEmptyString = true;
	else
		m_bEnableEmptyString = false;
	
	dprintf(L"[FilterPage] IncludeList=%s\n", m_wszIncludeList);
	dprintf(L"[FilterPage] ExcludeList=%s\n", m_wszExcludeList);
	dprintf(L"[FilterPage] Enable Empty String=%s\n", (m_bEnableEmptyString) ? L"TRUE" : L"False");
	SetModified (TRUE);
}