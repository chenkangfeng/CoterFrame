//  
//  Author  : Coter
//  Data    : 2016-12-06
//

#ifndef CF_DYNLIB_H
#define CF_DYNLIB_H

#include "CFPrecompiled.h"

NS_CF_BEGIN

#if CF_PLATFORM(CF_PLATFORM_WIN)
struct HINSTANCE__;
#define DYNLIB_HANDLE struct HINSTANCE__*
#define DYNLIB_LOAD(Library) LoadLibraryEx(Library, NULL, LOAD_WITH_ALTERED_SEARCH_PATH)
#define DYNLIB_GETSYM(Handle, Symbol) GetProcAddress(Handle, Symbol)
#define DYNLIB_UNLOAD(Library) FreeLibrary(Library)
#elif CF_PLATFORM(CF_PLATFORM_LINUX | CF_PLATFORM_ANDROID)
    #include <dlfcn.h>
    #define DYNLIB_HANDLE void*
    #define DYNLIB_LOAD(Library) dlopen(Library, RTLD_LAZY | RTLD_GLOBAL)
    #define DYNLIB_GETSYM(Handle, Symbol) dlsym(Handle, Symbol)
    #define DYNLIB_UNLOAD(Library) dlclose(Library)
#elif CF_PLATFORM(CF_PLATFORM_MAC | CF_PLATFORM_IOS)
    #include <dlfcn.h>
    #define DYNLIB_HANDLE void*
    #define DYNLIB_LOAD(Library) dlopen(Library, RTLD_LAZY | RTLD_LOCAL)
    #define DYNLIB_GETSYM(Handle, Symbol) dlsym(Handle, Symbol)
    #define DYNLIB_UNLOAD(Library) dlclose(Library)
#endif

class CFDynLib
{
public:
    CFDynLib(CFStrPtr libName);
    ~CFDynLib(void);

private:
    std::string _libName;
};

NS_CF_END

#endif // CF_DYNLIB_H
