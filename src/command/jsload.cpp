/**
 * @file cmd_jsload.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#include "precompile.h"

#include "src/extension.h"

#include "util/util_string.h"

EXTERN_C HRESULT __stdcall jsload(IDebugClient *debugClient, const char *cmdline)
{
    HRESULT finalResult = E_FAIL;

    HRESULT hr = E_FAIL;

    JsValueRef exports = nullptr;

    JsErrorCode errorCode = JsErrorFatal;

    JsValueRef routine = nullptr;

    Extension *extension = Extension::GetInstance();

    std::vector<std::string> argv = UtilCmdlineToArgv(cmdline);

    std::string  filename;

    do
    {
        UNREFERENCED_PARAMETER(debugClient);

        if (argv.size() <= 0)
        {
            extension->m_pod->DebugPrintf("[jswd] invalid usage of jscall , use !js.help for help.\n");
            break;
        }

        filename = argv[0];

        exports = extension->FindScript(filename);
        if (nullptr != exports )
        {
            extension->m_pod->DebugPrintf("[jswd] script \"%s\" is already loaded.\n" , filename.c_str() );
            break;
        }

        errorCode = extension->m_pod->RequireModule(filename, &exports);
        if (JsNoError != errorCode)
        {
            extension->m_pod->PrintException();
            break;
        }

        if ( !extension->AddScript(filename, exports) )
        {
            extension->m_pod->DebugPrintf("[jswd] script \"%s\" is already loaded.\n" , filename.c_str() );
            break;
        }

        errorCode = JsExGetProperty(exports, "load", true, &routine);
        if (JsNoError == errorCode)
        {
            JsExCall(nullptr, routine, nullptr);
        }

        extension->m_pod->DebugPrintf("[jswd] load script \"%s\" ok.\n" , filename.c_str() );

        finalResult = S_OK;

    } while (false);

    return finalResult;
}
