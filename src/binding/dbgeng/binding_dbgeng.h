/**
 * @file binding_dbgeng.h
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#ifndef __MY_BINDING_DBGENG_HEADER_FILE__
#define __MY_BINDING_DBGENG_HEADER_FILE__
////////////////////////////////////////////////////

#include <precompile.h>

class BindingDbgEng
{
  public:
    BindingDbgEng(IDebugClient *debugClient, IDebugControl *debugControl);

    ~BindingDbgEng();

  public:
    JsErrorCode Initialize();

    JsValueRef GetHandle();


    JsErrorCode bindRoutine(
        _In_ const std::string &name,
        _In_ JsNativeFunction routine
    );

  protected:

    JsErrorCode bindDebugClient();

    JsErrorCode bindDebugClient2();

    JsErrorCode bindDebugControl();

    JsErrorCode bindDebugDataSpaces();

    JsErrorCode bindDebugRegisters();

    JsErrorCode bindDebugSymbols();

    JsErrorCode bindDebugSystemObjects();

    JsErrorCode bindDebugSystemObjects2();

public:

    static _Ret_maybenull_ JsValueRef CALLBACK ControlOutput(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );


  protected:
    // IDebugClient

    static _Ret_maybenull_ JsValueRef CALLBACK GetExitCode(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetIdentity(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetRunningProcessDescription(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetRunningProcessSystemIdByExecutableName(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );


    static _Ret_maybenull_ JsValueRef CALLBACK WriteDumpFile(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );


protected:

    // IDebugClient2

    static _Ret_maybenull_ JsValueRef CALLBACK IsKernelDebuggerEnabled(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );


  protected:
    // IDebugControl

    static _Ret_maybenull_ JsValueRef CALLBACK Assemble(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK CallExtension(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK Disassemble(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );


    static _Ret_maybenull_ JsValueRef CALLBACK Evaluate(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

     static _Ret_maybenull_ JsValueRef CALLBACK Execute(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

      static _Ret_maybenull_ JsValueRef CALLBACK GetActualProcessorType(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

      static _Ret_maybenull_ JsValueRef CALLBACK GetCodeLevel(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

      static _Ret_maybenull_ JsValueRef CALLBACK GetDebuggeeType(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

     static _Ret_maybenull_ JsValueRef CALLBACK GetEffectiveProcessorType(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetExecutingProcessorType(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetExecutionStatus(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetNearInstruction(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

     static _Ret_maybenull_ JsValueRef CALLBACK GetNumberPossibleExecutingProcessorTypes(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

     static _Ret_maybenull_ JsValueRef CALLBACK GetNumberProcessors(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

      static _Ret_maybenull_ JsValueRef CALLBACK GetNumberSupportedProcessorTypes(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

     static _Ret_maybenull_ JsValueRef CALLBACK GetPageSize(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );




     static _Ret_maybenull_ JsValueRef CALLBACK GetProcessorTypeNames(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );


     static _Ret_maybenull_ JsValueRef CALLBACK GetReturnOffset(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

     static _Ret_maybenull_ JsValueRef CALLBACK GetStackTrace(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );


     static _Ret_maybenull_ JsValueRef CALLBACK GetSystemVersion(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

     static _Ret_maybenull_ JsValueRef CALLBACK IsPointer64Bit(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

      static _Ret_maybenull_ JsValueRef CALLBACK ReadBugCheck(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );


      static _Ret_maybenull_ JsValueRef CALLBACK SetEffectiveProcessorType(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

      static _Ret_maybenull_ JsValueRef CALLBACK SetExecutionStatus(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );





  protected:
    // for IDebugDataSpaces

    static _Ret_maybenull_ JsValueRef CALLBACK ReadBus(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK ReadControl(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK ReadDebugger(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

     static _Ret_maybenull_ JsValueRef CALLBACK ReadIo(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

     static _Ret_maybenull_ JsValueRef CALLBACK ReadMsr(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

     static _Ret_maybenull_ JsValueRef CALLBACK ReadPhysical(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

     static _Ret_maybenull_ JsValueRef CALLBACK ReadProcessor(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );


     static _Ret_maybenull_ JsValueRef CALLBACK ReadVirtual(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

     static _Ret_maybenull_ JsValueRef CALLBACK SearchVirtual(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

     static _Ret_maybenull_ JsValueRef CALLBACK WriteBus(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

     static _Ret_maybenull_ JsValueRef CALLBACK WriteControl(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

     static _Ret_maybenull_ JsValueRef CALLBACK WriteIo(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

     static _Ret_maybenull_ JsValueRef CALLBACK WriteMsr(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

     static _Ret_maybenull_ JsValueRef CALLBACK WritePhysical(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

     static _Ret_maybenull_ JsValueRef CALLBACK WriteVirtual(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

protected:

     // IDebugRegisters

    static _Ret_maybenull_ JsValueRef CALLBACK GetRegisterDescription(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetFrameOffset(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetRegisterIndex(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetInstructionOffset(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetNumberRegisters(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetStackOffset(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetRegisterValue(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK SetRegisterValue(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );


protected:

    // IDebugSymbolGroup

protected:

    // IDebugSymbols

    static _Ret_maybenull_ JsValueRef CALLBACK GetFieldOffset(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );


    static _Ret_maybenull_ JsValueRef CALLBACK GetModuleByIndex(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetModuleByName(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetModuleByOffset(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetModuleNames(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetModuleParameters(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetNameByOffset(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetNearNameByOffset(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetNumberModules(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetOffsetByName(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetOffsetTypeId(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );


    static _Ret_maybenull_ JsValueRef CALLBACK GetSymbolModule(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetSymbolPath(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetSymbolTypeId(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetTypeId(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetTypeName(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetTypeSize(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );


    static _Ret_maybenull_ JsValueRef CALLBACK Reload(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK SetSymbolPath(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );


protected:

    // for IDebugSystemObjects

    static _Ret_maybenull_ JsValueRef CALLBACK GetCurrentProcessDataOffset(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetCurrentProcessExecutableName(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );


    static _Ret_maybenull_ JsValueRef CALLBACK GetCurrentProcessId(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetCurrentProcessPeb(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetCurrentProcessSystemId(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetCurrentThreadDataOffset(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetCurrentThreadId(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetCurrentThreadSystemId(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetCurrentThreadTeb(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );


    static _Ret_maybenull_ JsValueRef CALLBACK GetThreadIdByProcessor(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK SetCurrentThreadId(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

      protected:

    // for IDebugSystemObjects2

    static _Ret_maybenull_ JsValueRef CALLBACK GetImplicitProcessDataOffset(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK GetImplicitThreadDataOffset(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );


    static _Ret_maybenull_ JsValueRef CALLBACK SetImplicitProcessDataOffset(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

    static _Ret_maybenull_ JsValueRef CALLBACK SetImplicitThreadDataOffset(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );


  protected:

    JsValueRef m_handle;

  protected:
    IDebugClient*  m_debugClient;

    IDebugClient2*  m_debugClient2;

    IDebugControl*      m_debugControl;

    IDebugDataSpaces*   m_debugDataSpaces;

    IDebugRegisters*      m_debugRegisters;

    IDebugSymbols*        m_debugSymbols;

    IDebugSystemObjects*   m_debugSystemObjects;

    IDebugSystemObjects2*   m_debugSystemObjects2;
};

////////////////////////////////////////////////////
#endif //__MY_BINDING_DBGENG_HEADER_FILE__
