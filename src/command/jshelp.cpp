/**
 * @file cmd_jshep.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#include "precompile.h"

#include "src/extension.h"

#include "util/util_string.h"

#include "version.h"

EXTERN_C HRESULT __stdcall jshelp(IDebugClient *debugClient, const char *cmdline)
{
    Extension *extension = Extension::GetInstance();

    UNREFERENCED_PARAMETER(debugClient);

    extension->printUsage();

    return S_OK;
}
