
#ifndef CF_NETWORK_H
#define CF_NETWORK_H

#include <functional>
#include "include/cfmacro.h"
#include "cfinetaddr.h"

NS_CF_BEGIN

// network baseclass
class CFNetwork
{
public:
    typedef std::function<void(void)> Callback;

    CFNetwork(void) {}
    virtual ~CFNetwork(void) {}

    // start network
    virtual CFBool start(const CFINetAddr::SharedPtr&, Callback) = 0;
    // close network
    virtual void close(void) = 0;
    // main loop network
    virtual void mainLoop(void) = 0;
};

NS_CF_END

#endif // CF_NETWORK_H
