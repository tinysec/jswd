/**
 * @file extension.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#include "precompile.h"

#include "version.h"

#include "extension.h"

#include "entrypoint.h"

////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef _WIN64
EXT_API_VERSION APIVersion = {MY_VERSION_MAJOR, MY_VERSION_MINOR, EXT_API_VERSION_NUMBER64, 0};
#else
EXT_API_VERSION APIVersion = {MY_VERSION_MAJOR, MY_VERSION_MINOR, EXT_API_VERSION_NUMBER32, 0};
#endif

EXTERN_C LPEXT_API_VERSION __stdcall ExtensionApiVersion(void)
{
    return &APIVersion;
}

EXTERN_C HRESULT __stdcall DebugExtensionInitialize(__out ULONG *pVersion, __out ULONG *pFlags)
{
    HRESULT result = E_FAIL;

    HRESULT hr = E_FAIL;

    Extension *extension = Extension::GetInstance();

    do
    {
        hr = extension->Initialize();
        if (!SUCCEEDED(hr))
        {
            result = hr;
            break;
        }

        result = S_OK;

    } while (false);

    return result;
}

EXTERN_C void __stdcall DebugExtensionUninitialize(void)
{
    Extension *extension = Extension::GetInstance();

    delete extension;
}

EXTERN_C HRESULT __stdcall KnownStructOutput(__in ULONG flags, __in ULONG64 address, __in PSTR structName,
                                             __out PSTR buffer, __inout PULONG pbufferSize)
{
    return S_OK;
}
