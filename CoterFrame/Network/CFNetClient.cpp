
#include "CFPrecompiled.h"
#include "CFNetClient.h"
#include "CFNetObject.h"

NS_CF_BEGIN

CFNetClient::CFNetClient(void) :
_connector(nullptr)
{
#ifdef CF_PLATFORM(CF_WIN)
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    _base = event_base_new();
}

CFNetClient::~CFNetClient(void)
{
}

void CFNetClient::setConnector(const CFNetConnector& connector)
{
    _connector = connector;
}

CFBool CFNetClient::startClient(const CFNetAddr& addr)
{
    CFBool ret = false;
    if (!_isRunning && nullptr != _base) {
        _isRunning = true;

        struct bufferevent* bev = bufferevent_socket_new(_base, -1, BEV_OPT_CLOSE_ON_FREE);
        if (nullptr == bev) {
            _closeNetwork();
        }

        if (nullptr != bev) {
            int ret = bufferevent_socket_connect(bev, &addr.getSockAddr().addr, addr.getSockLen());
            if (0 != ret) {
                bufferevent_free(bev);
                _closeNetwork();
                return false;
            }
            else {
                evutil_socket_t fd = bufferevent_getfd(bev);
                bufferevent_enable(bev, EV_READ | EV_WRITE);
                _doConnect(fd, addr, bev);
                ret = true;
            }
        }
    }

    return ret;
}

void CFNetClient::_doConnect(evutil_socket_t fd, const CFNetAddr& addr, struct bufferevent* bev)
{
    if (_connector) {
        CFNetObject::SharePtr netObject(new CF_NOTHROW CFNetObject(this, fd, addr, bev));
        _connector(std::move(netObject));
    }
}

NS_CF_END
