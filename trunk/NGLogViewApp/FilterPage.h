#pragma once


// CFilterPage dialog

class CFilterPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CFilterPage)

public:
	CFilterPage();
	virtual ~CFilterPage();
	
// Dialog Data
	enum { IDD = IDD_PROPPAGE_FILTER };
	bool    m_bEnableEmptyString;
	wchar_t m_wszExcludeList[_MAX_PATH];
	wchar_t m_wszIncludeList[_MAX_PATH];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnChange();
	DECLARE_MESSAGE_MAP()
};
