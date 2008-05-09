
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
	cLogFileLoader.SetLineNumberFilter(10000, 20000);
	cLogFileLoader.RunFilterResult();
	cLogFileLoader.PrintResult();
	system("PAUSE");
	return 0;
}