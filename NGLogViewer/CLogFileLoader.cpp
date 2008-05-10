#include "CLogFileLoader.h"
#include <fstream>
#include <iostream>
#include <algorithm>


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
	int nIndex = 0;
	while(wiFile.getline(wszLineBuffer, LINE_BUFFER_SIZE))
	{
		GetLineBufferData(wszLineBuffer, pCLineBuffer);
		//1. Preprocess the Max/min line number
		{
			if (nIndex ==0)
			{
				m_nMaxLineNumber = pCLineBuffer->m_nLineNumber;
				m_nMinLineNumber = pCLineBuffer->m_nLineNumber;
				m_fMinTime = pCLineBuffer->m_Time;
				m_fMaxTime = pCLineBuffer->m_Time;
			}
			else
			{
				if (pCLineBuffer->m_nLineNumber> m_nMaxLineNumber)
					m_nMaxLineNumber = pCLineBuffer->m_nLineNumber;
				if (pCLineBuffer->m_Time> m_fMaxTime)
					m_fMaxTime = pCLineBuffer->m_Time;
			}
		}

		//2. Preprocess tags and process number
		m_setWstrTags.insert(pCLineBuffer->m_wstrTag);
		m_setIntProcessNumber.insert(pCLineBuffer->m_nProcess);
		nIndex++;
	}
	m_nTotalLines = nIndex;

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
	//Prinet member var
	wprintf(L"Path:%s\n", m_wstrFilename.c_str());
	wprintf(L"Min Line number:%d\n", m_nMinLineNumber);
	wprintf(L"Max Line number:%d\n", m_nMaxLineNumber);
	wprintf(L"Min Time:%f\n", GetMinTime());
	wprintf(L"Max Time:%f\n", GetMaxTime());
	wprintf(L"====================================\n");

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
	wchar_t wszString[LINE_BUFFER_SIZE]={0};
	swscanf(wszBuffer, L"%d %f [%d]", &pCLineBuffer->m_nLineNumber, &pCLineBuffer->m_Time, &pCLineBuffer->m_nProcess);
	wchar_t *pWstr;
	pWstr = wcschr(wszBuffer, '[');
	pCLineBuffer->m_wstrMessage = pWstr;
	if (pCLineBuffer->m_nProcess != 0)
	{
		pWstr = wcschr(wszBuffer, ']');
		if (pWstr ==NULL)
		{
			wszString[0] = '\0';
		}
		else
		{
			pWstr++;	//empty char
			pWstr++;	//'['
			if (pWstr!=NULL)
			{
				wcscpy(wszString,pWstr);
				CleanAsTag(wszString);
			}
		}
	}
	
	pCLineBuffer->m_wstrTag = wszString;
	return 0;
}

void CLogFileLoader::CleanAsTag(wchar_t *wszString)
{
	//Clean tag String:
	if (wszString[0] !='[')
		wszString[0] = '\0';
	else
	{
		wchar_t *pWstr=wszString;
		do 
		{
			pWstr = wcschr(pWstr, ']');
			if (pWstr==NULL)
			{
				break;
			}
			else
			{
				pWstr++;
				if (*pWstr == '[')
				{
					continue;
				}
				else
				{
					*pWstr='\0';
					break;
				}
			}
		} while (true);

	}
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
	sort(vecWstrTags.begin(), vecWstrTags.end() );     
	return vecWstrTags;
}

int CLogFileLoader::ClearAll()
{
	m_setIntProcessNumber.clear();
	m_setWstrTags.clear();
	m_nMinLineNumber=0;
	m_nMaxLineNumber=0;
	m_fMinTime=0.0;
	m_fMaxTime=0.0;
	m_bEnableLineNumberFilter = false;
	m_bEnableTimeFilter = false;

	return 0;
}

int CLogFileLoader::GetMinLineNumber()
{
	return m_nMinLineNumber;
}

int CLogFileLoader::GetMaxLineNumber()
{
	return m_nMaxLineNumber;
}

int CLogFileLoader::GetResultSize()
{
	return m_setResultLine.size();
}

int CLogFileLoader::RunFilterResult()
{
	m_setResultLine.clear();

	wifstream wiFile(this->m_wstrFilename.c_str());
	if (!wiFile)
	{
		return 0;
	}

	wchar_t wszLineBuffer[LINE_BUFFER_SIZE];
	class CLineBuffer *pCLineBuffer = new CLineBuffer();
	int nIndex = 0;
	int llpos = wiFile.tellg();
	while(wiFile.getline(wszLineBuffer, LINE_BUFFER_SIZE))
	{
		GetLineBufferData(wszLineBuffer, pCLineBuffer);
		if (! IsFilterLine(pCLineBuffer))
		{
			m_setResultLine.insert(nIndex);
			m_vecResultLinePos.push_back(llpos);
		}
		nIndex++;
		llpos = wiFile.tellg();
	}
}

bool CLogFileLoader::IsFilterLine(class CLineBuffer *pCLineBuffer)
{
	if (m_bEnableLineNumberFilter && IsFilterLineByLineNumber(pCLineBuffer))
		return true;
	if (m_bEnableTimeFilter && IsFilterLineByTime(pCLineBuffer))
		return true;
	return false;
}

bool CLogFileLoader::IsFilterLineByLineNumber(class CLineBuffer *pCLineBuffer)
{
	if (pCLineBuffer->m_nLineNumber< this->m_nStartLineNumber)
		return true;
	if (pCLineBuffer->m_nLineNumber> this->m_nEndLineNumber)
		return true;
	return false;
}

bool CLogFileLoader::IsFilterLineByTime(class CLineBuffer *pCLineBuffer)
{
	if (pCLineBuffer->m_Time< this->m_fStartTime)
		return true;
	if (pCLineBuffer->m_Time> this->m_fEndTime)
		return true;
	return false;
}

int CLogFileLoader::GetResultLine(int nLine, CLineBuffer *pCLineBuffer)
{
	wchar_t wszLineBuffer[LINE_BUFFER_SIZE];
	GetResultLine(nLine,wszLineBuffer);
	GetLineBufferData(wszLineBuffer, pCLineBuffer);
	return 0;
}

int CLogFileLoader::GetResultLine(int nLine, wchar_t *wszLineBuffer)
{
	int llPos = m_vecResultLinePos[nLine];
	wifstream wiFile(this->m_wstrFilename.c_str());
	if (!wiFile)
	{
		return 1;
	}
	wiFile.seekg(llPos);
	wiFile.getline(wszLineBuffer, LINE_BUFFER_SIZE);
	return 0;
}

int CLogFileLoader::SetLineNumberFilter(int nStartLineNumber, int nEndLineNumber)
{
	m_bEnableLineNumberFilter = true;
	m_nStartLineNumber = nStartLineNumber;
	m_nEndLineNumber = nEndLineNumber;
	return 0;
}

void CLogFileLoader::PrintResult()
{
	int nTotlal = this->GetResultSize();
	wchar_t wstrBuffer[LINE_BUFFER_SIZE];
	for (int i=0;i<nTotlal;++i)
	{
		this->GetResultLine(i, wstrBuffer);
		wprintf(L"%s\n", wstrBuffer);
	}
}

float CLogFileLoader::GetMinTime()
{
	return m_fMinTime;
}

float CLogFileLoader::GetMaxTime()
{
	return m_fMaxTime;
}


int CLogFileLoader::SetTimeFilter(float fStartTime, float fEndTime)
{
	m_bEnableTimeFilter = true;
	m_fStartTime = fStartTime;
	m_fEndTime = fEndTime;
	return 0;
}
