
#ifndef CF_I_NET_ADDR_INFO_H
#define CF_I_NET_ADDR_INFO_H

#include <vector>
#include "kernel/cfinterface.hpp"
#include "cfinetaddr.h"

NS_CF_BEGIN

CF_INTERFACE(CFINetAddrInfo)
{
public:
    CFINetAddrInfo(void) {}
    virtual ~CFINetAddrInfo(void) {}

    virtual void addAddrInfo(evutil_addrinfo*) = 0;

    virtual CFInt32 size(void) = 0;
    virtual CFINetAddr::SharedPtr& at(CFInt32) = 0;
};

NS_CF_END

#endif // CF_I_NET_ADDR_INFO_H
