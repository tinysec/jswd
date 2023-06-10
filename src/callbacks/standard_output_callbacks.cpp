/**
 * @file standard_output_callbacks.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#include "standard_output_callbacks.h"

StandardOutputCallbacks::StandardOutputCallbacks()
{
    this->m_refs = 1;
}

StandardOutputCallbacks::~StandardOutputCallbacks()
{
}

HRESULT __stdcall StandardOutputCallbacks::QueryInterface(_In_ REFIID InterfaceId, _Out_ PVOID *ppvObject)
{
    HRESULT hr = E_FAIL;

    HRESULT result = E_FAIL;

    do
    {
        if (nullptr == ppvObject)
        {
            result = E_INVALIDARG;
            break;
        }

        if (IsEqualIID(InterfaceId, IID_IUnknown))
        {
            this->AddRef();
            *ppvObject = this;
        }
        else if (IsEqualIID(InterfaceId, IID_IDebugOutputCallbacks))
        {
            this->AddRef();
            *ppvObject = this;
        }
        else
        {
            result = E_NOTIMPL;
            break;
        }

        result = S_OK;

    } while (false);

    return result;
}

ULONG __stdcall StandardOutputCallbacks::AddRef()
{
    return InterlockedIncrement(&this->m_refs);
}

ULONG __stdcall StandardOutputCallbacks::Release()
{
    ULONG refs = InterlockedDecrement(&this->m_refs);

    if (0 == refs)
    {
        delete this;
    }

    return refs;
}

HRESULT __stdcall StandardOutputCallbacks::Output(_In_ ULONG Mask, _In_ PCSTR Text)
{
    do
    {
        if (nullptr == Text)
        {
            break;
        }

        printf("%s", Text);

    } while (false);

    return S_OK;
}