
#ifndef __CLOGFILELOADER_H_
#define __CLOGFILELOADER_H_

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#include <set>
#include <boost\shared_ptr.hpp>
using namespace std;

#ifdef WIN32
#include <hash_set>
using namespace stdext;
#else
#include <ext/hash_set>
using namespace __gnu_cxx;
#endif

#define LINE_BUFFER_SIZE	2048

wchar_t *wcsistr
(
 const wchar_t *  szStringToBeSearched,
 const wchar_t *  szSubstringToSearchFor
 );

class CLogFileLoaderCallback
{
public:
	CLogFileLoaderCallback(){};
	virtual ~CLogFileLoaderCallback(){};
	virtual bool OnPercentCallback(float fPos) {return true;};
};

class CLineBuffer 
{
public:
	CLineBuffer() {}
public:
	int m_nLineNumber;
	int m_nProcess;
	float m_fTime;
	time_t m_tTime;
	wstring m_wstrTag;
	wstring m_wstrMessage;
	wstring m_wstrTimeString;
};

typedef boost::shared_ptr<CLineBuffer> CLineBufferSharedPtr;

#define CLOGFILELOADER_DIRTYBIT_INCLUDE	1
#define CLOGFILELOADER_DIRTYBIT_EXCLUDE 2

class CLogFileLoader
{

private:
	wstring m_wstrFilename;
	wifstream m_wiFile;

	hash_set<wstring> m_setWstrTags;
	set<int> m_setIntProcessNumber;
	set<int> m_setResultLine;
	vector<int>  m_vecResultLinePos;

	//Check the line data is header of log file or not.
	bool IsHeaderLineOfLogfile(const wchar_t *wsz);
	
	//Data after preprocessing
	int m_nMinLineNumber;
	int m_nMaxLineNumber;	
	int m_nTotalLines;

	float m_fMinTime;
	float m_fMaxTime;

	//Filter Setting:
	vector<wstring> * m_pVecWstrFilterTags;
	vector<wstring>   m_vecWstrFilterKeyWords;
	vector<wstring>   m_vecWstrIncludeKerWords;
	vector<int> * m_pVecIntFilterProcessNumber;

	vector<int> m_vecRawResultLinePos;				// The file pointer position
	vector<CLineBufferSharedPtr> m_vecRawData;		// The Data is totally same with the file
	vector<CLineBufferSharedPtr> m_vecpRunBuffer;


	int m_nStartLineNumber;
	int m_nEndLineNumber;

	float m_fStartTime;
	float m_fEndTime;

	bool m_bEnableLineNumberFilter;
	bool m_bEnableTimeFilter;
	bool m_bEnableProcessFilter;
	bool m_bEnableTagsFilter;
	bool m_bEnableKillEmptyMessage;
	bool m_bEnableOutputNoProcessNumber;
	bool m_bEnableOutputEmptyFilter;
	bool m_bEnableExcludeKeywordsFilter;
	bool m_bEnableIncludeKeeywordsFilter;

	//Includer:
	bool m_bIncludeAllTag;
	bool m_bInculdeAllProcessNumber;

	//string compare flag
	bool m_bEnableMatchCaseStringCompare;

	wstring GetTag(wchar_t *wszBuffer);
	void CleanAsTag(wchar_t *wszString);
	int GetProcessNumber(wchar_t *wszBuffer);
	float GetTime(wchar_t *wszBuffer);
	int GetLineNumber(wchar_t *wszBuffer);
	int GetLineBufferData(wchar_t *wszBuffer, CLineBufferSharedPtr & LineBuffer_Ptr, bool bTag = true); 

	//Filter function:
	bool IsFilterLine(CLineBufferSharedPtr & LineBuffer_Ptr);
	bool IsFilterLineByLineNumber(CLineBufferSharedPtr & LineBuffer_Ptr);
	bool IsFilterLineByTime(CLineBufferSharedPtr & LineBuffer_Ptr);
	bool IsFilterLineByProcess(CLineBufferSharedPtr & LineBuffer_Ptr);
	bool IsFilterLineByTags(CLineBufferSharedPtr & LineBuffer_Ptr);
	bool IsFilterLineByExcludeKeyWords(CLineBufferSharedPtr & LineBuffer_Ptr);
	bool IsFilterLineByIncludeKeyWords(CLineBufferSharedPtr & LineBuffer_Ptr);

	bool IsEmptyString(const wchar_t * pwszStr);

	CLogFileLoaderCallback *m_CallbackObject;
	
	int CompareString(const wchar_t *s1, const wchar_t *s2);
	const wchar_t * CheckSubString(const wchar_t *s1, const wchar_t *s2);

	//Dirty function 
	bool IsNeedDirtyReFilterData();
	int m_bReFilterDirtyBit;
	void SetDirtyBit(int bit);
	void ReSetDirtyBit(int bit=0xffffffff);
	wstring m_wstrInclude; 
	wstring m_wstrExclude;
	bool ClearKeyWordInclude();
	bool ClearKeyWordExclude();
	
public:
	CLogFileLoader(wstring wstrFileName);
	~CLogFileLoader();

	int LoadFile();
	int PreProcessing();
	int ClearAll();
	int ReSetFileName(wstring wstrFileName);
	vector<int> GetVecIntProcessNumber();
	vector<wstring> GetVecWstrTags();

	int GetResultSize();
	int GetResultLine(int nLine, CLineBufferSharedPtr & LineBuffer_Ptr);
	int GetResultLine(int nLine, wchar_t *wszLineBuffer);
	int GetResultLineEx(int nLine, CLineBufferSharedPtr & LineBuffer_Ptr);
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

	// Filter Empty Message
	int SetEnableFilterEmptyMessage(bool bInput);

	void PrintInfo();
	void PrintResult();

	void SetCallbackPercentFunction(CLogFileLoaderCallback *pObj);
	
	// Set string compare function for match case or ignore case
	void SetEnableMatchCaseStringCompare(bool bInput);
};

#endif