/**
 * @file cmd_jscall.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#include "precompile.h"

#include "src/extension.h"

#include "util/util_string.h"

// jscall filename routine
EXTERN_C HRESULT __stdcall jscall(IDebugClient *debugClient, const char *cmdline)
{
    HRESULT finalResult = E_FAIL;

    HRESULT hr = E_FAIL;

    JsValueRef exports = nullptr;

    JsErrorCode errorCode = JsErrorFatal;

    JsValueRef routineValue = nullptr;

    Extension *extension = Extension::GetInstance();

    std::vector<std::string> argv = UtilCmdlineToArgv(cmdline);

    std::string filename;

    std::string routineName;

    do
    {
        UNREFERENCED_PARAMETER(debugClient);

        if (argv.size() < 2)
        {
            extension->m_pod->DebugPrintf("[jswd] invalid usage of jscall , use !js.help for help.\n");
            break;
        }

        filename = std::string( argv[0] );
        argv.erase(argv.begin() );


        exports = extension->FindScript(filename);
        if (nullptr == exports )
        {
            extension->m_pod->DebugPrintf("[jswd] not found loaded script \"%s\".\n" , filename.c_str() );
            break ;
        }

        routineName = argv[0];
        argv.erase(argv.begin() );

        errorCode = JsExGetProperty(exports, routineName, true, &routineValue);
        if (JsNoError == errorCode)
        {
            JsExCallWithStringArguments(nullptr, routineValue, argv, nullptr);
        }
        else
        {
            extension->m_pod->DebugPrintf("[jswd] not found routine \"%s\" in loaded script \"%s\" ok.\n" , routineName.c_str() , filename.c_str() );
        }

        finalResult = S_OK;

    } while (false);

    return finalResult;
}
