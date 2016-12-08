
#include "CFPrecompiled.h"
#include "CFPluginProtocol.h"

NS_CF_BEGIN

CFPluginProtocol::CFPluginProtocol(const std::string& name) :
_pluginName(name)
{
}

CFPluginProtocol::~CFPluginProtocol(void)
{
}

void CFPluginProtocol::setDebugMode(CFBool debug)
{
    _debug = debug;
}

CFBool CFPluginProtocol::load(void)
{
    return false;
}

CFBool CFPluginProtocol::unLoad(void)
{
    return false;
}

NS_CF_END
