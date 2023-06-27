/**
 * @file bingd_data_spaces.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */
#include <precompile.h>

#include "binding_dbgeng.h"



_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::ReadBus(

    _In_ JsValueRef callee,

    _In_ bool isConstructCall,

    _In_ JsValueRef *arguments,

    _In_ unsigned short argumentCount,

    _In_opt_ void *callbackState
)
{
    BindingDbgEng *pthis = (BindingDbgEng *)(callbackState);

    JsValueRef  result = nullptr;

    JsErrorCode errorCode = JsErrorFatal;

    HRESULT     hr = E_FAIL;

    uint32_t     arg1BusDataType = 0;

    uint32_t     arg2BusNumber = 0;

    uint32_t     arg3SlotNumber = 0;


    uint64_t     arg4Offset = 0;

    UCHAR*       arg5Buffer = nullptr;

    uint32_t     bufferLength = 0;

    ULONG       bytesRead = 0;

    do
    {
        if (argumentCount < 6)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[1]  , &arg1BusDataType);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume busDataType  fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsExAssumeUint32( arguments[2]  , &arg2BusNumber);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume BusNumber  fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsExAssumeUint32( arguments[3]  , &arg3SlotNumber);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume SlotNumber  fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsExAssumeUint64( arguments[4]  , &arg4Offset);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume offset  fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsGetArrayBufferStorage(arguments[5] , &arg5Buffer , &bufferLength);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsGetArrayBufferStorage fail 0x%08X" , errorCode );
            break;
        }

        if ( 0 == bufferLength )
        {
            JsExThrowError("empty buffer"  );
            break;
        }

        hr = pthis->m_debugDataSpaces->ReadBusData(
                arg1BusDataType ,
                arg2BusNumber,
                arg3SlotNumber,
                arg4Offset ,
                arg5Buffer ,
                bufferLength ,
                &bytesRead
        );

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("ReadBus fail 0x%08X" , hr);
            break ;
        }

        JsIntToNumber((int)bytesRead , &result );

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::ReadControl(

    _In_ JsValueRef callee,

    _In_ bool isConstructCall,

    _In_ JsValueRef *arguments,

    _In_ unsigned short argumentCount,

    _In_opt_ void *callbackState
)
{
    BindingDbgEng *pthis = (BindingDbgEng *)(callbackState);

    JsValueRef  result = nullptr;

    JsErrorCode errorCode = JsErrorFatal;

    HRESULT     hr = E_FAIL;

    uint32_t    arg1Processor = 0;

    uint64_t     arg2Offset = 0;

    UCHAR*       arg3Buffer = nullptr;

    uint32_t     bufferLength = 0;

    ULONG       bytesRead = 0;

    do
    {
        if (argumentCount < 4)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[1]  , &arg1Processor);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume processor 0x%08X" , errorCode );
            break;
        }

        errorCode = JsExAssumeUint64( arguments[2]  , &arg2Offset);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume offset 0x%08X" , errorCode );
            break;
        }

        errorCode = JsGetArrayBufferStorage(arguments[3] , &arg3Buffer , &bufferLength);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsGetArrayBufferStorage fail 0x%08X" , errorCode );
            break;
        }

        if ( 0 == bufferLength )
        {
            JsExThrowError("empty buffer"  );
            break;
        }

        hr = pthis->m_debugDataSpaces->ReadControl(
                arg1Processor,
                arg2Offset ,
                arg3Buffer ,
                bufferLength ,
                &bytesRead
                );
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("ReadControl fail 0x%08X" , hr);
            break ;
        }

        JsIntToNumber( (int)bytesRead , &result );

    } while (false);

    return result;
}


 _Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::ReadDebugger(

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
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint32(  arguments[1]  , &argIndex );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume index fail" );
            break ;
        }

        errorCode = JsGetArrayBufferStorage( arguments[2] , &argBuffer , &bufferSize);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsGetArrayBufferStorage fail" );
            break ;
        }

        hr = pthis->m_debugDataSpaces->ReadDebuggerData(argIndex , argBuffer , bufferSize , &dataSize );
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("ReadDebugger fail 0x%08X" , hr);
            break ;
        }

        JsIntToNumber((int)dataSize , &result);

    } while (false);

    return result;
}



