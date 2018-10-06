#include <Windows.h>
#include "Debug.h"

void DebugOut(std::string fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	wchar_t dbg_out[4096];
	vswprintf_s(dbg_out, std::wstring(fmt.begin(), fmt.end()).c_str(), argp);
	va_end(argp);
	OutputDebugStringW(dbg_out);
}
