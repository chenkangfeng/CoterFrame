
#ifndef CF_C_NET_CLIENT_H
#define CF_C_NET_CLIENT_H

#include "interface/cfinetclient.h"
#include "event.h"

NS_CF_BEGIN

// client component
CF_COMPONENT(CFINetClient, CFCNetClient), public std::enable_shared_from_this<CFCNetClient>
{
public:
    CFCNetClient(void);
    virtual ~CFCNetClient(void);

    // start client
    virtual CFBool start(const CFINetAddr::SharedPtr& addr, Callback callback);
    // close client
    virtual void close(void);
    // loop client to dispatch event
    virtual void mainLoop(void);
private:
    // on connect after client start
    static void onConnect(struct bufferevent* bev, CFInt16 events, void* data);
    // do connect after connect
    void doConnect(struct bufferevent* bev);

    // client addr
    CFINetAddr::SharedPtr addr_;
    // callback when connect
    Callback callback_;

    // is running of client
    CFBool is_running_;
    // libevent event base
    struct event_base* base_;
};

NS_CF_END

#endif // CF_C_NET_CLIENT_H
