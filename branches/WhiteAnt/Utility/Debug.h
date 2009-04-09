#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <wchar.h>

void dprintf(const wchar_t* fmt, ...);
void dprintf(const char* fmt, ...);

class AutoPrint
{
 public:
     AutoPrint(const char* msg);
     AutoPrint(const wchar_t* msg);
     ~AutoPrint();

 private:
    char* m_msg;
    wchar_t* m_wmsg;
};

#endif	//_DEBUG_H_
