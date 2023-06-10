/**
 * @file solar.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#include "precompile.h"

#include "extension.h"

#include "version.h"

Extension *extensionInstance = nullptr;

Extension::Extension()
{
    this->m_pod = new JSPod();
}

Extension::~Extension()
{
    if (nullptr != this->m_pod)
    {
        delete this->m_pod;

        this->m_pod = nullptr;
    }
}

Extension *Extension::GetInstance()
{
    if (nullptr == extensionInstance)
    {
        extensionInstance = new Extension();
    }

    return extensionInstance;
}

HRESULT Extension::Initialize()
{
    HRESULT result = E_FAIL;

    HRESULT hr = E_FAIL;

    do
    {
        hr = this->m_pod->Initialize();
        if (!SUCCEEDED(hr))
        {
            result = hr;
            break;
        }

        this->m_pod->DebugPrintf(MY_BANNER);

        this->m_pod->DebugPrintf("use !js.help to get the usage , have a nice day.\n");

        result = S_OK;
    } while (false);

    return result;
}

void Extension::printUsage()
{
    do
    {

        this->m_pod->DebugPrintf(MY_BANNER);

        this->m_pod->DebugPrintf("Version: %d.%d.%d.%d , build from %s.%s , compile at %s %s\n",
                                 MY_VERSION_MAJOR,
                                 MY_VERSION_MINOR,
                                 MY_VERSION_PART_3,
                                 MY_VERSION_PART_4,
                                 GIT_BRANCH,
                                 GIT_COMMIT_HASH,
                                 __DATE__, __TIME__);

        this->m_pod->DebugPrintf("You can get help from https://github.com/tinysec/jswd.\n");

        this->m_pod->DebugPrintf("Usage: !js.[command] [args]...\n");

        this->m_pod->DebugPrintf(
            "+-------------+----------------------------+---------------------------------------+\n");

        this->m_pod->DebugPrintf(
            "| command     | usage                      | decription                            |\n");

        this->m_pod->DebugPrintf(
            "+-------------+----------------------------+---------------------------------------+\n");

        this->m_pod->DebugPrintf(
            "| !js         | !js script.js              | same as !jsrun                        |\n");

        this->m_pod->DebugPrintf(
            "| !jshelp     | !jshelp                    | print help                            |\n");

        this->m_pod->DebugPrintf(
            "| !jscall     | !jscall script.js foobar   | call a already loaded file's method   |\n");

        this->m_pod->DebugPrintf(
            "| !jsrun      | !jsrun script.js           | run a script file and call main       |\n");

        this->m_pod->DebugPrintf(
            "| !jslist     | !jslist                    | list all loaded script files          |\n");

        this->m_pod->DebugPrintf(
            "| !jsclear    | !jsclear                   | unload all loaded script files        |\n");

        this->m_pod->DebugPrintf(
            "| !jsload     | !jsload script.js          | load a script file                    |\n");

        this->m_pod->DebugPrintf(
            "| !jsunload   | !jsunload script.js        | unload a already loaded file          |\n");

        this->m_pod->DebugPrintf(
            "| !js.help    | !js.help                   | same as !jshelp                       |\n");

        this->m_pod->DebugPrintf(
            "| !js.js      | !js.js script.js           | same as !jsrun                        |\n");

        this->m_pod->DebugPrintf(
            "| !js.call    | !js.call script.js         | same as !jscall                       |\n");

        this->m_pod->DebugPrintf(
            "| !js.run     | !js.run script.js          | same as !jsrun                        |\n");

        this->m_pod->DebugPrintf(
            "| !js.clear   | !js.clear                  | same as !jsclear                      |\n");

        this->m_pod->DebugPrintf(
            "| !js.list    | !js.list                   | same as !jslist                       |\n");

        this->m_pod->DebugPrintf(
            "| !js.load    | !js.load script.js         | same as !jsload                       |\n");

        this->m_pod->DebugPrintf(
            "| !js.unload  | !js.unload script.js       | same as !jsunload                     |\n");

        this->m_pod->DebugPrintf(
            "+-------------+----------------------------+---------------------------------------+\n");

    } while (false);
}


JsValueRef Extension::FindScript(const std::string& name)
{
    std::map<std::string , JsValueRef>::iterator it;

    it = this->m_scripts.find( name );
    if (this->m_scripts.end() == it )
    {
        return nullptr;
    }

    return it->second;
}

bool Extension::AddScript(const std::string& name , JsValueRef exports)
{
    std::map<std::string , JsValueRef>::iterator it;

    it = this->m_scripts.find( name );
    if (this->m_scripts.end() != it )
    {
        return false;
    }

    JsAddRef(exports , nullptr);

    this->m_scripts[name] = exports;

    return true;
}

JsValueRef Extension::RemoveScript(const std::string& name)
{
    std::map<std::string , JsValueRef>::iterator it;

    JsValueRef exports = nullptr;

    it = this->m_scripts.find( name );
    if (this->m_scripts.end() == it )
    {
        return nullptr;
    }

    exports = it->second;

    this->m_scripts.erase(it);

    return exports;
}

