
#include "cfprecompiled.h"
#include "cfcnetdns.h"
#include "include/cfplatform.h"
#include "kernel/cfsharedptr.hpp"

NS_CF_BEGIN

CFCNetDNS::CFCNetDNS(void)
{
#if CF_PLATFORM(CF_PLATFORM_WIN)
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
}

CFCNetDNS::~CFCNetDNS(void)
{
}

CFBool CFCNetDNS::parse(Protocol protocol, CFStrPtr domain, DNSCallback dns_callback)
{
    evutil_addrinfo hints, *result = nullptr;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = EVUTIL_AI_CANONNAME;
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

    CFBool ret = false;
    CFINetAddrInfo::SharedPtr addr_info = CFINetAddrInfo::createComponent();
    if (addr_info) {
        ret = (evutil_getaddrinfo(domain, nullptr, &hints, &result) == 0);
        if (ret){
            addr_info->addAddrInfo(result);
            evutil_freeaddrinfo(result);
        }
    }
    if (dns_callback) {
        dns_callback(std::move(addr_info));
    }
    return ret;
}

NS_CF_END