_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::ReadIo(

    _In_ JsValueRef callee,

    _In_ bool isConstructCall,

    _In_ JsValueRef *arguments,

    _In_ unsigned short argumentCount,

    _In_opt_ void *callbackState
)
{
    BindingDbgEng *pthis = (BindingDbgEng *)(callbackState);

    JsValueRef  result = nullptr;

    JsErrorCode errorCode = JsErrorFatal;

    HRESULT     hr = E_FAIL;

    uint32_t     arg1InterfaceType = 0;

    uint32_t     arg2BusNumber = 0;

    uint32_t     arg3AddressSpace = 0;


    uint64_t     arg4Offset = 0;

    UCHAR*       arg5Buffer = nullptr;

    uint32_t     bufferLength = 0;

    ULONG       bytesRead = 0;

    do
    {
        if (argumentCount < 6)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[1]  , &arg1InterfaceType);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume busDataType  fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsExAssumeUint32( arguments[2]  , &arg2BusNumber);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume BusNumber  fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsExAssumeUint32( arguments[3]  , &arg3AddressSpace);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume SlotNumber  fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsExAssumeUint64( arguments[4]  , &arg4Offset);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume offset  fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsGetArrayBufferStorage(arguments[5] , &arg5Buffer , &bufferLength);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsGetArrayBufferStorage fail 0x%08X" , errorCode );
            break;
        }

        if ( 0 == bufferLength )
        {
            JsExThrowError("empty buffer"  );
            break;
        }

        hr = pthis->m_debugDataSpaces->ReadIo(
                arg1InterfaceType ,
                arg2BusNumber,
                arg3AddressSpace,
                arg4Offset ,
                arg5Buffer ,
                bufferLength ,
                &bytesRead
        );

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("ReadIo fail 0x%08X" , hr);
            break ;
        }

        JsIntToNumber((int)bytesRead , &result );

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::ReadMsr(

    _In_ JsValueRef callee,

    _In_ bool isConstructCall,

    _In_ JsValueRef *arguments,

    _In_ unsigned short argumentCount,

    _In_opt_ void *callbackState
)
{
    BindingDbgEng *pthis = (BindingDbgEng *)(callbackState);

    JsValueRef  result = nullptr;

    JsErrorCode errorCode = JsErrorFatal;

    HRESULT     hr = E_FAIL;

    uint32_t     arg1Address = 0;

    ULONG64     value = 0;

    do
    {
        if (argumentCount < 2)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[1]  , &arg1Address );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume address fail" );
            break ;
        }

        hr = pthis->m_debugDataSpaces->ReadMsr(arg1Address , &value);
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("ReadMsr fail 0x%08X" , hr);
            break ;
        }

        // return as hex string
        JsExCreateUint64( value , &result);

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::ReadPhysical(

    _In_ JsValueRef callee,

    _In_ bool isConstructCall,

    _In_ JsValueRef *arguments,

    _In_ unsigned short argumentCount,

    _In_opt_ void *callbackState
)
{
    BindingDbgEng *pthis = (BindingDbgEng *)(callbackState);

    JsValueRef  result = nullptr;

    JsErrorCode errorCode = JsErrorFatal;

    HRESULT     hr = E_FAIL;

    uint64_t     arg1Offset = 0;

    UCHAR*       arg2Buffer = nullptr;

    uint32_t     bufferLength = 0;

    ULONG       bytesRead = 0;

    do
    {
        if (argumentCount < 3)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[1]  , &arg1Offset);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume offset fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsGetArrayBufferStorage( arguments[2] , &arg2Buffer , &bufferLength);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsGetArrayBufferStorage fail 0x%08X" , errorCode );
            break;
        }

        if ( 0 == bufferLength )
        {
            JsExThrowError("empty buffer"  );
            break;
        }

        hr = pthis->m_debugDataSpaces->ReadPhysical(arg1Offset , arg2Buffer , bufferLength , &bytesRead );
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("ReadPhysical fail 0x%08X" , hr);
            break ;
        }

        JsIntToNumber( (int)bytesRead , &result );

    } while (false);

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::ReadProcessor(

    _In_ JsValueRef callee,

    _In_ bool isConstructCall,

    _In_ JsValueRef *arguments,

    _In_ unsigned short argumentCount,

    _In_opt_ void *callbackState
)
{
    BindingDbgEng *pthis = (BindingDbgEng *)(callbackState);

    JsValueRef  result = nullptr;

    JsErrorCode errorCode = JsErrorFatal;

    HRESULT     hr = E_FAIL;

    uint32_t     arg1Processor = 0;

    uint32_t     arg2Index = 0;

    UCHAR*       arg3Buffer = nullptr;

    uint32_t     bufferLength = 0;

    ULONG       bytesRead = 0;

    do
    {
        if (argumentCount < 4)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[1]  , &arg1Processor);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume processor fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsExAssumeUint32( arguments[2]  , &arg2Index);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume index fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsGetArrayBufferStorage(arguments[3] , &arg3Buffer , &bufferLength);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsGetArrayBufferStorage fail 0x%08X" , errorCode );
            break;
        }

        if ( 0 == bufferLength )
        {
            JsExThrowError("empty buffer"  );
            break;
        }

        hr = pthis->m_debugDataSpaces->ReadProcessorSystemData(arg1Processor , arg2Index , arg3Buffer , bufferLength , &bytesRead );
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("ReadPhysical fail 0x%08X" , hr);
            break ;
        }

        JsIntToNumber( (int)bytesRead , &result );

    } while (false);

    return result;
}



