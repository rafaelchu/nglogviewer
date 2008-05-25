
#ifndef _CREGSETTING_H_
#define _CREGSETTING_H_
#include <Windows.h>
class CRegSetting
{
    public:
    CRegSetting(const wchar_t *wszPath, HKEY hKeyRoot = HKEY_CURRENT_USER);
	~CRegSetting();	

	bool WriteRegKey(const wchar_t *wszName, DWORD dwInput);
	bool WriteRegKey(const wchar_t *wszName, const wchar_t *wszValue);
	bool WriteRegKey(const wchar_t *wszName, int nSize, const BYTE *bytedata);

	bool ReadRegKey(const wchar_t *wszName, DWORD &dwInput);
	bool ReadRegKey(const wchar_t *wszName, int nSize, wchar_t *wszValue);
	bool ReadRegKey(const wchar_t *wszName, int nSize, BYTE *bytedata);


    private:
		HKEY 	m_hKey;

};
#endif
