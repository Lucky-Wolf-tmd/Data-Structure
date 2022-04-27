#pragma once
extern "C"
//__declspec(dllimport) ;

__declspec(dllimport) int __cdecl _CrtDbgReport(
    int         _ReportType,
    char const* _FileName,
    int         _Linenumber,
    char const* _ModuleName,
    char const* _Format,
    ...);

void ABORT(bool flag,const char* msg) {
    // if (AbortandReport(1, __FILE__, __LINE__, nullptr,  msg))
        // 1, "Mudule", 1000, "Report", "Message"
    if (flag) {
        if (_CrtDbgReport(1, __FILE__, __LINE__, nullptr, "%s", msg))
            __debugbreak();
    }
}