_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::ReadVirtual(

    _In_ JsValueRef callee,

    _In_ bool isConstructCall,

    _In_ JsValueRef *arguments,

    _In_ unsigned short argumentCount,

    _In_opt_ void *callbackState
)
{
    BindingDbgEng *pthis = (BindingDbgEng *)(callbackState);

    JsValueRef  result = nullptr;

    JsErrorCode errorCode = JsErrorFatal;

    HRESULT     hr = E_FAIL;

    uint64_t     arg1Offset = 0;

    UCHAR*       arg2Buffer = nullptr;

    uint32_t     bufferLength = 0;

    ULONG       bytesRead = 0;

    bool        arg3Uncached = false;

    do
    {
        if (argumentCount < 3)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[1]  , &arg1Offset);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume offset fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsGetArrayBufferStorage( arguments[2] , &arg2Buffer , &bufferLength);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsGetArrayBufferStorage fail 0x%08X" , errorCode );
            break;
        }

        if ( 0 == bufferLength )
        {
            JsExThrowError("empty buffer"  );
            break;
        }

        if ( argumentCount >= 4)
        {
            errorCode = JsExAssumeBool( arguments[3] , true , &arg3Uncached );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("argument 3 must be bool" );
                break;
            }
        }

        if ( arg3Uncached )
        {
            hr = pthis->m_debugDataSpaces->ReadVirtualUncached(arg1Offset , arg2Buffer , bufferLength , &bytesRead );
        }
        else
        {
            hr = pthis->m_debugDataSpaces->ReadVirtual(arg1Offset , arg2Buffer , bufferLength , &bytesRead );
        }

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("ReadVirtual 0x%X fail 0x%08X" , arg1Offset ,  hr);
            break ;
        }

        JsIntToNumber( (int)bytesRead , &result );

    } while (false);

    return result;
}



