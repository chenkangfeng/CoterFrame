
#ifndef CF_C_NET_SERVER_H
#define CF_C_NET_SERVER_H

#include "interface/cfinetserver.h"
#include "event.h"
#include "event2/listener.h"

NS_CF_BEGIN

// server component
CF_COMPONENT(CFINetServer, CFCNetServer, CFUInt8), public std::enable_shared_from_this<CFCNetServer>
{
public:
    CFCNetServer(CFUInt8 cpus);
    virtual ~CFCNetServer(void);

    // start server
    virtual CFBool start(const CFINetAddr::SharedPtr& addr, Callback callback);
    // close server
    virtual void close(void);
    // loop server to dispatch event
    virtual void mainLoop(void);
private:
    // on accept after server start
    static void onAccept(struct evconnlistener* listener, evutil_socket_t fd,
                         struct sockaddr* addr, CFInt32 sockLen, void* data);
    // do accept after accpet
    void doAccept(evutil_socket_t fd, struct sockaddr* addr, struct bufferevent* bev);

    // callback when accpet
    Callback callback_;

    // is running of server
    CFBool is_running_;
    // libevent event base
    struct event_base* base_;
    // libevent event listener
    struct evconnlistener* listener_;
};

NS_CF_END

#endif // CF_C_NET_SERVER_H
