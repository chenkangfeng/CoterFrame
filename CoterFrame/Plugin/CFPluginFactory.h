
#ifndef CF_PLUGIN_FACTORY_H
#define CF_PLUGIN_FACTORY_H

#include "CFPrecompiled.h"
#include <functional>
#include <map>

NS_CF_BEGIN

class CFPluginProtocol;

typedef std::function<CFPluginProtocol*(const char*)> CFPluginCreator;
class CFPluginFactory : public Singleton<CFPluginFactory>
{
public:
    CFPluginFactory(void);
    virtual ~CFPluginFactory(void);

    void registerPlugin(const char* name, const CFPluginCreator& creator);
    CFPluginProtocol* createPlugin(const char* name);
private:
    typedef std::map<std::string, CFPluginCreator> _mapPluginsType;
    _mapPluginsType _mapPlugins;
};

NS_CF_END

#endif // CF_PLUGIN_FACTORY_H
