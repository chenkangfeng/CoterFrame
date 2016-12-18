
#include "cfprecompiled.h"
#include "cfcnetaddrinfo.h"

NS_CF_BEGIN

CFCNetAddrInfo::CFCNetAddrInfo(void)
{
}

CFCNetAddrInfo::~CFCNetAddrInfo(void)
{
}

void CFCNetAddrInfo::addAddrInfo(evutil_addrinfo* addr_info)
{
    while (nullptr != addr_info) {
        CF_SHARED_PTR<CFINetAddr> addr = CFINetAddr::createComponent();
        if (addr) {
            addr->set_addr(addr_info->ai_addr, addr_info->ai_addrlen);
            cfvec_addr_.pushBack(std::move(addr));
        }
        addr_info = addr_info->ai_next;
    }
}

CFInt32 CFCNetAddrInfo::size(void)
{
    return cfvec_addr_.size();
}

CFINetAddr& CFCNetAddrInfo::operator[](CFInt32 index)
{
    return *cfvec_addr_[index].get();
}

NS_CF_END
