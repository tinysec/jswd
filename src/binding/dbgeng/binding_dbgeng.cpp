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

    this->m_debugClient2 = nullptr;

    this->m_debugControl = debugControl;

    this->m_debugDataSpaces = nullptr;

    this->m_debugRegisters = nullptr;

    this->m_debugSymbols = nullptr;

    this->m_debugSystemObjects = nullptr;

    this->m_debugSystemObjects2 = nullptr;
}

BindingDbgEng::~BindingDbgEng()
{
    if (nullptr != this->m_debugClient2)
    {
        this->m_debugClient2->Release();
        this->m_debugClient2 = nullptr;
    }

    if (nullptr != this->m_debugDataSpaces)
    {
        this->m_debugDataSpaces->Release();
        this->m_debugDataSpaces = nullptr;
    }

    if (nullptr != this->m_debugRegisters)
    {
        this->m_debugRegisters->Release();
        this->m_debugRegisters = nullptr;
    }

    if (nullptr != this->m_debugSymbols)
    {
        this->m_debugSymbols->Release();
        this->m_debugSymbols = nullptr;
    }

    if (nullptr != this->m_debugSystemObjects)
    {
        this->m_debugSystemObjects->Release();
        this->m_debugSystemObjects = nullptr;
    }

    if (nullptr != this->m_debugSystemObjects2)
    {
        this->m_debugSystemObjects2->Release();
        this->m_debugSystemObjects2 = nullptr;
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

        hr = this->m_debugClient->QueryInterface( __uuidof(IDebugClient2), (PVOID *)&(this->m_debugClient2) );
        if ( !SUCCEEDED(hr) )
        {
            break ;
        }

        hr = this->m_debugClient->QueryInterface( __uuidof(IDebugDataSpaces), (PVOID *)&(this->m_debugDataSpaces) );
        if ( !SUCCEEDED(hr) )
        {
            break ;
        }

        hr = this->m_debugClient->QueryInterface( __uuidof(IDebugRegisters), (PVOID *)&(this->m_debugRegisters) );
        if ( !SUCCEEDED(hr) )
        {
            break ;
        }

        hr = this->m_debugClient->QueryInterface( __uuidof(IDebugSymbols), (PVOID *)&(this->m_debugSymbols) );
        if ( !SUCCEEDED(hr) )
        {
            break ;
        }

         hr = this->m_debugClient->QueryInterface( __uuidof(IDebugSystemObjects), (PVOID *)&(this->m_debugSystemObjects) );
        if ( !SUCCEEDED(hr) )
        {
            break ;
        }

         hr = this->m_debugClient->QueryInterface( __uuidof(IDebugSystemObjects2), (PVOID *)&(this->m_debugSystemObjects2) );
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

        errorCode = this->bindDebugClient2();
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

        errorCode = this->bindDebugRegisters();
        if (JsNoError != errorCode)
        {
            finalCode = errorCode;
            break;
        }

        errorCode = this->bindDebugSymbols();
        if (JsNoError != errorCode)
        {
            finalCode = errorCode;
            break;
        }

        errorCode = this->bindDebugSystemObjects();
        if (JsNoError != errorCode)
        {
            finalCode = errorCode;
            break;
        }

        errorCode = this->bindDebugSystemObjects2();
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

JsErrorCode BindingDbgEng::bindRoutine(
    _In_ const std::string &name,
    _In_ JsNativeFunction routine
)
{
    return JsExSetPropertyFunction(this->m_handle, name, routine,this, true);
}

JsErrorCode BindingDbgEng::bindDebugClient()
{
    JsErrorCode errorCode = JsErrorFatal;

    JsErrorCode finalCode = JsErrorFatal;

    do
    {

        errorCode = this->bindRoutine("getExitCode", BindingDbgEng::GetExitCode);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getIdentity", BindingDbgEng::GetIdentity);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getRunningProcessDescription", BindingDbgEng::GetRunningProcessDescription);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getRunningProcessSystemIdByExecutableName", BindingDbgEng::GetRunningProcessSystemIdByExecutableName);
        if (JsNoError != errorCode)
        {
            break;
        }

         errorCode = this->bindRoutine("writeDumpFile", BindingDbgEng::WriteDumpFile);
        if (JsNoError != errorCode)
        {
            break;
        }

        finalCode = JsNoError;
    } while (false);

    return finalCode;
}

JsErrorCode BindingDbgEng::bindDebugClient2()
{
  JsErrorCode errorCode = JsErrorFatal;

    JsErrorCode finalCode = JsErrorFatal;

    do
    {

        errorCode = this->bindRoutine("isKernelDebuggerEnabled", BindingDbgEng::IsKernelDebuggerEnabled);
        if (JsNoError != errorCode)
        {
            break;
        }

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

        errorCode = this->bindRoutine("assemble", BindingDbgEng::Assemble);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("callExtension", BindingDbgEng::CallExtension);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("disassemble", BindingDbgEng::Disassemble);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("execute", BindingDbgEng::Execute);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getActualProcessorType", BindingDbgEng::GetActualProcessorType);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getCodeLevel", BindingDbgEng::GetCodeLevel);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getDebuggeeType", BindingDbgEng::GetDebuggeeType);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getEffectiveProcessorType", BindingDbgEng::GetEffectiveProcessorType);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getExecutingProcessorType", BindingDbgEng::GetExecutingProcessorType);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getExecutionStatus", BindingDbgEng::GetExecutionStatus);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getNearInstruction", BindingDbgEng::GetNearInstruction);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getNumberPossibleExecutingProcessorTypes", BindingDbgEng::GetNumberPossibleExecutingProcessorTypes);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getNumberProcessors", BindingDbgEng::GetNumberProcessors);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getNumberSupportedProcessorTypes", BindingDbgEng::GetNumberSupportedProcessorTypes);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getPageSize", BindingDbgEng::GetPageSize);
        if (JsNoError != errorCode)
        {
            break;
        }


        errorCode = this->bindRoutine("getProcessorTypeNames", BindingDbgEng::GetProcessorTypeNames);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getReturnOffset", BindingDbgEng::GetReturnOffset);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getStackTrace", BindingDbgEng::GetStackTrace);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getSystemVersion", BindingDbgEng::GetSystemVersion);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("isPointer64Bit", BindingDbgEng::IsPointer64Bit);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("readBugCheck", BindingDbgEng::ReadBugCheck);
        if (JsNoError != errorCode)
        {
            break;
        }


        errorCode = this->bindRoutine("setEffectiveProcessorType", BindingDbgEng::SetEffectiveProcessorType);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("setExecutionStatus", BindingDbgEng::SetExecutionStatus);
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

        errorCode = this->bindRoutine("readBus", BindingDbgEng::ReadBus);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("readControl" , BindingDbgEng::ReadControl );
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("readDebugger", BindingDbgEng::ReadDebugger);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("readIo" , BindingDbgEng::ReadIo );
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("readMsr", BindingDbgEng::ReadMsr);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("readPhysical", BindingDbgEng::ReadPhysical);
        if (JsNoError != errorCode)
        {
            break;
        }

         errorCode = this->bindRoutine("readProcessor", BindingDbgEng::ReadProcessor);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("readVirtual", BindingDbgEng::ReadVirtual);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("searchVirtual", BindingDbgEng::SearchVirtual);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("writeBus", BindingDbgEng::WriteBus);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("writeControl", BindingDbgEng::WriteControl);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("writeIo", BindingDbgEng::WriteIo);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("writeMsr", BindingDbgEng::WriteMsr);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("writeVirtual", BindingDbgEng::WriteVirtual);
        if (JsNoError != errorCode)
        {
            break;
        }


        finalCode = JsNoError;
    } while (false);

    return finalCode;
}

