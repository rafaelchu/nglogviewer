
#include "CLogFileLoader.h"
#include "sattime.h"
using namespace std;

#ifdef WIN32
#include <hash_set>
using namespace stdext;
#else
#include <ext/hash_set>
using namespace __gnu_cxx;
#endif

int main (int argc, char **argv)
{
	wstring wstr(L"C:\\all.LOG");
	sattime cTimeCheck;
	cTimeCheck.restart();
	CLogFileLoader cLogFileLoader(wstr);
	cTimeCheck.printSecs("CLogFileLoader init");

	cLogFileLoader.PreProcessing();
	cTimeCheck.printSecs("CLogFileLoader preprocessing");
	//print all tags
	//cLogFileLoader.PrintInfo();
	
	//Test case:
	//cLogFileLoader.SetLineNumberFilter(10000, 20000);
	
	//cLogFileLoader.SetTimeFilter(cLogFileLoader.GetMinTime()+20.0, cLogFileLoader.GetMinTime()+40.0);
	
	//Test case: filter process
	/*
		vector<int> vec;
		vec.clear();
		vec.push_back(532);
		vec.push_back(2756);
		vec.push_back(1968);
		cLogFileLoader.SetProcessFilter(&vec);
	*/

	//Test case: filter [CLRec4]
		//vector<wstring> vec2;
		//vec2.push_back(L"[CLSchMgr]");
		//vec2.push_back(L"[CLRec4]");
		//vec2.push_back(L"EPG");
		//vec2.push_back(L"(SQL)");
		//cLogFileLoader.SetTagsFilter(&vec2);

	//Test case: Exclude
	//cLogFileLoader.SetKeyWordExcludeFilter(L"[CLSchMgr];[CLRec4];EPG");

	//Test case: Include
	cLogFileLoader.SetKeyWordIncludeFilter(L"[CLRec4];EPG");
	
	cTimeCheck.restart();
	cLogFileLoader.RunFilterResult();
	cTimeCheck.printSecs("CLogFileLoader RunFilterResult ");
	//cLogFileLoader.PrintResult();
	cLogFileLoader.SaveResultAs(L"C:\\Result.txt");
	system("PAUSE");
	return 0;
}