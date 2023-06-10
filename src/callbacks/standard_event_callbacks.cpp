/**
 * @file standard_event_callbacks.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#include "standard_event_callbacks.h"

StandardEventCallbacks::StandardEventCallbacks()
{
    this->m_refs = 1;
}

StandardEventCallbacks::~StandardEventCallbacks()
{
}

HRESULT __stdcall StandardEventCallbacks::QueryInterface(_In_ REFIID InterfaceId, _Out_ PVOID *ppvObject)
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
        else if (IsEqualIID(InterfaceId, IID_IDebugEventCallbacks))
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

ULONG __stdcall StandardEventCallbacks::AddRef()
{
    return InterlockedIncrement(&this->m_refs);
}

ULONG __stdcall StandardEventCallbacks::Release()
{
    ULONG refs = InterlockedDecrement(&this->m_refs);

    if (0 == refs)
    {
        delete this;
    }

    return refs;
}

// The engine calls GetInterestMask once when
// the event callbacks are set for a client.
HRESULT __stdcall StandardEventCallbacks::GetInterestMask(_Out_ PULONG Mask)
{
    HRESULT result = E_FAIL;

    HRESULT hr = E_FAIL;

    ULONG interestMask = 0;

    do
    {
        interestMask |= DEBUG_EVENT_BREAKPOINT;

        interestMask |= DEBUG_EVENT_EXCEPTION;

        interestMask |= DEBUG_EVENT_CREATE_THREAD;

        interestMask |= DEBUG_EVENT_EXIT_THREAD;

        interestMask |= DEBUG_EVENT_CREATE_PROCESS;

        interestMask |= DEBUG_EVENT_EXIT_PROCESS;

        interestMask |= DEBUG_EVENT_LOAD_MODULE;

        interestMask |= DEBUG_EVENT_UNLOAD_MODULE;

        interestMask |= DEBUG_EVENT_SYSTEM_ERROR;

        interestMask |= DEBUG_EVENT_SESSION_STATUS;

        interestMask |= DEBUG_EVENT_CHANGE_DEBUGGEE_STATE;

        interestMask |= DEBUG_EVENT_CHANGE_ENGINE_STATE;

        interestMask |= DEBUG_EVENT_CHANGE_SYMBOL_STATE;

        interestMask |= DEBUG_EVENT_SERVICE_EXCEPTION;

        result = S_OK;

    } while (false);

    return result;
}

// A breakpoint event is generated when
// a breakpoint exception is received and
// it can be mapped to an existing breakpoint.
// The callback method is given a reference
// to the breakpoint and should release it when
// it is done with it.
HRESULT __stdcall StandardEventCallbacks::Breakpoint(_In_ PDEBUG_BREAKPOINT Bp)
{
    HRESULT result = E_FAIL;

    HRESULT hr = E_FAIL;

    do
    {

        result = S_OK;

    } while (false);

    return result;
}

// Exceptions include breaks which cannot
// be mapped to an existing breakpoint
// instance.
HRESULT __stdcall StandardEventCallbacks::Exception(_In_ PEXCEPTION_RECORD64 Exception, _In_ ULONG FirstChance)
{
    HRESULT result = E_FAIL;

    HRESULT hr = E_FAIL;

    do
    {

        result = S_OK;

    } while (false);

    return result;
}

// Any of these values can be zero if they
// cannot be provided by the engine.
// Currently the kernel does not return thread
// or process change events.
HRESULT __stdcall StandardEventCallbacks::CreateThread(_In_ ULONG64 Handle, _In_ ULONG64 DataOffset,
                                                       _In_ ULONG64 StartOffset)
{
    HRESULT result = E_FAIL;

    HRESULT hr = E_FAIL;

    do
    {

        result = S_OK;

    } while (false);

    return result;
}

HRESULT __stdcall StandardEventCallbacks::ExitThread(_In_ ULONG ExitCode)
{
    HRESULT result = E_FAIL;

    HRESULT hr = E_FAIL;

    do
    {

        result = S_OK;

    } while (false);

    return result;
}

// Any of these values can be zero if they
// cannot be provided by the engine.
HRESULT __stdcall StandardEventCallbacks::CreateProcess(_In_ ULONG64 ImageFileHandle, _In_ ULONG64 Handle,
                                                        _In_ ULONG64 BaseOffset, _In_ ULONG ModuleSize,
                                                        _In_opt_ PCSTR ModuleName, _In_opt_ PCSTR ImageName,
                                                        _In_ ULONG CheckSum, _In_ ULONG TimeDateStamp,
                                                        _In_ ULONG64 InitialThreadHandle, _In_ ULONG64 ThreadDataOffset,
                                                        _In_ ULONG64 StartOffset)
{
    HRESULT result = E_FAIL;

    HRESULT hr = E_FAIL;

    do
    {

        result = S_OK;

    } while (false);

    return result;
}

_Analysis_noreturn_ HRESULT __stdcall StandardEventCallbacks::ExitProcess(_In_ ULONG ExitCode)
{
    HRESULT result = E_FAIL;

    HRESULT hr = E_FAIL;

    do
    {

        result = S_OK;

    } while (false);

    return result;
}

// Any of these values may be zero.
HRESULT __stdcall StandardEventCallbacks::LoadModule(_In_ ULONG64 ImageFileHandle, _In_ ULONG64 BaseOffset,
                                                     _In_ ULONG ModuleSize, _In_opt_ PCSTR ModuleName,
                                                     _In_opt_ PCSTR ImageName, _In_ ULONG CheckSum,
                                                     _In_ ULONG TimeDateStamp)
{
    HRESULT result = E_FAIL;

    HRESULT hr = E_FAIL;

    do
    {

        result = S_OK;

    } while (false);

    return result;
}

HRESULT __stdcall StandardEventCallbacks::UnloadModule(_In_opt_ PCSTR ImageBaseName, _In_ ULONG64 BaseOffset)
{
    HRESULT result = E_FAIL;

    HRESULT hr = E_FAIL;

    do
    {

        result = S_OK;

    } while (false);

    return result;
}

HRESULT __stdcall StandardEventCallbacks::SystemError(_In_ ULONG Error, _In_ ULONG Level)
{
    HRESULT result = E_FAIL;

    HRESULT hr = E_FAIL;

    do
    {

        result = S_OK;

    } while (false);

    return result;
}

// Session status is synchronous like the other
// wait callbacks but it is called as the state
// of the session is changing rather than at
// specific events so its return value does not
// influence waiting.  Implementations should just
// return DEBUG_STATUS_NO_CHANGE.
// Also, because some of the status
// notifications are very early or very
// late in the session lifetime there may not be
// current processes or threads when the notification
// is generated.
HRESULT __stdcall StandardEventCallbacks::SessionStatus(_In_ ULONG Status)
{
    HRESULT result = E_FAIL;

    HRESULT hr = E_FAIL;

    do
    {

        result = S_OK;

    } while (false);

    return result;
}

// The following callbacks are informational
// callbacks notifying the provider about
// changes in debug state.  The return value
// of these callbacks is ignored.  Implementations
// can not call back into the engine.

// Debuggee state, such as registers or data spaces,
// has changed.
HRESULT __stdcall StandardEventCallbacks::ChangeDebuggeeState(_In_ ULONG Flags, _In_ ULONG64 Argument)
{
    HRESULT result = E_FAIL;

    HRESULT hr = E_FAIL;

    do
    {

        result = S_OK;

    } while (false);

    return result;
}

// Engine state has changed.
HRESULT __stdcall StandardEventCallbacks::ChangeEngineState(_In_ ULONG Flags, _In_ ULONG64 Argument)
{
    HRESULT result = E_FAIL;

    HRESULT hr = E_FAIL;

    do
    {

        result = S_OK;

    } while (false);

    return result;
}

// Symbol state has changed.
HRESULT __stdcall StandardEventCallbacks::ChangeSymbolState(_In_ ULONG Flags, _In_ ULONG64 Argument)
{
    HRESULT result = E_FAIL;

    HRESULT hr = E_FAIL;

    do
    {

        result = S_OK;

    } while (false);

    return result;
}
