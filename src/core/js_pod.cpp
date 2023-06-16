/**
 * @file jswd_pod.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */
#include "precompile.h"

#include "binding/dbgeng/binding_dbgeng.h"

#include <gen/script/dbgeng.js.h>

#include <gen/script/jswd.js.h>

#include <gen/script/module.js.h>

#include <gen/script/reader.js.h>

#include <gen/script/register.js.h>

#include <gen/script/symbol.js.h>

#include <gen/script/virtual.js.h>

#include <gen/script/physical.js.h>

#include "js_pod.h"

JSPod::JSPod()
{
    this->m_runtime = nullptr;

    this->m_context = nullptr;

    this->m_binding = nullptr;

    this->m_builtin = nullptr;

    this->m_nativeRequire = nullptr;

    this->m_moduleRequire = nullptr;

    this->m_output = nullptr;

    /// for dbgeng

    this->m_debugClient = nullptr;

    this->m_debugControl = nullptr;
}

JSPod::~JSPod()
{
    if (nullptr != this->m_runtime)
    {
        JsSetCurrentContext(JS_INVALID_REFERENCE);

        JsDisposeRuntime(this->m_runtime);
        this->m_runtime = nullptr;
    }

    if (nullptr != this->m_debugClient)
    {
        this->m_debugClient->Release();
        this->m_debugClient = nullptr;
    }

    if (nullptr != this->m_debugControl)
    {
        this->m_debugControl->Release();
        this->m_debugControl = nullptr;
    }
}

HRESULT JSPod::Initialize()
{
    HRESULT result = E_FAIL;

    HRESULT hr = E_FAIL;

    JsErrorCode  errorCode = JsErrorFatal;

    do
    {
        hr = this->InitializeJSRT();
        if (!SUCCEEDED(hr))
        {
            break;
        }

        hr = this->InitializeDbgEng();
        if (!SUCCEEDED(hr))
        {
            break;
        }

        hr = this->SetupBindings();
        if (!SUCCEEDED(hr))
        {
            break;
        }

        // builtin script

        errorCode = this->m_builtin->RegisterSource(
            "dbgeng" ,
            std::string( (const char*)JSWD_BUILTIN_SCRIPT_DBGENG , SIZEOF_JSWD_BUILTIN_SCRIPT_DBGENG )
        );
        if ( JsNoError != errorCode )
        {
            break ;
        }



        errorCode = this->m_builtin->RegisterSource(
            "jswd/module" ,
            std::string( (const char*)JSWD_BUILTIN_SCRIPT_MODULE , SIZEOF_JSWD_BUILTIN_SCRIPT_MODULE )
        );
        if ( JsNoError != errorCode )
        {
            break ;
        }

         errorCode = this->m_builtin->RegisterSource(
            "jswd/physical" ,
            std::string( (const char*)JSWD_BUILTIN_SCRIPT_PHYSICAL , SIZEOF_JSWD_BUILTIN_SCRIPT_PHYSICAL )
        );
        if ( JsNoError != errorCode )
        {
            break ;
        }

        errorCode = this->m_builtin->RegisterSource(
            "jswd/reader" ,
            std::string( (const char*)JSWD_BUILTIN_SCRIPT_READER , SIZEOF_JSWD_BUILTIN_SCRIPT_READER )
        );
        if ( JsNoError != errorCode )
        {
            break ;
        }

        errorCode = this->m_builtin->RegisterSource(
            "jswd/register" ,
            std::string( (const char*)JSWD_BUILTIN_SCRIPT_REGISTER , SIZEOF_JSWD_BUILTIN_SCRIPT_REGISTER )
        );
        if ( JsNoError != errorCode )
        {
            break ;
        }

         errorCode = this->m_builtin->RegisterSource(
            "jswd/symbol" ,
            std::string( (const char*)JSWD_BUILTIN_SCRIPT_SYMBOL , SIZEOF_JSWD_BUILTIN_SCRIPT_SYMBOL )
        );
        if ( JsNoError != errorCode )
        {
            break ;
        }

         errorCode = this->m_builtin->RegisterSource(
            "jswd/virtual" ,
            std::string( (const char*)JSWD_BUILTIN_SCRIPT_VIRTUAL , SIZEOF_JSWD_BUILTIN_SCRIPT_VIRTUAL )
        );
        if ( JsNoError != errorCode )
        {
            break ;
        }


        errorCode = this->m_builtin->RegisterSource(
            "jswd" ,
            std::string( (const char*)JSWD_BUILTIN_SCRIPT_JSWD , SIZEOF_JSWD_BUILTIN_SCRIPT_JSWD )
            );
        if ( JsNoError != errorCode )
        {
            break ;
        }

        // query real output
        hr = this->m_binding->GetValue("stdio", "output", &(this->m_output));
        if (!SUCCEEDED(hr))
        {
            break;
        }

        hr = this->BootstrapJSRT();
        if (!SUCCEEDED(hr))
        {
            this->PrintException();
            break;
        }

        result = S_OK;
    } while (false);

    return result;
}

