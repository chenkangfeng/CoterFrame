
#include "cfprecompiled.h"
#include "cfcnetaddr.h"
#include "evutil.h"

NS_CF_BEGIN

CFCNetAddr::CFCNetAddr(void)
{
    memset(&addr_, 0, sizeof(addr_));
}

CFCNetAddr::~CFCNetAddr(void)
{
}

const sockaddr CFCNetAddr::addr(void) const
{
    return addr_.addr;
}

CFInt32 CFCNetAddr::length(void) const
{
    CFInt32 ret = 0;
    switch (family()) {
    case kIPv4:
        ret = sizeof(sockaddr_in);
        break;
    case kIPv6:
        ret = sizeof(sockaddr_in6);
        break;
    default:
        break;
    }
    return ret;
}

void CFCNetAddr::set_addr(struct sockaddr* addr)
{
    switch (addr->sa_family) {
    case kIPv4:
        memcpy(&addr_, addr, sizeof(sockaddr_in));
        break;
    case kIPv6:
        memcpy(&addr_, addr, sizeof(sockaddr_in6));
        break;
    default:
        break;
    }
}

void CFCNetAddr::set_addr(struct sockaddr* addr, socklen_t length)
{
    memcpy(&addr_, addr, length);
}

CFINetAddr::Family CFCNetAddr::family(void) const
{
    return (Family)addr_.addr.sa_family;
}

void CFCNetAddr::set_family(Family family)
{
    addr_.addr.sa_family = family;
}

CFUInt16 CFCNetAddr::port(void) const
{
    CFUInt16 ret = -1;
    switch (family()) {
    case kIPv4:
        ret = ntohs(addr_.ipv4.sin_port);
        break;
    case kIPv6:
        ret = ntohs(addr_.ipv6.sin6_port);
        break;
    default:
        break;
    }
    return ret;
}

void CFCNetAddr::set_port(CFUInt16 port)
{
    switch (family()) {
    case kIPv4:
        addr_.ipv4.sin_port = htons(port);
        break;
    case kIPv6:
        addr_.ipv6.sin6_port = htons(port);
        break;
    default:
        break;
    }
}

std::string CFCNetAddr::ip(void) const
{
    char buffer[128] = {};
    switch (family()) {
    case kIPv4:
        evutil_inet_ntop(AF_INET, &addr_.ipv4.sin_addr, buffer, sizeof(buffer));
        break;
    case kIPv6:
        evutil_inet_ntop(AF_INET6, &addr_.ipv6.sin6_addr, buffer, sizeof(buffer));
        break;
    default:
        break;
    }
    return std::string(buffer);
}

void CFCNetAddr::set_ip(const std::string& ip)
{
    switch (family()) {
    case kIPv4:
        evutil_inet_pton(AF_INET, ip.c_str(), &addr_.ipv4.sin_addr);
        break;
    case kIPv6:
        evutil_inet_pton(AF_INET6, ip.c_str(), &addr_.ipv6.sin6_addr);
        break;
    default:
        break;
    }
}

NS_CF_END
