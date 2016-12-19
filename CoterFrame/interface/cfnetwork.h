
#ifndef CF_NETWORK_H
#define CF_NETWORK_H

#include <functional>
#include "include/cfmacro.h"
#include "cfinetaddr.h"

NS_CF_BEGIN

class CFNetwork
{
public:
    typedef std::function<void(void)> Callback;

    CFNetwork(void) {}
    virtual ~CFNetwork(void) {}

    virtual CFBool start(const CFINetAddr::SharedPtr&, Callback) = 0;
    virtual void close(void) = 0;
    virtual void mainLoop(void) = 0;
};

NS_CF_END

#endif // CF_NETWORK_H
