
#ifndef CF_DNS_H
#define CF_DNS_H

#include "CFPrecompiled.h"
#include "evdns.h"
#include "CFNetAddrInfo.h"

NS_CF_BEGIN

class CFDNS
{
public:
    typedef enum {
        TCP = IPPROTO_TCP,
        UDP = IPPROTO_UDP
    } CFProtocol;

    CFDNS(void);
    ~CFDNS(void);

    static CFBool parse(CFProtocol protocol, CFStrPtr domain, CFNetAddrInfo& addrInfo);
private:
    static void _initAddrInfo(CFProtocol protocol, evutil_addrinfo& hints);

    struct event_base* _eventBase;
    struct evdns_base* _evdnsBase;
};

NS_CF_END

#endif // CF_DNS_H
