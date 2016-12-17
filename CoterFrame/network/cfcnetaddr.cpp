
#include "cfprecompiled.h"
#include "cfcnetaddr.h"

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
    if (family() == AF_INET) {
        ret = sizeof(sockaddr_in);
    }
    else if (family() == AF_INET6) {
        ret = sizeof(sockaddr_in6);
    }
    return ret;
}

void CFCNetAddr::set_addr(struct sockaddr* addr)
{
    if (addr->sa_family == AF_INET) {
        memcpy(&addr_, addr, sizeof(sockaddr_in));
    }
    else if (addr->sa_family == AF_INET6) {
        memcpy(&addr_, addr, sizeof(sockaddr_in6));
    }
}

void CFCNetAddr::set_addr(struct sockaddr* addr, socklen_t length)
{
    memcpy(&addr_, addr, length);
}

CFUInt16 CFCNetAddr::family(void) const
{
    return addr_.addr.sa_family;
}

void CFCNetAddr::set_family(CFUInt16 family)
{
    addr_.addr.sa_family = family;
}

CFUInt16 CFCNetAddr::port(void) const
{
    CFUInt16 ret = -1;
    if (family() == AF_INET) {
        ret = ntohs(addr_.ipv4.sin_port);
    }
    else if (family() == AF_INET6) {
        ret = ntohs(addr_.ipv6.sin6_port);
    }
    return ret;
}

void CFCNetAddr::set_port(CFUInt16 port)
{
    if (family() == AF_INET) {
        addr_.ipv4.sin_port = htons(port);
    }
    else if (family() == AF_INET6) {
        addr_.ipv6.sin6_port = htons(port);
    }
}

std::string CFCNetAddr::ip(void) const
{
    char buffer[128] = {};
    if (family() == AF_INET) {
        evutil_inet_ntop(AF_INET, &addr_.ipv4.sin_addr, buffer, sizeof(buffer));
    }
    else if (family() == AF_INET6) {
        evutil_inet_ntop(AF_INET6, &addr_.ipv6.sin6_addr, buffer, sizeof(buffer));
    }
    return std::string(buffer);
}

void CFCNetAddr::set_ip(const std::string& ip)
{
    if (family() == AF_INET) {
        evutil_inet_pton(AF_INET, ip.c_str(), &addr_.ipv4.sin_addr);
    }
    else if (family() == AF_INET6) {
        evutil_inet_pton(AF_INET6, ip.c_str(), &addr_.ipv6.sin6_addr);
    }
}

NS_CF_END
