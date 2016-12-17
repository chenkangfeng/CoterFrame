
#ifndef CF_NET_ADDR_INFO_H
#define CF_NET_ADDR_INFO_H

#include "CFPrecompiled.h"
#include <vector>
#include "evutil.h"
#include "CFNetAddr.h"

NS_CF_BEGIN

class CFNetAddrInfo
{
public:
    CFNetAddrInfo(void);
    CFNetAddrInfo(evutil_addrinfo* addrInfo);
    ~CFNetAddrInfo(void);

    void addAddrInfo(evutil_addrinfo* addrInfo);

    CFInt32 size(void);
    CFNetAddr& operator[](CFInt32 index);
private:
    std::vector<CFNetAddr> _vecAddrs;
};

NS_CF_END

#endif // CF_NET_ADDR_INFO_H
