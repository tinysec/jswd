/**
 * @file binding_control.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#include <precompile.h>

#include "callbacks/captured_output_callbacks.h"

#include "binding_dbgeng.h"



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
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeString(arguments[1], true, &text);
        if (JsNoError != errorCode)
        {
            JsExThrowError("assume text fail 0x%08X" , errorCode);
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




_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::Assemble(

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

    uint64_t  arg1Offset = 0;

    std::string arg2Instruction;

    ULONG64   endOffset = 0;

    do
    {
        if (argumentCount < 3)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[1] , &arg1Offset );
        if ( JsNoError != errorCode )
        {
             JsExThrowError("assume offset fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExAssumeString( arguments[2] , true , &arg2Instruction );
        if ( JsNoError != errorCode )
        {
             JsExThrowError("assume instruction fail 0x%08X" , errorCode);
            break;
        }

        hr = pthis->m_debugControl->Assemble(
                arg1Offset ,
                arg2Instruction.c_str() ,
                &endOffset
        );

        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("Assemble fail 0x%08X" , hr);
            break;
        }

        JsExCreateUint64( endOffset , &result);

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::CallExtension(

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

    uint64_t   arg1Handle = 0;

    std::string  arg2Function;

    std::string  arg3Arguments;

   IDebugOutputCallbacks* oldOutput = nullptr;

    CapturedOutputCallbacks* subOutput = nullptr;

    std::string  capturedText;

    do
    {
        if (argumentCount < 3)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[1] , &arg1Handle );
        if ( JsNoError != errorCode )
        {
             JsExThrowError("assume handle fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExAssumeString( arguments[2] , true , &arg2Function );
        if ( JsNoError != errorCode )
        {
             JsExThrowError("assume function fail 0x%08X" , errorCode);
            break;
        }

        if ( argumentCount >= 4 )
        {
            errorCode = JsExAssumeString( arguments[3] , true , &arg3Arguments );
            if ( JsNoError != errorCode )
            {
                 JsExThrowError("assume arguments fail 0x%08X" , errorCode);
                break;
            }
        }

         // get the old
        hr = pthis->m_debugClient->GetOutputCallbacks( &oldOutput );
        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetOutputCallbacks fail 0x%08X" , errorCode );
            break ;
        }

        subOutput = new CapturedOutputCallbacks();

        hr = pthis->m_debugClient->SetOutputCallbacks( subOutput );
        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("SetOutputCallbacks fail 0x%08X" , errorCode );
            break ;
        }

        hr = pthis->m_debugControl->CallExtension(
                arg1Handle ,
                arg2Function.c_str(),
                arg3Arguments.empty() ? nullptr : arg3Arguments.c_str()
        );

        // recover
        pthis->m_debugClient->SetOutputCallbacks( oldOutput );

        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("CallExtension fail 0x%08X" , hr);
            break;
        }

        capturedText = subOutput->GetCapturedText();

        JsExCreateString(

            capturedText.c_str() ,

            capturedText.length() ,

            &result
        );

    } while (false);

    if (nullptr != oldOutput )
    {
        oldOutput->Release();
        oldOutput = nullptr;
    }

    if (nullptr != subOutput )
    {
        subOutput->Release();
        subOutput = nullptr;
    }

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::Disassemble(

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

    uint64_t  arg1Offset = 0;

    uint32_t  arg2Flags = 0;

    std::vector<char> buffer;

    ULONG       bufferSize = 0;

    ULONG       dataSize = 0;

    ULONG64     endOffset = 0;

    JsValueRef  info = nullptr;

    do
    {
        if (argumentCount < 3)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[1] , &arg1Offset );
        if ( JsNoError != errorCode )
        {
             JsExThrowError("assume offset fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[2] , &arg2Flags );
        if ( JsNoError != errorCode )
        {
             JsExThrowError("assume flags fail 0x%08X" , errorCode);
            break;
        }

        hr = pthis->m_debugControl->Disassemble(
                arg1Offset ,
                arg2Flags ,
                nullptr,
                0,
                &bufferSize,
                &endOffset
        );

        if ( 0 == bufferSize )
        {
            JsExThrowError("Disassemble fail 0x%08X" , hr);
            break;
        }

        buffer.resize( bufferSize );

         hr = pthis->m_debugControl->Disassemble(
                arg1Offset ,
                arg2Flags ,
                buffer.data(),
                bufferSize,
                &dataSize,
                &endOffset
        );

         if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("Disassemble fail 0x%08X" , hr);
            break;
        }

        errorCode = JsCreateObject( &info );
        if ( JsNoError != errorCode )
        {
             JsExThrowError("JsCreateObject 0x%08X" , errorCode);
            break;
        }

        if  ( dataSize > 1 )
        {
             errorCode = JsExSetPropertyString(
                info ,
                "text" ,
                std::string(  buffer.data() , dataSize ),
                true
             );

             if ( JsNoError != errorCode )
            {
                 JsExThrowError("JsExSetPropertyString fail 0x%08X" , errorCode);
                break;
            }
        }
        else
        {
            errorCode = JsExSetPropertyString(
                info ,
                "text" ,
               "",
                true
             );

             if ( JsNoError != errorCode )
            {
                 JsExThrowError("JsExSetPropertyString fail 0x%08X" , errorCode);
                break;
            }
        }

        errorCode = JsExSetPropertyUint64(
                info ,
                "endOffset",
                true ,
                endOffset
       );

        if ( JsNoError != errorCode )
        {
             JsExThrowError("JsExSetPropertyUint64 fail 0x%08X" , errorCode);
            break;
        }

        result = info;

    } while (false);

    return result;
}



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


    ULONG controlFlags = DEBUG_OUTCTL_THIS_CLIENT;

    ULONG  executeFlags = 0;


    IDebugOutputCallbacks* oldOutput = nullptr;

    CapturedOutputCallbacks* subOutput = nullptr;

    std::string  capturedText;

    do
    {
        if (argumentCount < 1)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        if ( argumentCount >= 2 )
        {
            errorCode = JsExAssumeString( arguments[1] , true , &command);
            if ( JsNoError != errorCode )
            {
                JsExThrowError("command must be string" );
                break ;
            }
        }

        if ( argumentCount >= 3 )
        {
            errorCode = JsExGetPropertyBool( arguments[2] , "echo" , false , &echo);
            if ( JsNoError != errorCode )
            {
                JsExThrowError("assume echo fail 0x%08X" , errorCode );
                break ;
            }

            errorCode = JsExGetPropertyBool( arguments[2] , "logged" , false , &logged);
            if ( JsNoError != errorCode )
            {
                JsExThrowError("assume logged fail 0x%08X" , errorCode );
                break ;
            }

            errorCode = JsExGetPropertyBool( arguments[2] , "repeat" , false , &repeat);
            if ( JsNoError != errorCode )
            {
                JsExThrowError("assume repeat fail 0x%08X" , errorCode );
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
            JsExThrowError("GetOutputCallbacks fail 0x%08X" , errorCode );
            break ;
        }

        subOutput = new CapturedOutputCallbacks();

        hr = pthis->m_debugClient->SetOutputCallbacks( subOutput );
        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("SetOutputCallbacks fail 0x%08X" , errorCode );
            break ;
        }

        hr = pthis->m_debugControl->Execute(
            controlFlags ,
            command.c_str() ,
            executeFlags
        );

        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("Execute fail 0x%08X" , hr );
            break ;
        }

        // recover
        pthis->m_debugClient->SetOutputCallbacks( oldOutput );

        capturedText = subOutput->GetCapturedText();

        JsExCreateString(

            capturedText.c_str() ,

            capturedText.length() ,

            &result
        );

    } while (false);

    if (nullptr != oldOutput )
    {
        oldOutput->Release();
        oldOutput = nullptr;
    }

    if (nullptr != subOutput )
    {
        subOutput->Release();
        subOutput = nullptr;
    }

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetActualProcessorType(

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

    ULONG  processorType = 0;

    do
    {

        hr = pthis->m_debugControl->GetActualProcessorType( &processorType );
         if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetActualProcessorType fail 0x%08X" , hr );
            break ;
        }

        JsIntToNumber( (int)processorType , &result );

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetCodeLevel(

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

    ULONG level = 0;

    do
    {
        hr = pthis->m_debugControl->GetCodeLevel( &level );
        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetCodeLevel fail 0x%08X" , hr );
            break ;
        }

        JsIntToNumber( (int)level , &result );


    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetDebuggeeType(

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

    ULONG       debuggeeClass = 0;

    ULONG       qualifier = 0;

    JsValueRef  info = nullptr;

    do
    {
        hr = pthis->m_debugControl->GetDebuggeeType( &debuggeeClass , &qualifier );
        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetDebuggeeType fail 0x%08X" , hr );
            break ;
        }

        errorCode = JsCreateObject( &info );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsCreateObject fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsExSetPropertyInt(info , "type" , debuggeeClass , true );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsExSetPropertyInt fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsExSetPropertyInt(info , "qualifier" , qualifier , true );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsExSetPropertyInt fail 0x%08X" , errorCode );
            break;
        }

        result = info;

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetEffectiveProcessorType(

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

    ULONG  processorType = 0;

    do
    {
        hr = pthis->m_debugControl->GetEffectiveProcessorType( &processorType );

        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetEffectiveProcessorType fail 0x%08X" , hr );
            break ;
        }

        JsIntToNumber( (int)processorType , &result );

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetExecutingProcessorType(

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

    ULONG  processorType = 0;

    do
    {
        hr = pthis->m_debugControl->GetExecutingProcessorType( &processorType );
        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetExecutingProcessorType fail 0x%08X" , hr );
            break ;
        }

        JsIntToNumber( (int)processorType , &result );


    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetExecutionStatus(

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

    ULONG status = 0;

    do
    {
        hr = pthis->m_debugControl->GetExecutionStatus( &status );
        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetExecutionStatus fail 0x%08X" , hr );
            break ;
        }

        JsIntToNumber( (int)status , &result );

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetNearInstruction(

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

    int32_t     arg2Delta = 0;

    ULONG64     nearOffset = 0;


    do
    {
        if (argumentCount < 2)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[1] , &arg1Offset );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume offset fail 0x%08X" , errorCode );
            break;
        }

        if ( argumentCount >= 3 )
        {
            errorCode = JsExAssumeInt32( arguments[2] , &arg2Delta );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("assume delta fail 0x%08X" , errorCode );
                break;
            }
        }

        hr = pthis->m_debugControl->GetNearInstruction(
                arg1Offset ,
                arg2Delta,
                &nearOffset
        );
        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetNearInstruction fail 0x%08X" , hr );
            break ;
        }

        JsExCreateUint64( nearOffset , &result );

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetNumberPossibleExecutingProcessorTypes(

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

    ULONG   processorTypes = 0;

    do
    {

        hr = pthis->m_debugControl->GetNumberPossibleExecutingProcessorTypes( &processorTypes );
        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetNumberPossibleExecutingProcessorTypes fail 0x%08X" , hr );
            break ;
        }

        JsIntToNumber( (int)processorTypes , &result );

    } while (false);

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
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        hr = pthis->m_debugControl->GetNumberProcessors(&number);
        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetNumberProcessors fail 0x%08X" , hr);
            break ;
        }

        JsIntToNumber( (int)number , &result );

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetNumberSupportedProcessorTypes(

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

    ULONG   processorTypes = 0;

    do
    {

        hr = pthis->m_debugControl->GetNumberSupportedProcessorTypes( &processorTypes );
        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetNumberSupportedProcessorTypes fail 0x%08X" , hr );
            break ;
        }

        JsIntToNumber( (int)processorTypes , &result );

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
        hr = pthis->m_debugControl->GetPageSize(&size);
        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetPageSize fail 0x%08X" , hr );
            break ;
        }

        JsIntToNumber( (int)size , &result );

    } while (false);

    return result;
}


 _Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetProcessorTypeNames(

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

    uint32_t    arg1Type = 0;

    std::vector<char> fullName;

    ULONG       fullNameBufferSize = 0;

    ULONG       fullNameDataSize = 0;

     std::vector<char> abbrevName;

    ULONG       abbrevNameBufferSize = 0;

    ULONG       abbrevNameDataSize = 0;

    JsValueRef   info = nullptr;

    do
    {
        if (argumentCount < 2)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[1] , &arg1Type );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume type fail 0x%08X" , errorCode);
            break;
        }

        pthis->m_debugControl->GetProcessorTypeNames(
                arg1Type ,
                nullptr,
                0,
                &fullNameBufferSize,
                nullptr,
                0,
                &abbrevNameBufferSize
        );


        if ( 0 != fullNameBufferSize )
        {
            fullName.resize(fullNameBufferSize);
        }

        if ( 0 != abbrevNameBufferSize )
        {
            abbrevName.resize(abbrevNameBufferSize);
        }


        hr = pthis->m_debugControl->GetProcessorTypeNames(
                arg1Type ,
                0 == fullNameBufferSize ? nullptr : fullName.data() ,
                fullNameBufferSize,
                &fullNameDataSize,
                0 == abbrevNameBufferSize ? nullptr : abbrevName.data(),
                abbrevNameBufferSize,
                &abbrevNameDataSize
        );
        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetProcessorTypeNames fail 0x%08X" , hr );
            break ;
        }

        errorCode = JsCreateObject( &info );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsCreateObject fail 0x%08X" , errorCode);
            break;
        }

        if ( fullNameDataSize > 1 )
        {
            errorCode = JsExSetPropertyString(
                    info ,
                    "fullname" ,
                    std::string( fullName.data() ,fullNameDataSize ) ,
                    true
            );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsExSetPropertyString fail 0x%08X" , errorCode);
                break;
            }
        }
        else
        {
            errorCode = JsExSetPropertyString(
                    info ,
                    "fullname" ,
                    "" ,
                    true
            );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsExSetPropertyString fail 0x%08X" , errorCode);
                break;
            }
        }

        if ( abbrevNameDataSize > 1 )
        {
            errorCode = JsExSetPropertyString(
                    info ,
                    "abbrevName" ,
                    std::string( abbrevName.data() ,abbrevNameDataSize ) ,
                    true
            );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsExSetPropertyString fail 0x%08X" , errorCode);
                break;
            }
        }
        else
        {
            errorCode = JsExSetPropertyString(
                    info ,
                    "abbrevName" ,
                    "" ,
                    true
            );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsExSetPropertyString fail 0x%08X" , errorCode);
                break;
            }
        }

        result = info;

    } while (false);

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetReturnOffset(

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

    ULONG64  offset = 0;

    do
    {

        hr = pthis->m_debugControl->GetReturnOffset( &offset );
        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetReturnOffset fail 0x%08X" , hr );
            break ;
        }

        JsExCreateUint64( offset , &result );

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetStackTrace(

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

    JsErrorCode finalCode = JsErrorFatal;

    HRESULT  hr = E_FAIL;

    uint64_t  arg1FrameOffset  = 0;

    uint64_t  arg2StackOffset  = 0;

    uint64_t  arg3InstructionOffset  = 0;

    uint32_t  arg4Depth = 0;

    DEBUG_STACK_FRAME*  frameBuffer = nullptr;

    ULONG       framesFilled = 0;

    JsValueRef   frameArray = nullptr;

    ULONG        i = 0;

    JsValueRef   frame = nullptr;

    JsValueRef   paramArray = nullptr;

    JsValueRef   param = nullptr;

    ULONG        j = 0;

    do
    {
        if (argumentCount < 1)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[1] , &arg1FrameOffset );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume frame offset fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[2] , &arg2StackOffset );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume stack offset fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[3] , &arg3InstructionOffset );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume instruction offset fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[4] , &arg4Depth );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume depth fail 0x%08X" , errorCode);
            break;
        }

        if ( 0 == arg4Depth )
        {
            JsExThrowError("empty frame depth" );
            break;
        }

        frameBuffer = (DEBUG_STACK_FRAME*)malloc( sizeof(DEBUG_STACK_FRAME) * arg4Depth );
        if (nullptr == frameBuffer )
        {
            JsExThrowError("alloc %d frame buffer fail" , arg4Depth );
            break;
        }

        RtlZeroMemory( frameBuffer , sizeof(DEBUG_STACK_FRAME) * arg4Depth );

        hr = pthis->m_debugControl->GetStackTrace(
                arg1FrameOffset,
                arg2StackOffset,
                arg3InstructionOffset,
                frameBuffer,
                arg4Depth,
                &framesFilled
        );
        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetStackTrace fail 0x%08X" , hr );
            break ;
        }

        if ( 0 == framesFilled )
        {
            JsExThrowError("empty frame filled" );
            break;
        }

        // build frame object frameArray

        errorCode = JsCreateArray( framesFilled , &frameArray );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsCreateArray fail 0x%08X" , errorCode);
            break;
        }

        for ( i = 0; i < framesFilled; i++ )
        {
            errorCode = JsCreateObject( &frame );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsCreateObject fail 0x%08X" , errorCode);
                break;
            }

            errorCode = JsExSetPropertyUint64(frame , "instructionOffset" , frameBuffer[i].InstructionOffset , true );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsExSetPropertyUint64 fail 0x%08X" , errorCode);
                break;
            }

            errorCode = JsExSetPropertyUint64(frame , "returnOffset" , frameBuffer[i].ReturnOffset , true );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsExSetPropertyUint64 fail 0x%08X" , errorCode);
                break;
            }

            errorCode = JsExSetPropertyUint64(frame , "frameOffset" , frameBuffer[i].FrameOffset , true );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsExSetPropertyUint64 fail 0x%08X" , errorCode);
                break;
            }

            errorCode = JsExSetPropertyUint64(frame , "stackOffset" , frameBuffer[i].StackOffset , true );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsExSetPropertyUint64 fail 0x%08X" , errorCode);
                break;
            }

            errorCode = JsExSetPropertyUint64(frame , "funcTableEntry" , frameBuffer[i].FuncTableEntry , true );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsExSetPropertyUint64 fail 0x%08X" , errorCode);
                break;
            }

            // Params
            errorCode = JsCreateArray( 4 , &paramArray );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsCreateArray fail 0x%08X" , errorCode);
                break;
            }

            for ( j = 0; j < 4;  j++ )
            {
                errorCode = JsExCreateUint64( frameBuffer[i].Params[j] , &param );
                if ( JsNoError != errorCode )
                {
                    JsExThrowError("JsExCreateUint64 fail 0x%08X" , errorCode);
                    break;
                }

                errorCode = JsExSetArrayElement( paramArray , j , param );
                if ( JsNoError != errorCode )
                {
                    JsExThrowError("JsExSetArrayElement fail 0x%08X" , errorCode);
                    break;
                }
            }


            errorCode = JsExSetPropertyBool(frame , "virtual" , frameBuffer[i].Virtual , true );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsExSetPropertyBool fail 0x%08X" , errorCode);
                break;
            }

            errorCode = JsExSetPropertyUint32(frame , "frameNumber" , frameBuffer[i].FrameNumber , true );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsExSetPropertyUint32 fail 0x%08X" , errorCode);
                break;
            }

            errorCode = JsExSetArrayElement( frameArray , i , frame );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsExSetArrayElement fail 0x%08X" , errorCode);
                break;
            }
        }

        result = frameArray;

    } while (false);

    if (nullptr != frameBuffer )
    {
        free(frameBuffer);
        frameBuffer = nullptr;
    }

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetSystemVersion(

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

    ULONG   platformId = 0;

    ULONG   major = 0;

    ULONG   minor = 0;

    std::vector<char> servicePackString;

    ULONG       servicePackStringBufferSize = 0;

    ULONG       servicePackStringDataSize = 0;


    ULONG       servicePackNumber = 0;


     std::vector<char> buildString;

    ULONG       buildStringBufferSize = 0;

    ULONG       buildStringDataSize = 0;

    JsValueRef  info = nullptr;

    do
    {
        pthis->m_debugControl->GetSystemVersion(
                &platformId ,
                &major,
                &minor,
                nullptr,
                0,
                &servicePackStringBufferSize,
                &servicePackNumber,
                nullptr,
                0,
                &buildStringBufferSize
        );

        if ( 0 != servicePackStringBufferSize )
        {
            servicePackString.resize( servicePackStringBufferSize );
        }

        if ( 0 != buildStringBufferSize )
        {
            buildString.resize( buildStringBufferSize );
        }


         hr = pthis->m_debugControl->GetSystemVersion(
                &platformId ,
                &major,
                &minor,
                0 == servicePackStringBufferSize ? nullptr : servicePackString.data(),
                servicePackStringBufferSize,
                &servicePackStringDataSize,
                &servicePackNumber,
                0 == buildStringBufferSize ? nullptr : buildString.data(),
                buildStringBufferSize,
                &buildStringDataSize
        );

         if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetSystemVersion fail 0x%08X" , hr );
            break ;
        }

        errorCode = JsCreateObject( &info );
         if ( JsNoError != errorCode )
         {
              JsExThrowError("JsCreateObject fail 0x%08X" , errorCode );
             break;
         }

        errorCode = JsExSetPropertyInt(info , "platformId" , (int)platformId , true );
         if ( JsNoError != errorCode )
         {
              JsExThrowError("JsExSetPropertyInt fail 0x%08X" , errorCode );
             break;
         }

         errorCode = JsExSetPropertyInt(info , "major" , (int)major , true );
         if ( JsNoError != errorCode )
         {
              JsExThrowError("JsExSetPropertyInt fail 0x%08X" , errorCode );
             break;
         }

         errorCode = JsExSetPropertyInt(info , "minor" , (int)minor , true );
         if ( JsNoError != errorCode )
         {
              JsExThrowError("JsExSetPropertyInt fail 0x%08X" , errorCode );
             break;
         }

         if ( servicePackStringDataSize > 1 )
         {
             errorCode = JsExSetPropertyString(
                     info ,
                     "servicePackString" ,
                     std::string( servicePackString.data() , servicePackStringDataSize - 1 ),
                     true
             );
             if ( JsNoError != errorCode )
             {
                  JsExThrowError("JsExSetPropertyInt fail 0x%08X" , errorCode );
                 break;
             }
         }
         else
         {
             errorCode = JsExSetPropertyString(
                     info ,
                     "servicePackString" ,
                     "",
                     true
             );
             if ( JsNoError != errorCode )
             {
                  JsExThrowError("JsExSetPropertyInt fail 0x%08X" , errorCode );
                 break;
             }
         }

         errorCode = JsExSetPropertyInt(info , "servicePack" , (int)servicePackNumber , true );
         if ( JsNoError != errorCode )
         {
              JsExThrowError("JsExSetPropertyInt fail 0x%08X" , errorCode );
             break;
         }

         if ( buildStringDataSize > 1 )
         {
             errorCode = JsExSetPropertyString(
                     info ,
                     "buildString" ,
                     std::string( buildString.data() , buildStringDataSize - 1 ),
                     true
             );
             if ( JsNoError != errorCode )
             {
                  JsExThrowError("JsExSetPropertyInt fail 0x%08X" , errorCode );
                 break;
             }
         }
         else
         {
             errorCode = JsExSetPropertyString(
                     info ,
                     "buildString" ,
                     "",
                     true
             );
             if ( JsNoError != errorCode )
             {
                  JsExThrowError("JsExSetPropertyInt fail 0x%08X" , errorCode );
                 break;
             }
         }

         result = info;

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

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::ReadBugCheck(

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

    JsValueRef  info = nullptr;

    ULONG       code = 0;

    ULONG64     arg1 = 0;

    ULONG64     arg2 = 0;

    ULONG64     arg3 = 0;

    ULONG64     arg4 = 0;


    do
    {

        hr = pthis->m_debugControl->ReadBugCheckData(
                &code ,
                &arg1 ,
                &arg2 ,
                &arg3,
                &arg4
        );
        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("ReadBugCheck fail 0x%08X" , hr );
            break ;
        }

        errorCode = JsCreateObject( &info );
        if ( JsNoError != errorCode )
         {
              JsExThrowError("JsCreateObject fail 0x%08X" , errorCode );
             break;
         }

        errorCode = JsExSetPropertyInt( info , "code" , (int)code , true );
        if ( JsNoError != errorCode )
         {
              JsExThrowError("JsExSetPropertyInt fail 0x%08X" , errorCode );
             break;
         }

        errorCode = JsExSetPropertyUint64( info , "arg1" , arg1 , true );
        if ( JsNoError != errorCode )
         {
              JsExThrowError("JsExSetPropertyUint64 fail 0x%08X" , errorCode );
             break;
         }

        errorCode = JsExSetPropertyUint64( info , "arg2" , arg2 , true );
        if ( JsNoError != errorCode )
         {
              JsExThrowError("JsExSetPropertyUint64 fail 0x%08X" , errorCode );
             break;
         }

        errorCode = JsExSetPropertyUint64( info , "arg3" , arg3 , true );
        if ( JsNoError != errorCode )
         {
              JsExThrowError("JsExSetPropertyUint64 fail 0x%08X" , errorCode );
             break;
         }

        errorCode = JsExSetPropertyUint64( info , "arg4" , arg4 , true );
        if ( JsNoError != errorCode )
         {
              JsExThrowError("JsExSetPropertyUint64 fail 0x%08X" , errorCode );
             break;
         }

        result = info;

    } while (false);

    return result;
}


 _Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::SetEffectiveProcessorType(

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

    uint32_t    arg1Type = 0;

    do
    {
        errorCode = JsExAssumeUint32( arguments[1] , &arg1Type );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume type fail 0x%08X" , errorCode);
            break;
        }

        hr = pthis->m_debugControl->SetEffectiveProcessorType(arg1Type);
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

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::SetExecutionStatus(

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

    uint32_t    arg1Status = 0;

    do
    {
        errorCode = JsExAssumeUint32( arguments[1] , &arg1Status );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume status fail 0x%08X" , errorCode);
            break;
        }

        hr = pthis->m_debugControl->SetExecutionStatus(arg1Status);
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


