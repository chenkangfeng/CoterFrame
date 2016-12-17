
#ifndef CF_NET_ADDR_H
#define CF_NET_ADDR_H

#include "CFPrecompiled.h"
#include "evutil.h"

NS_CF_BEGIN

class CFNetAddr
{
public:
    CFNetAddr(void);
    CFNetAddr(struct sockaddr* addr);
    CFNetAddr(struct sockaddr* addr, socklen_t len);
    CFNetAddr(CFUInt16 family, CFUInt16 port, const std::string& ip);
    ~CFNetAddr(void);

    const sockaddr addr(void) const;
    CFInt32 length(void) const;

    CFUInt16 family(void) const;
    void setFamily(CFUInt16 family);

    CFUInt16 port(void) const;
    void setPort(CFUInt16 port);

    std::string ip(void) const;
    void setIp(const std::string& ip);
private:
    typedef union {
        struct sockaddr addr;
        struct sockaddr_in ipv4;
        struct sockaddr_in6 ipv6;
    } CFSockAddr;

    void _initAddr(void);

    CFSockAddr _addr;
};

NS_CF_END

#endif // CF_NET_ADDR_H
