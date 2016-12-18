
#ifndef CF_I_NET_ADDR_H
#define CF_I_NET_ADDR_H

#include <string>
#include "include/cfmacro.h"
#include "kernel/cfinterface.hpp"
#include "evutil.h"

NS_CF_BEGIN

CF_INTERFACE(CFINetAddr)
{
public:
    typedef enum {
        kIPv4 = AF_INET,
        kIPv6 = AF_INET6
    } Family;

    CFINetAddr(void) {}
    virtual ~CFINetAddr(void) {}

    virtual const sockaddr addr(void) const = 0;
    virtual CFInt32 length(void) const = 0;
    virtual void set_addr(struct sockaddr*) = 0;
    virtual void set_addr(struct sockaddr*, socklen_t) = 0;

    virtual Family family(void) const = 0;
    virtual void set_family(Family) = 0;

    virtual CFUInt16 port(void) const = 0;
    virtual void set_port(CFUInt16) = 0;

    virtual std::string ip(void) const = 0;
    virtual void set_ip(const std::string&) = 0;
};

NS_CF_END

#endif // CF_I_NET_ADDR_H
