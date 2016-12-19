
#ifndef CF_I_NET_DNS_H
#define CF_I_NET_DNS_H

#include <functional>
#include "include/cfmacro.h"
#include "cfinetaddrinfo.h"

NS_CF_BEGIN

// dns interface
CF_INTERFACE(CFINetDNS)
{
public:
    // tcp udp enum
    typedef enum {
        kTCP = IPPROTO_TCP,
        kUDP = IPPROTO_UDP
    } Protocol;
    // dns callback
    typedef std::function<void(CFINetAddrInfo::SharedPtr&&)> Callback;

    CFINetDNS(void) {}
    virtual ~CFINetDNS(void) {}

    // parse domain
    virtual CFBool parse(Protocol, CFStrPtr, Callback) = 0;
};

NS_CF_END

#endif // CF_I_NET_DNS_H
