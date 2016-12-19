
#ifndef CF_I_NET_ADDR_H
#define CF_I_NET_ADDR_H

#include <string>
#include "include/cfmacro.h"
#include "kernel/cfinterface.hpp"
#include "evutil.h"

NS_CF_BEGIN

// addr interface
CF_INTERFACE(CFINetAddr)
{
public:
	// ipv4 ipv6 enum
    typedef enum {
        kIPv4 = AF_INET,
        kIPv6 = AF_INET6
    } Family;

    CFINetAddr(void) {}
    virtual ~CFINetAddr(void) {}

    // get sockaddr
    virtual const sockaddr addr(void) const = 0;
    // get sockaddr length
    virtual CFInt32 length(void) const = 0;
    // init sockaddr
    virtual void set_addr(struct sockaddr*) = 0;
    // init sockaddr with len
    virtual void set_addr(struct sockaddr*, socklen_t) = 0;

    // get ipv4 or ipv6
    virtual Family family(void) const = 0;
    // set ipv4 or ipv6
    virtual void set_family(Family) = 0;

    // get port
    virtual CFUInt16 port(void) const = 0;
    // set port
    virtual void set_port(CFUInt16) = 0;

    // get ip
    virtual std::string ip(void) const = 0;
    // set ip
    virtual void set_ip(const std::string&) = 0;
};

NS_CF_END

#endif // CF_I_NET_ADDR_H
