/**
 * @file extension.h
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#ifndef __MY_ENTRYPOINT_HEADER_FILE__
#define __MY_ENTRYPOINT_HEADER_FILE__
////////////////////////////////////////////////////

#include <jsrt.h>

EXTERN_C HRESULT __stdcall DebugExtensionInitialize(__out ULONG *pVersion, __out ULONG *pFlags);

EXTERN_C void __stdcall DebugExtensionUninitialize(void);

////////////////////////////////////////////////////
#endif //__MY_ENTRYPOINT_HEADER_FILE__
