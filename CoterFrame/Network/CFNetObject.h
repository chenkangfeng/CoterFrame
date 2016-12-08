
#ifndef CF_NET_OBJECT_H
#define CF_NET_OBJECT_H

#include "CFPrecompiled.h"
#include <string>
#include <functional>
#include "CFNetwork.h"
#include "CFNetAddr.h"

NS_CF_BEGIN

class CFNetObject : public CFSharePtr<CFNetObject>
{
public:
    CFNetObject(CFNetwork* network, evutil_socket_t fd,
        const CFNetAddr& addr, bufferevent* bev);
    ~CFNetObject();

    const char* getBuffer();
    CFUInt32 getBufferLen() const;
    void appendBuffer(const char* str, CFUInt32 len);
    void removeBuffer(CFUInt32 start, CFUInt32 len);
private:
    static void _onRead(struct bufferevent* bev, void* data);
    static void _onWrite(struct bufferevent* bev, void* data);
    static void _onEvent(struct bufferevent* bev, CFInt16 events, void* data);

    std::string _buffer;

    CFNetwork* _network;
    evutil_socket_t _fd;
    CFNetAddr _addr;
    bufferevent* _bev;
};

NS_CF_END

#endif // CF_NET_OBJECT_H
