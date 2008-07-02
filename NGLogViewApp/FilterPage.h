#pragma once

#include "../Utility/CRegSetting.h"
#include "ColorPair.h"
#include <map>
#include <string>
using namespace std;
// CFilterPage dialog
#define MAX_HIGHLIGHT_FILTER 20
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
	HBRUSH   m_brMine;
	wstring m_wstrHighlight[MAX_HIGHLIGHT_FILTER];
	void RefreshHighLightData();
	map<wstring,  COLORPAIR> GetMapStringToColors();
	int m_nEditNowSelect;

protected:
	CRegSetting* m_pRegSetting;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboHighlight();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
