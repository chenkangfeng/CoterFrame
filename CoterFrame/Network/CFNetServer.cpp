
#include "CFPrecompiled.h"
#include "CFNetServer.h"
#include "event2/thread.h"
#include <thread>

NS_CF_BEGIN

CFNetServer::CFNetServer(CFInt32 cpus) :
_listener(nullptr),
_acceptor(nullptr)
{
    struct event_config* config = event_config_new();
#if CF_PLATFORM(CF_PLATFORM_WIN)
    WSADATA wsaData;
    WSAStartup(0x0201, &wsaData);

    if (nullptr != config) {
        if (event_config_set_flag(config, EVENT_BASE_FLAG_STARTUP_IOCP) < 0) {
            event_config_free(config);
            config = nullptr;
        }
    }
#else
    if (nullptr != config) {
        if (event_config_set_flag(config, EVENT_BASE_FLAG_EPOLL_USE_CHANGELIST) < 0) {
            event_config_free(config);
            config = nullptr;
        }
    }
#endif
    if (nullptr != config) {
        if (event_config_set_num_cpus_hint(config, cpus)) {
            event_config_free(config);
            config = nullptr;
        }
    }

    if (nullptr != config) {
        _base = event_base_new_with_config(config);
        event_config_free(config);
    }
}

CFNetServer::~CFNetServer(void)
{
    if (nullptr != _listener) {
        evconnlistener_free(_listener);
    }
}

CFBool CFNetServer::initServer(const CFNetAddr& addr)
{
    printf("thread id %p\n", std::this_thread::get_id());

    CFBool ret = false;
    if (!_isRunning && nullptr != _base) {
        _isRunning = true;

        _listener = evconnlistener_new_bind(_base, _onAccept, this,
            LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1,
            &addr.getSockAddr().addr, addr.getSockLen());
        if (nullptr == _listener) {
            _closeNetwork();
        }
        else {
            ret = true;
        }
    }

    return ret;
}

void CFNetServer::setAcceptor(const CFNetAcceptor& acceptor)
{
    _acceptor = acceptor;
}

void CFNetServer::_onAccept(struct evconnlistener* listener, evutil_socket_t fd,
struct sockaddr* addr, CFInt32 sockLen, void* data)
{
    printf("thread id %p\n", std::this_thread::get_id());
    CFNetServer* netServer = static_cast<CFNetServer*>(data);
    if (nullptr != netServer) {
        struct event_base* base = netServer->_base;
        if (nullptr != base) {
            struct bufferevent* bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
            if (nullptr != bev) {

            }
        }
    }
}

void CFNetServer::_doAccept(evutil_socket_t fd, const CFNetAddr& addr, struct bufferevent* bev)
{
    if (_acceptor) {
        CFNetObject::SharePtr netObject(new CFNetObject(this, fd, addr, bev));
        _acceptor(netObject);
    }
}

NS_CF_END