_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::SearchVirtual(

    _In_ JsValueRef callee,

    _In_ bool isConstructCall,

    _In_ JsValueRef *arguments,

    _In_ unsigned short argumentCount,

    _In_opt_ void *callbackState
)
{
    BindingDbgEng *pthis = (BindingDbgEng *)(callbackState);

    JsValueRef  result = nullptr;

    JsErrorCode errorCode = JsErrorFatal;

    HRESULT     hr = E_FAIL;

    uint64_t     arg1Offset = 0;

    uint64_t     arg2Length = 0;

    UCHAR*       arg3Pattern = nullptr;

    uint32_t     patternSize = 0;

    uint32_t     arg4PatternGranularity = 0;

    ULONG64       matchOffset = 0;



    do
    {
        if (argumentCount < 4)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[1]  , &arg1Offset);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume offset fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsExAssumeUint64( arguments[2]  , &arg2Length);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume length fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsGetArrayBufferStorage(arguments[3] , &arg3Pattern , &patternSize);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsGetArrayBufferStorage fail 0x%08X" , errorCode );
            break;
        }

        if (0 == patternSize )
        {
            JsExThrowError("empty buffer"  );
            break;
        }


        errorCode = JsExAssumeUint32( arguments[4]  , &arg4PatternGranularity);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("get arg4PatternGranularity  fail 0x%08X" , errorCode );
            break;
        }

        hr = pthis->m_debugDataSpaces->SearchVirtual(
                arg1Offset ,
                arg2Length,
                arg3Pattern ,
                patternSize ,
                arg4PatternGranularity ,
                &matchOffset
        );
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("SearchVirtual fail 0x%08X" , hr);
            break ;
        }

        JsExCreateUint64( matchOffset , &result );

    } while (false);

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::WriteBus(

    _In_ JsValueRef callee,

    _In_ bool isConstructCall,

    _In_ JsValueRef *arguments,

    _In_ unsigned short argumentCount,

    _In_opt_ void *callbackState
)
{
    BindingDbgEng *pthis = (BindingDbgEng *)(callbackState);

    JsValueRef  result = nullptr;

    JsErrorCode errorCode = JsErrorFatal;

    HRESULT     hr = E_FAIL;

    uint32_t     arg1BusDataType = 0;

    uint32_t     arg2BusNumber = 0;

    uint32_t     arg3SlotNumber = 0;


    uint64_t     arg4Offset = 0;

    UCHAR*       arg5Buffer = nullptr;

    uint32_t     bufferLength = 0;

    ULONG       bytesWritten = 0;

    do
    {
        if (argumentCount < 4)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[1]  , &arg1BusDataType);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume busDataType  fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsExAssumeUint32( arguments[2]  , &arg2BusNumber);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume BusNumber  fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsExAssumeUint32( arguments[3]  , &arg3SlotNumber);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume SlotNumber  fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsExAssumeUint64( arguments[4]  , &arg4Offset);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume offset  fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsGetArrayBufferStorage(arguments[5] , &arg5Buffer , &bufferLength);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsGetArrayBufferStorage fail 0x%08X" , errorCode );
            break;
        }

        if ( 0 == bufferLength )
        {
            JsExThrowError("empty buffer"  );
            break;
        }

        hr = pthis->m_debugDataSpaces->WriteBusData(
                arg1BusDataType ,
                arg2BusNumber,
                arg3SlotNumber,
                arg4Offset ,
                arg5Buffer ,
                bufferLength ,
                &bytesWritten
                );

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("WriteBus fail 0x%08X" , hr);
            break ;
        }

        JsIntToNumber((int)bytesWritten , &result );

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::WriteControl(

    _In_ JsValueRef callee,

    _In_ bool isConstructCall,

    _In_ JsValueRef *arguments,

    _In_ unsigned short argumentCount,

    _In_opt_ void *callbackState
)
{
    BindingDbgEng *pthis = (BindingDbgEng *)(callbackState);

    JsValueRef  result = nullptr;

    JsErrorCode errorCode = JsErrorFatal;

    HRESULT     hr = E_FAIL;

    uint32_t     arg1Processor = 0;

    uint64_t     arg2Offset = 0;

    UCHAR*       arg2Buffer = nullptr;

    uint32_t     bufferLength = 0;

    ULONG       bytesWritten = 0;

    do
    {
        if (argumentCount < 4)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[1]  , &arg1Processor);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume processor  fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsExAssumeUint64( arguments[2]  , &arg2Offset);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume offset  fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsGetArrayBufferStorage( arguments[3] , &arg2Buffer , &bufferLength);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsGetArrayBufferStorage fail 0x%08X" , errorCode );
            break;
        }

        if ( 0 == bufferLength )
        {
            JsExThrowError("empty buffer"  );
            break;
        }

        hr = pthis->m_debugDataSpaces->WriteControl(arg1Processor , arg2Offset , arg2Buffer , bufferLength , &bytesWritten );

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("WriteControl fail 0x%08X" , hr);
            break ;
        }

        JsIntToNumber((int)bytesWritten , &result );

    } while (false);

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::WriteIo(

    _In_ JsValueRef callee,

    _In_ bool isConstructCall,

    _In_ JsValueRef *arguments,

    _In_ unsigned short argumentCount,

    _In_opt_ void *callbackState
)
{
    BindingDbgEng *pthis = (BindingDbgEng *)(callbackState);

    JsValueRef  result = nullptr;

    JsErrorCode errorCode = JsErrorFatal;

    HRESULT     hr = E_FAIL;

    uint32_t     arg1InterfaceType = 0;

    uint32_t     arg2BusNumber = 0;

    uint32_t     arg3AddressSpace = 0;


    uint64_t     arg4Offset = 0;

    UCHAR*       arg5Buffer = nullptr;

    uint32_t     bufferLength = 0;

    ULONG       bytesWritten = 0;

    do
    {
        if (argumentCount < 6)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[1]  , &arg1InterfaceType);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume busDataType  fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsExAssumeUint32( arguments[2]  , &arg2BusNumber);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume BusNumber  fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsExAssumeUint32( arguments[3]  , &arg3AddressSpace);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume SlotNumber  fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsExAssumeUint64( arguments[4]  , &arg4Offset);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume offset  fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsGetArrayBufferStorage(arguments[5] , &arg5Buffer , &bufferLength);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsGetArrayBufferStorage fail 0x%08X" , errorCode );
            break;
        }

        if ( 0 == bufferLength )
        {
            JsExThrowError("empty buffer"  );
            break;
        }

        hr = pthis->m_debugDataSpaces->WriteIo(
                arg1InterfaceType ,
                arg2BusNumber,
                arg3AddressSpace,
                arg4Offset ,
                arg5Buffer ,
                bufferLength ,
                &bytesWritten
        );

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("WriteIo fail 0x%08X" , hr);
            break ;
        }

        JsIntToNumber((int)bytesWritten , &result );

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::WriteMsr(

    _In_ JsValueRef callee,

    _In_ bool isConstructCall,

    _In_ JsValueRef *arguments,

    _In_ unsigned short argumentCount,

    _In_opt_ void *callbackState
 )
 {
    BindingDbgEng *pthis = (BindingDbgEng *)(callbackState);

    JsValueRef  result = nullptr;

    JsErrorCode errorCode = JsErrorFatal;

    HRESULT     hr = E_FAIL;

    uint32_t     arg1Offset = 0;

    uint64_t     arg2Value = 0;

    do
    {
        if (argumentCount < 2)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[1]  , &arg1Offset );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume offset fail 0x%08X" , errorCode );
            break ;
        }

        errorCode = JsExAssumeUint64( arguments[2]  , &arg2Value );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume msr value fail" );
            break ;
        }

        hr = pthis->m_debugDataSpaces->WriteMsr(arg1Offset , arg2Value);
        if  ( !SUCCEEDED(hr) )
        {
            JsBoolToBoolean(false , &result);
            break ;
        }

         JsBoolToBoolean(true , &result);

    } while (false);

    return result;
}


 _Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::WritePhysical(

    _In_ JsValueRef callee,

    _In_ bool isConstructCall,

    _In_ JsValueRef *arguments,

    _In_ unsigned short argumentCount,

    _In_opt_ void *callbackState
 )
{
    BindingDbgEng *pthis = (BindingDbgEng *)(callbackState);

    JsValueRef  result = nullptr;

    JsErrorCode errorCode = JsErrorFatal;

    HRESULT     hr = E_FAIL;

    uint64_t     arg1Offset = 0;

    UCHAR*       arg2Buffer = nullptr;

    uint32_t     bufferLength = 0;

    ULONG       bytesWritten = 0;

    do
    {
        if (argumentCount < 3)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[1]  , &arg1Offset);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume offset  fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsGetArrayBufferStorage( arguments[2] , &arg2Buffer , &bufferLength);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsGetArrayBufferStorage fail 0x%08X" , errorCode );
            break;
        }

        if ( 0 == bufferLength )
        {
            JsExThrowError("empty buffer"  );
            break;
        }

        hr = pthis->m_debugDataSpaces->WritePhysical(arg1Offset , arg2Buffer , bufferLength , &bytesWritten );

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("WritePhysical fail 0x%08X" , hr);
            break ;
        }

        JsIntToNumber((int)bytesWritten , &result );

    } while (false);

    return result;
}

 _Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::WriteVirtual(

    _In_ JsValueRef callee,

    _In_ bool isConstructCall,

    _In_ JsValueRef *arguments,

    _In_ unsigned short argumentCount,

    _In_opt_ void *callbackState
 )
{
     BindingDbgEng *pthis = (BindingDbgEng *)(callbackState);

    JsValueRef  result = nullptr;

    JsErrorCode errorCode = JsErrorFatal;

    HRESULT     hr = E_FAIL;

    uint64_t     arg1Offset = 0;

    UCHAR*       arg2Buffer = nullptr;

    uint32_t     bufferLength = 0;

    ULONG       bytesWritten = 0;

    bool        arg3Uncached = false;

    do
    {
        if (argumentCount < 3)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[1]  , &arg1Offset);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("get address  fail 0x%08X" , errorCode );
            break;
        }

        errorCode = JsGetArrayBufferStorage( arguments[2] , &arg2Buffer , &bufferLength);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsGetArrayBufferStorage fail 0x%08X" , errorCode );
            break;
        }

        if ( 0 == bufferLength )
        {
            JsExThrowError("empty buffer"  );
            break;
        }

        if ( argumentCount >= 4)
        {
            errorCode = JsExAssumeBool( arguments[3] , true , &arg3Uncached );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("argument 3 must be bool" );
                break;
            }
        }

        if ( arg3Uncached )
        {
            hr = pthis->m_debugDataSpaces->WriteVirtualUncached(arg1Offset , arg2Buffer , bufferLength , &bytesWritten );
        }
        else
        {
            hr = pthis->m_debugDataSpaces->WriteVirtual(arg1Offset , arg2Buffer , bufferLength , &bytesWritten );
        }

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("WriteVirtual fail 0x%08X" , hr);
            break ;
        }

        JsIntToNumber((int)bytesWritten , &result );

    } while (false);

    return result;
}

