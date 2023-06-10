/**
 * @file standard_output_callbacks.h
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#ifndef __MY_STANDARD_OUTPUT_CALLBACKS_HEADER_FILE__
#define __MY_STANDARD_OUTPUT_CALLBACKS_HEADER_FILE__
////////////////////////////////////////////////////

#include "precompile.h"

class StandardOutputCallbacks : public IDebugOutputCallbacks
{
  public:
    StandardOutputCallbacks();

    ~StandardOutputCallbacks();

  public:
    // IUnknown.
    HRESULT __stdcall QueryInterface(_In_ REFIID InterfaceId, _Out_ PVOID *ppvObject);

    ULONG __stdcall AddRef();

    ULONG __stdcall Release();

  public:
    // IDebugOutputCallbacks.

    HRESULT __stdcall Output(_In_ ULONG Mask, _In_ PCSTR Text);

  private:
    ULONG m_refs;
};

////////////////////////////////////////////////////
#endif //__MY_STANDARD_OUTPUT_CALLBACKS_HEADER_FILE__
