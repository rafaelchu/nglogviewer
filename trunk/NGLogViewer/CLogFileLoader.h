
#ifndef __CLOGFILELOADER_H_
#define __CLOGFILELOADER_H_

#include <vector>
#include <string>
#include <hash_set>
#include <set>

using namespace std;
using namespace stdext;


class CLineBuffer 
{
public:
	int m_nLineNumber;
	int m_nProcess;
	float m_Time;
	wstring m_wstrMessage;
};

class CLogFileLoader
{

private:
	wstring m_wstrFilename;
	hash_set<wstring> m_setWstrTags;
	set<int> m_setIntProcessNumber;
	
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
	int GetLineBufferData(wchar_t *wszBuffer, class CLineBuffer *pCLineBuffer); 


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