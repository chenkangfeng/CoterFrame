
#include "CFPrecompiled.h"
#include "CFNetClient.h"
#include "CFNetObject.h"

NS_CF_BEGIN

CFNetClient::CFNetClient(void) :
_connector(nullptr)
{
#ifdef CF_PLATFORM(CF_PLATFORM_WIN)
    WSADATA wsaData;
    WSAStartup(0x0201, &wsaData);
#endif
    _base = event_base_new();
}

CFNetClient::~CFNetClient(void)
{
}

CFBool CFNetClient::initClient(const CFNetAddr& addr)
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
                _doConnect(fd, addr, bev);
                ret = true;
            }
        }
    }

    return ret;
}

void CFNetClient::setConnector(const CFNetConnector& connector)
{
    _connector = connector;
}

void CFNetClient::_doConnect(evutil_socket_t fd, const CFNetAddr& addr, struct bufferevent* bev)
{
    if (_connector) {
        CFNetObject::SharePtr netObject(new CFNetObject(this, fd, addr, bev));
        _connector(netObject);
    }
}

NS_CF_END
