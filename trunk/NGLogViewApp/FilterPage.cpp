// FilterPage.cpp : implementation file
//

#include "stdafx.h"
#include "NGLogViewApp.h"
#include "FilterPage.h"
DWORD DWLISTCOLOR[40] =
{
	0xFFFFFF,
	0xFF    ,
	0xFFFFFF,
	0xFF0080,
	0xFFFFFF,
	0x4080FF,
	0xFFFFFF,
	0x808040,
	0xFFFFFF,
	0xFF8000,
	0x0     ,
	0xFF8080,
	0x0     ,
	0x80FF80,
	0x0     ,
	0xFFFF80,
	0x0     ,
	0x80FF80,
	0x0     ,
	0x80FFFF,
	0xFFFFFF,
	0xFF    ,
	0xFFFFFF,
	0xFF0080,
	0xFFFFFF,
	0x4080FF,
	0xFFFFFF,
	0x808040,
	0xFFFFFF,
	0xFF8000,
	0x0     ,
	0xFF8080,
	0x0     ,
	0x80FF80,
	0x0     ,
	0xFFFF80,
	0x0     ,
	0x80FF80,
	0x0     ,
	0x80FFFF,
};
// CFilterPage dialog
#define APP_SETTING_PATH (L"SOFTWARE\\NG\\LOGViewer")


IMPLEMENT_DYNAMIC(CFilterPage, CPropertyPage)

CFilterPage::CFilterPage()
	: CPropertyPage(CFilterPage::IDD)
{
	m_pRegSetting = NULL;
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
	m_pRegSetting = new CRegSetting(APP_SETTING_PATH);
	// 1. Load m_PropInfo from reg key
	m_pRegSetting->ReadRegKey(L"ExcludeList", _MAX_PATH, m_PropInfo.wszExcludeList);
	m_pRegSetting->ReadRegKey(L"IncludeList", _MAX_PATH, m_PropInfo.wszIncludeList);
	m_pRegSetting->ReadRegKey(L"EnableEmptyString", m_PropInfo.bEnableEmptyString);
	m_pRegSetting->ReadRegKey(L"EnableMatchCase", m_PropInfo.bEnableMatchCase);

	// 2. Set m_PropInfo into UI
	SetDlgItemText(IDC_EDIT_EXCLUDE, m_PropInfo.wszExcludeList);
	SetDlgItemText(IDC_EDIT_INCLUDE, m_PropInfo.wszIncludeList);
	SetDlgItemCheck(IDC_CHECK_EMPTY_STRING, m_PropInfo.bEnableEmptyString);
	SetDlgItemCheck(IDC_CHECK_MATCH_CASE, m_PropInfo.bEnableMatchCase);

	//2. Set HighLight 20 items
	CComboBox *pComboBox = (CComboBox *) GetDlgItem(IDC_COMBO_HIGHLIGHT);
	for (int i =0;i<20; i++)
	{
		wchar_t wszString [256];
		wsprintf(wszString, L"Filter %d", i+1);
		pComboBox->AddString(wszString);
	}
	m_nEditNowSelect =0;
	pComboBox->SetCurSel(0);
	pComboBox->SetWindowText(m_wstrHighlight[m_nEditNowSelect].c_str());
	return TRUE;

}

BOOL CFilterPage::OnApply()
{
	CString str1, str2;
	GetDlgItemText(IDC_EDIT_INCLUDE, str1);
	GetDlgItemText(IDC_EDIT_EXCLUDE, str2);

	wsprintf(m_PropInfo.wszIncludeList, TEXT("%s"), str1);
	wsprintf(m_PropInfo.wszExcludeList, TEXT("%s"), str2);

	SyncDataFromUIToDataStructByCheckBox(IDC_CHECK_EMPTY_STRING, m_PropInfo.bEnableEmptyString);
	SyncDataFromUIToDataStructByCheckBox(IDC_CHECK_MATCH_CASE, m_PropInfo.bEnableMatchCase);
	
	dprintf(L"[FilterPage] IncludeList=%s\n", m_PropInfo.wszIncludeList);
	dprintf(L"[FilterPage] ExcludeList=%s\n", m_PropInfo.wszExcludeList);
	dprintf(L"[FilterPage] Enable Empty String=%s\n", (m_PropInfo.bEnableEmptyString) ? L"true" : L"false");
	dprintf(L"[FilterPage] Enable Match Case=%s\n",  (m_PropInfo.bEnableMatchCase) ? L"true" : L"false");
	
	m_pRegSetting->WriteRegKey(L"ExcludeList", m_PropInfo.wszExcludeList);
	m_pRegSetting->WriteRegKey(L"IncludeList", m_PropInfo.wszIncludeList);
	m_pRegSetting->WriteRegKey(L"EnableEmptyString", m_PropInfo.bEnableEmptyString);
	m_pRegSetting->WriteRegKey(L"EnableMatchCase", m_PropInfo.bEnableMatchCase);

	RefreshHighLightData();

	SetModified (TRUE);
	return TRUE;
}

void CFilterPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}

void CFilterPage::SyncDataFromUIToDataStructByCheckBox(int nId, bool &bOutput)
{
	CButton* pCheckBox = (CButton*)GetDlgItem(nId);
	if (pCheckBox->GetCheck() == BST_CHECKED)
		bOutput = true;
	else
		bOutput = false;
}

void CFilterPage::SetDlgItemCheck(int nID, bool bInput)
{
	CButton* btnCheckBox = (CButton*)GetDlgItem(nID);
	if (bInput)
		btnCheckBox->SetCheck(BST_CHECKED);
	else
		btnCheckBox->SetCheck(BST_UNCHECKED);
}


BEGIN_MESSAGE_MAP(CFilterPage, CPropertyPage)
	ON_CBN_SELCHANGE(IDC_COMBO_HIGHLIGHT, &CFilterPage::OnCbnSelchangeComboHighlight)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CFilterPage message handlers

void CFilterPage::OnCbnSelchangeComboHighlight()
{
	CComboBox *pComboHighlight = (CComboBox*)GetDlgItem(IDC_COMBO_HIGHLIGHT);
	CEdit *pEditHighlight = (CEdit*)GetDlgItem(IDC_EDIT_HIGHLIGHT);

	RefreshHighLightData();
	
	int nSelect = pComboHighlight->GetCurSel();
	if (CB_ERR!= nSelect)
	{
		m_nEditNowSelect = nSelect;
		pEditHighlight->SetWindowText(m_wstrHighlight[nSelect].c_str());
	}
}

void CFilterPage::RefreshHighLightData()
{
	CString cstr;
	GetDlgItemText(IDC_EDIT_HIGHLIGHT, cstr);
	wchar_t *wszText = new wchar_t[cstr.GetLength()+1];
	wsprintf(wszText, TEXT("%s"), cstr);
	m_wstrHighlight[m_nEditNowSelect] = wszText;
	delete [] wszText;
}

HBRUSH CFilterPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if ((pWnd->GetDlgCtrlID() == IDC_EDIT_HIGHLIGHT) && (nCtlColor == CTLCOLOR_EDIT))
	{   
		CEdit *pEditHighlight = (CEdit*)GetDlgItem(IDC_EDIT_HIGHLIGHT);
		COLORREF dwTextColor;
		COLORREF dwBkColor;
		CComboBox *pComboBox = (CComboBox *) GetDlgItem(IDC_COMBO_HIGHLIGHT);
		int nCurrent = pComboBox->GetCurSel();
		dwTextColor = (COLORREF)DWLISTCOLOR[nCurrent*2];
		dwBkColor = (COLORREF)DWLISTCOLOR[nCurrent*2+1];
		pDC->SetTextColor(dwTextColor);          
		pDC->SetBkColor(dwBkColor);
		m_brMine = ::CreateSolidBrush(dwBkColor);   
		return   m_brMine;       
	} 
	else if ((pWnd->GetDlgCtrlID() == IDC_COMBO_HIGHLIGHT) )
	{
		CEdit *pEditHighlight = (CEdit*)GetDlgItem(IDC_EDIT_HIGHLIGHT);
		HBRUSH   hbr   =   CDialog::OnCtlColor(pDC,   pWnd,   nCtlColor);   
		return   hbr;   
	}
	else   
	{   
		HBRUSH   hbr   =   CDialog::OnCtlColor(pDC,   pWnd,   nCtlColor);   
		return   hbr;   
	}   

}

std::map<std::wstring, COLORPAIR> CFilterPage::GetMapStringToColors()
{
	std::map<std::wstring, COLORPAIR> mapRet;

	for (int i=0;i<MAX_HIGHLIGHT_FILTER;++i)
	{
		wstring wstr = this->m_wstrHighlight[i];
		if (wstr.length()==0)
			continue;
		COLORPAIR colors;
		colors.m_cBkColor = (COLORREF)DWLISTCOLOR[i*2+1];
		colors.m_cTextColor = (COLORREF)DWLISTCOLOR[i*2];

		const wchar_t *wstrKeyWords;
		wstrKeyWords = wstr.c_str();
		wchar_t *pwszBuffer = new wchar_t [wcslen(wstrKeyWords)+1];

		wcscpy(pwszBuffer, wstrKeyWords);

		wchar_t wszDelims[] = L";";
		wchar_t *result = NULL;
		result = wcstok(pwszBuffer, wszDelims );
		while (result != NULL)
		{
			mapRet[result] = colors;
			result = wcstok(NULL, wszDelims);
		}
		delete [] pwszBuffer;
		pwszBuffer = NULL;
	}
	return mapRet;
}