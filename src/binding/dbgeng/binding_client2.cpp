/**
 * @file binding_client2.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#include <precompile.h>

#include "binding_dbgeng.h"


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::IsKernelDebuggerEnabled(

    _In_ JsValueRef callee,

    _In_ bool isConstructCall,

    _In_ JsValueRef *arguments,

    _In_ unsigned short argumentCount,

    _In_opt_ void *callbackState
 )
  {
    BindingDbgEng *pthis = (BindingDbgEng *)(callbackState);

    JsValueRef result = nullptr;

    JsErrorCode errorCode = JsErrorFatal;

    HRESULT  hr = E_FAIL;

    do
    {
       hr = pthis->m_debugClient2->IsKernelDebuggerEnabled();
       if ( SUCCEEDED(hr) )
       {
           JsBoolToBoolean(true , &result );
       }
       else
       {
           JsBoolToBoolean(false , &result );
       }

    } while (false);

    return result;
}
