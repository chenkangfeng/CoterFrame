
#ifndef CF_PLUGIN_PROTOCOL_H
#define CF_PLUGIN_PROTOCOL_H

#include "CFPrecompiled.h"
#include <string>
#include "CFPluginFactory.h"

NS_CF_BEGIN

#define CFPluginRegister(Plugin) \
static void Plugin::RegisterPlugin(void) \
{ \
    CFPluginFactory::GetInstance()->registerPlugin(#Plugin, [](const char* name)->Plugin*{ \
        return new Plugin(name); \
    }); \
}

class CFPluginProtocol
{
public:
    CFPluginRegister(CFPluginProtocol)

    CFPluginProtocol(const std::string& name);
    virtual ~CFPluginProtocol(void);

    void setDebugMode(CFBool debug);

    virtual CFBool load(void);
    virtual CFBool unLoad(void);
private:
    CFBool _debug;
    std::string _pluginName;
};

NS_CF_END

#endif // CF_PLUGIN_PROTOCOL_H
