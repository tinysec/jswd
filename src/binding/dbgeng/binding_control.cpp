/**
 * @file binding_control.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#include <precompile.h>

#include "callbacks/captured_output_callbacks.h"

#include "binding_dbgeng.h"



_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::Execute(

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

    HRESULT   hr = E_FAIL;

    std::string command;

    bool echo = false;

    bool logged = true;

    bool repeat = true;

    IDebugOutputCallbacks* oldOutput = nullptr;

    CapturedOutputCallbacks* subOutput = nullptr;


    ULONG controlFlags = DEBUG_OUTCTL_THIS_CLIENT;

    ULONG  executeFlags = 0;

    std::string  capturedText;

    do
    {
        if (argumentCount < 1)
        {
            break;
        }

        if ( argumentCount >= 2 )
        {
            errorCode = JsExAssumeString( arguments[1] , true , &command);
            if ( JsNoError != errorCode )
            {
                break ;
            }
        }

        if ( argumentCount >= 3 )
        {
            errorCode = JsExGetPropertyBool( arguments[2] , "echo" , false , &echo);
            if ( JsNoError != errorCode )
            {
                break ;
            }

            errorCode = JsExGetPropertyBool( arguments[2] , "logged" , false , &logged);
            if ( JsNoError != errorCode )
            {
                break ;
            }

            errorCode = JsExGetPropertyBool( arguments[2] , "repeat" , false , &repeat);
            if ( JsNoError != errorCode )
            {
                break ;
            }
        }


        if ( echo )
        {
            executeFlags |= DEBUG_EXECUTE_ECHO;
        }

        if ( !logged )
        {
            executeFlags |= DEBUG_EXECUTE_NOT_LOGGED;
        }

        if ( !repeat )
        {
            executeFlags |= DEBUG_EXECUTE_NO_REPEAT;
        }

        // get the old
        hr = pthis->m_debugClient->GetOutputCallbacks( &oldOutput );
        if ( !SUCCEEDED(hr) )
        {
            break ;
        }

        subOutput = new CapturedOutputCallbacks();

        hr = pthis->m_debugClient->SetOutputCallbacks( subOutput );
        if ( !SUCCEEDED(hr) )
        {
            break ;
        }

        pthis->m_debugControl->Execute(
            controlFlags ,
            command.c_str() ,
            executeFlags
        );

        // recover
        pthis->m_debugClient->SetOutputCallbacks( oldOutput );

        capturedText = subOutput->GetCapturedText();

        JsExCreateString(

            capturedText.c_str() ,

            capturedText.length() ,

            &result
        );

    } while (false);

    if (nullptr != subOutput )
    {
        delete subOutput;
        subOutput = nullptr;
    }

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetNumberProcessors(

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

    ULONG  number = 0;

    do
    {
        if (argumentCount < 1)
        {
            break;
        }

        hr = pthis->m_debugControl->GetNumberProcessors(&number);
        if ( !SUCCEEDED(hr) )
        {
            break ;
        }

        JsIntToNumber( (int)number , &result );

    } while (false);

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetPageSize(

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

    ULONG  size = 0;

    do
    {
        if (argumentCount < 1)
        {
            break;
        }

        hr = pthis->m_debugControl->GetPageSize(&size);
        if ( !SUCCEEDED(hr) )
        {
            break ;
        }

        JsIntToNumber( (int)size , &result );

    } while (false);

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::IsPointer64Bit(

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
        if (argumentCount < 1)
        {
            break;
        }

        hr = pthis->m_debugControl->IsPointer64Bit();
        if ( SUCCEEDED(hr) )
        {
            JsBoolToBoolean( true , &result);
        }
        else
        {
            JsBoolToBoolean( false , &result);
        }

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::ControlOutput(

    _In_ JsValueRef callee,

    _In_ bool isConstructCall,

    _In_ JsValueRef *arguments,

    _In_ unsigned short argumentCount,

    _In_opt_ void *callbackState)
{
    BindingDbgEng *pthis = (BindingDbgEng *)(callbackState);

    JsValueRef result = nullptr;

    JsErrorCode errorCode = JsErrorFatal;

    std::string text;

    do
    {
        if (argumentCount < 1)
        {
            break;
        }

        errorCode = JsExAssumeString(arguments[1], true, &text);
        if (JsNoError != errorCode)
        {
            break;
        }

        if (text.empty())
        {
            break;
        }

        pthis->m_debugControl->ControlledOutput(
            DEBUG_OUTCTL_ALL_CLIENTS | DEBUG_OUTCTL_DML,
            DEBUG_OUTPUT_NORMAL,
            "%s",
            text.c_str()
            );

    } while (false);

    return result;
}