
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

	return 0;
}