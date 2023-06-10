/**
 * @file main.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1
 * 22-12-21   init
 */

#ifndef BUILD_TESTS
////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>

#ifdef BUILD_LIBRARY

BOOL __stdcall DllMain(__in HMODULE module, __in DWORD reason, LPVOID lparam)
{
    UNREFERENCED_PARAMETER(module);
    UNREFERENCED_PARAMETER(reason);
    UNREFERENCED_PARAMETER(lparam);

    switch (reason)
    {
    case DLL_PROCESS_ATTACH: {

        break;
    }
    case DLL_PROCESS_DETACH: {

        break;
    }
    default: {
        break;
    }
    }

    return TRUE;
}

#else

int main(int argc, char **argv)
{

    return 0;
}

#endif // #ifdef BUILD_LIBRARY

////////////////////////////////////////////////////////////////////////////////////////
#endif // #ifndef BUILD_TESTS
