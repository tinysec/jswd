/**
 * @file cmd_jsrun.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#include "precompile.h"

#include "src/extension.h"

#include "util/util_string.h"

EXTERN_C HRESULT __stdcall jsrun(IDebugClient *debugClient, const char *cmdline)
{
    HRESULT finalResult = E_FAIL;

    HRESULT hr = E_FAIL;

    JsValueRef exports = nullptr;

    JsErrorCode errorCode = JsErrorFatal;

    JsValueRef routine = nullptr;

    Extension *extension = Extension::GetInstance();

    std::vector<std::string> argv = UtilCmdlineToArgv(cmdline);

    std::string filename;

    do
    {
        UNREFERENCED_PARAMETER(debugClient);

        if (argv.size() <= 0)
        {
            extension->m_pod->DebugPrintf("[jswd] invalid usage of jscall , use !js.help for help.\n");
            break;
        }

        filename = argv[0];

        errorCode = extension->m_pod->RequireModule(filename, &exports);
        if (JsNoError != errorCode)
        {
            extension->m_pod->PrintException();
            break;
        }

        errorCode = JsExGetProperty(exports, "main", true, &routine);
        if (JsNoError == errorCode)
        {
            JsExCallWithStringArray(nullptr, routine, argv, nullptr);
        }

        finalResult = S_OK;

    } while (false);

    return finalResult;
}
