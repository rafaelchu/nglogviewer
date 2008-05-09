
#ifndef __CLOGFILELOADER_H_
#define __CLOGFILELOADER_H_

#include <vector>
#include <string>
#include <hash_set>
#include <set>

using namespace std;
using namespace stdext;

#define LINE_BUFFER_SIZE	2048

class CLineBuffer 
{
public:
	int m_nLineNumber;
	int m_nProcess;
	float m_Time;
	wstring m_wstrTag;
	wstring m_wstrMessage;
};

class CLogFileLoader
{

private:
	wstring m_wstrFilename;
	hash_set<wstring> m_setWstrTags;
	set<int> m_setIntProcessNumber;
	set<int> m_setResultLine;
	vector<int>  m_vecResultLinePos;
	
	//Data after preprocessing
	int m_nMinLineNumber;
	int m_nMaxLineNumber;	
	int m_nTotalLines;

	//Filter Setting:
	vector<wstring> m_vecWstrFilterTags;
	vector<int> m_vecIntFilterProcessNumber;
	int m_nStartLineNumber;
	int m_nEndLineNumber;

	//Includer:
	bool m_bIncludeAllTag;
	bool m_bInculdeAllProcessNumber;

	wstring GetTag(wchar_t *wszBuffer);
	void CleanAsTag(wchar_t *wszString);
	int GetProcessNumber(wchar_t *wszBuffer);
	float GetTime(wchar_t *wszBuffer);
	int GetLineNumber(wchar_t *wszBuffer);
	int GetLineBufferData(wchar_t *wszBuffer, class CLineBuffer *pCLineBuffer); 
	bool IsFilterLine(class CLineBuffer *pCLineBuffer);

public:
	CLogFileLoader(wstring wstrFileName);
	~CLogFileLoader();

	int PreProcessing();
	int ClearAll();
	int ReSetFileName(wstring wstrFileName);
	vector<int> GetVecIntProcessNumber();
	vector<wstring> GetVecWstrTags();

	int GetResultSize();
	int GetResultLine(int nLine, CLineBuffer *pCLineBuffer);
	int GetResultLine(int nLine, wchar_t *wszLineBuffer);

	// Tags Filter
	int SetTagsFilter(vector<wstring> *pTagsFilter);

	// Process Filter
	int SetProcessFilter(vector<int> *pProcessFilter, bool bIncludeNoProcessFilter = false);

	// LineNumber Filter 
	int GetMinLineNumber();
	int GetMaxLineNumber();
	int SetLineNumberFilter(int nStartLineNumber, int nEndLineNumber);
	
	// Timer Filter 
	float GetMinTime();
	float GetMaxTime();
	int SetTimeFilter(float fStartTime, float fEndTime);

	// Keyword Filter
	int SetKeyWordIncludeFilter(const wchar_t *wstrKeyWords);
	int SetKeyWordExcludeFilter(const wchar_t *wstrKeyWords);

	int RunFilterResult();


	// Save as function
	bool SaveResultAs(wstring wstrPathName);

	void PrintInfo();
	void PrintResult();
};

#endif