
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
        CFINetAddr::SharedPtr addr = CFINetAddr::createComponent();
        if (addr) {
            addr->set_addr(addr_info->ai_addr, addr_info->ai_addrlen);
            cfvec_addr_.push_back(std::move(addr));
        }
        addr_info = addr_info->ai_next;
    }
}

CFInt32 CFCNetAddrInfo::size(void)
{
    return cfvec_addr_.size();
}

CFINetAddr::SharedPtr& CFCNetAddrInfo::at(CFInt32 index)
{
    return cfvec_addr_[index];
}

NS_CF_END
