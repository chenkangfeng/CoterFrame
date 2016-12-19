
#ifndef CF_I_NET_CLIENT_H
#define CF_I_NET_CLIENT_H

#include "cfnetwork.h"

NS_CF_BEGIN

CF_INTERFACE(CFINetClient), public CFNetwork
{
public:
    CFINetClient(void) {}
    virtual ~CFINetClient(void) {}

    virtual CFBool start(const CFINetAddr::SharedPtr&, Callback) = 0;
    virtual void close(void) = 0;
    virtual void mainLoop(void) = 0;
};

NS_CF_END

#endif // CF_I_NET_CLIENT_H
