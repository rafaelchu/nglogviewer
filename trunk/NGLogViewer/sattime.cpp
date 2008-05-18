#include <time.h>
#include <iostream>

#include "sattime.h"
using namespace std;

sattime::sattime()
{
    startclock=clock();
}

double sattime::getRunningSecs()
{
    endclock=clock();
    unsigned long totclock=endclock-startclock;
    double outputtime;
    outputtime = (double)totclock/(double)CLK_TCK;
    return outputtime;      
}

void sattime::printSecs()
{
	cout << "Use "<< this->getRunningSecs() <<" secs"<<endl;
}

void sattime::printSecs(const char *titleStr)
{
	cout << titleStr;
	this->printSecs();
}
void sattime::restart()
{
	startclock=clock();
}