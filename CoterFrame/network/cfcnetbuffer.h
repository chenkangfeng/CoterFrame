
#ifndef CF_NET_BUFFER_H
#define CF_NET_BUFFER_H

#include "CFPrecompiled.h"
#include "CFNetLock.h"

NS_CF_BEGIN

class CFNetBuffer
{
public:
    CFNetBuffer(CFBool isEnableLock = false);
    ~CFNetBuffer(void);

    CFUInt32 length() const;
    void appendBuffer(CFStrPtr str, CFUInt32 len);
    void removeBuffer(CFUInt32 pos, CFUInt32 len);
private:
    std::string _buffer;

    CFBool _isEnableLock;
    CFNetLock _lock;
};

NS_CF_END

#endif // CF_NET_BUFFER_H
