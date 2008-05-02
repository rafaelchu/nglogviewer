
#ifndef __CLOGFILELOADER_H_
#define __CLOGFILELOADER_H_

#include <vector>
#include <string>
#include <hash_set>

using namespace std;
using namespace stdext;

class CLogFileLoader
{

private:
	wstring m_wstrFilename;
	hash_set<wstring> m_setWstrTags;
	vector<int> m_vecIntProcessNumber;
	
	//Filter:
	vector<wstring> m_vecWstrFilterTags;
	vector<int> m_vecIntFilterProcessNumber;
	
	//Includer:
	bool m_bIncludeAllTag;
	bool m_bInculdeAllProcessNumber;
	
	wstring GetTag(wchar_t *wszBuffer);
	int GetProcessNumber(wchar_t *wszBuffer);
	float GetTime(wchar_t *wszBuffer);
	int GetLineNumber(wchar_t *wszBuffer);


public:
	CLogFileLoader(wstring wstrFileName);
	~CLogFileLoader();

	int PreProcessing();
	int ClearAll();
	int ReSetFileName();
	vector<int> GetVecIntProcessNumber();
	vector<wstring> GetVecWstrTags();

	void PrintInfo();
};

#endif