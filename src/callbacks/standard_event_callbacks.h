/**
 * @file standard_event_callbacks.h
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#ifndef __MY_STANDARD_EVENT_CALLBACKS_HEADER_FILE__
#define __MY_STANDARD_EVENT_CALLBACKS_HEADER_FILE__
////////////////////////////////////////////////////

#include "precompile.h"

class StandardEventCallbacks : public IDebugEventCallbacks
{
  public:
    StandardEventCallbacks();

    ~StandardEventCallbacks();

  public:
    // IUnknown.
    HRESULT __stdcall QueryInterface(_In_ REFIID InterfaceId, _Out_ PVOID *ppvObject);

    ULONG __stdcall AddRef();

    ULONG __stdcall Release();

  public:
    // IDebugEventCallbacks.

    // The engine calls GetInterestMask once when
    // the event callbacks are set for a client.
    HRESULT __stdcall GetInterestMask(_Out_ PULONG Mask);

    // A breakpoint event is generated when
    // a breakpoint exception is received and
    // it can be mapped to an existing breakpoint.
    // The callback method is given a reference
    // to the breakpoint and should release it when
    // it is done with it.
    HRESULT __stdcall Breakpoint(_In_ PDEBUG_BREAKPOINT Bp);

    // Exceptions include breaks which cannot
    // be mapped to an existing breakpoint
    // instance.
    HRESULT __stdcall Exception(_In_ PEXCEPTION_RECORD64 Exception, _In_ ULONG FirstChance);

    // Any of these values can be zero if they
    // cannot be provided by the engine.
    // Currently the kernel does not return thread
    // or process change events.
    HRESULT __stdcall CreateThread(_In_ ULONG64 Handle, _In_ ULONG64 DataOffset, _In_ ULONG64 StartOffset);

    HRESULT __stdcall ExitThread(_In_ ULONG ExitCode);

    // Any of these values can be zero if they
    // cannot be provided by the engine.
    HRESULT __stdcall CreateProcess(_In_ ULONG64 ImageFileHandle, _In_ ULONG64 Handle, _In_ ULONG64 BaseOffset,
                                    _In_ ULONG ModuleSize, _In_opt_ PCSTR ModuleName, _In_opt_ PCSTR ImageName,
                                    _In_ ULONG CheckSum, _In_ ULONG TimeDateStamp, _In_ ULONG64 InitialThreadHandle,
                                    _In_ ULONG64 ThreadDataOffset, _In_ ULONG64 StartOffset);

    _Analysis_noreturn_ HRESULT __stdcall ExitProcess(_In_ ULONG ExitCode);

    // Any of these values may be zero.
    HRESULT __stdcall LoadModule(_In_ ULONG64 ImageFileHandle, _In_ ULONG64 BaseOffset, _In_ ULONG ModuleSize,
                                 _In_opt_ PCSTR ModuleName, _In_opt_ PCSTR ImageName, _In_ ULONG CheckSum,
                                 _In_ ULONG TimeDateStamp);

    HRESULT __stdcall UnloadModule(_In_opt_ PCSTR ImageBaseName, _In_ ULONG64 BaseOffset);

    HRESULT __stdcall SystemError(_In_ ULONG Error, _In_ ULONG Level);

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
    HRESULT __stdcall SessionStatus(_In_ ULONG Status);

    // The following callbacks are informational
    // callbacks notifying the provider about
    // changes in debug state.  The return value
    // of these callbacks is ignored.  Implementations
    // can not call back into the engine.

    // Debuggee state, such as registers or data spaces,
    // has changed.
    HRESULT __stdcall ChangeDebuggeeState(_In_ ULONG Flags, _In_ ULONG64 Argument);

    // Engine state has changed.
    HRESULT __stdcall ChangeEngineState(_In_ ULONG Flags, _In_ ULONG64 Argument);

    // Symbol state has changed.
    HRESULT __stdcall ChangeSymbolState(_In_ ULONG Flags, _In_ ULONG64 Argument);

  private:
    ULONG m_refs;

  private:
    IDebugClient *m_debugClient;
};

////////////////////////////////////////////////////
#endif //__MY_STANDARD_EVENT_CALLBACKS_HEADER_FILE__
