
#include "CFPrecompiled.h"
#include "CFNetClient.h"
#include "CFNetObject.h"

NS_CF_BEGIN

CFNetClient::CFNetClient(void) :
_connector(nullptr)
{
    CFBool initFailed = false;
#if CF_PLATFORM(CF_WIN)
    WSADATA wsaData;
    if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        initFailed = true;
    }
#endif
    if (!initFailed) {
        _base = event_base_new();
    }
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
    _addr = addr;

    CFBool ret = false;
    if (!_isRunning && nullptr != _base) {
        _isRunning = true;

        struct bufferevent* bev = bufferevent_socket_new(_base, -1, BEV_OPT_CLOSE_ON_FREE);
        if (nullptr == bev) {
            _closeNetwork();
        }

        if (nullptr != bev) {
            int ret = bufferevent_socket_connect(bev, &addr.addr(), addr.length());
            if (0 != ret) {
                bufferevent_free(bev);
                _closeNetwork();
                return false;
            }
            else {
                bufferevent_setcb(bev, nullptr, nullptr, _onConnect, this);
                ret = true;
            }
        }
    }

    return ret;
}

void CFNetClient::_onConnect(struct bufferevent* bev, CFInt16 events, void* data)
{
    CFNetClient* netClient = static_cast<CFNetClient*>(data);
    if (nullptr != netClient && BEV_EVENT_CONNECTED == events) {
        netClient->_doConnect(bev);
        bufferevent_enable(bev, EV_READ | EV_WRITE);
    }
}

void CFNetClient::_doConnect(struct bufferevent* bev)
{
    if (_connector) {
        evutil_socket_t fd = bufferevent_getfd(bev);
        CFNetObject::SharePtr netObject(new CF_NOTHROW CFNetObject(this, fd, _addr, bev));
        _connector(std::move(netObject));
    }
}

NS_CF_END
