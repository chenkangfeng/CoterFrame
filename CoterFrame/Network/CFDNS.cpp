
#include "CFPrecompiled.h"
#include "CFDNS.h"

NS_CF_BEGIN

CFDNS::CFDNS(void) :
_eventBase(nullptr),
_evdnsBase(nullptr)
{

}

CFDNS::~CFDNS(void)
{

}

CFBool CFDNS::parse(CFProtocol protocol, CFStrPtr domain, CFNetAddrInfo& addrInfo)
{
    evutil_addrinfo hints, *result;
    _initAddrInfo(protocol, hints);

    CFBool ret = (evutil_getaddrinfo(domain, nullptr, &hints, &result) == 0);
    if (ret){
        addrInfo.addAddrInfo(result);
    }
    evutil_freeaddrinfo(result);
    return ret;
}

void CFDNS::_initAddrInfo(CFProtocol protocol, evutil_addrinfo& hints)
{
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_CANONNAME;
    switch (protocol)
    {
    case TCP:
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        break;
    case UDP:
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_protocol = IPPROTO_UDP;
        break;
    default:
        break;
    }
}

NS_CF_END
