#pragma once

#include "../Utility/CRegSetting.h"
// CFilterPage dialog

typedef struct tagPROPINFO {
	wchar_t wszExcludeList[_MAX_PATH];
	wchar_t wszIncludeList[_MAX_PATH];
	bool    bEnableEmptyString;
	bool    bEnableMatchCase;
	
	tagPROPINFO()
	{
		ZeroMemory(wszExcludeList, sizeof(wchar_t)*_MAX_PATH);
		ZeroMemory(wszIncludeList, sizeof(wchar_t)*_MAX_PATH);
		bEnableEmptyString = false;
		bEnableMatchCase = false;
	}

} PROPINFO;

class CFilterPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CFilterPage)

public:
	CFilterPage();
	virtual ~CFilterPage();
	virtual BOOL OnInitDialog();
	virtual BOOL OnApply();
	
	void SyncDataFromUIToDataStructByCheckBox(int nId, bool &bOutput);
	void SetDlgItemCheck(int nID, bool bInput);
// Dialog Data
	enum { IDD = IDD_PROPPAGE_FILTER };

	PROPINFO m_PropInfo;


protected:
	CRegSetting* m_pRegSetting;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
};
