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
	CString m_strExcludeList;
	CString m_strIncludeList;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
};
