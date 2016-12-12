
#ifndef CF_NET_CLIENT_H
#define CF_NET_CLIENT_H

#include "CFPrecompiled.h"
#include <functional>
#include "CFNetwork.h"
#include "CFNetAddr.h"
#include "CFNetObject.h"

NS_CF_BEGIN

typedef std::function<void(CFNetObject::SharePtr&&)> CFNetConnector;
class CFNetClient : public CFNetwork
{
public:
    CFNetClient(void);
    virtual ~CFNetClient(void);

    void setConnector(const CFNetConnector& connector);
    CFBool startClient(const CFNetAddr& addr);
private:
    static void _onConnect(struct bufferevent* bev, CFInt16 events, void* data);

    void _doConnect(struct bufferevent* bev);

    CFNetAddr _addr;
    CFNetConnector _connector;
};

NS_CF_END

#endif // CF_NET_CLIENT_H
