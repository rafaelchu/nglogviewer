#include "CLogFileLoader.h"
#include <fstream>
#include <iostream>

#define LINE_BUFFER_SIZE	2048
using namespace std;

int CLogFileLoader::PreProcessing()
{
	this->ClearAll();

	wifstream wiFile(this->m_wstrFilename.c_str());
	if (!wiFile)
	{
		return 0;
	}

	wchar_t wszLineBuffer[LINE_BUFFER_SIZE];
	class CLineBuffer *pCLineBuffer = new CLineBuffer();
	while(wiFile.getline(wszLineBuffer, LINE_BUFFER_SIZE))
	{
		GetLineBufferData(wszLineBuffer, pCLineBuffer);
		m_setWstrTags.insert(pCLineBuffer->m_wstrMessage);
		m_setIntProcessNumber.insert(pCLineBuffer->m_nProcess);
	}

	delete pCLineBuffer;
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
	//List All Tags
	vector<wstring>::iterator vecWstrIter;
	int i =0;
	vector<wstring> vecWstrTags=GetVecWstrTags();
	for ( vecWstrIter = vecWstrTags.begin(); vecWstrIter != vecWstrTags.end(); ++vecWstrIter )
	{
		i++;
		wchar_t *wstrA;
		wstrA =(wchar_t *) (vecWstrIter->c_str());
		wprintf(L"%d:%s\n", i, wstrA);
	}

	//List All Process
	vector<int> vecProcessNumber= this->GetVecIntProcessNumber();
	vector<int>::iterator veciIter;
	i=0;
	for (veciIter = vecProcessNumber.begin(); veciIter != vecProcessNumber.end(); ++veciIter)
	{
		i++;
		wprintf(L"%d:[%d]\n", i, *veciIter);
	}

}

int CLogFileLoader::GetLineBufferData(wchar_t *wszBuffer, class CLineBuffer *pCLineBuffer)
{
	wchar_t wszSkip[LINE_BUFFER_SIZE]={0};
	wchar_t wszString[LINE_BUFFER_SIZE]={0};
	swscanf(wszBuffer, L"%d %f [%d] %s", &pCLineBuffer->m_nLineNumber, &pCLineBuffer->m_Time, &pCLineBuffer->m_nProcess, wszString);
	if (wszString[0] !='[')
		wszString[0] = '\0';
	pCLineBuffer->m_wstrMessage = wszString;
	return 0;
}

vector<int> CLogFileLoader::GetVecIntProcessNumber()
{
	vector<int> vecIntProcessNumber;
	set<int>::iterator sIter;
	int i =0;
	for ( sIter = m_setIntProcessNumber.begin(); sIter != m_setIntProcessNumber.end(); ++sIter )
	{
		vecIntProcessNumber.push_back(*sIter);
	}
	return vecIntProcessNumber;
}

vector<wstring> CLogFileLoader::GetVecWstrTags()
{
	vector<wstring> vecWstrTags;
	hash_set<wstring>::iterator hsIter;
	int i =0;
	for ( hsIter = m_setWstrTags.begin(); hsIter != m_setWstrTags.end(); ++hsIter )
	{
		vecWstrTags.push_back(*hsIter);
	}
	return vecWstrTags;
}

int CLogFileLoader::ClearAll()
{
	m_setIntProcessNumber.clear();
	m_setWstrTags.clear();
	return 0;
}