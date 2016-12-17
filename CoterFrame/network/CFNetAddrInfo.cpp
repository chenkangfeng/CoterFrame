
#include "CFPrecompiled.h"
#include "CFNetAddrInfo.h"

NS_CF_BEGIN

CFNetAddrInfo::CFNetAddrInfo(void)
{
}

CFNetAddrInfo::CFNetAddrInfo(evutil_addrinfo* addrInfo)
{
    addAddrInfo(addrInfo);
}

CFNetAddrInfo::~CFNetAddrInfo(void)
{
}

void CFNetAddrInfo::addAddrInfo(evutil_addrinfo* addrInfo)
{
    while (nullptr != addrInfo) {
        _vecAddrs.push_back(std::move(CFNetAddr(addrInfo->ai_addr, addrInfo->ai_addrlen)));
        addrInfo = addrInfo->ai_next;
    }
}

CFInt32 CFNetAddrInfo::size(void)
{
    return static_cast<CFInt32>(_vecAddrs.size());
}

CFNetAddr& CFNetAddrInfo::operator[](CFInt32 index)
{
    return _vecAddrs[index];
}

NS_CF_END
