
#ifndef CF_C_NET_DNS_H
#define CF_C_NET_DNS_H

#include "interface/cfinetdns.h"

NS_CF_BEGIN

CF_COMPONENT(CFINetDNS, CFCNetDNS)
{
public:
    CFCNetDNS(void);
    virtual ~CFCNetDNS(void);

    virtual CFBool parse(Protocol protocol, CFStrPtr domain, Callback callback);
};

NS_CF_END

#endif // CF_C_NET_DNS_H
