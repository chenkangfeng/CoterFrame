
#include "CFPrecompiled.h"
#include "CFPluginFactory.h"
#include "CFPluginProtocol.h"

NS_CF_BEGIN

CFPluginFactory::CFPluginFactory(void)
{
}

CFPluginFactory::~CFPluginFactory(void)
{
}

void CFPluginFactory::registerPlugin(const char* name, const CFPluginCreator& creator)
{
    _mapPluginsType::iterator iter = _mapPlugins.find(name);
    if (iter == _mapPlugins.end()) {
        _mapPlugins.insert(_mapPluginsType::value_type(name, std::move(creator)));
    }
    else {
        iter->second = creator;
    }
}

CFPluginProtocol* CFPluginFactory::createPlugin(const char* name)
{
    CFPluginProtocol* ret = nullptr;
    _mapPluginsType::iterator iter = _mapPlugins.find(name);
    if (iter != _mapPlugins.end()) {
        ret = iter->second(name);
        if (nullptr != ret) {
            if (!ret->load()) {
                CF_ASSERT(ret->unLoad());
                CF_SAFE_DELETE(ret);
            }
        }
    }
    return ret;
}

NS_CF_END
