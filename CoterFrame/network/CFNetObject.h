
#ifndef CF_NET_OBJECT_H
#define CF_NET_OBJECT_H

#include "CFPrecompiled.h"
#include <functional>
#include "CFNetwork.h"
#include "CFNetAddr.h"
#include "CFNetBuffer.h"
#include "CFNetMessage.h"

NS_CF_BEGIN

typedef std::function<void(CFNetMessage&&)> CFNetReader;
typedef std::function<void(CFNetMessage&&)> CFNetWriter;
class CFNetObject : public CFSharePtr<CFNetObject>
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

#endif // CF_NET_OBJECT_H
