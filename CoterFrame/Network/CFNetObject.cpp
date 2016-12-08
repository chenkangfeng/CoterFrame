
#include "CFPrecompiled.h"
#include "CFNetObject.h"

NS_CF_BEGIN

CFNetObject::CFNetObject(CFNetwork* network, evutil_socket_t fd,
    const CFNetAddr& addr, bufferevent* bev) :
    _network(network), _fd(fd), _addr(addr), _bev(bev)
{
    if (nullptr != _bev) {
        bufferevent_setcb(_bev, _onRead, _onWrite, _onEvent, this);
        bufferevent_enable(_bev, EV_READ | EV_WRITE);
    }
}

CFNetObject::~CFNetObject(void)
{
}

const char* CFNetObject::getBuffer(void)
{
    return _buffer.data();
}

CFUInt32 CFNetObject::getBufferLen(void) const
{
    return _buffer.length();
}

void CFNetObject::appendBuffer(const char* str, CFUInt32 len)
{
    _buffer.append(str, len);
}

void CFNetObject::removeBuffer(CFUInt32 start, CFUInt32 len)
{
    if (start >= 0 && start + len <= _buffer.length()) {
        _buffer.erase(start, len);
    }
}

void CFNetObject::_onRead(struct bufferevent* bev, void* data)
{

}

void CFNetObject::_onWrite(struct bufferevent* bev, void* data)
{

}

void CFNetObject::_onEvent(struct bufferevent* bev, CFInt16 events, void* data)
{

}

NS_CF_END
