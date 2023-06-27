/**
 * @file binding_system_object.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */
#include <precompile.h>

#include "binding_dbgeng.h"


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetCurrentProcessDataOffset(

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

    ULONG64     offset = 0;

    do
    {
        hr = pthis->m_debugSystemObjects->GetCurrentProcessDataOffset(&offset);
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetCurrentProcessDataOffset fail 0x%08X" , hr);
            break ;
        }

        JsExCreateUint64( offset , &result);

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetCurrentProcessId(

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

    ULONG   id = 0;

    do
    {
        hr = pthis->m_debugSystemObjects->GetCurrentProcessId(&id);
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetCurrentProcessId fail 0x%08X" , hr);
            break ;
        }

        JsIntToNumber( (int)id , &result);

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetCurrentProcessPeb(

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

    ULONG64     offset = 0;

    do
    {
        hr = pthis->m_debugSystemObjects->GetCurrentProcessPeb(&offset);
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetCurrentProcessPeb fail 0x%08X" , hr);
            break ;
        }

        JsExCreateUint64( offset , &result);

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetCurrentProcessSystemId(

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

    ULONG   id = 0;

    do
    {
        hr = pthis->m_debugSystemObjects->GetCurrentProcessSystemId(&id);
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetCurrentProcessSystemId fail 0x%08X" , hr);
            break ;
        }

        JsIntToNumber( (int)id , &result);

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetCurrentThreadDataOffset(

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

    ULONG64     offset = 0;

    do
    {
        hr = pthis->m_debugSystemObjects->GetCurrentThreadDataOffset(&offset);
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetCurrentThreadDataOffset fail 0x%08X" , hr);
            break ;
        }

        JsExCreateUint64( offset , &result);

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetCurrentThreadId(

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

    ULONG   id = 0;

    do
    {
        hr = pthis->m_debugSystemObjects->GetCurrentThreadId(&id);
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetCurrentThreadId fail 0x%08X" , hr);
            break ;
        }

        JsIntToNumber( (int)id , &result);

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetCurrentThreadSystemId(

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

    ULONG   id = 0;

    do
    {
        hr = pthis->m_debugSystemObjects->GetCurrentThreadSystemId(&id);
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetCurrentThreadSystemId fail 0x%08X" , hr);
            break ;
        }

        JsIntToNumber( (int)id , &result);

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetCurrentThreadTeb(

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

    ULONG64     offset = 0;

    do
    {
        hr = pthis->m_debugSystemObjects->GetCurrentThreadTeb(&offset);
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetCurrentThreadTeb fail 0x%08X" , hr);
            break ;
        }

        JsExCreateUint64( offset , &result);

    } while (false);

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetThreadIdByProcessor(

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

    uint32_t    arg1Processor = 0;

    ULONG     id = 0;

    do
    {
        if ( argumentCount < 2 )
        {
            JsExThrowError("invalid argument cound %d" , argumentCount);
            break;
        }

         errorCode = JsExAssumeUint32( arguments[1] , &arg1Processor );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume processor fail 0x%08X" , errorCode);
            break;
        }

        hr = pthis->m_debugSystemObjects->GetThreadIdByProcessor(arg1Processor , &id);
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetThreadIdByProcessor fail 0x%08X" , hr);
            break ;
        }

        JsIntToNumber( (int)id , &result);

    } while (false);

    return result;
}



_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::SetCurrentThreadId(

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

    uint64_t    arg1Id = 0;


    do
    {
        if ( argumentCount < 2 )
        {
            JsExThrowError("invalid argument cound %d" , argumentCount);
            break;
        }

         errorCode = JsExAssumeUint64( arguments[1] , &arg1Id );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume id fail 0x%08X" , errorCode);
            break;
        }

        hr = pthis->m_debugSystemObjects->SetCurrentThreadId(arg1Id);
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

