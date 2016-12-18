
#ifndef CF_C_NET_ADDR_INFO_H
#define CF_C_NET_ADDR_INFO_H

#include "interface/cfinetaddrinfo.h"
#include "kernel/cfstl.hpp"

NS_CF_BEGIN

CF_COMPONENT(CFINetAddrInfo, CFCNetAddrInfo)
{
public:
    CFCNetAddrInfo(void);
    virtual ~CFCNetAddrInfo(void);

    virtual void addAddrInfo(evutil_addrinfo* addr_info);

    virtual CFInt32 size(void);
    virtual CFINetAddr::SharedPtr& at(CFInt32 index);
private:
    CFVector<CFINetAddr> cfvec_addr_;
};

NS_CF_END

#endif // CF_C_NET_ADDR_INFO_H
