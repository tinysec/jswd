/**
 * @file binding_registers.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */
#include <precompile.h>

#include "binding_dbgeng.h"



_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetRegisterDescription(

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

    uint32_t arg1Index = 0;

    std::vector<char>  name;

    ULONG       nameBufferSize = 0;

    ULONG       nameDataSize = 0;

    DEBUG_REGISTER_DESCRIPTION description = {0};

    JsValueRef  info = nullptr;

    do
    {
        if (argumentCount < 2)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[1] , &arg1Index );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume index fail 0x%08X" , errorCode);
            break;
        }

        pthis->m_debugRegisters->GetDescription(
                arg1Index ,
                nullptr,
                0,
                &nameBufferSize,
                &description
        );

        if ( 0 != nameBufferSize )
        {
            name.resize( nameBufferSize );
        }

        hr = pthis->m_debugRegisters->GetDescription(
                arg1Index ,
                0 == nameBufferSize ? nullptr : name.data(),
                nameBufferSize,
                &nameDataSize,
                &description
        );

         if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetDescription fail 0x%08X" , hr);
            break ;
        }

         errorCode = JsCreateObject( &info );
         if ( JsNoError != errorCode )
        {
            JsExThrowError("assume index fail 0x%08X" , errorCode);
            break;
        }

         if ( nameDataSize > 1 )
         {
             errorCode = JsExSetPropertyString(
                     info ,
                     "name" ,
                     std::string( name.data() , nameDataSize - 1 ),
                     true
            );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsExSetPropertyInt fail 0x%08X" , errorCode);
                break;
            }
         }
         else
         {
             errorCode = JsExSetPropertyString(
                     info ,
                     "name" ,
                     "",
                     true
            );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsExSetPropertyInt fail 0x%08X" , errorCode);
                break;
            }

         }

        errorCode = JsExSetPropertyInt( info , "type" , (int)description.Type , true );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsExSetPropertyInt fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExSetPropertyInt( info , "flags" , (int)description.Flags , true );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsExSetPropertyInt fail 0x%08X" , errorCode);
            break;
        }

        if ( description.Flags & DEBUG_REGISTER_SUB_REGISTER )
        {
            errorCode = JsExSetPropertyInt( info , "subregMaster" , (int)description.SubregMaster , true );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsExSetPropertyInt fail 0x%08X" , errorCode);
                break;
            }

            errorCode = JsExSetPropertyInt( info , "subregLength" , (int)description.SubregLength , true );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsExSetPropertyInt fail 0x%08X" , errorCode);
                break;
            }

            errorCode = JsExSetPropertyUint64( info , "subregMask" , description.SubregMask , true );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsExSetPropertyInt fail 0x%08X" , errorCode);
                break;
            }

            errorCode = JsExSetPropertyInt( info , "subregShift" , (int)description.SubregShift , true );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsExSetPropertyInt fail 0x%08X" , errorCode);
                break;
            }
        }


        result = info;

    } while (false);

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetFrameOffset(

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

    ULONG64 offset = 0;

    do
    {

        hr = pthis->m_debugRegisters->GetFrameOffset( &offset );
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetIndexByName fail 0x%08X" , hr);
            break ;
        }

        JsExCreateUint64( offset , &result );

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetRegisterIndex(

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

    std::string  arg1Name;

    ULONG        index = 0;

    do
    {
        if (argumentCount < 1)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeString( arguments[1] , true , &arg1Name );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume name fail 0x%08X" , errorCode);
            break;
        }

        hr = pthis->m_debugRegisters->GetIndexByName( arg1Name.c_str() , &index );
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetIndexByName fail 0x%08X" , hr);
            break ;
        }

        JsIntToNumber( (int)index , &result );

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetInstructionOffset(

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
        hr = pthis->m_debugRegisters->GetInstructionOffset( &offset );
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetInstructionOffset fail 0x%08X" , hr);
            break ;
        }

        JsExCreateUint64( offset , &result );

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetNumberRegisters(

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

    ULONG   value = 0;

    do
    {
        hr = pthis->m_debugRegisters->GetNumberRegisters( &value );
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetNumberRegisters fail 0x%08X" , hr);
            break ;
        }

        JsIntToNumber( (int)value , &result );

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetStackOffset(

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
        hr = pthis->m_debugRegisters->GetStackOffset( &offset );
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetStackOffset fail 0x%08X" , hr);
            break ;
        }

        JsExCreateUint64( offset , &result );

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetRegisterValue(

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

    uint32_t     arg1Index = 0;

    DEBUG_VALUE  value = {0};

    JsValueRef    data = nullptr;

    JsValueRef    info = nullptr;


    do
    {
        if (argumentCount < 2)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[1] , &arg1Index );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume index fail 0x%08X" , errorCode);
            break;
        }

        hr = pthis->m_debugRegisters->GetValue( arg1Index , &value );
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetValue fail 0x%08X" , hr);
            break ;
        }

       if ( DEBUG_VALUE_INT8 == value.Type )
       {
           JsIntToNumber( (int)value.I8 , &data );
       }
       else if ( DEBUG_VALUE_INT16 == value.Type )
       {
           JsIntToNumber( (int)value.I16 , &data );
       }
       else if ( DEBUG_VALUE_INT32 == value.Type )
       {
           JsIntToNumber( (int)value.I32 , &data );
       }
       else if ( DEBUG_VALUE_INT64 == value.Type )
       {
           JsExCreateUint64( value.I64 , &data );
       }
       else if ( DEBUG_VALUE_FLOAT32 == value.Type )
       {
           JsDoubleToNumber( (double)value.F32 , &data );
       }
       else if ( DEBUG_VALUE_FLOAT64 == value.Type )
       {
           JsExCreateUint8Array( value.RawBytes , 8 , &data);
       }
       else if ( DEBUG_VALUE_FLOAT80 == value.Type )
       {
           JsExCreateUint8Array( value.F80Bytes , 10 , &data);
       }
       else if ( DEBUG_VALUE_FLOAT128 == value.Type )
       {
           JsExCreateUint8Array( value.F128Bytes , 16 , &data);
       }
       else if ( DEBUG_VALUE_VECTOR64 == value.Type )
       {
           JsExCreateUint8Array( value.VI8 , 8, &data);
       }
       else if ( DEBUG_VALUE_VECTOR128 == value.Type )
       {
           JsExCreateUint8Array( value.VI8 , 16, &data);
       }
       else
       {
           JsExCreateUint8Array( value.RawBytes , ARRAYSIZE(value.RawBytes) , &data);
       }

       errorCode = JsCreateObject( &info );
       if ( JsNoError != errorCode )
        {
            JsExThrowError("JsCreateObject fail 0x%08X" , errorCode);
            break;
        }

       JsExSetProperty(info , "value" , data , true );

       JsExSetPropertyUint32(info , "type" , value.Type , true );

       result = info;

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::SetRegisterValue(

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

    uint32_t  arg1Index = 0;

    DEBUG_VALUE  value = {0};

    JsValueType  valueType = JsUndefined;

    uint32_t     bytes = 0;

    do
    {
        if (argumentCount < 4)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[1] , &arg1Index );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume index fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[2] , (uint32_t*)&(value.Type) );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume type fail 0x%08X" , errorCode);
            break;
        }

        if ( DEBUG_VALUE_INT8 == value.Type )
        {
            bytes = 1;
        }
        else if ( DEBUG_VALUE_INT16 == value.Type )
        {
            bytes = 2;
        }
        else if ( DEBUG_VALUE_INT32 == value.Type )
        {
            bytes = 4;
        }
        else if ( DEBUG_VALUE_INT64 == value.Type )
        {
            bytes = 8;
        }
        else if ( DEBUG_VALUE_FLOAT32 == value.Type )
        {
            bytes = 4;
        }
        else if ( DEBUG_VALUE_FLOAT64 == value.Type )
        {
            bytes = 8;
        }
        else if ( DEBUG_VALUE_FLOAT80 == value.Type )
        {
            bytes = 10;
        }
        else if ( DEBUG_VALUE_FLOAT128 == value.Type )
        {
            bytes = 16;
        }
        else if ( DEBUG_VALUE_VECTOR64 == value.Type )
        {
            bytes = 8;
        }
        else if ( DEBUG_VALUE_VECTOR128 == value.Type )
        {
            bytes = 16;
        }
        else
        {
            JsExThrowError("not supported type fail %d" , value.Type);
            break;
        }

        errorCode = JsGetValueType( arguments[3] , &valueType);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsGetValueType fail 0x%08X" , errorCode);
            break;
        }

        if ( JsArray == valueType )
        {
            errorCode = JsExAssumeUint8Array(
                arguments[3] ,
                (uint8_t *)&(value.RawBytes),
                bytes
            );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsExAssumeUint8Array fail 0x%08X" , errorCode);
                break;
            }
        }
        else if ( JsNumber == valueType )
        {
            errorCode = JsExAssumeUint32( arguments[3] , (uint32_t *)&(value.I32) );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsExAssumeUint32 fail 0x%08X" , errorCode);
                break;
            }
        }
        else if ( JsString == valueType )
        {
            errorCode = JsExAssumeUint64( arguments[3] , (uint64_t *)&(value.I64) );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsExAssumeUint64 fail 0x%08X" , errorCode);
                break;
            }
        }
        else
        {
            JsExThrowError("not supported value type 0x%08X" , valueType);
            break;
        }

        hr = pthis->m_debugRegisters->SetValue( arg1Index , &value );
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("SetValue fail 0x%08X" , hr);
            break ;
        }

    } while (false);

    return result;
}