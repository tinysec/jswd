/**
 * @file binding_client.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#include <precompile.h>

#include "binding_dbgeng.h"

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetExitCode(

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

    ULONG  code = 0;

    do
    {
        hr = pthis->m_debugClient->GetExitCode(&code);
        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetExitCode fail 0x%08X" , hr);
            break;
        }

        JsIntToNumber( (int)code , &result );

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetIdentity(

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

    ULONG   bufferSize = 0;

    ULONG   dataSize = 0;

    std::vector<char> buffer;

    do
    {
        if (argumentCount < 1)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        hr = pthis->m_debugClient->GetIdentity(nullptr , 0 , &bufferSize );

        if ( 0 == bufferSize )
        {
            JsExThrowError("GetIdentity fail 0x%08X" , hr);
            break;
        }

        buffer.resize( bufferSize );

        hr = pthis->m_debugClient->GetIdentity( buffer.data() , bufferSize , &dataSize );
        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetIdentity fail 0x%08X" , hr);
            break;
        }

        JsExCreateString( buffer.data() , dataSize , &result );

    } while (false);

    return result;
}

// This method is available only for live user-mode debugging
_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetRunningProcessDescription(

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

    uint64_t  arg1Server = 0;

    uint32_t  arg2SystemId = 0;

    uint32_t  arg3Flags = 0;

    std::vector<char> exeName;

    ULONG             exeNameBufferSize = 0;

    ULONG             exeNameDataSize = 0;

    std::vector<char> description;

    ULONG             descriptionBufferSize = 0;

    ULONG             descriptionDataSize = 0;

    JsValueRef        info = nullptr;

    do
    {
        if (argumentCount < 4)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[1]  , &arg1Server );
        if (JsNoError != errorCode)
        {
            JsExThrowError("assume server fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[2]  , &arg2SystemId );
        if (JsNoError != errorCode)
        {
            JsExThrowError("assume systemId fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[3]  , &arg3Flags );
        if (JsNoError != errorCode)
        {
            JsExThrowError("assume flags fail 0x%08X" , errorCode);
            break;
        }

        pthis->m_debugClient->GetRunningProcessDescription(
                arg1Server ,
                arg2SystemId ,
                arg3Flags ,
                nullptr ,
                0,
                &exeNameBufferSize,
                nullptr ,
                0,
                &descriptionBufferSize
        );

        if ( 0 != exeNameBufferSize )
        {
            exeName.resize( exeNameBufferSize );
        }

        if ( 0 != descriptionBufferSize )
        {
            description.resize( descriptionBufferSize );
        }

        hr = pthis->m_debugClient->GetRunningProcessDescription(
                arg1Server ,
                arg2SystemId ,
                arg3Flags ,
                exeName.data() ,
                exeNameBufferSize,
                &exeNameDataSize,
                description.data() ,
                descriptionBufferSize,
                &descriptionDataSize
        );

        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetRunningProcessDescription fail 0x%08X" , hr);
            break;
        }

        errorCode = JsCreateObject( &info );
         if (JsNoError != errorCode)
        {
            JsExThrowError("JsCreateObject 0x%08X" , errorCode);
            break;
        }

         if ( exeNameDataSize > 1 )
         {
             errorCode = JsExSetPropertyString( info , "exeName" , std::string( exeName.data() , exeNameDataSize - 1) , true);
             if (JsNoError != errorCode)
            {
                JsExThrowError("JsExSetPropertyString 0x%08X" , errorCode);
                break;
            }
         }
         else
         {
              errorCode = JsExSetPropertyString( info , "exeName" , "" , true);
             if (JsNoError != errorCode)
            {
                JsExThrowError("JsExSetPropertyString 0x%08X" , errorCode);
                break;
            }
         }

         if ( descriptionDataSize > 1 )
         {
             errorCode = JsExSetPropertyString( info , "description" , std::string( description.data() , descriptionDataSize - 1) , true);
             if (JsNoError != errorCode)
            {
                JsExThrowError("JsExSetPropertyString 0x%08X" , errorCode);
                break;
            }
         }
         else
         {
              errorCode = JsExSetPropertyString( info , "description" , "", true);
             if (JsNoError != errorCode)
            {
                JsExThrowError("JsExSetPropertyString 0x%08X" , errorCode);
                break;
            }
         }
         result = info;

    } while (false);

    return result;
}

// This method is available only for live user-mode debugging.
_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetRunningProcessSystemIdByExecutableName(

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

    uint64_t    arg1Server = 0;

    std::string  arg2ExeName;

    uint32_t     arg3Flags = 0;

    ULONG        id = 0;

    do
    {
        if (argumentCount < 4)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[1]  , &arg1Server );
        if (JsNoError != errorCode)
        {
            JsExThrowError("assume server fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExAssumeString( arguments[2]  , true , &arg2ExeName );
        if (JsNoError != errorCode)
        {
            JsExThrowError("assume exeName fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[3]  , &arg3Flags );
        if (JsNoError != errorCode)
        {
            JsExThrowError("assume flags fail 0x%08X" , errorCode);
            break;
        }

        hr = pthis->m_debugClient->GetRunningProcessSystemIdByExecutableName(
                arg1Server ,
                arg2ExeName.c_str(),
                arg3Flags ,
                &id
        );
        if ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetRunningProcessSystemIdByExecutableName fail 0x%08X" , hr);
            break;
        }

        JsIntToNumber( (int)id , &result );

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::WriteDumpFile(

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

    std::string  arg1FileName;

    uint32_t     arg2Qualifier = 0;

    do
    {
        if (argumentCount < 3)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeString( arguments[1] , true , &arg1FileName );
        if (JsNoError != errorCode)
        {
            JsExThrowError("assume filename fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[2]  , &arg2Qualifier );
        if (JsNoError != errorCode)
        {
            JsExThrowError("assume qualifier fail 0x%08X" , errorCode);
            break;
        }

        hr = pthis->m_debugClient->WriteDumpFile(
                arg1FileName.c_str() ,
                arg2Qualifier
                );

         if ( !SUCCEEDED(hr) )
        {
            JsBoolToBoolean( false , &result);
            break;
        }

        JsBoolToBoolean( true , &result);

    } while (false);

    return result;
}