HRESULT JSPod::InitializeJSRT()
{
    HRESULT result = E_FAIL;

    JsErrorCode errorCode = JsErrorFatal;

    bool ok = false;

    uint32_t refs = 0;

    do
    {
        this->m_runtime = JsExCreateRuntime(false);
        if (nullptr == this->m_runtime)
        {
            break;
        }

        errorCode = JsExCreateContext(this->m_runtime, &(this->m_context));
        if (JsNoError != errorCode)
        {
            break;
        }

        JsAddRef(this->m_context, &refs);

        errorCode = JsSetCurrentContext(this->m_context);
        if (JsNoError != errorCode)
        {
            break;
        }

        this->m_binding = NativeBinding::Create();
        if (nullptr == this->m_binding)
        {
            break;
        }

        this->m_builtin = NativeBuiltin::Create();
        if (nullptr == this->m_builtin)
        {
            break;
        }

        this->m_nativeRequire = NativeRequire::Create();
        if (nullptr == this->m_nativeRequire)
        {
            break;
        }

        ok = this->m_nativeRequire->RegisterModule("builtin", this->m_builtin->GetHandle());
        if (!ok)
        {
            break;
        }

        ok = this->m_nativeRequire->RegisterModule("binding", this->m_binding->GetHandle());
        if (!ok)
        {
            break;
        }

        result = S_OK;
    } while (false);

    return result;
}

HRESULT JSPod::InitializeDbgEng()
{
    HRESULT result = E_FAIL;

    HRESULT hr = E_FAIL;

    do
    {

        hr = DebugCreate(__uuidof(IDebugClient), (PVOID *)&(this->m_debugClient));
        if (!SUCCEEDED(hr))
        {
            break;
        }

        hr = this->m_debugClient->QueryInterface(__uuidof(IDebugControl), (PVOID *)&(this->m_debugControl));
        if (!SUCCEEDED(hr))
        {
            break;
        }

        result = S_OK;
    } while (false);

    return result;
}

HRESULT JSPod::SetupBindings()
{
    HRESULT result = E_FAIL;

    HRESULT hr = E_FAIL;

    JsErrorCode errorCode = JsErrorFatal;

    BindingDbgEng *dbgeng = nullptr;

    do
    {
        dbgeng = new BindingDbgEng(this->m_debugClient, this->m_debugControl);

        errorCode = dbgeng->Initialize();
        if (JsNoError != errorCode)
        {
            break;
        }

        // for binding

        errorCode = this->m_binding->SetValue("", "dbgeng", dbgeng->GetHandle());
        if (JsNoError != errorCode)
        {
            break;
        }

        // overwrite output
        errorCode = this->m_binding->SetRoutine("stdio", "output", dbgeng->ControlOutput, dbgeng);
        if (JsNoError != errorCode)
        {
            break;
        }



        result = S_OK;

    } while (false);

    return result;
}

HRESULT JSPod::BootstrapJSRT()
{
    HRESULT result = E_FAIL;

    JsErrorCode errorCode = JsErrorFatal;

    uint32_t refs = 0;

    do
    {
        errorCode = JsExBootstrap(this->m_nativeRequire->GetHandle(), &(this->m_moduleRequire));
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = JsAddRef(this->m_moduleRequire, &refs);
        if (JsNoError != errorCode)
        {
            break;
        }

        result = S_OK;
    } while (false);

    return result;
}

JsErrorCode JSPod::RequireModule(_In_ const std::string &filename, _Out_ JsValueRef *exports)
{
    return JsExRequireModule(this->m_moduleRequire, filename, exports);
}

JsErrorCode JSPod::PrintException()
{
    return JsExDumpException(this->m_output);
}

void __cdecl JSPod::DebugPrintf(_In_ const char *format, ...)
{
    va_list args;

    va_start(args, format);

    this->m_debugControl->ControlledOutputVaList(DEBUG_OUTCTL_ALL_CLIENTS, DEBUG_OUTPUT_NORMAL, format, args);

    va_end(args);
}
