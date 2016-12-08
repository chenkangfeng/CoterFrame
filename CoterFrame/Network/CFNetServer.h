
#ifndef CF_NET_SERVER_H
#define CF_NET_SERVER_H

#include "CFPrecompiled.h"
#include <functional>
#include "event2/listener.h"
#include "CFNetwork.h"
#include "CFNetAddr.h"
#include "CFNetObject.h"

NS_CF_BEGIN

typedef std::function<void(CFNetObject::SharePtr)> CFNetAcceptor;
class CFNetServer : public CFNetwork
{
public:
    CFNetServer(CFInt32 cpus);
    virtual ~CFNetServer(void);

    CFBool initServer(const CFNetAddr& addr);
    void setAcceptor(const CFNetAcceptor& acceptor);
private:
    static void _onAccept(struct evconnlistener* listener, evutil_socket_t fd,
        struct sockaddr* addr, CFInt32 sockLen, void* data);

    void _doAccept(evutil_socket_t fd, const CFNetAddr& addr, struct bufferevent* bev);

    struct evconnlistener* _listener;
    CFNetAcceptor _acceptor;
};

NS_CF_END

#endif // CF_NET_SERVER_H
