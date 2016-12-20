
#ifndef CF_I_NET_ADDR_INFO_H
#define CF_I_NET_ADDR_INFO_H

#include <vector>
#include "kernel/cfinterface.hpp"
#include "cfinetaddr.h"

NS_CF_BEGIN

// addr info interface
CF_INTERFACE(CFINetAddrInfo)
{
public:
    CFINetAddrInfo(void) {}
    virtual ~CFINetAddrInfo(void) {}

    // add addr info
    virtual void addAddrInfo(struct addrinfo*) = 0;

    // get addr info size
    virtual CFInt32 size(void) = 0;
    // get addr in addr info
    virtual CFINetAddr::SharedPtr& at(CFInt32) = 0;
};

NS_CF_END

#endif // CF_I_NET_ADDR_INFO_H
