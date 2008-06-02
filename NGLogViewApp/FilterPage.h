#pragma once

#include "../Utility/CRegSetting.h"
// CFilterPage dialog

class CFilterPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CFilterPage)

public:
	CFilterPage();
	virtual ~CFilterPage();
	virtual BOOL OnInitDialog();
	virtual BOOL OnApply();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_FILTER };
	bool    m_bEnableEmptyString;
	wchar_t m_wszExcludeList[_MAX_PATH];
	wchar_t m_wszIncludeList[_MAX_PATH];

protected:
	CRegSetting* m_pRegSetting;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
};
