/**
 * @file bingd_data_spaces.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */
#include <precompile.h>

#include "binding_dbgeng.h"



 _Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::ReadDebuggerData(

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

    uint32_t  argIndex = 0;

    BYTE* argBuffer = nullptr;

    UINT32   bufferSize = 0;

    ULONG  dataSize = 0;


    do
    {
        if (argumentCount < 3)
        {
            break;
        }

        errorCode = JsExAssumeUint32(  arguments[1] , true , &argIndex );
        if ( JsNoError != errorCode )
        {
            break ;
        }

        errorCode = JsGetArrayBufferStorage( arguments[2] , &argBuffer , &bufferSize);
        if ( JsNoError != errorCode )
        {
            break ;
        }

        hr = pthis->m_debugDataSpaces->ReadDebuggerData(argIndex , argBuffer , bufferSize , &dataSize );
        if  ( !SUCCEEDED(hr) )
        {
            break ;
        }

        JsIntToNumber((int)dataSize , &result);

    } while (false);

    return result;
}