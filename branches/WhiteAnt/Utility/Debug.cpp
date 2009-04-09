#ifndef _AFXDLL
#include "windows.h"
#else
#include <afxwin.h>
#endif
#include <stdio.h>
#include <stdarg.h>
#include "Debug.h"
const wchar_t AP_KEYPATH[] = L"Software\\NG\\Logviewer";
const wchar_t AP_KEYNAME[] = L"dprint";
bool g_bDumpMsg = false;

class _CHECK_REG 
{
public:_CHECK_REG() 
	   {

		   HKEY hKey = NULL;
		   DWORD dwDumpMsg = 0;       // default value
		   LONG lRetValue = RegOpenKeyExW(HKEY_LOCAL_MACHINE, AP_KEYPATH, 0, KEY_ALL_ACCESS, &hKey);
		   if (lRetValue == ERROR_SUCCESS)

		   {
			   DWORD dwType;
			   DWORD dwSize = sizeof(DWORD);
			   RegQueryValueExW(hKey, AP_KEYNAME, NULL, &dwType, (BYTE *) & dwDumpMsg, &dwSize);
			   RegCloseKey(hKey);
			   g_bDumpMsg = (dwDumpMsg > 0);
		   }

	   }
};

static _CHECK_REG _check_reg;

void dprintf(const wchar_t* fmt, ...) 
{
	if (g_bDumpMsg)
	{
		va_list marker;
		va_start(marker, fmt);

		wchar_t buffer[1024];
		_vsnwprintf(buffer, 1023, fmt, marker);
		OutputDebugStringW(buffer);
		OutputDebugStringW(L"\n");

		va_end(marker);
	}
}


void dprintf(const char *fmt, ...) 
{
	if (g_bDumpMsg)
	{
		va_list marker;
		va_start(marker, fmt);
		char buffer[1024];
		_vsnprintf(buffer, 1023, fmt, marker);
		OutputDebugStringA(buffer);
		OutputDebugStringA("\n");
		va_end(marker);
	}
} 

AutoPrint::AutoPrint(const char* msg): m_msg(NULL), m_wmsg(NULL)
{
	if (!g_bDumpMsg)
		return;

	/// backup msg ///
	m_msg = new char[strlen(msg) + 1];
	strcpy(m_msg, msg);

	/// print "m_msg start" ///
	char* buf = new char[strlen(m_msg) + 32];
	strcpy(buf, m_msg);
	strcat(buf, " start\n");
	printf(buf);
	delete [] buf;
}


AutoPrint::AutoPrint(const wchar_t* wmsg): m_msg(NULL), m_wmsg(NULL)
{
	if (!g_bDumpMsg)
		return;

	/// backup wmsg ///
	m_wmsg = new wchar_t[wcslen(wmsg) + 1];
	wcscpy(m_wmsg, wmsg);

	/// print "m_wmsg start" ///
	wchar_t* wbuf = new wchar_t[wcslen(m_wmsg) + 32];
	wcscpy(wbuf, m_wmsg);
	wcscat(wbuf, L" start\n");

	wprintf(wbuf);



	delete [] wbuf;
}


AutoPrint::~AutoPrint()
{
	if (!g_bDumpMsg)
		return;

	/// print "m_msg end" ///
	if (m_msg)
	{
		char* buf = new char[strlen(m_msg) + 32];
		strcpy(buf, m_msg);
		strcat(buf, " end\n");

		printf(buf);



		delete [] buf;
		delete [] m_msg;
	}

	/// print "m_wmsg end" ///
	if (m_wmsg)
	{
		wchar_t* wbuf = new wchar_t[wcslen(m_wmsg) + 32];
		wcscpy(wbuf, m_wmsg);
		wcscat(wbuf, L" end\n");
		wprintf(wbuf);
		delete [] wbuf;
		delete [] m_wmsg;
	}
}
