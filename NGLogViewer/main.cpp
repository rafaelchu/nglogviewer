
#include "CLogFileLoader.h"
#include <hash_set>
using namespace std;
using namespace stdext;
int main (int argc, char **argv)
{
	wstring wstr(L"C:\\all.LOG");
	CLogFileLoader cLogFileLoader(wstr);
	cLogFileLoader.PreProcessing();
	//print all tags
	cLogFileLoader.PrintInfo();
	
	//Test case:
	cLogFileLoader.SetLineNumberFilter(10000, 20000);
	
	//cLogFileLoader.SetTimeFilter(cLogFileLoader.GetMinTime()+20.0, cLogFileLoader.GetMinTime()+40.0);
	
	//Test case: filter process
		vector<int> vec;
		vec.clear();
		vec.push_back(532);
		vec.push_back(2756);
		vec.push_back(1968);
		cLogFileLoader.SetProcessFilter(&vec);

	cLogFileLoader.RunFilterResult();
	cLogFileLoader.PrintResult();
	system("PAUSE");
	return 0;
}