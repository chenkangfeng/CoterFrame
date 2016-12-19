
#include "cfprecompiled.h"
#include "cfcnetclient.h"

NS_CF_BEGIN

CFCNetClient::CFCNetClient(void)
{
#if CF_PLATFORM(CF_PLATFORM_WIN)
    WSADATA wsa_data;
    WSAStartup(MAKEWORD(2, 2), &wsa_data);
#endif
    base_ = event_base_new();
    is_running_ = false;
}

CFCNetClient::~CFCNetClient(void)
{
    close();
}

CFBool CFCNetClient::start(const CFINetAddr::SharedPtr& addr, Callback callback)
{
    addr_ = addr;
    callback_ = callback;

    CFBool ret = false;
    if (!is_running_ && nullptr != base_) {
        is_running_ = true;

        struct bufferevent* bev = bufferevent_socket_new(base_, -1, BEV_OPT_CLOSE_ON_FREE);
        if (nullptr == bev) {
            close();
        }
        else {
            ret = (bufferevent_socket_connect(bev, &addr_->addr(), addr_->length()) == 0);
            if (ret) {
                bufferevent_setcb(bev, nullptr, nullptr, onConnect, this);
            }
            else {
                bufferevent_free(bev);
                close();
            }
        }
    }
    return ret;
}

void CFCNetClient::close(void)
{
    is_running_ = false;
    if (nullptr != base_) {
        event_base_free(base_);
        base_ = nullptr;
    }
}

void CFCNetClient::mainLoop(void)
{
    if (is_running_ && nullptr != base_) {
        event_base_loop(base_, EVLOOP_ONCE | EVLOOP_NONBLOCK);
    }
}

void CFCNetClient::onConnect(struct bufferevent* bev, CFInt16 events, void* data)
{
    CFCNetClient* client = static_cast<CFCNetClient*>(data);
    if (nullptr != client && BEV_EVENT_CONNECTED == events) {
        client->doConnect(bev);
        bufferevent_enable(bev, EV_READ | EV_WRITE);
    }
}

void CFCNetClient::doConnect(struct bufferevent* bev)
{
    if (callback_) {
        evutil_socket_t fd = bufferevent_getfd(bev);
        //CFNetObject::SharePtr netObject(new CF_NOTHROW CFNetObject(this, fd, _addr, bev));
        //callback_(std::move(netObject));
        callback_();
    }
}

NS_CF_END
