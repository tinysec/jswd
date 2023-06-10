/**
 * @file commands.h
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#ifndef __MY_COMMANDS_HEADER_FILE__
#define __MY_COMMANDS_HEADER_FILE__
////////////////////////////////////////////////////

#include "precompile.h"

EXTERN_C HRESULT __stdcall jshelp(IDebugClient *debugClient, const char *cmdline);

EXTERN_C HRESULT __stdcall jscall(IDebugClient *debugClient, const char *cmdline);

EXTERN_C HRESULT __stdcall jsrun(IDebugClient *debugClient, const char *cmdline);

EXTERN_C HRESULT __stdcall jsload(IDebugClient *debugClient, const char *cmdline);

EXTERN_C HRESULT __stdcall jsunload(IDebugClient *debugClient, const char *cmdline);


EXTERN_C HRESULT __stdcall jslist(IDebugClient *debugClient, const char *cmdline);

EXTERN_C HRESULT __stdcall jsclear(IDebugClient *debugClient, const char *cmdline);

////////////////////////////////////////////////////
#endif //__MY_COMMANDS_HEADER_FILE__
