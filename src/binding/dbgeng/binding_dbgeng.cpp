/**
 * @file binding_dbgeng.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#include "binding_dbgeng.h"

BindingDbgEng::BindingDbgEng(IDebugClient *debugClient, IDebugControl *debugControl)
{
    this->m_handle = nullptr;

    this->m_debugClient = debugClient;

    this->m_debugControl = debugControl;

    this->m_debugDataSpaces = nullptr;
}

BindingDbgEng::~BindingDbgEng()
{
    if (nullptr != this->m_debugDataSpaces)
    {
        this->m_debugDataSpaces->Release();
        this->m_debugDataSpaces = nullptr;
    }
}

JsErrorCode BindingDbgEng::Initialize()
{
    JsErrorCode errorCode = JsErrorFatal;

    JsErrorCode finalCode = JsErrorFatal;

    HRESULT  hr = E_FAIL;

    do
    {
        hr = this->m_debugClient->QueryInterface( __uuidof(IDebugDataSpaces), (PVOID *)&(this->m_debugDataSpaces) );
        if ( !SUCCEEDED(hr) )
        {
            break ;
        }


        errorCode = JsCreateExternalObject(this, nullptr, &(this->m_handle));
        if (JsNoError != errorCode)
        {
            break;
        }

        // bind
        errorCode = this->bindDebugClient();
        if (JsNoError != errorCode)
        {
            finalCode = errorCode;
            break;
        }

        errorCode = this->bindDebugControl();
        if (JsNoError != errorCode)
        {
            finalCode = errorCode;
            break;
        }



        errorCode = this->bindDebugDataSpaces();
        if (JsNoError != errorCode)
        {
            finalCode = errorCode;
            break;
        }


        finalCode = JsNoError;

    } while (false);

    return finalCode;
}

JsValueRef BindingDbgEng::GetHandle()
{
    return this->m_handle;
}

JsErrorCode BindingDbgEng::bindDebugClient()
{
   JsErrorCode errorCode = JsErrorFatal;

    JsErrorCode finalCode = JsErrorFatal;

    do
    {

        finalCode = JsNoError;
    } while (false);

    return finalCode;
}

JsErrorCode BindingDbgEng::bindDebugControl()
{
   JsErrorCode errorCode = JsErrorFatal;

    JsErrorCode finalCode = JsErrorFatal;

    do
    {

        errorCode = JsExSetPropertyFunction(this->m_handle, "Execute", BindingDbgEng::Execute, this, true);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = JsExSetPropertyFunction(this->m_handle, "GetNumberProcessors", BindingDbgEng::GetNumberProcessors,
                                            this, true);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = JsExSetPropertyFunction(this->m_handle, "GetPageSize", BindingDbgEng::GetPageSize, this, true);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode =
            JsExSetPropertyFunction(this->m_handle, "IsPointer64Bit", BindingDbgEng::IsPointer64Bit, this, true);
        if (JsNoError != errorCode)
        {
            break;
        }


        errorCode = JsExSetPropertyFunction(this->m_handle, "ControlOutput", BindingDbgEng::ControlOutput, this, true);
        if (JsNoError != errorCode)
        {
            break;
        }

        finalCode = JsNoError;
    } while (false);

    return finalCode;
}

JsErrorCode BindingDbgEng::bindDebugDataSpaces()
{
    JsErrorCode errorCode = JsErrorFatal;

    JsErrorCode finalCode = JsErrorFatal;

    do
    {

        errorCode =
            JsExSetPropertyFunction(this->m_handle, "ReadDebuggerData", BindingDbgEng::ReadDebuggerData, this, true);
        if (JsNoError != errorCode)
        {
            break;
        }




        finalCode = JsNoError;
    } while (false);

    return finalCode;
}