JsErrorCode BindingDbgEng::bindDebugRegisters()
{
    JsErrorCode errorCode = JsErrorFatal;

    JsErrorCode finalCode = JsErrorFatal;

    do
    {

        errorCode = this->bindRoutine("getRegisterDescription" , BindingDbgEng::GetRegisterDescription );
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getFrameOffset", BindingDbgEng::GetFrameOffset);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getRegisterIndex", BindingDbgEng::GetRegisterIndex);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getInstructionOffset", BindingDbgEng::GetInstructionOffset);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getNumberRegisters", BindingDbgEng::GetNumberRegisters);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getStackOffset", BindingDbgEng::GetStackOffset);
        if (JsNoError != errorCode)
        {
            break;
        }

         errorCode = this->bindRoutine("getRegisterValue", BindingDbgEng::GetRegisterValue);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("setRegisterValue", BindingDbgEng::SetRegisterValue);
        if (JsNoError != errorCode)
        {
            break;
        }

        finalCode = JsNoError;
    } while (false);

    return finalCode;
}

JsErrorCode BindingDbgEng::bindDebugSymbols()
{
    JsErrorCode errorCode = JsErrorFatal;

    JsErrorCode finalCode = JsErrorFatal;

    do
    {

        errorCode = this->bindRoutine("getFieldOffset" , BindingDbgEng::GetFieldOffset );
        if (JsNoError != errorCode)
        {
            break;
        }


        errorCode = this->bindRoutine("getModuleByIndex" , BindingDbgEng::GetModuleByIndex );
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getModuleByName", BindingDbgEng::GetModuleByName);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getModuleByOffset", BindingDbgEng::GetModuleByOffset);
        if (JsNoError != errorCode)
        {
            break;
        }

         errorCode = this->bindRoutine("getModuleNames", BindingDbgEng::GetModuleNames);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getModuleParameters", BindingDbgEng::GetModuleParameters);
        if (JsNoError != errorCode)
        {
            break;
        }

         errorCode = this->bindRoutine("getNameByOffset", BindingDbgEng::GetNameByOffset);
        if (JsNoError != errorCode)
        {
            break;
        }

         errorCode = this->bindRoutine("getNearNameByOffset", BindingDbgEng::GetNearNameByOffset);
        if (JsNoError != errorCode)
        {
            break;
        }

         errorCode = this->bindRoutine("getNumberModules", BindingDbgEng::GetNumberModules);
        if (JsNoError != errorCode)
        {
            break;
        }

         errorCode = this->bindRoutine("getOffsetByName", BindingDbgEng::GetOffsetByName);
        if (JsNoError != errorCode)
        {
            break;
        }

         errorCode = this->bindRoutine("getOffsetTypeId", BindingDbgEng::GetOffsetTypeId);
        if (JsNoError != errorCode)
        {
            break;
        }


         errorCode = this->bindRoutine("getSymbolModule", BindingDbgEng::GetSymbolModule);
        if (JsNoError != errorCode)
        {
            break;
        }

         errorCode = this->bindRoutine("getSymbolPath", BindingDbgEng::GetSymbolPath);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getSymbolTypeId", BindingDbgEng::GetSymbolTypeId);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getTypeId", BindingDbgEng::GetTypeId);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getTypeName", BindingDbgEng::GetTypeName);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getTypeSize", BindingDbgEng::GetTypeSize);
        if (JsNoError != errorCode)
        {
            break;
        }


        errorCode = this->bindRoutine("reload", BindingDbgEng::Reload);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("setSymbolPath", BindingDbgEng::SetSymbolPath);
        if (JsNoError != errorCode)
        {
            break;
        }

        finalCode = JsNoError;
    } while (false);

    return finalCode;
}

