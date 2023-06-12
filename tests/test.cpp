/**
 * @file test_foobar.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1
 * 22-12-21   init
 */

#include <windows.h>

#include <DbgEng.h>

#include "src/extension.h"

#include "src/entrypoint.h"

#include "command/commands.h"

#include "callbacks/standard_output_callbacks.h"

int main(int argc, char **argv)
{
    HRESULT hr = S_FALSE;

    ULONG version = 0;

    ULONG flags = 0;

    IDebugClient *debugClient = nullptr;

    IDebugControl *debugControl = nullptr;

    IDebugSymbols *debugSymbols = nullptr;

    StandardOutputCallbacks *standardOutputCallbacks = nullptr;

    StandardEventCallbacks *standardEventCallbacks = nullptr;

    do
    {

        hr = DebugCreate(__uuidof(IDebugClient), (PVOID *)&(debugClient));
        if (!SUCCEEDED(hr))
        {
            break;
        }

        hr = debugClient->QueryInterface(__uuidof(IDebugControl), (PVOID *)&(debugControl));
        if (!SUCCEEDED(hr))
        {
            break;
        }

        hr = debugClient->QueryInterface(__uuidof(IDebugSymbols), (PVOID *)&(debugSymbols));
        if (!SUCCEEDED(hr))
        {
            break;
        }


        standardOutputCallbacks = new StandardOutputCallbacks();

        hr = debugClient->SetOutputCallbacks(standardOutputCallbacks);
        if (!SUCCEEDED(hr))
        {
            break;
        }

        // set event callbacks
        standardEventCallbacks = new StandardEventCallbacks();

        hr = debugClient->SetEventCallbacks(standardEventCallbacks);
        if (!SUCCEEDED(hr))
        {
            break;
        }

        hr = debugSymbols->SetSymbolPath("D:\\sys\\symbols");
        if (!SUCCEEDED(hr))
        {
            break;
        }


        hr = DebugExtensionInitialize(&version, &flags);
        if (!SUCCEEDED(hr))
        {
            break;
        }

        hr = debugClient->OpenDumpFile("D:\\sys\\crash\\MEMORY.DMP");
        if (!SUCCEEDED(hr))
        {
            break;
        }
        hr = debugControl->Execute( 0 , ".reload nt" , 0);
        if (!SUCCEEDED(hr))
        {
            break;
        }


        // Set to zero. There are currently no flags that can be used in this parameter.
        hr = debugControl->WaitForEvent(0, INFINITE);
        if (!SUCCEEDED(hr))
        {
            break;
        }

        hr = jsrun(debugClient, "jstests/test.js");
        if (!SUCCEEDED(hr))
        {

            break;
        }


    } while (false);

    DebugExtensionUninitialize();

    if (nullptr != debugClient)
    {
        debugClient->SetOutputCallbacks(nullptr);

        // set event callbacks
        debugClient->SetEventCallbacks(nullptr);

        debugClient->Release();
        debugClient = nullptr;
    }

    if (nullptr != debugControl)
    {
        debugControl->Release();
        debugControl = nullptr;
    }

    if (nullptr != standardOutputCallbacks)
    {
        standardOutputCallbacks->Release();
        standardOutputCallbacks = nullptr;
    }

    if (nullptr != standardEventCallbacks)
    {
        standardEventCallbacks->Release();
        standardEventCallbacks = nullptr;
    }

    return 0;
}