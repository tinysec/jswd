/**
 * @file captured_output_callbacks.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#include "captured_output_callbacks.h"

CapturedOutputCallbacks::CapturedOutputCallbacks()
{
    this->m_refs = 1;
}

CapturedOutputCallbacks::~CapturedOutputCallbacks()
{
}

std::string CapturedOutputCallbacks::GetCapturedText()
{
    return this->m_text;
}

HRESULT __stdcall CapturedOutputCallbacks::QueryInterface(_In_ REFIID InterfaceId, _Out_ PVOID *ppvObject)
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

ULONG __stdcall CapturedOutputCallbacks::AddRef()
{
    return InterlockedIncrement(&this->m_refs);
}

ULONG __stdcall CapturedOutputCallbacks::Release()
{
    ULONG refs = InterlockedDecrement(&this->m_refs);

    if (0 == refs)
    {
        delete this;
    }

    return refs;
}

HRESULT __stdcall CapturedOutputCallbacks::Output(_In_ ULONG Mask, _In_ PCSTR Text)
{
    do
    {
        if (nullptr == Text)
        {
            break;
        }

        this->m_text += std::string( Text);

    } while (false);

    return S_OK;
}