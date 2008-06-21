#include "CRegSetting.h"

CRegSetting::CRegSetting(const wchar_t *wszPath, HKEY hKeyRoot /* = HKEY_CURRENT_USER */)
{
	DWORD dw;
	LONG ReturnValue = RegCreateKeyEx (hKeyRoot, wszPath, 0L, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, 
		&m_hKey, &dw);
	RegCloseKey(m_hKey);
	ReturnValue = RegOpenKeyEx (hKeyRoot, wszPath, 0L, KEY_ALL_ACCESS, &m_hKey);

}

CRegSetting::~CRegSetting()
{
	RegCloseKey(m_hKey);

}

bool CRegSetting::WriteRegKey(const wchar_t *wszName, DWORD dwInput)
{
	DWORD dwValue;
	dwValue = (DWORD)dwInput;
	LONG ReturnValue = RegSetValueExW (m_hKey, wszName, 0L, REG_DWORD,
		(CONST BYTE*) &dwValue, sizeof(DWORD));

	if(ReturnValue == ERROR_SUCCESS)
		return true;

	return false;
}

bool CRegSetting::WriteRegKey(const wchar_t *wszName, const wchar_t *wszValue)
{
	LONG ReturnValue = RegSetValueExW (m_hKey, wszName, 0L, REG_SZ,
		(CONST BYTE*) wszValue, (wcslen(wszValue) + 1)*sizeof(wchar_t));
	if(ReturnValue == ERROR_SUCCESS)
		return true;
	return false;
}

bool CRegSetting::WriteRegKey(const wchar_t *wszName, int nSize, const BYTE *bytedata)
{
	if (bytedata==NULL) return false;
	LONG lReturn = RegSetValueExW(m_hKey, wszName, 0, REG_BINARY,
		bytedata, nSize);
	if(lReturn == ERROR_SUCCESS)
		return true;
	return false;
}

bool CRegSetting::ReadRegKey(const wchar_t *wszName, int nSize, BYTE *bytedata)
{
	DWORD dwType=REG_BINARY;
	DWORD dwSize = 0;
	LONG lReturn = RegQueryValueExW(m_hKey, wszName, NULL, &dwType, NULL, &dwSize);
	if ( (lReturn == ERROR_SUCCESS) && (dwSize<=nSize))
	{
		lReturn = RegQueryValueExW(m_hKey, wszName, NULL, &dwType, bytedata, &dwSize);
		if(lReturn == ERROR_SUCCESS)
			return true;
		return false;
	}
	else 
	{
		return false;
	}
}

bool CRegSetting::ReadRegKey(const wchar_t *wszName, DWORD &dwInput)
{
	DWORD dwType;
	DWORD dwSize = sizeof (DWORD);
	DWORD dwDest;

	LONG lReturn = RegQueryValueExW (m_hKey, wszName, NULL,
		&dwType, (BYTE *) &dwDest, &dwSize);

	if(lReturn == ERROR_SUCCESS)
	{
		dwInput = (DWORD)dwDest;
		return true;
	}
	return false;
}

bool CRegSetting::ReadRegKey(const wchar_t *wszName, int nSize, wchar_t *wszValue)
{
	DWORD dwType;
	DWORD dwSize = nSize;
	LONG lReturn = RegQueryValueExW (m_hKey, wszName, NULL,
		&dwType, (BYTE *) wszValue, &dwSize);

	if(lReturn == ERROR_SUCCESS)
	{
		return true;
	}
	
	return false;
}

bool CRegSetting::ReadRegKey(const wchar_t *wszName, bool &bInput)
{
	DWORD dwType;
	DWORD dwSize = sizeof (DWORD);
	DWORD dwDest;

	LONG lReturn = RegQueryValueExW (m_hKey, wszName, NULL,
		&dwType, (BYTE *) &dwDest, &dwSize);

	if(lReturn == ERROR_SUCCESS)
	{
		if (dwDest >0)
			bInput = true;
		else
			bInput = false;
		return true;
	}
	return false;
}

bool CRegSetting::WriteRegKey(const wchar_t *wszName, bool bInput)
{
	DWORD dwValue;
	if (bInput)
		dwValue = (DWORD)1;
	else
		dwValue = (DWORD)0;
	LONG ReturnValue = RegSetValueExW (m_hKey, wszName, 0L, REG_DWORD,
		(CONST BYTE*) &dwValue, sizeof(DWORD));

	if(ReturnValue == ERROR_SUCCESS)
		return true;

	return false;
}
