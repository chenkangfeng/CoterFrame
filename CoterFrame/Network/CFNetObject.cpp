
#include "CFPrecompiled.h"
#include "CFNetObject.h"
#include "CFNetLock.h"

NS_CF_BEGIN

CFNetObject::CFNetObject(CFNetwork* network, evutil_socket_t fd,
const CFNetAddr& addr, bufferevent* bev) :
_reader(nullptr), _writer(nullptr),
_network(network), _fd(fd), _addr(addr), _bev(bev)
{
    if (nullptr != _bev) {
        bufferevent_setcb(_bev, _onRead, _onWrite, _onEvent, this);
    }
}

CFNetObject::~CFNetObject(void)
{
}

void CFNetObject::setReader(const CFNetReader& reader)
{
    _reader = reader;
    bufferevent_enable(_bev, EV_READ);
}

void CFNetObject::setWriter(const CFNetWriter& writer)
{
    _writer = writer;
    bufferevent_enable(_bev, EV_WRITE);
}

void CFNetObject::sendMessage(const std::string& message)
{
    if (nullptr != _bev) {
        bufferevent_write(_bev, message.data(), message.length());
    }
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

const CFNetAddr& CFNetObject::getNetAddr(void) const
{
    return _addr;
}

void CFNetObject::_onRead(struct bufferevent* bev, void* data)
{
    CFNetObject* netObject = static_cast<CFNetObject*>(data);
    if (nullptr != netObject) {
        netObject->_doRead(bev);
    }
}

void CFNetObject::_onWrite(struct bufferevent* bev, void* data)
{

}

void CFNetObject::_onEvent(struct bufferevent* bev, CFInt16 events, void* data)
{
    printf("onEvent %d\n", events);
}

void CFNetObject::_doRead(struct bufferevent* bev)
{
    if (nullptr != _network) {
        struct evbuffer* input = bufferevent_get_input(bev);
        if (nullptr != input) {
            CFNetLock netLock(_network->isUseThread());
            CFUInt32 len = evbuffer_get_length(input);
            char* buffer = new CF_NOTHROW char[len];
            CFUInt32 recvLen = 0;
            CFUInt32 recvOff = 0;
            while ((recvLen = evbuffer_remove(input, buffer + recvOff, len)) > 0) {
                recvOff += recvLen;
            }
            appendBuffer(buffer, recvOff);
            CF_SAFA_DELETE_ARRAY(buffer);
            if (_reader) {
                _reader(CFNetMessage(_buffer, CFNetHead::UseHead));
            }
        }
    }
}

NS_CF_END
