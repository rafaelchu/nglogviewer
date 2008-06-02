// FilterPage.cpp : implementation file
//

#include "stdafx.h"
#include "NGLogViewApp.h"
#include "FilterPage.h"

// CFilterPage dialog
#define APP_SETTING_PATH (L"SOFTWARE\\NG\\LOGViewer")


IMPLEMENT_DYNAMIC(CFilterPage, CPropertyPage)

CFilterPage::CFilterPage()
	: CPropertyPage(CFilterPage::IDD)
{
	ZeroMemory(m_wszExcludeList, sizeof(wchar_t)*_MAX_PATH);
	ZeroMemory(m_wszIncludeList, sizeof(wchar_t)*_MAX_PATH);
	m_pRegSetting = NULL;
	m_bEnableEmptyString = false;
}

CFilterPage::~CFilterPage()
{
	if(m_pRegSetting)
	{
		delete m_pRegSetting;
		m_pRegSetting = NULL;
	}
}
BOOL CFilterPage::OnInitDialog()
{
	wchar_t wszExclude[_MAX_PATH];
	wchar_t wszInclude[_MAX_PATH];
	DWORD dwVal = 0;

	ZeroMemory(wszExclude, sizeof(wchar_t)*_MAX_PATH);
	ZeroMemory(wszInclude, sizeof(wchar_t)*_MAX_PATH);
	m_pRegSetting = new CRegSetting(APP_SETTING_PATH);
	m_pRegSetting->ReadRegKey(L"ExcludeList", _MAX_PATH, wszExclude);
	m_pRegSetting->ReadRegKey(L"IncludeList", _MAX_PATH, wszInclude);
	m_pRegSetting->ReadRegKey(L"EnableEmptyString", dwVal);
	
	wcscpy(m_wszExcludeList, wszExclude);
	wcscpy(m_wszIncludeList, wszInclude);
	if(dwVal > 0)
		m_bEnableEmptyString = TRUE;
	else
		m_bEnableEmptyString = FALSE;
	
	SetDlgItemText(IDC_EDIT_EXCLUDE, m_wszExcludeList);
	SetDlgItemText(IDC_EDIT_INCLUDE, m_wszIncludeList);
	CButton* btnCheckBox = (CButton*)GetDlgItem(IDC_CHECK_EMPTY_STRING);
	if (m_bEnableEmptyString)
		btnCheckBox->SetCheck(BST_CHECKED);
	else
		btnCheckBox->SetCheck(BST_UNCHECKED);
	return TRUE;

}
BOOL CFilterPage::OnApply()
{
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
	
	m_pRegSetting->WriteRegKey(L"ExcludeList", m_wszExcludeList);
	m_pRegSetting->WriteRegKey(L"IncludeList", m_wszIncludeList);
	m_pRegSetting->WriteRegKey(L"EnableEmptyString", m_bEnableEmptyString);

	SetModified (TRUE);
	return TRUE;
}
void CFilterPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFilterPage, CPropertyPage)
END_MESSAGE_MAP()


// CFilterPage message handlers
