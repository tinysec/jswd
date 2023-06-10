/**
 * @file cmd_jslist.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#include "precompile.h"

#include "src/extension.h"

#include "util/util_string.h"

EXTERN_C HRESULT __stdcall jslist(IDebugClient *debugClient, const char *cmdline)
{
    HRESULT finalResult = E_FAIL;

    JsErrorCode errorCode = JsErrorFatal;

    Extension *extension = Extension::GetInstance();

    std::vector<std::string> argv = UtilCmdlineToArgv(cmdline);

    std::map<std::string , JsValueRef>::iterator it;

    std::string filename;

    int i = 0;


    do
    {
        UNREFERENCED_PARAMETER(debugClient);

        extension->m_pod->DebugPrintf("[jswd] there are %d scripts.\n" ,  extension->m_scripts.size() );

        for ( it = extension->m_scripts.begin(); it != extension->m_scripts.end(); it++ )
        {
            filename = it->first;

            extension->m_pod->DebugPrintf("[%d] -> %s\n" , i , filename.c_str() );

            i++;
        }

        finalResult = S_OK;

    } while (false);

    return finalResult;
}
