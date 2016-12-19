
#ifndef CF_C_NET_CLIENT_H
#define CF_C_NET_CLIENT_H

#include "interface/cfinetclient.h"
#include "event.h"

NS_CF_BEGIN

CF_COMPONENT(CFINetClient, CFCNetClient), public std::enable_shared_from_this<CFCNetClient>
{
public:
    CFCNetClient(void);
    virtual ~CFCNetClient(void);

    virtual CFBool start(const CFINetAddr::SharedPtr& addr, Callback callback);
    virtual void close(void);
    virtual void mainLoop(void);
private:
    static void onConnect(struct bufferevent* bev, CFInt16 events, void* data);
    void doConnect(struct bufferevent* bev);

    CFINetAddr::SharedPtr addr_;
    Callback callback_;

    CFBool is_running_;
    struct event_base* base_;
};

NS_CF_END

#endif // CF_C_NET_CLIENT_H
