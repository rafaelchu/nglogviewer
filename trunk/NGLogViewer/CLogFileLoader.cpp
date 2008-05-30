#include "CLogFileLoader.h"


using namespace std;

int CLogFileLoader::PreProcessing()
{
	this->ClearAll();
	m_wiFile.seekg(0);
	if (!m_wiFile)
	{
		return 0;
	}

	wchar_t wszLineBuffer[LINE_BUFFER_SIZE];
	class CLineBuffer *pCLineBuffer = new CLineBuffer();
	int nIndex = 0;
	
	while(m_wiFile.getline(wszLineBuffer, LINE_BUFFER_SIZE))
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
	pCLineBuffer = NULL;
	m_wiFile.clear();
	return 0;
}

CLogFileLoader::CLogFileLoader(wstring wstrFileName)
{
	ClearAll();
	m_wstrFilename = wstrFileName;
	m_wiFile.open(m_wstrFilename.c_str());
	if (m_wiFile.bad())
	{
		printf("fail to load!");
	}
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

int CLogFileLoader::GetLineBufferData(wchar_t *wszBuffer, class CLineBuffer *pCLineBuffer, bool bTag)
{
	wchar_t wszString[LINE_BUFFER_SIZE]={0};
	swscanf(wszBuffer, L"%d %f [%d]", &pCLineBuffer->m_nLineNumber, &pCLineBuffer->m_Time, &pCLineBuffer->m_nProcess);

	if (bTag)
	{
		wchar_t *pWstr;
		pWstr = wcschr(wszBuffer, '[');
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
				pCLineBuffer->m_wstrMessage = pWstr;
				if (pWstr!=NULL)
				{
					//wcscpy(wszString,pWstr);
					CleanAsTag(pWstr);
				}
			}
		}
		pCLineBuffer->m_wstrTag = pWstr;
	}
	else
	{
		wchar_t *pWstr;
		pWstr = wcschr(wszBuffer, '[');
		pCLineBuffer->m_wstrMessage = pWstr;
		pCLineBuffer->m_wstrTag =L"";
	}
	
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
	m_bEnableOutputNoProcessNumber = false;
	m_bEnableProcessFilter = false;
	m_bEnableOutputEmptyFilter = false;
	m_bEnableExcludeKeywordsFilter = false;
	m_pVecIntFilterProcessNumber = NULL;
	m_pVecWstrFilterTags = NULL;
	m_vecWstrFilterKeyWords.clear();

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
	m_vecResultLinePos.clear();
	m_wiFile.seekg(0);

	wchar_t wszLineBuffer[LINE_BUFFER_SIZE];
	class CLineBuffer *pCLineBuffer = new CLineBuffer();
	int nIndex = 0;

	int llpos = m_wiFile.tellg();
	while(m_wiFile.getline(wszLineBuffer, LINE_BUFFER_SIZE))
	{
		GetLineBufferData(wszLineBuffer, pCLineBuffer, false);
		if (! IsFilterLine(pCLineBuffer))
		{
			m_setResultLine.insert(nIndex);
			m_vecResultLinePos.push_back(llpos);
		}
		nIndex++;
		llpos = m_wiFile.tellg();
	}
	delete pCLineBuffer;
	m_wiFile.clear();
	return 0;
}

bool CLogFileLoader::IsFilterLine(class CLineBuffer *pCLineBuffer)
{
	if (m_bEnableIncludeKeeywordsFilter && IsFilterLineByIncludeKeyWords(pCLineBuffer) )
		return true;
	if (m_bEnableOutputEmptyFilter && IsEmptyString(pCLineBuffer->m_wstrMessage.c_str()))
		return true;
	if (m_bEnableLineNumberFilter && IsFilterLineByLineNumber(pCLineBuffer))
		return true;
	if (m_bEnableTimeFilter && IsFilterLineByTime(pCLineBuffer))
		return true;
	if (m_bEnableProcessFilter && IsFilterLineByProcess(pCLineBuffer))
		return true;
	if (m_bEnableTagsFilter && IsFilterLineByTags(pCLineBuffer))
		return true;
	if (m_bEnableExcludeKeywordsFilter && IsFilterLineByExcludeKeyWords(pCLineBuffer))
		return true;
	return false;
}

bool CLogFileLoader::IsFilterLineByTags(class CLineBuffer *pCLineBuffer)
{
	if (m_pVecWstrFilterTags==NULL)
		return false;
	vector<wstring>::iterator pos;
	for (pos = m_pVecWstrFilterTags->begin();pos != m_pVecWstrFilterTags->end();++pos)
	{
		if (wcsstr(pCLineBuffer->m_wstrMessage.c_str(), pos->c_str()) != NULL)
		{
			return true;
		}
	}

	return false;
}

bool CLogFileLoader::IsFilterLineByExcludeKeyWords(class CLineBuffer *pCLineBuffer)
{
	vector<wstring>::iterator pos;
	for (pos = m_vecWstrFilterKeyWords.begin();pos != m_vecWstrFilterKeyWords.end();++pos)
	{
		if (wcsstr(pCLineBuffer->m_wstrMessage.c_str(), pos->c_str()) != NULL)
		{
			return true;
		}
	}
	return false;
}

