
#ifndef CF_C_NET_ADDR_INFO_H
#define CF_C_NET_ADDR_INFO_H

#include "interface/cfinetaddrinfo.h"
#include "kernel/cfstl.hpp"

NS_CF_BEGIN

// addr info component
CF_COMPONENT(CFINetAddrInfo, CFCNetAddrInfo)
{
public:
    CFCNetAddrInfo(void);
    virtual ~CFCNetAddrInfo(void);

    // add addr info
    virtual void addAddrInfo(evutil_addrinfo* addr_info);

    // get addr info size
    virtual CFInt32 size(void);
    // get addr in addr info
    virtual CFINetAddr::SharedPtr& at(CFInt32 index);
private:
    // addr vector
    CFVector<CFINetAddr> cfvec_addr_;
};

NS_CF_END

#endif // CF_C_NET_ADDR_INFO_H
