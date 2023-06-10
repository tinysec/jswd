/**
 * @file cmd_jsunload.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#include "precompile.h"

#include "src/extension.h"

#include "util/util_string.h"

EXTERN_C HRESULT __stdcall jsunload(IDebugClient *debugClient, const char *cmdline)
{
    HRESULT finalResult = E_FAIL;

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
            extension->m_pod->DebugPrintf("[jswd] invalid usage of jsunload , use !js.help for help.\n");
            break;
        }

        filename = argv[0];

        exports = extension->RemoveScript(filename);
        if (nullptr == exports)
        {
            extension->m_pod->DebugPrintf("[jswd] not found loaded script \"%s\".\n" , filename.c_str() );
            break;
        }

        errorCode = JsExGetProperty(exports, "unload", true, &routine);
        if (JsNoError == errorCode)
        {
            JsExCall(nullptr, routine, nullptr);
        }

        JsRelease(exports , nullptr);

        extension->m_pod->DebugPrintf("[jswd] unload script \"%s\" ok.\n" , filename.c_str() );

        finalResult = S_OK;

    } while (false);

    return finalResult;
}
