
#ifndef CF_C_NET_OBJECT_H
#define CF_C_NET_OBJECT_H

#include "interface/cfinetobject.h"

NS_CF_BEGIN

CF_COMPONENT(CFINetObject, CFCNetObject)
{
public:
    CFNetObject(CFNetwork* network, evutil_socket_t fd,
        const CFNetAddr& addr, bufferevent* bev);
    ~CFNetObject();

    void setReader(const CFNetReader& reader);
    void setWriter(const CFNetWriter& writer);

    void sendMessage(const std::string& message);

    const CFNetAddr& netAddr(void) const;
private:
    static void _onRead(struct bufferevent* bev, void* data);
    static void _onWrite(struct bufferevent* bev, void* data);
    static void _onEvent(struct bufferevent* bev, CFInt16 events, void* data);

    void _doRead(struct bufferevent* bev);

    CFNetReader _reader;
    CFNetWriter _writer;

    CFNetBuffer _buffer;

    CFNetwork* _network;
    evutil_socket_t _fd;
    CFNetAddr _addr;
    bufferevent* _bev;
};

NS_CF_END

#endif // CF_C_NET_OBJECT_H