bool CLogFileLoader::IsFilterLineByIncludeKeyWords(class CLineBuffer *pCLineBuffer)
{
	vector<wstring>::iterator pos;
	for (pos = m_vecWstrIncludeKerWords.begin();pos != m_vecWstrIncludeKerWords.end();++pos)
	{
		if (wcsstr(pCLineBuffer->m_wstrMessage.c_str(), pos->c_str()) != NULL)
		{
			return false;
		}
	}
	return true;
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

bool CLogFileLoader::IsFilterLineByProcess(class CLineBuffer *pCLineBuffer)
{
	if(m_pVecIntFilterProcessNumber == NULL)
		return false;
	if((m_bEnableOutputNoProcessNumber) && (pCLineBuffer->m_nLineNumber == 0))
		return false;
	vector<int>::iterator pos;
	for (pos = m_pVecIntFilterProcessNumber->begin();pos!= m_pVecIntFilterProcessNumber->end() ;pos++)
	{
		if (*pos == pCLineBuffer->m_nProcess)
			return true;
	}
	return false;
}

int CLogFileLoader::GetResultLine(int nLine, CLineBuffer *pCLineBuffer)
{
	wchar_t wszLineBuffer[LINE_BUFFER_SIZE];
	GetResultLine(nLine,wszLineBuffer);
	GetLineBufferData(wszLineBuffer, pCLineBuffer, false);
	return 0;
}

int CLogFileLoader::GetResultLine(int nLine, wchar_t *wszLineBuffer)
{
	int llPos = m_vecResultLinePos[nLine];
	m_wiFile.seekg(llPos);
	m_wiFile.getline(wszLineBuffer, LINE_BUFFER_SIZE);
	m_wiFile.clear();
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

int CLogFileLoader::SetProcessFilter(vector<int> *pProcessFilter, bool bIncludeNoProcessFilter/* = false*/)
{
	m_bEnableProcessFilter = true;
	m_bEnableOutputNoProcessNumber = bIncludeNoProcessFilter;
	m_pVecIntFilterProcessNumber = pProcessFilter;
	return 0;
}

int CLogFileLoader::SetTagsFilter(vector<wstring> *pTagsFilter)
{
	m_bEnableTagsFilter = true;
	m_pVecWstrFilterTags = pTagsFilter;
	return 0;
}

bool CLogFileLoader::IsEmptyString(const wchar_t * pwszStr)
{
	const wchar_t * pwszStrAfterProcess;
	pwszStrAfterProcess = wcschr(pwszStr, ']');
	if (pwszStrAfterProcess!=NULL)
		pwszStrAfterProcess++;
	else
		pwszStrAfterProcess = pwszStr;
	for(unsigned int i =0;i<wcslen(pwszStrAfterProcess);++i)
	{
		if (isspace(pwszStrAfterProcess[i])==0)
		{
			return false;
		}
	}
	return true;
}

bool CLogFileLoader::SaveResultAs(wstring wstrPathName)
{
	wofstream fwoFile(wstrPathName.c_str());
	if (fwoFile.fail())
		return false;
	int nCount = this->GetResultSize();
	wchar_t wszBuffer [LINE_BUFFER_SIZE];
	for (int i = 0; i<nCount ;i++)
	{
		this->GetResultLine(i, wszBuffer);
		fwoFile<< wszBuffer << endl;
	}
	fwoFile.close();
	return true;
}

int CLogFileLoader::SetEnableFilterEmptyMessage(bool bInput)
{
	m_bEnableOutputEmptyFilter = bInput;
	return 0;
}

int CLogFileLoader::SetKeyWordExcludeFilter(const wchar_t *wstrKeyWords)
{
	if (wstrKeyWords == NULL)
	{
		m_bEnableExcludeKeywordsFilter = false;
		m_vecWstrFilterKeyWords.clear();
		return 0;
	}

	m_bEnableExcludeKeywordsFilter = true;
	wchar_t *pwszBuffer = new wchar_t [wcslen(wstrKeyWords)+1];
	
	wcscpy(pwszBuffer, wstrKeyWords);

	wchar_t wszDelims[] = L";";
	wchar_t *result = NULL;
	result = wcstok(pwszBuffer, wszDelims );
	while (result != NULL)
	{
		m_vecWstrFilterKeyWords.push_back(result);
		result = wcstok(NULL, wszDelims);
	}
	delete [] pwszBuffer;
	pwszBuffer = NULL;
	return 0;
}

int CLogFileLoader::SetKeyWordIncludeFilter(const wchar_t *wstrKeyWords)
{
	if (wstrKeyWords == NULL || 
		(wcscmp(wstrKeyWords, L"*")==0) ||
		(wcscmp(wstrKeyWords, L"") ==0)
		)
	{
		m_bEnableIncludeKeeywordsFilter = false;
		m_vecWstrIncludeKerWords.clear();
		return 0;
	}

	m_bEnableIncludeKeeywordsFilter = true;
	wchar_t *pwszBuffer = new wchar_t [wcslen(wstrKeyWords)+1];

	wcscpy(pwszBuffer, wstrKeyWords);

	wchar_t wszDelims[] = L";";
	wchar_t *result = NULL;
	result = wcstok(pwszBuffer, wszDelims );
	while (result != NULL)
	{
		m_vecWstrIncludeKerWords.push_back(result);
		result = wcstok(NULL, wszDelims);
	}
	delete [] pwszBuffer;
	pwszBuffer = NULL;
	return 0;
}