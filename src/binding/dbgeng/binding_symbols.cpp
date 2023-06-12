/**
 * @file binding_symbols.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */
#include <precompile.h>

#include "binding_dbgeng.h"


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetFieldOffset(

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

    uint64_t  arg1Module = 0;

    uint32_t  arg2TypeId = 0;

    std::string arg3Field;

    ULONG       offset = 0;

    do
    {
        if (argumentCount < 4)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[1] , &arg1Module );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume module fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[2] , &arg2TypeId );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume typeId fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExAssumeString( arguments[3] , true , &arg3Field );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume field fail 0x%08X" , errorCode);
            break;
        }

        hr = pthis->m_debugSymbols->GetFieldOffset(
                arg1Module ,
                arg2TypeId,
                arg3Field.c_str(),
                &offset
        );

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetFieldOffset fail 0x%08X" , hr);
            break ;
        }

        JsIntToNumber( (int)offset , &result );

    } while (false);

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetModuleByIndex(

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

    ULONG64     imageBase = 0;

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

        hr = pthis->m_debugSymbols->GetModuleByIndex(
                arg1Index ,
                &imageBase
        );
        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetModuleByIndex fail 0x%08X" , hr);
            break ;
        }

        JsExCreateUint64( imageBase , &result);

    } while (false);

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetModuleByName(

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

    uint32_t  arg2StartIndex = 0;

    ULONG       moduleIndex = 0;

    ULONG64     imageBase = 0;

    JsValueRef  info = nullptr;

    do
    {
        if (argumentCount < 2)
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

        if ( argumentCount >=3 )
        {
            errorCode = JsExAssumeUint32( arguments[2] , &arg2StartIndex );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("assume index fail 0x%08X" , errorCode);
                break;
            }
        }

        hr = pthis->m_debugSymbols->GetModuleByModuleName(
                arg1Name.c_str() ,
                arg2StartIndex ,
                &moduleIndex,
                &imageBase
        );

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetModuleByModuleName fail 0x%08X" , hr);
            break ;
        }

        errorCode = JsCreateObject( &info );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsCreateObject fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExSetPropertyUint32(info , "index" , moduleIndex , true);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsExSetPropertyUint32 fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExSetPropertyUint64(info , "imageBase" , imageBase , true);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsExSetPropertyUint64 fail 0x%08X" , errorCode);
            break;
        }

        result = info;

    } while (false);

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetModuleByOffset(

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

    uint64_t    arg1Offset;

    uint32_t    arg2StartIndex = 0;

    ULONG       moduleIndex = 0;

    ULONG64     imageBase = 0;

    JsValueRef  info = nullptr;

    do
    {
        if (argumentCount < 2)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[1]  , &arg1Offset );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume offset fail 0x%08X" , errorCode);
            break;
        }

        if ( argumentCount >=3 )
        {
            errorCode = JsExAssumeUint32( arguments[2] , &arg2StartIndex );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("assume index fail 0x%08X" , errorCode);
                break;
            }
        }

        hr = pthis->m_debugSymbols->GetModuleByOffset(
                arg1Offset ,
                arg2StartIndex ,
                &moduleIndex,
                &imageBase
        );

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetModuleByOffset fail 0x%08X" , hr);
            break ;
        }

        errorCode = JsCreateObject( &info );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsCreateObject fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExSetPropertyUint32(info , "index" , moduleIndex , true);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsExSetPropertyUint32 fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExSetPropertyUint64(info , "imageBase" , imageBase , true);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsExSetPropertyUint64 fail 0x%08X" , errorCode);
            break;
        }

        result = info;

    } while (false);

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetModuleNames(

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

    uint32_t           arg1Index = 0;

    uint64_t           arg2Base = 0;

    std::vector<char> imageName;

    ULONG             imageNameBufferSize = 0;

    ULONG             imageNameDataSize = 0;


    std::vector<char> moduleName;

    ULONG             moduleNameBufferSize = 0;

    ULONG             moduleNameDataSize = 0;


    std::vector<char> loadedImageName;

    ULONG             loadedImageNameBufferSize = 0;

    ULONG             loadedImageNameDataSize = 0;

    JsValueRef        info = nullptr;


    do
    {
        if (argumentCount < 1)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[1]  , &arg1Index );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume index fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[2]  , &arg2Base );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume base fail 0x%08X" , errorCode);
            break;
        }

        pthis->m_debugSymbols->GetModuleNames(
            arg1Index ,
            arg2Base ,
            nullptr,
            0,
            &imageNameBufferSize,
            nullptr,
            0,
            &moduleNameBufferSize,
            nullptr,
            0,
            &loadedImageNameBufferSize
        );

        if ( 0 != imageNameBufferSize )
        {
            imageName.resize( imageNameBufferSize );
        }

        if ( 0 != moduleNameBufferSize )
        {
            moduleName.resize( moduleNameBufferSize );
        }

        if ( 0 != loadedImageNameBufferSize )
        {
            loadedImageName.resize( loadedImageNameBufferSize );
        }


        hr = pthis->m_debugSymbols->GetModuleNames(
            arg1Index ,
            arg2Base ,
            0 == imageNameBufferSize ? nullptr : imageName.data(),
            imageNameBufferSize,
            &imageNameDataSize,
            0 == moduleNameBufferSize ? nullptr : moduleName.data(),
            moduleNameBufferSize,
            &moduleNameDataSize,
            0 == loadedImageNameBufferSize ? nullptr : loadedImageName.data(),
            loadedImageNameBufferSize,
            &loadedImageNameDataSize
        );

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetModuleNames fail 0x%08X" , hr);
            break ;
        }

        errorCode = JsCreateObject( &info );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsCreateObject fail 0x%08X" , errorCode);
            break;
        }

        if ( imageNameDataSize > 1 )
        {
            errorCode = JsExSetPropertyString(
                    info ,
                    "imageName" ,
                    std::string( imageName.data() , imageNameDataSize - 1 ) ,
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
                    "imageName" ,
                    "",
                    true
            );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsExSetPropertyString fail 0x%08X" , errorCode);
                break;
            }
        }

        if ( moduleNameDataSize > 1)
        {
            errorCode = JsExSetPropertyString(
                    info ,
                    "moduleName" ,
                    std::string( moduleName.data() , moduleNameDataSize - 1 ) ,
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
                    "moduleName" ,
                    "" ,
                    true
            );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("JsExSetPropertyString fail 0x%08X" , errorCode);
                break;
            }
        }

        if ( loadedImageNameDataSize > 1 )
        {
            errorCode = JsExSetPropertyString(
                    info ,
                    "loadedImageName" ,
                    std::string( imageName.data() , loadedImageNameDataSize - 1 ) ,
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
                    "loadedImageName" ,
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


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetModuleParameters(

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

    DEBUG_MODULE_PARAMETERS params = {0};

    JsValueRef  info = nullptr;

    do
    {
        if (argumentCount < 2)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

         errorCode = JsExAssumeUint32( arguments[1]  , &arg1Index );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume index fail 0x%08X" , errorCode);
            break;
        }

        hr = pthis->m_debugSymbols->GetModuleParameters(
                1 ,
                nullptr,
                arg1Index,
                &params
        );

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetModuleParameters fail 0x%08X" , hr);
            break ;
        }

        errorCode = JsCreateObject( &info );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsCreateObject fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExSetPropertyUint64(info , "imageBase" , params.Base , true );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsExSetPropertyUint64 fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExSetPropertyUint32(info , "imageSize" , params.Size , true );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsExSetPropertyUint32 fail 0x%08X" , errorCode);
            break;
        }

         errorCode = JsExSetPropertyUint32(info , "timeDateStamp" , params.TimeDateStamp , true );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsExSetPropertyUint32 fail 0x%08X" , errorCode);
            break;
        }

         errorCode = JsExSetPropertyUint32(info , "checksum" , params.Checksum , true );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsExSetPropertyUint32 fail 0x%08X" , errorCode);
            break;
        }

         errorCode = JsExSetPropertyUint32(info , "flags" , params.Flags , true );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsExSetPropertyUint32 fail 0x%08X" , errorCode);
            break;
        }

         errorCode = JsExSetPropertyUint32(info , "symbolType" , params.SymbolType , true );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsExSetPropertyUint32 fail 0x%08X" , errorCode);
            break;
        }

        result = info;

    } while (false);

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetNameByOffset(

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

    std::vector<char> name;

    ULONG           nameBufferSize = 0;

    ULONG           nameDataSize = 0;

    ULONG64         displacement = 0;

    JsValueRef      info = nullptr;

    do
    {
        if (argumentCount < 2)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[1]  , &arg1Offset );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume offset fail 0x%08X" , errorCode);
            break;
        }


        pthis->m_debugSymbols->GetNameByOffset(
                arg1Offset ,
                nullptr,
                0,
                &nameBufferSize,
                &displacement
        );

        if ( 0 != nameBufferSize )
        {
            name.resize( nameBufferSize );
        }

         hr = pthis->m_debugSymbols->GetNameByOffset(
            arg1Offset ,
            0 == nameBufferSize ? nullptr : name.data(),
            nameBufferSize,
            &nameDataSize,
            &displacement
        );

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetNameByOffset fail 0x%08X" , hr);
            break ;
        }

         errorCode = JsCreateObject( &info );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsCreateObject fail 0x%08X" , errorCode);
            break;
        }

        if ( nameDataSize > 1 )
        {
            errorCode = JsExSetPropertyString(
                info ,
                "name" ,
                std::string( name.data() , nameDataSize - 1 ) ,
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
                "name" ,
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
                "displacement" ,
                displacement,
                true
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


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetNearNameByOffset(

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

    int32_t    arg2Delta = 0;

    std::vector<char> name;

    ULONG           nameBufferSize = 0;

    ULONG           nameDataSize = 0;

    ULONG64         displacement = 0;

    JsValueRef      info = nullptr;

    do
    {
        if (argumentCount < 2)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[1]  , &arg1Offset );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume offset fail 0x%08X" , errorCode);
            break;
        }

        if ( argumentCount >= 3 )
        {
            errorCode = JsExAssumeInt32( arguments[2]  , &arg2Delta );
            if ( JsNoError != errorCode )
            {
                JsExThrowError("assume delta fail 0x%08X" , errorCode);
                break;
            }
        }


        pthis->m_debugSymbols->GetNearNameByOffset(
                arg1Offset ,
                arg2Delta,
                nullptr,
                0,
                &nameBufferSize,
                &displacement
        );

        if ( 0 != nameBufferSize )
        {
            name.resize( nameBufferSize );
        }

         hr = pthis->m_debugSymbols->GetNearNameByOffset(
            arg1Offset ,
            arg2Delta,
            0 == nameBufferSize ? nullptr : name.data(),
            nameBufferSize,
            &nameDataSize,
            &displacement
        );

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetNearNameByOffset fail 0x%08X" , hr);
            break ;
        }

         errorCode = JsCreateObject( &info );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsCreateObject fail 0x%08X" , errorCode);
            break;
        }

        if ( nameDataSize > 1 )
        {
            errorCode = JsExSetPropertyString(
                info ,
                "name" ,
                std::string( name.data() , nameDataSize ) ,
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
                "name" ,
                "" ,
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
                "displacement" ,
                displacement,
                true
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


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetNumberModules(

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

    ULONG    loaded = 0;

    ULONG    unloaded = 0;

    JsValueRef      info = nullptr;

    do
    {
        if (argumentCount < 1)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        hr = pthis->m_debugSymbols->GetNumberModules(
            &loaded,
            &unloaded
        );

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetNumberModules fail 0x%08X" , hr);
            break ;
        }

        errorCode = JsCreateObject( &info );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsCreateObject fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExSetPropertyUint32(
                info ,
                "loaded" ,
                loaded,
                true
        );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsExSetPropertyUint32 fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExSetPropertyUint32(
                info ,
                "unloaded" ,
                unloaded,
                true
        );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsExSetPropertyUint32 fail 0x%08X" , errorCode);
            break;
        }

        result = info;

    } while (false);

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetOffsetByName(

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

    std::string     arg1Name;

    ULONG64         offset = 0;

    do
    {
        if (argumentCount < 2)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeString( arguments[1]  , true , &arg1Name );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume name fail 0x%08X" , errorCode);
            break;
        }


        hr = pthis->m_debugSymbols->GetOffsetByName(
            arg1Name.c_str(),
            &offset
        );

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetOffsetByName fail 0x%08X" , hr);
            break ;
        }

        JsExCreateUint64( offset , &result );

    } while (false);

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetOffsetTypeId(

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

    ULONG     typeId = 0;

    ULONG64   imageBase = 0;

    JsValueRef  info = nullptr;


    do
    {
        if (argumentCount < 2)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[1]   , &arg1Offset );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume offset fail 0x%08X" , errorCode);
            break;
        }

        hr = pthis->m_debugSymbols->GetOffsetTypeId(
                arg1Offset,
                &typeId,
                &imageBase
        );

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetOffsetTypeId fail 0x%08X" , hr);
            break ;
        }

        errorCode = JsCreateObject( &info );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsCreateObject fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExSetPropertyUint32(info , "typeId" , (int)typeId , true);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsExSetPropertyUint32 fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExSetPropertyUint64(info , "imageBase" , imageBase , true);
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsExSetPropertyUint64 fail 0x%08X" , errorCode);
            break;
        }

        result = info;

    } while (false);

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetSymbolModule(

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

    std::string     arg1Symbol;

    ULONG64         imageBase = 0;

    do
    {
        if (argumentCount < 2)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeString( arguments[1]  , true , &arg1Symbol );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume symbol fail 0x%08X" , errorCode);
            break;
        }

        hr = pthis->m_debugSymbols->GetSymbolModule(
                arg1Symbol.c_str() ,
                &imageBase
        );

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetSymbolModule fail 0x%08X" , hr);
            break ;
        }

        JsExCreateUint64( imageBase , &result);

    } while (false);

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetSymbolPath(

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

    std::vector<char> path;

    ULONG       pathBufferSize = 0;

    ULONG       pathDataSize = 0;

    do
    {

        pthis->m_debugSymbols->GetSymbolPath(nullptr , 0 , &pathBufferSize);

        if ( 0 == pathBufferSize )
        {
            break;
        }

        path.resize(pathBufferSize);


        hr = pthis->m_debugSymbols->GetSymbolPath(
                path.data() ,
                pathBufferSize ,
                &pathDataSize
        );

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetSymbolPath fail 0x%08X" , hr);
            break ;
        }

        JsExCreateString(
                path.data() ,
                pathDataSize,
                &result
        );

    } while (false);

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetSymbolTypeId(

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

    std::string     arg1Symbol;

    ULONG       typeId = 0;

    ULONG64     imageBase = 0;

    JsValueRef   info = nullptr;

    do
    {
        if (argumentCount < 2)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeString( arguments[1]  , true , &arg1Symbol );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume symbol fail 0x%08X" , errorCode);
            break;
        }

        hr = pthis->m_debugSymbols->GetSymbolTypeId(
                arg1Symbol.c_str() ,
                &typeId ,
                &imageBase
        );

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetSymbolTypeId fail 0x%08X" , hr);
            break ;
        }

        errorCode = JsCreateObject( &info );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsCreateObject fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExSetPropertyUint32(info , "typeId" , typeId , true );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsExSetPropertyUint32 fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExSetPropertyUint64(info , "imageBase" , imageBase , true );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("JsExSetPropertyUint64 fail 0x%08X" , errorCode);
            break;
        }

        result= info;

    } while (false);

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetTypeId(

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

    uint64_t     arg1ModuleBase = 0;

    std::string  arg2Name;

    ULONG        typeId = 0;


    do
    {
        if (argumentCount < 3)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[1]   , &arg1ModuleBase );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume module fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExAssumeString( arguments[2]  , true , &arg2Name );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume name fail 0x%08X" , errorCode);
            break;
        }

         hr = pthis->m_debugSymbols->GetTypeId(
            arg1ModuleBase,
            arg2Name.c_str(),
            &typeId
        );

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetTypeId fail 0x%08X" , hr);
            break ;
        }

        JsIntToNumber( (int)typeId , &result );

    } while (false);

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetTypeName(

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

    uint64_t   arg1ModuleBase = 0;

    uint32_t    arg2TypeId = 0;

    std::vector<char>   name;

    ULONG       nameBufferSize = 0;

    ULONG       nameDataSize = 0;

    do
    {
        if (argumentCount < 3)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[1]   , &arg1ModuleBase );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume module base fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[2]   , &arg2TypeId );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume type id fail 0x%08X" , errorCode);
            break;
        }

        pthis->m_debugSymbols->GetTypeName(
                arg1ModuleBase ,
                arg2TypeId,
                nullptr ,
                0,
                &nameBufferSize
        );

        if ( 0 != nameBufferSize )
        {
            name.resize(nameBufferSize);
        }

         hr = pthis->m_debugSymbols->GetTypeName(
                arg1ModuleBase ,
                arg2TypeId,
                0 == nameBufferSize ? nullptr : name.data() ,
                nameBufferSize,
                &nameDataSize
        );

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetTypeId fail 0x%08X" , hr);
            break ;
        }

        JsExCreateString(
                name.data() ,
                nameDataSize,
                &result
        );

    } while (false);

    return result;
}


