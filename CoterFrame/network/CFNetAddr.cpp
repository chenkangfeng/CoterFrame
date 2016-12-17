
#include "CFPrecompiled.h"
#include "CFNetAddr.h"

NS_CF_BEGIN

CFNetAddr::CFNetAddr(void)
{
    _initAddr();
}

CFNetAddr::CFNetAddr(struct sockaddr* addr)
{
    _initAddr();
    if (addr->sa_family == AF_INET) {
        memcpy(&_addr, addr, sizeof(sockaddr_in));
    }
    else if (addr->sa_family == AF_INET6) {
        memcpy(&_addr, addr, sizeof(sockaddr_in6));
    }
}

CFNetAddr::CFNetAddr(struct sockaddr* addr, socklen_t len)
{
    _initAddr();
    memcpy(&_addr, addr, len);
}

CFNetAddr::CFNetAddr(CFUInt16 family, CFUInt16 port, const std::string& ip)
{
    _initAddr();
    setFamily(family);
    setPort(port);
    setIp(ip);
}

CFNetAddr::~CFNetAddr(void)
{
}

const sockaddr CFNetAddr::addr(void) const
{
    return _addr.addr;
}

CFInt32 CFNetAddr::length(void) const
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

CFUInt16 CFNetAddr::family(void) const
{
    return _addr.addr.sa_family;
}

void CFNetAddr::setFamily(CFUInt16 family)
{
    _addr.addr.sa_family = family;
}

CFUInt16 CFNetAddr::port(void) const
{
    CFUInt16 ret = -1;
    if (family() == AF_INET) {
        ret = ntohs(_addr.ipv4.sin_port);
    }
    else if (family() == AF_INET6) {
        ret = ntohs(_addr.ipv6.sin6_port);
    }
    return ret;
}

void CFNetAddr::setPort(CFUInt16 port)
{
    if (family() == AF_INET) {
        _addr.ipv4.sin_port = htons(port);
    }
    else if (family() == AF_INET6) {
        _addr.ipv6.sin6_port = htons(port);
    }
}

std::string CFNetAddr::ip(void) const
{
    char buffer[128] = {};
    if (family() == AF_INET) {
        evutil_inet_ntop(AF_INET, &_addr.ipv4.sin_addr, buffer, sizeof(buffer));
    }
    else if (family() == AF_INET6) {
        evutil_inet_ntop(AF_INET6, &_addr.ipv6.sin6_addr, buffer, sizeof(buffer));
    }
    return std::string(buffer);
}

void CFNetAddr::setIp(const std::string& ip)
{
    if (family() == AF_INET) {
        evutil_inet_pton(AF_INET, ip.c_str(), &_addr.ipv4.sin_addr);
    }
    else if (family() == AF_INET6) {
        evutil_inet_pton(AF_INET6, ip.c_str(), &_addr.ipv6.sin6_addr);
    }
}

void CFNetAddr::_initAddr(void)
{
    memset(&_addr, 0, sizeof(_addr));
}

NS_CF_END
