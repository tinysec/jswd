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


  protected:

    JsErrorCode bindDebugClient();

    JsErrorCode bindDebugControl();

    JsErrorCode bindDebugDataSpaces();


  protected:
    // IDebugClient



  protected:
    // IDebugControl

     static _Ret_maybenull_ JsValueRef CALLBACK Execute(

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

     static _Ret_maybenull_ JsValueRef CALLBACK GetPageSize(

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

   public:

    static _Ret_maybenull_ JsValueRef CALLBACK ControlOutput(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );

  protected:
    // for IDebugDataSpaces

    static _Ret_maybenull_ JsValueRef CALLBACK ReadDebuggerData(

        _In_ JsValueRef callee,

        _In_ bool isConstructCall,

        _In_ JsValueRef *arguments,

        _In_ unsigned short argumentCount,

        _In_opt_ void *callbackState
     );



  protected:
    JsValueRef m_handle;

  protected:
    IDebugClient *m_debugClient;

    IDebugControl *m_debugControl;

    IDebugDataSpaces*m_debugDataSpaces;
};

////////////////////////////////////////////////////
#endif //__MY_BINDING_DBGENG_HEADER_FILE__
