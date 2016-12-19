
#ifndef CF_I_NET_SERVER_H
#define CF_I_NET_SERVER_H

#include "cfnetwork.h"

NS_CF_BEGIN

// server interface
CF_INTERFACE(CFINetServer, CFUInt8), public CFNetwork
{
public:
    CFINetServer(CFUInt8) {}
    virtual ~CFINetServer(void) {}

    // start server
    virtual CFBool start(const CFINetAddr::SharedPtr&, Callback) = 0;
    // close server
    virtual void close(void) = 0;
    // loop server to dispatch event
    virtual void mainLoop(void) = 0;
};

NS_CF_END

#endif // CF_I_NET_SERVER_H
