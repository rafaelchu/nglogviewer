#include "CLogFileLoader.h"
#include <fstream>
#include <iostream>

#define LINE_BUFFER_SIZE	2048
using namespace std;

int CLogFileLoader::PreProcessing()
{
	wifstream wiFile(this->m_wstrFilename.c_str());
	if (!wiFile)
	{
		return 0;
	}

	wchar_t wszLineBuffer[LINE_BUFFER_SIZE];

	while(wiFile.getline(wszLineBuffer, LINE_BUFFER_SIZE))
	{
		wstring wstr=GetTag(wszLineBuffer);
		m_setWstrTags.insert(wstr);
	}
	return 0;
}

CLogFileLoader::CLogFileLoader(wstring wstrFileName)
{
	this->m_wstrFilename = wstrFileName;
}

wstring CLogFileLoader::GetTag(wchar_t *wszBuffer)
{
	int nNumber;
	float fNumber;
	wchar_t wszSkip[LINE_BUFFER_SIZE]={0};
	wchar_t wszString[LINE_BUFFER_SIZE]={0};
	swscanf(wszBuffer, L"%d %f %s %s", &nNumber, &fNumber, wszSkip, wszString);
	if (wszString[0] !='[')
		return L"";
	wstring wstr(wszString);
	return wstr;
}

CLogFileLoader::~CLogFileLoader()
{
}

void CLogFileLoader::PrintInfo()
{
	hash_set<wstring>::iterator hsIter;
	int i =0;
	for ( hsIter = m_setWstrTags.begin(); hsIter != m_setWstrTags.end(); hsIter++ )
	{
		i++;
		wchar_t *wstrA;
		wstrA =(wchar_t *) (hsIter->c_str());
		wprintf(L"%d:%s\n", i, wstrA);
	}
}