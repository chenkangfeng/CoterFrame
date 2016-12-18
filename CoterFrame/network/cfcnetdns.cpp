
#include "cfprecompiled.h"
#include "cfcnetdns.h"
#include "kernel/cfsharedptr.hpp"

NS_CF_BEGIN

CFCNetDNS::CFCNetDNS(void)
{
}

CFCNetDNS::~CFCNetDNS(void)
{
}

CFBool CFCNetDNS::parse(Protocol protocol, CFStrPtr domain, DNSCallback dns_callback)
{
    evutil_addrinfo hints, *result = nullptr;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_CANONNAME;
    switch (protocol)
    {
    case kTCP:
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        break;
    case kUDP:
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_protocol = IPPROTO_UDP;
        break;
    default:
        break;
    }

    CFBool ret = (evutil_getaddrinfo(domain, nullptr, &hints, &result) == 0);
    if (ret){
        CF_SHARED_PTR<CFINetAddrInfo> addr_info = CFINetAddrInfo::createComponent();
        if (addr_info) {
            addr_info->addAddrInfo(result);
            dns_callback(std::move(*addr_info.get()));
        }
        evutil_freeaddrinfo(result);
    }
    return ret;
}

NS_CF_END
