
#ifndef CF_C_NET_SERVER_H
#define CF_C_NET_SERVER_H

#include "interface/cfinetserver.h"
#include "event.h"
#include "event2/listener.h"

NS_CF_BEGIN

CF_COMPONENT(CFINetServer, CFCNetServer, CFUInt8), public std::enable_shared_from_this<CFCNetServer>
{
public:
    CFCNetServer(CFUInt8 cpus);
    virtual ~CFCNetServer(void);

    virtual CFBool start(const CFINetAddr::SharedPtr& addr, Callback callback);
    virtual void close(void);
    virtual void mainLoop(void);
private:
    static void onAccept(struct evconnlistener* listener, evutil_socket_t fd,
                         struct sockaddr* addr, CFInt32 sockLen, void* data);
    void doAccept(evutil_socket_t fd, struct sockaddr* addr, struct bufferevent* bev);

    Callback callback_;

    CFBool is_running_;
    struct event_base* base_;
    struct evconnlistener* listener_;
};

NS_CF_END

#endif // CF_C_NET_SERVER_H
