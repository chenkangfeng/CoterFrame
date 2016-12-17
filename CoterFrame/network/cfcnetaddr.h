
#ifndef CF_C_NET_ADDR_H
#define CF_C_NET_ADDR_H

#include "interface/cfinetaddr.h"

NS_CF_BEGIN

CF_COMPONENT(CFINetAddr, CFCNetAddr)
{
public:
    CFCNetAddr(void);
    virtual ~CFCNetAddr(void);

    virtual const sockaddr addr(void) const;
    virtual CFInt32 length(void) const;
    virtual void set_addr(struct sockaddr* addr);
    virtual void set_addr(struct sockaddr* addr, socklen_t length);

    virtual CFUInt16 family(void) const;
    virtual void set_family(CFUInt16 family);

    virtual CFUInt16 port(void) const;
    virtual void set_port(CFUInt16 port);

    virtual std::string ip(void) const;
    virtual void set_ip(const std::string& ip);
private:
    typedef union {
        struct sockaddr addr;
        struct sockaddr_in ipv4;
        struct sockaddr_in6 ipv6;
    } CFSockAddr;

    CFSockAddr addr_;
};

NS_CF_END

#endif // CF_C_NET_ADDR_H
