/**
 * @file binding_system_objects2.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1
 */

#include <precompile.h>

#include "binding_dbgeng.h"


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetImplicitProcessDataOffset(

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

    ULONG64   offset = 0;

    do
    {
        hr = pthis->m_debugSystemObjects2->GetImplicitProcessDataOffset(&offset);
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetImplicitProcessDataOffset fail 0x%08X" , hr);
            break ;
        }

        JsExCreateUint64( offset , &result);

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetImplicitThreadDataOffset(

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

    ULONG64   offset = 0;

    do
    {
        hr = pthis->m_debugSystemObjects2->GetImplicitThreadDataOffset(&offset);
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetImplicitThreadDataOffset fail 0x%08X" , hr);
            break ;
        }

        JsExCreateUint64( offset , &result);

    } while (false);

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::SetImplicitProcessDataOffset(

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

    uint64_t    arg1Offset = 0;


    do
    {
        if ( argumentCount < 2 )
        {
            JsExThrowError("invalid argument cound %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[1] , &arg1Offset );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume offset fail 0x%08X" , errorCode);
            break;
        }

        hr = pthis->m_debugSystemObjects2->SetImplicitProcessDataOffset(arg1Offset);
        if  ( SUCCEEDED(hr) )
        {
            JsBoolToBoolean(true , &result);
        }
        else
        {
            JsBoolToBoolean(false , &result);
        }


    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::SetImplicitThreadDataOffset(

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

    uint64_t    arg1Offset = 0;


    do
    {
        if ( argumentCount < 2 )
        {
            JsExThrowError("invalid argument cound %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[1] , &arg1Offset );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume offset fail 0x%08X" , errorCode);
            break;
        }

        hr = pthis->m_debugSystemObjects2->SetImplicitThreadDataOffset(arg1Offset);
        if  ( SUCCEEDED(hr) )
        {
            JsBoolToBoolean(true , &result);
        }
        else
        {
            JsBoolToBoolean(false , &result);
        }

    } while (false);

    return result;
}