JsErrorCode BindingDbgEng::bindDebugSystemObjects()
{
    JsErrorCode errorCode = JsErrorFatal;

    JsErrorCode finalCode = JsErrorFatal;

    do
    {

        errorCode = this->bindRoutine("getCurrentProcessDataOffset" , BindingDbgEng::GetCurrentProcessDataOffset );
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getCurrentProcessId" , BindingDbgEng::GetCurrentProcessId );
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getCurrentProcessPeb", BindingDbgEng::GetCurrentProcessPeb);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getCurrentProcessSystemId", BindingDbgEng::GetCurrentProcessSystemId);
        if (JsNoError != errorCode)
        {
            break;
        }

         errorCode = this->bindRoutine("getCurrentThreadDataOffset", BindingDbgEng::GetCurrentThreadDataOffset);
        if (JsNoError != errorCode)
        {
            break;
        }

         errorCode = this->bindRoutine("getCurrentThreadId", BindingDbgEng::GetCurrentThreadId);
        if (JsNoError != errorCode)
        {
            break;
        }

         errorCode = this->bindRoutine("getCurrentThreadSystemId", BindingDbgEng::GetCurrentThreadSystemId);
        if (JsNoError != errorCode)
        {
            break;
        }

         errorCode = this->bindRoutine("getCurrentThreadTeb", BindingDbgEng::GetCurrentThreadTeb);
        if (JsNoError != errorCode)
        {
            break;
        }

         errorCode = this->bindRoutine("getThreadIdByProcessor", BindingDbgEng::GetThreadIdByProcessor);
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("setCurrentThreadId", BindingDbgEng::SetCurrentThreadId);
        if (JsNoError != errorCode)
        {
            break;
        }


        finalCode = JsNoError;
    } while (false);

    return finalCode;
}


JsErrorCode BindingDbgEng::bindDebugSystemObjects2()
{
    JsErrorCode errorCode = JsErrorFatal;

    JsErrorCode finalCode = JsErrorFatal;

    do
    {

        errorCode = this->bindRoutine("getImplicitProcessDataOffset" , BindingDbgEng::GetImplicitProcessDataOffset );
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("getImplicitThreadDataOffset" , BindingDbgEng::GetImplicitThreadDataOffset );
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("setImplicitProcessDataOffset" , BindingDbgEng::SetImplicitProcessDataOffset );
        if (JsNoError != errorCode)
        {
            break;
        }

        errorCode = this->bindRoutine("setImplicitThreadDataOffset" , BindingDbgEng::SetImplicitThreadDataOffset );
        if (JsNoError != errorCode)
        {
            break;
        }


        finalCode = JsNoError;
    } while (false);

    return finalCode;
}
