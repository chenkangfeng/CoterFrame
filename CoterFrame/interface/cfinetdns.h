
#ifndef CF_I_NET_DNS_H
#define CF_I_NET_DNS_H

#include <functional>
#include "include/cfmacro.h"
#include "cfinetaddrinfo.h"

NS_CF_BEGIN

CF_INTERFACE(CFINetDNS)
{
public:
    typedef enum {
        kTCP = IPPROTO_TCP,
        kUDP = IPPROTO_UDP
    } Protocol;
    typedef std::function<void(CFINetAddrInfo::SharedPtr&&)> DNSCallback;

    CFINetDNS(void) {}
    virtual ~CFINetDNS(void) {}

    virtual CFBool parse(Protocol protocol, CFStrPtr domain, DNSCallback dns_callback) = 0;
};

NS_CF_END

#endif // CF_I_NET_DNS_H
