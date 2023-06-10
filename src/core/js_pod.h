/**
 * @file jswd_pod.h
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#ifndef __MY_JS_POD_HEADER_FILE__
#define __MY_JS_POD_HEADER_FILE__
////////////////////////////////////////////////////

#include "precompile.h"

#include "callbacks/standard_output_callbacks.h"

#include "callbacks/standard_event_callbacks.h"

class JSPod
{
  public:
    JSPod();

    ~JSPod();

  public:
    HRESULT Initialize();

    JsErrorCode RequireModule(_In_ const std::string &filename, _Out_ JsValueRef *exports);

    JsErrorCode PrintException();

    void __cdecl DebugPrintf(_In_ const char *format, ...);

  protected:
    HRESULT InitializeJSRT();

    HRESULT InitializeDbgEng();

    HRESULT SetupBindings();

    HRESULT BootstrapJSRT();

  public:
    JsRuntimeHandle m_runtime;

    JsContextRef m_context;

    NativeBinding *m_binding;

    NativeBuiltin *m_builtin;

    NativeRequire *m_nativeRequire;

    JsValueRef m_moduleRequire;

    JsValueRef m_output;

  public:
    IDebugClient *m_debugClient;

    IDebugControl *m_debugControl;
};

////////////////////////////////////////////////////
#endif //__MY_JS_POD_HEADER_FILE__
