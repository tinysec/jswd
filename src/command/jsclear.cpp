/**
 * @file cmd_jsclear.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#include "precompile.h"

#include "src/extension.h"

#include "util/util_string.h"

EXTERN_C [[maybe_unused]] HRESULT __stdcall jsclear(IDebugClient *debugClient, const char *cmdline)
{
    HRESULT finalResult = E_FAIL;

    JsErrorCode errorCode = JsErrorFatal;

    Extension *extension = Extension::GetInstance();

    std::map<std::string , JsValueRef>::iterator it;

    std::string filename;

    JsValueRef exports = nullptr;

    JsValueRef routine = nullptr;

    do
    {
        UNREFERENCED_PARAMETER(debugClient);

        for ( it = extension->m_scripts.begin(); it != extension->m_scripts.end(); it++ )
        {
            filename = it->first;

            exports = it->second;


            routine = nullptr;
            errorCode = JsExGetProperty(exports, "unload", true, &routine);
            if (JsNoError == errorCode)
            {
                JsExCall(nullptr, routine, nullptr);
            }

            extension->m_pod->DebugPrintf("[jswd] unload script \"%s\" ok.\n" , filename.c_str() );

            JsRelease(exports , nullptr);
        }

        extension->m_scripts.clear();

        extension->m_pod->DebugPrintf("[jswd] all loaded scripts clear.");

        finalResult = S_OK;

    } while (false);

    return finalResult;
}
