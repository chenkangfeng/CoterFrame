
#ifndef CF_C_NET_ADDR_H
#define CF_C_NET_ADDR_H

#include "interface/cfinetaddr.h"

NS_CF_BEGIN

// addr component
CF_COMPONENT(CFINetAddr, CFCNetAddr)
{
public:
    CFCNetAddr(void);
    virtual ~CFCNetAddr(void);

    // get sockaddr
    virtual const sockaddr addr(void) const;
    // get sockaddr length
    virtual CFInt32 length(void) const;
    // init sockaddr
    virtual void set_addr(struct sockaddr* addr);
    // init sockaddr
    virtual void set_addr(struct sockaddr* addr, socklen_t length);

    // get ipv4 or ipv6
    virtual Family family(void) const;
    // set ipv4 or ipv6
    virtual void set_family(Family family);

    // get port
    virtual CFUInt16 port(void) const;
    // set port
    virtual void set_port(CFUInt16 port);

    // get ip
    virtual std::string ip(void) const;
    // set ip
    virtual void set_ip(const std::string& ip);
private:
    // ipv4 and ipv6 union
    typedef union {
        struct sockaddr addr;
        struct sockaddr_in ipv4;
        struct sockaddr_in6 ipv6;
    } SockAddr;

    // sockaddr union
    SockAddr addr_;
};

NS_CF_END

#endif // CF_C_NET_ADDR_H
