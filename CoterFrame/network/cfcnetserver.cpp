
#include "cfprecompiled.h"
#include "cfcnetserver.h"
#include "event2/thread.h"

NS_CF_BEGIN

CFCNetServer::CFCNetServer(CFUInt8 cpus) :
CFComponent(cpus),
is_running_(false),
base_(nullptr), listener_(nullptr)
{
    struct event_config* config = event_config_new();
#if CF_PLATFORM(CF_PLATFORM_WIN)
    WSADATA wsa_data;
    WSAStartup(MAKEWORD(2, 2), &wsa_data);

    if (nullptr != config) {
        if (0 != evthread_use_windows_threads()) {
            event_config_free(config);
            config = nullptr;
        }
    }
    if (nullptr != config) {
        if (0 != event_config_set_flag(config, EVENT_BASE_FLAG_STARTUP_IOCP)) {
            event_config_free(config);
            config = nullptr;
        }
    }
#else
    if (nullptr != config) {
        if (0 != evthread_use_pthreads()) {
            event_config_free(config);
            config = nullptr;
        }
    }
    if (nullptr != config) {
        if (0 != event_config_set_flag(config, EVENT_BASE_FLAG_EPOLL_USE_CHANGELIST)) {
            event_config_free(config);
            config = nullptr;
        }
    }
#endif
    if (nullptr != config) {
        if (0 != event_config_set_num_cpus_hint(config, cpus)) {
            event_config_free(config);
            config = nullptr;
        }
    }
    if (nullptr != config) {
        base_ = event_base_new_with_config(config);
        event_config_free(config);
    }
}

CFCNetServer::~CFCNetServer(void)
{
    close();
}

CFBool CFCNetServer::start(const CFINetAddr::SharedPtr& addr, Callback callback)
{
    callback_ = callback;

    CFBool ret = false;
    if (!is_running_ && nullptr != base_) {
        is_running_ = true;

        listener_ = evconnlistener_new_bind(base_, onAccept, this,
            LEV_OPT_THREADSAFE | LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1,
            &addr->addr(), addr->length());
        if (nullptr == listener_) {
            close();
        }
        else {
            ret = true;
        }
    }

    return ret;
}

void CFCNetServer::close(void)
{
    is_running_ = false;
    if (nullptr != listener_) {
        evconnlistener_free(listener_);
        listener_ = nullptr;
    }
    if (nullptr != base_) {
        event_base_free(base_);
        base_ = nullptr;
    }
}

void CFCNetServer::mainLoop(void)
{
    if (is_running_ && nullptr != base_) {
        event_base_loop(base_, EVLOOP_ONCE | EVLOOP_NONBLOCK);
    }
}

void CFCNetServer::onAccept(struct evconnlistener* listener, evutil_socket_t fd,
                            struct sockaddr* addr, CFInt32 sockLen, void* data)
{
    CFCNetServer* server = static_cast<CFCNetServer*>(data);
    if (nullptr != server) {
        struct event_base* base = server->base_;
        if (nullptr != base) {
            struct bufferevent* bev = bufferevent_socket_new(base, fd, LEV_OPT_THREADSAFE | BEV_OPT_CLOSE_ON_FREE);
            if (nullptr != bev) {
                server->doAccept(fd, addr, bev);
            }
        }
    }
}

void CFCNetServer::doAccept(evutil_socket_t fd, struct sockaddr* addr, struct bufferevent* bev)
{
    if (callback_) {
        //CFNetObject::SharePtr netObject(new CF_NOTHROW CFNetObject(this, fd, addr, bev));
        //_acceptor(std::move(netObject));
        callback_();
    }
}

NS_CF_END
