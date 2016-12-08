
#ifndef CF_NET_CLIENT_H
#define CF_NET_CLIENT_H

#include "CFPrecompiled.h"
#include <functional>
#include "CFNetwork.h"
#include "CFNetAddr.h"
#include "CFNetObject.h"

NS_CF_BEGIN

class CFNetObject;

typedef std::function<void(CFNetObject::SharePtr&&)> CFNetConnector;
class CFNetClient : public CFNetwork
{
public:
    CFNetClient(void);
    virtual ~CFNetClient(void);

    void setConnector(const CFNetConnector& connector);
    CFBool startClient(const CFNetAddr& addr);
private:
    void _doConnect(evutil_socket_t fd, const CFNetAddr& addr, struct bufferevent* bev);

    CFNetConnector _connector;
};

NS_CF_END

#endif // CF_NET_CLIENT_H