_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::GetTypeSize(

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

    uint64_t   arg1ModuleBase = 0;

    uint32_t    arg2TypeId = 0;

    ULONG       typeSize = 0;


    do
    {
        if (argumentCount < 3)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeUint64( arguments[1]   , &arg1ModuleBase );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume module base fail 0x%08X" , errorCode);
            break;
        }

        errorCode = JsExAssumeUint32( arguments[2]   , &arg2TypeId );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume type id fail 0x%08X" , errorCode);
            break;
        }

        hr = pthis->m_debugSymbols->GetTypeSize(
                arg1ModuleBase ,
                arg2TypeId,
                &typeSize
        );

        if  ( !SUCCEEDED(hr) )
        {
            JsExThrowError("GetTypeSize fail 0x%08X" , hr);
            break ;
        }

        JsIntToNumber( (int)typeSize , &result );

    } while (false);

    return result;
}

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::Reload(

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

    std::string arg1ModuleName;

    do
    {
        if (argumentCount < 2)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeString( arguments[1]   ,  true , &arg1ModuleName );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume module name fail 0x%08X" , errorCode);
            break;
        }

        hr = pthis->m_debugSymbols->Reload(
                arg1ModuleName.c_str()
        );

        if  ( SUCCEEDED(hr) )
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

_Ret_maybenull_ JsValueRef CALLBACK BindingDbgEng::SetSymbolPath(

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

    std::string  arg1Path;

    do
    {
        if (argumentCount < 2)
        {
            JsExThrowError("invalid argument count %d" , argumentCount);
            break;
        }

        errorCode = JsExAssumeString( arguments[1]   ,  true , &arg1Path );
        if ( JsNoError != errorCode )
        {
            JsExThrowError("assume path fail 0x%08X" , errorCode);
            break;
        }

         hr = pthis->m_debugSymbols->SetSymbolPath(
                arg1Path.c_str()
        );

        if  ( SUCCEEDED(hr) )
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

