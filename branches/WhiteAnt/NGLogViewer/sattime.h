
#ifndef _SATTIME_H_
#define _SATTIME_H_

#include <time.h>

class sattime
{
    public:
    sattime();
    double getRunningSecs();
    void restart();
	void printSecs();
	void printSecs(const char *titleStr);	

    private:
    unsigned long startclock;
    unsigned long endclock;
    unsigned long usedclock;


};
#endif
