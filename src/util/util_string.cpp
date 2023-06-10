/**
 * @file util_string.cpp
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#include <precompile.h>

#include <codecvt>

#include <cstring>

#include <locale>

std::vector<std::string> UtilCmdlineToArgv(const std::string &cmdline)
{
    HRESULT result = E_FAIL;

    HRESULT hr = E_FAIL;

    LPWSTR *wideArgv = nullptr;

    int i = 0;

    std::wstring wideArg;

    int argc = 0;

    std::string arg;

    std::vector<std::string> argv;

    do
    {
        if (!cmdline.empty())
        {
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

            std::wstring wideCmdline = converter.from_bytes(cmdline.c_str());

            wideArgv = CommandLineToArgvW(wideCmdline.c_str(), &argc);
            if (nullptr == wideArgv)
            {
                break;
            }

            for (i = 0; i < argc; i++)
            {
                wideArg = std::wstring(wideArgv[i]);

                arg = converter.to_bytes(wideArg.c_str());

                argv.push_back(arg);
            }
        }

        result = S_OK;

    } while (false);

    if (nullptr != wideArgv)
    {
        LocalFree(wideArgv);
        wideArgv = nullptr;
    }

    return argv;
}