/**
 * @file solar.h
 * @author tinysec
 * @brief
 * @version 0.0.1

 */

#ifndef __MY_EXTENSION_HEADER_FILE__
#define __MY_EXTENSION_HEADER_FILE__
////////////////////////////////////////////////////

#include "src/precompile.h"

#include "core/js_pod.h"

class Extension
{
  public:
    Extension();

    ~Extension();

  public:
    static Extension *GetInstance();

  public:

    HRESULT Initialize();

    void printUsage();


  public:

    JsValueRef FindScript(const std::string& name);

    bool AddScript(const std::string& name , JsValueRef exports);

    JsValueRef RemoveScript(const std::string& name);


  public:

    JSPod *m_pod;

  public:
    std::map<std::string , JsValueRef> m_scripts;
};

////////////////////////////////////////////////////
#endif //__MY_EXTENSION_HEADER_FILE__
